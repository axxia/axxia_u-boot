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
#if defined ( CONFIG_AXXIA_25xx ) || defined ( CONFIG_AXXIA_55XX )
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
#elif defined(CONFIG_AXXIA_344X) || defined(CONFIG_AXXIA_342X)
#define INT_STATUS_OFFSET 0x16c
#define ECC_ERROR_MASK 0x78
#elif defined(CONFIG_AXXIA_25xx)
#define INT_STATUS_OFFSET 0x410
#define ECC_ERROR_MASK 0x78
#elif defined(CONFIG_AXXIA_55XX)
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


#ifdef CONFIG_AXXIA_25xx
#define MEMORY_BARRIER mb();
#else
/* #define MEMORY_BARRIER __asm__ __volatile__ ("" : : : "memory");*/
#define MEMORY_BARRIER dmb();
#endif

#define SMAV( regName, regField, newValue ) \
do { \
regName *tmpMask = (regName *)&mask;\
regName *tmpValue = (regName *)&value;\
tmpMask->regField = -1;\
tmpValue->regField = newValue;\
MEMORY_BARRIER \
} while( 0 );

#define SV( regName, regField, newValue ) \
do { \
regName *tmpValue = (regName *)&value;\
tmpValue->regField = newValue;\
MEMORY_BARRIER \
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

	for (offset = 0x3d8;offset <= 0xbd8;offset += 0x400) {
		ncr_read32(region, offset, &value);
		printf("0.%x.1.%010x: %08x\n", node[id], offset, value);
	}

	for (offset = 0x803c;offset <= 0x847c;offset += 0x40) {
		ncr_read32(region, offset, &value);
		printf("0.%x.1.%010x: %08x\n", node[id], offset, value);
	}

	offset = 0x8000 + ((rank >> 1) * 0x800);

	for (i = 0;i < 9;++i) {
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

	for (i = 0;i < 9;++i) {
		ncr_read32(region, offset, &value);
		printf("0.%x.1.%010x: %08x\n", node[id], offset, value);
		offset += 0x40;
		ncr_read32(region, offset, &value);
		printf("0.%x.1.%010x: %08x\n", node[id], offset, value);
		offset += 0x40;
	}

	for (tmp = 0;tmp < 1;++tmp) {
		offset = 0x10000 + (tmp * 0x800);

		for (i = 0;i < 9;++i) {
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

	for (tmp = 0;tmp <= 1;++tmp) {
		offset = 0x18000 + (tmp * 0x800);

		for (i = 0;i < 9;++i) {
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

	for (i = 0x103a0;i <= 0x103bc;++i) {
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
#ifndef CONFIG_AXXIA_55XX
	unsigned num_sc_nodes;
#endif
	unsigned value;
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

#ifdef CONFIG_MEMORY_RETENTION
    extern void *retention;
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
	for (count = i2c_chip;count <= i2c_chip_limit;count++) {
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
				printf("SPD detected RDIMM which we don't support\n");
				return 1;
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
			sysmem->address_mirroring = spd_address_mirroring;
		}
		printf("Values read from SPD:\n spd_num_ranks_per_interface = 0x%x\n spd_topology = 0x%x\n spd_device_width = 0x%x\n spd_device_density = 0x%x\n spd_high_temp_dram = 0x%x\n spd_address_mirroring = 0x%x\n", spd_num_ranks_per_interface, spd_topology, spd_device_width, spd_device_density, spd_high_temp_dram, spd_address_mirroring);
	}
#endif

/* #define DISPLAY_PARAMETERS */
#ifdef DISPLAY_PARAMETERS
    {
        unsigned long *p;
        int i;
	printf("-- -- Sysmem Parameters \n");

        printf("version=0x%08x\n", sysmem->version);
        printf("ddrClockSpeedMHz=0x%08x\n", sysmem->ddrClockSpeedMHz);
        printf("auto_detect=0x%08x\n", sysmem->auto_detect);
        printf("num_interfaces=0x%08x\n", sysmem->num_interfaces);
        printf("num_ranks_per_interface=0x%08x\n", sysmem->num_ranks_per_interface);
        printf("primary_bus_width=0x%08x\n", sysmem->primary_bus_width);
        printf("topology=0x%08x\n", sysmem->topology);
        printf("min_ctrl_roundtrip_delay=0x%08x\n", sysmem->min_ctrl_roundtrip_delay);
	printf("phy_rdlat=0x%08x\n", sysmem->phy_rdlat);
        printf("added_rank_switch_delay=0x%08x\n", sysmem->added_rank_switch_delay);
        printf("zqcs_interval=0x%08x\n", sysmem->zqcs_interval);
        printf("enableECC=0x%08x\n", sysmem->enableECC);
        printf("enable_runtime_updates=0x%08x\n", sysmem->enable_runtime_updates);
        printf("dramPrechargePolicy=0x%08x\n", sysmem->dramPrechargePolicy);
        printf("open_page_size=0x%08x\n", sysmem->open_page_size);
        printf("syscacheControl=0x%08x\n", sysmem->syscacheControl);
        printf("sdram_device_density=0x%08x\n", sysmem->sdram_device_density);
        printf("sdram_device_width=0x%08x\n", sysmem->sdram_device_width);
        printf("CAS_latency=0x%08x\n", sysmem->CAS_latency);
        printf("CAS_write_latency=0x%08x\n", sysmem->CAS_write_latency);
        printf("address_mirroring=0x%08x\n", sysmem->address_mirroring);
        printf("registeredDIMM=0x%08x\n", sysmem->registeredDIMM);
        printf("rdimm_ctl_0_0=0x%08x\n", sysmem->rdimm_ctl_0_0);
        printf("rdimm_ctl_0_1=0x%08x\n", sysmem->rdimm_ctl_0_1);
        printf("rdimm_msic=0x%08x\n", sysmem->rdimm_misc);
        printf("write_ODT_ctl=0x%08x\n", sysmem->write_ODT_ctl);
        printf("read_ODT_ctl=0x%08x\n", sysmem->read_ODT_ctl);
        printf("single_bit_mpr=0x%08x\n", sysmem->single_bit_mpr);
        printf("high_temp_dram=0x%08x\n", sysmem->high_temp_dram);

        for (i = 0;i < 2;i++) {

          p = (unsigned long *) sysmem->per_mem[i].sdram_rtt_nom;
          printf("RTTnom=0x%08x\n", *p++);
          printf("RTTwr=0x%08x\n", *p++);
          printf("drvimp=0x%08x\n", *p++);

          printf("phy_min_cal_delay=0x%08x\n", sysmem->per_mem[i].phy_min_cal_delay);
          printf("phy_adr_phase_select=0x%08x\n", sysmem->per_mem[i].phy_adr_phase_select);
          printf("phy_dp_io_vref_set=0x%08x\n", sysmem->per_mem[i].phy_dp_io_vref_set);
          printf("phy_adr_io_vref_set=0x%08x\n", sysmem->per_mem[i].phy_adr_io_vref_set);
          printf("phy_rdlvl_cmp_even=0x%08x\n", sysmem->per_mem[i].phy_rdlvl_cmp_even);
          printf("phy_rdlvl_cmp_odd=0x%08x\n", sysmem->per_mem[i].phy_rdlvl_cmp_odd);
          printf("phy_write_align_finetune=0x%08x\n", sysmem->per_mem[i].phy_write_align_finetune);
        }
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
#if defined (ACP_X1V2) || defined (ACP_X2V1)
	sysmem->version = 3;
#else

    ncr_read32(NCP_REGION_ID(34,0xff), 0, (ncp_uint32_t *) &sysmem->version);
    sysmem->version &= 0xff;
    sysmem->version = 0x9;	/* Fix for unexpected pfuse value!!! */
#endif
#endif

	/*
	 * determine number of syscaches and half_mem setting
	 * based on chipType and num_interfaces
	 */
#ifndef CONFIG_AXXIA_55XX
	num_sc_nodes = sysmem->num_interfaces * 4;
#endif

#if defined (ACP_X1V1) || defined (CONFIG_AXXIA_344X)
	if (sysmem->num_interfaces == 1) {
		sysmem->half_mem = 1;
	}
#endif

#ifdef CONFIG_MEMORY_RETENTION
    printf("global->flags = %d\n", global->flags);

    if (global->flags & 0x00000020) {
        printf("DDR Retention enabled in U-Boot Parameter Flags\n");
        sysmem->ddrRetentionEnable = 1;
    }
    else
    {
        printf("DDR Retention disabled in U-Boot Parameter Flags\n");
        sysmem->ddrRetentionEnable = 0;
    }
#endif

#if 0
	delay_dump(__LINE__, sm_nodes[0]);
	if (sysmem->half_mem == 0) {
		delay_dump(__LINE__, sm_nodes[1]);
	}
#endif

#ifndef CONFIG_AXXIA_55XX
	/*
	  Put all system caches in "force_uncached" mode
	*/
	for (i = 0;i < num_sc_nodes;++i) {
		ncr_write32(NCP_REGION_ID(sc_nodes[i], 0), 0x100, 1);
	}
#endif

	/*
	 * sysmem init goes here!!
	 */
#ifdef CONFIG_MEMORY_RETENTION

   /*
    *  we use bit 0 of the persistent scratch register to
    *  inidicate ddrRetention recovery.
    */
    ncr_read32(NCP_REGION_ID(0x156, 0x00), 0x00dc, &value);
    sysmem->ddrRecovery = (value & 0x1) ;
    value &= 0xfffffffe;
    ncr_write32(NCP_REGION_ID(0x156, 0x00), 0x00dc, value);

    printf("ddrRetentionEnable = %lu\n", sysmem->ddrRetentionEnable);
    printf("ddrRecovery = %lu\n", sysmem->ddrRecovery);

    if (sysmem->ddrRetentionEnable && sysmem->ddrRecovery)
    {
        /*
         * if we are attempting DDR recovery first make sure that
         * we have a valid set of parameters
         */
        for (i = 0;i < sysmem->num_interfaces;i++) {
            ncp_uint32_t *tag = retention + (i * DDR_PHY_REGS_SIZE);

            printf("checking tag[%d] %p = %x\n", i, tag, *tag);
            if (*tag != DDR_PHY_REGS_TAG_PROM) {
                printf("DDR restore buffer invalid - disabling ddrRecovery\n");
                sysmem->ddrRecovery = 0;
            }
        }
    }

   if (sysmem->ddrRecovery == 0) {
        /* reset SDRAM */
        sysmem_reset();
    }
#endif


	for (i = 0;i < sysmem->num_interfaces;i++) {
#if defined ( CONFIG_AXXIA_25xx ) || defined ( CONFIG_AXXIA_55XX )
		ncr_sysmem_init_mode_enable();
		rc = ncp_sysmem_init_lsiphy(NULL, i, sysmem);
		ncr_sysmem_init_mode_disable();

		if (rc != 0) {
		  printf("*** Sysmem Init Failed ***\n");
#ifdef CONFIG_AXXIA_25xx
          /* ??? */
		  printf("0x18e.0.0xc: 0x%08x\n",
			 dcr_read(0x1703));
		  printf("0x18d.4.0x0: 0x%08x\n"
			 "0x18d.4.0x4: 0x%08x\n",
			 dcr_read(0xd70), dcr_read(0xd71));
#endif
		  acp_failure( __FILE__, __FUNCTION__, __LINE__ );
		}
#else
#if defined (CONFIG_AXXIA_344X) || defined (CONFIG_AXXIA_342X)
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

		sysmem->totalSize = sdram_capacity_bytes;
	}

	/* Just match the RTE trace... */
	NCR_TRACE("ncpRead    0.24.255.0x0000000004 1\n");

#ifndef CONFIG_AXXIA_55XX
#include "../axxia-ppc/sysmem_asic_ppc.c"
#else
    /* TEMP : declarations */
ncp_st_t ncp_elm_init( ncp_dev_hdl_t dev, ncp_sm_parms_t *parms);
ncp_st_t ncp_elm_sysmem_fill( ncp_dev_hdl_t dev, ncp_sm_parms_t *parms);

    ncp_elm_init(NULL, sysmem);
    if ((sysmem->enableECC) && (sysmem->ddrRecovery == 0)) {
        ncp_elm_sysmem_fill(NULL, sysmem);
    }

#endif


	return 0;
}
