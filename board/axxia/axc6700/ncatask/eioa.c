/*
 *  Copyright (C) 2011 LSI Corporation
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <malloc.h>
#include <net.h>
#include <miiphy.h>
#include <asm/io.h> /*writel, readl*/

DECLARE_GLOBAL_DATA_PTR;

/* task NCAv3 */
#include "uboot/ncp_task_basetypes.h"
#include "uboot/ncp_task_pvt.h"      
#include "uboot/ncp_mme_ext.h"       
#include "ncp_task_basetypes.h"
#include "ncp_timer_regions.h"
#include "ncp_tmgr_system_count_reg_defines.h"
#include "ncp_axis_apb2ser3_regions.h" /* syscon */
#include "ncp_syscon_xlf_reg_defines.h" /* syscon */
#include "ncp_ncap_reg_defines.h" /* eg. NCP_NCAP_CONFIG_INIT */
#include "ncp_cmn_axi_reg_defines.h" /* eg. NCP_CMN_AXI_CFG_RING_ACK_TIMER_CNT */

/*==============================================================================
  ==============================================================================
  Private Interface
  ==============================================================================
  ==============================================================================
*/

static int initialized = 0;
static int loopback = 0;
static int rxtest = 0;
static ncp_task_tqs_hdl_t tqsHdl = NULL;
static ncp_hdl_t ncpHdl = NULL;

#define ALL_TRACES
#define SNAPSHOT /*define if you want a snapshot*/
/*#define PHY*/ /*We don't have ext. PHYs on a Waco */

#define NCP_EIOA_GEN_CFG_REG_OFFSET(portIndex)                                  \
    0x100000 +                                                                  \
    ((portIndex > 0) ? 0x10000 : 0) +                                           \
    ((portIndex > 0) ? (0x1000 * (portIndex)) : 0)

/* Native domain is up to 10 gmacs, they are numbered
 * 0-4 and 15-20. Nokia is gmac20 */
int phy_by_index[21] = 
{ 
    0x12, 0x13, 0x18, 0x19, 0x1a, /* EIOA0 */
	0x0, 0x0, 0x0, 0x0, 0x0, /* don't exist */
	0x0, 0x0, 0x0, 0x0, 0x0, /* don't exist */
	0x0, /* do not exist */
	0x1, 0x17, 0x1b, 0x2, 0x3 /* EIOA1 */
};


typedef enum {
	NCR_COMMAND_NULL,
	NCR_COMMAND_WRITE,
	NCR_COMMAND_WRITE64,
	NCR_COMMAND_READ,
	NCR_COMMAND_MODIFY,
	NCR_COMMAND_USLEEP,
	NCR_COMMAND_POLL,
} ncr_command_code_t;

typedef struct {
	ncr_command_code_t command;
	unsigned region;
	unsigned offset;
	unsigned value;
	unsigned mask;
} ncr_command_t;

static int
ncp_dev_configure(ncr_command_t *commands);

/* ncp_dev_reset */


ncp_uint32_t
ncp_caal_regions_xlf[] =
{
    NCP_REGION_ID(0x0b, 0x05),      /* SPPV2   */
    NCP_REGION_ID(0x0c, 0x05),      /* SED     */
    NCP_REGION_ID(0x0e, 0x05),      /* DPI_HFA */
    NCP_REGION_ID(0x14, 0x05),      /* MTM     */
    NCP_REGION_ID(0x14, 0x0a),      /* MTM2    */
    NCP_REGION_ID(0x15, 0x00),      /* MME     */
    NCP_REGION_ID(0x16, 0x05),      /* NCAV3   */
    NCP_REGION_ID(0x16, 0x10),      /* NCAV32  */
    NCP_REGION_ID(0x17, 0x05),      /* EIOAM   */
    NCP_REGION_ID(0x19, 0x05),      /* TMGR    */
    NCP_REGION_ID(0x1a, 0x05),      /* MPPY    */
    NCP_REGION_ID(0x1a, 0x23),      /* MPPY2   */
    NCP_REGION_ID(0x1a, 0x21),      /* MPPY3   */
    NCP_REGION_ID(0x1b, 0x05),      /* PIC     */
    NCP_REGION_ID(0x1c, 0x05),      /* PAB     */
    NCP_REGION_ID(0x1f, 0x05),      /* EIOAMH  */
    NCP_REGION_ID(0x31, 0x05),      /* ISB     */
    NCP_REGION_ID(0x3e, 0x05),      /* DEC     */
    NCP_REGION_ID(0x40, 0x05),      /* ERIF0   */
    NCP_REGION_ID(0x41, 0x05),      /* ERIF0   */
    NCP_REGION_ID(0x44, 0x05),      /* RIF0    */
    NCP_REGION_ID(0x45, 0x05),      /* RIF0    */
    NCP_REGION_ID(0xff, 0xff)
};

ncp_uint32_t
ncp_cnal_regions_xlf[] =
{
    NCP_REGION_ID(0x28, 0x06),      /* EIOASM0 */
    NCP_REGION_ID(0x28, 0x07),      /* EIOASM0 */
    NCP_REGION_ID(0x29, 0x06),      /* EIOASM1 */
    NCP_REGION_ID(0x29, 0x07),      /* EIOASM1 */
    NCP_REGION_ID(0x2a, 0x06),      /* EIOAS2  */
    NCP_REGION_ID(0x2a, 0x07),      /* EIOAS2  */
    NCP_REGION_ID(0x2b, 0x06),      /* EIOAS3  */
    NCP_REGION_ID(0x2b, 0x07),      /* EIOAS3  */
    NCP_REGION_ID(0x32, 0x06),      /* ISBV2s0 */
    NCP_REGION_ID(0x32, 0x07),      /* ISBV2s0 */
    NCP_REGION_ID(0x35, 0x06),      /* ISBV2s1 */
    NCP_REGION_ID(0x35, 0x07),      /* ISBV2s1 */
    NCP_REGION_ID(0xff, 0xff)
};


/*
  ------------------------------------------------------------------------------
  ncp_dev_reset
*/

static ncp_st_t
ncp_dev_quiesce(void)
{
    ncp_st_t         ncpStatus = NCP_ST_SUCCESS;
    ncp_uint32_t    *pCnalRegions = ncp_cnal_regions_xlf;
    ncp_uint32_t    *pCaalRegions = ncp_caal_regions_xlf;
    ncp_uint32_t    *pRegion;
    ncp_uint32_t     ort, owt;
    ncp_uint32_t     buf = 0;
    ncp_uint32_t     loop;

    pRegion = pCnalRegions;
    while (*pRegion != NCP_REGION_ID(0xff, 0xff) )
    {

        /* set read/write transaction limits to zero */
        NCP_CALL(ncr_write32(*pRegion, 0x8, buf));
        NCP_CALL(ncr_write32(*pRegion, 0xc, buf));
        pRegion++;
    }

    pRegion = pCaalRegions;
    while (*pRegion != NCP_REGION_ID(0xff, 0xff) )
    {

        /* set read/write transaction limits to zero */
        NCP_CALL(ncr_write32(*pRegion, 0x8, buf));
        NCP_CALL(ncr_write32(*pRegion, 0xc, buf));
        pRegion++;
    }


    pRegion = pCaalRegions;
    loop = 0;
    while (*pRegion != NCP_REGION_ID(0xff, 0xff) )
    {
        /* read the number of outstanding read/write transactions */
        NCP_CALL(ncr_read32(*pRegion, 0xf8, &ort));
        NCP_CALL(ncr_read32(*pRegion, 0xfc, &owt));

        if ( (ort == 0) && (owt == 0) )
        {
            /* this engine has been quiesced, move on to the next */
            loop = 0;
            pRegion++;
        }
        else 
        {
            if (loop++ > 10000) {
                NCP_MSG(NCP_MSG_ERROR, "unable to quiesce region 0x%02x.0x%02x! \n",
                        NCP_NODE_ID(*pRegion), NCP_TARGET_ID(*pRegion));
                loop = 0;
                continue;
            }
        }
    }

    pRegion = pCnalRegions;
    loop = 0;
    while (*pRegion != NCP_REGION_ID(0xff, 0xff) )
    {
        /* read the number of outstanding read/write transactions */
        NCP_CALL(ncr_read32(*pRegion, 0x1c0, &ort));
        NCP_CALL(ncr_read32(*pRegion, 0x1c4, &owt));

        if ( (ort == 0) && (owt == 0) )
        {
            /* this engine has been quiesced, move on to the next */
            loop = 0;
            pRegion++;
        }
        else 
        {
            if (loop++ > 10000) {
                NCP_MSG(NCP_MSG_ERROR, "unable to quiesce region 0x%02x.0x%02x! \n",
                        NCP_NODE_ID(*pRegion), NCP_TARGET_ID(*pRegion));
                loop = 0;
                continue;
            }
        }
    }


NCP_RETURN_LABEL
    return ncpStatus;
}

