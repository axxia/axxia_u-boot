/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2017, Intel Corporation.                        *
 **                                                                       *
 **************************************************************************/

#include <common.h>
#include <malloc.h>

#include "uboot/ncp_sal_types_linux.h"
#include "uboot/ncp_task_basetypes.h"

#include "uboot/ncp.h"
#include "uboot/ncp_pvt.h"
#include "uboot/ncp_cow_ext.h"
#undef  NCP_TASK_NCA_GLOBALS
#include "uboot/ncp_dev_pvt.h"
#include "uboot/ncp_task_pvt.h"
#include "uboot/ncp_ncav3_pvt.h"
#include "uboot/ncp_task_hw.h"

#if !defined(NCP_DEV_SOCKET) && !defined(NCP_DEV_FBRS) && !defined(NCP_DEV_FBDEV)
#include "uboot/ncp_task_inline_funcs.h"
#endif

#if !defined(NCP_KERNEL) && defined(NCP_NCA_ARM_PMU_PROFILING_ENABLED)
#ifdef NCP_TASK_PROFILE_TXTASK_UPDATE
    static ncp_update_task_pmu_results_t pmu_tx_task_update_results[NCP_MAX_PMU_RESULTS];
    static int numPmuTxTaskUpdateResults=0;    
#endif
#ifdef NCP_TASK_PROFILE_RXTASK_UPDATE
    static ncp_update_task_pmu_results_t pmu_rx_task_update_results[NCP_MAX_PMU_RESULTS];
    static int numPmuRxTaskUpdateResults=0;    
#endif    
#endif


/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Process Management Interface
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 */
ncp_st_t ncp_task_getpid(ncp_pid_t *pPid)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    *pPid = (ncp_pid_t) ncp_get_pid();    

NCP_RETURN_LABEL
    return(ncpStatus);
}


#if (1 == NCP_TASK_TBR_ENABLED) 
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * TBR Support Functions
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 */
 
 
ncp_st_t
ncp_task_initialize_tbr_arrays(void)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    int poolId;

    for (poolId = NCP_NCAV3_FIRST_SHARED_POOL_ID;
            poolId <= NCP_NCAV3_LAST_CPU_POOL_ID;
            poolId++)
    {
        int j;

        if (pNcpTaskSwState->taskPools[poolId].tbrArraysInitialized)
        {
            /* Already initialized */
            continue;
        }

        if (pNcpTaskSwState->perDomainPoolsMask & (1 << poolId))
        {
            for (j = 0; j < NCP_TASK_NUM_BUFF_SIZES; j++)
            {
                ncp_uint32_t numBuffers;

                if (0 != (numBuffers = pNcpTaskSwState->taskPools[poolId].numBlocks[j]))
                {
                    /* allocate and memset tbr tracking array for this pool */
                    /* TODO */
                    NCP_CALL(ncp_nvm_robust_malloc(numBuffers * sizeof(ncp_task_pid_t),
                                (void **)&pNcpTaskSwState->taskPools[poolId].pTbrArray[j],
                                NCP_DO_MEMSET));
                    pNcpTaskSwState->taskPools[poolId].numTbrEntries[j] = numBuffers;
                    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                          ncp_xlf_task_initialize_tbr_arrays_poolEntryInfo,
                                          NCP_MSG_DEBUG,
                                          "Pool %d TbrArray for sz %d @ %p has %d entries\r\n",
                                          poolId, j,
                                          (void *) pNcpTaskSwState->taskPools[poolId].pTbrArray[j],
                                          numBuffers);
                }
                else
                {
                    /* buffer size not configured */
                    pNcpTaskSwState->taskPools[poolId].pTbrArray[j]      = NULL;
                    pNcpTaskSwState->taskPools[poolId].numTbrEntries[j] = 0;
                }
            }

            pNcpTaskSwState->taskPools[poolId].tbrArraysInitialized = TRUE;
        }
        else
        {
            /* pool not used by this domain */
            pNcpTaskSwState->taskPools[poolId].pTbrArray[0]      = NULL;
            pNcpTaskSwState->taskPools[poolId].pTbrArray[1]      = NULL;
            pNcpTaskSwState->taskPools[poolId].pTbrArray[2]      = NULL;
            pNcpTaskSwState->taskPools[poolId].pTbrArray[3]      = NULL;
            pNcpTaskSwState->taskPools[poolId].numTbrEntries[0] = 0;
            pNcpTaskSwState->taskPools[poolId].numTbrEntries[1] = 0;
            pNcpTaskSwState->taskPools[poolId].numTbrEntries[2] = 0;
            pNcpTaskSwState->taskPools[poolId].numTbrEntries[3] = 0;
        }
    }

NCP_RETURN_LABEL

    return ncpStatus;
}


ncp_st_t
ncp_task_tbr_unbind_threads(ncp_task_process_info_t *pProcess) 
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_thread_info_t  *pThread; 
    
    
    pThread = pProcess->activeThreads;     
    while (pThread) 
    {
        /* gratuitous unbind */  
        NCP_CALL(ncp_task_internal_tqs_unbind(pThread->recoveryTqsHdl,
                                              TRUE,
                                              TRUE));
                                              
        pThread = pThread->pNextThread;
    } 
    
NCP_RETURN_LABEL       
    return(ncpStatus);                              
}


ncp_st_t
ncp_task_tbr_global_pool_refill_recovery(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl) 
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_int64_t refillsOwed[4] = {0,0,0,0};
    ncp_uint32_t buffSizes[4] = {256, (2*1024), (16*1024), (64*1024)};    
    ncp_task_tqs_swState_t *pTqs;
    int i;
    ncp_task_pcq_t *p_oPCQ;
    ncp_uint32_t numDone;
    void *pBuffer;
    ncp_task_pool_t *pCpuPool = pvtTqsHdl->cpuPoolHdl;
    
    /* 
     * Run all of the TQSets that use this CPU pool,   and verify that no refills are owed.
     * Note that if a particular TQS owes refills,   another may have a negative count and counteract
     * it due to having performed refills not associated with a received task.
     */
    if (NULL != (pTqs = pCpuPool->u.cpu.pCpuPoolTQSets))
    {     
        do {
           /* At the tqs level,   refills owed accounts for all refills issued as well */ 
           refillsOwed[0] += pTqs->tqsRefillsOwed[0];
           refillsOwed[1] += pTqs->tqsRefillsOwed[1];
           refillsOwed[2] += pTqs->tqsRefillsOwed[2];
           refillsOwed[3] += pTqs->tqsRefillsOwed[3];
           
           /* Zero counters */
           pTqs->tqsRefillsOwed[0] = 0;
           pTqs->tqsRefillsOwed[1] = 0;
           pTqs->tqsRefillsOwed[2] = 0;
           pTqs->tqsRefillsOwed[3] = 0;     
        } while (NULL != (pTqs = pTqs->pNextCpuPoolTqs));                                       

    }
    else
    {
        NCP_CALL(NCP_ST_INTERNAL_ERROR);
    }  
    
    /* Now perform the refills, if any */

    pTqs = pCpuPool->u.cpu.pCpuPoolTQSets;
    p_oPCQ = &pTqs->txQ0; /* Guaranteed available during recovery */
                
    for (i=0; i<4; i++)
    {
        if (refillsOwed[i])
        {
            NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                  ncp_xlf_task_tbr_global_pool_refill_recovery_attemptingToIssueRefillsWhenRecovering,
                                  NCP_MSG_INFO,
                                  "Attempting to issue %d refills for buffer size=%d when recovering pool %d\r\n",
                                  (int)(refillsOwed[i]),
                                  (int)buffSizes[i],
                                  (int)pCpuPool->poolId);

            do
            {
                /* Allocate a buffer. (NOTE:  no contention for pool while in recovery) */
                NCP_CALL(ncp_task_CpuPool_alloc_noLock(pvtTqsHdl,
                                                       pCpuPool,
                                                       buffSizes[i],
                                                       &pBuffer));

                NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                      ncp_xlf_task_tbr_global_pool_refill_recovery_allocatedBuffer,
                                      NCP_MSG_INFO, "Allocated buffer %p",
                                      pBuffer);

                /* Perform refill by issuing free command to oPCQ */
                NCP_CALL(ncp_task_bulk_buffer_free(pvtTqsHdl,
                                                  p_oPCQ,
                                                  NCP_TASK_CPU_POOL_ALIAS,
                                                  1,
                                                  &numDone,
                                                  &pBuffer,
                                                  FALSE, /* no mRef for CPU pools */
                                                  TRUE));

                NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                      ncp_xlf_task_tbr_global_pool_refill_recovery_done,
                                      NCP_MSG_INFO, "... Done\r\n");

                refillsOwed[i]--;    
            } while(refillsOwed[i]);                       
        }        
    }  
  
    /* TODO */
NCP_RETURN_LABEL
    if (NCP_ST_SUCCESS != ncpStatus)
    {
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_tbr_global_pool_refill_recovery_poolUseCountZeroWhenRefillsStillOwed,
                              NCP_MSG_ERROR,
                              "Pool use count going to zero when NCA Rx Buffer Refills Are Still Owed\r\n");
        if (NULL != (pTqs = pCpuPool->u.cpu.pCpuPoolTQSets))
        {
            NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                  ncp_xlf_task_tbr_global_pool_refill_recovery_rxBuffersRequired,
                                  NCP_MSG_ERROR,
                                  "The NCA requires %6d 256B, %0d 2KB %6d 16KB, and %6d 64KB receive buffers from pool %d\r\n",
                                  (int)(refillsOwed[0]),
                                  (int)(refillsOwed[1]),
                                  (int)(refillsOwed[2]),
                                  (int)(refillsOwed[3]),
                                  (int)pCpuPool->poolId);
        }
    }        
    return(ncpStatus);
}    

ncp_st_t
ncp_task_tbr_update_per_tqs_cpupool_refill_count(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl)
{                                                                              
    ncp_st_t ncpStatus = NCP_ST_SUCCESS; 
    ncp_task_tqs_swState_t *pTqs;  
     
    if (0 != pvtTqsHdl->cpuPoolId)                                           
    {
        pTqs = pvtTqsHdl->pTqs;                                                                  
        pTqs->tqsRefillsOwed[0] += (pvtTqsHdl->perHdlRefillsOwed[0] - (pvtTqsHdl->perHdlRefillsIssued[NCP_TASK_TXQ_0][0] + pvtTqsHdl->perHdlRefillsIssued[NCP_TASK_TXQ_1][0]));    
        pTqs->tqsRefillsOwed[1] += (pvtTqsHdl->perHdlRefillsOwed[1] - (pvtTqsHdl->perHdlRefillsIssued[NCP_TASK_TXQ_0][1] + pvtTqsHdl->perHdlRefillsIssued[NCP_TASK_TXQ_1][1]));                            
        pTqs->tqsRefillsOwed[2] += (pvtTqsHdl->perHdlRefillsOwed[2] - (pvtTqsHdl->perHdlRefillsIssued[NCP_TASK_TXQ_0][2] + pvtTqsHdl->perHdlRefillsIssued[NCP_TASK_TXQ_1][2]));                       
        pTqs->tqsRefillsOwed[3] += (pvtTqsHdl->perHdlRefillsOwed[3] - (pvtTqsHdl->perHdlRefillsIssued[NCP_TASK_TXQ_0][3] + pvtTqsHdl->perHdlRefillsIssued[NCP_TASK_TXQ_1][3]));    
          
        /*
         * Zero counts to make sure we never double count
         */
         
        pvtTqsHdl->perHdlRefillsOwed[0] = pvtTqsHdl->perHdlRefillsIssued[NCP_TASK_TXQ_0][0] = pvtTqsHdl->perHdlRefillsIssued[NCP_TASK_TXQ_1][0]  = 0;
        pvtTqsHdl->perHdlRefillsOwed[1] = pvtTqsHdl->perHdlRefillsIssued[NCP_TASK_TXQ_0][1] = pvtTqsHdl->perHdlRefillsIssued[NCP_TASK_TXQ_1][1]  = 0;
        pvtTqsHdl->perHdlRefillsOwed[2] = pvtTqsHdl->perHdlRefillsIssued[NCP_TASK_TXQ_0][2] = pvtTqsHdl->perHdlRefillsIssued[NCP_TASK_TXQ_1][2]  = 0;
        pvtTqsHdl->perHdlRefillsOwed[3] = pvtTqsHdl->perHdlRefillsIssued[NCP_TASK_TXQ_0][3] = pvtTqsHdl->perHdlRefillsIssued[NCP_TASK_TXQ_1][3]  = 0;                        
                              
    }     
    
NCP_RETURN_LABEL                                                                            
    return(ncpStatus);
} 

ncp_st_t 
ncp_task_tbr_buffers_recover(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
                             ncp_task_pid_t searchPid)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    int poolId;
    ncp_uint32_t numFreed;
    ncp_bool_t   mRef = FALSE;
    ncp_uint32_t buffSizes[4] = {256, (2*1024), (16*1024), (64*1024)};         

#if 0
    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                          ncp_xlf_task_tbr_buffers_recover_params, NCP_MSG_INFO,
                          "In buffers recover fn, searchPid=%d, tqsHdl=%p, poolsMask =0x%x\r\n",
                          searchPid, pvtTqsHdl, pvtTqsHdl->pProcess->poolsMask );
#endif

    for (poolId  = NCP_NCAV3_FIRST_SHARED_POOL_ID; 
         poolId <= NCP_NCAV3_LAST_CPU_POOL_ID;
         poolId++)
    {
        int i,buffSz;
        ncp_task_pool_t *pPool;
        
        if (0 == (pvtTqsHdl->pProcess->poolsMask  & (1<<poolId)))
        {
            continue;
        }
        
        pPool = &pNcpTaskSwState->taskPools[poolId];
        
        if (FALSE == pPool->valid)
        {
            continue;
        }

#if 0
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_tbr_buffers_recover_checkingPool,
                              NCP_MSG_INFO,
                              "In buffers recover fn, checking pool=%d\r\n",
                              poolId);
#endif

        /* 
         * for each buffer size, search tbr data for buffers owned by this process 
         */
        for (buffSz=0; buffSz<=3; buffSz++)
        {
            int numEntries = pPool->numTbrEntries[buffSz];
            volatile ncp_task_pid_t *pTbrEntry = pPool->pTbrArray[buffSz]; 
            int matched=0;
            
            for(i=0; i < numEntries; i++)
            {
                if (searchPid == pTbrEntry[i])
                {  
                    void *buffVa;
                                                          
                    buffVa = (void *)(ncp_uintptr_t) (((ncp_uintptr_t)(pPool->blocksVA[buffSz])) + (i * buffSizes[buffSz])); 
                    matched++;

#if 0
                    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                          ncp_xlf_task_tbr_buffers_recover_bufferInfo,
                                          NCP_MSG_INFO,
                                          "buffVa=%p, addr of buffVa=%p, blocksVa=%p, i=%d, sz=%d\r\n",
                                          buffVa, &buffVa,
                                          (void *)(pPool->blocksVA[buffSz]),
                                          i, buffSizes[buffSz]);
#endif

                    /* Optimize - free multiple buffers per invocation */                    
                    if (poolId < NCP_NCAV3_FIRST_CPU_POOL_ID)
                    {

#if 0
                        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                              ncp_xlf_task_tbr_buffers_recover_freeingRecoveredBufferToMME,
                                              NCP_MSG_INFO,
                                              "Freeing recovered buffer %p to MME\r\n",
                                              buffVa);
#endif

                        NCP_CALL(ncp_task_bulk_buffer_free( 
                                 pvtTqsHdl,
                                 &pvtTqsHdl->pTqs->txQ0,         /* use any txq while in recovery */
                                 poolId,
                                 1, 
                                 &numFreed, 
                                 &buffVa,          
                                 &mRef,
                                 TRUE));
                    }
                    else
                    {
#if 0
                        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                              ncp_xlf_task_tbr_buffers_recover_freeingRecoveredBufferToCpuPoolFreeList,
                                              NCP_MSG_INFO,
                                              "Freeing recovered buffer %p to CPU Pool Free List\r\n",
                                              buffVa);
#endif

                        NCP_CALL(ncp_task_bulk_cpu_pool_buffer_free(pvtTqsHdl,
                                  1,
                                  &numFreed, 
                                  &buffVa));                        
                    }             

                }    
            }   
            if (matched)
            {
                    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                          ncp_xlf_task_tbr_buffers_recover_numBuffersRecovered,
                                          NCP_MSG_INFO,
                                          "%d buffers sz=%d in pool %d were recovered for process %s pid=%d\n",
                                          matched,
                                          buffSz,
                                          poolId,
                                          pNcpTaskSwState->pidArray[searchPid]->clientProcess.name,
                                          searchPid);
            }
        }
    }

NCP_RETURN_LABEL    
    return(ncpStatus);
}
                                 
ncp_st_t 
ncp_task_tbr_leak_check(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
                        ncp_task_pid_t searchPid)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    int poolId;
    
    for (poolId  = NCP_NCAV3_FIRST_SHARED_POOL_ID; 
         poolId <= NCP_NCAV3_LAST_CPU_POOL_ID;
         poolId++)
    {
        int i,buffSz;
        ncp_task_pool_t *pPool = &pNcpTaskSwState->taskPools[poolId];
        
        if (0 == (pvtTqsHdl->pProcess->poolsMask  & (1<<poolId)))
        {
            continue;
        }
        
        if (FALSE == pPool->valid)
        {
            continue;
        }
        
        /* for each buffer size */
        for (buffSz=0; buffSz<=3; buffSz++)
        {
            int numEntries = pPool->numTbrEntries[buffSz];
            volatile ncp_task_pid_t *pTbrEntry = pPool->pTbrArray[buffSz]; 
            int matched=0;
            
            for(i=0; i < numEntries; i++)
            {
                if (searchPid == pTbrEntry[i])
                {    
                    /* set error status,   but continue checking so we get an accurate count */
                    ncpStatus = NCP_ST_TASK_BUFFER_LEAK;
                    matched++;
                }    
            }   
            if (matched)
            {
                    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                          ncp_xlf_task_tbr_leak_check_buffersInPoolOwnedByProcess,
                                          NCP_MSG_ERROR,
                                          "%d buffers sz=%d in pool %d are owned by process %s pid=%d\n",
                                          matched,
                                          buffSz,
                                          poolId,
                                          pNcpTaskSwState->pidArray[searchPid]->clientProcess.name,
                                          searchPid);
            }
        }
    }
    return(ncpStatus);
}  




ncp_st_t
ncp_task_tbr_task_buffer_pid_get( ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
                                            ncp_uint8_t poolId,
                                            void *pBuffer,
                                            ncp_task_pid_t *pPid)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_pool_t *pPool;
    volatile ncp_task_pid_t *tbrArray;
    ncp_uint64_t tbrOffset = (ncp_uint64_t)(ncp_uintptr_t)pBuffer;                                                

    if (poolId != 0)
    {    
        pPool = &pNcpTaskSwState->taskPools[poolId];
    }
    else
    {
        pPool = pvtTqsHdl->cpuPoolHdl;
    }            
    if ((tbrOffset >= pPool->blocksVA[0]) && (tbrOffset < pPool->blocksVAend[0]))
    {
        /* 256B - normalize and convert to buffer number (0..last) */
        tbrOffset -= pPool->blocksVA[0];
        /* convert to offset */
        tbrOffset = (tbrOffset & ~(256-1)) >> 7;
        tbrArray = (ncp_task_pid_t *)(ncp_uintptr_t)
            (((ncp_uintptr_t)pPool->pTbrArray[0]) + tbrOffset); /* Assumes 16 bit PID! */
    }        
    else if ((tbrOffset >= pPool->blocksVA[1]) && (tbrOffset < pPool->blocksVAend[1]))
    {
        /* 2K - normalize and convert to buffer number (0..last) */
        tbrOffset -= pPool->blocksVA[1]; 
        /* convert to offset */              
        tbrOffset = (tbrOffset & ~((2*1024)-1)) >> 10;
        tbrArray = (ncp_task_pid_t *)(ncp_uintptr_t)
            (((ncp_uintptr_t)pPool->pTbrArray[1]) + tbrOffset); /* Assumes 16 bit PID! */
    }   
    else if ((tbrOffset >= pPool->blocksVA[2]) && (tbrOffset < pPool->blocksVAend[2]))
    {
        /* 16K - normalize and convert to buffer number (0..last) */
        tbrOffset -= pPool->blocksVA[2];
        /* convert to offset */        
        tbrOffset = (tbrOffset & ~((16*1024)-1)) >> 13;       
        tbrArray = (ncp_task_pid_t *)(ncp_uintptr_t)
            (((ncp_uintptr_t)pPool->pTbrArray[2]) + tbrOffset); /* Assumes 16 bit PID! */
    }   
    else if ((tbrOffset >= pPool->blocksVA[3]) && (tbrOffset < pPool->blocksVAend[3]))
    {
        /* 64K - normalize and convert to buffer number (0..last) */
        tbrOffset -= pPool->blocksVA[3];
        /* convert to offset */        
        tbrOffset = (tbrOffset & ~((64*1024)-1)) >> 15;       
        tbrArray = (ncp_task_pid_t *)(ncp_uintptr_t)
            (((ncp_uintptr_t)pPool->pTbrArray[3]) + tbrOffset); /* Assumes 16 bit PID! */
    } 
    else
    {
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_tbr_task_buffer_pid_get_invalidBuffer,
                              NCP_MSG_ERROR, "TBR: Invalid buffer %p\r\n",
                              (void *)pBuffer);
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_tbr_task_buffer_pid_get_pool,
                              NCP_MSG_ERROR, "pool=%d\r\n",
                              (int)pPool->poolId);
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_tbr_task_buffer_pid_get_blocksVAStartEnd,
                              NCP_MSG_ERROR, "blocksVA[%d] start=%p, end=%p\r\n",
                              0, (void *)pPool->blocksVA[0], (void *)pPool->blocksVAend[0]);
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_tbr_task_buffer_pid_get_blocksVAStartEnd,
                              NCP_MSG_ERROR, "blocksVA[%d] start=%p, end=%p\r\n",
                              1, (void *)pPool->blocksVA[1], (void *)pPool->blocksVAend[1]);
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_tbr_task_buffer_pid_get_blocksVAStartEnd,
                              NCP_MSG_ERROR, "blocksVA[%d] start=%p, end=%p\r\n",
                              2, (void *)pPool->blocksVA[2], (void *)pPool->blocksVAend[2]);
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_tbr_task_buffer_pid_get_blocksVAStartEnd,
                              NCP_MSG_ERROR, "blocksVA[%d] start=%p, end=%p\r\n",
                              3, (void *)pPool->blocksVA[3], (void *)pPool->blocksVAend[3]);
        NCP_CALL(NCP_ST_TASK_TBR_INVALID_BUFFER);
    }
    
    *pPid = *tbrArray;
                            
NCP_RETURN_LABEL
    return(ncpStatus);
}  

#endif /* NCP_TASK_TBR_ENABLED */

