/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2017, Intel Corporation.                        *
 **                                                                       *
 **************************************************************************/

#ifndef __NCP_TASK_PVT_H__
#define __NCP_TASK_PVT_H__

#ifdef __cplusplus
extern "C" {
#endif

#define NCP_INLINE static __inline__

#include "uboot/ncp_sal.h"
#include "uboot/ncp.h"
#include "uboot/ncp_pvt.h"
#include "uboot/ncp_task.h"
#include "uboot/ncp_ncav3.h"

#if !defined(NCP_KERNEL) && defined(NCP_NCA_ARM_PMU_PROFILING_ENABLED)
typedef struct {
    ncp_uint64_t cycles;
    ncp_uint8_t  ptrCnt;
    ncp_bool_t   combinedHeader;
}  ncp_update_task_pmu_results_t;  
#define NCP_MAX_PMU_RESULTS 20
#undef NCP_TASK_PROFILE_TXTASK_UPDATE
#undef NCP_TASK_PROFILE_RXTASK_UPDATE
#endif

#define NCP_TASK_RESTRICT_BULK_APIS 0
#define NCP_TASK_API_MAX_BULK_ITEM_COUNT 32 /* Sized to be equal to a max size oPCQ/iPCQ */

#define NCP_TASK_INITIAL_PID_LIMIT (2*1024); /* 2K */

#undef NCP_TASK_USE_BARRIER_FOR_TASK_RECV
/* if 0,  then use address dependency instead of full barrier (best performance - ARM only) */
#define NCP_TASK_USE_BARRIER_FOR_TASK_RECV 0 

#define NCP_TASK_FIXED_POOL_ID 31
#define NCP_TASK_FIXED_POOL_ENCODED_ID 1

/* #define NCP_NCA_CRITICAL_SECTION_TRACKING */
#undef NCP_NCA_CRITICAL_SECTION_TRACKING

#ifdef NCP_TASKIO_TBR_DISABLED
#define NCP_TASK_TBR_ENABLED 0 /* 1==ON */
#else
#define NCP_TASK_TBR_ENABLED 1 /* 1==ON */
#endif
#define NCP_TASK_NO_REFILL_CHECK_AT_HDL_UNBIND

#if (1 == NCP_TASK_TBR_ENABLED)
#ifdef NCP_TASKIO_CHECK_DISABLED
#undef NCP_TASK_TBR_VALIDATE_CURRENT_BUFFER_STATE
#else
#define NCP_TASK_TBR_VALIDATE_CURRENT_BUFFER_STATE
#endif
#endif /* NCP_TASK_TBR_ENABLED */

#define NCP_TASK_UNUSED_PARAM 0 
#define NCP_TASK_SLEEP_POLL 1

#undef NCP_TASK_DBG_SENDDONE
#define NCP_TASK_AUX_BUFF_FREE_THRESHOLD 8 /* 32 */

#ifdef NCP_TASKIO_CHECK_DISABLED
#define NCP_TASK_BUFFER_OVERRUN_CHECK_DISABLE                           
#define NCP_TASK_VALIDATE_OUTPUT_TASK_DISABLE   
#define NCP_TASK_VALIDATE_UNSCHEDULED_QUEUE_TASK_DISABLE
#define NCP_TASK_TBR_BUFFER_STATE_CHECK_DISABLE /* TODO: Not implemented yet */
#define NCP_TASK_SET_INCALLBACK_FLAG(_p, _id, _v) 
#else
#undef NCP_TASK_BUFFER_OVERRUN_CHECK_DISABLE                           
#undef NCP_TASK_VALIDATE_OUTPUT_TASK_DISABLE
#undef NCP_TASK_VALIDATE_UNSCHEDULED_QUEUE_TASK_DISABLE
#undef NCP_TASK_TBR_BUFFER_STATE_CHECK_DISABLE
#define NCP_TASK_SET_INCALLBACK_FLAG(_p, _id, _v) (_p)->inOpcqCallbackDoneFn[_id] = _v;   
#endif
  
/*
 * PMU data collection
 */
typedef struct {
    char         name[32];
    int          val[6];
    ncp_uint32_t cycle_count;
} ncpTaskArmPmuResults_t;

/* A structure that allows us greater freedom when accessing and initializing oPCQ entries */
typedef struct {
    union u {
        ncp_opcq_entry_t opcqEntry;
        ncp_uint64_t     opcqDword[2];
    } u;
} opcq_entry_overlay_t;
        
#ifdef NCP_KERNEL
typedef struct ncp_task_v3_mutex_krn_s {
    spinlock_t      lock;
    volatile ncp_bool_t exclusion;
} ncp_task_v3_mutex_t;
#else
typedef ncp_mutex_t      ncp_task_v3_mutex_t;
#endif
typedef struct ncp_task_v3_mutex_hdl_s {
    ncp_task_v3_mutex_t *lock;
    ncp_pid_t   pid;   /*!< owner process of mutex
                        *
                        * Mutex can be shared or private
                        * - If mutex is allocated private then it was allocated
                        * on heap of process who allocated it. Process id of
                        * that process is stored in this field.
                        * If mutex is shared then this field should be 0.
                        */
    ncp_mutex_attr_t flags; /*!< private flags for mutex
                             * 0x1 - private mutex
                             * 0x2 - robust mutex.
                             */
} ncp_task_v3_mutex_hdl_t;

#define NCP_TASK_V3_MUTEX_HDL_ALLOCATED(pMutex) \
    (NULL != (pMutex)->lock)

#define NCP_TASK_V3_MUTEX_HDL_PID(pMutex)       \
    (pMutex)->pid

#define NCP_TASK_V3_MUTEX_HDL_FLAGS(pMutex)     \
    (pMutex)->flags

#define NCP_TASK_V3_MUTEX_CLEAR(pMutex)                         \
    do {                                                        \
        (pMutex)->NCP_POINTER(lock) = NULL;                     \
        (pMutex)->pid = 0;                                      \
        (pMutex)->flags = NCP_MUTEX_PROCESS_SHARED_ROBUST;      \
    } while(0)

typedef enum ncp_task_block_sizes_e {
    TASK_BLOCK_SZ0 = 0,
    TASK_BLOCK_SZ1 = 1,
    TASK_BLOCK_SZ2,
    TASK_BLOCK_SZ3,
    TASK_BLOCK_SZ_UNKNOWN
} ncp_task_block_sizes_t;

#define NCP_TASK_A53_CACHE_LINE_MASK ~(64-1)
typedef struct ncp_task_cache_line_s 
{
  ncp_uint64_t unusedData[8];   /* 64 bytes, DWORD aligned */
} ncp_task_cache_line_t;   

/* queueset access mode, raw added to support taskIO lite */
typedef enum {
        NCP_NCA_QS_AVAILABLE=0,
        NCP_NCA_QS_EXCLUSIVE,
        NCP_NCA_QS_SHARED,
        NCP_NCA_QS_RAW
}  ncp_nca_qs_access_mode_t;

/* Wait profile support */

typedef enum {
    NCP_NCA_WAIT_FOR_RX_INTR=0,
    NCP_NCA_WAIT_FOR_RX_INTR_USING_WFI, 
    NCP_NCA_WAIT_FOR_TX0_INTR, 
    NCP_NCA_WAIT_FOR_TX1_INTR,     
    NCP_NCA_WAIT_FOR_ANY_INTR,
    NCP_NCA_WAIT_FOR_CFG_DMA_INTR,
    NCP_NCA_WAIT_NONE   /* Do not enter kernel */
} nca_wait_intr_types_e;
 
typedef struct ncp_task_wait_s {
      /* the profile */
      ncp_task_wait_profile_type_t  wait_profile;
      nca_wait_intr_types_e         isr_wait_type;         /* If entering kernel */
      ncp_uint32_t                  poll_timeout_value_us;
      ncp_task_poll_type_t          poll_type;
      ncp_uint32_t                  sleep_poll_value_us;
      /* Local state */
      ncp_bool_t                    pollInProgress;
      ncp_timespec_us_t             pollStartTime;
      ncp_timespec_us_t             pollEndTime;
      ncp_bool_t                    pollTimeWraps;  /* TODO - make sure to fix by 2038 :-) */    
      ncp_st_t                      pollTimeoutEC;
      ncp_uint32_t                  tqsRelId;       /* 1 if TXQ1 refill/free/send, all others are 0 */
} ncp_task_wait_t;  

/*
 * SEND DONE SUPPORT 
 */
 
typedef enum {
    NCP_TASK_NO_SEND_CALLBACK = 0,
    NCP_TASK_TASK_CALLBACK,
    NCP_TASK_BUFFER_CALLBACK,
} ncp_task_send_done_type_t;

typedef union {
    ncp_task_send_done_fn_t sendDoneFn;
    ncp_task_buffer_transfer_done_fn_t transferDoneFn;
} ncp_task_send_done_fn_union_t;

/* NCA Output Queue Aux Data - 1 per oPCQ entry - updated for each opcq put */
typedef struct ncp_task_per_oPCQ_aux_data_s
{
    struct ncp_task_pvt_tqsHdl_data_s  *sendDoneTqsHdl; /* != 0 is send done, else NOOP */
} ncp_task_per_oPCQ_aux_data_t;

typedef enum {
    NCP_TASK_QUEUE_TYPE_RSVD=0,
    NCP_TASK_QUEUE_TYPE_RXQ,
    NCP_TASK_QUEUE_TYPE_TXQ0,
    NCP_TASK_QUEUE_TYPE_TXQ1
} ncp_task_queue_type_t;

   
typedef struct iPCQ_info_s {
    ncp_ipcq_entry_t            *pIPCQentry; 
    ncp_ipcq_entry_t            *pPrefetchEntry1; /* one ahead */
    ncp_ipcq_entry_t            *pPrefetchEntry2; /* two ahead */    
    ncp_ipcq_entry_t            *pLastEntry;      /* wrap detection */
    ncp_uint32_t                numRxAvail; /* cached value */
    ncp_uint8_t                 appConsumerVal;  /* used for auto-deferred completion mode */    
    ncp_uint8_t                 appToggleBit;    /* used for auto-deferred completion mode */
    ncp_bool_t                  autoCompletionMode;
    ncp_bool_t                  autoConsumptionMode;
    ncp_uint32_t                numQueueGroupMappings;
    ncp_int32_t                 groupIndexes[NCP_NCAV3_NUM_QUEUE_GROUPS_PER_IPCQ]; /* Unpacked array. A value of -1 means unused */
    ncp_int32_t                 groupPriorities[NCP_NCAV3_NUM_QUEUE_GROUPS_PER_IPCQ];
} iPCQ_info_t;

typedef struct oPCQ_info_s {
    /* oPCQ housekeeping info */
    ncp_opcq_entry_t               *pOPCQentry; 
    ncp_opcq_entry_t               *pPrefetchEntry; /* one ahead */
    ncp_opcq_entry_t               *pLastEntry;     /* wrap detection */    
    ncp_uint32_t                   numTxAvail;      /* cached value */    
    ncp_uint32_t                   sendDoneCnt;
    ncp_uint32_t                   relId;           /* 0 or 1 */
    /* auxData housekeeping info */    
    ncp_uint32_t                   auxIdx;          /* next unprocessed idx */
    ncp_task_per_oPCQ_aux_data_t  *pAuxWriteEntry;  /* next entry to populate */             
    ncp_task_per_oPCQ_aux_data_t  *pAuxReadEntry;   /* next unprocessed entry */             
    ncp_task_per_oPCQ_aux_data_t  *pLastAuxEntry;   /* used for roll detection */             
    ncp_task_per_oPCQ_aux_data_t  *pBaseAuxEntry;   /* start of sw aux queue */                
} oPCQ_info_t;

typedef struct mPCQ_info_s {
    ncp_mpcq_entry_t              *pMPCQentry; 
    ncp_mpcq_entry_t              *pPrefetchEntry; /* one ahead */
    ncp_mpcq_entry_t              *pLastEntry;     /* wrap detection */        
    ncp_uint32_t                  numAvail;        /* optimizition   */
} mPCQ_info_t;

typedef union ncp_pcq_info_u {
    iPCQ_info_t ipcq_info;
    oPCQ_info_t opcq_info;
    mPCQ_info_t mpcq_info;
} ncp_pcq_info_t;


#define NCP_PCQ_TOGGLE_BIT       0x80
#define NCP_PCQ_TOGGLE_BIT_MASK  0x7F
#define NCP_PCQ_TOGGLE_BIT_SHIFT 0x7

#define NCP_TASK_PCQ_COOKIE 0x07620051
typedef struct ncp_task_pcq_s {
    ncp_task_cache_line_t       forceCacheIndependence;     
    ncp_uint32_t                cookie;                     
    ncp_uint32_t                nEntriesMinusOne;   /* used as a mask  */ 
    ncp_uint32_t                nEntriesMinusTwo;   /* used as a limit */    
    ncp_uint32_t                nEntriesDiv2;       /* optimizes memory barriers */          
    void                       *pPCQbase;       /* VA of entries[0] */
    volatile ncp_uint8_t       *pConsumerIdx;   /* ptr to PGIT */           
    volatile ncp_uint8_t       *pProducerIdx;   /* ptr to PGIT */              
    ncp_uint8_t                 hwProducerVal;          /* cached value - contains toggle bit */
    ncp_uint8_t                 hwConsumerVal;          /* cached value - contains toggle bit */    
    ncp_uint8_t                 toggleBit;     /* current value of bit 0bX000_0000 */      
    ncp_uint64_t                pcqRollCnt; 
    ncp_task_v3_mutex_hdl_t     qLock;
    ncp_bool_t                  shared;
    ncp_uint8_t                 nEntries;       /* queue depth */
    ncp_pcq_info_t              u;  /* varies by queue type */
} ncp_task_pcq_t;



/*
 * Stored in a per tqsHdl sendDone PCQ
 */

typedef struct 
{
    ncp_task_send_done_type_t type;
    ncp_task_send_done_fn_union_t callbackFn;
    void *sendDoneArg1; /* user-supplied argument to callback function */
    void *sendDoneArg2; /* send done: task header, txfer done: buf desc ptr */
    ncp_bool_t sendDoneArg3; /* txfer done: mrefBit */
    ncp_uint8_t sendDoneArg4; /* txfer done: poolId */
} ncp_task_sendDone_entry_t;

typedef struct ncp_task_pvt_sendDone_ctl_s {
   volatile ncp_uint8_t            pIdx;
   volatile ncp_uint8_t            cIdx;   
   ncp_uint8_t                     pendingIdx;
   ncp_uint8_t                     nEntriesMinusOne;
   ncp_bool_t                      sendDonePending;
   ncp_task_sendDone_entry_t *currFillEntry;
   ncp_task_sendDone_entry_t *currPendingEntry;   
   ncp_task_sendDone_entry_t *entries;
}  ncp_task_pvt_sendDone_ctl_t;   


typedef struct ncp_task_tqs_share_ctl_s { 
ncp_task_tqs_shared_t   shareFlags;
ncp_uint32_t            rxQ_useCnt;
ncp_uint32_t            txQ0_useCnt;
ncp_uint32_t            txQ1_useCnt;
ncp_uint32_t            allocatorUseCnt[NCP_NCAV3_MAX_SHARED_POOLS];
} ncp_task_tqs_share_ctl_t;
    

/**********************************************************************
 * Memory pool structures
 **********************************************************************/
    
typedef struct ncp_task_mme_allocator_s
{
    ncp_int32_t         id;
    ncp_bool_t          valid;     /* is pool configured for this tqs?  */ 
    ncp_bool_t          shared;
    ncp_int32_t         useCnt;
    ncp_task_pcq_t      mPCQ[4];  /* NcaV3 MME uses real PCQs for allocation */
    ncp_task_v3_mutex_hdl_t mmeLock; /*shared queue mutex*/
} ncp_task_mme_allocator_t;


#define NCP_POOL_KEY 0xCAFEBEEF
typedef struct ncp_buffDescriptor_s
{
    struct ncp_buffDescriptor_s *next;
} ncp_buffDescriptor_t;

typedef struct {
    void                 *VAstart;
    void                 *VAend;
    ncp_uint32_t          size;
    ncp_buffDescriptor_t *free;
    ncp_buffDescriptor_t *last;
    ncp_uint32_t          numFree;
    ncp_uint32_t          freeLowWaterMark;
    ncp_uintptr_t         mask;
} ncp_task_bufflist_t;

typedef struct {
    ncp_dev_hdl_t       devHdl;
    ncp_bool_t          ncaSupplyDone;
#if (1 == NCP_TASK_TBR_ENABLED)   
    ncp_bool_t          inCpuPoolRecovery;          /* cpu pool is being recovered */
    struct ncp_task_tqs_swState_s *pCpuPoolTQSets;  /* list of all TQSets that reference this pool,   even if not bound */
#endif    
    ncp_task_bufflist_t buffListArray[NCP_TASK_NUM_BUFF_SIZES];
} ncp_task_cpu_managed_buffer_pool_t;

typedef struct {
    /* Add mPCQ allocators here? */
} ncp_task_vp_managed_buffer_pool_t;

typedef union ncp_task_pool_types_union_u
{
    ncp_task_cpu_managed_buffer_pool_t cpu;
    ncp_task_vp_managed_buffer_pool_t  vp;
} ncp_task_pool_types_union_t;

/* typedef ncp_uint64_t ncp_pid_t;  */
typedef struct runtime_mutex_attr_state_s {
    ncp_mutex_attr_t attr;
    ncp_pid_t pid;
} runtime_mutex_attr_state_t;


typedef struct {
    ncp_task_cache_line_t    forceCacheIndependence;    
    ncp_task_resource_name_t name;
    ncp_bool_t        valid;
    ncp_uint32_t      poolKey;
    ncp_int32_t       poolId;
    ncp_bool_t        isCpuManagedPool;    /* CPU or VP/MME managed? */
    ncp_bool_t        disabledForReinit;
    ncp_uint32_t      poolUseCnt;          /* actively using the pool */
    ncp_bool_t        exclusiveUse;        /* no locks! */
    ncp_task_v3_mutex_hdl_t poolLock;      /* global lock for *this* pool */
    ncp_task_pool_types_union_t u;
    /* Begin - From ASE config */
    ncp_uint64_t      poolPA;
    ncp_uint64_t      poolSize;
    ncp_uintptr_t     poolVA;
    ncp_uintptr_t     poolVAEnd;
    ncp_uint64_t      poolMaxDynamic;
    ncp_bool_t        uMode;
    ncp_uintptr_t     blocksVA[NCP_TASK_NUM_BUFF_SIZES];
    ncp_uintptr_t     blocksVAend[NCP_TASK_NUM_BUFF_SIZES];
    ncp_uint64_t      blocksPA[NCP_TASK_NUM_BUFF_SIZES];
    int               numBlocks[NCP_TASK_NUM_BUFF_SIZES];
    int               numBlocksForNCA[NCP_TASK_NUM_BUFF_SIZES];
    /* End - From ASE */
#if (1 == NCP_TASK_TBR_ENABLED)
    ncp_uint64_t           numTbrEntries[NCP_TASK_NUM_BUFF_SIZES];
    ncp_bool_t             tbrArraysInitialized;
    volatile ncp_task_pid_t  *pTbrArray[NCP_TASK_NUM_BUFF_SIZES];
#endif      
    runtime_mutex_attr_state_t mtxAttr;
} ncp_task_pool_t;

/**********************************************************************
 * Task I/O Domain Bundle 
 **********************************************************************/
typedef struct ncp_task_domain_bundle_s {
    /* 
     * The domain bundle contains all hw structs (queues,pgits,...)
     * used by this domain, and does not need to be fixed to any 
     * particular VA 
     */    
    ncp_uint64_t                        domainBundle_PA;    
    ncp_uintptr_t                       domainBundle_VA;
    ncp_uint64_t                        domainBundle_Size;  
} ncp_task_domain_bundle_t;

/**********************************************************************
 * Task I/O State
 **********************************************************************/

#define NCP_TASK_TQS_SWSTATE_COOKIE 0x07620039
typedef struct ncp_task_tqs_swState_s {
  ncp_task_cache_line_t    forceCacheIndependence;
  ncp_uint32_t             cookie;

  /***************************************************************/
  /*** The following members are maintained only in the kernel ***/
  /***************************************************************/
  /* Kernel-mode task I/O can reconfigure the TQS and change 'configured', so
   * it must be centralized in the kernel. 'domainId' shouldn't ever change,
   * but it's included just to be safe.
   */
  ncp_bool_t               configured;
  ncp_uint32_t             domainId;

  /* 'name' and 'mqg' are mainted in the kernel because they can be read
   * (via getter functions) without a TQS being bound. The members that
   * depend on a TQS being bound, or that are required in the task I/O
   * datapath, are maintained TQS's uMode's space.
   */
  ncp_task_resource_name_t name;
  ncp_int32_t              mqg;

  /***********************************************************************/
  /*** The following members are maintained in the kernel and, if the  ***/
  /*** TQS's uMode is TRUE, user-space.                                ***/
  /***********************************************************************/
  ncp_ncav3_application_profile_t *pAppProfile;
  ncp_bool_t               tqsEnabled;

  /***********************************************************************/
  /*** The following members are maintained in the TQS's space         ***/
  /*** (either user or kernel).                                        ***/
  /***********************************************************************/
  ncp_bool_t               staticConfiguration;
  ncp_int32_t              tqsId;
  ncp_int32_t              coreId;
  ncp_uint32_t             tqsUseCnt;
  ncp_task_tqs_share_ctl_t shareCtl;
  ncp_uint32_t             validPoolsMask;
  ncp_uint32_t             cpuPoolId;
  ncp_int32_t              profileId;
  void                     *pCpuPgit;
  void                     *pNcaPgit;
  ncp_task_pcq_t           rxQ;
  ncp_task_pcq_t           txQ0;
  ncp_task_pcq_t           txQ1;
  ncp_task_cache_line_t    forceCacheIndependence2;
  ncp_task_mme_allocator_t mmeAllocator[8]; /* only pools 2-7 really used here */
#if (1 == NCP_TASK_TBR_ENABLED)
  ncp_bool_t               inTqsRecovery;
  ncp_int32_t              tqsRefillsOwed[NCP_TASK_NUM_BUFF_SIZES];       /* Must be signed */
  struct ncp_task_tqs_swState_s *pNextCpuPoolTqs; /* used if CPU pool */
#endif
  struct ncp_task_pvt_tqsHdl_data_s *clientTqsHdls;
  ncp_task_stats_t         taskStats;       /* TQS-local statistics */
  runtime_mutex_attr_state_t  mtxAttr;
} ncp_task_tqs_swState_t;

typedef struct {
    ncp_bool_t useRxQueue;
    ncp_bool_t useTxQueue[2]; /* TXQ_0 and TXQ_1 */
    ncp_bool_t useAllocator[NCP_NCAV3_MAX_SHARED_POOLS];
} ncp_task_pvt_tqs_usage_t;

typedef enum {
NCP_TASK_THREAD_RUNNING=0,
NCP_TASK_THREAD_NEEDS_CLEANUP,   /* awaiting unbind and associated cleanup (free buffers, issue completions, ... ) */
NCP_TASK_THREAD_CLEANUP_DONE     /* application notified, cleanup done, and unbind done. Note: if cpu pool - all users must cleanup */
} ncp_task_execution_state_e;

typedef struct ncp_task_thread_info_s {
    struct ncp_task_thread_info_s   *pNextThread;
    struct ncp_task_process_info_s  *pParentProcess;
    ncp_uint32_t                    tqsId;              /* TQS contains pools mask */
    ncp_task_execution_state_e      executionState;
    struct ncp_task_pvt_tqsHdl_data_s *recoveryTqsHdl;   
    ncp_task_resource_name_t        clientThread;
} ncp_task_thread_info_t;

typedef struct ncp_task_process_info_s {
    struct ncp_task_process_info_s  *pNextProcess;
    ncp_uint32_t                    numThreads;         /* same as old global, myProcessIdUseCnt */
    ncp_uint32_t                    poolsMask;          /* same as old global, myPidPoolsMask */
    ncp_task_thread_info_t          *activeThreads;
    ncp_task_pid_t                  pid;                /* same as old global, myProcessId - not linux pid! - used for TBR state tracking */
    ncp_pid_t                       osPid;              /* used for user mode only - is real linux pid - do not confuse with pid above!   */
    ncp_bool_t                      inProcessRecovery;
    ncp_task_resource_name_t        clientProcess;
} ncp_task_process_info_t;

#define NCP_TASK_TQS_HDL_COOKIE 0x05560045
typedef struct ncp_task_pvt_tqsHdl_data_s 
{
  ncp_task_cache_line_t    forceCacheIndependence; 
  ncp_uint32_t             cookie;
  ncp_uint32_t             tqsId;
  ncp_task_execution_state_e  executionState;
  ncp_task_process_info_t  *pProcess;        /* pointer to process struct */
  ncp_task_thread_info_t   thisThread;       /* not indirect */
  ncp_uint32_t             mappedPools;
  ncp_uint32_t             cpuPoolId;  
  ncp_task_pool_t         *cpuPoolHdl;
#if (1 == NCP_TASK_TBR_ENABLED)  
  ncp_int32_t              perHdlRefillsOwed[NCP_TASK_NUM_BUFF_SIZES];      /* hdl level accounting */
  ncp_int32_t              perHdlRefillsIssued[NCP_NCAV3_NUM_OPCQS_PER_TQS][NCP_TASK_NUM_BUFF_SIZES]; /* hdl level separate accounting for TXQ0 and TXQ1 */     
#endif    
#if !defined(NCP_TASKIO_CHECK_DISABLED)
  ncp_bool_t               inOpcqCallbackDoneFn[2]; /* Tracked separately for both oPCQs in the TQS */
#endif  
  ncp_uint32_t             inCriticalSection;
  ncp_uint64_t             completionsOwed;      /* used for manual completion mode */
  ncp_uint64_t             completionsIssued[NCP_NCAV3_NUM_OPCQS_PER_TQS]; /* used for manual completion mode */
  ncp_uint32_t             consumptionsOwed;    /* used for deferred consumption mode */  
  ncp_task_pid_t           pid;
  ncp_task_tqs_swState_t   *pTqs;               /* pointer to tqs sw state */
  opcq_entry_overlay_t     taskSendDefaultCmdBits;         /* Optimization */
  opcq_entry_overlay_t     taskBufferFreeDefaultCmdBits;   /* Optimization */
  opcq_entry_overlay_t     taskFreeDefaultCmdBits;         /* Optimization */
  opcq_entry_overlay_t     taskCompleteDefaultCmdBits;     /* Optimization */ 
  ncp_task_pvt_tqs_usage_t  useFlags;  
  ncp_bool_t               *pTqsEnabled;
  ncp_task_pvt_sendDone_ctl_t  sendDoneInfo[NCP_NCAV3_NUM_OPCQS_PER_TQS];  
  ncp_task_wait_t          waitProfile[NCP_TASK_API_CLASS_FREE_TXQ1+1];
  struct ncp_task_pvt_tqsHdl_data_s *nextTqsHdl;           /* global "active" list */
  struct ncp_task_pvt_tqsHdl_data_s *nextClientTqsHdl;     /* per tqs list */
} ncp_task_pvt_tqsHdl_data_t;

typedef struct ncp_ncav3_nca_queue_state_s {
    ncp_task_resource_name_t name;
    ncp_int32_t tqId;
    ncp_bool_t  enabled;
    ncp_int32_t priority;
    ncp_int32_t wrrWeight;
    ncp_bool_t  traceEnabled;
    ncp_int32_t queueProfileId;
    ncp_ncav3_nca_queue_profile_t *profile;
    ncp_int32_t groupId;
    ncp_bool_t orderedFullBP;
    ncp_bool_t unorderedFullBP;
    ncp_bool_t bcamFullBP;
    ncp_bool_t bcamAFullBP;
    struct ncp_ncav3_nca_queue_state_s *next;
} ncp_ncav3_nca_queue_state_t;

typedef struct {
    ncp_bool_t enabled;
    ncp_int32_t groupId;
    ncp_ncav3_recv_queue_type_t queueType;
    ncp_task_resource_name_t name;
    ncp_ncav3_nca_queue_state_t *groupMembers;
    ncp_bitmap_t *tqsBitmap; /* iPCQs fed by the group */
} ncp_ncav3_nca_queue_group_t;

typedef struct {
    ncp_uint32_t regionId;
    ncp_uint32_t size;
    ncp_uint64_t virtualBase;
    ncp_uint64_t physicalBase;
    ncp_task_resource_name_t name;
} ncp_ncav3_shared_region_t;

typedef struct {
    ncp_uint32_t size;
    ncp_uint64_t virtualBase;
    ncp_uint64_t physicalBase;
    ncp_task_resource_name_t name;
    ncp_bool_t valid;
} ncp_ncav3_fixed_pool_t;

struct ncp_ncav3_hdl_s;

#define NCP_TASK_STATE_COOKIE 0x6A6EEAD5
typedef struct {
    ncp_uint64_t                cookie;
    ncp_uint32_t                inCriticalSection;
    ncp_bool_t                  uMode; 
    ncp_uint32_t                domainId; 
    ncp_bool_t                  inWarmRestart;  
    ncp_t                       *ncp;
    struct ncp_ncav3_hdl_s      *nca;
    ncp_task_domain_bundle_t    domainMemMap;
    ncp_task_pool_t             taskPools[NCP_NCAV3_NUM_TASK_MEMORY_POOLS];
    ncp_task_v3_mutex_t         *taskIoResourceLock;
    ncp_task_tqs_swState_t      tqsSwState[NCP_NCAV3_MAX_NUM_TQSETS];
    ncp_uint32_t                numNcaQueues;
    ncp_ncav3_nca_queue_state_t ncaQueueState[NCP_NCAV3_MAX_NUM_NCAQS];
    ncp_uint32_t                numQueueGroups;
    ncp_ncav3_nca_queue_group_t queueGroups[NCP_NCAV3_MAX_NUM_QUEUE_GROUPS];
    ncp_uint32_t                numSharedDataRegions;
    ncp_ncav3_shared_region_t   *sharedDataRegions;
    ncp_ncav3_fixed_pool_t      fixedPoolInfo;
    ncp_uint32_t                perDomainPoolsMask;
    ncp_uint32_t                currPidArrayEntries;
    ncp_uint32_t                numActivePids;
    ncp_uint64_t                activeTQSMask;
    ncp_task_process_info_t     **pidArray;
    ncp_task_process_info_t     *activeProcesses; 
    ncp_task_pvt_tqsHdl_data_t  *activeTqsHdls;   
    ncp_task_global_stats_t     taskStats;       /* global statistics */ 
#ifdef NCP_NCA_ARM_PMU_PROFILING_ENABLED
    ncp_bool_t                  armPmuEnabled;   
    int                         numPmuCounters;
#endif    
    ncp_bool_t                  domainIsInternal;
} ncp_task_swState_t;

/**********************************************************************
 * NCA Handle
 **********************************************************************/
#define NCP_NCA_HDL_COOKIE 0xBAB1F00D
typedef struct ncp_ncav3_hdl_s {
    ncp_uint32_t             cookie;
    ncp_task_swState_t      *taskSwState;
    ncp_ncav3_tqs_control_t *tqsArray;
    ncp_ncav3_config_info_t  configInfo;
    /* Used to assert that certain functions are only called at config-time */
    ncp_bool_t               inConfigurationPhase;
} ncp_ncav3_hdl_t;

/**********************************************************************
 * Miscellaneous macros
 **********************************************************************/

#define NCP_OPCQ_SYSMEM_BARRIER() NCP_SYSMEM_STORE_BARRIER()  

#define NCP_TASK_PPROCESS_DECL(_pProcess) \
    ncp_task_process_info_t *_pProcess;
    
/*
 * Critical Section Mgmt
 * NOTE: It is important that the critical-section state be entered as early as possible after API entry 
 * and exited as late as possible (just before API exit).   Regardless of how innocuous the API,   if the 
 * RTE faults during API execution it is likely that the system is not in a stable state.   Unexpected
 * faults in seemingly safe APIs or code chunks may be an indicator that data structures have been corrupted.
 * For this reason we set the critical section flag for *all* APIs,   even if all they are doing is a resource lookup.
 */

#if (1 == NCP_TASK_TBR_ENABLED)
#define NCP_NCA_CRITICAL_SECTION_TRACKING
#else
#undef  NCP_NCA_CRITICAL_SECTION_TRACKING
#endif

#ifdef NCP_NCA_CRITICAL_SECTION_TRACKING
#define NCP_NCA_CRITICAL_SECTION_FLAG_DECL(_critSecFlag) ncp_bool_t _critSecFlag=FALSE;
#define NCP_NCA_INC_CRITICAL_SECTION(_pvtTqsHdl, _critSecFlag)\
{                                           \
    if (pNcpTaskSwState && _pvtTqsHdl)      \
    {                                       \
        (_pvtTqsHdl)->inCriticalSection++;  \
        _critSecFlag = TRUE;                \
    }                                       \
}

#define NCP_NCA_TEST_CRITICAL_SECTION(_val, _expectedVal)   \
({ ncp_bool_t _ret=TRUE;                                    \
   if (_expectedVal != _val)                                \
   { _ret = FALSE; }                                        \
   _ret;                                                    \
})

#define NCP_NCA_DEC_CRITICAL_SECTION(_pvtTqsHdl, _critSecFlag)\
{                                           \
    if (_critSecFlag && _pvtTqsHdl)         \
    {                                       \
        (_pvtTqsHdl)->inCriticalSection--;  \
        _critSecFlag = FALSE;               \
    }                                       \
}
#define NCP_NCA_INC_GLOBAL_CRITICAL_SECTION(_critSecFlag)   \
{                                           \
    if (pNcpTaskSwState)                    \
    {                                       \
        (pNcpTaskSwState)->inCriticalSection++;  \
        _critSecFlag = TRUE;                \
    }                                       \
}
    
#define NCP_NCA_DEC_GLOBAL_CRITICAL_SECTION(_critSecFlag)   \
{                                           \
    if (_critSecFlag)                       \
    {                                       \
        (pNcpTaskSwState)->inCriticalSection--;  \
        _critSecFlag = FALSE;               \
    }                                       \
}
#else
#define NCP_NCA_CRITICAL_SECTION_FLAG_DECL(_critSecFlag)
#define NCP_NCA_GLOBAL_CRITICAL_SECTION_FLAG_DECL(_critSecFlag)
#define NCP_NCA_INC_CRITICAL_SECTION(_pvtTqsHdl, _critSecFlag)
#define NCP_NCA_DEC_CRITICAL_SECTION(_pvtTqsHdl, _critSecFlag)
#define NCP_NCA_INC_GLOBAL_CRITICAL_SECTION(_critSecFlag)
#define NCP_NCA_DEC_GLOBAL_CRITICAL_SECTION(_critSecFlag)
#define NCP_NCA_TEST_CRITICAL_SECTION(_val, _expectedVal)  FALSE
#endif

#if (1 == NCP_TASK_TBR_ENABLED)

typedef struct ncp_task_tbr_params_s {
    ncp_task_pid_t  *statePtrArray[7];
    ncp_bool_t      mrefBitArray[7];
    ncp_task_pid_t  **pPtrs;    
    ncp_uint32_t    ptrCnt; 
    ncp_task_pid_t  expectedState;            
    ncp_task_pid_t  newState;
    ncp_int32_t   *pRefillsIssued;       
} ncp_task_tbr_params_t;
        
#define NCP_TASK_TBR_STATE_PTRS_DECL()         \
    ncp_task_tbr_params_t tbr; \
    ncp_task_tbr_params_t *pTbr=&tbr;           

#define NCP_TASK_TBR_STATE_PTRS_INIT()      \
    tbr.ptrCnt = 0;                         \
    tbr.pPtrs = &tbr.statePtrArray[0];
    
#define NCP_TASK_INITIALIZE_TBR_ARRAYS() \
    NCP_CALL(ncp_task_initialize_tbr_arrays()) 
    
#define NCP_TASK_DECREMENT_POOL_USE_COUNTS(_pvtTqsHdl) \
    NCP_CALL(ncp_task_decrement_pool_use_counts(_pvtTqsHdl))

#define NCP_TASK_INCREMENT_POOL_USE_COUNTS(_pvtTqsHdl) \
    ncp_task_increment_pool_use_counts(_pvtTqsHdl)
    
#define NCP_TASK_TBR_TQS_IN_RECOVERY_CLEAR(_ncpHdl, _pTqs)  \
{                                               \
    if (_pTqs->inTqsRecovery)                   \
    {                                           \
        NCP_TASK_TQS_ENABLE(_pTqs->tqsId);      \
        _pTqs->inTqsRecovery = FALSE;           \
    }                                           \
}    
    
#define NCP_TASK_TBR_CPU_POOL_RECOVERY_CLEAR(_poolId) \
    NCP_CALL(ncp_task_tbr_cpu_pool_recovery_clear(_poolId))
                    
#define NCP_TASK_TBR_GLOBAL_POOL_REFILL_RECOVERY(_pvtTqsHdl) \
    NCP_CALL(ncp_task_tbr_global_pool_refill_recovery(_pvtTqsHdl))

#define NCP_TASK_TBR_UNBIND_THREADS(_pProcess)          \
{                                                       \
    NCP_CALL(ncp_task_tbr_unbind_threads(_pProcess));   \
}    

    
#define NCP_TASK_TBR_INITIATE_RECOVERY(_pProcess, _pNcpStatus)  \
{                                                               \
    ncp_st_t _tmpStat;                                          \
    if (NCP_ST_SUCCESS != (_tmpStat = ncp_task_tbr_initiate_recovery(_pProcess))) \
    {                                                           \
        /* override RESTART_DRTECTED only if recovery failed */ \
        *(_pNcpStatus) = _tmpStat;                              \
    }                                                           \
}                                                               \

#define NCP_TASK_TBR_ADD_TO_CPUPOOL_TQS_LIST(_poolId, _pTqs)    \
{                                                               \
    ncp_task_pool_t *_pPool;                                    \
                                                                \
    _pPool = &pNcpTaskSwState->taskPools[_poolId];              \
    _pTqs->pNextCpuPoolTqs = _pPool->u.cpu.pCpuPoolTQSets;      \
    _pPool->u.cpu.pCpuPoolTQSets = _pTqs;                       \
}

#define NCP_TASK_TBR_REMOVE_FROM_CPUPOOL_TQS_LIST(_tqsHdl) \
    NCP_CALL(ncp_task_tbr_remove_from_cpupool_tqs_list(_tqsHdl))
 
#ifndef NCP_TASK_NO_REFILL_CHECK_AT_HDL_UNBIND    
#define NCP_TASK_TBR_THREAD_RX_REFILL_CHECK(_pvtTqsHdl)                                                                                     \
({                                                                                                                                          \
    ncp_st_t _st=NCP_ST_SUCCESS;                                                                                                            \
    ncp_int32_t _refillsIssued[NCP_TASK_NUM_BUFF_SIZES] = {0,0,0,0};                                                                        \
                                                                                                                                            \
    refillsIssued[0] = _pvtTqsHdl->perHdlRefillsIssued[NCP_TASK_TXQ_0][0]                                                                      \
                     + _pvtTqsHdl->perHdlRefillsIssued[NCP_TASK_TXQ_1][0];                                                                     \
    refillsIssued[1] = _pvtTqsHdl->perHdlRefillsIssued[NCP_TASK_TXQ_0][1]                                                                      \
                     + _pvtTqsHdl->perHdlRefillsIssued[NCP_TASK_TXQ_1][1];                                                                     \
    refillsIssued[2] = _pvtTqsHdl->perHdlRefillsIssued[NCP_TASK_TXQ_0][2]                                                                      \
                     + _pvtTqsHdl->perHdlRefillsIssued[NCP_TASK_TXQ_1][2];                                                                     \
    refillsIssued[3] = _pvtTqsHdl->perHdlRefillsIssued[NCP_TASK_TXQ_0][3]                                                                      \
                     + _pvtTqsHdl->perHdlRefillsIssued[NCP_TASK_TXQ_1][3];                                                                     \
    if ((_pvtTqsHdl->perHdlRefillsOwed[0] != refillsIssued[0]))                                                                             \
        || ((_pvtTqsHdl->perHdlRefillsOwed[1]) != refillsIssued[1])                                                                         \
        || ((_pvtTqsHdl->perHdlRefillsOwed[2]) != refillsIssued[2])                                                                         \
        || ((_pvtTqsHdl->perHdlRefillsOwed[3]) != refillsIssued[3])                                                                         \
    {                                                                                                                                       \
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca, ncp_xlf_task_tbr_thread_rx_refill_check_attemptingToUnbindWhenRefillsAreOwed, NCP_MSG_ERROR, \
                "Process %s (pid=%d) Thread %s is attempting to unbind when buffer refills are owed to the NCAV3 hardware\r\n",             \
                _pvtTqsHdl->pProcess->clientProcess.name,                                                                                   \
                _pvtTqsHdl->pProcess->pid,                                                                                                  \
                _pvtTqsHdl->thisThread.clientThread.name);                                                                                  \
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca, ncp_xlf_task_tbr_thread_rx_refill_check_256bBuffersOwedIssued, NCP_MSG_ERROR,            \
                              "Pool %d: Total 256B buffers owed=%d, issued=%d\r\n",  (int)_pvtTqsHdl->cpuPoolId,                            \
                              (int)_pvtTqsHdl->perHdlRefillsOwed[0],                                                                        \
                              (int)_refillsIssued[0]);                                                                                      \
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca, ncp_xlf_task_tbr_thread_rx_refill_check_2kBuffersOwedIssued, NCP_MSG_ERROR,              \
                              "Pool %d: Total 2KB  buffers owed=%d, issued=%d\r\n",  (int)_pvtTqsHdl->cpuPoolId,                            \
                                (int)_pvtTqsHdl->perHdlRefillsOwed[1],                                                                      \
                                (int)_refillsIssued[1]);                                                                                    \
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca, ncp_xlf_task_tbr_thread_rx_refill_check_16kBuffersOwedIssued, NCP_MSG_ERROR,             \
                              "Pool %d: Total 16KB buffers owed=%d, issued=%d\r\n",  (int)_pvtTqsHdl->cpuPoolId,                            \
                                (int)_pvtTqsHdl->perHdlRefillsOwed[2],                                                                      \
                                (int)_refillsIssued[2]);                                                                                    \
        NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,  ncp_xlf_task_tbr_thread_rx_refill_check_64kBuffersOwedIssued, NCP_MSG_ERROR,            \
                              "Pool %d: Total 64KB buffers owed=%d, issued=%d\r\n",  (int)_pvtTqsHdl->cpuPoolId,                            \
                                (int)_pvtTqsHdl->perHdlRefillsOwed[3],                                                                      \
                                (int)_refillsIssued[3]);                                                                                    \
        _st = NCP_ST_TASK_UNBIND_WHEN_REFILLS_OWED;                                                                                         \
    }                                                                                                                                       \
    _st;                                                                                                                                    \
}) 
    
