/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


#ifndef _NCP_COW_EXT_H_
#define _NCP_COW_EXT_H_

#include "uboot/ncp_sal.h"
#include "uboot/ncp_cow.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NCP_COW_EIOA_NUM_TO_ENGINE(eioa_num)                \
    ({                                                      \
        ncp_engine_type_t __engine = 0;                     \
        switch(eioa_num)                                    \
        {                                                   \
        case NCP_EIOA0:                                     \
            __engine = ncp_engine_eioa0;                    \
            break;                                          \
        case NCP_EIOA1:                                     \
            __engine = ncp_engine_eioa1;                    \
            break;                                          \
        case NCP_EIOA2:                                     \
            __engine = ncp_engine_eioa2;                    \
            break;                                          \
        case NCP_EIOA3:                                     \
            __engine = ncp_engine_eioa3;                    \
            break;                                          \
        case NCP_EIOA4:                                     \
            __engine = ncp_engine_eioa4;                    \
            break;                                          \
        case NCP_EIOA5:                                     \
            __engine = ncp_engine_eioa5;                    \
            break;                                          \
        case NCP_EIOA6:                                     \
            __engine = ncp_engine_eioa6;                    \
            break;                                          \
        case NCP_EIOA7:                                     \
            __engine = ncp_engine_eioa7;                    \
            break;                                          \
        }                                                   \
        __engine;                                           \
    })

#define NCP_COW_ENGINE_TO_EIOA_NUM(engine)                  \
    ({                                                      \
        ncp_eioa_num_t __eioa_num = 0xff;                   \
        switch(engine)                                      \
        {                                                   \
        case ncp_engine_eioa0:                              \
            __eioa_num = NCP_EIOA0;                         \
            break;                                          \
        case ncp_engine_eioa1:                              \
            __eioa_num = NCP_EIOA1;                         \
            break;                                          \
        case ncp_engine_eioa2:                              \
            __eioa_num = NCP_EIOA2;                         \
            break;                                          \
        case ncp_engine_eioa3:                              \
            __eioa_num = NCP_EIOA3;                         \
            break;                                          \
        case ncp_engine_eioa4:                              \
            __eioa_num = NCP_EIOA4;                         \
            break;                                          \
        case ncp_engine_eioa5:                              \
            __eioa_num = NCP_EIOA5;                         \
            break;                                          \
        case ncp_engine_eioa6:                              \
            __eioa_num = NCP_EIOA6;                         \
            break;                                          \
        case ncp_engine_eioa7:                              \
            __eioa_num = NCP_EIOA7;                         \
            break;                                          \
        default:                                            \
            break;                                          \
        }                                                   \
        __eioa_num;                                         \
    })


/* Backpressure strings */
#define NCP_COW_BP_QUEUE_SRCS       "BPQueueSrcs"
#define NCP_COW_BP_QUEUE_SRC        "QueueSrc"
#define NCP_COW_BP_SRC_MTM_SCRIPT   "mtm-script"
#define NCP_COW_BP_SRC_INST         "instance"
#define NCP_COW_BP_SRC_PRIO         "priority"
#define NCP_COW_BP_DEST_ENGINE      "destEngine"
#define NCP_COW_BP_DEST_INDEX       "destIndex"

#define NCP_BP_PHYID_INVALID 0xff

/* 
 * Data type definitions 
 */

/* 
 * Enum of HW engine BP phyid in acp. Needs to match with HW definition.
 */
typedef enum ncp_bp_phyid_e {
    ncp_bp_phyid_cpu = 0,
    ncp_bp_phyid_sed,
    ncp_bp_phyid_spp,
    ncp_bp_phyid_dpi,
    ncp_bp_phyid_mtm,
    ncp_bp_phyid_eioa1,
    ncp_bp_phyid_timer,
    ncp_bp_phyid_mpp,
    ncp_bp_phyid_pic,
    ncp_bp_phyid_eioa0,
    ncp_bp_phyid_pab,
    ncp_bp_phyid_bpagg,
    ncp_bp_phyid_sink = 0x3f
} ncp_bp_phyid_t;