ncp_st_t                    
ncp_task_recover_tqs_hdl_by_thread(ncp_task_resource_name_t *processName, 
                                   ncp_task_resource_name_t *threadName, 
                                   ncp_uint32_t             tqsId, 
                                   ncp_task_pvt_tqsHdl_data_t **pPvtTqsHdl)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_thread_info_t  *pThread=NULL;
    ncp_task_process_info_t *pProcess = NULL;    
    
    /* Find the process,  and then the thread */
    pProcess = pNcpTaskSwState->activeProcesses;
    while (NULL != pProcess)
    {
        if (0 == strncmp(&pProcess->clientProcess.name[0], 
                         &processName->name[0],
                         sizeof(ncp_task_resource_name_t)))
        {
            pThread = pProcess->activeThreads;
            while (NULL != pThread)
            { 
                if ((tqsId == pThread->tqsId) 
                    && (0 == strncmp(&pThread->clientThread.name[0], 
                                     &threadName->name[0],
                                     sizeof(ncp_task_resource_name_t))))
                {
                    /* found it! */
                    *pPvtTqsHdl = pThread->recoveryTqsHdl;
                    NCP_JUMP_RETURN();
                }                     
                pThread = pThread->pNextThread;        
            }                
            NCP_CALL(NCP_ST_TASK_THREAD_NOT_FOUND);
        }                     
        pProcess = pProcess->pNextProcess;
    }  
    NCP_CALL(NCP_ST_TASK_PROCESS_NOT_FOUND);            
    
NCP_RETURN_LABEL
    
    return(ncpStatus);
}  

ncp_st_t
ncp_task_process_name_validate( ncp_task_resource_name_t *processName,
                                ncp_task_resource_name_t *threadName,
                                ncp_uint32_t tqsId,
                                ncp_task_process_info_t **ppProcess)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_process_info_t *pProcess;
    ncp_task_thread_info_t  *pThread;
        
    /*
     * Check for process name uniqueness
     */
     
    pProcess = pNcpTaskSwState->activeProcesses;

#if 0
    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                          ncp_xlf_task_add_thread_checkingProcessNameUniqueness,
                          NCP_MSG_INFO,
                          "Checking for process name uniqueness, pNcpTaskSwState->activeProcesses=%p\r\n",
                          pProcess);
#endif

    while (NULL != pProcess)
    {
        
#if 0
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_add_thread_checkingProcessNameAgainstStoredProcessName,
                              NCP_MSG_INFO,
                              "Checking processName %s vs stored process name %s\r\n",
                              &processName->name[0],
                              &pProcess->clientProcess.name[0]);
#endif

        if (0 == strncmp(&pProcess->clientProcess.name[0], 
                         &processName->name[0],
                         sizeof(ncp_task_resource_name_t)))
        {
#if 0
            NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                  ncp_xlf_task_add_thread_processNameMatched,
                                  NCP_MSG_INFO, "ProcessName Matched\r\n");
#endif

            /* 
             * Process name matched.  If thread name matches existing thread,   then it is a process restart.
             * Otherwise it is just a new thread starting.
             */
             
            pThread = pProcess->activeThreads;
            while (NULL != pThread)
            {

#if 0
                NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                      ncp_xlf_task_add_thread_checkingThreadNameTqsId,
                                      NCP_MSG_INFO,
                                      "Checking threadName %s tqsId %d vs stored threadName %s tqsId=%d\r\n",
                                      &threadName->name[0],
                                      tqsId,
                                      &pThread->clientThread.name[0],
                                      pThread->tqsId);
#endif

                if ((tqsId == pThread->tqsId) 
                    && (0 == strncmp(&pThread->clientThread.name[0], 
                                     &threadName->name[0],
                                     sizeof(ncp_task_resource_name_t))))
                {
                    NCP_CALL(NCP_ST_TASK_PROCESS_RESTART_DETECTED);
                }                     
                pThread = pThread->pNextThread;        
            }
            
            /* Different Linux PID using same name,   and not a restart? */
            
            NCP_CALL(ncp_task_os_pid_match_check(pProcess, TRUE, NCP_ST_TASK_PROCESS_NAME_NOT_UNIQUE));
            
            break; /* valid "new" process/thread combo add,  so get out  */
            
        }  
        else
        {
            /* All threads in a process must use same process name,  we check for that here */
            NCP_CALL(ncp_task_os_pid_match_check(pProcess, FALSE, NCP_ST_TASK_PROCESS_NAME_MISMATCH));
        }                           
        pProcess = pProcess->pNextProcess;
    }  /* while */  
    
NCP_RETURN_LABEL

    *ppProcess = pProcess;
    return(ncpStatus);        
}   


ncp_st_t
ncp_task_add_thread(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
                    ncp_task_resource_name_t *processName,
                    ncp_task_resource_name_t *threadName,
                    ncp_uint32_t tqsId,
                    ncp_task_process_info_t **ppProcess)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    int i;

    ncp_task_thread_info_t  *pThread=NULL;
    ncp_task_process_info_t *pProcess=NULL;    


#if 0
    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                          ncp_xlf_task_add_thread_processThreadParams,
                          NCP_MSG_INFO,
                          "Add thread -   processName %s threadName %s\r\n",
                          &processName->name[0], &threadName->name[0]);
#endif


    NCP_CALL(ncp_task_process_name_validate(processName, threadName, tqsId, &pProcess));

    /*
     * If process name did not already exist,   then add it
     */

    if (NULL == pProcess)
    {
    
        /* 
         * Do we need to grow the pidArray?
         * Account for "NCP_TASK_TBR_FIRST_APPLICATION_PID" reserved entries (0,1) when checking for full 
         */
        if (pNcpTaskSwState->currPidArrayEntries 
            == (pNcpTaskSwState->numActivePids + NCP_TASK_TBR_FIRST_APPLICATION_PID))
        {
            ncp_task_process_info_t **newProcessNamesPtr;
            
            NCP_CALL(ncp_nvm_robust_realloc( pNcpTaskSwState->pidArray, 
                                    ((pNcpTaskSwState->currPidArrayEntries + 1024) 
                                     * sizeof(ncp_task_process_info_t *)),
                                    (void **)&newProcessNamesPtr));
            memset(&newProcessNamesPtr[pNcpTaskSwState->currPidArrayEntries],
                   0,
                   (1024*sizeof(ncp_task_process_info_t *)));
            pNcpTaskSwState->currPidArrayEntries += 1024;
            pNcpTaskSwState->pidArray = newProcessNamesPtr;       
        }                                       
            
        /* 
         * Now find a free slot in pidArray - this is a new uniqueue client process 
         */
        for (i = NCP_TASK_TBR_FIRST_APPLICATION_PID; 
             i < pNcpTaskSwState->currPidArrayEntries; 
             i++)
        {
            if (NULL == pNcpTaskSwState->pidArray[i])
            {
                /*
                 * Add this process
                 */
                pNcpTaskSwState->pidArray[i] = malloc(sizeof(ncp_task_process_info_t));
				memset( pNcpTaskSwState->pidArray[i],0,sizeof(ncp_task_process_info_t)); 
                pProcess =  pNcpTaskSwState->pidArray[i];            
                strncpy(&pProcess->clientProcess.name[0], 
                        &processName->name[0], 
                        sizeof(ncp_task_resource_name_t));   
                pNcpTaskSwState->numActivePids++;                          
                /* save PID */
                pProcess->pid = i;
                /* save pointer to process struct in tqs handle */
                pvtTqsHdl->pProcess = pProcess;            
                NCP_CALL(ncp_task_os_pid_store(pProcess));  /* Save the real linux pid (if user mode) in the new entry */

#if 0
                NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                      ncp_xlf_task_add_thread_addedPID,
                                      NCP_MSG_INFO,
                                      "Added pid %d for processName %s, threadName %s \r\n",
                                      i,
                                      &processName->name[0],
                                      &threadName->name[0]);
#endif

                break;     
            }         
        }
    
        if (i == pNcpTaskSwState->currPidArrayEntries)
        {
            NCP_CALL(NCP_ST_TASK_OUT_OF_PIDS);
        }

    }   /* if (NULL == pProcess) */
    else
    {
        /* save pointer to process struct in tqs handle */
        pvtTqsHdl->pProcess = pProcess;
    }
 
#if 0
    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                          ncp_xlf_task_add_thread_settingPID,
                          NCP_MSG_INFO,
                          "Setting PID to %d\r\n",
                          i);
#endif
    
    /* 
     * check for thread name uniqueness
     */                              
    pThread = pProcess->activeThreads;
    while (NULL != pThread)
    { 
        if (0 == strncmp(&pThread->clientThread.name[0], 
                         &threadName->name[0],
                         sizeof(ncp_task_resource_name_t)))
        {
            NCP_CALL(NCP_ST_TASK_THREAD_NAME_NOT_UNIQUE);
        }                     
        pThread = pThread->pNextThread;        
    }

    /* Add thread struct to process-local linked list */            
    pThread = &pvtTqsHdl->thisThread;
    pThread->recoveryTqsHdl = pvtTqsHdl;    /* used for TBR recovery */
    pThread->pNextThread = pProcess->activeThreads;
    pThread->pParentProcess = pProcess;
    pProcess->activeThreads = pThread;
    pProcess->numThreads++;
    
    /* save thread name and tqsId in thread struct - which is actually part of pvt tqs handle */
    pThread->tqsId = tqsId;    
    strncpy(&pvtTqsHdl->thisThread.clientThread.name[0],
            &threadName->name[0],
            sizeof(ncp_task_resource_name_t)); 

#if 0
    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                          ncp_xlf_task_add_pProcess_to_tqsHdl,
                          NCP_MSG_INFO,
                          "Setting pProcess in tqsHdl %p to %p\r\n",
                          pvtTqsHdl,
                          pvtTqsHdl->pProcess);
#endif

    /* TODO - need linked list of all threads sharing this tqs? */
        
    /* If this is a new process,   hook it */
    if (1 == pProcess->numThreads)
    {
        pProcess->pNextProcess = pNcpTaskSwState->activeProcesses;          
        pNcpTaskSwState->activeProcesses = pProcess;        
    }        
    
NCP_RETURN_LABEL

    *ppProcess = pProcess;  /* Return result to caller,   even if failed due to restart required */
    return(ncpStatus);
}   


static ncp_st_t
ncp_task_pool_mutex_reset_default(ncp_task_pool_t *pPool, ncp_pid_t pid)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    runtime_mutex_attr_state_t *mtxAttr = &pPool->mtxAttr;

    if (NCP_MUTEX_PROCESS_SHARED_ROBUST != mtxAttr->attr)
    {
        mtxAttr->attr = NCP_MUTEX_PROCESS_SHARED_ROBUST;
        mtxAttr->pid = 0;
        if (NCP_TASK_V3_MUTEX_HDL_ALLOCATED(&(pPool->poolLock)))
        {
            if (NCP_MUTEX_PROCESS_PRIVATE == NCP_TASK_V3_MUTEX_HDL_FLAGS(&(pPool->poolLock)) &&
                pid != NCP_TASK_V3_MUTEX_HDL_PID(&(pPool->poolLock)))
            {
                NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                      ncp_xlf_task_pool_mutex_reset_default_pid_mismatch,
                                      NCP_MSG_ERROR,
                                      "Attempt to reset pool=%d lock, but owner PID=%d mismatch callers PID=%d\n",
                                      (int)pPool->poolId, NCP_TASK_V3_MUTEX_HDL_PID(&(pPool->poolLock)), pid
                    );
                NCP_RETURN(NCP_ST_TASK_BAD_POOL_OWNER_PROCESS);
            }
            else
            {
                /* ncp_task_v3_destroy_lock checks validity of passed lock */
                NCP_CALL(ncp_task_v3_destroy_lock(&(pPool->poolLock)));
                NCP_CALL(ncp_task_v3_create_lock(&(pPool->poolLock), mtxAttr));
            }
        }
    }

NCP_RETURN_LABEL
    return(ncpStatus);
}

/* NOTE - Will zero callers copy if use count goes to zero */
ncp_st_t
ncp_task_delete_thread(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
                       ncp_task_resource_name_t *threadName)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_process_info_t *pProcess = NULL;
    ncp_task_process_info_t *pPrevProcess = NULL;    
    ncp_task_thread_info_t *pThread;
    ncp_task_thread_info_t *pPrevThread=NULL;
    runtime_mutex_attr_state_t *mtxAttr = NULL;
    ncp_int32_t tqsId;

#if 0
    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                          ncp_xlf_task_delete_thread_entry, NCP_MSG_INFO,
                          "Enter delete thread -  pid %d for processName %s threadName %s\r\n",
                          pvtTqsHdl->pProcess->pid,
                          &pNcpTaskSwState->pidArray[pvtTqsHdl->pProcess->pid]->clientProcess.name[0],
                          &threadName->name[0]);
#endif

    /* first delete threadName from active threads list  */
    
    pThread =  pvtTqsHdl->pProcess->activeThreads;
    while (NULL != pThread)
    {
        if (&pvtTqsHdl->thisThread == pThread)
        {
            /* found it */
            if (NULL == pPrevThread)
            { 
                pvtTqsHdl->pProcess->activeThreads = pThread->pNextThread;      
            }
            else
            {
                pPrevThread->pNextThread = pThread->pNextThread;              
            }  
            pvtTqsHdl->pProcess->numThreads--;
            break;
        } 
        pPrevThread = pThread;
        pThread = pThread->pNextThread;       
    }        
    
    if (NULL == pThread)
    {
        NCP_CALL(NCP_ST_INTERNAL_ERROR);
    }
            
    /* Now delete process if use count falls to zero */
        
    if (0 == pvtTqsHdl->pProcess->numThreads)
    {
#if 0
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_delete_thread_removingPIDForProcessName,
                              NCP_MSG_INFO,
                              "Removing pid %d for processName %s @ %p\r\n",
                              pvtTqsHdl->pProcess->pid,
                              &pNcpTaskSwState->pidArray[pvtTqsHdl->pProcess->pid]->clientProcess.name[0],
                              pNcpTaskSwState->pidArray[pvtTqsHdl->pProcess->pid]);
#endif

        /*
         * Remove process struct from active processes list
         */    
        pProcess =  pNcpTaskSwState->activeProcesses;
        while (NULL != pProcess)
        {
            if (pProcess == pvtTqsHdl->pProcess)
            {
                /* found it */
                if (NULL == pPrevProcess)
                { 
                    pNcpTaskSwState->activeProcesses = pvtTqsHdl->pProcess->pNextProcess;      
                }
                else
                {
                    pPrevProcess->pNextProcess = pvtTqsHdl->pProcess->pNextProcess;         
                }  
                break;  
            } 
            pPrevProcess = pProcess;
            pProcess = pProcess->pNextProcess;       
        }
       
        if (NULL == pProcess)
        {
            NCP_CALL(NCP_ST_INTERNAL_ERROR);
        }

        /* TQS lock update */
        if (pvtTqsHdl->pTqs)
        {
            tqsId = pvtTqsHdl->pTqs->tqsId;
            mtxAttr = &pvtTqsHdl->pTqs->mtxAttr;
            /* When deleting process which exclusively owns TQS update all
               related locks */
            if (NCP_MUTEX_PROCESS_PRIVATE == mtxAttr->attr)
            {
                mtxAttr->attr = NCP_MUTEX_PROCESS_SHARED_ROBUST;
                mtxAttr->pid = 0;
                NCP_CALL(ncp_task_tqs_destroy_locks(tqsId));
                NCP_CALL(ncp_task_tqs_create_locks(tqsId, mtxAttr));
            }
        }
        else
        {
            NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                  ncp_xlf_task_delete_thread_missingTqs, NCP_MSG_ERROR,
                                  "TqsHdl contains invalid Tqs pointer pvtTqsHdl=%p\n",
                                  pvtTqsHdl);
        }
        /* Pool lock update */
        if (NCP_NCAV3_FIRST_CPU_POOL_ID <= pvtTqsHdl->cpuPoolId &&
            NCP_NCAV3_LAST_CPU_POOL_ID > pvtTqsHdl->cpuPoolId)
        {
            ncp_task_pool_t *pPool;
            ncp_pid_t pid = pvtTqsHdl->pProcess->osPid;
            /* if pool mutex is configuration differ from default then update it
               to default */
            pPool = pvtTqsHdl->cpuPoolHdl;
            if (pPool)
            {
                /* Deleting last thread and process for lock which is set
                   private. Update Lock to default so it can be reused by other
                   process. */
                if (NCP_MUTEX_PROCESS_PRIVATE == pPool->mtxAttr.attr)
                {
                    NCP_CALL(ncp_task_pool_mutex_reset_default(pPool, pid));
                }
            }
            else
            {
                NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                      ncp_xlf_task_delete_thread_null_cpuPoolHdl,
                                      NCP_MSG_ERROR,
                                      "poolLock reset pid=%d osPid=%d poolId=%d\r\n",
                                      pvtTqsHdl->pProcess->pid,
                                      pvtTqsHdl->pProcess->osPid,
                                      pvtTqsHdl->cpuPoolId);
            }
        }

        free(pNcpTaskSwState->pidArray[pvtTqsHdl->pProcess->pid]);   /* free process struct */
		pNcpTaskSwState->pidArray[pvtTqsHdl->pProcess->pid] = 0;
        pNcpTaskSwState->numActivePids--;
    }


NCP_RETURN_LABEL
    return(ncpStatus);
}  
 
ncp_st_t
ncp_task_internal_tqs_unbind(
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
    ncp_bool_t inRecovery,
    ncp_bool_t deleteThread)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_pvt_tqsHdl_data_t *prev;
    ncp_task_pvt_tqsHdl_data_t *curr;

    /*
     * Non-recovery path:
     * Do not allow thread to unbind if it still owes task completions
     * This indicates an application bug,   and if we are using a CPU pool,
     * then it is also likely that the application has not properly
     * refilled the NCA RX buffers.
     */

    if (pvtTqsHdl->completionsOwed !=
        (pvtTqsHdl->completionsIssued[NCP_TASK_TXQ_0] + pvtTqsHdl->completionsIssued[NCP_TASK_TXQ_1]))
    {
        if (!inRecovery)
        {
            NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                  ncp_xlf_task_internal_tqs_unbind_taskCompletionsOwed,
                                  NCP_MSG_ERROR,
                                  "Attempt to unbind with 0x%"PRIx64" task completions owed, 0x%"PRIx64" issued on TXQ0, 0x%"PRIx64" issued on TXQ1\r\n",
                                  pvtTqsHdl->completionsOwed,
                                  pvtTqsHdl->completionsIssued[NCP_TASK_TXQ_0],
                                  pvtTqsHdl->completionsIssued[NCP_TASK_TXQ_1]);
            NCP_CALL(NCP_ST_TASK_EXITING_WITH_COMPLETIONS_OWED);
        }
        else
        {
            ncp_uint32_t numCompleted=0;
            /*
             * Issue the owed completions.
             * No need to check usage flags if in recovery.
             */
            ncpStatus = ncp_task_bulk_complete(pvtTqsHdl,
                                                &pvtTqsHdl->pTqs->txQ0, /* p_oPCQ */
                                                pvtTqsHdl->completionsOwed,
                                                &numCompleted,
                                                TRUE);
        }
    }

    /*
     * For non-recovery path:
     *
     * (1) Do not allow last thread to unbind if process still owns buffers,  as this
     * would result in a memory leak.
     *
     * (2) Do not allow last thread to unbind if process still owes buffer refills to NCA,  as this
     * would result in a receive buffer leak and potential NCA receive buffer exhaustion.
     *
     * We can only perform these checks when the last thread of a given process
     * attempts to exit since TBR is implemented on a process basis.
     */

    /* If deleteThread is true, we didn't call ncp_task_add_thread() and so
     * pProcess is NULL. */
    if (deleteThread)
    {
        if (1 == pvtTqsHdl->pProcess->numThreads)
        {
            if (!inRecovery)
            {
                ncpStatus = NCP_TASK_TBR_LEAK_CHECK(pvtTqsHdl, pvtTqsHdl->pProcess->pid);
                if (NCP_ST_SUCCESS != ncpStatus)
                {
                    NCP_CALL(ncpStatus);
                }
            }
            else
            {
                ncpStatus = NCP_TASK_TBR_BUFFERS_RECOVER(pvtTqsHdl, pvtTqsHdl->pProcess->pid);
                if (NCP_ST_SUCCESS != ncpStatus)
                {
                    NCP_CALL(ncpStatus);
                }
            }
        }
    }

    if (pvtTqsHdl->cpuPoolHdl)
    {

        if (!inRecovery)
        {
            /*
             * This check can be enabled *only* for environments where refills are always performed by
             * the same thread that received the task.
             */
            NCP_CALL(NCP_TASK_TBR_THREAD_RX_REFILL_CHECK(pvtTqsHdl));
        }

        NCP_TASK_TBR_CPUPOOL_REFILL_COUNT_UPDATE(pvtTqsHdl);
    }

    /* RWXXX NCP_TASK_DECREMENT_POOL_USE_COUNTS(pvtTqsHdl); */

    /*
     * make sure state is appropriate and perform any cleanup
     * before freeing tqs handle
     */

    NCP_CALL(ncp_task_detach_tqs(pvtTqsHdl));

    if (deleteThread)
    {
        NCP_CALL(ncp_task_delete_thread(pvtTqsHdl, &pvtTqsHdl->thisThread.clientThread));
    }

    /* Remove from list of active tqs handles */

    prev = NULL;
    curr = pNcpTaskSwState->activeTqsHdls;
    while(curr)
    {
        if (curr == pvtTqsHdl)
        {
            if (NULL == prev)
            {
                pNcpTaskSwState->activeTqsHdls = curr->nextTqsHdl;
            }
            else
            {
                prev->nextTqsHdl = curr->nextTqsHdl;
            }
            break;
        }
        prev = curr;
        curr = curr->nextTqsHdl;
    }
    if (NULL == curr)
    {
        /* Note: sets EC and jumps up to return label to process stat update and error handling */
        NCP_CALL(NCP_ST_INTERNAL_ERROR);
    }

NCP_RETURN_LABEL

    return(ncpStatus);
}
 


ncp_st_t
ncp_task_buffer_overrun_check(ncp_uint8_t poolId, ncp_uintptr_t ptr, ncp_uint16_t sz)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_pool_t *pPool = &pNcpTaskSwState->taskPools[poolId];
    ncp_uintptr_t normalizedPtr;
    ncp_uintptr_t blockSz;
    
    if (NCP_TASK_FIXED_POOL_ENCODED_ID == poolId)
    {
        /* The fixed pool isn't divided into four sub-pools, but the NCA treats
            all fixed pool buffers as 64KB buffers. We must confirm that the
            buffer is in the fixed pool VA range, and doesn't cross a 64K
            boundary. */
        if (!((ptr >= pPool->poolVA) && (ptr < pPool->poolVAEnd)))
        {
            NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                  ncp_xlf_task_buffer_overrun_check_invalidBufferNotMemberOfFixedPool31,
                                  NCP_MSG_ERROR,
                                  "Invalid buffer %p is not a member of fixed pool 31\r\n",
                                  (void *)ptr);
            NCP_CALL(NCP_ST_TASK_INVALID_BUFFER);
        }

        blockSz = 64 * 1024;
    }
    else if ((ptr >= pPool->blocksVA[0]) && (ptr < pPool->blocksVAend[0]))
    {
        blockSz = 256;
    }        
    else if ((ptr >= pPool->blocksVA[1]) && (ptr < pPool->blocksVAend[1]))
    {
        blockSz = (2*1024);        
    }   
    else if ((ptr >= pPool->blocksVA[2]) && (ptr < pPool->blocksVAend[2]))
    {
        blockSz = (16*1024);         
    }   
    else if ((ptr >= pPool->blocksVA[3]) && (ptr < pPool->blocksVAend[3]))
    {
        blockSz = (64*1024);         
    } 
    else
    {
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_buffer_overrun_check_invalidBufferNotMemberOfPool,
                              NCP_MSG_ERROR,
                              "Invalid buffer %p is not a member of pool\r\n",
                              (void *)ptr);
        NCP_CALL(NCP_ST_TASK_INVALID_BUFFER);
    }
    
    normalizedPtr = ptr;
    normalizedPtr &= ~(blockSz - 1);
    if ((ptr + sz) > (normalizedPtr + blockSz))
    {
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_buffer_overrun_check_bufferOverrunDetected,
                              NCP_MSG_ERROR,
                              "Buffer overrun detected!  Pool %d corruption is likely. Buffer is @ %p, normalized ptr is %p,  blockSize=%p, user supplied segSize=%d\r\n",
                              (int)   poolId,
                              (void *)ptr,
                              (void *)normalizedPtr,
                              (void *)blockSz,
                              sz);

        NCP_CALL(NCP_ST_TASK_BUFFER_OVERRUN);
    }

