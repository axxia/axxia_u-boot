/*
 * Copyright (C) 2015 Intel
 *
 * Common definitions for Axxia.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __AXXIA_H
#define __AXXIA_H

#define CONFIG_AXXIA

#define CONFIG_AXXIA_SERIAL

/*
 */

#define CONFIG_LSI_NCR

#ifndef __ASSEMBLY__
void ncr_tracer_enable(void);
void ncr_tracer_disable(void);
int ncr_tracer_is_enabled(void);
void ncr_sysmem_init_mode_enable(void);
void ncr_sysmem_init_mode_disable(void);
#endif

/*
  ==============================================================================
  ==============================================================================
  Parameters
  ==============================================================================
  ==============================================================================
*/

#ifndef __ASSEMBLY__

#define PARAMETERS_MAGIC 0x12af34ec

#define PARAMETERS_GLOBAL_SET_VOLTAGE      0x00000001
#define PARAMETERS_GLOBAL_SET_CLOCKS       0x00000002
#define PARAMETERS_GLOBAL_SET_PEI          0x00000004
#define PARAMETERS_GLOBAL_SET_SMEM         0x00000008
#define PARAMETERS_GLOBAL_SET_CMEM         0x00000010
#define PARAMETERS_GLOBAL_ENABLE_RETENTION 0x00000020
#define PARAMETERS_GLOBAL_ENABLE_SW_MEM_MTEST 0x00800000
#define PARAMETERS_GLOBAL_ENABLE_SW_MEM_ADDR_TEST 0x01000000
#define PARAMETERS_GLOBAL_ENABLE_SW_MEM_DATA_TEST 0x02000000
#define PARAMETERS_GLOBAL_DISABLE_RESET    0x10000000
#define PARAMETERS_GLOBAL_RUN_CMEM_BIST    0x20000000
#define PARAMETERS_GLOBAL_RUN_SMEM_RANGES  0x40000000
#define PARAMETERS_GLOBAL_RUN_SMEM_BIST    0x80000000

typedef long long               ncp_int64_t;
typedef unsigned long long      ncp_uint64_t;
typedef unsigned                ncp_uint32_t;
typedef long                    ncp_int32_t;
typedef unsigned short          ncp_uint16_t;
typedef unsigned char           ncp_uint8_t;
typedef unsigned char           ncp_bool_t;
typedef void *                  ncp_dev_hdl_t;
typedef unsigned                ncp_region_id_t;

typedef enum {
	NCP_ST_SUCCESS = 0,
	NCP_ST_ERROR,
	NCP_ST_SYSMEM_INVALID_ID,
	NCP_ST_SYSMEM_PHY_CPC_CAL_TIMEOUT,
	NCP_ST_SYSMEM_PHY_TRAIN_TIMEOUT,
	NCP_ST_SYSMEM_PHY_TRAIN_SW_TIMEOUT,
	NCP_ST_SYSMEM_PHY_WL_ERR,
	NCP_ST_SYSMEM_PHY_WL_DLY_ERR,
	NCP_ST_SYSMEM_PHY_ECC_WL_ERR,
	NCP_ST_SYSMEM_PHY_ECC_WL_DLY_ERR,
	NCP_ST_SYSMEM_PHY_RDFIFO_OPT_ERR,
	NCP_ST_SYSMEM_PHY_CPC_ERR,
	NCP_ST_SYSMEM_PHY_RD_DLY_ERR,
	NCP_ST_SYSMEM_PHY_RD_CAL_ERR,
	NCP_ST_SYSMEM_PHY_WR_LVL_ERR,
	NCP_ST_SYSMEM_PHY_RD_LVL_ERR,
	NCP_ST_SYSMEM_PHY_GT_TRN_ERR,
	NCP_ST_SYSMEM_PHY_CMD_DLY_ERR,
	NCP_ST_TREEMEM_DDR_INIT_ERR,
	NCP_ST_POLL_TIMEOUT
} ncp_st_t;

/*
 * enumerated type for the four 'standard' topologies
 * the values are assigned as a bit mask of which ranks
 * (chip selects) exist.
 */
typedef enum {
	NCP_SM_TOPO_ONE_SINGLE_RANK = 0x1,
	NCP_SM_TOPO_ONE_DUAL_RANK   = 0x3,
	NCP_SM_TOPO_TWO_SINGLE_RANK = 0x5,
	NCP_SM_TOPO_TWO_DUAL_RANK   = 0xf
} ncp_sm_topology_t;

