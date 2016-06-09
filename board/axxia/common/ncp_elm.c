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
#else
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
    ncp_uint32_t     hash_mask;
    ncp_uint32_t     opsize;
    ncp_uint32_t     bit; 

    /*
     *
     */
    NCP_COMMENT("ELM initialization");

    /* 
     * if open_page_size is non-zero then we
     * calculate the setting of the ELM munge 
     * register and program it.
     *
     * if the open_page_size is zero then we 
     * leave the munge register in it's default
     * state (unmunged). 
     */
    if (parms->open_page_size)
    {
        /* 
         * calculate the value of the ELM munge register 
         *
         * first calculate the value of the XOR mask based on
         * number of bits of address per controller and number
         * of chip-selects
         */
      if (4 == parms->num_interfaces)
        sdramSize = parms->totalSize >> 3;
      else if (2 == parms->num_interfaces)
        sdramSize = parms->totalSize >> 1;
      else
        sdramSize = parms->totalSize;

        while ( 0 < sdramSize) {
            ++ddrBits;
            sdramSize >>= 1;
        }
        --ddrBits;

        if ((parms->version == NCP_CHIP_ACP56xx) ||
            (parms->version == NCP_CHIP_ACPXLF))
	{
	    ncp_uint32_t	mungebits = 0, mungemask = 0, cscount = 0;
	    ncp_denali_DENALI_CTL_128_5600_t reg128 = {0};

	    ncr_read32(NCP_REGION_ID(0x22, NCP_SYSMEM_TGT_DENALI), NCP_DENALI_CTL_128_5600, (ncp_uint32_t *)&reg128);

      	    if (4 == parms->num_ranks_per_interface)
        	cscount = 2;
      	    else if (2 == parms->num_ranks_per_interface)
        	cscount = 1;
      	    else if (1 == parms->num_ranks_per_interface)
        	cscount = 0;

	    mungebits = 4 - (reg128.bg_rotate_en) - ((parms->sdram_device_width == 2) ? 1 /*x16*/ : 0/*x8*/) + cscount;
	    mungemask = ((1 << mungebits) - 1);

            switch (parms->num_ranks_per_interface)
            {
                case 1 : 
                    xorMask = (mungemask << ((reg128.bg_rotate_en) + ((parms->sdram_device_width == 2) ? 1 : 0) + ddrBits - 25));
                    break;
    
                case 2:
                    xorMask = (mungemask << ((reg128.bg_rotate_en) + ((parms->sdram_device_width == 2) ? 1 : 0) + ddrBits - 26));
                    break;
    
                case 4:
                    xorMask = (mungemask << ((reg128.bg_rotate_en) + ((parms->sdram_device_width == 2) ? 1 : 0) + ddrBits - 27));
                    break;
    
                default:
		    return NCP_ST_ERROR;
            }
	}
	else
	{
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
	}	

        /*
         * now calculate the value for the hash_mask 
         * based on open_page_size
         */
        hash_mask = 0xffff;
        opsize = parms->open_page_size;
        bit = 0;
        while (opsize > 64) {
            hash_mask &= ~(1 << bit);
            bit++;
            opsize >>= 1;
        }

        mungeValue = (xorMask << 16) | hash_mask;
        /* set ELM munge regsiter */
        if (parms->version == NCP_CHIP_ACP56xx) 
	{
            ncr_write32 (NCP_REGION_ID(0x167, 0), 0x1c, mungeValue);
            ncr_write32 (NCP_REGION_ID(0x167, 1), 0x1c, mungeValue);
	}
        else if (parms->version == NCP_CHIP_ACPXLF) 
	{
            ncr_write32 (NCP_REGION_ID(0x167, 0), 0x1c, mungeValue);
            ncr_write32 (NCP_REGION_ID(0x167, 1), 0x1c, mungeValue);
            ncr_write32 (NCP_REGION_ID(0x167, 2), 0x1c, mungeValue);
            ncr_write32 (NCP_REGION_ID(0x167, 3), 0x1c, mungeValue);
	}
	else
	{	
            ncr_write32 (NCP_REGION_ID(0x158, 0), 0x1c, mungeValue);
            ncr_write32 (NCP_REGION_ID(0x159, 0), 0x1c, mungeValue);
	}
    }

