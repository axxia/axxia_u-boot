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
#include "ncp_sysmem_lsiphy.h" /* for macros and stuff mainly */
#include "ncp_sysmem_synopphy.h"
#else
#include "ncp.h"
#include "ncp_pvt.h"
#include "ncp_sysmem_ext.h"
#include "ncp_sysmem_lsiphy.h" /* for macros and stuff mainly */
#include "ncp_sysmem_synopphy.h"
#endif

extern ncp_sm_poll_controller_fn_t  pollControllerFn;

ncp_uint32_t
ncp_ps_to_clk(
		ncp_uint32_t tck_ps,
		ncp_uint32_t num_ps);
/*
 * DDR3 timing parameters 
 */
typedef struct {
	ncp_uint16_t  	speed; 		/* comes from part as ddrClockSpeed in sm_parms */
	ncp_uint8_t   	binned_CL[4]; 	/* comes from part CL-nRCD-nRP as user input in sm_parms */
	ncp_uint8_t   	CL_config[9]; 	/* comes from sm_parms as CAS_latency */
	ncp_uint16_t   	tRCD[4];	/* JEDEC unit of ns converted to ps so don't have to deal with floats */
	ncp_uint16_t   	tRP[4];		/* JEDEC unit of ns converted to ps */
	ncp_uint16_t   	tRAS[4];	/* JEDEC unit of ns converted to ps */
	ncp_uint16_t   	tRC[4];		/* JEDEC unit of ns converted to ps */
	ncp_uint16_t   	tRRD[2];	/* JEDEC unit of ns converted to ps 1KB, 2KB page sizes respectively */
	ncp_uint16_t   	tFAW[2];	/* JEDEC unit of ns converted to ps 1KB, 2KB page sizes respectively */
	ncp_uint16_t   	tCKE;		/* JEDEC unit of ns converted to ps */
} ncp_ddr3_speedbin_vals_t;

/*
 * DDR4 timing parameters 
 */
typedef struct {
	/* from JEDEC section 9 79-4 */
	ncp_uint16_t  	speed; 		/* comes from part as ddrClockSpeed in sm_parms */
	ncp_uint8_t   	binned_CL[4]; 	/* comes from part CL-nRCD-nRP as user input in sm_parms */
	ncp_uint8_t   	CL_config[10]; 	/* comes from sm_parms as CAS_latency */
	ncp_uint16_t   	tRCD[4];	/* JEDEC unit of ns converted to ps so don't have to deal with floats */
	ncp_uint16_t   	tRP[4];		/* JEDEC unit of ns converted to ps */
	ncp_uint16_t   	tRAS[4];	/* JEDEC unit of ns converted to ps */
	ncp_uint16_t   	tRC[4];		/* JEDEC unit of ns converted to ps */

	/* from JEDEC section 12.3 79-4 */
	ncp_uint16_t	tCCD_L;		/* nCK */
	ncp_uint16_t	tCCD_S;		/* nCK */
	ncp_uint16_t	tRRD_S[3];	/* 0.5KB, 1KB, 2KB page sizes array indices; Programmed value is Max(4nCK, <value>ps) */
	ncp_uint16_t	tRRD_L[3];	/* 0.5KB, 1KB, 2KB page sizes array indices; Programmed value is Max(4nCK, <value>ps)*/
	ncp_uint16_t	tFAW[3];	/* 0.5KB, 1KB, 2KB page sizes array indices; Programmed value is Max(4nCK, <value>ps)*/
	ncp_uint16_t	tWTR_S;		/* Programmed value is Max(2nCK, <value> ps) */
	ncp_uint16_t	tWTR_L;		/* Programmed value is Max(4nCK, <value> ps) */
	ncp_uint16_t	tRTP;		/* Programmed value is Max(4nCK, <value> ps) */
	ncp_uint16_t	tWR;
	ncp_uint16_t	tMRD;		/* nCK */
	ncp_uint16_t	tMOD;		/* Programmed value is Max(24nCK, <value> ps) */
	ncp_uint16_t	tMPRR;		/* nCK */
	ncp_uint16_t	tWR_MPR;	/* Programmed value is Max(24nCK, <value> ps) */
	ncp_uint16_t	tZQinit;	/* nCK */
	ncp_uint32_t	tRFC;		/* nCK */
	ncp_uint32_t	tXPR;		/* Programmed value is Max(5nCK, <value> (tRFC_min) + 10000ps) */
	ncp_uint32_t	tXS;		/* Programmed value is <value>(tRFC_min) + 10000ps */
	ncp_uint16_t	tCKESR;		/* Programmed value is Max(3nCK, <value>ps) + 1nCK */
	ncp_uint16_t	tCKSRE;		/* Programmed value is Max(5nCK, <value>ps) */
	ncp_uint16_t	tCKE;		/* Programmed value is Max(3nCK, <value>ps) */
	ncp_uint16_t	tMRD_PDA;	/* Programmed value is Max(16nCK, <value>ps) */

} ncp_ddr4_speedbin_vals_t;


/* NOTES: Below are fixed parameters
 * tRTP = 7.5ns uniformly
 * tWTR = 7.5ns uniformly
 * tWR = 15ns uniformly
 * tMRD = 4nCK uniformly
 * tMOD = 15ns uniformly
 * tCCD = 4nCK uniformly
 * tMPRR = 1nCK uniformly
 * tXPR = tRFC + 10ns
 * tREFI 7.8us for low temp, 3.9us for high temp- for all device densities
 */

/* Used for JEDEC Speed Bin Table Validation
 * and Timing parameter Lookup
 * A zero or 0xff means invalid */
ncp_ddr3_speedbin_vals_t speedbin_ddr3_vals[6] =  {

	{/*DDR3-800 Table*/	400, {5,6,0xff,0xff}, {5,6,0xff,0xff,0xff,0xff,0xff,0xff,0xff}, {12500,15000,0xffff,0xffff}, {12500,15000,0xffff,0xffff}, 
		{37500,37500,0xffff,0xffff}, {50000,52500,0xffff,0xffff}, {10000,10000}, {40000,50000}, 7500},

	{/*DDR3-1066 Table*/533, {6,7,8,0xff}, {5,6,7,8,0xff,0xff,0xff,0xff,0xff}, {11250,13125,15000,0xffff}, {11250,13125,15000,0xffff}, 
		{37500,37500,37500,0xffff}, {48750,50625,52500,0xffff}, {7500,10000}, {37500,50000}, 5625},

	{/*DDR3-1333 Table*/667, {7,8,9,10}, {5,6,7,8,9,10,0xff,0xff,0xff}, {10500,12000,13500,15000}, {10500,12000,13500,15000}, 
		{36000,36000,36000,36000}, {46500,48000,49500,51000}, {6000,7500}, {30000,45000}, 5625},

	{/*DDR3-1600 Table*/800, {8,9,10,11}, {5,6,7,8,9,10,11,0xff,0xff}, {10000,11250,12500,13750}, {10000,11250,12500,13750}, 
		{35000,35000,35000,35000}, {45000,46250,47500,48750}, {6000,7500}, {30000,40000}, 5000},

	{/*DDR3-1866 Table*/933, {10,11,12,13}, {5,6,7,8,9,10,11,12,13}, {10700,11770,12840,13910}, {10700,11770,12840,13910}, 
		{34000,34000,34000,34000}, {44700,45770,46840,47910}, {5000,6000}, {27000,35000}, 5000},

	{/*DDR3-2133 Table*/1066, {11,12,13,14}, {5,6,7,8,9,10,11,12,13}, {10285,11220,12155,13090}, {10285,11220,12155,13090}, 
		{33000,33000,33000,33000}, {43285,44220,45155,46090}, {5000,6000}, {25000,35000}, 5000}

};

ncp_ddr4_speedbin_vals_t speedbin_ddr4_vals[4] =  {

	{/*DDR3-1600 Table*/800, {10,11,12,0xff}, {9,10,11,12,0xff,0xff,0xff,0xff,0xff,0xff}, {12500,13750,15000,0xff}, {12500,13750,15000,0xff}, {35000,35000,35000,0xff}, 
		{47500,48750,50000,0xff}, 5, 4, {5000, 5000, 6000}, {6000, 6000, 7500}, {20000, 25000, 35000}, 2500, 7500, 7500, 15000, 8, 15000, 
		1, 15000, 1024, 160000, 160000, 5000, 10000, 5000, 10000},

	{/*DDR3-1866 Table*/933, {12,13,14,0xff}, {9,10,11,12,13,14,0xff,0xff,0xff,0xff}, {12850,13920,15000,0xff}, {12850,13920,15000,0xff}, {34000,34000,34000,0xff}, 
		{46850,47920,49000,0xff}, 5, 4, {4200, 4200, 5300}, {5300, 5300, 6400}, {17000, 23000, 30000}, 2500, 7500, 7500, 15000, 8, 15000, 
		1, 15000, 1024, 160000, 160000, 5000, 10000, 5000, 10000},

	{/*DDR3-2133 Table*/1066, {14,15,16,0xff}, {9,10,11,12,13,14,15,16,0xff,0xff}, {13130,14060,15000,0xff}, {13130,14060,15000,0xff}, {33000,33000,33000,0xff}, 
		{46130,47060,48000,0xff}, 6, 4, {3700, 3700, 5300}, {5300, 5300, 6400}, {15000, 21000, 30000}, 2500, 7500, 7500, 15000, 8, 15000, 
		1, 15000, 1024, 160000, 160000, 5000, 10000, 5000, 10000},

	{/*DDR3-2400 Table*/1200, {15,16,17,18}, {9,10,11,12,13,14,15,16,17,18}, {12500,13320,14160,15000}, {12500,13320,14160,15000}, {32000,32000,32000,32000}, 
		{44500,45320,46160,47000}, 6, 4, {3300, 3300, 5300}, {4900, 4900, 6400}, {13000, 21000, 30000}, 2500, 7500, 7500, 15000, 8, 15000, 
		1, 15000, 1024, 160000, 160000, 5000, 10000, 5000, 10000}

};

/* DDR3 tRFC lookup table
 * this is based on sdram_device_density as:
 *   0=256M, 1=512Mb, 2=1Gb, 3=2Gb, 4=4Gb, 5=8Gb, and 6=16Gb [Array indices]
 * in ns
 */
ncp_uint16_t ddr3refresh_parms_by_density[7] = { 0, 90, 110, 160, 300, 350, 0/*chk */ };

/* DDR4 tRFC lookup table
 * this is based on sdram_device_density as:
 *   0=256M, 1=512Mb, 2=1Gb, 3=2Gb, 4=4Gb, 5=8Gb, and 6=16Gb [Array indices]
 * in ps
 */
ncp_uint32_t ddr4refresh_parms_by_density_1x[7] = { 0xffff, 0xffff, 0xffff, 160000, 260000, 350000, 0xffff/*chk */ };
ncp_uint32_t ddr4refresh_parms_by_density_2x[7] = { 0xffff, 0xffff, 0xffff, 110000, 160000, 260000, 0xffff/*chk */ };
ncp_uint32_t ddr4refresh_parms_by_density_4x[7] = { 0xffff, 0xffff, 0xffff, 90000, 110000, 160000, 0xffff/*chk */ };

