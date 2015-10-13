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

#define NCP_TASK_USE_55XX_HEADERS

#define NCP_TASK_NCA_GLOBALS
/*
#define DEBUG
#include <common.h>

#define NCP_TASK_DEBUG_MME
*/
/* #include "ncp_dev_pvt.h" */
#if 0 /* UBOOT */
#include "ncp_dev.h"
#include "ncp_release_id.h"
#endif
#include "ncp_task_pvt.h"
#include "ncp_task_inline_funcs_axm55xx.h"

#include <watchdog.h>

/* ======
 * EXPORTS for native ncav2 APIS.
 * They are not routed through ncp_task_api_entry.c
 * TEMP: not yet implemented for socket mdoe
 */

#if !defined(NCP_DEV_SOCKET) && !defined(NCP_DEV_FBRS)
NCP_EXPORT_SYMBOL(ncp_task_ncav2_recv);
NCP_EXPORT_SYMBOL(ncp_task_ncav2_send);
NCP_EXPORT_SYMBOL(ncp_task_ncav2_buffer_alloc);
NCP_EXPORT_SYMBOL(ncp_task_ncav2_buffer_free);
NCP_EXPORT_SYMBOL(ncp_task_ncav2_recv_done);
NCP_EXPORT_SYMBOL(ncp_task_ncav2_free_rx_task);
NCP_EXPORT_SYMBOL(ncp_task_ncav2_free_pdu_segments);
#endif

/*
 * =============================
 * old ncp_task.c
 * =============================
 */

#undef  NCP_TASK_ENABLE_DEBUG /* <--------------- POTENTIALLY MASSIVE AMOUNTS OF DEBUG OUTPUT */


#if 0 /* UBOOT */
#if !defined(NCP_KERNEL) || defined(NCP_VXWORKS)
static pthread_once_t gNcaTask_key_once = PTHREAD_ONCE_INIT;
static pthread_key_t  gNcaTask_key = 0;
#endif
#endif /* UBOOT */

#if 0 /* UBOOT */
/*
 * access thread local storage
 */
#if !defined(NCP_KERNEL) || defined(NCP_VXWORKS)
static void
ncp_task_v2_make_key(void);
#endif

static void
ncp_task_v2_destroy_key(void);


static ncp_st_t
ncp_task_v2_store_taskHdl(ncp_pvt_task_hdl_t *myTaskHdl);

#endif /* UBOOT */


/* Define usable API entry points below.   FBRS and FBDEV entry points will be stubs */

ncp_st_t
ncp_task_v2_get_default_queueset(
    ncp_hdl_t       ncpHdl,
    ncp_uint8_t     *pThreadQueueSetId)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

#if defined(NCP_KERNEL) && !defined(NCP_VXWORKS)
    NCP_CALL(NCP_ST_NOT_IMPLEMENTED);
#else

    ncp_nca_t        *nca;
    int i;

    /*
     * Has the GSM been mapped in ?
     */
    NCP_CHECK((NULL != pNcpNcaV2_TaskSwState), NCP_ST_TASK_NO_GSM);

    NCP_TASK_CHECK_FOR_SHUTDOWN();

    NCP_NCA_VALIDATE_NCP_HDL(ncpHdl);

    NCP_ASSERT((NULL != (nca = (ncp_nca_t *)((ncp_t *)ncpHdl)->ncaHdl)),
                NCP_ST_NOT_CONFIGURED);

    for (i=0; i<NCP_X7_NUM_THREAD_QUEUESETS; i++)
    {
        /* This domain *and* uses a user mode buffer pool */
#if defined(NCP_KERNEL) || defined(NCP_VXWORKS)
        /* Everything is kernel mode for VxWorks */
        if (pNcpNcaV2_TaskSwState->myDomain == pNcpNcaV2_TaskSwState->threadQueueSets[i].tqsDomain)
#else
        if ((pNcpNcaV2_TaskSwState->myDomain == pNcpNcaV2_TaskSwState->threadQueueSets[i].tqsDomain)
         && (TRUE == pNcpNcaV2_TaskSwState->threadQueueSets[i].uMode))
#endif
        {
            *pThreadQueueSetId = pNcpNcaV2_TaskSwState->threadQueueSets[i].id;
            break;
        }
    }

    NCP_ASSERT((i != NCP_X7_NUM_THREAD_QUEUESETS), NCP_ST_TASK_NO_QUEUESET_IN_DOMAIN);

#endif

NCP_RETURN_LABEL
    return ncpStatus;
}

ncp_st_t
ncp_task_v2_hdl_create(
    ncp_hdl_t       ncpHdl,
    ncp_uint8_t     threadQueueSetId,
    ncp_bool_t      shared,
    ncp_task_hdl_t  *taskHdl)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_pvt_task_hdl_t *myTaskHdl=NULL;
    ncp_bool_t      unlockRequired = FALSE;
#if defined(NCP_KERNEL) && (defined(NCP_OSE) || defined(NCP_VXWORKS))
    spinlock_flags_t flags = 0;
#endif

    /*
     * Has the GSM been mapped in ?
     */
    NCP_CHECK((NULL != pNcpNcaV2_TaskSwState), NCP_ST_TASK_NO_GSM);

    NCP_TASK_CHECK_FOR_SHUTDOWN();

    NCP_NCA_VALIDATE_NCP_HDL(ncpHdl);

    /*
     * Is this thread queueset in the local domain?
     */

    NCP_CHECK((pNcpNcaV2_TaskSwState->myDomain ==  pNcpNcaV2_TaskSwState->threadQueueSets[threadQueueSetId].tqsDomain),
                NCP_ST_TASK_QUESET_NOT_IN_LOCAL_DOMAIN);

    unlockRequired = TRUE;
    NCP_TASK_CLAIM_LOCK(pNcpNcaV2_TaskSwState->taskIoResourceLock, flags);

    /*
     * Allocate memory for the task handle's internal private data
     */

    NCP_ASSERT((NULL != (myTaskHdl = (ncp_pvt_task_hdl_t *) ncp_nvm_malloc((sizeof(ncp_pvt_task_hdl_t))))),
                NCP_ST_TASK_NO_MALLOC_MEM);
    ncp_memset(myTaskHdl, 0, sizeof(ncp_pvt_task_hdl_t));

    NCA_INC_CRITICAL_SECTION(myTaskHdl);

    myTaskHdl->cookie       = NCP_TASK_HDL_COOKIE;
    myTaskHdl->ncpHdl       = ncpHdl;
    myTaskHdl->dev          = ncp_dev_hdls[((ncp_t *)ncpHdl)->id];

    /*
     * Treat all kernel mode task handles as shared initially.   The app
     * can disable the locking specifically if it is truly single threaded.
     * With NcaV1,  an applciation with exactly 1 send only thread and
     * exactly 1 receive only thread could both use the same non-shared
     * task handle provided ordered output was FALSE.   This same model
     * will not work with NcaV2,  since the oPCQ is now overloaded with
     * many new functions; task completion, deallocate, ....
     */
    if (FALSE == pNcpNcaV2_TaskSwState->inUmode)
    {
        shared = TRUE;
    }

    /*
     * Create queueset's output bindings, and get poolID in task hdl
    */

    NCP_CALL(ncp_task_v2_output_queueset_bind(myTaskHdl,
	                               shared,
	                               threadQueueSetId));

#if !defined(NCP_DEV_SOCKET) && !defined(NCP_DEV_FBRS)

    /*
     * Map in task memory pool
     */
    if (FALSE == memPoolMapped[myTaskHdl->poolID])
    {
        ncp_task_ncaV2_pool_t *pPoolEntry
         = &pNcpNcaV2_TaskSwState->taskMemoryPool[myTaskHdl->poolID];

        void *tmpPtr=NULL;

#ifdef NCP_KMODE_DEBUG
    NCP_LOG(NCP_MSG_INFO, "Calling MEM_MAP with dev=%p, VA=%p, sz=%llx, PA=%llx\r\n",
            myTaskHdl->dev,
            (void *)(ncp_raw_addr_t)pPoolEntry->pool_VA,
            pPoolEntry->pool_Size,
            pPoolEntry->pool_PA);
#endif

        tmpPtr
	  = (void *)(unsigned)
             NCP_TASK_MEM_MMAP(myTaskHdl->dev,
                          (void *)(ncp_raw_addr_t)pPoolEntry->pool_VA,
                          pPoolEntry->pool_Size,
                          pPoolEntry->pool_PA);

        if (pNcpNcaV2_TaskSwState->inUmode)
        {
            NCP_ASSERT(tmpPtr == (void *)pPoolEntry->pool_VA, NCP_ST_TASK_MMAP_FAILED);
        }
        else
        {
            /* We do not peg VAs in kernel mode */
            NCP_ASSERT(tmpPtr != NULL, NCP_ST_TASK_MMAP_FAILED);
            pPoolEntry->pool_VA = (ncp_raw_addr_t)tmpPtr;
            pPoolEntry->pool_EndVA
                = pPoolEntry->pool_VA + pPoolEntry->pool_Size;
        }
        /* so we do not map more than once per process */
        memPoolMapped[myTaskHdl->poolID] = TRUE;

#ifdef NCP_TASK_PRINT_BASE_ADDRESSES_AND_MAPPINGS
        NCP_MSG(NCP_MSG_INFO, "mapped taskMemoryPool %d at VA %p\r\n",
                myTaskHdl->poolID,
                (void *)pPoolEntry->pool_VA);
#endif
    }

    NCP_CALL(ncp_task_attach_mme_allocator(myTaskHdl));

#endif

    /*
     * Store task handle in thread local storage
     */

    NCP_CALL(ncp_task_v2_store_taskHdl(myTaskHdl));

    /*
     * Success: Return pointer to caller
     */

    *taskHdl = (void *)myTaskHdl;

    /*
     * maintain list of active task handles for use during warm restart
     */
    myTaskHdl->next = pNcpNcaV2_TaskSwState->activeTaskHdlList;
    pNcpNcaV2_TaskSwState->activeTaskHdlList = myTaskHdl;

NCP_RETURN_LABEL

    if (unlockRequired)
    {
        NCP_TASK_FREE_LOCK(pNcpNcaV2_TaskSwState->taskIoResourceLock, flags);
    }

    NCA_DEC_CRITICAL_SECTION(myTaskHdl);

    if (NCP_ST_SUCCESS == ncpStatus)
    {
        NCP_TASK_INC_STAT(api_task_hdl_create_ok);
    }
    else
    {
        if (myTaskHdl)
        {
            ncp_nvm_free(myTaskHdl);
        }
        NCP_TASK_INC_STAT(api_task_hdl_create_err);
    }

    return ncpStatus;
}


ncp_st_t
ncp_task_v2_hdl_remove(
	ncp_task_hdl_t taskHdl)
{
    ncp_st_t ncpStatus= NCP_ST_SUCCESS;
    ncp_pvt_task_hdl_t *myTaskHdl = (ncp_pvt_task_hdl_t *)taskHdl;
    ncp_bool_t      unlockRequired = FALSE;
#if defined(NCP_KERNEL) && (defined(NCP_OSE) || defined(NCP_VXWORKS))
    spinlock_flags_t flags = 0;
#endif

    if (NULL == pNcpNcaV2_TaskSwState)
    {
        goto ncp_return;    /* do nothing */
    }

    NCP_CALL(ncp_task_v2_get_taskHdl((void *)&myTaskHdl));

    NCA_INC_CRITICAL_SECTION(myTaskHdl);

    /*
     * Active iPCQs?
     */

    if (myTaskHdl->currRecvPtr)
    {
        NCP_CALL(NCP_ST_HANDLE_IN_USE);
    }

    /*
     * Unbind the thread queue set
     */

     unlockRequired = TRUE;
     NCP_TASK_CLAIM_LOCK(pNcpNcaV2_TaskSwState->taskIoResourceLock, flags);

     ncp_task_v2_output_queueset_unbind(myTaskHdl);

     /*
      * Free the memory and destroy the thread storage key
      */

     ncp_task_v2_destroy_key();

    /*
     * Update list of active task handles
     */

    {
        ncp_pvt_task_hdl_t *currTaskHdl = pNcpNcaV2_TaskSwState->activeTaskHdlList;
        ncp_pvt_task_hdl_t *prevTaskHdl = NULL;

        while(currTaskHdl != NULL)
        {
            if (currTaskHdl == myTaskHdl)
            {
                if (prevTaskHdl)
                {
                    prevTaskHdl->next = currTaskHdl->next; /* unlink */
                }
                else
                {
                     pNcpNcaV2_TaskSwState->activeTaskHdlList = currTaskHdl->next;
                }
                break;
            }
            else
            {
                prevTaskHdl = currTaskHdl;
                currTaskHdl = currTaskHdl->next;
            }
        }
    }

    NCP_CALL(ncp_task_detach_mme_allocator(myTaskHdl));

     /*
      * Since myTaskHdl was created in kernel mode, the previous
      * call to ncp_task_v2_destroy_key() and this call to ncp_nvm_free()
      * are freeing the same handle.
      */
     ncp_nvm_free(myTaskHdl);

NCP_RETURN_LABEL

    if (unlockRequired)
    {
        NCP_TASK_FREE_LOCK(pNcpNcaV2_TaskSwState->taskIoResourceLock, flags);
    }

    if (NCP_ST_SUCCESS == ncpStatus)
    {
        NCP_TASK_INC_STAT(api_task_hdl_remove_ok);
    }
    else
    {
        NCP_TASK_INC_STAT(api_task_hdl_remove_err);
    }

    /* NOTE: No need to dec critical section counter here,  since we just free'd the task handle */

    return ncpStatus;
}

ncp_st_t
ncp_task_v2_send_mutex_disable(
	ncp_task_hdl_t taskHdl)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_pvt_task_hdl_t *myTaskHdl = (ncp_pvt_task_hdl_t *)taskHdl;

    myTaskHdl->pThreadQueueSet->sendMutexDisabled = TRUE;

NCP_RETURN_LABEL

    if (NCP_ST_SUCCESS == ncpStatus)
    {
        NCP_TASK_INC_STAT(api_send_mutex_disable_ok);
    }
    else
    {
        NCP_TASK_INC_STAT(api_send_mutex_disable_err);
    }
    return(ncpStatus);
}

ncp_st_t
ncp_task_v2_recv_queue_bind(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t ncaQueueId,
	ncp_uint8_t weight,
	ncp_bool_t shared,
	ncp_bool_t fixedRecvQueueId,
	ncp_uint8_t *pRecvQueueId)
{
    ncp_st_t ncpStatus= NCP_ST_SUCCESS;
    ncp_pvt_task_hdl_t *myTaskHdl = (ncp_pvt_task_hdl_t *)taskHdl;
    ncp_pvt_task_recv_queue_t *recvQueue=NULL;
    ncp_task_pcq_t   *p_iPCQ;
    ncp_bool_t      unlockRequired = FALSE;
#if defined(NCP_KERNEL) && (defined(NCP_OSE) || defined(NCP_VXWORKS))
    spinlock_flags_t flags = 0;
#endif

    NCP_CHECK((NULL != pNcpNcaV2_TaskSwState), NCP_ST_TASK_NO_GSM);

    NCP_CALL(ncp_task_v2_get_taskHdl((void *)&myTaskHdl));

    if (shared)
    {
        NCP_CALL(NCP_ST_TASK_SHARED_RECEIVE_QUEUES_NOT_SUPPORTED);
    }

    NCA_INC_CRITICAL_SECTION(myTaskHdl);

    NCP_TASK_CHECK_FOR_SHUTDOWN();

    NCP_CHECK((NULL != pRecvQueueId), NCP_ST_TASK_NULL_RECVQUEUEID_PTR);

#if 0 /* We now allow requesting fixed ID's in the dynamic range - needed for warm restart by ADK packet handler */
    if (TRUE == fixedRecvQueueId)
    {
        NCP_CHECK(((*pRecvQueueId) & NCP_RECV_QUEUE_FIXEDBIT),NCP_ST_TASK_INVALID_FIXED_QUEUEID); /* is fixed bit set in ID ? */
    }
#endif


    if (((int)ncaQueueId) >= NCP_X7_NUM_HW_INPUT_QUEUES)
    {
        NCP_CALL(NCP_ST_TASK_INVALID_NCA_INPUT_QUEUE);
    }

    if ((ncaQueueId < myTaskHdl->pThreadQueueSet->first_iPCQ_id)
        || (ncaQueueId > (myTaskHdl->pThreadQueueSet->first_iPCQ_id + (myTaskHdl->pThreadQueueSet->num_iPCQs_in_queueSet - 1))))
    {
        NCP_CALL(NCP_ST_TASK_RECV_QUEUE_NOT_IN_QUEUESET);
    }

    unlockRequired = TRUE;
    NCP_TASK_CLAIM_LOCK(pNcpNcaV2_TaskSwState->taskIoResourceLock, flags);

    /*
     * Map linear queue number to internal pcq struct
     * Validate requested binding is appropriate for the NCA Queue.
     */
    NCP_CALL(ncp_task_v2_map_queuenum_to_pcq(NCP_TASK_PCQ_INPUT, ncaQueueId, &p_iPCQ));
    NCP_CALL(ncp_task_v2_validate_input_queue_binding(p_iPCQ));

    NCP_ASSERT((NULL != (recvQueue =  (ncp_pvt_task_recv_queue_t *)
                     ncp_nvm_malloc((sizeof(ncp_pvt_task_recv_queue_t))))),
                            NCP_ST_TASK_NO_MALLOC_MEM);
    ncp_memset(recvQueue, 0, sizeof(ncp_pvt_task_recv_queue_t));


    recvQueue->cookie   = NCP_TASK_RECV_QUEUE_COOKIE;   /* For Sanity Checking          */
    recvQueue->next     = NULL;                         /* No WRR list defined yet      */
    recvQueue->ncaQueueId   = ncaQueueId;               /* Which NCA Task Input Queue   */
    if (0 == (recvQueue->weight = weight))              /* Specified by caller          */
    {
        recvQueue->weight = 1;
    }

    /*
     * Allocate, initialize, and hook the new queue to the active queue list on the receive handle.
     * Create and initialize a S/W PCQ
     */

    NCP_CALL(
        ncp_task_v2_initialize_sw_task_input_queue(myTaskHdl,
                                           recvQueue,
                                           p_iPCQ,
                                           fixedRecvQueueId,
                                           pRecvQueueId));

    /*
     * TODO - fixme set up rxBufferPool shared settings
     */

NCP_RETURN_LABEL

    if (NCP_ST_SUCCESS == ncpStatus)
    {
        /* need to use group relative ipcq index here */
        myTaskHdl->myIPCQmask |= (1ULL << (ncaQueueId));
        NCP_TASK_INC_STAT(api_recv_queue_bind_ok);
    }
    else
    {
        NCP_TASK_INC_STAT(api_recv_queue_bind_err);

        /*
         * Perform cleanup and free any resources that were allocated in this routine
         */

        if (NULL != recvQueue)
        {
            ncp_nvm_free(recvQueue);
        }
    }

    if (unlockRequired)
    {
        NCP_TASK_FREE_LOCK(pNcpNcaV2_TaskSwState->taskIoResourceLock, flags);
    }

    NCA_DEC_CRITICAL_SECTION(myTaskHdl);

    return ncpStatus;
}

ncp_st_t
ncp_task_v2_recv_queue_unbind(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t recvQueueId)
{
    ncp_st_t ncpStatus= NCP_ST_SUCCESS;
    ncp_pvt_task_recv_queue_t   *recvQueuePtr;
    ncp_pvt_task_recv_queue_t   *tmpRecvQueuePtr;
    ncp_task_pcq_t              *p_iPCQ;
    ncp_pvt_task_hdl_t *myTaskHdl = (ncp_pvt_task_hdl_t *)taskHdl;
    ncp_bool_t      unlockRequired = FALSE;
    ncp_uint8_t     ncaQueueId=0xff;
#if defined(NCP_KERNEL) && (defined(NCP_OSE) || defined(NCP_VXWORKS))
    spinlock_flags_t flags = 0;
#endif

    NCP_CHECK((NULL != pNcpNcaV2_TaskSwState), NCP_ST_TASK_NO_GSM);

    NCP_CALL(ncp_task_v2_get_taskHdl((void *)&myTaskHdl));

    NCA_INC_CRITICAL_SECTION(myTaskHdl);

    /* NULL queue list ? */

    if (NULL == (tmpRecvQueuePtr = recvQueuePtr = myTaskHdl->currRecvPtr))
    {
        /*
         * not found
         */
        NCP_CALL(NCP_ST_TASK_HANDLE_HEAD_NULL);   /* return error */
    }


    unlockRequired = TRUE;
    NCP_TASK_CLAIM_LOCK(pNcpNcaV2_TaskSwState->taskIoResourceLock, flags);

    /*
     * First we must find the proper recvQueue in the list
     */

    while(1)
    {

        if (recvQueueId == recvQueuePtr->recvQueueId) /* Found it ? */
        {
            ncaQueueId = recvQueuePtr->ncaQueueId;
            break;
        }
        else
        {
            recvQueuePtr = recvQueuePtr->next;
            if (recvQueuePtr == tmpRecvQueuePtr)
            {
                NCP_CALL(NCP_ST_TASK_RECEIVE_QUEUE_NOT_FOUND);
            }
        }
    }

    /*
     * Now we must delink the recvQueue,   which means finding the element which points to this,
     * since we have a singly linked circular list.
     */

     if (recvQueuePtr->next == recvQueuePtr)
     {
        myTaskHdl->currRecvPtr = NULL;   /* only element identified by pointing at itself */
     }
     else
     {
        tmpRecvQueuePtr = myTaskHdl->currRecvPtr;
        while(1)
        {
            /* found it? */
            if (tmpRecvQueuePtr->next == recvQueuePtr)
            {
                /* delink */
                tmpRecvQueuePtr->next = recvQueuePtr->next;
                if (myTaskHdl->currRecvPtr == recvQueuePtr)
                {
                    myTaskHdl->currRecvPtr = recvQueuePtr->next;
                }
                break;
            }
            else
            {
                tmpRecvQueuePtr = tmpRecvQueuePtr->next;
            }
         } /* while */
     } /* else */



    if (NULL != (p_iPCQ = recvQueuePtr->taskQueue))
    {
        p_iPCQ->pcqUseCnt--;

        ncp_nvm_free(recvQueuePtr);

#ifdef NCP_NCA_USE_GLOBAL_RECVQUEUEID
        pNcpNcaV2_TaskSwState->perNca_recvQ_IDs[0].inUse[recvQueueId] = FALSE;
#else
        pNcpNcaV2_TaskSwState->perNca_recvQ_IDs[recvQueuePtr->ncaQueueId].inUse[recvQueueId] = FALSE;
#endif
    }


NCP_RETURN_LABEL
    if (unlockRequired)
    {
        NCP_TASK_FREE_LOCK(pNcpNcaV2_TaskSwState->taskIoResourceLock, flags);
    }

    if (NCP_ST_SUCCESS == ncpStatus)
    {
        /* need to use group relative ipcq index here */
        myTaskHdl->myIPCQmask &= ~(1ULL << (ncaQueueId));
        NCP_TASK_INC_STAT(api_recv_queue_unbind_ok);
    }
    else
    {
        NCP_TASK_CHECK_FOR_SHUTDOWN_IN_EXIT();
        NCP_TASK_INC_STAT(api_recv_queue_unbind_err);
    }

    NCA_DEC_CRITICAL_SECTION(myTaskHdl);

    return ncpStatus;
}

