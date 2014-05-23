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
#include <asm/io.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/mmc_host_def.h>

#include "mux_data.h"

DECLARE_GLOBAL_DATA_PTR;

unsigned long pfuse __attribute__ ((section ("data")));

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
  set_cluster_coherency
*/

static int
set_cluster_coherency(unsigned cluster, unsigned state)
{
#ifndef CONFIG_AXXIA_SIM
	ncp_uint32_t sdcr_offsets[] = {
		0x00,		/* This is the DVM */
		0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27
	};
	int i;
	int retries;
	ncp_uint32_t mask;
	ncp_uint32_t value;
#ifdef CONFIG_AXXIA_EMU
	int bit_by_cluster[] = {19, 9};
#else
	int bit_by_cluster[] = {1, 9, 11, 19};
#endif

#ifdef CONFIG_AXXIA_EMU
	if (1 < cluster)
		return -1;
#else
	if (3 < cluster)
		return -1;
#endif

	printf("%s cluster %d %s the coherency domain.\n",
	       state ? "Adding" : "Removing",
	       cluster,
	       state ? "to" : "from");
	mask = (1 << bit_by_cluster[cluster]);

	for (i = 0; i < (sizeof(sdcr_offsets) / sizeof(ncp_uint32_t)); ++i) {
		int offset;

		offset = DICKENS | (sdcr_offsets[i] << 16);

		if (0 == state)
			writel(mask, (offset + 0x220));
		else
			writel(mask, (offset + 0x210));

		retries = 1000;

		do {
			--retries;
			value = readl(offset + 0x200);

			if (0 == state) {
				if (0 == (mask & value))
					break;
			} else {
				if (mask == (mask & value))
					break;
			}
		} while (0 < retries);

		if (0 == retries)
			return -1;
	}

#endif	/* CONFIG_AXXIA_SIM */
	return 0;
}

/*
  ------------------------------------------------------------------------------
  power_down_cluster
*/

#ifndef CONFIG_AXXIA_EMU