typedef struct
{
#ifdef NCP_BIG_ENDIAN
          /* word 0 */
     unsigned      reserved0_38_7                            : 32;
          /* word 1 */
     unsigned      reserved0_6_0                             :  7;
     unsigned      pcie_rst                                  :  1;
     unsigned      treemem_rst                               :  1;
     unsigned      tmgr_rst                                  :  1;
     unsigned      scnt_dist_rst                             :  1;
     unsigned      cmem_rst                                  :  1;
     unsigned      cmem_phy_io_rst                           :  1;
     unsigned      spp_rst                                   :  1;
     unsigned      smc3_rst                                  :  1;
     unsigned      smem3_phy_io_rst                          :  1;
     unsigned      smc2_rst                                  :  1;
     unsigned      smem2_phy_io_rst                          :  1;
     unsigned      smc1_rst                                  :  1;
     unsigned      smem1_phy_io_rst                          :  1;
     unsigned      smc0_rst                                  :  1;
     unsigned      smem0_phy_io_rst                          :  1;
     unsigned      gic500_rst                                :  1;
     unsigned      elm3_rst                                  :  1;
     unsigned      elm2_rst                                  :  1;
     unsigned      elm1_rst                                  :  1;
     unsigned      elm0_rst                                  :  1;
     unsigned      sed_rst                                   :  1;
     unsigned      rif1_rst                                  :  1;
     unsigned      rif0_rst                                  :  1;
     unsigned      amxs_rst                                  :  1;
     unsigned      pic_rst                                   :  1;
          /* word 2 */
     unsigned      pab_rst                                   :  1;
     unsigned      pcx_rst                                   :  1;
     unsigned      pbm_tq_rst                                :  1;
     unsigned      pbm_rst                                   :  1;
     unsigned      tq_nic_rst                                :  1;
     unsigned      tq_pb_rst                                 :  1;
     unsigned      data_nic_rst                              :  1;
     unsigned      data_pb_rst                               :  1;
     unsigned      ncapd_rst                                 :  1;
     unsigned      ncapc_rst                                 :  1;
     unsigned      ncapb_rst                                 :  1;
     unsigned      ncapa_rst                                 :  1;
     unsigned      ncap9_rst                                 :  1;
     unsigned      ncap8_rst                                 :  1;
     unsigned      ncap7_rst                                 :  1;
     unsigned      ncap6_rst                                 :  1;
     unsigned      ncap5_rst                                 :  1;
     unsigned      ncap4_rst                                 :  1;
     unsigned      ncap3_rst                                 :  1;
     unsigned      ncap2_rst                                 :  1;
     unsigned      ncap1_rst                                 :  1;
     unsigned      ncap0_rst                                 :  1;
     unsigned      mtm_rst                                   :  1;
     unsigned      mppy_rst                                  :  1;
     unsigned      mme_rst                                   :  1;
     unsigned      isb_rst                                   :  1;
     unsigned      eshim_rst                                 :  1;
     unsigned      erif0_rst                                 :  1;
     unsigned      ioctl_rst                                 :  1;
     unsigned      fes_rst                                   :  1;
     unsigned      erif1_rst                                 :  1;
     unsigned      eioa_phy14_rst                            :  1;
          /* word 3 */
     unsigned      eioa_phy13_rst                            :  1;
     unsigned      eioa_phy12_rst                            :  1;
     unsigned      eioa_phy11_rst                            :  1;
     unsigned      eioa_phy10_rst                            :  1;
     unsigned      eioa_phy9_rst                             :  1;
     unsigned      eioa_phy8_rst                             :  1;
     unsigned      eioa_phy7_rst                             :  1;
     unsigned      eioa_phy6_rst                             :  1;
     unsigned      eioa_phy5_rst                             :  1;
     unsigned      eioa_phy4_rst                             :  1;
     unsigned      eioa_phy3_rst                             :  1;
     unsigned      eioa_phy2_rst                             :  1;
     unsigned      eioa_phy1_rst                             :  1;
     unsigned      eioa_phy0_rst                             :  1;
     unsigned      dpi_rst                                   :  1;
     unsigned      dec_rst                                   :  1;
     unsigned      nlink5_rst                                :  1;
     unsigned      nlink4_rst                                :  1;
     unsigned      nlink3_rst                                :  1;
     unsigned      nlink2_rst                                :  1;
     unsigned      nlink1_rst                                :  1;
     unsigned      nlink0_rst                                :  1;
     unsigned      ccm_rst                                   :  1;
     unsigned      isbs1_rst                                 :  1;
     unsigned      isbs0_rst                                 :  1;
     unsigned      ccms_rst                                  :  1;
     unsigned      eioasm1_rst                               :  1;
     unsigned      eioasm0_rst                               :  1;
     unsigned      eioas1_rst                                :  1;
     unsigned      eioas0_rst                                :  1;
     unsigned      eioamh_rst                                :  1;
     unsigned      eioam_rst                                 :  1;
#else    /* Little Endian */
          /* word 0 */
     unsigned      reserved0_38_7                            : 32;
          /* word 1 */
     unsigned      pic_rst                                   :  1;
     unsigned      amxs_rst                                  :  1;
     unsigned      rif0_rst                                  :  1;
     unsigned      rif1_rst                                  :  1;
     unsigned      sed_rst                                   :  1;
     unsigned      elm0_rst                                  :  1;
     unsigned      elm1_rst                                  :  1;
     unsigned      elm2_rst                                  :  1;
     unsigned      elm3_rst                                  :  1;
     unsigned      gic500_rst                                :  1;
     unsigned      smem0_phy_io_rst                          :  1;
     unsigned      smc0_rst                                  :  1;
     unsigned      smem1_phy_io_rst                          :  1;
     unsigned      smc1_rst                                  :  1;
     unsigned      smem2_phy_io_rst                          :  1;
     unsigned      smc2_rst                                  :  1;
     unsigned      smem3_phy_io_rst                          :  1;
     unsigned      smc3_rst                                  :  1;
     unsigned      spp_rst                                   :  1;
     unsigned      cmem_phy_io_rst                           :  1;
     unsigned      cmem_rst                                  :  1;
     unsigned      scnt_dist_rst                             :  1;
     unsigned      tmgr_rst                                  :  1;
     unsigned      treemem_rst                               :  1;
     unsigned      pcie_rst                                  :  1;
     unsigned      reserved0_6_0                             :  7;
          /* word 2 */
     unsigned      eioa_phy14_rst                            :  1;
     unsigned      erif1_rst                                 :  1;
     unsigned      fes_rst                                   :  1;
     unsigned      ioctl_rst                                 :  1;
     unsigned      erif0_rst                                 :  1;
     unsigned      eshim_rst                                 :  1;
     unsigned      isb_rst                                   :  1;
     unsigned      mme_rst                                   :  1;
     unsigned      mppy_rst                                  :  1;
     unsigned      mtm_rst                                   :  1;
     unsigned      ncap0_rst                                 :  1;
     unsigned      ncap1_rst                                 :  1;
     unsigned      ncap2_rst                                 :  1;
     unsigned      ncap3_rst                                 :  1;
     unsigned      ncap4_rst                                 :  1;
     unsigned      ncap5_rst                                 :  1;
     unsigned      ncap6_rst                                 :  1;
     unsigned      ncap7_rst                                 :  1;
     unsigned      ncap8_rst                                 :  1;
     unsigned      ncap9_rst                                 :  1;
     unsigned      ncapa_rst                                 :  1;
     unsigned      ncapb_rst                                 :  1;
     unsigned      ncapc_rst                                 :  1;
     unsigned      ncapd_rst                                 :  1;
     unsigned      data_pb_rst                               :  1;
     unsigned      data_nic_rst                              :  1;
     unsigned      tq_pb_rst                                 :  1;
     unsigned      tq_nic_rst                                :  1;
     unsigned      pbm_rst                                   :  1;
     unsigned      pbm_tq_rst                                :  1;
     unsigned      pcx_rst                                   :  1;
     unsigned      pab_rst                                   :  1;
          /* word 3 */
     unsigned      eioam_rst                                 :  1;
     unsigned      eioamh_rst                                :  1;
     unsigned      eioas0_rst                                :  1;
     unsigned      eioas1_rst                                :  1;
     unsigned      eioasm0_rst                               :  1;
     unsigned      eioasm1_rst                               :  1;
     unsigned      ccms_rst                                  :  1;
     unsigned      isbs0_rst                                 :  1;
     unsigned      isbs1_rst                                 :  1;
     unsigned      ccm_rst                                   :  1;
     unsigned      nlink0_rst                                :  1;
     unsigned      nlink1_rst                                :  1;
     unsigned      nlink2_rst                                :  1;
     unsigned      nlink3_rst                                :  1;
     unsigned      nlink4_rst                                :  1;
     unsigned      nlink5_rst                                :  1;
     unsigned      dec_rst                                   :  1;
     unsigned      dpi_rst                                   :  1;
     unsigned      eioa_phy0_rst                             :  1;
     unsigned      eioa_phy1_rst                             :  1;
     unsigned      eioa_phy2_rst                             :  1;
     unsigned      eioa_phy3_rst                             :  1;
     unsigned      eioa_phy4_rst                             :  1;
     unsigned      eioa_phy5_rst                             :  1;
     unsigned      eioa_phy6_rst                             :  1;
     unsigned      eioa_phy7_rst                             :  1;
     unsigned      eioa_phy8_rst                             :  1;
     unsigned      eioa_phy9_rst                             :  1;
     unsigned      eioa_phy10_rst                            :  1;
     unsigned      eioa_phy11_rst                            :  1;
     unsigned      eioa_phy12_rst                            :  1;
     unsigned      eioa_phy13_rst                            :  1;
#endif
} __attribute__ ( ( packed ) ) ncp_syscon_reset_mod_r_xlf_t;

