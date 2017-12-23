
#ifndef __ncp_pcq_h__
#define __ncp_pcq_h__

#ifdef __cplusplus
extern "C" { 
#endif

#include "uboot/ncp_types.h"

typedef struct ncp_ipcq_s
{
#ifdef NCP_BIG_ENDIAN
    ncp_uint64_t        taskAddress;

    ncp_uint64_t        reserved0:4;
    ncp_uint64_t        headerSize:1;
    ncp_uint64_t        reserved1:2;
    ncp_uint64_t        headerSeparate:1;
    ncp_uint64_t        reserved2:5;
    ncp_uint64_t        cmd:3;
    ncp_uint64_t        reserved3:4;
    ncp_uint64_t        pool:4;
    ncp_uint64_t        templateId:8;
    ncp_uint32_t        gid:8;
    ncp_uint32_t        reserved4:3;
    ncp_uint32_t        generation:1;
    ncp_uint32_t        reserved5:1;
    ncp_uint32_t        priority:3;
    ncp_uint32_t        qid:8;
    ncp_uint64_t        reserved6:8;
#else
    ncp_uint64_t        taskAddress;

    ncp_uint64_t        reserved6:8;
    ncp_uint32_t        qid:8;
    ncp_uint32_t        priority:3;
    ncp_uint32_t        reserved5:1;
    ncp_uint32_t        generation:1;
    ncp_uint32_t        reserved4:3;
    ncp_uint32_t        gid:8;
    ncp_uint64_t        templateId:8;
    ncp_uint64_t        pool:4;
    ncp_uint64_t        reserved3:4;
    ncp_uint64_t        cmd:3;
    ncp_uint64_t        reserved2:5;
    ncp_uint64_t        headerSeparate:1;
    ncp_uint64_t        reserved1:2;
    ncp_uint64_t        headerSize:1;
    ncp_uint64_t        reserved0:4;
#endif
} ncp_ipcq_t;

typedef ncp_ipcq_t ncp_ipcq_entry_t;

/* 
 * NCAV3 Commands - see cmd field in opcq entry 
 */
#define NCP_NCAV3_CMD_NOOP      0
#define NCP_NCAV3_CMD_SENDTH    1
#define NCP_NCAV3_CMD_RSVD1     2
#define NCP_NCAV3_CMD_ADPAH     3
#define NCP_NCAV3_CMD_ADPAE     4
#define NCP_NCAV3_CMD_RSVD2     5
#define NCP_NCAV3_CMD_IPCQ_DRAIN 6
#define NCP_NCAV3_CMD_CPCQ       7

/*
 * MREF bit is encoded in 4bit pool field
 */
#define NCP_NCAV3_MREF_POOL_BIT          0x8
#define NCP_NCAV3_ENCODED_POOL_BITS_MASK 0x7

/*
 * returnHeader field (RCCH)
 */
#define NCP_NCAV3_SENDTH_RCCH_DEC_REFCNT_RETURN_HDR 0       /* PE returns header with task */
#define NCP_NCAV3_SENDTH_RCCH_NOOP_REFCNT_KEEP_HDR  1       /* PE send task and keep copy of header ptr */

#define NCP_NCAV3_ADPAH_RCCH_DEC_REFCNT_RETURN_HDR 0       /* PE returns header with task */
#define NCP_NCAV3_ADPAH_RCCH_NOOP_REFCNT_KEEP_HDR  1       /* PE send task and keep copy of header ptr */

#define NCP_NCAV3_ADPAE_RCCH_NOOP   3                       /* no action - always use this value! */

/*
 * returnDATA field (RCCD)
 */
 
#define NCP_NCAV3_SENDTH_RCCD_DEC_REFCNT_RETURN_DATA 0         /* PE send task and return data */
#define NCP_NCAV3_SENDTH_RCCD_NOOP_REFCNT_KEEP_DATA  1         /* PE send task and keep a copy of data */    
#define NCP_NCAV3_SENDTH_RCCD_UNDEFINED              2         /* do not use! */
#define NCP_NCAV3_SENDTH_RCCD_NOOP                   3         /* no reference count operations on data ptrs */

#define NCP_NCAV3_ADPAH_RCCD_NOOP_REFCNT_RETURN_DATA 0         /* PE send task and return data */
#define NCP_NCAV3_ADPAH_RCCD_INC_REFCNT              1         /* PE send task and keep a copy of data */    
#define NCP_NCAV3_ADPAH_RCCD_DEC_REFCNT              2         /* decrement ref cnt on data ptrs */
#define NCP_NCAV3_ADPAH_RCCD_UNDEFINED               3         /* do not use */

#define NCP_NCAV3_ADPAE_RCCD_NOOP_REFCNT_RETURN_DATA 0         /* PE send task and return data */
#define NCP_NCAV3_ADPAE_RCCD_INC_REFCNT              1         /* increment refcntPE send task and keep a copy of data */    
#define NCP_NCAV3_ADPAE_RCCD_DEC_REFCNT              2         /* decrement ref cnt on data ptrs */
#define NCP_NCAV3_ADPAE_RCCD_UNDEFINED               3         /* do not use */

/*
 * quotaTransfer include header field (MQGC)
 */
#define NCP_NCAV3_SENDTH_MQGI_INCL_HDR   0          /* include header in MQGI command */
#define NCP_NCAV3_SENDTH_MQGI_EXCL_HDR   1          /* do not include header in MQGI command */

#define NCP_NCAV3_ADPAH_MQGI_INCL_HDR   0           /* include header in MQGI command */
#define NCP_NCAV3_ADPAH_MQGI_EXCL_HDR   1           /* do not include header in MQGI command */

#define NCP_NCAV3_ADPAE_MQGI_UNDEF_0    0           /* undefined */

/*
 * Quota transfer (MQGC)
 */

#define NCP_NCAV3_SENDTH_MQGC_DEC_SOURCE 0
#define NCP_NCAV3_SENDTH_MQGC_NOOP       1
#define NCP_NCAV3_SENDTH_MQGC_UNDEF_0    2
#define NCP_NCAV3_SENDTH_MQGC_UNDEF_1    3

#define NCP_NCAV3_ADPAH_MQGC_DEC_SOURCE_AND_INC_PCQ 0
#define NCP_NCAV3_ADPAH_MQGC_INC_PCQ                1
#define NCP_NCAV3_ADPAH_MQGC_DEC_SOURCE             2
#define NCP_NCAV3_ADPAH_MQGC_NOOP                   3

#define NCP_NCAV3_ADPAE_MQGC_DEC_SOURCE_AND_INC_PCQ 0
#define NCP_NCAV3_ADPAE_MQGC_INC_PCQ                1
#define NCP_NCAV3_ADPAE_MQGC_DEC_SOURCE             2
#define NCP_NCAV3_ADPAE_MQGC_NOOP                   3

typedef struct ncp_opcq_s
{
#ifdef NCP_BIG_ENDIAN
    ncp_uint64_t        taskAddress;

    ncp_uint64_t        flowControlDisabled:1;          /* FC   */
    ncp_uint64_t        reserved0:1;
    ncp_uint64_t        interruptEn:1;          /* I    */
    ncp_uint64_t        reserved1:1;            /* FM   */
    ncp_uint64_t        headerSize:1;           /* S    */
    ncp_uint64_t        taskCompletion:1;       /* C    */
    ncp_uint64_t        reserved2:1;
    ncp_uint64_t        headerSeparate:1;       /* H    */
    ncp_uint64_t        reserved3:5;
    ncp_uint64_t        cmd:3;                  /* command */
    ncp_uint64_t        reserved4:4;
    ncp_uint64_t        headerPoolMref:1;
    ncp_uint64_t        headerPool:3;
    ncp_uint64_t        reserved5:8;
    ncp_uint64_t        destIpcqId:8;           /* PCQ  */
    ncp_uint64_t        returnHeader:2;         /* RCCH */
    ncp_uint64_t        returnData:2;           /* RCCD */
    ncp_uint64_t        forceCopy:1;            /* FCPY */
    ncp_uint64_t        quotaIncludeHeader:1;   /* MQGI */
    ncp_uint64_t        quotaTransfer:2;        /* MQGC */
    ncp_uint64_t        reserved6:16;
#else
    ncp_uint64_t        taskAddress;

    ncp_uint64_t        reserved6:16;
    ncp_uint64_t        quotaTransfer:2;
    ncp_uint64_t        quotaIncludeHeader:1;
    ncp_uint64_t        forceCopy:1;
    ncp_uint64_t        returnData:2;
    ncp_uint64_t        returnHeader:2;
    ncp_uint64_t        destIpcqId:8;
    ncp_uint64_t        reserved5:8;
    ncp_uint64_t        headerPool:3;
    ncp_uint64_t        headerPoolMref:1;
    ncp_uint64_t        reserved4:4;
    ncp_uint64_t        cmd:3;
    ncp_uint64_t        reserved3:5;
    ncp_uint64_t        headerSeparate:1;
    ncp_uint64_t        reserved2:1;
    ncp_uint64_t        taskCompletion:1;
    ncp_uint64_t        headerSize:1;
    ncp_uint64_t        reserved1:1;
    ncp_uint64_t        interruptEn:1;
    ncp_uint64_t        reserved0:1;
    ncp_uint64_t        flowControlDisabled:1;
#endif
} ncp_opcq_t;

typedef ncp_opcq_t ncp_opcq_entry_t;


typedef struct ncp_mpcq_s
{
#ifdef NCP_BIG_ENDIAN
    ncp_uint64_t        address;
#else
    ncp_uint64_t        address;
#endif
} ncp_mpcq_t;

typedef ncp_mpcq_t ncp_mpcq_entry_t;

/*****************************************************************************************************
 * TQS (ThreadQueueSet)
 * A TQS structure comprises
 *      128 byte Control
 *      64 byte PE index table
 *      64 byte NCA index table
 *      Queues
 * Minimum size is defined as 1K and maximum size is 4K. 
 ******************************************************************************************************/
#define NCP_TQS_CONTROL_COOKIE          0xf41b9fbf
#define NCP_TQS_CONTROL_SHUTDOWN_INIT   0xc7
#define NCP_TQS_CONTROL_SHUTDOWN_DONE   0xd8
#define NCP_TQS_SHARED_POOL_2_ENABLED   0x4
#define NCP_TQS_SHARED_POOL_3_ENABLED   0x8
#define NCP_TQS_SHARED_POOL_4_ENABLED   0x10
#define NCP_TQS_SHARED_POOL_5_ENABLED   0x20
#define NCP_TQS_SHARED_POOL_6_ENABLED   0x40
#define NCP_TQS_SHARED_POOL_7_ENABLED   0x80
#define NCP_TQS_HWSEM_ENABLED           0x1
#define NCP_TQS_UNSCHEDQ_ENABLED        0x2
#define NCP_TQS_ALLOCS_ENABLED          0x4

/* Control structure. This structure is sized as 128 bytes. It contains 16B
 * offsets to the queues themselves with the control structure as the base */
typedef struct ncp_tqs_control_s
{
    ncp_uint32_t        cookie;                 /* Cookie to check validity. Initialized to NCP_TQS_CONTROL_COOKIE */
    ncp_uint8_t         auto_task_completion;   /* Whether auto task completion is enabled */
    ncp_uint8_t         allocators_bitmap;      /* Bitmap for which shared pools are mapped in
                                                 * P7, P6, P5, P4, P3, P2, Rsvd, Rsvd */
    ncp_uint8_t         ipcq_offset;            /* 16B ipcq offset in the tqs space */
    ncp_uint8_t         ipcq_depth;             /* Depth of ipcq */
    ncp_uint8_t         opcq0_offset;           /* 16B opcq0 offset in the tqs space */
    ncp_uint8_t         opcq0_depth;            /* Depth of opcq0 */
    ncp_uint8_t         opcq1_offset;           /* 16B opcq1 offset in the tqs space */
    ncp_uint8_t         opcq1_depth;            /* Depth of opcq */
    ncp_uint8_t         mpcq0_offsets[4];       /* Mpcq0 (shared pool 2) offsets in tqs space */
    ncp_uint8_t         mpcq0_depths[4];        /* Mpcq0 (shared pool 2) depths */
    ncp_uint8_t         mpcq1_offsets[4];       /* Mpcq1 (shared pool 3) offsets in tqs space */
    ncp_uint8_t         mpcq1_depths[4];        /* Mpcq1 (shared pool 3) depths */
    ncp_uint8_t         mpcq2_offsets[4];       /* Mpcq2 (shared pool 4) offsets in tqs space */
    ncp_uint8_t         mpcq2_depths[4];        /* Mpcq2 (shared pool 4) depths */
    ncp_uint8_t         mpcq3_offsets[4];       /* Mpcq3 (shared pool 5) offsets in tqs space */
    ncp_uint8_t         mpcq3_depths[4];        /* Mpcq3 (shared pool 5) depths */
    ncp_uint8_t         mpcq4_offsets[4];       /* Mpcq4 (shared pool 6) offsets in tqs space */
    ncp_uint8_t         mpcq4_depths[4];        /* Mpcq4 (shared pool 6) depths */
    ncp_uint8_t         mpcq5_offsets[4];       /* Mpcq5 (shared pool 7) offsets in tqs space */
    ncp_uint8_t         mpcq5_depths[4];        /* Mpcq5 (shared pool 7) depths */
    ncp_uint8_t         reserved0[4];
    ncp_uint8_t         reserved1[64];
} ncp_tqs_control_t;

/* PE index table. PE maintained copy of the producer/consumer index table for the various pcqs.
 * This structure is sized as 64 bytes. */
typedef struct ncp_tqs_pe_idx_table_s
{
    ncp_uint8_t         mc0_indexes[4];         /* Mpcq0 (shared pool 2) consumer indices */
    ncp_uint8_t         mc1_indexes[4];         /* Mpcq1 (shared pool 3) consumer indices */
    ncp_uint8_t         mc2_indexes[4];         /* Mpcq2 (shared pool 4) consumer indices */
    ncp_uint8_t         mc3_indexes[4];         /* Mpcq3 (shared pool 5) consumer indices */
    ncp_uint8_t         mc4_indexes[4];         /* Mpcq4 (shared pool 6) consumer indices */
    ncp_uint8_t         mc5_indexes[4];         /* Mpcq5 (shared pool 7) consumer indices */
    ncp_uint8_t         op0_index;              /* Opcq0 producer index */
    ncp_uint8_t         reserved0[3];
    ncp_uint8_t         op1_index;              /* Opcq1 producer index */
    ncp_uint8_t         reserved1[3];
    ncp_uint8_t         reserved2[8];
    ncp_uint8_t         ic_index;               /* Ipcq consumer index */
    ncp_uint8_t         reserved3[7];
    ncp_uint8_t         reserved4;
    ncp_uint8_t         reserved5[3];
    ncp_uint8_t         reserved6[12];
} ncp_tqs_pe_idx_table_t;

/* NCA index table. NCA maintained copy of the producer/consumer index table for the various pcqs.
 * This structure is sized as 64 bytes. */
typedef struct ncp_tqs_nca_idx_table_s
{
    ncp_uint8_t         mp0_indexes[4];         /* Mpcq0 (shared pool 2) producer indices */
    ncp_uint8_t         mp1_indexes[4];         /* Mpcq1 (shared pool 3) producer indices */
    ncp_uint8_t         mp2_indexes[4];         /* Mpcq2 (shared pool 4) producer indices */
    ncp_uint8_t         mp3_indexes[4];         /* Mpcq3 (shared pool 5) producer indices */
    ncp_uint8_t         mp4_indexes[4];         /* Mpcq4 (shared pool 6) producer indices */
    ncp_uint8_t         mp5_indexes[4];         /* Mpcq5 (shared pool 7) producer indices */
    ncp_uint8_t         oc0_index;              /* Opcq0 consumer index */
    ncp_uint8_t         reserved0[3];
    ncp_uint8_t         oc1_index;              /* Opcq1 consumer index */
    ncp_uint8_t         reserved1[3];
    ncp_uint8_t         reserved2[8];
    ncp_uint8_t         ip_index;               /* Ipcq producer index */
    ncp_uint8_t         reserved3[3];
    ncp_uint8_t         reserved4[20];
} ncp_tqs_nca_idx_table_t;
    
/* The ncp_tqs_t structure contains the control structure and the two index tables. The queues themselves
 * are provisioned after this 256 byte structure */
typedef struct ncp_tqs_s
{
    ncp_tqs_control_t           control;
    ncp_tqs_pe_idx_table_t      cputable;
    ncp_tqs_nca_idx_table_t     ncatable;
} ncp_tqs_t;

#ifdef __cplusplus
}
#endif

#endif
