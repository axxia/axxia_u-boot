/*
 *  Copyright (C) 2010 LSI Corporation
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
#if defined(ACP_25xx) || defined(AXM_35xx)
#include "ncp_sysmem_lsiphy.h"
extern ncp_st_t ncp_sysmem_init_lsiphy(ncp_dev_hdl_t, ncp_uint32_t, ncp_sm_parms_t *);
extern ncp_st_t ncp_cm_dram_init(ncp_dev_hdl_t, ncp_uint32_t);
#else
typedef long long               ncp_int64_t;
typedef unsigned long long      ncp_uint64_t;
typedef unsigned long           ncp_uint32_t;
typedef unsigned short          ncp_uint16_t;
typedef unsigned char           ncp_uint8_t;
typedef unsigned char           ncp_bool_t;
typedef void *                  ncp_dev_hdl_t;
typedef unsigned long           ncp_st_t;
typedef unsigned long           ncp_region_id_t;
typedef parameters_sysmem_t     ncp_sm_parms_t;

#define TRUE   (1)
#define FALSE  (0)
#define NCP_RETURN_LABEL
#endif

#if defined(ACP_X1V1)
#define INT_STATUS_OFFSET 0x16c
#define ECC_ERROR_MASK 0x3c
#elif defined(ACP_X1V2) || defined(ACP_X2V1)
#define INT_STATUS_OFFSET 0x16c
#define ECC_ERROR_MASK 0x78
#elif defined(ACP_25xx)
#define INT_STATUS_OFFSET 0x410
#define ECC_ERROR_MASK 0x78
#elif defined(AXM_35xx)
#define INT_STATUS_OFFSET 0x568
#define ECC_ERROR_MASK 0x78
#endif

/*
  ==============================================================================
  ==============================================================================
  ==============================================================================
  Local Stuff
  ==============================================================================
  ==============================================================================
  ==============================================================================
*/

static unsigned long sc_nodes [ ] = {
	0x20, 0x1e, 0x21, 0x1d, 0x11, 0x12, 0x10, 0x13
};

static unsigned long sm_nodes [ ] = {
	0x22, 0x0f, 0x08, 0x09
};

static unsigned long rank_address_map [ 2 ] [ 2 ] = {
    { 0x300, 0x100 },
    { 0x400, 0x600 }
}; 

/*
 * tRFC values based on device density
 *
 *       density     tRFC             @800MHz    @667MHz  @533MHz 
 *         512Mb      90 ns/clk           72       60       48
 *           1GB     110 ns/clk           88       74       59
 *           2GB     160 ns/clk          128      107       86
 *           4GB     300 ns/clk          240      200      160
 *
 */
ncp_uint8_t tRFC_vals_533[5] = { 0, 0x30, 0x3b, 0x56, 0x8b } ;
ncp_uint8_t tRFC_vals_667[5] = { 0, 0x3c, 0x4a, 0x6b, 0xae } ;
ncp_uint8_t tRFC_vals_800[5] = { 0, 0x48, 0x58, 0x80, 0xd0 } ;



#define SMAV( regName, regField, newValue ) \
do { \
regName *tmpMask = (regName *)&mask; \
regName *tmpValue = (regName *)&value; \
tmpMask->regField = -1; \
tmpValue->regField = newValue; \
mb(); \
} while( 0 );

#define SV( regName, regField, newValue ) \
do { \
regName *tmpValue = (regName *)&value; \
tmpValue->regField = newValue; \
mb(); \
} while( 0 );


#ifdef SM_REG_DUMP

/*
  ------------------------------------------------------------------------------
  sm_reg_dump
*/

