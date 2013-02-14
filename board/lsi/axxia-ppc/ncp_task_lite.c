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


/*
 * Hardcode some defines specifically for the UBOOT minimum environment,   really should be defined in
 * a env file or make file.
 */

 

#define NCP_TASKIO_LITE_DEFINE_GLOBALS
 
#ifdef NCP_TASKIO_UBOOT_ENV


/*
 * Includes
 */

#include <stdint.h>
#include <sys/types.h>

#include "ncp_task_lite_nca_regs.h"
#include "ncp_task_lite_nca_reg_defines.h"
#include "ncp_task_lite_basetypes.h"
#endif /* 0 */

#include "ncp_task_lite.h"
#include "ncp_task_lite_pvt.h"


/*
 * Task I/O Symbols
 */

#ifdef NCP_KERNEL
NCP_EXPORT_SYMBOL(ncp_task_lite_hdl_create); 
NCP_EXPORT_SYMBOL(ncp_task_lite_hdl_remove);
NCP_EXPORT_SYMBOL(ncp_task_lite_recv_hdl_create);
NCP_EXPORT_SYMBOL(ncp_task_lite_recv_hdl_remove);
NCP_EXPORT_SYMBOL(ncp_task_lite_recv);
NCP_EXPORT_SYMBOL(ncp_task_lite_recv_done);
NCP_EXPORT_SYMBOL(ncp_task_lite_send);
NCP_EXPORT_SYMBOL(ncp_task_lite_free_send_buffers);
NCP_EXPORT_SYMBOL(ncp_task_lite_supply_rxbuffer_to_nca);
#endif


/* Define PPC variants of cache funtions if building for uboot */
#ifdef NCP_TASKIO_UBOOT_ENV
void 
ncp_cache_prefetch_L0(const void *pX)
{
    if (/*unlikely*/(!(pX)))
        return;

    __asm__ __volatile__ ("dcbt 0,%0" : : "r" (pX));    /* L0 Cache */
}

void 
ncp_cache_prefetch_L2(const void *pX)
{
    if (/*unlikely*/(!(pX)))
        return;

    __asm__ __volatile__ ("dcbt 2,%0" : : "r" (pX));    /* L2 Cache */
}

ncp_st_t
ncp_task_map_queuenum_to_pcq(ncp_task_pcq_type_t qType, ncp_uint8_t queueNum, ncp_task_pcq_t   **ppcq)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    
    /*
     * is queue value in the valid range for this type of queue?
     */
    
    if (NCP_TASK_PCQ_INPUT == qType) 
    {    
        if (NCP_X1_UBOOT_CFG_NUM_HW_INPUT_QUEUES <= queueNum)
        {        
            NCP_CALL_LITE(NCP_ST_TASK_QMAP_ERR_TOO_BIG);
        }
    } 
    else if (NCP_X1_UBOOT_CFG_NUM_HW_NONINPUT_QUEUES <= queueNum)
    {    
        {        
            NCP_CALL_LITE(NCP_ST_TASK_QMAP_ERR_TOO_BIG);
        }
    }    
        
    switch (qType)
    {
    case NCP_TASK_PCQ_INPUT:
        
        *ppcq = &pNcpNcaTaskGSM->iPCQs[queueNum];
        break;
        
    case NCP_TASK_PCQ_OUTPUT:
        
        *ppcq = &pNcpNcaTaskGSM->oPCQs[queueNum];        
        break;        
        
    case NCP_TASK_PCQ_COMPLETION:
        
        *ppcq = &pNcpNcaTaskGSM->tPCQs[queueNum];
        break;        

    case NCP_TASK_PCQ_RX_BUFFER:
        
       
        *ppcq = &pNcpNcaTaskGSM->rPCQs[queueNum];
        break;        

    case NCP_TASK_PCQ_CONFIG:

       
        *ppcq = &pNcpNcaTaskGSM->cPCQs[queueNum];
        break;        

    case NCP_TASK_PCQ_PROXY:
    default:

        NCP_CALL_LITE(NCP_ST_TASK_UNEXPECTED_QUEUE_TYPE);
    } /* switch */
    
    NCP_ASSERT_LITE((NULL != (*ppcq)->PRODUCER_PTR), NCP_ST_TASK_NULL_PCQ_PRODUCER_PTR);
    NCP_ASSERT_LITE((NULL != (*ppcq)->CONSUMER_PTR), NCP_ST_TASK_NULL_PCQ_CONSUMER_PTR);    
    
    
