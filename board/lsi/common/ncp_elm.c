
/**************************************************************************
 **                                                                        *
 **   LSI Corporation, Inc. CONFIDENTIAL                                   *
 **                                                                        *
 **                       PROPRIETARY NOTE                                 *
 **                                                                        *
 **    This software contains information confidential and proprietary     *
 **    to LSI Corporation Inc.  It shall not be reproduced in whole or in  *
 **    part, or transferred to other documents, or disclosed to third      *
 **    parties, or used for any purpose other than that for which it was   *
 **    obtained, without the prior written consent of LSI Corporation Inc. *
 **    (c) 2008-2013, LSI Corporation Inc.  All rights reserved.           *
 **                                                                        *
 **  ***********************************************************************
 **
 **  ***********************************************************************
 **  
 **************************************************************************/
#ifndef UBOOT
#include <stdio.h>
#include "ncp.h"
#include "ncp_pvt.h"
#endif
#include "ncp_sysmem_ext.h"
#include "ncp_sysmem_lsiphy.h"

#include "regs/ncp_elm_regs.h"
#include "regs/ncp_elm_reg_defines.h"

ncp_st_t
ncp_elm_init(
    ncp_dev_hdl_t dev,
    ncp_sm_parms_t *parms)
{
    ncp_st_t         ncpStatus = NCP_ST_SUCCESS;
    ncp_uint32_t     ddrBits = 0;
    ncp_uint32_t     xorMask = 0;
    ncp_uint64_t     sdramSize; 
    ncp_uint32_t     mungeValue; 

    /*
     *
     */
    NCP_COMMENT("ELM initialization");

    /* 
     * calculate the value of the ELM munger register 
     *
     * first calculate the value of the XOR mask based on
     * number of bits of address per controller and number
     * of chip-selects
     */
    sdramSize = parms->totalSize / parms->num_interfaces; 
    while ( 0 < sdramSize) {
        ++ddrBits;
        sdramSize >>= 1;
    }
    --ddrBits;

    switch (parms->num_ranks_per_interface)
    {
        case 1 : 
            xorMask = 0x7 << (ddrBits - 24);
            break;

        case 2:
            xorMask = 0xf << (ddrBits - 25);
            break;

        case 4:
            xorMask = 0x1f << (ddrBits - 26);
            break;
    }

    /* 
     * TODO: 
     * Munge register hash mask should be configurable! 
     * we need an open page size parameter.
     */
    mungeValue = (xorMask << 16) | 0xffff;


    if (parms->syscacheMode == NCP_SYSCACHE_MODE_PERFORMANCE) 
    {
        /* set ELM munge regsiter */
        ncr_write32 (NCP_REGION_ID(0x158, 0), 0x1c, mungeValue);
        ncr_write32 (NCP_REGION_ID(0x159, 0), 0x1c, mungeValue);
    }

ncp_return:
    return ncpStatus;
}

extern ncp_sm_intr_status_fn_t      intrStatFn ;


ncp_st_t
ncp_elm_sysmem_fill(
        ncp_dev_hdl_t dev,
        ncp_sm_parms_t *parms)
{
    ncp_st_t         ncpStatus = NCP_ST_SUCCESS;
    ncp_uint32_t     numCacheLines ;
    int i;

    NCP_COMMENT("Initializing system memory for ECC");
    /* 
     * initialize all of sysmem through the ELMs
     * start each ELM before checking completion so they
     * all run in parallel
     */

    numCacheLines = (ncp_uint32_t) ((parms->totalSize / parms->num_interfaces) / 64);
    numCacheLines--;



    /* elm0 */
    ncr_write32(NCP_REGION_ID(0x158, 0), 0x40, 0x00000000);
    ncr_write32(NCP_REGION_ID(0x158, 0), 0x44, numCacheLines);
    ncr_write32(NCP_REGION_ID(0x158, 0), 0x48, 0x0);

    /* elm1 */
    ncr_write32(NCP_REGION_ID(0x159, 0), 0x40, 0x00000000);
    ncr_write32(NCP_REGION_ID(0x159, 0), 0x44, numCacheLines);
    ncr_write32(NCP_REGION_ID(0x159, 0), 0x48, 0x0);
    
    /* poll elm0 for completion */
    ncr_poll(NCP_REGION_ID(0x158, 0), 0x44, 0x1fffffff, 0x0, 10000, 1000000);
    
    /* poll elm1 for completion */
    ncr_poll(NCP_REGION_ID(0x159, 0), 0x44, 0x1fffffff, 0x0, 10000, 1000000);    

	/* If ECC is enabled, clear the status bits. */
	if (0 != parms->enableECC) {
		/* clear ECC interrupt status bits */
		for( i = 0; i < parms->num_interfaces; ++ i ) {
            intrStatFn(NULL, 
                    NCP_REGION_ID (sm_nodes[i], 0), 
                    NCP_SM_DENALI_V2_ECC_INTR_BITS);

		}
	}

ncp_return:
    return ncpStatus;

}


