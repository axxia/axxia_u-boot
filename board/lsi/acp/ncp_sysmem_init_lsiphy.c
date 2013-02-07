/**************************************************************************
 **                                                                       *
 **   LSI Corporation CONFIDENTIAL                                        *
 **                           PROPRIETARY NOTE                            *
 **                                                                       *
 **    This software contains information confidential and proprietary    *
 **    to LSI Corporation Inc.  It shall not be reproduced in whole or in *
 **    part, or transferred to other documents, or disclosed to third     *
 **    parties, or used for any purpose other than that for which it was  *
 **    obtained, without the prior written consent of LSI Corporation Inc.*
 **    (c) 2008, LSI Corporation Inc.  All rights reserved.               *
 **                                                                       *
 **  **********************************************************************
 **
 **  **********************************************************************
 **   File:         $HeadURL$
 **   Version:      $Revision$
 **   Date:         $Date$
 **
 **************************************************************************/

#ifndef UBOOT
#include <stdio.h>

#include "ncp.h"
#include "ncp_pvt.h"
#include "ncp_sysmem_ext.h"
#include "ncp_sysmem_lsiphy.h"
#endif

/* register definitions for ACP25xx */
#define NCP_SYSMEM_LSIPHY
#include "regs/ncp_phy_regs_acp2500.h"
#include "regs/ncp_phy_reg_defines_acp2500.h"
#include "regs/ncp_denali_regs_acp2500.h"
#include "regs/ncp_denali_reg_defines_acp2500.h"

#define NCP_SM_BURST_SIZE 128
#define NCP_SM_DATA_BYTELANES 8
#define NCP_SM_WL_MAX_LOOPS   4


typedef struct {
    ncp_uint32_t    early;
    ncp_uint32_t    late;
    ncp_uint32_t    bad;
} ncp_sm_bad_bytelane_t;

typedef struct {
    ncp_uint16_t    smId;
    ncp_uint16_t    offset;
    ncp_uint16_t    value;
} ncp_sm_reg_table_t;



/* temp */
typedef void ncp_sm_phy_stat_t;

#if 0
static ncp_st_t
ncp_sm_denali_init(
    ncp_dev_hdl_t dev,
    ncp_uint32_t  smId,
    ncp_sm_parms_t *parms)
{
    ncp_st_t ncpStatus;
    ncp_region_id_t ctlReg;


    if (smId >= NCP_SYSMEM_NUM_NODES) {
        NCP_CALL(NCP_ST_SYSMEM_INVALID_ID);
    }

    NCP_COMMENT("sysmem %d denali controller init", smId);


    NCP_CALL(ncp_sm_denali_2041_init(dev, ctlReg, parms));

NCP_RETURN_LABEL
    return ncpStatus;
}
#endif


typedef ncp_st_t
(*phy_training_run_fn_t) (
        ncp_dev_hdl_t               dev,
        ncp_uint32_t                smId,
        ncp_region_id_t             ctlRegion,
        ncp_region_id_t             phyRegion,
        ncp_uint32_t                rank,
        ncp_uint32_t                edge,
        ncp_sm_phy_training_mode_t  mode,
        ncp_sm_parms_t             *parms);


#define SM_REG_DUMP

#ifdef SM_REG_DUMP

static ncp_st_t 
dump_regs(ncp_dev_hdl_t dev, ncp_uint32_t region, ncp_uint32_t offset, ncp_uint32_t num)
{
    int i;
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_uint32_t reg;
    for (i = 0; i < num;  i++) 
    {
        if ( (i & 0x3) == 0) printf("  %d.%d.0x%08x  ", NCP_NODE_ID(region), NCP_TARGET_ID(region), offset);

        ncr_read32(region, offset, &reg);
        printf(" %08x", reg);
        offset += 4;

        if ( ( i & 0x3) == 3) printf("\n");
    }
NCP_RETURN_LABEL
    return ncpStatus;
}

static ncp_st_t 
dump_config(ncp_dev_hdl_t dev, 
        ncp_region_id_t region,
        ncp_uint32_t    num_bls)
{

    ncp_st_t ncpStatus = NCP_ST_SUCCESS; 
    ncp_uint32_t reg;
    int i;

    printf("\n### PHY config registers ### \n");
    
    printf("PHYCONFIG0-2:\n");
    dump_regs(dev, region, 0x10000, 3);

    printf("\nPHYSMCTRL/STAT:\n");
    dump_regs(dev, region, 0x10084, 2);

    printf("\nPHYDEBUG:\n");
    dump_regs(dev, region, 0x100d0, 4);

    
    printf("\n DPCONFIG0 : ");
    for (i = 0; i < num_bls; i++) 
    {
        ncr_read32(region, 
                NCP_PHY_CFG_SYSMEM_PHY_DPCONFIG0_BL0 + (i * 0x800), &reg);
        printf(" 0x%04x ", reg);
    }

    printf("\n DPCONFIG2 : ");
    for (i = 0; i < num_bls; i++) 
    {
        ncr_read32( region, 
                NCP_PHY_CFG_SYSMEM_PHY_DPCONFIG2_BL0 + (i * 0x800), &reg);
        printf(" 0x%04x ", reg);
    }

    printf("\nPHYCONFIG3 : ");
    for (i = 0; i < num_bls; i++) 
    {
        ncr_read32( region, 
                NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG3_BL0 + (i * 0x800), &reg);
        printf(" 0x%04x ", reg);
    }

    printf("\n");

NCP_RETURN_LABEL
    return ncpStatus;
}

static ncp_st_t 
dump_qrtr(ncp_dev_hdl_t dev, 
        ncp_region_id_t region,
        ncp_uint32_t    num_bls)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS; 
    ncp_uint32_t reg;
    int i;

    printf("\n### Quarter cycle eval registers ###\n");

    ncr_read32( region, 
                NCP_PHY_CFG_SYSMEM_PHY_ADR0_GTDLYCTRL, &reg);
    printf("ADR0_GTDLYCTRL : 0x%08x\n", reg);

    ncr_read32( region, 
                NCP_PHY_CFG_SYSMEM_PHY_ADR1_GTDLYCTRL, &reg);
    printf("ADR1_GTDLYCTRL : 0x%08x\n", reg);

    ncr_read32( region, 
                NCP_PHY_CFG_SYSMEM_PHY_ADR2_GTDLYCTRL, &reg);
    printf("ADR2_GTDLYCTRL : 0x%08x\n", reg);


    printf("Align Delays \n");
    for (i = 0; i < num_bls; i++) {
        ncr_read32( region, (0x100c8 + (i * 0x800)) , &reg);
        printf("%08x ", reg);
    }
    printf("\n");
NCP_RETURN_LABEL
    return ncpStatus;
}

static ncp_st_t 
dump_wl(ncp_dev_hdl_t dev, 
        ncp_region_id_t region,
        ncp_uint32_t    num_bls,
        ncp_uint32_t    num_ranks)
{

    ncp_st_t ncpStatus = NCP_ST_SUCCESS; 
    ncp_uint32_t reg;
    ncp_uint32_t offset;
    int i, j;

    printf("\n### Write Leveling Registers ###");
    
    printf("\nWRTLVLRESP  : ");
    for (i = 0; i < num_bls; i++) 
    {
        ncr_read32( region, 
                NCP_PHY_CFG_SYSMEM_PHY_WRLVLRESP_BL(i), &reg);
        printf(" 0x%04x ", reg);
    }

    for (j = 0; j < num_ranks; j++) {
        printf("\nWRTLVLUPP[%d]: ", j);
        for (i = 0; i < num_bls; i++) 
        {
            ncr_read32( region, 
                NCP_PHY_CFG_SYSMEM_PHY_WRTLVLUPP_BL_CS(i, j), &reg);
            printf(" 0x%04x ", reg);
        }

        printf("\nWRTLVLLOW[%d]: ", j);
        for (i = 0; i < num_bls; i++) 
        {
            ncr_read32( region, 
                NCP_PHY_CFG_SYSMEM_PHY_WRTLVLLOW_BL_CS(i, j), &reg);
            printf(" 0x%04x ", reg);
        }
    }

    printf("\n");

    for (j = 0; j < num_ranks; j++) {
        printf("\nWRTALIGNDQ[%d]:\n", j);
        offset = 0x18000 + (j * 0x100) ;
        for (i = 0; i < num_bls; i++) 
        {
            dump_regs(dev, region, offset, 12);
            offset += 0x800;
        }
    }



NCP_RETURN_LABEL
    return ncpStatus;
}



static ncp_st_t 
dump_gt(ncp_dev_hdl_t dev, 
        ncp_region_id_t region,
        ncp_uint32_t    num_bls,
        ncp_uint32_t    num_ranks)
{

    ncp_st_t ncpStatus = NCP_ST_SUCCESS; 
    ncp_uint32_t reg;
    int i, j;

    printf("\n### Gate Training Registers ### \n");
    printf("GTTRAINSTATx\n");
    dump_regs(dev, region, 0x10020, 2);
    
    for (j = 0; j < num_ranks; j++) 
    {
        printf("\nGTUPPCTRL[%d]: ", j);
        for (i = 0; i < num_bls; i++) 
        {
            ncr_read32( region, 
                    NCP_PHY_CFG_SYSMEM_PHY_GTUPPCTRL_BL_CS(i, j), &reg);
            printf(" 0x%04x ", reg);
        }

        printf("\nGTLOWCTRL[%d]: ", j);
        for (i = 0; i < num_bls; i++) 
        {
            ncr_read32( region, 
                    NCP_PHY_CFG_SYSMEM_PHY_GTLOWCTRL_BL_CS(i, j), &reg);
            printf(" 0x%04x ", reg);
        }
    }

    printf("\n");



NCP_RETURN_LABEL
    return ncpStatus;
}


static ncp_st_t 
dump_rl(ncp_dev_hdl_t dev, 
        ncp_region_id_t regionId,
        ncp_uint32_t    num_bls,
        ncp_uint32_t    num_ranks)
{

    ncp_st_t ncpStatus = NCP_ST_SUCCESS; 
    ncp_uint32_t reg;
    ncp_uint32_t offset;

    int i, j;

    printf("\n### Read Leveling Registers ### \n");
    printf("RDDSKWSTAT:\n");
    dump_regs(dev, regionId, 0x1002c, 4);


    printf("\nP2F          : ");
    for (i = 0; i < num_bls; i++) 
    {
        ncr_read32( regionId, 
                    NCP_PHY_CFG_SYSMEM_PHY_RDLVLP2FDLY_BL(i),
                    &reg);
        printf(" 0x%04x ", reg);
    }

    printf("\nF2P          : ");
    for (i = 0; i < num_bls; i++) 
    {
        ncr_read32( regionId, 
                    NCP_PHY_CFG_SYSMEM_PHY_RDLVLF2PDLY_BL(i),
                    &reg);
        printf(" 0x%04x ", reg);
    }

    for (j = 0; j < num_ranks; j++) 
    {
        printf("\nPUPPDQSDLY[%d]: ", j);
        for (i = 0; i < num_bls; i++) 
        {
            ncr_read32( regionId, 
                        NCP_PHY_CFG_SYSMEM_PHY_PUPPDQSDLY_BL_CS(i, j),
                     &reg);
            printf(" 0x%04x ", reg);
        }

        printf("\nNUPPDQSDLY[%d]: ", j);
        for (i = 0; i < num_bls; i++) 
        {
            ncr_read32( regionId, 
                        NCP_PHY_CFG_SYSMEM_PHY_NUPPDQSDLY_BL_CS(i, j),
                        &reg);
            printf(" 0x%04x ", reg);
        }

        printf("\nPLOWDQSDLY[%d]: ", j);
        for (i = 0; i < num_bls; i++) 
        {
            ncr_read32( regionId, 
                        NCP_PHY_CFG_SYSMEM_PHY_PLOWDQSDLY_BL_CS(i, j),
                        &reg);
            printf(" 0x%04x ", reg);
        }

        printf("\nNLOWDQSDLY[%d]: ", j);
        for (i = 0; i < num_bls; i++) 
        {
            ncr_read32( regionId, 
                        NCP_PHY_CFG_SYSMEM_PHY_NLOWDQSDLY_BL_CS(i, j),
                        &reg);
            printf(" 0x%04x ", reg);
        }
    }

    printf("\n");
    for (j = 0; j < num_ranks; j++) 
    {
        printf("\nRDALIGNGNDQ[%d]: \n", j);
        offset = 0x18040 + (j * 0x100);
        for (i = 0; i < num_bls; i++) 
        {
            dump_regs(dev, regionId, offset, 8);
            offset += 0x800;
        }
    }

NCP_RETURN_LABEL
    return ncpStatus;
}

