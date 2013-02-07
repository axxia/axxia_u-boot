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

#ifndef __ncp_task_lite_pvt_h__
#define __ncp_task_lite_pvt_h__

#ifdef __cplusplus
extern "C" { 
#endif

#ifndef NCP_STD_TASKIO_LITE
#include <config.h>
#endif

#ifdef NCP_TASKIO_UBOOT_ENV
#include "ncp_task_lite_nca_regs.h"
#endif

#ifdef NCP_TASKIO_UBOOT_ENV /* ============================ */
/* MAXIMUMS */
#define NCP_DEV_NUM_PCQ_GROUPS  6
#define NCP_DEV_NUM_THREAD_QUEUESETS_PER_GROUP 4

#define NCP_DEV_NUM_IPCQ_PER_GROUP 16
#define NCP_DEV_NUM_OPCQ_PER_GROUP  NCP_DEV_NUM_THREAD_QUEUESETS_PER_GROUP
#define NCP_DEV_NUM_TPCQ_PER_GROUP  NCP_DEV_NUM_THREAD_QUEUESETS_PER_GROUP
#define NCP_DEV_NUM_RPCQ_PER_GROUP  NCP_DEV_NUM_THREAD_QUEUESETS_PER_GROUP
#define NCP_DEV_NUM_CPCQ_PER_GROUP  NCP_DEV_NUM_THREAD_QUEUESETS_PER_GROUP
/* END MAXIMUMS */
#endif /* NCP_TASKIO_UBOOT_ENV ============================ */


/* NUM USED IN UBOOT ENV */
#define NCP_DEV_UBOOT_CFG_NUM_TASK_MEMPOOLS   1 
#define NCP_DEV_UBOOT_CFG_NUM_RXB_POOLS       1   
#define NCP_DEV_UBOOT_CFG_NUM_PCQ_GROUPS      6 /* Must still init 6 to sane values */

#define NCP_DEV_UBOOT_CFG_NUM_THREAD_QUEUESETS_PER_GROUP 1

#define NCP_DEV_UBOOT_CFG_NUM_IPCQ_PER_GROUP 1
#define NCP_DEV_UBOOT_CFG_NUM_OPCQ_PER_GROUP  NCP_DEV_UBOOT_CFG_NUM_THREAD_QUEUESETS_PER_GROUP
#define NCP_DEV_UBOOT_CFG_NUM_TPCQ_PER_GROUP  NCP_DEV_UBOOT_CFG_NUM_THREAD_QUEUESETS_PER_GROUP
#define NCP_DEV_UBOOT_CFG_NUM_RPCQ_PER_GROUP  NCP_DEV_UBOOT_CFG_NUM_THREAD_QUEUESETS_PER_GROUP
#define NCP_DEV_UBOOT_CFG_NUM_CPCQ_PER_GROUP  NCP_DEV_UBOOT_CFG_NUM_THREAD_QUEUESETS_PER_GROUP

#define NCP_X1_UBOOT_CFG_NUM_HW_INPUT_QUEUES           1
#define NCP_X1_UBOOT_CFG_NUM_HW_NONINPUT_QUEUES        1 
#define NCP_X1_UBOOT_CFG_NUM_HW_OUTPUT_QUEUES          NCP_X1_UBOOT_CFG_NUM_HW_NONINPUT_QUEUES
#define NCP_X1_UBOOT_CFG_NUM_HW_TASK_COMPLETION_QUEUES NCP_X1_UBOOT_CFG_NUM_HW_NONINPUT_QUEUES
#define NCP_X1_UBOOT_CFG_NUM_HW_RXBUFF_QUEUES          NCP_X1_UBOOT_CFG_NUM_HW_NONINPUT_QUEUES
#define NCP_X1_UBOOT_CFG_NUM_HW_CONFIG_QUEUES          NCP_X1_UBOOT_CFG_NUM_HW_NONINPUT_QUEUES

#define NCP_X1_UBOOT_CFG_NUM_THREAD_QUEUESETS          NCP_X1_UBOOT_CFG_NUM_HW_NONINPUT_QUEUES
/* END NUM USED IN UBOOT ENV */

#ifdef NCP_TASKIO_UBOOT_ENV /* ============================ */

#define NCP_DEV_NUM_RXB_POOLS                NCP_DEV_UBOOT_CFG_NUM_RXB_POOLS
#define NCP_DEV_NUM_TASK_MEMPOOLS            NCP_DEV_UBOOT_CFG_NUM_TASK_MEMPOOLS
#define NCP_X1_NUM_HW_INPUT_QUEUES           24
#define NCP_X1_NUM_HW_NONINPUT_QUEUES        12
#define NCP_X1_NUM_HW_OUTPUT_QUEUES          NCP_X1_NUM_HW_NONINPUT_QUEUES

/* MAXIMUMS */
#define NCP_DEV_NUM_PCQ_GROUPS  6
#define NCP_DEV_NUM_THREAD_QUEUESETS_PER_GROUP 4

#define NCP_DEV_NUM_IPCQ_PER_GROUP 16
#define NCP_DEV_NUM_OPCQ_PER_GROUP  NCP_DEV_NUM_THREAD_QUEUESETS_PER_GROUP
#define NCP_DEV_NUM_TPCQ_PER_GROUP  NCP_DEV_NUM_THREAD_QUEUESETS_PER_GROUP
#define NCP_DEV_NUM_RPCQ_PER_GROUP  NCP_DEV_NUM_THREAD_QUEUESETS_PER_GROUP
#define NCP_DEV_NUM_CPCQ_PER_GROUP  NCP_DEV_NUM_THREAD_QUEUESETS_PER_GROUP
/* END MAXIMUMS */


#define NCP_TASK_SLEEP_POLL 1
#define NCP_NCA_CACHE_PRELOAD 1


#define NCP_PCI_DOMAIN       1
#define NCP_LOCAL_DOMAIN     2
#define NCP_SYSMEM_DOMAIN    3
#define NCP_LCM_DOMAIN       4

/*
 * AXI Master DMA base addresses
 */
#define NCP_DEV_AXI_PCIE_BASE    0x002040000000ULL
#define NCP_DEV_AXI_SRIO_BASE    0x002080000000ULL
#define NCP_DEV_AXI_PLB_BASE     0x000000000000ULL
#define NCP_DEV_AXI_SRIOEP_BASE  0x002080000000ULL



#define NCP_1_MB                    0x0100000
#define NCP_1_MB64                  0x0100000LL
#define NCP_2_MB                    (NCP_1_MB*2)
#define NCP_16_MB                   (NCP_1_MB*16)
#define NCP_31_MB                   0x1F00000
#define NCP_31_MB64                 0x1F00000LL
#define NCP_32_MB                   0x2000000
#define NCP_32_MB64                 0x2000000LL

#define NCP_CACHE_128B          0x80
#define NCP_CACHE_128B_PRESERVE 0xFFFFFF80
#define NCP_CACHE_128B_MASK     0x7F


#define NCP_TASK_LCM_ADDR_PA               (0x001ffffe0000ULL)
#define NCP_TASK_LCM_SIZE                  (128*1024) /* 128KB */

/* 
 * GSM (Globally Shared Memory) and LCM config attibutes
 */
typedef struct ncp_nca_gsm_info_s {
    
    ncp_uint32_t    hwGSM_VA;
    ncp_uint32_t    hwGSM_kernVA;
    ncp_uint32_t    hwGSM_size;
    ncp_uint32_t    hwGSM_PA;
        
    
    ncp_uint32_t    taskGSM_VA;
    ncp_uint32_t    taskGSM_kernVA;
    ncp_uint32_t    taskGSM_size;    
    ncp_uint32_t    taskGSM_PA;

    ncp_uint32_t    LCM_VA;
    ncp_uint32_t    LCM_kernVA;
    ncp_uint32_t    LCM_size;
    ncp_uint64_t    LCM_PA;
    
    ncp_uint64_t    axiDmaBase;
    
} ncp_nca_gsm_info_t;


#define NCP_TASK_SM_BUFF                  0
#define NCP_TASK_MED_BUFF                 1
#define NCP_TASK_LG_BUFF                  2
#define NCP_TASK_XL_BUFF                  3
#define NCP_TASK_NUM_BUFF_SIZES           4

/* queueset access mode, raw added to support taskIO lite */

typedef enum {
        NCP_NCA_QS_AVAILABLE=0,
        NCP_NCA_QS_EXCLUSIVE,
        NCP_NCA_QS_SHARED,
        NCP_NCA_QS_RAW
}  ncp_nca_qs_access_mode_t;

/* PCQ configuration */

typedef enum {
    NCP_TASK_PCQ_INPUT = 0,
    NCP_TASK_PCQ_OUTPUT,
    NCP_TASK_PCQ_COMPLETION,
    NCP_TASK_PCQ_RX_BUFFER,
    NCP_TASK_PCQ_CONFIG,
    NCP_TASK_PCQ_PROXY, /* proxy is a software only queue */
} ncp_task_pcq_type_t;


/* 
 * PCQ, MemPool & Group defines 
 * Note: uboot environment uses a minim al config
 */
 
#define NCP_REGION_NCA_AXI       (NCP_REGION_ID(0x101,  0)) /* 257.0 */

/* 
 * I/O Macros 
 */
#define NCP_DEV_NCA_READ_REG32(_dev, _region, _offset, _pReg32Val) \
*_pReg32Val = in_be32((NCA + _offset));

#define NCP_DEV_NCA_WRITE_INDIRECT_REG32(_dev, _region, _offset, _pReg32Val) \
{mb(); out_be32((NCA + _offset), *_pReg32Val); (void)in_be32(NCA + _offset);}

#define NCP_DEV_NCA_WRITE_REG32(_dev, _region, _offset, _reg32Val) \
{mb(); out_be32((NCA + _offset), _reg32Val); (void)in_be32(NCA + _offset);}

typedef struct {
    volatile ncp_uint16_t i_pIdx[NCP_DEV_NUM_IPCQ_PER_GROUP];
    volatile ncp_uint16_t o_cIdx[NCP_DEV_NUM_OPCQ_PER_GROUP];
    volatile ncp_uint16_t t_cIdx[NCP_DEV_NUM_TPCQ_PER_GROUP];
    volatile ncp_uint16_t r_cIdx[NCP_DEV_NUM_RPCQ_PER_GROUP];
    volatile ncp_uint16_t c_cIdx[NCP_DEV_NUM_CPCQ_PER_GROUP];
} ncp_dev_nca_pgit_t;

typedef struct {
    volatile ncp_uint16_t i_cIdx[NCP_DEV_NUM_IPCQ_PER_GROUP];
    volatile ncp_uint16_t o_pIdx[NCP_DEV_NUM_OPCQ_PER_GROUP];
    volatile ncp_uint16_t t_pIdx[NCP_DEV_NUM_TPCQ_PER_GROUP];
    volatile ncp_uint16_t r_pIdx[NCP_DEV_NUM_RPCQ_PER_GROUP];
    volatile ncp_uint16_t c_pIdx[NCP_DEV_NUM_CPCQ_PER_GROUP];
} ncp_dev_cpu_pgit_t;


typedef struct ncp_dev_nca_pgit_ptrs_s {
ncp_dev_nca_pgit_t *u_ptr;
ncp_dev_nca_pgit_t *k_ptr;   
} ncp_dev_nca_pgit_ptr_t;

typedef struct ncp_dev_cpu_pgit_ptrs_s {
ncp_dev_cpu_pgit_t *u_ptr;
ncp_dev_cpu_pgit_t *k_ptr;   
} ncp_dev_cpu_pgit_ptr_t;

#define NCP_NCA_PGIT_PTR u_ptr
#define NCP_CPU_PGIT_PTR u_ptr


typedef struct {
    ncp_nca_pcq_grp_reg0_t r0;
    ncp_nca_pcq_grp_reg1_t r1;
    ncp_nca_pcq_grp_reg2_t r2;
    ncp_nca_pcq_grp_reg3_t r3;
    ncp_nca_pcq_grp_reg4_t r4;
    ncp_nca_pcq_grp_reg5_t r5;
} ncp_dev_pcq_grp_init_t;



/*
 * Flow Completion Queue Entry
 */

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

typedef struct {
    ncp_nca_cfg_pio_cdr0_reg_t cdr0;
    ncp_uint32_t dataBufAddr;
    ncp_nca_cfg_pio_cdr1_reg_t cdr1;
    ncp_nca_cfg_pio_cdr2_reg_t cdr2;
} ncp_task_cPCQ_entry_t;


/*
 * typedef ncp_task_input_pcq_entry_t
 * brief NCP Task Input Producer Consumer Queue Entry
*/
typedef struct ncp_task_iPCQ_entry_s
{
#ifdef NCP_BIG_ENDIAN
    unsigned    bufferId            :32;    /* Word 0 */
    unsigned    templateId          :8;     /* Word 1 */
    unsigned    pduDataStartOffset  :8;
    unsigned    bufferPoolSize      :2;
    unsigned    bufferSizeError     :1;
    unsigned    taskError           :1;
    unsigned    parmByte29_3_0      :4;
    unsigned    parmByte30_7_0      :8; 
#else
    unsigned    bufferId            :32;    /* Word 0 */
    unsigned    parmByte30_7_0      :8;     /* Word 1 */
    unsigned    parmByte29_3_0      :4; 
    unsigned    taskError           :1; 
    unsigned    bufferSizeError     :1; 
    unsigned    bufferPoolSize      :2;  
    unsigned    pduDataStartOffset  :8;               
    unsigned    templateId          :8;     
#endif
} ncp_task_iPCQ_entry_t;

/*
 * typedef ncp_task_oPCQ_entry_t
 * brief NCP Task Output PCQ Entry - Defines Task parameters and inline data
*/


typedef struct ncp_task_oPCQ_entry_s 
{
#ifdef NCP_BIG_ENDIAN     
    unsigned    vpId                :8;     /* Word 0 */
    unsigned    flowId              :24;
    unsigned    setTaskEr           :1;     /* Word 1 */
    unsigned    interruptOnComplete :1;
    unsigned    taskPrio            :3;            
    unsigned    reserved1           :1;
    unsigned    incTFCxmitCnt       :1;     /* V2+ Only, otherwise must be binary 1 */    
    unsigned    debugFieldV         :1;
    unsigned    debugData           :24;
    unsigned    dataSize            :16;    /* Word 2 */
    unsigned    numSegments         :4;
    unsigned    gatherMode          :1;
    unsigned    reserved2           :5;        
    unsigned    dataBufferAddr_37_32:6;  
    unsigned    dataBufferAddr_31_0 :32;    /* Word 3 */                    
    ncp_uint8_t  taskParms[NCP_TASK_PARAM_SIZE_BYTES];             /* Word 4..11  */
    void *      taskBuffer;                     /* used to be reservedd! */
    void *      taskPduData;                        /* used to be reservedd! */    
    ncp_task_lite_send_done_fn_t      clientFreeFn;  /* used to be reservedd! */
    void                        *clientFreeFnArg;   /* Word 15 */
#else
    unsigned    flowId              :24;    /* Word 0 */
    unsigned    vpId                :8;     
    unsigned    debugData           :24;    /* Word 1 */
    unsigned    debugFieldV         :1;
    unsigned    incTFCxmitCnt       :1;     /* V2+ Only, otherwise must be binary 1 */        
    unsigned    reserved1           :1;
    unsigned    taskPrio            :3;
    unsigned    interruptOnComplete :1;
    unsigned    setTaskEr           :1;
    unsigned    dataBufferAddr_37_32:6;     /* Word 2 */
    unsigned    reserved2           :5;
    unsigned    gatherMode          :1;
    unsigned    numSegments         :4;
    unsigned    dataSize            :16;    
    unsigned    dataBufferAddr_31_0 :32;    /* Word 3 */                    
    ncp_uint8_t  taskParms[NCP_TASK_PARAM_SIZE_BYTES];             /* Word 4..11  */
    void *      taskBuffer;                     /* used to be reservedd! */
    void *      taskPduData;                        /* used to be reservedd! */    
    ncp_task_lite_send_done_fn_t      clientFreeFn;  /* used to be reservedd! */
    void                        *clientFreeFnArg;   /* Word 15 */
#endif
} ncp_task_oPCQ_entry_t;


/*
 * typedef ncp_task_rPCQ_entry_t
 * brief NCP Task IO Receive buffer queue element
*/
typedef struct ncp_task_rPCQ_entry_s {
#ifdef NCP_BIG_ENDIAN     
    unsigned bufferId  :32;             /* Word 0 */
    unsigned reserved1 :30;             /* Word 1 */
    unsigned bufferSize:2;
    unsigned reserved2 :26;             /* Word 2 */
    unsigned bufferAddress32_37:6;        
    unsigned bufferAddress00_31:32;     /* Word 3 */
#else
    unsigned bufferId  :32;             /* Word 0 */
    unsigned bufferSize:2;              /* Word 1 */
    unsigned reserved1 :30;    
    unsigned bufferAddress32_37:6;      /* Word 2 */
    unsigned reserved2 :26;    
    unsigned bufferAddress00_31:32;     /* Word 3 */
#endif        
} ncp_task_rPCQ_entry_t;




typedef struct iPCQ_info_s {
    ncp_task_iPCQ_entry_t *pIPCQentry;    
    void       *holBlockedTask; /* prematurely dequeued,  and HOL blocked */
    ncp_uint8_t holTemplateId;
    ncp_uint8_t holPduDataStartOffset;
    ncp_bool_t  holTaskErr;
    ncp_bool_t  holBufferSizeErr;    
    ncp_bool_t  rxTaskAutoComplete;
    ncp_uint8_t holBufferPoolSize;
    ncp_uint8_t rxBufferQueue;
    ncp_uint8_t rxBufferPool;
    volatile ncp_task_tPCQ_entry_t taskCompletionInfo;  
} iPCQ_info_t;

typedef struct oPCQ_info_s {
    ncp_task_oPCQ_entry_t *pOPCQentry;     
    ncp_uint32_t total_oTaskCnt;
    ncp_uint8_t  taskCnt;
    ncp_uint16_t intransitTasksIdx;
    ncp_uint16_t intransitSlotsAvail;
    ncp_uint8_t  taskMemPool;
} oPCQ_info_t;


typedef struct tPCQ_info_s {
    ncp_task_tPCQ_entry_t *pTPCQentry;
} tPCQ_info_t;

typedef struct rPCQ_info_s {
    ncp_task_rPCQ_entry_t *pRPCQentry;    
    ncp_uint8_t rxBufferPool;
} rPCQ_info_t;

typedef struct cPCQ_info_s {
    ncp_task_cPCQ_entry_t *pCPCQentry;    
    ncp_uint32_t blockSize;
} cPCQ_info_t;

typedef union ncp_pcq_info_u {
    iPCQ_info_t ipcq_info;
    oPCQ_info_t opcq_info;
    tPCQ_info_t tpcq_info;
    rPCQ_info_t rpcq_info;
    cPCQ_info_t cpcq_info;
} ncp_pcq_info_t;

#define PROXY_HEAD        u_proxyHead
#define PROXY_CURR        u_proxyCurr
#define NCA_BASE_BUFF_CPUADDR u_bufferCpuAddr


#define P_NEXT_PROXY_QUEUE u_pNxtProxyQueue
#define P_ACTIVE_TASK_HDL_LIST u_activeTaskHdlList



typedef struct ncp_task_pcq_s {
    
    ncp_uint32_t                cookie;
    
    ncp_uint8_t                 ncaQueueId;
    ncp_uint8_t                 grpId; 
    ncp_uint8_t                 useCnt;                       
    ncp_bool_t                  shared; 
    ncp_uint32_t                nEntries;
    volatile ncp_uint16_t       *u_pConsumerIdx;
    volatile ncp_uint16_t       *k_pConsumerIdx;
    
    volatile ncp_uint16_t       *u_pProducerIdx;
    volatile ncp_uint16_t       *k_pProducerIdx;
   
    void                        *u_pPCQbase;  
    void                        *k_pPCQbase;

    struct ncp_pvt_task_hdl_s   *ownerTaskHdl;
    struct ncp_task_pcq_s        *ncaQ;    /* NULL if real h/w queue */   


    void                        *u_pPCQdescTbl;
    void                        *k_pPCQdescTbl;

    void                        *u_bufferCpuAddr;
    void                        *k_bufferCpuAddr;
    ncp_uint64_t                bufferBusAddr;
    ncp_uint64_t                baseBusAddr;

    ncp_bool_t                  umode;
    ncp_bool_t                  swQueue;
    volatile ncp_pcq_info_t        u;            /* union containing tighltly coupled info for the queue,   varies by queue type */
} ncp_task_pcq_t;

typedef struct {
    ncp_uint32_t         id;                                /* groupId or 0xFF(unused)   */
    ncp_dev_nca_pgit_t  *pNca_pgit;                /* NCA PCQ group index table */
    ncp_dev_cpu_pgit_t  *pCpu_pgit;                /* NCA PCQ group index table */
    ncp_uint32_t        cpu_pgit_bus_addr;
    ncp_uint64_t        baseAddress;                        /* from cfg */
    ncp_uint32_t        num_iPCQs;                          /* num configured in this group  */
    ncp_uint32_t        num_oPCQs;                          /* num configured in this group  */
    ncp_uint32_t        num_tPCQs;                          /* num configured in this group  */
    ncp_uint32_t        num_cPCQs;                          /* num configured in this group  */
    ncp_uint32_t        num_rPCQs;                          /* num configured in this group  */
    ncp_uint32_t        default_tPCQ;                       /* default for task completions  */    
    ncp_int32_t         grpDomain;                          /* which domain manages this grp? */
    ncp_uint32_t        pgitNormalLoadTimer;                /* valid v1+ */
    ncp_uint32_t        pgitNormalUploadTimer;              /* valid v1+ */
    ncp_uint32_t        pgitNcaEventLoadTimer;              /* valid v1+ */
    ncp_int32_t         taskArrivalsPerInterrupt;           /* valid v1+ */
    ncp_int32_t         taskArrivalInterruptMaxDelayTime;   /* valid v1+ */
    ncp_uint32_t        pgitNcaEventUploadTimer;            /* valid v2+ ONLY */
    ncp_uint32_t        pgitIpcqEmptyToNotEmptyLoadTimer;   /* valid v2+ ONLY */
    ncp_uint32_t        pgitCpuEventLoadTimer;              /* valid v2+ ONLY */
    ncp_int32_t         pgitTaskArrivalEventThreshold;      /* valid v2+ ONLY */
    ncp_int32_t         pgitOutputEventThreshold;           /* valid v2+ ONLY */
 } ncp_dev_pcq_grp_t;


typedef struct ncp_nca_thread_queue_set_iPCQinfo_s {
    ncp_int32_t taskInputQEntries;
    ncp_int32_t rxTaskAutoComplete; 
    ncp_int32_t wrrWeight;
} ncp_nca_thread_queue_set_iPCQinfo_t;

typedef struct ncp_nca_thread_queue_set_s {
    struct ncp_nca_thread_queue_set_s *next_proxy_tqs; /* used by proxy service */
    ncp_uint32_t id;                            /* id == 0xff -> not configured */
    ncp_uint32_t grpId;                         /* group associated with this thread queue set */
    ncp_bool_t   useCnt;
    ncp_nca_qs_access_mode_t qsAccessMode;      /* exclusive, raw, shared */
    int                      qsAccessCnt;    
    ncp_int32_t              tqsDomain;
    volatile ncp_bool_t      active;            /* hooked by proxy */
    volatile ncp_bool_t      sync;              /* proxy has seen all of our previously queued cmd items */
    ncp_uint32_t first_iPCQ_id;                 /* 1st iPCQ linear ID in this set */
    ncp_uint32_t  num_iPCQs_in_queueSet;        /* Num iPCQs in this queueSet, could be zero   */
    ncp_task_pcq_t *p_oPCQ;                      /* hardware output queue */
    ncp_uint32_t taskSendQEntries;              /* num entries */
    ncp_task_pcq_t *p_tPCQ;                      /* hardware task completion queue */
    ncp_uint32_t taskCompletionQEntries;        /* num entries */
    ncp_task_pcq_t *p_rPCQ;                      /* hardware rxBuffer queue */
    ncp_uint32_t receiveBufferQEntries;         /* num entries */
    ncp_task_pcq_t *p_cPCQ;                      /* hardware configuration queue */
    ncp_uint32_t configurationQEntries;         /* num entries */
    ncp_uint32_t rxPool;                        /* Which pool */    
    ncp_nca_thread_queue_set_iPCQinfo_t inputQinfo[NCP_DEV_NUM_IPCQ_PER_GROUP];
    ncp_task_pcq_t *sw_iPCQ_head;               /* used by proxy service */
    ncp_task_pcq_t *sw_oPCQ_head;               /* used by proxy service */
    ncp_task_pcq_t *sw_tPCQ_head;               /* used by proxy service */
    ncp_task_pcq_t *sw_rPCQ_head;               /* used by proxy service */
} ncp_nca_thread_queue_set_t;

/*
 * NCA Input Queue 
 */
 
typedef struct ncp_nca_queue_s { 
    ncp_task_iPCQ_entry_t  *entries;
} ncp_nca_input_queue_t;

/*
 * NCA Output Queue
 */
 
typedef struct ncp_nca_output_queue_s {
     ncp_task_oPCQ_entry_t *entries;
} ncp_nca_output_queue_t;


/*
 * NCA Task Completion Queue 
 */

typedef struct ncp_nca_flow_completion_queue_s {
     ncp_task_tPCQ_entry_t *entries;
} ncp_nca_completion_queue_t;


/*
 * NCA receive buffer queue 
 */

typedef struct ncp_nca_receive_buffer_queue_s {
     ncp_task_rPCQ_entry_t *entries;
} ncp_nca_rxbuff_queue_t;


typedef ncp_uint8_t ncp_dev_nca_axi_cache_pad_t;

typedef struct ncp_nca_cfg_queue_block_s {
    ncp_uint8_t blkdata[1024];  /* <---- hardcoded */
} ncp_cfg_queue_block_t; 

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
            unsigned                parms[NCP_TASK_PARAM_SIZE_BYTES]; /* Word 4..11 */      
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
            unsigned                parms[NCP_TASK_PARAM_SIZE_BYTES]; /* Word 4..11 */     
            /* 8 Bytes of Debug Data, if any - see debugFieldV              */
            /* Data, if any - see dataSz                                    */      
#endif
} ncp_input_task_header_t;


