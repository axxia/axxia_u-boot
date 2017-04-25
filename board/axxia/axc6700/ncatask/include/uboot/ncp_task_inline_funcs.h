/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2017, Intel Corporation.                        *
 **                                                                       *
 **************************************************************************/


#ifndef __ncp_task_inline_funcs__
#define __ncp_task_inline_funcs__

#include <common.h>
#include "uboot/arm64/ncp_sal_memory.h"
#include "uboot/arm64/ncp_sal_barrier.h"


#if (1 == NCP_TASK_TBR_ENABLED)

NCP_INLINE  ncp_st_t
ncp_task_tbr_buffer_state_prefetch(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl, 
                                   ncp_uint64_t pBuffer, 
                                   ncp_uint8_t poolId, 
                                   ncp_bool_t  mrefBit,
                                   ncp_task_tbr_params_t *pTbr)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_pool_t *pPool;
    ncp_task_pid_t *tbrArray;
    ncp_uint64_t tbrOffset = pBuffer;
	debug("ML offset %llx\n", tbrOffset); 
    pPool = &pNcpTaskSwState->taskPools[poolId];
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
                              ncp_xlf_task_tbr_buffer_state_prefetch_invalidBuffer,
                              NCP_MSG_ERROR, "TBR: Invalid buffer %p\r\n",
                              (void *)pBuffer);
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_tbr_buffer_state_prefetch_pool,
                              NCP_MSG_ERROR, "pool=%d\r\n",
                              (int) pPool->poolId);
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_tbr_buffer_state_prefetch_blocksVAStartEnd,
                              NCP_MSG_ERROR, "blocksVA[%d] start=%p, end=%p\r\n",
                              0, (void *)pPool->blocksVA[0], (void *)pPool->blocksVAend[0]);
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_tbr_buffer_state_prefetch_blocksVAStartEnd,
                              NCP_MSG_ERROR, "blocksVA[%d] start=%p, end=%p\r\n",
                              1, (void *)pPool->blocksVA[1], (void *)pPool->blocksVAend[1]);
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_tbr_buffer_state_prefetch_blocksVAStartEnd,
                              NCP_MSG_ERROR, "blocksVA[%d] start=%p, end=%p\r\n",
                              2, (void *)pPool->blocksVA[2], (void *)pPool->blocksVAend[2]);
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_tbr_buffer_state_prefetch_blocksVAStartEnd,
                              NCP_MSG_ERROR, "blocksVA[%d] start=%p, end=%p\r\n",
                              3, (void *)pPool->blocksVA[3], (void *)pPool->blocksVAend[3]);
        NCP_CALL(NCP_ST_TASK_TBR_INVALID_BUFFER);
    }

    /* Prefetch the cache line and update array metrics for buffs to be modified in stage2 */
    arch_prefetch_data_for_write((void *)tbrArray);
    *(pTbr->pPtrs)++ = (void *)tbrArray;
    pTbr->mrefBitArray[pTbr->ptrCnt] = mrefBit;
    pTbr->ptrCnt += 1;

NCP_RETURN_LABEL
    return(ncpStatus);
}     

NCP_INLINE  ncp_st_t
ncp_task_tbr_cpu_pool_buffer_state_prefetch(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
                                          ncp_uint64_t pBuffer, 
                                          ncp_uint8_t poolID,
                                          ncp_task_pool_t *pPool,
                                          ncp_task_tbr_params_t *pTbr) 
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_pid_t *tbrArray;
    ncp_uint64_t tbrOffset = pBuffer;

    /* Application profiles can enable both a CPU pool and the fixed pool, so
     * ignore buffers from the fixed pool.
     */
    if (poolID != NCP_TASK_CPU_POOL_ALIAS)
    {
        NCP_RETURN(NCP_ST_SUCCESS);
    }

    pTbr->mrefBitArray[pTbr->ptrCnt] = 0;

    if ((tbrOffset >= pPool->blocksVA[0]) && (tbrOffset < pPool->blocksVAend[0]))
    {
        /* 256B - normalize and convert to buffer number (0..last) */
        tbrOffset -= pPool->blocksVA[0];
        /* convert to offset */        
        tbrOffset = (tbrOffset & ~(256-1)) >> 7;
        tbrArray = (ncp_task_pid_t *)(ncp_uintptr_t)
            (((ncp_uintptr_t)pPool->pTbrArray[0]) + tbrOffset); /* Assumes 16 bit PID! */

        /* Prefetch the cache line and update array metrics for buffs to be modified in stage2 */
        arch_prefetch_data_for_write((void *)tbrArray);
        *(pTbr->pPtrs)++ = (void *)tbrArray;
        pTbr->ptrCnt += 1;            
        
        if (NCP_TASK_TBR_STATE_NCA_OWNED == pTbr->expectedState)
        {
            pvtTqsHdl->perHdlRefillsOwed[0]++;
        }
        else if (NCP_TASK_TBR_STATE_NCA_OWNED == pTbr->newState)
        {
            pTbr->pRefillsIssued[0]++; /* separate accounting for TXQ0 and TXQ1 */
        }             
    }        
    else if ((tbrOffset >= pPool->blocksVA[1]) && (tbrOffset < pPool->blocksVAend[1]))
    {
        /* 2K - normalize and convert to buffer number (0..last) */
        tbrOffset -= pPool->blocksVA[1];  
        /* convert to offset */             
        tbrOffset = (tbrOffset & ~((2*1024)-1)) >> 10;
        tbrArray = (ncp_task_pid_t *)(ncp_uintptr_t)
            (((ncp_uintptr_t)pPool->pTbrArray[1]) + tbrOffset); /* Assumes 16 bit PID! */
        
        /* Prefetch the cache line and update array metrics for buffs to be modified in stage2 */        
        arch_prefetch_data_for_write((void *)tbrArray);
        *(pTbr->pPtrs)++ = (void *)tbrArray;
        pTbr->ptrCnt += 1;   
                   
        if (NCP_TASK_TBR_STATE_NCA_OWNED == pTbr->expectedState)
        {
            pvtTqsHdl->perHdlRefillsOwed[1]++;
        }
        else if (NCP_TASK_TBR_STATE_NCA_OWNED == pTbr->newState)
        {
            pTbr->pRefillsIssued[1]++; /* separate accounting for TXQ0 and TXQ1 */
        }              
    }   
    else if ((tbrOffset >= pPool->blocksVA[2]) && (tbrOffset < pPool->blocksVAend[2]))
    {
        /* 16K - normalize and convert to buffer number (0..last) */
        tbrOffset -= pPool->blocksVA[2];
        /* convert to offset */        
        tbrOffset = (tbrOffset & ~((16*1024)-1)) >> 13;       
        tbrArray = (ncp_task_pid_t *)(ncp_uintptr_t)
            (((ncp_uintptr_t)pPool->pTbrArray[2]) + tbrOffset); /* Assumes 16 bit PID! */
        
        /* Prefetch the cache line and update array metrics for buffs to be modified in stage2 */            
        arch_prefetch_data_for_write((void *)tbrArray);
        *(pTbr->pPtrs)++ = (void *)tbrArray;
        pTbr->ptrCnt += 1; 
                     
        if (NCP_TASK_TBR_STATE_NCA_OWNED == pTbr->expectedState)
        {
            pvtTqsHdl->perHdlRefillsOwed[2]++;
        }
        else if (NCP_TASK_TBR_STATE_NCA_OWNED == pTbr->newState)
        {
            pTbr->pRefillsIssued[2]++; /* separate accounting for TXQ0 and TXQ1 */
        }              
    }   
    else if ((tbrOffset >= pPool->blocksVA[3]) && (tbrOffset < pPool->blocksVAend[3]))
    {
        /* 64K - normalize and convert to buffer number (0..last) */
        tbrOffset -= pPool->blocksVA[3];
        /* convert to offset */
        tbrOffset = (tbrOffset & ~((64*1024)-1)) >> 15;       
        tbrArray = (ncp_task_pid_t *)(ncp_uintptr_t)
            (((ncp_uintptr_t)pPool->pTbrArray[3]) + tbrOffset); /* Assumes 16 bit PID! */
        
        /* Prefetch the cache line and update array metrics for buffs to be modified in stage2 */            
        arch_prefetch_data_for_write((void *)tbrArray);
        *(pTbr->pPtrs)++ = (void *)tbrArray;
        pTbr->ptrCnt += 1; 
         
        if (NCP_TASK_TBR_STATE_NCA_OWNED == pTbr->expectedState)
        {
            pvtTqsHdl->perHdlRefillsOwed[3]++;
        }
        else if (NCP_TASK_TBR_STATE_NCA_OWNED == pTbr->newState)
        {
            pTbr->pRefillsIssued[3]++; /* separate accounting for TXQ0 and TXQ1 */
        }           
    } 
    else
    {
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_tbr_cpu_pool_buffer_state_prefetch_invalidBuffer,
                              NCP_MSG_ERROR, "TBR: Invalid buffer %p\r\n",
                              (void *)pBuffer);
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_tbr_cpu_pool_buffer_state_prefetch_pool,
                              NCP_MSG_ERROR, "pool=%d\r\n",
                              (int) pPool->poolId);
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_tbr_cpu_pool_buffer_state_prefetch_blocksVAStartEnd,
                              NCP_MSG_ERROR, "blocksVA[%d] start=%p, end=%p\r\n",
                              0, (void *)pPool->blocksVA[0], (void *)pPool->blocksVAend[0]);
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_tbr_cpu_pool_buffer_state_prefetch_blocksVAStartEnd,
                              NCP_MSG_ERROR, "blocksVA[%d] start=%p, end=%p\r\n",
                              1, (void *)pPool->blocksVA[1], (void *)pPool->blocksVAend[1]);
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_tbr_cpu_pool_buffer_state_prefetch_blocksVAStartEnd,
                              NCP_MSG_ERROR, "blocksVA[%d] start=%p, end=%p\r\n",
                              2, (void *)pPool->blocksVA[2], (void *)pPool->blocksVAend[2]);
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_tbr_cpu_pool_buffer_state_prefetch_blocksVAStartEnd,
                              NCP_MSG_ERROR, "blocksVA[%d] start=%p, end=%p\r\n",
                              3, (void *)pPool->blocksVA[3], (void *)pPool->blocksVAend[3]);
        NCP_CALL(NCP_ST_TASK_TBR_INVALID_BUFFER);
    }