typedef struct
{
#ifdef NCP_BIG_ENDIAN
          /* word 0 */
     unsigned      reserved0_63_32                           : 32;
          /* word 1 */
     unsigned      reserved0_31_0                            : 32;
          /* word 2 */
     unsigned      usb1_phy_rst                              :  1;
     unsigned      usb1_phy_fab_rst                          :  1;
     unsigned      usb0_phy_rst                              :  1;
     unsigned      usb0_phy_fab_rst                          :  1;
     unsigned      ccn512_rst                                :  1;
     unsigned      usb1_rst                                  :  1;
     unsigned      nrcp_rst                                  :  1;
     unsigned      cpm_rst                                   :  1;
     unsigned      usb1_fabric_rst                           :  1;
     unsigned      usb0_rst                                  :  1;
     unsigned      usb0_fabric_rst                           :  1;
     unsigned      uart_2_rst                                :  1;
     unsigned      uart_1_rst                                :  1;
     unsigned      uart_0_rst                                :  1;
     unsigned      timer_rst                                 :  1;
     unsigned      ssp2_rst                                  :  1;
     unsigned      ssp1_rst                                  :  1;
     unsigned      ssp0_rst                                  :  1;
     unsigned      smb_rst                                   :  1;
     unsigned      mtc_rst                                   :  1;
     unsigned      mdio1_rst                                 :  1;
     unsigned      mdio0_rst                                 :  1;
     unsigned      i2c_11_rst                                :  1;
     unsigned      i2c_10_rst                                :  1;
     unsigned      i2c_9_rst                                 :  1;
     unsigned      i2c_8_rst                                 :  1;
     unsigned      i2c_7_rst                                 :  1;
     unsigned      i2c_6_rst                                 :  1;
     unsigned      i2c_5_rst                                 :  1;
     unsigned      i2c_4_rst                                 :  1;
     unsigned      i2c_3_rst                                 :  1;
     unsigned      i2c_2_rst                                 :  1;
          /* word 3 */
     unsigned      i2c_1_rst                                 :  1;
     unsigned      i2c_0_rst                                 :  1;
     unsigned      gpio_rst                                  :  1;
     unsigned      gemac_rst                                 :  1;
     unsigned      fc_rst                                    :  1;
     unsigned      periph_fabric_rst                         :  1;
     unsigned      eac_rst                                   :  1;
     unsigned      axi_pci_rst                               :  1;
     unsigned      pci_rst                                   :  1;
     unsigned      pci_fabric_rst                            :  1;
     unsigned      trng_rst                                  :  1;
     unsigned      sbb_rst                                   :  1;
     unsigned      pka__rst                                  :  1;
     unsigned      lsm_rst                                   :  1;
     unsigned      jtag2axi_rst                              :  1;
     unsigned      gpdma_1_rst                               :  1;
     unsigned      gpdma_0_rst                               :  1;
     unsigned      gic490_rst                                :  1;
     unsigned      mmap_fabric_rst                           :  1;
     unsigned      axi2ser12_rst                             :  1;
     unsigned      axi2ser11_rst                             :  1;
     unsigned      axi2ser10_rst                             :  1;
     unsigned      axi2ser9_rst                              :  1;
     unsigned      axi2ser8_rst                              :  1;
     unsigned      axi2ser6_rst                              :  1;
     unsigned      axi2ser5_rst                              :  1;
     unsigned      axi2ser4_rst                              :  1;
     unsigned      axi2ser3_rst                              :  1;
     unsigned      axi2ser2_rst                              :  1;
     unsigned      axi2ser1_rst                              :  1;
     unsigned      axi2ser0_rst                              :  1;
     unsigned      awlock_rst                                :  1;
#else    /* Little Endian */
          /* word 0 */
     unsigned      reserved0_63_32                           : 32;
          /* word 1 */
     unsigned      reserved0_31_0                            : 32;
          /* word 2 */
     unsigned      i2c_2_rst                                 :  1;
     unsigned      i2c_3_rst                                 :  1;
     unsigned      i2c_4_rst                                 :  1;
     unsigned      i2c_5_rst                                 :  1;
     unsigned      i2c_6_rst                                 :  1;
     unsigned      i2c_7_rst                                 :  1;
     unsigned      i2c_8_rst                                 :  1;
     unsigned      i2c_9_rst                                 :  1;
     unsigned      i2c_10_rst                                :  1;
     unsigned      i2c_11_rst                                :  1;
     unsigned      mdio0_rst                                 :  1;
     unsigned      mdio1_rst                                 :  1;
     unsigned      mtc_rst                                   :  1;
     unsigned      smb_rst                                   :  1;
     unsigned      ssp0_rst                                  :  1;
     unsigned      ssp1_rst                                  :  1;
     unsigned      ssp2_rst                                  :  1;
     unsigned      timer_rst                                 :  1;
     unsigned      uart_0_rst                                :  1;
     unsigned      uart_1_rst                                :  1;
     unsigned      uart_2_rst                                :  1;
     unsigned      usb0_fabric_rst                           :  1;
     unsigned      usb0_rst                                  :  1;
     unsigned      usb1_fabric_rst                           :  1;
     unsigned      cpm_rst                                   :  1;
     unsigned      nrcp_rst                                  :  1;
     unsigned      usb1_rst                                  :  1;
     unsigned      ccn512_rst                                :  1;
     unsigned      usb0_phy_fab_rst                          :  1;
     unsigned      usb0_phy_rst                              :  1;
     unsigned      usb1_phy_fab_rst                          :  1;
     unsigned      usb1_phy_rst                              :  1;
          /* word 3 */
     unsigned      awlock_rst                                :  1;
     unsigned      axi2ser0_rst                              :  1;
     unsigned      axi2ser1_rst                              :  1;
     unsigned      axi2ser2_rst                              :  1;
     unsigned      axi2ser3_rst                              :  1;
     unsigned      axi2ser4_rst                              :  1;
     unsigned      axi2ser5_rst                              :  1;
     unsigned      axi2ser6_rst                              :  1;
     unsigned      axi2ser8_rst                              :  1;
     unsigned      axi2ser9_rst                              :  1;
     unsigned      axi2ser10_rst                             :  1;
     unsigned      axi2ser11_rst                             :  1;
     unsigned      axi2ser12_rst                             :  1;
     unsigned      mmap_fabric_rst                           :  1;
     unsigned      gic490_rst                                :  1;
     unsigned      gpdma_0_rst                               :  1;
     unsigned      gpdma_1_rst                               :  1;
     unsigned      jtag2axi_rst                              :  1;
     unsigned      lsm_rst                                   :  1;
     unsigned      pka__rst                                  :  1;
     unsigned      sbb_rst                                   :  1;
     unsigned      trng_rst                                  :  1;
     unsigned      pci_fabric_rst                            :  1;
     unsigned      pci_rst                                   :  1;
     unsigned      axi_pci_rst                               :  1;
     unsigned      eac_rst                                   :  1;
     unsigned      periph_fabric_rst                         :  1;
     unsigned      fc_rst                                    :  1;
     unsigned      gemac_rst                                 :  1;
     unsigned      gpio_rst                                  :  1;
     unsigned      i2c_0_rst                                 :  1;
     unsigned      i2c_1_rst                                 :  1;
#endif
} __attribute__ ( ( packed ) ) ncp_syscon_reset_axis_r_xlf_t;

