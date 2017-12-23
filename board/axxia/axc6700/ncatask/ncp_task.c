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
#define  NCP_TASK_NCA_GLOBALS
#include "uboot/ncp_task_pvt.h"
#include "uboot/ncp_task_ext.h"
#include "uboot/ncp_task_hw.h"

#if !defined(NCP_DEV_SOCKET) && !defined(NCP_DEV_FBRS) && !defined(NCP_DEV_FBDEV)
#include "uboot/ncp_task_inline_funcs.h"
#endif

/* 
 * Export are reuired for kernel entry points
 */
NCP_EXPORT_SYMBOL(ncp_task_attach);
NCP_EXPORT_SYMBOL(ncp_task_tqs_bind);
NCP_EXPORT_SYMBOL(ncp_task_tqs_unbind);
NCP_EXPORT_SYMBOL(ncp_task_rx_queue_flush);
NCP_EXPORT_SYMBOL(ncp_task_tx_queue_flush);
NCP_EXPORT_SYMBOL(ncp_task_send);
NCP_EXPORT_SYMBOL(ncp_task_recv);
NCP_EXPORT_SYMBOL(ncp_task_complete);
NCP_EXPORT_SYMBOL(ncp_task_buffer_alloc);
NCP_EXPORT_SYMBOL(ncp_task_buffer_free);
NCP_EXPORT_SYMBOL(ncp_task_free);


NCP_API ncp_st_t
ncp_task_attach(
    ncp_t *ncp)
{
    ncp_st_t ncpStatus   = NCP_ST_SUCCESS;
    ncp_ncav3_hdl_t *nca = NULL;
    void *pDomainBundle;  

    NCP_NCA_CRITICAL_SECTION_FLAG_DECL(globalCritSecFlag)

    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                          ncp_xlf_task_attach_entry,
                          NCP_MSG_ENTRY,
                          "ncp=%p\n", ncp);
    NCP_CHECK((NULL != ncp), NCP_ST_INVALID_PARAMETER);
    
    NCP_NCA_INC_GLOBAL_CRITICAL_SECTION(globalCritSecFlag);

    nca  = (ncp_ncav3_hdl_t *)ncp->ncaHdl;

    if (NULL == nca)
    {
        /* 
         * Return success if the NCA isn't configured,  so that ncp_config_attach can proceed.
         * This allows the EIOA (and other non-NCA) CLIs to execute without having the NCA configured. 
         */
        NCP_RETURN(NCP_ST_SUCCESS);
    }

    if (NULL == (pNcpTaskSwState = nca->taskSwState))
    {    
            NCP_CALL(NCP_ST_TASK_NO_GSM);
    }
    
    if (0 == ncpTaskDomainBundleMapCnt &&
        0 != pNcpTaskSwState->domainMemMap.domainBundle_VA)
    {     
        NCP_CALL(NCP_TASK_DOMAIN_BUNDLE_ATTACH(ncp, &pDomainBundle)); 

        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_attach_domainBundleAttachOk,
                              NCP_MSG_DEBUG,
                              "DOMAIN_BUNDLE_ATTACH OK, pDomainBundle = %p\r\n",
                              pDomainBundle);
    }
    else
    {
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_attach_domainBundleAttachSkipped,
                              NCP_MSG_DEBUG,
                              "DOMAIN_BUNDLE_ATTACH SKIPPED,%s curr useCnt=%d\r\n",
                              (ncpTaskDomainBundleMapCnt != 0) ? " already mapped," : "",
                              ncpTaskDomainBundleMapCnt);
    }
    ncpTaskDomainBundleMapCnt++;
    
    myNcpHdl = (ncp_hdl_t *)ncp;
    myDevHdl = ncp_dev_hdls[ncp->id];

    /* RWXXX NCP_CALL(ncp_ncav3_map_unscheduled_queues()); */

NCP_RETURN_LABEL

    if (NCP_ST_SUCCESS == ncpStatus)
    {
        NCP_TASK_INC_GLOBAL_STAT(api_task_attach_ok);        
    }        
    else
    {
        NCP_TASK_INC_GLOBAL_STAT(api_task_attach_err);        
    }
    
    if (NULL != pNcpTaskSwState)
    {
        NCP_NCA_DEC_GLOBAL_CRITICAL_SECTION(globalCritSecFlag);
    }
    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                          ncp_xlf_task_attach_exit,
                          NCP_MSG_EXIT,
                          "ncpStatus=%d\n", ncpStatus);
    return(ncpStatus);
}

#if 0 /* not in header not called */
NCP_API ncp_st_t
ncp_task_detach(
    ncp_t *ncp)
{
    ncp_st_t ncpStatus   = NCP_ST_SUCCESS;
    ncp_ncav3_hdl_t *nca = NULL;  

    NCP_NCA_CRITICAL_SECTION_FLAG_DECL(globalCritSecFlag)

    NCP_CHECK((NULL != pNcpTaskSwState), NCP_ST_TASK_NO_GSM);
    NCP_NCA_INC_GLOBAL_CRITICAL_SECTION(globalCritSecFlag);    
    NCP_CHECK((NULL != ncp), NCP_ST_INVALID_PARAMETER);  
    
    nca  = ncp->ncaHdl;
    if (NULL == (pNcpTaskSwState = nca->taskSwState))
    {    
            NCP_CALL(NCP_ST_TASK_NO_GSM);
    }

    ncpTaskDomainBundleMapCnt--;
    if (0 == ncpTaskDomainBundleMapCnt)
    {     
        NCP_CALL(NCP_TASK_DOMAIN_BUNDLE_DETACH(ncp, (void *)pNcpTaskSwState->domainMemMap.domainBundle_VA)); 

        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_detach_domainBundleDeattachOk,
                              NCP_MSG_DEBUG,
                              "DOMAIN_BUNDLE_DEATTACH OK, pDomainBundle = %p\r\n",
                              (void *)pNcpTaskSwState->domainMemMap.domainBundle_VA);
    }
    else
    {
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                              ncp_xlf_task_detach_domainBundleDeattachSkipped,
                              NCP_MSG_DEBUG,
                              "DOMAIN_BUNDLE_DEATTACH SKIPPED, still in use, new useCnt=%d\r\n",
                              ncpTaskDomainBundleMapCnt);
    }

NCP_RETURN_LABEL

    if (NCP_ST_SUCCESS == ncpStatus)
    {
        NCP_TASK_INC_GLOBAL_STAT(api_task_detach_ok);        
    }        
    else
    {
        NCP_TASK_INC_GLOBAL_STAT(api_task_detach_err);        
    } 
    
    if (pNcpTaskSwState)
    {
        NCP_NCA_DEC_GLOBAL_CRITICAL_SECTION(globalCritSecFlag);     
    }
    return(ncpStatus);
}
#endif /* 0 */


NCP_API ncp_st_t
ncp_task_tqs_bind(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t tqsId,
    ncp_task_tqs_usage_t *pParams,
    ncp_task_resource_name_t *processName,
    ncp_task_resource_name_t *threadName,
    ncp_task_tqs_hdl_t *pTqsHdl)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl = NULL;
    NCP_MUTEX_LOCKED_FLAG_DECL(unlockRequired);
    ncp_bool_t pidInitDone=FALSE;
    ncp_bool_t tqsAttachDone=FALSE;
    ncp_task_process_info_t *pProcess = NULL;
    ncp_pid_t  myPid = ncp_get_pid();
    NCP_NCA_CRITICAL_SECTION_FLAG_DECL(critSecFlag)
    NCP_NCA_CRITICAL_SECTION_FLAG_DECL(globalCritSecFlag)
    NCP_TASK_LOCK_FLAGS(flags);

    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                   ncp_xlf_task_tqs_bind_entry,
                   NCP_MSG_ENTRY,
                   "ncpHdl=%p tqsId=%u pParams=%p processName=%s threadName=%s pTqsHdl=%p"
                   "\n",
                   ncpHdl, tqsId, pParams,
                   ((processName) ? (processName->name) : "(null)"),
                   ((threadName) ? (threadName->name) : "(null)"),
                   pTqsHdl);
    NCP_CHECK((NULL != pNcpTaskSwState), NCP_ST_TASK_NO_GSM);
    NCP_CALL(NCP_VALIDATE_NCP_HDL(ncpHdl));
    NCP_CHECK(tqsId < NCP_NCAV3_NUM_CPU_TQSETS, NCP_ST_INVALID_PARAMETER);
    NCP_CHECK((NULL != pParams), NCP_ST_INVALID_PARAMETER);
    NCP_CHECK((NULL != pTqsHdl), NCP_ST_INVALID_PARAMETER);

    /* Validate supplied name */
    NCP_TASK_VALIDATE_RESOURCE_NAME(processName, NCP_ST_TASK_BAD_RESOURCE_NAME);
    NCP_TASK_VALIDATE_RESOURCE_NAME(threadName, NCP_ST_TASK_BAD_RESOURCE_NAME);

    NCP_NCA_INC_GLOBAL_CRITICAL_SECTION(globalCritSecFlag);

    NCP_CALL(NCP_TASK_CLAIM_LOCK(pNcpTaskSwState->taskIoResourceLock, flags, &unlockRequired));

    if (pNcpTaskSwState->domainId !=
        pNcpTaskSwState->tqsSwState[tqsId].domainId)
    {
        NCP_CALL(NCP_ST_TASK_QUESET_NOT_IN_LOCAL_DOMAIN);
    }

    /* If configured is true, the other tqsSwState variables are valid for
     * the caller's mode. */
    if (FALSE == pNcpTaskSwState->tqsSwState[tqsId].configured)
    {
        NCP_CALL(NCP_ST_TASK_TQS_NOT_CONFIGURED);
    }

    if (pNcpTaskSwState->uMode !=
        pNcpTaskSwState->tqsSwState[tqsId].pAppProfile->baseProfile.uMode)
    {
        NCP_CALL(NCP_ST_TASK_TQS_MODE_CONFLICT);
    }

    if (FALSE == pNcpTaskSwState->tqsSwState[tqsId].tqsEnabled)
    {
        NCP_CALL(NCP_ST_TASK_TQS_DISABLED);
    }

    if (NCP_MUTEX_PROCESS_PRIVATE == pNcpTaskSwState->tqsSwState[tqsId].mtxAttr.attr &&
        pNcpTaskSwState->tqsSwState[tqsId].mtxAttr.pid != myPid)
    {
        NCP_RETURN(NCP_ST_TASK_PID_MISMATCH);
    }
    /*
     * Be optimistic that the tqs handle does not need to be recovered,
     * i.e. that app is not restarting and TBR is ON.
     */
