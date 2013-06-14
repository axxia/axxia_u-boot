/*
 *  board/lsi/axxia-arm/spl.c
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

#include <common.h>

/*
  ==============================================================================
  ==============================================================================
  Local Stuff
  ==============================================================================
  ==============================================================================
*/

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

/*
  ------------------------------------------------------------------------------
  board_init_f

  This function is declared "void __weak" in arch/arm/lib/spl.c.  It's
  overridden here to handle the SPL boot on Axxia ARM systems.
*/

void
board_init_f(ulong bootflag)
{
	int rc;

	serial_early_init();
	puts("\n"
	     "   ___             _        __  __    ___            __    _______  __ \n"
	     "  / _ |__ ____ __ (_)__ _  / / / /___/ _ )___  ___  / /_  / __/ _ \\/ / \n"
	     " / __ |\\ \\ /\\ \\ // / _ `/ / /_/ /___/ _  / _ \\/ _ \\/ __/ _\\ \\/ ___/ /__\n"
	     "/_/ |_/_\\_\\/_\\_\\/_/\\_,_/  \\____/   /____/\\___/\\___/\\__/ /___/_/  /____/\n");
	printf("\nLSI Version: %s\n", get_lsi_version());
	rc = axxia_initialize();

	if (0 != rc)
		acp_failure(__FILE__, __FUNCTION__, __LINE__);

	printf("Memory initialized\n");
	ssp_init(0, 1);
	rc = ssp_read((void *)0x40000000, 0x100000, 0x200000);
	printf("U-Boot Copied\n");
	reset_cpu_fabric();
	acp_failure(__FILE__, __FUNCTION__, __LINE__);

	return;
}