/*
 * Private PCQ Related MACROS [ capable of hwio tracing in Debug only ]
 */

/*
 * Advance producer index of PCQ
 */

#define NCP_DEV_NCA_PCQ_PIDX_ADVANCE(pcq)               \
{                                                       \
    NCP_SYSMEM_BARRIER();                               \
    if ((*(pcq)->PRODUCER_PTR) == (pcq->nEntries - 1))  \
       *(pcq)->PRODUCER_PTR = 0;                        \
    else                                                \
       *(pcq)->PRODUCER_PTR+=1;                         \
}


/*
 * Advance consumer index of PCQ
 */
 
 
#define NCP_DEV_NCA_PCQ_CIDX_ADVANCE(pcq)               \
{                                                       \
    NCP_SYSMEM_BARRIER();                               \
    if ((*(pcq)->CONSUMER_PTR) == (pcq->nEntries - 1))  \
        *(pcq)->CONSUMER_PTR = 0;                       \
    else                                                \
        *(pcq)->CONSUMER_PTR+=1;                        \
}

/*
 * Is the PCQ full?
 */        
        


#define NCP_DEV_NCA_PCQ_IS_FULL(pcq) \
    ( {                              \
    (((((*(pcq)->PRODUCER_PTR) + 1) % (pcq->nEntries)) == (*(pcq)->CONSUMER_PTR)) ? TRUE : FALSE); \
    } )     