/* 
 * Enum of HW engine BP phyid in acp v3. Needs to match with HW definition.
 */
typedef enum ncp_bp_v3_phyid_e {
    ncp_bp_v3_phyid_cpu     = 0,
    ncp_bp_v3_phyid_spp     = 2,
    ncp_bp_v3_phyid_mtm     = 4,
    ncp_bp_v3_phyid_mpp     = 7,
    ncp_bp_v3_phyid_eioa0   = 9,
    ncp_bp_v3_phyid_bpagg   = 11,
    ncp_bp_v3_phyid_pic     = 12,
    ncp_bp_v3_phyid_pab     = 12,
    ncp_bp_v3_phyid_sed     = 13,
    ncp_bp_v3_phyid_dpi     = 13,    
    ncp_bp_v3_phyid_eioa1   = 14,
    ncp_bp_v3_phyid_timer   = 14,
    ncp_bp_v3_phyid_sink    = 0x3f
} ncp_bp_v3_phyid_t;

/* 
 * Enum of HW engine BP phyid in acp 25xx. Needs to match with HW definition.
 */
typedef enum ncp_bp_25xx_phyid_e {
    ncp_bp_25xx_phyid_cpu     = 0,
    ncp_bp_25xx_phyid_timer   = 0,
    ncp_bp_25xx_phyid_mtm     = 4,
    ncp_bp_25xx_phyid_mpp     = 7,
    ncp_bp_25xx_phyid_eioa0   = 9,
    ncp_bp_25xx_phyid_bpagg   = 11,
    ncp_bp_25xx_phyid_pic     = 12,
    ncp_bp_25xx_phyid_pab     = 12,
    ncp_bp_25xx_phyid_dpi     = 12,
    ncp_bp_25xx_phyid_sed     = 13,
    ncp_bp_25xx_phyid_spp     = 13,    
    ncp_bp_25xx_phyid_eioa1   = 14,
    ncp_bp_25xx_phyid_tdmioa  = 14,
    ncp_bp_25xx_phyid_sink    = 0x3f
} ncp_bp_25xx_phyid_t;

/* 
 * Enum of HW engine BP phyid in acp 55xx. Needs to match with HW definition.
 */
typedef enum ncp_bp_55xx_phyid_e {
    ncp_bp_55xx_phyid_cpu = 0,
    ncp_bp_55xx_phyid_spp = 1,
    ncp_bp_55xx_phyid_sed = 2,
    ncp_bp_55xx_phyid_dpi = 3,
    ncp_bp_55xx_phyid_mtm = 4,
    ncp_bp_55xx_phyid_eioa1 = 5,    
    ncp_bp_55xx_phyid_timer = 6,
    ncp_bp_55xx_phyid_mpp = 7,
    ncp_bp_55xx_phyid_pic = 8,    
    ncp_bp_55xx_phyid_eioa0 = 9,
    ncp_bp_55xx_phyid_pab = 10,
    ncp_bp_55xx_phyid_bpagg = 11,
    ncp_bp_55xx_phyid_isb = 12,
    ncp_bp_55xx_phyid_eioa2 = 7,
    ncp_bp_55xx_phyid_eioa3 = 1,
    ncp_bp_55xx_phyid_eioa4 = 2,
    ncp_bp_55xx_phyid_eioa5 = 3,
    ncp_bp_55xx_phyid_eioa6 = 4,
    ncp_bp_55xx_phyid_eioa7 = 5,
    ncp_bp_55xx_phyid_isbs = 6,
    ncp_bp_55xx_phyid_sink = 0x3f
} ncp_bp_55xx_phyid_t;

/* 
 * Enum of HW engine BP phyid in acp56xx. Needs to match with HW definition.
 */
