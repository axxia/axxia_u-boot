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

#ifndef __NCP_SYSMEM_SYNOPPHY_H__
#define __NCP_SYSMEM_SYNOPPHY_H__

/* register definitions for ACP56xx */
#include "regs/ncp_denali_5600_regs.h"
#include "regs/ncp_denali_5600_reg_defines.h"
#include "regs/ncp_phy_5600_regs.h"
#include "regs/ncp_phy_5600_reg_defines.h"

#define Max(a,b) ((a) > (b) ? (a) : (b))

/* using printf as default, can be changed to invoke some other logging if available */
#define errprintf(fmt,args...) printf(fmt,##args)
/*#define dbgprintf(fmt,args...) printf(fmt,##args)*/
#define dbgprintf(fmt,args...)

/* From Address pins per JEDEC */
#define NCP_SM_ENCODE_RTT_NOM_DDR3(val)  \
	( ( (val & 0x1) << 2 ) |  /* a2 */ \
	  ( (val & 0x2) << 5 ) |  /* a6 */ \
	  ( (val & 0x4) << 7 ) )  /* a9 */

#define NCP_SM_ENCODE_DRV_IMP_DDR3(val)  \
	( ( (val & 0x1) << 1 ) |  /* a1 */ \
	  ( (val & 0x2) << 4 ) )  /* a5 */ 

#define NCP_SM_ENCODE_RTT_NOM_DDR4(val)  \
	( ( (val & 0x1) << 8 ) |  /* a8 */ \
	  ( (val & 0x2) << 8 ) |  /* a9 */ \
	  ( (val & 0x4) << 8 ) )  /* a10 */

#define NCP_SM_ENCODE_DRV_IMP_DDR4(val)  \
	( ( (val & 0x1) << 1 ) |  /* a1 */ \
	  ( (val & 0x2) << 1 ) )  /* a2 */ 

#define NCP_SM_ENCODE_RTT_PARK_DDR4(val)  \
	( ( (val & 0x1) << 6 ) |  /* a6 */ \
	  ( (val & 0x2) << 6 ) |  /* a7 */ \
	  ( (val & 0x4) << 6 ) )  /* a8 */

/*
 * Timing Parameters
 * Common to MC, Phy
 * TBD: save to handle for cmem use as well
 */
typedef struct {
	ncp_uint16_t  	speed;
	ncp_uint8_t   	binned_CL;
	ncp_uint8_t   	CL_config;
	ncp_uint16_t   	tRCD;
	ncp_uint16_t   	tRP;
	ncp_uint16_t   	tRAS;
	ncp_uint16_t   	tRC;
	ncp_uint16_t   	tRRD;
	ncp_uint16_t   	tFAW;
	ncp_uint16_t   	tCKE;

	ncp_uint16_t	tCCD_L;
	ncp_uint16_t	tCCD_S;
	ncp_uint16_t	tRRD_S;
	ncp_uint16_t	tRRD_L;
	ncp_uint16_t	tWTR_S;
	ncp_uint16_t	tWTR_L;
	ncp_uint16_t	tRTP;
	ncp_uint16_t	tWR;
	ncp_uint16_t	tMRD;
	ncp_uint16_t	tMOD;
	ncp_uint16_t	tMPRR;
	ncp_uint16_t	tWR_MPR;
	ncp_uint16_t	tZQinit;
	ncp_uint32_t	tXPR;
	ncp_uint32_t	tXS;
	ncp_uint16_t	tCKESR;
	ncp_uint16_t	tCKSRE;
	ncp_uint16_t	tMRD_PDA;

	ncp_uint16_t	tREFI;

	ncp_uint16_t	tRFC;

	ncp_uint32_t	mr0;
	ncp_uint32_t	mr1;
	ncp_uint32_t	mr2;
	ncp_uint32_t	mr3;
	ncp_uint32_t	mr4;
	ncp_uint32_t	mr5;
	ncp_uint32_t	mr6;

} ncp_common_timing_parameters_t;

ncp_uint32_t
ncp_ps_to_clk(
		ncp_uint32_t tck_ps,
		ncp_uint32_t num_ps);

ncp_st_t
ncp_sm_ddr4_mc_reg_dump(
		ncp_dev_hdl_t   dev,
		ncp_uint32_t    smNode);

ncp_st_t
ncp_sm_ddr4_phy_reg_dump(
		ncp_dev_hdl_t   dev,
		ncp_uint32_t    smNode);

ncp_st_t
ncp_sm_ddr4_phy_training_error_check(
		ncp_dev_hdl_t   dev,
		ncp_uint32_t    smNode);

ncp_st_t
ncp_sm_ddr4_phy_training(
		ncp_dev_hdl_t   dev,
		ncp_uint32_t    smNode,
		ncp_sm_parms_t *parms);

ncp_st_t
ncp_sm_ddr4_post_phy_training_mc_setup(
		ncp_dev_hdl_t   dev,
		ncp_uint32_t    smNode,
		ncp_sm_parms_t *parms);

ncp_st_t
ncp_sm_ddr4_phy_init(
		ncp_dev_hdl_t   dev,
		ncp_uint32_t    smNode,
		ncp_sm_parms_t *parms,
		ncp_common_timing_parameters_t *ctm);

ncp_st_t
ncp_sm_common_setup_56xx(
		ncp_dev_hdl_t   dev,
		ncp_uint32_t    smNode,
		ncp_sm_parms_t *parms,
		ncp_common_timing_parameters_t *ctm);

ncp_st_t
ncp_sm_denali_2041_init_56xx(
		ncp_dev_hdl_t   dev,
		ncp_uint32_t    smNode,
		ncp_sm_parms_t *parms,
		ncp_common_timing_parameters_t *ctm);

#endif