NCP_RETURN_LABEL
    
    return(ncpStatus);
}

#endif /* #ifdef NCP_TASKIO_UBOOT_ENV */

ncp_st_t 
ncp_task_lite_hdl_create(
    ncp_hdl_t ncpHdl,
    ncp_uint8_t     threadQueueSetId,
    ncp_task_lite_hdl_t  *taskLiteHdl)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_pvt_task_lite_hdl_t *myTaskLiteHdl=NULL;    
    ncp_nca_thread_queue_set_t  *pThreadQueueSet;

    /*
     * Has the GSM been mapped in ?
     */
    NCP_ASSERT_LITE((NULL != pNcpNcaTaskGSM), NCP_ST_TASK_NO_GSM);
    
#ifndef NCP_TASKIO_UBOOT_ENV     
    NCP_NCA_VALIDATE_NCP_HDL(ncpHdl);
#endif
         
    /*
     * Is this thread queueset in the local domain? 
     */

    NCP_ASSERT_LITE((pNcpNcaTaskGSM->myDomain ==  pNcpNcaTaskGSM->threadQueueSet[threadQueueSetId].tqsDomain),
                NCP_ST_TASK_QUESET_NOT_IN_LOCAL_DOMAIN);

    pThreadQueueSet = &pNcpNcaTaskGSM->threadQueueSet[threadQueueSetId];
    
    
    NCP_ASSERT_LITE(((pThreadQueueSet->qsAccessMode == NCP_NCA_QS_AVAILABLE) 
                || (pThreadQueueSet->qsAccessMode == NCP_NCA_QS_RAW)),
                NCP_ST_TASK_LITE_QS_NOT_AVAILABLE);

    NCP_ASSERT_LITE((NULL != (myTaskLiteHdl = (ncp_pvt_task_lite_hdl_t *)     
        task_lite_alloc_nvm_fn((sizeof(ncp_pvt_task_lite_hdl_t))))), 
                NCP_ST_TASK_NO_MALLOC_MEM);
    memset(myTaskLiteHdl, 0, sizeof(ncp_pvt_task_lite_hdl_t));

    myTaskLiteHdl->pThreadQueueSet = pThreadQueueSet;
    
#if !defined(NCP_TASKIO_UBOOT_ENV) && !defined(NCP_KERNEL)
    myTaskLiteHdl->dev = ncp_dev_hdls[((ncp_t *)ncpHdl)->id];
#else
    myTaskLiteHdl->dev = 0;
#endif
    
    pThreadQueueSet->qsAccessMode = NCP_NCA_QS_RAW;
    pThreadQueueSet->qsAccessCnt++;  
         


NCP_RETURN_LABEL

    *taskLiteHdl = (ncp_task_lite_hdl_t) myTaskLiteHdl;
    return(ncpStatus);
}        

ncp_st_t 
ncp_task_lite_hdl_remove(
    ncp_task_lite_hdl_t  taskLiteHdl)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_pvt_task_lite_hdl_t *myTaskLiteHdl = (ncp_pvt_task_lite_hdl_t *)taskLiteHdl;    
    ncp_nca_thread_queue_set_t  *pThreadQueueSet = (ncp_nca_thread_queue_set_t *)myTaskLiteHdl->pThreadQueueSet; 
    
    NCP_ASSERT_LITE(pThreadQueueSet->qsAccessMode == NCP_NCA_QS_RAW,
                NCP_ST_TASK_LITE_QS_NOT_IN_USE);
                
    pThreadQueueSet->qsAccessCnt--;
    
    if (0 == pThreadQueueSet->qsAccessCnt)
    {    
        pThreadQueueSet->qsAccessMode = NCP_NCA_QS_AVAILABLE;    
    }    
    
NCP_RETURN_LABEL

    task_lite_free_nvm_fn(myTaskLiteHdl);
    
    return(ncpStatus);
}  
	
