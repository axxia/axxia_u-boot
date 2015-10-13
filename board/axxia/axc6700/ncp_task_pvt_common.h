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

#ifndef __ncp_task_pvt_common_h__
#define __ncp_task_pvt_common_h__

#if 0 /* UBOOT */
#include "ncp_sal.h"
#endif

#if 1 /* UBOOT */
#define NCP_SLEEP_POLL_INTERVAL 0
#endif

/* ================================================
 * Cookie definitions
 * ================================================
 */

#define NCP_TASK_FREE_BUFF_COOKIE       0xFEDCBA98
#define NCP_TASK_STATE_COOKIE           0xFACE0FFF
#define NCP_TASK_HDL_COOKIE             0xDEADF00D
#define NCP_TASK_RECV_QUEUE_COOKIE      0xBADDFEED
#define NCP_TASK_SEND_QUEUE_COOKIE      0xDADDD00D
#define NCP_TASK_TCOMP_QUEUE_COOKIE     0xABBADABA
#define NCP_TASK_SKB_COOKIE             0x02051960
#define NCP_TASK_PCQ_INPUT_COOKIE       0xBADDABC1
#define NCP_TASK_PCQ_OUTPUT_COOKIE      0xBADDABC2
#define NCP_TASK_PCQ_COMPLETION_COOKIE  0xBADDABC3
#define NCP_TASK_PCQ_RX_BUFFER_COOKIE   0xBADDABC4
#define NCP_TASK_PCQ_CONFIG_COOKIE      0xBADDABC5


/* ================================================
 * DEBUG Enables
 * ================================================
 */


/* FIXME - does not currently work for multiple pools */
#undef   NCP_TASK_DBG_BUFFERS  /* DEBUG ONLY! - DOES NOT CURRENTLY WORK WITH LINUX KMODE POOLS! */
#ifdef   NCP_TASK_DBG_BUFFERS
#define NCP_TASK_TAKE_ON_NCA_LOCK /* Disable for speed, but possible race */
#ifndef NCP_TASK_NCA_RXPOOL_DEPTH
#define NCP_TASK_NCA_RXPOOL_DEPTH (1024+512+256+128) /* FIXME FOR 55XX */
#endif
#endif

#undef  NCP_TASK_DBG_NVM_CORRUPTION


/* ================================================
 * COMPILE/RUNTIME CONTROL
 * ================================================
 */
#define NCP_TASK_CHECK_FOR_SHUTDOWN_IN_EXIT()
#define NCP_TASK_CHECK_FOR_SHUTDOWN()
#define NCP_TASK_SILENT_CHECK_FOR_SHUTDOWN()

#define NCP_TASK_INLINE_FNS /* Use with *ALL* platforms now! */

#ifdef NCP_TASK_COLLECT_STATS_DISABLED
#define NCP_TASK_COLLECT_STATS 0
#else
#define NCP_TASK_COLLECT_STATS 1
#endif
#define NCP_TASK_GLOBAL_STATS

#if defined(PROC_X86_PLX64)
#define NCP_TASK_64BIT_ADDRESSES 1
#else
#define NCP_TASK_64BIT_ADDRESSES 0
#endif


#define NCP_TASK_ENCODE_PARAMETERS          1
#define NCP_TASK_DECODE_PARAMETERS          1
#define NCP_TASK_ENABLE_RBP_BACKPRESSURE    1


#define NCP_TASK_SLEEP_POLL 1


/* Config PCQs */
#define NCP_NCA_DEFAULT_CPCQ_DEPTH 128
#define NCP_NCA_DEFAULT_CPCQ_BLOCK_SIZE 1024

/* PIPELINE TABLE */
#define NCP_NCA_USE_GLOBAL_RECVQUEUEID      1
#define NCP_TASK_MAX_LEVEL1_BIND_ENTRIES  256
#define NCP_START_DYNAMIC_RECV_QUEUE        0
#define NCP_MAX_DYNAMIC_RECV_QUEUE          127
#define NCP_START_FIXED_RECV_QUEUE          128
#define NCP_MAX_FIXED_RECV_QUEUE            255
#define NCP_RECV_QUEUE_FIXEDBIT             0x80

