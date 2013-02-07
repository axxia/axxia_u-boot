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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */




#ifndef NCP_STD_TASKIO_LITE
#include <config.h>
#else
#include <stdint.h>
#include <sys/types.h>
#endif


#if defined(NCP_TASKIO_UBOOT_ENV)
#include "ncp_task_lite_nca_regs.h"
#include "ncp_task_lite_nca_reg_defines.h"
#include "ncp_task_lite_basetypes.h"
#include "ncp_task_lite.h"
#include "ncp_task_lite_pvt.h"
#else /* defined(NCP_TASKIO_UBOOT_ENV) */
#include "ncp_task_lite.h"
#include "ncp_task_lite_pvt.h"
#endif /* defined(NCP_TASKIO_UBOOT_ENV) */

/*
 * Task I/O Symbols
 */
#if 0 
NCP_EXPORT_SYMBOL(ncp_task_lite_uboot_config);
NCP_EXPORT_SYMBOL(ncp_task_lite_uboot_register_allocators);
#endif


#if defined(NCP_TASKIO_UBOOT_ENV) || defined(TASKIOLITE_USES_UBOOT_CFG)

#undef NCP_TASKIO_LITE_USE_BACKPRESSURE

ncp_st_t
ncp_task_lite_uboot_set_rbp_backpressure(ncp_dev_t *dev, ncp_bool_t enable, ncp_uint32_t iPCQmask, ncp_uint32_t bSizeMask)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;    
    ncp_uint32_t regVal32=0;
    
    NCP_DEV_NCA_READ_REG32(dev, NCP_REGION_NCA_AXI, NCP_NCA_RBP_ITASK_BP_EN, (ncp_uint32_t *)&regVal32); 
        
    if (enable)
    {
        regVal32 |= iPCQmask;
    }    
    else
    {
        regVal32 &= ~iPCQmask;
    }
    NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,  NCP_NCA_RBP_ITASK_BP_EN, regVal32);
    
    /* 
     * Backpressure on selected buff sizes 
     * NOTE: Must program even if backpressure is off
     */        
    NCP_DEV_NCA_WRITE_REG32(dev, 
                            NCP_REGION_NCA_AXI,  
                            NCP_NCA_RBP_ITASK_BP_INCLD_BSIZ, bSizeMask); 
    
NCP_RETURN_LABEL
    return(ncpStatus);    
}

ncp_uint64_t
ncp_task_lite_uboot_nca_va_2_pa(void *va32)
{
     ncp_uint64_t x64;
     ncp_uint32_t pa32;
     ncp_uint64_t pa64=0ULL;
     
     if (0 != va32)
     {
#ifndef TASKIOLITE_USES_UBOOT_CFG  
        pa32 = task_lite_va_2_pa_fn(va32);
#if 0
	printf("%s:%d - va32=0x%p pa32=0x%lx\n",
	       __FILE__, __LINE__, va32, pa32);	/* ZZZ */
#endif
#else
        ncp_nca_va_2_pa(0, va32);
#endif
        
        pa64 += (ncp_uint64_t)pa32 + NCP_DEV_AXI_PLB_BASE;  /* PLB SUPPORT ONLY! */
#if 0
	printf("%s:%d - pa64=0x%llx pa32=0x%lx\n",
	       __FILE__, __LINE__, pa64, pa32);	/* ZZZ */
#endif
     }   

     return pa64;
}




ncp_st_t
ncp_task_lite_uboot_config_mem()
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;



#ifndef TASKIOLITE_USES_UBOOT_CFG  

    /* 
     * We allocate on the fly in the u-boot environment, so no need
     * for GSM info,  normally obtained from ncp driver
    */
    NCP_ASSERT_LITE(NULL != 
        (pNcpNcaTaskGSM = 
            task_lite_alloc_aligned_fn(sizeof(ncp_nca_task_t))),
        NCP_ST_TASK_NO_CACHE_ALLLIGNED_MEM);  
          
    /*
     * Unless done so for clarity,   we only initialize those structure
     * members that require non-zero intial values.
     */
      
    pNcpNcaTaskGSM->gsmAllocsAllowed                = TRUE; /* DEBUG */ 

    /* DEBUG */
    pNcpNcaTaskGSM->cookie1 = 0xAABBCCDD;
    pNcpNcaTaskGSM->cookie2 = 0xFFEEDDCC;
    /* END DEBUG */   
#endif

    pNcpNcaTaskGSM->cannedCompletionRolloverEntry.taskPriority    = 0;
    pNcpNcaTaskGSM->cannedCompletionRolloverEntry.toid            = 0;    
    pNcpNcaTaskGSM->cannedCompletionRolloverEntry.dataSize        = 0;
    pNcpNcaTaskGSM->cannedCompletionRolloverEntry.queueId         = 0;
    pNcpNcaTaskGSM->cannedCompletionRolloverEntry.completionCntInc= 255;
    pNcpNcaTaskGSM->cannedCompletionRolloverEntry.nOp             = 1;
    pNcpNcaTaskGSM->cannedCompletionRolloverEntry.destId          = 0;
    pNcpNcaTaskGSM->cannedCompletionRolloverEntry.intOnComplete   = 1;

NCP_RETURN_LABEL
    return(ncpStatus);    
}

ncp_st_t
ncp_task_lite_uboot_config_tqs_struct()
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    
     /* 
      * Configure 1 thread queue set
      */
     pNcpNcaTaskGSM->threadQueueSet[0].id = 0;
     pNcpNcaTaskGSM->threadQueueSet[0].grpId = 0;
     pNcpNcaTaskGSM->threadQueueSet[0].taskSendQEntries = 16;
     pNcpNcaTaskGSM->threadQueueSet[0].taskCompletionQEntries = 16;
     pNcpNcaTaskGSM->threadQueueSet[0].receiveBufferQEntries = 16;               
     pNcpNcaTaskGSM->threadQueueSet[0].configurationQEntries = 16;  
     pNcpNcaTaskGSM->threadQueueSet[0].rxPool = 0;  
     pNcpNcaTaskGSM->threadQueueSet[0].qsAccessMode = NCP_NCA_QS_AVAILABLE;             
     pNcpNcaTaskGSM->threadQueueSet[0].tqsDomain = 0;   
     pNcpNcaTaskGSM->threadQueueSet[0].num_iPCQs_in_queueSet = 1;  
     pNcpNcaTaskGSM->threadQueueSet[0].first_iPCQ_id = 0; 
     pNcpNcaTaskGSM->threadQueueSet[0].inputQinfo[0].taskInputQEntries = 16;
     pNcpNcaTaskGSM->threadQueueSet[0].inputQinfo[0].rxTaskAutoComplete = 1;     

NCP_RETURN_LABEL
    return(ncpStatus);  
}


