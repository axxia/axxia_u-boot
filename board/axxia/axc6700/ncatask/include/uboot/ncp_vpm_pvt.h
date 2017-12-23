/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


#ifndef _NCP_VPM_PVT_H_
#define _NCP_VPM_PVT_H_
#include "uboot/ncp_cow.h"
#include "uboot/ncp_dev_pvt.h"
#include "uboot/ncp_vpm_ext.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definitions of config strings
 */

#define NCP_NAME                "name"
#define NCP_SIZE                "bytes"
#define NCP_TEMPLATE_ID         "templateId"
#define NCP_TASK_PRIORITY       "taskPriority"
#define NCP_TASK_LOG            "allowTaskLogging"

#define NCP_VIRTUAL_PIPELINES   "VirtualPipelines"
#define NCP_FLOW_DATA_BASE_ADDR "flowDataBaseAddress"

#define NCP_LE_EIOA             "EIOA"
#define NCP_LE_MPP              "MPP"
#define NCP_LE_CPU              "CPU"
#define NCP_LE_EXPANDER         "Expander"
#define NCP_LE_TDMIOA           "TDMIOA"
#define NCP_LE_RIF              "RIF"
#define NCP_LE_EMC              "EMC"
#define NCP_LE_ERIF             "ERIF"

#define NCP_VIRTUAL_PIPELINE    "VirtualPipeline"
#define NCP_VP_NAME             NCP_NAME
#define NCP_VP_ID               "vpId"
#define NCP_VP_FLOW_BASE_ADDR   "flowBaseAddr"
#define NCP_VP_FLOW_ENTRY_SZ    "flowEntrySize"
#define NCP_VP_FLOW_ENTRY_DOMAIN    "managementDomain"
#define NCP_VP_MAX_FLOWS        "numFlows"
#define NCP_VP_C_COOKIE         "cCookie"
#define NCP_VP_TASK_PRIO        NCP_TASK_PRIORITY
#define NCP_VP_TASK_LOG         NCP_TASK_LOG

#define NCP_FLOW_ENTRIES            "FlowEntries"
#define NCP_FLOW_ENTRY              "FlowEntry"
#define NCP_FLOW_ENTRY_ID           "id"
#define NCP_FLOW_ENTRY_TEMPLATE_ID  NCP_TEMPLATE_ID
#define NCP_FLOW_ENTRY_TASK_PRIO    NCP_TASK_PRIORITY
#define NCP_FLOW_ENTRY_DATA         "flowData"
#define NCP_FLOW_ENTRY_TASK_LOG     NCP_TASK_LOG

#define NCP_ENGINE_SEQUENCE     "EngineSequence"
#define NCP_PIPE_NAME           NCP_NAME
#define NCP_ES_FLOW_PARAM_SZ    "flowParamSize"

#define NCP_FLOW_PARAM          "FlowParam"
#define NCP_FLOW_PARAM_NAME     NCP_NAME
#define NCP_FLOW_PARAM_SIZE     NCP_SIZE
#define NCP_FLOW_PARAM_TYPE     "type"
#define NCP_FLOW_PARAM_TYPE_UINT        "UnsignedInt"
#define NCP_FLOW_PARAM_TYPE_SINT        "SignedInt"
#define NCP_FLOW_PARAM_TYPE_BYTES       "ByteArray"
#define NCP_FLOW_PARAM_TYPE_NS_ID       "NamespaceId"
#define NCP_FLOW_PARAM_TYPE_IPV4_ADDR   "IPv4Address"
#define NCP_FLOW_PARAM_TYPE_IPV6_ADDR   "IPv6Address"
#define NCP_FLOW_PARAM_TYPE_MAC_ADDR    "MACAddress"
#define NCP_FLOW_PARAM_TYPE_SED_CE_SCRIPT_REF "SedCEScriptRef"

#define NCP_ENGINE                      "Engine"
#define NCP_ENGINE_TYPE                 "destType"
#define NCP_ENGINE_TEMPLATE_ID          NCP_TEMPLATE_ID
#define NCP_ENGINE_OUT_PARAM_FORMAT     "outputParamSetName"
#define NCP_ENGINE_OUT_PARAM_SIZE       "outputParamsSize"
#define NCP_ENGINE_IN_PARAM_FORMAT      "inputParamSetName"
#define NCP_ENGINE_TEMPLATE_TARGET_SEL  "templateTargetSelect"
#define NCP_ENGINE_INP_TEMPLATE_SEL     "inputTemplateParamSel"
#define NCP_ENGINE_INP_TEMPLATE_DEF     "inputTemplateParamDef"
#define NCP_ENGINE_OUT_TEMPLATE         "outputTemplateData"


