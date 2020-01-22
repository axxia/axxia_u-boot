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

#ifdef __UBOOT__
#include <common.h>
#include "ncp_sysmem_ext.h"
#include "ncp_sysmem_lsiphy.h" /* for macros and stuff mainly */
#include "ncp_sysmem_synopphy.h"
#include "ncp_axis_apb2ser3_regions.h"
#include "ncp_syscon_xlf_regs.h"
#include "ncp_syscon_xlf_reg_defines.h"
#else
#include <stdio.h>
#include "ncp.h"
#include "ncp_pvt.h"
#include "ncp_sysmem_ext.h"
#include "ncp_sysmem_lsiphy.h" /* for macros and stuff mainly */
#include "ncp_sysmem_synopphy.h"
#include "../pll/ncp_axis_apb2ser3_regions.h"
#include "../ncp/regs/ncp_syscon_xlf_regs.h"
#include "../ncp/regs/ncp_syscon_xlf_reg_defines.h"
#endif

extern ncp_uint16_t ddr3refresh_parms_by_density[7];
extern ncp_uint32_t ddr4refresh_parms_by_density_1x[7];
extern ncp_uint32_t ddr4refresh_parms_by_density_2x[7];
extern ncp_uint32_t ddr4refresh_parms_by_density_4x[7];

extern ncp_uint32_t
ncp_ps_to_clk(
              ncp_uint32_t tck_ps,
              ncp_uint32_t num_ps);

extern ncp_st_t
ncp_sm_ddr4_mc_reg_dump(
                        ncp_dev_hdl_t   dev,
                        ncp_uint32_t    smNode);

ncp_st_t
ncp_sm_ddr4_phy_reg_dump(
                         ncp_dev_hdl_t   dev,
                         ncp_uint32_t    smNode);

extern ncp_st_t
ncp_sm_ddr4_phy_training_error_check(
                                     ncp_dev_hdl_t   dev,
                                     ncp_uint32_t    smNode);

ncp_st_t
ncp_sm_ddr4_pre_retention_restore(
                                  ncp_dev_hdl_t   dev,
                                  ncp_uint32_t    smNode,
                                  ncp_sm_parms_t *parms,
                                  ncp_common_timing_parameters_t *ctm,
                                  ncp_uint32_t *preRetentionZQ,
                                  ncp_bool_t latchEnable)
{
    ncp_st_t	ncpStatus = NCP_ST_SUCCESS;
    ncp_region_id_t 	phyReg 	= NCP_REGION_ID(smNode, NCP_SYSMEM_TGT_PHY);
    unsigned int		i = 0;
    ncp_phy_ZQ0DR_5600_t regZQ0DR = {0};

    /* Restore ZQ calibrated values (pre-data-retention).
     *
     * Save 28-bit info on Impedance Controller Impedance data.
     * 27:21 is pull-up on-die termination
     * 20:14 is pull-down on-die impedance
     * 13:7 is pull-up output impedance
     * 6:0 is pull-down output impedance
     */
    for (i = 0; i < 4; i++)
    {
        /* based on number of islands */
        ncr_read32(phyReg, (NCP_PHY_ZQ0DR_5600 + (0x10 * i)), (ncp_uint32_t *)&regZQ0DR);
        if (latchEnable == TRUE)
        {
            regZQ0DR.zdata = preRetentionZQ[i];
            regZQ0DR.odt_zden = 0x1; /* termination override enable */
            regZQ0DR.drv_zden = 0x1; /* drive-strength override enable */
            /* SAX1-2064_CHK leave below as power-up-default */
            regZQ0DR.zsegbyp = 0x0; /* when set bypass current calib segment during auto cal */
        }
        else
        {
            regZQ0DR.odt_zden = 0x0; /* termination override enable */
            regZQ0DR.drv_zden = 0x0; /* drive-strength override enable */
            /* SAX1-2064_CHK leave below as power-up-default */
            regZQ0DR.zsegbyp = 0x0; /* when set bypass current calib segment during auto cal */
        }
        ncr_write32(phyReg, (NCP_PHY_ZQ0DR_5600 + (0x10 * i)), *((ncp_uint32_t *)&regZQ0DR));
    }

    NCP_RETURN_LABEL
        return ncpStatus;
}

ncp_st_t
ncp_sm_ddr4_mc_sf_mode(
                       ncp_dev_hdl_t   dev,
                       ncp_uint32_t    smNode,
                       ncp_sm_parms_t *parms,
                       ncp_common_timing_parameters_t *ctm,
                       ncp_bool_t enable)
{
    ncp_st_t	        ncpStatus = NCP_ST_SUCCESS;
    ncp_region_id_t     ctlReg = NCP_REGION_ID(smNode, NCP_SYSMEM_TGT_DENALI);

    ncp_denali_DENALI_CTL_48_5600_t reg48 = {0};
    ncp_denali_DENALI_CTL_348_5600_t reg348 = {0};
    unsigned int		            tmp = 0;

    /* Program MC to put DRAM into self-refresh mode. 
     * via denali regs or PUB DCU. SAX1-2064_CHK.
     * enable = TRUE: put into self-refresh
     * enable = FALSE: pull out of self-refresh
     */
    if (enable == TRUE)
    {
        ncr_read32(ctlReg, NCP_DENALI_CTL_382_5600, &tmp);
        /* 
         * set 19th bit LP_CTRL_PATH_EN	
         * Set to 1 to allow the address/ctl portion of the PHY to got into low power when requested by memory controller. 
         * Typically, this should remain as zero so that the memory controller can continue performing refreshes in the 
         * active power-down and pre-charge power-down modes.
         *
         * set also bit 29 PERF_MON_EN to 1 to enable the performance logic and associated clock (not needed- tb only)
         */
        tmp |= 0x00080000;
        ncr_write32(ctlReg, NCP_DENALI_CTL_382_5600, tmp);
    }

    ncr_read32(ctlReg, NCP_DENALI_CTL_382_5600, &tmp);
    dbgprintf("CTL_382 reads 0x%x\n",tmp);

    /* DENALI_CTL_48 */
    ncr_read32(ctlReg, NCP_DENALI_CTL_48_5600, (ncp_uint32_t *)&reg48);
    /* LP_CMD is 7:0. It is a Low Power Software Command request interface.
     * Bit 0: controls exit
     * Bit 1: controls entry
     * Bit 2:4 defines low-power-state
     * Bit 5: controls memory clock gating
     * Bit 6: controls Ctrl clock gating
     * Bit 7: controls lock
     * WR_only
     */
    reg48.lp_cmd = (enable == TRUE) ? 10 : 9;
    /*reg48.lpi_pd_wakeup = 0;*/ /* (16) number of DFI clocks that PHY will be idle when mem is power-down mode */
    /*reg48.lpi_sr_wakeup = 2;*/ /* (64) number of DFI clocks that PHY will be idle when mem is self-refresh mode */
    ncr_write32(ctlReg, NCP_DENALI_CTL_48_5600, *((ncp_uint32_t *)&reg48));

    /* DENALI_CTL_348 */

    /* LP_STATE 21:16 is Low Power state status parameter
     * Bit 4:0 [20:16] indicate current low-power state
     * Bit 5 [21] indicates that status bits are valid
     * RD_ONLY
     */
    ncpStatus = (ncr_poll(ctlReg, NCP_DENALI_CTL_348_5600,  0x200000,  0x200000,  1000,  10000));
    if (ncpStatus == NCP_ST_POLL_TIMEOUT)
    {
        errprintf("LP_STATE bit 5 status never became valid in poll interval\n");
        NCP_CALL(NCP_ST_POLL_TIMEOUT);
    }
    ncr_read32(ctlReg, NCP_DENALI_CTL_348_5600, (ncp_uint32_t *)&reg348);
    if (reg348.lp_state & 0x20)
    {
        dbgprintf("LP state of DRAM memories is ");
        switch (reg348.lp_state & 0x1f)
        {
            case 0:
                dbgprintf("IDLE\n");
            break;
            case 1:
                dbgprintf("Active Power-Down\n");
            break;
            case 2:
                dbgprintf("Active Power-Down with Memory Clock Gating\n");
            break;
            case 3:
                dbgprintf("Pre-Charge Power-Down\n");
            break;
            case 4:
                dbgprintf("Pre-Charge Power-Down with Memory Clock Gating\n");
            break;
            case 5:
                dbgprintf("Self-Refresh\n");
            break;
            case 6:
                dbgprintf("Self-Refresh with Memory Clock Gating\n");
            break;
            case 7:
                dbgprintf("Self-Refresh with Memory and Controller Clock Gating\n");
            break;
            default:
                ;
        }

        if (((reg348.lp_state & 0x1f) != 5) && ((reg348.lp_state & 0x1f) != 0))
        {
            errprintf("Check on LP State Status. Reading 0x%x expected 0x5 (self-refresh) OR 0x0 (idle)\n", (reg348.lp_state & 0x1f));
        }
        else
        {
            dbgprintf("State entry/exit confirmed by LP State Status = 0x%x (0x5 Self-Refresh, 0x0 Idle)\n", (reg348.lp_state & 0x1f));
        }
    }
    else
    {
        errprintf("LP_STATE Status readout is invalid i.e bit 5 did not get set\n");
        NCP_CALL(NCP_ST_ERROR);
    }

    NCP_RETURN_LABEL
        return ncpStatus;
}

ncp_st_t
ncp_sm_ddr4_pre_retention_save(
                               ncp_dev_hdl_t   dev,
                               ncp_uint32_t    smNode,
                               ncp_sm_parms_t *parms,
                               ncp_common_timing_parameters_t *ctm,
                               ncp_uint32_t *preRetentionZQ)
{
    ncp_st_t	ncpStatus = NCP_ST_SUCCESS;
    ncp_region_id_t 	phyReg 	= NCP_REGION_ID(smNode, NCP_SYSMEM_TGT_PHY);
    unsigned int		i = 0;
    ncp_phy_ZQ0DR_5600_t regZQ0DR = {0};

    /* Read ZQ calibrated values (pre-data-retention).
     *
     * Save 28-bit info on Impedance Controller Impedance data.
     * 27:21 is pull-up on-die termination
     * 20:14 is pull-down on-die impedance
     * 13:7 is pull-up output impedance
     * 6:0 is pull-down output impedance
     */
    for (i = 0; i < 4; i++)
    {
        /* based on number of islands */
        ncr_read32(phyReg, (NCP_PHY_ZQ0DR_5600 + (0x10 * i)), (ncp_uint32_t *)&regZQ0DR);
        preRetentionZQ[i] = regZQ0DR.zdata;
    }

    NCP_RETURN_LABEL
        return ncpStatus;
}

ncp_st_t
ncp_sm_ddr4_phy_self_refresh_io_control(
                                        ncp_dev_hdl_t   dev,
                                        ncp_uint32_t    smNode,
                                        ncp_sm_parms_t *parms,
                                        ncp_common_timing_parameters_t *ctm,
                                        ncp_uint8_t ioValue)
{
    ncp_st_t	ncpStatus = NCP_ST_SUCCESS;
    ncp_region_id_t 	phyReg 	= NCP_REGION_ID(smNode, NCP_SYSMEM_TGT_PHY);
    unsigned int		tmp = 0;

    /* Control of IO of PHY- appropriate DFI signals to maintain self-refresh 
     * set GPR0 (retain the signals on the PHY DDR interface) 
     * assert PHY_TOP data retention enable signals ret_en/ret_en_i/ret_en_n_i 
     * set PHY 0x30 which is GPR0 */
    ncr_read32(phyReg, NCP_PHY_GPR0_5600, &tmp);
    tmp = ioValue;
    ncr_write32(phyReg, NCP_PHY_GPR0_5600, tmp);

    /* any wait SAX1-2064_CHK */

    NCP_RETURN_LABEL
        return ncpStatus;
}

ncp_st_t
ncp_sm_ddr4_phy_pd_control(
                           ncp_dev_hdl_t   dev,
                           ncp_uint32_t    smNode,
                           ncp_sm_parms_t *parms,
                           ncp_common_timing_parameters_t *ctm)
{
    ncp_st_t	ncpStatus = NCP_ST_SUCCESS;
    ncp_region_id_t 	phyReg 	= NCP_REGION_ID(smNode, NCP_SYSMEM_TGT_PHY);
    ncp_phy_DX0GCR1_5600_t regDX0GCR1 = {0};
    ncp_phy_DX0GCR1_5600_t regDX0GCR1_rd = {0};
    unsigned int		i = 0;
#if 0
    ncp_phy_DX0GCR3_5600_t regDX0GCR3 = {0};
    ncp_phy_DX0GCR4_5600_t regDX0GCR4 = {0};
    ncp_phy_DX0GCR5_5600_t regDX0GCR5 = {0};
#endif


    /* Remove power (power-off). Is this applicable ?
     * Continue to stay in power-off mode. Is this applicable ?
     * Restore power (power-on). Is this applicable ?
     */

    /* Power Down OFF in PHY */
    for (i = 0; i < 9; i++)
    {
        /* DX0GCR1 .. DX8GCR1 */
        ncr_read32(phyReg, (NCP_PHY_DX0GCR1_5600 + (0x100 * i)), (ncp_uint32_t *)&regDX0GCR1_rd);
        regDX0GCR1.dxpddmode = 0x0000;
        regDX0GCR1.dxpdrmode = 0x0000;
        ncr_write32(phyReg, (NCP_PHY_DX0GCR1_5600 + (0x100 * i)), *((ncp_uint32_t *)&regDX0GCR1));
    }

    /* SAX1-2064_CHK: Should we really mess with this ?? */
#if 0
    for (i = 0; i < 9; i++)
    {
        /* DX0GCR3 .. DX8GCR3 */
        ncr_read32(phyReg, (NCP_PHY_DX0GCR3_5600 + (0x100 * i)), (ncp_uint32_t *)&regDX0GCR3);
        regDX0GCR3.dspdrmode = 0x0; /* based on pub_routines */
        /* default for others ?? */
        ncr_write32(phyReg, (NCP_PHY_DX0GCR3_5600 + (0x100 * i)), *((ncp_uint32_t *)&regDX0GCR3));

        /* DX0GCR4 .. DX8GCR4 */
        ncr_read32(phyReg, (NCP_PHY_DX0GCR4_5600 + (0x100 * i)), (ncp_uint32_t *)&regDX0GCR4);
        regDX0GCR4.dxrefien = 0x3; /* vref enable control for DQ IO buffers of a byte lane */
        regDX0GCR4.dxrefssel = 0x9; /* 50.35%(mid-rail) */
        regDX0GCR4.dxrefiom = 0x2;
        /* default for others ?? */
        ncr_write32(phyReg, (NCP_PHY_DX0GCR4_5600 + (0x100 * i)), *((ncp_uint32_t *)&regDX0GCR4));

        /* DX0GCR5 .. DX8GCR5 */
        ncr_read32(phyReg, (NCP_PHY_DX0GCR5_5600 + (0x100 * i)), (ncp_uint32_t *)&regDX0GCR5);
        regDX0GCR5.dxrefiselr0 = 0x2e; /* 76.17% byte lane internal vref select for rank 0 */
        regDX0GCR5.dxrefiselr1 = 0x2e; /* 76.17% byte lane internal vref select for rank 1 */
        /* default for others ?? */
        ncr_write32(phyReg, (NCP_PHY_DX0GCR5_5600 + (0x100 * i)), *((ncp_uint32_t *)&regDX0GCR5));
    }
#endif
    /* Power restore in PHY */
    for (i = 0; i < 9; i++)
    {
        /* DX0GCR1 .. DX8GCR1 */
        ncr_write32(phyReg, (NCP_PHY_DX0GCR1_5600 + (0x100 * i)), *((ncp_uint32_t *)&regDX0GCR1_rd));
    }

    NCP_RETURN_LABEL
        return ncpStatus;
}

