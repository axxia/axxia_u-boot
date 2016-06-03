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
#include <stdio.h>
#include "ncp.h"
#include "ncp_pvt.h"
#include "ncp_sysmem_ext.h"
#include "ncp_sysmem_lsiphy.h" /* for macros and stuff mainly */
#include "ncp_sysmem_synopphy.h"
#endif

ncp_st_t
ncp_sm_ddr4_mc_reg_dump(
		ncp_dev_hdl_t   dev,
		ncp_uint32_t    smNode)
{
	ncp_st_t		ncpStatus = NCP_ST_SUCCESS;
	ncp_region_id_t 	ctlReg = NCP_REGION_ID(smNode, NCP_SYSMEM_TGT_DENALI);
	/*ncp_region_id_t 	phyReg 	= NCP_REGION_ID(smNode, NCP_SYSMEM_TGT_PHY);*/
	ncp_uint32_t		tmp = 0;
	ncp_uint32_t		period = 0, frequency = 0, ddr3 = 0, wrrtp = 0, cas = 0, drv_impd = 0, rtt_nom = 0;
	ncp_uint32_t		additivelatency = 0, wrcrc = 0, rtt_wr = 0, cwl = 0, cslat = 0, rddbi = 0, wrdbi = 0;
	ncp_uint32_t		caparlat = 0, ccd_l = 0, vreftrain = 0;

	ncp_denali_DENALI_CTL_00_5600_t 	reg00 = {0};
	ncp_denali_DENALI_CTL_01_5600_t 	reg01 = {0};
	ncp_denali_DENALI_CTL_05_5600_t 	reg05 = {0};
	ncp_denali_DENALI_CTL_06_5600_t 	reg06 = {0};
	ncp_denali_DENALI_CTL_07_5600_t 	reg07 = {0};
	ncp_denali_DENALI_CTL_08_5600_t 	reg08 = {0};
	ncp_denali_DENALI_CTL_09_5600_t 	reg09 = {0};
	ncp_denali_DENALI_CTL_10_5600_t 	reg10 = {0};
	ncp_denali_DENALI_CTL_11_5600_t 	reg11 = {0};
	ncp_denali_DENALI_CTL_12_5600_t 	reg12 = {0};
	ncp_denali_DENALI_CTL_13_5600_t 	reg13 = {0};
	ncp_denali_DENALI_CTL_16_5600_t 	reg16 = {0};
	ncp_denali_DENALI_CTL_18_5600_t 	reg18 = {0};
	ncp_denali_DENALI_CTL_21_5600_t 	reg21 = {0};
	ncp_denali_DENALI_CTL_35_5600_t 	reg35 = {0};
	ncp_denali_DENALI_CTL_36_5600_t 	reg36 = {0};
	ncp_denali_DENALI_CTL_40_5600_t 	reg40 = {0};
	ncp_denali_DENALI_CTL_41_5600_t 	reg41 = {0};
	ncp_denali_DENALI_CTL_42_5600_t 	reg42 = {0};
	ncp_denali_DENALI_CTL_101_5600_t 	reg101 = {0};
	ncp_denali_DENALI_CTL_114_5600_t 	reg114 = {0};
	ncp_denali_DENALI_CTL_117_5600_t 	reg117 = {0};
	ncp_denali_DENALI_CTL_118_5600_t 	reg118 = {0};
	ncp_denali_DENALI_CTL_119_5600_t 	reg119 = {0};
	ncp_denali_DENALI_CTL_120_5600_t 	reg120 = {0};
	ncp_denali_DENALI_CTL_121_5600_t 	reg121 = {0};
	ncp_denali_DENALI_CTL_122_5600_t 	reg122 = {0};
	ncp_denali_DENALI_CTL_124_5600_t 	reg124 = {0};
	ncp_denali_DENALI_CTL_126_5600_t 	reg126 = {0};
	ncp_denali_DENALI_CTL_128_5600_t 	reg128 = {0};
	ncp_denali_DENALI_CTL_123_5600_t 	reg123 = {0};
	ncp_denali_DENALI_CTL_155_5600_t 	reg155 = {0};
	ncp_denali_DENALI_CTL_156_5600_t 	reg156 = {0};
	ncp_denali_DENALI_CTL_157_5600_t 	reg157 = {0};
	ncp_denali_DENALI_CTL_158_5600_t 	reg158 = {0};
	ncp_denali_DENALI_CTL_159_5600_t 	reg159 = {0};
	ncp_denali_DENALI_CTL_336_5600_t 	reg336 = {0};
	ncp_denali_DENALI_CTL_366_5600_t 	reg366 = {0};
	ncp_denali_DENALI_CTL_386_5600_t 	reg386 = {0};
	ncp_denali_DENALI_CTL_397_5600_t 	reg397 = {0};

	ncr_read32(ctlReg, NCP_DENALI_CTL_00_5600, (ncp_uint32_t *)&reg00);
	printf ("Class = 0x%x\n", reg00.dram_class);

	printf ("--------------------------------------------------------------------------------\n -- DDR Controller version %u\n--------------------------------------------------------------------------------\n\n",reg00.version); 

	ncr_read32(ctlReg, NCP_DENALI_CTL_124_5600, (ncp_uint32_t *)&reg124);
	ncr_read32(ctlReg, NCP_DENALI_CTL_366_5600, (ncp_uint32_t *)&reg366);

	printf ("\n----- STATUS -----\n");
	printf ("    0x%2x.0.0x1F0 - Denali controller busy        = 0x%x\n", smNode, reg124.controller_busy);
	printf ("    0x%2x.0.0x5B8 - Interrupt status              = 0x%x\n", smNode, reg366.int_status);

	ncr_read32(ctlReg, NCP_DENALI_CTL_42_5600, (ncp_uint32_t *)&reg42);
	period = 7800000/(reg42.tref + 10);
	printf ("Period is %u ps\n",period);

	frequency = 1000000/period;
	ddr3 = (reg00.dram_class == 6) ? 1 : 0;

	ncr_read32(ctlReg, NCP_DENALI_CTL_05_5600, (ncp_uint32_t *)&reg05);
	ncr_read32(ctlReg, NCP_DENALI_CTL_06_5600, (ncp_uint32_t *)&reg06);
	ncr_read32(ctlReg, NCP_DENALI_CTL_07_5600, (ncp_uint32_t *)&reg07);
	ncr_read32(ctlReg, NCP_DENALI_CTL_08_5600, (ncp_uint32_t *)&reg08);
	ncr_read32(ctlReg, NCP_DENALI_CTL_336_5600, (ncp_uint32_t *)&reg336);
	ncr_read32(ctlReg, NCP_DENALI_CTL_01_5600, (ncp_uint32_t *)&reg01);
	ncr_read32(ctlReg, NCP_DENALI_CTL_117_5600, (ncp_uint32_t *)&reg117);
	ncr_read32(ctlReg, NCP_DENALI_CTL_118_5600, (ncp_uint32_t *)&reg118);
	ncr_read32(ctlReg, NCP_DENALI_CTL_123_5600, (ncp_uint32_t *)&reg123);

	printf ("*************************************************\n");
	printf ("Interesting Info\n");
	printf ("*************************************************\n");
	printf ("DRAM Interface is %s\n", (reg00.start) ? "ENABLED" : "DISABLED");
	printf ("DDR Type - %s\n", ddr3 ? "DDR3" : "DDR4");
	printf ("Best Guess Frequency = %u MHz\n",frequency);
	printf ("TINIT - %d cycles\n", reg05.tinit);
	printf ("Duration of reset - %u ns \n", ((reg06.trst_pwron * period)/1000));
	printf ("CKE Inactive time - %u ns \n", ((reg07.cke_inactive * period)/1000));
	printf ("CAS Latency = %d  -- WRLAT = %d\n",  (reg08.caslat_lin/2), reg08.wrlat);
	printf ("RDLAT_ADJ = 0x%x\t",reg336.rdlat_adj);
	printf ("WRLAT_ADJ = 0x%x",reg336.wrlat_adj);
	printf ("\n");
	printf ("Row Bits = %u\t", (reg01.max_row_reg - reg117.row_diff));
	printf ("Col Bits = %u\t", (reg01.max_col_reg - reg118.col_diff));
	printf ("Bank Bits = %u", (4 - reg117.bank_diff));
	printf ("\n");
	printf ("MEMDATA_RATIO_0 = 0x%x\t",reg123.memdata_ratio_0);
	printf ("REDUC = 0x%x",reg123.reduc);

	printf ("\n");
	printf ("\n");

	ncr_read32(ctlReg, NCP_DENALI_CTL_09_5600, (ncp_uint32_t *)&reg09);
	ncr_read32(ctlReg, NCP_DENALI_CTL_40_5600, (ncp_uint32_t *)&reg40);
	ncr_read32(ctlReg, NCP_DENALI_CTL_126_5600, (ncp_uint32_t *)&reg126);
	ncr_read32(ctlReg, NCP_DENALI_CTL_386_5600, (ncp_uint32_t *)&reg386);
	ncr_read32(ctlReg, NCP_DENALI_CTL_101_5600, (ncp_uint32_t *)&reg101);

	printf ("******** Optional Settings ********** \n");
	if (reg09.ca_parity_lat > 0) {
		printf ("\n ***** CA Parity Configuration *****\n");
		printf ("CA_PARITY_LAT = 0x%x", reg09.ca_parity_lat);
		printf ("CA_PARITY_ERROR = 0x%x", reg40.ca_parity_error); 
		printf ("\n");
	} else {
		printf ("CA PARITY Enabled? - NO\n");
	}
	printf ("RD_DBI_EN = 0x%x\t", reg126.rd_dbi_en); 
	printf ("WR_DBI_EN = 0x%x\t", reg126.wr_dbi_en); 
	printf ("CRC_MODE = 0x%x\t", reg386.crc_mode); 
	printf ("ECC_EN = 0x%x", reg101.ecc_en); 
	printf ("\n");

	ncr_read32(ctlReg, NCP_DENALI_CTL_35_5600, (ncp_uint32_t *)&reg35);
	ncr_read32(ctlReg, NCP_DENALI_CTL_36_5600, (ncp_uint32_t *)&reg36);

	printf ("\n ***** System Configuration ***** \n");
	printf ("CS_MAP \t= 0x%x", reg123.cs_map); 
	printf ("\n");
	printf ("CS_MAP_DIMM_0 \t= 0x%x\t", reg35.cs_map_dimm_0); 
	printf ("RANK0_MAP_DIMM_0 \t= 0x%x\t", reg36.rank0_map_dimm_0); 
	printf ("\n");
	printf ("CS_MAP_DIMM_1 \t= 0x%x\t", reg36.cs_map_dimm_1); 
	printf ("RANK0_MAP_DIMM_1 \t= 0x%x", reg36.rank0_map_dimm_1); 
	printf ("\n");

	ncr_read32(ctlReg, NCP_DENALI_CTL_10_5600, (ncp_uint32_t *)&reg10);

	printf ("\n ***** DRAM Configuration *****\n");
	if (reg10.tccd != 4)
	{
		printf ("tCCD should be 4!\n");
	}

	ncr_read32(ctlReg, NCP_DENALI_CTL_11_5600, (ncp_uint32_t *)&reg11);
	printf ("TRC \t= 0x%x\t", reg11.trc);
	printf ("TRRD \t= 0x%x\t", reg11.trrd);
	printf ("TRRD_L \t= 0x%x\t", reg11.trrd_l);
	printf ("TCCD \t= 0x%x\t", reg10.tccd);
	printf ("TCCD_L \t= 0x%x", reg11.tccd_l);
	printf ("\n");
	ncr_read32(ctlReg, NCP_DENALI_CTL_12_5600, (ncp_uint32_t *)&reg12);
	ncr_read32(ctlReg, NCP_DENALI_CTL_18_5600, (ncp_uint32_t *)&reg18);
	printf ("TRP \t= 0x%x\t", reg12.trp);
	printf ("TRP_AB \t= 0x%x\t", reg18.trp_ab);
	printf ("TWTR \t= 0x%x\t", reg12.twtr);
	printf ("TWTR_L \t= 0x%x\t", reg12.twtr_l);
	printf ("TRAS_MIN \t= 0x%x", reg12.tras_min);
	printf ("\n");
	ncr_read32(ctlReg, NCP_DENALI_CTL_13_5600, (ncp_uint32_t *)&reg13);
	ncr_read32(ctlReg, NCP_DENALI_CTL_16_5600, (ncp_uint32_t *)&reg16);
	printf ("TRTP \t= 0x%x\t", reg13.trtp);
	printf ("TFAW \t= 0x%x\t", reg13.tfaw);
	printf ("TWR \t= 0x%x\t", reg16.twr);
	printf ("TRCD \t= 0x%x\t", reg16.trcd);
	printf ("TREF \t= 0x%x", reg42.tref);
	printf ("\n");

	ncr_read32(ctlReg, NCP_DENALI_CTL_41_5600, (ncp_uint32_t *)&reg41);
	ncr_read32(ctlReg, NCP_DENALI_CTL_114_5600, (ncp_uint32_t *)&reg114);
	printf ("TRFC \t= 0x%x\t", reg41.trfc);
	printf ("ZQCS \t= 0x%x\t", reg114.zqcs);
	printf ("ZQCL \t= 0x%x\t", reg114.zqcl);
	printf ("TMRD \t= 0x%x", reg13.tmrd);
	printf ("\n");

	printf ("\n ***** MR Registers ***** \n");

	/* MR0 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_78_5600, &tmp);

	wrrtp = (tmp >> 9) & 0x7;
	cas = ((((tmp >> 4) & 0x7)*2) +((tmp >> 2) & 0x1));
	printf ("MR0 = 0x%x\n",tmp);
	printf ("    - Write Recover/RTP = %s\n", ((wrrtp == 0) ? "10/5" :
				(wrrtp == 1) ? "12/6" :
				(wrrtp == 2) ? "14/7" :
				(wrrtp == 3) ? "16/8" :
				(wrrtp == 4) ? "18/9" :
				(wrrtp == 5) ? "20/10" :
				(wrrtp == 6) ? "24/12" :
				"Err/Err"));
	printf ("    - CAS \t\t= %s\n", ((cas == 0) ? "9" :
				(cas == 1) ? "10" :
				(cas == 2) ? "11" :
				(cas == 3) ? "12" :
				(cas == 4) ? "13" :
				(cas == 5) ? "14" :
				(cas == 6) ? "15" :
				(cas == 7) ? "16" :
				(cas == 8) ? "18" :
				(cas == 9) ? "20" :
				(cas == 10) ? "22" :
				(cas == 11) ? "24" :
				"ERROR"));

	/* MR1 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_79_5600, &tmp);

	drv_impd = ((tmp >> 1) & 0x3);
	rtt_nom  = ((tmp >> 8) & 0x7);
	additivelatency = ((tmp >> 3) & 0x3);
	printf ("MR1 = 0x%x\n",tmp);
	printf ("    - RTT_NOM \t\t= %s\n", ((rtt_nom == 0) ? "RTT_NOM disabled" :
				(rtt_nom == 1) ? "RZQ/4 (60 ohm)" :
				(rtt_nom == 2) ? "RZQ/2 (120 ohm)" :
				(rtt_nom == 3) ? "RZQ/6 (40 ohm)" :
				(rtt_nom == 4) ? "RZQ/1 (240 ohm)" :
				(rtt_nom == 5) ? "RZQ/5 (48 ohm)" :
				(rtt_nom == 6) ? "RZQ/3 (80 ohm)" :
				"RZQ/7 (38 ohm)"));
	printf ("    - AL \t\t= %u\n", additivelatency);
	printf ("    - DRV Impedance\t= %s\n", ((drv_impd == 0) ? "RZQ/7 (34 ohm)" :
				(drv_impd == 1) ? "RZQ/5 (48 ohm)" :
				"ERROR"));

	/* MR2 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_80_5600, &tmp);

	wrcrc = ((tmp >> 12) & 0x1);
	rtt_wr = ((tmp >> 9) & 0x3);
	cwl = ((tmp >> 3) & 0xf);
	printf ("MR2 = 0x%x\n",tmp);
	printf ("    - Write CRC \t= %s\n", wrcrc ? "ENABLED" : "DISABLED");
	printf ("    - RTT_WR \t\t= %s\n", ((rtt_wr == 0) ? "Dynamic ODT OFF" :
				(rtt_wr == 1) ? "RZQ/2 (120 ohm)" :
				(rtt_wr == 2) ? "RZQ/1 (240 ohm)" :
				"High-Z"));
	printf ("    - CWL \t\t= %s\n", ((cwl == 0) ? "9  - 1600" :
				(cwl == 1) ? "10 - 1866" :
				(cwl == 2) ? "11 - 2133,1600" :
				(cwl == 3) ? "12 - 2400,1866" :
				(cwl == 4) ? "14 - 2133" :
				(cwl == 5) ? "16 - 2400" :
				(cwl == 6) ? "18 - ??" :
				"ERROR"));

	/* MR3 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_82_5600, &tmp);

	printf ("MR3 = 0x%x\n",tmp);

	/* MR4 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_83_5600, &tmp);

	cslat = ((tmp >> 6) & 0x7);
	printf ("MR4 = 0x%x\n",tmp);
	printf ("    - Wr/Rd Preamble \t= %u/%u\n", ((tmp >> 12) & 0x1), ((tmp >> 11) & 0x1));
	printf ("    - CS to CMD/ADDR latency = %u (0 is DISABLED)\n", (cslat == 0) ? 0 : cslat+2);

	/* MR5 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_84_5600, &tmp);

	rddbi = ((tmp >> 12) & 0x1);
	wrdbi = ((tmp >> 11) & 0x1);
	caparlat = tmp & 0x7;
	printf ("MR5 = 0x%x\n",tmp);
	printf ("    - Wr/Rd DBI \t= %u/%u\n", wrdbi, rddbi);
	printf ("    - CA Parity Latency = %s\n", ((caparlat == 0) ? "DISABLED" :
				(caparlat == 1) ? "4 - 1600,1866,2133" :
				(caparlat == 2) ? "5 - 2400" :
				"ERROR"));

	/* MR6 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_85_5600, &tmp);

	ccd_l = ((tmp >> 10) & 0x7);
	vreftrain = tmp & 0x7f;
	printf ("MR6 = 0x%x\n",tmp);
	printf ("    - tCCD_L \t\t= %s\n", ((ccd_l == 0) ? "4 - <= 1333" :
				(ccd_l == 1) ? "5 - <= 1866" :
				(ccd_l == 2) ? "6 - <= 2400" :
				"ERROR"));
	printf ("    - VREF Trained value = 0x%X\n",vreftrain);

	printf ("\n ***** Optimizations ***** \n");
	ncr_read32(ctlReg, NCP_DENALI_CTL_21_5600, (ncp_uint32_t *)&reg21);
	ncr_read32(ctlReg, NCP_DENALI_CTL_119_5600, (ncp_uint32_t *)&reg119);
	ncr_read32(ctlReg, NCP_DENALI_CTL_120_5600, (ncp_uint32_t *)&reg120);
	ncr_read32(ctlReg, NCP_DENALI_CTL_121_5600, (ncp_uint32_t *)&reg121);
	ncr_read32(ctlReg, NCP_DENALI_CTL_122_5600, (ncp_uint32_t *)&reg122);
	ncr_read32(ctlReg, NCP_DENALI_CTL_128_5600, (ncp_uint32_t *)&reg128);
	ncr_read32(ctlReg, NCP_DENALI_CTL_397_5600, (ncp_uint32_t *)&reg397);

	printf ("OPTIMAL_RMODW_EN \t= 0x%x", reg21.optimal_rmodw_en); 
	printf ("\n");
	printf ("ADDR_CMP_EN \t= 0x%x\t", reg119.addr_cmp_en); 
	printf ("RW_SAME_EN \t= 0x%x\t", reg120.rw_same_en); 
	printf ("PRIORITY_EN \t= 0x%x\t", reg120.priority_en); 
	printf ("PLACEMENT_EN \t= 0x%x\t", reg120.placement_en); 
	printf ("BANK_SPLIT_EN \t= 0x%x", reg120.bank_split_en); 
	printf ("\n");
	printf ("W2R_SPLIT_EN \t= 0x%x\t", reg121.w2r_split_en); 
	printf ("CS_SAME_EN \t= 0x%x\t", reg121.cs_same_en); 
	printf ("RW_SAME_PAGE_EN \t= 0x%x\t", reg121.rw_same_page_en); 
	printf ("SWAP_EN \t= 0x%x", reg122.swap_en);  
	printf ("\n");
	printf ("IN_ORDER_ACCEPT \t= 0x%x\t", reg124.in_order_accept);
	printf ("BG_ROTATE_EN \t= 0x%x\t", reg128.bg_rotate_en);
	printf ("WR_ORDER_REQ \t= 0x%x", reg397.wr_order_req);
	printf ("\n");

	printf ("\n ***** ODT Configuration ***** \n");
	ncr_read32(ctlReg, NCP_DENALI_CTL_156_5600, (ncp_uint32_t *)&reg156);
	ncr_read32(ctlReg, NCP_DENALI_CTL_157_5600, (ncp_uint32_t *)&reg157);
	ncr_read32(ctlReg, NCP_DENALI_CTL_155_5600, (ncp_uint32_t *)&reg155);

	printf ("ODT_EN \t= 0x%x\t", reg156.odt_en); 
	printf ("TODTH_RD \t= 0x%x\t", reg156.todth_rd); 
	printf ("TODTH_WR \t= 0x%x\t", reg156.todth_wr); 
	printf ("TODTL_2CMD \t= 0x%x\t", reg156.todtl_2cmd); 
	printf ("RD_TO_ODTH \t= 0x%x", reg157.rd_to_odth); 
	printf ("\n");
	printf ("ODT_RD_MAP_CS0 \t= 0x%x\t", reg155.odt_rd_map_cs0); 
	printf ("ODT_WR_MAP_CS0 \t= 0x%x\t", reg155.odt_wr_map_cs0); 
	printf ("ODT_RD_MAP_CS1 \t= 0x%x\t", reg155.odt_rd_map_cs1); 
	printf ("ODT_WR_MAP_CS1 \t= 0x%x", reg155.odt_wr_map_cs1); 
	printf ("\n");

	printf ("\n ***** Turnaround Configuration ***** \n");
	ncr_read32(ctlReg, NCP_DENALI_CTL_158_5600, (ncp_uint32_t *)&reg158);
	ncr_read32(ctlReg, NCP_DENALI_CTL_159_5600, (ncp_uint32_t *)&reg159);

	printf ("R2R_SAMECS_DLY = 0x%x\t", reg158.r2r_samecs_dly); 
	printf ("R2W_SAMECS_DLY = 0x%x", reg158.r2w_samecs_dly); 
	printf ("\n");
	printf ("W2W_SAMECS_DLY = 0x%x\t", reg159.w2w_samecs_dly); 
	printf ("W2R_SAMECS_DLY = 0x%x", reg159.w2r_samecs_dly); 
	printf ("\n");
	printf ("R2R_DIFFCS_DLY = 0x%x\t", reg157.r2r_diffcs_dly); 
	printf ("R2W_DIFFCS_DLY = 0x%x", reg157.r2w_diffcs_dly); 
	printf ("\n");
	printf ("W2W_DIFFCS_DLY = 0x%x\t", reg158.w2w_diffcs_dly); 
	printf ("W2R_DIFFCS_DLY = 0x%x", reg158.w2r_diffcs_dly); 
	printf ("\n");


	NCP_RETURN_LABEL
		return ncpStatus;
}

ncp_st_t
ncp_sm_ddr4_phy_reg_dump(
		ncp_dev_hdl_t   dev,
		ncp_uint32_t    smNode)
{
	ncp_st_t		ncpStatus = NCP_ST_SUCCESS;
	ncp_region_id_t 	phyReg 	= NCP_REGION_ID(smNode, NCP_SYSMEM_TGT_PHY);
	ncp_uint32_t		numbytes = 0, bytecnt = 0, tmp = 0, period = 0, freq = 0, numranks = 0, numislands = 0;
	ncp_uint32_t		errorindicated = 0, vreferrorindicated = 0, bits = 0, field = 0, val = 0;

	ncp_phy_DX0GCR0_5600_t regDX0GCR0 = {0};
	ncp_phy_DX0GCR5_5600_t regDX0GCR5 = {0};
	ncp_phy_DX0GCR6_5600_t regDX0GCR6 = {0};
	ncp_phy_DCR_5600_t regDCR = {0};
	ncp_phy_PGCR2_5600_t regPGCR2 = {0};
	ncp_phy_PGCR3_5600_t regPGCR3 = {0};
	ncp_phy_PTR0_5600_t regPTR0 = {0};
	ncp_phy_PTR1_5600_t regPTR1 = {0};
	ncp_phy_PLLCR0_5600_t regPLLCR0 = {0};
	/*ncp_phy_PLLCR_5600_t regPLLCR = {0};*/
	ncp_phy_ZQCR_5600_t regZQCR = {0};
	ncp_phy_MR0_5600_t regMR0 = {0};
	ncp_phy_MR1_5600_t regMR1 = {0};
	ncp_phy_MR2_5600_t regMR2 = {0};
	/*ncp_phy_MR3_5600_t regMR3 = {0};*/
	ncp_phy_MR4_5600_t regMR4 = {0};
	ncp_phy_MR5_5600_t regMR5 = {0};
	ncp_phy_MR6_5600_t regMR6 = {0};
	ncp_phy_DTPR0_5600_t regDTPR0 = {0};
	ncp_phy_DTPR1_5600_t regDTPR1 = {0};
	ncp_phy_DTPR4_5600_t regDTPR4 = {0};
	ncp_phy_DTPR5_5600_t regDTPR5 = {0};
	ncp_phy_PTR3_5600_t regPTR3 = {0};
	ncp_phy_PTR4_5600_t regPTR4 = {0};
	ncp_phy_DXCCR_5600_t regDXCCR = {0};
	ncp_phy_DTCR0_5600_t regDTCR0 = {0};
	ncp_phy_DTCR1_5600_t regDTCR1 = {0};
	ncp_phy_VTCR0_5600_t regVTCR0 = {0};
	ncp_phy_ZQ0PR_5600_t regZQ0PR = {0};
	ncp_phy_DX0RSR0_5600_t regDX0RSR0 = {0};
	ncp_phy_DX0RSR1_5600_t regDX0RSR1 = {0};
	ncp_phy_DX0RSR2_5600_t regDX0RSR2 = {0};
	ncp_phy_DX0RSR3_5600_t regDX0RSR3 = {0};
	ncp_phy_DX0GSR3_5600_t regDX0GSR3 = {0};
	ncp_phy_DX0GSR2_5600_t regDX0GSR2 = {0};
	ncp_phy_RANKIDR_5600_t regRANKIDR = {0};
	ncp_phy_DX0MDLR0_5600_t regDX0MDLR0 = {0};
	ncp_phy_DX0MDLR1_5600_t regDX0MDLR1 = {0};
	ncp_phy_DX0GSR0_5600_t regDX0GSR0 = {0};
	ncp_phy_DX0LCDLR0_5600_t regDX0LCDLR0 = {0};
	ncp_phy_DX0LCDLR1_5600_t regDX0LCDLR1 = {0};
	ncp_phy_DX0LCDLR2_5600_t regDX0LCDLR2 = {0};
	ncp_phy_DX0LCDLR3_5600_t regDX0LCDLR3 = {0};
	ncp_phy_DX0LCDLR4_5600_t regDX0LCDLR4 = {0};
	ncp_phy_DX0GTR0_5600_t regDX0GTR0 = {0};

	for (bytecnt = 0; bytecnt < 9; bytecnt++)
	{
		/* DXnGCR0 */
		ncr_read32(phyReg, (NCP_PHY_DX0GCR0_5600 + (bytecnt * 0x100)), (ncp_uint32_t *)&regDX0GCR0);
		if (regDX0GCR0.dxen)
		{
			numbytes++;
		}
	}
	printf ("NUM BYTES calculated as %d\n", numbytes);

	/* DCR */
	ncr_read32(phyReg, NCP_PHY_DCR_5600, (ncp_uint32_t *)&regDCR);
	if (regDCR.ddrmd != 0x4)
	{
		printf ("ERROR: DCR[2:0] - Expect DDR4\n");
	}
	if (regDCR.ddr2t != 0x1)
	{
		printf ("ERROR: DCR[28] - Expect DDR2T\n");
	}
	if (regDCR.udimm != 0x1)
	{
		printf ("WARNING: DCR[29] - Expect Address Mirroring\n");
	}
	if (regDCR.ubg)
	{
		printf ("PHY is configured for x16 DRAM devices\n");
	}
	else
	{
		printf ("PHY is configured for x8 DRAM devices\n");
	}

	/* PGCR0-5 */
	ncr_read32(phyReg, NCP_PHY_PGCR2_5600, (ncp_uint32_t *)&regPGCR2);
	period = (7800 * 9 * 2 * 1000/regPGCR2.trefprd);
	freq = (1000000 / period);
	printf ("PGCR2 - Best Guess DDR Clock Frequency = %d MHz\n",freq);

	ncr_read32(phyReg, NCP_PHY_PGCR3_5600, (ncp_uint32_t *)&regPGCR3);
	if (regPGCR3.rdmode != 1)
	{
		printf ("ERROR: PGCR3 RDMODE should be -Static Read Response\n");
	}

	ncr_read32(phyReg, NCP_PHY_PGCR4_5600, &tmp);
	if (tmp != 0)
	{
		printf ("ERROR: Check PGCR4 value - 0x%x!\n", tmp);
	}

	/* PTR0-2 */
	ncr_read32(phyReg, NCP_PHY_PTR0_5600, (ncp_uint32_t *)&regPTR0);
	printf ("tPLLGS = %d ns clocks(min 4000 ns?)\n",(regPTR0.tpllgs * period)/1000);
	printf ("tPLLPD = %d ns clocks(min 1000 ns?)\n",(regPTR0.tpllpd * period)/1000);

	ncr_read32(phyReg, NCP_PHY_PTR1_5600, (ncp_uint32_t *)&regPTR1);
	printf ("tPLLRST = %d ns clocks(min 9000 ns?)\n",(regPTR1.tpllrst * period)/1000);
	printf ("tPLLLOCK = %d ns clocks(min 100000 ns?)\n",(regPTR1.tplllock * period)/1000);

	/* PLLCR0 */
	ncr_read32(phyReg, NCP_PHY_PLLCR0_5600, (ncp_uint32_t *)&regPLLCR0);
	if (((regPLLCR0.frqsel == 0) && (freq < 440)) || ((regPLLCR0.frqsel == 1) && ((freq < 225) || (freq > 490))))
	{
		printf ("ERROR: PLLCR0.FRQSEL is incorrect for frequency of %d MHz\n",freq);
	}

	/*ncr_read32(phyReg, NCP_PHY_PLLCR_5600, (ncp_uint32_t *)&regPLLCR);
	  if (((regPLLCR.frqsel == 0) && (freq < 440)) || ((regPLLCR.frqsel == 1) && ((freq < 225) || (freq > 490))))
	  {
	  printf ("ERROR: PLLCR.FRQSEL is incorrect for frequency of %d MHz\n",freq);
	  }*/

	/* ZQCR */
	ncr_read32(phyReg, NCP_PHY_ZQCR_5600, (ncp_uint32_t *)&regZQCR);
	if ((regZQCR.term_off != 0x0) || (regZQCR.zqpd != 0x0))
	{
		printf ("ZQCR[7:0] should be all 0\n");
	}
	if (regZQCR.pgwait != 0x7)
	{
		printf ("ERROR: ZQCR.PGWAIT should be 0x7, but got 0x%d\n",regZQCR.pgwait);
	}

	/* MR0-6 */
	ncr_read32(phyReg, NCP_PHY_MR0_5600, (ncp_uint32_t *)&regMR0);
	ncr_read32(phyReg, NCP_PHY_MR0_5600, &tmp);
	printf ("MR0 = 0x%x\n",tmp);
	printf ("    - Write Recover/RTP = %s\n", ((regMR0.wr == 0) ? "10/5" :
				(regMR0.wr == 1) ? "12/6" :
				(regMR0.wr == 2) ? "14/7" :
				(regMR0.wr == 3) ? "16/8" :
				(regMR0.wr == 4) ? "18/9" :
				(regMR0.wr == 5) ? "20/10" :
				(regMR0.wr == 6) ? "24/12" :
				"Err/Err"));
	printf ("    - CAS \t\t= %s\n", ((((regMR0.cl_6_4 * 2) + (regMR0.cl_2)) == 0) ? "9" :
				(((regMR0.cl_6_4 * 2) + (regMR0.cl_2)) == 1) ? "10" :
				(((regMR0.cl_6_4 * 2) + (regMR0.cl_2)) == 2) ? "11" :
				(((regMR0.cl_6_4 * 2) + (regMR0.cl_2)) == 3) ? "12" :
				(((regMR0.cl_6_4 * 2) + (regMR0.cl_2)) == 4) ? "13" :
				(((regMR0.cl_6_4 * 2) + (regMR0.cl_2)) == 5) ? "14" :
				(((regMR0.cl_6_4 * 2) + (regMR0.cl_2)) == 6) ? "15" :
				(((regMR0.cl_6_4 * 2) + (regMR0.cl_2)) == 7) ? "16" :
				(((regMR0.cl_6_4 * 2) + (regMR0.cl_2)) == 8) ? "18" :
				(((regMR0.cl_6_4 * 2) + (regMR0.cl_2)) == 9) ? "20" :
				(((regMR0.cl_6_4 * 2) + (regMR0.cl_2)) == 10) ? "22" :
				(((regMR0.cl_6_4 * 2) + (regMR0.cl_2)) == 11) ? "24" :
				"ERROR"));

	ncr_read32(phyReg, NCP_PHY_MR1_5600, (ncp_uint32_t *)&regMR1);
	ncr_read32(phyReg, NCP_PHY_MR1_5600, &tmp);
	printf ("MR1 = 0x%x\n",tmp);
	printf ("    - RTT_NOM \t\t= %s\n", ((((tmp & 0x700) >> 8) == 0) ? "RTT_NOM disabled" :
				(((tmp & 0x700) >> 8) == 1) ? "RZQ/4 (60 ohm)" :
				(((tmp & 0x700) >> 8) == 2) ? "RZQ/2 (120 ohm)" :
				(((tmp & 0x700) >> 8) == 3) ? "RZQ/6 (40 ohm)" :
				(((tmp & 0x700) >> 8) == 4) ? "RZQ/1 (240 ohm)" :
				(((tmp & 0x700) >> 8) == 5) ? "RZQ/5 (48 ohm)" :
				(((tmp & 0x700) >> 8) == 6) ? "RZQ/3 (80 ohm)" :
				"RZQ/7 (38 ohm)"));
	printf ("    - AL \t\t= %d\n", regMR1.al);
	printf ("    - DRV Impedance\t= %s\n", ((((tmp & 0x6) >> 1) == 0) ? "RZQ/7 (34 ohm)" :
				(((tmp & 0x6) >> 1) == 1) ? "RZQ/5 (48 ohm)" :
				"ERROR"));

	ncr_read32(phyReg, NCP_PHY_MR2_5600, (ncp_uint32_t *)&regMR2);
	ncr_read32(phyReg, NCP_PHY_MR2_5600, &tmp);
	printf ("MR2 = 0x%x\n",tmp);
	printf ("    - Write CRC \t= %s\n", ((tmp & 0x1000) >> 12) ? "ENABLED" : "DISABLED"); /* per jedec */
	printf ("    - RTT_WR \t\t= %s\n", ((regMR2.rttwr == 0) ? "Dynamic ODT OFF" :
				(regMR2.rttwr == 1) ? "RZQ/2 (120 ohm)" :
				(regMR2.rttwr == 2) ? "RZQ/1 (240 ohm)" :
				"High-Z"));
	printf ("    - CWL \t\t= %s\n", ((regMR2.cwl == 0) ? "9  - 1600" :
				(regMR2.cwl == 1) ? "10 - 1866" :
				(regMR2.cwl == 2) ? "11 - 2133,1600" :
				(regMR2.cwl == 3) ? "12 - 2400,1866" :
				(regMR2.cwl == 4) ? "14 - 2133" :
				(regMR2.cwl == 5) ? "16 - 2400" :
				(regMR2.cwl == 6) ? "18 - ??" :
				"ERROR"));

	ncr_read32(phyReg, NCP_PHY_MR3_5600, &tmp);
	printf ("MR3 = 0x%x\n",tmp);

	ncr_read32(phyReg, NCP_PHY_MR4_5600, (ncp_uint32_t *)&regMR4);
	ncr_read32(phyReg, NCP_PHY_MR4_5600, &tmp);
	printf ("MR4 = 0x%x\n",tmp);
	printf ("    - Wr/Rd Preamble \t= %d/%d\n", regMR4.wrp, regMR4.rdp);
	printf ("    - CS to CMD/ADDR latency = %d\n", (regMR4.cs2cmdl == 0) ? 0/*"DISABLED"*/ : (regMR4.cs2cmdl+2));

	ncr_read32(phyReg, NCP_PHY_MR5_5600, (ncp_uint32_t *)&regMR5);
	ncr_read32(phyReg, NCP_PHY_MR5_5600, &tmp);
	printf ("MR5 = 0x%x\n",tmp);
	printf ("    - Wr/Rd DBI \t= %d/%d\n", regMR5.wdbi, regMR5.rdbi);
	printf ("    - CA Parity Latency = %s\n", ((regMR5.capm == 0) ? "DISABLED" :
				(regMR5.capm == 1) ? "4 - 1600,1866,2133" :
				(regMR5.capm == 2) ? "5 - 2400" :
				"ERROR"));

	ncr_read32(phyReg, NCP_PHY_MR6_5600, (ncp_uint32_t *)&regMR6);
	ncr_read32(phyReg, NCP_PHY_MR6_5600, &tmp);
	printf ("MR6 = 0x%x\n",tmp);
	printf ("    - tCCD_L \t\t= %s\n", ((regMR6.tccdl == 0) ? "4 - <= 1333" :
				(regMR6.tccdl == 1) ? "5 - <= 1866" :
				(regMR6.tccdl == 2) ? "6 - <= 2400" :
				"ERROR"));
	printf ("    - VREF Trained value = 0x%X\n",(tmp & 0x7f)); /* from jedec */

	/* DTPR0-6 */
	ncr_read32(phyReg, NCP_PHY_DTPR0_5600, (ncp_uint32_t *)&regDTPR0);
	ncr_read32(phyReg, NCP_PHY_DTPR1_5600, (ncp_uint32_t *)&regDTPR1);
	ncr_read32(phyReg, NCP_PHY_DTPR4_5600, (ncp_uint32_t *)&regDTPR4);
	ncr_read32(phyReg, NCP_PHY_DTPR5_5600, (ncp_uint32_t *)&regDTPR5);

	printf ("tRC  \t= %d\t",  regDTPR5.trc);
	printf ("tRRD \t= %d\n",  regDTPR0.trrd);

	printf ("tRP  \t= %d\t",  regDTPR0.trp);
	printf ("tWTR \t= %d\t",  regDTPR5.twtr);
	printf ("tRAS \t= %d\n",  regDTPR0.tras);

	printf ("tRTP \t= %d\t",  regDTPR0.trtp);
	printf ("tFAW \t= %d\t",  regDTPR1.tfaw);
	printf ("tRCD \t= %d\n",  regDTPR5.trcd);

	printf ("tRFC \t= %d\t",  regDTPR4.trfc);
	printf ("tMRD \t= %d\t",  regDTPR1.tmrd);
	printf ("tMOD \t= %d\t",  regDTPR1.tmod);
	printf ("tWLMRD \t= %d\t",regDTPR1.twlmrd);
	printf ("tWLO \t= %d\n",  regDTPR4.twlo);

	/* PTR3-4 */
	ncr_read32(phyReg, NCP_PHY_PTR3_5600, (ncp_uint32_t *)&regPTR3);
	ncr_read32(phyReg, NCP_PHY_PTR4_5600, (ncp_uint32_t *)&regPTR4);

	printf ("tDINIT0 = %d ns (min 500000 ns?)\n",((regPTR3.tdinit0) * period)/1000);
	printf ("tDINIT1 = %d clocks (tRFC + 5 ?)\n",regPTR3.tdinit1);
	printf ("tDINIT2 = %d ns (min 200000 ns?)\n",((regPTR4.tdinit2) * period)/1000);

	/* DXCCR */
	ncr_read32(phyReg, NCP_PHY_DXCCR_5600, (ncp_uint32_t *)&regDXCCR);
	ncr_read32(phyReg, NCP_PHY_DXCCR_5600, &tmp);

	printf ("DXCCR register = 0x%x\n", tmp);
	printf ("MSBDQ = %d\n",regDXCCR.msbudq);

	/* DTCR0-1 */
	ncr_read32(phyReg, NCP_PHY_DTCR0_5600, (ncp_uint32_t *)&regDTCR0);
	ncr_read32(phyReg, NCP_PHY_DTCR1_5600, (ncp_uint32_t *)&regDTCR1);

	if (regDTCR0.dtmpr == 0) {
		printf ("ERROR: DQS Gate Training does NOT use MPR. Not Recommended for DDR4\n");
	}
	if (regDTCR0.dtcmpd == 0) {
		printf ("NOTE: DQS Gate Training does NOT use data comparison.\n");
	}

	numranks = regDTCR1.ranken;
	if (regDTCR1.ranken == 3)  
	{
		numranks = 2;
	}
	else if (regDTCR1.ranken == 7)  
	{
		numranks = 3;
	}
	else if (regDTCR1.ranken == 15) 
	{
		numranks = 4;
	}
	printf ("NUMBER of RANKS configured = %d\n", numranks);

	/* VTCR0-1 */
	ncr_read32(phyReg, NCP_PHY_VTCR0_5600, (ncp_uint32_t *)&regVTCR0);
	printf ("tVREF = %d ns (min 150 ns?)\n",((1 << (regVTCR0.tvref + 4)) * period)/1000);

	printf ("\n************** ODT and Impedance config - Assuming RZQ=240ohm ******************\n");
	printf ("\t\t\t");
	numislands = 4;
	for (bytecnt = 0; bytecnt < numislands; bytecnt++) 
	{
		printf ("Island %d \t", bytecnt);
	}
	printf ("\n");

	/* ZQnPR */
	printf ("Output Impedance\t");
	for (bytecnt = 0; bytecnt < numislands; bytecnt++) 
	{
		ncr_read32(phyReg, (NCP_PHY_ZQ0PR_5600 + (0x10 * bytecnt)), (ncp_uint32_t *)&regZQ0PR);
		printf (" %s \t", (((regZQ0PR.zqdiv & 0xF) == 1 ) ? "240 ohm" :
					((regZQ0PR.zqdiv & 0xF) == 3 ) ? "120 ohm" :
					((regZQ0PR.zqdiv & 0xF) == 5 ) ? "80 ohm" :
					((regZQ0PR.zqdiv & 0xF) == 7 ) ? "60 ohm" :
					((regZQ0PR.zqdiv & 0xF) == 9 ) ? "48 ohm" :
					((regZQ0PR.zqdiv & 0xF) == 11 ) ? "40 ohm" :
					((regZQ0PR.zqdiv & 0xF) == 13 ) ? "34 ohm" :
					"UNKNOWN"));
	} 
	printf ("\n");
	printf ("ODT settings\t\t");
	for (bytecnt = 0; bytecnt < numislands; bytecnt++) 
	{
		ncr_read32(phyReg, (NCP_PHY_ZQ0PR_5600 + (0x10 * bytecnt)), (ncp_uint32_t *)&regZQ0PR);
		printf (" %s \t", ((((regZQ0PR.zqdiv & 0xF0) >> 4) == 1 ) ? "240 ohm" :
					(((regZQ0PR.zqdiv & 0xF0) >> 4) == 3 ) ? "120 ohm" :
					(((regZQ0PR.zqdiv & 0xF0) >> 4) == 5 ) ? "80 ohm" :
					(((regZQ0PR.zqdiv & 0xF0) >> 4) == 7 ) ? "60 ohm" :
					(((regZQ0PR.zqdiv & 0xF0) >> 4) == 9 ) ? "48 ohm" :
					(((regZQ0PR.zqdiv & 0xF0) >> 4) == 11 ) ? "40 ohm" :
					(((regZQ0PR.zqdiv & 0xF0) >> 4) == 13 ) ? "34 ohm" :
					"UNKNOWN"));
	}
	printf ("\n");

	/* Data Training Results */
	printf ("\n***********************************************************\n");
	printf (" ** DDR Training typically occurs in the following order **\n");
	printf ("***********************************************************\n");
	printf (" *  1) PHY INIT \t\t-> PHY PLLs are initialized, and delay lines are calibrated\n");
	printf (" *  2) Write Leveling \t\t-> DQS at DRAM each is aligned to the Clock at each DRAM\n");
	printf (" *  3) Gate Training \t\t-> The timing for expecting a DQS from DRAM during a read is determined\n");
	printf (" *  4) Write Latency Adjust \t-> The correct write latency is determined after write leveling\n");
	printf (" *  5) Static Read Training \t-> Minimum amount of time to leave read data in read FIFOs is determined\n");
	printf (" *  6) Read bit de-skew \t-> Each bit in a data lane is adjusted for timing to optimize reads\n");
	printf (" *  7) Write bit de-skew \t-> Each bit in a data lane is adjusted for timing to optimize writes\n");
	printf (" *  8) Read eye training \t-> Read DQS is adjusted to optimally place DQS edge in center of data eye\n");
	printf (" *  9) Write eye training \t-> Write DQS is adjusted to optimally place DQS edge in center of data eye\n");
	printf (" * 10) VREF training \t\t-> Adjust VREF settings in DRAM and in PHY for optimal placement\n");

	printf ("\n**************** Training Errors *******************\n");
	printf ("***** All Values in Binary with Error per rank *****\n");
	printf ("\t\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		printf ("Byte %d \t", bytecnt);
	}
	printf ("\n");
	errorindicated = 0;
	vreferrorindicated = 0;

	printf ("Gate Train Error\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnRSR0 */
		ncr_read32(phyReg, (NCP_PHY_DX0RSR0_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0RSR0);
		errorindicated += regDX0RSR0.qsgerr;
		printf (" %d%d%d%d \t", 
				((regDX0RSR0.qsgerr & 0x8) ? 1 : 0),
				((regDX0RSR0.qsgerr & 0x4) ? 1 : 0),
				((regDX0RSR0.qsgerr & 0x2) ? 1 : 0),
				((regDX0RSR0.qsgerr & 0x1) ? 1 : 0));
	}
	printf ("\n");

	printf ("Read Leveling Error\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnRSR1 */
		ncr_read32(phyReg, (NCP_PHY_DX0RSR1_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0RSR1);
		errorindicated += regDX0RSR1.rdlvlerr;
		printf (" %d%d%d%d \t", 
				((regDX0RSR1.rdlvlerr & 0x8) ? 1 : 0),
				((regDX0RSR1.rdlvlerr & 0x4) ? 1 : 0),
				((regDX0RSR1.rdlvlerr & 0x2) ? 1 : 0),
				((regDX0RSR1.rdlvlerr & 0x1) ? 1 : 0));
	}
	printf ("\n");

	printf ("WriteLatencyDQ Error\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnRSR2 */
		ncr_read32(phyReg, (NCP_PHY_DX0RSR2_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0RSR2);
		errorindicated += regDX0RSR2.wlawn;
		printf (" %d%d%d%d \t", 
				((regDX0RSR2.wlawn & 0x8) ? 1 : 0),
				((regDX0RSR2.wlawn & 0x4) ? 1 : 0),
				((regDX0RSR2.wlawn & 0x2) ? 1 : 0),
				((regDX0RSR2.wlawn & 0x1) ? 1 : 0));
	}
	printf ("\n");

	printf ("Write Latency Error\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnRSR3 */
		ncr_read32(phyReg, (NCP_PHY_DX0RSR3_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0RSR3);
		errorindicated += regDX0RSR3.wlaerr;
		printf (" %d%d%d%d \t", 
				((regDX0RSR3.wlaerr & 0x8) ? 1 : 0),
				((regDX0RSR3.wlaerr & 0x4) ? 1 : 0),
				((regDX0RSR3.wlaerr & 0x2) ? 1 : 0),
				((regDX0RSR3.wlaerr & 0x1) ? 1 : 0));
	}
	printf ("\n");

	printf ("Host VREF Error\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 	
	{
		/* DXnGSR3 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR3_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR3);
		errorindicated += regDX0GSR3.hverr;
		vreferrorindicated += regDX0GSR3.hverr;
		printf (" %d%d%d%d \t", 
				((regDX0GSR3.hverr & 0x8) ? 1 : 0),
				((regDX0GSR3.hverr & 0x4) ? 1 : 0),
				((regDX0GSR3.hverr & 0x2) ? 1 : 0),
				((regDX0GSR3.hverr & 0x1) ? 1 : 0));
	}
	printf ("\n");

	printf ("Host VREF Warning\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGSR3 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR3_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR3);
		errorindicated += regDX0GSR3.hvwrn;
		vreferrorindicated += regDX0GSR3.hvwrn;
		printf (" %d%d%d%d \t", 
				((regDX0GSR3.hvwrn & 0x8) ? 1 : 0),
				((regDX0GSR3.hvwrn & 0x4) ? 1 : 0),
				((regDX0GSR3.hvwrn & 0x2) ? 1 : 0),
				((regDX0GSR3.hvwrn & 0x1) ? 1 : 0));
	}
	printf ("\n");

	printf ("DRAM VREF Error\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGSR3 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR3_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR3);
		errorindicated += regDX0GSR3.dverr;
		vreferrorindicated += regDX0GSR3.dverr;
		printf (" %d%d%d%d \t", 
				((regDX0GSR3.dverr & 0x8) ? 1 : 0),
				((regDX0GSR3.dverr & 0x4) ? 1 : 0),
				((regDX0GSR3.dverr & 0x2) ? 1 : 0),
				((regDX0GSR3.dverr & 0x1) ? 1 : 0));
	}
	printf ("\n");

	printf ("DRAM VREF Warning\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGSR3 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR3_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR3);
		errorindicated += regDX0GSR3.dvwrn;
		vreferrorindicated += regDX0GSR3.dvwrn;
		printf (" %d%d%d%d \t", 
				((regDX0GSR3.dvwrn & 0x8) ? 1 : 0),
				((regDX0GSR3.dvwrn & 0x4) ? 1 : 0),
				((regDX0GSR3.dvwrn & 0x2) ? 1 : 0),
				((regDX0GSR3.dvwrn & 0x1) ? 1 : 0));
	}
	printf ("\n");

	if (vreferrorindicated) 
	{
		printf ("VREF Debug Code\t");
		for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
		{
			/* DXnGSR3 */
			ncr_read32(phyReg, (NCP_PHY_DX0GSR3_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR3);
			errorindicated += regDX0GSR3.estat;
			vreferrorindicated += regDX0GSR3.estat;
			printf (" %d%d%d%d \t", 
					((regDX0GSR3.estat & 0x8) ? 1 : 0),
					((regDX0GSR3.estat & 0x4) ? 1 : 0),
					((regDX0GSR3.estat & 0x2) ? 1 : 0),
					((regDX0GSR3.estat & 0x1) ? 1 : 0));
		}
		printf ("\n");
	}

	printf ("\n**************** Training Errors *******************\n");
	printf ("******** All Values in Binary. NOT per rank *********\n");
	printf ("\t\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		printf ("Byte %d \t", bytecnt);
	}
	printf ("\n");

	printf ("Read bit deskew Error\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGSR2 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR2_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR2);
		errorindicated += regDX0GSR2.rderr;
		printf (" %d%d%d%d \t", 
				((regDX0GSR2.rderr & 0x8) ? 1 : 0),
				((regDX0GSR2.rderr & 0x4) ? 1 : 0),
				((regDX0GSR2.rderr & 0x2) ? 1 : 0),
				((regDX0GSR2.rderr & 0x1) ? 1 : 0));
	}
	printf ("\n");

	printf ("Read bit deskew Warn\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGSR2 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR2_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR2);
		errorindicated += regDX0GSR2.rdwn;
		printf (" %d%d%d%d \t", 
				((regDX0GSR2.rdwn & 0x8) ? 1 : 0),
				((regDX0GSR2.rdwn & 0x4) ? 1 : 0),
				((regDX0GSR2.rdwn & 0x2) ? 1 : 0),
				((regDX0GSR2.rdwn & 0x1) ? 1 : 0));
	}
	printf ("\n");

	printf ("Write bit deskew Error\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGSR2 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR2_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR2);
		errorindicated += regDX0GSR2.wderr;
		printf (" %d%d%d%d \t", 
				((regDX0GSR2.wderr & 0x8) ? 1 : 0),
				((regDX0GSR2.wderr & 0x4) ? 1 : 0),
				((regDX0GSR2.wderr & 0x2) ? 1 : 0),
				((regDX0GSR2.wderr & 0x1) ? 1 : 0));
	}
	printf ("\n");

	printf ("Write bit deskew Warn\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGSR2 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR2_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR2);
		errorindicated += regDX0GSR2.wdwn;
		printf (" %d%d%d%d \t", 
				((regDX0GSR2.wdwn & 0x8) ? 1 : 0),
				((regDX0GSR2.wdwn & 0x4) ? 1 : 0),
				((regDX0GSR2.wdwn & 0x2) ? 1 : 0),
				((regDX0GSR2.wdwn & 0x1) ? 1 : 0));
	}
	printf ("\n");

	printf ("Read eye Center Error\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGSR2 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR2_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR2);
		errorindicated += regDX0GSR2.reerr;
		printf (" %d%d%d%d \t", 
				((regDX0GSR2.reerr & 0x8) ? 1 : 0),
				((regDX0GSR2.reerr & 0x4) ? 1 : 0),
				((regDX0GSR2.reerr & 0x2) ? 1 : 0),
				((regDX0GSR2.reerr & 0x1) ? 1 : 0));
	}
	printf ("\n");

	printf ("Read eye Center Warn\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGSR2 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR2_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR2);
		errorindicated += regDX0GSR2.rewn;
		printf (" %d%d%d%d \t", 
				((regDX0GSR2.rewn & 0x8) ? 1 : 0),
				((regDX0GSR2.rewn & 0x4) ? 1 : 0),
				((regDX0GSR2.rewn & 0x2) ? 1 : 0),
				((regDX0GSR2.rewn & 0x1) ? 1 : 0));
	}
	printf ("\n");

	printf ("Write eye Center Error\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGSR2 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR2_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR2);
		errorindicated += regDX0GSR2.weerr;
		printf (" %d%d%d%d \t", 
				((regDX0GSR2.weerr & 0x8) ? 1 : 0),
				((regDX0GSR2.weerr & 0x4) ? 1 : 0),
				((regDX0GSR2.weerr & 0x2) ? 1 : 0),
				((regDX0GSR2.weerr & 0x1) ? 1 : 0));
	}
	printf ("\n");

	printf ("Write eye Center Warn\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGSR2 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR2_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR2);
		errorindicated += regDX0GSR2.wewn;
		printf (" %d%d%d%d \t", 
				((regDX0GSR2.wewn & 0x8) ? 1 : 0),
				((regDX0GSR2.wewn & 0x4) ? 1 : 0),
				((regDX0GSR2.wewn & 0x2) ? 1 : 0),
				((regDX0GSR2.wewn & 0x1) ? 1 : 0));
	}
	printf ("\n");

	printf ("Static Read Error\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGSR2 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR2_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR2);
		errorindicated += regDX0GSR2.srderr;
		printf (" %d%d%d%d \t", 
				((regDX0GSR2.srderr & 0x8) ? 1 : 0),
				((regDX0GSR2.srderr & 0x4) ? 1 : 0),
				((regDX0GSR2.srderr & 0x2) ? 1 : 0),
				((regDX0GSR2.srderr & 0x1) ? 1 : 0));
	}
	printf ("\n");

	if (errorindicated) {
		printf ("\nERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR\n");
		printf ("ERROR: See above for a training error indicated\n");
		printf ("ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR\n");
	}

	ncr_read32(phyReg, NCP_PHY_RANKIDR_5600, (ncp_uint32_t *)&regRANKIDR);

	printf ("\n***********************************************************\n");
	printf ("************ All Results are based on Rank #%d *************\n", regRANKIDR.rankrid);
	printf ("***********************************************************\n");

	printf ("\n**************** Period Measurement Results *******************\n");
	printf ("\t\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		printf ("Byte %d \t", bytecnt);
	}
	printf ("\n");

	printf ("Master Delay Initial\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnMDLR0 */
		ncr_read32(phyReg, (NCP_PHY_DX0MDLR0_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0MDLR0);
		printf (" 0x%X \t",regDX0MDLR0.iprd);
	}
	printf ("\n");

	printf ("Master Delay Target\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnMDLR0 */
		ncr_read32(phyReg, (NCP_PHY_DX0MDLR0_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0MDLR0);
		printf (" 0x%X \t",regDX0MDLR0.tprd);
	}
	printf ("\n");

	printf ("Master Delay Selected\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnMDLR1 */
		ncr_read32(phyReg, (NCP_PHY_DX0MDLR1_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0MDLR1);
		printf (" 0x%X \t",regDX0MDLR1.mdld);
	}
	printf ("\n");

	printf ("Write Level Period\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGSR0 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR0_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR0);
		printf (" 0x%X \t",regDX0GSR0.wlprd);
	}
	printf ("\n");

	printf ("Read Level Period\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGSR0 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR0_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR0);
		printf (" 0x%X \t",regDX0GSR0.gdqsprd);
	}
	printf ("\n");

	printf ("\n**************** LCDL Training Results *******************\n");
	printf ("\t\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		printf ("Byte %d \t", bytecnt);
	}
	printf ("\n");

	printf ("Write DQS Delay\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnLCDLR0 */
		ncr_read32(phyReg, (NCP_PHY_DX0LCDLR0_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0LCDLR0);
		printf (" 0x%X \t",regDX0LCDLR0.wld);
	}
	printf ("\n");

	printf ("Write Adjust\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGTR0 */
		ncr_read32(phyReg, (NCP_PHY_DX0GTR0_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GTR0);
		printf (" %s \t",((regDX0GTR0.wlsl == 0) ? "-1" :
					(regDX0GTR0.wlsl == 1) ? "-0.5" :
					(regDX0GTR0.wlsl == 2) ? "+-0" :
					(regDX0GTR0.wlsl == 3) ? "+0.5" :
					(regDX0GTR0.wlsl == 4) ? "+1" :
					(regDX0GTR0.wlsl == 5) ? "+1.5" :
					(regDX0GTR0.wlsl == 6) ? "+2" :
					(regDX0GTR0.wlsl == 7) ? "+2.5" :
					(regDX0GTR0.wlsl == 8) ? "+3" :
					(regDX0GTR0.wlsl == 9) ? "+3.5" :
					"ERROR"));
	}
	printf ("\n");

	printf ("Write Data Delay\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnLCDLR1 */
		ncr_read32(phyReg, (NCP_PHY_DX0LCDLR1_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0LCDLR1);
		printf (" 0x%X \t",regDX0LCDLR1.wdqd);
	}
	printf ("\n");

	printf ("DQS Gate Delay\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnLCDLR2 */
		ncr_read32(phyReg, (NCP_PHY_DX0LCDLR2_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0LCDLR2);
		printf (" 0x%X \t",regDX0LCDLR2.dqsgd);
	}
	printf ("\n");

	printf ("DQS Gate Adjust\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGTR0 */
		ncr_read32(phyReg, (NCP_PHY_DX0GTR0_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GTR0);
		if (regDX0GTR0.dgsl == 0) 
		{
			printf (" +-0 \t");
		}
		else 
		{
			printf (" +%.1f \t",((double)regDX0GTR0.dgsl/2));
		}		      
	}
	printf ("\n");

	printf ("Read DQS Delay\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnLCDLR3 */
		ncr_read32(phyReg, (NCP_PHY_DX0LCDLR3_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0LCDLR3);
		printf (" 0x%X \t",regDX0LCDLR3.rdqsd);
	}
	printf ("\n");

	printf ("Read DQSN Delay\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnLCDLR4 */
		ncr_read32(phyReg, (NCP_PHY_DX0LCDLR4_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0LCDLR4);
		printf (" 0x%X \t",regDX0LCDLR4.rdqsnd);
	}
	printf ("\n");

	printf ("\n**************** Other Training Results *******************\n");
	printf ("\t\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		printf ("Byte %d \t", bytecnt);
	}
	printf ("\n");

	printf ("Static Read Delay\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++)
	{
		/* DXnGCR0 */
		ncr_read32(phyReg, (NCP_PHY_DX0GCR0_5600 + (bytecnt * 0x100)), (ncp_uint32_t *)&regDX0GCR0);
		printf (" 0x%X \t",regDX0GCR0.rddly);
	}
	printf ("\n");

	/* VREF training */
	printf ("Host VREF rank0\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++)
	{
		/* DXnGCR5 */
		ncr_read32(phyReg, (NCP_PHY_DX0GCR5_5600 + (bytecnt * 0x100)), (ncp_uint32_t *)&regDX0GCR5);
		printf (" 0x%X \t",regDX0GCR5.dxrefiselr0);
	}
	printf ("\n");

	printf ("Host VREF rank1\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++)
	{
		/* DXnGCR5 */
		ncr_read32(phyReg, (NCP_PHY_DX0GCR5_5600 + (bytecnt * 0x100)), (ncp_uint32_t *)&regDX0GCR5);
		printf (" 0x%X \t",regDX0GCR5.dxrefiselr1);
	}
	printf ("\n");

	printf ("DRAM VREF rank0\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++)
	{
		/* DXnGCR6 */
		ncr_read32(phyReg, (NCP_PHY_DX0GCR6_5600 + (bytecnt * 0x100)), (ncp_uint32_t *)&regDX0GCR6);
		printf (" 0x%X \t",regDX0GCR6.dxdqvrefr0);
	}
	printf ("\n");

	printf ("DRAM VREF rank1\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++)
	{
		/* DXnGCR6 */
		ncr_read32(phyReg, (NCP_PHY_DX0GCR6_5600 + (bytecnt * 0x100)), (ncp_uint32_t *)&regDX0GCR6);
		printf (" 0x%X \t",regDX0GCR6.dxdqvrefr1);
	}
	printf ("\n");

	printf ("\n**************** Read Data bit deskew Results *******************\n");
	printf ("         D  |  D  |  D  |  D  |  D  |  D  |  D  |  D  |  D  |  D  |  D  |\n");
	printf ("         Q  |  Q  |  Q  |  Q  |  Q  |  Q  |  Q  |  Q  |  M  |  Q  |  Q  |\n");
	printf ("         0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |     |  S  |  SN |\n");
	printf ("------------------------------------------------------------------\n");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		printf ("Byte %d ", bytecnt);
		printf ("  ");
		for (bits = 0; bits <= 10; bits++) 
		{
			field = bits % 4;
			/* DXnBDLR3-6 */
			ncr_read32(phyReg, (NCP_PHY_DX0BDLR3_5600 + (bytecnt * 0x100)), &tmp);
			switch (field)
			{
				case 0:
					val = (tmp & 0x3f);
					break;
				case 1:
					val = (tmp & 0x3f00) >> 8;
					break;
				case 2:
					val = (tmp & 0x3f0000) >> 16;
					break;
				case 3:
					val = (tmp & 0x3f000000) >> 24;
					break;
			}
			printf ("%d|  ", val);
		}
		printf ("\n");
	}
	printf ("\n");

	printf ("**************** Write Data bit deskew Results *******************\n");
	printf ("         D  |  D  |  D  |  D  |  D  |  D  |  D  |  D  |  D  |  D  |  O  |\n");
	printf ("         Q  |  Q  |  Q  |  Q  |  Q  |  Q  |  Q  |  Q  |  M  |  Q  |  E  |\n");
	printf ("         0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |     |  S  |     |\n");
	printf ("------------------------------------------------------------------\n");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		printf ("Byte %d ", bytecnt);
		printf ("  ");
		for (bits = 0; bits <= 10; bits++) 
		{
			field = bits % 4;
			/* DXnBDLR0-2 */
			ncr_read32(phyReg, (NCP_PHY_DX0BDLR0_5600 + (bytecnt * 0x100)), &tmp);
			switch (field)
			{
				case 0:
					val = (tmp & 0x3f);
					break;
				case 1:
					val = (tmp & 0x3f00) >> 8;
					break;
				case 2:
					val = (tmp & 0x3f0000) >> 16;
					break;
				case 3:
					val = (tmp & 0x3f000000) >> 24;
					break;
			}
			printf ("%d|  ", val);
		}
		printf ("\n");
	}
	printf ("\n");

	/* Trained Registers
#ACLCDLR0
#ACMDLR0
#ACMDLR1
#DXnGTR0
#DXnGTR1
#DXnGTR2
#DXnGTR3
#DXnGSR0
#DXnGSR1
#DXnGSR2
#DXnGSR3
#DXnGSR4
#DXnGSR5
	 */

	NCP_RETURN_LABEL
		return ncpStatus;
}

ncp_st_t
ncp_sm_ddr4_phy_training_error_check(
		ncp_dev_hdl_t   dev,
		ncp_uint32_t    smNode)
{
	ncp_st_t		ncpStatus = NCP_ST_SUCCESS;
	ncp_region_id_t 	phyReg 	= NCP_REGION_ID(smNode, NCP_SYSMEM_TGT_PHY);

	ncp_phy_PGSR0_5600_t regPGSR0 = {0};

	/* Checking Gate Training Error */
	ncr_read32(phyReg, NCP_PHY_PGSR0_5600, (ncp_uint32_t *)&regPGSR0);

	/* ncpStatus = return <appropriate return code TBD> */

	if (regPGSR0.verr)
	{
		errprintf("VREF Training Error\n");
		ncpStatus = NCP_ST_ERROR;
	}

	if (regPGSR0.zcerr)
	{
		errprintf("Impedance Calibration Error\n");
		ncpStatus = NCP_ST_ERROR;
	}

	if (regPGSR0.wlerr)
	{
		errprintf("Write Leveling Error\n");
		ncpStatus = NCP_ST_ERROR;
	}

	if (regPGSR0.qsgerr)
	{
		errprintf("DQS Gate Training Error\n");
		ncpStatus = NCP_ST_ERROR;
	}

	if (regPGSR0.wlaerr)
	{
		errprintf("Write Leveling Adjustment Error\n");
		ncpStatus = NCP_ST_ERROR;
	}

	if (regPGSR0.rderr)
	{
		errprintf("Read Bit Deskew Error\n");
		ncpStatus = NCP_ST_ERROR;
	}

	if (regPGSR0.wderr)
	{
		errprintf("Write Bit Deskew Error\n");
		ncpStatus = NCP_ST_ERROR;
	}

	if (regPGSR0.reerr)
	{
		errprintf("Read Eye Training Error\n");
		ncpStatus = NCP_ST_ERROR;
	}

	if (regPGSR0.weerr)
	{
		errprintf("Write Eye Training Error\n");
		ncpStatus = NCP_ST_ERROR;
	}

	if (regPGSR0.caerr)
	{
		errprintf("CA Training Error\n");
		ncpStatus = NCP_ST_ERROR;
	}

	if (regPGSR0.cawrn)
	{
		errprintf("CA Training Warning\n");
	}

	if (regPGSR0.srderr)
	{
		errprintf("Static Read Error\n");
		ncpStatus = NCP_ST_ERROR;
	}

	NCP_RETURN_LABEL
		return ncpStatus;
}

ncp_st_t
ncp_sm_ddr4_phy_training(
		ncp_dev_hdl_t   dev,
		ncp_uint32_t    smNode,
		ncp_sm_parms_t *parms)
{
	ncp_st_t		ncpStatus = NCP_ST_SUCCESS;
	unsigned int		tmp = 0;
	ncp_region_id_t 	phyReg 	= NCP_REGION_ID(smNode, NCP_SYSMEM_TGT_PHY);

	ncp_phy_DTCR0_5600_t regDTCR0 = {0};
	ncp_phy_DTCR1_5600_t regDTCR1 = {0};
	/*ncp_phy_DTAR0_5600_t regDTAR0 = {0};*/
	ncp_phy_PIR_5600_t regPIR = {0};
	ncp_phy_PGCR0_5600_t regPGCR0 = {0};
	ncp_phy_PGCR3_5600_t regPGCR3 = {0};
	ncp_phy_PGCR1_5600_t regPGCR1 = {0};
	ncp_phy_BISTAR1_5600_t regBISTAR1 = {0};
	ncp_phy_DXCCR_5600_t regDXCCR = {0};
	ncp_phy_VTCR1_5600_t regVTCR1 = {0};


	/* PGCR1 */
	ncr_read32(phyReg, NCP_PHY_PGCR1_5600, (ncp_uint32_t *)&regPGCR1);
	/* Enables if set the PUB to control the interface to the PHY and SDRAM.
	 * In this mode the DFI commands from the controller are ignored. The bit must
	 * be set to 0 after the system determines it is convenient to pass control of the DFI
	 * bus to the controller. When set to 0 the DFI interface has control of the PHY and SDRAM
	 * interface except when trigerring pub operations such as BIST, DCU or data training.
	 */
	regPGCR1.pubmode = 0x1;
	ncr_write32(phyReg, NCP_PHY_PGCR1_5600, *((ncp_uint32_t *)&regPGCR1));

	/* ZQCR set asymmetric ODT based on number of islands ZQnDR regs */
	ncr_read32(phyReg, NCP_PHY_RIDR_5600, &tmp);

#if 0

	for (i = 0; i < 4; i++)
	{
		/* ZQCR set asymmetric ODT (based on number of islands) ZQnDR regs */
		ncr_read32(phyReg, (NCP_PHY_ZQ0DR_5600 + (0x10 * i)), (ncp_uint32_t *)&regZQ0DR);
		regZQ0DR.odt_zden = 0x1;
		regZQ0DR.zdata &= ~(0x1fc000);
		ncr_write32(phyReg, (NCP_PHY_ZQ0DR_5600 + (0x10 * i)), *((ncp_uint32_t *)&regZQ0DR));
	}

	/* Force ZQ calibration- this was already done in phy_init */
	ncr_read32(phyReg, NCP_PHY_ZQCR_5600, (ncp_uint32_t *)&regZQCR);
	regZQCR.force_zcal_vt_update = 0x1;
	ncr_write32(phyReg, NCP_PHY_ZQCR_5600, *((ncp_uint32_t *)&regZQCR));
	regZQCR.force_zcal_vt_update = 0x0;
	ncr_write32(phyReg, NCP_PHY_ZQCR_5600, *((ncp_uint32_t *)&regZQCR));
#endif

	/* Started Data Training */
	/*************************/

	/* DTCR0 */
	ncr_read32(phyReg, NCP_PHY_DTCR0_5600, (ncp_uint32_t *)&regDTCR0);
	regDTCR0.dtrptn = 0x7; /* Data Training Repeat Number */
	regDTCR0.dtmpr = (parms->dram_class == NCP_SM_DDR4_MODE) ? 0x1 : 0x0; /* Data Training using MPR */
	regDTCR0.dtcmpd = 0x1; /* DQS Gate training compare data */
	regDTCR0.rfshent = 0x1; /* previously 0x9 : Assuming PHY refresh enabled during training */
	regDTCR0.dtwbddm = 0x1; /* Data training write bit deskew data mask */
	regDTCR0.dtbdc = 0x1; /* Data training bit deskew centering enables */
	regDTCR0.dtdrs = 0x0; /* DTDRS Data training debug rank select */
	regDTCR0.dtdbs = 0x0; /* DTDBS Data training debug byte select */
	/* RDBI deskewing is not performed */
	if (parms->dbi_rd_en)
	{
		regDTCR0.dtrdbitr = 0x2;
	}
	else
	{
		regDTCR0.dtrdbitr = 0x0;
	}
	regDTCR0.dtden = 0x0; /* DTDEN Data training debug enable */
	regDTCR0.dtdstp = 0x0; /* DTDSTP Data training debug step */
	regDTCR0.dtexd = 0x0; /* DTEXD Data training extended write DQ */
	regDTCR0.dtexg = 0x0; /* DTEXG Data training early/extended gate */
	regDTCR0.rfshdt = 0x0; /* Assuming PHY refresh enabled during training */
	ncr_write32(phyReg, NCP_PHY_DTCR0_5600, *((ncp_uint32_t *)&regDTCR0));

	/* DTCR1 */
	ncr_read32(phyReg, NCP_PHY_DTCR1_5600, (ncp_uint32_t *)&regDTCR1);
	regDTCR1.bsten = 0x1;
	regDTCR1.rdlvlen = 0x1;
	regDTCR1.rdprmvl_trn = 0x1;
	regDTCR1.rdlvlgs = 0x3;
	regDTCR1.rdlvlgdiff = 0x2;
	regDTCR1.dtrank = 0x0;
	regDTCR1.ranken = parms->topology; /* Each bit will enable each rank */
	ncr_write32(phyReg, NCP_PHY_DTCR1_5600, *((ncp_uint32_t *)&regDTCR1));

	/* DTAR0 */
#if 0	/* check if this is not needed */
	ncr_read32(phyReg, NCP_PHY_DTAR0_5600, (ncp_uint32_t *)&regDTAR0);
	regDTAR0.mprloc = 0x1;
	ncr_write32(phyReg, NCP_PHY_DTAR0_5600, *((ncp_uint32_t *)&regDTAR0));
#endif

	/* Used by VREF training. BIST */
	ncr_write32(phyReg, NCP_PHY_BISTRR_5600, 0x007e4008);
	ncr_write32(phyReg, NCP_PHY_BISTMSKR1_5600, 0x01000000); /* CIDMSK */

	/* BISTAR1 */
	ncr_read32(phyReg, NCP_PHY_BISTAR1_5600, (ncp_uint32_t *)&regBISTAR1);
	regBISTAR1.brank = 0x0;/* was parms->topology - 1;*/
	regBISTAR1.bainc = 0x8; /* for BL8 lower bits should be 000 to mark beginning of burst boundary */
	regBISTAR1.bmrank = parms->num_ranks_per_interface - 1; /* BIST Maximum rank */
	ncr_write32(phyReg, NCP_PHY_BISTAR1_5600, *((ncp_uint32_t *)&regBISTAR1));

	ncr_write32(phyReg, NCP_PHY_BISTAR2_5600, 0x000000c8); /* 31:28 BIST max bank address, 11:0 BIST max col address */
	ncr_write32(phyReg, NCP_PHY_BISTAR4_5600, 0x00003fff); /* 17:0 is BIST max row address */
	ncr_write32(phyReg, NCP_PHY_BISTUDPR_5600, 0xa5a5a5a5); /* user-data-patter 2 16-bits */

	/* VTCR1 */
	ncr_read32(phyReg, NCP_PHY_VTCR1_5600, (ncp_uint32_t *)&regVTCR1);
	regVTCR1.ENUM = 0x1; /* number of LCDL eye points for which training is repeated */
	regVTCR1.vwcr = 0xf; /* VREF word count */
	regVTCR1.hvss = 0x0; /* host vref step size */
	regVTCR1.shrnk = 0x0; /* static host Vref rank value */
	regVTCR1.shren = 0x1; /* static host Vref rank enable */
	ncr_write32(phyReg, NCP_PHY_VTCR1_5600, *((ncp_uint32_t *)&regVTCR1));

	/* PIR */
	if ((parms->packedPHYTrainingOptions >> 9) & 0x1)
	{
		ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
		regPIR.init = 1; 
		/* Actual init involves selection among the following steps:
		 * ZCAL: impedance calibration
		 * CA: CA training
		 * PLLINIT: pll init (pll power, reset, gear shift, wait for lock)
		 * DCAL: digital delay line calibration
		 * PHYRST: reset the AC and DATX8
		 * DRAMRST: reset, wait 200us
		 * DRAMINIT: executes DRAM init sequence
		 * WL: write leveling
		 * QSGATE: read dqs gate training
		 * WLADJ: write leveling adjust
		 * RDDSKW: read data bit deskew
		 * WRDSKW: write data bit deskew
		 * RDEYE: read data eye training
		 * WREYE: write data eye training
		 *
		 *
		 * <specials are>
		 * SRD: static read training
		 * VREF: vref training
		 * CTLDINIT: controller performs DRAM init
		 * RDIMMINIT: rdimm init
		 */
		regPIR.zcal = 0; 
		regPIR.ca = 0; 
		regPIR.pllinit = 0; 
		regPIR.dcal = 0; 
		regPIR.phyrst = 0; 
		regPIR.dramrst = 0; 
		regPIR.draminit = 0; 
		regPIR.wl = 1; 
		regPIR.qsgate = 0; 
		regPIR.wladj = 0; 
		regPIR.rddskw = 0; 
		regPIR.wrdskw = 0; 
		regPIR.rdeye = 0; 
		regPIR.wreye = 0; 
		regPIR.srd = 0; 
		regPIR.vref = 0; 
		regPIR.ctldinit = 0;  /* should this be 1 ?. */
		regPIR.rdimminit = 0; 
		ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));

		/* Check the General Status register */

		/* poll for idone(bit 0) */
		ncpStatus = (ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0x21,  0x21,  1000,  10000));

		if (ncpStatus == NCP_ST_POLL_TIMEOUT)
		{
			ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
			errprintf("POLL timeout while waiting for write levelling training to complete [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
			return ncpStatus;
		}

		/* Checking for Error's */
		ncpStatus = (ncp_sm_ddr4_phy_training_error_check(dev, smNode));
		if (ncpStatus == NCP_ST_ERROR)
		{
			return ncpStatus;
		}

		ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
		dbgprintf("SUCCESS: result while waiting for write levelling training to complete [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
	}

	/* work-around for Star 9000952604 */
	/* Disable data training data compare by writing DTCR0[7]=1'b0 (DTCMPD) and enable read preamble
	 * training enable by writing DTCR1[2]=1'b1 (RDPRMBL_TRN) */

	ncr_read32(phyReg, NCP_PHY_DTCR0_5600, (ncp_uint32_t *)&regDTCR0);
	regDTCR0.dtcmpd = 0x0;
	ncr_write32(phyReg, NCP_PHY_DTCR0_5600, *((ncp_uint32_t *)&regDTCR0));

	ncr_read32(phyReg, NCP_PHY_DTCR1_5600, (ncp_uint32_t *)&regDTCR1);
	regDTCR1.rdprmvl_trn = 0x1;
	ncr_write32(phyReg, NCP_PHY_DTCR1_5600, *((ncp_uint32_t *)&regDTCR1));

	/* select to run basic gate training and read levelling by writing DTCR1[0]=1'b1 BSTEN and
	 * DTCR1[1]=1'b1 RDLVLEN */
	ncr_read32(phyReg, NCP_PHY_DTCR1_5600, (ncp_uint32_t *)&regDTCR1);
	regDTCR1.bsten = 0x1;
	regDTCR1.rdlvlen = 0x1;
	ncr_write32(phyReg, NCP_PHY_DTCR1_5600, *((ncp_uint32_t *)&regDTCR1));

	/* Disable QS counter enable by writing DXCCR[22]=1'b0 QSCNTEN */
	ncr_read32(phyReg, NCP_PHY_DXCCR_5600, (ncp_uint32_t *)&regDXCCR);
	regDXCCR.qscnten = 0x0;
	ncr_write32(phyReg, NCP_PHY_DXCCR_5600, *((ncp_uint32_t *)&regDXCCR));

	/* Select to run Read DQS Gate training */
	/*************************************/
	if ((parms->packedPHYTrainingOptions >> 10) & 0x1)
	{
		/* PIR */
		ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
		regPIR.init = 1; 
		/* Actual init involves selection among the following steps:
		 * ZCAL: impedance calibration
		 * CA: CA training
		 * PLLINIT: pll init (pll power, reset, gear shift, wait for lock)
		 * DCAL: digital delay line calibration
		 * PHYRST: reset the AC and DATX8
		 * DRAMRST: reset, wait 200us
		 * DRAMINIT: executes DRAM init sequence
		 * WL: write leveling
		 * QSGATE: read dqs gate training
		 * WLADJ: write leveling adjust
		 * RDDSKW: read data bit deskew
		 * WRDSKW: write data bit deskew
		 * RDEYE: read data eye training
		 * WREYE: write data eye training
		 *
		 *
		 * <specials are>
		 * SRD: static read training
		 * VREF: vref training
		 * CTLDINIT: controller performs DRAM init
		 * RDIMMINIT: rdimm init
		 */
		regPIR.zcal = 0; 
		regPIR.ca = 0; 
		regPIR.pllinit = 0; 
		regPIR.dcal = 0; 
		regPIR.phyrst = 0; 
		regPIR.dramrst = 0; 
		regPIR.draminit = 0; 
		regPIR.wl = 0; 
		regPIR.qsgate = 1; 
		regPIR.wladj = 0; 
		regPIR.rddskw = 0; 
		regPIR.wrdskw = 0; 
		regPIR.rdeye = 0; 
		regPIR.wreye = 0; 
		regPIR.srd = 0; 
		regPIR.vref = 0; 
		regPIR.ctldinit = 0;
		regPIR.rdimminit = 0; 
		ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));

		/* Check the General Status register */

		/* poll for idone(bit 0) */
		ncpStatus = (ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0x41,  0x41,  1000,  10000));

		if (ncpStatus == NCP_ST_POLL_TIMEOUT)
		{
			ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
			errprintf("POLL timeout while waiting for read DQS gate training to complete [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
			return ncpStatus;
		}

		/* Checking for Error's */
		ncpStatus = (ncp_sm_ddr4_phy_training_error_check(dev, smNode));
		if (ncpStatus == NCP_ST_ERROR)
		{
			return ncpStatus;
		}

		ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
		dbgprintf("SUCCESS: result while waiting for read DQS gate training to complete [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
	}

	/* Enable QS counter enable by writing DXCCR[22]=1'b1 QSCNTEN */
	ncr_read32(phyReg, NCP_PHY_DXCCR_5600, (ncp_uint32_t *)&regDXCCR);
	regDXCCR.qscnten = 0x1;
	ncr_write32(phyReg, NCP_PHY_DXCCR_5600, *((ncp_uint32_t *)&regDXCCR));

	/* Perform Write Level Adjustment */
	/*************************************/
	if ((parms->packedPHYTrainingOptions >> 11) & 0x1)
	{
		/* PIR */
		ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
		regPIR.init = 1; 
		/* Actual init involves selection among the following steps:
		 * ZCAL: impedance calibration
		 * CA: CA training
		 * PLLINIT: pll init (pll power, reset, gear shift, wait for lock)
		 * DCAL: digital delay line calibration
		 * PHYRST: reset the AC and DATX8
		 * DRAMRST: reset, wait 200us
		 * DRAMINIT: executes DRAM init sequence
		 * WL: write leveling
		 * QSGATE: read dqs gate training
		 * WLADJ: write leveling adjust
		 * RDDSKW: read data bit deskew
		 * WRDSKW: write data bit deskew
		 * RDEYE: read data eye training
		 * WREYE: write data eye training
		 *
		 *
		 * <specials are>
		 * SRD: static read training
		 * VREF: vref training
		 * CTLDINIT: controller performs DRAM init
		 * RDIMMINIT: rdimm init
		 */
		regPIR.zcal = 0; 
		regPIR.ca = 0; 
		regPIR.pllinit = 0; 
		regPIR.dcal = 0; 
		regPIR.phyrst = 0; 
		regPIR.dramrst = 0; 
		regPIR.draminit = 0; 
		regPIR.wl = 0; 
		regPIR.qsgate = 0; 
		regPIR.wladj = 1; 
		regPIR.rddskw = 0; 
		regPIR.wrdskw = 0; 
		regPIR.rdeye = 0; 
		regPIR.wreye = 0; 
		regPIR.srd = 0; 
		regPIR.vref = 0; 
		regPIR.ctldinit = 0;
		regPIR.rdimminit = 0; 
		ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));

		/* Check the General Status register */

		/* poll for idone(bit 0) */
		ncpStatus = (ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0x81,  0x81,  1000,  10000));

		if (ncpStatus == NCP_ST_POLL_TIMEOUT)
		{
			ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
			errprintf("POLL timeout while waiting for write level adjustment to complete [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
			return ncpStatus;
		}

		/* Checking for Error's */
		ncpStatus = (ncp_sm_ddr4_phy_training_error_check(dev, smNode));
		if (ncpStatus == NCP_ST_ERROR)
		{
			return ncpStatus;
		}

		ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
		dbgprintf("SUCCESS: result while waiting for write level adjustment to complete [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
	}


	/* Perform Static Read Data Training */
	/*************************************/

	/* PGCR0 */
	ncr_read32(phyReg, NCP_PHY_PGCR0_5600, (ncp_uint32_t *)&regPGCR0);
	/* PHY FIFO Reset: 0 resets AC and DATX8 FIFO's without resetting PUB logic.
	 * write 1 to de-assert the reset later */
	regPGCR0.phyfrst = 0x0; 
	ncr_write32(phyReg, NCP_PHY_PGCR0_5600, *((ncp_uint32_t *)&regPGCR0));

	/* PGCR3 */
	ncr_read32(phyReg, NCP_PHY_PGCR3_5600, (ncp_uint32_t *)&regPGCR3);
	regPGCR3.rdmode = 0x1;  /* Static read response */
	ncr_write32(phyReg, NCP_PHY_PGCR3_5600, *((ncp_uint32_t *)&regPGCR3));

	/* PGCR0 */
	ncr_read32(phyReg, NCP_PHY_PGCR0_5600, (ncp_uint32_t *)&regPGCR0);
	/* PHY FIFO Reset: 0 resets AC and DATX8 FIFO's without resetting PUB logic.
	 * write 1 to de-assert the reset later */
	regPGCR0.phyfrst = 0x1; 
	ncr_write32(phyReg, NCP_PHY_PGCR0_5600, *((ncp_uint32_t *)&regPGCR0));

	/* Start SRD trainings */
	/*****************************/
	if ((parms->packedPHYTrainingOptions >> 16) & 0x1)
	{
		/* PIR */
		ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
		regPIR.init = 1; 
		/* Actual init involves selection among the following steps:
		 * ZCAL: impedance calibration
		 * CA: CA training
		 * PLLINIT: pll init (pll power, reset, gear shift, wait for lock)
		 * DCAL: digital delay line calibration
		 * PHYRST: reset the AC and DATX8
		 * DRAMRST: reset, wait 200us
		 * DRAMINIT: executes DRAM init sequence
		 * WL: write leveling
		 * QSGATE: read dqs gate training
		 * WLADJ: write leveling adjust
		 * RDDSKW: read data bit deskew
		 * WRDSKW: write data bit deskew
		 * RDEYE: read data eye training
		 * WREYE: write data eye training
		 *
		 *
		 * <specials are>
		 * SRD: static read training
		 * VREF: vref training
		 * CTLDINIT: controller performs DRAM init
		 * RDIMMINIT: rdimm init
		 */
		regPIR.zcal = 0; 
		regPIR.ca = 0; 
		regPIR.pllinit = 0; 
		regPIR.dcal = 0; 
		regPIR.phyrst = 0; 
		regPIR.dramrst = 0; 
		regPIR.draminit = 0; 
		regPIR.wl = 0; 
		regPIR.qsgate = 0; 
		regPIR.wladj = 0; 
		regPIR.rddskw = 0; 
		regPIR.wrdskw = 0; 
		regPIR.rdeye = 0; 
		regPIR.wreye = 0; 
		regPIR.srd = 1; 
		regPIR.vref = 0; 
		regPIR.ctldinit = 0; 
		regPIR.rdimminit = 0; 
		ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));

		/* Check the General Status register */

		/* poll for idone(bit 0) */
		ncpStatus = (ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0x2001,  0x2001,  1000,  10000));

		if (ncpStatus == NCP_ST_POLL_TIMEOUT)
		{
			ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
			errprintf("POLL timeout while SRD training [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
			return ncpStatus;
		}

		/* Checking for Error's */
		ncpStatus = (ncp_sm_ddr4_phy_training_error_check(dev, smNode));
		if (ncpStatus == NCP_ST_ERROR)
		{
			return ncpStatus;
		}

		ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
		dbgprintf("SUCCESS: result while waiting for srd training to complete [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
	}

	/* Read Data Bit Deskew Training */
	/*********************************/
	if ((parms->packedPHYTrainingOptions >> 12) & 0x1)
	{
		/* PIR */
		ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
		regPIR.init = 1; 
		/* Actual init involves selection among the following steps:
		 * ZCAL: impedance calibration
		 * CA: CA training
		 * PLLINIT: pll init (pll power, reset, gear shift, wait for lock)
		 * DCAL: digital delay line calibration
		 * PHYRST: reset the AC and DATX8
		 * DRAMRST: reset, wait 200us
		 * DRAMINIT: executes DRAM init sequence
		 * WL: write leveling
		 * QSGATE: read dqs gate training
		 * WLADJ: write leveling adjust
		 * RDDSKW: read data bit deskew
		 * WRDSKW: write data bit deskew
		 * RDEYE: read data eye training
		 * WREYE: write data eye training
		 *
		 *
		 * <specials are>
		 * SRD: static read training
		 * VREF: vref training
		 * CTLDINIT: controller performs DRAM init
		 * RDIMMINIT: rdimm init
		 */
		regPIR.zcal = 0; 
		regPIR.ca = 0; 
		regPIR.pllinit = 0; 
		regPIR.dcal = 0; 
		regPIR.phyrst = 0; 
		regPIR.dramrst = 0; 
		regPIR.draminit = 0; 
		regPIR.wl = 0; 
		regPIR.qsgate = 0; 
		regPIR.wladj = 0; 
		regPIR.rddskw = 1; 
		regPIR.wrdskw = 0; 
		regPIR.rdeye = 0; 
		regPIR.wreye = 0; 
		regPIR.srd = 0; 
		regPIR.vref = 0; 
		regPIR.ctldinit = 0; 
		regPIR.rdimminit = 0; 
		ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));

		/* Check the General Status register */

		/* poll for idone(bit 0) */
		ncpStatus = (ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0x101,  0x101,  1000,  10000));

		if (ncpStatus == NCP_ST_POLL_TIMEOUT)
		{
			ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
			errprintf("POLL timeout while read data bit deskew training [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
			return ncpStatus;
		}

		/* Checking for Error's */
		ncpStatus = (ncp_sm_ddr4_phy_training_error_check(dev, smNode));
		if (ncpStatus == NCP_ST_ERROR)
		{
			return ncpStatus;
		}

		ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
		dbgprintf("SUCCESS: result while waiting for read deskew training to complete [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
	}

	/* Write Data Bit Deskew Training */
	/**********************************/
	if ((parms->packedPHYTrainingOptions >> 13) & 0x1)
	{
		/* PIR */
		ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
		regPIR.init = 1; 
		/* Actual init involves selection among the following steps:
		 * ZCAL: impedance calibration
		 * CA: CA training
		 * PLLINIT: pll init (pll power, reset, gear shift, wait for lock)
		 * DCAL: digital delay line calibration
		 * PHYRST: reset the AC and DATX8
		 * DRAMRST: reset, wait 200us
		 * DRAMINIT: executes DRAM init sequence
		 * WL: write leveling
		 * QSGATE: read dqs gate training
		 * WLADJ: write leveling adjust
		 * RDDSKW: read data bit deskew
		 * WRDSKW: write data bit deskew
		 * RDEYE: read data eye training
		 * WREYE: write data eye training
		 *
		 *
		 * <specials are>
		 * SRD: static read training
		 * VREF: vref training
		 * CTLDINIT: controller performs DRAM init
		 * RDIMMINIT: rdimm init
		 */
		regPIR.zcal = 0; 
		regPIR.ca = 0; 
		regPIR.pllinit = 0; 
		regPIR.dcal = 0; 
		regPIR.phyrst = 0; 
		regPIR.dramrst = 0; 
		regPIR.draminit = 0; 
		regPIR.wl = 0; 
		regPIR.qsgate = 0; 
		regPIR.wladj = 0; 
		regPIR.rddskw = 0; 
		regPIR.wrdskw = 1; 
		regPIR.rdeye = 0; 
		regPIR.wreye = 0; 
		regPIR.srd = 0; 
		regPIR.vref = 0; 
		regPIR.ctldinit = 0; 
		regPIR.rdimminit = 0; 
		ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));

		/* Check the General Status register */

		/* poll for idone(bit 0) */
		ncpStatus = (ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0x201,  0x201,  1000,  10000));

		if (ncpStatus == NCP_ST_POLL_TIMEOUT)
		{
			ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
			errprintf("POLL timeout while write data bit deskew training [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
			return ncpStatus;
		}

		/* Checking for Error's */
		ncpStatus = (ncp_sm_ddr4_phy_training_error_check(dev, smNode));
		if (ncpStatus == NCP_ST_ERROR)
		{
			return ncpStatus;
		}

		ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
		dbgprintf("SUCCESS: result while waiting for write deskew training to complete [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
	}

	/* Read Data Eye Training */
	/**********************************/
	/* PIR */
	if ((parms->packedPHYTrainingOptions >> 14) & 0x1)
	{
		ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
		regPIR.init = 1; 
		/* Actual init involves selection among the following steps:
		 * ZCAL: impedance calibration
		 * CA: CA training
		 * PLLINIT: pll init (pll power, reset, gear shift, wait for lock)
		 * DCAL: digital delay line calibration
		 * PHYRST: reset the AC and DATX8
		 * DRAMRST: reset, wait 200us
		 * DRAMINIT: executes DRAM init sequence
		 * WL: write leveling
		 * QSGATE: read dqs gate training
		 * WLADJ: write leveling adjust
		 * RDDSKW: read data bit deskew
		 * WRDSKW: write data bit deskew
		 * RDEYE: read data eye training
		 * WREYE: write data eye training
		 *
		 *
		 * <specials are>
		 * SRD: static read training
		 * VREF: vref training
		 * CTLDINIT: controller performs DRAM init
		 * RDIMMINIT: rdimm init
		 */
		regPIR.zcal = 0; 
		regPIR.ca = 0; 
		regPIR.pllinit = 0; 
		regPIR.dcal = 0; 
		regPIR.phyrst = 0; 
		regPIR.dramrst = 0; 
		regPIR.draminit = 0; 
		regPIR.wl = 0; 
		regPIR.qsgate = 0; 
		regPIR.wladj = 0; 
		regPIR.rddskw = 0; 
		regPIR.wrdskw = 0; 
		regPIR.rdeye = 1; 
		regPIR.wreye = 0; 
		regPIR.srd = 0; 
		regPIR.vref = 0; 
		regPIR.ctldinit = 0; 
		regPIR.rdimminit = 0; 
		ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));

		/* Check the General Status register */

		/* poll for idone(bit 0) */
		ncpStatus = (ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0x401,  0x401,  1000,  10000));

		if (ncpStatus == NCP_ST_POLL_TIMEOUT)
		{
			ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
			errprintf("POLL timeout while read data eye training [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
			return ncpStatus;
		}

		/* Checking for Error's */
		ncpStatus = (ncp_sm_ddr4_phy_training_error_check(dev, smNode));
		if (ncpStatus == NCP_ST_ERROR)
		{
			return ncpStatus;
		}

		ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
		dbgprintf("SUCCESS: result while waiting for read eye training to complete [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
	}

	/* Write Data Eye Training */
	/**********************************/
	if ((parms->packedPHYTrainingOptions >> 15) & 0x1)
	{
		/* PIR */
		ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
		regPIR.init = 1; 
		/* Actual init involves selection among the following steps:
		 * ZCAL: impedance calibration
		 * CA: CA training
		 * PLLINIT: pll init (pll power, reset, gear shift, wait for lock)
		 * DCAL: digital delay line calibration
		 * PHYRST: reset the AC and DATX8
		 * DRAMRST: reset, wait 200us
		 * DRAMINIT: executes DRAM init sequence
		 * WL: write leveling
		 * QSGATE: read dqs gate training
		 * WLADJ: write leveling adjust
		 * RDDSKW: read data bit deskew
		 * WRDSKW: write data bit deskew
		 * RDEYE: read data eye training
		 * WREYE: write data eye training
		 *
		 *
		 * <specials are>
		 * SRD: static read training
		 * VREF: vref training
		 * CTLDINIT: controller performs DRAM init
		 * RDIMMINIT: rdimm init
		 */
		regPIR.zcal = 0; 
		regPIR.ca = 0; 
		regPIR.pllinit = 0; 
		regPIR.dcal = 0; 
		regPIR.phyrst = 0; 
		regPIR.dramrst = 0; 
		regPIR.draminit = 0; 
		regPIR.wl = 0; 
		regPIR.qsgate = 0; 
		regPIR.wladj = 0; 
		regPIR.rddskw = 0; 
		regPIR.wrdskw = 0; 
		regPIR.rdeye = 0; 
		regPIR.wreye = 1; 
		regPIR.srd = 0; 
		regPIR.vref = 0; 
		regPIR.ctldinit = 0; 
		regPIR.rdimminit = 0; 
		ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));

		/* Check the General Status register */

		/* poll for idone(bit 0) */
		ncpStatus = (ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0x801,  0x801,  1000,  10000));

		if (ncpStatus == NCP_ST_POLL_TIMEOUT)
		{
			ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
			errprintf("POLL timeout while write data eye training [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
			return ncpStatus;
		}

		/* Checking for Error's */
		ncpStatus = (ncp_sm_ddr4_phy_training_error_check(dev, smNode));
		if (ncpStatus == NCP_ST_ERROR)
		{
			return ncpStatus;
		}

		ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
		dbgprintf("SUCCESS: result while waiting for write eye training to complete [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
	}

	/* VREF Training */
	/*****************/
	if ((parms->packedPHYTrainingOptions >> 17) & 0x1)
	{
		/* PIR */
		ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
		regPIR.init = 1; 
		/* Actual init involves selection among the following steps:
		 * ZCAL: impedance calibration
		 * CA: CA training
		 * PLLINIT: pll init (pll power, reset, gear shift, wait for lock)
		 * DCAL: digital delay line calibration
		 * PHYRST: reset the AC and DATX8
		 * DRAMRST: reset, wait 200us
		 * DRAMINIT: executes DRAM init sequence
		 * WL: write leveling
		 * QSGATE: read dqs gate training
		 * WLADJ: write leveling adjust
		 * RDDSKW: read data bit deskew
		 * WRDSKW: write data bit deskew
		 * RDEYE: read data eye training
		 * WREYE: write data eye training
		 *
		 *
		 * <specials are>
		 * SRD: static read training
		 * VREF: vref training
		 * CTLDINIT: controller performs DRAM init
		 * RDIMMINIT: rdimm init
		 */
		regPIR.zcal = 0; 
		regPIR.ca = 0; 
		regPIR.pllinit = 0; 
		regPIR.dcal = 0; 
		regPIR.phyrst = 0; 
		regPIR.dramrst = 0; 
		regPIR.draminit = 0; 
		regPIR.wl = 0; 
		regPIR.qsgate = 0; 
		regPIR.wladj = 0; 
		regPIR.rddskw = 0; 
		regPIR.wrdskw = 0; 
		regPIR.rdeye = 0; 
		regPIR.wreye = 0; 
		regPIR.srd = 0; 
		regPIR.vref = 1; 
		regPIR.ctldinit = 0; 
		regPIR.rdimminit = 0; 
		ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));

		/* Check the General Status register */

		/* poll for idone(bit 0) */
		ncpStatus = (ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0x4001,  0x4001,  1000,  10000));

		if (ncpStatus == NCP_ST_POLL_TIMEOUT)
		{
			ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
			errprintf("POLL timeout while VREF training [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
			return ncpStatus;
		}

		/* Checking for Error's */
		ncpStatus = (ncp_sm_ddr4_phy_training_error_check(dev, smNode));
		if (ncpStatus == NCP_ST_ERROR)
		{
			return ncpStatus;
		}

		ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
		dbgprintf("SUCCESS: result while waiting for vref training to complete [line:%d] PGSR0= 0x%x\n",__LINE__, tmp);
	}

	ncr_read32(phyReg, NCP_PHY_VTDR_5600, &tmp);
	/*dbgprintf("After VREF training VTDR result = 0x%x\n",tmp);*/

	ncr_read32(phyReg, NCP_PHY_DTCR0_5600, (ncp_uint32_t *)&regDTCR0);
	regDTCR0.rfshdt = 0x9; /* Assuming PHY refresh enabled during training */
	ncr_write32(phyReg, NCP_PHY_DTCR0_5600, *((ncp_uint32_t *)&regDTCR0));

	/* PGCR1 */
	ncr_read32(phyReg, NCP_PHY_PGCR1_5600, (ncp_uint32_t *)&regPGCR1);
	/* Enables if set the PUB to control the interface to the PHY and SDRAM.
	 * In this mode the DFI commands from the controller are ignored. The bit must
	 * be set to 0 after the system determines it is convenient to pass control of the DFI
	 * bus to the controller. When set to 0 the DFI interface has control of the PHY and SDRAM
	 * interface except when trigerring pub operations such as BIST, DCU or data training.
	 */
	regPGCR1.pubmode = 0x0;
	ncr_write32(phyReg, NCP_PHY_PGCR1_5600, *((ncp_uint32_t *)&regPGCR1));

	NCP_RETURN_LABEL
		return ncpStatus;
}

ncp_st_t
ncp_sm_ddr4_phy_init(
		ncp_dev_hdl_t   dev,
		ncp_uint32_t    smNode,
		ncp_sm_parms_t *parms,
		ncp_common_timing_parameters_t *ctm)
{
	ncp_st_t		ncpStatus = NCP_ST_SUCCESS;
	ncp_region_id_t 	ctlReg  = NCP_REGION_ID(smNode, NCP_SYSMEM_TGT_DENALI);
	ncp_region_id_t 	phyReg 	= NCP_REGION_ID(smNode, NCP_SYSMEM_TGT_PHY);
	unsigned int		i = 0;
	unsigned int		tmp = 0;


	ncp_phy_PTR3_5600_t regPTR3 = {0};
	ncp_phy_PTR4_5600_t regPTR4 = {0};
	ncp_phy_DTPR0_5600_t regDTPR0 = {0};
	ncp_phy_DTPR1_5600_t regDTPR1 = {0};
	ncp_phy_DTPR2_5600_t regDTPR2 = {0};
	ncp_phy_DTPR3_5600_t regDTPR3 = {0};
	ncp_phy_DTPR4_5600_t regDTPR4 = {0};
	ncp_phy_DTPR5_5600_t regDTPR5 = {0};
	ncp_phy_DX4GCR0_5600_t regDX4GCR0 = {0};
	ncp_phy_DX8GCR0_5600_t regDX8GCR0 = {0};
	ncp_phy_RDIMMGCR0_5600_t regRDIMMGCR0 = {0};
	ncp_phy_RDIMMCR0_5600_t regRDIMMCR0 = {0};
	ncp_phy_RDIMMCR1_5600_t regRDIMMCR1 = {0};
	ncp_phy_RDIMMCR2_5600_t regRDIMMCR2 = {0};
	ncp_phy_RDIMMCR3_5600_t regRDIMMCR3 = {0};
	ncp_phy_RDIMMCR4_5600_t regRDIMMCR4 = {0};
	ncp_phy_DX0GCR1_5600_t regDX0GCR1 = {0};
	ncp_phy_DX0GCR3_5600_t regDX0GCR3 = {0};
	ncp_phy_DX0GCR4_5600_t regDX0GCR4 = {0};
	ncp_phy_DX0GCR5_5600_t regDX0GCR5 = {0};
	ncp_phy_DCR_5600_t regDCR = {0};
	ncp_phy_PGCR2_5600_t regPGCR2 = {0};
	ncp_phy_PIR_5600_t regPIR = {0};
	ncp_phy_PGCR0_5600_t regPGCR0 = {0};
	ncp_phy_PGCR1_5600_t regPGCR1 = {0};
	ncp_phy_PGSR0_5600_t regPGSR0 = {0};
	ncp_phy_BISTRR_5600_t regBISTRR = {0};
	ncp_phy_BISTUDPR_5600_t regBISTUDPR = {0};
	ncp_phy_DSGCR_5600_t regDSGCR = {0};
	ncp_phy_DXCCR_5600_t regDXCCR = {0};
	ncp_phy_IOVCR0_5600_t regIOVCR0 = {0};
	ncp_phy_IOVCR1_5600_t regIOVCR1 = {0};
	ncp_phy_ZQCR_5600_t regZQCR = {0};
	ncp_phy_ZQ0PR_5600_t regZQ0PR = {0};
	ncp_phy_ZQ1PR_5600_t regZQ1PR = {0};
	ncp_phy_ZQ2PR_5600_t regZQ2PR = {0};
	ncp_phy_ZQ3PR_5600_t regZQ3PR = {0};
	ncp_phy_ACIOCR0_5600_t regACIOCR0 = {0};
	/*ncp_phy_DX0GCR0_5600_t regDX0GCR0 = {0};*/

	ncp_denali_DENALI_CTL_00_5600_t reg00 = {0};

	/* check if PHY is already configured */
	ncr_read32(phyReg, NCP_PHY_PGSR0_5600, (ncp_uint32_t *)&regPGSR0);
	if (regPGSR0.aplock)
	{
		/* AC PLL lock set */
		errprintf("WARNING: PHY still configured!! PLEASE RESET. \n");
		return ncpStatus;
	}

	/* PGCR0 */
	ncr_read32(phyReg, NCP_PHY_PGCR0_5600, (ncp_uint32_t *)&regPGCR0);
	regPGCR0.icpc = 1;
	ncr_write32(phyReg, NCP_PHY_PGCR0_5600, *((ncp_uint32_t *)&regPGCR0));

	if ((parms->enableECC == TRUE) && (parms->version == NCP_CHIP_ACPXLF))
	{
		/* DXCCR */
		ncr_read32(phyReg, NCP_PHY_DXCCR_5600, (ncp_uint32_t *)&regDXCCR);
		regDXCCR.msbudq = 4;
		ncr_write32(phyReg, NCP_PHY_DXCCR_5600, *((ncp_uint32_t *)&regDXCCR));
	}

	for (i = 0; i < 9; i++)
	{
		/* DX0BDLR0 .. DX8BDLR2 */
		ncr_read32(phyReg, (NCP_PHY_DX0BDLR0_5600 + (0x100 * i)), &tmp);
		tmp = 0x04040404;
		ncr_write32(phyReg, (NCP_PHY_DX0BDLR0_5600 + (0x100 * i)), tmp);

		ncr_read32(phyReg, (NCP_PHY_DX0BDLR1_5600 + (0x100 * i)), &tmp);
		tmp = 0x04040404;
		ncr_write32(phyReg, (NCP_PHY_DX0BDLR1_5600 + (0x100 * i)), tmp);

		ncr_read32(phyReg, (NCP_PHY_DX0BDLR2_5600 + (0x100 * i)), &tmp);
		tmp = 0x04040404;
		ncr_write32(phyReg, (NCP_PHY_DX0BDLR2_5600 + (0x100 * i)), tmp);
	}

	/* PGCR1 */
	ncr_read32(phyReg, NCP_PHY_PGCR1_5600, (ncp_uint32_t *)&regPGCR1);
	regPGCR1.wlstep = 1; /* write leveling step */
	/*regPGCR1.pubmode = 1;*/ /* PUB controls the interface to PHY and SDRAM */
	regPGCR1.ioddrm = 1; /* DDR4 */
	ncr_write32(phyReg, NCP_PHY_PGCR1_5600, *((ncp_uint32_t *)&regPGCR1));

	/* setup BIST early to UserDataPattern for VREF training bug */
	ncr_read32(phyReg, NCP_PHY_BISTRR_5600, (ncp_uint32_t *)&regBISTRR);
	regBISTRR.bmode = 1;
	regBISTRR.bdxen = 1; /* bist datx8 enable */
	regBISTRR.bdpat = 3;
	ncr_write32(phyReg, NCP_PHY_BISTRR_5600, *((ncp_uint32_t *)&regBISTRR));

	ncr_read32(phyReg, NCP_PHY_BISTUDPR_5600, (ncp_uint32_t *)&regBISTUDPR);
	regBISTUDPR.budp0 = 0xaaaa;
	regBISTUDPR.budp1 = 0x5555;
	ncr_write32(phyReg, NCP_PHY_BISTUDPR_5600, *((ncp_uint32_t *)&regBISTUDPR));
#if 1
	/* PTR3 */
	ncr_read32(phyReg, NCP_PHY_PTR3_5600, (ncp_uint32_t *)&regPTR3);
	/* dram init time in cke, use 500us per dwc pub */
	regPTR3.tdinit0 = ncp_ps_to_clk(parms->tck_ps, 500000000);
	regPTR3.tdinit1 = Max(5, (ctm->tRFC + ncp_ps_to_clk(parms->tck_ps, 10000)));
	ncr_write32(phyReg, NCP_PHY_PTR3_5600, *((ncp_uint32_t *)&regPTR3));

	/* PTR4 */
	ncr_read32(phyReg, NCP_PHY_PTR4_5600, (ncp_uint32_t *)&regPTR4);
	/* 200us on power up */
	regPTR4.tdinit2 = ncp_ps_to_clk(parms->tck_ps, 200000000);
	/* time from ZQ init to first command */
	regPTR4.tdinit3 = ctm->tZQinit; /* 1024 */
	ncr_write32(phyReg, NCP_PHY_PTR4_5600, *((ncp_uint32_t *)&regPTR4));
#endif
	/* DTPR0 */
	ncr_read32(phyReg, NCP_PHY_DTPR0_5600, (ncp_uint32_t *)&regDTPR0);
	regDTPR0.trtp = ctm->tRTP;
	regDTPR0.trp = ctm->tRP;
	regDTPR0.tras = ctm->tRAS;
	regDTPR0.trrd = ctm->tRRD_S;
	ncr_write32(phyReg, NCP_PHY_DTPR0_5600, *((ncp_uint32_t *)&regDTPR0));

	/* DTPR1 */
	ncr_read32(phyReg, NCP_PHY_DTPR1_5600, (ncp_uint32_t *)&regDTPR1);
	regDTPR1.tmrd = ctm->tMRD;
	regDTPR1.tmod = ctm->tMOD;
	regDTPR1.tfaw = ctm->tFAW;
	/*regDTPR1.twlmrd = default */
	ncr_write32(phyReg, NCP_PHY_DTPR1_5600, *((ncp_uint32_t *)&regDTPR1));

	/* DTPR2 */
	ncr_read32(phyReg, NCP_PHY_DTPR2_5600, (ncp_uint32_t *)&regDTPR2);
	regDTPR2.txs = ctm->tXS;
	regDTPR2.tcke = ctm->tCKE;
	/*regDTPR2.trtodt = default */
	/*regDTPR2.trtw = default */
	ncr_write32(phyReg, NCP_PHY_DTPR2_5600, *((ncp_uint32_t *)&regDTPR2));

	/* DTPR3 */
	ncr_read32(phyReg, NCP_PHY_DTPR3_5600, (ncp_uint32_t *)&regDTPR3);
	/*regDTPR3.tdqsck = default */
	/*regDTPR3.tdqsckmax = default */
	/*regDTPR3.tdllk = default */
	regDTPR3.tccd = 0x1;/* For PHY and DDR4 */
	/*regDTPR3.tofdx = default */ /* ODT turn-off delay extension */
	ncr_write32(phyReg, NCP_PHY_DTPR3_5600, *((ncp_uint32_t *)&regDTPR3));

	/* DTPR4 */
	ncr_read32(phyReg, NCP_PHY_DTPR4_5600, (ncp_uint32_t *)&regDTPR4);
	/*regDTPR4.txp = default */
	regDTPR4.twlo = 0xf; /* write-levelling output delay */
	regDTPR4.trfc = ctm->tRFC;
	ncr_write32(phyReg, NCP_PHY_DTPR4_5600, *((ncp_uint32_t *)&regDTPR4));

	/* DTPR5 */
	ncr_read32(phyReg, NCP_PHY_DTPR5_5600, (ncp_uint32_t *)&regDTPR5);
	regDTPR5.twtr = ctm->tWTR_L;
	regDTPR5.trcd = ctm->tRCD;
	regDTPR5.trc = ctm->tRC;
	ncr_write32(phyReg, NCP_PHY_DTPR5_5600, *((ncp_uint32_t *)&regDTPR5));

	/* Initializing the ddr4 phy */

	/* Deal with RDIMM stuff */
	if (parms->rdimm_misc & 0x1)
	{
		/* RDIMMGCR0 */
		ncr_read32(phyReg, NCP_PHY_RDIMMGCR0_5600, (ncp_uint32_t *)&regRDIMMGCR0);
		regRDIMMGCR0.rdimm = 1;
		ncr_write32(phyReg, NCP_PHY_RDIMMGCR0_5600, *((ncp_uint32_t *)&regRDIMMGCR0));

		/* RDIMMCR0 */
		ncr_read32(phyReg, NCP_PHY_RDIMMCR0_5600, (ncp_uint32_t *)&regRDIMMCR0);
		regRDIMMCR0.rc0 = parms->rdimm_ctl_0_0 & 0xf; 
		regRDIMMCR0.rc1 = (parms->rdimm_ctl_0_0 & 0xf0) >> 4;
		regRDIMMCR0.rc2 = (parms->rdimm_ctl_0_0 & 0xf00) >> 8;
		regRDIMMCR0.rc3 = (parms->rdimm_ctl_0_0 & 0xf000) >> 12;
		regRDIMMCR0.rc4 = (parms->rdimm_ctl_0_0 & 0xf0000) >> 16;
		regRDIMMCR0.rc5 = (parms->rdimm_ctl_0_0 & 0xf00000) >> 20;
		regRDIMMCR0.rc6 = (parms->rdimm_ctl_0_0 & 0xf000000) >> 24;
		regRDIMMCR0.rc7 = (parms->rdimm_ctl_0_0 & 0xf0000000) >> 28;
		ncr_write32(phyReg, NCP_PHY_RDIMMCR0_5600, *((ncp_uint32_t *)&regRDIMMCR0));

		/* RDIMMCR1 */
		ncr_read32(phyReg, NCP_PHY_RDIMMCR1_5600, (ncp_uint32_t *)&regRDIMMCR1);
		regRDIMMCR1.rc8 = parms->rdimm_ctl_0_1 & 0xf; 
		regRDIMMCR1.rc9 = (parms->rdimm_ctl_0_1 & 0xf0) >> 4;
		regRDIMMCR1.rc10 = (parms->rdimm_ctl_0_1 & 0xf00) >> 8;
		regRDIMMCR1.rc11 = (parms->rdimm_ctl_0_1 & 0xf000) >> 12;
		regRDIMMCR1.rc12 = (parms->rdimm_ctl_0_1 & 0xf0000) >> 16;
		regRDIMMCR1.rc13 = (parms->rdimm_ctl_0_1 & 0xf00000) >> 20;
		regRDIMMCR1.rc14 = (parms->rdimm_ctl_0_1 & 0xf000000) >> 24;
		regRDIMMCR1.rc15 = (parms->rdimm_ctl_0_1 & 0xf0000000) >> 28;
		ncr_write32(phyReg, NCP_PHY_RDIMMCR1_5600, *((ncp_uint32_t *)&regRDIMMCR1));

		/* RDIMMCR2 */
		ncr_read32(phyReg, NCP_PHY_RDIMMCR2_5600, (ncp_uint32_t *)&regRDIMMCR2);
		regRDIMMCR2.rc1x = parms->rdimm_ctl_0_2 & 0xff; 
		regRDIMMCR2.rc2x = (parms->rdimm_ctl_0_2 & 0xff00) >> 8;
		regRDIMMCR2.rc3x = (parms->rdimm_ctl_0_2 & 0xff0000) >> 16;
		regRDIMMCR2.rc4x = (parms->rdimm_ctl_0_2 & 0xff000000) >> 24;
		ncr_write32(phyReg, NCP_PHY_RDIMMCR2_5600, *((ncp_uint32_t *)&regRDIMMCR2));

		/* RDIMMCR3 */
		ncr_read32(phyReg, NCP_PHY_RDIMMCR3_5600, (ncp_uint32_t *)&regRDIMMCR3);
		regRDIMMCR3.rc5x = parms->rdimm_ctl_0_3 & 0xff; 
		regRDIMMCR3.rc6x = (parms->rdimm_ctl_0_3 & 0xff00) >> 8;
		regRDIMMCR3.rc7x = (parms->rdimm_ctl_0_3 & 0xff0000) >> 16;
		regRDIMMCR3.rc8x = (parms->rdimm_ctl_0_3 & 0xff000000) >> 24;
		ncr_write32(phyReg, NCP_PHY_RDIMMCR3_5600, *((ncp_uint32_t *)&regRDIMMCR3));

		/* RDIMMCR4 */
		ncr_read32(phyReg, NCP_PHY_RDIMMCR4_5600, (ncp_uint32_t *)&regRDIMMCR4);
		regRDIMMCR4.rc9x = parms->rdimm_ctl_0_4 & 0xff; 
		regRDIMMCR4.rcax = (parms->rdimm_ctl_0_4 & 0xff00) >> 8;
		regRDIMMCR4.rcbx = (parms->rdimm_ctl_0_4 & 0xff0000) >> 16;
		regRDIMMCR4.rcxx = (parms->rdimm_ctl_0_4 & 0xff000000) >> 24;
		ncr_write32(phyReg, NCP_PHY_RDIMMCR4_5600, *((ncp_uint32_t *)&regRDIMMCR4));
	}

	/* Power Down OFF in PHY */

	for (i = 0; i < 9; i++)
	{
		/* DX0GCR1 .. DX8GCR1 */
		ncr_read32(phyReg, (NCP_PHY_DX0GCR1_5600 + (0x100 * i)), (ncp_uint32_t *)&regDX0GCR1);
		regDX0GCR1.dxpddmode = 0x0000;
		regDX0GCR1.dxpdrmode = 0x0000; /* based on pub_routines */
		ncr_write32(phyReg, (NCP_PHY_DX0GCR1_5600 + (0x100 * i)), *((ncp_uint32_t *)&regDX0GCR1));
	}

	for (i = 0; i < 9; i++)
	{
		/* DX0GCR3 .. DX8GCR3 */
		ncr_read32(phyReg, (NCP_PHY_DX0GCR3_5600 + (0x100 * i)), (ncp_uint32_t *)&regDX0GCR3);
		regDX0GCR3.dspdrmode = 0x0; /* based on pub_routines */
		/* default for others ?? */
		ncr_write32(phyReg, (NCP_PHY_DX0GCR3_5600 + (0x100 * i)), *((ncp_uint32_t *)&regDX0GCR3));

		/* DX0GCR4 .. DX8GCR4 */
		ncr_read32(phyReg, (NCP_PHY_DX0GCR4_5600 + (0x100 * i)), (ncp_uint32_t *)&regDX0GCR4);
		regDX0GCR4.dxrefien = 0x3; /* vref enable control for DQ IO buffers of a byte lane */
		regDX0GCR4.dxrefssel = 0x9; /* 50.35%(mid-rail) */
		regDX0GCR4.dxrefiom = 0x2;
		/* default for others ?? */
		ncr_write32(phyReg, (NCP_PHY_DX0GCR4_5600 + (0x100 * i)), *((ncp_uint32_t *)&regDX0GCR4));

		/* DX0GCR5 .. DX8GCR5 */
		ncr_read32(phyReg, (NCP_PHY_DX0GCR5_5600 + (0x100 * i)), (ncp_uint32_t *)&regDX0GCR5);
		regDX0GCR5.dxrefiselr0 = 0x2e; /* 76.17% byte lane internal vref select for rank 0 */
		regDX0GCR5.dxrefiselr1 = 0x2e; /* 76.17% byte lane internal vref select for rank 1 */
		/* default for others ?? */
		ncr_write32(phyReg, (NCP_PHY_DX0GCR5_5600 + (0x100 * i)), *((ncp_uint32_t *)&regDX0GCR5));
	}

	/* DSGCR */
	ncr_read32(phyReg, NCP_PHY_DSGCR_5600, (ncp_uint32_t *)&regDSGCR);
	regDSGCR.wrrmode = 1;
	regDSGCR.rrrmode = 1;
	ncr_write32(phyReg, NCP_PHY_DSGCR_5600, *((ncp_uint32_t *)&regDSGCR));

	/* PHY DCR Register */

	ncr_read32(phyReg, NCP_PHY_DCR_5600, (ncp_uint32_t *)&regDCR);
	regDCR.ddrmd = (parms->dram_class == NCP_SM_DDR4_MODE) ? 0x4 : 0x3;
	regDCR.ddr8bnk = 0x1; /* SDRAM uses 8 banks or less */
	regDCR.pdq = 0x0; /* which if the 0..7 DQ pins is primary for MPR */
	regDCR.mprdq = 0x1; /* both primary and other DQ pins all drive same data from MPR */

	/* This is for read data on all byte lanes during read DQS gate training */
#if 0
	if (parms->primary_bus_width == 2)
	{
		/* half-datapath feature */
		regDCR.bytemask = 0xf; 
	}
	else
	{
		regDCR.bytemask = 0xff; 
	}
#endif

	/* No simultaneous Rank Access on same clock cycle allowed */
	regDCR.nosra = parms->address_mirroring; 

	/* 2T timing should be used by PUB generated sdram transactions */
	regDCR.ddr2t = 0x1; 

	/* UDIMM address mirroring */
	/* PUB will rescramble bank and address when sending MR cmds to second rank */
	regDCR.udimm = parms->address_mirroring; 

	if (parms->sdram_device_width == 2)
	{
		/* x16 */
		regDCR.ubg = 0x1; /* un-used bank group */
	}

	ncr_write32(phyReg, NCP_PHY_DCR_5600, *((ncp_uint32_t *)&regDCR));

	ncr_read32(phyReg, NCP_PHY_RIDR_5600, &tmp);
	if ((tmp & 0xff) == 0x22)
	{
		ncr_write32(phyReg, NCP_PHY_PLLCR2_5600, 0x5140e7c0);
		ncr_write32(phyReg, NCP_PHY_PLLCR3_5600, 0x0000e670);
	}

	/* IOVCR0 Register */
	ncr_read32(phyReg, NCP_PHY_IOVCR0_5600, (ncp_uint32_t *)&regIOVCR0);
	regIOVCR0.acvrefisel = 0x9; /* 50.35% mid-rail */
	regIOVCR0.acrefsen = 0x0;
	regIOVCR0.acrefiom = 0x2;
	ncr_write32(phyReg, NCP_PHY_IOVCR0_5600, *((ncp_uint32_t *)&regIOVCR0));

	/* IOVCR1 Register */
	ncr_read32(phyReg, NCP_PHY_IOVCR1_5600, (ncp_uint32_t *)&regIOVCR1);
	regIOVCR1.zqrefisel = 0x9; /* 50.35% mid-rail */
	ncr_write32(phyReg, NCP_PHY_IOVCR1_5600, *((ncp_uint32_t *)&regIOVCR1));

	/* ZQCR Register */
	ncr_read32(phyReg, NCP_PHY_ZQCR_5600, (ncp_uint32_t *)&regZQCR);
	regZQCR.term_off = 0x0;
	regZQCR.zqpd = 0x0;
	regZQCR.pgwait = 0x7; /* 467 clock */
	regZQCR.zcalt = 0x1; /* continous cal */
	regZQCR.avgmax = 0x2; /* 8 rounds */
	regZQCR.avgen = 0x1; /* averaging on */
	regZQCR.iodlmt = 0x2;
	regZQCR.asym_drv_en = 0x1;
	regZQCR.pu_odt_only = 0x1;
	regZQCR.dis_non_lin_comp = 0x0;
	regZQCR.force_zcal_vt_update = 0x0;
	regZQCR.zctrl_upper = 0x0;
	ncr_write32(phyReg, NCP_PHY_ZQCR_5600, *((ncp_uint32_t *)&regZQCR));

	ncr_read32(phyReg, NCP_PHY_RIDR_5600, &tmp);
	if ((tmp & 0xff) == 0x33)
	{
		/* ZQCR for D4MU IOs */
		regZQCR.zctrl_upper = 0x3;
		ncr_write32(phyReg, NCP_PHY_ZQCR_5600, *((ncp_uint32_t *)&regZQCR));
	}

	ncr_read32(phyReg, NCP_PHY_RIDR_5600, &tmp);
#if 0
	for (i = 0; i < 4; i++)
	{
		/* ZQCR set asymmetric ODT (based on number of islands) ZQnDR regs */
		ncr_read32(phyReg, (NCP_PHY_ZQ0DR_5600 + (0x10 * i)), (ncp_uint32_t *)&regZQ0DR);
		if ((tmp & 0xff) != 0x22)
		{
			regZQ0DR.odt_zden = 0x1;
			regZQ0DR.zdata = 28 << 21;
		}
		ncr_write32(phyReg, (NCP_PHY_ZQ0DR_5600 + (0x10 * i)), *((ncp_uint32_t *)&regZQ0DR));
	}
#endif
	ncr_read32(phyReg, NCP_PHY_ZQ0PR_5600, (ncp_uint32_t *)&regZQ0PR);
	ncr_read32(phyReg, NCP_PHY_ZQ2PR_5600, (ncp_uint32_t *)&regZQ2PR);
	ncr_read32(phyReg, NCP_PHY_ZQ1PR_5600, (ncp_uint32_t *)&regZQ1PR);
	ncr_read32(phyReg, NCP_PHY_ZQ3PR_5600, (ncp_uint32_t *)&regZQ3PR);
	ncr_read32(phyReg, NCP_PHY_ACIOCR0_5600, (ncp_uint32_t *)&regACIOCR0);
	ncr_read32(phyReg, NCP_PHY_DXCCR_5600, (ncp_uint32_t *)&regDXCCR);

	switch (smNode) {
		case 0x22:
			/* X9/XLF */
			regZQ0PR.zprog_asym_drv_pu = parms->packedAddrCmdCtrlOI & 0xf;
			regZQ0PR.zprog_asym_drv_pd = parms->packedAddrCmdCtrlOI & 0xf;
			regZQ2PR.zprog_asym_drv_pu = parms->packedAddrCmdCtrlOI & 0xf;
			regZQ2PR.zprog_asym_drv_pd = parms->packedAddrCmdCtrlOI & 0xf;

			regZQ1PR.zprog_asym_drv_pu = parms->packedClockOI & 0xf;
			regZQ1PR.zprog_asym_drv_pd = parms->packedClockOI & 0xf;

			regZQ3PR.zprog_pu_odt_only = parms->packedDqDmDqsODT & 0xf;

			regZQ3PR.zprog_asym_drv_pu = parms->packedDqDmDqsOI & 0xf;
			regZQ3PR.zprog_asym_drv_pd = parms->packedDqDmDqsOI & 0xf;

			regACIOCR0.acsr = parms->packedAddrCmdCtrlClkSlewRates & 0xf;

			regDXCCR.dxsr = parms->packedDqDmDqsSlewRates & 0xf;
			break;
		case 0xf:
			/* X9/XLF */
			regZQ0PR.zprog_asym_drv_pu = (parms->packedAddrCmdCtrlOI >> 8) & 0xf;
			regZQ0PR.zprog_asym_drv_pd = (parms->packedAddrCmdCtrlOI >> 8) & 0xf;
			regZQ2PR.zprog_asym_drv_pu = (parms->packedAddrCmdCtrlOI >> 8) & 0xf;
			regZQ2PR.zprog_asym_drv_pd = (parms->packedAddrCmdCtrlOI >> 8) & 0xf;

			regZQ1PR.zprog_asym_drv_pu = (parms->packedClockOI >> 8) & 0xf;
			regZQ1PR.zprog_asym_drv_pd = (parms->packedClockOI >> 8) & 0xf;

			regZQ3PR.zprog_pu_odt_only = (parms->packedDqDmDqsODT >> 8) & 0xf;

			regZQ3PR.zprog_asym_drv_pu = (parms->packedDqDmDqsOI >> 8) & 0xf;
			regZQ3PR.zprog_asym_drv_pd = (parms->packedDqDmDqsOI >> 8) & 0xf;

			regACIOCR0.acsr = (parms->packedAddrCmdCtrlClkSlewRates >> 8) & 0xf;

			regDXCCR.dxsr = (parms->packedDqDmDqsSlewRates >> 8) & 0xf;
			break;
		case 0x23:
			/* XLF */
			regZQ0PR.zprog_asym_drv_pu = (parms->packedAddrCmdCtrlOI >> 16) & 0xf;
			regZQ0PR.zprog_asym_drv_pd = (parms->packedAddrCmdCtrlOI >> 16) & 0xf;
			regZQ2PR.zprog_asym_drv_pu = (parms->packedAddrCmdCtrlOI >> 16) & 0xf;
			regZQ2PR.zprog_asym_drv_pd = (parms->packedAddrCmdCtrlOI >> 16) & 0xf;

			regZQ1PR.zprog_asym_drv_pu = (parms->packedClockOI >> 16) & 0xf;
			regZQ1PR.zprog_asym_drv_pd = (parms->packedClockOI >> 16) & 0xf;

			regZQ3PR.zprog_pu_odt_only = (parms->packedDqDmDqsODT >> 16) & 0xf;

			regZQ3PR.zprog_asym_drv_pu = (parms->packedDqDmDqsOI >> 16) & 0xf;
			regZQ3PR.zprog_asym_drv_pd = (parms->packedDqDmDqsOI >> 16) & 0xf;

			regACIOCR0.acsr = (parms->packedAddrCmdCtrlClkSlewRates >> 16) & 0xf;

			regDXCCR.dxsr = (parms->packedDqDmDqsSlewRates >> 16) & 0xf;
			break;
		case 0x24:
			/* XLF */
			regZQ0PR.zprog_asym_drv_pu = (parms->packedAddrCmdCtrlOI >> 24) & 0xf;
			regZQ0PR.zprog_asym_drv_pd = (parms->packedAddrCmdCtrlOI >> 24) & 0xf;
			regZQ2PR.zprog_asym_drv_pu = (parms->packedAddrCmdCtrlOI >> 24) & 0xf;
			regZQ2PR.zprog_asym_drv_pd = (parms->packedAddrCmdCtrlOI >> 24) & 0xf;

			regZQ1PR.zprog_asym_drv_pu = (parms->packedClockOI >> 24) & 0xf;
			regZQ1PR.zprog_asym_drv_pd = (parms->packedClockOI >> 24) & 0xf;

			regZQ3PR.zprog_pu_odt_only = (parms->packedDqDmDqsODT >> 24) & 0xf;

			regZQ3PR.zprog_asym_drv_pu = (parms->packedDqDmDqsOI >> 24) & 0xf;
			regZQ3PR.zprog_asym_drv_pd = (parms->packedDqDmDqsOI >> 24) & 0xf;

			regACIOCR0.acsr = (parms->packedAddrCmdCtrlClkSlewRates >> 24) & 0xf;

			regDXCCR.dxsr = (parms->packedDqDmDqsSlewRates >> 24) & 0xf;
			break;
		default:
			NCP_CALL(NCP_ST_ERROR);
	}

	/*regZQ0PR.zprog_pu_odt_only = 0xd;*/
	ncr_write32(phyReg, NCP_PHY_ZQ0PR_5600, *((ncp_uint32_t *)&regZQ0PR));

	/*regZQ1PR.zprog_pu_odt_only = 0xd;*/
	ncr_write32(phyReg, NCP_PHY_ZQ1PR_5600, *((ncp_uint32_t *)&regZQ1PR));

	/*regZQ2PR.zprog_pu_odt_only = 0xd;*/
	ncr_write32(phyReg, NCP_PHY_ZQ2PR_5600, *((ncp_uint32_t *)&regZQ2PR));

	/*regZQ3PR.zqdiv = (0x7 << 4) | 0xb; *//* DQ ODT value and DQ drive impedance */
	ncr_write32(phyReg, NCP_PHY_ZQ3PR_5600, *((ncp_uint32_t *)&regZQ3PR));

	ncr_write32(phyReg, NCP_PHY_ACIOCR0_5600, *((ncp_uint32_t *)&regACIOCR0));

	ncr_write32(phyReg, NCP_PHY_DXCCR_5600, *((ncp_uint32_t *)&regDXCCR));


	/* PHY PGCR2 Register */

	ncr_read32(phyReg, NCP_PHY_PGCR2_5600, (ncp_uint32_t *)&regPGCR2);
	/* ctm->tREFI will account for clock period.
	 * assuming 9 refresh per refresh interval
	 * use 400 clock safety margin per PUB
	 */
	regPGCR2.trefprd = (9 * ctm->tREFI) - 400;
	/*regPGCR2.trefprd = 0x10a8;*/
	ncr_write32(phyReg, NCP_PHY_PGCR2_5600, *((ncp_uint32_t *)&regPGCR2));

	/* NOTE: MR settings are coming from end-user's selection in ASE and they
	 * feed into both rank provisioning in MC, whereas, only rank-0 is used
	 * PHY here */

	/* PHY MR0 Register */
	tmp = ctm->mr0;
	ncr_write32(phyReg, NCP_PHY_MR0_5600, tmp);

	/* PHY MR1 Register */
	tmp = ctm->mr1;
	ncr_write32(phyReg, NCP_PHY_MR1_5600, tmp);

	/* PHY MR2 Register */
	tmp = ctm->mr2;
	ncr_write32(phyReg, NCP_PHY_MR2_5600, tmp);

	/* PHY MR3 Register */
	tmp = ctm->mr3;
	ncr_write32(phyReg, NCP_PHY_MR3_5600, tmp);

	/* PHY MR4 Register */
	tmp = ctm->mr4;
	ncr_write32(phyReg, NCP_PHY_MR4_5600, tmp);

	/* PHY MR5 Register */
	tmp = ctm->mr5;
	ncr_write32(phyReg, NCP_PHY_MR5_5600, tmp);

	/* PHY MR6 Register */
	tmp = ctm->mr6;
	ncr_write32(phyReg, NCP_PHY_MR6_5600, tmp);

	/* Force ZQ calibration */
	ncr_read32(phyReg, NCP_PHY_ZQCR_5600, (ncp_uint32_t *)&regZQCR);
	regZQCR.force_zcal_vt_update = 0x1;
	ncr_write32(phyReg, NCP_PHY_ZQCR_5600, *((ncp_uint32_t *)&regZQCR));
	regZQCR.force_zcal_vt_update = 0x0;
	ncr_write32(phyReg, NCP_PHY_ZQCR_5600, *((ncp_uint32_t *)&regZQCR));

	/* PLL init and Impedance Calibration */

	ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
	/* Init trigger for DDR system init including PHY init, DRAM init, and PHY training */
	regPIR.init = 1; 
	/* Actual init involves selection among the following steps:
	 * ZCAL: impedance calibration
	 * CA: CA training
	 * PLLINIT: pll init (pll power, reset, gear shift, wait for lock)
	 * DCAL: digital delay line calibration
	 * PHYRST: reset the AC and DATX8
	 * DRAMRST: reset, wait 200us
	 * DRAMINIT: executes DRAM init sequence
	 * WL: write leveling
	 * QSGATE: read dqs gate training
	 * WLADJ: write leveling adjust
	 * RDDSKW: read data bit deskew
	 * WRDSKW: write data bit deskew
	 * RDEYE: read data eye training
	 * WREYE: write data eye training
	 *
	 *
	 * <specials are>
	 * SRD: static read training
	 * VREF: vref training
	 * CTLDINIT: controller performs DRAM init
	 * RDIMMINIT: rdimm init
	 */
	regPIR.zcal = 1; 
	regPIR.ca = 0; 
	regPIR.pllinit = 1; 
	regPIR.dcal = 1; 
	regPIR.phyrst = 1; 
	regPIR.dramrst = 0; 
	regPIR.draminit = 0; 
	regPIR.wl = 0; 
	regPIR.qsgate = 0; 
	regPIR.wladj = 0; 
	regPIR.rddskw = 0; 
	regPIR.wrdskw = 0; 
	regPIR.rdeye = 0; 
	regPIR.wreye = 0; 
	regPIR.srd = 0; 
	regPIR.vref = 0; 
	regPIR.ctldinit = 0; 
	regPIR.rdimminit = 0; 
	ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));
	ncr_read32(phyReg, NCP_PHY_PIR_5600, &tmp);

	/* Check the General Status register */

	/* poll for idone(bit 0), pldone(1), dcdone(2), zcdone(3) */
	ncpStatus = (ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0xf,  0xf,  1000,  10000));

	if (ncpStatus == NCP_ST_POLL_TIMEOUT)
	{
		ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
		errprintf("POLL timeout during PHY init [line:%d] exp 0x1f read 0x%x\n",__LINE__, tmp);
		return ncpStatus;
	}

	/* Checking for Error's */
	ncpStatus = (ncp_sm_ddr4_phy_training_error_check(dev, smNode));
	if (ncpStatus == NCP_ST_ERROR)
	{
		return ncpStatus;
	}

	ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
	dbgprintf("SUCCESS: result after PHY init PLL init and impedance calibration [line:%d] read 0x%x\n",__LINE__, tmp);

	/* disable all unused bytes */
	if ((parms->enableECC == FALSE) && (parms->version == NCP_CHIP_ACP56xx))
	{
		/* DX8GCR0 */
		ncr_read32(phyReg, NCP_PHY_DX8GCR0_5600, (ncp_uint32_t *)&regDX8GCR0);
		regDX8GCR0.dxen = 0;
		ncr_write32(phyReg, NCP_PHY_DX8GCR0_5600, *((ncp_uint32_t *)&regDX8GCR0));
	}
	else if ((parms->enableECC == FALSE) && (parms->version == NCP_CHIP_ACPXLF))
	{
		/* DX4GCR0 */
		ncr_read32(phyReg, NCP_PHY_DX4GCR0_5600, (ncp_uint32_t *)&regDX4GCR0);
		regDX4GCR0.dxen = 0;
		ncr_write32(phyReg, NCP_PHY_DX4GCR0_5600, *((ncp_uint32_t *)&regDX4GCR0));
	}

	/* PHY Init done!!! */

#if 0 	/* Check if this is needed ?? MC is already init'd by this point
	 * should DRAM init be done by PHY-side or should PHY be told Controller will do DRAM init ?? */

	dbgprintf("DRAM init initiated by PHY!!!!!\n");
	/*ncr_read32(phyReg, NCP_PHY_GPR0_5600, &tmp);
	  dbgprintf("pubmode = %d PHY:GPR0=0x%x\n",regPGCR1.pubmode, tmp);*/

	/* PGCR1 */
	ncr_read32(phyReg, NCP_PHY_PGCR1_5600, (ncp_uint32_t *)&regPGCR1);
	/* Enables if set the PUB to control the interface to the PHY and SDRAM.
	 * In this mode the DFI commands from the controller are ignored. The bit must
	 * be set to 0 after the system determines it is convenient to pass control of the DFI
	 * bus to the controller. When set to 0 the DFI interface has control of the PHY and SDRAM
	 * interface except when trigerring pub operations such as BIST, DCU or data training.
	 */
	regPGCR1.pubmode = 0x1;
	ncr_write32(phyReg, NCP_PHY_PGCR1_5600, *((ncp_uint32_t *)&regPGCR1));

	/* SDRAM Initialization by PHY !!! */

	ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
	regPIR.init = 1; 
	regPIR.zcal = 0; 
	regPIR.ca = 0; 
	regPIR.pllinit = 0; 
	regPIR.dcal = 0; 
	regPIR.phyrst = 0; 
	regPIR.dramrst = 1; 
	regPIR.draminit = 1; 
	regPIR.wl = 0; 
	regPIR.qsgate = 0; 
	regPIR.wladj = 0; 
	regPIR.rddskw = 0; 
	regPIR.wrdskw = 0; 
	regPIR.rdeye = 0; 
	regPIR.wreye = 0; 
	regPIR.srd = 0; 
	regPIR.vref = 0; 
	regPIR.ctldinit = 0; 
	regPIR.rdimminit = 0; 
	ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));

	/* Check the General Status register */

	/* poll for idone(bit 0), didone(4) */
	ncpStatus = (ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0x11,  0x11,  1000,  10000));

	if (ncpStatus == NCP_ST_POLL_TIMEOUT)
	{
		ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
		errprintf("POLL timeout during SDRAM initialization by PHY [line:%d] exp 0x11 read 0x%x\n",__LINE__, tmp);
		return ncpStatus;
	}

	/* Checking for Error's */
	ncpStatus = (ncp_sm_ddr4_phy_training_error_check(dev, smNode));
	if (ncpStatus == NCP_ST_ERROR)
	{
		return ncpStatus;
	}

	ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
	dbgprintf("SUCCESS: result during SDRAM initialization by PHY [line:%d] read 0x%x\n",__LINE__, tmp);


	/* SDRAM Initialization by PHY done !!! */
#if 0
	/* start MC init operation */
	ncr_read32(ctlReg, NCP_DENALI_CTL_00_5600, (ncp_uint32_t *)&reg00);
	reg00.start = 0x1;
	ncr_write32(ctlReg, NCP_DENALI_CTL_00_5600, *((ncp_uint32_t *)&reg00));

	/* poll for memory init operation bit-8 */
	ncpStatus = (ncr_poll(ctlReg, NCP_DENALI_CTL_366_5600,  0x0100,  0x0100,  1000,  10000));

	if (ncpStatus == NCP_ST_POLL_TIMEOUT)
	{
		ncr_read32(ctlReg, NCP_DENALI_CTL_366_5600, &tmp);
		errprintf("POLL timeout during MC init [line:%d] exp 0x100 read 0x%x\n",__LINE__, tmp);
	}
#endif
#else
	dbgprintf("DRAM init initiated by MC!!!!!\n");
	/*ncr_read32(phyReg, NCP_PHY_PGCR1_5600, (ncp_uint32_t *)&regPGCR1);
	  ncr_read32(phyReg, NCP_PHY_GPR0_5600, &tmp);
	  dbgprintf("pubmode = %d PHY:GPR0=0x%x\n",regPGCR1.pubmode, tmp);*/

	ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
	regPIR.init = 1; 
	regPIR.zcal = 0; 
	regPIR.ca = 0; 
	regPIR.pllinit = 0; 
	regPIR.dcal = 0; 
	regPIR.phyrst = 0; 
	regPIR.dramrst = 0; 
	regPIR.draminit = 0; 
	regPIR.wl = 0; 
	regPIR.qsgate = 0; 
	regPIR.wladj = 0; 
	regPIR.rddskw = 0; 
	regPIR.wrdskw = 0; 
	regPIR.rdeye = 0; 
	regPIR.wreye = 0; 
	regPIR.srd = 0; 
	regPIR.vref = 0; 
	regPIR.ctldinit = 1;  /* check with TB code */
	regPIR.rdimminit = 0; 
	ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));

	/*ncr_read32(phyReg, NCP_PHY_PIR_5600, &tmp);
	  dbgprintf("regPIR written as = 0x%x\n",tmp);*/

	ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
	dbgprintf("During MC initialization of the DRAM's [line:%d] PGSR0 = 0x%x\n",__LINE__, tmp);
	/* Check the General Status register */
#if 0
	/* poll for idone(bit 0) */
	ncpStatus = (ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0x1f,  0x1f,  1000,  10000));

	if (ncpStatus == NCP_ST_POLL_TIMEOUT)
	{
		ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
		errprintf("POLL timeout during MC initialization the DRAM's [line:%d] exp 0x11 read 0x%x\n",__LINE__, tmp);
		return ncpStatus;
	}

	/* Checking for Error's */
	ncpStatus = (ncp_sm_ddr4_phy_training_error_check(dev, smNode));
	if (ncpStatus == NCP_ST_ERROR)
	{
		return ncpStatus;
	}

	ncr_read32(phyReg, NCP_PHY_PGSR0_5600, &tmp);
	dbgprintf("SUCCESS: result during MC initialization the DRAM's [line:%d] exp 0x11 read 0x%x\n",__LINE__, tmp);