typedef enum {
	/*
	  NCP_SM_SDRAM_DENSITY_256MBIT  = 0,
	*/
	NCP_SM_SDRAM_DENSITY_512MBIT  = 1,
	NCP_SM_SDRAM_DENSITY_1GBIT    = 2,
	NCP_SM_SDRAM_DENSITY_2GBIT    = 3,
	NCP_SM_SDRAM_DENSITY_4GBIT    = 4,
	NCP_SM_SDRAM_DENSITY_8GBIT    = 5,
	NCP_SM_SDRAM_DENSITY_16GBIT   = 6
} ncp_sm_sdram_density_t;

typedef enum {
	NCP_SM_SDRAM_WIDTH_4BITS  = 0,
	NCP_SM_SDRAM_WIDTH_8BITS  = 1,
	NCP_SM_SDRAM_WIDTH_16BITS = 2,
	NCP_SM_SDRAM_WIDTH_32BITS = 3
} ncp_sm_sdram_width_t;

typedef enum {
	NCP_SM_PRIMARY_BUS_WIDTH_8BITS  = 0,
	NCP_SM_PRIMARY_BUS_WIDTH_16BITS = 1,
	NCP_SM_PRIMARY_BUS_WIDTH_32BITS = 2,
	NCP_SM_PRIMARY_BUS_WIDTH_64BITS = 3
} ncp_sm_primary_bus_width_t;

typedef struct __attribute__((packed)) {
	unsigned char sdram_rtt_nom[4];
	unsigned char sdram_rtt_wr[4];
	unsigned char sdram_data_drv_imp[4];
	unsigned long phy_min_cal_delay;
	unsigned long phy_adr_phase_select;
	unsigned long phy_dp_io_vref_set;
	unsigned long phy_adr_io_vref_set;
	unsigned long phy_rdlvl_cmp_even;
	unsigned long phy_rdlvl_cmp_odd;
	unsigned long phy_write_align_finetune;
} ncp_per_sysmem_parms_t;

typedef enum {
	NCP_SM_DDR3_MODE = 6,
	NCP_SM_DDR4_MODE = 10
} ncp_dram_class_t;

typedef enum {
	NCP_SM_REFRESH_MODE_1X = 0,
	NCP_SM_REFRESH_MODE_2X = 1,
	NCP_SM_REFRESH_MODE_4X = 2
} ncp_refresh_mode_t;

extern ncp_uint32_t sm_nodes[];

#ifdef CONFIG_AXXIA_ARM

typedef struct {
	unsigned version;
	unsigned flags;
	unsigned baud_rate;
	unsigned memory_ranges[16];
	unsigned sequence;
	char description[128];
} __attribute__((packed)) parameters_global_t;

#else  /* CONFIG_AXXIA_ARM */

typedef struct {
	unsigned version;
	unsigned flags;
} __attribute__((packed)) parameters_global_t;

#endif	/* CONFIG_AXXIA_ARM */

#ifdef CONFIG_AXXIA_ARM
typedef struct {
	unsigned version;
	unsigned char offsets[128];
} __attribute__((packed)) parameters_voltage_t;
#else
typedef struct {
	unsigned checksum;
	unsigned version;
	unsigned vofs;
	unsigned tvid;
	unsigned long long twait;
	unsigned VIDChecks;
	unsigned char vidLT[64];
} __attribute__((packed)) parameters_voltage_t;
#endif

