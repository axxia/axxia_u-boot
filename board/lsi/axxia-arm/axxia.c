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
#include <watchdog.h>
#include <twl6035.h>
#include <asm/io.h>
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

static int number_of_clusters = -1;

#ifndef CONFIG_AXXIA_SIM

static int bit_by_cluster[4];

/*
  ------------------------------------------------------------------------------
  init_clusters_info
*/

static int
initialize_cluster_info(void)
{
	/* pfuse gets initialized in lowlevel.S */
#ifndef CONFIG_AXXIA_EMU
	unsigned long product_variant;
	unsigned long cluster_not_present_vector;
	unsigned long chip_type;
	unsigned long chip_version_major;
#endif

	if (-1 == number_of_clusters) {
#ifndef CONFIG_AXXIA_EMU
		product_variant = (pfuse >> 24) & 7;
		cluster_not_present_vector = (pfuse >> 20) & 0xf;
		chip_type = pfuse & 0x1f;
		chip_version_major = (pfuse >> 8) & 7;
#endif

#ifdef CONFIG_AXXIA_EMU
		number_of_clusters = 2;
		bit_by_cluster[0] = 19;
		bit_by_cluster[1] = 9;
		bit_by_cluster[2] = -1;
		bit_by_cluster[3] = -1;

		return 0;
#else
		number_of_clusters = 4;
		bit_by_cluster[0] = 1;
		bit_by_cluster[1] = 9;
		bit_by_cluster[2] = 11;
		bit_by_cluster[3] = 19;

		if (0 == chip_type ||
		    0 == cluster_not_present_vector ||
		    0 == chip_version_major)
			return 0;

		switch (product_variant) {
		case 1:			/* 3 clusters */
			number_of_clusters = 3;
			bit_by_cluster[3] = -1;

			switch (cluster_not_present_vector) {
			case 0x8:
				bit_by_cluster[0] = 1;
				bit_by_cluster[1] = 9;
				bit_by_cluster[2] = 11;
				break;
			case 0x4:
				bit_by_cluster[0] = 1;
				bit_by_cluster[1] = 9;
				bit_by_cluster[2] = 19;
				break;
			case 0x2:
				bit_by_cluster[0] = 1;
				bit_by_cluster[1] = 11;
				bit_by_cluster[2] = 19;
				break;
			case 0x1:
				bit_by_cluster[0] = 9;
				bit_by_cluster[1] = 11;
				bit_by_cluster[2] = 19;
				break;
			default:
				acp_failure(__FILE__, __func__, __LINE__);
				break;
			}
			break;
		case 3:			/* 2 clusters */
			number_of_clusters = 2;
			bit_by_cluster[2] = -1;
			bit_by_cluster[3] = -1;

			switch (cluster_not_present_vector) {
			case 0xc:
				bit_by_cluster[0] = 1;
				bit_by_cluster[1] = 9;
				break;
			case 0xa:
				bit_by_cluster[0] = 1;
				bit_by_cluster[1] = 11;
				break;
			case 0x9:
				bit_by_cluster[0] = 9;
				bit_by_cluster[1] = 11;
				break;
			case 0x6:
				bit_by_cluster[0] = 1;
				bit_by_cluster[1] = 19;
				break;
			case 0x5:
				bit_by_cluster[0] = 9;
				bit_by_cluster[1] = 19;
				break;
			case 0x3:
				bit_by_cluster[0] = 11;
				bit_by_cluster[1] = 19;
				break;
			default:
				acp_failure(__FILE__, __func__, __LINE__);
				break;
			}
			break;
		case 7:			/* 1 cluster */
			number_of_clusters = 1;
			bit_by_cluster[1] = -1;
			bit_by_cluster[2] = -1;
			bit_by_cluster[3] = -1;

			switch (cluster_not_present_vector) {
			case 0xe:
				bit_by_cluster[0] = 1;
				break;
			case 0xd:
				bit_by_cluster[0] = 9;
				break;
			case 0xb:
				bit_by_cluster[0] = 11;
				break;
			case 0x7:
				bit_by_cluster[0] = 19;
				break;
			default:
				acp_failure(__FILE__, __func__, __LINE__);
				break;
			}
			break;
		default:
			break;
		}

		return 0;
#endif
	}

	return 0;
}

/*
  ------------------------------------------------------------------------------
  get_number_of_clusters
*/

static unsigned long
get_number_of_clusters(void)
{
	if (0 != initialize_cluster_info())
		acp_failure(__FILE__, __func__, __LINE__);

	return number_of_clusters;
}

/*
  ------------------------------------------------------------------------------
  get_bit_by_cluster
*/

static unsigned long
get_bit_by_cluster(unsigned long cluster)
{
	if (0 != initialize_cluster_info() ||
	    cluster >= number_of_clusters)
		acp_failure(__FILE__, __func__, __LINE__);

	return bit_by_cluster[cluster];
}

#endif

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
	mask = (1 << get_bit_by_cluster(cluster));

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
	ncp_uint32_t clusters = 0;

#ifdef CONFIG_AXXIA_SIM
	clusters = 0xf;
	number_of_clusters = 4;
#else
	switch (get_number_of_clusters()) {
	case 1:
		clusters = 0x1;
		break;
	case 2:
		clusters = 0x3;
		break;
	case 3:
		clusters = 0x7;
		break;
	case 4:
		clusters = 0xf;
		break;
	default:
		acp_failure(__FILE__, __func__, __LINE__);
		break;
	}

	printf("%s:%d - Based on pfuse (0x%08lx), clusters=0x%lx number_of_clusters=%d\n",
	       __FILE__, __LINE__, (unsigned long)pfuse, (unsigned long)clusters,
	       number_of_clusters);