/* Useful constants  */
#define NCP_1_MB                    0x0100000
#define NCP_1_MB64                  0x0100000LL
#define NCP_2_MB                    (NCP_1_MB*2)
#define NCP_16_MB                   (NCP_1_MB*16)
#define NCP_31_MB                   0x1F00000
#define NCP_31_MB64                 0x1F00000LL
#define NCP_32_MB                   0x2000000
#define NCP_32_MB64                 0x2000000LL
#define NCP_CACHE_128B              0x80
#define NCP_CACHE_128B_PRESERVE     0xFFFFFF80
#define NCP_CACHE_128B_MASK         0x7F
#define NCP_64K                     (1024*64)
#define NCP_64K_MASK                ((1024*64)-1)
#define NCP_16K_MASK                ((1024*16)-1)
#define NCP_2K_MASK                 ((1024*2)-1)
#define NCP_256_MASK                (256-1)
#define NCP_64K_PRESERVE            (~(NCP_64K_MASK))
#define NCP_16K_PRESERVE            (~(NCP_16K_MASK))
#define NCP_2K_PRESERVE             (~(NCP_2K_MASK))
#define NCP_256B_PRESERVE           (~(NCP_256B_MASK))

/* Useful macros */
#if 0
#define MY_PRINT_DBG_LINE_FILE NCP_MSG(NCP_MSG_INFO, "%s, line = %d\n", __FILE__,__LINE__)
#else
#define MY_PRINT_DBG_LINE_FILE
#endif

#ifdef NCP_TASK_INLINE_FNS
#define NCP_INLINE static __inline__
#else
#define NCP_INLINE
#error NCP_INLINE not defined
#endif


/* ================================================
 * Error defines
 * ================================================
 */

#define NCP_TASK_INVALID_GROUP 0xFF


/* ================================================
 * Common Data Structures
 * ================================================
 */


/* ==============================================
 * ACP34XX Data Structures
 * ==============================================
 */

/*
 * typedef ncp_input_task_recv_buf_t
 * brief NCP Task IO Receive/Input Header
*/

typedef struct ncp_input_task_header_s
{
#ifdef NCP_BIG_ENDIAN
            unsigned                reserved1       :1;  /* Word 0 */
            unsigned                paramSz         :7;
            unsigned                reserved2       :24;
            unsigned                reserved3       :14; /* Word 1 */
            unsigned                launchId        :18;
            unsigned                traceEn         :1;  /* Word 2 */
            unsigned                taskPrio        :3;
            unsigned                TOID            :12;
            unsigned                dataSz          :16;
            unsigned                QID             :8;  /* Word 3 */
            unsigned                destId_17_10    :8;
            unsigned                taskErr         :1;
            unsigned                bufferSizeErr   :1;
            unsigned                bufferSize      :2;
            unsigned                debugFieldV     :2;
            unsigned                destId_9_0      :10;
            ncp_uint8_t             parms[NCP_TASK_PARAM_SIZE_BYTES]; /* Word 4..11 */
            /* 8 Bytes of Debug Data, if any - see debugFieldV              */
            /* Data, if any - see dataSz                                    */
#else
            unsigned                reserved2       :24; /* Word 0 */
            unsigned                paramSz         :7;
            unsigned                reserved1       :1;
            unsigned                launchId        :18; /* Word 1 */
            unsigned                reserved3       :14;
            unsigned                dataSz          :16; /* Word 2 */
            unsigned                TOID            :12;
            unsigned                taskPrio        :3;
            unsigned                traceEn         :1;
            unsigned                destId_9_0      :10; /* Word 3 */
            unsigned                debugFieldV     :2;
            unsigned                bufferSize      :2;
            unsigned                bufferSizeErr   :1;
            unsigned                taskErr         :1;
            unsigned                destId_17_10    :8;
            unsigned                QID             :8;
            ncp_uint8_t             parms[NCP_TASK_PARAM_SIZE_BYTES]; /* Word 4..11 */
            /* 8 Bytes of Debug Data, if any - see debugFieldV              */
            /* Data, if any - see dataSz                                    */
#endif
} ncp_input_task_header_t;

