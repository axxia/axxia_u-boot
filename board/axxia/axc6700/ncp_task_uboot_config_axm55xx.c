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

#include <config.h>

#define NCP_TASK_USE_55XX_HEADERS

#if 0 /* UBOOT */
#include "ncp_dev.h"
#include "ncp_release_id.h"
#endif

#include "ncp_task_pvt.h"

#if 0 /* UBOOT */
#if !defined(NCP_KERNEL) || defined(NCP_VXWORKS)
#include "ncp.h"
#include "ncp_pvt.h"
#endif
#endif

#ifndef NCP_DEV_FBRS
#include "ncp_task_inline_funcs_axm55xx.h"
#endif


/*
 * WARNING:
 * Certain XML changes may require changing the constants below!!!
 */

/* ACP5.Engines.NCA.NcaDomainInfo.DomainEntry[id=0].startOffset */
#define DOMAINBUNDLE_PA 0x2FC00000 /* 801112064 */

/* ACP5.Engines.NCA.NcaDomainInfo.DomainEntry[id=0].size */
#define DOMAINBUNDLE_SIZE 0x14000 /* 81920 */

/* ACP5.Engines.NCA.NcaDomainInfo.DomainEntry[id=0].otbpOffset */
#define OTBP_PA 0x2FC00000 /* 801112064 */

/* ACP5.Engines.NCA.QueueGroup[id=0].ThreadQueueSet[id=0].oPcQOffset */
#define OPCQ_OFFSET 0x2FC01480 /* 801117312 */

/* ACP5.Engines.NCA.QueueGroup[id=0].ThreadQueueSet[id=0].cPcQOffset */
#define CPCQ_OFFSET 0x2FC02480 /* 801121408 */

/* ACP5.Engines.NCA.QueueGroup[id=0].ThreadQueueSet[id=0].cfgDmaBuffersOffset */
#define CFG_BUFFS_OFFSET 0x2FC02900 /* 801122560 */

/* ACP5.Engines.NCA.QueueGroup[id=0].ThreadQueueSet[id=0].TaskReceiveQueue[id=0].iPcQOffset */
#define IPCQ_OFFSET 0x2FC01080 /* 801116288 */

/* ACP5.Engines.NCA.QueueGroup[id=0].ncaPgitOffset */
#define NCAPGIT_OFFSET 0x2FC01000 /* 801116160 */

/* ACP5.Engines.NCA.QueueGroup[id=0].cpuPgitOffset */
#define CPUPGIT_OFFSET 0x2FC01040 /* 801116224 */

/* ACP5.Engines.NCA.QueueGroup[id=0].ThreadQueueSet[id=0].Allocators.Allocator[id=0].allocatorOffset */
#define MMEALLOCATOR_OFFSET 0x2FC12C00 /* 801188864 */

/* ACP5.Engines.MME.MemoryPoolMap.SharedMemoryPools.SharedMemoryPool[id=0].physicalBaseAddress */
#define POOL_0_PA 0

/* ACP5.Engines.MME.MemoryPoolMap.VPPMemoryPools.VPPMemoryPool[id=0].maxDynamic */
#define POOL_0_SIZE 901565439


/* ACP5.Engines.MME.MemoryPoolMap.SharedMemoryPools.SharedMemoryPool[id=2].physicalBaseAddress */
#define POOL_2_PA 937295872

/* ACP5.Engines.MME.MemoryPoolMap.SharedMemoryPools.SharedMemoryPool[id=2].size */
#define POOL_2_SIZE 126214656

/*
 * Note - MME presents the following in the reverse order of what Task I/O needs
 */

/*ACP5.Engines.MME.MemoryPoolMap.SharedMemoryPools.SharedMemoryPool[id=2].BlockEntry[id=3].physicalBaseAddress */
#define POOL_2_SZ0_PA 1051367424
#define POOL_2_SZ0_VA 1051367424
/* ACP5.Engines.MME.MemoryPoolMap.SharedMemoryPools.SharedMemoryPool[id=2].BlockEntry[id=3].size */
#define POOL_2_SZ0_SIZE 12143104
#define POOL_2_SZ0_NUMBLOCKS 774

