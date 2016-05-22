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
#include "ncp_treemem_synopphy.h"
#else
#include "ncp.h"
#include "ncp_pvt.h"
#include "ncp_sysmem_ext.h"
#include "ncp_sysmem_lsiphy.h" /* for macros and stuff mainly */
#include "ncp_sysmem_synopphy.h"
#include "ncp_treemem_synopphy.h"
#endif

extern ncp_uint16_t ddr3refresh_parms_by_density[7]; /* see ncp_sm_denali_2041_init_56xx.c */
extern ncp_uint32_t ddr4refresh_parms_by_density_1x[7]; /* ditto */
extern ncp_uint32_t ddr4refresh_parms_by_density_2x[7]; /* ditto */
extern ncp_uint32_t ddr4refresh_parms_by_density_4x[7]; /* ditto */

ncp_st_t
ncp_cm_denali_init_56xx(
		ncp_dev_hdl_t   dev,
		ncp_uint32_t    cmNode,
		ncp_sm_parms_t *parms,
		ncp_common_timing_parameters_t *ctm)
{
	ncp_st_t   ncpStatus = NCP_ST_SUCCESS;

	ncp_uint8_t i = 0;
	ncp_uint8_t rd_ODT[4];
	ncp_uint8_t wr_ODT[4];
	ncp_uint32_t value=0;
	ncp_uint32_t value2=0;

	/*ncp_region_id_t     axiRegion;*/
	ncp_region_id_t     ddrRegion;
	/*ncp_region_id_t     phyRegion;*/
	ncp_region_id_t     cmemCfgRegion;
	/*ncp_region_id_t     cfgRegion;*/

	ncp_memory_controller_DENALI_CTL_00_t reg00 = {0};
	ncp_memory_controller_DENALI_CTL_01_t reg01 = {0};
	ncp_memory_controller_DENALI_CTL_05_t reg05 = {0};
	ncp_memory_controller_DENALI_CTL_06_t reg06 = {0};
	ncp_memory_controller_DENALI_CTL_07_t reg07 = {0};
	ncp_memory_controller_DENALI_CTL_08_t reg08 = {0};
	ncp_memory_controller_DENALI_CTL_09_t reg09 = {0};
	ncp_memory_controller_DENALI_CTL_10_t reg10 = {0};
	ncp_memory_controller_DENALI_CTL_11_t reg11 = {0};
	ncp_memory_controller_DENALI_CTL_12_t reg12 = {0};
	ncp_memory_controller_DENALI_CTL_13_t reg13 = {0};
	ncp_memory_controller_DENALI_CTL_14_t reg14 = {0};
	ncp_memory_controller_DENALI_CTL_15_t reg15 = {0};
	ncp_memory_controller_DENALI_CTL_16_t reg16 = {0};
	ncp_memory_controller_DENALI_CTL_17_t reg17 = {0};
	ncp_memory_controller_DENALI_CTL_18_t reg18 = {0};
	ncp_memory_controller_DENALI_CTL_19_t reg19 = {0};
	ncp_memory_controller_DENALI_CTL_22_t reg22 = {0};
	ncp_memory_controller_DENALI_CTL_23_t reg23 = {0};
	ncp_memory_controller_DENALI_CTL_24_t reg24 = {0};
	ncp_memory_controller_DENALI_CTL_25_t reg25 = {0};
	ncp_memory_controller_DENALI_CTL_26_t reg26 = {0};
	ncp_memory_controller_DENALI_CTL_27_t reg27 = {0};
	ncp_memory_controller_DENALI_CTL_28_t reg28 = {0};
	ncp_memory_controller_DENALI_CTL_29_t reg29 = {0};
	ncp_memory_controller_DENALI_CTL_31_t reg31 = {0};
	ncp_memory_controller_DENALI_CTL_42_t reg42 = {0};
	ncp_memory_controller_DENALI_CTL_43_t reg43 = {0};
	ncp_memory_controller_DENALI_CTL_44_t reg44 = {0};
	ncp_memory_controller_DENALI_CTL_46_t reg46 = {0};
	ncp_memory_controller_DENALI_CTL_47_t reg47 = {0};
	ncp_memory_controller_DENALI_CTL_48_t reg48 = {0};
	ncp_memory_controller_DENALI_CTL_49_t reg49 = {0};
	ncp_memory_controller_DENALI_CTL_50_t reg50 = {0};
	ncp_memory_controller_DENALI_CTL_51_t reg51 = {0};
	ncp_memory_controller_DENALI_CTL_52_t reg52 = {0};
	ncp_memory_controller_DENALI_CTL_54_t reg54 = {0};
	ncp_memory_controller_DENALI_CTL_55_t reg55 = {0};
	ncp_memory_controller_DENALI_CTL_56_t reg56 = {0};
	ncp_memory_controller_DENALI_CTL_57_t reg57 = {0};
	ncp_memory_controller_DENALI_CTL_58_t reg58 = {0};
	ncp_memory_controller_DENALI_CTL_62_t reg62 = {0};
	ncp_memory_controller_DENALI_CTL_71_t reg71 = {0};
	ncp_memory_controller_DENALI_CTL_72_t reg72 = {0};
	ncp_memory_controller_DENALI_CTL_73_t reg73 = {0};
	ncp_memory_controller_DENALI_CTL_74_t reg74 = {0};
	ncp_memory_controller_DENALI_CTL_75_t reg75 = {0};
	ncp_memory_controller_DENALI_CTL_76_t reg76 = {0};
	ncp_memory_controller_DENALI_CTL_77_t reg77 = {0};
	ncp_memory_controller_DENALI_CTL_78_t reg78 = {0};
	ncp_memory_controller_DENALI_CTL_79_t reg79 = {0};
	ncp_memory_controller_DENALI_CTL_80_t reg80 = {0};
	ncp_memory_controller_DENALI_CTL_81_t reg81 = {0};
	ncp_memory_controller_DENALI_CTL_82_t reg82 = {0};
	ncp_memory_controller_DENALI_CTL_83_t reg83 = {0};
	ncp_memory_controller_DENALI_CTL_85_t reg85 = {0};
	ncp_memory_controller_DENALI_CTL_96_t reg96 = {0};
	ncp_memory_controller_DENALI_CTL_97_t reg97 = {0};
	ncp_memory_controller_DENALI_CTL_98_t reg98 = {0};
	ncp_memory_controller_DENALI_CTL_99_t reg99 = {0};
	ncp_memory_controller_DENALI_CTL_100_t reg100 = {0};
	ncp_memory_controller_DENALI_CTL_103_t reg103 = {0};
	ncp_memory_controller_DENALI_CTL_104_t reg104 = {0};
	ncp_memory_controller_DENALI_CTL_105_t reg105 = {0};
	ncp_memory_controller_DENALI_CTL_106_t reg106 = {0};
	ncp_memory_controller_DENALI_CTL_115_t reg115 = {0};
	ncp_memory_controller_DENALI_CTL_116_t reg116 = {0};
	ncp_memory_controller_DENALI_CTL_117_t reg117 = {0};
	ncp_memory_controller_DENALI_CTL_118_t reg118 = {0};
	ncp_memory_controller_DENALI_CTL_119_t reg119 = {0};
	ncp_memory_controller_DENALI_CTL_120_t reg120 = {0};
	ncp_memory_controller_DENALI_CTL_121_t reg121 = {0};
	ncp_memory_controller_DENALI_CTL_122_t reg122 = {0};
	ncp_memory_controller_DENALI_CTL_124_t reg124 = {0};
	ncp_memory_controller_DENALI_CTL_125_t reg125 = {0};
	ncp_memory_controller_DENALI_CTL_126_t reg126 = {0};
	ncp_memory_controller_DENALI_CTL_127_t reg127 = {0};
	ncp_memory_controller_DENALI_CTL_128_t reg128 = {0};
	ncp_memory_controller_DENALI_CTL_129_t reg129 = {0};
	ncp_memory_controller_DENALI_CTL_130_t reg130 = {0};
	ncp_memory_controller_DENALI_CTL_131_t reg131 = {0};
	ncp_memory_controller_DENALI_CTL_134_t reg134 = {0};
	ncp_memory_controller_DENALI_CTL_139_t reg139 = {0};
	ncp_memory_controller_DENALI_CTL_140_t reg140 = {0};
	ncp_memory_controller_DENALI_CTL_143_t reg143 = {0};
	ncp_memory_controller_DENALI_CTL_144_t reg144 = {0};

	ncp_cmem_cfg_ddr_cfg_r_t ddrCfg = {0};
	ncp_cmem_cfg_ddr_ctl_r_t ddrCtl = {0};
	ncp_uint32_t cmId = 0;
	ncp_uint32_t tmp = 0;
	ncp_uint32_t tmp1=0;

	/* this below is only for sm_parms's per_smem[n] access */
	switch (cmNode) {
		case 0x8:
			cmId  = 0x0;	/* X9/XLF */
			break;
		case 0x9:
			cmId  = 0x1;	/* X9 */
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

	/*axiRegion = NCP_REGION_ID(cmNode, 0x08);*/ /* monitor */
	ddrRegion = NCP_REGION_ID(cmNode, 0x09); /* memory_controller */
	/*phyRegion = NCP_REGION_ID(cmNode, 0x0a);*/
	cmemCfgRegion = NCP_REGION_ID(cmNode, 0x0b); /* cmem_cfg */
	/*cfgRegion = NCP_REGION_ID(cmNode, 0xff);*/ /* cfg_node */

	NCP_COMMENT("## Begin CMEM%d config", cmNode);

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_00, (ncp_uint32_t *)&reg00);
	reg00.dram_class = parms->dram_class; /* ddr3=6, ddr4=10 */
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_00, *((ncp_uint32_t *)&reg00));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_74, (ncp_uint32_t *)&reg74);
	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_75, (ncp_uint32_t *)&reg75);

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_01, (ncp_uint32_t *)&reg01);
	if (parms->dram_class == NCP_SM_DDR4_MODE)
	{
		switch(parms->sdram_device_density)
		{
			case 3:
				reg74.row_diff = reg01.max_row_reg - 14; /* A0-A13 */
				break;
			case 4:
				reg74.row_diff = reg01.max_row_reg - 15; /* A0-A14 */
				break;
			case 5:
				reg74.row_diff = reg01.max_row_reg - 16; /* A0-A15 */
				break;
			case 6:
				reg74.row_diff = reg01.max_row_reg - 17; /* A0-A16 */
				break;
			default:
				errprintf("invalid sdram_device_density\n");
				NCP_CALL(NCP_ST_ERROR);
		}
		reg75.col_diff = reg01.max_col_reg - 10; /* A0-A9 always */
	}
	else
	{
		if (parms->sdram_device_density == NCP_SM_SDRAM_DENSITY_8GBIT) {
			reg74.row_diff = reg01.max_row_reg - 16;
			reg75.col_diff = reg01.max_col_reg + parms->sdram_device_width - 12;
		}
		else 
		{
			reg74.row_diff = reg01.max_row_reg + parms->sdram_device_width - parms->sdram_device_density - 13;
			reg75.col_diff = reg01.max_col_reg - 10;
		}
	}

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_05, (ncp_uint32_t *)&reg05);
	/* dram initialization delay in memory clocks
	 * For DDR3= 700us + 10ns + tXPR + (3*tMRD) + tMOD + tZQinit
	 * For DDR4= 700us + tXPR + (3*tMRD) + tMOD + tZQinit
	 * choosing 701us upper bound */
	reg05.tinit = ncp_ps_to_clk(parms->tck_ps,701*(1000000));
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_05, *((ncp_uint32_t *)&reg05));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_06, (ncp_uint32_t *)&reg06);
	/* number of clocks that memory will be held in reset during init seq
	 * assuming 200us is sufficient */
	reg06.trst_pwron = ncp_ps_to_clk(parms->tck_ps,200*(1000000));
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_06, *((ncp_uint32_t *)&reg06));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_07, (ncp_uint32_t *)&reg07);
	/* number of clocks after reset before cke will become active
	 * assuming 500us is sufficient */
	reg07.cke_inactive = ncp_ps_to_clk(parms->tck_ps,500*(1000000));
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_07, *((ncp_uint32_t *)&reg07));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_08, (ncp_uint32_t *)&reg08);
	reg08.tdll = 0x300;/*0x255;*/
	reg08.caslat_lin = parms->CAS_latency * 2; /* CAS latency linear value */
	reg08.wrlat = parms->CAS_write_latency;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_08, *((ncp_uint32_t *)&reg08));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_09, (ncp_uint32_t *)&reg09);
	if (parms->dram_class == NCP_SM_DDR4_MODE)
	{
		if (parms->ddrClockSpeedMHz <= 300)
			reg09.ca_parity_lat = 0;
		else if (parms->ddrClockSpeedMHz <= 1067)
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
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_09, *((ncp_uint32_t *)&reg09));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_10, (ncp_uint32_t *)&reg10);
	reg10.tparity_error_cmd_inhibit = 0x0;
	reg10.tbst_int_interval = 0x4;
	reg10.tccd = (parms->dram_class == NCP_SM_DDR4_MODE) ? ctm->tCCD_S : 0x4; 
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_10, *((ncp_uint32_t *)&reg10));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_11, (ncp_uint32_t *)&reg11);
	reg11.trc = ctm->tRC;
	reg11.trrd_l = (parms->dram_class == NCP_SM_DDR4_MODE) ? ctm->tRRD_L : 0x0;
	reg11.trrd = (parms->dram_class == NCP_SM_DDR4_MODE) ? ctm->tRRD_S : ctm->tRRD;
	reg11.tccd_l = (parms->dram_class == NCP_SM_DDR4_MODE) ? ctm->tCCD_L : 0x0;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_11, *((ncp_uint32_t *)&reg11));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_12, (ncp_uint32_t *)&reg12);
	reg12.trp = ctm->tRP;
	reg12.twtr_l = (parms->dram_class == NCP_SM_DDR4_MODE) ? ctm->tWTR_L : 0x0;
	reg12.twtr = ncp_ps_to_clk(parms->tck_ps,2500);
	reg12.tras_min = ctm->tRAS;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_12, *((ncp_uint32_t *)&reg12));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_13, (ncp_uint32_t *)&reg13);
	reg13.tmrd = 8;
	reg13.trtp_ap = ctm->tRTP;/*4;*/ /* for auto-precharge get from speedbin_ddr4 */
	/*reg13.trtp = (parms->dram_class == NCP_SM_DDR4_MODE) ? ctm->tRTP : ncp_ps_to_clk(parms->tck_ps,7500);*/
	reg13.trtp = ncp_ps_to_clk(parms->tck_ps,7500);
	reg13.tfaw = ctm->tFAW;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_13, *((ncp_uint32_t *)&reg13));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_14, (ncp_uint32_t *)&reg14);
	reg14.tmod = (parms->dram_class == NCP_SM_DDR4_MODE) ? ctm->tMOD : ncp_ps_to_clk(parms->tck_ps,15000);
	/* tRAS_max = (9 * tREFI) */
	reg14.tras_max = 9*(ncp_ps_to_clk(parms->tck_ps, ((parms->high_temp_dram == TRUE) ?  3900000 : 7800000)));
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_14, *((ncp_uint32_t *)&reg14));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_15, (ncp_uint32_t *)&reg15);
	/*reg15.tcke = ctm->tCKE;*/
	reg15.tcke = ncp_ps_to_clk(parms->tck_ps,5000);
	reg15.tckesr = reg15.tcke + 1; /* tCKE + 1nCK */
	reg15.twr_mpr = (parms->dram_class == NCP_SM_DDR4_MODE) ? ctm->tWR_MPR : 0x0;
	reg15.writeinterp = 0; /* for both ddr3, ddr4 */
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_15, *((ncp_uint32_t *)&reg15));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_16, (ncp_uint32_t *)&reg16);
	reg16.trcd = ctm->tRCD;
	reg16.twr = (parms->dram_class == NCP_SM_DDR4_MODE) ? ctm->tWR : ncp_ps_to_clk(parms->tck_ps,15000);
	reg16.tvref = (parms->dram_class == NCP_SM_DDR4_MODE) ? ncp_ps_to_clk(parms->tck_ps, 150000) : 0x0;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_16, *((ncp_uint32_t *)&reg16));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_17, (ncp_uint32_t *)&reg17);
	reg17.tmrd_pda = (parms->dram_class == NCP_SM_DDR4_MODE) ? ctm->tMRD_PDA : 0x0;
	reg17.tmprr = (parms->dram_class == NCP_SM_DDR4_MODE) ? ctm->tMPRR : 0x0;
	reg17.ap = (parms->dramPrechargePolicy == 0) ? 1 : 0;
	reg17.concurrentap = (parms->dramPrechargePolicy == 0) ? 1 : 0;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_17, *((ncp_uint32_t *)&reg17));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_18, (ncp_uint32_t *)&reg18);
	reg18.tras_lockout = 1;
	reg18.tdal = (parms->dram_class == NCP_SM_DDR4_MODE) ? (ctm->tWR + ctm->tRP) 
		: ( ncp_ps_to_clk(parms->tck_ps,15000) + ctm->tRP); /* tWR + roundup(tRP/tCK) */
	reg18.bstlen = parms->bstlen;/* 1 for BL2, 2 for BL4, 3 for BL8 */
	reg18.trp_ab = parms->CAS_latency;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_18, *((ncp_uint32_t *)&reg18));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_19, (ncp_uint32_t *)&reg19);
	reg19.reg_dimm_enable = (parms->rdimm_misc & 0x1);
	/* For mirroring, 0 means std. pinout, 1 means mirrored wiring */
	reg19.address_mirroring = (parms->address_mirroring) ? 0xa : 0x0; /* bit 0 for cs0 ....3 for cs3 */
	reg19.optimal_rmodw_en = 0x1;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_19, *((ncp_uint32_t *)&reg19));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_22, (ncp_uint32_t *)&reg22);
	reg22.ca_parity_error = 0x0;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_22, *((ncp_uint32_t *)&reg22));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_23, (ncp_uint32_t *)&reg23);
	reg23.sref_entry_wait_enable = 0x0;
	/* initiate auto refresh at end of current burst boundary */
	reg23.arefresh = 0x0;
	/* enables refresh commands */
	reg23.tref_enable = 0x1;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_23, *((ncp_uint32_t *)&reg23));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_24, (ncp_uint32_t *)&reg24);
	reg24.trfc = (parms->dram_class == NCP_SM_DDR4_MODE) ? ctm->tRFC : ncp_ps_to_clk(parms->tck_ps,ddr3refresh_parms_by_density[parms->sdram_device_density]);
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_24, *((ncp_uint32_t *)&reg24));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_25, (ncp_uint32_t *)&reg25);
	reg25.tref = ncp_ps_to_clk(parms->tck_ps, ((parms->high_temp_dram == TRUE) ?  3900000 : 7800000));
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_25, *((ncp_uint32_t *)&reg25));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_26, (ncp_uint32_t *)&reg26);
	reg26.tpdex = (parms->ddrClockSpeedMHz < 1066) ? 0x6 : 0x7;
	reg26.txpdll = (parms->ddrClockSpeedMHz < 1066) ? 0x17 : 0x1a;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_26, *((ncp_uint32_t *)&reg26));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_27, (ncp_uint32_t *)&reg27);
	reg27.txsr = 0x200;
	reg27.txsnr = (parms->dram_class == NCP_SM_DDR4_MODE) ? ctm->tXS : ncp_ps_to_clk(parms->tck_ps,(ddr3refresh_parms_by_density[parms->sdram_device_density] + 10000));
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_27, *((ncp_uint32_t *)&reg27));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_28, (ncp_uint32_t *)&reg28);
	reg28.pwrup_srefresh_exit = (parms->ddrRecovery == TRUE) ? 1 : 0;
	reg28.srefresh_exit_no_refresh = 0x0;
	reg28.enable_quick_srefresh = 0x1;
	reg28.cke_delay = 3; /* or 0 */
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_28, *((ncp_uint32_t *)&reg28));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_29, (ncp_uint32_t *)&reg29);
	reg29.lowpower_refresh_enable = 0x0;
	reg29.cksre = (parms->ddrClockSpeedMHz < 1066) ? 0xa : 0xb;;
	reg29.cksrx = (parms->ddrClockSpeedMHz < 1066) ? 0xa : 0xb;;
	reg29.lp_cmd = 0x0;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_29, *((ncp_uint32_t *)&reg29));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_31, (ncp_uint32_t *)&reg31);
	reg31.lp_auto_mem_gate_en = 0x0;
	reg31.lp_auto_pd_idle = 0xfff;
	reg31.lp_auto_sr_idle = 0x0;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_31, *((ncp_uint32_t *)&reg31));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_42, (ncp_uint32_t *)&reg42);
	reg42.mprr_data_3 = 0x0;
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


	reg42.mr0_data_0 = (((parms->dram_class == NCP_SM_DDR4_MODE) ? tmp1 : ncp_ps_to_clk(parms->tck_ps,15000)) << 9);
	reg42.mr0_data_0 &= ~(0x7c);
	reg42.mr0_data_0 |= (tmp << 2);
	ctm->mr0 = reg42.mr0_data_0;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_42, *((ncp_uint32_t *)&reg42));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_43, (ncp_uint32_t *)&reg43);
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
		reg43.mr1_data_0 = NCP_SM_ENCODE_RTT_NOM_DDR4(parms->per_smem[cmId].sdram_rtt_nom[0]) |
			NCP_SM_ENCODE_DRV_IMP_DDR4(parms->per_smem[cmId].sdram_data_drv_imp[0]) |
			(parms->additive_latency << 3) | (0x1 /*DLLenable*/);
	}
	else
	{
		reg43.mr1_data_0 = NCP_SM_ENCODE_RTT_NOM_DDR3(parms->per_smem[cmId].sdram_rtt_nom[0]) |
			NCP_SM_ENCODE_DRV_IMP_DDR3(parms->per_smem[cmId].sdram_data_drv_imp[0]) | 
			(0x1 /*DLLenable*/);
	}
	ctm->mr1 = reg43.mr1_data_0;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_43, *((ncp_uint32_t *)&reg43));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_44, (ncp_uint32_t *)&reg44);
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
	if (parms->dram_class == NCP_SM_DDR4_MODE)
	{
		switch (parms->CAS_write_latency)
		{
			case 9:
				tmp = 0;
				break;
			case 10:
				tmp = 1;
				break;
			case 11:
				tmp = 2;
				break;
			case 12:
				tmp = 3;
				break;
			case 14:
				tmp = 4;
				break;
			case 16:
				tmp = 5;
				break;
			case 18:
				tmp = 6;
				break;
			default:
				tmp = 0;
				;
		}
		reg44.mr2_data_0 = (parms->per_smem[cmId].sdram_rtt_wr[0] << 9);
		reg44.mr2_data_0 &= ~(0x38);
		reg44.mr2_data_0 |= (tmp << 3);
		if (parms->high_temp_dram == TRUE)
		{
			reg44.mr2_data_0 |= 0x80;
		}
		else
		{
			reg44.mr2_data_0 |= 0x40;
		}
	}
	else
	{
		reg44.mr2_data_0 = ((parms->CAS_write_latency - 5 ) << 3) | (parms->per_smem[cmId].sdram_rtt_wr[0] << 9);
		if (parms->high_temp_dram == TRUE)
		{
			reg44.mr2_data_0 |= 0x80;
		}
	}
	ctm->mr2 = reg44.mr2_data_0;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_44, *((ncp_uint32_t *)&reg44));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_46, (ncp_uint32_t *)&reg46);
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
			/* check */
			if ((parms->CAS_latency == 16) ||
					(parms->CAS_latency == 18) ||
					(parms->CAS_latency == 14))
			{
				tmp = 1;
			}
			else
			{
				tmp = 0;
			}
			reg46.mr3_data_0 = (tmp << 9) | (parms->refresh_mode << 6);
		}
		else
		{
			reg46.mr3_data_0 = 0;
		}
	}
	ctm->mr3 = reg46.mr3_data_0;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_46, *((ncp_uint32_t *)&reg46));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_47, (ncp_uint32_t *)&reg47);
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
			reg47.mr4_data_0 |= 0x4;
		}
	}
	ctm->mr4 = reg47.mr4_data_0;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_47, *((ncp_uint32_t *)&reg47));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_48, (ncp_uint32_t *)&reg48);
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
		reg48.mr5_data_0 = NCP_SM_ENCODE_RTT_PARK_DDR4(parms->per_smem[cmId].sdram_rtt_park[0]) |
			(0x400 /* enable data mask */) | (parms->dbi_wr_en << 11) | (parms->dbi_rd_en << 12);
	}
	ctm->mr5 = reg48.mr5_data_0;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_48, *((ncp_uint32_t *)&reg48));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_49, (ncp_uint32_t *)&reg49);
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
#if 0
		/* Override tCCD_L originally from speedBin in ctm using below algo */
		if( (parms->CAS_latency==10) && (parms->CAS_write_latency==9) )
		{
			ctm->tCCD_L = 0x0;
		}
		else if((parms->CAS_latency==12) && ( (parms->CAS_write_latency==9) || (parms->CAS_write_latency==11) ))
		{
			ctm->tCCD_L = 0x1;
		}
		else if((parms->CAS_latency==14) && ( (parms->CAS_write_latency==10) || (parms->CAS_write_latency==12) ))
		{
			ctm->tCCD_L = 0x1;
		}
		else if((parms->CAS_latency==16) && ( (parms->CAS_write_latency==11) || (parms->CAS_write_latency==14) ))
		{
			ctm->tCCD_L = 0x2;
		}
		else if((parms->CAS_latency==18) && ( (parms->CAS_write_latency==12) || (parms->CAS_write_latency==16) ))
		{
			ctm->tCCD_L = 0x2;
		}
		reg49.mr6_data_0 = ((parms->dram_class == NCP_SM_DDR4_MODE) ? (ctm->tCCD_L << 10) : 0x0) | 0x18;
