/*
 *  Copyright (C) 2009 LSI Corporation
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

#include <common.h>
#include <asm/io.h>

/*
  ======================================================================
  ======================================================================
  Public Interface
  ======================================================================
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  dcr_read
*/

unsigned long
dcr_read( unsigned long offset )
{
	unsigned long value;

#if 0
	__asm__ __volatile__
		(
			"mfdcrx %0,%1"
			: "=r" ( value )
			: "r" ( offset )
		);
#else
	/*
	  Don't use mfdcrx directly, it won't be understood by older binutils.
	*/

	__asm__ __volatile__
		(
			".long 0x7c000206 | (%0 << 21) | (%1 << 16)"
			: "=r" ( value )
			: "r" ( offset )
		);
#endif

	return value;
}

/*
  ----------------------------------------------------------------------
  dcr_write
*/

void
dcr_write( unsigned long value, unsigned long offset )
{
#if 0
	__asm__ __volatile__
		(
			"mtdcrx %0,%1"
			:
			: "r" ( offset ), "r" ( value )
		);
#else
	/*
	  Don't use mtdcrx directly, it won't be understood by older binutils.
	*/

	__asm__ __volatile__
		(
			".long 0x7c000306 | (%0 << 21) | (%1 << 16)"
			:
			: "r" ( value ), "r" ( offset )
		);
#endif

	return;
}