ncp_st_t
ncp_sm_common_setup_56xx(
		ncp_dev_hdl_t dev,
		ncp_uint32_t  smNode,
		ncp_sm_parms_t *parms,
		ncp_common_timing_parameters_t *ctm)
{
	ncp_st_t ncpStatus = NCP_ST_SUCCESS;

	ncp_uint16_t clkSpeedIndex=0;
	ncp_uint16_t binnedCLIndex=0;
	ncp_uint16_t tmpVal=0;

	if ((parms == NULL) || (ctm == NULL))
	{
		errprintf("NULL parms\n");
		NCP_CALL(NCP_ST_ERROR);
	}

	if ((parms->dram_class != NCP_SM_DDR3_MODE) && (parms->dram_class != NCP_SM_DDR4_MODE))
	{
		errprintf("Error specifying dram_class %d\n",parms->dram_class);
		NCP_CALL(NCP_ST_ERROR);
	}

	if ((parms->dram_class == NCP_SM_DDR3_MODE) && 
			(parms->ddrClockSpeedMHz != 400) &&
			(parms->ddrClockSpeedMHz != 533) &&
			(parms->ddrClockSpeedMHz != 667) &&
			(parms->ddrClockSpeedMHz != 800) &&
			(parms->ddrClockSpeedMHz != 933) &&
			(parms->ddrClockSpeedMHz != 1066))
	{
		errprintf("ddr3 clock speed must be 400/533/667/800/933/1066 MHz\n");
		NCP_CALL(NCP_ST_ERROR);
	}

	if ((parms->dram_class == NCP_SM_DDR4_MODE) && 
			(parms->ddrClockSpeedMHz != 800) &&
			(parms->ddrClockSpeedMHz != 933) &&
			(parms->ddrClockSpeedMHz != 1066) &&
			(parms->ddrClockSpeedMHz != 1200))
	{
		errprintf("ddr4 clock speed must be 800/933/1066/1200 MHz\n");
		NCP_CALL(NCP_ST_ERROR);
	}

	if ((parms->dram_class == NCP_SM_DDR3_MODE) && 
			(parms->sdram_device_width != 1) &&
			(parms->sdram_device_width != 2))
	{
		errprintf("ddr3 device_width must be x8/x16 \n");
		NCP_CALL(NCP_ST_ERROR);
	}

	if ((parms->dram_class == NCP_SM_DDR4_MODE) && 
			(parms->sdram_device_width != 1) &&
			(parms->sdram_device_width != 2))
	{
		errprintf("ddr4 device_width must be x8/x16 \n");
		NCP_CALL(NCP_ST_ERROR);
	}

	if ((parms->dram_class == NCP_SM_DDR4_MODE) && 
			(parms->bstlen != 3))
	{
		/* 1 for BL2, 2 for BL4, 3 for BL8 */
		errprintf("ddr4 bstlen must be 3 \n");
		NCP_CALL(NCP_ST_ERROR);
	}

	/* tCK checks are non-trivial looking up various possibilities from JEDEC, hence doing a boundary check here so we stay on track */
	if ((parms->dram_class == NCP_SM_DDR3_MODE) && 
			(((parms->ddrClockSpeedMHz == 400) && ((parms->tck_ps < 2500) || (parms->tck_ps > 3300))) ||
			 ((parms->ddrClockSpeedMHz == 533) && ((parms->tck_ps < 1875) || (parms->tck_ps > 3300))) ||
			 ((parms->ddrClockSpeedMHz == 667) && ((parms->tck_ps < 1500) || (parms->tck_ps > 3300))) ||
			 ((parms->ddrClockSpeedMHz == 800) && ((parms->tck_ps < 1250) || (parms->tck_ps > 3300))) ||
			 ((parms->ddrClockSpeedMHz == 933) && ((parms->tck_ps < 1070) || (parms->tck_ps > 3300))) ||
			 ((parms->ddrClockSpeedMHz == 1066) && ((parms->tck_ps < 938) || (parms->tck_ps > 3300)))))
	{
		errprintf("ddr3 invalid tck_ps clock-period in pico-sec \n");
		NCP_CALL(NCP_ST_ERROR);
	}

	if ((parms->dram_class == NCP_SM_DDR4_MODE) && 
			(((parms->ddrClockSpeedMHz == 800) && ((parms->tck_ps < 1250) || (parms->tck_ps > 1600))) ||
			 ((parms->ddrClockSpeedMHz == 933) && ((parms->tck_ps < 1071) || (parms->tck_ps > 1600))) ||
			 ((parms->ddrClockSpeedMHz == 1066) && ((parms->tck_ps < 938) || (parms->tck_ps > 1600))) ||
			 ((parms->ddrClockSpeedMHz == 1200) && ((parms->tck_ps < 833) || (parms->tck_ps > 1600)))))
	{
		errprintf("ddr4 invalid tck_ps clock-period in pico-sec \n");
		NCP_CALL(NCP_ST_ERROR);
	}

	if ((parms->topology != NCP_SM_TOPO_ONE_SINGLE_RANK) &&
			(parms->topology != NCP_SM_TOPO_ONE_DUAL_RANK) &&
			(parms->topology != NCP_SM_TOPO_TWO_DUAL_RANK))
	{
		errprintf("invalid chip-select_map i.e. topology selected \n");
		NCP_CALL(NCP_ST_ERROR);
	}

	if (parms->dram_class == NCP_SM_DDR3_MODE)
	{
		/* derive clkSpeedIndex for later use */
		while (parms->ddrClockSpeedMHz != speedbin_ddr3_vals[clkSpeedIndex].speed) clkSpeedIndex++;

		/* validate binned_CL and derive binnedCLIndex for later use */
		while ((parms->binned_CAS_latency != speedbin_ddr3_vals[clkSpeedIndex].binned_CL[binnedCLIndex]) &&
				(speedbin_ddr3_vals[clkSpeedIndex].binned_CL[binnedCLIndex] != 0xff)) binnedCLIndex++;
		if (speedbin_ddr3_vals[clkSpeedIndex].binned_CL[binnedCLIndex] == 0xff)
		{
			errprintf("invalid binned_CAS_latency\n");
			NCP_CALL(NCP_ST_ERROR);
		}

		/* validate CAS_latency */
		tmpVal = 0;
		while ((parms->CAS_latency != speedbin_ddr3_vals[clkSpeedIndex].CL_config[tmpVal]) &&
				(speedbin_ddr3_vals[clkSpeedIndex].CL_config[tmpVal] != 0xff)) tmpVal++;
		if (speedbin_ddr3_vals[clkSpeedIndex].CL_config[tmpVal] == 0xff)
		{
			errprintf("invalid CAS_latency\n");
			NCP_CALL(NCP_ST_ERROR);
		}
	}
	else
	{
		/* derive clkSpeedIndex for later use */
		while (parms->ddrClockSpeedMHz != speedbin_ddr4_vals[clkSpeedIndex].speed) clkSpeedIndex++;

		/* validate binned_CL and derive binnedCLIndex for later use */
		while ((parms->binned_CAS_latency != speedbin_ddr4_vals[clkSpeedIndex].binned_CL[binnedCLIndex]) &&
				(speedbin_ddr4_vals[clkSpeedIndex].binned_CL[binnedCLIndex] != 0xff)) binnedCLIndex++;
		if (speedbin_ddr4_vals[clkSpeedIndex].binned_CL[binnedCLIndex] == 0xff)
		{
			errprintf("invalid binned_CAS_latency\n");
			NCP_CALL(NCP_ST_ERROR);
		}

		/* validate CAS_latency */
		tmpVal = 0;
		while ((parms->CAS_latency != speedbin_ddr4_vals[clkSpeedIndex].CL_config[tmpVal]) &&
				(speedbin_ddr4_vals[clkSpeedIndex].CL_config[tmpVal] != 0xff)) tmpVal++;
		if (speedbin_ddr4_vals[clkSpeedIndex].CL_config[tmpVal] == 0xff)
		{
			errprintf("invalid CAS_latency\n");
			NCP_CALL(NCP_ST_ERROR);
		}
	}

	/* validate tCK: this is non-trivial because of ranges used in JEDEC. TBD */

	/* validate CWL: this is non-trivial because of many values depending on rates are Reserved per JEDEC. TBD */

	/* Extract timing parameters for example:
	 * ncp_ps_to_clk(parms->tck_ps, (speedbin_ddr3_vals[clkSpeedIndex].tRCD[binnedCLIndex]))
	 * ncp_ps_to_clk(parms->tck_ps, (speedbin_ddr4_vals[clkSpeedIndex].tRCD[binnedCLIndex]))
	 * over tCK period for calculation
	 * Note that this is same as using ncp_ps_to_clk if running at prescribed rate.
	 * However, for example a 933 part can be run at lower rates like 800 MHz, thus having a different tCK
	 * and if using above method would cover <any> JEDEC tCK cases as well */

	/*dbgprintf("X9/XLF MC node %d Common Timing Parameters Init....\n",smNode);*/

	/* First Populate Commonly used Timing Parameters based on a) sm_parms info b) JEDEC */
	if (parms->dram_class == NCP_SM_DDR3_MODE)
	{
		ctm->speed = speedbin_ddr3_vals[clkSpeedIndex].speed;  /* Mhz */
		ctm->binned_CL = speedbin_ddr3_vals[clkSpeedIndex].binned_CL[binnedCLIndex];
		ctm->CL_config = speedbin_ddr3_vals[clkSpeedIndex].CL_config[tmpVal];
		ctm->tRCD = ncp_ps_to_clk(parms->tck_ps, (speedbin_ddr3_vals[clkSpeedIndex].tRCD[binnedCLIndex]));
		ctm->tRP = ncp_ps_to_clk(parms->tck_ps, (speedbin_ddr3_vals[clkSpeedIndex].tRP[binnedCLIndex]));
		ctm->tRAS = ncp_ps_to_clk(parms->tck_ps, (speedbin_ddr3_vals[clkSpeedIndex].tRAS[binnedCLIndex]));
		ctm->tRC = ncp_ps_to_clk(parms->tck_ps, (speedbin_ddr3_vals[clkSpeedIndex].tRC[binnedCLIndex]));

		/* sdram_device_width is defined as 0=x4(no support), 1=x8, 2=x16, 3=x32(no support)
		 * 1KB page size for x8, 2KB page size for x16 */
		ctm->tRRD = ncp_ps_to_clk(parms->tck_ps, (speedbin_ddr3_vals[clkSpeedIndex].tRRD[parms->sdram_device_width - 1]));
		ctm->tFAW = ncp_ps_to_clk(parms->tck_ps, (speedbin_ddr3_vals[clkSpeedIndex].tFAW[parms->sdram_device_width - 1]));

		ctm->tCKE = ncp_ps_to_clk(parms->tck_ps, (speedbin_ddr3_vals[clkSpeedIndex].tCKE));
	}
	else
	{
		ctm->speed = speedbin_ddr4_vals[clkSpeedIndex].speed;  /* Mhz */
		ctm->binned_CL = speedbin_ddr4_vals[clkSpeedIndex].binned_CL[binnedCLIndex];
		ctm->CL_config = speedbin_ddr4_vals[clkSpeedIndex].CL_config[tmpVal];
		ctm->tRCD = ncp_ps_to_clk(parms->tck_ps, (speedbin_ddr4_vals[clkSpeedIndex].tRCD[binnedCLIndex])); 
		ctm->tRP = ncp_ps_to_clk(parms->tck_ps, (speedbin_ddr4_vals[clkSpeedIndex].tRP[binnedCLIndex])); 
		ctm->tRAS = ncp_ps_to_clk(parms->tck_ps, (speedbin_ddr4_vals[clkSpeedIndex].tRAS[binnedCLIndex])); 
		ctm->tRC = ncp_ps_to_clk(parms->tck_ps, (speedbin_ddr4_vals[clkSpeedIndex].tRC[binnedCLIndex])); 

		ctm->tCCD_L = (speedbin_ddr4_vals[clkSpeedIndex].tCCD_L); 
		ctm->tCCD_S = (speedbin_ddr4_vals[clkSpeedIndex].tCCD_S); 

		/* sdram_device_width is defined as 0=x4, 1=x8, 2=x16, 3=x32(no support)
		 * 512B page size for x4, 1KB page size for x8, 2KB page size for x16 */
		ctm->tRRD_S = Max(4, ncp_ps_to_clk(parms->tck_ps, (speedbin_ddr4_vals[clkSpeedIndex].tRRD_S[parms->sdram_device_width])));
		ctm->tRRD_L = Max(4, ncp_ps_to_clk(parms->tck_ps, (speedbin_ddr4_vals[clkSpeedIndex].tRRD_L[parms->sdram_device_width])));
		ctm->tFAW = Max(4, ncp_ps_to_clk(parms->tck_ps, (speedbin_ddr4_vals[clkSpeedIndex].tFAW[parms->sdram_device_width])));
		ctm->tWTR_S = Max(2, ncp_ps_to_clk(parms->tck_ps, (speedbin_ddr4_vals[clkSpeedIndex].tWTR_S)));
		ctm->tWTR_L = Max(4, ncp_ps_to_clk(parms->tck_ps, (speedbin_ddr4_vals[clkSpeedIndex].tWTR_L)));
		ctm->tRTP = Max(4, ncp_ps_to_clk(parms->tck_ps, (speedbin_ddr4_vals[clkSpeedIndex].tRTP)));
		ctm->tWR = ncp_ps_to_clk(parms->tck_ps, (speedbin_ddr4_vals[clkSpeedIndex].tWR));
		ctm->tMRD = speedbin_ddr4_vals[clkSpeedIndex].tMRD;
		ctm->tMOD = Max(24, ncp_ps_to_clk(parms->tck_ps, (speedbin_ddr4_vals[clkSpeedIndex].tMOD)));
		ctm->tMPRR = speedbin_ddr4_vals[clkSpeedIndex].tMPRR;
		ctm->tWR_MPR = Max(24, ncp_ps_to_clk(parms->tck_ps, (speedbin_ddr4_vals[clkSpeedIndex].tWR_MPR)));
		ctm->tZQinit = speedbin_ddr4_vals[clkSpeedIndex].tZQinit;
		switch(parms->refresh_mode)
		{
			case NCP_SM_REFRESH_MODE_1X:
				ctm->tRFC = ncp_ps_to_clk(parms->tck_ps,(ddr4refresh_parms_by_density_1x[parms->sdram_device_density]));
				ctm->tXPR = Max(5, ncp_ps_to_clk(parms->tck_ps,((ddr4refresh_parms_by_density_1x[parms->sdram_device_density]) + 10000)));
				ctm->tXS = ncp_ps_to_clk(parms->tck_ps,(ddr4refresh_parms_by_density_1x[parms->sdram_device_density] + 10000));
				break;
			case NCP_SM_REFRESH_MODE_2X:
				ctm->tRFC = ncp_ps_to_clk(parms->tck_ps,(ddr4refresh_parms_by_density_2x[parms->sdram_device_density]));
				ctm->tXPR = Max(5, ncp_ps_to_clk(parms->tck_ps,((ddr4refresh_parms_by_density_2x[parms->sdram_device_density]) + 10000)));
				ctm->tXS = ncp_ps_to_clk(parms->tck_ps,(ddr4refresh_parms_by_density_2x[parms->sdram_device_density] + 10000));
			case NCP_SM_REFRESH_MODE_4X:
				ctm->tRFC = ncp_ps_to_clk(parms->tck_ps,(ddr4refresh_parms_by_density_4x[parms->sdram_device_density]));
				ctm->tXPR = Max(5, ncp_ps_to_clk(parms->tck_ps,((ddr4refresh_parms_by_density_4x[parms->sdram_device_density]) + 10000)));
				ctm->tXS = ncp_ps_to_clk(parms->tck_ps,(ddr4refresh_parms_by_density_4x[parms->sdram_device_density] + 10000));
			default:
				;
		}
		ctm->tCKESR = Max(3, ncp_ps_to_clk(parms->tck_ps, (speedbin_ddr4_vals[clkSpeedIndex].tCKESR))) + 1;
		ctm->tCKSRE = Max(5, ncp_ps_to_clk(parms->tck_ps, (speedbin_ddr4_vals[clkSpeedIndex].tCKESR)));
		ctm->tCKE = Max(3, ncp_ps_to_clk(parms->tck_ps, (speedbin_ddr4_vals[clkSpeedIndex].tCKE)));
		ctm->tMRD_PDA = Max(16, ncp_ps_to_clk(parms->tck_ps, (speedbin_ddr4_vals[clkSpeedIndex].tMRD_PDA)));
		ctm->tREFI = ncp_ps_to_clk(parms->tck_ps, ((parms->high_temp_dram == TRUE) ?  3900000 : 7800000));

		dbgprintf("ctm->speed = %d, ctm->binned_CL = %d, ctm->CL_config = %d, ctm->tRCD = %d, ctm->tRP = %d, ctm->tRAS = %d, ctm->tRC = %d, ctm->tCCD_L = %d, ctm->tCCD_S = %d, ctm->tRRD_S = %d, ctm->tRRD_L = %d, ctm->tFAW = %d, ctm->tWTR_S = %d, ctm->tWTR_L = %d, ctm->tRTP = %d, ctm->tWR = %d, ctm->tMRD = %d, ctm->tMOD = %d, ctm->tMPRR = %d, ctm->tWR_MPR = %d, ctm->tZQinit = %d, ctm->tRFC = %d, ctm->tXPR = %d, ctm->tXS = %d, ctm->tCKESR = %d, ctm->tCKSRE = %d, ctm->tCKE = %d, ctm->tMRD_PDA = %d, ctm->tREFI = %d\n",
				ctm->speed,
				ctm->binned_CL,
				ctm->CL_config,
				ctm->tRCD,
				ctm->tRP,
				ctm->tRAS,
				ctm->tRC,
				ctm->tCCD_L,
				ctm->tCCD_S,
				ctm->tRRD_S,
				ctm->tRRD_L,
				ctm->tFAW,
				ctm->tWTR_S,
				ctm->tWTR_L,
				ctm->tRTP,
				ctm->tWR,
				ctm->tMRD,
				ctm->tMOD,
				ctm->tMPRR,
				ctm->tWR_MPR,
				ctm->tZQinit,
				ctm->tRFC,
				ctm->tXPR,
				ctm->tXS,
				ctm->tCKESR,
				ctm->tCKSRE,
				ctm->tCKE,
				ctm->tMRD_PDA,
				ctm->tREFI);
		/* HACK */
		/*ctm->tRC = 50;*/
		/*ctm->tRRD_S = 7;*/
		/*ctm->tRP = 14;*/
		/*ctm->tFAW = 38;*/
		/*ctm->tRCD = 14;*/
		ctm->tMOD = 12; /* on MC this should be 12 and on PHY this should be 4 */
		/*ctm->tCKE = 6;*/
		/*ctm->tXS = 0x200;*/
		/*ctm->tCCD_L = 0x0;*/
	}

	NCP_RETURN_LABEL
		return ncpStatus;
}

