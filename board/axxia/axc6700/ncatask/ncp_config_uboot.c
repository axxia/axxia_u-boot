/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.              *
 **                                                                       *
 **************************************************************************/
#include <common.h>
#include <malloc.h>
#include "main.h"
#include "uboot/ncp_task_pvt.h"
#include "uboot/ncp_dev_pvt.h"
#include "uboot/ncp_mme_ext.h"

/* AXC6732.Engines.NCAv3.NcaDomainInfo.DomainEntry[id=0].startOffset */
#define DOMAINBOUNDLE_PA           0x82000000ULL   /* 0x82000000 */
/* AXC6732.Engines.NCAv3.NcaDomainInfo.DomainEntry[id=0].vpIOControlVirtualBaseOffset */
#define DOMAINBOUNDLE_VA           0x82000000ULL   /* 0x70000000 */
/* AXC6732.Engines.NCAv3.NcaDomainInfo.DomainEntry[id=0].size */
#define DOMAINBOUNDLE_SIZE             524288   /* 0x80000 */



/* AXC6732.Engines.MME.MemoryPoolMap.SharedMemoryPools.SharedMemoryPool[id=2].physicalBaseAddress */
#define POOL_2_PA                 0x9B800000ULL /* 0x9B800000 */

/* AXC6732.Engines.MME.MemoryPoolMap.SharedMemoryPools.SharedMemoryPool[id=2].actualSize */
#define POOL_2_SIZE               268409088 /* 0xFFF9900 */

/* AXC6732.Engines.MME.MemoryPoolMap.SharedMemoryPools.SharedMemoryPool[id=2].virtualBaseAddress */
#define POOL_2_VA                 0x9B800000 /* 0x70080000 */

/* virtual address + actual size */
#define POOL_2_VA_END             0xAB7F9900 /* 0x80079900 */

/* AXC6732.Engines.NCAv3.ApplicationProfiles.taskTransmitQueue0Depth */
#define TASK_QUEUE_TX0_DEPTH      8
#define TASK_QUEUE_TX0_OFFSET     20

/* AXC6732.Engines.NCAv3.ApplicationProfiles.taskTransmitQueue1Depth */
#define TASK_QUEUE_TX1_DEPTH      4
#define TASK_QUEUE_TX1_OFFSET     28

/* AXC6732.Engines.NCAv3.ApplicationProfiles.taskReceiveQueueActualDepth */
#define TASK_QUEUE_RX0_DEPTH      4
#define TASK_QUEUE_RX0_OFFSET     16


extern ncp_task_swState_t *pNcpTaskSwState;
#ifdef NCP_USE_NVM
extern ncp_mutex_t *pNvmLock;
extern ncp_bool_t *pNvmActive;
#endif	/* NCP_USE_NVM */

extern unsigned long ncp_nvm_vaddr;
extern unsigned long ncp_nvm_size;

void *taskIOMem;
ncp_t *ncp;

void clean_memory_eioa(void);
/*********************/
/* for GDB debugging */

ncp_ncav3_tqs_control_t peek_tqs_ctrl(int offset)
{
    return ((ncp_ncav3_tqs_control_t*)taskIOMem)[offset];
}

ncp_uint8_t  peek_txq0_pidx(int offset)
{
    return *pNcpTaskSwState->tqsSwState[offset].txQ0.pProducerIdx;
}

ncp_uint8_t  peek_txq0_cidx(int offset)
{
    return *pNcpTaskSwState->tqsSwState[offset].txQ0.pConsumerIdx;
}

ncp_task_pcq_t peek_pcq(int offset)
{
    return ((ncp_task_pcq_t*)pNcpTaskSwState->tqsSwState[0].mmeAllocator[SHARED_BUFFER_POOL2].mPCQ)[offset];
}

ncp_uint8_t peek_pidx(int offset)
{
    ncp_task_pcq_t p_mPCQ = peek_pcq(offset);
    return *(p_mPCQ).pProducerIdx;
}

ncp_ncav3_tqs_control_t peek_tqs_array(int offset)
{
    ncp_ncav3_hdl_t *nca  = (ncp_ncav3_hdl_t *)ncp->ncaHdl;
    return ((ncp_ncav3_tqs_control_t *)&nca->tqsArray)[offset];
}

/* end for GDB debugging */
/*************************/

