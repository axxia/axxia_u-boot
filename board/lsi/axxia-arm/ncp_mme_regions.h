/**************************************************************************
 **                                                                       *
 **   LSI CONFIDENTIAL                                                    *
 **                           PROPRIETARY NOTE                            *
 **                                                                       *
 **    This software contains information confidential and proprietary    *
 **    to LSI Inc.  It shall not be reproduced in whole or in             *
 **    part, or transferred to other documents, or disclosed to third     *
 **    parties, or used for any purpose other than that for which it was  *
 **    obtained, without the prior written consent of LSI Inc.            *
 **    (c) 2001-2013, LSI Inc.  All rights reserved.                      *
 **                                                                       *
 **  **********************************************************************
 **                                                                       *
 **  **********************************************************************
 **  File:       $HeadURL: $                                              *
 **  Version:    $Revision: $                                             *
 **  Date:       $Date: $                                                 *
 **  **********************************************************************/


#ifndef _NCP_MME_REGIONS_H_
#define _NCP_MME_REGIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

#if 0 /* UBOOT */
#include "ncp_sal_types.h"
#endif

#include "ncp_nodes.h"

#define    NCP_REGION_MME_MME_CORE                              NCP_REGION_ID(NCP_NODE_MME, 0x0010) /* 21.16 */
#define    NCP_REGION_MME_POKE                                  NCP_REGION_ID(0x109,0x0) /* 265.0 */
#define    NCP_REGION_MME_CFG_NODE                              NCP_REGION_ID(NCP_NODE_MME, 0x00ff) /* 21.255 */


#ifdef __cplusplus
}
#endif

#endif /* _NCP_MME_REGIONS_H_ */
