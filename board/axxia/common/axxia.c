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

	printf("Sysmem Size: %llu Mb\n",
	       (sysmem_size() / (1024ULL * 1024ULL)));

	return 0;
}

/*
------------------------------------------------------------------------------
ft_board_setup
*/

int
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

	return 0;
}

int
dram_init(void) {

	return 0;
}
