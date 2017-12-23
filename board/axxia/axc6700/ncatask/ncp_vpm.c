/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.              *
 **                                                                       *
 **************************************************************************/

#include <common.h>
#include "uboot/ncp_sal_types_linux.h"
#include "uboot/ncp_task_basetypes.h"

#include "uboot/ncp_sal.h"

#if !defined(NCP_KERNEL)

#include "uboot/ncp.h"
#include "uboot/ncp_pvt.h"
#include "uboot/ncp_dev.h"

#endif /* #ifdef NCP_KERNEL */

#include "uboot/ncp_vpm.h"
#include "uboot/ncp_vpm_ext.h"
#include "uboot/ncp_vpm_pvt.h"


/*
 * Per-process variables to store flow data and task param encode/decode
 * function pointers.
 */

/* this is indexed by templateId */
ncp_vpm_flow_data_func_ptr_t *flowDataFuncTbl[ncp_launch_engine_max];

/* this is indexed by vpId */
ncp_task_param_encode_fn *ncaTaskParamEncodeFunc = NULL;

/* this is indexed by templateId */
ncp_task_param_decode_fn *ncaTaskParamDecodeFunc = NULL;

/*
 * reference count to make sure the memory is freed only when the last
 * thread/process is detached.
 */
ncp_uint32_t numUsers = 0;

/* Forward declaration */
#if defined(NCP_KERNEL)
ncp_st_t ncp_vpm_kernel_destroy(ncp_dev_hdl_t devHdl);
#endif

/*
 * Launch engine strings.
 * This needs to be in same sequence as ncp_launch_engine_type_t
 */
#if !defined(NCP_KERNEL)
static char __maybe_unused
launchEngineStr[ncp_launch_engine_max][10] =
{
    NCP_LE_EIOA,
    NCP_LE_MPP,
    NCP_LE_CPU,
    NCP_LE_EXPANDER,
    NCP_LE_TDMIOA,
    NCP_LE_RIF,
    NCP_LE_EMC,
    NCP_LE_ERIF
};
#endif

NCP_EXPORT_SYMBOL(ncp_vp_handle_get);
NCP_EXPORT_SYMBOL(ncp_vp_id_get);
NCP_EXPORT_SYMBOL(ncp_vp_num_flows_get);
NCP_EXPORT_SYMBOL(ncp_vp_flow_data_func_set);
NCP_EXPORT_SYMBOL(ncp_vp_task_param_decode_func_set);
NCP_EXPORT_SYMBOL(ncp_vp_task_param_encode_func_set);
NCP_EXPORT_SYMBOL(ncp_vp_task_param_decode_func_get);
NCP_EXPORT_SYMBOL(ncp_vp_task_param_encode_func_get);
NCP_EXPORT_SYMBOL(ncp_vp_engine_seq_id_get);
NCP_EXPORT_SYMBOL(ncp_vp_cpu_terminate_template_id_get);

#if defined(NCP_KERNEL)

ncp_st_t ncp_dev_handle_check(ncp_dev_t *dev);

#endif

#if !defined(NCP_KERNEL)

#define NCP_VPM_ALIGN_256B(addr) (((addr) & 0xff) ? \
            ((addr) + 0x100 - ((addr) & 0xff)) : (addr))

#endif /* #if !defined(NCP_KERNEL) */


#ifndef NCP_KERNEL

extern ncp_bool_t
ncp_config_is_image_loaded(ncp_t *ncp, ncp_uint16_t nodeId);

#endif /* #ifdef NCP_KERNEL */


ncp_st_t
ncp_vp_handle_get(ncp_hdl_t  ncpHdl, ncp_uint64_t cookie, ncp_bool_t bCheckCookie,
                  ncp_launch_engine_type_t type,
                  const char *vpName, ncp_vp_hdl_t *vpHdl)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
#if defined(NCP_KERNEL)
    ncp_dev_t *hdl = (ncp_dev_t *)ncpHdl;
