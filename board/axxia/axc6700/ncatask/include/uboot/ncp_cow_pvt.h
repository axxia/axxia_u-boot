/**************************************************************************
 ** INTEL CONFIDENTIAL
 ** Copyright 2008 - 2015 Intel Corporation All Rights Reserved.
 **
 ** The source code contained or described herein and all documents related to 
 ** the source code ("Material") are owned by Intel Corporation or its 
 ** suppliers or licensors. Title to the Material remains with 
 ** Intel Corporation or its suppliers and licensors. 
 ** The Material contains trade secrets and proprietary and confidential
 ** information of Intel or its suppliers and licensors. The Material is 
 ** protected by worldwide copyright and trade secret laws and treaty 
 ** provisions. No part of the Material may be used, copied, reproduced, 
 ** modified, published, uploaded, posted, transmitted, distributed, or 
 ** disclosed in any way without Intel's prior express written permission.
 **
 ** No license under any patent, copyright, trade secret or other 
 ** intellectual property right is granted to or conferred upon you by 
 ** disclosure or delivery of the Materials, either expressly, by implication, 
 ** inducement, estoppel or otherwise. Any license under such intellectual 
 ** property rights must be express and approved by Intel in writing.
 *************************************************************************/


#ifndef _NCP_COW_PVT_H_
#define _NCP_COW_PVT_H_

#ifdef __cplusplus
extern "C" {
#endif

/* #define NCP_COW_WRITE_EIOA1 */

/* Macro to convert value to big endian */
#ifdef NCP_BIG_ENDIAN
#define NCP_BIG_ENDIAN_VAL32(val) (val)
#else
#define NCP_BIG_ENDIAN_VAL32(val) \
    ((((ncp_uint32_t)(val) >> 24) & 0x000000ff) |  \
     (((ncp_uint32_t)(val) >>  8) & 0x0000ff00) |  \
     (((ncp_uint32_t)(val) <<  8) & 0x00ff0000) |  \
     (((ncp_uint32_t)(val) << 24) & 0xff000000))
#endif

#define NCP_COW_ONLINE_MAX_TIME 100000  /* 100ms delay */
#define NCP_COW_ONLINE_DELAY_TIME 1000 /* 1ms delay */
#define NCP_COW_ONLINE_RETRIES (NCP_COW_ONLINE_MAX_TIME/NCP_COW_ONLINE_DELAY_TIME)

/* get number of task queue instances */
#define NCP_COW_NUM_DEST_INST_TASKQ(engine) (ncpCowEngineInfo[(engine)]->numTaskQueues / \
                                             ncpCowEngineInfo[(engine)]->numPriorities)

/* get number of logical queue instances */
#define NCP_COW_NUM_DEST_INST_LOGICALQ(engine) (ncpCowEngineInfo[(engine)]->numLogicalQueues / \
                                                ncpCowEngineInfo[(engine)]->numPriorities)

/* struct to store generic cow info per engine */
typedef struct ncp_cow_engine_info_st {
    ncp_uint16_t nodeId;                /* hardware node id */
    ncp_uint16_t numTemplates;          /* number of templates */
    ncp_uint16_t numTaskQueues;         /* number of task queues */
    ncp_uint8_t  numPriorities;         /* number of priorities */
    ncp_uint8_t bpEnginePhyId;          /* hardware BP phy id */

    /* TCLd info */
    ncp_uint8_t numLogicalQueues;       /* number of logical queues */
    ncp_uint8_t numBpIds;               /* number of bp ids */
    ncp_uint8_t numBpThresGrps;         /* number of BP threshold groups */
    ncp_uint8_t logicalQStartDest;      /* start dest inst for logical queue */
    ncp_uint8_t logicalQStartId;        /* start queue id for logical queue */
    ncp_uint8_t numDiscardThresGrps;    /* number of discard threshold groups */
    ncp_uint16_t numTOTEntries;         /* number of TOT entries */

    /* TIL info */
    ncp_uint8_t numIParamBytes;         /* number of input param bytes */
    ncp_bool_t  vFlowTablePresent;      /* whether vflow table is present */

    ncp_uint16_t taskQueueStartId;      /* start queue id for task queue */
    ncp_uint8_t chipType;               /* chip type of this engine. Useful mainly in FPGA systems. */
    ncp_uint8_t instRange;              /* instance range of this engine. Mainly used for shared engines. */
    ncp_uint8_t taskQInstRange;         /* instance range of task queues for this engine. Mainly used for shared engines. */
    ncp_uint8_t logicalQInstRange;      /* instance range of logical queues for this engine. Mainly used for shared engines. */
    ncp_uint8_t thresGrpStartId;        /* start id for threshold groups Mainly used for shared engines. */
} ncp_cow_engine_info_t;

extern ncp_cow_engine_info_t *ncpCowEngineInfo[ncp_engine_max];
extern ncp_cow_engine_info_t *ncpCowEngineInfo_hw[ncp_engine_max];

/* 
 * Private data type definitions 
 */


/*
 * TIL register defines and structs that are different from generated files 
 * are defined here.
 */

#define NCP_NU_TIL_IPARAMDEF(tid, word)         (NCP_NU_TIL_ITEMP_INST_BASE + \
                                                (NCP_NU_TIL_ITEMP_INST_ACCESS_SIZE * (tid)) + \
                                                (4 * (word)))

/* paramSel starts 64 into the register. Add it by default. */
#define NCP_NU_TIL_IPARAMSEL(tid, word)         (NCP_NU_TIL_ITEMP_INST_BASE + \
                                                (NCP_NU_TIL_ITEMP_INST_ACCESS_SIZE * (tid)) + \
                                                (NCP_NU_TIL_ITEMP_INST_ACCESS_SIZE >> 1) + \
                                                (4 * (word)))

/* Last word to start the input template commit. */
#define NCP_NU_TIL_IPARAM_COMMIT(tid)           (NCP_NU_TIL_ITEMP_INST_BASE + \
                                                (NCP_NU_TIL_ITEMP_INST_ACCESS_SIZE * (tid)) + \
                                                (NCP_NU_TIL_ITEMP_INST_ACCESS_SIZE - 4))