ncp_st_t
ncp_sm_denali_2041_init_56xx(
		ncp_dev_hdl_t dev,
		ncp_uint32_t  smNode,
		ncp_sm_parms_t *parms,
		ncp_common_timing_parameters_t *ctm)
{
	ncp_st_t ncpStatus = NCP_ST_SUCCESS;
	ncp_region_id_t ctlReg = NCP_REGION_ID(smNode, NCP_SYSMEM_TGT_DENALI);
	ncp_uint32_t loop=0;
	ncp_uint32_t tmp=0;
	/*ncp_uint32_t tmp1=0;*/

	int i=0;
	ncp_uint8_t rd_ODT[4];
	ncp_uint8_t wr_ODT[4];
	ncp_uint32_t value=0;
	ncp_uint32_t value2=0;

	ncp_denali_DENALI_CTL_00_5600_t reg00 = {0};
	ncp_denali_DENALI_CTL_01_5600_t reg01 = {0};
	ncp_denali_DENALI_CTL_05_5600_t reg05 = {0};
	ncp_denali_DENALI_CTL_06_5600_t reg06 = {0};
	ncp_denali_DENALI_CTL_07_5600_t reg07 = {0};
	ncp_denali_DENALI_CTL_08_5600_t reg08 = {0};
	ncp_denali_DENALI_CTL_09_5600_t reg09 = {0};
	ncp_denali_DENALI_CTL_10_5600_t reg10 = {0};
	ncp_denali_DENALI_CTL_11_5600_t reg11 = {0};
	ncp_denali_DENALI_CTL_12_5600_t reg12 = {0};
	ncp_denali_DENALI_CTL_13_5600_t reg13 = {0};
	ncp_denali_DENALI_CTL_14_5600_t reg14 = {0};
	ncp_denali_DENALI_CTL_15_5600_t reg15 = {0};
	ncp_denali_DENALI_CTL_16_5600_t reg16 = {0};
	ncp_denali_DENALI_CTL_17_5600_t reg17 = {0};
	ncp_denali_DENALI_CTL_18_5600_t reg18 = {0};
	ncp_denali_DENALI_CTL_19_5600_t reg19 = {0};
	ncp_denali_DENALI_CTL_20_5600_t reg20 = {0};
	ncp_denali_DENALI_CTL_21_5600_t reg21 = {0};
	ncp_denali_DENALI_CTL_22_5600_t reg22 = {0};
	ncp_denali_DENALI_CTL_23_5600_t reg23 = {0};
	ncp_denali_DENALI_CTL_24_5600_t reg24 = {0};
	ncp_denali_DENALI_CTL_25_5600_t reg25 = {0};
	ncp_denali_DENALI_CTL_26_5600_t reg26 = {0};
	ncp_denali_DENALI_CTL_27_5600_t reg27 = {0};
	ncp_denali_DENALI_CTL_28_5600_t reg28 = {0};
	ncp_denali_DENALI_CTL_29_5600_t reg29 = {0};
	ncp_denali_DENALI_CTL_30_5600_t reg30 = {0};
	ncp_denali_DENALI_CTL_31_5600_t reg31 = {0};
	ncp_denali_DENALI_CTL_32_5600_t reg32 = {0};
	ncp_denali_DENALI_CTL_33_5600_t reg33 = {0};
	ncp_denali_DENALI_CTL_34_5600_t reg34 = {0};
	ncp_denali_DENALI_CTL_35_5600_t reg35 = {0};
	ncp_denali_DENALI_CTL_36_5600_t reg36 = {0};
	ncp_denali_DENALI_CTL_37_5600_t reg37 = {0};
	ncp_denali_DENALI_CTL_38_5600_t reg38 = {0};
	ncp_denali_DENALI_CTL_39_5600_t reg39 = {0};
	ncp_denali_DENALI_CTL_40_5600_t reg40 = {0};
	ncp_denali_DENALI_CTL_41_5600_t reg41 = {0};
	ncp_denali_DENALI_CTL_42_5600_t reg42 = {0};
	ncp_denali_DENALI_CTL_43_5600_t reg43 = {0};
	ncp_denali_DENALI_CTL_44_5600_t reg44 = {0};
	ncp_denali_DENALI_CTL_45_5600_t reg45 = {0};
	ncp_denali_DENALI_CTL_46_5600_t reg46 = {0};
	ncp_denali_DENALI_CTL_47_5600_t reg47 = {0};
	ncp_denali_DENALI_CTL_48_5600_t reg48 = {0};
	ncp_denali_DENALI_CTL_49_5600_t reg49 = {0};
	ncp_denali_DENALI_CTL_50_5600_t reg50 = {0};
	ncp_denali_DENALI_CTL_51_5600_t reg51 = {0};
	ncp_denali_DENALI_CTL_52_5600_t reg52 = {0};
	ncp_denali_DENALI_CTL_53_5600_t reg53 = {0};
	ncp_denali_DENALI_CTL_56_5600_t reg56 = {0};
	ncp_denali_DENALI_CTL_78_5600_t reg78 = {0};
	ncp_denali_DENALI_CTL_79_5600_t reg79 = {0};
	ncp_denali_DENALI_CTL_80_5600_t reg80 = {0};
	ncp_denali_DENALI_CTL_81_5600_t reg81 = {0};
	ncp_denali_DENALI_CTL_82_5600_t reg82 = {0};
	ncp_denali_DENALI_CTL_83_5600_t reg83 = {0};
	ncp_denali_DENALI_CTL_84_5600_t reg84 = {0};
	ncp_denali_DENALI_CTL_85_5600_t reg85 = {0};
	ncp_denali_DENALI_CTL_86_5600_t reg86 = {0};
	ncp_denali_DENALI_CTL_87_5600_t reg87 = {0};
	ncp_denali_DENALI_CTL_88_5600_t reg88 = {0};
	ncp_denali_DENALI_CTL_89_5600_t reg89 = {0};
	ncp_denali_DENALI_CTL_90_5600_t reg90 = {0};
	ncp_denali_DENALI_CTL_91_5600_t reg91 = {0};
	ncp_denali_DENALI_CTL_92_5600_t reg92 = {0};
	ncp_denali_DENALI_CTL_93_5600_t reg93 = {0};
	ncp_denali_DENALI_CTL_101_5600_t reg101 = {0};
	ncp_denali_DENALI_CTL_113_5600_t reg113 = {0};
	ncp_denali_DENALI_CTL_114_5600_t reg114 = {0};
	ncp_denali_DENALI_CTL_115_5600_t reg115 = {0};
	ncp_denali_DENALI_CTL_116_5600_t reg116 = {0};
	ncp_denali_DENALI_CTL_117_5600_t reg117 = {0};
	ncp_denali_DENALI_CTL_118_5600_t reg118 = {0};
	ncp_denali_DENALI_CTL_119_5600_t reg119 = {0};
	ncp_denali_DENALI_CTL_120_5600_t reg120 = {0};
	ncp_denali_DENALI_CTL_121_5600_t reg121 = {0};
	ncp_denali_DENALI_CTL_122_5600_t reg122 = {0};
	ncp_denali_DENALI_CTL_123_5600_t reg123 = {0};
	ncp_denali_DENALI_CTL_124_5600_t reg124 = {0};
	ncp_denali_DENALI_CTL_125_5600_t reg125 = {0};
	ncp_denali_DENALI_CTL_126_5600_t reg126 = {0};
	ncp_denali_DENALI_CTL_128_5600_t reg128 = {0};
	ncp_denali_DENALI_CTL_155_5600_t reg155 = {0};
	ncp_denali_DENALI_CTL_156_5600_t reg156 = {0};
	ncp_denali_DENALI_CTL_157_5600_t reg157 = {0};
	ncp_denali_DENALI_CTL_158_5600_t reg158 = {0};
	ncp_denali_DENALI_CTL_159_5600_t reg159 = {0};
	ncp_denali_DENALI_CTL_163_5600_t reg163 = {0};
	ncp_denali_DENALI_CTL_164_5600_t reg164 = {0};
	ncp_denali_DENALI_CTL_166_5600_t reg166 = {0};
	ncp_denali_DENALI_CTL_175_5600_t reg175 = {0};
	ncp_denali_DENALI_CTL_176_5600_t reg176 = {0};
	ncp_denali_DENALI_CTL_177_5600_t reg177 = {0};
	ncp_denali_DENALI_CTL_178_5600_t reg178 = {0};
	ncp_denali_DENALI_CTL_179_5600_t reg179 = {0};
	ncp_denali_DENALI_CTL_180_5600_t reg180 = {0};
	ncp_denali_DENALI_CTL_181_5600_t reg181 = {0};
	ncp_denali_DENALI_CTL_182_5600_t reg182 = {0};
	ncp_denali_DENALI_CTL_183_5600_t reg183 = {0};
	ncp_denali_DENALI_CTL_184_5600_t reg184 = {0};
	ncp_denali_DENALI_CTL_185_5600_t reg185 = {0};
	ncp_denali_DENALI_CTL_186_5600_t reg186 = {0};
	ncp_denali_DENALI_CTL_187_5600_t reg187 = {0};
	ncp_denali_DENALI_CTL_188_5600_t reg188 = {0};
	ncp_denali_DENALI_CTL_189_5600_t reg189 = {0};
	ncp_denali_DENALI_CTL_221_5600_t reg221 = {0};
	ncp_denali_DENALI_CTL_261_5600_t reg261 = {0};
	ncp_denali_DENALI_CTL_328_5600_t reg328 = {0};
	ncp_denali_DENALI_CTL_329_5600_t reg329 = {0};
	ncp_denali_DENALI_CTL_330_5600_t reg330 = {0};
	ncp_denali_DENALI_CTL_331_5600_t reg331 = {0};
	ncp_denali_DENALI_CTL_332_5600_t reg332 = {0};
	ncp_denali_DENALI_CTL_333_5600_t reg333 = {0};
	ncp_denali_DENALI_CTL_334_5600_t reg334 = {0};
	ncp_denali_DENALI_CTL_335_5600_t reg335 = {0};
	ncp_denali_DENALI_CTL_336_5600_t reg336 = {0};
	ncp_denali_DENALI_CTL_337_5600_t reg337 = {0};
	ncp_denali_DENALI_CTL_338_5600_t reg338 = {0};
	ncp_denali_DENALI_CTL_339_5600_t reg339 = {0};
	ncp_denali_DENALI_CTL_340_5600_t reg340 = {0};
	ncp_denali_DENALI_CTL_341_5600_t reg341 = {0};
	ncp_denali_DENALI_CTL_342_5600_t reg342 = {0};
	ncp_denali_DENALI_CTL_343_5600_t reg343 = {0};
	ncp_denali_DENALI_CTL_344_5600_t reg344 = {0};
	ncp_denali_DENALI_CTL_345_5600_t reg345 = {0};
	ncp_denali_DENALI_CTL_346_5600_t reg346 = {0};
	ncp_denali_DENALI_CTL_349_5600_t reg349 = {0};
	ncp_denali_DENALI_CTL_350_5600_t reg350 = {0};
	ncp_denali_DENALI_CTL_351_5600_t reg351 = {0};
	ncp_denali_DENALI_CTL_352_5600_t reg352 = {0};
	ncp_denali_DENALI_CTL_353_5600_t reg353 = {0};
	ncp_denali_DENALI_CTL_354_5600_t reg354 = {0};
	ncp_denali_DENALI_CTL_355_5600_t reg355 = {0};
	ncp_denali_DENALI_CTL_356_5600_t reg356 = {0};
	ncp_denali_DENALI_CTL_357_5600_t reg357 = {0};
	ncp_denali_DENALI_CTL_358_5600_t reg358 = {0};
	ncp_denali_DENALI_CTL_359_5600_t reg359 = {0};
	ncp_denali_DENALI_CTL_360_5600_t reg360 = {0};
	ncp_denali_DENALI_CTL_361_5600_t reg361 = {0};
	ncp_denali_DENALI_CTL_362_5600_t reg362 = {0};
	ncp_denali_DENALI_CTL_363_5600_t reg363 = {0};
	ncp_denali_DENALI_CTL_364_5600_t reg364 = {0};
	ncp_denali_DENALI_CTL_365_5600_t reg365 = {0};
	ncp_denali_DENALI_CTL_368_5600_t reg368 = {0};
	ncp_denali_DENALI_CTL_369_5600_t reg369 = {0};
	ncp_denali_DENALI_CTL_370_5600_t reg370 = {0};
	ncp_denali_DENALI_CTL_371_5600_t reg371 = {0};
	ncp_denali_DENALI_CTL_372_5600_t reg372 = {0};
	ncp_denali_DENALI_CTL_373_5600_t reg373 = {0};
	ncp_denali_DENALI_CTL_374_5600_t reg374 = {0};
	ncp_denali_DENALI_CTL_375_5600_t reg375 = {0};
	ncp_denali_DENALI_CTL_376_5600_t reg376 = {0};
	ncp_denali_DENALI_CTL_377_5600_t reg377 = {0};
	ncp_denali_DENALI_CTL_378_5600_t reg378 = {0};
	ncp_denali_DENALI_CTL_379_5600_t reg379 = {0};
	ncp_denali_DENALI_CTL_380_5600_t reg380 = {0};
	ncp_denali_DENALI_CTL_381_5600_t reg381 = {0};
	ncp_denali_DENALI_CTL_382_5600_t reg382 = {0};
	ncp_denali_DENALI_CTL_386_5600_t reg386 = {0};
	ncp_uint32_t smId = 0;

	/* this below is only for sm_parms's per_smem[n] access
	 * n is a packed parms index i.e.
	 * index 0 corresponds to 4 chars as u32 wherein
	 *		char0: interface-0 rank-0
	 *		char1: interface-0 rank-1
	 *		char2: interface-0 rank-2
	 *		char3: interface-0 rank-3
	 * X9 has 2 SMEM's so it uses only per_smem 0,1 indices and given dual-rank
	 *	the char-2,3 will always be zero.
	 * XLF has 4 SMEM's so it uses 0,1,2,3 per_smem[4] indices
	 */
	switch (smNode) {
		case 0x22:
			smId  = 0x0;	/* X9/XLF */
			break;
		case 0xf:
			smId  = 0x1;	/* X9/XLF */
			break;
		case 0x23:
			smId  = 0x2;	/* XLF */
			break;
		case 0x24:
			smId  = 0x3;	/* XLF */
			break;
		default:
			NCP_CALL(NCP_ST_ERROR);
	}

	/* unpack the ODT control words into indexed arrays */
	value  = parms->read_ODT_ctl;
	value2 = parms->write_ODT_ctl;
	for (i=0; i<4; i++) {

		rd_ODT[i] = value  & 0xf;
		wr_ODT[i] = value2 & 0xf;

		value >>= 4;
		value2 >>= 4;
	}

	/*dbgprintf("X9/XLF SMC %d Init....\n",smNode);*/

	/* DENALI_CTL_00 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_00_5600, (ncp_uint32_t *)&reg00);
	reg00.dram_class = parms->dram_class;
	ncr_write32(ctlReg, NCP_DENALI_CTL_00_5600, *((ncp_uint32_t *)&reg00));
	/*dbgprintf("start=0x%x dram_class=0x%x version=0x%x reg00=0x%x\n",reg00.start,reg00.dram_class,reg00.version,*((ncp_uint32_t *)&reg00));*/

	ncr_read32(ctlReg, NCP_DENALI_CTL_117_5600, (ncp_uint32_t *)&reg117);
	ncr_read32(ctlReg, NCP_DENALI_CTL_118_5600, (ncp_uint32_t *)&reg118);

	/* DENALI_CTL_01 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_01_5600, (ncp_uint32_t *)&reg01);
	if (parms->dram_class == NCP_SM_DDR4_MODE)
	{
		switch(parms->sdram_device_density)
		{
			case 3:
				reg117.row_diff = reg01.max_row_reg - 14; /* A0-A13 */
				break;
			case 4:
				reg117.row_diff = reg01.max_row_reg - 15; /* A0-A14 */
				break;
			case 5:
				reg117.row_diff = reg01.max_row_reg - 16; /* A0-A15 */
				break;
			case 6:
				reg117.row_diff = reg01.max_row_reg - 17; /* A0-A16 */
				break;
			default:
				errprintf("invalid sdram_device_density\n");
				NCP_CALL(NCP_ST_ERROR);
		}
		reg118.col_diff = reg01.max_col_reg - 10; /* A0-A9 always */
	}
	else
	{
		if (parms->sdram_device_density == NCP_SM_SDRAM_DENSITY_8GBIT) {
			reg117.row_diff = reg01.max_row_reg - 16;
			reg118.col_diff = reg01.max_col_reg + parms->sdram_device_width - 12;
		}
		else 
		{
			reg117.row_diff = reg01.max_row_reg + parms->sdram_device_width - parms->sdram_device_density - 13;
			reg118.col_diff = reg01.max_col_reg - 10;
		}
	}

	/* DENALI_CTL_05 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_05_5600, (ncp_uint32_t *)&reg05);
	/* dram initialization delay in memory clocks
	 * For DDR3= 700us + 10ns + tXPR + (3*tMRD) + tMOD + tZQinit
	 * For DDR4= 700us + tXPR + (3*tMRD) + tMOD + tZQinit
	 * choosing 701us upper bound */
	reg05.tinit = ncp_ps_to_clk(parms->tck_ps,701*(1000000));
	ncr_write32(ctlReg, NCP_DENALI_CTL_05_5600, *((ncp_uint32_t *)&reg05));


	/* DENALI_CTL_06 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_06_5600, (ncp_uint32_t *)&reg06);
	/* number of clocks that memory will be held in reset during init seq
	 * assuming 200us is sufficient */
	reg06.trst_pwron = ncp_ps_to_clk(parms->tck_ps,200*(1000000));
	ncr_write32(ctlReg, NCP_DENALI_CTL_06_5600, *((ncp_uint32_t *)&reg06));


	/* DENALI_CTL_07 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_07_5600, (ncp_uint32_t *)&reg07);
	/* number of clocks after reset before cke will become active
	 * assuming 500us is sufficient */
	reg07.cke_inactive = ncp_ps_to_clk(parms->tck_ps,500*(1000000));
	ncr_write32(ctlReg, NCP_DENALI_CTL_07_5600, *((ncp_uint32_t *)&reg07));


	/* DENALI_CTL_08 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_08_5600, (ncp_uint32_t *)&reg08);
	reg08.wrlat = parms->CAS_write_latency;
	reg08.caslat_lin = parms->CAS_latency * 2; /* CAS latency linear value */
	reg08.tdll = 0x300;/*0x255;*/ /* for dd3 it is 512 clocks */
	ncr_write32(ctlReg, NCP_DENALI_CTL_08_5600, *((ncp_uint32_t *)&reg08));


	/* DENALI_CTL_09 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_09_5600, (ncp_uint32_t *)&reg09);
	if (parms->dram_class == NCP_SM_DDR4_MODE)
	{
		if (parms->ddrClockSpeedMHz <= 300)
			reg09.ca_parity_lat = 0;
		else if (parms->ddrClockSpeedMHz <= 1066)
			reg09.ca_parity_lat = 4;
		else
			reg09.ca_parity_lat = 5;
		if (parms->ca_parity_en == FALSE)
			reg09.ca_parity_lat = 0;
		reg09.tmod_par = ncp_ps_to_clk(parms->tck_ps,15000) + reg09.ca_parity_lat;
		reg09.tmrd_par = ncp_ps_to_clk(parms->tck_ps,15000) + reg09.ca_parity_lat;
		reg09.additive_lat = parms->additive_latency; /* option to reggen tcl */
	}
	else
	{
		reg09.tmrd_par = 0x0;
		reg09.tmod_par = 0x0;
		reg09.ca_parity_lat = 0x0;
		reg09.additive_lat = 0x0;
	}
	ncr_write32(ctlReg, NCP_DENALI_CTL_09_5600, *((ncp_uint32_t *)&reg09));


	/* DENALI_CTL_10 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_10_5600, (ncp_uint32_t *)&reg10);
	/* min delay between CAS-to-CAS commands between different bank groups */
	reg10.tccd = (parms->dram_class == NCP_SM_DDR4_MODE) ? ctm->tCCD_S : 0x4; 
	reg10.tbst_int_interval = 4;
	reg10.tparity_error_cmd_inhibit = 0x0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_10_5600, *((ncp_uint32_t *)&reg10));


	/* DENALI_CTL_11 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_11_5600, (ncp_uint32_t *)&reg11);
	reg11.trc = ctm->tRC;
	reg11.trrd_l = (parms->dram_class == NCP_SM_DDR4_MODE) ? ctm->tRRD_L : 0x0;
	reg11.trrd = (parms->dram_class == NCP_SM_DDR4_MODE) ? ctm->tRRD_S : ctm->tRRD;
	reg11.tccd_l = (parms->dram_class == NCP_SM_DDR4_MODE) ? ctm->tCCD_L : 0x0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_11_5600, *((ncp_uint32_t *)&reg11));


	/* DENALI_CTL_12 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_12_5600, (ncp_uint32_t *)&reg12);
	reg12.trp = ctm->tRP;
	reg12.twtr_l = (parms->dram_class == NCP_SM_DDR4_MODE) ? ctm->tWTR_L : 0x0;
	reg12.twtr = ncp_ps_to_clk(parms->tck_ps,2500);
	reg12.tras_min = ctm->tRAS;
	ncr_write32(ctlReg, NCP_DENALI_CTL_12_5600, *((ncp_uint32_t *)&reg12));


	/* DENALI_CTL_13 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_13_5600, (ncp_uint32_t *)&reg13);
	reg13.tmrd = 8;
	reg13.trtp_ap = ctm->tRTP;/* was 4;*/ /* for auto-precharge get from speedbin_ddr4 */
	/*reg13.trtp = (parms->dram_class == NCP_SM_DDR4_MODE) ? ctm->tRTP : ncp_ps_to_clk(parms->tck_ps,7500);*/
	reg13.trtp = ncp_ps_to_clk(parms->tck_ps,7500);
	reg13.tfaw = ctm->tFAW;
	ncr_write32(ctlReg, NCP_DENALI_CTL_13_5600, *((ncp_uint32_t *)&reg13));


	/* DENALI_CTL_14 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_14_5600, (ncp_uint32_t *)&reg14);
	reg14.tmod = (parms->dram_class == NCP_SM_DDR4_MODE) ? ctm->tMOD : ncp_ps_to_clk(parms->tck_ps,15000);
	/* tRAS_max = (9 * tREFI) */
	reg14.tras_max = 9*(ncp_ps_to_clk(parms->tck_ps, ((parms->high_temp_dram == TRUE) ?  3900000 : 7800000)));
	ncr_write32(ctlReg, NCP_DENALI_CTL_14_5600, *((ncp_uint32_t *)&reg14));


	/* DENALI_CTL_15 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_15_5600, (ncp_uint32_t *)&reg15);
	/*reg15.tcke = ctm->tCKE;*/
	reg15.tcke = ncp_ps_to_clk(parms->tck_ps,5000);
	reg15.tckesr = reg15.tcke + 1; /* tCKE + 1nCK */
	reg15.twr_mpr = (parms->dram_class == NCP_SM_DDR4_MODE) ? ctm->tWR_MPR : 0x0;
	reg15.writeinterp = 0; /* for both ddr3, ddr4 */
	ncr_write32(ctlReg, NCP_DENALI_CTL_15_5600, *((ncp_uint32_t *)&reg15));


	/* DENALI_CTL_16 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_16_5600, (ncp_uint32_t *)&reg16);
	reg16.trcd = ctm->tRCD;
	reg16.twr = (parms->dram_class == NCP_SM_DDR4_MODE) ? ctm->tWR : ncp_ps_to_clk(parms->tck_ps,15000);
	reg16.tvref = (parms->dram_class == NCP_SM_DDR4_MODE) ? ncp_ps_to_clk(parms->tck_ps, 150000) : 0x0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_16_5600, *((ncp_uint32_t *)&reg16));


	/* DENALI_CTL_17 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_17_5600, (ncp_uint32_t *)&reg17);
	reg17.tmrd_pda = (parms->dram_class == NCP_SM_DDR4_MODE) ? ctm->tMRD_PDA : 0x0;
	reg17.tmprr = (parms->dram_class == NCP_SM_DDR4_MODE) ? ctm->tMPRR : 0x0;
	reg17.ap = (parms->dramPrechargePolicy == 0) ? 1 : 0;
	reg17.concurrentap = (parms->dramPrechargePolicy == 0) ? 1 : 0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_17_5600, *((ncp_uint32_t *)&reg17));


	/* DENALI_CTL_18 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_18_5600, (ncp_uint32_t *)&reg18);
	reg18.tras_lockout = 1;
	reg18.tdal = (parms->dram_class == NCP_SM_DDR4_MODE) ? (ctm->tWR + ctm->tRP) 
		: ( ncp_ps_to_clk(parms->tck_ps,15000) + ctm->tRP); /* tWR + roundup(tRP/tCK) */
	reg18.bstlen = parms->bstlen;/* 1 for BL2, 2 for BL4, 3 for BL8 */
	reg18.trp_ab = ctm->tRP;/* was this before parms->CAS_latency;*/
	ncr_write32(ctlReg, NCP_DENALI_CTL_18_5600, *((ncp_uint32_t *)&reg18));


	/* DENALI_CTL_19 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_19_5600, (ncp_uint32_t *)&reg19);
	reg19.reg_dimm_enable = (parms->rdimm_misc & 0x1);
	/* For mirroring, 0 means std. pinout, 1 means mirrored wiring */
	reg19.address_mirroring = (parms->address_mirroring) ? 0xa : 0x0; /* bit 0 for cs0 ....3 for cs3 */
	/* For inversion, 0 means std. pinout, 1 means inverted pinout
	   bit 0 for cs0 ....3 for cs3 */
	reg19.address_inversion = (parms->address_inversion && (parms->dram_class == NCP_SM_DDR4_MODE)) ? 0xa : 0x0; 
	ncr_write32(ctlReg, NCP_DENALI_CTL_19_5600, *((ncp_uint32_t *)&reg19));


	/* DENALI_CTL_19 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_20_5600, (ncp_uint32_t *)&reg20);
	/* Reference:
	 * For 16-bit devices: 7:4 controls dev 1, 3:0 controls dev 0
	 - 'b0000 does not use addr_inversion A side
	 - 'b1111 does use addr_inversion B side
	 For 8-bit devices: 3:2 controls dev 1, 1:0 controls dev 0
	 - 'b00 does not use addr_inversion A side
	 - 'b11 does use addr_inversion B side
	 For 4-bit devices: 1 controls dev 1, 0 controls dev 0
	 - 'b0 does not use addr_inversion A side
	 - 'b1 does use addr_inversion B side
	 */
	reg20.pda_invert_dev_cs0 = (parms->dram_class == NCP_SM_DDR4_MODE) ? /*Fix me */0 : 0x0;
	reg20.pda_invert_dev_cs1 = (parms->dram_class == NCP_SM_DDR4_MODE) ? /*Fix me */0 : 0x0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_20_5600, *((ncp_uint32_t *)&reg20));


	/* DENALI_CTL_21 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_21_5600, (ncp_uint32_t *)&reg21);
	reg21.optimal_rmodw_en = 1;
	reg21.pda_invert_ecc_dev_cs1 = (parms->dram_class == NCP_SM_DDR4_MODE) ? /*Fix me */0 : 0x0;
	reg21.pda_invert_ecc_dev_cs0 = (parms->dram_class == NCP_SM_DDR4_MODE) ? /*Fix me */0 : 0x0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_21_5600, *((ncp_uint32_t *)&reg21));


	/* DENALI_CTL_22 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_22_5600, (ncp_uint32_t *)&reg22);
	reg22.no_memory_dm = ~(parms->dm_masking);
	ncr_write32(ctlReg, NCP_DENALI_CTL_22_5600, *((ncp_uint32_t *)&reg22));


	/* DENALI_CTL_23 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_23_5600, (ncp_uint32_t *)&reg23);
	reg23.rdimm_ctl_0 = (parms->rdimm_misc & 0x1) ? parms->rdimm_ctl_0_0 : 0x0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_23_5600, *((ncp_uint32_t *)&reg23));


	/* DENALI_CTL_24 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_24_5600, (ncp_uint32_t *)&reg24);
	reg24.rdimm_ctl_0 = (parms->rdimm_misc & 0x1) ? parms->rdimm_ctl_0_1 : 0x0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_24_5600, *((ncp_uint32_t *)&reg24));


	/* DENALI_CTL_25 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_25_5600, (ncp_uint32_t *)&reg25);
	reg25.rdimm_ctl_0 = (parms->rdimm_misc & 0x1) ? parms->rdimm_ctl_0_2 : 0x0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_25_5600, *((ncp_uint32_t *)&reg25));


	/* DENALI_CTL_26 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_26_5600, (ncp_uint32_t *)&reg26);
	reg26.rdimm_ctl_0 = (parms->rdimm_misc & 0x1) ? parms->rdimm_ctl_0_3 : 0x0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_26_5600, *((ncp_uint32_t *)&reg26));


	/* DENALI_CTL_27 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_27_5600, (ncp_uint32_t *)&reg27);
	reg27.rdimm_ctl_0 = (parms->rdimm_misc & 0x1) ? parms->rdimm_ctl_0_4 : 0x0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_27_5600, *((ncp_uint32_t *)&reg27));


	/* DENALI_CTL_28 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_28_5600, (ncp_uint32_t *)&reg28);
	reg28.rdimm_ctl_1 = (parms->rdimm_misc & 0x1) ? parms->rdimm_ctl_1_0 : 0x0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_28_5600, *((ncp_uint32_t *)&reg28));


	/* DENALI_CTL_29 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_29_5600, (ncp_uint32_t *)&reg29);
	reg29.rdimm_ctl_1 = (parms->rdimm_misc & 0x1) ? parms->rdimm_ctl_1_1 : 0x0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_29_5600, *((ncp_uint32_t *)&reg29));


	/* DENALI_CTL_30 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_30_5600, (ncp_uint32_t *)&reg30);
	reg30.rdimm_ctl_1 = (parms->rdimm_misc & 0x1) ? parms->rdimm_ctl_1_2 : 0x0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_30_5600, *((ncp_uint32_t *)&reg30));


	/* DENALI_CTL_31 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_31_5600, (ncp_uint32_t *)&reg31);
	reg31.rdimm_ctl_1 = (parms->rdimm_misc & 0x1) ? parms->rdimm_ctl_1_3 : 0x0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_31_5600, *((ncp_uint32_t *)&reg31));


	/* DENALI_CTL_32 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_32_5600, (ncp_uint32_t *)&reg32);
	reg32.rdimm_ctl_1 = (parms->rdimm_misc & 0x1) ? parms->rdimm_ctl_1_4 : 0x0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_32_5600, *((ncp_uint32_t *)&reg32));


	/* DENALI_CTL_33 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_33_5600, (ncp_uint32_t *)&reg33);
	reg33.rdimm_cw_map = (parms->rdimm_misc & 0xffff0000)>>16;
	ncr_write32(ctlReg, NCP_DENALI_CTL_33_5600, *((ncp_uint32_t *)&reg33));


	/* DENALI_CTL_34 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_34_5600, (ncp_uint32_t *)&reg34);
	reg34.rdimm_tmrd = 8;
	reg34.rdimm_cw_hold_cke_en = (parms->rdimm_misc & 0x1);
	reg34.rdimm_cww_req = 0; /* trigger really */
	ncr_write32(ctlReg, NCP_DENALI_CTL_34_5600, *((ncp_uint32_t *)&reg34));


	/* DENALI_CTL_35 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_35_5600, (ncp_uint32_t *)&reg35);
	reg35.cs_map_dimm_0 = parms->topology; /* only for RDIMM */
	reg35.rdimm_tstab = (parms->dram_class == NCP_SM_DDR4_MODE) ? ncp_ps_to_clk(parms->tck_ps,5*(1000000)) : ncp_ps_to_clk(parms->tck_ps,6*(1000000));
	ncr_write32(ctlReg, NCP_DENALI_CTL_35_5600, *((ncp_uint32_t *)&reg35));


	/* DENALI_CTL_36 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_36_5600, (ncp_uint32_t *)&reg36);
	/* currently only supporting 1 rdimm so this can be zero */
	reg36.cs_map_dimm_1 = 0;
	reg36.rank0_map_dimm_0 = 0x1; /* defines which cs is rank0 on dimm 0 */
	reg36.rank0_map_dimm_1 = 0;
	reg36.rdimm_tmrd_l = (parms->dram_class == NCP_SM_DDR4_MODE) ? 16 : 0x0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_36_5600, *((ncp_uint32_t *)&reg36));


	/* DENALI_CTL_37 */
	if (parms->dram_class == NCP_SM_DDR4_MODE)
	{
		ncr_read32(ctlReg, NCP_DENALI_CTL_37_5600, (ncp_uint32_t *)&reg37);
		reg37.rdimm_tmrc = 0x10;
		reg37.rdimm_tmrd_l2 = 0x20;
		ncr_write32(ctlReg, NCP_DENALI_CTL_37_5600, *((ncp_uint32_t *)&reg37));
	}


	/* DENALI_CTL_38 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_38_5600, (ncp_uint32_t *)&reg38);
	/* for ddr4 rdimm's RC0A (bit 10) and RC3x (bit 18) are used to do special
	 * commands not desired during initialization by default */
	reg38.rdimm_cww_init_map_cke_low = ((parms->rdimm_misc & 0x1) && (parms->dram_class == NCP_SM_DDR4_MODE)) ? 
		((1<<10) - 1 - (1<<18)) : 0x0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_38_5600, *((ncp_uint32_t *)&reg38));


	/* DENALI_CTL_39 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_39_5600, (ncp_uint32_t *)&reg39);
	/* defines which bit of the CA bus to corrupt when a CA parity error is forced */
	reg39.ca_parity_error_inject = 0; /* could be in a utility ? */
	ncr_write32(ctlReg, NCP_DENALI_CTL_39_5600, *((ncp_uint32_t *)&reg39));


	/* DENALI_CTL_40 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_40_5600, (ncp_uint32_t *)&reg40);
	reg40.arefresh = 0; /* initiate auto refresh at end of current burst boundary */
	ncr_write32(ctlReg, NCP_DENALI_CTL_40_5600, *((ncp_uint32_t *)&reg40));


	/* DENALI_CTL_41 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_41_5600, (ncp_uint32_t *)&reg41);
	/* the refresh command time in clocks */
	reg41.trfc = (parms->dram_class == NCP_SM_DDR4_MODE) ? ctm->tRFC : ncp_ps_to_clk(parms->tck_ps,ddr3refresh_parms_by_density[parms->sdram_device_density]);
	reg41.tref_enable = 1; /* enables refresh commands */
	ncr_write32(ctlReg, NCP_DENALI_CTL_41_5600, *((ncp_uint32_t *)&reg41));


	/* DENALI_CTL_42 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_42_5600, (ncp_uint32_t *)&reg42);
	/* the refresh command time in clocks */
	reg42.tref = ncp_ps_to_clk(parms->tck_ps, ((parms->high_temp_dram == TRUE) ?  3900000 : 7800000));
	ncr_write32(ctlReg, NCP_DENALI_CTL_42_5600, *((ncp_uint32_t *)&reg42));


	/* DENALI_CTL_43 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_43_5600, (ncp_uint32_t *)&reg43);
	/* cycles between refreshes to different cs's. Also this must be < trfc */
	reg43.tref_interval = (parms->rdimm_misc & 0x1) ? 0x8 : 0x5;
	ncr_write32(ctlReg, NCP_DENALI_CTL_43_5600, *((ncp_uint32_t *)&reg43));


	/* DENALI_CTL_44 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_44_5600, (ncp_uint32_t *)&reg44);
	reg44.txpdll = (parms->ddrClockSpeedMHz < 1066) ? 0x17 : 0x1a;
	reg44.tpdex = (parms->ddrClockSpeedMHz < 1066) ? 0x6 : 0x7;
	ncr_write32(ctlReg, NCP_DENALI_CTL_44_5600, *((ncp_uint32_t *)&reg44));


	/* DENALI_CTL_45 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_45_5600, (ncp_uint32_t *)&reg45);
	/* trfc + 10ns, or 0xfa */
	reg45.txsnr = (parms->dram_class == NCP_SM_DDR4_MODE) ? ctm->tXS : ncp_ps_to_clk(parms->tck_ps,(ddr3refresh_parms_by_density[parms->sdram_device_density] + 10000));
	reg45.txsr = 0x200;
	ncr_write32(ctlReg, NCP_DENALI_CTL_45_5600, *((ncp_uint32_t *)&reg45));


	/* DENALI_CTL_46 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_46_5600, (ncp_uint32_t *)&reg46);
	reg46.cke_delay = 3;
	reg46.enable_quick_srefresh = 1;
	reg46.srefresh_exit_no_refresh = 0;
	reg46.pwrup_srefresh_exit = (parms->ddrRecovery == TRUE) ? 1 : 0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_46_5600, *((ncp_uint32_t *)&reg46));


	/* DENALI_CTL_47 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_47_5600, (ncp_uint32_t *)&reg47);
	reg47.lowpower_refresh_enable = 0x0; /* obsoleted */
	reg47.cksre = (parms->ddrClockSpeedMHz < 1066) ? 0xa : 0xb;;
	reg47.cksrx = (parms->ddrClockSpeedMHz < 1066) ? 0xa : 0xb;;
	ncr_write32(ctlReg, NCP_DENALI_CTL_47_5600, *((ncp_uint32_t *)&reg47));


	/* DENALI_CTL_48 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_48_5600, (ncp_uint32_t *)&reg48);
	reg48.lp_cmd = 0;
	reg48.lpi_pd_wakeup = 0; /* (16) number of DFI clocks that PHY will be idle when mem is power-down mode */
	reg48.lpi_sr_wakeup = 2; /* (64) number of DFI clocks that PHY will be idle when mem is self-refresh mode */
	ncr_write32(ctlReg, NCP_DENALI_CTL_48_5600, *((ncp_uint32_t *)&reg48));


	/* DENALI_CTL_49 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_49_5600, (ncp_uint32_t *)&reg49);
	reg49.lpi_wakeup_en = 0x0;/* HACK was 0x1f */
	reg49.lpi_timer_wakeup = 4;
	reg49.lpi_sr_mcclk_gate_wakeup = 3;
	ncr_write32(ctlReg, NCP_DENALI_CTL_49_5600, *((ncp_uint32_t *)&reg49));


	/* DENALI_CTL_50 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_50_5600, (ncp_uint32_t *)&reg50);
	reg50.lpi_wakeup_timeout = 4;
	reg50.lpi_timer_count = 3;
	ncr_write32(ctlReg, NCP_DENALI_CTL_50_5600, *((ncp_uint32_t *)&reg50));


	/* DENALI_CTL_51 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_51_5600, (ncp_uint32_t *)&reg51);
	reg51.tdfi_lp_resp = 7;
	ncr_write32(ctlReg, NCP_DENALI_CTL_51_5600, *((ncp_uint32_t *)&reg51));


	/* DENALI_CTL_52 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_52_5600, (ncp_uint32_t *)&reg52);
	reg52.lp_auto_mem_gate_en = 0;
	reg52.lp_auto_exit_en = 0;
	reg52.lp_auto_entry_en = 0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_52_5600, *((ncp_uint32_t *)&reg52));


	/* DENALI_CTL_53 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_53_5600, (ncp_uint32_t *)&reg53);
	reg53.lp_auto_sr_mc_gate_idle = 0;
	reg53.lp_auto_sr_idle = 0;
	reg53.lp_auto_pd_idle = 0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_53_5600, *((ncp_uint32_t *)&reg53));


	/* DENALI_CTL_56 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_56_5600, (ncp_uint32_t *)&reg56);
	reg56.write_modereg = 0; /* to issue mem mode register writes */
	ncr_write32(ctlReg, NCP_DENALI_CTL_56_5600, *((ncp_uint32_t *)&reg56));


	/* DENALI_CTL_57 through CTL_77 (read_mpr: not doing any multi purpose reg access) */

	/* DENALI_CTL_78 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_78_5600, (ncp_uint32_t *)&reg78);
	{
#if 1
		/* algorithm adapted from register_gen_CTL.tcl */
		ncp_uint32_t ddr3_plus = 0, ddr4bst = 0,
			     ddr3bst = 0,
			     bsttype = 0,
			     ddr3_caslat_gt_11 = 0, ddr4_caslat = 0,
			     caslat_bit0 = 0, caslat_bit3_1 = 0,
			     wr = 0;
		ncp_uint32_t tWR = ncp_ps_to_clk(parms->tck_ps,15000);

		if (parms->dram_class == NCP_SM_DDR3_MODE) 
			ddr3_plus = 1;
		if (parms->bstlen == 2) 
		{ 
			ddr3bst = 0; 
		} 
		else if (parms->bstlen == 4) 
		{
			if (ddr3_plus) ddr3bst = 2;
		}
		else
		{
			ddr3bst = 0;
		}
		if (parms->dram_class == NCP_SM_DDR3_MODE) 
		{
			if (parms->CAS_latency > 11) ddr3_caslat_gt_11 = 1;
			/* write-recovery */
			if ((tWR == 10) || (tWR == 9)) wr = 5;
			else if ((tWR == 12) || (tWR == 11)) wr = 6;
			else if ((tWR == 14) || (tWR == 13)) wr = 7;
			else if (tWR > 14) wr = 0;
			else if (tWR > 4) wr = tWR - 4;
			else wr = 1;
			if (wr > 7) errprintf ("DDR3:Invalid write-recovery for MR0 %d\n",wr);

			/* data to prog into mem mode reg 0 for cs 0 */
			reg78.mr0_data_0 = (ddr3bst + (bsttype << 3) + (parms->CAS_latency << 4) + 
					(ddr3_caslat_gt_11 << 2) + (wr << 9));
		}
		else
		{
			if(parms->CAS_latency == 17) ddr4_caslat = 13;
			else if (parms->CAS_latency == 19) ddr4_caslat = 14;
			else if (parms->CAS_latency == 21) ddr4_caslat = 15;
			else if (parms->CAS_latency < 18) ddr4_caslat = parms->CAS_latency - 9;
			else ddr4_caslat = (parms->CAS_latency / 2) - 1;
			caslat_bit0 = ddr4_caslat & 0x1;
			caslat_bit3_1 = ((ddr4_caslat >> 1) & 0x7);
			if (tWR < 10) wr = 0;
			else if (tWR > 20) wr = (tWR + 3) / 4;
			else wr = ((tWR + 1) / 2) - 5;
			if (wr > 6) errprintf ("DDR4:Invalid write-recovery for MR0 %d\n",wr);

			/* data to prog into mem mode reg 0 for cs 0 */
			reg78.mr0_data_0 = (ddr4bst + (caslat_bit0 << 2) + (bsttype << 3) + (caslat_bit3_1 << 4) + (wr << 9));
		}