static int
power_down_cluster(int cluster)
{
	ncp_uint32_t value;
	ncp_uint32_t mask;
	int i;

	printf("Powering down cluster %d.\n", cluster);

	/*
	  Power down the cpus.
	*/

	for (i = 0; i < 4; ++i) {
		mask = (1 << (i + (cluster * 4)));

		/* clear nPWRUPCPURAM */
		ncr_and(NCP_REGION_ID(0x156, 0), 0x1488, ~mask);
		ncr_read32(NCP_REGION_ID(0x156, 0), 0x1488, &value);

		/* set nISOLATECPU */
		ncr_or(NCP_REGION_ID(0x156, 0), 0x148c, mask);
		ncr_read32(NCP_REGION_ID(0x156, 0), 0x148c, &value);

		/* clear nPWRUPCPUSTG2 */
		ncr_and(NCP_REGION_ID(0x156, 0), 0x1484, ~mask);
		ncr_read32(NCP_REGION_ID(0x156, 0), 0x1484, &value);

		/* clear nPWRUPCPUSTG1 */
		ncr_and(NCP_REGION_ID(0x156, 0), 0x1480, ~mask);
		ncr_read32(NCP_REGION_ID(0x156, 0), 0x1480, &value);
	}

	/*
	 */

	mask = (1 << cluster);

	/* set pwr_ACEPWRDNRQ bit for cluster */
	ncr_or(NCP_REGION_ID(0x156, 0), 0x142c, mask);

	/* set pwr_ACINACTM bit for cluster */
	ncr_or(NCP_REGION_ID(0x156, 0), 0x1408, mask);

	/*
	  Power down the L2.
	*/

	/* clear CSYSREQ_TS */
	ncr_and(NCP_REGION_ID(0x156, 0), 0x1410, ~mask);
	ncr_read32(NCP_REGION_ID(0x156, 0), 0x1410, &value);

	/* clear CSYSREQ_CNT */
	ncr_and(NCP_REGION_ID(0x156, 0), 0x1414, ~mask);
	ncr_read32(NCP_REGION_ID(0x156, 0), 0x1414, &value);

	/* set CHIPSELECTEN */
	ncr_or(NCP_REGION_ID(0x156, 0), 0x140c, mask);
	ncr_read32(NCP_REGION_ID(0x156, 0), 0x140c, &value);

	/* clear nPWRUPL2HSRAM */
	ncr_and(NCP_REGION_ID(0x156, 0), 0x1428, ~mask);
	ncr_read32(NCP_REGION_ID(0x156, 0), 0x1428, &value);

	ncr_and(NCP_REGION_ID(0x156, 0), (0x1588 + (cluster * 0xc)), ~0xff);
	ncr_read32(NCP_REGION_ID(0x156, 0), 0x1588 + (cluster * 0xc), &value);

	ncr_and(NCP_REGION_ID(0x156, 0), (0x1588 + (cluster * 0xc)), ~0xf00);
	ncr_read32(NCP_REGION_ID(0x156, 0), 0x1588 + (cluster * 0xc), &value);

	ncr_and(NCP_REGION_ID(0x156, 0), (0x1588 + (cluster * 0xc)),
		~(0xff000));
	ncr_read32(NCP_REGION_ID(0x156, 0), 0x1588 + (cluster * 0xc), &value);

	ncr_and(NCP_REGION_ID(0x156, 0), (0x1588 + (cluster * 0xc)), ~0xf00000);
	ncr_read32(NCP_REGION_ID(0x156, 0), 0x1588 + (cluster * 0xc), &value);

	ncr_and(NCP_REGION_ID(0x156, 0), (0x1588 + (cluster * 0xc)),
		~0xff000000);
	ncr_read32(NCP_REGION_ID(0x156, 0), 0x1588 + (cluster * 0xc), &value);

	ncr_and(NCP_REGION_ID(0x156, 0), (0x1584 + (cluster * 0xc)), ~0xf);
	ncr_read32(NCP_REGION_ID(0x156, 0), 0x1584 + (cluster * 0xc), &value);

	ncr_and(NCP_REGION_ID(0x156, 0), (0x1584 + (cluster * 0xc)), ~0xff0);
	ncr_read32(NCP_REGION_ID(0x156, 0), 0x1584 + (cluster * 0xc), &value);

	ncr_and(NCP_REGION_ID(0x156, 0), (0x1584 + (cluster * 0xc)), ~0xf000);
	ncr_read32(NCP_REGION_ID(0x156, 0), 0x1588 + (cluster * 0xc), &value);

	ncr_and(NCP_REGION_ID(0x156, 0), (0x1584 + (cluster * 0xc)), ~0xff0000);
	ncr_read32(NCP_REGION_ID(0x156, 0), 0x1588 + (cluster * 0xc), &value);

	ncr_and(NCP_REGION_ID(0x156, 0), (0x1584 + (cluster * 0xc)),
		~0xf000000);
	ncr_read32(NCP_REGION_ID(0x156, 0), 0x1588 + (cluster * 0xc), &value);

	ncr_and(NCP_REGION_ID(0x156, 0), (0x1584 + (cluster * 0xc)),
		~0xf0000000);
	ncr_read32(NCP_REGION_ID(0x156, 0), 0x1588 + (cluster * 0xc), &value);

	ncr_and(NCP_REGION_ID(0x156, 0), (0x1580 + (cluster * 0xc)), ~0xf);
	ncr_read32(NCP_REGION_ID(0x156, 0), 0x1588 + (cluster * 0xc), &value);

	ncr_and(NCP_REGION_ID(0x156, 0), (0x1580 + (cluster * 0xc)), ~0xf0);
	ncr_read32(NCP_REGION_ID(0x156, 0), 0x1588 + (cluster * 0xc), &value);

	ncr_and(NCP_REGION_ID(0x156, 0), (0x1580 + (cluster * 0xc)), ~0xff00);
	ncr_read32(NCP_REGION_ID(0x156, 0), 0x1588 + (cluster * 0xc), &value);

	ncr_and(NCP_REGION_ID(0x156, 0), (0x1580 + (cluster * 0xc)), ~0xf0000);
	ncr_read32(NCP_REGION_ID(0x156, 0), 0x1588 + (cluster * 0xc), &value);

	ncr_and(NCP_REGION_ID(0x156, 0), (0x1580 + (cluster * 0xc)),
		~0xff00000);
	ncr_read32(NCP_REGION_ID(0x156, 0), 0x1588 + (cluster * 0xc), &value);

	ncr_and(NCP_REGION_ID(0x156, 0), (0x1580 + (cluster * 0xc)),
		~0xf0000000);
	ncr_read32(NCP_REGION_ID(0x156, 0), 0x1588 + (cluster * 0xc), &value);

	/* Clear the hold bit for the cpus in this cluster. */
	mask = (0xf << (cluster * 4));
	ncr_or(NCP_REGION_ID(0x156, 0), 0x1010, mask);
	ncr_read32(NCP_REGION_ID(0x156, 0), 0x1010, &value);

	/* Clear the clusterN_clken bit. */
	ncr_and(NCP_REGION_ID(0x156, 0), 0x1400, (1 << cluster));
	ncr_read32(NCP_REGION_ID(0x156, 0), 0x1400, &value);

	return 0;
}

#endif

/*
  ------------------------------------------------------------------------------
  set_clusters
*/