/*
 * For EIOA0, the next dest inst needs to be 16(multicast) and 17(learning).
 * For EIOA1, the next dest inst needs to be 32(multicast) and 33(learning).
 * As this macro is called for eioa0 and eioa1, the value can be flipped.
 * nxtdestmsb will always be eioa0. Change it from one to another just looking 
 * at the nxtdestlsb.
 */

#define NCP_COW_ADJUST_EIOA_OTEMP_NXT_DEST_INST(engine)                         \
({                                                                              \
    ncp_uint32_t __val = (*reg);                                                \
    if(indx == 1)                                                               \
    {                                                                           \
        ncp_nu_tgl_til_otemp_1_t *otemp1 = (ncp_nu_tgl_til_otemp_1_t *)&__val;  \
                                                                                \
        /* reg is in BE format. convert to host format. */                      \
        __val = ncp_ntohl(__val);                                               \
                                                                                \
        if(otemp1->nxtdestmsb == ncp_engine_eioa0 && otemp1->nxtdestlsbsel == 0)\
        {                                                                       \
            if(ncpHdl->rev.chipType == NCP_CHIP_ACP25xx)                        \
            {                                                                   \
                if(otemp1->nxtdestlsb == 32 || otemp1->nxtdestlsb == 33)        \
                {                                                               \
                    otemp1->nxtdestlsb -= ((engine) == ncp_engine_eioa0) ?      \
                                            16 : 0;                             \
                }                                                               \
            }                                                                   \
            else if(ncpHdl->rev.chipType == NCP_CHIP_ACP55xx ||                 \
                    ncpHdl->rev.chipType == NCP_CHIP_ACP56xx)                   \
            {                                                                   \
                if(otemp1->nxtdestlsb == 128 || otemp1->nxtdestlsb == 129)      \
                {                                                               \
                    otemp1->nxtdestlsb += ((engine) == ncp_engine_eioa1) ?      \
                                            4 : 0;                              \
                    otemp1->nxtdestlsb += ((engine) == ncp_engine_eioa3) ?      \
                                            4 : 0;                              \
                    otemp1->nxtdestlsb += ((engine) == ncp_engine_eioa4) ?      \
                                            8 : 0;                              \
                    otemp1->nxtdestlsb += ((engine) == ncp_engine_eioa5) ?      \
                                            12 : 0;                             \
                    otemp1->nxtdestlsb += ((engine) == ncp_engine_eioa6) ?      \
                                            16 : 0;                             \
                    otemp1->nxtdestlsb += ((engine) == ncp_engine_eioa7) ?      \
                                            20 : 0;                             \
                }                                                               \
            }                                                                   \
            else if(ncpHdl->rev.chipType == NCP_CHIP_ACPXLF)                    \
            {                                                                   \
                if(otemp1->nxtdestlsb == 128 || otemp1->nxtdestlsb == 129)      \
                {                                                               \
                    otemp1->nxtdestlsb += ((engine) == ncp_engine_eioa1) ?      \
                                            4 : 0;                              \
                    otemp1->nxtdestlsb += ((engine) == ncp_engine_eioa3) ?      \
                                            4 : 0;                              \
                    otemp1->nxtdestlsb += ((engine) == ncp_engine_eioa4) ?      \
                                            8 : 0;                              \
                    otemp1->nxtdestlsb += ((engine) == ncp_engine_eioa5) ?      \
                                            12 : 0;                             \
                }                                                               \
            }                                                                   \
        }                                                                       \
        /* For XLF ext domain eioa, when using mParam and when nxtdestlsb is */ \
        /* more than param size, update the template use engine params for */   \
        /* next dest instance and next template id. */                          \
        if(ncpHdl->rev.chipType == NCP_CHIP_ACPXLF &&                           \
           (engine == ncp_engine_eioa2 || engine == ncp_engine_eioa3 ||         \
            engine == ncp_engine_eioa4 || engine == ncp_engine_eioa5 ||         \
            engine == ncp_engine_isbs || engine == ncp_engine_isbs1))           \
        {                                                                       \
            /* for eioa-erif, use engine signals. */                            \
            if(otemp1->nxtdestmsb == ncp_dest_type_xlf_nd_erif ||               \
               otemp1->nxtdestmsb == ncp_dest_type_xlf_ed_erif ||               \
               otemp1->nxtdestmsb == ncp_engine_erif0 ||                        \
               otemp1->nxtdestmsb == ncp_engine_erif1)                          \
            {                                                                   \
                otemp1->nxtdestlsbsel = 0x4;    /* eng_tdgl_cmd_dest_inst[7:0] */   \
            }                                                                   \
            /* In ext domain, nxtdestlsbsel = 3 is not supported. convert it */ \
            /* to 7 with single byte offset. */                                 \
            if(otemp1->nxtdestlsbsel == 3)                                      \
            {                                                                   \
                otemp1->nxtdestlsbsel = 7;                                      \
                otemp1->nxtdestlsb = (((otemp1->nxtdestlsb >> 5) + 1) << 5);                              \
            }                                                                   \
            if(otemp1->nxtdestlsbsel == 7 &&                                    \
                (otemp1->nxtdestlsb >> 5) >= outParamSize)                      \
            {                                                                   \
                otemp1->nxtdestlsbsel = 0x4;    /* eng_tdgl_cmd_dest_inst[7:0] */   \
            }                                                                   \
            if(otemp1->nxttemplateidsel == 3 &&                                 \
               otemp1->nxttemplateid >= outParamSize)                           \
            {                                                                   \
                otemp1->nxttemplateidsel = 0x2; /* eng_tdgl_cmd_next_template[5:0] */  \
            }                                                                   \
        }                                                                       \
                                                                                \
        /* convert it back to BE format */                                      \
        __val = ncp_htonl(__val);                                               \
    }                                                                           \
    __val;                                                                      \
})

typedef enum ncp_dest_type_xlf_nd_e
{
    ncp_dest_type_xlf_nd_eioa = 1,
    ncp_dest_type_xlf_nd_timer = 2,
    ncp_dest_type_xlf_nd_pab = 3,
    ncp_dest_type_xlf_nd_mpp = 4,
    ncp_dest_type_xlf_nd_spp = 5,
    ncp_dest_type_xlf_nd_sed = 6,
    ncp_dest_type_xlf_nd_cpu = 7,
    ncp_dest_type_xlf_nd_dpi = 8,
    ncp_dest_type_xlf_nd_pic = 9,
    ncp_dest_type_xlf_nd_mtm = 10,
    ncp_dest_type_xlf_nd_decoder = 11,
    ncp_dest_type_xlf_nd_rif = 12,
    ncp_dest_type_xlf_nd_erif = 13    
} ncp_dest_type_xlf_nd_t;

