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

#ifndef __ncp_task_pvt_axm55xx_h__
#define __ncp_task_pvt_axm55xx_h__

#if 0 /* UBOOT */
#include "ncp_sal.h"
#endif
#include "ncp_mme_ext.h"
#include "ncp_mme_regions.h"

/* ================================================
 * RUNTIME CONTROL - subject to override
 * ================================================
 */

#ifndef NCP_TASK_CACHE_PRELOAD
#define NCP_TASK_CACHE_PRELOAD      1
#endif

#ifndef NCP_NCA_CFG_TASK_INTERRUPTS
#define NCP_NCA_CFG_TASK_INTERRUPTS 1
#endif

#if NCP_TASK_COLLECT_STATS
#define NCP_TASK_INC_STAT(thisStat) { if (NULL != pNcpNcaV2_domainBundle) { pNcpNcaV2_TaskSwState->myTaskStats.stat_##thisStat ++; }}
#else
#define NCP_TASK_INC_STAT(thisStat)
#endif

#define NCP_TASK_ENABLE_PGIT_UPLOADS 0
#define NCP_TASK_OTBP_ALLOWED

#define NCP_TASK_NVAV2_PGIT_WRAP_BIT ((ncp_uint16_t)(1<<15))

/*
 * Is free list for CPU managed pools implemented as a FIFO or LIFO?
 * LIFO is faster,  but increases likelyhood of application bugs corrupting data, or the
 * freelist itself.
 */
#define NCP_TASK_CPU_POOL_IS_LIFO

/*
 * There are a few NcaV2 H/W bugs that will be present in the V1 ASIC.
 * The following defines will force s/w workarounds to be executed.
 * These code modifications must be removed for the production hardware!
 */

#define NCP_TASK_SW_WORKAROUNDS_FOR_V1_ASIC_HW_BUGS
#ifdef NCP_TASK_SW_WORKAROUNDS_FOR_V1_ASIC_HW_BUGS

/*
 * BZ 44412
 * BZ 44392
 */
#define NCP_TASK_FORCE_OTASK_COPY 1

/*
 * BZ 44279
 */
#define NCP_TASK_BUFFSZ_BITS_REQ_FOR_SHARED_POOL_BUG

/*
 * BZ 44419
 * BZ 44405
 * BZ 44520
 * Must use dealloc immediate instead of dealloc
 * Must use completion followed by dealloc immedaite instead of completion_plus-dealloc
 */
#define NCP_TASK_DEALLOC_BUG
#define NCP_TASK_COMPLETION_PLUS_DEALLOC_BUG

/*
 * BZ 44422 - Solution UNKNOWN!!
 */

/*
 * Queue full/empty detection for NCA hardware
 */
#define NCP_TASK_NCAV2_USES_WRAP_BIT 0
#else
#define NCP_TASK_FORCE_OTASK_COPY 0
#define NCP_TASK_NCAV2_USES_WRAP_BIT 1
#endif  /* NCP_TASK_SW_WORKAROUNDS_FOR_V1_ASIC_HW_BUGS */

/*
 * DEBUG
 */

/* #define NCP_TASK_DEBUG_MME */
/* #define NCP_TASK_DBG_55XX_TASK_FLOW */
/* #define NCP_TASK_DBG_TRACK_ALLOC_FREE */
/* #define NCP_TASK_DBG_TRACK_AUX_DATA */
/* #define NCP_TASK_PRINT_BASE_ADDRESSES_AND_MAPPINGS */
#define NCP_TASK_NCAV2_SHPOOL_PTR_DEBUG  0
/* #define NCP_KMODE_DEBUG */

/* ================================================
 *  NCA HW Constants
 * ================================================
 */

#define NCP_NCAV2_NUM_PCQ_GROUPS   16
#define NCP_X7_NUM_PCQ_GROUPS   NCP_NCAV2_NUM_PCQ_GROUPS
#define NCP_X7_NUM_DOMAINS      16

#define NCP_X7_NUM_THREAD_QUEUESETS_PER_GROUP  4
#define NCP_X7_NUM_IPCQ_PER_GROUP              16
#define NCP_X7_NUM_OPCQ_PER_GROUP      NCP_X7_NUM_THREAD_QUEUESETS_PER_GROUP
#define NCP_X7_NUM_CPCQ_PER_GROUP      NCP_X7_NUM_THREAD_QUEUESETS_PER_GROUP
#define NCP_X7_NUM_RSVD_PCQ_PER_GROUP  NCP_X7_NUM_THREAD_QUEUESETS_PER_GROUP

#define NCP_X7_NUM_HW_INPUT_QUEUES           64
#define NCP_X7_NUM_HW_NONINPUT_QUEUES        32
#define NCP_X7_NUM_HW_OUTPUT_QUEUES          NCP_X7_NUM_HW_NONINPUT_QUEUES
#define NCP_X7_NUM_HW_CONFIG_QUEUES          NCP_X7_NUM_HW_NONINPUT_QUEUES

#define NCP_X7_NUM_THREAD_QUEUESETS          NCP_X7_NUM_HW_NONINPUT_QUEUES

#define NCP_X7_NUM_TASK_MEMORY_POOLS    24 /* 0-1 rsvd, 2-7 HW Managed, 8-23 CPU Managed */
#define NCP_X7_NUM_SHARED_MEMORY_POOLS   8
#define NCP_X7_NUM_MME_ALLOCATORS       64 /* 4 queues each */

/*
 * Maximum number of segments allowed per task
 */

#define NCP_X7_MAX_PDU_SEGS 6

/* Buffer sizes are not configurable with X7 NCA V2 */
#define NCP_X7_BUFFER_SZ0  256
#define NCP_X7_BUFFER_SZ1  (1024*2)
#define NCP_X7_BUFFER_SZ2  (1024*16)
#define NCP_X7_BUFFER_SZ3  (1024*64)

/* Masks used to find start of buffer even if free ptr is not @ buff start */
#define NCP_X7_BUFFER_START_MASK_SZ0 ((ncp_raw_addr_t)(~(NCP_X7_BUFFER_SZ0-1)))
#define NCP_X7_BUFFER_START_MASK_SZ1 ((ncp_raw_addr_t)(~(NCP_X7_BUFFER_SZ1-1)))
#define NCP_X7_BUFFER_START_MASK_SZ2 ((ncp_raw_addr_t)(~(NCP_X7_BUFFER_SZ2-1)))
#define NCP_X7_BUFFER_START_MASK_SZ3 ((ncp_raw_addr_t)(~(NCP_X7_BUFFER_SZ3-1)))


#define NCP_DEV_FIRST_CPU_MANAGED_POOL          8
#define NCP_DEV_LAST_CPU_MANAGED_POOL           23

/*
 * Convenience macros for better readability
 */
#define NCP_TASK_IS_SHARED_POOL(_poolID) \
((_poolID) < NCP_DEV_FIRST_CPU_MANAGED_POOL  ? TRUE : FALSE)

#define NCP_TASK_IS_CPU_POOL(_poolID) \
((_poolID) >= NCP_DEV_FIRST_CPU_MANAGED_POOL ? TRUE : FALSE)


#define NCP_TASK_HACK_BOARD_BRINGUP_NUM_BUFFS_TO_NCA 8

#define NCP_TASK_USE_MME_RECOVER_PTR_MODE

#define NCP_TASK_POOL_0 0
#define NCP_TASK_POOL_8 8
#define NCP_TASK_POOL_9 9

/* FIXME HACK - TEST WITH VP CONTROL STRUCTS IN POOL8 INSTEAD OF 0 */
#define NCP_TASK_VP_CONTROL_POOL_ID NCP_TASK_POOL_0

/*
 * Kernel mode enable
 * Note: Current support is limited to LINUX only!
 */

#if defined(NCP_LINUX) && !defined(NCP_DEV_FBRS) && !defined(NCP_DEV_SOCKET)
#define NCP_TASK_KERNEL_MODE_TASKIO_ALLOWED (TRUE)
#else
#define NCP_TASK_KERNEL_MODE_TASKIO_ALLOWED (FALSE)
#endif



/*
 * External host only!:
 * PCIe windows for access from 55xx h/w to external host memory
 */
#define NCP_TASK_PCIE2_MEM_WINDOW_PA 0x3000000000ULL
#define NCP_TASK_PCIE1_MEM_WINDOW_PA 0x3040000000ULL
#define NCP_TASK_PCIE0_MEM_WINDOW_PA 0x3080000000ULL



/* ==========================================
 * Optimizations, based on coherency
 * ==========================================
 */

#if defined(NCP_NCA_COHERENT_IO)

