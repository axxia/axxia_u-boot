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
#include <serial.h>
#include <asm/io.h>

DECLARE_GLOBAL_DATA_PTR;

/*
  ==============================================================================
  ==============================================================================
  Private
  ==============================================================================
  ==============================================================================
*/

#define DONT_SET_CLUSTERS

#ifndef CONFIG_AXXIA_SIM
#ifndef DONT_SET_CLUSTERS
static int number_of_clusters = -1;
static int bit_by_cluster[4];
#endif
#endif

/*
  ------------------------------------------------------------------------------
  init_clusters_info
*/

#ifndef CONFIG_AXXIA_SIM
#ifndef DONT_SET_CLUSTERS
static int
initialize_cluster_info(void)
{
	/* pfuse gets initialized in lowlevel.S */
	unsigned long product_variant;
	unsigned long cluster_not_present_vector;
	unsigned long chip_type;
	unsigned long chip_version_major;

	if (-1 == number_of_clusters) {
		product_variant = (pfuse >> 24) & 7;
		cluster_not_present_vector = (pfuse >> 20) & 0xf;
		chip_type = pfuse & 0x1f;
		chip_version_major = (pfuse >> 8) & 7;
		printf("pfuse : 0x%x\n"
		       "\t   product_variant : 0x%lx\n"
		       "\t              cnpv : 0x%lx\n"
		       "\t         chip_type : 0x%lx\n"
		       "\tchip_version_major : 0x%lx\n",
		       pfuse, product_variant, cluster_not_present_vector,
		       chip_type, chip_version_major);

#if defined(CONFIG_AXXIA_EMU) || defined(CONFIG_AXXIA_SIM)
		number_of_clusters = 3;
		bit_by_cluster[0] = 19;
		bit_by_cluster[1] = 9;
		bit_by_cluster[2] = 1;

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
#endif
#endif

/*
  ------------------------------------------------------------------------------
  get_number_of_clusters
*/

#ifndef CONFIG_AXXIA_SIM
#ifndef DONT_SET_CLUSTERS

static unsigned long
get_number_of_clusters(void)
{
	if (0 != initialize_cluster_info())
		acp_failure(__FILE__, __func__, __LINE__);

	return number_of_clusters;
}

#endif	/* DONT_SET_CLUSTERS */
#endif

/*
  ------------------------------------------------------------------------------
  get_bit_by_cluster
*/

#ifndef CONFIG_AXXIA_SIM
#ifndef DONT_SET_CLUSTERS
static unsigned long
get_bit_by_cluster(unsigned long cluster)
{
	if (0 != initialize_cluster_info() ||
	    cluster >= number_of_clusters)
		acp_failure(__FILE__, __func__, __LINE__);

	return bit_by_cluster[cluster];
}
#endif
#endif

/*
  ------------------------------------------------------------------------------
  set_cluster_coherency
*/

#ifndef CONFIG_AXXIA_SIM
#ifndef DONT_SET_CLUSTERS
static int
set_cluster_coherency(unsigned cluster, unsigned state)
{
	unsigned int sdcr_offsets[] = {
		0x00,		/* This is the DVM */
		0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27
	};
	int i;
	int retries;
	unsigned int mask;
	unsigned int value;

#ifdef CONFIG_AXXIA_EMU
	if (2 < cluster)
		return -1;
#else
	if (3 < cluster)
		return -1;
#endif

	printf("%s cluster %d %s the coherency domain.\n",
	       state ? "Adding" : "Removing",
	       cluster,
	       state ? "to" : "from");
	return 0;
	mask = (1 << get_bit_by_cluster(cluster));

	for (i = 0; i < (sizeof(sdcr_offsets) / sizeof(unsigned int)); ++i) {
		void *offset;

		offset = (void *)(DICKENS | (sdcr_offsets[i] << 16));

		if (0 == state)
			writel((unsigned int)mask, (offset + 0x220));
		else
			writel((unsigned int)mask, (offset + 0x210));

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

		printf("%s:%d - i=%d retries=%d\n",
		       __FILE__, __LINE__,
		       i, retries); /* ZZZ */

		if (0 == retries)
			return -1;
	}

	return 0;
}
#endif
#endif

/*
  ------------------------------------------------------------------------------
  power_down_cluster
*/

#if !defined(CONFIG_AXXIA_EMU) && !defined(CONFIG_AXXIA_SIM)

static int
power_down_cluster(int cluster)
{
#ifndef CONFIG_AXXIA_SIM
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

#endif

	return 0;
}

#endif

/*
  ------------------------------------------------------------------------------
  set_clusters
*/

#ifndef DONT_SET_CLUSTERS

static int
set_clusters(void)
{
#ifndef CONFIG_AXXIA_SIM
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
	puts("Setting up Coherency for Clusters: 0,1,2\n");

	if (0 != set_cluster_coherency(1, 1))
			acp_failure(__FILE__, __func__, __LINE__);

	if (0 != set_cluster_coherency(2, 1))
			acp_failure(__FILE__, __func__, __LINE__);
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
#endif

	return 0;
}

#endif	/* DONT_SET_CLUSTERS */

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
#if 0
	void *page_table_address;

	page_table_address = (void *)&page_table[0];
#endif
#if 0
#if defined(AXXIA_FORCE_NORMAL_MODE)
	WATCHDOG_RESET();
	dcache_disable();
	enter_ns();
	setup_page_tables(page_table_address);
#elif !defined(AXXIA_FORCE_SECURE_MODE)
	if (0 != ((pfuse & 0x7e0) >>5)) {
		WATCHDOG_RESET();
		dcache_disable();
		enter_ns();
		setup_page_tables(page_table_address);
	}
#endif
#endif

	return 0;
}

/*
  ------------------------------------------------------------------------------
  misc_init_f
*/

int
misc_init_f(void)
{
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
#if 0
	unsigned long cntpct_low;
	unsigned long cntpct_high;
	unsigned long long cntpct0;
	unsigned long long cntpct1;
	int retries = WA_811981_RETRIES;

	/*
	  Workaround for ARM errata 811981.  After a reset, make sure
	  that cntpct is non-zero and incrementing.
	*/

	do {
		asm volatile ("mrrc p15, 0, %0, %1, c14"
			      : "=r" (cntpct_low), "=r" (cntpct_high));
		cntpct0 = (unsigned long long)cntpct_low |
			(unsigned long long)cntpct_high;
		--retries;
	} while (0ULL == cntpct0 && 0 < retries);

	if (0 == retries)
		acp_failure(__FILE__, __func__, __LINE__);

	retries = WA_811981_RETRIES;

	do {
		asm volatile ("mrrc p15, 0, %0, %1, c14"
			      : "=r" (cntpct_low), "=r" (cntpct_high));
		cntpct1 = (unsigned long long)cntpct_low |
			(unsigned long long)cntpct_high;
		--retries;
	} while (cntpct0 == cntpct1 && 0 < retries);

	if (0 == retries)
		acp_failure(__FILE__, __func__, __LINE__);
#endif

#ifndef CONFIG_AXXIA_SIM

	/* Add cluster 0 to the coherency domain. */

#ifndef DONT_SET_CLUSTERS
	if (0 != set_cluster_coherency(0, 1))
		acp_failure(__FILE__, __func__, __LINE__);
#endif

	/*
	  Enable SW access to cp14 registers and power on the ETB RAM
	  modules (via dbg_sw_enable register)
	*/

	/*writel(0xf, SYSCON + 0xcc);*/

	/* Enable EVENT (sev/wfe) signals to all cores */
	writel(0xffff, SYSCON + 0x14);

#endif	/* CONFIG_AXXIA_SIM */

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
  board_get_usable_ram_top
*/

ulong
board_get_usable_ram_top(ulong total_size)
{
	char *osmemory_string;
	unsigned long osmemory_value;

	osmemory_string = getenv("osmemory");

	if (NULL != osmemory_string) {
		osmemory_value = simple_strtoul(osmemory_string, NULL, 0);
		osmemory_value *= (1024 * 1024);
	} else {
		osmemory_value = OSMEMORY_DEFAULT;
	}

	return osmemory_value;
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

	serial_init();
	gd->have_console = 1;
	puts(" _______              _____            _____  __     ________            _____ \n"
	     " ___    |___  _____  ____(_)_____ _    __  / / /     ___  __ )_____________  /_\n"
	     " __  /| |_  |/_/_  |/_/_  /_  __ `/    _  / / /________  __  |  __ \\  __ \\  __/\n"
	     " _  ___ |_>  < __>  < _  / / /_/ /     / /_/ /_/_____/  /_/ // /_/ / /_/ / /_  \n"
	     " /_/  |_/_/|_| /_/|_| /_/  \\__,_/      \\____/        /_____/ \\____/\\____/\\__/  ");

#if defined(AXXIA_VERSION)
	printf("\n\nAxxia Version: %s", AXXIA_VERSION);
#else
	printf("\n\nAxxia Version: UNKNOWN");
#endif

	printf("\n%s:%d - GICC_IIDR=0x%x\n", __FILE__, __LINE__,
	       readl(0x8001000000 + 0xfc));
	printf("%s:%d - GICD_IIDR=0x%x (0x%x)\n", __FILE__, __LINE__,
	       readl(GICD_BASE + 0x8), readl(GICD_BASE + 0xffe0));
	printf("%s:%d - GICR_IIDR=0x%x (0x%x)\n", __FILE__, __LINE__,
	       readl(GICR_BASE + 0x4), readl(GICR_BASE + 0xffe0));

	printf("%s:%d - pfuse=0x%x\n", __FILE__, __LINE__,
	       readl(SYSCON + 0x34));
	printf("%s:%d - nca+0xe0 is 0x%x\n", __FILE__, __LINE__,
	       readl(NCA + 0xe0));

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
	/*char cpu_string[40];*/
	int node;
	int rc;
#if !defined(CONFIG_AXXIA_SIM) && !defined(CONFIG_AXXIA_EMU)
	int i;
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

#ifndef DONT_SET_CLUSTERS
	if (0 != set_clusters())
		acp_failure(__FILE__, __func__, __LINE__);
#endif

	/*
	  Set the PLL/Clock frequencies.
	*/

#if !defined(CONFIG_AXXIA_SIM) && !defined(CONFIG_AXXIA_EMU)
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

#if 0

	tmp = htonl((unsigned long)&spin_table[0] + spin_loop_release_offset);

	for (i = 1; i < 16; ++i) {
		sprintf(cpu_string, "/cpus/cpu@%d", i);
		node = fdt_path_offset(blob, cpu_string);
		tmp = (ncp_uint32_t)((void *)(&spin_table[i * SPIN_LOOP_SIZE]));
		tmp = htonl(tmp);

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

#endif

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

#if !defined(CONFIG_AXXIA_SIM) && !defined(CONFIG_AXXIA_EMU)
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

int
dram_init(void) {

	return 0;
}
