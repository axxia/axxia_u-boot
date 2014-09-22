/*
 * nvram.c
 *
 * Fake environment for the 3rd stage boot loader in ISS.
 *
 * Copyright (C) 2009 LSI Corporation
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <config.h>

#ifdef ACP_ISS

#include <common.h>

/*
  ----------------------------------------------------------------------
  nvram_read
*/

void *
nvram_read( void * destination, const short source, size_t count )
{
	uchar * out = ( uchar * ) destination;
	uchar * in = ( uchar * ) source;

	while( count -- ) {
		* out ++ = * in ++;
	}

	return destination;
}

/*
  ----------------------------------------------------------------------
  nvram_write
*/

void
nvram_write( short destination, const void * source, size_t count )
{
	uchar * out = ( uchar * ) destination;
	uchar * in = ( uchar * ) source;

	while( count -- ) {
		* out ++ = * in ++;
	}

	return;
}

#endif /* ACP_ISS */