/* NCA V1 Task Flow Completion Queue Entry */
/* Also used by V2 S/W auto-complete       */
typedef struct ncp_task_tPCQ_entry_s {
#ifdef NCP_BIG_ENDIAN
    unsigned intOnComplete  :1;     /* Word 0 */
    unsigned taskPriority   :3;
    unsigned toid           :12;
    unsigned dataSize       :16;
    unsigned queueId        :8;     /* Word 1 */
    unsigned completionCntInc :8;
    unsigned nOp            :1;
    unsigned reserved       :5;     /* We use this field internally as a flag, then clear before issueing */
    unsigned destId         :10;
#else
    unsigned dataSize       :16;    /* Word 0 */
    unsigned toid           :12;
    unsigned taskPriority   :3;
    unsigned intOnComplete  :1;
    unsigned destId         :10;    /* Word 1 */
    unsigned reserved       :5;
    unsigned nOp            :1;
    unsigned completionCntInc :8;
    unsigned queueId        :8;
#endif
} ncp_task_tPCQ_entry_t;

/* ===========================================
 * Misc
 * ===========================================
 */


typedef void *ncp_event_t;

#if defined(NCP_KERNEL) && !defined(NCP_VXWORKS)
typedef spinlock_t ncp_task_mutex_t;
#else
typedef ncp_sem_t ncp_task_mutex_t;
#endif


typedef enum {
    NCP_NCA_WAIT_FOR_RX_INTR=0,
    NCP_NCA_WAIT_FOR_TX_INTR,
    NCP_NCA_WAIT_FOR_TASK_COMPLETION_INTR,
    NCP_NCA_WAIT_FOR_ANY_INTR,
    NCP_NCA_WAIT_FOR_CFG_DMA_INTR
} e_nca_wait_intr_types_t;


/* queueset access mode, raw added to support taskIO lite */

typedef enum {
        NCP_NCA_QS_AVAILABLE=0,
        NCP_NCA_QS_EXCLUSIVE,
        NCP_NCA_QS_SHARED,
        NCP_NCA_QS_RAW
}  ncp_nca_qs_access_mode_t;

/* rx buffer logical sizes */
typedef enum {
    NCP_TASK_SM_BUFF=0,
    NCP_TASK_MED_BUFF,
    NCP_TASK_LG_BUFF,
    NCP_TASK_XL_BUFF,
    NCP_TASK_NUM_BUFF_SIZES
} ncp_nca_rx_buffer_sizes_t;

#if defined(NCP_TASK_KERN_NETDRIVER_ZERO_COPY)
typedef struct ncp_task_skb_taskio_header_s {
    ncp_uint32_t    task_skb_cookie;
    struct sk_buff *skb;
    ncp_uint32_t   *cache_pad[14];
} ncp_task_skb_taskio_header_t;
#endif /* defined(NCP_TASK_KERN_NETDRIVER_ZERO_COPY)  */

/*
 * typedef ncp_recv_queue_level1_bind_t
 * brief NCP Task NCA Queue Level 1 bind table - 1 per nca queue.
*/
typedef struct ncp_recv_queue_level1_bind_s
{
#ifdef NCP_BIG_ENDIAN
    unsigned    reserved        :1;
    unsigned    sharedBindCount :8;
    unsigned    reserved1       :23;
    void                        *taskQueue;
    ncp_vp_hdl_t                vpHdl;
    ncp_uint8_t                 engineSequenceId;
    ncp_task_recv_fn_t          recvFunc;
    void                        *recvFuncArg;
#else
    unsigned    reserved1       :23;
    unsigned    sharedBindCount :8;
    unsigned    reserved        :1;
    void                        *taskQueue;
    ncp_vp_hdl_t                vpHdl;
    ncp_uint8_t                 engineSequenceId;
    ncp_task_recv_fn_t          recvFunc;
    void                        *recvFuncArg;
#endif
} ncp_recv_queue_level1_bind_t;

typedef struct ncp_recv_queue_level1_bind_wrapper_s
{
    ncp_int32_t useCnt;
    ncp_recv_queue_level1_bind_t
        level1_bind[NCP_TASK_MAX_LEVEL1_BIND_ENTRIES];
} ncp_recv_queue_level1_bind_wrapper_t;


/*
 * Data structures used to interface with the ncp device driver
 */