#define NCP_COW_ADJUST_OTEMP_NXT_DEST_MSB_NATIVE_DOMAIN(val, engine)            \
({                                                                              \
    ncp_uint32_t __val = (val);                                                 \
    if(ncpHdl->rev.chipType == NCP_CHIP_ACPXLF && indx == 1)                    \
    {                                                                           \
        ncp_nu_tgl_til_otemp_1_t *otemp1 = (ncp_nu_tgl_til_otemp_1_t *)&__val;  \
        ncp_uint32_t __oldNxtdestmsb = 0;                                       \
                                                                                \
        /* reg is in BE format. convert to host format. */                      \
        __val = ncp_ntohl(__val);                                               \
        __oldNxtdestmsb = otemp1->nxtdestmsb;                                   \
                                                                                \
        switch(__oldNxtdestmsb)                                                 \
        {                                                                       \
        case ncp_engine_eioa0:                                                  \
        case ncp_engine_eioa1:                                                  \
        case ncp_engine_isb:                                                    \
            otemp1->nxtdestmsb = ncp_dest_type_xlf_nd_eioa;                     \
            break;                                                              \
        case ncp_engine_timer:                                                  \
            otemp1->nxtdestmsb = ncp_dest_type_xlf_nd_timer;                    \
            break;                                                              \
        case ncp_engine_pab:                                                    \
            otemp1->nxtdestmsb = ncp_dest_type_xlf_nd_pab;                      \
            break;                                                              \
        case ncp_engine_mpp:                                                    \
            otemp1->nxtdestmsb = ncp_dest_type_xlf_nd_mpp;                      \
            break;                                                              \
        case ncp_engine_spp:                                                    \
            otemp1->nxtdestmsb = ncp_dest_type_xlf_nd_spp;                      \
            break;                                                              \
        case ncp_engine_sed:                                                    \
            otemp1->nxtdestmsb = ncp_dest_type_xlf_nd_sed;                      \
            break;                                                              \
        case ncp_engine_cpu:                                                    \
            otemp1->nxtdestmsb = ncp_dest_type_xlf_nd_cpu;                      \
            break;                                                              \
        case ncp_engine_dpi:                                                    \
            otemp1->nxtdestmsb = ncp_dest_type_xlf_nd_dpi;                      \
            break;                                                              \
        case ncp_engine_pic:                                                    \
            otemp1->nxtdestmsb = ncp_dest_type_xlf_nd_pic;                      \
            break;                                                              \
        case ncp_engine_mtm:                                                    \
        case ncp_engine_expander:                                               \
            otemp1->nxtdestmsb = ncp_dest_type_xlf_nd_mtm;                      \
            break;                                                              \
        case ncp_engine_decoder:                                                \
            otemp1->nxtdestmsb = ncp_dest_type_xlf_nd_decoder;                  \
            break;                                                              \
        case ncp_engine_rif0:                                                   \
        case ncp_engine_rif1:                                                   \
            otemp1->nxtdestmsb = ncp_dest_type_xlf_nd_rif;                      \
            break;                                                              \
        case ncp_engine_erif0:                                                  \
        case ncp_engine_erif1:                                                  \
            otemp1->nxtdestmsb = ncp_dest_type_xlf_nd_erif;                     \
            break;                                                              \
        default:                                                                \
            break;                                                              \
        }                                                                       \
                                                                                \
        /* convert it back to BE format */                                      \
        __val = ncp_htonl(__val);                                               \
    }                                                                           \
    __val;                                                                      \
})

/*
 * Reserved engine for XLF/EMC. EMC is a dummy engine w/o any templates, etc.
 * This value is passed by ASE. RTE skips processing this engine.
 */
#define NCP_ENGINE_EMC 0xff
#define NCP_ENGINE_EMC_STR "emc"

#define NCP_COW_OTEMP_NXT_DEST_MSB_IS_EMC(engine)                               \
({                                                                              \
    ncp_bool_t __bEmc = FALSE;                                                  \
    if(ncpHdl->rev.chipType == NCP_CHIP_ACPXLF  &&                              \
       (engine == ncp_engine_eioa0 || engine == ncp_engine_eioa1 ||             \
        engine == ncp_engine_isb))                                              \
    {                                                                           \
        ncp_uint32_t __val = ((ncp_uint32_t  *)outputTemplate)[1];              \
        ncp_nu_tgl_til_otemp_1_t *otemp1 = (ncp_nu_tgl_til_otemp_1_t *)&__val;  \
                                                                                \
        /* reg is in BE format. convert to host format. */                      \
        __val = ncp_ntohl(__val);                                               \
                                                                                \
        if(otemp1->nxtdestmsb == NCP_ENGINE_EMC)                                \
        {                                                                       \
            __bEmc = TRUE;                                                      \
        }                                                                       \
    }                                                                           \
    __bEmc;                                                                     \
})

#define NCP_COW_OTEMP_NXT_DEST_MSB_IS_ERIF(engine)                              \
({                                                                              \
    ncp_bool_t __bErif = FALSE;                                                 \
    if(ncpHdl->rev.chipType == NCP_CHIP_ACPXLF  &&                              \
       (engine == ncp_engine_eioa0 || engine == ncp_engine_eioa1 ||             \
        engine == ncp_engine_isb))                                              \
    {                                                                           \
        ncp_uint32_t __val = ((ncp_uint32_t  *)outputTemplate)[1];              \
        ncp_nu_tgl_til_otemp_1_t *otemp1 = (ncp_nu_tgl_til_otemp_1_t *)&__val;  \
                                                                                \
        /* reg is in BE format. convert to host format. */                      \
        __val = ncp_ntohl(__val);                                               \
                                                                                \
        if(otemp1->nxtdestmsb == ncp_engine_erif0 ||                            \
           otemp1->nxtdestmsb == ncp_engine_erif1)                              \
        {                                                                       \
            __bErif = TRUE;                                                     \
        }                                                                       \
    }                                                                           \
    __bErif;                                                                    \
})