ncp_st_t
ncp_task_lite_recv_hdl_create(
	ncp_task_lite_hdl_t  taskLiteHdl,
	ncp_uint8_t ncaQueueId,
	ncp_task_lite_rxQ_hdl_t *taskRxHdl)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_pvt_task_lite_hdl_t *myTaskLiteHdl = (ncp_pvt_task_lite_hdl_t *)taskLiteHdl;    
    ncp_task_pcq_t   *p_iPCQ;
    ncp_nca_thread_queue_set_t  *pThreadQueueSet = (ncp_nca_thread_queue_set_t *)myTaskLiteHdl->pThreadQueueSet; 
    
    NCP_ASSERT_LITE(pThreadQueueSet->qsAccessMode == NCP_NCA_QS_RAW,
                NCP_ST_TASK_LITE_QS_NOT_IN_USE);

    NCP_CALL_LITE(ncp_task_map_queuenum_to_pcq(NCP_TASK_PCQ_INPUT, ncaQueueId, &p_iPCQ));
    
    *taskRxHdl = (ncp_task_lite_rxQ_hdl_t) p_iPCQ;
        
NCP_RETURN_LABEL
    return(ncpStatus);
}  

ncp_st_t
ncp_task_lite_recv_hdl_remove(
	ncp_task_lite_hdl_t  taskLiteHdl,
	ncp_task_lite_rxQ_hdl_t taskRxHdl)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_pvt_task_lite_hdl_t *myTaskLiteHdl = (ncp_pvt_task_lite_hdl_t *)taskLiteHdl;    

    /* NO-OP: Nothing to do here */
    
NCP_RETURN_LABEL
    return(ncpStatus);
}  
	