/*ACP5.Engines.MME.MemoryPoolMap.SharedMemoryPools.SharedMemoryPool[id=2].BlockEntry[id=2].physicalBaseAddress */
#define POOL_2_SZ1_VA 1019772928
#define POOL_2_SZ1_PA 1019772928
/* ACP5.Engines.MME.MemoryPoolMap.SharedMemoryPools.SharedMemoryPool[id=2].BlockEntry[id=2].size */
#define POOL_2_SZ1_SIZE 31594496
#define POOL_2_SZ1_NUMBLOCKS 1938

/*ACP5.Engines.MME.MemoryPoolMap.SharedMemoryPools.SharedMemoryPool[id=2].BlockEntry[id=1].physicalBaseAddress */
#define POOL_2_SZ2_VA 988020736
#define POOL_2_SZ2_PA 988020736
/* ACP5.Engines.MME.MemoryPoolMap.SharedMemoryPools.SharedMemoryPool[id=2].BlockEntry[id=1].size */
#define POOL_2_SZ2_SIZE 31752192
#define POOL_2_SZ2_NUMBLOCKS 15427

/*ACP5.Engines.MME.MemoryPoolMap.SharedMemoryPools.SharedMemoryPool[id=2].BlockEntry[id=0].physicalBaseAddress */
#define POOL_2_SZ3_VA 937295872
#define POOL_2_SZ3_PA 937295872
/* ACP5.Engines.MME.MemoryPoolMap.SharedMemoryPools.SharedMemoryPool[id=2].BlockEntry[id=0].size */
#define POOL_2_SZ3_SIZE 50724864
#define POOL_2_SZ3_NUMBLOCKS 47434



ncp_st_t
ncp_task_v2_uboot_config_mme_for_tqs(ncp_int32_t tqsID)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_nca_thread_queue_set_t *pTQS
        = &pNcpNcaV2_TaskSwState->threadQueueSets[tqsID];
    int i;

#ifdef NCP_TASK_DEBUG_MME
    NCP_LOG(NCP_MSG_INFO,"config_mme_for_tqs (%d)\r\n",tqsID);