#else /* !(#ifdef NCP_KERNEL) */
    ncp_t *hdl = (ncp_t *)ncpHdl;
#endif /* #ifdef NCP_KERNEL */
    ncp_vpm_t *vpmHdl = NULL;
    ncp_vp_t *vp = NULL;
    int indx = 0;
    
    NCP_TRACEPOINT(Intel_AXXIA_ncp_vpm, ncp_vp_handle_get_entry,  NCP_MSG_ENTRY, "ncpHdl=%p cookie=%"PRIu64" bCheckCookie=%d type=%d \n", 
            ncpHdl,cookie,bCheckCookie, type);
#if defined(NCP_KERNEL)
    NCP_CALL(ncp_dev_handle_check(hdl));
#else /* !(#ifdef NCP_KERNEL) */
    NCP_CALL(NCP_CONFIG_VALIDATE_HANDLE(hdl));
#endif /* #ifdef NCP_KERNEL */

    if(!hdl->vpmHdl) {
        NCP_CALL(NCP_ST_INVALID_HANDLE);
    }

    if(type < ncp_launch_engine_min || type >= ncp_launch_engine_max) {
        NCP_CALL(NCP_ST_VPM_INVALID_LAUNCH_ENGINE);
    }

    if(!vpName) {
        NCP_CALL(NCP_ST_VPM_INVALID_VP_NAME);
    }

    vpmHdl = (ncp_vpm_t *)hdl->vpmHdl;

    if(!vpmHdl->numVps || vpmHdl->numVps[type] == 0 ||
       !vpmHdl->NCP_POINTER_ARRAY(vpTable, type)) {
        NCP_CALL(NCP_ST_VPM_VP_NOT_FOUND);
    }

    /* loop thru the vps to get the required vp */
    for(indx = 0; indx < vpmHdl->numVps[type]; indx++) {
        vp = vpmHdl->NCP_POINTER_ARRAY(vpTable, type)[indx].NCP_POINTER(vp);
        if(strcmp(vp->NCP_POINTER(name), vpName) == 0) {
            break;
        }
    }

    if(indx == vpmHdl->numVps[type]) {
        NCP_CALL(NCP_ST_VPM_VP_NOT_FOUND);
    }

    /* validate vp handle */
    NCP_CALL(NCP_VP_VALIDATE_HANDLE(vp));
 
    if(bCheckCookie == TRUE && vp->cCodeCookie != cookie) {
        NCP_CALL(NCP_ST_VPM_C_COOKIE_MISMATCH);
    }

    *vpHdl = vp;

NCP_RETURN_LABEL
    NCP_TRACEPOINT(Intel_AXXIA_ncp_vpm, ncp_vp_handle_get_exit,  NCP_MSG_EXIT,"ncpStatus=%d vpHdl=%p\n",ncpStatus, vpHdl?*vpHdl:0);
    return ncpStatus;
}

ncp_st_t
ncp_vp_id_get(ncp_vp_hdl_t vpHdl, ncp_uint8_t *vpId)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_vp_t *vp = (ncp_vp_t *)vpHdl;

    NCP_TRACEPOINT(Intel_AXXIA_ncp_vpm, ncp_vp_id_get_entry,  NCP_MSG_ENTRY, "vpHdl=%p vpId=%p\n", vpHdl,vpId);
    /* validate vp handle */
    NCP_CALL(NCP_VP_VALIDATE_HANDLE(vp));

    *vpId = vp->id;

NCP_RETURN_LABEL
    NCP_TRACEPOINT(Intel_AXXIA_ncp_vpm, ncp_vp_id_get_exit,  NCP_MSG_EXIT,"ncpStatus=%d vpId=%d\n",ncpStatus,vpId?*vpId:0);
    return ncpStatus;
}