static int
set_clusters(void)
{
	char *clusters_env;
	ncp_uint32_t clusters;

#ifdef CONFIG_AXXIA_EMU
	clusters = 0x1;
#else
	clusters = 0xf;
#endif

	clusters_env = getenv("clusters");

	if (NULL != clusters_env)
		clusters = simple_strtoul(clusters_env, NULL, 0);

	if (0 == (clusters & 1)) {
		printf("Cluster 0 MUST be enabled, enabling.\n");
		clusters |= 1;
	}

#ifdef CONFIG_AXXIA_EMU
	if (0 != (clusters & 0xc)) {
		printf("Emulation only supports clusters 0 and 1!\n"
		       "Change the \"clusters\" variable to 1 or 3.\n");
		return -1;
	}

	puts("Setting up Coherency for Clusters: 0");

	if (0 != (clusters & 0x2))
		puts(",1");

	puts("\n");

	if (0 != (clusters & 0x2)) {
		if (0 != set_cluster_coherency(1, 1))
			acp_failure(__FILE__, __func__, __LINE__);
	}
#else
	puts("Setting up Coherency for Clusters: 0");

	if (0 != (clusters & 0x2))
		puts(",1");

	if (0 != (clusters & 0x4))
		puts(",2");

	if (0 != (clusters & 0x8))
		puts(",3");

	puts("\n");

	if (0 == (clusters & 0x2)) {
		power_down_cluster(1);

		if (0 != set_cluster_coherency(1, 0))
			acp_failure(__FILE__, __func__, __LINE__);
	} else if (0 != set_cluster_coherency(1, 1)) {
		acp_failure(__FILE__, __func__, __LINE__);
	}

	if (0 == (clusters & 0x4)) {
		power_down_cluster(2);

		if (0 != set_cluster_coherency(2, 0))
			acp_failure(__FILE__, __func__, __LINE__);
	} else if (0 != set_cluster_coherency(2, 1)) {
		acp_failure(__FILE__, __func__, __LINE__);
	}

	if (0 == (clusters & 0x8)) {
		power_down_cluster(3);

		if (0 != set_cluster_coherency(3, 0))
			acp_failure(__FILE__, __func__, __LINE__);
	} else if (0 != set_cluster_coherency(3, 1)) {
		acp_failure(__FILE__, __func__, __LINE__);
	}
#endif

	return 0;
}

/*
  ==============================================================================
  ==============================================================================
  Public
  ==============================================================================
  ==============================================================================
*/

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
	if (0 != set_cluster_coherency(0, 1))
		acp_failure(__FILE__, __func__, __LINE__);

	/* Enable SW access to cp14 registers and power on the ETB RAM modules
	 * (via dbg_sw_enable register)
	 */
	writel(0xf, SYSCON + 0xcc);

	/* Enable EVENT (sev/wfe) signals to all cores */
	writel(0xffff, SYSCON + 0x14);

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
	/*
	  The bootROM code leaves SPI device 0 selected, BZ 45907.
	  Deselect here.
	*/

	writel(0x1f, (ncp_uint32_t *)(SSP + SSP_CSR));

	gd->ram_size = 0x40000000;

#ifdef CONFIG_HW_WATCHDOG
	(void)start_watchdog();
#endif

	return 0;
}

/*
  ------------------------------------------------------------------------------
  arch_early_init_r

  Called just after the heap has been initialized.
*/

