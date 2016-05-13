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

#ifndef __NCP_TREEMEM_SYNOPPHY_H__
#define __NCP_TREEMEM_SYNOPPHY_H__

/* Following includes apply to new controller for X9, XLF */
#include "regs/cmem_56xx/ncp_memory_controller_regs.h"
#include "regs/cmem_56xx/ncp_memory_controller_reg_defines.h"
#include "regs/cmem_56xx/ncp_cmem_cfg_regs.h"
#include "regs/cmem_56xx/ncp_cmem_cfg_reg_defines.h"
#include "regs/cmem_56xx/ncp_phy_regs.h"
#include "regs/cmem_56xx/ncp_phy_reg_defines.h"

ncp_st_t
ncp_cm_ddr4_phy_reg_dump(
		ncp_dev_hdl_t   dev,
		ncp_uint32_t    cmNode);

ncp_st_t
ncp_cm_ddr4_phy_training_error_check(
		ncp_dev_hdl_t   dev,
		ncp_uint32_t    cmNode);

ncp_st_t
ncp_cm_ddr4_phy_training(
		ncp_dev_hdl_t   dev,
		ncp_uint32_t    cmNode,
		ncp_sm_parms_t *parms);

ncp_st_t
ncp_cm_ddr4_post_phy_training_mc_setup(
		ncp_dev_hdl_t   dev,
		ncp_uint32_t    cmNode,
		ncp_sm_parms_t *parms);

ncp_st_t
ncp_cm_ddr4_phy_init(
		ncp_dev_hdl_t   dev,
		ncp_uint32_t    cmNode,
		ncp_sm_parms_t *parms,
		ncp_common_timing_parameters_t *ctm);

NCP_API ncp_st_t
ncp_cm_denali_init_56xx(
		ncp_dev_hdl_t   dev,
		ncp_uint32_t    cmNode,
		ncp_sm_parms_t *parms,
		ncp_common_timing_parameters_t *ctm);

#endif