NCP_RETURN_LABEL
    return(ncpStatus);
} 

NCP_INLINE ncp_st_t
ncp_task_tbr_task_state_prefetch(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
                               ncp_task_header_t *pTaskHeader, 
                               ncp_bool_t freeHeader,
                               ncp_bool_t freeBuffer,
                               ncp_task_tbr_params_t *pTbr)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    if (freeBuffer)
    {  
        /* optimize for most common cases, before entering switch */ 
        if (1 == pTaskHeader->ptrCnt)
        {    
            NCP_TASK_TBR_BUFFER_STATE_PREFETCH(
                pvtTqsHdl,
                pTaskHeader->pduSegAddr0,
                pTaskHeader->pool0,
                pTaskHeader->pool0Mref,
                pTbr);
            if ((0 == pTaskHeader->combinedHeader) && (freeHeader))
            {    
                NCP_TASK_TBR_BUFFER_STATE_PREFETCH(
                    pvtTqsHdl,
                    pTaskHeader,
                    pTaskHeader->headerPool,
                    pTaskHeader->headerPoolMref,
                    pTbr);
            }
        }
        else if (0 == pTaskHeader->ptrCnt)
        {
            if ((0 == pTaskHeader->combinedHeader) && (freeHeader))
            {    
                NCP_TASK_TBR_BUFFER_STATE_PREFETCH(
                    pvtTqsHdl,
                    pTaskHeader,
                    pTaskHeader->headerPool,
                    pTaskHeader->headerPoolMref,
                    pTbr);
            }      
        }            
        else switch(pTaskHeader->ptrCnt)
        {
            case 6:
                NCP_TASK_TBR_BUFFER_STATE_PREFETCH(
                    pvtTqsHdl,
                    pTaskHeader->pduSegAddr5,
                    pTaskHeader->pool5,
                    pTaskHeader->pool5Mref,
                    pTbr);
            case 5:
                NCP_TASK_TBR_BUFFER_STATE_PREFETCH(
                    pvtTqsHdl,
                    pTaskHeader->pduSegAddr4,
                    pTaskHeader->pool4,
                    pTaskHeader->pool4Mref,
                    pTbr);
            case 4:
                NCP_TASK_TBR_BUFFER_STATE_PREFETCH(
                    pvtTqsHdl,
                    pTaskHeader->pduSegAddr3,
                    pTaskHeader->pool3,
                    pTaskHeader->pool3Mref,
                    pTbr);
            case 3:
                NCP_TASK_TBR_BUFFER_STATE_PREFETCH(
                    pvtTqsHdl,
                    pTaskHeader->pduSegAddr2,
                    pTaskHeader->pool2,
                    pTaskHeader->pool2Mref,
                    pTbr);
            case 2:
                NCP_TASK_TBR_BUFFER_STATE_PREFETCH(
                    pvtTqsHdl,
                    pTaskHeader->pduSegAddr1,
                    pTaskHeader->pool1,
                    pTaskHeader->pool1Mref,
                    pTbr);
            case 1: 
                NCP_TASK_TBR_BUFFER_STATE_PREFETCH(
                    pvtTqsHdl,
                    pTaskHeader->pduSegAddr0,
                    pTaskHeader->pool0,
                    pTaskHeader->pool0Mref,
                    pTbr);
            case 0:
                if ((0 == pTaskHeader->combinedHeader) && (freeHeader))
                {
                    NCP_TASK_TBR_BUFFER_STATE_PREFETCH(
                        pvtTqsHdl,
                        pTaskHeader,
                        pTaskHeader->headerPool,
                        pTaskHeader->headerPoolMref,
                        pTbr);
                }    
                break;
            default:
                NCP_CALL(NCP_ST_TASK_BAD_PTR_CNT);
        }   /* switch */ 
    }
    else if (freeHeader)
    {
        NCP_TASK_TBR_BUFFER_STATE_PREFETCH(
            pvtTqsHdl,
            pTaskHeader,
            pTaskHeader->headerPool,
            pTaskHeader->headerPoolMref,
            pTbr);
    }  
              
NCP_RETURN_LABEL
    return(ncpStatus);
}  


NCP_INLINE ncp_st_t
ncp_task_tbr_cpu_pool_task_state_prefetch(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
                               ncp_task_header_t *pTaskHeader, 
                               ncp_bool_t freeHeader,
                               ncp_bool_t freeBuffer,
                               ncp_task_tbr_params_t *pTbr)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_pool_t *pPool;

    pPool = pvtTqsHdl->cpuPoolHdl;
        
    if (freeBuffer)
    {    
        /* optimize for most common cases, before entering switch */ 
        if (1 == pTaskHeader->ptrCnt)
        {    
            NCP_TASK_TBR_CPU_POOL_BUFFER_STATE_PREFETCH(pvtTqsHdl, pTaskHeader->pduSegAddr0, 
                                                      pTaskHeader->pool0, pPool, pTbr);
            if ((0 == pTaskHeader->combinedHeader) && (freeHeader))
            {    
                NCP_TASK_TBR_CPU_POOL_BUFFER_STATE_PREFETCH(pvtTqsHdl, pTaskHeader,  
                                                          pTaskHeader->headerPool, pPool, pTbr);
            }                                                             
        }
        else if (0 == pTaskHeader->ptrCnt)
        {
            if ((0 == pTaskHeader->combinedHeader) && (freeHeader))
            {    
                NCP_TASK_TBR_CPU_POOL_BUFFER_STATE_PREFETCH(pvtTqsHdl, pTaskHeader,  
                                                          pTaskHeader->headerPool, pPool, pTbr);
            }       
        }            
        else switch(pTaskHeader->ptrCnt)        
        {
            case 6:
                NCP_TASK_TBR_CPU_POOL_BUFFER_STATE_PREFETCH(pvtTqsHdl, pTaskHeader->pduSegAddr5, 
                                                          pTaskHeader->pool5, pPool, pTbr);
            case 5:
                NCP_TASK_TBR_CPU_POOL_BUFFER_STATE_PREFETCH(pvtTqsHdl, pTaskHeader->pduSegAddr4, 
                                                          pTaskHeader->pool4, pPool, pTbr);
            case 4:
                NCP_TASK_TBR_CPU_POOL_BUFFER_STATE_PREFETCH(pvtTqsHdl, pTaskHeader->pduSegAddr3, 
                                                          pTaskHeader->pool3, pPool, pTbr);
            case 3:
                NCP_TASK_TBR_CPU_POOL_BUFFER_STATE_PREFETCH(pvtTqsHdl, pTaskHeader->pduSegAddr2, 
                                                          pTaskHeader->pool2, pPool, pTbr);
            case 2:
                NCP_TASK_TBR_CPU_POOL_BUFFER_STATE_PREFETCH(pvtTqsHdl, pTaskHeader->pduSegAddr1, 
                                                          pTaskHeader->pool1, pPool, pTbr);
            case 1: 
                NCP_TASK_TBR_CPU_POOL_BUFFER_STATE_PREFETCH(pvtTqsHdl, pTaskHeader->pduSegAddr0, 
                                                          pTaskHeader->pool0, pPool, pTbr);
            case 0:
                if ((0 == pTaskHeader->combinedHeader) && (freeHeader))
                {    
                    NCP_TASK_TBR_CPU_POOL_BUFFER_STATE_PREFETCH(pvtTqsHdl, pTaskHeader,  
                                                              pTaskHeader->headerPool, pPool, pTbr);
                }    
                break;
            default:
                NCP_CALL(NCP_ST_TASK_BAD_PTR_CNT);
        }   /* switch */ 
    }
    else if (freeHeader)
    {
        NCP_TASK_TBR_CPU_POOL_BUFFER_STATE_PREFETCH(pvtTqsHdl, pTaskHeader,  
                                                  pTaskHeader->headerPool, pPool, pTbr);
    } 
                 
NCP_RETURN_LABEL
    return(ncpStatus);
}

  
#endif /* NCP_TASK_TBR_ENABLED */