ncp_st_t
ncp_task_v2_recv_queue_vp_bind(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t recvQueueId,
	ncp_vp_hdl_t vpHdl,
	ncp_uint8_t engineSequenceId,
	ncp_bool_t shared,
	ncp_task_recv_fn_t recvFunc,
	void *recvFuncArg)
{
    ncp_st_t ncpStatus= NCP_ST_SUCCESS;
    ncp_pvt_task_recv_queue_t *pRecvQueue=NULL;
    ncp_recv_queue_level1_bind_wrapper_t* pBindTableEntry;
    ncp_pvt_task_hdl_t *myTaskHdl = (ncp_pvt_task_hdl_t *)taskHdl;
    ncp_uint8_t      templateId = 0;
    ncp_bool_t freeOnErr=FALSE;
    ncp_bool_t      unlockRequired = FALSE;
#if defined(NCP_KERNEL) && (defined(NCP_OSE) || defined(NCP_VXWORKS))
    spinlock_flags_t flags = 0;
#endif


    NCP_CHECK((NULL != pNcpNcaV2_TaskSwState), NCP_ST_TASK_NO_GSM);

    NCP_CALL(ncp_task_v2_get_taskHdl((void *)&myTaskHdl));

    if (shared)
    {
        NCP_CALL(NCP_ST_TASK_SHARED_PIPELINES_NOT_SUPPORTED);
    }

    NCA_INC_CRITICAL_SECTION(myTaskHdl);

    NCP_TASK_CHECK_FOR_SHUTDOWN();

    /*
     * Sanity checking
     */

    if ((NULL == myTaskHdl) || (NCP_TASK_HDL_COOKIE != myTaskHdl->cookie))
    {
        /* return error */
        NCP_CALL(NCP_ST_TASK_INVALID_TASK_HANDLE);
    }


    NCP_VP_VALIDATE_HANDLE(vpHdl);

    unlockRequired = TRUE;
    NCP_TASK_CLAIM_LOCK(pNcpNcaV2_TaskSwState->taskIoResourceLock, flags);

    NCP_CALL(ncp_task_v2_find_recv_queue((ncp_pvt_task_hdl_t *)myTaskHdl, recvQueueId, &pRecvQueue));


    if (NULL == pRecvQueue->taskQueue)
    {
        NCP_CALL(NCP_ST_TASK_INVALID_RECEIVE_QUEUE);
    }

    if (0 == pRecvQueue->taskQueue->pcqUseCnt)
    {
        NCP_CALL(NCP_ST_TASK_INVALID_RECEIVE_QUEUE);
    }

    /*
     * Set up receive queue binding table,   indexed by template id
     */

    ncp_vp_cpu_terminate_template_id_get(vpHdl, engineSequenceId, templateId);    /* Macro - result returned in templateId!! */



    if (NULL == (pBindTableEntry = pNcpNcaV2_TaskSwState->ncaQueueToPipelineBindings[pRecvQueue->ncaQueueId]))
    {
		/*
		 * Allocate table space
		 */
		NCP_ASSERT((NULL !=
				   (pBindTableEntry
				   = pNcpNcaV2_TaskSwState->ncaQueueToPipelineBindings[pRecvQueue->ncaQueueId]
				   = ncp_nvm_malloc(sizeof(ncp_recv_queue_level1_bind_wrapper_t)))),
							NCP_ST_TASK_NO_MEM_L1BIND);
        ncp_memset(pNcpNcaV2_TaskSwState->ncaQueueToPipelineBindings[pRecvQueue->ncaQueueId],
                0,
                sizeof(ncp_recv_queue_level1_bind_wrapper_t));
        pBindTableEntry->useCnt = 0;
        freeOnErr = TRUE;
    }

    /*
     * Set up bind table for newly bound pipeline
     */

    if (NULL  == pBindTableEntry->level1_bind[templateId].taskQueue)
    {

        pBindTableEntry->level1_bind[templateId].taskQueue = ( ncp_task_pcq_t * )pRecvQueue->taskQueue;
    }
    else
    {
        /* ERROR */
        NCP_CALL(NCP_ST_TASK_EXCLUSIVE_VP_BINDING_NOT_AVAIL);
    }
    pBindTableEntry->useCnt++;
    pBindTableEntry->level1_bind[templateId].vpHdl         = vpHdl;
    pBindTableEntry->level1_bind[templateId].engineSequenceId    = engineSequenceId;
    pBindTableEntry->level1_bind[templateId].recvFunc      = recvFunc;
    pBindTableEntry->level1_bind[templateId].recvFuncArg   = recvFuncArg;

NCP_RETURN_LABEL

    if (NCP_ST_SUCCESS == ncpStatus)
    {
        NCP_TASK_INC_STAT(api_recv_queue_vp_bind_ok);
    }
    else
    {
        if (freeOnErr)
        {
            ncp_nvm_free(pNcpNcaV2_TaskSwState->ncaQueueToPipelineBindings[pRecvQueue->ncaQueueId]);
            pNcpNcaV2_TaskSwState->ncaQueueToPipelineBindings[pRecvQueue->ncaQueueId] = NULL;
        }
        NCP_TASK_INC_STAT(api_recv_queue_vp_bind_err);
    }

    if (unlockRequired)
    {
        NCP_TASK_FREE_LOCK(pNcpNcaV2_TaskSwState->taskIoResourceLock, flags);
    }

    NCA_DEC_CRITICAL_SECTION(myTaskHdl);

    return ncpStatus;
}


ncp_st_t
ncp_task_v2_recv_queue_vp_unbind(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t recvQueueId,
	ncp_vp_hdl_t vpHdl,
	ncp_uint8_t engineSequenceId)
{
    ncp_st_t ncpStatus= NCP_ST_SUCCESS;
    ncp_pvt_task_hdl_t *myTaskHdl      = (ncp_pvt_task_hdl_t *)taskHdl;
    ncp_pvt_task_recv_queue_t *pRecvQueue=NULL;
    ncp_recv_queue_level1_bind_wrapper_t *pBindTableEntry;
    ncp_uint8_t      templateId = 0;
    ncp_bool_t unlockRequired = FALSE;
#if defined(NCP_KERNEL) && (defined(NCP_OSE) || defined(NCP_VXWORKS))
    spinlock_flags_t flags = 0;
#endif

    /*
     * Perform validation on inputs
     */

    NCP_CHECK((NULL != pNcpNcaV2_TaskSwState), NCP_ST_TASK_NO_GSM);

    NCP_CALL(ncp_task_v2_get_taskHdl((void *)&myTaskHdl));

    NCA_INC_CRITICAL_SECTION(myTaskHdl);

    NCP_VP_VALIDATE_HANDLE(vpHdl);

    NCP_CALL(ncp_task_v2_find_recv_queue((ncp_pvt_task_hdl_t *)myTaskHdl, recvQueueId, &pRecvQueue));

    NCP_ASSERT((NULL != (pBindTableEntry
		= pNcpNcaV2_TaskSwState->ncaQueueToPipelineBindings[pRecvQueue->ncaQueueId])), NCP_ST_TASK_NULL_L1_BINDP);






    ncp_vp_cpu_terminate_template_id_get(vpHdl, engineSequenceId, templateId);    /* Macro - result returned in templateId!! */

    if (( pBindTableEntry->level1_bind[templateId].vpHdl != vpHdl) || (NULL == pBindTableEntry->level1_bind[templateId].vpHdl))
    {
        NCP_CALL(NCP_ST_TASK_INVALID_VP_HANDLE);

    }

    unlockRequired = TRUE;
    NCP_TASK_CLAIM_LOCK(pNcpNcaV2_TaskSwState->taskIoResourceLock, flags);



    /*
     * Housekeeping for NCA queue level bindings
     */
    pBindTableEntry->useCnt--;
    if (0 == pBindTableEntry->useCnt)
    {
        ncp_nvm_free(pBindTableEntry);
        pNcpNcaV2_TaskSwState->ncaQueueToPipelineBindings[pRecvQueue->ncaQueueId] = NULL;
    }

NCP_RETURN_LABEL

    if (unlockRequired)
    {
        NCP_TASK_FREE_LOCK(pNcpNcaV2_TaskSwState->taskIoResourceLock, flags);
    }

    if (NCP_ST_SUCCESS == ncpStatus)
    {
        NCP_TASK_INC_STAT(api_recv_queue_vp_unbind_ok);
    }
    else
    {
        NCP_TASK_CHECK_FOR_SHUTDOWN_IN_EXIT();
        NCP_TASK_INC_STAT(api_recv_queue_vp_unbind_err);
    }

    NCA_DEC_CRITICAL_SECTION(myTaskHdl);

    return ncpStatus;
}

static int dbg_manage_rxstats=0;

ncp_st_t
ncp_task_ncav2_recv(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t *pRecvQueueId,
	ncp_vp_hdl_t *pVpHdl,
	ncp_uint8_t *pEngineSequenceId,
	ncp_task_ncaV2_recv_buf_t **task,
	void **recvHandlerArg,
	ncp_bool_t wait)
{
    ncp_st_t ncpStatus= NCP_ST_SUCCESS;

#ifdef NCP_DEV_SOCKET
    /* FIXME - This will take some work.
     * The 34xx receive header is smaller than the 55xx
     * so not only must we convert,  we must copy data too!
     */
    ncpStatus = NCP_ST_NOT_IMPLEMENTED;
#else
    ncp_pvt_task_hdl_t *myTaskHdl = (ncp_pvt_task_hdl_t *)taskHdl;
    ncp_pvt_task_recv_queue_t   *myRecvQueue;
#if 0 /* UBOOT */
    ncp_recv_queue_level1_bind_wrapper_t* pBindTableEntry;
    ncp_uint8_t                  templateId;
    ncp_vp_hdl_t                 thisVpHdl;
    ncp_uint8_t                  thisEngSeqId;
    ncp_task_pcq_t               *pcq;
#endif
    ncp_pvt_task_recv_queue_t   *firstRecvQueue;
    ncp_uint8_t                  buffSizeBits;

    NCP_CHECK((NULL != pNcpNcaV2_TaskSwState), NCP_ST_TASK_NO_GSM);


    NCP_CALL(ncp_task_v2_get_taskHdl((void *)&myTaskHdl));

    NCA_INC_CRITICAL_SECTION(myTaskHdl);

    NCP_TASK_CHECK_FOR_SHUTDOWN();

    /*
     * Get first queue to service.
     */

    if (NULL == (myRecvQueue = myTaskHdl->currRecvPtr))
    {
        /* return error */
        NCP_CALL(NCP_ST_TASK_HANDLE_HEAD_NULL);
    }
    firstRecvQueue =  myRecvQueue;

    do {

#if 0 /* UBOOT */
ncp_recv_retry:
#endif

#if 0 /* UBOOT */
        pcq = myRecvQueue->taskQueue;
#endif

        WATCHDOG_RESET();

        if (NCP_ST_SUCCESS ==
            (ncpStatus = NCP_NCA_CHECK_TASK_INPUT_QUEUE(
                                         myTaskHdl,
                                         myRecvQueue,
                                         task,
                                         &buffSizeBits )))
        {
            ncp_task_ncaV2_recv_buf_t *myTask = (ncp_task_ncaV2_recv_buf_t *)*task;
#if 0 /* UBOOT */
            ncp_recv_queue_level1_bind_t *pLevel1_bind;
            ncp_bool_t dropTask = FALSE;
#endif

            debug("ncp_task_ncav2_recv(): received task!! task addr=0x%p\n", myTask);

            dbg_manage_rxstats=1;

            NCP_TASK_INC_STAT(RxQueueNotEmpty);

#if 0 /* UBOOT */

            templateId = myTask->templateID;

            /*
             * First check for errors,   and issue any completions as required
             */

            if (NULL == (pBindTableEntry
                = pNcpNcaV2_TaskSwState->ncaQueueToPipelineBindings[myRecvQueue->ncaQueueId]))
            {
                dropTask = TRUE;
            }
            else
            {
                pLevel1_bind = &pBindTableEntry->level1_bind[templateId];
                if ((NULL == pLevel1_bind) || (NULL == (thisVpHdl = pLevel1_bind->vpHdl)))
                {
                    dropTask = TRUE;
                }
            }

            if (dropTask)
            {

                /*
                 * Must complete here if manual completion,
                 * but not if h/w auto completion.
                 */
                if (NCP_TASK_COMPLETION_HW_AUTOMATIC
                    != pcq->u.ipcq_info.rxTaskCompletionMode)
                {

                    NCP_NCA_LOWLEVEL_TASK_COMPLETION(myTaskHdl,
                                        (ncp_ncaV2_task_completion_data_t *)myTask);

                }

                ncp_task_ncav2_buffer_free((ncp_task_hdl_t *)myTaskHdl, (void *)myTask);

                NCP_TASK_INC_STAT(RxDroppedNoBind);

                if (0 == myRecvQueue->wrrCounter--)
                {
                     myTaskHdl->currRecvPtr = myRecvQueue = myRecvQueue->next;
                     myRecvQueue->wrrCounter = myRecvQueue->weight;
                }

                goto ncp_recv_retry;

            } /* dropTask */



            if (NCP_TASK_COMPLETION_HW_AUTOMATIC != pcq->u.ipcq_info.rxTaskCompletionMode)
            {
                if (NCP_TASK_COMPLETION_SW_AUTOMATIC == pcq->u.ipcq_info.rxTaskCompletionMode)
                {
                    /* FIXME if support is really required in 55xx */
                    NCP_CALL(NCP_ST_NOT_IMPLEMENTED);
                }
                else
                {
                    if (pNcpNcaV2_TaskSwState->warmRestartEnabled)
                    {
                        ncp_task_man_completion_list_element_t *curr;
                        /*
                         * Add to list of owed task completions associated with this task handle
                         */
                        NCP_ASSERT((NULL != (curr = ncp_nvm_malloc(sizeof(ncp_task_man_completion_list_element_t)))),
                            NCP_ST_NO_MEMORY);

                        curr->task = myTask;

                        if (NULL == myTaskHdl->firstManCompletion)
                        {
                            curr->next = curr->prev = NULL;
                            myTaskHdl->firstManCompletion = myTaskHdl->lastManCompletion = curr;
                        }
                        else
                        {
                            myTaskHdl->lastManCompletion->next = curr;
                            curr->prev =  myTaskHdl->lastManCompletion;
                            myTaskHdl->lastManCompletion = curr;
                            curr->next = NULL;
                        }
                    }    /* warmRestartEnabled */
                }
            } /* NCP_TASK_COMPLETION_HW_AUTOMATIC */

            if (NULL != pRecvQueueId)
            {
                *pRecvQueueId = myRecvQueue->recvQueueId;
            }

            thisEngSeqId = pLevel1_bind->engineSequenceId;

            if (NULL != pEngineSequenceId)
            {
                *pEngineSequenceId = thisEngSeqId;
            }

			/*
			 * Decode task parameters before handing task off to application
			 */
			ncp_vpm_task_param_decode(templateId,
				&((myTask)->params[0]),
				&((myTask)->params[0]));

			/* Is caller intested in the vpHdl? */
			if (NULL != pVpHdl)
			{
			    *pVpHdl = thisVpHdl;
			}

            if (NULL != recvHandlerArg)
            {
                *recvHandlerArg = pLevel1_bind->recvFuncArg;
            }
            if (NULL != pLevel1_bind->recvFunc)
            {

                NCP_CALL(
                (pLevel1_bind->recvFunc)(myRecvQueue->recvQueueId,
                                                       pLevel1_bind->vpHdl,
                                                       thisEngSeqId,
                                                       pLevel1_bind->recvFuncArg,
                                                       myTask,
                                                       NCP_TASK_NCAV2_DATA(myTask)));
                NCP_TASK_INC_STAT(RxTaskDispatched);
                myTask = NULL;
                ncpStatus = NCP_ST_TASK_DISPATCHED;

                if (0 == myRecvQueue->wrrCounter--)
                {
                    myTaskHdl->currRecvPtr = myRecvQueue = myRecvQueue->next;
                    myRecvQueue->wrrCounter = myRecvQueue->weight;
                }
                break;      /* return to caller */
            }


#endif /* UBOOT */

            NCP_TASK_INC_STAT(RxTaskDirect);

            if (0 == myRecvQueue->wrrCounter--)
            {
                 myTaskHdl->currRecvPtr = myRecvQueue = myRecvQueue->next;
                 myRecvQueue->wrrCounter = myRecvQueue->weight;
            }

            break;
        }
        else
        {
            if (NCP_ST_TASK_RECV_QUEUE_EMPTY != ncpStatus)
            {
                NCP_CALL(ncpStatus); /* Get out if not retry-able */
            }
        }

        /*
         * === No task recevied on this queue, so advance to next regardless of wrrCounter
         */

        myTaskHdl->currRecvPtr = myRecvQueue = myRecvQueue->next;
        myRecvQueue->wrrCounter = myRecvQueue->weight;

        /*
         * Have we checked all of the queues?
         */
        if (myRecvQueue == firstRecvQueue)
        {
            if (wait)
            {
                NCP_TASK_CHECK_FOR_SHUTDOWN();

                if (dbg_manage_rxstats) /* don't count empty conditions until traffic has actually started */
                {
                    NCP_TASK_INC_STAT(RxQueueEmpty);
                }

                NCP_TASK_BLOCK_ON_INTERRUPT(myTaskHdl,
                                            myTaskHdl->dev,
                                            NCP_NCA_WAIT_FOR_RX_INTR,
                                            pcq->grpId,
                                            myTaskHdl->myIPCQmask);
            }
            else
            {
                ncpStatus = NCP_ST_TASK_RECV_QUEUE_EMPTY;     /* get out with appropriate NON-ERROR status */
                break;
            }
        }


    } while(1);

NCP_RETURN_LABEL

    if ((NCP_ST_SUCCESS == ncpStatus) || (NCP_ST_TASK_DISPATCHED == ncpStatus))
    {
        NCP_TASK_INC_STAT(api_recv_ok);
    }
    else if (NCP_ST_TASK_RECV_QUEUE_EMPTY != ncpStatus)
    {
        NCP_TASK_INC_STAT(api_recv_err);
    }

    NCA_DEC_CRITICAL_SECTION(myTaskHdl);

#endif /* NCP_DEV_SOCKET */
    return ncpStatus;
}