ncp_st_t
ncp_sm_ddr4_reset_mc_phy(
                         ncp_dev_hdl_t   dev,
                         ncp_uint32_t    smNode,
                         ncp_sm_parms_t *parms,
                         ncp_common_timing_parameters_t *ctm)
{
    ncp_st_t	                    ncpStatus = NCP_ST_SUCCESS;
    ncp_syscon_reset_mod_r_xlf_t    resetReg = {0};

    /* Enable protected writes. Key is the only field in this register. */
    ncr_write32(NCP_REGION_AXIS_APB2SER3_SYSCON, NCP_SYSCON_KEY_xlf, 0xAB);

    ncr_block_read32(NCP_REGION_AXIS_APB2SER3_SYSCON,
                     NCP_SYSCON_RESET_MOD_xlf, ((ncp_uint32_t *)&resetReg),
                     NCP_SYSCON_RESET_MOD_xlf_ACCESS_SIZE/sizeof(ncp_uint32_t),
                     0);
    switch(smNode)
    {
        case 0x22:
            resetReg.smc0_rst         = 1;
        break;
        case 0xf:
            resetReg.smc1_rst         = 1;
        break;
        case 0x23:
            resetReg.smc2_rst         = 1;
        break;
        case 0x24:
            resetReg.smc3_rst         = 1;
        break;
        default:
            ;
    }
    ncr_block_write32(NCP_REGION_AXIS_APB2SER3_SYSCON,
                      NCP_SYSCON_RESET_MOD_xlf, ((ncp_uint32_t *)&resetReg),
                      NCP_SYSCON_RESET_MOD_xlf_ACCESS_SIZE/sizeof(ncp_uint32_t),
                      0);
    switch(smNode)
    {
        case 0x22:
            resetReg.smc0_rst         = 0;
        break;
        case 0xf:
            resetReg.smc1_rst         = 0;
        break;
        case 0x23:
            resetReg.smc2_rst         = 0;
        break;
        case 0x24:
            resetReg.smc3_rst         = 0;
        break;
        default:
            ;
    }
    ncr_block_write32(NCP_REGION_AXIS_APB2SER3_SYSCON,
                      NCP_SYSCON_RESET_MOD_xlf, ((ncp_uint32_t *)&resetReg),
                      NCP_SYSCON_RESET_MOD_xlf_ACCESS_SIZE/sizeof(ncp_uint32_t),
                      0);

    switch(smNode)
    {
        case 0x22:
            resetReg.smem0_phy_io_rst         = 1;
        break;
        case 0xf:
            resetReg.smem1_phy_io_rst         = 1;
        break;
        case 0x23:
            resetReg.smem2_phy_io_rst         = 1;
        break;
        case 0x24:
            resetReg.smem3_phy_io_rst         = 1;
        break;
        default:
            ;
    }
    ncr_block_write32(NCP_REGION_AXIS_APB2SER3_SYSCON,
                      NCP_SYSCON_RESET_MOD_xlf, ((ncp_uint32_t *)&resetReg),
                      NCP_SYSCON_RESET_MOD_xlf_ACCESS_SIZE/sizeof(ncp_uint32_t),
                      0);
    switch(smNode)
    {
        case 0x22:
            resetReg.smem0_phy_io_rst         = 0;
        break;
        case 0xf:
            resetReg.smem1_phy_io_rst         = 0;
        break;
        case 0x23:
            resetReg.smem2_phy_io_rst         = 0;
        break;
        case 0x24:
            resetReg.smem3_phy_io_rst         = 0;
        break;
        default:
            ;
    }
    ncr_block_write32(NCP_REGION_AXIS_APB2SER3_SYSCON,
                      NCP_SYSCON_RESET_MOD_xlf, ((ncp_uint32_t *)&resetReg),
                      NCP_SYSCON_RESET_MOD_xlf_ACCESS_SIZE/sizeof(ncp_uint32_t),
                      0);
    /* Disable protected writes */
    ncr_write32(NCP_REGION_AXIS_APB2SER3_SYSCON, NCP_SYSCON_KEY_xlf, 0x0);

    NCP_RETURN_LABEL
        return ncpStatus;
}

