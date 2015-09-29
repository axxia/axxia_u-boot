/*
 * (C) Copyright 2002-2006
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * To match the U-Boot user interface on ARM platforms to the U-Boot
 * standard (as on PPC platforms), some messages with debug character
 * are removed from the default U-Boot build.
 *
 * Define DEBUG here if you want additional info as shown below
 * printed upon startup:
 *
 * U-Boot code: 00F00000 -> 00F3C774  BSS: -> 00FC3274
 * IRQ Stack: 00ebff7c
 * FIQ Stack: 00ebef7c
 */

#include <common.h>
#include <command.h>
#include <environment.h>
#include <malloc.h>
#include <stdio_dev.h>
#include <version.h>
#include <net.h>
#include <serial.h>
#include <nand.h>
#include <onenand_uboot.h>
#include <mmc.h>
#include <libfdt.h>
#include <fdtdec.h>
#include <post.h>
#include <logbuff.h>

#ifdef CONFIG_BITBANGMII
#include <miiphy.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

ulong monitor_flash_len;

#ifdef CONFIG_HAS_DATAFLASH
extern int  AT91F_DataflashInit(void);
extern void dataflash_print_info(void);
#endif

#if defined(CONFIG_HARD_I2C) || \
    defined(CONFIG_SOFT_I2C)
#include <i2c.h>
#endif


/*****************************************************************
 * PCIe AXM55xx workaround
 *****************************************************************/
//#if defined(CONFIG_AXXIA_55XX) && defined(CONFIG_SPL_BUILD)
#ifdef CONFIG_SPL_PCI_SUPPORT
typedef enum {
        PEI_2_5G = 1,
        PEI_5G = 2
} peiSpeed_t;

extern unsigned long pfuse;