#endif

    if (NCP_TASK_IS_SHARED_POOL(pTQS->poolID))
    {
        ncp_task_ncaV2_pool_t *pPoolEntry;
        pPoolEntry = &pNcpNcaV2_TaskSwState->taskMemoryPool[pTQS->poolID];

        for (i=0; i < pTQS->numAllocators; i++)
        {
            ncp_uint64_t *p64_VA;

            /*
             * Get VA and memset entire allocation interface.
             * Size is 4 queues of 128 64bit entries plus
             * 4 64bit read pointers.   The read pointers index
             * into the queues,   which are populated by MME with
             * free task buffers.
             */
            NCP_CALL(NCP_TASK_INITIALIZE_DOMAIN_OBJ_VA(
                MMEALLOCATOR_OFFSET,
                ((sizeof(ncp_uint64_t)*128*4)+(4*sizeof(ncp_uint64_t))),
                &pTQS->mme[i].baseVA,
                FALSE));

            p64_VA = (ncp_uint64_t *)pTQS->mme[i].baseVA;

            /*
             * Initialize MME Queues.
             * Queues are laid out from 64K to 256B
             */

            /* 64K queue */
#ifdef NCP_TASK_DEBUG_MME
            NCP_LOG(NCP_MSG_INFO, "64K queue entries start at %p\r\n",((void *)(ncp_raw_addr_t)p64_VA));
#endif
            pTQS->mme[i].allocIF[3].entries_baseVA
                = p64_VA;
            p64_VA +=  128;

           /* 16K Queue */
#ifdef NCP_TASK_DEBUG_MME
            NCP_LOG(NCP_MSG_INFO, "16K queue entries start at %p\r\n",((void *)(ncp_raw_addr_t)p64_VA));
#endif
             pTQS->mme[i].allocIF[2].entries_baseVA
                = p64_VA;
            p64_VA +=  128;

            /* 2K queue */
#ifdef NCP_TASK_DEBUG_MME
            NCP_LOG(NCP_MSG_INFO, "2K queue entries start at %p\r\n",((void *)(ncp_raw_addr_t)p64_VA));
#endif
            pTQS->mme[i].allocIF[1].entries_baseVA
                = p64_VA;
            p64_VA +=  128;

            /* 256B queue */
#ifdef NCP_TASK_DEBUG_MME
            NCP_LOG(NCP_MSG_INFO, "256B queue entries start at %p\r\n",((void *)(ncp_raw_addr_t)p64_VA));
#endif
            pTQS->mme[i].allocIF[0].entries_baseVA
                = p64_VA;
            p64_VA +=  128;

            /*
             * Read Pointers are laid out as follows: 2K, 16K, 64K, 256B
             *
             * Inititalize Read Pointer related state.
             * We will maintain a pointer to the "real" h/w read ptr area,
             * where we will manage a physAddr that us read by the h/w.
             * We will also maintain a sw pointer for direct access into
             * mPCQ entries. Test for queue wrap will be performed on
             * the s/w pointer,  since that is a 32-bit test with current
             * target platforms.
             */


            /* 2K */
#ifdef NCP_TASK_DEBUG_MME
            NCP_LOG(NCP_MSG_INFO, "2K readPtr @ %p\r\n",((void *)(ncp_raw_addr_t)p64_VA));
#endif
            pTQS->mme[i].allocIF[1].queueValid
                = ((pPoolEntry->numBlocks[1] == 0)? FALSE : TRUE);

            pTQS->mme[i].allocIF[1].readP_hwVA = (ncp_uint64_t *)p64_VA;
            pTQS->mme[i].allocIF[1].readP_hw_indx0_val
                = NCP_TASK_VA_2_PA(
                        pTQS->mme[i].allocIF[1].entries_baseVA,
                        0);
            pTQS->mme[i].allocIF[1].readP_swVA
                = pTQS->mme[i].allocIF[1].entries_baseVA;
            pTQS->mme[i].allocIF[1].readP_swVA_max_val
                = (ncp_uint64_t *)pTQS->mme[i].allocIF[1].readP_swVA + 127;

#if defined(NCP_TASK_DEBUG_MME) && !defined(NCP_KERNEL)
            NCP_LOG(NCP_MSG_INFO, "Contents:\r\n");
            ncp_r32((ncp_uint32_t *)pTQS->mme[i].allocIF[1].entries_baseVA, 256);
#endif

            /* 16K */

            p64_VA++;
#ifdef NCP_TASK_DEBUG_MME
            NCP_LOG(NCP_MSG_INFO, "16K readPtr @ %p\r\n",((void *)(ncp_raw_addr_t)p64_VA));
#endif
            pTQS->mme[i].allocIF[2].queueValid
                = ((pPoolEntry->numBlocks[2] == 0)? FALSE : TRUE);
            pTQS->mme[i].allocIF[2].readP_hwVA = (ncp_uint64_t *)p64_VA;
            pTQS->mme[i].allocIF[2].readP_hw_indx0_val
                = NCP_TASK_VA_2_PA(
                        pTQS->mme[i].allocIF[2].entries_baseVA,
                        0);
            pTQS->mme[i].allocIF[2].readP_swVA
                = pTQS->mme[i].allocIF[2].entries_baseVA;
            pTQS->mme[i].allocIF[2].readP_swVA_max_val
                = (ncp_uint64_t *)pTQS->mme[i].allocIF[2].readP_swVA + 127;


#if defined(NCP_TASK_DEBUG_MME) && !defined(NCP_KERNEL)
            NCP_LOG(NCP_MSG_INFO, "Contents:\r\n");
            ncp_r32((ncp_uint32_t *)pTQS->mme[i].allocIF[2].entries_baseVA, 256);
#endif

            /* 64K */
            p64_VA++;

#ifdef NCP_TASK_DEBUG_MME
            NCP_LOG(NCP_MSG_INFO, "64K readPtr @ %p\r\n",((void *)(ncp_raw_addr_t)p64_VA));
#endif
            pTQS->mme[i].allocIF[3].queueValid
                = ((pPoolEntry->numBlocks[3] == 0)? FALSE : TRUE);

            pTQS->mme[i].allocIF[3].readP_hwVA = (ncp_uint64_t *)p64_VA;
            pTQS->mme[i].allocIF[3].readP_hw_indx0_val
                = NCP_TASK_VA_2_PA(
                        pTQS->mme[i].allocIF[3].entries_baseVA,
                        0);
            pTQS->mme[i].allocIF[3].readP_swVA
                = pTQS->mme[i].allocIF[3].entries_baseVA;
            pTQS->mme[i].allocIF[3].readP_swVA_max_val
                = (ncp_uint64_t *)pTQS->mme[i].allocIF[3].readP_swVA + 127;


#if defined(NCP_TASK_DEBUG_MME) && !defined(NCP_KERNEL)
            NCP_LOG(NCP_MSG_INFO, "Contents:\r\n");
            ncp_r32((ncp_uint32_t *)pTQS->mme[i].allocIF[3].entries_baseVA, 256);
#endif

            /* 256B */
            p64_VA++;
#ifdef NCP_TASK_DEBUG_MME
            NCP_LOG(NCP_MSG_INFO, "256B readPtr @ %p\r\n",((void *)(ncp_raw_addr_t)p64_VA));
#endif

            pTQS->mme[i].allocIF[0].queueValid
                = ((pPoolEntry->numBlocks[0] == 0)? FALSE : TRUE);

            pTQS->mme[i].allocIF[0].readP_hwVA = (ncp_uint64_t *)p64_VA;
            pTQS->mme[i].allocIF[0].readP_hw_indx0_val
                = NCP_TASK_VA_2_PA(
                        pTQS->mme[i].allocIF[0].entries_baseVA,
                        0);
            pTQS->mme[i].allocIF[0].readP_swVA
                = pTQS->mme[i].allocIF[0].entries_baseVA;
            pTQS->mme[i].allocIF[0].readP_swVA_max_val
                = (ncp_uint64_t *)pTQS->mme[i].allocIF[0].readP_swVA + 127;


#if defined(NCP_TASK_DEBUG_MME) && !defined(NCP_KERNEL)
            NCP_LOG(NCP_MSG_INFO, "Contents:\r\n");
            ncp_r32((ncp_uint32_t *)pTQS->mme[i].allocIF[0].entries_baseVA, 256);
#endif

            p64_VA++;

#ifdef NCP_TASK_PRINT_BASE_ADDRESSES_AND_MAPPINGS

           NCP_MSG(NCP_MSG_INFO, "initialized shared pool allocator (%d) @offset 0x%llx baseVA=%p, endVA=%p\r\n",
                pTQS->mme[i].id,
                pTQS->mme[i].cfgOffset,
                (void *)pTQS->mme[i].baseVA,
                (void *)p64_VA);
#endif

        }
    }


