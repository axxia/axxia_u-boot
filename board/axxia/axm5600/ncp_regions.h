/*
*  Copyright (C) 2014 LSI (john.jacques@lsi.com)
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

#ifndef __NCP_REGIONS_H__
#define __NCP_REGIONS_H__

/* #include "ncp_dev_access.h" */
#include "ncp_nodes.h"

#if 0 /* UBOOT */
/* Includes for induvidual node regions.
* These files will define the targets within
* that node.
*/
#include "ncp_spp_regions.h"
#include "ncp_eioa_regions.h"
#include "ncp_timer_regions.h"
#include "ncp_pab_top_regions.h"
#include "ncp_mpp_regions.h"
#include "ncp_sed_regions.h"
/* #include "ncp_dpi_regions.h" */
#include "ncp_pic_regions.h"
#include "ncp_mtm_regions.h"
#include "ncp_mme_regions.h"
#include "ncp_mmb_regions.h"
#include "ncp_nca_regions.h"
#include "ncp_x1_pll_regions.h"
#include "ncp_syscon_clk_regions.h"


#define NCP_NODE_MASK             (0xFFFF)
#define NCP_TARGET_MASK           (0xFFFF)

#define NCP_MAX_NODE              (0xFFFF)
#define NCP_MAX_TARGET            (0xFFFF)
#define NCP_CFG_NODE_TARGET       (0xFF)

#define NCP_MAX_CONFIG_RING_NODE  (0xFF)

#define NCP_NODE_ID(regionId)    (((regionId) >> 16) & NCP_NODE_MASK)
#define NCP_TARGET_ID(regionId)  ((regionId) & NCP_TARGET_MASK)

#define NCP_REGION_ID(node, target) \
((ncp_region_id_t) \
((((node) & NCP_NODE_MASK) << 16) | ((target) & NCP_TARGET_MASK)))
#endif/* 0 UBOOT */

/* --------------------------------- */
/* --- NCP Region ID Definitions --- */
/* --------------------------------- */

/* Temporary dummy regions */
#define NCP_REGION_DUMMY_INDIRECT         (NCP_REGION_ID(0x0ff,  0))
#define NCP_REGION_DUMMY_DIRECT           (NCP_REGION_ID(0x0ff,  1))
#define NCP_REGION_DUMMY_INVALID          (NCP_REGION_ID(0x0ff,  2))

#define NCP_REGION_NULL                   (NCP_REGION_ID(0xffff, 0xffff))


#define NCP_REGION_NCA_COW_NU_TCLD           (NCP_REGION_ID(0x16,  0))
#define NCP_REGION_NCA_COW_NU_TIL            (NCP_REGION_ID(0x16,  1))
#define NCP_REGION_NCA_COW_NU_TDGL           (NCP_REGION_ID(0x16,  2))
#define NCP_REGION_NCA_COW_NU_TGL            (NCP_REGION_ID(0x16,  3))
#define NCP_REGION_NCA_COW_NU_MMB            (NCP_REGION_ID(0x16,  4))
#define NCP_REGION_NCA_COW_NU_CNAL           (NCP_REGION_ID(0x16,  5))
#define NCP_REGION_NCA_COW_NU_TCLS           (NCP_REGION_ID(0x16,  6))
#define NCP_REGION_NCA_CFG                   (NCP_REGION_ID(0x16,  0xff))

/* --- Hardware (RDL) defined Virtual Regions (0x100-0x1ff) --- */
/* Raw PCI express access */
#define NCP_REGION_PCIE0_BAR_0            (NCP_REGION_ID(0x100,  0)) /* 256.0 */
#define NCP_REGION_PCIE0_BAR_1            (NCP_REGION_ID(0x100,  1)) /* 256.1 */
#define NCP_REGION_PCIE0_BAR_2            (NCP_REGION_ID(0x100,  2)) /* 256.2 */
#define NCP_REGION_PCIE0_CONFIG           (NCP_REGION_ID(0x100,  3)) /* 256.3 */
#define NCP_REGION_PCIE0_PEI              (NCP_REGION_ID(0x100,  4)) /* 256.4 */
#define NCP_REGION_PCIE0_AXI_SLV          (NCP_REGION_ID(0x100,  5)) /* 256.5 */

