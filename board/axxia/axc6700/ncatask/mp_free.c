/* 
*	MP-Malloc: Malloc for memory pools.
*
*	This library is a work derived from the GNU malloc library.
*	Changes by Dirk Meyer, Chair of Process Control Engineering,
*	RWTH Aachen/Germany (dirk@plt.rwth-aachen.de).
*
*	$Id: mp_free.c,v 1.3 2006/05/23 15:09:04 vj4 Exp $
*/

/* Free a block of memory allocated by `malloc'.
   Copyright 1990, 1991, 1992, 1994 Free Software Foundation, Inc.
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
#pragma warning disable = 46
#endif

/* Debugging hook for free.  */
void (*__mp_free_hook) __MP ((__ptr_t __ptr));

/* Return memory to the heap.
   Like `mp_free' but don't call a __mp_free_hook if there is one.  */
void
_mp_free_internal (__ptr_t ptr)
{
  int type;
  __malloc_size_t block, blocks;
  register __malloc_size_t i;
  struct list *prev, *next;

  block = BLOCK (ptr);

  type = _mp_info_ptr->heapinfo[block].busy.type;
  switch (type)
    {
    case 0:
      /* Get as many statistics as early as we can.  */
      --_mp_info_ptr->chunks_used;
      _mp_info_ptr->bytes_used -= _mp_info_ptr->heapinfo[block].busy.info.size * BLOCKSIZE;
      _mp_info_ptr->bytes_free += _mp_info_ptr->heapinfo[block].busy.info.size * BLOCKSIZE;

      /* Find the free cluster previous to this one in the free list.
	 Start searching at the last block referenced; this may benefit
	 programs with locality of allocation.  */
      i = _mp_info_ptr->heapindex;
      if (i > block)
	while (i > block)
	  i = _mp_info_ptr->heapinfo[i].free.prev;
      else
	{
	  do
	    i = _mp_info_ptr->heapinfo[i].free.next;
	  while (i > 0 && i < block);
	  i = _mp_info_ptr->heapinfo[i].free.prev;
	}

      /* Determine how to link this block into the free list.  */
      if (block == i + _mp_info_ptr->heapinfo[i].free.size)
	{
	  /* Coalesce this block with its predecessor.  */
	  _mp_info_ptr->heapinfo[i].free.size += _mp_info_ptr->heapinfo[block].busy.info.size;
	  block = i;
	}
      else
	{
	  /* Really link this block back into the free list.  */
	  _mp_info_ptr->heapinfo[block].free.size = _mp_info_ptr->heapinfo[block].busy.info.size;
	  _mp_info_ptr->heapinfo[block].free.next = _mp_info_ptr->heapinfo[i].free.next;
	  _mp_info_ptr->heapinfo[block].free.prev = i;
	  _mp_info_ptr->heapinfo[i].free.next = block;
	  _mp_info_ptr->heapinfo[_mp_info_ptr->heapinfo[block].free.next].free.prev = block;
	  ++_mp_info_ptr->chunks_free;
	}

      /* Now that the block is linked in, see if we can coalesce it
	 with its successor (by deleting its successor from the list
	 and adding in its size).  */
      if (block + _mp_info_ptr->heapinfo[block].free.size == _mp_info_ptr->heapinfo[block].free.next)
	{
	  _mp_info_ptr->heapinfo[block].free.size
	    += _mp_info_ptr->heapinfo[_mp_info_ptr->heapinfo[block].free.next].free.size;
	  _mp_info_ptr->heapinfo[block].free.next
	    = _mp_info_ptr->heapinfo[_mp_info_ptr->heapinfo[block].free.next].free.next;
	  _mp_info_ptr->heapinfo[_mp_info_ptr->heapinfo[block].free.next].free.prev = block;
	  --_mp_info_ptr->chunks_free;
	}

      /* Now see if we can return stuff to the system.  */
      blocks = _mp_info_ptr->heapinfo[block].free.size;
      if (blocks >= FINAL_FREE_BLOCKS && block + blocks == _mp_info_ptr->heaplimit
	  && (*__mp_morecore) (0) == ADDRESS (block + blocks))
	{
	  register __malloc_size_t bytes = blocks * BLOCKSIZE;
	  _mp_info_ptr->heaplimit -= blocks;
	  (*__mp_morecore) (-bytes);
	  _mp_info_ptr->heapinfo[_mp_info_ptr->heapinfo[block].free.prev].free.next
	    = _mp_info_ptr->heapinfo[block].free.next;
	  _mp_info_ptr->heapinfo[_mp_info_ptr->heapinfo[block].free.next].free.prev
	    = _mp_info_ptr->heapinfo[block].free.prev;
	  block = _mp_info_ptr->heapinfo[block].free.prev;
	  --_mp_info_ptr->chunks_free;
	  _mp_info_ptr->bytes_free -= bytes;
	}

      /* Set the next search to begin at this block.  */
      _mp_info_ptr->heapindex = block;
      break;

    default:
      /* Do some of the statistics.  */
      --_mp_info_ptr->chunks_used;
      _mp_info_ptr->bytes_used -= 1 << type;
      ++_mp_info_ptr->chunks_free;
      _mp_info_ptr->bytes_free += 1 << type;

      /* Get the address of the first free fragment in this block.  */
      prev = (struct list *) ((char *) ADDRESS (block) +
			   (_mp_info_ptr->heapinfo[block].busy.info.frag.first << type));

      if (_mp_info_ptr->heapinfo[block].busy.info.frag.nfree == (unsigned)(BLOCKSIZE >> type) - 1)
	{
	  /* If all fragments of this block are free, remove them
	     from the fragment list and free the whole block.  */
	  next = prev;
	  for (i = 1; i < (__malloc_size_t) (BLOCKSIZE >> type); ++i)
	    next = next->next;
	  prev->prev->next = next;
	  if (next != NULL)
	    next->prev = prev->prev;
	  _mp_info_ptr->heapinfo[block].busy.type = 0;
	  _mp_info_ptr->heapinfo[block].busy.info.size = 1;

	  /* Keep the statistics accurate.  */
	  ++_mp_info_ptr->chunks_used;
	  _mp_info_ptr->bytes_used += BLOCKSIZE;
	  _mp_info_ptr->chunks_free -= BLOCKSIZE >> type;
	  _mp_info_ptr->bytes_free -= BLOCKSIZE;

	  mp_free (ADDRESS (block));
	}
      else if (_mp_info_ptr->heapinfo[block].busy.info.frag.nfree != 0)
	{
	  /* If some fragments of this block are free, link this
	     fragment into the fragment list after the first free
	     fragment of this block. */
	  next = (struct list *) ptr;
	  next->next = prev->next;
	  next->prev = prev;
	  prev->next = next;
	  if (next->next != NULL)
	    next->next->prev = next;
	  ++_mp_info_ptr->heapinfo[block].busy.info.frag.nfree;
	}
      else
	{
	  /* No fragments of this block are free, so link this
	     fragment into the fragment list and announce that
	     it is the first free fragment of this block. */
	  prev = (struct list *) ptr;
	  _mp_info_ptr->heapinfo[block].busy.info.frag.nfree = 1;
	  _mp_info_ptr->heapinfo[block].busy.info.frag.first = (unsigned long int)
	    ((unsigned long int) ((char *) ptr - (char *) NULL)
	     % BLOCKSIZE >> type);
	  prev->next = _mp_info_ptr->fraghead[type].next;
	  prev->prev = &_mp_info_ptr->fraghead[type];
	  prev->prev->next = prev;
	  if (prev->next != NULL)
	    prev->next->prev = prev;
	}
      break;
    }
}

/* Return memory to the heap.  */
void
mp_free (__ptr_t ptr)
{
  register struct alignlist *l;

  if (ptr == NULL)
    return;

  for (l = _mp_info_ptr->aligned_blocks; l != NULL; l = l->next)
    if (l->aligned == ptr)
      {
	l->aligned = NULL;	/* Mark the slot in the list as free.  */
	ptr = l->exact;
	break;
      }

  if (__mp_free_hook != NULL)
    (*__mp_free_hook) (ptr);
  else
    _mp_free_internal (ptr);
}
