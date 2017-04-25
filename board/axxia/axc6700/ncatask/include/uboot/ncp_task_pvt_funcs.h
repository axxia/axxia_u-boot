/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                        *
 **                                                                       *
 **************************************************************************/

#ifndef __NCP_TASK_PVT_FUNCS_H__
#define __NCP_TASK_PVT_FUNCS_H__

#ifdef __cplusplus
extern "C" {
#endif

ncp_st_t 
ncp_task_getpid(ncp_pid_t *pPid);

extern ncp_st_t 
ncp_task_block_on_hw_interrupt(ncp_dev_hdl_t devHdl, ncp_uint32_t intrType, 
                               ncp_uint8_t grp, ncp_uint32_t tqsRelId, ncp_uint8_t tqsID);
     
ncp_st_t
ncp_task_tbr_task_buffer_pid_get( ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
                                            ncp_uint8_t poolId,
                                            void *taskBuffer,
                                            ncp_task_pid_t *pPid);
                                                                                    
ncp_st_t
ncp_task_tbr_cpu_pool_recovery_clear(ncp_uint8_t poolId);

ncp_st_t
ncp_task_tbr_global_pool_refill_recovery(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl);

void
ncp_task_increment_pool_use_counts(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl);

ncp_st_t
ncp_task_decrement_pool_use_counts(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl);
    
ncp_st_t
ncp_task_internal_tqs_unbind(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
                             ncp_bool_t inRecovery,
                             ncp_bool_t deleteThread);
    
ncp_st_t 
ncp_task_map_pools(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,  
                   ncp_uint32_t tqsId);
  
ncp_st_t
ncp_task_tbr_unbind_threads(ncp_task_process_info_t *pProcess); 
                                                           
ncp_st_t
ncp_task_tbr_initiate_recovery(ncp_task_process_info_t *pProcess);

ncp_st_t
ncp_task_tbr_update_per_tqs_cpupool_refill_count(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl);

ncp_st_t
ncp_task_add_thread(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
                    ncp_task_resource_name_t *processName,
                    ncp_task_resource_name_t *threadName,
                    ncp_uint32_t tqsId,
                    ncp_task_process_info_t **ppProcess);
                    
/* TODO - make inline */
ncp_st_t 
ncp_task_tbr_buffers_recover(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
                             ncp_task_pid_t searchPid);

/* TODO - make inline */
ncp_st_t 
ncp_task_tbr_leak_check(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
                        ncp_task_pid_t searchPid);

ncp_st_t
ncp_task_add_thread(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
                    ncp_task_resource_name_t *processName,
                    ncp_task_resource_name_t *threadName,
                    ncp_uint32_t tqsId,
                    ncp_task_process_info_t **ppProcess);
                    
ncp_st_t                    
ncp_task_recover_tqs_hdl_by_thread(ncp_task_resource_name_t *processName, 
                                   ncp_task_resource_name_t *threadName, 
                                   ncp_uint32_t             tqsId, 
                                   ncp_task_pvt_tqsHdl_data_t **pvtTqsHdl);
                                                     

ncp_st_t
ncp_task_delete_thread(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
                       ncp_task_resource_name_t *threadName);
        
/* TODO - make these debug checks depend on NCP_CHECK once bugs worked out of common samples */
 
#ifndef NCP_TASK_BUFFER_OVERRUN_CHECK_DISABLE                           
ncp_st_t
ncp_task_buffer_overrun_check(ncp_uint8_t poolId, ncp_uintptr_t ptr, ncp_uint16_t sz);

#define NCP_TASK_BUFFER_OVERRUN_CHECK(_poolId, _ptr, _sz) \
    NCP_CALL(ncp_task_buffer_overrun_check(_poolId, (ncp_uintptr_t)(void *)_ptr, _sz))
#else
#define NCP_TASK_BUFFER_OVERRUN_CHECK(_poolId, _ptr, _sz)
#endif

#ifndef NCP_TASK_VALIDATE_OUTPUT_TASK_DISABLE                                                          
ncp_st_t
ncp_task_validate_output_task(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl, 
                           ncp_task_header_t *thisHeader);
#define NCP_TASK_VALIDATE_OUTPUT_TASK(_pvtTqsHdl, _taskHeader) \
    NCP_CALL(ncp_task_validate_output_task(_pvtTqsHdl, _taskHeader))
#else
#define NCP_TASK_VALIDATE_OUTPUT_TASK(_pvtTqsHdl, _taskHeader)
#endif    

ncp_st_t
ncp_task_bulk_complete(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
                    ncp_task_pcq_t             *p_oPCQ,
                    ncp_uint32_t               numTasks,
                    ncp_uint32_t               *pNumTasksCompleted,
                    ncp_bool_t                 wait);
                    
/* TODO - Remove forwards when added to inline_funcs.h */

ncp_st_t _ncp_task_buffer_free( 
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
    ncp_task_pcq_t *p_oPCQ,
    ncp_uint8_t  bufferPoolId,    
    ncp_uint32_t numBuffers, 
    ncp_uint32_t *pNumFreed, 
    void        **pBuffers,    
    ncp_bool_t  *pMrefBitSet,
    ncp_bool_t wait);
    
#define NCP_TASK_PROCESS_SEND_DONE(_myTqsHdl, _txQueueId)             \
    if (TRUE == _myTqsHdl->sendDoneInfo[_txQueueId].sendDonePending)  \
    {                                                                 \
        ncp_task_process_send_done(pvtTqsHdl, _txQueueId);            \
    } 
    
#define NCP_TASK_ADD_SEND_DONE(_pvtTqsHdl,     \
                                  _txQueueId,  \
                                  _type,       \
                                  _sendDonefn, \
                                  _arg1,       \
                                  _arg2,       \
                                  _arg3,       \
                                  _arg4)       \
    ncp_task_add_send_done(_pvtTqsHdl,         \
                          _txQueueId,          \
                          _type,               \
                          _sendDonefn,         \
                          _arg1,               \
                          _arg2,               \
                          _arg3,               \
                          _arg4)               \

    
