/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                        *
 **                                                                       *
 **************************************************************************/

#ifndef __NCP_NCAV3_QPM_H__
#define __NCP_NCAV3_QPM_H__

#ifdef __cplusplus
extern "C" {
#endif

/****************************/
/******** QPM Macros ********/
/****************************/

#define NCP_NCAV3_QPM_NUM_EXTASK_INFO_MEM_LOCATIONS 128

#define NCP_NCAV3_QPM_NUM_INTERRUPT_QUEUES_USED 3
#define NCP_NCAV3_QPM_PUSH_QUEUE 0
#define NCP_NCAV3_QPM_POP_QUEUE 1
#define NCP_NCAV3_QPM_OVERFLOW_QUEUE 2

/*********************************/
/******** QPM Stats types ********/
/*********************************/

typedef struct {
    ncp_uint64_t numEvents[3];
} ncp_ncav3_qpm_stats_t;

/***********************************/
/******** QPM Command types ********/
/***********************************/

typedef struct {
#ifdef NCP_BIG_ENDIAN
    ncp_uint64_t reserved0 :39;
    ncp_uint64_t mmio      :1;
    ncp_uint64_t axAddr    :16;
    ncp_uint64_t cmd       :5;
    ncp_uint64_t reserved1 :3;
#else
    ncp_uint64_t reserved1 :3;
    ncp_uint64_t cmd       :5;
    ncp_uint64_t axAddr    :16;
    ncp_uint64_t mmio      :1;
    ncp_uint64_t reserved0 :39;
#endif
} ncp_ncav3_qpm_cmd_t;


typedef enum {
    QPM_RD_TP = 0,
    QPM_RD_HP,
    QPM_RD_EXCEPTION_MAP,
    QPM_RD_NOOP,
    QPM_RD_POINTERS,
    QPM_RD_THRESHOLDS,
    QPM_RD_QUEUE_MEM,
    QPM_RD_ELEMENT_COUNT,
    QPM_RD_LL_STATE_MEM,
    QPM_RD_LL_HEAD_PTR,
    QPM_RD_LL_DATA_MEM,
    QPM_RD_LL_FREE_LIST_MEM,
    QPM_RD_LINK_MEM,
    QPM_RD_FREE_LIST_MEM,
    QPM_RD_EXCEPTION_TASK_INFO,
    QPM_RD_RSVD1,
    QPM_RD_ADDS_TO_QUEUE_COUNT,
    QPM_RD_POPS_FROM_NON_EMPTY_QUEUE,
    QPM_RD_POPS_FROM_EMPTY_QUEUE,
    QPM_RD_MIN_MAX_QUEUE_SIZE,
    QPM_RD_INTQ,
    QPM_RD_EXREPORTED
} ncp_ncav3_qpm_rd_cmd_e;


typedef enum {
    QPM_WR_TP = 0,
    QPM_WR_HP,
    QPM_WR_EXCEPTION_MAP,
    QPM_WR_NOOP,
    QPM_WR_RSVD1,
    QPM_WR_THRESHOLDS,
    QPM_WR_QUEUE_MEM,
    QPM_WR_RSVD2,
    QPM_WR_RSVD3,
    QPM_WR_RSVD4,
    QPM_WR_RSVD5,
    QPM_WR_RSVD6,
    QPM_WR_LINK_MEM,
    QPM_WR_RSVD7,
    QPM_WR_EXCEPTION_TASK_INFO,
    QPM_WR_EXCEPTION_OVERFLOW_STATUS_CLEAR,
    QPM_WR_ADDS_TO_QUEUE_COUNT,
    QPM_WR_POPS_FROM_NON_EMPTY_QUEUE,
    QPM_WR_POPS_FROM_EMPTY_QUEUE,
    QPM_WR_MIN_MAX_QUEUE_SIZE,
    QPM_WR_RSVD8,
    QPM_WR_RSVD9,
    QPM_WR_EXCEPTION_ACK_MM,
    QPM_WR_INTERRUPT_ACK
} ncp_ncav3_qpm_wr_cmd_e;

/***********************************/
/********   QPM Data types  ********/
/***********************************/

typedef struct {
#ifdef NCP_BIG_ENDIAN
    ncp_uint32_t reserved :16;
    ncp_uint32_t queueNum :16;
#else
    ncp_uint32_t queueNum :16;
    ncp_uint32_t reserved :16;
#endif
} ncp_ncav3_qpm_wr_resp_t;


typedef struct {
#ifdef NCP_BIG_ENDIAN
    ncp_uint64_t reserved :52;
    ncp_uint64_t pushMap  :4;
    ncp_uint64_t popMap   :4;
    ncp_uint64_t ofMap    :4;
#else
    ncp_uint64_t ofMap    :4;
    ncp_uint64_t popMap   :4;
    ncp_uint64_t pushMap  :4;
    ncp_uint64_t reserved :52;
#endif
} ncp_ncav3_qpm_exception_map_t;


typedef struct {
#ifdef NCP_BIG_ENDIAN
    ncp_uint64_t reserved0 :16;
    ncp_uint64_t headPtr   :16;
    ncp_uint64_t reserved1 :16;
    ncp_uint64_t tailPtr   :16;
#else
    ncp_uint64_t tailPtr   :16;
    ncp_uint64_t reserved1 :16;
    ncp_uint64_t headPtr   :16;
    ncp_uint64_t reserved0 :16;
#endif
} ncp_ncav3_qpm_pointers_t;


typedef struct {
#ifdef NCP_BIG_ENDIAN
    ncp_uint64_t reserved0          :2;
    ncp_uint64_t compareThreshEqual :1;
    ncp_uint64_t ackless            :1;
    ncp_uint64_t serviceType        :1;
    ncp_uint64_t deltaSelect        :3;
    ncp_uint64_t popSelect          :3;
    ncp_uint64_t pushSelect         :3;
    ncp_uint64_t enAF               :1;
    ncp_uint64_t aFthresh           :16;
    ncp_uint64_t enAE               :1;
    ncp_uint64_t aEthresh           :16;
    ncp_uint64_t FullThresh         :16;
#else
    ncp_uint64_t FullThresh         :16;
    ncp_uint64_t aEthresh           :16;
    ncp_uint64_t enAE               :1;
    ncp_uint64_t aFthresh           :16;
    ncp_uint64_t enAF               :1;
    ncp_uint64_t pushSelect         :3;
    ncp_uint64_t popSelect          :3;
    ncp_uint64_t deltaSelect        :3;
    ncp_uint64_t serviceType        :1;
    ncp_uint64_t ackless            :1;
    ncp_uint64_t compareThreshEqual :1;
    ncp_uint64_t reserved0          :2;
#endif
} ncp_ncav3_qpm_thresholds_t;


typedef struct {
#ifdef NCP_BIG_ENDIAN
    ncp_uint32_t reserved :16;
    ncp_uint32_t address  :16;
#else
    ncp_uint32_t address  :16;
    ncp_uint32_t reserved :16;
#endif
} ncp_ncav3_qpm_queue_mem_wr_resp_t;


typedef struct {
#ifdef NCP_BIG_ENDIAN
    ncp_uint64_t reserved       :47;
    ncp_uint64_t overflowStatus :1;
    ncp_uint64_t numElements    :16;
#else
    ncp_uint64_t numElements    :16;
    ncp_uint64_t overflowStatus :1;
    ncp_uint64_t reserved       :47;
#endif
} ncp_ncav3_qpm_elem_count_t;


typedef struct {
#ifdef NCP_BIG_ENDIAN
    ncp_uint64_t reserved :50;
    ncp_uint64_t link     :14;
#else
    ncp_uint64_t link     :14;
    ncp_uint64_t reserved :50;
#endif
} ncp_ncav3_qpm_link_mem_t;


typedef struct {
#ifdef NCP_BIG_ENDIAN
    ncp_uint64_t reserved :32;
    ncp_uint64_t flm      :32;
#else
    ncp_uint64_t flm      :32;
    ncp_uint64_t reserved :32;
#endif
} ncp_ncav3_qpm_free_list_mem_t;


typedef struct {
#ifdef NCP_BIG_ENDIAN
    ncp_uint64_t reserved   :13;
    ncp_uint64_t priority   :3;
    ncp_uint64_t pushTag    :8;
    ncp_uint64_t popTag     :8;
    ncp_uint64_t vflowID    :8;
    ncp_uint64_t vflowIndex :24;
#else
    ncp_uint64_t vflowIndex :24;
    ncp_uint64_t vflowID    :8;
    ncp_uint64_t popTag     :8;
    ncp_uint64_t pushTag    :8;
    ncp_uint64_t priority   :3;
    ncp_uint64_t reserved   :13;
#endif
} ncp_ncav3_qpm_exception_task_info_t;


typedef struct {
#ifdef NCP_BIG_ENDIAN
    ncp_uint64_t reserved    :16;
    ncp_uint64_t addsToQueue :48;
#else
    ncp_uint64_t addsToQueue :48;
    ncp_uint64_t reserved    :16;
#endif
} ncp_ncav3_qpm_adds_to_queue_t;


typedef struct {
#ifdef NCP_BIG_ENDIAN
    ncp_uint64_t reserved       :16;
    ncp_uint64_t popsFromyQueue :48;
#else
    ncp_uint64_t popsFromQueue :48;
    ncp_uint64_t reserved      :16;
#endif
} ncp_ncav3_qpm_num_queue_pops_t;


typedef struct {
#ifdef NCP_BIG_ENDIAN
    ncp_uint64_t reserved0      :17;
    ncp_uint64_t MinQueueSize   :15;
    ncp_uint64_t reserved1      :17;
    ncp_uint64_t MaxQueueSize   :15;
#else
    ncp_uint64_t MaxQueueSize   :15;
    ncp_uint64_t reserved1      :17;
    ncp_uint64_t MinQueueSize   :15;
    ncp_uint64_t reserved0      :17;
#endif
} ncp_ncav3_qpm_queue_size_t;


typedef struct {
#ifdef NCP_BIG_ENDIAN
    ncp_uint64_t reserved0  :32;
    ncp_uint64_t intq_depth :16;
    ncp_uint64_t qnum       :16;
#else
    ncp_uint64_t qnum       :16;
    ncp_uint64_t intq_depth :16;
    ncp_uint64_t reserved0  :32;
#endif
} ncp_ncav3_qpm_intq_entry_t;


#ifdef __cplusplus
}
#endif

#endif /* __NCP_NCAV3_QPM_H__ */