typedef enum ncp_dest_type_xlf_ed_e
{
    ncp_dest_type_xlf_ed_nd = 0,    /* reach native domain engines */
    ncp_dest_type_xlf_ed_eioa = 1,
    ncp_dest_type_xlf_ed_erif = 2,
    ncp_dest_type_xlf_ed_emc = 3,
} ncp_dest_type_xlf_ed_t;

/*
 * Next dest msb is already HW dest type here. Adjust it so it is mapped
 * to the right dest type in ext domain.
 */
#define NCP_COW_ADJUST_OTEMP_NXT_DEST_MSB_EXT_DOMAIN(val, engine)               \
({                                                                              \
    ncp_uint32_t __val = (val);                                                 \
    if(ncpHdl->rev.chipType == NCP_CHIP_ACPXLF && indx == 1)                    \
    {                                                                           \
        ncp_nu_tgl_til_otemp_1_t *otemp1 = (ncp_nu_tgl_til_otemp_1_t *)&__val;  \
        ncp_uint32_t __oldNxtdestmsb = 0;                                       \
                                                                                \
        /* reg is in BE format. convert to host format. */                      \
        __val = ncp_ntohl(__val);                                               \
        __oldNxtdestmsb = otemp1->nxtdestmsb;                                   \
                                                                                \
        switch(__oldNxtdestmsb)                                                 \
        {                                                                       \
        case ncp_dest_type_xlf_nd_eioa:                                         \
            otemp1->nxtdestmsb = ncp_dest_type_xlf_ed_eioa;                     \
            break;                                                              \
        case ncp_dest_type_xlf_nd_erif:                                         \
        case ncp_engine_erif0:                                                  \
        case ncp_engine_erif1:                                                  \
            otemp1->nxtdestmsb = ncp_dest_type_xlf_ed_erif;                     \
            break;                                                              \
        case 0xff: /* EMC engine as given by ASE */                             \
            otemp1->nxtdestmsb = ncp_dest_type_xlf_ed_emc;                      \
            break;                                                              \
        case ncp_dest_type_xlf_nd_timer:                                        \
        case ncp_dest_type_xlf_nd_pab:                                          \
        case ncp_dest_type_xlf_nd_mpp:                                          \
        case ncp_dest_type_xlf_nd_spp:                                          \
        case ncp_dest_type_xlf_nd_sed:                                          \
        case ncp_dest_type_xlf_nd_cpu:                                          \
        case ncp_dest_type_xlf_nd_dpi:                                          \
        case ncp_dest_type_xlf_nd_pic:                                          \
        case ncp_dest_type_xlf_nd_mtm:                                          \
        case ncp_dest_type_xlf_nd_decoder:                                      \
        case ncp_dest_type_xlf_nd_rif:                                          \
            otemp1->nxtdestmsb = ncp_dest_type_xlf_ed_nd;                       \
            break;                                                              \
        default:                                                                \
            break;                                                              \
        }                                                                       \
                                                                                \
        /* convert it back to BE format */                                      \
        __val = ncp_htonl(__val);                                               \
    }                                                                           \
    __val;                                                                      \
})

/* macros to split toid field when flow data is not used */
#define NCP_NU_TIL_VFLOW_LSB_TOID(toid)         ((toid) & 0x3)
#define NCP_NU_TIL_VFLOW_MSB_TOID(toid)         (((toid) >> 2) & 0x3ff)

#define NCP_NU_TIL_SHARE_CONTROL_INST(instRange)     \
    (NCP_NU_TIL_TIL_SHARE_CONTROL_INST0_ACP2500 + ((instRange) * 4))

/*!
 * We configure engine any time, an engine is present.
 */
#define NCP_COW_CONFIGURE_ENGINE(ncp, engine)                                   \
    ({                                                                          \
        ncp_bool_t bConfigure = TRUE;                                           \
        if(ncpCowEngineInfo[(engine)] == NULL)                                  \
        {                                                                       \
            bConfigure = FALSE;                                                 \
        }                                                                       \
        bConfigure;                                                             \
    })

/*!
 * We configure EIOA1 if engine is eioa0 or eioa1 and eioa1 is present.
 */
#define NCP_COW_CONFIGURE_EIOA(engine, eioa_engine)                             \
    ({                                                                          \
        ncp_bool_t bConfigure = FALSE;                                          \
        if((engine) == ncp_engine_eioa0 &&                                      \
           ncpCowEngineInfo[eioa_engine] != NULL)                               \
        {                                                                       \
            bConfigure = TRUE;                                                  \
        }                                                                       \
        bConfigure;                                                             \
    })

/*!
 * Configure ERIF1 if engine is erif0 or erif1 and erif1 is present.
 */
#define NCP_COW_CONFIGURE_ERIF(engine, erif_engine)                             \
    ({                                                                          \
        ncp_bool_t bConfigure = FALSE;                                          \
        if((engine) == ncp_engine_erif0 &&                                      \
           ncpCowEngineInfo[erif_engine] != NULL)                               \
        {                                                                       \
            bConfigure = TRUE;                                                  \
        }                                                                       \
        bConfigure;                                                             \
    })

/*!
 * Configure RIF1 if engine is rif0 or rif1 and rif1 is present.
 */
#define NCP_COW_CONFIGURE_RIF(engine, rif_engine)                               \
    ({                                                                          \
        ncp_bool_t bConfigure = FALSE;                                          \
        if((engine) == ncp_engine_rif0 &&                                       \
           ncpCowEngineInfo[rif_engine] != NULL)                                \
        {                                                                       \
            bConfigure = TRUE;                                                  \
        }                                                                       \
        bConfigure;                                                             \
    })

#define NCP_COW_TASKQ_QUEUEID(engine, queue)                                    \
    (ncpCowEngineInfo[(engine)]->taskQueueStartId + (queue))
            