#ifdef CONFIG_AXXIA_ARM
typedef struct {
	unsigned version;
	unsigned flags;
	unsigned syspll_prms;
	unsigned syspll_ctrl;
	unsigned syspll_csw;
	unsigned syspll_div;
	unsigned syspll_psd;
	unsigned cpupll_prms;
	unsigned cpupll_ctrl;
	unsigned cpupll_csw;
	unsigned cpupll_div;
	unsigned cpupll_psd;
	unsigned sm0pll_prms;
	unsigned sm0pll_ctrl;
	unsigned sm0pll_csw;
	unsigned sm0pll_div;
	unsigned sm0pll_psd;
	unsigned sm1pll_prms;
	unsigned sm1pll_ctrl;
	unsigned sm1pll_csw;
	unsigned sm1pll_div;
	unsigned sm1pll_psd;
	unsigned tmpll_prms;
	unsigned tmpll_ctrl;
	unsigned tmpll_csw;
	unsigned tmpll_div;
	unsigned tmpll_psd;
	unsigned fabpll_prms;
	unsigned fabpll_ctrl;
	unsigned fabpll_csw;
	unsigned fabpll_div;
	unsigned fabpll_psd;
	unsigned nrcpinput_csw;
	unsigned nrcpinput_div;
	unsigned per_csw;
	unsigned per_div;
	unsigned emmc_csw;
	unsigned emmc_div;
	unsigned debug_csw;
	unsigned stop_csw;
} __attribute__ ((packed)) parameters_clocks_t;
#else  /* CONFIG_AXXIA_ARM */
typedef struct {
#ifdef CONFIG_AXXIA_25xx
	unsigned syspll_prms;
	unsigned syspll_ctrl;
	unsigned syspll_mcgc;
	unsigned syspll_mcgc1;
	unsigned syspll_psd;
	unsigned ppcpll_prms;
	unsigned ppcpll_ctrl;
	unsigned ppcpll_mcgc;
	unsigned ppcpll_mcgc1;
	unsigned ppcpll_psd;
	unsigned smpll_prms;
	unsigned smpll_ctrl;
	unsigned smpll_mcgc;
	unsigned smpll_mcgc1;
	unsigned smpll_psd;
	unsigned tmpll_prms;
	unsigned tmpll_ctrl;
	unsigned tmpll_mcgc;
	unsigned tmpll_mcgc1;
	unsigned tmpll_psd;
	unsigned per_mcgc;
	unsigned per_mcgc1;
#else
	unsigned sys_control;
	unsigned sys_lftune_upper;
	unsigned sys_lftune_lower;
	unsigned sys_fftune;
	unsigned sys_locktune;
	unsigned ppc_control;
	unsigned ppc_lftune_upper;
	unsigned ppc_lftune_lower;
	unsigned ppc_fftune;
	unsigned ppc_locktune;
	unsigned ddr0_control;
	unsigned ddr1_control;
	unsigned ddr_lftune_upper;
	unsigned ddr_lftune_lower;
	unsigned ddr_fftune;
	unsigned ddr_locktune;
#endif
} __attribute__ ((packed)) parameters_clocks_t;

#endif	/* CONFIG_AXXIA_ARM */

typedef struct {
	unsigned version;
	unsigned control;
} __attribute__((packed)) parameters_pciesrio_t;

typedef unsigned ncp_uint32_t;
typedef void *   ncp_dev_hdl_t;
typedef unsigned ncp_region_id_t;

typedef struct {
	unsigned char sdram_rtt_nom[4];
	unsigned char sdram_rtt_wr[4];
	unsigned char sdram_data_drv_imp[4];
	unsigned phy_min_cal_delay;
	unsigned phy_adr_phase_select;
	unsigned phy_dp_io_vref_set;
	unsigned phy_adr_io_vref_set;
	unsigned phy_rdlvl_cmp_even;
	unsigned phy_rdlvl_cmp_odd;
	unsigned phy_write_align_finetune;
} __attribute__((packed)) per_mem_parms_t;

