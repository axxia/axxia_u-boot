/*
 * (C) Copyright 2013
 * LSI Corporation <www.lsi.com>
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

#ifndef __CONFIGS_AXXIA_H
#define __CONFIGS_AXXIA_H

#define CONFIG_AXXIA

#define CONFIG_AXXIA_SERIAL

/*
 */

#define CONFIG_LSI_NCR

/*
  ================================================================================
  ================================================================================
  Networking
  ================================================================================
  ================================================================================
*/

#ifndef CONFIG_SPL_BUILD

#define CONFIG_AXXIA_FEMAC
/*#define CONFIG_AXXIA_EIOA*/

#if defined(CONFIG_AXXIA_FEMAC) || defined(CONFIG_AXXIA_EIOA)
#define CONFIG_AXXIA_NET
#define CONFIG_CMD_NET
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_PING
#endif

#endif	/* CONFIG_SPL_BUILD */

/*
  ================================================================================
  ================================================================================
  SSP Access
  ================================================================================
  ================================================================================
*/

#define SSP_CR0       0x000
#define SSP_CR1       0x004
#define SSP_DR        0x008
#define SSP_SR        0x00c
#define SSP_CPSR      0x010
#define SSP_IMSC      0x014
#define SSP_RIS       0x018
#define SSP_MIS       0x01c
#define SSP_ICR       0x020
#define SSP_DMACR     0x024
#define SSP_CSR       0x030
#define SSP_PERIPHID0 0xfe0
#define SSP_PERIPHID1 0xfe4
#define SSP_PERIPHID2 0xfe8
#define SSP_PERIPHID3 0xfec
#define SSP_PCELLID0  0xff0
#define SSP_PCELLID1  0xff4
#define SSP_PCELLID2  0xff8
#define SSP_PCELLID3  0xffc

#define SSP_DEFAULT_CLOCK  1250000
#define SSP_MAXIMUM_CLOCK 25000000

#ifndef __ASSEMBLY__
int ssp_read(void *, unsigned long, unsigned long);
int ssp_write(void *, unsigned long, unsigned long, int);
int ssp_set_speed(unsigned long *);
int ssp_init(int, int);
#endif

/*
  ======================================================================
  ======================================================================
  Clocks
  ======================================================================
  ======================================================================
*/

#ifndef __ASSEMBLY__

#define CLK_REF0 125000000

typedef enum {
        clock_system, clock_core, clock_memory, clock_peripheral
} acp_clock_t;

int acp_clock_get(acp_clock_t, unsigned long *);

#endif /* __ASSEMBLY__ */

/*
  ================================================================================
  ================================================================================
  Include the Common LSI Header
  ================================================================================
  ================================================================================
*/

#include <configs/lsi.h>

#endif /* __CONFIGS_AXXIA_H */
