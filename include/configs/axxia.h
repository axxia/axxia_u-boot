/*
 * (C) Copyright 2013
 * LSI Corporation <www.lsi.com>
 * John Jacques <john.jacques@lsi.com>
 * Configuration settings for the LSI ACP development boards.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIGS_AXXIA_H
#define __CONFIGS_AXXIA_H

#define CONFIG_AXXIA

#define CONFIG_AXXIA_SERIAL

/*
 */

#define CONFIG_LSI_NCR

/*
  ================================================================================
  ================================================================================
  Parameters
  ================================================================================
  ================================================================================
*/

#ifndef __ASSEMBLY__

#define PARAMETERS_MAGIC 0x12af34ec

#define PARAMETERS_GLOBAL_IGNORE_VOLTAGE     0x00000001
#define PARAMETERS_GLOBAL_IGNORE_CLOCKS      0x00000010
#define PARAMETERS_GLOBAL_IGNORE_SYSMEM      0x00000100
#define PARAMETERS_GLOBAL_IGNORE_PCIESRIO    0x00001000

#define PARAMETERS_GLOBAL_RUN_SYSMEM_BIST    0x80000000
#define PARAMETERS_GLOBAL_SET_L2_FTC         0x40000000
#define PARAMETERS_GLOBAL_SET_L2_DISABLE_SL  0x20000000
#define PARAMETERS_GLOBAL_DISABLE_RESET      0x10000000
#define PARAMETERS_GLOBAL_SM_PHY_REG_RESTORE 0x08000000
#define PARAMETERS_GLOBAL_SM_PHY_REG_DUMP    0x04000000

#ifdef CONFIG_AXXIA_ARM

typedef struct {
	unsigned long version;
	unsigned long flags;
	unsigned long baud_rate;
	unsigned long memory_check_ranges;
} __attribute__((packed)) parameters_global_t;

#else  /* CONFIG_AXXIA_ARM */

typedef struct {
	unsigned long version;
	unsigned long flags;
} __attribute__((packed)) parameters_global_t;

#endif	/* CONFIG_AXXIA_ARM */

typedef struct {
	unsigned long control;
} __attribute__((packed)) parameters_pciesrio_t;

typedef struct {
	unsigned long checksum;
	unsigned long version;
	unsigned long vofs;
	unsigned long tvid;
	unsigned long long twait;
	unsigned long VIDChecks;
	unsigned char vidLT[64];
} __attribute__((packed)) parameters_voltage_t;

#ifdef CONFIG_AXXIA_ARM

typedef struct {
	unsigned long flags;
	unsigned long syspll0_prms;
	unsigned long syspll0_ctrl;
	unsigned long syspll0_csw;
	unsigned long syspll0_div;
	unsigned long syspll0_psd;
	unsigned long cpupll0_prms;
	unsigned long cpupll0_ctrl;
	unsigned long cpupll0_csw;
	unsigned long cpupll0_div;
	unsigned long cpupll0_psd;
	unsigned long smpll0_prms;
	unsigned long smpll0_ctrl;
	unsigned long smpll0_csw;
	unsigned long smpll0_div;
	unsigned long smpll0_psd;
	unsigned long smpll1_prms;
	unsigned long smpll1_ctrl;
	unsigned long smpll1_csw;
	unsigned long smpll1_div;
	unsigned long smpll1_psd;
	unsigned long tmpll0_prms;
	unsigned long tmpll0_ctrl;
	unsigned long tmpll0_csw;
	unsigned long tmpll0_div;
	unsigned long tmpll0_psd;
	unsigned long fabpll0_prms;
	unsigned long fabpll0_ctrl;
	unsigned long fabpll0_csw;
	unsigned long fabpll0_div;
	unsigned long fabpll0_psd;
	unsigned long nrcp_csw;
	unsigned long nrcp_div;
	unsigned long per_csw;
	unsigned long per_div;
	unsigned long emmc_csw;
	unsigned long emmc_div;
	unsigned long debug_csw;
	unsigned long stop_csw;
} __attribute__ ((packed)) parameters_clocks_t;

#else  /* CONFIG_AXXIA_ARM */