static ncp_st_t 
dump_ratio(ncp_dev_hdl_t dev, 
        ncp_region_id_t regionId,
        ncp_uint32_t    num_bls,
        ncp_uint32_t    num_ranks)
{

    ncp_st_t ncpStatus = NCP_ST_SUCCESS; 
    ncp_uint32_t reg;

    int i, j;

    printf("\n### Ratio Registers ### \n");

    for (j = 0; j < num_ranks; j ++) 
    {
        printf("\n PUPPRATIO[%d]: ", j);
        for (i = 0; i < num_bls; i++) 
        {
            ncr_read32( regionId, 
                        NCP_PHY_CFG_SYSMEM_PHY_PUPPRATIO_BL_CS(i, j),
                        &reg);
            printf(" 0x%04x ", reg);
        }
    
        printf("\n NUPPRATIO[%d]: ", j);
        for (i = 0; i < num_bls; i++) 
        {
            ncr_read32( regionId, 
                        NCP_PHY_CFG_SYSMEM_PHY_NUPPRATIO_BL_CS(i, j),
                        &reg);
            printf(" 0x%04x ", reg);
        }
    
        printf("\n PLOWRATIO[%d]: ", j);
        for (i = 0; i < num_bls; i++) 
        {
            ncr_read32( regionId, 
                        NCP_PHY_CFG_SYSMEM_PHY_PLOWRATIO_BL_CS(i, j),
                        &reg);
            printf(" 0x%04x ", reg);
        }
    
        printf("\n PLOWRATIO[%d]: ", j);
        for (i = 0; i < num_bls; i++) 
        {
            ncr_read32( regionId, 
                        NCP_PHY_CFG_SYSMEM_PHY_PLOWRATIO_BL_CS(i, j),
                        &reg);
            printf(" 0x%04x ", reg);
        }
    }
    
    
NCP_RETURN_LABEL
    return ncpStatus;
}




/*
 * ncp_sm_lsiphy_reg_dump
 *
 */
ncp_st_t
ncp_sm_lsiphy_reg_dump(
    ncp_dev_hdl_t dev,
    ncp_uint32_t smId)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_uint32_t num_bls;
    ncp_uint32_t num_ranks;
    ncp_region_id_t regionId;


    if (smId < NCP_SYSMEM_NUM_NODES) {
        num_bls = NCP_SM_NUM_BYTE_LANES;
        num_ranks = 2;
        printf("##############################\n");
        printf("### Sysmem %d Register Dump ###\n", smId);
    } 
    else 
    {
        num_bls = NCP_CM_NUM_BYTE_LANES;
        num_ranks = 1;

        printf("\n");
        printf("##################################\n");
        printf("### Treemem %d Register Dump ###\n", 
                            smId - NCP_SYSMEM_NUM_NODES);
    }

    switch (smId) {
        case 0: 
            regionId = NCP_REGION_ID(0x22, 1);
            break;

        default:
            regionId = NCP_REGION_ID(0x8, 0xa);
            break;
    }


    NCP_CALL(dump_config(dev, regionId, num_bls));
    NCP_CALL(dump_qrtr(dev, regionId, num_bls));
    NCP_CALL(dump_wl(dev, regionId, num_bls, num_ranks));
    NCP_CALL(dump_gt(dev, regionId, num_bls, num_ranks));
    NCP_CALL(dump_rl(dev, regionId, num_bls, num_ranks));
    NCP_CALL(dump_ratio(dev, regionId, num_bls, num_ranks));


    printf("\n");

NCP_RETURN_LABEL

    if (ncpStatus != NCP_ST_SUCCESS) 
    {
        ncp_status_print("ncp_sm_lsiphy_reg_dump", ncpStatus);
    }
    return ncpStatus;
}

#endif /* SM_REG_DUMP */




/*
 * read all of the phy error registers for display purposes
 *
 */
ncp_st_t
ncp_sm_lsiphy_status_get(
        ncp_dev_hdl_t dev,
        ncp_uint32_t  smId,
        ncp_sm_lsiphy_stat_t *stat)
{
    ncp_st_t        ncpStatus = NCP_ST_SUCCESS;
    ncp_region_id_t region;
    ncp_bool_t      isSysMem;
    ncp_uint32_t    n_byte_lanes;

    if (smId >= NCP_EXTMEM_NUM_NODES) {
        NCP_CALL(NCP_ST_SYSMEM_INVALID_ID);
    }

    if (smId < NCP_SYSMEM_NUM_NODES) 
    {
        region = NCP_REGION_ID(sm_nodes[smId], NCP_SYSMEM_TGT_PHY);
        isSysMem = TRUE;
        n_byte_lanes = NCP_SM_NUM_BYTE_LANES;
    }
    else 
    {
        region = NCP_REGION_ID(sm_nodes[smId], NCP_TREEMEM_TGT_PHY);
        isSysMem = FALSE;
        n_byte_lanes = NCP_CM_NUM_BYTE_LANES;
    }

    /* general PHY status */
    ncr_read32(region, NCP_PHY_CFG_SYSMEM_PHY_STAT, 
                        (ncp_uint32_t *) &stat->phyStat);


    /* gate-training status */
    ncr_read32(region, NCP_PHY_CFG_SYSMEM_PHY_GTTRAINSTAT0, 
                        (ncp_uint32_t *) &stat->gttrn.stat0);

    ncr_read32(region, NCP_PHY_CFG_SYSMEM_PHY_GTTRAINSTAT1, 
                        (ncp_uint32_t *) &stat->gttrn.stat1);


    /* read-leveling status */
    ncr_read32(region, NCP_PHY_CFG_SYSMEM_PHY_RDLVLSTATNEDGE, 
                        (ncp_uint32_t *) &stat->rdlvl.nedge);
    /* mask out errors on non-existant ECC */
    stat->rdlvl.nedge.dp4rdndqs1ovf = 0;

    ncr_read32(region, NCP_PHY_CFG_SYSMEM_PHY_RDLVLSTATPEDGE, 
                        (ncp_uint32_t *) &stat->rdlvl.pedge);
    /* mask out errors on non-existant ECC */
    stat->rdlvl.pedge.dp4rdpdqs1ovf = 0;

    ncr_read32(region, NCP_PHY_CFG_SYSMEM_PHY_RDDSKWSTAT, 
                        (ncp_uint32_t *) &stat->rdlvl.dskew);

    ncr_read32(region, NCP_PHY_CFG_SYSMEM_PHY_RDDSKWFATALSTAT, 
                        (ncp_uint32_t *) &stat->rdlvl.dskew_fatal);

    /* write-leveling status */
    ncr_read32(region, NCP_PHY_CFG_SYSMEM_PHY_WRLVLSMSTAT, 
                        (ncp_uint32_t *) &stat->wrlvl.stat);
    stat->wrlvl.stat.dp4wrdqs0ovf = 0;


NCP_RETURN_LABEL
    return ncpStatus;
}


#define NCP_SM_CHECK_STAT_STRUCT(_struct, _err) \
    do { \
        int _i; \
        ncp_uint32_t *_p = (ncp_uint32_t *)&_struct; \
        for (_i=0; _i<((sizeof(_struct))/(sizeof(ncp_uint32_t))) ; _i++) {\
            if (_p[_i] != 0) { \
                NCP_CALL(_err);  \
            }\
        }\
    } while (0);





/*
 * check each of the bits in the top-level PHY status register
 * and if set return the corresponding status. 
 */
ncp_st_t
ncp_sm_lsiphy_status_check(
        ncp_dev_hdl_t dev,
        ncp_uint32_t  smId,
        ncp_sm_parms_t *parms)
{
    ncp_st_t        ncpStatus = NCP_ST_SUCCESS;
    ncp_uint32_t    n_byte_lanes;
    ncp_uint32_t    eccBytelane;
    ncp_region_id_t region;
    ncp_sm_lsiphy_stat_t phyStat = {{0}};

    if (smId >= NCP_EXTMEM_NUM_NODES) {
        NCP_CALL(NCP_ST_SYSMEM_INVALID_ID);
    }

    if (smId < NCP_SYSMEM_NUM_NODES) 
    {
        region = NCP_REGION_ID(sm_nodes[smId], NCP_SYSMEM_TGT_PHY);
        n_byte_lanes = NCP_SM_NUM_BYTE_LANES;
        eccBytelane = 0x100;
    }
    else 
    {
        region = NCP_REGION_ID(sm_nodes[smId], NCP_TREEMEM_TGT_PHY);
        n_byte_lanes = NCP_CM_NUM_BYTE_LANES;
        eccBytelane = 0x002;
    }

    /* get the current PHY status */
    NCP_CALL(ncp_sm_lsiphy_status_get(dev, smId, &phyStat));

    /*
     * with the LSI PHY status registers if any bit is set it 
     * indicates an error
     */
    NCP_SM_CHECK_STAT_STRUCT(phyStat.gttrn, NCP_ST_SYSMEM_PHY_GT_TRN_ERR);
    NCP_SM_CHECK_STAT_STRUCT(phyStat.rdlvl, NCP_ST_SYSMEM_PHY_RD_LVL_ERR);
    NCP_SM_CHECK_STAT_STRUCT(phyStat.wrlvl, NCP_ST_SYSMEM_PHY_WR_LVL_ERR);


NCP_RETURN_LABEL
    return ncpStatus;
}

