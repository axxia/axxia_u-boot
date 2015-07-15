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
#define NCP_CONFIG_CMEM
#include <stdio.h>

#include "ncp.h"
#include "ncp_pvt.h"
#include "ncp_sysmem_ext.h"
#include "ncp_sysmem_lsiphy.h"

/* RTE build always includes 5500 ELM support */
#define NCP_CONFIG_ELM

#else 
#ifdef CONFIG_CMEM_INIT
#define NCP_CONFIG_CMEM
#endif

/* U-boot build only includes ELM support for 5500 */
#ifdef CONFIG_AXXIA_55XX
#define NCP_CONFIG_ELM
#endif
#endif


/* register definitions for ACP25xx */
#define NCP_SYSMEM_LSIPHY
#include "regs/ncp_phy_regs_acp2500.h"
#include "regs/ncp_phy_reg_defines_acp2500.h"
#include "regs/ncp_denali_regs_acp2500.h"
#include "regs/ncp_denali_reg_defines_acp2500.h"

#ifdef NCP_CONFIG_ELM
/* register definitions for ACP55xx */
#include "regs/ncp_elm_regs.h"
#include "regs/ncp_elm_reg_defines.h"
#endif

#ifdef NCP_CONFIG_CMEM
#include "regs/ncp_ddr_regs.h"
#include "regs/ncp_ddr_reg_defines.h"
#endif

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



/* globals */
#ifndef UBOOT
ncp_sm_intr_status_fn_t intrStatFn = NULL;
ncp_sm_ecc_enb_fn_t eccEnbFn = NULL;
ncp_sm_poll_controller_fn_t pollControllerFn = NULL;
ncp_uint32_t num_bytelanes = 0;
#else
ncp_sm_intr_status_fn_t intrStatFn __attribute__ ((section ("data"))) = NULL;
ncp_sm_ecc_enb_fn_t eccEnbFn __attribute__ ((section ("data"))) = NULL;
ncp_sm_poll_controller_fn_t pollControllerFn __attribute__ ((section ("data"))) = NULL;
ncp_uint32_t num_bytelanes __attribute__ ((section ("data"))) = 0;
#endif

/* temp */
typedef void ncp_sm_phy_stat_t;

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

#ifndef UBOOT
#define NCP_SM_PHY_REG_DUMP
#endif
#ifdef  NCP_SM_PHY_REG_DUMP 

static ncp_st_t 
dump_regs(ncp_dev_hdl_t dev, ncp_uint32_t region, ncp_uint32_t offset, ncp_uint32_t num)
{
    int i;
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_uint32_t reg;
    for (i = 0; i < num;  i++) 
    {
        if ( (i & 0x3) == 0) printf("  %u.%u.0x%08x  ", NCP_NODE_ID(region), NCP_TARGET_ID(region), offset);

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



    ncr_read32(region, NCP_PHY_CFG_SYSMEM_PHY_DPIOVREFSET, &reg);
    printf("\n\n  DPIOVREFSET : 0x%08x\n",  reg);
    ncr_read32(region, NCP_PHY_CFG_SYSMEM_PHY_ADR0_ADRIOSET_1ST, &reg);
    printf(  "\nADR0_ADRIOSET : 0x%08x\n", reg);
    ncr_read32(region, NCP_PHY_CFG_SYSMEM_PHY_ADR1_ADRIOSET, &reg);
    printf(  "ADR1_ADRIOSET : 0x%08x\n", reg);
    ncr_read32(region, NCP_PHY_CFG_SYSMEM_PHY_ADR2_ADRIOSET, &reg);
    printf(  "ADR2_ADRIOSET : 0x%08x\n", reg);
    ncr_read32(region, NCP_PHY_CFG_SYSMEM_PHY_ADR3_ADRIOSET, &reg);
    printf(  "ADR3_ADRIOSET : 0x%08x\n", reg);

    printf("\nADR Phase Select :\n");
    dump_regs(dev, region, 0x8000, 2);
    printf("\n");
    dump_regs(dev, region, 0x8800, 2);
    printf("\n");
    dump_regs(dev, region, 0x9000, 2);
    printf("\n");
    dump_regs(dev, region, 0x9800, 2);
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
        printf("\nRDALIGNNDQ[%d]: \n", j);
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
    
        printf("\n NLOWRATIO[%d]: ", j);
        for (i = 0; i < num_bls; i++) 
        {
            ncr_read32( regionId, 
                        NCP_PHY_CFG_SYSMEM_PHY_NLOWRATIO_BL_CS(i, j),
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
    ncp_uint32_t smId,
    ncp_uint32_t chipType)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_uint32_t num_bls;
    ncp_uint32_t num_ranks;
    ncp_region_id_t regionId;


    if (smId < NCP_SYSMEM_NUM_NODES) {
        num_bls = (chipType == NCP_CHIP_ACP25xx) ? 5 : 9;
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

        case 1: 
            regionId = NCP_REGION_ID(0xf, 1);
            break;

        case 2:
            regionId = NCP_REGION_ID(0x8, 0xa);
            break;

        case 3:
            regionId = NCP_REGION_ID(0x9, 0xa);
            break;
        default:
            NCP_CALL(NCP_ST_SYSMEM_INVALID_ID);
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
     

#ifdef NCP_SM_PHY_REG_RESTORE
/*
 * ncp_sm_lsiphy_reg_save/restore 
 *
 *   A set of functions to read a set of PHY calibration registers 
 *   and store them to SPI flash, or read the register values from
 *   flash and restore them to h/w. 
 *
 *   The register list is compacted to reduce code and data size.
 */

typedef struct {
    ncp_uint32_t   baseOffset;
    ncp_uint8_t    nregs;
    ncp_uint8_t    stride;
    ncp_uint8_t    width;
    ncp_uint8_t    nranks;
    short          *fudge;
} ncp_sm_phy_reg_list_t;

/* 
 * address fudge factor for WRTALIGNDQS broadcast addresses 
 */
short wrdqs_fudge[2] = {36, -8};

ncp_sm_phy_reg_list_t ncp_sm_phy_regs[2] = 
{
    { NCP_PHY_CFG_SYSMEM_PHY_WRTLVLUPP_BL0CS0,   2,  4,  1,  1, NULL},
    { NCP_PHY_CFG_SYSMEM_PHY_WRTALIGNDQ0_BL0CS0, 2, 16,  1,  1, wrdqs_fudge},
};

#ifndef UBOOT 
/* 
 * for testing from the external host
 *
 */
#define PHY_REG_STORAGE_SIZE ( 4 * 1024 )

void *retention=NULL;

int
ncp_map_phy_reg_file(void)
{

    char  fname[]  = "/tmp/sm_phy_regs.dat";
    int   fd;
    char null = '\0';

    fd = open(fname, O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("open");
        return -1;
    }

#if 1
    /* set the file size */
    if (lseek(fd, PHY_REG_STORAGE_SIZE, SEEK_SET) < 0)
    {
        (perror("lseek"));
        return -1; 
    }

    if (write(fd, (void *) &null, sizeof(char)) == -1)
    {
        (perror("write"));
        return -1;
    }
#endif

    retention = (ncp_uint8_t *)mmap( 0, PHY_REG_STORAGE_SIZE,
                                     (PROT_READ | PROT_WRITE),
                                     MAP_SHARED, fd, 0);

    printf("retention = %p\n", retention);
    if (retention == (ncp_uint8_t *) MAP_FAILED)
    {
        perror("mmap");
        return -1;
    }

    return 0;

}

#else 
#define ncp_map_phy_reg_file() 0
#endif

ncp_st_t
ncp_sm_lsiphy_reg_save_restore(
        ncp_dev_hdl_t dev,
        ncp_region_id_t region,
        ncp_uint8_t    num_bytelanes,
        ncp_uint32_t   *buf,
        ncp_bool_t    save)

{

    ncp_st_t     ncpStatus = NCP_ST_SUCCESS;
    ncp_uint32_t idx;
    ncp_uint32_t bl;
    ncp_uint32_t rank;
    ncp_uint32_t nreg; 
    ncp_uint32_t offset;
    ncp_uint8_t  *pnt = (ncp_uint8_t *) buf;
    ncp_uint8_t   val8;
    ncp_uint16_t  val16;
    ncp_uint16_t *p16;

    ncp_sm_phy_reg_list_t *pList;
    ncp_uint32_t  value;

    for (idx = 0; idx < 2; idx++) 
    {
        pList = &ncp_sm_phy_regs[idx];

        for (rank = 0; rank <= pList->nranks; rank++)
        {
            for (bl = 0; bl < num_bytelanes; bl++) 
            {
                offset = pList->baseOffset + (rank * 0x100) + (bl * 0x800);
                for (nreg = 0; nreg < pList->nregs; nreg++) 
                {

                    if (save) 
                    {
                        /* 
                         * read the register and save it in the packed buffer
                         */
                        ncr_read32(region, offset, &value);

                        if (pList->width == 1) 
                        {
                            *pnt++ = (ncp_uint8_t) value;
                        } else {
                            p16 = (ncp_uint16_t *) pnt;
                            *p16 = (ncp_uint16_t) value;
                            pnt+=2;
                        }
                    } else {
                        /* 
                         * read the value from the packed buffer and write it
                         * back to h/w.
                         */
                        if (pList->width == 1) 
                        {
                            val8 = *pnt++;
                            value = (ncp_uint32_t) val8;
                        } else {
                            p16 = (ncp_uint16_t *) pnt;
                            val16 = *p16;
                            value = (ncp_uint32_t) val16;
                            pnt += 2;
                        }

                        if (pList->fudge) 
                        {
                            offset += pList->fudge[nreg];
                        }

                        ncr_write32(region, offset, value); 
                    }

                    offset += pList->stride;
                }
            }
        }
    }

NCP_RETURN_LABEL

    return ncpStatus;

}

ncp_st_t
ncp_sm_lsiphy_reg_save(
        ncp_dev_hdl_t dev,
        ncp_uint32_t smId,
        ncp_sm_parms_t *parms)

{
    ncp_uint32_t *buf = retention + (smId * DDR_PHY_REGS_SIZE);
    ncp_region_id_t regionId;

    if (smId == 0) {
        regionId = NCP_REGION_ID(34,1);
    } else {
        regionId = NCP_REGION_ID(15,1);
    }

    printf("setting smId %d *buf (%p) to %x\n", smId, buf, DDR_PHY_REGS_TAG_SAVE);

    *buf++ = DDR_PHY_REGS_TAG_SAVE;

    NCP_COMMENT("writing SMEM%d PHY registers to LSM\n", smId);
    ncp_sm_lsiphy_reg_save_restore(dev, regionId,
                    parms->num_bytelanes, buf, 1);

#ifndef UBOOT
    buf = retention + (smId * DDR_PHY_REGS_SIZE);
    *buf = DDR_PHY_REGS_TAG_PROM;
    printf("reg_save2buf @%p = 0x%08x\n", buf, *buf);
#endif

    return NCP_ST_SUCCESS;
}


ncp_st_t
ncp_sm_lsiphy_reg_restore(
        ncp_dev_hdl_t dev,
        ncp_uint32_t smId,
        ncp_sm_parms_t *parms)

{

    ncp_uint32_t *buf = retention + (smId * DDR_PHY_REGS_SIZE);
    ncp_region_id_t regionId;

    if (smId == 0) {
        regionId = NCP_REGION_ID(34,1);
    } else {
        regionId = NCP_REGION_ID(15,1);
    }
    printf("checking smId %d *buf (%p) : %x\n", smId, buf, *buf);

/*     if ( (smId == 0) && (*buf != DDR_PHY_REGS_TAG_PROM) ) { */
    if ( (*buf != DDR_PHY_REGS_TAG_PROM) ) {
        printf("SMEM%d DDR restore buffer invalid!\n", smId);
        return -1;
    }

    buf++;

    ncp_sm_lsiphy_reg_save_restore(dev, regionId,
                    parms->num_bytelanes, buf, 0);

    return NCP_ST_SUCCESS;
}

#else 

#define ncp_sm_lsiphy_reg_restore(d, s, p) NCP_ST_SUCCESS
#define ncp_sm_lsiphy_reg_save(d, s, p)    NCP_ST_SUCCESS
#define ncp_map_phy_reg_file()             NCP_ST_SUCCESS

#endif /* UBOOT */



static ncp_uint32_t
ncp_sm_intr_status_55xx(
    ncp_dev_hdl_t   dev,
    ncp_region_id_t regionId,
    ncp_uint32_t    mask)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_uint32_t value;
    /* read interrupt status */
    ncr_read32( regionId, NCP_DENALI_CTL_260, &value );

    /* apply mask */
    value &= mask;

    /* write interrupt acknowledge */
    ncr_write32( regionId, NCP_DENALI_CTL_338, value );

    NCP_CALL(ncpStatus);

NCP_RETURN_LABEL
    return value;
}

static ncp_uint32_t
ncp_sm_poll_controller_55xx(
    ncp_dev_hdl_t   dev,
    ncp_region_id_t regionId,
    ncp_sm_poll_event_t event)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_uint32_t value;

    switch (event)
    {
        case NCP_SM_MC_INIT_DONE:
            value = 0x00000100;
            break;

        case NCP_SM_LP_OP_DONE:
            value = 0x00000200;
            break;

        case NCP_SM_BIST_DONE:
            value = 0x00000400;
            break;

        case NCP_SM_LVL_OP_DONE:
            value = 0x00040000;
            break;

        case NCP_SM_MR_OP_DONE:
            value = 0x00100000;
            break;

        default:
            NCP_CALL(NCP_ST_ERROR);
    }

    ncpStatus = ncr_poll(regionId, NCP_DENALI_CTL_260, 
                value, value, 100, 100) ;

    /* return if error */
    NCP_CALL(ncpStatus); 

    /* acknowledge the interrupts */
    ncp_sm_intr_status_55xx(dev, regionId, value);

NCP_RETURN_LABEL
    return ncpStatus;
}


static ncp_uint32_t
ncp_sm_ecc_enb_55xx(
    ncp_dev_hdl_t   dev,
    ncp_region_id_t regionId,
    ncp_uint32_t    eccEnb)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_uint32_t mask, value;

    mask = value = 0;
    SMAV( ncp_denali_DENALI_CTL_421_t, ecc_en, eccEnb );
    ncr_modify32( regionId, NCP_DENALI_CTL_421, mask, value );

    NCP_CALL(ncpStatus);

NCP_RETURN_LABEL
    return value;
}


static ncp_uint32_t
ncp_sm_intr_status_35xx(
    ncp_dev_hdl_t   dev,
    ncp_region_id_t regionId,
    ncp_uint32_t    mask)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_uint32_t value;
    /* read interrupt status */
    ncr_read32( regionId, NCP_DENALI_CTL_346, &value );

    /* apply mask */
    value &= mask;

    /* write interrupt acknowledge */
    ncr_write32( regionId, NCP_DENALI_CTL_347, value );

    NCP_CALL(ncpStatus);

NCP_RETURN_LABEL
    return value;
}

