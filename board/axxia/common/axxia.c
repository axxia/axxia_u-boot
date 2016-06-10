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
ft_board_setup
*/

int
ft_board_setup(void *blob, bd_t *bd)
{
	int rc;
#if !defined(CONFIG_TARGET_SIMULATION) && !defined(CONFIG_TARGET_EMULATION)
#if defined(ACP_PEI0) || defined(ACP_PEI1) || defined(ACP_PEI2)
	int node;
	ncp_uint32_t pciesrio;
#endif
#endif
	u64 start[CONFIG_NR_DRAM_BANKS];
	u64 size[CONFIG_NR_DRAM_BANKS];

	/*
	  Disable PEIn controllers that are not enabled or RC.
	*/

#if !defined(CONFIG_TARGET_SIMULATION) && !defined(CONFIG_TARGET_EMULATION)
#if defined(ACP_PEI0) || defined(ACP_PEI1) || defined(ACP_PEI2)

	ncr_read32(NCP_REGION_ID(0x115, 0), 0, &pciesrio);

	node = fdt_path_offset(blob, "/soc/pcie@c000000000");

	if (0 <= node) {
		if (0 != (pciesrio & (1 << 0)) && 0 != (pciesrio & (1 << 22))) {
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
	}

	/* PEI1 is always RC. */
	node = fdt_path_offset(blob, "/soc/pcie@c800000000");

	if (0 <= node) {
		if (0 != (pciesrio & (1 << 1))) {
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
	}

	/* PEI2 is always RC. */
	node = fdt_path_offset(blob, "/soc/pcie@d000000000");

	if (0 <= node) {
		if (0 != (pciesrio & (1 << 1))) {
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
	}

#if 0

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
#endif
#endif

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