void
sm_reg_dump(int id, int rank, char *file, unsigned long line)
{
	unsigned region;
	unsigned offset;
	unsigned value;
	int tmp;
	int i;
	int j;
	int node[] = {0x22, 0x0f};

	printf("SM Register (node=0x%x rank=%d) Dump from %s, line %d\n",
	       node[id], rank, file, line);
	region = NCP_REGION_ID(node[id], 1);

	for (offset = 0x3d8; offset <= 0xbd8; offset += 0x400) {
		ncr_read32(region, offset, &value);
		printf("0.%x.1.%010x: %08x\n", node[id], offset, value);
	}

	for (offset = 0x803c; offset <= 0x847c; offset += 0x40) {
		ncr_read32(region, offset, &value);
		printf("0.%x.1.%010x: %08x\n", node[id], offset, value);
	}

	offset = 0x8000 + ((rank >> 1) * 0x800);

	for (i = 0; i < 9; ++i) {
		unsigned buffer[4];

		ncr_read(region, 0, offset, 16, buffer);
		printf("0.%x.1.%010x: %08x %08x %08x %08x\n", node[id], offset,
		       buffer[0], buffer[1], buffer[2], buffer[3]);
		offset += 0x40;
		ncr_read(region, 0, offset, 16, buffer);
		printf("0.%x.1.%010x: %08x %08x %08x %08x\n", node[id], offset,
		       buffer[0], buffer[1], buffer[2], buffer[3]);
		offset += 0x40;
	}

	offset = 0x8010 + ((rank >> 1) * 0x800);

	for (i = 0; i < 9; ++i) {
		ncr_read32(region, offset, &value);
		printf("0.%x.1.%010x: %08x\n", node[id], offset, value);
		offset += 0x40;
		ncr_read32(region, offset, &value);
		printf("0.%x.1.%010x: %08x\n", node[id], offset, value);
		offset += 0x40;
	}

	for (tmp = 0; tmp < 1; ++tmp) {
		offset = 0x10000 + (tmp * 0x800);

		for (i = 0; i < 9; ++i) {
			unsigned buffer[8];

			ncr_read(region, 0, offset, 12, buffer);
			printf("0.%x.1.%010x: %08x %08x %08x\n",
			       node[id], offset,
			       buffer[0], buffer[1], buffer[2]);
			ncr_read(region, 0, (offset + 0x20), 32, buffer);
			printf("0.%x.1.%010x: %08x %08x %08x %08x\n",
			       node[id], (offset + 0x20),
			       buffer[0], buffer[1], buffer[2], buffer[3]);
			printf("0.%x.1.%010x: %08x %08x %08x %08x\n",
			       node[id], (offset + 0x30),
			       buffer[4], buffer[5], buffer[6], buffer[7]);
			offset += 0x80;
		}
	}

	for (tmp = 0; tmp <= 1; ++tmp) {
		offset = 0x18000 + (tmp * 0x800);

		for (i = 0; i < 9; ++i) {
			ncr_read32(region, offset, &value);
			printf("0.%x.1.%010x: %08x\n", node[id], offset, value);
			offset += 0x80;
		}
	}

	return;
}

/*
  check_for_failure
*/

int
check_for_failure(int display, char *file, unsigned long line)
{
	int rc = 0;
	int i;

	for (i = 0x103a0; i <= 0x103bc; ++i) {
		unsigned long value0;
		unsigned long value1;

		ncr_read32(NCP_REGION_ID(0x22, 1), i, &value0);
		ncr_read32(NCP_REGION_ID(0x0f, 1), i, &value1);

		if (0x20 <= value0) {
			printf("0x22.1.0x%08x = 0x%08x\n", i, value0);
			rc = 1;
		}

		if (0x20 <= value1) {
			printf("0x0f.1.0x%08x = 0x%08x\n", i, value1);
			rc = 1;
		}
	}

	if (0 != display || 0 != rc) {
		sm_reg_dump(0, 0, file, line);
		sm_reg_dump(0, 1, file, line);
		sm_reg_dump(1, 0, file, line);
		sm_reg_dump(1, 1, file, line);
	}

	return rc;
}

#endif /* SM_REG_DUMP */

/*
  ==============================================================================
  ==============================================================================
  ==============================================================================
  System Memory Initialization
  ==============================================================================
  ==============================================================================
  ==============================================================================
*/

void
sysmem_size_init(void)
{
	unsigned long long sdram_capacity_bytes;
	unsigned long sdram_device_width_bits; 
	unsigned long primary_bus_width_bits;

	sdram_capacity_bytes =
		(1 << sysmem->sdram_device_density) *
		((256 * 1024 * 1024) / 8);
	sdram_device_width_bits = 4 * (1 << sysmem->sdram_device_width);
	primary_bus_width_bits = 8 * (1 << sysmem->primary_bus_width);
	sdram_capacity_bytes =
		sysmem->num_interfaces * sysmem->num_ranks_per_interface *
		sdram_capacity_bytes *
		(primary_bus_width_bits / sdram_device_width_bits);
	sysmem_size = 0;

	while (0 < sdram_capacity_bytes) {
		++sysmem_size;
		sdram_capacity_bytes >>= 1;
	}

	--sysmem_size;

	return;
}


