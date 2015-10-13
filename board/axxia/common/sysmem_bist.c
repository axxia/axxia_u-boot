/*
 *  Copyright (C) 2009 LSI Corporation
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
#include <asm/io.h>

#if defined (CONFIG_AXXIA_344X) || defined (CONFIG_AXXIA_342X)
#include "regs/ncp_denali_regs.h"
#include "regs/ncp_denali_reg_defines.h"
#include "regs/ncp_phy_regs.h"
#include "regs/ncp_phy_reg_defines.h"
#endif

#if defined (CONFIG_AXXIA_25xx) || defined(CONFIG_AXXIA_55XX)
#include "regs/ncp_denali_regs_acp2500.h"
#include "regs/ncp_denali_reg_defines_acp2500.h"
#include "regs/ncp_phy_regs_acp2500.h"
#include "regs/ncp_phy_reg_defines_acp2500.h"
#endif

/*
  ===============================================================================
  ===============================================================================
  Local
  ===============================================================================
  ===============================================================================
*/

#if defined(ACP_X1V1)
#define INT_STATUS_OFFSET 0x16c
#define BIST_COMPLETION 0x200
#define ECC_ERROR_MASK 0x3c
#elif defined(CONFIG_AXXIA_344X) || defined(CONFIG_AXXIA_342X)
#define INT_STATUS_OFFSET 0x16c
#define BIST_COMPLETION 0x400
#define ECC_ERROR_MASK 0x78
#elif defined(CONFIG_AXXIA_25xx)
#define INT_STATUS_OFFSET 0x410
#define BIST_COMPLETION 0x800
#define ECC_ERROR_MASK 0x78
#elif defined(CONFIG_AXXIA_55XX)
#define INT_STATUS_OFFSET 0x410
#define BIST_COMPLETION 0x400
#define ECC_ERROR_MASK 0x78
#endif

#define BIST_STATUS_OFFSET 0x50

#if defined(CONFIG_AXXIA_25xx) || defined(CONFIG_AXXIA_55XX)
#define INT_STATUS_CLEAR_OFFSET 0x548
#else
#define INT_STATUS_CLEAR_OFFSET 0x164
#endif

/*
  ----------------------------------------------------------------------
  axxia_sysmem_bist_failure
*/

static void
axxia_sysmem_bist_failure(unsigned long region)
{
	int i;
	unsigned long value;
	unsigned long offsets[] = {
		0x248, 0x24c,
#if defined(CONFIG_AXXIA_25xx) || defined(CONFIG_AXXIA_55XX)
		0x418, 0x41c, 0x420, 0x424, 0x428, 0x42c, 0x430, 0x434,
		0x438, 0x43c, 0x440, 0x444, 0x448, 0x44c, 0x450, 0x454
#else
		0x2b0, 0x2b4, 0x2b8, 0x2bc, 0x2c0, 0x2c4, 0x2c8, 0x2cc
#endif
	};

	for (i = 0;i < (sizeof(offsets) / sizeof(unsigned long));++i) {
		ncr_read32(region, offsets[i], (ncp_uint32_t *)&value);
		printf("\t\tRegion:0x%08lx Offset:0x%04lx Value:0x%08lx\n",
		       region, offsets[i], value);
	}

	return;
}

/*
  ----------------------------------------------------------------------
  axxia_sysmem_asic_check_ecc
*/

