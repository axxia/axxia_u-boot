/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2017, Intel Corporation.                        *
 **                                                                       *
 **************************************************************************/

/*! @file      ncp_task.h
 *
 *  @brief     Task I/O APIs
 *
 *  @addtogroup _taskV3_ Task Management
 *             
 *  @details   This document discusses the APIs for, and high level design of, the runtime software 
 *             interfaces that enable the host CPU to send tasks and receive tasks.
 *
 *             The CPU communicates with other engines in the system via tasks. The CPU sends and 
 *             receives tasks using very efficient, cacheable memory based producer-consumer style 
 *             DMA queues. These queues are called task queues and hardware support for task queues 
 *             is provided by the Nuevo CPU Adapter (NCA). 
 *
 *             Applications gain access to task queues by binding to thread queue sets (TQS).   Each TQS
 *             contains 1 input queue,   two output queues,   and up to 24 memory queues.   
 *             Input, or receive queues (iPCQ),   are used to receive tasks.   Output queues (oPCQ) are used 
 *             to send tasks, free tasks (shared pools),   refill the NCA's internal pool of receive buffers (CPU pools),
 *             and perform task completions for tasks received on an input queue that has been configured for
 *             manual task completion.   Memory queues (mPCQ) are accessed by the RTE when allocating buffers from a 
 *             shared pool (2..7).   There are 4 mPCQs per shared pool configured for the TQS,
 *             each serving one of the buffer sizes configured in the ASE (256B, 2K, 16K, and 64K).
 *
 * @note       It is invalid for a thread to use a TQS handle that was bound by a different thread.
 * 
 * @note       A TQS can be configured to use up to 6 shared pools (2..7),  or 1 of the 16 CPU pools (8..23).
 *             The RTE does not support a TQS configuration that includes both shared pools and CPU pools.
 *             If the TQS is configured to use a CPU pool,   the application shall use NCP_TASK_CPU_POOL_ALIAS for 
 *             poolId in all places where a pool ID is required; task header,  buffer management APIs, etc... .
 *
 * @note       Special CPU pool considerations:
 *             A portion of each CPU pool (rxReserve) must be provisioned to the NCA hardware in order for tasks to be received
 *             on the rx queue associated with a TQS configured to use a CPU pool.   The percentage,   or number of buffers, of
 *             each buffer size is specified in the ASE.    The RTE will supply the NCA with its initial allotment of receive buffers
 *             for each pool at config time.    Applications are responsible for replenishing receive buffers that are consumed by 
 *             the NCA when receiving tasks.   Each task received will be composed of between 1 and 7 task buffers.   If combinedHeader is
 *             FALSE,   then the number of buffers comprising a task is 1 (for the header) plus taskHeader->ptrCnt.   If combinedHeader
 *             is TRUE,  then the number of buffers comprising a task is equal to taskHeader->ptrCnt.   Not only must the total number of 
 *             buffers received be replenished by the application,   but the buffers that are replenished (refilled) must be of the same size
 *             as those buffers that were consumed.   The RTE provides an API to map a buffer to its poolId and size.    CPU pool receive
 *             buffer refills can be accomplished by using one or more of the following APIs;   ncp_task_send,   ncp_task_free,   ncp_task_refill,
 *             or ncp_task_buffer_refill.   See the descriptions for each of these APIs for documentation on which parameters control whether
 *             a task or buffers will be used to refill the NCA's internal pool of receive buffers.
 * 
 * @note       Task completion considerations: It does not make sense for a TQS to be configured to share its rxQ if the rxQ is configured to
 *             to use either manual or auto_deferred task completion modes.    Additionally,   using auto_deferred completion mode may impact
 *             the rate at which the NCA can fill the rxQ,   thereby reducing the number of tasks received per call to ncp_task_recv,   or 
 *             increasing the number of times that the RTE software sees the rxQ as empty.   Both of the previous potential side effects of 
 *             auto_deferred completion mode would therefore imply that auto_deferred mode should only be used where required.    The auto_immediate 
 *             task completion should always be selected when the incoming tasks are not ordered or atomic,   since it will provide for the best
 *             performance when tasks are not ordered or atomic.
 *
 *
 * @note       If an API returns an error status,   then all output (returned) parameter values are undefined and
 *             must not be used.   The return status NCP_ST_SUCCESS signifies success.   Some status codes convey information,
 *             and are not to be treated as errors; NCP_ST_TASK_SEND_QUEUE_FULL,  NCP_ST_TASK_RECV_QUEUE_EMPTY, NCP_ST_TASK_PARTIAL_SUCCESS, ... .
 * 
 *  @{
 */
 
#ifndef __NCP_TASK_H__
#define __NCP_TASK_H__

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *  @brief NCP_TASK_MAX_RESOURCE_NAME_LEN: Constant equal to the maximum
 *      length of a string used to hold the name of a Task I/O resource, such
 *      as a thread queue set name or a queue name. Note that Task I/O resource
 *      names are C strings, and thus one character is reserved for the null
 *      terminator. This limits the usable text length of the name to 95
 *      characters.
 */
#define NCP_TASK_MAX_RESOURCE_NAME_LEN      96
/*!
 *  @brief NCP_TASK_PARAM_SIZE_BYTES: Constant equal to the size of the task parameters array
 *         in the task header data structure.
 */
#define NCP_TASK_PARAM_SIZE_BYTES           32
/*!
 *  @brief NCP_NCAV3_NUM_SHARED_POOLS: Constant equal to the number of shared pools (2..7) available for use
 *         by Task I/O client applications.
 */
#define NCP_NCAV3_NUM_SHARED_POOLS          6 /* Just CPU usable shared pools */
/*!
 *  @brief NCP_NCAV3_NUM_SHARED_POOLS: Constant equal to the total number of shared pools (2..7) available for use
 *         by Task I/O client applications.   Typically used for data structure sizing withing an application.
 */
#define NCP_NCAV3_MAX_SHARED_POOLS          8 /* 0 is CPU alias, then 2..7 */
/*!
 *  @brief NCP_TASK_TXQ_0: Each TQS has 2 TX queues.   This define can be used to facilitate more readable code when specifying
 *         one of these two queues,   especially where txQueueId must be supplied to a Task I/O API.
 */
#define NCP_TASK_TXQ_0 0
/*!
 *  @brief NCP_TASK_TXQ_1: Each TQS has 2 TX queues.   This define can be used to facilitate more readable code when specifying
 *         one of these two queues,   especially where txQueueId must be supplied to a Task I/O API.
 */
#define NCP_TASK_TXQ_1 1
/*!
 *  @brief NCP_TASK_CPU_POOL_ALIAS: If a TQS is configured to use a CPU pool (8..23),   then the application must use this alias 
 *         wherever poolId is required in a task header (headerPool, pool0, pool1, ..., pool5),   or where a poolId is required by a
 *         Task I/O API.   Similarly,   received tasks that contain buffers belong to a CPU pool, will have the poolId fields in the
 *         task header set to NCP_TASK_CPU_POOL_ALIAS.
 */
#define NCP_TASK_CPU_POOL_ALIAS 0

typedef void *ncp_task_tqs_hdl_t;

typedef ncp_uint16_t ncp_task_pid_t;

typedef struct ncp_task_resource_name_s {
    char name[NCP_TASK_MAX_RESOURCE_NAME_LEN];
}  ncp_task_resource_name_t;  

/*!
 *  @brief ncp_task_header_t: A task header is used to describe all sent and
 *      received tasks. Fields in the task header corresponding to a received
 *      task are set by hardware. All fields in the task header associated with
 *      a task send must be set by the application!
 *
 *      Each PDU in a task has an mref bit. This bit indicates whether there are
 *      one (mref == 0) or more (mref == 1) references t to this buffer in the
 *      system.  When sending or freeing, all allocated tasks should have an
 *      mref of 0, while all buffers gotten from an iPCQ should have the same
 *      mref value as when the task was received.
 */
typedef struct ncp_task_header_s
{
#ifdef NCP_BIG_ENDIAN
    /* Bytes 0-7 */
    ncp_uint32_t        templateId:8;     /*!< iPCQ: template ID,
                                               oPCQ: virtual pipeline ID */
    ncp_uint32_t        ID:24;            /*!< iPCQ: GID[7:0],
                                                      {3’d0, Gen, 1’d0, Priority[2:0]},
                                                      QID[7:0]
                                               oPCQ: virtualFlowIndex*/
    ncp_uint32_t        pduSegSize1:16;   /*!< Size (in bytes) of the second PDU */
    ncp_uint32_t        pduSegSize0:16;   /*!< Size (in bytes) of the first PDU*/
    /* Bytes 8-15 */
    ncp_uint32_t        reserved2:4;
    ncp_uint32_t        pool0Mref:1;      /*!< Mref bit for the first PDU */
    ncp_uint32_t        pool0:3;          /*!< The first PDU's pool */
    ncp_uint32_t        pool2Mref:1;      /*!< Mref bit for the third PDU*/
    ncp_uint32_t        pool2:3;          /*!< The third PDU's pool */
    ncp_uint32_t        pool1Mref:1;      /*!< Mref bit for the second PDU*/
    ncp_uint32_t        pool1:3;          /*!< The second PDU's pool */
    ncp_uint32_t        pool4Mref:1;      /*!< Mref bit for the fifth PDU*/
    ncp_uint32_t        pool4:3;          /*!< The fifth PDU's pool */
    ncp_uint32_t        pool3Mref:1;      /*!< Mref bit for the fourth PDU*/
    ncp_uint32_t        pool3:3;          /*!< The fourth PDU's pool */
    ncp_uint32_t        debugValid:1;     /*!< Enable/disable debug data */
    ncp_uint32_t        priority:3;       /*!< Task priority */
    ncp_uint32_t        pool5Mref:1;      /*!< Mref bit for the sixth PDU*/
    ncp_uint32_t        pool5:3;          /*!< The sixth PDU's pool */
    ncp_uint32_t        pduSize:16;       /*!< The sum of the PDU sizes
                                               (not including the header if combined) */
    ncp_uint32_t        reserved1:5;
    ncp_uint32_t        ptrCnt:3;         /*!< The number of PDUs in this task */
    ncp_uint32_t        combinedHeader:1; /*!< True if the first PDU contains the header,
                                                false if the header is in a separate buffer */
    ncp_uint32_t        reserved0:3;
    ncp_uint32_t        headerPoolMref:1; /*!< Combined or separate header */
    ncp_uint32_t        headerPool:3;     /*!< The header buffer's pool */

    /* Bytes 16-47 */
    ncp_uint8_t         params[32];       /*!< Task parameters */

    /* Bytes 52-55 */
    ncp_uint64_t        pduSegAddr0;      /*!< The address of the first PDU */

    /* Bytes 60-63 */
    ncp_uint64_t        pduSegAddr1;      /*!< The address of the second PDU */

    /* Bytes 64-65 */
    ncp_uint16_t        pduSegSize3;      /*!< The size of the fourth PDU */
    /* Bytes 66-67 */
    ncp_uint16_t        pduSegSize2;      /*!< The size of the third PDU */
    /* Bytes 68-69 */
    ncp_uint16_t        pduSegSize5;      /*!< The size of the sixth PDU */
    /* Bytes 70-71 */
    ncp_uint16_t        pduSegSize4;      /*!< The size of the fifth PDU */

    /* Bytes 76-79 */
    ncp_uint64_t        pduSegAddr2;      /*!< The address of the third PDU */

    /* Bytes 84-87 */
    ncp_uint64_t        pduSegAddr3;      /*!< The address of the fourth PDU */

    /* Bytes 92-95 */
    ncp_uint64_t        pduSegAddr4;      /*!< The address of the fifth PDU */

    /* Bytes 100-103 */
    ncp_uint64_t        pduSegAddr5;      /*!< The address of the sixth PDU */

    /* Bytes 104-111 */
    ncp_uint8_t         debugData[8];     /*!< Debug data */
#else
    /* Bytes 0-7 */
    ncp_uint32_t        pduSegSize0:16;   /*!< Size (in bytes) of the first PDU*/
    ncp_uint32_t        pduSegSize1:16;   /*!< Size (in bytes) of the second PDU */
    ncp_uint32_t        ID:24;            /*!< iPCQ: GID[7:0],
                                                      {3’d0, Gen, 1’d0, Priority[2:0]},
                                                      QID[7:0]
                                               oPCQ: virtualFlowIndex*/
    ncp_uint32_t        templateId:8;     /*!< iPCQ: template ID,
                                               oPCQ: virtual pipeline ID */

    /* Bytes 8-15 */
    ncp_uint64_t        headerPool:3;     /*!< The header buffer's pool */
    ncp_uint64_t        headerPoolMref:1; /*!< Combined or separate header */
    ncp_uint64_t        reserved0:3;
    ncp_uint64_t        combinedHeader:1; /*!< True if the first PDU contains the header,
                                                false if the header is in a separate buffer */
    ncp_uint32_t        ptrCnt:3;         /*!< The number of PDUs in this task */
    ncp_uint32_t        reserved1:5;
    ncp_uint32_t        pduSize:16;       /*!< The sum of the PDU sizes
                                               (not including the header if combined) */
    ncp_uint32_t        pool5:3;          /*!< The sixth PDU's pool */
    ncp_uint32_t        pool5Mref:1;      /*!< Mref bit for the sixth PDU*/
    ncp_uint32_t        priority:3;       /*!< Task priority */
    ncp_uint32_t        debugValid:1;     /*!< Enable/disable debug data */
    ncp_uint32_t        pool3:3;          /*!< The fourth PDU's pool */
    ncp_uint32_t        pool3Mref:1;      /*!< Mref bit for the fourth PDU*/
    ncp_uint32_t        pool4:3;          /*!< The fifth PDU's pool */
    ncp_uint32_t        pool4Mref:1;      /*!< Mref bit for the fifth PDU*/
    ncp_uint32_t        pool1:3;          /*!< The second PDU's pool */
    ncp_uint32_t        pool1Mref:1;      /*!< Mref bit for the second PDU*/
    ncp_uint32_t        pool2:3;          /*!< The third PDU's pool */
    ncp_uint32_t        pool2Mref:1;      /*!< Mref bit for the third PDU*/
    ncp_uint32_t        pool0:3;          /*!< The first PDU's pool */
    ncp_uint32_t        pool0Mref:1;      /*!< Mref bit for the first PDU */
    ncp_uint32_t        reserved2:4;

    /* Bytes 16-47 */
    ncp_uint8_t         params[32];       /*!< Task parameters */

    /* Bytes 48-51 */
    ncp_uint64_t        pduSegAddr0;      /*!< The address of the first PDU */

    /* Bytes 56-59 */
    ncp_uint64_t        pduSegAddr1;      /*!< The address of the second PDU */

    /* Bytes 64-65 */
    ncp_uint16_t        pduSegSize4;      /*!< The size of the fifth PDU */
    /* Bytes 66-67 */
    ncp_uint16_t        pduSegSize5;      /*!< The size of the sixth PDU */
    /* Bytes 68-69 */
    ncp_uint16_t        pduSegSize2;      /*!< The size of the third PDU */
    /* Bytes 70-71 */
    ncp_uint16_t        pduSegSize3;      /*!< The size of the fourth PDU */

    /* Bytes 72-75 */
    ncp_uint64_t        pduSegAddr2;      /*!< The address of the third PDU */

    /* Bytes 80-83 */
    ncp_uint64_t        pduSegAddr3;      /*!< The address of the fourth PDU */

    /* Bytes 88-91 */
    ncp_uint64_t        pduSegAddr4;      /*!< The address of the fifth PDU */

    /* Bytes 96-99 */
    ncp_uint64_t        pduSegAddr5;      /*!< The address of the sixth PDU */

    /* Bytes 104-111 */
    ncp_uint8_t         debugData[8];     /*!< Debug data */
#endif
} ncp_task_header_t;

/*!
 *  @brief ncp_task_ipcq_header_id_t: This structure contains the sub-fields
 *          that comprise a task header ID field. This only applies to headers
 *          received on an iPCQ. For outgoing (oPCQ) task headers, the ID
 *          field contains the 24-bit virtualFlowIndex.
 */
typedef struct {
#ifdef NCP_BIG_ENDIAN
    ncp_uint32_t gid:8;
    ncp_uint32_t reserved0:3;
    ncp_uint32_t generation:1;
    ncp_uint32_t reserved1:1;
    ncp_uint32_t priority:3;
    ncp_uint32_t qid:8;
#else
    ncp_uint32_t qid:8;
    ncp_uint32_t priority:3;
    ncp_uint32_t reserved1:1;
    ncp_uint32_t generation:1;
    ncp_uint32_t reserved0:3;
    ncp_uint32_t gid:8;
#endif
} ncp_task_ipcq_header_id_t;

/*!
 *  @brief ncp_task_tqs_shared_t: This data structure is used when configuring a TQS.   It describes the expected application
 *         sharing model that will be employed at runtime.   The RTE compares the ncp_task_tqs_usage_t flags supplied at ncp_task_tqs_bind
 *         to validate that the sharing model is not being violated.   The RTE will return an error if it detects a sharing violation at TQS
 *         bind time.
 */
typedef struct {
    ncp_bool_t sharedRxQueue;
    ncp_bool_t sharedTxQueue0;
    ncp_bool_t sharedTxQueue1;
    ncp_bool_t sharedAllocator[NCP_NCAV3_MAX_SHARED_POOLS];
} ncp_task_tqs_shared_t;

/*!
 *  @brief ncp_task_tqs_usage_t: TQS usage flags, used to enforce exclusive
 *              access to TQS structures. The useAllocator array is used to
 *              indicate which shared pool allocators (i.e. mPCQs) will be
 *              used by the TQS.
 */
typedef struct {
    ncp_bool_t useRxQueue;
    ncp_bool_t useTxQueue0;
    ncp_bool_t useTxQueue1;
    ncp_bool_t useAllocator[NCP_NCAV3_MAX_SHARED_POOLS];
} ncp_task_tqs_usage_t;

/*!
 *  @brief ncp_task_send_done_fn_t: task send done callback function signature.
 */
typedef void (*ncp_task_send_done_fn_t)(
    void *sendDoneFuncArg,
	ncp_task_header_t *taskHeader);

/*!
 *  @brief ncp_task_send_meta_t: metadata for sending a task
 */
typedef struct {
    ncp_task_send_done_fn_t sendDoneFn; 
    void *sendDoneArg;
    ncp_bool_t freeHeader;
    ncp_bool_t freeDataPointers;
    ncp_task_header_t *taskHeader;
    ncp_bool_t issueCompletion;
} ncp_task_send_meta_t;

/*!
 *  @brief ncp_task_free_done_fn_t: task free done callback function signature.
 */
typedef void (*ncp_task_free_done_fn_t)(
    void *freeDoneFuncArg);          
	
/*!
 *  @brief ncp_task_free_meta_t: metadata for freeing a task
 */
typedef struct {
    ncp_task_free_done_fn_t freeDoneFn; 
    void *freeDoneArg;
    ncp_task_header_t *task;
    ncp_bool_t freeHeader;
    ncp_bool_t issueCompletion;
} ncp_task_free_meta_t;

/*!
 *  @brief ncp_task_buffer_desc_t: task buffer descriptor
 */
typedef struct {
     void *taskBuffer;
     ncp_bool_t mrefBitIsSet;
     ncp_uint8_t poolId;
} ncp_task_buffer_desc_t;

/*!
 *  @brief ncp_task_buffer_transfer_done_fn_t: task buffer quota transfer done
 *              callback function signature.
 */
typedef void (*ncp_task_buffer_transfer_done_fn_t)(
    void *transferDoneArg,
    void *taskBuffer,
    ncp_bool_t mrefBitIsSet,
    ncp_uint8_t poolId);

/*!
 *  @brief ncp_task_transfer_done_fn_t: task quota transfer done callback
 *              function signature.
 */
typedef void (*ncp_task_transfer_done_fn_t)(
    void *transferDoneArg,
    void *taskBuffer);

/*!
 *  @brief ncp_task_buffer_refCnt_inc_done_fn_t: buffer reference count
 *              increment done callback function signature.
 */
typedef void (*ncp_task_buffer_refCnt_inc_done_fn_t)(
    void *refCntIncDoneArg,
    void *taskBuffer,
    ncp_bool_t mrefBitIsSet,
    ncp_uint8_t poolId);

/*!
 *  @brief ncp_task_refCnt_inc_done_fn_t: task reference count increment done
 *              callback function signature.
 */
typedef void (*ncp_task_refCnt_inc_done_fn_t)(
    void *refCntIncDoneArg,
    void *taskBuffer);

/*!
 *  @brief ncp_task_queue_group_set_t: Queue group configuration structure
 */
typedef struct {
    ncp_uint32_t queueGroup;
    ncp_uint32_t queueGroupPriority;
    ncp_st_t     queueGroupStatus;
} ncp_task_queue_group_set_t;

/*!
 *  @brief ncp_task_recv_queue_type_t: Receive queue scheduling types
 */
typedef enum {
    UNORDERED = 0,
    ORDERED,
    UNSCHEDULED
} ncp_ncav3_recv_queue_type_t;

/*!
 *  @brief ncp_task_execution_modes_t: TQS execution modes
 */
typedef enum
{
    NCP_TASK_STATS_MODE_RESERVED=0,
    NCP_TASK_STATS_MODE_USER,
    NCP_TASK_STATS_MODE_KERNEL
}  ncp_task_execution_modes_t;

typedef ncp_uint64_t ncp_task_stat_entry_t;

/*!
 *  @brief ncp_task_global_stats_t: Global task I/O statistics.
 */
