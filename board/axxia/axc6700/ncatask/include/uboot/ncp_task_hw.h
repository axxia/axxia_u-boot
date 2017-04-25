/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                        *
 **                                                                       *
 **************************************************************************/

#ifndef __NCP_TASK_HW_H__
#define __NCP_TASK_HW_H__

#ifdef __cplusplus
extern "C" {
#endif

/* TODO - Add ARM 64bit preload macros */
#define NCP_TASK_CACHE_PRELOAD      1
#if (1 == NCP_TASK_CACHE_PRELOAD)
#define NCP_TASK_PREFETCH_CPUPOOL_FREELIST(_ptr)        arch_prefetch_data_for_write(_ptr)
#define NCP_TASK_PREFETCH_PGIT(_pgit)                   arch_prefetch_data((void *)_pgit)
#define NCP_TASK_PREFETCH_PGIT_FOR_WRITE(_pgit)         arch_prefetch_data_for_write((void *)_pgit)
#define NCP_TASK_PREFETCH_PCQ_ENTRY(_pQueueEntry)       arch_prefetch_data((void *)_pQueueEntry)
#define NCP_TASK_PREFETCH_PCQ_ENTRY_FOR_WRITE(_pQueueEntry)  arch_prefetch_data_for_write((void *)_pQueueEntry)
#define NCP_TASK_PREFETCH_TASK_HEADER(_pEntry)     arch_prefetch_data((void *)(_pEntry->taskAddress))
#else
#define NCP_TASK_PREFETCH_CPUPOOL_FREELIST(_ptr)
#define NCP_TASK_PREFETCH_PGIT(_pPgitPtr)               
#define NCP_TASK_PREFETCH_PGIT_FOR_WRITE(_pPgitPtr)     
#define NCP_TASK_PREFETCH_PCQ_ENTRY(_pQueueEntry)       
#define NCP_TASK_PREFETCH_PCQ_ENTRY_FOR_WRITE(_pQueueEntry)  
#define NCP_TASK_PREFETCH_TASK_HEADER(_pTaskHeader)     
#endif

ncp_st_t
_ncp_task_buffer_pool_get(
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
    void *pBuffer,
    ncp_uint8_t *pBufferPoolId);
    
#define NCP_TASK_BUFFER_POOL_GET(_pvtTqsHdl, _pBuffer, _pBufferPoolId) \
    _ncp_task_buffer_pool_get(_pvtTqsHdl, _pBuffer, _pBufferPoolId)

ncp_st_t
_ncp_task_buffer_address_validate(
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl,
    void *pBuffer,
    ncp_uint8_t poolId);

#define NCP_TASK_BUFFER_ADDRESS_VALIDATE(_pvtTqsHdl, _pBuffer, _poolId) \
    _ncp_task_buffer_address_validate(_pvtTqsHdl, _pBuffer, _poolId)

ncp_st_t
_ncp_task_buffer_size_and_start_get(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl, 
                                  ncp_uint8_t _poolId, 
                                  ncp_uintptr_t pBuffer, 
                                  ncp_uint32_t *pBufferSize, 
                                  void **pBufferStart);

#define NCP_TASK_BUFFER_SIZE_AND_START_GET(_pvtTqsHdl, _poolId, _pBuffer, _pBufferSize, _pBufferStart) \
    _ncp_task_buffer_size_and_start_get(_pvtTqsHdl, _poolId, (ncp_uintptr_t)_pBuffer, _pBufferSize, _pBufferStart)

ncp_st_t
_ncp_task_buffer_size_get(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl, 
                          ncp_uint8_t _poolId, 
                          ncp_uintptr_t pBuffer, 
                          ncp_uint32_t *pBufferSize);

#define NCP_TASK_BUFFER_SIZE_GET(_pvtTqsHdl, _poolId, _pBuffer, _pBufferSize) \
    _ncp_task_buffer_size_get(_pvtTqsHdl, _poolId, (ncp_uintptr_t)_pBuffer, _pBufferSize)

#define NCP_TASK_PUT_OPCQ(_pvtTqsHdl, _p_oPCQ, _pMetadata, _pSrcEntry) \
    ncp_task_put_opcq(_pvtTqsHdl, _p_oPCQ, _pMetadata, _pSrcEntry)

#define NCP_TASK_BLOCK_ON_INTERRUPT(_pvtTqsHdl, _dev, _type, _tqsRelId, _tqsID)                         \
{                                                                                                       \
    NCP_NCA_CRITICAL_SECTION_FLAG_DECL(critSecFlag)                                                     \
    if (_pvtTqsHdl->pTqs->tqsEnabled)                                                                   \
    {                                                                                                   \
        NCP_NCA_DEC_CRITICAL_SECTION(_pvtTqsHdl, critSecFlag);                                          \
        if ((((ncp_t *)(myNcpHdl))->rev.useInterrupts) && FALSE == pNcpTaskSwState->inWarmRestart)      \
        {                                                                                               \
            NCP_TASK_IRQ_WAIT(_dev,                                                                     \
                              _type,                                                                    \
                              0, /* _grp not used for XLF*/                                             \
                              _tqsRelId, /* tqsRelId instead of grpRelQueueId for XLF */                \
                              _tqsID);                                                                  \
        }                                                                                               \
        else                                                                                            \
        {                                                                                               \
            /* Must poll here since there is no interrupt handler registered at warm restart time */    \
            if (NCP_TASK_SLEEP_POLL)                                                                    \
            {                                                                                           \
                ncp_sys_usleep(NCP_SLEEP_POLL_INTERVAL);                                                \
            }                                                                                           \
        }                                                                                               \
        NCP_NCA_INC_CRITICAL_SECTION(_pvtTqsHdl, critSecFlag);                                          \
    }                                                                                                   \
    else                                                                                                \
    {                                                                                                   \
        NCP_CALL(NCP_ST_TASK_TQS_DISABLED);                                                             \
    }                                                                                                   \
}
 
#define NCP_TASK_RESET_POLL_STATE(_pWait)   \
    (_pWait)->pollInProgress = FALSE;       

#if 0
#define NCP_TASK_POLLTIME_EXPIRED(_pWait) \
    ncp_task_polltime_expired(_pvtTqsHdl, _pWait, _grp, _linearId);     
#endif

ncp_st_t
ncp_task_do_wait(ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl, 
                 ncp_task_wait_t *pWait, 
                 ncp_dev_hdl_t dev,
                 ncp_uint8_t   tqsID);
#define NCP_TASK_DO_WAIT(_tqsHdl, _pWait, _dev, _tqsID)  \
    ncp_task_do_wait(_tqsHdl, _pWait, _dev, _tqsID)
    
extern ncp_st_t ncp_task_mmap_attach(ncp_t *ncp, 
                                     void **pDomainBundle);
#define NCP_TASK_DOMAIN_BUNDLE_ATTACH(_ncp, _pDomainBundle) \
    ncp_task_mmap_attach(_ncp, _pDomainBundle)

extern ncp_st_t ncp_task_mmap_detach(ncp_t *ncp, 
                                     void *pDomainBundle);    
#define NCP_TASK_DOMAIN_BUNDLE_DETACH(_ncp, _pDomainBundle)  \
    ncp_task_mmap_detach(_ncp, _pDomainBundle)

/* RWXXX
#if defined(NCP_KERNEL) 
#include <ncp_task_pvt_kmode.h>
#else
#include <ncp_task_pvt_umode.h>
#endif
*/

#include "uboot/ncp_task_pvt_umode.h"

#ifdef __cplusplus
}
#endif
#endif /* __NCP_TASK_HW_H__ */