NCP_RETURN_LABEL
    if (NCP_ST_SUCCESS != ncpStatus)
    {
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_buffer_overrun_check_pool,
                              NCP_MSG_ERROR, "pool=%d\r\n", (int)pPool->poolId);
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_buffer_overrun_check_blocksVAStartEnd,
                              NCP_MSG_ERROR, "blocksVA[%d] start=%p, end=%p\r\n",
                              0, (void *)pPool->blocksVA[0], (void *)pPool->blocksVAend[0]);
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_buffer_overrun_check_blocksVAStartEnd,
                              NCP_MSG_ERROR, "blocksVA[%d] start=%p, end=%p\r\n",
                              1, (void *)pPool->blocksVA[1], (void *)pPool->blocksVAend[1]);
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_buffer_overrun_check_blocksVAStartEnd,
                              NCP_MSG_ERROR, "blocksVA[%d] start=%p, end=%p\r\n",
                              2, (void *)pPool->blocksVA[2], (void *)pPool->blocksVAend[2]);
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_buffer_overrun_check_blocksVAStartEnd,
                              NCP_MSG_ERROR, "blocksVA[%d] start=%p, end=%p\r\n",
                              3, (void *)pPool->blocksVA[3], (void *)pPool->blocksVAend[3]);
    }
    return(ncpStatus);
}        

ncp_st_t
ncp_task_validate_output_task(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl, 
                           ncp_task_header_t *thisHeader)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_pool_t *pCpuPool = pvtTqsHdl->cpuPoolHdl;
    ncp_uint32_t poolId;
    ncp_uint32_t validPoolsMask = pvtTqsHdl->pTqs->validPoolsMask;
    ncp_uint16_t pduSize=0;
    
    switch(thisHeader->ptrCnt)
    {
        case 6:
            poolId = thisHeader->pool5;
            if (0 == (validPoolsMask & (1<<poolId)))
            {
                NCP_CALL(NCP_ST_TASK_TQS_INVALID_POOL);             
            }        
            if (0 == poolId) 
            {   if (NULL == pCpuPool)
                {
                    NCP_CALL(NCP_ST_TASK_TQS_INVALID_POOL);
                }
                if (TRUE == pCpuPool->disabledForReinit)
                {
                    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                          ncp_xlf_task_validate_output_task_disabledForReinit,
                                          NCP_MSG_ERROR,
                                          "It is invalid to operate on a task handle while its"
                                          " pool is being reinitialized.\n");
                    NCP_CALL(NCP_ST_TASK_POOL_IS_BEING_REINITIALIZED);
                }
                poolId = pvtTqsHdl->cpuPoolId;
            }
            NCP_ASSERT(thisHeader->pduSegSize5 != 0, NCP_ST_TASK_INVALID_PDU_SIZE);
            NCP_TASK_BUFFER_OVERRUN_CHECK(poolId, thisHeader->pduSegAddr5, thisHeader->pduSegSize5);
            /* Only 63KB can be used in 64K blocks */
            NCP_ASSERT(thisHeader->pduSegSize5 <= 64512, NCP_ST_TASK_INVALID_PDU_SIZE);
            pduSize +=  thisHeader->pduSegSize5;  
        case 5:
            poolId = thisHeader->pool4;
            if (0 == (validPoolsMask & (1<<poolId)))
            {
                NCP_CALL(NCP_ST_TASK_TQS_INVALID_POOL);             
            }        
            if (0 == poolId) 
            {   if (NULL == pCpuPool)
                {
                    NCP_CALL(NCP_ST_TASK_TQS_INVALID_POOL);
                }
                if (TRUE == pCpuPool->disabledForReinit)
                {
                    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                          ncp_xlf_task_validate_output_task_disabledForReinit,
                                          NCP_MSG_ERROR,
                                          "It is invalid to operate on a task handle while its"
                                          " pool is being reinitialized.\n");
                    NCP_CALL(NCP_ST_TASK_POOL_IS_BEING_REINITIALIZED);
                }
                poolId = pvtTqsHdl->cpuPoolId;                
            }
            NCP_ASSERT(thisHeader->pduSegSize4 != 0, NCP_ST_TASK_INVALID_PDU_SIZE);
            NCP_TASK_BUFFER_OVERRUN_CHECK(poolId, thisHeader->pduSegAddr4, thisHeader->pduSegSize4);             
            /* Only 63KB can be used in 64K blocks */
            NCP_ASSERT(thisHeader->pduSegSize4 <= 64512, NCP_ST_TASK_INVALID_PDU_SIZE);
            pduSize +=  thisHeader->pduSegSize4;                         
        case 4:
            poolId = thisHeader->pool3;
            if (0 == (validPoolsMask & (1<<poolId)))
            {
                NCP_CALL(NCP_ST_TASK_TQS_INVALID_POOL);             
            }        
            if (0 == poolId) 
            {   if (NULL == pCpuPool)
                {
                    NCP_CALL(NCP_ST_TASK_TQS_INVALID_POOL);
                }
                if (TRUE == pCpuPool->disabledForReinit)
                {
                    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                          ncp_xlf_task_validate_output_task_disabledForReinit,
                                          NCP_MSG_ERROR,
                                          "It is invalid to operate on a task handle while its"
                                          " pool is being reinitialized.\n");
                    NCP_CALL(NCP_ST_TASK_POOL_IS_BEING_REINITIALIZED);
                }
                poolId = pvtTqsHdl->cpuPoolId;                
            }
            NCP_ASSERT(thisHeader->pduSegSize3 != 0, NCP_ST_TASK_INVALID_PDU_SIZE);
            NCP_TASK_BUFFER_OVERRUN_CHECK(poolId, thisHeader->pduSegAddr3, thisHeader->pduSegSize3);            
            /* Only 63KB can be used in 64K blocks */
            NCP_ASSERT(thisHeader->pduSegSize3 <= 64512, NCP_ST_TASK_INVALID_PDU_SIZE);
            pduSize +=  thisHeader->pduSegSize3;                         
        case 3:
            poolId = thisHeader->pool2;
            if (0 == (validPoolsMask & (1<<poolId)))
            {
                NCP_CALL(NCP_ST_TASK_TQS_INVALID_POOL);             
            }        
            if (0 == poolId) 
            {   if (NULL == pCpuPool)
                {
                    NCP_CALL(NCP_ST_TASK_TQS_INVALID_POOL);
                }
                if (TRUE == pCpuPool->disabledForReinit)
                {
                    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                          ncp_xlf_task_validate_output_task_disabledForReinit,
                                          NCP_MSG_ERROR,
                                          "It is invalid to operate on a task handle while its"
                                          " pool is being reinitialized.\n");
                    NCP_CALL(NCP_ST_TASK_POOL_IS_BEING_REINITIALIZED);
                }
                poolId = pvtTqsHdl->cpuPoolId;                
            } 
            NCP_ASSERT(thisHeader->pduSegSize2 != 0, NCP_ST_TASK_INVALID_PDU_SIZE);
            NCP_TASK_BUFFER_OVERRUN_CHECK(poolId, thisHeader->pduSegAddr2, thisHeader->pduSegSize2);            
            /* Only 63KB can be used in 64K blocks */
            NCP_ASSERT(thisHeader->pduSegSize2 <= 64512, NCP_ST_TASK_INVALID_PDU_SIZE);
            pduSize +=  thisHeader->pduSegSize2;                       
        case 2:
            poolId = thisHeader->pool1;
            if (0 == (validPoolsMask & (1<<poolId)))
            {
                NCP_CALL(NCP_ST_TASK_TQS_INVALID_POOL);             
            }        
            if (0 == poolId) 
            {   if (NULL == pCpuPool)
                {
                    NCP_CALL(NCP_ST_TASK_TQS_INVALID_POOL);
                }
                if (TRUE == pCpuPool->disabledForReinit)
                {
                    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                          ncp_xlf_task_validate_output_task_disabledForReinit,
                                          NCP_MSG_ERROR,
                                          "It is invalid to operate on a task handle while its"
                                          " pool is being reinitialized.\n");
                    NCP_CALL(NCP_ST_TASK_POOL_IS_BEING_REINITIALIZED);
                }
                poolId = pvtTqsHdl->cpuPoolId;                
            }
            NCP_ASSERT(thisHeader->pduSegSize1 != 0, NCP_ST_TASK_INVALID_PDU_SIZE);
            NCP_TASK_BUFFER_OVERRUN_CHECK(poolId, thisHeader->pduSegAddr1, thisHeader->pduSegSize1);            
            /* Only 63KB can be used in 64K blocks */
            NCP_ASSERT(thisHeader->pduSegSize1 <= 64512, NCP_ST_TASK_INVALID_PDU_SIZE);
            pduSize +=  thisHeader->pduSegSize1;                       
        case 1: 
            poolId = thisHeader->pool0;
            if (0 == (validPoolsMask & (1<<poolId)))
            {
                NCP_CALL(NCP_ST_TASK_TQS_INVALID_POOL);             
            }        
            if (0 == poolId) 
            {   if (NULL == pCpuPool)
                {
                    NCP_CALL(NCP_ST_TASK_TQS_INVALID_POOL);
                }
                if (TRUE == pCpuPool->disabledForReinit)
                {
                    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                          ncp_xlf_task_validate_output_task_disabledForReinit,
                                          NCP_MSG_ERROR,
                                          "It is invalid to operate on a task handle while its"
                                          " pool is being reinitialized.\n");
                    NCP_CALL(NCP_ST_TASK_POOL_IS_BEING_REINITIALIZED);
                }
                poolId = pvtTqsHdl->cpuPoolId;                
            }
            else if (NCP_TASK_FIXED_POOL_ENCODED_ID == poolId)
            {
                if (TRUE == thisHeader->combinedHeader)
                {
                    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                          ncp_xlf_task_validate_output_task_combinedHeaderNotAllowed,
                                          NCP_MSG_ERROR,
                                          "Combined header not allowed if pduSegAdd0 is in fixed pool\r\n");
                    NCP_CALL(NCP_ST_TASK_FIXED_POOL_TASK_HEADER_VIOLATION);
                }
            }
            NCP_ASSERT(thisHeader->pduSegSize0 != 0, NCP_ST_TASK_INVALID_PDU_SIZE);
            /* Only 63KB can be used in 64K blocks */
            NCP_ASSERT(thisHeader->pduSegSize0 <= 64512, NCP_ST_TASK_INVALID_PDU_SIZE);
            NCP_TASK_BUFFER_OVERRUN_CHECK(poolId, thisHeader->pduSegAddr0, thisHeader->pduSegSize0);   
            if (TRUE == thisHeader->combinedHeader)
            {       
                NCP_TASK_BUFFER_OVERRUN_CHECK(poolId, thisHeader, ((thisHeader->ptrCnt <= 2) ? 64 : 128)); 
                if (thisHeader->ptrCnt != 0)
                {        
                    ncp_uintptr_t tmpPtr;
                    ncp_uint32_t  tmpSz;
                
                    tmpPtr = (ncp_uintptr_t)thisHeader;
                    if (FALSE == thisHeader->debugValid)
                    {                        
                        if (thisHeader->ptrCnt <= 2)
                        {
                            tmpSz = 64;
                        }        
                        else  
                        {
                            tmpSz = 112 - 8;
                        }
                    }    
                    else
                    {
                        tmpSz = 112;
                    }                
                    if (tmpPtr + tmpSz > (ncp_uintptr_t)(thisHeader->pduSegAddr0))
                    {
                        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                              ncp_xlf_task_validate_output_task_taskHeaderOverlapsPduSegAddr0Data,
                                              NCP_MSG_ERROR,
                                              "Task header @ %p, overlaps pduSegAddr0 data @%p\r\n",
                                              thisHeader,
                                              (void *)(ncp_uintptr_t)(thisHeader->pduSegAddr0));
                        NCP_CALL(NCP_ST_TASK_HEADER_OVERLAPS_DATA);        
                    
                    }   
                }           
            }                  
            pduSize +=  thisHeader->pduSegSize0;                   
        case 0:
            poolId = thisHeader->headerPool;
            if (0 == (validPoolsMask & (1<<poolId)))
            {
                NCP_CALL(NCP_ST_TASK_TQS_INVALID_POOL);             
            }        
            if (0 == poolId) 
            {   if (NULL == pCpuPool)
                {
                    NCP_CALL(NCP_ST_TASK_TQS_INVALID_POOL);
                }
                if (TRUE == pCpuPool->disabledForReinit)
                {
                    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                          ncp_xlf_task_validate_output_task_disabledForReinit,
                                          NCP_MSG_ERROR,
                                          "It is invalid to operate on a task handle while its"
                                          " pool is being reinitialized.\n");
                    NCP_CALL(NCP_ST_TASK_POOL_IS_BEING_REINITIALIZED);
                }
                poolId = pvtTqsHdl->cpuPoolId;                
            }
            else if (NCP_TASK_FIXED_POOL_ENCODED_ID == poolId)
            {
                NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                      ncp_xlf_task_validate_output_task_errorTaskHeaderMemberOfFixedPool,
                                      NCP_MSG_ERROR,
                                      "Task header cannot be a member of the fixed pool (31)\r\n");
                NCP_CALL(NCP_ST_TASK_FIXED_POOL_TASK_HEADER_VIOLATION);
            }                              
            if (FALSE == thisHeader->combinedHeader)
            {
                ncp_uint32_t  tmpSz;                
                if (FALSE == thisHeader->debugValid)
                {                        
                    if (thisHeader->ptrCnt <= 2)
                    {
                        tmpSz = 64;
                    }        
                    else  
                    {
                        tmpSz = 112 - 8;
                    }
                }    
                else
                {
                    tmpSz = 112;
                }                  
                NCP_TASK_BUFFER_OVERRUN_CHECK(poolId, thisHeader, tmpSz);                 
            }        
            break;
        default:
            NCP_CALL(NCP_ST_TASK_BAD_PTR_CNT);
    }   /* switch */     

    if (pduSize != thisHeader->pduSize)
    {
        NCP_CALL(NCP_ST_TASK_INVALID_PDU_SIZE);    
    }    
    
NCP_RETURN_LABEL
    return(ncpStatus);    
}                               
                           
        
/* NCP_INLINE */ 
ncp_st_t
ncp_task_bulk_complete(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
                    ncp_task_pcq_t             *p_oPCQ,
                    ncp_uint32_t               numTasks,
                    ncp_uint32_t               *pNumTasksCompleted,
                    ncp_bool_t                 wait)     
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;   
    opcq_entry_overlay_t *pEntry;  
    ncp_bool_t barrierIssued = FALSE;    
    ncp_uint32_t skipBarrierCnt = p_oPCQ->nEntriesDiv2;   
    int numRemaining = numTasks;
    int currLoopCount;
    ncp_bool_t needPollStateReset = TRUE;
    

    if (p_oPCQ->u.opcq_info.sendDoneCnt)
    {
        NCP_TASK_UPDATE_NUM_TX_ENTRIES_AVAIL(pvtTqsHdl, p_oPCQ);
    }
    
    /* Set up what will be the contents of the oPCQ entry - exactly the same for each */
    
    pEntry = (opcq_entry_overlay_t *)p_oPCQ->u.opcq_info.pOPCQentry;    
    pEntry->u.opcqEntry.taskAddress = (ncp_uint64_t) 0LL;    
    pEntry->u.opcqDword[1] = pvtTqsHdl->taskCompleteDefaultCmdBits.u.opcqDword[1];
        
    while(numRemaining)
    {
        do
        {
            if ((numRemaining) <= p_oPCQ->u.opcq_info.numTxAvail)
            {
                currLoopCount = numRemaining; 
                break;
            }        
            /* update num entries available */
            NCP_TASK_UPDATE_NUM_TX_ENTRIES_AVAIL(pvtTqsHdl, p_oPCQ);
            if (0 == p_oPCQ->u.opcq_info.numTxAvail) 
            {
                if (wait)
                {   
                    ncp_st_t tmpStatus;                      

                    if (needPollStateReset)
                    {
                        needPollStateReset = FALSE;
                        NCP_TASK_RESET_POLL_STATE(&pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ0 + p_oPCQ->u.opcq_info.relId]);   
                    }
                    if (NCP_ST_SUCCESS != (tmpStatus = NCP_TASK_DO_WAIT(
                            pvtTqsHdl,
                            (&pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ0 + p_oPCQ->u.opcq_info.relId]),
                            myDevHdl,
                            pvtTqsHdl->tqsId)))
                    {
                        ncpStatus = tmpStatus;
                        NCP_JUMP_RETURN();
                    }            
                }
                else
                {
                    ncpStatus = NCP_ST_TASK_SEND_QUEUE_FULL;
                    NCP_JUMP_RETURN();
                }  
            } 
            else
            {
                if ((numRemaining) <= p_oPCQ->u.opcq_info.numTxAvail)
                {
                    currLoopCount = numRemaining; 
                }                      
                else
                {    
                    currLoopCount = p_oPCQ->u.opcq_info.numTxAvail;                          
                }                             
                break;
            }    
        } while(1);   

        /* OK to adjust all counts prematurely,  we know we have enough empty entries */
        p_oPCQ->u.opcq_info.numTxAvail -= currLoopCount;                
        numRemaining -= currLoopCount;
        
        while(currLoopCount--)
        {
            

            NCP_TASK_FILL_PER_OPCQ_AUX_DATA(NULL, 
                                            p_oPCQ);                
                
            NCP_TASK_OPCQ_UPDATE_CACHED_PIDX(p_oPCQ);

            if (0 == skipBarrierCnt--)
            {    
                NCP_TASK_OPCQ_ISSUE_BARRIER_AND_WRITE_PIDX(p_oPCQ);
                skipBarrierCnt = p_oPCQ->nEntriesDiv2;
                barrierIssued = TRUE;
            }
            else
            {
                barrierIssued = FALSE;            
            }            
        } /* for */
    } /* while numRemaining */    

NCP_RETURN_LABEL

    if ((barrierIssued == FALSE) && (0 != (numTasks - numRemaining)))
    {
        NCP_TASK_OPCQ_ISSUE_BARRIER_AND_WRITE_PIDX(p_oPCQ);        
    }

    *pNumTasksCompleted  += (numTasks - numRemaining);    
    
                
    return(ncpStatus);        
}             
    
/* NCP_INLINE */ 
ncp_st_t 
ncp_task_bulk_cpu_pool_buffer_free( 
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
    ncp_uint32_t numBuffers, 
    ncp_uint32_t *pNumFreed, 
    void        **pBuffers)   
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    int numFreed=0;
    ncp_task_pool_t *pPool;
    NCP_MUTEX_LOCKED_FLAG_DECL(unlockRequired);    
    NCP_TASK_LOCK_FLAGS(flags);
        
    if (NULL == (pPool = pvtTqsHdl->cpuPoolHdl))
    {
        NCP_CALL(NCP_ST_TASK_TQS_INVALID_POOL);    
    }    
    if (TRUE == pPool->disabledForReinit)
    {
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_bulk_cpu_buffer_free_disabledForReinit,
                              NCP_MSG_ERROR,
                              "It is invalid to operate on a task handle while its"
                              " pool is being reinitialized.\n");
        NCP_CALL(NCP_ST_TASK_POOL_IS_BEING_REINITIALIZED);
    }

    NCP_CALL(NCP_TASK_CLAIM_LOCK_HDL(&pPool->poolLock, flags, &unlockRequired));
        
    while (numBuffers--)
    {
        if (NCP_ST_SUCCESS != (ncpStatus = ncp_task_CpuPool_free_noLock(
                                                      pvtTqsHdl,
                                                      pPool, 
                                                      *(pBuffers + numFreed)))) 
        {
            break;
        }                                 
        numFreed++;                             
    }
    
NCP_RETURN_LABEL
   
    NCP_CLEANUP_MUTEX_CALL(NCP_TASK_FREE_LOCK_HDL(&pPool->poolLock, flags, &unlockRequired));
           
    *pNumFreed = numFreed;

    return(ncpStatus);
} 
    