ncp_st_t
ncp_task_v2_legacy_recv(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t *pRecvQueueId,
	ncp_vp_hdl_t *pVpHdl,
	ncp_uint8_t *pEngineSequenceId,
	ncp_task_recv_buf_t **task,
	void                **taskData,
    void **recvHandlerArg,
	ncp_bool_t wait)
{
    ncp_pvt_task_hdl_t *myTaskHdl = (ncp_pvt_task_hdl_t *)taskHdl;
    ncp_pvt_task_recv_queue_t   *myRecvQueue;
    ncp_recv_queue_level1_bind_wrapper_t* pBindTableEntry;
    ncp_pvt_task_recv_queue_t   *firstRecvQueue;
    ncp_uint8_t                  templateId;
    ncp_vp_hdl_t                 thisVpHdl;
    ncp_task_pcq_t               *pcq;
    ncp_uint8_t                 thisEngSeqId;
#ifndef NCP_DEV_SOCKET
    ncp_uint8_t                  buffSizeBits;
#endif
    ncp_st_t ncpStatus= NCP_ST_SUCCESS;


    NCP_CHECK((NULL != pNcpNcaV2_TaskSwState), NCP_ST_TASK_NO_GSM);


    NCP_CALL(ncp_task_v2_get_taskHdl((void *)&myTaskHdl));

    NCA_INC_CRITICAL_SECTION(myTaskHdl);

    NCP_TASK_CHECK_FOR_SHUTDOWN();

    /*
     * Get first queue to service.
     */

    if (NULL == (myRecvQueue = myTaskHdl->currRecvPtr))
    {
        /* return error */
        NCP_CALL(NCP_ST_TASK_HANDLE_HEAD_NULL);
    }
    firstRecvQueue =  myRecvQueue;

    do {

ncp_recv_retry:


        pcq = myRecvQueue->taskQueue;


        if (NCP_ST_SUCCESS ==
            (ncpStatus = NCP_NCA_CHECK_TASK_INPUT_QUEUE(
                                         myTaskHdl,
                                         myRecvQueue,
                                         task,
                                         &buffSizeBits )))
        {
            ncp_task_ncaV2_recv_buf_t *myTask = (ncp_task_ncaV2_recv_buf_t *)*task;
            ncp_task_recv_buf_t *my3400Task
                    = (ncp_task_recv_buf_t *)myTask;
            ncp_recv_queue_level1_bind_t *pLevel1_bind;
            ncp_bool_t dropTask = FALSE;

            dbg_manage_rxstats=1;

            NCP_TASK_INC_STAT(RxQueueNotEmpty);

#ifndef NCP_DEV_SOCKET
            templateId = myTask->templateID;
#else
            /* already in 34xx format for socket mode */
            templateId = my3400Task->templateId;
#endif

            /*
             * First check for errors,   and issue any completions as required
             */

            if (NULL == (pBindTableEntry
                = pNcpNcaV2_TaskSwState->ncaQueueToPipelineBindings[myRecvQueue->ncaQueueId]))
            {
                dropTask = TRUE;
            }
            else
            {
                pLevel1_bind = &pBindTableEntry->level1_bind[templateId];
                if ((NULL == pLevel1_bind) || (NULL == (thisVpHdl = pLevel1_bind->vpHdl)))
                {
                    dropTask = TRUE;
                }
            }

            if (dropTask)
            {

                /*
                 * discard - no active listener is bound
                 */

                /*
                 * Must complete here if manual completion,
                 * but not if h/w auto completion.
                 */
                if (NCP_TASK_COMPLETION_HW_AUTOMATIC
                    != pcq->u.ipcq_info.rxTaskCompletionMode)
                {

                    NCP_NCA_LOWLEVEL_TASK_COMPLETION(myTaskHdl,
                                        (ncp_ncaV2_task_completion_data_t *)myTask);

                }

                ncp_task_ncav2_buffer_free((ncp_task_hdl_t *)myTaskHdl, (void *)myTask);

                NCP_TASK_INC_STAT(RxDroppedNoBind);

                if (0 == myRecvQueue->wrrCounter--)
                {
                     myTaskHdl->currRecvPtr = myRecvQueue = myRecvQueue->next;
                     myRecvQueue->wrrCounter = myRecvQueue->weight;
                }

                goto ncp_recv_retry;

            } /* dropTask */


#ifndef NCP_DEV_SOCKET /* already in 34xx format for socket mode */

           /*
             * CONVERT ncaV2 NATIVE INPUT TASK HEADER to 3400 HEADER
             * FOR BACKWARD COMPATIBILITY - we'll perform the conversion
             * in-place.
             */
            {
                int savBufferSz     = myTask->pduBlockSz0;  /* Word 11 */
                int savDebug        = myTask->debug;        /* Word 11 */

                /* Copy parameters in reverse order */
                /* Words 4..11                      */
                {
                    int idx;

                    for (idx=31; idx >= 0; idx--)
                    {
                        my3400Task->parms[idx] =  myTask->params[idx];
                    }
                }

		ncp_vpm_task_param_decode(templateId,
			&((my3400Task)->parms[0]),
			                              &((my3400Task)->parms[0]));

                /* Word 2 */
                my3400Task->traceEn     = 0; /* ??? */
                my3400Task->taskPrio    = myTask->priority;
                my3400Task->TOID        = myTask->TOID;
                my3400Task->dataSz      = myTask->pduSize;

                /* Word 3 */
                my3400Task->QID         = myTask->QID;
                my3400Task->templateId  = myTask->templateID;
                my3400Task->taskErr     = my3400Task->bufferSizeErr = 0;
                my3400Task->bufferSize  = savBufferSz;
                my3400Task->debugFieldV = savDebug;
                my3400Task->destId_9_0  = myTask->dstID_9_0;

                /* Word 1 */
                my3400Task->launchId   = 0; /* ??? */

                /* Word 0 */
                my3400Task->dataOffset = (ncp_uint32_t)((ncp_uint32_t)myTask->pduSegAddr0 - (ncp_raw_addr_t)(myTask));
            }
            /* END CONVERT */

#endif /* #ifndef NCP_DEV_SOCKET */

            if (NCP_TASK_COMPLETION_HW_AUTOMATIC != pcq->u.ipcq_info.rxTaskCompletionMode)
            {
                if (NCP_TASK_COMPLETION_SW_AUTOMATIC == pcq->u.ipcq_info.rxTaskCompletionMode)
                {
                    /* FIXME if support is really required in 55xx */
                    NCP_CALL(NCP_ST_NOT_IMPLEMENTED);
                }
                else
                {
                    if (pNcpNcaV2_TaskSwState->warmRestartEnabled)
                    {
                        ncp_task_man_completion_list_element_t *curr;
                        /*
                         * Add to list of owed task completions associated with this task handle
                         */
                        NCP_ASSERT((NULL != (curr = ncp_nvm_malloc(sizeof(ncp_task_man_completion_list_element_t)))),
                            NCP_ST_NO_MEMORY);

                        curr->task = myTask;

                        if (NULL == myTaskHdl->firstManCompletion)
                        {
                            curr->next = curr->prev = NULL;
                            myTaskHdl->firstManCompletion = myTaskHdl->lastManCompletion = curr;
                        }
                        else
                        {
                            myTaskHdl->lastManCompletion->next = curr;
                            curr->prev =  myTaskHdl->lastManCompletion;
                            myTaskHdl->lastManCompletion = curr;
                            curr->next = NULL;
                        }
                    } /* warmRestartEnabled */
                }
            } /* NCP_TASK_COMPLETION_HW_AUTOMATIC */

            if (NULL != pRecvQueueId)
            {
                *pRecvQueueId = myRecvQueue->recvQueueId;
            }

            thisEngSeqId = pLevel1_bind->engineSequenceId;

            if (NULL != pEngineSequenceId)
            {
                *pEngineSequenceId = thisEngSeqId;
            }

			/* Is caller intested in the vpHdl? */
			if (NULL != pVpHdl)
			{
			    *pVpHdl = thisVpHdl;
			}

            if (NULL != recvHandlerArg)
            {
                *recvHandlerArg = pLevel1_bind->recvFuncArg;
            }
            if (NULL != pLevel1_bind->recvFunc)
            {

                NCP_CALL(
                (pLevel1_bind->recvFunc)(myRecvQueue->recvQueueId,
                                                       pLevel1_bind->vpHdl,
                                                       thisEngSeqId,
                                                       pLevel1_bind->recvFuncArg,
                                                       my3400Task,
                                                       NCP_TASK_DATA(my3400Task)));
                NCP_TASK_INC_STAT(RxTaskDispatched);
                myTask = NULL;
                ncpStatus = NCP_ST_TASK_DISPATCHED;

                if (0 == myRecvQueue->wrrCounter--)
                {
                    myTaskHdl->currRecvPtr = myRecvQueue = myRecvQueue->next;
                    myRecvQueue->wrrCounter = myRecvQueue->weight;
                }
                break;      /* return to caller */
            }
            else
            {
                *taskData = NCP_TASK_DATA(my3400Task);
            }

            NCP_TASK_INC_STAT(RxTaskDirect);

            if (0 == myRecvQueue->wrrCounter--)
            {
                 myTaskHdl->currRecvPtr = myRecvQueue = myRecvQueue->next;
                 myRecvQueue->wrrCounter = myRecvQueue->weight;
            }

            break;
        }
        else
        {
            if (NCP_ST_TASK_RECV_QUEUE_EMPTY != ncpStatus)
            {
                NCP_CALL(ncpStatus); /* Get out if not retry-able */
            }
        }

        /*
         * === No task recevied on this queue, so advance to next regardless of wrrCounter
         */

        myTaskHdl->currRecvPtr = myRecvQueue = myRecvQueue->next;
        myRecvQueue->wrrCounter = myRecvQueue->weight;

        /*
         * Have we checked all of the queues?
         */
        if (myRecvQueue == firstRecvQueue)
        {
            if (wait)
            {
                NCP_TASK_CHECK_FOR_SHUTDOWN();

                if (dbg_manage_rxstats) /* don't count empty conditions until traffic has actually started */
                {
                    NCP_TASK_INC_STAT(RxQueueEmpty);
                }

                NCP_TASK_BLOCK_ON_INTERRUPT(myTaskHdl,
                                            myTaskHdl->dev,
                                            NCP_NCA_WAIT_FOR_RX_INTR,
                                            pcq->grpId,
                                            myTaskHdl->myIPCQmask);
            }
            else
            {
                ncpStatus = NCP_ST_TASK_RECV_QUEUE_EMPTY;     /* get out with appropriate NON-ERROR status */
                break;
            }
        }


    } while(1);

NCP_RETURN_LABEL

    if ((NCP_ST_SUCCESS == ncpStatus) || (NCP_ST_TASK_DISPATCHED == ncpStatus))
    {
        NCP_TASK_INC_STAT(api_recv_ok);
    }
    else if (NCP_ST_TASK_RECV_QUEUE_EMPTY != ncpStatus)
    {
        NCP_TASK_INC_STAT(api_recv_err);
    }

    NCA_DEC_CRITICAL_SECTION(myTaskHdl);

    return ncpStatus;
}



ncp_st_t
ncp_task_v2_completion_queue_flush(
	ncp_task_hdl_t taskHdl,
    ncp_bool_t wait,
    ncp_bool_t *pQueueStatus)
{
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;

    /* 55XX does not have completion queues, so just return success */

NCP_RETURN_LABEL

    return(ncpStatus);
}

ncp_st_t
ncp_task_remove_manual_completion_element(ncp_pvt_task_hdl_t   *myTaskHdl,
                                          void *task)
{
    ncp_st_t ncpStatus= NCP_ST_SUCCESS;
    ncp_task_man_completion_list_element_t *curr;

    /*
     * Delink the manual task completion entry
     */

    if (NULL != (curr = myTaskHdl->firstManCompletion))
    {
        do
        {
            if (curr->task == task)
            {
                if (NULL == curr->prev)
                {
                    myTaskHdl->firstManCompletion = curr->next;
                    if (curr->next)
                    {
                        curr->next->prev = NULL;
                    }
                }
                else
                {
                    curr->prev->next = curr->next;
                    if (curr->next)
                    {
                        curr->next->prev = curr->prev;
                    }
                }

                if (NULL == curr->next)
                {
                    myTaskHdl->lastManCompletion = curr->prev;
                    if (curr->prev)
                    {
                        curr->prev->next = NULL;
                    }
                }
                else
                {
                    curr->next->prev = curr->prev;
                    if (curr->prev)
                    {
                        curr->prev->next = curr->next;
                    }
                }

                ncp_nvm_free(curr);
                break;
            } /* found */
        } while(NULL != (curr = curr->next));

        if (NULL == curr)
        {
            NCP_CALL(NCP_ST_TASK_NO_MAN_COMPLETION_OWED);
        }
    }   /* list not empty */
    else
    {
        NCP_CALL(NCP_ST_TASK_NULL_MAN_COMPLETION_LIST);
    }

NCP_RETURN_LABEL
    return(ncpStatus);

}

ncp_st_t
ncp_task_v2_recv_done(
	ncp_task_hdl_t taskHdl,
	ncp_task_recv_buf_t *task)
{
    ncp_st_t ncpStatus= NCP_ST_SUCCESS;
    ncp_pvt_task_hdl_t   *myTaskHdl = (ncp_pvt_task_hdl_t *)taskHdl;
    ncp_ncaV2_task_completion_data_t completionData;

    NCP_CHECK((NULL != pNcpNcaV2_TaskSwState), NCP_ST_TASK_NO_GSM);

    NCP_CALL(ncp_task_v2_get_taskHdl((void *)&myTaskHdl));

    NCA_INC_CRITICAL_SECTION(myTaskHdl);

    NCP_TASK_CHECK_FOR_SHUTDOWN();

    if (NULL == task)
    {
        NCP_CALL(NCP_ST_TASK_NULL_TASK_IN_RECVDONE);
    }

#ifdef NCP_DEV_SOCKET
    /* Return success - We forced automatic completion mode since we use the 34xx rdev interface for native mode */
    goto ncp_return;
#endif

    if (pNcpNcaV2_TaskSwState->warmRestartEnabled)
    {
        NCP_CALL(ncp_task_remove_manual_completion_element(myTaskHdl, task));
    }

    /* Build completion Data from ncaV1 style task */

    completionData.templateID = task->templateId;
    completionData.QID        = task->QID;
    completionData.pduSize    = task->dataSz;
    completionData.dstID_9_0  = task->destId_9_0;
    completionData.priority   = task->taskPrio;
    completionData.TOID       = task->TOID;

    NCP_NCA_LOWLEVEL_TASK_COMPLETION(myTaskHdl,
                    (ncp_ncaV2_task_completion_data_t *)&completionData);

NCP_RETURN_LABEL

    if (NCP_ST_SUCCESS == ncpStatus)
    {
        NCP_TASK_INC_STAT(api_recv_done_ok);
    }
    else
    {
        NCP_TASK_INC_STAT(api_recv_done_err);
    }

    NCA_DEC_CRITICAL_SECTION(myTaskHdl);

    return ncpStatus;
}


ncp_st_t
ncp_task_free_task_with_dealloc_immediate(
    ncp_pvt_task_hdl_t   *myTaskHdl,
	ncp_task_ncaV2_recv_buf_t *task)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_ncaV2_free_pdu_segments_t dealloc_immediate;

    dealloc_immediate.ptrCnt = task->ptrCnt;
    switch (dealloc_immediate.ptrCnt)
    {
    case 6:
        dealloc_immediate.pduSegAddr5 = task->pduSegAddr5;
    case 5:
        dealloc_immediate.pduSegAddr4 = task->pduSegAddr4;
    case 4:
        dealloc_immediate.pduSegAddr3 = task->pduSegAddr3;
    case 3:
        dealloc_immediate.pduSegAddr2 = task->pduSegAddr2;
    case 2:
        dealloc_immediate.pduSegAddr1 = task->pduSegAddr1;
    case 1:
    case 0:
        dealloc_immediate.pduSegAddr0 = (ncp_uint64_t)(ncp_raw_addr_t)task;
        break;
    default:
        NCP_CALL(NCP_ST_INTERNAL_ERROR);
    }

    NCP_CALL(ncp_task_ncav2_free_pdu_segments((ncp_task_hdl_t)myTaskHdl,
	                                          &dealloc_immediate));

NCP_RETURN_LABEL

    return(ncpStatus);
}

ncp_st_t
ncp_task_ncav2_recv_done(
	ncp_task_hdl_t taskHdl,
	ncp_task_ncaV2_recv_buf_t *task,
	ncp_bool_t freepduSegments)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_pvt_task_hdl_t   *myTaskHdl = (ncp_pvt_task_hdl_t *)taskHdl;
#if defined(NCP_KERNEL) && (defined(NCP_OSE) || defined(NCP_VXWORKS))
    spinlock_flags_t spinFlags = 0;
#endif

    NCP_CHECK((NULL != pNcpNcaV2_TaskSwState), NCP_ST_TASK_NO_GSM);

    NCP_CALL(ncp_task_v2_get_taskHdl((void *)&myTaskHdl));

    NCA_INC_CRITICAL_SECTION(myTaskHdl);

    NCP_TASK_CHECK_FOR_SHUTDOWN();

    if (NULL == task)
    {
        NCP_CALL(NCP_ST_TASK_NULL_TASK_IN_RECVDONE);
    }

#ifdef NCP_DEV_SOCKET
    /* Return success - We forced automatic completion mode since we use the 34xx rdev interface for native mode */
    goto ncp_return;
#endif

    if (pNcpNcaV2_TaskSwState->warmRestartEnabled)
    {
        NCP_CALL(ncp_task_remove_manual_completion_element(myTaskHdl, task));
    }

    if (freepduSegments)
    {
        if (NCP_TASK_IS_SHARED_POOL(myTaskHdl->poolID))
        {
#if (NCP_TASK_NCAV2_SHPOOL_PTR_DEBUG) || defined(NCP_TASK_DBG_55XX_TASK_FLOW)
            NCP_LOG(NCP_MSG_INFO,
                    "COMP_DEALLOC ptrCnt=%d\r\n",
                    task->ptrCnt);

            switch (task->ptrCnt)
            {
                case 6:
                    NCP_LOG(NCP_MSG_INFO,"va5=%p\r\n",
                    ((void *)(ncp_raw_addr_t)task->pduSegAddr5));

                case 5:
                    NCP_LOG(NCP_MSG_INFO,"va4=%p\r\n",
                    ((void *)(ncp_raw_addr_t)task->pduSegAddr4));

                case 4:
                    NCP_LOG(NCP_MSG_INFO,"va5=%p\r\n",
                    ((void *)(ncp_raw_addr_t)task->pduSegAddr3));
                case 3:
                    NCP_LOG(NCP_MSG_INFO,"va2=%p\r\n",
                    ((void *)(ncp_raw_addr_t)task->pduSegAddr2));
                case 2:
                    NCP_LOG(NCP_MSG_INFO,"va1=%p\r\n",
                    ((void *)(ncp_raw_addr_t)task->pduSegAddr1));
                    break;

                case 1:
                    NCP_LOG(NCP_MSG_INFO,"va0=%p\r\n",
                    ((void *)(ncp_raw_addr_t)task->pduSegAddr0));
                    break;

                default:
                    break;
            }
#endif

#ifndef NCP_TASK_COMPLETION_PLUS_DEALLOC_BUG
            /* VP Managed Pool,   let H/W free the tasks */
            NCP_NCA_LOWLEVEL_TASK_COMPLETION_PLUS_DEALLOC(myTaskHdl,
                    (ncp_task_ncaV2_recv_buf_t *)task);
#else
            /*
             * SW Workaround
             * 55xx preproduction ASIC Only
             */
            NCP_NCA_LOWLEVEL_TASK_COMPLETION(myTaskHdl,
                                            (ncp_ncaV2_task_completion_data_t *)task);
            NCP_CALL(ncp_task_free_task_with_dealloc_immediate(
                                             myTaskHdl,
                                             task));
#endif
        }
        else
        {

            NCP_NCA_LOWLEVEL_TASK_COMPLETION(myTaskHdl,
                                            (ncp_ncaV2_task_completion_data_t *)task);

            /* free to CPU managed pool */
            switch(task->ptrCnt)
            {
                case 6:
                    ncp_task_v2_CpuPool_free(
                        myTaskHdl->poolHdl,
                        (void *)(ncp_raw_addr_t)(task->pduSegAddr5));
                case 5:
                    ncp_task_v2_CpuPool_free(
                        myTaskHdl->poolHdl,
                        (void *)(ncp_raw_addr_t)(task->pduSegAddr4));
                case 4:
                    ncp_task_v2_CpuPool_free(
                        myTaskHdl->poolHdl,
                        (void *)(ncp_raw_addr_t)(task->pduSegAddr3));
                case 3:
                    ncp_task_v2_CpuPool_free(
                        myTaskHdl->poolHdl,
                        (void *)(ncp_raw_addr_t)(task->pduSegAddr2));
                case 2:
                    ncp_task_v2_CpuPool_free(
                        myTaskHdl->poolHdl,
                        (void *)(ncp_raw_addr_t)(task->pduSegAddr1));;
                case 1:
                case 0:
                    ncp_task_v2_CpuPool_free(
                        myTaskHdl->poolHdl,
                        task);
                    break;
                default:
                    break;
            }
        }
    }
    else
    {

        NCP_NCA_LOWLEVEL_TASK_COMPLETION(myTaskHdl,
                    (ncp_ncaV2_task_completion_data_t *)task);

    }

NCP_RETURN_LABEL

    if (NCP_ST_SUCCESS == ncpStatus)
    {
        NCP_TASK_INC_STAT(api_recv_done_ok);
    }
    else
    {
        NCP_TASK_INC_STAT(api_recv_done_err);
    }

    NCA_DEC_CRITICAL_SECTION(myTaskHdl);

    return(ncpStatus);
}


ncp_st_t
ncp_task_v2_send_queue_flush(
	ncp_task_hdl_t taskHdl,
    ncp_bool_t wait,
    ncp_bool_t *pQueueStatus)
{
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;
	ncp_pvt_task_hdl_t *myTaskHdl = (ncp_pvt_task_hdl_t *) taskHdl;
    ncp_task_pcq_t *p_oPCQ;


    NCP_CHECK((NULL != pNcpNcaV2_TaskSwState), NCP_ST_TASK_NO_GSM);

    NCP_CALL(ncp_task_v2_get_taskHdl((void *)&myTaskHdl));

    NCA_INC_CRITICAL_SECTION(myTaskHdl);

    p_oPCQ = myTaskHdl->sendQueue;

    do
    {
        if (TRUE != NCP_DEV_NCA_PCQ_IS_EMPTY(p_oPCQ))
        {
            if (wait)
            {
                ncp_sys_usleep(NCP_SLEEP_POLL_INTERVAL);
            }
            else
            {
                *pQueueStatus = 1; /* Not empty */
                break;
            }
        }
        else
        {
            *pQueueStatus = 0; /* empty */
            break;
        }
    } while(1);

    NCP_CALL(NCP_TASK_FREE_SEND_BUFFERS(p_oPCQ, FALSE));

NCP_RETURN_LABEL

    NCP_TASK_CHECK_FOR_SHUTDOWN_IN_EXIT();

    NCA_DEC_CRITICAL_SECTION(myTaskHdl);

    return(ncpStatus);
}