typedef struct {
    
    /*
     * API success stats that will always appear only in the global stats.
     * They cannot be tracked on a per TQS basis.
     */
     
    ncp_task_stat_entry_t stat_api_task_shutdown_ok;  
    ncp_task_stat_entry_t stat_api_task_shutdown_wait_ok;
    ncp_task_stat_entry_t stat_api_task_attach_ok;
    ncp_task_stat_entry_t stat_api_task_detach_ok;
    ncp_task_stat_entry_t stat_api_task_configure_ok;
    ncp_task_stat_entry_t stat_api_task_configure_flags_get_ok;
    ncp_task_stat_entry_t stat_api_task_nca_queue_configure_ok;
    ncp_task_stat_entry_t stat_api_task_nca_queue_disable_ok;
    ncp_task_stat_entry_t stat_api_task_nca_queue_enable_ok;
    ncp_task_stat_entry_t stat_api_task_tqs_queue_group_set_ok;
    ncp_task_stat_entry_t stat_api_task_tqs_queue_group_get_ok;
    ncp_task_stat_entry_t stat_api_task_nca_queue_group_set_ok;
    ncp_task_stat_entry_t stat_api_task_queue_group_membership_get_ok;
    ncp_task_stat_entry_t stat_api_task_queue_group_name_get_ok;
    ncp_task_stat_entry_t stat_api_task_tqs_name_get_ok;
    ncp_task_stat_entry_t stat_api_task_nca_queue_name_get_ok;
    ncp_task_stat_entry_t stat_api_task_queue_group_id_get_ok;
    ncp_task_stat_entry_t stat_api_task_tqs_id_get_ok;
    ncp_task_stat_entry_t stat_api_task_nca_queue_id_get_ok;
    ncp_task_stat_entry_t stat_api_task_cpu_app_profile_name_get_ok;
    ncp_task_stat_entry_t stat_api_task_cpu_app_profile_get_ok;
    ncp_task_stat_entry_t stat_api_task_cpu_app_profile_id_get_ok;
    ncp_task_stat_entry_t stat_api_task_nca_queue_profile_name_get_ok;
    ncp_task_stat_entry_t stat_api_task_nca_queue_profile_get_ok;
    ncp_task_stat_entry_t stat_api_task_nca_queue_profile_id_get_ok;
    ncp_task_stat_entry_t stat_api_task_tqs_cpu_affinity_get_ok;
    ncp_task_stat_entry_t stat_api_task_pool_name_get_ok;
    ncp_task_stat_entry_t stat_api_task_pool_id_get_ok;
    ncp_task_stat_entry_t stat_api_task_process_name_pid_get_ok;  
    ncp_task_stat_entry_t stat_api_task_unscheduled_queue_push_ok;
    ncp_task_stat_entry_t stat_api_task_unscheduled_queue_pop_ok;
    ncp_task_stat_entry_t stat_api_task_buffer_quota_transfer_ok;
    ncp_task_stat_entry_t stat_api_task_refCnt_increment_ok;
    ncp_task_stat_entry_t stat_api_task_buffer_refCnt_increment_ok;
    ncp_task_stat_entry_t stat_api_task_unscheduled_queue_depth_get_ok;
    ncp_task_stat_entry_t reserved_ok[16];  /* room to grow */
      
    /* 
     * API Error stats that will always show up in global stats.   These cannot be tracked
     * on a per TQS basis.
     */
    
    ncp_task_stat_entry_t stat_api_task_shutdown_err;    
    ncp_task_stat_entry_t stat_api_task_shutdown_wait_err;
    ncp_task_stat_entry_t stat_api_task_attach_err;
    ncp_task_stat_entry_t stat_api_task_detach_err;  
    ncp_task_stat_entry_t stat_api_task_configure_err;  
    ncp_task_stat_entry_t stat_api_task_configure_flags_get_err;
    ncp_task_stat_entry_t stat_api_task_nca_queue_configure_err;
    ncp_task_stat_entry_t stat_api_task_nca_queue_disable_err;
    ncp_task_stat_entry_t stat_api_task_nca_queue_enable_err;
    ncp_task_stat_entry_t stat_api_task_tqs_queue_group_set_err;
    ncp_task_stat_entry_t stat_api_task_tqs_queue_group_get_err;
    ncp_task_stat_entry_t stat_api_task_nca_queue_group_set_err;  
    ncp_task_stat_entry_t stat_api_task_queue_group_membership_get_err;
    ncp_task_stat_entry_t stat_api_task_queue_group_name_get_err;
    ncp_task_stat_entry_t stat_api_task_tqs_name_get_err;
    ncp_task_stat_entry_t stat_api_task_nca_queue_name_get_err;
    ncp_task_stat_entry_t stat_api_task_queue_group_id_get_err;
    ncp_task_stat_entry_t stat_api_task_tqs_id_get_err;
    ncp_task_stat_entry_t stat_api_task_nca_queue_id_get_err;
    ncp_task_stat_entry_t stat_api_task_cpu_app_profile_name_get_err;
    ncp_task_stat_entry_t stat_api_task_cpu_app_profile_get_err;
    ncp_task_stat_entry_t stat_api_task_cpu_app_profile_id_get_err;
    ncp_task_stat_entry_t stat_api_task_nca_queue_profile_name_get_err;
    ncp_task_stat_entry_t stat_api_task_nca_queue_profile_get_err;
    ncp_task_stat_entry_t stat_api_task_nca_queue_profile_id_get_err;
    ncp_task_stat_entry_t stat_api_task_tqs_cpu_affinity_get_err;
    ncp_task_stat_entry_t stat_api_task_pool_name_get_err;
    ncp_task_stat_entry_t stat_api_task_pool_id_get_err;
    ncp_task_stat_entry_t stat_api_task_process_name_pid_get_err; 
    ncp_task_stat_entry_t reserved_err[20];  /* room to grow */
    /* 
     * TQS-local Task API Error exception stats that could not be reported in 
     * the TQS-local stats due to invalid tqsHdl,  invalid tqsId, tqs not configured, etc...
     * These stats are *not* a cumulative total of the TQS-local stats!   
     */
    ncp_task_stat_entry_t stat_api_task_tqs_hdl_bind_err;    
    ncp_task_stat_entry_t stat_api_task_tqs_hdl_recover_err;     
    ncp_task_stat_entry_t stat_api_task_tqs_hdl_unbind_err;
    ncp_task_stat_entry_t stat_api_task_tqs_disable_err;           
    ncp_task_stat_entry_t stat_api_task_tqs_enable_err;    
    ncp_task_stat_entry_t stat_api_task_rx_queue_flush_err;
    ncp_task_stat_entry_t stat_api_task_tx_queue_flush_err;
    ncp_task_stat_entry_t stat_api_task_send_err; 
    ncp_task_stat_entry_t stat_api_task_recv_err;
    ncp_task_stat_entry_t stat_api_task_deferred_consume_err;
    ncp_task_stat_entry_t stat_api_task_complete_err;
    ncp_task_stat_entry_t stat_api_task_unscheduled_queue_push_err;
    ncp_task_stat_entry_t stat_api_task_unscheduled_queue_pop_err;
    ncp_task_stat_entry_t stat_api_task_buffer_alloc_err; 
    ncp_task_stat_entry_t stat_api_task_buffer_free_err; 
    ncp_task_stat_entry_t stat_api_task_free_err; 
    ncp_task_stat_entry_t stat_api_task_mmio_buffer_alloc_err;
    ncp_task_stat_entry_t stat_api_task_mmio_buffer_free_err;
    ncp_task_stat_entry_t stat_api_task_buffer_pool_get_err;      
    ncp_task_stat_entry_t stat_api_task_buffer_size_get_err;
    ncp_task_stat_entry_t stat_api_task_buffer_size_and_start_get_err;    
    ncp_task_stat_entry_t stat_api_task_buffer_refill_err;
    ncp_task_stat_entry_t stat_api_task_refill_err;
    ncp_task_stat_entry_t stat_api_task_quota_transfer_err;
    ncp_task_stat_entry_t stat_api_task_set_wait_profile_err; 
    ncp_task_stat_entry_t stat_api_task_tbr_task_take_err;
    ncp_task_stat_entry_t stat_api_task_tbr_buffer_take_err;
    ncp_task_stat_entry_t stat_api_task_task_give_err;
    ncp_task_stat_entry_t stat_api_task_tbr_buffer_give_err;   
    ncp_task_stat_entry_t stat_api_task_task_transfer_err;
    ncp_task_stat_entry_t stat_api_task_tbr_buffer_transfer_err; 
    ncp_task_stat_entry_t stat_api_task_tbr_buffer_ownership_get_err;      
    ncp_task_stat_entry_t stat_api_task_pid_get_err; 
    ncp_task_stat_entry_t stat_api_task_completion_mode_get_err;
    ncp_task_stat_entry_t stat_api_task_consumption_mode_get_err;        
    ncp_task_stat_entry_t stat_api_task_buffer_quota_transfer_err;
    ncp_task_stat_entry_t stat_api_task_refCnt_increment_err;
    ncp_task_stat_entry_t stat_api_task_buffer_refCnt_increment_err;
    ncp_task_stat_entry_t stat_api_task_unscheduled_queue_depth_get_err;
    ncp_task_stat_entry_t stat_api_task_tqs_shutdown_err;
    ncp_task_stat_entry_t reserved_failover[15];  /* room to grow */
        
} ncp_task_global_stats_t;

/*!
 *  @brief ncp_task_stats_t: Per-TQS task I/O statistics.
 */
typedef struct ncp_task_stats_s {
    /* TQS-local traffic related counters */
    ncp_task_stat_entry_t stat_RxQueueEmpty;
    ncp_task_stat_entry_t stat_RxTask;
    ncp_task_stat_entry_t stat_TX0_TxQueue_Full;
    ncp_task_stat_entry_t stat_TX1_TxQueue_Full;    
    ncp_task_stat_entry_t stat_TX0_TxTask;    
    ncp_task_stat_entry_t stat_TX1_TxTask;
    ncp_task_stat_entry_t stat_TX0_TaskCompletions;
    ncp_task_stat_entry_t stat_TX1_TaskCompletions;    
    ncp_task_stat_entry_t stat_BuffAllocs;
    ncp_task_stat_entry_t stat_TX0_BuffFrees;
    ncp_task_stat_entry_t stat_TX1_BuffFrees;    
    ncp_task_stat_entry_t stat_TX0_TaskFrees;
    ncp_task_stat_entry_t stat_TX1_TaskFrees;    
    ncp_task_stat_entry_t stat_TX0_BuffRefills;
    ncp_task_stat_entry_t stat_TX1_BuffRefills;  
    ncp_task_stat_entry_t reserved_traffic[20];  /* room to grow */
    
    /* TQS-local Task API Stats - SUCCESS */
    ncp_task_stat_entry_t stat_api_task_tqs_hdl_bind_ok;
    ncp_task_stat_entry_t stat_api_task_tqs_hdl_recover_ok;    
    ncp_task_stat_entry_t stat_api_task_tqs_hdl_unbind_ok;
    ncp_task_stat_entry_t stat_api_task_tqs_disable_ok;
    ncp_task_stat_entry_t stat_api_task_tqs_enable_ok;
    ncp_task_stat_entry_t stat_api_task_rx_queue_flush_ok;
    ncp_task_stat_entry_t stat_api_task_tx_queue_flush_ok;
    ncp_task_stat_entry_t stat_api_task_send_ok;
    ncp_task_stat_entry_t stat_api_task_recv_ok;
    ncp_task_stat_entry_t stat_api_task_deferred_consume_ok;
    ncp_task_stat_entry_t stat_api_task_complete_ok;
    ncp_task_stat_entry_t stat_api_task_buffer_alloc_ok;    
    ncp_task_stat_entry_t stat_api_task_buffer_free_ok; 
    ncp_task_stat_entry_t stat_api_task_free_ok;
    ncp_task_stat_entry_t stat_api_task_mmio_buffer_alloc_ok;
    ncp_task_stat_entry_t stat_api_task_mmio_buffer_free_ok;   
    ncp_task_stat_entry_t stat_api_task_buffer_pool_get_ok;
    ncp_task_stat_entry_t stat_api_task_buffer_size_get_ok;
    ncp_task_stat_entry_t stat_api_task_buffer_size_and_start_get_ok;    
    ncp_task_stat_entry_t stat_api_task_buffer_refill_ok; 
    ncp_task_stat_entry_t stat_api_task_refill_ok;
    ncp_task_stat_entry_t stat_api_task_quota_transfer_ok;
    ncp_task_stat_entry_t stat_api_task_set_wait_profile_ok;
    ncp_task_stat_entry_t stat_api_task_tbr_task_take_ok;
    ncp_task_stat_entry_t stat_api_task_tbr_buffer_take_ok;
    ncp_task_stat_entry_t stat_api_task_task_give_ok;
    ncp_task_stat_entry_t stat_api_task_tbr_buffer_give_ok;
    ncp_task_stat_entry_t stat_api_task_task_transfer_ok;
    ncp_task_stat_entry_t stat_api_task_tbr_buffer_transfer_ok; 
    ncp_task_stat_entry_t stat_api_task_tbr_buffer_ownership_get_ok;    
    ncp_task_stat_entry_t stat_api_task_pid_get_ok; 
    ncp_task_stat_entry_t stat_api_task_completion_mode_get_ok;
    ncp_task_stat_entry_t stat_api_task_consumption_mode_get_ok;        
    ncp_task_stat_entry_t stat_api_task_buffer_quota_transfer_ok;
    ncp_task_stat_entry_t stat_api_task_refCnt_increment_ok;
    ncp_task_stat_entry_t stat_api_task_buffer_refCnt_increment_ok;
    ncp_task_stat_entry_t stat_api_task_tqs_shutdown_ok;
    ncp_task_stat_entry_t reserved_ok[16];  /* room to grow */

        
    /* TQS-local Task API Stats - ERROR */
    ncp_task_stat_entry_t stat_api_task_tqs_hdl_bind_err;    
    ncp_task_stat_entry_t stat_api_task_tqs_hdl_recover_err;    
    ncp_task_stat_entry_t stat_api_task_tqs_hdl_unbind_err;
    ncp_task_stat_entry_t stat_api_task_tqs_disable_err;           
    ncp_task_stat_entry_t stat_api_task_tqs_enable_err;    
    ncp_task_stat_entry_t stat_api_task_rx_queue_flush_err;
    ncp_task_stat_entry_t stat_api_task_tx_queue_flush_err;
    ncp_task_stat_entry_t stat_api_task_send_err; 
    ncp_task_stat_entry_t stat_api_task_recv_err;
    ncp_task_stat_entry_t stat_api_task_deferred_consume_err;
    ncp_task_stat_entry_t stat_api_task_complete_err;
    ncp_task_stat_entry_t stat_api_task_buffer_alloc_err; 
    ncp_task_stat_entry_t stat_api_task_buffer_free_err; 
    ncp_task_stat_entry_t stat_api_task_free_err; 
    ncp_task_stat_entry_t stat_api_task_mmio_buffer_alloc_err;
    ncp_task_stat_entry_t stat_api_task_mmio_buffer_free_err;
    ncp_task_stat_entry_t stat_api_task_buffer_pool_get_err;      
    ncp_task_stat_entry_t stat_api_task_buffer_size_get_err;
    ncp_task_stat_entry_t stat_api_task_buffer_size_and_start_get_err;    
    ncp_task_stat_entry_t stat_api_task_buffer_refill_err;
    ncp_task_stat_entry_t stat_api_task_refill_err;
    ncp_task_stat_entry_t stat_api_task_quota_transfer_err;
    ncp_task_stat_entry_t stat_api_task_set_wait_profile_err;
    ncp_task_stat_entry_t stat_api_task_tbr_task_take_err;
    ncp_task_stat_entry_t stat_api_task_tbr_buffer_take_err;
    ncp_task_stat_entry_t stat_api_task_task_give_err;
    ncp_task_stat_entry_t stat_api_task_tbr_buffer_give_err;            
    ncp_task_stat_entry_t stat_api_task_task_transfer_err;
    ncp_task_stat_entry_t stat_api_task_tbr_buffer_transfer_err; 
    ncp_task_stat_entry_t stat_api_task_tbr_buffer_ownership_get_err;     
    ncp_task_stat_entry_t stat_api_task_pid_get_err; 
    ncp_task_stat_entry_t stat_api_task_completion_mode_get_err;
    ncp_task_stat_entry_t stat_api_task_consumption_mode_get_err;         
    ncp_task_stat_entry_t stat_api_task_buffer_quota_transfer_err;
    ncp_task_stat_entry_t stat_api_task_refCnt_increment_err;
    ncp_task_stat_entry_t stat_api_task_buffer_refCnt_increment_err;
    ncp_task_stat_entry_t stat_api_task_tqs_shutdown_err;
    ncp_task_stat_entry_t reserved_err[16];  /* room to grow */
               
} NCP_COMPAT_PACKED ncp_task_stats_t;



/*! 
 *  @brief ncp_task_api_class_t: an enum for the wait profile classes.
*/
typedef enum {
NCP_TASK_API_CLASS_RECV=0,
NCP_TASK_API_CLASS_RECV_QUEUE_FLUSH,
NCP_TASK_API_CLASS_SEND_TXQ0,
NCP_TASK_API_CLASS_SEND_TXQ1,
NCP_TASK_API_CLASS_ALLOC,
NCP_TASK_API_CLASS_REFILL_TXQ0,
NCP_TASK_API_CLASS_REFILL_TXQ1,
NCP_TASK_API_CLASS_FREE_TXQ0,
NCP_TASK_API_CLASS_FREE_TXQ1 /* Must be last! */
} ncp_task_api_class_t;

/*! 
 *  @brief ncp_task_poll_type_t: an enum for the wait profile polling types.
*/
typedef enum {
NCP_TASK_POLL_TYPE_SLEEP_POLL=0,
NCP_TASK_POLL_TYPE_HARD_POLL
} ncp_task_poll_type_t;

/*! 
 *  @brief ncp_task_wait_profile_type_t: an enum for the wait profile types.
*/
typedef enum {
NCP_TASK_WAIT_ISR=0,
NCP_TASK_WAIT_WFI,     /* Valid only for receive API(s) */
NCP_TASK_WAIT_TIMEOUT
} ncp_task_wait_profile_type_t;


/*! 
 *  @brief ncp_task_nca_queue_sched_params_t: NCA queue scheduling parameters.
 */
typedef struct {
    ncp_int32_t priority;
    ncp_int32_t wrrWeight;
} ncp_task_nca_queue_sched_params_t;

/*!
 *  @brief ncp_task_qpm_stats_t: NCA QPM queue exception counters.
 */
typedef struct {
    ncp_uint64_t numFullQueueExceptions;
    ncp_uint64_t numEmptyQueueExceptions;
    ncp_uint64_t numOverflowExceptions;
} ncp_task_qpm_stats_t;

/* ============================== APIs ============================== */

/*!
 * @fn ncp_st_t ncp_task_tqs_configure(
 *  ncp_hdl_t ncpHdl,   
 *  ncp_uint32_t tqsId,
 *  ncp_task_resource_name_t *tqsName,
 *  ncp_task_resource_name_t *appProfileName,
 *  ncp_task_tqs_shared_t *flags,
 *  ncp_uint32_t memoryQuotaGroupId);
 *
 * @brief   This API dynamically configures a thread queue set.
 *          If this TQS is configured in ASE, this function need only be called to change the configuration.
 *          Reconfiguration is possible if all threads have unbound the TQS, on a warm restart, or if the chip is reconfigured.
 *          The shared arguments tell the RTE whether locks are required when accessing the resource.
 *          Resources configured as exclusive must only be used by a single thread.   Exclusive use provides the best performance,  since
 *          access is not serialized using a mutex or spinlock.  
 *
 * @note    This function doesn't not reset or modify the queue groups that
 *          feed the TQS' iPCQ. The queue group mapping (if any) will remain
 *          the same after calling this function. In order to change it,
 *          use ncp_task_tqs_queue_group_set().
 *
 * @note    User-space threads can't configure kernel-mode TQSes, and
 *          kernel-space threads can't configure user-mode TQSes. The RTE
 *          will detect this and return NCP_ST_TASK_TQS_MODE_CONFLICT.
 *
 * @param[in] ncpHdl:  NCP handle returned by previous call to ncp_config.
 * @param[in] tqsId:   The ID of the Thread Queue Set.
 * @param[in] tqsName: Name of the TQS.
 * @param[in] appProfileName: Name of application profile configured in the ASE.
 * @param[in] flags: See ncp_task_tqs_shared_t. Describes whether individual
 *              resources associated with this TQS are shared or exclusive.
 * @param[in] memoryQuotaGroupId: The ID of the memory quota group this TQS
 *              will join.
 *
 * @retval NCP_ST_SUCCESS success
 * @retval NCP_ST_BAD_RESOURCE_NAME The supplied TQS name is in use by another TQS.
 * @retval NCP_ST_TASK_NO_GSM The software state is not valid. This may be due
 *              to corruption or a configuration problem.
 * @retval NCP_ST_INVALID_PARAMETER The flags pointer and/or the appProfileName
 *              pointer is NULL, or the tqsId is not between 0 and 63
 *              (inclusive), or the specified profile is not a CPU profile, or
 *              memoryQuotaGroupId is not between 0 and 31 (inclusive).
 * @retval NCP_ST_TASK_TQS_ALREADY_CONFIGURED The TQS is already configured. In
 *              order to re-configure it, the configuration must be destroyed
 *              with ncp_task_tqs_shutdown() first.
 * @retval NCP_ST_TASK_TQS_SHARING_VIOLATION The usage flags indicate that
 *              another thread is already using the resource, and that
 *              resource is not configured to be shared.
 * @retval NCP_ST_TASK_MANUAL_COMPLETION_REQUIRES_TXQ The thread has indicated
 *              that it will be using the RXQ, but the RXQ is configured for
 *              manual completion and the thread has not indicated that it will
 *              be using either TXQ. A TXQ must by included in the usage flags,
 *              since manual task completions require the use of a TXQ.
 * @retval NCP_ST_TASK_TQS_INVALID_POOL The thread has indicated that it will
 *              be using an allocator associated with a pool that is not
 *              configured for this TQS. Only allocators associated with pools
 *              that are configured for this TQS may be used by this thread.
 * @retval NCP_ST_TASK_NCAP_DOES_NOT_EXIST Attempted to configure a TQS on an
 *              A53 NCAP that does not exist. On the regular FPGA only NCAP0
 *              exists, and on a super FPGA NCAPs 0, 2, and 4 exist.
 * @retval NCP_ST_TASK_TQS_MODE_CONFLICT The TQS is being configured with a
 *              kernel-mode profile from user-space, or a user-mode profile
 *              from kernel-space.
 */	

NCP_API ncp_st_t
ncp_task_tqs_configure(
    ncp_hdl_t ncpHdl,   
    ncp_uint32_t tqsId,
    ncp_task_resource_name_t *tqsName,
    ncp_task_resource_name_t *appProfileName,
    ncp_task_tqs_shared_t *flags,
    ncp_uint32_t memoryQuotaGroupId);
  
/*!
 * @fn ncp_st_t ncp_task_tqs_configure_flags_get(
 *          ncp_hdl_t ncpHdl,
 *          ncp_uint32_t tqsId,
 *          ncp_task_tqs_shared_t *flags);
 *
 * @brief   Get the configuration flags associated with the specified TQS.
 *          The TQS must have been configured prior to calling this function
 *          either statically through ASE or dynamically through the
 *          ncp_task_tqs_configure() API.
 *
 * @param[in]       ncpHdl:  NCP handle returned by previous call to ncp_config
 * @param[in]       tqsId:   The ID of the Thread Queue Set
 * @param[in,out]   flags:   See ncp_task_tqs_shared_t are returned on success.  
 *
 * @retval NCP_ST_SUCCESS success
 * @retval NCP_ST_INVALID_PARAMETER The flags pointer is NULL, or the tqsId is
 *              not between 0 and 63 (inclusive).
 * @retval NCP_ST_TASK_NO_GSM The software state is not valid. This may be due
 *              to corruption or a configuration problem.
 * @retval NCP_ST_TASK_QUESET_NOT_IN_LOCAL_DOMAIN The TQS is not a member of
 *              the local domain (AMP only).
 * @retval NCP_ST_TASK_TQS_NOT_CONFIGURED The TQS must be configured in the ASE
 *              or dynamically before it can be used in this API.
 */	        
NCP_API ncp_st_t
ncp_task_tqs_configure_flags_get(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t tqsId,
    ncp_task_tqs_shared_t *flags);

/*!
 * @fn ncp_st_t ncp_task_tqs_memory_quota_group_get(
 *          ncp_hdl_t ncpHdl,
 *          ncp_uint32_t tqsId,
 *          ncp_uint32_t *memoryQuotaGroupId);
 *
 * @brief   Get the ID of the memory quota group associated with the specified
 *          TQS. The TQS must have been configured prior to calling this
 *          function either statically through ASE or dynamically through the
 *          ncp_task_tqs_configure() API.
 *
 * @param[in]  ncpHdl: NCP handle returned by previous call to ncp_config
 * @param[in]  tqsId:  The ID of the Thread Queue Set
 * @param[out] memoryQuotaGroupId: The TQS's memory quota group ID is returned
 *                  on success.
 *
 * @retval NCP_ST_SUCCESS success
 * @retval NCP_ST_INVALID_PARAMETER The memoryQuotaGroupId pointer is NULL, or
 *              the tqsId is not between 0 and 86 (inclusive).
 * @retval NCP_ST_TASK_NO_GSM The software state is not valid. This may be due
 *              to corruption or a configuration problem.
 * @retval NCP_ST_TASK_QUESET_NOT_IN_LOCAL_DOMAIN The TQS is not a member of
 *              the local domain (AMP only).
 * @retval NCP_ST_TASK_TQS_NOT_CONFIGURED The TQS must be configured in the ASE
 *              or dynamically before it can be used in this API.
 */

NCP_API ncp_st_t
ncp_task_tqs_memory_quota_group_get(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t tqsId,
    ncp_uint32_t *memoryQuotaGroupId);

/*!
 * @fn ncp_st_t ncp_task_nca_queue_configure(
 *      ncp_hdl_t ncpHdl,
 *      ncp_uint32_t ncaQueueId,
 *      ncp_task_resource_name_t *queueName,
 *      ncp_task_resource_name_t *queueProfileName,
 *      ncp_int32_t queueGroupId,
 *      ncp_uint32_t paramsSize,
 *      ncp_task_nca_queue_sched_params_t *params);
 *
 * @brief   Configure the NCA queue with the profile indicated by queueProfileName.
 *          No iPCQs may be connected to the NCA queue when configuring.
 *          Also, queueGroupId must be an enabled queue group.
 *
 * @param[in] ncpHdl: NCP handle returned by previous call to ncp_config
 * @param[in] ncaQueueId: The ID of the NCA queue 
 * @param[in] queueName: Name of the NCA queue
 * @param[in] queueProfileName: The profile name that contains the
 *                  configuration related data for this NCA queue. If
 *                  this argument is NULL, the queue's current profile
 *                  is used, if the queue has one.
 * @param[in] queueGroupId: The queue group to which this NCA queue will
 *                  belong. If queueGroupId is -1, the RTE will use the
 *                  previously configured queue group, if one exists.
 * @param[in] paramsSize: This argument must be set to
 *                  sizeof(ncp_task_nca_queue_sched_params_t).
 * @param[in] params: The task scheduling parameters. If this argument is NULL,
 *                  the queue's current task scheduling parameters are used.
 *
 * @retval NCP_ST_SUCCESS success
 * @retval NCP_ST_INVALID_PARAMETER queueProfileName is NULL and the queue
 *              does not already have a profile, or the ncaQueueId is not
 *              between 0 and 203 (inclusive), queueGroupId is greater than
 *              255, or queueName is NULL.
 * @retval NCP_ST_TASK_NCA_QUEUE_GROUP_NOT_SPECIFIED queueGroupId is -1 and the
 *              queue has no previously configured queue group.
 * @retval NCP_ST_TASK_QUEUE_GROUP_NOT_ENABLED the queue group specified by
 *              queueGroupId is not enabled.
 * @retval NCP_ST_BAD_RESOURCE_NAME The supplied NCA queue name is in use by
 *              another NCA queue.
 */
ncp_st_t
ncp_task_nca_queue_configure(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t ncaQueueId,
    ncp_task_resource_name_t *queueName,
    ncp_task_resource_name_t *queueProfileName,
    ncp_int32_t queueGroupId,
    ncp_uint32_t paramsSize,
    ncp_task_nca_queue_sched_params_t *params);

  