/* AXI clients */
#define NCP_REGION_NCA_AXI                (NCP_REGION_ID(0x101,  0)) /* 257.0 */
#define NCP_REGION_NCA_COW_TIL            (NCP_REGION_ID(0x101,  1)) /* 257.1 */
#define NCP_REGION_NCA_COW_TDGL           (NCP_REGION_ID(0x101,  2)) /* 257.2 */
#define NCP_REGION_NCA_COW_TGL            (NCP_REGION_ID(0x101,  3)) /* 257.3 */
#define NCP_REGION_NCA_COW_CNAL           (NCP_REGION_ID(0x101,  5)) /* 257.5 */
#define NCP_REGION_NCA_COW_TCLS           (NCP_REGION_ID(0x101,  6)) /* 257.6 */

/* Raw SRIO access */
#define NCP_REGION_SRIO_PIO_WIN_0         (NCP_REGION_ID(0x102,  0)) /* 258.0 */
#define NCP_REGION_SRIO_PIO_WIN_1         (NCP_REGION_ID(0x102,  1)) /* 258.1 */
#define NCP_REGION_SRIO_PIO_WIN_2         (NCP_REGION_ID(0x102,  2)) /* 258.2 */
#define NCP_REGION_SRIO_PIO_WIN_3         (NCP_REGION_ID(0x102,  3)) /* 258.3 */
#define NCP_REGION_SRIO_PIO_WIN_4         (NCP_REGION_ID(0x102,  4)) /* 258.4 */
#define NCP_REGION_SRIO_PIO_WIN_5         (NCP_REGION_ID(0x102,  5)) /* 258.5 */
#define NCP_REGION_SRIO_PIO_WIN_6         (NCP_REGION_ID(0x102,  6)) /* 258.6 */
#define NCP_REGION_SRIO_PIO_WIN_7         (NCP_REGION_ID(0x102,  7)) /* 258.7 */
#define NCP_REGION_SRIO_PIO_WIN_8         (NCP_REGION_ID(0x102,  8)) /* 258.8 */
#define NCP_REGION_SRIO_PIO_WIN_9         (NCP_REGION_ID(0x102,  9)) /* 258.9 */
#define NCP_REGION_SRIO_PIO_WIN_10        (NCP_REGION_ID(0x102, 10)) /* 258.10*/
#define NCP_REGION_SRIO_PIO_WIN_11        (NCP_REGION_ID(0x102, 11)) /* 258.11*/
#define NCP_REGION_SRIO_PIO_WIN_12        (NCP_REGION_ID(0x102, 12)) /* 258.12*/
#define NCP_REGION_SRIO_PIO_WIN_13        (NCP_REGION_ID(0x102, 13)) /* 258.13*/
#define NCP_REGION_SRIO_PIO_WIN_14        (NCP_REGION_ID(0x102, 14)) /* 258.14*/
#define NCP_REGION_SRIO_PIO_WIN_15        (NCP_REGION_ID(0x102, 15)) /* 258.15*/

#define NCP_REGION_SRIO_PIO_WIN(n)        (NCP_REGION_ID(0x102, (n)))

#define NCP_REGION_SRIO_CFG_GRIO          (NCP_REGION_ID(0x102, 16))
#define NCP_REGION_SRIO_CFG_RAB           (NCP_REGION_ID(0x102, 17))

#define NCP_REGION_PKA                    (NCP_REGION_ID(0x103,  0)) /* 259.0 */
#define NCP_REGION_ROM                    (NCP_REGION_ID(0x104,  0)) /* 260.0 */

