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

#ifndef __ncp_task_lite_h__
#define __ncp_task_lite_h__

#ifdef __cplusplus
extern "C" { 
#endif
 
#ifndef NCP_STD_TASKIO_LITE
#include <config.h>
#endif

#if defined(NCP_TASKIO_UBOOT_ENV)
#include "ncp_task_lite_basetypes.h"
#endif

#define NCP_TASK_LITE_HDL_COOKIE        0xFACE00FF


/*
 * Client registered memeory functions
 */
 
typedef void *      (*ncp_task_lite_alloc_128B_aligned_fn_t)(int size); 
typedef void        (*ncp_task_lite_free_128B_aligned_fn_t)(void *pMem);
typedef void *      (*ncp_task_lite_alloc_nvm_fn_t)(int size); 
typedef void        (*ncp_task_lite_free_nvm_fn_t)(void *pMem);
typedef ncp_uint32_t (*ncp_task_lite_va_2_pa_fn_t)(void *va);




#if defined(NCP_TASKIO_UBOOT_ENV) 


typedef void *  ncp_hdl_t;
typedef void *  ncp_dev_t;
typedef void *  ncp_dev_hdl_t;

/* 
 * A general purpose way to eliminate warnings due the the label not being referenced.
 * 
 */
#define NCP_RETURN_LABEL \
goto ncp_return; \
ncp_return:


/*
 * MACROS
 */
 
/*#define NCP_NCA_VA_2_PA_LITE(_va) ncp_task_lite_uboot_nca_va_2_pa(_va)*/
#define NCP_NCA_VA_2_PA_LITE(_va) (unsigned long long)(_va)
 
/* no interrupt support in uboot so just hard poll,   there is nothing else to do */
#define NCP_TASK_LITE_BLOCK_ON_HW_INTERRUPT(_myTaskLiteHdl, _dev, _type, _grpId, _linearId)


/*
 * Enable these trimmed down versions if not supported in uboot env
 */
#if 1 
#define NCP_ASSERT_LITE(condition, err)  \
    if (!(condition)) {             \
        ncpStatus = (err);          \
        goto ncp_return;            \
    }

#define NCP_CALL_LITE(ncpFunc)           \
    do {                                 \
        ncpStatus = (ncpFunc);           \
        if (ncpStatus != NCP_ST_SUCCESS) \
        {                                \
            goto ncp_return;             \
        }                                \
    } while(0);
#else /* 1 */
#define NCP_ASSERT_LITE(condition, err)  NCP_ASSERT(condition, err)  
#define NCP_CALL_LITE(ncpFunc)           NCP_CALL(ncpFunc)          
#endif /* 1 */



#else /* ============= NCP_TASKIO_UBOOT_ENV ================ */

#define NCP_ASSERT_LITE(condition, err)  NCP_ASSERT(condition, err)  
#define NCP_CALL_LITE(ncpFunc)           NCP_CALL(ncpFunc)           

/* We poll in task_lite (at least for now) */
#define NCP_TASK_LITE_BLOCK_ON_HW_INTERRUPT(_myTaskHdl, _dev, _type, _grp, linearId) \
{ \
 if (NCP_TASK_SLEEP_POLL) \
 { \
      NCP_MSLEEP(NCP_SLEEP_POLL_INTERVAL); \
 } \
}

/* We do not use LCM for task i/o lite uboot */
#define NCP_NCA_VA_2_PA_LITE(_va) NCP_NCA_VA_2_PA(NCP_PCI_DOMAIN, _va)

#endif /* ============= NCP_TASKIO_UBOOT_ENV ================ */


/*! 
 *  @brief Task IO-Lite Handle:  Obtained by calling ncp_task_lite_hdl_create().  
 *       Once created,   the handle is supplied as a parameter to all other TaskIO APIs
*/
typedef void  * ncp_task_lite_hdl_t;

/*! 
 *  @brief Task IO-Lite rxQ Handle:  Obtained by calling ncp_task_lite_rx_hdl_create().  
 *       Once created,   the handle is supplied as a parameter to the TaskIO-lite receive APIs
*/
typedef void  * ncp_task_lite_rxQ_hdl_t;

/*!
 * @fn void * NCP_TASK_DATA(ncp_task_recv_buf_t *task);
 *
 * @brief NCP Task IO macro to return 32/64 bit virtual address of task data,   given the task header's VA

 * @param[in]       task:  Pointer to task receive buffer
 * @retval          Pointer to start of task data within the task receive buffer supplied (no errors returned)
*/
#define NCP_TASK_DATA(_task) ((void *)((ncp_uint8_t *)(_task) + (_task)->dataOffset))
   


/*! 
 *  @brief Task IO-Lite sond complete fucntion:  Called in the application's context during 
 *  execution of the ncp_task_lite_free_send_buffers API
*/

typedef void (*ncp_task_lite_send_done_fn_t)(
    void *sendDoneFuncArg,  /*!< An opaque argument supplied by the application on the ncp_task_send() and returned at task-done time */
	void *txBuffer);        /*!< The completed task buffer that was previously supplied to the ncp_task_send API */


#define NCP_TASK_PARAM_SIZE_BYTES         32


/*!
 * @brief NCP Task Lite Send Meta Data:   populated by the application and supplied to the ncp_task_lite_send()
 *                                        API when transmitting a task.
 */
 
typedef struct ncp_task_lite_send_meta_s
{
#ifdef NCP_BIG_ENDIAN    
    unsigned    vpId                :8;     /* Word 0 */    
    unsigned    flowId              :24;
    unsigned    reserved1           :1;     /* Word 1 */
    unsigned    reserved2           :1;     
    unsigned    priority            :3;
    unsigned    reserved3           :1;
    unsigned    incTFCxmitCnt       :1;
    unsigned    debugFieldV         :1;        
    unsigned    debugData           :24;
    unsigned    dataSize            :16;    /* Word 2 */
    unsigned    numSegments         :4;     /* Not supported in taskIO lite */
    unsigned    gatherMode          :1;     /* Not supported in taskIO lite */
    unsigned    reserved4           :5;     
    unsigned    reserved5           :6;
    unsigned    reserved6           :32;    /* Word 3 */        
    ncp_uint8_t taskParms[NCP_TASK_PARAM_SIZE_BYTES];   /* Word 4 ... 11 */
    void *      taskBuffer;                     
    void *      taskPduData;                    
    ncp_task_lite_send_done_fn_t     clientFreeFn;  
    void                            *clientFreeFnArg;   /* Word 15 */
#else
    unsigned    flowId              :24;    /* Word 0 */
    unsigned    vpId                :8;     
    unsigned    debugData           :24;    /* Word 1 */
    unsigned    debugFieldV         :1; 
    unsigned    incTFCxmitCnt       :1;         
    unsigned    reserved3           :1; 
    unsigned    priority            :3;  
    unsigned    reserved2           :1;             
    unsigned    reserved1           :1;     
    unsigned    reserved5           :6;    /* Word 2 */
    unsigned    reserved4           :5; 
    unsigned    gatherMode          :1;    /* Not supported in taskIO lite */
    unsigned    numSegments         :4;    /* Not supported in taskIO lite */ 
    unsigned    dataSize            :16;
    unsigned    reserved6           :32;    /* Word 3 */        
    ncp_uint8_t taskParms[NCP_TASK_PARAM_SIZE_BYTES];              /* Word 4 ... 11 */
    void *      taskBuffer;                     
    void *      taskPduData;                       
    ncp_task_lite_send_done_fn_t   clientFreeFn;  
    void                          *clientFreeFnArg;   /* Word 15 */
#endif
} ncp_task_lite_send_meta_t;

/*!
 * @brief NCP Task IO Receive buffer:   Tasks received using the ncp_task_recv() API function are presented to  
 *        the application in a buffer containing a data structure of this type.
*/


typedef struct ncp_task_lite_recv_buf_s 
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
} ncp_task_lite_recv_buf_t;