void pci_speed_change(char peiCore, peiSpeed_t changeSpeed) {
	unsigned lnkStatus, addr;
	unsigned width;
	peiSpeed_t speedBefore, speedAfter;
	unsigned peiControl;
	unsigned peiDelay, peiConfig;
	char * env_value;
	unsigned short v1_0 = 0;

	if (0 == ((pfuse & 0x7e0) >> 5)) {
		v1_0 = 1;
	}

	env_value = getenv("pei_speed_change_delay");
	if ((char *)0 != env_value) {
		peiDelay = simple_strtoul(env_value, NULL, 0);
		if (peiDelay <= 0) {
			peiDelay = 1;
		}
	} else {
		peiDelay = 1;
	}
	printf("delay used after PEI speed change = %d usecs\n", peiDelay);


	if (peiCore == 0) {
		addr = PCIE0_CONFIG;
		ncr_read32(NCP_REGION_ID(0x115, 0), 0x200, &peiControl);
	} else {
		addr = PCIE1_CONFIG;
		ncr_read32(NCP_REGION_ID(0x115, 3), 0x200, &peiControl);
	}


	lnkStatus = readl((void *)(addr + 0x117c));
	printf("PEI%d 0x117c LnkStatus = 0x%x\n",  peiCore,lnkStatus);
	speedBefore = lnkStatus & 0xf;
	width = (lnkStatus & 0xf0) >> 4;
	printf("PEI%d width - %d lane \n",peiCore, width);

	if (changeSpeed == speedBefore) {
		if (changeSpeed == PEI_2_5G)
			printf("PEI%d speed already set to (2.5 Gb/s)\n", peiCore);
		else
			printf("PEI%d speed already set to (5 Gb/s)\n", peiCore);
	} else if (changeSpeed == PEI_2_5G) {
		/* Change PEI speed to Gen 1 */
		writel(0x1, (void *)(addr + 0x90));
		writel(0x10000, (void *)(addr + 0x117c));

		/* delay for 1000ms */
		mdelay(1000);
		lnkStatus = readl((void *)(addr + 0x117c));
		printf("pei%d lnkStatus 0x117c after speed initiation = 0x%x\n", peiCore, lnkStatus);
		speedAfter = lnkStatus & 0xf;
		if ((lnkStatus & 0xc00) == 0xc00) {
			/* Please note that this is also ensuring that there is no link training error */
			printf("PEI%d has Link Training error\n", peiCore);
			if (lnkStatus & 0x10000) {
				/* clear speed change initiation bit */
				writel(0x20000, (void *)(addr + 0x117c));
			}
			return;
		}
		if ((lnkStatus & 0x10000) != 0x10000) {
			if (speedAfter == changeSpeed) {
				printf("Successfully changed PEI%d speed from Gen2 (5 Gb/s) to Gen 1 (2.5 Gb/s)\n", peiCore);
			} else {
				printf("Speed Initiation for PEI%d from Gen2 (5 Gb/s) to Gen 1 (2.5 Gb/s) failed\n", peiCore);
			}
		} else {
			/* clear speed change initiation bit */
			writel(0x20000, (void *)(addr + 0x117c));
			printf("Speed Initiation for PEI%d from Gen2 (5 Gb/s) to Gen 1 (2.5 Gb/s) failed\n", peiCore);
		}
	} else if (changeSpeed == PEI_5G) {
		if ((peiCore == 0) && ((peiControl & 0x1c400001)== 0x00400001)) {
			/* PEI0 RC x4 */
			if (v1_0) {
				peiConfig = readl((void *)(addr + 0x1000));
				/* clear force gen1 bit 18 */
				peiConfig = peiConfig & 0xfffbffff;
				writel(peiConfig, (void *)(addr + 0x1000));
			}
			
			/* Change PEI speed to Gen 2 */
			writel(0x2, (void *)(addr + 0x90));
			writel(0x10000, (void *)(addr + 0x117c));
			if (v1_0) {
				/* Applicable only to v1.0 */
				udelay(peiDelay);

				/* ncr w 0x115.1.0x08e 0x0406 */
				ncr_write16( NCP_REGION_ID( 0x115, 0x1 ), 0x8e, 0x0406 );

				/* ncr w 0x115.1.0x28e 0x0406 */
				ncr_write16( NCP_REGION_ID( 0x115, 0x1 ), 0x28e, 0x0406 );

				/* ncr w 0x115.1.0x68e 0x0406 */
				ncr_write16( NCP_REGION_ID( 0x115, 0x1 ), 0x68e, 0x0406 );
		
				/* ncr w 0x115.1.0x88e 0x0406 */
				ncr_write16( NCP_REGION_ID( 0x115, 0x1 ), 0x88e, 0x0406 );
			}
		} else if ((peiCore == 1) && ((peiControl & 0x0c400001)== 0x00400001)) {
			/* PEI1 RC x4 */
			if (v1_0) {
				peiConfig = readl((void *)(addr + 0x1000));
				/* clear force gen1 bit 18 */
				peiConfig = peiConfig & 0xfffbffff;
				writel(peiConfig, (void *)(addr + 0x1000));
			}
			
			/* Change PEI speed to Gen 2 */
			writel(0x2, (void *)(addr + 0x90));
			writel(0x10000, (void *)(addr + 0x117c));
			udelay(peiDelay);

			if (v1_0) {
				/* ncr w 0x115.4.0x08e 0x0406 */
				ncr_write16( NCP_REGION_ID( 0x115, 0x4 ), 0x8e, 0x0406 );

				/* ncr w 0x115.4.0x28e 0x0406 */
				ncr_write16( NCP_REGION_ID( 0x115, 0x4 ), 0x28e, 0x0406 );

				/* ncr w 0x115.4.0x68e 0x0406 */
				ncr_write16( NCP_REGION_ID( 0x115, 0x4 ), 0x68e, 0x0406 );
		
				/* ncr w 0x115.4.0x88e 0x0406 */
				ncr_write16( NCP_REGION_ID( 0x115, 0x4 ), 0x88e, 0x0406 );
			}
		} else if (((peiCore == 0) &&
			    (((peiControl & 0x1c400001)== 0x04400001))) ||
			   ((peiControl & 0x1c400001)== 0x08400001)) {
			/* PEI0 RC x2 */
			if (v1_0) {
				peiConfig = readl((void *)(addr + 0x1000));
				/* clear force gen1 bit 18 */
				peiConfig = peiConfig & 0xfffbffff;
				writel(peiConfig, (void *)(addr + 0x1000));
			}
			
			/* Change PEI speed to Gen 2 */
			writel(0x2, (void *)(addr + 0x90));
			writel(0x10000, (void *)(addr + 0x117c));
			udelay(peiDelay);

			if (v1_0) {
				/* ncr w 0x115.1.0x68e 0x0406 */
				ncr_write16( NCP_REGION_ID( 0x115, 0x1 ), 0x68e, 0x0406 );
		
				/* ncr w 0x115.1.0x88e 0x0406 */
				ncr_write16( NCP_REGION_ID( 0x115, 0x1 ), 0x88e, 0x0406 );
			}
		} else if ((peiCore == 1) && ((peiControl & 0x0c400001)== 0x04400001)) {
			/* PEI1 RC x2 */
			if (v1_0) {
				peiConfig = readl((void *)(addr + 0x1000));
				/* clear force gen1 bit 18 */
				peiConfig = peiConfig & 0xfffbffff;
				writel(peiConfig, (void *)(addr + 0x1000));
			}
			
			/* Change PEI speed to Gen 2 */
			writel(0x2, (void *)(addr + 0x90));
			writel(0x10000, (void *)(addr + 0x117c));
			udelay(peiDelay);

			if (v1_0) {
				/* ncr w 0x115.4.0x08e 0x0406 */
				ncr_write16( NCP_REGION_ID( 0x115, 0x4 ), 0x8e, 0x0406 );

				/* ncr w 0x115.4.0x28e 0x0406 */
				ncr_write16( NCP_REGION_ID( 0x115, 0x4 ), 0x28e, 0x0406 );
			}

		} else if ((peiCore == 0) && ((peiControl & 0x1c400001)== 0x14400001)) {
			/* PEI0 RC x1 */
			if (v1_0) {
				peiConfig = readl((void *)(addr + 0x1000));
				/* clear force gen1 bit 18 */
				peiConfig = peiConfig & 0xfffbffff;
				writel(peiConfig, (void *)(addr + 0x1000));
			}
			
			/* Change PEI speed to Gen 2 */
			writel(0x2, (void *)(addr + 0x90));
			writel(0x10000, (void *)(addr + 0x117c));
			udelay(peiDelay);
	
			if (v1_0) {
				/* ncr w 0x115.1.0x88e 0x0406 */
				ncr_write16( NCP_REGION_ID( 0x115, 0x1 ), 0x88e, 0x0406 );
			}
		} else if ((peiCore == 1) && ((peiControl & 0x0c400001)== 0x08400001)) {
			/* PEI1 RC x1 */
			if (v1_0) {
				peiConfig = readl((void *)(addr + 0x1000));
				/* clear force gen1 bit 18 */
				peiConfig = peiConfig & 0xfffbffff;
				writel(peiConfig, (void *)(addr + 0x1000));
			}
			
			/* Change PEI speed to Gen 2 */
			writel(0x2, (void *)(addr + 0x90));
			writel(0x10000, (void *)(addr + 0x117c));
			udelay(peiDelay);

			if (v1_0) {
				/* ncr w 0x115.4.0x08e 0x0406 */
				ncr_write16( NCP_REGION_ID( 0x115, 0x4 ), 0x8e, 0x0406 );
			}

		} else {
			printf("Unsupported PEI%d config = 0x%x\n", peiCore, peiControl);
			return;
		}
		/* delay for 1000 ms */
		mdelay(1000);
		lnkStatus = readl((void *)(addr + 0x117c));
		printf("pei%d lnkStatus 0x117c after speed initiation = 0x%x\n", peiCore, lnkStatus);
		speedAfter = lnkStatus & 0xf;

		if ((lnkStatus & 0xc00) == 0xc00) {
			/* Please note that this is also ensuring that there is no link training error */
			printf("PEI%d has Link Training error\n", peiCore);
			if (lnkStatus & 0x10000) {
				/* clear speed change initiation bit */
				writel(0x20000, (void *)(addr + 0x117c));
			}
			return;
		}

		if ((lnkStatus & 0x10000) != 0x10000) {
			if (speedAfter == changeSpeed) {
				printf("Successfully changed PEI%d speed from Gen1 (2.5 Gb/s) to Gen 2 (5 Gb/s)\n", peiCore);
			} else {
				printf("Speed Initiation for PEI%d from Gen1 (2.5 Gb/s) to Gen 2 (5 Gb/s) failed\n", peiCore);
			}
		} else {
			/* clear speed change initiation bit */
			writel(0x20000, (void *)(addr + 0x117c));
			printf("Speed Initiation for PEI%d from Gen1 (2.5 Gb/s) to Gen 2 (5 Gb/s) failed\n", peiCore);
		}
	}
}
#endif