ncp_st_t
ncp_sm_lsiphy_static_init(
        ncp_dev_hdl_t   dev,
        ncp_uint32_t    smId,
        ncp_sm_parms_t *parms)
{

    ncp_st_t        ncpStatus = NCP_ST_SUCCESS;
    ncp_region_id_t region;
    ncp_bool_t      isSysMem;
    ncp_uint32_t    n_byte_lanes;
    ncp_uint32_t    reg;
    int             i;
    ncp_uint32_t    vtc_cnt;

    ncp_phy_CFG_SYSMEM_PHY_DPCONFIG2_BLx_r_t   dpconfig2  = {0};
    ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG1_r_t      phyconfig1 = {0};
    ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG2_r_t      phyconfig2 = {0};
    ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG3_BLx_r_t  phyconfig3 = {0};
    ncp_phy_CFG_SYSMEM_PHY_SMCTRL_r_t          smctrl     = {0};
    ncp_phy_CFG_SYSMEM_PHY_ADRx_ADRIOSET_1ST_r_t adrioset = {0};
    ncp_phy_CFG_SYSMEM_PHY_DPIOVREFSET_r_t     dpiovrefset = {0};
    ncp_phy_CFG_SYSMEM_PHY_ADRx_AD12_ADRIOLPRCTRL_r_t lpctrl = {0}; 
    ncp_uint32_t mask, value;

    if (smId >= NCP_EXTMEM_NUM_NODES) {
        NCP_CALL(NCP_ST_SYSMEM_INVALID_ID);
    }

    if (smId < NCP_SYSMEM_NUM_NODES) 
    {
        NCP_COMMENT("sysmem %d PHY static init", smId);
        region = NCP_REGION_ID(sm_nodes[smId], NCP_SYSMEM_TGT_PHY);
        n_byte_lanes = NCP_SM_NUM_BYTE_LANES;
        isSysMem = TRUE;
    }
#ifndef UBOOT 
    else 
    {
        NCP_COMMENT("treemem %d PHY static init", smId - NCP_SYSMEM_NUM_NODES);
        region = NCP_REGION_ID(sm_nodes[smId], NCP_TREEMEM_TGT_PHY);
        n_byte_lanes = NCP_CM_NUM_BYTE_LANES;
        isSysMem = FALSE;
    }
#endif


    /* initial PHY configuration */
    dpconfig2.clrgate = 1;
    dpconfig2.enardpath = 0;
    for (i = 0; i < n_byte_lanes; i++) 
    {
        ncr_write32(region, NCP_PHY_CFG_SYSMEM_PHY_DP_CONFIG2_BL(i), 
                        *(ncp_uint32_t *) &dpconfig2);
    }

    phyconfig1.rdranksw  = 0; /* TODO: Do these need to be set later on?? */
    phyconfig1.wrranksw  = 0;
    phyconfig1.wrlatrank = 5;
    ncr_write32(region, NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG1, 
                        *(ncp_uint32_t *) &phyconfig1);

    /* reset the PHY */
    phyconfig2.clrfifo         = 1;
    phyconfig2.fifoena         = 1;
    phyconfig2.dp8ena          = 1;
    phyconfig2.dp7ena          = 1;
    phyconfig2.dp6ena          = 1;
    phyconfig2.dp5ena          = 1;
    phyconfig2.dp4ena          = 1;
    phyconfig2.dp3ena          = 1;
    phyconfig2.dp2ena          = 1;
    phyconfig2.dp1ena          = 1;
    phyconfig2.dp0ena          = 1;
    phyconfig2.rstnio          = 1;
    phyconfig2.dfiwrlvlphymode = 1;
    phyconfig2.dfigttrainmode  = 1;
    phyconfig2.dfirdlvlphymode = 1;
    
    ncr_write32(region, NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG2, 
                        *(ncp_uint32_t *) &phyconfig2);



    phyconfig3.rdlatrank = parms->min_phy_cal_delay;
    phyconfig3.rdlatgate = parms->min_phy_cal_delay;
    for (i = 0; i < n_byte_lanes; i++) 
    {
        ncr_write32(region, NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG3_BL(i), 
                        *(ncp_uint32_t *) &phyconfig3);
    }

    /* 
     * disable non-existant bytelanes
     * Note that this assumes phyconfig2 has not been changed since
     * being initialized above.
     */
    phyconfig2.clrfifo         = 0;
    phyconfig2.dp8ena          = 0;
    phyconfig2.dp7ena          = 0;
    phyconfig2.dp6ena          = 0;
    phyconfig2.dp5ena          = 0;
    if (parms->enableECC == FALSE) {
        if (isSysMem) 
        {
            phyconfig2.dp4ena      = 0;
        } else {
            phyconfig2.dp1ena      = 0;
        }
    }

    ncr_write32(region, NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG2, 
                        *(ncp_uint32_t *) &phyconfig2);


    /* 
     * NOTE: For now this is ACP2500 specific!!
     */
    
    mask = value = 0;
    if (isSysMem) {
        /* enable internal VREF */
        lpctrl.enivref10 = 1;
        ncr_write32(region, NCP_PHY_CFG_SYSMEM_PHY_ADR0_AD12_ADRIOLPRCTRL, 
                        *(ncp_uint32_t *) &lpctrl);

        /* initialize VTC count */
        /* TODO : make this configuration parameter?? */
        /* FREQDEP: for now 7.8 us at 800MHz */
        vtc_cnt = 0x1860;

        SMAV(ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG0_r_t , fblpsel, 2 );
    }
    else {
        /* enable internal VREF */
        lpctrl.enivref6 = 1;
        ncr_write32(region, NCP_PHY_CFG_SYSMEM_PHY_ADR2_AD12_ADRIOLPRCTRL, 
                        *(ncp_uint32_t *) &lpctrl);

        /* initialize VTC count */
        /* TODO : make this configuration parameter?? */
        /* FREQDEP: for now 7.8 us at 667MHz */
        vtc_cnt = 0x1450;

        SMAV(ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG0_r_t , fbadrsel, 2 );
        SMAV(ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG0_r_t , fblpsel,  1 );
    }
    ncr_write32(region, NCP_PHY_CFG_SYSMEM_PHY_VTCCOUNT, vtc_cnt);

    ncr_modify32( region, NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG0, mask, value );


    /* init qrtr */
    smctrl.initqrtr     = 1;
    smctrl.initdfitrain = 1;
    smctrl.initfb       = 1;
    ncr_write32(region, NCP_PHY_CFG_SYSMEM_PHY_SMCTRL, 
                        *(ncp_uint32_t *) &smctrl);

    if (parms->single_bit_mpr) {
        reg =  parms->rdcal_cmp_even |  
                  (parms->rdcal_cmp_even << 8) |
                      (parms->rdcal_cmp_even << 16) |
                          (parms->rdcal_cmp_even << 24);

        ncr_write32(region, NCP_PHY_CFG_SYSMEM_PHY_RDLVLCMPDATEVN, reg);

        reg =  parms->rdcal_cmp_odd |  
                  (parms->rdcal_cmp_odd << 8) |
                      (parms->rdcal_cmp_odd << 16) |
                          (parms->rdcal_cmp_odd << 24);

        ncr_write32(region, NCP_PHY_CFG_SYSMEM_PHY_RDLVLCMPDATODD, reg);

    }

    adrioset.adrdrvac  = parms->phy_adr_imp;
    adrioset.adrdrvck0 = parms->phy_adr_imp;
    adrioset.adrdrvck1 = parms->phy_adr_imp;
    adrioset.adrslac   = parms->phy_adr_imp;
    adrioset.adrslck0  = parms->phy_adr_imp;
    adrioset.adrslck1  = parms->phy_adr_imp;

    ncr_write32(region, NCP_PHY_CFG_SYSMEM_PHY_ADR0_ADRIOSET_1ST, *(ncp_uint32_t *) &adrioset);
    ncr_write32(region, NCP_PHY_CFG_SYSMEM_PHY_ADR1_ADRIOSET, *(ncp_uint32_t *) &adrioset);
    ncr_write32(region, NCP_PHY_CFG_SYSMEM_PHY_ADR2_ADRIOSET, *(ncp_uint32_t *) &adrioset);

    dpiovrefset.drvdq  = parms->phy_dat_imp;
    dpiovrefset.drvdqs = parms->phy_dat_imp;
    dpiovrefset.drvdm  = parms->phy_dat_imp;
    dpiovrefset.odtimpdq  = parms->phy_rcv_imp;
    dpiovrefset.odtimpdqs = parms->phy_rcv_imp;
    dpiovrefset.odtimpdm  = parms->phy_rcv_imp;
    ncr_write32(region, NCP_PHY_CFG_SYSMEM_PHY_DPIOVREFSET, *(ncp_uint32_t *) &dpiovrefset);

    /* check the PHY status */
    ncpStatus = ncp_sm_lsiphy_status_check(dev, smId, parms);

NCP_RETURN_LABEL
    return ncpStatus;
}


#ifndef UBOOT
static ncp_st_t
ncp_sm_lsiphy_poll_for_op_done(
        ncp_dev_hdl_t dev,
        ncp_region_id_t region)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_denali_DENALI_CTL_13_t ctl_13 = {0};
    ncp_denali_DENALI_CTL_13_t ctl_13_mask = {0};

    ctl_13_mask.swlvl_op_done = ctl_13.swlvl_op_done = 1;
    NCP_CALL(ncp_poll(dev, region, NCP_DENALI_CTL_13,
                *(ncp_uint32_t *)&ctl_13_mask,
                *(ncp_uint32_t *)&ctl_13,
                NCP_SYSMEM_PHY_TRAIN_DELAY_USEC,
                NCP_SYSMEM_PHY_TRAIN_DELAY_LOOPS));


NCP_RETURN_LABEL
    return ncpStatus;
}

#endif

/*
 * The 'general purpose' sysmem PHY training init procedure. 
 * This is called by the higher level function to initiate
 * a training sequence and return when complete. Analysis
 * of what happened takes place at the higher level.
 */
static ncp_st_t
ncp_sm_sysmem_phy_training_run(
        ncp_dev_hdl_t               dev,
        ncp_uint32_t                smId,
        ncp_region_id_t             ctlRegion,
        ncp_region_id_t             phyRegion,
        ncp_uint32_t                rank,
        ncp_uint32_t                edge,
        ncp_sm_phy_training_mode_t  mode,
        ncp_sm_parms_t             *parms)
{

    ncp_st_t        ncpStatus = NCP_ST_SUCCESS;

    int i;
    ncp_uint32_t ctl_58; 
/*    ncp_uint32_t ctl_59; */
    ncp_uint32_t ctl_60;
    ncp_uint32_t mask, value;
    ncp_uint32_t            phyconfig2;
    ncp_uint32_t  dp_en;
    ncp_uint32_t  swlvl_complete;

    ncp_uint32_t trainLoops;
#ifndef UBOOT
    ncp_uint32_t busAdaptor;
#endif

    switch (mode) {
        case NCP_SYSMEM_PHY_GATE_TRAINING:
            NCP_COMMENT("Sysmem %d PHY gate training rank %d ", smId, rank);
            break;

        case NCP_SYSMEM_PHY_WRITE_LEVELING:
            NCP_COMMENT("Sysmem %d PHY write leveling rank %d", smId, rank);
            break;

        case NCP_SYSMEM_PHY_READ_LEVELING:
            NCP_COMMENT("Sysmem %d PHY read leveling rank %d %s edge", smId, rank, (edge == 0) ? "pos" : "neg");
            break;

        default:
            NCP_COMMENT("unexpected PHY training mode %d !", mode);
    }

#ifndef UBOOT
    /* get the driver bus adaptor */
    NCP_CALL(ncp_dev_read32(dev, NCP_REGION_DRIVER_CFG, 
                                 NCP_DEV_CFG_BUS_ADAPTOR, &busAdaptor));
#endif



    /*
     * Initialize the leveling response registers to zero.
     * TODO: It's not clear whether the h/w does this for us
     * or not, but since these registers are defined as read/write
     * we'll initialize them to zero just in case.
     */
    ncr_write32( ctlRegion, NCP_DENALI_CTL_58, 0 );
    ncr_write32( ctlRegion, NCP_DENALI_CTL_59, 0 );
    ncr_write32( ctlRegion, NCP_DENALI_CTL_60, 0 );

    /* initialize the local dp_enable field */

    ncr_read32(phyRegion, NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG2, &phyconfig2);
    dp_en = (phyconfig2 & 0x001ff000) >> 12;


    /* read-leveling chip_select */
    mask = value = 0;
    SMAV( ncp_denali_DENALI_CTL_20_t, rdlvl_cs, rank );
    ncr_modify32( ctlRegion, NCP_DENALI_CTL_20, mask, value );

    /* read-leveling edge */
    mask = value = 0;
    SMAV( ncp_denali_DENALI_CTL_07_t, rdlvl_edge, edge );
    ncr_modify32( ctlRegion, NCP_DENALI_CTL_07, mask, value );

    /* write-leveling chip_select and mode */
    mask = value = 0;
    SMAV( ncp_denali_DENALI_CTL_21_t, wrlvl_cs, rank );
    SMAV( ncp_denali_DENALI_CTL_21_t, sw_leveling_mode, mode );
    ncr_modify32( ctlRegion, NCP_DENALI_CTL_21, mask, value );

    /* set the start bit */
    mask = value = 0;
    SMAV( ncp_denali_DENALI_CTL_14_t, swlvl_start, 1);
    ncr_modify32( ctlRegion, NCP_DENALI_CTL_14, mask, value );


    /* poll for the OP_DONE bit */
    NCP_SM_POLL_FOR_OP_DONE(ctlRegion);


#define NCP_PHY_MAX_TRAIN_LOOPS 5000
    trainLoops = 0;
    while (trainLoops < NCP_PHY_MAX_TRAIN_LOOPS) {
        /* set the load bit */
        mask = value = 0;
        SMAV( ncp_denali_DENALI_CTL_13_t, swlvl_load, 1 );
        ncr_modify32( ctlRegion, NCP_DENALI_CTL_13, mask, value );

        /* poll for the OP_DONE bit */
        NCP_SM_POLL_FOR_OP_DONE(ctlRegion);

        /* 
         * read the leveling response registers
         * we'll check the values after completing the training operation
         */
        swlvl_complete = 0;
        ncr_read32(ctlRegion, NCP_DENALI_CTL_58, &ctl_58);
        for (i = 0; i < 4; i++) 
        {
            if (ctl_58 & 0xff) {
                swlvl_complete |= (1 << i);
            }
            ctl_58 >>= 8;
        }

#if 0
        ncr_read32(ctlRegion, NCP_DENALI_CTL_59, &ctl_59);
        for (i = 0; i < 4; i++) 
        {
            if (ctl_59 & 0xff) {
                swlvl_complete |= (0x10 << i);
            }
            ctl_59 >>= 8;
        }
#endif

        ncr_read32(ctlRegion, NCP_DENALI_CTL_60, &ctl_60);
        if (ctl_60)
        {
            swlvl_complete |= 0x10;
        }

        /*
         * Now compare the bitmask of completed bytelanes against those
         * that are enabled. If all enabled bytelanes are complete then
         * we're finished. 
         */
        if ((swlvl_complete & dp_en) == dp_en)
        {
            break; 
        }

#ifndef UBOOT
        if (busAdaptor == NCP_DEV_BUS_FBRS) 
        {
            NCP_COMMENT("### FBRS setting leveling response registers");
            NCP_CALL(ncp_dev_write32(dev, ctlRegion, NCP_DENALI_CTL_58, 0xffffffff));
            NCP_CALL(ncp_dev_write32(dev, ctlRegion, NCP_DENALI_CTL_59, 0xffffffff));
            NCP_CALL(ncp_dev_write32(dev, ctlRegion, NCP_DENALI_CTL_60, 0x000000ff));
        }
#endif


    	/* Clear any errors for the next iteration */
    	ncr_read32( ctlRegion, NCP_DENALI_CTL_260, & value );
        ncr_write32( ctlRegion, NCP_DENALI_CTL_89, value);

        trainLoops++;
    }

    if (trainLoops >= NCP_PHY_MAX_TRAIN_LOOPS) 
    {
        NCP_CALL(NCP_ST_SYSMEM_PHY_TRAIN_TIMEOUT);
    }

    /* set the exit bit */
    mask = value = 0;
    SMAV( ncp_denali_DENALI_CTL_13_t, swlvl_exit, 1);
    ncr_modify32( ctlRegion, NCP_DENALI_CTL_13, 0x100, 0x10100 );


    /* poll for the OP_DONE bit */
    NCP_SM_POLL_FOR_OP_DONE(ctlRegion);

#if 0
    /* disable firmware control of ODT */
    ctl_127 &= 0xe0ffffff; 
    NCP_CALL(ncp_write32(dev, ctlRegion, NCP_DENALI_CTL_127, ctl_127));
#endif

    /* check the PHY status */
    if (mode != NCP_SYSMEM_PHY_GATE_TRAINING)
    {
        ncpStatus = ncp_sm_lsiphy_status_check(dev, smId, parms);

    }

    if (mode == NCP_SYSMEM_PHY_READ_LEVELING)
    {
        /* re-enable all bytelanes and clear fifo */
        mask = value = 0;
        SMAV( ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG2_r_t, clrfifo, 1 );
        ncr_modify32( phyRegion, NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG2, mask, value );
        
        /* enable read path */
        mask = value = 0;
        SMAV( ncp_phy_CFG_SYSMEM_PHY_DPCONFIG2_BLx_r_t, enardpath, 1 );
        SMAV( ncp_phy_CFG_SYSMEM_PHY_DPCONFIG2_BLx_r_t, clrgate, 1 );
        for (i = 0; i < 5; i++) /* TEMP : hard-coded value */
        {
            ncr_modify32( phyRegion, NCP_PHY_CFG_SYSMEM_PHY_DP_CONFIG2_BL(i), mask, value );
        }

    }

    if (mode == NCP_SYSMEM_PHY_WRITE_LEVELING) 
    {
    	/* Check the interrupt status. */
    	ncr_read32( ctlRegion, NCP_DENALI_CTL_260, & value );
        ncr_write32( ctlRegion, NCP_DENALI_CTL_89, value);
        if (value & 0x00004000) {
            /* a write leveling error occurred */
            NCP_CALL(NCP_ST_SYSMEM_PHY_WR_LVL_ERR); 
        }
    }


NCP_RETURN_LABEL
    return ncpStatus;
}