ncp_st_t
ncp_vp_name_get(ncp_vp_hdl_t vpHdl, char *vpName, ncp_uint32_t nameLen)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_vp_t *vp = (ncp_vp_t *)vpHdl;

    /* validate vp handle */
    ncp_vp_validate_handle(vp);

    NCP_ASSERT(nameLen > vp->nameLen, NCP_VPM_INVALID_VP_NAME_LEN);

    ncp_strcpy(vpName, vp->NCP_POINTER(name));

ncp_return:
    return ncpStatus;
}

ncp_st_t
ncp_vp_num_flows_get(ncp_vp_hdl_t vpHdl, ncp_uint32_t *numFlows)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_vp_t *vp = (ncp_vp_t *)vpHdl;

    NCP_TRACEPOINT(Intel_AXXIA_ncp_vpm, ncp_vp_num_flows_get_entry,  NCP_MSG_ENTRY, "vpHdl=%p numFlows=%p\n", vpHdl,numFlows);
    /* validate vp handle */
    NCP_CALL(NCP_VP_VALIDATE_HANDLE(vp));

    *numFlows = vp->numFlows;

NCP_RETURN_LABEL
    NCP_TRACEPOINT(Intel_AXXIA_ncp_vpm, ncp_vp_num_flows_get_exit,  NCP_MSG_EXIT,"ncpStatus=%d numFlows=%d\n",ncpStatus, numFlows?*numFlows:0);
    return ncpStatus;
}

ncp_st_t
ncp_vp_flow_data_func_set(ncp_vp_hdl_t vpHdl,
                          ncp_uint8_t engineSeqId,
                          ncp_flow_data_encode_fn encode,
                          ncp_flow_data_decode_fn decode)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_vp_t *vp = (ncp_vp_t *)vpHdl;
    ncp_uint8_t templateId = 0;
    ncp_vpm_t *vpmHdl = NULL;

    NCP_TRACEPOINT(Intel_AXXIA_ncp_vpm, ncp_vp_flow_data_func_set_entry,  NCP_MSG_ENTRY, "vpHdl=%p engineSeqId=%d encode=%p decode=%p\n", 
            vpHdl,engineSeqId,encode,decode);
    /* validate vp handle */
    NCP_CALL(NCP_VP_VALIDATE_HANDLE(vp));
    vpmHdl = vp->NCP_POINTER(vpmHdl);

    NCP_ASSERT(engineSeqId < vp->numPipelines,
               NCP_ST_VPM_ENGINE_SEQUENCE_NOT_FOUND);

    templateId = vp->NCP_POINTER(pipelines)[engineSeqId].NCP_POINTER(pipeline)->NCP_POINTER(engines)[0].NCP_POINTER(engine)->templateId;
    NCP_ASSERT(templateId < vpmHdl->numFlowDataFuncs[vp->le],
               NCP_ST_VPM_ENGINE_SEQUENCE_NOT_FOUND);

    /* update the function pointers */
    flowDataFuncTbl[vp->le][templateId].flowDataEncodeFn = encode;
    flowDataFuncTbl[vp->le][templateId].flowDataDecodeFn = decode;

NCP_RETURN_LABEL
    NCP_TRACEPOINT(Intel_AXXIA_ncp_vpm, ncp_vp_flow_data_func_set_exit,  NCP_MSG_EXIT,"ncpStatus=%d\n",ncpStatus);
    return ncpStatus;
}

ncp_st_t
ncp_vp_task_param_decode_func_set(ncp_vp_hdl_t vpHdl,
                                  ncp_uint8_t engineSeqId,
                                  ncp_task_param_decode_fn decode)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_vp_t *vp = (ncp_vp_t *)vpHdl;
    ncp_uint8_t templateId = 0;
    ncp_vpm_t *vpmHdl = NULL;
    
    NCP_TRACEPOINT(Intel_AXXIA_ncp_vpm, ncp_vp_task_param_decode_func_set_entry,  NCP_MSG_ENTRY, "vpHdl=%p engineSeqId=%d decode=%p \n", 
            vpHdl, engineSeqId,decode);
    /* validate vp handle */
    NCP_CALL(NCP_VP_VALIDATE_HANDLE(vp));
    vpmHdl = vp->NCP_POINTER(vpmHdl);

    /* get terminating cpu input template id */
    ncp_vp_cpu_terminate_template_id_get(vpHdl, engineSeqId, &templateId);

    NCP_ASSERT(templateId < vpmHdl->numNcaTaskParamDecodeFuncs,
               NCP_ST_VPM_ENGINE_SEQUENCE_NOT_FOUND);

    /* update the function pointer */
    ncaTaskParamDecodeFunc[templateId] = decode;