#else
		/* Implementation for MR0 from JEDEC */

		/*
		 * A1:A0 	Burst Length = 0 means 8 fixed
		 * A3		Read Burst Type = 0 sequential
		 * A6:A4,A2	CAS Latency
		 * A7		TM = 0 normal
		 * A8		DLL Reset = 0 No
		 * A11:A9	WR and RTP (Write Recovery and Read to Precharge for auto precharge)
		 * A17, A13, A12	RFU = 0 during MRS
		 */
		/* Do the CAS latency translation per Table-2 in JEDEC */
		switch (parms->CAS_latency)
		{
			/* A6:A5:A4:A3(0):A2 */
			case 9: 
				tmp = 0x0;
				break;
			case 10: 
				tmp = 0x1;
				break;
			case 11: 
				tmp = 0x4;
				break;
			case 12: 
				tmp = 0x5;
				break;
			case 13: 
				tmp = 0x8;
				break;
			case 14: 
				tmp = 0x9;
				break;
			case 15: 
				tmp = 0xc;
				break;
			case 16: 
			case 17:
				tmp = 0xd;
				break;
			case 18: 
				tmp = 0x10;
				break;
			case 19: 
				tmp = 0xe;
				break;
			case 20: 
				tmp = 0x11;
				break;
			case 21: 
				tmp = 0xf;
				break;
			case 22: 
				tmp = 0x14;
				break;
			case 24: 
				tmp = 0x15;
				break;
			default:
				tmp = 0;
		}
		/* A11-A9 is based off tWR and tRTP, note- tWR is twice tRTP */
		switch (ctm->tRTP)
		{
			case 5:
				tmp1 = 0;
				break;
			case 6:
				tmp1 = 1;
				break;
			case 7:
				tmp1 = 2;
				break;
			case 8:
				tmp1 = 3;
				break;
			case 9:
				tmp1 = 4;
				break;
			case 10:
				tmp1 = 5;
				break;
			case 12:
				tmp1 = 6;
				break;
			default:
				tmp1 = 0;
		}
		reg78.mr0_data_0 = (((parms->dram_class == NCP_SM_DDR4_MODE) ? tmp1 : ncp_ps_to_clk(parms->tck_ps,15000)) << 9);
		reg78.mr0_data_0 &= ~(0x7c);
		reg78.mr0_data_0 |= (tmp << 2);