ncp_st_t ncp_task_bulk_buffer_free( 
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
    ncp_task_pcq_t *p_oPCQ,
    ncp_uint8_t bufferPoolId,
    ncp_uint32_t numBuffers, 
    ncp_uint32_t *pNumFreed, 
    void        **pBuffers, 
    ncp_bool_t  *pMrefBitSet,
    ncp_bool_t wait) 
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    /* ncp_task_tqs_swState_t *pTqs = pvtTqsHdl->pTqs; */
    ncp_uint32_t numFreed=0;
    ncp_bool_t barrierIssued = FALSE;
    ncp_uint32_t skipBarrierCnt = p_oPCQ->nEntriesDiv2;     
    opcq_entry_overlay_t *pEntry;
    ncp_uint64_t DefaultCmdBits;
    int numRemaining = numBuffers;
    int currLoopCount;
    ncp_bool_t needPollStateReset = TRUE;
    ncp_bool_t refill;
    NCP_TASK_TBR_STATE_PTRS_DECL()

    DefaultCmdBits = pvtTqsHdl->taskBufferFreeDefaultCmdBits.u.opcqDword[1];
    
    if (NULL == pvtTqsHdl->cpuPoolHdl)
    {
        refill = FALSE;
    }   
    else        
    {    
        refill = TRUE;
    }
    
    if (p_oPCQ->u.opcq_info.sendDoneCnt)
    {
        NCP_TASK_UPDATE_NUM_TX_ENTRIES_AVAIL(pvtTqsHdl, p_oPCQ);
    }       
    while(numRemaining)
    {
        do
        {
            if ((numRemaining) <= p_oPCQ->u.opcq_info.numTxAvail)
            {
                currLoopCount = numRemaining; 
                break;
            }        
            /* update num entries available */
            NCP_TASK_UPDATE_NUM_TX_ENTRIES_AVAIL(pvtTqsHdl, p_oPCQ);
            if (0 == p_oPCQ->u.opcq_info.numTxAvail) 
            {
                if (wait)
                {  
                    ncp_st_t tmpStatus; 
                    ncp_task_api_class_t apiClass;
                        
                    /* perf opt: waiting is unlikely,  so moved apiClass init out of data path */                        
                    if (NULL == pvtTqsHdl->cpuPoolHdl)
                    {
                        apiClass = NCP_TASK_API_CLASS_FREE_TXQ0 + p_oPCQ->u.opcq_info.relId;        
                    }      
                    else
                    {    
                        apiClass = NCP_TASK_API_CLASS_REFILL_TXQ0 + p_oPCQ->u.opcq_info.relId;
                    }
                                       
                    if (needPollStateReset)
                    {
                        needPollStateReset = FALSE;
                        NCP_TASK_RESET_POLL_STATE(&pvtTqsHdl->waitProfile[apiClass]);
                    }
                    if (NCP_ST_SUCCESS != (tmpStatus = NCP_TASK_DO_WAIT(
                            pvtTqsHdl,
                            (&pvtTqsHdl->waitProfile[apiClass]),
                            myDevHdl,
                            pvtTqsHdl->tqsId)))
                    {
                        ncpStatus = tmpStatus;
                        NCP_JUMP_RETURN();
                    }            
                }
                else
                {
                    ncpStatus = NCP_ST_TASK_SEND_QUEUE_FULL;
                    NCP_JUMP_RETURN();
                }  
            } 
            else
            {
                if ((numRemaining) <= p_oPCQ->u.opcq_info.numTxAvail)
                {
                    currLoopCount = numRemaining; 
                }                      
                else
                {    
                    currLoopCount = p_oPCQ->u.opcq_info.numTxAvail;                          
                }                          
                break;
            }    
        } while(1);

        /* it is *not* ok to preadjust TxAvail count here,  since errors are possible within the loop */
        numRemaining -= currLoopCount;
                        
        while(currLoopCount--)
        {                      
            void *thisBuffer = *(pBuffers + numFreed);
    
                        
            /* 
             * Set task address and default opcq entry fields 
             */

            pEntry = (opcq_entry_overlay_t *)p_oPCQ->u.opcq_info.pOPCQentry;
            pEntry->u.opcqEntry.taskAddress = (ncp_uint64_t ) thisBuffer;
            
            pEntry->u.opcqDword[1] = DefaultCmdBits;

            /*
             * Set up what will be the variable contents of the oPCQ entry
             */
            
    

        
            if (!refill)
            {    

                NCP_TASK_TBR_STATE_PTRS_INIT();
                NCP_TASK_TBR_INIT_BUFFER_STATES(pTbr, pvtTqsHdl->pProcess->pid, NCP_TASK_TBR_STATE_FREE);
                NCP_TASK_TBR_BUFFER_STATE_PREFETCH(pvtTqsHdl,
                                                   thisBuffer,
                                                   bufferPoolId,
                                                 *(pMrefBitSet + numFreed),
                                                   pTbr);
                                                   
                /* pMrefBitSet need not be set if using a CPU pool */    
                if (0 != (pEntry->u.opcqEntry.headerPool = bufferPoolId))
                {
                    pEntry->u.opcqEntry.headerPoolMref = (*(pMrefBitSet + numFreed));
                } 
       
            }
            else
            {
                
                NCP_TASK_TBR_STATE_PTRS_INIT();                
                NCP_TASK_TBR_INIT_BUFFER_STATES(
                        pTbr,
                        pvtTqsHdl->pProcess->pid,
                        NCP_TASK_TBR_STATE_NCA_OWNED);
                NCP_TASK_TBR_BUFFER_STATE_PREFETCH(
                        pvtTqsHdl,
                        thisBuffer,
                        pvtTqsHdl->cpuPoolId,
                        0,
                        pTbr);
            }        

            NCP_TASK_TBR_BUFFER_STATE_UPDATE_MREF(pTbr); /* must be done before pgit update */
                
            NCP_TASK_FILL_PER_OPCQ_AUX_DATA(NULL, 
                                            p_oPCQ);                

            NCP_TASK_OPCQ_UPDATE_CACHED_PIDX(p_oPCQ);

            p_oPCQ->u.opcq_info.numTxAvail--;  
            numFreed++;
            
            if (0 == skipBarrierCnt--)
            {    
                NCP_TASK_OPCQ_ISSUE_BARRIER_AND_WRITE_PIDX(p_oPCQ);
                skipBarrierCnt = p_oPCQ->nEntriesDiv2;                
                barrierIssued = TRUE;
            }
            else
            {
                barrierIssued = FALSE;  
            }  
                 
        } /* currLoopCount */
    } /* while numRemaining */    

NCP_RETURN_LABEL

    if ((barrierIssued == FALSE) && (0 != numFreed))
    {
        NCP_TASK_OPCQ_ISSUE_BARRIER_AND_WRITE_PIDX(p_oPCQ);
    }
    
    *pNumFreed = numFreed;
    
    return(ncpStatus);
}

ncp_st_t
ncp_task_v3_create_lock(ncp_task_v3_mutex_hdl_t *pLock, runtime_mutex_attr_state_t *pAttr)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_pid_t myPid = ncp_get_pid();
    ncp_bool_t shared = TRUE;
    ncp_pid_t pid = 0;
    ncp_mutex_attr_t attr = NCP_MUTEX_PROCESS_SHARED_ROBUST;

    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                          ncp_task_v3_create_lock,
                          NCP_MSG_DEBUG,
                          "TaskV3CreateLock pLock=%p pAttr=%p pid=%d\r\n",
                          pLock, pAttr, ncp_get_pid());

    if (NULL == pLock)
    {
        NCP_RETURN(NCP_ST_INVALID_PARAMETER);
    }

    if (NULL != pAttr)
    {
        pid = pAttr->pid;
        attr = pAttr->attr;
    }

    switch (attr)
    {
    case NCP_MUTEX_PROCESS_PRIVATE:
        if (0 == pid || pid != myPid)
        {
            NCP_RETURN(NCP_ST_TASK_INVALID_PID);
        }
        pLock->lock = ncp_calloc(sizeof(*(pLock->lock)), 1);
        if (!pLock->lock)
        {
            NCP_RETURN(NCP_ST_DEV_NO_MEMORY);
        }
        pLock->pid = myPid;
        pLock->flags = NCP_MUTEX_PROCESS_PRIVATE;
        shared = FALSE;
        break;
    case NCP_MUTEX_PROCESS_SHARED:
        if (0 != pid)
        {
            NCP_RETURN(NCP_ST_TASK_INVALID_PID);
        }
        pLock->lock = ncp_nvm_calloc(sizeof(*(pLock->lock)), 1);
        if (!pLock->lock)
        {
            NCP_RETURN(NCP_ST_DEV_NO_MEMORY);
        }
        pLock->pid = 0;
        pLock->flags = NCP_MUTEX_PROCESS_SHARED;
        shared = TRUE;
        break;
    case NCP_MUTEX_PROCESS_SHARED_ROBUST:
        if (0 != pid)
        {
            NCP_RETURN(NCP_ST_TASK_INVALID_PID);
        }
        NCP_CALL(ncp_nvm_robust_malloc(sizeof(*(pLock->lock)),
                                       (void **)&pLock->lock,  /* already a pointer to a pointer */
                                       NCP_DO_MEMSET));
        pLock->pid = 0;
        pLock->flags = NCP_MUTEX_PROCESS_SHARED_ROBUST;
        shared = TRUE;
        break;
    default:
        NCP_RETURN(NCP_ST_MUTEX_WRONG_STATE);
    }
    NCP_CALL(NCP_TASK_INIT_LOCK_HDL(pLock, shared));
NCP_RETURN_LABEL
    return(ncpStatus);
}

ncp_st_t
ncp_task_tqs_create_locks(int tqsId, runtime_mutex_attr_state_t *mtxAttr)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_tqs_swState_t *pTqs = &pNcpTaskSwState->tqsSwState[tqsId];
    int poolId;

    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                          ncp_task_v3_create_locks,
                          NCP_MSG_DEBUG,
                          "TaskV3CreateLocks tqsId=%d mtxAttr=%p pid=%d\r\n",
                          tqsId, mtxAttr, ncp_get_pid());

    if (pTqs->shareCtl.shareFlags.sharedRxQueue)
    {
        pTqs->rxQ.shared = TRUE;
        NCP_CALL(ncp_task_v3_create_lock(&pTqs->rxQ.qLock, mtxAttr));
    }
    if (pTqs->shareCtl.shareFlags.sharedTxQueue0)
    {
        pTqs->txQ0.shared = TRUE;
        NCP_CALL(ncp_task_v3_create_lock(&pTqs->txQ0.qLock, mtxAttr));
    }
    if (pTqs->shareCtl.shareFlags.sharedTxQueue1)
    {
        pTqs->txQ1.shared = TRUE;
        NCP_CALL(ncp_task_v3_create_lock(&pTqs->txQ1.qLock, mtxAttr));
    }
    for (poolId  = NCP_NCAV3_FIRST_SHARED_POOL_ID;
         poolId <= NCP_NCAV3_LAST_SHARED_POOL_ID;
         poolId++)
    {
        ncp_task_mme_allocator_t *pAllocator = &pTqs->mmeAllocator[poolId];
        if (pTqs->shareCtl.shareFlags.sharedAllocator[poolId])
        {
            pAllocator->shared = TRUE;
            NCP_CALL(ncp_task_v3_create_lock(&pAllocator->mmeLock, mtxAttr));
        }
    }

NCP_RETURN_LABEL
    return(ncpStatus);
}

ncp_st_t
ncp_task_v3_destroy_lock(ncp_task_v3_mutex_hdl_t *pLock)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_pid_t myPid = ncp_get_pid();

    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                          ncp_task_v3_destroy_lock,
                          NCP_MSG_DEBUG,
                          "TaskV3DestroyLock pLock=%p pid=%d\r\n",
                          pLock, ncp_get_pid());

    if (!pLock)
    {
        NCP_RETURN(ncpStatus);
    }

    if (!pLock->lock)
    {
        NCP_RETURN(ncpStatus);
    }

    switch (pLock->flags)
    {
    case NCP_MUTEX_PROCESS_PRIVATE:
        if (pLock->pid != myPid)
        {
            NCP_RETURN(NCP_ST_TASK_INVALID_PID);
        }
        NCP_TASK_DESTROY_LOCK(pLock->lock);
        ncp_free(pLock->lock);
        break;
    case NCP_MUTEX_PROCESS_SHARED:
        if (0 != pLock->pid)
        {
            NCP_RETURN(NCP_ST_TASK_INVALID_PID);
        }
        NCP_TASK_DESTROY_LOCK(pLock->lock);
        ncp_nvm_free(pLock->lock);
        break;
    case NCP_MUTEX_PROCESS_SHARED_ROBUST:
        if (0 != pLock->pid)
        {
            NCP_RETURN(NCP_ST_TASK_INVALID_PID);
        }
        NCP_TASK_DESTROY_LOCK(pLock->lock);
        NCP_CALL(ncp_nvm_robust_free((void **)&(pLock->lock)));
        break;
    default:
        NCP_RETURN(NCP_ST_MUTEX_WRONG_STATE);
    }

    pLock->lock = NULL;
    pLock->pid = 0;
    pLock->flags = NCP_MUTEX_PROCESS_SHARED_ROBUST;

NCP_RETURN_LABEL
    return(ncpStatus);
}

ncp_st_t
ncp_task_tqs_destroy_locks(int tqsId)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_tqs_swState_t *tqs = &pNcpTaskSwState->tqsSwState[tqsId];
    runtime_mutex_attr_state_t *mtxAttr = &tqs->mtxAttr;
    int i;

    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                          ncp_task_v3_destroy_locks,
                          NCP_MSG_DEBUG,
                          "TaskV3DestroyLocks tqsId=%d pid=%d\r\n",
                          tqsId, ncp_get_pid());

    mtxAttr->pid = 0;
    mtxAttr->attr = NCP_MUTEX_PROCESS_SHARED_ROBUST;

    NCP_CALL(ncp_task_v3_destroy_lock(&(tqs->rxQ.qLock)));
    NCP_CALL(ncp_task_v3_destroy_lock(&(tqs->txQ0.qLock)));
    NCP_CALL(ncp_task_v3_destroy_lock(&(tqs->txQ1.qLock)));

    for (i = NCP_NCAV3_FIRST_SHARED_POOL_ID;
         i <= NCP_NCAV3_LAST_SHARED_POOL_ID;
         i++)
    {
        ncp_task_mme_allocator_t *pAllocator = &tqs->mmeAllocator[i];
        NCP_CALL(ncp_task_v3_destroy_lock(&pAllocator->mmeLock));
    }

NCP_RETURN_LABEL
    return(ncpStatus);
}

/*! Reset qLock and mmeLock PID and pointer. This auxiliary function shall be
 *  used only when clenaup is needed after process crash.
 */
ncp_st_t
ncp_task_tqs_cleanup_locks(int tqsId)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_tqs_swState_t *tqs = &pNcpTaskSwState->tqsSwState[tqsId];
    runtime_mutex_attr_state_t *mtxAttr = &tqs->mtxAttr;
    int i;

    mtxAttr->pid = 0;
    mtxAttr->attr = NCP_MUTEX_PROCESS_SHARED_ROBUST;

    NCP_TASK_V3_MUTEX_CLEAR(&tqs->rxQ.qLock);
    NCP_TASK_V3_MUTEX_CLEAR(&tqs->txQ0.qLock);
    NCP_TASK_V3_MUTEX_CLEAR(&tqs->txQ1.qLock);

    for (i = NCP_NCAV3_FIRST_SHARED_POOL_ID;
         i <= NCP_NCAV3_LAST_SHARED_POOL_ID;
         i++)
    {
        ncp_task_mme_allocator_t *pAllocator = &tqs->mmeAllocator[i];
        NCP_TASK_V3_MUTEX_CLEAR(&pAllocator->mmeLock);
    }

NCP_RETURN_LABEL
    return(ncpStatus);
}

ncp_bool_t
ncp_task_polltime_expired(ncp_task_wait_t *pWait)
{
    ncp_timespec_us_t currTime;
    
    ncp_hr_gettime_us(&currTime);
    return((1 == ncp_hr_time_compare(&currTime, &pWait->pollEndTime)? TRUE: FALSE));
}


ncp_st_t ncp_task_init_sw_state(ncp_t *ncp)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_pool_t *pPool;
    
    /*
     * Init per domain global task state 
     */
    pNcpTaskSwState->cookie = NCP_TASK_STATE_COOKIE;
#ifdef NCP_KERNEL
    pNcpTaskSwState->uMode  = FALSE;
#else
    pNcpTaskSwState->uMode  = TRUE;
#endif
    pNcpTaskSwState->domainId   = ncp->domainId;
    pNcpTaskSwState->perDomainPoolsMask = 0;
    pNcpTaskSwState->ncp        = ncp;         
    pNcpTaskSwState->nca        = ncp->ncaHdl;
    NCP_CALL(ncp_nvm_robust_malloc(sizeof(ncp_task_v3_mutex_t),
                                   (void **)&pNcpTaskSwState->taskIoResourceLock,
                                   NCP_DO_MEMSET));
    NCP_CALL(NCP_TASK_INIT_LOCK(pNcpTaskSwState->taskIoResourceLock, TRUE));
    /*
     * Set up process name array.   The index into the array is the RTE assigned PID.
     */
    pNcpTaskSwState->numActivePids = 0;
    pNcpTaskSwState->currPidArrayEntries  =  NCP_TASK_INITIAL_PID_LIMIT; /* can be grown with realloc at runtime */
    NCP_CALL(ncp_nvm_robust_malloc(
            (pNcpTaskSwState->currPidArrayEntries * sizeof(ncp_task_process_info_t *)), 
            (void **)&pNcpTaskSwState->pidArray,
            NCP_DO_MEMSET));
    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                          ncp_xlf_task_init_sw_state_allocatedPidArray,
                          NCP_MSG_DEBUG, "Allocated pid array @ %p\r\n",
                          pNcpTaskSwState->pidArray);

    /* 
     * We use the entry for task memory pool 1 for the fixed pool (pool 31).   
     * The fixed pool is encoded as 1,  so this works out nicely.
     * Note: we only set up blockVA(end) [2],   since fixed pool blocks are all 16K.
     * Note: NCP_TASK_FIXED_POOL_ENCODED_ID is defined to be 1.
     */
    
    /* Wipe any existing state from the "real" pool 1,   which is never used by Task I/O */
    pPool = &pNcpTaskSwState->taskPools[NCP_TASK_FIXED_POOL_ENCODED_ID];    
    memset(pPool, 0, sizeof(ncp_task_pool_t));
    
    if (pNcpTaskSwState->fixedPoolInfo.valid)     
    {
        /* Use pool 1 entry for fixed pool. */
        pPool->valid            = TRUE;
        pPool->poolPA           = pNcpTaskSwState->fixedPoolInfo.physicalBase;
        pPool->poolSize         = pNcpTaskSwState->fixedPoolInfo.size;
        pPool->poolVA           = pNcpTaskSwState->fixedPoolInfo.virtualBase;
        pPool->poolVAEnd        = pPool->poolVA + pNcpTaskSwState->fixedPoolInfo.size;                     
        pPool->blocksVA[2]      = pPool->poolVA;
        pPool->blocksVAend[2]   = pPool->poolVAEnd;
        strncpy(pPool->name.name,
                pNcpTaskSwState->fixedPoolInfo.name.name,
                sizeof(ncp_task_resource_name_t));        
    }        
    
    /*
     * Set up tbr arrays
     */
    NCP_TASK_INITIALIZE_TBR_ARRAYS();
        
    /*
     * Currently is a no-op unless NCP_NCA_ARM_PMU_PROFILING_ENABLED is 
     * enabled in build flags and ARM platform.
     * May be abstracted to support X86 in the future.
     */
    NCP_TASK_PMU_ENABLE();
                  
NCP_RETURN_LABEL
    return(ncpStatus);        
}

ncp_st_t
ncp_task_do_wait(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl, 
                 ncp_task_wait_t *pWait, 
                 ncp_dev_hdl_t dev,
                 ncp_uint8_t   tqsID)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    
    /*
     * Is polling enabled? 
     */
    if (0 != pWait->poll_timeout_value_us) 
    {    
        if (FALSE == pWait->pollInProgress)
        {
            pWait->pollInProgress = TRUE;
            if (-1 != pWait->poll_timeout_value_us)
            {
                ncp_hr_gettime_us(&pWait->pollStartTime);
                ncp_hr_addtime_us(&pWait->pollStartTime, &pWait->pollEndTime, pWait->poll_timeout_value_us);
                if (0 <= ncp_hr_time_compare(&pWait->pollStartTime, &pWait->pollEndTime))
                {
                    pWait->pollTimeWraps = FALSE;
                }      
                else
                {
                    pWait->pollTimeWraps = TRUE;
                }                                            
            }  
            if (NCP_TASK_POLL_TYPE_SLEEP_POLL == pWait->poll_type)
            {
                ncp_sys_usleep(pWait->sleep_poll_value_us);
            }  
            NCP_JUMP_RETURN();             
        }
        
        /* Done polling? */
        
        if ((-1 == pWait->poll_timeout_value_us)
            || (FALSE == ncp_task_polltime_expired(pWait)))
        {    
            if (NCP_TASK_POLL_TYPE_SLEEP_POLL == pWait->poll_type)
            {
                ncp_sys_usleep(pWait->sleep_poll_value_us);
            }
            NCP_JUMP_RETURN();
        } 
    }                     
    
    /* 
     * Wait on interrupt,   or return timeout
     */
     
    if (NCP_NCA_WAIT_NONE != pWait->isr_wait_type)
    {
        /* RWXXX
        NCP_TASK_BLOCK_ON_INTERRUPT(pvtTqsHdl, 
                                    dev, 
                                    pWait->isr_wait_type, 
                                    pWait->tqsRelId,
                                    tqsID);
        */
    }
    else
    {
        ncpStatus =  pWait->pollTimeoutEC;;
    }         
      
NCP_RETURN_LABEL
    return(ncpStatus);
} 

/*
 * initialize default wait profiles
 *
 */
ncp_st_t ncp_task_init_wait_profile(
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_poll_type_t pollType;

#ifndef NCP_KERNEL
    pollType = NCP_TASK_POLL_TYPE_SLEEP_POLL;
#else
    pollType = NCP_TASK_POLL_TYPE_HARD_POLL;
#endif

    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_RECV].wait_profile        = NCP_TASK_WAIT_ISR;
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_RECV].isr_wait_type       = NCP_NCA_WAIT_FOR_RX_INTR;
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_RECV].poll_timeout_value_us  = 0;
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_RECV].poll_type           = pollType;    
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_RECV].sleep_poll_value_us = 0;
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_RECV].pollInProgress      = FALSE;
    memset(&pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_RECV].pollStartTime, 0, sizeof(ncp_timespec_us_t));
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_RECV].pollTimeoutEC       = NCP_ST_TASK_RECV_QUEUE_EMPTY;    
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_RECV].tqsRelId            = 0; /* N/A */
    
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_RECV_QUEUE_FLUSH].wait_profile        = NCP_TASK_WAIT_TIMEOUT; 
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_RECV_QUEUE_FLUSH].isr_wait_type       = NCP_NCA_WAIT_NONE;    
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_RECV_QUEUE_FLUSH].poll_timeout_value_us  = 2000000;
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_RECV_QUEUE_FLUSH].poll_type           = pollType;    
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_RECV_QUEUE_FLUSH].sleep_poll_value_us = 1;
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_RECV_QUEUE_FLUSH].pollInProgress      = FALSE;
    memset(&pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_RECV_QUEUE_FLUSH].pollStartTime, 0, sizeof(ncp_timespec_us_t)); 
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_RECV_QUEUE_FLUSH].pollTimeoutEC       = NCP_ST_SUCCESS;  
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_RECV_QUEUE_FLUSH].tqsRelId            = 0; /* N/A */       
    
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ0].wait_profile        = NCP_TASK_WAIT_TIMEOUT;
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ0].isr_wait_type       = NCP_NCA_WAIT_NONE;    
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ0].poll_timeout_value_us  = -1;
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ0].poll_type           = pollType;
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ0].sleep_poll_value_us = 0;
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ0].pollInProgress      = FALSE;
    memset(&pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ0].pollStartTime, 0, sizeof(ncp_timespec_us_t));
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ0].pollTimeoutEC       = NCP_ST_TASK_SEND_QUEUE_FULL;   
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ0].tqsRelId            = NCP_TASK_TXQ_0;
    
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ1].wait_profile        = NCP_TASK_WAIT_TIMEOUT; 
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ1].isr_wait_type       = NCP_NCA_WAIT_NONE;    
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ1].poll_timeout_value_us  = -1;
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ1].poll_type           = pollType;
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ1].sleep_poll_value_us = 0;
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ1].pollInProgress      = FALSE;
    memset(&pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ1].pollStartTime, 0, sizeof(ncp_timespec_us_t));
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ1].pollTimeoutEC       = NCP_ST_TASK_SEND_QUEUE_FULL;
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ1].tqsRelId            = NCP_TASK_TXQ_1;           
    
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_ALLOC].wait_profile        = NCP_TASK_WAIT_TIMEOUT; 
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_ALLOC].isr_wait_type       = NCP_NCA_WAIT_NONE;    
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_ALLOC].poll_timeout_value_us  = -1;
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_ALLOC].poll_type           = pollType;    
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_ALLOC].sleep_poll_value_us = 0;
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_ALLOC].pollInProgress      = FALSE;
    memset(&pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_ALLOC].pollStartTime, 0, sizeof(ncp_timespec_us_t)); 
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_ALLOC].pollTimeoutEC       = NCP_ST_NO_MEMORY;     
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_ALLOC].tqsRelId            = 0; /* N/A */

    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_REFILL_TXQ0].wait_profile        = NCP_TASK_WAIT_TIMEOUT; 
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_REFILL_TXQ0].isr_wait_type       = NCP_NCA_WAIT_NONE;     
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_REFILL_TXQ0].poll_timeout_value_us  = -1;
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_REFILL_TXQ0].poll_type           = pollType;    
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_REFILL_TXQ0].sleep_poll_value_us = 0;
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_REFILL_TXQ0].pollInProgress      = FALSE;
    memset(&pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_REFILL_TXQ0].pollStartTime, 0, sizeof(ncp_timespec_us_t));    
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_REFILL_TXQ0].pollTimeoutEC       = NCP_ST_TASK_WAIT_TIMEOUT;      
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_REFILL_TXQ0].tqsRelId            = NCP_TASK_TXQ_0;
    
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_REFILL_TXQ1].wait_profile        = NCP_TASK_WAIT_TIMEOUT; 
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_REFILL_TXQ1].isr_wait_type       = NCP_NCA_WAIT_NONE;     
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_REFILL_TXQ1].poll_timeout_value_us  = -1;
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_REFILL_TXQ1].poll_type           = pollType;    
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_REFILL_TXQ1].sleep_poll_value_us = 0;
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_REFILL_TXQ1].pollInProgress      = FALSE;
    memset(&pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_REFILL_TXQ1].pollStartTime, 0, sizeof(ncp_timespec_us_t));    
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_REFILL_TXQ1].pollTimeoutEC       = NCP_ST_TASK_WAIT_TIMEOUT;   
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_REFILL_TXQ1].tqsRelId            = NCP_TASK_TXQ_1;    
            
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_FREE_TXQ0].wait_profile        = NCP_TASK_WAIT_TIMEOUT; 
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_FREE_TXQ0].isr_wait_type       = NCP_NCA_WAIT_NONE;     
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_FREE_TXQ0].poll_timeout_value_us  = -1;
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_FREE_TXQ0].poll_type           = pollType;    
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_FREE_TXQ0].sleep_poll_value_us = 0;
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_FREE_TXQ0].pollInProgress      = FALSE;
    memset(&pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_FREE_TXQ0].pollStartTime, 0, sizeof(ncp_timespec_us_t));    
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_FREE_TXQ0].pollTimeoutEC       = NCP_ST_TASK_WAIT_TIMEOUT;      
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_FREE_TXQ0].tqsRelId            = NCP_TASK_TXQ_0;
    
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_FREE_TXQ1].wait_profile        = NCP_TASK_WAIT_TIMEOUT; 
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_FREE_TXQ1].isr_wait_type       = NCP_NCA_WAIT_NONE;     
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_FREE_TXQ1].poll_timeout_value_us  = -1;
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_FREE_TXQ1].poll_type           = pollType;    
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_FREE_TXQ1].sleep_poll_value_us = 0;
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_FREE_TXQ1].pollInProgress      = FALSE;
    memset(&pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_FREE_TXQ1].pollStartTime, 0, sizeof(ncp_timespec_us_t));    
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_FREE_TXQ1].pollTimeoutEC       = NCP_ST_TASK_WAIT_TIMEOUT;   
    pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_FREE_TXQ1].tqsRelId            = NCP_TASK_TXQ_1;
            