ncp_st_t
ncp_sm_ddr4_phy_init_self_refresh(
                                  ncp_dev_hdl_t   dev,
                                  ncp_uint32_t    smNode,
                                  ncp_sm_parms_t *parms,
                                  ncp_common_timing_parameters_t *ctm,
                                  ncp_uint32_t *preRetentionZQ)
{
    ncp_st_t		ncpStatus = NCP_ST_SUCCESS;
    ncp_region_id_t 	ctlReg  = NCP_REGION_ID(smNode, NCP_SYSMEM_TGT_DENALI);
    ncp_region_id_t 	phyReg 	= NCP_REGION_ID(smNode, NCP_SYSMEM_TGT_PHY);
    unsigned int		i = 0;
    unsigned int		tmp = 0;


    ncp_phy_PTR3_5600_t regPTR3 = {0};
    ncp_phy_PTR4_5600_t regPTR4 = {0};
    ncp_phy_DTPR0_5600_t regDTPR0 = {0};
    ncp_phy_DTPR1_5600_t regDTPR1 = {0};
    ncp_phy_DTPR2_5600_t regDTPR2 = {0};
    ncp_phy_DTPR3_5600_t regDTPR3 = {0};
    ncp_phy_DTPR4_5600_t regDTPR4 = {0};
    ncp_phy_DTPR5_5600_t regDTPR5 = {0};
    ncp_phy_DX4GCR0_5600_t regDX4GCR0 = {0};
    ncp_phy_DX8GCR0_5600_t regDX8GCR0 = {0};
    ncp_phy_RDIMMGCR0_5600_t regRDIMMGCR0 = {0};
    ncp_phy_RDIMMCR0_5600_t regRDIMMCR0 = {0};
    ncp_phy_RDIMMCR1_5600_t regRDIMMCR1 = {0};
    ncp_phy_RDIMMCR2_5600_t regRDIMMCR2 = {0};
    ncp_phy_RDIMMCR3_5600_t regRDIMMCR3 = {0};
    ncp_phy_RDIMMCR4_5600_t regRDIMMCR4 = {0};
    ncp_phy_DX0GCR1_5600_t regDX0GCR1 = {0};
    ncp_phy_DX0GCR3_5600_t regDX0GCR3 = {0};
    ncp_phy_DX0GCR4_5600_t regDX0GCR4 = {0};
    ncp_phy_DX0GCR5_5600_t regDX0GCR5 = {0};
    ncp_phy_DCR_5600_t regDCR = {0};
    ncp_phy_PGCR2_5600_t regPGCR2 = {0};
    ncp_phy_PIR_5600_t regPIR = {0};
    ncp_phy_PGCR0_5600_t regPGCR0 = {0};
    ncp_phy_PGCR1_5600_t regPGCR1 = {0};
    ncp_phy_PGSR0_5600_t regPGSR0 = {0};
    ncp_phy_BISTRR_5600_t regBISTRR = {0};
    ncp_phy_BISTUDPR_5600_t regBISTUDPR = {0};
    ncp_phy_DSGCR_5600_t regDSGCR = {0};
    ncp_phy_DXCCR_5600_t regDXCCR = {0};
    ncp_phy_IOVCR0_5600_t regIOVCR0 = {0};
    ncp_phy_IOVCR1_5600_t regIOVCR1 = {0};
    ncp_phy_ZQCR_5600_t regZQCR = {0};
    ncp_phy_ZQ0PR_5600_t regZQ0PR = {0};
    ncp_phy_ZQ1PR_5600_t regZQ1PR = {0};
    ncp_phy_ZQ2PR_5600_t regZQ2PR = {0};
    ncp_phy_ZQ3PR_5600_t regZQ3PR = {0};
    ncp_phy_ACIOCR0_5600_t regACIOCR0 = {0};
    /*ncp_phy_DX0GCR0_5600_t regDX0GCR0 = {0};*/
    ncp_phy_PLLCR0_5600_t 	regPLLCR0 = {0};

    ncp_denali_DENALI_CTL_00_5600_t reg00 = {0};
    ncp_denali_DENALI_CTL_56_5600_t reg56 = {0};

    ncp_bool_t  ddr_recovery = 0;

#ifdef UBOOT
    ddr_recovery = (cold != get_ddr_init_type()) ? 1 : 0;
#else
    ddr_recovery = parms->ddrRecovery;
#endif

    /* check if PHY is already configured */
    ncr_read32(phyReg, NCP_PHY_PGSR0_5600, (ncp_uint32_t *)&regPGSR0);
    if (regPGSR0.aplock)
    {
        /* AC PLL lock set */
        errprintf("WARNING: PHY still configured!! PLEASE RESET. \n");
        if (ddr_recovery == FALSE)
        {
            NCP_RETURN(NCP_ST_SUCCESS);
        }
    }

    /* PLLCR0 */
    ncr_read32(phyReg, NCP_PHY_PLLCR0_5600, (ncp_uint32_t *)&regPLLCR0);
    /* PLL frequency select- select the operating range of the PLL. Supports upto 2400Mbps
     * this is one-fourth DRAM rate */
    if (((parms->ddrClockSpeedMHz/2) >= 561) && ((parms->ddrClockSpeedMHz/2) <= 667))
    {
        regPLLCR0.frqsel = 0;
    }
    else if (((parms->ddrClockSpeedMHz/2) >= 472) && ((parms->ddrClockSpeedMHz/2) <= 560))
    {
        regPLLCR0.frqsel = 1;
    }
    else if (((parms->ddrClockSpeedMHz/2) >= 397) && ((parms->ddrClockSpeedMHz/2) <= 471))
    {
        regPLLCR0.frqsel = 2;
    }
    else if (((parms->ddrClockSpeedMHz/2) >= 333) && ((parms->ddrClockSpeedMHz/2) <= 396))
    {
        regPLLCR0.frqsel = 3;
    }
    else if (((parms->ddrClockSpeedMHz/2) >= 280) && ((parms->ddrClockSpeedMHz/2) <= 332))
    {
        regPLLCR0.frqsel = 4;
    }
    else if (((parms->ddrClockSpeedMHz/2) >= 236) && ((parms->ddrClockSpeedMHz/2) <= 279))
    {
        regPLLCR0.frqsel = 5;
    }
    else if (((parms->ddrClockSpeedMHz/2) >= 198) && ((parms->ddrClockSpeedMHz/2) <= 235))
    {
        regPLLCR0.frqsel = 6;
    }
    else if (((parms->ddrClockSpeedMHz/2) >= 166) && ((parms->ddrClockSpeedMHz/2) <= 197))
    {
        regPLLCR0.frqsel = 7;
    }
    ncr_write32(phyReg, NCP_PHY_PLLCR0_5600, *((ncp_uint32_t *)&regPLLCR0));

    /* PGCR0 */
    ncr_read32(phyReg, NCP_PHY_PGCR0_5600, (ncp_uint32_t *)&regPGCR0);
    regPGCR0.icpc = 1;
    ncr_write32(phyReg, NCP_PHY_PGCR0_5600, *((ncp_uint32_t *)&regPGCR0));

    if ((parms->enableECC == TRUE) && (parms->version == NCP_CHIP_ACPXLF))
    {
        /* DXCCR */
        ncr_read32(phyReg, NCP_PHY_DXCCR_5600, (ncp_uint32_t *)&regDXCCR);
        regDXCCR.msbudq = 4;
        ncr_write32(phyReg, NCP_PHY_DXCCR_5600, *((ncp_uint32_t *)&regDXCCR));
    }
    else if (parms->enableECC == FALSE)
    {
        /* DXCCR - power-up-default is 4 hence this is needed chip-independant */
        ncr_read32(phyReg, NCP_PHY_DXCCR_5600, (ncp_uint32_t *)&regDXCCR);
        regDXCCR.msbudq = 0;
        ncr_write32(phyReg, NCP_PHY_DXCCR_5600, *((ncp_uint32_t *)&regDXCCR));
    }

    for (i = 0; i < ((parms->version == NCP_CHIP_ACP56xx) ? 9 : 5); i++)
    {
        /* DX0BDLR0 .. DX8BDLR2 */
        ncr_read32(phyReg, (NCP_PHY_DX0BDLR0_5600 + (0x100 * i)), &tmp);
        tmp = 0x04040404;
        ncr_write32(phyReg, (NCP_PHY_DX0BDLR0_5600 + (0x100 * i)), tmp);

        ncr_read32(phyReg, (NCP_PHY_DX0BDLR1_5600 + (0x100 * i)), &tmp);
        tmp = 0x04040404;
        ncr_write32(phyReg, (NCP_PHY_DX0BDLR1_5600 + (0x100 * i)), tmp);

        ncr_read32(phyReg, (NCP_PHY_DX0BDLR2_5600 + (0x100 * i)), &tmp);
        tmp = 0x04040404;
        ncr_write32(phyReg, (NCP_PHY_DX0BDLR2_5600 + (0x100 * i)), tmp);
    }

    /* PGCR1 */
    ncr_read32(phyReg, NCP_PHY_PGCR1_5600, (ncp_uint32_t *)&regPGCR1);
    regPGCR1.wlstep = 1; /* write leveling step */
    /*regPGCR1.pubmode = 1;*/ /* PUB controls the interface to PHY and SDRAM */
    regPGCR1.ioddrm = 1; /* DDR4 */
    ncr_write32(phyReg, NCP_PHY_PGCR1_5600, *((ncp_uint32_t *)&regPGCR1));

    /* setup BIST early to UserDataPattern for VREF training bug */
    ncr_read32(phyReg, NCP_PHY_BISTRR_5600, (ncp_uint32_t *)&regBISTRR);
    regBISTRR.bmode = 1;
    regBISTRR.bdxen = 1; /* bist datx8 enable */
    regBISTRR.bdpat = 3;
    ncr_write32(phyReg, NCP_PHY_BISTRR_5600, *((ncp_uint32_t *)&regBISTRR));

    ncr_read32(phyReg, NCP_PHY_BISTUDPR_5600, (ncp_uint32_t *)&regBISTUDPR);
    regBISTUDPR.budp0 = 0xaaaa;
    regBISTUDPR.budp1 = 0x5555;
    ncr_write32(phyReg, NCP_PHY_BISTUDPR_5600, *((ncp_uint32_t *)&regBISTUDPR));
#if 1
    /* PTR3 */
    ncr_read32(phyReg, NCP_PHY_PTR3_5600, (ncp_uint32_t *)&regPTR3);
    /* dram init time in cke, use 500us per dwc pub */
    regPTR3.tdinit0 = ncp_ps_to_clk(parms->tck_ps, 500000000);
    regPTR3.tdinit1 = Max(5, (ctm->tRFC + ncp_ps_to_clk(parms->tck_ps, 10000)));
    ncr_write32(phyReg, NCP_PHY_PTR3_5600, *((ncp_uint32_t *)&regPTR3));

    /* PTR4 */
    ncr_read32(phyReg, NCP_PHY_PTR4_5600, (ncp_uint32_t *)&regPTR4);
    /* 200us on power up */
    regPTR4.tdinit2 = ncp_ps_to_clk(parms->tck_ps, 200000000);
    /* time from ZQ init to first command */
    regPTR4.tdinit3 = ctm->tZQinit; /* 1024 */
    ncr_write32(phyReg, NCP_PHY_PTR4_5600, *((ncp_uint32_t *)&regPTR4));
#endif
    /* DTPR0 */
    ncr_read32(phyReg, NCP_PHY_DTPR0_5600, (ncp_uint32_t *)&regDTPR0);
    regDTPR0.trtp = ctm->tRTP;
    regDTPR0.trp = ctm->tRP;
    regDTPR0.tras = ctm->tRAS;
    regDTPR0.trrd = ctm->tRRD_S;
    ncr_write32(phyReg, NCP_PHY_DTPR0_5600, *((ncp_uint32_t *)&regDTPR0));

    /* DTPR1 */
    ncr_read32(phyReg, NCP_PHY_DTPR1_5600, (ncp_uint32_t *)&regDTPR1);
    regDTPR1.tmrd = ctm->tMRD - 8; /* per Synopsys 8000923590 */
    switch(ctm->tMOD)
    {
        case 24:
            regDTPR1.tmod = 0;
        break;
        case 25:
            regDTPR1.tmod = 1;
        break;
        case 26:
            regDTPR1.tmod = 2;
        break;
        case 27:
            regDTPR1.tmod = 3;
        break;
        case 28:
            regDTPR1.tmod = 4;
        break;
        case 29:
            regDTPR1.tmod = 5;
        break;
        case 30:
            regDTPR1.tmod = 6;
        break;
        default:
            regDTPR1.tmod = 4; /* power-up-default */
    }
    regDTPR1.tfaw = ctm->tFAW;
    /*regDTPR1.twlmrd = default */
    ncr_write32(phyReg, NCP_PHY_DTPR1_5600, *((ncp_uint32_t *)&regDTPR1));

    /* DTPR2 */
    ncr_read32(phyReg, NCP_PHY_DTPR2_5600, (ncp_uint32_t *)&regDTPR2);
    regDTPR2.txs = ctm->tXS;
    regDTPR2.tcke = ctm->tCKE;
    /*regDTPR2.trtodt = default */
    /*regDTPR2.trtw = default */
    ncr_write32(phyReg, NCP_PHY_DTPR2_5600, *((ncp_uint32_t *)&regDTPR2));

    /* DTPR3 */
    ncr_read32(phyReg, NCP_PHY_DTPR3_5600, (ncp_uint32_t *)&regDTPR3);
    /*regDTPR3.tdqsck = default */
    /*regDTPR3.tdqsckmax = default */
    /*regDTPR3.tdllk = default */
    regDTPR3.tccd = 0x1;/* For PHY and DDR4 */
    /*regDTPR3.tofdx = default */ /* ODT turn-off delay extension */
    ncr_write32(phyReg, NCP_PHY_DTPR3_5600, *((ncp_uint32_t *)&regDTPR3));

    /* DTPR4 */
    ncr_read32(phyReg, NCP_PHY_DTPR4_5600, (ncp_uint32_t *)&regDTPR4);
    /*regDTPR4.txp = default */
    regDTPR4.twlo = 0xf; /* write-levelling output delay */
    regDTPR4.trfc = ctm->tRFC;
    ncr_write32(phyReg, NCP_PHY_DTPR4_5600, *((ncp_uint32_t *)&regDTPR4));

    /* DTPR5 */
    ncr_read32(phyReg, NCP_PHY_DTPR5_5600, (ncp_uint32_t *)&regDTPR5);
    regDTPR5.twtr = ctm->tWTR_L;
    regDTPR5.trcd = ctm->tRCD;
    regDTPR5.trc = ctm->tRC;
    ncr_write32(phyReg, NCP_PHY_DTPR5_5600, *((ncp_uint32_t *)&regDTPR5));

    /* Initializing the ddr4 phy */

    /* Deal with RDIMM stuff */
    if (parms->rdimm_misc & 0x1)
    {
        /* RDIMMGCR0 */
        ncr_read32(phyReg, NCP_PHY_RDIMMGCR0_5600, (ncp_uint32_t *)&regRDIMMGCR0);
        regRDIMMGCR0.rdimm = 1;
        ncr_write32(phyReg, NCP_PHY_RDIMMGCR0_5600, *((ncp_uint32_t *)&regRDIMMGCR0));

        /* RDIMMCR0 */
        ncr_read32(phyReg, NCP_PHY_RDIMMCR0_5600, (ncp_uint32_t *)&regRDIMMCR0);
        regRDIMMCR0.rc0 = parms->rdimm_ctl_0_0 & 0xf; 
        regRDIMMCR0.rc1 = (parms->rdimm_ctl_0_0 & 0xf0) >> 4;
        regRDIMMCR0.rc2 = (parms->rdimm_ctl_0_0 & 0xf00) >> 8;
        regRDIMMCR0.rc3 = (parms->rdimm_ctl_0_0 & 0xf000) >> 12;
        regRDIMMCR0.rc4 = (parms->rdimm_ctl_0_0 & 0xf0000) >> 16;
        regRDIMMCR0.rc5 = (parms->rdimm_ctl_0_0 & 0xf00000) >> 20;
        regRDIMMCR0.rc6 = (parms->rdimm_ctl_0_0 & 0xf000000) >> 24;
        regRDIMMCR0.rc7 = (parms->rdimm_ctl_0_0 & 0xf0000000) >> 28;
        ncr_write32(phyReg, NCP_PHY_RDIMMCR0_5600, *((ncp_uint32_t *)&regRDIMMCR0));

        /* RDIMMCR1 */
        ncr_read32(phyReg, NCP_PHY_RDIMMCR1_5600, (ncp_uint32_t *)&regRDIMMCR1);
        regRDIMMCR1.rc8 = parms->rdimm_ctl_0_1 & 0xf; 
        regRDIMMCR1.rc9 = (parms->rdimm_ctl_0_1 & 0xf0) >> 4;
        regRDIMMCR1.rc10 = (parms->rdimm_ctl_0_1 & 0xf00) >> 8;
        regRDIMMCR1.rc11 = (parms->rdimm_ctl_0_1 & 0xf000) >> 12;
        regRDIMMCR1.rc12 = (parms->rdimm_ctl_0_1 & 0xf0000) >> 16;
        regRDIMMCR1.rc13 = (parms->rdimm_ctl_0_1 & 0xf00000) >> 20;
        regRDIMMCR1.rc14 = (parms->rdimm_ctl_0_1 & 0xf000000) >> 24;
        regRDIMMCR1.rc15 = (parms->rdimm_ctl_0_1 & 0xf0000000) >> 28;
        ncr_write32(phyReg, NCP_PHY_RDIMMCR1_5600, *((ncp_uint32_t *)&regRDIMMCR1));

        /* RDIMMCR2 */
        ncr_read32(phyReg, NCP_PHY_RDIMMCR2_5600, (ncp_uint32_t *)&regRDIMMCR2);
        regRDIMMCR2.rc1x = parms->rdimm_ctl_0_2 & 0xff; 
        regRDIMMCR2.rc2x = (parms->rdimm_ctl_0_2 & 0xff00) >> 8;
        regRDIMMCR2.rc3x = (parms->rdimm_ctl_0_2 & 0xff0000) >> 16;
        regRDIMMCR2.rc4x = (parms->rdimm_ctl_0_2 & 0xff000000) >> 24;
        ncr_write32(phyReg, NCP_PHY_RDIMMCR2_5600, *((ncp_uint32_t *)&regRDIMMCR2));

        /* RDIMMCR3 */
        ncr_read32(phyReg, NCP_PHY_RDIMMCR3_5600, (ncp_uint32_t *)&regRDIMMCR3);
        regRDIMMCR3.rc5x = parms->rdimm_ctl_0_3 & 0xff; 
        regRDIMMCR3.rc6x = (parms->rdimm_ctl_0_3 & 0xff00) >> 8;
        regRDIMMCR3.rc7x = (parms->rdimm_ctl_0_3 & 0xff0000) >> 16;
        regRDIMMCR3.rc8x = (parms->rdimm_ctl_0_3 & 0xff000000) >> 24;
        ncr_write32(phyReg, NCP_PHY_RDIMMCR3_5600, *((ncp_uint32_t *)&regRDIMMCR3));

        /* RDIMMCR4 */
        ncr_read32(phyReg, NCP_PHY_RDIMMCR4_5600, (ncp_uint32_t *)&regRDIMMCR4);
        regRDIMMCR4.rc9x = parms->rdimm_ctl_0_4 & 0xff; 
        regRDIMMCR4.rcax = (parms->rdimm_ctl_0_4 & 0xff00) >> 8;
        regRDIMMCR4.rcbx = (parms->rdimm_ctl_0_4 & 0xff0000) >> 16;
        regRDIMMCR4.rcxx = (parms->rdimm_ctl_0_4 & 0xff000000) >> 24;
        ncr_write32(phyReg, NCP_PHY_RDIMMCR4_5600, *((ncp_uint32_t *)&regRDIMMCR4));
    }

    /* Power Down OFF in PHY */

    for (i = 0; i < 9; i++)
    {
        /* DX0GCR1 .. DX8GCR1 */
        ncr_read32(phyReg, (NCP_PHY_DX0GCR1_5600 + (0x100 * i)), (ncp_uint32_t *)&regDX0GCR1);
        regDX0GCR1.dxpddmode = 0x0000;
        /* SAX1-2064_CHK: should dxpdrmode be 0xaaaa per tb.
         * Enables the PDR mode values for DQ[7:0].
         * Bit [1:0] is for DQ[0], bit[3:2] for DQ[1] etc.
         */
        regDX0GCR1.dxpdrmode = 0x0000; /* based on pub_routines */
        ncr_write32(phyReg, (NCP_PHY_DX0GCR1_5600 + (0x100 * i)), *((ncp_uint32_t *)&regDX0GCR1));
    }

    for (i = 0; i < 9; i++)
    {
        /* DX0GCR3 .. DX8GCR3 */
        ncr_read32(phyReg, (NCP_PHY_DX0GCR3_5600 + (0x100 * i)), (ncp_uint32_t *)&regDX0GCR3);
        /* SAX1-2064_CHK: should dspdrmode be 2'b10/PDR always off/0x2
         * enables the PDR mode values for DQS */
        regDX0GCR3.dspdrmode = 0x0; /* based on pub_routines */
        /* default for others ?? */
        ncr_write32(phyReg, (NCP_PHY_DX0GCR3_5600 + (0x100 * i)), *((ncp_uint32_t *)&regDX0GCR3));

        /* DX0GCR4 .. DX8GCR4 */
        ncr_read32(phyReg, (NCP_PHY_DX0GCR4_5600 + (0x100 * i)), (ncp_uint32_t *)&regDX0GCR4);
        regDX0GCR4.dxrefien = 0x3; /* vref enable control for DQ IO buffers of a byte lane */
        regDX0GCR4.dxrefssel = 0x9; /* 50.35%(mid-rail) */
        regDX0GCR4.dxrefiom = 0x2;
        /* default for others ?? */
        ncr_write32(phyReg, (NCP_PHY_DX0GCR4_5600 + (0x100 * i)), *((ncp_uint32_t *)&regDX0GCR4));

        /* DX0GCR5 .. DX8GCR5 */
        ncr_read32(phyReg, (NCP_PHY_DX0GCR5_5600 + (0x100 * i)), (ncp_uint32_t *)&regDX0GCR5);
        regDX0GCR5.dxrefiselr0 = 0x2e; /* 76.17% byte lane internal vref select for rank 0 */
        regDX0GCR5.dxrefiselr1 = 0x2e; /* 76.17% byte lane internal vref select for rank 1 */
        /* default for others ?? */
        ncr_write32(phyReg, (NCP_PHY_DX0GCR5_5600 + (0x100 * i)), *((ncp_uint32_t *)&regDX0GCR5));
    }

    /* DSGCR */
    ncr_read32(phyReg, NCP_PHY_DSGCR_5600, (ncp_uint32_t *)&regDSGCR);
    regDSGCR.wrrmode = 1;
    regDSGCR.rrrmode = 1;
    regDSGCR.puren = 0;
    ncr_write32(phyReg, NCP_PHY_DSGCR_5600, *((ncp_uint32_t *)&regDSGCR));

    /* PHY DCR Register */

    ncr_read32(phyReg, NCP_PHY_DCR_5600, (ncp_uint32_t *)&regDCR);
    regDCR.ddrmd = (parms->dram_class == NCP_SM_DDR4_MODE) ? 0x4 : 0x3;
    regDCR.ddr8bnk = 0x1; /* SDRAM uses 8 banks or less */
    regDCR.pdq = 0x0; /* which if the 0..7 DQ pins is primary for MPR */
    regDCR.mprdq = 0x1; /* both primary and other DQ pins all drive same data from MPR */

    /* This is for read data on all byte lanes during read DQS gate training */
#if 0
    if (parms->primary_bus_width == 2)
    {
        /* half-datapath feature */
        regDCR.bytemask = 0xf; 
    }
    else
    {
        regDCR.bytemask = 0xff; 
    }
#endif

    /* No simultaneous Rank Access on same clock cycle allowed */
    regDCR.nosra = parms->address_mirroring; 

    /* 2T timing should be used by PUB generated sdram transactions */
    regDCR.ddr2t = 0x1; 

    /* UDIMM address mirroring */
    /* PUB will rescramble bank and address when sending MR cmds to second rank */
    regDCR.udimm = parms->address_mirroring; 

    if (parms->sdram_device_width == 2)
    {
        /* x16 */
        regDCR.ubg = 0x1; /* un-used bank group */
    }

    ncr_write32(phyReg, NCP_PHY_DCR_5600, *((ncp_uint32_t *)&regDCR));

    ncr_read32(phyReg, NCP_PHY_RIDR_5600, &tmp);
    if ((tmp & 0xff) == 0x22)
    {
        ncr_write32(phyReg, NCP_PHY_PLLCR2_5600, 0x5140e7c0);
        ncr_write32(phyReg, NCP_PHY_PLLCR3_5600, 0x0000e670);
    }

    /* IOVCR0 Register */
    ncr_read32(phyReg, NCP_PHY_IOVCR0_5600, (ncp_uint32_t *)&regIOVCR0);
    regIOVCR0.acvrefisel = 0x9; /* 50.35% mid-rail */
    regIOVCR0.acrefsen = 0x0;
    regIOVCR0.acrefiom = 0x2;
    ncr_write32(phyReg, NCP_PHY_IOVCR0_5600, *((ncp_uint32_t *)&regIOVCR0));

    /* IOVCR1 Register */
    ncr_read32(phyReg, NCP_PHY_IOVCR1_5600, (ncp_uint32_t *)&regIOVCR1);
    regIOVCR1.zqrefisel = 0x9; /* 50.35% mid-rail */
    ncr_write32(phyReg, NCP_PHY_IOVCR1_5600, *((ncp_uint32_t *)&regIOVCR1));

    /* ZQCR Register */
    ncr_read32(phyReg, NCP_PHY_ZQCR_5600, (ncp_uint32_t *)&regZQCR);
    regZQCR.term_off = 0x0;
    regZQCR.zqpd = 0x0;
    regZQCR.pgwait = 0x7; /* 467 clock */
    regZQCR.zcalt = 0x1; /* continous cal */
    regZQCR.avgmax = 0x2; /* 8 rounds */
    regZQCR.avgen = 0x1; /* averaging on */
    regZQCR.iodlmt = 0x2;
    regZQCR.asym_drv_en = 0x1;
    regZQCR.pu_odt_only = 0x1;
    regZQCR.dis_non_lin_comp = 0x0;
    regZQCR.force_zcal_vt_update = 0x0;
    regZQCR.zctrl_upper = 0x0;
    ncr_write32(phyReg, NCP_PHY_ZQCR_5600, *((ncp_uint32_t *)&regZQCR));

    ncr_read32(phyReg, NCP_PHY_RIDR_5600, &tmp);
    if ((tmp & 0xff) == 0x33)
    {
        /* ZQCR for D4MU IOs */
        regZQCR.zctrl_upper = 0x3;
        ncr_write32(phyReg, NCP_PHY_ZQCR_5600, *((ncp_uint32_t *)&regZQCR));
    }

    ncr_read32(phyReg, NCP_PHY_RIDR_5600, &tmp);
#if 0
    for (i = 0; i < 4; i++)
    {
        /* ZQCR set asymmetric ODT (based on number of islands) ZQnDR regs */
        ncr_read32(phyReg, (NCP_PHY_ZQ0DR_5600 + (0x10 * i)), (ncp_uint32_t *)&regZQ0DR);
        if ((tmp & 0xff) != 0x22)
        {
            regZQ0DR.odt_zden = 0x1;
            regZQ0DR.zdata = 28 << 21;
        }
        ncr_write32(phyReg, (NCP_PHY_ZQ0DR_5600 + (0x10 * i)), *((ncp_uint32_t *)&regZQ0DR));
    }
#endif
    ncr_read32(phyReg, NCP_PHY_ZQ0PR_5600, (ncp_uint32_t *)&regZQ0PR);
    ncr_read32(phyReg, NCP_PHY_ZQ2PR_5600, (ncp_uint32_t *)&regZQ2PR);
    ncr_read32(phyReg, NCP_PHY_ZQ1PR_5600, (ncp_uint32_t *)&regZQ1PR);
    ncr_read32(phyReg, NCP_PHY_ZQ3PR_5600, (ncp_uint32_t *)&regZQ3PR);
    ncr_read32(phyReg, NCP_PHY_ACIOCR0_5600, (ncp_uint32_t *)&regACIOCR0);
    ncr_read32(phyReg, NCP_PHY_DXCCR_5600, (ncp_uint32_t *)&regDXCCR);

    switch (smNode) {
        case 0x22:
            /* X9/XLF */
            regZQ0PR.zprog_asym_drv_pu = parms->packedAddrCmdCtrlOI & 0xf;
            regZQ0PR.zprog_asym_drv_pd = parms->packedAddrCmdCtrlOI & 0xf;
            regZQ2PR.zprog_asym_drv_pu = parms->packedAddrCmdCtrlOI & 0xf;
            regZQ2PR.zprog_asym_drv_pd = parms->packedAddrCmdCtrlOI & 0xf;

            regZQ1PR.zprog_asym_drv_pu = parms->packedClockOI & 0xf;
            regZQ1PR.zprog_asym_drv_pd = parms->packedClockOI & 0xf;

            regZQ3PR.zprog_pu_odt_only = parms->packedDqDmDqsODT & 0xf;

            regZQ3PR.zprog_asym_drv_pu = parms->packedDqDmDqsOI & 0xf;
            regZQ3PR.zprog_asym_drv_pd = parms->packedDqDmDqsOI & 0xf;

            regACIOCR0.acsr = parms->packedAddrCmdCtrlClkSlewRates & 0xf;

            regDXCCR.dxsr = parms->packedDqDmDqsSlewRates & 0xf;
        break;
        case 0xf:
            /* X9/XLF */
            regZQ0PR.zprog_asym_drv_pu = (parms->packedAddrCmdCtrlOI >> 8) & 0xf;
            regZQ0PR.zprog_asym_drv_pd = (parms->packedAddrCmdCtrlOI >> 8) & 0xf;
            regZQ2PR.zprog_asym_drv_pu = (parms->packedAddrCmdCtrlOI >> 8) & 0xf;
            regZQ2PR.zprog_asym_drv_pd = (parms->packedAddrCmdCtrlOI >> 8) & 0xf;

            regZQ1PR.zprog_asym_drv_pu = (parms->packedClockOI >> 8) & 0xf;
            regZQ1PR.zprog_asym_drv_pd = (parms->packedClockOI >> 8) & 0xf;

            regZQ3PR.zprog_pu_odt_only = (parms->packedDqDmDqsODT >> 8) & 0xf;

            regZQ3PR.zprog_asym_drv_pu = (parms->packedDqDmDqsOI >> 8) & 0xf;
            regZQ3PR.zprog_asym_drv_pd = (parms->packedDqDmDqsOI >> 8) & 0xf;

            regACIOCR0.acsr = (parms->packedAddrCmdCtrlClkSlewRates >> 8) & 0xf;

            regDXCCR.dxsr = (parms->packedDqDmDqsSlewRates >> 8) & 0xf;
        break;
        case 0x23:
            /* XLF */
            regZQ0PR.zprog_asym_drv_pu = (parms->packedAddrCmdCtrlOI >> 16) & 0xf;
            regZQ0PR.zprog_asym_drv_pd = (parms->packedAddrCmdCtrlOI >> 16) & 0xf;
            regZQ2PR.zprog_asym_drv_pu = (parms->packedAddrCmdCtrlOI >> 16) & 0xf;
            regZQ2PR.zprog_asym_drv_pd = (parms->packedAddrCmdCtrlOI >> 16) & 0xf;

            regZQ1PR.zprog_asym_drv_pu = (parms->packedClockOI >> 16) & 0xf;
            regZQ1PR.zprog_asym_drv_pd = (parms->packedClockOI >> 16) & 0xf;

            regZQ3PR.zprog_pu_odt_only = (parms->packedDqDmDqsODT >> 16) & 0xf;

            regZQ3PR.zprog_asym_drv_pu = (parms->packedDqDmDqsOI >> 16) & 0xf;
            regZQ3PR.zprog_asym_drv_pd = (parms->packedDqDmDqsOI >> 16) & 0xf;

            regACIOCR0.acsr = (parms->packedAddrCmdCtrlClkSlewRates >> 16) & 0xf;

            regDXCCR.dxsr = (parms->packedDqDmDqsSlewRates >> 16) & 0xf;
        break;
        case 0x24:
            /* XLF */
            regZQ0PR.zprog_asym_drv_pu = (parms->packedAddrCmdCtrlOI >> 24) & 0xf;
            regZQ0PR.zprog_asym_drv_pd = (parms->packedAddrCmdCtrlOI >> 24) & 0xf;
            regZQ2PR.zprog_asym_drv_pu = (parms->packedAddrCmdCtrlOI >> 24) & 0xf;
            regZQ2PR.zprog_asym_drv_pd = (parms->packedAddrCmdCtrlOI >> 24) & 0xf;

            regZQ1PR.zprog_asym_drv_pu = (parms->packedClockOI >> 24) & 0xf;
            regZQ1PR.zprog_asym_drv_pd = (parms->packedClockOI >> 24) & 0xf;

            regZQ3PR.zprog_pu_odt_only = (parms->packedDqDmDqsODT >> 24) & 0xf;

            regZQ3PR.zprog_asym_drv_pu = (parms->packedDqDmDqsOI >> 24) & 0xf;
            regZQ3PR.zprog_asym_drv_pd = (parms->packedDqDmDqsOI >> 24) & 0xf;

            regACIOCR0.acsr = (parms->packedAddrCmdCtrlClkSlewRates >> 24) & 0xf;

            regDXCCR.dxsr = (parms->packedDqDmDqsSlewRates >> 24) & 0xf;
        break;
        default:
            NCP_CALL(NCP_ST_ERROR);
    }

    /*regZQ0PR.zprog_pu_odt_only = 0xd;*/
    ncr_write32(phyReg, NCP_PHY_ZQ0PR_5600, *((ncp_uint32_t *)&regZQ0PR));

    /*regZQ1PR.zprog_pu_odt_only = 0xd;*/
    ncr_write32(phyReg, NCP_PHY_ZQ1PR_5600, *((ncp_uint32_t *)&regZQ1PR));

    /*regZQ2PR.zprog_pu_odt_only = 0xd;*/
    ncr_write32(phyReg, NCP_PHY_ZQ2PR_5600, *((ncp_uint32_t *)&regZQ2PR));

    /*regZQ3PR.zqdiv = (0x7 << 4) | 0xb; *//* DQ ODT value and DQ drive impedance */
    ncr_write32(phyReg, NCP_PHY_ZQ3PR_5600, *((ncp_uint32_t *)&regZQ3PR));

    ncr_write32(phyReg, NCP_PHY_ACIOCR0_5600, *((ncp_uint32_t *)&regACIOCR0));

    ncr_write32(phyReg, NCP_PHY_DXCCR_5600, *((ncp_uint32_t *)&regDXCCR));


    /* PHY PGCR2 Register */

    ncr_read32(phyReg, NCP_PHY_PGCR2_5600, (ncp_uint32_t *)&regPGCR2);
    /* ctm->tREFI will account for clock period.
     * assuming 9 refresh per refresh interval
     * use 400 clock safety margin per PUB
     */
    regPGCR2.trefprd = (9 * ctm->tREFI) - 400;
    /*regPGCR2.trefprd = 0x10a8;*/
    ncr_write32(phyReg, NCP_PHY_PGCR2_5600, *((ncp_uint32_t *)&regPGCR2));

    /* NOTE: MR settings are coming from end-user's selection in ASE and they
     * feed into both rank provisioning in MC, whereas, only rank-0 is used
     * PHY here */

    /* PHY MR0 Register */
    tmp = ctm->mr0;
    ncr_write32(phyReg, NCP_PHY_MR0_5600, tmp);

    /* PHY MR1 Register */
    tmp = ctm->mr1;
    ncr_write32(phyReg, NCP_PHY_MR1_5600, tmp);

    /* PHY MR2 Register */
    tmp = ctm->mr2;
    ncr_write32(phyReg, NCP_PHY_MR2_5600, tmp);

    /* PHY MR3 Register */
    tmp = ctm->mr3;
    ncr_write32(phyReg, NCP_PHY_MR3_5600, tmp);

    /* PHY MR4 Register */
    tmp = ctm->mr4;
    ncr_write32(phyReg, NCP_PHY_MR4_5600, tmp);

    /* PHY MR5 Register */
    tmp = ctm->mr5;
    ncr_write32(phyReg, NCP_PHY_MR5_5600, tmp);

    /* PHY MR6 Register */
    tmp = ctm->mr6;
    ncr_write32(phyReg, NCP_PHY_MR6_5600, tmp);

    /* Force ZQ calibration */
    ncr_read32(phyReg, NCP_PHY_ZQCR_5600, (ncp_uint32_t *)&regZQCR);
    regZQCR.force_zcal_vt_update = 0x1;
    ncr_write32(phyReg, NCP_PHY_ZQCR_5600, *((ncp_uint32_t *)&regZQCR));
    regZQCR.force_zcal_vt_update = 0x0;
    ncr_write32(phyReg, NCP_PHY_ZQCR_5600, *((ncp_uint32_t *)&regZQCR));

    /* PLL init and Impedance Calibration */

    ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
    /* Init trigger for DDR system init including PHY init, DRAM init, and PHY training */
    regPIR.init = 1; 
    /* Actual init involves selection among the following steps:
     * ZCAL: impedance calibration
     * CA: CA training
     * PLLINIT: pll init (pll power, reset, gear shift, wait for lock)
     * DCAL: digital delay line calibration
     * PHYRST: reset the AC and DATX8
     * DRAMRST: reset, wait 200us
     * DRAMINIT: executes DRAM init sequence
     * WL: write leveling
     * QSGATE: read dqs gate training
     * WLADJ: write leveling adjust
     * RDDSKW: read data bit deskew
     * WRDSKW: write data bit deskew
     * RDEYE: read data eye training
     * WREYE: write data eye training
     *
     *
     * <specials are>
     * SRD: static read training
     * VREF: vref training
     * CTLDINIT: controller performs DRAM init
     * RDIMMINIT: rdimm init
     */
    regPIR.zcal = 0;    /* SAX1-2064_CHK: all these make regPIR=0x40000071 */
    regPIR.ca = 0; 
    regPIR.pllinit = 1; 
    regPIR.dcal = 1; 
    regPIR.phyrst = 1; 
    regPIR.dramrst = 0; 
    regPIR.draminit = 0; 
    regPIR.wl = 0; 
    regPIR.qsgate = 0; 
    regPIR.wladj = 0; 
    regPIR.rddskw = 0; 
    regPIR.wrdskw = 0; 
    regPIR.rdeye = 0; 
    regPIR.wreye = 0; 
    regPIR.srd = 0; 
    regPIR.vref = 0; 
    regPIR.ctldinit = 0; 
    regPIR.rdimminit = 0; 
    regPIR.dcalpse = 0; /* SAX1-2064_CHK */
    regPIR.zcalbyp = 1; /* SAX1-2064_CHK */
    ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));
    ncr_read32(phyReg, NCP_PHY_PIR_5600, &tmp);

    /* Check the General Status register */

    /* poll for idone(bit 0), pldone(1), dcdone(2) */
    ncpStatus = (ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0x7,  0x7,  1000,  10000));

    if (ncpStatus == NCP_ST_POLL_TIMEOUT)
    {
        ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
        errprintf("POLL timeout during PHY init [line:%d] exp 0x1f read 0x%x\n",__LINE__, tmp);
        NCP_CALL(NCP_ST_POLL_TIMEOUT);
    }

    /* Checking for Error's */
    ncpStatus = (ncp_sm_ddr4_phy_training_error_check(dev, smNode));
    if (ncpStatus == NCP_ST_ERROR)
    {
        NCP_CALL(NCP_ST_ERROR);
    }

    ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
    dbgprintf("SUCCESS: result after PHY init PLL init and impedance calibration [line:%d] read 0x%x\n",__LINE__, tmp);