/* 
 * ========================== API Entry points =================================
 */
 
#if defined(NCP_TASKIO_UBOOT_ENV) || defined(TASKIOLITE_USES_UBOOT_CFG)

/*!
 * @fn ncp_task_lite_uboot_register_allocators(); 
 *
 * @brief This API is called by the task-lite client in a uboot
 * environment in order to register the memory allocator functions and 
 * conversion fcuntions.  Note that the nvm functions are allowed to be simple
 * mallocs if nvm is not required for this platform.
 *
*/	
NCP_API ncp_st_t
ncp_task_lite_uboot_register_allocators(
            ncp_task_lite_alloc_128B_aligned_fn_t    task_lite_client_alloc_aligned,
            ncp_task_lite_free_128B_aligned_fn_t     task_lite_client_free_aligned,
            ncp_task_lite_alloc_nvm_fn_t             task_lite_client_alloc_nvm,
            ncp_task_lite_free_nvm_fn_t              task_lite_client_free_nvm, ncp_task_lite_va_2_pa_fn_t               task_lite_va_2_pa);


/*!
 * @fn ncp_task_lite_uboot_config(); 
 *
 * @brief This API configured the NCA for a minimal u-boot environment.
 * This environment consists of reduced GSM memory,  a reduced task memory pool, 
 * 1 pcq group, 1 thread queue set,  and one input/receive PCQ.
 *
*/	
NCP_API ncp_st_t
ncp_task_lite_uboot_config(); 
#endif