ncp_st_t
ncp_task_lite_uboot_config_grp_struct()
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    
    /*
     * Configure 1 pcq group
     */
     
    pNcpNcaTaskGSM->pcq_grp[0].id = 0;     
    pNcpNcaTaskGSM->pcq_grp[1].id = 0xff;   /* unused */
    pNcpNcaTaskGSM->pcq_grp[2].id = 0xff;   /* unused */
    pNcpNcaTaskGSM->pcq_grp[3].id = 0xff;   /* unused */
    pNcpNcaTaskGSM->pcq_grp[4].id = 0xff;   /* unused */
    pNcpNcaTaskGSM->pcq_grp[5].id = 0xff;   /* unused */
                        
    pNcpNcaTaskGSM->pcq_grp[0].grpDomain = 0;
    pNcpNcaTaskGSM->pcq_grp[0].pgitNormalLoadTimer = 0x1800; 
    pNcpNcaTaskGSM->pcq_grp[0].pgitNormalUploadTimer = 0x1800;  
    pNcpNcaTaskGSM->pcq_grp[0].pgitNcaEventLoadTimer = 0;
    pNcpNcaTaskGSM->pcq_grp[0].taskArrivalsPerInterrupt = 0;  
    pNcpNcaTaskGSM->pcq_grp[0].taskArrivalInterruptMaxDelayTime = 0; 
    pNcpNcaTaskGSM->pcq_grp[0].pgitIpcqEmptyToNotEmptyLoadTimer = 0; 
    pNcpNcaTaskGSM->pcq_grp[0].pgitCpuEventLoadTimer = 0; 
    pNcpNcaTaskGSM->pcq_grp[0].pgitTaskArrivalEventThreshold = 0; 
    pNcpNcaTaskGSM->pcq_grp[0].pgitOutputEventThreshold = 0; 
    
    pNcpNcaTaskGSM->pcq_grp[0].num_iPCQs = 1;
    pNcpNcaTaskGSM->pcq_grp[0].num_oPCQs = 1; 
    pNcpNcaTaskGSM->pcq_grp[0].num_cPCQs = 0;
    pNcpNcaTaskGSM->pcq_grp[0].num_tPCQs = 1;
    pNcpNcaTaskGSM->pcq_grp[0].num_rPCQs = 1;

    pNcpNcaTaskGSM->pcq_grp[0].default_tPCQ = 0;     
    
    
    
NCP_RETURN_LABEL
    return(ncpStatus);  
}


ncp_st_t
ncp_task_lite_uboot_set_nca_poke_and_timer_enable_reg(ncp_dev_t *dev,
                                ncp_uint8_t hw_load_poke_enab,
                                ncp_uint8_t hw_upload_poke_enab,
                                ncp_uint8_t cpcq_poke_enable,
                                ncp_uint8_t tpcq_poke_enable,
                                ncp_uint8_t opcq_poke_enable,
                                ncp_uint8_t ipcq_poke_enable,                                                                
                                ncp_uint8_t grpMask,                                
                                ncp_uint8_t grp_load_enab,
                                ncp_uint8_t grp_upload_enab)
 {
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;
    ncp_nca_hw_poke_and_timer_enable_reg_t regVal32;
    
    NCP_DEV_NCA_READ_REG32(dev, NCP_REGION_NCA_AXI, NCP_NCA_HW_POKE_AND_TIMER_ENABLE, (ncp_uint32_t *)&regVal32);
    if (hw_load_poke_enab)
    {    
        regVal32.hardware_load_poke_en   |= grpMask;
    }
    else
    {
        regVal32.hardware_load_poke_en   &= ~grpMask;        
    }
    if (hw_upload_poke_enab)
    {
        regVal32.hardware_upload_poke_en |= grpMask;
    }
    else
    {
        regVal32.hardware_upload_poke_en &= ~grpMask;        
    }    
    regVal32.cpcq_poke_enable        = cpcq_poke_enable;
    regVal32.tpcq_poke_enable        = tpcq_poke_enable;
    regVal32.opcq_poke_enable        = opcq_poke_enable;
    regVal32.ipcq_poke_enable        = ipcq_poke_enable;            
    if (grpMask & (1<<0)) /* group 0 */
    {
        regVal32.grp0_load_timer_en     = grp_load_enab;
        regVal32.grp0_upload_timer_en   = grp_upload_enab;    
    }
    if (grpMask & (1<<1)) /* group 1 */
    {
        regVal32.grp1_load_timer_en     = grp_load_enab;
        regVal32.grp1_upload_timer_en   = grp_upload_enab;    
    }
    if (grpMask & (1<<2)) /* group 2 */
    {
        regVal32.grp2_load_timer_en     = grp_load_enab;
        regVal32.grp2_upload_timer_en   = grp_upload_enab;    
    }
    if (grpMask & (1<<3)) /* group 3 */
    {
        regVal32.grp3_load_timer_en     = grp_load_enab;
        regVal32.grp3_upload_timer_en   = grp_upload_enab;    
    }
    if (grpMask & (1<<4)) /* group 4 */
    {
        regVal32.grp4_load_timer_en     = grp_load_enab;
        regVal32.grp4_upload_timer_en   = grp_upload_enab;    
    }
    if (grpMask & (1<<5)) /* group 5 */
    {
        regVal32.grp5_load_timer_en     = grp_load_enab;
        regVal32.grp5_upload_timer_en   = grp_upload_enab;    
    }
    NCP_DEV_NCA_WRITE_INDIRECT_REG32(dev, NCP_REGION_NCA_AXI,  (ncp_uint64_t)NCP_NCA_HW_POKE_AND_TIMER_ENABLE, (ncp_uint32_t *)&regVal32);
 
NCP_RETURN_LABEL
    return(ncpStatus);   
}   

  
ncp_st_t
ncp_task_lite_uboot_pcq_hw_init(
    ncp_dev_t *dev, 
    ncp_uint32_t pcqType,
    ncp_bool_t   enable,
    ncp_uint32_t queueId,
    ncp_uint32_t numEntries,
    ncp_uint32_t rxBufferPoolId,
    ncp_uint64_t baseAddr )
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_nca_PCQ_desc_reg0_t pcq_desc_r0;
    ncp_nca_PCQ_desc_reg1_t pcq_desc_r1;
    ncp_uint32_t offset;


    /* find the register offset for this queue */
    switch (pcqType) {
        case NCP_TASK_PCQ_INPUT:
            offset = NCP_NCA_PCQ_DESC_IPCQ_R0(queueId);
            break;

        case NCP_TASK_PCQ_OUTPUT:
            offset = NCP_NCA_PCQ_DESC_OPCQ_R0(queueId);
            break;

        case NCP_TASK_PCQ_COMPLETION:
            offset = NCP_NCA_PCQ_DESC_TPCQ_R0(queueId);
            break;

        case NCP_TASK_PCQ_RX_BUFFER:
            offset = NCP_NCA_PCQ_DESC_RPCQ_R0(queueId);
            break;

        case NCP_TASK_PCQ_CONFIG:
            offset = NCP_NCA_PCQ_DESC_CPCQ_R0(queueId);
            break;

        default:
            NCP_CALL_LITE(NCP_ST_ERROR);
    }

    NCP_DEV_NCA_READ_REG32(dev, NCP_REGION_NCA_AXI, offset, ((ncp_uint32_t *)&pcq_desc_r0));
    NCP_DEV_NCA_READ_REG32(dev, NCP_REGION_NCA_AXI, offset+4, ((ncp_uint32_t *)&pcq_desc_r1));    

    /* set up the registers */
    pcq_desc_r0.number_of_queue_entries = numEntries;
    pcq_desc_r0.enable_bit = enable;
    pcq_desc_r0.reserved0 = 0;    /* ??? - do we really need a read/write combo so as to not disturb or is writing 0s OK? */
    pcq_desc_r0.qentry_bar_upper = ((ncp_uint32_t) (baseAddr >> 32)) & 0x3f;    /* top 6 bits of 38bit address */

    if ((NCP_TASK_PCQ_RX_BUFFER == pcqType) || (NCP_TASK_PCQ_INPUT == pcqType))
    {
        pcq_desc_r0.rbpid =  rxBufferPoolId;
    }
    else
    {  
        pcq_desc_r0.rbpid =  0;        
    }

    pcq_desc_r1.qentry_bar_lower = (ncp_uint32_t) (baseAddr & 0xffffffffULL);

    NCP_DEV_NCA_WRITE_INDIRECT_REG32(dev, NCP_REGION_NCA_AXI,  offset, ((ncp_uint32_t *)&pcq_desc_r0));
    NCP_DEV_NCA_WRITE_INDIRECT_REG32(dev, NCP_REGION_NCA_AXI,  offset+4, (ncp_uint32_t *)&pcq_desc_r1);

