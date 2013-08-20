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
#include <common.h>
#include <twl6035.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/mmc_host_def.h>

#include "mux_data.h"

DECLARE_GLOBAL_DATA_PTR;

const struct omap_sysinfo sysinfo = {
	"Board: OMAP5430 EVM\n"
};

/*
  ==============================================================================
  ==============================================================================
  Private
  ==============================================================================
  ==============================================================================
*/

/*
  ------------------------------------------------------------------------------
  set_coherency
*/

static int
set_coherency(unsigned long sdcr_ddcr_value)
{
	unsigned long sdcr_offsets[] = {
		0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27
	};
	int i;
	int retries;

	printf("SDCR/DDCR: 0x%lx\n", sdcr_ddcr_value);

	for (i = 0; i < (sizeof(sdcr_offsets) / sizeof(unsigned long)); ++i) {
		int offset;

		offset = DICKENS | (sdcr_offsets[i] << 16);
		writel(sdcr_ddcr_value, (offset + 0x210));
		retries = 1000;

		do {
			--retries;
		} while (0 < retries &&
			 sdcr_ddcr_value != readl(offset + 0x200));

		if (0 == retries)
			return -1;
	}

	/* Update DVM */
	writel(sdcr_ddcr_value, (DICKENS + 0x210));
	retries = 1000;

	do {
		--retries;
	} while (0 < retries && sdcr_ddcr_value != readl(DICKENS + 0x200));

	if (0 == retries)
		return -1;

	return 0;
}

/*
  -------------------------------------------------------------------------------
  set_clusters
*/

static int
set_clusters(void)
{
	char *clusters_env;
	unsigned long clusters;
	unsigned long sdcr_ddcr = DEFAULT_SDCR_VALUE;

	if (NULL == (clusters_env = getenv("clusters")))
		clusters = 0xf;
	else
		clusters = simple_strtoul(clusters_env, NULL, 0);

	if (0 == (clusters & 1)) {
		printf("Cluster 0 MUST be enabled, enabling.\n");
		clusters |= 1;
	}

	puts("Setting up Coherencly for Clusters: 0");

	if (0 != (clusters & 0x2))
		puts(",1");

	if (0 != (clusters & 0x4))
		puts(",2");

	if (0 != (clusters & 0x8))
		puts(",3");

	puts("\n");

	/*
	  How many clusters should be up?
	*/

	if (0 != set_coherency(sdcr_ddcr))
		return -1;

	return 0;
}

/*
  ==============================================================================
  ==============================================================================
  Public
  ==============================================================================
  ==============================================================================
*/

/*
  -------------------------------------------------------------------------------
  flush_l3
*/

void flush_l3(void)
{
	unsigned long hnf_offsets[] = {
		0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27
	};
	int i;
        unsigned long status, id;
	int retries;

	puts("Flushing L3 Cache\n");
	
	for (i = 0; i < (sizeof(hnf_offsets) / sizeof(unsigned long)); ++i) {
		/* set state NOL3 */
		writel(0x0, DICKENS + (0x10000 * hnf_offsets[i]) + 0x10);
	}

	for (i = 0; i < (sizeof(hnf_offsets) / sizeof(unsigned long)); ++i) {
		retries = 10000;

		do {
			status = readl(DICKENS +
				       (0x10000 * hnf_offsets[i]) + 0x18);
			udelay(10);
		} while ((0 < --retries) && (0x0 != (status & 0xf)));

		if (0 == retries)
			acp_failure(__FILE__, __FUNCTION__, __LINE__);
	}

	/* */

	for (i = 0; i < (sizeof(hnf_offsets) / sizeof(unsigned long)); ++i) {
		/* set state NOL3 */
		writel(0x3, DICKENS + (0x10000 * hnf_offsets[i]) + 0x10);
	}

	for (i = 0; i < (sizeof(hnf_offsets) / sizeof(unsigned long)); ++i) {
		retries = 10000;

		do {
			status = readl(DICKENS +
				       (0x10000 * hnf_offsets[i]) + 0x18);
			udelay(10);
		} while ((0 < --retries) && (0xc != (status & 0xf)));

		if (0 == retries)
			acp_failure(__FILE__, __FUNCTION__, __LINE__);
	}

	return;
}

/**
 * @brief board_init
 *
 * @return 0
 */
int
board_init(void)
{
	return 0;
}

/*
  ------------------------------------------------------------------------------
  misc_init_r
*/

int
misc_init_r(void)
{
	return 0;
}

void set_muxconf_regs_essential(void)
{
	return;
}

void set_muxconf_regs_non_essential(void)
{
	return;
}

/*
  ------------------------------------------------------------------------------
  board_early_init_f
*/

int
board_early_init_f(void)
{
	gd->ram_size = 0x40000000;

	return 0;
}

/*
  ------------------------------------------------------------------------------
  arch_early_init_r
*/

int
arch_early_init_r(void)
{
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
	char cpu_string[40];
	int node;
	unsigned long release_addr;
	int rc;
	acp_clock_t clocks[] = {
		clock_core, clock_peripheral, clock_emmc
	};
	const char *clock_names[] = {
		"/clocks/cpu", "/clocks/peripheral", "/clocks/emmc"
	};

	/*
  	  Set up the coherency domains and clusters.  This is handled
	  late in order to use the latest environment.
	*/

	if (0 != set_clusters())
		acp_failure(__FILE__, __FUNCTION__, __LINE__);

	/*
	  Set the PLL/Clock frequencies.
	*/

	for (i = 0; i < (sizeof(clocks) / sizeof(acp_clock_t)); ++i) {
		unsigned long clock_frequency;

		node = fdt_path_offset(blob, clock_names[i]);

		if (0 > node)
			acp_failure(__FILE__, __FUNCTION__, __LINE__);

		acp_clock_get(clocks[i], &clock_frequency);
		clock_frequency *= 1000;
		clock_frequency = htonl(clock_frequency);
		rc = fdt_setprop(blob, node, "frequency",
				 &clock_frequency, sizeof(unsigned long));

		if (0 != rc)
			acp_failure(__FILE__, __FUNCTION__, __LINE__);
	}				 

	/*
	  Fix up the spin table addresses.
	*/

	release_addr = htonl(_spin_table_start_ofs + spin_loop_release_offset);

	for (i = 1; i < 16; ++i) {
		sprintf(cpu_string, "/cpus/cpu@%d", i);
		node = fdt_path_offset(blob, cpu_string);

		if (0 > node)
			continue;

		rc = fdt_setprop(blob, node, "cpu-release-addr",
				 &release_addr, sizeof(unsigned long));

		if (0 != rc) {
			printf("%s:%d - Error setting property, %d!\n",
			       __FILE__, __LINE__, rc);
			continue;
		}
	}

	return;
}