#if 1 /* extra steps review SAX1-2064_CHK */
    dbgprintf("PHY Init done!!!\nCalibration Bypassed!!!\n");

    /* Restore pre-data-retention ZQ calibrated values i.e. impedance data
     * Override ZQ cal with previously (pre-retention) calibrated values.
     * - set odt_zden ZQnDR.ODT_ZDEN
     * - set drv_zden ZQnDR.DRV_ZDEN
     */
    NCP_CALL(ncp_sm_ddr4_pre_retention_restore(dev, smNode, parms, ctm, preRetentionZQ, TRUE));

    /* Force ZQ calibration */
    /* SAX1-2064_CHK: make sure pgwait clk rate is set correctly */
    ncr_read32(phyReg, NCP_PHY_ZQCR_5600, (ncp_uint32_t *)&regZQCR);
    regZQCR.force_zcal_vt_update = 0x1;
    ncr_write32(phyReg, NCP_PHY_ZQCR_5600, *((ncp_uint32_t *)&regZQCR));
    regZQCR.force_zcal_vt_update = 0x0;
    ncr_write32(phyReg, NCP_PHY_ZQCR_5600, *((ncp_uint32_t *)&regZQCR));

    ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
    /* Init trigger for DDR system init including PHY init, DRAM init, and PHY training */
    regPIR.init = 1; 
    /* Actual init involves selection among the following steps:
     * ZCAL: impedance calibration
     * CA: CA training
     * PLLINIT: pll init (pll power, reset, gear shift, wait for lock)
     * DCAL: digital delay line calibration
     * PHYRST: reset the AC and DATX8
     * DRAMRST: reset, wait 200us
     * DRAMINIT: executes DRAM init sequence
     * WL: write leveling
     * QSGATE: read dqs gate training
     * WLADJ: write leveling adjust
     * RDDSKW: read data bit deskew
     * WRDSKW: write data bit deskew
     * RDEYE: read data eye training
     * WREYE: write data eye training
     *
     *
     * <specials are>
     * SRD: static read training
     * VREF: vref training
     * CTLDINIT: controller performs DRAM init
     * RDIMMINIT: rdimm init
     */
    regPIR.zcal = 0;    /* SAX1-2064_CHK: all these make regPIR=0x40040001 */
    regPIR.ca = 0; 
    regPIR.pllinit = 0; 
    regPIR.dcal = 0; 
    regPIR.phyrst = 0; 
    regPIR.dramrst = 0; 
    regPIR.draminit = 0; 
    regPIR.wl = 0; 
    regPIR.qsgate = 0; 
    regPIR.wladj = 0; 
    regPIR.rddskw = 0; 
    regPIR.wrdskw = 0; 
    regPIR.rdeye = 0; 
    regPIR.wreye = 0; 
    regPIR.srd = 0; 
    regPIR.vref = 0; 
    regPIR.ctldinit = 1; 
    regPIR.rdimminit = 0; 
    regPIR.dcalpse = 0;
    regPIR.zcalbyp = 0; /* SAX1-2064_CHK: */
    ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));
    ncr_read32(phyReg, NCP_PHY_PIR_5600, &tmp);

    /* Check the General Status register */

    /* poll for idone(bit 0) */
    ncpStatus = (ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0x1/* 0x1f*/,  0x1/* 0x1f*/,  1000,  10000));

    if (ncpStatus == NCP_ST_POLL_TIMEOUT)
    {
        ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
        errprintf("POLL timeout during PHY init [line:%d] exp 0x1f read 0x%x\n",__LINE__, tmp);
        NCP_CALL(NCP_ST_POLL_TIMEOUT);
    }

    /* Checking for Error's */
    ncpStatus = (ncp_sm_ddr4_phy_training_error_check(dev, smNode));
    if (ncpStatus == NCP_ST_ERROR)
    {
        NCP_CALL(NCP_ST_ERROR);
    }

    ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
    dbgprintf("SUCCESS: result after PHY init MC DRAM init ZCalBypassed[line:%d] read 0x%x\n",__LINE__, tmp);
    dbgprintf("VT update PHY Init done!!!\n");

    /* UnLatch IO of PHY and appropriate signals to maintain self-refresh
     * - de-assert PHY_TOP data retention enable signals
     * - set GPR0
     */
    NCP_CALL(ncp_sm_ddr4_phy_self_refresh_io_control(dev, smNode, parms, ctm, 0x2));

    /* Remove Override ZQ cal with previously (pre-retention) calibrated values.
     * - unset odt_zden ZQnDR.ODT_ZDEN
     * - unset drv_zden ZQnDR.DRV_ZDEN
     */
    NCP_CALL(ncp_sm_ddr4_pre_retention_restore(dev, smNode, parms, ctm, preRetentionZQ, FALSE));