/*
 * Is the PCQ empty?
 */



#define NCP_DEV_NCA_PCQ_IS_EMPTY(pcq) \
    ( {                               \
    ((*(pcq)->PRODUCER_PTR == *(pcq)->CONSUMER_PTR) ? TRUE : FALSE); \
    } )  

/*
 * The Producer Index
 */



#define NCP_DEV_NCA_PCQ_PRODUCER_IDX(pcq) \
    ( {                               \
    (*(pcq)->PRODUCER_PTR);           \
    } )      

/*
 * The Consumer Index
 */


#define NCP_DEV_NCA_PCQ_CONSUMER_IDX(pcq) \
    ( {                               \
    (*(pcq)->CONSUMER_PTR);           \
} )

/*
 * advance non-consumer/producer mirror index using num PCQ entries as water mark
 */


#define NCP_DEV_NCA_PCQ_IDX_ADVANCE(pcq, idx) \
    {                                         \
        NCP_SYSMEM_BARRIER();                 \
        if ((idx) == (pcq->nEntries - 1))     \
            (idx) = 0;                        \
        else                                  \
            (idx)+=1;                         \
    }

#define CONSUMER_PTR u_pConsumerIdx
#define PRODUCER_PTR u_pProducerIdx
#define P_PCQ_BASE   u_pPCQbase
#define P_PCQ_DESCTBL_BASE u_pPCQdescTbl