static void
axxia_sysmem_asic_check_ecc(unsigned long region)
{
	unsigned long value;

#ifdef CONFIG_AXXIA_55XX
	ncr_read32(region, NCP_DENALI_CTL_421, (ncp_uint32_t *)&value);

	if (1 != ((ncp_denali_DENALI_CTL_421_t *)&value)->ecc_en) {
		if (NCP_NODE_ID(region) == 0x22) {
			/* SM0 */
			printf("ECC is not enabled for SM0 node 0x%03lx\n",
		       NCP_NODE_ID(region));
		} else if (NCP_NODE_ID(region) == 0xf) {
			/* SM1 */
			printf("ECC is not enabled for SM1 node 0x%03lx\n",
		       NCP_NODE_ID(region));
		}
		return;
	}
#else
	ncr_read32(region, NCP_DENALI_CTL_20, &value);

	if (3 != ((ncp_denali_DENALI_CTL_20_t *)&value)->ctrl_raw) {
		printf("ECC is not enabled for node 0x%03lx\n",
		       NCP_NODE_ID(region));
		return;
	}
#endif

	ncr_read32(region, INT_STATUS_OFFSET, (ncp_uint32_t *)&value);

	if (0 == (value & ECC_ERROR_MASK)) {
#ifdef CONFIG_AXXIA_55XX
		if (NCP_NODE_ID(region) == 0x22) {
			printf("No ECC Errors Detected on SM0 Node 0x%03lx.\n",
		       NCP_NODE_ID(region));
		} else if (NCP_NODE_ID(region) == 0xf) {
			printf("No ECC Errors Detected on SM1 Node 0x%03lx.\n",
		       NCP_NODE_ID(region));
		}
#else
			printf("No ECC Errors Detected on Node 0x%03lx.\n",
		       NCP_NODE_ID(region));
#endif
	} else {
		int i;
		unsigned long offsets[] = {
			0x0ac, 0x258, 0x260, 0x264, 0x288, 0x28c, 0x290, 0x294
		};

#ifdef CONFIG_AXXIA_55XX
		if (NCP_NODE_ID(region) == 0x22) {
			printf("ECC Errors Detected on SM0 Node 0x%03lx: 0x%02lx\n",
		       NCP_NODE_ID(region), (value & ECC_ERROR_MASK));
		} else if (NCP_NODE_ID(region) == 0xf) {
			printf("ECC Errors Detected on SM1 Node 0x%03lx: 0x%02lx\n",
		       NCP_NODE_ID(region), (value & ECC_ERROR_MASK));
		}
#else
		printf("ECC Errors Detected on Node 0x%03lx: 0x%02lx\n",
		       NCP_NODE_ID(region), (value & ECC_ERROR_MASK));
#endif

		for (i = 0;i < (sizeof(offsets) / sizeof(unsigned long));
		     ++ i) {
			ncr_read32(region, offsets[i], (ncp_uint32_t *)&value);
			printf("\tRegion:0x%08lx Offset:0x%04lx Value:0x%08lx\n",
			       region, offsets[i], value);
		}
	}

	return;
}

/*
  ----------------------------------------------------------------------
  axxia_sysmem_bist_start
*/

static void
axxia_sysmem_bist_start(unsigned long region, int bits, int test,
			unsigned long long address)
{
	/* Disable BIST_GO parameter */
	ncr_and(region, 0x8, 0xfffffffe);

	/* Unset the previous data and address test modes. */
	ncr_and(region, 0x4, 0xfefeffff);

	/* Program to test either address or data. */
	if (1 == test) {
		ncr_or(region, 0x4, 0x00010000);
	} else {
		ncr_or(region, 0x4, 0x01000000);
	}

	/* Program the start address. */
	ncr_write32(region, 0x250, /* bottom 32 bits */
		    (unsigned long)(address & 0xffffffff));
	ncr_write32(region, 0x254, /* top 4 bits */
		    ((unsigned long)((address & 0xffffffff00000000ULL) >> 32)) &
		    0xf);

	/* Program the data mask. */
#if defined(CONFIG_AXXIA_25xx) || defined(CONFIG_AXXIA_55XX)
	ncr_write32(region, 0x3f8, 0);
	ncr_write32(region, 0x3fc, 0);
	ncr_write32(region, 0x400, 0);
	ncr_write32(region, 0x404, 0);
#else
	ncr_write32(region, 0x280, 0);
	ncr_write32(region, 0x284, 0);
#endif

	/*
	  The end address is specified by the number
	  of address bits.
	*/
	if (1 == test) {
		/*
		  For address checking, the spec says
		  the register value should be value
		  calculated
		*/
		ncr_and(region, 0xa4, 0xc0ffffff);
		ncr_or(region, 0xa4, ((bits) << 24));
	} else {
		/*
		  For data checking we just use the
		  value calculated above for the
		  specified memory size. (i.e. 2GB ==
		  31 bits).
		*/
		ncr_and(region, 0xa4, 0xc0ffffff);
		ncr_or(region, 0xa4, ((bits) << 24));
	}

	/* Erase the interrupt status from the previous run. */
#if defined(CONFIG_AXXIA_25xx) || defined (CONFIG_AXXIA_55XX)
	ncr_or(region, INT_STATUS_CLEAR_OFFSET, 0x200);
#else
	ncr_or(region, INT_STATUS_CLEAR_OFFSET, 0x600);
#endif

	/* Start the test. */
	ncr_or(region, 0x8, 0x1);

	return;
}

/*
  ----------------------------------------------------------------------
  axxia_sysmem_bist
*/

int
axxia_sysmem_bist(unsigned long long address, unsigned long long length,
		  enum bist_type type)
{
	unsigned long bits;
	int test, test_val, test_end;
	unsigned long result;
	unsigned long interrupt_status;
	unsigned long long temp;