ncp_st_t                                       
ncp_dev_reset_hw(void)
{
    ncp_st_t                    ncpStatus = NCP_ST_SUCCESS;
    ncp_st_t                    st = NCP_ST_SUCCESS;
    ncp_uint32_t 				ubootCmemInit = 1;
    ncp_uint32_t                *reg = NULL;
	ncp_uint32_t				offset = 0;
	ncp_uint32_t 				*p = NULL;
    ncp_syscon_reset_mod_r_xlf_t    resetReg = {0};
    ncp_syscon_reset_axis_r_xlf_t   resetAxisReg = {0};

	{
		p = (ncp_uint32_t *)&resetAxisReg;
		debug("resetAxisReg addr %p -> %08x %08x %08x %08x\n", 
					(void*)p, *p, *(p+1), *(p+2), *(p+3));

		p = (ncp_uint32_t *)&resetReg;
		debug("resetReg addr %p -> %08x %08x %08x %08x\n", 
					(void*)p, *p, *(p+1), *(p+2), *(p+3));
	}

    /* Make sure the boot counter is decoupled from the Nuevo timestamp */
    NCP_CALL(ncr_write32(NCP_REGION_TIMER_TMGR_SYSTEM_COUNT,
         NCP_TMGR_SYSTEM_COUNT_CFG_SYSTEM_COUNTER_CONTROL, 0));

    /* wait for the PIO to complete */
    udelay(100000);

    /* quiesce the system */
    ncpStatus = ncp_dev_quiesce();
    if (ncpStatus != NCP_ST_SUCCESS)
    {
        NCP_MSG(NCP_MSG_ERROR, "ncp_dev_quiesce failed with %d\n", ncpStatus);
    }

    /* Enable protected writes.  Key is the only field in this register. */
    NCP_CALL(ncr_write32(NCP_REGION_AXIS_APB2SER3_SYSCON, NCP_SYSCON_KEY_xlf, 0xAB));

    resetReg.mppy_rst         = 1;
    resetReg.ncap0_rst        = 1;
    resetReg.ncap1_rst        = 1;
    resetReg.ncap2_rst        = 1;
    resetReg.ncap3_rst        = 1;
    resetReg.ncap4_rst        = 1;
    resetReg.ncap5_rst        = 1;
    resetReg.ncap6_rst        = 1;
    resetReg.ncap7_rst        = 1;
    resetReg.ncap8_rst        = 1;
    resetReg.ncap9_rst        = 1;
    resetReg.ncapa_rst        = 1;
    resetReg.ncapb_rst        = 1;
    resetReg.ncapc_rst        = 1;
    resetReg.ncapd_rst        = 1;
    resetReg.nlink0_rst       = 1;
    resetReg.nlink1_rst       = 1;
    resetReg.nlink2_rst       = 1;
    resetReg.nlink3_rst       = 1;
    resetReg.nlink4_rst       = 1;
    resetReg.nlink5_rst       = 1;
    resetReg.mme_rst          = 1;
    resetReg.spp_rst          = 1;
    resetReg.dpi_rst          = 1;
    resetReg.pic_rst          = 1;
    resetReg.rif0_rst         = 1;
    resetReg.rif1_rst         = 1;
    resetReg.erif0_rst        = 1;
    resetReg.erif1_rst        = 1;
    resetReg.dec_rst          = 1;
    resetReg.eshim_rst        = 1;
    resetReg.pab_rst          = 1;
    resetReg.sed_rst          = 1;
    resetReg.mtm_rst          = 1;
    resetReg.tmgr_rst         = 1;
    resetReg.treemem_rst      = 1;
    resetReg.eioam_rst        = 1;
    resetReg.eioamh_rst       = 1;
    resetReg.eioas0_rst       = 1;
    resetReg.eioas1_rst       = 1;
    resetReg.eioasm0_rst      = 1;
    resetReg.eioasm1_rst      = 1;
    resetReg.isb_rst          = 1;
    resetReg.pcx_rst          = 1;
    resetReg.ccm_rst          = 1;
#if 0
    resetReg.ring_bp_rst      = 1;
#endif
    resetReg.eioa_phy0_rst    = 1;
    resetReg.eioa_phy1_rst    = 1;
    resetReg.eioa_phy2_rst    = 1;
    resetReg.eioa_phy3_rst    = 1;
    resetReg.eioa_phy4_rst    = 1;
    resetReg.eioa_phy5_rst    = 1;
    resetReg.eioa_phy6_rst    = 1;
    resetReg.eioa_phy7_rst    = 1;
    resetReg.eioa_phy8_rst    = 1;
    resetReg.eioa_phy9_rst    = 1;
    resetReg.eioa_phy10_rst   = 1;
    resetReg.eioa_phy11_rst   = 1;
    resetReg.eioa_phy12_rst   = 1;
    resetReg.eioa_phy13_rst   = 1;
    resetReg.eioa_phy14_rst   = 1;
    resetReg.isbs0_rst        = 1;
    resetReg.isbs1_rst        = 1;
    resetReg.ccms_rst         = 1;
    resetReg.pbm_rst          = 1;
    resetReg.pbm_tq_rst       = 1;
    resetReg.tq_nic_rst       = 1;
    resetReg.tq_pb_rst        = 1;
    resetReg.data_nic_rst     = 1;
    resetReg.data_pb_rst      = 1;
#if 0
    resetReg.timestamp_rst    = 1;
#endif

    if (ubootCmemInit == 0) 
    {
        resetReg.cmem_rst        = 1;
        resetReg.cmem_phy_io_rst = 1;
    }

#define NCP_DEV_ACE
#ifndef NCP_DEV_ACE
    resetReg.smc0_rst         = 1;
    resetReg.smem0_phy_io_rst = 1;
    resetReg.smc1_rst         = 1;
    resetReg.smem1_phy_io_rst = 1;
    resetReg.smc2_rst         = 1;
    resetReg.smem2_phy_io_rst = 1;
    resetReg.smc3_rst         = 1;
    resetReg.smem3_phy_io_rst = 1;
    resetReg.elm0_rst         = 1;
    resetReg.elm1_rst         = 1;
    resetReg.elm2_rst         = 1;
    resetReg.elm3_rst         = 1;
    resetReg.gic500_rst       = 1;
    resetReg.scnt_dist_rst    = 1;
#endif

    debug("writing NCP_SYSCON_RESET_MOD\n");

	{
		p = (ncp_uint32_t *)&resetReg;
		debug("resetReg (post) addr %p -> %08x %08x %08x %08x\n", 
					(void*)p, *p, *(p+1), *(p+2), *(p+3));
	}

    reg = (ncp_uint32_t *)&resetReg;
    ncr_write32(NCP_REGION_AXIS_APB2SER3_SYSCON,
                         NCP_SYSCON_RESET_MOD_xlf, 
                         *reg);
    reg++;
    ncr_write32(NCP_REGION_AXIS_APB2SER3_SYSCON,
                         NCP_SYSCON_RESET_MOD_xlf + 0x4, 
                         *reg);
    reg++;
    ncr_write32(NCP_REGION_AXIS_APB2SER3_SYSCON,
                         NCP_SYSCON_RESET_MOD_xlf + 0x8, 
                         *reg);
    reg++;
    ncr_write32(NCP_REGION_AXIS_APB2SER3_SYSCON,
                         NCP_SYSCON_RESET_MOD_xlf + 0xc, 
                         *reg);
    debug("Done\n");

    debug("writing NCP_SYSCON_RESET_AXIS\n");
    resetAxisReg.nrcp_rst     = 1;
	/*resetAxisReg.axi2ser9_rst = 1; */
	{
		p = (ncp_uint32_t *)&resetAxisReg;
		debug("resetAxisReg (post) addr %p -> %08x %08x %08x %08x\n", 
					(void*)p, *p, *(p+1), *(p+2), *(p+3));
	}

    reg = (ncp_uint32_t *)&resetAxisReg;
    ncr_write32(NCP_REGION_AXIS_APB2SER3_SYSCON,
                       NCP_SYSCON_RESET_AXIS_xlf,
                       *reg);
    reg++;
    ncr_write32(NCP_REGION_AXIS_APB2SER3_SYSCON,
                       NCP_SYSCON_RESET_AXIS_xlf + 0x4,
                       *reg);
    reg++;
    ncr_write32(NCP_REGION_AXIS_APB2SER3_SYSCON,
                       NCP_SYSCON_RESET_AXIS_xlf + 0x8,
                       *reg);
    reg++;
    ncr_write32(NCP_REGION_AXIS_APB2SER3_SYSCON,
                       NCP_SYSCON_RESET_AXIS_xlf + 0xc,
                       *reg);
    debug("Done\n");
    udelay(100000);

	debug("de-assert reset for modules and axis\n");
	for (offset = 0; offset<0x10; offset += 0x4) {
		ncr_write32(NCP_REGION_AXIS_APB2SER3_SYSCON,
							 NCP_SYSCON_RESET_MOD_xlf + offset,
							 0);
		ncr_write32(NCP_REGION_AXIS_APB2SER3_SYSCON,
							 NCP_SYSCON_RESET_AXIS_xlf + offset,
							 0);
	}


    debug("Done\n");
    udelay(100000);

    /* Disable protected writes */
    ncr_write32(NCP_REGION_AXIS_APB2SER3_SYSCON, NCP_SYSCON_KEY_xlf, 0x0);
	
NCP_RETURN_LABEL
    if(st != NCP_ST_SUCCESS)
        ncpStatus = st;
    return ncpStatus;
}


typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      spare6                                    :  1;
     unsigned      itask_end_data_fill_off                   :  1;
     unsigned      cfg_ring_ack_timer_en                     :  1;
     unsigned      ita_ord_wr_disable                        :  1;
     unsigned      opcq_entry_wr_dis                         :  1;
     unsigned      cpcq_en                                   :  1;
     unsigned      otask_accum_en                            :  1;
     unsigned      itask_accum_en                            :  1;
     unsigned      spare4                                    :  1;
     unsigned      otbp_soft_reset                           :  1;
     unsigned      spare3                                    :  1;
     unsigned      mpbf_en                                   :  1;
     unsigned      otbp_ext_mem_wen                          :  1;
     unsigned      spare2                                    :  2;
     unsigned      cpcq_exec_disable                         :  1;
     unsigned      spare1                                    :  2;
     unsigned      opcq_num_ent_per_req_m1                   :  2;
     unsigned      ota_num_beat                              :  2;
     unsigned      ita_num_beat                              :  2;
     unsigned      spare0                                    :  4;
     unsigned      pgit_w_num_beat                           :  2;
     unsigned      pgit_r_num_beat                           :  2;
#else    /* Little Endian */
     unsigned      pgit_r_num_beat                           :  2;
     unsigned      pgit_w_num_beat                           :  2;
     unsigned      spare0                                    :  4;
     unsigned      ita_num_beat                              :  2;
     unsigned      ota_num_beat                              :  2;
     unsigned      opcq_num_ent_per_req_m1                   :  2;
     unsigned      spare1                                    :  2;
     unsigned      cpcq_exec_disable                         :  1;
     unsigned      spare2                                    :  2;
     unsigned      otbp_ext_mem_wen                          :  1;
     unsigned      mpbf_en                                   :  1;
     unsigned      spare3                                    :  1;
     unsigned      otbp_soft_reset                           :  1;
     unsigned      spare4                                    :  1;
     unsigned      itask_accum_en                            :  1;
     unsigned      otask_accum_en                            :  1;
     unsigned      cpcq_en                                   :  1;
     unsigned      opcq_entry_wr_dis                         :  1;
     unsigned      ita_ord_wr_disable                        :  1;
     unsigned      cfg_ring_ack_timer_en                     :  1;
     unsigned      itask_end_data_fill_off                   :  1;
     unsigned      spare6                                    :  1;
#endif
} ncp_cmn_axi_config_init_reg_t;

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 22;
     unsigned      singlebit_ecc_correct_en                  :  1;
     unsigned      singlebit_ecc_detect_en                   :  1;
     unsigned      multibit_ecc_detect_en                    :  1;
     unsigned      cfg_par_err_rst_en                        :  1;
     unsigned      cfg_parity_type_ring2                     :  1;
     unsigned      cfg_parity_type_ring1                     :  1;
     unsigned      cfg_parity_type_ring0                     :  1;
     unsigned      cfg_parity_err_en_ring2                   :  1;
     unsigned      cfg_parity_err_en_ring1                   :  1;
     unsigned      cfg_parity_err_en_ring0                   :  1;
#else    /* Little Endian */
     unsigned      cfg_parity_err_en_ring0                   :  1;
     unsigned      cfg_parity_err_en_ring1                   :  1;
     unsigned      cfg_parity_err_en_ring2                   :  1;
     unsigned      cfg_parity_type_ring0                     :  1;
     unsigned      cfg_parity_type_ring1                     :  1;
     unsigned      cfg_parity_type_ring2                     :  1;
     unsigned      cfg_par_err_rst_en                        :  1;
     unsigned      multibit_ecc_detect_en                    :  1;
     unsigned      singlebit_ecc_detect_en                   :  1;
     unsigned      singlebit_ecc_correct_en                  :  1;
     unsigned      reserved0                                 : 22;
#endif
} ncp_ncap_cfg_ring_parity_reg_t;


