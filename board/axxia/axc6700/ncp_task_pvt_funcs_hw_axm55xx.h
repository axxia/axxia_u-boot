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

#ifndef __ncp_task_pvt_funcs_hw_axm55xx_h__
#define __ncp_task_pvt_funcs_hw_axm55xx_h__


/* =====================================================
 * real acp34xx hardware platforms only!
 * Forward and external function declarations
 * =====================================================
 */

ncp_st_t
ncp_task_detach_mme_allocator(ncp_pvt_task_hdl_t *myTaskHdl);

ncp_st_t
ncp_task_attach_mme_allocator(ncp_pvt_task_hdl_t *myTaskHdl);


ncp_st_t
ncp_task_v2_allocate_domain_object(ncp_uint64_t objOffset,
                                   int          size,
                                   void         **pAddr,
                                   ncp_bool_t   doMemset);

#define NCP_TASK_INITIALIZE_DOMAIN_OBJ_VA(_objOffset, _size, _pAddr, _doMemset) \
    ncp_task_v2_allocate_domain_object(_objOffset,(int)( _size),(void **) (_pAddr), _doMemset)

ncp_st_t ncp_task_register_grp_interrupts(ncp_dev_hdl_t devHdl,
                                          ncp_uint32_t activeGrpMask);

ncp_st_t ncp_task_block_on_hw_interrupt(ncp_dev_hdl_t devHdl, ncp_uint32_t intType, ncp_uint8_t grp, ncp_uint64_t linearId);

ncp_st_t ncp_task_v2_read_rbp_depths(ncp_dev_hdl_t dev,
                                 int rbpoolID,
                                 ncp_uint32_t *pDepth_sz0,
                                 ncp_uint32_t *pDepth_sz1,
                                 ncp_uint32_t *pDepth_sz2,
                                 ncp_uint32_t *pDepth_sz3);


ncp_st_t
ncp_dev_read_rbp_depth(ncp_dev_hdl_t dev, ncp_uint32_t group, ncp_uint32_t *pDepth0, ncp_uint32_t *pDepth1);

ncp_st_t
ncp_task_v2_set_rbp_backpressure(ncp_dev_hdl_t dev, ncp_bool_t enable, ncp_uint32_t iPCQmask, ncp_uint32_t bSizeMask);

#define NCP_ALLOC_CACHEABLE(_size) \
ncp_task_v2_alloc_cacheable(_size)

ncp_st_t
ncp_task_v2_alloc_aligned(void **pMem, int size, ncp_uint32_t alignment);

ncp_st_t
ncp_task_v2_alloc_cache_aligned(void **pMem, int size);

void *
ncp_task_v2_alloc_cacheable(int size);

void
ncp_task_v2_unmap_all_memory_pools(ncp_dev_hdl_t devHdl);

ncp_st_t
ncp_task_v2_nca_put_segments_tOutput(ncp_pvt_task_hdl_t *taskHdl,
                                 ncp_vp_hdl_t vpHdl,
                                 ncp_pvt_task_send_meta_t *taskMetaData,
                                 ncp_task_ncaV2_oPCQ_aux_data_t  *taskAuxData,
                                 ncp_task_segment_entry_t *pSegTable,
                                 int numSegs,
                                 ncp_bool_t wait);

ncp_st_t
ncp_task_v2_mmap_prepare_nca_mmio(ncp_hdl_t ncpHdl, ncp_dev_hdl_t devHdl, ncp_bool_t warmRestart);

ncp_st_t
ncp_task_v2_lowlevel_memcfg(ncp_hdl_t ncpHdl, ncp_dev_hdl_t dev, ncp_nca_t *nca, ncp_bool_t warmRestart);

ncp_st_t
ncp_task_v2_program_rxPoolSizes(ncp_dev_hdl_t dev,
                                ncp_uint8_t        id,
                                ncp_uint16_t    size0,
                                ncp_uint16_t    size1,
                                ncp_uint16_t    size2,
                                ncp_uint16_t    size3);

ncp_st_t
ncp_task_v2_config_free(ncp_nca_t *nca);

ncp_st_t
ncp_dev_nca_grp_intr_enable(ncp_dev_hdl_t devHdl, ncp_uint32_t type, ncp_uint8_t grp);

ncp_st_t
ncp_dev_nca_grp_intr_disable(ncp_dev_hdl_t devHdl, ncp_uint32_t type, ncp_uint8_t grp);