typedef struct {
#ifdef CONFIG_AXXIA_25xx
	unsigned long syspll_prms;
	unsigned long syspll_ctrl;
	unsigned long syspll_mcgc;
	unsigned long syspll_mcgc1;
	unsigned long syspll_psd;
	unsigned long ppcpll_prms;
	unsigned long ppcpll_ctrl;
	unsigned long ppcpll_mcgc;
	unsigned long ppcpll_mcgc1;
	unsigned long ppcpll_psd;
	unsigned long smpll_prms;
	unsigned long smpll_ctrl;
	unsigned long smpll_mcgc;
	unsigned long smpll_mcgc1;
	unsigned long smpll_psd;
	unsigned long tmpll_prms;
	unsigned long tmpll_ctrl;
	unsigned long tmpll_mcgc;
	unsigned long tmpll_mcgc1;
	unsigned long tmpll_psd;
	unsigned long per_mcgc;
	unsigned long per_mcgc1;
#else
	unsigned long sys_control;
	unsigned long sys_lftune_upper;
	unsigned long sys_lftune_lower;
	unsigned long sys_fftune;
	unsigned long sys_locktune;
	unsigned long ppc_control;
	unsigned long ppc_lftune_upper;
	unsigned long ppc_lftune_lower;
	unsigned long ppc_fftune;
	unsigned long ppc_locktune;
	unsigned long ddr0_control;
	unsigned long ddr1_control;
	unsigned long ddr_lftune_upper;
	unsigned long ddr_lftune_lower;
	unsigned long ddr_fftune;
	unsigned long ddr_locktune;
#endif
} __attribute__ ((packed)) parameters_clocks_t;

#endif	/* CONFIG_AXXIA_ARM */


typedef unsigned long           ncp_uint32_t;
typedef void *                  ncp_dev_hdl_t;
typedef unsigned long           ncp_region_id_t;
typedef unsigned long           ncp_st_t;

typedef enum {
    NCP_SM_MC_INIT_DONE = 1,
    NCP_SM_LP_OP_DONE,
    NCP_SM_BIST_DONE,
    NCP_SM_LVL_OP_DONE,
    NCP_SM_MR_OP_DONE
} ncp_sm_poll_event_t;

typedef ncp_uint32_t
(*ncp_sm_intr_status_fn_t) (
    ncp_dev_hdl_t   dev,
    ncp_region_id_t regionId,
    ncp_uint32_t    mask);

typedef ncp_st_t
(*ncp_sm_poll_controller_fn_t) (
    ncp_dev_hdl_t   dev,
    ncp_region_id_t regionId,
    ncp_sm_poll_event_t event);


typedef ncp_uint32_t
(*ncp_sm_ecc_enb_fn_t) (
    ncp_dev_hdl_t   dev,
    ncp_region_id_t regionId,
    ncp_uint32_t    value);


typedef struct {
	unsigned long version;
	unsigned long auto_detect;
	unsigned long num_interfaces;
	unsigned long num_ranks_per_interface;
	unsigned long topology;
	unsigned long sdram_device_density;
	unsigned long sdram_device_width;
	unsigned long primary_bus_width;
	unsigned long CAS_latency;
	unsigned long CAS_write_latency;
	unsigned long enableECC;
	unsigned long enable_deskew;
	unsigned long enable_rdlvl;
	unsigned long enable_auto_cpc;
	unsigned long min_phy_cal_delay;
	unsigned long min_ctrl_roundtrip_delay;
	unsigned long single_bit_mpr;
	unsigned long rdcal_cmp_even;
	unsigned long rdcal_cmp_odd;
	unsigned long phy_rdlat;
	unsigned long added_rank_switch_delay;
	unsigned long high_temp_dram;
	unsigned long sdram_rtt_nom;
	unsigned long sdram_rtt_wr;
	unsigned long sdram_data_drv_imp;
	unsigned long phy_adr_imp;
	unsigned long phy_dat_imp;
	unsigned long phy_rcv_imp;
	unsigned long syscacheMode;
	unsigned long syscacheDisable;
	unsigned long half_mem;
	unsigned long address_mirroring;

	unsigned long                  num_bytelanes;
    	unsigned long long           totalSize;
    	ncp_sm_intr_status_fn_t      intrStatFn;
    	ncp_sm_ecc_enb_fn_t          eccEnbFn;
    	ncp_sm_poll_controller_fn_t  pollControllerFn;

} __attribute__((packed)) parameters_sysmem_t;

#ifdef CONFIG_AXXIA_ARM