ncp_st_t
ncp_task_ncav2_send(
	ncp_task_hdl_t taskHdl,
	ncp_vp_hdl_t vpHdl,
	ncp_task_ncaV2_send_meta_t *taskMetaData,
	ncp_bool_t wait,
    ncp_task_send_done_fn_t sendDoneFn,
    void                   *sendDoneFuncArg)
{
    ncp_st_t ncpStatus= NCP_ST_SUCCESS;
#ifdef NCP_DEV_SOCKET
    /* FIXME - need native API conversion for socket mode */
#else
    ncp_pvt_task_hdl_t *myTaskHdl = taskHdl;
    ncp_task_ncaV2_oPCQ_aux_data_t  taskAuxData={0};


#if 0 /* UBOOT */
    /* We do not start collecting samples until traffic starts flowing */
    ncp_profiler_start(myTaskHdl->ncpHdl);
#endif

    NCP_CHECK((NULL != pNcpNcaV2_TaskSwState), NCP_ST_TASK_NO_GSM);


    NCP_CALL(ncp_task_v2_get_taskHdl((void *)&myTaskHdl));

    NCA_INC_CRITICAL_SECTION(myTaskHdl);

    NCP_TASK_CHECK_FOR_SHUTDOWN();

    NCP_VP_VALIDATE_HANDLE(vpHdl);

    NCP_CHECK((NULL != taskMetaData),
             (NCP_ST_TASK_SEND_NULL_METADATA_PTR));

    /* FIXME - add validation on dataSz, ptrCnt, and pduSegAddr and sizes */

    if (NCP_TASK_IS_SHARED_POOL(myTaskHdl->poolID))
    {
        if (sendDoneFn)
        {
            NCP_CALL(NCP_ST_TASK_SENDDONE_FN_WITH_VP_MANAGED_POOL);
        }
    }

    if (NCP_TASK_IS_CPU_POOL(myTaskHdl->poolID))
    {
        taskAuxData.clientFreeFn     = sendDoneFn;
        taskAuxData.clientFreeFnArg  = sendDoneFuncArg;
        if (0 !=
            (taskAuxData.ptrCnt = taskMetaData->ptrCnt))
        {

            switch(taskMetaData->ptrCnt)
            {
            case 6:
                taskAuxData.pduSegAddr5
                    = (ncp_uint64_t)(ncp_raw_addr_t)taskMetaData->pduSegAddr5;
            case 5:
                taskAuxData.pduSegAddr4
                    = (ncp_uint64_t)(ncp_raw_addr_t)taskMetaData->pduSegAddr4;
            case 4:
                taskAuxData.pduSegAddr3
                    = (ncp_uint64_t)(ncp_raw_addr_t)taskMetaData->pduSegAddr3;
            case 3:
                taskAuxData.pduSegAddr2
                    = (ncp_uint64_t)(ncp_raw_addr_t)taskMetaData->pduSegAddr2;
            case 2:
                taskAuxData.pduSegAddr1
                    = (ncp_uint64_t)(ncp_raw_addr_t)taskMetaData->pduSegAddr1;
            case 1:
                taskAuxData.pduSegAddr0
                    = (ncp_uint64_t)(ncp_raw_addr_t)taskMetaData->pduSegAddr0;
            default:
                break;
            }
        }
    }

    /*
     * Go add the send to the output PCQ (or thread local queue,  as appropriate)
     */

    ncpStatus =
             NCP_NCA_LOWLEVEL_TASK_NCAV2_NATIVE_SEND(myTaskHdl,
                                       vpHdl,
                                       taskMetaData,
                                       &taskAuxData,
                                       wait);

    if (NCP_ST_SUCCESS == ncpStatus)
    {
        NCP_TASK_INC_STAT(TxTask);

    }

NCP_RETURN_LABEL

    if (NCP_ST_SUCCESS == ncpStatus)
    {
        NCP_TASK_INC_STAT(api_send_ok);
    }
    else if (NCP_ST_TASK_SEND_QUEUE_FULL != ncpStatus)
    {
        NCP_TASK_INC_STAT(api_send_err);
    }

    NCA_DEC_CRITICAL_SECTION(myTaskHdl);
#endif /* NCP_DEV_SOCKET */
    return ncpStatus;
}


/*
 *  ncp_st_t ncp_task_v2_legacy_send(	ncp_task_hdl_t taskHdl,
 *                          ncp_vp_hdl_t vpHdl,
 *                      	ncp_task_send_meta_t *taskMetaData,
 *                      	void *taskData,
 *                      	ncp_bool_t wait,
 *                          ncp_task_send_done_fn_t sendDoneFn,
 *                          void *sendDoneFuncArg);
 *  This function is called to send a task.
 *  ncpHdl:  NCP handle returned by previous call to ncp_config.
 *  note Not needed if we can we get this from the vpHdl.
 *  vpHdl: Virtual Pipeline handle
 *  taskMetaData: Pointer to task meta data
 *  taskData: Pointer to task data
 *  wait:  Boolean flag. If set to TRUE, specifies that the call should block if necessary until task output queue resources are
 *               available to queue this task for transmission.
 *  sendDoneDoneFn: Function to be called when buffer associated when this ncp_task_send is no longer in use.
 *                            If non-zero,   the task API will not free the buffer.
  * sendDoneFuncArg: Client supplied Opaque argument to be included in call to sendDoneFn(),  if sendDoneFn() provided.
*/
ncp_st_t
ncp_task_v2_legacy_send(
	ncp_task_hdl_t        taskHdl,
	ncp_vp_hdl_t vpHdl,
	ncp_task_send_meta_t *clientTaskMetaData,
	void *taskBuffer,
	void *taskPduData,
	ncp_bool_t wait,
	ncp_task_send_done_fn_t sendDoneFn,
	void                    *sendDoneFuncArg)
{
    ncp_pvt_task_hdl_t *myTaskHdl = taskHdl;
    ncp_task_ncaV2_oPCQ_aux_data_t  taskAuxData={0};
    ncp_st_t ncpStatus= NCP_ST_SUCCESS;

#if 0 /* UBOOT */
    /* We do not start collecting samples until traffic starts flowing */
    ncp_profiler_start(myTaskHdl->ncpHdl);
#endif

    NCP_CHECK((NULL != pNcpNcaV2_TaskSwState), NCP_ST_TASK_NO_GSM);

    NCP_CALL(ncp_task_v2_get_taskHdl((void *)&myTaskHdl));

    NCA_INC_CRITICAL_SECTION(myTaskHdl);

    NCP_TASK_CHECK_FOR_SHUTDOWN();

    NCP_VP_VALIDATE_HANDLE(vpHdl);

    NCP_CHECK((NULL != clientTaskMetaData),
             (NCP_ST_TASK_SEND_NULL_METADATA_PTR));

    NCP_CHECK(!((NULL == taskPduData)
                && ( 0 != clientTaskMetaData->dataSize)),
                NCP_ST_TASK_SEND_NULL_TASK_PTR);

    if (NCP_TASK_IS_SHARED_POOL(myTaskHdl->poolID))
    {
        if (sendDoneFn)
        {
            NCP_CALL(NCP_ST_TASK_SENDDONE_FN_WITH_VP_MANAGED_POOL);
        }
    }

    if (NCP_TASK_IS_CPU_POOL(myTaskHdl->poolID))
    {
        taskAuxData.clientFreeFn     = sendDoneFn;
        taskAuxData.clientFreeFnArg  = sendDoneFuncArg;
        if (clientTaskMetaData->dataSize)
        {
            taskAuxData.ptrCnt           = 1;
            taskAuxData.pduSegAddr0
                = (ncp_uint64_t)(ncp_raw_addr_t)taskPduData;
        }
    }

    /*
     * Go add the send to the output PCQ (or thread local queue,  as appropriate)
     */

    ncpStatus =
             NCP_NCA_LOWLEVEL_TASK_LEGACY_SEND(myTaskHdl,
                                       vpHdl,
                                       clientTaskMetaData,
                                       taskPduData,                     &taskAuxData,
                                       wait);

    if (NCP_ST_SUCCESS == ncpStatus)
    {
        NCP_TASK_INC_STAT(TxTask);

    }

NCP_RETURN_LABEL

    if (NCP_ST_SUCCESS == ncpStatus)
    {
        NCP_TASK_INC_STAT(api_send_ok);
    }
    else if (NCP_ST_TASK_SEND_QUEUE_FULL != ncpStatus)
    {
        NCP_TASK_INC_STAT(api_send_err);
    }

    NCA_DEC_CRITICAL_SECTION(myTaskHdl);

    return ncpStatus;
}

ncp_st_t
ncp_task_v2_send_segments(
	ncp_task_hdl_t       taskHdl,
	ncp_vp_hdl_t         vpHdl,
	ncp_task_send_meta_t *clientTaskMetaData,
	ncp_uint8_t          numSegs,
    ncp_task_segment_entry_t    *pSegTable,
	ncp_bool_t                  wait,
	ncp_task_send_done_fn_t     sendDoneFn,
	void                        *sendDoneFuncArg)
{
    ncp_pvt_task_hdl_t *myTaskHdl = taskHdl;
    ncp_task_ncaV2_oPCQ_aux_data_t  taskAuxData = {0};
    ncp_st_t ncpStatus= NCP_ST_SUCCESS;

    NCP_CHECK((NULL != pNcpNcaV2_TaskSwState), NCP_ST_TASK_NO_GSM);

    NCP_CALL(ncp_task_v2_get_taskHdl((void *)&myTaskHdl));

    NCA_INC_CRITICAL_SECTION(myTaskHdl);

    NCP_TASK_CHECK_FOR_SHUTDOWN();

    NCP_VP_VALIDATE_HANDLE(vpHdl);

    NCP_CHECK((NULL != clientTaskMetaData),
               NCP_ST_TASK_SEND_NULL_METADATA_PTR);

    NCP_CHECK(!((NULL == pSegTable) || (0 == clientTaskMetaData->dataSize)
        || (0 == pSegTable[numSegs-1].size)),
                NCP_ST_TASK_SEND_SEGMENTS_INVALID_DESC);

    NCP_CHECK((!((0 == numSegs) || (numSegs > NCP_X7_MAX_PDU_SEGS))),
               NCP_ST_TASK_SEND_SEGMENTS_INVALID_NUM_SEGS);

   if (NCP_TASK_IS_SHARED_POOL(myTaskHdl->poolID))
    {
        if (sendDoneFn)
        {
            NCP_CALL(NCP_ST_TASK_SENDDONE_FN_WITH_VP_MANAGED_POOL);
        }
    }

    if (NCP_TASK_IS_CPU_POOL(myTaskHdl->poolID))
    {
        taskAuxData.clientFreeFn    = sendDoneFn;
        taskAuxData.clientFreeFnArg = sendDoneFuncArg;
        taskAuxData.ptrCnt           = numSegs;
        switch (numSegs)
        {
            case 6:
            taskAuxData.pduSegAddr5
                = (ncp_uint64_t)(ncp_raw_addr_t)pSegTable[5].addr;
            case 5:
            taskAuxData.pduSegAddr4
                = (ncp_uint64_t)(ncp_raw_addr_t)pSegTable[4].addr;
            case 4:
            taskAuxData.pduSegAddr3
                = (ncp_uint64_t)(ncp_raw_addr_t)pSegTable[3].addr;
            case 3:
            taskAuxData.pduSegAddr2
                = (ncp_uint64_t)(ncp_raw_addr_t)pSegTable[2].addr;
            case 2:
            taskAuxData.pduSegAddr1
                = (ncp_uint64_t)(ncp_raw_addr_t)pSegTable[1].addr;
            case 1:
            taskAuxData.pduSegAddr0
                = (ncp_uint64_t)(ncp_raw_addr_t)pSegTable[0].addr;
                break;
            default:
                NCP_CALL(NCP_ST_INVALID_VALUE);
        }
    }


    /*
     * Go add the send to the output PCQ (or thread local queue,  as appropriate)
     */
    ncpStatus = NCP_NCA_LOWLEVEL_TASK_LEGACY_SEND_SEGMENTS(myTaskHdl, vpHdl,
                         clientTaskMetaData, &taskAuxData, pSegTable, numSegs, wait);

    if (NCP_ST_SUCCESS == ncpStatus)
    {
        NCP_TASK_INC_STAT(TxTaskSegments);

    }

NCP_RETURN_LABEL


    if (NCP_ST_SUCCESS == ncpStatus)
    {
        NCP_TASK_INC_STAT(api_send_segments_ok);
    }
    else if (NCP_ST_TASK_SEND_QUEUE_FULL != ncpStatus)
    {
        NCP_TASK_INC_STAT(api_send_segments_err);
    }

    NCA_DEC_CRITICAL_SECTION(myTaskHdl);

    return ncpStatus;
}


/* FIXME - use abstraction here */
#ifndef NCP_DEV_SOCKET


/* Native ncaV2 API - task must be a receive buffer with optional pdu segments */
ncp_st_t
ncp_task_ncav2_free_rx_task(
	ncp_task_hdl_t taskHdl,
	ncp_task_ncaV2_recv_buf_t *task)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_pvt_task_hdl_t *myTaskHdl = (ncp_pvt_task_hdl_t *) taskHdl;
#if defined(NCP_KERNEL) && (defined(NCP_OSE) || defined(NCP_VXWORKS))
    spinlock_flags_t spinFlags = 0;
#endif

    NCP_CHECK((NULL != pNcpNcaV2_TaskSwState), NCP_ST_TASK_NO_GSM);

    NCP_CALL(ncp_task_v2_get_taskHdl((void *)&myTaskHdl));

    NCA_INC_CRITICAL_SECTION(myTaskHdl);

    NCP_TASK_CHECK_FOR_SHUTDOWN();

    if (NULL == task)
    {
        NCP_CALL(NCP_ST_TASK_NULL_TASK);
    }

    /* FIXME - add ncav2 apis for socket mode */
#ifdef NCP_DEV_SOCKET
    /* Return success - We forced automatic completion mode since we use the 34xx rdev interface for native mode */
    goto ncp_return;
#endif

    if (NCP_TASK_IS_SHARED_POOL(myTaskHdl->poolID))
    {
#if (NCP_TASK_NCAV2_SHPOOL_PTR_DEBUG) || defined(NCP_TASK_DBG_55XX_TASK_FLOW)
        NCP_LOG(NCP_MSG_INFO,
                    "DEALLOC ptrCnt=%d, va0=%p\r\n",
                    task->ptrCnt,
                    ((void *)(ncp_raw_addr_t)task->pduSegAddr0));
#endif

#ifndef NCP_TASK_DEALLOC_BUG
        /* VP Managed Pool,   let H/W free the tasks */
        NCP_NCA_LOWLEVEL_TASK_DEALLOC(myTaskHdl,
                (ncp_task_ncaV2_recv_buf_t *)task);
#else
        /*
         * SW Workaround
         * 55xx preproduction ASIC Only
         */

        NCP_CALL(ncp_task_free_task_with_dealloc_immediate(
                                             myTaskHdl,
                                             task));
#endif

    }
    else
    {
        /* free to CPU managed pool */
        switch(task->ptrCnt)
        {
            case 6:
                ncp_task_v2_CpuPool_free(
                    myTaskHdl->poolHdl,
                    (void *)(ncp_raw_addr_t)(task->pduSegAddr5));
            case 5:
                ncp_task_v2_CpuPool_free(
                    myTaskHdl->poolHdl,
                    (void *)(ncp_raw_addr_t)(task->pduSegAddr4));
            case 4:
                ncp_task_v2_CpuPool_free(
                    myTaskHdl->poolHdl,
                    (void *)(ncp_raw_addr_t)(task->pduSegAddr3));
            case 3:
                ncp_task_v2_CpuPool_free(
                    myTaskHdl->poolHdl,
                    (void *)(ncp_raw_addr_t)(task->pduSegAddr2));
            case 2:
                ncp_task_v2_CpuPool_free(
                    myTaskHdl->poolHdl,
                    (void *)(ncp_raw_addr_t)(task->pduSegAddr1));;
            case 1:
            case 0:
                ncp_task_v2_CpuPool_free(
                        myTaskHdl->poolHdl,
                        task);
                break;
            default:
                break;
        }
    }

NCP_RETURN_LABEL
    return(ncpStatus);
}

/* Native ncaV2 API - populate as needed */
ncp_st_t
ncp_task_ncav2_free_pdu_segments(
	ncp_task_hdl_t taskHdl,
	ncp_ncaV2_free_pdu_segments_t *pFreePduSegs)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_pvt_task_hdl_t *myTaskHdl = (ncp_pvt_task_hdl_t *) taskHdl;
#if defined(NCP_KERNEL) && (defined(NCP_OSE) || defined(NCP_VXWORKS))
    spinlock_flags_t spinFlags = 0;
#endif

    NCP_CHECK((NULL != pNcpNcaV2_TaskSwState), NCP_ST_TASK_NO_GSM);

    NCP_CALL(ncp_task_v2_get_taskHdl((void *)&myTaskHdl));

    NCA_INC_CRITICAL_SECTION(myTaskHdl);

    NCP_TASK_CHECK_FOR_SHUTDOWN();

    if ((NULL == pFreePduSegs) ||
        (0 == pFreePduSegs->ptrCnt))
    {
        NCP_CALL(NCP_ST_TASK_NULL_TASK);
    }

    /* FIXME - add ncav2 apis for socket mode */
#ifdef NCP_DEV_SOCKET
    /* Return success - We forced automatic completion mode since we use the 34xx rdev interface for native mode */
    goto ncp_return;
#endif

    if (NCP_TASK_IS_SHARED_POOL(myTaskHdl->poolID))
    {
#if (NCP_TASK_NCAV2_SHPOOL_PTR_DEBUG) || defined(NCP_TASK_DBG_55XX_TASK_FLOW)
            NCP_LOG(NCP_MSG_INFO,
                    "DEALLOC_IMMED ptrCnt=%d, va0=%p\r\n",
                    pFreePduSegs->ptrCnt,
                    ((void *)(ncp_raw_addr_t)pFreePduSegs->pduSegAddr0));
#endif

        /* VP Managed Pool,   let H/W free the tasks */
        NCP_NCA_LOWLEVEL_DEALLOC_IMMEDIATE(myTaskHdl,
                                           pFreePduSegs,
                                           TRUE);
    }
    else
    {
        /* free to CPU managed pool */
        switch(pFreePduSegs->ptrCnt)
        {
            case 6:
                ncp_task_v2_CpuPool_free(
                    myTaskHdl->poolHdl,
                    (void *)(ncp_raw_addr_t)(pFreePduSegs->pduSegAddr5));
            case 5:
                ncp_task_v2_CpuPool_free(
                    myTaskHdl->poolHdl,
                    (void *)(ncp_raw_addr_t)(pFreePduSegs->pduSegAddr4));
            case 4:
                ncp_task_v2_CpuPool_free(
                    myTaskHdl->poolHdl,
                    (void *)(ncp_raw_addr_t)(pFreePduSegs->pduSegAddr3));
            case 3:
                ncp_task_v2_CpuPool_free(
                    myTaskHdl->poolHdl,
                    (void *)(ncp_raw_addr_t)(pFreePduSegs->pduSegAddr2));
            case 2:
                ncp_task_v2_CpuPool_free(
                    myTaskHdl->poolHdl,
                    (void *)(ncp_raw_addr_t)(pFreePduSegs->pduSegAddr1));
            case 1:
                 ncp_task_v2_CpuPool_free(
                    myTaskHdl->poolHdl,
                    (void *)(ncp_raw_addr_t)(pFreePduSegs->pduSegAddr0));
                break;
            default:
                break;
        }
    }


NCP_RETURN_LABEL
    return(ncpStatus);
}

/* #if !defined(NCP_KERNEL) */
ncp_st_t
ncp_task_ncav2_buffer_alloc (
    ncp_task_hdl_t *taskHdl,
	ncp_uint32_t size,
	void **taskAddr)
{
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;
    ncp_pvt_task_hdl_t *myTaskHdl = (ncp_pvt_task_hdl_t *)taskHdl;

    debug("ncp_task_ncav2_buffer_alloc(): size=%d\n", size);

    NCP_CHECK ((NULL != taskAddr), NCP_ST_TASK_ALLOC_REQUIRES_POINTER);
    if (0 == size)
    {
	*taskAddr = NULL;
	    NCP_CALL(NCP_ST_TASK_REQUEST_FOR_ZERO_LENGTH_TASK_BUFFER);
    }

    if (NCP_TASK_IS_CPU_POOL(myTaskHdl->poolID))
    {
        NCP_CALL(ncp_task_v2_CpuPool_alloc(myTaskHdl->poolHdl, size, taskAddr));
    }
    else
    {
        NCP_CALL(ncp_task_v2_MMEpool_alloc(
                myTaskHdl,
                size,
                taskAddr));
#if (NCP_TASK_NCAV2_SHPOOL_PTR_DEBUG) || defined(NCP_TASK_DBG_55XX_TASK_FLOW)
        NCP_LOG(NCP_MSG_INFO,
                    "ALLOC va0=%p\r\n",
                    *taskAddr);
#endif
    }
NCP_RETURN_LABEL

    if (NCP_ST_SUCCESS == ncpStatus)
    {
        NCP_TASK_INC_STAT(api_task_buffer_alloc_ok);
    }
    else
    {
        NCP_TASK_INC_STAT(api_task_buffer_alloc_err);
    }
    return(ncpStatus);
}


ncp_st_t
ncp_task_ncav2_buffer_free (
    ncp_task_hdl_t *taskHdl,
	void *taskAddr)
{
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;
    ncp_pvt_task_hdl_t *myTaskHdl = (ncp_pvt_task_hdl_t *)taskHdl;

    if (NULL != taskAddr)
    {
        if (NCP_TASK_IS_CPU_POOL(myTaskHdl->poolID))
        {
            ncp_task_v2_CpuPool_free(myTaskHdl->poolHdl,
                                     taskAddr);
        }
        else
        {
#if (NCP_TASK_NCAV2_SHPOOL_PTR_DEBUG) || defined(NCP_TASK_DBG_55XX_TASK_FLOW)
            NCP_LOG(NCP_MSG_INFO,
                    "FREE va0=%p\r\n",
                    taskAddr);
#endif
            NCP_CALL(ncp_task_v2_MMEpool_free(myTaskHdl,
                                              taskAddr));
        }
    }
    else
    {
        NCP_CALL(NCP_ST_TASK_CLIENT_FREE_NULLPTR);
    }
NCP_RETURN_LABEL

    if (NCP_ST_SUCCESS == ncpStatus)
    {
        NCP_TASK_INC_STAT(api_task_buffer_free_ok);
    }
    else
    {
        NCP_TASK_INC_STAT(api_task_buffer_free_err);
    }

    return(ncpStatus);
}
#else /* NCP_DEV_SOCKET */
ncp_st_t
ncp_task_ncav2_free_rx_task(
	ncp_task_hdl_t taskHdl,
	ncp_task_ncaV2_recv_buf_t *task)
{
    return(NCP_ST_NOT_IMPLEMENTED);
}