ncp_st_t
ncp_dev_intr_enable_nca_rx_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp);

ncp_st_t
ncp_dev_intr_disable_nca_rx_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp);

ncp_st_t
ncp_dev_intr_enable_nca_tx_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp);

ncp_st_t
ncp_dev_intr_disable_nca_tx_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp);

ncp_st_t
ncp_dev_intr_enable_nca_task_completion_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp);

ncp_st_t
ncp_dev_intr_disable_nca_task_completion_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp);

ncp_st_t
ncp_task_v2_format_task_mem_pool(int poolID);

ncp_st_t
ncp_get_sz_kernel_lock(ncp_dev_hdl_t devHdl, int *pSz);

/* called by linus/ose kernel */
ncp_st_t
ncp_task_v2_fill_kernel_mempool(ncp_nca_fill_kernel_memPool_t *pFillPool);

/* called by user mode */
#define NCP_FORMAT_KERNEL_TASK_MEM_POOL(_dev, _numBuffs) \
    ncp_format_kernel_task_mem_pool(_dev, _numBuffs)

ncp_st_t
ncp_format_kernel_task_mem_pool(ncp_dev_hdl_t dev, int numBuffs);

/* called by user mode */
#define NCP_TASK_FILL_KERNEL_BUFFPOOL(_ncpHdl, _i, _k, _qs, _k_ncaRxBuffIndex) \
    ncp_task_fill_kernel_buffPool(_ncpHdl, _i, _k, _qs, _k_ncaRxBuffIndex)

ncp_st_t
ncp_task_fill_kernel_buffPool(ncp_hdl_t ncpHdl, int sz, int num, int queueNum, int buffId);


ncp_st_t
ncp_task_do_kmode_config(ncp_hdl_t ncpHdl,
                         ncp_task_ncaV2_t *swState);

ncp_st_t
ncp_task_finish_kmode_config(ncp_hdl_t ncpHdl,
                         ncp_task_ncaV2_t *pSwState);

#if defined(NCP_KERNEL) && (defined(NCP_OSE) || defined(NCP_VXWORKS))
#define NCP_TASK_SPINLOCK_FLAGS_DECL spinlock_flags_t _spinFlags = 0;
#else
#define NCP_TASK_SPINLOCK_FLAGS_DECL
#endif

#define NCP_NCA_LOWLEVEL_TASK_NCAV2_NATIVE_SEND(_taskHdl,  _vpHdl, _taskMetaData, _taskAuxData, _wait)  \
({                                                                                                      \
    ncp_st_t _st;                                                                                       \
    if ( (NCP_NCA_QS_SHARED == _taskHdl->pThreadQueueSet->qsAccessMode)                                 \
      && (FALSE == _taskHdl->pThreadQueueSet->sendMutexDisabled))                                       \
    {                                                                                                   \
        NCP_TASK_SPINLOCK_FLAGS_DECL;                                                                   \
        NCP_TASK_CLAIM_LOCK(_taskHdl->pThreadQueueSet->qsLock,                                          \
                            _spinFlags);                                                                \
        _st = ncp_task_v2_put_tOutput(_taskHdl,  _vpHdl, _taskMetaData, _taskAuxData, _wait);           \
        NCP_TASK_FREE_LOCK(_taskHdl->pThreadQueueSet->qsLock,                                           \
                            _spinFlags);                                                                \
    }                                                                                                   \
    else  /* Exclusive access - no lock required */                                                     \
    {                                                                                                   \
        _st = ncp_task_v2_put_tOutput(_taskHdl,  _vpHdl, _taskMetaData, _taskAuxData, _wait);           \
    }                                                                                                   \
    _st; /* make function result available */                                                           \
})



#define NCP_NCA_LOWLEVEL_TASK_LEGACY_SEND(_taskHdl,  _vpHdl, _taskMetaData, _taskPduData, _taskAuxData, _wait) \
({                                                                                                      \
    ncp_st_t _st;                                                                                       \
    if ( (NCP_NCA_QS_SHARED == _taskHdl->pThreadQueueSet->qsAccessMode)                                 \
      && (FALSE == _taskHdl->pThreadQueueSet->sendMutexDisabled))                                       \
    {                                                                                                   \
        NCP_TASK_SPINLOCK_FLAGS_DECL;                                                                   \
        NCP_TASK_CLAIM_LOCK(_taskHdl->pThreadQueueSet->qsLock,                                          \
                            _spinFlags);                                                                \
        _st = ncp_task_v2_legacy_put_tOutput(_taskHdl,  _vpHdl, _taskMetaData, _taskPduData, _taskAuxData, _wait); \
        NCP_TASK_FREE_LOCK(_taskHdl->pThreadQueueSet->qsLock,                                           \
                            _spinFlags);                                                                \
    }                                                                                                   \
    else  /* Exclusive access - no lock required */                                                     \
    {                                                                                                   \
        _st = ncp_task_v2_legacy_put_tOutput(_taskHdl,  _vpHdl, _taskMetaData, _taskPduData, _taskAuxData, _wait); \
    }                                                                                                   \
    _st; /* make function result available */                                                           \
})

