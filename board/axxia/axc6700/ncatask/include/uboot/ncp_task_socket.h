/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2017, Intel Corporation.                        *
 **                                                                       *
 **************************************************************************/

#ifndef __NCP_TASK_SOCKET_H__
#define __NCP_TASK_SOCKET_H__

#ifdef __cplusplus
extern "C" {
#endif

#define NCP_TASK_CACHE_PRELOAD      0
#define NCP_TASK_PREFETCH_CPUPOOL_FREELIST(_ptr)
#define NCP_TASK_PREFETCH_PGIT_FOR_WRITE(_pPgitPtr)
#define NCP_TASK_PREFETCH_PCQ_ENTRY(_InputQueueEntry)
#define NCP_TASK_PREFETCH_TASK_HEADER(_pTaskHeader)

#define NCP_TASK_TQS_DISABLE(_tqsId)                \
{                                                            \
    pNcpTaskSwState->tqsSwState[_tqsId].tqsEnabled = FALSE;  \
}
    
#define NCP_TASK_TQS_ENABLE(_tqsId)                 \
{                                                            \
    pNcpTaskSwState->tqsSwState[_tqsId].tqsEnabled = TRUE;   \
}

#define NCP_TASK_BUFFER_POOL_GET(_pvtTqsHdl, _pBuffer, _pBufferPoolId) \
 (NCP_ST_NOT_IMPLEMENTED)
 
#define NCP_TASK_BUFFER_ADDRESS_VALIDATE(_pvtTqsHdl, _pBuffer, _pBufferPoolId) \
 (NCP_ST_NOT_IMPLEMENTED)

#define NCP_TASK_BUFFER_SIZE_AND_START_GET(_pvtTqsHdl, _poolId, _pBuffer, _pBufferSize, _pBufferStart) \
 (NCP_ST_NOT_IMPLEMENTED)
 
#define NCP_TASK_BUFFER_SIZE_GET(_pvtTqsHdl, _poolId, _pBuffer, _pBufferSize) \
 (NCP_ST_NOT_IMPLEMENTED)
 
#define NCP_TASK_PUT_OPCQ(_pvtTqsHdl, _p_oPCQ, _pMetadata, _pSrcEntry) \
 (NCP_ST_NOT_IMPLEMENTED)

#define NCP_TASK_BLOCK_ON_INTERRUPT(_tqsHdl, _dev, _type, _tqsRelId, _tqsID)    \
{                                                                               \
 ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl = (ncp_task_pvt_tqsHdl_data_t *)_tqsHdl; \
 NCA_DEC_CRITICAL_SECTION(pvtTqsHdl);                                           \
 if (NCP_TASK_SLEEP_POLL)                                                       \
 {                                                                              \
      ncp_sys_usleep(NCP_SLEEP_POLL_INTERVAL);                                  \
 }                                                                              \
 NCA_INC_CRITICAL_SECTION(pvtTqsHdl);                                           \
}

#define NCP_TASK_DO_WAIT(_tqsHdl, _pWait, _dev, _tqsID) (NCP_ST_SUCCESS)
#define NCP_TASK_INITIATE_SHUTDOWN(_dev) (NCP_ST_SUCCESS)
#define NCP_TASK_DOMAIN_BUNDLE_ATTACH(_ncp, _pDomainBundle) (NCP_ST_SUCCESS)
#define NCP_TASK_DOMAIN_BUNDLE_DETACH(_ncp, _pDomainBundle) (NCP_ST_SUCCESS)

/* RWXXX #define NCP_MEM_MMAP(_dev, _startVA, _physAddr, _size) 0 */
/* RWXXX #define NCP_USER_MEM_UNMAP(_addr, _len)    */

#define NCP_TASK_MEM_MMAP(_dev, _startVA, _physAddr, _size) \
    NCP_MEM_MMAP(_dev, _startVA, _physAddr, _size)
#define NCP_TASK_MEM_UNMAP(_dev, _addr, _len) \
    NCP_USER_MEM_UNMAP(_addr, _len)   
 
 /* Mutual exclusion */    
#define NCP_TASK_LOCK_FLAGS(_f)

#define NCP_TASK_INIT_LOCK(_pMutex, _shared)    NCP_MUTEX_INIT(_pMutex, _shared)
#define NCP_TASK_DESTROY_LOCK(_pMutex)          NCP_MUTEX_DESTROY(_pMutex)
#define NCP_TASK_CLAIM_LOCK(_pMutex, _spinFlags, _pUnlockRequired)       NCP_MUTEX_LOCK(_pMutex, _pUnlockRequired)
#define NCP_TASK_FREE_LOCK(_pMutex,  _spinFlags,  _pUnlockRequired)      NCP_MUTEX_UNLOCK(_pMutex, _pUnlockRequired)


#define NCP_TASK_INIT_LOCK_HDL(_pMutex, _shared)        \
	NCP_MUTEX_INIT((_pMutex)->lock, _shared)
#define NCP_TASK_DESTROY_LOCK_HDL(_pMutex)	\
	NCP_MUTEX_DESTROY((_pMutex)->lock)
#define NCP_TASK_CLAIM_LOCK_HDL(_pMutex, _spinFlags, _pUnlockRequired) \
	NCP_MUTEX_LOCK((_pMutex)->lock, _pUnlockRequired)
#define NCP_TASK_FREE_LOCK_HDL(_pMutex,  _spinFlags,  _pUnlockRequired) \
	NCP_MUTEX_UNLOCK((_pMutex)->lock, _pUnlockRequired)
#ifdef __cplusplus
}
#endif
#endif /* __NCP_TASK_SOCKET_H__ */
