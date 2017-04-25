/* 
*	MP-Malloc: Malloc for memory pools.
*
*	This library is a work derived from the GNU malloc library.
*	Changes by Dirk Meyer, Chair of Process Control Engineering,
*	RWTH Aachen/Germany (dirk@plt.rwth-aachen.de).
*
*	$Id: mp_malloc.c,v 1.4 2008/01/31 17:54:12 mb Exp $
*/

/* Memory allocator `malloc'.
   Copyright 1990, 1991, 1992, 1993, 1994, 1995 Free Software Foundation, Inc.
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

#include "uboot/mp_malloc.h"

#ifdef __C166__
#pragma warning disable = 115
#endif

/* All global memory pool info in one structure. */
mp_info *_mp_info_ptr;

/* How to really get more memory.  */
__ptr_t (*__mp_morecore) __MP ((ptrdiff_t __size)) = NULL;

/* Debugging hook for `mp_malloc'.  */
__ptr_t (*__mp_malloc_hook) __MP ((__malloc_size_t __size)) = NULL;

/* Aligned allocation.  */
static __ptr_t align __MP ((__malloc_size_t));
static __ptr_t
align(__malloc_size_t size)
{
  __ptr_t result;
  unsigned long int adj;

  result = (*__mp_morecore) (size);
  adj = (unsigned long int) ((unsigned long int) ((char *) result -
						  (char *) NULL)) % BLOCKSIZE;
  if (adj != 0)
    {
      adj = BLOCKSIZE - adj;
      (void) (*__mp_morecore) (adj);
      result = (char *) result + adj;
    }

  return result;
}

/* Get neatly aligned memory, initializing or
   growing the heap info table as necessary. */
static __ptr_t morecore __MP ((__malloc_size_t));
static __ptr_t
morecore (__malloc_size_t size)
{
  __ptr_t result;
  malloc_info *newinfo, *oldinfo;
  __malloc_size_t newsize;

  result = align (size);
  if (result == NULL)
    return NULL;

  /* Check if we need to grow the info table.  */
  if ((__malloc_size_t) BLOCK ((char *) result + size) > _mp_info_ptr->heapsize)
    {
      newsize = _mp_info_ptr->heapsize;
      while ((__malloc_size_t) BLOCK ((char *) result + size) > newsize)
	newsize *= 2;
      newinfo = (malloc_info *) align (newsize * sizeof (malloc_info));
      if (newinfo == NULL)
	{
	  (*__mp_morecore) (-size);
	  return NULL;
	}
      memcpy (newinfo, _mp_info_ptr->heapinfo, _mp_info_ptr->heapsize * sizeof (malloc_info));
      memset (&newinfo[_mp_info_ptr->heapsize], 0,
	      (newsize - _mp_info_ptr->heapsize) * sizeof (malloc_info));
      oldinfo = _mp_info_ptr->heapinfo;
      newinfo[BLOCK (oldinfo)].busy.type = 0;
      newinfo[BLOCK (oldinfo)].busy.info.size
	= BLOCKIFY (_mp_info_ptr->heapsize * sizeof (malloc_info));
      _mp_info_ptr->heapinfo = newinfo;
      /* Account for the _mp_info_ptr->heapinfo block itself in the statistics.  */
      _mp_info_ptr->bytes_used += newsize * sizeof (malloc_info);
      ++_mp_info_ptr->chunks_used;
      _mp_free_internal (oldinfo);
      _mp_info_ptr->heapsize = newsize;
    }

  _mp_info_ptr->heaplimit = BLOCK ((char *) result + size);
  return result;
}

/* Set everything up and remember that we have.  */
int mp_initialize __MP ((mp_info *mp_info_ptr, __ptr_t (*func) __MP ((__malloc_ptrdiff_t __size))));
int
mp_initialize (mp_info	*mp_info_ptr,
	       __ptr_t (*func) __MP ((__malloc_ptrdiff_t __size)))
{
  __malloc_size_t i;

  if (!mp_info_ptr || !func)
	return 0;

  _mp_info_ptr = mp_info_ptr;
  __mp_morecore = func;

  _mp_info_ptr->heapsize = HEAP / BLOCKSIZE;
  _mp_info_ptr->heapinfo = (malloc_info *) align (_mp_info_ptr->heapsize * sizeof (malloc_info));
  if (_mp_info_ptr->heapinfo == NULL)
    return 0;
  memset (_mp_info_ptr->heapinfo, 0, _mp_info_ptr->heapsize * sizeof (malloc_info));
  _mp_info_ptr->heapinfo[0].free.size = 0;
  _mp_info_ptr->heapinfo[0].free.next = _mp_info_ptr->heapinfo[0].free.prev = 0;
  _mp_info_ptr->heapindex = 0;
  _mp_info_ptr->heapbase = (char *) _mp_info_ptr->heapinfo;
  _mp_info_ptr->heaplimit = 0;
  for (i=0; i<BLOCKLOG; i++)
	{
	  _mp_info_ptr->fraghead[i].next = 0;
	  _mp_info_ptr->fraghead[i].prev = 0;
	}
  _mp_info_ptr->aligned_blocks = 0;

  /* Account for the heapinfo block itself in the statistics.  */
  _mp_info_ptr->bytes_used = _mp_info_ptr->heapsize * sizeof (malloc_info);
  _mp_info_ptr->chunks_used = 1;
  _mp_info_ptr->bytes_free = 0;
  _mp_info_ptr->chunks_free = 0;

  return 1;
}

