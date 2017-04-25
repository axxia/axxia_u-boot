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

#include <common.h>
#include "uboot/ncp_sal_types_linux.h"
#include "uboot/ncp_task_basetypes.h"

#include "uboot/ncp.h"
#include "uboot/ncp_pvt.h"

#define NCP_RELEASE_VARIABLES

/* --- Exportable State Data --- */
ncp_hdl_t **ncp_hdls = NULL;
ncp_dev_hdl_t ncp_dev_hdls[NCP_MAX_DEVS] =
{
  (ncp_dev_hdl_t)-1
};

ncp_uint8_t ncp_dev_hdl_users[NCP_MAX_DEVS] = {0};

void *ncpHwioTraceFuncArg = NULL;
ncp_hwio_trace_func_t ncpHwioTraceFunc = NULL;

ncp_uint32_t sc_nodes[NCP_SYSCACHE_NUM_NODES] = 
                    {0x20, 0x1e, 0x21, 0x1d, 0x11, 0x12, 0x10, 0x13};
ncp_uint32_t sm_nodes[NCP_EXTMEM_NUM_NODES] = {0x22, 0x0f, 0x08, 0x09};

ncp_bool_t ncp_dev_initialized = FALSE;

/* --- Published Functions --- */

/* --- Internal Functions --- */

/*
 * temporory "not yet" functions
 *
 */
void
ncp_hw_not_yet(const char *s)
{
    printf("no hw mod for: %s\n",s);
}

void
ncp_stub_not_yet(const char *s)
{
    printf("no api or hw mod for %s\n",s);
}


/*
 * ncp_comment
 */
void
ncp_comment(
    const char *msg)
{
    /* Log HWIO tracepoint, if enabled */
#if (defined(NCP_LTTNG_USERSPACE) && !defined(NCP_KERNEL))
    if (msg != NULL) {
        tracepoint(Intel_AXXIA_ncp_custom,
                   ncp_custom_hwio_comment,
                   NCP_HWIO_COMMENT,
                   msg
                  );
    }
#endif

    if ((ncpHwioTraceFunc != NULL) && (msg != NULL)) {
        ncpHwioTraceFunc(
                ncpHwioTraceFuncArg,
                NCP_HWIO_COMMENT,
                0,
                (void *)msg);
    }
}


/*
 * ncp_usleep
 */
int
ncp_usleep(
    unsigned long usecs)
{
    /* Log HWIO tracepoint, if enabled */
#if (defined(NCP_LTTNG_USERSPACE) && !defined(NCP_KERNEL))
    tracepoint(Intel_AXXIA_ncp_custom,
               ncp_custom_hwio_generic,
               NCP_HWIO_USLEEP,
               0,
               usecs
              );
#endif

    if (ncpHwioTraceFunc != NULL) {
        ncpHwioTraceFunc(
                ncpHwioTraceFuncArg,
                NCP_HWIO_USLEEP,
                0,
                (void *)usecs);
    }

    return ncp_sys_usleep(usecs);
}


/*---------------------------------------------------------*/


/* --- Published API Functions --- */


/*
 * ncp_user_info()
 *
 *   Copy the NCP userInfo string to the user's buffer.
 */
ncp_st_t
ncp_user_info(
    ncp_hdl_t    inHdl,
    ncp_uint32_t userInfoSizeBytes,
    char       *userInfo)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_t *ncp = (ncp_t *)inHdl;

    NCP_CALL(NCP_CONFIG_VALIDATE_HANDLE(ncp));

    /*
     * Need room for the string terminator, at least.
     */
    if (userInfoSizeBytes == 0) {
        NCP_CALL(NCP_ST_INVALID_PARAMETER);
    }

    if (ncp->userInfo != NULL) {
        userInfoSizeBytes--;    /* make room for the terminator */
        if (strlen(ncp->userInfo) < userInfoSizeBytes) {
            userInfoSizeBytes = strlen(ncp->userInfo);
        }
        strncpy(userInfo, ncp->userInfo, userInfoSizeBytes);
        userInfo[userInfoSizeBytes] = 0;
    } else {
        userInfo[0] = 0;
    }

NCP_RETURN_LABEL
    return ncpStatus;
}

/*
 * ncp_trace_level_set
 *
 *   Set the trace level flags to enable or disable runtime messages.
 */
ncp_st_t
ncp_trace_level_set(
    int traceLevel)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    NCP_TRACEPOINT (Intel_AXXIA_ncp_common, ncp_trace_level_set_entry, NCP_MSG_ENTRY,
        "traceLevel=%d\n", traceLevel);

    ncp_trace_level = traceLevel;

NCP_RETURN_LABEL
    NCP_TRACEPOINT (Intel_AXXIA_ncp_common, ncp_trace_level_set_exit, NCP_MSG_EXIT,
                "ncpStatus=%d\n", ncpStatus);
    return ncpStatus;
}

#ifdef NCP_ROBUST_MUTEX_TEST
extern ncp_bool_t ncp_owner_dead;
extern ncp_mutex_t* ncp_mutex_ptr;
NCP_API ncp_st_t
ncp_owner_dead_set(
    ncp_bool_t ownerDead)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    ncp_owner_dead = ownerDead;

NCP_RETURN_LABEL
    return ncpStatus;
}
NCP_API ncp_st_t
ncp_mutex_reinit(void)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    NCP_CALL(ncp_mutex_destroy(ncp_mutex_ptr));
    NCP_CALL(ncp_mutex_init(ncp_mutex_ptr, TRUE));
NCP_RETURN_LABEL
    return ncpStatus;
}
#endif
