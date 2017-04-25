/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2017, Intel Corporation.                        *
 **                                                                       *
 **************************************************************************/

#ifndef __NCP_TASK_PVT_UMODE_H__
#define __NCP_TASK_PVT_UMODE_H__

#ifdef __cplusplus
extern "C" {
#endif 


extern 
ncp_st_t ncp_task_tqs_state_modify(ncp_dev_hdl_t devHdl,
                                   ncp_uint8_t grp,
                                   ncp_uint8_t tqsID,
                                   ncp_bool_t  disableTQS);
                                   
#define NCP_TASK_TQS_DISABLE(_tqsId)                   \
{                                                               \
    pNcpTaskSwState->tqsSwState[_tqsId].tqsEnabled = FALSE;     \
    ncp_task_tqs_state_modify(myDevHdl,                         \
                              0, /* grpId Not used for NcaV3 */ \
                              _tqsId,                           \
                              TRUE);                            \
}
    
#define NCP_TASK_TQS_ENABLE(_tqsId)                             \
{                                                               \
    pNcpTaskSwState->tqsSwState[_tqsId].tqsEnabled = TRUE;      \
    ncp_task_tqs_state_modify(myDevHdl,                          \
                              0, /* grpId Not used for NcaV3 */ \
                              _tqsId,                           \
                              FALSE);                           \
}

ncp_st_t ncp_task_initiate_shutdown(ncp_dev_hdl_t devHdl);
#define NCP_TASK_INITIATE_SHUTDOWN(_dev)   ncp_task_initiate_shutdown(_dev)
     
#define NCP_TASK_MEM_MMAP(_dev, _startVA,  _size, _physAddr) \
    NCP_MEM_MMAP(_dev, _startVA, _size, _physAddr)
#define NCP_TASK_MEM_UNMAP(_dev, _addr, _len) \
     NCP_USER_MEM_UNMAP(_addr, _len)
          
#define NCP_TASK_IRQ_WAIT(_dev, _type, _grp, _tqsRelId, _tqsID) \
    ncp_task_block_on_hw_interrupt(_dev, _type, _grp, _tqsRelId, _tqsID) 
    
/* Mutual exclusion */
#define NCP_TASK_LOCK_FLAGS(_f)

#define NCP_TASK_INIT_LOCK(_pMutex, _shared)    NCP_MUTEX_INIT(_pMutex, _shared)
#define NCP_TASK_DESTROY_LOCK(_pMutex)          NCP_MUTEX_DESTROY(_pMutex)
#define NCP_TASK_CLAIM_LOCK(_pMutex, _spinFlags, _pUnlockRequired)       NCP_MUTEX_LOCK(_pMutex, _pUnlockRequired)
#define NCP_TASK_FREE_LOCK(_pMutex,  _spinFlags,  _pUnlockRequired)      NCP_MUTEX_UNLOCK(_pMutex, _pUnlockRequired)

#define NCP_TASK_INIT_LOCK_HDL(_pMutex, _shared)        \
    NCP_MUTEX_INIT((_pMutex)->lock, _shared)
#define NCP_TASK_DESTROY_LOCK_HDL(_pMutex)      \
    NCP_MUTEX_DESTROY((_pMutex)->lock)
#define NCP_TASK_CLAIM_LOCK_HDL(_pMutex, _spinFlags, _pUnlockRequired)  \
    NCP_MUTEX_LOCK((_pMutex)->lock, _pUnlockRequired)
#define NCP_TASK_FREE_LOCK_HDL(_pMutex,  _spinFlags,  _pUnlockRequired) \
    NCP_MUTEX_UNLOCK((_pMutex)->lock, _pUnlockRequired)
/* =============== Start ARM_PMU wrappers =================== */
#ifdef NCP_NCA_ARM_PMU_PROFILING_ENABLED /* && defined(NCP_ARM_SKIP_DRIVER_PMU_ENABLE) */

ncp_st_t
ncpTaskArmPmuEnable(int *pNumCounters) ;
#define NCP_TASK_PMU_ENABLE() \
if (FALSE == pNcpTaskSwState->armPmuEnabled)                    \
{                                                               \
    if (NCP_ST_SUCCESS == ncpTaskArmPmuEnable((int *)(&pNcpTaskSwState->numPmuCounters)))    \
    { pNcpTaskSwState->armPmuEnabled = TRUE;  }                 \
}    

#else
#define NCP_TASK_PMU_ENABLE()
#endif    
/* =============== End ARM_PMU wrappers ===================== */

#ifdef __cplusplus
}
#endif
#endif /* __NCP_TASK_PVT_UMODE_H__ */ 