typedef struct ncp_task_man_completion_list_element_s {
    struct ncp_task_man_completion_list_element_s *prev;
    struct ncp_task_man_completion_list_element_s *next;
    void *task;
    void *reserved;
}  ncp_task_man_completion_list_element_t;


/*
 * typedef ncp_pvt_task_hdl_t
 * brief   data structure used as container for receive handle data
 */
typedef struct ncp_pvt_task_hdl_s
{
  ncp_uint32_t                  cookie;
  struct ncp_pvt_task_hdl_s     *next;              /* Link to next task handle */
  ncp_hdl_t                     ncpHdl; 
  ncp_dev_t                     *dev;               /* dev */  
  ncp_int32_t                   threadQueueSetId;   /* Logical queue # */
  ncp_nca_thread_queue_set_t    *pThreadQueueSet;   /* Pointer to thread queue set struct */
  
  /*
   * fields related to output queue(s) abstraction
   */
  ncp_task_pcq_t        *sendQueue;
  ncp_task_pcq_t        *completionQueue;
  ncp_task_pcq_t        *rxBufferQueue;
  
  /*
   * fields related to input PCQ(s)
   */
  ncp_task_man_completion_list_element_t *firstManCompletion; 
  ncp_task_man_completion_list_element_t *lastManCompletion; 
  ncp_bool_t                orderedTaskCompletion;
} ncp_pvt_task_hdl_t;