/*
 * Data type definitions.
 */

/*
 * Macros to set flow data header. These can be used only when flow data header
 * needs to be set in BE format. Its used for static flow data in config file.
 */

#define NCP_FLOW_DATA_SET_TASK_PRIO_BE(flowData, prio)  \
    {                                                   \
        char *fd = (char *)flowData;                    \
        fd[0] |= ((prio & 0x7) << 5);                   \
    }

#define NCP_FLOW_DATA_GET_TASK_PRIO_BE(flowData, prio)  \
    {                                                   \
        char *fd = (char *)flowData;                    \
        prio = ((fd[0] >> 5) & 0x7);                    \
    }

#define NCP_FLOW_DATA_SET_DBG_BE(flowData, dbg) \
    {                                           \
        char *fd = (char *)flowData;            \
        fd[0] |= ((dbg & 0x3) << 3);            \
    }

#define NCP_FLOW_DATA_GET_DBG_BE(flowData, dbg) \
    {                                           \
        char *fd = (char *)flowData;            \
        dbg = ((fd[0] >> 3) & 0x3);            \
    }

#define NCP_FLOW_DATA_SET_TRACE_EN_BE(flowData, t)  \
    {                                               \
        char *fd = (char *)flowData;                \
        fd[0] |= ((t & 0x1) << 2);                  \
    }

#define NCP_FLOW_DATA_SET_TEMPLATE_ID_BE(flowData, id)  \
    {                                                   \
        char *fd = (char *)flowData;                    \
        fd[0] |= ((id & 0xc0) >> 6);                    \
        fd[1] |= ((id & 0x3f) << 2);                    \
    }

#define NCP_FLOW_DATA_SET_SIZE_BE(flowData, size)   \
    {                                               \
        char *fd = (char *)flowData;                \
        fd[3] |= ((size & 0x60) >> 5);              \
        fd[4] |= ((size & 0x1f) << 3);              \
    }

/*
 * Flow Header and Data structure. This is used by ncp_vp_flow_data_write API.
 * There are BE and LE format of this struct. On a LE processor, the format is
 * converted by encodeFlowData function before writing to sysmem.
 */
typedef struct ncp_flow_data_full_st
{
#ifdef NCP_BIG_ENDIAN
     /* word 0 */
     unsigned      task_prio             :  3; /* task priority */
     unsigned      debug_field           :  2; /* debug field */
     unsigned      trace_en              :  1; /* trace enable */
     unsigned      template_id           :  8; /* template id */
     unsigned      reserved1             :  16;/* reserved */
     unsigned      size_msb2b            :  2; /* exact size of flow data. MSB 2 bits. */
     /* word 1 */
     unsigned      size_lsb5b            :  5; /* exact size of flow data. LSB 5 bits. */
     unsigned      reserved2             :  27;/* reserved */
     /* word 2+ */
     char          flow_data[NCP_FLOW_DATA_MAX_SIZE]; /* upto 128 bytes of flow data */
#else    /* Little Endian */
     /* word 0 */
     unsigned      size_msb2b            :  2; /* exact size of flow data. MSB 2 bits. */
     unsigned      reserved1             :  16;/* reserved */
     unsigned      template_id           :  8; /* template id */
     unsigned      trace_en              :  1; /* trace enable */
     unsigned      debug_field           :  2; /* debug field */
     unsigned      task_prio             :  3; /* task priority */
     /* word 1 */
     unsigned      reserved2             :  27;/* reserved */
     unsigned      size_lsb5b            :  5; /* exact size of flow data. LSB 5 bits. */
     /* word 2+ */
     char          flow_data[NCP_FLOW_DATA_MAX_SIZE]; /* upto 128 bytes of flow data */
#endif
} ncp_flow_data_full_t;

/* macro to calculate the size of flow data header */
#define NCP_FLOW_DATA_HDR_SIZE (sizeof(ncp_flow_data_full_t) - NCP_FLOW_DATA_MAX_SIZE)