/*!
 * @fn ncp_st_t ncp_task_tqs_bind(ncp_hdl_t ncpHdl,
 *                                ncp_uint32_t tqsId,
 *                                ncp_task_tqs_usage_t *params,
 *                                ncp_task_resource_name_t *processName,
 *                                ncp_task_resource_name_t *threadName,  
 *                                ncp_task_tqs_hdl_t *tqsHdl);
 *
 * @brief   Every thread that uses a TQS must bind to it.
 *          TQS handles must not be shared among threads.  Resources associated with a TQS may be shared,   but each thread
 *          that uses a TQS must issue its own bind,  and then use the returned handle for its accesses.   Sharing TQS resources
 *          will result in lower performance since access to to those resources must be serialized with a mutex/spinlock.
 *          TQS bind will fail if the TQS is not yet configured.
 *          All threads in the same process must supply the same processName (used for internal tracking purposes).

 *
 * @param[in]       ncpHdl:  NCP handle returned by previous call to ncp_config
 * @param[in]       tqsId:   The ID of the Thread Queue Set 
 * @param[in]       params:  Usage parameters that describe which specific TQS resources will be used by this thread.
 * @param[in]       processName: pointer to process name,   which can be any name the application chooses to use,   and does
 *                               not necessarily need to be the name of the application/executable.  Each process must use a unique process name.
 *                               Threads within a given process must all use the same process name.
 * @param[in]       threadName: pointer to thread name,   which can be any name the application chooses to use.   The thread name must be unique
 *                               within the process name space.   That is,   no two threads in the same process can use the same thread name.
*                                Collectively,   the process name and thread name can be used by the RTE to detect if a thread has been restarted due to a crash.
 * #param[in,out]   tqsHdl: pointer to where the handle will be returned upon success.   The handle is used in other Task I/O APIs,  and 
 *                          must only be used by a single thread.
 *
 * @retval  NCP_ST_SUCCESS success.
 * @retval  NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval  NCP_ST_INVALID_PARAMETER One or more of the parameters supplied is not valid.
 * @retval  NCP_ST_TASK_BAD_RESOURCE_NAME The process or Thread name is not valid.
 * @retval  NCP_ST_TASK_QUESET_NOT_IN_LOCAL_DOMAIN The TQS is not a member of the local domain (AMP only).
 * @retval  NCP_ST_TASK_TQS_NOT_CONFIGURED The TQS must be configured in the ASE or dynamically before it can be used in this API.
 * @retval  NCP_ST_TASK_TQS_MODE_CONFLICT The TQS is configured for kernel mode but is attempting to by bound in USER mode, or vice versa.
 * @retval  NCP_ST_TASK_TQS_DISABLED The TQS is currently disabled.   It must be enabled before it can be used in this API.
 * @retval  NCP_ST_TASK_PROCESS_RESTART_DETECTED The RTE detected that the Process/Thread is restarting.   It is also possible to 
 *                                               see this error if the application is not using unique process/Thread name combinations.
 *                                               If the error is a result of a Process crash and restart,   and if TBR is enabled,   the RTE 
 *                                               will attempt to recover the resources from the previous instance so that the system state 
 *                                               is restored and the TQS is cleaned up for reuse.
 * @retval  NCP_ST_TASK_PROCESS_NAME_NOT_UNIQUE Another application is using the same process name.   Process names must be unique.
 * @retval  NCP_ST_NO_MEMORY  NVM has been exhausted.
 * @retval  NCP_ST_TASK_OUT_OF_PIDS No free process ID (PID) exists.   There is a fixed limit of approximately 64K process IDs.
 * @retval  NCP_ST_TASK_PROCESS_NAME_MISMATCH All threads within the same linux process must use the same process name.
 * @retval  NCP_ST_TASK_THREAD_NAME_NOT_UNIQUE All threads in the same linux process must use unique thread names.
 * @retval  NCP_ST_TASK_TQS_SHARING_VIOLATION The usage flags indicate that another thread is already using the resource,  and that resource is 
 *                                            not configured to be shared.
 * @retval  NCP_ST_TASK_MANUAL_COMPLETION_REQUIRES_TXQ The thread has indicated that it will be using the RXQ,   but the RXQ is configured for
 *                                                      manual completion and the thread has not indicated that it will be using either TXQ.   A TXQ must
 *                                                      by included in the usage flags,   since manual task completions require the
 *                                                      use of a TXQ.
 * @retval  NCP_ST_TASK_TQS_INVALID_POOL The thread has indicated that it will be using an allocator associated with a pool that is not
 *                                       configured for this TQS.   Only allocators associated with pools that are configured for this
 *                                       TQS may be used by this thread.
 * @retval  NCP_ST_TASK_MMAP_FAILED  The RTE could not mmap the memory range associated with one of the task memory pools that have been requested.
 * @retval NCP_ST_TASK_OUT_OF_PIDS The PID table has been exhausted.   Approximately 64K PIDs are available,  and each process consumes 1.
 * 
*/	
    
NCP_API ncp_st_t
ncp_task_tqs_bind(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t tqsId,
    ncp_task_tqs_usage_t *params,
    ncp_task_resource_name_t *processName,
    ncp_task_resource_name_t *threadName, 
    ncp_task_tqs_hdl_t *tqsHdl);


/*!
 * @fn ncp_st_t ncp_task_tqs_hdl_recover(ncp_hdl_t ncpHdl,
 *                                ncp_uint32_t tqsId,
 *                                ncp_task_tqs_usage_t *params,
 *                                ncp_task_resource_name_t *processName,
 *                                ncp_task_resource_name_t *threadName,  
 *                                ncp_task_tqs_hdl_t *tqsHdl);
 *
 * @brief   Every thread that uses a TQS must bind to it.   If a thread restarts due to a crash,   it may not be able to determine the 
 *          value of the handle that it was using in its previous incarnation.   This API can be used by a thread that has restarted and
 *          needs to reacquire its previous tqs handle in order to be able to perform cleanup related to its previous crash.   Once the cleanup
 *          is performed,   the thread is expected to call ncp_task_tqs_unbind.    A recovered task handle can be used to flush queues,  issue completions,
 *          free tasks or buffers.  A recovered tqs handle cannot be used to allocate task buffers,   or send or receive tasks.
 *          Depending on the pool(s) used by the parent process,   and the number of threads and processes that need to perform cleanup,   subsequent bind calls will return
 *          NCP_ST_TASK_TQS_DISABLED until all related resources have been recovered via TBR. 
 *
 *
 *
 * @param[in]       ncpHdl:  NCP handle returned by previous call to ncp_config
 * @param[in]       tqsId:   The ID of the Thread Queue Set 
 * @param[in]       params:  Usage parameters that describe which specific TQS resources will be used by this thread.   Must match original ncp_task_tqs_bind.
 * @param[in]       processName: pointer to process name,   which is a can be any name the application chooses to use,   and does
 *                               not necessarily need to be the name of the application/executable.  Each process must use a unique process name.
 *                               Threads within a given process must all use the same process name.
 * @param[in]       threadName: pointer to thread name,   which can be any name the application chooses to use.   The thread name must be unique
 *                               within the process name space.   That is,   no two threads in the same process can use the same thread name.
*                                Collectively,   the process name and thread name can be used by the RTE to detect if a thread has been restarted due to a crash.
 * #param[in,out]   tqsHdl: pointer to where the recovered handle will be returned.
 *
 * @retval  NCP_ST_SUCCESS success.
 * @retval  NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval  NCP_ST_INVALID_HANDLE The TQS handle failed validation.   The application must call ncp_task_tqs_bind to obtain a TQS handle,
 *                                and then use the handle that is returned in subsequent API calls.   The handle is valid until the thread 
 *                                calls ncp_task_tqs_unbind. 
 * @retval  NCP_ST_INVALID_PARAMETER One or more of the parameters supplied is not valid.
 * @retval  NCP_ST_TASK_BAD_RESOURCE_NAME The process or Thread name is not valid.
 * @retval  NCP_ST_TASK_QUESET_NOT_IN_LOCAL_DOMAIN The TQS is not a member of the local domain (AMP only). 
 * @retval  NCP_ST_TASK_TQS_NOT_CONFIGURED The TQS must be configured in the ASE or dynamically before it can be used in this API.
 * @retval  NCP_ST_TASK_TQS_MODE_CONFLICT The TQS is configured for kernel mode but is attempting to by bound in USER mode, or vice versa.
 * @retval  NCP_ST_TASK_TQS_DISABLED The TQS is currently disabled.   It must be enabled before it can be used in this API. 
 * @retval  NCP_ST_TASK_PROCESS_IN_CRITICAL_SECTION The handle cannot be recovered.   The SW state indicates that a previous process/thread instance crashed 
 *                                                  while executing a RTE API.   This may indicate corruption,   so it is not safe to attempt the recovery.
 * @retval  NCP_ST_TASK_THREAD_NOT_FOUND No previous instance of a thread by this name was found.
 * @retval  NCP_ST_TASK_PROCESS_NOT_FOUND No previous instance of a process by this name was found.
*/	
    
NCP_API ncp_st_t
ncp_task_tqs_hdl_recover(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t tqsId,
    ncp_task_tqs_usage_t *params,
    ncp_task_resource_name_t *processName,
    ncp_task_resource_name_t *threadName, 
    ncp_task_tqs_hdl_t *tqsHdl);
    
/*!
 * @fn ncp_st_t ncp_task_tqs_unbind(ncp_task_tqs_hdl_t tqsHdl);
 *
 * @brief   Every thread that binds a TQS must unbind it before exiting.   Exactly one unbind should be issued for each 
 *          successful bind that was issued.
 *
 *
 * @param[in]       tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
 *
 * @retval  NCP_ST_SUCCESS success.
 * @retval  NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval  NCP_ST_INVALID_HANDLE The TQS handle failed validation.   The application must call ncp_task_tqs_bind to obtain a TQS handle,
 *                                and then use the handle that is returned in subsequent API calls.   The handle is valid until the thread 
 *                                calls ncp_task_tqs_unbind. 
 * @retval  NCP_ST_INVALID_PARAMETER One or more of the parameters supplied is not valid.
 * @retval  NCP_ST_TASK_TQS_SHARING_VIOLATION The TX or RX queue is not available for this thread.   See usage specified in the ncp_task_tqs_bind API.
 *                                            This error should not occur in this API.
 * @retval  NCP_ST_TASK_SENDQUEUE_CALLBACK_RECURSION_DETECTED  The ncp_task_tqs_unbind API may not
 *                                                             be called from a task send or task free callback function.
* @retval NCP_ST_TASK_TBR_BUFFERS_OWNED_DURING_REMOVE The application removed the task handle while it still owned
       one or more buffers. This is only an alert -- the task buffers are 
       flushed when the task handle is removed, but the developer needs to
       fix the application so it doesn't leak buffers when Task Buffer 
       Recovery is disabled.
 * @retval NCP_ST_TASK_EXITING_WITH_COMPLETIONS_OWED The thread is attempting to unbind the tqs,  but task completions are still owed. 
 * @retval NCP_ST_TASK_TBR_INVALID_BUFFER TBR detected that the buffer does not belong to the pool
 * @retval NCP_ST_TASK_TBR_FATAL_POOL_CORRUPTION TBR detected that the buffer is not in the expected state,  and pool corruption is likely
 
*/	 
NCP_API ncp_st_t
ncp_task_tqs_unbind(
    ncp_task_tqs_hdl_t tqsHdl);

/*!
 * @fn ncp_st_t ncp_task_tqs_shutdown(
 *                  ncp_hdl_t    ncpHdl,
 *                  ncp_uint32_t tqsId);
 *
 * @brief This function shuts down a TQS, which flushes its iPCQ and mPCQ. This
 *          function must be called before re-configuring a TQS, and there must
 *          non be any TQS handles bound to the TQS.
 *
 * @param[in] ncpHdl:  NCP handle returned by previous call to ncp_config
 * @param[in] tqsId:   The ID of the Thread Queue Set 
 *
 * @retval  NCP_ST_SUCCESS success.
 * @retval  NCP_ST_TASK_NO_GSM The software state is not valid. This may be due to corruption or a configuration problem.
 * @retval  NCP_ST_TASK_NONZERO_USE_COUNT There is at least one TQS handle that
 *              hasn't been unbound.
 */	 
NCP_API ncp_st_t
ncp_task_tqs_shutdown(
    ncp_hdl_t    ncpHdl,
    ncp_uint32_t tqsId);

/*!
 * @fn ncp_st_t ncp_task_tqs_disable(
 *                  ncp_hdl_t ncpHdl,
 *                  ncp_uint32_t tqsId);
 *
 * @brief   Sets TQS software state to disabled.  Any Task I/O operations on a
 *          disabled TQS will fail. Any thread blocked on an interrupt for a
 *          queue contained in a disabled will be unblocked. All affected tx
 *          threads should call ncp_task_send_queue_flush() to perform any
 *          necessary callback functions. All affected rx threads should call
 *          ncp_task_recv_queue_flush().
 *
 * @param[in] ncpHdl:  NCP handle returned by previous call to ncp_config
 * @param[in] tqsId:   The ID of the Thread Queue Set 
 *
 * @retval NCP_ST_SUCCESS success
 * @retval NCP_ST_TASK_TQS_NOT_CONFIGURED The TQS must be configured in the ASE
 *              or dynamically before it can be used in this API.
 * @retval NCP_ST_INVALID_PARAMETER The tqsId is not between 0 and 85
 *              (inclusive).
 * @retval NCP_ST_TASK_NO_GSM The software state is not valid. This may be due
 *              to corruption or a configuration problem.
 */	
NCP_API ncp_st_t
ncp_task_tqs_disable(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t tqsId);

/*!
 * @fn ncp_st_t ncp_task_tqs_enable(
 *                  ncp_hdl_t ncpHdl,
 *                  ncp_uint32_t tqsId);
 *
 * @brief   Sets TQS software state to enabled.
 *
 * @param[in]       ncpHdl:  NCP handle returned by previous call to ncp_config
 * @param[in]       tqsId:   The ID of the Thread Queue Set 
 *
 * @retval NCP_ST_SUCCESS success
 * @retval NCP_ST_TASK_TQS_NOT_CONFIGURED The TQS must be configured in the ASE
 *              or dynamically before it can be used in this API.
 * @retval NCP_ST_INVALID_PARAMETER The tqsId is not between 0 and 85
 *              (inclusive).
 * @retval NCP_ST_TASK_NO_GSM The software state is not valid. This may be due
 *              to corruption or a configuration problem.
 */	
NCP_API ncp_st_t
ncp_task_tqs_enable(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t tqsId);

/*!
 * @fn ncp_st_t ncp_task_nca_queue_disable(
 *                  ncp_hdl_t ncpHdl,
 *                  ncp_uint32_t ncaQueueId);
 *
 * @brief Disable the NCA queue.
 *
 * @param[in] ncpHdl: NCP handle returned by previous call to ncp_config
 * @param[in] ncaQueueId: The ID of the NCA queue
 *
 * @retval NCP_ST_SUCCESS success
 * @retval NCP_ST_INVALID_PARAMETER The ncaQueueId is not between 0 and 203
 *              (inclusive).
 * @retval NCP_ST_TASK_NO_GSM The software state is not valid. This may be due
 *              to corruption or a configuration problem.
 */	
NCP_API ncp_st_t
ncp_task_nca_queue_disable(
    ncp_hdl_t ncpHdl,    
    ncp_uint32_t ncaQueueId);

/*!
 * @fn ncp_st_t ncp_task_nca_queue_enable(ncp_hdl_t ncpHdl,    
 *                                        ncp_uint32_t ncaQueueId);
 *
 * @brief   Enable the NCA queue.
 *
 * @param[in]       ncpHdl:  NCP handle returned by previous call to ncp_config
 * @param[in]       ncaQueueId:   The ID of the NCA queue
 *
 * @retval NCP_ST_SUCCESS success
 * @retval NCP_ST_TASK_NCA_QUEUE_NOT_CONFIGURED the specified NCA queue is not
 *              configured.
 * @retval NCP_ST_INVALID_PARAMETER The ncaQueueId is not between 0 and 203
 *              (inclusive).
 * @retval NCP_ST_TASK_NO_GSM The software state is not valid. This may be due
 *              to corruption or a configuration problem.
 * @retval NCP_ST_TASK_NCA_QUEUE_GROUP_NOT_SPECIFIED The specified queue is not
 *              a member of a queue group. To add the queue to a queue group,
 *              use ncp_task_nca_queue_configure()
 */	
ncp_st_t
ncp_task_nca_queue_enable(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t ncaQueueId);

/*!
 * @fn ncp_st_t ncp_task_rx_queue_flush(ncp_task_tqs_hdl_t tqsHdl,
 *                                      ncp_uint32_t txQueueId);
 *
 * @brief   Flush the receive queue (iPCQ) associated with the TQS.  Remove tasks from the specified receive queue 
 *          until it and the NCA queues that feed it are depleted. This function may issue manual completions or 
 *          task frees on the specified transmit queue.

 *
 * @param[in]       tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in]       txQueueId:   TxQueueId to use for freeing any tasks presently in the receive queue.   The TxQueueTd
 *                               will also be used when issuing any manual completions (if the iPCQ is configured for manual completion).
 *
 * @retval  NCP_ST_SUCCESS success.
 * @retval  NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval  NCP_ST_INVALID_HANDLE The TQS handle failed validation.   The application must call ncp_task_tqs_bind to obtain a TQS handle,
 *                                and then use the handle that is returned in subsequent API calls.   The handle is valid until the thread 
 *                                calls ncp_task_tqs_unbind. 
 * @retval  NCP_ST_INVALID_PARAMETER One or more of the parameters supplied is not valid.
 * @retval  NCP_ST_TASK_TQS_SHARING_VIOLATION The TX or RX queue is not available for this thread.   See usage specified in the ncp_task_tqs_bind API.
 *                                            This error should not occur in this API.
 * @retval  NCP_ST_TASK_SENDQUEUE_CALLBACK_RECURSION_DETECTED  The ncp_task_rx_queue_flush API may not
 *                                                             be called from a task send or task free callback function.
 * @retval  XXX Any errors that can be returned by ncp_task_recv, ncp_task_complete, or ncp_task_free
 *
*/	
ncp_st_t
ncp_task_rx_queue_flush(
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint32_t txQueueId);

/*!
 * @fn ncp_st_t ncp_task_tx_queue_flush(ncp_task_tqs_hdl_t tqsHdl,
 *                                      ncp_uint32_t txQueueId);
 *
 * @brief   Flush the TQS's tx queue.  This function blocks until the specified tx queue (oPCQ) is empty.
 *          Any outstanding tasks sent with send done will have their send done function executed after the 
 *          queue is drained.
 *
 * @param[in]       tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in]       txQueueId:   TxQueueId of queue to flush.
 *
 * @retval  NCP_ST_SUCCESS success.
 * @retval  NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval  NCP_ST_INVALID_HANDLE The TQS handle failed validation.   The application must call ncp_task_tqs_bind to obtain a TQS handle,
 *                                and then use the handle that is returned in subsequent API calls.   The handle is valid until the thread 
 *                                calls ncp_task_tqs_unbind. 
 * @retval  NCP_ST_INVALID_PARAMETER One or more of the parameters supplied is not valid.
 * @retval  NCP_ST_TASK_TQS_SHARING_VIOLATION The TX or RX queue is not available for this thread.   See usage specified in the ncp_task_tqs_bind API.
 *                                            This error should not occur in this API.
 * @retval  NCP_ST_TASK_SENDQUEUE_CALLBACK_RECURSION_DETECTED  The ncp_task_tx_queue_flush API may not
 *                                                             be called from a task send or task free callback function.
 *
*/	
NCP_API ncp_st_t
ncp_task_tx_queue_flush(
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint32_t txQueueId);


/*!
 * @fn ncp_st_t ncp_task_send(ncp_task_tqs_hdl_t tqsHdl,
 *                           ncp_uint8_t txQueueId,
 *                           ncp_uint32_t numTasks, 
 *                           ncp_uint32_t *numSent, 
 *                           ncp_task_send_meta_t *metadata, 
 *                           ncp_bool_t wait);
 *
 * @brief   Send one or more tasks.  Specifically send up to numTasks tasks.
 *
 * @note    The caller is responsible for setting all of the fields in the task header and task metadata data structures,
 *          including encoding the task parameters for each task sent. Note that the task header pointer is included in the task metadata.
 *
 * @note    Depending on the wait parameter,   and the wait profile,   this function may return before sending 
 *          all of the tasks.   In this case,   the return status will be NCP_ST_SEND_QUEUE_FULL if the premature return was due to 
 *          encountering a blocking condition.   The caller must check the numSent value to determine how many tasks were sent,   and then retry 
 *          the send at some point.  Typically the retry would be for (numTasks - numSent) tasks starting at (metadata + numSent).
 *
 * @note    If a sendDone function is specified in the metadata,   it is important for the caller to keep track of how
 *          it set freeHeader and freeData in the metadata associated with each task.   The RTE will always invoke the sendDone
 *          function callback with both the function argument and task header specified in the metadata,   regardless of 
 *          whether the task header or buffers were freed as part of sending the task.   Corruption will occur if the caller 
 *          attempts to use a header or buffer that has been freed.
 *
 * @note    If a send done function is specified,   the callback will be performed in the calling threads context on this or a subsequent 
 *          call to either the ncp_task_send of ncp_task_tx_queue_flush APIs.
 *
 * @note    It is not valid to send a task, issue a task refill, free a task, or issue task completions,  from the callback 
 *          function,   as that might result in taking a lock in a recursive call 
 *          scenario and therefore result in a deadlock.
 *
 * @note    A task completion for the oldest task received in this TQS will be combined with the send if issueCompletion is TRUE.   See metadata.
 *
 * @note    If the TQS is configured to use a CPU pool,   performing a send with freeHeader and/or freeData will result in a refill operation for
 *          the NCA hardware's internal list of receive buffers.   If the application wishes to free the header and/or buffers to the CPU pool free list,
 *          then a send done function must be used.   If the TQS is configured to use shared pools,   then setting freeHeader and/or freeBuffers will
 *          result in the header/buffer(s) being returned to MME.
 *
 * @note    freeHeader is ignored if combinedHeader is TRUE
 *
 * @note    If the user wishes *not* to free the data pointers on the send (i.e. freeDataPointers is FALSE), care must be taken.
 *          In order to send a task without freeing the task data, you must first increment the reference count(s) for all task
 *          data buffers and set their mref bits first. In addition, you must free the buffer twice: once for the initial allocation,
 *          and again for the incremented reference count. If the user does not follow these steps, pool corruption can occur.
 *
 * @param[in]       tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in]       txQueueId:   TxQueueId of queue to use when sending the tasks(s).
 * @param[in]       numTasks: maximum number of tasks to send.   If numTasks equals zero,   the function processes any completed sends, 
 *                  if sendDone outstanding,   and returns success.
 * @param[in,out]   numSent: pointer to location where RTE writes the actual number of tasks sent.   See note above.   The value
 *                  written by the RTE may be less than the number of tasks that the caller requested to be sent.
 * @param[in]       metadata:  array of meta data structures,   one per task.   All fields in the meta data must be initialized by the 
 *                  caller.
 * @param[in]       wait: FALSE - send zero or more tasks,   stopping if all tasks are sent,   a blocking condition is encountered, or an error is
 *                  detected.   TRUE - send every task,   stopping early only if an error is detected,   or a wait timeout expires (see wait profiles).
 *
 * @retval NCP_ST_SUCCESS successfully transmitted all of the tasks that were requested to be sent.
 * @retval  NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval  NCP_ST_INVALID_HANDLE The TQS handle failed validation.   The application must call ncp_task_tqs_bind to obtain a TQS handle,
 *                                and then use the handle that is returned in subsequent API calls.   The handle is valid until the thread 
 *                                calls ncp_task_tqs_unbind. 
 * @retval  NCP_ST_INVALID_PARAMETER One or more of the parameters supplied is not valid.
 * @retval  NCP_ST_TASK_TQS_SHARING_VIOLATION The TX or RX queue is not available for this thread.   See usage specified in the ncp_task_tqs_bind API.
 *                                            This error should not occur in this API.
 * @retval  NCP_ST_TASK_SENDQUEUE_CALLBACK_RECURSION_DETECTED  The ncp_task_send API may not
 *                                                             be called from a task send or task free callback function. 
 * @retval NCP_ST_TASK_SEND_QUEUE_FULL check numSent to determine the number of tasks that were sent,   if any.  This status code is not an error.
 * @retval NCP_ST_TASK_BULK_REQUEST_TOO_BIG numTasks exceeds NCP_TASK_API_MAX_BULK_ITEM_COUNT.
 * @retval NCP_ST_TASK_TBR_INVALID_BUFFER TBR detected that the buffer does not belong to the pool
 * @retval NCP_ST_TASK_TBR_FATAL_POOL_CORRUPTION TBR detected that the buffer is not in the expected state,  and pool corruption is likely
 * @retval NCP_ST_TASK_TOO_MANY_TASK_COMPLETIONS The number of task completions requested exceeds the number owed by this thread.
 * @retval NCP_ST_INVALID_PDU_SIZE One or more of the PDU segment sizes is 0.
 *
 */
ncp_st_t
ncp_task_send( 
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint8_t txQueueId,
    ncp_uint32_t numTasks, 
    ncp_uint32_t *numSent, 
    ncp_task_send_meta_t *metadata, 
    ncp_bool_t wait);

/*!
 * @fn ncp_st_t ncp_task_recv(ncp_task_tqs_hdl_t tqsHdl,
 *                   ncp_uint32_t numTasks, 
 *                   ncp_uint32_t *numReceived, 
 *                   ncp_task_header_t **tasks,
 *                   ncp_bool_t wait);
 *
 * @brief   Receive one or more tasks, specifically receive up to numTasks tasks.
 *
 * @param[in]       tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in]       numTasks:   The maximum number of tasks the application is prepared to receive.   The caller must have
 *                  provided sufficient storage for this number of task header pointers (see the tasks parameter)
 * @param[in,out]   numReceived:   pointer to memory where the RTE will return the number of tasks actually received.
 * @param[in,out]   tasks: pointer to memory where the RTE will write the task headers associated with the tasks that are received.
 * @param[in]       wait:   If FALSE,   then the RTE will return as soon as it encounters an empty receive queue,  has received the
 *                  maximum number of tasks,  or encounters an error.   If TRUE,  then the RTE will employ the wait profile.   The 
 *                  API may return early if it encounters and error,  of encounters a blocking condition (empty rx queue) and at least one
 *                  task has been received,   or if a timeout wait profile was used and the timeout expires.
 *
 * @note:           The caller is responsible for refilling the NCA's list of receive buffers if this TQS is configured to use a CPU pool.
 *                  This requires the caller to replenish each and every task header (if combinedHeader is FALSE) and each and every task
 *                  buffer with a replacement buffer of the same size.    The NCA refill can be accomplished using one of the following APIs:
 *                  ncp_task_send, ncp_task_refill,   ncp_task_free,   or ncp_task_buffer_free.
 *
 * @note:           The caller is responsible for decoding the task parameters.
 *
 * @retval NCP_ST_SUCCESS successfully received at least one task.   The caller must check numReceived,  to determine how many tasks were
 *                        actually received.
 * @retval  NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval  NCP_ST_INVALID_HANDLE The TQS handle failed validation.   The application must call ncp_task_tqs_bind to obtain a TQS handle,
 *                                and then use the handle that is returned in subsequent API calls.   The handle is valid until the thread 
 *                                calls ncp_task_tqs_unbind. 
 * @retval  NCP_ST_INVALID_PARAMETER One or more of the parameters supplied is not valid.
 * @retval  NCP_ST_TASK_TQS_SHARING_VIOLATION The TX or RX queue is not available for this thread.   See usage specified in the ncp_task_tqs_bind API.
 *                                            This error should not occur in this API.
 * @retval  NCP_ST_TASK_SENDQUEUE_CALLBACK_RECURSION_DETECTED  The ncp_task_recv API may not
 *                                                             be called from a task send or task free callback function.  
 * @retval NCP_ST_RECV_QUEUE_EMPTY The function encountered an empty iPCQ. If
 *          called with wait == TRUE, the function waited (according to its
 *          wait profile) and timed out before any new tasks arrived.
 */
 