#define NCP_NCA_LOWLEVEL_TASK_LEGACY_SEND_SEGMENTS(_taskHdl,  _vpHdl, _taskMetaData, _taskAuxData, _taskData, _numSegs, _wait) \
({                                                                                                      \
    ncp_st_t _st;                                                                                       \
    if ( (NCP_NCA_QS_SHARED == _taskHdl->pThreadQueueSet->qsAccessMode)                                 \
      && (FALSE == _taskHdl->pThreadQueueSet->sendMutexDisabled))                                       \
    {                                                                                                   \
        NCP_TASK_SPINLOCK_FLAGS_DECL;                                                                   \
        NCP_TASK_CLAIM_LOCK(_taskHdl->pThreadQueueSet->qsLock,                                          \
                            _spinFlags);                                                                \
        _st = ncp_task_v2_nca_legacy_put_segments_tOutput(_taskHdl,  _vpHdl, _taskMetaData, _taskAuxData, _taskData, _numSegs, _wait); \
        NCP_TASK_FREE_LOCK(_taskHdl->pThreadQueueSet->qsLock,                                           \
                            _spinFlags);                                                                \
    }                                                                                                   \
    else  /* Exclusive access - no lock required */                                                     \
    {                                                                                                   \
        _st = ncp_task_v2_nca_legacy_put_segments_tOutput(_taskHdl,  _vpHdl, _taskMetaData, _taskAuxData, _taskData, _numSegs, _wait); \
    }                                                                                                   \
    _st; /* make function result available */                                                           \
})


#define NCP_NCA_LOWLEVEL_TASK_COMPLETION(_taskHdl, _pTask) \
({                                                                                                      \
    ncp_st_t _st;                                                                                       \
    if ( (NCP_NCA_QS_SHARED == _taskHdl->pThreadQueueSet->qsAccessMode)                                 \
      && (FALSE == _taskHdl->pThreadQueueSet->sendMutexDisabled))                                       \
    {                                                                                                   \
        NCP_TASK_SPINLOCK_FLAGS_DECL;                                                                   \
        NCP_TASK_CLAIM_LOCK(_taskHdl->pThreadQueueSet->qsLock,                                          \
                            _spinFlags);                                                                \
        _st = ncp_task_v2_put_completion(_taskHdl,  _pTask, TRUE);                                      \
        NCP_TASK_FREE_LOCK(_taskHdl->pThreadQueueSet->qsLock,                                           \
                            _spinFlags);                                                                \
    }                                                                                                   \
    else  /* Exclusive access - no lock required */                                                     \
    {                                                                                                   \
        _st = ncp_task_v2_put_completion(_taskHdl,  _pTask, TRUE);                                      \
    }                                                                                                   \
    _st; /* make function result available */                                                           \
})


#define NCP_NCA_LOWLEVEL_TASK_COMPLETION_PLUS_DEALLOC(_taskHdl, _pTask) \
({                                                                                                      \
    ncp_st_t _st;                                                                                       \
    if ( (NCP_NCA_QS_SHARED == _taskHdl->pThreadQueueSet->qsAccessMode)                                 \
      && (FALSE == _taskHdl->pThreadQueueSet->sendMutexDisabled))                                       \
    {                                                                                                   \
        NCP_TASK_SPINLOCK_FLAGS_DECL;                                                                   \
        NCP_TASK_CLAIM_LOCK(_taskHdl->pThreadQueueSet->qsLock,                                          \
                            _spinFlags);                                                                \
        _st = ncp_task_v2_put_completion_plus_deallocate(_taskHdl,  _pTask, TRUE);                      \
        NCP_TASK_FREE_LOCK(_taskHdl->pThreadQueueSet->qsLock,                                           \
                            _spinFlags);                                                                \
    }                                                                                                   \
    else  /* Exclusive access - no lock required */                                                     \
    {                                                                                                   \
        _st = ncp_task_v2_put_completion_plus_deallocate(_taskHdl,  _pTask, TRUE);                      \
    }                                                                                                   \
    _st; /* make function result available */                                                           \
})