ncp_st_t
ncp_task_ncav2_free_pdu_segments(
	ncp_task_hdl_t taskHdl,
	ncp_ncaV2_free_pdu_segments_t *pFreePduSegs)
{
    return(NCP_ST_NOT_IMPLEMENTED);
}

ncp_st_t
ncp_task_ncav2_buffer_alloc (
    ncp_task_hdl_t *taskHdl,
	ncp_uint32_t size,
	void **taskAddr)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    if (NULL == (*taskAddr = ncp_malloc(size)))
    {
        NCP_CALL(NCP_ST_NO_MEMORY);
    }
NCP_RETURN_LABEL
    return(ncpStatus);
}

ncp_st_t
ncp_task_ncav2_buffer_free (
    ncp_task_hdl_t *myTaskHdl,
	void *taskAddr)
{
    ncp_free(taskAddr);
    return(NCP_ST_SUCCESS);
}


#endif /* NCP_DEV_SOCKET */

NCP_API ncp_st_t
ncp_task_v2_reset_stats(ncp_hdl_t ncpHdl )
{
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;

    if (0 == NCP_TASK_COLLECT_STATS)
    {
        NCP_CALL(NCP_ST_TASK_STATS_DISABLED);
    }

    NCP_CHECK((NULL != pNcpNcaV2_TaskSwState), NCP_ST_TASK_NO_GSM);

    NCP_NCA_VALIDATE_NCP_HDL(ncpHdl);

    ncp_memset(&pNcpNcaV2_TaskSwState->myTaskStats, 0, sizeof(ncp_task_stats_t));

NCP_RETURN_LABEL
    return(ncpStatus);
}

NCP_API ncp_st_t
ncp_task_v2_get_stats(	ncp_hdl_t ncpHdl,
                        ncp_task_stats_t *pStats)
{
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;


    if (0 == NCP_TASK_COLLECT_STATS)
    {
        NCP_CALL(NCP_ST_TASK_STATS_DISABLED);
    }

    NCP_CHECK((NULL != pNcpNcaV2_TaskSwState), NCP_ST_TASK_NO_GSM);

    NCP_NCA_VALIDATE_NCP_HDL(ncpHdl);

    memcpy(pStats, &pNcpNcaV2_TaskSwState->myTaskStats, sizeof(ncp_task_stats_t));

#if 0 /* FIXME - print for all pools */
    {


    pStats->stat_upool_sz0_buffers_total = pPoolEntry->u.cpu.buffListArray[0].numTotal;
    pStats->stat_upool_sz1_buffers_total = pPoolEntry->u.cpu.buffListArray[1].numTotal;
    pStats->stat_upool_sz2_buffers_total = pPoolEntry->u.cpu.buffListArray[2].numTotal;
    pStats->stat_upool_sz3_buffers_total = pPoolEntry->u.cpu.buffListArray[3].numTotal;

    pStats->stat_upool_sz0_buffers_free =  pPoolEntry->u.cpu.buffListArray[0].numFree;
    pStats->stat_upool_sz1_buffers_free =  pPoolEntry->u.cpu.buffListArray[1].numFree;
    pStats->stat_upool_sz2_buffers_free =  pPoolEntry->u.cpu.buffListArray[2].numFree;
    pStats->stat_upool_sz3_buffers_free =  pPoolEntry->u.cpu.buffListArray[3].numFree;

    pStats->stat_upool_sz0_buffers_low_water = pPoolEntry->u.cpu.buffListArray[0].freeLowWaterMark;
    pStats->stat_upool_sz1_buffers_low_water = pPoolEntry->u.cpu.buffListArray[1].freeLowWaterMark;
    pStats->stat_upool_sz2_buffers_low_water = pPoolEntry->u.cpu.buffListArray[2].freeLowWaterMark;
    pStats->stat_upool_sz3_buffers_low_water = pPoolEntry->u.cpu.buffListArray[3].freeLowWaterMark;

    /* Kernel Mode Buffer Pool Statistics */
    pPoolEntry = &pNcpNcaV2_TaskSwState->k_pool;

    pStats->stat_kpool_sz0_buffers_total = pPoolEntry->u.cpu.buffListArray[0].numTotal;
    pStats->stat_kpool_sz1_buffers_total = pPoolEntry->u.cpu.buffListArray[1].numTotal;
    pStats->stat_kpool_sz2_buffers_total = pPoolEntry->u.cpu.buffListArray[2].numTotal;
    pStats->stat_kpool_sz3_buffers_total = pPoolEntry->u.cpu.buffListArray[3].numTotal;

    pStats->stat_kpool_sz0_buffers_free =  pPoolEntry->u.cpu.buffListArray[0].numFree;
    pStats->stat_kpool_sz1_buffers_free =  pPoolEntry->u.cpu.buffListArray[1].numFree;
    pStats->stat_kpool_sz2_buffers_free =  pPoolEntry->u.cpu.buffListArray[2].numFree;
    pStats->stat_kpool_sz3_buffers_free =  pPoolEntry->u.cpu.buffListArray[3].numFree;

    pStats->stat_kpool_sz0_buffers_low_water = pPoolEntry->u.cpu.buffListArray[0].freeLowWaterMark;
    pStats->stat_kpool_sz1_buffers_low_water = pPoolEntry->u.cpu.buffListArray[1].freeLowWaterMark;
    pStats->stat_kpool_sz2_buffers_low_water = pPoolEntry->u.cpu.buffListArray[2].freeLowWaterMark;
    pStats->stat_kpool_sz3_buffers_low_water = pPoolEntry->u.cpu.buffListArray[3].freeLowWaterMark;
#endif   /* FIXME - print for all pools */

NCP_RETURN_LABEL
    return(ncpStatus);

}

#if 0 /* UBOOT */
ncp_st_t
ncp_task_v2_shutdown(ncp_uint32_t devNum)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

#ifndef NCP_DEV_SOCKET
    ncp_dev_hdl_t devHdl = NULL;

    NCP_CALL(ncp_dev_open(devNum, 0, &devHdl));


    NCP_TASK_INITIATE_SHUTDOWN(devHdl);

    ncp_dev_close(devHdl);
#else
    {

        /* Nothing to do here */

    }
#endif /* NCP_DEV_SOCKET */

NCP_RETURN_LABEL
    if(ncpStatus != NCP_ST_SUCCESS)
    {
        NCP_MSG(NCP_MSG_INFO, "ncpTaskShutdown failed. status=%s.\n", ncp_status_get(ncpStatus));
    }

    return(ncpStatus);
}

ncp_st_t
ncp_task_v2_shutdown_wait(
    ncp_hdl_t   ncpHdl)
{
#if defined(NCP_KERNEL) && !defined(NCP_VXWORKS)
    ncp_st_t    ncpStatus = NCP_ST_NOT_IMPLEMENTED;
#else
    ncp_st_t    ncpStatus = NCP_ST_SUCCESS;
#endif /* defined(NCP_KERNEL) && !defined(NCP_VXWORKS) */

NCP_RETURN_LABEL
    if(ncpStatus != NCP_ST_SUCCESS)
    {
        NCP_MSG(NCP_MSG_INFO,
                "ncpTaskShutdownWait failed. status=%s.\n",
                ncp_status_get(ncpStatus));
    }

    return(ncpStatus);
}

#endif /* UBOOT */


ncp_st_t
ncp_task_v2_attach_to_gsm(ncp_hdl_t ncpHdl,
                          void **pDomainBundle,
                          void **pTaskSwState)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_t *myNcpHdl = (ncp_t *)ncpHdl;
    ncp_nca_t *ncaHdl   = myNcpHdl->ncaHdl;

    if (NULL == ncaHdl)
    {
        return(ncpStatus); /* NCA not configured,   no need to attach to gsm */
    }

    pNcpNcaV2_TaskSwState = ncaHdl->myNcpNcaTaskState;

#ifndef NCP_DEV_SOCKET
    if ((ncp_dev_hdl_t)-1 != (ncp_dev_hdls[myNcpHdl->id]))
    {
        NCP_CALL(ncp_task_v2_mmap_attach(ncp_dev_hdls[myNcpHdl->id], (void **)pDomainBundle, (ncp_task_ncaV2_t **)pTaskSwState));

        *pTaskSwState = ncaHdl->myNcpNcaTaskState; /* in NVM for 55xx! */
    }

#else

    if (NULL == (*pTaskSwState = ncaHdl->myNcpNcaTaskState))
    {
            NCP_CALL(NCP_ST_TASK_NO_GSM);
    }

#endif /* !NCP_DEV_SOCKET */

NCP_RETURN_LABEL
    return(ncpStatus);
}

#if 0 /* UBOOT */

/*
 *  ncp_st_t ncp_nca_bp_dest_val_get(ncp_hdl_t ncpHdl, ncp_uint8_t destBit,
 *                                   ncp_bool_t *destVal);
 *  For a given dest bit, this function returns the NCA backpressure state.
 *  ncpHdl:  NCP handle.
 *  destBit: The bp dest bit that needs to be queried.
 *           Valid values: 0-11 (rev 1.0), 0-31 (rev 1.1)
 *  destVal: TRUE - if bp state is on for the given bit.
 *           FALSE - if bp state is off for the given bit.
 */

ncp_st_t
ncp_nca_v2_bp_dest_val_get(ncp_hdl_t ncpHdl, ncp_uint8_t destBit,
                        ncp_bool_t *destVal)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
#if !defined(NCP_KERNEL) || defined(NCP_VXWORKS)
    ncp_t *ncp = (ncp_t *)ncpHdl;
    ncp_dev_hdl_t devHdl = ncp_dev_hdls[ncp->id];
#else
    ncp_dev_hdl_t devHdl = NULL;
#endif
    ncp_nca_otask_opcq_backpressure_t bpDest = { 0 };
    ncp_uint32_t *reg = (ncp_uint32_t *)&bpDest;
    ncp_uint32_t val = 0;
    /* TODO: This API is not currently implemented for kernel mode. */
#if defined(NCP_KERNEL) && !defined(NCP_VXWORKS)
    NCP_CALL(NCP_ST_NOT_IMPLEMENTED);
#endif
    NCP_NCA_VALIDATE_NCP_HDL(ncpHdl);

    /* Check the dest bit to be within range */
    if(destBit > 31) {
        NCP_CALL(NCP_ST_NCA_BP_DEST_BIT_INVALID);
    }

    NCP_ASSERT(destVal != NULL, NCP_ST_NCA_BP_BUFFER_INVALID);

    /* read the reg */
    NCP_CALL(ncp_read32(devHdl,
                        NCP_REGION_NCA_AXI,
                        NCP_NCA_OTASK_OPCQ_BP_55XX,
                        reg));
    val = 1 << destBit;
    if ((val & bpDest.otask_dest_bp) == val)
    {
        *destVal = TRUE;
    }
    else
    {
        *destVal = FALSE;
    }
NCP_RETURN_LABEL
    return ncpStatus;
}

ncp_st_t
ncp_nca_v2_bp_state_get(ncp_hdl_t ncpHdl, ncp_uint32_t *bpState)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
#if !defined(NCP_KERNEL) || defined(NCP_VXWORKS)
    ncp_t *ncp = (ncp_t *)ncpHdl;
    ncp_dev_hdl_t devHdl = ncp_dev_hdls[ncp->id];
#else
    ncp_dev_hdl_t devHdl = NULL;
#endif

    /* TODO: This API is not currently implemented for kernel mode. */
#if defined(NCP_KERNEL) && !defined(NCP_VXWORKS)
    NCP_CALL(NCP_ST_NOT_IMPLEMENTED);
#endif
    NCP_NCA_VALIDATE_NCP_HDL(ncpHdl);

    NCP_ASSERT(bpState != NULL, NCP_ST_NCA_BP_BUFFER_INVALID);

    /* read the reg */
    NCP_CALL(ncp_read32(devHdl,
                        NCP_REGION_NCA_AXI,
                        NCP_NCA_OTASK_OPCQ_BP_55XX,
                        bpState));
NCP_RETURN_LABEL
    return ncpStatus;
}
#endif /* UBOOT */




#if 0 /* UBOOT */
#if !defined(NCP_KERNEL) || defined(NCP_VXWORKS)

static void
ncp_task_v2_make_key()
{
    (void) pthread_key_create(&gNcaTask_key, NULL);
}


ncp_st_t
ncp_task_v2_get_taskHdl(ncp_task_hdl_t **taskHdl)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    if (NULL == *taskHdl)
    {

        if (NULL == (*taskHdl = pthread_getspecific(gNcaTask_key)))
        {

            ncpStatus = NCP_ST_TASK_TLS_RETRIEVAL_ERR;
        }
    }
    if ((ncpStatus == NCP_ST_SUCCESS)
        && (NCP_TASK_HDL_COOKIE != (((ncp_pvt_task_hdl_t *)*taskHdl))->cookie))
    {
        ncpStatus = NCP_ST_TASK_INVALID_TASK_HANDLE;
    }

NCP_RETURN_LABEL
    return(ncpStatus);
}

static void
ncp_task_v2_destroy_key()
{
    pthread_setspecific(gNcaTask_key, NULL);

NCP_RETURN_LABEL
    return;
}

static ncp_st_t
ncp_task_v2_store_taskHdl(ncp_pvt_task_hdl_t *myTaskHdl)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_pvt_task_hdl_t *tmpTaskHdl;
    int ret = 0;


    ret = pthread_once(&gNcaTask_key_once, ncp_task_v2_make_key);
    NCP_ASSERT(ret == 0, NCP_ST_PTHREAD_ONCE_ERROR);

    if (NULL == (tmpTaskHdl = (ncp_pvt_task_hdl_t *)pthread_getspecific(gNcaTask_key))) {
        ret = pthread_setspecific(gNcaTask_key, (void *)myTaskHdl);
        NCP_ASSERT(ret == 0, NCP_ST_PTHREAD_SETSPECIFIC_ERROR);
    }
    else if (tmpTaskHdl != myTaskHdl)
    {
        /* same thread called task_hdl_create more than once? */
        NCP_CALL(NCP_ST_TASK_INVALID_TASK_HANDLE);
    }


NCP_RETURN_LABEL
    return(ncpStatus);
}

#else  /* NCP_KERNEL */

ncp_st_t
ncp_task_v2_get_taskHdl(ncp_task_hdl_t **taskHdl)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    if (NULL == (*taskHdl = (ncp_task_hdl_t *)kernelTaskHdl))
    {
        NCP_CALL(NCP_ST_TASK_TLS_RETRIEVAL_ERR)
    }

    if (NCP_TASK_HDL_COOKIE != (((ncp_pvt_task_hdl_t *)*taskHdl))->cookie)
    {
        NCP_CALL(NCP_ST_TASK_INVALID_TASK_HANDLE);
    }

NCP_RETURN_LABEL
    return(ncpStatus);
}

static void
ncp_task_v2_destroy_key()
{
    kernelTaskHdl = NULL;
    return;
}

static ncp_st_t
ncp_task_v2_store_taskHdl(ncp_pvt_task_hdl_t *myTaskHdl)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    if (NULL == (kernelTaskHdl = ncp_nvm_malloc(sizeof(ncp_pvt_task_hdl_t))))
    {
        NCP_CALL(NCP_ST_TASK_HDL_CREATE_ERR);
    }
    ncp_memcpy(kernelTaskHdl, myTaskHdl, sizeof(ncp_pvt_task_hdl_t));

NCP_RETURN_LABEL
    return(ncpStatus);
}


#endif  /* NCP_KERNEL */
#endif /* UBOOT */


/*
 * =============================
 * old ncp_task_internal.c
 * =============================
 */

 /*
 * Task internal support functions
 */

ncp_st_t
ncp_task_v2_validate_input_queue_binding(ncp_task_pcq_t *pcq)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    if (0 != pcq->pcqUseCnt)
    {
        NCP_CALL(NCP_ST_TASK_EXCLUSIVE_BINDING_NOT_AVAIL);
    }

NCP_RETURN_LABEL
    return ncpStatus;
}

ncp_st_t ncp_task_v2_find_recv_queue(ncp_pvt_task_hdl_t *taskHdl, ncp_uint8_t recvQueueId, ncp_pvt_task_recv_queue_t **recvQueue)
{
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;
    ncp_pvt_task_recv_queue_t *tmp_recvQueue;

    NCP_ASSERT (NULL != (tmp_recvQueue = taskHdl->currRecvPtr), NCP_ST_TASK_INVALID_RECEIVE_QUEUE);
    do
    {
        if (tmp_recvQueue->recvQueueId == recvQueueId)
        {
            *recvQueue = tmp_recvQueue;    /* return pointer */
            break;
        }
        tmp_recvQueue = tmp_recvQueue->next;
    } while(taskHdl->currRecvPtr != tmp_recvQueue);

    if (tmp_recvQueue->recvQueueId != recvQueueId)
    {
        NCP_CALL(NCP_ST_TASK_INVALID_RECEIVE_QUEUE);
    }
NCP_RETURN_LABEL

    return(ncpStatus);
}

ncp_st_t
ncp_task_v2_initialize_sw_task_input_queue(ncp_pvt_task_hdl_t *myTaskHdl,                                                        ncp_pvt_task_recv_queue_t *recvQueuePtr,                                              ncp_task_pcq_t *pcq,
                                   ncp_bool_t fixedRecvQueueId,
                                   ncp_uint8_t *pRecvQueueId)
{
    ncp_st_t ncpStatus = NCP_ST_NO_MEMORY;

    /*
     * We need a s/w queue structure, since we are not accessing the NCA queue structures directly
     */

    NCP_ASSERT((NULL != recvQueuePtr), NCP_ST_TASK_NULL_RECV_QUEUE_PTR);

    /*
     * First validate fixed ID,   or find a free synamic ID
     */
    if (FALSE == fixedRecvQueueId)
    {
        int i;
        for (i=NCP_START_DYNAMIC_RECV_QUEUE; i<=NCP_MAX_DYNAMIC_RECV_QUEUE; i++)
        {
#ifdef NCP_NCA_USE_GLOBAL_RECVQUEUEID
            if (FALSE == pNcpNcaV2_TaskSwState->perNca_recvQ_IDs[0].inUse[i])
#else
            if (FALSE == pNcpNcaV2_TaskSwState->perNca_recvQ_IDs[ncaQueueId].inUse[i])
#endif
            {
                *pRecvQueueId = i;
                break;
            }
        }
        if (i > NCP_MAX_DYNAMIC_RECV_QUEUE)
        {
            NCP_CALL(NCP_ST_TASK_NO_FREE_DYNAMIC_QUEUE);
        }
    }
    else
    {
#ifdef NCP_NCA_USE_GLOBAL_RECVQUEUEID
        if (TRUE == pNcpNcaV2_TaskSwState->perNca_recvQ_IDs[0].inUse[*pRecvQueueId])
#else
        if (TRUE == pNcpNcaV2_TaskSwState->perNca_recvQ_IDs[ncaQueueId].inUse[*pRecvQueueId])
#endif
        {
            NCP_CALL(NCP_ST_TASK_INVALID_FIXED_QUEUEID);
        }
    }
#ifdef NCP_NCA_USE_GLOBAL_RECVQUEUEID
    pNcpNcaV2_TaskSwState->perNca_recvQ_IDs[0].inUse[*pRecvQueueId] = TRUE;
#else
    pNcpNcaV2_TaskSwState->perNca_recvQ_IDs[ncaQueueId].inUse[*pRecvQueueId] = TRUE;
#endif


    /*
     * Allocate from cacheable portion of GSM.   Must be continuously visible to both user and kernel software.
     */

    NCP_CALL(ncp_task_v2_link_queue_to_taskHdl(myTaskHdl,
                                    &recvQueuePtr->taskQueue,
                                    NCP_TASK_PCQ_INPUT,
                                    pcq->ncaQueueId));

    /*
     * We need the NCA queue ID here in order to init pointers and bind tables
     */

    recvQueuePtr->recvQueueId  = *pRecvQueueId;

    /*
     * Hook the newly allocated structure
     */

    if (NULL == myTaskHdl->currRecvPtr)
    {
        myTaskHdl->currRecvPtr = recvQueuePtr;
        recvQueuePtr->next = recvQueuePtr; /* if only entry,   then point to self */
    }
    else
    {
        ncp_pvt_task_recv_queue_t *ptr = myTaskHdl->currRecvPtr;
        while(1)
        {
            /* Find end */
            if (ptr->next == myTaskHdl->currRecvPtr)
            {
                ptr->next = recvQueuePtr;
                recvQueuePtr->next = myTaskHdl->currRecvPtr;
                break;
            }
            else
            {
                ptr = ptr->next;
            }
        }
    }

    ncpStatus = NCP_ST_SUCCESS;

NCP_RETURN_LABEL

    return ncpStatus;
}




void nca_task_v2_display_task_stats(void)
{
#ifndef NCP_KERNEL
    if (NULL != pNcpNcaV2_TaskSwState)
    {
        int i;

        ncp_uint32_t *pStats = (ncp_uint32_t *)&pNcpNcaV2_TaskSwState->myTaskStats;


        printf("\r\n");

        i = sizeof(ncp_task_stats_t) / sizeof(ncp_uint32_t);
        while(0 != i--)
        {
            if (0 == (i%8))
            {
                printf("\r\n");
            }
            printf("0x%08X    ",*pStats++);
        }

    }
#endif
    return;
}

#ifdef NCP_PROFILER

ncp_uint16_t profileVal; /* Global */