/************************************************************************
 * Coloured LED functionality
 ************************************************************************
 * May be supplied by boards if desired
 */
inline void __coloured_LED_init(void) {}
void coloured_LED_init(void)
	__attribute__((weak, alias("__coloured_LED_init")));
inline void __red_led_on(void) {}
void red_led_on(void) __attribute__((weak, alias("__red_led_on")));
inline void __red_led_off(void) {}
void red_led_off(void) __attribute__((weak, alias("__red_led_off")));
inline void __green_led_on(void) {}
void green_led_on(void) __attribute__((weak, alias("__green_led_on")));
inline void __green_led_off(void) {}
void green_led_off(void) __attribute__((weak, alias("__green_led_off")));
inline void __yellow_led_on(void) {}
void yellow_led_on(void) __attribute__((weak, alias("__yellow_led_on")));
inline void __yellow_led_off(void) {}
void yellow_led_off(void) __attribute__((weak, alias("__yellow_led_off")));
inline void __blue_led_on(void) {}
void blue_led_on(void) __attribute__((weak, alias("__blue_led_on")));
inline void __blue_led_off(void) {}
void blue_led_off(void) __attribute__((weak, alias("__blue_led_off")));

/*
 ************************************************************************
 * Init Utilities							*
 ************************************************************************
 * Some of this code should be moved into the core functions,
 * or dropped completely,
 * but let's get it working (again) first...
 */

#if defined(CONFIG_ARM_DCC) && !defined(CONFIG_BAUDRATE)
#define CONFIG_BAUDRATE 115200
#endif

static int init_baudrate(void)
{
	gd->baudrate = getenv_ulong("baudrate", 10, CONFIG_BAUDRATE);
	return 0;
}

static int display_banner(void)
{
#ifdef CONFIG_AXXIA_ARM
	puts("\n"
	     "   ___             _        __  __    ___            __ \n"
	     "  / _ |__ ____ __ (_)__ _  / / / /___/ _ )___  ___  / /_\n"
	     " / __ |\\ \\ /\\ \\ // / _ `/ / /_/ /___/ _  / _ \\/ _ \\/ __/\n"
	     "/_/ |_/_\\_\\/_\\_\\/_/\\_,_/  \\____/   /____/\\___/\\___/\\__/ \n");
#endif
	printf("\n\n%s\n\n", version_string);
	debug("U-Boot code: %08lX -> %08lX  BSS: -> %08lX\n",
	       _TEXT_BASE,
	       _bss_start_ofs + _TEXT_BASE, _bss_end_ofs + _TEXT_BASE);
#ifdef CONFIG_MODEM_SUPPORT
	debug("Modem Support enabled\n");
#endif
#ifdef CONFIG_USE_IRQ
	debug("IRQ Stack: %08lx\n", IRQ_STACK_START);
	debug("FIQ Stack: %08lx\n", FIQ_STACK_START);
#endif

	return (0);
}