#ifndef NCP_KERNEL
#if 0
    printf("pcq_hw_init,  baseAddr=0x%llx/0x%lx-0x%lx, entries=%d, enabled=%d\r\n",
	   baseAddr,
	   in_be32(NCA+offset), in_be32(NCA+offset+4),
	   numEntries,
	   enable);
#endif
#endif

NCP_RETURN_LABEL
    return ncpStatus;
}

/*
 * Hw recommends setting r0 and r1 early,   and r2..r5 later in the init process
 */
 
ncp_st_t
ncp_task_lite_uboot_pcq_group_init_base_addresses(
    ncp_dev_t *dev, 
    ncp_uint32_t groupId)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_uint64_t pgitBarAddr;
    ncp_uint64_t cpuPgitBarAddr;
    ncp_dev_pcq_grp_init_t pcq_grp_init = {{0}}; 


    /*
     * Convert PGIT VAs to PAs suitable for programming into NCA base registers
     */
     
    if ((NULL == pNcpNcaTaskGSM->pcq_grp[groupId].pNca_pgit) || (NULL == pNcpNcaTaskGSM->pcq_grp[groupId].pCpu_pgit))
    {
        pgitBarAddr     = 0x0LL;    /* This group is not used,   go ahead and provide reasonably sane values anyway */
        cpuPgitBarAddr  = 0x0LL;    /* This group is not used,   go ahead and provide reasonably sane values anyway */
        
    }        
    else
    {    

        /* 
         * Compute PGIT Phys Addrs
         */

         pgitBarAddr     = NCP_NCA_VA_2_PA_LITE(
            (void *)(pNcpNcaTaskGSM->pcq_grp[groupId].pNca_pgit)); 
   
         cpuPgitBarAddr  = NCP_NCA_VA_2_PA_LITE(
            (void *)(pNcpNcaTaskGSM->pcq_grp[groupId].pCpu_pgit));

#ifndef NCP_KERNEL
#if 0
         printf("Program pgit bars nca va=%p, pa=%llx, cpu va=%p, pa=%llx\r\n",
            pNcpNcaTaskGSM->pcq_grp[groupId].pNca_pgit,
            pgitBarAddr,
            pNcpNcaTaskGSM->pcq_grp[groupId].pCpu_pgit,
            cpuPgitBarAddr);
#endif
#endif

    }


    /*
     * program nca and cpu pgit base address registers with 38 bit physaddr 
     */
     
    pcq_grp_init.r2.pgit_bar_upper = (ncp_uint32_t)   ((pgitBarAddr >> 32) & (0x0000003F));    /* 6 bits */
    pcq_grp_init.r3.pgit_bar_lower = (ncp_uint32_t)      ((pgitBarAddr & 0xffffffc0) >> 6);       /* 26 significant bits + lower 6 all zero */

    pcq_grp_init.r4.cpu_pgit_bar_upper = (ncp_uint32_t)  ((cpuPgitBarAddr >> 32) & (0x0000003F)); /* 6 bits */
    pcq_grp_init.r5.cpu_pgit_bar_lower = (ncp_uint32_t)  ((cpuPgitBarAddr & 0xffffffc0) >> 6);    /* 26 significant bits + lower 6 all zero */


    
    NCP_DEV_NCA_WRITE_INDIRECT_REG32(dev, NCP_REGION_NCA_AXI,  NCP_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R2(groupId), (ncp_uint32_t *)&pcq_grp_init.r2);
    NCP_DEV_NCA_WRITE_INDIRECT_REG32(dev, NCP_REGION_NCA_AXI,  NCP_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R3(groupId), (ncp_uint32_t *)&pcq_grp_init.r3);
    NCP_DEV_NCA_WRITE_INDIRECT_REG32(dev, NCP_REGION_NCA_AXI,  NCP_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R4(groupId), (ncp_uint32_t *)&pcq_grp_init.r4);
    NCP_DEV_NCA_WRITE_INDIRECT_REG32(dev, NCP_REGION_NCA_AXI,  NCP_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R5(groupId), (ncp_uint32_t *)&pcq_grp_init.r5);
            
NCP_RETURN_LABEL
    return ncpStatus;
}



/*
 * Hw recommends setting r0 and r1 early,   and r2..r5 later in the init process
 */
 
ncp_st_t
ncp_task_lite_uboot_pcq_group_init(
    ncp_dev_t *dev, 
    int i,
    ncp_int32_t domain,
    ncp_bool_t warmRestart)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_dev_pcq_grp_init_t pcq_grp_init = {{0}}; 
    ncp_dev_pcq_grp_t *pPCQgrp = &pNcpNcaTaskGSM->pcq_grp[i];
    ncp_uint32_t groupId = pPCQgrp->id;
    
    if (!warmRestart)
    {    

        if ((pNcpNcaTaskGSM->myDomain != 0) &&  (pNcpNcaTaskGSM->myDomain != domain))
        {
            pNcpNcaTaskGSM->hw.nca_pgit[groupId].u_ptr  
             = pNcpNcaTaskGSM->hw.nca_pgit[groupId].k_ptr  
             = NULL;
            goto ncp_return;
        }

        /*
         * We must program the # of queues in groups managed by the other domains,
         * so that the NCA and S/W's view of queue numbers is consistent.
         */
    
        pcq_grp_init.r0.num_out_queues            = pPCQgrp->num_oPCQs;
        pcq_grp_init.r0.num_in_queues             = pPCQgrp->num_iPCQs;
        pcq_grp_init.r1.num_config_queues         = pPCQgrp->num_cPCQs; 
        pcq_grp_init.r1.num_rx_buffer_pool_queues = pPCQgrp->num_rPCQs; 
        pcq_grp_init.r1.num_tcomp_queues          = pPCQgrp->num_tPCQs; 
        
        
        NCP_DEV_NCA_WRITE_INDIRECT_REG32(dev, NCP_REGION_NCA_AXI,  NCP_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R0(groupId), (ncp_uint32_t *)&pcq_grp_init.r0);
        NCP_DEV_NCA_WRITE_INDIRECT_REG32(dev, NCP_REGION_NCA_AXI,  NCP_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R1(groupId), (ncp_uint32_t *)&pcq_grp_init.r1);
    
    
        if (pNcpNcaTaskGSM->myDomain != domain)
        {
            pNcpNcaTaskGSM->hw.nca_pgit[groupId].u_ptr  
             = pNcpNcaTaskGSM->hw.nca_pgit[groupId].k_ptr  
             = NULL;
            goto ncp_return;
        }

    
        NCP_ASSERT_LITE( NULL != (pNcpNcaTaskGSM->hw.nca_pgit[groupId].u_ptr =         
                    task_lite_alloc_aligned_fn(sizeof(ncp_dev_nca_pgit_t))),
                NCP_ST_TASK_NO_CACHE_ALLLIGNED_MEM);  
    
        memset(pNcpNcaTaskGSM->hw.nca_pgit[groupId].u_ptr, 0, sizeof(ncp_dev_nca_pgit_t));
        
        pPCQgrp->pNca_pgit = pNcpNcaTaskGSM->hw.nca_pgit[groupId].u_ptr;
    
        NCP_ASSERT_LITE( NULL != (pNcpNcaTaskGSM->hw.cpu_pgit[groupId].u_ptr =     
                    task_lite_alloc_aligned_fn(sizeof(ncp_dev_cpu_pgit_t))),
                NCP_ST_TASK_NO_CACHE_ALLLIGNED_MEM);
       
        memset(pNcpNcaTaskGSM->hw.cpu_pgit[groupId].u_ptr, 0, sizeof(ncp_dev_cpu_pgit_t));
         
        pPCQgrp->pCpu_pgit = pNcpNcaTaskGSM->hw.cpu_pgit[groupId].u_ptr;    


        /*
        * Configure NCA/CPU PGIT base addresses
        */
        NCP_CALL_LITE(ncp_task_lite_uboot_pcq_group_init_base_addresses(                      dev, 
                    groupId));
    
        /* 
         * Program NCA PGIT cpu load timer 
         */
        NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,  
                                NCP_NCA_PGIT_GRP_LOAD_TIMER(groupId), 
                                pPCQgrp->pgitNormalLoadTimer);
                                    
        /* 
         * Program NCA PGIT nca upload timer 
         */
        NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,  
                                NCP_NCA_PGIT_GRP_UPLOAD_TIMER(groupId), 
                                pPCQgrp->pgitNormalUploadTimer);
         
        /* 
         * Program Interrupt Aggregation Register
         */
        { 
            ncp_nca_int_param_grp_reg_t  intAggregationReg;
            ncp_uint32_t                 *pReg32 = (ncp_uint32_t *)&intAggregationReg; 
            
            *pReg32 = 0;
            intAggregationReg.wtask = pPCQgrp->taskArrivalsPerInterrupt;        
            intAggregationReg.wtime = pPCQgrp->taskArrivalInterruptMaxDelayTime;
            NCP_DEV_NCA_WRITE_INDIRECT_REG32(dev, NCP_REGION_NCA_AXI,  
                                NCP_NCA_INT_PARAM_GRP(groupId), 
                                pReg32);
        }
    } /* !warmRestart */
    