#else
#define NCP_TASK_TBR_THREAD_RX_REFILL_CHECK(_pvtTqsHdl)  (NCP_ST_SUCCESS)
#endif
 
#define NCP_TASK_TBR_BUFFERS_RECOVER(_pvtTqsHdl, _state) \
    ncp_task_tbr_buffers_recover(_pvtTqsHdl, _state)

#define NCP_TASK_TBR_LEAK_CHECK(_pvtTqsHdl, _searchPid) \
    ncp_task_tbr_leak_check(_pvtTqsHdl, _searchPid)
 
#define NCP_TASK_TBR_TASK_STATE_PREFETCH(_pvtTqsHdl, _pTaskHdr, _freeHeader, _freeData, _pTbr) \
( ncp_task_tbr_task_state_prefetch(_pvtTqsHdl, _pTaskHdr, _freeHeader, _freeData, _pTbr) )
    
#define NCP_TASK_TBR_CPU_POOL_TASK_STATE_PREFETCH(_pvtTqsHdl,           \
                                                _pTaskHdr,              \
                                                _freeHeader,            \
                                                _freeData,              \
                                                _pTbr)                  \
(    ncp_task_tbr_cpu_pool_task_state_prefetch(_pvtTqsHdl,              \
                                            _pTaskHdr,                  \
                                            _freeHeader,                \
                                            _freeData,                  \
                                            _pTbr)                      \
)

