/*
 * Copyright (C) 2016 Intel Corporation
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
#include <watchdog.h>

#include "ncp_sysmem_ext.h"
#include "ncp_sysmem_lsiphy.h" /* for macros and stuff mainly */
#include "ncp_sysmem_synopphy.h"

/*
  ==============================================================================
  ==============================================================================
  Local
  ==============================================================================
  ==============================================================================
*/

#if defined(CONFIG_AXXIA_56XX_SIM) || defined(CONFIG_AXXIA_56XX)
static unsigned int nodes[] = {0x22, 0xf}; /* Two Controllers */
#elif defined(CONFIG_AXXIA_XLF_SIM) || defined(CONFIG_AXXIA_XLF)
static unsigned int nodes[] = {0x22, 0xf, 0x23, 0x24}; /* Four Controllers */
#endif

#ifndef CONFIG_AXXIA_EMU

#define number_of_nodes() (sizeof(nodes) / sizeof(unsigned int))

struct bist_test {
	unsigned int node;
	unsigned int region;
	unsigned int high;
	unsigned int low;
	unsigned int bits;
	enum bist_type type;
};

/*
  ------------------------------------------------------------------------------
  check_node_ecc
*/

static int
check_node_ecc(unsigned int node)
{
	ncp_uint32_t value;

	/* Is ECC enabled?  If not, return success. */
	ncr_read32(NCP_REGION_ID(node, 0), NCP_DENALI_CTL_101_5600, &value);

	if (0 == (value & 1))
		return 0;

	/* Otherwise, check the interrupt status. */
	ncr_read32(NCP_REGION_ID(node, 0), NCP_DENALI_CTL_366_5600, &value);

	if (0 == (value & 0x78))
		return 0;

	printf("ECC Errors (Node 0x%x)\n"
	       "\tCorrectible 0x%x\n"
	       "\tMultiple Correctible 0x%x\n"
	       "\tUncorrectible 0x%x\n"
	       "\tMultiple Uncorrectible 0x%x\n",
	       node,
	       ((value & 0x8) >> 3), ((value & 0x10) >> 4),
	       ((value & 0x20) >> 5), ((value & 0x40) >> 6));

	return -1;
}

/*
  ----------------------------------------------------------------------
  bist_result
*/

static void
bist_result(struct bist_test *test)
{
	int i;
	ncp_uint32_t value;
	unsigned int offsets[] = {
		NCP_DENALI_CTL_366_5600, /* Interrupt Status */
		NCP_DENALI_CTL_367_5600, /* Interrupt Status */
		NCP_DENALI_CTL_135_5600, /* Expected Data */
		NCP_DENALI_CTL_136_5600, /* Expected Data */
		NCP_DENALI_CTL_137_5600, /* Expected Data */
		NCP_DENALI_CTL_138_5600, /* Expected Data */
		NCP_DENALI_CTL_139_5600, /* Expected Data */
		NCP_DENALI_CTL_140_5600, /* Expected Data */
		NCP_DENALI_CTL_141_5600, /* Expected Data */
		NCP_DENALI_CTL_142_5600, /* Expected Data */
		NCP_DENALI_CTL_143_5600, /* Actual Data */
		NCP_DENALI_CTL_144_5600, /* Actual Data */
		NCP_DENALI_CTL_145_5600, /* Actual Data */
		NCP_DENALI_CTL_146_5600, /* Actual Data */
		NCP_DENALI_CTL_147_5600, /* Actual Data */
		NCP_DENALI_CTL_148_5600, /* Actual Data */
		NCP_DENALI_CTL_149_5600, /* Actual Data */
		NCP_DENALI_CTL_150_5600, /* Actual Data */
		NCP_DENALI_CTL_151_5600, /* Failure Address */
		NCP_DENALI_CTL_152_5600, /* Failure Address */
	};

	/* Get the result. */
	ncr_read32(test->region, NCP_DENALI_CTL_94_5600, &value);

	/* TODO: explain... */
	ncr_write32(test->region, NCP_DENALI_CTL_93_5600, 0x818);

	if (data == test->type && 1 == (value & 1)) {
		printf("\tDATA (node 0x%02x): Passed\n",
		       NCP_NODE_ID(test->region));

		return;
	} else if (addr == test->type && 0x2 == (value & 2)) {
		printf("\tADDRESS (node 0x%02x): Passed\n",
		       NCP_NODE_ID(test->region));

		return;
	}

	/* There was a failure, display "offsets". */
	for (i = 0; i < (sizeof(offsets) / sizeof(unsigned int)); ++i) {
		ncr_read32(test->region, offsets[i], &value);
		printf("\tRegion:0x%08x Offset:0x%04x Value:0x%08x\n",
		       test->region, offsets[i], value);
	}

	return;
}

/*
  ----------------------------------------------------------------------
  bist_start
*/

static void
bist_start(struct bist_test *test)
{
	unsigned int value;

	/* Acknowledge any existing interrupts. */
	ncr_write32(test->region, NCP_DENALI_CTL_368_5600, 0xffffffff);
	ncr_write32(test->region, NCP_DENALI_CTL_369_5600, 0x3);

	/* Set the address. */
	ncr_write32(test->region, NCP_DENALI_CTL_95_5600, test->low);
	ncr_write32(test->region, NCP_DENALI_CTL_96_5600, test->high);

	/* Set the length (power of 2). */
	value = (test->bits << 8);

	if (data == test->type)
		value |= (1 << 16);
	else
		value |= (1 << 24);

	ncr_write32(test->region, NCP_DENALI_CTL_94, value);

	/* Unmask all bits. */
	ncr_write32(test->region, NCP_DENALI_CTL_97_5600, 0);
	ncr_write32(test->region, NCP_DENALI_CTL_98_5600, 0);
	ncr_write32(test->region, NCP_DENALI_CTL_99_5600, 0);
	ncr_write32(test->region, NCP_DENALI_CTL_100_5600, 0);

	/* Start the test. */
	ncr_or(test->region, NCP_DENALI_CTL_93, (1 << 24));

	return;
}

