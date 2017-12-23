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


/*
 * NCP UNIX API <--> Driver System Call Interfaces
 */

#include <compiler.h>

#include <common.h>
#include "uboot/ncp_sal_types_linux.h"
#include "uboot/ncp_task_basetypes.h"

#include "uboot/ncp.h"
#include "uboot/ncp_pvt.h"
#include "uboot/ncp_dev_linux.h"
#include "uboot/ncp_dev_pvt.h"
#include "uboot/ncp_task.h"
#include "uboot/ncp_task_pvt.h"

#ifdef __linux__


/* --- Types & Definitions --- */

#define NCP_MAX_DEV_NAME_LEN    (25)


/* --- Internal Functions ---- */

/*
 * ncp_status_code
 *
 *   Translate UNIX errno into an appropriate NCP status code.
 */
#if 0
	static ncp_st_t
ncp_status_code(void)
{
/*
    switch (errno)
    {
        case EBADF:
        case ENOTTY:
            return NCP_ST_DEV_INVALID_HANDLE;

        case ENOENT:
            return NCP_ST_DEV_DEVICE_FILE_NOT_FOUND;

        case ENXIO:
        case ENODEV:
            return NCP_ST_DEV_DEVICE_NOT_FOUND;

        case EFAULT:
            return NCP_ST_DEV_INVALID_BUFFER;

        case EINVAL:
            return NCP_ST_DEV_INVALID_IOCTL_COMMAND;
    }

    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_status_code_unexpectedIoctl, NCP_MSG_ERROR,
                   "Unexpected ioctl error : %d\n", errno);
*/
    return NCP_ST_DEV_UNMAPPED_ERROR;
}
#endif

/* --- External Functions ---- */


#undef NCP_TASK_DBG_ISR_LATENCY

void *
ncp_mem_mmap(ncp_dev_hdl_t devHdl, void *startAddr, ncp_uint32_t size, 
             ncp_uint64_t physAddr)
{
    void *mmapPtr = NULL;
#if 0

    mmapPtr = mmap(startAddr, size, (PROT_READ | PROT_WRITE), MAP_SHARED,
                           (intptr_t)devHdl, (off_t) physAddr);
    
    if (((NULL != startAddr) && (startAddr != mmapPtr)) || (NULL == mmapPtr))
    {
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_mem_mmap_failed, NCP_MSG_ERROR,
                       "ncp_mem_mmap(): mmap failed startAddr=%p, retAddr=%p, physAddr=0x%s, size=0x%x, errno=0x%x\r\n",
                       startAddr, mmapPtr,
                       NCP_CONVERT_LONG_TO_HEX_STR_FORMAT("%012", physAddr),
                       size, errno);
        perror("mmap");
        if (mmapPtr)
        {
            munmap(mmapPtr, size);
        }
        mmapPtr = NULL; /* so caller see's the error */
    }
    else
    {
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_mem_mmap_success, NCP_MSG_DEBUG,
                       "ncp_mem_mmap(): mmap success:  startAddr=%p, retAddr=%p, physAddr=0x%s, size=0x%x, errno=0x%x\r\n",
                       startAddr, mmapPtr,
                       NCP_CONVERT_LONG_TO_HEX_STR_FORMAT("%012", physAddr),
                       size, errno);
    }

NCP_RETURN_LABEL
#endif
    return mmapPtr;
}


/* ------------------------------------------------------------------------- */

/*
 * Daemonize ourself.
 * Prevent ncpCfgTool from being marked defunct and hanging up tclsh exec
 * if executed programatically.
 */ 
ncp_st_t
ncp_daemonize_self(void)
{
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;
#if 0
    pid_t sid;
         
    /* Change the file mode mask */
    umask(0);
    
    /* Create a new SID for the child process */
    
    sid = setsid();
    if (sid < 0)
    {
        NCP_CALL(NCP_ST_SAL_SSID_FAILURE);
    }
    
    /* Change the current working directory.  This prevents the current
       directory from being locked; hence not being able to remove it. */
    if ((chdir("/")) < 0)
    {
        NCP_CALL(NCP_ST_SAL_CHDIR_FAILURE);
    }
    
    /* Redirect standard files to /dev/null */
    freopen( "/dev/null", "r", stdin);
    freopen( "/dev/null", "w", stdout);
    freopen( "/dev/null", "w", stderr);
        
NCP_RETURN_LABEL        
#endif
    return(ncpStatus);
}

#if (1 == USE_NCAV3)

ncp_st_t
ncp_ncav3_enable_ipcq(
    ncp_dev_hdl_t dev,
    ncp_uint8_t   ncapId,
    ncp_uint8_t   relTqsId,
    ncp_uint8_t   pgitId)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
#if 0
    ncp_ioc_ncav3_ipcq_modify_t arg;

    /*
     * This function performs a read-modify-write operation on the ITP's IPCQ
     * online and IPCQ valid registers. Since user- and kernel-space could call
     * this (or disable_ipcq) at any time, their accesses must be synchronized.
     * Hence, the operation is centralized in the kernel module.
     */

    arg.NCP_POINTER(st) = &ncpStatus;
    arg.ncapId = ncapId;
    arg.relTqsId = relTqsId;
    arg.pgitId = pgitId;

    NCP_POINTER_FIXUP(arg.NCP_POINTER_64(st));

    if (ioctl((intptr_t) dev, NCP_IOC_TASK_NCAV3_ENABLE_IPCQ, &arg) == -1)
    {
        return ncp_status_code();
    }

NCP_RETURN_LABEL
#endif
    return(ncpStatus);
}

ncp_st_t
ncp_ncav3_disable_ipcq(
    ncp_dev_hdl_t dev,
    ncp_uint8_t   ncapId,
    ncp_uint8_t   relTqsId,
    ncp_uint8_t   pgitId)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
#if 0
    ncp_ioc_ncav3_ipcq_modify_t arg;

    /*
     * This function performs a read-modify-write operation on the ITP's IPCQ
     * online and IPCQ valid registers. Since user- and kernel-space could call
     * this (or enable_ipcq) at any time, their accesses must be synchronized.
     * Hence, the operation is centralized in the kernel module.
     */

    arg.NCP_POINTER(st) = &ncpStatus;
    arg.ncapId = ncapId;
    arg.relTqsId = relTqsId;
    arg.pgitId = pgitId;

    NCP_POINTER_FIXUP(arg.NCP_POINTER_64(st));

    if (ioctl((intptr_t) dev, NCP_IOC_TASK_NCAV3_DISABLE_IPCQ, &arg) == -1)
    {
        return ncp_status_code();
    }

NCP_RETURN_LABEL
#endif
    return(ncpStatus);
}

#endif

#endif /* __linux__ */