NCP_INLINE   ncp_st_t
ncp_task_recv_deferred(
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
    ncp_task_pcq_t *p_iPCQ,
    ncp_ipcq_entry_t *pIPCQentry,
    ncp_uint32_t numTasks, 
    ncp_uint32_t *pNumReceived, 
    ncp_task_header_t **pTasks,
    ncp_bool_t wait) 
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    NCP_ADDR_DEPENDENCY_TMPVAR_DECL(tmp_isZero)    
    int numAvailableTasks;
    int numReceivedTasks=0;
    ncp_uint8_t strippedConsumerVal;
    ncp_bool_t needPollStateReset=TRUE;
    /* hint to compiler that these can be cached in a register */
    ncp_ipcq_entry_t *pPrefetchEntry1 = p_iPCQ->u.ipcq_info.pPrefetchEntry1;
    ncp_ipcq_entry_t *pPrefetchEntry2 = p_iPCQ->u.ipcq_info.pPrefetchEntry2;    
    ncp_uint8_t appToggleBit   = p_iPCQ->u.ipcq_info.appToggleBit;
    ncp_uint8_t appConsumerVal = p_iPCQ->u.ipcq_info.appConsumerVal;
    NCP_TASK_TBR_STATE_PTRS_DECL()
    
    /*
     * For deferred consumption mode,  we force the index update at the next ncp_task_recv.
     * Caller can request to receive zero tasks,   in which case ncp_task_recv will just 
     * consume all outstanding tasks for this iPCQ.
     */
    if (p_iPCQ->hwConsumerVal != appConsumerVal)
    {    
        *(p_iPCQ->pConsumerIdx) = p_iPCQ->hwConsumerVal = appConsumerVal;   /* Update PGIT index */
        p_iPCQ->toggleBit = appToggleBit;                                   /* Update toggle bit too */
        pvtTqsHdl->consumptionsOwed = 0;
    }   
    if (0 == numTasks)
    {
        NCP_JUMP_RETURN();
    }
            
    /*
     * wait == FALSE: revceive the available tasks, up to a max of numTasks
     * wait == TRUE: spin until 1 or more, up to numTasks, tasks are available
     */
    if (p_iPCQ->u.ipcq_info.numRxAvail < numTasks)
    {
        do  
        {
            
            /*
             * Optimization - only read pIDX out of pgit when cached val shows
             *                empty.
             * Minimizes cache misses due to NCA/CPU interaction.
             */

            p_iPCQ->hwProducerVal = NCP_TASK_PRODUCER_IDX_GET(p_iPCQ, tmp_isZero);

            if (appConsumerVal == p_iPCQ->hwProducerVal)
            {
                if (appConsumerVal == p_iPCQ->hwProducerVal)
                {
                    NCP_TASK_INC_STAT(pvtTqsHdl->pTqs, RxQueueEmpty);
    
                    if (FALSE == wait)
                    {
                        ncpStatus = NCP_ST_TASK_RECV_QUEUE_EMPTY;
                        goto queue_empty;
                    }
                    else
                    {
                        ncp_st_t tmpStatus;  
                                         
                        if (needPollStateReset)
                        {
                            needPollStateReset = FALSE;               
                            NCP_TASK_RESET_POLL_STATE(&pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_RECV]);   
                        }    
                        if (NCP_ST_SUCCESS != (tmpStatus = NCP_TASK_DO_WAIT(
                                pvtTqsHdl,
                                (&pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_RECV]),
                                myDevHdl,
                                pvtTqsHdl->tqsId)))
                        {
                            ncpStatus = tmpStatus;
                            NCP_JUMP_RETURN();
                        }
                        continue;
                    }
                }
            }
    
            /**
             *  Queue is non-empty. Now calculate the number of availables tasks,   and return stripped consumer value
             */
            NCP_ITASK_SYSMEM_BARRIER(); /* NULL macro if address dependcy enabled */
            strippedConsumerVal = NCP_TASK_UPDATE_NUM_RX_DEFERRED_AVAIL(p_iPCQ);
            break;
        } while(1);
    } /* if numRxAvail */ 
    else
    {
        strippedConsumerVal = appConsumerVal & NCP_PCQ_TOGGLE_BIT_MASK;  
    }       
       
    if (numTasks < p_iPCQ->u.ipcq_info.numRxAvail)
    {
        numAvailableTasks = numTasks;
    }
    else
    {
        numAvailableTasks = p_iPCQ->u.ipcq_info.numRxAvail;    
    }        

    while(numReceivedTasks < numAvailableTasks)
    {
        ncp_task_header_t         *pTaskHeader;
        ncp_uint64_t taskAddr64 = NCP_TASK_TASKADDR64_GET(pIPCQentry, tmp_isZero); /* implements addr dependency, if enabled */
                
        pTaskHeader = pTasks[numReceivedTasks] = (void *)(ncp_uintptr_t)taskAddr64;

        NCP_TASK_TBR_STATE_PTRS_INIT();
        NCP_TASK_TBR_RXTASK_STATE_PREFETCH(pvtTqsHdl, pTaskHeader, pTbr);

        strippedConsumerVal++;
        strippedConsumerVal &= p_iPCQ->nEntriesMinusOne;
        
        if (0 != strippedConsumerVal)
        {            
            if (strippedConsumerVal < p_iPCQ->nEntriesMinusTwo)
            {
                pIPCQentry++;
                pPrefetchEntry1++;
                pPrefetchEntry2++;
            }
            else if (strippedConsumerVal == p_iPCQ->nEntriesMinusTwo)    
            {
                pIPCQentry++;
                pPrefetchEntry1++;
                pPrefetchEntry2 = (ncp_ipcq_entry_t *)(p_iPCQ->pPCQbase);   
            }        
            else 
            {
                pIPCQentry++;
                pPrefetchEntry1 = (ncp_ipcq_entry_t *)(p_iPCQ->pPCQbase);;
                pPrefetchEntry2++; 
            }  
        }          
        else
        {
            pIPCQentry = (ncp_ipcq_entry_t *)(p_iPCQ->pPCQbase);
            pPrefetchEntry1++;
            pPrefetchEntry2++;            
            appToggleBit ^= (1 << NCP_PCQ_TOGGLE_BIT_SHIFT); /* invert app toggle bit */
            p_iPCQ->pcqRollCnt++;
        }
        appConsumerVal = strippedConsumerVal | appToggleBit;        

        NCP_TASK_PREFETCH_PCQ_ENTRY(pPrefetchEntry2);
        NCP_TASK_PREFETCH_TASK_HEADER(pPrefetchEntry1);
            
        if (numReceivedTasks != numAvailableTasks)
        {
            numReceivedTasks++;
            NCP_TASK_INC_STAT(pvtTqsHdl->pTqs, RxTask);    
            NCP_TASK_RXTASK_TBR_BUFFER_STATE_UPDATE_MREF(pTbr);
        }    
        else
        {
            numReceivedTasks++;
            NCP_TASK_INC_STAT(pvtTqsHdl->pTqs, RxTask);  
            NCP_TASK_RXTASK_TBR_BUFFER_STATE_UPDATE_MREF(pTbr);
            break;
        }
    }

NCP_RETURN_LABEL

    /* update state before exit */
    p_iPCQ->u.ipcq_info.pIPCQentry      = pIPCQentry;
    p_iPCQ->u.ipcq_info.pPrefetchEntry1  = pPrefetchEntry1;
    p_iPCQ->u.ipcq_info.pPrefetchEntry2  = pPrefetchEntry2;    
    p_iPCQ->u.ipcq_info.appToggleBit    = appToggleBit;
    p_iPCQ->u.ipcq_info.appConsumerVal  = appConsumerVal;  
      
    p_iPCQ->u.ipcq_info.numRxAvail -= numReceivedTasks;
    pvtTqsHdl->consumptionsOwed += numReceivedTasks;            
    if (FALSE == p_iPCQ->u.ipcq_info.autoCompletionMode) 
    {
         pvtTqsHdl->completionsOwed += numReceivedTasks;

#if 0
         NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                               ncp_xlf_task_recv_deferred_completionsOwedInfo,
                               NCP_MSG_DEBUG,
                               "completions owed incremented by %d, total = 0x%"PRIx64"\r\n",
                               numReceivedTasks,
                               pvtTqsHdl->completionsOwed);
#endif
    }

queue_empty:

    *pNumReceived = numReceivedTasks;

    return(ncpStatus);
} /* ncp_task_recv_deferred */

NCP_INLINE   ncp_st_t
ncp_task_recv_normal(
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
    ncp_task_pcq_t *p_iPCQ,    
    ncp_ipcq_entry_t *pIPCQentry,
    ncp_uint32_t numTasks, 
    ncp_uint32_t *pNumReceived, 
    ncp_task_header_t **pTasks,
    ncp_bool_t wait) 
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    NCP_ADDR_DEPENDENCY_TMPVAR_DECL(tmp_isZero)    
    int numAvailableTasks;
    int numReceivedTasks=0;
    ncp_uint8_t strippedConsumerVal;
    ncp_bool_t needPollStateReset=TRUE;
    /* hint to compiler that these can be cached in a register */
    ncp_ipcq_entry_t *pPrefetchEntry1 = p_iPCQ->u.ipcq_info.pPrefetchEntry1;
    ncp_ipcq_entry_t *pPrefetchEntry2 = p_iPCQ->u.ipcq_info.pPrefetchEntry2;    
    ncp_uint8_t  hwConsumerVal = p_iPCQ->hwConsumerVal;         
    ncp_uint8_t  toggleBit = p_iPCQ->toggleBit;   
    NCP_TASK_TBR_STATE_PTRS_DECL()
     
    /*
     * wait == FALSE: revceive the available tasks, up to a max of numTasks
     * wait == TRUE: spin until 1 or more, up to numTasks, tasks are available
     */
    if (p_iPCQ->u.ipcq_info.numRxAvail < numTasks)
    {
        do  
        {
            
            /*
             * Optimization - only read pIDX out of pgit when cached val shows
             *                empty.
             * Minimizes cache misses due to NCA/CPU interaction.
             */

            p_iPCQ->hwProducerVal = NCP_TASK_PRODUCER_IDX_GET(p_iPCQ, tmp_isZero);

            if (hwConsumerVal == p_iPCQ->hwProducerVal)
            {
                NCP_TASK_INC_STAT(pvtTqsHdl->pTqs, RxQueueEmpty);

                if (FALSE == wait)
                {
                    ncpStatus = NCP_ST_TASK_RECV_QUEUE_EMPTY;
                    goto queue_empty;
                }
                else
                {
                    
                    ncp_st_t tmpStatus;                   

                    if (needPollStateReset)
                    {
                        needPollStateReset = FALSE;               
                        NCP_TASK_RESET_POLL_STATE(&pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_RECV]);   
                    }        
                    if (NCP_ST_SUCCESS != (tmpStatus = NCP_TASK_DO_WAIT(
                            pvtTqsHdl,
                            (&pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_RECV]),
                            myDevHdl,
                            pvtTqsHdl->tqsId)))
                    {
                        ncpStatus = tmpStatus;
                        NCP_JUMP_RETURN();
                    }
                    continue;
                }
            }
    
            /**
             *  Queue is non-empty. Now calculate the number of availables tasks,   and return stripped consumer value
             */
            NCP_ITASK_SYSMEM_BARRIER(); /* NULL macro if address dependcy enabled */             
            strippedConsumerVal = NCP_TASK_UPDATE_NUM_RX_AVAIL(p_iPCQ);
            break;
        }  while(1);
    } /* if numRxAvail */ 
    else
    {
        strippedConsumerVal = hwConsumerVal & NCP_PCQ_TOGGLE_BIT_MASK;  
    }       
    
    if (numTasks < p_iPCQ->u.ipcq_info.numRxAvail)
    {
        numAvailableTasks = numTasks;
    }
    else
    {
        numAvailableTasks = p_iPCQ->u.ipcq_info.numRxAvail;    
    }        

    while(numReceivedTasks < numAvailableTasks)
    {
        ncp_task_header_t         *pTaskHeader;
        ncp_uint64_t taskAddr64 = NCP_TASK_TASKADDR64_GET(pIPCQentry, tmp_isZero); /* implements addr dependency, if enabled */
        pTaskHeader = pTasks[numReceivedTasks] = (void *)(ncp_uintptr_t)taskAddr64;

        NCP_TASK_TBR_STATE_PTRS_INIT();
        NCP_TASK_TBR_RXTASK_STATE_PREFETCH(pvtTqsHdl, pTaskHeader, pTbr);
        
        strippedConsumerVal++;
        strippedConsumerVal &= p_iPCQ->nEntriesMinusOne; 
        
        if (0 != strippedConsumerVal)
        {    
            if (strippedConsumerVal < p_iPCQ->nEntriesMinusTwo)
            {
                pIPCQentry++;
                pPrefetchEntry1++;
                pPrefetchEntry2++;
            }
            else if (strippedConsumerVal == p_iPCQ->nEntriesMinusTwo)    
            {
                pIPCQentry++;
                pPrefetchEntry1++;
                pPrefetchEntry2 = (ncp_ipcq_entry_t *)(p_iPCQ->pPCQbase);   
            }        
            else 
            {
                pIPCQentry++;
                pPrefetchEntry1 = (ncp_ipcq_entry_t *)(p_iPCQ->pPCQbase);
                pPrefetchEntry2++; 
            }  
        }          
        else
        {
            pIPCQentry = (ncp_ipcq_entry_t *)(p_iPCQ->pPCQbase);
            pPrefetchEntry1++;
            pPrefetchEntry2++;            
            toggleBit ^= (1 << NCP_PCQ_TOGGLE_BIT_SHIFT); /* invert app toggle bit */
            p_iPCQ->pcqRollCnt++;
        }
        hwConsumerVal = strippedConsumerVal | toggleBit; 
        
        NCP_TASK_PREFETCH_PCQ_ENTRY(pPrefetchEntry2);
        NCP_TASK_PREFETCH_TASK_HEADER(pPrefetchEntry1);
                
        if (numReceivedTasks != numAvailableTasks)
        {
            numReceivedTasks++;
            NCP_TASK_INC_STAT(pvtTqsHdl->pTqs, RxTask);            
            NCP_TASK_RXTASK_TBR_BUFFER_STATE_UPDATE_MREF(pTbr);
        }    
        else
        {
            numReceivedTasks++;
            NCP_TASK_INC_STAT(pvtTqsHdl->pTqs, RxTask);             
            NCP_TASK_RXTASK_TBR_BUFFER_STATE_UPDATE_MREF(pTbr);
            break;
        }
    }