#ifndef NCP_KERNEL
#if 0
    printf("pcq_grp_init:  grp=%d, pNcpNcaTaskGSM->hw.nca_pgit[groupId].u_ptr=%p, pNcpNcaTaskGSM->hw.cpu_pgit[groupId].u_ptr=%p, pPCQgrp->pNca_pgit=%p, pPCQgrp->pCpu_pgit=%p\r\n",
        groupId,
        pNcpNcaTaskGSM->hw.nca_pgit[groupId].u_ptr,
        pNcpNcaTaskGSM->hw.cpu_pgit[groupId].u_ptr,
        pPCQgrp->pNca_pgit,
        pPCQgrp->pCpu_pgit);
#endif
#endif
NCP_RETURN_LABEL
    return ncpStatus;
}   
   
ncp_st_t
ncp_task_lite_uboot_set_nca_load_indexes_reg(ncp_dev_t *dev,
                                 ncp_uint8_t activeGrpMask)
{
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;
    ncp_nca_pgit_load_grp_indexes_reg_t regVal32;
    
    NCP_DEV_NCA_READ_REG32(dev, NCP_REGION_NCA_AXI, NCP_NCA_PGIT_LOAD_GRP_INDEXES, (ncp_uint32_t *)&regVal32);
    regVal32.load_nca_index_grp  |= activeGrpMask;
    regVal32.load_cpu_index_grp  |= activeGrpMask;    
    NCP_DEV_NCA_WRITE_INDIRECT_REG32(dev, NCP_REGION_NCA_AXI,  NCP_NCA_PGIT_LOAD_GRP_INDEXES, (ncp_uint32_t *)&regVal32);
 
NCP_RETURN_LABEL
    return(ncpStatus);   
} 
 
#ifdef TASKIOLITE_USES_UBOOT_CFG  
void * myAllocAligned(size)
{
    void *pMem;
    ncp_alloc_cache_aligned(&pMem,size);
    return(pMem);    
}
#endif 

ncp_st_t
ncp_task_lite_uboot_register_allocators(
            ncp_task_lite_alloc_128B_aligned_fn_t task_lite_client_alloc_128B_aligned,
            ncp_task_lite_free_128B_aligned_fn_t  task_lite_client_free_128B_aligned,
            ncp_task_lite_alloc_nvm_fn_t          task_lite_client_alloc_nvm,
            ncp_task_lite_free_nvm_fn_t           task_lite_client_free_nvm,             
            ncp_task_lite_va_2_pa_fn_t            task_lite_va_2_pa)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

#ifdef TASKIOLITE_USES_UBOOT_CFG     
    if (NULL == (task_lite_alloc_aligned_fn      = task_lite_client_alloc_128B_aligned))
    {    
       task_lite_alloc_aligned_fn = myAllocAligned;
    }    
    if (NULL == (task_lite_free_aligned_fn       = task_lite_client_free_128B_aligned))
    {
        /* No default replacement */
    }
    if (NULL == (task_lite_alloc_nvm_fn          = task_lite_client_alloc_nvm))
    {
        task_lite_alloc_nvm_fn = ncp_nvm_malloc;    
    }    
    if (NULL == (task_lite_free_nvm_fn           = task_lite_client_free_nvm))   
    {
        task_lite_free_nvm_fn = ncp_nvm_free;
    }            
    if (NULL == (task_lite_va_2_pa_fn            = task_lite_va_2_pa))
    {
        task_lite_va_2_pa_fn = ncp_nca_va_2_pa;    
    }    
#else
    task_lite_alloc_aligned_fn = task_lite_client_alloc_128B_aligned;
    task_lite_free_aligned_fn       = task_lite_client_free_128B_aligned;
    task_lite_alloc_nvm_fn          = task_lite_client_alloc_nvm;
    task_lite_free_nvm_fn           = task_lite_client_free_nvm;
    task_lite_va_2_pa_fn            = task_lite_va_2_pa;
#endif    

NCP_RETURN_LABEL
    return ncpStatus;
}   

#ifdef TASKIOLITE_USES_UBOOT_CFG  
myRegisterAllocators()
{
    ncp_task_lite_uboot_register_allocators(
            ( ncp_task_lite_alloc_128B_aligned_fn_t) myAllocAligned,
            ( ncp_task_lite_free_128B_aligned_fn_t) NULL,
            ( ncp_task_lite_alloc_nvm_fn_t) ncp_nvm_malloc,
            ( ncp_task_lite_free_nvm_fn_t) ncp_nvm_free,             
            ( ncp_task_lite_va_2_pa_fn_t) ncp_nca_va_2_pa);    
}    
#endif


ncp_st_t
ncp_task_lite_uboot_program_rxPoolSizes(ncp_dev_hdl_t   dev, 
                                ncp_uint8_t     id,
                                ncp_uint16_t    size0,
                                ncp_uint16_t    size1,
                                ncp_uint16_t    size2,
                                ncp_uint16_t    size3)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_nca_rcv_buff_pool_size_reg_a_t ncp_nca_rcv_buff_pool_size_reg_a;
    ncp_nca_rcv_buff_pool_size_reg_b_t ncp_nca_rcv_buff_pool_size_reg_b;



    ncp_nca_rcv_buff_pool_size_reg_a.rbuff_size_0 = size0;    
    ncp_nca_rcv_buff_pool_size_reg_a.rbuff_size_1 = size1;    
    
    NCP_DEV_NCA_WRITE_INDIRECT_REG32(dev, NCP_REGION_NCA_AXI,  NCP_NCA_RCV_BUFF_POOL_SIZE_0_1_R(id),              
                                     (ncp_uint32_t *)&ncp_nca_rcv_buff_pool_size_reg_a);       /* TODO --- hardcoded right now */

    ncp_nca_rcv_buff_pool_size_reg_b.rbuff_size_2 = size2;   
    
    /* special case where user selected 64k as the largest buffer */ 
    /* ASE really should not allow configuring a buffer to be this large (17 bits) */
    if (0 == size3)
    {
        size3 = 0xffff; /* we only have 16 bits */
    }
    
    ncp_nca_rcv_buff_pool_size_reg_b.rbuff_size_3 = size3;    
    
    NCP_DEV_NCA_WRITE_INDIRECT_REG32(dev, NCP_REGION_NCA_AXI,  NCP_NCA_RCV_BUFF_POOL_SIZE_2_3_R(id), 
                                    (ncp_uint32_t *)&ncp_nca_rcv_buff_pool_size_reg_b);       /* TODO --- hardcoded right now */

