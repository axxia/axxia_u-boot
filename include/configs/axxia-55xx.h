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

#ifndef __CONFIGS_AXXIA_55XX_H
#define __CONFIGS_AXXIA_55XX_H

#define CONFIG_AXXIA_55XX

/*
  ==============================================================================
  ==============================================================================
  Constants
  ==============================================================================
  ==============================================================================
*/

#define DEFAULT_SDCR_VALUE 0x00080a02
#define CONFIG_BAUDRATE    9600

/********** FEMAC PHY ADDRESS *************/
#define CONFIG_AXXIA_PHY_ADDRESS 0x1e

#define CONFIG_LSI_CLOCKS

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

#define CONFIG_PARAMETER_OFFSET          (256 * 1024)
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

/*
  Switch to normal mode on v1.0 silicon.  Note that v1.0 silicon does
  not fully support normal mode.  Linux boots, but coherent IO is not
  possible.
*/

/*#define AXXIA_FORCE_NORMAL_MODE*/

/*
  Switch to secure mode on v1.1 silicon.
*/

/*#define AXXIA_FORCE_SECURE_MODE*/

/*
  OR in the fuse force register's pv and cnpv fields when initializing
  pfuse.
*/

#define AXXIA_OR_IN_FUSE_FORCE

/*
  Start the secondary cores in U-Boot.

  This is a work-around required if using Linux releases before
  8.8.1.21 It only applies in NORMAL mode.  It is NOT required for
  Linux 3.4 (7.8.x.x).
*/

/*#define AXXIA_START_SECONDARY_CORES*/

#define CONFIG_HW_WATCHDOG
/*#define LEAVE_WATCHDOG_ON*/
#define CONFIG_REDUNDANT_PARAMETERS
#define CONFIG_REDUNDANT_UBOOT

/*
  In the Linux boot/compressed code, there is no obvious way to flush
  the L3 cache.  That being the case, define the following to leave
  the L3 disabled.  It will be re-enabled during the Linux boot in
  recent versions of Axxia Linux.
*/
#define LEAVE_L3_OFF

#define V_MIN   795
#define V_SAFE  940
#define V_MAX  1050

#define CONFIG_MEMORY_RETENTION

#define CONFIG_LSI_SBB

#define SSP_DEFAULT_CLOCK  4000000

#define CONFIG_AXXIA_PCI
#define CONFIG_SPL_PCI_SUPPORT

#define CONFIG_AXXIA_FEMAC
#define CONFIG_AXXIA_EIOA
#define CONFIG_SPL

#define CONFIG_BOOTDELAY 3

#define CONFIG_EXTRA_ENV_SETTINGS \
	"loadaddr=0x82000000\0" \
	"console=ttyO2,115200n8\0" \
	"usbtty=cdc_acm\0" \
	"vram=16M\0" \
	"mmcdev=0\0" \
	"mmcroot=/dev/mmcblk0p2 rw\0" \
	"mmcrootfstype=ext3 rootwait\0" \
	"mmcargs=setenv bootargs console=${console} " \
		"vram=${vram} " \
		"root=${mmcroot} " \
		"rootfstype=${mmcrootfstype}\0" \
	"loadbootscript=fatload mmc ${mmcdev} ${loadaddr} boot.scr\0" \
	"bootscript=echo Running bootscript from mmc${mmcdev} ...; " \
		"source ${loadaddr}\0" \
	"loaduimage=fatload mmc ${mmcdev} ${loadaddr} uImage\0" \
	"mmcboot=echo Booting from mmc${mmcdev} ...; " \
		"run mmcargs; " \
		"bootm ${loadaddr}\0" \

#define CONFIG_BOOTCOMMAND \
	"mmc dev ${mmcdev}; if mmc rescan; then " \
		"if run loadbootscript; then " \
			"run bootscript; " \
		"else " \
			"if run loaduimage; then " \
				"run mmcboot; " \
			"fi; " \
		"fi; " \
	"fi"

#include <configs/axxia-arm.h>

#endif	/* __CONFIGS_AXXIA_55XX_H */