typedef struct {
	ncp_uint8_t                 version;
	ncp_bool_t                  auto_detect;
	ncp_uint8_t                 num_interfaces;
	ncp_uint8_t                 num_ranks_per_interface;
	ncp_sm_topology_t           topology;
	ncp_sm_sdram_density_t      sdram_device_density;
	ncp_sm_sdram_width_t        sdram_device_width;
	ncp_sm_primary_bus_width_t  primary_bus_width;
	ncp_uint8_t                 CAS_latency;
	ncp_uint8_t                 CAS_write_latency;
	ncp_bool_t                  enableECC;
	ncp_uint8_t                 min_phy_cal_delay;
	ncp_uint8_t                 min_ctrl_roundtrip_delay;
	ncp_bool_t                  single_bit_mpr;
	ncp_uint32_t                rdcal_cmp_even;
	ncp_uint32_t                rdcal_cmp_odd;
	ncp_bool_t                  enable_deskew;
	ncp_bool_t                  enable_rdlvl;
	ncp_bool_t                  enable_auto_cpc;

	ncp_uint8_t                 added_rank_switch_delay;
	ncp_bool_t                  high_temp_dram;

	ncp_uint32_t                sdram_rtt_nom;
	ncp_uint32_t                sdram_rtt_wr;
	ncp_uint32_t                sdram_data_drv_imp;
	ncp_uint32_t                phy_adr_imp;
	ncp_uint32_t                phy_dat_imp;
	ncp_uint32_t                phy_rcv_imp;

	ncp_uint8_t                 phy_rdlat;
	ncp_uint8_t                 address_mirroring;
	ncp_uint8_t                 fixed_read_lat;
	ncp_uint8_t                 bubble_clobber;
	ncp_uint8_t                 syscacheMode;
	ncp_bool_t                  syscacheDisable;

	/* new for 5500 */
	ncp_uint32_t                zqcs_interval;
	ncp_bool_t                  enable_runtime_updates;
	ncp_uint8_t                 dramPrechargePolicy;
	ncp_uint32_t                open_page_size;
	ncp_per_sysmem_parms_t      per_smem[2];

	ncp_uint32_t                flags;
	ncp_bool_t                  half_mem;
	ncp_uint16_t                cmemMR1[2];

	ncp_bool_t                 ddrRetentionEnable;
	ncp_bool_t                 ddrRecovery;

	ncp_uint16_t               ddrClockSpeedMHz;
	ncp_uint8_t                 num_bytelanes;
	ncp_int64_t                 totalSize;

	/* RDIMM support */
	ncp_uint32_t		rdimm_ctl_0_0;
	ncp_uint32_t		rdimm_ctl_0_1;
	ncp_uint32_t		rdimm_misc;

	/* ODT Rd/Wr map support */
	ncp_uint32_t		read_ODT_ctl;
	ncp_uint32_t		write_ODT_ctl;

	/* new for 5600 */
	ncp_dram_class_t		dram_class;
	ncp_uint32_t		additive_latency;
	ncp_uint8_t			binned_CAS_latency; 	/* from part definition like CL-nRCD-nRP */
	ncp_uint32_t		tck_ps;  		/* period or rate at which part runs in pico-sec */
	ncp_uint8_t			refresh_mode;		/* 1 means 1x, 2 means 2x, 4 means 4x */
	ncp_uint8_t                 address_inversion;	/* applies only to ddr4 */
	ncp_uint8_t                 bstlen;			/* encoded burst_length during init and calculations */
	ncp_uint8_t                 dm_masking;		/* support availability on external dram */
	ncp_uint32_t		rdimm_ctl_0_2;
	ncp_uint32_t		rdimm_ctl_0_3;
	ncp_uint32_t		rdimm_ctl_0_4;
	ncp_uint32_t		rdimm_ctl_1_0;
	ncp_uint32_t		rdimm_ctl_1_1;
	ncp_uint32_t		rdimm_ctl_1_2;
	ncp_uint32_t		rdimm_ctl_1_3;
	ncp_uint32_t		rdimm_ctl_1_4;
	ncp_bool_t			vref_en;
	ncp_uint32_t		vref_cs;
	ncp_uint32_t		vref_val; 		/* VREF value per DRAM per chip-select- same for now */
	ncp_uint16_t		wr_protect_en_mask;
	ncp_bool_t			rdlvl_en;	/* Data eye training */
	ncp_bool_t			dbi_en;		/* data-bus inversion for rd and wr enable */
	ncp_bool_t			rdlvl_gate_en;	/* Gate training */
	ncp_uint32_t		rdlvl_interval;	/* Max long count sequences between data eye training */
	ncp_uint32_t		rdlvl_gate_interval;	/* Max long count sequences between gate training */
	ncp_uint8_t			preamble_support;/* 0-3 */
	ncp_uint8_t			crc_mode;/* Bit(0): 1 to enable crc gen/checking, Bit(1): 1: performed in MC 0: in PHY */
	ncp_uint32_t		dq_map_0[5]; /* Bit Map is 144 bits, so only 16-bits of index 4 are valid */
	ncp_uint32_t		dq_map_1[5]; /* Bit Map is 144 bits, so only 16-bits of index 4 are valid */
	ncp_uint8_t			dq_map_odd_rank_swap_0; /* 4 bits representing chip-selects */
	ncp_uint8_t			dq_map_odd_rank_swap_1; /* 4 bits representing chip-selects */
} __attribute__((packed)) parameters_mem_t;

typedef parameters_mem_t ncp_sm_parms_t;