/*TODO*/
    pvtTqsHdl = malloc(sizeof(ncp_task_pvt_tqsHdl_data_t));
	memset(pvtTqsHdl,0,sizeof(ncp_task_pvt_tqsHdl_data_t));

    NCP_NCA_INC_CRITICAL_SECTION(pvtTqsHdl, critSecFlag);

    NCP_CALL(ncp_task_add_thread(pvtTqsHdl, processName, threadName, tqsId, &pProcess));
    pidInitDone = TRUE;

    /* Bind to tqs, validating shared flags and usage */

    NCP_CALL(ncp_task_attach_tqs(ncpHdl, pvtTqsHdl, tqsId, pParams));
    tqsAttachDone = TRUE;

    NCP_CALL(ncp_task_init_wait_profile(pvtTqsHdl));

    /*
     * TASK SEND 
     */
    pvtTqsHdl->taskSendDefaultCmdBits.u.opcqDword[1]           = 0; /* zero init flags portion of entry */
    pvtTqsHdl->taskSendDefaultCmdBits.u.opcqEntry.cmd          = NCP_NCAV3_CMD_SENDTH;
    pvtTqsHdl->taskSendDefaultCmdBits.u.opcqEntry.interruptEn  = 1;
    
    /*
     * TASK BUFFER FREE
     */
    pvtTqsHdl->taskBufferFreeDefaultCmdBits.u.opcqDword[1]  = 0; /* zero init flags portion of entry */
    pvtTqsHdl->taskBufferFreeDefaultCmdBits.u.opcqEntry.cmd =  NCP_NCAV3_CMD_ADPAE;
    pvtTqsHdl->taskBufferFreeDefaultCmdBits.u.opcqEntry.interruptEn = 1;
    pvtTqsHdl->taskBufferFreeDefaultCmdBits.u.opcqEntry.flowControlDisabled = 0;
    pvtTqsHdl->taskBufferFreeDefaultCmdBits.u.opcqEntry.headerPoolMref = 0; /* note: mref is a don't care for CPU pools */
    pvtTqsHdl->taskBufferFreeDefaultCmdBits.u.opcqEntry.headerPool = 0;
    pvtTqsHdl->taskBufferFreeDefaultCmdBits.u.opcqEntry.returnHeader  = NCP_NCAV3_ADPAE_RCCH_NOOP;
    pvtTqsHdl->taskBufferFreeDefaultCmdBits.u.opcqEntry.returnData    = NCP_NCAV3_ADPAE_RCCD_DEC_REFCNT;
    pvtTqsHdl->taskBufferFreeDefaultCmdBits.u.opcqEntry.quotaTransfer = NCP_NCAV3_ADPAE_MQGC_DEC_SOURCE;        

    /*
     * TASK FREE
     */
     
    pvtTqsHdl->taskFreeDefaultCmdBits.u.opcqDword[1]  = 0; /* zero init flags portion of entry */     
    pvtTqsHdl->taskFreeDefaultCmdBits.u.opcqEntry.cmd = NCP_NCAV3_CMD_ADPAH;
    pvtTqsHdl->taskFreeDefaultCmdBits.u.opcqEntry.interruptEn = 1;
    /* pvtTqsHdl->taskFreeDefaultCmdBits.u.opcqEntry.flowControlDisabled = 0; */    /* already zero */
    /* entry.quotaIncludeHeader    = NCP_NCAV3_ADPAH_MQGI_INCL_HDR; */              /* already zero */
    pvtTqsHdl->taskFreeDefaultCmdBits.u.opcqEntry.returnData     = NCP_NCAV3_ADPAH_RCCD_DEC_REFCNT;
    pvtTqsHdl->taskFreeDefaultCmdBits.u.opcqEntry.quotaTransfer  = NCP_NCAV3_ADPAH_MQGC_DEC_SOURCE;    
     
    /* 
     * TASK COMPLETE
     */
     
    pvtTqsHdl->taskCompleteDefaultCmdBits.u.opcqDword[1]  = 0; /* zero init flags portion of entry */     
    pvtTqsHdl->taskCompleteDefaultCmdBits.u.opcqEntry.cmd = NCP_NCAV3_CMD_NOOP;     
    pvtTqsHdl->taskCompleteDefaultCmdBits.u.opcqEntry.taskCompletion = 1;
    pvtTqsHdl->taskCompleteDefaultCmdBits.u.opcqEntry.interruptEn = 1;
    /* pvtTqsHdl->taskCompleteDefaultCmdBits.u.opcqEntry.flowControlDisabled = 0; */ /* already zero */
    
     
    /* Supply NCA buffers if this is the first user of a CPU pool. */
    /* RWXXX
    if (pNcpTaskSwState->tqsSwState[tqsId].tqsUseCnt == 1)
    {
        NCP_CALL(ncp_ncav3_supply_nca_buffers((ncp_t *) ncpHdl, pvtTqsHdl));
    }
    */

NCP_RETURN_LABEL
    if (NCP_ST_SUCCESS == ncpStatus)
    {
        /* Add to list of active tqs handles */
        pvtTqsHdl->nextTqsHdl = pNcpTaskSwState->activeTqsHdls;
        pNcpTaskSwState->activeTqsHdls = pvtTqsHdl;

        NCP_TASK_INC_STAT(pvtTqsHdl->pTqs,  api_task_tqs_hdl_bind_ok);
        *pTqsHdl = (ncp_task_tqs_hdl_t *)pvtTqsHdl;
    }
    else
    {
        if (pvtTqsHdl)
        {
            NCP_TASK_INC_ERROR_STAT_VIA_PTQS(&pNcpTaskSwState->tqsSwState[tqsId],
                                             api_task_tqs_hdl_bind_err);
        }
        else
        {
            NCP_TASK_INC_GLOBAL_STAT(api_task_tqs_hdl_bind_err);
        }
        if (pidInitDone)
        {
            /*TODO*/
            NCP_CLEANUP_CALL(ncp_task_delete_thread(pvtTqsHdl, threadName));
        }
        if (tqsAttachDone)
        {
            ncp_task_detach_tqs(pvtTqsHdl);
        }
        if (pvtTqsHdl)
        {
            free(pvtTqsHdl);
            pvtTqsHdl = NULL;
        }
        *pTqsHdl = NULL; /* return null tqs handle */

        /*
         * If process restart and TBR enabled,   then attempt to recover resources.
         *
         * Application responsibilities include:
         * 1) if TQS_DISABLED,   then free any buffers, and unbind (if currently bound)
         * 2) repeatedly call ncp_task_tqs_bind(),  performing a small delay in between attempts,
         *    until RTE reenables TQS,   at which time bind will succeed if same parameters were used
         *    as in thread's initial bind.
         *
         * RTE will reenable all TQSets only after last client performs its unbind.
         * RTE will recover all buffers.
         * RTE will issue completions, if necessary.
         * RTE will perform NCA RX buffer refills, if necessary
         */

    }

    NCP_CLEANUP_MUTEX_CALL(NCP_TASK_FREE_LOCK(pNcpTaskSwState->taskIoResourceLock, flags, &unlockRequired));
    
    NCP_NCA_DEC_CRITICAL_SECTION(pvtTqsHdl, critSecFlag);
    NCP_NCA_DEC_GLOBAL_CRITICAL_SECTION(globalCritSecFlag);
    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                   ncp_xlf_task_tqs_bind_exit,
                   NCP_MSG_EXIT,
                   "ncpStatus=%d pTqsHdl=%p(%p)"
                   "\n",
                   ncpStatus, pTqsHdl, ((pTqsHdl) ? (*pTqsHdl) : 0));
    return(ncpStatus);
}


NCP_API ncp_st_t
ncp_task_tqs_unbind(
    ncp_task_tqs_hdl_t tqsHdl)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl = (ncp_task_pvt_tqsHdl_data_t * )tqsHdl;
    NCP_MUTEX_LOCKED_FLAG_DECL(unlockRequired);
    NCP_NCA_CRITICAL_SECTION_FLAG_DECL(critSecFlag)
    NCP_TASK_LOCK_FLAGS(flags);

    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                   ncp_xlf_task_tqs_unbind_entry,
                   NCP_MSG_ENTRY,
                   "tqsHdl=%p"
                   "\n",
                   tqsHdl
        );

    NCP_CHECK((NULL != pNcpTaskSwState), NCP_ST_TASK_NO_GSM);
    NCP_VALIDATE_TQS_HDL(pvtTqsHdl);
    NCP_NCA_INC_CRITICAL_SECTION(pvtTqsHdl, critSecFlag);

    NCP_CALL(NCP_TASK_CLAIM_LOCK(pNcpTaskSwState->taskIoResourceLock, flags, &unlockRequired));

    /*
     * Flush the oPCQ(s) to issue any outstanding send done callbacks.
     * App must free buffers in order to avoid a memmory leak.
     */

    if (pvtTqsHdl->useFlags.useTxQueue[0])
    {
        NCP_CALL(ncp_task_tx_queue_flush(tqsHdl, 0));
    }

    if (pvtTqsHdl->useFlags.useTxQueue[1])
    {
        NCP_CALL(ncp_task_tx_queue_flush(tqsHdl, 1));
    }

    /* Unbind. Clean up TQS software state if tqsUseCnt is 0. */
    NCP_CALL(ncp_task_internal_tqs_unbind(pvtTqsHdl,
                                          FALSE, /* NOT in recovery */
                                          TRUE));