#ifndef UBOOT 

/*
 * The 'general purpose' treemem PHY training init procedure. 
 * This is called by the higher level function to initiate
 * a training sequence and return when complete. Analysis
 * of what happened takes place at the higher level.
 */
static ncp_st_t
ncp_sm_treemem_phy_training_run(
        ncp_dev_hdl_t   dev,
        ncp_uint32_t    smId,
        ncp_region_id_t ctlRegion,
        ncp_region_id_t phyRegion,
        ncp_uint32_t    rank,
        ncp_uint32_t    edge,
        ncp_sm_phy_training_mode_t mode,
        ncp_sm_parms_t             *parms)
{

    ncp_st_t        ncpStatus = NCP_ST_SUCCESS;

    ncp_ddr_CFG_NTEMC_MRS_r_t mrs = {0};
    ncp_ddr_CFG_NTEMC_DDR_STATUS_r_t ddr_status = {0};

    NCP_RMW_REG(ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t,   ddr_ctrl);

    /* clear any previous operation */
    NCP_RMW_SET_FIELD(ddr_ctrl, rd_gate_lvl, 0);
    NCP_RMW_SET_FIELD(ddr_ctrl, wrt_lvl,     0);
    NCP_RMW_SET_FIELD(ddr_ctrl, rd_lvl,      0);
    NCP_RMW_SET_FIELD(ddr_ctrl, lvl_rsp,     1);
    NCP_RMW_SET_FIELD(ddr_ctrl, ref_ena,     0);
    NCP_RMW(dev, ctlRegion, NCP_DDR_CFG_NTEMC_DDR_CTRL, ddr_ctrl);

    switch (mode) {
        case NCP_SYSMEM_PHY_GATE_TRAINING:
            NCP_COMMENT("Treemem %d PHY gate training rank %d", 
                                smId - NCP_SYSMEM_NUM_NODES, rank);

            /* MRS MPR operation - enables training functionality in DRAM */
            mrs.mrs_adr  = 4;
            mrs.mrs_badr = 3;
            mrs.mrs_cmd  = 0;
            mrs.mrs_cke  = 1;
            NCP_CALL(ncp_write32(dev, ctlRegion, NCP_DDR_CFG_NTEMC_MRS, 
                                  *(ncp_uint32_t *) &mrs));

            /* issue MRS command */
            NCP_CALL(ncp_write32(dev, ctlRegion, NCP_DDR_CFG_NTEMC_ISSUE_MRS, 1));

            /* initiate gate training */
            NCP_RMW_SET_FIELD(ddr_ctrl, rd_gate_lvl, 1);
            NCP_RMW_SET_FIELD(ddr_ctrl, lvl_rsp,     0);
            NCP_RMW_SET_FIELD(ddr_ctrl, odt_mode,    3);
            NCP_RMW(dev, ctlRegion, NCP_DDR_CFG_NTEMC_DDR_CTRL, ddr_ctrl);

            /* poll for completion */
            ddr_status.rdgtlvldone = 1;
            NCP_CALL(ncp_poll(dev, ctlRegion, NCP_DDR_CFG_NTEMC_DDR_STATUS,
                                *(ncp_uint32_t *) &ddr_status,
                                *(ncp_uint32_t *) &ddr_status,
                                1, 100));

            /* 
             * check rdgtlvlstat to make sure training completed satisfactorily 
             * we use ncp_poll so that this will succeed on FBRS as well 
             */ 
            ddr_status.rdgtlvlstat = 1;
            NCP_CALL(ncp_poll(dev, ctlRegion, NCP_DDR_CFG_NTEMC_DDR_STATUS,
                                *(ncp_uint32_t *) &ddr_status,
                                *(ncp_uint32_t *) &ddr_status,
                                1, 2));


            /* MRS normal operation */
            mrs.mrs_adr  = 0;
            NCP_CALL(ncp_write32(dev, ctlRegion, NCP_DDR_CFG_NTEMC_MRS, 
                                  *(ncp_uint32_t *) &mrs));

            /* issue MRS command */
            NCP_CALL(ncp_write32(dev, ctlRegion, NCP_DDR_CFG_NTEMC_ISSUE_MRS, 1));


            break;

        case NCP_SYSMEM_PHY_WRITE_LEVELING:
            NCP_COMMENT("Treemem %d PHY write leveling rank %d", 
                            smId - NCP_SYSMEM_NUM_NODES, rank);

            /* MRS operation */
            mrs.mrs_adr  = 0xcb;
            mrs.mrs_badr = 1;
            mrs.mrs_cmd  = 0;
            mrs.mrs_cke  = 1;
            NCP_CALL(ncp_write32(dev, ctlRegion, NCP_DDR_CFG_NTEMC_MRS, 
                                  *(ncp_uint32_t *) &mrs));

            /* issue MRS command */
            NCP_CALL(ncp_write32(dev, ctlRegion, NCP_DDR_CFG_NTEMC_ISSUE_MRS, 1));

            /* initiate write leveling */
            NCP_RMW_SET_FIELD(ddr_ctrl, wrt_lvl,     1);
            NCP_RMW_SET_FIELD(ddr_ctrl, lvl_rsp,     0);
            NCP_RMW_SET_FIELD(ddr_ctrl, odt_mode,    1);
            NCP_RMW(dev, ctlRegion, NCP_DDR_CFG_NTEMC_DDR_CTRL, ddr_ctrl);


            /* poll for completion */
            ddr_status.wrlvldone = 1;
            NCP_CALL(ncp_poll(dev, ctlRegion, NCP_DDR_CFG_NTEMC_DDR_STATUS,
                                *(ncp_uint32_t *) &ddr_status,
                                *(ncp_uint32_t *) &ddr_status,
                                1, 100));

            /* 
             * check rdgtlvlstat to make sure training completed satisfactorily 
             * we use ncp_poll so that this will succeed on FBRS as well 
             */ 
            ddr_status.wrlvlstat = 1;
            NCP_CALL(ncp_poll(dev, ctlRegion, NCP_DDR_CFG_NTEMC_DDR_STATUS,
                                *(ncp_uint32_t *) &ddr_status,
                                *(ncp_uint32_t *) &ddr_status,
                                1, 2));

            /* disable write leveling */
            mrs.mrs_adr  = 0x4b;
            NCP_CALL(ncp_write32(dev, ctlRegion, NCP_DDR_CFG_NTEMC_MRS, 
                                  *(ncp_uint32_t *) &mrs));

            /* issue MRS command */
            NCP_CALL(ncp_write32(dev, ctlRegion, NCP_DDR_CFG_NTEMC_ISSUE_MRS, 1));



            break;


        case NCP_SYSMEM_PHY_READ_LEVELING:
            NCP_COMMENT("Treemem %d PHY read leveling rank %d %s edge", 
                            smId - NCP_SYSMEM_NUM_NODES, rank,
                            (edge == 0) ? "pos" : "neg" );

            /* MRS operation */
            mrs.mrs_adr  = 4;
            mrs.mrs_badr = 3;
            mrs.mrs_cmd  = 0;
            mrs.mrs_cke  = 1;
            NCP_CALL(ncp_write32(dev, ctlRegion, NCP_DDR_CFG_NTEMC_MRS, 
                                  *(ncp_uint32_t *) &mrs));

            /* issue MRS command */
            NCP_CALL(ncp_write32(dev, ctlRegion, NCP_DDR_CFG_NTEMC_ISSUE_MRS, 1));

            /* initiate read leveling */
            NCP_RMW_SET_FIELD(ddr_ctrl, rd_lvl,      1);
            NCP_RMW_SET_FIELD(ddr_ctrl, lvl_edge,    edge);
            NCP_RMW_SET_FIELD(ddr_ctrl, lvl_rsp,     0);
            NCP_RMW_SET_FIELD(ddr_ctrl, odt_mode,    3);
            NCP_RMW(dev, ctlRegion, NCP_DDR_CFG_NTEMC_DDR_CTRL, ddr_ctrl);


            /* poll for completion */
            ddr_status.rdlvldone = 1;
            NCP_CALL(ncp_poll(dev, ctlRegion, NCP_DDR_CFG_NTEMC_DDR_STATUS,
                                *(ncp_uint32_t *) &ddr_status,
                                *(ncp_uint32_t *) &ddr_status,
                                1, 100));

            /* 
             * check rdgtlvlstat to make sure training completed satisfactorily 
             * we use ncp_poll so that this will succeed on FBRS as well 
             */ 
            ddr_status.rdlvlstat = 1;
            NCP_CALL(ncp_poll(dev, ctlRegion, NCP_DDR_CFG_NTEMC_DDR_STATUS,
                                *(ncp_uint32_t *) &ddr_status,
                                *(ncp_uint32_t *) &ddr_status,
                                1, 2));

            /* disable write leveling */
            mrs.mrs_adr  = 0x4b;
            NCP_CALL(ncp_write32(dev, ctlRegion, NCP_DDR_CFG_NTEMC_MRS, 
                                  *(ncp_uint32_t *) &mrs));

            /* issue MRS command */
            NCP_CALL(ncp_write32(dev, ctlRegion, NCP_DDR_CFG_NTEMC_ISSUE_MRS, 1));



            break;


        default:
            NCP_COMMENT("unexpected PHY training mode!!!");
    }

    if (mode != NCP_SYSMEM_PHY_GATE_TRAINING)
    {
        /* check the PHY status */
        ncpStatus = ncp_sm_lsiphy_status_check(dev, smId, parms);
    }



NCP_RETURN_LABEL
    return ncpStatus;
}
#endif /* not UBOOT */