/*
 * Passed to driver when we wish to block pending a NCA hardware interrupt
 */
typedef struct ncp_task_interrupt_s {
    ncp_uint32_t intrType;
    ncp_uint8_t  grp;
    ncp_uint64_t linearId; /* or mask if iPCQ(s) */
} ncp_task_interrupt_t;

/*
 * Passed to driver when we are configuring a kernel mode buffer pool
 */

typedef struct ncp_nca_format_memPool_s {
    int         numBuffs;
} ncp_nca_format_memPool_t;


typedef struct ncp_nca_fill_kernel_memPool_s {
    int numBuffs;
    int startingBuffId;
    int size;
    int queueNum;
} ncp_nca_fill_kernel_memPool_t;

typedef struct ncp_task_event_s {
    ncp_uint8_t  grp;
    ncp_uint8_t  reserved;
} ncp_task_event_t;

typedef struct ncp_get_sz_kernel_lock_t {
    int         *pSizeOfLock;  /* OUT: returned size */
    ncp_st_t    *st;          /* OUT: status code */
} ncp_get_sz_kernel_lock_t;

/*
 * Misc data structures
 */

typedef struct ncp_taskQ_IDs{
ncp_bool_t inUse[256];
} ncp_taskQ_IDs_t;


#ifdef NCP_TASK_DBG_NVM_CORRUPTION
typedef struct ncp_nvm_dbg_s {
    struct ncp_nvm_dbg_s   *next;
    void        *addr;
}   ncp_nvm_dbg_t;
#endif

/*
 * Used for CPU managed task buffer free list
 */

typedef struct ncp_buffDescriptor_s
{
    struct ncp_buffDescriptor_s *next;
    ncp_uint32_t                cookie;
    void                        *writeDbgDataPatternHere;
} ncp_buffDescriptor_t;


typedef struct ncp_task_bufflist_s {
    void                    *VAstart;
    void                    *VAend;
    ncp_uint32_t            size;
    ncp_buffDescriptor_t    *free;
    ncp_buffDescriptor_t    *last;
    ncp_uint32_t            numFree;
    ncp_uint32_t            freeLowWaterMark;
    ncp_uint32_t            numTotal;
    ncp_raw_addr_t          mask;
} ncp_task_bufflist_t;

/*
 * config queue address generation
 */
#define NCP_DEV_NCA_cPCQ_BUFFER_CPU_ADDR(pcq, idx) \
    ((void *) (pcq)->NCA_BASE_BUFF_CPUADDR + ((idx) * (pcq)->u.cpcq_info.blockSize))

/*
 * config queue address generation
 */
#define NCP_DEV_NCA_cPCQ_BUFF_BUS_ADDR(pcq, idx) \
    ((void *) (pcq)->bufferBusAddr + ((idx) * (pcq)->u.cpcq_info.blockSize))


#ifdef NCP_KERNEL

/*
 * PRIVATE - Task ISR Wait Control
 */
ncp_st_t
ncp_dev_nca_wakeup_all(ncp_task_isr_wait_object_t *waitListHead);

void
ncp_dev_nca_free_all_wait_objs(ncp_task_isr_wait_object_t *objListHead);

void
ncp_dev_nca_putWaitObj(ncp_task_isr_wait_object_t **pWaitListHead,
                       ncp_task_isr_wait_object_t *pWaitObj);

void
ncp_dev_nca_getWaitObj(ncp_task_isr_wait_object_t **pWaitListHead,
                       ncp_task_isr_wait_object_t **pWaitObj);
void
ncp_dev_nca_removeWaitObj(ncp_task_isr_wait_object_t **pWaitListHead,
                       ncp_task_isr_wait_object_t *pWaitObj);


/*!
 * @fn ncp_st_t ncp_dev_enable_1shot_nca_rx_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp, ncp_task_isr_wait_object_t **ppWaitObj);
 * @return Status code indicating success or failure \link ncp_st_t \endlink
 * @brief Function to force nca rx interrupts to be enabled for the specified queue
 * group.  Do not use in clients that use asynchronous interrupt callbacks.
 * This API is available only in kernel mode.
 * @param devHdl    - IN: NCP device handle.
 * @param grp       - nca pcq queue group
 * @param ppWaitOb  - if not NULL,   then pointer to allocated wait object returned here on success
 */
