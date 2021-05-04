/*
 * oem.c
 *
 * OEM calls into the secure monitor.
 *
 * Copyright (C) 2021 Intel
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
#include <common.h>
#include <asm/io.h>

/*
  ------------------------------------------------------------------------------
  axxia_ccn_get
*/

int
axxia_ccn_get(unsigned long offset, unsigned long *value)
{
	unsigned long rc;
	unsigned long result;

	asm volatile("mov x0, %2\n"
		     "mov x1, %3\n"
		     "mov x2, #0\n"
		     "mov x3, #0\n"
		     "smc #0\n"
		     "mov %0, x0\n"
		     "mov %1, x1\n"
		     : "=r" (rc), "=r" (result)
		     : "r" (0xc3000006), "r" (offset)
		     : "x0", "x1", "x2", "x3"
		);

	if (rc)
		return -1;

	*value = result;

	return 0;
}

/*
  ------------------------------------------------------------------------------
  axxia_ccn_set
*/

int
axxia_ccn_set(unsigned long offset, unsigned long value)
{
	unsigned long rc;

	asm volatile("mov x0, %1\n"
		     "mov x1, %2\n"
		     "mov x2, %3\n"
		     "mov x3, #0\n"
		     "smc #0\n"
		     "mov %0, x0\n"
		     : "=r" (rc)
		     : "r" (0xc3000007), "r" (offset), "r" (value)
		     : "x0", "x1", "x2", "x3"
		);

	if (rc)
		return -1;

	return 0;
}