/* 
 * the common PHY training function. 
 * just figure out whether we're training the sysmem or the
 * treemem and call the appropriate function.
 */
ncp_st_t
ncp_sm_lsiphy_training_run(
        ncp_dev_hdl_t               dev,
        ncp_uint32_t                smId,
        ncp_uint32_t                rank,
        ncp_uint32_t                edge,
        ncp_sm_phy_training_mode_t  mode,
        ncp_sm_parms_t             *parms)
{

    ncp_st_t                ncpStatus = NCP_ST_SUCCESS;
    ncp_region_id_t         ctlRegion = 0;
    ncp_region_id_t         phyRegion = 0;
    phy_training_run_fn_t   trnFn = NULL;

    switch (smId) {
        case 0:
        case 1:
            ctlRegion = NCP_REGION_ID(sm_nodes[smId], NCP_SYSMEM_TGT_DENALI);
            phyRegion = NCP_REGION_ID(sm_nodes[smId], NCP_SYSMEM_TGT_PHY);
            trnFn = ncp_sm_sysmem_phy_training_run;
            break;

#ifndef UBOOT
        case 2:
        case 3:
            ctlRegion = NCP_REGION_ID(sm_nodes[smId], NCP_TREEMEM_TGT_DDR);
            phyRegion = NCP_REGION_ID(sm_nodes[smId], NCP_TREEMEM_TGT_PHY);
            trnFn = ncp_sm_treemem_phy_training_run;
            break;
#endif

        default:
            NCP_CALL(NCP_ST_SYSMEM_INVALID_ID);
    }

    NCP_CALL(trnFn(dev, smId, ctlRegion, phyRegion, rank, edge, mode, parms));


NCP_RETURN_LABEL
    return ncpStatus;
}

/* 
 * the gate training function for the LSI PHY.
 * this requires iterative calls to the common 
 * PHY training function.
 */
ncp_st_t
ncp_sm_lsiphy_gate_training(
        ncp_dev_hdl_t               dev,
        ncp_uint32_t                smId,
        ncp_uint32_t                rank,
        ncp_sm_parms_t             *parms)
{

    ncp_st_t                ncpStatus = NCP_ST_SUCCESS;
    ncp_region_id_t         ctlRegion;
    ncp_region_id_t         phyRegion;
    phy_training_run_fn_t   trnFn = NULL;
    ncp_uint32_t            phyconfig2;
    ncp_uint32_t            mask, value;
    ncp_uint16_t            dp_en;
    ncp_uint64_t            gt_stat;
    ncp_uint32_t            bl_stat;
    ncp_uint32_t            num_bls;
    int                     i;
    ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG3_BLx_r_t  *phyconfig3 = (ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG3_BLx_r_t *) &value;

    switch (smId) {
        case 0:
        case 1:
            ctlRegion = NCP_REGION_ID(sm_nodes[smId], NCP_SYSMEM_TGT_DENALI);
            phyRegion = NCP_REGION_ID(sm_nodes[smId], NCP_SYSMEM_TGT_PHY);
            num_bls = 5;
            trnFn = ncp_sm_sysmem_phy_training_run;
            break;

#ifndef UBOOT
        case 2:
        case 3:
            ctlRegion = NCP_REGION_ID(sm_nodes[smId], NCP_TREEMEM_TGT_DDR);
            phyRegion = NCP_REGION_ID(sm_nodes[smId], NCP_TREEMEM_TGT_PHY);
            num_bls = 2;
            trnFn = ncp_sm_treemem_phy_training_run;
            break;
#endif

        default:
            NCP_CALL(NCP_ST_SYSMEM_INVALID_ID);
    }

    /* disable read path */
    mask = value = 0;
    SMAV( ncp_phy_CFG_SYSMEM_PHY_DPCONFIG2_BLx_r_t, enardpath, 0 );
    for (i = 0; i < num_bls; i++) 
    {
        ncr_modify32( phyRegion, NCP_PHY_CFG_SYSMEM_PHY_DP_CONFIG2_BL(i), mask, value );
    }

    /* for gate training, the LSI PHY does not automatically
     * traverse a range of gate delay values. So we must loop
     * and increment the gate delay values ourselves. we start
     * with a (user-specified?) minimum value for rlgate and
     * attempt gate training on all active bytelanes. We disable
     * any bytelane that passes to exempt it from further training,
     * increment rlgate, and try again. When all bytelanes are
     * trained we're done, or if we get to the max values and 
     * some are still untrained we fail.
     */

    /* first initialize the local dp_enable field */

    ncr_read32(phyRegion, NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG2, &phyconfig2);
    dp_en = (phyconfig2 & 0x001ff000) >> 12;

    while (dp_en) 
    {
        /* run the training */
        NCP_CALL(trnFn(dev, smId, ctlRegion, phyRegion, 
                    rank, 0, NCP_SYSMEM_PHY_GATE_TRAINING, parms));

        /* test for success, disable any good bytelanes */
        /* first read gttrn stat for all bytelanes */

        ncr_read32(phyRegion, NCP_PHY_CFG_SYSMEM_PHY_GTTRAINSTAT1, &value);
        gt_stat = (ncp_uint64_t) value << 32;

        ncr_read32(phyRegion, NCP_PHY_CFG_SYSMEM_PHY_GTTRAINSTAT0, &value);
        gt_stat |= value;

        for (i = 0; i < num_bls; i++)
        {
            bl_stat = (ncp_uint32_t) gt_stat & 0xf;
            if (bl_stat == 0) 
            {
                /* This bytelane passed! disable it */
                dp_en &= ~(1 << i);
            }
            else 
            {
                /* this bytelane failed! try incrememnting rlgate */

                ncr_read32(phyRegion, 
                        NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG3_BL(i), &value);

                phyconfig3->rdlatrank += 1;
                phyconfig3->rdlatgate += 1;
                if (phyconfig3->rdlatgate >= 32)
                {
                    NCP_CALL(NCP_ST_ERROR); /* TODO */
                }

                ncr_write32(phyRegion, 
                        NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG3_BL(i), value);
            }

            gt_stat >>= 4;
        }

        /* disable successful bytelanes */
        value = (phyconfig2 & 0xffe00fff) | (dp_en << 12);
        ncr_write32(phyRegion, NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG2, value);
    }


NCP_RETURN_LABEL
    if (ncpStatus == NCP_ST_SUCCESS)
    {
        /* re-enable all bytelanes and clear fifo */
        mask = value = phyconfig2;
        SMAV( ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG2_r_t, clrfifo, 1 );
        ncr_modify32( phyRegion, NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG2, mask, value );
        
        /* enable read path */
        mask = value = 0;
        SMAV( ncp_phy_CFG_SYSMEM_PHY_DPCONFIG2_BLx_r_t, enardpath, 1 );
        SMAV( ncp_phy_CFG_SYSMEM_PHY_DPCONFIG2_BLx_r_t, clrgate, 1 );
        for (i = 0; i < num_bls; i++) 
        {
            ncr_modify32( phyRegion, NCP_PHY_CFG_SYSMEM_PHY_DP_CONFIG2_BL(i), mask, value );
        }
    }


    return ncpStatus;
}

/* #define SM_BYTELANE_TEST_DEBUG */

/*
 *------------------------------------------------------------------------------
 *  sm_bytelane_test
 *
 *    pattern is now defined thusly:
 *
 *    bit 0 : 0 - walking one pattern
 *            1 - walking zero pattern
 *    bit 1 : 0 - read back data block
 *            1 - write data block without reading
 *    bit 2 : 0 - perform bytelane alignment checking
 *            1 - check entire buffer
 */

static int
sm_bytelane_test(ncp_dev_hdl_t dev, unsigned long address, int pattern, 
        ncp_uint32_t *bad_bl_bad, ncp_uint32_t *bad_bl_early, ncp_uint32_t *bad_bl_late, 
		 unsigned long num_bls)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
	int i;
	int j;
	ncp_uint32_t  value32 = 0x01010101UL;
    ncp_uint8_t   compare_value;
	ncp_uint32_t  offset = num_bls * 2;
    ncp_uint32_t  *pTmp;
#ifdef UBOOT
	ncp_uint32_t  *p32 = (unsigned long *)(NCA + 0x1000);
	ncp_uint8_t   *p8 = (unsigned char *)(NCA + 0x1060);
#else
    ncp_uint8_t   wbuf[NCP_SM_BURST_SIZE];
    ncp_uint8_t   rbuf[NCP_SM_BURST_SIZE];
    ncp_uint32_t  *p32 = (ncp_uint32_t *) wbuf;
    ncp_uint8_t   *p8 = &rbuf[0x60];
#endif


	/* Build buffer */
    pTmp = p32;
	for (i = 0; i < (128 / num_bls); ++i) {
		unsigned long temp;

		if (0 == pattern)
			temp = value32;
		else
			temp = ~value32;

		*pTmp++ = temp;

		NCR_TRACE("ncpWrite  -w8 0.512.1.0x00%08lx " \
			  "0x%02x 0x%02x 0x%02x 0x%02x\n",
			  (address + (num_bls * i)),
			  (unsigned char )((temp & 0xff000000) >> 24),
			  (unsigned char )((temp & 0x00ff0000) >> 16),
			  (unsigned char )((temp & 0x0000ff00) >>  8),
			  (unsigned char )(temp & 0x000000ff));

		if (num_bls == 8) {
			*pTmp++ = temp;
			NCR_TRACE("ncpWrite  -w8 0.512.1.0x00%08lx " \
				  "0x%02x 0x%02x 0x%02x 0x%02x\n",
				  (address + 4 + (8 * i)),
				  (unsigned char )((temp & 0xff000000) >> 24),
				  (unsigned char )((temp & 0x00ff0000) >> 16),
				  (unsigned char )((temp & 0x0000ff00) >>  8),
				  (unsigned char )(temp & 0x000000ff));
		}

		if (0x80808080UL > value32)
			value32 = value32 << 1;
		else
			value32 = 0x01010101UL;

	}

#ifdef SM_BYTELANE_TEST_DEBUG
	{
		int index;

        pTmp = p32;
		for (index = 0; index < (128 / 4); ++index) {
			printf("<%03d:0x%08x>", (index * 4), *pTmp++);
		}

		printf("\n");
	}
#endif

    /* write it out and save the comparison value from the write buffer*/
#ifdef UBOOT
	ncr_write( NCP_REGION_ID( 512, 1 ), address, 128 );
    compare_value = *p8;
#else 

    NCP_CALL(ncp_block_write8(dev, NCP_REGION_NCA_NIC_SYSMEM, address, 
                                wbuf, NCP_SM_BURST_SIZE, 0));

    compare_value = wbuf[0x60];
#endif

	if (0 != (pattern & 0x2))
		return 0;

	/* Read back and compare. */
#ifdef UBOOT
	ncr_read( NCP_REGION_ID( 512, 1 ), address, 128 );
	NCR_TRACE("ncpRead   -w8 0.512.1.0x00%08lx 128\n", address);
    pTmp = p32;
#else 
    NCP_CALL(ncp_block_read8(dev, NCP_REGION_NCA_NIC_SYSMEM, address, 
                                rbuf, NCP_SM_BURST_SIZE, 0));
    
    pTmp = (ncp_uint32_t *) rbuf;
#endif

#ifdef SM_BYTELANE_TEST_DEBUG
	{
		for (i = 0; i < (128 / 4); ++i) {
			printf("(%03d:0x%08x)", (i * 4), *pTmp++);
		}
		printf("\n");
	}
