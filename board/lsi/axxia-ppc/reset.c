/*
 *  Copyright (C) 2010 LSI Corporation
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
#include <asm/processor.h>
#include <ppc47x.h>

#if defined(CONFIG_ACP3) && (defined(ACP_25xx) || defined(AXM_35xx))
#define WA_BZ42743
#endif

#if defined(AXM_35xx)
#define WA_BZ49339
#endif

/*
  ------------------------------------------------------------------------------
  acp_reset
*/

void
acp_reset(int argc, char *argv[])
{
#ifdef CONFIG_ACP3
	unsigned long value;
#endif

#if defined(WA_BZ49339)
	unsigned long mcgc;
#endif

#if defined(WA_BZ42743)
#if defined(ACP_25xx)
	value = dcr_read(0xd00);
	value |= 0xab;
	dcr_write(value, 0xd00);
#else
	value = dcr_read(0xd0a);
	value |= 0xab;
	dcr_write(value, 0xd0a);
#endif
#endif

#if defined(WA_BZ49339)
	if ((2 > argc) ||	/* No type specified => system */
	    (2 == argc &&
	     (0 == strncmp("chip", argv[1], strlen("chip")) ||
	      0 == strncmp("system", argv[1], strlen("system"))))) {
		/*
		  Before a chip or system reset on 3500, switch the
		  PPCs to the reference clock.  No errata number is
		  available yet, but here is the description from
		  BZ49339.

		  The reset_system issue is caused since the 6
		  counters are **NOT** reset by reset_system, but the
		  PLL and clock switch that controls the counters
		  **IS**.  Workaround for this: switch clk_ppc to
		  clk_ref before a reset_system or reset_chip. This
		  logically should work, BUT no STA work has been done
		  to validate this. Empirically, this seems to work.
		*/
		printf("Switching PPCs to the reference clock.\n");
		mcgc = dcr_read(0xd0a);
		mcgc |= 0xab;
		dcr_write(mcgc, 0xd0a);
		mcgc = dcr_read(0xd00);
		mcgc &= ~0xc0000000;
		dcr_write(mcgc, 0xd00);
	}
#endif

#ifdef CONFIG_ACP2
#if defined(WA_BZ42743)
	dcr_write(1, DCR_RESET_BASE);
#else
	mtspr(dbcr0, 0x30000000);
#endif
#else
	value = dcr_read(DCR_RESET_BASE + 1);
	dcr_write(value, (DCR_RESET_BASE + 1));

	if (2 == argc) {
		if (0 == strncmp("core", argv[1], strlen("core")) ||
		    0 == strncmp("warm", argv[1], strlen("warm"))) {
			/*
			  Core/L2 Reset -- Warm Restart.
			*/
			printf("Core/Warm Reset\n");

			/*
			  Update the TLB entry for system memory
			  (change WIMG to 0101).
			*/
			__asm__ __volatile__ ( ".long 0x7c00078c\n"            \
					       ".long 0x7c00038c\n"            \
					       ".long 0x7c0004ac\n"            \
					       "tlbwe %1,%0,0\n"               \
					       "tlbwe %2,%0,1\n"               \
					       "tlbwe %3,%0,2\n"               \
					       "isync\n" : :
					       "r" (0x80000000),
					       "r" (0x000009f0),
					       "r" (0x00000000),
					       "r" (0x00030507));

			/* Release the system lock. */
			acp_unlock_stage3();

			/* Do the reset. */
			mtspr(dbcr0, 0x10000000);
		} else if (0 == strncmp("chip", argv[1], strlen("chip"))) {
			/*
			  Chip Reset -- ?
			*/
			printf("Chip Reset\n");
#if defined(WA_BZ42743)
			dcr_write(2, DCR_RESET_BASE);
#else
			mtspr(dbcr0, 0x20000000);
#endif
		}
	}

	/* Default is a System Reset. */
	printf("System Reset\n");
#if defined(WA_BZ42743)
	dcr_write(1, DCR_RESET_BASE);
#else
	mtspr(dbcr0, 0x30000000);
#endif
#endif

	return;
}