ncp_st_t
ncp_task_recv(
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint32_t numTasks, 
    ncp_uint32_t *numReceived, 
    ncp_task_header_t **tasks,
    ncp_bool_t wait);


/*!
 * @fn ncp_st_t ncp_task_complete(ncp_task_tqs_hdl_t tqsHdl,
 *                       ncp_uint8_t txQueueId,
 *                       ncp_uint32_t numTasks,
 *                       ncp_uint32_t *numTasksCompleted,
 *                       ncp_bool_t wait);   
 *
 * @brief   Send a task completion for the oldest previously received task.   The application must issue task completions if the
 *          receive queue (iPCQ) has been configured for manual task completion.    
 *          This API should only be called if the TQS's receive queue is configured for manual task completion.
 *
 * @param[in]       tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in]       txQueueId:   Which tx queue (0 or 1) to use when sending the task completion request(s)
 * @param[in]       numTasksCompleted: pointer to a location in memory where the RTE will return the number of task completions actually issued.
 * @param[in]       wait:   If FALSE,   then the RTE will return as soon as it encounters an full tx queue,  has issued the
 *                  requested number of task completions,  or encounters an error.   If TRUE,  then the RTE will employ the associated wait profile.   The 
 *                  API may return early if it encounters an error,  or encounters a blocking condition (full tx queue), or if a timeout wait 
                    profile was used and the timeout expires.
 *
 * @retval NCP_ST_SUCCESS successfully sent all of the task completions requested.
 * @retval  NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval  NCP_ST_INVALID_HANDLE The TQS handle failed validation.   The application must call ncp_task_tqs_bind to obtain a TQS handle,
 *                                and then use the handle that is returned in subsequent API calls.   The handle is valid until the thread 
 *                                calls ncp_task_tqs_unbind. 
 * @retval  NCP_ST_INVALID_PARAMETER One or more of the parameters supplied is not valid.
 * @retval  NCP_ST_TASK_TQS_SHARING_VIOLATION The TX or RX queue is not available for this thread.   See usage specified in the ncp_task_tqs_bind API.
 *                                            This error should not occur in this API.
 * @retval  NCP_ST_TASK_SENDQUEUE_CALLBACK_RECURSION_DETECTED  The ncp_task_complete API may not
 *                                                             be called from a task send or task free callback function.   
 * @retval NCP_ST_TASK_SEND_QUEUE_FULL sent zero or more task completions.   The caller must check numTasksCompleted to determine how many completions were
 *                                     actually sent.   Typically the caller would retry the operation at some point,   specifying (numTasks - numTasksCompleted)
 *                                     tasks.
 * @retval NCP_ST_TASK_WRONG_COMPLETION_MODE It is not valid to call this API if the receive queue is configured for 
 *                                           automatic task completion.
 * @retval NCP_ST_TASK_TOO_MANY_TASK_COMPLETIONS The number of task completions requested exceeds the number owed by this thread.
 */
 
NCP_API ncp_st_t
ncp_task_complete( 
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint8_t txQueueId,
    ncp_uint32_t numTasks,
    ncp_uint32_t *numTasksCompleted,
    ncp_bool_t wait);    
    
/*!
 * @fn ncp_st_t ncp_task_deferred_consume(ncp_task_tqs_hdl_t tqsHdl,
 *                                              ncp_uint32_t numTasks)
 *
 * @brief   Update the RxQ consumer index to reflect that numTasks tasks have been processed by the application.
 *          The NCA hardware will see the newly consumed iPCQ entries as available upon completion of this API.
 *          An error will be returned if the caller provides a numTasks value that is greater than the current 
 *          number of received,   but not consumed,  tasks.
 *          If an error condition is encountered,   this API will exit leaving the RxQ consumer index unchanged.
 *          
 *
 * @param[in]       tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in]       numTasks: the increment count for the RxQ consumer index.                  
 *
 * @retval NCP_ST_SUCCESS The consumer index was successfully incremented by numTasks
 * @retval  NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval  NCP_ST_INVALID_HANDLE The TQS handle failed validation.   The application must call ncp_task_tqs_bind to obtain a TQS handle,
 *                                and then use the handle that is returned in subsequent API calls.   The handle is valid until the thread 
 *                                calls ncp_task_tqs_unbind. 
 * @retval NCP_ST_TASK_INVALID_NUMTASKS The caller has provided a value for numTasks that is greater than the number of tasks
 *                                      currently being processed by the application.
 * @retval  NCP_ST_TASK_TQS_SHARING_VIOLATION The RX queue is not available for this thread.   See usage specified in the ncp_task_tqs_bind API.
 *                                            This error should not occur in this API.
 * @retval  NCP_ST_TASK_SENDQUEUE_CALLBACK_RECURSION_DETECTED  The ncp_task_deferred_consume API may not
 *                                                             be called from a task send or task free callback function.   
 * @retval NCP_ST_TASK_SEND_QUEUE_FULL sent zero or more task completions.   The caller must check numTasksCompleted to determine how many completions were
 *                                     actually sent.   Typically the caller would retry the operation at some point,   specifying (numTasks - numTasksCompleted)
 *                                     tasks.
 * @retval NCP_ST_TASK_WRONG_CONSUMPTION_MODE It is not valid to call this API if the receive queue is configured for 
 *                                           automatic task consumption. 
 */
 
NCP_API ncp_st_t
ncp_task_deferred_consume( 
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint32_t numTasks);

/*!
 * @fn ncp_st_t ncp_task_unscheduled_queue_push(
 *                  ncp_hdl_t ncpHdl,
 *                  ncp_uint32_t unscheduledQueueId, 
 *                  ncp_uint64_t data);
 *
 * @brief Push 64b (8B) of data to the specified uncheduled queue using memory
 *          mapped I/O (MMIO).
 *
 * @param[in] ncpHdl:  NCP handle returned by previous call to ncp_config
 * @param[in] unscheduledQueueId:   The ID of the unscheduled queue 
 * @param[in] data:                 The data to be pushed 
 *
 * @retval NCP_ST_SUCCESS No parameter errors were detected. MMIO writes may
 *              fail silently, so NCP_ST_SUCCESS does not guarantee that the
 *              data was successfully sent. The caller can use queue empty
 *              events to determine when to push data.
 * @retval NCP_ST_TASK_NO_GSM The software state is not valid. This may be due
 *          to corruption or a configuration problem.
 * @retval NCP_ST_INVALID_PARAMETER unscheduledQueueid is not between 0 and
 *          16383 (inclusive).
 */
NCP_API ncp_st_t
ncp_task_unscheduled_queue_push(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t unscheduledQueueId, 
    ncp_uint64_t data);
  
/*!
 * @fn ncp_st_t ncp_task_unscheduled_queue_pop(
 *                  ncp_hdl_t ncpHdl,
 *                  ncp_uint32_t unscheduledQueueId,
 *                  ncp_uint64_t *data);
 *
 * @brief Pop 64b (8B) of data from the specified unscheduled queue using
 *          memory mapped I/O (MMIO).  This API will return 0 (zero) if the
 *          queue is empty. The caller can use queue full events to determine
 *          when data is available.
 *
 * @param[in]       ncpHdl:  NCP handle returned by previous call to ncp_config
 * @param[in]       unscheduledQueueId:   The ID of the unscheduled queue
 * @param[out]      data:                 Pointer to the data that was popped from the unscheduled queue.   This API will return 0 (zero) if the 
 *                                        queue is empty.
 *
 * @retval NCP_ST_SUCCESS No parameter errors were detected.
 * @retval NCP_ST_TASK_NO_GSM The software state is not valid. This may be due
 *          to corruption or a configuration problem.
 * @retval NCP_ST_INVALID_PARAMETER data is NULL, or unscheduledQueueid is not
 *          between 0 and 16383 (inclusive).
 */
NCP_API ncp_st_t
ncp_task_unscheduled_queue_pop(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t unscheduledQueueId,
    ncp_uint64_t *data);

/*!
 * @fn ncp_st_t ncp_task_unscheduled_queue_pop_task(
 *                  ncp_task_tqs_hdl_t tqsHdl,
 *                  ncp_uint32_t unscheduledQueueId,
 *                  ncp_task_header_t **pHeader);
 *
 * @brief Like ncp_task_unscheduled_queue_pop(), this function pops 64b
 *        (8B) of data from the specified unscheduled queue using memory mapped
 *        I/O (MMIO). Unlike that function, this API is used when the caller
 *        knows that the popped data is a task header pointer (in the case that
 *        an application enqueued it over the VP ring). In addition to popping
 *        the unscheduled queue, this API changes the TBR state of the task
 *        header (and any PDU segments it points to) from
 *        NCP_TASK_TBR_STATE_FREE to caller-owned.
 *
 *        If ncp_task_unscheduled_queue_pop() is used and it returns a task
 *        header pointer, and the user attempts to perform task I/O (e.g.
 *        ncp_task_send() or ncp_task_free()) on that task, TBR will return
 *        NCP_ST_TASK_TBR_FATAL_POOL_CORRUPTION (if TBR is enabled).
 *        ncp_task_unscheduled_queue_pop_task() is designed to avoid this
 *        problem.
 *
 *        Since this function is called on unscheduled queues that only contain
 *        task pointers, an unscheduled queue pop value of 0x0 is interpreted
 *        to mean the queue was empty (since 0x0 is never a valid task
 *        pointer).
 *
 * @note: If this function pops a non-task pointer 8B value, undefined behavior
 *        will result. We recommend that the user allocate unscheduled queues
 *        for task pointers or for non-task pointers, but never a mix of the
 *        two.
 *
 * @note: For debug purposes, if the function returns the
 *        NCP_ST_TASK_INVALID_BUFFER error the function will still return
 *        the memory pointed to by the pHeader argument. If the user ignores
 *        this error and uses the buffer, undefined behavior will result.
 *
 * @param[in]  tqsHdl: TQS handle returned by previous call to
 *                  ncp_task_tqs_bind().
 * @param[in]  unscheduledQueueId: The ID of the unscheduled queue
 * @param[out] pHeader: Pointer to the header pointer that was popped from the
 *                  unscheduled queue.
 *
 * @retval NCP_ST_SUCCESS No parameter errors were detected.
 * @retval NCP_ST_TASK_NO_GSM The software state is not valid. This may be due
 *          to corruption or a configuration problem.
 * @retval NCP_ST_INVALID_PARAMETER pHeader is NULL, or unscheduledQueueId is
 *          not between 0 and 16383 (inclusive).
 * @retval NCP_ST_TASK_INVALID_BUFFER The task header, or one of its PDUs, is
 *          in a pool that this TQS's application profile does not map in.
 *          This check is *not* performed if the NCP_TASKIO_CHECK_DISABLED
 *          build flag is enabled.
 * @retval NCP_ST_TASK_TBR_FATAL_POOL_CORRUPTION The task header, or one of its
 *          PDUs, is not in the expected TBR state, and pool corruption is
 *          likely.
 * @retval NCP_ST_TASK_UNSCHEDULED_QUEUE_IS_EMPTY The unscheduled queue pop
 *          returned 0. Since 0x0 is never a valid task pointer, the queue is
 *          empty.
 */
NCP_API ncp_st_t
ncp_task_unscheduled_queue_pop_task(
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint32_t unscheduledQueueId,
    ncp_task_header_t **pHeader);


/*!
 * @fn ncp_st_t ncp_task_unscheduled_queue_depth_get(
 *                  ncp_hdl_t ncpHdl,
 *                  ncp_uint32_t unscheduledQueueId,
 *                  ncp_uint16_t *qDepth);
 *
 * @brief Return the number of elements in the specified queue.
 *
 * @param[in] ncpHdl: NCP handle returned by previous call to ncp_config
 * @param[in] unscheduledQueueId: The ID of the unscheduled queue
 * @param[out] qDepth: Pointer to memory that is filled with the number of
 *                      elements in the queue.
 *
 * @retval NCP_ST_SUCCESS No parameter errors were detected.
 * @retval NCP_ST_TASK_NO_GSM The software state is not valid. This may be due
 *          to corruption or a configuration problem.
 * @retval NCP_ST_INVALID_PARAMETER qDepth is NULL, or unscheduledQueueid is
 *          not between 0 and 16383 (inclusive).
 */
NCP_API ncp_st_t
ncp_task_unscheduled_queue_depth_get(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t unscheduledQueueId,
    ncp_uint16_t *pQDepth);

/*!
 * @fn ncp_st_t ncp_task_buffer_alloc(ncp_task_tqs_hdl_t tqsHdl,
 *                                  ncp_uint32_t numTaskBuffers, 
 *                                  ncp_uint32_t *numAllocated, 
 *                                  ncp_uint32_t *bufferSizes, 
 *                                  ncp_uint8_t   bufferPoolId, 
 *                                  void **taskBuffers, 
 *                                  ncp_bool_t wait);
 *
 * @brief   Allocate one or more task buffers from the specified task memory pool.   Fixed pool buffers
 *          (pool 31 encoded as 1) cannot be allocated using this interface.
 *
 * @param[in]       tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in]       numTaskBuffers: The maximum number of buffers to Allocate
 * @param[in, out]  numAllocated: The actual number of buffers allocated.
 * @param[in, out]  pointer to an array of buffer sizes,   where cell x corresponds to the size
 *                  of the buffer associated with taskBuffers[x].
 * @param[in]       bufferPoolId:   The buffer pool to use for all buffers allocated during this invocation
 *                                  of the API.   This is not an array of poolIds.
 * @param[in,out]   taskBuffers: pointer to an array of task buffer pointers.   The caller must ensure that the array is
 *                               sufficiently large to be able to hold numTaskBuffers buffer pointers.
 * @parameter[in]   wait:  If FALSE,   then allocate zero or more buffers.   The API will return if all buffers were allocated,
 *                         a blocking condition is encountered,  or an error was detected.
 *                         If TRUE,  then allocate one or more buffers.   The API will return if all buffers were allocated,
 *                         the timeout in the wait profile expired,   or an error was detected.                           
 *  
 *
 * @retval NCP_ST_SUCCESS - The requested number of buffers (numTaskBuffers) were allocated successfully.
 * @retval  NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval  NCP_ST_INVALID_HANDLE The TQS handle failed validation.   The application must call ncp_task_tqs_bind to obtain a TQS handle,
 *                                and then use the handle that is returned in subsequent API calls.   The handle is valid until the thread 
 *                                calls ncp_task_tqs_unbind. 
 * @retval  NCP_ST_INVALID_PARAMETER One or more of the parameters supplied is not valid.
 * @retval  NCP_ST_TASK_TQS_SHARING_VIOLATION The TX or RX queue is not available for this thread.   See usage specified in the ncp_task_tqs_bind API.
 *                                            This error should not occur in this API. 
 * @retval NCP_ST_TASK_BUFFER_POOL_NOT_CONFIGURED_FOR_TQS The TQS is not configured to use the pool that was specified.
 * @retval NCP_ST_TASK_BULK_REQUEST_TOO_BIG numTaskBuffers exceeds NCP_TASK_API_MAX_BULK_ITEM_COUNT.
 * @retval NCP_ST_NO_MEMORY - The caller must check numAllocated to determine how many buffers were allocated.   The caller may wish to
 *                            retry this operation requesting numTaskBuffers-numAllocated buffers of sizes bufferSizes+numAllocated,  and filling
 *                            starting at taskbuffers+numAllocated.
 * @retval NCP_ST_TASK_TQS_INVALID_POOL The pool that was specified is not valid for this TQS.
 * @retval NCP_ST_TASK_POOL_IS_BEING_REINITIALIZED The pool that was specified is temporarily unavailable.   Pool recovery is in progress.
 * @retval NCP_ST_TASK_NO_MME_ALLOCATOR The TQS does not have a valid allocator configured for this pool.
 * @retval NCP_ST_TASK_REQUEST_FOR_ZERO_LENGTH_TASK_BUFFER It is not valid to request a zero length task buffer.
 * @retval NCP_ST_TASK_BUFFSIZE_TOO_LARGE The buffer size requested is larger than the maximum block size configured for this pool.
 * @retval NCP_ST_TASK_TBR_INVALID_BUFFER TBR detected that the buffer does not belong to the pool
 * @retval NCP_ST_TASK_TBR_FATAL_POOL_CORRUPTION TBR detected that the buffer is not in the expected state,  and pool corruption is likely
 */     
NCP_API ncp_st_t
ncp_task_buffer_alloc( 
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint32_t numTaskBuffers, 
    ncp_uint32_t *numAllocated, 
    ncp_uint32_t *bufferSizes, 
    ncp_uint8_t   bufferPoolId, 
    void **taskBuffers, 
    ncp_bool_t wait);

/*!
 * @fn ncp_st_t ncp_task_buffer_free( ncp_task_tqs_hdl_t tqsHdl,
 *                                    ncp_uint8_t txQueueId,   
 *                                    ncp_uint32_t numTaskBuffers, 
 *                                    ncp_uint32_t *numFreed, 
 *                                    ncp_uint8_t bufferPoolId,
 *                                    void **taskBuffers,
 *                                    ncp_bool_t *mrefBitSet,
 *                                    ncp_bool_t wait);
 *
 * @brief   Free one or more task buffers from the specified task memory pool.   Fixed pool buffers
 *          (pool 31 encoded as 1) cannot be freed using this interface.
 *
 * @param[in]       tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in]       txQueueId; The TX queue (0 or 1) to use when freeing bufferPoolId corresponds to a shared pool (2..7)
 * @param[in]       numTaskBuffers: The maximum number of buffers to free
 * @param[in, out]  numFreed: The actual number of buffers freed.
 * @param[in]       bufferPoolId:   The buffer pool to use for all buffers freed during this invocation
 *                                  of the API.   This is not an array of poolIds.
 * @param[in]       taskBuffers: pointer to an array of task buffer pointers to be freed
 * @param[in]   mrefBitSet: pointer to an array of booleans where the value in cell x determines whether the mref bit should be set when 
 *                          freeing the buffer in cell x.   A null pointer may be used if the TQS is configured to use a CPU pool,  since mref 
 *                          does not apply to CPU pool buffers and a TQS cannot be configured to simultaneously use a CPU pool and one or more shared pools.
 * @parameter[in]   wait:  If FALSE,   then free zero or more buffers.   The API will return if all buffers were freed,
 *                         a blocking condition is encountered,  or an error was detected.
 *                         If TRUE,  then free zero or more buffers.   The API will return if all buffers were freed,
 *                         the timeout in the wait profile expired,   or an error was detected.                           
 *  
 *
 * @retval NCP_ST_SUCCESS - The requested number of buffers (numTaskBuffers) were freed successfully.
 * @retval  NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval  NCP_ST_INVALID_HANDLE The TQS handle failed validation.   The application must call ncp_task_tqs_bind to obtain a TQS handle,
 *                                and then use the handle that is returned in subsequent API calls.   The handle is valid until the thread 
 *                                calls ncp_task_tqs_unbind. 
 * @retval  NCP_ST_INVALID_PARAMETER One or more of the parameters supplied is not valid.
 * @retval  NCP_ST_TASK_TQS_SHARING_VIOLATION The TX or RX queue is not available for this thread.   See usage specified in the ncp_task_tqs_bind API.
 *                                            This error should not occur in this API. 
 * @retval NCP_ST_TASK_BUFFER_POOL_NOT_CONFIGURED_FOR_TQS The TQS is not configured to use the pool that was specified.
 * @retval NCP_ST_TASK_BULK_REQUEST_TOO_BIG numTaskBuffers exceeds NCP_TASK_API_MAX_BULK_ITEM_COUNT. 
 * @retval NCP_ST_NO_MEMORY - The caller must check numFreed to determine how many buffers were freed.   The caller may wish to
 *                            retry this operation requesting numTaskBuffers-numAllocated buffers starting at taskBuffers+numAllocated be freed,
 *                            using the mrefBit+numAllocated starting point in the mrefBit array.
 * @retval NCP_ST_TASK_BULK_REQUEST_TOO_BIG numTaskBuffers exceeds NCP_TASK_API_MAX_BULK_ITEM_COUNT.
 * @retval NCP_ST_TASK_POOL_IS_BEING_REINITIALIZED The pool that was specified is temporarily unavailable.   Pool recovery is in progress.
 * @retval  NCP_ST_TASK_SENDQUEUE_CALLBACK_RECURSION_DETECTED  The ncp_task_buffer_free API may not
 *                                                             be called from a task send or task free callback function, unless the caller is using 
 *                                                             a CPU managed task memory pool. 
 * @retval NCP_ST_TASK_SEND_QUEUE_FULL Check numFreed to determine the number of tasks that were freed,   if any.  This status code is not an error.
 * @retval NCP_ST_TASK_TQS_INVALID_POOL The TQS is not configured to use the specified pool.
 * @retval NCP_ST_INVALID_VALUE The buffer address is outside of the range of those addresses that are valid for the pool.
 * @retval NCP_ST_TASK_TBR_INVALID_BUFFER TBR detected that the buffer does not belong to the pool
 * @retval NCP_ST_TASK_TBR_FATAL_POOL_CORRUPTION TBR detected that the buffer is not in the expected state,  and pool corruption is likely
 */  
NCP_API ncp_st_t
ncp_task_buffer_free( 
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint8_t txQueueId,
    ncp_uint32_t numTaskBuffers, 
    ncp_uint32_t *numFreed, 
    ncp_uint8_t bufferPoolId,
    void **taskBuffers,
    ncp_bool_t *mrefBitSet,
    ncp_bool_t wait);

/*!
 * @fn ncp_st_t ncp_task_free(ncp_task_tqs_hdl_t tqsHdl,
 *                            ncp_uint8_t txQueueId,
 *                            ncp_uint32_t numTasks,
 *                            ncp_uint32_t *numFreed,
 *                            ncp_task_free_meta_t *metadata,
 *                            ncp_bool_t wait);
 *
 * @brief   Free one or more tasks.
  *
 * @param[in]       tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in]       txQueueId; The TX queue Id (0 or 1) to use when freeing and the bufferPoolId corresponds to a shared pool (2..7).
 *                             The TX queue Id is ignored for CPU pools.
 * @param[in]       numTasks: The maximum number of tasks to free
 * @param[in, out]  numFreed: pointer to a location where the RTE will return the actual number of tasks freed.
 * @param[in]       metadata:    pointer to an array of task free meta data structs.  
 * @parameter[in]   wait:  If FALSE,   then free zero or more tasks.   The API will return if all tasks were freed,
 *                         a blocking condition is encountered,  or an error was detected.
 *                         If TRUE,  then free zero or more tasks.   The API will return if all tasks were freed,
 *                         the timeout in the wait profile expired,   or an error was detected.                           
 *  
 * @note: if combinedHeader is true,  the caller must specify freeHeader in the corresponding
 *        meta data structure for that task.
 *
 * @note: if freeHeader is FALSE,   then the caller must provide a callback function,   and wait for the callback to 
 *        be executed prior to modifying the header.    Failure to do this may result in 
 *        corruption.
 *
 * @note: for bulk requests and where a callback function is required,   it is sufficient to 
 *        only specify a callback function for the last task in the bulk request.    This optimization
 *        takes advantage of the fact the frees are performed in order,   so free 1, 2, and 3,   are
 *        guaranteed to have been completed prior to free 4.
 *
 * @note    It is not valid to send a task, issue a task refill, free a task,  or issue task completions from the callback 
 *          function,   as that might result in taking a lock in a recursive call 
 *          scenario and therefore result in a deadlock.
 *
 * @retval NCP_ST_SUCCESS - The requested number of buffers (numTaskBuffers) were freed successfully.
 * @retval NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval  NCP_ST_INVALID_HANDLE The TQS handle failed validation.   The application must call ncp_task_tqs_bind to obtain a TQS handle,
 *                                and then use the handle that is returned in subsequent API calls.   The handle is valid until the thread 
 *                                calls ncp_task_tqs_unbind. 
 * @retval  NCP_ST_INVALID_PARAMETER One or more of the parameters supplied is not valid.
 * @retval  NCP_ST_TASK_TQS_SHARING_VIOLATION The TX or RX queue is not available for this thread.   See usage specified in the ncp_task_tqs_bind API.
 *                                            This error should not occur in this API. 
 * @retval NCP_ST_TASK_BUFFER_POOL_NOT_CONFIGURED_FOR_TQS The TQS is not configured to use the pool that was specified.
 * @retval NCP_ST_TASK_BULK_REQUEST_TOO_BIG numTaskBuffers exceeds NCP_TASK_API_MAX_BULK_ITEM_COUNT. 
 * @retval NCP_ST_NO_MEMORY - The caller must check numFreed to determine how many buffers were freed.   The caller may wish to
 *                            retry this operation requesting numTaskBuffers-numAllocated buffers starting at taskBuffers+numAllocated be freed,
 *                            using the mrefBit+numAllocated starting point in the mrefBit array.
 * @retval NCP_ST_TASK_BULK_REQUEST_TOO_BIG numTasks exceeds NCP_TASK_API_MAX_BULK_ITEM_COUNT.
 * @retval NCP_ST_TASK_POOL_IS_BEING_REINITIALIZED The pool that was specified is temporarily unavailable.   Pool recovery is in progress.
 * @retval  NCP_ST_TASK_SENDQUEUE_CALLBACK_RECURSION_DETECTED   The ncp_task_free API may not
 *                                                             be called from a task send or task free callback function, unless the caller is using 
 *                                                             a CPU managed task memory pool. 
 * @retval NCP_ST_TASK_SEND_QUEUE_FULL - The caller must check numFreed to determine how many buffers were freed.   The caller may wish to
 *                            retry this operation requesting numTasks-numAllocated be freed starting at tasks+numAllocated be freed.
 * @retval NCP_ST_TASK_TQS_INVALID_POOL The TQS is not configured to use the specified pool.
 * @retval NCP_ST_INVALID_VALUE The buffer address is outside of the range of those addresses that are valid for the pool.
 * @retval NCP_ST_TASK_TBR_INVALID_BUFFER TBR detected that the buffer does not belong to the pool
 * @retval NCP_ST_TASK_TBR_FATAL_POOL_CORRUPTION TBR detected that the buffer is not in the expected state,  and pool corruption is likely
 * @retval NCP_ST_TASK_TOO_MANY_TASK_COMPLETIONS The number of task completions requested exceeds the number owed by this thread.
 *
 */ 
