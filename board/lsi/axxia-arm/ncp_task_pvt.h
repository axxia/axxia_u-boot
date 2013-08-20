/**************************************************************************
**                                                                        *
**   LSI Corporation, Inc. CONFIDENTIAL                                   *
**                                                                        *
**                       PROPRIETARY NOTE                                 *
**                                                                        *
**    This software contains information confidential and proprietary     *
**    to LSI Corporation Inc.  It shall not be reproduced in whole or in  *
**    part, or transferred to other documents, or disclosed to third      *
**    parties, or used for any purpose other than that for which it was   *
**    obtained, without the prior written consent of LSI Corporation Inc. *
**    (c) 2008-2013, LSI Corporation Inc.  All rights reserved.           *
**                                                                        *
**  ***********************************************************************
**
**  ***********************************************************************
**   File:       $HeadURL: $
**   Version:    $Revision: $
**   Date:       $Date: $
**
*************************************************************************
*/

#ifndef __ncp_task_pvt_h__
#define __ncp_task_pvt_h__

/* ===============================
 * Required include files
 * ===============================
 */
 
#include "ncp_status.h"
#include "ncp_task_basetypes.h"
#include "ncp_nodes.h" 
/* #include "ncp_regions.h" */
#include "ncp_task.h"
#include "ncp_task_pvt_common.h"



/* ===============================
 * Platform specific include files
 * ===============================
 */
 
#ifndef NCP_TASK_USE_55XX_HEADERS
/* ================== BEGIN 3400 ============================= */
/*
 * Pull in overrides
 */
#if defined(NCP_DEV_SOCKET)
#include "ncp_task_pvt_socket.h"
#elif defined(NCP_DEV_FBRS) || defined(NCP_DEV_FBDEV) 
#include "ncp_task_pvt_fbxx.h"
#endif 

/* NCA V1 registers */
#include "ncp_nca_regs.h"
#include "ncp_nca_reg_defines.h"

#if 0 /* UBOOT */
#include "ncp_task_pvt_acp34xx.h"
#include "ncp_task_pvt_funcs_acp34xx.h"


#if defined(NCP_DEV_SOCKET)
#include "ncp_task_pvt_funcs_socket_acp34xx.h"
#elif defined(NCP_DEV_FBRS) || defined(NCP_DEV_FBDEV) 
#include "ncp_task_pvt_funcs_fbxx.h"
#else
#include "ncp_task_pvt_funcs_hw_acp34xx.h"
#endif
#endif /* UBOOT */

/* ================== END 3400 ============================= */


#else /* NCP_TASK_USE_55XX_HEADERS */

/* ================== BEGIN 5500 ============================= */

/*
 * Pull in overrides
 */
#if defined(NCP_DEV_SOCKET)
#include "ncp_task_pvt_socket.h"
#elif defined(NCP_DEV_FBRS) || defined(NCP_DEV_FBDEV) 
#include "ncp_task_pvt_fbxx.h"
#endif 

/* NCA V1 registers */
#if 0 /* Use merged headers */
#include "regs/ncp_nca_5500_regs.h"
#include "regs/ncp_nca_5500_reg_defines.h"
#else
#if 0 /* UBOOT */
#include "regs/ncp_nca_regs.h"
#include "regs/ncp_nca_reg_defines.h"
#else
#include "ncp_nca_regs.h"
#include "ncp_nca_reg_defines.h"
#endif
#endif

#include "ncp_task_pvt_axm55xx.h"
#include "ncp_task_pvt_funcs_axm55xx.h"

#if defined(NCP_DEV_SOCKET)
#include "ncp_task_pvt_funcs_socket_axm55xx.h"
#elif defined(NCP_DEV_FBRS) || defined(NCP_DEV_FBDEV) 
#include "ncp_task_pvt_funcs_fbxx.h"
#else
#include "ncp_task_pvt_funcs_hw_axm55xx.h"
#endif

/* ================== END 5500 ============================= */

#endif /* NCP_TASK_USE_55XX_HEADERS */


/* ===============================
 * Typical include files
 * ===============================
 */
 
#if 0 /* UBOOT */    
#ifndef NCP_KERNEL
#include "ncp.h"
#include "ncp_pvt.h"
#include "ncp_llist.h"
#include "ncp_sorted_set.h"
#include "ncp_map.h"
#endif
#include "ncp_regions.h" 
 
 
#include "ncp_profiler.h"

#if defined(NCP_KERNEL)
#ifdef NCP_LINUX
#include <linux/skbuff.h>
#endif
#endif /* #if defined(NCP_KERNEL) */

#include "ncp_cow_ext.h"
#include "ncp_vpm.h"
#include "ncp_vpm_pvt.h"
#include "ncp_vpm_ext.h"
#else /* #if 0 */

/* FOR UBOOT */
#include "ncp_regions.h" 

#endif /* #if 0 */

#endif /* __ncp_task_pvt_h__ */