typedef struct {
	unsigned long retentionSize;
	unsigned long retentionOffset;
	unsigned long sysmemSize;
	unsigned long sysmemOffset;
	unsigned long clocksSize;
	unsigned long clocksOffset;
	unsigned long voltageSize;
	unsigned long voltageOffset;
	unsigned long pciesrioSize;
	unsigned long pciesrioOffset;
	unsigned long globalSize;
	unsigned long globalOffset;
	unsigned long version;
	unsigned long flags;
	unsigned long checksum;
	unsigned long size;
	unsigned long magic;
} __attribute__((packed)) parameters_header_t;

#else  /* CONFIG_AXXIA_ARM */

typedef struct {
	unsigned long sysmemSize;
	unsigned long sysmemOffset;
	unsigned long clocksSize;
	unsigned long clocksOffset;
	unsigned long voltageSize;
	unsigned long voltageOffset;
	unsigned long pciesrioSize;
	unsigned long pciesrioOffset;
	unsigned long globalSize;
	unsigned long globalOffset;
	unsigned long version;
	unsigned long checksum;
	unsigned long size;
	unsigned long magic;
} __attribute__((packed)) parameters_header_t;

#endif	/* CONFIG_AXXIA_ARM */

typedef struct {
	parameters_header_t *header;
	parameters_global_t *global;
	parameters_voltage_t *voltage;
	parameters_pciesrio_t *pciesrio;
	parameters_clocks_t *clocks;
	parameters_sysmem_t *sysmem;
} parameters_t;

extern parameters_header_t *header;
extern parameters_global_t *global;
extern parameters_pciesrio_t *pciesrio;
extern parameters_voltage_t *voltage;
extern parameters_clocks_t *clocks;
extern parameters_sysmem_t *sysmem;
#ifdef CONFIG_AXXIA_ARM
extern void *retention;
#endif

int read_parameters(void);

#ifdef CONFIG_MEMORY_RETENTION
int write_parameters(parameters_t *);
#endif

#ifndef CONFIG_SPL_BUILD
#define CONFIG_CMD_LSI_PARAMETERS
#endif

#endif	/* __ASSEMBLY__ */

/*
  ================================================================================
  ================================================================================
  Networking
  ================================================================================
  ================================================================================
*/

#ifndef CONFIG_SPL_BUILD

#define CONFIG_AXXIA_FEMAC
/*#define CONFIG_AXXIA_EIOA*/

#if defined(CONFIG_AXXIA_FEMAC) || defined(CONFIG_AXXIA_EIOA)
#define CONFIG_AXXIA_NET
#define CONFIG_CMD_NET
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_PING
#endif

#endif	/* CONFIG_SPL_BUILD */

/*
  ================================================================================
  ================================================================================
  SSP Access
  ================================================================================
  ================================================================================
*/

#define SSP_CR0       0x000
#define SSP_CR1       0x004
#define SSP_DR        0x008
#define SSP_SR        0x00c
#define SSP_CPSR      0x010
#define SSP_IMSC      0x014
#define SSP_RIS       0x018
#define SSP_MIS       0x01c
#define SSP_ICR       0x020
#define SSP_DMACR     0x024
#define SSP_CSR       0x030
#define SSP_PERIPHID0 0xfe0
#define SSP_PERIPHID1 0xfe4
#define SSP_PERIPHID2 0xfe8
#define SSP_PERIPHID3 0xfec
#define SSP_PCELLID0  0xff0
#define SSP_PCELLID1  0xff4
#define SSP_PCELLID2  0xff8
#define SSP_PCELLID3  0xffc

#define SSP_DEFAULT_CLOCK  1250000
#define SSP_MAXIMUM_CLOCK 25000000

#ifndef __ASSEMBLY__
int ssp_read(void *, unsigned long, unsigned long);
int ssp_write(void *, unsigned long, unsigned long, int);
int ssp_set_speed(unsigned long *);
int ssp_init(int, int);
#endif

/*
  ======================================================================
  ======================================================================
  Clocks
  ======================================================================
  ======================================================================
*/

#ifndef __ASSEMBLY__

#define CLK_REF0 125000000

typedef enum {
        clock_system, clock_core, clock_memory, clock_peripheral
} acp_clock_t;

int acp_clock_get(acp_clock_t, unsigned long *);

#endif /* __ASSEMBLY__ */

/*
  ================================================================================
  ================================================================================
  Include the Common LSI Header
  ================================================================================
  ================================================================================
*/

#include <configs/lsi.h>

#endif /* __CONFIGS_AXXIA_H */