void ncp_task_v2_profiler_nca_mem_tests(ncp_hdl_t ncpHdl, int run_tests_count)
{

    ncp_uint64_t val64start;
    ncp_uint64_t val64stop;
    char *pProfileMem;
    char *pMallocMem;
    char *pSaveProfileMem;
    int i;
    volatile ncp_uint16_t *p16;

    ncp_task_ncaV2_pool_t *pPoolEntry  = &pNcpNcaV2_TaskSwState->NCA_TASK_BUFF_POOL;


    /*
     * We'll use this for testing malloc memory,   as well as for preserving the other 128KB targets
     */

    pMallocMem     = ncp_malloc(NCP_PROFILER_NCA_MEM_PROFILE_SZ);
    pSaveProfileMem = ncp_malloc(NCP_PROFILER_NCA_MEM_PROFILE_SZ);

    /*
     * Profile speed of malloc mem
     */
    pProfileMem = pMallocMem;
    memcpy(pSaveProfileMem, pProfileMem, NCP_PROFILER_NCA_MEM_PROFILE_SZ);  /* Save current contents - not necessary,   but consistent */

#if NCP_PROFILER_MEM_MALLOC_WRITE_ENABLED
    {
        for (i = 0; i < run_tests_count; i++)
        {
            /* write 128K */
            ncp_memset(pProfileMem, 0, NCP_PROFILER_NCA_MEM_PROFILE_SZ);
        }
    }
#endif

#if NCP_PROFILER_MEM_MALLOC_READ_WRITE_ENABLED
    {
        for (i = 0; i < run_tests_count; i++)
        {
            /* read/write 128K */
            memcpy(pProfileMem, pProfileMem + (NCP_PROFILER_NCA_MEM_PROFILE_SZ/2), (NCP_PROFILER_NCA_MEM_PROFILE_SZ/2));
            memcpy(pProfileMem + (NCP_PROFILER_NCA_MEM_PROFILE_SZ/2), pProfileMem, (NCP_PROFILER_NCA_MEM_PROFILE_SZ/2));
        }
    }
#endif

    memcpy(pProfileMem, pSaveProfileMem, NCP_PROFILER_NCA_MEM_PROFILE_SZ); /* Restore contents, for consistensy between tests */


    /*
     * And now DMA/MMIO GSM - use buffers region so we do not step on control data structures shared with hardware.
     */
    pProfileMem = (char *)pPoolEntry->u.cpu.poolBuffersBaseVA;
    memcpy(pSaveProfileMem, pProfileMem, NCP_PROFILER_NCA_MEM_PROFILE_SZ); /* Save current contents */


#if NCP_PROFILER_MEM_GSM_WRITE_ENABLED
    {
        for (i = 0; i < run_tests_count; i++)
        {
            /* write 128K */
            ncp_memset(pProfileMem, 0, NCP_PROFILER_NCA_MEM_PROFILE_SZ);
        }
    }
#endif


#if NCP_PROFILER_MEM_GSM_READ_WRITE_ENABLED
    {

        for (i = 0; i < run_tests_count; i++)
        {
            /* read/write 128K */
            memcpy(pProfileMem, pProfileMem + (NCP_PROFILER_NCA_MEM_PROFILE_SZ/2), (NCP_PROFILER_NCA_MEM_PROFILE_SZ/2));
            memcpy(pProfileMem + (NCP_PROFILER_NCA_MEM_PROFILE_SZ/2), pProfileMem, (NCP_PROFILER_NCA_MEM_PROFILE_SZ/2));
        }
    }
#endif

    memcpy(pProfileMem, pSaveProfileMem, NCP_PROFILER_NCA_MEM_PROFILE_SZ);  /* restore contents */

    /*
     * And now TASK GSM (SW ONLY)
     */
    pProfileMem = (char *)pNcpNcaV2_TaskSwState;
    memcpy(pSaveProfileMem, pProfileMem, NCP_PROFILER_NCA_MEM_PROFILE_SZ); /* Save current contents */

#if NCP_PROFILER_MEM_TASKGSM_WRITE_ENABLED
    {
        for (i = 0; i < run_tests_count; i++)
        {
            /* write 128K */
            ncp_memset(pProfileMem, 0, NCP_PROFILER_NCA_MEM_PROFILE_SZ);
        }
    }
#endif

#if NCP_PROFILER_MEM_TASKGSM_READ_WRITE_ENABLED
    {
        for (i = 0; i < run_tests_count; i++)
        {
            /* read/write 128K */
            memcpy(pProfileMem, pProfileMem + (NCP_PROFILER_NCA_MEM_PROFILE_SZ/2), (NCP_PROFILER_NCA_MEM_PROFILE_SZ/2));
            memcpy(pProfileMem + (NCP_PROFILER_NCA_MEM_PROFILE_SZ/2), pProfileMem, (NCP_PROFILER_NCA_MEM_PROFILE_SZ/2));
        }
    }
#endif

    memcpy(pProfileMem, pSaveProfileMem, NCP_PROFILER_NCA_MEM_PROFILE_SZ);    /* restore contents */

    /*
     * PROFILE NCA PGIT READ ACCESS
     */

#if NCP_PROFILER_NCA_PGIT_ENABLED
    {

        for (i=0; i< run_tests_count; i++)
        {
            p16 = (volatile ncp_uint16_t *)pNcpNcaV2_TaskSwState->hw.nca_pgit[0].ptr;

            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;

        }
    }
#endif

#if NCP_PROFILER_NCA_PGIT_MEMCPY_ENABLED
    {

        p16 = (volatile ncp_uint16_t *)pNcpNcaV2_TaskSwState->hw.nca_pgit[0].ptr;
        for (i=0; i< run_tests_count; i++)
        {
            memcpy(pMallocMem, (ncp_uint16_t *)p16, sizeof(ncp_dev_nca_pgit_t));
        }
    }
#endif

#if NCP_PROFILER_NCA_PGIT_READ16_ENABLED
    {

        p16 = (volatile ncp_uint16_t *)pNcpNcaV2_TaskSwState->hw.nca_pgit[0].ptr;
        for (i=0; i< run_tests_count; i++)
        {
           profileVal = (volatile ncp_uint16_t)*p16;
        }
    }
#endif

#if NCP_PROFILER_NCA_PGIT_READ16_5US_DELAY_ENABLED
    {

        p16 = (volatile ncp_uint16_t *)pNcpNcaV2_TaskSwState->hw.nca_pgit[0].ptr;
        ncp_sys_usleep(5UL);
        for (i=0; i< run_tests_count; i++)
        {
           profileVal = (volatile ncp_uint16_t)*p16;
           ncp_sys_usleep(5UL);
        }
    }
#endif

    /*
     * PROFILE CPU PGIT READ ACCESS
     */


#if NCP_PROFILER_CPU_PGIT_ENABLED
    {


        for (i=0; i< run_tests_count; i++)
        {
            p16 = (volatile ncp_uint16_t *)pNcpNcaV2_TaskSwState->hw.cpu_pgit[0].ptr;

            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;
            profileVal = (volatile ncp_uint16_t)*p16++;

        }
    }
#endif

#if NCP_PROFILER_CPU_PGIT_MEMCPY_ENABLED
    {

        p16 = (volatile ncp_uint16_t *)pNcpNcaV2_TaskSwState->hw.cpu_pgit[0].ptr;
        for (i=0; i< run_tests_count; i++)
        {
            memcpy(pMallocMem, (ncp_uint16_t *)p16, sizeof(ncp_dev_cpu_pgit_t));
        }

    }
#endif

#if NCP_PROFILER_CPU_PGIT_READ16_ENABLED
    {
        p16 = (volatile ncp_uint16_t *)pNcpNcaV2_TaskSwState->hw.cpu_pgit[0].ptr;
        for (i=0; i< run_tests_count; i++)
        {
           profileVal = (volatile ncp_uint16_t)*p16;
        }
    }
#endif

#if NCP_PROFILER_CPU_PGIT_READ16_5US_DELAY_ENABLED
    {
        p16 = (volatile ncp_uint16_t *)pNcpNcaV2_TaskSwState->hw.cpu_pgit[0].ptr;
        ncp_sys_usleep(5UL);
        for (i=0; i< run_tests_count; i++)
        {
           profileVal = (volatile ncp_uint16_t)*p16;
           ncp_sys_usleep(5UL);
        }
    }
#endif

    ncp_free(pMallocMem);
    ncp_free(pSaveProfileMem);

    return;
}


#endif /* NCP_TASK_PROFILE */




/*
 * =============================
 * old ncp_dev_nca.c
 * =============================
 */





/* --- Forward References --- */



/* --- Functions --- */

/*
 * Useful placeholder for setting breakpoints (especially if called from w/in a macro)
 */

void
ncp_task_v2_breakpoint(int reason)
{
#if 1
    volatile int i=0; /* so we can change it in the debugger */

    NCP_MSG(NCP_MSG_INFO, "***ERROR*** In ncp_task_v2_breakpoint; reason=%d - please attach and debug\r\n", reason);
    while(i==0)
    {
	ncp_sys_usleep(1000000);
    }
#endif
    return;
}

#if defined(NCP_KERNEL) || defined(NCP_VXWORKS)

ncp_st_t
ncp_task_v2_fill_kernel_mempool(ncp_nca_fill_kernel_memPool_t *pFillPool)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
#if 0 /* FIXME */
    int ok=0;
    int buffId = pFillPool->startingBuffId;
    ncp_task_pcq_t *r_PCQ = &pNcpNcaV2_TaskSwState->rPCQs[pFillPool->queueNum];



    for (ok=0; ok < pFillPool->numBuffs; )
    {

        if (NCP_ST_SUCCESS != (ncpStatus = ncp_task_v2_supply_freebuffer_to_nca(r_PCQ, pFillPool->size, NULL, buffId++, TRUE)))
        {
#ifdef NCP_KERNEL
            ncpStatus = NCP_ST_SUCCESS; /* normal for skbuffs */
#endif
            break;
        }
        ok++;
    }
#endif /* #if 0 FIXME */
#if 0
    NCP_MSG(NCP_MSG_INFO, "Allocated %d kernel task receive buffers\r\n",ok);
#endif
    return(ncpStatus);
}
#endif

#ifdef NCP_TASK_DBG_BUFFERS
/* FIXME for all functions in this section - does not currently work for multiple pools */


/*
 * Return index and normailzed buffer address
 */
ncp_uint32_t ncp_task_v2_debug_array_index(
        void *taskAddr,
        void **buffStartAddr,
        int poolID)
{
    ncp_task_ncaV2_pool_t *pPoolEntry
        = &pNcpNcaV2_TaskSwState->taskMemoryPool[poolID];
    int index=0;
    int i;

    if (   ((ncp_raw_addr_t)taskAddr >  (ncp_raw_addr_t)(pPoolEntry->pool_EndVA))
        || ((ncp_raw_addr_t)taskAddr <  (ncp_raw_addr_t)(pPoolEntry->pool_VA)))
    {
        NCP_MSG( NCP_MSG_ERROR, "Bad task buffer passed to ncp_task_get_debug_array_index, addr=0x%p, low=0x%x, high=0x%x\r\n",
            taskAddr,
            (ncp_raw_addr_t)(pPoolEntry->u.cpu.poolBuffersBaseVA),
            (ncp_raw_addr_t)(pPoolEntry->u.cpu.poolBuffersEndVA));
        ncp_task_v2_breakpoint(0x80);
    }

    for (i=0; i < NCP_TASK_NUM_BUFF_SIZES; i++)
    {
        if (((ncp_raw_addr_t)taskAddr >= (ncp_raw_addr_t)(pPoolEntry->u.cpu.buffListArray[i].VAstart))
            && ((ncp_raw_addr_t)taskAddr < (ncp_raw_addr_t)(pPoolEntry->u.cpu.buffListArray[i].VAend)))
        {
            taskAddr = *buffStartAddr = (void*)
                ((ncp_raw_addr_t)(taskAddr)
                & pPoolEntry->u.cpu.buffListArray[i].mask);
            index
                += (int)(((ncp_uint32_t)taskAddr
                    - (ncp_uint32_t)pPoolEntry->u.cpu.buffListArray[i].VAstart)
                    / (ncp_uint32_t)(pPoolEntry->u.cpu.buffListArray[i].size));
            break;
        }
        else
        {
            index += pPoolEntry->u.cpu.buffListArray[i].numTotal;
        }
    }
    return(index);
}

void
ncp_task_v2_verify_not_free(void *taskAddr, int poolID)
{
    void *buffStartAddr;
    int index;

    index = ncp_task_v2_debug_array_index(taskAddr, &buffStartAddr, poolID);

    if (NULL == pNcpNcaV2_TaskSwState->allocated[index])
    {
            NCP_MSG( NCP_MSG_ERROR, "(ERROR), taskAddr %p is on free list!\r\n", buffStartAddr);
            ncp_task_v2_breakpoint(53);
    }
    else if (buffStartAddr != pNcpNcaV2_TaskSwState->allocated[index])
    {
            NCP_MSG( NCP_MSG_ERROR, "(ERROR), taskAddr %p is allocated, but allocated list has wrong address value!\r\n", buffStartAddr);
            ncp_task_v2_breakpoint(53);
    }

NCP_RETURN_LABEL
    return;
}

void
ncp_task_v2_check_onNca(void *taskAddr, int poolID)
{
    void *buffStartAddr;
    int index;
#ifdef NCP_TASK_TAKE_ON_NCA_LOCK
    NCP_TASK_LOCK_FLAGS(flags);
    NCP_TASK_CLAIM_LOCK(pNcpNcaV2_TaskSwState->onNcaLock, flags);
#endif

    index = ncp_task_v2_debug_array_index(taskAddr, &buffStartAddr, poolID);

    /* Check if buffer is already on nca list */
    if (NULL != pNcpNcaV2_TaskSwState->onNcaList[index])
    {
        NCP_MSG( NCP_MSG_ERROR, "(ERROR), taskAddr %p already on NcaList\r\n", buffStartAddr);
        ncp_task_v2_breakpoint(1);
    }

#ifdef NCP_TASK_TAKE_ON_NCA_LOCK
    NCP_TASK_FREE_LOCK(pNcpNcaV2_TaskSwState->onNcaLock, flags);
#endif

    return;
}


void
ncp_task_v2_add_onNca(void *taskAddr, int poolID)
{
    void *buffStartAddr;
    int index;
#ifdef NCP_TASK_TAKE_ON_NCA_LOCK
    NCP_TASK_LOCK_FLAGS(flags);
    NCP_TASK_CLAIM_LOCK(pNcpNcaV2_TaskSwState->onNcaLock, flags);
#endif

    index = ncp_task_v2_debug_array_index(taskAddr, &buffStartAddr, poolID);

    ncp_task_v2_verify_not_free(buffStartAddr, poolID);

    /* Check if buffer is already on nca list */
    if (NULL != pNcpNcaV2_TaskSwState->onNcaList[index])
    {
        NCP_MSG( NCP_MSG_ERROR, "(ERROR), taskAddr %p already on NcaList\r\n", buffStartAddr);
        ncp_task_v2_breakpoint(1);
    }
    pNcpNcaV2_TaskSwState->onNcaList[index] = buffStartAddr;

#ifdef NCP_TASK_TAKE_ON_NCA_LOCK
    NCP_TASK_FREE_LOCK(pNcpNcaV2_TaskSwState->onNcaLock, flags);
#endif

    return;
}

void
ncp_task_v2_del_onNca(void *taskAddr, int poolID)
{
    void *buffStartAddr;
    int index;
#ifdef NCP_TASK_TAKE_ON_NCA_LOCK
    NCP_TASK_LOCK_FLAGS(flags);
    NCP_TASK_CLAIM_LOCK(pNcpNcaV2_TaskSwState->onNcaLock, flags);
#endif

    index = ncp_task_v2_debug_array_index(taskAddr, &buffStartAddr, poolID);

    ncp_task_v2_verify_not_free(buffStartAddr, poolID);

    /* Check if buffer was on nca list */
    if (buffStartAddr != pNcpNcaV2_TaskSwState->onNcaList[index])
    {
        NCP_MSG( NCP_MSG_ERROR, "(ERROR), taskAddr %p is *not* on NcaList\r\n", buffStartAddr);
        ncp_task_v2_breakpoint(1);
    }
    pNcpNcaV2_TaskSwState->onNcaList[index] = NULL;

#ifdef NCP_TASK_TAKE_ON_NCA_LOCK
    NCP_TASK_FREE_LOCK(pNcpNcaV2_TaskSwState->onNcaLock, flags);
#endif

    return;
}



void
ncp_task_v2_validate_buffer(void *taskAddr, int alloc, int poolID)
{
    void *buffStartAddr;
    int index;

    index = ncp_task_v2_debug_array_index(taskAddr, &buffStartAddr, poolID);

    if (alloc)
    {
        if (buffStartAddr == pNcpNcaV2_TaskSwState->allocated[index])
        {
            NCP_MSG( NCP_MSG_ERROR, "(ERROR), taskAddr %p is already allocated\r\n", buffStartAddr);
            ncp_task_v2_breakpoint(4);
        }
        pNcpNcaV2_TaskSwState->allocated[index] = buffStartAddr;
    }
    else /* free */
    {
        if (buffStartAddr != pNcpNcaV2_TaskSwState->allocated[index])
        {
            NCP_MSG( NCP_MSG_ERROR, "(ERROR), attempt to free taskAddr %p which is *not* allocated\r\n", buffStartAddr);
            ncp_task_v2_breakpoint(4);
        }
        pNcpNcaV2_TaskSwState->allocated[index] = NULL;
    }
NCP_RETURN_LABEL
    return;
}

#endif/* #ifdef NCP_TASK_DBG_BUFFERS  */

void
ncp_task_v2_unlink_queue_from_taskHdl(ncp_task_pcq_t * pQ)
{
    if (pQ)
    {
        pQ->pcqUseCnt--;
    }
    return;
}


ncp_st_t
ncp_task_v2_link_queue_to_taskHdl(ncp_pvt_task_hdl_t *myTaskHdl,
                        ncp_task_pcq_t **pQueue,
                        ncp_task_pcq_type_t type,
                        ncp_uint8_t ncaQueueId)
{
    ncp_st_t     ncpStatus   = NCP_ST_SUCCESS;
    ncp_task_pcq_t *pNcaQ;

    NCP_CALL(ncp_task_v2_map_queuenum_to_pcq(type, ncaQueueId, (ncp_task_pcq_t   **)&pNcaQ));



    /*
     *  Use the real h/w queue (exclusive access)
     */

    pNcaQ->pcqUseCnt++;
    pNcaQ->ownerTaskHdl = (void *)myTaskHdl;
    *pQueue   = pNcaQ; /* return queue to caller */

NCP_RETURN_LABEL

    return(ncpStatus);
}

ncp_st_t
ncp_task_v2_output_queueset_bind(
    ncp_pvt_task_hdl_t  *myTaskHdl,
    ncp_bool_t          shared,
    ncp_uint8_t         threadQueueSetId)
{
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;
    ncp_nca_thread_queue_set_t *pThreadQueueSet = &pNcpNcaV2_TaskSwState->threadQueueSets[threadQueueSetId];



    NCP_TASK_CHECK_FOR_SHUTDOWN();

    myTaskHdl->pThreadQueueSet   = pThreadQueueSet;
    myTaskHdl->threadQueueSetId  = threadQueueSetId;

    /*
     * Validate requested output binding
     */

    if (TRUE == shared)
    {
        if (0 != pThreadQueueSet->qsUseCnt)
        {
            if (NCP_NCA_QS_SHARED != pThreadQueueSet->qsAccessMode)
            {
                NCP_CALL(NCP_ST_TASK_SHARED_BINDING_NOT_AVAIL);
            }
        }
        else
        {
            if (NULL == pThreadQueueSet->qsLock)
            {
                pThreadQueueSet->qsLock
                    = ncp_nvm_malloc(sizeof(ncp_task_mutex_t));
                ncp_memset(pThreadQueueSet->qsLock, 0, sizeof(ncp_task_mutex_t));
                NCP_TASK_INIT_LOCK(pThreadQueueSet->qsLock, 1, 1);
            }
        }
    }
    else
    {
        if (0 != pThreadQueueSet->qsUseCnt)
        {
            NCP_CALL(NCP_ST_TASK_EXCLUSIVE_BINDING_NOT_AVAIL);
        }
        pThreadQueueSet->sendMutexDisabled = TRUE;
    }

    /*
     * create queue associations
     */
    myTaskHdl->completionQueue
        = myTaskHdl->sendQueue
        = myTaskHdl->rxBufferQueue
        = NULL;

    NCP_CALL(ncp_task_v2_link_queue_to_taskHdl(myTaskHdl,
                                    &myTaskHdl->sendQueue,
                                    NCP_TASK_PCQ_OUTPUT,
                                    threadQueueSetId));

    /*
     * Populate poolID and handle
     */
    myTaskHdl->poolID = pThreadQueueSet->poolID;
    myTaskHdl->poolHdl  =
        &pNcpNcaV2_TaskSwState->taskMemoryPool[pThreadQueueSet->poolID];

NCP_RETURN_LABEL

    if (NCP_ST_SUCCESS == ncpStatus)
    {
        if (1 == (pThreadQueueSet->qsUseCnt += 1))
        {
            if (shared)
            {
                pThreadQueueSet->qsAccessMode = NCP_NCA_QS_SHARED;
            }
            else

                pThreadQueueSet->qsAccessMode = NCP_NCA_QS_EXCLUSIVE;
            }
        }
    }
    else
    {
        /*
         * cleanup if returning error
         */
        if (NULL != myTaskHdl->sendQueue)
        {
            ncp_task_v2_unlink_queue_from_taskHdl(myTaskHdl->sendQueue);
        }
        if (NULL != myTaskHdl->completionQueue)
        {
            ncp_task_v2_unlink_queue_from_taskHdl(myTaskHdl->completionQueue);
        }
        if (NULL != myTaskHdl->rxBufferQueue)
        {
            ncp_task_v2_unlink_queue_from_taskHdl(myTaskHdl->rxBufferQueue);
        }
        if ((0 == pThreadQueueSet->qsUseCnt)
            && (NULL != pThreadQueueSet->qsLock))
        {
            NCP_TASK_DESTROY_LOCK(pThreadQueueSet->qsLock);
            ncp_nvm_free(pThreadQueueSet->qsLock);
            pThreadQueueSet->qsLock = NULL;
        }

    }
    return(ncpStatus);
}