#define NCP_TASK_LOCK_REDUCTION 1

#else  /* NCP_NCA_COHERENT_IO */

#define NCP_TASK_LOCK_REDUCTION 0

#endif /* NCP_NCA_COHERENT_IO */


/*
 * NOTE: for 55xx we swap if BIG_ENDIAN,   but for 34xx we swap if for
 * little endian.
 * Socket layer provides the byte swap on little endian platforms (x86)
 */


#if !defined(NCP_BIG_ENDIAN) || defined(NCP_DEV_SOCKET)
#define SWAP_16(n)    (n)
#define SWAP_32(n)    (n)
#define SWAP_64(n)    (n)
#else
#ifdef NCP_PLX
#if __GNUC__ == 4 && __GNUC_MINOR__ > 3
#define SWAP_16(n)         (__builtin_bswap32(n)>> 16)
#define SWAP_32(n)		__builtin_bswap32(n)
#define SWAP_64(n)		__builtin_bswap64(n)
#else
#define SWAP_16(n)              Endian16_Swap(n)
#define SWAP_32(n)              Endian32_Swap(n)
#define SWAP_64(n)              Endian64_Swap(n)
#endif
#else
#define SWAP_16(n)              Endian16_Swap(n)
#define SWAP_32(n)              Endian32_Swap(n)
#define SWAP_64(n)              Endian64_Swap(n)
#endif
#endif



/* ================================================
 * 34xx/25xx Specific Data Structures
 * ================================================
 */

typedef enum {
    NCP_TASK_PCQ_INPUT = 0,
    NCP_TASK_PCQ_OUTPUT,
    NCP_TASK_PCQ_CONFIG,
} ncp_task_pcq_type_t;

/* Interrupt domains */

typedef enum {
        NCP_NCA_CPU_ANY=0,
        NCP_NCA_CPU_0,
        NCP_NCA_CPU_1,
        NCP_NCA_CPU_2,
        NCP_NCA_CPU_3,
        NCP_NCA_CPU_4,
        NCP_NCA_CPU_5,
        NCP_NCA_CPU_6,
        NCP_NCA_CPU_7,
        NCP_NCA_CPU_8,
        NCP_NCA_CPU_9,
        NCP_NCA_CPU_10,
        NCP_NCA_CPU_11,
        NCP_NCA_CPU_12,
        NCP_NCA_CPU_13,
        NCP_NCA_CPU_14,
        NCP_NCA_CPU_15,
        NCP_NCA_CPU_PCIe0,
        NCP_NCA_CPU_PCIe1,
        NCP_NCA_CPU_PCIe2,
        NCP_NCA_CPU_SRIO
}  ncp_nca_cpu_ids_t;

/* Memory domains */

typedef enum {
    NCP_PCI_DOMAIN=1,
    NCP_SYSMEM_DOMAIN
} ncp_nca_memory_domains_t;

/* NCA V1 PGIT Layout */
typedef struct {
    volatile ncp_uint16_t i_pIdx[NCP_X7_NUM_IPCQ_PER_GROUP];
    volatile ncp_uint16_t o_cIdx[NCP_X7_NUM_OPCQ_PER_GROUP];
    volatile ncp_uint16_t rsvd1_cIdx[NCP_X7_NUM_RSVD_PCQ_PER_GROUP];
    volatile ncp_uint16_t rsvd2_cIdx[NCP_X7_NUM_RSVD_PCQ_PER_GROUP];
    volatile ncp_uint16_t c_cIdx[NCP_X7_NUM_CPCQ_PER_GROUP];
} ncp_dev_nca_pgit_t;

typedef struct {
    volatile ncp_uint16_t i_cIdx[NCP_X7_NUM_IPCQ_PER_GROUP];
    volatile ncp_uint16_t o_pIdx[NCP_X7_NUM_OPCQ_PER_GROUP];
    volatile ncp_uint16_t rsvd1_pIdx[NCP_X7_NUM_RSVD_PCQ_PER_GROUP];
    volatile ncp_uint16_t rsvd2_pIdx[NCP_X7_NUM_RSVD_PCQ_PER_GROUP];
    volatile ncp_uint16_t c_pIdx[NCP_X7_NUM_CPCQ_PER_GROUP];
} ncp_dev_cpu_pgit_t;

typedef struct ncp_dev_nca_pgit_ptrs_s {
ncp_dev_nca_pgit_t *ptr;
} ncp_dev_nca_pgit_ptr_t;

typedef struct ncp_dev_cpu_pgit_ptrs_s {
ncp_dev_cpu_pgit_t *ptr;
} ncp_dev_cpu_pgit_ptr_t;

typedef struct {
    ncp_nca_pcq_grp_reg0_t r0;
    ncp_nca_pcq_grp_reg1_55xx_t r1;
    ncp_nca_pcq_grp_reg2_55xx_t r2;
    ncp_nca_pcq_grp_reg3_55xx_t r3;
    ncp_nca_pcq_grp_reg4_55xx_t r4;
    ncp_nca_pcq_grp_reg5_55xx_t r5;
} ncp_dev_pcq_grp_init_t;


/* NCA V1 Config DMA Queue Entry */
typedef struct {
    ncp_nca_cfg_pio_cdr0_reg_t cdr0;
    ncp_uint32_t dataBufAddr;
    ncp_nca_cfg_pio_cdr1_reg_t cdr1;
    ncp_nca_cfg_pio_cdr2_reg_t cdr2;
} ncp_task_cPCQ_entry_t;


/*
 * ncaV2 Task Completion Modes
 */
typedef  enum
{
    NCP_TASK_COMPLETION_HW_AUTOMATIC=0,
    NCP_TASK_COMPLETION_SW_AUTOMATIC,
    NCP_TASK_COMPLETION_MANUAL
} ncp_task_completion_mode_t;



#define NCP_OPCQ_PAD ( 16 - sizeof(void *))

/*
 * typedef ncp_pvt_task_send_meta_t
 * brief NCP Private Task Send Meta Data:
 *  exposes additional fields used internally,  and hidden from client apps
*/
typedef struct ncp_pvt_task_send_meta_s
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
    unsigned    numSegments         :4;
    unsigned    gatherMode          :1;
    unsigned    reserved4           :5;
    unsigned    reserved5           :6;

    unsigned    reserved6           :32;    /* Word 3 */

    ncp_uint8_t taskParms[NCP_TASK_PARAM_SIZE_BYTES];   /* Word 4 ... 11 */
    unsigned    padding[4];
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
    unsigned    gatherMode          :1;
    unsigned    numSegments         :4;
    unsigned    dataSize            :16;

    unsigned    reserved6           :32;    /* Word 3 */

    ncp_uint8_t taskParms[NCP_TASK_PARAM_SIZE_BYTES];   /* Word 4 ... 11 */
    unsigned    padding[4];
#endif
} ncp_pvt_task_send_meta_t;

/* 55XX Specific Data Structures - BEGIN */
/*
 * AXMncaV2 Specific Data Structures Used By The CPU and NCA.
 * Note that rPCQs and tPCQs have been eliminated,   and that
 * oPCQs are now used to perform several functions,  as determined
 * by the cmdCode.    Additionally,   if a task to be sent contains
 * more than 2 segments,   then 2 oPCQ entries are used.  These entries
 * can wrap from the end of the PCQ to the begining.
 */

typedef struct ncp_ncaV2_task_iPCQ_entry_s
{
#ifdef NCP_BIG_ENDIAN
    ncp_uint64_t taskAddr          ;    /* Word 0-1 */

    unsigned templateID         :8;     /* Word 2 */
    unsigned QID                :8;
    unsigned pduSize            :16;

    unsigned reserved0          :6;     /* Word 3 */
    unsigned dstID_9_0          :10;
    unsigned reserved1          :1;
    unsigned priority           :3;
    unsigned TOID               :12;
#else
    ncp_uint64_t taskAddr          ;    /* Word 0-1 */

    unsigned pduSize            :16;    /* Word 2 */
    unsigned QID                :8;
    unsigned templateID         :8;


    unsigned TOID               :12;    /* Word 3 */
    unsigned priority           :3;
    unsigned reserved1          :1;
    unsigned dstID_9_0          :10;
    unsigned reserved0          :6;

#endif
} ncp_task_ncaV2_iPCQ_entry_t;

typedef struct ncp_ncaV2_input_task_header_s
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
} ncp_ncaV2_input_task_header_t;