NCP_RETURN_LABEL
    NCP_TRACEPOINT(Intel_AXXIA_ncp_vpm, ncp_vp_task_param_decode_func_set_exit,  NCP_MSG_EXIT,"ncpStatus=%d\n",ncpStatus);
    return ncpStatus;
}

ncp_st_t
ncp_vp_task_param_decode_func_get(ncp_vp_hdl_t vpHdl,
                                  ncp_uint8_t engineSeqId,
                                  ncp_task_param_decode_fn *decode)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_vp_t *vp = (ncp_vp_t *)vpHdl;
    ncp_uint8_t templateId = 0;
    ncp_vpm_t *vpmHdl = NULL;

    NCP_TRACEPOINT(Intel_AXXIA_ncp_vpm, ncp_vp_task_param_decode_func_get_entry,  NCP_MSG_ENTRY, "vpHdl=%p engineSeqId=%d decode=%p\n", vpHdl,engineSeqId,decode);
    /* validate vp handle */
    NCP_CALL(NCP_VP_VALIDATE_HANDLE(vp));
    vpmHdl = vp->NCP_POINTER(vpmHdl);

    NCP_ASSERT(decode != NULL, NCP_ST_INVALID_PARAMETER);

    /* get terminating cpu input template id */
    ncp_vp_cpu_terminate_template_id_get(vpHdl, engineSeqId, &templateId);

    NCP_ASSERT(templateId < vpmHdl->numNcaTaskParamDecodeFuncs,
               NCP_ST_VPM_ENGINE_SEQUENCE_NOT_FOUND);

    /* update the function pointer */
    *decode = ncaTaskParamDecodeFunc[templateId];

NCP_RETURN_LABEL
    NCP_TRACEPOINT(Intel_AXXIA_ncp_vpm, ncp_vp_task_param_decode_func_get_exit,  NCP_MSG_EXIT,"ncpStatus=%d decode=%p\n",ncpStatus,decode?*decode:0 );
    return ncpStatus;
}

ncp_st_t
ncp_vp_task_param_encode_func_set(ncp_vp_hdl_t vpHdl,
                                  ncp_task_param_encode_fn encode)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_vp_t *vp = (ncp_vp_t *)vpHdl;
    ncp_vpm_t *vpmHdl = NULL;

    NCP_TRACEPOINT(Intel_AXXIA_ncp_vpm, ncp_vp_task_param_encode_func_set_entry,  NCP_MSG_ENTRY, "vpHdl=%p encode=%p\n", vpHdl,encode);
    /* validate vp handle */
    NCP_CALL(NCP_VP_VALIDATE_HANDLE(vp));

    /* if its not a cpu launch engine, error out */
    ncp_vp_is_cpu_launch_engine(vp);

    vpmHdl = vp->NCP_POINTER(vpmHdl);
    NCP_ASSERT(vp->id < vpmHdl->numNcaTaskParamEncodeFuncs, NCP_ST_VPM_VP_NOT_FOUND);

    /* update the function pointer */
    ncaTaskParamEncodeFunc[vp->id] = encode;

NCP_RETURN_LABEL
    NCP_TRACEPOINT(Intel_AXXIA_ncp_vpm, ncp_vp_task_param_encode_func_set_exit,  NCP_MSG_EXIT,"ncpStatus=%d\n",ncpStatus);
    return ncpStatus;
}