#endif

	clusters_env = getenv("clusters");

	if (NULL != clusters_env) {
		printf("Using \"clusters\" from the U-Boot Environment.\n");
		clusters = simple_strtoul(clusters_env, NULL, 0);
	}

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

	if (0 != (clusters & 0x2) && 2 <= number_of_clusters)
		puts(",1");

	if (0 != (clusters & 0x4) && 3 <= number_of_clusters)
		puts(",2");

	if (0 != (clusters & 0x8) && 4 <= number_of_clusters)
		puts(",3");

	puts("\n");

	if (2 <= number_of_clusters) {
		if (0 == (clusters & 0x2)) {
			power_down_cluster(1);

			if (0 != set_cluster_coherency(1, 0))
				acp_failure(__FILE__, __func__, __LINE__);
		} else if (0 != set_cluster_coherency(1, 1)) {
			acp_failure(__FILE__, __func__, __LINE__);
		}
	}

	if (3 <= number_of_clusters) {
		if (0 == (clusters & 0x4)) {
			power_down_cluster(2);

			if (0 != set_cluster_coherency(2, 0))
				acp_failure(__FILE__, __func__, __LINE__);
		} else if (0 != set_cluster_coherency(2, 1)) {
			acp_failure(__FILE__, __func__, __LINE__);
		}
	}

	if (4 <= number_of_clusters) {
		if (0 == (clusters & 0x8)) {
			power_down_cluster(3);

			if (0 != set_cluster_coherency(3, 0))
				acp_failure(__FILE__, __func__, __LINE__);
		} else if (0 != set_cluster_coherency(3, 1)) {
			acp_failure(__FILE__, __func__, __LINE__);
		}
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
#if defined(AXXIA_FORCE_NORMAL_MODE)
	WATCHDOG_RESET();
	dcache_disable();
	enter_ns();
	setup_page_tables((void *)_page_table_start);
#elif !defined(AXXIA_FORCE_SECURE_MODE)
	if (0 != ((pfuse & 0x7e0) >>5)) {
		WATCHDOG_RESET();
		dcache_disable();
		enter_ns();
		setup_page_tables((void *)_page_table_start);
	}
#endif

	return 0;
}

/*
  ------------------------------------------------------------------------------
  misc_init_r
*/

#define WA_811981_RETRIES 10000

int
misc_init_r(void)
{
	unsigned long cntpct_low;
	unsigned long cntpct_high;
	unsigned long long cntpct0;
	unsigned long long cntpct1;
	int retries = WA_811981_RETRIES;
	unsigned long ccn_qos_rni6_s0_value;
	char *ccn_qos_rni6_s0_env;
	unsigned long *address;
	unsigned long value;

	/*
	  Workaround for ARM errata 811981.  After a reset, make sure
	  that cntpct is non-zero and incrementing.
	*/

	do {
		asm volatile ("mrrc p15, 0, %0, %1, c14"
			      : "=r" (cntpct_low), "=r" (cntpct_high));
		cntpct0 = (unsigned long long)cntpct_low |
			(unsigned long long)cntpct_high << 32;
		--retries;
	} while (0ULL == cntpct0 && 0 < retries);

	if (0 == retries)
		acp_failure(__FILE__, __func__, __LINE__);

	retries = WA_811981_RETRIES;

	do {
		asm volatile ("mrrc p15, 0, %0, %1, c14"
			      : "=r" (cntpct_low), "=r" (cntpct_high));
		cntpct1 = (unsigned long long)cntpct_low |
			(unsigned long long)cntpct_high << 32;
		--retries;
	} while (cntpct0 == cntpct1 && 0 < retries);

	if (0 == retries)
		acp_failure(__FILE__, __func__, __LINE__);

	/* Add cluster 0 to the coherency domain. */

	if (0 != set_cluster_coherency(0, 1))
		acp_failure(__FILE__, __func__, __LINE__);

	/*
	  Enable SW access to cp14 registers and power on the ETB RAM
	  modules (via dbg_sw_enable register)
	*/

	writel(0xf, SYSCON + 0xcc);

	/* Enable EVENT (sev/wfe) signals to all cores */
	writel(0xffff, SYSCON + 0x14);

	/* Update AXI QoS */
	ccn_qos_rni6_s0_env = getenv("ccn_qos_rni6_s0");

	if (NULL == ccn_qos_rni6_s0_env)
		ccn_qos_rni6_s0_value = CCN_QOS_RNI6_SO_DEFAULT;
	else
		ccn_qos_rni6_s0_value =
			simple_strtoul(ccn_qos_rni6_s0_env, NULL, 0);

	address = (unsigned long *)(DICKENS | 0x86 << 16 | 0x10);
	value = *address;

	if (value != ccn_qos_rni6_s0_value) {
		printf("Updating s0_qos_control: 0x%08lx => 0x%08lx\n",
		       value, ccn_qos_rni6_s0_value);
		*address = ccn_qos_rni6_s0_value;
	}

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
#if defined(AXXIA_VERSION)
	printf("Axxia Version: %s\n", AXXIA_VERSION);
#else
	printf("Axxia Version: UNKNOWN\n");
#endif

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
#ifndef LEAVE_WATCHDOG_ON
	stop_watchdog();
#endif
#endif

	return;
}
