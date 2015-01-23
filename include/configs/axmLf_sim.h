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

#ifndef __CONFIGS_AXXIA_LF_SIM_H
#define __CONFIGS_AXXIA_LF_SIM_H

/*#define CONFIG_AXXIA_LF_SIM_V_1_0*/
#define CONFIG_AXXIA_LF_SIM
#define CONFIG_AXXIA_SIM
#define ARM64

#define CONFIG_AXXIA_AXM_I2C

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
#define CONFIG_ENV_IS_NOWHERE

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

#define CONFIG_EXTRA_ENV_SETTINGS		\
	"loadaddr=0x80100000\0"			\
	"kernel_addr=0x100000\0"		\
	"ramdisk_addr=0x800000\0"		\
	"ramdisk_size=0x2000000\0"		\
	"fdt_high=0xffffffffffffffff\0"		\
	"initrd_high=0xffffffffffffffff\0"	\
	"kernel_start=0x581200000\0"		\
	"kernel_load=0x806f0000\0"		\
	"kernel_size=0x1000000\0"		\
	"console=ttyAMA0,115200n8\0"

#define CONFIG_BOOTARGS		"root=/dev/vda1 console=ttyAMA0,115200 " \
				"earlycon=pl011,0x8080000000 " \
				"mem=2G"
#define CONFIG_BOOTCOMMAND	"bootm 4010000 - 4000000"
#define CONFIG_BOOTDELAY	3

#define V_MIN   795
#define V_SAFE  940
#define V_MAX  1050

/*#define CONFIG_MEMORY_RETENTION*/

#define SSP_DEFAULT_CLOCK  1000000

#define CONFIG_AXXIA_PCI
#define CONFIG_SPL_PCI_SUPPORT


/*#define CONFIG_AXXIA_FEMAC*/
/*#define CONFIG_AXXIA_EIOA*/

#include <configs/axmLf_common.h>

#endif	/* __CONFIGS_AXXIA_LF_SIM_H */