/* #define DISPLAY_PARAMETERS */
#ifdef DISPLAY_PARAMETERS
static void disp_ddr_parms(char * name, parameters_mem_t *parms)
{
#ifndef AXM_35xx
	printf("-- -- %s\n"
	       "0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx\n"
	       "0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx\n"
	       "0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx\n"
	       "0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx\n",
           name,
	       parms->version, parms->auto_detect,
	       parms->num_interfaces, parms->num_ranks_per_interface,
	       parms->topology, parms->sdram_device_density,
	       parms->sdram_device_width, parms->primary_bus_width,
	       parms->CAS_latency, parms->CAS_write_latency,
	       parms->enableECC, parms->enable_deskew,
	       parms->enable_rdlvl, parms->enable_auto_cpc,
	       parms->min_phy_cal_delay,
	       parms->min_ctrl_roundtrip_delay, parms->single_bit_mpr,
	       parms->rdcal_cmp_even, parms->rdcal_cmp_odd,
	       parms->phy_rdlat, parms->added_rank_switch_delay,
	       parms->high_temp_dram, parms->sdram_rtt_nom,
	       parms->sdram_rtt_wr, parms->sdram_data_drv_imp,
	       parms->phy_adr_imp, parms->phy_dat_imp,
	       parms->phy_rcv_imp, parms->sysCacheMode,
	       parms->syscacheDisable, parms->half_mem,
	       parms->address_mirroring);
#else
	printf("-- -- %s\n"
	       "0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx\n"
	       "0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx\n"
	       "0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx\n"
	       "0x%lx 0x%lx 0x%lx 0x%lx 0x%lx\n",
           name,
	       parms->version,
	       parms->ddrClockSpeedMHz,
	       parms->auto_detect,
	       parms->num_interfaces,
	       parms->num_ranks_per_interface,
	       parms->primary_bus_width,
	       parms->min_ctrl_roundtrip_delay,
	       parms->topology,
	       parms->phy_rdlat,
	       parms->added_rank_switch_delay,
	       parms->zqcs_interval,
	       parms->enableECC,
	       parms->enable_runtime_updates,
	       parms->dramPrechargePolicy,
	       parms->open_page_size,
	       parms->syscacheControl,
	       parms->sdram_device_density,
	       parms->sdram_device_width,
	       parms->CAS_latency,
	       parms->CAS_write_latency,
	       parms->address_mirroring,
	       parms->rdimm,
	       parms->rdimm_ctl_0_0,
	       parms->rdimm_ctl_0_1,
	       parms->rdimm_misc,
	       parms->write_ODT_ctl,
	       parms->read_ODT_ctl,
	       parms->single_bit_mpr,
	       parms->high_temp_dram);
	{
		int i;
		per_mem_parms_t *per_mem_parms;

		for (i = 0; i < 2; ++i) {
			per_mem_parms = &(parms->per_mem[i]);

			printf("-- -- per mem %d\n", i);
			printf("sdram_rtt_nom[] = {%d %d %d %d}\n"
			       "sdram_rtt_wr[] = {%d %d %d %d}\n"
			       "sdram_data_drv_imp[] = {%d %d %d %d}\n"
			       "0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx\n",
			       per_mem_parms->sdram_rtt_nom[3],
			       per_mem_parms->sdram_rtt_nom[2],
			       per_mem_parms->sdram_rtt_nom[1],
			       per_mem_parms->sdram_rtt_nom[0],
			       per_mem_parms->sdram_rtt_wr[3],
			       per_mem_parms->sdram_rtt_wr[2],
			       per_mem_parms->sdram_rtt_wr[1],
			       per_mem_parms->sdram_rtt_wr[0],
			       per_mem_parms->sdram_data_drv_imp[3],
			       per_mem_parms->sdram_data_drv_imp[2],
			       per_mem_parms->sdram_data_drv_imp[1],
			       per_mem_parms->sdram_data_drv_imp[0],
			       per_mem_parms->phy_min_cal_delay,
			       per_mem_parms->phy_adr_phase_select,
			       per_mem_parms->phy_dp_io_vref_set,
			       per_mem_parms->phy_adr_io_vref_set,
			       per_mem_parms->phy_rdlvl_cmp_even,
			       per_mem_parms->phy_rdlvl_cmp_odd,
			       per_mem_parms->phy_write_align_finetune);
		}
	}	       
#endif
}

