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

	/*
	  Enable SW access to cp14 registers and power on the ETB RAM
	  modules (via dbg_sw_enable register)
	*/

/*	writel(0xf, SYSCON + 0xcc); */

	/* Enable EVENT (sev/wfe) signals to all cores */
#ifdef CONFIG_AXXIA_XLF
	writel(0xffffffff, SYSCON + 0x40);
	writel(0xffffffff, SYSCON + 0x44);
#else
 	writel(0xffff, SYSCON + 0x14); 
#endif

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
#ifdef SYSCACHE_ONLY_MODE
		osmemory_value = (phys_size_t)SYSCACHE_SIZE;
#else
		osmemory_value = OSMEMORY_DEFAULT;
#endif
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
	unsigned int el;

	gd->ram_size = CONFIG_UBOOT_MAX_MEM;

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

#ifdef SYSCACHE_ONLY_MODE
	printf("\nRunning in System Cache");
#endif

	asm volatile("mrs %0, CurrentEL" : "=r" (el));

	if (0xc == el)
		printf("\nEL3");
	else if (0x8 == el)
		printf("\nEL2");
	else if (0x4 == el)
		printf("\nEL1");
	else
		printf("\nUnknown EL!");

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

	printf("Sysmem Size: %llu MB\n",
	       (sysmem_size() / (1024ULL * 1024ULL)));
	printf("Relocation Address: 0x%lx\n", gd->relocaddr);

	return 0;
}

/*
  ------------------------------------------------------------------------------
  ft_update_pei
*/