typedef ncp_pvt_task_hdl_t ncp_pvt_task_lite_hdl_t;

/*
 * Primary hardware interface related data structures
 */
 
typedef struct ncp_nca_hwif_s { 
    
    /*
     * Begin H/W related structs
     */   
    ncp_dev_nca_pgit_ptr_t              nca_pgit[NCP_DEV_NUM_PCQ_GROUPS];    
    ncp_dev_cpu_pgit_ptr_t              cpu_pgit[NCP_DEV_NUM_PCQ_GROUPS];    
    ncp_nca_input_queue_t               NcaInputQueues[NCP_X1_UBOOT_CFG_NUM_HW_INPUT_QUEUES];
    ncp_nca_output_queue_t              NcaOutputQueues[NCP_X1_UBOOT_CFG_NUM_HW_OUTPUT_QUEUES];
    ncp_nca_completion_queue_t          NcaTaskCompletionQueues[NCP_X1_UBOOT_CFG_NUM_HW_TASK_COMPLETION_QUEUES];
    ncp_nca_rxbuff_queue_t              NcaRxBufferQueues[NCP_DEV_NUM_TASK_MEMPOOLS];
    ncp_task_cPCQ_entry_t               NcaCfgQueues[NCP_X1_UBOOT_CFG_NUM_HW_CONFIG_QUEUES];
    ncp_cfg_queue_block_t               NcaCfgQueueBlocks[8 ];  /* <---- hardcoded */
} ncp_nca_hwif_t;