#else
#define disp_ddr_parms(name, parms)
#endif

#ifdef AXM_35xx

static swap_impedance_parms(
	per_mem_parms_t *per_mem_parms)
{
	unsigned long *temp;

		temp = (unsigned long *)
			&(per_mem_parms->sdram_rtt_nom[0]);
		*temp = swab32(*temp);

		temp = (unsigned long *)
			&(per_mem_parms->sdram_rtt_wr[0]);
		*temp = swab32(*temp);

		temp = (unsigned long *)
			&(per_mem_parms->sdram_data_drv_imp[0]);
		*temp = swab32(*temp);
}
#else

#define swap_impedance_parms(s) 
#endif

int
sysmem_init(void)
{
	unsigned long num_sc_nodes;
	unsigned long controller;
	unsigned long phy;
	unsigned long mask;
	unsigned long value;
	unsigned long munge_reg;
	unsigned long num_bls;
	int i;
	int rc;
#ifdef CONFIG_SPD
	int count;
	unsigned char i2c_chip = 0x50;
	unsigned char i2c_chip_limit = 0x57;
	unsigned char spd_memType;
	unsigned char rDimm;
	unsigned char spd_num_ranks_per_interface;
	unsigned char spd_topology;
	unsigned char spd_device_density;
	unsigned char spd_device_width;
	unsigned char spd_high_temp_dram;
	unsigned char spd_address_mirroring;
	unsigned char buffer;
#endif

	/*
	  Flip the "per rank" parameters, since this is big endian...
	*/

	for (i = 0; i < sysmem->num_interfaces; ++i) {
		swap_impedance_parms(&(sysmem->per_mem[i])) ;
    }
	for (i = 0; i < cmem->num_interfaces; ++i) {
		swap_impedance_parms(&(cmem->per_mem[i])) ;
    }

	/*
	  ======================================================================
	  This should follow ncp_sm_init.nsh
	  ======================================================================
	*/

#ifdef CONFIG_SPD
#ifndef AXM_35xx
	/* Initialize I2C */
	i2c_init(CONFIG_SYS_I2C_SPEED, 0);
#else
	/* I2C 1 has the SPD EEPROM */
	i2c_set_bus_num(1);
#endif
	/* i2c chip 0x50-0x57 contain SPD info so check for the first one
	 * with valid info
	 */
	for (count = i2c_chip; count <= i2c_chip_limit; count++) {
		if (i2c_read(count, 0x2, 1, &buffer, 1) != -1) {
			spd_memType = buffer;
			if (spd_memType == 0xb) {
				/* DDR3 memory type detected */
				printf("SPD detected DDR3 memory type on i2c chip 0x%x\n", i2c_chip);
				break;
			}
		}
	}
	
	if (count > i2c_chip_limit) {
		printf("SPD not detected in i2c chip range 0x%x-0x%x\n", i2c_chip, i2c_chip_limit);
	} else{
		/* Check if RDIMM since we don't support it */
		if (i2c_read(count, 0x3, 1, &buffer, 1) != -1) {
			rDimm = buffer;
			if ((rDimm & 0xf) == 0x1) {
#ifndef AXM_35xx
				printf("SPD detected RDIMM which we don't support\n");
				return 1;
#else
				printf("SPD detected RDIMM \n");
#endif
			} 
		}

		/* Read the number of Ranks per Interface and device width*/
		if (i2c_read(count, 0x7, 1, &buffer, 1) != -1) {
			/* byte 7 bits 5:3 and add 1 to it*/
			spd_num_ranks_per_interface = ((buffer >> 3) & 0x7) + 0x1;
			sysmem->num_ranks_per_interface = spd_num_ranks_per_interface;
			if (spd_num_ranks_per_interface == 0x2) {
				/* dual Rank */
				spd_topology = 0x3;
				sysmem->topology = spd_topology;
			} else if (spd_num_ranks_per_interface == 0x1) {
				/* single Rank */
				spd_topology = 0x1;
				sysmem->topology = spd_topology;
			}
			/* byte 7 bits 2:0 */
			spd_device_width = (buffer & 0x7);
			sysmem->sdram_device_width = spd_device_width;
		}

		/* Read the Device Density */
		if (i2c_read(count, 0x4, 1, &buffer, 1) != -1) {
			/* byte 4 bits 3:0 */
			spd_device_density = (buffer & 0xf);
			sysmem->sdram_device_density = spd_device_density;
		}
		/* Read the Temperature */
		if (i2c_read(count, 0x1f, 1, &buffer, 1) != -1) {
			/* byte 31 bit 0 */
			spd_high_temp_dram = (buffer & 0x1);
			sysmem->high_temp_dram = spd_high_temp_dram;
		}
		/* Read the Address Mirroring */
		if (i2c_read(count, 0x3f, 1, &buffer, 1) != -1) {
			/* byte 63 bit 0 */
			spd_address_mirroring = (buffer & 0x1);
#ifdef AXM_35xx
			if ((rDimm & 0xf) == 0x1) {
				spd_address_mirroring = 0;
			}
#endif
			sysmem->address_mirroring = spd_address_mirroring;
		}
		printf("Values read from SPD:\n spd_num_ranks_per_interface = 0x%x\n spd_topology = 0x%x\n spd_device_width = 0x%x\n spd_device_density = 0x%x\n spd_high_temp_dram = 0x%x\n spd_address_mirroring = 0x%x\n", spd_num_ranks_per_interface, spd_topology, spd_device_width, spd_device_density, spd_high_temp_dram, spd_address_mirroring);
	}
#endif



	/*
	 * set the version.
	 * Note that this is the Denali controller version,
	 * which is 2 for v1 and 3 for v2+
	 */
#ifdef ACP_X1V1
	sysmem->version = 2;
#else
	sysmem->version = 3;
#endif

#ifdef AXM_35xx
	sysmem->version = 16;
#endif

	/*
	 * determine number of syscaches and half_mem setting 
	 * based on chipType and num_interfaces 
	 */
	num_sc_nodes = sysmem->num_interfaces * 4;

#if defined (ACP_X1V1) || defined (ACP_X1V2)
	if (sysmem->num_interfaces == 1) {
		sysmem->half_mem = 1;
	}
#endif

#if 0
	delay_dump(__LINE__, sm_nodes[0]);
	if (sysmem->half_mem == 0) {
		delay_dump(__LINE__, sm_nodes[1]);
	}
#endif

    disp_ddr_parms("SMEM Parameters", sysmem);

	if (sysmem->primary_bus_width == 2) {
		num_bls = 4;    
	} else {
		num_bls = 8;
	}


	/*
	  Put all system caches in "force_uncached" mode 
	*/

	for (i = 0; i < num_sc_nodes; ++i) {
		ncr_write32(NCP_REGION_ID(sc_nodes[i], 0), 0x100, 1);
	}

	/* 
	 * sysmem init goes here!! 
	 */
	for (i = 0; i < sysmem->num_interfaces; i++) {
#if defined(ACP_25xx) || defined(AXM_35xx)
		ncr_sysmem_init_mode_enable();
		rc = ncp_sysmem_init_lsiphy(NULL, i, sysmem);
		ncr_sysmem_init_mode_disable();

		if (rc != 0) {
		  printf("*** Sysmem Init Failed ***\n");
		  printf("0x18e.0.0xc: 0x%08x\n",
			 dcr_read(0x1703));
		  printf("0x18d.4.0x0: 0x%08x\n"
			 "0x18d.4.0x4: 0x%08x\n",
			 dcr_read(0xd70), dcr_read(0xd71));
		  acp_failure( __FILE__, __FUNCTION__, __LINE__ );
		}
#else
#if defined (ACP_X1V2) || defined (ACP_X2V1)
		ncp_sysmem_init_ibmphy(NULL, i, sysmem);
#endif
#endif
	}

	/*
	  Initialize sysmem_size
	*/

	sysmem_size_init();

	/* Just match the RTE trace... */
	NCR_TRACE("ncpRead    0.24.255.0x0000000004 1\n");

	/*
	  Enable system caches.
	*/

	/* loop through all syscaches */
#if !defined(ACP_DISABLE_L3)
	for (i = 0; i < num_sc_nodes; ++i) {
		/* enable the cache - unless the user asked not to */
#ifdef AXM_35xx
		if (0 == (sysmem->syscacheControl & 0xff00))
#else
		if (!sysmem->syscacheDisable)
#endif
			/*
			  TODO: This should only be done for
			  architectures before ACP2500V2!

			  See BZ38534.
			*/
			ncr_write32(NCP_REGION_ID(sc_nodes[i], 0), 0x100,
				    (0 == sysmem->enableECC) ? 0 : 8);
	}
#endif

	NCR_TRACE("# Initializing system cache\n");

	/*
	 * Determine appropriate value of the system cache address munge
	 * register based on the number of syscaches present.
	 * The field we program has a different value meaning for v1
	 * and v2:
	 *
	 *         v1                                v2
	 *   system_memory_size      value     memory_per_cache
	 *        64GB                 0            16GB
	 *        32GB                 1             8GB
	 *        16GB                 2             4GB
	 *         8GB                 3             2GB
	 *         4GB                 4             1GB
	 *         2GB                 5           512MB
	 *         1GB                 6           256MB
	 *       512MB                 7           128MB
	 *
         *         3500
         *   system_memory_size      value
         *        8GB                 0
         *        4GB                 1
         *        2GB                 2
         *        1GB                 3
         *        512MB               4
         *        256MB               5
         *        128MB               6
         *        64MB                7
         */
#if defined( ACP_X1V1 )
	switch( ( 1 << ( sysmem_size - 20 ) ) ) {
	case 512:
		value = 7;
		break;
	case 1024:
		value = 6;
		break;
	case 2048:
		value = 5;
		break;
	case 4096:
		value = 4;
		break;
	case 8192:
		value = 3;
		break;
	case 16384:
		value = 2;
		break;
	case 32768:
		value = 1;
		break;
	case 65536:
		value = 0;
		break;
	default:
		printf( "Error Calculating Munge Value.\n" );
		acp_failure( __FILE__, __FUNCTION__, __LINE__ );
		break;
	}
#elif defined(ACP_X1V2) || defined(ACP_X2V1) || defined(ACP_25xx) || defined(AXM_35xx)
	value = ( 1 << ( sysmem_size - 20 ) ) / num_sc_nodes;

	switch( value ) {
#if defined (AXM_35xx)
	case 64:
		value = 8;
		break;
#endif
	case 128:
		value = 7;
		break;
	case 256:
		value = 6;
		break;
	case 512:
		value = 5;
		break;
	case 1024:
		value = 4;
		break;
	case 2048:
		value = 3;
		break;
	case 4196:
		value = 2;
		break;
	case 8192:
		value = 1;
		break;
#if !defined(AXM_35xx)
	case 16384:
		value = 0;
		break;
#endif
	default:
		printf( "Error Calculating Munge Value.\n" );
		acp_failure( __FILE__, __FUNCTION__, __LINE__ );
		break;
	}
#else
#error "Unsupported System!"
#endif

#if defined(AXM_35xx)
        /* get appropriate value to program into munge reg for 3500
         * based on 3500 syscache table above
         */
        value = value-1;
#endif

	/* if syscacheMode == 1 set the munge reg 'field_order' to 2 */
#if defined(AXM_35xx)
	munge_reg = value | ((sysmem->syscacheControl & 0xff) << 4);
#else
	munge_reg = value | (sysmem->sysCacheMode << 4);
#endif

	/* Just match the RTE trace... */
	NCR_TRACE("ncpRead    0.24.255.0x0000000004 1\n");
	NCR_TRACE("ncpRead    0.32.0.0x0000000014 1\n");
	NCR_TRACE("ncpRead    0.32.0.0x0000000014 1\n");

	/* loop through all syscaches */
	for( i = 0; i < num_sc_nodes; ++ i ) {
		/* write 'magic value' to enable_init field */
		ncr_write32( NCP_REGION_ID(sc_nodes[i], 0), 0x18, 0xed );
		/* set init_cache_ram field */
		ncr_write32( NCP_REGION_ID(sc_nodes[i], 0), 0x18, 0x000200ed );

		/* wait for it to complete */
		if (0 != ncr_poll(NCP_REGION_ID(sc_nodes[i], 0), 0x20, 
				  0x4,        /* mask */
				  0,          /* value */
				  0,          /* delayTime */
				  1000))       /* delayLoops */
		{
			acp_failure( __FILE__, __FUNCTION__, __LINE__ );
		}

		/* set the munge register */
		ncr_write32( NCP_REGION_ID(sc_nodes[i], 0), 0x14, munge_reg );

		/*
		  BZ 33026
		  X1V2 & X2: WFQ Mechanism in SYSCACHE Needs New
		  Updated Weight Configuration
		*/
		ncr_write32(NCP_REGION_ID(sc_nodes[i], 0), 0x1c, 0x23630323);

#ifdef ACP_X1V1
		/*
		  BZ 29933
		  Change the high water mark (the fifo_high_wm field in
		  mem_inf_write_scr_cmd_fifo_wm) to 4 (default is 5).
		  Should be done for all system caches in V1.
		*/
		ncr_write32( NCP_REGION_ID( sc_nodes[i], 1 ), 0x254,
			     0x00040004 );
#endif
	}

	/* Clear System Memory. */
	fill_sysmem(0ULL, (1ULL << sysmem_size), num_sc_nodes);

	/* If ECC is enabled, clear the status bits. */
	if (0 != sysmem->enableECC) {
		/* clear ECC interrupt status bits */
		for( i = 0; i < sysmem->num_interfaces; ++ i ) {
			ncr_read32( NCP_REGION_ID( sm_nodes [ i ], 0 ),
				    INT_STATUS_OFFSET, & value );
			value &= ECC_ERROR_MASK;
#ifndef AXM_35xx
			ncr_write32( NCP_REGION_ID( sm_nodes [ i ], 0 ),
				     NCP_DENALI_CTL_89, value );
#else
			ncr_write32( NCP_REGION_ID( sm_nodes [ i ], 0 ),
				     NCP_DENALI_CTL_347, value );
#endif
		}
	}

	/* Disable some speculative reads. */
#if defined(ACP_X1V1) || defined(ACP_X1V2) || defined(ACP_X2V1)
	if (sysmem->half_mem)
		dcr_write( 0x3377c800, 0xf00 );
	else
		dcr_write( 0x33774800, 0xf00 );
#endif

	/* set up NHA */
#ifndef AXM_35xx
	if (sysmem->half_mem) {
		/* and all the other sysmem clients */
		mask = value = 0x10000000;
		ncr_modify32( NCP_REGION_ID(0x0b, 0x05), 0x4, mask, value );
		ncr_modify32( NCP_REGION_ID(0x0e, 0x05), 0x4, mask, value );
		ncr_modify32( NCP_REGION_ID(0x15, 0x00), 0x4, mask, value );
		ncr_modify32( NCP_REGION_ID(0x16, 0x05), 0x4, mask, value );
		ncr_modify32( NCP_REGION_ID(0x19, 0x05), 0x4, mask, value );
		ncr_modify32( NCP_REGION_ID(0x1c, 0x05), 0x4, mask, value );
		ncr_modify32( NCP_REGION_ID(0x17, 0x05), 0x4, mask, value );
		ncr_modify32( NCP_REGION_ID(0x1f, 0x05), 0x4, mask, value );
		ncr_modify32( NCP_REGION_ID(0x1a, 0x05), 0x4, mask, value );
		ncr_modify32( NCP_REGION_ID(0x1a, 0x23), 0x4, mask, value );
		ncr_modify32( NCP_REGION_ID(0x14, 0x05), 0x4, mask, value );
		ncr_modify32( NCP_REGION_ID(0x14, 0x0a), 0x4, mask, value );
		ncr_modify32( NCP_REGION_ID(0x0c, 0x05), 0x4, mask, value );
		ncr_modify32( NCP_REGION_ID(0x1b, 0x05), 0x4, mask, value );
		ncr_modify32( NCP_REGION_ID(0x00, 0x00), 0x4, mask, value );
	}
#endif

	/* WA for 34575 (applies to X1V2 and X2). */
#if defined(ACP_X1V2) || defined(ACP_X2V1)
	dcr_write(0, 0xf1f);
#endif

#if defined(ACP2)
	__asm__ __volatile__ ( "tlbwe %1,%0,0\n"			\
			       "tlbwe %2,%0,1\n"			\
			       "tlbwe %3,%0,2\n"			\
			       "isync\n" : :
			       "r" (0x80000000),
			       "r" (0x00000bf0),
			       "r" (0x00000000),
			       "r" (0x00030207));
#endif

	return 0;
}