NCP_RETURN_LABEL
    return(ncpStatus);    
}

ncp_st_t
ncp_task_lite_uboot_set_nca_config_init_reg(ncp_dev_t *dev,    
                                  ncp_uint8_t init_done,                                 
                                  ncp_uint8_t tfc_compl_cnt_reset,                       
                                  ncp_uint8_t tfc_flush,                                 
                                  ncp_uint8_t cpcq_en,                                   
                                  ncp_uint8_t otask_accum_en,                            
                                  ncp_uint8_t itask_accum_en,                            
                                  ncp_uint8_t tfc_en,                                    
                                  ncp_uint8_t otbp_soft_reset,                           
                                  ncp_uint8_t rbp_soft_reset,                            
                                  ncp_uint8_t rbp_en,                                    
                                  ncp_uint8_t opcq_cons_ent,                             
                                  ncp_uint8_t opcq_num_beat,                             
                                  ncp_uint8_t ipcq_num_beat,                             
                                  ncp_uint8_t tpcq_num_beat,                             
                                  ncp_uint8_t rpcq_num_beat,                             
                                  ncp_uint8_t pgit_w_num_beat,                           
                                  ncp_uint8_t pgit_r_num_beat)
                                 
 
{
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;
    ncp_nca_config_init_reg_t regVal32;
    
    NCP_DEV_NCA_READ_REG32(dev, NCP_REGION_NCA_AXI, NCP_NCA_CONFIG_INIT, (ncp_uint32_t *)&regVal32);     

    /* regVal32.reserved 1 bit                                          */     /* 1 bit */
    /* regVal32.cfg_ring_ack_timer_en      =   cfg_ring_ack_timer_en;   */     /* don't walk on prev setting */
    regVal32.tfc_compl_cnt_reset        =   tfc_compl_cnt_reset;       
    regVal32.tfc_flush                  =   tfc_flush;           
    regVal32.cpcq_en                    =   cpcq_en;          
    regVal32.otask_accum_en             =   otask_accum_en;          
    regVal32.itask_accum_en             =   itask_accum_en;          
    regVal32.tfc_en                     =   tfc_en;          
    regVal32.otbp_soft_reset            =   otbp_soft_reset;          
    regVal32.rbp_soft_reset             =   rbp_soft_reset;          
    regVal32.rbp_en                     =   rbp_en;    
    /* regVal32.reserved0 */                                            /* 4 bits */       
    regVal32.opcq_cons_ent              =   opcq_cons_ent;              /* 4 bits */  
    regVal32.opcq_num_beat              =   opcq_num_beat;              /* 2 bits */
    regVal32.ipcq_num_beat              =   ipcq_num_beat;              /* 2 bits */
    regVal32.tpcq_num_beat              =   tpcq_num_beat;              /* 2 bits */
    regVal32.rpcq_num_beat              =   rpcq_num_beat;              /* 2 bits */
    regVal32.pgit_w_num_beat            =   pgit_w_num_beat;            /* 2 bits */
    regVal32.pgit_r_num_beat            =   pgit_r_num_beat;            /* 2 bits */
#if 0
    regVal32.init_done                  =   init_done;                  /* 1 bit */
#endif

    NCP_DEV_NCA_WRITE_INDIRECT_REG32(dev, NCP_REGION_NCA_AXI,  (ncp_uint64_t)NCP_NCA_CONFIG_INIT, (ncp_uint32_t *)&regVal32);

NCP_RETURN_LABEL
    return(ncpStatus);    
}
    
ncp_st_t
ncp_task_lite_uboot_disable_PCQs(ncp_dev_hdl_t dev, ncp_bool_t primaryDomain)
{
    int i;
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    
    for (i=0; i<NCP_X1_NUM_HW_INPUT_QUEUES; i++)
    {
       NCP_CALL_LITE(ncp_task_lite_uboot_pcq_hw_init(
         dev, 
         NCP_TASK_PCQ_INPUT,
         FALSE,
         i,
         16,
         0,
         0LL));        
    }    
    for (i=0; i<NCP_X1_NUM_HW_NONINPUT_QUEUES; i++)
    {
       NCP_CALL_LITE(ncp_task_lite_uboot_pcq_hw_init(
         dev, 
         NCP_TASK_PCQ_OUTPUT,
         FALSE,
         i,
         16,
         0,
         0LL));        
    
       NCP_CALL_LITE(ncp_task_lite_uboot_pcq_hw_init(
        dev, 
        NCP_TASK_PCQ_RX_BUFFER,
        FALSE,
        i,
        16,
        0,
        0LL));    
        
      NCP_CALL_LITE(ncp_task_lite_uboot_pcq_hw_init(
        dev, 
        NCP_TASK_PCQ_CONFIG,
        FALSE,
        i,
        16,
        0,
        0LL));             
    
      NCP_CALL_LITE(ncp_task_lite_uboot_pcq_hw_init(
        dev, 
        NCP_TASK_PCQ_COMPLETION,
        FALSE,
        i,
        16,
        0,
        0LL));        
    } /* for */

        
NCP_RETURN_LABEL
    return(ncpStatus);    
}

ncp_st_t
ncp_task_lite_uboot_ipcq_init(
    ncp_dev_t         *dev,
    ncp_uint32_t       groupId,
    ncp_uint32_t       queueId,
    ncp_uint8_t        linearQueueId,
    ncp_uint32_t       nEntries,
    ncp_uint8_t        auto_complete,
    ncp_uint8_t        pool,
    ncp_uint32_t       umode,
    ncp_int32_t        domain,
    ncp_bool_t         warmRestart)
{
    ncp_st_t              ncpStatus = NCP_ST_SUCCESS;
    ncp_dev_pcq_grp_t    *pPCQgrp = &pNcpNcaTaskGSM->pcq_grp[groupId];
    ncp_task_pcq_t        *pcq = &pNcpNcaTaskGSM->iPCQs[linearQueueId];



    if (!warmRestart)
    {
        memset(pcq, 0, sizeof(ncp_task_pcq_t));
    
        if (pNcpNcaTaskGSM->myDomain != domain)
        {
            goto ncp_return;
        }
    

        NCP_ASSERT_LITE( NULL != 
           (pNcpNcaTaskGSM->hw.NcaInputQueues[linearQueueId].entries =           
                task_lite_alloc_aligned_fn(nEntries * sizeof(ncp_task_iPCQ_entry_t))),
           NCP_ST_TASK_NO_CACHE_ALLLIGNED_MEM);
                
        pcq->u_pPCQbase = &(pNcpNcaTaskGSM->hw.NcaInputQueues[linearQueueId].entries[0]); 
        pcq->baseBusAddr = NCP_NCA_VA_2_PA_LITE(pcq->P_PCQ_BASE);

        pcq->nEntries  = nEntries;
        pcq->grpId     = groupId;    
        pcq->ncaQueueId  = linearQueueId; 
        pcq->CONSUMER_PTR = &pPCQgrp->pCpu_pgit->i_cIdx[queueId]; 
        pcq->PRODUCER_PTR = &pPCQgrp->pNca_pgit->i_pIdx[queueId]; 
        /* fixup for kernel pointers */

         
        pcq->u.ipcq_info.rxTaskAutoComplete = auto_complete; 
        memset((void *)&(pcq->u.ipcq_info.taskCompletionInfo), 0,     
            sizeof(ncp_task_tPCQ_entry_t));    
        
        pcq->u.ipcq_info.pIPCQentry = pcq->u_pPCQbase; 
        pcq->ncaQ = pcq;            

        NCP_CALL_LITE(ncp_task_lite_uboot_pcq_hw_init(dev, NCP_TASK_PCQ_INPUT, TRUE,
                                 linearQueueId, nEntries, pool, pcq->baseBusAddr));
   } /* !warmRestart */
     
#ifndef NCP_KERNEL
#if 0
   printf("ipcq_init, pcq=%p, CONSUMER=%p, PRODUCER=%p, ncaQueueid=%d, nEntries=%d, grpId=%d, base=%p\r\n",
        pcq, pcq->CONSUMER_PTR, pcq->PRODUCER_PTR, pcq->ncaQueueId, pcq->nEntries, pcq->grpId, pcq->u_pPCQbase);
#endif
#endif

NCP_RETURN_LABEL
    return ncpStatus;
}