#define NCP_COW_TASKQ_REG_BASE(ncpHdl, engine, queue)                           \
({                                                                              \
    ncp_uint32_t __offset = 0;                                                  \
    if(ncpCowEngineInfo[(engine)]->chipType == NCP_CHIP_ACP56xx ||              \
       (ncpCowEngineInfo[engine]->chipType == NCP_CHIP_ACPXLF &&                \
        NCP_COW_ENGINE_IS_NATIVE(engine)))                                      \
    {                                                                           \
        __offset = NCP_NU_TCLD_REG_TASK_QUEUE_MEMORY_5600(                      \
                        NCP_COW_TASKQ_QUEUEID(engine, queue));                  \
    }                                                                           \
    else if(ncpCowEngineInfo[engine]->chipType == NCP_CHIP_ACPXLF &&            \
            !NCP_COW_ENGINE_IS_NATIVE(engine))                                  \
    {                                                                           \
        __offset = NCP_NU_TRECV_XLF_TASK_QUEUE_STATE(                           \
                        NCP_COW_TASKQ_QUEUEID(engine, queue));                  \
    }                                                                           \
    else                                                                        \
    {                                                                           \
        __offset = NCP_NU_TCLD_REG_TASK_QUEUE_MEMORY(                           \
                        NCP_COW_TASKQ_QUEUEID(engine, queue));                  \
    }                                                                           \
    __offset;                                                                   \
})

#define NCP_COW_TASKQ_REG_SIZE(ncpHdl, engine)                                  \
({                                                                              \
    ncp_uint32_t __size = 0;                                                    \
    if(ncpCowEngineInfo[(engine)]->chipType == NCP_CHIP_ACP56xx ||              \
       (ncpCowEngineInfo[engine]->chipType == NCP_CHIP_ACPXLF &&                \
        NCP_COW_ENGINE_IS_NATIVE(engine)))                                      \
    {                                                                           \
        __size = sizeof(ncp_nu_tcld_task_queue_rf_5600_t)/sizeof(ncp_uint32_t); \
    }                                                                           \
    else if(ncpCowEngineInfo[engine]->chipType == NCP_CHIP_ACPXLF &&            \
            !NCP_COW_ENGINE_IS_NATIVE(engine))                                  \
    {                                                                           \
        __size = sizeof(ncp_nu_trecv_xlf_task_queue_state_r_t)/sizeof(ncp_uint32_t); \
    }                                                                           \
    else                                                                        \
    {                                                                           \
        __size = sizeof(ncp_nu_tcld_task_queue_rf_t)/sizeof(ncp_uint32_t);      \
    }                                                                           \
    __size;                                                                     \
})


#define NCP_COW_LOGICALQ_QUEUEID(engine, queue)                                 \
    (ncpCowEngineInfo[(engine)]->logicalQStartId + (queue))
            
#define NCP_COW_LOGICALQ_REG_BASE(engine, queue)                                \
({										\
    ncp_uint32_t _offset = 0;							\
    if(ncpCowEngineInfo[(engine)]->chipType == NCP_CHIP_ACP56xx ||              \
       ncpCowEngineInfo[(engine)]->chipType == NCP_CHIP_ACPXLF)                 \
    {                                                                           \
        /* start from fourth word. First three words are reserved. */           \
        _offset = NCP_NU_TCLD_REG_LOGICAL_QUEUE_MEMORY_5600(NCP_COW_LOGICALQ_QUEUEID(engine, queue)) + 0xc; \
    }										\
    else									\
    {										\
        _offset = NCP_NU_TCLD_REG_LOGICAL_QUEUE_MEMORY(NCP_COW_LOGICALQ_QUEUEID(engine, queue)); \
    }										\
    _offset;									\
})

#define NCP_COW_LOGICALQ_REG_SIZE(engine)                                       \
({                                                                              \
    ncp_uint32_t __size = 0;                                                    \
    if(ncpCowEngineInfo[(engine)]->chipType == NCP_CHIP_ACP56xx ||              \
       ncpCowEngineInfo[(engine)]->chipType == NCP_CHIP_ACPXLF)                 \
    {                                                                           \
        __size = sizeof(ncp_nu_tcld_logical_queue_rf_5600_t)/sizeof(ncp_uint32_t); \
    }                                                                           \
    else                                                                        \
    {                                                                           \
        __size = sizeof(ncp_nu_tcld_logical_queue_rf_t)/sizeof(ncp_uint32_t);   \
    }                                                                           \
    __size;                                                                     \
})

#define NCP_COW_LOGICALQ_DESTID_2_QUEUEID(engine, destId) (\
            (destId) \
            - ncpCowEngineInfo[(engine)]->logicalQStartDest \
            + ncpCowEngineInfo[(engine)]->logicalQStartId)

#define NCP_COW_ADJUST_BY_INST_RANGE(engine, index) \
    ((index) + ncpCowEngineInfo[engine]->instRange)

#define NCP_COW_INST_RANGE_VAL(engine, instRange)                           \
    ({                                                                  \
        ncp_uint8_t __destRange = 0;                                    \
        if(instRange == ncp_cow_inst_range_task_queue)                  \
        {                                                               \
            __destRange = ncpCowEngineInfo[engine]->taskQInstRange;     \
        }                                                               \
        else if(instRange == ncp_cow_inst_range_logical_queue)          \
        {                                                               \
            __destRange = ncpCowEngineInfo[engine]->logicalQInstRange;  \
        }                                                               \
        __destRange;                                                    \
    })

#define NCP_COW_EIOA_MC_QUEUE_LEARN_INSTANCE(engine)                            \
({                                                                              \
    ncp_uint32_t _instance = 0;                                                 \
                                                                                \
    if(ncpCowEngineInfo[engine]->chipType == NCP_CHIP_ACP56xx)                  \
    {                                                                           \
        switch(engine)                                                          \
        {                                                                       \
        case ncp_engine_eioa0:                                                  \
        case ncp_engine_eioa1:                                                  \
            _instance = 5;                                                      \
            break;                                                              \
        case ncp_engine_eioa2:                                                  \
        case ncp_engine_eioa3:                                                  \
        case ncp_engine_eioa4:                                                  \
        case ncp_engine_eioa5:                                                  \
        case ncp_engine_eioa6:                                                  \
        case ncp_engine_eioa7:                                                  \
            _instance = 2;                                                      \
            break;                                                              \
        default:                                                                \
            break;                                                              \
        }                                                                       \
    }                                                                           \
    else if(ncpCowEngineInfo[engine]->chipType == NCP_CHIP_ACPXLF)              \
    {                                                                           \
        switch(engine)                                                          \
        {                                                                       \
        case ncp_engine_eioa0:                                                  \
        case ncp_engine_eioa1:                                                  \
            _instance = 5;                                                      \
            break;                                                              \
        case ncp_engine_eioa2:                                                  \
        case ncp_engine_eioa3:                                                  \
            _instance = 4;                                                      \
            break;                                                              \
        case ncp_engine_eioa4:                                                  \
        case ncp_engine_eioa5:                                                  \
            _instance = 3;                                                      \
            break;                                                              \
        default:                                                                \
            break;                                                              \
        }                                                                       \
    }                                                                           \
    _instance;                                                                  \
})