#if 0
uboot - no files
static ncp_st_t
status_code(void)
{
    switch (errno)
    {
        case EBADF:
        case ENOTTY:
            return NCP_ST_DEV_INVALID_HANDLE;

        case ENOENT:
            return NCP_ST_DEV_DEVICE_FILE_NOT_FOUND;

        case ENXIO:
        case ENODEV:
            return NCP_ST_DEV_DEVICE_NOT_FOUND;

        case EFAULT:
            return NCP_ST_DEV_INVALID_BUFFER;

        case EINVAL:
            return NCP_ST_DEV_INVALID_IOCTL_COMMAND;
    }

    return NCP_ST_DEV_UNMAPPED_ERROR;
}
#endif

static ncp_st_t
ncav3_map_domain_memory(ncp_t *ncp, ncp_ncav3_hdl_t *nca, ncp_dev_hdl_t dev)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_ncav3_domain_info_t *domInfo = &nca->configInfo.domainInfo[ncp->domainId];

    pNcpTaskSwState->domainMemMap.domainBundle_PA = domInfo->physBase;
    pNcpTaskSwState->domainMemMap.domainBundle_VA = domInfo->virtBase;
    pNcpTaskSwState->domainMemMap.domainBundle_Size = domInfo->size;

	taskIOMem = (void *) pNcpTaskSwState->domainMemMap.domainBundle_PA;
    if (NULL == (void *)pNcpTaskSwState->domainMemMap.domainBundle_VA)
    {
        pNcpTaskSwState->domainMemMap.domainBundle_VA = (ncp_uintptr_t) taskIOMem;
    }

    nca->tqsArray = (ncp_ncav3_tqs_control_t *) taskIOMem;


NCP_RETURN_LABEL

    return ncpStatus;
}



ncp_st_t
mme_config(ncp_t *ncp)
{
    ncp_mme_t       *mme      = NULL;
    ncp_mme_pool_t  *memPool  = NULL;
    ncp_mme_mpcq_t  *mPCQ     = NULL;
    ncp_uint32_t    blockId   = 0;

    mme = malloc(sizeof(ncp_mme_t));
    memset(mme, 0, sizeof(ncp_mme_t));

    ncp->mmeHdl = (ncp_mme_t *)mme;
    mme->cookie = NCP_MME_HANDLE_COOKIE;
    /* NCP_CALL(NCP_MUTEX_INIT(&mme->lock, TRUE)); */
    mme->ncpHdl = ncp;
    memPool = mme->mmePool;
    mPCQ = mme->mmeMPCQ;

    memPool[SHARED_BUFFER_POOL2].poolVirtBase = POOL_2_VA;
    memPool[SHARED_BUFFER_POOL2].poolPhysBase = POOL_2_PA;
    memPool[SHARED_BUFFER_POOL2].maxDynamic   = 268409087;
    memPool[SHARED_BUFFER_POOL2].poolSize     = POOL_2_SIZE;

    memPool[SHARED_BUFFER_POOL2].blockSize[0] = 65536;
    memPool[SHARED_BUFFER_POOL2].blockSize[1] = 16384;
    memPool[SHARED_BUFFER_POOL2].blockSize[2] = 2048;
    memPool[SHARED_BUFFER_POOL2].blockSize[3] = 256;

    memPool[SHARED_BUFFER_POOL2].virtBase[3]  = 2850422784;
    memPool[SHARED_BUFFER_POOL2].physBase[3]  = 2850422784;
    memPool[SHARED_BUFFER_POOL2].numBlocks[3] = 104857;

    memPool[SHARED_BUFFER_POOL2].virtBase[2]  = 2783313920;
    memPool[SHARED_BUFFER_POOL2].physBase[2]  = 2783313920;
    memPool[SHARED_BUFFER_POOL2].numBlocks[2] = 32768;

    memPool[SHARED_BUFFER_POOL2].virtBase[1]  = 2716205056;
    memPool[SHARED_BUFFER_POOL2].physBase[1]  = 2716205056;
    memPool[SHARED_BUFFER_POOL2].numBlocks[1] = 4096;

    memPool[SHARED_BUFFER_POOL2].virtBase[0]  = POOL_2_VA;
    memPool[SHARED_BUFFER_POOL2].physBase[0]  = POOL_2_PA;
    memPool[SHARED_BUFFER_POOL2].numBlocks[0] = 1638;

    for (blockId = 0; blockId < 4; blockId++)
    {
        if(memPool[SHARED_BUFFER_POOL2].numBlocks[blockId] == 0)
        {
            mme->mmePool[SHARED_BUFFER_POOL2].physBase[blockId] = mme->mmePool[SHARED_BUFFER_POOL2].poolPhysBase;
        }
    }

    mPCQ[2].id = 2;
    mPCQ[2].valid = TRUE;
    mPCQ[2].pool = SHARED_BUFFER_POOL2;
    mPCQ[2].entrySize[0] = 65536;
    mPCQ[2].entrySize[1] = 16384;
    mPCQ[2].entrySize[2] = 2048;
    mPCQ[2].entrySize[3] = 256;

    return NCP_ST_SUCCESS;
}