/* 
 * Reserved engine for XLF/EMC. EMC is a dummy engine w/o any templates, etc.
 * This value is passed by ASE. RTE skips processing this engine.
 */
#define NCP_ENGINE_EMC 0xff
#define NCP_ENGINE_EMC_STR "emc"

typedef struct ncp_vp_inp_template_s {
    char *templateDef;                  /* template data binary */
    ncp_uint8_t templateDefLen;         /* template def length */
    char *templateSel;                  /* template sel */
} ncp_vp_inp_template_t;

/* hw engine data struct */
typedef struct ncp_engine_s {
    ncp_engine_type_t type;             /* engine type */
    ncp_vp_param_format_t inFormat;     /* input parameter format */
    ncp_vp_param_format_t outFormat;    /* output parameter format */
    ncp_uint8_t templateId;             /* template id, for launch engines,
                                           it refers to either input or output.
                                           for other engines both are same. */
    ncp_uint8_t hwTemplateId;           /* hw template id, can be different from 
                                           templateId for shared cow engines. */
#if !defined(NCP_KERNEL)
    ncp_uint8_t targetSel;              /* target select - to differenciate
                                           between MTM and expander */
    ncp_vp_inp_template_t ipTemplate;   /* input template bitmap */
    char *opTemplate;                   /* output template bitmap */
#endif /* #if !defined(NCP_KERNEL) */
    ncp_uint16_t outParamSize;          /* output template param size */
} NCP_COMPAT_PACKED ncp_engine_t;

typedef enum {
    ncp_flow_param_data_type_uint = 0,
    ncp_flow_param_data_type_sint,
    ncp_flow_param_data_type_bytes,
    ncp_flow_param_data_type_ns_id,
    ncp_flow_param_data_type_ipv4_addr,
    ncp_flow_param_data_type_ipv6_addr,
    ncp_flow_param_data_type_mac_addr,
    ncp_flow_param_data_type_sed_ce_script_ref
} ncp_flow_param_data_type_t;

/* flow param definition */
typedef struct ncp_flow_param_s {
    char *name;                         /* name */
    ncp_uint8_t size;                   /* size */
    ncp_flow_param_data_type_t type;    /* type */
} ncp_flow_param_def_t;

typedef struct ncp_engine_ptr_s {
    NCP_DECLARE_POINTER(ncp_engine_t, engine);
} NCP_COMPAT_PACKED ncp_engine_ptr_t;

/* pipeline data struct */
typedef struct ncp_pipeline_s {
    NCP_DECLARE_POINTER(char, name);    /* pipeline name */
    ncp_uint32_t nameLen;               /* pipeline name length */
    NCP_DECLARE_POINTER(ncp_engine_ptr_t, engines);             /* array of pointers to engines in the pipeline */
    ncp_uint8_t numEngines;             /* number of engines */
    ncp_uint8_t flowParamSize;
#if !defined(NCP_KERNEL)
    ncp_uint8_t numFlowParams;          /* number of flow params */
    ncp_flow_param_def_t **flowParamDef;/* array of pointers to flow param definition */
#endif
} NCP_COMPAT_PACKED ncp_pipeline_t;

/* ncp flow data struct */
typedef struct ncp_vp_flow_s {
    ncp_uint32_t flowId;
    ncp_uint8_t taskPrio;	    /* priority of the task */
    ncp_uint8_t debugFieldV;	/* debug field */
    ncp_uint8_t templateId;	    /* output template id */
    ncp_uint32_t flowDataSize;  /* exact size of flow data */
    char *flowData;
} ncp_vp_flow_t;

typedef void* ncp_vpm_hdl_t;

#define NCP_VP_HDL_COOKIE 0x5a697887

typedef struct ncp_pipeline_ptr_s {
    NCP_DECLARE_POINTER(ncp_pipeline_t, pipeline);
} NCP_COMPAT_PACKED ncp_pipeline_ptr_t;