/* Set everything up again.  */
int mp_restart __MP ((mp_info *mp_info_ptr, __ptr_t (*func) __MP ((__malloc_ptrdiff_t __size))));
int
mp_restart (mp_info	*mp_info_ptr,
	    __ptr_t (*func) __MP ((__malloc_ptrdiff_t __size)))
{
  if (!mp_info_ptr || !func)
	return 0;

  _mp_info_ptr = mp_info_ptr;
  __mp_morecore = func;

  return 1;
}

/* Allocate memory from the heap.  */
__ptr_t
mp_malloc (__malloc_size_t size)
{
  __ptr_t result;
  __malloc_size_t block, blocks, lastblocks, start;
  register __malloc_size_t i;
  struct list *next;

  /* ANSI C allows `malloc (0)' to either return NULL, or to return a
     valid address you can realloc and free (though not dereference).

     It turns out that some extant code (sunrpc, at least Ultrix's version)
     expects `malloc (0)' to return non-NULL and breaks otherwise.
     Be compatible.  */

#if	0
  if (size == 0)
    return NULL;
#endif

  if (__mp_malloc_hook != NULL)
    return (*__mp_malloc_hook) (size);

  if (size < sizeof (struct list))
    size = sizeof (struct list);

#ifdef SUNOS_LOCALTIME_BUG
  if (size < 16)
    size = 16;
#endif

  /* Determine the allocation policy based on the request size.  */
  if (size <= BLOCKSIZE / 2)
    {
      /* Small allocation to receive a fragment of a block.
	 Determine the logarithm to base two of the fragment size. */
      register __malloc_size_t _log = 1;
      --size;
      while ((size /= 2) != 0)
	++_log;

      /* Look in the fragment lists for a
	 free fragment of the desired size. */
      next = _mp_info_ptr->fraghead[_log].next;
      if (next != NULL)
	{
	  /* There are free fragments of this size.
	     Pop a fragment out of the fragment list and return it.
	     Update the block's nfree and first counters. */
	  result = (__ptr_t) next;
	  next->prev->next = next->next;
	  if (next->next != NULL)
	    next->next->prev = next->prev;
	  block = BLOCK (result);
	  if (--_mp_info_ptr->heapinfo[block].busy.info.frag.nfree != 0)
	    _mp_info_ptr->heapinfo[block].busy.info.frag.first = (unsigned long int)
	      ((unsigned long int) ((char *) next->next - (char *) NULL)
	       % BLOCKSIZE) >> _log;

	  /* Update the statistics.  */
	  ++_mp_info_ptr->chunks_used;
	  _mp_info_ptr->bytes_used += 1 << _log;
	  --_mp_info_ptr->chunks_free;
	  _mp_info_ptr->bytes_free -= 1 << _log;
	}
      else
	{
	  /* No free fragments of the desired size, so get a new block
	     and break it into fragments, returning the first.  */
	  result = mp_malloc (BLOCKSIZE);
	  if (result == NULL)
	    return NULL;

	  /* Link all fragments but the first into the free list.  */
	  for (i = 1; i < (__malloc_size_t) (BLOCKSIZE >> _log); ++i)
	    {
	      next = (struct list *) ((char *) result + (i << _log));
	      next->next = _mp_info_ptr->fraghead[_log].next;
	      next->prev = &_mp_info_ptr->fraghead[_log];
	      next->prev->next = next;
	      if (next->next != NULL)
		next->next->prev = next;
	    }

	  /* Initialize the nfree and first counters for this block.  */
	  block = BLOCK (result);
	  _mp_info_ptr->heapinfo[block].busy.type = _log;
	  _mp_info_ptr->heapinfo[block].busy.info.frag.nfree = i - 1;
	  _mp_info_ptr->heapinfo[block].busy.info.frag.first = i - 1;

	  _mp_info_ptr->chunks_free += (BLOCKSIZE >> _log) - 1;
	  _mp_info_ptr->bytes_free += BLOCKSIZE - (1 << _log);
	  _mp_info_ptr->bytes_used -= BLOCKSIZE - (1 << _log);
	}
    }
  else
    {
      /* Large allocation to receive one or more blocks.
	 Search the free list in a circle starting at the last place visited.
	 If we loop completely around without finding a large enough
	 space we will have to get more memory from the system.  */
      blocks = BLOCKIFY (size);
      start = block = _mp_info_ptr->heapindex;
      while (_mp_info_ptr->heapinfo[block].free.size < blocks)
	{
	  block = _mp_info_ptr->heapinfo[block].free.next;
	  if (block == start)
	    {
	      /* Need to get more from the system.  Check to see if
		 the new core will be contiguous with the final free
		 block; if so we don't need to get as much.  */
	      block = _mp_info_ptr->heapinfo[0].free.prev;
	      lastblocks = _mp_info_ptr->heapinfo[block].free.size;
	      if (_mp_info_ptr->heaplimit != 0 && block + lastblocks == _mp_info_ptr->heaplimit &&
		  (*__mp_morecore) (0) == ADDRESS (block + lastblocks) &&
		  (morecore ((blocks - lastblocks) * BLOCKSIZE)) != NULL)
		{
 		  /* Which block we are extending (the `final free
 		     block' referred to above) might have changed, if
 		     it got combined with a freed info table.  */
 		  block = _mp_info_ptr->heapinfo[0].free.prev;
  		  _mp_info_ptr->heapinfo[block].free.size += (blocks - lastblocks);
		  _mp_info_ptr->bytes_free += (blocks - lastblocks) * BLOCKSIZE;
		  continue;
		}
	      result = morecore (blocks * BLOCKSIZE);
	      if (result == NULL)
		return NULL;
	      block = BLOCK (result);
	      _mp_info_ptr->heapinfo[block].busy.type = 0;
	      _mp_info_ptr->heapinfo[block].busy.info.size = blocks;
	      ++_mp_info_ptr->chunks_used;
	      _mp_info_ptr->bytes_used += blocks * BLOCKSIZE;
	      return result;
	    }
	}

      /* At this point we have found a suitable free list entry.
	 Figure out how to remove what we need from the list. */
      result = ADDRESS (block);
      if (_mp_info_ptr->heapinfo[block].free.size > blocks)
	{
	  /* The block we found has a bit left over,
	     so relink the tail end back into the free list. */
	  _mp_info_ptr->heapinfo[block + blocks].free.size
	    = _mp_info_ptr->heapinfo[block].free.size - blocks;
	  _mp_info_ptr->heapinfo[block + blocks].free.next
	    = _mp_info_ptr->heapinfo[block].free.next;
	  _mp_info_ptr->heapinfo[block + blocks].free.prev
	    = _mp_info_ptr->heapinfo[block].free.prev;
	  _mp_info_ptr->heapinfo[_mp_info_ptr->heapinfo[block].free.prev].free.next
	    = _mp_info_ptr->heapinfo[_mp_info_ptr->heapinfo[block].free.next].free.prev
	    = _mp_info_ptr->heapindex = block + blocks;
	}
      else
	{
	  /* The block exactly matches our requirements,
	     so just remove it from the list. */
	  _mp_info_ptr->heapinfo[_mp_info_ptr->heapinfo[block].free.next].free.prev
	    = _mp_info_ptr->heapinfo[block].free.prev;
	  _mp_info_ptr->heapinfo[_mp_info_ptr->heapinfo[block].free.prev].free.next
	    = _mp_info_ptr->heapindex = _mp_info_ptr->heapinfo[block].free.next;
	  --_mp_info_ptr->chunks_free;
	}

      _mp_info_ptr->heapinfo[block].busy.type = 0;
      _mp_info_ptr->heapinfo[block].busy.info.size = blocks;
      ++_mp_info_ptr->chunks_used;
      _mp_info_ptr->bytes_used += blocks * BLOCKSIZE;
      _mp_info_ptr->bytes_free -= blocks * BLOCKSIZE;

      /* Mark all the blocks of the object just allocated except for the
	 first with a negative number so you can find the first block by
	 adding that adjustment.  */
      while (--blocks > 0)
	_mp_info_ptr->heapinfo[block + blocks].busy.info.size = -blocks;
    }

  return result;
}