NCP_RETURN_LABEL

    if (NCP_ST_SUCCESS == ncpStatus)
    {

        NCP_TASK_INC_STAT(pvtTqsHdl->pTqs,  api_task_tqs_hdl_unbind_ok);
        /*
         * Nuke cookie in callers task handle.
         * Otherwise we can't necessarily detect a bad (already freed) handle
         */
        pvtTqsHdl->cookie = 0xDEADD00D;
        free(pvtTqsHdl);
        pvtTqsHdl = NULL;
    }
    else
    {
        NCP_TASK_INC_ERROR_STAT_VIA_PTQSHDL(pvtTqsHdl,   api_task_tqs_hdl_unbind_err);
    }

    NCP_CLEANUP_MUTEX_CALL(NCP_TASK_FREE_LOCK(pNcpTaskSwState->taskIoResourceLock, flags, &unlockRequired));

    NCP_NCA_DEC_CRITICAL_SECTION(pvtTqsHdl, critSecFlag);
    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca, ncp_xlf_task_tqs_unbind_exit,
                   NCP_MSG_EXIT,
                   "ncpStatus=%d\n",
                   ncpStatus
        );
    return(ncpStatus);
}


#define NCP_TASK_NUM_RXFLUSH_TASKS 32
#define NCP_TASK_FLUSH_MAX_CONSECUTIVE_RX_EMPTY 128
NCP_API ncp_st_t
ncp_task_rx_queue_flush(
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint32_t txQueueId)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl = (ncp_task_pvt_tqsHdl_data_t *)tqsHdl;
    ncp_task_tqs_swState_t *pTqs = NULL;    
    ncp_task_pcq_t *p_oPCQ = NULL;    
    NCP_MUTEX_LOCKED_FLAG_DECL(txUnlockRequired);    
    ncp_task_pcq_t *p_iPCQ = NULL;
    NCP_MUTEX_LOCKED_FLAG_DECL(rxUnlockRequired); 
    ncp_task_header_t *tasks[NCP_TASK_NUM_RXFLUSH_TASKS];
    ncp_uint32_t numReceived;
    ncp_uint32_t numFreed; 
    ncp_bool_t   issueCompletions;  
    ncp_ipcq_entry_t *pInputQueueEntry;
    int loops=0;
    int numEmpty=0;
    ncp_bool_t needPollStateReset = TRUE;
    NCP_NCA_CRITICAL_SECTION_FLAG_DECL(critSecFlag)
    /* ncp_uint32_t numFlushed = 0; */  /* DEBUG */
    NCP_TASK_LOCK_FLAGS(txqLockFlags); 
    NCP_TASK_LOCK_FLAGS(rxqLockFlags);    
    
    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                   ncp_task_rx_queue_flush_entry,
                   NCP_MSG_ENTRY,
                   "tqsHdl=%p txQueueId=%u"
                   "\n",
                   tqsHdl, txQueueId);
    NCP_TASKIO_CHECK((NULL != pNcpTaskSwState), NCP_ST_TASK_NO_GSM);
    NCP_VALIDATE_TQS_HDL(pvtTqsHdl);
    NCP_NCA_INC_CRITICAL_SECTION(pvtTqsHdl, critSecFlag);    
    NCP_TASKIO_CHECK((txQueueId == NCP_TASK_TXQ_0 
               || txQueueId == NCP_TASK_TXQ_1),
               NCP_ST_INVALID_PARAMETER);
    NCP_TASKIO_CHECK((TRUE == pvtTqsHdl->useFlags.useTxQueue[txQueueId]), 
              NCP_ST_TASK_TQS_SHARING_VIOLATION);
    NCP_TASKIO_CHECK((TRUE == pvtTqsHdl->useFlags.useRxQueue), 
              NCP_ST_TASK_TQS_SHARING_VIOLATION); 
              
    NCP_TASKIO_CHECK((TRUE != pvtTqsHdl->inOpcqCallbackDoneFn[txQueueId]), 
                      NCP_ST_TASK_SENDQUEUE_CALLBACK_RECURSION_DETECTED);               
              
/*
 *  Remove tasks from the specified receive queue until it and 
 *  the NCA queues that feed it are depleted.
 *
 *  This function may issue manual completions or task frees 
 *  on the specified transmit queue.
 */

    pTqs = pvtTqsHdl->pTqs;
    NCP_TASK_PREFETCH_PGIT_FOR_WRITE(pTqs->pCpuPgit);
    NCP_TASK_PREFETCH_PGIT(pTqs->pNcaPgit);    
    
    p_iPCQ = &pTqs->rxQ;
    if (p_iPCQ->shared == TRUE)
    {
        NCP_CALL(NCP_TASK_CLAIM_LOCK_HDL(&p_iPCQ->qLock, rxqLockFlags, &rxUnlockRequired));
    }
        
    if (NCP_TASK_TXQ_0 == txQueueId)
    {
        p_oPCQ = &pTqs->txQ0;
    }
    else
    {
        p_oPCQ = &pTqs->txQ1;
    }  

    if (p_oPCQ->shared)
    {
        NCP_CALL(NCP_TASK_CLAIM_LOCK_HDL(&p_oPCQ->qLock, txqLockFlags, &txUnlockRequired));
    }


    /*
     * TODO - take parent NCA queues offline if no other TQSets
     * are actively using them.
     */
     
    issueCompletions = (FALSE == p_iPCQ->u.ipcq_info.autoCompletionMode);

    pInputQueueEntry = p_iPCQ->u.ipcq_info.pIPCQentry;
    NCP_TASK_PREFETCH_PCQ_ENTRY((pInputQueueEntry));
    NCP_TASK_PREFETCH_TASK_HEADER(pInputQueueEntry);

    do 
    {
        loops++;

        if (p_iPCQ->u.ipcq_info.autoConsumptionMode)
        {
            ncpStatus = ncp_task_recv_normal(
                    pvtTqsHdl,
                    p_iPCQ,
                    p_iPCQ->u.ipcq_info.pIPCQentry,
                    NCP_TASK_NUM_RXFLUSH_TASKS,
                    &numReceived,
                    &tasks[0],
                    FALSE);
        }
        else
        {
            ncpStatus = ncp_task_recv_deferred(
                    pvtTqsHdl,
                    p_iPCQ,
                    p_iPCQ->u.ipcq_info.pIPCQentry,
                    NCP_TASK_NUM_RXFLUSH_TASKS,
                    &numReceived,
                    &tasks[0],
                    FALSE);
        }

        if (NCP_ST_SUCCESS != ncpStatus)
        {                             
            if (NCP_ST_TASK_RECV_QUEUE_EMPTY == ncpStatus)
            {  
                numEmpty++;
                if (numEmpty < NCP_TASK_FLUSH_MAX_CONSECUTIVE_RX_EMPTY)
                { 
                    ncp_st_t tmpStatus;
                    
                    if (needPollStateReset)
                    {       
                        needPollStateReset = FALSE;             
                        NCP_TASK_RESET_POLL_STATE(
                            &pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_RECV_QUEUE_FLUSH]);
                    }        
                               
                    if (NCP_ST_SUCCESS != (tmpStatus = NCP_TASK_DO_WAIT(
                            pvtTqsHdl,
                            (&pvtTqsHdl->waitProfile[NCP_TASK_API_CLASS_RECV_QUEUE_FLUSH]),
                            myDevHdl,
                            pvtTqsHdl->tqsId)))
                    {
                        ncpStatus = tmpStatus;
                        NCP_JUMP_RETURN();
                    }
                    continue; 
                } 
                else
                {
                    /* Assume the queue is really drained and exit early */
                    break;
                }        
            }
            else 
            {
                NCP_CALL(ncpStatus);
            }        
        }
        else
        {
            numEmpty = 0; /* reset */
        }           

        /* Free the tasks just received, issueing completions if 
         * required.   Note if this TQS uses a cpu pool,   then this
         * free will resupply the NCA with same buffers that were 
         * received above.
         */
        NCP_CALL(ncp_task_bulk_task_free(
                pvtTqsHdl,
                p_oPCQ,
                numReceived,
                &numFreed,
                &tasks[0],
                TRUE,
                issueCompletions,
                TRUE));
                
        /* numFlushed += numReceived; */ /* DEBUG */

        NCP_ASSERT((numReceived ==  numFreed), NCP_ST_INTERNAL_ERROR);

        if (issueCompletions)
        {
            pvtTqsHdl->completionsIssued[txQueueId] += numFreed;
            NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                  ncp_xlf_task_rx_queue_flush_txCompletionInfo,
                                  NCP_MSG_DEBUG,
                                  "[%s()] TxQ_%d completions issued incremented by %d, total = 0x%"PRIx64"\n",
                                  __func__, txQueueId, numFreed,
                                  pvtTqsHdl->completionsIssued[txQueueId]);
        }

    } while(1);   
    
NCP_RETURN_LABEL

    /* DEBUG */