#endif

    /* disable all unused bytes */
    if ((parms->enableECC == FALSE) && (parms->version == NCP_CHIP_ACP56xx))
    {
        /* DX8GCR0 */
        ncr_read32(phyReg, NCP_PHY_DX8GCR0_5600, (ncp_uint32_t *)&regDX8GCR0);
        regDX8GCR0.dxen = 0;
        ncr_write32(phyReg, NCP_PHY_DX8GCR0_5600, *((ncp_uint32_t *)&regDX8GCR0));
    }
    else if ((parms->enableECC == FALSE) && (parms->version == NCP_CHIP_ACPXLF))
    {
        /* DX4GCR0 */
        ncr_read32(phyReg, NCP_PHY_DX4GCR0_5600, (ncp_uint32_t *)&regDX4GCR0);
        regDX4GCR0.dxen = 0;
        ncr_write32(phyReg, NCP_PHY_DX4GCR0_5600, *((ncp_uint32_t *)&regDX4GCR0));
    }

    /* PHY Init done!!! */

#if 0 	/* Check if this is needed ?? MC is already init'd by this point
         * should DRAM init be done by PHY-side or should PHY be told Controller will do DRAM init ?? */

    dbgprintf("DRAM init initiated by PHY!!!!!\n");
    /*ncr_read32(phyReg, NCP_PHY_GPR0_5600, &tmp);
      dbgprintf("pubmode = %d PHY:GPR0=0x%x\n",regPGCR1.pubmode, tmp);*/

    /* PGCR1 */
    ncr_read32(phyReg, NCP_PHY_PGCR1_5600, (ncp_uint32_t *)&regPGCR1);
    /* Enables if set the PUB to control the interface to the PHY and SDRAM.
     * In this mode the DFI commands from the controller are ignored. The bit must
     * be set to 0 after the system determines it is convenient to pass control of the DFI
     * bus to the controller. When set to 0 the DFI interface has control of the PHY and SDRAM
     * interface except when trigerring pub operations such as BIST, DCU or data training.
     */
    regPGCR1.pubmode = 0x1;
    ncr_write32(phyReg, NCP_PHY_PGCR1_5600, *((ncp_uint32_t *)&regPGCR1));

    /* SDRAM Initialization by PHY !!! */

    ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
    regPIR.init = 1; 
    regPIR.zcal = 0; 
    regPIR.ca = 0; 
    regPIR.pllinit = 0; 
    regPIR.dcal = 0; 
    regPIR.phyrst = 0; 
    regPIR.dramrst = 1; 
    regPIR.draminit = 1; 
    regPIR.wl = 0; 
    regPIR.qsgate = 0; 
    regPIR.wladj = 0; 
    regPIR.rddskw = 0; 
    regPIR.wrdskw = 0; 
    regPIR.rdeye = 0; 
    regPIR.wreye = 0; 
    regPIR.srd = 0; 
    regPIR.vref = 0; 
    regPIR.ctldinit = 0; 
    regPIR.rdimminit = 0; 
    ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));

    /* Check the General Status register */

    /* poll for idone(bit 0), didone(4) */
    ncpStatus = (ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0x11,  0x11,  1000,  10000));

    if (ncpStatus == NCP_ST_POLL_TIMEOUT)
    {
        ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
        errprintf("POLL timeout during SDRAM initialization by PHY [line:%d] exp 0x11 read 0x%x\n",__LINE__, tmp);
        return ncpStatus;
    }

    /* Checking for Error's */
    ncpStatus = (ncp_sm_ddr4_phy_training_error_check(dev, smNode));
    if (ncpStatus == NCP_ST_ERROR)
    {
        return ncpStatus;
    }

    ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
    dbgprintf("SUCCESS: result during SDRAM initialization by PHY [line:%d] read 0x%x\n",__LINE__, tmp);


    /* SDRAM Initialization by PHY done !!! */
#if 0
    /* start MC init operation */
    ncr_read32(ctlReg, NCP_DENALI_CTL_00_5600, (ncp_uint32_t *)&reg00);
    reg00.start = 0x1;
    ncr_write32(ctlReg, NCP_DENALI_CTL_00_5600, *((ncp_uint32_t *)&reg00));

    /* poll for memory init operation bit-8 */
    ncpStatus = (ncr_poll(ctlReg, NCP_DENALI_CTL_366_5600,  0x0100,  0x0100,  1000,  10000));

    if (ncpStatus == NCP_ST_POLL_TIMEOUT)
    {
        ncr_read32(ctlReg, NCP_DENALI_CTL_366_5600, &tmp);
        errprintf("POLL timeout during MC init [line:%d] exp 0x100 read 0x%x\n",__LINE__, tmp);
    }
#endif
#else
    dbgprintf("DRAM init initiated by MC!!!!!\n");
    /*ncr_read32(phyReg, NCP_PHY_PGCR1_5600, (ncp_uint32_t *)&regPGCR1);
      ncr_read32(phyReg, NCP_PHY_GPR0_5600, &tmp);
      dbgprintf("pubmode = %d PHY:GPR0=0x%x\n",regPGCR1.pubmode, tmp);*/

    ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
    regPIR.init = 1; /* SAX1-2064_CHK: all these make regPIR=0x00040003 */
    regPIR.zcal = 1; 
    regPIR.ca = 0; 
    regPIR.pllinit = 0; 
    regPIR.dcal = 0; 
    regPIR.phyrst = 0; 
    regPIR.dramrst = 0; 
    regPIR.draminit = 0; 
    regPIR.wl = 0; 
    regPIR.qsgate = 0; 
    regPIR.wladj = 0; 
    regPIR.rddskw = 0; 
    regPIR.wrdskw = 0; 
    regPIR.rdeye = 0; 
    regPIR.wreye = 0; 
    regPIR.srd = 0; 
    regPIR.vref = 0; 
    regPIR.ctldinit = 1;  /* check with TB code */
    regPIR.rdimminit = 0; 
    regPIR.dcalpse = 0;
    regPIR.zcalbyp = 0;
    ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));

    /*ncr_read32(phyReg, NCP_PHY_PIR_5600, &tmp);
      dbgprintf("regPIR written as = 0x%x\n",tmp);*/

    ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
    dbgprintf("During MC initialization of the DRAM's [line:%d] PGSR0 = 0x%x\n",__LINE__, tmp);
    /* Check the General Status register */
#if 1
    /* poll for idone(bit 0) zcdone(3) */
    ncpStatus = (ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0x9/*0x1f*/,  0x9/*0x1f*/,  1000,  10000));

    if (ncpStatus == NCP_ST_POLL_TIMEOUT)
    {
        ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
        errprintf("POLL timeout during MC initialization the DRAM's [line:%d] exp 0x1f read 0x%x\n",__LINE__, tmp);
        return ncpStatus;
    }

    /* Checking for Error's */
    ncpStatus = (ncp_sm_ddr4_phy_training_error_check(dev, smNode));
    if (ncpStatus == NCP_ST_ERROR)
    {
        NCP_CALL(NCP_ST_ERROR);
    }

    ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
    dbgprintf("SUCCESS: result during MC initialization the DRAM's [line:%d] exp 0x1f read 0x%x\n",__LINE__, tmp);
    dbgprintf("ZCAL update PHY Init done!!!\n");
#endif

    /* start MC init operation */
    ncr_read32(ctlReg, NCP_DENALI_CTL_00_5600, (ncp_uint32_t *)&reg00);
    reg00.start = 0x1;
    ncr_write32(ctlReg, NCP_DENALI_CTL_00_5600, *((ncp_uint32_t *)&reg00));

#if 1 /* SAX1-2064_CHK */
    ncpStatus = (ncr_poll(ctlReg, NCP_DENALI_CTL_366_5600,  0x0100/*bit-8*/,  0x0100/*bit-8*/,  1000,  1000));
    if (ncpStatus == NCP_ST_POLL_TIMEOUT)
    {
        errprintf("poll is timing out at line %d\n",__LINE__);
        ncr_read32(ctlReg, NCP_DENALI_CTL_366_5600, &tmp);
        dbgprintf("CTL_366 int_status = 0x%x\n",tmp);
    }

    /* DENALI_CTL_56 */
    ncr_read32(ctlReg, NCP_DENALI_CTL_56_5600, (ncp_uint32_t *)&reg56);
    /* SAX1-2064_CHK: set bit 25,24,17 of this 25:0 */
    reg56.write_modereg = 0x3020000; /* to issue mem mode register writes */
    ncr_write32(ctlReg, NCP_DENALI_CTL_56_5600, *((ncp_uint32_t *)&reg56));

    ncpStatus = (ncr_poll(ctlReg, NCP_DENALI_CTL_366_5600,  0x10000000/*'bit-28*/,  0x10000000/*'bit-28*/,  1000,  1000));
    if (ncpStatus == NCP_ST_POLL_TIMEOUT)
    {
        errprintf("poll is timing out at line %d\n",__LINE__);
        ncr_read32(ctlReg, NCP_DENALI_CTL_366_5600, &tmp);
        dbgprintf("CTL_366 int_status = 0x%x\n",tmp);
    }
#else
    /* poll for memory init operation bit-8 */
    ncpStatus = (ncr_poll(ctlReg, NCP_DENALI_CTL_366_5600,  0x0100,  0x0100,  1000,  1000));
#endif

    ncr_read32(ctlReg, NCP_DENALI_CTL_366_5600, &tmp);
    dbgprintf("CTL_366 int_status = 0x%x looking for 0x100\n",tmp);
    ncr_read32(ctlReg, NCP_DENALI_CTL_367_5600, &tmp);
    dbgprintf("CTL_367 int_status = 0x%x\n",tmp);

    if (ncpStatus == NCP_ST_POLL_TIMEOUT)
    {
        ncr_read32(ctlReg, NCP_DENALI_CTL_366_5600, &tmp);
        errprintf("POLL timeout during MC init [line:%d] exp 0x100 read 0x%x\n",__LINE__, tmp);
    }

#endif
#if 1 /* SAX1-2064_CHK */
    NCP_CALL(ncp_sm_ddr4_phy_self_refresh_io_control(dev, smNode, parms, ctm, 0x6));

    /* DENALI_CTL_328 Poll till MEM_RST_VALID bit-24 goes high */
    ncpStatus = (ncr_poll(ctlReg, NCP_DENALI_CTL_328_5600,  0x01000000,  0x01000000,  10000,  10000));

    if (ncpStatus == NCP_ST_POLL_TIMEOUT)
    {
        ncr_read32(ctlReg, NCP_DENALI_CTL_328_5600, &tmp);
        errprintf("TIMEOUT while waiting for MEM_RST_VALID  to be asserted [line:%d] exp 0x1 read 0x%x\n",__LINE__, tmp);
    }
    ncr_read32(ctlReg, NCP_DENALI_CTL_328_5600, &tmp);
    dbgprintf("CTL_328 mem_rst_valid = 0x%x\n",tmp);
#endif

    NCP_RETURN_LABEL
        return ncpStatus;
}