#endif
	}
	ctm->mr0 = reg78.mr0_data_0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_78_5600, *((ncp_uint32_t *)&reg78));

	/* DENALI_CTL_79 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_79_5600, (ncp_uint32_t *)&reg79);
	{
		/* data to prog into mem mode reg 1 for cs 0 */
		/* Implementation for MR1 from JEDEC (ddr4) */

		/*
		 * A0 		DLL Enable 0=disable
		 * A2,A1	Output Driver Impedance Control
		 * A4, A3	Additive Latency
		 * A6,A5	RFU = 0 during MRS
		 * A7		Write Leveling Enable 0 = disable
		 * A10/9/8	RTT_NOM
		 * A11		TDQS enable 0 = disable
		 * A12		Qoff 0 = output buffer enabled
		 * A13,A17	RFU 0 during MRS
		 */
		if (parms->dram_class == NCP_SM_DDR4_MODE)
		{
			reg79.mr1_data_0 = NCP_SM_ENCODE_RTT_NOM_DDR4(parms->per_smem[smId].sdram_rtt_nom[0]) |
				NCP_SM_ENCODE_DRV_IMP_DDR4(parms->per_smem[smId].sdram_data_drv_imp[0]) |
				(parms->additive_latency << 3) | (0x1 /*DLLenable*/);
		}
		else
		{
			reg79.mr1_data_0 = NCP_SM_ENCODE_RTT_NOM_DDR3(parms->per_smem[smId].sdram_rtt_nom[0]) |
				NCP_SM_ENCODE_DRV_IMP_DDR3(parms->per_smem[smId].sdram_data_drv_imp[0]) |
				(0x1 /*DLLenable*/);
		}
	}
	ctm->mr1 = reg79.mr1_data_0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_79_5600, *((ncp_uint32_t *)&reg79));

	/* DENALI_CTL_80 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_80_5600, (ncp_uint32_t *)&reg80);
	{
		/* data to prog into mem mode reg 2 for cs 0 */
		/* Implementation for MR2 from JEDEC (ddr4) */

		/*
		 * A2:A0 	RFU 0 during MRS
		 * A5:A3	CAS Write Latency
		 * A7:A6	LP ASR 0 = Normal, 1 = Reduced temp, 2 = extended temp, 3 = auto self-refresh
		 * A8		RFU 0 during MRS
		 * A10:A9	RTT_WR
		 * A11		RFU 0 during MRS
		 * A12		write CRC 0 = disable
		 * A13		RFU 0 during MRS	
		 * A17		RFU 0 during MRS	
		 */
		switch (parms->CAS_write_latency)
		{
			/* A5:A4:A3 */
			case 9: 
				tmp = 0x0;
				break;
			case 10: 
				tmp = 0x1;
				break;
			case 11: 
				tmp = 0x2;
				break;
			case 12: 
				tmp = 0x3;
				break;
			case 14: 
				tmp = 0x4;
				break;
			case 16: 
				tmp = 0x5;
				break;
			case 18: 
				tmp = 0x6;
				break;
			default:
				tmp = 0;
		}
		if (parms->dram_class == NCP_SM_DDR4_MODE)
		{
			reg80.mr2_data_0 = (parms->per_smem[smId].sdram_rtt_wr[0] << 9);
			reg80.mr2_data_0 &= ~(0x38);
			reg80.mr2_data_0 |= (tmp << 3);
			if (parms->high_temp_dram == TRUE)
			{
				reg80.mr2_data_0 |= 0x80;
			}
			else
			{
				reg80.mr2_data_0 |= 0x40;
			}
		}
		else
		{
			reg80.mr2_data_0 = ((parms->CAS_write_latency - 5 ) << 3) | (parms->per_smem[smId].sdram_rtt_wr[0] << 9);
			if (parms->high_temp_dram == TRUE)
			{
				reg80.mr2_data_0 |= 0x80;
			}
		}
	}
	/* HACK: */
	/*reg80.mr2_data_0 &= ~(0x40);*/
	ctm->mr2 = reg80.mr2_data_0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_80_5600, *((ncp_uint32_t *)&reg80));

	/* DENALI_CTL_81 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_81_5600, (ncp_uint32_t *)&reg81);
	reg81.mrsingle_data_0 = 0x0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_81_5600, *((ncp_uint32_t *)&reg81));

	/* DENALI_CTL_82 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_82_5600, (ncp_uint32_t *)&reg82);
	{
		/* data to prog into mem mode reg 3 for cs 0 */
		/* Implementation for MR3 from JEDEC (ddr4) */

		/*
		 * A1:A0 	MPR Page selection 0 = page0
		 * A2		MPR operation 0 = normal
		 * A3		Geardown mode  0 = 1/2 rate
		 * A4		per DRAM addressability 0 = disable
		 * A5		temp sensor readout 0 = disabled
		 * A8:A6 	fine granularity refresh mode 0 = normal, 1 = 2x, 2 = 4x, Enable-on-the-fly 2x/4x TBD
		 * A10:A9	Write cmd latency when crc and DM are enabled
		 * A12:A11	MPR read format 0 = serial
		 * A13, A17	RFU 0 during MRS
		 */
		if (parms->dram_class == NCP_SM_DDR4_MODE)
		{
			reg82.mr3_data_0 = parms->refresh_mode << 6;
		}
		else
		{
			reg82.mr3_data_0 = 0;
		}
	}
	/* HACK: For 1866,2133,2400 set 10:9 01, for 1600 set as '00*/
	reg82.mr3_data_0 |= 0x200;
	ctm->mr3 = reg82.mr3_data_0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_82_5600, *((ncp_uint32_t *)&reg82));

	/* DENALI_CTL_83 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_83_5600, (ncp_uint32_t *)&reg83);
	{
		/* data to prog into mem mode reg 4 for cs 0 */
		/* Implementation for MR4 from JEDEC (ddr4) */

		/*
		 * A0		RFU
		 * A1		Max power-down mode 0 = disable
		 * A2		temp controlled refresh range 0 = normal 1 = extended
		 * A3 		temp controlled refresh mode 0 = disable, 1 = enable
		 * A4		Int vref monitor 0 = disable
		 * A5		RFU
		 * A8:A6	cs to cmd/addr latency mode 0 = disable
		 * A9		self refresh abort 0 = disable
		 * A10		read preamble training mode 0 = disable
		 * A11		read preamble 0 = 1 nCK
		 * A12		write preamble 0 = 1 nCK
		 * A13, A17	RFU
		 */
		if (parms->high_temp_dram == TRUE)
		{
			reg83.mr4_data_0 |= 0x4;
		}
	}
	ctm->mr4 = reg83.mr4_data_0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_83_5600, *((ncp_uint32_t *)&reg83));

	/* DENALI_CTL_84 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_84_5600, (ncp_uint32_t *)&reg84);
	{
		/* data to prog into mem mode reg 5 for cs 0 */
		/* Implementation for MR5 from JEDEC (ddr4) */

		/*
		 * A2:A0	CA parity lat mode 0 = disable
		 * A3		crc error clear 0 = clear
		 * A4		ca parity error status 0 = clear
		 * A5		odt input buffer 0 = activated
		 * A8:A6	rtt_park 0 = disable
		 * A9		ca parity persistent error 0 = disable
		 * A10		data mask 0 = disable
		 * A11		write dbi 0 = disable
		 * A12		read dbi 0 = disable
		 * A13, A17	RFU
		 */
		reg84.mr5_data_0 = NCP_SM_ENCODE_RTT_PARK_DDR4(parms->per_smem[smId].sdram_rtt_park[0]) |
			(0x400 /* enable data mask */) | (parms->dbi_wr_en << 11) | (parms->dbi_rd_en << 12);
	}
	ctm->mr5 = reg84.mr5_data_0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_84_5600, *((ncp_uint32_t *)&reg84));

	/* DENALI_CTL_85 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_85_5600, (ncp_uint32_t *)&reg85);
	{
		/* data to prog into mem mode reg 6 for cs 0 */
		/* Implementation for MR6 from JEDEC (ddr4) */

		/*
		 * A5:A0	vref training value (set this to 0x18)
		 * A6		vref training range
		 * A7		vref training enable
		 * A9,A8	RFU
		 * A12:A10	tCCD_L
		 * A13, A17	RFU
		 */
		switch (ctm->tCCD_L)
		{
			case 4:
				tmp = 0;
				break;
			case 5:
				tmp = 1;
				break;
			case 6:
				tmp = 2;
				break;
			case 7:
				tmp = 3;
				break;
			case 8:
				tmp = 4;
				break;
			default:
				tmp = 0;
				;
		}
		reg85.mr6_data_0 = 0x18;
		reg85.mr6_data_0 &= ~(0x1c00);
		reg85.mr6_data_0 |= ((parms->dram_class == NCP_SM_DDR4_MODE) ? (tmp << 10) : 0x0);
	}
	/* HACK */
	reg85.mr6_data_0 |= 0x800;
	ctm->mr6 = reg85.mr6_data_0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_85_5600, *((ncp_uint32_t *)&reg85));

	/* DENALI_CTL_86 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_86_5600, (ncp_uint32_t *)&reg86);
	reg86.mr0_data_1 = reg78.mr0_data_0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_86_5600, *((ncp_uint32_t *)&reg86));

	/* DENALI_CTL_87 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_87_5600, (ncp_uint32_t *)&reg87);
	if (parms->dram_class == NCP_SM_DDR4_MODE)
	{
		reg87.mr1_data_1 = NCP_SM_ENCODE_RTT_NOM_DDR4(parms->per_smem[smId].sdram_rtt_nom[1]) |
			NCP_SM_ENCODE_DRV_IMP_DDR4(parms->per_smem[smId].sdram_data_drv_imp[1]) |
			(parms->additive_latency << 3) | (0x1 /*DLLenable*/);
	}
	else
	{
		reg87.mr1_data_1 = NCP_SM_ENCODE_RTT_NOM_DDR3(parms->per_smem[smId].sdram_rtt_nom[1]) |
			NCP_SM_ENCODE_DRV_IMP_DDR3(parms->per_smem[smId].sdram_data_drv_imp[1]) |
			(0x1 /*DLLenable*/);
	}
	ncr_write32(ctlReg, NCP_DENALI_CTL_87_5600, *((ncp_uint32_t *)&reg87));

	/* DENALI_CTL_88 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_88_5600, (ncp_uint32_t *)&reg88);
	/* data to prog into mem mode reg 2 for cs 0 */
	/* Implementation for MR2 from JEDEC (ddr4) */

	/*
	 * A2:A0 	RFU 0 during MRS
	 * A5:A3	CAS Write Latency
	 * A7:A6	LP ASR 0 = Normal, 1 = Reduced temp, 2 = extended temp, 3 = auto self-refresh
	 * A8		RFU 0 during MRS
	 * A10:A9	RTT_WR
	 * A11		RFU 0 during MRS
	 * A12		write CRC 0 = disable
	 * A13		RFU 0 during MRS	
	 * A17		RFU 0 during MRS	
	 */
	switch (parms->CAS_write_latency)
	{
		/* A5:A4:A3 */
		case 9: 
			tmp = 0x0;
			break;
		case 10: 
			tmp = 0x1;
			break;
		case 11: 
			tmp = 0x2;
			break;
		case 12: 
			tmp = 0x3;
			break;
		case 14: 
			tmp = 0x4;
			break;
		case 16: 
			tmp = 0x5;
			break;
		case 18: 
			tmp = 0x6;
			break;
		default:
			tmp = 0;
	}
	if (parms->dram_class == NCP_SM_DDR4_MODE)
	{
		reg88.mr2_data_1 = (parms->per_smem[smId].sdram_rtt_wr[1] << 9);
		reg88.mr2_data_1 &= ~(0x38);
		reg88.mr2_data_1 |= (tmp << 3);
		if (parms->high_temp_dram == TRUE)
		{
			reg88.mr2_data_1 |= 0x80;
		}
		else
		{
			reg88.mr2_data_1 |= 0x40;
		}
	}
	else
	{
		reg88.mr2_data_1 = ((parms->CAS_write_latency - 5 ) << 3) | (parms->per_smem[smId].sdram_rtt_wr[1] << 9);
		if (parms->high_temp_dram == TRUE)
		{
			reg88.mr2_data_1 |= 0x80;
		}
	}
	ncr_write32(ctlReg, NCP_DENALI_CTL_88_5600, *((ncp_uint32_t *)&reg88));

	/* DENALI_CTL_89 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_89_5600, (ncp_uint32_t *)&reg89);
	reg89.mrsingle_data_1 = reg81.mrsingle_data_0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_89_5600, *((ncp_uint32_t *)&reg89));

	/* DENALI_CTL_90 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_90_5600, (ncp_uint32_t *)&reg90);
	reg90.mr3_data_1 = reg82.mr3_data_0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_90_5600, *((ncp_uint32_t *)&reg90));

	/* DENALI_CTL_91 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_91_5600, (ncp_uint32_t *)&reg91);
	reg91.mr4_data_1 = reg83.mr4_data_0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_91_5600, *((ncp_uint32_t *)&reg91));

	/* DENALI_CTL_92 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_92_5600, (ncp_uint32_t *)&reg92);
	{
		/* data to prog into mem mode reg 5 for cs 0 */
		/* Implementation for MR5 from JEDEC (ddr4) */

		/*
		 * A2:A0	CA parity lat mode 0 = disable
		 * A3		crc error clear 0 = clear
		 * A4		ca parity error status 0 = clear
		 * A5		odt input buffer 0 = activated
		 * A8:A6	rtt_park 0 = disable
		 * A9		ca parity persistent error 0 = disable
		 * A10		data mask 0 = disable
		 * A11		write dbi 0 = disable
		 * A12		read dbi 0 = disable
		 * A13, A17	RFU
		 */
		reg92.mr5_data_1 = NCP_SM_ENCODE_RTT_PARK_DDR4(parms->per_smem[smId].sdram_rtt_park[1]) |
			(0x400 /* enable data mask */) | (parms->dbi_wr_en << 11) | (parms->dbi_rd_en << 12);
	}
	ncr_write32(ctlReg, NCP_DENALI_CTL_92_5600, *((ncp_uint32_t *)&reg92));

	/* DENALI_CTL_93 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_93_5600, (ncp_uint32_t *)&reg93);
	reg93.bist_go = 0x0;
	reg93.mr6_data_1 = reg85.mr6_data_0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_93_5600, *((ncp_uint32_t *)&reg93));

	/* DENALI_CTL_101 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_101_5600, (ncp_uint32_t *)&reg101);
	reg101.fwc = 0;
	reg101.ecc_en = parms->enableECC;
	ncr_write32(ctlReg, NCP_DENALI_CTL_101_5600, *((ncp_uint32_t *)&reg101));

	/* This is needed in the case where MC init's the DRAM's and for done to be achieved */
	/* DENALI_CTL_382 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_382_5600, (ncp_uint32_t *)&reg382);
	reg382.init_start = 1;
	ncr_write32(ctlReg, NCP_DENALI_CTL_382_5600, *((ncp_uint32_t *)&reg382));

	/* DENALI_CTL_113 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_113_5600, (ncp_uint32_t *)&reg113);
	reg113.zqinit = (parms->dram_class == NCP_SM_DDR4_MODE) ? ctm->tZQinit : ncp_ps_to_clk(parms->tck_ps, 1000000); /* 1 us */
	reg113.long_count_mask = 0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_113_5600, *((ncp_uint32_t *)&reg113));

	/* DENALI_CTL_114 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_114_5600, (ncp_uint32_t *)&reg114);
	reg114.zqcs = 128;/* ncp_ps_to_clk(parms->tck_ps, 90000); *//* 90 ns */
	reg114.zqcl = 512;/* ncp_ps_to_clk(parms->tck_ps, 360000); *//* 360 ns */
	ncr_write32(ctlReg, NCP_DENALI_CTL_114_5600, *((ncp_uint32_t *)&reg114));

	/* DENALI_CTL_115 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_115_5600, (ncp_uint32_t *)&reg115);
	/* ZQ Calib performed at self-refresh exit is per zqcs (set to 1)
	 * or zqcl (set to 2) */
	reg115.zq_on_sref_exit = 2; 
	reg115.zq_req = 0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_115_5600, *((ncp_uint32_t *)&reg115));

	/* DENALI_CTL_116 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_116_5600, (ncp_uint32_t *)&reg116);
	reg116.zq_interval = (((parms->zqcs_interval /* units in micro-sec */)*1000000)/parms->tck_ps)/1024 /* long count seq */;
	ncr_write32(ctlReg, NCP_DENALI_CTL_116_5600, *((ncp_uint32_t *)&reg116));

	/* DENALI_CTL_117 */
	/* reg117.row_diff set early on */
	reg117.bank_diff = 0; /* all banks being used */
	reg117.zqcs_rotate = 1;
	ncr_write32(ctlReg, NCP_DENALI_CTL_117_5600, *((ncp_uint32_t *)&reg117));

	/* DENALI_CTL_118 */
	reg118.aprebit = 0xa; /* loc of auto pre-charge bit in dram addr */
	/* reg118.col_diff set early on */
	ncr_write32(ctlReg, NCP_DENALI_CTL_118_5600, *((ncp_uint32_t *)&reg118));

	/* DENALI_CTL_119 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_119_5600, (ncp_uint32_t *)&reg119);
	reg119.addr_cmp_en = 1; /* enable addr collision detection */
	reg119.command_age_count = 0xff;
	reg119.age_count = 0xff;
	ncr_write32(ctlReg, NCP_DENALI_CTL_119_5600, *((ncp_uint32_t *)&reg119));

	/* DENALI_CTL_120 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_120_5600, (ncp_uint32_t *)&reg120);
	reg120.rw_same_en = 0x1;
	reg120.priority_en = 0x1;
	reg120.placement_en = 0x1;
	reg120.bank_split_en = 0x1;
	ncr_write32(ctlReg, NCP_DENALI_CTL_120_5600, *((ncp_uint32_t *)&reg120));

	/* DENALI_CTL_121 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_121_5600, (ncp_uint32_t *)&reg121);
	reg121.disable_rw_group_w_bnk_conflict = 0x1;
	reg121.w2r_split_en = 0x1;
	reg121.cs_same_en = 0x1;
	reg121.rw_same_page_en = 0x1;
	ncr_write32(ctlReg, NCP_DENALI_CTL_121_5600, *((ncp_uint32_t *)&reg121));

	/* DENALI_CTL_122 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_122_5600, (ncp_uint32_t *)&reg122);
	reg122.num_q_entries_act_disable = 8;
	reg122.swap_en = 1;
	reg122.disable_rd_interleave = 0;
	reg122.inhibit_dram_cmd = 0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_122_5600, *((ncp_uint32_t *)&reg122));

	/* DENALI_CTL_123 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_123_5600, (ncp_uint32_t *)&reg123);
	reg123.cs_map = parms->topology;
	reg123.burst_on_fly_bit = 0xc;
	reg123.reduc = (parms->primary_bus_width == 2) ? 1 : 0;
	reg123.memdata_ratio_0 = (parms->sdram_device_width == 1) ? 3 : 2;
	ncr_write32(ctlReg, NCP_DENALI_CTL_123_5600, *((ncp_uint32_t *)&reg123));

	/* DENALI_CTL_124 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_124_5600, (ncp_uint32_t *)&reg124);
	reg124.memdata_ratio_1 = (parms->sdram_device_width == 1) ? 3 : 2;
	ncr_write32(ctlReg, NCP_DENALI_CTL_124_5600, *((ncp_uint32_t *)&reg124));

	/* DENALI_CTL_125 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_125_5600, (ncp_uint32_t *)&reg125);
	reg125.rd_preamble_training_en = 0x0;
	reg125.preamble_support = parms->preamble_support;
	reg125.ctrlupd_req_per_aref_en = 0x1;
	reg125.ctrlupd_req = 0x0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_125_5600, *((ncp_uint32_t *)&reg125));

	/* DENALI_CTL_126 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_126_5600, (ncp_uint32_t *)&reg126);
	reg126.rd_dbi_en = parms->dbi_rd_en;
	reg126.wr_dbi_en = parms->dbi_wr_en;
	ncr_write32(ctlReg, NCP_DENALI_CTL_126_5600, *((ncp_uint32_t *)&reg126));

	/* DENALI_CTL_128 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_128_5600, (ncp_uint32_t *)&reg128);
	reg128.bg_rotate_en = 0x1;
	ncr_write32(ctlReg, NCP_DENALI_CTL_128_5600, *((ncp_uint32_t *)&reg128));

	/* DENALI_CTL_155 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_155_5600, (ncp_uint32_t *)&reg155);
	reg155.odt_wr_map_cs1 = wr_ODT[1];
	reg155.odt_rd_map_cs1 = rd_ODT[1];
	reg155.odt_wr_map_cs0 = wr_ODT[0];
	reg155.odt_rd_map_cs0 = rd_ODT[0];
	ncr_write32(ctlReg, NCP_DENALI_CTL_155_5600, *((ncp_uint32_t *)&reg155));

	/* DENALI_CTL_156 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_156_5600, (ncp_uint32_t *)&reg156);
	reg156.odt_en = 0x1;
	reg156.todth_rd = 0x6;
	reg156.todth_wr = 0x6;
	reg156.todtl_2cmd = (parms->additive_latency + parms->CAS_write_latency -2 + 1);/* was 0x8 */
	ncr_write32(ctlReg, NCP_DENALI_CTL_156_5600, *((ncp_uint32_t *)&reg156));

	/* DENALI_CTL_157 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_157_5600, (ncp_uint32_t *)&reg157);
	reg157.r2w_diffcs_dly = 0x2;
	reg157.r2r_diffcs_dly = 0x2;
	reg157.rd_to_odth = 0x5;
	ncr_write32(ctlReg, NCP_DENALI_CTL_157_5600, *((ncp_uint32_t *)&reg157));

	/* DENALI_CTL_158 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_158_5600, (ncp_uint32_t *)&reg158);
	reg158.r2w_samecs_dly = 0x4;
	reg158.r2r_samecs_dly = 0x0;
	reg158.w2w_diffcs_dly = 0x2;
	reg158.w2r_diffcs_dly = 0x2;
	ncr_write32(ctlReg, NCP_DENALI_CTL_158_5600, *((ncp_uint32_t *)&reg158));

	/* DENALI_CTL_159 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_159_5600, (ncp_uint32_t *)&reg159);
	reg159.w2r_samecs_dly = 0x2;
	ncr_write32(ctlReg, NCP_DENALI_CTL_159_5600, *((ncp_uint32_t *)&reg159));

	/* DENALI_CTL_163 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_163_5600, (ncp_uint32_t *)&reg163);
	reg163.wldqsen = 0xd;
	reg163.wlmrd = 0x28;
	ncr_write32(ctlReg, NCP_DENALI_CTL_163_5600, *((ncp_uint32_t *)&reg163));

	/* DENALI_CTL_164 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_164_5600, (ncp_uint32_t *)&reg164);
	reg164.wrlvl_en = 0x0;
	reg164.wrlvl_interval = 0x0;
	reg164.dfi_phy_wrlvl_mode = 0x1;
	ncr_write32(ctlReg, NCP_DENALI_CTL_164_5600, *((ncp_uint32_t *)&reg164));

	/* DENALI_CTL_166 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_166_5600, (ncp_uint32_t *)&reg166);
	reg166.wrlvl_aref_en = 0x1;
	reg166.wrlvl_rotate = 0x0;
	reg166.wrlvl_cs_map = 0xf;
	ncr_write32(ctlReg, NCP_DENALI_CTL_166_5600, *((ncp_uint32_t *)&reg166));

	/* DENALI_CTL_175 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_175_5600, (ncp_uint32_t *)&reg175);
	reg175.dfi_phy_rdlvl_mode = 0x1;
	reg175.rdlvl_gate_seq_en = 0x0;
	reg175.rdlvl_seq_en = 0x0;
	reg175.rdlvl_format_3 = 0x0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_175_5600, *((ncp_uint32_t *)&reg175));

	/* DENALI_CTL_176 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_176_5600, (ncp_uint32_t *)&reg176);
	reg176.rdlvl_gate_periodic = 0x0;
	reg176.rdlvl_on_sref_exit = 0x0;
	reg176.rdlvl_periodic = 0x0;
	reg176.dfi_phy_rdlvl_gate_mode = 0x1; /* Phy support for DFI gate training */
	ncr_write32(ctlReg, NCP_DENALI_CTL_176_5600, *((ncp_uint32_t *)&reg176));

	/* DENALI_CTL_177 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_177_5600, (ncp_uint32_t *)&reg177);
	reg177.rdlvl_gate_rotate = 0x0;
	reg177.rdlvl_rotate = 0x0;
	reg177.rdlvl_aref_en = 0x1;
	reg177.rdlvl_gate_on_sref_exit = 0x0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_177_5600, *((ncp_uint32_t *)&reg177));

	/* DENALI_CTL_178 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_178_5600, (ncp_uint32_t *)&reg178);
	reg178.rdlvl_cs_map = 0xf;
	reg178.rdlvl_gate_cs_map = 0xf;
	reg178.vref_cs = parms->vref_cs; /* default cs0 set to 0x1 */
	reg178.vref_en = 0x0;/* would be done by PHY ((parms->packedPHYTrainingOptions >> 17) & 0x1);*/ /* default disabled set to 0x0 */
	ncr_write32(ctlReg, NCP_DENALI_CTL_178_5600, *((ncp_uint32_t *)&reg178));

	if (parms->dram_class == NCP_SM_DDR4_MODE)
	{
		/* DENALI_CTL_179 */
		ncr_read32(ctlReg, NCP_DENALI_CTL_179_5600, (ncp_uint32_t *)&reg179);
		/* vref_pda_en is per DRAM addressability during VREF training, set to simply
		 * vref_en setting. */
		reg179.vref_pda_en = ((parms->packedPHYTrainingOptions >> 17) & 0x1);
		/* defines the range and value for vref training - 0x67 set to ~70%
		 * It is 7 bits, b[6] is range, whereas b[5:0] is the actual vref value
		 * there is setting for each DRAM for each chip-select */

		/* set vref_val in sm_parms to 0x67 */
		reg179.vref_val_dev0_0 = parms->vref_val;
		reg179.vref_val_dev0_1 = parms->vref_val;
		reg179.vref_val_dev1_0 = parms->vref_val;
		ncr_write32(ctlReg, NCP_DENALI_CTL_179_5600, *((ncp_uint32_t *)&reg179));

		/* DENALI_CTL_180 */
		ncr_read32(ctlReg, NCP_DENALI_CTL_180_5600, (ncp_uint32_t *)&reg180);
		reg180.vref_val_dev1_1 = parms->vref_val;
		reg180.vref_val_dev2_0 = parms->vref_val;
		reg180.vref_val_dev2_1 = parms->vref_val;
		reg180.vref_val_dev3_0 = parms->vref_val;
		ncr_write32(ctlReg, NCP_DENALI_CTL_180_5600, *((ncp_uint32_t *)&reg180));

		/* DENALI_CTL_181 */
		ncr_read32(ctlReg, NCP_DENALI_CTL_181_5600, (ncp_uint32_t *)&reg181);
		reg181.vref_val_dev3_1 = parms->vref_val;
		reg181.vref_val_dev4_0 = parms->vref_val;
		reg181.vref_val_dev4_1 = parms->vref_val;
		reg181.vref_val_dev5_0 = parms->vref_val;
		ncr_write32(ctlReg, NCP_DENALI_CTL_181_5600, *((ncp_uint32_t *)&reg181));

		/* DENALI_CTL_182 */
		ncr_read32(ctlReg, NCP_DENALI_CTL_182_5600, (ncp_uint32_t *)&reg182);
		reg182.vref_val_dev5_1 = parms->vref_val;
		reg182.vref_val_dev6_0 = parms->vref_val;
		reg182.vref_val_dev6_1 = parms->vref_val;
		reg182.vref_val_dev7_0 = parms->vref_val;
		ncr_write32(ctlReg, NCP_DENALI_CTL_182_5600, *((ncp_uint32_t *)&reg182));

		/* DENALI_CTL_183 */
		ncr_read32(ctlReg, NCP_DENALI_CTL_183_5600, (ncp_uint32_t *)&reg183);
		reg183.vref_val_dev7_1 = parms->vref_val;
		reg183.vref_val_dev8_0 = parms->vref_val;
		reg183.vref_val_dev8_1 = parms->vref_val;
		reg183.vref_val_dev9_0 = parms->vref_val;
		ncr_write32(ctlReg, NCP_DENALI_CTL_183_5600, *((ncp_uint32_t *)&reg183));

		/* DENALI_CTL_184 */
		ncr_read32(ctlReg, NCP_DENALI_CTL_184_5600, (ncp_uint32_t *)&reg184);
		reg184.vref_val_dev9_1 = parms->vref_val;
		reg184.vref_val_dev10_0 = parms->vref_val;
		reg184.vref_val_dev10_1 = parms->vref_val;
		reg184.vref_val_dev11_0 = parms->vref_val;
		ncr_write32(ctlReg, NCP_DENALI_CTL_184_5600, *((ncp_uint32_t *)&reg184));

		/* DENALI_CTL_185 */
		ncr_read32(ctlReg, NCP_DENALI_CTL_185_5600, (ncp_uint32_t *)&reg185);
		reg185.vref_val_dev11_1 = parms->vref_val;
		reg185.vref_val_dev12_0 = parms->vref_val;
		reg185.vref_val_dev12_1 = parms->vref_val;
		reg185.vref_val_dev13_0 = parms->vref_val;
		ncr_write32(ctlReg, NCP_DENALI_CTL_185_5600, *((ncp_uint32_t *)&reg185));

		/* DENALI_CTL_186 */
		ncr_read32(ctlReg, NCP_DENALI_CTL_186_5600, (ncp_uint32_t *)&reg186);
		reg186.vref_val_dev13_1 = parms->vref_val;
		reg186.vref_val_dev14_0 = parms->vref_val;
		reg186.vref_val_dev14_1 = parms->vref_val;
		reg186.vref_val_dev15_0 = parms->vref_val;
		ncr_write32(ctlReg, NCP_DENALI_CTL_186_5600, *((ncp_uint32_t *)&reg186));

		/* DENALI_CTL_187 */
		ncr_read32(ctlReg, NCP_DENALI_CTL_187_5600, (ncp_uint32_t *)&reg187);
		reg187.vref_val_dev15_1 = parms->vref_val;
		reg187.vref_val_ecc_dev0_0 = parms->vref_val;
		reg187.vref_val_ecc_dev0_1 = parms->vref_val;
		reg187.vref_val_ecc_dev1_0 = parms->vref_val;
		ncr_write32(ctlReg, NCP_DENALI_CTL_187_5600, *((ncp_uint32_t *)&reg187));
	}

	/* DENALI_CTL_188 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_188_5600, (ncp_uint32_t *)&reg188);
	reg188.vref_val_ecc_dev1_1 = parms->vref_val;
	reg188.axi0_all_strobes_used_enable = 0x0; /* allows AXI port to accept Wr without waiting for all data */
	reg188.axi0_fixed_port_priority_enable = 0x0; /* defines priority scheme used 0 means defined per command, 1 means per port */
	reg188.axi0_r_priority = 0x8; /* read priority 0 is highest */
	ncr_write32(ctlReg, NCP_DENALI_CTL_188_5600, *((ncp_uint32_t *)&reg188));

	/* DENALI_CTL_189 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_189_5600, (ncp_uint32_t *)&reg189);
	reg189.axi0_w_priority = 0x8; /* write priority 0 is highest */
	reg189.port_addr_protection_en = 0x0; /* enable port address range protection logic by default */
	reg189.axi0_address_range_enable = 0x0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_189_5600, *((ncp_uint32_t *)&reg189));

	/* DENALI_CTL_190 (0x2f8)...221 (0x374) */
	for (loop=0; loop < 32; loop++)
	{
		/* axi0_start_addr is 0x0 and axi0_end_addr is 0xffffff uniformly */
		ncr_write32(ctlReg, (NCP_DENALI_CTL_190_5600 + (loop * 0x4)), ((!(loop % 2)) ? 0x0 : 0xffffff));
	}

	/* DENALI_CTL_221 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_221_5600, (ncp_uint32_t *)&reg221);
	reg221.axi0_range_prot_bits_0 = 0x3; /* 0: privileged and secure, 1: secure, 2: privileged, 3: full access */
	ncr_write32(ctlReg, NCP_DENALI_CTL_221_5600, *((ncp_uint32_t *)&reg221));

	/* DENALI_CTL_222 (0x378), 227 (0x38c).... */
	for (loop=0; loop < 8; loop++)
	{
		/* Programming
		 * axi0_range_wid_check_bits_0 through 14
		 * axi0_range_rid_check_bits_0 through 14
		 * over multiple registers.
		 */
		ncr_write32(ctlReg, (NCP_DENALI_CTL_222_5600 + (loop * 0x14)), 0xffffffff);

		/* Programming
		 * axi0_range_wid_check_bits_id_lookup_0 through 14
		 * axi0_range_rid_check_bits_id_lookup_0 through 14
		 *
		 * axi0_range_wid_check_bits_id_lookup_1
		 * axi0_range_prot_bits_2
		 * over multiple registers.
		 */
		ncr_write32(ctlReg, (NCP_DENALI_CTL_223_5600 + (loop * 0x14)), ((!(loop % 2)) ? 0xf000f : 0x3000f));

		/* Programming
		 * axi0_range_prot_bits_*
		 * axi0_range_rid_check_bits_*
		 * over multiple registers.
		 */
		ncr_write32(ctlReg, (NCP_DENALI_CTL_224_5600 + (loop * 0x14)), 0xffff03);

		/* Programming
		 * axi0_range_wid_check_bits_1*
		 * axi0_range_rid_check_bits_id_lookup_1*
		 * over multiple registers.
		 */
		ncr_write32(ctlReg, (NCP_DENALI_CTL_225_5600 + (loop * 0x14)), 0x0ffff);

		ncr_write32(ctlReg, (NCP_DENALI_CTL_226_5600 + (loop * 0x14)), 0x30000);
	}

	/* DENALI_CTL_261 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_261_5600, (ncp_uint32_t *)&reg261);
	reg261.axi0_range_wid_check_bits_id_lookup_15 = 0xf;
	ncr_write32(ctlReg, NCP_DENALI_CTL_261_5600, *((ncp_uint32_t *)&reg261));

	/* DENALI_CTL_262 (0x418) through DENALI_CTL_326 (0x518) */
	for (loop=0; loop < 65; loop++)
	{
		/* Zero'ng out all write-protect stuff */
		ncr_write32(ctlReg, (NCP_DENALI_CTL_262_5600 + (loop * 0x4)), 0x0);
	}

	/* DENALI_CTL_328 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_328_5600, (ncp_uint32_t *)&reg328);
	reg328.wrtprct_enable = parms->wr_protect_en_mask;
	ncr_write32(ctlReg, NCP_DENALI_CTL_328_5600, *((ncp_uint32_t *)&reg328));

	/* DENALI_CTL_329 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_329_5600, (ncp_uint32_t *)&reg329);
	reg329.dll_rst_adj_dly = 0x0;
	reg329.dll_rst_delay = 0x0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_329_5600, *((ncp_uint32_t *)&reg329));

	/* DENALI_CTL_330 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_330_5600, (ncp_uint32_t *)&reg330);
	reg330.tdfi_phy_rdlat = parms->phy_rdlat;
	reg330.dram_clk_disable = ~(parms->topology);
	ncr_write32(ctlReg, NCP_DENALI_CTL_330_5600, *((ncp_uint32_t *)&reg330));

	/* DENALI_CTL_331 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_331_5600, (ncp_uint32_t *)&reg331);
	/*reg331.tdfi_ctrlupd_max = 0x385c;*/
	reg331.tdfi_ctrlupd_max = 2 * ncp_ps_to_clk(parms->tck_ps, ((parms->high_temp_dram == TRUE) ?  3900 : 7800)*1000);
	ncr_write32(ctlReg, NCP_DENALI_CTL_331_5600, *((ncp_uint32_t *)&reg331));

	/* DENALI_CTL_332 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_332_5600, (ncp_uint32_t *)&reg332);
	reg332.tdfi_phyupd_type0 = 0x200;
	reg332.tdfi_phyupd_type1 = 0x200;
	ncr_write32(ctlReg, NCP_DENALI_CTL_332_5600, *((ncp_uint32_t *)&reg332));

	/* DENALI_CTL_333 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_333_5600, (ncp_uint32_t *)&reg333);
	reg333.tdfi_phyupd_type2 = 0x200;
	reg333.tdfi_phyupd_type3 = 0x200;
	ncr_write32(ctlReg, NCP_DENALI_CTL_333_5600, *((ncp_uint32_t *)&reg333));

	/* DENALI_CTL_334 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_334_5600, (ncp_uint32_t *)&reg334);
	/*reg334.tdfi_phyupd_resp = 0x385c;*/
	reg334.tdfi_phyupd_resp = 2 * ncp_ps_to_clk(parms->tck_ps, ((parms->high_temp_dram == TRUE) ?  3900 : 7800)*1000);
	ncr_write32(ctlReg, NCP_DENALI_CTL_334_5600, *((ncp_uint32_t *)&reg334));

	/* DENALI_CTL_335 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_335_5600, (ncp_uint32_t *)&reg335);
	/*reg335.tdfi_ctrlupd_interval = 0x119cc;*/
	reg335.tdfi_ctrlupd_interval = 10 * ncp_ps_to_clk(parms->tck_ps, ((parms->high_temp_dram == TRUE) ?  3900 : 7800)*1000);
	ncr_write32(ctlReg, NCP_DENALI_CTL_335_5600, *((ncp_uint32_t *)&reg335));

	/* DENALI_CTL_336 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_336_5600, (ncp_uint32_t *)&reg336);
	/* Adjustment for PHY read timing */
	/* Should this be cas_lat + additive_lat + ca_parity_lat Check ?? Should minimum be 4 ? */
	reg336.rdlat_adj = ((parms->CAS_latency + parms->additive_latency + reg09.ca_parity_lat - reg19.reg_dimm_enable) - 3);
	/* Adjustment for PHY write timing */
	/* Should this be write_lat + additive_lat + ca_parity_lat Check ?? Should minimum be 1 ? */
	reg336.wrlat_adj = ((parms->CAS_write_latency + parms->additive_latency + reg09.ca_parity_lat - reg19.reg_dimm_enable) - 1);
	reg336.tdfi_ctrl_delay = 0x2;
	reg336.tdfi_dram_clk_disable = 0x2; /* from register_gen TCL */
	ncr_write32(ctlReg, NCP_DENALI_CTL_336_5600, *((ncp_uint32_t *)&reg336));

	/* DENALI_CTL_337 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_337_5600, (ncp_uint32_t *)&reg337);
	reg337.tdfi_dram_clk_enable = 0x1; /* from register_gen; should this be 0x3 ?. */
	reg337.tdfi_wrlvl_en = 0xa;
	reg337.tdfi_wrlvl_ww = 0x1c; /* from register_gen; should this be 0xa ? */
	ncr_write32(ctlReg, NCP_DENALI_CTL_337_5600, *((ncp_uint32_t *)&reg337));

	/* DENALI_CTL_338 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_338_5600, (ncp_uint32_t *)&reg338);
	reg338.tdfi_wrlvl_resp = 0x0; /* from register_gen */
	ncr_write32(ctlReg, NCP_DENALI_CTL_338_5600, *((ncp_uint32_t *)&reg338));

	/* DENALI_CTL_339 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_339_5600, (ncp_uint32_t *)&reg339);
	reg339.tdfi_wrlvl_max = 0x0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_339_5600, *((ncp_uint32_t *)&reg339));

	/* DENALI_CTL_340 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_340_5600, (ncp_uint32_t *)&reg340);
	reg340.tdfi_rdlvl_en = 0xa; /* from reg gen */
	reg340.tdfi_rdlvl_rr = 0xf; /* from reg gen */
	ncr_write32(ctlReg, NCP_DENALI_CTL_340_5600, *((ncp_uint32_t *)&reg340));

	/* DENALI_CTL_341 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_341_5600, (ncp_uint32_t *)&reg341);
	reg341.tdfi_rdlvl_resp = 0x0; /* from reg gen */
	ncr_write32(ctlReg, NCP_DENALI_CTL_341_5600, *((ncp_uint32_t *)&reg341));

	/* DENALI_CTL_342 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_342_5600, (ncp_uint32_t *)&reg342);
	reg342.rdlvl_resp_mask = 0x0; /* from reg gen */
	reg342.rdlvl_en = 0x0; /* controller will never drive data-eye training, the PHY would */
	reg342.rdlvl_gate_en = 0x0;/*would be done by PHY ((parms->packedPHYTrainingOptions >> 10) & 0x1);*/
	ncr_write32(ctlReg, NCP_DENALI_CTL_342_5600, *((ncp_uint32_t *)&reg342));

	/* DENALI_CTL_343 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_343_5600, (ncp_uint32_t *)&reg343);
	reg343.tdfi_rdlvl_max = 0x0; /* from reg gen; should this be tref ?. */
	ncr_write32(ctlReg, NCP_DENALI_CTL_343_5600, *((ncp_uint32_t *)&reg343));

	/* DENALI_CTL_344 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_344_5600, (ncp_uint32_t *)&reg344);
	reg344.rdlvl_interval = parms->rdlvl_interval;
	ncr_write32(ctlReg, NCP_DENALI_CTL_344_5600, *((ncp_uint32_t *)&reg344));

	/* DENALI_CTL_345 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_345_5600, (ncp_uint32_t *)&reg345);
	reg345.rdlvl_gate_interval = parms->rdlvl_gate_interval;
	reg345.tdfi_phy_wrdata = 2;/*(1 + (parms->preamble_support >> 1));*/ /* from reg tcl */
	reg345.tdfi_rdcslat = 0xc; /* cas_latency + additive lat + ca_parity_lat - (preamble_support & 0x1); is this correct ? */
	ncr_write32(ctlReg, NCP_DENALI_CTL_345_5600, *((ncp_uint32_t *)&reg345));

	/* DENALI_CTL_346 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_346_5600, (ncp_uint32_t *)&reg346);
	reg346.tdfi_wrcslat = 0x8; /* wrlat_adj - 6 - (preamble_support >> 1) Should this be the calculation ?. */
	reg346.tdfi_parin_lat = (parms->dram_class == NCP_SM_DDR4_MODE) ? 0x0 : 0x1; /* from reg tcl */
	reg346.pda_invert_dev_cs2 = 0x0; /* only for ddr4 */
	ncr_write32(ctlReg, NCP_DENALI_CTL_346_5600, *((ncp_uint32_t *)&reg346));

	/* CTL_347 pda_invert* all zero's */
	/* Ignore CTL_348 not dealing with low-power stuff */

	/* DENALI_CTL_349 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_349_5600, (ncp_uint32_t *)&reg349);
	reg349.mr0_data_2 = reg78.mr0_data_0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_349_5600, *((ncp_uint32_t *)&reg349));

	/* DENALI_CTL_350 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_350_5600, (ncp_uint32_t *)&reg350);
	if (parms->dram_class == NCP_SM_DDR4_MODE)
	{
		reg350.mr1_data_2 = NCP_SM_ENCODE_RTT_NOM_DDR4(parms->per_smem[smId].sdram_rtt_nom[2]) |
			NCP_SM_ENCODE_DRV_IMP_DDR4(parms->per_smem[smId].sdram_data_drv_imp[2]) |
			(parms->additive_latency << 3);
	}
	else
	{
		reg350.mr1_data_2 = NCP_SM_ENCODE_RTT_NOM_DDR3(parms->per_smem[smId].sdram_rtt_nom[2]) |
			NCP_SM_ENCODE_DRV_IMP_DDR3(parms->per_smem[smId].sdram_data_drv_imp[2]);
	}
	ncr_write32(ctlReg, NCP_DENALI_CTL_350_5600, *((ncp_uint32_t *)&reg350));

	/* DENALI_CTL_351 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_351_5600, (ncp_uint32_t *)&reg351);
	/* data to prog into mem mode reg 2 for cs 0 */
	/* Implementation for MR2 from JEDEC (ddr4) */

	/*
	 * A2:A0 	RFU 0 during MRS
	 * A5:A3	CAS Write Latency
	 * A7:A6	LP ASR 0 = Normal, 1 = Reduced temp, 2 = extended temp, 3 = auto self-refresh
	 * A8		RFU 0 during MRS
	 * A10:A9	RTT_WR
	 * A11		RFU 0 during MRS
	 * A12		write CRC 0 = disable
	 * A13		RFU 0 during MRS	
	 * A17		RFU 0 during MRS	
	 */
	switch (parms->CAS_write_latency)
	{
		/* A5:A4:A3 */
		case 9: 
			tmp = 0x0;
			break;
		case 10: 
			tmp = 0x1;
			break;
		case 11: 
			tmp = 0x2;
			break;
		case 12: 
			tmp = 0x3;
			break;
		case 14: 
			tmp = 0x4;
			break;
		case 16: 
			tmp = 0x5;
			break;
		case 18: 
			tmp = 0x6;
			break;
		default:
			tmp = 0;
	}
	if (parms->dram_class == NCP_SM_DDR4_MODE)
	{
		reg351.mr2_data_2 = (parms->per_smem[smId].sdram_rtt_wr[2] << 9);
		reg351.mr2_data_2 &= ~(0x38);
		reg351.mr2_data_2 |= (tmp << 3);
		if (parms->high_temp_dram == TRUE)
		{
			reg351.mr2_data_2 |= 0x80;
		}
		else
		{
			reg351.mr2_data_2 |= 0x40;
		}
	}
	else
	{
		reg351.mr2_data_2 = ((parms->CAS_write_latency - 5 ) << 3) | (parms->per_smem[smId].sdram_rtt_wr[2] << 9);
		if (parms->high_temp_dram == TRUE)
		{
			reg351.mr2_data_2 |= 0x80;
		}
	}
	ncr_write32(ctlReg, NCP_DENALI_CTL_351_5600, *((ncp_uint32_t *)&reg351));

	/* DENALI_CTL_352 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_352_5600, (ncp_uint32_t *)&reg352);
	reg352.mrsingle_data_2 = reg81.mrsingle_data_0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_352_5600, *((ncp_uint32_t *)&reg352));

	/* DENALI_CTL_353 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_353_5600, (ncp_uint32_t *)&reg353);
	reg353.mr3_data_2 = reg82.mr3_data_0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_353_5600, *((ncp_uint32_t *)&reg353));

	/* DENALI_CTL_354 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_354_5600, (ncp_uint32_t *)&reg354);
	reg354.mr4_data_2 = reg83.mr4_data_0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_354_5600, *((ncp_uint32_t *)&reg354));

	/* DENALI_CTL_355 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_355_5600, (ncp_uint32_t *)&reg355);
	{
		/* data to prog into mem mode reg 5 for cs 0 */
		/* Implementation for MR5 from JEDEC (ddr4) */

		/*
		 * A2:A0	CA parity lat mode 0 = disable
		 * A3		crc error clear 0 = clear
		 * A4		ca parity error status 0 = clear
		 * A5		odt input buffer 0 = activated
		 * A8:A6	rtt_park 0 = disable
		 * A9		ca parity persistent error 0 = disable
		 * A10		data mask 0 = disable
		 * A11		write dbi 0 = disable
		 * A12		read dbi 0 = disable
		 * A13, A17	RFU
		 */
		reg355.mr5_data_2 = NCP_SM_ENCODE_RTT_PARK_DDR4(parms->per_smem[smId].sdram_rtt_park[2]) |
			(0x400 /* enable data mask */) | (parms->dbi_wr_en << 11) | (parms->dbi_rd_en << 12);
	}
	ncr_write32(ctlReg, NCP_DENALI_CTL_355_5600, *((ncp_uint32_t *)&reg355));

	/* DENALI_CTL_356 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_356_5600, (ncp_uint32_t *)&reg356);
	reg356.mr6_data_2 = reg85.mr6_data_0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_356_5600, *((ncp_uint32_t *)&reg356));

	/* DENALI_CTL_357 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_357_5600, (ncp_uint32_t *)&reg357);
	reg357.mr0_data_3 = reg78.mr0_data_0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_357_5600, *((ncp_uint32_t *)&reg357));

	/* DENALI_CTL_358 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_358_5600, (ncp_uint32_t *)&reg358);
	if (parms->dram_class == NCP_SM_DDR4_MODE)
	{
		reg358.mr1_data_3 = NCP_SM_ENCODE_RTT_NOM_DDR4(parms->per_smem[smId].sdram_rtt_nom[3]) |
			NCP_SM_ENCODE_DRV_IMP_DDR4(parms->per_smem[smId].sdram_data_drv_imp[3]) |
			(parms->additive_latency << 3);
	}
	else
	{
		reg358.mr1_data_3 = NCP_SM_ENCODE_RTT_NOM_DDR3(parms->per_smem[smId].sdram_rtt_nom[3]) |
			NCP_SM_ENCODE_DRV_IMP_DDR3(parms->per_smem[smId].sdram_data_drv_imp[3]);
	}
	ncr_write32(ctlReg, NCP_DENALI_CTL_358_5600, *((ncp_uint32_t *)&reg358));

	/* DENALI_CTL_359 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_359_5600, (ncp_uint32_t *)&reg359);
	/* data to prog into mem mode reg 2 for cs 0 */
	/* Implementation for MR2 from JEDEC (ddr4) */

	/*
	 * A2:A0 	RFU 0 during MRS
	 * A5:A3	CAS Write Latency
	 * A7:A6	LP ASR 0 = Normal, 1 = Reduced temp, 2 = extended temp, 3 = auto self-refresh
	 * A8		RFU 0 during MRS
	 * A10:A9	RTT_WR
	 * A11		RFU 0 during MRS
	 * A12		write CRC 0 = disable
	 * A13		RFU 0 during MRS	
	 * A17		RFU 0 during MRS	
	 */
	switch (parms->CAS_write_latency)
	{
		/* A5:A4:A3 */
		case 9: 
			tmp = 0x0;
			break;
		case 10: 
			tmp = 0x1;
			break;
		case 11: 
			tmp = 0x2;
			break;
		case 12: 
			tmp = 0x3;
			break;
		case 14: 
			tmp = 0x4;
			break;
		case 16: 
			tmp = 0x5;
			break;
		case 18: 
			tmp = 0x6;
			break;
		default:
			tmp = 0;
	}
	if (parms->dram_class == NCP_SM_DDR4_MODE)
	{
		reg359.mr2_data_3 = (parms->per_smem[smId].sdram_rtt_wr[3] << 9);
		reg359.mr2_data_3 &= ~(0x38);
		reg359.mr2_data_3 |= (tmp << 3);
		if (parms->high_temp_dram == TRUE)
		{
			reg359.mr2_data_3 |= 0x80;
		}
		else
		{
			reg359.mr2_data_3 |= 0x40;
		}
	}
	else
	{
		reg359.mr2_data_3 = ((parms->CAS_write_latency - 5 ) << 3) | (parms->per_smem[smId].sdram_rtt_wr[3] << 9);
		if (parms->high_temp_dram == TRUE)
		{
			reg359.mr2_data_3 |= 0x80;
		}
	}
	ncr_write32(ctlReg, NCP_DENALI_CTL_359_5600, *((ncp_uint32_t *)&reg359));

	/* DENALI_CTL_360 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_360_5600, (ncp_uint32_t *)&reg360);
	reg360.mrsingle_data_3 = reg81.mrsingle_data_0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_360_5600, *((ncp_uint32_t *)&reg360));

	/* DENALI_CTL_361 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_361_5600, (ncp_uint32_t *)&reg361);
	reg361.mr3_data_3 = reg82.mr3_data_0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_361_5600, *((ncp_uint32_t *)&reg361));

	/* DENALI_CTL_362 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_362_5600, (ncp_uint32_t *)&reg362);
	reg362.mr4_data_3 = reg83.mr4_data_0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_362_5600, *((ncp_uint32_t *)&reg362));

	/* DENALI_CTL_363 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_363_5600, (ncp_uint32_t *)&reg363);
	{
		/* data to prog into mem mode reg 5 for cs 0 */
		/* Implementation for MR5 from JEDEC (ddr4) */

		/*
		 * A2:A0	CA parity lat mode 0 = disable
		 * A3		crc error clear 0 = clear
		 * A4		ca parity error status 0 = clear
		 * A5		odt input buffer 0 = activated
		 * A8:A6	rtt_park 0 = disable
		 * A9		ca parity persistent error 0 = disable
		 * A10		data mask 0 = disable
		 * A11		write dbi 0 = disable
		 * A12		read dbi 0 = disable
		 * A13, A17	RFU
		 */
		reg363.mr5_data_3 = NCP_SM_ENCODE_RTT_PARK_DDR4(parms->per_smem[smId].sdram_rtt_park[3]) |
			(0x400 /* enable data mask */) | (parms->dbi_wr_en << 11) | (parms->dbi_rd_en << 12);
	}
	ncr_write32(ctlReg, NCP_DENALI_CTL_363_5600, *((ncp_uint32_t *)&reg363));

	/* DENALI_CTL_364 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_364_5600, (ncp_uint32_t *)&reg364);
	reg364.mr6_data_3 = reg85.mr6_data_0;
	reg364.memdata_ratio_2 = (parms->sdram_device_width == 1) ? 3 : 2;
	ncr_write32(ctlReg, NCP_DENALI_CTL_364_5600, *((ncp_uint32_t *)&reg364));

	/* DENALI_CTL_365 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_365_5600, (ncp_uint32_t *)&reg365);
	reg365.memdata_ratio_3 = (parms->sdram_device_width == 1) ? 3 : 2;
	ncr_write32(ctlReg, NCP_DENALI_CTL_365_5600, *((ncp_uint32_t *)&reg365));
#if 0
	/* int_status */
	/* DENALI_CTL_368 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_368_5600, (ncp_uint32_t *)&reg368);
	reg368.int_ack = 0xffffffff;  /* clears associated bit in int_status */
	ncr_write32(ctlReg, NCP_DENALI_CTL_368_5600, *((ncp_uint32_t *)&reg368));

	/* DENALI_CTL_369 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_369_5600, (ncp_uint32_t *)&reg369);
	reg369.int_ack = 0x3; /* clears associated bit in int_status */
	ncr_write32(ctlReg, NCP_DENALI_CTL_369_5600, *((ncp_uint32_t *)&reg369));