ncp_st_t
ncp_dev_reset_sw(void)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_uint32_t reg = 0;

    ncp_cmn_axi_config_init_reg_t  *nca_cfg_init = NULL;
    ncp_ncap_cfg_ring_parity_reg_t *nca_cfg_ring_parity = NULL;

    /* Enable NCA config ring timeouts */
    ncr_read32(NCP_REGION_ID(0x101, 0), NCP_NCAP_CONFIG_INIT, &reg);
    nca_cfg_init = (ncp_cmn_axi_config_init_reg_t *) &reg;
    nca_cfg_init->cfg_ring_ack_timer_en = 1;
    ncr_write32(NCP_REGION_ID(0x101, 0), NCP_NCAP_CONFIG_INIT, reg);

    ncr_write32(NCP_REGION_ID(0x101, 0), NCP_CMN_AXI_CFG_RING_ACK_TIMER_CNT, 0x5f5e10);

    /* Enable config ring parity checking */
    ncr_read32(NCP_REGION_ID(0x101, 0), NCP_CMN_AXI_CFG_RING_PARITY, &reg);
    nca_cfg_ring_parity = (ncp_ncap_cfg_ring_parity_reg_t *) &reg;
    nca_cfg_ring_parity->cfg_parity_err_en_ring0 = 1;
    nca_cfg_ring_parity->cfg_parity_err_en_ring1 = 1;
    nca_cfg_ring_parity->cfg_parity_err_en_ring2 = 1;
    nca_cfg_ring_parity->multibit_ecc_detect_en = 1;
    nca_cfg_ring_parity->singlebit_ecc_detect_en = 1;
    nca_cfg_ring_parity->singlebit_ecc_correct_en = 1;
	ncr_write32(NCP_REGION_ID(0x101, 0), NCP_CMN_AXI_CFG_RING_PARITY, reg);

	/* TEMP? cfg_tzc400 */
	/*  
	 *  TZC400 Programming
	 */
	 /*  Wait for TZC internal config. 
	  *  This read will be on hold until tzc finishes internal config */
	/* Make sure the TZC has finished internal configuration. */
	(void)readl(TZC + 8);
	/* (Enable Gate keeper register to allow secure access from tzc) */
	writel(0x1, (TZC + 0x8));
	/*  Enable read/write acccess */
	writel(0xc000000f, (TZC + 0x110));

    /*
     * SAX1-1213: configure NCAv3 for non-secure access 
     * to support CDC DMM
     *
     * Perform the following writes: 
     *
     * ncpWrite 0x170.1.0x42800 0x3
     * ncpWrite 0x170.1.0x18 0xffff
     * ncpWrite 0x170.1.0x3c 0xffff
     * ncpWrite 0x170.1.0x7c 0xffff
     * ncpWrite 0x170.1.0x880 0xffffffff 0xffffffff
     * ncpWrite 0x170.1.0x888 0xffffffff 0xffffffff
     *
     */
	writel(0x3, (MMAP_SCB + 0x42800));
	writel(0xffff, (MMAP_SCB + 0x18));
	writel(0xffff, (MMAP_SCB + 0x3c));
	writel(0xffff, (MMAP_SCB + 0x7c));
	writel(0xffffffff, (MMAP_SCB + 0x880));
	writel(0xffffffff, (MMAP_SCB + 0x884));
	writel(0xffffffff, (MMAP_SCB + 0x888));
	writel(0xffffffff, (MMAP_SCB + 0x88c));

NCP_RETURN_LABEL
    return ncpStatus;
}

/*
  ------------------------------------------------------------------------------
  ncp_dev_reset
*/

static int
ncp_dev_reset(void)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    ncpStatus = ncp_dev_reset_hw();
    debug("ncp_dev_reset_hw\n");
    if(ncpStatus != NCP_ST_SUCCESS)
    {
        NCP_MSG(NCP_MSG_ERROR, "ncp_dev_reset_hw failed with %d\n", ncpStatus);
        return -1;
    }

    ncpStatus = ncp_dev_reset_sw();
    debug("ncp_dev_reset_sw\n");
    if(ncpStatus != NCP_ST_SUCCESS)
    {
        NCP_MSG(NCP_MSG_ERROR, "ncp_dev_reset_sw failed with %d\n", ncpStatus);
        return -1;
    }

	return 0;
}

/*
  ------------------------------------------------------------------------------
  ncp_dev_do_read
*/

static int
ncp_dev_do_read(ncr_command_t *command, unsigned *value)
{
	switch (command->region) {
	case NCP_REGION_ID(0x200, 0x0):
	{
		*value = *(volatile unsigned*)(unsigned long)command->offset;
	}
	/* We have them in the traces but ignoring */
	case NCP_REGION_ID(0x301, 0x0): /*NCP_REGION_DRIVER_CFG*/
	case NCP_REGION_ID(0x147, 0x0): /*MDIO*/
	{
		return 0;
	}
	default:
		if (0 != ncr_read32(command->region, command->offset, value)) {
			debug("READ ERROR: n=0x%x t=0x%x o=0x%x\n",
					NCP_NODE_ID(command->region),
					NCP_TARGET_ID(command->region), command->offset);
			return -1;
		}
		return 0;
	}

	return 0;
}

/*
  ------------------------------------------------------------------------------
  ncp_dev_do_write
*/

static int
ncp_dev_do_write(ncr_command_t *command)
{
	switch (command->region) {
	case NCP_REGION_ID(0x200, 1):
	{
		unsigned int read_back = *(volatile unsigned*)(unsigned long)command->offset;

 		*(volatile unsigned*)(unsigned long)(command->offset) = (unsigned) command->value;
		if (read_back != command->value) {
			debug("WRITE ERROR: n=0x%x t=0x%x o=0x%x "
				"v=0x%x\n",
				NCP_NODE_ID(command->region),
				NCP_TARGET_ID(command->region),
				command->offset, command->value);
			return -1;
		}
		break;
	}
	/* We have them in the traces but ignoring */
	case NCP_REGION_ID(0x301, 0x0): /*NCP_REGION_DRIVER_CFG*/
	case NCP_REGION_ID(0x147, 0x0): /*MDIO*/
	{
		return 0;
	}
	default:
		if (0 != ncr_write32(command->region, command->offset,
					 command->value)) {
			printf("WRITE ERROR: n=0x%x t=0x%x o=0x%x "
					"v=0x%x\n",
					NCP_NODE_ID(command->region),
					NCP_TARGET_ID(command->region),
					command->offset, command->value);

			return -1;
		}
		break;
	}
	
	return 0;
}

/*
  ------------------------------------------------------------------------------
  ncp_dev_do_write_64
	
  This is only for the memory writes. Most likely not necessary as the current 
  traces do not use the values over 1 word (32 bits) but may be they will in future
  so leaving in.
*/

static int
ncp_dev_do_write_64(ncr_command_t *command)
{
	if (NCP_REGION_ID(0x200, 1) == command->region) {
		debug("val 0x%lx @ addr 0x%lx\n", 
				(unsigned long)command->value,  (unsigned long)command->offset);

 		*(volatile unsigned long*)(unsigned long)(command->offset) = (unsigned long) command->value;
		
		unsigned long read_back = *(volatile unsigned long*)(unsigned long)command->offset;
		if (read_back != command->value) {
			printf("WRITE ERROR: n=0x%x t=0x%x o=0x%x "
				"v=0x%x\n",
				NCP_NODE_ID(command->region),
				NCP_TARGET_ID(command->region),
				command->offset, command->value);
			return -1;
		}
		
		return 0;
	}

	return -1;
}

/*
  ------------------------------------------------------------------------------
  ncp_dev_do_modify
*/

static int
ncp_dev_do_modify(ncr_command_t *command)
{
    if (NCP_REGION_ID(0x200, 1) == command->region) {
        ncp_dev_do_read(command, &command->value);

        command->value &= ~command->mask;
        command->value |= command->value;

        ncp_dev_do_write(command);

		return 0;
	} 

	if (0 != ncr_modify32(command->region, command->offset,
			      command->mask, command->value)) {
		debug("MODIFY ERROR: n=0x%x t=0x%x o=0x%x m=0x%x "
			    "v=0x%x\n",
			    NCP_NODE_ID(command->region),
			    NCP_TARGET_ID(command->region), command->offset,
			    command->mask, command->value);

		return -1;
	} 

#ifdef NCR_DEBUG
		debug("MODIFY: r=0x%x o=0x%x m=0x%x v=0x%x\n",
			    command->region, command->offset,
			    command->mask, command->value);
#endif

    return 0;
}

/*
  ------------------------------------------------------------------------------
  ncp_dev_do_poll
*/

static int
ncp_dev_do_poll(ncr_command_t *command)
{
	int timeout = 1000;
	int delay = 1000;
	unsigned value;

	do {
		udelay(delay);

		if (0 != ncp_dev_do_read(command, &value)) {
			printf("ncp_dev_do_read() failed!\n");
			return -1;
		}
	} while (((value & command->mask) != command->value) &&
		 0 < --timeout);

	if (0 == timeout) {
		printf("ncp_dev_do_poll() timed out!\n");
		return -1;
	}

	return 0;
}

/*
  ------------------------------------------------------------------------------
  ncp_dev_configure
*/

static int
ncp_dev_configure(ncr_command_t *commands) {
	int rc = 0;
	unsigned value;
    ncr_command_t *startCmd = commands;

	while (NCR_COMMAND_NULL != commands->command) {
		switch (commands->command) {
		case NCR_COMMAND_WRITE:
			rc = ncp_dev_do_write(commands);
			break;
		case NCR_COMMAND_WRITE64:
			rc = ncp_dev_do_write_64(commands);
			break;
		case NCR_COMMAND_READ:
			rc = ncp_dev_do_read(commands, &value);
			break;
		case NCR_COMMAND_MODIFY:
			rc = ncp_dev_do_modify(commands);
			break;
		case NCR_COMMAND_USLEEP:
#ifdef NCR_DEBUG
			debug("USLEEP: v=0x%x\n", commands->value);
#endif
			udelay(commands->value);
			break;
		case NCR_COMMAND_POLL:
			rc = ncp_dev_do_poll(commands);
			break;
		default:
			printf("Unknown Command: 0x%x, startCmd=%p, curCmd=%p\n",
			       (unsigned int)commands->command,
			       startCmd,
			       commands);
			rc = -1;
			break;
		}

		if (ctrlc()) {
			printf("Canceling configuration.\n");
			break;
		}

		++commands;
	}

	return rc;
}

#if defined(CONFIG_AXXIA_XLF)
#ifdef ALL_TRACES
#include "EIOA67xx/all.c"
#else
#include "EIOA67xx/mme.c"
#include "EIOA67xx/pbm.c"
#include "EIOA67xx/vp.c"
#include "EIOA67xx/nca.c"
#include "EIOA67xx/eioa.c"
#endif /* ALL_TRACES */
#else
#error "EIOA is not defined for this architecture!"
#endif