NCP_API ncp_st_t
ncp_task_free(ncp_task_tqs_hdl_t tqsHdl,
              ncp_uint8_t  txQueueId,
              ncp_uint32_t numTasks,
              ncp_uint32_t *numFreed,
              ncp_task_free_meta_t *metadata,
              ncp_bool_t   wait);


/*!
 * @fn ncp_st_t ncp_task_mmio_buffer_alloc(ncp_task_tqs_hdl_t tqsHdl,
 *                                         ncp_uint8_t sharedPoolId,
 *                                         ncp_uint32_t bufferSize,
 *                                         void **buffer);
 *
 * @brief   Allocate a buffer from a shared pool (2..7) using the MMIO allocation interface.
 *
 * @param[in] tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in] sharedPooId: 2..7
 * @param[in] The buffer size 1-64K
 * @param[in,out] Pointer to a task buffer pointer.   The allocated buffer pointer will be returned here.
 *
 * @retval NCP_ST_SUCCESS - The buffer was successfully allocated
 * @retval NCP_ST_NO_MEMORY - The shared pool does not currently have any buffers available of the requested size.
 */
NCP_API ncp_st_t
ncp_task_mmio_buffer_alloc(
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint8_t sharedPoolId,
    ncp_uint8_t bufferSize,
    void **buffer);

/*!
 * @fn ncp_st_t ncp_task_mmio_buffer_free(ncp_task_tqs_hdl_t tqsHdl,
 *                                      ncp_uint8_t sharedPoolId,
 *                                      ncp_bool_t mrefBitIsSet,
 *                                      void *buffer);
 *
 * @brief   Free a buffer to a shared pool (2..7) using the MMIO allocation interface.
 *
 * @param[in] tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in] sharedPoolId: 2..7
 * @param[in] mrefBitIsSet: If TRUE mref bit will be set,   otherwise if will be zero.
 * @param[in,out] Pointer to the task buffer to free.   It is important to realize that
 *                only one buffer or header will be freed.   If one wishes to free an entire task
 *                then they would call this api headerPointer->ptrCnt times to free pduSegAddr0..5,
 *                and then call it to free the task Header itself if header->combinedHeader is false.
 *
 * @retval NCP_ST_SUCCESS - The buffer was successfully freed
 */
NCP_API ncp_st_t
ncp_task_mmio_buffer_free(
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint8_t sharedPoolId,
    ncp_bool_t mrefBitIsSet,
    void *buffer);

/*!
 * @fn ncp_st_t ncp_task_buffer_pool_get(ncp_task_tqs_hdl_t tqsHdl,
 *                                       void *buffer,
 *                                       ncp_uint8_t *bufferPoolId);
 *
 * @brief   Given a task buffer,   return the buffer poolId associated with that buffer.
 *
 * @param[in] tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in] buffer:  a valid task buffer pointer
 * @param[in,out] Pointer to the location where the buffer's poolId will be written.
 *          If the buffer belongs to the fixed pool (31),
 *          then the value 1 will be returned in the location pointed to by bufferPoolId.  
 *          This is the encoded value used when sending or receiving tasks. 
 *
 * @retval NCP_ST_SUCCESS - The buffer was valid,   and the buffer's bufferPoolId was returned
 * @retval NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval NCP_ST_INVALID_HANDLE The TQS handle failed validation.   The application must call ncp_task_tqs_bind to obtain a TQS handle,
 *                                and then use the handle that is returned in subsequent API calls.   The handle is valid until the thread 
 *                                calls ncp_task_tqs_unbind. 
 * NCP_ST_TASK_BUFFER_POOL_NOT_CONFIGURED_FOR_TQS The TQS is not configured to use the specified pool.
 * @retval NCP_ST_INVALID_PARAMETER One or more of the parameters supplied is not valid. 
 * @retval NCP_ST_TASK_INVALID_BUFFER The buffer address supplied is not contained in the specified pool.
 *
 */
NCP_API ncp_st_t
ncp_task_buffer_pool_get(
    ncp_task_tqs_hdl_t tqsHdl,
    void *buffer,
    ncp_uint8_t *bufferPoolId);

/*!
 * @fn ncp_st_t ncp_task_buffer_size_get(ncp_task_tqs_hdl_t tqsHdl,
 *                                       ncp_uint8_t   bufferPoolId,
 *                                       void *buffer,
 *                                       ncp_uint32_t *bufferSize);
 *
 * @brief   Given a task buffer,   return the buffer size (256, 2K, 16K, or 64K).   As noted,
 *          the size returned is related to one of the 4 buffer sizes,   and is unrelated to how
 *          much PDU data is present in the buffer.   If the buffer belongs to the fixed pool (31),
 *          then the value 1 should be provided for bufferPoolId.  This is the encoded value used when sending
 *          or receiving tasks.
 *         
 *
 * @param[in] tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in] bufferPoolId:   The buffer pool, 2-7, NCP_TASK_CPU_POOL_ALIAS, or 1 if fixed pool.
 * @param[in] buffer:  a valid task buffer pointer,   which may or may not point to the actual start of the buffer.
 * @param[in,out] bufferSize: Pointer to the location where the buffer's size will be written.   The value returned is in bytes.
 *              
 *
 * @retval NCP_ST_SUCCESS - The buffer was valid,   and the buffer size was returned
 * @retval NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval NCP_ST_INVALID_HANDLE The TQS handle failed validation.   The application must call ncp_task_tqs_bind to obtain a TQS handle,
 *                                and then use the handle that is returned in subsequent API calls.   The handle is valid until the thread 
 *                                calls ncp_task_tqs_unbind. 
 * @retval NCP_ST_TASK_BUFFER_POOL_NOT_CONFIGURED_FOR_TQS The TQS is not configured to use the specified pool.
 * @retval NCP_ST_INVALID_PARAMETER One or more of the parameters supplied is not valid. 
 * @retval NCP_ST_TASK_INVALID_BUFFER The buffer address supplied is not contained in the specified pool.
 */
NCP_API ncp_st_t
ncp_task_buffer_size_get(
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint8_t   bufferPoolId,
    void *buffer,
    ncp_uint32_t *bufferSize);
    
/*!
 * @fn ncp_st_t ncp_task_buffer_size_and_start_get(ncp_task_tqs_hdl_t tqsHdl,
 *                                       ncp_uint8_t   bufferPoolId,
 *                                       void *buffer,
 *                                       ncp_uint32_t *bufferSize,
 *                                       void **bufferStart);
 *
 * @brief   Given a task buffer,   return the buffer size (256, 2K, 16K, or 64K) and normalized starting address.   As noted,
 *          the size returned is related to one of the 4 buffer sizes,   and is unrelated to how
 *          much PDU data is present in the buffer.   If the buffer belongs to the fixed pool (31),
 *          then the value 1 should be provided for bufferPoolId.  This is the encoded value used when sending
 *          or receiving tasks.
 *
 * @param[in] tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in] bufferPoolId:   The buffer pool, 2-7 or NCP_TASK_CPU_POOL_ALIAS
 * @param[in] buffer:  a valid task buffer pointer,   which may or may not point to the actual start of the buffer.
 * @param[in,out] bufferSize: Pointer to the location where the buffer's size will be written.   The value returned is in bytes.
 * @param[in,out] bufferStart: Pointer to the location where the normalized buffer start address will be written.
 * 
 * @note:   This API returns the buffer start address,   and not the start of PDU data.   
 *
 * @retval NCP_ST_SUCCESS - The buffer was valid,   and the buffer size and buffer start address were returned
 * @retval NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval NCP_ST_INVALID_HANDLE The TQS handle failed validation.   The application must call ncp_task_tqs_bind to obtain a TQS handle,
 *                                and then use the handle that is returned in subsequent API calls.   The handle is valid until the thread 
 *                                calls ncp_task_tqs_unbind. 
 * @retval NCP_ST_TASK_BUFFER_POOL_NOT_CONFIGURED_FOR_TQS The TQS is not configured to use the specified pool.
 * @retval NCP_ST_INVALID_PARAMETER One or more of the parameters supplied is not valid. 
 * @retval NCP_ST_TASK_INVALID_BUFFER The buffer address supplied is not contained in the specified pool. 
 */
NCP_API ncp_st_t
ncp_task_buffer_size_and_start_get(
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint8_t   bufferPoolId,
    void *buffer,
    ncp_uint32_t *bufferSize,
    void **bufferStart);    

/*!
 * @fn ncp_st_t ncp_task_buffer_refill(ncp_task_tqs_hdl_t tqsHdl,
 *                                     ncp_uint8_t txQueueId,
 *                                     ncp_uint32_t numTaskBuffers,
 *                                     ncp_uint32_t *numRefilled,
 *                                     void **taskBuffers,
 *                                     ncp_bool_t wait);
 *
 * @brief   Perform a NCA task receive buffer refill operation.   That is,   replenish one of more
 *          CPU pool buffers previously consumed by task receive.   This API is not needed if the TQS 
 *          is configured to use shared pool(s).
 *
 * @param[in] tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in] txQueueId:   Which TX queue to use for returning the CPU pool buffers to the NCA.
 * @param[in] numTaskBuffers:   The number of buffers requested to be returned to the NCA
 * @param[in,out] numRefilled:  The actual number of buffers that were successfully returned
 * @param[in,out] taskBuffers:  Pointer to an array of task buffer pointers that is numTaskBuffers deep.
 * @param[in] wait:  FALSE - preform a refill of zero or more task buffers,   stopping if all buffers are sent,   a blocking condition is encountered, or an error is
 *                  detected.   TRUE - return (refill) every task buffer requested,   stopping early only if an error is detected,   or a wait timeout expires (see wait profiles).
 *              
 *
 * @retval NCP_ST_SUCCESS - The requested number of buffers was successfully returned to the NCA receive buffer pool.
 * @retval  NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval  NCP_ST_INVALID_HANDLE The TQS handle failed validation.   The application must call ncp_task_tqs_bind to obtain a TQS handle,
 *                                and then use the handle that is returned in subsequent API calls.   The handle is valid until the thread 
 *                                calls ncp_task_tqs_unbind. 
 * @retval  NCP_ST_INVALID_PARAMETER One or more of the parameters supplied is not valid.
 * @retval  NCP_ST_TASK_TQS_SHARING_VIOLATION The TX or RX queue is not available for this thread.   See usage specified in the ncp_task_tqs_bind API.
 *                                            This error should not occur in this API.
 * @retval  NCP_ST_TASK_SENDQUEUE_CALLBACK_RECURSION_DETECTED  The ncp_task_buffer_refill API may not
 *                                                             be called from a task send or task free callback function. 
 * @retval NCP_ST_TASK_SEND_QUEUE_FULL check numSent to determine the number of tasks that were sent,   if any.  This status code is not an error.
 * @retval NCP_ST_TASK_BULK_REQUEST_TOO_BIG numTasks exceeds NCP_TASK_API_MAX_BULK_ITEM_COUNT.
 * @retval NCP_ST_TASK_TBR_INVALID_BUFFER TBR detected that the buffer does not belong to the pool
 * @retval NCP_ST_TASK_TBR_FATAL_POOL_CORRUPTION TBR detected that the buffer is not in the expected state,  and pool corruption is likely
  */
NCP_API ncp_st_t
ncp_task_buffer_refill(
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint8_t txQueueId,
    ncp_uint32_t numTaskBuffers,
    ncp_uint32_t *numrefilled,
    void **taskBuffers,
    ncp_bool_t wait);

/*!
 * @fn ncp_st_t ncp_task_refill(ncp_task_tqs_hdl_t tqsHdl,
 *                                     ncp_uint8_t txQueueId,
 *                                     ncp_uint32_t numTasks,
 *                                     ncp_uint32_t *numTasksRefilled,
 *                                     ncp_task_header_t **headers,
 *                                     ncp_bool_t issueCompletions,
 *                                     ncp_bool_t wait);
 *
 * @brief   Perform a NCA task receive buffer refill operation,   using tasks instead of individual buffers.   Each task
 *          is described by a task header,   and may actually contain up to 7 individual task buffers if combinedHeader is FALSE.   
 *          The task(s) supplied to the API would typically be task(s) previously returned by a successful call to the ncp_task_recv() API.
 *
 * @param[in] tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in] txQueueId:   Which TX queue to use for returning the CPU pool buffers to the NCA.
 * @param[in] numTasks:   The number of tasks requested to be returned to the NCA
 * @param[in,out] numTasksRefilled:  The actual number of tasks were successfully returned
 * @param[in,out] taskBuffers:  Pointer to an array of task header pointers that is numTasks deep.
 * @param[in] wait:  FALSE - perform a refill of zero or more tasks,   stopping if all buffers are sent,   a blocking condition is encountered, or an error is
 *                  detected.   TRUE - return (refill) every task,   stopping early only if an error is detected,   or a wait timeout expires (see wait profiles).
 *              
 *
 * @retval NCP_ST_SUCCESS - The requested number of buffers was successfully returned to the NCA receive buffer pool.
 * @retval  NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval  NCP_ST_INVALID_HANDLE The TQS handle failed validation.   The application must call ncp_task_tqs_bind to obtain a TQS handle,
 *                                and then use the handle that is returned in subsequent API calls.   The handle is valid until the thread 
 *                                calls ncp_task_tqs_unbind. 
 * @retval  NCP_ST_INVALID_PARAMETER One or more of the parameters supplied is not valid.
 * @retval  NCP_ST_TASK_TQS_SHARING_VIOLATION The TX or RX queue is not available for this thread.   See usage specified in the ncp_task_tqs_bind API.
 *                                            This error should not occur in this API.
 * @retval  NCP_ST_TASK_SENDQUEUE_CALLBACK_RECURSION_DETECTED  The ncp_task_refill API may not
 *                                                             be called from a task send or task free callback function. 
 * @retval NCP_ST_TASK_SEND_QUEUE_FULL check numSent to determine the number of tasks that were sent,   if any.  This status code is not an error.
 * @retval NCP_ST_TASK_BULK_REQUEST_TOO_BIG numTasks exceeds NCP_TASK_API_MAX_BULK_ITEM_COUNT.
 * @retval NCP_ST_TASK_RX_QUEUE_IS_AUTOMATIC_COMPLETION Completion was requested,   but the TQS TX queue is configured for automatic
 *                                                      task completion.
 * @retval NCP_ST_TASK_TBR_INVALID_BUFFER TBR detected that the buffer does not belong to the pool
 * @retval NCP_ST_TASK_TBR_FATAL_POOL_CORRUPTION TBR detected that the buffer is not in the expected state,  and pool corruption is likely
 * @retval NCP_ST_TASK_TOO_MANY_TASK_COMPLETIONS The number of task completions requested exceeds the number owed by this thread.
 */
NCP_API ncp_st_t
ncp_task_refill(
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint8_t txQueueId,
    ncp_uint32_t numTasks, 
    ncp_uint32_t *numTasksRefilled,
    ncp_task_header_t **headers,
    ncp_bool_t issueCompletions,
    ncp_bool_t wait);

/*!
 * @fn ncp_st_t ncp_task_set_wait_profile(
 *                         ncp_task_tqs_hdl_t            tqsHdl,
 *                         ncp_task_api_class_t          api_class,
 *                         ncp_task_wait_profile_type_t  wait_profile,
 *                         ncp_uint32_t                  poll_timeout_value,  
 *                         ncp_task_poll_type_t          poll_type,
 *                         ncp_uint32_t                  sleep_poll_value);
 *
 * @brief This API is used to override the default blocking mode behavior associated with 
 * task send,   receive,   alloc,   and free APIs.
 *
 * @param[in] tqsHdl:    TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in] api_class: Any of the enum members of the type ncp_task_api_class_t.   This parameter 
 *                       describes which API class (send, receive, ....) the user defined wait profile will be 
 *                       applied to.   Note that not all behaviors are valid for all APIs.   
 * @param[in] wait_profile: This API allows threads to override the default
 *        wait semantics of Nca Task I/O APIs.  This API can be used to define
 *        the behavior when send, receive, or receive queue select APIs are
 *        called with wait==TRUE and a condition is encountered where the API
 *        would block.   If wait==FALSE,   then the wait profile is not
 *        executed,   and the application will immediately return with an
 *        appropriate status if the API cannot be completed.
 *
 *        This API can be used to define the behavior for alloc and free APIs
 *        when a buffer is not available,   or when a free cannot be completed
 *        due to insufficient space in the output PCQ.
 *
 *        NCP_TASK_WAIT_ISR is valid for receive,  send,  refill, and receive
 *        queue select APIs. It is also valid for free functions, but only for
 *        shared pools.
 *        This wait profile will wait for a hardware generated interrupt that
 *        signals that the wait condition has been remedied,   and that the
 *        queue is no longer full/empty.    The API will not return until the
 *        condition no longer exists,   or a shutdown is requested due to the
 *        TQS being disabled.
 *
 *        NCP_TASK_WAIT_WFI is valid only for receive APIs and only when the
 *        RTE us executing on the local ARM core(s) of a supported XLF device.
 *        NCP_TASK_WAIT_WFI is similar to WAIT_ISR,   except that the processor
 *        is put into a low power state while waiting for the hardware
 *        interrupt.   No other threads,  whether application or system will
 *        execute while the processor is in low power state.   It is the
 *        application responsibility to ensure that interrupt steering has been
 *        set up,   and that the executing application thread is executing on
 *        the same core that the interrupt will be delivered to (interrupt
 *        affinity ).   It is not valid to mix NCP_TASK_WAIT_WFI and
 *        NCP_TASK_WAIT_ISR on the same core,  and additionally it is expected
 *        that NCP_TASK_WAIT_WFI will typically be used only when a single
 *        thread is receiving on any particular core.
 *
 *        NCP_TASK_WAIT_TIMEOUT is used to poll the interface,   rather than
 *        wait for an interrupt.   The poll_timeout and poll_type will be used
 *        to control how to poll and how long to poll before returning to the
 *        caller.
 *
 *        NCP_TASK_API_CLASS_REFILL cannot be specified for NcaV1 platforms
 *        (34xx/35xx).
 *
 *        The default wait profiles are:
 *           - CLASS_RECV:            NCP_TASK_WAIT_ISR, poll timeout = 0
 *           - CLASS_SEND_TXQ0:   NCP_TASK_WAIT_TIMEOUT, poll timeout = -1
 *           - CLASS_SEND_TXQ1:   NCP_TASK_WAIT_TIMEOUT, poll timeout = -1
 *           - CLASS_ALLOC:       NCP_TASK_WAIT_TIMEOUT, poll timeout = -1
 *           - CLASS_REFILL_TXQ0: NCP_TASK_WAIT_TIMEOUT, poll timeout = -1
 *           - CLASS_REFILL_TXQ1: NCP_TASK_WAIT_TIMEOUT, poll timeout = -1
 *           - CLASS_FREE_TXQ0:   NCP_TASK_WAIT_TIMEOUT, poll timeout = -1
 *           - CLASS_FREE_TXQ1:   NCP_TASK_WAIT_TIMEOUT, poll timeout = -1
 *
 *        The default wait profiles that use NCP_TASK_WAIT_TIMEOUT use sleep
 *        polling in user-space and hard polling in kernel-space.
 *
 * @param[in] poll_timeout_value : Units are Microseconds.  This parameter determines how long to poll before either returning to the application (NCP_TASK_WAIT_TIMEOUT),
 *                       or before entering the kernel to wait for an interrupt (WAIT_ISR or NCP_TASK_WAIT_WFI).   A value of -1 
 *                       means poll forever.    The poll_type parameter is used to determine how to poll (hard vs sleep).                                 
 * @param[in] poll_type: Sets the poll method to be performed by the RTE.   NCP_TASK_POLL_TYPE_HARD_POLL will cause the RTE to
 *                       poll the interface repeatedly without performing any operations to specifically relinquish the CPU so that
 *                       other threads can be scheduled.   The poll type NCP_TASK_POLL_TYPE_SLEEP_POLL will cause the RTE to 
 *                       call sleep after each poll.   For most operating systems,   this will allow other threads to be scheduled.
 * @param[in] sleep_poll_value:  Units are microseconds.  If NCP_TASK_POLL_TYPE_SLEEP_POLL was specified,   then this parameter defines the amount of time
 *                       to sleep after each non productive poll.   For most operating systems,   a value of zero will result in 
 *                       scheduling other threads of equal or higher priority.                        
 *
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured,  or the application has not attached to the configuration.
 * @retval NCP_ST_INVALID_HANDLE the taskHdl provided is not valid
 * @retval NCP_ST_INVALID_VALUE One or more input parameters are invalid.
 * @retval NCP_ST_TASK_BAD_WFI_TARGET WFI is only supported for a subset of device architectures; ARM
 * @retval NCP_ST_INVALID_WAIT_PROFILE_FOR_POOL_TYPE A wait profile type of WAIT_ISR was specified for pool operations
 *                                                   but the pool type is CPU pool.
*/
ncp_st_t
ncp_task_set_wait_profile(
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_task_api_class_t api_class,
    ncp_task_wait_profile_type_t wait_profile,
    ncp_uint32_t poll_timeout_value,
    ncp_task_poll_type_t poll_type,
    ncp_uint32_t sleep_poll_value);

/*!
 * @fn ncp_st_t ncp_task_buffer_quota_transfer(
 *                  ncp_task_tqs_hdl_t tqsHdl,
 *                  ncp_uint8_t txQueueId,
 *                  ncp_uint32_t numDescs,
 *                  ncp_uint32_t *numTransferred,
 *                  ncp_task_buffer_desc_t *descs,
 *                  ncp_task_buffer_transfer_done_fn_t *fns,
 *                  void **transferDoneArgs,
 *                  ncp_uint8_t destTQS,
 *                  ncp_bool_t wait);
 *
 * @brief Decrement the caller's memory quota count and increment the
 *          destination TQS's memory quota count for each descriptor supplied.
 *          Hardware maintains memory quotas for shared pools only. If a quota
 *          group's quota is maxed-out, it will be unable to allocate shared
 *          pool buffers until it reduces its quota count by freeing buffers.
 *
 *        To give a copy of a buffer to another thread, the user must first
 *          increment the buffer's reference count, then perform the quota
 *          transfer, then (upon quota transfer completion) give the buffer to
 *          the destination.
 *
 * @param[in] tqsHdl: TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in] txQueueId: Which TX queue to use to issue the quota transfer
 *              operations.
 * @param[in] numDescs: The number of quota transfer operations requested.
 * @param[in,out] numTransferred: The actual number of quota transfer
 *                                  operations successfully completed.
 * @param[in] descs: Array of buffer descriptors.
 * @param[in] fns: Pointer to an array of transfer done functions. If a
 *                  function pointer is non-NULL, the RTE will perform the
 *                  callback during a future send-type operation when the
 *                  corresponding quota transfer operation is complete. If
 *                  fns is NULL, no callback function(s) will be registered.
 * @param[in] transferDoneArgs: Pointer to an array of transfer done function
 *                              arguments. Must be non-NULL if fns is non-NULL.
 * @param[in] destTQS: ID of the TQS whose quota count will be increased.
 * @param[in] wait: FALSE - perform zero or more transfer operations, stopping
 *                      if all transfers are sent, a blocking condition is
 *                      encountered, or an error is detected.
 *                  TRUE - perform every transfer operation, stopping early
 *                      only if an error is detected or a wait timeout expires
 *                      (see wait profiles).
 *
 * @retval NCP_ST_SUCCESS The requested number of transfer operations were
 *              completed.
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 * @retval NCP_ST_SEND_QUEUE_FULL The operation blocked on a full send queue
 *              before completing all transfer operations.
 * @retval NCP_ST_INVALID_PARAMETER numTransferred or descs are NULL, txQueueId
 *              is not NCP_TASK_TXQ_0 or NCP_TASK_TXQ_1, one of the descriptor's
 *              pools is not a shared pool, or fns is non-NULL but
 *              transferDoneArgs is NULL.
 * @retval NCP_ST_TASK_BULK_REQUEST_TOO_BIG numDescs exceeds
 *              NCP_TASK_API_MAX_BULK_ITEM_COUNT.
 * @retval NCP_ST_TASK_SENDQUEUE_CALLBACK_RECURSION_DETECTED  The
 *              ncp_task_buffer_quota_transfer API may not be called from a
 *              task send or task free callback function.
 */
NCP_API ncp_st_t
ncp_task_buffer_quota_transfer(
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint8_t txQueueId,
    ncp_uint32_t numDescs,
    ncp_uint32_t *numTransferred,
    ncp_task_buffer_desc_t *descs,
    ncp_task_buffer_transfer_done_fn_t *fns,
    void **transferDoneArgs,
    ncp_uint8_t destTQS,
    ncp_bool_t wait);

