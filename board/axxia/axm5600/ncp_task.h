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

/*! @file      ncp_task.h
*
*  @brief     Task I/O APIs
*
*  @addtogroup _task_ Task Management
*
*  @details   This document discusses the APIs for, and high level design of, the runtime software
*             interfaces that enable the host CPU to send tasks to and receive tasks from virtual
*             pipelines.
*             The CPU communicates with other engines in the system via tasks. The CPU sends and
*             receives tasks using very efficient, cacheable memory based producer-consumer style
*             DMA queues. These queues are called task queues and hardware support for task queues
*             is provided by the Nuevo CPU Adapter (NCA). Four types of task queues are supported:
*             task input queues, task output queues,   task completion queues,  and NCA task
*             receive buffer queues.     Note that input (Rx) and output (Tx) directions are from
*             the CPU’s perspective. That is, the CPU transmits tasks using task output queues and
*             receives tasks using task input queues.  The CPU uses task completion queues to
*             notify the NCA that processing is complete for a particular task.   Similarly,   the
*             CPU uses NCA task receive buffer queues to provide buffers to the NCA’s receive
*             buffer pool.
*             The NCA is designed for multi-core CPUs and therefore provides redundant resources
*             to allow independent operation of each core (i.e. no shared resource contention
*             issues between cores). The first implementation of Nuevo is designed to support up
*             to 6 (4 internal + 2 external) CPUs. It provides 24 task input queues and 12 task
*             output,  completion,   and receive buffer queues. The motivation behind the 24 task
*             input queue number is to provide a minimum of 4 input queues per CPU core. This
*             allows each core to have high and low priority user mode and kernel mode task input
*             queues. The reason for 12 task output queues is to provide each CPU core with both a
*             user mode and kernel mode task output queue. Note that the queue usages mentioned
*             here are only for design sizing purposes. All NCA task queues are general purpose
*             and can be partitioned in any number of different ways, as configured by software.
*             In addition to the 24 task input queues described above, the NCA provides a total of
*             8 logical task input queues where each logical queue can be mapped to as many as 8
*             real input queues. The NCA performs load balancing and ordering (if configured to do
*             so) for tasks sent to logical queues.
*             As noted above the NCA design sizing accounts for the possibility of having both
*             “user mode” and “kernel mode” queues. This comes from the requirement to support a
*             very efficient (low CPU overhead) runtime environment for Linux user mode
*             applications.
*  @note      As noted above,  the NCA exposes numerous queues that are used to interact with the
*             CPU in order to accomplish sending and receiving tasks.   Output queues can be used
*             in either exclusive or shared mode. Exclusive mode
*             assumes that there will be no contention for the queue between multiple threads
*             or processes.   In this mode,   no locking or other means of access synchronization
*             are employed.   Exclusive mode therefore provides the highest level of performance
*             since applications interact directly with the target NCA hardware queue in a lockless manner.
*             Serialization using mutual exclusion primitives is required when output queues are shared,
*             so shared queues will not allow for maximum performance.
*
*  @{
*/

#ifndef __ncp_task_h__
#define __ncp_task_h__