NCP_RETURN_LABEL
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
    if (4 == parms->num_interfaces)
      numCacheLines = (ncp_uint32_t)(parms->totalSize >> 8);
    else if (2 == parms->num_interfaces)
      numCacheLines = (ncp_uint32_t)(parms->totalSize >> 7);
    else
      numCacheLines = (ncp_uint32_t)(parms->totalSize >> 6);

    numCacheLines--;

    if (parms->version == NCP_CHIP_ACP56xx) 
    {
	for( i = 0; i < parms->num_interfaces; ++ i ) {
            ncr_write32(NCP_REGION_ID(0x167, i), 0x40, 0x00000000);
            ncr_write32(NCP_REGION_ID(0x167, i), 0x44, numCacheLines);
            ncr_write32(NCP_REGION_ID(0x167, i), 0x48, 0x0);
	}
	/* separating init and poll saves significant time during config */
	for( i = 0; i < parms->num_interfaces; ++ i ) {
    	    /* poll elmi for completion */
    	    ncr_poll(NCP_REGION_ID(0x167, i), 0x44, 0x1fffffff, 0x0, 10000, 1000000);
	}
    }
    else if (parms->version == NCP_CHIP_ACPXLF) 
    {
	for( i = 0; i < parms->num_interfaces; ++ i ) {
            ncr_write32(NCP_REGION_ID(0x167, i), 0x40, 0x00000000);
            ncr_write32(NCP_REGION_ID(0x167, i), 0x44, numCacheLines);
            ncr_write32(NCP_REGION_ID(0x167, i), 0x48, 0x0);
	}
	/* separating init and poll saves significant time during config */
	for( i = 0; i < parms->num_interfaces; ++ i ) {
    	    /* poll elmi for completion */
    	    ncr_poll(NCP_REGION_ID(0x167, i), 0x44, 0x1fffffff, 0x0, 10000, 1000000);
	}
    }
    else
    {
#ifndef __UBOOT__
        /* elm0 */
        ncr_write32(NCP_REGION_ID(0x158, 0), 0x40, 0x00000000);
        ncr_write32(NCP_REGION_ID(0x158, 0), 0x44, numCacheLines);
        ncr_write32(NCP_REGION_ID(0x158, 0), 0x48, 0x0);

        /* elm1 */
        if (parms->num_interfaces == 2 ) {
            ncr_write32(NCP_REGION_ID(0x159, 0), 0x40, 0x00000000);
            ncr_write32(NCP_REGION_ID(0x159, 0), 0x44, numCacheLines);
            ncr_write32(NCP_REGION_ID(0x159, 0), 0x48, 0x0);
        }
    
        /* poll elm0 for completion */
        ncr_poll(NCP_REGION_ID(0x158, 0), 0x44, 0x1fffffff, 0x0, 10000, 1000000);
    
        /* poll elm1 for completion */
        if (parms->num_interfaces == 2 ) {
            ncr_poll(NCP_REGION_ID(0x159, 0), 0x44, 0x1fffffff, 0x0, 10000, 1000000);    
        }

	/* If ECC is enabled, clear the status bits. */
	if ((0 != parms->enableECC) && (intrStatFn != NULL)) {
		/* clear ECC interrupt status bits */
		for( i = 0; i < parms->num_interfaces; ++ i ) {
                    intrStatFn(dev, 
                        NCP_REGION_ID (sm_nodes[i], 0), 
                        NCP_SM_DENALI_V2_ECC_INTR_BITS);

		}
	}
#endif	/* __UBOOT__ */
    }

NCP_RETURN_LABEL
    return ncpStatus;

}