NCP_RETURN_LABEL
    return(ncpStatus);
}

void
ncp_task_uboot_domain_bundle_clear(void)
{
    ncp_memset((void *)DOMAINBUNDLE_PA, 0, DOMAINBUNDLE_SIZE);
}

ncp_st_t
ncp_task_uboot_config(void)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_t     *ncp  = &gNCP;
    ncp_dev_t *dev  = &gDEV;
    ncp_nca_t *nca;
    int i;
    ncp_task_v2_pcq_grp_t *pPCQgrp;
    ncp_task_pcq_t        *pcq;


    /*
     * ========================================================
     * Allocate sw structs used to hold state and config info
     * ========================================================
     */

    NCP_ASSERT((NULL !=
                (nca = (ncp_nca_t *)ncp_nvm_malloc(sizeof(ncp_nca_t)))),
                NCP_ST_TASK_NO_MALLOC_MEM);

    ncp_memset(nca, 0, sizeof(ncp_nca_t));
    nca->cookie = NCP_TASK_STATE_COOKIE;

    NCP_ASSERT((NULL !=
                (nca->myNcpNcaTaskState =
                    ncp_nvm_malloc(sizeof(ncp_task_ncaV2_t)))),
                 NCP_ST_TASK_NO_MALLOC_MEM);
    ncp_memset(nca->myNcpNcaTaskState, 0, sizeof(ncp_task_ncaV2_t));
    pNcpNcaV2_TaskSwState = nca->myNcpNcaTaskState;
    ncp->ncaHdl = (ncp_nca_t *)nca;

    /*
     * ========================================================
     * Hardcode uBoot config - as if parsed cfg file
     * ========================================================
     */

    NCP_CALL(NCP_TASK_LOWLEVEL_MEMCFG((ncp_hdl_t)ncp,
                                        dev,
                                        nca,
                                        FALSE));

    /* Preinit all groups to unused  */
    for (i=0; i<NCP_X7_NUM_PCQ_GROUPS; i++)
    {
        pNcpNcaV2_TaskSwState->pcq_grp[i].id=0xFF; /* unused */
    }

    /* Preinit all QueueSets to unused  */
    for (i=0; i<NCP_X7_NUM_THREAD_QUEUESETS; i++)
    {
        pNcpNcaV2_TaskSwState->threadQueueSets[i].id=0xFF; /* unused */
    }


    /* Pool 0 */
    pNcpNcaV2_TaskSwState->taskMemoryPool[0].pool_PA
        = pNcpNcaV2_TaskSwState->taskMemoryPool[0].pool_VA
        = POOL_0_PA;

    pNcpNcaV2_TaskSwState->taskMemoryPool[0].pool_Size
        = POOL_0_SIZE;

    pNcpNcaV2_TaskSwState->taskMemoryPool[0].pool_EndVA
        = pNcpNcaV2_TaskSwState->taskMemoryPool[0].pool_VA
        + POOL_0_SIZE + 1;
    pNcpNcaV2_TaskSwState->taskMemoryPool[0].uMode = TRUE;

    /* Pool 2 */
    pNcpNcaV2_TaskSwState->taskMemoryPool[2].pool_PA
        = pNcpNcaV2_TaskSwState->taskMemoryPool[2].pool_VA
        = POOL_2_PA;

    pNcpNcaV2_TaskSwState->taskMemoryPool[2].pool_Size
        = POOL_2_SIZE;

    pNcpNcaV2_TaskSwState->taskMemoryPool[2].pool_EndVA
        = pNcpNcaV2_TaskSwState->taskMemoryPool[2].pool_VA
        + POOL_2_SIZE + 1;

    pNcpNcaV2_TaskSwState->taskMemoryPool[2].tqsRefCount = 1;
    pNcpNcaV2_TaskSwState->taskMemoryPool[2].uMode = TRUE;

    /* Blocks for pool 2 */
    pNcpNcaV2_TaskSwState->taskMemoryPool[2].numBlocks[3]           = POOL_2_SZ3_NUMBLOCKS;
    pNcpNcaV2_TaskSwState->taskMemoryPool[2].blocksVA[3]            = (void *)POOL_2_SZ3_PA;
    pNcpNcaV2_TaskSwState->taskMemoryPool[2].blocksVAend[3]         = (void *)(POOL_2_SZ3_PA + POOL_2_SZ0_SIZE);
    pNcpNcaV2_TaskSwState->taskMemoryPool[2].blocksPA[3]            = POOL_2_SZ3_PA;
    pNcpNcaV2_TaskSwState->taskMemoryPool[2].numBlocksRxReserve[3]  = 0;

    pNcpNcaV2_TaskSwState->taskMemoryPool[2].numBlocks[2]           = POOL_2_SZ2_NUMBLOCKS;
    pNcpNcaV2_TaskSwState->taskMemoryPool[2].blocksVA[2]            = (void *)POOL_2_SZ2_PA;
    pNcpNcaV2_TaskSwState->taskMemoryPool[2].blocksVAend[2]         = (void *)(POOL_2_SZ2_PA + POOL_2_SZ2_SIZE);
    pNcpNcaV2_TaskSwState->taskMemoryPool[2].blocksPA[2]            = POOL_2_SZ2_PA;
    pNcpNcaV2_TaskSwState->taskMemoryPool[2].numBlocksRxReserve[2]  = 0;

    pNcpNcaV2_TaskSwState->taskMemoryPool[2].numBlocks[1]           = POOL_2_SZ1_NUMBLOCKS;
    pNcpNcaV2_TaskSwState->taskMemoryPool[2].blocksVA[1]            = (void *)POOL_2_SZ1_PA;
    pNcpNcaV2_TaskSwState->taskMemoryPool[2].blocksVAend[1]         = (void *)(POOL_2_SZ1_PA + POOL_2_SZ1_SIZE);
    pNcpNcaV2_TaskSwState->taskMemoryPool[2].blocksPA[1]            = POOL_2_SZ1_PA;
    pNcpNcaV2_TaskSwState->taskMemoryPool[2].numBlocksRxReserve[1]  = 0;

    pNcpNcaV2_TaskSwState->taskMemoryPool[2].numBlocks[0]           = POOL_2_SZ0_NUMBLOCKS;
    pNcpNcaV2_TaskSwState->taskMemoryPool[2].blocksVA[0]            = (void *)POOL_2_SZ0_PA;
    pNcpNcaV2_TaskSwState->taskMemoryPool[2].blocksVAend[0]         = (void *)(POOL_2_SZ0_PA + POOL_2_SZ0_SIZE);
    pNcpNcaV2_TaskSwState->taskMemoryPool[2].blocksPA[0]            = POOL_2_SZ0_PA;
    pNcpNcaV2_TaskSwState->taskMemoryPool[2].numBlocksRxReserve[0]  = 0;



    /* Base config parameters */

    pNcpNcaV2_TaskSwState->myDomain     = 0;
    pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_VA = DOMAINBUNDLE_PA;
    pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_PA = DOMAINBUNDLE_PA;
    pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_Size
        = DOMAINBUNDLE_SIZE;

    /* Backpressure */
    pNcpNcaV2_TaskSwState->otbpInfo_Offset = OTBP_PA;

    NCP_CALL(NCP_TASK_INITIALIZE_DOMAIN_OBJ_VA(
        pNcpNcaV2_TaskSwState->otbpInfo_Offset,
        sizeof(ncp_uint32_t),
        &pNcpNcaV2_TaskSwState->otbpInfo_VA,
        TRUE));

    /* Queue Group 0 */

    pPCQgrp = &pNcpNcaV2_TaskSwState->pcq_grp[0];

    pPCQgrp->ncaPgitOffset = NCAPGIT_OFFSET;

    NCP_CALL(NCP_TASK_INITIALIZE_DOMAIN_OBJ_VA(
        pPCQgrp->ncaPgitOffset,
        sizeof(ncp_dev_nca_pgit_t),
        &pNcpNcaV2_TaskSwState->hw.nca_pgit[0].ptr,
        TRUE));

    pPCQgrp->pNca_pgit = pNcpNcaV2_TaskSwState->hw.nca_pgit[0].ptr;

    pPCQgrp->cpuPgitOffset = CPUPGIT_OFFSET;                           NCP_CALL(NCP_TASK_INITIALIZE_DOMAIN_OBJ_VA(
        pPCQgrp->cpuPgitOffset,
        sizeof(ncp_dev_cpu_pgit_t),
        &pNcpNcaV2_TaskSwState->hw.cpu_pgit[0].ptr,
        TRUE));

    pPCQgrp->pCpu_pgit = pNcpNcaV2_TaskSwState->hw.cpu_pgit[0].ptr;

    pPCQgrp->id = 0;
    pPCQgrp->grpDomain = 0;
    pPCQgrp->cpuId = NCP_NCA_CPU_ANY;
    pPCQgrp->num_oPCQs = 1;
    pPCQgrp->num_cPCQs = 1;
    pPCQgrp->num_iPCQs = 1;

    /* Config TQS 0 */

    pNcpNcaV2_TaskSwState->threadQueueSets[0].id     = 0;
    pNcpNcaV2_TaskSwState->threadQueueSets[0].grpId  = 0;
    pNcpNcaV2_TaskSwState->threadQueueSets[0].poolID = 2;
    pNcpNcaV2_TaskSwState->threadQueueSets[0].uMode  = TRUE;
    pNcpNcaV3_TaskSwState->threadQueueSets[0].qsAccessMode
        = NCP_NCA_QS_AVAILABLE;
    pNcpNcaV2_TaskSwState->threadQueueSets[0].tqsDomain = 0;
    pNcpNcaV2_TaskSwState->threadQueueSets[0].first_iPCQ_id = 0;
    pNcpNcaV2_TaskSwState->threadQueueSets[0].num_iPCQs_in_queueSet = 1;

    /* config cPCQ 0 */


    pcq = &pNcpNcaV2_TaskSwState->cPCQs[0];

    pcq->u.cpcq_info.cPcqOffset = CPCQ_OFFSET;
    pcq->nEntries  = 64;

    NCP_CALL(NCP_TASK_INITIALIZE_DOMAIN_OBJ_VA(
          pcq->u.cpcq_info.cPcqOffset,
           pcq->nEntries  * sizeof(ncp_task_cPCQ_entry_t),
          &pcq->pPCQbase,
          TRUE));


    pcq->baseBusAddr = NCP_TASK_VA_2_PA(pcq->pPCQbase, 0);
    pcq->nEntriesMinusOne   = pcq->nEntries - 1;
    pcq->ncaQueueId         = 0;
    pcq->u.cpcq_info.blockSize  = 1024;
    pcq->pProducerIdx           = &pPCQgrp->pCpu_pgit->c_pIdx[0];
    pcq->pConsumerIdx           = &pPCQgrp->pNca_pgit->c_cIdx[0];
    pcq->u.cpcq_info.pCPCQentry = pcq->pPCQbase;

    NCP_CALL(ncp_task_v2_map_queuenum_to_pcq(NCP_TASK_PCQ_CONFIG, 0,
                &pNcpNcaV2_TaskSwState->threadQueueSets[0].p_cPCQ));

    /* config oPCQ 0 */

    pcq = &pNcpNcaV2_TaskSwState->oPCQs[0];

    pcq->u.opcq_info.oPcqOffset = OPCQ_OFFSET;
    pcq->nEntries           = 64;

    NCP_CALL(NCP_TASK_INITIALIZE_DOMAIN_OBJ_VA(
            pcq->u.opcq_info.oPcqOffset,
            pcq->nEntries *  sizeof(ncp_task_ncaV2_oPCQ_entry_t),
            &pNcpNcaV2_TaskSwState->hw.NcaOutputQueues[0].entries,
            TRUE));

    pcq->pPCQbase
        = &(pNcpNcaV2_TaskSwState->hw.NcaOutputQueues[0].entries[0]);
    pcq->baseBusAddr = NCP_TASK_VA_2_PA(pcq->pPCQbase,
                                        0);


    pcq->nEntriesMinusOne   = pcq->nEntries - 1;
    pcq->grpId          = 0;
    pcq->ncaQueueId     = 0;
    pcq->pProducerIdx   = &pPCQgrp->pCpu_pgit->o_pIdx[0];
    pcq->pConsumerIdx   = &pPCQgrp->pNca_pgit->o_cIdx[0];
    pcq->u.opcq_info.copyPool = 2;
    pcq->u.opcq_info.pOPCQentry = pcq->pPCQbase;

    NCP_CALL(ncp_task_v2_map_queuenum_to_pcq(NCP_TASK_PCQ_OUTPUT, 0,
                &pNcpNcaV2_TaskSwState->threadQueueSets[0].p_oPCQ));

    /*
     * Init oPCQ Aux Data
     */

    if (NULL == (pNcpNcaV2_TaskSwState->outputQueueAuxData[0]
         = (ncp_task_ncaV2_oPCQ_aux_data_t *)
           NCP_ALLOC_CACHEABLE(pcq->nEntries * sizeof(ncp_task_ncaV2_oPCQ_aux_data_t))))
    {
        NCP_CALL(NCP_ST_NO_MEMORY);
    }
    ncp_memset(pNcpNcaV2_TaskSwState->outputQueueAuxData[0],
               0,
              (pcq->nEntries * sizeof(ncp_task_ncaV2_oPCQ_aux_data_t)));
    pcq->u.opcq_info.pAuxWriteEntry
        = pcq->u.opcq_info.pAuxReadEntry
        = pNcpNcaV2_TaskSwState->outputQueueAuxData[0];
    pcq->u.opcq_info.pLastAuxEntry
        = pcq->u.opcq_info.pAuxReadEntry + pcq->nEntries;
    pcq->u.opcq_info.auxEntriesAvail  = pcq->nEntries-2;

    /* Config iPCQ 0 */

    pcq = &pNcpNcaV2_TaskSwState->iPCQs[0];

    pcq->u.ipcq_info.iPcqOffset = IPCQ_OFFSET;
    pcq->nEntries  = 64;

    NCP_CALL(NCP_TASK_INITIALIZE_DOMAIN_OBJ_VA(
        pcq->u.ipcq_info.iPcqOffset,
        pcq->nEntries * sizeof(ncp_task_ncaV2_iPCQ_entry_t),
        &pNcpNcaV2_TaskSwState
            ->hw.NcaInputQueues[0].entries,
        TRUE));

    pcq->nEntriesMinusOne               = pcq->nEntries - 1;

    pcq->pPCQbase
        = &(pNcpNcaV2_TaskSwState->hw.NcaInputQueues[0].entries[0]);
    pcq->baseBusAddr = NCP_TASK_VA_2_PA(pcq->pPCQbase, 0);

    pcq->u.ipcq_info.ipcqConsumerIdx    = 0;
    pcq->grpId        = 0;
    pcq->ncaQueueId   = 0;
    pcq->pConsumerIdx = &pPCQgrp->pCpu_pgit->i_cIdx[0];
    pcq->pProducerIdx = &pPCQgrp->pNca_pgit->i_pIdx[0];

    pcq->u.ipcq_info.wrrWeight = 16;
    pcq->u.ipcq_info.multiSegRxOK =TRUE;
    pcq->u.ipcq_info.rxTaskCompletionMode = NCP_TASK_COMPLETION_HW_AUTOMATIC;
    pcq->u.ipcq_info.pIPCQentry = pcq->pPCQbase;


    /* Config MME allocator 0 */

    pNcpNcaV2_TaskSwState->threadQueueSets[0].mme[0].cfgOffset
        = MMEALLOCATOR_OFFSET;

    pNcpNcaV2_TaskSwState->threadQueueSets[0].numAllocators = 1;

    NCP_ASSERT((NULL != (pNcpNcaV2_TaskSwState->threadQueueSets[0].mme
    = (ncp_task_mme_allocator_t   *)
       ncp_nvm_malloc(
                    (sizeof(ncp_task_mme_allocator_t)))
                     )),
                    NCP_ST_TASK_NO_MALLOC_MEM);

    memset(pNcpNcaV2_TaskSwState->threadQueueSets[0].mme,
           0,
           (sizeof(ncp_task_mme_allocator_t)));

    pNcpNcaV2_TaskSwState->threadQueueSets[0].mme[0].valid = TRUE;
    pNcpNcaV2_TaskSwState->threadQueueSets[0].mme[0].id = 0;

    /* Add and initialize an allocator for TQS 0 */
    ncp_task_v2_uboot_config_mme_for_tqs(0);

    /*
     * ========================================================
     * Proceed with hardware confgiration that was not accomplished
     * using the hardware read/write playback of i/o operations
     * ========================================================
     */

    debug("Configuring local domain %d\r\n", pNcpNcaV2_TaskSwState->myDomain);

    /*
     * Hook task I/O state off nca handle
     */
     nca->myNcpNcaTaskState = pNcpNcaV2_TaskSwState;

    /*
     * Cache items from ncp handle
     */
    pNcpNcaV2_TaskSwState->myDomain = ncp->domainId;
    pNcpNcaV2_TaskSwState->ncpId = ncp->id;
    pNcpNcaV2_TaskSwState->inWarmRestart = FALSE;
    pNcpNcaV2_TaskSwState->inUmode = TRUE;
    pNcpNcaV2_TaskSwState->domainIsInternal = ncp->domainIsInternal = TRUE;



NCP_RETURN_LABEL
    return(ncpStatus);
}

void
ncp_task_uboot_unconfig(void)
{
    ncp_t     *ncp  = &gNCP;

    if(ncp->ncaHdl) {
        ncp_nca_t *nca = ncp->ncaHdl;

        if(nca->myNcpNcaTaskState) {
            ncp_nvm_free(nca->myNcpNcaTaskState);
        }

        ncp_nvm_free(nca);
        ncp->ncaHdl = NULL;
        pNcpNcaV2_TaskSwState = NULL;
    }
}