/* v2 has two additional PCI cores */
#define NCP_REGION_PCIE1_BAR_0            (NCP_REGION_ID(0x105,  0)) /* 261.0 */
#define NCP_REGION_PCIE1_BAR_1            (NCP_REGION_ID(0x105,  1)) /* 261.1 */
#define NCP_REGION_PCIE1_BAR_2            (NCP_REGION_ID(0x105,  2)) /* 261.2 */
#define NCP_REGION_PCIE1_CONFIG           (NCP_REGION_ID(0x105,  3)) /* 261.3 */
#define NCP_REGION_PCIE1_PEI              (NCP_REGION_ID(0x105,  4)) /* 261.4 */
#define NCP_REGION_PCIE1_AXI_SLV          (NCP_REGION_ID(0x105,  5)) /* 261.5 */

#define NCP_REGION_PCIE2_BAR_0            (NCP_REGION_ID(0x106,  0)) /* 262.0 */
#define NCP_REGION_PCIE2_BAR_1            (NCP_REGION_ID(0x106,  1)) /* 262.1 */
#define NCP_REGION_PCIE2_BAR_2            (NCP_REGION_ID(0x106,  2)) /* 262.2 */
#define NCP_REGION_PCIE2_CONFIG           (NCP_REGION_ID(0x106,  3)) /* 262.3 */
#define NCP_REGION_PCIE2_PEI              (NCP_REGION_ID(0x106,  4)) /* 262.4 */
#define NCP_REGION_PCIE2_AXI_SLV          (NCP_REGION_ID(0x106,  5)) /* 262.5 */

/* AXM55xx has an additional SRIO core */
#define NCP_REGION_SRIO1_PIO_WIN_0        (NCP_REGION_ID(0x107,  0)) /* 258.0 */
#define NCP_REGION_SRIO1_PIO_WIN_1        (NCP_REGION_ID(0x107,  1)) /* 258.1 */
#define NCP_REGION_SRIO1_PIO_WIN_2        (NCP_REGION_ID(0x107,  2)) /* 258.2 */
#define NCP_REGION_SRIO1_PIO_WIN_3        (NCP_REGION_ID(0x107,  3)) /* 258.3 */
#define NCP_REGION_SRIO1_PIO_WIN_4        (NCP_REGION_ID(0x107,  4)) /* 258.4 */
#define NCP_REGION_SRIO1_PIO_WIN_5        (NCP_REGION_ID(0x107,  5)) /* 258.5 */
#define NCP_REGION_SRIO1_PIO_WIN_6        (NCP_REGION_ID(0x107,  6)) /* 258.6 */
#define NCP_REGION_SRIO1_PIO_WIN_7        (NCP_REGION_ID(0x107,  7)) /* 258.7 */
#define NCP_REGION_SRIO1_PIO_WIN_8        (NCP_REGION_ID(0x107,  8)) /* 258.8 */
#define NCP_REGION_SRIO1_PIO_WIN_9        (NCP_REGION_ID(0x107,  9)) /* 258.9 */
#define NCP_REGION_SRIO1_PIO_WIN_10       (NCP_REGION_ID(0x107, 10)) /* 258.10*/
#define NCP_REGION_SRIO1_PIO_WIN_11       (NCP_REGION_ID(0x107, 11)) /* 258.11*/
#define NCP_REGION_SRIO1_PIO_WIN_12       (NCP_REGION_ID(0x107, 12)) /* 258.12*/
#define NCP_REGION_SRIO1_PIO_WIN_13       (NCP_REGION_ID(0x107, 13)) /* 258.13*/
#define NCP_REGION_SRIO1_PIO_WIN_14       (NCP_REGION_ID(0x107, 14)) /* 258.14*/
#define NCP_REGION_SRIO1_PIO_WIN_15       (NCP_REGION_ID(0x107, 15)) /* 258.15*/

#define NCP_REGION_SRIO1_PIO_WIN(n)       (NCP_REGION_ID(0x107, (n)))

#define NCP_REGION_SRIO1_CFG_GRIO         (NCP_REGION_ID(0x107, 16))
#define NCP_REGION_SRIO1_CFG_RAB          (NCP_REGION_ID(0x107, 17))


/* New AXM55xx FAS blocks */
#define NCP_REGION_LSM                    (NCP_REGION_ID(0x108,  0))
#define NCP_REGION_MME_CONF               (NCP_REGION_ID(0x109,  0))

#define NCP_REGION_PCI_SRIO_PHY           (NCP_REGION_ID(0x115,  0))

