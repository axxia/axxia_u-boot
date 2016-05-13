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

#ifndef __NCP_L3LOCK_REGION_H__
#define __NCP_L3LOCK_REGION_H__
typedef struct {
	ncp_uint32_t	totalL3LockedSize;
	/* bit 31: valid; bits[23:0]- physical offset in MB */
	ncp_uint32_t	region[4];
} ncp_l3lock_region_info_t;

ncp_st_t
ncp_l3lock_region_init ( ncp_dev_hdl_t   dev, 
		ncp_l3lock_region_info_t *l3lock_params, ncp_bool_t isFPGA);

#endif