typedef enum
{
    NCP_NCAV2_OPCQ_ENTRY_AVAILABLE=0,                    /* 3b000 */
    NCP_NCAV2_OPCQ_ENTRY_OTASK_LE_2_PTRS,                /* 3b001 */
    NCP_NCAV2_OPCQ_ENTRY_OTASK_GT_2_PTRS,                /* 3b010 */
    NCP_NCAV2_OPCQ_ENTRY_OTASK_EXTENSION,                /* 3b011 */
    NCP_NCAV2_OPCQ_ENTRY_TASK_COMPLETION,                /* 3b100 */
    NCP_NCAV2_OPCQ_ENTRY_TASK_DEALLOC,                   /* 3b101 */
    NCP_NCAV2_OPCQ_ENTRY_TASK_COMPLETION_PLUS_DEALLOC,   /* 3b110 */
    NCP_NCAV2_OPCQ_ENTRY_TASK_DEALLOC_IMMEDIATE          /* 3b111 */
} ncp_ncaV2_opcq_entry_command_codes_t;

/*
 * oPCQ entry types,  determined by
 * cmdCode (ncp_ncaV2_opcq_entry_command_codes_t).
 *
 * Note that all entry types are padded (if necessary) to make sure they
 * are exactly 16 32-bit words (64 bytes) in size.
 */


typedef struct ncp_task_ncaV2_oPCQ_entry_task_s
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
#endif
} ncp_task_ncaV2_oPCQ_entry_task_t;

typedef struct ncp_task_ncaV2_oPCQ_entry_task_extension_s
{
#ifdef NCP_BIG_ENDIAN
    unsigned cmdCode             :3;    /* Word 0 - 3b010 */
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
    unsigned reserved0          :29;    /* Word 0 - 3b010 */
    unsigned cmdCode             :3;

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
} ncp_task_ncaV2_oPCQ_entry_task_extension_t;

typedef struct ncp_ncaV2_task_oPCQ_entry_completion_s
{
#ifdef NCP_BIG_ENDIAN
    unsigned cmdCode             :3;    /* Word 0 - 3b011 */
    unsigned interruptOnComplete :1;
    unsigned reserved0          :28;

    unsigned reserved1          :21;    /* Word 1 */
    unsigned reserved2          :5;
    unsigned poolID             :6;

    ncp_uint64_t taskAddr          ;     /* Word 2-3 */

    ncp_uint32_t pad[12]           ;     /* Words 4..15 */
#else
    unsigned reserved0          :28;    /* Word 0 - 3b011 */
    unsigned interruptOnComplete :1;
    unsigned cmdCode             :3;

    unsigned poolID             :6;     /* Word 1 */
    unsigned reserved2          :5;
    unsigned reserved1          :21;

    ncp_uint64_t taskAddr          ;     /* Word 2-3 */

    ncp_uint32_t pad[12]           ;     /* Words 4..15 */
#endif
} ncp_ncaV2_task_oPCQ_entry_completion_t;

typedef struct ncp_ncaV2_task_oPCQ_entry_dealloc_s
{
#ifdef NCP_BIG_ENDIAN
    unsigned cmdCode             :3;    /* Word 0 - 3b100 */
    unsigned interruptOnComplete :1;
    unsigned reserved0          :28;

    unsigned reserved1          :21;    /* Word 1 */
    unsigned ptrCnt             :3;
    unsigned reserved2          :2;
    unsigned poolID             :6;

    ncp_uint64_t taskAddr          ;     /* Word 2-3 */

    ncp_uint32_t pad[12]           ;     /* Words 4..15 */
#else
    unsigned reserved0          :28;    /* Word 0 - 3b100 */
    unsigned interruptOnComplete :1;
    unsigned cmdCode             :3;

    unsigned poolID             :6;     /* Word 1 */
    unsigned reserved2          :2;
    unsigned ptrCnt             :3;
    unsigned reserved1          :21;

    ncp_uint64_t taskAddr          ;     /* Word 2-3 */

    ncp_uint32_t pad[12]           ;     /* Words 4..15 */
#endif
} ncp_ncaV2_task_oPCQ_entry_dealloc_t;

typedef struct ncp_ncaV2_task_oPCQ_entry_completion_plus_dealloc_s
{
#ifdef NCP_BIG_ENDIAN
    unsigned cmdCode             :3;    /* Word 0 - 3b101 */
    unsigned interruptOnComplete :1;
    unsigned reserved0          :28;

    unsigned reserved1          :21;    /* Word 1 */
    unsigned ptrCnt             :3;
    unsigned reserved2          :2;
    unsigned poolID             :6;

    ncp_uint64_t taskAddr          ;     /* Word 2-3 */

    ncp_uint32_t pad[12]           ;     /* Words 4..15 */
#else
    unsigned reserved0          :28;    /* Word 0 - 3b101 */
    unsigned interruptOnComplete :1;
    unsigned cmdCode             :3;

    unsigned poolID             :6;     /* Word 1 */
    unsigned reserved2          :2;
    unsigned ptrCnt             :3;
    unsigned reserved1          :21;

    ncp_uint64_t taskAddr          ;     /* Word 2-3 */

    ncp_uint32_t pad[12]           ;     /* Words 4..15 */

#endif
} ncp_ncaV2_task_oPCQ_entry_completion_plus_dealloc_t;

typedef struct ncp_ncaV2_task_oPCQ_entry_dealloc_immediate_s
{
#ifdef NCP_BIG_ENDIAN
    unsigned cmdCode             :3;    /* Word 0 - 3b100 */
    unsigned interruptOnComplete :1;
    unsigned reserved0          :28;

    unsigned pduBlockSz0        :2;    /* Word 1 */
    unsigned pduBlockSz1        :2;
    unsigned pduBlockSz2        :2;
    unsigned pduBlockSz3        :2;
    unsigned pduBlockSz4        :2;
    unsigned pduBlockSz5        :2;
    unsigned reserved1          :9;
    unsigned ptrCnt             :3;
    unsigned reserved2          :2;
    unsigned poolID             :6;

    ncp_uint64_t pduSegAddr0       ;     /* Word 2-3 */
    ncp_uint64_t pduSegAddr1       ;     /* Word 4-5 */
    ncp_uint64_t pduSegAddr2       ;     /* Word 6-7 */
    ncp_uint64_t pduSegAddr3       ;     /* Word 8-9 */
    ncp_uint64_t pduSegAddr4       ;     /* Word 10-11 */
    ncp_uint64_t pduSegAddr5       ;     /* Word 12-13 */
    ncp_uint32_t pad[2]            ;     /* Words 14..15 */
#else
    unsigned reserved0          :28;     /* Word 0 - 3b100 */
    unsigned interruptOnComplete :1;
    unsigned cmdCode             :3;

    unsigned poolID             :6;     /* Word 1 */
    unsigned reserved2          :2;
    unsigned ptrCnt             :3;
    unsigned reserved1          :9;
    unsigned pduBlockSz5        :2;
    unsigned pduBlockSz4        :2;
    unsigned pduBlockSz3        :2;
    unsigned pduBlockSz2        :2;
    unsigned pduBlockSz1        :2;
    unsigned pduBlockSz0        :2;


    ncp_uint64_t pduSegAddr0       ;     /* Word 2-3 */
    ncp_uint64_t pduSegAddr1       ;     /* Word 4-5 */
    ncp_uint64_t pduSegAddr2       ;     /* Word 6-7 */
    ncp_uint64_t pduSegAddr3       ;     /* Word 8-9 */
    ncp_uint64_t pduSegAddr4       ;     /* Word 10-11 */
    ncp_uint64_t pduSegAddr5       ;     /* Word 12-13 */
    ncp_uint32_t pad[2]            ;     /* Words 14..15 */
#endif
} ncp_ncaV2_task_oPCQ_entry_dealloc_immediate_t;
/*
 * The following entry type can be used when inspecting a
 * oPCQ entry in order to determine which command is contained therein.
 * Note that this type is not recognized by the NCA hardware,   and is
 * to be used for software inspection/decode only.
 */

typedef struct ncp_ncaV2_task_oPCQ_entry_generic_s {
#ifdef NCP_BIG_ENDIAN
    unsigned cmdCode             :3;    /* Word 0 */
    unsigned reserved0          :29;

    ncp_uint32_t pad[15]           ;    /* Words 1..15 */
#else
    unsigned reserved0          :29;    /* Word 0 */
    unsigned cmdCode             :3;

    ncp_uint32_t pad[15]           ;    /* Words 1..15 */
#endif
} ncp_ncaV2_task_oPCQ_entry_generic_t;

/*
 * Any given oPCQ entry may be populated with a variety of commands.
 * Therefore it is appropriate to use of the following union when declaring
 * output PCQs.   The exact command contained in any given entry is determined
 * by the command code.
 */