int
ft_update_pei(void *blob)
{
	int node;
	int rc;
	unsigned int value;
	unsigned int pei0_lanes = 0;
	unsigned int pei1_lanes = 0;
	unsigned int pei2_lanes = 0;

	/*
	  In this case, Linux will set up the PEIs.
	*/

	/* Add the pei_control node and set control based on the parameters. */

	node = fdt_path_offset(blob, "/soc");

	if (0 <= node) {
		rc = fdt_add_subnode(blob, node, "pei_control");

		if (0 > rc)
			return -1;
	} else
		return -1;

	node = fdt_path_offset(blob, "/soc/pei_control");

	if (0 <= node) {
		/* version */
		value = cpu_to_fdt32(pciesrio->version);
		rc = fdt_setprop(blob, node, "version", &value, sizeof(value));

		if (0 > rc)
			return -1;

		/* control */
		value = cpu_to_fdt32(pciesrio->control);
		rc = fdt_setprop(blob, node, "control", &value, sizeof(value));

		if (0 > rc)
			return -1;

		if (2 == pciesrio->version) {
			/* primary_input_clock */
			value = cpu_to_fdt32(pciesrio->primary_input_clock);
			rc = fdt_setprop(blob, node, "primary_input_clock",
					 &value, sizeof(value));

			if (0 > rc)
				return -1;

			/* input_ref_clock_range */
			value = cpu_to_fdt32(pciesrio->input_ref_clock_range);
			rc = fdt_setprop(blob, node, "input_ref_clock_range",
					 &value, sizeof(value));

			if (0 > rc)
				return -1;

			/* lane_0_eq_main */
			value = cpu_to_fdt32(pciesrio->lane_0_eq_main);
			rc = fdt_setprop(blob, node, "lane_0_eq_main",
					 &value, sizeof(value));

			if (0 > rc)
				return -1;

			/* lane_0_eq_pre */
			value = cpu_to_fdt32(pciesrio->lane_0_eq_pre);
			rc = fdt_setprop(blob, node, "lane_0_eq_pre",
					 &value, sizeof(value));

			if (0 > rc)
				return -1;

			/* lane_0_eq_post */
			value = cpu_to_fdt32(pciesrio->lane_0_eq_post);
			rc = fdt_setprop(blob, node, "lane_0_eq_post",
					 &value, sizeof(value));

			if (0 > rc)
				return -1;

			/* lane_0_eq_vboost */
			value = cpu_to_fdt32(pciesrio->lane_0_vboost);
			rc = fdt_setprop(blob, node, "lane_0_vboost",
					 &value, sizeof(value));

			if (0 > rc)
				return -1;

			/* lane_1_eq_main */
			value = cpu_to_fdt32(pciesrio->lane_1_eq_main);
			rc = fdt_setprop(blob, node, "lane_1_eq_main",
					 &value, sizeof(value));

			if (0 > rc)
				return -1;

			/* lane_1_eq_pre */
			value = cpu_to_fdt32(pciesrio->lane_1_eq_pre);
			rc = fdt_setprop(blob, node, "lane_1_eq_pre",
					 &value, sizeof(value));

			if (0 > rc)
				return -1;

			/* lane_1_eq_post */
			value = cpu_to_fdt32(pciesrio->lane_1_eq_post);
			rc = fdt_setprop(blob, node, "lane_1_eq_post",
					 &value, sizeof(value));

			if (0 > rc)
				return -1;

			/* lane_1_vboost */
			value = cpu_to_fdt32(pciesrio->lane_1_vboost);
			rc = fdt_setprop(blob, node, "lane_1_vboost",
					 &value, sizeof(value));

			if (0 > rc)
				return -1;
		}
	} else
		return -1;

	value = 0;

#if !defined(PEI_SETUP_IN_LINUX)
	if (0 != (global->flags & PARAMETERS_GLOBAL_SET_PEI))
		value = 1;
#endif

	value = cpu_to_fdt32(value);
	rc = fdt_setprop(blob, node, "initialized", &value, sizeof(value));

	if (0 > rc)
		return -1;

	if (0 == value)
		printf("Linux will handle PEI setup.\n");

	/* Enable PEIs based on the paramters. */

	value = (pciesrio->control & 0x3c00000) >> 22;
	/* Set PEI0 number of lanes */
	switch (value) {
	case 0:
		pei0_lanes = 8;
		break;
	case 1:
		pei0_lanes = 4;
		pei1_lanes = 4;
		break;
	case 2:
		pei0_lanes = 4;
		pei1_lanes = 2;
		break;
	case 3:
	case 6:
		pei0_lanes = 2;
		pei1_lanes = 2;
		pei2_lanes = 2;
		break;
	case 4:
		pei0_lanes = 2;
		pei1_lanes = 4;
		break;
	case 5:
		pei0_lanes = 2;
		pei1_lanes = 2;
		break;
	case 7:
		pei1_lanes = 4;
		break;
	case 8:
		pei1_lanes = 2;
		break;
	case 9:
		pei1_lanes = 2;
		pei2_lanes = 2;
		break;
	default:
		printf("%s:%d Unsupported lane configuration 0x%x\n", __FILE__,
		       __LINE__, value);
		pei0_lanes = 1;
		pei1_lanes = 1;
		pei2_lanes = 1;
	}

	node = fdt_path_offset(blob, "/soc/pcie@c000000000");

	if (0 <= node) {
		if (0 != (pciesrio->control & (1 << 0)) &&
		    0 != (pciesrio->control & (1 << 7))) {
			/* If PEI0 is enabled and is RC, set OKAY; */
			rc = fdt_set_node_status(blob, node,
						 FDT_STATUS_OKAY, 0);
			printf("Enabling PEI0 as Root Complex\n");
		} else {
			/* otherwise, set DISABLE. */
			rc = fdt_set_node_status(blob, node,
						 FDT_STATUS_DISABLED, 0);
			printf("Disabling PEI0\n");
		}

		if (0 != rc)
			printf("%s:%d - Couldn't set PEI0 status!\n",
			       __FILE__, __LINE__);
		pei0_lanes = cpu_to_fdt32(pei0_lanes);
		rc = fdt_setprop(blob, node, "num-lanes",
				 &pei0_lanes, sizeof(pei0_lanes));
	}

	node = fdt_path_offset(blob, "/soc/pcie@c800000000");

	if (0 <= node) {
		if (0 != (pciesrio->control & (1 << 1))) {
			/* If PEI1 is enabled, set OKAY; */
			rc = fdt_set_node_status(blob, node,
						 FDT_STATUS_OKAY, 0);
			printf("Enabling PEI1 as Root Complex\n");
		} else {
			/* otherwise, set DISABLE. */
			rc = fdt_set_node_status(blob, node,
						 FDT_STATUS_DISABLED, 0);
			printf("Disabling PEI1\n");
		}

		if (0 != rc)
			printf("%s:%d - Couldn't set PEI1 status!\n",
			       __FILE__, __LINE__);
		pei1_lanes = cpu_to_fdt32(pei1_lanes);
		rc = fdt_setprop(blob, node, "num-lanes",
				 &pei1_lanes, sizeof(pei1_lanes));
	}

	node = fdt_path_offset(blob, "/soc/pcie@d000000000");

	if (0 <= node) {
		if (0 != (pciesrio->control & (1 << 2))) {
			/* If PEI2 is enabled, set OKAY; */
			rc = fdt_set_node_status(blob, node,
						 FDT_STATUS_OKAY, 0);
			printf("Enabling PEI2 as Root Complex\n");
		} else {
			/* otherwise, set DISABLE. */
			rc = fdt_set_node_status(blob, node,
						 FDT_STATUS_DISABLED, 0);
			printf("Disabling PEI2\n");
		}

		if (0 != rc)
			printf("%s:%d - Couldn't set PEI2 status!\n",
			       __FILE__, __LINE__);

		pei2_lanes = cpu_to_fdt32(pei2_lanes);
		rc = fdt_setprop(blob, node, "num-lanes",
				 &pei2_lanes, sizeof(pei2_lanes));
	}

	/* DTS for rapidio is using 0x prefix. For now I'm using 0x here as
	well. Or should I unify DTS notation?
	*/
	node = fdt_path_offset(blob, "/soc/rapidio@0xb000000000");

	if (0 <= node) {
		if (0 != (pciesrio->control & (1 << 3))) {
			/* If SRIO0 is enabled, set OKAY; */
			rc = fdt_set_node_status(blob, node,
						 FDT_STATUS_OKAY, 0);
			printf("Enabling SRIO0\n");
		} else {
			/* otherwise, set DISABLE. */
			rc = fdt_set_node_status(blob, node,
						 FDT_STATUS_DISABLED, 0);
			printf("Disabling SRIO0\n");
		}

		if (0 != rc)
			printf("%s:%d - Couldn't set SRIO0 status!\n",
			       __FILE__, __LINE__);
	}

	node = fdt_path_offset(blob, "/soc/rapidio@0xb800000000");

	if (0 <= node) {
		if (0 != (pciesrio->control & (1 << 4))) {
			/* If SRIO1 is enabled, set OKAY; */
			rc = fdt_set_node_status(blob, node,
						 FDT_STATUS_OKAY, 0);
			printf("Enabling SRIO1\n");
		} else {
			/* otherwise, set DISABLE. */
			rc = fdt_set_node_status(blob, node,
						 FDT_STATUS_DISABLED, 0);
			printf("Disabling SRIO1\n");
		}

		if (0 != rc)
			printf("%s:%d - Couldn't set SRIO1 status!\n",
			       __FILE__, __LINE__);
	}

	node = fdt_path_offset(blob, "/soc/sata@a000000000");

	if (0 <= node) {
		if (0 != (pciesrio->control & (1 << 5))) {
			/* If SATA0 is enabled, set OKAY; */
			rc = fdt_set_node_status(blob, node,
						 FDT_STATUS_OKAY, 0);
			printf("Enabling SATA0\n");
		} else {
			/* otherwise, set DISABLE. */
			rc = fdt_set_node_status(blob, node,
						 FDT_STATUS_DISABLED, 0);
			printf("Disabling SATA0\n");
		}

		if (0 != rc)
			printf("%s:%d - Couldn't set SATA0 status!\n",
			       __FILE__, __LINE__);
	}

	node = fdt_path_offset(blob, "/soc/sata@a000010000");

	if (0 <= node) {
		if (0 != (pciesrio->control & (1 << 6))) {
			/* If SATA1 is enabled, set OKAY; */
			rc = fdt_set_node_status(blob, node,
						 FDT_STATUS_OKAY, 0);
			printf("Enabling SATA1\n");
		} else {
			/* otherwise, set DISABLE. */
			rc = fdt_set_node_status(blob, node,
						 FDT_STATUS_DISABLED, 0);
			printf("Disabling SATA1\n");
		}

		if (0 != rc)
			printf("%s:%d - Couldn't set SATA1 status!\n",
			       __FILE__, __LINE__);
	}

	char config = (pciesrio->control >> 22) & 0xf;

	switch (config) {
	case 0x0:
		printf("config: PEI0x8\n");
		break;
	case 0x1:
		printf("config: PEI0x4 PEI1x4\n");
		break;
	case 0x2:
		printf("config: PEI0x4 PEI1x2 SATA0x1 SATA1x1\n");
		break;
	case 0x3:
		printf("config: PEI0x2 PEI2x2 PEI1x2 SATA0x1 SATA1x1\n");
		break;
	case 0x4:
		printf("config: PEI0x2 SRIO0x2 PEI1x4\n");
		break;
	case 0x5:
		printf("config: PEI0x2 SRIO0x2 PEI1x2 SATA0x1 SATA1x1\n");
		break;
	case 0x6:
		printf("config: PEI0x2 SRIO0x2 PEI1x2 PEI2x2\n");
		break;
	case 0x7:
		printf("config: SRIO1x2 SRIO0x2 PEI1x4\n");
		break;
	case 0x8:
		printf("config: SRIO1x2 SRIO0x2 PEI1x2 SATA0x1 SATA1x1\n");
		break;
	case 0x9:
		printf("config: SRIO1x2 SRIO0x2 PEI1x2 PEI2x2\n");
		break;
	default:
		printf("config: unrecognized(%#08x)\n", config);
	};

	return 0;
}