static ncp_uint32_t
ncp_sm_poll_controller_35xx(
    ncp_dev_hdl_t   dev,
    ncp_region_id_t regionId,
    ncp_sm_poll_event_t event)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_uint32_t value;

    switch (event)
    {
        case NCP_SM_MC_INIT_DONE:
            value = 0x00000100;
            break;

        case NCP_SM_LP_OP_DONE:
            value = 0x00000200;
            break;

        case NCP_SM_BIST_DONE:
            value = 0x00000400;
            break;

        case NCP_SM_LVL_OP_DONE:
            value = 0x00040000;
            break;

        case NCP_SM_MR_OP_DONE:
            value = 0x00100000;
            break;

        default:
            NCP_CALL(NCP_ST_ERROR);
    }

    ncpStatus = ncr_poll(regionId, NCP_DENALI_CTL_346, 
                value, value, 100, 100) ;

    /* return if error */
    NCP_CALL(ncpStatus); 

    /* acknowledge the interrupts */
    ncp_sm_intr_status_35xx(dev, regionId, value);

NCP_RETURN_LABEL
    return ncpStatus;
}


static ncp_uint32_t
ncp_sm_ecc_enb_35xx(
    ncp_dev_hdl_t   dev,
    ncp_region_id_t regionId,
    ncp_uint32_t    eccEnb)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_uint32_t value=0;

    ncr_read32( regionId, NCP_DENALI_CTL_373, &value );
    value &= ~(1<<8);
    value |= (eccEnb << 8);
    ncr_write32( regionId, NCP_DENALI_CTL_373, value );

    NCP_CALL(ncpStatus);

NCP_RETURN_LABEL
    return value;
}


static ncp_st_t 
ncp_sm_dfi_init_start(
    ncp_dev_hdl_t dev,
    ncp_region_id_t region,
    ncp_sm_parms_t *parms)
{
    ncp_st_t     ncpStatus = NCP_ST_SUCCESS;
    ncp_uint32_t value;

    /* enable ECC if needed */
    if (parms->enableECC) 
    {
        eccEnbFn(dev, region, 1);
    }

    /* set reduc if needed */
    if (parms->primary_bus_width == 2) {
        value = 0;
        /* set the controller half-data path mode for 32-bit bus */
        SV( ncp_denali_DENALI_CTL_11_t, reduc, 1 );
        ncr_write32(region, 0x002c, value);
    }

    /* 
     * DENALI_CTL_127  
     * set dfi_init_start 
     */
    ncr_write32(region,  0x01fc, 0x80000000);

NCP_RETURN_LABEL
    return ncpStatus;

}

#ifdef NCP_CONFIG_CMEM
static ncp_st_t 
ncp_cm_dfi_init_start(
    ncp_dev_hdl_t dev,
    ncp_region_id_t region,
    ncp_sm_parms_t *parms)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_uint32_t value;

    /* enable ECC if needed */
    if (parms->enableECC) 
    {
        /* TODO ??? */
    }

    ncr_read32(region, NCP_DDR_CFG_NTEMC_DDR_CTRL, &value);
    value |= 0x00800000;
    ncr_write32(region, NCP_DDR_CFG_NTEMC_DDR_CTRL, value);

NCP_RETURN_LABEL
    return ncpStatus;
}

#endif


/*
 * read all of the phy error registers for display purposes
 *
 */
