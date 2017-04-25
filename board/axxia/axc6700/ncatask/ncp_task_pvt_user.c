/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                        *
 **                                                                       *
 **************************************************************************/

#include <common.h>
#include "uboot/ncp_sal_types_linux.h"
#include "uboot/ncp_task_basetypes.h"

#include "uboot/ncp.h"
#include "uboot/ncp_pvt.h"

#include "uboot/ncp_cow_ext.h"
#undef  NCP_TASK_NCA_GLOBALS
#include "uboot/ncp_dev_pvt.h"
#include "uboot/ncp_task_pvt.h"
#include "uboot/ncp_ncav3_pvt.h"

#if defined(NCP_DEV_SOCKET)
#include "uboot/ncp_task_socket.h"
#else
#include "uboot/ncp_task_hw.h"
#endif

#if !defined(NCP_DEV_SOCKET) && !defined(NCP_DEV_FBRS) && !defined(NCP_DEV_FBDEV)
#include "uboot/ncp_task_inline_funcs.h"
#endif


ncp_st_t
ncp_task_os_pid_match_check(ncp_task_process_info_t *pProcess, ncp_bool_t expectedResult, ncp_st_t specificError)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_pid_t myPid = 0;

    NCP_CALL(ncp_task_getpid(&myPid));

    /* Caller specified wheth pid should match or not */
    if (expectedResult != (myPid == pProcess->osPid))
    {
        NCP_CALL(specificError);
    }

NCP_RETURN_LABEL
    return(ncpStatus);
}

ncp_st_t
ncp_task_os_pid_store(ncp_task_process_info_t *pProcess)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    NCP_CALL(ncp_task_getpid(&pProcess->osPid));

NCP_RETURN_LABEL
    return(ncpStatus);
}


