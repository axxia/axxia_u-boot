/*
 *
 * Copyright (c) 2012	Christoffer Dall <c.dall@virtualopensystems.com>
 * 					 <cdall@cs.columbia.edu>
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
#include <linux/linkage.h>

ENTRY(smp_kick_secondary)
#if 0
	/* Bring up the second core */
	ldr r0, =(APB2_SER3_BASE + 0x1000)
	mov r1, #0xab
	str r1, [r0]

	ldr r0, =(APB2_SER3_BASE + 0x1010)
	ldr r1, =0x0000
	str r1, [r0]
	dsb
	bx	lr
#else
	ret
#endif
ENDPROC(smp_kick_secondary)