/*
 * Task I/O data structure that can exist in cached memory for both external and internal host 
 * configurations
 */
typedef struct ncp_nca_task_s {
    ncp_uint32_t                        cookie1;
    ncp_bool_t                          gsmAllocsAllowed;
    ncp_nca_hwif_t                      hw;    
    ncp_uint32_t                        otbpInfo; /* memory based otask backpressure bits (written by NCA) */
    ncp_dev_pcq_grp_t                   pcq_grp[NCP_DEV_NUM_PCQ_GROUPS];       /* SW only               */
    ncp_nca_thread_queue_set_t          threadQueueSet[NCP_X1_UBOOT_CFG_NUM_THREAD_QUEUESETS]; 
    ncp_task_pcq_t                       iPCQs[NCP_X1_UBOOT_CFG_NUM_HW_INPUT_QUEUES];     /* task input            */
    ncp_task_pcq_t                       oPCQs[NCP_X1_UBOOT_CFG_NUM_HW_NONINPUT_QUEUES];  /* task output           */
    ncp_task_pcq_t                       tPCQs[NCP_X1_UBOOT_CFG_NUM_HW_NONINPUT_QUEUES];  /* task completion       */
    ncp_task_pcq_t                       rPCQs[NCP_X1_UBOOT_CFG_NUM_HW_NONINPUT_QUEUES];  /* task receive buffer   */
    ncp_task_pcq_t                       cPCQs[NCP_X1_UBOOT_CFG_NUM_HW_NONINPUT_QUEUES];  /* configuration         */    
    ncp_bool_t                          v1Hardware;
    ncp_uint8_t                         ncpId;  /* Needed when perform ops w/o task handle */    
    ncp_int32_t                         myDomain;
    ncp_task_tPCQ_entry_t               cannedCompletionRolloverEntry;        
    ncp_uint32_t                        activeGrpMask;
    ncp_uint32_t                        allGrpMask;
    ncp_uint32_t                         myInputPCQbitMask;
    ncp_uint32_t                         cookie2;
} ncp_nca_task_t;


