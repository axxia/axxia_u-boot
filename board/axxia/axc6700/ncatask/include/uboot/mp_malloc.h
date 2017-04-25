/* 
*	MP-Malloc: Malloc for memory pools.
*
*	This library is a work derived from the GNU malloc library.
*	Changes by Dirk Meyer, Chair of Process Control Engineering,
*	RWTH Aachen/Germany (dirk@plt.rwth-aachen.de).
*
*	$Id: mp_malloc.h,v 1.2 2006/05/23 15:09:04 vj4 Exp $
*/

/* Declarations for `mp_malloc' and friends.
   Copyright 1990, 1991, 1992, 1993, 1995 Free Software Foundation, Inc.
		  Written May 1989 by Mike Haertel.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public License as
published by the Free Software Foundation; either version 2 of the
License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with this library; see the file COPYING.LIB.  If
not, write to the Free Software Foundation, Inc., 675 Mass Ave,
Cambridge, MA 02139, USA.

   The author may be reached (Email) at the address mike@ai.mit.edu,
   or (US mail) as Mike Haertel c/o Free Software Foundation.  */

#ifndef _MP_MALLOC_H
#define _MP_MALLOC_H	1

#ifdef	HAVE_CONFIG_H
#include <config.h>
#endif

#if	defined(_LIBC) || defined(STDC_HEADERS) || defined(USG) || (defined(__STDC__) && __STDC__) 
#include <linux/string.h>
#ifdef __C166__
#define memset xmemset
#define memcpy xmemcpy
#define memmove xmemmove
#pragma warning disable = 118
#endif
#else
#ifndef memset
#define	memset(s, zero, n)	bzero ((s), (n))
#endif
#ifndef memcpy
#define	memcpy(d, s, n)		bcopy ((s), (d), (n))
#endif
#endif

//#if	defined (__GNU_LIBRARY__) || (defined (__STDC__) && __STDC__)
//#include <limits.h>
//#else
#ifndef CHAR_BIT
#define	CHAR_BIT	8
#endif
//#endif