typedef union ncp_ncaV2_task_oPCQ_entry_u {
    ncp_task_ncaV2_oPCQ_entry_task_t             entryTask;
    ncp_task_ncaV2_oPCQ_entry_task_extension_t   entryTaskExtension;
    ncp_ncaV2_task_oPCQ_entry_completion_t       entryTaskCompletion;
    ncp_ncaV2_task_oPCQ_entry_dealloc_t          entryTaskDealloc;
    ncp_ncaV2_task_oPCQ_entry_completion_plus_dealloc_t
                                                entryTaskCompletionPlusDealloc;
    ncp_ncaV2_task_oPCQ_entry_dealloc_immediate_t                                                                                       entryTaskDeallocImmediate;
    ncp_ncaV2_task_oPCQ_entry_generic_t          entryGeneric;
} ncp_task_ncaV2_oPCQ_entry_t;

/*
 * command specific data blocks pointed to by the taskAddr field
 * in some of the subtypes of the ncp_ncaV2_task_oPCQ_entry_u definition.
 */

typedef struct ncp_ncaV2_task_completion_data_s
{
#ifdef NCP_BIG_ENDIAN
    unsigned templateID          :8;    /* Word 0 */
    unsigned QID                 :8;
    unsigned pduSize            :16;

    unsigned reserved0           :6;    /* Word 1 */
    unsigned dstID_9_0          :10;
    unsigned reserved1           :1;
    unsigned priority            :3;
    unsigned TOID               :12;
#else
    unsigned pduSize            :16;     /* Word 0 */
    unsigned QID                 :8;
    unsigned templateID          :8;


    unsigned TOID               :12;    /* Word 1 */
    unsigned priority            :3;
    unsigned reserved1           :1;
    unsigned dstID_9_0          :10;
    unsigned reserved0           :6;

#endif
} ncp_ncaV2_task_completion_data_t;

typedef struct ncp_ncaV2_task_dealloc_data_s
{
#ifdef NCP_BIG_ENDIAN
    unsigned pduBlockSz0           :2;      /* Word 0 */
    unsigned pduBlockSz1           :2;
    unsigned pduBlockSz2           :2;
    unsigned pduBlockSz3           :2;
    unsigned pduBlockSz4           :2;
    unsigned pduBlockSz5           :2;
    unsigned reserved0             :9;
    unsigned ptrCnt                :3;
    unsigned reserved1             :2;
    unsigned poolID                :6;

    unsigned reserved2             :32;     /* Word 1 */

    ncp_uint64_t pduSegAddr0       ;     /* Word 2-3 */

    ncp_uint64_t pduSegAddr1       ;     /* Word 4-5 */

    unsigned reserved3          :32;     /* Word 6 */

    unsigned reserved4          :32;     /* Word 7 */

    ncp_uint64_t pduSegAddr2       ;     /* Word 8-9 */

    ncp_uint64_t pduSegAddr3       ;     /* Word 10-11 */

    ncp_uint64_t pduSegAddr4       ;     /* Word 12-13 */

    ncp_uint64_t pduSegAddr5       ;     /* Word 14-15 */
#else
    unsigned poolID                :6;  /* Word 0 */
    unsigned reserved1             :2;
    unsigned ptrCnt                :3;
    unsigned reserved0             :9;
    unsigned pduBlockSz5           :2;
    unsigned pduBlockSz4           :2;
    unsigned pduBlockSz3           :2;
    unsigned pduBlockSz2           :2;
    unsigned pduBlockSz1           :2;
    unsigned pduBlockSz0           :2;


    unsigned reserved2             :32;     /* Word 1 */

    ncp_uint64_t pduSegAddr0       ;     /* Word 2-3 */

    ncp_uint64_t pduSegAddr1       ;     /* Word 4-5 */

    unsigned reserved3          :32;     /* Word 6 */

    unsigned reserved4          :32;     /* Word 7 */

    ncp_uint64_t pduSegAddr2       ;     /* Word 8-9 */

    ncp_uint64_t pduSegAddr3       ;     /* Word 10-11 */

    ncp_uint64_t pduSegAddr4       ;     /* Word 12-13 */

    ncp_uint64_t pduSegAddr5       ;     /* Word 14-15 */

#endif
} ncp_ncaV2_task_dealloc_data_t;

typedef struct ncp_ncaV2_task_completion_plus_deallocdata_s
{
#ifdef NCP_BIG_ENDIAN
    unsigned templateID          :8;    /* Word 0 */
    unsigned QID                 :8;
    unsigned pduSize            :16;

    unsigned reserved0           :6;    /* Word 1 */
    unsigned dstID_9_0          :10;
    unsigned reserved1           :1;
    unsigned priority            :3;
    unsigned TOID               :12;

    ncp_uint32_t reserved2[8]      ;   /* Words 2..9 */

    unsigned pduBlockSz0        :2;     /* Word 10 */
    unsigned pduBlockSz1        :2;
    unsigned pduBlockSz2        :2;
    unsigned pduBlockSz3        :2;
    unsigned pduBlockSz4        :2;
    unsigned pduBlockSz5        :2;
    unsigned reserved3          :9;
    unsigned ptrCnt             :3;
    unsigned reserved5          :2;
    unsigned poolID             :6;


    unsigned reserved6          :32;     /* Word 11 */

    ncp_uint64_t pduSegAddr0       ;     /* Word 12-13 */

    ncp_uint64_t pduSegAddr1       ;     /* Word 14-15 */

    unsigned reserved7          :32;     /* Word 16 */

    unsigned reserved8          :32;     /* Word 17 */

    ncp_uint64_t pduSegAddr2       ;     /* Word 18-19 */

    ncp_uint64_t pduSegAddr3       ;     /* Word 20-21 */

    ncp_uint64_t pduSegAddr4       ;     /* Word 22-23 */

    ncp_uint64_t pduSegAddr5       ;     /* Word 24-25 */
#else
    unsigned pduSize            :16;    /* Word 0 */
    unsigned QID                 :8;
    unsigned templateID          :8;

    unsigned TOID               :12;     /* Word 1 */
    unsigned priority            :3;
    unsigned reserved1           :1;
    unsigned dstID_9_0          :10;
    unsigned reserved0           :6;

    ncp_uint32_t reserved2[8]      ;   /* Words 2..9 */

    unsigned poolID             :6;    /* Word 10 */
    unsigned reserved5          :2;
    unsigned ptrCnt             :3;
    unsigned reserved3          :9;
    unsigned pduBlockSz5        :2;
    unsigned pduBlockSz4        :2;
    unsigned pduBlockSz3        :2;
    unsigned pduBlockSz2        :2;
    unsigned pduBlockSz1        :2;
    unsigned pduBlockSz0        :2;

    unsigned reserved6          :32;     /* Word 11 */

    ncp_uint64_t pduSegAddr0       ;     /* Word 12-13 */

    ncp_uint64_t pduSegAddr1       ;     /* Word 14-15 */

    unsigned reserved7          :32;     /* Word 16 */

    unsigned reserved8          :32;     /* Word 17 */

    ncp_uint64_t pduSegAddr2       ;     /* Word 18-19 */

    ncp_uint64_t pduSegAddr3       ;     /* Word 20-21 */

    ncp_uint64_t pduSegAddr4       ;     /* Word 22-23 */

    ncp_uint64_t pduSegAddr5       ;     /* Word 24-25 */

#endif
} ncp_ncaV2_task_completion_plus_deallocdata_t;


/* NCA V2 Output Queue Aux Data - sw managed,  and only used if CPU managed pool */
typedef struct
{
    ncp_uint32_t                cmdCode;
    volatile ncp_uint64_t       *p_oPCQentry;
    ncp_int32_t                 ptrCnt;
    ncp_uint64_t                pduSegAddr0;
    ncp_uint64_t                pduSegAddr1;
    ncp_uint64_t                pduSegAddr2;
    ncp_uint64_t                pduSegAddr3;
    ncp_uint64_t                pduSegAddr4;
    ncp_uint64_t                pduSegAddr5;
    ncp_task_send_done_fn_t     clientFreeFn;
    void                      * clientFreeFnArg;
} ncp_task_ncaV2_oPCQ_aux_data_t;


/*
 * AXMncaV2 Specific Data Structures Used By The CPU and MME.
 * The MME is producer,  and the CPU is the consumer.
 * The tasks being allocated may be VP managed,  or may have been
 * specifically provided by the CPU and thereafter managed by hardware.
 * Note that even though the MME produces that tasks that are
 * consumed (allocated) by the CPU,  these tasks are deallocated via
 * a NCA output PCQ.
 */

