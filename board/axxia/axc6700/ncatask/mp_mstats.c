/* 
*	MP-Malloc: Malloc for memory pools.
*
*	This library is a work derived from the GNU malloc library.
*	Changes by Dirk Meyer, Chair of Process Control Engineering,
*	RWTH Aachen/Germany (dirk@plt.rwth-aachen.de).
*
*	$Id: mp_mstats.c,v 1.2 2006/02/21 16:40:45 mb Exp $
*/

/* Access the statistics maintained by `malloc'.
   Copyright 1990, 1991, 1992 Free Software Foundation, Inc.
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

struct mstats
mp_mstats (void)
{
  struct mstats result;

  result.bytes_total = (char *) (*__mp_morecore) (0) - _mp_info_ptr->heapbase;
  result.chunks_used = _mp_info_ptr->chunks_used;
  result.bytes_used = _mp_info_ptr->bytes_used;
  result.chunks_free = _mp_info_ptr->chunks_free;
  result.bytes_free = _mp_info_ptr->bytes_free;
  return result;
}
