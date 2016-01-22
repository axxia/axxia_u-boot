/*
 *  Copyright (C) 2016 Intel (john.jacques@intel.com)
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

#ifndef _NCP_CMEM_CFG_REG_DEFINES_H_
#define _NCP_CMEM_CFG_REG_DEFINES_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __UBOOT__
#include "ncp_sal_types.h"
#endif


    /* NODE 0x8 , TARGET 0xb*/


#define     NCP_CMEM_CFG_DDR_CFG                                (0x00000000)
#define     NCP_CMEM_CFG_DUPLICATION_CFG                        (0x00000004)
#define     NCP_CMEM_CFG_DDR_CTL                                (0x00000008)
#define     NCP_CMEM_CFG_AXI_CTL                                (0x0000000c)
#define     NCP_CMEM_CFG_USER_SCRUB_ADDR                        (0x00000080)
#define     NCP_CMEM_CFG_MAX_SCRUB_ADDR                         (0x00000084)
#define     NCP_CMEM_CFG_SCRUB_CFG                              (0x00000088)
#define     NCP_CMEM_CFG_CMD_FIFO_STATUS                        (0x00000090)
#define     NCP_CMEM_CFG_DATA_FIFO_STATUS                       (0x00000094)
#define     NCP_CMEM_CFG_WR_STATUS                              (0x00000098)
#define     NCP_CMEM_CFG_DDRMC_INFO                             (0x0000009c)
#define     NCP_CMEM_CFG_EDG_IRQ_STAT                           (0x00000110)
#define     NCP_CMEM_CFG_EDG_IRQ_MASK                           (0x00000114)
#define     NCP_CMEM_CFG_EDG_IRQ_INV                            (0x00000118)
#define     NCP_CMEM_CFG_EDG_IRQ_NOMASK                         (0x0000011c)
#define     NCP_CMEM_CFG_EDG_IRQ_RAW                            (0x00000120)
#ifdef __cplusplus
}
#endif

#endif /* _NCP_CMEM_CFG_REG_DEFINES_H_ */