typedef struct ncp_ncaV2_mme_mPCQ_entry_s
{
    ncp_uint64_t  taskAddr;     /* taskAddr*/  /* Word 0-1 */
} ncp_ncaV2_mme_mPCQ_entry_t;

/* Defect 44455: write additional register values */
/* TODO: Are these available in new RDL-generated header files? */

typedef struct ncp_ncaV2_base_addr_max_dyn_register_s
{
#ifdef NCP_BIG_ENDIAN
    unsigned base_addr_h           :32;
    unsigned base_addr_l           :32;
    unsigned max_dynamic_h         :32;
    unsigned max_dynamic_l         :32;
#else
    unsigned base_addr_h           :32;
    unsigned base_addr_l           :32;
    unsigned max_dynamic_h         :32;
    unsigned max_dynamic_l         :32;
#endif
} ncp_ncaV2_base_addr_max_dyn_register_t;

typedef struct ncp_ncaV2_base_addr_register_s
{
#ifdef NCP_BIG_ENDIAN
    unsigned base_addr_256_h       :32;
    unsigned base_addr_256_l       :32;
    unsigned base_addr_2k_h        :32;
    unsigned base_addr_2k_l        :32;
    unsigned base_addr_16k_h       :32;
    unsigned base_addr_16k_l       :32;
    unsigned base_addr_64k_h       :32;
    unsigned base_addr_64k_l       :32;
#else
    unsigned base_addr_256_h       :32;
    unsigned base_addr_256_l       :32;
    unsigned base_addr_2k_h        :32;
    unsigned base_addr_2k_l        :32;
    unsigned base_addr_16k_h       :32;
    unsigned base_addr_16k_l       :32;
    unsigned base_addr_64k_h       :32;
    unsigned base_addr_64k_l       :32;
#endif
} ncp_ncaV2_base_addr_register_t;


/* 55XX Specific Data Structures - END */

/* ==================================
 * Software PCQ State
 * ==================================
*/

typedef struct iPCQ_info_s {
    ncp_uint64_t                iPcqOffset;
    ncp_task_ncaV2_iPCQ_entry_t *pIPCQentry;
    ncp_uint16_t                ipcqConsumerIdx;
    ncp_uint16_t                lastProducerIdx;
    ncp_bool_t                  multiSegRxOK;
    ncp_task_completion_mode_t  rxTaskCompletionMode;
    ncp_task_ncaV2_recv_buf_t    *pSwAutoTaskCompletionTask;
    ncp_int32_t                  wrrWeight;
} iPCQ_info_t;

/* H/W requires 16B alignment */
typedef struct {
    ncp_uint32_t completionData_W0;
    ncp_uint32_t completionData_W1;
    ncp_uint32_t completionData_W2; /* unused, but must be present */
    ncp_uint32_t completionData_W3; /* unused, but must be present */
} ncp_task_ncav2_min_completion_data_t;

typedef struct oPCQ_info_s {
    /* oPCQ housekeeping info */
    ncp_uint64_t                     oPcqOffset;
    ncp_task_ncaV2_oPCQ_entry_t      *pOPCQentry;
    ncp_uint16_t                     opcqProducerIdx;
    /* auxData housekeeping info */
    ncp_uint16_t                     auxEntriesAvail;
    ncp_task_ncaV2_oPCQ_aux_data_t   *pAuxWriteEntry;
    ncp_task_ncaV2_oPCQ_aux_data_t   *pAuxReadEntry;
    ncp_task_ncaV2_oPCQ_aux_data_t   *pLastAuxEntry;
    /* memPool associated with this oPCQ - cached here for performance */
    /* cache optimization info */
    ncp_task_ncaV2_oPCQ_entry_t *nxtCacheLoadOPCQentry;
    ncp_task_ncaV2_oPCQ_entry_t *maxCacheLoadOPCQentry;
    ncp_uint32_t                    copyPool;
    ncp_task_ncav2_min_completion_data_t *pCompletionData;
} oPCQ_info_t;

typedef struct cPCQ_info_s {
    ncp_uint64_t           cPcqOffset;
    ncp_task_cPCQ_entry_t *pCPCQentry;
    ncp_uint32_t blockSize;
} cPCQ_info_t;

typedef union ncp_pcq_info_u {
    iPCQ_info_t ipcq_info;
    oPCQ_info_t opcq_info;
    cPCQ_info_t cpcq_info;
} ncp_pcq_info_t;


/* oPCQ gather-mode descriptors, entries, table */
typedef struct ncp_task_oPCQ_desc_entry_s
{
#ifdef NCP_BIG_ENDIAN
    unsigned   dataSegSz            :16;    /* Word 0 */
    unsigned   reserved1            :10;
    unsigned   dataSegAddr_37_32    :6;
    unsigned   dataSegAddr_31_0     :32;    /* Word 1 */
#else
    unsigned   dataSegAddr_37_32    :6;     /* Word 0 */
    unsigned   reserved1            :10;
    unsigned   dataSegSz            :16;
    unsigned   dataSegAddr_31_0     :32;    /* Word 1 */
#endif
} ncp_task_oPCQ_desc_entry_t;

#define NCA_OPCQ_MAX_GATHER_SEGS 16
typedef struct ncp_task_oPCQ_desc_table_s
{
    ncp_task_oPCQ_desc_entry_t  seg[NCA_OPCQ_MAX_GATHER_SEGS];
} ncp_task_oPCQ_desc_table_t;


typedef struct ncp_task_oPCQ_descs_s {
    ncp_task_oPCQ_desc_table_t *descEntries;
} ncp_task_oPCQ_descs_t;



typedef struct ncp_task_pcq_s {

    ncp_uint32_t                cookie;

    ncp_uint8_t                 ncaQueueId;
    ncp_uint8_t                 grpId;
    ncp_uint8_t                 pcqUseCnt;
    ncp_uint32_t                nEntries;
    ncp_uint32_t                nEntriesMinusOne;
    volatile ncp_uint16_t       *pConsumerIdx;
    volatile ncp_uint16_t       *pProducerIdx;
    ncp_uint16_t                pcqToggleBitVal;
    void                        *pPCQbase;
    struct ncp_pvt_task_hdl_s   *ownerTaskHdl;
    void                        *bufferCpuAddr;
    ncp_uint64_t                bufferBusAddr;
    ncp_uint64_t                baseBusAddr;
    ncp_bool_t                  uMode;
    ncp_pcq_info_t              u;  /* union containing tighltly coupled info for the queue,   varies by queue type */
} ncp_task_pcq_t;

/*
 * Private receive queue data structure
 */
typedef struct ncp_pvt_task_recv_queue_s
{
    ncp_uint32_t                        cookie;
    struct ncp_pvt_task_recv_queue_s    *next;
    ncp_task_pcq_t                      *taskQueue;
    ncp_uint8_t                         recvQueueId;
    ncp_uint8_t                         ncaQueueId;
    ncp_uint16_t                        weight;
    ncp_uint16_t                        wrrCounter;
} ncp_pvt_task_recv_queue_t;


/* ==========================================================
 * NCA QUEUE Group Config Related Software Data Structures
 * ==========================================================
 */

typedef struct {
    ncp_uint32_t         id;                                /* groupId or 0xFF(unused)   */
    ncp_uint64_t         ncaPgitOffset;
    ncp_dev_nca_pgit_t  *pNca_pgit;                         /* NCA PCQ group index table */
    ncp_uint64_t         cpuPgitOffset;
    ncp_dev_cpu_pgit_t  *pCpu_pgit;                         /* NCA PCQ group index table */
    ncp_uint32_t        cpu_pgit_bus_addr;
    ncp_nca_cpu_ids_t   cpuId;                              /* from cfg */
    ncp_uint64_t        baseAddress;                        /* from cfg */
    ncp_uint32_t        grpMemSize;                         /* from cfg */
    ncp_uint32_t        first_iPCQ_inGroup;                 /* linear id of 1st iPCQ in grp */
    ncp_uint32_t        num_iPCQs;                          /* num configured in this group  */
    ncp_uint32_t        num_oPCQs;                          /* num configured in this group  */
    ncp_uint32_t        num_cPCQs;                          /* num configured in this group  */
    ncp_int32_t         grpDomain;                          /* which domain manages this grp? */
    ncp_uint32_t        pgitNormalLoadTimer;
    ncp_uint32_t        pgitNormalUploadTimer;
    ncp_uint32_t        pgitNcaEventLoadTimer;
    ncp_int32_t         taskArrivalsPerInterrupt;
    ncp_int32_t         taskArrivalInterruptMaxDelayTime;
    ncp_uint32_t        pgitNcaEventUploadTimer;
    ncp_uint32_t        pgitIpcqEmptyToNotEmptyLoadTimer;
    ncp_uint32_t        pgitCpuEventLoadTimer;
    ncp_int32_t         pgitTaskArrivalEventThreshold;
    ncp_int32_t         pgitOutputEventThreshold;
 } ncp_task_v2_pcq_grp_t;