ncp_st_t
ncp_vp_task_param_encode_func_get(ncp_vp_hdl_t vpHdl,
                                  ncp_task_param_encode_fn *encode)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_vp_t *vp = (ncp_vp_t *)vpHdl;
    ncp_vpm_t *vpmHdl = NULL;

    NCP_TRACEPOINT(Intel_AXXIA_ncp_vpm, ncp_vp_task_param_encode_func_get_entry,  NCP_MSG_ENTRY, "vpHdl=%p encode=%p\n", vpHdl,encode);
    /* validate vp handle */
    NCP_CALL(NCP_VP_VALIDATE_HANDLE(vp));

    /* if its not a cpu launch engine, error out */
    ncp_vp_is_cpu_launch_engine(vp);

    vpmHdl = vp->NCP_POINTER(vpmHdl);
    NCP_ASSERT(vp->id < vpmHdl->numNcaTaskParamEncodeFuncs, NCP_ST_VPM_VP_NOT_FOUND);

    NCP_ASSERT(encode != NULL, NCP_ST_INVALID_PARAMETER);

    /* update the function pointer */
    *encode = ncaTaskParamEncodeFunc[vp->id];

NCP_RETURN_LABEL
    NCP_TRACEPOINT(Intel_AXXIA_ncp_vpm, ncp_vp_task_param_encode_func_get_exit,  NCP_MSG_EXIT,
            "ncpStatus=%d encode=%p\n",ncpStatus,encode?*encode:0);
    return ncpStatus;
}

ncp_st_t
ncp_vp_engine_seq_id_get(
            ncp_vp_hdl_t vpHdl,
	        const char *engineSeqName,
            ncp_uint8_t *engineSeqId)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_vp_t *vp = (ncp_vp_t *)vpHdl;
    ncp_pipeline_t *pPipeline = NULL;
    int indx = 0;

    NCP_TRACEPOINT(Intel_AXXIA_ncp_vpm, ncp_vp_engine_seq_id_get_entry,  NCP_MSG_ENTRY, 
            "vpHdl=%p engineSeqId=%p\n", vpHdl,engineSeqId);
    NCP_CALL(NCP_VP_VALIDATE_HANDLE(vp));
    /* weird, but true! */
    if(vp->numPipelines == 0) {
        NCP_CALL(NCP_ST_VPM_ENGINE_SEQUENCE_NOT_FOUND);
    }

    /* if there is only one pipeline, dont need name and return zero. */
    if(vp->numPipelines == 1) {
        *engineSeqId = 0;
        NCP_RETURN( NCP_ST_SUCCESS);
    }
    else {
        if(!engineSeqName) {
            NCP_CALL(NCP_ST_VPM_INVALID_ENGINE_SEQUENCE_NAME);
        }

        /* negative assigment, we assume that seq is not found */
        ncpStatus = NCP_ST_VPM_ENGINE_SEQUENCE_NOT_FOUND;
        for(indx = 0; indx < vp->numPipelines; indx++) {
            pPipeline = vp->NCP_POINTER(pipelines)[indx].NCP_POINTER(pipeline);
            if(strcmp(engineSeqName, pPipeline->NCP_POINTER(name)) == 0) {
                *engineSeqId = indx;
                ncpStatus = NCP_ST_SUCCESS;
            }
        }
    }

NCP_RETURN_LABEL
    NCP_TRACEPOINT(Intel_AXXIA_ncp_vpm, ncp_vp_engine_seq_id_get_exit,  NCP_MSG_EXIT,
            "ncpStatus=%d engineSeqId=%d\n",ncpStatus,engineSeqId?*engineSeqId:0);
    return ncpStatus;
}

/* Check if a vpHdl is launched by the specified engine */
ncp_st_t
ncp_vp_launch_engine_check(ncp_vp_hdl_t vpHdl, ncp_launch_engine_type_t le)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_vp_t *vp = (ncp_vp_t *)vpHdl;

    NCP_TRACEPOINT(Intel_AXXIA_ncp_vpm, ncp_vp_launch_engine_check_entry,  NCP_MSG_ENTRY, "vpHdl=%p le=%d\n", vpHdl,le);
    NCP_CALL(NCP_VP_VALIDATE_HANDLE(vp));

    if (vp->le != le)
    {
        NCP_CALL(NCP_ST_VPM_LAUNCH_ENGINE_MISMATCH);
    }