ncp_st_t
ncp_sm_ddr4_phy_training_self_refresh(
                                      ncp_dev_hdl_t   dev,
                                      ncp_uint32_t    smNode,
                                      ncp_sm_parms_t *parms)
{
    ncp_st_t		ncpStatus = NCP_ST_SUCCESS;
    unsigned int		tmp = 0;
    ncp_region_id_t 	phyReg 	= NCP_REGION_ID(smNode, NCP_SYSMEM_TGT_PHY);

    ncp_phy_DTCR0_5600_t regDTCR0 = {0};
    ncp_phy_DTCR1_5600_t regDTCR1 = {0};
    /*ncp_phy_DTAR0_5600_t regDTAR0 = {0};*/
    ncp_phy_PIR_5600_t regPIR = {0};
    ncp_phy_PGCR0_5600_t regPGCR0 = {0};
    ncp_phy_PGCR3_5600_t regPGCR3 = {0};
    ncp_phy_PGCR1_5600_t regPGCR1 = {0};
    ncp_phy_BISTAR1_5600_t regBISTAR1 = {0};
    ncp_phy_DXCCR_5600_t regDXCCR = {0};
    ncp_phy_VTCR1_5600_t regVTCR1 = {0};

    ncp_bool_t  ddr_recovery = 0;

#ifdef UBOOT
    ddr_recovery = (cold != get_ddr_init_type()) ? 1 : 0;
#else
    ddr_recovery = parms->ddrRecovery;
#endif

    dbgprintf("Running the ddr4 phy sw training using synopsys phy\n");

    /* PGCR1 */
    ncr_read32(phyReg, NCP_PHY_PGCR1_5600, (ncp_uint32_t *)&regPGCR1);
    /* Enables if set the PUB to control the interface to the PHY and SDRAM.
     * In this mode the DFI commands from the controller are ignored. The bit must
     * be set to 0 after the system determines it is convenient to pass control of the DFI
     * bus to the controller. When set to 0 the DFI interface has control of the PHY and SDRAM
     * interface except when trigerring pub operations such as BIST, DCU or data training.
     */
    regPGCR1.pubmode = 0x1;
    ncr_write32(phyReg, NCP_PHY_PGCR1_5600, *((ncp_uint32_t *)&regPGCR1));

    /* ZQCR set asymmetric ODT based on number of islands ZQnDR regs */
    ncr_read32(phyReg, NCP_PHY_RIDR_5600, &tmp);

#if 0

    for (i = 0; i < 4; i++)
    {
        /* ZQCR set asymmetric ODT (based on number of islands) ZQnDR regs */
        ncr_read32(phyReg, (NCP_PHY_ZQ0DR_5600 + (0x10 * i)), (ncp_uint32_t *)&regZQ0DR);
        regZQ0DR.odt_zden = 0x1;
        regZQ0DR.zdata &= ~(0x1fc000);
        ncr_write32(phyReg, (NCP_PHY_ZQ0DR_5600 + (0x10 * i)), *((ncp_uint32_t *)&regZQ0DR));
    }

    /* Force ZQ calibration- this was already done in phy_init */
    ncr_read32(phyReg, NCP_PHY_ZQCR_5600, (ncp_uint32_t *)&regZQCR);
    regZQCR.force_zcal_vt_update = 0x1;
    ncr_write32(phyReg, NCP_PHY_ZQCR_5600, *((ncp_uint32_t *)&regZQCR));
    regZQCR.force_zcal_vt_update = 0x0;
    ncr_write32(phyReg, NCP_PHY_ZQCR_5600, *((ncp_uint32_t *)&regZQCR));
#endif

    /* Started Data Training */
    /*************************/

    /* DTCR0 */
    ncr_read32(phyReg, NCP_PHY_DTCR0_5600, (ncp_uint32_t *)&regDTCR0);
    regDTCR0.dtrptn = 0x7; /* Data Training Repeat Number */
    regDTCR0.dtmpr = (parms->dram_class == NCP_SM_DDR4_MODE) ? 0x1 : 0x0; /* Data Training using MPR */
    regDTCR0.dtcmpd = 0x1; /* DQS Gate training compare data */
    regDTCR0.rfshent = 0x1; /* 0x9 is Sim value: Assuming PHY refresh enabled during training */
    regDTCR0.dtwbddm = parms->dm_masking; /* Data training write bit deskew data mask */
    regDTCR0.dtbdc = 0x1; /* Data training bit deskew centering enables */
    regDTCR0.dtdrs = 0x0; /* DTDRS Data training debug rank select */
    regDTCR0.dtdbs = 0x0; /* DTDBS Data training debug byte select */
    /* RDBI deskewing is not performed */
    if (parms->dbi_rd_en)
    {
        regDTCR0.dtrdbitr = 0x2;
    }
    else
    {
        regDTCR0.dtrdbitr = 0x0;
    }
    regDTCR0.dtden = 0x0; /* DTDEN Data training debug enable */
    regDTCR0.dtdstp = 0x0; /* DTDSTP Data training debug step */
    regDTCR0.dtexd = 0x0; /* DTEXD Data training extended write DQ */
    regDTCR0.dtexg = 0x0; /* DTEXG Data training early/extended gate */
    regDTCR0.rfshdt = 0x0; /* 0x9 is Sim value: Assuming PHY refresh enabled during training */
    ncr_write32(phyReg, NCP_PHY_DTCR0_5600, *((ncp_uint32_t *)&regDTCR0));

    /* DTCR1 */
    ncr_read32(phyReg, NCP_PHY_DTCR1_5600, (ncp_uint32_t *)&regDTCR1);
    regDTCR1.bsten = 0x1;
    regDTCR1.rdlvlen = 0x1;
    regDTCR1.rdprmvl_trn = 0x1;
    regDTCR1.rdlvlgs = 0x3;
    regDTCR1.rdlvlgdiff = 0x2;
    regDTCR1.dtrank = 0x0;
    regDTCR1.ranken = parms->topology; /* Each bit will enable each rank */
    ncr_write32(phyReg, NCP_PHY_DTCR1_5600, *((ncp_uint32_t *)&regDTCR1));

    /* DTAR0 */
#if 0	/* check if this is not needed */
    ncr_read32(phyReg, NCP_PHY_DTAR0_5600, (ncp_uint32_t *)&regDTAR0);
    regDTAR0.mprloc = 0x1;
    ncr_write32(phyReg, NCP_PHY_DTAR0_5600, *((ncp_uint32_t *)&regDTAR0));
#endif

    if (((parms->packedPHYTrainingOptions >> 17) & 0x1) && (ddr_recovery == FALSE)/*SAX1-2064_CHK*/)
    {
        /* Used by VREF training. BIST */
        ncr_write32(phyReg, NCP_PHY_BISTRR_5600, 0x007e4008);
        ncr_write32(phyReg, NCP_PHY_BISTMSKR1_5600, 0x01000000); /* CIDMSK */

        /* BISTAR1 */
        ncr_read32(phyReg, NCP_PHY_BISTAR1_5600, (ncp_uint32_t *)&regBISTAR1);
        regBISTAR1.brank = 0x0;/* was parms->topology - 1;*/
        regBISTAR1.bainc = 0x8; /* for BL8 lower bits should be 000 to mark beginning of burst boundary */
        regBISTAR1.bmrank = parms->num_ranks_per_interface - 1; /* BIST Maximum rank */
        ncr_write32(phyReg, NCP_PHY_BISTAR1_5600, *((ncp_uint32_t *)&regBISTAR1));

        ncr_write32(phyReg, NCP_PHY_BISTAR2_5600, 0x000000c8); /* 31:28 BIST max bank address, 11:0 BIST max col address */
        ncr_write32(phyReg, NCP_PHY_BISTAR4_5600, 0x00003fff); /* 17:0 is BIST max row address */
        ncr_write32(phyReg, NCP_PHY_BISTUDPR_5600, 0xa5a5a5a5); /* user-data-patter 2 16-bits */

        /* VTCR1 */
        ncr_read32(phyReg, NCP_PHY_VTCR1_5600, (ncp_uint32_t *)&regVTCR1);
        regVTCR1.ENUM = 0x1; /* number of LCDL eye points for which training is repeated */
        regVTCR1.vwcr = 0xf; /* VREF word count */
        regVTCR1.hvss = 0x0; /* host vref step size */
        regVTCR1.shrnk = 0x0; /* static host Vref rank value */
        regVTCR1.shren = 0x1; /* static host Vref rank enable */
        ncr_write32(phyReg, NCP_PHY_VTCR1_5600, *((ncp_uint32_t *)&regVTCR1));
    }

    /* PIR */
    if ((parms->packedPHYTrainingOptions >> 9) & 0x1)
    {
        ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
        regPIR.init = 1; 
        /* Actual init involves selection among the following steps:
         * ZCAL: impedance calibration
         * CA: CA training
         * PLLINIT: pll init (pll power, reset, gear shift, wait for lock)
         * DCAL: digital delay line calibration
         * PHYRST: reset the AC and DATX8
         * DRAMRST: reset, wait 200us
         * DRAMINIT: executes DRAM init sequence
         * WL: write leveling
         * QSGATE: read dqs gate training
         * WLADJ: write leveling adjust
         * RDDSKW: read data bit deskew
         * WRDSKW: write data bit deskew
         * RDEYE: read data eye training
         * WREYE: write data eye training
         *
         *
         * <specials are>
         * SRD: static read training
         * VREF: vref training
         * CTLDINIT: controller performs DRAM init
         * RDIMMINIT: rdimm init
         */
        regPIR.zcal = 0; /* SAX1-2064_CHK: all these make regPIR=0x00040e01 "progressively" */
        regPIR.ca = 0; 
        regPIR.pllinit = 0; 
        regPIR.dcal = 0; 
        regPIR.phyrst = 0; 
        regPIR.dramrst = 0; 
        regPIR.draminit = 0; 
        regPIR.wl = 1; 
        regPIR.qsgate = 0; 
        regPIR.wladj = 0; 
        regPIR.rddskw = 0; 
        regPIR.wrdskw = 0; 
        regPIR.rdeye = 0; 
        regPIR.wreye = 0; 
        regPIR.srd = 0; 
        regPIR.vref = 0; 
        regPIR.ctldinit = 1;  /* should this be 1 ?. */
        regPIR.rdimminit = 0; 
        ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));

        /* Check the General Status register */

        /* poll for idone(bit 0) */
        ncpStatus = (ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0x21,  0x21,  1000,  10000));

        if (ncpStatus == NCP_ST_POLL_TIMEOUT)
        {
            ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
            errprintf("POLL timeout while waiting for write levelling training to complete [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
            NCP_CALL(NCP_ST_POLL_TIMEOUT);
        }

        /* Checking for Error's */
        ncpStatus = (ncp_sm_ddr4_phy_training_error_check(dev, smNode));
        if (ncpStatus == NCP_ST_ERROR)
        {
            ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
            errprintf("PGSR0 before training_error_check exit = 0x%x\n",tmp);
            NCP_CALL(NCP_ST_ERROR);
        }

        ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
        dbgprintf("SUCCESS: result while waiting for write levelling training to complete [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
    }

    /* work-around for Star 9000952604 */
    /* Disable data training data compare by writing DTCR0[7]=1'b0 (DTCMPD) and enable read preamble
     * training enable by writing DTCR1[2]=1'b1 (RDPRMBL_TRN) */

    ncr_read32(phyReg, NCP_PHY_DTCR0_5600, (ncp_uint32_t *)&regDTCR0);
    regDTCR0.dtcmpd = 0x0;
    ncr_write32(phyReg, NCP_PHY_DTCR0_5600, *((ncp_uint32_t *)&regDTCR0));

    ncr_read32(phyReg, NCP_PHY_DTCR1_5600, (ncp_uint32_t *)&regDTCR1);
    regDTCR1.rdprmvl_trn = 0x1;
    ncr_write32(phyReg, NCP_PHY_DTCR1_5600, *((ncp_uint32_t *)&regDTCR1));

    /* select to run basic gate training and read levelling by writing DTCR1[0]=1'b1 BSTEN and
     * DTCR1[1]=1'b1 RDLVLEN */
    ncr_read32(phyReg, NCP_PHY_DTCR1_5600, (ncp_uint32_t *)&regDTCR1);
    regDTCR1.bsten = 0x1;
    regDTCR1.rdlvlen = 0x1;
    ncr_write32(phyReg, NCP_PHY_DTCR1_5600, *((ncp_uint32_t *)&regDTCR1));

    /* Disable QS counter enable by writing DXCCR[22]=1'b0 QSCNTEN */
    ncr_read32(phyReg, NCP_PHY_DXCCR_5600, (ncp_uint32_t *)&regDXCCR);
    regDXCCR.qscnten = 0x0;
    ncr_write32(phyReg, NCP_PHY_DXCCR_5600, *((ncp_uint32_t *)&regDXCCR));

    /* Select to run Read DQS Gate training */
    /*************************************/
    if ((parms->packedPHYTrainingOptions >> 10) & 0x1)
    {
        /* PIR */
        ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
        regPIR.init = 1; 
        /* Actual init involves selection among the following steps:
         * ZCAL: impedance calibration
         * CA: CA training
         * PLLINIT: pll init (pll power, reset, gear shift, wait for lock)
         * DCAL: digital delay line calibration
         * PHYRST: reset the AC and DATX8
         * DRAMRST: reset, wait 200us
         * DRAMINIT: executes DRAM init sequence
         * WL: write leveling
         * QSGATE: read dqs gate training
         * WLADJ: write leveling adjust
         * RDDSKW: read data bit deskew
         * WRDSKW: write data bit deskew
         * RDEYE: read data eye training
         * WREYE: write data eye training
         *
         *
         * <specials are>
         * SRD: static read training
         * VREF: vref training
         * CTLDINIT: controller performs DRAM init
         * RDIMMINIT: rdimm init
         */
        regPIR.zcal = 0;  /* SAX1-2064_CHK: all these make regPIR=0x00040e01 "progressively" */
        regPIR.ca = 0; 
        regPIR.pllinit = 0; 
        regPIR.dcal = 0; 
        regPIR.phyrst = 0; 
        regPIR.dramrst = 0; 
        regPIR.draminit = 0; 
        regPIR.wl = 0; 
        regPIR.qsgate = 1; 
        regPIR.wladj = 0; 
        regPIR.rddskw = 0; 
        regPIR.wrdskw = 0; 
        regPIR.rdeye = 0; 
        regPIR.wreye = 0; 
        regPIR.srd = 0; 
        regPIR.vref = 0; 
        regPIR.ctldinit = 1;
        regPIR.rdimminit = 0; 
        ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));

        /* Check the General Status register */

        /* poll for idone(bit 0) */
        ncpStatus = (ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0x41,  0x41,  1000,  10000));

        if (ncpStatus == NCP_ST_POLL_TIMEOUT)
        {
            ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
            errprintf("POLL timeout while waiting for read DQS gate training to complete [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
            NCP_CALL(NCP_ST_POLL_TIMEOUT);
        }

        /* Checking for Error's */
        ncpStatus = (ncp_sm_ddr4_phy_training_error_check(dev, smNode));
        if (ncpStatus == NCP_ST_ERROR)
        {
            NCP_CALL(NCP_ST_ERROR);
        }

        ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
        dbgprintf("SUCCESS: result while waiting for read DQS gate training to complete [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
    }

    /* Enable QS counter enable by writing DXCCR[22]=1'b1 QSCNTEN */
    ncr_read32(phyReg, NCP_PHY_DXCCR_5600, (ncp_uint32_t *)&regDXCCR);
    regDXCCR.qscnten = 0x1;
    ncr_write32(phyReg, NCP_PHY_DXCCR_5600, *((ncp_uint32_t *)&regDXCCR));

    /* Perform Write Level Adjustment */
    /*************************************/
    if ((parms->packedPHYTrainingOptions >> 11) & 0x1)
    {
        /* PIR */
        ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
        regPIR.init = 1; 
        /* Actual init involves selection among the following steps:
         * ZCAL: impedance calibration
         * CA: CA training
         * PLLINIT: pll init (pll power, reset, gear shift, wait for lock)
         * DCAL: digital delay line calibration
         * PHYRST: reset the AC and DATX8
         * DRAMRST: reset, wait 200us
         * DRAMINIT: executes DRAM init sequence
         * WL: write leveling
         * QSGATE: read dqs gate training
         * WLADJ: write leveling adjust
         * RDDSKW: read data bit deskew
         * WRDSKW: write data bit deskew
         * RDEYE: read data eye training
         * WREYE: write data eye training
         *
         *
         * <specials are>
         * SRD: static read training
         * VREF: vref training
         * CTLDINIT: controller performs DRAM init
         * RDIMMINIT: rdimm init
         */
        regPIR.zcal = 0; /* SAX1-2064_CHK: all these make regPIR=0x00040e01 "progressively" */
        regPIR.ca = 0; 
        regPIR.pllinit = 0; 
        regPIR.dcal = 0; 
        regPIR.phyrst = 0; 
        regPIR.dramrst = 0; 
        regPIR.draminit = 0; 
        regPIR.wl = 0; 
        regPIR.qsgate = 0; 
        regPIR.wladj = 1; 
        regPIR.rddskw = 0; 
        regPIR.wrdskw = 0; 
        regPIR.rdeye = 0; 
        regPIR.wreye = 0; 
        regPIR.srd = 0; 
        regPIR.vref = 0; 
        regPIR.ctldinit = 1;
        regPIR.rdimminit = 0; 
        ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));

        /* Check the General Status register */

        /* poll for idone(bit 0) */
        ncpStatus = (ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0x81,  0x81,  1000,  10000));

        if (ncpStatus == NCP_ST_POLL_TIMEOUT)
        {
            ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
            errprintf("POLL timeout while waiting for write level adjustment to complete [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
            NCP_CALL(NCP_ST_POLL_TIMEOUT);
        }

        /* Checking for Error's */
        ncpStatus = (ncp_sm_ddr4_phy_training_error_check(dev, smNode));
        if (ncpStatus == NCP_ST_ERROR)
        {
            NCP_CALL(NCP_ST_ERROR);
        }

        ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
        dbgprintf("SUCCESS: result while waiting for write level adjustment to complete [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
    }


    /* Perform Static Read Data Training */
    /*************************************/

    /* PGCR0 */
    ncr_read32(phyReg, NCP_PHY_PGCR0_5600, (ncp_uint32_t *)&regPGCR0);
    /* PHY FIFO Reset: 0 resets AC and DATX8 FIFO's without resetting PUB logic.
     * write 1 to de-assert the reset later */
    regPGCR0.phyfrst = 0x0; 
    ncr_write32(phyReg, NCP_PHY_PGCR0_5600, *((ncp_uint32_t *)&regPGCR0));

    /* PGCR3 */
    ncr_read32(phyReg, NCP_PHY_PGCR3_5600, (ncp_uint32_t *)&regPGCR3);
    regPGCR3.rdmode = 0x1;  /* Static read response */
    ncr_write32(phyReg, NCP_PHY_PGCR3_5600, *((ncp_uint32_t *)&regPGCR3));

    /* PGCR0 */
    ncr_read32(phyReg, NCP_PHY_PGCR0_5600, (ncp_uint32_t *)&regPGCR0);
    /* PHY FIFO Reset: 0 resets AC and DATX8 FIFO's without resetting PUB logic.
     * write 1 to de-assert the reset later */
    regPGCR0.phyfrst = 0x1; 
    ncr_write32(phyReg, NCP_PHY_PGCR0_5600, *((ncp_uint32_t *)&regPGCR0));

    /* Start SRD trainings */
    /*****************************/
    if ((parms->packedPHYTrainingOptions >> 16) & 0x1)
    {
        /* PIR */
        ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
        regPIR.init = 1; 
        /* Actual init involves selection among the following steps:
         * ZCAL: impedance calibration
         * CA: CA training
         * PLLINIT: pll init (pll power, reset, gear shift, wait for lock)
         * DCAL: digital delay line calibration
         * PHYRST: reset the AC and DATX8
         * DRAMRST: reset, wait 200us
         * DRAMINIT: executes DRAM init sequence
         * WL: write leveling
         * QSGATE: read dqs gate training
         * WLADJ: write leveling adjust
         * RDDSKW: read data bit deskew
         * WRDSKW: write data bit deskew
         * RDEYE: read data eye training
         * WREYE: write data eye training
         *
         *
         * <specials are>
         * SRD: static read training
         * VREF: vref training
         * CTLDINIT: controller performs DRAM init
         * RDIMMINIT: rdimm init
         */
        regPIR.zcal = 0; /* SAX1-2064_CHK: all these make regPIR=0x0005f001 "progressively" */
        regPIR.ca = 0; 
        regPIR.pllinit = 0; 
        regPIR.dcal = 0; 
        regPIR.phyrst = 0; 
        regPIR.dramrst = 0; 
        regPIR.draminit = 0; 
        regPIR.wl = 0; 
        regPIR.qsgate = 0; 
        regPIR.wladj = 0; 
        regPIR.rddskw = 0; 
        regPIR.wrdskw = 0; 
        regPIR.rdeye = 0; 
        regPIR.wreye = 0; 
        regPIR.srd = 1; 
        regPIR.vref = 0; 
        regPIR.ctldinit = 1; 
        regPIR.rdimminit = 0; 
        ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));

        /* Check the General Status register */

        /* poll for idone(bit 0) */
        ncpStatus = (ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0x2001,  0x2001,  1000,  10000));

        if (ncpStatus == NCP_ST_POLL_TIMEOUT)
        {
            ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
            errprintf("POLL timeout while SRD training [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
            NCP_CALL(NCP_ST_POLL_TIMEOUT);
        }

        /* Checking for Error's */
        ncpStatus = (ncp_sm_ddr4_phy_training_error_check(dev, smNode));
        if (ncpStatus == NCP_ST_ERROR)
        {
            NCP_CALL(NCP_ST_ERROR);
        }

        ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
        dbgprintf("SUCCESS: result while waiting for srd training to complete [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
    }

    /* Read Data Bit Deskew Training */
    /*********************************/
    if ((parms->packedPHYTrainingOptions >> 12) & 0x1)
    {
        /* PIR */
        ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
        regPIR.init = 1; 
        /* Actual init involves selection among the following steps:
         * ZCAL: impedance calibration
         * CA: CA training
         * PLLINIT: pll init (pll power, reset, gear shift, wait for lock)
         * DCAL: digital delay line calibration
         * PHYRST: reset the AC and DATX8
         * DRAMRST: reset, wait 200us
         * DRAMINIT: executes DRAM init sequence
         * WL: write leveling
         * QSGATE: read dqs gate training
         * WLADJ: write leveling adjust
         * RDDSKW: read data bit deskew
         * WRDSKW: write data bit deskew
         * RDEYE: read data eye training
         * WREYE: write data eye training
         *
         *
         * <specials are>
         * SRD: static read training
         * VREF: vref training
         * CTLDINIT: controller performs DRAM init
         * RDIMMINIT: rdimm init
         */
        regPIR.zcal = 0; /* SAX1-2064_CHK: all these make regPIR=0x0005f001 "progressively" */
        regPIR.ca = 0; 
        regPIR.pllinit = 0; 
        regPIR.dcal = 0; 
        regPIR.phyrst = 0; 
        regPIR.dramrst = 0; 
        regPIR.draminit = 0; 
        regPIR.wl = 0; 
        regPIR.qsgate = 0; 
        regPIR.wladj = 0; 
        regPIR.rddskw = 1; 
        regPIR.wrdskw = 0; 
        regPIR.rdeye = 0; 
        regPIR.wreye = 0; 
        regPIR.srd = 0; 
        regPIR.vref = 0; 
        regPIR.ctldinit = 1; 
        regPIR.rdimminit = 0; 
        ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));

        /* Check the General Status register */

        /* poll for idone(bit 0) */
        ncpStatus = (ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0x101,  0x101,  1000,  10000));

        if (ncpStatus == NCP_ST_POLL_TIMEOUT)
        {
            ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
            errprintf("POLL timeout while read data bit deskew training [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
            NCP_CALL(NCP_ST_POLL_TIMEOUT);
        }

        /* Checking for Error's */
        ncpStatus = (ncp_sm_ddr4_phy_training_error_check(dev, smNode));
        if (ncpStatus == NCP_ST_ERROR)
        {
            NCP_CALL(NCP_ST_ERROR);
        }

        ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
        dbgprintf("SUCCESS: result while waiting for read deskew training to complete [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
    }

    /* Write Data Bit Deskew Training */
    /**********************************/
    if ((parms->packedPHYTrainingOptions >> 13) & 0x1)
    {
        /* PIR */
        ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
        regPIR.init = 1; 
        /* Actual init involves selection among the following steps:
         * ZCAL: impedance calibration
         * CA: CA training
         * PLLINIT: pll init (pll power, reset, gear shift, wait for lock)
         * DCAL: digital delay line calibration
         * PHYRST: reset the AC and DATX8
         * DRAMRST: reset, wait 200us
         * DRAMINIT: executes DRAM init sequence
         * WL: write leveling
         * QSGATE: read dqs gate training
         * WLADJ: write leveling adjust
         * RDDSKW: read data bit deskew
         * WRDSKW: write data bit deskew
         * RDEYE: read data eye training
         * WREYE: write data eye training
         *
         *
         * <specials are>
         * SRD: static read training
         * VREF: vref training
         * CTLDINIT: controller performs DRAM init
         * RDIMMINIT: rdimm init
         */
        regPIR.zcal = 0; /* SAX1-2064_CHK: all these make regPIR=0x0005f001 "progressively" */
        regPIR.ca = 0; 
        regPIR.pllinit = 0; 
        regPIR.dcal = 0; 
        regPIR.phyrst = 0; 
        regPIR.dramrst = 0; 
        regPIR.draminit = 0; 
        regPIR.wl = 0; 
        regPIR.qsgate = 0; 
        regPIR.wladj = 0; 
        regPIR.rddskw = 0; 
        regPIR.wrdskw = 1; 
        regPIR.rdeye = 0; 
        regPIR.wreye = 0; 
        regPIR.srd = 0; 
        regPIR.vref = 0; 
        regPIR.ctldinit = 1; 
        regPIR.rdimminit = 0; 
        ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));

        /* Check the General Status register */

        /* poll for idone(bit 0) */
        ncpStatus = (ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0x201,  0x201,  1000,  10000));

        if (ncpStatus == NCP_ST_POLL_TIMEOUT)
        {
            ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
            errprintf("POLL timeout while write data bit deskew training [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
            NCP_CALL(NCP_ST_POLL_TIMEOUT);
        }

        /* Checking for Error's */
        ncpStatus = (ncp_sm_ddr4_phy_training_error_check(dev, smNode));
        if (ncpStatus == NCP_ST_ERROR)
        {
            NCP_CALL(NCP_ST_ERROR);
        }

        ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
        dbgprintf("SUCCESS: result while waiting for write deskew training to complete [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
    }

    /* Read Data Eye Training */
    /**********************************/
    /* PIR */
    if ((parms->packedPHYTrainingOptions >> 14) & 0x1)
    {
        ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
        regPIR.init = 1; 
        /* Actual init involves selection among the following steps:
         * ZCAL: impedance calibration
         * CA: CA training
         * PLLINIT: pll init (pll power, reset, gear shift, wait for lock)
         * DCAL: digital delay line calibration
         * PHYRST: reset the AC and DATX8
         * DRAMRST: reset, wait 200us
         * DRAMINIT: executes DRAM init sequence
         * WL: write leveling
         * QSGATE: read dqs gate training
         * WLADJ: write leveling adjust
         * RDDSKW: read data bit deskew
         * WRDSKW: write data bit deskew
         * RDEYE: read data eye training
         * WREYE: write data eye training
         *
         *
         * <specials are>
         * SRD: static read training
         * VREF: vref training
         * CTLDINIT: controller performs DRAM init
         * RDIMMINIT: rdimm init
         */
        regPIR.zcal = 0; /* SAX1-2064_CHK: all these make regPIR=0x0005f001 "progressively" */
        regPIR.ca = 0; 
        regPIR.pllinit = 0; 
        regPIR.dcal = 0; 
        regPIR.phyrst = 0; 
        regPIR.dramrst = 0; 
        regPIR.draminit = 0; 
        regPIR.wl = 0; 
        regPIR.qsgate = 0; 
        regPIR.wladj = 0; 
        regPIR.rddskw = 0; 
        regPIR.wrdskw = 0; 
        regPIR.rdeye = 1; 
        regPIR.wreye = 0; 
        regPIR.srd = 0; 
        regPIR.vref = 0; 
        regPIR.ctldinit = 1; 
        regPIR.rdimminit = 0; 
        ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));

        /* Check the General Status register */

        /* poll for idone(bit 0) */
        ncpStatus = (ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0x401,  0x401,  1000,  10000));

        if (ncpStatus == NCP_ST_POLL_TIMEOUT)
        {
            ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
            errprintf("POLL timeout while read data eye training [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
            NCP_CALL(NCP_ST_POLL_TIMEOUT);
        }

        /* Checking for Error's */
        ncpStatus = (ncp_sm_ddr4_phy_training_error_check(dev, smNode));
        if (ncpStatus == NCP_ST_ERROR)
        {
            NCP_CALL(NCP_ST_ERROR);
        }

        ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
        dbgprintf("SUCCESS: result while waiting for read eye training to complete [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
    }

    /* Write Data Eye Training */
    /**********************************/
    if ((parms->packedPHYTrainingOptions >> 15) & 0x1)
    {
        /* PIR */
        ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
        regPIR.init = 1; 
        /* Actual init involves selection among the following steps:
         * ZCAL: impedance calibration
         * CA: CA training
         * PLLINIT: pll init (pll power, reset, gear shift, wait for lock)
         * DCAL: digital delay line calibration
         * PHYRST: reset the AC and DATX8
         * DRAMRST: reset, wait 200us
         * DRAMINIT: executes DRAM init sequence
         * WL: write leveling
         * QSGATE: read dqs gate training
         * WLADJ: write leveling adjust
         * RDDSKW: read data bit deskew
         * WRDSKW: write data bit deskew
         * RDEYE: read data eye training
         * WREYE: write data eye training
         *
         *
         * <specials are>
         * SRD: static read training
         * VREF: vref training
         * CTLDINIT: controller performs DRAM init
         * RDIMMINIT: rdimm init
         */
        regPIR.zcal = 0; /* SAX1-2064_CHK: all these make regPIR=0x0005f001 "progressively" */
        regPIR.ca = 0; 
        regPIR.pllinit = 0; 
        regPIR.dcal = 0; 
        regPIR.phyrst = 0; 
        regPIR.dramrst = 0; 
        regPIR.draminit = 0; 
        regPIR.wl = 0; 
        regPIR.qsgate = 0; 
        regPIR.wladj = 0; 
        regPIR.rddskw = 0; 
        regPIR.wrdskw = 0; 
        regPIR.rdeye = 0; 
        regPIR.wreye = 1; 
        regPIR.srd = 0; 
        regPIR.vref = 0; 
        regPIR.ctldinit = 1; 
        regPIR.rdimminit = 0; 
        ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));

        /* Check the General Status register */

        /* poll for idone(bit 0) */
        ncpStatus = (ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0x801,  0x801,  1000,  10000));

        if (ncpStatus == NCP_ST_POLL_TIMEOUT)
        {
            ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
            errprintf("POLL timeout while write data eye training [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
            NCP_CALL(NCP_ST_POLL_TIMEOUT);
        }

        /* Checking for Error's */
        ncpStatus = (ncp_sm_ddr4_phy_training_error_check(dev, smNode));
        if (ncpStatus == NCP_ST_ERROR)
        {
            NCP_CALL(NCP_ST_ERROR);
        }

        ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
        dbgprintf("SUCCESS: result while waiting for write eye training to complete [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
    }

    /* VREF Training */
    /*****************/
    if (((parms->packedPHYTrainingOptions >> 17) & 0x1) && (ddr_recovery == FALSE))
    {
        /* PIR */
        ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
        regPIR.init = 1; 
        /* Actual init involves selection among the following steps:
         * ZCAL: impedance calibration
         * CA: CA training
         * PLLINIT: pll init (pll power, reset, gear shift, wait for lock)
         * DCAL: digital delay line calibration
         * PHYRST: reset the AC and DATX8
         * DRAMRST: reset, wait 200us
         * DRAMINIT: executes DRAM init sequence
         * WL: write leveling
         * QSGATE: read dqs gate training
         * WLADJ: write leveling adjust
         * RDDSKW: read data bit deskew
         * WRDSKW: write data bit deskew
         * RDEYE: read data eye training
         * WREYE: write data eye training
         *
         *
         * <specials are>
         * SRD: static read training
         * VREF: vref training
         * CTLDINIT: controller performs DRAM init
         * RDIMMINIT: rdimm init
         */
        regPIR.zcal = 0; 
        regPIR.ca = 0; 
        regPIR.pllinit = 0; 
        regPIR.dcal = 0; 
        regPIR.phyrst = 0; 
        regPIR.dramrst = 0; 
        regPIR.draminit = 0; 
        regPIR.wl = 0; 
        regPIR.qsgate = 0; 
        regPIR.wladj = 0; 
        regPIR.rddskw = 0; 
        regPIR.wrdskw = 0; 
        regPIR.rdeye = 0; 
        regPIR.wreye = 0; 
        regPIR.srd = 0; 
        regPIR.vref = 1; 
        regPIR.ctldinit = 0; 
        regPIR.rdimminit = 0; 
        ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));

        /* Check the General Status register */

        /* poll for idone(bit 0) */
        ncpStatus = (ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0x4001,  0x4001,  1000,  10000));

        if (ncpStatus == NCP_ST_POLL_TIMEOUT)
        {
            ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
            errprintf("POLL timeout while VREF training [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
            NCP_CALL(NCP_ST_POLL_TIMEOUT);
        }

        /* Checking for Error's */
        ncpStatus = (ncp_sm_ddr4_phy_training_error_check(dev, smNode));
        if (ncpStatus == NCP_ST_ERROR)
        {
            NCP_CALL(NCP_ST_ERROR);
        }

        ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
        dbgprintf("SUCCESS: result while waiting for vref training to complete [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
    }

    ncr_read32(phyReg, NCP_PHY_VTDR_5600, &tmp);
    /*dbgprintf("After VREF training VTDR result = 0x%x\n",tmp);*/

    ncr_read32(phyReg, NCP_PHY_DTCR0_5600, (ncp_uint32_t *)&regDTCR0);
    regDTCR0.rfshdt = 0x9; /* Assuming PHY refresh enabled during training */
    ncr_write32(phyReg, NCP_PHY_DTCR0_5600, *((ncp_uint32_t *)&regDTCR0));

    /* PGCR1 */
    ncr_read32(phyReg, NCP_PHY_PGCR1_5600, (ncp_uint32_t *)&regPGCR1);
    /* Enables if set the PUB to control the interface to the PHY and SDRAM.
     * In this mode the DFI commands from the controller are ignored. The bit must
     * be set to 0 after the system determines it is convenient to pass control of the DFI
     * bus to the controller. When set to 0 the DFI interface has control of the PHY and SDRAM
     * interface except when trigerring pub operations such as BIST, DCU or data training.
     */
    regPGCR1.pubmode = 0x0;
    ncr_write32(phyReg, NCP_PHY_PGCR1_5600, *((ncp_uint32_t *)&regPGCR1));

    NCP_RETURN_LABEL
        return ncpStatus;
}