NCP_RETURN_LABEL

    /* update state before exit */
    p_iPCQ->hwConsumerVal = hwConsumerVal;
    p_iPCQ->toggleBit     = toggleBit;      
    p_iPCQ->u.ipcq_info.pIPCQentry      = pIPCQentry;
    p_iPCQ->u.ipcq_info.pPrefetchEntry1  = pPrefetchEntry1;
    p_iPCQ->u.ipcq_info.pPrefetchEntry2  = pPrefetchEntry2;    
    
    p_iPCQ->u.ipcq_info.numRxAvail -= numReceivedTasks;
    *(p_iPCQ->pConsumerIdx) = p_iPCQ->hwConsumerVal;    /* Update PGIT index */
    if (FALSE == p_iPCQ->u.ipcq_info.autoCompletionMode) 
    {
         pvtTqsHdl->completionsOwed += numReceivedTasks;  
#if 0
         NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                               ncp_xlf_task_recv_normal_completionsOwedInfo,
                               NCP_MSG_DEBUG,
                               "completions owed incremented by %d, total = 0x%"PRIx64"\r\n",
                               numReceivedTasks,
                               pvtTqsHdl->completionsOwed);
#endif
    }

queue_empty:

    /* increment callers count */
    *pNumReceived = numReceivedTasks;
        
    return(ncpStatus);
}  /* ncp_task_recv_normal */

NCP_INLINE  ncp_st_t
ncp_task_bulk_MMEpool_alloc(
                ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
                ncp_task_mme_allocator_t *pAllocator, 
                ncp_uint32_t numTaskBuffers,
                ncp_uint32_t *numTaskBuffersAllocated,
                ncp_uint32_t *taskBufferSizes,
                void **taskBuffers,
                ncp_uint32_t poolId,                
                ncp_bool_t wait)
{
#ifndef NCP_KERNEL     
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_pcq_t  *p_mPCQ;
    void         **pRetBuffers = &taskBuffers[0];
    ncp_uint32_t *pSz          = &taskBufferSizes[0];
    NCP_MUTEX_LOCKED_FLAG_DECL(unlockRequired);
    int totalAllocated = 0;
    ncp_bool_t needPollStateReset = TRUE;
    NCP_TASK_LOCK_FLAGS(flags);
    NCP_TASK_TBR_STATE_PTRS_DECL()
    
    if (FALSE == pAllocator->valid)
    {
        NCP_CALL(NCP_ST_TASK_NO_MME_ALLOCATOR);
    }

    if (pAllocator->shared)
    {
        NCP_CALL(NCP_TASK_CLAIM_LOCK_HDL(&pAllocator->mmeLock, flags, &unlockRequired));
    }

    /* assumes caller wants 1 or more buffers! */
    do
    {

        /*
         * The following code will advance to a larger buffer,   if the best-fit
         * size is not configured.
         */
        ncp_uint32_t size; 
        
        if (0 != (size = *pSz++))
        {
            size--;
            if (pAllocator->mPCQ[0].nEntries      && (0 == (size & 0xFFFFFF00))) /* <= 256 */
            {
                p_mPCQ = &pAllocator->mPCQ[0];
            }
            else if (pAllocator->mPCQ[1].nEntries && (0 == (size & 0xFFFFF800))) /* <= 2K */
            {
                p_mPCQ = &pAllocator->mPCQ[1];
            }    
            else if (pAllocator->mPCQ[2].nEntries && (0 == (size & 0xFFFFC000))) /* <= 16K */
            {
                p_mPCQ = &pAllocator->mPCQ[2];
            }        
            else if (pAllocator->mPCQ[3].nEntries && (0 == (size & 0xFFFF0000))) /* <= 64K */
            {
                p_mPCQ = &pAllocator->mPCQ[3];
            }                                        
            else
            {
                NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                      ncp_xlf_task_bulk_MMEpool_alloc_bufSizeTooLargeForPool,
                                      NCP_MSG_ERROR,
                                      "mme alloc request - buffSize %d too large for pool_%d\r\n",
                                      size + 1,
                                      poolId);

                NCP_CALL(NCP_ST_TASK_BUFFSIZE_TOO_LARGE);
            }
        }
        else
        {
            NCP_CALL(NCP_ST_TASK_REQUEST_FOR_ZERO_LENGTH_TASK_BUFFER);
        }
        
        NCP_TASK_PREFETCH_PCQ_ENTRY(p_mPCQ->u.mpcq_info.pMPCQentry);
    
        /* mme_alloc_retry: */
        
        /* Keep executing loop until a buffer is successfully allocated,  
         * or wait profile expires 
         */
    
        do {
            
            if (p_mPCQ->u.mpcq_info.numAvail)
            {
                /* likely */
                p_mPCQ->u.mpcq_info.numAvail--;
            }        
            else
            {
                /* Queue is empty - refresh producer Idx */
                p_mPCQ->hwProducerVal = *(p_mPCQ)->pProducerIdx;
    
                /* Still empty ? */
                if (p_mPCQ->hwConsumerVal == p_mPCQ->hwProducerVal)
                {
                    if (FALSE == wait)
                    {
                        ncpStatus = NCP_ST_NO_MEMORY;
                        NCP_JUMP_RETURN();
                    }
                    else if (0 != totalAllocated)
                    {
                        NCP_JUMP_RETURN();  /* We return success if at least one allocated */
                    }                         
                    else
                    {
                        ncp_st_t tmpStatus;
                        
                        if (needPollStateReset)
                        {
                            needPollStateReset = FALSE;               
                            NCP_TASK_RESET_POLL_STATE(&pvtTqsHdl->waitProfile
                                [NCP_TASK_API_CLASS_ALLOC]);   
                        }    
                        if (NCP_ST_SUCCESS != (tmpStatus = NCP_TASK_DO_WAIT(
                                pvtTqsHdl,
                                (&pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_ALLOC]),
                                myDevHdl,
                                pvtTqsHdl->tqsId)))
                        {
                            ncpStatus = tmpStatus;
                            NCP_JUMP_RETURN();
                        }
                        continue;
                    }
                }
                else
                {
                    ncp_uint8_t strippedProducerVal = p_mPCQ->hwProducerVal & NCP_PCQ_TOGGLE_BIT_MASK;
                    ncp_uint8_t strippedConsumerVal = p_mPCQ->hwConsumerVal & NCP_PCQ_TOGGLE_BIT_MASK;      

                    /*
                     *  Queue is non-empty. Now calculate and save the number of availables tasks.
                     */
                    
                    /* 
                     * optimization: cache num avail 
                     * important: we set numAvail to 1 less that are actually available
                     * as the code assumes we have already decremented numAvail!
                     */
                    
                    if (strippedProducerVal == strippedConsumerVal) 
                    {
                        if (p_mPCQ->hwConsumerVal != p_mPCQ->hwProducerVal)
                        {  
                            /* if toggle bit is only difference,  then queue is 100% full of available entries */  
                            p_mPCQ->u.mpcq_info.numAvail = p_mPCQ->nEntriesMinusOne;
                        }                
                    }        
                    else if (strippedProducerVal > strippedConsumerVal)
                    {
                        p_mPCQ->u.mpcq_info.numAvail = strippedProducerVal - strippedConsumerVal - 1;
                    }
                    else
                    {
                        p_mPCQ->u.mpcq_info.numAvail = (p_mPCQ->nEntriesMinusOne - strippedConsumerVal) + strippedProducerVal;
                    } 

                    /* 
                     * refreshed prododucer Idx, so issue barrier. No more barriers are
                     * needed until we consume numAvail task buffers from this mpcq_info
                     */
                    NCP_SYSMEM_BARRIER();                                       
                    
                }           
            }  /* else */  
                        
            NCP_TASK_TBR_STATE_PTRS_INIT();        
            NCP_TASK_TBR_INIT_BUFFER_STATES(pTbr, NCP_TASK_TBR_STATE_FREE, pvtTqsHdl->pProcess->pid);

            /* Store buffer address for caller */
            *pRetBuffers = (void *)p_mPCQ->u.mpcq_info.pMPCQentry->address;

            NCP_TASK_TBR_BUFFER_STATE_PREFETCH(
                pvtTqsHdl,
                *pRetBuffers, /* the newly allocated buffer */
                poolId,
                0,
                pTbr);
            
            /* advance to next location in callers array. */
            pRetBuffers++;                     
             
            /* Note: proven faster than using if (0 == (p_mPCQ->hwConsumerVal & p_mPCQ->nEntriesMinusOne)) */
            if (p_mPCQ->u.mpcq_info.pMPCQentry != p_mPCQ->u.mpcq_info.pLastEntry)
            {
                /* This is the common case - not wrapping */
                p_mPCQ->u.mpcq_info.pMPCQentry++;
                p_mPCQ->hwConsumerVal++;
                *(p_mPCQ->pConsumerIdx) = p_mPCQ->hwConsumerVal;
            }
            else
            {
                p_mPCQ->u.mpcq_info.pMPCQentry = (ncp_mpcq_entry_t *)(p_mPCQ->pPCQbase);
                p_mPCQ->toggleBit ^= (1 << NCP_PCQ_TOGGLE_BIT_SHIFT); /* invert toggle bit */
                *(p_mPCQ->pConsumerIdx) = p_mPCQ->hwConsumerVal = p_mPCQ->toggleBit; /* Add toggle bit */
                p_mPCQ->pcqRollCnt++;
            }

            /* delayed update of buffer state- improves cache prefetch distance */
            /* NCP_TASK_TBR_BUFFER_STATE_UPDATE(pTbr, TRUE); */

            {
                ncp_task_pid_t  **_pStatePtr =  &pTbr->statePtrArray[0];
                ncp_task_pid_t  *_pState;
                int _i = pTbr->ptrCnt;
                while(_i--)
                {
                    _pState = *_pStatePtr++;
                    if ((*_pState == pTbr->expectedState) ||
                        (*_pState == NCP_TASK_TBR_STATE_MULTI_REFS))
                    {
                        /* likely code path - optimization */
                    }
                    else
                    {
                        NCP_CALL(NCP_ST_TASK_TBR_FATAL_POOL_CORRUPTION);
                    }
                    *_pState = pTbr->newState;
                }
            }
    
            break; /* Got one,   so exit retry loop */
    
        }  while(1); /* retry loop */
              
    } while (++totalAllocated < numTaskBuffers);

