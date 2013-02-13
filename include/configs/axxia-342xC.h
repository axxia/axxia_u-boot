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

#ifndef __CONFIGS_AXXIA_342XC_H
#define __CONFIGS_AXXIA_342XC_H

#define CONFIG_AXXIA_342X 1
#define CONFIG_AXXIA_P0   1

#define CONFIG_AXXIA_SERIAL
#define CONFIG_AXXIA_USB
#define CONFIG_AXXIA_PCI
#define CONFIG_AXXIA_NET
/*#define CONFIG_AXXIA_EIOA*/
#define CONFIG_AXXIA_FEMAC
#define CONFIG_AXXIA_NAND
#define CONFIG_AXXIA_SERIAL_FLASH
#define CONFIG_AXXIA_NAND_ENV

#include <configs/axxia-ppc.h>

#endif	/* __CONFIGS_AXXIA_342XC_H */