/*
  ------------------------------------------------------------------------------
 */
int static
gmac_set_region_offset(
	unsigned gmac,
	unsigned *eioaRegion,
	unsigned *hwPortGmac, 	
	unsigned *gmacRegion, 
	unsigned *gmacPortOffset)
{
	/* Set the region and offset. Just native dmain:
  		EIOA0: gmac0
  		EIOA1: gmac16-20. gmac20 is Nokia!!!*/
    if (5 > gmac) {
        *hwPortGmac = ((gmac == 0) ? 0 : (gmac - 1));
		*eioaRegion = NCP_REGION_ID(31, 16); /* 0x1f.0x10 */
		*gmacRegion = ((gmac == 0) ? NCP_REGION_ID(31, 17) : /* 0x1f.0x11 */ 
                                     NCP_REGION_ID(31, 18)); /* 0x1f.0x12 */
		*gmacPortOffset = 0xc * (*hwPortGmac);
	} else if (16 <= gmac && 20 >= gmac) {
	    *hwPortGmac = ((gmac == 16) ? 0 : (gmac - 17));
		*eioaRegion = NCP_REGION_ID(23, 16); /* 0x17.0x10 */
        *gmacRegion = ((gmac == 16) ? NCP_REGION_ID(23, 17) : /* 0x17.0x11 */ 
                                     NCP_REGION_ID(23, 18)); /* 0x17.0x12 */
		*gmacPortOffset = 0xc * (*hwPortGmac);
	} else {
		debug("NetBoot XLF doesn't support gmac%d\n", gmac);
		return -1;
	}

	return 0;
}

/*
  ------------------------------------------------------------------------------
  take_snapshot: this allows seeing the rx/tx counters at the interfaces
*/
int __weak
take_snapshot(int gmac) 
{
	int rc, number = 56;
	unsigned val, zero = 0;
	int offset_rx = 0xf00, offset_tx = 0xe00;
	/*unsigned eioaRegion;*/
	unsigned gmacRegion;
	unsigned gmacPortOffset;
	unsigned hwPortGmac;

	if (0 != gmac_set_region_offset(gmac, NULL, &hwPortGmac, &gmacRegion, &gmacPortOffset))
		return -1;

	/* eg. gmac00_config @0x17.0x11.0xd0c */
	debug("gmac0x_config @gmacRegion 0x%x, gmacPortOffset 0x%x, v 0x45ee\n", gmacRegion, 0xd0c + 4 * hwPortGmac);
	ncr_write32(gmacRegion, 0xd0c + 4 * hwPortGmac, 0x45ee);
		udelay(5000);
	/* snapshot @gmacRegion.0xd40 */
	debug("snapshot @gmacRegion 0x%x, gmacPortOffset 0x%x, v 0x%x\n", gmacRegion, 0xd40, hwPortGmac);
	ncr_write32(gmacRegion, 0xd40, hwPortGmac);	
		udelay(5000);
		udelay(5000);

	printf("Snapshot for gmac%d\n", gmac);
	while (0 < number--) {
		rc = ncr_read32(gmacRegion, offset_tx, &val);
		if (0 != val) { 
			zero = 1;
			printf("%08x\t", val);
		}

		if (0 != rc)
			return -1;

		offset_tx += 4;
	}

	number = 56;
	while (0 < number--) {
		rc = ncr_read32(gmacRegion, offset_rx, &val);
		if (0 != val) { 
			zero = 1;
			printf("%08x\t", val);
		}

		if (0 != rc)
			return -1;

		offset_rx += 4;
	}
	if (zero == 0)
		printf("00000000\n");
	else 
		printf("\n");
	

	return 0;
}


/*
  -------------------------------------------------------------------------------
  ncp_task_uboot_domain_bundle_clear
*/

void static
ncp_task_uboot_domain_bundle_clear(void)
{
	return;
}

/*
  -------------------------------------------------------------------------------
  line_setup
*/

int
line_setup(int index) {
	ncp_st_t         ncpStatus = NCP_ST_SUCCESS;
	unsigned ncr_status;
	unsigned gmacRegion;
	unsigned gmacPortOffset;
	unsigned hwPortGmac;
	unsigned eioaRegion;
	unsigned top;
	unsigned bottom;
	char *oneg = "1G";
	char *envstring = getenv("phy_address");

	if (envstring)
		phy_by_index[index] = simple_strtoul(envstring, NULL, 0);

	mdio_initialize();

	/* Check for "macspeed" */
	envstring = getenv("macspeed");
	if (NULL == envstring) 
		envstring = oneg;
		
	debug("Setting gmac%d to %s\n", index, envstring);

	if (0 != gmac_set_region_offset(index, &eioaRegion, &hwPortGmac, &gmacRegion, &gmacPortOffset))
		return -1;

	debug("eioaRegion 0x%08x, hwPortGmac 0x%08x, gmacRegion 0x%08x, gmacPortOffset 0x%08x\n",
				eioaRegion, hwPortGmac, gmacRegion, gmacPortOffset);

	/* 
 		Disable stuff. 
	 */

	/* MAC Enable and Pause Control */
	NCP_CALL(ncr_modify32(gmacRegion, 0x330 + gmacPortOffset, 0x3f, 0));
	/* Packet Filter Engine Control */
	NCP_CALL(ncr_modify32(gmacRegion, 0x300 + gmacPortOffset, 0x8, 0x0));
	NCP_CALL(ncr_modify32(eioaRegion, 
				NCP_EIOA_GEN_CFG_REG_OFFSET(hwPortGmac) + 0x0, 
				0x00000003, 0x0));
	NCP_CALL(ncr_modify32(gmacRegion, 0x300 + gmacPortOffset, 0x4, 0x0));

	/* 
 		Set macspeed.
	 */
	
	NCP_CALL(ncr_read32(gmacRegion, 0x324 + gmacPortOffset,
				&ncr_status));
	ncr_status &= ~0x3c;
	ncr_status |= 0x08; /* Force Link Up */

	if (0 == strcmp("10MH", envstring)) {
	} else if (0 == strcmp("10MF", envstring)) {
		ncr_status |= 0x04;
	} else if (0 == strcmp("100MH", envstring)) {
		ncr_status |= 0x10;
	} else if (0 == strcmp("100MF", envstring)) {
		ncr_status |= 0x14;
	} else if (0 == strcmp("1G", envstring)) {
		ncr_status |= 0x24;
	} else {
		printf("macspeed must be set to 10MH, 10MF, 100MH, "
			   "100MF, or 1G\n");
		return -1;
	}

	ncr_status &= 0xfffffbff;
	NCP_CALL(ncr_write32(gmacRegion, 0x324 + gmacPortOffset,
				 ncr_status));

#ifdef PHY
{
	unsigned control, ad_value, ge_ad_value;	

	control = mdio_read(phy_by_index[index], 0);    
	ad_value = mdio_read(phy_by_index[index], 4);   
	ge_ad_value = mdio_read(phy_by_index[index], 9);

	control &= 0xdebf; /* clear bit 6, 8 and 13 */
	ad_value &= 0xfe1f; /* clear bits 5, 6, 7, 8 */
	ge_ad_value &= 0xcff; /* clear bits 8, 9 */
	
	if (0 == strcmp("10MH", envstring)) {
		ad_value |= 0x20;       /* set bit 5 */
	} else if (0 == strcmp("10MF", envstring)) {
		ad_value |= 0x40;       /* set bit 6 */
		control |= 0x100; /* set bit 8 */
	} else if (0 == strcmp("100MH", envstring)) {
		ad_value |= 0x80;       /* set bit 7 */
		control |= 0x2000; /* set bit 13 */
	} else if (0 == strcmp("100MF", envstring)) {
		ad_value |= 0x100;      /* set bit 8 */
		control |= 0x2100; /* set bit 8, 13 */
	} else if (0 == strcmp("1G", envstring)) {
		ge_ad_value |= 0x300;   /* set bit 8, 9 */
		control |= 0x40;        /* set bit 6 */
		control &= 0xdfff;      /* clear bit 13 */
	} else {

		printf("macspeed must be set to 10MH, 10MF, 100MH, "
			   "100MF, or 1G\n");
		return -1;
	}
	
	mdio_write(phy_by_index[index], 4, ad_value);    
	mdio_write(phy_by_index[index], 9, ge_ad_value); 
	mdio_write(phy_by_index[index], 0, control);     
	udelay(5000);
}
#endif

	/*
		Set the Ethernet addresses...
	*/

	top = (ethernet_address[0] << 8) | ethernet_address[1];
	bottom = (ethernet_address[2] << 24) | (ethernet_address[3] << 16) |
	  (ethernet_address[4] << 8) | (ethernet_address[5]);

	/* - EIOA */
	NCP_CALL(ncr_write32(eioaRegion, NCP_EIOA_GEN_CFG_REG_OFFSET(hwPortGmac) + 0x4, bottom));
	NCP_CALL(ncr_write32(eioaRegion, NCP_EIOA_GEN_CFG_REG_OFFSET(hwPortGmac) + 0x8, top));

	/* - Source */
	NCP_CALL(ncr_write32(gmacRegion, 0x304 + gmacPortOffset, bottom));
	NCP_CALL(ncr_write32(gmacRegion, 0x308 + gmacPortOffset, top));

	/* - Unicast */
	NCP_CALL(ncr_write32(gmacRegion, 0x344 + gmacPortOffset, bottom));
	NCP_CALL(ncr_write32(gmacRegion, 0x348 + gmacPortOffset, bottom));
	NCP_CALL(ncr_write32(gmacRegion, 0x34c + gmacPortOffset,
				 ((top & 0xffff) << 16) | (top & 0xffff)));
	NCP_CALL(ncr_write32(gmacRegion, 0x350 + gmacPortOffset, bottom));
	NCP_CALL(ncr_write32(gmacRegion, 0x354 + gmacPortOffset, top));

	/* 
 		Enable stuff. 
	 */
	NCP_CALL(ncr_modify32(gmacRegion, 0x300 + gmacPortOffset, 0x8, 0x8));
	NCP_CALL(ncr_modify32(eioaRegion, 
				NCP_EIOA_GEN_CFG_REG_OFFSET(hwPortGmac) + 0x0, 
				0x00000003, 0x3));
	NCP_CALL(ncr_modify32(gmacRegion, 0x300 + gmacPortOffset, 0x4, 0x4));
	NCP_CALL(ncr_modify32(gmacRegion, 0x330 + gmacPortOffset, 0x3f, 0x09));

NCP_RETURN_LABEL
    return ncpStatus;
}




