/*
 * spintable.c
 *
 * Handles all non-zero cores on LSI's Axxia.
 *
 * Copyright (C) 2009...2013 LSI Corporation
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
#include <malloc.h>
#include <libfdt.h>
#include <fdt_support.h>
#include <asm/io.h>
#include <asm/processor.h>

#define ALIGNMENT 32UL

static int core_hold[ACP_NR_CORES] = {1};
static int core_up[ACP_NR_CORES] = {0};

/*
  -------------------------------------------------------------------------------
  acp_spintable_spin

  Executed by all non-zero cores...
*/

void
acp_spintable_spin(void)
{
	unsigned long core;
	acp_spintable_t *spintable;

	__asm__ __volatile__ ("mfspr %0,0x11e" : "=r"(core));
	spintable = (acp_spintable_t *)(0x2000 + (0x40 * core));


	while (1 == core_hold[core])
		;

	core_hold[core] = 1;
	core_up[core] = 1;

	/* Clear all pending interrupts. */
	while (0xff != dcr_read(0xffc000a0)) {
		dcr_write(0, 0xffc000b0);
	}

	/* Wait for the OS... */
	while ((unsigned long long)1 == spintable->entry_address)
		isync();

	/* Fix up CCRn. */
	mtspr(ccr0, spintable->ccr0_value);
	mtspr(ccr1, spintable->ccr1_value);
	mtspr(ccr2, spintable->ccr2_value);
	isync();

	/* Make the jump. */
#if 0
	asm volatile ("mtspr     0x1a,%0\n"
		      "mtspr     0x1b,%1\n"
		      "ori       3,%2,0\n"
		      "rfi" : : 
		      "r"((unsigned long)spintable->entry_address),
		      "r"(0),
		      "r"((unsigned long)spintable->r3_value));
#else
	acp_spintable_jump((unsigned long)spintable->r3_value,
			   (unsigned long)spintable->entry_address);
#endif

	/* Should never get here! */
	acp_failure(__FILE__, __FUNCTION__, __LINE__);

	return;
}

/*
  -------------------------------------------------------------------------------
  acp_spintable_init

  Set up the spin tables.
*/

int
acp_spintable_init(int core, int cold_start)
{
	acp_spintable_t *spintable;
	int retries = 1000;
#if defined(CONFIG_AXXIA_25xx) && defined(RESET_INSTEAD_OF_IPI)
	unsigned long temp;
#endif

	core_up[core] = 0;
	flush_dcache_range(&(core_up[core]),
			   (unsigned long)(&(core_up[core])) + sizeof(int));

	/* Allocate a spin table */
#if 0
	if ((acp_spintable_t *) 0 ==
	    (spintable = malloc(sizeof(acp_spintable_t) + ALIGNMENT))) {
		printf("Error allocating memory for core %d.\n", core);
		return -1;
	}

	spintable = (acp_spintable_t *)
		((((unsigned long) (spintable) +
		   (ALIGNMENT - 1UL)) & ~(ALIGNMENT - 1UL)));
#else
	spintable = (acp_spintable_t *)(0x2000 + (0x40 * core));
#endif
	printf("%s:%d - cold_start=%d spintable=0x%p\n",
	       __FILE__, __LINE__, cold_start, spintable); /* ZZZ */

	/* Initialize the spin table */
	spintable->entry_address = 1;
	spintable->r3_value = core;
	spintable->rsvd1_value = 0;
	spintable->pir_value = core;
	flush_dcache_range(spintable,
			   (unsigned long)spintable + sizeof(acp_spintable_t));
	isync();

	/* Get the core from the 1st stage by sending an IPI. */
	debug("Changing core %d spintable state.\n", core);

	if (0 != cold_start) {
#if defined(CONFIG_AXXIA_25xx) && defined(RESET_INSTEAD_OF_IPI)
		/* Enable L2 1 and Core 1 */
		temp = dcr_read(0xd00);
		temp |= 0xab;
		dcr_write(temp, 0xd00);
		dcr_write(0x0, (DCR_RESET_BASE + 2));
		dcr_write(0x0, (DCR_RESET_BASE + 1));
		temp = dcr_read(0xd00);
		temp &= ~0xab;
		dcr_write(temp, 0xd00);
#else
#if defined(CONFIG_AXXIA_25xx)
		/* Wake up the L2 */
		dcr_write(0x84, 0x300 + (0x100 * core));
		dcr_write(0, 0x304 + (0x100 * core));
#endif
		/* Send an IPI */
		debug("Sending an IPI to core %d.\n", core);
		dcr_write((1 << core), 0xffc00040);
#endif
	} else {
		core_hold[core] = 0;
	}

	isync();

	/* Wait for a response */
	while (0 < retries) {
		--retries;

		if(0 != core_up[core])
			break;

		udelay(100);
	}

	if (0 == retries)
		printf( "Core %d is hung!\n", core );
	else
		debug("Core %d woke up!\n", core);

	return 0;
}

/*
  ------------------------------------------------------------------------------
  ft_board_setup
*/

void
ft_board_setup(void *blob, bd_t *bd)
{
	int i;

	printf("%s:%d - \n", __FILE__, __LINE__); /* ZZZ */

#if 0
	for (i = 1; i < ACP_NR_CORES; ++i) {
		char cpu_string[40];
		int node;
		int rc;
		acp_spintable_t *spintable;
		unsigned long release_address;

		sprintf(cpu_string, "/cpus/cpu@%d", i);
		printf("%s:%d - cpu_string=%s\n",
		       __FILE__, __LINE__, cpu_string); /* ZZZ */
		node = fdt_path_offset(blob, cpu_string);
		printf("%s:%d - i=%d node=%d blob=0x%p\n",
		       __FILE__, __LINE__, i, node, blob); /* ZZZ */

		if (0 > node)
			continue;

		spintable = (acp_spintable_t *)(0x2000 + (0x40 * i));
		release_address = (unsigned long)
			((unsigned long *)&spintable->entry_address);
		printf("%s:%d - spintable=0x%p release_address=0x%p\n",
		       __FILE__, __LINE__, spintable, release_address); /* ZZZ */
		rc = fdt_setprop(blob, node, "cpu-release-addr",
				 &release_address, sizeof(unsigned long));

		if (0 != rc) {
			printf("%s:%d - Error setting property, %d!\n",
			       __FILE__, __LINE__, rc);
			continue;
		}
	}
#endif

	fdt_fixup_ethernet(blob);

	return;
}