#ifdef	HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef	__cplusplus
extern "C"
{
#endif

#if defined (__cplusplus) || (defined (__STDC__) && __STDC__)
#undef	__MP
#define	__MP(args)	args
#undef	__ptr_t
#define	__ptr_t		void *
#else /* Not C++ or ANSI C.  */
#undef	__MP
#define	__MP(args)	()
#undef	const
#define	const
#undef	__ptr_t
#define	__ptr_t		char *
#endif /* C++ or ANSI C.  */

#if defined (__STDC__) && __STDC__
#include <stddef.h>
#define	__malloc_size_t		size_t
#define	__malloc_ptrdiff_t	ptrdiff_t
#else
#define	__malloc_size_t		unsigned int
#define	__malloc_ptrdiff_t	int
#endif

#ifndef	NULL
#define	NULL	0
#endif

/* Allocate SIZE bytes of memory.  */
extern __ptr_t mp_malloc __MP ((__malloc_size_t __size));

/* Re-allocate the previously allocated block
   in __ptr_t, making the new block SIZE bytes long.  */
extern __ptr_t mp_realloc __MP ((__ptr_t __ptr, __malloc_size_t __size));

/* Allocate NMEMB elements of SIZE bytes each, all initialized to 0.  */
extern __ptr_t mp_calloc __MP ((__malloc_size_t __nmemb, __malloc_size_t __size));

/* Free a block allocated by `mp_malloc', `mp_realloc' or `mp_calloc'.  */
extern void mp_free __MP ((__ptr_t __ptr));

/* Allocate SIZE bytes allocated to ALIGNMENT bytes.  */
extern __ptr_t mp_memalign __MP ((__malloc_size_t __alignment,
			      __malloc_size_t __size));

/* The allocator divides the heap into blocks of fixed size; large
   requests receive one or more whole blocks, and small requests
   receive a fragment of a block.  Fragment sizes are powers of two,
   and all fragments of a block are the same size.  When all the
   fragments in a block have been freed, the block itself is freed.  */
#define INT_BIT		(CHAR_BIT * sizeof(int))
#define BLOCKLOG	(INT_BIT > 16 ? 12 : 9)
#define BLOCKSIZE	(((long)1) << BLOCKLOG)
#define BLOCKIFY(SIZE)	(((SIZE) + BLOCKSIZE - 1) / BLOCKSIZE)

/* Determine the amount of memory spanned by the initial heap table
   (not an absolute limit).  */
#define HEAP		(INT_BIT > 16 ? 4194304 : 65536)

/* Number of contiguous free blocks allowed to build up at the end of
   memory before they will be returned to the system.  */
#define FINAL_FREE_BLOCKS	8

/* Data structure giving per-block information.  */
typedef union
  {
    /* Heap information for a busy block.  */
    struct
      {
	/* Zero for a large (multiblock) object, or positive giving the
	   logarithm to the base two of the fragment size.  */
	int type;
	union
	  {
	    struct
	      {
		__malloc_size_t nfree; /* Free frags in a fragmented block.  */
		__malloc_size_t first; /* First free fragment of the block.  */
	      } frag;
	    /* For a large object, in its first block, this has the number
	       of blocks in the object.  In the other blocks, this has a
	       negative number which says how far back the first block is.  */
	    __malloc_ptrdiff_t size;
	  } info;
      } busy;
    /* Heap information for a free block
       (that may be the first of a free cluster).  */
    struct
      {
	__malloc_size_t size;	/* Size (in blocks) of a free cluster.  */
	__malloc_size_t next;	/* Index of next free cluster.  */
	__malloc_size_t prev;	/* Index of previous free cluster.  */
      } free;
  } malloc_info;

/* Address to block number and vice versa.  */
#define BLOCK(A)	( ((unsigned int)((char *) (A) - _mp_info_ptr->heapbase)) / BLOCKSIZE + 1)
#define ADDRESS(B)	((__ptr_t) (((B) - 1) * BLOCKSIZE + _mp_info_ptr->heapbase))

/* Doubly linked lists of free fragments.  */
struct list
  {
    struct list *next;
    struct list *prev;
  };

/* List of blocks allocated with `memalign' (or `valloc').  */
struct alignlist
  {
    struct alignlist *next;
    __ptr_t aligned;		/* The address that memaligned returned.  */
    __ptr_t exact;		/* The address that malloc returned.  */
  };

/* All global memory pool info in one structure. */
typedef struct
  {
	char				*heapbase;			/* Pointer to first block of the heap.  */
	__malloc_size_t		heapsize;			/* Number of info entries.  */
	malloc_info			*heapinfo;			/* Table indexed by block number giving per-block information.  */
	__malloc_size_t		heapindex;			/* Current search index for the heap table.  */
	__malloc_size_t		heaplimit;			/* Limit of valid info table indices.  */
	struct list			fraghead[BLOCKLOG];	/* Free list headers for each fragment size.  */
	struct alignlist	*aligned_blocks;	/* List of blocks allocated with `memalign' (or `valloc').  */
	__malloc_size_t		chunks_used;		/* Instrumentation.  */
	__malloc_size_t		bytes_used;			/* Instrumentation.  */
	__malloc_size_t		chunks_free;		/* Instrumentation.  */
	__malloc_size_t		bytes_free;			/* Instrumentation.  */
  } mp_info;

extern mp_info *_mp_info_ptr;

/* Set everything up and remember that we have.  */
int mp_initialize __MP ((mp_info *mp_info_ptr, __ptr_t (*func) __MP ((__malloc_ptrdiff_t __size))));

/* Set everything up again.  */
int mp_restart __MP ((mp_info *mp_info_ptr, __ptr_t (*func) __MP ((__malloc_ptrdiff_t __size))));

/* Internal version of `mp_free' used in `mp_morecore' (mp_malloc.c). */
extern void _mp_free_internal __MP ((__ptr_t __ptr));

/* Given an address in the middle of a malloc'd object,
   return the address of the beginning of the object.  */
extern __ptr_t mp_malloc_find_object_address __MP ((__ptr_t __ptr));

/* Underlying allocation function; successive calls should
   return contiguous pieces of memory.  */
extern __ptr_t (*__mp_morecore) __MP ((__malloc_ptrdiff_t __size));

/* Hooks for debugging versions.  */
extern void (*__mp_free_hook) __MP ((__ptr_t __ptr));
extern __ptr_t (*__mp_malloc_hook) __MP ((__malloc_size_t __size));
extern __ptr_t (*__mp_realloc_hook) __MP ((__ptr_t __ptr, __malloc_size_t __size));
extern __ptr_t (*__mp_memalign_hook) __MP ((__malloc_size_t __size,
					__malloc_size_t __alignment));

/* Return values for `mp_mprobe': these are the kinds of inconsistencies that
   `mp_mcheck' enables detection of.  */
enum mcheck_status
  {
    MCHECK_DISABLED = -1,	/* Consistency checking is not turned on.  */
    MCHECK_OK,			/* Block is fine.  */
    MCHECK_FREE,		/* Block freed twice.  */
    MCHECK_HEAD,		/* Memory before the block was clobbered.  */
    MCHECK_TAIL			/* Memory after the block was clobbered.  */
  };

/* Activate a standard collection of debugging hooks.  This must be called
   before `mp_malloc' is ever called.  ABORTFUNC is called with an error code
   (see enum above) when an inconsistency is detected.  If ABORTFUNC is
   null, the standard function prints on stderr and then calls `abort'.  */
extern int mp_mcheck __MP ((void (*__abortfunc) __MP ((enum mcheck_status))));

/* Check for aberrations in a particular malloc'd block.  You must have
   called `mp_mcheck' already.  These are the same checks that `mp_mcheck' does
   when you free or reallocate a block.  */
extern enum mcheck_status mprobe __MP ((__ptr_t __ptr));

/* Activate a standard collection of tracing hooks.  */
extern void mp_mtrace __MP ((void));
extern void mp_muntrace __MP ((void));

/* Statistics available to the user.  */
struct mstats
  {
    __malloc_size_t bytes_total; /* Total size of the heap. */
    __malloc_size_t chunks_used; /* Chunks allocated by the user. */
    __malloc_size_t bytes_used;	/* Byte total of user-allocated chunks. */
    __malloc_size_t chunks_free; /* Chunks in the free list. */
    __malloc_size_t bytes_free;	/* Byte total of chunks in the free list. */
  };

/* Pick up the current statistics. */
extern struct mstats mp_mstats __MP ((void));

#ifdef	__cplusplus
}
#endif

#endif /* malloc.h  */