/*
 * WARNING: this code looks "cleaner" than the PowerPC version, but
 * has the disadvantage that you either get nothing, or everything.
 * On PowerPC, you might see "DRAM: " before the system hangs - which
 * gives a simple yet clear indication which part of the
 * initialization if failing.
 */
static int display_dram_config(void)
{
	int i;

#ifdef DEBUG
	puts("RAM Configuration:\n");

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++) {
		printf("Bank #%d: %08lx ", i, gd->bd->bi_dram[i].start);
		print_size(gd->bd->bi_dram[i].size, "\n");
	}
#else
	ulong size = 0;

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++)
		size += gd->bd->bi_dram[i].size;

	puts("DRAM:  ");
	print_size(size, "\n");
#endif

	return (0);
}

#if defined(CONFIG_HARD_I2C) || defined(CONFIG_SOFT_I2C)
static int init_func_i2c(void)
{
	puts("I2C:   ");
	i2c_init(CONFIG_SYS_I2C_SPEED, CONFIG_SYS_I2C_SLAVE);
	puts("ready\n");
	return (0);
}
#endif

#if defined(CONFIG_CMD_PCI) || defined (CONFIG_PCI)


struct serdes_value_t {
unsigned short offset;
unsigned short value;
};

void pciesrio_serdes_powerdown(unsigned long pcieSrioVal)
{
	int i;
	unsigned short hss5Val, hss6Val, regVal;
	struct serdes_value_t serdes_values[] = {
		{0x00ba, 0},
		{0x001c, 0},
		{0x0010, 0},
		{0x02ba, 0},
		{0x021c, 0},
		{0x0210, 0},
		{0x06ba, 0},
		{0x061c, 0},
		{0x0610, 0},
		{0x08ba, 0},
		{0x081c, 0},
		{0x0810, 0},
	};

	hss5Val = (pcieSrioVal >> 12);
	if (hss5Val & 0x1) {
		/* Powerdown HSS5 ch0 */
		serdes_values[0].value = 1;
	}
	if (hss5Val & 0x2) {
		/* Powerdown HSS5 ch1 */
		serdes_values[3].value = 1;
	}
	if (hss5Val & 0x4) {
		/* Powerdown HSS5 ch2 */
		serdes_values[6].value = 1;
	}
	if (hss5Val & 0x8) {
		/* Powerdown HSS5 ch3 */
		serdes_values[9].value = 1;
	}

	for (i = 0; i < 12; i = i+3) {
		if (serdes_values[i].value) {
			/* pd_pin_override 0x115.0x1.0xba bit 4 */
			ncr_read16(NCP_REGION_ID(0x115, 1),
				serdes_values[i].offset, &regVal);
			regVal = regVal | (0x1 << 4);
			ncr_write16(NCP_REGION_ID(0x115, 1),
				serdes_values[i].offset, regVal);

			/* rxpd_r2a 0x115.0x1.0x1c bit 14 */
			ncr_read16(NCP_REGION_ID(0x115, 1),
				serdes_values[i+1].offset, &regVal);
			regVal = regVal | (0x1 << 14);
			ncr_write16(NCP_REGION_ID(0x115, 1),
				serdes_values[i+1].offset, regVal);

			/* txpd_r2a 0x115.0x1.0x10 bit 10 */
			ncr_read16(NCP_REGION_ID(0x115, 1),
				serdes_values[i+2].offset, &regVal);
			regVal = regVal | (0x1 << 10);
			ncr_write16(NCP_REGION_ID(0x115, 1),
				serdes_values[i+2].offset, regVal);
		}
	}
	serdes_values[0].value = 0;
	serdes_values[3].value = 0;
	serdes_values[6].value = 0;
	serdes_values[9].value = 0;

	hss6Val = (pcieSrioVal >> 16);
	if (hss6Val & 0x1) {
		/* Powerdown HSS6 ch0 */
		serdes_values[0].value = 1;
	}
	if (hss6Val & 0x2) {
		/* Powerdown HSS6 ch1 */
		serdes_values[3].value = 1;
	}
	if (hss6Val & 0x4) {
		/* Powerdown HSS6 ch2 */
		serdes_values[6].value = 1;
	}
	if (hss6Val & 0x8) {
		/* Powerdown HSS6 ch3 */
		serdes_values[9].value = 1;
	}
	for (i = 0; i < 12; i = i+3) {
		if (serdes_values[i].value) {
			/* pd_pin_override 0x115.0x4.0xba bit 4 */
			ncr_read16(NCP_REGION_ID(0x115, 4),
				serdes_values[i].offset, &regVal);
			regVal = regVal | (0x1 << 4);
			ncr_write16(NCP_REGION_ID(0x115, 4),
				serdes_values[i].offset, regVal);
			/* rxpd_r2a 0x115.0x4.0x1c bit 14 */
			ncr_read16(NCP_REGION_ID(0x115, 4),
				serdes_values[i+1].offset, &regVal);
			regVal = regVal | (0x1 << 14);
			ncr_write16(NCP_REGION_ID(0x115, 4),
				serdes_values[i+1].offset, regVal);

			/* txpd_r2a 0x115.0x4.0x10 bit 10 */
			ncr_read16(NCP_REGION_ID(0x115, 4),
				serdes_values[i+2].offset, &regVal);
			regVal = regVal | (0x1 << 10);
			ncr_write16(NCP_REGION_ID(0x115, 4),
				serdes_values[i+2].offset, regVal);
		}
	}

}