typedef enum ncp_bp_56xx_phyid_e {
    ncp_bp_56xx_phyid_cpu = 0,
    ncp_bp_56xx_phyid_spp = 1,
    ncp_bp_56xx_phyid_sed = 2,
    ncp_bp_56xx_phyid_dpi = 3,
    ncp_bp_56xx_phyid_mtm = 4,
    ncp_bp_56xx_phyid_eioa1 = 5,    
    ncp_bp_56xx_phyid_timer = 6,
    ncp_bp_56xx_phyid_mpp = 7,
    ncp_bp_56xx_phyid_pic = 8,    
    ncp_bp_56xx_phyid_eioa0 = 9,
    ncp_bp_56xx_phyid_pab = 10,
    ncp_bp_56xx_phyid_bpagg = 11,
    ncp_bp_56xx_phyid_isb = 12,
    ncp_bp_56xx_phyid_bpagg2 = 0,
    ncp_bp_56xx_phyid_eioa2 = 1,
    ncp_bp_56xx_phyid_eioa3 = 2,
    ncp_bp_56xx_phyid_eioa4 = 3,
    ncp_bp_56xx_phyid_eioa5 = 4,
    ncp_bp_56xx_phyid_eioa6 = 5,
    ncp_bp_56xx_phyid_eioa7 = 6,
    ncp_bp_56xx_phyid_isbs = 7,
    ncp_bp_56xx_phyid_sink = 0x3f
} ncp_bp_56xx_phyid_t;

/* 
 * Enum of HW engine BP phyid in acp 55xx. Needs to match with HW definition.
 */
typedef enum ncp_bp_xlf_phyid_e {
    ncp_bp_xlf_phyid_cpu = 0,
    ncp_bp_xlf_phyid_spp = 1,
    ncp_bp_xlf_phyid_sed = 2,
    ncp_bp_xlf_phyid_dpi = 3,
    ncp_bp_xlf_phyid_mtm = 4,
    ncp_bp_xlf_phyid_eioa1 = 5,    
    ncp_bp_xlf_phyid_timer = 6,
    ncp_bp_xlf_phyid_mpp = 7,
    ncp_bp_xlf_phyid_pic = 8,    
    ncp_bp_xlf_phyid_eioa0 = 9,
    ncp_bp_xlf_phyid_pab = 10,
    ncp_bp_xlf_phyid_bpagg = 11,
    ncp_bp_xlf_phyid_isb = 12,
    ncp_bp_xlf_phyid_decoder = 13,
    ncp_bp_xlf_phyid_erif0 = 14,
    ncp_bp_xlf_phyid_erif1 = 15,
    ncp_bp_xlf_phyid_rif0 = 16,
    ncp_bp_xlf_phyid_rif1 = 17,
    ncp_bp_xlf_phyid_bpagg2 = 0,
    ncp_bp_xlf_phyid_eioa2 = 1,
    ncp_bp_xlf_phyid_eioa3 = 2,
    ncp_bp_xlf_phyid_eioa4 = 3,
    ncp_bp_xlf_phyid_eioa5 = 4,
    ncp_bp_xlf_phyid_isbs = 5,
    ncp_bp_xlf_phyid_isbs1 = 6,
    ncp_bp_xlf_phyid_sink = 0x3f
} ncp_bp_xlf_phyid_t;

/* 
 * Enum of HW engine BP phyid in acp 35xx. Needs to match with HW definition.
 */
typedef enum ncp_bp_35xx_phyid_e {
    ncp_bp_35xx_phyid_cpu = 0,
    ncp_bp_35xx_phyid_spp = 1,
    ncp_bp_35xx_phyid_mtm = 2,
    ncp_bp_35xx_phyid_mpp = 3,
    ncp_bp_35xx_phyid_eioa0 = 4,
    ncp_bp_35xx_phyid_pic = 9,
    ncp_bp_35xx_phyid_pab = 9,
    ncp_bp_35xx_phyid_sed = 10,
    ncp_bp_35xx_phyid_dpi = 10,
    ncp_bp_35xx_phyid_bpagg = 11,
    ncp_bp_35xx_phyid_timer = 12,
    ncp_bp_35xx_phyid_sink = 0x3f
} ncp_bp_35xx_phyid_t;