#ifdef CONFIG_AXXIA_ARM
typedef struct {
	unsigned magic;
	unsigned size;
	unsigned checksum;
	unsigned version;
	unsigned chipType;
	unsigned globalOffset;
	unsigned globalSize;
	unsigned pciesrioOffset;
	unsigned pciesrioSize;
	unsigned voltageOffset;
	unsigned voltageSize;
	unsigned clocksOffset;
	unsigned clocksSize;
	unsigned systemMemoryOffset;
	unsigned systemMemorySize;
	unsigned classifierMemoryOffset;
	unsigned classifierMemorySize;
	unsigned systemMemoryRetentionOffset;
	unsigned systemMemoryRetentionSize;
} __attribute__((packed)) parameters_header_t;
#else  /* CONFIG_AXXIA_ARM */
typedef struct {
	unsigned sysmemSize;
	unsigned sysmemOffset;
	unsigned clocksSize;
	unsigned clocksOffset;
	unsigned voltageSize;
	unsigned voltageOffset;
	unsigned pciesrioSize;
	unsigned pciesrioOffset;
	unsigned globalSize;
	unsigned globalOffset;
	unsigned version;
	unsigned checksum;
	unsigned size;
	unsigned magic;
} __attribute__((packed)) parameters_header_t;
#endif	/* CONFIG_AXXIA_ARM */

typedef struct {
	parameters_header_t *header;
	parameters_global_t *global;
	parameters_voltage_t *voltage;
	parameters_clocks_t *clocks;
	parameters_pciesrio_t *pciesrio;
	parameters_mem_t *sysmem;
	parameters_mem_t *cmem;
} parameters_t;

extern parameters_header_t *header;
extern parameters_global_t *global;
extern parameters_pciesrio_t *pciesrio;
extern parameters_voltage_t *voltage;
extern parameters_clocks_t *clocks;
extern parameters_mem_t *sysmem;
extern parameters_mem_t *cmem;
#ifdef CONFIG_AXXIA_ARM
extern void *retention;
#endif

int read_parameters(void);
int write_parameters(void);

#ifndef CONFIG_SPL_BUILD
#define CONFIG_CMD_LSI_PARAMETERS
#endif

#endif	/* __ASSEMBLY__ */

/*
  ==============================================================================
  ==============================================================================
  Networking
  ==============================================================================
  ==============================================================================
*/

#ifndef CONFIG_SPL_BUILD

#if defined(CONFIG_AXXIA_FEMAC) || defined(CONFIG_AXXIA_EIOA) || defined(CONFIG_AXXIA_NEMAC)
#define CONFIG_AXXIA_NET
#define CONFIG_AXXIA_MDIO
#define CONFIG_CMD_NET
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_PING
#define CONFIG_CMD_MII
#define CONFIG_PHYLIB
#define CONFIG_MII
#define CONFIG_PHY_BROADCOM
#define CONFIG_PHY_DAVICOM
#define CONFIG_PHY_MICREL
#define CONFIG_PHY_VITESSE
#endif

#ifndef MDIO_CLK_OFFSET_DEFAULT
#ifdef CONFIG_AXXIA_EMU
/*#define MDIO_CLK_OFFSET_DEFAULT 0x10*/
#define MDIO_CLK_OFFSET_DEFAULT 0x5
#else
#define MDIO_CLK_OFFSET_DEFAULT 0x1c
#endif
#endif

#ifndef MDIO_CLK_PERIOD_DEFAULT
#ifdef CONFIG_AXXIA_EMU
/*#define MDIO_CLK_PERIOD_DEFAULT 0x2c*/
#define MDIO_CLK_PERIOD_DEFAULT 0xc
#else
#define MDIO_CLK_PERIOD_DEFAULT 0xf0
#endif
#endif

#endif	/* CONFIG_SPL_BUILD */

/*
  ==============================================================================
  ==============================================================================
  SSP Access
  ==============================================================================
  ==============================================================================
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

#define SSP_MAXIMUM_CLOCK 25000000

#ifndef __ASSEMBLY__
int ssp_read(void *, unsigned, unsigned);
int ssp_set_speed(unsigned *);
int ssp_init(int);
#endif

/*
  ==============================================================================
  ==============================================================================
  Clocks
  ==============================================================================
  ==============================================================================
*/

#ifndef __ASSEMBLY__

#define CLK_REF0 125000000

typedef enum {
	clock_system, clock_core, clock_memory, clock_peripheral,
	clock_fab, clock_treemem, clock_emmc
} acp_clock_t;

int acp_clock_get(acp_clock_t, ncp_uint32_t *);

unsigned int spi_get_per_clk(void);

#endif /* __ASSEMBLY__ */

/*
  ==============================================================================
  ==============================================================================
  System Memory
  ==============================================================================
  ==============================================================================
*/

#ifndef __ASSEMBLY__
int sysmem_reset(void);
unsigned long long sysmem_size(void);
#endif