NCP_RETURN_LABEL
    return(ncpStatus);        
}

ncp_st_t ncp_task_unmap_pools(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,  
                             ncp_uint32_t tqsId)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_tqs_swState_t *pTqs = pvtTqsHdl->pTqs;
    ncp_task_pool_t *pPool;
    int poolId;

    pTqs = &pNcpTaskSwState->tqsSwState[tqsId];
        
    /* Validation
     * 1) check that any pools marked as used are configured for this tqs.
     * 2) check allocator use counts are consistent with "shared" cfg
     *    setting
     */
    for (poolId = 0; poolId < NCP_NCAV3_MAX_SHARED_POOLS; poolId++)
    {
        int mapCntIdx = poolId;

        if (0 == poolId)
        {        
            if (0 != pvtTqsHdl->cpuPoolId)
            {
                pPool = &pNcpTaskSwState->taskPools[pvtTqsHdl->cpuPoolId]; 

                mapCntIdx = pvtTqsHdl->cpuPoolId;
            }  
            else
            {
                continue;
            }         
        }         
        else if (1 == poolId)
        {
            continue;
        }
        else
        {
            if (0 == (pTqs->validPoolsMask & (1<<poolId)))
            {    
                continue;
            } 
            pPool = &pNcpTaskSwState->taskPools[poolId];    
        }                
     
        if (0 != (pvtTqsHdl->mappedPools & (1<<poolId)))
        {    
            if (1 == ncpTaskPoolMapCnt[mapCntIdx])
            {    
				munmap(pPool->poolVA, pPool->poolSize);
            }
            (pvtTqsHdl->mappedPools &= ~(1<<poolId));
            ncpTaskPoolMapCnt[mapCntIdx]--;
        }    
    } /* for */ 
    
NCP_RETURN_LABEL
    return(ncpStatus);
}  

ncp_st_t ncp_task_map_pools(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,  
                             ncp_uint32_t tqsId) 
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_ncav3_application_profile_t *pAppProfile;
    ncp_task_tqs_swState_t *pTqs;
    ncp_task_pool_t *pPool;
    int poolId;

    pTqs = &pNcpTaskSwState->tqsSwState[tqsId];
    pAppProfile = pTqs->pAppProfile;

    if (pAppProfile == NULL)
    {
        NCP_CALL(NCP_ST_TASK_TQS_NOT_CONFIGURED);
    }
        
    /* Validation
     * 1) check that any pools mared used are configured for this tqs.
     * 2) check allocator use counts are consistent with "shared" cfg
     *    setting
     */
     
    for (poolId = 0; poolId < NCP_NCAV3_MAX_SHARED_POOLS; poolId++) 
    {
        int mapCntIdx = poolId;

        if (0 == poolId)
        {        
            if (0 != pvtTqsHdl->cpuPoolId)
            {
                pPool = &pNcpTaskSwState->taskPools[pvtTqsHdl->cpuPoolId]; 

                mapCntIdx = pvtTqsHdl->cpuPoolId;
            }        
            else
            {
                continue;
            }    
        }         
        else if (1 == poolId)
        {
            continue;
        }
        else
        {
            if (0 == (pTqs->validPoolsMask & (1<<poolId)))
            {    
                continue;
            } 
            pPool = &pNcpTaskSwState->taskPools[poolId];    
        }                
     
        if (0 == ncpTaskPoolMapCnt[mapCntIdx])
        {   
			debug("mmap memory pool\n");
			pPool->poolVA = pPool->poolPA;
#if 0 
			mmapResult = mmap((void *)pPool->poolVA, pPool->poolSize, (PROT_READ | PROT_WRITE), MAP_SHARED,
                           (intptr_t)myDevHdl, (off_t) pPool->poolPA);
            NCP_ASSERT((mmapResult == (void *)pPool->poolVA),
                    NCP_ST_TASK_MMAP_FAILED);
#endif

        }
        pvtTqsHdl->mappedPools |= (1<<poolId);
        ncpTaskPoolMapCnt[mapCntIdx]++;
    } /* for */ 
    
NCP_RETURN_LABEL
    return(ncpStatus);
}                                     

ncp_st_t
ncp_task_attach_tqs(ncp_hdl_t *ncpHdl, ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,  ncp_uint32_t tqsId, ncp_task_tqs_usage_t *pParams)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_tqs_swState_t *pTqs = &pNcpTaskSwState->tqsSwState[tqsId];
	debug("get tqs: %d\t", tqsId);
    debug("valid pools mask %d\n",pTqs->validPoolsMask);
    int poolId;
    
    /* First validate permissions/usage */
    
    if (pParams->useRxQueue)
    {
        if (((pTqs->shareCtl.rxQ_useCnt + 1) > 1) && (FALSE == pTqs->shareCtl.shareFlags.sharedRxQueue))
        {
            NCP_CALL(NCP_ST_TASK_TQS_SHARING_VIOLATION);
        }      
    }          
    if (pParams->useTxQueue0)
    {
        if (((pTqs->shareCtl.txQ0_useCnt + 1) > 1) && (FALSE == pTqs->shareCtl.shareFlags.sharedTxQueue0))
        {
            NCP_CALL(NCP_ST_TASK_TQS_SHARING_VIOLATION);
        }           
    }  
    if (pParams->useTxQueue1)
    {
        if (((pTqs->shareCtl.txQ1_useCnt + 1) > 1) && (FALSE == pTqs->shareCtl.shareFlags.sharedTxQueue1))        
        {
            NCP_CALL(NCP_ST_TASK_TQS_SHARING_VIOLATION);
        }               
    } 
    if  (pParams->useRxQueue 
      && (FALSE == pTqs->rxQ.u.ipcq_info.autoCompletionMode)
      && (FALSE == pParams->useTxQueue0)
      && (FALSE == pParams->useTxQueue1))
    {
        NCP_CALL(NCP_ST_TASK_MANUAL_COMPLETION_REQUIRES_TXQ);
    }
           
    /* Valildate allocator usage */
    for (poolId = NCP_NCAV3_FIRST_SHARED_POOL_ID; 
         poolId < NCP_NCAV3_MAX_SHARED_POOLS; 
         poolId++)
    {
        if (pParams->useAllocator[poolId])
        {
			
            if (0 == (pTqs->validPoolsMask & (1<<poolId)))
            {
                NCP_CALL(NCP_ST_TASK_TQS_INVALID_POOL);
            }        
            if (((pTqs->shareCtl.allocatorUseCnt[poolId] + 1) > 1) 
                && (FALSE == pTqs->shareCtl.shareFlags.sharedAllocator[poolId]))
            {
                NCP_CALL(NCP_ST_TASK_TQS_SHARING_VIOLATION);                
            }        
        } 
    } 

    /* Queue access/permission validated,   save some state info and move on to mapping the memory pools */
            
    pvtTqsHdl->pTqs = pTqs;
    if (0 != (pvtTqsHdl->cpuPoolId = pTqs->cpuPoolId))
    {
        pvtTqsHdl->cpuPoolHdl = &pNcpTaskSwState->taskPools[pTqs->cpuPoolId];
    }        
    pvtTqsHdl->tqsId  = tqsId;
        
    
    NCP_CALL(ncp_task_map_pools(pvtTqsHdl,  
                                tqsId)); 


    /* RWXXX NCP_CALL(ncp_ncav3_map_unscheduled_queues()); */

    /*
     * Allocate per thread sendDone PCQs 
     */
     
     /* TXQ0 sendone */
    memset(&pvtTqsHdl->sendDoneInfo[0], 0, sizeof(ncp_task_pvt_sendDone_ctl_t));
    pvtTqsHdl->sendDoneInfo[0].nEntriesMinusOne = NCP_TASK_API_MAX_BULK_ITEM_COUNT - 1;
    NCP_CALL(ncp_nvm_robust_malloc( (NCP_TASK_API_MAX_BULK_ITEM_COUNT*sizeof(ncp_task_sendDone_entry_t)),
                                 (void **)&pvtTqsHdl->sendDoneInfo[0].entries,
                                 NCP_DO_MEMSET));   
    pvtTqsHdl->sendDoneInfo[0].currFillEntry
        = pvtTqsHdl->sendDoneInfo[0].currPendingEntry
        = pvtTqsHdl->sendDoneInfo[0].entries;        
    
     /* TXQ1 sendone */
    memset(&pvtTqsHdl->sendDoneInfo[1], 0, sizeof(ncp_task_pvt_sendDone_ctl_t));
    pvtTqsHdl->sendDoneInfo[1].nEntriesMinusOne = NCP_TASK_API_MAX_BULK_ITEM_COUNT - 1;
    NCP_CALL(ncp_nvm_robust_malloc( (NCP_TASK_API_MAX_BULK_ITEM_COUNT*sizeof(ncp_task_sendDone_entry_t)),
                                 (void **)&pvtTqsHdl->sendDoneInfo[1].entries,
                                 NCP_DO_MEMSET));   
    pvtTqsHdl->sendDoneInfo[1].currFillEntry
        = pvtTqsHdl->sendDoneInfo[1].currPendingEntry
        = pvtTqsHdl->sendDoneInfo[1].entries;        
     
     
    /* Now its ok to update use counts */    
    if (pParams->useRxQueue)
    {
        pTqs->shareCtl.rxQ_useCnt++; 
        pvtTqsHdl->useFlags.useRxQueue = TRUE;         
    }          
    if (pParams->useTxQueue0)
    {
        pTqs->shareCtl.txQ0_useCnt++;
        pvtTqsHdl->useFlags.useTxQueue[0] = TRUE;        
    }  
    if (pParams->useTxQueue1)
    {
        pTqs->shareCtl.txQ1_useCnt++;
        pvtTqsHdl->useFlags.useTxQueue[1] = TRUE;        
    } 
    
    /* Valildate allocator usage */
    for (poolId = NCP_NCAV3_FIRST_SHARED_POOL_ID; 
         poolId < NCP_NCAV3_MAX_SHARED_POOLS; 
         poolId++)
    {
        if (pParams->useAllocator[poolId])
        {
            pTqs->shareCtl.allocatorUseCnt[poolId]++;
            pvtTqsHdl->useFlags.useAllocator[poolId] = TRUE;            
        } 
    }  
       
    pvtTqsHdl->pProcess->poolsMask |= pTqs->validPoolsMask;

    /* RWXXX
    NCP_CALL(ncp_ncav3_map_shared_data_regions(pvtTqsHdl));

    NCP_CALL(ncp_ncav3_map_fixed_pool(
        &pvtTqsHdl->pTqs->pAppProfile->baseProfile));
    */

    /* If this is the first handle to bind to this TQS, turn on its iPCQ */

    if (0 == pvtTqsHdl->pTqs->tqsUseCnt)
    {
        ncp_dev_hdl_t dev = ncp_dev_hdls[((ncp_t *) ncpHdl)->id];

        NCP_CALL(ncp_ncav3_enable_ipcq(dev, tqsId / 8, tqsId % 8, tqsId));
    }
    
    /* RWXXX NCP_TASK_INCREMENT_POOL_USE_COUNTS(pvtTqsHdl); */
    

    
    /* add to list of handles associated with this tqs */
    pvtTqsHdl->nextClientTqsHdl = pTqs->clientTqsHdls;
    pTqs->clientTqsHdls = pvtTqsHdl;
    
    pTqs->tqsUseCnt++;

    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                          ncp_xlf_task_attach_tqs_addedTqsHdlInstance1,
                          NCP_MSG_DEBUG,
                          "Added tqsHdl (instance 1) %p fom client list for tqsId=%d, new useCnt=%d, clientHdlsBase=%p\r\n",
                          pvtTqsHdl, (int)pTqs->tqsId, (int)pTqs->tqsUseCnt,
                          pTqs->clientTqsHdls);

    pvtTqsHdl->cookie = NCP_TASK_TQS_HDL_COOKIE;
    
NCP_RETURN_LABEL
    if (NCP_ST_SUCCESS != ncpStatus)
    {
        /* update mapped pool state, ignoring any errors */
        ncp_task_unmap_pools(pvtTqsHdl,  
                             tqsId);
    }        
                            
    return(ncpStatus);
}

ncp_st_t
ncp_task_detach_tqs(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_tqs_swState_t *pTqs 
        = &pNcpTaskSwState->tqsSwState[pvtTqsHdl->tqsId];
    ncp_task_pvt_tqsHdl_data_t *tmpTqsHdl;      
    int poolId;

    /* update perQ use-counts */    
    if (pvtTqsHdl->useFlags.useRxQueue)
    {
        pTqs->shareCtl.rxQ_useCnt--;          
    }          
    if (pvtTqsHdl->useFlags.useTxQueue[0])
    {
        pTqs->shareCtl.txQ0_useCnt--;
    }  
    if (pvtTqsHdl->useFlags.useTxQueue[1])
    {
        pTqs->shareCtl.txQ1_useCnt--;
    }  

    /*
     * Remove handle from tqs list 
     */

    pTqs->tqsUseCnt--;

    if (pvtTqsHdl == pTqs->clientTqsHdls)
    {
        pTqs->clientTqsHdls = pvtTqsHdl->nextClientTqsHdl;

        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_detach_tqs_removedTqsHdlInstance1,
                              NCP_MSG_DEBUG,
                              "Removed tqsHdl (instance 1) %p fom client list for tqsId=%d, new useCnt=%d, clientHdlsBase = %p\r\n",
                              pvtTqsHdl, (int)pTqs->tqsId, pTqs->tqsUseCnt,
                              pTqs->clientTqsHdls);

    }
    else
    {
        tmpTqsHdl = (ncp_task_pvt_tqsHdl_data_t *)pTqs->clientTqsHdls;    
        while(tmpTqsHdl)
        {
            if (pvtTqsHdl == tmpTqsHdl->nextClientTqsHdl)
            {
                tmpTqsHdl->nextClientTqsHdl = pvtTqsHdl->nextClientTqsHdl;

                NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                      ncp_xlf_task_detach_tqs_removedTqsHdlInstance2,
                                      NCP_MSG_DEBUG,
                                      "Removed tqsHdl (instance 2) %p fom client list for tqsId=%d, , new useCnt=%d, clientHdlsBase = %p\r\n",
                                      pvtTqsHdl, (int)pTqs->tqsId, pTqs->tqsUseCnt,
                                      pTqs->clientTqsHdls);

                break;
            } 
            tmpTqsHdl = tmpTqsHdl->nextClientTqsHdl;       
        }     
    }

    if (0 == pTqs->tqsUseCnt)
    {
#if (1 == NCP_TASK_TBR_ENABLED)
        /* RWXXX NCP_TASK_TBR_TQS_IN_RECOVERY_CLEAR(myNcpHdl, pTqs); */
#endif
    }

    for (poolId = NCP_NCAV3_FIRST_SHARED_POOL_ID; 
         poolId < NCP_NCAV3_MAX_SHARED_POOLS; 
         poolId++)
    {
        if (pvtTqsHdl->useFlags.useAllocator[poolId])
        {
            pTqs->shareCtl.allocatorUseCnt[poolId]--;
        } 
    }    

    NCP_CALL(ncp_nvm_robust_free((void **)&(pvtTqsHdl->sendDoneInfo[0].entries)));

    NCP_CALL(ncp_nvm_robust_free((void **)&(pvtTqsHdl->sendDoneInfo[1].entries)));

    /* TODO - if domain bundle was mapped,   then unmap it - OR does app call detach? */

    /* if any pools were mapped,   then unmap them now */
    ncp_task_unmap_pools(pvtTqsHdl,  
                         pvtTqsHdl->tqsId);

    /* RWXXX
    NCP_CALL(ncp_ncav3_unmap_shared_data_regions(pvtTqsHdl));
    
    NCP_CALL(ncp_ncav3_unmap_fixed_pool());
    */
    
NCP_RETURN_LABEL

    return(ncpStatus);
}         

/* 
 * map domain bundle
 */
ncp_st_t
ncp_task_mmap_attach(ncp_t *ncp, 
                     void **pDomainBundle) 
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
                                                            
#if  defined(NCP_DEV_SOCKET) 
    return (ncpStatus);
#else    
#ifndef NCP_KERNEL
    ncp_dev_hdl_t devHdl = ncp_dev_hdls[ncp->id];
    
    if ((ncp_dev_hdl_t)-1 == devHdl)
    {                                                               
        NCP_CALL(NCP_ST_INTERNAL_ERROR);                            
    }   

    *pDomainBundle
        = (void *)
        NCP_TASK_MEM_MMAP(devHdl, 
                      (void *)pNcpTaskSwState->domainMemMap.domainBundle_VA,    
                       pNcpTaskSwState->domainMemMap.domainBundle_Size,
                       pNcpTaskSwState->domainMemMap.domainBundle_PA);   
    
    NCP_ASSERT(
        (*pDomainBundle == (void *)
        pNcpTaskSwState->domainMemMap.domainBundle_VA), NCP_ST_TASK_MMAP_FAILED);
        
#else    /* NCP_KERNEL */
    *pDomainBundle = (void *)pNcpTaskSwState->domainMemMap.domainBundle_VA;
#endif  /* NCP_KERNEL */  

#ifdef NCP_TASK_PRINT_BASE_ADDRESSES_AND_MAPPINGS
    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                          ncp_xlf_task_mmap_attach_mappedDomainBundle,
                          NCP_MSG_DEBUG, "mapped domainBundle at VA %p\r\n",
                          (void *)*pDomainBundle);
#endif
    
NCP_RETURN_LABEL
    return(ncpStatus);
#endif /* SOCKET */    
}

/* 
 * unmap domain bundle
 */
ncp_st_t
ncp_task_mmap_detach(ncp_t *ncp, 
                     void *pDomainBundle) 
{

    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
                                                            
#if  defined(NCP_DEV_SOCKET) 
    return (ncpStatus);
#else    
#ifndef NCP_KERNEL
    ncp_dev_hdl_t devHdl = ncp_dev_hdls[ncp->id];
    
    if ((ncp_dev_hdl_t)-1 == devHdl)
    {                                                               
        NCP_CALL(NCP_ST_INTERNAL_ERROR);                            
    } 
    
    NCP_USER_MEM_UNMAP(pDomainBundle,  pNcpTaskSwState->domainMemMap.domainBundle_Size);

#ifdef NCP_TASK_PRINT_BASE_ADDRESSES_AND_MAPPINGS
    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                          ncp_xlf_task_mmap_detach_unmappedDomainBundle,
                          NCP_MSG_DEBUG, "unmapped domainBundle at VA %p\r\n",
                          (void *)*pDomainBundle);
#endif
#endif /* NCP_KERNEL */  
  
NCP_RETURN_LABEL
    return(ncpStatus);
