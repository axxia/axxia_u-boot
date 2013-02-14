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
#ifdef ACP_25xx
#include "ncp_sysmem_lsiphy.h"
extern ncp_st_t ncp_sysmem_init_lsiphy(ncp_dev_hdl_t, ncp_uint32_t, ncp_sm_parms_t *);
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
#elif defined(ACP_X1V2) || defined(ACP_X2V1) || defined(AXM_35xx)
#define INT_STATUS_OFFSET 0x16c
#define ECC_ERROR_MASK 0x78
#elif defined(ACP_25xx)
#define INT_STATUS_OFFSET 0x410
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
ncp_uint8_t tRFC_vals_533[5] = { 0, 0x30, 0x3b, 0x56, 0xa0 } ;
ncp_uint8_t tRFC_vals_667[5] = { 0, 0x3c, 0x4a, 0x6b, 0xc8 } ;
ncp_uint8_t tRFC_vals_800[5] = { 0, 0x48, 0x58, 0x80, 0xf0 } ;



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
	unsigned long region;
	unsigned long offset;
	unsigned long value;
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

		ncr_read(region, offset, 16, buffer);
		printf("0.%x.1.%010x: %08x %08x %08x %08x\n", node[id], offset,
		       buffer[0], buffer[1], buffer[2], buffer[3]);
		offset += 0x40;
		ncr_read(region, offset, 16, buffer);
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
			unsigned long buffer[8];

			ncr_read(region, offset, 12, buffer);
			printf("0.%x.1.%010x: %08x %08x %08x\n",
			       node[id], offset,
			       buffer[0], buffer[1], buffer[2]);
			ncr_read(region, (offset + 0x20), 32, buffer);
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
	unsigned char spd_num_ranks_per_interface;
	unsigned char spd_topology;
	unsigned char spd_device_density;
	unsigned char spd_device_width;
	unsigned char spd_high_temp_dram;
	unsigned char spd_address_mirroring;
	unsigned char buffer;
#endif


	/*
	  ======================================================================
	  This should follow ncp_sm_init.nsh
	  ======================================================================
	*/

#ifdef CONFIG_SPD
	/* Initialize I2C */
	i2c_init(CONFIG_SYS_I2C_SPEED, 0);

	/* i2c chip 0x50-0x57 contain SPD info so check for the first one
	 * with valid info
	 */
	for (count = i2c_chip; count <= i2c_chip_limit; count++) {
		if (i2c_read(0x50, 0x2, 1, &buffer, 1) != -1) {
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
		/* Read the number of Ranks per Interface and device width*/
		if (i2c_read(0x50, 0x7, 1, &buffer, 1) != -1) {
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
		if (i2c_read(0x50, 0x4, 1, &buffer, 1) != -1) {
			/* byte 4 bits 3:0 */
			spd_device_density = (buffer & 0xf);
			sysmem->sdram_device_density = spd_device_density;
		}
		/* Read the Temperature */
		if (i2c_read(0x50, 0x1f, 1, &buffer, 1) != -1) {
			/* byte 31 bit 0 */
			spd_high_temp_dram = (buffer & 0x1);
			sysmem->high_temp_dram = spd_high_temp_dram;
		}
		/* Read the Address Mirroring */
		if (i2c_read(0x50, 0x3f, 1, &buffer, 1) != -1) {
			/* byte 63 bit 0 */
			spd_address_mirroring = (buffer & 0x1);
			sysmem->address_mirroring = spd_address_mirroring;
		}
		printf("Values read from SPD:\n spd_num_ranks_per_interface = 0x%x\n spd_topology = 0x%x\n spd_device_width = 0x%x\n spd_device_density = 0x%x\n spd_high_temp_dram = 0x%x\n spd_address_mirroring = 0x%x\n", spd_num_ranks_per_interface, spd_topology, spd_device_width, spd_device_density, spd_high_temp_dram, spd_address_mirroring);
	}
#endif

#ifdef DISPLAY_PARAMETERS
	printf("-- -- Sysmem\n"
	       "0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx\n"
	       "0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx\n"
	       "0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx\n"
	       "0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx\n",
	       sysmem->version, sysmem->auto_detect,
	       sysmem->num_interfaces, sysmem->num_ranks_per_interface,
	       sysmem->topology, sysmem->sdram_device_density,
	       sysmem->sdram_device_width, sysmem->primary_bus_width,
	       sysmem->CAS_latency, sysmem->CAS_write_latency,
	       sysmem->enableECC, sysmem->enable_deskew,
	       sysmem->enable_rdlvl, sysmem->enable_auto_cpc,
	       sysmem->min_phy_cal_delay,
	       sysmem->min_ctrl_roundtrip_delay, sysmem->single_bit_mpr,
	       sysmem->rdcal_cmp_even, sysmem->rdcal_cmp_odd,
	       sysmem->phy_rdlat, sysmem->added_rank_switch_delay,
	       sysmem->high_temp_dram, sysmem->sdram_rtt_nom,
	       sysmem->sdram_rtt_wr, sysmem->sdram_data_drv_imp,
	       sysmem->phy_adr_imp, sysmem->phy_dat_imp,
	       sysmem->phy_rcv_imp, sysmem->sysCacheMode,
	       sysmem->syscacheDisable, sysmem->half_mem, sysmem->address_mirroring);
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

	/*
	 * determine number of syscaches and half_mem setting 
	 * based on chipType and num_interfaces 
	 */
	num_sc_nodes = sysmem->num_interfaces * 4;

#if defined (ACP_X1V1) || defined (ACP_X1V2) || defined(AXM_35xx)
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
#ifdef ACP_25xx
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
#if defined (ACP_X1V2) || defined (ACP_X2V1) || defined(AXM_35xx)
		ncp_sysmem_init_ibmphy(NULL, i, sysmem);
#endif
#endif
	}

	/*
	  Calculate the size of system memory.

	  This should match ncp_calc_mem_size().
	*/

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
	}

	/* Just match the RTE trace... */
	NCR_TRACE("ncpRead    0.24.255.0x0000000004 1\n");

	/*
	  Enable system caches.
	*/

	/* loop through all syscaches */
#if !defined(ACP_DISABLE_L3)
	for (i = 0; i < num_sc_nodes; ++i) {
		/* enable the cache - unless the user asked not to */
		if (!sysmem->syscacheDisable)
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
	case 16384:
		value = 0;
		break;
	default:
		printf( "Error Calculating Munge Value.\n" );
		acp_failure( __FILE__, __FUNCTION__, __LINE__ );
		break;
	}
#else
#error "Unsupported System!"
#endif

	/* if syscacheMode == 1 set the munge reg 'field_order' to 2 */
	munge_reg = value | (sysmem->sysCacheMode << 4);

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
			ncr_write32( NCP_REGION_ID( sm_nodes [ i ], 0 ),
				     NCP_DENALI_CTL_89, value );
		}
	}

	/* Disable some speculative reads. */
#if defined(ACP_X1V1) || defined(ACP_X1V2) || defined(ACP_X2V1) || defined(AXM_35xx)
	if (sysmem->half_mem)
		dcr_write( 0x3377c800, 0xf00 );
	else
		dcr_write( 0x33774800, 0xf00 );
#endif

	/* set up NHA */
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

	/* WA for 34575 (applies to X1V2 and X2). */
#if defined(ACP_X1V2) || defined(ACP_X2V1) || defined(AXM_35xx)
	dcr_write(0, 0xf1f);
#endif

	return 0;
}