#ifdef NCP_TASK_TBR_VALIDATE_CURRENT_BUFFER_STATE 

#define NCP_TASK_TBR_INIT_BUFFER_STATES(_pTbr, _expectedState, _newState) \
    _pTbr->expectedState = (ncp_task_pid_t)_expectedState;                \
    _pTbr->newState = (ncp_task_pid_t)_newState;
    
#define NCP_TASK_TBR_BUFFER_STATE_UPDATE(_pTbr, _canBeMultiRefs) \
{                                                                \
    ncp_task_pid_t  **_pStatePtr =  &_pTbr->statePtrArray[0];    \
    ncp_task_pid_t  *_pState;                                    \
    int _i = _pTbr->ptrCnt;                                      \
    while(_i--)                                                  \
    {                                                            \
        _pState = *_pStatePtr++;                                 \
        if ((*_pState == _pTbr->expectedState) ||                \
            (_canBeMultiRefs && (*_pState == NCP_TASK_TBR_STATE_MULTI_REFS))) \
        {                                                        \
            /* likely code path - optimization */                \
        }                                                        \
        else                                                     \
        {                                                        \
            NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,           \
                ncp_xlf_task_tbr_buffer_state_update_invalidState, \
                NCP_MSG_ERROR,                                   \
                "TBR: Invalid state @ stateLoc %p, expected=%hx, actual=%hx\r\n", \
                _pState,                                         \
                (ncp_uint16_t)_pTbr->expectedState,              \
                (ncp_uint16_t)*_pState);                         \
            NCP_CALL(NCP_ST_TASK_TBR_FATAL_POOL_CORRUPTION);     \
        }                                                        \
                                                                 \
        *_pState = _pTbr->newState;                              \
                                                                 \
    }                                                            \
}  