#define NCP_NCA_LOWLEVEL_TASK_DEALLOC(_taskHdl, _pTask) \
({                                                                                                      \
    ncp_st_t _st;                                                                                       \
    if ( (NCP_NCA_QS_SHARED == _taskHdl->pThreadQueueSet->qsAccessMode)                                 \
      && (FALSE == _taskHdl->pThreadQueueSet->sendMutexDisabled))                                       \
    {                                                                                                   \
        NCP_TASK_SPINLOCK_FLAGS_DECL;                                                                   \
        NCP_TASK_CLAIM_LOCK(_taskHdl->pThreadQueueSet->qsLock,                                          \
                            _spinFlags);                                                                \
        _st = ncp_task_v2_put_task_deallocate(_taskHdl,  _pTask, TRUE);                                 \
        NCP_TASK_FREE_LOCK(_taskHdl->pThreadQueueSet->qsLock,                                           \
                            _spinFlags);                                                                \
    }                                                                                                   \
    else  /* Exclusive access - no lock required */                                                     \
    {                                                                                                   \
        _st = ncp_task_v2_put_task_deallocate(_taskHdl,  _pTask, TRUE);                                 \
    }                                                                                                   \
    _st; /* make function result available */                                                           \
})


#define NCP_NCA_LOWLEVEL_DEALLOC_IMMEDIATE(_taskHdl, _pDeallocImmediate, _wait) \
({                                                                                                      \
    ncp_st_t _st;                                                                                       \
    if ( (NCP_NCA_QS_SHARED == _taskHdl->pThreadQueueSet->qsAccessMode)                                 \
      && (FALSE == _taskHdl->pThreadQueueSet->sendMutexDisabled))                                       \
    {                                                                                                   \
        NCP_TASK_SPINLOCK_FLAGS_DECL;                                                                   \
        NCP_TASK_CLAIM_LOCK(_taskHdl->pThreadQueueSet->qsLock,                                          \
                            _spinFlags);                                                                \
        _st = ncp_task_v2_put_deallocate_immediate(_taskHdl,                                            \
                            (ncp_ncaV2_task_oPCQ_entry_dealloc_immediate_t *)_pDeallocImmediate,        \
                            _wait);                                                                     \
        NCP_TASK_FREE_LOCK(_taskHdl->pThreadQueueSet->qsLock,                                           \
                            _spinFlags);                                                                \
    }                                                                                                   \
    else  /* Exclusive access - no lock required */                                                     \
    {                                                                                                   \
        _st = ncp_task_v2_put_deallocate_immediate(_taskHdl,                                            \
                            (ncp_ncaV2_task_oPCQ_entry_dealloc_immediate_t *) _pDeallocImmediate,       \
                            _wait);                                                                     \
    }                                                                                                   \
    _st; /* make function result available */                                                           \
})


#define NCP_NCA_CHECK_TASK_INPUT_QUEUE(_taskHdl, _myRecvQueue, _task, _pBuffSizeBits ) \
            ncp_task_v2_check_input_queue(_taskHdl, _myRecvQueue, (ncp_task_ncaV2_recv_buf_t **)_task, _pBuffSizeBits)

#define NCP_TASK_FREE_SEND_BUFFERS(_p_oPCQ, _bulkFree) \
        ncp_task_v2_free_send_buffers(_p_oPCQ, _bulkFree)

ncp_st_t
ncp_dev_nca_put_tqs_tCompletion(ncp_nca_thread_queue_set_t *pThreadQueueSet,
                                ncp_task_recv_buf_t *task);

#ifdef NCP_DEV_SRIOEP
#ifndef FORCE_POLLING_MODE
#define FORCE_POLLING_MODE
#endif
#endif

#if 0 /* UBOOT */

#ifdef NCP_KERNEL

#define NCP_TASK_REGISTER_GROUP_INTERRUPTS(_dev, _activeGrpMask)

#define NCP_TASK_IRQ_WAIT(_dev, _type, _grp, _linearId) \
    ncp_dev_nca_wait_for_isr_wakeup(_dev, _type, _grp, (_linearId))
#else

