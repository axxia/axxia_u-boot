/*
 *  Copyright (C) 2015 Intel Corporation
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

#ifndef UBOOT
#include <stdio.h>
#include "ncp.h"
#include "ncp_pvt.h"
#include "ncp_sysmem_ext.h"
#include "ncp_sysmem_lsiphy.h"
#include "regs/ncp_ddr_regs.h"
#include "regs/ncp_ddr_reg_defines.h"
#else
#define ncp_usleep(n) udelay(n)
#endif



#define NCP_SM_ENCODE_RTT_NOM(val)  \
    ( ( (val & 0x1) << 2 ) |  /* a2 */ \
      ( (val & 0x2) << 5 ) |  /* a6 */ \
      ( (val & 0x4) << 7 ) )  /* a9 */
      

#define NCP_SM_ENCODE_DRV_IMP(val)  \
    ( ( (val & 0x1) << 1 ) |  /* a1 */ \
      ( (val & 0x2) << 4 ) )  /* a5 */ 

extern ncp_uint8_t tRFC_vals_533[];
extern ncp_uint8_t tRFC_vals_667[];


ncp_st_t
ncp_cm_dram_init(
    ncp_dev_hdl_t dev,
    ncp_uint32_t  num_cmem)
{
    ncp_st_t            ncpStatus = NCP_ST_SUCCESS;
    ncp_uint32_t        nodeId;
    ncp_region_id_t     ctrlRegion;
    ncp_uint32_t        memId;

    ncp_uint32_t        cm_nodes[2]= {8, 9};
    ncp_uint32_t        testCtlReg = 0;
    ncp_uint32_t        ddrStatReg = 0;

    ncp_ddr_CFG_NTEMC_HW_TEST_CTRL_r_t *pTestCtlReg = 
                    (ncp_ddr_CFG_NTEMC_HW_TEST_CTRL_r_t *) &testCtlReg;

    ncp_ddr_CFG_NTEMC_DDR_STATUS_r_t   *pDdrStatReg = 
                    (ncp_ddr_CFG_NTEMC_DDR_STATUS_r_t *) &ddrStatReg;

    NCP_COMMENT("Initialize all of tree memory");


    pTestCtlReg->hwmeminit = 1;
    pTestCtlReg->test_patt = 0;   /* user test-pattern registers */
    pTestCtlReg->test_mode = 0;   /* all writes then all reads */
    pTestCtlReg->num_ops   = 32;  

    for (memId = 0; memId < num_cmem; memId++)
    {
        nodeId = cm_nodes[memId];
        ctrlRegion = NCP_REGION_ID(nodeId, 9);

        /* set hw_test data pattern to all zeros */
        ncr_write32( ctrlRegion, 
                NCP_DDR_CFG_NTEMC_HW_TEST_DATA_UPR, 0);
        ncr_write32( ctrlRegion, 
                NCP_DDR_CFG_NTEMC_HW_TEST_DATA_LWR, 0);

        ncr_write32( ctrlRegion, 
                             NCP_DDR_CFG_NTEMC_HW_TEST_CTRL, testCtlReg);


    }

    pDdrStatReg->meminitdone = 1; 

    for (memId = 0; memId < num_cmem; memId++)
    {
        nodeId = cm_nodes[memId];
        ctrlRegion = NCP_REGION_ID(nodeId, 9);

        ncr_poll(ctrlRegion, NCP_DDR_CFG_NTEMC_DDR_STATUS,
                ddrStatReg, ddrStatReg, 1000, 100000);

    }

NCP_RETURN_LABEL
    return ncpStatus;

}