#define NCP_COW_EIOA_LEARN_QUEUE_LEARN_INSTANCE(engine)                         \
    (NCP_COW_EIOA_MC_QUEUE_LEARN_INSTANCE(engine) + 1)

/* 
 * This is the word 31 of the input template. It needs to be written to 
 * commit the input template.
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
          /* word 31 */
     unsigned      sparamsel_res_a_480                       :  1;
     unsigned      sparamsel_res_a_481                       :  1;
     unsigned      sparamsel_res_a_482                       :  1;
     unsigned      sparamsel_res_a_483                       :  1;
     unsigned      sparamsel_res_a_484                       :  1;
     unsigned      sparamsel_res_a_485                       :  1;
     unsigned      sparamsel_res_a_486                       :  1;
     unsigned      sparamsel_res_a_487                       :  1;
     unsigned      sparamsel_res_a_488                       :  1;
     unsigned      sparamsel_res_a_489                       :  1;
     unsigned      sparamsel_res_a_490                       :  1;
     unsigned      sparamsel_res_a_491                       :  1;
     unsigned      sparamsel_res_a_492                       :  1;
     unsigned      sparamsel_res_a_493                       :  1;
     unsigned      sparamsel_res_a_494                       :  1;
     unsigned      sparamsel_res_a_495                       :  1;
     unsigned      sparamsel_res_a_496                       :  1;
     unsigned      sparamsel_res_a_497                       :  1;
     unsigned      sparamsel_res_a_498                       :  1;
     unsigned      sparamsel_res_a_499                       :  1;
     unsigned      sparamsel_res_a_500                       :  1;
     unsigned      sparamsel_res_a_501                       :  1;
     unsigned      sparamsel_res_a_502                       :  1;
     unsigned      sparamsel_res_a_503                       :  1;
     unsigned      sparamsel_res_a_504                       :  1;
     unsigned      sparamsel_res_a_505                       :  1;
     unsigned      sparamsel_res_a_506                       :  1;
     unsigned      sparamsel_res_a_507                       :  1;
     unsigned      sparamsel_res_a_508                       :  1;
     unsigned      sparamsel_res_a_509                       :  1;
     unsigned      sparamsel_res_a_510                       :  1;
     unsigned      iparam_v                                  :  1;
#else    /* Little Endian */
          /* word 31 */
     unsigned      iparam_v                                  :  1;
     unsigned      sparamsel_res_a_510                       :  1;
     unsigned      sparamsel_res_a_509                       :  1;
     unsigned      sparamsel_res_a_508                       :  1;
     unsigned      sparamsel_res_a_507                       :  1;
     unsigned      sparamsel_res_a_506                       :  1;
     unsigned      sparamsel_res_a_505                       :  1;
     unsigned      sparamsel_res_a_504                       :  1;
     unsigned      sparamsel_res_a_503                       :  1;
     unsigned      sparamsel_res_a_502                       :  1;
     unsigned      sparamsel_res_a_501                       :  1;
     unsigned      sparamsel_res_a_500                       :  1;
     unsigned      sparamsel_res_a_499                       :  1;
     unsigned      sparamsel_res_a_498                       :  1;
     unsigned      sparamsel_res_a_497                       :  1;
     unsigned      sparamsel_res_a_496                       :  1;
     unsigned      sparamsel_res_a_495                       :  1;
     unsigned      sparamsel_res_a_494                       :  1;
     unsigned      sparamsel_res_a_493                       :  1;
     unsigned      sparamsel_res_a_492                       :  1;
     unsigned      sparamsel_res_a_491                       :  1;
     unsigned      sparamsel_res_a_490                       :  1;
     unsigned      sparamsel_res_a_489                       :  1;
     unsigned      sparamsel_res_a_488                       :  1;
     unsigned      sparamsel_res_a_487                       :  1;
     unsigned      sparamsel_res_a_486                       :  1;
     unsigned      sparamsel_res_a_485                       :  1;
     unsigned      sparamsel_res_a_484                       :  1;
     unsigned      sparamsel_res_a_483                       :  1;
     unsigned      sparamsel_res_a_482                       :  1;
     unsigned      sparamsel_res_a_481                       :  1;
     unsigned      sparamsel_res_a_480                       :  1;
#endif
} ncp_nu_til_itemp_commit_t;

/*
 * TCLd register defines and structs that are different from generated files 
 * are defined here.
 */

/* queue discard threshold id */
#define NCP_NU_TCLD_QUEUE_DISCARD_THRES_ID(inst, destId) \
    (NCP_NU_TCLD_INST_RANGE_0_QUEUE_DISCARD_THRESH_GROUP_ARRAY(destId) + \
    ((NCP_NU_TCLD_INST_RANGE_1_QUEUE_DISCARD_THRESH_GROUP_ARRAY_BASE - \
      NCP_NU_TCLD_INST_RANGE_0_QUEUE_DISCARD_THRESH_GROUP_ARRAY_BASE) * (inst)))

/* queue discard threshold group */
#define NCP_NU_TCLD_REG_QUEUE_DISCARD_THRES_GRP(grp, prio) \
    NCP_NU_TCLD_REG_QUEUE_DISCARD_THRESHOLD_MEMORY(((grp * 8) + prio))

/* queue packet discard threshold group */
#define NCP_NU_TCLD_REG_QUEUE_PACKET_DISCARD_THRES_GRP(engine, grp, prio)       \
    (NCP_NU_TCLD_REG_QUEUE_DISCARD_THRESHOLD_MEMORY(                            \
        (((ncpCowEngineInfo[engine]->numDiscardThresGrps + grp) * 8) + prio)))