typedef struct ncp_task_mme_allocator_if_s
{
    ncp_bool_t              queueValid;          /* blocks actually configured?      */
    volatile ncp_uint64_t   *readP_swVA;         /* points to 64b entry in mPQ array */
    ncp_uint64_t            *readP_swVA_max_val; /* For wrap test                    */
    volatile ncp_uint64_t   *readP_hwVA; /* ptr to loc conatining PA of entry        */
    ncp_uint64_t            readP_hw_indx0_val;  /* base PA val to use when wraps    */
    ncp_uint64_t            *entries_baseVA;     /* base VA value to use when wraps  */
} ncp_task_mme_allocator_if_t;

typedef struct ncp_task_mme_allocator_s
{
    ncp_int32_t  id;
    ncp_bool_t   valid;     /* is block size configured ?  */
    ncp_int32_t  useCnt;
    ncp_raw_addr_t baseVA;
    ncp_int64_t  cfgOffset; /* From domain bundle start    */
    ncp_task_mme_allocator_if_t allocIF[4];
} ncp_task_mme_allocator_t;


/* =================================================
 * Thread Queue Set Related Data Structures
 * =================================================
 */

typedef struct ncp_nca_thread_queue_set_s {
    ncp_uint32_t id;                            /* id == 0xff -> not configured */
    ncp_uint32_t grpId;                         /* group associated with this thread queue set */
    ncp_int32_t              tqsDomain;         /* What domain is parent queue group in? */
    int                      qsUseCnt;          /* current user count for this queue set */
    ncp_task_mutex_t         *qsLock;         /* shared queue mutex */
    ncp_nca_qs_access_mode_t qsAccessMode;      /* free, exclusive, raw, shared */
    ncp_bool_t               sendMutexDisabled; /* run-time override of above lock */
    ncp_uint32_t  first_iPCQ_id;                /* 1st iPCQ linear ID in this set */
    ncp_uint32_t  first_iPCQ_inGroup;           /* 1st iPCQ linear ID in the group which contains this thread queue set */
    ncp_uint32_t  num_iPCQs_in_queueSet;        /* Num iPCQs in this queueSet, could be zero   */
    ncp_task_pcq_t *p_oPCQ;                      /* hardware output queue */
    ncp_task_pcq_t *p_cPCQ;                      /* hardware configuration queue */
    ncp_uint32_t poolID;                        /* Which task memory pool */
    ncp_bool_t                 uMode;
    ncp_bool_t                 requiresCompletionData;
    ncp_int32_t                numAllocators;
    ncp_task_mme_allocator_t   *mme;
} ncp_nca_thread_queue_set_t;

/* ====================================================================
 * 3400/2500 style CPU managed pool.
 * May change as we enahance the interface to support multiple pools
 * ====================================================================
 */

#define NCP_POOL_KEY 0xC001BABE

typedef struct ncp_task_ncaV2_cpu_managed_buffer_pool_s {
    ncp_dev_hdl_t     devHdl;                                       /* Handle to driver that provided this reserved ram */
    ncp_task_bufflist_t  buffListArray[NCP_TASK_NUM_BUFF_SIZES];    /* the lists and data structures used to manage pool */
} ncp_task_ncaV2_cpu_managed_buffer_pool_t;

typedef struct ncp_task_ncaV2_vp_managed_buffer_pool_s {
    /* FIXME */
    /* Add mPCQ allocators here! */
} ncp_task_ncaV2_vp_managed_buffer_pool_t;

typedef union ncp_task_ncaV2_pool_types_union_u
{
    ncp_task_ncaV2_cpu_managed_buffer_pool_t cpu;
    ncp_task_ncaV2_vp_managed_buffer_pool_t  vp;
} ncp_task_ncaV2_pool_types_union_t;

typedef struct ncp_task_ncaV2_pool_s{
    ncp_uint32_t      poolKey;             /* for validation */
    ncp_int32_t       poolID;              /* ID Of thisPool           */
    ncp_bool_t        isCpuManagedPool;    /* CPU Managed? or VP/MME managed? */
    ncp_int32_t       useCnt;              /* number of active clients */
    ncp_task_mutex_t  *poolLock;           /* global lock for *this* pool */
    ncp_task_ncaV2_pool_types_union_t u;
    /* Begin - From ASE config */
    ncp_uint64_t      pool_PA;
    ncp_uint64_t      pool_Size;
    ncp_raw_addr_t    pool_VA;
    ncp_raw_addr_t    pool_EndVA;
    ncp_bool_t        uMode;
    int               tqsRefCount;
    void              *blocksVA[NCP_TASK_NUM_BUFF_SIZES];
    void              *blocksVAend[NCP_TASK_NUM_BUFF_SIZES];
    ncp_uint64_t      blocksPA[NCP_TASK_NUM_BUFF_SIZES];
    int               numBlocks[NCP_TASK_NUM_BUFF_SIZES];
    int               numBlocksRxReserve[NCP_TASK_NUM_BUFF_SIZES];
    /* End - From ASE */
} ncp_task_ncaV2_pool_t;

/* =======================================================================
 * Private PCQ Related MACROS
 * =======================================================================
 */

/*
 * Advance producer index of PCQ
 */

#define NCP_DEV_NCA_PCQ_PIDX_ADVANCE(pcq)               \
({                                                      \
    ncp_uint16_t prod;                                  \
    NCP_SYSMEM_BARRIER();                               \
    prod = SWAP_16(*(pcq)->pProducerIdx);               \
    if ( prod  == (pcq->nEntries - 1))                  \
       prod = 0;                                        \
    else                                                \
       prod+=1;                                         \
       *(pcq)->pProducerIdx = SWAP_16(prod);            \
   })


/*
 * Advance consumer index of PCQ
 */

#define NCP_DEV_NCA_PCQ_CIDX_ADVANCE(pcq)               \
({                                                      \
    NCP_SYSMEM_BARRIER();                               \
    ncp_uint16_t consumer;                              \
    consumer = SWAP_16(*(pcq)->pConsumerIdx);           \
    if ( consumer == (pcq->nEntries - 1))               \
       consumer = 0;                                    \
    else                                                \
        consumer+=1;                                    \
        *(pcq)->pConsumerIdx = SWAP_16(consumer);       \
})


/*
 * Is the PCQ full?
 */

#define NCP_DEV_NCA_PCQ_IS_FULL(pcq)                                \
({                                                                  \
    ncp_uint16_t prod, consumer;                                    \
    prod = SWAP_16(*(pcq)->pProducerIdx);                           \
    consumer = SWAP_16 (*(pcq)->pConsumerIdx);                      \
    (((( prod + 1) & (pcq->nEntries - 1)) == consumer) ? TRUE : FALSE); \
})

/*
 * Is the PCQ empty?
 */

#define NCP_DEV_NCA_PCQ_IS_EMPTY(pcq)            \
({                                               \
    ncp_uint16_t prod, consumer;                 \
    prod = SWAP_16(*(pcq)->pProducerIdx);        \
    consumer = SWAP_16 (*(pcq)->pConsumerIdx);   \
    ((prod == consumer) ? TRUE : FALSE);         \
})

/*
 * Advance the Producer Index
 */

#define NCP_DEV_NCA_PCQ_PRODUCER_IDX(pcq)   \
({                                          \
    ncp_uint16_t prod;                      \
    prod = SWAP_16(*(pcq)->pProducerIdx);   \
    prod;                                   \
})

/*
 * Advance the Consumer Index
 */

#define NCP_DEV_NCA_PCQ_CONSUMER_IDX(pcq)         \
({                                                \
    ncp_uint16_t consumer;                        \
    consumer = SWAP_16(*(pcq)->pConsumerIdx);     \
    consumer;                                     \
})



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