/* If the buffer is STATE_MULTI_REFS, don't modify its state */
#define NCP_TASK_TBR_BUFFER_GIVE_STATE_UPDATE(_pTbr)          \
{                                                             \
    ncp_task_pid_t  **_pStatePtr =  &_pTbr->statePtrArray[0]; \
    ncp_task_pid_t  *_pState;                                 \
    int _i = _pTbr->ptrCnt;                                   \
    while(_i--)                                               \
    {                                                         \
        _pState = *_pStatePtr++;                              \
                                                              \
        if (*_pState == NCP_TASK_TBR_STATE_MULTI_REFS)        \
        {                                                     \
            continue;                                         \
        }                                                     \
                                                              \
        if (*_pState == _pTbr->expectedState)                 \
        {                                                     \
            /* likely code path - optimization */             \
        }                                                     \
        else                                                  \
        {                                                     \
            NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,        \
                ncp_xlf_task_tbr_buffer_give_state_update_invalidState, \
                NCP_MSG_ERROR,                                \
                "TBR: Invalid state @ stateLoc %p, expected=%hx, actual=%hx\r\n", \
                _pState,                                      \
                (ncp_uint16_t)_pTbr->expectedState,           \
                (ncp_uint16_t)*_pState);                      \
            NCP_CALL(NCP_ST_TASK_TBR_FATAL_POOL_CORRUPTION);  \
        }                                                     \
                                                              \
        *_pState = _pTbr->newState;                           \
                                                              \
    }                                                         \
}

#define NCP_TASK_TBR_BUFFER_TRANSFER_STATE_UPDATE(_pTbr) \
    NCP_TASK_TBR_BUFFER_GIVE_STATE_UPDATE(_pTbr)

#define NCP_TASK_TBR_BUFFER_STATE_UPDATE_MREF(_pTbr)             \
{                                                                \
    ncp_task_pid_t  **_pStatePtr =  &_pTbr->statePtrArray[0];    \
    ncp_task_pid_t  *_pState;                                    \
    int _i = _pTbr->ptrCnt;                                      \
    while(_i--)                                                  \
    {                                                            \
        ncp_uint16_t newState;                                   \
        ncp_bool_t mrefBit = _pTbr->mrefBitArray[_pTbr->ptrCnt - 1 - _i]; \
                                                                 \
        newState = (mrefBit) ?                                   \
            NCP_TASK_TBR_STATE_MULTI_REFS :                       \
            _pTbr->newState;                                     \
                                                                 \
        _pState = *_pStatePtr++;                                 \
        if (((mrefBit == 1) &&                                   \
             (*_pState == NCP_TASK_TBR_STATE_MULTI_REFS)) ||      \
            ((mrefBit == 0) &&                                   \
             (*_pState == _pTbr->expectedState)))                \
        {                                                        \
            /* likely code path - optimization */                \
        }                                                        \
        else                                                     \
        {                                                        \
            ncp_uint16_t expectedState;                          \
                                                                 \
            expectedState = (mrefBit) ?                          \
                NCP_TASK_TBR_STATE_MULTI_REFS :                   \
                _pTbr->expectedState;                            \
                                                                 \
            NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,           \
                ncp_xlf_task_tbr_buffer_state_update_mref_invalidState, \
                NCP_MSG_ERROR,                                   \
                "TBR: Invalid state @ stateLoc %p, expected=%hx, actual=%hx (mref = %d)\r\n", \
                _pState,                                         \
                expectedState,                                   \
                (ncp_uint16_t)*_pState,                          \
                mrefBit);                                        \
                                                                 \
            NCP_CALL(NCP_ST_TASK_TBR_FATAL_POOL_CORRUPTION);     \
        }                                                        \
                                                                 \
        *_pState = newState;                                     \
    }                                                            \
}

#define NCP_TASK_RXTASK_TBR_BUFFER_STATE_UPDATE_MREF(_pTbr)      \
{                                                                \
    ncp_task_pid_t  **_pStatePtr =  &_pTbr->statePtrArray[0];    \
    ncp_task_pid_t  *_pState;                                    \
    int _i = _pTbr->ptrCnt;                                      \
    while(_i--)                                                  \
    {                                                            \
        ncp_uint16_t newState;                                   \
        ncp_bool_t mrefBit = _pTbr->mrefBitArray[_pTbr->ptrCnt - 1 - _i]; \
                                                                 \
        newState = (mrefBit) ?                                   \
            NCP_TASK_TBR_STATE_MULTI_REFS :                      \
            _pTbr->newState;                                     \
                                                                 \
        _pState = *_pStatePtr++;                                 \
        if (((mrefBit == 1) &&                                   \
            ((*_pState == NCP_TASK_TBR_STATE_MULTI_REFS) ||      \
             (*_pState == _pTbr->expectedState))) ||             \
            ((mrefBit == 0) &&                                   \
             (*_pState == _pTbr->expectedState)) ||              \
            /* If we receive a task that had STATE_MULTI_REFS,   \
             * and its mref bit is unset, we know it now has     \
             * a single reference.                               \
             */                                                  \
            ((mrefBit == 0) &&                                   \
             (*_pState == NCP_TASK_TBR_STATE_MULTI_REFS)))       \
        {                                                        \
            /* likely code path - optimization */                \
        }                                                        \
        else                                                     \
        {                                                        \
            ncp_uint16_t expectedState;                          \
                                                                 \
            expectedState = _pTbr->expectedState;                \
                                                                 \
            NCP_TASKIO_TRACEPOINT(Intel_AXXIA_ncp_nca,           \
                ncp_xlf_task_rxtask_tbr_buffer_state_update_mref_invalidState, \
                NCP_MSG_ERROR,                                   \
                "TBR: Invalid state @ stateLoc %p, expected=%hx, actual=%hx (mref = %d)\r\n", \
                _pState,                                         \
                expectedState,                                   \
                (ncp_uint16_t)*_pState,                          \
                mrefBit);                                        \
                                                                 \
            NCP_CALL(NCP_ST_TASK_TBR_FATAL_POOL_CORRUPTION);     \
        }                                                        \
                                                                 \
        *_pState = newState;                                     \
    }                                                            \
}

