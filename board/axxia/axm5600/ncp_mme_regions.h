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

#endif/* _NCP_MME_REGIONS_H_ */