#endif /* SOCKET */    
}
/*TODO MM*/
/* TODO - Move some of these to inline funcs after unit tested */

  
/* NCP_INLINE */ 
ncp_st_t
ncp_task_bulk_task_send(
                ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
                ncp_task_pcq_t *p_oPCQ,
                ncp_uint32_t numTasks,
                ncp_uint32_t *pNumTasksSent,
                ncp_task_send_meta_t *pMetadata,
                ncp_int32_t *pCompletionsIssued,
                ncp_bool_t wait)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    /* ncp_task_tqs_swState_t *pTqs = pvtTqsHdl->pTqs; */
    ncp_bool_t barrierIssued = FALSE;
    ncp_uint32_t skipBarrierCnt = p_oPCQ->nEntriesDiv2;    
    opcq_entry_overlay_t *pEntry = (opcq_entry_overlay_t *)p_oPCQ->u.opcq_info.pOPCQentry;
    ncp_task_send_meta_t *pCurrMetadata = pMetadata;
    opcq_entry_overlay_t savedEntryVal;   
    ncp_uint32_t numSent=0;
    int numRemaining=numTasks;
    int currLoopCount;
    ncp_bool_t needPollStateReset = TRUE;
    ncp_int32_t completionsIssued=0;
    NCP_TASK_TBR_STATE_PTRS_DECL()    
    
    
    /* fill in fields that never change, and save a copy of the dword containing them */
    savedEntryVal.u.opcqDword[1] = 0;
    savedEntryVal.u.opcqEntry.cmd =  NCP_NCAV3_CMD_SENDTH;
    savedEntryVal.u.opcqEntry.interruptEn = 1;
    /* savedEntryVal.flowControlDisabled = 0; */ /* already zero */

    if (p_oPCQ->u.opcq_info.sendDoneCnt)
    {
        NCP_TASK_UPDATE_NUM_TX_ENTRIES_AVAIL(pvtTqsHdl, p_oPCQ);
    }        
    while(numRemaining)
    {
        int tmpSent;
        
        do
        {
            if ((numRemaining) <= p_oPCQ->u.opcq_info.numTxAvail)
            {
                currLoopCount = numRemaining; 
                break;
            }
                    
            /* update num entries available */
            NCP_TASK_UPDATE_NUM_TX_ENTRIES_AVAIL(pvtTqsHdl, p_oPCQ);
            if (0 == p_oPCQ->u.opcq_info.numTxAvail) 
            {
                if (wait)
                {  
                    ncp_st_t tmpStatus;                       

                    if (needPollStateReset)
                    {
                        needPollStateReset = FALSE;               
                        NCP_TASK_RESET_POLL_STATE(&pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ0 + p_oPCQ->u.opcq_info.relId]);   
                    }
                    if (NCP_ST_SUCCESS != (tmpStatus = NCP_TASK_DO_WAIT(
                            pvtTqsHdl,
                            (&pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ0 + p_oPCQ->u.opcq_info.relId]),
                            myDevHdl,
                            pvtTqsHdl->tqsId)))
                    {
                        ncpStatus = tmpStatus;
                        NCP_JUMP_RETURN();
                    }            
                }
                else
                {
                    ncpStatus = NCP_ST_TASK_SEND_QUEUE_FULL;
                    NCP_JUMP_RETURN();
                }  
            } 
            else
            {
                if ((numRemaining) <= p_oPCQ->u.opcq_info.numTxAvail)
                {
                    currLoopCount = numRemaining; 
                }                      
                else
                {    
                    currLoopCount = p_oPCQ->u.opcq_info.numTxAvail;                          
                }    
                break;
            }    
        } while(1);
        
        /* it is *not* ok to preadjust TxAvail count here,  since errors are possible within the loop */
        tmpSent = 0;            
        numRemaining -= currLoopCount;
        while(currLoopCount--)
        {
            
            /* It is possible for the send done array to be full, so test it early. */
            if (pCurrMetadata->sendDoneFn)
            {
                if (NCP_ST_SUCCESS != (ncpStatus = NCP_TASK_ADD_SEND_DONE(pvtTqsHdl,
                                       p_oPCQ->u.opcq_info.relId,
                                       NCP_TASK_TASK_CALLBACK,
                                       pCurrMetadata->sendDoneFn,
                                       pCurrMetadata->sendDoneArg,
                                       pCurrMetadata->taskHeader,
                                       0,
                                       0)))
                {  
                    /* update state before erroring out */                  
                    numSent += tmpSent;
                    p_oPCQ->u.opcq_info.numTxAvail -= tmpSent;
                    NCP_TASK_OPCQ_ISSUE_BARRIER_AND_WRITE_PIDX(p_oPCQ); 
                    barrierIssued = TRUE;
                    NCP_CALL(ncpStatus);
                }                             
            } 
                        
            NCP_TASK_VALIDATE_OUTPUT_TASK(pvtTqsHdl, pCurrMetadata->taskHeader);

            NCP_TASK_TBR_STATE_PTRS_INIT();             
            NCP_TASK_TBR_TXTASK_STATE_PREFETCH(pvtTqsHdl, 
                                             pCurrMetadata->taskHeader, 
                                             pCurrMetadata->freeHeader, 
                                             pCurrMetadata->freeDataPointers,
                                             p_oPCQ,
                                             pTbr);
                                                                      
            /*
             * Set up what will be the contents of the oPCQ entry, note savedEntryVal initialized above
             */
            pEntry->u.opcqDword[1] = savedEntryVal.u.opcqDword[1];
            pEntry->u.opcqEntry.taskAddress = (ncp_uint64_t) (pCurrMetadata->taskHeader);
    
            /* pEntry->u.opcqEntry.headerSize is currently zero */
            if ((pCurrMetadata->taskHeader->ptrCnt > 2) || (1 == pCurrMetadata->taskHeader->debugValid))
            {
                pEntry->u.opcqEntry.headerSize = 1; /* 128B */            
            }
              
            pEntry->u.opcqEntry.headerPool = pCurrMetadata->taskHeader->headerPool;
            pEntry->u.opcqEntry.headerPoolMref = pCurrMetadata->taskHeader->headerPoolMref;

            pEntry->u.opcqEntry.headerSeparate = !pCurrMetadata->taskHeader->combinedHeader;
            
            /* pEntry->u.opcqEntry.taskCompletion is currently zero */
            if (pCurrMetadata->issueCompletion)
            {   
                NCP_TASKIO_CHECK((FALSE == pvtTqsHdl->pTqs->rxQ.u.ipcq_info.autoCompletionMode),
                             NCP_ST_TASK_RX_QUEUE_IS_AUTOMATIC_COMPLETION);
                NCP_TASKIO_CHECK(1 <= pvtTqsHdl->completionsOwed,
                             NCP_ST_TASK_TOO_MANY_TASK_COMPLETIONS);
                completionsIssued++;                      
                pEntry->u.opcqEntry.taskCompletion = 1;
            }  
            
            /* pEntry->u.opcqEntry.forceCopy is currently zero */      
            if (pCurrMetadata->sendDoneFn)
            {    
                pEntry->u.opcqEntry.forceCopy = 1;
            }
            
            /* pEntry->u.opcqEntry.returnHeader = NCP_NCAV3_SENDTH_RCCH_DEC_REFCNT_RETURN_HDR; */ /* already zero */
            /* pEntry->u.opcqEntry.quotaIncludeHeader = NCP_NCAV3_SENDTH_MQGI_INCL_HDR; */        /* already zero */                          
            if (0 == pCurrMetadata->freeHeader)
            {
                pEntry->u.opcqEntry.returnHeader = NCP_NCAV3_SENDTH_RCCH_NOOP_REFCNT_KEEP_HDR;
                pEntry->u.opcqEntry.quotaIncludeHeader = NCP_NCAV3_SENDTH_MQGI_EXCL_HDR;
            }

            /* pEntry->u.opcqEntry.returnData    = NCP_NCAV3_SENDTH_RCCD_DEC_REFCNT_RETURN_DATA; */ /* already zero */
            /* pEntry->u.opcqEntry.quotaTransfer = NCP_NCAV3_SENDTH_MQGC_DEC_SOURCE;             */ /* already zero */            
            if (0 == pCurrMetadata->freeDataPointers)
            {
                pEntry->u.opcqEntry.returnData    = NCP_NCAV3_SENDTH_RCCD_NOOP_REFCNT_KEEP_DATA;
                pEntry->u.opcqEntry.quotaTransfer = NCP_NCAV3_SENDTH_MQGC_NOOP;
            }         

            NCP_TASK_TBR_BUFFER_STATE_UPDATE_MREF(pTbr);  /* must be done before pgit update! */

            if (pCurrMetadata->sendDoneFn)
            {
                NCP_TASK_FILL_PER_OPCQ_AUX_DATA(pvtTqsHdl, 
                                                p_oPCQ);               
            }
            else 
            {
                NCP_TASK_FILL_PER_OPCQ_AUX_DATA(NULL, 
                                                p_oPCQ);                
            }                 

            NCP_TASK_OPCQ_UPDATE_CACHED_PIDX(p_oPCQ);

            
            if (0 == skipBarrierCnt--)
            {    
                NCP_TASK_OPCQ_ISSUE_BARRIER_AND_WRITE_PIDX(p_oPCQ);
                skipBarrierCnt = p_oPCQ->nEntriesDiv2;
                barrierIssued = TRUE;
            }
            else
            {
                barrierIssued = FALSE;
            } 
            
            tmpSent++;
            pCurrMetadata++;  
            pEntry = (opcq_entry_overlay_t *)p_oPCQ->u.opcq_info.pOPCQentry;
        }
        numSent += tmpSent;
        p_oPCQ->u.opcq_info.numTxAvail -= tmpSent;    
    } /* while numRemaining */

NCP_RETURN_LABEL

    if ((barrierIssued == FALSE) && (0 != numSent))
    {
        NCP_TASK_OPCQ_ISSUE_BARRIER_AND_WRITE_PIDX(p_oPCQ);        
    }

    *pCompletionsIssued = completionsIssued;
    *pNumTasksSent = (numSent);
    
    return(ncpStatus);
         
}

/* NCP_INLINE */
ncp_st_t
ncp_task_bulk_task_quota_transfer(
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
    ncp_task_pcq_t *p_oPCQ,
    ncp_uint8_t destTQS,
    ncp_uint32_t numTasks,
    ncp_task_header_t **pTasks,
    ncp_uint32_t *pNumTasksTransferred,
    ncp_bool_t *pTransferHeader,
    ncp_task_transfer_done_fn_t *pFns,
    void **pTransferDoneArgs,
    ncp_bool_t wait)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_bool_t barrierIssued = FALSE;
    ncp_uint32_t skipBarrierCnt = p_oPCQ->nEntriesDiv2;
    ncp_opcq_entry_t entry={0};
    ncp_uint32_t numSent=0;
    int numRemaining = numTasks;
    int currLoopCount;
    ncp_bool_t needPollStateReset = TRUE;

    /* fill in fields that never change */

    entry.cmd = NCP_NCAV3_CMD_ADPAH;
    entry.interruptEn = 1;
    entry.flowControlDisabled = 0;
    entry.taskCompletion = 0;
    entry.destIpcqId = destTQS;
    entry.returnHeader  = NCP_NCAV3_ADPAH_RCCH_NOOP_REFCNT_KEEP_HDR;
    entry.returnData    = NCP_NCAV3_ADPAH_RCCD_NOOP_REFCNT_RETURN_DATA;
    entry.quotaTransfer = NCP_NCAV3_ADPAH_MQGC_DEC_SOURCE_AND_INC_PCQ;
    entry.forceCopy = 0;

    if (p_oPCQ->u.opcq_info.sendDoneCnt)
    {
        NCP_TASK_UPDATE_NUM_TX_ENTRIES_AVAIL(pvtTqsHdl, p_oPCQ);
    }
    while(numRemaining)
    {
        do
        {
            if ((numRemaining) <= p_oPCQ->u.opcq_info.numTxAvail)
            {
                currLoopCount = numRemaining;
                break;
            }
            /* update num entries available */
            NCP_TASK_UPDATE_NUM_TX_ENTRIES_AVAIL(pvtTqsHdl, p_oPCQ);
            if (0 == p_oPCQ->u.opcq_info.numTxAvail)
            {
                if (wait)
                {
                    ncp_st_t tmpStatus;

                    if (needPollStateReset)
                    {
                        needPollStateReset = FALSE;
                        NCP_TASK_RESET_POLL_STATE(&pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ0 + p_oPCQ->u.opcq_info.relId]);
                    }
                    if (NCP_ST_SUCCESS != (tmpStatus = NCP_TASK_DO_WAIT(
                            pvtTqsHdl,
                            (&pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ0 + p_oPCQ->u.opcq_info.relId]),
                            myDevHdl,
                            pvtTqsHdl->tqsId)))
                    {
                        ncpStatus = tmpStatus;
                        NCP_JUMP_RETURN();
                    }
                }
                else
                {
                    ncpStatus = NCP_ST_TASK_SEND_QUEUE_FULL;
                    NCP_JUMP_RETURN();
                }
            }
            else
            {
                if ((numRemaining) <= p_oPCQ->u.opcq_info.numTxAvail)
                {
                    currLoopCount = numRemaining;
                }
                else
                {
                    currLoopCount = p_oPCQ->u.opcq_info.numTxAvail;
                }
                break;
            }
        } while(1);

        /* it is *not* ok to preadjust TxAvail count here,  since errors are possible within the loop */
        numRemaining -= currLoopCount;

        while(currLoopCount--)
        {
            ncp_task_send_meta_t currMetadata;

            if (pFns)
            {
                currMetadata.sendDoneFn = (ncp_task_send_done_fn_t) pFns[numSent];
            }
            else
            {
                currMetadata.sendDoneFn = NULL;
            }

            /* It is possible for the send done array to be full, so test it early. */
            if (currMetadata.sendDoneFn)
            {
                NCP_CALL(NCP_TASK_ADD_SEND_DONE(pvtTqsHdl,
                                       p_oPCQ->u.opcq_info.relId,
                                       NCP_TASK_TASK_CALLBACK,
                                       currMetadata.sendDoneFn,
                                       pTransferDoneArgs[numSent],
                                       pTasks[numSent],
                                       0, 0));
            }

            /* FIXME: Create VALIDATE_SHARED_POOL_OUTPUT_TASK that errors
                if task and its PDUs are not shared pool buffers */
            NCP_TASK_VALIDATE_OUTPUT_TASK(pvtTqsHdl, pTasks[numSent]);

            /*
             * Set up what will be the contents of the oPCQ entry
             */
            entry.taskAddress = (ncp_uint64_t) pTasks[numSent];

            if ((pTasks[numSent]->ptrCnt <= 2) &&
                (0 == pTasks[numSent]->debugValid))
            {
                entry.headerSize = 0; /* 64BB */
            }
            else
            {
                entry.headerSize = 1; /* 128B */
            }

            entry.headerPool = pTasks[numSent]->headerPool;
            entry.headerPoolMref = pTasks[numSent]->headerPoolMref;

            entry.headerSeparate = !pTasks[numSent]->combinedHeader;

            entry.quotaIncludeHeader = (pTransferHeader[numSent]) ?
                                        NCP_NCAV3_ADPAH_MQGI_INCL_HDR :
                                        NCP_NCAV3_ADPAH_MQGI_EXCL_HDR;

            NCP_TASK_PUT_OPCQ(pvtTqsHdl,
                              p_oPCQ,
                              &currMetadata,
                              &entry);

            numSent++;
            p_oPCQ->u.opcq_info.numTxAvail--;

            if (0 == skipBarrierCnt--)
            {
                NCP_TASK_OPCQ_ISSUE_BARRIER_AND_WRITE_PIDX(p_oPCQ);
                skipBarrierCnt = p_oPCQ->nEntriesDiv2;
                barrierIssued = TRUE;
            }
            else
            {
                barrierIssued = FALSE;
            }
        }
    } /* while numRemaining */

NCP_RETURN_LABEL

    if ((barrierIssued == FALSE) && (0 != numSent))
    {
        NCP_TASK_OPCQ_ISSUE_BARRIER_AND_WRITE_PIDX(p_oPCQ);
    }

    *pNumTasksTransferred = numSent;

    return ncpStatus;
}

/* NCP_INLINE */
ncp_st_t
ncp_task_bulk_buffer_quota_transfer(
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
    ncp_task_pcq_t *p_oPCQ,
    ncp_uint8_t destTQS,
    ncp_uint32_t numDescs,
    ncp_task_buffer_desc_t *pDescs,
    ncp_uint32_t *pNumTasksTransferred,
    ncp_task_buffer_transfer_done_fn_t *pFns,
    void **pTransferDoneArgs,
    ncp_bool_t wait)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_bool_t barrierIssued = FALSE;
    ncp_uint32_t skipBarrierCnt = p_oPCQ->nEntriesDiv2;
    ncp_opcq_entry_t entry={0};
    ncp_uint32_t numSent=0;
    int numRemaining = numDescs;
    int currLoopCount;
    ncp_bool_t needPollStateReset = TRUE;


    /* fill in fields that never change */

    entry.cmd = NCP_NCAV3_CMD_ADPAE;
    entry.interruptEn = 1;
    entry.flowControlDisabled = 0;
    entry.headerSize = 0; /* 64BB */
    entry.taskCompletion = 0;
    entry.headerSeparate = 0;
    entry.destIpcqId = destTQS;
    entry.returnHeader  = NCP_NCAV3_ADPAE_RCCH_NOOP;
    entry.returnData    = NCP_NCAV3_ADPAE_RCCD_NOOP_REFCNT_RETURN_DATA;
    entry.quotaTransfer = NCP_NCAV3_ADPAE_MQGC_DEC_SOURCE_AND_INC_PCQ;
    entry.quotaIncludeHeader = NCP_NCAV3_ADPAE_MQGI_UNDEF_0;
    entry.forceCopy = 0;

    if (p_oPCQ->u.opcq_info.sendDoneCnt)
    {
        NCP_TASK_UPDATE_NUM_TX_ENTRIES_AVAIL(pvtTqsHdl, p_oPCQ);
    }
    while(numRemaining)
    {
        do
        {
            if ((numRemaining) <= p_oPCQ->u.opcq_info.numTxAvail)
            {
                currLoopCount = numRemaining;
                break;
            }
            /* update num entries available */
            NCP_TASK_UPDATE_NUM_TX_ENTRIES_AVAIL(pvtTqsHdl, p_oPCQ);
            if (0 == p_oPCQ->u.opcq_info.numTxAvail)
            {
                if (wait)
                {
                    ncp_st_t tmpStatus;

                    if (needPollStateReset)
                    {
                        needPollStateReset = FALSE;
                        NCP_TASK_RESET_POLL_STATE(&pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ0 + p_oPCQ->u.opcq_info.relId]);
                    }
                    if (NCP_ST_SUCCESS != (tmpStatus = NCP_TASK_DO_WAIT(
                            pvtTqsHdl,
                            (&pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ0 + p_oPCQ->u.opcq_info.relId]),
                            myDevHdl,
                            pvtTqsHdl->tqsId)))
                    {
                        ncpStatus = tmpStatus;
                        NCP_JUMP_RETURN();
                    }
                }
                else
                {
                    ncpStatus = NCP_ST_TASK_SEND_QUEUE_FULL;
                    NCP_JUMP_RETURN();
                }
            }
            else
            {
                if ((numRemaining) <= p_oPCQ->u.opcq_info.numTxAvail)
                {
                    currLoopCount = numRemaining;
                }
                else
                {
                    currLoopCount = p_oPCQ->u.opcq_info.numTxAvail;
                }
                break;
            }
        } while(1);

        /* it is *not* ok to preadjust TxAvail count here,  since errors are possible within the loop */
        numRemaining -= currLoopCount;

        while(currLoopCount--)
        {
            ncp_task_send_meta_t currMetadata;

            if (pFns)
            {
                currMetadata.sendDoneFn = (ncp_task_send_done_fn_t) pFns[numSent];
            }
            else
            {
                currMetadata.sendDoneFn = NULL;
            }

            /* It is possible for the send done array to be full, so test it early. */
            if (currMetadata.sendDoneFn)
            {
                NCP_CALL(NCP_TASK_ADD_SEND_DONE(pvtTqsHdl,
                                       p_oPCQ->u.opcq_info.relId,
                                       NCP_TASK_BUFFER_CALLBACK,
                                       currMetadata.sendDoneFn,
                                       pTransferDoneArgs[numSent],
                                       pDescs[numSent].taskBuffer,
                                       pDescs[numSent].mrefBitIsSet,
                                       pDescs[numSent].poolId));
            }

            /*
             * Set up what will be the contents of the oPCQ entry
             */
            entry.taskAddress = (ncp_uint64_t) pDescs[numSent].taskBuffer;

            /* (mref bit is ignored when there are no refCnt operations) */
            entry.headerPool = pDescs[numSent].poolId;

            NCP_TASKIO_CHECK(((entry.headerPool >= NCP_NCAV3_FIRST_SHARED_POOL_ID) &&
                              (entry.headerPool <= NCP_NCAV3_LAST_SHARED_POOL_ID)),
                            NCP_ST_INVALID_PARAMETER);

            NCP_TASK_PUT_OPCQ(pvtTqsHdl,
                              p_oPCQ,
                              &currMetadata,
                              &entry);

            numSent++;
            p_oPCQ->u.opcq_info.numTxAvail--;

            if (0 == skipBarrierCnt--)
            {
                NCP_TASK_OPCQ_ISSUE_BARRIER_AND_WRITE_PIDX(p_oPCQ);
                skipBarrierCnt = p_oPCQ->nEntriesDiv2;
                barrierIssued = TRUE;
            }
            else
            {
                barrierIssued = FALSE;
            }
        }
    } /* while numRemaining */

NCP_RETURN_LABEL

    if ((barrierIssued == FALSE) && (0 != numSent))
    {
        NCP_TASK_OPCQ_ISSUE_BARRIER_AND_WRITE_PIDX(p_oPCQ);
    }

    *pNumTasksTransferred = numSent;

    return ncpStatus;
}