ncp_st_t
ncp_task_lite_recv(
	ncp_task_lite_hdl_t  taskLiteHdl,
	ncp_task_lite_rxQ_hdl_t taskRxHdl,
	ncp_task_lite_recv_buf_t **task,
    void                **taskData,	
	ncp_bool_t wait)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_pvt_task_lite_hdl_t *myTaskLiteHdl = (ncp_pvt_task_lite_hdl_t *)taskLiteHdl;
    ncp_nca_thread_queue_set_t  *pThreadQueueSet = (ncp_nca_thread_queue_set_t *)myTaskLiteHdl->pThreadQueueSet;     
    ncp_task_pcq_t              *p_iPCQ = (ncp_task_pcq_t *)taskRxHdl;

    ncp_task_lite_recv_buf_t *pTask;
    ncp_task_iPCQ_entry_t *pInputQueueEntry = p_iPCQ->u.ipcq_info.pIPCQentry; 
    ncp_uint16_t          consumerVal       
        = pInputQueueEntry - ((ncp_task_iPCQ_entry_t *)p_iPCQ->P_PCQ_BASE);  /* Must calulate this way! */
                                                                             /* Consumer idx updated every 16 */  
    ncp_uint16_t          nEntries          = p_iPCQ->nEntries;
    

    while(1)
    {
        if ((*(p_iPCQ->PRODUCER_PTR)) != (consumerVal))
        {
    
            pTask = ( ncp_task_lite_recv_buf_t *)(pInputQueueEntry->bufferId);
    
            pTask->dataOffset = pInputQueueEntry->pduDataStartOffset;
    
            /* 
             * propogate vp and error info back to client 
             */
            
            pTask->templateId = pInputQueueEntry->templateId;  

    
                    
            if (nEntries == (++consumerVal))
            {    
                consumerVal = 0;
                p_iPCQ->u.ipcq_info.pIPCQentry 
                    = pInputQueueEntry 
                    = (ncp_task_iPCQ_entry_t *)(p_iPCQ->P_PCQ_BASE);             
            }
            else
            {
                p_iPCQ->u.ipcq_info.pIPCQentry = ++pInputQueueEntry;
            } 
                
            /* 
             * start of new 128B cache line 
             * or queue depth to small for optimization?
             */                
             
            if ((0 == (((ncp_uint32_t)pInputQueueEntry) & 0x7F)) 
                || (nEntries <= 16))
            {  
       
                *(p_iPCQ->CONSUMER_PTR) = consumerVal;
                if (NCP_NCA_CACHE_PRELOAD)
                {    
            
                    /*
                     * force cache load of next descriptor
                     */
                    ncp_cache_prefetch_L2((void *)pInputQueueEntry); 
                }                
            }    
            if (NCP_NCA_CACHE_PRELOAD)
            {    
            
                /* Access next descriptor (may load cache) and explicity 
                 * force cache load of 1st cache line of next task buffer 
                 */
                ncp_cache_prefetch_L2((void *)pInputQueueEntry->bufferId);
            }
            break; /* We have a task */
        }  /* queue not empty */
        else
        {
            if (wait)
            {
                NCP_TASK_LITE_BLOCK_ON_HW_INTERRUPT(myTaskLiteHdl, 
                                                    myTaskLiteHdl->dev, 
                                                    NCP_NCA_WAIT_FOR_RX_INTR, 
                                                    p_iPCQ->grpId, 
                                                    0xFF);              
            }
            else
            {
                ncpStatus = NCP_ST_TASK_RECV_QUEUE_EMPTY;        
                goto ncp_return;
            }
        }   
    } /* While(1) */

    if (p_iPCQ->u.ipcq_info.rxTaskAutoComplete)
    { 
        ncp_task_tPCQ_entry_t *pTaskCompletionInfo = (ncp_task_tPCQ_entry_t *)&p_iPCQ->u.ipcq_info.taskCompletionInfo;
        if (0 != pTaskCompletionInfo->reserved)
        {
            ncp_task_pcq_t *p_tPCQ = pThreadQueueSet->p_tPCQ;
            ncp_task_tPCQ_entry_t *pTaskCompletionQueueEntry = (ncp_task_tPCQ_entry_t  *)p_tPCQ->P_PCQ_BASE;;                
            pTaskCompletionQueueEntry = &pTaskCompletionQueueEntry[NCP_DEV_NCA_PCQ_PRODUCER_IDX(p_tPCQ)];   
                               
            do 
            {
                if (NCP_DEV_NCA_PCQ_IS_FULL(p_tPCQ))
                {  
                        NCP_TASK_LITE_BLOCK_ON_HW_INTERRUPT(myTaskLiteHdl, 
                                                    myTaskLiteHdl->dev, 
                                                    NCP_NCA_WAIT_FOR_TASK_COMPLETION_INTR, 
                                                    p_tPCQ->grpId, 
                                                    p_tPCQ->ncaQueueId);           
                        continue;
                }  
                break;      
            } while(1);  
       
                
            pTaskCompletionQueueEntry->intOnComplete   = 1;  
            pTaskCompletionQueueEntry->taskPriority    = pTaskCompletionInfo->taskPriority;
            pTaskCompletionQueueEntry->toid            = pTaskCompletionInfo->toid;    
            pTaskCompletionQueueEntry->dataSize        = pTaskCompletionInfo->dataSize;
            pTaskCompletionQueueEntry->queueId         = pTaskCompletionInfo->queueId;
            pTaskCompletionQueueEntry->completionCntInc= 0; /* we do not support oTask ordering in lite-mode */
            pTaskCompletionQueueEntry->nOp             = 0;
            pTaskCompletionQueueEntry->destId          = pTaskCompletionInfo->destId;   
            
            /*
             * Give completion to NCA 
             */
            NCP_DEV_NCA_PCQ_PIDX_ADVANCE(p_tPCQ);             
        }
        
        /*
         * Save info for next completion 
         */
        pTaskCompletionInfo->taskPriority    = (pTask)->taskPrio;
        pTaskCompletionInfo->toid            = (pTask)->TOID;    
        pTaskCompletionInfo->dataSize        = (pTask)->dataSz;
        pTaskCompletionInfo->queueId         = (pTask)->QID;
        pTaskCompletionInfo->destId          = (pTask)->destId_9_0;  
        pTaskCompletionInfo->reserved        = 1; /* internally used as a flag */
    }
            
    *task     = pTask;
    *taskData = NCP_TASK_DATA(pTask);                            

NCP_RETURN_LABEL
    return(ncpStatus);
}  

ncp_st_t
ncp_task_lite_recv_done(
	ncp_task_lite_hdl_t  taskLiteHdl,
	ncp_task_lite_recv_buf_t     *task)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_pvt_task_lite_hdl_t *myTaskLiteHdl = (ncp_pvt_task_lite_hdl_t *)taskLiteHdl;
    
NCP_RETURN_LABEL
    return(ncpStatus);
}  