NCP_API ncp_st_t
ncp_dev_enable_1shot_nca_rx_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp, ncp_task_isr_wait_object_t **ppWaitObj);

/*!
 * @fn ncp_st_t ncp_dev_disable_1shot_nca_rx_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp, ncp_task_isr_wait_object_t *pWaitObj);
 * @return Status code indicating success or failure \link ncp_st_t \endlink
 * @brief Function to force nca rx interrupts to be disabled for the specified queue
 * group.   Do not use in clients that use asynchronous interrupt callbacks.
 * This API is available only in kernel mode.
 * @param devHdl    - IN: NCP device handle.
 * @param grp       - nca pcq queue group
 * @param pWaitObj  - if not NULL,   then return this wait object to free pool
 */
NCP_API ncp_st_t
ncp_dev_disable_1shot_nca_rx_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp, ncp_task_isr_wait_object_t *pWaitObj);

/*!
 * @fn ncp_st_t ncp_dev_enable_1shot_nca_tx_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp, ncp_task_isr_wait_object_t **ppWaitObj);
 * @return Status code indicating success or failure \link ncp_st_t \endlink
 * @brief Function to force nca tx interrupts to be enabled for the specified queue
 * group.   Do not use in clients that use asynchronous interrupt callbacks.
 * This API is available only in kernel mode.
 * @param devHdl    - IN: NCP device handle.
 * @param grp       - nca pcq queue group
 * @param ppWaitOb  - if not NULL,   then pointer to wait object returned here on success
 */
NCP_API ncp_st_t
ncp_dev_enable_1shot_nca_tx_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp, ncp_task_isr_wait_object_t **ppWaitObj);

/*!
 * @fn ncp_st_t ncp_dev_disable_1shot_nca_tx_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp, ncp_task_isr_wait_object_t *pWaitObj);
 * @return Status code indicating success or failure \link ncp_st_t \endlink
 * @brief Function to force nca tx interrupts to be disabled for the specified queue
 * group.   Do not use in clients that use asynchronous interrupt callbacks.
 * This API is available only in kernel mode.
 * @param devHdl    - IN: NCP device handle.
 * @param grp       - nca pcq queue group
 * @param pWaitObj  - if not NULL,   then return this wait object to free pool
 */
NCP_API ncp_st_t
ncp_dev_disable_1shot_nca_tx_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp, ncp_task_isr_wait_object_t *pWaitObj);

/*!
 * @fn ncp_st_t ncp_dev_enable_1shot_nca_task_completion_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp, ncp_task_isr_wait_object_t **ppWaitObj);
 * @return Status code indicating success or failure \link ncp_st_t \endlink
 * @brief Function to force nca task completion interrupts to be enabled for the
 * specified queue group.   Do not use in clients that use asynchronous interrupt
 * callbacks.
 * This API is available only in kernel mode.
 * @param devHdl    - IN: NCP device handle.
 * @param grp       - nca pcq queue group
 * @param ppWaitOb  - if not NULL,   then pointer to wait object returned here on success
 */
NCP_API ncp_st_t
ncp_dev_enable_1shot_nca_task_completion_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp, ncp_task_isr_wait_object_t **ppWaitObj);

/*!
 * ncp_st_t ncp_dev_disable_1shot_nca_task_completion_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp, ncp_task_isr_wait_object_t *pWaitObj);
 * @return Status code indicating success or failure \link ncp_st_t \endlink
 * @brief Function to force nca task completion interrupts to be disabled for the
 * specified queue group. Do not use in clients that use asynchronous interrupt
 * callbacks.
 * This API is available only in kernel mode.
 *
 * @param devHdl    - IN: NCP device handle.
 * @param grp       - nca pcq queue group
 * @param pWaitObj  - if not NULL,   then return this wait object to free pool
 */
NCP_API ncp_st_t
ncp_dev_disable_1shot_nca_task_completion_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp, ncp_task_isr_wait_object_t *pWaitObj);

#ifdef NCP_VXWORKS

