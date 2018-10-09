/*
 *  Copyright (C) 2016 Intel (john.jacques@intel.com)
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

#ifdef __UBOOT__
#include <common.h>
#include "ncp_sysmem_ext.h"
#include "ncp_sysmem_lsiphy.h" 
#include "ncp_l3lock_region.h" 
#else  /* __UBOOT__ */
#include <stdio.h>
#include "ncp.h"
#include "ncp_pvt.h"
#include "ncp_sysmem_ext.h"
#include "ncp_sysmem_lsiphy.h"
#include "ncp_l3lock_region.h"
#endif	/* __UBOOT__ */

ncp_st_t
ncp_l3lock_region_init (ncp_dev_hdl_t dev,
			ncp_l3lock_region_info_t *l3lock_params,
			ncp_bool_t isFPGA)
{
	ncp_st_t	ncpStatus = NCP_ST_SUCCESS;
	ncp_uint32_t	numLockedWays = 0;
	int             i;
	int		j;
#ifndef __UBOOT__
	ncp_uint32_t    tmp;
#endif	/* __UBOOT__ */

#ifndef __UBOOT__	
	NCP_ASSERT(l3lock_params != NULL, NCP_ST_INVALID_PARAMETER);
#endif	/* __UBOOT__ */

	if (l3lock_params->totalL3LockedSize == 0)
		return NCP_ST_SUCCESS;

	if (isFPGA) {
		if (l3lock_params->totalL3LockedSize == 8) {
			numLockedWays = 8;
		} else if (l3lock_params->totalL3LockedSize == 12) {
			numLockedWays = 12;
		} else {
			printf("Total Locked size supported on FPGA is either 8 or 12 MB\n");
			NCP_CALL(NCP_ST_INVALID_PARAMETER);
		}
	} else {
		if (l3lock_params->totalL3LockedSize == 4) {
			numLockedWays = 2;
		} else if (l3lock_params->totalL3LockedSize == 8) {
			numLockedWays = 4;
		} else if (l3lock_params->totalL3LockedSize == 16) {
			numLockedWays = 8;
		} else {
			printf("Total Locked size supported on ASIC is either 4/8/16 MB\n");
			NCP_CALL(NCP_ST_INVALID_PARAMETER);
		}
	}

#ifndef __UBOOT__
	/* Setup secure mode */
	ncr_read32(NCP_REGION_ID(0x170, 1), 0x42800, &tmp);
	ncr_write32(NCP_REGION_ID(0x170, 1), 0x42800, 2);
#endif	/* __UBOOT__ */

	/* setup regions */
	for (j= 0; j < 4; j++) {
		ncp_uint64_t base;
		ncp_uint32_t u;
		ncp_uint32_t l;

		/* Convert the parameter region to a base value. */
		base = ((ncp_uint64_t)(l3lock_params->region[j] &
				       0x80000000) << 32);
		base |= ((ncp_uint64_t)(l3lock_params->region[j] & 0x00ffffff) << 20);

		u = ((base >> 32) & 0xffffffff);
		l = (base & 0xffffffff);

		for (i = 0x20; i <= 0x27; i++) {
#ifdef __UBOOT__
			writel(l, (DICKENS + (i * 0x10000) + 0x48 + (j * 8)));
			writel(u, (DICKENS + (i * 0x10000) + 0x4c + (j * 8)));
#else  /* __UBOOT__ */
			ncr_write32(NCP_REGION_ID(0x1e0, i), 0x48 + (j * 8),
				    (ncp_uint32_t)(base & 0xFFFFFFFF));
			ncr_write32(NCP_REGION_ID(0x1e0, i), 0x4c + (j * 8),
				    (ncp_uint32_t)((base >> 32) &
						   0xFFFFFFFF));
#endif
		}
	}

	/* setup number of locked ways */
	for (i = 0x20; i <= 0x27; i++) {
#ifdef __UBOOT__
		writel(numLockedWays, (DICKENS + (i * 0x10000) + 0x40));
#else  /* __UBOOT__ */
		ncr_write32( NCP_REGION_ID(0x1e0, i), 0x40, numLockedWays);
#endif	/* __UBOOT__ */
	}

#ifndef __UBOOT__
	/* Set it back to non-secure mode or the mode we started with. */
	ncr_write32(NCP_REGION_ID(0x170, 1), 0x42800, tmp);
#endif	/* __UBOOT__ */

	NCP_RETURN_LABEL
		return ncpStatus;
}
