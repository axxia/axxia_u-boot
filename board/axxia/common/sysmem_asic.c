/*
 *  Copyright (C) 2010 LSI Corporation
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software;you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation;either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY;without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program;if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>

ncp_st_t
ncp_sysmem_init_synopphy(ncp_dev_hdl_t, ncp_uint32_t, ncp_sm_parms_t *);

/*
  ==============================================================================
  ==============================================================================
  ==============================================================================
  System Memory Initialization
  ==============================================================================
  ==============================================================================
  ==============================================================================
*/

int
sysmem_init(void)
{
#if defined(CONFIG_AXXIA_56XX) || defined(CONFIG_AXXIA_56XX_SIM)
	unsigned sm_nodes[] = {0x22, 0xf};
#else
	unsigned sm_nodes[] = {0x22, 0xf, 0x23, 0x24};
#endif
	int i;
	int rc;

#ifdef DISPLAY_PARAMETERS
	printf("-- -- Sysmem Parameters \n");

	printf("version=0x%08x\n", sysmem->version);
	printf("ddrClockSpeedMHz=0x%08x\n", sysmem->ddrClockSpeedMHz);
	printf("auto_detect=0x%08x\n", sysmem->autoDetect);
	printf("num_interfaces=0x%08x\n", sysmem->numInterfaces);
	printf("num_ranks_per_interface=0x%08x\n", sysmem->numRanks);
	printf("primary_bus_width=0x%08x\n", sysmem->primary_bus_width);
	printf("topology=0x%08x\n", sysmem->topology);
	printf("min_ctrl_roundtrip_delay=0x%08x\n",
	       sysmem->minCtrlRoundtripDelay);
	printf("phy_rdlat=0x%08x\n", sysmem->phy_rdlat);
	printf("addedRankSwitchDly=0x%08x\n",
	       sysmem->addedRankSwitchDly);
	printf("zqcs_interval=0x%08x\n", sysmem->zqcs_interval);
	printf("enableECC=0x%08x\n", sysmem->enableECC);
	printf("enable_runtime_updates=0x%08x\n",
	       sysmem->enableRuntime);
	printf("dramPrechargePolicy=0x%08x\n", sysmem->dramPrechargePolicy);
	printf("open_page_size=0x%08x\n", sysmem->open_page_size);
	printf("syscacheControl=0x%08x\n", sysmem->syscacheControl);
	printf("sdram_device_density=0x%08x\n", sysmem->sdram_device_density);
	printf("sdram_device_width=0x%08x\n", sysmem->sdram_device_width);
	printf("CAS_latency=0x%08x\n", sysmem->CAS_latency);
	printf("CAS_write_latency=0x%08x\n", sysmem->CAS_write_latency);
	printf("address_mirroring=0x%08x\n", sysmem->address_mirroring);
	printf("registeredDIMM=0x%08x\n", sysmem->registeredDimm);
	printf("rdimm_ctl_0_0=0x%08x\n", sysmem->rdimmCtl_0);
	printf("rdimm_ctl_0_1=0x%08x\n", sysmem->rdimmCtl_1);
	printf("rdimm_msic=0x%08x\n", sysmem->rdimm_misc);
	printf("write_ODT_ctl=0x%08x\n", sysmem->write_ODT_ctl);
	printf("read_ODT_ctl=0x%08x\n", sysmem->read_ODT_ctl);
	printf("single_bit_mpr=0x%08x\n", sysmem->singleBitMPR);
	printf("high_temp_dram=0x%08x\n", sysmem->high_temp_dram);

	for (i = 0; i < 2; i++) {
		unsigned *p;

		p = (unsigned *)sysmem->per_sysmem[i].sdram_rtt_nom;
		printf("RTTnom=0x%08x\n", *p++);
		printf("RTTwr=0x%08x\n", *p++);
		printf("drvimp=0x%08x\n", *p++);

		printf("phy_min_cal_delay=0x%08x\n",
		       sysmem->per_sysmem[i].phy_min_cal_delay);
		printf("phy_adr_phase_select=0x%08x\n",
		       sysmem->per_sysmem[i].phy_adr_phase_select);
		printf("phy_dp_io_vref_set=0x%08x\n",
		       sysmem->per_sysmem[i].phy_dp_io_vref_set);
		printf("phy_adr_io_vref_set=0x%08x\n",
		       sysmem->per_sysmem[i].phy_adr_io_vref_set);
		printf("phy_rdlvl_cmp_even=0x%08x\n",
		       sysmem->per_sysmem[i].phy_rdlvl_cmp_even);
		printf("phy_rdlvl_cmp_odd=0x%08x\n",
		       sysmem->per_sysmem[i].phy_rdlvl_cmp_odd);
		printf("phy_write_align_finetune=0x%08x\n",
		       sysmem->per_sysmem[i].phy_write_align_finetune);
	}

	printf("dram_class=0x%08x\n", sysmem->dram_class);

	for (i = 0; i < 4; i++) {
		unsigned *p;

		p = (unsigned *)sysmem->per_smem[i].sdram_rtt_nom;
		printf("RTTnom=0x%08x\n", *p++);
		printf("RTTwr=0x%08x\n", *p++);
		printf("drvimp=0x%08x\n", *p++);
	}

	printf("additive_latency=0x%08x\n", sysmem->additive_latency);
	printf("binned_CAS_latency=0x%08x\n", sysmem->binned_CAS_latency);
	printf("tck_ps=0x%08x\n", sysmem->tck_ps);
	printf("refresh_mode=0x%08x\n", sysmem->refresh_mode);
	printf("address_inversion=0x%08x\n", sysmem->address_inversion);
	printf("bstlen=0x%08x\n", sysmem->bstlen);
	printf("dm_masking=0x%08x\n", sysmem->dm_masking);
	printf("rdimm_ctl_0_0=0x%08x\n", sysmem->rdimm_ctl_0_0);
	printf("rdimm_ctl_0_1=0x%08x\n", sysmem->rdimm_ctl_0_1);
	printf("rdimm_ctl_0_2=0x%08x\n", sysmem->rdimm_ctl_0_2);
	printf("rdimm_ctl_0_3=0x%08x\n", sysmem->rdimm_ctl_0_3);
	printf("rdimm_ctl_0_4=0x%08x\n", sysmem->rdimm_ctl_0_4);
	printf("rdimm_ctl_1_0=0x%08x\n", sysmem->rdimm_ctl_1_0);
	printf("rdimm_ctl_1_1=0x%08x\n", sysmem->rdimm_ctl_1_1);
	printf("rdimm_ctl_1_2=0x%08x\n", sysmem->rdimm_ctl_1_2);
	printf("rdimm_ctl_1_3=0x%08x\n", sysmem->rdimm_ctl_1_3);
	printf("rdimm_ctl_1_4=0x%08x\n", sysmem->rdimm_ctl_1_4);
	printf("vref_en=0x%08x\n", sysmem->vref_en);
	printf("vref_cs=0x%08x\n", sysmem->vref_cs);
	printf("vref_val=0x%08x\n", sysmem->vref_val);
	printf("wr_protect_en_mask=0x%08x\n", sysmem->wr_protect_en_mask);
	printf("rdlvl_en=0x%08x\n", sysmem->rdlvl_en);
	printf("dbi_rd_en=0x%08x\n", sysmem->dbi_rd_en);
	printf("dbi_wr_en=0x%08x\n", sysmem->dbi_wr_en);
	printf("ca_parity_en; =0x%08x\n", sysmem->ca_parity_en);
	printf("rdlvl_gate_en=0x%08x\n", sysmem->rdlvl_gate_en);
	printf("rdlvl_interval;=0x%08x\n", sysmem->rdlvl_interval);
	printf("rdlvl_gate_interval=0x%08x\n", sysmem->rdlvl_gate_interval);
	printf("preamble_support=0x%08x\n", sysmem->preamble_support);
	printf("crc_mode=0x%08x\n", sysmem->crc_mode);

	printf("dq_map_0[] = {");
	for (i = 0; i < 18; i++) {
		printf("0x%02x", sysmem->dq_map_0[i]);

		if (i < 17)
			printf(", ");
	}
	printf("}\n");

	printf("dq_map_1[] = {");
	for (i = 0; i < 18; i++) {
		printf("0x%02x", sysmem->dq_map_1[i]);

		if (i < 17)
			printf(", ");
	}
	printf("}\n");

	printf("dq_map_odd_rank_swap_0=0x%08x\n",
	       sysmem->dq_map_odd_rank_swap_0);
	printf("dq_map_odd_rank_swap_1=0x%08x\n",
	       sysmem->dq_map_odd_rank_swap_1);
#endif

	for (i = 0; i < sizeof(sm_nodes)/sizeof(unsigned); ++i) {
		rc = ncp_sysmem_init_synopphy(NULL, i, sysmem);

		if (NCP_ST_SUCCESS != rc) {
			printf("Initializing Sysmem Node 0x%x Failed!\n",
			       sm_nodes[i]);

			return -1;
		}
	}

	return 0;
}