ncp_st_t
mme_destroy(ncp_t *ncp)
{
	free(ncp->mmeHdl);
	ncp->mmeHdl = 0;
	return NCP_ST_SUCCESS;
}



ncp_st_t
ncav3_config_hw(ncp_t *ncp)
{
    ncp_st_t         ncpStatus           = NCP_ST_SUCCESS;
    ncp_mme_pool_t   *pMMEpoolInfo       = NULL;
    ncp_mme_t        *mme                = NULL;
    ncp_ncav3_hdl_t  *nca                = (ncp_ncav3_hdl_t *) ncp->ncaHdl;
    ncp_dev_hdl_t    dev                 = ncp_dev_hdls[ncp->id];
    int              buffSizes[4]        = {256, 2048, 16384, 65536};
    ncp_task_tqs_swState_t *pTqs         = NULL;
    ncp_task_mme_allocator_t *pAllocator = NULL;
    ncp_task_pcq_t           *p_mPCQ     = NULL;
    ncp_task_pcq_t           *p_oPCQ     = NULL;
    ncp_task_pcq_t           *p_iPCQ     = NULL;
    ncp_ncav3_tqs_control_t  *tqsControl = NULL;
    ncp_ncav3_cpu_profile_t  *profile    = NULL;
    ncp_uintptr_t tmp;


    myDevHdl = dev;
    myNcpHdl = (ncp_hdl_t) ncp;
    mme = (ncp_mme_t *)(ncp->mmeHdl);
    pTqs = &pNcpTaskSwState->tqsSwState[0];

    ncav3_map_domain_memory(ncp, nca, dev);

    pMMEpoolInfo = &(mme->mmePool[0]);

    pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].valid = pMMEpoolInfo[SHARED_BUFFER_POOL2].valid;
    pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].poolId = SHARED_BUFFER_POOL2;
    pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].poolPA = pMMEpoolInfo[SHARED_BUFFER_POOL2].poolPhysBase;
    pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].poolSize = pMMEpoolInfo[SHARED_BUFFER_POOL2].poolSize;
    pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].poolVA = (ncp_uintptr_t) pMMEpoolInfo[SHARED_BUFFER_POOL2].poolVirtBase;
    pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].poolMaxDynamic = (ncp_uint64_t)pMMEpoolInfo[SHARED_BUFFER_POOL2].maxDynamic;
    pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].poolVAEnd = pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].poolVA \
        + pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].poolSize;
    strncpy(pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].name.name, pMMEpoolInfo[SHARED_BUFFER_POOL2].name, NCP_TASK_MAX_RESOURCE_NAME_LEN-1);

    pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].numBlocks[3] = pMMEpoolInfo[SHARED_BUFFER_POOL2].numBlocks[0];
    pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].blocksVA[3]  = pMMEpoolInfo[SHARED_BUFFER_POOL2].virtBase[0];
    pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].blocksVAend[3] = pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].blocksVA[3] \
        + (pMMEpoolInfo[SHARED_BUFFER_POOL2].numBlocks[0] * buffSizes[3]);
    pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].blocksPA[3] = pMMEpoolInfo[SHARED_BUFFER_POOL2].physBase[0];
    pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].numBlocksForNCA[3] = pMMEpoolInfo[SHARED_BUFFER_POOL2].numReserveBlocks[0];

    pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].numBlocks[2] = pMMEpoolInfo[SHARED_BUFFER_POOL2].numBlocks[1];
    pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].blocksVA[2]  = pMMEpoolInfo[SHARED_BUFFER_POOL2].virtBase[1];
    pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].blocksVAend[2] = pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].blocksVA[2] \
        + (pMMEpoolInfo[SHARED_BUFFER_POOL2].numBlocks[1] * buffSizes[2]);
    pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].blocksPA[2] = pMMEpoolInfo[SHARED_BUFFER_POOL2].physBase[1];
    pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].numBlocksForNCA[2] = pMMEpoolInfo[SHARED_BUFFER_POOL2].numReserveBlocks[1];

    pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].numBlocks[1] = pMMEpoolInfo[SHARED_BUFFER_POOL2].numBlocks[2];
    pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].blocksVA[1]  = pMMEpoolInfo[SHARED_BUFFER_POOL2].virtBase[2];
    pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].blocksVAend[1] = pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].blocksVA[1] \
        + (pMMEpoolInfo[SHARED_BUFFER_POOL2].numBlocks[2] * buffSizes[1]);
    pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].blocksPA[1] = pMMEpoolInfo[SHARED_BUFFER_POOL2].physBase[2];
    pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].numBlocksForNCA[1] = pMMEpoolInfo[SHARED_BUFFER_POOL2].numReserveBlocks[2];

    pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].numBlocks[0] = pMMEpoolInfo[SHARED_BUFFER_POOL2].numBlocks[3];
    pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].blocksVA[0]  = pMMEpoolInfo[SHARED_BUFFER_POOL2].virtBase[3];
    pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].blocksVAend[0] = pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].blocksVA[0] \
        + (pMMEpoolInfo[SHARED_BUFFER_POOL2].numBlocks[3] * buffSizes[0]);
    pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].blocksPA[0] = pMMEpoolInfo[SHARED_BUFFER_POOL2].physBase[3];
    pNcpTaskSwState->taskPools[SHARED_BUFFER_POOL2].numBlocksForNCA[0] = pMMEpoolInfo[SHARED_BUFFER_POOL2].numReserveBlocks[3];


    /* set up any shared pool allocators used by this TQS */

    pAllocator = &pTqs->mmeAllocator[SHARED_BUFFER_POOL2];
    pAllocator->id = SHARED_BUFFER_POOL2;
    pAllocator->valid = TRUE;

    p_mPCQ = &pAllocator->mPCQ[0];
    p_mPCQ->nEntries = 16;
    p_mPCQ->pPCQbase = (void*)0x82000200;
    p_mPCQ->pConsumerIdx = (void*)0x82000080;
    p_mPCQ->pProducerIdx = (void*)0x820000c0;
    p_mPCQ->nEntriesMinusOne = p_mPCQ->nEntries - 1;
    p_mPCQ->nEntriesMinusTwo = p_mPCQ->nEntries - 2;
    p_mPCQ->nEntriesDiv2     = p_mPCQ->nEntries / 2;
    p_mPCQ->cookie = NCP_TASK_PCQ_COOKIE;
    p_mPCQ->u.mpcq_info.pMPCQentry = p_mPCQ->pPCQbase;
    p_mPCQ->u.mpcq_info.pPrefetchEntry = p_mPCQ->u.mpcq_info.pMPCQentry + 1;
    p_mPCQ->u.mpcq_info.pLastEntry = p_mPCQ->u.mpcq_info.pMPCQentry + p_mPCQ->nEntries - 1;
    p_mPCQ->u.mpcq_info.numAvail = p_mPCQ->nEntriesMinusTwo;
    p_mPCQ->hwProducerVal = 0;
    p_mPCQ->hwConsumerVal = 0;
    p_mPCQ->toggleBit = 0;

    p_mPCQ = &pAllocator->mPCQ[1];
    p_mPCQ->nEntries = 8;
    p_mPCQ->pPCQbase = (void*)0x82000280;
    p_mPCQ->pConsumerIdx = (void*)0x82000081;
    p_mPCQ->pProducerIdx = (void*)0x820000c1;
    p_mPCQ->nEntriesMinusOne = p_mPCQ->nEntries - 1;
    p_mPCQ->nEntriesMinusTwo = p_mPCQ->nEntries - 2;
    p_mPCQ->nEntriesDiv2     = p_mPCQ->nEntries / 2;
    p_mPCQ->cookie = NCP_TASK_PCQ_COOKIE;
    p_mPCQ->u.mpcq_info.pMPCQentry = p_mPCQ->pPCQbase;
    p_mPCQ->u.mpcq_info.pPrefetchEntry = p_mPCQ->u.mpcq_info.pMPCQentry + 1;
    p_mPCQ->u.mpcq_info.pLastEntry = p_mPCQ->u.mpcq_info.pMPCQentry + p_mPCQ->nEntries - 1;
    p_mPCQ->u.mpcq_info.numAvail = p_mPCQ->nEntriesMinusTwo;
    p_mPCQ->hwProducerVal = 0;
    p_mPCQ->hwConsumerVal = 0;
    p_mPCQ->toggleBit = 0;

    p_mPCQ = &pAllocator->mPCQ[2];
    p_mPCQ->nEntries = 8;
    p_mPCQ->pPCQbase = (void*)0x820002c0;
    p_mPCQ->pConsumerIdx = (void*)0x82000082;
    p_mPCQ->pProducerIdx = (void*)0x820000c2;
    p_mPCQ->nEntriesMinusOne = p_mPCQ->nEntries - 1;
    p_mPCQ->nEntriesMinusTwo = p_mPCQ->nEntries - 2;
    p_mPCQ->nEntriesDiv2     = p_mPCQ->nEntries / 2;
    p_mPCQ->cookie = NCP_TASK_PCQ_COOKIE;
    p_mPCQ->u.mpcq_info.pMPCQentry = p_mPCQ->pPCQbase;
    p_mPCQ->u.mpcq_info.pPrefetchEntry = p_mPCQ->u.mpcq_info.pMPCQentry + 1;
    p_mPCQ->u.mpcq_info.pLastEntry = p_mPCQ->u.mpcq_info.pMPCQentry + p_mPCQ->nEntries - 1;
    p_mPCQ->u.mpcq_info.numAvail = p_mPCQ->nEntriesMinusTwo;
    p_mPCQ->hwProducerVal = 0;
    p_mPCQ->hwConsumerVal = 0;
    p_mPCQ->toggleBit = 0;

    p_mPCQ = &pAllocator->mPCQ[3];
    p_mPCQ->nEntries = 4;
    p_mPCQ->pPCQbase = (void*)0x82000300;
    p_mPCQ->pConsumerIdx = (void*)0x82000083;
    p_mPCQ->pProducerIdx = (void*)0x820000c3;
    p_mPCQ->nEntriesMinusOne = p_mPCQ->nEntries - 1;
    p_mPCQ->nEntriesMinusTwo = p_mPCQ->nEntries - 2;
    p_mPCQ->nEntriesDiv2     = p_mPCQ->nEntries / 2;
    p_mPCQ->cookie = NCP_TASK_PCQ_COOKIE;
    p_mPCQ->u.mpcq_info.pMPCQentry = p_mPCQ->pPCQbase;
    p_mPCQ->u.mpcq_info.pPrefetchEntry = p_mPCQ->u.mpcq_info.pMPCQentry + 1;
    p_mPCQ->u.mpcq_info.pLastEntry = p_mPCQ->u.mpcq_info.pMPCQentry + p_mPCQ->nEntries - 1;
    p_mPCQ->u.mpcq_info.numAvail = p_mPCQ->nEntriesMinusTwo;
    p_mPCQ->hwProducerVal = 0;
    p_mPCQ->hwConsumerVal = 0;
    p_mPCQ->toggleBit = 0;

    pTqs->cookie    = NCP_TASK_TQS_SWSTATE_COOKIE;
    pTqs->tqsUseCnt = 0;
    pTqs->tqsId     = 0;

    ncp_task_initialize_tbr_arrays();

    tqsControl = (ncp_ncav3_tqs_control_t *) &nca->tqsArray[0];

    /* OPCQ_0 */
    memset(&pTqs->txQ0, 0, sizeof(ncp_pcq_info_t));

    tqsControl->tqs.control.opcq0_depth = TASK_QUEUE_TX0_DEPTH;
    tqsControl->tqs.control.opcq0_offset = TASK_QUEUE_TX0_OFFSET;

    p_oPCQ = &pTqs->txQ0;
    p_oPCQ->pProducerIdx = &tqsControl->tqs.cputable.op0_index;
    p_oPCQ->pConsumerIdx = &tqsControl->tqs.ncatable.oc0_index;
    p_oPCQ->pPCQbase = (void *) ((ncp_uintptr_t) tqsControl +
                              (tqsControl->tqs.control.opcq0_offset << 4));
    p_oPCQ->nEntries = tqsControl->tqs.control.opcq0_depth;
    p_oPCQ->nEntriesMinusOne = p_oPCQ->nEntries - 1;
    p_oPCQ->nEntriesMinusTwo = p_oPCQ->nEntries - 2;
    p_oPCQ->nEntriesDiv2     = p_oPCQ->nEntries / 2;
    p_oPCQ->cookie = NCP_TASK_PCQ_COOKIE;
    p_oPCQ->u.opcq_info.pOPCQentry = p_oPCQ->pPCQbase;
    p_oPCQ->u.opcq_info.pPrefetchEntry = p_oPCQ->u.opcq_info.pOPCQentry + 1;
    p_oPCQ->u.opcq_info.pLastEntry = p_oPCQ->u.opcq_info.pOPCQentry + p_oPCQ->nEntries - 1;
    p_oPCQ->u.opcq_info.relId = NCP_TASK_TXQ_0;
    p_oPCQ->u.opcq_info.numTxAvail = p_oPCQ->nEntries;
    p_oPCQ->hwProducerVal = 0;
    p_oPCQ->hwConsumerVal = 0;
    p_oPCQ->toggleBit = 0;
    if (pTqs->shareCtl.shareFlags.sharedTxQueue0)
    {
        p_oPCQ->shared = TRUE;
        /* NCP_CALL(ncp_task_v3_create_lock(&pTqs->txQ0.qLock, mtxAttr)); */
    }

    /* OPCQ_1 */
    memset(&pTqs->txQ1, 0, sizeof(ncp_pcq_info_t));

    tqsControl->tqs.control.opcq1_depth = TASK_QUEUE_TX1_DEPTH;
    tqsControl->tqs.control.opcq1_offset = TASK_QUEUE_TX1_OFFSET;

    p_oPCQ = &pTqs->txQ1;
    p_oPCQ->pProducerIdx = &tqsControl->tqs.cputable.op1_index;
    p_oPCQ->pConsumerIdx = &tqsControl->tqs.ncatable.oc1_index;
    p_oPCQ->pPCQbase = (void *) ((ncp_uintptr_t) tqsControl +
                              (tqsControl->tqs.control.opcq1_offset << 4));
    p_oPCQ->nEntries = tqsControl->tqs.control.opcq1_depth;
    p_oPCQ->nEntriesMinusOne = p_oPCQ->nEntries - 1;
    p_oPCQ->nEntriesMinusTwo = p_oPCQ->nEntries - 2;
    p_oPCQ->nEntriesDiv2     = p_oPCQ->nEntries / 2;
    p_oPCQ->cookie = NCP_TASK_PCQ_COOKIE;
    p_oPCQ->u.opcq_info.pOPCQentry = p_oPCQ->pPCQbase;
    p_oPCQ->u.opcq_info.pPrefetchEntry = p_oPCQ->u.opcq_info.pOPCQentry + 1;
    p_oPCQ->u.opcq_info.pLastEntry = p_oPCQ->u.opcq_info.pOPCQentry + p_oPCQ->nEntries - 1;
    p_oPCQ->u.opcq_info.relId = NCP_TASK_TXQ_1;
    p_oPCQ->u.opcq_info.numTxAvail = p_oPCQ->nEntries;
    p_oPCQ->hwProducerVal = 0;
    p_oPCQ->hwConsumerVal = 0;
    p_oPCQ->toggleBit = 0;
    if (pTqs->shareCtl.shareFlags.sharedTxQueue1)
    {
        p_oPCQ->shared = TRUE;
        /* NCP_CALL(ncp_task_v3_create_lock(&pTqs->txQ0.qLock, mtxAttr)); */
    }


    /* IPCQ */

    profile  = &pNcpTaskSwState->tqsSwState[0].pAppProfile->baseProfile;
    tqsControl->tqs.control.ipcq_depth = TASK_QUEUE_RX0_DEPTH;
    tqsControl->tqs.control.ipcq_offset = TASK_QUEUE_RX0_OFFSET;

    p_iPCQ = &pTqs->rxQ;
    p_iPCQ->pProducerIdx = &tqsControl->tqs.ncatable.ip_index;
    p_iPCQ->pConsumerIdx = &tqsControl->tqs.cputable.ic_index;
    p_iPCQ->pPCQbase = (void *) ((ncp_uintptr_t) tqsControl +
                              (tqsControl->tqs.control.ipcq_offset << 4));
    p_iPCQ->nEntries = tqsControl->tqs.control.ipcq_depth;
    p_iPCQ->u.ipcq_info.autoCompletionMode  =
        (profile->completionMode == NCP_TASK_AUTO_COMPLETION_MODE);
    p_iPCQ->u.ipcq_info.autoConsumptionMode =
        (profile->consumptionMode == NCP_TASK_IMMEDIATE_CONSUMPTION_MODE);

    pTqs->rxQ.nEntriesMinusOne  = pTqs->rxQ.nEntries - 1;
    pTqs->rxQ.nEntriesMinusTwo  = pTqs->rxQ.nEntries - 2;
    pTqs->rxQ.nEntriesDiv2      = pTqs->rxQ.nEntries / 2;
    pTqs->rxQ.cookie = NCP_TASK_PCQ_COOKIE;
    pTqs->rxQ.u.ipcq_info.pIPCQentry = pTqs->rxQ.pPCQbase;
    pTqs->rxQ.u.ipcq_info.pPrefetchEntry1 = pTqs->rxQ.u.ipcq_info.pIPCQentry + 1;
    pTqs->rxQ.u.ipcq_info.pPrefetchEntry2 = pTqs->rxQ.u.ipcq_info.pIPCQentry + 2;
    pTqs->rxQ.u.ipcq_info.pLastEntry = pTqs->rxQ.u.ipcq_info.pIPCQentry + pTqs->rxQ.nEntries - 1;
    pTqs->rxQ.hwProducerVal = 0;
    pTqs->rxQ.hwConsumerVal = 0;
    pTqs->rxQ.toggleBit = 0;
    pTqs->rxQ.u.ipcq_info.appConsumerVal = 0;
    pTqs->rxQ.u.ipcq_info.appToggleBit = 0;

    if (pTqs->shareCtl.shareFlags.sharedRxQueue)
    {
        pTqs->rxQ.shared = TRUE;
        /* NCP_CALL(ncp_task_v3_create_lock(&pTqs->rxQ.qLock, mtxAttr)); */
    }

    /*
     * All queues (iPCq, oPCQ, mPCQ) in a given TQS use the following two cache lines
     * for PGIT accesses.
     * We can use these values to get a little better cache prefetch distance for the PGITs
     */
    tmp = (ncp_uintptr_t)(((ncp_uintptr_t)pTqs->rxQ.pProducerIdx) & NCP_TASK_A53_CACHE_LINE_MASK);
    pTqs->pNcaPgit = (void *)tmp;

    tmp = (ncp_uintptr_t)(((ncp_uintptr_t)pTqs->rxQ.pConsumerIdx) & NCP_TASK_A53_CACHE_LINE_MASK);
    pTqs->pCpuPgit = (void *)tmp;