#define NCP_DEV_NCA_WRITE_REG32(_dev, _region, _offset, _val) \
{                                                       \
    ncp_uint32_t _tmp_val = _val;                       \
    ncp_uint32_t *_pVal =  &_tmp_val;                   \
    if (ncpHwioTraceFunc != NULL)                       \
    {                                                   \
        ncp_hwio_rw_t _hw;                              \
        ncp_uint32_t _devNum;                           \
        NCP_CALL(ncp_dev_num_get(_dev, &_devNum));      \
        _hw.regionId = _region;                         \
        _hw.offset = (_offset);                         \
        _hw.buffer = (ncp_uint32_t*)_pVal;              \
        _hw.count = 1;                                  \
        _hw.flags = 0;                                  \
        ncpHwioTraceFunc(                               \
                ncpHwioTraceFuncArg,                    \
                NCP_HWIO_WRITE32,                       \
                _devNum,                                \
                &_hw);                                  \
    }                                                   \
    NCP_CALL(ncp_dev_block_write32(_dev, _region, _offset, _pVal, 1, 0));\
}

#define NCP_DEV_NCA_WRITE_INDIRECT_REG32(_dev, _region, _offset, _pVal)     \
{                                                               \
    if (ncpHwioTraceFunc != NULL)                       \
    {                                                   \
        ncp_hwio_rw_t _hw;                              \
        ncp_uint32_t _devNum;                           \
        NCP_CALL(ncp_dev_num_get(_dev, &_devNum));      \
        _hw.regionId = _region;                         \
        _hw.offset = (_offset);                          \
        _hw.buffer = (ncp_uint32_t*)_pVal;                 \
        _hw.count = 1;                                   \
        _hw.flags = 0;                                   \
        ncpHwioTraceFunc(                               \
                ncpHwioTraceFuncArg,                    \
                NCP_HWIO_WRITE32,                       \
                _devNum,                                \
                &_hw);                                  \
    }                                                   \
    NCP_CALL(ncp_dev_block_write32(_dev, _region, _offset, _pVal, 1, 0));\
}


#define NCP_DEV_NCA_READ_REG32(_dev, _region, _offset, _pVal)     \
{                                                       \
    NCP_CALL(ncp_dev_block_read32(_dev, _region, _offset, _pVal, 1, 0));\
    if (ncpHwioTraceFunc != NULL)                       \
    {                                                   \
        ncp_hwio_rw_t _hw;                              \
        ncp_uint32_t _devNum;                           \
        NCP_CALL(ncp_dev_num_get(_dev, &_devNum));      \
        _hw.regionId = _region;                         \
        _hw.offset = (_offset);                          \
        _hw.buffer = (ncp_uint32_t*)_pVal;                 \
        _hw.count = 1;                                   \
        _hw.flags = 0;                                   \
        ncpHwioTraceFunc(                               \
                ncpHwioTraceFuncArg,                    \
                NCP_HWIO_READ32,                        \
                _devNum,                                \
                &_hw);                                  \
    }                                                   \
}

/*
 * use internal wrappers
 */
#else

extern void
ncp_dev_nca_taskio_write_reg32(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t  offset,
    ncp_uint32_t  val);

extern void
ncp_dev_nca_taskio_read_reg32(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t  offset,
    ncp_uint32_t  *pVal);

#define NCP_DEV_NCA_WRITE_REG32(_dev, _region, _offset, _value) \
ncp_dev_nca_taskio_write_reg32(_dev, _offset, _value)

#define NCP_DEV_NCA_WRITE_INDIRECT_REG32(_dev, _region, _offset, _pVal) \
{                                                                       \
    ncp_uint32_t _value = *_pVal;                                       \
    ncp_dev_nca_taskio_write_reg32(_dev, _offset, _value);              \
}

#define NCP_DEV_NCA_READ_REG32(_dev, _region, _offset, _pVal) \
ncp_dev_nca_taskio_read_reg32(_dev, _offset, ((ncp_uint32_t *)_pVal))

#endif /* !NCP_VXWORKS */

#else /* ****************************************************************************************************************/

#if 0 /* UBOOT */
#include "ncp.h"
#include "ncp_pvt.h"