ncp_st_t
ncp_sm_lsiphy_status_get(
        ncp_dev_hdl_t dev,
        ncp_uint32_t  smId,
        ncp_sm_lsiphy_stat_t *status)
{
    ncp_st_t        ncpStatus = NCP_ST_SUCCESS;
    ncp_region_id_t region;

    if (smId >= NCP_EXTMEM_NUM_NODES) {
        NCP_CALL(NCP_ST_SYSMEM_INVALID_ID);
    }

    if (smId < NCP_SYSMEM_NUM_NODES) 
    {
        region = NCP_REGION_ID(sm_nodes[smId], NCP_SYSMEM_TGT_PHY);
    }
    else 
    {
        region = NCP_REGION_ID(sm_nodes[smId], NCP_TREEMEM_TGT_PHY);
    }

    /* general PHY status */
    ncr_read32(region, NCP_PHY_CFG_SYSMEM_PHY_STAT, 
                        (ncp_uint32_t *) &status->phyStat);

    /* gate-training status */
    ncr_read32(region, NCP_PHY_CFG_SYSMEM_PHY_GTTRAINSTAT0, 
                        (ncp_uint32_t *) &status->gttrn.stat0);

    ncr_read32(region, NCP_PHY_CFG_SYSMEM_PHY_GTTRAINSTAT1, 
                        (ncp_uint32_t *) &status->gttrn.stat1);


    /* read-leveling status */
    ncr_read32(region, NCP_PHY_CFG_SYSMEM_PHY_RDLVLSTATNEDGE, 
                        (ncp_uint32_t *) &status->rdlvl.nedge);

    ncr_read32(region, NCP_PHY_CFG_SYSMEM_PHY_RDLVLSTATPEDGE, 
                        (ncp_uint32_t *) &status->rdlvl.pedge);

    ncr_read32(region, NCP_PHY_CFG_SYSMEM_PHY_RDDSKWSTAT, 
                        (ncp_uint32_t *) &status->rdlvl.dskew);

    ncr_read32(region, NCP_PHY_CFG_SYSMEM_PHY_RDDSKWFATALSTAT, 
                        (ncp_uint32_t *) &status->rdlvl.dskew_fatal);

    /* write-leveling status */
    ncr_read32(region, NCP_PHY_CFG_SYSMEM_PHY_WRLVLSMSTAT, 
                        (ncp_uint32_t *) &status->wrlvl.stat);


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
    ncp_sm_lsiphy_stat_t phyStat = {{0}};

    if (smId >= NCP_EXTMEM_NUM_NODES) {
        NCP_CALL(NCP_ST_SYSMEM_INVALID_ID);
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
    ncp_region_id_t region = 0;
    ncp_region_id_t ctlRegion;
    ncp_bool_t      isSysMem;
    ncp_uint32_t    memId = 0;
    int             i;
    ncp_uint32_t    vtc_cnt;
    ncp_uint32_t    eccBlMask;
    ncp_int32_t     rlrank_adj;

    ncp_phy_CFG_SYSMEM_PHY_DPCONFIG2_BLx_r_t   dpconfig2  = {0};
    ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG1_r_t      phyconfig1 = {0};
    ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG2_r_t      phyconfig2 = {0};
    ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG3_BLx_r_t  phyconfig3 = {0};
    ncp_phy_CFG_SYSMEM_PHY_SMCTRL_r_t          smctrl     = {0};
#if 0
    ncp_phy_CFG_SYSMEM_PHY_ADRx_AD12_ADRIOLPRCTRL_r_t lpctrl = {0}; 
#endif
    ncp_uint32_t mask, value;

    if (smId >= NCP_EXTMEM_NUM_NODES) {
        NCP_CALL(NCP_ST_SYSMEM_INVALID_ID);
    }

    /* set up chip-specific parameters */
    if (smId < NCP_SYSMEM_NUM_NODES) 
    {
        NCP_COMMENT("sysmem %d PHY static init", smId);
        region    = NCP_REGION_ID(sm_nodes[smId], NCP_SYSMEM_TGT_PHY);
        ctlRegion = NCP_REGION_ID(sm_nodes[smId], NCP_SYSMEM_TGT_DENALI);
        isSysMem = TRUE;
        memId    = smId;

        switch (parms->version) 
        {
            case NCP_CHIP_ACP35xx:
                parms->num_bytelanes = 9; /* 8 8-bit data + 1 ecc lanes */
                intrStatFn = ncp_sm_intr_status_35xx;
                eccEnbFn = ncp_sm_ecc_enb_35xx;
                pollControllerFn = ncp_sm_poll_controller_35xx;
                break;

            case NCP_CHIP_ACP55xx:
                parms->num_bytelanes = 9;
                intrStatFn = ncp_sm_intr_status_55xx;
                eccEnbFn = ncp_sm_ecc_enb_55xx;
                pollControllerFn = ncp_sm_poll_controller_55xx;
                break;

            default:
                printf("Unexpected chipType %d\n", (int) parms->version);
                NCP_CALL(NCP_ST_ERROR);
        }

        /*
         * new sequence for DFI2.0
         * we must set up the controller to indicate which bytelanes
         * are disabled prior to issuing dfi_cntl_start, which must 
         * be prior to PHY static init
         */
        ncp_sm_dfi_init_start(dev, ctlRegion, parms);
    }
#ifdef NCP_CONFIG_CMEM
    else
    {
        NCP_COMMENT("treemem %d PHY static init", smId - NCP_SYSMEM_NUM_NODES);
        region    = NCP_REGION_ID(sm_nodes[smId], NCP_TREEMEM_TGT_PHY);
        ctlRegion = NCP_REGION_ID(sm_nodes[smId], NCP_TREEMEM_TGT_DDR);
        isSysMem = FALSE;
        parms->num_bytelanes = 2;
        memId = smId - NCP_SYSMEM_NUM_NODES;
        /* TODO??? intrStat/eccEnb functions? */

        ncp_cm_dfi_init_start(dev, ctlRegion, parms);
    }
#endif


    /* Disable Dynamic ODT */
    mask = value = 0;
    SMAV(ncp_phy_CFG_SYSMEM_PHY_DPCONFIG0_BLx_r_t, ovrdynodt, 1);
    for (i = 0; i < parms->num_bytelanes; i++) 
    {
        ncr_modify32(region, NCP_PHY_CFG_SYSMEM_PHY_DP_CONFIG0_BL(i), 
                        mask, value);
    }

    /* initial PHY configuration */
   /*
    * the setting of WLRANK is determined by the formula 
    *
    *   WLRANK = CWL + AL - 3 - (halfx mode) - (rank_highfreq * 2) 
    *
    *   For sysmem, AL = 0, halfx = 1, and rank_highfreq = 1,
    *   so we have CWL - 3 - 1 - 2, or CWL-6
    *
    * This doesn't matter for CMEM since CMEM is single-rank
    */
    phyconfig1.rdranksw  = 0; /* TODO: Do these need to be set later on?? */
    phyconfig1.wrranksw  = 0;
    phyconfig1.wrlatrank = parms->CAS_write_latency - 6;
    ncr_write32(region, NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG1, 
                        *(ncp_uint32_t *) &phyconfig1);

    /* reset the PHY */
    phyconfig2.clrfifo         = 1;
    phyconfig2.fifoena         = 1;
    phyconfig2.dpen            = 0x1ff;
    phyconfig2.rstnio          = 1;
    phyconfig2.dfiwrlvlphymode = 1;
    phyconfig2.dfigttrainmode  = 1;
    phyconfig2.dfirdlvlphymode = 1;
    
    ncr_write32(region, NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG2, 
                        *(ncp_uint32_t *) &phyconfig2);


    /* 
     * RLRANK = RLGATE - tDFI_RDDATA_EN
     *
     * tDFI_RDDATA_EN = RDLAT_ADJ + REG_DIMM_ENABLE - 1
     *
     * For now, RDLAT_ADJ is hard-coded to 4 and registered
     * DIMMs are not yet supported, so we have 
     *
     * RLRANK = RLGATE - (4 + 0 - 1) = RLGATE - 3
     *
     * if the initial RLRANK value (specified by the 
     * min_phy_cal_delay parameter) is less then 3 we
     * make it 3.
     *
     * TODO!?! 
     * If REG_DIMM_ENABLE then add one to RLGATE
     *
     */

    if (parms->version == NCP_CHIP_ACP35xx)
    {
	/* based on waveform readout */
        rlrank_adj = -2;
    } 
    else 
    {
        rlrank_adj = 1;
    }

#if 0
    if (parms->per_mem[memId].phy_min_cal_delay < rlrank_adj) {
        parms->per_mem[memId].phy_min_cal_delay = rlrank_adj;
    }
#endif

    phyconfig3.rdlatrank = parms->per_mem[memId].phy_min_cal_delay + rlrank_adj;
    phyconfig3.rdlatgate = parms->per_mem[memId].phy_min_cal_delay;
    for (i = 0; i < parms->num_bytelanes; i++) 
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

    eccBlMask = 0x100;  /* BL8 for ECC */

    if (parms->enableECC == FALSE) {
        if (isSysMem) 
        {
            phyconfig2.dpen &= ~eccBlMask;
        } else {
            phyconfig2.dpen &= 0x001;  /* BL0 only */
        }
    }

    /* only needed for treemem in FBRS mode */
    if (isSysMem == FALSE) {
        phyconfig2.dpen &= 0x003;
    }

    ncr_write32(region, NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG2, 
                        *(ncp_uint32_t *) &phyconfig2);


    mask = value = 0;
    if (isSysMem) {
        /* enable internal VREF */
#if 0
        /* TODO: for register DIMM support !! */
        /* parity error input */
        lpctrl.enivref4 = 1;
        ncr_write32(region, NCP_PHY_CFG_SYSMEM_PHY_ADR0_AD12_ADRIOLPRCTRL, 
                    *(ncp_uint32_t *) &lpctrl);
        lpctrl.enivref4 = 0;
#endif

        /* feedback loop */
        mask = value = 0;
        SMAV(ncp_phy_CFG_SYSMEM_PHY_ADRx_AD12_ADRIOLPRCTRL_r_t , lpr4, 0 );
        ncr_modify32(region, NCP_PHY_CFG_SYSMEM_PHY_ADR1_AD12_ADRIOLPRCTRL, 
                    mask, value);

        SMAV(ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG0_r_t , fbadrsel, 1 );
        SMAV(ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG0_r_t , fblpsel,  0 );

        /* initialize VTC count */
        /* TODO : make this configuration parameter?? */
        /* FREQDEP: for now 7.8 us at 800MHz */
        vtc_cnt = 0x1860;

    }
    else {

        /* initialize VTC count */
        /* TODO : make this configuration parameter?? */
        /* FREQDEP: for now 7.8 us at 667MHz */
        vtc_cnt = 0x1450;

        /* feedback loop */
        mask = value = 0;
        SMAV(ncp_phy_CFG_SYSMEM_PHY_ADRx_AD12_ADRIOLPRCTRL_r_t , lpr10, 0 );
        ncr_modify32(region, NCP_PHY_CFG_SYSMEM_PHY_ADR2_AD12_ADRIOLPRCTRL, 
                    mask, value);

        SMAV(ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG0_r_t , fbadrsel, 2 );
        SMAV(ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG0_r_t , fblpsel,  2 );
    }
    ncr_write32(region, NCP_PHY_CFG_SYSMEM_PHY_VTCCOUNT, vtc_cnt);

    ncr_modify32( region, NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG0, mask, value );


    /* init qrtr */
    smctrl.initqrtr     = 1;
    smctrl.initdfitrain = 1;
    smctrl.initfb       = 1;
    ncr_write32(region, NCP_PHY_CFG_SYSMEM_PHY_SMCTRL, 
                        *(ncp_uint32_t *) &smctrl);

    /* Poll till feedback SM and qrtr cycle SM are settled */
    if (0 != ncr_poll(region, NCP_PHY_CFG_SYSMEM_PHY_STAT, 0x600, 0x000, 100, 100) )
    {
        NCP_CALL(NCP_ST_ERROR);
    }

    /*
     * BZ52010
     *
     * the PHY will enable read path as part of the above training.
     * On some systems having the read path enabled during write leveling
     * causes problems (so far this has only been observed for CMEM). 
     * We can avoid these issues by disabling the read path here, it will
     * be enabled later 
     */
    dpconfig2.enardpath = 0;
    for (i = 0; i < parms->num_bytelanes; i++) 
    {
        ncr_write32(region, NCP_PHY_CFG_SYSMEM_PHY_DP_CONFIG2_BL(i), 
                        *(ncp_uint32_t *) &dpconfig2);
    }

    if (parms->single_bit_mpr) {
        ncr_write32(region, NCP_PHY_CFG_SYSMEM_PHY_RDLVLCMPDATEVN, 
                parms->per_mem[memId].phy_rdlvl_cmp_even);
        ncr_write32(region, NCP_PHY_CFG_SYSMEM_PHY_RDLVLCMPDATODD, 
                parms->per_mem[memId].phy_rdlvl_cmp_odd);
    }

    /* 
     * ADR Phase Select 
     * 
     *   the config parameter is a two-bit field which 
     *   indicates 0/90/180 degree of phase shift. This
     *   is applied to each of the ADDR_CMD_OUT bits. 
     *
     *   Instead of messing with the register field definitions
     *   we just mechanically compute the register value.
     */
    value = 0;
    for (i = 0; i < 8; i++) 
    {
        value |= (parms->per_mem[memId].phy_adr_phase_select & 0x3) << (i*2);
    }
    ncr_write32(region, NCP_PHY_CFG_SYSMEM_PHY_ADR_BC_PHASE90SEL0, value);
    ncr_write32(region, NCP_PHY_CFG_SYSMEM_PHY_ADR_BC_PHASE90SEL1, value);
   

    /* ADR_IO_VREF_SETTING */
    /* use SMAV to set the mask for all configurable fields */
    mask = value = 0;
    SMAV(ncp_phy_CFG_SYSMEM_PHY_ADRx_ADRIOSET_1ST_r_t, adrdrvac, 3);
    SMAV(ncp_phy_CFG_SYSMEM_PHY_ADRx_ADRIOSET_1ST_r_t, adrdrvck0, 3);
    SMAV(ncp_phy_CFG_SYSMEM_PHY_ADRx_ADRIOSET_1ST_r_t, adrdrvck1, 3);
    SMAV(ncp_phy_CFG_SYSMEM_PHY_ADRx_ADRIOSET_1ST_r_t, adrslac, 3);
    SMAV(ncp_phy_CFG_SYSMEM_PHY_ADRx_ADRIOSET_1ST_r_t, adrslck0, 3);
    SMAV(ncp_phy_CFG_SYSMEM_PHY_ADRx_ADRIOSET_1ST_r_t, adrslck1, 3);

    /* now set the value from the user configuration */
    value = parms->per_mem[memId].phy_adr_io_vref_set;

    ncr_modify32(region, NCP_PHY_CFG_SYSMEM_PHY_ADR0_ADRIOSET_1ST, mask, value);
    ncr_modify32(region, NCP_PHY_CFG_SYSMEM_PHY_ADR1_ADRIOSET, mask, value);
    ncr_modify32(region, NCP_PHY_CFG_SYSMEM_PHY_ADR2_ADRIOSET, mask, value);


    /* DP_IO_VREF_SETTING */
    /* use SMAV to set the mask for all configurable fields */
    mask = value = 0;
    SMAV(ncp_phy_CFG_SYSMEM_PHY_DPIOVREFSET_r_t, sldm, 3);
    SMAV(ncp_phy_CFG_SYSMEM_PHY_DPIOVREFSET_r_t, sldqs, 3);
    SMAV(ncp_phy_CFG_SYSMEM_PHY_DPIOVREFSET_r_t, sldq, 3);

    SMAV(ncp_phy_CFG_SYSMEM_PHY_DPIOVREFSET_r_t, drvdq, 3);
    SMAV(ncp_phy_CFG_SYSMEM_PHY_DPIOVREFSET_r_t, drvdqs, 3);
    SMAV(ncp_phy_CFG_SYSMEM_PHY_DPIOVREFSET_r_t, drvdm, 3);

    SMAV(ncp_phy_CFG_SYSMEM_PHY_DPIOVREFSET_r_t, odtimpdq, 3);
    SMAV(ncp_phy_CFG_SYSMEM_PHY_DPIOVREFSET_r_t, odtimpdqs, 3);
    SMAV(ncp_phy_CFG_SYSMEM_PHY_DPIOVREFSET_r_t, odtimpdm, 3);

    /* now set the value from the user configuration */
    value = parms->per_mem[memId].phy_dp_io_vref_set;

    ncr_modify32(region, NCP_PHY_CFG_SYSMEM_PHY_DPIOVREFSET, mask, value);

    /* check the PHY status */
    ncpStatus = ncp_sm_lsiphy_status_check(dev, smId, parms);

NCP_RETURN_LABEL
    return ncpStatus;
}



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
    ncp_st_t        st;

    int i;
    ncp_uint32_t mask, value;
    ncp_uint32_t offset = 0;


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
    ncr_modify32( ctlRegion, NCP_DENALI_CTL_21, mask, value );

    switch (mode) {
        case NCP_SYSMEM_PHY_WRITE_LEVELING:
            NCP_COMMENT("Sysmem %d PHY write leveling rank %d", smId, rank);
            
            mask = value = 0;
            SMAV( ncp_denali_DENALI_CTL_231_t, wrlvl_en, 1 );
            ncr_modify32( ctlRegion, NCP_DENALI_CTL_231, mask, value );

            mask = value = 0;
            SMAV( ncp_denali_DENALI_CTL_15_t, wrlvl_req, 1 );
            offset = NCP_DENALI_CTL_15;

            break;

        case NCP_SYSMEM_PHY_GATE_TRAINING:
            NCP_COMMENT("Sysmem %d PHY gate training rank %d ", smId, rank);

            mask = value = 0;
            SMAV( ncp_denali_DENALI_CTL_08_t, rdlvl_gate_en, 1 );
            ncr_modify32( ctlRegion, NCP_DENALI_CTL_08, mask, value );

            mask = value = 0;
            SMAV( ncp_denali_DENALI_CTL_08_t, rdlvl_gate_req, 1 );
            offset = NCP_DENALI_CTL_08;

            break;

        case NCP_SYSMEM_PHY_READ_LEVELING:
            NCP_COMMENT("Sysmem %d PHY read leveling rank %d %s edge", smId, rank, (edge == 0) ? "pos" : "neg");

            mask = value = 0;
            SMAV( ncp_denali_DENALI_CTL_08_t, rdlvl_en, 1 );
            ncr_modify32( ctlRegion, NCP_DENALI_CTL_08, mask, value );

            mask = value = 0;
            SMAV( ncp_denali_DENALI_CTL_11_t, rdlvl_req, 1 );
            offset = NCP_DENALI_CTL_11;

            break;

        default:
            NCP_COMMENT("unexpected PHY training mode %d !", mode);
    }

    /*
     * initiate the training operation using the offset,
     * mask and value set above for this training mode.
     */
    ncr_modify32( ctlRegion, offset, mask, value );


    /* poll for leveling operation complete */

    if ( NCP_ST_SUCCESS != (pollControllerFn(dev, ctlRegion, NCP_SM_LVL_OP_DONE)))
    {
        /* shouldn't happen */
        NCP_CALL(NCP_ST_SYSMEM_PHY_TRAIN_TIMEOUT);
    }

    /* check the PHY status */
    if (mode != NCP_SYSMEM_PHY_GATE_TRAINING)
    {
        NCP_CALL(ncp_sm_lsiphy_status_check(dev, smId, parms));
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
        for (i = 0; i < parms->num_bytelanes; i++) 
        {
            ncr_modify32( phyRegion, NCP_PHY_CFG_SYSMEM_PHY_DP_CONFIG2_BL(i), mask, value );
        }

    }

NCP_RETURN_LABEL
    /* reset training enables */
    st = ncpStatus;
    mask = value = 0;
    SMAV( ncp_denali_DENALI_CTL_08_t, rdlvl_gate_en, 0 );
    SMAV( ncp_denali_DENALI_CTL_08_t, rdlvl_en, 0 );
    ncr_modify32( ctlRegion, NCP_DENALI_CTL_08, mask, value );

    mask = value = 0;
    SMAV( ncp_denali_DENALI_CTL_231_t, wrlvl_en, 0 );
    ncr_modify32( ctlRegion, NCP_DENALI_CTL_231, mask, value );


    return st;
}