/* =================================
 * 55xx specific PCQ tests
 * =================================
 */
 #define NCP_TASK_55xx_OPCQ_FULL(_pcq, _producerIdx, _poolID) \
 ({                                                    \
    ncp_ncaV2_task_oPCQ_entry_generic_t *_pNextEntry;  \
    int _idx = _producerIdx + 1;                      \
    if (_idx != (_pcq)->nEntries)                   \
    {                                               \
        _pNextEntry = (ncp_ncaV2_task_oPCQ_entry_generic_t *) \
            (_pcq)->u.opcq_info.pOPCQentry + 1;              \
    }                                               \
    else                                            \
    {                                               \
        _pNextEntry = (ncp_ncaV2_task_oPCQ_entry_generic_t *) \
            (_pcq)->pPCQbase;                              \
    }                                               \
    if (0 == (_pcq)->u.opcq_info.auxEntriesAvail)   \
    {                                               \
        ncp_task_v2_process_oPCQ_auxData(_pcq,NULL,0,NULL,_poolID); \
    }                                               \
    (((( 0 == (_pcq)->u.opcq_info.auxEntriesAvail))  \
        || (0LL != (*(ncp_uint64_t *)(_pNextEntry))))   \
    ? TRUE : FALSE);                                \
})


#define NCP_TASK_55xx_UPDATE_OPCQ_PRODUCER_IDX(_pOPCQ, _pIdx, _pEntry, _cmd, _pAuxData, _poolID)       \
{                                                                           \
    if (NCP_TASK_IS_CPU_POOL(_poolID))                                      \
    {                                                                       \
        ncp_task_v2_process_oPCQ_auxData(                                   \
                _pOPCQ,                                                     \
                (ncp_ncaV2_task_oPCQ_entry_generic_t *)_pEntry,             \
                _cmd,                                                       \
                _pAuxData,                                                  \
                _poolID);                                                   \
    }                                                                       \
    ++_pIdx;                                                                \
    if (0 == (_pIdx & _pOPCQ->nEntriesMinusOne))                            \
    {                                                                       \
        if (NCP_TASK_NCAV2_USES_WRAP_BIT)                                   \
        {                                                                   \
            if (0 != _pOPCQ->pcqToggleBitVal)                               \
            {                                                               \
                _pIdx                                                       \
                    = _pOPCQ->pcqToggleBitVal                               \
                    = 0;                                                    \
            }                                                               \
            else                                                            \
            {                                                               \
                _pIdx                                                       \
                    = _pOPCQ->pcqToggleBitVal                               \
                    = NCP_TASK_NVAV2_PGIT_WRAP_BIT;                         \
            }                                                               \
        }                                                                   \
        else                                                                \
        {                                                                   \
            _pIdx = 0;                                                      \
        }                                                                   \
        _pOPCQ->u.opcq_info.pOPCQentry = _pOPCQ->pPCQbase;                  \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        _pOPCQ->u.opcq_info.pOPCQentry++;                                   \
    }                                                                       \
    NCP_SYSMEM_BARRIER();  /* enforce write ordering */                     \
    *(_pOPCQ->pProducerIdx) = SWAP_16(_pIdx);                               \
    _pOPCQ->u.opcq_info.opcqProducerIdx = _pIdx;                            \
}

/* ======================================
 * VA->PA and PA->VA conversions
 * ======================================
 */

#define NCP_TASK_VA_2_PA(_va, _poolID) \
ncp_task_v2_va_2_pa(((void *)(ncp_raw_addr_t)(_va)), _poolID)

#define NCP_TASK_PA_2_VA(xhigh, xlow, _poolID) \
ncp_task_v2_pa_2_va((ncp_uint32_t)(xhigh), (ncp_uint32_t)xlow, _poolID)

/*
 * Macro to convert the offset associated with a domain bundle object to its mapped VA
 */

/* =================================
 * Swapping for queue entries
 * =================================
 */

/*
 * for the oPCQ entry we only worry about swapping the
 * first four words.  The parameters will be written later
 * (they don't need to be swapped) and we don't need to
 * worry about the last four words of padding.
 */
#define NCP_TASK_OPCQ_ENTRY_PUT(_dest, _src)         \
    NCP_DEV_FOUR_WORD_SWAP(_dest, _src)

#define NCP_DEV_OPCQ_ENTRY_GET(_dest, _src)         \
    NCP_DEV_FOUR_WORD_SWAP(_dest, _src)

/*
 * swap macro for the receive buffer header
 * --- NOTE ---
 * Disable - optimization actually makes performance worse it must have
 * beneficial side effect regarding cache hits later in the code path
 * be
 */
#define NCP_DEV_RECV_BUFFER_HDR_GET(_dest, _src)         \
    NCP_DEV_FOUR_WORD_SWAP(_dest, _src)

#define NCP_DEV_RECV_BUFFER_HDR_PUT(_dest, _src)         \
    NCP_DEV_FOUR_WORD_SWAP(_dest, _src)

/*
 * copy the two-word TPCQ entry with appropriate byte-swapping
 */
#define NCP_DEV_TPCQ_ENTRY_PUT(_dest, _src)         \
    NCP_DEV_TWO_WORD_SWAP(_dest, _src)

#define NCP_DEV_TPCQ_ENTRY_GET(_dest, _src)         \
    NCP_DEV_TWO_WORD_SWAP(_dest, _src)

/*
 * copy the two-word IPCQ entry with appropriate byte-swapping
 */
#define NCP_DEV_IPCQ_ENTRY_PUT(_dest, _src)         \
    NCP_DEV_TWO_WORD_SWAP(_dest, _src)

#define NCP_DEV_IPCQ_ENTRY_GET(_dest, _src)         \
    NCP_DEV_TWO_WORD_SWAP(_dest, _src)


/* =======================================================
 * Task Completion S/W structs
 * =======================================================
 */

/*
 * typedef ncp_task_man_completion_list_element_t
 * brief   data structure used as to manage outstanding manual task completions owed
 */

typedef struct ncp_task_man_completion_list_element_s {
    struct ncp_task_man_completion_list_element_s *prev;
    struct ncp_task_man_completion_list_element_s *next;
    void *task;
    void *reserved;
}  ncp_task_man_completion_list_element_t;

/* ====================================================================
 * typedef ncp_pvt_task_hdl_t
 * brief   data structure used as container for receive handle data
 * ====================================================================
 */
typedef struct ncp_pvt_task_hdl_s
{
  ncp_uint32_t                  cookie;
  struct ncp_pvt_task_hdl_s     *next;              /* Link to next task handle */
  ncp_hdl_t                     ncpHdl;
  ncp_dev_hdl_t                 dev;                /* dev */
  ncp_int32_t                   threadQueueSetId;   /* Logical TQS # */
  ncp_nca_thread_queue_set_t    *pThreadQueueSet;   /* Pointer to thread queue set struct */
  ncp_task_ncaV2_pool_t          *poolHdl;           /* Pointer to buffer pool control */
  ncp_task_mme_allocator_t       *mmeAllocator;
  /*
   * fields related to output queue(s) abstraction
   */
  ncp_task_pcq_t        *sendQueue;
  ncp_task_pcq_t        *completionQueue;
  ncp_task_pcq_t        *rxBufferQueue;
#if 0
  ncp_task_pcq_t        *configurationQueue;
#endif

  /*
   * fields related to input PCQ(s)
   */
  ncp_pvt_task_recv_queue_t *currRecvPtr;
  ncp_uint32_t              inCriticalSection;
  ncp_uint64_t              myIPCQmask;
  ncp_task_man_completion_list_element_t *firstManCompletion;
  ncp_task_man_completion_list_element_t *lastManCompletion;
  ncp_bool_t                orderedTaskCompletion;
  ncp_uint8_t               poolID;
} ncp_pvt_task_hdl_t;


typedef ncp_pvt_task_hdl_t ncp_pvt_task_lite_hdl_t;

/* =========================================================
 * Primary hardware interface related data structures
 * =========================================================
 */

/*
 * NCA Input Queue
 */

typedef struct ncp_nca_queue_s {
    ncp_task_ncaV2_iPCQ_entry_t  *entries;
} ncp_nca_input_queue_t;

/*
 * NCA Output Queue
 */

typedef struct ncp_nca_output_queue_s {
    ncp_task_ncaV2_oPCQ_entry_t *entries;
} ncp_nca_output_queue_t;


/*
 * Config queue
 */

typedef struct ncp_nca_cfg_queue_block_s {
    ncp_uint8_t blkdata[1024];  /* <---- hardcoded */
} ncp_cfg_queue_block_t;


typedef struct ncp_nca_hwif_s {

    /*
     * Begin H/W related structs
     */
    ncp_dev_nca_pgit_ptr_t      nca_pgit[NCP_X7_NUM_PCQ_GROUPS];
    ncp_dev_cpu_pgit_ptr_t      cpu_pgit[NCP_X7_NUM_PCQ_GROUPS];
    ncp_nca_input_queue_t       NcaInputQueues[NCP_X7_NUM_HW_INPUT_QUEUES];
    ncp_nca_output_queue_t      NcaOutputQueues[NCP_X7_NUM_HW_OUTPUT_QUEUES];
    ncp_task_cPCQ_entry_t       NcaCfgQueues[NCP_X7_NUM_HW_CONFIG_QUEUES];
    ncp_cfg_queue_block_t       NcaCfgQueueBlocks[8 ];  /* <---- hardcoded */
} ncp_nca_hwif_t;