/*
  ------------------------------------------------------------------------------
  ft_board_setup
*/

int
ft_board_setup(void *blob, bd_t *bd)
{
	int rc;
	u64 start[CONFIG_NR_DRAM_BANKS];
	u64 size[CONFIG_NR_DRAM_BANKS];
	int node;
	u32 tmp;

	/*
	  Update the PEI setup.
	*/

	rc = ft_update_pei(blob);

	if (0 != rc)
		printf("%s:%d - Couldn't update PEIs!\n",
		       __FILE__, __LINE__);

	/*
	  Update the clocks.
	*/

	node = fdt_path_offset(blob, "/clocks/clk_per");

	if (0 > node) {
		printf("/clocks/clk_per is missing, skipping update!\n");
	} else {
		acp_clock_get(clock_peripheral, &tmp);
		tmp *= 1000;
		printf("Peripheral frequency: %u\n", tmp);
		tmp = htonl(tmp);
		rc = fdt_setprop(blob, node, "clock-frequency",
				 &tmp, sizeof(ncp_uint32_t));

		if (0 != rc)
			printf("Couldn't set peripheral clock frequency!\n");
	}

	/*
	  Update the size of system memory in the device tree.
	*/

	start[0] = 0;
	size[0] = sysmem_size();
	rc = fdt_fixup_memory_banks(blob, start, size, 1);

	if (0 != rc)
		printf("%s:%d - Couldn't update memory banks!\n",
		       __FILE__, __LINE__);

#ifdef CONFIG_HW_WATCHDOG
#ifndef LEAVE_WATCHDOG_ON
	stop_watchdog();
#endif
#endif

	return 0;
}

int
dram_init(void) {

	return 0;
}