#define PACKET_ECHO_SIZE 97
static ncp_uint8_t packet_echo[PACKET_ECHO_SIZE];



void initPacketEcho(void)
{
    /*
    0000   da c2 93 8a 17 0c 00 05 1b 00 5f bf 08 00 45 00
    0010   00 54 43 a7 40 00 40 01 f1 a5 c0 a8 42 01 c0 a8
    0020   42 0a 08 00 42 a2 3c a8 00 01 cd 52 5b 59 00 00
    0030   00 00 8a 35 07 00 00 00 00 00 10 11 12 13 14 15
    0040   16 17 18 19 1a 1b 1c 1d 1e 1f 20 21 22 23 24 25
    0050   26 27 28 29 2a 2b 2c 2d 2e 2f 30 31 32 33 34 35
    0060   36
    */
        
    packet_echo[0] = 0xda;
    packet_echo[1] = 0xc2;
    packet_echo[2] = 0x93;
    packet_echo[3] = 0x8a;
    packet_echo[4] = 0x17;
    packet_echo[5] = 0x0c;
    packet_echo[6] = 0x00;
    packet_echo[7] = 0x05;
    packet_echo[8] = 0x1b;
    packet_echo[9] = 0x00;
    packet_echo[10] = 0x5f;
    packet_echo[11] = 0xbf;
    packet_echo[12] = 0x08;
    packet_echo[13] = 0x00;
    packet_echo[14] = 0x45;
    packet_echo[15] = 0x00;

    packet_echo[16] = 0x00;
    packet_echo[17] = 0x54;
    packet_echo[18] = 0x43;
    packet_echo[19] = 0xa7;
    packet_echo[20] = 0x40;
    packet_echo[21] = 0x00;
    packet_echo[22] = 0x40;
    packet_echo[23] = 0x01;
    packet_echo[24] = 0xf1;
    packet_echo[25] = 0xa5;
    packet_echo[26] = 0xc0;
    packet_echo[27] = 0xa8;
    packet_echo[28] = 0x42;
    packet_echo[29] = 0x01;
    packet_echo[30] = 0xc0;
    packet_echo[31] = 0xa8;

    packet_echo[32] = 0x42;
    packet_echo[33] = 0x0a;
    packet_echo[34] = 0x08;
    packet_echo[35] = 0x00;
    packet_echo[36] = 0x42;
    packet_echo[37] = 0xa2;
    packet_echo[38] = 0x3c;
    packet_echo[39] = 0xa8;
    packet_echo[40] = 0x00;
    packet_echo[41] = 0x01;
    packet_echo[42] = 0xcd;
    packet_echo[43] = 0x52;
    packet_echo[44] = 0x5b;
    packet_echo[45] = 0x59;
    packet_echo[46] = 0x00;
    packet_echo[47] = 0x00;

    packet_echo[48] = 0x00;
    packet_echo[49] = 0x00;
    packet_echo[50] = 0x8a;
    packet_echo[51] = 0x35;
    packet_echo[52] = 0x07;
    packet_echo[53] = 0x00;
    packet_echo[54] = 0x00;
    packet_echo[55] = 0x00;
    packet_echo[56] = 0x00;
    packet_echo[57] = 0x00;
    packet_echo[58] = 0x10;
    packet_echo[59] = 0x11;
    packet_echo[60] = 0x12;
    packet_echo[61] = 0x13;
    packet_echo[62] = 0x14;
    packet_echo[63] = 0x15;

    packet_echo[64] = 0x16;
    packet_echo[65] = 0x17;
    packet_echo[66] = 0x18;
    packet_echo[67] = 0x19;
    packet_echo[68] = 0x1a;
    packet_echo[69] = 0x1b;
    packet_echo[70] = 0x1c;
    packet_echo[71] = 0x1d;
    packet_echo[72] = 0x1e;
    packet_echo[73] = 0x1f;
    packet_echo[74] = 0x20;
    packet_echo[75] = 0x21;
    packet_echo[76] = 0x22;
    packet_echo[77] = 0x23;
    packet_echo[78] = 0x24;
    packet_echo[79] = 0x25;

    packet_echo[80] = 0x26;
    packet_echo[81] = 0x27;
    packet_echo[82] = 0x28;
    packet_echo[83] = 0x29;
    packet_echo[84] = 0x2a;
    packet_echo[85] = 0x2b;
    packet_echo[86] = 0x2c;
    packet_echo[87] = 0x2d;
    packet_echo[88] = 0x2e;
    packet_echo[89] = 0x2f;
    packet_echo[90] = 0x30;
    packet_echo[91] = 0x31;
    packet_echo[92] = 0x32;
    packet_echo[93] = 0x33;
    packet_echo[94] = 0x34;
    packet_echo[95] = 0x35;

    packet_echo[96] = 0x36;
}

/*
  -------------------------------------------------------------------------------
  initialize_task_io
*/

int
initialize_task_io(struct eth_device *dev)
{
	ncp_st_t         ncpStatus = NCP_ST_SUCCESS;
	ncp_uint32_t          devNum = 0;


	debug("Resetting device...");
	if (0 != ncp_dev_reset()) {
		printf("Device reset Failed\n");
		return -1;
	}
	debug("done\n");

	debug("Clearing NCA domain bundle...");
	ncp_task_uboot_domain_bundle_clear();
	debug("done\n");


#ifdef ALL_TRACES
	debug("Configuring all.c ...");
	if (0 != ncp_dev_configure(all)) {
		printf("all.c Configuration Failed\n");
		return -1;
	}
	debug("done\n");
#else
	debug("Configuring MME...");
	if (0 != ncp_dev_configure(mme)) {
		printf("MME Configuration Failed\n");
		return -1;
	}
	debug("done\n");

	debug("Configuring PBM...");
	if (0 != ncp_dev_configure(pbm)) {
		printf("PBM Configuration Failed\n");
		return -1;
	}
	debug("done\n");

	debug("Configuring VP...");
	if (0 != ncp_dev_configure(vp)) {
		printf("Virtual Pipeline Configuration Failed\n");
		return -1;
	}
	debug("done\n");

	debug("Configuring NCA...");
	if (0 != ncp_dev_configure(nca)) {
		printf("NCA Configuration Failed\n");
		return -1;
	}
	debug("done\n");

	debug("Configuring EIOA...");
	if (0 != ncp_dev_configure(eioa)) {
		printf("EIOA Configuration Failed\n");
		return -1;
	}
	debug("done\n");
#endif

	NCP_CALL(ncp_config_uboot_attach(devNum, &ncpHdl));
	debug("Attach done ncpHdl=%p\n",ncpHdl);

{
#define RECV_PGIT             0
	ncp_task_tqs_usage_t     params;
	ncp_task_resource_name_t processName;
	int i;
	for (i = 0; i < 8; i++)
		params.useAllocator[i] = FALSE;
#define SHARED_BUFFER_POOL2   2
	params.useAllocator[SHARED_BUFFER_POOL2] = TRUE;
	params.useRxQueue  = TRUE;
	params.useTxQueue0 = TRUE;
	params.useTxQueue1 = TRUE;
	strncpy(processName.name, "TaskRecvLoop", sizeof("TaskRecvLoop"));
	NCP_CALL(ncp_task_tqs_bind(ncpHdl, RECV_PGIT, &params, &processName, &processName, &tqsHdl));
	debug("Bind done, tqsHdl=%p\n", (void*) tqsHdl);
}

	/* enable ipcq */
#define NCP_NCA_ITP_IPCQ_ONLINE00 0x0017FF40
#define NCP_NCA_ITP_IPCQ_VALID00  0x0017FF60
	NCP_CALL(ncr_write32(NCP_REGION_NCAV3_CORE,
				NCP_NCA_ITP_IPCQ_ONLINE00, 0x1));
	NCP_CALL(ncr_write32(NCP_REGION_NCAV3_CORE,
				NCP_NCA_ITP_IPCQ_VALID00, 0x1));

 ncp_return:
	if (NCP_ST_SUCCESS != ncpStatus) {
        printf("ERROR: status=%d\n", ncpStatus);
		lsi_eioa_eth_halt(dev);
		return -1;
	} else 
		return 0;
}

static __maybe_unused
void printTask(ncp_task_header_t *task)
{
    printf("----- task start -------\n");

    printf("task 0x%p\n", task);

    /*
    for (i = 0; i < 32; i++){
        printf("task->params[%d] 0x%x\n",i,task->params[i]);
    }
    */

    printf("task->ID 0x%x\n",task->ID);
    printf("task->templateId 0x%x\n",task->templateId);
    printf("task->headerPool 0x%x\n",task->headerPool);
    printf("task->headerPoolMref 0x%x\n",task->headerPoolMref);
    printf("task->combinedHeader 0x%x\n",task->combinedHeader);
    printf("task->pduSize %d\n",task->pduSize);
    printf("task->pool0 0x%x\n",task->pool0);
    printf("task->pool0Mref 0x%x\n",task->pool0Mref);
    printf("task->ptrCnt 0x%x\n",task->ptrCnt);
    printf("task->pduSegSize0 = %d\n",task->pduSegSize0);
    printf("task->pduSegAddr0 = 0x%llx\n", task->pduSegAddr0);

#if 0
    printf("-- data start --\n");
    int j = 0;
    for (i = 0; i < task->pduSegSize0; i++)
    {
        printf("%04x   ", i);
        for (j = i; j < (i + 16) && j < task->pduSegSize0; j++)
        {
            printf("%02x ", ((char *)task->pduSegAddr0)[j]);
        }
        printf("\n");
        i += 15;
    }
    printf("-- data end --\n");
#endif

    printf("----- task end -------\n");
}