#ifdef NCP_CONFIG_CMEM

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
    ncp_uint32_t    mask, value ;

    ncp_ddr_CFG_NTEMC_MRS_r_t mrs = {0};
    ncp_ddr_CFG_NTEMC_DDR_STATUS_r_t ddr_status = {0};
    ncp_uint32_t cmemId = smId - NCP_SYSMEM_NUM_NODES;

    /* clear any previous operation */
    mask = value = 0;
    SMAV(ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t, rd_gate_lvl, 0);
    SMAV(ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t, wrt_lvl,     0);
    SMAV(ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t, rd_lvl,      0);
    SMAV(ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t, lvl_rsp,     1);
    SMAV(ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t, ref_ena,     0);
    ncr_modify32(ctlRegion, NCP_DDR_CFG_NTEMC_DDR_CTRL, mask, value);

    switch (mode) {
        case NCP_SYSMEM_PHY_GATE_TRAINING:
            NCP_COMMENT("Treemem %d PHY gate training rank %d", 
                                cmemId, rank);

            /* MRS MPR operation - enables training functionality in DRAM */
            mrs.mrs_adr  = 4;
            mrs.mrs_badr = 3;
            mrs.mrs_cmd  = 0;
            mrs.mrs_cke  = 1;
            ncr_write32(ctlRegion, NCP_DDR_CFG_NTEMC_MRS, 
                                  *(ncp_uint32_t *) &mrs);

            /* issue MRS command */
            ncr_write32( ctlRegion, NCP_DDR_CFG_NTEMC_ISSUE_MRS, 1);

            /* initiate gate training */
            mask = value = 0;
            SMAV(ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t, rd_gate_lvl, 1);
            SMAV(ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t, lvl_rsp,     0);
            SMAV(ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t, odt_mode,    3);
            ncr_modify32(ctlRegion, NCP_DDR_CFG_NTEMC_DDR_CTRL, mask, value);

            /* poll for completion */
            ddr_status.rdgtlvldone = 1;
            ncr_poll( ctlRegion, NCP_DDR_CFG_NTEMC_DDR_STATUS,
                                *(ncp_uint32_t *) &ddr_status,
                                *(ncp_uint32_t *) &ddr_status,
                                1, 100);

            /* 
             * check rdgtlvlstat to make sure training completed satisfactorily 
             * we use ncp_poll so that this will succeed on FBRS as well 
             */ 
            ddr_status.rdgtlvlstat = 1;
            ncr_poll ( ctlRegion, NCP_DDR_CFG_NTEMC_DDR_STATUS,
                                *(ncp_uint32_t *) &ddr_status,
                                *(ncp_uint32_t *) &ddr_status,
                                1, 2);


            /* MRS normal operation */
            mrs.mrs_adr  = 0;
            ncr_write32( ctlRegion, NCP_DDR_CFG_NTEMC_MRS, 
                                  *(ncp_uint32_t *) &mrs);

            /* issue MRS command */
            ncr_write32( ctlRegion, NCP_DDR_CFG_NTEMC_ISSUE_MRS, 1);


            break;

        case NCP_SYSMEM_PHY_WRITE_LEVELING:
            NCP_COMMENT("Treemem %d PHY write leveling rank %d", 
                            cmemId, rank);

            /* MRS operation */
            mrs.mrs_adr  = parms->cmemMR1[cmemId] | 0x80 ;
            mrs.mrs_badr = 1;
            mrs.mrs_cmd  = 0;
            mrs.mrs_cke  = 1;
            ncr_write32( ctlRegion, NCP_DDR_CFG_NTEMC_MRS, 
                                  *(ncp_uint32_t *) &mrs);

            /* issue MRS command */
            ncr_write32( ctlRegion, NCP_DDR_CFG_NTEMC_ISSUE_MRS, 1);

            /* initiate write leveling */
            mask = value = 0;
            SMAV(ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t, wrt_lvl,     1);
            SMAV(ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t, lvl_rsp,     0);
            SMAV(ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t, odt_mode,    1);
            ncr_modify32(ctlRegion, NCP_DDR_CFG_NTEMC_DDR_CTRL, mask, value);


            /* poll for completion */
            ddr_status.wrlvldone = 1;
            ncr_poll ( ctlRegion, NCP_DDR_CFG_NTEMC_DDR_STATUS,
                                *(ncp_uint32_t *) &ddr_status,
                                *(ncp_uint32_t *) &ddr_status,
                                1, 100);

            /* 
             * check rdgtlvlstat to make sure training completed satisfactorily 
             * we use ncp_poll so that this will succeed on FBRS as well 
             */ 
            ddr_status.wrlvlstat = 1;
            ncr_poll( ctlRegion, NCP_DDR_CFG_NTEMC_DDR_STATUS,
                                *(ncp_uint32_t *) &ddr_status,
                                *(ncp_uint32_t *) &ddr_status,
                                1, 2);

            /* disable write leveling */
            mrs.mrs_adr  = parms->cmemMR1[cmemId];
            ncr_write32( ctlRegion, NCP_DDR_CFG_NTEMC_MRS, 
                                  *(ncp_uint32_t *) &mrs);

            /* issue MRS command */
            ncr_write32( ctlRegion, NCP_DDR_CFG_NTEMC_ISSUE_MRS, 1);



            break;


        case NCP_SYSMEM_PHY_READ_LEVELING:
            NCP_COMMENT("Treemem %d PHY read leveling rank %d %s edge", 
                            cmemId, rank,
                            (edge == 0) ? "pos" : "neg" );

            /* MRS operation */
            mrs.mrs_adr  = 4;
            mrs.mrs_badr = 3;
            mrs.mrs_cmd  = 0;
            mrs.mrs_cke  = 1;
            ncr_write32( ctlRegion, NCP_DDR_CFG_NTEMC_MRS, 
                                  *(ncp_uint32_t *) &mrs);

            /* issue MRS command */
            ncr_write32( ctlRegion, NCP_DDR_CFG_NTEMC_ISSUE_MRS, 1);

            /* initiate read leveling */
            mask = value = 0;
            SMAV(ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t, rd_lvl,      1);
            SMAV(ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t, lvl_edge,    edge);
            SMAV(ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t, lvl_rsp,     0);
            SMAV(ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t, odt_mode,    3);
            ncr_modify32(ctlRegion, NCP_DDR_CFG_NTEMC_DDR_CTRL, mask, value);


            /* poll for completion */
            ddr_status.rdlvldone = 1;
            ncr_poll( ctlRegion, NCP_DDR_CFG_NTEMC_DDR_STATUS,
                                *(ncp_uint32_t *) &ddr_status,
                                *(ncp_uint32_t *) &ddr_status,
                                1, 100);

            /* 
             * check rdgtlvlstat to make sure training completed satisfactorily 
             * we use ncp_poll so that this will succeed on FBRS as well 
             */ 
            ddr_status.rdlvlstat = 1;
            ncr_poll( ctlRegion, NCP_DDR_CFG_NTEMC_DDR_STATUS,
                                *(ncp_uint32_t *) &ddr_status,
                                *(ncp_uint32_t *) &ddr_status,
                                1, 2);

            /* disable read leveling */
            mrs.mrs_adr  = 0;
            ncr_write32( ctlRegion, NCP_DDR_CFG_NTEMC_MRS, 
                                  *(ncp_uint32_t *) &mrs);

            /* issue MRS command */
            ncr_write32( ctlRegion, NCP_DDR_CFG_NTEMC_ISSUE_MRS, 1);



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
#endif /* not NCP_CONFIG_CMEM */

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

#ifdef NCP_CONFIG_CMEM
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

    ncpStatus = (trnFn(dev, smId, ctlRegion, phyRegion, rank, edge, mode, parms));

    if (ncpStatus != NCP_ST_SUCCESS) 
    {
        printf("trnFn failed! rank=%d, mode=%d, edge=%d\n", rank, mode, edge);
    }


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
    int                     i;
    ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG3_BLx_r_t  *phyconfig3 = (ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG3_BLx_r_t *) &value;
    ncp_uint32_t busAdaptor = 0;

#ifndef UBOOT
    /* get the driver bus adaptor */
    NCP_CALL(ncp_dev_read32(dev, NCP_REGION_DRIVER_CFG, NCP_DEV_CFG_BUS_ADAPTOR, &busAdaptor));
#endif

    switch (smId) {
        case 0:
        case 1:
            ctlRegion = NCP_REGION_ID(sm_nodes[smId], NCP_SYSMEM_TGT_DENALI);
            phyRegion = NCP_REGION_ID(sm_nodes[smId], NCP_SYSMEM_TGT_PHY);
            trnFn = ncp_sm_sysmem_phy_training_run;
            break;

#ifdef NCP_CONFIG_CMEM
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

    /* disable read path */
    mask = value = 0;
    SMAV( ncp_phy_CFG_SYSMEM_PHY_DPCONFIG2_BLx_r_t, enardpath, 0 );
    for (i = 0; i < parms->num_bytelanes; i++) 
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

        for (i = 0; i < parms->num_bytelanes; i++)
        {
            bl_stat = (ncp_uint32_t) gt_stat & 0xf;
            if (bl_stat == 0) 
            {
                /* 
                 * This bytelane passed! 
                 * Check the gate delay, if it's greater than two cycles 
                 * we'll increment RLGATE again. Otherwise we've found 
                 * the 'optimal' RLGATE so we disable this bytelane from
                 * further training. 
                 *
                 * bits [12:11] is the single cycle delay, so if bit 12 
                 * is set we've got two or more cycles of delay 
                 *
                 * We only do this for rank0. For rank1 we'll use the 
                 * RLGATE values we got for rank0, and as long as it 
                 * works we don't try to restrict the gate delays.
                 */

                if (rank == 0) {
                    ncr_read32( phyRegion, 
                        NCP_PHY_CFG_SYSMEM_PHY_GTUPPCTRL_BL_CS(i, rank), &value);
                    if ( (value & 0x00001000) )
                    {
                        /* indicate this bytelane failed */
                        bl_stat = 0xf;
                    }
                } 
            }

            if (bl_stat == 0) 
            {
                /* this bytelane still passed! disable it */
                dp_en &= ~(1 << i);
            } 
            else 
            {
                /* this bytelane failed! try incrememnting rlgate */
                if (rank != 0)  {
                    NCP_CALL(NCP_ST_SYSMEM_PHY_GT_TRN_ERR);
                }


                ncr_read32(phyRegion, 
                        NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG3_BL(i), &value);

                phyconfig3->rdlatrank += 1;
                phyconfig3->rdlatgate += 1;
                if (phyconfig3->rdlatgate >= 31)
                {
                    NCP_CALL(NCP_ST_SYSMEM_PHY_GT_TRN_ERR);
                }

                ncr_write32(phyRegion, 
                        NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG3_BL(i), value);
            }

            gt_stat >>= 4;
        }

        /* disable successful bytelanes */
        value = (phyconfig2 & 0xffe00fff) | (dp_en << 12);
        ncr_write32(phyRegion, NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG2, value);

        if (busAdaptor == NCP_DEV_BUS_FBRS) 
	    break;
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
        for (i = 0; i < parms->num_bytelanes; i++) 
        {
            ncr_modify32( phyRegion, NCP_PHY_CFG_SYSMEM_PHY_DP_CONFIG2_BL(i), mask, value );
        }
    }


    return ncpStatus;
}


#ifdef NCP_SM_WRLVL_DUP
/* 
 *  copy a set of write levling registers
 *  from one rank to another
 */
ncp_st_t
ncp_sm_lsiphy_wrlvl_dup(
        ncp_dev_hdl_t               dev,
        ncp_uint32_t                smId,
        ncp_uint32_t                srcRank,
        ncp_uint32_t                destRank)
{

    ncp_st_t                ncpStatus = NCP_ST_SUCCESS;
    ncp_region_id_t         phyRegion;
    ncp_uint32_t            value;
    ncp_uint32_t            from, to;
    int i;


    phyRegion = NCP_REGION_ID(sm_nodes[smId], NCP_SYSMEM_TGT_PHY);

    /* 
     * copy WRTLVLUPP/LOW
     */
    for ( i = 0; i < 5; i++) 
    {
        ncr_read32(phyRegion,
                        NCP_PHY_CFG_SYSMEM_PHY_WRTLVLUPP_BL_CS(i, srcRank),
                        &value);
        ncr_write32(phyRegion,
                        NCP_PHY_CFG_SYSMEM_PHY_WRTLVLUPP_BL_CS(i, destRank),
                        value);

        ncr_read32(phyRegion,
                        NCP_PHY_CFG_SYSMEM_PHY_WRTLVLLOW_BL_CS(i, srcRank),
                        &value);
        ncr_write32(phyRegion,
                        NCP_PHY_CFG_SYSMEM_PHY_WRTLVLLOW_BL_CS(i, destRank),
                        value);
    }

    /*
     * copy WRTALIGNDQ 
     */
    for (i = 0; i < 5; i++) {
        from = 0x18000 + (srcRank  * 0x100) + (i * 0x800) ;
        to   = 0x18024 + (destRank * 0x100) + (i * 0x800) ;

        /* lower nibble */
        ncr_read32 (phyRegion, from,  &value);
        ncr_write32(phyRegion, to,     value);

        /* upper nibble */
        from += 0x10;
        to   += 0x08;
        ncr_read32 (phyRegion, from,  &value);
        ncr_write32(phyRegion, to,     value);
    }


NCP_RETURN_LABEL
    if (ncpStatus == NCP_ST_SUCCESS)
    {
    }

    return ncpStatus;
}
#endif



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

typedef ncp_st_t 
(*ncp_sm_bytelane_test_fn_t) (
    ncp_dev_hdl_t dev, 
    ncp_uint32_t  node, 
    ncp_uint64_t  address, 
    ncp_uint32_t  pattern, 
    ncp_uint32_t *bad_bl, 
    ncp_uint32_t  num_bls);

typedef ncp_st_t
(*ncp_sm_ecc_bytelane_test_fn_t) (
        ncp_dev_hdl_t dev, 
        ncp_uint32_t ctrlRegion, 
        ncp_uint64_t address,
        ncp_uint32_t node,  
        ncp_uint32_t pattern, 
        ncp_uint32_t ecc_mask,
        ncp_uint32_t  num_bls,
        ncp_uint32_t *bad_bl);


static ncp_st_t
sm_bytelane_test(
    ncp_dev_hdl_t dev, 
    ncp_uint32_t  notUsed, 
    ncp_uint64_t  address, 
    ncp_uint32_t  pattern, 
    ncp_uint32_t *bad_bl, 
    ncp_uint32_t  num_bls)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    int i;
    int j;
    ncp_uint32_t  value32 = 0x01010101UL;
    ncp_uint8_t   compare_value;
#ifdef SM_BYTELANE_TEST_DEBUG
    ncp_uint32_t  offset = num_bls * 2;
#endif
    ncp_uint32_t  *pTmp;

    ncp_uint32_t  burstSize;
    ncp_uint32_t  blockSize;
    ncp_uint32_t  cmpOff; 

#ifdef UBOOT
    ncp_uint32_t  *p32 = (unsigned *)(NCA + 0x1000);
    ncp_uint8_t   *p8 = (unsigned char *)(NCA + 0x1000);
    unsigned uppAddr;
    unsigned lowAddr;