ncp_st_t
ncp_cm_controller_init(
        ncp_dev_hdl_t dev,
        ncp_uint32_t  smId,
        ncp_sm_parms_t *parms)
{
    ncp_st_t   ncpStatus = NCP_ST_SUCCESS;
    ncp_region_id_t  ctlRegion;
    ncp_region_id_t  axiRegion;
    ncp_uint32_t     value;

    ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t  ddr_ctrl = {0};
    ncp_ddr_CFG_NTEMC_DRAM_TYPE_r_t dram_type = {0};
    ncp_ddr_CFG_NTEMC_SPECVAL1_r_t cfg_spec1 = {0};
    ncp_ddr_CFG_NTEMC_SPECVAL2_r_t cfg_spec2 = {0};
    ncp_ddr_CFG_NTEMC_SPECVAL3_r_t cfg_spec3 = {0};
    ncp_ddr_CFG_NTEMC_SPECVAL4_r_t cfg_spec4 = {0};
    ncp_ddr_CFG_NTEMC_DFI_TIMING1_r_t dfi_time1 = {0};
    ncp_ddr_CFG_NTEMC_DFI_TIMING2_r_t dfi_time2 = {0};
    ncp_ddr_CFG_NTEMC_DFI_TIMING3_r_t dfi_time3 = {0};
    ncp_ddr_CFG_NTEMC_DFI_TIMING4_r_t dfi_time4 = {0};
    ncp_ddr_CFG_NTEMC_DFI_TIMING5_r_t dfi_time5 = {0};
    ncp_ddr_CFG_NTEMC_MRS_r_t ddr_cmd = {0};
    ncp_ddr_CFG_NTEMC_ISSUE_MRS_r_t cmd_issue = {0};
    ncp_ddr_CFG_NTEMC_ECC_CTRL_r_t ecc_ctrl = {0};


    ncp_uint32_t cmemId;
    ncp_uint32_t rttNom, rttWr, drvImp;
    ncp_uint32_t tmp32;
    ncp_uint32_t cl, al, cwl, wl;
    ncp_uint8_t    *tRFC_vals;
    ncp_bool_t   is667 = FALSE;
    ncp_bool_t   need_added_cycle_workaround;


    if (smId < NCP_SYSMEM_NUM_NODES) {
        NCP_CALL(NCP_ST_SYSMEM_INVALID_ID);
    }

    cmemId = smId - NCP_SYSMEM_NUM_NODES;
    NCP_COMMENT( "treemem %d ddr controller init", cmemId);


    if ((parms->version == NCP_CHIP_ACP34xx) ||
        (parms->version == NCP_CHIP_ACP32xx))  {
        is667 = FALSE;
        tRFC_vals = tRFC_vals_533;
        /*
         * X1/X2 controller did not support adding extra cycles 
         * between read/write commands. When this flag is true 
         * we implement a workaround to achieve the same result.
         */
        need_added_cycle_workaround = TRUE;

    } else {
        tRFC_vals = tRFC_vals_667;
        is667 = TRUE;
        need_added_cycle_workaround = FALSE;
    }


    ctlRegion = NCP_REGION_ID(sm_nodes[smId], NCP_TREEMEM_TGT_DDR);
    axiRegion = NCP_REGION_ID(sm_nodes[smId], NCP_TREEMEM_TGT_AXI);
    
    /*
     * Main control for Tree Engine DDR controller
     */
    if (need_added_cycle_workaround == FALSE)  {
        /* this controller supports added cycles, just set the value ! */
        ddr_ctrl.add_r2w = parms->min_ctrl_roundtrip_delay ;
    }
    ddr_ctrl.idle_mode = 1; 
    ddr_ctrl.cmdhist_ena = 1;
    ddr_ctrl.auto_zq = 0;
    ddr_ctrl.zq_per = 3; 
    ddr_ctrl.zq_intv = 1; 
    ddr_ctrl.odt_prof = 2; 
    ddr_ctrl.byp_ena = 1; 
    ncr_write32( ctlRegion,
                         NCP_DDR_CFG_NTEMC_DDR_CTRL,
                         *(ncp_uint32_t *)&ddr_ctrl);

    /* 
     *  axi cfg. 
     *  RDL does not match script.  Just hard code 
     */  
    tmp32 = 0x03BFDEF1;
    ncr_write32( axiRegion,
             0x00000004,
             *(ncp_uint32_t *)&tmp32);


    /*
     *  Density and CL/AL/CWL settings for the target DRAM
     */
    cl = parms->CAS_latency;
    al = cl - 1;
    cwl = parms->CAS_write_latency;

    /* rl = cl + al; */
    wl = cwl + al;

    dram_type.type_cl = cl;
    dram_type.type_al = al;
    dram_type.type_cwl = cwl;
    if (need_added_cycle_workaround)  {
        dram_type.type_cwl -= parms->min_ctrl_roundtrip_delay;
    }

    /*
     * treemem row/column settings
     * (enumerated values in parenthesis) 
     *
     *  Density      Width      row bits    col bits 
     *  512Mb (1)     x8 (1)      13 (2)       10 (1)
     *  512Mb        x16 (2)      12 (1)       10   
     *    1Gb (2)     x8          14 (3)       10  
     *    1Gb        x16          13           10 
     *    2Gb (3)     x8          15 (4)       10     
     *    2Gb        x16          14           10    
     *    4Gb (4)     x8          16 (5)       10   
     *    4Gb        x16          15           10  
     *    8Gb (5)     x8          16           11 (2)
     *    8Gb        x16          16           10
     *
     *
     */

    if ( 5 == parms->sdram_device_density) {
        dram_type.type_col = 3 - parms->sdram_device_width;
        dram_type.type_row = 5;
    } else {
        dram_type.type_col = 1;
        dram_type.type_row = 
            2 + parms->sdram_device_density - parms->sdram_device_width;
    }


    dram_type.type_ba = 1;
    dram_type.ddr_type = 1;
    dram_type.type_wradj = 3;
    dram_type.type_rdadj = 0;
    ncr_write32( ctlRegion,
                         NCP_DDR_CFG_NTEMC_DRAM_TYPE,
                        *(ncp_uint32_t *) &dram_type);
    /*
     *  First group of DRAM timing parameters  
     */
    cfg_spec1.trefi = is667 ? 0x144E : 0x103E;
    cfg_spec1.trfc = tRFC_vals[parms->sdram_device_density];
    cfg_spec1.trp = (parms->version == 0) ? 0x1f : cl;

    if (parms->high_temp_dram) {
        /* double refresh rate (half the interval) for high temp */
        cfg_spec1.trefi >>= 1;
    }

    ncr_write32( ctlRegion,
                         NCP_DDR_CFG_NTEMC_SPECVAL1,
                        *(ncp_uint32_t *) &cfg_spec1);

    /*
     *  Second group of DRAM timing parameters  
     */
    if (is667) {
        cfg_spec2.twr = 10 ;
        if (need_added_cycle_workaround)  {
            cfg_spec2.twr +=  parms->min_ctrl_roundtrip_delay;
        }
        cfg_spec2.twtr = cfg_spec2.trtp = 5;
        if ( ( 5 == parms->sdram_device_density ) || 
             ( 2 == parms->sdram_device_width) ) {
            cfg_spec2.tfaw = 0x22;
        } else {
            cfg_spec2.tfaw = 0x19 ;
        }
        cfg_spec2.trc  = 0x22 ;
        cfg_spec2.tras = 0x19 ;
    } else {
        cfg_spec2.twr = 8;
        if (need_added_cycle_workaround)  {
            cfg_spec2.twr +=  parms->min_ctrl_roundtrip_delay;
        }
        cfg_spec2.twtr = cfg_spec2.trtp = 4;
        if ( ( 5 == parms->sdram_device_density ) || 
             ( 2 == parms->sdram_device_width) ) {
            cfg_spec2.tfaw = 0x1b;
        } else {
            cfg_spec2.tfaw = 0x14;
        }
        cfg_spec2.trc  = 0x1B;
        cfg_spec2.tras = 0x14;

    }

    ncr_write32( ctlRegion,
                         NCP_DDR_CFG_NTEMC_SPECVAL2,
                        *(ncp_uint32_t *) &cfg_spec2);

    /*
     *  Third group of DRAM timing parameters  
     */
    if (is667) {
        cfg_spec3.trrd = 2 + (parms->sdram_device_width * 2 );
        cfg_spec3.tmod = 0xf;
        cfg_spec3.tmrd = 5;
        cfg_spec3.twlmrd = 0x32;
        cfg_spec3.twldqsen = 0x20;
    } else {
        cfg_spec3.trrd = 2 + (parms->sdram_device_width * 2 );
        cfg_spec3.tmod = 0xC;
        cfg_spec3.tmrd = 4;
        cfg_spec3.twlmrd = 0x28;
        cfg_spec3.twldqsen = 0x19;
    }
    ncr_write32( ctlRegion,
                         NCP_DDR_CFG_NTEMC_SPECVAL3,
                        *(ncp_uint32_t *) &cfg_spec3);

    /*
     *  Fourth group of DRAM timing parameters  
     */
    if (is667) { 
        cfg_spec4.zqcal_per = 0x00a0;
        cfg_spec4.scrub_per = 0x0067;
    } else {
        cfg_spec4.zqcal_per = 0x0080;
        cfg_spec4.scrub_per = 0x0052;
    }
    /* 
     * ZQCS interval is specified in refresh intervals 
     * TODO: this calculation assumes 667MHz DDR clock
     */
    tmp32 = parms->zqcs_interval * 667 / cfg_spec1.trefi;
    if (tmp32 > 0xffff) tmp32 = 0xffff;
    cfg_spec4.zqcal_per = tmp32;
    ncr_write32( ctlRegion,
                         NCP_DDR_CFG_NTEMC_SPECVAL4,
                        *(ncp_uint32_t *) &cfg_spec4);
    /*
     *  First group of DFI timing parameters: controller to PHY 
     *  timing parameters for reads and writes
     */
    dfi_time1.tctrl_dly = 0;
    dfi_time1.tphy_wrlat = wl - 1;
    dfi_time1.trddataen = 0;
    dfi_time1.tphy_rdlat = 0;
    dfi_time1.reserved0 = 0x176;
    dfi_time1.tclk_dis = 0;
    dfi_time1.tclk_ena = 0;
    ncr_write32( ctlRegion,
                         NCP_DDR_CFG_NTEMC_DFI_TIMING1,
                        *(ncp_uint32_t *) &dfi_time1);

    /*
     *  Second group of DFI timing parameters: controller to PHY 
     *  timing parameters for for update requests and DRAM clk control
     */
    dfi_time2.tctlupd_intv = 0x100;
    dfi_time2.tctlupd_min = 7;
    dfi_time2.tctlupd_max = 0xF;
    dfi_time2.tphyupd_rsp = 0x100;
    ncr_write32( ctlRegion,
                         NCP_DDR_CFG_NTEMC_DFI_TIMING2,
                        *(ncp_uint32_t *) &dfi_time2);

    /*
     *  Third group of DFI timing parameters: controller training 
     *  state machines to PHY training state machines.
     * 
     *  Set the timeout to the max value
     */
    dfi_time3.trdlvl_max = 0xffffffff;
    ncr_write32( ctlRegion,
                         NCP_DDR_CFG_NTEMC_DFI_TIMING3,
                        *(ncp_uint32_t *) &dfi_time3);

    dfi_time4.twrlvl_max = 0xffffffff;
    ncr_write32( ctlRegion,
                         NCP_DDR_CFG_NTEMC_DFI_TIMING4,
                        *(ncp_uint32_t *) &dfi_time4);

    dfi_time5.trdlvl_en = 5;
    dfi_time5.twrlvl_en = 5;
    dfi_time5.trdlvl_rr = 50;
    dfi_time5.twrlvl_ww = 50;
    ncr_write32( ctlRegion,
                         NCP_DDR_CFG_NTEMC_DFI_TIMING5,
                        *(ncp_uint32_t *) &dfi_time5);
    /*
     * details control for ecc behavior
    */
    ecc_ctrl.ecc_err_mode = 0; 
    ecc_ctrl.ecc_mode = 0; 
    ecc_ctrl.seldatabit = 0; 
    ecc_ctrl.seleccbit = 0;
    ncr_write32( ctlRegion,
                         NCP_DDR_CFG_NTEMC_ECC_CTRL,
                        *(ncp_uint32_t *) &ecc_ctrl);
     
    /*
     * Engine DDR controller : Take out of idle.
     */
    ncr_read32( ctlRegion, NCP_DDR_CFG_NTEMC_DDR_CTRL, &value);
    SV(ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t, idle_mode,   0);
    ncr_write32( ctlRegion, NCP_DDR_CFG_NTEMC_DDR_CTRL, value);

    /*
     * Engine DDR controller : DDR3 to reset
     */
    SV(ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t, ddr_rstn,   1);
    ncr_write32( ctlRegion, NCP_DDR_CFG_NTEMC_DDR_CTRL, value);
    ncp_usleep(500);

    /*
     * Engine DDR controller : DDR3 clk enable 
     *
     * NOTE: BZ44512  
     * - refresh enable has been moved until after PHY training
     */
    ncr_read32( ctlRegion, NCP_DDR_CFG_NTEMC_DDR_CTRL, &value);
    SV(ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t, ddr_cke,   1);
    ncr_write32( ctlRegion, NCP_DDR_CFG_NTEMC_DDR_CTRL, value);


    /*
     * issue commands to the ddr
     */

    /* MR2
     *    a5a4a3 : CWL
     */
    rttWr = parms->per_mem[cmemId].sdram_rtt_wr[0];
    ddr_cmd.mrs_adr = (rttWr << 9) | (cwl - 5) << 3;
    ddr_cmd.mrs_badr = 2;
    ddr_cmd.mrs_cmd = 0;  
    ddr_cmd.mrs_cke = 1;  
    ncr_write32( ctlRegion,
                         NCP_DDR_CFG_NTEMC_MRS,
                        *(ncp_uint32_t *) &ddr_cmd);
    /* issue command */
    cmd_issue.init_cmd = 1;
    ncr_write32( ctlRegion,
                         NCP_DDR_CFG_NTEMC_ISSUE_MRS,
                        *(ncp_uint32_t *)&cmd_issue);

    /* MR3 */
    ddr_cmd.mrs_adr = 0;
    ddr_cmd.mrs_badr = 3;
    ddr_cmd.mrs_cmd = 0;  
    ddr_cmd.mrs_cke = 1;  
    ncr_write32( ctlRegion,
                         NCP_DDR_CFG_NTEMC_MRS,
                        *(ncp_uint32_t *) &ddr_cmd);
    /* issue command */
    ncr_write32( ctlRegion,
                         NCP_DDR_CFG_NTEMC_ISSUE_MRS,
                        *(ncp_uint32_t *)&cmd_issue);

    /* MR1 */
    value = 0;  /* DLL enabled */
    rttNom = parms->per_mem[cmemId].sdram_rtt_nom[0];
    value |= NCP_SM_ENCODE_RTT_NOM(rttNom);
    drvImp = parms->per_mem[cmemId].sdram_data_drv_imp[0];
    value |= NCP_SM_ENCODE_DRV_IMP(drvImp);
    value |= ( 1 << 3) ;    /* AL = CL-1 */

    parms->cmemMR1[cmemId] = value;

    ddr_cmd.mrs_adr = value;
    ddr_cmd.mrs_badr = 1;
    ddr_cmd.mrs_cmd = 0;  
    ddr_cmd.mrs_cke = 1;  
    ncr_write32( ctlRegion,
                         NCP_DDR_CFG_NTEMC_MRS,
                        *(ncp_uint32_t *) &ddr_cmd);
    /* issue command */
    ncr_write32( ctlRegion,
                         NCP_DDR_CFG_NTEMC_ISSUE_MRS,
                        *(ncp_uint32_t *)&cmd_issue);


    /* MR0 */
    if (cl < 12) {
        ddr_cmd.mrs_adr = 0x1900 | ((cl - 4) << 4);
    } else {
        ddr_cmd.mrs_adr = 0x1904 | ((cl - 12) << 4);
    }
    ddr_cmd.mrs_badr = 0;
    ddr_cmd.mrs_cmd = 0;  
    ddr_cmd.mrs_cke = 1;  
    ncr_write32( ctlRegion,
                         NCP_DDR_CFG_NTEMC_MRS,
                        *(ncp_uint32_t *) &ddr_cmd);
    /* issue command */
    ncr_write32( ctlRegion,
                         NCP_DDR_CFG_NTEMC_ISSUE_MRS,
                        *(ncp_uint32_t *)&cmd_issue);

    /* zqcalinit */
    ddr_cmd.mrs_adr = 0x0400;
    ddr_cmd.mrs_badr = 0;
    ddr_cmd.mrs_cmd = 6;  
    ddr_cmd.mrs_cke = 1;  
    ncr_write32( ctlRegion,
                         NCP_DDR_CFG_NTEMC_MRS,
                        *(ncp_uint32_t *) &ddr_cmd);
    /* issue command */
    ncr_write32( ctlRegion,
                         NCP_DDR_CFG_NTEMC_ISSUE_MRS,
                        *(ncp_uint32_t *)&cmd_issue);
    /*
     * Sleep for 10 milliseconds waiting for SDRAM init 
     * to complete
     */
    ncp_usleep(10000);  

ncp_return:
    return ncpStatus;
}


