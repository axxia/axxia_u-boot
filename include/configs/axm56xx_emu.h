/*
 * (C) Copyright 2013
 * LSI <www.lsi.com>
 * John Jacques <john.jacques@lsi.com>
 * Configuration settings for the LSI ACP development boards.
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

#ifndef __CONFIGS_AXXIA_56XX_EMU_H
#define __CONFIGS_AXXIA_56XX_EMU_H

/*#define CONFIG_AXXIA_56XX_EMU_V_1_0*/
#define CONFIG_AXXIA_56XX_EMU
#define CONFIG_AXXIA_EMU
#define ARM64

/*
  ==============================================================================
  ==============================================================================
  Constants
  ==============================================================================
  ==============================================================================
*/

#define CONFIG_BAUDRATE    9600


/********** FEMAC PHY ADDRESS *************/
#define CONFIG_AXXIA_PHY_ADDRESS 0x3


/* HACK: Define it until cache coherency is figured out */
/* #define USE_CACHE_SYNC */

/*
  ==============================================================================
  ==============================================================================
  Non-Volatile Storage
  ==============================================================================
  ==============================================================================
*/

#define CONFIG_AXXIA_SERIAL_FLASH /* Include support for SPI flash. */

#define CONFIG_AXXIA_SERIAL_FLASH_ENV
#define CONFIG_ENV_IS_IN_SPI_FLASH

#define CONFIG_PARAMETER_OFFSET          (512 * 1024)
#define CONFIG_PARAMETER_SIZE            (64 * 1024)
#define CONFIG_PARAMETER_RANGE           (64 * 1024)
#define CONFIG_PARAMETER_OFFSET_REDUND \
	(CONFIG_PARAMETER_OFFSET + CONFIG_PARAMETER_RANGE)
#define CONFIG_PARAMETER_SIZE_REDUND     CONFIG_PARAMETER_SIZE
#define CONFIG_PARAMETER_RANGE_REDUND    CONFIG_PARAMETER_RANGE

#define CONFIG_SYS_REDUNDAND_ENVIRONMENT
#define CONFIG_ENV_OFFSET \
	(CONFIG_PARAMETER_OFFSET_REDUND + CONFIG_PARAMETER_RANGE_REDUND)
#define CONFIG_ENV_SECT_SIZE             (64 * 1024)
#define CONFIG_ENV_SIZE                  (64 * 1024)
#define CONFIG_ENV_SECT_SIZE             (64 * 1024)
#define CONFIG_ENV_RANGE                 (64 * 1024)
#define CONFIG_ENV_OFFSET_REDUND         (CONFIG_ENV_OFFSET + CONFIG_ENV_RANGE)
#define CONFIG_ENV_SIZE_REDUND            CONFIG_ENV_SIZE
#define CONFIG_ENV_RANGE_REDUND           CONFIG_ENV_RANGE

#define CONFIG_UBOOT_OFFSET              (1 * 1024 * 1024)
#define CONFIG_UBOOT_SIZE                (2 * 1024 * 1024)
#define CONFIG_UBOOT_OFFSET_REDUND       (3 * 1024 * 1024)
#define CONFIG_UBOOT_SIZE_REDUND         CONFIG_UBOOT_SIZE

/*
  ==============================================================================
  ==============================================================================
  Features.
  ==============================================================================
  ==============================================================================
*/

#define CONFIG_REDUNDANT_UBOOT
#define CONFIG_REDUNDANT_UBOOT_AUTO

/*#define CONFIG_HW_WATCHDOG*/
/*#define LEAVE_WATCHDOG_ON*/
#define WATCHDOG_TIMEOUT_SECS 240

#define CONFIG_GICV3
#define GICD_BASE (0x8010000000)
#define GICR_BASE (0x8010200000)

#define CONFIG_BOOTP_ID_CACHE_SIZE 32

/*#define CONFIG_SYS_DCACHE_OFF*/

#define CONFIG_SYS_CNTR_FREQ 4000000

#define V_MIN   795
#define V_SAFE  940
#define V_MAX  1050

/*#define CONFIG_MEMORY_RETENTION*/

#define SSP_DEFAULT_CLOCK  1000000

#define CONFIG_AXXIA_MDIO
#define CONFIG_AXXIA_NEMAC
/*#define CONFIG_AXXIA_EIOA*/

#define CONFIG_BOOTDELAY 3

#define CONFIG_EXTRA_ENV_SETTINGS \
	"baudrate=9600\0" \
	"bootargs=console=ttyAMA0 mem=1024M ip=dhcp root=/dev/nfs rw\0" \
	"bootdelay=5\0" \
	"ethact=NEMAC\0" \
	"fdt_high=0x20000000\0" \
	"initrd_high=0x20000000\0" \
	"loadaddr=4000000\0" \
	"stderr=serial\0" \
	"stdin=serial\0" \
	"stdout=serial\0"

#define CONFIG_BOOTCOMMAND "setenv autoload ; dhcp ; bootm"

#include <configs/axm56xx_common.h>

#endif	/* __CONFIGS_AXXIA_56XX_EMU_H */