#else /* NCP_TASK_TBR_VALIDATE_CURRENT_BUFFER_STATE */

#define NCP_TASK_TBR_INIT_BUFFER_STATES(_pTbr, _expectedState, _newState) \
    _pTbr->newState = _newState;

#define NCP_TASK_TBR_BUFFER_STATE_UPDATE(_pTbr, _canBeMultiRefs) \
{                                                                \
    ncp_task_pid_t  **_pStatePtr =  &_pTbr->statePtrArray[0];    \
    ncp_task_pid_t  *_pState;                                    \
    int _i = _pTbr->ptrCnt;                                      \
    while(_i--)                                                  \
    {                                                            \
        _pState = *_pStatePtr++;                                 \
                                                                 \
        *_pState = _pTbr->newState;                              \
                                                                 \
    }                                                            \
}

/* If the buffer is STATE_MULTI_REFS, don't modify its state */
#define NCP_TASK_TBR_BUFFER_GIVE_STATE_UPDATE(_pTbr)          \
{                                                             \
    ncp_task_pid_t  **_pStatePtr =  &_pTbr->statePtrArray[0]; \
    ncp_task_pid_t  *_pState;                                 \
    int _i = _pTbr->ptrCnt;                                   \
    while(_i--)                                               \
    {                                                         \
        _pState = *_pStatePtr++;                              \
                                                              \
        if (*_pState == NCP_TASK_TBR_STATE_MULTI_REFS)        \
        {                                                     \
            continue;                                         \
        }                                                     \
                                                              \
        *_pState = _pTbr->newState;                           \
                                                              \
    }                                                         \
}

#define NCP_TASK_TBR_BUFFER_TRANSFER_STATE_UPDATE(_pTbr) \
    NCP_TASK_TBR_BUFFER_GIVE_STATE_UPDATE(_pTbr)

#define NCP_TASK_TBR_BUFFER_STATE_UPDATE_MREF(_pTbr)          \
{                                                             \
    ncp_task_pid_t  **_pStatePtr =  &_pTbr->statePtrArray[0]; \
    ncp_task_pid_t  *_pState;                                 \
    int _i = _pTbr->ptrCnt;                                   \
    while(_i--)                                               \
    {                                                         \
        ncp_uint16_t newState;                                \
        ncp_bool_t mrefBit = _pTbr->mrefBitArray[_pTbr->ptrCnt - 1 - _i]; \
        _pState = *_pStatePtr++;                              \
                                                              \
        newState = (mrefBit) ?                \
            NCP_TASK_TBR_STATE_MULTI_REFS :                    \
            _pTbr->newState;                                  \
                                                              \
        *_pState = newState;                                  \
    }                                                         \
}

#define NCP_TASK_RXTASK_TBR_BUFFER_STATE_UPDATE_MREF(_pTbr) \
        NCP_TASK_TBR_BUFFER_STATE_UPDATE_MREF(_pTbr)

#endif  /* NCP_TASK_TBR_VALIDATE_CURRENT_BUFFER_STATE */
                                                       
#define NCP_TASK_TBR_BUFFER_STATE_PREFETCH(_pvtTqsHdl, _pBuffer, _poolId, _mrefBit, _pTbr)                                         \
{                                                                                                                        \
    if (NCP_TASK_FIXED_POOL_ENCODED_ID != _poolId)                                                                       \
    {                                                                                                                    \
        NCP_CALL(ncp_task_tbr_buffer_state_prefetch(_pvtTqsHdl, (ncp_uint64_t)(ncp_uintptr_t)_pBuffer, _poolId, _mrefBit, _pTbr)); \
    }                                                                                                                    \
}    
    
/*
 * We need current state when dealing with CPU pool buffers in order to track refills 
 */    
#define NCP_TASK_TBR_CPU_POOL_BUFFER_STATE_PREFETCH(_pvtTqsHdl,             \
                                                  _pBuffer,                 \
                                                  _poolID,                  \
                                                  _pPool,                   \
                                                  _pTbr)                    \
    NCP_CALL(ncp_task_tbr_cpu_pool_buffer_state_prefetch(_pvtTqsHdl,                            \
                                                       (ncp_uint64_t)(ncp_uintptr_t)_pBuffer,   \
                                                       _poolID, _pPool,  _pTbr))                \
    
#ifndef NCP_TASK_PROFILE_RXTASK_UPDATE    
#define NCP_TASK_TBR_RXTASK_STATE_PREFETCH(_pvtTqsHdl, _pTaskHdr, _pTbr)    \
{                                                                           \
    if (NULL == _pvtTqsHdl->cpuPoolHdl)                                     \
    {                                                                       \
        NCP_TASK_TBR_INIT_BUFFER_STATES(_pTbr, NCP_TASK_TBR_STATE_FREE, _pvtTqsHdl->pProcess->pid);    \
        NCP_CALL(NCP_TASK_TBR_TASK_STATE_PREFETCH(_pvtTqsHdl,               \
                                   _pTaskHdr,                               \
                                   TRUE,                                    \
                                   TRUE,                                    \
                                   _pTbr));                                 \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        NCP_TASK_TBR_INIT_BUFFER_STATES(_pTbr, NCP_TASK_TBR_STATE_NCA_OWNED, _pvtTqsHdl->pProcess->pid); \
        NCP_CALL(NCP_TASK_TBR_CPU_POOL_TASK_STATE_PREFETCH(_pvtTqsHdl,      \
                                  _pTaskHdr,                                \
                                   TRUE,                                    \
                                   TRUE,                                    \
                                   _pTbr));                                 \
    }                                                                       \
}  
#else
#define NCP_TASK_TBR_RXTASK_STATE_PREFETCH(_pvtTqsHdl, _pTaskHdr, _pTbr) \
{                                                               \
    ncp_uint64_t start, finish;                                 \
    int _x;                                                     \
    enable_ccnt();                                              \
    reset_ccnt();                                               \
    start = read_ccnt();                                        \
    if (NULL == _pvtTqsHdl->cpuPoolHdl)                         \
    {                                                                       \
        NCP_TASK_TBR_INIT_BUFFER_STATES(_pTbr, NCP_TASK_TBR_STATE_FREE, _pvtTqsHdl->pProcess->pid);    \
        NCP_CALL(NCP_TASK_TBR_TASK_STATE_PREFETCH(_pvtTqsHdl,               \
                                   _pTaskHdr,                               \
                                   TRUE,                                    \
                                   TRUE,                                    \
                                   _pTbr));                                 \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        NCP_TASK_TBR_INIT_BUFFER_STATES(_pTbr, NCP_TASK_TBR_STATE_NCA_OWNED, _pvtTqsHdl->pProcess->pid); \
        NCP_CALL(NCP_TASK_TBR_CPU_POOL_TASK_STATE_PREFETCH(_pvtTqsHdl,      \
                                  _pTaskHdr,                                \
                                   TRUE,                                    \
                                   TRUE,                                    \
                                   _pTbr));                                 \
    }                                                                       \
    finish = read_ccnt();                                                   \
    pmu_rx_task_update_results[numPmuRxTaskUpdateResults].cycles = finish - start; \
    pmu_rx_task_update_results[numPmuRxTaskUpdateResults].ptrCnt = _pTaskHdr->ptrCnt; \
    pmu_rx_task_update_results[numPmuRxTaskUpdateResults].combinedHeader = _pTaskHdr->combinedHeader; \
    numPmuRxTaskUpdateResults++;                                            \
    if (NCP_MAX_PMU_RESULTS == numPmuRxTaskUpdateResults)                   \
    {                                                                       \
        int _x;                                                             \
        printf("last %d TXTASK_UPDATE pmu results\n", NCP_MAX_PMU_RESULTS); \
        for (_x=0; _x<NCP_MAX_PMU_RESULTS; _x++)                            \
        {                                                                   \
            printf("(cycles=%lld ptrCnt=%d CH=%d) ",                        \
                (long long int)pmu_rx_task_update_results[_x].cycles,       \
                (int)pmu_rx_task_update_results[_x].ptrCnt,                 \
                (int)pmu_rx_task_update_results[_x].combinedHeader);        \
        }                                                                   \
        printf("\r\n");                                                     \
        numPmuRxTaskUpdateResults = 0;                                      \
    }                                                                       \
}  
#endif /* NCP_TASK_PROFILE_RXTASK_UPDATE */
  
#ifndef NCP_TASK_PROFILE_TXTASK_UPDATE  
#define NCP_TASK_TBR_TXTASK_STATE_PREFETCH(_pvtTqsHdl, _pTaskHdr, _freeHeader, _freeData, _p_oPCQ, _pTbr) \
{                                                           \
    if (NULL == _pvtTqsHdl->cpuPoolHdl)                     \
    {                                                                       \
        NCP_TASK_TBR_INIT_BUFFER_STATES(_pTbr, _pvtTqsHdl->pProcess->pid, NCP_TASK_TBR_STATE_FREE);                \
        NCP_CALL(NCP_TASK_TBR_TASK_STATE_PREFETCH(_pvtTqsHdl,               \
                                   _pTaskHdr,                               \
                                   _freeHeader,                             \
                                   _freeData,                               \
                                   _pTbr));                                 \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        _pTbr->pRefillsIssued                                               \
            = &(_pvtTqsHdl->perHdlRefillsIssued[_p_oPCQ->u.opcq_info.relId][0]);  \
        NCP_TASK_TBR_INIT_BUFFER_STATES(_pTbr, _pvtTqsHdl->pProcess->pid, NCP_TASK_TBR_STATE_NCA_OWNED);                \
        NCP_CALL(NCP_TASK_TBR_CPU_POOL_TASK_STATE_PREFETCH(_pvtTqsHdl,      \
                                   _pTaskHdr,                               \
                                   _freeHeader,                             \
                                   _freeData,                               \
                                   _pTbr));                                 \
    }                                                                       \
}
#else
/* WARNING: This profile function is *not* multi-thread or multi-process safe - run just 1 client! */
#define NCP_TASK_TBR_TXTASK_STATE_PREFETCH(_pvtTqsHdl, _pTaskHdr, _freeHeader, _freeData, _p_oPCQ, _pTbr) \
{                                                           \
    ncp_uint64_t start, finish;                             \
    int _x;                                                 \
    enable_ccnt();                                          \
    reset_ccnt();                                           \
    start = read_ccnt();                                    \
    if (NULL == _pvtTqsHdl->cpuPoolHdl)                     \
    {                                                                       \
        NCP_TASK_TBR_INIT_BUFFER_STATES(_pTbr, _pvtTqsHdl->pProcess->pid, NCP_TASK_TBR_STATE_FREE);                \
        NCP_CALL(NCP_TASK_TBR_TASK_STATE_PREFETCH(_pvtTqsHdl,               \
                                   _pTaskHdr,                               \
                                   _freeHeader,                             \
                                   _freeData,                               \
                                   _pTbr));                                 \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        _pTbr->pRefillsIssued                                               \
            = &(_pvtTqsHdl->perHdlRefillsIssued[_p_oPCQ->u.opcq_info.relId][0]);  \
        NCP_TASK_TBR_INIT_BUFFER_STATES(_pTbr, _pvtTqsHdl->pProcess->pid, NCP_TASK_TBR_STATE_NCA_OWNED);                \
        NCP_CALL(NCP_TASK_TBR_CPU_POOL_TASK_STATE_PREFETCH(_pvtTqsHdl,      \
                                   _pTaskHdr,                               \
                                   _freeHeader,                             \
                                   _freeData,                               \
                                   _pTbr));                                 \
    }                                                                       \                                                                      \
    finish = read_ccnt();                                                   \
    pmu_tx_task_update_results[numPmuTxTaskUpdateResults].cycles = finish - start; \
    pmu_tx_task_update_results[numPmuTxTaskUpdateResults].ptrCnt = _pTaskHdr->ptrCnt; \
    pmu_tx_task_update_results[numPmuTxTaskUpdateResults].combinedHeader = _pTaskHdr->combinedHeader; \
    numPmuTxTaskUpdateResults++;                                            \
    if (NCP_MAX_PMU_RESULTS == numPmuTxTaskUpdateResults)                   \
    {                                                                       \
        int _x;                                                             \
        printf("last %d TXTASK_UPDATE pmu results\n", NCP_MAX_PMU_RESULTS); \
        for (_x=0; _x<NCP_MAX_PMU_RESULTS; _x++)                            \
        {                                                                   \
            printf("(cycles=%lld ptrCnt=%d CH=%d) ",                        \
                (long long int)pmu_tx_task_update_results[_x].cycles,       \
                (int)pmu_tx_task_update_results[_x].ptrCnt,                 \
                (int)pmu_tx_task_update_results[_x].combinedHeader);        \
        }                                                                   \
        printf("\r\n");                                                     \
        numPmuTxTaskUpdateResults = 0;                                      \
    }                                                                       \
}
#endif /* NCP_TASK_PROFILE_TXTASK_UPDATE */