int
arch_early_init_r(void)
{
	/*
	  System Memory Size
	*/

	printf("Sysmem Size: %llu Mb\n",
	       (sysmem_size() / (1024ULL * 1024ULL)));

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
	int rc;
#ifndef CONFIG_AXXIA_SIM
	acp_clock_t clocks[] = {
		clock_core, clock_peripheral, clock_emmc
	};
	const char *clock_names[] = {
		"/clocks/cpu", "/clocks/peripheral", "/clocks/emmc"
	};
	ncp_uint32_t phy0_ctrl, phy1_ctrl;
#endif
	char *ad_value;
	char *macspeed;
	ncp_uint32_t tmp;

	/*
	  Set up the coherency domains and clusters.  This is handled
	  late in order to use the latest environment.
	*/

	if (0 != set_clusters())
		acp_failure(__FILE__, __func__, __LINE__);

	/*
	  Set the PLL/Clock frequencies.
	*/

#ifndef CONFIG_AXXIA_SIM
	for (i = 0; i < (sizeof(clocks) / sizeof(acp_clock_t)); ++i) {
		node = fdt_path_offset(blob, clock_names[i]);

		if (0 > node)
			acp_failure(__FILE__, __func__, __LINE__);

		acp_clock_get(clocks[i], &tmp);
		tmp *= 1000;
		printf("%s/frequency: %u\n", clock_names[i], tmp);
		tmp = htonl(tmp);
		rc = fdt_setprop(blob, node, "frequency",
				 &tmp, sizeof(ncp_uint32_t));

		if (0 != rc)
			printf("%s:%d - Couldn't set PLLs!\n",
			       __FILE__, __LINE__);
	}
#endif

	/*
	  Fix up the spin table addresses.
	*/

	tmp = htonl(_spin_table_start_ofs + spin_loop_release_offset);

	for (i = 1; i < 16; ++i) {
		sprintf(cpu_string, "/cpus/cpu@%d", i);
		node = fdt_path_offset(blob, cpu_string);

		if (0 > node)
			continue;

		rc = fdt_setprop(blob, node, "cpu-release-addr",
				 &tmp, sizeof(ncp_uint32_t));

		if (0 != rc) {
			printf("%s:%d - Error setting property, %d!\n",
			       __FILE__, __LINE__, rc);
			continue;
		}
	}

	/*
	  Set the PHY link type.

	  The default is auto (auto-negotiate) if macspeed is not set.
	*/

	node = fdt_path_offset(blob, "/femac@0x2010120000");

	if (0 <= node) {
		macspeed = getenv("macspeed");

		if (NULL == macspeed)
			macspeed = "auto";

		if (0 == strncmp(macspeed, "auto", strlen("auto"))) {
			ad_value = getenv("ad_value");

			if (NULL == ad_value)
				tmp = htonl(0x1e1);
			else
				tmp = htonl(simple_strtoul(ad_value, NULL, 0));

			rc = fdt_setprop(blob, node, "ad-value", &tmp,
					 sizeof(ncp_uint32_t));

			if (0 != rc)
				printf("%s:%d - Couldn't set ad-value!\n",
				       __FILE__, __LINE__);

			rc = fdt_setprop(blob, node, "phy-link", "auto",
					 strlen("auto"));

			if (0 != rc)
				printf("%s:%d - Couldn't set phy-link!\n",
				       __FILE__, __LINE__);
		} else {
			rc = fdt_setprop(blob, node, "phy-link", macspeed,
					 strlen(macspeed));

			if (0 != rc)
				printf("%s:%d - Couldn't set phy-link!\n",
				       __FILE__, __LINE__);
		}
	}

	/*
	  Enable PEI0/PEI1 controllers
	*/

#ifndef CONFIG_AXXIA_SIM
	node = fdt_path_offset(blob, "/pciex@0x3000000000");

	if (0 <= node) {
		/* check if PEI0 is enabled */
		ncr_read32(NCP_REGION_ID(0x115, 0), 0x200, &phy0_ctrl);

		if (phy0_ctrl & 0x1) {
			/* PEI0 is enabled */
			rc = fdt_set_node_status(blob, node,
						 FDT_STATUS_OKAY, 0);

			if (0 != rc)
				printf("%s:%d - Couldn't set PEI0 status!\n",
				       __FILE__, __LINE__);

			printf("PEI0 is enabled\n");
		}
	}

	node = fdt_path_offset(blob, "/pciex@0x3080000000");

	if (0 <= node) {
		/* check if PEI1 is enabled */
		ncr_read32(NCP_REGION_ID(0x115, 3), 0x200, &phy1_ctrl);

		if (phy1_ctrl & 0x1) {
			/* PEI1 is enabled */
			rc = fdt_set_node_status(blob, node,
						 FDT_STATUS_OKAY, 0);

			if (0 != rc)
				printf("%s:%d - Couldn't set PEI1 status!\n",
				       __FILE__, __LINE__);
			printf("PEI1 is enabled\n");
		}
	}

	/*
	  Enable SRI00/SRIO1 controllers
	*/

	node = fdt_path_offset(blob, "/rapidio@0x3100000000");

	if (0 <= node) {
		/* check if SRIO0 is enabled */
		ncr_read32(NCP_REGION_ID(0x115, 0), 0x200, &phy0_ctrl);

		if (phy0_ctrl & 0x8) {
			/* SRIO0 is enabled */
			rc = fdt_set_node_status(blob, node,
						 FDT_STATUS_OKAY, 0);
			if (0 != rc)
				printf("%s:%d - Couldn't set SRIO0 status!\n",
				       __FILE__, __LINE__);
			printf("SRIO0 is enabled\n");
		}
	}

	node = fdt_path_offset(blob, "/rapidio@0x3140000000");

	if (0 <= node) {
		/* check if SRIO1 is enabled */
		ncr_read32(NCP_REGION_ID(0x115, 0), 0x200, &phy0_ctrl);

		if (phy0_ctrl & 0x400) {
			/* SRIO1 is enabled */
			rc = fdt_set_node_status(blob, node,
						 FDT_STATUS_OKAY, 0);

			if (0 != rc)
				printf("%s:%d - Couldn't set SRIO1 status!\n",
				       __FILE__, __LINE__);
			printf("SRIO1 is enabled\n");
		}
	}
#endif

#ifdef CONFIG_HW_WATCHDOG
	stop_watchdog();
#endif

	return;
}