/* NCP_INLINE */
ncp_st_t 
ncp_task_bulk_cpu_pool_buffer_free( 
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
    ncp_uint32_t numBuffers, 
    ncp_uint32_t *pNumFreed, 
    void        **pBuffers);   
        
/* NCP_INLINE */ 

ncp_st_t 
ncp_task_bulk_buffer_free( 
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
    ncp_task_pcq_t *p_oPCQ,
    ncp_uint8_t  bufferPoolId,
    ncp_uint32_t numBuffers, 
    ncp_uint32_t *pNumFreed, 
    void        **pBuffers,
    ncp_bool_t  *pMrefBitSet,
    ncp_bool_t  wait);
 
/* NCP_INLINE */ 
ncp_st_t
ncp_task_bulk_task_send(
                ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
                ncp_task_pcq_t *p_oPCQ,
                ncp_uint32_t numTasks,
                ncp_uint32_t *pNumTasksSent,
                ncp_task_send_meta_t *pMetadata,
                ncp_int32_t *pCompletionsIssued,
                ncp_bool_t wait);

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
    ncp_bool_t wait);

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
    ncp_bool_t wait);

/* NCP_INLINE */
ncp_st_t
ncp_task_bulk_task_refCnt_increment(
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
    ncp_task_pcq_t *p_oPCQ,
    ncp_uint32_t numTasks,
    ncp_task_header_t **pTasks,
    ncp_uint32_t *pNumTasksIncremented,
    ncp_task_refCnt_inc_done_fn_t *pFns,
    void **pRefCntIncDoneArgs,
    ncp_bool_t wait);

/* NCP_INLINE */
ncp_st_t
ncp_task_bulk_buffer_refCnt_increment(
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
    ncp_task_pcq_t *p_oPCQ,
    ncp_uint32_t numDescs,
    ncp_task_buffer_desc_t *pDescs,
    ncp_uint32_t *pNumTasksIncremented,
    ncp_task_buffer_refCnt_inc_done_fn_t *pFns,
    void **pRefCntIncDoneArgs,
    ncp_bool_t wait);

/* NCP_INLINE */    
ncp_st_t
ncp_task_bulk_cpu_pool_task_free(
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
    ncp_task_pcq_t       *p_oPCQ,
    ncp_uint32_t          numTasks,
    ncp_uint32_t         *pNumFreed,
    ncp_task_free_meta_t *metadata,
    ncp_bool_t            wait);
                                
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
                ncp_bool_t wait);

ncp_st_t
ncp_task_bulk_task_free_by_metadata(
                ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
                ncp_task_pcq_t *p_oPCQ,
                ncp_uint32_t numTasks,
                ncp_uint32_t *pNumTasksFreed,
                ncp_task_free_meta_t *metadata,
                ncp_bool_t wait);
                                
ncp_st_t 
ncp_task_init_wait_profile(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl);

ncp_st_t
ncp_task_attach_tqs(ncp_hdl_t *ncpHdl, ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl, ncp_uint32_t tqsId, ncp_task_tqs_usage_t *pParams);

ncp_st_t
ncp_task_detach_tqs(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl);

ncp_st_t
ncp_task_bulk_buffer_alloc_cpu_pool(
    ncp_task_pvt_tqsHdl_data_t  *pvtTqsHdl,  /* TODO: needed? */
    ncp_task_pool_t             *pPool,
    void                       **taskBuffers,
    ncp_uint32_t                *taskBufferSizes,
    ncp_uint32_t                 numTaskBuffers,
    ncp_uint32_t                *numTaskBuffersAllocated);
    
#ifdef NCP_NCA_ARM_PMU_PROFILING_ENABLED
ncp_st_t
ncpTaskArmPmuEnable(int *pNumCounters) ;

void
ncpTaskArmPmuInitCounters(int numPmuEvents,
                          ncp_uint32_t *pmuEventCodes);
              
void
ncpTaskArmPmuResetCounters(void);

void  
ncpTaskArmPmuStoreResults(ncpTaskArmPmuResults_t *pPmuResults,
                          int numPmuEvents,
                          ncp_uint32_t *pmuEventCodes,
                          const char *txtString);

void
ncpTaskArmPmuDisplayStoredResults(ncpTaskArmPmuResults_t *pPmuResultsStart,
                                  ncpTaskArmPmuResults_t *pPmuResults,
                                  int numEntries, 
                                  int numPmuEvents, 
                                  ncp_uint32_t *pmuEventCodes);
                                  
#endif /* NCP_NCA_ARM_PMU_PROFILING_ENABLED */

#ifdef __cplusplus
}
#endif
#endif /* __NCP_TASK_PVT_FUNCS_H__ */