/* AHB clients */
#define NCP_REGION_NAND                   (NCP_REGION_ID(0x120,  0)) /* 288.0 */
#define NCP_REGION_TRNG                   (NCP_REGION_ID(0x121,  0)) /* 289.0 */
#define NCP_REGION_FEMAC                  (NCP_REGION_ID(0x122,  0)) /* 290.0 */
#define NCP_REGION_USB                    (NCP_REGION_ID(0x123,  0)) /* 291.0 */
#define NCP_REGION_GPDMA_0                (NCP_REGION_ID(0x124,  0)) /* 292.0 */
#define NCP_REGION_GPDMA_1                (NCP_REGION_ID(0x125,  0)) /* 293.0 */
#define NCP_REGION_M3SS                   (NCP_REGION_ID(0x126,  0)) /* 294.0 */

/* APB clients */
#define NCP_REGION_GPIO_0                 (NCP_REGION_ID(0x140,  0)) /* 320.0 */
#define NCP_REGION_GPIO_1                 (NCP_REGION_ID(0x141,  0)) /* 321.0 */
#define NCP_REGION_SSP                    (NCP_REGION_ID(0x142,  0)) /* 322.0 */
#define NCP_REGION_I2C                    (NCP_REGION_ID(0x143,  0)) /* 323.0 */
#define NCP_REGION_UART_0                 (NCP_REGION_ID(0x144,  0)) /* 324.0 */
#define NCP_REGION_UART_1                 (NCP_REGION_ID(0x145,  0)) /* 325.0 */
#define NCP_REGION_TIMER                  (NCP_REGION_ID(0x146,  0)) /* 326.0 */
#define NCP_REGION_MDIO                   (NCP_REGION_ID(0x147,  0)) /* 327.0 */
#define NCP_REGION_APB2RC                 (NCP_REGION_ID(0x148,  0)) /* 328.0 */
#define NCP_REGION_GPREG                  (NCP_REGION_ID(0x149,  0)) /* 329.0 */
#define NCP_REGION_SRIO_CONF              (NCP_REGION_ID(0x14a,  0)) /* 330.0 */
#define NCP_REGION_PL301                  (NCP_REGION_ID(0x14b,  0)) /* 331.0 */
#define NCP_REGION_I2C_1                  (NCP_REGION_ID(0x14c,  0)) /* 332.0 */
#define NCP_REGION_UART_2                 (NCP_REGION_ID(0x14d,  0)) /* 333.0 */

/* AXM55xx */
#define NCP_REGION_XVRC                   (NCP_REGION_ID(0x14e,  0)) /* 334.0 */
#define NCP_REGION_SSP_1                  (NCP_REGION_ID(0x14f,  0)) /* 335.0 */
#define NCP_REGION_SPF                    (NCP_REGION_ID(0x150,  0)) /* 336.0 */
#define NCP_REGION_SRIO_1_CONF            (NCP_REGION_ID(0x151,  0)) /* 330.0 */
#define NCP_REGION_I2C_2                  (NCP_REGION_ID(0x152,  0)) /* 338.0 */

/* 0x153-0x155 : TODO : all the APB2SER blocks */
#define NCP_REGION_APB2SER_PHY            (NCP_REGION_ID(0x153,  0))
#define NCP_REGION_APB2SER_CPM            (NCP_REGION_ID(0x154,  0))
#define NCP_REGION_APB2SER_CLK            (NCP_REGION_ID(0x155,  0))
#define NCP_REGION_X7_NRCP                (NCP_REGION_ID(0x155,  10))/* 341.10 */
#define NCP_REGION_SYSCON                 (NCP_REGION_ID(0x156,  0)) /* */
#define NCP_REGION_X7_ECM                 (NCP_REGION_ID(0x156,  1)) /* */
#define NCP_REGION_IPI                    (NCP_REGION_ID(0x157,  0)) /* 343.0 */
#define NCP_REGION_ELM_0                  (NCP_REGION_ID(0x158,  0)) /* 344.0 */
#define NCP_REGION_ELM_1                  (NCP_REGION_ID(0x159,  0)) /* 345.0 */
#define NCP_REGION_UART_3                 (NCP_REGION_ID(0x15a,  0)) /* 346.0 */
#define NCP_REGION_PL301_1                (NCP_REGION_ID(0x15b,  0)) /* 347.0 */
#define NCP_REGION_SMB                    (NCP_REGION_ID(0x15c,  0)) /* 348.0 */
#define NCP_REGION_MTC                    (NCP_REGION_ID(0x15d,  0)) /* 349.0 */