NCP_RETURN_LABEL

    NCP_CLEANUP_MUTEX_CALL(NCP_TASK_FREE_LOCK_HDL(&pAllocator->mmeLock, flags, &unlockRequired));

    *numTaskBuffersAllocated = totalAllocated;

    return(ncpStatus);
#else   /* NCP_KERNEL */
    return(NCP_ST_NOT_IMPLEMENTED);
#endif
}
 
NCP_INLINE ncp_st_t
ncp_task_add_send_done(
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
    int                         txQueueId,
    ncp_task_send_done_type_t   type,
    void                       *callbackFn,
    void                       *sendDoneArg1,
    void                       *sendDoneArg2,
    ncp_bool_t                  sendDoneArg3,
    ncp_uint8_t                 sendDoneArg4)
{
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;                                     
    ncp_uint8_t nxt_pIdx = ((pvtTqsHdl->sendDoneInfo[txQueueId].pIdx + 1)           
                            & (pvtTqsHdl->sendDoneInfo[txQueueId].nEntriesMinusOne)); 
 
    if (nxt_pIdx != pvtTqsHdl->sendDoneInfo[txQueueId].pendingIdx)                   
    {                                                                       
        ncp_task_sendDone_entry_t *pEntry                            
            = pvtTqsHdl->sendDoneInfo[txQueueId].currFillEntry;  

        pEntry->type       = type;
        if (type == NCP_TASK_TASK_CALLBACK)
        {
            pEntry->callbackFn.sendDoneFn = callbackFn;
        }
        else
        {
            pEntry->callbackFn.transferDoneFn = callbackFn;
        }
        pEntry->sendDoneArg1 = sendDoneArg1;
        pEntry->sendDoneArg2 = sendDoneArg2;
        pEntry->sendDoneArg3 = sendDoneArg3;
        pEntry->sendDoneArg4 = sendDoneArg4;

        /* 
         * Housekeeping for PCQ
         */
                             
        if (0 != nxt_pIdx)           
        {                                                               
            pvtTqsHdl->sendDoneInfo[txQueueId].pIdx = nxt_pIdx;
            pvtTqsHdl->sendDoneInfo[txQueueId].currFillEntry++; 
        }                                                               
        else                                                            
        {
            pvtTqsHdl->sendDoneInfo[txQueueId].pIdx=0;
            pvtTqsHdl->sendDoneInfo[txQueueId].currFillEntry                      
                = pvtTqsHdl->sendDoneInfo[txQueueId].entries;                     
        }    
        pvtTqsHdl->sendDoneInfo[txQueueId].sendDonePending = TRUE;                
    }                                                                   
    else                                                                
    {                                                                   
        NCP_CALL(NCP_ST_TASK_SEND_QUEUE_FULL);                       
    } 
NCP_RETURN_LABEL                                                                
    return(ncpStatus);                                                         
}

NCP_INLINE ncp_st_t
ncp_task_process_send_done(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl, int txQueueId)                           
{  
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;      
    ncp_task_sendDone_entry_t *pEntry                            
            = pvtTqsHdl->sendDoneInfo[txQueueId].currPendingEntry;  
    ncp_uint8_t pendIdx = pvtTqsHdl->sendDoneInfo[txQueueId].pendingIdx;  
    ncp_uint8_t endIdx  = pvtTqsHdl->sendDoneInfo[txQueueId].cIdx;  
    
    while(pendIdx != endIdx) 
    {                                                                       
    
        if (NULL == pEntry)
        {
            NCP_CALL(NCP_ST_INTERNAL_ERROR);
        }
        if (pEntry->type == NCP_TASK_TASK_CALLBACK)
        {
            NCP_TASK_SET_INCALLBACK_FLAG(pvtTqsHdl, txQueueId, TRUE);
            pEntry->callbackFn.sendDoneFn(
                pEntry->sendDoneArg1,
                pEntry->sendDoneArg2);
            NCP_TASK_SET_INCALLBACK_FLAG(pvtTqsHdl, txQueueId, FALSE);            
        }
        else if (pEntry->type == NCP_TASK_BUFFER_CALLBACK)
        {
            NCP_TASK_SET_INCALLBACK_FLAG(pvtTqsHdl, txQueueId, TRUE);           
            pEntry->callbackFn.transferDoneFn(
                pEntry->sendDoneArg1,
                pEntry->sendDoneArg2,
                pEntry->sendDoneArg3,
                pEntry->sendDoneArg4);
            NCP_TASK_SET_INCALLBACK_FLAG(pvtTqsHdl, txQueueId, FALSE);               
        }

        pendIdx++;                              
        pendIdx &= pvtTqsHdl->sendDoneInfo[txQueueId].nEntriesMinusOne; 
        if (0 != pendIdx)                       
        {                                                                   
            pEntry++;                    
        }                                                                   
        else                                                                
        {                                                                   
            pEntry = pvtTqsHdl->sendDoneInfo[txQueueId].entries;                         
        }                                                                   
    } 
    
    /*
     * Housekeeping for thread-private PCQ.   This PCQ allows us to tie callback to the actual thread
     * and address space that requested it.
     */
     
    pvtTqsHdl->sendDoneInfo[txQueueId].currPendingEntry = pEntry;
    pvtTqsHdl->sendDoneInfo[txQueueId].pendingIdx = pendIdx; 
    if (pendIdx == pvtTqsHdl->sendDoneInfo[txQueueId].pIdx) 
    {                                                                   
        pvtTqsHdl->sendDoneInfo[txQueueId].sendDonePending = FALSE;               
    }   
    
NCP_RETURN_LABEL    
    return(ncpStatus);                                                                      
}

NCP_INLINE ncp_st_t
ncp_task_process_oPCQ_aux_entries(
                              ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
                              ncp_task_pcq_t     *p_oPCQ)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_per_oPCQ_aux_data_t *pAuxEntry = p_oPCQ->u.opcq_info.pAuxReadEntry;
    ncp_uint8_t                   auxIdx    = p_oPCQ->u.opcq_info.auxIdx;
    ncp_uint8_t endIdx;
    ncp_uint8_t sendDoneCnt;     
    
    if (0 == (sendDoneCnt = p_oPCQ->u.opcq_info.sendDoneCnt))
    {
        /* Intentional NULL body - just return */
    }
    else
    { 
        /* We want a full refresh of the consumer Idx if any sendDone requests are outstanding */
        p_oPCQ->hwConsumerVal = *(p_oPCQ)->pConsumerIdx;
        endIdx = p_oPCQ->hwConsumerVal & NCP_PCQ_TOGGLE_BIT_MASK;
    
        /* 
         * Inspect all processed entries, calling the send done funcs,  
         * for so long as we still have outstanding send done requests 
         */
        do      
        {
            if (NULL != pAuxEntry->sendDoneTqsHdl)
            {
                NCP_TASK_POST_SEND_DONE(pAuxEntry->sendDoneTqsHdl, p_oPCQ);
                pAuxEntry->sendDoneTqsHdl = NULL;
                p_oPCQ->u.opcq_info.sendDoneCnt--;
                if (0 == --sendDoneCnt)
                {
                    /* 
                     * Skip aux state update - it will be reinitialized 
                     * the next time a send done request is added 
                     */
                    NCP_JUMP_RETURN();  
                }        
            }
    
            if (++pAuxEntry != p_oPCQ->u.opcq_info.pLastAuxEntry)  
            {
                auxIdx++;
            }                                      
            else
            {
                pAuxEntry = p_oPCQ->u.opcq_info.pBaseAuxEntry;
                auxIdx = 0;
            }
            
        } while(auxIdx != endIdx);
        
        /* still have send done requests outstanding,   so update state before exit */
        p_oPCQ->u.opcq_info.pAuxReadEntry = pAuxEntry;
        p_oPCQ->u.opcq_info.auxIdx        = auxIdx;
        p_oPCQ->u.opcq_info.sendDoneCnt   = sendDoneCnt;
        
    }
    