/*!
 * @fn ncp_st_t ncp_task_lite_hdl_create(ncp_hdl_t       ncpHdl,
 *                                       ncp_uint8_t     threadQueueSetId,
 *                                       ncp_task_lite_hdl_t  *pTaskLiteHdl);
 *
 * @brief This API returns the task-lite handle.   The handle is supplied as a parameter to all other Task-Lite APIs
 *
 * @param[in]       ncpHdl:  NCP handle returned by previous call to ncp_config. Supply NULL if uboot 
                    environment 
 * @param[in]       threadQueueSetId: The linear ID (0..11) of the Thread Queue Set
 * @param[out]      pTaskLiteHdl: Pointer to where the task-lite handle will be returned 
 *
 * @retval NCP_ST_TASK_NO_GSM Task I/O Shared Memory Not Initialized
 * @retval NCP_ST_TASK_SHUTDOWN Task I/O is shutting down 
 * @retval NCP_ST_TASK_NO_MALLOC_MEM Could not allocate storage for task-lite handle
 * @retval NCP_ST_TASK_LITE_QS_NOT_AVAILABLE Invalid queueset detected.   It may be in use, out of range,  or managed
 *         by a different domain.
*/	

NCP_API ncp_st_t 
ncp_task_lite_hdl_create(
    ncp_hdl_t       ncpHdl,
    ncp_uint8_t     threadQueueSetId,
    ncp_task_lite_hdl_t  *pTaskLiteHdl);

/*!
 * @fn ncp_st_t ncp_task_lite_hdl_remove(ncp_task_lite_hdl_t  taskLiteHdl);
 *
 * @brief This API removes the task handle previously created by a call to the ncp_task_lite_hdl_create API.
 *        Any receive handles must be removed prior to calling this API.   
 *
 * @param[in]       taskLiteHdl:  task handle previously created by a call to the ncp_task_lite_hdl_create API
 *
 * @retval NCP_ST_INVALID_HANDLE taskLiteHandle is not in use
 * @retval NCP_ST_TASK_LITE_QS_NOT_IN_USE - The queueset referenced by the tak-lite handle is not currently
 *         in-use for task i/o "lite" operations. 
*/	

NCP_API ncp_st_t 
ncp_task_lite_hdl_remove(
    ncp_task_lite_hdl_t  taskLiteHdl);