/* XLF queue discard threshold group */
#define NCP_NU_TRECV_XLF_TASK_QUEUE_DISCARD_THRESHOLD_GRP(grp, prio) \
    NCP_NU_TRECV_XLF_TASK_QUEUE_DISCARD_THRESHOLD(((grp * 8) + prio))

/* XLF queue packet discard threshold group */
#define NCP_NU_TRECV_XLF_TASK_QUEUE_PACKET_DISCARD_THRESHOLD_GRP(engine, grp, prio)       \
    (NCP_NU_TRECV_XLF_PACKET_QUEUE_DISCARD_THRESHOLD((((grp) * 8) + prio)))

#define NCP_COW_ENGINE_IS_NATIVE(engine)        \
    ({                                          \
        ncp_bool_t isNative = FALSE;            \
                                                \
        if(engine != ncp_engine_eioa2 &&        \
           engine != ncp_engine_eioa3 &&        \
           engine != ncp_engine_eioa4 &&        \
           engine != ncp_engine_eioa5 &&        \
           engine != ncp_engine_eioa6 &&        \
           engine != ncp_engine_eioa7 &&        \
           engine != ncp_engine_isbs  &&        \
           engine != ncp_engine_isbs1)          \
        {                                       \
            isNative = TRUE;                    \
        }                                       \
        isNative;                               \
    })

/* TIL ARB mode. Values need to be same as defined in HW. */
#define NCP_COW_TIL_ARB_MODE_STRICT     0
#define NCP_COW_TIL_ARB_MODE_ROTATE     1
#define NCP_COW_TIL_ARB_MODE_RR         2
#define NCP_COW_TIL_ARB_MODE_WRR        3

/* TCLd threshold units. Values need to be same as defined in HW. */
#define NCP_COW_TCLD_THRES_UNIT_TASKS   0
#define NCP_COW_TCLD_THRES_UNIT_256B    1

/* TCLd bp threshold hysteresis config */
#define NCP_COW_TCLD_BP_THRESH_16       0
#define NCP_COW_TCLD_BP_THRESH_64       1

/***************************************
 * TIL internal functions
 ***************************************/

/* bring TIL online */
ncp_st_t
ncp_cow_til_online(ncp_hdl_t hdl, ncp_engine_type_t engine);

/* set arb mode and return it */
ncp_st_t
ncp_cow_til_arb_mode_set(ncp_hdl_t hdl, ncp_engine_type_t engine, 
                         ncp_map_t *map, ncp_uint8_t *arbMode,
                         ncp_uint8_t *s1arbMode);

/* set input queue weights */
ncp_st_t
ncp_cow_til_input_queue_weight_config(ncp_hdl_t hdl, ncp_engine_type_t engine, 
                                   ncp_uint8_t qid, ncp_map_t *queueMap);

ncp_st_t
ncp_cow_til_s1_arb_weight_config(ncp_hdl_t hdl, ncp_engine_type_t engine,
                                 ncp_uint8_t instance, ncp_map_t *map);

/***************************************
 * TGL internal functions
 ***************************************/

/* bring TGL online */
ncp_st_t
ncp_cow_tgl_online(ncp_hdl_t hdl, ncp_engine_type_t engine);

/* Set the timestamp resolution (55xx only) */
ncp_st_t
ncp_cow_tgl_ts_resolution_set(ncp_hdl_t hdl, ncp_engine_type_t engine, ncp_map_t *map);

/***************************************
 * TCLs internal functions
 ***************************************/

/* bring TCLs online */
ncp_st_t
ncp_cow_tcls_online(ncp_hdl_t hdl, ncp_engine_type_t engine);

/* init free pointer list fifo */
ncp_st_t
ncp_cow_tcls_init_free_ptr_fifo(ncp_hdl_t hdl, ncp_engine_type_t engine);

/***************************************
 * TIL internal functions
 ***************************************/

/* init TCLd */
ncp_st_t
ncp_cow_tcld_init(ncp_hdl_t hdl, ncp_engine_type_t engine);

/* bring TCLd online/offline */
ncp_st_t
ncp_cow_tcld_online(ncp_hdl_t hdl, ncp_engine_type_t engine, ncp_bool_t online);

/* function to set priority mapping */
ncp_st_t
ncp_cow_tcld_priority_map_set(ncp_hdl_t hdl, ncp_engine_type_t engine,
                              ncp_cow_inst_range_t instRange, ncp_map_t *queueMap);

/* configure resource id */
ncp_st_t
ncp_cow_tcld_resource_id_set(ncp_hdl_t hdl, ncp_engine_type_t engine, 
                             ncp_uint8_t id, ncp_uint8_t resIndex);

/* map the taskq to a logicalq */
ncp_st_t
ncp_cow_tcld_add_taskq_to_logicalq(ncp_hdl_t hdl, ncp_engine_type_t engine, 
                                   ncp_uint8_t taskQ, ncp_map_t *taskQueueMap,
                                   ncp_int32_t *logicalQ);

/* map the taskq to a logicalq */
ncp_st_t
ncp_cow_tcld_logicalq_ordered_set(ncp_hdl_t hdl, ncp_engine_type_t engine, 
                                  ncp_uint8_t logicalQ, 
                                  ncp_map_t *logicalQueueMap, 
                                  ncp_uint8_t *numOrdered, 
                                  ncp_uint8_t *orderedLogicalQ);

/* configure task queue threshold for a logical queue */
ncp_st_t
ncp_cow_tcld_logicalq_taskq_thresh_set(ncp_hdl_t hdl, ncp_engine_type_t engine, 
                                       ncp_uint8_t logicalQ, ncp_map_t *map);

/* configure task order entries for logicalq */
ncp_st_t
ncp_cow_tcld_logicalq_TO_set(ncp_hdl_t hdl, ncp_engine_type_t engine, 
                             ncp_uint8_t numOrdered, ncp_uint8_t orderedLogicalQ);

/* init the logicalq base and map registers */
ncp_st_t
ncp_cow_tcld_logicalq_init(ncp_hdl_t hdl, ncp_engine_type_t engine);