#define NCP_TASK_TBR_REFCNT_INC_TASK_STATE_PREFETCH(_pvtTqsHdl, _pTaskHdr, _p_oPCQ, _pTbr) \
{                                                    \
        NCP_TASK_TBR_INIT_BUFFER_STATES(             \
            _pTbr,                                   \
            _pvtTqsHdl->pProcess->pid,               \
            NCP_TASK_TBR_STATE_MULTI_REFS);          \
                                                     \
        NCP_CALL(NCP_TASK_TBR_TASK_STATE_PREFETCH(   \
            _pvtTqsHdl,                              \
            _pTaskHdr,                               \
            FALSE,                                   \
            TRUE,                                    \
            _pTbr));                                 \
}

#define NCP_TASK_TBR_TASK_TAKE_STATE_PREFETCH(_pvtTqsHdl, _pTaskHdr, _pTbr)                   \
{                                                                       \
    if (NULL == _pvtTqsHdl->cpuPoolHdl)                                 \
    {                                                                   \
        NCP_TASK_TBR_INIT_BUFFER_STATES(_pTbr, NCP_TASK_TBR_STATE_RTE_OWNED, _pvtTqsHdl->pProcess->pid); \
        NCP_CALL(NCP_TASK_TBR_TASK_STATE_PREFETCH(_pvtTqsHdl,           \
                               _pTaskHdr,                               \
                               TRUE,                                    \
                               TRUE,                                    \
                               _pTbr));                                 \
    }                                                                   \
    else                                                                \
    {                                                                   \
        NCP_TASK_TBR_INIT_BUFFER_STATES(_pTbr, NCP_TASK_TBR_STATE_RTE_OWNED, _pvtTqsHdl->pProcess->pid); \
        NCP_CALL(NCP_TASK_TBR_CPU_POOL_TASK_STATE_PREFETCH(_pvtTqsHdl,  \
                               _pTaskHdr,                               \
                               TRUE,                                    \
                               TRUE,                                    \
                               _pTbr));                                 \
    }                                                                   \
} 

#define NCP_TASK_TBR_BUFFER_TAKE_STATE_PREFETCH(_pvtTqsHdl, _poolId, _pBuffer, _pTbr) \
{                                                                                     \
    NCP_TASK_TBR_INIT_BUFFER_STATES(_pTbr, NCP_TASK_TBR_STATE_RTE_OWNED, _pvtTqsHdl->pProcess->pid);             \
    NCP_TASK_TBR_BUFFER_STATE_PREFETCH(_pvtTqsHdl, _pBuffer, _poolId, 0, _pTbr)          \
}    
  
#define NCP_TASK_TBR_TASK_GIVE_STATE_PREFETCH(_pvtTqsHdl, _pTaskHdr, _pTbr)  \
{                                                                       \
    if (NULL == _pvtTqsHdl->cpuPoolHdl)                                 \
    {                                                                   \
        NCP_TASK_TBR_INIT_BUFFER_STATES(_pTbr, _pvtTqsHdl->pProcess->pid, NCP_TASK_TBR_STATE_RTE_OWNED);            \
        NCP_CALL(NCP_TASK_TBR_TASK_STATE_PREFETCH(_pvtTqsHdl,           \
                               _pTaskHdr,                               \
                               TRUE,                                    \
                               TRUE,                                    \
                               _pTbr));                                 \
    }                                                                   \
    else                                                                \
    {                                                                   \
        NCP_TASK_TBR_INIT_BUFFER_STATES(_pTbr, _pvtTqsHdl->pProcess->pid, NCP_TASK_TBR_STATE_RTE_OWNED);            \
        NCP_CALL(NCP_TASK_TBR_CPU_POOL_TASK_STATE_PREFETCH(_pvtTqsHdl,  \
                               _pTaskHdr,                               \
                               TRUE,                                    \
                               TRUE,                                    \
                               _pTbr));                                 \
    }                                                                   \
}
 
#define NCP_TASK_TBR_BUFFER_GIVE_STATE_PREFETCH(_pvtTqsHdl, _poolId,  _pBuffer, _pTbr) \
{                                                                                      \
    NCP_TASK_TBR_INIT_BUFFER_STATES(_pTbr, _pvtTqsHdl->pProcess->pid, NCP_TASK_TBR_STATE_RTE_OWNED);                               \
    NCP_TASK_TBR_BUFFER_STATE_PREFETCH(_pvtTqsHdl, _pBuffer, _poolId, 0, _pTbr);          \
}

#define NCP_TASK_TBR_TASK_ATOMIC_TRANSFER_STATE_PREFETCH(_pvtTqsHdl, _targetPid, _pTaskHdr, _pTbr)   \
{                                                                       \
    if (NULL == _pvtTqsHdl->cpuPoolHdl)                                 \
    {                                                                   \
        NCP_TASK_TBR_INIT_BUFFER_STATES(_pTbr, _pvtTqsHdl->pProcess->pid, _targetPid);            \
        NCP_CALL(NCP_TASK_TBR_TASK_STATE_PREFETCH(_pvtTqsHdl,           \
                               _pTaskHdr,                               \
                               TRUE,                                    \
                               TRUE,                                    \
                               _pTbr));                                 \
    }                                                                   \
    else                                                                \
    {                                                                   \
        NCP_TASK_TBR_INIT_BUFFER_STATES(_pTbr, _pvtTqsHdl->pProcess->pid, _targetPid);            \
        NCP_CALL(NCP_TASK_TBR_CPU_POOL_TASK_STATE_PREFETCH(_pvtTqsHdl,  \
                               _pTaskHdr,                               \
                               TRUE,                                    \
                               TRUE,                                    \
                               _pTbr));                                 \
    }                                                                   \
}

#define NCP_TASK_TBR_TASK_BUFFER_OWNERSHIP_GET(_pvtTqsHdl, _poolId, _taskBuffer, _pPid) \
    NCP_CALL(ncp_task_tbr_task_buffer_pid_get(_pvtTqsHdl, _poolId, _taskBuffer, _pPid))
  
#define NCP_TASK_TBR_BUFFER_ATOMIC_TRANSFER_STATE_PREFETCH(_pvtTqsHdl, _target_pid, _poolId,  _pBuffer, _pTbr)       \
{                                                                                               \
    NCP_TASK_TBR_INIT_BUFFER_STATES(_pTbr, _pvtTqsHdl->pProcess->pid, _target_pid);                                        \
    NCP_TASK_TBR_BUFFER_STATE_PREFETCH(_pvtTqsHdl, _pBuffer, _poolId, 0, _pTbr);                   \
} 

#define NCP_TASK_TBR_CPUPOOL_REFILL_COUNT_UPDATE(_pvtTqsHdl) \
    NCP_CALL(ncp_task_tbr_update_per_tqs_cpupool_refill_count(_pvtTqsHdl))

#else /* (1 == NCP_TASK_TBR_ENABLED) */

#define NCP_TASK_TBR_STATE_PTRS_DECL()

#define NCP_TASK_TBR_STATE_PTRS_INIT()

#define NCP_TASK_INITIALIZE_TBR_ARRAYS()

#define NCP_TASK_DECREMENT_POOL_USE_COUNTS(_pvtTqsHdl)

#define NCP_TASK_INCREMENT_POOL_USE_COUNTS(_pvtTqsHdl)

#define NCP_TASK_TBR_TQS_IN_RECOVERY_CLEAR(_ncpHdl, _pTqs)

#define NCP_TASK_TBR_CPU_POOL_RECOVERY_CLEAR(_poolId)

#define NCP_TASK_TBR_GLOBAL_POOL_REFILL_RECOVERY(_cpuPoolHdl)

#define NCP_TASK_TBR_INITIATE_RECOVERY( _pProcess, _pNcpStatus) 

#define NCP_TASK_TBR_THREAD_REFILL_CHECK(_pvtTqsHdl)

#define NCP_TASK_TBR_ADD_TO_CPUPOOL_TQS_LIST(_poolId, _pTqs) 

#define NCP_TASK_TBR_REMOVE_FROM_CPUPOOL_TQS_LIST(_tqsHdl)

#define NCP_TASK_TBR_THREAD_RX_REFILL_CHECK(_pvtTqsHdl) (NCP_ST_SUCCESS)

#define NCP_TASK_TBR_BUFFERS_RECOVER(_pvtTqsHdl, _state) (NCP_ST_SUCCESS)

#define NCP_TASK_TBR_LEAK_CHECK(_pvtTqsHdl, _searchPid) (NCP_ST_SUCCESS)

#define NCP_TASK_TBR_TASK_STATE_PREFETCH(_pvtTqsHdl, _pTaskHdr, _freeHeader, _freeData, _pTbr)

#define NCP_TASK_TBR_INIT_BUFFER_STATES(_pTbr, _expectedstate, _newState)

#define NCP_TASK_TBR_BUFFER_STATE_UPDATE(_pTbr, _canBeMultiRefs)

#define NCP_TASK_TBR_BUFFER_GIVE_STATE_UPDATE(_pTbr)

#define NCP_TASK_TBR_BUFFER_TRANSFER_STATE_UPDATE(_pTbr)

#define NCP_TASK_TBR_BUFFER_STATE_UPDATE_MREF(_pTbr)

#define NCP_TASK_RXTASK_TBR_BUFFER_STATE_UPDATE_MREF(_pTbr)

#define NCP_TASK_TBR_BUFFER_STATE_PREFETCH(_pvtTqsHdl, _pBuffer, _poolId, _mrefBit, _pTbr) 

#define NCP_TASK_TBR_RXTASK_STATE_PREFETCH(_pvtTqsHdl, _pTaskHdr, _pTbr) 

#define NCP_TASK_TBR_TXTASK_STATE_PREFETCH(_pvtTqsHdl, _pTaskHdr, _freeHeader, _freeData, _p_oPCQ, _pTbr) 

#define NCP_TASK_TBR_REFCNT_INC_TASK_STATE_PREFETCH(_pvtTqsHdl, _pTaskHdr, _p_oPCQ, _pTbr)

#define NCP_TASK_TBR_TASK_TAKE_STATE_PREFETCH(_pvtTqsHdl, _pTaskHdr, _pTbr)

#define NCP_TASK_TBR_BUFFER_TAKE_STATE_PREFETCH(_pvtTqsHdl,  _poolId, _pBuffer, _pTbr)

#define NCP_TASK_TBR_TASK_GIVE_STATE_PREFETCH(_pvtTqsHdl, _pTaskHdr, _pTbr)

#define NCP_TASK_TBR_BUFFER_GIVE_STATE_PREFETCH(_pvtTqsHdl, _poolId,  _pBuffer, _pTbr)

#define NCP_TASK_TBR_TASK_BUFFER_OWNERSHIP_GET(_pvtTqsHdl, _poolId, _taskBuffer, _pPid)

#define NCP_TASK_TBR_TASK_ATOMIC_TRANSFER_STATE_PREFETCH(_pvtTqsHdl, _targetPid, _pTaskHdr, _pTbr)

#define NCP_TASK_TBR_BUFFER_ATOMIC_TRANSFER_STATE_PREFETCH(_pvtTqsHdl, _targetPid, _poolId,  _pBuffer, _pTbr)

#define NCP_TASK_TBR_CPUPOOL_REFILL_COUNT_UPDATE(_pvtTqsHdl)

#endif /* (1 == NCP_TASK_TBR_ENABLED) */

#define NCP_TASK_FILL_PER_OPCQ_AUX_DATA(_pvtTqsHdl,     \
                               _p_oPCQ)                 \
ncp_task_fill_per_opcq_aux_data(_pvtTqsHdl,             \
                       _p_oPCQ);                     
  
#if (0 == ARCH_HAS_STORE_RELEASE_INSTRUCTION)
#define NCP_TASK_OPCQ_ISSUE_BARRIER_AND_WRITE_PIDX(_pOPCQ)                               \
{                                                                   \
        NCP_OPCQ_SYSMEM_BARRIER();  /* enforce write ordering */    \
        *(_pOPCQ->pProducerIdx) = _pOPCQ->hwProducerVal;            \
}        
#else
#define NCP_TASK_OPCQ_ISSUE_BARRIER_AND_WRITE_PIDX(_pOPCQ)  \
    arch_store_release_8b(_pOPCQ->hwProducerVal, _pOPCQ->pProducerIdx);