#if 0
    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                          ncp_xlf_task_rx_queue_flush_results, NCP_MSG_INFO,
                          "Flushed %d tasks, loops=%d, numEmpty=%d\r\n",
                          numFlushed, loops, numEmpty);
#endif

    if ((NCP_ST_SUCCESS == ncpStatus)
     || (NCP_ST_TASK_RECV_QUEUE_EMPTY == ncpStatus))
    {
        NCP_TASK_INC_STAT(pvtTqsHdl->pTqs, api_task_rx_queue_flush_ok); 
    }        
    else
    {
        NCP_TASK_INC_ERROR_STAT_VIA_PTQSHDL(pvtTqsHdl,  api_task_rx_queue_flush_err);      
    }  
    
    NCP_NCA_DEC_CRITICAL_SECTION(pvtTqsHdl, critSecFlag);   
    
    NCP_CLEANUP_MUTEX_CALL(NCP_TASK_FREE_LOCK_HDL(&p_oPCQ->qLock, txqLockFlags, &txUnlockRequired));
    
    NCP_CLEANUP_MUTEX_CALL(NCP_TASK_FREE_LOCK_HDL(&p_iPCQ->qLock, rxqLockFlags, &rxUnlockRequired));
    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                   ncp_task_rx_queue_flush_exit,
                   NCP_MSG_EXIT,
                   "ncpStatus=%d"
                   "\n",
                   ncpStatus);
    return(ncpStatus);
}

NCP_API ncp_st_t
ncp_task_tx_queue_flush(
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint32_t txQueueId) 
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
#ifndef NCP_DEV_SOCKET
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl = (ncp_task_pvt_tqsHdl_data_t *)tqsHdl;
    ncp_task_tqs_swState_t *pTqs = NULL;
    ncp_task_pcq_t *p_oPCQ = NULL;
    NCP_MUTEX_LOCKED_FLAG_DECL(unlockRequired);
    NCP_NCA_CRITICAL_SECTION_FLAG_DECL(critSecFlag)
    NCP_TASK_LOCK_FLAGS(txqLockFlags);      
            
    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                   ncp_task_tx_queue_flush_entry,
                   NCP_MSG_ENTRY,
                   "tqsHdl=%p txQueueId=%u"
                   "\n",
                   tqsHdl, txQueueId);
    NCP_TASKIO_CHECK((NULL != pNcpTaskSwState), NCP_ST_TASK_NO_GSM);
    NCP_VALIDATE_TQS_HDL(pvtTqsHdl);
    NCP_NCA_INC_CRITICAL_SECTION(pvtTqsHdl, critSecFlag);    
    NCP_TASKIO_CHECK((txQueueId == NCP_TASK_TXQ_0 
               || txQueueId == NCP_TASK_TXQ_1),
               NCP_ST_INVALID_PARAMETER);    
    NCP_TASKIO_CHECK((TRUE == pvtTqsHdl->useFlags.useTxQueue[txQueueId]), 
              NCP_ST_TASK_TQS_SHARING_VIOLATION);
              
    NCP_TASKIO_CHECK((TRUE != pvtTqsHdl->inOpcqCallbackDoneFn[txQueueId]), 
                      NCP_ST_TASK_SENDQUEUE_CALLBACK_RECURSION_DETECTED);              

    pTqs = pvtTqsHdl->pTqs;
    NCP_TASK_PREFETCH_PGIT_FOR_WRITE(pTqs->pCpuPgit);
    NCP_TASK_PREFETCH_PGIT(pTqs->pNcaPgit);    
    
    if (NCP_TASK_TXQ_0 == txQueueId)
    {
        p_oPCQ = &pTqs->txQ0;
    }
    else
    {
        p_oPCQ = &pTqs->txQ1;
    }  

    if (p_oPCQ->shared)
    {
        NCP_CALL(NCP_TASK_CLAIM_LOCK_HDL(&p_oPCQ->qLock, txqLockFlags, &unlockRequired));
    }         

    do {
        /* We wait for empty to be reflected in the PGIT */
        if (*(p_oPCQ->pProducerIdx) == *(p_oPCQ->pConsumerIdx))
        {    
            break;  /* Empty, get out */
        }  
        else
        {
#ifndef NCP_KERNEL
            ncp_sys_usleep(NCP_SLEEP_POLL_INTERVAL);
#endif
        }

    } while(1);

    /*
     * Force send done dispatch to thread local pcq
     */
    NCP_TASK_UPDATE_NUM_TX_ENTRIES_AVAIL(pvtTqsHdl, p_oPCQ);     
    


NCP_RETURN_LABEL

    if (NCP_ST_SUCCESS == ncpStatus)
    {
        NCP_TASK_INC_STAT(pvtTqsHdl->pTqs, api_task_tx_queue_flush_ok); 
    }        
    else
    {
        NCP_TASK_INC_ERROR_STAT_VIA_PTQSHDL(pvtTqsHdl,  api_task_tx_queue_flush_err);      
    }  

    NCP_NCA_DEC_CRITICAL_SECTION(pvtTqsHdl, critSecFlag);    
    
    /* must unlock before allowing callbacks */    
    NCP_CLEANUP_MUTEX_CALL(NCP_TASK_FREE_LOCK_HDL(&p_oPCQ->qLock, txqLockFlags, &unlockRequired));
    
    NCP_TASK_PROCESS_SEND_DONE(pvtTqsHdl, txQueueId);
        
#endif  /* NCP_DEV_SOCKET */
    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                   ncp_task_tx_queue_flush_exit,
                   NCP_MSG_EXIT,
                   "ncpStatus=%d"
                   "\n",
                   ncpStatus);
    return(ncpStatus);
}

NCP_API ncp_st_t
ncp_task_send( 
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint8_t  txQueueId,
    ncp_uint32_t numTasks, 
    ncp_uint32_t *pNumSent, 
    ncp_task_send_meta_t *pMetadata, 
    ncp_bool_t wait) 
{
#if defined(NCP_DEV_SOCKET)  
    return NCP_ST_NOT_IMPLEMENTED;
#else
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl = (ncp_task_pvt_tqsHdl_data_t *)tqsHdl;
    NCP_MUTEX_LOCKED_FLAG_DECL(unlockRequired);
    
#ifdef NCP_TASKIO_CHECK_DISABLED    
    /* Optimized init block. Saves ~6 cycles (~3%) for the performance path */
    ncp_task_tqs_swState_t *pTqs;
    ncp_task_pcq_t *p_oPCQ;
    ncp_int32_t completionsIssued;
    NCP_NCA_CRITICAL_SECTION_FLAG_DECL(critSecFlag)
    NCP_TASK_LOCK_FLAGS(txqLockFlags); 
    /* end optimized init block */        

    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                          ncp_task_send_check_disabled_entry,
                          NCP_MSG_ENTRY,
                          "tqsHdl=%p txQueueId=%u numTasks=%u pNumSent=%p pMetadata=%p wait=%u"
                          "\n",
                          tqsHdl, txQueueId, numTasks, pNumSent, pMetadata, wait);
#else    
    /* Unoptimized init block.   Provides sane values for premature returns due to check failing */
    ncp_task_tqs_swState_t *pTqs = NULL;
    ncp_task_pcq_t *p_oPCQ = NULL;
    ncp_int32_t completionsIssued = 0;
    NCP_NCA_CRITICAL_SECTION_FLAG_DECL(critSecFlag)
    NCP_TASK_LOCK_FLAGS(txqLockFlags);  
    /* end unoptimized init block */  

    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                          ncp_task_send_entry,
                          NCP_MSG_ENTRY,
                          "tqsHdl=%p txQueueId=%u numTasks=%u pNumSent=%p pMetadata=%p wait=%u"
                          "\n",
                          tqsHdl, txQueueId, numTasks, pNumSent, pMetadata, wait);
    /* 
     * API Parameter Validation 
     */
    NCP_TASKIO_CHECK((NULL != pNumSent), NCP_ST_INVALID_PARAMETER);
    *pNumSent = 0;
    
    NCP_TASKIO_CHECK((NULL != pNcpTaskSwState), NCP_ST_TASK_NO_GSM);
    NCP_VALIDATE_TQS_HDL(pvtTqsHdl);
    NCP_NCA_INC_CRITICAL_SECTION(pvtTqsHdl, critSecFlag);    
    NCP_TASKIO_CHECK((txQueueId == NCP_TASK_TXQ_0 
               || txQueueId == NCP_TASK_TXQ_1),
               NCP_ST_INVALID_PARAMETER);    
    NCP_TASKIO_CHECK((NULL != pMetadata), NCP_ST_INVALID_PARAMETER);  
    NCP_TASKIO_CHECK((TRUE == pvtTqsHdl->useFlags.useTxQueue[txQueueId]), 
              NCP_ST_TASK_TQS_SHARING_VIOLATION);
              
    NCP_TASKIO_CHECK((TRUE != pvtTqsHdl->inOpcqCallbackDoneFn[txQueueId]), 
                      NCP_ST_TASK_SENDQUEUE_CALLBACK_RECURSION_DETECTED);              
    if (NCP_TASK_RESTRICT_BULK_APIS)
    {    
        NCP_TASKIO_CHECK((numTasks <= NCP_TASK_API_MAX_BULK_ITEM_COUNT),
                   NCP_ST_TASK_BULK_REQUEST_TOO_BIG);              
    }                        