/*!
 * @fn ncp_st_t ncp_task_quota_transfer(
 *                  ncp_task_tqs_hdl_t tqsHdl,
 *                  ncp_uint8_t txQueueId,
 *                  ncp_uint32_t numTasks,
 *                  ncp_uint32_t *numTransferred,
 *                  ncp_task_header_t **tasks,
 *                  ncp_task_transfer_done_fn_t *fns,
 *                  void **transferDoneArgs,
 *                  ncp_bool_t *transferHeader,
 *                  ncp_uint8_t destTQS,
 *                  ncp_bool_t wait);
 *
 * @brief Decrement the caller's memory quota count and increment the
 *          destination TQS's memory quota count for each segment in each task
 *          supplied, optionally including the task header. Hardware maintains
 *          memory quotas for shared pools only. If a quota group's quota is
 *          maxed-out, it will be unable to allocate shared pool buffers until
 *          it reduces its quota count by freeing buffers.
 *
 *        To give a copy of a buffer to another thread, the user must first
 *          increment the buffer's reference count, then perform the quota
 *          transfer, then (upon quota transfer completion) give the buffer to
 *          the destination.
 *
 * @param[in] tqsHdl: TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in] txQueueId: Which TX queue to use to issue the quota transfer
 *              operations.
 * @param[in] numTasks: The number of per-task quota transfer operations
 *                      requested.
 * @param[in,out] numTransferred: The actual number of quota transfer
 *                                  operations successfully completed.
 * @param[in] tasks: Array of task header pointers.
 * @param[in] fns: Pointer to an array of transfer done functions. If a
 *                  function pointer is non-NULL, the RTE will perform the
 *                  callback during a future send-type operation when the
 *                  corresponding quota transfer operation is complete. If
 *                  fns is NULL, no callback function(s) will be registered.
 * @param[in] transferDoneArgs: Pointer to an array of transfer done function
 *                              arguments. Must be non-NULL if fns is non-NULL.
 * @param[in] transferHeader: Array of booleans indicating whether or not to
 *                              include the task header buffer in the quota
 *                              transfer operation. This flag is ignored if
 *                              the task uses a combined header.
 * @param[in] destTQS: ID of the TQS whose quota count will be increased.
 * @param[in] wait: FALSE - perform zero or more transfer operations, stopping
 *                      if all transfers are sent, a blocking condition is
 *                      encountered, or an error is detected.
 *                  TRUE - perform every transfer operation, stopping early
 *                      only if an error is detected or a wait timeout expires
 *                      (see wait profiles).
 *
 * @retval NCP_ST_SUCCESS The requested number of transfer operations were
 *              completed.
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 * @retval NCP_ST_SEND_QUEUE_FULL The operation blocked on a full send queue
 *              before completing all transfer operations.
 * @retval NCP_ST_INVALID_PARAMETER numTransferred or descs are NULL, txQueueId
 *              is not NCP_TASK_TXQ_0 or NCP_TASK_TXQ_1, one of the buffer
 *              pools is not a shared pool, or fns is non-NULL but
 *              transferDoneArgs is NULL.
 * @retval NCP_ST_TASK_BULK_REQUEST_TOO_BIG numDescs exceeds
 *              NCP_TASK_API_MAX_BULK_ITEM_COUNT.
 * @retval NCP_ST_TASK_SENDQUEUE_CALLBACK_RECURSION_DETECTED  The
 *              ncp_task_quota_transfer API may not be called from a
 *              task send or task free callback function.
 */
NCP_API ncp_st_t
ncp_task_quota_transfer(
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint8_t txQueueId,
    ncp_uint32_t numTasks,
    ncp_uint32_t *numTransferred,
    ncp_task_header_t **tasks,
    ncp_task_transfer_done_fn_t *fns,
    void **transferDoneArgs,
    ncp_bool_t *transferHeader,
    ncp_uint8_t destTQS,
    ncp_bool_t wait);

/*!
 * @fn ncp_st_t ncp_task_buffer_refCnt_increment(
 *                  ncp_task_tqs_hdl_t tqsHdl,
 *                  ncp_uint8_t txQueueId,
 *                  ncp_uint32_t numDescs,
 *                  ncp_uint32_t *numIncremented,
 *                  ncp_task_buffer_desc_t *descs,
 *                  ncp_task_refCnt_inc_done_fn_t *fns,
 *                  void **refCntIncDoneArgs,
 *                  ncp_bool_t wait);
 *
 * @brief Increment a buffer's reference count.
 *
 *        Hardware maintains buffer reference counts for shared pools only.
 *        Once the reference count operation completes (indicated by the
 *        callback function) the user must set buffer's mref bit to TRUE
 *        for future task I/O operations.
 *
 *        To give a copy of a buffer to another thread, the user must first
 *        increment the buffer's reference count, then perform a quota
 *        transfer, then (upon quota transfer completion) give the buffer to
 *        the destination.
 *
 * @param[in] tqsHdl: TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in] txQueueId: Which TX queue to use to issue the reference count
 *              increment operations.
 * @param[in] numDescs: The number of reference count increment operations
 *              requested.
 * @param[in,out] numIncremented: The actual number of reference count increment
 *                                  operations successfully completed.
 * @param[in] descs: Array of buffer descriptors.
 * @param[in] fns: Pointer to an array of increment done functions. The RTE
 *                  will perform the callback during a future send-type
 *                  operation when the corresponding reference count increment
 *                  operation is complete.
 * @param[in] refCntIncDoneArgs: Pointer to an array of reference count
 *                  increment done function arguments.
 * @param[in] wait: FALSE - issue zero or more increment operations, stopping
 *                      if all operations are issued, a blocking condition is
 *                      encountered, or an error is detected.
 *                  TRUE - issue every increment operation, stopping early
 *                      only if an error is detected or a wait timeout expires
 *                      (see wait profiles).
 *
 * @retval NCP_ST_SUCCESS The requested number of reference count increment
 *              operations were completed.
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 * @retval NCP_ST_SEND_QUEUE_FULL The operation blocked on a full send queue
 *              before completing all reference count increment operations.
 * @retval NCP_ST_INVALID_PARAMETER numTransferred or descs are NULL, txQueueId
 *              is not NCP_TASK_TXQ_0 or NCP_TASK_TXQ_1, one of the
 *              descriptor's pools is not a shared pool, fns is NULL, or
 *              refCntIncDoneArgs is NULL.
 * @retval NCP_ST_TASK_BULK_REQUEST_TOO_BIG numDescs exceeds
 *              NCP_TASK_API_MAX_BULK_ITEM_COUNT.
 * @retval NCP_ST_TASK_SENDQUEUE_CALLBACK_RECURSION_DETECTED  The
 *              ncp_task_buffer_refCnt_increment API may not be called from a
 *              task send or task free callback function.
 */
NCP_API ncp_st_t
ncp_task_buffer_refCnt_increment(
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint8_t txQueueId,
    ncp_uint32_t numDescs,
    ncp_uint32_t *numIncremented,
    ncp_task_buffer_desc_t *descs,
    ncp_task_buffer_refCnt_inc_done_fn_t *fns,
    void **refCntIncDoneArgs,
    ncp_bool_t wait);

/*!
 * @fn ncp_st_t ncp_task_refCnt_increment(
 *                  ncp_task_tqs_hdl_t tqsHdl,
 *                  ncp_uint8_t txQueueId,
 *                  ncp_uint32_t numTasks,
 *                  ncp_uint32_t *numIncremented,
 *                  ncp_task_header_t **tasks,
 *                  ncp_task_refCnt_inc_done_fn_t *fns,
 *                  void **refCntIncDoneArgs,
 *                  ncp_bool_t wait);
 *
 * @brief Increment a task's PDUs' reference counts. If the header is not
 *        combined, its reference count is _not_ incremented. In that case, the
 *        user must call ncp_task_buffer_refCnt_increment() to increment the
 *        header buffer's reference count.
 *
 *        Hardware maintains buffer reference counts for shared pools only.
 *        Once the reference count operation completes (indicated by the
 *        callback function) the user must set buffer's mref bit to TRUE
 *        for future task I/O operations.
 *
 *        To give a copy of a buffer to another thread, the user must first
 *        increment the buffer's reference count, then perform a quota
 *        transfer, then (upon quota transfer completion) give the buffer to
 *        the destination.
 *
 * @param[in] tqsHdl: TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in] txQueueId: Which TX queue to use to issue the reference count
 *              increment operations.
 * @param[in] numTasks: The number of reference count increment operations
 *              requested. Each PDU in the task will have its reference count
 *              incremented, except the task header.
 * @param[in,out] numIncremented: The actual number of reference count increment
 *                                  operations successfully completed.
 * @param[in] tasks: Array of task header pointers.
 * @param[in] fns: Pointer to an array of increment done functions. The RTE
 *                  will perform the callback during a future send-type
 *                  operation when the corresponding reference count increment
 *                  operation is complete.
 * @param[in] refCntIncDoneArgs: Pointer to an array of reference count
 *                  increment done function arguments.
 * @param[in] wait: FALSE - issue zero or more increment operations, stopping
 *                      if all operations are issued, a blocking condition is
 *                      encountered, or an error is detected.
 *                  TRUE - issue every increment operation, stopping early
 *                      only if an error is detected or a wait timeout expires
 *                      (see wait profiles).
 *
 * @retval NCP_ST_SUCCESS The requested number of reference count increment
 *              operations were completed.
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 * @retval NCP_ST_SEND_QUEUE_FULL The operation blocked on a full send queue
 *              before completing all reference count increment operations.
 * @retval NCP_ST_INVALID_PARAMETER numTransferred or descs are NULL, txQueueId
 *              is not NCP_TASK_TXQ_0 or NCP_TASK_TXQ_1, one of the buffer
 *              pools is not a shared pool, fns is NULL, or refCntIncDoneArgs
 *              is NULL.
 * @retval NCP_ST_TASK_BULK_REQUEST_TOO_BIG numDescs exceeds
 *              NCP_TASK_API_MAX_BULK_ITEM_COUNT.
 * @retval NCP_ST_TASK_SENDQUEUE_CALLBACK_RECURSION_DETECTED  The
 *              ncp_task_refCnt_increment API may not be called from a
 *              task send or task free callback function.
 */
NCP_API ncp_st_t
ncp_task_refCnt_increment(
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint8_t txQueueId,
    ncp_uint32_t numTasks,
    ncp_uint32_t *numIncremented,
    ncp_task_header_t **tasks,
    ncp_task_refCnt_inc_done_fn_t *fns,
    void **refCntIncDoneArgs,
    ncp_bool_t wait);

/*!
 * @fn ncp_st_t ncp_task_tqs_queue_group_set(
 *          ncp_hdl_t ncpHdl,
 *          ncp_uint32_t tqsId,
 *          ncp_task_queue_group_set_t pGrp[8],
 *          ncp_uint8_t numQueueGroups);
 *
 * @brief   This function allows the caller to change the set of queue groups
 *          that feed a TQS. If this TQS is the last consumer of one of its
 *          current group's NCA queues, and that group isn't included in the
 *          new queue group set, those queues must be disabled before calling
 *          this function. For each NCA queue that feeds the queue groups
 *          listed in pGrp, its virtual region must be the same as the TQS's
 *          and its pools must be a subset of the TQS's allowed pools.
 *
 *          To remove all queue groups that feed a TQS, set numQueueGroups to
 *          0.
 *
 * @param[in] ncpHdl: NCP handle returned by previous call to ncp_config.
 * @param[in] tqsId: the ID of the TQS to modify
 * @param[in] pGrp: the list of queue group IDs and their priorities
 * @param[in] numQueueGroups: the depth of pGrp. Must be <= 8.
 *
 * @retval NCP_ST_SUCCESS the TQS's queue groups were successfully changed.
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 * @retval NCP_ST_INVALID_PARAMETER tqsId isn't between 0 and 85, numQueueGroups
 *              isn't between 0 and 8, or pGrp is NULL.
 * @retval NCP_ST_TASK_QUESET_NOT_IN_LOCAL_DOMAIN The TQS specified by tqsId
 *              is not located in the caller's OS domain
 * @retval NCP_ST_TASK_TQS_NOT_CONFIGURED The TQS specified by tqsId is not
 *              configured.
 * @retval NCP_ST_TASK_QUEUE_GROUP_HAS_ENABLED_NCA_QUEUE This TQS is the last
 *              consumer of one of its current groups, and one of that group's
 *              NCA queues isn't disabled.
 * @retval NCP_ST_TASK_VIRTUAL_REGION_MISMATCH The TQS's virtual region doesn't
 *              match the virtual region of one of the NCA queues that feeds
 *              one of the queue groups specified in pGrp.
 * @retval NCP_ST_TASK_ALLOWED_POOLS_MISMATCH The TQS's allowed pools set is
 *              not a superset of one of pGrp's queue group's NCA queues'
 *              pools.
 */
NCP_API ncp_st_t
ncp_task_tqs_queue_group_set(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t tqsId,
    ncp_task_queue_group_set_t pGrp[8],
    ncp_uint8_t numQueueGroups);

/*!
 * @fn ncp_st_t ncp_task_tqs_queue_group_get(
 *          ncp_hdl_t ncpHdl,
 *          ncp_uint32_t tqsId,
 *          ncp_task_queue_group_set_t pGrp[8],
 *          ncp_uint8_t *pNumQueueGroups);
 *
 * @brief   This function allows the caller to determine the set of queue
 *          groups that feed a TQS.
 *
 * @param[in] ncpHdl: NCP handle returned by previous call to ncp_config.
 * @param[in] tqsId: the ID of the TQS to modify
 * @param[out] pGrp: the list of queue group IDs and their priorities
 * @param[out] numQueueGroups: A pointer to the depth of pGrp.
 *
 * @retval NCP_ST_SUCCESS the TQS's queue groups were successfully returned.
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 * @retval NCP_ST_INVALID_PARAMETER tqsId isn't between 0 and 85, or pGrp or
 *              pNumQueueGroups is NULL.
 * @retval NCP_ST_TASK_QUESET_NOT_IN_LOCAL_DOMAIN The TQS specified by tqsId
 *              is not located in the caller's OS domain
 * @retval NCP_ST_TASK_TQS_NOT_CONFIGURED The TQS specified by tqsId is not
 *              configured.
 */
NCP_API ncp_st_t
ncp_task_tqs_queue_group_get(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t tqsId,
    ncp_task_queue_group_set_t pGrp[8],
    ncp_uint8_t *pNumQueueGroups);

/*!
 * @fn ncp_st_t ncp_task_nca_queue_group_set(
 *          ncp_hdl_t ncpHdl,
 *          ncp_uint32_t ncaQueueId,
 *          ncp_uint32_t queueGroupId);
 *
 * @brief   This function allows the caller to change the queue group that an
 *          NCA queue feeds. For each iPCQ that is fed by queueGroupId, its
 *          application profile's pool set must be a superset of this queue's
 *          pools.
 *
 * @param[in] ncpHdl: NCP handle returned by previous call to ncp_config.
 * @param[in] ncaQueueId: the NCA queue ID.
 * @param[in] queueGroupId: the queue group ID.
 *
 * @retval NCP_ST_SUCCESS the TQS's queue groups were successfully changed.
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 * @retval NCP_ST_INVALID_PARAMETER ncaQueueId is greater than 203, or
 *              queueGroupId is greater than 255, or queueGroupId refers
 *              to an unconfigured queue group.
 * @retval NCP_ST_TASK_NCA_QUEUE_NOT_CONFIGURED the specified NCA queue is not
 *              configured.
 * @retval NCP_ST_TASK_ALLOWED_POOLS_MISMATCH The NCA queue's pools are not a
 *              subset of one of the TQS's that the queue group specified by
 *              queueGroupId feeds.
 */
NCP_API ncp_st_t
ncp_task_nca_queue_group_set(
    ncp_hdl_t    ncpHdl,
    ncp_uint32_t ncaQueueId,
    ncp_uint32_t queueGroupId);

/*!
 * @fn ncp_st_t ncp_task_queue_group_add(
 *          ncp_hdl_t ncpHdl,
 *          ncp_uint32_t queueGroupId,
 *          ncp_task_resource_name_t *name,
 *          ncp_ncav3_recv_queue_type_t ordering);
 *
 * @brief   This function creates a new queue group with the specified 
 *          queueGroupId, name, and ordering attribute.
 *
 * @param[in] ncpHdl: NCP handle returned by previous call to ncp_config.
 * @param[in] queueGroupId: the queue group ID.
 * @param[in] name: the queue group's name.
 * @param[in] ordering: the queue group's ordering type.
 *
 * @retval NCP_ST_SUCCESS the queue group is successfully added.
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 * @retval NCP_ST_INVALID_PARAMETER queueGroupId is greater than 254 (group 255
 *              is reserved for unscheduled queues), or it corresponds to an
 *              existing queue group.
 * @retval NCP_ST_TASK_BAD_RESOURCE_NAME name matches the name of an existing
 *              queue group.
 */
NCP_API ncp_st_t
ncp_task_queue_group_add(
    ncp_hdl_t    ncpHdl,
    ncp_uint32_t queueGroupId,
    ncp_task_resource_name_t *name,
    ncp_ncav3_recv_queue_type_t ordering);

/*!
 * @fn ncp_st_t ncp_task_queue_group_delete(
 *          ncp_hdl_t ncpHdl,
 *          ncp_uint32_t queueGroupId);
 *
 * @brief   This function deletes a queue group specified by its ID. The queue
 *          group must not have any NCA queues connected when calling this
 *          function, and this queue group must not feed any iPCQs.
 *
 * @param[in] ncpHdl: NCP handle returned by previous call to ncp_config.
 * @param[in] queueGroupId: the queue group ID.
 *
 * @retval NCP_ST_SUCCESS the queue group is successfully deleted.
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 * @retval NCP_ST_INVALID_PARAMETER queueGroupId is greater than 254 (group 255
 *              is reserved for unscheduled queues), or it does not correspond
 *              to an existing queue group.
 * @retval NCP_ST_TASK_QUEUE_GROUP_HAS_ENABLED_NCA_QUEUE This queue group has
 *              NCA queues connected to it.
 * @retval NCP_ST_TASK_QUEUE_GROUP_FEEDS_IPCQ There is at least one iPCQ that
 *              is configured to receive tasks from this queue group.
 */
NCP_API ncp_st_t
ncp_task_queue_group_delete(
    ncp_hdl_t    ncpHdl,
    ncp_uint32_t queueGroupId);

/*!
 * @fn ncp_st_t ncp_task_queue_group_modify(
 *          ncp_hdl_t ncpHdl,
 *          ncp_uint32_t queueGroupId,
 *          ncp_ncav3_recv_queue_type_t ordering);
 *
 * @brief   This function modifies a queue group's ordering attribute. The queue
 *          group must not have any NCA queues connected when calling this
 *          function.
 *
 * @param[in] ncpHdl: NCP handle returned by previous call to ncp_config.
 * @param[in] queueGroupId: the queue group ID.
 *
 * @retval NCP_ST_SUCCESS the queue group is successfully modified.
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 * @retval NCP_ST_INVALID_PARAMETER queueGroupId is greater than 254 (group 255
 *              is reserved for unscheduled queues), or it does not correspond
 *              to an existing queue group.
 * @retval NCP_ST_TASK_QUEUE_GROUP_HAS_ENABLED_NCA_QUEUE This queue group has
 *              NCA queues connected to it.
 */
NCP_API ncp_st_t
ncp_task_queue_group_modify(
    ncp_hdl_t    ncpHdl,
    ncp_uint32_t queueGroupId,
    ncp_ncav3_recv_queue_type_t ordering);

/*!
 * @fn ncp_st_t ncp_task_queue_group_membership_get(
 *          ncp_hdl_t ncpHdl,
 *          ncp_uint32_t ncaQueueId,
 *          ncp_uint32_t *queueGroupId);
 *
 * @brief   This function allows the caller to determine the queue group that
 *          an NCA queue feeds.
 *
 * @param[in] ncpHdl: NCP handle returned by previous call to ncp_config.
 * @param[in] ncaQueueId: the NCA queue ID.
 * @param[out] queueGroupId: a pointer to the queue group ID.
 *
 * @retval NCP_ST_SUCCESS the TQS's queue groups were successfully changed.
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 * @retval NCP_ST_INVALID_PARAMETER ncaQueueId is greater than 203, or
 *              queueGroupId is NULL.
 */
ncp_st_t
ncp_task_queue_group_membership_get(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t ncaQueueId,
    ncp_uint32_t *queueGroupId);

/*!
 * @fn ncp_st_t ncp_task_queue_group_name_get(
 *          ncp_hdl_t ncpHdl,
 *          ncp_uint32_t queueGroupId,
 *          ncp_task_resource_name_t *name);
 *
 * @brief   This function allows the caller to determine a queue group's name.
 *
 * @param[in] ncpHdl: NCP handle returned by previous call to ncp_config.
 * @param[in] queueGroupId: the queue group's ID.
 * @param[out] name: a pointer to the queue group's name.
 *
 * @retval NCP_ST_SUCCESS the queue group's name was found and returned.
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 * @retval NCP_ST_INVALID_PARAMETER queueGroupId is greater than 255, or name
 *              is NULL.
 */
NCP_API ncp_st_t
ncp_task_queue_group_name_get(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t queueGroupId,
    ncp_task_resource_name_t *name);

/*!
 * @fn ncp_st_t ncp_task_queue_group_id_get(
 *          ncp_hdl_t ncpHdl,
 *          ncp_task_resource_name_t *name,
 *          ncp_uint32_t *queueGroupId);
 *
 * @brief   This function allows the caller to find a queue group's ID by its
 *          name.
 *
 * @param[in] ncpHdl: NCP handle returned by previous call to ncp_config.
 * @param[in] name: a pointer to the queue group's name.
 * @param[out] queueGroupId: a pointer to the queue group's ID.
 *
 * @retval NCP_ST_SUCCESS the queue group's ID was found and returned.
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 * @retval NCP_ST_INVALID_PARAMETER name or queueGroupId is NULL.
 * @retval NCP_ST_TASK_BAD_RESOURCE_NAME the resource name is invalid.
 */
NCP_API ncp_st_t
ncp_task_queue_group_id_get(
    ncp_hdl_t ncpHdl,
    ncp_task_resource_name_t *name,
    ncp_uint32_t *queueGroupId);

/*!
 * @fn ncp_st_t ncp_task_tqs_name_get(
 *          ncp_hdl_t ncpHdl,
 *          ncp_uint32_t tqsId,
 *          ncp_task_resource_name_t *name);
 *
 * @brief   This function allows the caller to determine a TQS's name.
 *
 * @param[in] ncpHdl: NCP handle returned by previous call to ncp_config.
 * @param[in] tqsId: the thread queue set's ID.
 * @param[out] name: a pointer to the TQS's name.
 *
 * @retval NCP_ST_SUCCESS the TQS's name was found and returned.
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 * @retval NCP_ST_INVALID_PARAMETER tqsId is greater than 85, or name is NULL.
 * @retval NCP_ST_TASK_QUESET_NOT_IN_LOCAL_DOMAIN The TQS specified by tqsId
 *              is not located in the caller's OS domain
 * @retval NCP_ST_TASK_TQS_NOT_CONFIGURED The TQS specified by tqsId is not
 *              configured.
 */
NCP_API ncp_st_t
ncp_task_tqs_name_get(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t tqsId,
    ncp_task_resource_name_t *name);

/*!
 * @fn ncp_st_t ncp_task_tqs_id_get(
 *          ncp_hdl_t ncpHdl,
 *          ncp_task_resource_name_t *name,
 *          ncp_uint32_t *tqsId);
 *
 * @brief   This function allows the caller to find a TQS's ID by its name.
 *
 * @param[in] ncpHdl: NCP handle returned by previous call to ncp_config.
 * @param[in] name: a pointer to the TQS's name.
 * @param[out] tqsId: a pointer to the thread queue set's ID.
 *
 * @retval NCP_ST_SUCCESS the TQS's ID was found and returned.
 * @retval NCP_ST_TASK_BAD_RESOURCE_NAME the resource name is invalid.
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 * @retval NCP_ST_INVALID_PARAMETER tqsId or name is NULL.
 * @retval NCP_ST_TASK_TQSNAME_NOT_FOUND The specified TQS resource name does
 *              not exist.
 */   
NCP_API ncp_st_t
ncp_task_tqs_id_get(
    ncp_hdl_t ncpHdl,
    ncp_task_resource_name_t *name,
    ncp_uint32_t *tqsId);

/*!
 * @fn ncp_st_t ncp_task_nca_queue_name_get(
 *          ncp_hdl_t ncpHdl,
 *          ncp_uint32_t ncaQueueId,
 *          ncp_task_resource_name_t *name);
 *
 * @brief   This function allows the caller to determine an NCA queue's name.
 *
 * @param[in] ncpHdl: NCP handle returned by previous call to ncp_config.
 * @param[in] ncaQueueId: the NCA queue's ID.
 * @param[out] name: a pointer to the NCA queue's name.
 *
 * @retval NCP_ST_SUCCESS the NCA queue's name was found and returned.
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 * @retval NCP_ST_INVALID_PARAMETER tqsId is greater than 203, or name is NULL.
 */
NCP_API ncp_st_t
ncp_task_nca_queue_name_get(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t ncaQueueId,
    ncp_task_resource_name_t *name);