#endif

	/* start MC init operation */
	ncr_read32(ctlReg, NCP_DENALI_CTL_00_5600, (ncp_uint32_t *)&reg00);
	reg00.start = 0x1;
	ncr_write32(ctlReg, NCP_DENALI_CTL_00_5600, *((ncp_uint32_t *)&reg00));

	/* poll for memory init operation bit-8 */
	ncpStatus = (ncr_poll(ctlReg, NCP_DENALI_CTL_366_5600,  0x0100,  0x0100,  1000,  1000));

	ncr_read32(ctlReg, NCP_DENALI_CTL_366_5600, &tmp);
	dbgprintf("CTL_366 int_status = 0x%x looking for 0x100\n",tmp);
	ncr_read32(ctlReg, NCP_DENALI_CTL_367_5600, &tmp);
	dbgprintf("CTL_367 int_status = 0x%x\n",tmp);

	if (ncpStatus == NCP_ST_POLL_TIMEOUT)
	{
		ncr_read32(ctlReg, NCP_DENALI_CTL_366_5600, &tmp);
		errprintf("POLL timeout during MC init [line:%d] exp 0x100 read 0x%x\n",__LINE__, tmp);
	}

#endif

	NCP_RETURN_LABEL
		return ncpStatus;
}

ncp_st_t
ncp_sm_ddr4_post_phy_training_mc_setup(
		ncp_dev_hdl_t   dev,
		ncp_uint32_t    smNode,
		ncp_sm_parms_t *parms)
{
	ncp_st_t		ncpStatus = NCP_ST_SUCCESS;
	ncp_region_id_t 	ctlReg  = NCP_REGION_ID(smNode, NCP_SYSMEM_TGT_DENALI);

	ncp_denali_DENALI_CTL_125_5600_t reg125 = {0};
	ncp_denali_DENALI_CTL_368_5600_t reg368 = {0};
	ncp_denali_DENALI_CTL_369_5600_t reg369 = {0};
	ncp_denali_DENALI_CTL_370_5600_t reg370 = {0};
	ncp_denali_DENALI_CTL_371_5600_t reg371 = {0};

	/* DENALI_CTL_125 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_125_5600, (ncp_uint32_t *)&reg125);
	/* enable an automatic controller initiated update after every refresh */
	reg125.ctrlupd_req_per_aref_en = 0x1;
	ncr_write32(ctlReg, NCP_DENALI_CTL_125_5600, *((ncp_uint32_t *)&reg125));

	/* clear 17th and 30th bit of interrupt before clearing the mask, else interrupt gets set. */
	/* DENALI_CTL_368 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_368_5600, (ncp_uint32_t *)&reg368);
	reg368.int_ack = 0xffffffff;
	ncr_write32(ctlReg, NCP_DENALI_CTL_368_5600, *((ncp_uint32_t *)&reg368));

	/* DENALI_CTL_369 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_369_5600, (ncp_uint32_t *)&reg369);
	reg369.int_ack = 0x3;
	ncr_write32(ctlReg, NCP_DENALI_CTL_369_5600, *((ncp_uint32_t *)&reg369));

	/* int_mask */
	/* DENALI_CTL_370 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_370_5600, (ncp_uint32_t *)&reg370);
	reg370.int_mask = 0x0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_370_5600, *((ncp_uint32_t *)&reg370));

	/* DENALI_CTL_371 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_371_5600, (ncp_uint32_t *)&reg371);
	reg371.int_mask &= ~(0x7);
	ncr_write32(ctlReg, NCP_DENALI_CTL_371_5600, *((ncp_uint32_t *)&reg371));

	NCP_RETURN_LABEL
		return ncpStatus;
}

ncp_st_t
ncp_sysmem_init_synopphy(
		ncp_dev_hdl_t   dev,
		ncp_uint32_t    smId,
		ncp_sm_parms_t *parms)
{
	ncp_st_t	ncpStatus = NCP_ST_SUCCESS;
	ncp_common_timing_parameters_t	ctm = {0};
	ncp_uint32_t smNode = 0;

#ifndef __UBOOT__
	/* cmem setup
	 * XLF has 1 CMEM, X9 has 2 CMEM's
	 * If smId == 4 && chip == XLF, then setup CMEM-0
	 * If smId == 2 && chip == X9, then setup CMEM-0
	 * If smId == 3 && chip == X9, then setup CMEM-1
	 */

	if (((parms->version == NCP_CHIP_ACPXLF) && (smId == 4)) ||
			((parms->version == NCP_CHIP_ACP56xx) && (smId == 2)) ||
			((parms->version == NCP_CHIP_ACP56xx) && (smId == 3)))
	{
#if 1
		/* until CMEM setup is implemented */
		NCP_CALL(ncp_treemem_init_synopphy(dev, smId, parms));
#endif
		return ncpStatus;
	}
#endif

	switch (smId) {
		case 0:
			smNode  = 0x22;	/* X9/XLF */
			break;
		case 1:
			smNode  = 0xf;	/* X9/XLF */
			break;
		case 2:
			smNode  = 0x23;	/* XLF */
			break;
		case 3:
			smNode  = 0x24;	/* XLF */
			break;
		default:
			NCP_CALL(NCP_ST_ERROR);
	}

	/* ctm is populated so it can be commonly used during mc,phy setup */
	NCP_CALL(ncp_sm_common_setup_56xx(dev, smNode, parms, &ctm)); 

	/* Initialize the system memory controller... */
	NCP_CALL(ncp_sm_denali_2041_init_56xx(dev, smNode, parms, &ctm)); 

	NCP_CALL(ncp_sm_ddr4_phy_init(dev, smNode, parms, &ctm)); 

	/* Now go through training */
	NCP_CALL(ncp_sm_ddr4_phy_training(dev, smNode, parms));

	NCP_CALL(ncp_sm_ddr4_post_phy_training_mc_setup(dev, smNode, parms));

ncp_return:
#ifdef NCP_SM_PHY_REG_DUMP
	if ((NCP_ST_SUCCESS != ncpStatus) && (NCP_ST_ERROR != ncpStatus))
	{
		/* Dump contents of synop phy regs */
		NCP_CALL(ncp_sm_ddr4_phy_reg_dump(dev, smNode));
	}
#endif
	return ncpStatus;
}