#endif

             

    pTqs = pvtTqsHdl->pTqs;
        
    NCP_TASK_PREFETCH_PGIT_FOR_WRITE(pTqs->pCpuPgit);
    NCP_TASK_PREFETCH_PGIT(pTqs->pNcaPgit);    

    if (FALSE == pTqs->tqsEnabled)
    {
        /*TODO*/
        *pNumSent = 0;                  /* Need sane value in exit path if checks OFF */
        completionsIssued = 0;          /* Need sane value in exit path if checks OFF */
        NCP_CALL(NCP_ST_TASK_TQS_DISABLED);
    }
        
    if (NCP_TASK_TXQ_0 == txQueueId)
    {
        p_oPCQ = &pTqs->txQ0;
    }
    else
    {
        p_oPCQ = &pTqs->txQ1;
    }  

    if (FALSE == p_oPCQ->shared)
    {
        /* Intentional NULL body */            
    }
    else        
    {
        NCP_CALL(NCP_TASK_CLAIM_LOCK_HDL(&p_oPCQ->qLock, txqLockFlags, &unlockRequired));
    } 
     
    NCP_TASK_PREFETCH_PCQ_ENTRY_FOR_WRITE(p_oPCQ->u.opcq_info.pOPCQentry);
         
    /*
     * Force any send done callbacks to be executed now.
     * This ensures that we do not overflow the send done PCQ.
     */
        
    NCP_TASK_PROCESS_SEND_DONE(pvtTqsHdl, txQueueId);
    
    /*
     * Do the send - optimized for single send case 
     */

    if (1 == numTasks)
    {
        ncpStatus = ncp_task_single_task_send(
                pvtTqsHdl,
                p_oPCQ,
                numTasks, 
                pNumSent,
                pMetadata,
                &completionsIssued,                        
                wait);
    }
    else if (0 != numTasks)
    {                                 
        ncpStatus = ncp_task_bulk_task_send(
                pvtTqsHdl,
                p_oPCQ,
                numTasks, 
                pNumSent,
                pMetadata,
                &completionsIssued,                        
                wait);
    }
    else
    {
        *pNumSent = 0;
        completionsIssued = 0;
        
    }        
            
NCP_RETURN_LABEL

    pvtTqsHdl->completionsIssued[txQueueId] += completionsIssued;
    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                          ncp_xlf_task_send_txCompletionInfo, NCP_MSG_DEBUG,
                          "in send: TxQ_%d completions issued incremented by %d, total = 0x%"PRIx64"\r\n",
                          (unsigned) txQueueId,
                          (unsigned) completionsIssued,
                          pvtTqsHdl->completionsIssued[txQueueId]);

    if (NCP_ST_SUCCESS == ncpStatus)
    {
        NCP_TASK_INC_STAT(pvtTqsHdl->pTqs, api_task_send_ok); 
        NCP_TASK_ADD_TXSTAT(pvtTqsHdl->pTqs, TxTask, txQueueId, *pNumSent);        
    }        
    else
    {
        NCP_TASK_INC_ERROR_STAT_VIA_PTQSHDL(pvtTqsHdl,  api_task_send_err);      
    }  
     
    NCP_NCA_DEC_CRITICAL_SECTION(pvtTqsHdl, critSecFlag);            

    NCP_CLEANUP_MUTEX_CALL(NCP_TASK_FREE_LOCK_HDL(&p_oPCQ->qLock, txqLockFlags, &unlockRequired));

    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                   ncp_task_send_exit,
                   NCP_MSG_EXIT,
                   "ncpStatus=%d pNumSent=%p(%u)"
                   "\n",
                   ncpStatus, pNumSent, (pNumSent) ? (*pNumSent) : 0);
    return(ncpStatus);
    
#endif /* SOCKET */    
}

NCP_API ncp_st_t
ncp_task_recv(
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint32_t numTasks, 
    ncp_uint32_t *pNumReceived, 
    ncp_task_header_t **pTasks,
    ncp_bool_t wait) 
{
#ifdef NCP_DEV_SOCKET
    return(ncpStatus);
#else
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_pcq_t *p_iPCQ = NULL;
    ncp_ipcq_entry_t *pInputQueueEntry = NULL;    
    NCP_MUTEX_LOCKED_FLAG_DECL(unlockRequired);    
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl =
        (ncp_task_pvt_tqsHdl_data_t *) tqsHdl;
    ncp_task_tqs_swState_t *pTqs;
    NCP_NCA_CRITICAL_SECTION_FLAG_DECL(critSecFlag)
    NCP_TASK_LOCK_FLAGS(flags);     
    
    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                   ncp_task_recv_entry,
                   NCP_MSG_ENTRY,
                   "tqsHdl=%p numTasks=%u pNumReceived=%p pTasks=%p wait=%u"
                   "\n",
                   tqsHdl, numTasks, pNumReceived, pTasks, wait);
    NCP_TASKIO_CHECK((NULL != pNumReceived), NCP_ST_INVALID_PARAMETER);
    *pNumReceived = 0;

    NCP_TASKIO_CHECK((NULL != pNcpTaskSwState), NCP_ST_TASK_NO_GSM);
    NCP_VALIDATE_TQS_HDL(pvtTqsHdl);
    NCP_NCA_INC_CRITICAL_SECTION(pvtTqsHdl, critSecFlag);    
    NCP_TASKIO_CHECK((NULL != pTasks), NCP_ST_INVALID_PARAMETER);    
    NCP_TASKIO_CHECK(((TRUE != pvtTqsHdl->inOpcqCallbackDoneFn[NCP_TASK_TXQ_0])
                   && (TRUE != pvtTqsHdl->inOpcqCallbackDoneFn[NCP_TASK_TXQ_1])),
                   NCP_ST_TASK_SENDQUEUE_CALLBACK_RECURSION_DETECTED);
    NCP_TASKIO_CHECK((TRUE == pvtTqsHdl->useFlags.useRxQueue), 
              NCP_ST_TASK_TQS_SHARING_VIOLATION);

    pTqs = pvtTqsHdl->pTqs;
    NCP_TASK_PREFETCH_PGIT_FOR_WRITE(pTqs->pCpuPgit);
    NCP_TASK_PREFETCH_PGIT(pTqs->pNcaPgit);    
    
    p_iPCQ = &pTqs->rxQ;
    if (p_iPCQ->shared == TRUE)
    {
        NCP_CALL(NCP_TASK_CLAIM_LOCK_HDL(&p_iPCQ->qLock, flags, &unlockRequired));
    }
    
    pInputQueueEntry = p_iPCQ->u.ipcq_info.pIPCQentry;
    NCP_TASK_PREFETCH_PCQ_ENTRY((pInputQueueEntry));
    NCP_TASK_PREFETCH_TASK_HEADER(pInputQueueEntry);
        
    if (p_iPCQ->u.ipcq_info.autoConsumptionMode)
    {
        NCP_TASKIO_CHECK(0 != numTasks, NCP_ST_INVALID_PARAMETER);
        if (NCP_ST_SUCCESS != (ncpStatus = ncp_task_recv_normal(pvtTqsHdl,
                                      p_iPCQ,
                                      pInputQueueEntry,
                                      numTasks, 
                                      pNumReceived, 
                                      pTasks,
                                      wait)))
        {                             
            if (NCP_ST_TASK_RECV_QUEUE_EMPTY == ncpStatus)
            {    
                NCP_JUMP_RETURN(); /* silent return */
            }
            else 
            {
                NCP_CALL(ncpStatus);
            }        
        }    
    }
    else
    {
        /* 
         * We allow caller to specify zero.   
         * Can be used to complete all outstanding without receiving more. 
         */
        if (NCP_ST_SUCCESS != (ncpStatus = ncp_task_recv_deferred(pvtTqsHdl,
                                        p_iPCQ,
                                        pInputQueueEntry,                                        
                                        numTasks, 
                                        pNumReceived, 
                                        pTasks,
                                        wait))) 
        {                             
            if (NCP_ST_TASK_RECV_QUEUE_EMPTY == ncpStatus)
            {    
                NCP_JUMP_RETURN(); /* silent return */
            }
            else 
            {
                NCP_CALL(ncpStatus);
            }        
        }                                                 
    }                
    
NCP_RETURN_LABEL

    if (NCP_ST_SUCCESS == ncpStatus)
    {
        NCP_TASK_INC_STAT(pvtTqsHdl->pTqs, api_task_recv_ok);
        NCP_TASK_ADD_STAT(pvtTqsHdl->pTqs, RxTask, *pNumReceived);
    }
    else
    {    
        NCP_TASK_INC_ERROR_STAT_VIA_PTQSHDL(pvtTqsHdl,  api_task_recv_err);
    }     
    
    NCP_NCA_DEC_CRITICAL_SECTION(pvtTqsHdl, critSecFlag);    
    
    NCP_CLEANUP_MUTEX_CALL(NCP_TASK_FREE_LOCK_HDL(&p_iPCQ->qLock, flags, &unlockRequired));
    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                   ncp_task_recv_exit,
                   NCP_MSG_EXIT,
                   "ncpStatus=%d pNumReceived=%p(%u)"
                   "\n",
                   ncpStatus,
                   pNumReceived, (pNumReceived) ? (*pNumReceived) : 0);
    return(ncpStatus);