#else
    ncp_uint8_t   wbuf[NCP_SM_BURST_SIZE];
    ncp_uint8_t   rbuf[NCP_SM_BURST_SIZE];
    ncp_uint32_t  *p32 = (ncp_uint32_t *) wbuf;
    ncp_uint8_t   *p8 = &rbuf[0x00];
#endif

    /*
     * calculate the block size for this test. 
     * One DDR burst is 8 beats, or 8 bytes per bytelane.
     * We will write two bursts, read two bursts, and compare
     * the data from the middle of the second burst.
     */
    burstSize = num_bls * 8;
    blockSize = burstSize * 2; 
    cmpOff    = burstSize + (burstSize / 2);
    p8       += cmpOff;

    /* Build buffer */
    pTmp = p32;
    for (i = 0; i < (blockSize / num_bls); ++i) {
        unsigned long temp;

        if (0 == pattern)
            temp = value32;
        else
            temp = ~value32;

        *pTmp++ = temp;

        NCR_TRACE("ncpWrite  -w8 0.512.1.0x00%012llx " \
              "0x%02x 0x%02x 0x%02x 0x%02x\n",
              (address + (num_bls * i)),
              (unsigned char )((temp & 0xff000000) >> 24),
              (unsigned char )((temp & 0x00ff0000) >> 16),
              (unsigned char )((temp & 0x0000ff00) >>  8),
              (unsigned char )(temp & 0x000000ff));

        if (num_bls == 8) {
            *pTmp++ = temp;
            NCR_TRACE("ncpWrite  -w8 0.512.1.0x00%012llx " \
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
        int idx;

        pTmp = p32;
        for (idx = 0; idx < (blockSize / 4); ++idx) {
            printf("<%03d:0x%08x>", (idx * 4), *pTmp++);
        }

        printf("\n");
    }
#endif

    /* write it out and save the comparison value from the write buffer*/
#ifdef UBOOT
    uppAddr = ( (unsigned) (address >> 32) );
    lowAddr = ( (unsigned) (address & 0xffffffff) );

    if (0 != ncr_write( NCP_REGION_ID( 512, 1 ), uppAddr, lowAddr, blockSize, NULL )) {
      printf("%d : ncr_write() failed: 0x%08x 0x%08x\n",
         __LINE__, in_be32(NCA + 0xe4), in_be32(NCA + 0xe8));
      return -1;
    }
    compare_value = *p8;
#else 

    NCP_CALL(ncp_block_write8(dev, NCP_REGION_NCA_NIC_SYSMEM, address, 
                                wbuf, blockSize, 0));

    compare_value = wbuf[cmpOff];
#endif

    if (0 != (pattern & 0x2))
        return NCP_ST_SUCCESS;

    /* Read back and compare. */
#ifdef UBOOT
    if (0 != ncr_read( NCP_REGION_ID( 512, 1 ), uppAddr, lowAddr, blockSize, NULL )) {
      printf("%d : ncr_read() failed: 0x%08x 0x%08x\n",
         __LINE__, in_be32(NCA + 0xe4), in_be32(NCA + 0xe8));
    }
    NCR_TRACE("ncpRead   -w8 0.512.1.0x00%012llx 128\n", address);
    pTmp = p32;
#else 
    NCP_CALL(ncp_block_read8(dev, NCP_REGION_NCA_NIC_SYSMEM, address, 
                                rbuf, blockSize, 0));
    
    pTmp = (ncp_uint32_t *) rbuf;
#endif

#ifdef SM_BYTELANE_TEST_DEBUG
    {
        for (i = 0; i < (blockSize / 4); ++i) {
            printf("(%03d:0x%08x)", (i * 4), *pTmp++);
        }
        printf("\n");
    }
#endif


    *bad_bl = 0;
    j = 0;

    if (0 == (pattern & 0x4)) 
    {

        /* TODO!! FIXME!! check multiple bursts!! */
        for (i = 0; i < num_bls; ++i) {

#ifdef SM_BYTELANE_TEST_DEBUG
        printf("i=%d j=%d expect=0x%02x "
               "p8=0x%p/0x%02x/0x%02x/0x%02x\n",
               i, j, compare_value, p8, *p8, *(p8 - offset),
               *(p8 + offset));
#endif

            if (compare_value != *p8) {
                *bad_bl |= 1 << i;
            }
    
            ++p8;
            ++j;
        }
    } else {
#ifndef UBOOT
        if (memcmp(rbuf, wbuf, blockSize)) {
            *bad_bl = 0x1ff;
        }
#else
    value32 = 0x01010101UL;
    pTmp = p32;

    for (i = 0; i < (blockSize / num_bls); ++i) {
      unsigned temp;

      if (0 == pattern)
        temp = value32;
      else
        temp = ~value32;

      if (*p32 != temp) {
        printf("\nCompare Failed! i=%d temp=0x%x *p32=0x%x",
           i, temp, *p32);
        *bad_bl = 0x1ff;
      }

      ++p32;

      if (8 == num_bls) {
        if (*p32 != temp) {
          printf("\nCompare 2 Failed! i=%d temp=0x%x *p32=0x%x",
             i, temp, *p32);
          *bad_bl = 0x1ff;
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
    printf("*bad_bl=0x%x \n", *bad_bl);
#endif

NCP_RETURN_LABEL
    return ncpStatus;
}

/*
  ------------------------------------------------------------------------------
  sm_ecc_bytelane_test
*/

/* #define SM_ECC_BYTELANE_TEST_DEBUG */

#include "ncp_sm_ecc_test_buffer.h"

static ncp_st_t
sm_ecc_bytelane_test(
        ncp_dev_hdl_t dev, 
        ncp_uint32_t ctrlRegion, 
        ncp_uint64_t address,
        ncp_uint32_t node,  
        ncp_uint32_t pattern, 
        ncp_uint32_t ecc_mask,
        ncp_uint32_t  num_bls,
        ncp_uint32_t *bad_bl)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_uint32_t value;
    ncp_uint32_t this_value;
    ncp_uint32_t temp;
#ifdef UBOOT 
    ncp_uint32_t  *p32 = (ncp_uint32_t *)(NCA + 0x1000); 
    unsigned uppAddr;
    unsigned lowAddr;
#else 
    ncp_uint8_t   wbuf[NCP_SM_BURST_SIZE];
    ncp_uint8_t   rbuf[NCP_SM_BURST_SIZE];
    ncp_uint32_t  *p32 = (ncp_uint32_t *) wbuf;
#endif

    ncp_uint32_t  burstSize = num_bls * 8;
    ncp_uint32_t  blockSize = burstSize * 2; 
    ncp_uint32_t  blockSizeWords = blockSize / 4;

    int i;
    int rc;

    /* clear ECC interrupt status bits */
    intrStatFn(dev, ctrlRegion, ecc_mask);


    /* copy the ECC test data buffer */        
    for (i = 0; i < blockSizeWords ; i++) {

        this_value = ecc_test_data_64bit[pattern][i];
        *p32++ = this_value;
        NCR_TRACE("ncpWrite  -w8 0.512.1.0x00%012llx " \
              "0x%02x 0x%02x 0x%02x 0x%02x\n",
              (address + (i * 4) ),
              (unsigned char )((this_value & 0xff000000) >> 24),
              (unsigned char )((this_value & 0x00ff0000) >> 16),
              (unsigned char )((this_value & 0x0000ff00) >>  8),
              (unsigned char )(this_value & 0x000000ff));

    }

    /* write it out */
#ifdef UBOOT 
    uppAddr = ( (unsigned) (address >> 32) );
    lowAddr = ( (unsigned) (address & 0xffffffff) );

    if (0 != ncr_write( NCP_REGION_ID( 512, 1 ), uppAddr, lowAddr, blockSize, NULL )) {
      printf("%d : ncr_write() failed!\n", __LINE__);
      return -1;
    }
    p32 = (ncp_uint32_t *)(NCA + 0x1000); 
#else 
    p32 = (ncp_uint32_t *)wbuf;
    NCP_CALL(ncp_block_write32(dev, NCP_REGION_NCA_NIC_SYSMEM, address, 
                                p32, blockSizeWords, 0));
#endif

#ifdef SM_ECC_BYTELANE_TEST_DEBUG
    {
        int idx;

        for (idx = 0; idx < (blockSizeWords); ++idx) {
            printf("<%03d:0x%08x>", (idx * 4), p32[idx]);
        }

        printf("\n");
    }
#endif /* SM_ECC_BYTELANE_TEST_DEBUG */

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
    uppAddr = ( (unsigned) ((address >> 2)  >> 32) );
    lowAddr = ( (unsigned) ((address >> 2)  & 0xffffffff) );
        rc = ncr_read( NCP_REGION_ID( node, 5 ), uppAddr, lowAddr, blockSizeWords, NULL );

    if (-1 == rc)
        rc = in_be32(NCA + 0xe4);

    NCR_TRACE( "ncpRead    0.%u.5.0x%010llx 32\n", node, (address >> 2) );
    p32 = (ncp_uint32_t *)(NCA + 0x1000); 
#else
    rc = ncp_block_read32(dev, NCP_REGION_ID(node, 5), (address >> 2), 
                                (ncp_uint32_t *)rbuf, blockSizeWords, 0);

    p32 = (ncp_uint32_t *)rbuf;
#endif

#ifdef SM_ECC_BYTELANE_TEST_DEBUG
    {
        int idx;

        for (idx = 0; idx < (blockSizeWords); ++idx) {
            printf("(%03d:0x%08x)", (idx * 4), p32[idx]);
        }

        printf("\n");
    }
#endif /* SM_ECC_BYTELANE_TEST_DEBUG */

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

        for (i = 0; i < blockSizeWords ; i++) {
            temp = *((unsigned long *)(NCA + 0x1000 + (i * 4)));
            if (temp != ecc_test_data_64bit[pattern][i]) {
                rc = 0x1ff;
            }
        }
#else
        /* Read back and compare. */
        if (memcmp(rbuf, wbuf, blockSize)) 
        {
#if 0
            int i;
            ncp_uint32_t *pr = (ncp_uint32_t *) rbuf;
            ncp_uint32_t *pw = (ncp_uint32_t *) wbuf;
            printf("memcmp failed!\n");

            for ( i = 0; i < blockSizeWords; i++) {
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
    value = intrStatFn(dev, ctrlRegion, ecc_mask);

    if (0 != value) {
        *bad_bl = 0x100;
    } else if (0 != rc) {
        *bad_bl = 0x1ff;
    }

NCP_RETURN_LABEL
    return ncpStatus;
}


#define NCP_BLTEST_NUM_CHECKS 8

#ifdef NCP_CONFIG_ELM
/*
 *------------------------------------------------------------------------------
 *  sm_bytelane_test_elm
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

static ncp_st_t
sm_bytelane_test_elm(
    ncp_dev_hdl_t dev, 
    ncp_uint32_t  elmNode, 
    ncp_uint64_t  address, 
    ncp_uint32_t  pattern, 
    ncp_uint32_t *bad_bl,
    ncp_uint32_t  num_bls)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    int i, j;

#ifdef SM_BYTELANE_TEST_DEBUG
#ifdef UBOOT 
    ncp_uint32_t  *p32 = (ncp_uint32_t *) (NCA + 0x1000); 
    unsigned uppAddr;
    unsigned lowAddr;
#else 
    ncp_uint8_t   rbuf[NCP_SM_BURST_SIZE];
    ncp_uint32_t  *p32 = (ncp_uint32_t *) rbuf;
#endif
#endif

    ncp_region_id_t elmRegion = NCP_REGION_ID(elmNode, 0);
    ncp_uint32_t  burstSize;
    ncp_uint32_t  blockSize;

    ncp_uint32_t  expValOffset;
    ncp_uint8_t  expVal;
    ncp_uint8_t  readVal;
    ncp_int32_t   valAdj;

    ncp_uint32_t  readData[2];
    ncp_uint8_t  *pDat;

    ncp_elm_sysmem_write_level_ctl_r_t wl_ctl = {0};

    /*
     * calculate the block size for this test.
     * One DDR burst is 8 beats, or 8 bytes per bytelane.
     * We will write two bursts, read two bursts, and compare
     * the data from the middle of the second burst.
     */
    burstSize = num_bls * 8;
    blockSize = burstSize * 2;

    /*
     * We add or subtract an adjustment factor equal to the
     * beat size to get the value for the previous and subsequent
     * beat.
     */
    if ( (pattern & 0x01) == 0) {
        valAdj  = 1;
    } 
    else
    {
        valAdj  = -1;
    }

    /* 
     * the ELM sysmem init cache address register specifies
     * the 64-byte cacheline, so we write the address shifted
     * by 6 bits.
     */
#ifdef SM_BYTELANE_TEST_DEBUG
    printf("ELM writing pattern %d to address %012llx\n", (pattern & 0x1), address);
#endif

    ncr_write32( elmRegion, NCP_ELM_SYSMEM_INIT_CACHE_ADDR, (address >> 6));

    /*
     * the ELM sysmem init cache line count registers specifies
     * the number of 64-byte cachelines to be written. A value
     * of zero indicates one cacheline.
     */
    ncr_write32( elmRegion, NCP_ELM_SYSMEM_INIT_CACHE_COUNT, ((blockSize/64) - 1)); 
     

    /*
     * write pattern into memory
     */
    wl_ctl.set_wl_pattern = 1;
    wl_ctl.invert_wl_pattern = (pattern & 0x01);
    ncr_write32( elmRegion, NCP_ELM_SYSMEM_WRITE_LEVEL_CTL, *(ncp_uint32_t *)&wl_ctl);

    /* this initiates the write */
    ncr_write32( elmRegion, NCP_ELM_SYSMEM_INIT_DATA, 0);

    /* always wait for the ELM to complete the write */
    if (0 != ncr_poll(elmRegion, 0x1000, 0x80, 0x80, 10, 10) )
    {
        /* shouldn't happen */
        NCP_CALL(NCP_ST_ERROR);
    }
    ncr_write32(elmRegion, 0x1000, 0x00000080);

    /* if we're not doing the readback and compare just return */
    if (0 != (pattern & 0x2))
        return 0;

    *bad_bl = 0;

    for (j = 0; j < NCP_BLTEST_NUM_CHECKS; j++)
    {
        /*
         * The write data is either an incrementing byte pattern
         * starting from 0, or a decrementing byte pattern starting
         * from 0xff. For the incrementing pattern the expected
         * value for the byte at offset 'n' will be 'n', and for
         * the decrementing pattern it will be the complement.
         *
         */
        expValOffset  = burstSize + (j * burstSize / NCP_BLTEST_NUM_CHECKS);
        if ( (pattern & 0x01) == 0) {
            expVal  = expValOffset;
        }
        else
        {
            expVal  = -expValOffset;
            expVal -= 1;
        }

#ifdef SM_BYTELANE_TEST_DEBUG
        printf("checking data at offset 0x%04x\n", expValOffset);
#endif

        /* Read back and compare. */
        ncr_write32( elmRegion, NCP_ELM_SYSMEM_INIT_CACHE_ADDR, ((address + expValOffset) >> 6));
        wl_ctl.set_wl_pattern = 0;
        wl_ctl.data_selector  = expValOffset / 8;
        ncr_write32( elmRegion, NCP_ELM_SYSMEM_WRITE_LEVEL_CTL, *(ncp_uint32_t *)&wl_ctl);


        /*
         * this initiates the memory block read and the read response
         * for the selected beat of data is stored in these registers
         */
        ncr_read32(elmRegion, NCP_ELM_SYSMEM_WRITE_LEVEL_READ_0, &readData[0]);
        ncr_read32(elmRegion, NCP_ELM_SYSMEM_WRITE_LEVEL_READ_1, &readData[1]);


        readData[0] = NCP_SM_SWAP32(readData[0]);
        readData[1] = NCP_SM_SWAP32(readData[1]);

        pDat = (ncp_uint8_t *) &readData[0];

        for (i = 0; i < num_bls; ++i) {
            readVal = pDat[i];
#ifdef SM_BYTELANE_TEST_DEBUG
            printf("readVal=%02x, expVal=%02x\n",
                readVal, expVal);
#endif
            if (readVal != expVal)
            {
                    *bad_bl |= 1 << i;
            }
            expVal += valAdj;
        }
    }



#ifdef SM_BYTELANE_TEST_DEBUG
    printf("*bad_bl=0x%x \n", *bad_bl);

    printf("NCA reading address %012llx\n", address);
#ifdef UBOOT 
    uppAddr = ( (unsigned) (address >> 32) );
    lowAddr = ( (unsigned) (address & 0xffffffff) );

    if (0 != ncr_read( NCP_REGION_ID( 512, 1 ), uppAddr, lowAddr, blockSize, NULL )) {
      printf("%d : ncr_write() failed!\n", __LINE__);
      return -1;
    }
    p32 = (ncp_uint32_t *) (NCA + 0x1000); 
#else 
    NCP_CALL(ncp_block_read8(dev, NCP_REGION_NCA_NIC_SYSMEM, address, 
                                rbuf, blockSize, 0));
    p32 = (ncp_uint32_t *)rbuf;
#endif
    {
        int idx;

        for (idx = 0; idx < (blockSize/4); ++idx) {
            printf("(%03x:0x%08x)", (idx * 4), p32[idx]);
            if ( (idx & 0x3) == 3) printf("\n");
        }

        printf("\n");
    }
#endif /* SM_BYTELANE_TEST_DEBUG */

NCP_RETURN_LABEL
    return 0;
}



static ncp_st_t use_elm(ncp_dev_hdl_t dev, int elm)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_uint32_t elm0_bits;
    ncp_uint32_t elm1_bits;
    
    switch (elm) {
        case 0: 
            elm0_bits = 4;
            elm1_bits = 4;
            break;
    
        case 1: 
            elm0_bits = 0xe;
            elm1_bits = 0xe;
            break;

        case 3:
        default:
            elm0_bits = 0x4;
            elm1_bits = 0xe;
            break;
    }

#ifndef UBOOT
    ncr_write32( NCP_REGION_ID(0x1e0, 0x20), 8, elm0_bits);
    ncr_write32( NCP_REGION_ID(0x1e0, 0x21), 8, elm0_bits);
    ncr_write32( NCP_REGION_ID(0x1e0, 0x22), 8, elm0_bits);
    ncr_write32( NCP_REGION_ID(0x1e0, 0x23), 8, elm0_bits);
    ncr_write32( NCP_REGION_ID(0x1e0, 0x24), 8, elm1_bits);
    ncr_write32( NCP_REGION_ID(0x1e0, 0x25), 8, elm1_bits);
    ncr_write32( NCP_REGION_ID(0x1e0, 0x26), 8, elm1_bits);
    ncr_write32( NCP_REGION_ID(0x1e0, 0x27), 8, elm1_bits);
#else
#ifndef AXM_35xx
    writel(elm0_bits, (DICKENS + 0x200008));
    writel(elm0_bits, (DICKENS + 0x210008));
    writel(elm0_bits, (DICKENS + 0x220008));
    writel(elm0_bits, (DICKENS + 0x230008));
    writel(elm1_bits, (DICKENS + 0x240008));
    writel(elm1_bits, (DICKENS + 0x250008));
    writel(elm1_bits, (DICKENS + 0x260008));
    writel(elm1_bits, (DICKENS + 0x270008));
#endif
#endif


    ncr_read32( NCP_REGION_ID(0x158, 0), 4, &elm0_bits);
    ncr_read32( NCP_REGION_ID(0x159, 0), 4, &elm1_bits);

    switch (elm) {
        case 0: 
        case 1: 
            /* clear 'two_elms' bit */
            elm0_bits &= 0xfffffdff;
            elm1_bits &= 0xfffffdff;

            break;

        case 3:
        default:
            /* set 'two_elms' bit */
            elm0_bits |= 0x00000200;
            elm1_bits |= 0x00000200;
            break;
    }

    ncr_write32( NCP_REGION_ID(0x158, 0), 4, elm0_bits);
    ncr_write32( NCP_REGION_ID(0x159, 0), 4, elm1_bits);

NCP_RETURN_LABEL
    return ncpStatus;
}





static ncp_st_t
sm_ecc_bytelane_test_elm(
        ncp_dev_hdl_t dev, 
        ncp_uint32_t ctrlRegion, 
        ncp_uint64_t address,
        ncp_uint32_t node,  
        ncp_uint32_t pattern, 
        ncp_uint32_t ecc_mask,
        ncp_uint32_t  num_bls,
        ncp_uint32_t *bad_bl)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_region_id_t elmRegion = NCP_REGION_ID(node, 0);
    ncp_uint32_t  eccErrs;
    ncp_uint32_t  elmStat;

    ncp_uint32_t this_value;
#ifdef UBOOT 
    ncp_uint32_t  *p32 = (ncp_uint32_t *)(NCA + 0x1000); 
    unsigned uppAddr;
    unsigned lowAddr;
#else 
    ncp_uint8_t   wbuf[NCP_SM_BURST_SIZE];
    ncp_uint32_t  *p32 = (ncp_uint32_t *) wbuf;
#endif

    ncp_uint32_t  expValOffset;
    ncp_uint32_t  expWdOffset;

    ncp_uint32_t  readData[2];

    ncp_elm_sysmem_write_level_ctl_r_t wl_ctl = {0};
    ncp_uint32_t  burstSize = num_bls * 8;
    ncp_uint32_t  blockSize = burstSize * 2; 
    ncp_uint32_t  blockSizeWords = blockSize / 4;

    int i;
    ncp_uint32_t tmp;

    /* clear ECC interrupt status bits */
    intrStatFn(dev, ctrlRegion, ecc_mask);

#ifdef SM_ECC_BYTELANE_TEST_DEBUG
    printf("ECC bytelane test  address 0x%012llx\n", address);

#endif

    /*
     * calculate the block size for this test. 
     * One DDR burst is 8 beats, or 8 bytes per bytelane.
     * We will write two bursts, read two bursts, and compare
     * the data from the middle of the second burst.
     */
    burstSize = num_bls * 8;
    blockSize = burstSize * 2; 

    /*
     * for ECC leveling we use a specially crafted data pattern
     * chosen to have unique ECC values for each beat.
     */
    expValOffset  = (burstSize + (burstSize / 2));
    expWdOffset   = expValOffset / 4;

    /* copy the ECC test data buffer */        
    for (i = 0; i < blockSizeWords ; i++) {

        this_value = ecc_test_data_64bit[pattern][i];
        *p32++ = this_value;
        NCR_TRACE("ncpWrite  -w8 0.512.1.0x00%012llx " \
              "0x%02x 0x%02x 0x%02x 0x%02x\n",
              (address + (i * 4) ),
              (unsigned char )((this_value & 0xff000000) >> 24),
              (unsigned char )((this_value & 0x00ff0000) >> 16),
              (unsigned char )((this_value & 0x0000ff00) >>  8),
              (unsigned char )(this_value & 0x000000ff));

    }

    /* write it out */
#ifdef UBOOT 
    uppAddr = ( (unsigned) (address >> 32) );
    lowAddr = ( (unsigned) (address & 0xffffffff) );

    if (0 != ncr_write( NCP_REGION_ID( 512, 1 ), uppAddr, lowAddr, blockSize, NULL )) {
      printf("%d : ncr_write() failed!\n", __LINE__);
      return -1;
    }
    p32 = (ncp_uint32_t *)(NCA + 0x1000); 
#else 
    NCP_CALL(ncp_block_write8(dev, NCP_REGION_NCA_NIC_SYSMEM, address, 
                                wbuf, blockSize, 0));
    p32 = (ncp_uint32_t *)wbuf;
#endif

#ifdef SM_ECC_BYTELANE_TEST_DEBUG
    {
        int idx;

        for (idx = 0; idx < (blockSizeWords); ++idx) {
            printf("<%03x:0x%08x>", (idx * 4), p32[idx]);
            if ( (idx & 0x3) == 3) printf("\n");
        }

        printf("\n");
    }
#endif /* SM_ECC_BYTELANE_TEST_DEBUG */

    /*
     * perform a sacrificial config ring read. 
     * This will guarantee that the preceedeing NCA SMBW
     * operation has completed before we attemp to read it back
     */
    ncr_read32(NCP_REGION_ID(0x16, 0xff), 0, &tmp);
    
    /* 
     * Read back and compare.
     * we read through the ELM in case the read fails due to bad ECC
     */
    ncr_write32( elmRegion, NCP_ELM_SYSMEM_INIT_CACHE_ADDR, 
                        ((address + expValOffset) >> 6));

    wl_ctl.set_wl_pattern = 0;
    wl_ctl.data_selector  = expValOffset / 8;
    ncr_write32( elmRegion, NCP_ELM_SYSMEM_WRITE_LEVEL_CTL, 
                            *(ncp_uint32_t *)&wl_ctl);

    /*
     * this initiates the memory block read and the read response
     * for the selected beat of data is stored in these registers
     */
    ncr_read32(elmRegion, NCP_ELM_SYSMEM_WRITE_LEVEL_READ_0, &readData[0]);
    ncr_read32(elmRegion, NCP_ELM_SYSMEM_WRITE_LEVEL_READ_1, &readData[1]);

    readData[0] = NCP_SM_SWAP32(readData[0]);
    readData[1] = NCP_SM_SWAP32(readData[1]);

#ifdef SM_ECC_BYTELANE_TEST_DEBUG
    printf("readData = 0x%08x 0x%08x\n", readData[0], readData[1]);
    printf("expData  = 0x%08x 0x%08x\n", 
                    ecc_test_data_64bit[pattern][expWdOffset], 
                    ecc_test_data_64bit[pattern][expWdOffset+1] );
#endif

    /* check for ECC errors */
    eccErrs = intrStatFn(dev, ctrlRegion, ecc_mask);


    if (eccErrs) {
        /* indicate bytelane failure */
        *bad_bl = 0x100;

#ifdef SM_ECC_BYTELANE_TEST_DEBUG
	{
	    ncp_uint32_t value;
        printf("eccErrs = 0x%08x\n", eccErrs);
        ncr_read32(ctrlRegion, 0xac, &value);
        printf("syndrome = 0x%08x\n", value);
        ncr_write32(ctrlRegion, 0xac, 0);
	}
#endif
    }


    /* check for ELM errors */
    ncr_read32(NCP_REGION_ID(node, 0), NCP_ELM_INTERRUPT_STATUS, &elmStat);

    if (elmStat & NCP_ELM_INTERRUPT_STATUS_ALARM_MASK) 
    {
        /* indicate bytelane failure */
        *bad_bl = 0x1ff;
#ifdef SM_ECC_BYTELANE_TEST_DEBUG
        printf("ECC coarse write leveling - elmStat = 0x%08x\n", elmStat);
#endif
    }
    ncr_write32(NCP_REGION_ID(node, 0), NCP_ELM_INTERRUPT_STATUS, elmStat);



    /* check for correct data */
    if (*bad_bl == 0) {
        if ((readData[0] != ecc_test_data_64bit[pattern][expWdOffset]) || 
            (readData[1] != ecc_test_data_64bit[pattern][expWdOffset+1]))
            {

                printf("ECC coarse write leveling data miscompare\n");
                printf("readData = 0x%08x 0x%08x\n", readData[0], readData[1]);
                printf("expData  = 0x%08x 0x%08x\n", 
                    ecc_test_data_64bit[pattern][expWdOffset], 
                    ecc_test_data_64bit[pattern][expWdOffset+1] );
            }
    }


NCP_RETURN_LABEL
        return ncpStatus;

}

#endif


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
    ncp_uint32_t    num_bls;

    ncp_uint32_t    mask, value;

    ncp_uint32_t    bad_bl = 0;

    ncp_uint32_t     node;   /* either SC (2500) or ELM (5500) */
    ncp_uint32_t    ecc_mask;

    ncp_uint8_t    bl;
    ncp_uint32_t    udly; 
    ncp_uint32_t    ldly; 
    ncp_uint8_t    nincs = 0;
    ncp_uint8_t    ndecs;
    int     adj;

    ncp_sm_bytelane_test_fn_t     bl_test_fn;
    ncp_sm_ecc_bytelane_test_fn_t ecc_bl_test_fn;
 
    ncp_uint32_t busAdaptor = 0;

#ifndef UBOOT
    /* get the driver bus adaptor */
    NCP_CALL(ncp_dev_read32(dev, NCP_REGION_DRIVER_CFG, 
                                 NCP_DEV_CFG_BUS_ADAPTOR, &busAdaptor));
#endif


    /* validate smId */
    switch (smId) {
        case 0:
        case 1:
            break;
        default:
            NCP_CALL(NCP_ST_SYSMEM_INVALID_ID);
    }

    NCP_COMMENT("sysmem phy coarse write leveling - rank %d, addr 0x%012llx",
            rank, addr);

#ifdef SM_BYTELANE_TEST_DEBUG
    printf("sysmem phy coarse write leveling - rank %d, addr 0x%012llx\n",
            rank, addr);
#endif

    switch (parms->version) 
    {
        case NCP_CHIP_ACP35xx:  /* TEMP - need to review support for 3500 */
            bl_test_fn = sm_bytelane_test;
            ecc_bl_test_fn = sm_ecc_bytelane_test;

            switch (rank) 
            {
                case 0: 
                    node = sc_nodes[0];
                    break;
                case 1: 
                    /* due to address hashing, if an odd bit is
                     * set in the address this write will end up 
                     * in syscache 2, if an even bit is set it 
                     * will end up in syscache 1. 
                     *
                     * NOTE! This assumes there is only one bit set in addr!! 
                     */
                    if (addr & 0xaaaaaaaa) {
                        node = sc_nodes[2];
                    } else {
                        node = sc_nodes[1];
                    }
                    break;
                default: 
                    NCP_CALL(NCP_ST_ERROR);
                }

            break;

#ifdef NCP_CONFIG_ELM
        case NCP_CHIP_ACP55xx:
            bl_test_fn = sm_bytelane_test_elm;
            ecc_bl_test_fn = sm_ecc_bytelane_test_elm;
            node = 0x158 + smId;    /* ELM node */

#ifndef UBOOT
            if (busAdaptor == NCP_DEV_BUS_FBRS) 
            {
                /* write expected values into write-level read registers */
                ncr_write32(NCP_REGION_ID(node, 0), 
                        NCP_ELM_SYSMEM_WRITE_LEVEL_READ_0, 0x63626160);
                ncr_write32(NCP_REGION_ID(node, 0), 
                        NCP_ELM_SYSMEM_WRITE_LEVEL_READ_1, 0x67666564);
            }
#endif

            break;
#endif

        default:
            /* unsupported chip */
            NCP_CALL(NCP_ST_ERROR);
    }

    /* number of data bytelanes (sans ECC) */
    num_bls = parms->num_bytelanes - 1;

    /* disable ECC */
    eccEnbFn(dev, ctlRegion, 0);

    /* ??? */
    mask = value = 0;
    SMAV(ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG1_r_t, bblclobber, 1); 
    SMAV(ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG1_r_t, wrranksw, 1); 
    SMAV(ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG1_r_t, rdranksw, 1); 
    ncr_modify32(region, NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG1, mask, value);

    /* Enable Dynamic ODT */
    mask = value = 0;
    SMAV(ncp_phy_CFG_SYSMEM_PHY_DPCONFIG0_BLx_r_t, ovrdynodt, 0);
    for (bl = 0; bl < parms->num_bytelanes; bl++) 
    {
        ncr_modify32(region, NCP_PHY_CFG_SYSMEM_PHY_DP_CONFIG0_BL(bl), 
                        mask, value);
    }

    /*
     * The basic algorithm for coarse write leveling is:
     *  - we generate a block of data with a walking one pattern
     *    in each byte-lane, and a second block of data with a 
     *    walking zero. Each byte of each eight-byte beat then 
     *    indicates the beat from which it was written.
     *  - write two bursts of the eight beat pattern
     *  - read back starting at the address of the second burst
     *    and compare the value of each byte lane. If a byte lane
     *    has incorrect data we advance one clock
     *  - Set the WLDQSxGRP register to indicate which byte-lanes
     *    need to be advanced by one clock
     *  - set DFICNTLWLCNTL with the rank to adjust and the dly_delta
     *    set to one to increment the delay. Writing this register 
     *    will perform the adjustment.
     *  - repeat the write/read/compare test using the walking zero
     *    pattern. If there are no errors then write-leveling has 
     *    succeeded.
     */

    /* first just run the bytelane test to initialize memory */
    NCP_CALL(bl_test_fn(dev, node, addr, 3, 
                &bad_bl, num_bls));

    bad_bl = 0;
    /* run the bytelane test using the walking one pattern */
    NCP_CALL(bl_test_fn(dev, node, addr, 0, 
                &bad_bl, num_bls));

    /*
     * advance one clock for each failing bytelane
     */
    for (bl = 0; bl < num_bls; bl++)
    {
        if (bad_bl & (1 << bl))
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
    }

    /* 
     * re-run the test with walking zero
     * It ought to pass. 
     */
    if (busAdaptor != NCP_DEV_BUS_FBRS) 
    {
        memset(&bad_bl, 0, sizeof(bad_bl));
        NCP_CALL(bl_test_fn(dev, node, addr, 1, 
                &bad_bl, num_bls));
    }


    /*
     * advance clocks for each failing bytelane
     */
    for (bl = 0; bl < num_bls; bl++)
    {
        if (bad_bl & (1 << bl))
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

    }

    /* 
     * re-run the test with walking zero
     * It ought to pass. 
     */
    memset(&bad_bl, 0, sizeof(bad_bl));
    if (busAdaptor != NCP_DEV_BUS_FBRS) 
    {
        NCP_CALL(bl_test_fn(dev, node, addr, 0, 
                &bad_bl, num_bls));
    }

    /* if we still have bad bytelanes then leveling has failed */
    if ((bad_bl) != 0 ) {
        NCP_CALL(NCP_ST_SYSMEM_PHY_WL_ERR);
    }

    /* check the PHY status */
    NCP_CALL(ncp_sm_lsiphy_status_check(dev, smId, parms));


    /* 
     * If ECC is enabled now level the ECC byte lane 
     */
    if ( (parms->enableECC) && (busAdaptor != NCP_DEV_BUS_FBRS) )
    {
        NCP_COMMENT("sysmem phy coarse write leveling - ECC bytelane rank %d", rank);

        ecc_mask = NCP_SM_DENALI_V2_ECC_INTR_BITS;

        /* enable ECC reporting with no correction */
        eccEnbFn(dev, ctlRegion, 1);

        NCP_CALL(ecc_bl_test_fn(dev, ctlRegion, addr, node, 
                                         1, ecc_mask, num_bls, &bad_bl));
        bad_bl = 0;
        NCP_CALL(ecc_bl_test_fn(dev, ctlRegion, addr, node, 
                                         0, ecc_mask, num_bls, &bad_bl));

        /* for now assume ECC is always the last BL */
        bl = num_bls ;

        if (bad_bl != 0) {
            
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

                NCP_CALL(ecc_bl_test_fn(dev, ctlRegion, addr, node, 
                                             1, ecc_mask, num_bls, &bad_bl));
                bad_bl = 0;
                NCP_CALL(ecc_bl_test_fn(dev, ctlRegion, addr, node, 
                                         0, ecc_mask, num_bls, &bad_bl));

                if (bad_bl == 0) {
                    /* it worked - we're done */
                    break;
                }
            }
            

        }

        if (bad_bl != 0) {
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

                NCP_CALL(ecc_bl_test_fn(dev, ctlRegion, addr, node, 
                                             1, ecc_mask, num_bls, &bad_bl));
                bad_bl = 0;
                NCP_CALL(ecc_bl_test_fn(dev, ctlRegion, addr, node, 
                                         0, ecc_mask, num_bls, &bad_bl));

                if (bad_bl == 0) {
                    /* it worked - we're done */
                    break;
                }
            }
        }

        /* if we still have bad bytelanes then leveling has failed */
        if ( (busAdaptor != NCP_DEV_BUS_FBRS) && (bad_bl) ) {
            NCP_CALL(NCP_ST_SYSMEM_PHY_ECC_WL_ERR);
        }

        /* disable ECC until all ranks are level */
        eccEnbFn(dev, ctlRegion, 0);
    }

    /* check the PHY status */
    NCP_CALL(ncp_sm_lsiphy_status_check(dev, smId, parms));

NCP_RETURN_LABEL
    return ncpStatus;
}



