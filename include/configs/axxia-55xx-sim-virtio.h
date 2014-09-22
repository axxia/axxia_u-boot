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

#ifndef __CONFIGS_AXXIA_55XX_SIM_H
#define __CONFIGS_AXXIA_55XX_SIM_H

#define CONFIG_AXXIA_55XX_SIM_VIRTIO
#define CONFIG_AXXIA_55XX_SIM
#define CONFIG_AXXIA_SIM

/*
  ===============================================================================
  ===============================================================================
  Constants
  ===============================================================================
  ===============================================================================
*/

#define CONFIG_BAUDRATE    9600


/********** FEMAC PHY ADDRESS *************/
#define CONFIG_AXXIA_PHY_ADDRESS 0x3


/* HACK: Define it until cache coherency is figured out */
/* #define USE_CACHE_SYNC */

/*
  ==============================================================================
  ==============================================================================
  Features.
  ==============================================================================
  ==============================================================================
*/

#define V_MIN   795
#define V_SAFE  940
#define V_MAX  1050

#define SSP_DEFAULT_CLOCK  1000000

#define CONFIG_ENV_IS_NOWHERE
#define CONFIG_ENV_OFFSET    0x80000
#define CONFIG_ENV_SIZE      0x20000
#define CONFIG_ENV_SECT_SIZE 0x20000

#define CONFIG_BOOTDELAY 0
#define CONFIG_BOOTCOMMAND \
  "setenv fdt_high 0xffffffff ; setenv bootargs console=ttyAMA root=/dev/vda rootwait mem=1024M ; bootm 4010000 - 4000000\0"

#include <configs/axxia-arm.h>

#endif	/* __CONFIGS_AXXIA_55XX_SIM_VIRTIO_H */