/*
* NOTICE! Targets for GIC-C and GIC-D are different
* between AXIS and Seahawk GICs!
*/
#define NCP_REGION_AXIS_GIC_CPU           (NCP_REGION_ID(0x160,  0)) /* 352.0 */
#define NCP_REGION_AXIS_GIC_DIST          (NCP_REGION_ID(0x160,  1)) /* 352.1 */

#define NCP_REGION_SEAHAWK_GIC_DIST       (NCP_REGION_ID(0x161,  1)) /* 353.1 */
#define NCP_REGION_SEAHAWK_GIC_CPU        (NCP_REGION_ID(0x161,  2)) /* 353.0 */
#define NCP_REGION_SEAHAWK_GIC_VIRT_CTRL  (NCP_REGION_ID(0x161,  4)) /* 353.2 */
#define NCP_REGION_SEAHAWK_GIC_VIRT_CPU   (NCP_REGION_ID(0x161,  6)) /* 353.3 */


/* DCR clients */
#define NCP_REGION_DCR_ARB                (NCP_REGION_ID(0x180,  0)) /* 384.0 */
#define NCP_REGION_PLB6_ARB               (NCP_REGION_ID(0x181,  0)) /* 385.0 */
#define NCP_REGION_TVSENSE                (NCP_REGION_ID(0x182,  0)) /* 386.0 */
#define NCP_REGION_L2_0                   (NCP_REGION_ID(0x183,  0)) /* 387.0 */
#define NCP_REGION_L2_0_INDIRECT          (NCP_REGION_ID(0x183,  1)) /* 387.1 */
#define NCP_REGION_L2_0_PMU               (NCP_REGION_ID(0x183,  2)) /* 387.2 */
#define NCP_REGION_L2_1                   (NCP_REGION_ID(0x184,  0)) /* 388.0 */
#define NCP_REGION_L2_1_INDIRECT          (NCP_REGION_ID(0x184,  1)) /* 388.1 */
#define NCP_REGION_L2_1_PMU               (NCP_REGION_ID(0x184,  2)) /* 388.2 */
#define NCP_REGION_L2_2                   (NCP_REGION_ID(0x185,  0)) /* 389.0 */
#define NCP_REGION_L2_2_INDIRECT          (NCP_REGION_ID(0x185,  1)) /* 389.1 */
#define NCP_REGION_L2_2_PMU               (NCP_REGION_ID(0x185,  2)) /* 389.2 */
#define NCP_REGION_L2_3                   (NCP_REGION_ID(0x186,  0)) /* 390.0 */
#define NCP_REGION_L2_3_INDIRECT          (NCP_REGION_ID(0x186,  1)) /* 390.1 */
#define NCP_REGION_L2_3_PMU               (NCP_REGION_ID(0x186,  2)) /* 390.2 */
#define NCP_REGION_PPC_ITRACE             (NCP_REGION_ID(0x187,  0)) /* 391.0 */
#define NCP_REGION_PPC_ITRACE_INDIRECT    (NCP_REGION_ID(0x187,  1)) /* 391.1 */
#define NCP_REGION_L2_0_TRACE             (NCP_REGION_ID(0x188,  0)) /* 392.0 */
#define NCP_REGION_L2_0_TRACE_INDIRECT    (NCP_REGION_ID(0x188,  1)) /* 392.1 */
#define NCP_REGION_L2_1_TRACE             (NCP_REGION_ID(0x189,  0)) /* 393.0 */
#define NCP_REGION_L2_1_TRACE_INDIRECT    (NCP_REGION_ID(0x189,  1)) /* 393.1 */
#define NCP_REGION_L2_2_TRACE             (NCP_REGION_ID(0x18a,  0)) /* 394.0 */
#define NCP_REGION_L2_2_TRACE_INDIRECT    (NCP_REGION_ID(0x18a,  1)) /* 394.1 */
#define NCP_REGION_L2_3_TRACE             (NCP_REGION_ID(0x18b,  0)) /* 395.0 */
#define NCP_REGION_L2_3_TRACE_INDIRECT    (NCP_REGION_ID(0x18b,  1)) /* 395.1 */
#define NCP_REGION_LAM_TRACE              (NCP_REGION_ID(0x18c,  0)) /* 396.0 */
#define NCP_REGION_LAM_TRACE_INDIRECT     (NCP_REGION_ID(0x18c,  1)) /* 396.1 */
#define NCP_REGION_CLK_CTRL               (NCP_REGION_ID(0x18d,  0)) /* 397.0 */
#define NCP_REGION_RESET_CTRL             (NCP_REGION_ID(0x18e,  0)) /* 398.0 */
/* 25xx uses new names for clk and reset */
#define NCP_REGION_SYSCON_CLK             (NCP_REGION_ID(0x18d,  0)) /* 397.0 */
#define NCP_REGION_SYSCON_RST             (NCP_REGION_ID(0x18e,  0)) /* 398.0 */
#define NCP_REGION_NHA                    (NCP_REGION_ID(0x18f,  0)) /* 399.0 */
#define NCP_REGION_P2A                    (NCP_REGION_ID(0x190,  0)) /* 400.0 */
#define NCP_REGION_A2P                    (NCP_REGION_ID(0x191,  0)) /* 401.0 */
#define NCP_REGION_MPIC_1                 (NCP_REGION_ID(0x192,  0)) /* 402.0 */
#define NCP_REGION_MPIC_0                 (NCP_REGION_ID(0x193,  0)) /* 403.0 */
#define NCP_REGION_LAM_MUX_CTRL           (NCP_REGION_ID(0x194,  0)) /* 404.0 */
/* new DCR regions for ACP2500 */
#define NCP_REGION_ECM                    (NCP_REGION_ID(0x195,  0)) /* 405.0 */
#define NCP_REGION_NRCP                   (NCP_REGION_ID(0x196,  0)) /* 406.0 */
#define NCP_REGION_MISC                   (NCP_REGION_ID(0x197,  0)) /* 407.0 */

