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

#ifndef __ncp_task_lite_basetypes_h__
#define __ncp_task_lite_basetypes_h__

#ifdef __cplusplus
extern "C" { 
#endif

#include <config.h>

#define NCP_API extern
#define NCP_EXPORT_SYMBOL(sym) EXPORT_SYMBOL(sym)

/*
 * Basic memory types
 */
 
#include <linux/types.h>

typedef unsigned char      __uint8_t;
typedef unsigned short     __uint16_t;
typedef unsigned long      __uint32_t;
typedef unsigned long long __uint64_t;

typedef int8_t     ncp_int8_t;
typedef int16_t    ncp_int16_t;
typedef int32_t    ncp_int32_t;

typedef __uint8_t  ncp_uint8_t;
typedef __uint16_t ncp_uint16_t;
typedef __uint32_t ncp_uint32_t;

typedef __uint8_t  ncp_bool_t;

typedef int64_t    ncp_int64_t;
typedef __uint64_t ncp_uint64_t;

/*
 * Errors
 */

typedef enum
{
    NCP_ST_SUCCESS,
    /*!< 
     * NO ERROR
     */ 
    NCP_ST_ERROR,
    /*!< 
     * Generic Error.
     */        
    NCP_ST_TASK_LITE_UBOOT_NO_ALLOCATOR_REGISTERED,
    /*!< 
     * The Task I/O-LITE module requires that the client register function
     * pointers for alloc, free, and va2pa before attempting to use the
     * API or configure the NCA.
     */           
    NCP_ST_TASK_LITE_NULL_SEND_DONE_FUNCTION,
    /*!< 
     * The Task I/O-LITE module requires that a send done function be set in the the send meta data.
     */             
    NCP_ST_TASK_LITE_QS_NOT_IN_USE,
    /*!< 
     * The Task Lite Handle is not valid
     */    
    NCP_ST_TASK_LITE_QS_NOT_AVAILABLE,
    /*!< 
     * The Task I/O-LITE module detected and invalid queueset.   It may be in use, out of range,  or managed
     * by a different domain.
     */           
    NCP_ST_TASK_GSM_ALLOC_NOT_ALLOWED,
    /*!< 
     * The Task I/O module detecgted an attempt to allocate fro the GSM during warm restart
     */    

    NCP_ST_TASK_MMAP_FAILED,
    /*!< 
     * The Task I/O module received an error when attempting to map a physical memory region
     */    
    NCP_ST_TASK_QUESET_NOT_IN_LOCAL_DOMAIN,
    /*!< 
     * The Thread Queue Set ID supplied references a queueset owned by another AMP domain.
     */

    NCP_ST_TASK_NO_MAN_COMPLETION_OWED,
    /*!< 
     * The task supplied in the ncp_task_recv_done API does not match one which is awaiting 
     * manual completion.
     */
    NCP_ST_TASK_NULL_MAN_COMPLETION_LIST,
    /*!< 
     * No tasks received on this task handle are awaiting manual completion.
     */
    NCP_ST_TASK_RECEIVE_QUEUES_MUST_HAVE_SAME_SHARE_PERMISSION,
    /*!< 
     * All receive queues used by a thread must have same share permission, 
     * either all exclusive or all shared.
     */
    NCP_ST_TASK_EXCLUSIVE_BINDING_NOT_AVAIL,                
    /*!< 
     * A request to bind to a queue or pipeline with exclusive access could 
     * not be completed.   This occurs when the resource has already been 
     * bound with either shared or exclusive access by another thread or 
     * process.
     */
    NCP_ST_TASK_SHARED_BINDING_NOT_AVAIL,                
    /*!<
     * A request to bind to a queue or pipeline with shared access could 
     * not be completed.   This occurs when the resource has already been 
     * bound with exclusive access by another thread or process.    
     */
    NCP_ST_TASK_SHARED_VP_BINDING_NOT_AVAIL,                
    /*!<
     * A request to bind to a VP in shared mode failed due to the associated nca queue
     * or vp already being bound for exclusive access
     */     
    NCP_ST_TASK_EXCLUSIVE_VP_BINDING_NOT_AVAIL,                
    /*!<
     * A request to bind to a VP in exclusive mode failed due to the associated nca queue
     * or vp already being bound for shared access 
     */          
    NCP_ST_TASK_INVALID_NCA_INPUT_QUEUE,                
    /*!< 
     * The NCA recevie queue specified in the bind exceeds
     * the upper limit defined for this hardware platform.
     */
    NCP_ST_TASK_INVALID_NCA_OUTPUT_QUEUE,                
    /*!< 
     * The NCA send queue specified in the bind exceeds
     * the upper limit defined for this hardware platform.
     */    
    NCP_ST_TASK_INVALID_RECEIVE_QUEUE,                
    /*!<
     * The software receive queue ID supplied for the request is not 
     * currently bound for this receive handle.
     */
    NCP_ST_TASK_SEND_QUEUE_FULL,                
    /*!<
     * The NCA output queue (exclusive use) or intermediate software 
     * queue (shared use) is currently full.   This is not an error 
     * condition.   Applications that use blocking (wait==TRUE) task 
     * IO api calls should never receive this status.
     */
    NCP_ST_TASK_RECV_QUEUE_EMPTY,                
    /*!<
     * The NCA input queue (exclusive use) or intermediate software 
     * queue (shared use) is currently empty.   This is not an error 
     * condition.   Applications that use blocking (wait==TRUE) task 
     * IO api calls should never receive this status.
     */    
    NCP_ST_TASK_INVALID_TASK_HANDLE,                
    /*!<
     * The task handle supplied for the API request is not valid.  
     * Task handles must be created using the ncp_task_hdl_create
     * API function, and are valid only withing the contect of the
     * thread that created them.
     */
    NCP_ST_TASK_INVALID_VP_HANDLE,                
    /*!<
     * The VpHdl (virtual pipeline handle) supplied to 
     * ncp_task_recv_queue_vp_unbind is invalid or NULL.
     */
    NCP_ST_TASK_INVALID_BIND_TABLE_ENTRY,                
    /*!<
     * The level 1 bind table receive queue is not null, but
     * shared binding is specified.   This is an internal error.
     */
    NCP_ST_TASK_NO_FREE_DYNAMIC_QUEUE,                
    /*!<
     * There are no recevie queue IDs currently available.   Dynamic queue 
     * IDs are in the range 0..127
     */
    NCP_ST_TASK_NULL_TASK_IN_RECVDONE,                
    /*!<
     * The API function ncp_task_recv_done was called with a Null Task
     * pointer
     */
    NCP_ST_TASK_RX_TOO_BIG,                
    /*!<
     * The size of the task buffer allocation request exceeds the maximum
     * size defined for the memory/rx pool.
     */
    NCP_ST_TASK_BUFFER_POOL_NOT_FOUND,
    /*!<
     * The task memory/buffer pool is not associated with a receive buffer queue.
     * This is an internal error.
     */    
    NCP_ST_TASK_REQUESTED_BUFF_POOL_TOO_BIG,                
    /*!<
     * The task memory/buffer pool could not be allocated due to its reqested
     * size being in excess of the amount of memory reserved for this purpose.
     */
    NCP_ST_TASK_QMAP_ERR_TOO_BIG,                
    /*!<
     * The specified queue ID exceeds the uppler limit for this hardware platform
     */
    NCP_ST_TASK_BAD_QTYPE_FOR_STATUS_READ,                
    /*!<
     * Invalid NCA queue type detected.   This is an internal error. 
     */
    NCP_ST_TASK_PUT_NULL_TASK_COMPLETION_QUEUE,                
    /*!<
     * An inconsistensy has been detected in the NCA completion queue.
     * This is an internal error.
     */
    NCP_ST_TASK_PUT_NULL_TASK_OUTPUT_QUEUE,                
    /*!<
     * An inconsistensy has been detected in the NCA output queue.
     * This is an internal error.
     */    
    NCP_ST_TASK_INVALID_FIXED_QUEUEID,                
    /*!<
     * The supplied receive queue ID is out of range, or in use.   Fixed queue IDs must
     * be in the range 128..255.
    */
    NCP_ST_TASK_NULL_RECVQUEUEID_PTR,                
    /*!<
     * The application has called ncp_task_recv_queue_bind with a NULL 
     * pointer for the pRecvQueueId parameter. The API requires a valid address 
     * where the allocated receive queue ID can be returned.
     */
    NCP_ST_TASK_HANDLE_HEAD_NULL,                
    /*!<
     * A request to unbind a queue, or receive from a queue, could not be 
     * satisfied due to no queues being associated with the receive handle 
     * that was supplied.
     */
    NCP_ST_TASK_SEND_NULL_METADATA_PTR,                
    /*!<
     * The application did not provide a valid pointer to the task meta data.
     * Task meta data is required for all task send requests.
      */
    NCP_ST_TASK_SEND_NULL_TASK_PTR,                
    /*!<
     * The application did not provide a valid pdu/buffer pointer.   If the
     * pdu data size of a ncp_task_send request is non zero,   a valid buffer
     * pointer is required.
     */
    NCP_ST_TASK_NO_GSM,                
    /*!<
     * The internal shared memory segment used by the task IO module has not
     * been created.   This is an internal error.
     */
    NCP_ST_TASK_BUFFSIZE_TOO_LARGE,                
    /*!<
     * A request to allocate a task buffer has failed due to the size requested
     * exceeding the maximum size configured for the task rx buffer/memory pool.
     */
    NCP_ST_TASK_CLIENT_FREE_NULLPTR,                
    /*!<
     * The application has called ncp_task_buffer_free with a null pointer.
     * A valid pointer to a buffer previously allocated with 
     * ncp_task_buffer_alloc must be provided.
     */
    NCP_ST_TASK_CFG_TOO_MANY_TASK_MEMPOOLS,                
    /*!<
     * The number of memory pools configured exceeds the maximum allowed
     * for this hardware platform.
     */
    NCP_ST_TASK_NO_WARM_RESTART_VP,
    /*!<
     * The CPU-CPU virtual pipeline required for NCA warm restart was not found.
     */    
    NCP_ST_TASK_NO_IPCQ_FOR_RXB_POOL_IN_WARM_RESTART,
    /*!<
     * Cannot drain receive buffer pool in NCA warm restart due to no NCA receive queues are configured to use
     * a configured receive buffer pool.
     */    
    NCP_ST_TASK_CFG_TOO_MANY_RXB_POOLS,                
    /*!<
     * The number of NCA receive pools associated with the configured task memory 
     * pool exceeds the maximum allowed for this hardware platform,  or exceeds 
     * the maximum currently supported by software (1).
     */     
    NCP_ST_TASK_CFG_TOO_MANY_QUEUE_GROUPS,      
    /*!<
     * The number of queue groups configured exceeds the maximum allowed
     * for this hardware platform.
     */
    NCP_ST_TASK_RECV_QUEUE_NOT_IN_QUEUESET,
    /*!<
     * The ncaQueueId specified in the ncp_task_recv_queue_bind must be part of the
     * thread queue set (outputQueueID) that was specified in the ncp_task_hdl_create API.
     */
    NCP_ST_TASK_RECV_ACCESS_MODE_NOT_SAME_AS_QUEUESET,
    /*!<
     * If the ncp_task_hdl_create API was used to open a queueset in exclusive mode, all assoiated receive queues must be bound in exclusive mode too.
     */    
    NCP_ST_TASK_CFG_TOO_MANY_THREAD_QUEUESETS_PER_GROUP,
    /*!<
     * The number of thread queue sets configured for this group exceeds the 
     * maximum allowed per group for this hardware platform.
     */       
    NCP_ST_TASK_BUFFSZ_ORDER_ERR,                
    /*!<
     * The configuration contains invalid sizes for the rx buffer pool.
     * Buffer size 0 must be < buffer size 1 < buffer size 2, < buffer 
     * size 3.  
     */
    NCP_ST_TASK_BUFFSZ_OUT_OF_BOUNDS,                
    /*!<
     * An invalid buffer size was detected during configuration.   This is 
     * an internal error.
     */
    NCP_ST_TASK_NO_CACHE_ALLLIGNED_MEM, 
    /*!<
     * The task IO module's private pool of cache alligned buffers has 
     * been exhausted.   
     */
    NCP_ST_TASK_NO_MALLOC_MEM,                
    /*!< 
     * A request for memory allocation could not be satisfied due to 
     * insufficient resources.
     */
    NCP_ST_TASK_NULL_RECV_QUEUE_PTR,                
    /*!<
     * A invalid receive queue pointer address was detected when allocating 
     * task queue resources.   
     */
    NCP_ST_TASK_RECV_RET_SUCCESS_WITH_NULL_PTR,                
    /*!<
     * A NULL pointer was returned during a task recevie operation.
     * This is an internal error. 
     */
    NCP_ST_TASK_NULL_PCQ_PRODUCER_PTR,                
    /*!<
     * The pointer to the producer index of a PCQ was NULL.   This is an
     * internal error.
     */
    NCP_ST_TASK_NULL_PCQ_CONSUMER_PTR,                
    /*!<
     * The pointer to the consumer index of a PCQ was NULL.   This is an
     * internal error.
     */    
    NCP_ST_TASK_NO_QUEUESET_IN_DOMAIN,
    /*!<
     * At least one task queue set must be defined for every management domain 
     */
    NCP_ST_TASK_NO_QUEUESET_IN_GRP,
    /*!<
     * At least one task queue set must be defined for every PCQ group
     * configured for the NCA.
     */
    NCP_ST_TASK_NO_TASKMEMPOOL_DEFINED,                
    /*!<
     * No task memory pools were configured.   Task memory pools are required 
     * for all valid NCA configurations.
     */
    NCP_ST_TASK_NO_RXB_POOL_DEFINED,                
    /*!<
     * At least one NCA receive buffer pool must be defined for each task memory pool that is configured.   
     */     
    NCP_ST_TASK_BUFFPOOL_CORRUPTION,                
    /*!<
     * An inconsistency has been detected while processing the task memory pool.
     */
    NCP_ST_TASK_POOLALLOC_RET_NULL,                
    /*!<
     * The task IO module was unable to replenish the NCA's internal receive 
     * buffer pool due to a resource shortage.
     */
    NCP_ST_TASK_POOLALLOC_RET_PHYSADDR_NULL,                
    /*!<
     * Unexpected error encountered when computing the physical aqddress of the
     * task buffer.  This is an internal error.
     */
    NCP_ST_TASK_CORRUPT_NCA_INPUT_QUEUE,                
    /*!< 
     * An inconsistency has been detected while processing the NCA input queue.
     * This is an internal error.
     */
    NCP_ST_TASK_REQUEST_FOR_ZERO_LENGTH_TASK_BUFFER,                
    /*!<
     * The task IO task_buffer_alloc API was called with size equal zero,  which
     * is invalid.
     */
    NCP_ST_TASK_ALLOC_REQUIRES_POINTER,                
    /*!<
     * The task IO task_buffer_alloc API was called with a NULL task pointer.
     * The newly allocated buffer is returned at the address provided by the 
     * caller,   which requires a non NULL pointer.
     */
    NCP_ST_TASK_DISPATCHED,                
    /*!<
     * This is an informational status code.   This status is returned when 
     * a call to ncp_tasK-recv results in tasks being dispatched to the receive 
     * dispatch function provided in the ncp_task_recv_queue_vp_bind API.
     */
    NCP_ST_TASK_REQ_FOR_ZERO_LEN_CACHE_ALIGNED_MEM,                
    /*!<
     * A request for cache alligned memory contained an invalid size specifier.
     * This is an internal error.
     */
    NCP_ST_TASK_NCP_DESTROY_HANDLE_INVALID,   
    /*!<
     * A request to destroy the NCA configuration could not be completed because
     * the NCA handle is corrupt or invalid.   This is an internal error.
     */
    NCP_ST_TASK_NO_SWQUEUE_MEM,                
    /*!<
     * An internal request for task queue memory could not be satisfied due to
     * memory exhaustion.
     */
    NCP_ST_TASK_HDL_CREATE_ERR,  
    /*!<
     * The task handle could not be created due to memory exhaustion.
     */  
    NCP_ST_TASK_TLS_RETRIEVAL_ERR,                
    /*!<
     * The task IO module could not retrieve the thread local 
     * storage for this thread. The API function ncp_task_hdl_create 
     * must be called by every thread that wishes to will use the Task IO API.
     */    
    NCP_ST_TASK_ALLOC_SKB_FAILURE,                
    /*!<
     * A task buffer could not be allocated due to skb pool exhaustion.   This
     * error applies to kernel mode task IO clients.
     */
    NCP_ST_TASK_BAD_GROUP_FOR_IRQ,                
    /*!<
     * The PCQ group associated with the interrupt enable/disable request is not 
     * valid.
     */
    NCP_ST_TASK_PROXY_CREATE_PROCESS_ERR,                
    /*!<
     * Could not start the task IO proxy service.   The proxy service is 
     * required if shared queues are requested.   This is an operating 
     * system specific error.
     */    
    NCP_ST_TASK_NULL_L1_BINDP,                
    /*!<
     * A request to unbind a pipeline via a call to 
     * ncp_task_recv_queue_vp_unbind failed due to no actively bound 
     * pipeline entry being found.   
     */
    NCP_ST_TASK_NO_MEM_L1BIND,                
    /*!<
     * The memory required to bind the virtual pipeline could not be allocated
     * due to memory exhaustion.
     */
    NCP_ST_TASK_NO_MEM_L2BIND,                
    /*!<
     * The memory required to bind the virtual pipeline could not be allocated
     * due to memory exhaustion.
     */    
    NCP_ST_TASK_NO_BUFF_DESC,                
    /*!<
     * A call to ncp_task_free failed due to buffer descriptor exhaustion.
     */
    NCP_ST_INVALID_BUFF_FOR_TASK_FREE,                
    /*!<
     * A call to ncp_task_free failed due to the buffer not belong to the VA range of the pool.
     */         
    NCP_ST_TASK_SEND_SEGMENTS_INVALID_DESC,                
    /*!<
     * A call to ncp_task_send_segments failed due to a NULL descriptor table
     * pointer.
     */
    NCP_ST_TASK_SEND_SEGMENTS_INVALID_NUM_SEGS,
    /*!<
     * A call to ncp_task_send_segments failed due to the number of segments being 
     * less that zero or greater than 16. 
     */    
    NCP_ST_TASK_UNEXPECTED_QUEUE_TYPE,                
    /*!<
     * A internal call to map a queue number to its associated PCQ pointer
     * failed due to an invalid queue type.   This is an internal error.
     */
    NCP_ST_TASK_SHUTDOWN,                
    /*!<
     * This status code is returned when the system is undergoing shutdown.
     * previously bound resources should be unbound,   and all task IO resources
     * should be returned.   Finally the application should exit.
     */
    NCP_ST_TASK_PROXY_GRP_OUT_OF_RANGE,                
    /*!<
     * The task IO proxy service was started with an invalid group parameter.
     * This is an internal error.
     */
    NCP_ST_TASK_PROXY_DID_NOT_STOP,                
    /*!<
     * The task IO proxy service could not be terminated.   This is an internal 
     * error.
     */
    NCP_ST_TASK_SHARED_QUEUES_DISABLED, 
    /*!<
     * The requested action cannot be taken because shared queue support is 
     * disabled.
     */
    NCP_ST_TASK_MISMATCH,              
    /*!<
     * This status code is used by the ncpTaskRecv CLI to report data 
     * validation errors.
     */
    NCP_ST_TASK_NO_LCM_MEMORY,
    /*!<
     * Could not mmap VMA for accessing LCM, or LCM exhausted.
     */
    NCP_ST_TASK_NO_GSM_MEMORY,
    /*!<
     * Could not mmap VMA for accessing GSM, or GSM exhausted.
     */
    NCP_ST_TASK_NO_TASK_CONTROL_MEMORY,
    /*!<
     * Could not mmap VMA for accessing Task Control are of GSM, or Task Control memory exhausted.
     */
    NCP_ST_TASK_NO_THREADQUEUESET_TDF_SECTION,
    /*!<
     * TDF file does not contain a threadQueueSet section,  which is required.
     */    
    NCP_ST_TASK_NO_TASKSEND_TDF_SECTION,
    /*!<
     * TDF file does not contain a taskSend section,  which is required.
     */    
    NCP_ST_TASK_NO_TASKRECV_TDF_SECTION,
    /*!<
     * TDF file does not contain a taskRecv section,  which is required.
     */         
    NCP_ST_TASK_NO_TASKRECVQUEUEBIND_TDF_SECTION,
    /*!<
     * TDF file does not contain a taskRecvQueueBind section,  which is required.
     */        
    NCP_ST_TASK_NO_TASKRECVQUEUEVPBIND_TDF_SECTION,
    /*!<
     * TDF file does not contain a taskRecvQueueVpBind section,  which is required.
     */     
    NCP_ST_TASK_RECEIVE_QUEUE_NOT_FOUND,
    /*
     *!< 
     * The specified receive queue was not found in the list of receive 
     * queues associated with this task handle.
     */
    NCP_ST_TASK_RETRY,
    /*
     *!< 
     * The device ioctl must be retried
     */      
    NCP_ST_TASK_IOCTL_FAILED,
    /*
     *!< 
     * The device ioctl has returned in error
     */                     
    NCP_ST_TASK_QUEUE_STUCK_IN_WARM_RESTART,
    /*
     *!< 
     * Detected unresponsive hardware queue in warm restart
     */       
    NCP_ST_TASK_WARM_RESTART_UNSUPPORTED_PLATFORM,
    /*
     *!< 
     * NCA TAsk I/O Is not supported on this platform.
     */       

    /* Used internally by NCA simulator,   but not used by TaskIO API */
    NCP_ST_TASK_INVALID_NCA_TASK_COMPLETION_QUEUE,  /*!< */
    NCP_ST_TASK_TASK_COMPLETION_QUEUE_FULL,         /*!< */

} ncp_st_t;
 



#ifdef __cplusplus
}
#endif

#endif
