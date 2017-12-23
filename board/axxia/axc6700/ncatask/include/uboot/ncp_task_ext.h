/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                        *
 **                                                                       *
 **************************************************************************/

#ifndef __NCP_TASK_EXT_H__
#define __NCP_TASK_EXT_H__

/* Inter-module functions */

NCP_API ncp_st_t
ncp_task_disable_umode_tqsets(ncp_hdl_t ncpHdl);

NCP_API ncp_st_t
ncp_task_shutdown(
    ncp_uint32_t devNum);

NCP_API ncp_st_t
ncp_task_shutdown_wait(
    ncp_hdl_t ncpHdl);

NCP_API ncp_st_t
ncp_task_attach(
    ncp_t *ncp);

NCP_API ncp_st_t
nca_task_v3_CpuPool_available_blocks_get(ncp_hdl_t ncpHdl,
                                         ncp_uint32_t poolId,
                                         ncp_uint32_t blockSize,
                                         ncp_uint32_t *numBlocks);
#endif /* __NCP_TASK_EXT_H__ */