#endif

	/* int_mask */
	/* DENALI_CTL_370 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_370_5600, (ncp_uint32_t *)&reg370);
	reg370.int_mask = 0x0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_370_5600, *((ncp_uint32_t *)&reg370));

	/* DENALI_CTL_371 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_371_5600, (ncp_uint32_t *)&reg371);
	reg371.int_mask = 0x0;
	reg371.odt_rd_map_cs2 = rd_ODT[2];
	reg371.odt_wr_map_cs2 = wr_ODT[2];
	reg371.odt_rd_map_cs3 = rd_ODT[3];
	ncr_write32(ctlReg, NCP_DENALI_CTL_371_5600, *((ncp_uint32_t *)&reg371));

	/* DENALI_CTL_372 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_372_5600, (ncp_uint32_t *)&reg372);
	reg372.odt_wr_map_cs3 = wr_ODT[3];
	ncr_write32(ctlReg, NCP_DENALI_CTL_372_5600, *((ncp_uint32_t *)&reg372));

	if (parms->dram_class == NCP_SM_DDR4_MODE)
	{
		/* DENALI_CTL_372 */
		ncr_read32(ctlReg, NCP_DENALI_CTL_372_5600, (ncp_uint32_t *)&reg372);
		reg372.vref_val_dev0_2 = parms->vref_val;
		reg372.vref_val_dev0_3 = parms->vref_val;
		reg372.vref_val_dev1_2 = parms->vref_val;
		ncr_write32(ctlReg, NCP_DENALI_CTL_372_5600, *((ncp_uint32_t *)&reg372));

		/* defines the range and value for vref training - 0x67 set to ~70%
		 * It is 7 bits, b[6] is range, whereas b[5:0] is the actual vref value
		 * there is setting for each DRAM for each chip-select */

		/* set vref_val in sm_parms to 0x67 */

		/* DENALI_CTL_373 */
		ncr_read32(ctlReg, NCP_DENALI_CTL_373_5600, (ncp_uint32_t *)&reg373);
		reg373.vref_val_dev1_3 = parms->vref_val;
		reg373.vref_val_dev2_2 = parms->vref_val;
		reg373.vref_val_dev2_3 = parms->vref_val;
		reg373.vref_val_dev3_2 = parms->vref_val;
		ncr_write32(ctlReg, NCP_DENALI_CTL_373_5600, *((ncp_uint32_t *)&reg373));

		/* DENALI_CTL_374 */
		ncr_read32(ctlReg, NCP_DENALI_CTL_374_5600, (ncp_uint32_t *)&reg374);
		reg374.vref_val_dev3_3 = parms->vref_val;
		reg374.vref_val_dev4_2 = parms->vref_val;
		reg374.vref_val_dev4_3 = parms->vref_val;
		reg374.vref_val_dev5_2 = parms->vref_val;
		ncr_write32(ctlReg, NCP_DENALI_CTL_374_5600, *((ncp_uint32_t *)&reg374));

		/* DENALI_CTL_375 */
		ncr_read32(ctlReg, NCP_DENALI_CTL_375_5600, (ncp_uint32_t *)&reg375);
		reg375.vref_val_dev5_3 = parms->vref_val;
		reg375.vref_val_dev6_2 = parms->vref_val;
		reg375.vref_val_dev6_3 = parms->vref_val;
		reg375.vref_val_dev7_2 = parms->vref_val;
		ncr_write32(ctlReg, NCP_DENALI_CTL_375_5600, *((ncp_uint32_t *)&reg375));

		/* DENALI_CTL_376 */
		ncr_read32(ctlReg, NCP_DENALI_CTL_376_5600, (ncp_uint32_t *)&reg376);
		reg376.vref_val_dev7_3 = parms->vref_val;
		reg376.vref_val_dev8_2 = parms->vref_val;
		reg376.vref_val_dev8_3 = parms->vref_val;
		reg376.vref_val_dev9_2 = parms->vref_val;
		ncr_write32(ctlReg, NCP_DENALI_CTL_376_5600, *((ncp_uint32_t *)&reg376));

		/* DENALI_CTL_377 */
		ncr_read32(ctlReg, NCP_DENALI_CTL_377_5600, (ncp_uint32_t *)&reg377);
		reg377.vref_val_dev9_3 = parms->vref_val;
		reg377.vref_val_dev10_2 = parms->vref_val;
		reg377.vref_val_dev10_3 = parms->vref_val;
		reg377.vref_val_dev11_2 = parms->vref_val;
		ncr_write32(ctlReg, NCP_DENALI_CTL_377_5600, *((ncp_uint32_t *)&reg377));

		/* DENALI_CTL_378 */
		ncr_read32(ctlReg, NCP_DENALI_CTL_378_5600, (ncp_uint32_t *)&reg378);
		reg378.vref_val_dev11_3 = parms->vref_val;
		reg378.vref_val_dev12_2 = parms->vref_val;
		reg378.vref_val_dev12_3 = parms->vref_val;
		reg378.vref_val_dev13_2 = parms->vref_val;
		ncr_write32(ctlReg, NCP_DENALI_CTL_378_5600, *((ncp_uint32_t *)&reg378));

		/* DENALI_CTL_379 */
		ncr_read32(ctlReg, NCP_DENALI_CTL_379_5600, (ncp_uint32_t *)&reg379);
		reg379.vref_val_dev13_3 = parms->vref_val;
		reg379.vref_val_dev14_2 = parms->vref_val;
		reg379.vref_val_dev14_3 = parms->vref_val;
		reg379.vref_val_dev15_2 = parms->vref_val;
		ncr_write32(ctlReg, NCP_DENALI_CTL_379_5600, *((ncp_uint32_t *)&reg379));

		/* DENALI_CTL_380 */
		ncr_read32(ctlReg, NCP_DENALI_CTL_380_5600, (ncp_uint32_t *)&reg380);
		reg380.vref_val_dev15_3 = parms->vref_val;
		reg380.vref_val_ecc_dev0_2 = parms->vref_val;
		reg380.vref_val_ecc_dev0_3 = parms->vref_val;
		reg380.vref_val_ecc_dev1_2 = parms->vref_val;
		ncr_write32(ctlReg, NCP_DENALI_CTL_380_5600, *((ncp_uint32_t *)&reg380));

		/* DENALI_CTL_381 */
		ncr_read32(ctlReg, NCP_DENALI_CTL_381_5600, (ncp_uint32_t *)&reg381);
		reg381.vref_val_ecc_dev1_3 = parms->vref_val;
		ncr_write32(ctlReg, NCP_DENALI_CTL_381_5600, *((ncp_uint32_t *)&reg381));
	}

	/* DENALI_CTL_386 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_386_5600, (ncp_uint32_t *)&reg386);
	reg386.crc_mode = parms->crc_mode;
	ncr_write32(ctlReg, NCP_DENALI_CTL_386_5600, *((ncp_uint32_t *)&reg386));

	/* DENALI_CTL_387 (0x60c) through DENALI_CTL_391 (0x61c) */
	for (loop=0; loop < 5; loop++)
	{
		value = 0;
		if (loop == 4)
		{
			value |= (parms->dq_map_0[16] | (parms->dq_map_0[17] << 8));
			ncr_write32(ctlReg, (NCP_DENALI_CTL_387_5600 + (loop * 0x4)),
					(((parms->dq_map_odd_rank_swap_0 & 0xf) << 16) | value));
		}
		else
		{
			for (i=0; i < 4; i++)
			{
				value |= (parms->dq_map_0[i + (loop * 4)] << (8 * i));
			}
			ncr_write32(ctlReg, (NCP_DENALI_CTL_387_5600 + (loop * 0x4)), value);
		}
	}

	/* DENALI_CTL_392 (0x620) through DENALI_CTL_396 (0x630) */
	for (loop=0; loop < 5; loop++)
	{
		value = 0;
		if (loop == 4)
		{
			value |= (parms->dq_map_1[16] | (parms->dq_map_1[17] << 8));
			ncr_write32(ctlReg, (NCP_DENALI_CTL_392_5600 + (loop * 0x4)), 
					(((parms->dq_map_odd_rank_swap_1 & 0xf) << 16) | value));
		}
		else
		{
			for (i=0; i < 4; i++)
			{
				value |= (parms->dq_map_1[i + (loop * 4)] << (8 * i));
			}
			ncr_write32(ctlReg, (NCP_DENALI_CTL_392_5600 + (loop * 0x4)), value);
		}
	}