#else
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
		reg49.mr6_data_0 = 0x18;
		reg49.mr6_data_0 &= ~(0x1c00);
		reg49.mr6_data_0 |= ((parms->dram_class == NCP_SM_DDR4_MODE) ? (tmp << 10) : 0x0);
#endif
	}
	/* HACK */
	reg49.mr6_data_0 |= 0x800;
	ctm->mr6 = reg49.mr6_data_0;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_49, *((ncp_uint32_t *)&reg49));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_50, (ncp_uint32_t *)&reg50);
	reg50.mr0_data_1 = reg42.mr0_data_0;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_50, *((ncp_uint32_t *)&reg50));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_51, (ncp_uint32_t *)&reg51);
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
		reg51.mr1_data_1 = NCP_SM_ENCODE_RTT_NOM_DDR4(parms->per_smem[cmId].sdram_rtt_nom[1]) |
			NCP_SM_ENCODE_DRV_IMP_DDR4(parms->per_smem[cmId].sdram_data_drv_imp[1]) |
			(parms->additive_latency << 3) | (0x1 /*DLLenable*/);
	}
	else
	{
		reg51.mr1_data_1 = NCP_SM_ENCODE_RTT_NOM_DDR3(parms->per_smem[cmId].sdram_rtt_nom[1]) |
			NCP_SM_ENCODE_DRV_IMP_DDR3(parms->per_smem[cmId].sdram_data_drv_imp[1]) | 
			(0x1 /*DLLenable*/);
	}
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_51, *((ncp_uint32_t *)&reg51));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_52, (ncp_uint32_t *)&reg52);
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
	if (parms->dram_class == NCP_SM_DDR4_MODE)
	{
		switch (parms->CAS_write_latency)
		{
			case 9:
				tmp = 0;
				break;
			case 10:
				tmp = 1;
				break;
			case 11:
				tmp = 2;
				break;
			case 12:
				tmp = 3;
				break;
			case 14:
				tmp = 4;
				break;
			case 16:
				tmp = 5;
				break;
			case 18:
				tmp = 6;
				break;
			default:
				tmp = 0;
				;
		}
		reg52.mr2_data_1 = (parms->per_smem[cmId].sdram_rtt_wr[1] << 9);
		reg52.mr2_data_1 &= ~(0x38);
		reg52.mr2_data_1 |= (tmp << 3);
		if (parms->high_temp_dram == TRUE)
		{
			reg52.mr2_data_1 |= 0x80;
		}
		else
		{
			reg52.mr2_data_1 |= 0x40;
		}
	}
	else
	{
		reg52.mr2_data_1 = ((parms->CAS_write_latency - 5 ) << 3) | (parms->per_smem[cmId].sdram_rtt_wr[1] << 9);
		if (parms->high_temp_dram == TRUE)
		{
			reg52.mr2_data_1 |= 0x80;
		}
	}
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_52, *((ncp_uint32_t *)&reg52));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_54, (ncp_uint32_t *)&reg54);
	reg54.mr3_data_1 = reg46.mr3_data_0;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_54, *((ncp_uint32_t *)&reg54));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_55, (ncp_uint32_t *)&reg55);
	reg55.mr4_data_1 = reg47.mr4_data_0;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_55, *((ncp_uint32_t *)&reg55));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_56, (ncp_uint32_t *)&reg56);
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
		reg56.mr5_data_1 = NCP_SM_ENCODE_RTT_PARK_DDR4(parms->per_smem[cmId].sdram_rtt_park[1]) |
			(0x400 /* enable data mask */) | (parms->dbi_wr_en << 11) | (parms->dbi_rd_en << 12);
	}
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_56, *((ncp_uint32_t *)&reg56));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_57, (ncp_uint32_t *)&reg57);
	reg57.mr6_data_1 = reg49.mr6_data_0;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_57, *((ncp_uint32_t *)&reg57));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_58, (ncp_uint32_t *)&reg58);
	reg58.bist_addr_check = 0x1;
	reg58.bist_data_check = 0x1;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_58, *((ncp_uint32_t *)&reg58));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_62, (ncp_uint32_t *)&reg62);
	reg62.ecc_en = parms->enableECC;
	reg62.xor_check_bits = 0x0;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_62, *((ncp_uint32_t *)&reg62));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_71, (ncp_uint32_t *)&reg71);
	reg71.zqinit = (parms->dram_class == NCP_SM_DDR4_MODE) ? ctm->tZQinit : ncp_ps_to_clk(parms->tck_ps, 1000000); /* 1 us */
	reg71.zqcl = 512;/* ncp_ps_to_clk(parms->tck_ps, 360000); *//* 360 ns */
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_71, *((ncp_uint32_t *)&reg71));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_72, (ncp_uint32_t *)&reg72);
	reg72.zqcs = 128;/* ncp_ps_to_clk(parms->tck_ps, 90000); *//* 90 ns */
	reg72.zq_req = 0x0;
	reg72.zq_on_sref_exit = 0x2;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_72, *((ncp_uint32_t *)&reg72));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_73, (ncp_uint32_t *)&reg73);
	reg73.zq_interval = (((parms->zqcs_interval /* units in micro-sec */)*1000000)/parms->tck_ps)/1024 /* long count seq */;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_73, *((ncp_uint32_t *)&reg73));

	reg74.zq_in_progress = 0x0;
	reg74.zqcs_rotate = 0x1;
	reg74.bank_diff = 0; /* all banks being used or should this be 0x1 */
	/* reg74.row_diff set early on */
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_74, *((ncp_uint32_t *)&reg74));

	/* reg75.col_diff set early on */
	reg75.aprebit = 0xa; /* loc of auto pre-charge bit in dram addr */
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_75, *((ncp_uint32_t *)&reg75));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_76, (ncp_uint32_t *)&reg76);
	reg76.age_count = 0xff;
	reg76.command_age_count = 0xff;
	reg76.addr_cmp_en = 0x1;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_76, *((ncp_uint32_t *)&reg76));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_77, (ncp_uint32_t *)&reg77);
	reg77.bank_split_en = 0x0;
	reg77.placement_en = 0x0;
	reg77.priority_en = 0x0;
	reg77.rw_same_en = 0x0;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_77, *((ncp_uint32_t *)&reg77));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_78, (ncp_uint32_t *)&reg78);
	reg78.rw_same_page_en = 0x0;
	reg78.cs_same_en = 0x0;
	reg78.w2r_split_en = 0x0;
	reg78.disable_rw_group_w_bnk_conflict = 0x1;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_78, *((ncp_uint32_t *)&reg78));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_79, (ncp_uint32_t *)&reg79);
	reg79.num_q_entries_act_disable = 0x3; /* 8 */
	reg79.swap_en = 0x1;
	reg79.disable_rd_interleave = 0x0;
	reg79.inhibit_dram_cmd = 0x0;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_79, *((ncp_uint32_t *)&reg79));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_80, (ncp_uint32_t *)&reg80);
	reg80.cs_map = parms->topology;
	reg80.burst_on_fly_bit = 0xc;
	reg80.reduc = 1; /* for CMEM this should always be ON */
	reg80.memdata_ratio_0 = (parms->sdram_device_width == 1) ? 3 : 2;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_80, *((ncp_uint32_t *)&reg80));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_81, (ncp_uint32_t *)&reg81);
	reg81.in_order_accept = 1;
	reg81.memdata_ratio_1 = (parms->sdram_device_width == 1) ? 3 : 2;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_81, *((ncp_uint32_t *)&reg81));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_82, (ncp_uint32_t *)&reg82);
	reg82.ctrlupd_req = 0x0;
	reg82.ctrlupd_req_per_aref_en = 0x1;
	reg82.preamble_support = parms->preamble_support;
	reg82.rd_preamble_training_en = 0x0;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_82, *((ncp_uint32_t *)&reg82));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_83, (ncp_uint32_t *)&reg83);
	reg83.bg_rotate_en = 0x1;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_83, *((ncp_uint32_t *)&reg83));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_96, (ncp_uint32_t *)&reg96);
	reg96.port_cmd_error_addr = 0x0;
	reg96.port_cmd_error_type = 0x0;
	reg96.odt_rd_map_cs0 = rd_ODT[0];
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_96, *((ncp_uint32_t *)&reg96));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_97, (ncp_uint32_t *)&reg97);
	reg97.odt_wr_map_cs0 = wr_ODT[0];
	reg97.odt_rd_map_cs1 = rd_ODT[1];
	reg97.odt_wr_map_cs1 = wr_ODT[1];
	reg97.todtl_2cmd = (parms->additive_latency + parms->CAS_write_latency -2 + 1);/* was 0x8 */
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_97, *((ncp_uint32_t *)&reg97));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_98, (ncp_uint32_t *)&reg98);
	reg98.todth_wr = 0x6;
	reg98.todth_rd = 0x6;
	reg98.odt_en = 0x1;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_98, *((ncp_uint32_t *)&reg98));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_99, (ncp_uint32_t *)&reg99);
	reg99.rd_to_odth = 0x5; /* check was 4 */
	reg99.r2r_diffcs_dly = 0x2;
	reg99.r2w_diffcs_dly = 0x2;
	reg99.w2r_diffcs_dly = 0x2;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_99, *((ncp_uint32_t *)&reg99));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_100, (ncp_uint32_t *)&reg100);
	reg100.w2w_diffcs_dly = 0x2;
	reg100.r2r_samecs_dly = 0x0;
	reg100.r2w_samecs_dly = 0x4;
	reg100.w2r_samecs_dly = 0x2;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_100, *((ncp_uint32_t *)&reg100));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_103, (ncp_uint32_t *)&reg103);
	reg103.swlvl_resp_2 = 0x0;
	reg103.wrlvl_req = 0x0;
	reg103.wrlvl_cs = 0x0;
	reg103.wldqsen = 0xd;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_103, *((ncp_uint32_t *)&reg103));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_104, (ncp_uint32_t *)&reg104);
	reg104.wlmrd = 0x28;
	reg104.wrlvl_en = 0x0;
	reg104.wrlvl_interval = 0x0;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_104, *((ncp_uint32_t *)&reg104));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_105, (ncp_uint32_t *)&reg105);
	reg105.dfi_phy_wrlvl_mode = 0x1;
	reg105.wrlvl_periodic = 0x0;
	reg105.wrlvl_on_sref_exit = 0x0;
	reg105.wrlvl_resp_mask = 0x0;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_105, *((ncp_uint32_t *)&reg105));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_106, (ncp_uint32_t *)&reg106);
	reg106.wrlvl_aref_en = 0x1;
	reg106.wrlvl_rotate = 0x0;
	reg106.wrlvl_cs_map = 0x3;
	reg106.wrlvl_error_status = 0x0;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_106, *((ncp_uint32_t *)&reg106));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_115, (ncp_uint32_t *)&reg115);
	reg115.rdlvl_format_3 = 0x0;
	reg115.rdlvl_seq_en = 0x0;
	reg115.rdlvl_gate_seq_en = 0x0;
	reg115.dfi_phy_rdlvl_mode = 0x1;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_115, *((ncp_uint32_t *)&reg115));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_116, (ncp_uint32_t *)&reg116);
	reg116.dfi_phy_rdlvl_gate_mode = 0x1;
	reg116.rdlvl_periodic = 0x0;
	reg116.rdlvl_on_sref_exit = 0x0;
	reg116.rdlvl_gate_periodic = 0x0;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_116, *((ncp_uint32_t *)&reg116));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_117, (ncp_uint32_t *)&reg117);
	reg117.rdlvl_gate_on_sref_exit = 0x0;
	reg117.rdlvl_aref_en = 0x1;
	reg117.rdlvl_rotate = 0x0;
	reg117.rdlvl_gate_rotate = 0x0;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_117, *((ncp_uint32_t *)&reg117));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_118, (ncp_uint32_t *)&reg118);
	reg118.rdlvl_cs_map = 0x3;
	reg118.rdlvl_gate_cs_map = 0x3;
	reg118.vref_cs = parms->vref_cs; /* default cs0 set to 0x1 */
	reg118.vref_en = 0x0;/* would be done by PHY ((parms->packedPHYTrainingOptions >> 17) & 0x1);*/ /* default disabled set to 0x0 */
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_118, *((ncp_uint32_t *)&reg118));
	if (parms->dram_class == NCP_SM_DDR4_MODE)
	{
		/* vref stuff needed ?? check */
		ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_119, (ncp_uint32_t *)&reg119);
		/* vref_pda_en is per DRAM addressability during VREF training, set to simply
		 * vref_en setting. */
		reg119.vref_pda_en = ((parms->packedPHYTrainingOptions >> 17) & 0x1);
		/* defines the range and value for vref training - 0x67 set to ~70%
		 * It is 7 bits, b[6] is range, whereas b[5:0] is the actual vref value
		 * there is setting for each DRAM for each chip-select */

		/* set vref_val in sm_parms to 0x67 */
		reg119.vref_val_dev0_0 = parms->vref_val;
		reg119.vref_val_dev0_1 = parms->vref_val;
		reg119.vref_val_dev1_0 = parms->vref_val;
		ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_119, *((ncp_uint32_t *)&reg119));

		ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_120, (ncp_uint32_t *)&reg120);
		reg120.vref_val_dev1_1 = parms->vref_val;
		reg120.vref_val_dev2_0 = parms->vref_val;
		reg120.vref_val_dev2_1 = parms->vref_val;
		reg120.vref_val_dev3_0 = parms->vref_val;
		ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_120, *((ncp_uint32_t *)&reg120));

		ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_121, (ncp_uint32_t *)&reg121);
		reg121.vref_val_dev3_1 = parms->vref_val;
		reg121.vref_val_ecc_dev0_0 = parms->vref_val;
		reg121.vref_val_ecc_dev0_1 = parms->vref_val;
		reg121.axi0_all_strobes_used_enable = 0x0; /* allows AXI port to accept Wr without waiting for all data */
		ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_121, *((ncp_uint32_t *)&reg121));
	}

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_122, (ncp_uint32_t *)&reg122);
	reg122.axi0_r_priority = 0x0; /* read priority 0 is highest */
	reg122.axi0_w_priority = 0x0; /* write priority 0 is highest */
	reg122.cke_status = 0x3;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_122, *((ncp_uint32_t *)&reg122));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_124, (ncp_uint32_t *)&reg124);
	reg124.tdfi_phy_rdlat = parms->phy_rdlat; /* check 48762 for 0x30 value */
	reg124.dram_clk_disable = ~(parms->topology);
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_124, *((ncp_uint32_t *)&reg124));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_125, (ncp_uint32_t *)&reg125);
	reg125.tdfi_ctrlupd_min = 0x0;
	reg125.tdfi_ctrlupd_max = 2 * ncp_ps_to_clk(parms->tck_ps, ((parms->high_temp_dram == TRUE) ?  3900 : 7800)*1000);
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_125, *((ncp_uint32_t *)&reg125));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_126, (ncp_uint32_t *)&reg126);
	reg126.tdfi_phyupd_type0 = 0x200;
	reg126.tdfi_phyupd_type1 = 0x200;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_126, *((ncp_uint32_t *)&reg126));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_127, (ncp_uint32_t *)&reg127);
	reg127.tdfi_phyupd_type2 = 0x200;
	reg127.tdfi_phyupd_type3 = 0x200;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_127, *((ncp_uint32_t *)&reg127));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_128, (ncp_uint32_t *)&reg128);
	reg128.tdfi_phyupd_resp = 2 * ncp_ps_to_clk(parms->tck_ps, ((parms->high_temp_dram == TRUE) ?  3900 : 7800)*1000);
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_128, *((ncp_uint32_t *)&reg128));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_129, (ncp_uint32_t *)&reg129);
	reg129.tdfi_ctrlupd_interval = 10 * ncp_ps_to_clk(parms->tck_ps, ((parms->high_temp_dram == TRUE) ?  3900 : 7800)*1000);
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_129, *((ncp_uint32_t *)&reg129));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_130, (ncp_uint32_t *)&reg130);
	/* Adjustment for PHY read timing */
	/* Should this be cas_lat + additive_lat + ca_parity_lat Check ?? Should minimum be 4 ? */
	reg130.rdlat_adj = ((parms->CAS_latency + parms->additive_latency + reg09.ca_parity_lat - reg19.reg_dimm_enable) - 3);
	/* Adjustment for PHY write timing */
	/* Should this be write_lat + additive_lat + ca_parity_lat Check ?? Should minimum be 1 ? */
	reg130.wrlat_adj = ((parms->CAS_write_latency + parms->additive_latency + reg09.ca_parity_lat - reg19.reg_dimm_enable) - 1);
	reg130.tdfi_ctrl_delay = 0x2;
	reg130.tdfi_dram_clk_disable = 0x2; /* from register_gen TCL 0 ?? */
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_130, *((ncp_uint32_t *)&reg130));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_131, (ncp_uint32_t *)&reg131);
	reg131.tdfi_dram_clk_enable = 0x1; /* from register_gen; should this be 0x3 ?. */
	reg131.tdfi_wrlvl_en = 0xa;
	reg131.tdfi_wrlvl_ww = 0x1c; /* from register_gen; should this be 0xa ? */
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_131, *((ncp_uint32_t *)&reg131));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_134, (ncp_uint32_t *)&reg134);
	reg134.tdfi_rdlvl_en = 0xa; /* from reg gen */
	reg134.tdfi_rdlvl_rr = 0xf;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_134, *((ncp_uint32_t *)&reg134));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_139, (ncp_uint32_t *)&reg139);
	reg139.rdlvl_gate_interval = parms->rdlvl_gate_interval;
	reg139.tdfi_phy_wrdata = 2;/*(1 + (parms->preamble_support >> 1));*/ /* from reg tcl */
	reg139.tdfi_rdcslat = 0xc; /* cas_latency + additive lat + ca_parity_lat - (preamble_support & 0x1); is this correct ? */
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_139, *((ncp_uint32_t *)&reg139));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_140, (ncp_uint32_t *)&reg140);
	reg140.tdfi_wrcslat = 0x8; /* wrlat_adj - 6 - (preamble_support >> 1) Should this be the calculation ?. */
	reg140.tdfi_parin_lat = (parms->dram_class == NCP_SM_DDR4_MODE) ? 0x0 : 0x1; /* from reg tcl */
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_140, *((ncp_uint32_t *)&reg140));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_143, (ncp_uint32_t *)&reg143);
	value = 0;
	for (i=0; i < 4; i++)
	{
		value |= (parms->dq_map_0[i] << (8 * i));
	}
	reg143.dq_map_0 = value;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_143, *((ncp_uint32_t *)&reg143));

	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_144, (ncp_uint32_t *)&reg144);
	reg144.dq_map_0 = (parms->dq_map_0[4] | (parms->dq_map_0[5] << 8));
	reg144.dq_map_odd_rank_swap_0 = parms->dq_map_odd_rank_swap_0;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_144, *((ncp_uint32_t *)&reg144));

	/* DDR configuration */

	ncr_read32(cmemCfgRegion, (ncp_uint32_t) NCP_CMEM_CFG_DDR_CFG, (ncp_uint32_t *)&ddrCfg);
	ddrCfg.col_diff = reg75.col_diff;
	ddrCfg.row_diff = reg74.row_diff;
	ddrCfg.bnk_diff = (parms->dram_class == NCP_SM_DDR4_MODE) ? 0x0 : 0x1;
	ddrCfg.num_rank = ((parms->topology == NCP_SM_TOPO_ONE_SINGLE_RANK) || (parms->topology == NCP_SM_TOPO_TWO_SINGLE_RANK)) ? 0x0 : 0x1;
	ncr_write32(cmemCfgRegion, NCP_CMEM_CFG_DDR_CFG, *((ncp_uint32_t *)&ddrCfg));

	ncr_read32(cmemCfgRegion, (ncp_uint32_t) NCP_CMEM_CFG_DDR_CTL, (ncp_uint32_t *)&ddrCtl);
	ddrCtl.init_start = 0x1;
	ddrCtl.erase_mem_go = 0x0;
	ddrCtl.erase_mem_mini = 0x0;
	ncr_write32(cmemCfgRegion, NCP_CMEM_CFG_DDR_CTL, *((ncp_uint32_t *)&ddrCtl));
#if 0
	/* Init MC */
	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_00, (ncp_uint32_t *)&reg00);
	reg00.start = 1;
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_00, *((ncp_uint32_t *)&reg00));

	/* poll for memory init operation */
	ncpStatus = (ncr_poll(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_84,  0x0100,  0x0100,  1000000,  10000));

	if (ncpStatus == NCP_ST_POLL_TIMEOUT)
	{
		errprintf("POLL timeout while waiting for MC init to complete [line:%d]\n",__LINE__);
	}
#endif
	/* Clear all interrupts */
	/* DENALI_CTL_85 */
	ncr_read32(ddrRegion, (ncp_uint32_t) NCP_MEMORY_CONTROLLER_DENALI_CTL_85, (ncp_uint32_t *)&reg85);
	reg85.int_ack = 0x7fffffff; /* clears associated bit in int_status */
	ncr_write32(ddrRegion, NCP_MEMORY_CONTROLLER_DENALI_CTL_85, *((ncp_uint32_t *)&reg85));

	NCP_COMMENT("## End CMEM%d config", cmNode);

	NCP_RETURN_LABEL
		return ncpStatus;
}