NCP_RETURN_LABEL

    return(ncpStatus);
}

NCP_INLINE ncp_st_t
ncp_task_fill_per_opcq_aux_data(ncp_task_pvt_tqsHdl_data_t *sendDoneTqsHdl,                                       
                               ncp_task_pcq_t *p_oPCQ)  
{   
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;                                                                             
 
    /* Reinit aux state if this is the first send done request */
    if (0 == p_oPCQ->u.opcq_info.sendDoneCnt)
    {   
 
        if (NULL == (sendDoneTqsHdl))
        {
            NCP_JUMP_RETURN(); /* get out,  no send dones to track */
        }   
        
        /* Init aux state since we must now track send done requests again */          
        p_oPCQ->u.opcq_info.auxIdx = p_oPCQ->hwProducerVal & NCP_PCQ_TOGGLE_BIT_MASK;
        p_oPCQ->u.opcq_info.pAuxReadEntry 
         = p_oPCQ->u.opcq_info.pAuxWriteEntry
         = p_oPCQ->u.opcq_info.pBaseAuxEntry + p_oPCQ->u.opcq_info.auxIdx;            
    }

    if (NULL != sendDoneTqsHdl)
    {
        p_oPCQ->u.opcq_info.sendDoneCnt++;
    }

    p_oPCQ->u.opcq_info.pAuxWriteEntry->sendDoneTqsHdl = sendDoneTqsHdl; /* Store the send done indicator */ 
    p_oPCQ->u.opcq_info.pAuxWriteEntry++;

    /* 
     * Housekeeping for per oPCQ aux data
     */
    if (p_oPCQ->u.opcq_info.pAuxWriteEntry != p_oPCQ->u.opcq_info.pLastAuxEntry)                    
    {                                                                       
        /* Intentional NULL body */
    }                                                                       
    else                                                                    
    {                                                                       
        p_oPCQ->u.opcq_info.pAuxWriteEntry                                  
          =  p_oPCQ->u.opcq_info.pBaseAuxEntry;
    } 
   
NCP_RETURN_LABEL
    
    return(ncpStatus);
}

NCP_INLINE ncp_st_t
ncp_task_put_opcq(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl, 
                  ncp_task_pcq_t *p_oPCQ, 
                  ncp_task_send_meta_t *pMetadata, 
                  ncp_opcq_entry_t *pSrcEntry)
{
    ncp_st_t            ncpStatus           = NCP_ST_SUCCESS;
    ncp_uint64_t        *dst64, *src64;
    
    /* Populate oPCQ entry with contents that caller set up */
    src64 = (ncp_uint64_t *)pSrcEntry;
    dst64 = (ncp_uint64_t *)p_oPCQ->u.opcq_info.pOPCQentry;
    *dst64++ = *src64++;
    *dst64   = *src64;

    if ((pMetadata) && pMetadata->sendDoneFn)
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

    
NCP_RETURN_LABEL
    return(ncpStatus);        
}

NCP_INLINE ncp_st_t
ncp_task_CpuPool_alloc_noLock(
        ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
        ncp_task_pool_t *pPoolEntry,
		ncp_uint32_t size,
		void **taskAddr)
{
    int i;
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;
    NCP_TASK_TBR_STATE_PTRS_DECL()

    if (taskAddr == NULL)
    {
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_CpuPool_alloc_noLock_nullTaskAddr,
                              NCP_MSG_ERROR, "NULL TASKADDR\r\n");
        NCP_CALL(NCP_ST_NO_MEMORY);
    }
    
    for (i=0; i<(NCP_TASK_NUM_BUFF_SIZES); i++)
    {
        if (size <=  pPoolEntry->u.cpu.buffListArray[i].size)
        {
            ncp_task_bufflist_t *pBuffList = &pPoolEntry->u.cpu.buffListArray[i];  
            ncp_buffDescriptor_t *pBuffDesc;  

            if ((NULL == pBuffList) || (NULL == (*taskAddr = (void *)(pBuffDesc = pBuffList->NCP_POINTER(free)))))
            {
                NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                      ncp_xlf_task_CpuPool_alloc_noLock_bufferAllocFailed,
                                      NCP_MSG_ERROR,
                                      "failed to allocate buffer of size %d in alloc, pPoolEntry=%p, pBuffList=%p\r\n",
                                      size, pPoolEntry,pBuffList);
                NCP_CALL(NCP_ST_NO_MEMORY);
            }   

            NCP_TASK_TBR_STATE_PTRS_INIT();
            NCP_TASK_TBR_INIT_BUFFER_STATES(pTbr, NCP_TASK_TBR_STATE_FREE, pvtTqsHdl->pProcess->pid);
            NCP_TASK_TBR_BUFFER_STATE_PREFETCH(
                pvtTqsHdl,
               *taskAddr,
                pPoolEntry->poolId,
                0,
                pTbr);
                                             
#ifdef NCP_TASK_CPU_POOL_IS_LIFO          
            pBuffList->NCP_POINTER(free) = pBuffDesc->next;
#else 
            if (NULL == (pBuffList->NCP_POINTER(free) = pBuffDesc->next))
            {    
                pBuffList->last = NULL;
            }   
#endif               
            NCP_TASK_PREFETCH_CPUPOOL_FREELIST(pBuffList->NCP_POINTER(free));
            
            pBuffList->numFree--;   
            if (pBuffList->numFree < pBuffList->freeLowWaterMark)
            {
                pBuffList->freeLowWaterMark = pBuffList->numFree;
            }  

            break;
        }
    }
    if (NCP_TASK_NUM_BUFF_SIZES != i)
    {
        NCP_TASK_TBR_BUFFER_STATE_UPDATE(pTbr, FALSE);
    }    
    else
    {
        NCP_CALL(NCP_ST_NO_MEMORY);
    }  

NCP_RETURN_LABEL  
    
    return(ncpStatus);
}	

NCP_INLINE ncp_st_t
ncp_task_CpuPool_free_noLock(
        ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
        ncp_task_pool_t *pPoolEntry,
		void *taskAddr)
{
    int i;
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;
    ncp_bool_t validBuff = FALSE;
    NCP_TASK_TBR_STATE_PTRS_DECL()    

    if (   ((ncp_uintptr_t)taskAddr > (ncp_uintptr_t)(pPoolEntry->poolVAEnd))
        || ((ncp_uintptr_t)taskAddr < (ncp_uintptr_t)(pPoolEntry->poolVA)))
    {
        NCP_CALL(NCP_ST_INVALID_VALUE);
    }

    for (i=0; i < NCP_TASK_NUM_BUFF_SIZES; i++)
    {
        if ((taskAddr >= pPoolEntry->u.cpu.buffListArray[i].NCP_POINTER(VAstart))
            && (taskAddr < pPoolEntry->u.cpu.buffListArray[i].NCP_POINTER(VAend)))
        {
            ncp_task_bufflist_t *pBuffList
                = &pPoolEntry->u.cpu.buffListArray[i];
            ncp_buffDescriptor_t *pBuffDesc;

            /* Normalize pointer to get start of buffer */
            taskAddr = (void *)
                ((ncp_uintptr_t)(taskAddr)
                & pPoolEntry->u.cpu.buffListArray[i].NCP_POINTER(mask));

            NCP_TASK_TBR_STATE_PTRS_INIT();
            NCP_TASK_TBR_INIT_BUFFER_STATES(pTbr, pvtTqsHdl->pProcess->pid, NCP_TASK_TBR_STATE_FREE);
            NCP_TASK_TBR_BUFFER_STATE_PREFETCH(
                pvtTqsHdl,
                taskAddr,
                pPoolEntry->poolId,
                0,
                pTbr);
                                             
            pBuffDesc =  (ncp_buffDescriptor_t *)taskAddr;

            /* Found the range, so add it to the free list */

#ifdef NCP_TASK_CPU_POOL_IS_LIFO
            pBuffDesc->next     = (struct ncp_buffDescriptor_s *)pBuffList->NCP_POINTER(free);
            pBuffList->NCP_POINTER(free) = pBuffDesc;
#else
            {
                if (NULL != pBuffList->NCP_POINTER(free))
                {
                   ncp_buffDescriptor_t *pBuffDesc2 = pBuffList->last;

                   pBuffList->last
                        = pBuffDesc2->next
                        = pBuffDesc;
                }
                else
                {
                   pBuffList->NCP_POINTER(free)
                        = pBuffList->last
                        = pBuffDesc;
                }
                pBuffDesc->next = NULL;
            }
#endif
            pBuffList->numFree++;
            validBuff = TRUE;
            break;
        }
    }
    if (TRUE == validBuff)
    {
        NCP_TASK_TBR_BUFFER_STATE_UPDATE(pTbr, FALSE);
    }    
    else    
    {
        NCP_CALL(NCP_ST_INVALID_BUFF_FOR_TASK_FREE);
    }

NCP_RETURN_LABEL

    return(ncpStatus);
}