#define NCP_DEV_NCA_WRITE_REG32(_dev, _region, _offset, _val) \
{                                                       \
    ncp_uint32_t _tmp_val = _val;                       \
    ncp_uint32_t *_pVal =  &_tmp_val;                   \
    if (ncpHwioTraceFunc != NULL)                       \
    {                                                   \
        ncp_hwio_rw_t _hw;                              \
        ncp_uint32_t _devNum;                           \
        NCP_CALL(ncp_dev_num_get(_dev, &_devNum));      \
        _hw.regionId = _region;                         \
        _hw.offset = (_offset);                         \
        _hw.buffer = (ncp_uint32_t*)_pVal;              \
        _hw.count = 1;                                  \
        _hw.flags = 0;                                  \
        ncpHwioTraceFunc(                               \
                ncpHwioTraceFuncArg,                    \
                NCP_HWIO_WRITE32,                       \
                _devNum,                                \
                &_hw);                                  \
    }                                                   \
    NCP_CALL(ncp_dev_block_write32(_dev, _region, _offset, _pVal, 1, 0));\
}

#define NCP_DEV_NCA_WRITE_INDIRECT_REG32(_dev, _region, _offset, _pVal)     \
{                                                               \
    if (ncpHwioTraceFunc != NULL)                       \
    {                                                   \
        ncp_hwio_rw_t _hw;                              \
        ncp_uint32_t _devNum;                           \
        NCP_CALL(ncp_dev_num_get(_dev, &_devNum));      \
        _hw.regionId = _region;                         \
        _hw.offset = (_offset);                          \
        _hw.buffer = (ncp_uint32_t*)_pVal;                 \
        _hw.count = 1;                                   \
        _hw.flags = 0;                                   \
        ncpHwioTraceFunc(                               \
                ncpHwioTraceFuncArg,                    \
                NCP_HWIO_WRITE32,                       \
                _devNum,                                \
                &_hw);                                  \
    }                                                   \
    NCP_CALL(ncp_dev_block_write32(_dev, _region, _offset, _pVal, 1, 0));\
}


#define NCP_DEV_NCA_READ_REG32(_dev, _region, _offset, _pVal)     \
{                                                       \
    NCP_CALL(ncp_dev_block_read32(_dev, _region, _offset, _pVal, 1, 0));\
    if (ncpHwioTraceFunc != NULL)                       \
    {                                                   \
        ncp_hwio_rw_t _hw;                              \
        ncp_uint32_t _devNum;                           \
        NCP_CALL(ncp_dev_num_get(_dev, &_devNum));      \
        _hw.regionId = _region;                         \
        _hw.offset = (_offset);                          \
        _hw.buffer = (ncp_uint32_t*)_pVal;                 \
        _hw.count = 1;                                   \
        _hw.flags = 0;                                   \
        ncpHwioTraceFunc(                               \
                ncpHwioTraceFuncArg,                    \
                NCP_HWIO_READ32,                        \
                _devNum,                                \
                &_hw);                                  \
    }                                                   \
}
#else

/* UBOOT - FIXME
 * We use these for uBoot environment
*/
#define NCP_DEV_NCA_WRITE_REG32(_dev, _region, _offset, _val)
#define NCP_DEV_NCA_WRITE_INDIRECT_REG32(_dev, _region, _offset, _pVal)
#define NCP_DEV_NCA_READ_REG32(_dev, _region, _offset, _pVal)
#endif /* UBOOT */
#endif

/*
 * Common byte swapping macros
 */

#define Endian16_Swap(value) \
    ({   \
       ncp_uint16_t  _val_= (ncp_uint16_t)value, _val1_;\
 _val1_ =((((_val_) & 0x00FF)) << 8) | \
          ((((_val_) & 0xFF00)) >> 8); \
          _val1_;\
       } )

#define Endian32_Swap(value) \
       ({       \
        ncp_uint32_t _val_ = (ncp_uint32_t)value, _val1_; \
         _val1_ = (((((_val_) & 0x000000FF)) << 24) | \
          ((((_val_) & 0x0000FF00)) << 8) | \
          ((((_val_) & 0x00FF0000)) >> 8) | \
          ((((_val_) & 0xFF000000)) >> 24)) ;\
          _val1_; \
       })