/*!
 * @fn ncp_st_t ncp_task_nca_queue_id_get(
 *          ncp_hdl_t ncpHdl,
 *          ncp_task_resource_name_t *name,
 *          ncp_uint32_t *ncaQueueId);
 *
 * @brief   This function allows the caller to find an NCA queue's ID by name.
 *
 * @param[in] ncpHdl: NCP handle returned by previous call to ncp_config.
 * @param[in] name: a pointer to the NCA queue's name.
 * @param[out] ncaQueueId: a pointer to the NCA queue's ID.
 *
 * @retval NCP_ST_SUCCESS the NCA queue's ID was found and returned.
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 * @retval NCP_ST_INVALID_PARAMETER tqsId or name is NULL.
 * @retval NCP_ST_TASK_BAD_RESOURCE_NAME the resource name is invalid.
 */
ncp_st_t
ncp_task_nca_queue_id_get(
    ncp_hdl_t ncpHdl,
    ncp_task_resource_name_t *name,
    ncp_uint32_t *ncaQueueId);

/*!
 * @fn ncp_st_t ncp_task_nca_queue_profile_name_get(
 *          ncp_hdl_t ncpHdl,
 *          ncp_uint32_t profileId,
 *          ncp_task_resource_name_t *name)
 *
 * @brief   This function allows the caller to find an NCA queue profile's
 *          name.
 *
 * @param[in] ncpHdl: NCP handle returned by previous call to ncp_config.
 * @param[in] profileId: a pointer to the NCA queue's ID.
 * @param[out] name: a pointer to the NCA queue's name.
 *
 * @retval NCP_ST_SUCCESS the NCA queue profile's name was found and returned.
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 * @retval NCP_ST_INVALID_PARAMETER profileId is greater than the number of NCA
 *              queue profiles or name is NULL.
 */
NCP_API ncp_st_t
ncp_task_nca_queue_profile_name_get(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t profileId,
    ncp_task_resource_name_t *name);

/*!
 * @fn ncp_st_t ncp_task_nca_queue_profile_id_get(
 *          ncp_hdl_t ncpHdl,
 *          ncp_uint32_t ncaQueueId,
 *          ncp_uint32_t *pProfileID);
 *
 * @brief   This function allows the caller to find an NCA queue's profile ID.
 *
 * @param[in] ncpHdl: NCP handle returned by previous call to ncp_config.
 * @param[in] ncaQueueId: the NCA queue ID.
 * @param[out] pProfileId: a pointer to the NCA queue's profile ID.
 *
 * @retval NCP_ST_SUCCESS the NCA queue's profile ID was found and returned.
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 * @retval NCP_ST_INVALID_PARAMETER ncaQueueId is greater than 203, or refers
 *              to an unconfigured NCA queue, or name is NULL.
 * @retval NCP_ST_TASK_BAD_RESOURCE_NAME the resource name is invalid.
 */
NCP_API ncp_st_t
ncp_task_nca_queue_profile_id_get(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t ncaQueueId,
    ncp_uint32_t *profileId);

/*!
 * @fn ncp_st_t ncp_task_tqs_cpu_affinity_get(
 *          ncp_hdl_t ncpHdl,
 *          ncp_uint32_t tqsId,
 *          ncp_uint32_t *cpuId);
 *
 * @brief   This function returns the TQS's CPU affinity as specified in the
 *          configuration.
 *
 * @param[in] ncpHdl: NCP handle returned by previous call to ncp_config.
 * @param[in] tqsId: the thread queue set ID.
 * @param[out] cpuId: a pointer to the TQS's affinitized CPU's ID.
 *
 * @retval NCP_ST_SUCCESS the TQS's CPU affinity found and returned.
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 * @retval NCP_ST_INVALID_PARAMETER tqsId is greater than 63, or cpuId is NULL.
 * @retval NCP_ST_TASK_QUESET_NOT_IN_LOCAL_DOMAIN The TQS specified by tqsId
 *              is not located in the caller's OS domain
 * @retval NCP_ST_TASK_TQS_NOT_CONFIGURED The TQS specified by tqsId is not
 *              configured.
 */
NCP_API ncp_st_t
ncp_task_tqs_cpu_affinity_get(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t tqsId,
    ncp_uint32_t *cpuId);

/*!
 * @fn ncp_st_t ncp_task_stats_get(
 *             ncp_hdl_t ncpHdl,
 *             ncp_uint32_t tqsId,
 *             ncp_uint32_t bufferSize,
 *             ncp_task_stats_t *stats);
 *
 * @brief   This API returns TQS-local Task I/O statistics.   The statistics collected include API success and failure counts,   as well as traffic 
 *          related statistics.    Certain API error cases cannot be tied to a particular TQS,   and thus those will be captured in the global statistics.
 *          It is important to note that statistics are never double counted,   a particular failure instance is reported in either the TQS local statics,
 *          or the global statistics,   never both.
 *
 * @param[in]       ncpHdl:  NCP handle returned by previous call to ncp_config
 * @param[in]       tqsId:   The ID of the Thread Queue Set
 * @param[in]       bufferSize: The size of the caller's buffer.   This should be set to sizeof(ncp_task_stats_t).   If bufferSize is less than
 *                  the TQS statistics array being used by the RTE,   the data returned will be truncated so as to not overrun the caller's buffer.
 * @param[in,out]   stats: Pointer to a buffer of size bufferSize where the RTE will copy the TQS-local statistics to.
 *
 * @retval NCP_ST_SUCCESS success
 * @retval  NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval  NCP_ST_INVALID_HANDLE The ncp handle failed validation.   
 * @retval  NCP_ST_TASK_TQS_NOT_CONFIGURED The TQS must be configured in the ASE or dynamically before it can be used in this API. 
 * @retval NCP_ST_INVALID_PARAMETER One or more input parameters are invalid. 
 * @retval NCP_ST_NOT_IMPLEMENTED either the platform (fbrs, socket) does not
 *          yet support task statistics, or the TQS is configured for kernel
 *          mode. Retrieving kernel mode statistics is not yet supported. 
*/	

NCP_API ncp_st_t
ncp_task_stats_get(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t tqsId,
    ncp_uint32_t bufferSize,
    ncp_task_stats_t *stats);

/*!
 * @fn ncp_st_t ncp_task_stats_reset(
 *             ncp_hdl_t ncpHdl,
 *             ncp_uint32_t tqsId);
 *
 * @brief   This API resets the TQS-local Task I/O statistics for the specified TQS.   
 *          All values are reset to zero.   This API has no effect on the RTE maintained global statistics.
 *
 * @param[in]       ncpHdl:  NCP handle returned by previous call to ncp_config
 * @param[in]       tqsId:   The ID of the Thread Queue Set
 *
 * @retval NCP_ST_SUCCESS success
 * @retval  NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval  NCP_ST_INVALID_HANDLE The ncp handle failed validation.  
 * @retval  NCP_ST_TASK_TQS_NOT_CONFIGURED The TQS must be configured in the ASE or dynamically before it can be used in this API. 
 * @retval NCP_ST_INVALID_PARAMETER One or more input parameters are invalid. 
 * @retval NCP_ST_NOT_IMPLEMENTED either the platform (fbrs, socket) does not yet support task statistics, or the TQS
 *                                is configured for kernel mode.   Resetting kernel mode statistics is not yet supported.  
 */	
NCP_API ncp_st_t
ncp_task_stats_reset(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t tqsId);
    
/*!
 * @fn ncp_st_t ncp_task_global_stats_get(
 *             ncp_hdl_t ncpHdl,
 *             ncp_task_execution_modes_t mode,
 *             ncp_uint32_t bufferSize,
 *             ncp_task_global_stats_t *stats);
 *
 * @brief   This API returns TQS-local Task I/O statistics. The statistics
 *          collected include API success and failure counts,   as well as
 *          traffic related statistics.    Certain API error cases cannot be
 *          tied to a particular TQS,   and thus those will be captured in the
 *          global statistics.
 *          It is important to note that statistics are never double counted,
 *          a particular failure instance is reported in either the TQS local
 *          statics, or the global statistics,   never both.
 *
 * @param[in]       ncpHdl:  NCP handle returned by previous call to ncp_config
 * @param[in]       mode: Return User or Kernel Mode stats? See ncp_task_execution_modes_t.
 * @param[in]       bufferSize: The size of the caller's buffer.   This should be set to sizeof(ncp_task_global_stats_t).   If bufferSize is less than
 *                  the TQS statistics array being used by the RTE,   the data returned will be truncated so as to not overrun the caller's buffer.
 * @param[in,out]   stats: Pointer to a buffer of size bufferSize where the RTE will copy the global Task I/O statistics to.
 *
 * @retval NCP_ST_SUCCESS success
 * @retval  NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval  NCP_ST_INVALID_HANDLE The ncp handle failed validation.  
 * @retval NCP_ST_INVALID_PARAMETER One or more input parameters are invalid. 
 * @retval NCP_ST_NOT_IMPLEMENTED either the platform (fbrs, socket) does not yet support task statistics, or the TQS
 *                                is configured for kernel mode.   Retrieving or resetting kernel mode statistics is not yet supported.  
*/	    
NCP_API ncp_st_t
ncp_task_global_stats_get(
    ncp_hdl_t ncpHdl,
    ncp_task_execution_modes_t mode,
    ncp_uint32_t bufferSize,
    ncp_task_global_stats_t *stats);

/*!
 * @fn ncp_st_t ncp_task_global_stats_reset(
 *             ncp_hdl_t ncpHdl);
 *   
 *
 * @brief   This API resets the global Task I/O statistics.   
 *          All values are reset to zero.   This API has no effect on the RTE maintained TQS-local statistics.
 *
 * @param[in]       ncpHdl:  NCP handle returned by previous call to ncp_config
 * @param[in]       mode: Reset User or Kernel Mode stats? See ncp_task_execution_modes_t. 
 *
 * @retval NCP_ST_SUCCESS success
 * @retval NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval NCP_ST_INVALID_HANDLE The ncp handle failed validation.  
 * @retval NCP_ST_INVALID_PARAMETER One or more input parameters are invalid. 
 * @retval NCP_ST_NOT_IMPLEMENTED either the platform (fbrs, socket) does not
 *          yet support task statistics, or the TQS is configured for kernel
 *          mode. Retrieving or resetting kernel mode statistics is not yet
 *          supported.  
 */
NCP_API ncp_st_t
ncp_task_global_stats_reset(
    ncp_hdl_t ncpHdl,
    ncp_task_execution_modes_t mode);

/*!
 * @fn ncp_st_t ncp_task_qpm_queue_stats_get(
 *             ncp_hdl_t ncpHdl,
 *             ncp_uint16_t queueId,
 *             ncp_task_qpm_stats_t *stats);
 *
 * @brief   This API returns a QPM queue's (almost) full, (almost) empty, and
 *          overflow statistics. These statistics are only maintained for
 *          queues with interrupt service type.
 *
 * @param[in]     ncpHdl:  NCP handle returned by previous call to ncp_config
 * @param[in]     queueId: QPM event queue ID.
 * @param[in,out] stats: Pointer to a buffer of size bufferSize where the RTE will copy the global Task I/O statistics to.
 *
 * @retval NCP_ST_SUCCESS success
 * @retval NCP_ST_TASK_NO_GSM The software state is not valid. This may be due
 *              to corruption or a configuration problem.
 * @retval NCP_ST_INVALID_HANDLE The ncp handle failed validation.
 * @retval NCP_ST_INVALID_PARAMETER One or more input parameters are invalid.
 * @retval NCP_ST_NOT_IMPLEMENTED the platform (fbrs, socket) does not yet
 *              support QPM statistics.
 */
ncp_st_t
ncp_task_qpm_queue_stats_get(
    ncp_hdl_t ncpHdl,
    ncp_uint16_t queueId,
    ncp_task_qpm_stats_t *stats);

/*!
 * @fn ncp_st_t ncp_task_pool_name_get(
 *              ncp_hdl_t ncpHdl,
 *              ncp_uint8_t bufferPoolId,
 *              ncp_task_resource_name_t *name);
 *
 * @brief   This function gets the name of a pool by its ID.  If the pool is the fixed pool (31), 
 *          then the value 1 should be provided for bufferPoolId.  This is the encoded value used when sending
 *          or receiving tasks.
 *
 * @param[in] ncpHdl: NCP handle returned by previous call to ncp_config
 * @param[in] bufferPoolId: The pool ID.
 * @param[out] name: The pool name.
 *
 * @retval NCP_ST_SUCCESS success
 * @retval  NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval  NCP_ST_INVALID_HANDLE The ncp handle failed validation.  
 * @retval NCP_ST_INVALID_PARAMETER One or more input parameters are invalid.
 *              Verify that the task memory pool is configured.
 */
NCP_API ncp_st_t
ncp_task_pool_name_get(
    ncp_hdl_t ncpHdl,
    ncp_uint8_t bufferPoolId,
    ncp_task_resource_name_t *name);

/*!
 * @fn ncp_st_t ncp_task_pool_id_get(
 *              ncp_hdl_t ncpHdl,
 *              ncp_task_resource_name_t *name,
 *              ncp_uint8_t bufferPoolId);
 *
 * @brief   This function gets the ID of a pool by its name.
 *
 * @param[in] ncpHdl: NCP handle returned by previous call to ncp_config
 * @param[in] name: The pool name.
 * @param[out] bufferPoolId: The pool ID.
 *
 * @retval NCP_ST_SUCCESS success
 * @retval NCP_ST_TASK_NO_GSM The software state is not valid. This may be due
 *              to corruption or a configuration problem.
 * @retval NCP_ST_INVALID_HANDLE The ncp handle failed validation.  
 * @retval NCP_ST_TASK_BAD_RESOURCE_NAME The pool name is invalid.
 * @retval NCP_ST_TASK_POOL_NOT_FOUND The pool name does not exist in the configuration.
 * @retval NCP_ST_INVALID_PARAMETER One or more input parameters are invalid.
 *              Verify that the task memory pool is configured.
 */
NCP_API ncp_st_t
ncp_task_pool_id_get(
    ncp_hdl_t ncpHdl,
    ncp_task_resource_name_t *name,
    ncp_uint8_t *bufferPoolId);

/*
 * TBR - Task Buffer Recovery APIs
 */

/*!
 *  @brief ncp_task_tbr_state_e: Represents buffer state or ownership with respect to TBR (Task Buffer Recovery)
 * The buffer state falls into just 4 categories.  Three are internal states,   and the 4th is process owned.
 * The buffer is owned by a process if PID >= 3.
 *
 * NCP_TASK_TBR_STATE_FREE: The buffer is on the free list. Applies to both
 *      Shared and CPU pool task buffers.
 * NCP_TASK_TBR_STATE_NCA_OWNED: The buffer is outstanding to the NCAV3
 *      hardware as a receive buffer.   Buffers enter this state at config time
 *      when the RTE performs its initial population of NCA receive buffers.
 *      Buffers also enter this state as a result of applications calling the
 *      refill API.   Buffers transition from the NCP_TASK_TBR_STATE_NCA_OWNED
 *      state to being owned by a process when they are received as part of a
 *      task returned to the application as a result of calling the
 *      ncp_task_recv API.
 * NCP_TASK_TBR_STATE_RTE_OWNED: Buffers whose ownership has been relinquished
 *      as a result of the application calling the ncp_task_tbr_task_give API.
 *      Buffers remain in this state until a process takes ownership of the
 *      buffer by calling the ncp_task_tbr_task_take API.   
 * NCP_TASK_TBR_STATE_MULTI_REFS: At one point, the system contained multiple
 *      references to this buffer. While in this state, the buffer is
 *      unrecoverable. The buffer leaves this state when it is allocated
 *      from an mPCQ or when it is received in a task with an mref value of 0.
 * NCP_TASK_TBR_FIRST_APPLICATION_PID: This is the first and numerically
 *      lowest value that corresponds to a buffer being owned by a process.
 *                               
 */
typedef enum {
    NCP_TASK_TBR_STATE_FREE=0,            /* 0 */
    NCP_TASK_TBR_STATE_NCA_OWNED,         /* 1 */
    NCP_TASK_TBR_STATE_RTE_OWNED,         /* 2 */
    NCP_TASK_TBR_STATE_MULTI_REFS,        /* 3 */
    /* Space reserved for future expansion. */
    NCP_TASK_TBR_FIRST_APPLICATION_PID=9  /* 9 */ /* Must be last! */
} ncp_task_tbr_state_e;    

/*!
 * @fn ncp_st_t ncp_task_tbr_task_take(
 *                  ncp_task_tqs_hdl_t tqsHdl,
 *                  ncp_task_header_t  *taskHeader);
 *
 * @brief   Add the task described by task header to this process's task buffer recovery (TBR) domain,   
 *          thereby effectively taking ownership of the task.   The task described by task header must have been 
 *          previously transferred by another process/thread.   It is imperative that application software that uses this
 *          API be written in a manner that ensures that the threads that call the ncp_task_tbr_task_take and ncp_task_tbr_task_give
 *          APIs not crash prior to completion of the task handoff.   A crash of either process/thread,   or even a premature normal exit 
 *          by the recipient process/thread,  may result in an orphaned task and the buffers that comprise that task.
 *
 * @param[in] tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in] taskHeader:   For purposes of TBR,   the caller is now assuming ownership of the task,  and all associated task buffers. 
 *
 * @note:   It is recommended that applications use the atomic transfer TBR APIs whenever possible.   There is a large window where tasks/buffers
 *          can become orphaned due to application crashes or restarts in between the give and take APIs calls.
 *
 *
 * @retval NCP_ST_SUCCESS - The task state and the state of all of its associated task buffers was appropriate for transfer,   
 *                          and the calling process now owns the task for purposes of TBR.
 * @retval  NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval  NCP_ST_INVALID_PARAMETER One or more of the parameters supplied is not valid. 
 * @retval NCP_ST_TASK_TBR_INVALID_BUFFER TBR detected that the buffer does not belong to the pool
 * @retval NCP_ST_TASK_TBR_FATAL_POOL_CORRUPTION TBR detected that the buffer is not in the expected state,  and pool corruption is likely
 *
 */
NCP_API ncp_st_t
ncp_task_tbr_task_take(
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_task_header_t  *taskHeader);

/*!
 * @fn ncp_st_t ncp_task_tbr_buffer_take(
 *                  ncp_task_tqs_hdl_t tqsHdl,
 *                  ncp_uint8_t    bufferPoolId, 
 *                  void *taskBuffer);
 *
 * @brief   Add the buffer to this process's task buffer recovery (TBR) domain,   
 *          thereby effectively taking ownership of the buffer.   The buffer must have been 
 *          previously transferred by another process/thread.   It is imperative that application software that uses this
 *          API be written in a manner that ensures that the threads that call the ncp_task_tbr_buffer_take and ncp_task_tbr_buffer_give
 *          APIs not crash prior to completion of the task handoff.   A crash of either process/thread,   or even a premature normal exit 
 *          by the recipient process/thread,  may result in an orphaned task buffer.  It is not valid
 *          to attempt to take, give, or transfer ownership of a buffer belonging to the fixed pool (31) which
 *          is encoded as bufferPoolId 1.
 *
 * @param[in] tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in] bufferPoolId:    The buffer pool Id that taskBuffer belongs to.
 * @param[in] taskBuffer:   For purposes of TBR,   the caller is now assuming ownership of the task buffer.
 *
 * @note:   It is recommended that applications use the atomic transfer TBR APIs whenever possible.   There is a large window where tasks/buffers
 *          can become orphaned due to application crashes or restarts in between the give and take APIs calls. 
 *
 * @retval NCP_ST_SUCCESS - The buffer state was appropriate for transfer,   
 *                          and the calling process now owns the task for purposes of TBR.
 * @retval  NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval  NCP_ST_INVALID_PARAMETER One or more of the parameters supplied is not valid. 
 * @retval NCP_ST_TASK_TBR_INVALID_BUFFER TBR detected that the buffer does not belong to the pool
 * @retval NCP_ST_TASK_TBR_FATAL_POOL_CORRUPTION TBR detected that the buffer is not in the expected state,  and pool corruption is likely
 *
 * 
 */
NCP_API ncp_st_t
ncp_task_tbr_buffer_take(
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint8_t    bufferPoolId,    
    void *taskBuffer);

/*!
 * @fn ncp_st_t ncp_task_tbr_task_give(
 *                  ncp_task_tqs_hdl_t tqsHdl,
 *                  ncp_task_header_t  *taskHeader);
 *
 * @brief   Remove the caller's TBR ownership of the task described by task header in preparation for another thread/process 
 *          taking ownership of the task via a subsequent call to the ncp_task_tbr_task_take API.
 *          It is imperative that application software that uses this
 *          API be written in a manner that ensures that the threads that call the ncp_task_tbr_task_take and ncp_task_tbr_task_give
 *          APIs not crash prior to completion of the task handoff.   A crash of either process/thread,   or even a premature normal exit 
 *          by the recipient process/thread,  may result in an orphaned task and the buffers that comprise that task.
 *
 * @param[in] tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in] taskHeader:   For purposes of TBR,   the caller is now relinquishing ownership of this task and it associated task
 *                          buffers.   It is important that another thread/process assume ownership of this buffer by calling the 
 *                          ncp_task_tbr_buffer_take API.
 *
 * @note:  This API must be called before posting the buffer to an application defined free pool,   
 *         or before using an IPC mechanism to inform a recipient that the task is now available.
 *
 * @note:   It is recommended that applications use the atomic transfer TBR APIs whenever possible.   There is a large window where tasks/buffers
 *          can become orphaned due to application crashes or restarts in between the give and take APIs calls.
 *
 * @note    If the state of any buffer in the task current TBR state is
 *          NCP_TASK_TBR_STATE_MULTI_REFS, this function will leave the state
 *          unchanged.
 *
 * @retval NCP_ST_SUCCESS - The task state and the state of all of its associated task buffers was appropriate for transfer,   
 *                          and the calling process now owns the task for purposes of TBR.
 *                          and the calling process now owns the task for purposes of TBR.
 * @retval  NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval  NCP_ST_INVALID_PARAMETER One or more of the parameters supplied is not valid. 
 * @retval NCP_ST_TASK_TBR_INVALID_BUFFER TBR detected that the buffer does not belong to the pool
 * @retval NCP_ST_TASK_TBR_FATAL_POOL_CORRUPTION TBR detected that the buffer is not in the expected state,  and pool corruption is likely
 *
 * 
 */    
ncp_st_t
ncp_task_tbr_task_give(
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_task_header_t  *taskHeader);

/*!
 * @fn ncp_st_t ncp_task_tbr_buffer_give(
 *                  ncp_task_tqs_hdl_t tqsHdl,
 *                  ncp_uint8_t    bufferPoolId,
 *                  void *taskBuffer);
 *
 * @brief   Remove the caller's TBR ownership of the task buffer in preparation for another thread/process 
 *          taking ownership of the buffer via a subsequent call to the ncp_task_tbr_buffer_take API.
 *          It is imperative that application software that uses this API be written in a manner that ensures that the threads that 
 *          call the ncp_task_tbr_buffer_take and ncp_task_tbr_buffer_give APIs not crash prior to completion of the task handoff.   
 *          A crash of either process/thread,   or even a premature normal exit 
 *          by the recipient process/thread,  may result in an orphaned task buffer.   It is not valid
 *          to attempt to take, give, or transfer ownership of a buffer belonging to the fixed pool (31) which
 *          is encoded as bufferPoolId 1.
 *
 * @note    If the buffer's current TBR state is NCP_TASK_TBR_STATE_MULTI_REFS,
 *          this function will leave the state unchanged.
 *
 * @param[in] tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in] bufferPoolId:   The buffer pool Id that taskBuffer belongs to.
 * @param[in] taskBuffer:   For purposes of TBR,   the caller is now relinquishing ownership of this task buffer.   It is important that
 *                          another thread/process assume ownership of this buffer by calling the ncp_task_tbr_buffer_take API.
 *
 * @note:  This API must be called before posting the buffer to an application defined free pool,   or using an IPC
 *         mechanism to inform a recipient that the buffer is now available.
 *
 * @note:   It is recommended that applications use the atomic transfer TBR APIs whenever possible.   There is a large window where tasks/buffers
 *          can become orphaned due to application crashes or restarts in between the give and take APIs calls.
 * 
 * @retval NCP_ST_SUCCESS - The task buffer state was appropriate for transfer,   
 *                          and the calling process now owns the task buffer for purposes of TBR.
 *                          and the calling process now owns the task for purposes of TBR.
 * @retval  NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval  NCP_ST_INVALID_PARAMETER One or more of the parameters supplied is not valid. 
 * @retval NCP_ST_TASK_TBR_INVALID_BUFFER TBR detected that the buffer does not belong to the pool
 * @retval NCP_ST_TASK_TBR_FATAL_POOL_CORRUPTION TBR detected that the buffer is not in the expected state,  and pool corruption is likely
 *
 * 
 */ 
ncp_st_t
ncp_task_tbr_buffer_give(
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint8_t    bufferPoolId,
    void *taskBuffer);    
    
 
/*!
 * @fn ncp_st_t ncp_task_tbr_buffer_ownership_get( ncp_task_tqs_hdl_t tqsHdl,
 *                           ncp_uint8_t poolId,
 *                           void *taskBuffer,  
 *                           ncp_task_pid_t *pid); 
 *                           
 * @brief   Return the Task I/O assigned PID of the buffer's owner.   See the enum type ncp_task_tbr_state_e,   
 *          as some PID values represent internal buffer states.
 *
 * @param[in] tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in] poolId:  The buffer pool Id that taskBuffer belongs to.
 * @param[in] taskBuffer:   Pointer to the task buffer   
 * @param[in] *pid:         The Task I/O assigned pid of the process that owns this buffer.
 *
 * @retval NCP_ST_SUCCESS - The task buffer was valid,   and the pid of the buffer owner has been returned
 *                          and the calling process now owns the task for purposes of TBR.
 * @retval  NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval  NCP_ST_INVALID_PARAMETER One or more of the parameters supplied is not valid. 
 * @retval NCP_ST_TASK_TBR_INVALID_BUFFER TBR detected that the buffer does not belong to the pool
 * @retval NCP_ST_TASK_TBR_FATAL_POOL_CORRUPTION TBR detected that the buffer is not in the expected state,  and pool corruption is likely
 *
 * 
 */     
    