#ifdef NCP_CONFIG_CMEM
#define NCP_CMEM_SANITY_TEST_BUF_SIZE 16

/* 
 * a simple write/read/compare memory test used to ensure
 * that CMEM is functional.
 * if 'pattern' is zero or one we use the ECC test data patterns,
 * otherwise we use a simple incrementing integer. 
 */

ncp_st_t ncp_sm_cmem_sanity_test(
    ncp_dev_hdl_t *dev,
    ncp_uint32_t   node,
    ncp_uint32_t   pattern)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_uint32_t val;
    ncp_uint32_t i;
#ifdef UBOOT
    ncp_uint32_t  *pBuf = (unsigned *)(NCA + 0x1000);
#else
    ncp_uint32_t  pBuf[NCP_CMEM_SANITY_TEST_BUF_SIZE];
#endif
    NCP_COMMENT("cmem sanity test node %d pattern %d\n", node, pattern);

    /* initialize write buffer */
    for ( i = 0; i < NCP_CMEM_SANITY_TEST_BUF_SIZE; i++) {
        if (pattern <= 1) {
            pBuf[i] = ecc_test_data_64bit[pattern][i];
        }
        else {
            pBuf [i] = i;
        }
    }

    /* write to target 4 */
#ifdef UBOOT
    ncr_write(NCP_REGION_ID( node, 4 ), 0, 0,
            NCP_CMEM_SANITY_TEST_BUF_SIZE*4, 0);