ncp_st_t
ncp_task_lite_free_send_buffers(ncp_task_lite_hdl_t  taskLiteHdl)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_pvt_task_lite_hdl_t *myTaskLiteHdl = (ncp_pvt_task_lite_hdl_t *)taskLiteHdl; 
       
    ncp_task_oPCQ_entry_t  *pTaskOutputQueueEntry;  
    ncp_nca_thread_queue_set_t  *pThreadQueueSet = (ncp_nca_thread_queue_set_t *)myTaskLiteHdl->pThreadQueueSet;     
    ncp_task_pcq_t  *p_oPCQ  = pThreadQueueSet->p_oPCQ;      
    ncp_uint16_t consumerIdx = NCP_DEV_NCA_PCQ_CONSUMER_IDX(p_oPCQ);
    ncp_uint16_t nEntries = p_oPCQ->nEntries;

    if ((p_oPCQ->u.opcq_info.intransitTasksIdx == consumerIdx))
    {
        goto ncp_return;        
    }    
    else     
    {  
        ncp_uint16_t freeIdx = p_oPCQ->u.opcq_info.intransitTasksIdx;
        pTaskOutputQueueEntry = (ncp_task_oPCQ_entry_t  *) p_oPCQ->P_PCQ_BASE;
        pTaskOutputQueueEntry = &pTaskOutputQueueEntry[freeIdx];

                 
        do
        {
            /*
             * Call send done fn
             */
             
            NCP_ASSERT_LITE( NULL != pTaskOutputQueueEntry->clientFreeFn, NCP_ST_TASK_LITE_NULL_SEND_DONE_FUNCTION);
            pTaskOutputQueueEntry->clientFreeFn(pTaskOutputQueueEntry->clientFreeFnArg, pTaskOutputQueueEntry->taskBuffer);
              
            p_oPCQ->u.opcq_info.intransitSlotsAvail++;
            
            
            /* wrap ? */
            freeIdx++;
            if (freeIdx != nEntries)
            {
                 pTaskOutputQueueEntry++;
            }
            else
            {
                 freeIdx = 0;
                 pTaskOutputQueueEntry = (ncp_task_oPCQ_entry_t  *) p_oPCQ->P_PCQ_BASE;
            }

        } while (freeIdx != consumerIdx);
        p_oPCQ->u.opcq_info.intransitTasksIdx = freeIdx;
    }
   
NCP_RETURN_LABEL

    return(ncpStatus);    
}    


ncp_st_t
ncp_task_lite_send (
	ncp_task_lite_hdl_t  taskLiteHdl,
	ncp_task_lite_send_meta_t *pTaskLiteMetaData,
	ncp_bool_t wait)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_pvt_task_lite_hdl_t *myTaskLiteHdl = (ncp_pvt_task_lite_hdl_t *)taskLiteHdl;    
    ncp_nca_thread_queue_set_t  *pThreadQueueSet = (ncp_nca_thread_queue_set_t *)myTaskLiteHdl->pThreadQueueSet;     
    ncp_task_pcq_t  *p_oPCQ  = pThreadQueueSet->p_oPCQ;          
    ncp_task_oPCQ_entry_t    *pTaskOutputQueueEntry = p_oPCQ->u.opcq_info.pOPCQentry;
    volatile ncp_uint16_t    *pProducer = p_oPCQ->PRODUCER_PTR;
    ncp_uint16_t             producerVal = *pProducer;
    volatile ncp_uint16_t    *pConsumer = p_oPCQ->CONSUMER_PTR;    
    ncp_uint16_t nEntries    = p_oPCQ->nEntries;            
    void *taskData;    
    ncp_uint64_t physAddr64;
    

    while (1)
    {
        if (0 == p_oPCQ->u.opcq_info.intransitSlotsAvail) 
        {
            /* We cannot proceed until the NCA takes our outstanding buffers,   which allows us to
             * then free those buffers.   Doing otherwise will result in a task buffer leak 
             */
            NCP_CALL_LITE(ncp_task_lite_free_send_buffers(taskLiteHdl));
            if (0 == p_oPCQ->u.opcq_info.intransitSlotsAvail) 
            {
                if (FALSE == wait)
                {
                    ncpStatus = NCP_ST_TASK_SEND_QUEUE_FULL;  
                    goto ncp_return;    
                }  
                else
                {
                    NCP_TASK_LITE_BLOCK_ON_HW_INTERRUPT(myTaskLiteHdl, 
                                                myTaskLiteHdl->dev, 
                                                NCP_NCA_WAIT_FOR_TX_INTR,
                                                p_oPCQ->grpId, 
                                                p_oPCQ->ncaQueueId); 
                }                                                                  
                continue;            
            }    
        }
        break;      
   }  
   
   /*
    * Client has already encoded parameters, so just copy the meta data into the oPCQ queue entry
    */  
   memcpy(pTaskOutputQueueEntry, pTaskLiteMetaData, sizeof(ncp_task_oPCQ_entry_t));
       
   /* TODO - make part of meta data???? debug and interrupt bits */
    
   pTaskOutputQueueEntry->setTaskEr             = 0;
   pTaskOutputQueueEntry->interruptOnComplete   = 1;   
   
   /* TODO - physaddr of pdu data - should we push this back on user too???? */
    
   if (NULL != (taskData = pTaskLiteMetaData->taskPduData))
   { 
     physAddr64 = NCP_NCA_VA_2_PA_LITE(taskData);
       pTaskOutputQueueEntry->dataBufferAddr_37_32  = ((physAddr64 >> 32) & (0x0000003F));
       pTaskOutputQueueEntry->dataBufferAddr_31_0   = (physAddr64 & 0xffffffff);
   } 
   else
   {
       pTaskOutputQueueEntry->dataBufferAddr_37_32  = 0;
       pTaskOutputQueueEntry->dataBufferAddr_31_0   = 0;
   }    
        
   
    NCP_SYSMEM_BARRIER();   
    
    /* Advance producer index */    
    if (producerVal == (nEntries - 1))
    {    
       *pProducer = 0; 
        p_oPCQ->u.opcq_info.pOPCQentry = p_oPCQ->P_PCQ_BASE;                              
    }   
    else                                              
    {    
        *pProducer = producerVal + 1;     
        p_oPCQ->u.opcq_info.pOPCQentry++;                              
    }  

    p_oPCQ->u.opcq_info.intransitSlotsAvail--;
    