#endif


	*bad_bl_bad = 0;
	*bad_bl_early = 0;
	*bad_bl_late = 0;
	j = 0;

    if (0 == (pattern & 0x4)) 
    {
    	for (i = 0; i < num_bls; ++i) {

#ifdef SM_BYTELANE_TEST_DEBUG
		printf("i=%d j=%d expect=0x%02x "
		       "p8=0x%08x/0x%02x/0x%02x/0x%02x\n",
		       i, j, compare_value, p8, *p8, *(p8 - offset),
		       *(p8 + offset));
#endif

    		if (compare_value != *p8) {
    			if (*(p8 - offset) == compare_value)
    				*bad_bl_early |= 1 << i;
    			else if (*(p8 + offset) == compare_value)
    				*bad_bl_late |= 1 << i;
    			else
    				*bad_bl_bad |= 1 << i;
    		}
    
    		++p8;
    		++j;
    	}
    } else {
        /* TODO!! implement full buffer compare for uboot */
#ifndef UBOOT
        if (memcmp(rbuf, wbuf, NCP_SM_BURST_SIZE)) {
            *bad_bl_bad = 0x1ff;
    	}
#else
	value32 = 0x01010101UL;
	pTmp = p32;

	for (i = 0; i < (128 / num_bls); ++i) {
	  unsigned long temp;

	  if (0 == pattern)
	    temp = value32;
	  else
	    temp = ~value32;

	  if (*p32 != temp) {
	    printf("\nCompare Failed! i=%d temp=0x%x *p32=0x%x",
		   i, temp, *p32);
	    *bad_bl_bad = 0x1ff;
	  }

	  ++p32;

	  if (8 == num_bls) {
	    if (*p32 != temp) {
	      printf("\nCompare 2 Failed! i=%d temp=0x%x *p32=0x%x",
		     i, temp, *p32);
	      *bad_bl_bad = 0x1ff;
	    }

	    ++p32;
	  }

	  if (0x80808080UL > value32)
	    value32 = value32 << 1;
	  else
	    value32 = 0x01010101UL;
	}
#endif
    }

#ifdef SM_BYTELANE_TEST_DEBUG
	printf("*bad_bl_bad=0x%x *bad_bl_early=0x%x *bad_bl_late=0x%x\n",
	       *bad_bl_bad, *bad_bl_early, *bad_bl_late);
#endif

NCP_RETURN_LABEL
	return 0;
}

/*
  ------------------------------------------------------------------------------
  sm_ecc_bytelane_test
*/
/* #define SM_ECC_BYTELANE_TEST_DEBUG */

static int
sm_ecc_bytelane_test(ncp_dev_hdl_t dev, unsigned long region, unsigned long address,
		     unsigned long node, int pattern, unsigned long ecc_mask,
		     ncp_uint32_t *bad_bl)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
	ncp_uint32_t value;
	ncp_uint32_t temp;
#ifdef UBOOT 
    ncp_uint32_t  *p32 = (NCA + 0x1000); 
#else 
    ncp_uint8_t   wbuf[NCP_SM_BURST_SIZE];
    ncp_uint8_t   rbuf[NCP_SM_BURST_SIZE];
    ncp_uint32_t  *p32 = (ncp_uint32_t *) wbuf;
#endif

	int i;
	int rc;

	/* clear ECC interrupt status bits */
	ncr_read32( region, NCP_DENALI_CTL_91, & value );
#ifdef SM_ECC_BYTELANE_TEST_DEBUG
	printf( "region=0x%08lx value=0x%08lx\n", region, value );
#endif /* SM_ECC_BYTELANE_TEST_DEBUG */
	value &= ecc_mask;
	ncr_write32( region, NCP_DENALI_CTL_89, value );

		
	/* Build buffer */
	value = 0x01010101;

	for (i = 0; i < 128 ; i += 8) {
		unsigned long this_value;

		if (0 == pattern)
			this_value = value;
		else
			this_value = ~value;

		*p32++ = this_value;
		*p32++ = this_value;
		NCR_TRACE("ncpWrite  -w8 0.512.1.0x00%08lx " \
			  "0x%02x 0x%02x 0x%02x 0x%02x\n",
			  (address + i),
			  (unsigned char )((this_value & 0xff000000) >> 24),
			  (unsigned char )((this_value & 0x00ff0000) >> 16),
			  (unsigned char )((this_value & 0x0000ff00) >>  8),
			  (unsigned char )(this_value & 0x000000ff));
		NCR_TRACE("ncpWrite  -w8 0.512.1.0x00%08lx " \
			  "0x%02x 0x%02x 0x%02x 0x%02x\n",
			  (address + 4 + i),
			  (unsigned char )((this_value & 0xff000000) >> 24),
			  (unsigned char )((this_value & 0x00ff0000) >> 16),
			  (unsigned char )((this_value & 0x0000ff00) >>  8),
			  (unsigned char )(this_value & 0x000000ff));

		if (value < 0x80808080)
			value <<= 1;
		else
			value = 0x01010101;
	}

    /* write it out */
#ifdef UBOOT 
#ifdef SM_ECC_BYTELANE_TEST_DEBUG
	{
		int index;

		for (index = 0; index < (128 / 4); ++index) {
			printf("<%03d:0x%08lx>", (index * 4),
			       *((unsigned long *)(NCA + 0x1000 + (index * 4))));
		}

		printf("\n");
	}
#endif /* SM_ECC_BYTELANE_TEST_DEBUG */

	ncr_write( NCP_REGION_ID( 512, 1 ), address, 128 );


#else 
    NCP_CALL(ncp_block_write8(dev, NCP_REGION_NCA_NIC_SYSMEM, address, 
                                wbuf, NCP_SM_BURST_SIZE, 0));
#endif
	/*
	  ncr_read() returns the contents of "CFG Ring Command Error
	  Status Register 0" after the operation.

	  The top 6 bits are all that matter; but the layout changed
	  as of X1V2.  See the definition of 0x101.0.0xe4 for details.

	  In X1V1, the RTE returns NCP_ST_DEV_PIO_DECODE_ERR when the
	  "decode_error" bit is set.

	  In X1V2 and later, the RTE returns NCP_ST_DEV_PIO_DECODE_ERR
	  when both the "target_error" and
	  "decode_err_or_node_err_type_bit0" bits are set.

	  In the following, both NCP_ST_SUCCESS, and
	  NCP_ST_DEV_PIO_DECODE_ERR should be acceptable; any other
	  return code is an error.
	*/

#ifdef UBOOT
#define NCR_ERROR_BIT_MASK 0xfc000000
#define NCP_ST_DEV_PIO_DECODE_ERR 0x84000000
#else
#define NCR_ERROR_BIT_MASK 0xffffffff

#endif

	/* 
     * Read back through the syscache backdoor.
     * This may fail if the ECC bytelane is out of level
     */
#ifdef UBOOT
	rc = ncr_read( NCP_REGION_ID( node, 5 ), (address >> 2), 128/4 );
	NCR_TRACE( "ncpRead    0.%lu.5.0x%010x 32\n", node, (address >> 2) );
#ifdef SM_ECC_BYTELANE_TEST_DEBUG
	{
		int index;

		for (index = 0; index < (128 / 4); ++index) {
			printf("(%03d:0x%08lx)", (index * 4),
			       *((unsigned long *)(NCA + 0x1000 + (index * 4))));
		}

		printf("\n");
	}
#endif /* SM_ECC_BYTELANE_TEST_DEBUG */
#else
    rc = ncp_block_read32(dev, NCP_REGION_ID(node, 5), (address >> 2), 
                                (ncp_uint32_t *)rbuf, NCP_SM_BURST_SIZE/4, 0);
#endif

#if 1
	if ((0 != rc) &&
	    (NCP_ST_DEV_PIO_DECODE_ERR != (rc & NCR_ERROR_BIT_MASK))) {
		printf("%s:%s:%d - rc=0x%x\n",
		       __FILE__, __FUNCTION__, __LINE__, rc);
		return rc;
	}
#else
    if (0 != rc) {
        *bad_bl = 0x1ff;
    }
#endif
    else {

    	/*
    	  If the interrupt status below is 0, the data just read back
    	  should be compared to what was written.  Since there isn't a
    	  place to store it, compare it now (since the following
    	  config ring accesses will overwrite the first few words).
    	 */
#ifdef UBOOT
		value = 0x01010101;
		rc = 0;

		for (i = 0; i < 128 ; i += 8) {
			unsigned long this_value;

			if (0 == pattern)
				this_value = value;
			else
				this_value = ~value;

			temp = *((unsigned long *)(NCA + 0x1000 + i));

			if (temp != this_value) {
				rc = 0x1ff;
			}

			temp = *((unsigned long *)(NCA + 0x1004 + i));

			if (temp != this_value) {
				rc = 0x1ff;
			}

			if (value < 0x80808080)
				value <<= 1;
			else
				value = 0x01010101;
		}
#else
    	/* Read back and compare. */
        if (memcmp(rbuf, wbuf, NCP_SM_BURST_SIZE)) 
        {
#if 0
            int i;
            ncp_uint32_t *pr = (ncp_uint32_t *) rbuf;
            ncp_uint32_t *pw = (ncp_uint32_t *) wbuf;
            printf("memcmp failed!\n");

            for ( i = 0; i < NCP_SM_BURST_SIZE/4; i++) {
                printf (" %08x : %08x\n", *pw++, *pr++);
            }
#endif
            *bad_bl = 0x1ff;
    	}
#endif
    }

	/* Clear any ACK errors created during initialization. */
	ncr_read32( NCP_REGION_ID( node, 0 ), 0, &temp);
	ncr_write32( NCP_REGION_ID( node, 0 ), 0, temp);

	/* Check the interrupt status. */
	ncr_read32( region, NCP_DENALI_CTL_260, & value );
    ncr_write32( region, NCP_DENALI_CTL_89, value);
#ifdef SM_ECC_BYTELANE_TEST_DEBUG
	printf("NCP_DENALI_CTL_91: 0x%lx\n", value);
#endif /* SM_ECC_BYTELANE_TEST_DEBUG */
	value &= ecc_mask;

	if (0 != value) {
		*bad_bl = 0x100;
	} else if (0 != rc) {
		*bad_bl = 0x1ff;
	}

NCP_RETURN_LABEL
	return 0;
}