#define NCP_TASK_REGISTER_GROUP_INTERRUPTS(_dev, _grpMask)  \
    if (ncp->rev.useInterrupts) {                           \
        ncp_task_register_grp_interrupts(_dev, _grpMask);  \
    }

#define NCP_TASK_IRQ_WAIT(_dev, _type, _grp, _linearId) \
    ncp_task_block_on_hw_interrupt(_dev, _type, _grp, (_linearId))

#endif


#define NCP_TASK_BLOCK_ON_INTERRUPT(_myTaskHdl, _dev, _type, _grp, _linearId) \
{ \
    NCA_DEC_CRITICAL_SECTION(_myTaskHdl);\
    if ((((ncp_t *)(_myTaskHdl->ncpHdl))->rev.useInterrupts) && FALSE == pNcpNcaV2_TaskSwState->inWarmRestart) \
    { \
        NCP_TASK_IRQ_WAIT(_dev, _type, _grp, (ncp_uint64_t)(_linearId));  \
    } \
    else \
    { \
        /* Must poll here since there is no interrupt handler registered at warm restart time */ \
        if (NCP_TASK_SLEEP_POLL)  \
        {  \
            ncp_sys_usleep(NCP_SLEEP_POLL_INTERVAL);  \
        } \
    } \
    NCA_INC_CRITICAL_SECTION(_myTaskHdl); \
}
#else
/*
 * UBOOT - Always poll
 */
#define NCP_TASK_BLOCK_ON_INTERRUPT(_myTaskHdl, _dev, _type, _grp, _linearId) \
{ \
    if (NCP_TASK_SLEEP_POLL)  \
    {  \
        ncp_sys_usleep(NCP_SLEEP_POLL_INTERVAL);  \
    } \
}
#endif /* UBOOT */

#ifdef NCP_KERNEL

#define NCP_TASK_INITIATE_SHUTDOWN(_dev)

#else /* NCP_KERNEL */

ncp_st_t ncp_task_initiate_shutdown(ncp_dev_hdl_t devHdl);

#define NCP_TASK_INITIATE_SHUTDOWN(_dev)   ncp_task_initiate_shutdown(_dev)

#endif /* NCP_KERNEL */

#if 0 /* UBOOT */
/*
 * Mutual exclusion
 */

#if defined(NCP_KERNEL) && !defined(NCP_VXWORKS) /* ======================= */

#ifndef NCP_LINUX
#define NCP_TASK_LOCK_FLAGS(_f)         spinlock_flags_t        _f = 0
#else   /*NCP_LINUX */
#define NCP_TASK_LOCK_FLAGS(_f)
#endif /* NCP_LINUX */

#define NCP_TASK_INIT_LOCK(_p, _s, _v)  NCP_SPINLOCK_INIT(_p)
#define NCP_TASK_DESTROY_LOCK(_p)
#define NCP_TASK_CLAIM_LOCK(_p, _f) \
{ \
    NCP_SPINLOCK_SW_INTERRUPT_DISABLE(_p, _f); \
}
#define NCP_TASK_FREE_LOCK(_p, _f) \
{ \
    NCP_SPINLOCK_SW_INTERRUPT_ENABLE(_p, _f); \
}

#else /* defined(NCP_KERNEL) && !defined(NCP_VXWORKS) ==================== */

#define NCP_TASK_LOCK_FLAGS(_f)
#define NCP_TASK_INIT_LOCK(_p, _s, _v)  ncp_sem_init(_p, _s, _v)
#define NCP_TASK_DESTROY_LOCK(_p)       ncp_sem_destroy(_p)
#define NCP_TASK_CLAIM_LOCK(_p, _f)                          \
{                                                            \
    ncp_sem_wait(_p);                                        \
}
#define NCP_TASK_FREE_LOCK(_p, _f)                           \
{                                                            \
    ncp_sem_post(_p);                                        \
}

#endif   /* ==================== defined(NCP_KERNEL) && !defined(NCP_VXWORKS) */
#else /* UBOOT */
/*
 * No locks needed for uboot
 */

#define NCP_TASK_LOCK_FLAGS(_f)
#define NCP_TASK_INIT_LOCK(_p, _s, _v)
#define NCP_TASK_DESTROY_LOCK(_p)
#define NCP_TASK_CLAIM_LOCK(_p, _f)
#define NCP_TASK_FREE_LOCK(_p, _f)
#endif /* UBOOT */

#if !defined(NCP_KERNEL) || defined(NCP_VXWORKS)