/* set queue discard threshold id */
ncp_st_t
ncp_cow_tcld_thres_group_id_config(ncp_hdl_t hdl, ncp_engine_type_t engine, 
                                ncp_cow_inst_range_t instRange, ncp_uint8_t destId,
                                ncp_map_t *map);

/* set threshold units */
ncp_st_t
ncp_cow_tcld_thres_unit_set(ncp_hdl_t hdl, ncp_engine_type_t engine,
                            ncp_map_t *map);

/* read global buffer threshold info from config file and configure the HW */
ncp_st_t
ncp_cow_tcld_global_buffer_thres_config(ncp_hdl_t hdl, ncp_engine_type_t engine,
                                        ncp_map_t *thresholdsMap);

/* read threshold groups from config file and configure the HW */
ncp_st_t
ncp_cow_tcld_thres_group_config(ncp_hdl_t hdl, ncp_engine_type_t engine,
                                ncp_map_t *thresholdsMap);

/* configure task/logical queue bp sources */
ncp_st_t
ncp_cow_tcld_bp_src_config(ncp_hdl_t hdl, ncp_engine_type_t engine, 
                            ncp_map_t *taskRecvMap);

/* clear task/logical queue memory */
ncp_st_t
ncp_cow_tcld_queue_clear(ncp_hdl_t hdl, ncp_engine_type_t engine);


/***************************************
 * Config strings used in ASE
 ***************************************/

/* MCIP config */
#define NCP_MCIP_PREFETCH       "PrefetchMMBBlocks"
#define NCP_MCIP_256B           "num256byteBlocks"
#define NCP_MCIP_2KB            "num2KbyteBlocks"
#define NCP_MCIP_16KB           "num16KbyteBlocks"
#define NCP_MCIP_64KB           "num64KbyteBlocks"

/* EIOA defines used to locate COW attributes */
#define NCP_EIOA_XLGMAC             "XLGMAC"
#define NCP_EIOA_XGMAC              "XGMAC"
#define NCP_EIOA_GMAC               "GMAC"

/* NCA defines used to locate COW attributes */
#define NCP_NCA_QUEUE_GROUP             "QueueGroup"
#define NCP_NCA_THREAD_QUEUE_SET        "ThreadQueueSet"
#define NCP_NCA_TASK_RECEIVE_QUEUE      "TaskReceiveQueue"
#define NCP_NCA_LOGICAL_QUEUE_MEMBER    "memberOfLogicalQueue"
#define NCP_NCA_LOGICAL_RECEIVE_QUEUE   "LogicalTaskReceiveQueue"
#define NCP_NCA_LOGICAL_QUEUE_ORDERED   "ordered"

#define NCP_COW_LOAD_BALANCE_MODE       "loadBalanceMode"
#define NCP_COW_LOAD_BALANCE_MODE_PRIO  "Priority"
#define NCP_COW_LOAD_BALANCE_MODE_CORE  "Core"

/* NCA defines used to locate COW attributes */
#define NCP_MTM_UNICAST             "Unicast"
#define NCP_MTM_MULTICAST           "Multicast"

/* Definitions of all config strings used */
#define NCP_COW_TASK_RECEIVE        "TaskReceive"
#define NCP_COW_TASK_TRACE          "TaskTrace"
#define NCP_COW_HP_QUEUE            "HighPriorityTaskQueue"
#define NCP_COW_LP_QUEUE            "LowPriorityTaskQueue"
#define NCP_COW_ARB_MODE            "taskQueueArbitration"
#define NCP_COW_ARB_MODE_STRICT     "Strict"
#define NCP_COW_ARB_MODE_ROTATE     "Rotating"
#define NCP_COW_ARB_MODE_RR         "RoundRobin"
#define NCP_COW_ARB_MODE_WRR        "WeightedRoundRobin"
#define NCP_COW_THRES_GROUP_ID      "thresGroupId"
#define NCP_COW_WRR_WEIGHT          "wrrWeight"
#define NCP_COW_HPQ_WRR_WEIGHT      "highPrioQueueWrrWeight"
#define NCP_COW_LPQ_WRR_WEIGHT      "lowPrioQueueWrrWeight"
#define NCP_COW_NUM_PRIO            "numTaskPriorities"
#define NCP_COW_NUM_HI_PRIO         "numHighPrioTaskQueuePriorities"
#define NCP_COW_NUM_LO_PRIO         "numLowprioTaskQueuePriorities"
#define NCP_COW_PRIO_MAP_HIGH       "High"
#define NCP_COW_PRIO_MAP_MED_HI     "MediumHigh"
#define NCP_COW_PRIO_MAP_MED_LOW    "MediumLow"
#define NCP_COW_PRIO_MAP_LOW        "Low"
#define NCP_COW_THRESHOLDS          "Thresholds"
#define NCP_COW_THRESHOLD_UINTS     "thresholdUnits"
#define NCP_COW_THRES_UNIT_TASKS    "Tasks"
#define NCP_COW_THRES_UNIT_256B     "BlockSize256B"
#define NCP_COW_THRES_UNIT_BOTH     "Both"
#define NCP_COW_BP_THRESH_HYST      "bpHysteresis"
#define NCP_COW_BP_THRESH_HYST_16   "DivideBy16"
#define NCP_COW_BP_THRESH_HYST_64   "DivideBy64"
#define NCP_COW_GLOBAL_BUFF_THRES   "GlobalBufferThres"
#define NCP_COW_PRIORITY            "Priority"
#define NCP_COW_RED_SLOPE           "redSlope"
#define NCP_COW_BUFFER_LOW_THRES    "bufferAvailLowThres"
#define NCP_COW_BUFFER_HIGH_THRES   "bufferAvailHighThres"
#define NCP_COW_THRES_GROUP         "ThresholdGroup"
#define NCP_COW_PACKET_THRES_GROUP  "PacketDataGroup"
#define NCP_COW_QDISCARD_MIN_THRES  "usedMinThres"
#define NCP_COW_QDISCARD_MAX_THRES  "usedMaxThres"
#define NCP_COW_BACKPRESSURE_THRES  "bptThres"
#define NCP_COW_ID                  "id"

/* Number of Priorities for Gbl or QDiscard Thresholds */
#define NCP_COW_THRESH_PRIORITY_COUNT  8

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _NCP_COW_PVT_H_ */