#define	Endian64_Swap(value)                                    \
({                                                              \
    ncp_uint64_t _val_ = (ncp_uint64_t)(value), _val1_;         \
    _val1_ = (((ncp_uint64_t)(_val_) << 56) |                   \
    (((ncp_uint64_t)(_val_) << 40) & 0xff000000000000ULL) |     \
    (((ncp_uint64_t)(_val_) << 24) & 0xff0000000000ULL) |       \
    (((ncp_uint64_t)(_val_) << 8)  & 0xff00000000ULL) |         \
    (((ncp_uint64_t)(_val_) >> 8)  & 0xff000000ULL) |           \
    (((ncp_uint64_t)(_val_) >> 24) & 0xff0000ULL) |             \
    (((ncp_uint64_t)(_val_) >> 40) & 0xff00ULL) |               \
    ( (ncp_uint64_t)(_val_) >> 56));                            \
    _val1_;                                                     \
})




/*
 * basic macros that will copy two or four  32-bit words from
 * the source to destination, with approprieate byte
 * swapping depending on the host.  These are used for
 * getting/putting various descriptor queue entries
 * or buffer headers.
 *
 * If the src and dest are the same (i.e. swap in place)
 * and we are running on a big-endian system then
 * hopefully the compiler will realize that this doesn't
 * do anything and optimize it out completely.
 * TEST: removed volatile - should not be needed
 */
#define NCP_DEV_FOUR_WORD_SWAP(_dest, _src)         \
({                                                   \
    ncp_uint32_t *_from32 = (ncp_uint32_t *) _src;   \
    ncp_uint32_t *_to32   = (ncp_uint32_t *) _dest;  \
    _to32[0] = SWAP_32(_from32[0]);                   \
    _to32[1] = SWAP_32(_from32[1]);                   \
    _to32[2] = SWAP_32(_from32[2]);                   \
    _to32[3] = SWAP_32(_from32[3]);                   \
})

/* TEST: removed volatile - should not be needed */
#define NCP_DEV_TWO_WORD_SWAP(_dest, _src)          \
({                                                   \
    ncp_uint32_t *_from32 = (ncp_uint32_t *) _src;   \
    ncp_uint32_t *_to32   = (ncp_uint32_t *) _dest;  \
    _to32[0] = SWAP_32(_from32[0]);                   \
    _to32[1] = SWAP_32(_from32[1]);                   \
})

/*
 * The following macros do not lend themselves well to NCP_CHECK()
 */

#if 0 /* UBOOT */
#if !defined(NCP_KERNEL) && !defined(NCP_CHECK_DISABLED)
#define NCP_NCA_VALIDATE_NCP_HDL(ncpHdl)     NCP_CALL(ncp_validate_handle(ncpHdl));
#define NCP_VP_VALIDATE_HANDLE(vpHdl)        ncp_vp_validate_handle(vpHdl);
#else
#define NCP_NCA_VALIDATE_NCP_HDL(ncpHdl)
#define NCP_VP_VALIDATE_HANDLE(vpHdl)
#endif /* NCP_KERNEL */
#endif

/*
 * Critical Section Mgmt
 */

#define NCA_INC_CRITICAL_SECTION(_myTaskHdl) \
    ( {                               \
    ((_myTaskHdl) ?   (_myTaskHdl)->inCriticalSection++ : 0); \
    } )

#define NCA_DEC_CRITICAL_SECTION(_myTaskHdl) \
    ( {                               \
    ((_myTaskHdl) ?   (_myTaskHdl)->inCriticalSection-- : 0); \
    } )


/* DEBUG Functions used with gdb */
void ncp_r32_swap(ncp_uint32_t *addr, int len);
void ncp_r64_swap(ncp_uint64_t *addr, int len);
void ncp_r16_swap(ncp_uint16_t *addr, int len);
void ncp_r32(ncp_uint32_t *addr, int len);
void ncp_r16(ncp_uint16_t *addr, int len);
void ncp_r8(ncp_uint8_t *addr, int len);
void ncp_w8(ncp_uint8_t *addr, ncp_uint8_t data);
void ncp_w16(ncp_uint16_t *addr, ncp_uint16_t data);
void ncp_w32(ncp_uint32_t *addr, ncp_uint32_t data);


#endif /* __ncp_task_pvt_common_h__ */