#else
    NCP_CALL(ncp_block_write32(dev, NCP_REGION_ID( node, 4 ), 0, pBuf,
            NCP_CMEM_SANITY_TEST_BUF_SIZE, 0));
#endif

    /* clear buffer */
    for ( i = 0; i < NCP_CMEM_SANITY_TEST_BUF_SIZE; i++) {
        pBuf [i] = 0;
    }

    /* read from target 1 */
#ifdef UBOOT
    ncr_read(NCP_REGION_ID( node, 1 ), 0, 0,
            NCP_CMEM_SANITY_TEST_BUF_SIZE*4, 0);
#else
    NCP_CALL(ncp_block_read32(dev, NCP_REGION_ID( node, 1 ), 0, pBuf,
            NCP_CMEM_SANITY_TEST_BUF_SIZE, 0));
#endif

    /* validate buffer contents */
    for ( i = 0; i < NCP_CMEM_SANITY_TEST_BUF_SIZE; i++) {
        if (pattern <= 1) {
            val = ecc_test_data_64bit[pattern][i];
        }
        else {
            val = i;
        }
                
        if (pBuf [i] != val) 
        {
            /* fail out if miscompare */
            NCP_CALL(NCP_ST_TREEMEM_DDR_INIT_ERR);
        }
    }

NCP_RETURN_LABEL
    return ncpStatus;

}


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
    ncp_uint32_t     mask, value;
    ncp_uint32_t     node;


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

    node = sm_nodes[smId];
    ctlRegion = NCP_REGION_ID(node, NCP_TREEMEM_TGT_DDR);

    /* set up for memory access */
    mask = value = 0;
    SMAV(ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t, wrt_lvl,     0);
    SMAV(ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t, ref_ena,     1);
    SMAV(ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t, odt_mode,    3);
    ncr_modify32( ctlRegion, NCP_DDR_CFG_NTEMC_DDR_CTRL, mask, value);

    /* enable ECC */
    if (parms->enableECC) {
        mask = value = 0;
        SMAV(ncp_ddr_CFG_NTEMC_ECC_CTRL_r_t, ecc_mode,     1);
        ncr_modify32( ctlRegion, NCP_DDR_CFG_NTEMC_ECC_CTRL, mask, value);
    }
     
    /* 
     * BUGZ 43920: workaround for h/w bug 42349
     * don't enable auto_zq for chips on which it's broken 
     * The older 34xx chips with the IBM PHY are handled in
     * a different file. The only device with the LSI PHY
     * for which auto_zq is broken is 2500_v1
     *
     * The ZQCS interval is now a user configurable parameter,
     * and an interval of zero indicates that auto-zq is disabled.
     */
    switch (parms->version) {
        default:
            if (parms->zqcs_interval != 0) {
                SMAV(ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t, auto_zq,     1);
            }
            break;
    }

    mask = value = 0;
    SMAV(ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t, zq_per,      0);
    ncr_modify32(ctlRegion, NCP_DDR_CFG_NTEMC_DDR_CTRL, mask, value);


    /*
     * perform a sanity test to make sure basic CMEM write/read is working.
     * if it's not return an error 
     *
     * first run the test with a simple incrementing pattern, then try
     * the ECC test data patterns
     */

    NCP_CALL(ncp_sm_cmem_sanity_test(dev, node, 3));
    NCP_CALL(ncp_sm_cmem_sanity_test(dev, node, 0));
    NCP_CALL(ncp_sm_cmem_sanity_test(dev, node, 1));