#endif /* #ifdef NCP_DEV_SOCKET */    
}

    
NCP_API ncp_st_t
ncp_task_complete( 
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint8_t txQueueId,
    ncp_uint32_t numTasks,
    ncp_uint32_t *pNumTasksCompleted,
    ncp_bool_t wait)     
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl = (ncp_task_pvt_tqsHdl_data_t *)tqsHdl;
    ncp_task_tqs_swState_t *pTqs = NULL;
    ncp_task_pcq_t *p_oPCQ = NULL;
    NCP_MUTEX_LOCKED_FLAG_DECL(unlockRequired);    
    NCP_NCA_CRITICAL_SECTION_FLAG_DECL(critSecFlag)
    NCP_TASK_LOCK_FLAGS(txqLockFlags);    
    
    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                   ncp_task_complete_entry,
                   NCP_MSG_ENTRY,
                   "tqsHdl=%p txQueueId=%u numTasks=%u pNumTasksCompleted=%p wait=%u"
                   "\n",
                   tqsHdl, txQueueId, numTasks, pNumTasksCompleted, wait);
    NCP_TASKIO_CHECK((NULL != pNumTasksCompleted), NCP_ST_INVALID_PARAMETER);
    *pNumTasksCompleted = 0;
        
    NCP_TASKIO_CHECK((NULL != pNcpTaskSwState), NCP_ST_TASK_NO_GSM);
    NCP_VALIDATE_TQS_HDL(pvtTqsHdl);
    NCP_NCA_INC_CRITICAL_SECTION(pvtTqsHdl, critSecFlag);    
    NCP_TASKIO_CHECK((txQueueId == NCP_TASK_TXQ_0 
               || txQueueId == NCP_TASK_TXQ_1),
               NCP_ST_INVALID_PARAMETER);    
    NCP_TASKIO_CHECK((TRUE == pvtTqsHdl->useFlags.useTxQueue[txQueueId]), 
              NCP_ST_TASK_TQS_SHARING_VIOLATION);  
    NCP_TASKIO_CHECK((TRUE != pvtTqsHdl->inOpcqCallbackDoneFn[txQueueId]), 
                      NCP_ST_TASK_SENDQUEUE_CALLBACK_RECURSION_DETECTED);  
    NCP_TASKIO_CHECK(FALSE == pvtTqsHdl->pTqs->rxQ.u.ipcq_info.autoCompletionMode,     
              NCP_ST_TASK_WRONG_COMPLETION_MODE);
    NCP_TASKIO_CHECK(numTasks <= pvtTqsHdl->completionsOwed,
              NCP_ST_TASK_TOO_MANY_TASK_COMPLETIONS);

    pTqs = pvtTqsHdl->pTqs;
    NCP_TASK_PREFETCH_PGIT_FOR_WRITE(pTqs->pCpuPgit);
    NCP_TASK_PREFETCH_PGIT(pTqs->pNcaPgit);    
         
    if (NCP_TASK_TXQ_0 == txQueueId)
    {
        p_oPCQ = &pTqs->txQ0;
    }
    else
    {
        p_oPCQ = &pTqs->txQ1;
    }  
    
    if (p_oPCQ->shared)
    {
        NCP_CALL(NCP_TASK_CLAIM_LOCK_HDL(&p_oPCQ->qLock, txqLockFlags, &unlockRequired));
    }     

    NCP_TASK_PREFETCH_PCQ_ENTRY_FOR_WRITE(p_oPCQ->u.opcq_info.pOPCQentry);
    
    if (1 == numTasks)    
    {
        
        ncpStatus = ncp_task_single_complete(pvtTqsHdl,
                                    p_oPCQ,
                                    pNumTasksCompleted,
                                    wait);         
                                    
    }
    else 
    {
               
        ncpStatus = ncp_task_bulk_complete(pvtTqsHdl,
                                    p_oPCQ,
                                    numTasks,
                                    pNumTasksCompleted,
                                    wait); 
                                    
    }                                
                                    
    if (ncpStatus != NCP_ST_SUCCESS &&
        ncpStatus != NCP_ST_TASK_SEND_QUEUE_FULL)
    {
        NCP_CALL(ncpStatus);
    }
                                        
NCP_RETURN_LABEL

    pvtTqsHdl->completionsIssued[txQueueId] += *pNumTasksCompleted;
    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                          ncp_xlf_task_complete_txCompletionInfo, NCP_MSG_DEBUG,
                          "in complete: TxQ_%d completions issued incremented by %d, total = 0x%"PRIx64"\r\n",
                          txQueueId,
                          *pNumTasksCompleted,
                          pvtTqsHdl->completionsIssued[txQueueId]);

    if (NCP_ST_SUCCESS == ncpStatus)
    {
        NCP_TASK_INC_STAT(pvtTqsHdl->pTqs, api_task_complete_ok); 
        NCP_TASK_ADD_TXSTAT(pvtTqsHdl->pTqs, TaskCompletions, txQueueId, *pNumTasksCompleted);             
    }        
    else
    {
        NCP_TASK_INC_ERROR_STAT_VIA_PTQSHDL(pvtTqsHdl,  api_task_complete_err);      
    } 
    
    NCP_NCA_DEC_CRITICAL_SECTION(pvtTqsHdl, critSecFlag);  
    
    NCP_CLEANUP_MUTEX_CALL(NCP_TASK_FREE_LOCK_HDL(&p_oPCQ->qLock, txqLockFlags, &unlockRequired));
    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                   ncp_task_complete_exit,
                   NCP_MSG_EXIT,
                   "ncpStatus=%d pNumTasksCompleted=%p(%u)"
                   "\n",
                   ncpStatus,
                   pNumTasksCompleted,
                   (pNumTasksCompleted) ? (*pNumTasksCompleted) : 0);
    return(ncpStatus);
}


NCP_API ncp_st_t 
ncp_task_buffer_alloc( 
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint32_t numTaskBuffers, 
    ncp_uint32_t *pNumAllocated, 
    ncp_uint32_t *pBufferSizes, 
    ncp_uint8_t    bufferPoolId, 
    void **pTaskBuffers, 
    ncp_bool_t wait) 
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl = (ncp_task_pvt_tqsHdl_data_t *)tqsHdl;
    ncp_task_pool_t         *pPool;
    NCP_NCA_CRITICAL_SECTION_FLAG_DECL(critSecFlag)    

    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                   ncp_task_buffer_alloc_entry,
                   NCP_MSG_ENTRY,
                   "tqsHdl=%p numTaskBuffers=%u pNumAllocated=%p pBufferSizes=%p bufferPoolId=%u pTaskBuffers=%p wait=%u"
                   "\n",
                   tqsHdl, numTaskBuffers, pNumAllocated, pBufferSizes, bufferPoolId, pTaskBuffers, wait);
    NCP_TASKIO_CHECK((NULL != pNumAllocated), NCP_ST_INVALID_PARAMETER);
    *pNumAllocated = 0;
    
    NCP_TASKIO_CHECK((NULL != pNcpTaskSwState), NCP_ST_TASK_NO_GSM);
    NCP_VALIDATE_TQS_HDL(pvtTqsHdl);
    NCP_NCA_INC_CRITICAL_SECTION(pvtTqsHdl, critSecFlag);
    NCP_TASKIO_CHECK((NULL != pBufferSizes), NCP_ST_INVALID_PARAMETER);
    NCP_TASKIO_CHECK((NULL != pTaskBuffers), NCP_ST_INVALID_PARAMETER);    
    NCP_TASKIO_CHECK(((bufferPoolId >= NCP_NCAV3_FIRST_SHARED_POOL_ID 
                && bufferPoolId < NCP_NCAV3_NUM_TASK_MEMORY_POOLS)
                || (NCP_TASK_CPU_POOL_ALIAS == bufferPoolId)), 
                NCP_ST_INVALID_PARAMETER); 
    NCP_TASKIO_CHECK((0 != (pvtTqsHdl->pTqs->validPoolsMask & (1<<bufferPoolId))), 
               NCP_ST_TASK_BUFFER_POOL_NOT_CONFIGURED_FOR_TQS);
               
    if (NCP_TASK_RESTRICT_BULK_APIS)
    {    
        NCP_TASKIO_CHECK((numTaskBuffers <= NCP_TASK_API_MAX_BULK_ITEM_COUNT),
                  NCP_ST_TASK_BULK_REQUEST_TOO_BIG);                     
    }
    
        
    if (0 == bufferPoolId) /* CPU Pool Alias? */
    {
        if (NULL == (pPool = pvtTqsHdl->cpuPoolHdl))
        {
			printf("1");
            NCP_CALL(NCP_ST_TASK_TQS_INVALID_POOL);    
        }    
        if (TRUE == pPool->disabledForReinit)
        {
            NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                  ncp_xlf_task_buffer_alloc_disabledForReinit,
                                  NCP_MSG_ERROR,
                                  "It is invalid to operate on a task handle while its pool is being reinitialized.\n");
            NCP_CALL(NCP_ST_TASK_POOL_IS_BEING_REINITIALIZED);
        }
        
        /**
         *  If wait is TRUE, repeatedly alloc until at least 1 buffer
         *   is allocated.
         */
        while (1)
        {

            ncpStatus = ncp_task_bulk_buffer_alloc_cpu_pool(
                    pvtTqsHdl,
                    pPool,
                    pTaskBuffers,
                    pBufferSizes,
                    numTaskBuffers,
                    pNumAllocated);

            if ( NCP_ST_PTHREAD_MUTEX_OWNER_DEAD  == ncpStatus )
            {
                NCP_CALL(ncpStatus);
            }


            if (!(wait == TRUE
                        && ncpStatus == NCP_ST_NO_MEMORY
                        && *pNumAllocated == 0))
            {
                break;
            }

            /** Give another thread a chance to free **/
#ifndef NCP_KERNEL
            ncp_sys_usleep(10);
#endif
        }
    }
    else 
    {
        ncp_task_tqs_swState_t *pTqs;
        ncp_task_mme_allocator_t *pAllocator;
        
        pTqs = pvtTqsHdl->pTqs;
        NCP_TASK_PREFETCH_PGIT_FOR_WRITE(pTqs->pCpuPgit);
        NCP_TASK_PREFETCH_PGIT(pTqs->pNcaPgit);    
        
        pAllocator = &pTqs->mmeAllocator[bufferPoolId];  
        
        ncpStatus = ncp_task_bulk_MMEpool_alloc(
                    pvtTqsHdl, 
                    pAllocator,
                    numTaskBuffers,
                    pNumAllocated,
                    pBufferSizes, 
                    pTaskBuffers,
                    bufferPoolId,
                    wait);

        if ((ncpStatus != NCP_ST_SUCCESS) && (ncpStatus != NCP_ST_NO_MEMORY))
        {
            NCP_CALL(ncpStatus);
        }    
    }