/*
 * Output queue init
 */

ncp_st_t
ncp_task_lite_uboot_opcq_init(
    ncp_dev_t         *dev,
    ncp_uint32_t       groupId,
    ncp_uint32_t       queueId,
    ncp_uint8_t        linearQueueId,
    ncp_uint32_t       nEntries,
    ncp_uint32_t       umode,
    ncp_int32_t        domain,
    ncp_bool_t         warmRestart)   
{
    ncp_st_t              ncpStatus = NCP_ST_SUCCESS;
    ncp_dev_pcq_grp_t    *grp = &pNcpNcaTaskGSM->pcq_grp[groupId];
    ncp_task_pcq_t        *pcq = &pNcpNcaTaskGSM->oPCQs[linearQueueId];
 
    if (!warmRestart)
    {
        memset(pcq, 0, sizeof(ncp_task_pcq_t));
        
    
        if (pNcpNcaTaskGSM->myDomain != domain)
        {
            goto ncp_return;
        }


        NCP_ASSERT_LITE( NULL != 
           (pNcpNcaTaskGSM->hw.NcaOutputQueues[linearQueueId].entries =           
                task_lite_alloc_aligned_fn(nEntries *  sizeof(ncp_task_oPCQ_entry_t))),
           NCP_ST_TASK_NO_CACHE_ALLLIGNED_MEM);
           
        pcq->u_pPCQbase     = 
            &(pNcpNcaTaskGSM->hw.NcaOutputQueues[linearQueueId].entries[0]); 
        pcq->baseBusAddr = NCP_NCA_VA_2_PA_LITE(pcq->P_PCQ_BASE);           
        
        pcq->nEntries  = nEntries;
        pcq->grpId     = groupId;
        pcq->ncaQueueId  = linearQueueId;   
        pcq->PRODUCER_PTR = &grp->pCpu_pgit->o_pIdx[queueId];
        pcq->CONSUMER_PTR = &grp->pNca_pgit->o_cIdx[queueId];
  
        
        pcq->u.opcq_info.taskCnt = 0; /* Init task completion index and counter */
        pcq->u.opcq_info.intransitTasksIdx    = 0;
        pcq->u.opcq_info.intransitSlotsAvail  = nEntries - 2;  
        
        pcq->u.opcq_info.pOPCQentry = pcq->u_pPCQbase; 
        pcq->ncaQ = pcq;            

        NCP_CALL_LITE(ncp_task_lite_uboot_pcq_hw_init(dev, NCP_TASK_PCQ_OUTPUT, TRUE,
                                 linearQueueId, nEntries, 0, pcq->baseBusAddr));

    } /* !warmRestart */
    
#ifndef NCP_KERNEL
#if 0
   printf("opcq_init, pcq=%p, CONSUMER=%p, PRODUCER=%p, ncaQueueid=%d, nEntries=%d, grpId=%d, base=%p\r\n",
        pcq, pcq->CONSUMER_PTR, pcq->PRODUCER_PTR, pcq->ncaQueueId, pcq->nEntries, pcq->grpId, pcq->u_pPCQbase);
#endif
#endif

NCP_RETURN_LABEL
    return ncpStatus;
}


/*
 * Task Completion queue init
 */

ncp_st_t
ncp_task_lite_uboot_tpcq_init(
    ncp_dev_t         *dev,
    ncp_uint32_t       groupId,
    ncp_uint32_t       queueId,
    ncp_uint8_t        linearQueueId,    
    ncp_uint32_t       nEntries,
    ncp_uint32_t       umode,
    ncp_int32_t        domain,
    ncp_bool_t         warmRestart) 
{
    ncp_st_t              ncpStatus = NCP_ST_SUCCESS;
    ncp_dev_pcq_grp_t    *grp = &pNcpNcaTaskGSM->pcq_grp[groupId];
    ncp_task_pcq_t        *pcq = &pNcpNcaTaskGSM->tPCQs[linearQueueId];


    if (!warmRestart)
    {
        memset(pcq, 0, sizeof(ncp_task_pcq_t));
    
    
        if (pNcpNcaTaskGSM->myDomain != domain)
        {
            goto ncp_return;
        }

        NCP_ASSERT_LITE( NULL != 
           (pNcpNcaTaskGSM->hw.NcaTaskCompletionQueues[linearQueueId].entries =           
                task_lite_alloc_aligned_fn(nEntries *  sizeof(ncp_task_tPCQ_entry_t))),
           NCP_ST_TASK_NO_CACHE_ALLLIGNED_MEM);
        
        pcq->u_pPCQbase = 
            &(pNcpNcaTaskGSM->hw.NcaTaskCompletionQueues[linearQueueId].entries[0]); 
        
        pcq->baseBusAddr = NCP_NCA_VA_2_PA_LITE(pcq->P_PCQ_BASE);

        pcq->nEntries  = nEntries;
        pcq->grpId     = groupId;    
        pcq->ncaQueueId  = linearQueueId;    
        pcq->PRODUCER_PTR = &grp->pCpu_pgit->t_pIdx[queueId];
        pcq->CONSUMER_PTR = &grp->pNca_pgit->t_cIdx[queueId];
    
    
        pcq->u.tpcq_info.pTPCQentry = pcq->u_pPCQbase; 
        pcq->ncaQ = pcq;            

        NCP_CALL_LITE(ncp_task_lite_uboot_pcq_hw_init(dev, NCP_TASK_PCQ_COMPLETION, TRUE,
                                 linearQueueId, nEntries, 0, pcq->baseBusAddr));
             
   } /* !warmRestart */

#ifndef NCP_KERNEL
#if 0
   printf("tpcq_init, pcq=%p, CONSUMER=%p, PRODUCER=%p, ncaQueueid=%d, nEntries=%d, grpId=%d, base=%p\r\n",
        pcq, pcq->CONSUMER_PTR, pcq->PRODUCER_PTR, pcq->ncaQueueId, pcq->nEntries, pcq->grpId, pcq->u_pPCQbase);
#endif
#endif
                                 
NCP_RETURN_LABEL
    return ncpStatus;
}



/*
 * Receive Buffer queue init
 */

ncp_st_t
ncp_task_lite_uboot_rpcq_init(
    ncp_dev_t         *dev,
    ncp_uint32_t       groupId,
    ncp_uint32_t       queueId,
    ncp_uint8_t        linearQueueId,    
    ncp_uint32_t       nEntries,
    ncp_uint8_t        rxPool,
    ncp_uint32_t       umode,
    ncp_int32_t        domain,
    ncp_bool_t         warmRestart)
    