NCP_INLINE ncp_st_t
ncp_task_get_size_bits(
        ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
		void *taskAddr, ncp_uint8_t *pSizeBits,
		ncp_uint32_t poolId)
{
    ncp_task_pool_t *pPoolEntry;
   
    int i;
    
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;
    
    if (poolId > NCP_NCAV3_LAST_CPU_POOL_ID)
    {   
        NCP_CALL(NCP_ST_INVALID_VALUE);         
    }    
    else if (poolId < NCP_NCAV3_FIRST_CPU_POOL_ID)
    {
        /* not a cpu pool */
        *pSizeBits = 0;
        NCP_JUMP_RETURN();
    }  
        
    pPoolEntry = &pNcpTaskSwState->taskPools[pvtTqsHdl->cpuPoolId];    
    if ((NULL == pPoolEntry) || (NCP_POOL_KEY != pPoolEntry->poolKey))
    {
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_get_size_bits_badPoolEntryPtr,
                              NCP_MSG_ERROR,
                              "ncp_task_get_size_bits called with bad pool entry ptr =0x%p\r\n",
                              pPoolEntry);
        NCP_CALL(NCP_ST_INVALID_HANDLE);
    }
        
    if (   ((ncp_uintptr_t)taskAddr >  (ncp_uintptr_t)(pPoolEntry->poolVAEnd)) 
        || ((ncp_uintptr_t)taskAddr <  (ncp_uintptr_t)(pPoolEntry->poolVA)))
    {
        NCP_CALL(NCP_ST_INVALID_VALUE);
    }    
        
    for (i=0; i < NCP_TASK_NUM_BUFF_SIZES; i++)
    {
        if ((taskAddr >= pPoolEntry->u.cpu.buffListArray[i].NCP_POINTER(VAstart))
            && (taskAddr < pPoolEntry->u.cpu.buffListArray[i].NCP_POINTER(VAend)))
        {  
            *pSizeBits = i;
            break;
        }
        
    }
NCP_RETURN_LABEL    
    return(ncpStatus);
}

NCP_INLINE
ncp_st_t
ncp_task_single_complete(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
                    ncp_task_pcq_t             *p_oPCQ,
                    ncp_uint32_t               *pNumTasksCompleted,
                    ncp_bool_t                 wait)     
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;   
    opcq_entry_overlay_t *pEntry;  
    ncp_bool_t needPollStateReset = TRUE;
    

    if (p_oPCQ->u.opcq_info.sendDoneCnt)
    {
        NCP_TASK_UPDATE_NUM_TX_ENTRIES_AVAIL(pvtTqsHdl, p_oPCQ);
    }
    
    /* Set up what will be the contents of the oPCQ entry - exactly the same for each */
    
    pEntry = (opcq_entry_overlay_t *)p_oPCQ->u.opcq_info.pOPCQentry;    
    pEntry->u.opcqEntry.taskAddress = (ncp_uint64_t) 0LL;   /* TODO: Probably not required since this is a NO-OP request */ 
    pEntry->u.opcqDword[1] = pvtTqsHdl->taskCompleteDefaultCmdBits.u.opcqDword[1];
        
    do
    {
        if (0 != p_oPCQ->u.opcq_info.numTxAvail)
        {
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
            break;
        }    
    } while(1);   

    p_oPCQ->u.opcq_info.numTxAvail--;
    
    NCP_TASK_FILL_PER_OPCQ_AUX_DATA(NULL, 
                                    p_oPCQ);                

    NCP_TASK_OPCQ_UPDATE_CACHED_PIDX(p_oPCQ);

    NCP_TASK_OPCQ_ISSUE_BARRIER_AND_WRITE_PIDX(p_oPCQ);
    
    *pNumTasksCompleted = 1;    
    return(NCP_ST_SUCCESS);
    /* optimization */

NCP_RETURN_LABEL

    *pNumTasksCompleted = 0;
    return(ncpStatus);        
}  

NCP_INLINE
ncp_st_t
ncp_task_single_task_send(
                ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
                ncp_task_pcq_t *p_oPCQ,
                ncp_uint32_t numTasks,
                ncp_uint32_t *pNumTasksSent,
                ncp_task_send_meta_t *pMetadata,
                ncp_int32_t *pCompletionsIssued,
                ncp_bool_t wait)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    opcq_entry_overlay_t *pEntry;
    ncp_bool_t needPollStateReset = TRUE;
    ncp_int32_t completionsIssued=0;
    NCP_TASK_TBR_STATE_PTRS_DECL()    
    
    if (p_oPCQ->u.opcq_info.sendDoneCnt)
    {
        NCP_TASK_UPDATE_NUM_TX_ENTRIES_AVAIL(pvtTqsHdl, p_oPCQ);
    }        
        
    do
    {
        if (0 != p_oPCQ->u.opcq_info.numTxAvail)
        {
            break;
        }
                
        /* update num entries available */
        /* NCP_TASK_UPDATE_NUM_TX_ENTRIES_AVAIL(pvtTqsHdl, p_oPCQ); */

        ({
            ncp_uint8_t _strippedConsumerVal;
            ncp_uint8_t _strippedProducerVal = p_oPCQ->hwProducerVal & NCP_PCQ_TOGGLE_BIT_MASK;
            /* refresh cached consumer idx */
            p_oPCQ->hwConsumerVal = *(p_oPCQ->pConsumerIdx);
            _strippedConsumerVal = p_oPCQ->hwConsumerVal & NCP_PCQ_TOGGLE_BIT_MASK;
            /* compute number of available txQ entries */
            if (_strippedProducerVal == _strippedConsumerVal)
            {
                if (p_oPCQ->hwConsumerVal == p_oPCQ->hwProducerVal)
                {
                    /* if toggle bit is the same,  then queue is (empty) 100% full of available entries */
                    p_oPCQ->u.opcq_info.numTxAvail = p_oPCQ->nEntries;
                }
                else
                {
                    p_oPCQ->u.opcq_info.numTxAvail = 0;
                }
            }
            else if (_strippedProducerVal > _strippedConsumerVal)
            {
                p_oPCQ->u.opcq_info.numTxAvail = ((p_oPCQ->nEntries) - _strippedProducerVal) + _strippedConsumerVal;
            }
            else
            {
                p_oPCQ->u.opcq_info.numTxAvail = _strippedConsumerVal - _strippedProducerVal;
            }
            /* process completed sends */
            ncp_task_process_oPCQ_aux_entries(pvtTqsHdl, p_oPCQ);
        });
        
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
            break;  /* we have at least one entry available */
        }    
    } while(1);
        
    /* It is possible for the send done array to be full, so test it early. */
    if (pMetadata->sendDoneFn)
    {
        NCP_CALL(NCP_TASK_ADD_SEND_DONE(pvtTqsHdl,
                               p_oPCQ->u.opcq_info.relId,
                               NCP_TASK_TASK_CALLBACK,
                               pMetadata->sendDoneFn,
                               pMetadata->sendDoneArg,
                               pMetadata->taskHeader,
                               0,
                               0));
    } 
                
    NCP_TASK_VALIDATE_OUTPUT_TASK(pvtTqsHdl, pMetadata->taskHeader);

    NCP_TASK_TBR_STATE_PTRS_INIT();             
    NCP_TASK_TBR_TXTASK_STATE_PREFETCH(pvtTqsHdl, 
                                     pMetadata->taskHeader, 
                                     pMetadata->freeHeader, 
                                     pMetadata->freeDataPointers,
                                     p_oPCQ,
                                     pTbr);
                                                              
    /* 
     * Set task address and default opcq entry fields 
     */

    pEntry = (opcq_entry_overlay_t *)p_oPCQ->u.opcq_info.pOPCQentry;    
    pEntry->u.opcqEntry.taskAddress = (ncp_uint64_t) (pMetadata->taskHeader);    
    pEntry->u.opcqDword[1] = pvtTqsHdl->taskSendDefaultCmdBits.u.opcqDword[1];
  

    /* pEntry->u.flowControlDisabled = 0; */ /* already zero */
    /* pEntry->u.opcqEntry.headerSize is currently zero */
    if ((pMetadata->taskHeader->ptrCnt > 2) || (1 == pMetadata->taskHeader->debugValid))
    {
        pEntry->u.opcqEntry.headerSize = 1; /* 128B */            
    }
      
    pEntry->u.opcqEntry.headerPool = pMetadata->taskHeader->headerPool;
    pEntry->u.opcqEntry.headerPoolMref = pMetadata->taskHeader->headerPoolMref;

    pEntry->u.opcqEntry.headerSeparate = !pMetadata->taskHeader->combinedHeader;
    
    /* pEntry->u.opcqEntry.taskCompletion is currently zero */
    if (pMetadata->issueCompletion)
    {   
        NCP_TASKIO_CHECK((FALSE == pvtTqsHdl->pTqs->rxQ.u.ipcq_info.autoCompletionMode),
                     NCP_ST_TASK_RX_QUEUE_IS_AUTOMATIC_COMPLETION);
        NCP_TASKIO_CHECK(1 <= pvtTqsHdl->completionsOwed,
                     NCP_ST_TASK_TOO_MANY_TASK_COMPLETIONS);
        completionsIssued = 1;                      
        pEntry->u.opcqEntry.taskCompletion = 1;
    }  
    
    /* pEntry->u.opcqEntry.forceCopy is currently zero */      
    if (pMetadata->sendDoneFn)
    {    
        pEntry->u.opcqEntry.forceCopy = 1;
    }
    
    /* pEntry->u.opcqEntry.returnHeader = NCP_NCAV3_SENDTH_RCCH_DEC_REFCNT_RETURN_HDR; */ /* already zero */
    /* pEntry->u.opcqEntry.quotaIncludeHeader = NCP_NCAV3_SENDTH_MQGI_INCL_HDR; */        /* already zero */                          
    if (0 == pMetadata->freeHeader)
    {
        pEntry->u.opcqEntry.returnHeader = NCP_NCAV3_SENDTH_RCCH_NOOP_REFCNT_KEEP_HDR;
        pEntry->u.opcqEntry.quotaIncludeHeader = NCP_NCAV3_SENDTH_MQGI_EXCL_HDR;
    }

    /* pEntry->u.opcqEntry.returnData    = NCP_NCAV3_SENDTH_RCCD_DEC_REFCNT_RETURN_DATA; */ /* already zero */
    /* pEntry->u.opcqEntry.quotaTransfer = NCP_NCAV3_SENDTH_MQGC_DEC_SOURCE;             */ /* already zero */            
    if (0 == pMetadata->freeDataPointers)
    {
        pEntry->u.opcqEntry.returnData    = NCP_NCAV3_SENDTH_RCCD_NOOP_REFCNT_KEEP_DATA;
        pEntry->u.opcqEntry.quotaTransfer = NCP_NCAV3_SENDTH_MQGC_NOOP;
    }         

    NCP_TASK_TBR_BUFFER_STATE_UPDATE_MREF(pTbr);

    if (NULL == pMetadata->sendDoneFn)
    {
        NCP_TASK_FILL_PER_OPCQ_AUX_DATA(NULL, 
                                        p_oPCQ);                
    }  
    else
    {
        NCP_TASK_FILL_PER_OPCQ_AUX_DATA(pvtTqsHdl, 
                                        p_oPCQ);               
    }

    NCP_TASK_OPCQ_UPDATE_CACHED_PIDX(p_oPCQ);

    
    NCP_TASK_OPCQ_ISSUE_BARRIER_AND_WRITE_PIDX(p_oPCQ);
    
    p_oPCQ->u.opcq_info.numTxAvail--;
    
   /*
    * NOTE;   This is the SUCCESS PATH,  and return a hardcoded NCP_ST_SUCCESS status
    * code in order to shave a few cycles in this performance critical API support function!
    */
      
          
    *pCompletionsIssued = completionsIssued;
    *pNumTasksSent = 1;
    return(NCP_ST_SUCCESS);   /* Non-typical early return */
        