NCP_RETURN_LABEL

    if (NCP_ST_SUCCESS == ncpStatus)
    {
        NCP_TASK_INC_STAT(pvtTqsHdl->pTqs, api_task_buffer_alloc_ok);
        NCP_TASK_ADD_STAT(pvtTqsHdl->pTqs, BuffAllocs, *pNumAllocated);        
    }
    else
    {
        NCP_TASK_INC_ERROR_STAT_VIA_PTQSHDL(pvtTqsHdl,  api_task_buffer_alloc_err);
    }
    
    NCP_NCA_DEC_CRITICAL_SECTION(pvtTqsHdl, critSecFlag);        
    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                          ncp_task_buffer_alloc_exit,
                          NCP_MSG_EXIT,
                          "ncpStatus=%d "
                          "pNumAllocated=%p(%u) pBufferSizes=%p(%u) pTaskBuffers=%p(%p)"
                          "\n",
                          ncpStatus,
                          pNumAllocated, (pNumAllocated) ? (*pNumAllocated) : 0,
                          pBufferSizes, (pBufferSizes) ? (*pBufferSizes) : 0,
                          pTaskBuffers, (pTaskBuffers) ? (*pTaskBuffers) : 0);
    return(ncpStatus);         
}

NCP_API ncp_st_t 
ncp_task_buffer_free( 
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint8_t txQueueId,
    ncp_uint32_t numTaskBuffers, 
    ncp_uint32_t *pNumFreed, 
    ncp_uint8_t bufferPoolId,
    void        **pTaskBuffers,    
    ncp_bool_t  *pMrefBitSet,
    ncp_bool_t wait) 
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl = (ncp_task_pvt_tqsHdl_data_t *)tqsHdl;
    ncp_task_pcq_t *p_oPCQ = NULL; /* fix compiler warning */   
    NCP_MUTEX_LOCKED_FLAG_DECL(unlockRequired);    
    NCP_NCA_CRITICAL_SECTION_FLAG_DECL(critSecFlag)
    NCP_TASK_LOCK_FLAGS(txqLockFlags);     

    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                   ncp_task_buffer_free_entry,
                   NCP_MSG_ENTRY,
                   "tqsHdl=%p txQueueId=%u numTaskBuffers=%u pNumFreed=%p bufferPoolId=%u pTaskBuffers=%p pMrefBitSet=%p wait=%u"
                   "\n",
                   tqsHdl, txQueueId, numTaskBuffers, pNumFreed, bufferPoolId, pTaskBuffers, pMrefBitSet, wait);
    NCP_TASKIO_CHECK((NULL != pNumFreed), NCP_ST_INVALID_PARAMETER);
    *pNumFreed = 0;
    
    NCP_TASKIO_CHECK((NULL != pNcpTaskSwState), NCP_ST_TASK_NO_GSM);
    NCP_VALIDATE_TQS_HDL(pvtTqsHdl);
    NCP_NCA_INC_CRITICAL_SECTION(pvtTqsHdl, critSecFlag);    
    NCP_TASKIO_CHECK((txQueueId == NCP_TASK_TXQ_0 
               || txQueueId == NCP_TASK_TXQ_1),
               NCP_ST_INVALID_PARAMETER);    

    NCP_TASKIO_CHECK((NULL != pTaskBuffers), NCP_ST_INVALID_PARAMETER);
    NCP_TASKIO_CHECK((NULL != pvtTqsHdl->cpuPoolHdl || NULL != pMrefBitSet), NCP_ST_INVALID_PARAMETER);  
    NCP_TASKIO_CHECK(((bufferPoolId >= NCP_NCAV3_FIRST_SHARED_POOL_ID 
                && bufferPoolId < NCP_NCAV3_NUM_TASK_MEMORY_POOLS)
                || (NCP_TASK_CPU_POOL_ALIAS == bufferPoolId)), 
                NCP_ST_INVALID_PARAMETER);   
    NCP_TASKIO_CHECK((0 != (pvtTqsHdl->pTqs->validPoolsMask & (1<<bufferPoolId))), 
               NCP_ST_TASK_BUFFER_POOL_NOT_CONFIGURED_FOR_TQS);                
    
    if (NCP_TASK_RESTRICT_BULK_APIS)
    {    
        NCP_TASKIO_CHECK((numTaskBuffers <= NCP_TASK_API_MAX_BULK_ITEM_COUNT),
                  NCP_ST_TASK_BULK_REQUEST_TOO_BIG);     
    }

                      
    NCP_TASKIO_CHECK((TRUE == pvtTqsHdl->useFlags.useTxQueue[txQueueId]), 
              NCP_ST_TASK_TQS_SHARING_VIOLATION);
         
    if (0 == bufferPoolId) /* CPU Pool Alias? */
    {
        if (NULL == pvtTqsHdl->cpuPoolHdl)
        {
			printf("2");
            NCP_CALL(NCP_ST_TASK_TQS_INVALID_POOL);    
        }    
        if (TRUE == pvtTqsHdl->cpuPoolHdl->disabledForReinit)
        {
            NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                                  ncp_xlf_task_buffer_free_disabledForReinit,
                                  NCP_MSG_ERROR,
                                  "It is invalid to operate on a task handle while its pool is being reinitialized.\n");
            NCP_CALL(NCP_ST_TASK_POOL_IS_BEING_REINITIALIZED);
        }
        
        /* TODO - make inline */
        NCP_CALL(ncp_task_bulk_cpu_pool_buffer_free(pvtTqsHdl,
                                  numTaskBuffers,
                                  pNumFreed, 
                                  pTaskBuffers));
    }   
    else
    { 
        ncp_task_tqs_swState_t *pTqs;
        
        NCP_TASKIO_CHECK((TRUE != pvtTqsHdl->inOpcqCallbackDoneFn[txQueueId]), 
                      NCP_ST_TASK_SENDQUEUE_CALLBACK_RECURSION_DETECTED);
                              
        pTqs = pvtTqsHdl->pTqs;
        NCP_TASK_PREFETCH_PGIT_FOR_WRITE(pTqs->pCpuPgit);
        NCP_TASK_PREFETCH_PGIT(pTqs->pNcaPgit);    
            
        if (NCP_TASK_TXQ_0 == txQueueId)
        {
            p_oPCQ = &pTqs->txQ0;
        }
        else
        {
            p_oPCQ = &pTqs->txQ1;
        }  
    
        if (p_oPCQ->shared)
        {
            NCP_CALL(NCP_TASK_CLAIM_LOCK_HDL(&p_oPCQ->qLock, txqLockFlags, &unlockRequired));
        }  

        NCP_TASK_PREFETCH_PCQ_ENTRY_FOR_WRITE(p_oPCQ->u.opcq_info.pOPCQentry);
            
        /* TODO - make inline */
        ncpStatus = ncp_task_bulk_buffer_free(pvtTqsHdl,
                                  p_oPCQ,
                                  bufferPoolId,
                                  numTaskBuffers,
                                  pNumFreed, 
                                  pTaskBuffers,
                                  pMrefBitSet,
                                  wait);    
                                  
        if (ncpStatus != NCP_ST_SUCCESS &&
            ncpStatus != NCP_ST_TASK_SEND_QUEUE_FULL)
        {
            NCP_CALL(ncpStatus);
        }                                  
    }
                                  
NCP_RETURN_LABEL
       
    if (NCP_ST_SUCCESS == ncpStatus)
    {
        NCP_TASK_INC_STAT(pvtTqsHdl->pTqs, api_task_buffer_free_ok);
        NCP_TASK_ADD_TXSTAT(pvtTqsHdl->pTqs, BuffFrees, txQueueId, *pNumFreed);          
    }
    else
    {
        NCP_TASK_INC_ERROR_STAT_VIA_PTQSHDL(pvtTqsHdl,  api_task_buffer_free_err);
    }

    NCP_CLEANUP_MUTEX_CALL(NCP_TASK_FREE_LOCK_HDL(&p_oPCQ->qLock, txqLockFlags, &unlockRequired));

    NCP_NCA_DEC_CRITICAL_SECTION(pvtTqsHdl, critSecFlag);
    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                   ncp_task_buffer_free_exit,
                   NCP_MSG_EXIT,
                   "ncpStatus=%d "
                   "pNumFreed=%p(%u) pTaskBuffers=%p(%p) pMrefBitSet=%p(%u)"
                   "\n",
                   ncpStatus,
                   pNumFreed, (pNumFreed) ? (*pNumFreed) : 0,
                   pTaskBuffers, (pTaskBuffers) ? (*pTaskBuffers) : 0,
                   pMrefBitSet, (pMrefBitSet) ? (*pMrefBitSet) : 0);
    return(ncpStatus);
}