{
    ncp_st_t              ncpStatus = NCP_ST_SUCCESS;
    ncp_dev_pcq_grp_t    *grp = &pNcpNcaTaskGSM->pcq_grp[groupId];
    ncp_task_pcq_t        *pcq = &pNcpNcaTaskGSM->rPCQs[linearQueueId];


    if (!warmRestart)
    {    
        memset(pcq, 0, sizeof(ncp_task_pcq_t));
        
    
        if (pNcpNcaTaskGSM->myDomain != domain)
        {
            goto ncp_return;
        }


        NCP_ASSERT_LITE( NULL != 
           (pNcpNcaTaskGSM->hw.NcaRxBufferQueues[linearQueueId].entries =           
                task_lite_alloc_aligned_fn(nEntries *  sizeof(ncp_task_rPCQ_entry_t))),
           NCP_ST_TASK_NO_CACHE_ALLLIGNED_MEM);

        pcq->u_pPCQbase = &(pNcpNcaTaskGSM->hw.NcaRxBufferQueues[linearQueueId].entries[0]);  
        pcq->baseBusAddr = NCP_NCA_VA_2_PA_LITE(pcq->P_PCQ_BASE);

        pcq->nEntries  = nEntries;
        pcq->grpId     = groupId;    
        pcq->ncaQueueId  = linearQueueId; 
        pcq->PRODUCER_PTR = &grp->pCpu_pgit->r_pIdx[queueId];
        pcq->CONSUMER_PTR = &grp->pNca_pgit->r_cIdx[queueId];

    
        pcq->u.rpcq_info.pRPCQentry = pcq->u_pPCQbase; 
        pcq->ncaQ = pcq;            
    
        NCP_CALL_LITE(ncp_task_lite_uboot_pcq_hw_init(dev,  NCP_TASK_PCQ_RX_BUFFER, TRUE,
                                 linearQueueId, nEntries, rxPool, pcq->baseBusAddr));
         
    } /* !warmRestart */

#ifndef NCP_KERNEL
#if 0
   printf("rpcq_init, pcq=%p, CONSUMER=%p, PRODUCER=%p, ncaQueueid=%d, nEntries=%d, grpId=%d, base=%p\r\n",
        pcq, pcq->CONSUMER_PTR, pcq->PRODUCER_PTR, pcq->ncaQueueId, pcq->nEntries, pcq->grpId, pcq->u_pPCQbase);
#endif
#endif
                                     
NCP_RETURN_LABEL
    return ncpStatus;
}

ncp_st_t ncp_task_lite_uboot_init_version_specific_features(ncp_dev_t *dev,
                                            ncp_uint32_t activeGroupMask,
                                            ncp_bool_t warmRestart)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_uint64_t otaskBackPressureBarAddr;         
    ncp_nca_otbp_bar_reg0_t r0;
    ncp_uint32_t * pR0 = (ncp_uint32_t *)&r0;
    ncp_nca_otbp_bar_reg1_t r1; 
    ncp_uint32_t * pR1 = (ncp_uint32_t *)&r1;
    int i;
    
    if (!warmRestart)
    {

        /* primary domain? */
        if (0 == pNcpNcaTaskGSM->myDomain)
        {
            /*
            * Backpressure changed in V2
            *
            * program nca and cpu pgit base address registers with 38 bit physaddr 
            */
     
            otaskBackPressureBarAddr     = 
                 NCP_NCA_VA_2_PA_LITE((ncp_uint32_t)(&pNcpNcaTaskGSM->otbpInfo)); 

            r0.otbp_bar_upper = (ncp_uint32_t)   ((otaskBackPressureBarAddr >> 32) & (0x0000003F));   /* 6 bits */
            r1.otbp_bar_lower = (ncp_uint32_t)   (otaskBackPressureBarAddr & 0xffffffff); /* Byte address */

            NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,NCP_NCA_OTBP_BAR_UPPER, *pR0);        
            NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,NCP_NCA_OTBP_BAR_LOWER, *pR1);          
    
            /*
            * Task Completions changed in V2
            */
    
            {
                ncp_nca_tfc_unordered_mode_reg_t reg_unordered_mode;
                ncp_uint32_t *pReg = (ncp_uint32_t *)&reg_unordered_mode;
                    
                reg_unordered_mode.tfc_unordered_mode_en = 1; 
                NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,  
                               NCP_NCA_TFC_UNORDERED_MODE,   
                               *pReg);              
            }      
    
        } /* primary domain */

        /*
        * ====== Program V2+ only Timer/Poke Related Registers ======
        */


        /* upload poke delay */
            
        NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,  
                        NCP_NCA_DELAY_GRP_UPLOAD_TIMER(0), 
                        0);

            
        /* load poke delay */
            
        NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,  
                        NCP_NCA_DELAY_GRP_LOAD_TIMER(0), 
                        0);

        /* ipcq empty to not empty poke timer*/

        NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,  
                        NCP_NCA_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER(0), 
                        0);
                        
        /* sw/CPU poke timer */            

        NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,  
                        NCP_NCA_SWPOKE_DELAY_GRP_LOAD_TIMER(0), 
                        0);

         /* iTask arrival counter threshold */
           
        NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,  
                        NCP_NCA_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR(0), 
                        0);

        /* output counter threshold */

        NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,  
                        NCP_NCA_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR(0), 
                        0);
           
    } /* !warmRestart */

    NCP_CALL_LITE(ncp_task_lite_uboot_set_nca_poke_and_timer_enable_reg(dev,
                            1,                                      /* hw_load_poke_enab    */
                            1,                                      /* hw_upload_poke_enab  */
                            1,                                      /* cpcq_poke_enable     */
                            1,                                      /* tpcq_poke_enable     */
                            1,                                      /* opcq_poke_enable     */
                            1,                                      /* ipcq_poke_enable     */  
                            activeGroupMask,                        /* group mask           */              
                            1,                                      /* grpX load enable     */
                            1));                                    /* grpX upload enable   */        
              
NCP_RETURN_LABEL

    return(ncpStatus);  
}
    
ncp_st_t
ncp_task_lite_uboot_config(ncp_dev_t   *dev)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_bool_t warmRestart = FALSE;
    int i;


#ifndef TASKIOLITE_USES_UBOOT_CFG 
    if (
        (NULL == task_lite_alloc_aligned_fn)
     || (NULL == task_lite_free_aligned_fn)
     || (NULL == task_lite_alloc_nvm_fn)
     || (NULL == task_lite_free_nvm_fn)     
     || (NULL == task_lite_va_2_pa_fn))
    {
        NCP_CALL_LITE(NCP_ST_TASK_LITE_UBOOT_NO_ALLOCATOR_REGISTERED);
    }     