#endif	/* CONFIG_AXXIA_EMU */

/*
  ==============================================================================
  ==============================================================================
  Public Interface
  ==============================================================================
  ==============================================================================
*/

#ifndef CONFIG_AXXIA_EMU

/*
  ----------------------------------------------------------------------
  axxia_sysmem_bist

  Note that the address given here is not the same as the core's
  physical address.  The address here is below the L3/system cache
  and on the other side of the munging that occurs there!

  Note also that, at least for now, the available memory is divided
  evenly across the nodes.  This is not technically required, but
  there is no way at present to handle any other case -- this code
  assumes memory is evenly divided among the nodes/controllers.

  To test all of memory, use an address of 0 and a lenght of sysmem_size().

  As for length, the following assumes that the nodes are contiguous.

  The data test does everything that the address test does and more.
  The tests must be run separately.
*/

int
axxia_sysmem_bist(unsigned long long address, unsigned long long length,
		  enum bist_type type)
{
	unsigned long bits;
	unsigned long long temp;
	unsigned int node;
	unsigned long long offset;
	unsigned long long size_per_node;
	struct bist_test bist_tests[number_of_nodes()];
	struct bist_test *test;

	memset(bist_tests, 0, sizeof(bist_tests));

	/*
	  Make sure that length is a power of 2 (required by the
	  hardware) and that the requested address and length are
	  within the range of available memory.
	*/

	if (0 == ((length != 0) && ((length & (~length + 1)) == length))) {
		printf("BIST: The given length, 0x%llx, is NOT a power of 2.\n",
		       length);

		return -1;
	}

	if (sysmem_size() < (address + length)) {
		printf("BIST: The requested test is out of range.\n");
		return -1;
	}

	/*
	  Initialize the bist_tests array...
	 */

	size_per_node = sysmem_size() / (unsigned long long)number_of_nodes();
	node = (unsigned int)(address / size_per_node);
	offset = address - (node * size_per_node);

	while (0 < length && node < number_of_nodes()) {
		unsigned long long length_to_test;

		length_to_test = (size_per_node - offset);

		if (length < length_to_test)
			length_to_test = length;

		if (0 == ((length_to_test != 0) &&
			  ((length_to_test &
			    (~length_to_test + 1)) == length_to_test))) {
			printf("BIST: Length in node not a power of 2!\n");

			return -1;
		}

		test = &bist_tests[node];

		/* Get the power of two... */
		bits = 0;
		temp = 1;

		while (temp < length_to_test) {
			++bits;
			temp <<= 1;
		}

		/* Fill in the test array. */
		test->node = node;
		test->region = NCP_REGION_ID(nodes[node], 0);
		test->high = offset & 0x3f00000000 >> 32;
		test->low = offset & 0xffffffff;
		test->bits = bits;
		test->type = type;

		/* Check for ECC errors. */
		check_node_ecc(NCP_NODE_ID(test->region));

		/* Start the test. */
		bist_start(test);

		/* Update the length etc. */
		length -= length_to_test;
		++node;
		offset = 0;
	}

	/*
	  Wait for completion and get the results.
	*/

	for (node = 0; node < number_of_nodes(); ++node, ++test) {
		int complete = 0;
		int remaining;

		test = &bist_tests[node];

		if (0 == test->region)
			continue;

		/*
		  Break polling into pieces to keep the watchdog up to date.
		*/

		if (addr == type)
			remaining = 80000;
		else
			remaining = 600000;

		remaining *= (size_per_node / (1024 * 1024 * 1024));

		while (0 < remaining) {
			WATCHDOG_RESET();

			if (0 == ncr_poll(test->region, NCP_DENALI_CTL_366_5600,
					  0x400, 0x400, 100, 10000)) {
				complete = 1;
				WATCHDOG_RESET();
				check_node_ecc(NCP_NODE_ID(test->region));
				bist_result(test);
				break;
			}

			remaining -= 10000;
		}

		WATCHDOG_RESET();

		if (0 == complete) {
			printf("SM Node 0x%x Didn't Complete.\n",
			       NCP_NODE_ID(test->region));

			return -1;
		}
	}

	return 0;
}

/*
  ------------------------------------------------------------------------------
  axxia_sysmem_check_ecc
*/

int
axxia_sysmem_check_ecc(void)
{
	int i;
	int rc;

	rc = 0;

	for (i = 0; i < number_of_nodes(); ++ i) {
		rc |= check_node_ecc(nodes[i]);
	}

	if (0 != rc)
		return -1;

	return 0;
}

#else  /* CONFIG_AXXIA_EMU */

/*
  ----------------------------------------------------------------------
  axxia_sysmem_bist
*/

int
axxia_sysmem_bist(unsigned long long address, unsigned long long length,
		  enum bist_type type)
{
	return 0;
}

/*
  ------------------------------------------------------------------------------
  axxia_sysmem_check_ecc
*/

int
axxia_sysmem_check_ecc(void)
{
	return 0;
}


#endif /* CONFIG_AXXIA_EMU */
