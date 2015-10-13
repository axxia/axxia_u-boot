/*
*  Copyright (C) 2014 LSI (john.jacques@lsi.com)
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
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
#endif/* UBOOT */

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

#endif/* NCP_TASK_USE_55XX_HEADERS */


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
#endif/* #if defined(NCP_KERNEL) */

#include "ncp_cow_ext.h"
#include "ncp_vpm.h"
#include "ncp_vpm_pvt.h"
#include "ncp_vpm_ext.h"
#else /* #if 0 */

/* FOR UBOOT */
#include "ncp_regions.h"

#endif/* #if 0 */

#endif/* __ncp_task_pvt_h__ */