ncp_st_t
ncp_sm_ddr4_post_phy_training_mc_setup_self_refresh(
                                                    ncp_dev_hdl_t   dev,
                                                    ncp_uint32_t    smNode,
                                                    ncp_sm_parms_t *parms)
{
    ncp_st_t		ncpStatus = NCP_ST_SUCCESS;
    ncp_region_id_t 	ctlReg  = NCP_REGION_ID(smNode, NCP_SYSMEM_TGT_DENALI);
    ncp_region_id_t 	phyReg 	= NCP_REGION_ID(smNode, NCP_SYSMEM_TGT_PHY);

    ncp_denali_DENALI_CTL_41_5600_t  reg41 = {0};
    ncp_denali_DENALI_CTL_125_5600_t reg125 = {0};
    ncp_denali_DENALI_CTL_368_5600_t reg368 = {0};
    ncp_denali_DENALI_CTL_369_5600_t reg369 = {0};
    ncp_denali_DENALI_CTL_370_5600_t reg370 = {0};
    ncp_denali_DENALI_CTL_371_5600_t reg371 = {0};
    ncp_phy_DSGCR_5600_t regDSGCR = {0};

    /* DENALI_CTL_41 */
    ncr_read32(ctlReg, NCP_DENALI_CTL_41_5600, (ncp_uint32_t *)&reg41);
    /* the refresh command time in clocks */
    reg41.tref_enable = 1; /* enables refresh commands */
    ncr_write32(ctlReg, NCP_DENALI_CTL_41_5600, *((ncp_uint32_t *)&reg41));

    /* DENALI_CTL_125 */
    ncr_read32(ctlReg, NCP_DENALI_CTL_125_5600, (ncp_uint32_t *)&reg125);
    /* enable an automatic controller initiated update after every refresh */
    reg125.ctrlupd_req_per_aref_en = 0x1;
    ncr_write32(ctlReg, NCP_DENALI_CTL_125_5600, *((ncp_uint32_t *)&reg125));

#if 1 /* SAX1-2064_CHK */
    /* DSGCR */
    ncr_read32(phyReg, NCP_PHY_DSGCR_5600, (ncp_uint32_t *)&regDSGCR);
    regDSGCR.cuaen = 1; /* Controller Update Acknowledge Enable */
    ncr_write32(phyReg, NCP_PHY_DSGCR_5600, *((ncp_uint32_t *)&regDSGCR));
#endif

    /* clear 17th and 30th bit of interrupt before clearing the mask, else interrupt gets set. */
    /* DENALI_CTL_368 */
    ncr_read32(ctlReg, NCP_DENALI_CTL_368_5600, (ncp_uint32_t *)&reg368);
    reg368.int_ack = 0xffffffff;
    ncr_write32(ctlReg, NCP_DENALI_CTL_368_5600, *((ncp_uint32_t *)&reg368));

    /* DENALI_CTL_369 */
    ncr_read32(ctlReg, NCP_DENALI_CTL_369_5600, (ncp_uint32_t *)&reg369);
    reg369.int_ack = 0x3;
    ncr_write32(ctlReg, NCP_DENALI_CTL_369_5600, *((ncp_uint32_t *)&reg369));

    /* int_mask */
    /* DENALI_CTL_370 */
    ncr_read32(ctlReg, NCP_DENALI_CTL_370_5600, (ncp_uint32_t *)&reg370);
    reg370.int_mask = 0x0;
    ncr_write32(ctlReg, NCP_DENALI_CTL_370_5600, *((ncp_uint32_t *)&reg370));

    /* DENALI_CTL_371 */
    ncr_read32(ctlReg, NCP_DENALI_CTL_371_5600, (ncp_uint32_t *)&reg371);
    reg371.int_mask &= ~(0x7);
    ncr_write32(ctlReg, NCP_DENALI_CTL_371_5600, *((ncp_uint32_t *)&reg371));

    NCP_RETURN_LABEL
        return ncpStatus;
}