NCP_RETURN_LABEL
    return ncpStatus;
}
#endif

#ifndef NCP_CONFIG_CMEM
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


#define NCP_SM_FILL_BLOCK_SIZE 0x00100000
ncp_st_t
ncp_sm_lsiphy_runtime_adj(
        ncp_dev_hdl_t   dev,
        ncp_uint32_t    smId,
        ncp_sm_parms_t *parms)
{

    ncp_st_t        ncpStatus = NCP_ST_SUCCESS;
    ncp_region_id_t region = 0;
    ncp_region_id_t ctlRegion = 0;
    ncp_bool_t isSysMem;
    ncp_uint32_t mask;
    ncp_uint32_t value;

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
#ifdef NCP_CONFIG_CMEM
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
    if (parms->enable_runtime_updates)
    {
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
    }

    if (isSysMem) {
        ncr_write32(ctlRegion, 0x114, 0x3fff);

        /* 
         * Enable ECC correction. 
         * we'll initialize all sysmem later as part of syscache init
         */
        if (parms->enableECC) 
        {
            NCP_COMMENT("enabling ECC");
       	    if (parms->version == NCP_CHIP_ACP35xx)
	    {
            	eccEnbFn(dev, ctlRegion, 1);
	    }
	    else
	    {
		/* not sure why we need 3 here- but leaving for legacy working */
            	eccEnbFn(dev, ctlRegion, 3);
	    }
        }

        /* clear controller interrupt status */
        intrStatFn(dev, ctlRegion, 0xffffffff);
    } 
#ifdef NCP_CONFIG_CMEM
    else 
    {
        ncp_uint32_t reg;

        /* NCP_DDR_CFG_NTEMC_DFI_TIMING2  tctlupd_intv = 4 */
        ncr_read32(ctlRegion, 0x30, &reg);
        reg &= 0xffffe000;
        reg |= 0x00000004;
        ncr_write32(ctlRegion, 0x30, reg);

        mask = value = 0;
        SMAV(ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t, ref_ena, 1); 
        ncr_modify32(region, NCP_DDR_CFG_NTEMC_DDR_CTRL, mask, value);

#ifdef UBOOT
        /*
         * write CMEM config local node scratch register to indicate
         * U-boot CMEM init complete
         */
        ncr_write32(NCP_REGION_ID(sm_nodes[smId], 0xff), 0x20, 1);
#endif
    }
#endif


    /* check the PHY status */
    ncpStatus = ncp_sm_lsiphy_status_check(dev, smId, parms);

NCP_RETURN_LABEL
    return ncpStatus;
}

#ifdef UBOOT
#include "ncp_sm_denali_2041_init.c"

#ifdef NCP_CONFIG_CMEM
#include "ncp_cm_ctrl_init.c"
#endif
#endif 

#if 0
static void set_fixed_latency(void)
{
        ncp_uint32_t reg32;
    /* TEMP DEBUG */
    /* 
     * enabling fixed latency mode will prevent a missing 
     * read response from hanging the system. Instead of 
     * not returning, the read will return garbage. 
     */
    printf("enabling fixed latency mode\n");

    /*
     * set fixed_rl. this value must be calculated using some
     * TBD formula.
     */
    ncr_read32(NCP_REGION_ID(34,1), 
            NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG0, &reg32);
    reg32 |= 0x00040000;
    ncr_write32(NCP_REGION_ID(34,1), 
            NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG0, reg32);

    ncr_read32(NCP_REGION_ID(15,1), 
            NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG0, &reg32);
    reg32 |= 0x00040000;
    ncr_write32(NCP_REGION_ID(15,1), 
            NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG0, reg32);


    /* enable fixed latency fifo mode */
    ncr_read32(NCP_REGION_ID(34,1), 
            NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG2, &reg32);
    reg32 |= 0x44000000;
    ncr_write32(NCP_REGION_ID(34,1), 
            NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG2, reg32);
    
    ncr_read32(NCP_REGION_ID(15,1), 
            NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG2, &reg32);
    reg32 |= 0x44000000;
    ncr_write32(NCP_REGION_ID(15,1), 
            NCP_PHY_CFG_SYSMEM_PHY_PHYCONFIG2, reg32);
}
#endif


static  ncp_uint64_t
calc_sdram_size(ncp_sm_parms_t *parms)
{
    unsigned long long sdram_capacity_bytes;
    unsigned long sdram_device_width_bits;
    unsigned long primary_bus_width_bits;
    unsigned long long total_sdram_size;

    sdram_capacity_bytes = (1 << parms->sdram_device_density) *
                ((256 * 1024 * 1024) / 8);
    sdram_device_width_bits = 4 * (1 << parms->sdram_device_width);
    primary_bus_width_bits = 8 * (1 << parms->primary_bus_width);
    total_sdram_size =  parms->num_ranks_per_interface *
                sdram_capacity_bytes *
                    (primary_bus_width_bits / sdram_device_width_bits);

    return total_sdram_size;

}



ncp_st_t
ncp_sysmem_init_lsiphy(
        ncp_dev_hdl_t   dev,
        ncp_uint32_t    smId,
        ncp_sm_parms_t *parms)
{
    ncp_st_t        ncpStatus;
    ncp_st_t        returnStatus;

    ncp_uint32_t    rank;
    ncp_uint64_t    addr;
    ncp_sm_topology_t topology = parms->topology;

    ncp_bool_t do_rd_lvl = TRUE;
    ncp_bool_t do_wr_lvl = TRUE;
    ncp_bool_t do_gt_trn = TRUE;
    ncp_bool_t did_training = FALSE;
    ncp_bool_t restore_complete = FALSE;

#ifndef UBOOT 
    ncp_bool_t ncp_sm_phy_reg_dump    = FALSE;
#endif

    /* static PHY setup */
    NCP_CALL(ncp_sm_lsiphy_static_init(dev, smId, parms));

    /* for DDR retention save or check operating point */

    if ((smId == 0) && ncp_map_phy_reg_file() != 0) {
        printf("couldn't map PHY reg file\n");
        NCP_CALL(NCP_ST_ERROR);
    }

#ifndef AXM_35xx
    if (  parms->ddrRetentionEnable && (parms->ddrRecovery == TRUE) )
    {
        if (NCP_ST_SUCCESS == ncp_sm_lsiphy_reg_restore(dev, smId, parms ))
        {
            printf("SMEM%d DDR PHY register restore succeeded\n", smId); 
            restore_complete = TRUE;
        }
        else {
            printf("SMEM%d DDR PHY register restore failed\n", smId); 
        }
    }
#endif

    if (smId < NCP_SYSMEM_NUM_NODES) {
        /* Initialize the system memory controller... */
        NCP_CALL(ncp_sm_denali_2041_init(dev, smId, parms)); 

        /* 
         * and enable it. 
         *
         * the enable is broken out in a separate function
         * to facilitate script based test capability.
         */
        NCP_CALL(ncp_sm_denali_enable(dev, smId, parms));
    } 
#ifdef NCP_CONFIG_CMEM
    else 
    {
        NCP_CALL(ncp_cm_controller_init(dev, smId, parms));
    }
#endif


    /* 
     * if the PHY registers have not been restored then we must
     * run the PHY training sequence.
     */

    /* 
     * NEW! only write-leveling registers are restored.
     * always do read calibration on each rank.
     */


    /*#define  NCP_SM_DISP_TRAINING_STEPS*/

    for (rank = 0; rank < NCP_SM_MAX_RANKS; rank++)
    {
        if (topology & (1 << rank)) 
        {

            if (do_wr_lvl &&  (restore_complete == FALSE) )
            {
                /* fine write leveling */
#ifdef NCP_SM_WRLVL_DUP
                if ( (parms->version == NCP_CHIP_ACP25xx) && ( rank > 0 ) )
                {
#ifdef NCP_SM_DISP_TRAINING_STEPS
                    printf("wrlvl dup smId %d rank %d\n", smId, rank);
#endif
                    NCP_CALL(ncp_sm_lsiphy_wrlvl_dup(dev, smId, 0, 1));
                } 
                else 
#endif
                {
#ifdef NCP_SM_DISP_TRAINING_STEPS
                    printf("wrlvl smId %d rank %d\n", smId, rank);
#endif
                    NCP_CALL(ncp_sm_lsiphy_training_run(dev, smId, rank, 0,
                             NCP_SYSMEM_PHY_WRITE_LEVELING,
                             parms));
                }
            }

            if (do_gt_trn) {
                /* gate training */
#ifdef NCP_SM_DISP_TRAINING_STEPS
                printf("gttrn smId %d rank %d\n", smId, rank);
#endif
                NCP_CALL(ncp_sm_lsiphy_gate_training(dev, smId, rank, parms));
            }

            if (do_rd_lvl) {
                /* read leveling */
#ifdef NCP_SM_DISP_TRAINING_STEPS
                printf("rdlvl smId %d rank %d\n", smId, rank);
#endif
                NCP_CALL(ncp_sm_lsiphy_training_run(dev, smId, rank, 0,
                             NCP_SYSMEM_PHY_READ_LEVELING,
                             parms));

                NCP_CALL(ncp_sm_lsiphy_training_run(dev, smId, rank, 1,
                             NCP_SYSMEM_PHY_READ_LEVELING,
                             parms));
            }
        }
    }


    if (restore_complete == FALSE)
    {

        if ((parms->version == NCP_CHIP_ACP55xx) &&
            (smId < 2)) 
        {
            ncp_uint32_t reg;
    
            ncr_read32(NCP_REGION_ID(0x156, 0x00), 0x1004, &reg);

            /* set up NCA VAT to cover all sysmem space */
            ncr_write32(NCP_REGION_ID(0x16, 0x10), 0x1000, 0x8000000f);
            ncr_write32(NCP_REGION_ID(0x16, 0x10), 0x1004, 0xffffff00);
            if (reg & 0x00000040) {
                /* reset system memory map */
                ncr_write32(NCP_REGION_ID(0x16, 0x10), 0x1008, 0x00000020);
            } else {
                /* mission mode memory map */
                ncr_write32(NCP_REGION_ID(0x16, 0x10), 0x1008, 0x00000000);
            }
            ncr_write32(NCP_REGION_ID(0x16, 0x10), 0x100c, 0x00000000);

            /* set NCA TTYPES */
            ncr_write32(NCP_REGION_ID(257,0), 0x10280, 0x00220026);
            ncr_write32(NCP_REGION_ID(0x16, 0x10), 0x280, 0x00000003);

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


#ifdef NCP_SM_DISP_TRAINING_STEPS
                printf("coarse wrlvl smId %d rank %d addr 0x%012llx\n",
                                smId, rank, addr);
#endif
#ifdef NCP_CONFIG_ELM
                if ((parms->version == NCP_CHIP_ACP55xx) && (smId < 2))
                {
                        use_elm(dev, smId);
                }
#endif

                NCP_CALL(ncp_sm_lsiphy_coarse_write_leveling(dev,
                            smId, rank, addr, parms));
            }
        }

        did_training = TRUE;
    }

    if (parms->ddrRetentionEnable && did_training)
    {
        /* 
         *  PHY training complete - perform memory test
         */
        /* TODO !! */

        /*
         * save these PHY training values for next time
         */
        ncpStatus = ncp_sm_lsiphy_reg_save(dev, smId, parms);
    }

    NCP_CALL(ncp_sm_lsiphy_runtime_adj(dev, smId, parms));

NCP_RETURN_LABEL

    returnStatus = ncpStatus;
#ifdef NCP_CONFIG_ELM
    if ((parms->version == NCP_CHIP_ACP55xx) &&
            (smId < 2)) 
    {
        /*
         * depending on how DDR retention is configured we may or
         * may not have configured single/dual ELM mode as part of
         * coarse write leveling above. Here we always reconfigure
         * the ELM for single/dual SMEM mode whether it needs it or not.
         */
        if (parms->num_interfaces == 2) {
            /* use both elms */
            use_elm(dev, 3);
        } 
        else
        {
            /* use ELM0 only */
            use_elm(dev, 0);
        }
        /* restore NCA TTYPEs */
        ncr_write32(NCP_REGION_ID(257,0), 0x10280, 0x12221222);
        ncr_write32(NCP_REGION_ID(0x16, 0x10), 0x280, 0x0000000b);
    }
#endif

#ifdef NCP_SM_PHY_REG_DUMP
  if ( (NCP_ST_SUCCESS != returnStatus) || ncp_sm_phy_reg_dump )
  {
    ncp_sm_lsiphy_reg_dump(dev, smId, parms->version);
  }
#endif

 return  returnStatus;
}