#include <pci.h>
static int arm_pci_init(void)
{

#ifdef CONFIG_SPL_PCI_SUPPORT
	{
	char *env_value;
	unsigned pciStatus, linkState;
	unsigned pei0Control, pei1Control;

	ncr_read32(NCP_REGION_ID(0x115, 0), 0x200, &pei0Control);
	ncr_read32(NCP_REGION_ID(0x115, 3), 0x200, &pei1Control);

	if (pei0Control & 0x1) {
		pciStatus = readl((void *)(PCIE0_CONFIG + 0x1004));
		printf("PEI0 pciStatus = 0x%x\n", pciStatus);
		linkState = (pciStatus & 0x3f00) >> 8;
		if (linkState == 0xb) {
			printf("PCIE0 link State UP = 0x%x\n", linkState);
			env_value = getenv("pei0_speed");
			if ((char *)0 != env_value) {
				unsigned pei0_speed;

				pei0_speed = simple_strtoul(env_value, NULL, 0);
				/* speed change applies only to PEI RC mode */
				if (pei0Control & 0x400000)
					pci_speed_change(0, pei0_speed);
			}
		} else {
			printf("PCIE0 link State DOWN = 0x%x\n", linkState);
		}
	}

	if (pei1Control & 0x1) {
		pciStatus = readl((void *)(PCIE1_CONFIG + 0x1004));
		printf("PEI1 pciStatus = 0x%x\n", pciStatus);
		linkState = (pciStatus & 0x3f00) >> 8;

		if (linkState == 0xb) {
			printf("PCIE1 link State UP = 0x%x\n", linkState);
			env_value = getenv("pei1_speed");
			if ((char *)0 != env_value) {
				unsigned pei1_speed;

				pei1_speed = simple_strtoul(env_value, NULL, 0);
				/* speed change applies only to PEI RC mode */
				if (pei1Control & 0x400000)
					pci_speed_change(1, pei1_speed);
			}
		} else {
			printf("PCIE1 link State DOWN = 0x%x\n", linkState);
		}
	}
}
#endif
#if defined(CONFIG_CMD_PCI) || defined (CONFIG_PCI)
{
	if (0 != (global->flags & PARAMETERS_GLOBAL_SET_PEI))
		pciesrio_serdes_powerdown(pciesrio->control);

	pci_init();
}
#endif
	return 0;
}
#endif /* CONFIG_CMD_PCI || CONFIG_PCI */

/*
 * Breathe some life into the board...
 *
 * Initialize a serial port as console, and carry out some hardware
 * tests.
 *
 * The first part of initialization is running from Flash memory;
 * its main purpose is to initialize the RAM so that we
 * can relocate the monitor code to RAM.
 */

/*
 * All attempts to come up with a "common" initialization sequence
 * that works for all boards and architectures failed: some of the
 * requirements are just _too_ different. To get rid of the resulting
 * mess of board dependent #ifdef'ed code we now make the whole
 * initialization sequence configurable to the user.
 *
 * The requirements for any new initalization function is simple: it
 * receives a pointer to the "global data" structure as it's only
 * argument, and returns an integer return code, where 0 means
 * "continue" and != 0 means "fatal error, hang the system".
 */
typedef int (init_fnc_t) (void);

int print_cpuinfo(void);

void __dram_init_banksize(void)
{
	gd->bd->bi_dram[0].start = CONFIG_SYS_SDRAM_BASE;
	gd->bd->bi_dram[0].size =  gd->ram_size;
}
void dram_init_banksize(void)
	__attribute__((weak, alias("__dram_init_banksize")));

int __arch_cpu_init(void)
{
	return 0;
}
int arch_cpu_init(void)
	__attribute__((weak, alias("__arch_cpu_init")));

int __power_init_board(void)
{
	return 0;
}
int power_init_board(void)
	__attribute__((weak, alias("__power_init_board")));

	/* Record the board_init_f() bootstage (after arch_cpu_init()) */
static int mark_bootstage(void)
{
	bootstage_mark_name(BOOTSTAGE_ID_START_UBOOT_F, "board_init_f");

	return 0;
}

init_fnc_t *init_sequence[] = {
	arch_cpu_init,		/* basic arch cpu dependent setup */
	mark_bootstage,
#ifdef CONFIG_OF_CONTROL
	fdtdec_check_fdt,
#endif
#if defined(CONFIG_BOARD_EARLY_INIT_F)
	board_early_init_f,
#endif
	//timer_init,		/* initialize timer */
#ifdef CONFIG_BOARD_POSTCLK_INIT
	board_postclk_init,
#endif
#ifdef CONFIG_FSL_ESDHC
	get_clocks,
#endif
	env_init,		/* initialize environment */
	init_baudrate,		/* initialze baudrate settings */
	serial_init,		/* serial communications setup */
#ifndef CONFIG_AXXIA_ARM
	console_init_f,		/* stage 1 init of console */
#endif
	display_banner,		/* say that we are here */
#if defined(CONFIG_DISPLAY_CPUINFO)
	print_cpuinfo,		/* display cpu info (and speed) */
#endif
#if defined(CONFIG_DISPLAY_BOARDINFO)
	checkboard,		/* display board info */
#endif
#if defined(CONFIG_HARD_I2C) || defined(CONFIG_SOFT_I2C)
	init_func_i2c,
#endif
#if 0
	dram_init,		/* configure available RAM banks */
#endif
	NULL,
};

