/*
 *  board/lsi/axxia-arm/outer_cache.S
 *
 *  Copyright (C) 2013 LSI (john.jacques@lsi.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <config.h>
#include <linux/linkage.h>

/*
  ------------------------------------------------------------------------------
  set_outer_cache_state

  Set the mode in (0x10000 * offset) + 0x10, bits 1:0.  Verify that it
  got set by reading (0x10000 * offset) + 0x18), bits 3:2.

  The modes are as follows.

  0b00 - OFF
  0b01 - SFONLY
  0b10 - HALF
  0b11 - FULL
*/

set_outer_cache_state:
#ifndef CONFIG_AXXIA_SIM
	/* Write the state. */
	ldr	r3, =(DICKENS + 0x200000)
	ldr	r2, =(DICKENS + 0x270000)
1:	str	r0, [r3, #0x10]
	add	r3, r3, #0x10000
	cmp	r3, r2
	ble	1b
	/* Verify the state. */
	ldr	r3, =(DICKENS + 0x200000)
	ldr	r2, =(DICKENS + 0x270000)
	mov	r0, r0, lsl #2
1:	ldr	r1, [r3, #0x18]
	cmp	r1, r0
	bne	1b
	add	r3, r3, #0x10000
	cmp	r3, r2
	ble	1b
#endif
	mov	r0, #0
	mov	pc, lr

/*
  ==============================================================================
  ==============================================================================
  Outer Cache Functions
  ==============================================================================
  ==============================================================================
*/

/*
  ------------------------------------------------------------------------------
  v7_outer_cache_enable
*/

ENTRY(v7_outer_cache_enable)
	bx	lr
ENDPROC(v7_outer_cache_enable)


/*
  ------------------------------------------------------------------------------
  v7_outer_cache_disable
*/

ENTRY(v7_outer_cache_disable)
	bx	lr
ENDPROC(v7_outer_cache_disable)

/*
  ------------------------------------------------------------------------------
  v7_outer_cache_flush_all
*/

ENTRY(v7_outer_cache_flush_all)
	mov	r12, lr
	mov	r0, #0
	bl	set_outer_cache_state
#ifndef LEAVE_L3_OFF
	mov	r0, #3
	bl	set_outer_cache_state
#endif
	mov	lr, r12
	bx	lr
ENDPROC(v7_outer_cache_flush_all)

/*
  ------------------------------------------------------------------------------
  v7_outer_cache_inval_all
*/

ENTRY(v7_outer_cache_inval_all)
	bx	lr
ENDPROC(v7_outer_cache_inval_all)

/*
  ------------------------------------------------------------------------------
  v7_outer_cache_flush_range
*/

ENTRY(v7_outer_cache_flush_range)
	bx	lr
ENDPROC(v7_outer_cache_flush_range)

/*
  ------------------------------------------------------------------------------
  v7_outer_cache_inval_range
*/

ENTRY(v7_outer_cache_inval_range)
	bx	lr
ENDPROC(v7_outer_cache_inval_range)

