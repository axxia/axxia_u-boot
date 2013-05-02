/*
 *  board/lsi/axxia-arm/axxia.c
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

/*
  ==============================================================================
  ==============================================================================
  Local Stuff
  ==============================================================================
  ==============================================================================
*/

static int test_value;

/*
  ==============================================================================
  ==============================================================================
  Global Stuff
  ==============================================================================
  ==============================================================================
*/

/*
  ------------------------------------------------------------------------------
  reset_cpu_fabric

  This sequence switches the memory map from reset to mission, and
  resets some hardware elements, including the core.  After the 'wfi'
  instruction, execution will start at offset 0 in system memory.

  Does not return!
*/

#ifdef CONFIG_SPL_BUILD

void
reset_cpu_fabric(void)
{
	unsigned long value;

	/*
	  Don't use readl()/writel(), as those contain barriers.  The
	  barriers below are part of the sequence.
	*/

	/* syscontrol access key */
	*((unsigned long *)(SYSCON + 0x1000)) = 0xab;

	/* set the resetFab bit in reset_ctl */
	value = *((unsigned long *)(SYSCON + 0x1008));
	value |= 4;
	*((unsigned long *)(SYSCON + 0x1008)) = value;

	/* dsb */
	asm volatile ("mcr p15,0,%0,c7,c10,4" : : "r" (0));

	/* read back reset_ctl */
	value = *((unsigned long *)(SYSCON + 0x1008));

	/* dsb */
	asm volatile ("mcr p15,0,%0,c7,c10,4" : : "r" (0));

	/* isb */
	asm volatile ("mcr p15,0,%0,c7,c5,4" : : "r" (0));

	/* wfi */
	asm volatile ("wfi");

	/* isb */
	asm volatile ("mcr p15,0,%0,c7,c5,4" : : "r" (0));

	return;
}

#endif	/* CONFIG_SPL_BUILD */

/*
  ------------------------------------------------------------------------------
  board_early_init_f

  Called quite early as part of the init sequence.
*/

int
board_early_init_f(void)
{
#ifdef CONFIG_SPL_BUILD
	/*
	  Initialize System Memory.
	*/

	asm volatile ("1: b 1b");

	reset_cpu_fabric();
#endif	/* CONFIG_SPL_BUILD */

	return 0;
}