void board_init_f(ulong bootflag)
{
	bd_t *bd;
	init_fnc_t **init_fnc_ptr;
	gd_t *id;
	ulong addr, addr_sp;
#ifdef CONFIG_PRAM
	ulong reg;
#endif

	void *new_fdt = NULL;
	size_t fdt_size = 0;

	memset((void *)gd, 0, sizeof(gd_t));

	gd->mon_len = _bss_end_ofs;
#ifdef CONFIG_OF_EMBED
	/* Get a pointer to the FDT */
	gd->fdt_blob = _binary_dt_dtb_start;
#elif defined CONFIG_OF_SEPARATE
	/* FDT is at end of image */
	gd->fdt_blob = (void *)(_end_ofs + _TEXT_BASE);
#endif
	/* Allow the early environment to override the fdt address */
	gd->fdt_blob = (void *)getenv_ulong("fdtcontroladdr", 16,
						(uintptr_t)gd->fdt_blob);

	for (init_fnc_ptr = init_sequence; *init_fnc_ptr; ++init_fnc_ptr) {
		if ((*init_fnc_ptr)() != 0) {
			hang ();
		}
	}

#ifdef CONFIG_OF_CONTROL
	/* For now, put this check after the console is ready */
	if (fdtdec_prepare_fdt()) {
		panic("** CONFIG_OF_CONTROL defined but no FDT - please see "
			"doc/README.fdt-control");
	}
#endif

	debug("monitor len: %08lX\n", gd->mon_len);
	/*
	 * Ram is setup, size stored in gd !!
	 */
	debug("ramsize: %08lX\n", gd->ram_size);
#if defined(CONFIG_SYS_MEM_TOP_HIDE)
	/*
	 * Subtract specified amount of memory to hide so that it won't
	 * get "touched" at all by U-Boot. By fixing up gd->ram_size
	 * the Linux kernel should now get passed the now "corrected"
	 * memory size and won't touch it either. This should work
	 * for arch/ppc and arch/powerpc. Only Linux board ports in
	 * arch/powerpc with bootwrapper support, that recalculate the
	 * memory size from the SDRAM controller setup will have to
	 * get fixed.
	 */
	gd->ram_size -= CONFIG_SYS_MEM_TOP_HIDE;
#endif

	addr = CONFIG_SYS_SDRAM_BASE + gd->ram_size;

#ifdef CONFIG_LOGBUFFER
#ifndef CONFIG_ALT_LB_ADDR
	/* reserve kernel log buffer */
	addr -= (LOGBUFF_RESERVE);
	debug("Reserving %dk for kernel logbuffer at %08lx\n", LOGBUFF_LEN,
		addr);
#endif
#endif

#ifdef CONFIG_PRAM
	/*
	 * reserve protected RAM
	 */
	reg = getenv_ulong("pram", 10, CONFIG_PRAM);
	addr -= (reg << 10);		/* size is in kB */
	debug("Reserving %ldk for protected RAM at %08lx\n", reg, addr);
#endif /* CONFIG_PRAM */

#if !(defined(CONFIG_SYS_ICACHE_OFF) && defined(CONFIG_SYS_DCACHE_OFF))
#ifndef CONFIG_AXXIA_ARM
	/* reserve TLB table */
	gd->tlb_size = 4096 * 4;
	addr -= gd->tlb_size;

	/* round down to next 64 kB limit */
	addr &= ~(0x10000 - 1);

	gd->tlb_addr = addr;
	debug("TLB table from %08lx to %08lx\n", addr, addr + gd->tlb_size);
#endif
#endif

	/* round down to next 4 kB limit */
	addr &= ~(4096 - 1);
	debug("Top of RAM usable for U-Boot at: %08lx\n", addr);

#ifdef CONFIG_LCD
#ifdef CONFIG_FB_ADDR
	gd->fb_base = CONFIG_FB_ADDR;
#else
	/* reserve memory for LCD display (always full pages) */
	addr = lcd_setmem(addr);
	gd->fb_base = addr;
#endif /* CONFIG_FB_ADDR */
#endif /* CONFIG_LCD */

	/*
	 * reserve memory for U-Boot code, data & bss
	 * round down to next 4 kB limit
	 */
	addr -= gd->mon_len;
	addr &= ~(4096 - 1);

	debug("Reserving %ldk for U-Boot at: %08lx\n", gd->mon_len >> 10, addr);

#ifndef CONFIG_SPL_BUILD
	/*
	 * reserve memory for malloc() arena
	 */
	addr_sp = addr - TOTAL_MALLOC_LEN;
	debug("Reserving %dk for malloc() at: %08lx\n",
			TOTAL_MALLOC_LEN >> 10, addr_sp);
	/*
	 * (permanently) allocate a Board Info struct
	 * and a permanent copy of the "global" data
	 */
	addr_sp -= sizeof (bd_t);
	bd = (bd_t *) addr_sp;
	gd->bd = bd;
	debug("Reserving %zu Bytes for Board Info at: %08lx\n",
			sizeof (bd_t), addr_sp);

#ifdef CONFIG_MACH_TYPE
	gd->bd->bi_arch_number = CONFIG_MACH_TYPE; /* board id for Linux */
#endif

	addr_sp -= sizeof (gd_t);
	id = (gd_t *) addr_sp;
	debug("Reserving %zu Bytes for Global Data at: %08lx\n",
			sizeof (gd_t), addr_sp);

#if defined(CONFIG_OF_SEPARATE) && defined(CONFIG_OF_CONTROL)
	/*
	 * If the device tree is sitting immediate above our image then we
	 * must relocate it. If it is embedded in the data section, then it
	 * will be relocated with other data.
	 */
	if (gd->fdt_blob) {
		fdt_size = ALIGN(fdt_totalsize(gd->fdt_blob) + 0x1000, 32);

		addr_sp -= fdt_size;
		new_fdt = (void *)addr_sp;
		debug("Reserving %zu Bytes for FDT at: %08lx\n",
		      fdt_size, addr_sp);
	}
#endif

	/* setup stackpointer for exeptions */
	gd->irq_sp = addr_sp;
#ifdef CONFIG_USE_IRQ
	addr_sp -= (CONFIG_STACKSIZE_IRQ+CONFIG_STACKSIZE_FIQ);
	debug("Reserving %zu Bytes for IRQ stack at: %08lx\n",
		CONFIG_STACKSIZE_IRQ+CONFIG_STACKSIZE_FIQ, addr_sp);
#endif
	/* leave 3 words for abort-stack    */
	addr_sp -= 12;

	/* 8-byte alignment for ABI compliance */
	addr_sp &= ~0x07;
#else
	addr_sp += 128;	/* leave 32 words for abort-stack   */
	gd->irq_sp = addr_sp;
#endif

	debug("New Stack Pointer is: %08lx\n", addr_sp);

#ifdef CONFIG_POST
	post_bootmode_init();
	post_run(NULL, POST_ROM | post_bootmode_get(0));
#endif

	gd->bd->bi_baudrate = gd->baudrate;
	/* Ram ist board specific, so move it to board code ... */
	dram_init_banksize();
	display_dram_config();	/* and display it */

	gd->relocaddr = addr;
	gd->start_addr_sp = addr_sp;
	gd->reloc_off = addr - _TEXT_BASE;
	debug("relocation Offset is: %08lx\n", gd->reloc_off);
	if (new_fdt) {
		memcpy(new_fdt, gd->fdt_blob, fdt_size);
		gd->fdt_blob = new_fdt;
	}
	memcpy(id, (void *)gd, sizeof(gd_t));
}