/*!
 * @fn ncp_st_t ncp_task_recv_lite_hdl_create(ncp_task_lite_hdl_t  taskLiteHdl,
 *                                       ncp_uint8_t ncaQueueId,
 *                                       ncp_task_lite_rxQ_hdl_t *pTaskRxHdl);
 *
 * @brief This API removes the receive handle preiousreturns the task-lite handle.   The handle is supplied as a parameter to the ncp_task_lite_recv API.   A separate receive handle must be created for each nca input queue that an application wishes to receive from.
 *
 * @param[in]       taskLiteHdl:  task handle previously created by a call to the ncp_task_lite_hdl_create API
 * @param[in]       ncaQueueId: The linear ID (0..23) of the NCA Task Receive Queue 
 * @param[out]      pTaskRxHdl: Pointer to where the task-lite receive handle will be returned 
 *
 * @retval NCP_ST_TASK_LITE_QS_NOT_IN_USE Invalid task-lite handle detected.   
*/
	
NCP_API ncp_st_t
ncp_task_lite_recv_hdl_create(
	ncp_task_lite_hdl_t  taskLiteHdl,
	ncp_uint8_t ncaQueueId,
	ncp_task_lite_rxQ_hdl_t *taskRxHdl);

/*!
 * @fn ncp_st_t ncp_task_lite_recv_hdl_remove(ncp_task_lite_hdl_t  taskLiteHdl,
 *		                                      ncp_task_lite_rxQ_hdl_t taskRxHdl);
 *
 *
 *
 * @brief This API removes the task-lite receive handle previously created by a call to the ncp_task_lite_recv_hdl_create API.
 * 
 *
 * @param[in]       taskLiteHdl:  task handle previously created by a call to the ncp_task_lite_hdl_create API
 * @param[in]      taskRxHdl:  task-lite receive handle  
 *
 * @retval NCP_ST_TASK_LITE_QS_NOT_IN_USE Invalid task-lite receive handle detected.   
*/

NCP_API ncp_st_t
ncp_task_lite_recv_hdl_remove(
	ncp_task_lite_hdl_t  taskLiteHdl,
	ncp_task_lite_rxQ_hdl_t taskRxHdl);

/*!
 * @fn ncp_st_t ncp_task_lite_recv(ncp_task_lite_hdl_t  taskLiteHdl,
 *		                           ncp_task_lite_rxQ_hdl_t taskRxHdl,
 *                                 ncp_task_lite_recv_buf_t **task,
 *                                 void                **taskData,	
 *	                               ncp_bool_t wait);

 *
 *
 *
 * @brief This API is called to receive the next task in the nca input queue associated 
 *        with the task-lite receive handle.   It is the callers responsibility to
 *        check for errors.
 *
 * @param[in]       taskLiteHdl:  task handle previously created by a call to the ncp_task_lite_hdl_create API
 * @param[in]      taskRxHdl:  task-lite receive handle 
 * @param[in,out] task: Pointer to a task receive buffer pointer. 
 * @param[in,out] taskData: Pointer to a void pointer that references the first byte of task  * * payload data (PDU data), if any. 
 * @param[in] wait: Boolean flag. If set to TRUE, specifies that the call should block if necessary until an input task becomes available 
 *
 * @retval NCP_ST_TASK_LITE_QS_NOT_IN_USE Invalid task-lite receive handle detected.   
 * @retval NCP_ST_TASK_RECV_QUEUE_EMPTY The NCA queue does not contain any tasks, and wait was false 
*/	
NCP_API ncp_st_t
ncp_task_lite_recv(
	ncp_task_lite_hdl_t  taskLiteHdl,
	ncp_task_lite_rxQ_hdl_t taskRxHdl,
	ncp_task_lite_recv_buf_t **task,
    void                **taskData,	
	ncp_bool_t wait);