#if 0
	/* start MC init operation */
	ncr_read32(ctlReg, NCP_DENALI_CTL_00_5600, (ncp_uint32_t *)&reg00);
	reg00.start = 0x1;
	ncr_write32(ctlReg, NCP_DENALI_CTL_00_5600, *((ncp_uint32_t *)&reg00));

	/* poll for memory init operation bit-8 */
	ncpStatus = (ncr_poll(ctlReg, NCP_DENALI_CTL_366_5600,  0x0100,  0x0100,  1000000,  10000));

	if (ncpStatus == NCP_ST_POLL_TIMEOUT)
	{
		errprintf("POLL timeout while waiting for MC init to complete [line:%d]\n",__LINE__);
	}

	/* poll for DFI init complete operation bit-30 */
	ncpStatus = (ncr_poll(ctlReg, NCP_DENALI_CTL_366_5600,  0x40000000,  0x40000000,  1000000,  10000));

	if (ncpStatus == NCP_ST_POLL_TIMEOUT)
	{
		errprintf("POLL timeout while waiting for DFI init to complete [line:%d]\n",__LINE__);
	}
#endif

	/* Clear all interrupts */
	/* DENALI_CTL_368 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_368_5600, (ncp_uint32_t *)&reg368);
	reg368.int_ack = 0xffffffff;  /* clears associated bit in int_status */
	ncr_write32(ctlReg, NCP_DENALI_CTL_368_5600, *((ncp_uint32_t *)&reg368));

	/* DENALI_CTL_369 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_369_5600, (ncp_uint32_t *)&reg369);
	reg369.int_ack = 0x3; /* clears associated bit in int_status */
	ncr_write32(ctlReg, NCP_DENALI_CTL_369_5600, *((ncp_uint32_t *)&reg369));

	NCP_RETURN_LABEL
		return ncpStatus;
}

ncp_uint32_t
ncp_ps_to_clk(
		ncp_uint32_t tck_ps,
		ncp_uint32_t num_ps)
{
	/*return ((num_ps * clk_in_mhz)/1000000);*/
	return (((num_ps) / (tck_ps)) + (((num_ps) % (tck_ps)) > 0 ? 1 : 0));
}