#ifdef NCP_TASKIO_LITE_DEFINE_GLOBALS
int             ncp_trace_level=0;                  
ncp_nca_task_t *pNcpNcaTaskGSM=NULL;      /* task I/O module state              */
#else
extern int             ncp_trace_level;                  
extern ncp_nca_task_t *pNcpNcaTaskGSM;    /* task I/O module state              */
#endif

#endif  /* NCP_TASKIO_UBOOT_ENV ============================ */



extern void ncp_cache_prefetch_L0(const void *pX);
extern void ncp_cache_prefetch_L2(const void *pX);


/* Fudge some globals,   to eliminate unresolved errors */

#ifdef NCP_TASKIO_LITE_DEFINE_GLOBALS
ncp_task_lite_alloc_128B_aligned_fn_t   task_lite_alloc_aligned_fn      = NULL;
ncp_task_lite_free_128B_aligned_fn_t    task_lite_free_aligned_fn       = NULL;
ncp_task_lite_alloc_nvm_fn_t            task_lite_alloc_nvm_fn           = NULL;
ncp_task_lite_free_nvm_fn_t             task_lite_free_nvm_fn            = NULL;
ncp_task_lite_va_2_pa_fn_t              task_lite_va_2_pa_fn            = NULL;
#else
extern ncp_task_lite_alloc_128B_aligned_fn_t   task_lite_alloc_aligned_fn;
extern ncp_task_lite_free_128B_aligned_fn_t    task_lite_free_aligned_fn;
extern ncp_task_lite_alloc_nvm_fn_t            task_lite_alloc_nvm_fn;
extern ncp_task_lite_free_nvm_fn_t             task_lite_free_nvm_fn;
extern ncp_task_lite_va_2_pa_fn_t              task_lite_va_2_pa_fn;
#endif




#ifdef __cplusplus
}
#endif

#endif
