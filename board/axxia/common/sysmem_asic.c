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
#include <asm/system.h>
#include <asm/io.h>

#include "ncp_sysmem_ext.h"
#include "ncp_sysmem_lsiphy.h"

#if defined(CONFIG_AXXIA_XLF_EMU) || defined(CONFIG_AXXIA_XLF)
#include "../axc6700/ncp_l3lock_region.h"
#endif

ncp_st_t
ncp_sysmem_init_synopphy(ncp_dev_hdl_t, ncp_uint32_t, ncp_sm_parms_t *);

ncp_st_t
ncp_treemem_init_synopphy(ncp_dev_hdl_t, ncp_uint32_t, ncp_sm_parms_t *);

ncp_st_t
ncp_elm_init(ncp_dev_hdl_t, ncp_sm_parms_t *);

ncp_st_t
ncp_elm_sysmem_fill(ncp_dev_hdl_t, ncp_sm_parms_t *);

#ifdef DISPLAY_PARAMETERS
static void
display_mem_parameters(const char *title, parameters_mem_t *parameters)
{
	int i;

	printf("-- -- %s\n", title);

	printf("version=0x%08x\n", parameters->version);
	printf("ddrClockSpeedMHz=0x%08x\n", parameters->ddrClockSpeedMHz);
	printf("auto_detect=0x%08x\n", parameters->autoDetect);
	printf("num_interfaces=0x%08x\n", parameters->num_interfaces);
	printf("num_ranks_per_interface=0x%08x\n",
	       parameters->num_ranks_per_interface);
	printf("primary_bus_width=0x%08x\n", parameters->primary_bus_width);
	printf("topology=0x%08x\n", parameters->topology);
	printf("min_ctrl_roundtrip_delay=0x%08x\n",
	       parameters->minCtrlRoundtripDelay);
	printf("phy_rdlat=0x%08x\n", parameters->phy_rdlat);
	printf("addedRankSwitchDly=0x%08x\n",
	       parameters->addedRankSwitchDly);
	printf("zqcs_interval=0x%08x\n", parameters->zqcs_interval);
	printf("enableECC=0x%08x\n", parameters->enableECC);
	printf("enable_runtime_updates=0x%08x\n",
	       parameters->enableRuntime);
	printf("dramPrechargePolicy=0x%08x\n", parameters->dramPrechargePolicy);
	printf("open_page_size=0x%08x\n", parameters->open_page_size);
	printf("syscacheControl=0x%08x\n", parameters->syscacheControl);
	printf("sdram_device_density=0x%08x\n", parameters->sdram_device_density);
	printf("sdram_device_width=0x%08x\n", parameters->sdram_device_width);
	printf("CAS_latency=0x%08x\n", parameters->CAS_latency);
	printf("CAS_write_latency=0x%08x\n", parameters->CAS_write_latency);
	printf("address_mirroring=0x%08x\n", parameters->address_mirroring);
	printf("registeredDIMM=0x%08x\n", parameters->registeredDimm);
	printf("rdimm_ctl_0_0=0x%08x\n", parameters->rdimm_ctl_0_0);
	printf("rdimm_ctl_0_1=0x%08x\n", parameters->rdimm_ctl_0_1);
	printf("rdimm_msic=0x%08x\n", parameters->rdimm_misc);
	printf("write_ODT_ctl=0x%08x\n", parameters->write_ODT_ctl);
	printf("read_ODT_ctl=0x%08x\n", parameters->read_ODT_ctl);
	printf("single_bit_mpr=0x%08x\n", parameters->singleBitMPR);
	printf("high_temp_dram=0x%08x\n", parameters->high_temp_dram);

	for (i = 0; i < 2; i++) {
		unsigned *p;

		p = (unsigned *)parameters->per_sysmem[i].sdram_rtt_nom;
		printf("RTTnom=0x%08x\n", *p++);
		printf("RTTwr=0x%08x\n", *p++);
		printf("drvimp=0x%08x\n", *p++);

		printf("phy_min_cal_delay=0x%08x\n",
		       parameters->per_sysmem[i].phy_min_cal_delay);
		printf("phy_adr_phase_select=0x%08x\n",
		       parameters->per_sysmem[i].phy_adr_phase_select);
		printf("phy_dp_io_vref_set=0x%08x\n",
		       parameters->per_sysmem[i].phy_dp_io_vref_set);
		printf("phy_adr_io_vref_set=0x%08x\n",
		       parameters->per_sysmem[i].phy_adr_io_vref_set);
		printf("phy_rdlvl_cmp_even=0x%08x\n",
		       parameters->per_sysmem[i].phy_rdlvl_cmp_even);
		printf("phy_rdlvl_cmp_odd=0x%08x\n",
		       parameters->per_sysmem[i].phy_rdlvl_cmp_odd);
		printf("phy_write_align_finetune=0x%08x\n",
		       parameters->per_sysmem[i].phy_write_align_finetune);
	}

	printf("dram_class=0x%08x\n", parameters->dram_class);

	for (i = 0; i < 4; i++) {
		unsigned *p;

		p = (unsigned *)parameters->per_smem[i].sdram_rtt_nom;
		printf("RTTnom=0x%08x\n", *p++);
		printf("RTTwr=0x%08x\n", *p++);
		printf("drvimp=0x%08x\n", *p++);
	}

	printf("additive_latency=0x%08x\n", parameters->additive_latency);
	printf("binned_CAS_latency=0x%08x\n", parameters->binned_CAS_latency);
	printf("tck_ps=0x%08x\n", parameters->tck_ps);
	printf("refresh_mode=0x%08x\n", parameters->refresh_mode);
	printf("address_inversion=0x%08x\n", parameters->address_inversion);
	printf("bstlen=0x%08x\n", parameters->bstlen);
	printf("dm_masking=0x%08x\n", parameters->dm_masking);
	printf("rdimm_ctl_0_0=0x%08x\n", parameters->rdimm_ctl_0_0);
	printf("rdimm_ctl_0_1=0x%08x\n", parameters->rdimm_ctl_0_1);
	printf("rdimm_ctl_0_2=0x%08x\n", parameters->rdimm_ctl_0_2);
	printf("rdimm_ctl_0_3=0x%08x\n", parameters->rdimm_ctl_0_3);
	printf("rdimm_ctl_0_4=0x%08x\n", parameters->rdimm_ctl_0_4);
	printf("rdimm_ctl_1_0=0x%08x\n", parameters->rdimm_ctl_1_0);
	printf("rdimm_ctl_1_1=0x%08x\n", parameters->rdimm_ctl_1_1);
	printf("rdimm_ctl_1_2=0x%08x\n", parameters->rdimm_ctl_1_2);
	printf("rdimm_ctl_1_3=0x%08x\n", parameters->rdimm_ctl_1_3);
	printf("rdimm_ctl_1_4=0x%08x\n", parameters->rdimm_ctl_1_4);
	printf("vref_cs=0x%08x\n", parameters->vref_cs);
	printf("vref_val=0x%08x\n", parameters->vref_val);
	printf("wr_protect_en_mask=0x%08x\n", parameters->wr_protect_en_mask);
	printf("dbi_rd_en=0x%08x\n", parameters->dbi_rd_en);
	printf("dbi_wr_en=0x%08x\n", parameters->dbi_wr_en);
	printf("ca_parity_en; =0x%08x\n", parameters->ca_parity_en);
	printf("rdlvl_interval;=0x%08x\n", parameters->rdlvl_interval);
	printf("rdlvl_gate_interval=0x%08x\n", parameters->rdlvl_gate_interval);
	printf("preamble_support=0x%08x\n", parameters->preamble_support);
	printf("crc_mode=0x%08x\n", parameters->crc_mode);

	printf("dq_map_0[] = {");
	for (i = 0; i < 18; i++) {
		printf("0x%02x", parameters->dq_map_0[i]);

		if (i < 17)
			printf(", ");
	}
	printf("}\n");

	printf("dq_map_1[] = {");
	for (i = 0; i < 18; i++) {
		printf("0x%02x", parameters->dq_map_1[i]);

		if (i < 17)
			printf(", ");
	}
	printf("}\n");

	printf("dq_map_odd_rank_swap_0=0x%08x\n",
	       parameters->dq_map_odd_rank_swap_0);
	printf("dq_map_odd_rank_swap_1=0x%08x\n",
	       parameters->dq_map_odd_rank_swap_1);

	return;
}
#endif