NCP_RETURN_LABEL

    /*
     * NOTE;   This is the ERROR PATH.   We know ncpStatus is not equal to NT_ST_SUCCESS, 
     * so this code is structured as such in order to shave a few cycles in this 
     * performance critical API support function!
     */
    *pCompletionsIssued = *pNumTasksSent = 0;                
    return(ncpStatus);
         
}

NCP_INLINE 
ncp_st_t
ncp_task_free_single_by_metadata(
                ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
                ncp_task_pcq_t *p_oPCQ,
                ncp_uint32_t *pNumTasksFreed,
                ncp_task_free_meta_t *pMetadata,
                ncp_bool_t wait)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    opcq_entry_overlay_t *pEntry;
    ncp_task_header_t *thisHeader;
    ncp_uint32_t numCompleted = 0;
    ncp_bool_t needPollStateReset = TRUE;
    ncp_task_api_class_t apiClass;
    NCP_MUTEX_LOCKED_FLAG_DECL(unlockRequired);
    NCP_TASK_TBR_STATE_PTRS_DECL()
    NCP_TASK_LOCK_FLAGS(txqLockFlags);   
          

    if (p_oPCQ->shared)
    {
        NCP_CALL(NCP_TASK_CLAIM_LOCK_HDL(&p_oPCQ->qLock, txqLockFlags, &unlockRequired));
    }    
     
    if (p_oPCQ->u.opcq_info.sendDoneCnt)
    {
        NCP_TASK_UPDATE_NUM_TX_ENTRIES_AVAIL(pvtTqsHdl, p_oPCQ);
    }
    
    do
    {
        if (0 != p_oPCQ->u.opcq_info.numTxAvail)
        {
            break;
        } 
               
        /* update num entries available */
        NCP_TASK_UPDATE_NUM_TX_ENTRIES_AVAIL(pvtTqsHdl, p_oPCQ);
        if (0 == p_oPCQ->u.opcq_info.numTxAvail) 
        {
            
            if (wait)
            { 
                ncp_st_t tmpStatus;   

                if (pvtTqsHdl->cpuPoolHdl)
                {    
                    apiClass = NCP_TASK_API_CLASS_REFILL_TXQ0 + p_oPCQ->u.opcq_info.relId;
                }
                else
                {
                    apiClass = NCP_TASK_API_CLASS_FREE_TXQ0 + p_oPCQ->u.opcq_info.relId;        
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
            break;
        }    
    } while(1);
        

    /* It is possible for the send done array to be full, so test it early. */
    if (pMetadata->freeDoneFn)
    {
         NCP_CALL(NCP_TASK_ADD_SEND_DONE(pvtTqsHdl,
                               p_oPCQ->u.opcq_info.relId,
                               NCP_TASK_TASK_CALLBACK,
                               pMetadata->freeDoneFn,
                               pMetadata->freeDoneArg,
                               0, 0, 0));
    }

    thisHeader = pMetadata->task;

    NCP_TASK_VALIDATE_OUTPUT_TASK(pvtTqsHdl, thisHeader);
            
    NCP_TASK_TBR_STATE_PTRS_INIT();
    NCP_TASK_TBR_TXTASK_STATE_PREFETCH(pvtTqsHdl, 
                                     thisHeader, 
                                     pMetadata->freeHeader, 
                                     TRUE, 
                                     p_oPCQ,
                                     pTbr);

    /*
     * Set up task address and default contents of the oPCQ entry
     */
    pEntry = (opcq_entry_overlay_t *)p_oPCQ->u.opcq_info.pOPCQentry;     
    pEntry->u.opcqEntry.taskAddress = (ncp_uint64_t)thisHeader; 
    pEntry->u.opcqDword[1]          = pvtTqsHdl->taskFreeDefaultCmdBits.u.opcqDword[1];
    
    /* Set up variable portion of oPCQ entry */

    pEntry->u.opcqEntry.headerSeparate  = !thisHeader->combinedHeader;
    pEntry->u.opcqEntry.headerSize      = thisHeader->debugValid || (thisHeader->ptrCnt > 2); /* 0-> 64B, 1 -> 128B */
    pEntry->u.opcqEntry.headerPool      = thisHeader->headerPool;
    pEntry->u.opcqEntry.headerPoolMref  = thisHeader->headerPoolMref;    

    pEntry->u.opcqEntry.cmd = NCP_NCAV3_CMD_ADPAH;
    pEntry->u.opcqEntry.interruptEn = 1;
    /* pEntry->u.opcqEntry.flowControlDisabled = 0; */                  /* already zero */
    /* entry.quotaIncludeHeader    = NCP_NCAV3_ADPAH_MQGI_INCL_HDR; */  /* already zero */
    pEntry->u.opcqEntry.returnData     = NCP_NCAV3_ADPAH_RCCD_DEC_REFCNT;
    pEntry->u.opcqEntry.quotaTransfer  = NCP_NCAV3_ADPAH_MQGC_DEC_SOURCE;    
     
    
    /* pEntry->u.opcqEntry.returnHeader = NCP_NCAV3_ADPAH_RCCH_DEC_REFCNT_RETURN_HDR; */ /* already zero */
    if (!pMetadata->freeHeader)
    {
        NCP_CHECK((FALSE == thisHeader->combinedHeader),
                NCP_ST_TASK_HEADER_IS_NOT_SEPARATE);
        pEntry->u.opcqEntry.returnHeader = NCP_NCAV3_ADPAH_RCCH_NOOP_REFCNT_KEEP_HDR;
        pEntry->u.opcqEntry.quotaIncludeHeader = NCP_NCAV3_ADPAH_MQGI_EXCL_HDR;
    }
    
    /* pEntry->u.opcqEntry.taskCompletion = 0; */ /* already zero */
    if (pMetadata->issueCompletion)
    {
        NCP_TASKIO_CHECK((FALSE == pvtTqsHdl->pTqs->rxQ.u.ipcq_info.autoCompletionMode),
                     NCP_ST_TASK_RX_QUEUE_IS_AUTOMATIC_COMPLETION);                
        NCP_TASKIO_CHECK(1 <= pvtTqsHdl->completionsOwed,
                     NCP_ST_TASK_TOO_MANY_TASK_COMPLETIONS);
        pEntry->u.opcqEntry.taskCompletion = 1;
        numCompleted = 1;
    }

    NCP_TASK_TBR_BUFFER_STATE_UPDATE_MREF(pTbr);  /* must be done before pgit update! */
    
    if (pMetadata->freeDoneFn)
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

    NCP_TASK_OPCQ_ISSUE_BARRIER_AND_WRITE_PIDX(p_oPCQ);
    p_oPCQ->u.opcq_info.numTxAvail--;
     
    /*
     * NOTE;   This is the SUCCESS PATH,  and return a hardcoded NT_ST_SUCCESS status
     * code in order to shave a few cycles in this performance critical API support function!
     */
      
    if (numCompleted)
    {    
        pvtTqsHdl->completionsIssued[p_oPCQ->u.opcq_info.relId] += numCompleted;
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_free_single_by_metadata_txCompletionsInfo,
                              NCP_MSG_DEBUG,
                              "In free: TxQ_%d completions issued incremented by %d, total = %"PRIx64"\r\n",
                              p_oPCQ->u.opcq_info.relId,
                              numCompleted,
                              pvtTqsHdl->completionsIssued[p_oPCQ->u.opcq_info.relId]);
    }

    *pNumTasksFreed = 1;
    NCP_TASK_INC_STAT(pvtTqsHdl->pTqs, api_task_free_ok); 
    NCP_TASK_ADD_TXSTAT(pvtTqsHdl->pTqs, TaskFrees, p_oPCQ->u.opcq_info.relId, 1);         

    NCP_CLEANUP_MUTEX_CALL(NCP_TASK_FREE_LOCK_HDL(&p_oPCQ->qLock, txqLockFlags, &unlockRequired));
    return(ncpStatus);   /* Non-typical early return! */
                    
NCP_RETURN_LABEL

    /*
     * NOTE;   This is the ERROR PATH.   We know ncpStatus is not equal to NT_ST_SUCCESS, 
     * so this code is structured as such in order to shave a few cycles in this 
     * performance critical API support function!
     */
     
    *pNumTasksFreed = 0;
    NCP_TASK_INC_ERROR_STAT_VIA_PTQSHDL(pvtTqsHdl,  api_task_free_err);      

    NCP_CLEANUP_MUTEX_CALL(NCP_TASK_FREE_LOCK_HDL(&p_oPCQ->qLock, txqLockFlags, &unlockRequired));
        
    return(ncpStatus);
}
#endif /* #ifndef __ncp_task_inline_funcs__ */ 
 
 
 
 
 
 
 
  