NCP_RETURN_LABEL
    NCP_TRACEPOINT(Intel_AXXIA_ncp_vpm, ncp_vp_launch_engine_check_exit,  NCP_MSG_EXIT,"ncpStatus=%d\n",ncpStatus);
    return ncpStatus;
}

/* Return the output format of the launch engine (pipeline 0, engine 0) */
ncp_st_t
ncp_vp_out_param_format_get(ncp_vp_hdl_t vpHdl, ncp_vp_param_format_t *format)
{
    ncp_vp_t *vp = (ncp_vp_t *)vpHdl;

    *format = vp->NCP_POINTER(pipelines)[0].NCP_POINTER(pipeline)->NCP_POINTER(engines)[0].NCP_POINTER(engine)->outFormat;

    return NCP_ST_SUCCESS;
}

/* Return the output format of the launch engine (pipeline 0, engine 0) */
ncp_st_t
ncp_vp_in_param_format_get(ncp_vp_hdl_t vpHdl, ncp_vp_param_format_t *format)
{
    ncp_vp_t *vp = (ncp_vp_t *)vpHdl;

    *format = vp->NCP_POINTER(pipelines)[0].NCP_POINTER(pipeline)->NCP_POINTER(engines)[0].NCP_POINTER(engine)->inFormat;

    return NCP_ST_SUCCESS;
}


/* get the cpu terminating template id */
ncp_st_t
ncp_vp_cpu_terminate_template_id_get(
	        ncp_vp_hdl_t vpHdl,
	        ncp_uint8_t engineSeqId,
            ncp_uint8_t *templateId)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_vp_t *vp = (ncp_vp_t *)vpHdl;
    ncp_pipeline_t *pPipeline = NULL;
    ncp_engine_t *pLastEngine = NULL;

    NCP_TRACEPOINT(Intel_AXXIA_ncp_vpm, ncp_vp_cpu_terminate_template_id_get_entry,  NCP_MSG_ENTRY, 
            "vpHdl=%p engineSeqId=%d templateId=%p\n", vpHdl,engineSeqId,templateId);
    NCP_CALL(NCP_VP_VALIDATE_HANDLE(vp));

    /* check if engineSeqId is valid */
    if(engineSeqId >= vp->numPipelines ||
       !vp->NCP_POINTER(pipelines)[engineSeqId].NCP_POINTER(pipeline)) {
        NCP_CALL(NCP_ST_VPM_ENGINE_SEQUENCE_NOT_FOUND);
    }

    NCP_ASSERT(templateId != NULL, NCP_VPM_INVALID_TEMPLATE_ID_BUFFER);

    pPipeline = vp->NCP_POINTER(pipelines)[engineSeqId].NCP_POINTER(pipeline);
    if(!pPipeline->NCP_POINTER(engines))
        NCP_CALL(NCP_ST_VPM_ENGINE_SEQUENCE_NOT_CPU_TERMINATING);

    pLastEngine = pPipeline->NCP_POINTER(engines)[pPipeline->numEngines - 1].NCP_POINTER(engine);

    if(pLastEngine && pLastEngine->type == ncp_engine_cpu) {
        *templateId = pLastEngine->templateId;
    } else {
        NCP_CALL(NCP_ST_VPM_ENGINE_SEQUENCE_NOT_CPU_TERMINATING);
    }

NCP_RETURN_LABEL
    NCP_TRACEPOINT(Intel_AXXIA_ncp_vpm, ncp_vp_cpu_terminate_template_id_get_exit,  NCP_MSG_EXIT,
            "ncpStatus=%d templateId=%d\n",ncpStatus,templateId?*templateId:0);
    return ncpStatus;
}