ncp_st_t
ncp_task_v2_output_queueset_unbind(
    ncp_pvt_task_hdl_t *myTaskHdl)
{
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;
    ncp_nca_thread_queue_set_t *pThreadQueueSet;

    /*
     * Get pointer to our output queue set
     */

    pThreadQueueSet = &pNcpNcaV2_TaskSwState->threadQueueSets[myTaskHdl->threadQueueSetId];


    /*
     * Unregister and Release thread local queues
     */


    if (pNcpNcaV2_TaskSwState->inWarmRestart)
    {
        pThreadQueueSet->qsUseCnt--;
        if (0 == pThreadQueueSet->qsUseCnt)
        {
            pThreadQueueSet->qsAccessMode = NCP_NCA_QS_AVAILABLE;
        }
    }
    else if (NCP_NCA_QS_SHARED == pThreadQueueSet->qsAccessMode)
    {

        pThreadQueueSet->qsUseCnt -= 1;
        if (0 == pThreadQueueSet->qsUseCnt)
        {
            /* cleanup resources and flags */
            if (NULL != pThreadQueueSet->qsLock)
            {
                NCP_TASK_DESTROY_LOCK(pThreadQueueSet->qsLock);
                ncp_nvm_free(pThreadQueueSet->qsLock);
                pThreadQueueSet->qsLock = NULL;
            }
            pThreadQueueSet->sendMutexDisabled = FALSE;
/* Resource is available */
            pThreadQueueSet->qsAccessMode = NCP_NCA_QS_AVAILABLE;
        }
    }
    else
    {
        pThreadQueueSet->qsUseCnt = 0;
        pThreadQueueSet->qsAccessMode = NCP_NCA_QS_AVAILABLE;
    }

#if !defined(NCP_DEV_SOCKET)

    /*
     * Don't leak DMA buffers
    */

    myTaskHdl->sendQueue->pcqUseCnt--;

    if (FALSE == pNcpNcaV2_TaskSwState->inWarmRestart)
    {
        if ((0 == myTaskHdl->sendQueue->pcqUseCnt)
         && (NCP_TASK_IS_CPU_POOL(myTaskHdl->poolID)))
        {
            ncp_task_pcq_t *p_oPCQ = myTaskHdl->sendQueue;

            do
            {
                ncp_task_v2_process_oPCQ_auxData(p_oPCQ,
                                                  NULL,
                                                  0,
                                                  NULL,
                                                  myTaskHdl->poolID);

                if (p_oPCQ->u.opcq_info.auxEntriesAvail == (p_oPCQ->nEntries-2))
                {

                    /*
                     * NCA has processed all oPCQ entries,  and all CPU
                     * managed buffers have been freed
                     */

                    break;
                }
                if (NCP_TASK_SLEEP_POLL)
                {
                    ncp_sys_usleep(NCP_SLEEP_POLL_INTERVAL);
                }
            } while(1);
        }
    }
#endif

    /*
     * Free s/w queues
     */

    ncp_task_v2_unlink_queue_from_taskHdl(myTaskHdl->sendQueue);
    ncp_task_v2_unlink_queue_from_taskHdl(myTaskHdl->completionQueue);
    ncp_task_v2_unlink_queue_from_taskHdl(myTaskHdl->rxBufferQueue);
NCP_RETURN_LABEL

    NCP_TASK_CHECK_FOR_SHUTDOWN_IN_EXIT();

    return(ncpStatus);
}


/*
 * ncp_nca_v2_cpcq_entry_put
 *
 *   Update the specified PCQ descriptor entry fc
 */
void
ncp_nca_v2_cpcq_entry_put(
    ncp_task_pcq_t *pcq,
    ncp_uint32_t   idx,
    ncp_task_cPCQ_entry_t *entry)
{
    ncp_uint32_t *from32 = (ncp_uint32_t *) entry;
    ncp_task_cPCQ_entry_t *my_nca_base_cpuaddr = (ncp_task_cPCQ_entry_t *)pcq->pPCQbase;
    ncp_uint32_t *to32   = (ncp_uint32_t *) &my_nca_base_cpuaddr[idx];

    /*
     * copy just words 0, 2, and 3
     * word1, the DataBufferAddress, should already be set for the
     * associated buffer.
     */
    to32[0] = SWAP_32(from32[0]);
    to32[2] = SWAP_32(from32[2]);
    to32[3] = SWAP_32(from32[3]);

}

ncp_st_t
ncp_task_v2_allocate_domain_object(ncp_uint64_t objOffset,
                                   int          size,
                                   void         **pAddr,
                                   ncp_bool_t   doMemset)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    *pAddr
    =
        ((void *)(ncp_raw_addr_t)
        (pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_VA
        + (
        (objOffset) - pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_PA))
        );

    if (doMemset)
    {
        memset(*pAddr, 0, size);
    }

NCP_RETURN_LABEL
    return(ncpStatus);
}



/*
 * MAP in simulated NCA MMIO register space
 *
 */

ncp_st_t
ncp_task_v2_mmap_prepare_nca_mmio(ncp_hdl_t ncpHdl, ncp_dev_hdl_t devHdl, ncp_bool_t warmRestart)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

#if !defined(NCP_DEV_SOCKET)
    ncp_dev_t *dev = (ncp_dev_t *)devHdl;
    extern void    *pNcpNcaV2_domainBundle;

    if (!warmRestart)
    {
       /*
        * First inform the kernel mode component of where the comain bundle resides in physical memory,
        * and what its size is.
        */

        if (pNcpNcaV2_TaskSwState->kernelModeConfigured)
        {
           NCP_CALL(NCP_TASK_NCAV2_CFG_KMODE_DOMAIN_BUNDLE(ncpHdl));
        }

       /* Domain bundle was mapped earlier for kernel mode */
       if (pNcpNcaV2_TaskSwState->inUmode)
       {
           /*
            * mmap the domain bundle
            */

            pNcpNcaV2_domainBundle
	      = (void *)(unsigned)
                 NCP_TASK_MEM_MMAP(devHdl,
                              (void *)pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_VA,
                               pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_Size,
                               pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_PA);


            if (NULL != (void *)pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_VA)
            {
                NCP_ASSERT((
                    (pNcpNcaV2_domainBundle ==
                    (void *)pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_VA)),
                    NCP_ST_TASK_MMAP_FAILED);
            }
            else
            {
                NCP_ASSERT((NULL != pNcpNcaV2_domainBundle),
                    NCP_ST_TASK_MMAP_FAILED);
                pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_VA
                = (ncp_raw_addr_t)pNcpNcaV2_domainBundle;
            }

#ifdef NCP_TASK_PRINT_BASE_ADDRESSES_AND_MAPPINGS
            NCP_MSG(NCP_MSG_INFO, "Domain Bundle PA 0x%llx sz 0x%llx, mapped to VA %p\r\n",
                    pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_PA,
                    pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_Size,
                    (void *)pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_VA);
#endif


           NCP_ASSERT(NULL != pNcpNcaV2_domainBundle, NCP_ST_TASK_MMAP_FAILED);
        }  /* user mode */
        else
        {
            pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_PA
                = dev->myDomainBundle.sharedPhysAddr;
            pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_Size
                = dev->myDomainBundle.sharedSize;
            pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_VA
                = (ncp_raw_addr_t)(dev->myDomainBundle.kernVA);
        }
    } /* !warmRestart */


    /*
     * selective ncp_memset
     */


    if (!warmRestart)
    {
#if 0 /* UBOOT */
        ncp_vp_hdl_t vpHdl;
#endif

        pNcpNcaV2_TaskSwState->inWarmRestart            = FALSE;

        if (pNcpNcaV2_TaskSwState->inUmode)
        {

#if 0 /* UBOOT */
            /*
             * Get vpHdl
             * Note: no rxq or vp binds are necessary since we are doing raw receives
            */
            if (NCP_ST_SUCCESS !=
                ncp_vp_handle_get_by_name(ncpHdl,
                                      ncp_launch_engine_cpu,
                                      "NCA_WARM_RESTART",
                                      &vpHdl))
            {
                pNcpNcaV2_TaskSwState->warmRestartEnabled = FALSE;
            }
            else
            {
                pNcpNcaV2_TaskSwState->warmRestartEnabled = TRUE;
            }
#else
            pNcpNcaV2_TaskSwState->warmRestartEnabled = FALSE;
#endif

        }
        else
        {
            pNcpNcaV2_TaskSwState->warmRestartEnabled = FALSE;
        }


#ifdef NCP_TASK_DBG_NVM_CORRUPTION
        pNcpNcaV2_TaskSwState->nvm_dbgLock = ncp_nvm_malloc(sizeof(ncp_task_mutex_t));
        ncp_memset(pNcpNcaV2_TaskSwState->nvm_dbgLock, 0, sizeof(ncp_task_mutex_t));
        NCP_TASK_INIT_LOCK(pNcpNcaV2_TaskSwState->nvm_dbgLock, 1, 1);
#endif

        /*
         * User mode taskio resource lock
         */
        pNcpNcaV2_TaskSwState->taskIoResourceLock
            = ncp_nvm_malloc(sizeof(ncp_task_mutex_t));
        ncp_memset(pNcpNcaV2_TaskSwState->taskIoResourceLock,
               0,
               sizeof(ncp_task_mutex_t));
        NCP_TASK_INIT_LOCK(pNcpNcaV2_TaskSwState->taskIoResourceLock, 1, 1);

    }

    /*
     * Initialized whether warm restart or not
     */

#ifdef NCP_TASK_DBG_BUFFERS
    if (!warmRestart)
    {
        pNcpNcaV2_TaskSwState->onNcaLock = NCP_ALLOC_CACHEABLE(sizeof(ncp_task_mutex_t));
    }
    else
    {
        ncp_memset(pNcpNcaV2_TaskSwState->onNcaLock, 0, sizeof(ncp_task_mutex_t));
    }
    NCP_TASK_INIT_LOCK(pNcpNcaV2_TaskSwState->onNcaLock, 1, 1);
#endif

    ncp_memset(&pNcpNcaV2_TaskSwState->perNca_recvQ_IDs[0], 0, (sizeof(ncp_taskQ_IDs_t) * NCP_X7_NUM_HW_INPUT_QUEUES));

    ncp_memset(&pNcpNcaV2_TaskSwState->myTaskStats, 0, sizeof(ncp_task_stats_t));

    pNcpNcaV2_TaskSwState->activeTaskHdlList = NULL;

    pNcpNcaV2_TaskSwState->myInputPCQbitMask=0;

    /* DEBUG */
    pNcpNcaV2_TaskSwState->cookie1 = 0xAABBCCDD;
    pNcpNcaV2_TaskSwState->cookie2 = 0xFFEEDDCC;
    pNcpNcaV2_TaskSwState->startlockTestOK = FALSE;
    /* END DEBUG */


    pNcpNcaV2_TaskSwState->shutdown       = FALSE;

#ifdef DBG_KMODE_INTS
    pNcpNcaV2_TaskSwState->dbg_rx_pkts_dequed = 0;
    pNcpNcaV2_TaskSwState->dbg_rxIntsEnabled = 0;
    pNcpNcaV2_TaskSwState->dbg_rxIntsDisabled = 0;
    pNcpNcaV2_TaskSwState->dbg_txIntsEnabled = 0;
    pNcpNcaV2_TaskSwState->dbg_txIntsDisabled = 0;
    pNcpNcaV2_TaskSwState->dbg_compIntsEnabled = 0;
    pNcpNcaV2_TaskSwState->dbg_compIntsDisabled = 0;
    pNcpNcaV2_TaskSwState->dbg_txQueueFull = 0;
    pNcpNcaV2_TaskSwState->dbg_compQueueFull = 0;
    pNcpNcaV2_TaskSwState->dbg_grp0_rx_events_dispatched = 0;
    pNcpNcaV2_TaskSwState->dbg_grp0_rx_events_caught = 0;
#endif


#endif



NCP_RETURN_LABEL

    if (NCP_ST_SUCCESS != ncpStatus)
    {
        NCP_LOG(NCP_MSG_INFO, "lowlevel mem config returning st=%d\r\n",
                ncpStatus);
    }

    return(ncpStatus);
}



#if !defined(NCP_DEV_SOCKET)


ncp_st_t
ncp_task_v2_lowlevel_memcfg(ncp_hdl_t ncpHdl, ncp_dev_hdl_t dev, ncp_nca_t *nca, ncp_bool_t warmRestart)
{
     ncp_st_t ncpStatus = NCP_ST_SUCCESS;


    /*
     * MAP in domain bundle and perform selected initialization on
     * Task I/O SW State
     */

     NCP_CALL(ncp_task_v2_mmap_prepare_nca_mmio(ncpHdl, dev, warmRestart));

NCP_RETURN_LABEL
    return(ncpStatus);
}

#endif

ncp_uint64_t
ncp_task_v2_va_2_pa(void * VA, int poolID)
{
    ncp_uint64_t x64 = 0LL;;



     if (NULL != VA)
     {
        /* PA is ZERO based for pool_0, which is not same load point  */

        x64 = (ncp_uint64_t) ((ncp_uint8_t *)VA - (ncp_uint8_t *)pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_VA);
        x64 += pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_PA;
     }
     return(x64);
}

void *
ncp_task_v2_pa_2_va(ncp_uint32_t high32, ncp_uint32_t low32, int poolID)
{
    ncp_raw_addr_t  va=0;
    ncp_uint64_t x64;
    ncp_uint32_t x32=0;

    x64 = high32;
    x64 = x64 << 32 | low32;


    /* PA is ZERO based for pool_0 */

    x32 = (ncp_uint32_t) x64
        - pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_PA;
    va = (ncp_raw_addr_t)
        (pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_VA);
    va += x32;

    return((void *)va);
}

#ifdef NCP_DEV_SOCKET

ncp_st_t
ncp_task_v2_ase_put_completion_plus_dealloc(ncp_pvt_task_hdl_t *myTaskHd,  ncp_task_ncaV2_recv_buf_t *task)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

NCP_RETURN_LABEL
    return(ncpStatus);
}

ncp_st_t
ncp_task_v2_ase_put_dealloc(ncp_pvt_task_hdl_t *myTaskHd,  ncp_task_ncaV2_recv_buf_t *task)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

NCP_RETURN_LABEL
    return(ncpStatus);
}


ncp_st_t
ncp_task_v2_ase_put_deallocate_immediate(
            ncp_pvt_task_hdl_t *myTaskHdl,  ncp_ncaV2_task_oPCQ_entry_dealloc_immediate_t *task,
            ncp_bool_t wait)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

NCP_RETURN_LABEL
    return(ncpStatus);
}

ncp_st_t
ncp_task_v2_ase_allocate_domain_object(int          size,
                                       void         **pAddr,
                                       ncp_bool_t   doMemset)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    if (NULL == (*pAddr = ncp_nvm_malloc(size)))
    {
        NCP_CALL(NCP_ST_NO_MEMORY);
    }
    if (doMemset)
    {
        memset(pAddr, 0, size);
    }
NCP_RETURN_LABEL
    return(ncpStatus);
}

ncp_st_t
ncp_task_v2_ase_alloc_cacheable(void **ppMem, int size)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;


    NCP_ASSERT((NULL != (*ppMem = ncp_nvm_malloc(size))), NCP_ST_TASK_NO_CACHE_ALLLIGNED_MEM);
    ncp_memset(*ppMem, 0, size);

NCP_RETURN_LABEL
    return(ncpStatus);
}

ncp_st_t
ncp_task_v2_ase_free_cacheable(void *pMem)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
#if !defined(NCP_KERNEL) || defined(NCP_VXWORKS)
    ncp_nvm_free(pMem);
#else
    NCP_CALL(NCP_ST_NOT_IMPLEMENTED);
#endif
NCP_RETURN_LABEL
    return(ncpStatus);
}

ncp_st_t
ncp_task_v2_ase_check_task_input_queue( ncp_pvt_task_hdl_t *myTaskHdl,
                                    ncp_pvt_task_recv_queue_t   *myRecvQueue,
                                    ncp_task_recv_buf_t    **task)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    ncp_uint8_t pduDataStart;
    ncp_bool_t taskErr;
    ncp_input_task_header_t *pInputHdr;
    ncp_task_pcq_t *taskQueue = myRecvQueue->taskQueue;
    ncp_uint8_t templateId;


    ncpStatus = ncp_dev_socket_input_task_get(myTaskHdl->dev,
                                        taskQueue->ncaQueueId,
                                        &templateId,
                                        (ncp_uint8_t *)&pduDataStart,
                                        (ncp_input_task_header_t **)task,
                                        &taskErr,
                                        0);

    /*
     * We must copy to a nvm buffer suitable for freeing with the NVM variant routines,
     * as these buffers are required for shared queues.
     */
     if (NCP_ST_SUCCESS == ncpStatus)
     {
        ncp_task_recv_buf_t * dstTask;

        dstTask = ncp_nvm_malloc((*task)->dataSz + pduDataStart);
        memcpy(dstTask,*task,(*task)->dataSz + pduDataStart);
        ncp_free(*task);
        *task = dstTask;
     }

    if (NCP_ST_SUCCESS == ncpStatus)
    {
        pInputHdr = (ncp_input_task_header_t *)*task;
        pInputHdr->taskErr = taskErr;
        (*task)->dataOffset     = pduDataStart;
        (*task)->templateId     = templateId;
    }
    else if (NCP_ST_TASK_RECV_QUEUE_EMPTY != ncpStatus)
    {
        NCP_CALL(ncpStatus);
    }

NCP_RETURN_LABEL
    return(ncpStatus);
}

ncp_st_t
ncp_task_v2_ase_put_directed_tCompletion(ncp_pvt_task_hdl_t *myTaskHdl,  ncp_ncaV2_task_completion_data_t    *pManualTaskCompletionTask)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    /* FIXME for socket mode - use old V1 interface? */
    return(ncpStatus);
}

ncp_st_t
ncp_task_v2_ase_put_tqs_tCompletion(ncp_dev_hdl_t dev,
                                    ncp_nca_thread_queue_set_t *pThreadQueueSet,
                                    ncp_task_recv_buf_t *task)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    /* FIXME */
    return(ncpStatus);
}



ncp_st_t
ncp_task_v2_ase_put_tOutput(ncp_pvt_task_hdl_t *myTaskHdl,
				ncp_vp_hdl_t vpHdl,
				ncp_task_send_meta_t *taskMetaData,
				void                 *taskPduData,
				ncp_task_ncaV2_oPCQ_aux_data_t  *taskAuxData,
				ncp_bool_t wait)
{
    ncp_st_t ncpStatus          =   NCP_ST_SUCCESS;

    ncp_t *ncp                  = (ncp_t *)(myTaskHdl->ncpHdl);
    ncp_dev_hdl_t dev           = ncp_dev_hdls[ncp->id];
    ncp_task_pcq_t  *p_oPCQ     = myTaskHdl->sendQueue;
    ncp_task_oPCQ_entry_t  *pTaskMetaData;

    /*
     * Encode pipeline parameters
     */
    ncp_vpm_task_param_encode(vpHdl, &taskMetaData->taskParms[0], &taskMetaData->taskParms[0]);

   /*
    * Cast to 34xx ouput element so we can fill in driver private fields
    */
   pTaskMetaData=( ncp_task_oPCQ_entry_t*)taskMetaData;
   pTaskMetaData->setTaskEr             = 0;
   pTaskMetaData->interruptOnComplete   = 0;
   pTaskMetaData->dataBufferAddr_37_32  = 0;    /* Does not make sense in socket env */
   pTaskMetaData->dataBufferAddr_31_0   = 0;    /* Does not make sense in socket env */



   /*
    * Send enqueue request over socket I/F to ASE server to be emulated by NCA in simulator
    */

    do
    {
        if (NCP_ST_SUCCESS ==
            (ncpStatus = ncp_dev_socket_output_task_put(dev,
                                                      p_oPCQ->ncaQueueId,
                                                      (ncp_task_send_meta_t *)taskMetaData,
                                                      taskPduData,
                                                      0)))
        {

            if (taskAuxData->clientFreeFn)
            {
               /*
                * Call user's send completion routine
                */
               taskAuxData->clientFreeFn(taskAuxData->clientFreeFnArg,
                                         taskPduData);
               taskAuxData->clientFreeFn    = NULL;
               taskAuxData->clientFreeFnArg = 0;
            }
            else
            {
               /*
                * Free the buffer
                */
               ncp_task_ncav2_buffer_free((ncp_task_hdl_t *)myTaskHdl, taskPduData);
            }

            break;
        }
        else if (NCP_ST_TASK_SEND_QUEUE_FULL != ncpStatus)
        {
            NCP_CALL(ncpStatus);
        }
        else if (FALSE == wait)
        {
            break;
        }
    } while(1);

NCP_RETURN_LABEL

    return(ncpStatus);
}

ncp_st_t
ncp_task_v2_ase_put_segments_tOutput(ncp_pvt_task_hdl_t *myTaskHdl,
					ncp_vp_hdl_t vpHdl,
                                        ncp_task_send_meta_t *taskMetaData,
                                        ncp_task_ncaV2_oPCQ_aux_data_t *taskAuxData,
                                        ncp_task_segment_entry_t *pSegTable,
                                        int numSegs,
                                        ncp_bool_t wait)
{
    ncp_st_t ncpStatus          =   NCP_ST_SUCCESS;
    int i;
    void *pduData;
    ncp_uint8_t *cpyPtr;

    /*
     * Allocate a new buffer and combine the segments into a contiguous
     * task,  freeing the original buffers as we go.
     */
    NCP_ASSERT( NULL != (pduData = ncp_nvm_malloc(taskMetaData->dataSize)),
        NCP_ST_NO_MEMORY);

    cpyPtr = (ncp_uint8_t *)pduData;

    for (i=0; i<numSegs; i++)
    {
        memcpy(cpyPtr, pSegTable[i].addr, pSegTable[i].size);
        cpyPtr += pSegTable[i].size;
        ncp_task_ncav2_buffer_free((ncp_task_hdl_t *)myTaskHdl, pSegTable[i].addr);
    }

    /*
     * Now send the task using the single segment API
     */
    NCP_CALL(ncp_task_v2_ase_put_tOutput(myTaskHdl,
				vpHdl,
				taskMetaData,
				pduData,
                                taskAuxData,
				wait));

NCP_RETURN_LABEL
    return(ncpStatus);
}