/* NCP_INLINE */
ncp_st_t
ncp_task_bulk_task_refCnt_increment(
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
    ncp_task_pcq_t *p_oPCQ,
    ncp_uint32_t numTasks,
    ncp_task_header_t **pTasks,
    ncp_uint32_t *pNumTaskRefsIncremented,
    ncp_task_refCnt_inc_done_fn_t *pFns,
    void **pRefCntIncDoneArgs,
    ncp_bool_t wait)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_bool_t barrierIssued = FALSE;
    ncp_uint32_t skipBarrierCnt = p_oPCQ->nEntriesDiv2;
    ncp_opcq_entry_t entry={0};
    ncp_uint32_t numSent=0;
    int numRemaining = numTasks;
    int currLoopCount;
    ncp_bool_t needPollStateReset = TRUE;
    NCP_TASK_TBR_STATE_PTRS_DECL()

    /* fill in fields that never change */

    entry.cmd = NCP_NCAV3_CMD_ADPAH;
    entry.interruptEn = 1;
    entry.flowControlDisabled = 0;
    entry.taskCompletion = 0;
    entry.destIpcqId = pvtTqsHdl->tqsId;
    entry.returnHeader  = NCP_NCAV3_ADPAH_RCCH_NOOP_REFCNT_KEEP_HDR;
    entry.returnData    = NCP_NCAV3_ADPAH_RCCD_INC_REFCNT;
    entry.quotaTransfer = NCP_NCAV3_ADPAH_MQGC_INC_PCQ;
    entry.quotaIncludeHeader = NCP_NCAV3_ADPAH_MQGI_EXCL_HDR;
    entry.forceCopy = 0;

    if (p_oPCQ->u.opcq_info.sendDoneCnt)
    {
        NCP_TASK_UPDATE_NUM_TX_ENTRIES_AVAIL(pvtTqsHdl, p_oPCQ);
    }
    while(numRemaining)
    {
        do
        {
            if ((numRemaining) <= p_oPCQ->u.opcq_info.numTxAvail)
            {
                currLoopCount = numRemaining;
                break;
            }
            /* update num entries available */
            NCP_TASK_UPDATE_NUM_TX_ENTRIES_AVAIL(pvtTqsHdl, p_oPCQ);
            if (0 == p_oPCQ->u.opcq_info.numTxAvail)
            {
                if (wait)
                {
                    ncp_st_t tmpStatus;

                    if (needPollStateReset)
                    {
                        needPollStateReset = FALSE;
                        NCP_TASK_RESET_POLL_STATE(&pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ0 + p_oPCQ->u.opcq_info.relId]);
                    }
                    if (NCP_ST_SUCCESS != (tmpStatus = NCP_TASK_DO_WAIT(
                            pvtTqsHdl,
                            (&pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ0 + p_oPCQ->u.opcq_info.relId]),
                            myDevHdl,
                            pvtTqsHdl->tqsId)))
                    {
                        ncpStatus = tmpStatus;
                        NCP_JUMP_RETURN();
                    }
                }
                else
                {
                    ncpStatus = NCP_ST_TASK_SEND_QUEUE_FULL;
                    NCP_JUMP_RETURN();
                }
            }
            else
            {
                if ((numRemaining) <= p_oPCQ->u.opcq_info.numTxAvail)
                {
                    currLoopCount = numRemaining;
                }
                else
                {
                    currLoopCount = p_oPCQ->u.opcq_info.numTxAvail;
                }
                break;
            }
        } while(1);

        /* it is *not* ok to preadjust TxAvail count here,  since errors are possible within the loop */
        numRemaining -= currLoopCount;

        while(currLoopCount--)
        {
            ncp_task_send_meta_t currMetadata;

            NCP_TASK_TBR_STATE_PTRS_INIT();
            NCP_TASK_TBR_REFCNT_INC_TASK_STATE_PREFETCH(
                pvtTqsHdl,
                pTasks[numSent],
                p_oPCQ,
                pTbr);

            currMetadata.sendDoneFn = (ncp_task_send_done_fn_t) pFns[numSent];

            /* It is possible for the send done array to be full, so test it early. */
            if (currMetadata.sendDoneFn)
            {
                NCP_CALL(NCP_TASK_ADD_SEND_DONE(pvtTqsHdl,
                                       p_oPCQ->u.opcq_info.relId,
                                       NCP_TASK_TASK_CALLBACK,
                                       currMetadata.sendDoneFn,
                                       pRefCntIncDoneArgs[numSent],
                                       pTasks[numSent],
                                       0, 0));
            }

            NCP_TASK_VALIDATE_OUTPUT_TASK(pvtTqsHdl, pTasks[numSent]);

            /*
             * Set up what will be the contents of the oPCQ entry
             */
            entry.taskAddress = (ncp_uint64_t) pTasks[numSent];

            if ((pTasks[numSent]->ptrCnt <= 2) &&
                (0 == pTasks[numSent]->debugValid))
            {
                entry.headerSize = 0; /* 64BB */
            }
            else
            {
                entry.headerSize = 1; /* 128B */
            }

            entry.headerPool = pTasks[numSent]->headerPool;

            entry.headerPoolMref = pTasks[numSent]->headerPoolMref;

            entry.headerSeparate = !pTasks[numSent]->combinedHeader;

            NCP_TASK_TBR_BUFFER_STATE_UPDATE_MREF(pTbr); /* must be done before pgit update */

            /* FIXME: Create VALIDATE_SHARED_POOL_OUTPUT_TASK that errors
                if task and its PDUs are not shared pool buffers */
            NCP_TASK_PUT_OPCQ(pvtTqsHdl,
                              p_oPCQ,
                              &currMetadata,
                              &entry);

            numSent++;
            p_oPCQ->u.opcq_info.numTxAvail--;

            if (0 == skipBarrierCnt--)
            {
                NCP_TASK_OPCQ_ISSUE_BARRIER_AND_WRITE_PIDX(p_oPCQ);
                skipBarrierCnt = p_oPCQ->nEntriesDiv2;
                barrierIssued = TRUE;
            }
            else
            {
                barrierIssued = FALSE;
            }
        }
    } /* while numRemaining */

NCP_RETURN_LABEL

    if ((barrierIssued == FALSE) && (0 != numSent))
    {
        NCP_TASK_OPCQ_ISSUE_BARRIER_AND_WRITE_PIDX(p_oPCQ);
    }

    *pNumTaskRefsIncremented = numSent;

    return ncpStatus;
}

/* NCP_INLINE */
ncp_st_t
ncp_task_bulk_buffer_refCnt_increment(
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
    ncp_task_pcq_t *p_oPCQ,
    ncp_uint32_t numDescs,
    ncp_task_buffer_desc_t *pDescs,
    ncp_uint32_t *pNumRefsIncremented,
    ncp_task_buffer_refCnt_inc_done_fn_t *pFns,
    void **pRefCntIncDoneArgs,
    ncp_bool_t wait)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_bool_t barrierIssued = FALSE;
    ncp_uint32_t skipBarrierCnt = p_oPCQ->nEntriesDiv2;
    ncp_opcq_entry_t entry={0};
    ncp_uint32_t numSent=0;
    int numRemaining = numDescs;
    int currLoopCount;
    ncp_bool_t needPollStateReset = TRUE;
    NCP_TASK_TBR_STATE_PTRS_DECL()


    /* fill in fields that never change */

    entry.cmd = NCP_NCAV3_CMD_ADPAE;
    entry.interruptEn = 1;
    entry.flowControlDisabled = 0;
    entry.headerSize = 0; /* 64BB */
    entry.taskCompletion = 0;
    entry.headerSeparate = 0;
    entry.destIpcqId = pvtTqsHdl->tqsId;
    entry.returnHeader  = NCP_NCAV3_ADPAE_RCCH_NOOP;
    entry.returnData    = NCP_NCAV3_ADPAE_RCCD_INC_REFCNT;
    entry.quotaTransfer = NCP_NCAV3_ADPAE_MQGC_INC_PCQ;
    entry.quotaIncludeHeader = NCP_NCAV3_ADPAE_MQGI_UNDEF_0;
    entry.forceCopy = 0;

    if (p_oPCQ->u.opcq_info.sendDoneCnt)
    {
        NCP_TASK_UPDATE_NUM_TX_ENTRIES_AVAIL(pvtTqsHdl, p_oPCQ);
    }
    while(numRemaining)
    {
        do
        {
            if ((numRemaining) <= p_oPCQ->u.opcq_info.numTxAvail)
            {
                currLoopCount = numRemaining;
                break;
            }
            /* update num entries available */
            NCP_TASK_UPDATE_NUM_TX_ENTRIES_AVAIL(pvtTqsHdl, p_oPCQ);
            if (0 == p_oPCQ->u.opcq_info.numTxAvail)
            {
                if (wait)
                {
                    ncp_st_t tmpStatus;

                    if (needPollStateReset)
                    {
                        needPollStateReset = FALSE;
                        NCP_TASK_RESET_POLL_STATE(&pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ0 + p_oPCQ->u.opcq_info.relId]);
                    }
                    if (NCP_ST_SUCCESS != (tmpStatus = NCP_TASK_DO_WAIT(
                            pvtTqsHdl,
                            (&pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_SEND_TXQ0 + p_oPCQ->u.opcq_info.relId]),
                            myDevHdl,
                            pvtTqsHdl->tqsId)))
                    {
                        ncpStatus = tmpStatus;
                        NCP_JUMP_RETURN();
                    }
                }
                else
                {
                    ncpStatus = NCP_ST_TASK_SEND_QUEUE_FULL;
                    NCP_JUMP_RETURN();
                }
            }
            else
            {
                if ((numRemaining) <= p_oPCQ->u.opcq_info.numTxAvail)
                {
                    currLoopCount = numRemaining;
                }
                else
                {
                    currLoopCount = p_oPCQ->u.opcq_info.numTxAvail;
                }
                break;
            }
        } while(1);

        /* it is *not* ok to preadjust TxAvail count here,  since errors are possible within the loop */
        numRemaining -= currLoopCount;

        while(currLoopCount--)
        {
            ncp_task_send_meta_t currMetadata;

            NCP_TASK_TBR_STATE_PTRS_INIT();

            NCP_TASK_TBR_INIT_BUFFER_STATES(
                pTbr,
                pvtTqsHdl->pProcess->pid,
                NCP_TASK_TBR_STATE_MULTI_REFS);

            NCP_TASK_TBR_BUFFER_STATE_PREFETCH(
                    pvtTqsHdl,
                    pDescs[numSent].taskBuffer,
                    pDescs[numSent].poolId,
                    pDescs[numSent].mrefBitIsSet,
                    pTbr);

            currMetadata.sendDoneFn = (ncp_task_send_done_fn_t) pFns[numSent];

            /* It is possible for the send done array to be full, so test it early. */
            if (currMetadata.sendDoneFn)
            {
                NCP_CALL(NCP_TASK_ADD_SEND_DONE(pvtTqsHdl,
                                       p_oPCQ->u.opcq_info.relId,
                                       NCP_TASK_BUFFER_CALLBACK,
                                       currMetadata.sendDoneFn,
                                       pRefCntIncDoneArgs[numSent],
                                       pDescs[numSent].taskBuffer,
                                       pDescs[numSent].mrefBitIsSet,
                                       pDescs[numSent].poolId));
            }

            /*
             * Set up what will be the contents of the oPCQ entry
             */
            entry.taskAddress = (ncp_uint64_t) pDescs[numSent].taskBuffer;

            entry.headerPool = pDescs[numSent].poolId;

            NCP_TASKIO_CHECK(((entry.headerPool >= NCP_NCAV3_FIRST_SHARED_POOL_ID) &&
                              (entry.headerPool <= NCP_NCAV3_LAST_SHARED_POOL_ID)),
                            NCP_ST_INVALID_PARAMETER);

            entry.headerPoolMref = pDescs[numSent].mrefBitIsSet;

            NCP_TASK_TBR_BUFFER_STATE_UPDATE_MREF(pTbr); /* must be done before pgit update */

            NCP_TASK_PUT_OPCQ(pvtTqsHdl,
                              p_oPCQ,
                              &currMetadata,
                              &entry);

            numSent++;
            p_oPCQ->u.opcq_info.numTxAvail--;

            if (0 == skipBarrierCnt--)
            {
                NCP_TASK_OPCQ_ISSUE_BARRIER_AND_WRITE_PIDX(p_oPCQ);
                skipBarrierCnt = p_oPCQ->nEntriesDiv2;
                barrierIssued = TRUE;
            }
            else
            {
                barrierIssued = FALSE;
            }
        }
    } /* while numRemaining */

NCP_RETURN_LABEL

    if ((barrierIssued == FALSE) && (0 != numSent))
    {
        NCP_TASK_OPCQ_ISSUE_BARRIER_AND_WRITE_PIDX(p_oPCQ);
    }

    *pNumRefsIncremented = numSent;

    return ncpStatus;
}

ncp_st_t
ncp_task_bulk_cpu_pool_task_free(
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
    ncp_task_pcq_t       *p_oPCQ,
    ncp_uint32_t          numTasks,
    ncp_uint32_t         *pNumFreed,
    ncp_task_free_meta_t *metadata,
    ncp_bool_t            wait)                
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_uint32_t numFreed  = 0;
    ncp_uint32_t numCompletionsToIssue = 0;
    ncp_uint32_t numIssued = 0;
    int numCompleted = 0;
    ncp_task_pool_t *pCpuPool;
    NCP_MUTEX_LOCKED_FLAG_DECL(poolUnlockRequired);
    NCP_MUTEX_LOCKED_FLAG_DECL(txUnlockRequired);     
    NCP_TASK_LOCK_FLAGS(txqLockFlags);         
    NCP_TASK_LOCK_FLAGS(cpuPoolLockFlags);
          
    if (NULL != (pCpuPool = pvtTqsHdl->cpuPoolHdl))
    {    
        if (FALSE == pCpuPool->exclusiveUse)
        {    
            NCP_CALL(NCP_TASK_CLAIM_LOCK_HDL(
                &pCpuPool->poolLock,
                cpuPoolLockFlags,
                &poolUnlockRequired));
        }    
    }
    else
    {
        NCP_CALL(NCP_ST_INTERNAL_ERROR);    
    }
    
    while(numTasks--)
    {
        ncp_task_header_t *thisHeader = metadata->task;
        ncp_bool_t combinedheader = thisHeader->combinedHeader;
       
        if (metadata->issueCompletion)
        {
            NCP_TASKIO_CHECK((FALSE == pvtTqsHdl->pTqs->rxQ.u.ipcq_info.autoCompletionMode),
                             NCP_ST_TASK_RX_QUEUE_IS_AUTOMATIC_COMPLETION);
            
            if ((p_oPCQ->shared) && (!txUnlockRequired))
            {
                NCP_CALL(NCP_TASK_CLAIM_LOCK_HDL(&p_oPCQ->qLock, txqLockFlags, &txUnlockRequired));
            }    
                
            numCompletionsToIssue++;
            
            /* flush completions? */
            
            if (numCompletionsToIssue >= p_oPCQ->u.opcq_info.numTxAvail)
            {    
                /* The only time this should ever fail is when numCompletionsToIssue is 1 and the
                 * oPCQ is full.   Otherewise the numTxAvail guarantees we will be able to 
                 * queue the requests.  Don't free if could not issue completion(s)
                 */
                ncpStatus = ncp_task_bulk_complete(pvtTqsHdl,
                                    p_oPCQ,
                                    numCompletionsToIssue,
                                    &numIssued,
                                    wait); 
                                  
                numCompletionsToIssue = 0;
                if (NCP_ST_SUCCESS != ncpStatus) 
                {
                    break; 
                } 
            }    
            
            numCompleted += numIssued; 
        }   
                                     
        NCP_TASK_VALIDATE_OUTPUT_TASK(pvtTqsHdl, thisHeader);
                
        switch (thisHeader->ptrCnt)
        {
            case 6:
                    ncp_task_CpuPool_free_noLock(
                        pvtTqsHdl,
                        pCpuPool,
                        (void *)(ncp_uintptr_t)thisHeader->pduSegAddr5);
            case 5: 
                    ncp_task_CpuPool_free_noLock(
                        pvtTqsHdl,
                        pCpuPool,
                        (void *)(ncp_uintptr_t)thisHeader->pduSegAddr4);
            case 4:
                    ncp_task_CpuPool_free_noLock(
                        pvtTqsHdl,
                        pCpuPool,
                        (void *)(ncp_uintptr_t)thisHeader->pduSegAddr3);
            case 3: 
                    ncp_task_CpuPool_free_noLock(
                        pvtTqsHdl,
                        pCpuPool,
                        (void *)(ncp_uintptr_t)thisHeader->pduSegAddr2);
            case 2:
                    ncp_task_CpuPool_free_noLock(
                        pvtTqsHdl,
                        pCpuPool,
                        (void *)(ncp_uintptr_t)thisHeader->pduSegAddr1);
            case 1: 
                    ncp_task_CpuPool_free_noLock(
                        pvtTqsHdl,
                            pCpuPool,
                            (void *)(ncp_uintptr_t)thisHeader->pduSegAddr0);
                    if (combinedheader)
                    {
                        NCP_CHECK((FALSE == metadata->freeHeader), 
                            NCP_ST_TASK_HEADER_IS_NOT_SEPARATE);                        
                        break;
                    }            
            case 0:
                    ncp_task_CpuPool_free_noLock(
                        pvtTqsHdl,
                        pCpuPool,
                        thisHeader);
                break;
            default:
                NCP_CALL(NCP_ST_INVALID_PARAMETER);
        }  
 
        /*
         * Issue callback, if requested
         */   
        if (metadata->freeDoneFn)
        {
            (metadata->freeDoneFn)(metadata->freeDoneArg);
        }

        numFreed++;
        metadata++;
                        
    } /* while */

NCP_RETURN_LABEL

    NCP_CLEANUP_MUTEX_CALL(NCP_TASK_FREE_LOCK_HDL(&pCpuPool->poolLock,
                           cpuPoolLockFlags,
                           &poolUnlockRequired));
    
    if (numCompletionsToIssue)
    {    
        ncpStatus = ncp_task_bulk_complete(pvtTqsHdl,
                            p_oPCQ,
                            numCompletionsToIssue,
                            &numIssued,
                            wait); 
        
        numCompleted += numIssued;                          
    }    

    if (numCompleted)
    {    
        pvtTqsHdl->completionsIssued[p_oPCQ->u.opcq_info.relId] += numCompleted;
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_bulk_cpu_pool_task_free_txCompletionInfo,
                              NCP_MSG_DEBUG,
                              "In free: TxQ_%d completions issued incremented by %d, total = 0x%"PRIx64"\r\n",
                              p_oPCQ->u.opcq_info.relId,
                              numCompleted,
                              pvtTqsHdl->completionsIssued[p_oPCQ->u.opcq_info.relId]);
    }

    if (NCP_ST_SUCCESS == ncpStatus)
    {
        NCP_TASK_INC_STAT(pvtTqsHdl->pTqs, api_task_free_ok); 
        NCP_TASK_ADD_TXSTAT(pvtTqsHdl->pTqs, TaskFrees, p_oPCQ->u.opcq_info.relId, numFreed);         
    }        
    else
    {
        NCP_TASK_INC_ERROR_STAT_VIA_PTQSHDL(pvtTqsHdl,  api_task_free_err);      
    }     

    NCP_CLEANUP_MUTEX_CALL(NCP_TASK_FREE_LOCK_HDL(&p_oPCQ->qLock, txqLockFlags, &txUnlockRequired));
            
    /* increment callers count */
    *pNumFreed = numFreed;

    return(ncpStatus);
}
                                              
/* NCP_INLINE */ 
ncp_st_t
ncp_task_bulk_task_free(
                ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
                ncp_task_pcq_t *p_oPCQ,
                ncp_uint32_t numTasks,
                ncp_uint32_t *pNumTasksFreed,
                ncp_task_header_t **pHeaders,
                ncp_bool_t freeHeaders,
                ncp_bool_t issueCompletions,
                ncp_bool_t wait)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    /* ncp_task_tqs_swState_t *pTqs = pvtTqsHdl->pTqs; */
    ncp_bool_t barrierIssued = FALSE;
    int numFreed = 0;
    ncp_uint32_t skipBarrierCnt = p_oPCQ->nEntriesDiv2;     
    ncp_opcq_entry_t entry={0};
    int numRemaining = numTasks;
    int currLoopCount;   
    ncp_bool_t needPollStateReset = TRUE;
    NCP_TASK_TBR_STATE_PTRS_DECL()
          
    /* set fields that never change - optimize for MME shared pool */         
    entry.cmd =  NCP_NCAV3_CMD_ADPAH;
    entry.interruptEn = 1;
    entry.flowControlDisabled = 0;
    entry.quotaIncludeHeader    = NCP_NCAV3_ADPAH_MQGI_INCL_HDR;
    entry.returnData            = NCP_NCAV3_ADPAH_RCCD_DEC_REFCNT;
    entry.quotaTransfer         = NCP_NCAV3_ADPAH_MQGC_DEC_SOURCE;    

    if (freeHeaders)
    {
        entry.returnHeader = NCP_NCAV3_ADPAH_RCCH_DEC_REFCNT_RETURN_HDR;
    }
    else
    {
        entry.returnHeader = NCP_NCAV3_ADPAH_RCCH_NOOP_REFCNT_KEEP_HDR;
    }

    if (issueCompletions)
    {
        entry.taskCompletion = 1;
    }
    else
    {
        entry.taskCompletion = 0;
    }                
                                                
    if (p_oPCQ->u.opcq_info.sendDoneCnt)
    {
        NCP_TASK_UPDATE_NUM_TX_ENTRIES_AVAIL(pvtTqsHdl, p_oPCQ);
    }
    
    while(numRemaining)
    {
        do
        {
            if ((numRemaining) <= p_oPCQ->u.opcq_info.numTxAvail)
            {
                currLoopCount = numRemaining;   
                break;
            }        
            /* update num entries available */
            NCP_TASK_UPDATE_NUM_TX_ENTRIES_AVAIL(pvtTqsHdl, p_oPCQ);
            if (0 == p_oPCQ->u.opcq_info.numTxAvail) 
            {
                
                if (wait)
                { 
                    ncp_st_t tmpStatus;   
                    ncp_task_api_class_t apiClass;

                    /* perf opt: waiting is unlikely,  so moved apiClass init out of data path */
                    if (NULL == pvtTqsHdl->cpuPoolHdl)
                    {
                        apiClass = NCP_TASK_API_CLASS_FREE_TXQ0 + p_oPCQ->u.opcq_info.relId;        
                    } 
                    else
                    {    
                        apiClass = NCP_TASK_API_CLASS_REFILL_TXQ0 + p_oPCQ->u.opcq_info.relId;
                    }
 
                        
                    if (needPollStateReset)
                    {
                        needPollStateReset = FALSE;               
                        NCP_TASK_RESET_POLL_STATE(&pvtTqsHdl->waitProfile[apiClass]);
                    }
                    if (NCP_ST_SUCCESS != (tmpStatus = NCP_TASK_DO_WAIT(
                            pvtTqsHdl,
                            (&pvtTqsHdl->waitProfile[apiClass]),
                            myDevHdl,
                            pvtTqsHdl->tqsId)))
                    {
                        ncpStatus = tmpStatus;
                        NCP_JUMP_RETURN();
                    }            
                }
                else
                {
                    ncpStatus = NCP_ST_TASK_SEND_QUEUE_FULL;
                    NCP_JUMP_RETURN();
                }  
            } 
            else
            {
                if ((numRemaining) <= p_oPCQ->u.opcq_info.numTxAvail)
                {
                    currLoopCount = numRemaining; 
                }                      
                else
                {    
                    currLoopCount = p_oPCQ->u.opcq_info.numTxAvail;                          
                }                    
                break;
            }    
        } while(1);
        
        /* it is *not* ok to preadjust TxAvail count here,  since errors are possible within the loop */
        numRemaining -= currLoopCount;

        while(currLoopCount--) 
        {
             
            
            ncp_task_header_t *thisHeader = pHeaders[numFreed];
            
            NCP_TASK_VALIDATE_OUTPUT_TASK(pvtTqsHdl, thisHeader);
                    
            NCP_TASK_TBR_STATE_PTRS_INIT();
            NCP_TASK_TBR_TXTASK_STATE_PREFETCH(pvtTqsHdl, 
                                             thisHeader, 
                                             freeHeaders, 
                                             TRUE, 
                                             p_oPCQ,
                                             pTbr);
        
            /*
             * Set up what will be the contents of the oPCQ entry
             */
            entry.taskAddress = (ncp_uint64_t) thisHeader;

            entry.headerSeparate = !thisHeader->combinedHeader;

            /* entry.destIpcqId = ?????; */
            if ((thisHeader->ptrCnt <= 2) && (0 == thisHeader->debugValid))
            {
                entry.headerSize = 0; /* 64B */
            }     
            else
            {
                entry.headerSize = 1; /* 128B */
            }                     
                    
            entry.headerPool = thisHeader->headerPool;
            entry.headerPoolMref = thisHeader->headerPoolMref;
                                                
            NCP_TASK_TBR_BUFFER_STATE_UPDATE_MREF(pTbr);  /* must be done before pgit update! */

            NCP_TASK_PUT_OPCQ(pvtTqsHdl,
                              p_oPCQ,
                              NULL,   /* pMetadata */
                              &entry);

            p_oPCQ->u.opcq_info.numTxAvail--;
            
            if (0 == skipBarrierCnt--)
            {
                NCP_TASK_OPCQ_ISSUE_BARRIER_AND_WRITE_PIDX(p_oPCQ);
                skipBarrierCnt = p_oPCQ->nEntriesDiv2;
                barrierIssued = TRUE;
            }
            else
            {
                barrierIssued = FALSE; 
            }       

            numFreed++;
        } /* currLoopCount */
    } /* while numRemaining */ 