typedef struct ncp_task_v2_domain_memory_map_s {
    /*
     * The domain bundle contains all pgits/queues used by this domain,
     * and does not need to be fixed to any particular VA
     */
    ncp_uint64_t                        domainBundle_PA;
    ncp_raw_addr_t                      domainBundle_VA;
    ncp_uint64_t                        domainBundle_Size;
} ncp_task_v2_domain_memory_map_t;

/* ===============================================================================
 * Task I/O data structure that can exist in cached memory for both external
 * and internal host configurations
 * ===============================================================================
 */
typedef struct ncp_nca_task_s {
    ncp_uint32_t                        cookie1;
    ncp_bool_t                          shutdown;                                   /* <--- Do *NOT* move   */
    ncp_task_v2_domain_memory_map_t     domainMemMap;                               /* From ASE             */

    /* ncp_dev_gsm_info_t                  myGSMinfo;           */
    /* ncp_dev_gsm_info_t                  warmRestart_GSMinfo; */
    ncp_nca_hwif_t                      hw;
    /* ncp_raw_addr_t                      warmRestartGSM_WaterMark;     */
    /* ncp_raw_addr_t                      warmRestartTaskGSM_WaterMark; */

    ncp_uint32_t                            *otbpInfo_VA; /* memory based otask backpressure bits (written by NCA) */
    ncp_uint64_t                            otbpInfo_Offset;
    ncp_taskQ_IDs_t                         perNca_recvQ_IDs[NCP_X7_NUM_HW_INPUT_QUEUES]; /* 0..255 for each nca Queue */
    ncp_recv_queue_level1_bind_wrapper_t    *ncaQueueToPipelineBindings[NCP_X7_NUM_HW_INPUT_QUEUES];   /* per ncaQ bindings */
    /* end of uMode/kmode specific addresses */
    ncp_task_v2_pcq_grp_t                   pcq_grp[NCP_X7_NUM_PCQ_GROUPS];
    ncp_nca_thread_queue_set_t              threadQueueSets[NCP_X7_NUM_THREAD_QUEUESETS];
    ncp_task_pcq_t
        iPCQs[NCP_X7_NUM_HW_INPUT_QUEUES];     /* task input            */
    ncp_task_pcq_t
        oPCQs[NCP_X7_NUM_HW_NONINPUT_QUEUES];  /* task output           */
    ncp_task_pcq_t
        cPCQs[NCP_X7_NUM_HW_NONINPUT_QUEUES];  /* configuration         */

    ncp_task_ncaV2_oPCQ_aux_data_t       *outputQueueAuxData[NCP_X7_NUM_HW_OUTPUT_QUEUES];

    ncp_task_ncaV2_pool_t                taskMemoryPool[NCP_X7_NUM_TASK_MEMORY_POOLS];

    ncp_task_stats_t                    myTaskStats;
    int                                 sizeofKernelLock;
    ncp_task_mutex_t                    *taskIoResourceLock;
    ncp_uint8_t                         ncpId;  /* Needed when perform ops w/o task handle */
    ncp_bool_t                          inWarmRestart;
    ncp_bool_t                          warmRestartEnabled;
    ncp_bool_t                          useInterrupts;
    ncp_bool_t                          kernelModeConfigured;
    ncp_int32_t                         myDomain;
    ncp_bool_t                          inUmode; /* are we in user mode? */
    ncp_bool_t                          domainIsInternal; /* AXI or SYSMEM? */
    ncp_uint32_t                        activeGrpMask;
    ncp_uint32_t                        allGrpMask;
#ifdef DBG_KMODE_INTS
    /* BEGIN K-MODE INTERRUPT DEBUG */
    ncp_uint32_t                         dbg_rx_pkts_dequed;
    ncp_uint32_t                         dbg_rxIntsEnabled;
    ncp_uint32_t                         dbg_rxIntsDisabled;
    ncp_uint32_t                         dbg_txIntsEnabled;
    ncp_uint32_t                         dbg_txIntsDisabled;
    ncp_uint32_t                         dbg_compIntsEnabled;
    ncp_uint32_t                         dbg_compIntsDisabled;
    ncp_uint32_t                         dbg_txQueueFull;
    ncp_uint32_t                         dbg_compQueueFull;
    ncp_uint32_t                         dbg_grp0_rx_events_dispatched;
    ncp_uint32_t                         dbg_grp0_rx_events_caught;
#endif
    /* END K-MODE INTERRUPT DEBUG */
#ifdef NCP_TASK_DBG_NVM_CORRUPTION
    ncp_nvm_dbg_t                        *nvm_dbg_curr_allocated_lst;
    ncp_nvm_dbg_t                        *nvm_dbg_allocated_lst;
    ncp_task_mutex_t                        *nvm_dbgLock;
#endif
    volatile ncp_bool_t                  startlockTestOK; /* DEBUG !!!! */
#ifdef NCP_TASK_DBG_BUFFERS
    ncp_task_mutex_t                    *onNcaLock;       /* DEBUG !!!! */
    volatile void **                     onNcaList; /* DEBUG !!!! */
    volatile void **                     allocated; /* DEBUG !!!! */
#endif
    struct ncp_pvt_task_hdl_s           *activeTaskHdlList;
    ncp_uint32_t                         myInputPCQbitMask;
    ncp_mme_pool_t MMEpoolInfo[NCP_X7_NUM_TASK_MEMORY_POOLS];
    ncp_uint32_t                         cookie2;
} ncp_task_ncaV2_t;

/* ================================
 * NCA structure in NVM
 * ================================
 */


typedef struct ncp_nca_s {
    ncp_uint32_t            cookie;
    ncp_task_ncaV2_t        *myNcpNcaTaskState;  /* in NVM for 55xx */
} ncp_nca_t;

#ifdef NCP_TASK_NCA_GLOBALS
    extern ncp_t gNCP;
ncp_dev_t       gDEV = { { 0 } };                   /* UBOOT */
    ncp_dev_hdl_t   ncp_dev_hdls[NCP_MAX_DEVS] = { &gDEV }; /* UBOOT */
    int     memPoolMapped[NCP_X7_NUM_TASK_MEMORY_POOLS] = {0};
    ncp_task_ncaV2_t *pNcpNcaV2_TaskSwState = NULL;    /* task I/O module state              */
    void           *pNcpNcaV2_domainBundle = NULL;        /* allocated structs used by hardware */
#if 0
    ncp_bool_t ncp_nca_debug = 0;
    ncp_raw_addr_t  gpNcaWaterMark=0; /* used for dynamic allocation of memory within the 32MB GSM */
    ncp_raw_addr_t  gpNcaCacheableWaterMark=0; /* used for dynamic allocation of cacheable memory within the 32MB GSM */
#ifdef NCP_KERNEL
    ncp_pvt_task_hdl_t *kernelTaskHdl=NULL;
#endif
#else  /* 0 */
    extern ncp_bool_t ncp_nca_debug;
    extern ncp_raw_addr_t  gpNcaWaterMark; /* used for dynamic allocation of memory within the 32MB GSM */
    extern ncp_raw_addr_t  gpNcaCacheableWaterMark; /* used for dynamic allocation of cacheable memory within the 32MB GSM */
#ifdef NCP_KERNEL
    extern ncp_pvt_task_hdl_t *kernelTaskHdl;
#endif
#endif /* 0 */
#else
    extern ncp_dev_hdl_t   ncp_dev_hdls[]; /* UBOOT */
    extern ncp_t           gNCP;           /* UBOOT */
    extern ncp_dev_t       gDEV;           /* UBOOT */
    extern int      memPoolMapped[];
    extern ncp_task_ncaV2_t *pNcpNcaV2_TaskSwState; /* task I/O module state */
    extern void             *pNcpNcaV2_domainBundle;        /* allocated structs used by hardware */
    extern ncp_bool_t     ncp_nca_debug;
    extern ncp_raw_addr_t   gpNcaWaterMark; /* used for dynamic allocation of memory within the 32MB GSM */
    extern ncp_raw_addr_t   gpNcaCacheableWaterMark; /* used for dynamic allocation of cacheable memory within the 32MB GSM */
#ifdef NCP_KERNEL
    extern  ncp_pvt_task_hdl_t *kernelTaskHdl;
#endif
#endif /* NCP_TASK_NCA_GLOBALS */

#endif /* __ncp_task_pvt_axm55xx_h__ */