#endif

/*
 * =============================
 * old ncp_task_helper_linux.c
 * =============================
 */


/*
 * Static buffer pool parameters - we will eventually get these from the config
 */
#define NCP_POOL_MASK_ALL_QUEUES       0xFF            /* BITS 1..31 all set,   thereby making this pool the only pool for receive buffers since it maps to all queues */



/*
 * Partition up the memory into preconfigured sizes and quantities
 */
#ifndef NCP_DEV_SOCKET

ncp_st_t
ncp_task_v2_partition_mem_pool(ncp_dev_hdl_t dev,
                               int poolID)
{
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;
    ncp_task_ncaV2_pool_t *pPoolEntry
        = &pNcpNcaV2_TaskSwState->taskMemoryPool[poolID];
    int i;
    int buffSz[4] = {NCP_X7_BUFFER_SZ0,
                     NCP_X7_BUFFER_SZ1,
                     NCP_X7_BUFFER_SZ2,
                     NCP_X7_BUFFER_SZ3};

    for (i=0; i<NCP_TASK_NUM_BUFF_SIZES; i++)
    {
        pPoolEntry->u.cpu.buffListArray[i].free = NULL;
        pPoolEntry->u.cpu.buffListArray[i].size = buffSz[i];

        /*
         * Mask is applied to taskAddr to get real buff start.
         * assumes all buffer sizes arepower of 2
         */
        pPoolEntry->u.cpu.buffListArray[i].mask
            = ~(buffSz[i]-1);

        /* just for consistency with v1 code */
        pPoolEntry->u.cpu.buffListArray[i].numTotal
            = pPoolEntry->numBlocks[i];

    }

    if (pNcpNcaV2_TaskSwState->inUmode == pPoolEntry->uMode)
    {
        NCP_CALL(ncp_task_v2_format_task_mem_pool(poolID));
    }

NCP_RETURN_LABEL
    return(ncpStatus);
}

ncp_st_t
ncp_task_v2_format_task_mem_pool(int poolID)
{
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;
    int i;
    ncp_buffDescriptor_t          *pBuffDesc;
    ncp_raw_addr_t                currBaseVA;
    ncp_task_ncaV2_pool_t         *pPoolEntry = &pNcpNcaV2_TaskSwState->taskMemoryPool[poolID];

    currBaseVA = (ncp_raw_addr_t)pPoolEntry->pool_VA;

#ifdef NCP_TASK_PRINT_BASE_ADDRESSES_AND_MAPPINGS
    NCP_MSG(NCP_MSG_INFO, "Pool Buffers Base VA = %p, End VA = %p\r\n",
            (void *)pPoolEntry->pool_VA,
            (void *)pPoolEntry->pool_EndVA);
#endif

    /*
     * Allocate the task buffers,   size by size
     */

    for (i=(NCP_TASK_NUM_BUFF_SIZES-1); i >= 0; i--)
    {
        int j;

        pPoolEntry->u.cpu.buffListArray[i].VAstart = (ncp_uint8_t *)currBaseVA ;

#ifdef NCP_TASK_PRINT_BASE_ADDRESSES_AND_MAPPINGS
        NCP_MSG(NCP_MSG_INFO, "VA Start[%d] =%p\r\n", i, (void *)currBaseVA);
#endif

        for (j=0; j < pPoolEntry->u.cpu.buffListArray[i].numTotal; j++)
        {

            pBuffDesc = (void *)currBaseVA;

#if defined(NCP_TASK_DBG_BUFFERS)
            pBuffDesc->cookie = NCP_TASK_FREE_BUFF_COOKIE;
#endif
            if (0 == j)
            {
                pPoolEntry->u.cpu.buffListArray[i].last = pBuffDesc;
            }
            currBaseVA += pPoolEntry->u.cpu.buffListArray[i].size;

            /* put it on the free list */
            pBuffDesc->next = (struct ncp_buffDescriptor_s*)(pPoolEntry->u.cpu.buffListArray[i].free);
            pPoolEntry->u.cpu.buffListArray[i].free = pBuffDesc;
            pPoolEntry->u.cpu.buffListArray[i].numFree++;
        }

        pPoolEntry->u.cpu.buffListArray[i].freeLowWaterMark
            = pPoolEntry->u.cpu.buffListArray[i].numFree;

        pPoolEntry->u.cpu.buffListArray[i].VAend = (ncp_uint8_t *)currBaseVA ;
#ifdef NCP_TASK_PRINT_BASE_ADDRESSES_AND_MAPPINGS
        NCP_MSG(NCP_MSG_DEBUG, "pPool Entry (%d) @%p, total=%d, numFree=%d, sz=%d, vaStart=%p, vaEnd=%p\r\n",
        i,
        pPoolEntry,
        pPoolEntry->u.cpu.buffListArray[i].numTotal,
        pPoolEntry->u.cpu.buffListArray[i].numFree,
        pPoolEntry->u.cpu.buffListArray[i].size,
        pPoolEntry->u.cpu.buffListArray[i].VAstart,
        pPoolEntry->u.cpu.buffListArray[i].VAend);
#endif

    }

    if (currBaseVA > pPoolEntry->pool_EndVA)
    {
        NCP_MSG(NCP_MSG_ERROR, "Pool %d overflowed by 0x%x bytes,start=%p, end=%p, overFlowAddress=%p\r\n",
            poolID,
            currBaseVA - pPoolEntry->pool_EndVA,
            (void *)pPoolEntry->pool_VA,
            (void *)pPoolEntry->pool_EndVA,
            (void *)currBaseVA);

        NCP_CALL(NCP_ST_INTERNAL_ERROR);
    }

NCP_RETURN_LABEL
    if (NCP_ST_SUCCESS != ncpStatus)
    {
        NCP_MSG(NCP_MSG_ERROR, "kmode: ncp_task_v2_format_task_mem_pool failed with error %d\n",ncpStatus);
    }

    return(ncpStatus);
}
#endif /* !NCP_DEV_SOCKET */


/*
 * Attach to the globally shared memory (GSM),   both the cacheable and noncacheable portions
 */

ncp_st_t
ncp_task_v2_mmap_attach(ncp_dev_hdl_t devHdl,
                        void **pGSM,
                        ncp_task_ncaV2_t **pTaskGSM)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

#if  !defined(NCP_DEV_SOCKET)

    /*
     * map domain bundle
     */
#ifndef NCP_KERNEL
    *pGSM
      = (void *)(unsigned)
         NCP_TASK_MEM_MMAP(devHdl,
                      (void *)pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_VA,
                       pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_Size,
                       pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_PA);


    NCP_ASSERT(
        (*pGSM == (void *)
        pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_VA), NCP_ST_TASK_MMAP_FAILED);

#else    /* NCP_KERNEL */
    *pGSM = (void *)pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_VA;
#endif  /* NCP_KERNEL */

#ifdef NCP_TASK_PRINT_BASE_ADDRESSES_AND_MAPPINGS
        NCP_MSG(NCP_MSG_INFO, "mapped domainBundle at VA %p\r\n",
                (void *)*pGSM);
#endif

#endif /* SOCKET */

NCP_RETURN_LABEL
    return(ncpStatus);
}


#ifndef NCP_DEV_SOCKET

void
ncp_task_v2_unmap_all_memory_pools(ncp_dev_hdl_t devHdl)
{
    int poolID;

    for (poolID = NCP_DEV_FIRST_CPU_MANAGED_POOL;
         poolID < NCP_X7_NUM_TASK_MEMORY_POOLS;
         poolID++)
    {
        ncp_task_ncaV2_pool_t *pPoolEntry
            = &pNcpNcaV2_TaskSwState->taskMemoryPool[poolID];

        if (pNcpNcaV2_TaskSwState->inUmode == pPoolEntry->uMode)
        {
            /*
             * Check if user mode and pool is referenced by at least 1 tqs
             */

            if (pPoolEntry->uMode && (0 != pPoolEntry->tqsRefCount))
            {
                /* unmap pages for the pool */

                NCP_TASK_MEM_UNMAP(dev,
                                   (void *)pPoolEntry->pool_VA,
                                   pPoolEntry->pool_Size);
                memPoolMapped[poolID] = FALSE;
            }
        } /* pool used in this execution mode */
    }   /* for */
}

ncp_st_t
ncp_task_v2_init_cpu_pools(
        ncp_dev_hdl_t   dev,
        ncp_nca_t       *nca)

{
    ncp_st_t ncpStatus= NCP_ST_SUCCESS;

#if  !defined(NCP_DEV_SOCKET)

    ncp_int32_t     poolID;


    /*
     * Initialize the CPU pools associated with this domain
     */

    for (poolID = NCP_DEV_FIRST_CPU_MANAGED_POOL;
         poolID < NCP_X7_NUM_TASK_MEMORY_POOLS;
         poolID++)
    {
        ncp_task_ncaV2_pool_t *pPoolEntry;
        pPoolEntry = &pNcpNcaV2_TaskSwState->taskMemoryPool[poolID];

        /*
         * Check if user mode and pool is referenced by at least 1 tqs
         */

        if (
            (pNcpNcaV2_TaskSwState->taskMemoryPool[poolID].uMode == pNcpNcaV2_TaskSwState->inUmode)
            &&
            (0 != pNcpNcaV2_TaskSwState->taskMemoryPool[poolID].tqsRefCount))
        {
            if (TRUE == memPoolMapped[poolID])
            {
                /* already mapped */
                NCP_LOG(NCP_MSG_INFO,
                        "skipping poolID=%d, already mapped\r\n",
                        poolID);
                continue;
            }
            /* Create user mode pages for the pool */

#ifdef NCP_KMODE_DEBUG
            NCP_LOG(NCP_MSG_INFO,"Mapping memory for pool %d, inUmode=%d, pool_uMode=%d\r\n",
                poolID,
                pNcpNcaV2_TaskSwState->inUmode,
                pNcpNcaV2_TaskSwState->taskMemoryPool[poolID].uMode);
#endif

            pPoolEntry->pool_VA
            = (ncp_raw_addr_t)
                 NCP_TASK_MEM_MMAP(dev,
                              (void *)pPoolEntry->pool_VA,
                              pPoolEntry->pool_Size,
                              pPoolEntry->pool_PA);

#ifdef NCP_TASK_PRINT_BASE_ADDRESSES_AND_MAPPINGS

            NCP_MSG(NCP_MSG_INFO, "CPU Pool %d PA 0x%llx sz 0x%llx, mapped to VA %p\r\n",
                    poolID,
                    pPoolEntry->pool_PA,
                    pPoolEntry->pool_Size,
                    (void *)pPoolEntry->pool_VA);
#endif

            NCP_ASSERT(NULL != (void *)pNcpNcaV2_TaskSwState->taskMemoryPool[poolID].pool_VA, NCP_ST_TASK_MMAP_FAILED);

            /* so we do not map more than once per process */
            memPoolMapped[poolID] = TRUE;

            pPoolEntry->poolKey                 = NCP_POOL_KEY;
            pPoolEntry->poolID                  = poolID;
            pPoolEntry->isCpuManagedPool        = TRUE;
            pPoolEntry->poolLock                = ncp_nvm_malloc(sizeof(ncp_task_mutex_t));

            pPoolEntry->pool_EndVA
                = (ncp_raw_addr_t)pPoolEntry->pool_VA
                + pPoolEntry->pool_Size;

            NCP_TASK_INIT_LOCK(pPoolEntry->poolLock, 1, 1);

            NCP_CALL(ncp_task_v2_partition_mem_pool(dev, poolID));
        }
        else
        {
            pPoolEntry->poolID = 0xff;
            continue;
        }
    }   /* for */


NCP_RETURN_LABEL

#endif /* !defined(NCP_DEV_SOCKET) && (!defined(NCP_KERNEL) || defined(NCP_VXWORKS)) */

    return ncpStatus;
}
#endif	 /* !NCP_DEV_SOCKET */


#ifndef NCP_DEV_SOCKET
void *
ncp_task_v2_alloc_cacheable(int size)
{
    void *pMem = NULL;

    if (0 != size)
    {
        if (NULL == (pMem = (void *)ncp_nvm_malloc(size)))
        {
            NCP_LOG(NCP_MSG_ERROR, "Task S/W Control: NVM exhausted -  failed for size=%d\r\n", size);
        }
        else
        {
            ncp_memset(pMem, 0, size);
        }
    }
NCP_RETURN_LABEL
    return(pMem);
}
#endif


ncp_st_t
ncp_task_detach_mme_allocator(ncp_pvt_task_hdl_t *myTaskHdl)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    if (myTaskHdl->mmeAllocator)
    {
        myTaskHdl->mmeAllocator->useCnt--;
        myTaskHdl->mmeAllocator = NULL;
    }

NCP_RETURN_LABEL
    return(ncpStatus);
}

ncp_st_t
ncp_task_attach_mme_allocator(ncp_pvt_task_hdl_t *myTaskHdl)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    int i;

    ncp_nca_thread_queue_set_t *pThreadQueueSet
        = myTaskHdl->pThreadQueueSet;
    ncp_task_mme_allocator_t *pAllocator = &pThreadQueueSet->mme[0];

    if (NCP_TASK_IS_SHARED_POOL(myTaskHdl->poolID))
    {
        /* Just grab 1st available allocator */
        for (i = 0; i < pThreadQueueSet->numAllocators; i++, pAllocator++)
        {

            if ((pAllocator->valid)
                && (0 == pAllocator->useCnt))
            {
                pAllocator->useCnt++;
                myTaskHdl->mmeAllocator = pAllocator;

#ifdef NCP_TASK_DEBUG_MME
                { /* DEBUG */
                    int _xx;

                    NCP_LOG(NCP_MSG_INFO, "using allocator %d @ %p\r\n",
                        pAllocator->id,
                        myTaskHdl->mmeAllocator);
                    NCP_LOG(NCP_MSG_INFO,"baseVA=%p\r\n",
                        (void *)(pAllocator->baseVA));

                    for (_xx=0; _xx<4; _xx++)
                    {
                        NCP_LOG(NCP_MSG_INFO,
    "AllofIF[%d]:queueValid=%d, readP_swVA=%p,readP_swVAmax_val=%p,entriesBaseVA=%p, readP_hw_indx0_val=%lld\r\n ",
                        _xx,
                        pAllocator->allocIF[_xx].queueValid,
                        pAllocator->allocIF[_xx].readP_swVA,
                        pAllocator->allocIF[_xx].readP_swVA_max_val,
                        pAllocator->allocIF[_xx].entries_baseVA,
                        pAllocator->allocIF[_xx].readP_hw_indx0_val);
                    }

                } /* DEBUG */
#endif
                break;
            }
        }
        if (i == pThreadQueueSet->numAllocators)
        {
            NCP_CALL(NCP_ST_TASK_NO_MME_ALLOCATOR);
        }
    }
    else
    {
        myTaskHdl->mmeAllocator = NULL;
    }
NCP_RETURN_LABEL
    return(ncpStatus);
}


/* Kernel mode task i/o is currently limited to linux hw and iss */
#if defined(NCP_LINUX) && !defined(NCP_KERNEL) && !defined(NCP_DEV_FBRS) && !defined(NCP_DEV_SOCKET)
ncp_st_t
ncp_task_config_kernel_mode_taskio(ncp_hdl_t ncpHdl,
                                   ncp_task_ncaV2_t *pSwState)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    if (pNcpNcaV2_TaskSwState->inUmode)
    {
        NCP_CALL(ncp_task_do_kmode_config(ncpHdl, pNcpNcaV2_TaskSwState));
    }

NCP_RETURN_LABEL
    return(ncpStatus);
}

ncp_st_t
ncp_task_finish_kernel_mode_taskio(ncp_hdl_t ncpHdl,
                                   ncp_task_ncaV2_t *pSwState)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    if (pNcpNcaV2_TaskSwState->inUmode)
    {
        NCP_CALL(ncp_task_finish_kmode_config(ncpHdl, pNcpNcaV2_TaskSwState));
    }

NCP_RETURN_LABEL
    return(ncpStatus);
}
#endif


ncp_st_t
ncp_task_v2_get_size_bits(
        ncp_pvt_task_hdl_t *myTaskHdl,
		void *taskAddr, ncp_uint8_t *pSizeBits)
{
    ncp_task_ncaV2_pool_t *pPoolEntry = myTaskHdl->poolHdl;

    int i;

    ncp_st_t ncpStatus=NCP_ST_SUCCESS;

    if (FALSE == pPoolEntry->isCpuManagedPool)
    {
        *pSizeBits = 0;
        return(NCP_ST_SUCCESS);
    }

    if ((NULL == pPoolEntry) || (NCP_POOL_KEY != pPoolEntry->poolKey))
    {
        NCP_LOG(NCP_MSG_ERROR, "ncp_task_v2_CpuPool_free called with bad pool entry ptr =0x%p\r\n",pPoolEntry);
        NCP_CALL(NCP_ST_INVALID_HANDLE);
    }

    if (   ((ncp_raw_addr_t)taskAddr >  (ncp_raw_addr_t)(pPoolEntry->pool_EndVA))
        || ((ncp_raw_addr_t)taskAddr <  (ncp_raw_addr_t)(pPoolEntry->pool_VA)))
    {
        NCP_CALL(NCP_ST_INVALID_VALUE);
    }

    for (i=0; i < NCP_TASK_NUM_BUFF_SIZES; i++)
    {
        if ((taskAddr >= pPoolEntry->u.cpu.buffListArray[i].VAstart)
            && (taskAddr < pPoolEntry->u.cpu.buffListArray[i].VAend))
        {
            *pSizeBits = i;
            break;
        }

    }
NCP_RETURN_LABEL
    return(ncpStatus);
}

#ifndef NCP_KERNEL
/*
 * This function is a debug-only hook that allows gdb to read MMAPed memory,   which is otherwise
 * not accessable by GDB,  as it runs as a separate process.
 *
 * when debugging with gdb,   use "call ncp_task_gdb_read(<addr>, <len>)"
 *
 * Example: (gdb)call ncp_task_gdb_read(0x3001d130, 100)
 *
 */
void ncp_r8(ncp_uint8_t *addr, int len)
{
    int i=0;

    printf("ADDR=%p:\r\n", addr);

    while(len)
    {
        printf("%2X ", *addr++);
        len--;
        i++;
        if (32 == i)
        {
            i = 0;
            printf("\r\n");
        }
    }
    printf("\r\n");
    return;
}

/*
 * This function is a debug-only hook that allows gdb to read MMAPed memory,   which is otherwise
 * not accessable by GDB,  as it runs as a separate process.
 *
 * when debugging with gdb,   use "call ncp_task_gdb_read(<addr>, <len>)"
 *
 * Example: (gdb)call ncp_task_gdb_read(0x3001d130, 100)
 *
 */
void ncp_r32(ncp_uint32_t *addr, int len)
{
    int i=0;

    printf("ADDR=%p:\r\n", addr);

    while(len)
    {
        printf("%8X ", *addr++);
        len--;
        i++;
        if (16 == i)
        {
            i = 0;
            printf("\r\n");
        }
    }
    printf("\r\n");
    return;
}

/*
 * This function is a debug-only hook that allows gdb to read MMAPed memory,   which is otherwise
 * not accessable by GDB,  as it runs as a separate process.
 *
 * when debugging with gdb,   use "call ncp_task_gdb_read(<addr>, <len>)"
 *
 * Example: (gdb)call ncp_task_gdb_read(0x3001d130, 100)
 *
 */
void ncp_r16(ncp_uint16_t *addr, int len)
{
    int i=0;

    printf("ADDR=%p:\r\n", addr);

    while(len)
    {
        printf("%8X ", *addr++);
        len--;
        i++;
        if (32 == i)
        {
            i = 0;
            printf("\r\n");
        }
    }
    printf("\r\n");
    return;
}



/*
 * The following functions provide a debug-only hook that allows gdb to write MMAPed memory,   which is otherwise
 * not accessable by GDB,  as it runs as a separate process.
 *
 * when debugging with gdb,   use "call ncp_task_gdb_mmio_writeXX(<addr>, <data>)"
 *
 * Example: (gdb)call ncp_task_gdb_read(0x3001d130, 100)
 *
 */
void ncp_w8(ncp_uint8_t *addr, ncp_uint8_t data)
{
    *addr = data;
    printf("Addr 0x%p now contains data=0x%hhx\r\n",addr, *addr);
    return;
}

void ncp_w16(ncp_uint16_t *addr, ncp_uint16_t data)
{
    *addr = data;
    printf("Addr 0x%p now contains data=0x%hx\r\n",addr, *addr);
    return;
}

void ncp_w32(ncp_uint32_t *addr, ncp_uint32_t data)
{
    *addr = data;
    printf("Addr 0x%p now contains data=0x%x\r\n",addr, *addr);
    return;
}



void ncp_r32_swap(ncp_uint32_t *addr, int len)
{
    int i=0;

    printf("ADDR=%p:\r\n", addr);

    while(len)
    {
        printf("%8X ", SWAP_32(*addr));
        addr++;
        len--;
        i++;
        if (16 == i)
        {
            i = 0;
            printf("\r\n");
        }
    }
    printf("\r\n");
    return;
}

void ncp_r64_swap(ncp_uint64_t *addr, int len)
{
    int i=0;

    printf("ADDR=%p:\r\n", addr);

    while(len)
    {
        printf("%8llX ", (long long unsigned int)SWAP_64(*addr));
        addr++;
        len--;
        i++;
        if (8 == i)
        {
            i = 0;
            printf("\r\n");
        }
    }
    printf("\r\n");
    return;
}

void ncp_r16_swap(ncp_uint16_t *addr, int len)
{
    int i=0;

    printf("ADDR=%p:\r\n", addr);

    while(len)
    {
        printf("%8X ", SWAP_16(*addr));
        addr++;
        len--;
        i++;
        if (32 == i)
        {
            i = 0;
            printf("\r\n");
        }
    }
    printf("\r\n");
    return;
}
#endif