ncp_st_t
ncp_sm_sm_coarse_write_leveling(
        ncp_dev_hdl_t   dev,
        ncp_uint32_t    smId,
        ncp_uint32_t    rank,
        ncp_uint64_t    addr,
        ncp_sm_parms_t *parms)
{

    ncp_st_t        ncpStatus = NCP_ST_SUCCESS;
    ncp_region_id_t region = NCP_REGION_ID(sm_nodes[smId], NCP_SYSMEM_TGT_PHY);
    ncp_region_id_t ctlRegion = NCP_REGION_ID(sm_nodes[smId], NCP_SYSMEM_TGT_DENALI);

    ncp_uint32_t    mask, value;

    ncp_uint32_t    bad_bl[3] = {0};

    ncp_uint8_t    sc_node;
    ncp_uint32_t    ecc_mask;

    ncp_uint8_t    bl;
    ncp_uint32_t    udly; 
    ncp_uint32_t    ldly; 
    ncp_uint8_t    nincs = 0;
    ncp_uint8_t    ndecs;
    int     adj;

 
    ncp_uint32_t    num_bls = 4;


    switch (smId) {
        case 0:
        case 1:
            break;
#ifndef UBOOT
        case 2:
        case 3:
            NCP_RETURN(NCP_ST_SUCCESS);
            break;
#endif
        default:
            NCP_CALL(NCP_ST_SYSMEM_INVALID_ID);
            break;
    }

    NCP_COMMENT("sysmem phy coarse write leveling");

    /* enable runtime */
    mask = value = 0;
    SMAV(ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG1_r_t, bblclobber, 1); 
    SMAV(ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG1_r_t, wrranksw, 1); 
    SMAV(ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG1_r_t, rdranksw, 1); 
    ncr_modify32(region, NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG1, mask, value);

    mask = value = 0;
    SMAV( ncp_denali_DENALI_CTL_334_t, ctrlupd_req_per_aref_en, 1 );
    ncr_modify32( ctlRegion, NCP_DENALI_CTL_334, mask, value );


    /*
     * The basic algorithm for coarse write leveling is:
     *  - we generate a block of data with a walking one pattern
     *    in each byte-lane, and a second block of data with a 
     *    walking zero. Each byte of each eight-byte beat then 
     *    indicates the beat from which it was written.
     *  - write two bursts of the eight beat pattern
     *  - read back starting at the address of the second burst
     *    and compare the value of each byte lane. If a byte lane
     *    has incorrect data we can tell by the value whether the
     *    write alignment is too early or too late.
     *  - Set the WLDQSxGRP register to indicate which byte-lanes
     *    need to be advanced by one clock
     *  - set DFICNTLWLCNTL with the rank to adjust and the dly_delta
     *    set to one to increment the delay. Writing this register 
     *    will perform the adjustment.
     *  - repeat the above two steps for byte-lanes that need to be
     *    retarded by one clock
     *  - repeat the write/read/compare test using the walking zero
     *    pattern. If there are no errors then write-leveling has 
     *    succeeded.
     */

    /* first just run the bytelane test to initialize memory */
    NCP_CALL(sm_bytelane_test(dev, addr, 3, 
                &bad_bl[0], &bad_bl[1], &bad_bl[2], num_bls));

    /* run the bytelane test using the walking one pattern */
    NCP_CALL(sm_bytelane_test(dev, addr, 0, 
                &bad_bl[0], &bad_bl[1], &bad_bl[2], num_bls));

    if (bad_bl[0] != 0) 
    {
        /* if any bytelane failed for some reason that does not 
         * appear to be write cycle alignment then it may be that
         * the memory is in some funky state. We try another write
         * to clear the state and rerun the test.
         */
        NCP_CALL(sm_bytelane_test(dev, addr, 1, 
                &bad_bl[0], &bad_bl[1], &bad_bl[2], num_bls));

        NCP_CALL(sm_bytelane_test(dev, addr, 0, 
                &bad_bl[0], &bad_bl[1], &bad_bl[2], num_bls));

        if (bad_bl[0] != 0) {
#ifdef SM_REG_DUMP
	    ncp_sm_lsiphy_reg_dump(dev, smId);
#endif
            /* if it's still bad then we bail out */
            NCP_CALL(NCP_ST_SYSMEM_PHY_WL_ERR);
        }
    }

    /*
     * advance or retard clocks for each failing bytelane
     */
    for (bl = 0; bl < num_bls; bl++)
    {
        if (bad_bl[1] & (1 << bl))
        {
            /* advance forward one clock */
            ncr_read32(region, 
                       NCP_PHY_CFG_SYSMEM_PHY_WRTLVLUPP_BL_CS(bl, rank),
                       &udly);
            ncr_write32(region, 
                       NCP_PHY_CFG_SYSMEM_PHY_WRTLVLUPP_BL_CS(bl, rank),
                       udly + 4);

            ncr_read32(region, 
                       NCP_PHY_CFG_SYSMEM_PHY_WRTLVLLOW_BL_CS(bl, rank),
                       &ldly);
            ncr_write32(region, 
                       NCP_PHY_CFG_SYSMEM_PHY_WRTLVLLOW_BL_CS(bl, rank),
                       ldly + 4);


        }

        if (bad_bl[2] & (1 << bl))
        {
            /* retard one clock 
             * if we don't have enough delay to go back
             * one full clock return an error
             */
            ncr_read32(region, 
                       NCP_PHY_CFG_SYSMEM_PHY_WRTLVLUPP_BL_CS(bl, rank),
                       &udly);
            if (udly < 4) 
            {
                NCP_CALL(NCP_ST_SYSMEM_PHY_WL_DLY_ERR);
            }
            ncr_write32(region, 
                       NCP_PHY_CFG_SYSMEM_PHY_WRTLVLUPP_BL_CS(bl, rank),
                       udly - 4);

            ncr_read32(region, 
                       NCP_PHY_CFG_SYSMEM_PHY_WRTLVLLOW_BL_CS(bl, rank),
                       &ldly);
            if (ldly < 4) 
            {
                NCP_CALL(NCP_ST_SYSMEM_PHY_WL_DLY_ERR);
            }
            ncr_write32(region, 
                       NCP_PHY_CFG_SYSMEM_PHY_WRTLVLLOW_BL_CS(bl, rank),
                       ldly - 4);
        }
    }

    /* 
     * re-run the test with walking zero
     * It ought to pass. 
     */
    memset(&bad_bl, 0, sizeof(bad_bl));
    NCP_CALL(sm_bytelane_test(dev, addr, 1, 
                &bad_bl[0], &bad_bl[1], &bad_bl[2], num_bls));


    /* if we still have bad bytelanes then leveling has failed */
    if ((bad_bl[0] | bad_bl[1] | bad_bl[2]) != 0 ) {
        NCP_CALL(NCP_ST_SYSMEM_PHY_WL_ERR);
    }

    /* check the PHY status */
    NCP_CALL(ncp_sm_lsiphy_status_check(dev, smId, parms));


    /* 
     * If ECC is enabled now level the ECC byte lane 
     */
    if (parms->enableECC) {
        NCP_COMMENT("sysmem phy coarse write leveling - ECC bytelane rank %d", rank);

        ecc_mask = (parms->version == 0) ? NCP_SM_DENALI_V1_ECC_INTR_BITS :
                                           NCP_SM_DENALI_V2_ECC_INTR_BITS;

        /*
         *
         */
        switch (rank) 
        {
            case 0: 
                sc_node = sc_nodes[0];
                break;
            case 1: 
                /* due to address hashing, if an odd bit is
                 * set in the address this write will end up 
                 * in syscache 2, if an even bit is set it 
                 * will end up in syscache 1. 
                 *
                 * NOTE! This assumes there is only one bit set in addr!! 
                 *
                 * TODO! Revisit this for 3500/5500
                 */
                if (addr & 0xaaaaaaaa) {
                    sc_node = sc_nodes[2];
                } else {
                    sc_node = sc_nodes[1];
                }
                break;
            default: 
                NCP_CALL(NCP_ST_ERROR);
        }

        /* enable ECC reporting with no correction */
        mask = value = 0;
        SMAV( ncp_denali_DENALI_CTL_20_t, ctrl_raw, 1 );
        ncr_modify32( ctlRegion, NCP_DENALI_CTL_20, mask, value );

        NCP_CALL(sm_ecc_bytelane_test(dev, ctlRegion, addr, sc_node, 
                                         1, ecc_mask, &bad_bl[0]));
        bad_bl[0] = 0;
        NCP_CALL(sm_ecc_bytelane_test(dev, ctlRegion, addr, sc_node, 
                                         0, ecc_mask, &bad_bl[0]));

        /* for now assume ECC is always the last BL */
        bl = num_bls ;

        if (bad_bl[0] != 0) {
            
            /* 
             *  ECC bytelane needs leveling. 
             * 
             * first get the current write-leveling delay values 
             */
            ncr_read32(region, 
                       NCP_PHY_CFG_SYSMEM_PHY_WRTLVLUPP_BL_CS(bl, rank),
                       &udly);

            ncr_read32(region, 
                       NCP_PHY_CFG_SYSMEM_PHY_WRTLVLLOW_BL_CS(bl, rank),
                       &ldly);

            /* 
             * for the current values calculate how many clocks 
             * we can increment/decrement 
             */
            if ( udly <= ldly ) {
                ndecs = udly >> 2;
                nincs = 3 - (ldly >> 2);
            } else {
                ndecs = ldly >> 2;
                nincs = 3 - (udly >> 2);
            }

            adj = 0;
            while (ndecs--) 
            {
                adj -= 4;
                ncr_write32(region, 
                       NCP_PHY_CFG_SYSMEM_PHY_WRTLVLUPP_BL_CS(bl, rank),
                       udly + adj);

                ncr_write32(region, 
                       NCP_PHY_CFG_SYSMEM_PHY_WRTLVLLOW_BL_CS(bl, rank),
                       ldly + adj);

                NCP_CALL(sm_ecc_bytelane_test(dev, ctlRegion, addr, sc_node, 
                                             1, ecc_mask, &bad_bl[0]));
                bad_bl[0] = 0;
                NCP_CALL(sm_ecc_bytelane_test(dev, ctlRegion, addr, sc_node, 
                                         0, ecc_mask, &bad_bl[0]));

                if (bad_bl[0] == 0) {
                    /* it worked - we're done */
                    break;
                }
            }
            

        }

        if (bad_bl[0] != 0) {
            /* still bad, try advancing clocks */
            adj = 0;
            while (nincs--) 
            {
                adj += 4;
                ncr_write32(region, 
                       NCP_PHY_CFG_SYSMEM_PHY_WRTLVLUPP_BL_CS(bl, rank),
                       udly + adj);

                ncr_write32(region, 
                       NCP_PHY_CFG_SYSMEM_PHY_WRTLVLLOW_BL_CS(bl, rank),
                       ldly + adj);

                NCP_CALL(sm_ecc_bytelane_test(dev, ctlRegion, addr, sc_node, 
                                             1, ecc_mask, &bad_bl[0]));
                bad_bl[0] = 0;
                NCP_CALL(sm_ecc_bytelane_test(dev, ctlRegion, addr, sc_node, 
                                         0, ecc_mask, &bad_bl[0]));

                if (bad_bl[0] == 0) {
                    /* it worked - we're done */
                    break;
                }
            }
        }

        /* if we still have bad bytelanes then leveling has failed */
        if (bad_bl[0]) {
            NCP_CALL(NCP_ST_SYSMEM_PHY_ECC_WL_ERR);
        }

        /* disable ECC until all ranks are level */
        mask = value = 0;
        SMAV( ncp_denali_DENALI_CTL_20_t, ctrl_raw, 0 );
        ncr_modify32( ctlRegion, NCP_DENALI_CTL_20, mask, value );

    }

    /* check the PHY status */
    NCP_CALL(ncp_sm_lsiphy_status_check(dev, smId, parms));

NCP_RETURN_LABEL
    return ncpStatus;
}

#ifndef UBOOT
ncp_st_t
ncp_sm_cm_coarse_write_leveling(
        ncp_dev_hdl_t   dev,
        ncp_uint32_t    smId,
        ncp_uint32_t    rank,
        ncp_uint64_t    addr,
        ncp_sm_parms_t *parms)
{
    ncp_st_t        ncpStatus = NCP_ST_SUCCESS;

    ncp_region_id_t  ctlRegion;
    NCP_RMW_REG(ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t,   ddr_ctrl);
    NCP_RMW_REG(ncp_ddr_CFG_NTEMC_ECC_CTRL_r_t,   ecc_ctrl);


    NCP_COMMENT("treemem phy coarse write leveling");

    /* TODO: 
     *
     * The tree memory interface only has two byte-lanes,
     * one for data and one for the ECC check bit. For most 
     * board designs the two bytelanes will be aligned and 
     * not require coarse write leveling. Should we ever run
     * across a board which does require coarse write leveling
     * on the treemem interface we'll need to implement this
     * function.
     *
     */

    ctlRegion = NCP_REGION_ID(sm_nodes[smId], NCP_TREEMEM_TGT_DDR);

    /* set up for memory access */
    NCP_RMW_SET_FIELD(ddr_ctrl, wrt_lvl,     0);
    NCP_RMW_SET_FIELD(ddr_ctrl, ref_ena,     1);
    NCP_RMW_SET_FIELD(ddr_ctrl, odt_mode,    3);
    NCP_RMW(dev, ctlRegion, NCP_DDR_CFG_NTEMC_DDR_CTRL, ddr_ctrl);

    /* enable ECC */
    if (parms->enableECC) {
        NCP_RMW_SET_FIELD(ecc_ctrl, ecc_mode,     1);
        NCP_RMW(dev, ctlRegion, NCP_DDR_CFG_NTEMC_ECC_CTRL, ecc_ctrl);
    }
     
    /* set up for memory access */
    NCP_RMW_SET_FIELD(ddr_ctrl, auto_zq,     1);
    NCP_RMW_SET_FIELD(ddr_ctrl, zq_per,      0);
    NCP_RMW(dev, ctlRegion, NCP_DDR_CFG_NTEMC_DDR_CTRL, ddr_ctrl);


NCP_RETURN_LABEL
    return ncpStatus;
}
#endif

#ifdef UBOOT
#define ncp_sm_lsiphy_coarse_write_leveling ncp_sm_sm_coarse_write_leveling

#else 
ncp_st_t
ncp_sm_lsiphy_coarse_write_leveling(
        ncp_dev_hdl_t   dev,
        ncp_uint32_t    smId,
        ncp_uint32_t    rank,
        ncp_uint64_t    addr,
        ncp_sm_parms_t *parms)
{
    ncp_st_t        ncpStatus = NCP_ST_SUCCESS;

    switch (smId) {
        case 0:
        case 1:
            NCP_CALL(ncp_sm_sm_coarse_write_leveling(dev, smId, 
                        rank, addr, parms));
            break;

        case 2:
        case 3:
            NCP_CALL(ncp_sm_cm_coarse_write_leveling(dev, smId, 
                        rank, addr, parms));
            break;

        default:
            NCP_CALL(NCP_ST_SYSMEM_INVALID_ID);
    }


NCP_RETURN_LABEL
    return ncpStatus;
}