/* type of instance range */
typedef enum
{
    ncp_cow_inst_range_task_queue = 0,  /* task queue instance range */
    ncp_cow_inst_range_logical_queue    /* logical queue instance range */
} ncp_cow_inst_range_t;

    /*
     * VFLOW LSB when flow data is not used.
     */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      toid_lsb2b            :  2; /* This field is the LSB 2b
                                                * of the TOID. MSB 10b is 
                                                * defined in ncp_nu_til_vflowh_no_flow_32b_t
                                                */
     unsigned      reserved              :  2; /* RESERVED */
     unsigned      entry_size            :  4; /* This field is the entry
                                                * size. A value of 0 corresponds
                                                * to size of 16B, 1 corresponds
                                                * to 32B, 2 corresponds
                                                * to 64B, 3 corresponds
                                                * to 128B and 15 corresponds
                                                * to 0B size. Rest values
                                                * are reserved. When the
                                                * size is 0 the address
                                                * field carries the header
                                                * as defined in the task
                                                * structure document
                                                */
     unsigned      max_index             : 24; /* This field is the maximum
                                                * value of the index
                                                */
#else    /* Little Endian */
     unsigned      max_index             : 24; /* This field is the maximum
                                                * value of the index
                                                */
     unsigned      entry_size            :  4; /* This field is the entry
                                                * size. A value of 0 corresponds
                                                * to size of 16B, 1 corresponds
                                                * to 32B, 2 corresponds
                                                * to 64B, 3 corresponds
                                                * to 128B and 15 corresponds
                                                * to 0B size. Rest values
                                                * are reserved. When the
                                                * size is 0 the address
                                                * field carries the header
                                                * as defined in the task
                                                * structure document
                                                */
     unsigned      reserved              :  2; /* RESERVED */
     unsigned      toid_lsb2b            :  2; /* This field is the LSB 2b
                                                * of the TOID. MSB 10b is 
                                                * defined in ncp_nu_til_vflowh_no_flow_32b_t
                                                */
#endif
} ncp_nu_til_vflowl_no_flow_32b_t;


    /*
     * VFLOW MSB when flow data is not used
     */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved              :  7; /* RESERVED */
     unsigned      valid                 :  1; /* Valid bit */
     unsigned      task_prio             :  3; /* task priority */
     unsigned      debug_field           :  2; /* debug field */
     unsigned      trace_en              :  1; /* trace enable */
     unsigned      template_id           :  8; /* template id */
     unsigned      toid_msb10b           : 10; /* This field is the MSB
                                                * 10b of the TOID. Lower 2b is 
                                                * defined in ncp_nu_til_vflowl_32b_t.
                                                */
#else    /* Little Endian */
     unsigned      toid_msb10b           : 10; /* This field is the MSB
                                                * 10b of the TOID. Lower 2b is 
                                                * defined in ncp_nu_til_vflowl_32b_t.
                                                */
     unsigned      template_id           :  8; /* template id */
     unsigned      trace_en              :  1; /* trace enable */
     unsigned      debug_field           :  2; /* debug field */
     unsigned      task_prio             :  3; /* task priority */
     unsigned      valid                 :  1; /* Valid bit */
     unsigned      reserved              :  7; /* RESERVED */
#endif
} ncp_nu_til_vflowh_no_flow_32b_t;

/* target defines for COW sub modules */
#define NCP_COW_TCLD_TARGET_ID      0x0
#define NCP_COW_TRECV_TARGET_ID     0x0
#define NCP_COW_TIL_TARGET_ID       0x1
#define NCP_COW_TILS2_TARGET_ID     0x1
#define NCP_COW_TDGL_TARGET_ID      0x2
#define NCP_COW_TDGLS2_TARGET_ID    0x2
#define NCP_COW_TGL_TARGET_ID       0x3
#define NCP_COW_TSEND_TARGET_ID     0x3
#define NCP_COW_MCIP_TARGET_ID      0x4
#define NCP_COW_PB_MMBS_TARGET_ID   0x4
#define NCP_COW_CNAL_TARGET_ID      0x5
#define NCP_COW_TQ_MMBS_TARGET_ID   0x5
#define NCP_COW_CAAL_TARGET_ID      0x5
#define NCP_COW_TCLS_TARGET_ID      0x6
#define NCP_COW_PB_CNAL_TARGET_ID   0x6
#define NCP_COW_TQ_CNAL_TARGET_ID   0x7
#define NCP_COW_TSL_TARGET_ID       0x7
#define NCP_COW_BCN_SLAVE_TARGET_ID 0x8