/*!
 * @fn ncp_st_t ncp_task_LITE_recv_done(
 *                                  ncp_task_LITE_hdl_t taskLiteHdl,
 *                              	ncp_task_lite_recv_buf_t *task);
 * @brief   This API is called to indicate that CPU processing for the task is complete. The receiver is responsible for calling this 
 *          function when it finishes processing a task that was received from an ordered NCA queue and automatic flow completion mode is 
 *          disabled. This call is not required for tasks that are received from unordered NCA queues; or from ordered NCA queues when 
 *          automatic flow completion mode is configured. 
 *
 * @param[in] taskLiteHdl:   Task handle returned by previous call to ncp_task_lite_hdl_create()
 * @param[in] task: Pointer to the task receive buffer to be completed;   returned in the *task parameter on a previous call to ncp_task_lite_recv.   
 *
 * @retval NCP_ST_TASK_NULL_MAN_COMPLETION_LIST No tasks received on this task handle are awaiting manual completion.
*/
NCP_API ncp_st_t
ncp_task_lite_recv_done(
	ncp_task_lite_hdl_t  taskLiteHdl,
	ncp_task_lite_recv_buf_t     *task);


/*!
 * @fn ncp_st_t ncp_task_lite_send(	ncp_task_lite_hdl_t taskHdl,
 *                      	ncp_task_lite_send_meta_t    *taskMetaData,
 *                          ncp_bool_t                  wait
 *
 * @brief API function sends a task. The entire task must be contiguous,   and must be
 * located in DMA capable memory.
 *
 * @param[in]:  taskLiteHdl:   Task handle returned by previous call to ncp_task_lite_hdl_create()
 * @param[in] taskLiteMetaData: Pointer to task-lite meta data
 * @param[in] wait:  Boolean flag. If set to TRUE, specifies that the call should block if 
 * necessary until task output queue resources are available to queue this task for 
 * transmission.
 *
 * @retval NCP_ST_TASK_SEND_QUEUE_FULL The NCA transmit queues is currently FULL and wait was FALSE.   
 *
*/
NCP_API ncp_st_t
ncp_task_lite_send (
	ncp_task_lite_hdl_t  taskLiteHdl,
	ncp_task_lite_send_meta_t *taskLiteMetaData,
	ncp_bool_t wait);


/*!
 * @fn ncp_task_lite_supply_rxbuffer_to_nca(ncp_task_lite_hdl_t  taskLiteHdl,
 *	                         void *taskAddr,
 *	                         ncp_uint8_t sizeBits);
 *
 * @brief API function replenishes a receive buffer for the NCA.  The NCA maintains
 * an internal list of receive buffers of the 4 block sizes configured in the ASE.
 * Each successful call to ncp_task_lite_recv,   even if error bits are set,   will
 * consume one of the NCA's buffers.   It is the repsonsibility of the application
 * to replenish these buffers in a timely fashion.
 *
 * @param[in]:  taskLiteHdl:   Task handle returned by previous call to ncp_task_lite_hdl_create()
 * @param[in] taskAddr: Pointer to task buffer to be supplied to NCA
 * @param[in] sizeBites Encoded value of size.   Must match size bits in the buffer
 * that is being replaced.
 *
 *
*/
NCP_API ncp_st_t 
ncp_task_lite_supply_rxbuffer_to_nca(ncp_task_lite_hdl_t  taskLiteHdl,
	                         void *taskAddr,
	                         ncp_uint8_t sizeBits);


/*!
 * @fn NCP_API ncp_st_t ncp_task_lite_free_send_buffers(ncp_task_lite_hdl_t  taskLiteHdl);
 *
 * @brief API function checks to see if buffers associated with previous calls to ncp_task_lite_send have been accepted by the NCA.   Applications must not reuse send
 * buffers prior to the task being processed by the NCA.
 *
 * @param[in]:  taskLiteHdl:   Task handle returned by previous call to ncp_task_lite_hdl_create()
 *
*/
NCP_API ncp_st_t
ncp_task_lite_free_send_buffers(ncp_task_lite_hdl_t  taskLiteHdl);

#ifdef __cplusplus
}
#endif

#endif

/*!
 * @}
 */