ncp_st_t CreateTask(ncp_task_tqs_hdl_t tqsHdl,
                ncp_uint8_t vpId,
                ncp_task_header_t **ppTask,
				void *packet, int length)
{
    ncp_st_t ncpStatus = NCP_ST_ERROR;
    ncp_task_header_t *task;
    ncp_uint32_t size;
    ncp_uint32_t num;
    void *pData[6];
    int pduSize = length;

    size = 128;
	NCP_CALL(ncp_task_buffer_alloc(tqsHdl, 1, &num, &size, 2, (void **) &task, 0));
	memset(task, 0, size);
	task->params[0] = 0x14;
	task->headerPool = 2;
	task->pool0 = 2;
	task->pduSegSize0 = pduSize;
	task->pduSize = pduSize;

	size = pduSize;
	NCP_CALL(ncp_task_buffer_alloc(tqsHdl, 1, &num, &size, 2, (void **) &pData[0], 0));
	memset(pData[0], 0, size);
	task->pduSize = size;
	memcpy(pData[0], packet, length);
	task->pduSegAddr0 = (ncp_uint64_t) pData[0];

    task->ptrCnt = 1;
    task->combinedHeader = 0;
    task->priority = 0;
    task->ID = 0;
    task->templateId = vpId;

    *ppTask = task;

    return ncpStatus;
 ncp_return:
    printf("myCreateTask: %d\n", ncpStatus);
	return ncpStatus;
}

ncp_st_t myCreateTask(ncp_task_tqs_hdl_t tqsHdl,
                ncp_uint8_t vpId,
                ncp_task_header_t **ppTask)
{
    ncp_st_t ncpStatus = NCP_ST_ERROR;
    ncp_task_header_t *task;
    ncp_uint32_t size;
    ncp_uint32_t num;
    void *pData[6];
    ncp_uint64_t combinedHeader = 0;
    int pduSize = 10;

    size = 128;
    NCP_CALL(ncp_task_buffer_alloc(tqsHdl, 1, &num, &size, 2, (void **) &task, 0));
	memset(task, 0, 128);
	task->params[0] = 0x14;
	task->headerPool = 2;
	task->pool0 = 2;
	task->pool0Mref = 0;
	task->pduSegSize0 = pduSize;
	task->pduSize = pduSize;

	size = pduSize;
	NCP_CALL(ncp_task_buffer_alloc(tqsHdl, 1, &num, &size, 2, (void **) &pData[0], 0));
	task->pduSize = size;
	task->pduSegAddr0 = (ncp_uint64_t) pData[0];

    task->ptrCnt = 1;
    task->combinedHeader = combinedHeader;
    task->priority = 0;
    task->ID = 0;
    task->templateId = vpId;

    *ppTask = task;

    return ncpStatus;
 ncp_return:
    printf("myCreateTask: %d\n", ncpStatus);
	return ncpStatus;
}

int getpid(void){
	return 0;
}

int pthread_mutex_lock(void *mutex){
	return 1;
}

int pthread_mutex_unlock(void *mutex){
	return 1;
}

int pthread_mutex_destroy(void *mutex){

	return 1;
}

extern ncp_st_t                                   
ncp_config_uboot_detach(ncp_hdl_t *ncpHdl);

static void
finalize_task_io(void)
{
	/* enable ipcq */
#define NCP_NCA_ITP_IPCQ_ONLINE00 0x0017FF40
#define NCP_NCA_ITP_IPCQ_VALID00  0x0017FF60
	ncr_write32(NCP_REGION_NCAV3_CORE,
				NCP_NCA_ITP_IPCQ_ONLINE00, 0x0);
	ncr_write32(NCP_REGION_NCAV3_CORE,
				NCP_NCA_ITP_IPCQ_VALID00, 0x0);

	if ( 0 != ncp_task_tqs_unbind(tqsHdl)) {
		printf("Failed to unbind\n");
		return;
	}
	tqsHdl = 0;

	if ( 0 != ncp_config_uboot_detach(ncpHdl)) {
        printf("Failed to detach\n");
		return;
	}	
	ncpHdl = 0;

	initialized = 0;
	return; 
}
 
/*
  ==============================================================================
  ==============================================================================
  Public Interface
  ==============================================================================
  ==============================================================================
*/


/*
  -------------------------------------------------------------------------------
  lsi_eioae_eth_halt
*/

void
lsi_eioa_eth_halt(struct eth_device *dev)
{
	if (0 != initialized)
		finalize_task_io();

	return;
}

/*
  ----------------------------------------------------------------------
  lsi_eioa_eth_init
*/

int
lsi_eioa_eth_init(struct eth_device *dev, bd_t *bd)
{
	if (0 != initialized) 
		return 0;

	if (0 != initialize_task_io(dev)) {
		printf("Failed to Initialize TaskIO Lite!\n");
		return -1;
	}

	if (0 != line_setup(20)) {
		printf("Failed to setup line\n");
		return -1;
	}

#ifdef SNAPSHOT
	take_snapshot(20);
#endif

	initialized = 1;
	return 0;
}

/*
  -------------------------------------------------------------------------------
  lsi_eioa_eth_send
*/

int
lsi_eioa_eth_send(struct eth_device *dev, void *packet, int length)
{
	ncp_st_t         ncpStatus = NCP_ST_SUCCESS;

	if ((tqsHdl == 0) || (ncpHdl == 0))
	{
		printf("NCA is not initialized\n");
		return -1;
	}

	/* NCAv3 code begin */
	ncp_task_send_meta_t    meta_data;
	ncp_uint32_t numSent;

	/* VP id - hardcoded*/
	ncp_uint8_t              vpTxId = 1;
	ncp_task_header_t        *newTask;
	ncpStatus = CreateTask(tqsHdl, vpTxId, &newTask, packet, length);
	if  (ncpStatus == NCP_ST_SUCCESS)
	{
		debug("sending task, length %d\n", length);

		/* Fill meta data fields */
		meta_data.sendDoneFn = NULL;
		meta_data.sendDoneArg = NULL;
		meta_data.freeHeader = TRUE;
		meta_data.freeDataPointers = TRUE;
		meta_data.issueCompletion = FALSE;
		meta_data.taskHeader = newTask;

		ncpStatus = ncp_task_send(tqsHdl, 0, 1, &numSent, &meta_data, TRUE);
		if (ncpStatus != NCP_ST_SUCCESS){
			printf("error sending task, error code: %d\n",ncpStatus);
			goto ncp_return;
		}
	}
	else
	{
		printf("error creating task error code: %d...\n",ncpStatus);
		goto ncp_return;
	}

	return length;

ncp_return:
    if(ncpStatus != NCP_ST_SUCCESS) {
        printf("Failed to send packet. status=%d\n", ncpStatus);
    }
	return 0;
}

/*
  -------------------------------------------------------------------------------
  lsi_eioa_eth_rx
*/

int
lsi_eioa_eth_rx(struct eth_device *dev)
{
    int bytes_received = 0;
	ncp_st_t         ncpStatus = NCP_ST_SUCCESS;

	/* NCAv3 code begin */
    ncp_task_free_meta_t     meta_task;

	/* VP id - hardcoded*/
	ncp_task_header_t        *task;
	ncp_uint32_t             numRx;

	if ((tqsHdl == 0) || (ncpHdl == 0))
	{
		printf("lsi_eioa_eth_rx: NCA is not initialized\n");
		return -1;
	}


	ncpStatus = ncp_task_recv(tqsHdl, 1, &numRx, &task, FALSE);
	if(NCP_ST_TASK_RECV_QUEUE_EMPTY == ncpStatus){
		return 0;
	}
	else if (ncpStatus == NCP_ST_SUCCESS){
		bytes_received = task->pduSegSize0;
		debug("received %d tasks %d bytes \n",numRx ,bytes_received);
		meta_task.freeDoneFn = NULL;
		meta_task.freeDoneArg = NULL;
		meta_task.task = task;
		meta_task.freeHeader = TRUE;
		meta_task.issueCompletion = FALSE;
		ncp_uint32_t numFree = 0;
		if (0 == loopback && 0 == rxtest)
			/* copy the received packet to the up layer buffer */
			net_process_received_packet((void *)task->pduSegAddr0, bytes_received);
		ncpStatus = ncp_task_free(tqsHdl, 1, numRx, &numFree, &meta_task, TRUE);
		if (ncpStatus != NCP_ST_SUCCESS){
			printf("free memory error, status %d freed %d\n",ncpStatus,numFree);
		}

	}
	else
	{
		printf("receive error. status code %d", ncpStatus);
		goto ncp_return;
	}
	return bytes_received;

ncp_return:
	if (NCP_ST_SUCCESS != ncpStatus) {
		printf("%s:%d - NCP_CALL() Failed: 0x%08x\n",
		       __FILE__, __LINE__, ncpStatus);
	}

	return -1;
}

/*
  -------------------------------------------------------------------------------
  lsi_eioa_receive_test
*/

void
lsi_eioa_receive_test(struct eth_device *dev)
{
	long int packets_received = 0;

	eth_halt();

	if (0 != eth_init()) {
        rxtest = 0;
		eth_halt();
		return;
	}

	for (;;) {
        int packet_len = eth_rx();
		if (0 != packet_len) {
			++packets_received;
        }

		if (ctrlc())
			break;
	}

   	rxtest = 0;
	eth_halt();
	printf("EIOA Receive Test Interrupted.  Received %ld packets.\n",
	       packets_received);
	return;
}

/*
  -------------------------------------------------------------------------------
  lsi_eioa_loopback_test
*/

void __maybe_unused
lsi_eioa_loopback_test(struct eth_device *dev)
{
	return;
}