/* Target defines for MTM specific COW modules */
#define NCP_COW_MTM_CNAL2_TARGET_ID             0xa
#define NCP_COW_MTM_TIL_LAUNCH_TARGET_ID        0xb
#define NCP_COW_MTM_TIL_INP_MERGE_TARGET_ID     0xc
#define NCP_COW_MTM_TGL_UNICAST_TARGET_ID       0xd

/* macro for otemp access */
#define NCP_NU_TGL_OUTPUT_TEMPLATE(tid, word)   (0x00001000 + (16 * (tid)) + (4 * (word)))

#if !defined(NCP_KERNEL)

/* Per engine COW initialization function */
NCP_API ncp_st_t
ncp_cow_engine_init(ncp_hdl_t ncpHdl, ncp_engine_type_t engine, 
                    ncp_map_t *engineMap);

/* Per engine COW online function */
NCP_API ncp_st_t
ncp_cow_engine_online(ncp_hdl_t ncpHdl, ncp_engine_type_t engine, 
                      ncp_map_t *engineMap);

/* NCAv3 MCIP online function */
NCP_API ncp_st_t
ncp_ncav3_mcip_online(ncp_hdl_t hdl, ncp_engine_type_t engine);


/* Function to setup chip profile depending upon the hardware */
NCP_API ncp_st_t
ncp_cow_setup_chip_profile(ncp_hdl_t ncpHdl);

/*************************************
 * Functions for TIL
 *************************************/

/* set input param definition */
NCP_API ncp_st_t
ncp_cow_til_input_param_set(ncp_hdl_t hdl, ncp_engine_type_t engine, 
                            ncp_uint8_t templateId, char *paramDef,
                            char *paramSel, ncp_uint8_t paramDefLen,
			    ncp_bool_t isEioaLaunch);

NCP_API ncp_st_t
ncp_cow_til_vflow_table_clear(ncp_hdl_t hdl, ncp_engine_type_t engine);

NCP_API ncp_st_t
ncp_cow_til_input_template_clear(ncp_hdl_t hdl, ncp_engine_type_t engine);

/* set vflow table entry when flows are enabled */
NCP_API ncp_st_t
ncp_cow_til_vflow_table_flow_set(ncp_hdl_t hdl, ncp_engine_type_t engine, 
                                 ncp_uint8_t vpId, ncp_uint64_t baseAddr,
                                 ncp_uint8_t entrySize, ncp_uint32_t maxEntries);

/* set vflow table entry when flows are disabled */
NCP_API ncp_st_t
ncp_cow_til_vflow_table_no_flow_set(ncp_hdl_t hdl, ncp_engine_type_t engine, 
                                    ncp_uint8_t vpId,
                                    ncp_uint8_t templateId, ncp_uint8_t taskPrio,
                                    ncp_uint8_t debug);

NCP_API ncp_st_t
ncp_cow_til_input_queue_weight_set(ncp_hdl_t hdl, ncp_engine_type_t engine, 
                           ncp_uint32_t queue, ncp_uint32_t wrrWeight);

/*************************************
 * Functions for TCLD
 *************************************/

NCP_API ncp_st_t
ncp_cow_tcld_runtime_bp_dest_set(ncp_hdl_t hdl, ncp_uint8_t destEnginePhyId, 
                         ncp_uint32_t destId, ncp_engine_type_t srcEngine, 
                         ncp_uint32_t srcInst, ncp_uint8_t srcPrio);

NCP_API ncp_st_t
ncp_cow_tcld_runtime_bp_dest_unset(ncp_hdl_t hdl, ncp_engine_type_t srcEngine, 
                                   ncp_uint32_t srcInst, ncp_uint8_t srcPrio);

NCP_API ncp_st_t
ncp_cow_tcld_priority_map_queue_index_get(ncp_hdl_t hdl,
                        ncp_engine_type_t engine,
                        ncp_cow_inst_range_t instRange,
                        ncp_uint8_t prio,
                        ncp_uint8_t *queueIndex);