NCP_API ncp_st_t 
ncp_task_free(ncp_task_tqs_hdl_t tqsHdl,
              ncp_uint8_t  txQueueId,
              ncp_uint32_t numTasks,
              ncp_uint32_t *pNumFreed,
              ncp_task_free_meta_t *metadata,
              ncp_bool_t   wait) 
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl = (ncp_task_pvt_tqsHdl_data_t *)tqsHdl;
    ncp_task_tqs_swState_t *pTqs = NULL;
    ncp_task_pcq_t *p_oPCQ = NULL;
    NCP_NCA_CRITICAL_SECTION_FLAG_DECL(critSecFlag)    

    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                   ncp_task_free_entry,
                   NCP_MSG_ENTRY,
                   "tqsHdl=%p txQueueId=%u"
                   "numTasks=%u pNumFreed=%p metadata=%p wait=%u"
                   "\n",
                   tqsHdl, txQueueId,
                   numTasks, pNumFreed, metadata, wait);
    NCP_TASKIO_CHECK((NULL != pNumFreed), NCP_ST_INVALID_PARAMETER);
    *pNumFreed = 0;        
    
    NCP_TASKIO_CHECK((NULL != pNcpTaskSwState), NCP_ST_TASK_NO_GSM);    
    NCP_VALIDATE_TQS_HDL(pvtTqsHdl);
    NCP_NCA_INC_CRITICAL_SECTION(pvtTqsHdl, critSecFlag);    
    NCP_TASKIO_CHECK((txQueueId == NCP_TASK_TXQ_0 
               || txQueueId == NCP_TASK_TXQ_1),
               NCP_ST_INVALID_PARAMETER);    

    NCP_TASKIO_CHECK((NULL != metadata), NCP_ST_INVALID_PARAMETER); 
    NCP_TASKIO_CHECK(numTasks != 0, NCP_ST_INVALID_PARAMETER);


    if (NCP_TASK_RESTRICT_BULK_APIS)
    {    
        NCP_TASKIO_CHECK((numTasks <= NCP_TASK_API_MAX_BULK_ITEM_COUNT),
                  NCP_ST_TASK_BULK_REQUEST_TOO_BIG);             
    }
                  
    NCP_TASKIO_CHECK((TRUE == pvtTqsHdl->useFlags.useTxQueue[txQueueId]), 
              NCP_ST_TASK_TQS_SHARING_VIOLATION);
                  
    pTqs = pvtTqsHdl->pTqs;
    NCP_TASK_PREFETCH_PGIT_FOR_WRITE(pTqs->pCpuPgit);
    NCP_TASK_PREFETCH_PGIT(pTqs->pNcaPgit);    
        
    if (NCP_TASK_TXQ_0 == txQueueId)
    {
        p_oPCQ = &pTqs->txQ0;
    }
    else
    {
        p_oPCQ = &pTqs->txQ1;
    }  
    NCP_TASK_PREFETCH_PCQ_ENTRY_FOR_WRITE(p_oPCQ->u.opcq_info.pOPCQentry);
        
    if (NULL == pvtTqsHdl->cpuPoolHdl)
    {
        NCP_TASKIO_CHECK((TRUE != pvtTqsHdl->inOpcqCallbackDoneFn[txQueueId]), 
                          NCP_ST_TASK_SENDQUEUE_CALLBACK_RECURSION_DETECTED);
                          
        if (1 == numTasks)
        {    
            
            ncpStatus = ncp_task_free_single_by_metadata(
                    pvtTqsHdl,
                    p_oPCQ,
                    pNumFreed,
                    metadata,
                    wait);
        }            
        else 
        {                        
            ncpStatus = ncp_task_bulk_task_free_by_metadata(
                    pvtTqsHdl,
                    p_oPCQ,
                    numTasks,
                    pNumFreed,
                    metadata,
                    wait);
        }            
    }    
    else
    {
        
        ncpStatus = ncp_task_bulk_cpu_pool_task_free(
                            pvtTqsHdl,
                            p_oPCQ,
                            numTasks,
                            pNumFreed,
                            metadata,
                            wait);

    }               
    if (ncpStatus != NCP_ST_SUCCESS &&
        ncpStatus != NCP_ST_TASK_SEND_QUEUE_FULL)
    {
        NCP_CALL(ncpStatus);
    }
                
NCP_RETURN_LABEL

    NCP_NCA_DEC_CRITICAL_SECTION(pvtTqsHdl, critSecFlag);
    NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,
                   ncp_task_free_exit,
                   NCP_MSG_EXIT,
                   "ncpStatus=%d "
                   "pNumFreed=%p(%u)"
                   "\n",
                   ncpStatus,
                   pNumFreed, (pNumFreed) ? (*pNumFreed) : 0);
    return(ncpStatus);
}


/* 
 * TBR APIs
 */

#if (1 == NCP_TASK_TBR_ENABLED) 
     
ncp_st_t  
ncp_task_tbr_buffer_ownership_get( ncp_task_tqs_hdl_t tqsHdl,
                            ncp_uint8_t poolId,
                            void *taskBuffer,  
                            ncp_task_pid_t *pPid)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl = (ncp_task_pvt_tqsHdl_data_t * )tqsHdl;
    NCP_NCA_CRITICAL_SECTION_FLAG_DECL(critSecFlag)
    
    NCP_TASKIO_CHECK((NULL != pNcpTaskSwState), NCP_ST_TASK_NO_GSM);    
    NCP_VALIDATE_TQS_HDL(pvtTqsHdl); 
    NCP_NCA_INC_CRITICAL_SECTION(pvtTqsHdl, critSecFlag); 
    NCP_TASKIO_CHECK((NULL != pPid), NCP_ST_INVALID_PARAMETER);       
    NCP_TASKIO_CHECK((NULL != taskBuffer), NCP_ST_INVALID_PARAMETER);

    NCP_TASK_TBR_TASK_BUFFER_OWNERSHIP_GET(pvtTqsHdl, poolId, taskBuffer, pPid);
        
NCP_RETURN_LABEL

    if (NCP_ST_SUCCESS == ncpStatus)
    {
        NCP_TASK_INC_STAT(pvtTqsHdl->pTqs, api_task_tbr_buffer_ownership_get_ok);        
    }        
    else
    {
        NCP_TASK_INC_ERROR_STAT_VIA_PTQSHDL(pvtTqsHdl,  api_task_tbr_buffer_ownership_get_err);        
    } 
        
    NCP_NCA_DEC_CRITICAL_SECTION(pvtTqsHdl, critSecFlag);    
    return(ncpStatus);        
}                                 
                            

#else

ncp_st_t  
ncp_task_tbr_buffer_ownership_get( ncp_task_tqs_hdl_t tqsHdl,
                            ncp_uint8_t poolId,
                            void *taskBuffer,  
                            ncp_task_pid_t *pPid)
{
    return NCP_ST_SUCCESS;
}


#endif
                              
ncp_st_t
ncp_task_shared_region_size_get_by_id(
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint32_t regionId,
    ncp_uint64_t *size)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_ncav3_cpu_profile_t *profile;
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl =
        (ncp_task_pvt_tqsHdl_data_t *) tqsHdl;
    int i;

    NCP_CHECK((NULL != size), NCP_ST_INVALID_PARAMETER);    
    NCP_CHECK((NULL != pNcpTaskSwState), NCP_ST_TASK_NO_GSM);    
    NCP_VALIDATE_TQS_HDL(pvtTqsHdl);                       

    profile = &pvtTqsHdl->pTqs->pAppProfile->baseProfile;

    for (i = 0; i < profile->numSharedDataRegionMaps; i++)
    {
        if (profile->sharedDataRegionMap[i].regionId == regionId)
        {
            *size = (ncp_uint64_t) profile->sharedDataRegionMap[i].size;
            NCP_RETURN(NCP_ST_SUCCESS);
        }
    }

    ncpStatus = NCP_ST_TASK_SHARED_REGION_NOT_FOUND;

NCP_RETURN_LABEL

    return ncpStatus;
}

ncp_st_t
ncp_task_shared_region_size_get_by_name(
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_task_resource_name_t *name,
    ncp_uint64_t *size)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_ncav3_cpu_profile_t *profile;
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl =
        (ncp_task_pvt_tqsHdl_data_t *) tqsHdl;
    int i;

    NCP_CHECK((NULL != size), NCP_ST_INVALID_PARAMETER);    
    NCP_CHECK((NULL != pNcpTaskSwState), NCP_ST_TASK_NO_GSM);    
    NCP_VALIDATE_TQS_HDL(pvtTqsHdl);                       

    profile = &pvtTqsHdl->pTqs->pAppProfile->baseProfile;

    for (i = 0; i < profile->numSharedDataRegionMaps; i++)
    {
        if (0 == strncmp(
                    profile->sharedDataRegionMap[i].name.name,
                    name->name,
                    sizeof(ncp_task_resource_name_t)))
        {
            *size = (ncp_uint64_t) profile->sharedDataRegionMap[i].size;
            NCP_RETURN(NCP_ST_SUCCESS);
        }
    }

    ncpStatus = NCP_ST_TASK_SHARED_REGION_NOT_FOUND;

NCP_RETURN_LABEL

    return ncpStatus;
}


ncp_st_t
ncp_task_ipcq_disable(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t tqsId)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_tqs_swState_t *pTqs;
    ncp_dev_hdl_t dev;

    NCP_CHECK((NULL != pNcpTaskSwState), NCP_ST_TASK_NO_GSM);
    NCP_CHECK(tqsId < NCP_NCAV3_NUM_CPU_TQSETS, NCP_ST_INVALID_PARAMETER);

    pTqs = &pNcpTaskSwState->tqsSwState[tqsId];
    NCP_CHECK(pTqs->configured == TRUE, NCP_ST_TASK_TQS_NOT_CONFIGURED);

    dev = ncp_dev_hdls[((ncp_t *) ncpHdl)->id];

    NCP_CALL(ncp_ncav3_disable_ipcq(dev, tqsId / 8, tqsId % 8, tqsId));

NCP_RETURN_LABEL

    return ncpStatus;
}