/* PLB6 client */
#define NCP_REGION_LCM                    (NCP_REGION_ID(0x1a0,  0)) /* 416.0 */

/* ACP25xx targets */
#define NCP_REGION_SBB                    (NCP_REGION_ID(0x1b0,  0)) /* 432.0 */
#define NCP_REGION_MSD                    (NCP_REGION_ID(0x1c0,  0)) /* 448.0 */
#define NCP_REGION_SCB                    (NCP_REGION_ID(0x1d0,  0)) /* 464.0 */
#define NCP_REGION_APB2SER                (NCP_REGION_ID(0x1d1,  0)) /* 465.0 */
#define NCP_REGION_TZC380                 (NCP_REGION_ID(0x1d2,  0)) /* 466.0 */
#define NCP_REGION_LBI                    (NCP_REGION_ID(0x1d3,  0)) /* 467.0 */
#define NCP_REGION_TZC380_1               (NCP_REGION_ID(0x1d4,  0)) /* 468.0 */

/* AXM55xx targets */
#define NCP_REGION_DICKENS(n)             (NCP_REGION_ID(0x1e0, n))  /* 480.n */
#define NCP_REGION_CORESIGHT(n)           (NCP_REGION_ID(0x1e1, n))  /* 481.n */


/* --- Software Defined Virtual Regions (0x200-0x2ff) --- */

/* System memory interfaces */
#define NCP_REGION_NCA_CR_SYSMEM          (NCP_REGION_ID(0x200,  0)) /* 512.0 */
#define NCP_REGION_NCA_NIC_SYSMEM         (NCP_REGION_ID(0x200,  1)) /* 512.1 */
#define NCP_REGION_AXI_PLB_SYSMEM         (NCP_REGION_ID(0x200,  2)) /* 512.2 */
#define NCP_REGION_AXI_PLB_SYSMEM_LE      (NCP_REGION_ID(0x200,  3)) /* 512.3 */