#endif
  
#if (0 == ARCH_HAS_STORE_RELEASE_INSTRUCTION)
#define NCP_TASK_OPCQ_UPDATE_CACHED_PIDX(_pOPCQ)                           \
{                                                                           \
    ncp_uint8_t _pIdx = ((_pOPCQ)->hwProducerVal & NCP_PCQ_TOGGLE_BIT_MASK);\
    _pIdx = (_pIdx + 1 ) & (_pOPCQ->nEntriesMinusOne);                      \
    if (0 == _pIdx)                                                         \
    {                                                                       \
        _pOPCQ->u.opcq_info.pOPCQentry = _pOPCQ->pPCQbase;                  \
        _pOPCQ->u.opcq_info.pPrefetchEntry++;                               \
        _pOPCQ->toggleBit ^= (1 << NCP_PCQ_TOGGLE_BIT_SHIFT); /* invert toggle bit */  \
        _pOPCQ->pcqRollCnt++;                                               \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        _pOPCQ->u.opcq_info.pOPCQentry++;                                   \
        if (_pOPCQ->u.opcq_info.pPrefetchEntry != _pOPCQ->u.opcq_info.pLastEntry) \
        {                                                                   \
            _pOPCQ->u.opcq_info.pPrefetchEntry++;                           \
        }                                                                   \
        else                                                                \
        {                                                                   \
            _pOPCQ->u.opcq_info.pPrefetchEntry = _pOPCQ->pPCQbase;          \
        }                                                                   \
    }                                                                       \
    /* prefetch next */                                                     \
    NCP_TASK_PREFETCH_PCQ_ENTRY_FOR_WRITE(_pOPCQ->u.opcq_info.pPrefetchEntry);  \
    /* Bulk functions will issue the memory barrier                         \
     * and write the new producer idx to the PGIT themselves.               \
     */                                                                     \
    _pOPCQ->hwProducerVal = (_pIdx | _pOPCQ->toggleBit);                    \
}
#else
/* TODO - implement using A53 store release instructions */
#define NCP_TASK_OPCQ_UPDATE_CACHED_PIDX(_pOPCQ)                           \
{                                                                           \
    ncp_uint8_t _pIdx = ((_pOPCQ)->hwProducerVal & NCP_PCQ_TOGGLE_BIT_MASK);\
    _pIdx = (_pIdx + 1 ) & (_pOPCQ->nEntriesMinusOne);                      \
    if (0 == _pIdx)                                                         \
    {                                                                       \
        _pOPCQ->u.opcq_info.pOPCQentry = _pOPCQ->pPCQbase;                  \
        _pOPCQ->u.opcq_info.pPrefetchEntry++;                               \
        _pOPCQ->toggleBit ^= (1 << NCP_PCQ_TOGGLE_BIT_SHIFT); /* invert toggle bit */  \
        _pOPCQ->pcqRollCnt++;                                               \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        _pOPCQ->u.opcq_info.pOPCQentry++;                                   \
        if (_pOPCQ->u.opcq_info.pPrefetchEntry != _pOPCQ->u.opcq_info.pLastEntry) \
        {                                                                   \
            _pOPCQ->u.opcq_info.pPrefetchEntry++;                           \
        }                                                                   \
        else                                                                \
        {                                                                   \
            _pOPCQ->u.opcq_info.pPrefetchEntry = _pOPCQ->pPCQbase;          \
        }                                                                   \
    }                                                                       \
    /* prefetch next */                                                     \
    NCP_TASK_PREFETCH_PCQ_ENTRY_FOR_WRITE(_pOPCQ->u.opcq_info.pPrefetchEntry);  \
    /* Bulk functions will issue the memory barrier                         \
     * and write the new producer idx to the PGIT themselves.               \
     */                                                                     \
    _pOPCQ->hwProducerVal = (_pIdx | _pOPCQ->toggleBit);                    \
}
#endif

#ifndef NCP_CHECK_DISABLED
#define NCP_TASK_VALIDATE_RESOURCE_NAME(_resourceName, _ec) \
{                                                   \
    size_t _myStrlen;                               \
    if (NULL == _resourceName)                      \
    {                                               \
        NCP_CALL(_ec);                              \
    }                                               \
    _myStrlen = ncp_strnlen((&(_resourceName->name[0])), sizeof(ncp_task_resource_name_t));\
    if ((0 == _myStrlen) || (sizeof(ncp_task_resource_name_t) == _myStrlen))               \
    {                                               \
        NCP_CALL(_ec);                              \
    }                                               \
}        
    
#define NCP_VALIDATE_TQS_HDL(_tqsHdl)                   \
{                                                       \
    if (NULL == _tqsHdl)                                \
    {                                                   \
        NCP_CALL(NCP_ST_INVALID_HANDLE);                \
    }                                                   \
    if (NCP_TASK_TQS_HDL_COOKIE !=                      \
        ((ncp_task_pvt_tqsHdl_data_t *)_tqsHdl)->cookie)\
    {                                                   \
        _tqsHdl=NULL; /* do not attempt err stat */     \
        NCP_CALL(NCP_ST_INVALID_TQS_HANDLE);            \
    }                                                   \
}    
#else
#define NCP_TASK_VALIDATE_RESOURCE_NAME(_name, _ec)
#define NCP_VALIDATE_TQS_HDL(_tqsHdl)
#endif


#if !defined(NCP_KERNEL) && !defined(NCP_CHECK_DISABLED)
#define NCP_VALIDATE_NCP_HDL(ncpHdl)     ncp_validate_handle(ncpHdl)
#define NCP_VP_VALIDATE_HANDLE(vpHdl)        ncp_vp_validate_handle(vpHdl)
#else
#define NCP_VALIDATE_NCP_HDL(ncpHdl)   NCP_ST_SUCCESS
#define NCP_VP_VALIDATE_HANDLE(vpHdl)  NCP_ST_SUCCESS
#endif /* NCP_KERNEL */

#if !defined(NCP_KERNEL) && !defined(NCP_TASKIO_CHECK_DISABLED)
#define NCP_TASKIO_VALIDATE_NCP_HDL(ncpHdl)     ncp_validate_handle(ncpHdl)
#define NCP_TASKIO_VP_VALIDATE_HANDLE(vpHdl)    ncp_vp_validate_handle(vpHdl)
#else
#define NCP_TASKIO_VALIDATE_NCP_HDL(ncpHdl) NCP_ST_SUCCESS
#define NCP_TASKIO_VP_VALIDATE_HANDLE(vpHdl) NCP_ST_SUCCESS
#endif /* NCP_KERNEL */

#define NCP_DEV_NCA_WRITE_INDIRECT_REG32(_dev, _region, _offset, _pVal)   \
{                                                                         \
    if (ncpHwioTraceFunc != NULL)                                         \
    {                                                                     \
        ncp_hwio_rw_t _hw;                                                \
        ncp_uint32_t _devNum;                                             \
        NCP_CALL(ncp_dev_num_get(_dev, &_devNum));                        \
        _hw.regionId = _region;                                           \
        _hw.offset = (_offset);                                           \
        _hw.buffer = (ncp_uint32_t*)_pVal;                                \
        _hw.count = 1;                                                    \
        _hw.flags = 0;                                                    \
        ncpHwioTraceFunc(                                                 \
                ncpHwioTraceFuncArg,                                      \
                NCP_HWIO_WRITE32,                                         \
                _devNum,                                                  \
                &_hw);                                                    \
    }                                                                     \
    NCP_CALL(ncp_dev_block_write32(_dev, _region, _offset, _pVal, 1, 0)); \
}

#define NCP_DEV_NCA_WRITE_REG32(_dev, _region, _offset, _val)             \
{                                                                         \
    ncp_uint32_t _tmp_val = _val;                                         \
    ncp_uint32_t *_pVal =  &_tmp_val;                                     \
    NCP_DEV_NCA_WRITE_INDIRECT_REG32(_dev, _region, _offset, _pVal);      \
}



#define NCP_DEV_NCA_READ_REG32(_dev, _region, _offset, _pVal)            \
{                                                                        \
    NCP_CALL(ncp_dev_block_read32(_dev, _region, _offset, _pVal, 1, 0)); \
    if (ncpHwioTraceFunc != NULL)                                        \
    {                                                                    \
        ncp_hwio_rw_t _hw;                                               \
        ncp_uint32_t _devNum;                                            \
        NCP_CALL(ncp_dev_num_get(_dev, &_devNum));                       \
        _hw.regionId = _region;                                          \
        _hw.offset = (_offset);                                          \
        _hw.buffer = (ncp_uint32_t*)_pVal;                               \
        _hw.count = 1;                                                   \
        _hw.flags = 0;                                                   \
        ncpHwioTraceFunc(                                                \
                ncpHwioTraceFuncArg,                                     \
                NCP_HWIO_READ32,                                         \
                _devNum,                                                 \
                &_hw);                                                   \
    }                                                                    \
}

#define NCP_TASK_POST_SEND_DONE(_pvtTqsHdl, _p_oPCQ)                      \
{                                                                         \
    int _txQueueId = _p_oPCQ->u.opcq_info.relId;                          \
    (_pvtTqsHdl)->sendDoneInfo[_txQueueId].cIdx                           \
       = (((_pvtTqsHdl)->sendDoneInfo[_txQueueId].cIdx + 1)               \
         & ((_pvtTqsHdl)->sendDoneInfo[_txQueueId].nEntriesMinusOne));    \
}  

#define NCP_TASK_UPDATE_NUM_TX_ENTRIES_AVAIL(_myTqsHdl, _pOPCQ) \
({                                                                                                      \
        ncp_uint8_t _strippedConsumerVal;                                                               \
        ncp_uint8_t _strippedProducerVal = _pOPCQ->hwProducerVal & NCP_PCQ_TOGGLE_BIT_MASK;             \
        /* refresh cached consumer idx */                                                               \
        _pOPCQ->hwConsumerVal = *(p_oPCQ->pConsumerIdx);                                                \
        _strippedConsumerVal = _pOPCQ->hwConsumerVal & NCP_PCQ_TOGGLE_BIT_MASK;                         \
        /* compute number of available txQ entries */                                                   \
        if (_strippedProducerVal == _strippedConsumerVal)                                               \
        {                                                                                               \
            if (_pOPCQ->hwConsumerVal == _pOPCQ->hwProducerVal)                                         \
            {                                                                                           \
                /* if toggle bit is the same,  then queue is (empty) 100% full of available entries */  \
                _pOPCQ->u.opcq_info.numTxAvail = _pOPCQ->nEntries;                                      \
            }                                                                                           \
            else                                                                                        \
            {                                                                                           \
                _pOPCQ->u.opcq_info.numTxAvail = 0;                                                     \
            }                                                                                           \
        }                                                                                               \
        else if (_strippedProducerVal > _strippedConsumerVal)                                           \
        {                                                                                               \
            _pOPCQ->u.opcq_info.numTxAvail = ((_pOPCQ->nEntries) - _strippedProducerVal) + _strippedConsumerVal;  \
        }                                                                                               \
        else                                                                                            \
        {                                                                                               \
            _pOPCQ->u.opcq_info.numTxAvail = _strippedConsumerVal - _strippedProducerVal;               \
        }                                                                                               \
        /* process completed sends */                                                                   \
        ncp_task_process_oPCQ_aux_entries(_myTqsHdl, _pOPCQ);                                           \
})         

/*
 * NOTE - Updates num rx tasks available and returns stripped consumer! 
 */
#define NCP_TASK_UPDATE_NUM_RX_DEFERRED_AVAIL(_pIPCQ)                                                   \
({                                                                                                      \
        ncp_uint8_t _strippedConsumerVal = _pIPCQ->u.ipcq_info.appConsumerVal & NCP_PCQ_TOGGLE_BIT_MASK;\
        ncp_uint8_t _strippedProducerVal = _pIPCQ->hwProducerVal & NCP_PCQ_TOGGLE_BIT_MASK;             \
        if (_strippedProducerVal == _strippedConsumerVal)                                               \
        {                                                                                               \
            if (_pIPCQ->u.ipcq_info.appConsumerVal != _pIPCQ->hwProducerVal)                            \
            {                                                                                           \
                /* if toggle bit is only difference,  then queue is 100% full of available entries */   \
                _pIPCQ->u.ipcq_info.numRxAvail = _pIPCQ->nEntries;                                      \
            }                                                                                           \
            else                                                                                        \
            {                                                                                           \
                _pIPCQ->u.ipcq_info.numRxAvail = 0;                                                     \
            }                                                                                           \
        }                                                                                               \
        else if (_strippedProducerVal > _strippedConsumerVal)                                           \
        {                                                                                               \
            _pIPCQ->u.ipcq_info.numRxAvail = _strippedProducerVal - _strippedConsumerVal;               \
        }                                                                                               \
        else                                                                                            \
        {                                                                                               \
            _pIPCQ->u.ipcq_info.numRxAvail                                                              \
                = ((_pIPCQ->nEntries) - _strippedConsumerVal) + _strippedProducerVal;                   \
        }                                                                                               \
        (_strippedConsumerVal);                                                                         \
})  