ncp_st_t  
ncp_task_tbr_buffer_ownership_get( ncp_task_tqs_hdl_t tqsHdl,
                            ncp_uint8_t poolId,
                            void *taskBuffer,  
                            ncp_task_pid_t *pid); 
                             
/*!
 * @fn ncp_st_t ncp_task_tbr_task_transfer( ncp_task_tqs_hdl_t tqsHdl,
 *                           ncp_task_header_t *task,  
 *                           ncp_task_pid_t pid); 
 *                           
 * @brief   Remove the caller's TBR ownership of the task and all of its buffers,   and atomically transfer ownership to 
 *          the process that has been assigned Task I/O process id "pid.    
 *          This API operates atomically,  and the recipient process should not call ncp_task_tbr_task_take.
 *
 * @note    If the state of any buffer in the task current TBR state is
 *          NCP_TASK_TBR_STATE_MULTI_REFS, this function will leave the state
 *          unchanged.
 *
 * @param[in] tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in] task:         For purposes of TBR,   the caller is relinquishing ownership of this task,  and all of its buffers.   
  * @param[in] pid:          The Task I/O assigned pid of the process to which ownership of the task and all of its associated buffers
 *                          will be transferred to.   Note that this pid is not related to the PID assigned by the host operating system.
 *
 * @retval NCP_ST_SUCCESS - The task buffer state was appropriate for transfer,   
 *                          and the process assigned PID=pid now owns the task and all of its buffer, for purposes of TBR.
 *                          and the calling process now owns the task for purposes of TBR.
 * @retval  NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval  NCP_ST_INVALID_PARAMETER One or more of the parameters supplied is not valid. 
 * @retval NCP_ST_TASK_TBR_INVALID_BUFFER TBR detected that the buffer does not belong to the pool
 * @retval NCP_ST_TASK_TBR_FATAL_POOL_CORRUPTION TBR detected that the buffer is not in the expected state,  and pool corruption is likely
 *
 * 
 */     
    
NCP_API ncp_st_t
ncp_task_tbr_task_transfer( ncp_task_tqs_hdl_t tqsHdl,
                            ncp_task_header_t *task,  
                            ncp_task_pid_t pid); 
                            
/*!
 * @fn ncp_st_t ncp_task_tbr_buffer_transfer( ncp_task_tqs_hdl_t tqsHdl,
 *                             void *taskBuffer,  
 *                             ncp_uint8_t    bufferPoolId,
 *                             ncp_task_pid_t pid);
 *
 * @brief   Remove the caller's TBR ownership of the task buffer,   and transfer ownership to the process that has been 
 *          assigned Task I/O process id "pid.    This API operates atomically,  and the recipient process should not 
 *           call ncp_task_tbr_buffer_take.   It is not valid
 *          to attempt to take, give, or transfer ownership of a buffer belonging to the fixed pool (31) which
 *          is encoded as bufferPoolId 1.
 *
 * @note    If the buffer's current TBR state is NCP_TASK_TBR_STATE_MULTI_REFS,
 *          this function will leave the state unchanged.
 *
 * @param[in] tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in] bufferPoolId:   The buffer pool Id that taskBuffer belongs to.
 * @param[in] taskBuffer:   For purposes of TBR,   the caller is now relinquishing ownership of this task buffer.   It is important that
 *                          another thread/process assume ownership of this buffer by calling the ncp_task_tbr_buffer_take API.
 * @param[in] pid:          The Task I/O assigned pid of the process to which ownership of the task and all of its associated buffers
 *                          will be transferred to.   Note that this pid is not related to the PID assigned by the host operating system.
 *
 * @retval NCP_ST_SUCCESS - The task buffer state was appropriate for transfer,   
 *                          and the process assigned PID=pid now owns the task buffer for purposes of TBR.
 *                          and the calling process now owns the task for purposes of TBR.
 * @retval  NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval  NCP_ST_INVALID_PARAMETER One or more of the parameters supplied is not valid. 
 * @retval NCP_ST_TASK_TBR_INVALID_BUFFER TBR detected that the buffer does not belong to the pool
 * @retval NCP_ST_TASK_TBR_FATAL_POOL_CORRUPTION TBR detected that the buffer is not in the expected state,  and pool corruption is likely
 *
 * 
 */ 
NCP_API ncp_st_t
ncp_task_tbr_buffer_transfer( ncp_task_tqs_hdl_t tqsHdl,
                              void *taskBuffer,  
                              ncp_uint8_t    bufferPoolId,
                              ncp_task_pid_t pid); 

/*!
 * @fn ncp_st_t ncp_task_pid_get(ncp_task_tqs_hdl_t tqsHdl,
 *                               ncp_task_pid_t *pid); 
 *
 * @brief   This API returns the Task I/O assigned PID that has been assigned to the caller.  Client applications may call this API to 
 *          get their pid so that it can be provided to another process for use ncp_task_tbr_buffer_transfer or ncp_task_tbr_task_transfer
 *          APIs.
 *
 * @param[in]       tqsHdl: TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in,out]   pid: pointer to a location of type ncp_task_pid_t where the caller's pid will be copied.
 *
 *
 * @retval NCP_ST_SUCCESS success
 *                          and the calling process now owns the task for purposes of TBR.
 * @retval  NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval  NCP_ST_INVALID_PARAMETER One or more of the parameters supplied is not valid. 
 * @retval  NCP_ST_TASK_PID_LOOKUP_FAILURE The caller does not currently have a valid Task IO PID.
 *                                         Task IO PIDs are assigned when the ncp_task_tqs_bind API is called successfully.
 
 * 
*/	                              
NCP_API ncp_st_t
ncp_task_pid_get(ncp_task_tqs_hdl_t tqsHdl,
                 ncp_task_pid_t *pid); 

/*!
 * @fn ncp_st_t ncp_task_process_name_pid_get(ncp_hdl_t ncpHdl, 
 *                                            ncp_task_resource_name_t *processName, 
 *                                            ncp_task_pid_t *pid); 
 *
 * @brief   This API returns the Task I/O assigned PID belong to the process whose name matches the supplied processName parameter.  
 *          The returned pid can be used with ncp_task_tbr_buffer_transfer or ncp_task_tbr_task_transfer APIs.
 *
 * @param[in]       ncpHdl:  NCP handle returned by previous call to ncp_config
 * @param[in]       processName: pointer to the processName whose pid should be returned.   The process must be running and have completed
 *                  its Task I/O initialization (ncp_task_tqs_bind).
 * 
 * @param[in,out]   pid: pointer to a location of type ncp_task_pid_t where the caller's pid will be copied.
 *
 * @note:  This API should not be called in the data path,   as it may execute for a significant amount of time as it looks up the
 *         target process.   Rather,   it is hoped that the caller of this API would only call this API once,   cache the pid that is 
 *         returned,   and then use that cached pid value in any performance sensitive functions and/or code paths.
 *
 * @retval NCP_ST_SUCCESS success
 * @retval  NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
 * @retval  NCP_ST_INVALID_PARAMETER One or more of the parameters supplied is not valid.  
 * @retval  NCP_ST_TASK_PID_LOOKUP_FAILURE The caller does not currently have a valid Task IO PID.
 *                                         Task IO PIDs are assigned when the ncp_task_tqs_bind API is called successfully.
 * 
*/	                            
NCP_API ncp_st_t
ncp_task_process_name_pid_get(ncp_hdl_t ncpHdl, 
                              ncp_task_resource_name_t *processName, 
                              ncp_task_pid_t *pid); 
 
typedef enum {
    NCP_TASK_MANUAL_COMPLETION_MODE = 0,
    NCP_TASK_AUTO_COMPLETION_MODE,
} ncp_ncav3_task_completion_mode_e;
                              
/*!
* @fn ncp_st_t ncp_task_completion_mode_get(ncp_task_tqs_hdl_t tqsHdl, 
 *                                           ncp_ncav3_task_completion_mode_e *completionMode); 
 *
* @brief   This API returns the completion mode configured for the receive queue associated with the thread queue set.
*
* @param[in]       tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
* @param[in/out]   pointer to location where the receive queue completion mode will be returned.
*
* @retval NCP_ST_SUCCESS success
* @retval  NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
* @retval  NCP_ST_INVALID_PARAMETER One or more of the parameters supplied is not valid.  
*/           
                            
NCP_API ncp_st_t
ncp_task_completion_mode_get(ncp_task_tqs_hdl_t tqsHdl,  
                             ncp_ncav3_task_completion_mode_e *completionMode);
   
typedef enum {
    NCP_TASK_IMMEDIATE_CONSUMPTION_MODE = 0,
    NCP_TASK_DEFERRED_CONSUMPTION_MODE
} ncp_ncav3_task_consumption_mode_e;
                             
/*!
* @fn ncp_st_t ncp_task_consumption_mode_get(ncp_task_tqs_hdl_t tqsHdl, 
 *                                           ncp_ncav3_task_consumption_mode_e *consumptionMode); 
 *
* @brief   This API returns the consumption mode configured for the receive queue associated with the thread queue set.
*
* @param[in]       tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
* @param[in/out]   pointer to location where the receive queue consumption will be returned.
*
* @retval NCP_ST_SUCCESS success
* @retval  NCP_ST_TASK_NO_GSM The software state is not valid.   This may be due to corruption or a configuration problem.
* @retval  NCP_ST_INVALID_PARAMETER One or more of the parameters supplied is not valid.  
*/                                       
NCP_API ncp_st_t
ncp_task_consumption_mode_get(ncp_task_tqs_hdl_t tqsHdl, 
                              ncp_ncav3_task_consumption_mode_e *consumptionMode);

/*!
 * @fn ncp_st_t ncp_task_shared_region_virtual_base_get_by_id(
 *                  ncp_task_tqs_hdl_t tqsHdl,
 *                  ncp_uint32_t regionId,
 *                  void **addr)
 *
 * @brief   This API returns the virtual base address of the shared region
 *          indicated by regionId.
 *
 * @param[in]       tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in]       regionId: the shared region ID.
 * @param[out]      addr: pointer where the shared region's virtual base address will be copied.
 *
 * @retval NCP_ST_SUCCESS success
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured,  or the application has not attached to the configuration.
 * @retval NCP_ST_INVALID_PARAMETER NULL addr pointer
 * @retval NCP_ST_TASK_SHARED_REGION_NOT_FOUND The shared region indicated by
 *          regionId is not included in this thread queue set.
*/

NCP_API ncp_st_t
ncp_task_shared_region_virtual_base_get_by_id(
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint32_t regionId,
    void **addr);

/*!
 * @fn ncp_st_t ncp_task_shared_region_virtual_base_get_by_name(
 *                  ncp_task_tqs_hdl_t tqsHdl,
 *                  ncp_task_resource_name_t *name,
 *                  void **addr)
 *
 * @brief   This API returns the virtual base address of the shared region
 *          indicated by name.
 *
 * @param[in]       tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in]       name: the shared region's name.
 * @param[out]      addr: pointer where the shared region's virtual base address will be copied.
 *
 * @retval NCP_ST_SUCCESS success
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured,  or the application has not attached to the configuration.
 * @retval NCP_ST_INVALID_PARAMETER NULL addr pointer
 * @retval NCP_ST_TASK_SHARED_REGION_NOT_FOUND The shared region indicated by
 *          regionId is not included in this thread queue set.
*/

NCP_API ncp_st_t
ncp_task_shared_region_virtual_base_get_by_name(
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_task_resource_name_t *name,
    void **addr);

/*!
 * @fn ncp_st_t ncp_task_shared_region_size_get_by_id(
 *                  ncp_task_tqs_hdl_t tqsHdl,
 *                  ncp_uint32_t regionId,
 *                  void **size)
 *
 * @brief   This API returns the size of the shared region indicated by
 *          regionId.
 *
 * @param[in]       tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in]       regionId: the shared region ID.
 * @param[out]      size: pointer where the shared region's size will be copied.
 *
 * @retval NCP_ST_SUCCESS success
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured,  or the application has not attached to the configuration.
 * @retval NCP_ST_INVALID_PARAMETER NULL size pointer
 * @retval NCP_ST_TASK_SHARED_REGION_NOT_FOUND The shared region indicated by
 *          regionId is not included in this thread queue set.
*/

ncp_st_t
ncp_task_shared_region_size_get_by_id(
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_uint32_t regionId,
    ncp_uint64_t *size);

/*!
 * @fn ncp_st_t ncp_task_shared_region_size_get_by_name(
 *                  ncp_task_tqs_hdl_t tqsHdl,
 *                  ncp_task_resource_name_t *name,
 *                  void **size)
 *
 * @brief   This API returns the size of the shared region indicated by name.
 *
 * @param[in]       tqsHdl:  TQS handle returned by previous call to ncp_task_tqs_bind()
 * @param[in]       name: the shared region's name.
 * @param[out]      size: pointer where the shared region's size will be copied.
 *
 * @retval NCP_ST_SUCCESS success
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured,  or the application has not attached to the configuration.
 * @retval NCP_ST_INVALID_PARAMETER NULL size pointer
 * @retval NCP_ST_TASK_SHARED_REGION_NOT_FOUND The shared region indicated by
 *          regionId is not included in this thread queue set.
*/

ncp_st_t
ncp_task_shared_region_size_get_by_name(
    ncp_task_tqs_hdl_t tqsHdl,
    ncp_task_resource_name_t *name,
    ncp_uint64_t *size);

/*!
 * @fn ncp_st_t ncp_task_tracing_enable(
 *                  ncp_hdl_t ncpHdl)
 *
 * @brief   This API enables NCAv3 task tracing. In order for the NCA to trace
 *          tasks on a given queue, task tracing must also be enabled for that
 *          queue, via ncp_task_queue_tracing_enable() or through the ASE
 *          configuration file.
 *
 * @note    To enable Coresight timestamp generation: ncpWrite 0x1e1.0.0x1000 1
 *
 * @param[in] ncpHdl:  NCP handle returned by previous call to ncp_config
 *
 * @retval NCP_ST_SUCCESS success
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 */

ncp_st_t
ncp_task_tracing_enable(
    ncp_hdl_t ncpHdl);

/*!
 * @fn ncp_st_t ncp_task_tracing_disable(
 *                  ncp_hdl_t ncpHdl)
 *
 * @brief   This API disables NCAv3 task tracing.
 *
 * @param[in] ncpHdl:  NCP handle returned by previous call to ncp_config
 *
 * @retval NCP_ST_SUCCESS success
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 */
ncp_st_t
ncp_task_tracing_disable(
    ncp_hdl_t ncpHdl);

/*!
 * @fn ncp_st_t ncp_task_tracing_reset(
 *                  ncp_hdl_t ncpHdl)
 *
 * @brief   This API resets the NCAv3 task tracing to its configuration state.
 *
 * @param[in] ncpHdl: NCP handle returned by previous call to ncp_config
 *
 * @retval NCP_ST_SUCCESS success
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 */
ncp_st_t
ncp_task_tracing_reset(
    ncp_hdl_t ncpHdl);


/*!
 * @fn ncp_st_t ncp_task_queue_tracing_enable(
 *                  ncp_hdl_t ncpHdl,
 *                  ncp_uint32_t ncaQueueId);
 *
 * @brief   This API enables task tracing for the specified queue. Task tracing
 *              must be globally enabled (via ncp_task_tracing_enable() or the
 *              ASE configuration) as well for the NCAv3 to trace tasks in this
 *              queue.
 *
 * @param[in] ncpHdl:  NCP handle returned by previous call to ncp_config
 * @param[in] ncaQueueId: The ID of the NCA queue
 *
 * @retval NCP_ST_SUCCESS success
 * @retval NCP_ST_INVALID_PARAMETER The ncaQueueId is not between 0 and 203
 *              (inclusive).
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 */

ncp_st_t
ncp_task_queue_tracing_enable(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t ncaQueueId);

/*!
 * @fn ncp_st_t ncp_task_queue_tracing_disable(
 *                  ncp_hdl_t ncpHdl,
 *                  ncp_uint32_t ncaQueueId);
 *
 * @brief   This API disables task tracing for the specified queue.
 *
 * @param[in] ncpHdl:  NCP handle returned by previous call to ncp_config
 * @param[in] ncaQueueId: The ID of the NCA queue
 *
 * @retval NCP_ST_SUCCESS success
 * @retval NCP_ST_INVALID_PARAMETER The ncaQueueId is not between 0 and 203
 *              (inclusive).
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 */

ncp_st_t
ncp_task_queue_tracing_disable(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t ncaQueueId);

/*!
 * @fn ncp_st_t ncp_task_app_profile_pool_mapping_get(
 *                  ncp_hdl_t ncpHdl,
 *                  ncp_task_resource_name_t *appProfileName,
 *                  ncp_bool_t poolEnabled[8]);
 *
 * @brief   This function will set poolEnabled[X] to true if pool X is in the
 *          profile’s pool mapping. poolEnabled[0] is for the CPU pool and
 *          poolEnabled[1] is for the fixed pool.
 *
 * @param[in] ncpHdl:  NCP handle returned by previous call to ncp_config
 * @param[in] appProfileName: Name of the application profile
 * @param[out] poolEnabled: array of booleans, one entry per pool, that
 *                  indicates whether the pool is in the application
 *                  profile's pool mapping.
 *
 * @retval NCP_ST_SUCCESS success
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 * @retval NCP_ST_INVALID_PARAMETER appProfileName is NULL or does not match a
 *              configured application profile, or poolEnabled is NULL.
 */
NCP_API ncp_st_t
ncp_task_app_profile_pool_mapping_get(
    ncp_hdl_t ncpHdl,
    ncp_task_resource_name_t *appProfileName,
    ncp_bool_t poolEnabled[8]);

/*!
 * @fn ncp_st_t ncp_task_app_profile_name_get(
 *                  ncp_hdl_t ncpHdl,
 *                  ncp_uint32_t tqsId,
 *                  ncp_task_resource_name_t *appProfileName);
 *
 * @brief   This function will return the application profile name for the
 *          specified (configured) TQS.
 *
 * @param[in] ncpHdl:  NCP handle returned by previous call to ncp_config
 * @param[in] tqsId:   The ID of the Thread Queue Set
 * @param[out] appProfileName: Name of the application profile
 *
 * @retval NCP_ST_SUCCESS success
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 * @retval NCP_ST_INVALID_PARAMETER appProfileName is NULL.
 * @retval NCP_ST_TASK_TQS_NOT_CONFIGURED The TQS must be configured in the ASE
 *              or dynamically before it can be used in this API.
 */
ncp_st_t
ncp_task_app_profile_name_get(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t tqsId,
    ncp_task_resource_name_t *appProfileName);

/*!
 * @fn ncp_st_t ncp_task_unscheduled_receive_queue_profile_pool_mapping_get(
 *                  ncp_hdl_t ncpHdl,
 *                  ncp_task_resource_name_t *queueProfileName,
 *                  ncp_bool_t poolEnabled[8]);
 *
 * @brief   This function will set poolEnabled[X] to true if pool X is in the
 *          unscheduled receive queue profile’s pool mapping. poolEnabled[0] is
 *          for the CPU pool and poolEnabled[1] is for the fixed pool.
 *
 * @param[in] ncpHdl:  NCP handle returned by previous call to ncp_config
 * @param[in] queueProfileName: Name of the unscheduled receive queue profile.
 * @param[out] poolEnabled: array of booleans, one entry per pool, that
 *                  indicates whether the pool is in the application
 *                  profile's pool mapping.
 *
 * @retval NCP_ST_SUCCESS success
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 * @retval NCP_ST_INVALID_PARAMETER queueProfileName is NULL or does not match a
 *              configured application profile, or poolEnabled is NULL.
 */
ncp_st_t
ncp_task_unscheduled_receive_queue_profile_pool_mapping_get(
    ncp_hdl_t ncpHdl,
    ncp_task_resource_name_t *queueProfileName,
    ncp_bool_t poolEnabled[8]);

/*!
 * @fn ncp_st_t ncp_task_unscheduled_receive_queue_profile_name_get(
 *                  ncp_hdl_t ncpHdl,
 *                  ncp_uint32_t tqsId,
 *                  ncp_task_resource_name_t *queueProfileName);
 *
 * @brief   This function will return the receive queue profile name for the
 *          specific unscheduled queue, if any.
 *
 * @param[in] ncpHdl:  NCP handle returned by previous call to ncp_config
 * @param[in] queueId: The unscheduled queue ID
 * @param[out] appProfileName: Name of the queue profile
 *
 * @retval NCP_ST_SUCCESS success
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 * @retval NCP_ST_INVALID_PARAMETER appProfileName is NULL.
 * @retval NCP_ST_TASK_UNSCHEDULED_QUEUE_HAS_NO_QUEUE_PROFILE There is no
 *              queue profile configured for this unscheduled queue.
 */
ncp_st_t
ncp_task_unscheduled_receive_queue_profile_name_get(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t queueId,
    ncp_task_resource_name_t *queueProfileName);

/*!
 * @fn ncp_st_t ncp_task_ipcq_disable(
 *                  ncp_hdl_t ncpHdl,
 *                  ncp_uint32_t tqsId);
 *
 * @brief   This function will stop the NCA from scheduling to the iPCQ.
 *
 * @param[in] ncpHdl:  NCP handle returned by previous call to ncp_config
 * @param[in] tqsId:   The ID of the Thread Queue Set.
 *
 * @retval NCP_ST_SUCCESS success
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 * @retval NCP_ST_INVALID_PARAMETER The tqsId is not between 0 and 63
 * 		(inclusive).
 * @retval NCP_ST_TASK_TQS_NOT_CONFIGURED The TQS must be configured in the ASE
 *              or dynamically before it can be used in this API.
 */
ncp_st_t
ncp_task_ipcq_disable(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t tqsId);

/*!
 * @fn ncp_st_t ncp_task_ipcq_enable(
 *                  ncp_hdl_t ncpHdl,
 *                  ncp_uint32_t tqsId);
 *
 * @brief   This function will tell the NCA to schedule to the iPCQ, if
 *	        had been previously disabled with ncp_task_ipcq_disable().
 *
 * @param[in] ncpHdl:  NCP handle returned by previous call to ncp_config
 * @param[in] tqsId:   The ID of the Thread Queue Set.
 *
 * @retval NCP_ST_SUCCESS success
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured, or the
 *              application has not attached to the configuration.
 * @retval NCP_ST_INVALID_PARAMETER The tqsId is not between 0 and 63
 * 		(inclusive).
 * @retval NCP_ST_TASK_TQS_NOT_CONFIGURED The TQS must be configured in the ASE
 *              or dynamically before it can be used in this API.
 */
ncp_st_t
ncp_task_ipcq_enable(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t tqsId);

/*!
 * @fn ncp_st_t ncp_task_fixed_pool_virtual_base_get(
 *                  ncp_hdl_t ncpHdl,
 *                  void **addr)
 *
 * @brief   This API returns the virtual base address of the fixed pool, if
 *          it has been configured.
 *
 * @param[in] ncpHdl:  NCP handle returned by previous call to ncp_config
 * @param[out] addr: pointer where the fixed pool's virtual base address will be copied.
 *
 * @retval NCP_ST_SUCCESS success
 * @retval NCP_ST_TASK_NO_GSM the device has not been configured,  or the application has not attached to the configuration.
 * @retval NCP_ST_INVALID_PARAMETER NULL addr pointer
 */
NCP_API ncp_st_t
ncp_task_fixed_pool_virtual_base_get(
    ncp_hdl_t ncpHdl,
    void **addr);
/*
 * @brief mutex_type_t: enum for the type of mutex used by APIs.
 */
typedef enum
{
    NCP_MUTEX_PROCESS_SHARED,
    NCP_MUTEX_PROCESS_PRIVATE,
    NCP_MUTEX_PROCESS_SHARED_ROBUST,
} ncp_mutex_attr_t;

/**
 * Set mutex attribute for CPU pool used by @p tqsHdl.
 *
 * @note This api works only for TQS which is using CPU Pool. if TQS is using
 * fixed pool (1) or shared buffer pool (2-7), then error will be retruned and
 * nothings will change.
 *
 * @param tqsHdl - valid task handle
 * @param mtxType - mutex attribute to be set on CPU Pool bound to @p tqsHdl
 * NCP_MUTEX_PROCESS_SHARED,NCP_MUTEX_PROCESS_PRIVATE,
 * NCP_MUTEX_PROCESS_SHARED_ROBUST
 *
 * @note All mutexes are configured as NCP_MUTEX_PROCESS_SHARED_ROBUST by
 * default.
 * @note Mutex attribute will be changed to NCP_MUTEX_PROCESS_SHARED_ROBUST once
 * all process threads will be unbound from tqs.
 *
 * @return NCP_ST_SUCCESS if change was possible
 */
NCP_API ncp_st_t
ncp_task_cpu_pool_mutex_attrib_set(ncp_task_tqs_hdl_t tqsHdl, ncp_mutex_attr_t mtxType);

NCP_API ncp_st_t
ncp_task_cpu_pool_mutex_attrib_get(ncp_task_tqs_hdl_t tqsHdl, ncp_mutex_attr_t *mtxType);

NCP_API ncp_st_t
ncp_task_tqs_mutex_attrib_set(ncp_uint8_t tqsID, ncp_mutex_attr_t mtxType);

NCP_API ncp_st_t
ncp_task_tqs_mutex_attrib_get(ncp_uint8_t tqsID, ncp_mutex_attr_t *mtxType);

/* Catch non-ported code */
#define ncp_task_hdl_create(_a,_b,_c,_d,_e) (NCP_ST_NOT_IMPLEMENTED)
#define ncp_task_hdl_remove(_a) (NCP_ST_NOT_IMPLEMENTED)


#ifdef __cplusplus
}
#endif
#endif /* __NCP_TASK_H__ */