	/* Make sure the size is a power of 2. */
	if (0 == ((length != 0) && ((length & (~length + 1)) == length))) {
		printf("length, 0x%llx, is NOT a power of 2.\n", length);
		return -1;
	}

	/* What power of 2 is it? */
	bits = 0;
	temp = 1;

	while (temp < length) {
		++bits;
		temp <<= 1;
	}

	printf("Running the Built In Self Test on 2^%lu bytes at 0x%llx.\n",
	       bits, address);

	/* Check for ECC errors. */
	axxia_sysmem_asic_check_ecc(NCP_REGION_ID(0x022, 0));

	if (1 < sysmem->num_interfaces)
		axxia_sysmem_asic_check_ecc(NCP_REGION_ID(0x00f, 0));

	if (type == data) {
		test_val = 0;
		test_end = 0;
	} else if (type == addr) {
		test_val = 1;
		test_end = 1;
	} else {
		test_val = 1;
		test_end = 0;
	}

	for (test = test_val; test >= test_end; --test) {
		unsigned long smregion0 = NCP_REGION_ID(0x22, 0);
		unsigned long smregion1 = NCP_REGION_ID(0xf, 0);
		unsigned long delay_loops;

		if (1 == test) {
			printf("ADDRESS Check MBIST on all nodes...\n");
			delay_loops = 20000;
		} else {
			printf("DATA Check MBIST on all nodes...\n");
			delay_loops = 100000;
		}

		axxia_sysmem_bist_start(smregion0, bits, test, address);

		if (1 < sysmem->num_interfaces)
			axxia_sysmem_bist_start(smregion1, bits, test, address);

		/* Poll for completion and get the results. */
		if (0 != ncr_poll(smregion0, INT_STATUS_OFFSET,
				  BIST_COMPLETION, BIST_COMPLETION,
				  10000, delay_loops)) {
			printf("SM Node 0x%lx Didn't Complete.\n",
			       NCP_NODE_ID(smregion0));
		} else {
			ncr_read32(smregion0, INT_STATUS_OFFSET,
				   (ncp_uint32_t *)&interrupt_status);
			ncr_write32(smregion0,
				    INT_STATUS_CLEAR_OFFSET, interrupt_status);
			ncr_read32(smregion0, BIST_STATUS_OFFSET,
				   (ncp_uint32_t *)&result);

			if (result & (1 << test)) {
				printf("\tSM Node 0 PASSED\n");
			} else {
				printf("\tSM Node 0 FAILED\n");
				axxia_sysmem_bist_failure(smregion0);
			}
		}

		if (1 < sysmem->num_interfaces) {
			if (0 != ncr_poll(smregion1, INT_STATUS_OFFSET,
					  BIST_COMPLETION, BIST_COMPLETION,
					  10000, delay_loops)) {
				printf("SM Node 0x%lx Didn't Complete.\n",
				       NCP_NODE_ID(smregion1));
			} else {
				ncr_read32(smregion1, INT_STATUS_OFFSET,
					   (ncp_uint32_t *)&interrupt_status);
				ncr_write32(smregion1, INT_STATUS_CLEAR_OFFSET,
					    interrupt_status);
				ncr_read32(smregion1, BIST_STATUS_OFFSET,
					   (ncp_uint32_t *)&result);

				if(result & (1 << test)) {
					printf("\tSM Node 1 PASSED\n");
				} else {
					printf("\tSM Node 1 FAILED\n");
					axxia_sysmem_bist_failure(smregion1);
				}
			}
		}

		/*
		  Make sure to disable before letting the
		  system access system memory.  Disabling
		  BIST_GO param.
		*/
		ncr_and(smregion0, 0x8, 0xfffffffe);

		do {
			ncr_read32(smregion0, 0x8, (ncp_uint32_t *)&result);
		} while (0 != (result & 1));

		if (1 < sysmem->num_interfaces) {
			ncr_and(smregion1, 0x8, 0xfffffffe);

			do {
				ncr_read32(smregion1, 0x8,
					   (ncp_uint32_t *)&result);
			} while (0 != (result & 1));
		}
	}

	axxia_sysmem_asic_check_ecc(NCP_REGION_ID(0x022, 0));

	if (1 < sysmem->num_interfaces)
		axxia_sysmem_asic_check_ecc(NCP_REGION_ID(0x00f, 0));

	return 0;
}

void
axxia_mtest_check_ecc() {
	axxia_sysmem_asic_check_ecc(NCP_REGION_ID(0x022, 0));

	if (1 < sysmem->num_interfaces)
		axxia_sysmem_asic_check_ecc(NCP_REGION_ID(0x00f, 0));
}