ncp_st_t
ncp_sysmem_init_synopphy_self_refresh(
                                      ncp_dev_hdl_t   dev,
                                      ncp_uint32_t    smId,
                                      ncp_sm_parms_t *parms)
{
    ncp_st_t	ncpStatus = NCP_ST_SUCCESS;
    ncp_common_timing_parameters_t	ctm = {0};
    ncp_uint32_t smNode = 0;

    ncp_uint32_t preRetentionZQ[] = {0,0,0,0};


#ifndef __UBOOT__
    /* cmem check
     * XLF has 1 CMEM, X9 has 2 CMEM's
     * If smId == 4 && chip == XLF, then setup CMEM-0
     * If smId == 2 && chip == X9, then setup CMEM-0
     * If smId == 3 && chip == X9, then setup CMEM-1
     */

    if (((parms->version == NCP_CHIP_ACPXLF) && (smId == 4)) ||
        ((parms->version == NCP_CHIP_ACP56xx) && (smId == 2)) ||
        ((parms->version == NCP_CHIP_ACP56xx) && (smId == 3)))
    {
        /* not for cmem */
        NCP_CALL(NCP_ST_ERROR);
    }
#endif

    switch (smId) {
        case 0:
            smNode  = 0x22;	/* X9/XLF */
        break;
        case 1:
            smNode  = 0xf;	/* X9/XLF */
        break;
        case 2:
            smNode  = 0x23;	/* XLF */
        break;
        case 3:
            smNode  = 0x24;	/* XLF */
        break;
        default:
            NCP_CALL(NCP_ST_ERROR);
    }

#ifdef UBOOT
    if (cold == get_ddr_init_type())
#else
    /* From Uboot this would get set when this top level
     * function is called, but from ncpBootMem CLI
     * this support is not added yet- hence this kludge
     */
    parms->ddrRecovery = TRUE;
    if (parms->ddrRecovery == FALSE)
#endif
    {
        errprintf("Incorrect function being called %s\n", __func__);
        NCP_CALL(NCP_ST_ERROR);
    }
    dbgprintf("Calling %s for Unplanned DDR4 Recovery for smNode=0x%x\n", __func__, smNode);

    /* ctm is populated so it can be commonly used during mc,phy setup */
    NCP_CALL(ncp_sm_common_setup_56xx(dev, smNode, parms, &ctm)); 

    /* Program MC to put DRAM into self-refresh mode */
    NCP_CALL(ncp_sm_ddr4_mc_sf_mode(dev, smNode, parms, &ctm, TRUE));

    /* Save pre-data-retention ZQ calibrated values i.e. impedance data */
    NCP_CALL(ncp_sm_ddr4_pre_retention_save(dev, smNode, parms, &ctm, preRetentionZQ));

    /* retain the signals on PHY DDR interface i.e. GPR0 as follows:
     * GPR0 = 0x1 Latch IO to maintain self_refresh
     * GPR0 = 0x2 After PHY init and before training
     * GPR0 = 0x6 After 0x40003 PIR training and Start bit
     * GPR0 = 0x2 Un Latch IO
     */

    /* Latch IO of PHY and appropriate signals to maintain self-refresh */
    NCP_CALL(ncp_sm_ddr4_phy_self_refresh_io_control(dev, smNode, parms, &ctm, 0x1));

    /* Should not mess with power */
    /*NCP_CALL(ncp_sm_ddr4_phy_pd_control(dev, smNode, parms, &ctm));*/

    /* Reset MC and PHY */
    NCP_CALL(ncp_sm_ddr4_reset_mc_phy(dev, smNode, parms, &ctm));

    /* Initialize the system memory controller with self_refresh set
     * This is EXACTLY same as cold-start MC init with existing mod for
     * write pwrup_srefresh_exit in ctl_46 before start bit in ctl_00 asserted here */
    NCP_CALL(ncp_sm_denali_2041_init_56xx(dev, smNode, parms, &ctm));

    /* Initialize the PHY
     * This is DIFFERENT than cold-start PHY init with below mods:
     * In PIR: set zcal to 0, dcalpse to 0 and zcalbyp to 1 (Bypass ZQ cal PIR.zcalbyp (phy.PIR 0x40000071))
     * wait for pgsr0.idone
     * this might take PLL RST time (4800 ctl_clk cycles) + PLL Lock time (53334 ctl_clk cycles)
     * marks MC DFI_Init() completion. PHY Init done with Calibration bypassed.
     * Trigger ZQ cal pir.zcal (phy.PIR 0x40003)
     * wait till done pgsr0.zcdone
     * wait for pgsr0.idone (PUB acks)
     * mark ZCAL Update PHY Init done.
     * write mode reg
     * clear all interrupts
     * poll phy.GPR0 for MEM_RST_VALID
     */
    NCP_CALL(ncp_sm_ddr4_phy_init_self_refresh(dev, smNode, parms, &ctm, preRetentionZQ));

    /* Now go through training
     * This is DIFFERENT than cold-start PHY training with below mods:
     * previous function does:
     *  - config PHY to use previously trained values (if PHY is reset ?.)
     *  - override data to ZQnDR.ZDATA (write pre-retention ZQ cal values read from 4 previous spots in PHY)
     *
     * There are many differences in training compared to upfront PHY training as detailed within
     * the function itself.
     *  - assert zqcr.force zcal vt update and clear
     *  - General Training steps follow:
     *      - Indicate PHY that SDRAM init will not be triggerred (pir.init (0x40040001) and pir.ctldinit)
     *      - poll PGSR0
     *  - mark VT update PHY init done
     *   Trigger data training again (except VREF).Reuse phy_training()
     *   - start data training
     *   - DTCR0.DTRPTN 0x7
     *   - DTCR0.DTMPR 0x1
     *   - DTCR0.DTCMPD 0x1
     *   - DTCR0.RFSHENT 0x9
     *   - DTCR0.DTWBDDM 0x1
     *   - DTCR0.DTBDC 0x1
     *   - DTCR0.DTDRS 0x0
     *   - DTCR0.DTDBS 0x0
     *   - DTCR0.DTRDBITR 0x0
     *   - DTCR0.DTDEN 0x0
     *   - DTCR0.DTDSTP 0x0
     *   - DTCR0.DTEXD 0x0
     *   - DTCR0.DTEXG 0x0
     *   - DTCR0.RFSHDT 0x9
     *   - set DTCR1.RANKEN basedon num_ranks
     *   - set DTCR1.DTRANK
     *   - program DTAR0.MPRLOC
     *   BASIC Training: phy.PIR 0x40e01 => poll PGSR0 for rank completion
     *   ncp_sm_ddr4_phy_training_error_check()
     *   - PHYFRST -> 0, change RDMODE to 1 -> PHYFRST -> 1
     *   Do SRD + Eye + Deskew trainings phy.PIR 0x5f001 => poll PGSR0
     *   ncp_sm_ddr4_phy_training_error_check()
     */
    NCP_CALL(ncp_sm_ddr4_phy_training_self_refresh(dev, smNode, parms));

    /* This is nearly similar to upfront PHY init with below mod:
     * SAX1-2064_CHK check on tref_enable setting ??
     *  set ctrlupd_req_per_aref_en -> cuaen
     *  clear denali 368, 370 (17th and 30th bit)
     */
    NCP_CALL(ncp_sm_ddr4_post_phy_training_mc_setup_self_refresh(dev, smNode, parms));

    /* UnLatch IO of PHY and appropriate signals to maintain self-refresh
     * - de-assert PHY_TOP data retention enable signals
     * - set GPR0
     * - write phy.GPR0.
     */
    NCP_CALL(ncp_sm_ddr4_phy_self_refresh_io_control(dev, smNode, parms, &ctm, 0x2));

    /* Program MC to come out self-refresh. Will go to IDLE. */
    NCP_CALL(ncp_sm_ddr4_mc_sf_mode(dev, smNode, parms, &ctm, FALSE));

    NCP_RETURN_LABEL
#ifdef NCP_SM_PHY_REG_DUMP
        if (NCP_ST_SUCCESS != ncpStatus)
        {
            /* Dump contents of synop phy regs on training failures */
            ncp_sm_ddr4_phy_reg_dump(dev, smNode);
        }
#endif
    return ncpStatus;
}