#define NCP_REGION_NCA_DMA_MEM_LE         (NCP_REGION_ID(0x201,  0))
#define NCP_REGION_NCA_DMA_MEM_BE         (NCP_REGION_ID(0x201,  1))

#define NCP_REGION_NCA_TASK_MEM_LE        (NCP_REGION_ID(0x202,  0))
#define NCP_REGION_NCA_TASK_MEM_BE        (NCP_REGION_ID(0x202,  1))

/* Embedded Planet MPC8641D SRIO controller access */
#define NCP_REGION_MPC_RIO_ENDPOINT       (NCP_REGION_ID(0x203,  0))
#define NCP_REGION_MPC_RIO_MSG_UNIT       (NCP_REGION_ID(0x203,  1))

/* Local Host Memory access */
#define NCP_REGION_HOSTMEM_LE             (NCP_REGION_ID(0x204,  0))
#define NCP_REGION_HOSTMEM_BE             (NCP_REGION_ID(0x204,  1))


/* ACP5500 Memory Pool Vindex/Vaddr access */
#define NCP_REGION_SYSMEM_POOL_VINDEX(n)  (NCP_REGION_ID(0x206,  n))
#define NCP_REGION_SYSMEM_POOL_VADDR(n)   (NCP_REGION_ID(0x207,  n))

#ifdef NCP_PLX
/* PLX PEX8608 PCIE switch controller access */
#define NCP_REGION_PCIE_PLX		  (NCP_REGION_ID(0x204,  0))
#endif

/* --- I2C Protocol Virtual Regions, Device 0 (0x210, 0-255) --- */
#define NCP_REGION_I2C_PROTOCOL(n)         (NCP_REGION_ID(NCP_NODE_I2C_PROTOCOL,  n))

/* --- I2C Protocol Virtual Regions, Device 1 (0x211, 0-255) --- */
/*     ACP25xx has two I2C controllers                           */
#define NCP_REGION_I2C_1_PROTOCOL(n)       (NCP_REGION_ID(NCP_NODE_I2C_1_PROTOCOL,  n))

/* --- I2C Protocol Virtual Regions, Device 2 (0x212, 0-255) --- */
/*     AXM55xx has three I2C controllers                         */
#define NCP_REGION_I2C_2_PROTOCOL(n)       (NCP_REGION_ID(NCP_NODE_I2C_2_PROTOCOL,  n))

/* --- SMB/I2C Protocol Virtual Regions, Device 0 (0x218, 0-255) --- */
/*     AXM55xx has one SMB/I2C controllers                           */
#define NCP_REGION_SMB_0_PROTOCOL(n)       (NCP_REGION_ID(NCP_NODE_SMB_0_PROTOCOL,  n))

/* --- LBI external device Virtual Regions (0x220, 0-15) --- */
#define NCP_REGION_LBI_DEVICE(n)           (NCP_REGION_ID(0x220,  n))

/* --- Other Assorted Virtual Regions (0x300-0x3ff) --- */

#define NCP_REGION_SIMULATOR_IF            (NCP_REGION_ID(0x300,  0))
#define NCP_REGION_DRIVER_CFG              (NCP_REGION_ID(0x301,  0))

/* --- Virtual MDIO - PHY reg R/W  clause 22 --- */
#define NCP_REGION_C22_MDIO_PHY(n)         (NCP_REGION_ID(0x302,  n))

/* --- Virtual MDIO - PHY reg R/W  clause 45 --- */
#define NCP_REGION_C45_MDIO_PHY(n)         (NCP_REGION_ID(0x303,  n))

/* --- Virtual MDIO - PHY adr R/W  clause 45 --- */
#define NCP_REGION_C45_MDIO_ADR(n)        (NCP_REGION_ID(0x304,  n))

#endif/* __NCP_REGIONS_H__ */