NCP_RETURN_LABEL

    if (barrierIssued == FALSE)
    {
        NCP_TASK_OPCQ_ISSUE_BARRIER_AND_WRITE_PIDX(p_oPCQ);
    }

    /* Increment callers count */
    *pNumTasksFreed = numFreed;

    return(ncpStatus);
}

/* NCP_INLINE */ 
ncp_st_t
ncp_task_bulk_task_free_by_metadata(
                ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
                ncp_task_pcq_t *p_oPCQ,
                ncp_uint32_t numTasks,
                ncp_uint32_t *pNumTasksFreed,
                ncp_task_free_meta_t *metadata,
                ncp_bool_t wait)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    /* ncp_task_tqs_swState_t *pTqs = pvtTqsHdl->pTqs; */
    ncp_bool_t barrierIssued = FALSE;
    int numFreed = 0;
    int numCompleted = 0;
    ncp_uint32_t skipBarrierCnt = p_oPCQ->nEntriesDiv2;     
    opcq_entry_overlay_t *pEntry = (opcq_entry_overlay_t *)p_oPCQ->u.opcq_info.pOPCQentry;
    ncp_task_free_meta_t *pCurrMetadata = metadata;
    opcq_entry_overlay_t savedEntryVal;   
    int numRemaining = numTasks;
    int currLoopCount;   
    ncp_bool_t needPollStateReset = TRUE;
    NCP_MUTEX_LOCKED_FLAG_DECL(unlockRequired);     
    NCP_TASK_TBR_STATE_PTRS_DECL()
    NCP_TASK_LOCK_FLAGS(txqLockFlags);         

    if (p_oPCQ->shared)
    {
        NCP_CALL(NCP_TASK_CLAIM_LOCK_HDL(&p_oPCQ->qLock, txqLockFlags, &unlockRequired));
    }    
    
   /* fill in fields that never change, and save a copy of the dword containing them */
    savedEntryVal.u.opcqDword[1] = 0;
    savedEntryVal.u.opcqEntry.cmd = NCP_NCAV3_CMD_ADPAH;
    savedEntryVal.u.opcqEntry.cmd =  NCP_NCAV3_CMD_ADPAH;
    savedEntryVal.u.opcqEntry.interruptEn = 1;
    savedEntryVal.u.opcqEntry.flowControlDisabled = 0;
    /* savedEntryVal.quotaIncludeHeader    = NCP_NCAV3_ADPAH_MQGI_INCL_HDR; */ /* already zero */
    /* savedEntryVal.u.opcqEntry.returnHeader =   NCP_NCAV3_ADPAH_RCCH_DEC_REFCNT_RETURN_HDR;  */ /* already zero */
    savedEntryVal.u.opcqEntry.returnData     = NCP_NCAV3_ADPAH_RCCD_DEC_REFCNT;
    savedEntryVal.u.opcqEntry.quotaTransfer  = NCP_NCAV3_ADPAH_MQGC_DEC_SOURCE;    
                                                
    if (p_oPCQ->u.opcq_info.sendDoneCnt)
    {
        NCP_TASK_UPDATE_NUM_TX_ENTRIES_AVAIL(pvtTqsHdl, p_oPCQ);
    }

    while(numRemaining)
    {
        int tmpSent;
        
        do
        {
            if ((numRemaining) <= p_oPCQ->u.opcq_info.numTxAvail)
            {
                currLoopCount = numRemaining;   
                break;
            } 
                   
            /* update num entries available */
            NCP_TASK_UPDATE_NUM_TX_ENTRIES_AVAIL(pvtTqsHdl, p_oPCQ);
            if (0 == p_oPCQ->u.opcq_info.numTxAvail) 
            {
                
                if (wait)
                { 
                    ncp_st_t tmpStatus;   
                    ncp_task_api_class_t apiClass;

                    /* perf opt: waiting is unlikely,  so moved apiClass init out of data path */
                    if (NULL == pvtTqsHdl->cpuPoolHdl)
                    {
                        apiClass = NCP_TASK_API_CLASS_FREE_TXQ0 + p_oPCQ->u.opcq_info.relId;        
                    }
                    else
                    {    
                        apiClass = NCP_TASK_API_CLASS_REFILL_TXQ0 + p_oPCQ->u.opcq_info.relId;
                    }

                    if (needPollStateReset)
                    {
                        needPollStateReset = FALSE;               
                        NCP_TASK_RESET_POLL_STATE(&pvtTqsHdl->waitProfile[apiClass]);
                    }
                    if (NCP_ST_SUCCESS != (tmpStatus = NCP_TASK_DO_WAIT(
                            pvtTqsHdl,
                            (&pvtTqsHdl->waitProfile[apiClass]),
                            myDevHdl,
                            pvtTqsHdl->tqsId)))
                    {
                        ncpStatus = tmpStatus;
                        NCP_JUMP_RETURN();
                    }            
                }
                else
                {
                    ncpStatus = NCP_ST_TASK_SEND_QUEUE_FULL;
                    NCP_JUMP_RETURN();
                }  
            } 
            else
            {
                if ((numRemaining) <= p_oPCQ->u.opcq_info.numTxAvail)
                {
                    currLoopCount = numRemaining; 
                }                      
                else
                {    
                    currLoopCount = p_oPCQ->u.opcq_info.numTxAvail;                          
                }                    
                break;
            }    
        } while(1);
        
        /* it is *not* ok to preadjust TxAvail count here,  since errors are possible within the loop */
        tmpSent = 0;
        numRemaining -= currLoopCount;

        while(currLoopCount--) 
        {
             
            ncp_task_header_t *thisHeader = pCurrMetadata->task;
            
            /* It is possible for the send done array to be full, so test it early. */
            if (pCurrMetadata->freeDoneFn)
            {
                 if (NCP_ST_SUCCESS != (ncpStatus = NCP_TASK_ADD_SEND_DONE(pvtTqsHdl,
                                       p_oPCQ->u.opcq_info.relId,
                                       NCP_TASK_TASK_CALLBACK,
                                       pCurrMetadata->freeDoneFn,
                                       pCurrMetadata->freeDoneArg,
                                       0, 0, 0)))
                 {
                    /* update state before erroring out */                  
                    numFreed += tmpSent;
                    p_oPCQ->u.opcq_info.numTxAvail -= tmpSent;
                    NCP_TASK_OPCQ_ISSUE_BARRIER_AND_WRITE_PIDX(p_oPCQ); 
                    NCP_CALL(ncpStatus);
                 }                                            
            }
                        
            NCP_TASK_VALIDATE_OUTPUT_TASK(pvtTqsHdl, thisHeader);
                    
            NCP_TASK_TBR_STATE_PTRS_INIT();
            NCP_TASK_TBR_TXTASK_STATE_PREFETCH(pvtTqsHdl, 
                                             thisHeader, 
                                             pCurrMetadata->freeHeader,
                                             TRUE, 
                                             p_oPCQ,
                                             pTbr);
        
            /*
             * Set up what will be the contents of the oPCQ entry
             */
            pEntry->u.opcqDword[1] = savedEntryVal.u.opcqDword[1];
            pEntry->u.opcqEntry.taskAddress = (ncp_uint64_t) thisHeader; 
            
            /* pEntry->u.opcqEntry.returnHeader = NCP_NCAV3_ADPAH_RCCH_DEC_REFCNT_RETURN_HDR; */ /* already one */
            if (!pCurrMetadata->freeHeader)
            {
                NCP_CHECK((FALSE == thisHeader->combinedHeader), 
                        NCP_ST_TASK_HEADER_IS_NOT_SEPARATE);
                pEntry->u.opcqEntry.returnHeader        = NCP_NCAV3_ADPAH_RCCH_NOOP_REFCNT_KEEP_HDR;
                pEntry->u.opcqEntry.quotaIncludeHeader  = NCP_NCAV3_ADPAH_MQGI_EXCL_HDR;
            }
            
            /* pEntry->u.opcqEntry.taskCompletion = 0; */ /* already zero */
            if (pCurrMetadata->issueCompletion)
            {
                NCP_TASKIO_CHECK((FALSE == pvtTqsHdl->pTqs->rxQ.u.ipcq_info.autoCompletionMode),
                             NCP_ST_TASK_RX_QUEUE_IS_AUTOMATIC_COMPLETION);                
                NCP_TASKIO_CHECK(1 <= pvtTqsHdl->completionsOwed,
                             NCP_ST_TASK_TOO_MANY_TASK_COMPLETIONS);
                pEntry->u.opcqEntry.taskCompletion = 1;
                numCompleted++;
            }
                 
            pEntry->u.opcqEntry.headerSeparate = !thisHeader->combinedHeader;

            /* pEntry->u.opcqEntry.destIpcqId = ?????; */
            
            /* pEntry->u.opcqEntry.headerSize = 0; */ /* already 0 -> 64B */
            if ((thisHeader->ptrCnt > 2) || (1 == thisHeader->debugValid))
            {
                pEntry->u.opcqEntry.headerSize = 1; /* 128B */
            }                     
                    
            pEntry->u.opcqEntry.headerPool = thisHeader->headerPool;
            pEntry->u.opcqEntry.headerPoolMref = thisHeader->headerPoolMref;

            NCP_TASK_TBR_BUFFER_STATE_UPDATE_MREF(pTbr);  /* must be done before pgit update! */

            if (pCurrMetadata->freeDoneFn)
            {
                NCP_TASK_FILL_PER_OPCQ_AUX_DATA(pvtTqsHdl, 
                                                p_oPCQ);               
            }
            else 
            {
                NCP_TASK_FILL_PER_OPCQ_AUX_DATA(NULL, 
                                                p_oPCQ);                
            }                 

            NCP_TASK_OPCQ_UPDATE_CACHED_PIDX(p_oPCQ);

            if (0 == skipBarrierCnt--)
            {
                NCP_TASK_OPCQ_ISSUE_BARRIER_AND_WRITE_PIDX(p_oPCQ);
                skipBarrierCnt = p_oPCQ->nEntriesDiv2;
                barrierIssued = TRUE;
            }
            else
            {
                barrierIssued = FALSE; 
            }       
            tmpSent++;
            pCurrMetadata++;
            pEntry = (opcq_entry_overlay_t *)p_oPCQ->u.opcq_info.pOPCQentry;
        } /* currLoopCount */
        
        numFreed += tmpSent;
        p_oPCQ->u.opcq_info.numTxAvail -= tmpSent;
        
    } /* while numRemaining */ 

NCP_RETURN_LABEL

    if (barrierIssued == FALSE)
    {
        NCP_TASK_OPCQ_ISSUE_BARRIER_AND_WRITE_PIDX(p_oPCQ);
    }

    if (numCompleted)
    {
        pvtTqsHdl->completionsIssued[p_oPCQ->u.opcq_info.relId] += numCompleted;
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_bulk_task_free_by_metadata_txCompletionInfo,
                              NCP_MSG_DEBUG,
                              "In free: TxQ_%d completions issued incremented by %d, total = 0x%"PRIx64"\r\n",
                              p_oPCQ->u.opcq_info.relId,
                              numCompleted,
                              pvtTqsHdl->completionsIssued[p_oPCQ->u.opcq_info.relId]);
    }

    if (NCP_ST_SUCCESS == ncpStatus)
    {
        NCP_TASK_INC_STAT(pvtTqsHdl->pTqs, api_task_free_ok); 
        NCP_TASK_ADD_TXSTAT(pvtTqsHdl->pTqs, TaskFrees, p_oPCQ->u.opcq_info.relId, numFreed);         
    }        
    else
    {
        NCP_TASK_INC_ERROR_STAT_VIA_PTQSHDL(pvtTqsHdl,  api_task_free_err);      
    }     

    NCP_CLEANUP_MUTEX_CALL(NCP_TASK_FREE_LOCK_HDL(&p_oPCQ->qLock, txqLockFlags, &unlockRequired));
        
    /* Increment callers count */
    *pNumTasksFreed = numFreed;

    return(ncpStatus);
}

ncp_st_t
ncp_task_bulk_buffer_alloc_cpu_pool(
    ncp_task_pvt_tqsHdl_data_t  *pvtTqsHdl,  
    ncp_task_pool_t             *pPool,
    void                       **taskBuffers,
    ncp_uint32_t                *taskBufferSizes,
    ncp_uint32_t                 numTaskBuffers,
    ncp_uint32_t                *numTaskBuffersAllocated)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    NCP_MUTEX_LOCKED_FLAG_DECL(unlockRequired);
    int i;
    int numAllocated=0;
    NCP_TASK_LOCK_FLAGS(flags);

    if (!pPool->exclusiveUse)
    {
        NCP_CALL(NCP_TASK_CLAIM_LOCK_HDL(&pPool->poolLock, flags, &unlockRequired));
    }

    *numTaskBuffersAllocated = 0;
    for (i = 0; i < numTaskBuffers; i++)
    {

        ncpStatus = ncp_task_CpuPool_alloc_noLock(
                            pvtTqsHdl,
                            pPool,
                            taskBufferSizes[i],
                            &(taskBuffers[i]));

        if (ncpStatus != NCP_ST_SUCCESS)
        {
            if (*numTaskBuffersAllocated > 0)
            {
                NCP_RETURN(NCP_ST_SUCCESS);
            }
            else
            {
                NCP_CALL(ncpStatus);
            }
        }

        numAllocated++;
    }

NCP_RETURN_LABEL

    NCP_CLEANUP_MUTEX_CALL(NCP_TASK_FREE_LOCK_HDL(&pPool->poolLock, flags, &unlockRequired));

    *numTaskBuffersAllocated = numAllocated;

    return(ncpStatus);
}

/* TODO - the actual mPCQ dequeue logic is very similar to the iPCQ dequeue logic - combine them? */



ncp_st_t
_ncp_task_buffer_size_get(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl, 
                          ncp_uint8_t poolId, 
                          ncp_uintptr_t pBuffer,  
                          ncp_uint32_t *pBufferSize)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_pool_t *pPool;
    
    if (NCP_TASK_CPU_POOL_ALIAS == poolId)
    {
        poolId = pvtTqsHdl->cpuPoolId;
    }        
    pPool = &pNcpTaskSwState->taskPools[poolId];
    if ((pBuffer >= pPool->blocksVA[0]) && (pBuffer < pPool->blocksVAend[0]))
    {
        *pBufferSize = 256;
    }        
    else if ((pBuffer >= pPool->blocksVA[1]) && (pBuffer < pPool->blocksVAend[1]))
    {
        *pBufferSize = (2*1024);        
    }   
    else if ((pBuffer >= pPool->blocksVA[2]) && (pBuffer < pPool->blocksVAend[2]))
    {
        *pBufferSize = (16*1024);         
    }   
    else if ((pBuffer >= pPool->blocksVA[3]) && (pBuffer < pPool->blocksVAend[3]))
    {
        *pBufferSize = (64*1024);         
    } 
    else
    {
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_buffer_size_get_invalidBuffer,
                              NCP_MSG_ERROR, "Invalid buffer %p\r\n",
                              (void *)pBuffer);
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_buffer_size_get_pool, NCP_MSG_ERROR,
                              "pool=%d\r\n", (int)pPool->poolId);
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_buffer_size_get_blocksVAStartEnd,
                              NCP_MSG_ERROR, "blocksVA[%d] start=%p, end=%p\r\n",
                              0, (void *)pPool->blocksVA[0], (void *)pPool->blocksVAend[0]);
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_buffer_size_get_blocksVAStartEnd,
                              NCP_MSG_ERROR, "blocksVA[%d] start=%p, end=%p\r\n",
                              1, (void *)pPool->blocksVA[1], (void *)pPool->blocksVAend[1]);
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_buffer_size_get_blocksVAStartEnd,
                              NCP_MSG_ERROR, "blocksVA[%d] start=%p, end=%p\r\n",
                              2, (void *)pPool->blocksVA[2], (void *)pPool->blocksVAend[2]);
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_buffer_size_get_blocksVAStartEnd,
                              NCP_MSG_ERROR, "blocksVA[%d] start=%p, end=%p\r\n",
                              3, (void *)pPool->blocksVA[3], (void *)pPool->blocksVAend[3]);
        NCP_CALL(NCP_ST_TASK_INVALID_BUFFER);
    }

NCP_RETURN_LABEL
    return(ncpStatus);
}  

ncp_st_t
_ncp_task_buffer_pool_get(
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
    void *pBuffer,
    ncp_uint8_t *pBufferPoolId)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    int poolId;
    ncp_task_tqs_swState_t *pTqs = pvtTqsHdl->pTqs;        

    if (pvtTqsHdl->cpuPoolHdl)
    {
        if (((ncp_uintptr_t)pBuffer >= pvtTqsHdl->cpuPoolHdl->poolVA) 
            && ((ncp_uintptr_t)pBuffer <= pvtTqsHdl->cpuPoolHdl->poolVAEnd))
        {
            *pBufferPoolId = NCP_TASK_CPU_POOL_ALIAS;
            NCP_JUMP_RETURN();    
        }    
    }        
    else for (poolId=NCP_TASK_FIXED_POOL_ENCODED_ID; /* fixed pool is encoded as 1 */
              poolId < NCP_NCAV3_MAX_SHARED_POOLS; 
              poolId++)
    {
        if (pTqs->validPoolsMask & (1<<poolId))
        {
            if (((ncp_uintptr_t)pBuffer >= pNcpTaskSwState->taskPools[poolId].poolVA) 
                && ((ncp_uintptr_t)pBuffer <= pNcpTaskSwState->taskPools[poolId].poolVAEnd))
            {
                *pBufferPoolId = poolId;
                NCP_JUMP_RETURN();    
            }    
        }
    }
    NCP_CALL(NCP_ST_TASK_INVALID_BUFFER);

NCP_RETURN_LABEL

    return(ncpStatus);
}    

ncp_st_t
_ncp_task_buffer_address_validate(
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
    void *pBuffer,
    ncp_uint8_t poolId)
{
    ncp_st_t ncpStatus = NCP_ST_TASK_INVALID_BUFFER;
    ncp_task_tqs_swState_t *pTqs = pvtTqsHdl->pTqs;

    if (pvtTqsHdl->cpuPoolHdl)
    {
        if (((ncp_uintptr_t)pBuffer >= pvtTqsHdl->cpuPoolHdl->poolVA)
            && ((ncp_uintptr_t)pBuffer <= pvtTqsHdl->cpuPoolHdl->poolVAEnd))
        {
            ncpStatus = NCP_ST_SUCCESS;
        }
    }
    else
    {
        if (pTqs->validPoolsMask & (1<<poolId))
        {
            if (((ncp_uintptr_t)pBuffer >= pNcpTaskSwState->taskPools[poolId].poolVA)
                && ((ncp_uintptr_t)pBuffer <= pNcpTaskSwState->taskPools[poolId].poolVAEnd))
            {
                ncpStatus = NCP_ST_SUCCESS;
            }
        }
    }

NCP_RETURN_LABEL

    return ncpStatus;
}
    
ncp_st_t
_ncp_task_buffer_size_and_start_get(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl, 
                          ncp_uint8_t poolId, 
                          ncp_uintptr_t pBuffer,  
                          ncp_uint32_t *pBufferSize,
                          void **pBufferStart)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_pool_t *pPool;
    
    if (NCP_TASK_CPU_POOL_ALIAS == poolId)
    {
        poolId = pvtTqsHdl->cpuPoolId;
    }        
    pPool = &pNcpTaskSwState->taskPools[poolId];
    if ((pBuffer >= pPool->blocksVA[0]) && (pBuffer < pPool->blocksVAend[0]))
    {
        *pBufferSize = 256;
        *pBufferStart = (void *)(ncp_uintptr_t)(pBuffer & ~(256-1));
    }        
    else if ((pBuffer >= pPool->blocksVA[1]) && (pBuffer < pPool->blocksVAend[1]))
    {
        *pBufferSize = (2*1024); 
        *pBufferStart = (void *)(ncp_uintptr_t)(pBuffer & ~((2*1024)-1));       
    }   
    else if ((pBuffer >= pPool->blocksVA[2]) && (pBuffer < pPool->blocksVAend[2]))
    {
        *pBufferSize = (16*1024);  
        *pBufferStart = (void *)(ncp_uintptr_t)(pBuffer & ~((16*1024)-1));               
    }   
    else if ((pBuffer >= pPool->blocksVA[3]) && (pBuffer < pPool->blocksVAend[3]))
    {
        *pBufferSize = (64*1024); 
        *pBufferStart = (void *)(ncp_uintptr_t)(pBuffer & ~((64*1024)-1));                
    } 
    else
    {
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_buffer_size_and_start_get_invalidBuffer,
                              NCP_MSG_ERROR, "Invalid buffer %p\r\n",
                              (void *)pBuffer);
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_buffer_size_and_start_get_pool,
                              NCP_MSG_ERROR, "pool=%d\r\n", (int)pPool->poolId);
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_buffer_size_and_start_get_blocksVAStartEnd,
                              NCP_MSG_ERROR,
                              "blocksVA[%d] start=%p, end=%p\r\n",
                              0, (void *)pPool->blocksVA[0], (void *)pPool->blocksVAend[0]);
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_buffer_size_and_start_get_blocksVAStartEnd,
                              NCP_MSG_ERROR,
                              "blocksVA[%d] start=%p, end=%p\r\n",
                              1, (void *)pPool->blocksVA[1], (void *)pPool->blocksVAend[1]);
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_buffer_size_and_start_get_blocksVAStartEnd,
                              NCP_MSG_ERROR,
                              "blocksVA[%d] start=%p, end=%p\r\n",
                              2, (void *)pPool->blocksVA[2], (void *)pPool->blocksVAend[2]);
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_buffer_size_and_start_get_blocksVAStartEnd,
                              NCP_MSG_ERROR,
                              "blocksVA[%d] start=%p, end=%p\r\n",
                              3, (void *)pPool->blocksVA[3], (void *)pPool->blocksVAend[3]);
        NCP_CALL(NCP_ST_TASK_INVALID_BUFFER);
    }

NCP_RETURN_LABEL
    return(ncpStatus);
}   


ncp_st_t
ncp_ncav3_get_queue_profile_from_name(
    ncp_task_resource_name_t       *name,
    ncp_ncav3_nca_queue_profile_t **queueProfile)
{
    ncp_st_t ncpStatus = NCP_ST_ERROR;
    ncp_ncav3_task_receive_queue_config_t *config;
    ncp_ncav3_nca_queue_profile_t *profiles;
    ncp_int32_t                    numProfiles;
    int i;

    config = &pNcpTaskSwState->nca->configInfo.taskReceiveQueues;

    profiles = config->queueProfiles;
    numProfiles = config->numProfiles;

    NCP_ASSERT(name != NULL, NCP_ST_INTERNAL_ERROR);
    NCP_ASSERT(profiles != NULL, NCP_ST_INTERNAL_ERROR);
    NCP_ASSERT(queueProfile != NULL, NCP_ST_INTERNAL_ERROR);

    for (i = 0; i < numProfiles; i++)
    {
        if (strncmp(profiles[i].name.name,
                    name->name,
                    sizeof(ncp_task_resource_name_t)) == 0)
        {
            *queueProfile = &profiles[i];
            NCP_RETURN(NCP_ST_SUCCESS);
        }
    }

NCP_RETURN_LABEL

    return ncpStatus;
}