NCP_RETURN_LABEL
    return ncpStatus;

}


ncp_st_t
ncav3_free_hw(void)
{
	// free malloc from ncp_task_initialize_tbr_arrays();
	int i = 0, j =0;;
	for (i = 0; i< NCP_NCAV3_NUM_TASK_MEMORY_POOLS; i++){
		for (j = 0; j < NCP_TASK_NUM_BUFF_SIZES; j++){
			free((void *)pNcpTaskSwState->taskPools[i].pTbrArray[j]);
			pNcpTaskSwState->taskPools[i].pTbrArray[j] = 0;

		}
	}
	return NCP_ST_SUCCESS;
}

extern ncp_task_swState_t   pNcpTaskSwState_in_bss;

ncp_st_t
ncp_config_uboot_attach(ncp_uint32_t id, ncp_hdl_t *ncpHdl)
{
    ncp_st_t ncpStatus = NCP_ST_ERROR;
    /* ncp_t               *ncp = NULL; */
    ncp_ncav3_hdl_t *nca     = NULL;
    ncp_dev_hdl_t   devHdl;

    ncp = (ncp_t*)malloc(sizeof(ncp_t));
    memset(ncp, 0, sizeof(ncp_t));
    ncp->domainId = 0;
    ncp->domainIsInternal = TRUE;

    nca = (ncp_ncav3_hdl_t*)malloc(sizeof(ncp_ncav3_hdl_t));
    memset(nca, 0, sizeof(ncp_ncav3_hdl_t));


    nca->configInfo.domainInfo[ncp->domainId].virtBase = DOMAINBOUNDLE_VA;
    nca->configInfo.domainInfo[ncp->domainId].physBase = DOMAINBOUNDLE_PA;
    nca->configInfo.domainInfo[ncp->domainId].size = DOMAINBOUNDLE_SIZE;

    ncp->ncaHdl = (ncp_ncav3_hdl_t*)nca;
    ncp->cookie = NCP_HANDLE_COOKIE;
    ncp->id = id;
    nca->inConfigurationPhase = TRUE;

#ifdef NCP_USE_NVM
    pNvmLock = malloc(sizeof(ncp_mutex_t));
    pNvmActive = malloc(sizeof(ncp_bool_t));
#endif	/* NCP_USE_NVM */


#if defined(CONFIG_EIOA_BIG_STRUCT_IN_BSS)
	pNcpTaskSwState = &pNcpTaskSwState_in_bss;
#else
	pNcpTaskSwState = malloc(sizeof(ncp_task_swState_t));
#endif

	memset(pNcpTaskSwState,0,sizeof(ncp_task_swState_t));

	pNcpTaskSwState->taskIoResourceLock = malloc(sizeof(ncp_task_v3_mutex_t));
	memset(pNcpTaskSwState->taskIoResourceLock,0,sizeof(ncp_task_v3_mutex_t));


	pNcpTaskSwState->tqsSwState[0].tqsEnabled = TRUE;
	pNcpTaskSwState->tqsSwState[0].configured = TRUE;
    pNcpTaskSwState->tqsSwState[0].staticConfiguration = TRUE;
	pNcpTaskSwState->tqsSwState[0].validPoolsMask = 4; // just poolid 2
    pNcpTaskSwState->perDomainPoolsMask = 4;
  	pNcpTaskSwState->tqsSwState[0].pAppProfile = malloc(sizeof(ncp_ncav3_application_profile_t));
	memset(pNcpTaskSwState->tqsSwState[0].pAppProfile,0,sizeof(ncp_ncav3_application_profile_t));
	pNcpTaskSwState->tqsSwState[0].pAppProfile->baseProfile.uMode = TRUE;
	pNcpTaskSwState->tqsSwState[0].pAppProfile->baseProfile.completionMode = NCP_TASK_AUTO_COMPLETION_MODE;
    pNcpTaskSwState->tqsSwState[0].pAppProfile->baseProfile.consumptionMode = NCP_TASK_IMMEDIATE_CONSUMPTION_MODE;
	pNcpTaskSwState->uMode = TRUE;

	// to check
  	pNcpTaskSwState->tqsSwState[0].pCpuPgit = (void*)0x82000080;
  	pNcpTaskSwState->tqsSwState[0].pNcaPgit = (void*)0x820000c0;

	ncp_task_process_info_t **pidArray;
	pidArray = malloc(sizeof(ncp_task_process_info_t*) * 10);
	memset(pidArray, 0, sizeof(ncp_task_process_info_t*) * 10);
	pNcpTaskSwState->currPidArrayEntries = 10;
	pNcpTaskSwState->pidArray = pidArray;

	devHdl = 0;
    myDevHdl = devHdl;
    ncp_dev_hdls[0] = devHdl;

    *ncpHdl = ncp;
    mme_config(ncp);
    ncav3_config_hw(ncp);

    ncp_task_tqs_swState_t *pTqs     = NULL;
    ncp_task_mme_allocator_t *pAllocator = NULL;
    ncp_task_pcq_t *p_mPCQ;

    pTqs = &pNcpTaskSwState->tqsSwState[0];
    pAllocator = &pTqs->mmeAllocator[SHARED_BUFFER_POOL2];

    p_mPCQ = &pAllocator->mPCQ[0];
    debug("entries: %d, base: %p\n", p_mPCQ->nEntries, p_mPCQ->pPCQbase);

	pNcpTaskSwState->tqsSwState[0].tqsEnabled = TRUE;
	pNcpTaskSwState->tqsSwState[0].configured = TRUE;

	return NCP_ST_SUCCESS;

NCP_RETURN_LABEL
    return ncpStatus;
}