#endif

    /*
     * Allocate minimal set of data structures
     */
     
    NCP_CALL_LITE(ncp_task_lite_uboot_config_mem());
    pNcpNcaTaskGSM->myDomain   = 0;
    pNcpNcaTaskGSM->ncpId      = 0;

    /*
     * Configure 1 pcq group
     */
    NCP_CALL_LITE(ncp_task_lite_uboot_config_grp_struct());
    
    /*
     * Configure 1 thread queue set
     */
    NCP_CALL_LITE(ncp_task_lite_uboot_config_tqs_struct());
     
    /*
     * <<<=== Start NCA Hardware Initialization ===>>> 
     */ 
     

    /* 
     * Config rxPool 0 
    */
    NCP_CALL_LITE(ncp_task_lite_uboot_program_rxPoolSizes(dev, 
                                            0,
                                            256,
                                            512,
                                            1024,
                                            2048));    
    
    
    /*
    * Force all queues to be disabled,   
    */

    NCP_CALL_LITE(ncp_task_lite_uboot_disable_PCQs(dev, TRUE));  

    /* 
     * Configure group 0
     */
     
    NCP_CALL_LITE(ncp_task_lite_uboot_pcq_group_init(dev, 
                                                0,
                                                0,
                                                warmRestart)); 

    /* 
     * rpcq0 
     */
    
    NCP_CALL_LITE(ncp_task_lite_uboot_rpcq_init(dev, 
                        0, /* Group Id */
                        0, /* Queue Id - group relative */
                        0, /* flat id */
                        16, /* Depth */
                        0,  /* Which pool this queue feeds */
                        TRUE, /* user mode pool queue */       
                        0,    /* grpDomain */
                        warmRestart)); /* warm restart */
        
   /*
    *  tPCQ 
    */

    NCP_CALL_LITE(ncp_task_lite_uboot_tpcq_init(dev, 
                0,  /* Group Id */
                0,  /* Queue Id - group relative */
                0,  /* flat id */                            
                16, /* Depth */
                TRUE, /* user mode pool ? */       
                0, 
                warmRestart));


   /*
    * oPCQ
    */

    NCP_CALL_LITE(ncp_task_lite_uboot_opcq_init(dev, 
                0,  /* Group Id */
                0,  /* Queue Id - group relative */
                0,  /* flat id */                            
                16, /* Depth */
                TRUE, /* user mode pool ? */       
                0,
                warmRestart));

    /* We do not configure cPCQs for uboot */
            
    /*
     * Configure iPCQs within this group and queueSet
     */
     
    NCP_CALL_LITE(ncp_task_lite_uboot_ipcq_init(dev, 
                0,  /* Group Id */
                0,  /* Queue Id - group relative */
                0,  /* flat id */                          
                16, /* Depth */
                TRUE, /* Completion Mode */
                0,  /* rx buffer pool Id */
                TRUE, /* user mode pool ? */       
                0, 
                warmRestart));
                                
    pNcpNcaTaskGSM->allGrpMask      = (1<<0);
    pNcpNcaTaskGSM->activeGrpMask   = (1<<0);
            

    /*
     * Link thread queue set struct to physical queues
     */
    for (i = 0; i < NCP_X1_UBOOT_CFG_NUM_THREAD_QUEUESETS; i++)
    {

        ncp_nca_thread_queue_set_t *pThreadQueueSet = &pNcpNcaTaskGSM->threadQueueSet[i];
        
        if ((0xFF == pThreadQueueSet->id)  /* unused ? */
         || (pThreadQueueSet->tqsDomain != pNcpNcaTaskGSM->myDomain))
        {
            continue;
        }    
        NCP_CALL_LITE(ncp_task_map_queuenum_to_pcq(NCP_TASK_PCQ_COMPLETION, i, &pThreadQueueSet->p_tPCQ));             
        NCP_CALL_LITE(ncp_task_map_queuenum_to_pcq(NCP_TASK_PCQ_OUTPUT, i, &pThreadQueueSet->p_oPCQ));             
        NCP_CALL_LITE(ncp_task_map_queuenum_to_pcq(NCP_TASK_PCQ_RX_BUFFER, i, &pThreadQueueSet->p_rPCQ));   
    }       

#ifdef NCP_TASKIO_LITE_USE_BACKPRESSURE
    
    /* Backpressure ON for iPCQ0, bufSZ 3 */
    printf("%s:%d - \n", __FILE__, __LINE__); /* ZZZ */
    NCP_CALL_LITE(ncp_task_lite_uboot_set_rbp_backpressure(dev, 
                    TRUE, 
                    1, 
                    0x8));  
#else
    /* Backpressure OFF */
    NCP_CALL_LITE(ncp_task_lite_uboot_set_rbp_backpressure(dev, 
                    FALSE,
                    1, 
                    0));  

#endif
            
    NCP_CALL_LITE(ncp_task_lite_uboot_set_nca_config_init_reg(dev,    
          0,                   /* init_done,        1 bit  */  
          0,                   /* tfc_compl_cnt_reset,  1 bit  */  
          0,                   /* tfc_flush,        1 bit  */          
          0,                   /* cpcq_en,         1 bit  */       
          0,                   /* otask_accum_en,      1 bit  */       
          0,                   /* itask_accum_en,      1 bit  */       
          0,                   /* tfc_en,          1 bit  */       
          0,                   /* otbp_soft_reset,     1 bit  */       
          0,                   /* rbp_soft_reset,      1 bit  */       
          0,                   /* rbp_en,          1 bit  */       
          /*0x0*/ /*0000b*/        /* RESERVED         4 bits */
          0x1,                   /* opcq_cons_ent,       4 bits */       
          3,                   /* opcq_num_beat,       2 bits */        
          3,                   /* ipcq_num_beat,       2 bits */       
          3,                   /* tpcq_num_beat,       2 bits */       
          3,                   /* rpcq_num_beat,       2 bits */       
          3,                   /* pgit_w_num_beat,     2 bits */       
          3));                 /* pgit_r_num_beat      2 bits */  

    /* 
     * X1/V2 and beyond has different implementations/capabilities
     */
         
    ncp_task_lite_uboot_init_version_specific_features(
            dev, 
            pNcpNcaTaskGSM->activeGrpMask, 
            warmRestart);
   
  
    NCP_CALL_LITE(ncp_task_lite_uboot_set_nca_config_init_reg(dev,    
          1,                   /* init_done,        1 bit  */  
          0,                   /* tfc_compl_cnt_reset,  1 bit  */  
          0,                   /* tfc_flush,        1 bit  */          
          0,                   /* cpcp disabled */  
          1,                   /* otask_accum_en,      1 bit  */       
          1,                   /* itask_accum_en,      1 bit  */     
          1,                   /* tfc_en,          1 bit  */       
          0,                   /* otbp_soft_reset,     1 bit  */       
          0,                   /* rbp_soft_reset,      1 bit  */       
          1,                   /* rbp_en,          1 bit  */       
          /*0x0*/                  /* RESERVED         4 bits */
          0x1,  /*0001b*/        /* opcq_cons_ent,       4 bits */       
          3,                   /* opcq_num_beat,       2 bits */        
          3,                   /* ipcq_num_beat,       2 bits */       
          3,                   /* tpcq_num_beat,       2 bits */       
          3,                   /* rpcq_num_beat,       2 bits */       
          3,                   /* pgit_w_num_beat,     2 bits */       
          3));                 /* pgit_r_num_beat      2 bits */   

  
    /* 
     * Force an immediate PGIT refresh for the newly added groups.
     * Since a mask is used,   the operation will apply to all of them,
     * and need not be applied individually as queue groups are added.
     * Note that this is not part of the required NCA configuration process,
     * but rather it is optional,   and in this case serves as a possible
     * opimization.
     */
    NCP_CALL_LITE(ncp_task_lite_uboot_set_nca_load_indexes_reg(dev,
                                              pNcpNcaTaskGSM->activeGrpMask));  


    /* NOTE - Client is responsible for filling NCA pool */

    /* NOTE - We do not enable backpressure */
         
NCP_RETURN_LABEL
    return(ncpStatus);
}

ncp_st_t
ncp_task_lite_uboot_unconfig(ncp_dev_t *dev)
{
	ncp_st_t ncpStatus = NCP_ST_SUCCESS;

	if (NULL != pNcpNcaTaskGSM) {
		task_lite_free_aligned_fn(pNcpNcaTaskGSM->
					  hw.NcaInputQueues[0].entries);
		task_lite_free_aligned_fn(pNcpNcaTaskGSM->
					  hw.NcaOutputQueues[0].entries);
		task_lite_free_aligned_fn(pNcpNcaTaskGSM->
					  hw.NcaTaskCompletionQueues[0].entries);
		task_lite_free_aligned_fn(pNcpNcaTaskGSM->
					  hw.NcaRxBufferQueues[0].entries);
		task_lite_free_aligned_fn(pNcpNcaTaskGSM->
					  hw.cpu_pgit[0].u_ptr);
		task_lite_free_aligned_fn(pNcpNcaTaskGSM->
					  hw.nca_pgit[0].u_ptr);
		task_lite_free_aligned_fn(pNcpNcaTaskGSM);
	}

	NCP_RETURN_LABEL;
	return ncpStatus;
}

#endif