#define NCP_TASK_MEM_MMAP(_dev, _startVA,  _size, _physAddr) \
    NCP_MEM_MMAP(_dev, _startVA, _size, _physAddr)

#define NCP_TASK_MEM_UNMAP(_dev, _addr, _len) \
     NCP_USER_MEM_UNMAP(_addr, _len)

#else

#define NCP_TASK_MEM_MMAP(_dev, _startVA, _size, _physAddr) \
    NCP_DMA_MEM_MAP((((ncp_dev_t *)_dev)->num), _physAddr, _size)

#define NCP_TASK_MEM_UNMAP(_devNum, _addr, _len) \
     NCP_MEM_UNMAP((((ncp_dev_t *)_dev)->num), _addr)

#endif


#define NCP_TASK_V2_INIT_CPU_POOLS(_dev, _nca) \
        ncp_task_v2_init_cpu_pools(_dev, _nca)

extern ncp_st_t
ncp_task_config_kernel_mode_taskio(ncp_hdl_t ncpHdl,
                                   ncp_task_ncaV2_t *pSwState);

ncp_st_t
ncp_task_finish_kernel_mode_taskio(ncp_hdl_t ncpHdl,
                                   ncp_task_ncaV2_t *pSwState);
extern ncp_st_t
ncp_task_config_kernel_mode_domain_bundle(ncp_hdl_t ncpHdl);

#if defined(NCP_LINUX) && !defined(NCP_DEV_FBRS) && !defined(NCP_DEV_SOCKET)

#ifndef NCP_KERNEL
#define NCP_TASK_DO_KMODE_CFG_FOR_TASKIO(_ncpHdl, _pCfg) \
ncp_task_config_kernel_mode_taskio(_ncpHdl, _pCfg)

#define NCP_TASK_FINISH_KMODE_CFG_FOR_TASKIO(_ncpHdl, _pCfg) \
ncp_task_finish_kernel_mode_taskio(_ncpHdl, _pCfg)

#define NCP_TASK_NCAV2_CFG_KMODE_DOMAIN_BUNDLE(_ncpHdl) \
ncp_task_config_kernel_mode_domain_bundle(_ncpHdl)

#else
#define NCP_TASK_DO_KMODE_CFG_FOR_TASKIO(_ncpHdl, _pCfg) (NCP_ST_SUCCESS)
#define NCP_TASK_FINISH_KMODE_CFG_FOR_TASKIO(_ncpHdl, _pCfg) (NCP_ST_SUCCESS)
#define NCP_TASK_NCAV2_CFG_KMODE_DOMAIN_BUNDLE(_ncpHdl) (NCP_ST_SUCCESS)
#endif /* NCP_KERNEL */

#else
#define NCP_TASK_DO_KMODE_CFG_FOR_TASKIO(_ncpHdl, _pCfg) (NCP_ST_SUCCESS)
#define NCP_TASK_FINISH_KMODE_CFG_FOR_TASKIO(_ncpHdl, _pCfg) (NCP_ST_SUCCESS)
#define NCP_TASK_NCAV2_CFG_KMODE_DOMAIN_BUNDLE(_ncpHdl) (NCP_ST_SUCCESS)
#endif

#define NCP_TASK_LOWLEVEL_MEMCFG(_ncpHdl, _dev, _nca, _warmRestart) \
        ncp_task_v2_lowlevel_memcfg(_ncpHdl, _dev, _nca, _warmRestart)

#define NCP_TASK_V2_ALLOCATE_COMPLETION_DATA(_ncpHdl) \
        ncp_task_v2_allocate_completion_data(_ncpHdl)

#define NCP_TASK_V2_PROGRAM_XLAT_TABLES(_dev) \
ncp_task_v2_program_xlat_tables(_dev)

#define NCP_TASK_V2_ENABLE_ALL_POOLS(_dev, _ncpHdl) \
ncp_task_v2_enable_all_pools(_dev, _ncpHdl)

#define NCP_TASK_V2_ENABLE_RBP_BACKPRESSURE(_dev, _linear_iPCQ) \
ncp_task_v2_enable_rbp_backpressure(_dev, _linear_iPCQ)

#define NCP_TASK_V2_UNMAP_ALL_MEMORY_POOLS(_dev) \
ncp_task_v2_unmap_all_memory_pools(_dev)

#endif /* __ncp_task_pvt_funcs_hw_acp34xx_h__ */