NCP_RETURN_LABEL

#if 0   /* TODO: Give the application control over this ???? */
    ncpStatus = ncp_task_lite_free_send_buffers(taskLiteHdl);
#endif

    return(ncpStatus);
}

ncp_st_t 
ncp_task_lite_supply_rxbuffer_to_nca(ncp_task_lite_hdl_t  taskLiteHdl,
	                         void *taskAddr,
	                         ncp_uint8_t sizeBits)
{
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;
    ncp_pvt_task_lite_hdl_t *myTaskLiteHdl = (ncp_pvt_task_lite_hdl_t *)taskLiteHdl;    
    ncp_nca_thread_queue_set_t  *pThreadQueueSet 
        = (ncp_nca_thread_queue_set_t *)myTaskLiteHdl->pThreadQueueSet;     
    ncp_task_pcq_t  *p_rPCQ  = pThreadQueueSet->p_rPCQ;    
    ncp_task_rPCQ_entry_t *pRecvBuffQueueEntry = p_rPCQ->u.rpcq_info.pRPCQentry; 
    volatile ncp_uint16_t *pConsumer = p_rPCQ->CONSUMER_PTR;
    ncp_uint16_t *pProducer = (ncp_uint16_t *)p_rPCQ->PRODUCER_PTR;     
    ncp_uint16_t nEntries   = p_rPCQ->nEntries;       
    ncp_uint64_t    taskPhysAddr64;   


    /*
     * Is there room?  
     */ 
    while(((((*pProducer) + 1) % (nEntries)) == (*pConsumer))) /* FULL */
    {
        /* TODO - sleep? */
    }

    pRecvBuffQueueEntry->bufferId = (ncp_uint32_t)taskAddr;

    taskPhysAddr64 = NCP_NCA_VA_2_PA_LITE(taskAddr);
     
    /*
     * Allocation ok
     */
      
    pRecvBuffQueueEntry->bufferSize = sizeBits; 

     
    pRecvBuffQueueEntry->bufferAddress00_31 = (ncp_uint32_t)(taskPhysAddr64 & 0xFFFFFFFF); 
    pRecvBuffQueueEntry->bufferAddress32_37 = (ncp_uint32_t)(taskPhysAddr64 >> 32) & 0x3f;

    /* 
     * Safe to advance producer pointer now,  which notifies HW that a new entry is available
     */
      
    /* Advance producer index */   
    NCP_SYSMEM_BARRIER();   
    if (*pProducer == (nEntries - 1))
    {    
       *pProducer = 0; 
        p_rPCQ->u.rpcq_info.pRPCQentry = p_rPCQ->P_PCQ_BASE;                              
    }   
    else                                              
    {    
       *pProducer = (*pProducer) + 1;
       p_rPCQ->u.rpcq_info.pRPCQentry++;                              
    }   

NCP_RETURN_LABEL

    return(ncpStatus); 
        
}