#if !defined(CONFIG_SYS_NO_FLASH)
static char *failed = "*** failed ***\n";
#endif

/*
 * Tell if it's OK to load the environment early in boot.
 *
 * If CONFIG_OF_CONFIG is defined, we'll check with the FDT to see
 * if this is OK (defaulting to saying it's not OK).
 *
 * NOTE: Loading the environment early can be a bad idea if security is
 *       important, since no verification is done on the environment.
 *
 * @return 0 if environment should not be loaded, !=0 if it is ok to load
 */
static int should_load_env(void)
{
#ifdef CONFIG_OF_CONTROL
	return fdtdec_get_config_int(gd->fdt_blob, "load-environment", 1);
#elif defined CONFIG_DELAY_ENVIRONMENT
	return 0;
#else
	return 1;
#endif
}

#if defined(CONFIG_DISPLAY_BOARDINFO_LATE) && defined(CONFIG_OF_CONTROL)
static void display_fdt_model(const void *blob)
{
	const char *model;

	model = (char *)fdt_getprop(blob, 0, "model", NULL);
	printf("Model: %s\n", model ? model : "<unknown>");
}
#endif

/************************************************************************
 *
 * This is the next part if the initialization sequence: we are now
 * running from RAM and have a "normal" C environment, i. e. global
 * data can be written, BSS has been cleared, the stack size in not
 * that critical any more, etc.
 *
 ************************************************************************
 */