/*
  ==============================================================================
  ==============================================================================
  ==============================================================================
  System Memory Initialization
  ==============================================================================
  ==============================================================================
  ==============================================================================
*/

/*
  ------------------------------------------------------------------------------
  cmem_init
*/

int
cmem_init(void)
{
#if defined(CONFIG_AXXIA_56XX) || defined(CONFIG_AXXIA_56XX_SIM)
	unsigned cm_nodes[] = {0x8, 0x9};
	int offset = 2;
#else
	unsigned cm_nodes[] = {0x8};
	int offset = 4;
#endif
	int i;
	int rc;

#ifdef DISPLAY_PARAMETERS
	display_mem_parameters("Tree Memory", cmem);
#endif

	for (i = 0; i < sizeof(cm_nodes)/sizeof(unsigned); ++i) {
		rc = ncp_treemem_init_synopphy(NULL, i + offset, cmem);

		if (NCP_ST_SUCCESS != rc) {
			printf("Initializing Tree Memory Node 0x%x Failed!\n",
			       cm_nodes[i]);

			return -1;
		}
	}

	return 0;
}

/*
  ------------------------------------------------------------------------------
  sysmem_init
*/

int
sysmem_init(void)
{
#if defined(CONFIG_AXXIA_56XX) || defined(CONFIG_AXXIA_56XX_SIM)
	unsigned sm_nodes[] = {0x22, 0xf};
#else
	unsigned sm_nodes[] = {0x22, 0xf, 0x23, 0x24};
#endif
#if defined(CONFIG_AXXIA_XLF_EMU) || defined(CONFIG_AXXIA_XLF)
	ncp_l3lock_region_info_t *ncp_l3lock_region_info;
#endif
	int i;
	ncp_uint32_t version_save;
	int rc = NCP_ST_SUCCESS;
#ifdef CONFIG_AXXIA_ANY_XLF
	int ncpStatus = NCP_ST_SUCCESS;
#endif

#ifdef DISPLAY_PARAMETERS
	display_mem_parameters("System Memory", sysmem);
#endif

	/*
	  Save the version of the parameter subsection and replace it
	  with the chip version as expected by the RTE code.
	*/

	version_save = sysmem->version;
#if defined(CONFIG_AXXIA_56XX) || defined(CONFIG_AXXIA_56XX_SIM)
	sysmem->version = NCP_CHIP_ACP56xx;
#elif defined(CONFIG_AXXIA_XLF) || defined(CONFIG_AXXIA_XLF_SIM)
	sysmem->version = NCP_CHIP_ACPXLF;
#else
#error "Invalid Chip Type!"
#endif

	if (sysmem->num_interfaces > ((sizeof(sm_nodes) / sizeof(unsigned)))) {
		printf("Number of Interfaces is Too Large\n");

		return -1;
	}

	/* X9 requires sysmem parameters version 3, XLF requires version 4. */
#ifdef CONFIG_AXXIA_ANY_XLF
	if (4 != version_save) {
		printf("Wrong Memory Parameter Version: %d\n", version_save);

		return -1;
	}
#endif
#ifdef CONFIG_AXXIA_ANY_56XX
	if (3 != version_save) {
		printf("Wrong Memory Parameter Version: %d\n", version_save);

		return -1;
	}
#endif

	/* Disable System Cache */
	__asm_disable_l3_cache();

	/* Initialize Memory */
#ifdef CONFIG_AXXIA_ANY_56XX
	for (i = 0; i < sysmem->num_interfaces; ++i) {
		rc = ncp_sysmem_init_synopphy(NULL, i, sysmem);

		if (NCP_ST_SUCCESS != rc) {
 			printf("Initializing Sysmem Node 0x%x Failed!\n",
			       sm_nodes[i]);

			return -1;
		}
	}
#endif
#ifdef CONFIG_AXXIA_ANY_XLF
	/*
	  For x1 any single interface is ok, for x2 0 & 2 or 1 & 3
	  are only valid, for x3 any 3 ok, for x4 all
	*/
	if ((sysmem->interface_sel > 0) &&
	    (sysmem->interface_sel != 0xf) && !(sysmem->interface_sel % 3))
		NCP_CALL(NCP_ST_INVALID_VALUE);

	/*
	  supports DRAM configuration of the kind x1,x2,x3,x4
	*/
	for (i = 0; i < 4; i++)
		if (0 != (sysmem->interface_sel & (1 << i))) {
                        rc = ncp_sysmem_init_synopphy(NULL, i, sysmem);

			if (NCP_ST_SUCCESS != rc) {
				printf("Initializing Sysmem Node 0x%x Failed!\n",
				       sm_nodes[i]);

				return -1;
			}
		}
#endif

	/* Set up the VAT */
	ncr_write32(NCP_REGION_ID(0x16, 0x10), 0x1000, 0xa200000f);
	ncr_write32(NCP_REGION_ID(0x16, 0x10), 0x1004, 0xffffff00);
	ncr_write32(NCP_REGION_ID(0x16, 0x10), 0x1008, 0);
	ncr_write32(NCP_REGION_ID(0x16, 0x10), 0x100c, 0);

	/* Then the ELM mode. */
#ifdef CONFIG_AXXIA_ANY_56XX
	if (1 == sysmem->num_interfaces) {
		unsigned int value;

		NCP_COMMENT("Setting single-ELM-0 mode\n");

		writel(0x4, ((DICKENS | (0x20 << 16)) + 0x8));
		writel(0x4, ((DICKENS | (0x21 << 16)) + 0x8));
		writel(0x4, ((DICKENS | (0x22 << 16)) + 0x8));
		writel(0x4, ((DICKENS | (0x23 << 16)) + 0x8));
		writel(0x4, ((DICKENS | (0x24 << 16)) + 0x8));
		writel(0x4, ((DICKENS | (0x25 << 16)) + 0x8));
		writel(0x4, ((DICKENS | (0x26 << 16)) + 0x8));
		writel(0x4, ((DICKENS | (0x27 << 16)) + 0x8));

		value = readl(ELM0 + 4);
		value &= 0xfffffdff;
		writel(value, ELM0 + 4);
	} else {
		writel(0x4, ((DICKENS | (0x20 << 16)) + 0x8));
		writel(0x4, ((DICKENS | (0x21 << 16)) + 0x8));
		writel(0x4, ((DICKENS | (0x22 << 16)) + 0x8));
		writel(0x4, ((DICKENS | (0x23 << 16)) + 0x8));
		writel(0xe, ((DICKENS | (0x24 << 16)) + 0x8));
		writel(0xe, ((DICKENS | (0x25 << 16)) + 0x8));
		writel(0xe, ((DICKENS | (0x26 << 16)) + 0x8));
		writel(0xe, ((DICKENS | (0x27 << 16)) + 0x8));
	}
#endif
#ifdef CONFIG_AXXIA_ANY_XLF
	if (0 != (sysmem->interface_sel & 0x1)) {
                ncr_write32(NCP_REGION_ID(0x170,0x1), 0x42800, 0x2);

                /* use only elm0 */
		writel(0x3, ((DICKENS | (0x20 << 16)) + 0x8));
		writel(0x3, ((DICKENS | (0x21 << 16)) + 0x8));
		writel(0x3, ((DICKENS | (0x22 << 16)) + 0x8));
		writel(0x3, ((DICKENS | (0x23 << 16)) + 0x8));
		writel(0x3, ((DICKENS | (0x24 << 16)) + 0x8));
		writel(0x3, ((DICKENS | (0x25 << 16)) + 0x8));
		writel(0x3, ((DICKENS | (0x26 << 16)) + 0x8));
		writel(0x3, ((DICKENS | (0x27 << 16)) + 0x8));

                ncr_write32(NCP_REGION_ID(0x170,0x1), 0x42800, 0x0);
	}

	if (0 != (sysmem->interface_sel & 0x2)) {
                ncr_write32(NCP_REGION_ID(0x170,0x1), 0x42800, 0x2);

                /* use only elm1 */
		writel(0x8, ((DICKENS | (0x20 << 16)) + 0x8));
		writel(0x8, ((DICKENS | (0x21 << 16)) + 0x8));
		writel(0x8, ((DICKENS | (0x22 << 16)) + 0x8));
		writel(0x8, ((DICKENS | (0x23 << 16)) + 0x8));
		writel(0x8, ((DICKENS | (0x24 << 16)) + 0x8));
		writel(0x8, ((DICKENS | (0x25 << 16)) + 0x8));
		writel(0x8, ((DICKENS | (0x26 << 16)) + 0x8));
		writel(0x8, ((DICKENS | (0x27 << 16)) + 0x8));

                ncr_write32(NCP_REGION_ID(0x170,0x1), 0x42800, 0x0);
	}

	if (0 != (sysmem->interface_sel & 0x4)) {
                ncr_write32(NCP_REGION_ID(0x170,0x1), 0x42800, 0x2);

                /* use only elm2 */
		writel(0x15, ((DICKENS | (0x20 << 16)) + 0x8));
		writel(0x15, ((DICKENS | (0x21 << 16)) + 0x8));
		writel(0x15, ((DICKENS | (0x22 << 16)) + 0x8));
		writel(0x15, ((DICKENS | (0x23 << 16)) + 0x8));
		writel(0x15, ((DICKENS | (0x24 << 16)) + 0x8));
		writel(0x15, ((DICKENS | (0x25 << 16)) + 0x8));
		writel(0x15, ((DICKENS | (0x26 << 16)) + 0x8));
		writel(0x15, ((DICKENS | (0x27 << 16)) + 0x8));

                ncr_write32(NCP_REGION_ID(0x170,0x1), 0x42800, 0x0);
	}

	if (0 != (sysmem->interface_sel & 0x8)) {
                ncr_write32(NCP_REGION_ID(0x170,0x1), 0x42800, 0x2);

                /* use only elm2 */
		writel(0x1a, ((DICKENS | (0x20 << 16)) + 0x8));
		writel(0x1a, ((DICKENS | (0x21 << 16)) + 0x8));
		writel(0x1a, ((DICKENS | (0x22 << 16)) + 0x8));
		writel(0x1a, ((DICKENS | (0x23 << 16)) + 0x8));
		writel(0x1a, ((DICKENS | (0x24 << 16)) + 0x8));
		writel(0x1a, ((DICKENS | (0x25 << 16)) + 0x8));
		writel(0x1a, ((DICKENS | (0x26 << 16)) + 0x8));
		writel(0x1a, ((DICKENS | (0x27 << 16)) + 0x8));

                ncr_write32(NCP_REGION_ID(0x170,0x1), 0x42800, 0x0);
	}

	/*set bit 9 of ELMs to force to use single ELM*/
	for (i = 0; i < 4; ++i)	{
		unsigned int tmp;

                ncr_read32(NCP_REGION_ID(0x167, i), 0x0004, &tmp);
                tmp &= 0xFFFFF9FF;
                ncr_write32(NCP_REGION_ID(0x167, i), 0x0004, tmp);
	}
#endif

	/* Initialize the ELMs */
	rc = ncp_elm_init(NULL, sysmem);

	if (NCP_ST_SUCCESS != rc) {
		printf("Initializing ELMs Failed!\n");

		return -1;
	}

	if (0 != sysmem->enableECC) {
		rc = ncp_elm_sysmem_fill(NULL, sysmem);

		if (NCP_ST_SUCCESS != rc) {
			printf("Filling Sysmem Failed!\n");

			return -1;
		}
	}

#if defined(CONFIG_AXXIA_XLF_EMU) || defined(CONFIG_AXXIA_XLF)
	ncp_l3lock_region_info = (ncp_l3lock_region_info_t *)
		&sysmem->total_l3_locked_size;
#endif

#if defined(CONFIG_AXXIA_XLF_EMU)
	rc = ncp_l3lock_region_init(NULL, ncp_l3lock_region_info, 1);
#elif defined(CONFIG_AXXIA_XLF)
	rc = ncp_l3lock_region_init(NULL, ncp_l3lock_region_info, 0);
#endif

#if defined(CONFIG_AXXIA_XLF_EMU) || defined(CONFIG_AXXIA_XLF)
	if (NCP_ST_SUCCESS != rc)
		printf("Locking L3 Cache Failed!\n");
#endif

	/* Re-enable the L3 cache. */
	__asm_enable_l3_cache();

	/*
	  Restore the version of the parameter subsection.
	*/

	sysmem->version = version_save;

	NCP_RETURN_LABEL;

	return rc;
}
