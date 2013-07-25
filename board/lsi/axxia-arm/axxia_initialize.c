/*
 *  Copyright (C) 2013 LSI Corporation
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>

/*
  ===============================================================================
  ===============================================================================
  Parameters
  ===============================================================================
  ===============================================================================
*/

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

typedef struct {
	unsigned long version;
	unsigned long flags;
} __attribute__((packed)) parameters_global_t;

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

typedef struct {
#ifdef ACP_25xx
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
	unsigned long sysCacheMode;
	unsigned long syscacheDisable;
	unsigned long half_mem;
	unsigned long address_mirroring;
} __attribute__((packed)) parameters_sysmem_t;

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

#define PARAMETERS_HEADER_ADDRESS \
  (LSM + (241 * 1024) - sizeof(parameters_header_t))

static parameters_header_t *header =
  (parameters_header_t *)PARAMETERS_HEADER_ADDRESS;

static parameters_global_t *global = (parameters_global_t *)1;
static parameters_pciesrio_t *pciesrio = (parameters_pciesrio_t *)1;
static parameters_voltage_t *voltage = (parameters_voltage_t *)1;
static parameters_clocks_t *clocks = (parameters_clocks_t *)1;
static parameters_sysmem_t *sysmem = (parameters_sysmem_t *)1;

#define PARAMETERS_OFFSET (240 * 1024)
#define PARAMETERS_ADDRESS (LSM + PARAMETERS_OFFSET)
#define PARAMETERS_SIZE (1024)
#define PARAMETERS_OFFSET_IN_FLASH 0x40000

/*
  ===============================================================================
  ===============================================================================
  Local
  ===============================================================================
  ===============================================================================
*/

#include "sysmem_emulation.c"

/*
  ==============================================================================
  ==============================================================================
  Public Interface
  ==============================================================================
  ==============================================================================
*/

/*
  ------------------------------------------------------------------------------
  axxia_initialize
*/

int
axxia_initialize(void)
{
	int returnCode = 0;
	int i;
	unsigned long *buffer;

	/*
	  Try LSM first, to allow for board repair when the serial
	  EEPROM contains a valid but incorrect (unusable) parameter
	  table.
	*/

	/* Verify that the paramater table is valid. */
	if( PARAMETERS_MAGIC != ntohl(header->magic )) {
		/* Initialize the SEEPROM (device 0, read only). */
		ssp_init(0, 1);

		/* Copy the last 1K of the SEEPROM to the last 1K of LCM. */
		returnCode = ssp_read((void *)PARAMETERS_ADDRESS,
				      PARAMETERS_OFFSET_IN_FLASH,
				      PARAMETERS_SIZE);

		if (0 != returnCode ||
		    PARAMETERS_MAGIC != ntohl(header->magic)) {
			/* No parameters available, fail. */
			returnCode = -1;
			goto acp_init_return;
		}
	}

	if (crc32(0, (void *)PARAMETERS_ADDRESS, (ntohl(header->size) - 12)) !=
	    ntohl(header->checksum) ) {
		printf( "Parameter table is corrupt. 0x%08x!=0x%08x\n",
			ntohl(header->checksum),
			crc32(0, (void *)PARAMETERS_ADDRESS,
			      (ntohl(header->size) - 12)));
		acp_failure( __FILE__, __FUNCTION__, __LINE__ );
	}

	buffer = (unsigned long *)PARAMETERS_ADDRESS;

	for (i = 0; i < (PARAMETERS_SIZE / 4); ++i) {
		*buffer = ntohl(*buffer);
		++buffer;
	}

#ifdef DISPLAY_PARAMETERS
	printf("-- -- Header\n"
	       "0x%08lx 0x%08lx 0x%08lx 0x%08lx\n"
	       "0x%08lx 0x%08lx\n"
	       "0x%08lx 0x%08lx\n"
	       "0x%08lx 0x%08lx\n"
	       "0x%08lx 0x%08lx\n"
	       "0x%08lx 0x%08lx\n",
	       header->magic,
	       header->size,
	       header->checksum,
	       header->version,
	       header->globalOffset, header->globalSize,
	       header->pciesrioOffset, header->pciesrioSize,
	       header->voltageOffset, header->voltageSize,
	       header->clocksOffset, header->clocksSize,
	       header->sysmemOffset, header->sysmemSize);
#endif

	global = (parameters_global_t *)
		(PARAMETERS_ADDRESS + header->globalOffset);
	pciesrio = (parameters_pciesrio_t *)
		(PARAMETERS_ADDRESS + header->pciesrioOffset);
	voltage = (parameters_voltage_t *)
		(PARAMETERS_ADDRESS + header->voltageOffset);
	clocks = (parameters_clocks_t *)
		(PARAMETERS_ADDRESS + header->clocksOffset);
	sysmem = (parameters_sysmem_t *)
		(PARAMETERS_ADDRESS + header->sysmemOffset);

#ifdef DISPLAY_PARAMETERS
	printf("version=%lu flags=0x%lx\n",
	       global->version, global->flags);
#endif

	/*
	  =======
	  Voltage
	  =======
	*/

#ifdef CONFIG_AXXIA_55XX
	if (0 == (global->flags & PARAMETERS_GLOBAL_IGNORE_VOLTAGE))
		if (0 != (returnCode = voltage_init()))
			goto acp_init_return;
#endif

	/*
	  =============
	  System Memory
	  =============
	*/

	if (0 == (global->flags & PARAMETERS_GLOBAL_IGNORE_SYSMEM))
		if (0 != (returnCode = sysmem_init()))
			goto acp_init_return;

 acp_init_return:

	return returnCode;
}
