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
#include <asm/ppc47x.h>

#define WA_BZ42743		/* ACP2500 system reset issue */

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

#if defined(CONFIG_ACP3) && defined(ACP_25xx) && defined(WA_BZ42743)
	value = dcr_read(0xd00);
	value |= 0xab;
	dcr_write(value, 0xd00);
#endif

#ifdef CONFIG_ACP2
	mtspr(dbcr0, 0x30000000);
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
#if defined(ACP_25xx) && defined(WA_BZ42743)
			dcr_write(2, DCR_RESET_BASE);
#else
			mtspr(dbcr0, 0x20000000);
#endif
		}
	}

	/* Default is a System Reset. */
	printf("System Reset\n");
#if defined(ACP_25xx) && defined(WA_BZ42743)
	dcr_write(1, DCR_RESET_BASE);
#else
	mtspr(dbcr0, 0x30000000);
#endif
#endif

	return;
}