/*
 * NOTE - Updates num rx tasks available and returns stripped consumer! 
 */
#define NCP_TASK_UPDATE_NUM_RX_AVAIL(_pIPCQ)                                                            \
({                                                                                                      \
        ncp_uint8_t _strippedConsumerVal = _pIPCQ->hwConsumerVal & NCP_PCQ_TOGGLE_BIT_MASK;             \
        ncp_uint8_t _strippedProducerVal = _pIPCQ->hwProducerVal & NCP_PCQ_TOGGLE_BIT_MASK;             \
        if (_strippedProducerVal == _strippedConsumerVal)                                               \
        {                                                                                               \
            if (_pIPCQ->hwConsumerVal != _pIPCQ->hwProducerVal)                                         \
            {                                                                                           \
                /* if toggle bit is only difference,  then queue is 100% full of available entries */   \
                _pIPCQ->u.ipcq_info.numRxAvail = _pIPCQ->nEntries;                                      \
            }                                                                                           \
            else                                                                                        \
            {                                                                                           \
                _pIPCQ->u.ipcq_info.numRxAvail = 0;                                                     \
            }                                                                                           \
        }                                                                                               \
        else if (_strippedProducerVal > _strippedConsumerVal)                                           \
        {                                                                                               \
            _pIPCQ->u.ipcq_info.numRxAvail = _strippedProducerVal - _strippedConsumerVal;               \
        }                                                                                               \
        else                                                                                            \
        {                                                                                               \
            _pIPCQ->u.ipcq_info.numRxAvail                                                              \
                = ((_pIPCQ->nEntries) - _strippedConsumerVal) + _strippedProducerVal;                   \
        }                                                                                               \
        (_strippedConsumerVal);                                                                         \
})        
        
        
#ifndef NCP_TASK_COLLECT_STATS_DISABLED 
/*
 * NOTE: atomic add/dec is not required for TQS-local stats, but is required for the global stats.
 * The TQS-local stats are ptoected by the appropriate q-locks. 
 */
 
#define NCP_TASK_INC_STAT(_pTqs, _thisStat)                \
    {                                                      \
        if (NULL != _pTqs)                                 \
            { (_pTqs)->taskStats.stat_##_thisStat ++; }    \
    }

#define NCP_TASK_INC_ERROR_STAT_VIA_PTQS(_pTqs, _thisStat) \
    {                                                      \
        if (NULL != _pTqs)                                 \
            { (_pTqs)->taskStats.stat_##_thisStat ++; }    \
        else if (NULL != pNcpTaskSwState)                  \
            { pNcpTaskSwState->taskStats.stat_##_thisStat ++; } \
    }    
    
#define NCP_TASK_INC_ERROR_STAT_VIA_PTQSHDL(_pTqsHdl, _thisStat)\
    {                                                           \
        if (NULL != _pTqsHdl)                                   \
            { (_pTqsHdl)->pTqs->taskStats.stat_##_thisStat ++; }\
        else if (NULL != pNcpTaskSwState)                       \
            { pNcpTaskSwState->taskStats.stat_##_thisStat ++; } \
    }        
    
#define NCP_TASK_ADD_STAT(_pTqs, _thisStat, _val)           \
    {                                                       \
        if (NULL != _pTqs)                                  \
            { (_pTqs)->taskStats.stat_##_thisStat += _val; }\
    }
    
#define NCP_TASK_ADD_TXSTAT(_pTqs, _thisStat, _txq, _val) {       \
    if (NULL != _pTqs)                                            \
    {                                                             \
        if (0 == _txq)                                            \
        {                                                         \
            (_pTqs)->taskStats.stat_TX0_##_thisStat += _val;      \
        }                                                         \
        else                                                      \
        {                                                         \
            (_pTqs)->taskStats.stat_TX1_##_thisStat += _val;      \
        }                                                         \
    }                                                             \
}
 
 
#if defined(__GNUC__) && \
    !(defined(__clang__)        || \
      defined(__INTEL_COMPILER) || \
      defined(PROC_EP8572)      || \
      defined(PROC_PM750F)      || \
      defined(PROC_EP8641))
/** Use GCC's atomic builtins. Check for clang and ICC because they also define
 *  __GNUC__. The EP8572, EP8641, and the PM750F toolchain do not support
 *  atomic builtins.
 */
#define NCP_TASK_INC_GLOBAL_STAT(_thisStat) {                                       \
    if (NULL != pNcpTaskSwState)                                                    \
    {                                                                               \
        __sync_fetch_and_add(&pNcpTaskSwState->taskStats.stat_##_thisStat, 1);      \
    }                                                                               \
}
#else
   
/* TODO: Take a lock here?   What platforms do not support GCC atomic builtins? */
            
#define NCP_TASK_INC_GLOBAL_STAT(_thisStat) { if (NULL != pNcpTaskSwState) { pNcpTaskSwState->taskStats.stat_##_thisStat ++; }}     
    
#endif
#else
#define NCP_TASK_INC_STAT(_pTqs, _thisStat)
#define NCP_TASK_INC_ERROR_STAT_VIA_PTQS(_pTqs, _thisStat)
#define NCP_TASK_INC_ERROR_STAT_VIA_PTQSHDL(_pTqsHdl, _thisStat)
#define NCP_TASK_ADD_STAT(_pTqs, _thisStat, _val) 
#define NCP_TASK_ADD_TXSTAT(_pTqs, _thisStat, _txq, _val)
#define NCP_TASK_INC_GLOBAL_STAT(_thisStat)
#endif /* NCP_TASK_COLLECT_STATS */

#include "uboot/ncp_task_pvt_funcs.h"
#include "uboot/ncp_ncav3_ext.h"

ncp_st_t
ncp_task_init_sw_state(
    ncp_t *ncp);

ncp_st_t
ncp_ncav3_get_pcq_info(
    ncp_t *ncp,
    ncp_uint32_t tqsId,
    ncp_ncav3_pcq_type_t type,
    ncp_uint8_t opcqIndex,
    ncp_uint8_t poolId,
    ncp_uint8_t bufSizeBits,
    ncp_task_pcq_t *pcq);

ncp_st_t
ncp_task_initialize_tqs_state(
    ncp_t *ncp,
    int    tqsId);

ncp_st_t
ncp_ncav3_get_queue_profile_from_name(
    ncp_task_resource_name_t       *name,
    ncp_ncav3_nca_queue_profile_t **queueProfile);

ncp_bool_t
ncp_dev_ncav3_ipcq_condition_met(
    ncp_uint32_t tqsId,
    ncp_st_t *ncpStatus);

ncp_bool_t
ncp_dev_ncav3_opcq_condition_met(
    ncp_uint32_t tqsId,
    ncp_uint32_t queueId,
    ncp_st_t *ncpStatus);

ncp_st_t
ncp_task_register_ncav3_interrupts(
    ncp_dev_hdl_t devHdl,
    ncp_uint64_t  activeTQSMask);

ncp_st_t
ncp_task_initialize_tbr_arrays(void);

ncp_st_t
ncp_task_tbr_remove_from_cpupool_tqs_list(
    ncp_task_pvt_tqsHdl_data_t *pTqsHdl);

ncp_st_t
ncp_task_os_pid_store(ncp_task_process_info_t *pProcess);

ncp_st_t
ncp_task_os_pid_match_check(ncp_task_process_info_t *pProcess, ncp_bool_t expectedResult, ncp_st_t specificError);

ncp_st_t
ncp_task_v3_create_lock(ncp_task_v3_mutex_hdl_t *pLock,
                        runtime_mutex_attr_state_t *attr);

ncp_st_t
ncp_task_v3_destroy_lock(ncp_task_v3_mutex_hdl_t *pLock);

ncp_st_t
ncp_task_tqs_create_locks(int tqsId, runtime_mutex_attr_state_t *mtxAttr);

ncp_st_t
ncp_task_tqs_destroy_locks(int tqsId);

ncp_st_t
ncp_task_tqs_cleanup_locks(int tqsId);

#if (1 == NCP_TASK_USE_BARRIER_FOR_TASK_RECV)
#define NCP_ITASK_SYSMEM_BARRIER() NCP_SYSMEM_BARRIER()
#define NCP_ADDR_DEPENDENCY_TMPVAR_DECL(tmp_isZero)
#define NCP_TASK_TASKADDR64_GET(_pQueueEntry, _tmp_isZero) (_pQueueEntry->taskAddress)
#define NCP_TASK_PRODUCER_IDX_GET(_pPCQ, _tmp_isZero) (*(_pPCQ)->pProducerIdx)
#else /* NCP_TASK_USE_BARRIER_FOR_TASK_RECV */
#if defined(PROC_ARMA53)
#define NCP_TASK_ASM_SET_TMP_ISZERO_TO_ZERO(_tmp_isZero) \
   __asm__ __volatile__ ("and %0, %1, xzr" : "=r" (_tmp_isZero) : "r" (_tmp_isZero) : "memory")
#else
   /* Task I/O does not run on this platform,  no need to perform a guaranteed zero - just don't break build */
#define NCP_TASK_ASM_SET_TMP_ISZERO_TO_ZERO(_tmp_isZero) \
   _tmp_isZero = (ncp_uintptr_t)0;   
#endif
#define NCP_ITASK_SYSMEM_BARRIER()
#define NCP_ADDR_DEPENDENCY_TMPVAR_DECL(tmp_isZero) \
    volatile ncp_uintptr_t tmp_isZero;
#define NCP_TASK_TASKADDR64_GET(_pQueueEntry, _tmp_isZero)                \
({      /* for zero in a way compiler will not optimize out! */           \
        NCP_TASK_ASM_SET_TMP_ISZERO_TO_ZERO(_tmp_isZero);                 \
        ((_pQueueEntry + _tmp_isZero)->taskAddress);  /* result */        \
})
#define NCP_TASK_PRODUCER_IDX_GET(_pPCQ, _tmp_isZero) (_tmp_isZero = (*(_pPCQ)->pProducerIdx))
#endif /* NCP_TASK_USE_BARRIER_FOR_TASK_RECV */

/*
 * Swap if BIG_ENDIAN.
 * Socket layer provides the byte swap on little endian platforms (x86).
 */
#if !defined(NCP_BIG_ENDIAN) || defined(NCP_DEV_SOCKET) 
#define SWAP_16(n)    (n)
#define SWAP_32(n)    (n)
#define SWAP_64(n)    (n)
#else
#ifdef NCP_PLX
#if __GNUC__ == 4 && __GNUC_MINOR__ > 3 
#define SWAP_16(n)     (__builtin_bswap32(n)>> 16)
#define SWAP_32(n)      __builtin_bswap32(n)
#define SWAP_64(n)      __builtin_bswap64(n)
#else
#define SWAP_16(n)     NCP_ENDIAN_SWAP_16(n)
#define SWAP_32(n)     NCP_ENDIAN_SWAP_32(n)
#define SWAP_64(n)     NCP_ENDIAN_SWAP_64(n)
#endif
#else
#define SWAP_16(n)     NCP_ENDIAN_SWAP_16(n)
#define SWAP_32(n)     NCP_ENDIAN_SWAP_32(n)
#define SWAP_64(n)     NCP_ENDIAN_SWAP_64(n)
#endif
#endif


/* =========================================
 * Process-local state (globals)
 * =========================================
 */
#ifdef NCP_TASK_NCA_GLOBALS
#if defined(CONFIG_EIOA_BIG_STRUCT_IN_BSS)
ncp_task_swState_t   pNcpTaskSwState_in_bss __attribute__((section(".bss")));
#endif
ncp_task_swState_t  *pNcpTaskSwState;        /* SW State */
void                *pNcpTaskDomainBundle = NULL;   /* HW region */
ncp_uint32_t         ncpTaskDomainBundleMapCnt = 0;
ncp_uint32_t         ncpTaskPoolMapCnt[NCP_NCAV3_NUM_TASK_MEMORY_POOLS] = {0};
ncp_hdl_t            myNcpHdl=NULL;
ncp_dev_hdl_t        myDevHdl=NULL;
#else
extern ncp_task_swState_t  *pNcpTaskSwState;
extern void                *pNcpTaskDomainBundle;
extern ncp_uint32_t         ncpTaskDomainBundleMapCnt;
extern ncp_uint32_t         ncpTaskPoolMapCnt[];
extern ncp_hdl_t            myNcpHdl;
extern ncp_dev_hdl_t        myDevHdl;
#endif




#ifdef __cplusplus
}
#endif
#endif /* __NCP_TASK_PVT_H__ */