NCP_API ncp_st_t
ncp_cow_tcld_task_queue_enable(ncp_hdl_t hdl, ncp_engine_type_t engine, 
                               ncp_uint32_t queue, ncp_bool_t enable);

NCP_API ncp_st_t
ncp_cow_tcld_thresh_group_id_set(ncp_hdl_t hdl, ncp_engine_type_t engine, 
                                 ncp_uint32_t queue, ncp_uint32_t threshGroupId);

/*************************************
 * Functions for TGL
 *************************************/

/* clear output template memory */
NCP_API ncp_st_t
ncp_cow_tgl_output_template_clear(ncp_hdl_t hdl, ncp_engine_type_t engine);

/* set output template */
NCP_API ncp_st_t
ncp_cow_tgl_output_template_set(ncp_hdl_t hdl, ncp_engine_type_t engine, 
                                ncp_uint8_t templateId, char *outputTemplate,
                                ncp_uint16_t outParamSize);

NCP_API ncp_st_t
ncp_cow_tgl_output_template_update(ncp_hdl_t hdl, ncp_engine_type_t engine, 
                                   ncp_uint8_t templateId, 
                                   ncp_uint8_t  nextTemplateId);

/*************************************
 * Access functions to retrieve COW info
 *************************************/

/* return if an engine is launch engine */
NCP_API ncp_st_t
ncp_cow_is_launch_engine(ncp_hdl_t ncpHdl, ncp_engine_type_t engine, 
                         ncp_bool_t *pLaunchEngine);

/* return engine name */
NCP_API const char *
ncp_cow_engine_enum2str(ncp_engine_type_t engine);

/* return enum from name */
NCP_API ncp_engine_type_t
ncp_cow_engine_str2enum(char *name);

/* return specific engine name. Like eioa1 instead of eioa */
NCP_API const char *
ncp_cow_engine_enum2str_specific(ncp_engine_type_t engine);

/* return enum from name looking like eioa0 */
NCP_API ncp_engine_type_t
ncp_cow_engine_str2enum_specific(char *name);

/* return node id */
NCP_API ncp_st_t
ncp_cow_engine_nodeid_get(ncp_hdl_t ncpHdl, ncp_engine_type_t engine, 
                          ncp_uint16_t *pNodeId);

/* get num templates */
NCP_API ncp_st_t
ncp_cow_engine_num_templates_get(ncp_hdl_t ncpHdl, ncp_engine_type_t engine, 
                                 ncp_uint16_t *pNumTemplates);

/* return the bp engine phy id */
NCP_API ncp_st_t
ncp_cow_bp_engine_phy_id_get(ncp_hdl_t ncpHdl, ncp_engine_type_t engine, 
                             ncp_uint8_t *pBpPhyId);

/* get BP engine phy id by name */
NCP_API ncp_st_t
ncp_cow_bp_engine_phy_id_get_by_name_ext(ncp_hdl_t ncpHdl, char *engineStr,
                                         ncp_uint8_t *pBpPhyId);

/* get bp phy id sink for the chip */
NCP_API ncp_st_t
ncp_cow_chip_bp_phy_id_sink_get(ncp_hdl_t hdl, ncp_uint8_t *bpPhyIdSink);

NCP_API ncp_uint8_t
ncp_cow_adjust_vflow_template_id(ncp_engine_type_t engine, ncp_uint8_t templateId);

NCP_API ncp_bool_t
ncp_cow_is_engine_present(ncp_engine_type_t engine);

NCP_API ncp_st_t
ncp_cow_nca_queue_size_get(ncp_hdl_t ncpHdl, ncp_uint32_t queueId,
                           ncp_bool_t *pModeTask, ncp_uint32_t  *pNumItems);

NCP_API ncp_uint32_t
ncp_cow_vflow_region_id_get(ncp_hdl_t ncpHdl, ncp_engine_type_t engine);

NCP_API ncp_uint32_t
ncp_cow_otemp_region_id_get(ncp_hdl_t ncpHdl, ncp_engine_type_t engine);

#endif /* #if !defined(NCP_KERNEL) */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _NCP_COW_H_ */