/* vp data struct */
typedef struct ncp_vp_s {
    NCP_DECLARE_POINTER(char, name);    /* vp name */
    ncp_uint32_t nameLen;               /* vp name length */
    ncp_launch_engine_type_t le;        /* launch engine */
    NCP_DECLARE_POINTER(ncp_pipeline_ptr_t, pipelines); /* pointers to */
                                                      /* all pipelines */
    ncp_uint8_t id;                     /* vp id */
    ncp_uint8_t numPipelines;           /* number of pipelines */
    ncp_uint8_t flowDataDomainId;       /* The owner domain for flow data */
    ncp_uint8_t flowEntrySize;          /* flow size for this vp with padding */
    ncp_int64_t baseAddr NCP_COMPAT_ALIGN64; /* flow data table base address */
    ncp_uint32_t numFlows;              /* max number of flows */
    ncp_int64_t cCodeCookie NCP_COMPAT_ALIGN64; /* per vp c code cookie */
    ncp_uint32_t hdlCookie;             /* vp hdl cookie */
    NCP_DECLARE_HDL(ncp_vpm_hdl_t, vpmHdl); /* handle to vpm */
    ncp_bool_t enTaskParamOpt;          /* enable task param optimization on vp */
#if !defined(NCP_KERNEL)
    ncp_vp_flow_t ** flows;             /* flows defined at config time */
    ncp_uint32_t numStaticFlows;        /* number of flows defined at config time */
    ncp_bool_t pipelineNameNull;        /* TRUE when any of the pipelines dont have a name */
    ncp_uint8_t taskPrio;               /* task prio when flow data not defined */
    ncp_uint8_t debugFieldV;            /* task logging when flow data not defined */
#endif /* #if !defined(NCP_KERNEL) */
} NCP_COMPAT_PACKED ncp_vp_t;

typedef struct ncp_vp_ptr_s {
    NCP_DECLARE_POINTER(ncp_vp_t, vp);
} NCP_COMPAT_PACKED ncp_vp_ptr_t;

/* struct containing all data necessary for vpm */
typedef struct ncp_vpm_s {
    /* pointers to vps based on launching engines */
    /*
    ncp_vp_t **vpTable[ncp_launch_engine_max];
    */
    NCP_DECLARE_POINTER_ARRAY(ncp_vp_ptr_t, vpTable, ncp_launch_engine_max);
    ncp_uint8_t numVps[ncp_launch_engine_max];          /* number of VPs */
    ncp_uint8_t numFlowDataFuncs[ncp_launch_engine_max];/* number of flow data func for each le */
    ncp_uint8_t numNcaTaskParamEncodeFuncs;             /* number of nca task param encode funcs */
    ncp_uint8_t numNcaTaskParamDecodeFuncs;             /* number of nca task param decode funcs */
    NCP_DECLARE_POINTER(ncp_dev_t, ncpDevHdl);          /* ncp dev handle */
    ncp_int64_t flowDataBaseAddr NCP_COMPAT_ALIGN64;    /* base addr for all flow data */
} NCP_COMPAT_PACKED ncp_vpm_t;

/* Data structure to store flow data function pointers */
typedef struct ncp_vpm_flow_data_func_ptr_st {
    ncp_flow_data_encode_fn flowDataEncodeFn;   /* flow data encode func */
    ncp_flow_data_decode_fn flowDataDecodeFn;   /* flow data decode func */
} ncp_vpm_flow_data_func_ptr_t;


#define ncp_vp_validate_handle(_pvpHdl) \
({ \
        ncp_st_t _st = NCP_ST_SUCCESS; \
        ncp_vp_t *_mvpHdl = (ncp_vp_t *)_pvpHdl; \
        if ( ( _mvpHdl == NULL) ||  \
                         ( _mvpHdl->hdlCookie != NCP_VP_HDL_COOKIE)) { \
                        _mvpHdl = NULL;                          \
                        _st = NCP_ST_VPM_INVALID_VP_HDL;  \
                           }\
           _st; \
})


/*
 * Per-process variables to store flow data and task param encode/decode
 * function pointers.
 */
extern ncp_vpm_flow_data_func_ptr_t *flowDataFuncTbl[ncp_launch_engine_max];
extern ncp_task_param_encode_fn *ncaTaskParamEncodeFunc;
extern ncp_task_param_decode_fn *ncaTaskParamDecodeFunc;

/*
 * Functions/Macros used by task i/o to call task param encode/decode
 */