void board_init_r(gd_t *id, ulong dest_addr)
{
	ulong malloc_start;
#if !defined(CONFIG_SYS_NO_FLASH)
	ulong flash_size;
#endif

#if 0
extern unsigned _u_boot_list_cmd__start; /* SR */
extern unsigned _u_boot_list__start; /* SR */
#endif

	gd->flags |= GD_FLG_RELOC;	/* tell others: relocation done */
	bootstage_mark_name(BOOTSTAGE_ID_START_UBOOT_R, "board_init_r");

	monitor_flash_len = _end_ofs;

#ifndef CONFIG_AXXIA_ARM
	/* Enable caches */
	enable_caches();
#endif

	debug("monitor flash len: %08lX\n", monitor_flash_len);
	board_init();	/* Setup chipselects */
	/*
	 * TODO: printing of the clock inforamtion of the board is now
	 * implemented as part of bdinfo command. Currently only support for
	 * davinci SOC's is added. Remove this check once all the board
	 * implement this.
	 */
#ifdef CONFIG_CLOCKS
	set_cpu_clk_info(); /* Setup clock information */
#endif

	serial_initialize();

	debug("Now running in RAM - U-Boot at: %08lx\n", dest_addr);

#ifdef CONFIG_LOGBUFFER
	logbuff_init_ptrs();
#endif
#ifdef CONFIG_POST
	post_output_backlog();
#endif

#ifdef CONFIG_AXXIA_ARM
	/* The Malloc area is immediately below the monitor copy in DRAM */
	malloc_start = CONFIG_SYS_MALLOC_BASE;
	mem_malloc_init (malloc_start, TOTAL_MALLOC_LEN);
#else
	/* The Malloc area is immediately below the monitor copy in DRAM */
	malloc_start = dest_addr - TOTAL_MALLOC_LEN;
	mem_malloc_init (malloc_start, TOTAL_MALLOC_LEN);
#endif

#ifdef CONFIG_ARCH_EARLY_INIT_R
	arch_early_init_r();
#endif
	power_init_board();

#if !defined(CONFIG_SYS_NO_FLASH)
	puts("Flash: ");

	flash_size = flash_init();
	if (flash_size > 0) {
# ifdef CONFIG_SYS_FLASH_CHECKSUM
		print_size(flash_size, "");
		/*
		 * Compute and print flash CRC if flashchecksum is set to 'y'
		 *
		 * NOTE: Maybe we should add some WATCHDOG_RESET()? XXX
		 */
		if (getenv_yesno("flashchecksum") == 1) {
			printf("  CRC: %08X", crc32(0,
				(const unsigned char *) CONFIG_SYS_FLASH_BASE,
				flash_size));
		}
		putc('\n');
# else	/* !CONFIG_SYS_FLASH_CHECKSUM */
		print_size(flash_size, "\n");
# endif /* CONFIG_SYS_FLASH_CHECKSUM */
	} else {
		puts(failed);
		hang();
	}
#endif

#if defined(CONFIG_CMD_NAND)
	puts("NAND:  ");
	nand_init();		/* go init the NAND */
#endif

#if defined(CONFIG_CMD_ONENAND)
	onenand_init();
#endif

#if 0
#ifdef CONFIG_GENERIC_MMC
	puts("MMC:   ");
	mmc_initialize(gd->bd);
#endif
#endif

#ifdef CONFIG_HAS_DATAFLASH
	AT91F_DataflashInit();
	dataflash_print_info();
#endif

	/* initialize environment */
	if (should_load_env())
		env_relocate();
	else
		set_default_env(NULL);

#if defined(CONFIG_CMD_PCI) || defined(CONFIG_PCI)
	arm_pci_init();
#endif

#ifndef CONFIG_AXXIA_ARM
	stdio_init();	/* get the devices list going. */
#endif

	jumptable_init();

#if defined(CONFIG_API)
	/* Initialize API */
	api_init();
#endif

#ifndef CONFIG_AXXIA_ARM
	console_init_r();	/* fully init console as a device */
#endif

#ifdef CONFIG_DISPLAY_BOARDINFO_LATE
# ifdef CONFIG_OF_CONTROL
	/* Put this here so it appears on the LCD, now it is ready */
	display_fdt_model(gd->fdt_blob);
# else
	checkboard();
# endif
#endif

#if defined(CONFIG_ARCH_MISC_INIT)
	/* miscellaneous arch dependent initialisations */
	arch_misc_init();
#endif
#if defined(CONFIG_MISC_INIT_R)
	/* miscellaneous platform dependent initialisations */
	misc_init_r();
#endif

	 /* set up exceptions */
	interrupt_init();
	/* enable exceptions */
	enable_interrupts();

	/* Initialize from environment */
	load_addr = getenv_ulong("loadaddr", 16, load_addr);

#ifdef CONFIG_BOARD_LATE_INIT
	board_late_init();
#endif

#ifdef CONFIG_BITBANGMII
	bb_miiphy_init();
#endif
#if defined(CONFIG_CMD_NET)
	puts("Net:   ");
	eth_initialize(gd->bd);
#if defined(CONFIG_RESET_PHY_R)
	debug("Reset Ethernet PHY\n");
	reset_phy();
#endif
#endif

#ifdef CONFIG_POST
	post_run(NULL, POST_RAM | post_bootmode_get(0));
#endif

#if defined(CONFIG_PRAM) || defined(CONFIG_LOGBUFFER)
	/*
	 * Export available size of memory for Linux,
	 * taking into account the protected RAM at top of memory
	 */
	{
		ulong pram = 0;
		uchar memsz[32];

#ifdef CONFIG_PRAM
		pram = getenv_ulong("pram", 10, CONFIG_PRAM);
#endif
#ifdef CONFIG_LOGBUFFER
#ifndef CONFIG_ALT_LB_ADDR
		/* Also take the logbuffer into account (pram is in kB) */
		pram += (LOGBUFF_LEN + LOGBUFF_OVERHEAD) / 1024;
#endif
#endif
		sprintf((char *)memsz, "%ldk", (gd->ram_size / 1024) - pram);
		setenv("mem", (char *)memsz);
	}
#endif

	/* main_loop() can return to retry autoboot, if so just run it again. */
	for (;;) {
		main_loop();
	}

	/* NOTREACHED - no way out of command loop except booting */
}

void hang(void)
{
	puts("### ERROR ### Please RESET the board ###\n");
	for (;;);
}