#endif


#if 0
/* TEMP TEST */
ncp_st_t 
ncp_sm_check_runtime(ncp_dev_hdl_t dev,
                     ncp_uint32_t  smId,
                     ncp_sm_parms_t *parms)
{
    ncp_st_t ncpStatus;
    int i;
    int bl;

    ncp_uint64_t addr;
    ncp_uint32_t base_offset = 0x10020;
    ncp_uint32_t offset;
    ncp_uint32_t regs[8];
    ncp_uint32_t nloops = 0;

    ncp_uint8_t wrbuf[NCP_SM_BURST_SIZE], rdbuf[NCP_SM_BURST_SIZE];

    ncp_uint16_t sm_node[2] = {34, 15};

    for (i = 0; i < NCP_SM_BURST_SIZE; i++)  {
        wrbuf[i] = i;
    }

    if (smId == 0) {
        addr = 0x300;
    }

    if (smId == 1) {
        addr = 0x400;
    }

    while (nloops < 10000) {
        offset = base_offset;
        for (bl = 0; bl < 9; bl++) {
            NCP_CALL(ncp_block_read32(dev, 
                                      NCP_REGION_ID(sm_node[smId], 1),
                                      offset,   
                                      &regs[0],
                                      8,
                                      0));

            for (i = 0; i < 8; i++) {
                if (regs[i] == 0x7f) {
                    int j;
                    printf("### got error after %d loops!\n", nloops);
                    printf("%d.1.0x%08x : ", sm_node[smId], offset);
                    for (j = 0; j < 4; j++) {
                        printf(" 0x%08x", regs[j]);
                    }
                    printf("\n");
                    printf("%d.1.0x%08x : ", sm_node[smId], offset + 0x10);
                    for (; j < 8; j++) {
                        printf(" 0x%08x", regs[j]);
                    }
                    printf("\n");

                    NCP_CALL(NCP_ST_ERROR);
                }
            }
            offset += 0x80;
        }


        /* if bit0 of the flags field is set, do some sysmem writes */
        if (parms->flags & 0x2) {
            NCP_CALL(ncp_block_write8(dev, NCP_REGION_NCA_NIC_SYSMEM,
                                      addr, wrbuf, NCP_SM_BURST_SIZE, 0));
        }


        /* if bit1 of the flags field is set, do some sysmem reads */
        if (parms->flags & 0x4) {
            NCP_CALL(ncp_block_read8(dev, NCP_REGION_NCA_NIC_SYSMEM,
                                      addr, rdbuf, NCP_SM_BURST_SIZE, 0));
        }

        nloops++;
    }

    printf("### no errors after %d loops!\n", nloops);

NCP_RETURN_LABEL
    return ncpStatus;

}
#endif

#define NCP_SM_FILL_BLOCK_SIZE 0x00100000
ncp_st_t
ncp_sm_lsiphy_runtime_adj(
        ncp_dev_hdl_t   dev,
        ncp_uint32_t    smId,
        ncp_sm_parms_t *parms)
{

    ncp_st_t        ncpStatus = NCP_ST_SUCCESS;
    ncp_region_id_t region;
    ncp_region_id_t ctlRegion;
    ncp_bool_t isSysMem;
    ncp_uint32_t mask;
    ncp_uint32_t value;
    ncp_uint32_t int_stat;

    if (smId >= NCP_EXTMEM_NUM_NODES) {
        NCP_CALL(NCP_ST_SYSMEM_INVALID_ID);
    }

    if (smId < NCP_SYSMEM_NUM_NODES) 
    {
        NCP_COMMENT("sysmem %d PHY runtime adjustment", smId);
        region = NCP_REGION_ID(sm_nodes[smId], NCP_SYSMEM_TGT_PHY);
        ctlRegion = NCP_REGION_ID(sm_nodes[smId], NCP_SYSMEM_TGT_DENALI);
        isSysMem = TRUE;

    }
#ifndef UBOOT
    else 
    {
        NCP_COMMENT("treemem %d PHY runtime adjustment", 
                            smId - NCP_SYSMEM_NUM_NODES);
        region = NCP_REGION_ID(sm_nodes[smId], NCP_TREEMEM_TGT_PHY);
        ctlRegion = NCP_REGION_ID(sm_nodes[smId], NCP_TREEMEM_TGT_DDR);
        isSysMem = FALSE;
    }
#endif

    /* indicate PHY initial training complete */

    if (isSysMem) {
        /* clear sw_leveling_mode */
        mask = value = 0;
        SMAV(ncp_denali_DENALI_CTL_21_t, sw_leveling_mode, 0);
        ncr_modify32(ctlRegion, NCP_DENALI_CTL_21, mask, value);

        mask = value = 0;
        SMAV(ncp_denali_DENALI_CTL_334_t, ctrlupd_req, 1);
        ncr_modify32(ctlRegion, NCP_DENALI_CTL_334, mask, value);
    }


    /* enable PHY runtime behavior */
    /* first do initratiotrain */
    mask = value = 0;
    SMAV(ncp_phy_CFG_SYSMEM_PHY_SMCTRL_r_t, initratiotrain, 1); 
    ncr_modify32(region, NCP_PHY_CFG_SYSMEM_PHY_SMCTRL, mask, value);

    /* poll for completion */
    SMAV(ncp_phy_CFG_SYSMEM_PHY_SMCTRL_r_t, initratiotrain, 0); 
    if (0 != ncr_poll(region, NCP_PHY_CFG_SYSMEM_PHY_SMCTRL, mask, value, 100, 100) )
    {
        /* shouldn't happen */
        NCP_CALL(NCP_ST_ERROR);
    }

    /* TODO! 
     * clear dpconfig0 bit 14 
     */

    /* enable runtime */
    mask = value = 0;
    SMAV(ncp_phy_CFG_SYSMEM_PHY_SMCTRL_r_t, tracklp, 1); 
    SMAV(ncp_phy_CFG_SYSMEM_PHY_SMCTRL_r_t, trackqrtr, 1); 
    SMAV(ncp_phy_CFG_SYSMEM_PHY_SMCTRL_r_t, vtccntena, 1); 
    ncr_modify32(region, NCP_PHY_CFG_SYSMEM_PHY_SMCTRL, mask, value);



    if (isSysMem) {
        ncr_write32(ctlRegion, 0x114, 0x3fff);

        /* 
         * Enable ECC correction. 
         * we'll initialize all sysmem later as part of syscache init
         */
        if (parms->enableECC) 
        {
            NCP_COMMENT("enabling ECC");
            mask = value = 0;
            SMAV( ncp_denali_DENALI_CTL_20_t, ctrl_raw, 3 );
            ncr_modify32( ctlRegion, NCP_DENALI_CTL_20, mask, value );
        }

        /* clear controller interrupt status */
        ncr_read32(ctlRegion, NCP_DENALI_CTL_260, &int_stat);
        ncr_write32(ctlRegion, NCP_DENALI_CTL_89, int_stat);
    } 
#ifndef UBOOT 
    else 
    {
        ncp_uint32_t reg;

        /* NCP_DDR_CFG_NTEMC_DFI_TIMING2  tctlupd_intv = 4 */
        NCP_CALL(ncp_read32(dev, ctlRegion, 0x30, &reg));
        reg &= 0xffffe000;
        reg |= 0x00000004;
        NCP_CALL(ncp_write32(dev, ctlRegion, 0x30, reg));
    }
#endif


    /* check the PHY status */
    ncpStatus = ncp_sm_lsiphy_status_check(dev, smId, parms);

#if 0
    /* TEMP DEBUG automatic checking of runtime operation */
    if (parms->flags & 0x01) {
        printf("checking runtime operation\n");
        NCP_CALL(ncp_sm_check_runtime(dev, smId, parms));
    }
#endif


NCP_RETURN_LABEL
    return ncpStatus;
}

#ifdef UBOOT
#include "ncp_sm_denali_2041_init.c"
#endif


static  ncp_uint64_t
calc_sdram_size(ncp_sm_parms_t *parms)
{
    unsigned long long sdram_capacity_bytes;
    unsigned long sdram_device_width_bits;
    unsigned long primary_bus_width_bits;

    sdram_capacity_bytes = (1 << parms->sdram_device_density) *
                ((256 * 1024 * 1024) / 8);
    sdram_device_width_bits = 4 * (1 << parms->sdram_device_width);
    primary_bus_width_bits = 8 * (1 << parms->primary_bus_width);
    sdram_capacity_bytes =  parms->num_ranks_per_interface *
                sdram_capacity_bytes *
                    (primary_bus_width_bits / sdram_device_width_bits);

    return sdram_capacity_bytes;

}

ncp_st_t
ncp_sysmem_init_lsiphy(
        ncp_dev_hdl_t   dev,
        ncp_uint32_t    smId,
        ncp_sm_parms_t *parms)
{
    ncp_st_t        ncpStatus;

    ncp_uint32_t    rank;
    ncp_uint64_t    addr;
    ncp_sm_topology_t topology = parms->topology;

    ncp_bool_t do_rd_lvl = TRUE;
    ncp_bool_t do_wr_lvl = TRUE;
    ncp_bool_t do_gt_trn = TRUE;


    /* static PHY setup */
    NCP_CALL(ncp_sm_lsiphy_static_init(dev, smId, parms));

    /* Get the system memory parameters via I2C or from the config */
    /* TODO */

    if (smId < NCP_SYSMEM_NUM_NODES) {
        /* Initialize the system memory controller */
        NCP_CALL(ncp_sm_denali_2041_init(dev, smId, parms)); 

        /* 
         * TEMP!?
         *   We enable the controller here instead of from within
         *   the controller init function to allow the script 
         *   framework to override controller init values.
         */
         
        /* enable the controller ! */
        ncr_write32(NCP_REGION_ID(34,0),  0x0030, 0x01010001 );
    } 
#ifndef UBOOT
    else 
    {
        NCP_CALL(ncp_cm_controller_init(dev, smId, parms)); 
    }
#endif


    /* do read calibration and fine write-leveling on each rank */
    for (rank = 0; rank < NCP_SM_MAX_RANKS; rank++) 
    {
        if (topology & (1 << rank)) 
        {
            if (do_wr_lvl) {
                /* fine write leveling */
                /* printf("wrlvl smId %d rank %d\n", smId, rank); */
                NCP_CALL(ncp_sm_lsiphy_training_run(dev, smId, rank, 0,
                         NCP_SYSMEM_PHY_WRITE_LEVELING,
                         parms));
            }

            if (do_gt_trn) {
                /* gate training */
                /* printf("gttrn smId %d rank %d\n", smId, rank); */
                NCP_CALL(ncp_sm_lsiphy_gate_training(dev, smId, rank, parms));
            }

            if (do_rd_lvl) {
                /* read leveling */
                /* printf("rdlvl smId %d rank %d\n", smId, rank); */
                NCP_CALL(ncp_sm_lsiphy_training_run(dev, smId, rank, 0,
                         NCP_SYSMEM_PHY_READ_LEVELING,
                         parms));

                NCP_CALL(ncp_sm_lsiphy_training_run(dev, smId, rank, 1,
                         NCP_SYSMEM_PHY_READ_LEVELING,
                         parms));
            }

        }
    }


    for (rank = 0; rank < NCP_SM_MAX_RANKS; rank++) 
    {
        if (topology & (1 << rank)) 
        {
            switch (rank) {
                case 0:
                default:
                    addr = 0;
                    break;

                case 1:
                    /*
                     * for the default setting of the syscache munge register
                     * on dual-rank memory, the bottom half of memory is rank0
                     * and the upper half is rank1
                     */
                    addr = calc_sdram_size(parms) >> 1;
                    break;
            }

#if 0
            printf("coarse wrlvl smId %d rank %d addr 0x%08llx\n", 
                                smId, rank, addr);
#endif
            NCP_CALL(ncp_sm_lsiphy_coarse_write_leveling(dev, smId, rank, addr,
                                                      parms));
        }
    }

    NCP_CALL(ncp_sm_lsiphy_runtime_adj(dev, smId, parms));

NCP_RETURN_LABEL

#ifdef SM_REG_DUMP
  if (NCP_ST_SUCCESS != ncpStatus)
    ncp_sm_lsiphy_reg_dump(dev, smId);
#endif

 return  ncpStatus;
}