ncp_st_t
ncp_config_uboot_detach(ncp_hdl_t *ncpHdl)
{
	clean_memory_eioa();
	mme_destroy(ncp);
	ncav3_free_hw();

#ifdef NCP_USE_NVM
	free(pNvmLock);
	pNvmLock = 0;
	free(pNvmActive);
	pNvmActive = 0;
#endif	/* NCP_USE_NVM */

	free(pNcpTaskSwState->taskIoResourceLock);
	free(pNcpTaskSwState->tqsSwState[0].pAppProfile);
	free(pNcpTaskSwState->pidArray);
#if defined(CONFIG_EIOA_BIG_STRUCT_IN_BSS)
	/*pNcpTaskSwState_in_bss stays in .bss forever*/;
#else 
	free(pNcpTaskSwState);
#endif
	pNcpTaskSwState = NULL;
	free(ncp->ncaHdl); // this will free nca;
	free(ncp);
	ncp = NULL;
	return NCP_ST_SUCCESS;
}

void
clean_memory_eioa(void)
{
	// clear domain bundle
	memset((void*)DOMAINBOUNDLE_PA,0,DOMAINBOUNDLE_SIZE);
	// clear memory pool
	memset((void*)POOL_2_PA,0,POOL_2_SIZE);
}

void
print_memory_eioa(void)
{
	printf("LSI_EIOA uses:\n"
	"-> DomainBoundle	0x%08llX - 0x%08llX\n" /* domain bundle */
	"-> Pool2		0x%08llX - 0x%08llX\n", /* memory pool 2 */
	DOMAINBOUNDLE_PA, DOMAINBOUNDLE_PA+DOMAINBOUNDLE_SIZE,
	POOL_2_PA, POOL_2_PA+POOL_2_SIZE);
}