/*
  ==============================================================================
  ==============================================================================
  Special Test
  ==============================================================================
  ==============================================================================
*/

/**********************************************************************
 * CONFIG_HYBRID_MBIST
 *
 * In order to use the MBIST controller to test a specific CPU linear range
 * of memory, software must understand the address munging algorithm and convert
 * the CPU linear range into multiple DDR physical sub-ranges. And, even after
 * doing this, due to the complicated nature of the munging algorithm and
 * limitations of the MBIST controller hardware, there will be some sub
 * ranges that cannot be tested using the MBIST hardware and therefore would
 * need to be tested via a software based memory test. Hence, we have this
 * hybrid approach for range based memory testing. This approach uses
 * the MBIST hardware in combination with software testing
 * of memory areas that cannot be covered by the MBIST controller. With
 * the hybrid approach, the user can only protect 768M or less of sysmem
 * by specifying the memory ranges on which they want the hybrid tests run.
 * It has been observed that hybrid approach versus s/w based memory testing
 * on the same range is 10-12 times faster.
 * If the user defines CONFIG_HYBRID_MBIST, then the ranges specified in
 * parameter file for memory range testing, will use the hybrid approach and
 * if CONFIG_HYBRID_MBIST is not defined, then s/w based spl_mtest will be
 * used for memory range testing. The user can specific which kind of spl_mtest
 * needs to be run by setting bits in Global Flags
 */
#define CONFIG_HYBRID_MBIST

/* Please note that CONFIG_SPL_MTEST just tests 0-1GB of sysmem */
/*#define CONFIG_SPL_MTEST*/
/*#define SM_PLL_533_MHZ*/
/*#define RUN_UNCACHED*/
/*#define RUN_NONSECURE*/
/*#define SINGLE_SMEM_MODE*/
/*#define DISPLAY_PARAMETERS*/

#define CONFIG_LSI
#define UBOOT

/*
  ==============================================================================
  ==============================================================================
  Version
  ==============================================================================
  ==============================================================================
*/

#ifndef __ASSEMBLY__
const char *get_lsi_version(void);
#endif /* __ASSEMBLY__ */

/*
  ==============================================================================
  ==============================================================================
  Nuevo Conf Ring Access (see board/lsi/common/ncr.c for the implementation)
  ==============================================================================
  ==============================================================================
*/

#ifndef __ASSEMBLY__
#define NCP_REGION_ID( node, target ) \
( ncp_uint32_t ) ( ( ( ( node ) & 0xffff ) << 16 ) | ( ( target ) & 0xffff ) )
#define NCP_NODE_ID( region ) ( ( ( region ) >> 16 ) & 0xffff )
#define NCP_TARGET_ID( region ) ( ( region ) & 0xffff )
int ncr_read(ncp_uint32_t, ncp_uint32_t, ncp_uint32_t, int, void *);
int ncr_read8( ncp_uint32_t, ncp_uint32_t, unsigned char * );
int ncr_read16( ncp_uint32_t, ncp_uint32_t, unsigned short * );
int ncr_read32( ncp_uint32_t, ncp_uint32_t, ncp_uint32_t * );
int ncr_write(ncp_uint32_t, ncp_uint32_t, ncp_uint32_t, int, void *);
int ncr_write8( ncp_uint32_t, ncp_uint32_t, unsigned char );
int ncr_write16( ncp_uint32_t, ncp_uint32_t, unsigned short );
int ncr_write32( ncp_uint32_t, ncp_uint32_t, ncp_uint32_t );
int ncr_modify32( ncp_uint32_t, ncp_uint32_t, ncp_uint32_t, ncp_uint32_t );
int ncr_and( ncp_uint32_t, ncp_uint32_t, ncp_uint32_t );
int ncr_or( ncp_uint32_t, ncp_uint32_t, ncp_uint32_t );
int ncr_poll( ncp_uint32_t, ncp_uint32_t, ncp_uint32_t,
              ncp_uint32_t, ncp_uint32_t, ncp_uint32_t );
void ncr_tracer_enable( void );
void ncr_tracer_disable( void );
int ncr_tracer_is_enabled( void );
void ncr_enable( void );
void ncr_disable( void );
#endif

/*
  ==============================================================================
  ==============================================================================
  Errata
  ==============================================================================
  ==============================================================================
*/

#ifndef __ASSEMBLY__
int setup_security(void);
#endif

#endif /* __AXXIA_H */