#define ncp_vpm_task_param_encode(vpHdl, dest, src) \
{                                                   \
    ncp_vp_t *vp = (ncp_vp_t *)vpHdl;               \
                                                    \
    if(ncaTaskParamEncodeFunc != NULL &&            \
       ncaTaskParamEncodeFunc[vp->id] != NULL ) {   \
        ncaTaskParamEncodeFunc[vp->id](dest, src);  \
    }                                               \
    /* Task i/o needs memcpy if buf is different */ \
    else if(dest != src) {                          \
        ncp_memcpy(dest, src, 32);                  \
    }                                               \
}

#define ncp_vpm_task_param_decode(templateId, dest, src)            \
{                                                                   \
    if(ncaTaskParamDecodeFunc != NULL &&                            \
       ncaTaskParamDecodeFunc[templateId] != NULL) {                \
        ncaTaskParamDecodeFunc[templateId](dest, src);              \
    }                                                               \
}


#ifndef NCP_VPM_DISABLE_ERROR_CHECK

#define ncp_vp_is_cpu_launch_engine(vpHdl)                          \
{                                                                   \
    ncp_vp_t *_vp = (ncp_vp_t *)vpHdl;                              \
                                                                    \
    if(!_vp) {                                                      \
        NCP_CALL(NCP_ST_VPM_VP_NOT_FOUND);                          \
    }                                                               \
                                                                    \
    if(_vp->le != ncp_launch_engine_cpu) {                          \
        NCP_CALL(NCP_ST_VPM_VP_NOT_CPU_LAUNCH_ENGINE);              \
    } else {                                                        \
        ncpStatus = NCP_ST_SUCCESS;                                 \
    }                                                               \
}

#if 0
#define ncp_vp_cpu_terminate_template_id_get(vpHdl, pipelineId, templateId) \
{                                                                       \
    ncp_vp_t *_vp = (ncp_vp_t *)vpHdl;                                  \
                                                                        \
    ncp_pipeline_t *_pPipeline = NULL;                                  \
    ncp_engine_t *_pLastEngine = NULL;                                  \
                                                                        \
    /* check if pipelineId is valid */                                  \
    if(pipelineId >= _vp->numPipelines ||                               \
       !_vp->pipelines[pipelineId]) {                                   \
        NCP_CALL(NCP_ST_VPM_ENGINE_SEQUENCE_NOT_FOUND);                 \
    }                                                                   \
                                                                        \
    _pPipeline = _vp->pipelines[pipelineId];                            \
    if(!_pPipeline->engines)                                            \
        NCP_CALL(NCP_ST_VPM_ENGINE_SEQUENCE_NOT_CPU_TERMINATING);       \
                                                                        \
    _pLastEngine = _pPipeline->engines[_pPipeline->numEngines - 1];     \
                                                                        \
    if(_pLastEngine && _pLastEngine->type == ncp_engine_cpu) {          \
        templateId = _pLastEngine->templateId;                          \
    } else {                                                            \
        NCP_CALL(NCP_ST_VPM_ENGINE_SEQUENCE_NOT_CPU_TERMINATING);       \
    }                                                                   \
 }
#endif
#else /* !NCP_DISABLE_ERROR_CHECK */

#define ncp_vp_is_cpu_launch_engine(vpHdl)                          \
{                                                                   \
    ncp_vp_t *_vp = (ncp_vp_t *)vpHdl;                              \
                                                                    \
    if(_vp->le != ncp_launch_engine_cpu) {                          \
        NCP_CALL(NCP_ST_VPM_VP_NOT_CPU_LAUNCH_ENGINE);              \
    } else {                                                        \
        ncpStatus = NCP_ST_SUCCESS;                                 \
    }                                                               \
}

#if 0
#define ncp_vp_cpu_terminate_template_id_get(vpHdl, pipelineId, templateId) \
{                                                                       \
    ncp_vp_t *vp = (ncp_vp_t *)vpHdl;                                   \
                                                                        \
    if(vp->pipelines[pipelineId]->engines[vp->pipelines[pipelineId].numEngines - 1]->type ==    \
       ncp_engine_cpu) {                                                \
        templateId = vp->pipelines[pipelineId]->engines[vp->pipelines[pipelineId].numEngines - 1]->templateId; \
    } else {                                                            \
        NCP_CALL(NCP_ST_VPM_ENGINE_SEQUENCE_NOT_CPU_TERMINATING);       \
    }                                                                   \
}
#endif

#endif /* NCP_DISABLE_ERROR_CHECK */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _NCP_VPM_PVT_H_ */