#ifdef __cplusplus
extern "C" {
#endif

#include "ncp_status.h"

/*!
*  @brief Task IO Handle:  Obtained by calling ncp_task_hdl_create().
*       Once created,   the task handle is supplied as a parameter to all other TaskIO APIs
*/
typedef void  * ncp_task_hdl_t;


#define NCP_TASK_PARAM_SIZE_BYTES         32

/*!
* @brief NCP Task IO Receive buffer:   Tasks received using the ncp_task_recv() API function are presented to
*        the application in a buffer containing a data structure of this type.
*/
typedef struct ncp_task_recv_buf_s
{
#ifdef NCP_BIG_ENDIAN
ncp_uint32_t            dataOffset;             /*!< Word 0: offset of received task data           */
unsigned                reserved3       :14;    /*!< Word 1: reserved                               */
unsigned                launchId        :18;    /*!< The ID of the lauching engine                  */
unsigned                traceEn         :1;     /*!< Word 2: debug bit to enable task tracing       */
unsigned                taskPrio        :3;     /*!< The priority of this task                      */
unsigned                TOID            :12;    /*!< The task order ID associated with this task    */
unsigned                dataSz          :16;    /*!< The number of bytes of data in the received task */
unsigned                QID             :8;     /*!< Word 3: The ID of the NCA Queue this task was sent to */
unsigned                templateId      :8;     /*!< The template ID associated with this task      */
unsigned                taskErr         :1;     /*!< Task Error Status - general                    */
unsigned                bufferSizeErr   :1;     /*!< Task Buffer Error Status - failure due to buffer error */
unsigned                bufferSize      :2;     /*!< The logical buffer size indicator 00..11 for sizes 0..3 */
unsigned                debugFieldV     :2;     /*!< 00-None, 01-Debug For trace, 10-Debug For Performance, 11-reserved */
unsigned                destId_9_0      :10;    /*!< The task destination instance ID, bits 0..9 */
ncp_uint8_t             parms[NCP_TASK_PARAM_SIZE_BYTES]; /*< Word 4..11: Task parameters */
#else
ncp_uint32_t            dataOffset;             /*!< Word 0: virtual address of received task data  */
unsigned                launchId        :18;    /*!< Word 1: The ID of the lauching engine          */
unsigned                reserved        :14;    /*!< reserved                                       */
unsigned                dataSz          :16;    /*!< Word 2: The number of bytes of data in the received task */
unsigned                TOID            :12;    /*!< The task order ID associated with this task    */
unsigned                taskPrio        :3;     /*!< The priority of this task                      */
unsigned                traceEn         :1;     /*!< debug bit to enable task tracing               */
unsigned                destId_9_0      :10;    /*!< Word 3:The task destination instance ID, bits 0..9      */
unsigned                debugFieldV     :2;     /*!< 00-None, 01-Debug For trace, 10-Debug For Performance, 11-reserved */
unsigned                bufferSize      :2;     /*!< The logical buffer size indicator 00..11 for sizes 0..3 */
unsigned                bufferSizeErr   :1;     /*!< Task Buffer Error Status - failure due to buffer error */
unsigned                taskErr         :1;     /*!< Task Error Status - general                    */
unsigned                templateId      :8;     /*!< The template ID associated with this task      */
unsigned                QID             :8;     /*!< The ID of the NCA Queue this task was sent to  */
ncp_uint8_t             parms[NCP_TASK_PARAM_SIZE_BYTES]; /*< Word 4..11: Task parameters */
#endif
} ncp_task_recv_buf_t;

/*!
* @brief NCP Task Send Meta Data:   populated by the application and supplied to the ncp_task_send()
*                                   or ncp_task_send_segments() APIs when transmitting a task.
*
*/
typedef struct ncp_task_send_meta_s
{
#ifdef NCP_BIG_ENDIAN
unsigned    reserved0           :8;     /*!< Word 0: reserved   */
unsigned    flowId              :24;    /*!< The FLOWID associated with this task transmission */
unsigned    reserved1           :1;     /*!< Word 1: reserved   */
unsigned    reserved2           :1;     /*!< reserved           */
unsigned    priority            :3;     /*!< The priority associated with this task */
unsigned    reserved3           :2;     /*!< reserved           */
unsigned    debugFieldV         :1;     /*!< debug/trace enabled */
unsigned    debugData           :24;    /*!< 3 bytes of debug data, valid if debugFieldV above is 01 or 10 */
unsigned    dataSize            :16;    /*!< Word 2: size in bytes of task payload */
unsigned    reserved4           :4;     /*!< reserved           */
unsigned    reserved5           :1;     /*!< reserved           */
unsigned    reserved6           :5;     /*!< reserved           */
unsigned    reserved7           :6;     /*!< reserved           */
unsigned    reserved8           :32;    /*!< Word 3: reserved   */
ncp_uint8_t taskParms[NCP_TASK_PARAM_SIZE_BYTES];  /*!< Word 4...11: The task parameters associated with this task */
ncp_uint32_t reserved9_12       [4];    /*!< Word 12-15: reserved */
#else
unsigned    flowId              :24;    /*!< Word 0: The FLOWID associated with this task transmission */
unsigned    reserved0           :8;     /*!< reserved           */
unsigned    debugData           :24;    /*!< 3 bytes of debug data, valid if debugFieldV below is 01 or 10 */
unsigned    debugFieldV         :1;     /*!< 00-No debug, 01-Debug field for tracing, 10-debug field for performance, 11-reserved */
unsigned    reserved3           :2;     /*!< reserved           */
unsigned    priority            :3;     /*!< The priority associated with this task */
unsigned    reserved2           :1;     /*!< reserved           */
unsigned    reserved1           :1;     /*!< reserved           */
unsigned    reserved7           :6;     /*!< Word 2: reserved   */
unsigned    reserved6           :5;     /*!< reserved           */
unsigned    reserved5           :1;     /*!< reserved           */
unsigned    reserved4           :4;     /*!< reserved           */
unsigned    dataSize            :16;    /*!< size in bytes of task payload */
unsigned    reserved8           :32;    /*!< Word 3: reserved           */
ncp_uint8_t taskParms[NCP_TASK_PARAM_SIZE_BYTES]; /*!< Word 4...11: The task parameters associated with this task */
ncp_uint32_t reserved9_12       [4];    /*!< Word 12-15: reserved */
#endif
} ncp_task_send_meta_t;

/*!
* @brief NCP Task Send Gather-Mode DMA Descriptor Field:   populated by the application and supplied to the
*                                                          ncp_task_send_segments() APIs when transmitting non-contiguous task
*                                                          using gather-mode DMA. The NCA supports gather-mode DMA of up to 16
*                                                          non-contiguous segments,   and the application allocates a table of
*                                                          the desired number of descriptor fields such that there is one descriptor
*                                                          field per segment to be transmitted.
*/
typedef struct ncp_task_segment_entry_s
{
ncp_uint16_t   size;     /*!< The size in bytes of this gather mode segment */
void           *addr;    /*!< The virtual address of this gather mode segment */
} ncp_task_segment_entry_t;


/*!
* @brief Global statistics maintained by the Task I/O modules:   supplied to the ncp_task_get_stats() API to
*        to retrieve the task statistics from the Task I/O module.
*/
typedef struct ncp_task_stats_s
{
/* Task Stats - SUCCESS */
ncp_uint32_t stat_RxTaskDispatched;             /*!< The total number of tasks successfully received using dispatch receive mode */
ncp_uint32_t stat_RxTaskDirect;                 /*!< The total number of tasks successfully tasks received using direct receive mode */
ncp_uint32_t stat_TxTask;                       /*!< The total number of tasks successfully transmitted */
ncp_uint32_t stat_TxTaskSegments;               /*!< The total number of tasks successfully transmitted using gather-mode DMA */
ncp_uint32_t stat_TxTaskComp;                   /*!< The total number of task completions   successfully transmitted */
/* Task Stats - FAILURE */
ncp_uint32_t stat_RxDroppedNoBind;              /*!< The total number of tasks received and discarded due to no active VP binding */
ncp_uint32_t stat_RxDroppedTaskErr;             /*!< The total number of tasks received and discarded due to a generic task error */
ncp_uint32_t stat_RxDroppedBufferSizeErr;       /*!< The total number of tasks received and discarded due to a buffer size error */

/* Queue State Statistics */
ncp_uint32_t stat_RxQueueEmpty;                 /*!< Number of times Rx Queue was empty - wait for irq */
ncp_uint32_t stat_RxQueueNotEmpty;              /*!< Number of times Rx Queue was not empty */
ncp_uint32_t stat_TxQueueFull;                  /*!< Number of times Tx Queue was full - wait for irq */
ncp_uint32_t stat_TxQueueNotFull;               /*!< Number of times Tx Queue was not full */
ncp_uint32_t stat_CompQueueFull;                /*!< Number of times Comp Queue was full - wait for irq */
ncp_uint32_t stat_CompQueueNotFull;             /*!< Number of times Comp Queue was not full */

/* API Stats - SUCCESS  */
ncp_uint32_t stat_api_task_hdl_create_ok;       /*!< The total number of successful API invocations */
ncp_uint32_t stat_api_task_hdl_remove_ok;       /*!< The total number of successful API invocations */
ncp_uint32_t stat_api_recv_queue_bind_ok;       /*!< The total number of successful API invocations */
ncp_uint32_t stat_api_recv_queue_unbind_ok;     /*!< The total number of successful API invocations */
ncp_uint32_t stat_api_recv_queue_vp_bind_ok;    /*!< The total number of successful API invocations */
ncp_uint32_t stat_api_recv_queue_vp_unbind_ok;  /*!< The total number of successful API invocations */
ncp_uint32_t stat_api_recv_ok;                  /*!< The total number of successful API invocations */
ncp_uint32_t stat_api_recv_done_ok;             /*!< The total number of successful API invocations */
ncp_uint32_t stat_api_send_ok;                  /*!< The total number of successful API invocations */
ncp_uint32_t stat_api_send_segments_ok;         /*!< The total number of successful API invocations */
ncp_uint32_t stat_api_task_buffer_alloc_ok;     /*!< The total number of successful API invocations */
ncp_uint32_t stat_api_task_buffer_free_ok;      /*!< The total number of successful API invocations */
ncp_uint32_t stat_api_send_mutex_disable_ok;    /*!< The total number of successful API invocations */
/* API Stats - FAILURE  */
ncp_uint32_t stat_api_task_hdl_create_err;      /*!< The total number of API invocations that failed due to error(s) */
ncp_uint32_t stat_api_task_hdl_remove_err;      /*!< The total number of API invocations that failed due to error(s) */
ncp_uint32_t stat_api_recv_queue_bind_err;      /*!< The total number of API invocations that failed due to error(s) */
ncp_uint32_t stat_api_recv_queue_unbind_err;    /*!< The total number of API invocations that failed due to error(s) */
ncp_uint32_t stat_api_recv_queue_vp_bind_err;   /*!< The total number of API invocations that failed due to error(s) */
ncp_uint32_t stat_api_recv_queue_vp_unbind_err; /*!< The total number of API invocations that failed due to error(s) */
ncp_uint32_t stat_api_recv_err;                 /*!< The total number of API invocations that failed due to error(s) */
ncp_uint32_t stat_api_recv_done_err;            /*!< The total number of API invocations that failed due to error(s) */
ncp_uint32_t stat_api_send_err;                 /*!< The total number of API invocations that failed due to error(s) */
ncp_uint32_t stat_api_send_segments_err;        /*!< The total number of API invocations that failed due to error(s) */
ncp_uint32_t stat_api_task_buffer_alloc_err;    /*!< The total number of API invocations that failed due to error(s) */
ncp_uint32_t stat_api_task_buffer_free_err;     /*!< The total number of API invocations that failed due to error(s) */
ncp_uint32_t stat_api_send_mutex_disable_err;   /*!< The total number of API invocations that failed due to error(s) */
/* User Mode Buffer Pool Statistics */
ncp_uint32_t stat_upool_sz0_buffers_total;      /*!< The total number of size0 buffers in user mode pool */
ncp_uint32_t stat_upool_sz1_buffers_total;      /*!< The total number of size1 buffers in user mode pool */
ncp_uint32_t stat_upool_sz2_buffers_total;      /*!< The total number of size2 buffers in user mode pool */
ncp_uint32_t stat_upool_sz3_buffers_total;      /*!< The total number of size3 buffers in user mode pool */
ncp_uint32_t stat_upool_sz0_buffers_free;       /*!< The current number of free size0 buffers in user mode pool */
ncp_uint32_t stat_upool_sz1_buffers_free;       /*!< The current number of free size1 buffers in user mode pool */
ncp_uint32_t stat_upool_sz2_buffers_free;       /*!< The current number of free size2 buffers in user mode pool */
ncp_uint32_t stat_upool_sz3_buffers_free;       /*!< The current number of free size3 buffers in user mode pool */
ncp_uint32_t stat_upool_sz0_buffers_low_water;  /*!< The lowest number of free size0 buffers in user mode pool */
ncp_uint32_t stat_upool_sz1_buffers_low_water;  /*!< The lowest number of free size1 buffers in user mode pool */
ncp_uint32_t stat_upool_sz2_buffers_low_water;  /*!< The lowest number of free size2 buffers in user mode pool */
ncp_uint32_t stat_upool_sz3_buffers_low_water;  /*!< The lowest number of free size3 buffers in user mode pool */
/* Kernel Mode Buffer Pool Statistics */
ncp_uint32_t stat_kpool_sz0_buffers_total;      /*!< The total number of size0 buffers in kernel mode pool */
ncp_uint32_t stat_kpool_sz1_buffers_total;      /*!< The total number of size1 buffers in kernel mode pool */
ncp_uint32_t stat_kpool_sz2_buffers_total;      /*!< The total number of size2 buffers in kernel mode pool */
ncp_uint32_t stat_kpool_sz3_buffers_total;      /*!< The total number of size3 buffers in kernel mode pool */
ncp_uint32_t stat_kpool_sz0_buffers_free;       /*!< The current number of free size0 buffers in kernel mode pool */
ncp_uint32_t stat_kpool_sz1_buffers_free;       /*!< The current number of free size1 buffers in kernel mode pool */
ncp_uint32_t stat_kpool_sz2_buffers_free;       /*!< The current number of free size2 buffers in kernel mode pool */
ncp_uint32_t stat_kpool_sz3_buffers_free;       /*!< The current number of free size3 buffers in kernel mode pool */
ncp_uint32_t stat_kpool_sz0_buffers_low_water;  /*!< The lowest number of free size0 buffers in kernel mode pool */
ncp_uint32_t stat_kpool_sz1_buffers_low_water;  /*!< The lowest number of free size1 buffers in kernel mode pool */
ncp_uint32_t stat_kpool_sz2_buffers_low_water;  /*!< The lowest number of free size2 buffers in kernel mode pool */
ncp_uint32_t stat_kpool_sz3_buffers_low_water;  /*!< The lowest number of free size3 buffers in kernel mode pool */
} ncp_task_stats_t;


/*
* This data structure must match the ncaV2 opcq deallocate immediate
*/

typedef struct ncp_ncaV2_free_pdu_segments_s
{
#ifdef NCP_BIG_ENDIAN
unsigned reserved0          :3;    /* Word 0 - 3b100 */
unsigned reserved1          :1;
unsigned reserved2          :28;

unsigned reserved3          :2;    /* Word 1 */
unsigned reserved4          :2;
unsigned reserved5          :2;
unsigned reserved6          :2;
unsigned reserved7          :2;
unsigned reserved8          :2;
unsigned reserved9          :9;
unsigned ptrCnt             :3;
unsigned reserved10         :2;
unsigned reserved11         :6;    /* hidden - poolID */

ncp_uint64_t pduSegAddr0       ;     /* Word 2-3 */
ncp_uint64_t pduSegAddr1       ;     /* Word 4-5 */
ncp_uint64_t pduSegAddr2       ;     /* Word 6-7 */
ncp_uint64_t pduSegAddr3       ;     /* Word 8-9 */
ncp_uint64_t pduSegAddr4       ;     /* Word 10-11 */
ncp_uint64_t pduSegAddr5       ;     /* Word 12-13 */
ncp_uint32_t pad[2]            ;     /* Words 14..15 */
#else
unsigned reserved2          :28;     /* Word 0 - 3b100 */
unsigned reserved1          :1;
unsigned reserved0          :3;

unsigned reserved11         :6;     /* Word 1 */ /* hidden - poolID */
unsigned reserved10         :2;
unsigned ptrCnt             :3;
unsigned reserved9          :9;
unsigned reserved8          :2;
unsigned reserved7          :2;
unsigned reserved6          :2;
unsigned reserved5          :2;
unsigned reserved4          :2;
unsigned reserved3          :2;


ncp_uint64_t pduSegAddr0       ;     /* Word 2-3 */
ncp_uint64_t pduSegAddr1       ;     /* Word 4-5 */
ncp_uint64_t pduSegAddr2       ;     /* Word 6-7 */
ncp_uint64_t pduSegAddr3       ;     /* Word 8-9 */
ncp_uint64_t pduSegAddr4       ;     /* Word 10-11 */
ncp_uint64_t pduSegAddr5       ;     /* Word 12-13 */
ncp_uint32_t pad[2]            ;     /* Words 14..15 */
#endif
} ncp_ncaV2_free_pdu_segments_t;
/*
* Matches ncaV2 input task header
*/

typedef struct ncp_task_ncaV2_recv_buf_s
{
#ifdef NCP_BIG_ENDIAN
unsigned templateID         :8;     /* Word 0 */
unsigned QID                :8;
unsigned pduSize            :16;

unsigned reserved0          :6;     /* Word 1 */
unsigned dstID_9_0          :10;
unsigned reserved1          :1;
unsigned priority           :3;
unsigned TOID               :12;

unsigned char params[32];           /* Words 2..9 */

unsigned pduBlockSz0        :2;     /* Word 10 */
unsigned pduBlockSz1        :2;
unsigned pduBlockSz2        :2;
unsigned pduBlockSz3        :2;
unsigned pduBlockSz4        :2;
unsigned pduBlockSz5        :2;
unsigned reserved2          :2;
unsigned debug              :2;
unsigned reserved3          :5;
unsigned ptrCnt             :3;
unsigned reserved4          :2;
unsigned poolID             :6;

unsigned pduSegSize0        :16;     /* Word 11 */
unsigned pduSegSize1        :16;

ncp_uint64_t pduSegAddr0       ;     /* Word 12-13 */

ncp_uint64_t pduSegAddr1       ;     /* Word 14-15 */

unsigned pduSegSize2        :16;     /* Word 16 */
unsigned pduSegSize3        :16;

unsigned pduSegSize4        :16;     /* Word 17 */
unsigned pduSegSize5        :16;

ncp_uint64_t pduSegAddr2       ;     /* Word 18-19 */

ncp_uint64_t pduSegAddr3       ;     /* Word 20-21 */

ncp_uint64_t pduSegAddr4       ;     /* Word 22-23 */

ncp_uint64_t pduSegAddr5       ;     /* Word 24-25 */

unsigned debugDataWord0     :32;     /* Word 26 */

unsigned debugDataWord1     :32;     /* Word 27 */
#else
unsigned pduSize            :16;     /* Word 0 */
unsigned QID                :8;
unsigned templateID         :8;

unsigned TOID               :12;     /* Word 1 */
unsigned priority           :3;
unsigned reserved1          :1;
unsigned dstID_9_0          :10;
unsigned reserved0          :6;

unsigned char params[32];           /* Words 2..9 */

unsigned poolID             :6;     /* Word 10 */
unsigned reserved4          :2;
unsigned ptrCnt             :3;
unsigned reserved3          :5;
unsigned debug              :2;
unsigned reserved2          :2;
unsigned pduBlockSz5        :2;
unsigned pduBlockSz4        :2;
unsigned pduBlockSz3        :2;
unsigned pduBlockSz2        :2;
unsigned pduBlockSz1        :2;
unsigned pduBlockSz0        :2;

unsigned pduSegSize1        :16;     /* Word 11 */
unsigned pduSegSize0        :16;

ncp_uint64_t pduSegAddr0       ;     /* Word 12-13 */

ncp_uint64_t pduSegAddr1       ;     /* Word 14-15 */

unsigned pduSegSize3        :16;     /* Word 16 */
unsigned pduSegSize2        :16;

unsigned pduSegSize5        :16;     /* Word 17 */
unsigned pduSegSize4        :16;

ncp_uint64_t pduSegAddr2       ;     /* Word 18-19 */

ncp_uint64_t pduSegAddr3       ;     /* Word 20-21 */

ncp_uint64_t pduSegAddr4       ;     /* Word 22-23 */

ncp_uint64_t pduSegAddr5       ;     /* Word 24-25 */

unsigned debugDataWord0     :32;     /* Word 26 */

unsigned debugDataWord1     :32;     /* Word 27 */

#endif
} ncp_task_ncaV2_recv_buf_t;

/*
* Matches concatenated ncaV2 OPCQ entry & extension
*/

typedef struct ncp_task_ncaV2_send_meta_s
{
#ifdef NCP_BIG_ENDIAN
unsigned cmdCode             :3;     /* Word 0 - 3b001*/
unsigned interruptOnComplete :1;
unsigned setTaskErr          :1;
unsigned debugFieldV         :1;
unsigned packetCtrl_forceCopy                :1;
unsigned packetCtrl_returnBuffToMMEafterCopy :1;
unsigned flowDataIndex       :24;

unsigned virtualFlowID       :8;    /* Word 1 */
unsigned debugData           :24;

unsigned char params[32]       ;    /* Words 2..9 */

unsigned pduBlockSz0        :2;     /* Word 10 */
unsigned pduBlockSz1        :2;
unsigned pduBlockSz2        :2;
unsigned pduBlockSz3        :2;
unsigned pduBlockSz4        :2;
unsigned pduBlockSz5        :2;
unsigned reserved2          :1;
unsigned priority           :3;
unsigned reserved3          :5;
unsigned ptrCnt             :3;
unsigned reserved4          :2;
unsigned poolID             :6;

unsigned pduSegSize0        :16;    /* Word 11 */
unsigned pduSegSize1        :16;

ncp_uint64_t pduSegAddr0       ;    /* Word 12-13 */

ncp_uint64_t pduSegAddr1       ;    /* Word 14-15 */

/* ----------------------- */

unsigned cmdCodeExt          :3;    /* Word 0 - 3b010 */
unsigned reserved0          :29;

unsigned reserved1          :32;    /* Word 1 */

unsigned pduSegSize2        :16;     /* Word 2 */
unsigned pduSegSize3        :16;

unsigned pduSegSize4        :16;     /* Word 3 */
unsigned pduSegSize5        :16;

ncp_uint64_t pduSegAddr2       ;     /* Word 4-5 */

ncp_uint64_t pduSegAddr3       ;     /* Word 6-7 */

ncp_uint64_t pduSegAddr4       ;     /* Word 8-9 */

ncp_uint64_t pduSegAddr5       ;     /* Word 10-11 */

ncp_uint32_t    pad[4]         ;     /* Words 12-15 */

#else

unsigned flowDataIndex       :24;   /* Word 0 - 3b001*/
unsigned packetCtrl_returnBuffToMMEafterCopy :1;
unsigned packetCtrl_forceCopy                :1;
unsigned debugFieldV         :1;
unsigned setTaskErr          :1;
unsigned interruptOnComplete :1;
unsigned cmdCode             :3;


unsigned debugData           :24;   /* Word 1 */
unsigned virtualFlowID       :8;

unsigned char params[32]       ;    /* Words 2..9 */

unsigned poolID             :6;     /* Word 10 */
unsigned reserved4          :2;
unsigned ptrCnt             :3;
unsigned reserved3          :5;
unsigned priority           :3;
unsigned reserved2          :1;
unsigned pduBlockSz5        :2;
unsigned pduBlockSz4        :2;
unsigned pduBlockSz3        :2;
unsigned pduBlockSz2        :2;
unsigned pduBlockSz1        :2;
unsigned pduBlockSz0        :2;


unsigned pduSegSize1        :16;    /* Word 11 */
unsigned pduSegSize0        :16;


ncp_uint64_t pduSegAddr0       ;    /* Word 12-13 */

ncp_uint64_t pduSegAddr1       ;    /* Word 14-15 */

/* ----------------------- */

unsigned reserved0          :29;    /* Word 0 - 3b010 */
unsigned cmdCodeExt          :3;

unsigned reserved1          :32;    /* Word 1 */

unsigned pduSegSize3        :16;    /* Word 2 */
unsigned pduSegSize2        :16;

unsigned pduSegSize5        :16;    /* Word 3 */
unsigned pduSegSize4        :16;

ncp_uint64_t pduSegAddr2       ;     /* Word 4-5 */

ncp_uint64_t pduSegAddr3       ;     /* Word 6-7 */

ncp_uint64_t pduSegAddr4       ;     /* Word 8-9 */

ncp_uint64_t pduSegAddr5       ;     /* Word 10-11 */

ncp_uint32_t    pad[4]         ;     /* Words 12-15 */

#endif

} ncp_task_ncaV2_send_meta_t;

/* ============================================================================================================
* BEGIN Common APIs.   These APIs are common across both NCA V1 and NCA V2 hardware.
* ============================================================================================================
*/



/*!
* @fn ncp_st_t ncp_task_get_default_queueset(ncp_hdl_t    ncpHdl,
*                                            ncp_uint8_t  pThreadQueueSetId);
*
* @brief This API returns the ID of the 1st thread local queueset managed by the local domain.
*        Is is intended for internal RTE use during config.
*
* @param[in]       ncpHdl:  NCP handle returned by previous call to ncp_config
* @param[out]      pThreadQueueSetId: The linear ID (0..11) of the Thread Queue Set
*
* @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
* @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
* @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down dur to config_destroy
* @retval NCP_ST_TASK_NO_QUEUESET_IN_DOMAIN At least one task queue set must be defined for every management domain
*/

NCP_API ncp_st_t
ncp_task_get_default_queueset(
ncp_hdl_t       ncpHdl,
ncp_uint8_t     *pThreadQueueSetId);

/*!
* @fn ncp_st_t ncp_task_hdl_create(ncp_hdl_t ncpHdl,
*                                  ncp_uint8_t     threadQueueSetId,
*                                  ncp_bool_t      shared,
*                                  ncp_bool_t      orderedTaskCompletion,
*                                  ncp_task_hdl_t  *taskHdl);
*
* @brief This API creates a thread-local task handle,   and must be the first Task I/O API issued by the application thread.
*        The handle returned is used in all subsequent calls to Task I/O APIs.
*        Task handles are thread-local,   and must not be shared among other threads in a process.
*        Requiring task handles to be thread-local greatly improves performance since serial access is guaranteed;   thus, eliminating
*        the need for a mutex.

* @param[in]       ncpHdl:  NCP handle returned by previous call to ncp_config
* @param[in]       threadQueueSetId: The linear ID (0..11) of the Thread Queue Set
* @param[in]       shared: if TRUE,   then the output type queues in the Thread Queue Set are shared,
*                  otherwise they are reserved for exclusive use.   Note that input queues can never be shared.
* @param[in]       orderedTaskCompletion: If TRUE,   then TaskIO module will perform output related maintenance operations
*                  on the task completion PCQ,   otherwise no maintenance operations will be performed.
* @param[in,out]   taskHdl: On success, the task handle is returned here.
*
* @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
* @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
* @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down dur to config_destroy
* @retval NCP_ST_TASK_NO_MALLOC_MEM insufficient memory resources to satisfy request
*/

NCP_API ncp_st_t
ncp_task_hdl_create(
ncp_hdl_t       ncpHdl,
ncp_uint8_t     threadQueueSetId,
ncp_bool_t      shared,
ncp_bool_t      orderedTaskCompletion,
ncp_task_hdl_t  *taskHdl);

/*!
* @fn ncp_st_t ncp_task_hdl_remove(ncp_task_hdl_t taskHdl);
* @brief This API removes the specified task handle from service. All resources associated with the specified task
*        handle are freed. Note that all associated pipelines and receive queues must be specifically unbound prior to
*        calling this function.   Failure to call this function prior to thread termination will result in a memory leak.
*
* @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
*
* @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
* @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy
* @retval NCP_ST_TASK_INVALID_TASK_HANDLE The taskHdl parameter is not valid
* @retval NCP_ST_HANDLE_IN_USE cannot remove taskHdl until queues and VPs unbound
* @retval NCP_ST_TASK_QUESET_NOT_IN_LOCAL_DOMAIN The Thread Queue Set ID supplied references a queueset owned by another AMP domain.
*/
NCP_API ncp_st_t
ncp_task_hdl_remove(
ncp_task_hdl_t  taskHdl);

/*!
* @fn ncp_st_t ncp_task_send_mutex_disable( ncp_task_hdl_t taskHdl)
* @brief This API can be used to disable mutex operations associated with sharing a queueset.
* See the RTE user's guide for the specific scenario where this function can be used.  If used incorrectly,
* corruption will be almost certain,   so care must be taken.
*
* @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
*
*/
NCP_API ncp_st_t
ncp_task_send_mutex_disable(
ncp_task_hdl_t taskHdl);

/*!
* @fn ncp_st_t ncp_task_recv_queue_bind(	ncp_task_hdl_t taskHdl,
*                                      	ncp_uint8_t ncaQueueId,
*                                      	ncp_uint8_t weight,
*                                      	ncp_bool_t shared,
*                               	ncp_bool_t fixedRecvQueueId,
*                                      	ncp_uint8_t *recvQueueId)
*
* @brief   This API binds the specified receive handle to the specified NCA task input queue. Upon success a receive queue ID is
*          returned that can be used in later ncp_task_recv_queue_vp_bind calls to specify the various pipelines that the caller is
*          interested in receiving from.
*          Only exclusive bindings are supported for NCA receive queues.
*          An exclusive binding allows a single process to bind directly to an NCA task input queue. This type of binding
*          provides maximum efficiency in the case of a single process application model. In this case the ncp_task_recv function
*          services the NCA task input queue directly.
*          Multiple receive queue bindings can be created by calling this function multiple times with a unique ncaReceiveQueueId specified
*          in each call. When a receive handle contains multiple receive queue bindings the ncp_task_recv function services each queue
*          using a weighted round robin (WRR) scheduling arbitration policy.
*          Receive queue bindings can be created and removed dynamically throughout the life of the system.

* @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
* @param[in] ncaQueueId: Specifies the NCA task input queue association for this receive queue.
* @param[in] weight: Specifies the WRR scheduling arbitration weight to use for this receive queue.
* @param[in] shared: This parameter must be set to FALSE.   Sharing receive queues is not supported.
* @param[in] fixedRecvQueueId:  If set to TRUE, to use the receive queue ID pointed to by recvQueueId. If set to FALSE,
*                           dynamically allocate the receive queue ID and return it in the location pointed to by recvQueueId. Note that
*                           the 8-bit receive queue ID space is partitioned into two equal ranges. The 0-127 range is reserved for
*                           dynamically allocated IDs and the 128-255 range is reserved for fixed (user managed) IDs. For additional
*                           information see ncp_task_recv_queue_vp_bind.
* @param[in,out] recvQueueId: Pointer to the receive queue ID. On success, the unique ID associated with this receive queue is stored in
*                this location.
*
* @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
* @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy
* @retval NCP_ST_TASK_INVALID_TASK_HANDLE The taskHdl parameter is not valid
* @retval NCP_ST_TASK_SHARED_RECEIVE_QUEUES_NOT_SUPPORTED Shared binding to receive queues is no longer supported
* @retval NCP_ST_TASK_NO_MALLOC_MEM    A request for memory allocation could not be satisfied due to insufficient resources.
* @retval NCP_ST_TASK_NULL_RECVQUEUEID_PTR the recvQueueId pointer is NULL
* @retval NCP_ST_TASK_INVALID_NCA_INPUT_QUEUE queue ID exceeds upper limit
* @retval NCP_ST_TASK_INVALID_FIXED_QUEUEID fixed queue IDs must be in the rang 128..255
* @retval NCP_ST_TASK_QMAP_ERR_TOO_BIG queue ID exceeds the upper limit
* @retval NCP_ST_TASK_NULL_PCQ_PRODUCER_PTR internal error
* @retval NCP_ST_TASK_NULL_PCQ_CONSUMER_PTR  internal error
* @retval NCP_ST_TASK_SHARED_VP_BINDING_NOT_AVAIL A request to bind to a VP in exclusive mode failed due to the NCA queue or VP already being bound for shared access
* @retval NCP_ST_TASK_EXCLUSIVE_BINDING_NOT_AVAIL resource to bind is already in use
* @retval NCP_ST_TASK_RECEIVE_QUEUES_MUST_HAVE_SAME_SHARE_PERMISSION All receive queues used by a thread must have same share permission, either all exclusive,  or all shared.
* @retval NCP_ST_TASK_RECV_ACCESS_MODE_NOT_SAME_AS_QUEUESET If the ncp_task_hdl_create API was used to open a queueset in exclusive mode, all assoiated receive queues must be bound in exclusive mode too.
* @retval NCP_ST_TASK_NULL_RECV_QUEUE_PTR invalid receive queue pointer encountered
* @retval NCP_ST_TASK_NULL_TASK_QUEUE_PTR invalid task queue pointer encountered
* @retval NCP_ST_TASK_NO_SWQUEUE_MEM insufficient memory available to create software queue
*/

NCP_API ncp_st_t
ncp_task_recv_queue_bind(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t ncaQueueId,
	ncp_uint8_t weight,
	ncp_bool_t shared,
	ncp_bool_t fixedRecvQueueId,
	ncp_uint8_t *recvQueueId);

/*!
* @fn ncp_st_t ncp_task_recv_queue_unbind(ncp_task_hdl_t taskHdl,
*                                         ncp_uint8_t recvQueueId);
* @brief This API removes the specified receive queue binding from service. All resources associated with the receive
*        queue itself are freed. Note that all VP bindings associated with this receive queue binding must be removed prior
*        to calling this function.
*
* @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
* @param[in] recvQueueId:  Receive queue ID returned from previous call to ncp_task_recv_queue_bind.
*
* @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
* @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy
* @retval NCP_ST_TASK_INVALID_TASK_HANDLE  The taskHdl parameter is not valid
* @NCP_ST_TASK_RECEIVE_HANDLE_HEAD_NULL No receive queues are currently bound for this task handle
* @retval NCP_ST_TASK_INVALID_RECEIVE_QUEUE software queue ID is not currently bound
* @retval NCP_ST_TASK_RECEIVE_QUEUE_NOT_FOUND The specified receive queue was not found in the list of receive queues associated with this task handle.
*/

NCP_API ncp_st_t
ncp_task_recv_queue_unbind(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t recvQueueId);


/*!
* @brief NCP Task IO Receive Dispatch Callback:
*       describes the function that is called when the ncp_task_receive() API is called and
*       the virtual pipeline associated with the current received task was bound by calling the ncp_task_recv_queue_vp_bind() API with a
*       non NULL  recvFunc parameter.
*/
typedef ncp_st_t (*ncp_task_recv_fn_t)(
	ncp_uint8_t recvQueueId,        /*!< The receive queue ID associated with this task,  as returned in the ncp_task_recv_queue_bind API */
	ncp_vp_hdl_t vpHdl,             /*!< The VP (virtual pipeline) handle associated with the received task */
	ncp_uint8_t engineSequenceId,	/* The engine sequeunce ID associated with the received task */
	void *recvFuncArg,              /* The argument provided by the application to the ncp_task_recv_queue_vp_bind() API for this VP bind */
	void *task,                     /* Virtual address of task is returned here.
	                                 * Note: legacy ncp_task_recv API returns ncaV1 header,  otherwise ncaV2
	                                 */
	void                *taskData); /* Virtual address of task Data is returned here        */


/*!
*  @fn ncp_st_t ncp_task_recv_queue_vp_bind(ncp_task_hdl_t taskHdl,
*	                                    ncp_uint8_t recvQueueId,
*	                                    ncp_vp_hdl_t vpHdl,
*	                                    ncp_uint8_t engineSequenceId,
*	                                    ncp_bool_t shared,
*	                                    ncp_task_recv_fn_t recvFunc,
*	                                    void *recvFuncArg);
* @brief   This API creates a binding between the specified receive queue and the specified virtual pipeline (VP). This is called a VP
*          level binding. Multiple VP level bindings can be created by calling this function multiple times with a unique {vpHdl,
*          engineSequenceId} pair specified in each call.
*          Two types of VP level bindings are supported: shared and exclusive. An exclusive VP level binding allows a single process to
*          receive all tasks from the specified VP.
*          A shared VP level binding allows multiple processes,  or threads,   to receive tasks from the same VP. Note that a shared VP
*          level binding can only be made (and only makes sense) when the associated NCA queue binding is shared. In this case a two-tuple
*          binding is created such that the calling process will only receive tasks that are from the specified VP and that are tagged with
*          the specified receive queue ID. Note that two ranges of receive queue IDs are supported: dynamic and fixed (see
*          ncp_recv_queue_create).
*          Dynamic receive queue IDs are provided for the cases where either: the process does not use any shared VPs (tasks for these VPs
*          are not tagged with a receive queue ID), or where the shared VPs are only used for direct peer-to-peer communication. For
*          example, a single shared VP could be used for all inter-process communication (IPC). In this case each process creates a shared
*          receive queue binding and lets the ncp_task_recv_queue_bind call allocate a unique receive queue ID. Each process then creates a
*          shared binding to the IPC VP and advertises the unique {NCA queue ID, receive queue ID} pair that they are listening on. Now
*          to communicate with some process the sender creates a task, tags the task with the target processes advertised receive queue ID,
*          and sends the task to the processes advertised NCA queue. Note that in this case the only requirement for the per-process receive
*          queue ID is that it be unique for all IPC processes that are listening on the same NCA queue.
*          Fixed receive queue IDs are provided for the case where one or more shared VPs are used for communication with “replicated”
*          processes. For example, a shared VP could be used to send work to any one of several instances (one per CPU) of the same
*          process. Note that a logical NCA task input queue group must be established to allow the NCA to load balance and order (if
*          needed) tasks that are sent to the replicated process. In this case each replicated process creates a shared receive queue
*          binding to one of the NCA queues in the logical NCA queue group and instructs the ncp_task_recv_queue_bind API to use a fixed
*          (identical for all process instances) receive queue ID. Each replicated process then creates a shared binding to and listens on
*          the shared VP. Now to send work to one of the replicated processes the sender creates a task, tags the task with the well known
*          receive queue ID, and sends the task to the logical NCA queue ID. Note that in this case the NCA will choose the real NCA queue
*          ID (based on current load and ordering constraints) but the receive queue ID is constant and therefore all replicated processes
*          must be listening on the same receive queue ID.
*          At this time the caller also specifies the task delivery mechanism for this VP level binding. If a task receive function is
*          specified (recvFunc != NULL) then tasks for this binding are dispatched to the specified function, within the context of the
*          ncp_task_recv caller. If a task receive function is not specified (recvFunc == NULL) then tasks for this binding are returned to
*          the ncp_task_recv caller.
*          VP level bindings can be created and removed dynamically throughout the life of the system.
*
* @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
* @param[in] recvQueueId: Specifies the software receive queue ID returned by the API ncp_task_recv_queue_bind (dynamic queue), or the fixed queue ID supplied to the API ncp_task_recv_queue_bind.
* @param[in] vpHdl: Virtual pipeline handle
* @param[in] engineSequenceId: Engine Sequence (Formerly Pipeline) ID
* @param[in] shared:  This parameter must be set to FALSE.   Sharing virtual pipelines is not supported.
* @param[in] recvFunc:  Receive handler function pointer. If not null then incoming tasks will be delivered by receive dispatch mode.
* @param[in] recvFuncArg: If a receive handler is not specified (recvFunc == NULL) then this argument is ignored.
*
* @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
* @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy
* @retval NCP_ST_TASK_INVALID_TASK_HANDLE  The taskHdl parameter is not valid
* @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
* @retval NCP_ST_TASK_INVALID_RECEIVE_QUEUE software queue ID is not currently bound
* @retval NCP_ST_TASK_NO_MEM_L1BIND  insufficient memory available to allocate bind table
* @retval NCP_ST_TASK_EXCLUSIVE_BINDING_NOT_AVAIL resource to bind is already in use
* @retval NCP_ST_TASK_SHARED_PIPELINES_NOT_SUPPORTED Shared bindings to Virtual Pipelines is no longer supported
* @retval NCP_ST_VPM_INVALID_VP_HDL the vpHdl parameter is not valid
* @retval NCP_ST_VPM_ENGINE_SEQUENCE_NOT_FOUND invalid engine sequence
*/
NCP_API ncp_st_t
ncp_task_recv_queue_vp_bind(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t recvQueueId,
	ncp_vp_hdl_t vpHdl,
	ncp_uint8_t engineSequenceId,
	ncp_bool_t shared,
	ncp_task_recv_fn_t recvFunc,
	void *recvFuncArg);

/*!
* @fn ncp_st_t ncp_task_recv_queue_vp_unbind(ncp_task_hdl_t taskHdl,
*                                      	ncp_uint8_t recvQueueId,
*                                          ncp_vp_hdl_t vpHdl,
*                                          ncp_uint8_t engineSequenceId);
* @brief This API removes the specified VP binding from the specified receive queue. All resources associated with
*        the VP binding are freed.
*
* @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
* @param[in] ncaQueueId: Specifies the NCA task input queue ID for this receive queue.
* @param[in] vpHdl: Virtual pipeline handle
* @param[in] engineSequenceId: (Formerly Pipeline) Engine Sequence ID
*
* @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
* @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy
* @retval NCP_ST_TASK_INVALID_TASK_HANDLE  The taskHdl parameter is not valid
* @retval NCP_ST_TASK_INVALID_RECEIVE_QUEUE software queue ID is not currently bound
* @retval NCP_ST_TASK_NULL_L1_BINDP  no binding exists
* @retval NCP_ST_TASK_INVALID_VP_HANDLE  the vpHdl parameter is invalid
* @retval NCP_ST_TASK_INVALID_BIND_TABLE_ENTRY internal error
* @retval NCP_ST_VPM_INVALID_VP_HDL the vpHdl parameter is not valid
* @retval NCP_ST_VPM_ENGINE_SEQUENCE_NOT_FOUND invalid engine sequence
*
*/
NCP_API ncp_st_t
ncp_task_recv_queue_vp_unbind(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t recvQueueId,
	ncp_vp_hdl_t vpHdl,
	ncp_uint8_t engineSequenceId);

/*!
* @fn ncp_st_t ncp_task_send_queue_flush(
*                                      ncp_task_hdl_t taskHdl,
*                                      ncp_bool_t wait,
*                                      ncp_bool_t *pQueueStatus);
* @brief This API is called to test the thread-local software send queue for the empty condition.   If the wait parameter is set to true,
*         then the function will block until all previously queued output tasks have been processed by the task send proxy service (i.e.
*         removed from the software queue and routed to the NCA hardware output queue).
*
* @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
* @param[in] wait: If FALSE,   then return current queue status in queueEmpty,  else wait for queue to drain
* @param[in,out] pQueueEmpty: Pointer to boolean where queue status (0 if empty or,  1 if non-empty) is returned
*
* @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
* @retval NCP_ST_TASK_SHUTDOWN  Task I/O is shutting down due to config_destroy
*/
NCP_API  ncp_st_t
ncp_task_send_queue_flush(
	ncp_task_hdl_t taskHdl,
ncp_bool_t wait,
ncp_bool_t *pQueueEmpty);





/*!
* @fn void ncp_task_reset_stats( ncp_hdl_t ncpHdl )
* @brief This API is called to reset task statistics
*
* @param[in] ncpHdl:  NCP handle returned by previous call to ncp_config.
*
* @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
*/
NCP_API ncp_st_t
ncp_task_reset_stats(	ncp_hdl_t ncpHdl );

/*!
* @fn void ncp_task_get_stats( ncp_hdl_t ncpHdl, ncp_task_stats_t *pStats );
* @brief This API is called to retrieve task statistics
*
* @param[in] ncpHdl:  NCP handle returned by previous call to ncp_config.
* @param[in,out]  pStats: pointer to ncp_task_stats_t structure to receive task statistics
*
* @retval NCP_ST_TASK_NO_GSM  Task I/O Shared Memory Not Initialized
*/
NCP_API ncp_st_t
ncp_task_get_stats(	ncp_hdl_t ncpHdl,
ncp_task_stats_t *pStats);

/*!
* @fn ncp_st_t ncp_nca_bp_dest_val_get(ncp_hdl_t ncpHdl, ncp_uint8_t destBit,
*                                      ncp_bool_t *destVal)
* @brief For a given dest bit, this function returns the NCA backpressure state.
*
* @param[in]  ncpHdl:  NCP API state handle.
* @param[in]  destBit: The bp dest bit that needs to be queried.
*                      Valid values: 0-31
* @param[out] destVal: TRUE - if bp state is on for the given bit.
*                      FALSE - if bp state is off for the given bit.
*/
NCP_API ncp_st_t
ncp_nca_bp_dest_val_get(ncp_hdl_t ncpHdl, ncp_uint8_t destBit,
ncp_bool_t *destVal);

/*!
* @fn ncp_st_t ncp_nca_bp_state_get(ncp_hdl_t ncpHdl, ncp_uint32_t *bpState)
*
* @brief This API returns the NCA backpressure state.
*
* @param[in]  ncpHdl:  NCP API state handle.
* @param[out] bpState: Buffer where the NCA backpressure state is written.
*/
NCP_API ncp_st_t
ncp_nca_bp_state_get(ncp_hdl_t ncpHdl, ncp_uint32_t *bpState);

/*!
* @fn ncp_st_t ncp_task_shutdown(ncp_uint32_t devNum)
*
* @brief Wrapper for the ncp task shutdown service.
*        Do not call directly!!
* @param devNum:  ncp device instance
*/
NCP_API ncp_st_t
ncp_task_shutdown(
ncp_uint32_t devNum);


/*!
* @fn ncp_st_t ncp_task_shutdown_wait(ncp_hdl_t ncpHdl)
*
* @brief Wrapper for the ncp task shutdown service.
*        Do not call directly!!
* @param ncpHdl:  ncp device reference
*/
NCP_API ncp_st_t
ncp_task_shutdown_wait(
ncp_hdl_t ncpHdl);

/* ============================================================================================================
* END Common APIs.   These APIs are common across both NCA V1 and NCA V2 hardware.
* ============================================================================================================
*/



/* ============================================================================================================
* Begin NCA V1 Legacy APIs.   The following APIs were developed for the ACP34xx/25xx family of prducts,  and more
* specifically,   those chips that utilize the NCA V1 architecture.
* The data structures used/returned by these APIs match those used by NCA V1 hardware.
* The legacy APIs can be used when running on a platform that uses NCA V2 hardware,   but there is a performance
* penalty for doing so,   since the RTE software must convert between NCA V1 and NCA V2 data structures.
* Futhermore,   an application that is designed to use the legacy APIs,   cannot take advantage of some of the
* new APIs that were developed specifically for the NCA V2 hardware.
* ============================================================================================================
*/


/*!
* @fn ncp_st_t ncp_task_buffer_alloc(  ncp_uint32_t size,
*                                  	void **taskAddr);
* @brief This API is called to allocate task receive buffers.
*
* @param[in]        size:     Task Size.
* @param[in,out]    taskAddr: Aaddress of location wshere the allocated task buffer virtual address will be stored.
*
* @retval NCP_ST_TASK_ALLOC_REQUIRES_POINTER  task alloc pointer for return val is NULL
* @retval NCP_ST_TASK_REQUEST_FOR_ZERO_LENGTH_TASK_BUFFER size must be greater than zero
* @retval NCP_ST_TASK_NO_MALLOC_MEM insufficient memory resources to satisfy request
*
*/
NCP_API ncp_st_t
ncp_task_buffer_alloc (
	ncp_uint32_t size,
	void **taskAddr);

/*!
* @fn ncp_st_t ncp_task_buffer_free(void *taskAddr);
* @brief This API is called to free task receive buffers.
*
* @param[in] taskAddr: task buffer to be freed.
*
* @retval NCP_ST_TASK_CLIENT_FREE_NULLPTR tried to free a null pointer
*/
NCP_API ncp_st_t
ncp_task_buffer_free (void *taskAddr);


/*!
* @fn void * NCP_TASK_DATA(ncp_task_recv_buf_t *task);
*
* @brief NCP Task IO macro to return 32/64 bit virtual address of task data,   given the task header's VA

* @param[in]       task:  Pointer to task receive buffer
* @retval          Pointer to start of task data within the task receive buffer supplied (no errors returned)
*/
#define NCP_TASK_DATA(_task) ((void *)((ncp_uint8_t *)(_task) + (_task)->dataOffset))




/*!
* @fn ncp_st_t ncp_task_recv(
*      ncp_task_hdl_t taskHdl,
*      ncp_uint8_t *pRecvQueueId,
*      ncp_vp_hdl_t *pVpHdl,
*      ncp_uint8_t *pEngineSequenceId,
*      ncp_task_recv_buf_t **task,
*      void **taskData,
*      void **recvHandlerArg,
*      ncp_bool_t wait)
*
* @brief   This API is called to receive a task. If the specified receive handle contains multiple receive queues then a weighted
*          round robin scheduling policy is used to arbitrate between the various queues. Note that the individual queue weights are
*          established at queue binding time. See ncp_task_recv_queue_vp_bind.
*          Two task delivery models are supported: a return model and a dispatch model. In the return model the ncp_task_recv function
*          simply returns the next task and associated recvFuncArg to the caller.
*          In the dispatch model the task is delivered directly to a pre-registered callback function (see ncp_task_recv_vp_bind). In this
*          case the ncp_task_recv function does not return with the task. Instead the ncp_task_recv function calls the user function that
*          is registered for the task's source VP. Upon completion of the client provided task receive function call,  the ncp_task_recv
*          API function will then return control to the caller with a status code of NCP_ST_TASK_DISPATCHED in order to allow the caller to
*          perform other work before processing the next task.
*          Note that the task delivery model is configurable on a per-VP basis.
*          Also note that, regardless of the delivery model, task receive processing is always performed within the context of the calling
*          thread.
*
* @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
* @param[in,out] pRecvQueueId: Receive queue ID pointer. If the return delivery mechanism is enabled for the source VP then
*                the ID for the receive queue that this task was received from is stored in this location.
* @param[in] vpHdl: Virtual pipeline handle
* @param[in] engineSequenceId: Formerly Pipeline ID
* @param[in,out] task: Pointer to a task receive buffer pointer. If the return delivery mechanism is enabled for the source pipeline
*                then the task buffer is stored in this location. See ncp_task_recv_buf_t.
* @param[in,out] taskData: Pointer to a void pointer that references the first byte of task Data, if any. If the return delivery
mechanism is enabled for the source pipeline then the virtual address of the task Data is stored in this location.
* @param[in,out] recvHandlerArg: If supplied,   then the application supplied argument is returned here
* @param[in] wait: Boolean flag. If set to TRUE, specifies that the call should block if necessary until an input task becomes available
*
* @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
* @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy
* @retval NCP_ST_TASK_INVALID_TASK_HANDLE  The taskHdl parameter is not valid
* @retval NCP_ST_TASK_RECV_RET_SUCCESS_WITH_NULL_PTR internal error
* @retval NCP_ST_TASK_CORRUPT_NCA_INPUT_QUEUE queue structure may be corrupt
* @retval NCP_ST_TASK_INVALID_NCA_INPUT_ELEMENT_BUFFERID queue element is corrupt
* @retval NCP_ST_TASK_ALLOC_REQUIRES_POINTER task alloc pointer for return val is NULL
* @retval NCP_ST_TASK_REQUEST_FOR_ZERO_LENGTH_TASK_BUFFER size must be greater than zero
* @retval NCP_ST_TASK_NO_MALLOC_MEM insufficient memory resources to satisfy request
* @retval NCP_ST_TASK_POOLALLOC_RET_NULL Could not replenish NCA buffer pool
* @retval NCP_ST_TASK_POOLALLOC_RET_PHYSADDR_NULL uUnexpected error when computing PA
* @retval NCP_ST_TASK_QMAP_ERR_TOO_BIG queue ID exceeds upper limit
* @retval NCP_ST_TASK_RXBUFFER_QUEUE_NOT_CONFIGURED queue must be configured in ASE config
* @retval NCP_ST_TASK_NULL_PCQ_PRODUCER_PTR internal error
* @retval NCP_ST_TASK_NULL_PCQ_CONSUMER_PTR   internal error
* @retval NCP_ST_TASK_DISPATCHED informative status, task was successfully dispatched
* @retval NCP_ST_TASK_RECV_QUEUE_EMPTY informative status, no tasks currently available
* @retval NCP_ST_TASK_PUT_NULL_TASK_COMPLETION_QUEUE completion queue not bound
* @retval NCP_ST_VPM_INVALID_VP_HDL the vpHdl parameter is not valid
* @retval NCP_ST_VPM_ENGINE_SEQUENCE_NOT_FOUND invalid engine sequence
*/
NCP_API ncp_st_t
ncp_task_recv(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t *pRecvQueueId,
	ncp_vp_hdl_t *pVpHdl,
	ncp_uint8_t *pEngineSequenceId,
	ncp_task_recv_buf_t **task,
void                **taskData,
	void **recvHandlerArg,
	ncp_bool_t wait);


/*!
* @fn ncp_st_t ncp_task_recv_done(
*                                  ncp_task_hdl_t taskHdl,
*                              	ncp_task_recv_buf_t *task);
* @brief   This API is called to indicate that CPU processing for the task is complete. The receiver is responsible for calling this
*          function when it finishes processing a task that was received from an ordered NCA queue and automatic flow completion mode is
*          disabled. This call is not required for tasks that are received from unordered NCA queues; or from ordered NCA queues when
*          automatic flow completion mode is configured.
*
* @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
* @param[in] task: Pointer to a task receive buffer pointer from a previous call to ncp_task_recv.
*
* @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
* @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy
ncp_task_create_recv_hdl
* @retval NCP_ST_TASK_INVALID_TASK_HANDLE  The taskHdl parameter is not valid
* @retval NCP_ST_TASK_NULL_TASK_IN_RECVDONE must pass pointer to task to be completed
* @retval NCP_ST_TASK_QMAP_ERR_TOO_BIG queue ID exceeds upper limit
* @retval NCP_ST_TASK_COMPLETION_QUEUE_NOT_CONFIGURED queue must be configured in ASE config
* @retval NCP_ST_TASK_NULL_PCQ_PRODUCER_PTR internal error
* @retval NCP_ST_TASK_NULL_PCQ_CONSUMER_PTR  internal error
* @retval NCP_ST_TASK_NO_MAN_COMPLETION_OWED The task supplied in the ncp_task_recv_done API does not match one which is awaiting manual completion.
* @retval NCP_ST_TASK_NULL_MAN_COMPLETION_LIST No tasks received on this task handle are awaiting manual completion.
*/
NCP_API ncp_st_t
ncp_task_recv_done(
	ncp_task_hdl_t taskHdl,
	ncp_task_recv_buf_t *task);


/*!
* @brief NCP Task IO Send Done Callback Function Prototype:
*        describes the function that is called when the ncp_task_send() API is called in send
*        completion notification mode.   In send completion mode,  the Task I/O module calls this function after the NCA
*        has successfully dequeued the task from the NCA output queue.   In this mode,   the Task I/O module does not automatically
*        free the buffer(s) associated with the task,   and after receiving the callback the application is free to free or reuse
*        the buffer.   Note the buffer was allocated by the the ncp_task_buffer_alloc API and therefore belongs to the task
*        I/O module and must be eventually returned to the pool by calling the ncp_task_buffer_free API.
*/
typedef void (*ncp_task_send_done_fn_t)(
void *sendDoneFuncArg,  /*!< An opaque argument supplied by the application on the ncp_task_send() and returned at task-done time */
	void *txBuffer);        /*!< The task buffer that was suppllied to the ncp_task_send API */


/*!
* @fn ncp_st_t ncp_task_send(	ncp_task_hdl_t taskHdl,
*                          ncp_vp_hdl_t vpHdl,
*                      	ncp_task_send_meta_t    *taskMetaData,
*                      	void *taskBuffer,
*                      	void *taskPduData,
*                      	ncp_bool_t wait,
* 	                        ncp_task_send_done_fn_t sendDoneFn,
*                          void *                  sendDoneFuncArg);
*
* @brief API function sends a task. The entire task must be contiguous.
*
* @param[in]:  taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
* @param vpHdl: Virtual Pipeline handle
* @param[in] taskMetaData: Pointer to task meta data
* @param[in] taskBuffer: Pointer to task buffer address that was allocated by the ncp_task_buffer_alloc() API (used in free)
* @param[in] taskPduData: Pointer to start of task PDU data to be transmitted.  May be same as taskBuffer.
* @param[in] wait:  Boolean flag. If set to TRUE, specifies that the call should block if necessary until task output queue resources are
*               available to queue this task for transmission.
* @param[in] sendDoneDoneFn: Application provided function pointer to be called when task has been delivered to the NCA and buffer can be
*              reused or deleted.   Otherwise, NULL if task i/o module will free the buffer.
* @param[in] sendDoneFuncArg: Opaque argument to be included in call to sendDoneFn,  if sendDoneFn provided.
*
* @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
* @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy
* @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
* @retval NCP_ST_TASK_TLS_RETRIEVAL_ERR  could not retrieve thread-local storage
* @retval NCP_ST_TASK_SEND_NULL_METADATA_PTR  metadata pointer must not be NULL
* @retval NCP_ST_TASK_SEND_NULL_TASK_PTR  task pointer must not be NULL if dataSize != 0
* @retval NCP_ST_TASK_SEND_QUEUE_FULL  informative status, no room for task in send queue
* @retval NCP_ST_TASK_BUFFSIZE_TOO_LARGE  task size exceeds memory pool maximum size buffer
* @retval NCP_ST_TASK_BUFFPOOL_CORRUPTION  internal error,  buffer pool corruption detected
* @retval NCP_ST_NO_MEMORY  insufficient memory
* @retval NCP_ST_TASK_PUT_NULL_TASK_OUTPUT_QUEUE  send queue not bound
* @retval NCP_ST_TASK_PUT_NULL_TASK_COMPLETION_QUEUE  completion queue not bound
* @retval NCP_ST_TASK_CLIENT_FREE_NULLPTR tried to free a null pointer
* @retval NCP_ST_VPM_INVALID_VP_HDL the vpHdl parameter is not valid
* @retval NCP_ST_VPM_VP_NOT_FOUND invalid virtual pipeline
*
*/
NCP_API ncp_st_t
ncp_task_send (
	ncp_task_hdl_t taskHdl,
	ncp_vp_hdl_t vpHdl,
	ncp_task_send_meta_t *taskMetaData,
	void *taskBuffer,
	void *taskPduData,
	ncp_bool_t wait,
	ncp_task_send_done_fn_t sendDoneFn,
void                   *sendDoneFuncArg);

/*!
* @fn ncp_st_t ncp_task_send_segments(	ncp_task_hdl_t taskHdl,
*                          ncp_vp_hdl_t                vpHdl,
*                      	ncp_task_send_meta_t        *taskMetaData,
*                      	ncp_uint8_t                 numSegs,
*                          ncp_task_segment_entry_t    *pSegTable,
*                      	ncp_bool_t                  wait,
*                      	ncp_task_send_done_fn_t     sendDoneFn,
*                          void                       *sendDoneFuncArg)
*
* @brief This API sends a discontiguous task using output gather-mode DMA.
*
* @param[in]:   taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
* @param vpHdl: Virtual Pipeline handle
* @param[in] taskMetaData: Pointer to task meta data
* @param[in] numSegs: The number of desriptors pointed to by pSegTable below.  The valid range for this parameter is 1..16 for *            tasks that contain data.   Zero is valid if the task contains no data.
* @param[in] pSegTable: Pointer to the descriptor table associated with the output gather-mode DMA.   There is one descriptor per contiguous segment.
* @param[in] wait:  Boolean flag. If set to TRUE, specifies that the call should block if necessary until task output queue resources are
*               available to queue this task for transmission.
* @param[in] sendDoneDoneFn: Application provided function pointer to be called when task has been delivered to the NCA and buffer(s) can be
*              reused or deleted.   Otherwise, NULL if task i/o module will free the buffer(s).
* @param[in] sendDoneFuncArg:   Application provided opaqueue data to be used in sendDone callback function above is provided.
*
* @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
* @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy
* @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
* @retval NCP_ST_TASK_TLS_RETRIEVAL_ERR could not retrieve thread-local storage
* @retval NCP_ST_TASK_SEND_NULL_METADATA_PTR metadata pointer must not be NULL
* @retval NCP_ST_TASK_SEND_SEGMENTS_INVALID_DESC A call to ncp_task_send_segments failed due to a NULL descriptor table pointer.
* @retval NCP_ST_TASK_SEND_SEGMENTS_INVALID_NUM_SEGS A call to ncp_task_send_segments failed due to the number of segments being less that zero or greater than 16.
* @retval NCP_ST_TASK_SEND_QUEUE_FULL  informative status, no room for task in send queue
* @retval NCP_ST_TASK_BUFFSIZE_TOO_LARGE  task size exceeds memory pool maximum size buffer
* @retval NCP_ST_TASK_BUFFPOOL_CORRUPTION  internal error,  buffer pool corruption detected
* @retval NCP_ST_NO_MEMORY  insufficient memory
* @retval NCP_ST_TASK_PUT_NULL_TASK_OUTPUT_QUEUE  send queue not bound
* @retval NCP_ST_TASK_PUT_NULL_TASK_COMPLETION_QUEUE  completion queue not bound
* @retval NCP_ST_TASK_CLIENT_FREE_NULLPTR tried to free a null pointer
* @retval NCP_ST_VPM_INVALID_VP_HDL the vpHdl parameter is not valid
* @retval NCP_ST_VPM_VP_NOT_FOUND invalid virtual pipeline
*/

NCP_API ncp_st_t
ncp_task_send_segments (
	ncp_task_hdl_t taskHdl,
	ncp_vp_hdl_t         vpHdl,
	ncp_task_send_meta_t *taskMetaData,
	ncp_uint8_t          numSegs,
ncp_task_segment_entry_t    *pSegTable,
	ncp_bool_t                  wait,
	ncp_task_send_done_fn_t     sendDoneFn,
	void                        *sendDoneFuncArg);


/*!
* @fn ncp_st_t ncp_task_completion_queue_flush(
*                                      ncp_task_hdl_t taskHdl,
*                                      ncp_bool_t wait,
*                                      ncp_bool_t *pQueueStatus);
*
* @brief This API is called to test the thread-locale software completion queue for the empty condition.   If the wait parameter is set to true,
*         then the function will block until all previously queued output tasks have been processed by the task send proxy service (i.e.
*         removed from the software queue and routed to the NCA hardware output queue
*
* @param[in] taskHdl: taskHdl handle returned by task module in a previous call to ncp_task_hdl_create
* @param[in] wait: If FALSE,   then return current queue status in queueEmpty,  else wait for queue to drain
* @param[in,out] pQueueEmpty: Pointer to boolean where queue status is returned, 0->empty, 1->not empty
*
* @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
* @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy
*/
NCP_API ncp_st_t
ncp_task_completion_queue_flush(
ncp_task_hdl_t taskHdl,
ncp_bool_t     wait,
ncp_bool_t     *pQueueStatus);


/* ============================================================================================================
* End NCA V1 Legacy APIs.
* ============================================================================================================
*/


/* ====

* * * W A R N I N G * * * *

NcaV2 Native APIS have not been tested at all!
Do not use!

==== */


/* ============================================================================================================
* Begin NCA V2 Native APIs.   The following APIs were developed for the AXM55xx,  and more
* specifically,   those chips that utilize the NCA V2 architecture.
* The data structures used/returned by these APIs match those used by NCA V2 hardware.
* The NCA V2 Native APIs are not backward compatible,  and can only be used when running on a platform that
* uses NCA V2 hardware.
* ============================================================================================================
*/

#define NCP_TASK_NCAV2_DATA(_task) ((void *)(ncp_raw_addr_t)((ncp_task_ncaV2_recv_buf_t *)(_task))->pduSegAddr0)

/*!
* @fn ncp_st_t ncp_task_ncav2_recv(
*      ncp_task_hdl_t taskHdl,
*      ncp_uint8_t *pRecvQueueId,
*      ncp_vp_hdl_t *pVpHdl,
*      ncp_uint8_t *pEngineSequenceId,
*      ncp_task_ncaV2_recv_buf_t **task,
*      void **recvHandlerArg,
*      ncp_bool_t wait)
*
* @brief   This API is called to receive a task. If the specified receive handle contains multiple receive queues then a weighted
*          round robin scheduling policy is used to arbitrate between the various queues. Note that the individual queue weights are
*          established at queue binding time. See ncp_task_recv_queue_vp_bind.
*          Two task delivery models are supported: a return model and a dispatch model. In the return model the ncp_task_recv function
*          simply returns the next task and associated recvFuncArg to the caller.
*          In the dispatch model the task is delivered directly to a pre-registered callback function (see ncp_task_recv_vp_bind). In this
*          case the ncp_task_recv function does not return with the task. Instead the ncp_task_recv function calls the user function that
*          is registered for the task's source VP. Upon completion of the client provided task receive function call,  the ncp_task_recv
*          API function will then return control to the caller with a status code of NCP_ST_TASK_DISPATCHED in order to allow the caller to
*          perform other work before processing the next task.
*          Note that the task delivery model is configurable on a per-VP basis.
*          Also note that, regardless of the delivery model, task receive processing is always performed within the context of the calling
*          thread.
*
* @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
* @param[in,out] pRecvQueueId: Receive queue ID pointer. If the return delivery mechanism is enabled for the source VP then
*                the ID for the receive queue that this task was received from is stored in this location.
* @param[in] vpHdl: Virtual pipeline handle
* @param[in] engineSequenceId: Formerly Pipeline ID
* @param[in,out] task: Pointer to a task receive buffer pointer. If the return delivery mechanism is enabled for the source pipeline
*                then the task buffer is stored in this location. See ncp_task_recv_buf_t.
* @param[in,out] recvHandlerArg: If supplied,   then the application supplied argument is returned here
* @param[in] wait: Boolean flag. If set to TRUE, specifies that the call should block if necessary until an input task becomes available
*
* @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
* @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy
* @retval NCP_ST_TASK_INVALID_TASK_HANDLE  The taskHdl parameter is not valid
* @retval NCP_ST_TASK_RECV_RET_SUCCESS_WITH_NULL_PTR internal error
* @retval NCP_ST_TASK_CORRUPT_NCA_INPUT_QUEUE queue structure may be corrupt
* @retval NCP_ST_TASK_INVALID_NCA_INPUT_ELEMENT_BUFFERID queue element is corrupt
* @retval NCP_ST_TASK_ALLOC_REQUIRES_POINTER task alloc pointer for return val is NULL
* @retval NCP_ST_TASK_REQUEST_FOR_ZERO_LENGTH_TASK_BUFFER size must be greater than zero
* @retval NCP_ST_TASK_NO_MALLOC_MEM insufficient memory resources to satisfy request
* @retval NCP_ST_TASK_POOLALLOC_RET_NULL Could not replenish NCA buffer pool
* @retval NCP_ST_TASK_POOLALLOC_RET_PHYSADDR_NULL uUnexpected error when computing PA
* @retval NCP_ST_TASK_QMAP_ERR_TOO_BIG queue ID exceeds upper limit
* @retval NCP_ST_TASK_RXBUFFER_QUEUE_NOT_CONFIGURED queue must be configured in ASE config
* @retval NCP_ST_TASK_NULL_PCQ_PRODUCER_PTR internal error
* @retval NCP_ST_TASK_NULL_PCQ_CONSUMER_PTR   internal error
* @retval NCP_ST_TASK_DISPATCHED informative status, task was successfully dispatched
* @retval NCP_ST_TASK_RECV_QUEUE_EMPTY informative status, no tasks currently available
* @retval NCP_ST_TASK_PUT_NULL_TASK_COMPLETION_QUEUE completion queue not bound
* @retval NCP_ST_VPM_INVALID_VP_HDL the vpHdl parameter is not valid
* @retval NCP_ST_VPM_ENGINE_SEQUENCE_NOT_FOUND invalid engine sequence
*/
NCP_API ncp_st_t
ncp_task_ncav2_recv(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t *pRecvQueueId,
	ncp_vp_hdl_t *pVpHdl,
	ncp_uint8_t *pEngineSequenceId,
	ncp_task_ncaV2_recv_buf_t **task,
	void **recvHandlerArg,
	ncp_bool_t wait);

/*!
* @fn ncp_st_t NCP_API ncp_st_t ncp_task_ncav2_send (
*	ncp_task_hdl_t taskHdl,
*	ncp_vp_hdl_t vpHdl,
*	ncp_task_ncaV2_send_meta_t *taskMetaData,
*	ncp_bool_t wait,
*	ncp_task_send_done_fn_t sendDoneFn,
*  void                   *sendDoneFuncArg	);
*
* @brief API function sends a task. The entire task must be contiguous.
*
* @param[in]:  taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
* @param vpHdl: Virtual Pipeline handle
* @param[in] taskMetaData: Pointer to task meta data
* @param[in] wait:  Boolean flag. If set to TRUE, specifies that the call should block if necessary until task output queue resources are
*               available to queue this task for transmission.
* @param[in] sendDoneDoneFn: Application provided function pointer to be called when task has been delivered to the NCA and buffer can be
*              reused or deleted.   Otherwise, NULL if task i/o module will free the buffer.
* @param[in] sendDoneFuncArg: Opaque argument to be included in call to sendDoneFn,  if sendDoneFn provided.
*
*
* @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
* @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy
* @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
* @retval NCP_ST_TASK_TLS_RETRIEVAL_ERR  could not retrieve thread-local storage
* @retval NCP_ST_TASK_SEND_NULL_METADATA_PTR  metadata pointer must not be NULL
* @retval NCP_ST_TASK_SEND_NULL_TASK_PTR  task pointer must not be NULL if dataSize != 0
* @retval NCP_ST_TASK_SEND_QUEUE_FULL  informative status, no room for task in send queue
* @retval NCP_ST_TASK_BUFFSIZE_TOO_LARGE  task size exceeds memory pool maximum size buffer
* @retval NCP_ST_TASK_BUFFPOOL_CORRUPTION  internal error,  buffer pool corruption detected
* @retval NCP_ST_NO_MEMORY  insufficient memory
* @retval NCP_ST_TASK_PUT_NULL_TASK_OUTPUT_QUEUE  send queue not bound
* @retval NCP_ST_TASK_PUT_NULL_TASK_COMPLETION_QUEUE  completion queue not bound
* @retval NCP_ST_TASK_CLIENT_FREE_NULLPTR tried to free a null pointer
* @retval NCP_ST_VPM_INVALID_VP_HDL the vpHdl parameter is not valid
* @retval NCP_ST_VPM_VP_NOT_FOUND invalid virtual pipeline
*
*/
NCP_API ncp_st_t
ncp_task_ncav2_send (
	ncp_task_hdl_t taskHdl,
	ncp_vp_hdl_t vpHdl,
	ncp_task_ncaV2_send_meta_t *taskMetaData,
	ncp_bool_t wait,
	ncp_task_send_done_fn_t sendDoneFn,
void                   *sendDoneFuncArg	);


/*!
* @fn ncp_st_t ncp_task_ncav2_recv_done(
*	ncp_task_hdl_t taskHdl,
* 	ncp_task_ncaV2_recv_buf_t *task,
*	ncp_bool_t freePduSegments);
* @brief   This API is called to indicate that CPU processing for the task is complete. The receiver is responsible for calling this
*          function when it finishes processing a task that was received from an ordered NCA queue and automatic flow completion mode is
*          disabled. This call is not required for tasks that are received from unordered NCA queues; or from ordered NCA queues when
*          automatic flow completion mode is configured.
*
* @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
* @param[in] task: Pointer to a task receive buffer pointer from a previous call to ncp_task_recv.
* @param[in] freePduSegments: If true,   then the task and all of its pdu segments will be freed in addition to the
*            task completion being performed.
*
* @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
* @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down due to config_destroy
ncp_task_create_recv_hdl
* @retval NCP_ST_TASK_INVALID_TASK_HANDLE  The taskHdl parameter is not valid
* @retval NCP_ST_TASK_NULL_TASK_IN_RECVDONE must pass pointer to task to be completed
* @retval NCP_ST_TASK_QMAP_ERR_TOO_BIG queue ID exceeds upper limit
* @retval NCP_ST_TASK_COMPLETION_QUEUE_NOT_CONFIGURED queue must be configured in ASE config
* @retval NCP_ST_TASK_NULL_PCQ_PRODUCER_PTR internal error
* @retval NCP_ST_TASK_NULL_PCQ_CONSUMER_PTR  internal error
* @retval NCP_ST_TASK_NO_MAN_COMPLETION_OWED The task supplied in the ncp_task_recv_done API does not match one which is awaiting manual completion.
* @retval NCP_ST_TASK_NULL_MAN_COMPLETION_LIST No tasks received on this task handle are awaiting manual completion.
*/
NCP_API ncp_st_t
ncp_task_ncav2_recv_done(
	ncp_task_hdl_t taskHdl,
	ncp_task_ncaV2_recv_buf_t *task,
	ncp_bool_t freePduSegments);

/*!
* @fn ncp_st_t ncp_task_ncav2_free_rx_task(
*	ncp_task_hdl_t taskHdl,
*	ncp_task_ncaV2_recv_buf_t *task);
* @brief This API is called to free a previously received task and all of its associated pdu segments.
* The receive buffer header contents must not be changed prior to calling this API.   This API must
* not be called to free tasks or buffers obtained using the legacy ncp_task_recv API.
*
* @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
* @param[in] taskAddr: task previously returned by ncp_task_ncav2_recv API
*
* @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
* @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
* @retval NCP_ST_TASK_CLIENT_FREE_NULLPTR tried to free a null pointer
*/
NCP_API ncp_st_t
ncp_task_ncav2_free_rx_task(
	ncp_task_hdl_t taskHdl,
	ncp_task_ncaV2_recv_buf_t *task);

/*!
* @fn API ncp_st_t ncp_task_ncav2_free_pdu_segments
* @brief This API is called to free multiple task buffers.   It is the callers responsibility to
* fully populate the ncp_ncaV2_free_pdu_segments_t data structure.
*
* @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
* @param[in] taskAddr: task buffer to be freed.
*
* @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
* @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
* @retval NCP_ST_TASK_CLIENT_FREE_NULLPTR tried to free a null pointer
*/
NCP_API ncp_st_t
ncp_task_ncav2_free_pdu_segments(
	ncp_task_hdl_t taskHdl,
	ncp_ncaV2_free_pdu_segments_t *task);

/*!
* @fn ncp_st_t ncp_task_ncav2_buffer_alloc(
*  ncp_task_hdl_t *taskHdl,
* 	ncp_uint32_t size,
*	void **taskAddr)
* @brief This API is called to allocate task buffers.   It is equivalent to ncp_task_buffer_alloc,   but faster
* since the caller provides the task handle,   therefore allowing the RTE to avoid accessing thread local storage
* in order to aquire the task handle.
*
* @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
* @param[in]        size:     Task Size.
* @param[in,out]    taskAddr: Aaddress of location wshere the allocated task buffer virtual address will be stored.
*
* @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
* @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
* @retval NCP_ST_TASK_ALLOC_REQUIRES_POINTER  task alloc pointer for return val is NULL
* @retval NCP_ST_TASK_REQUEST_FOR_ZERO_LENGTH_TASK_BUFFER size must be greater than zero
* @retval NCP_ST_TASK_NO_MALLOC_MEM insufficient memory resources to satisfy request
*
*/
NCP_API ncp_st_t
ncp_task_ncav2_buffer_alloc (
ncp_task_hdl_t *taskHdl,
	ncp_uint32_t size,
	void **taskAddr);

/*!
* @fn ncp_st_t ncp_task_ncav2_buffer_free (
*    ncp_task_hdl_t *taskHdl,
*	void *taskAddr);
* @brief This API is called to free a single task buffer or pduSegment.   It is equivalent to ncp_task_buffer_free,   but faster
* since the caller provides the task handle,   therefore allowing the RTE to avoid accessing thread local storage
* in order to aquire the task handle.
*
* @param[in] taskHdl:   Task handle returned by previous call to ncp_task_hdl_create()
* @param[in]    taskAddr: Address of task buffer to be freed.
*
* @retval NCP_ST_INVALID_HANDLE ncpHdl is invalid
* @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
* @retval NCP_ST_TASK_ALLOC_REQUIRES_POINTER  task alloc pointer for return val is NULL
* @retval NCP_ST_TASK_REQUEST_FOR_ZERO_LENGTH_TASK_BUFFER size must be greater than zero
* @retval NCP_ST_TASK_NO_MALLOC_MEM insufficient memory resources to satisfy request
*
*/
NCP_API ncp_st_t
ncp_task_ncav2_buffer_free (
ncp_task_hdl_t *taskHdl,
	void *taskAddr);

/* ============================================================================================================
* End NCA V2 Native APIs.
* ============================================================================================================
*/

#ifdef NCP_64
typedef ncp_uint64_t ncp_raw_addr_t;
#else
typedef ncp_uint32_t ncp_raw_addr_t;
#endif


#ifdef __cplusplus
}
#endif

#endif

/*!
* @}
*/

