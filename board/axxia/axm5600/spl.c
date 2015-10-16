/*
 *  board/lsi/axxia-arm/spl.c
 *
 *  Copyright (C) 2013 LSI (john.jacques@lsi.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307	 USA
 */

#include <config.h>
#include <common.h>
#include <version.h>
#include <serial.h>
#include <malloc.h>
#include <spl.h>
#include <spi.h>
#include <spi_flash.h>
#include <watchdog.h>
#include <asm/io.h>

DECLARE_GLOBAL_DATA_PTR;

/*
  ==============================================================================
  ==============================================================================
  Local Stuff
  ==============================================================================
  ==============================================================================
*/

/*#define COPY_MONITOR_TO_RAM*/

/*
  ------------------------------------------------------------------------------
  is_redundant_enabled
*/

static int
is_redundant_enabled(void)
{
#if !defined(CONFIG_REDUNDANT_UBOOT)
	return 0;
#endif

#if defined(CONFIG_REDUNDANT_UBOOT_AUTO)
	if (0 != (pfuse & (1 << 12)))
		return 1;

	return 0;
#else
	return 1;
#endif
}

/*
  ----------------------------------------------------------------------
  spl_mtest
*/

enum spl_mtest_type {
	spl_mtest_data = 0,
	spl_mtest_addr,
	spl_mtest_mtest,
	spl_mtest_all
};

int
spl_mtest(unsigned long *start, unsigned long *end, int total_iterations,
	  enum spl_mtest_type type)
{
#if 0
	vu_long	*addr;
	ulong	val;
	ulong	readback;
	ulong	errs = 0;
	int iterations = 0;
	vu_long	len;
	vu_long	offset;
	vu_long	test_offset;
	vu_long	pattern;
	vu_long	temp;
	vu_long	anti_pattern;
	vu_long	num_words;
	vu_long *dummy;
	int	j;

	static const ulong bitpattern[] = {
		0x00000001,	/* single bit */
		0x00000003,	/* two adjacent bits */
		0x00000007,	/* three adjacent bits */
		0x0000000F,	/* four adjacent bits */
		0x00000005,	/* two non-adjacent bits */
		0x00000015,	/* three non-adjacent bits */
		0x00000055,	/* four non-adjacent bits */
		0xaaaaaaaa,	/* alternating 1/0 */
	};

	pattern = 0;

	printf("Testing %08x ... %08x:\n", (uint)start, (uint)end);

	for (;;) {

		if (iterations >= total_iterations) {
			printf("Tested %d iteration(s) with %lu errors.\n",
			       iterations, errs);
			return errs != 0;
		}

		iterations++;
		printf("Iteration: %d\n", iterations);
		debug("\n");

		if ((type == spl_mtest_data) || (type == spl_mtest_all)) {
			/*
				* Data line test: write a pattern to the first
				* location, write the 1's complement to a 'parking'
			 * address (changes the state of the data bus so a
			 * floating bus doen't give a false OK), and then
									 * read the value back. Note that we read it back
									 * into a variable because the next time we read it,
									 * it might be right (been there, tough to explain to
				* the quality guys why it prints a failure when the
				* "is" and "should be" are obviously the same in the
				* error message).
									 *
									 * Rather than exhaustively testing, we test some
									 * patterns by shifting '1' bits through a field of
									 * '0's and '0' bits through a field of '1's (i.e.
				* pattern and ~pattern).
									 */
			addr = start;
			dummy = start + 1;
			for (j = 0;
			     j < sizeof(bitpattern)/sizeof(bitpattern[0]);
			     j++) {
				for (val = bitpattern[j]; val != 0; val <<= 1) {
					*addr  = val;
					/* clear the test data off of the bus */
					*dummy	= ~val;
					readback = *addr;
					if (readback != val) {
						printf("FAILURE (data line): " \
						       "expected %08lx, actual %08lx\n",
						       val, readback);
						errs++;
					}
					*addr  = ~val;
					*dummy	= val;
					readback = *addr;
					if (readback != ~val) {
						printf("FAILURE (data line): " \
						       "Is %08lx, should be %08lx\n",
						       readback, ~val);
						errs++;
					}
				}
			}
		}

		if ((type == spl_mtest_addr) || (type == spl_mtest_all)) {
			/*
			 * Based on code whose Original Author and Copyright
			 * information follows: Copyright (c) 1998 by Michael
			 * Barr. This software is placed into the public
			 * domain and may be used for any purpose. However,
			 * this notice must not be changed or removed and no
			 * warranty is either expressed or implied by its
			 * publication or distribution.
			 */

			/*
			 * Address line test
			 *
			 * Description: Test the address bus wiring in a
			 *		memory region by performing a walking
			 *		1's test on the relevant bits of the
			 *		address and checking for aliasing.
			 *		This test will find single-bit
			 *		address failures such as stuck -high,
			 *		stuck-low, and shorted pins. The base
			 *		address and size of the region are
			 *		selected by the caller.
			 *
			 * Notes:	For best results, the selected base
			 *		address should have enough LSB 0's to
			 *		guarantee single address bit changes.
			 *		For example, to test a 64-Kbyte
			 *		region, select a base address on a
			 *		64-Kbyte boundary. Also, select the
			 *		region size as a power-of-two if at
			 *		all possible.
			 *
			 * Returns:
			 * 0 if the test succeeds, 1 if the test fails.
			 */
			len = ((ulong)end - (ulong)start)/sizeof(vu_long);
			pattern = (vu_long) 0xaaaaaaaa;
			anti_pattern = (vu_long) 0x55555555;

			printf("%s:%d: length = 0x%.8lx\n",
			       __FILE__, __LINE__,
			       len);
			/*
			 * Write the default pattern at each of the
			 * power-of-two offsets.
			 */
			for (offset = 1; offset < len; offset <<= 1)
				start[offset] = pattern;

			/*
			 * Check for address bits stuck high.
			 */
			test_offset = 0;
			start[test_offset] = anti_pattern;

			for (offset = 1; offset < len; offset <<= 1) {
				temp = start[offset];
				if (temp != pattern) {
					printf("\nFAILURE: Address bit stuck" \
					       " high @ 0x%.8lx:" \
					       " expected 0x%.8lx," \
					       " actual 0x%.8lx\n", \
					       (ulong)&start[offset],
					       pattern, temp);
					errs++;
				}
			}
			start[test_offset] = pattern;
			WATCHDOG_RESET();

			/*
			 * Check for addr bits stuck low or shorted.
			 */
			for (test_offset = 1; test_offset < len;
			     test_offset <<= 1) {
				start[test_offset] = anti_pattern;

				for (offset = 1; offset < len; offset <<= 1) {
					temp = start[offset];
					if ((temp != pattern) &&
					    (offset != test_offset)) {
						printf("\nFAILURE: Address bit"\
						       "stuck low or"
						       " shorted @" \
						       " 0x%.8lx:" \
						       " expected 0x%.8lx, "\
						       "actual 0x%.8lx\n",
						       (ulong)&start[offset],
						       pattern,
						       temp);
						errs++;
					}
				}
				start[test_offset] = pattern;
			}
		}

		if ((type == spl_mtest_mtest) || (type == spl_mtest_all)) {
			/*
			 * Description: Test the integrity of a physical
			 *	memory device by performing an
			 *	increment/decrement test over the
			 *	entire region. In the process every
			 *	storage bit in the device is tested
			 *	as a zero and a one. The base address
			 *	and the size of the region are
			 *	selected by the caller.
			 *
			 * Returns:
			 *     0 if the test succeeds, 1 if the test fails.
			 */
			num_words =
				((ulong)end - (ulong)start)/sizeof(vu_long) + 1;

			/*
			 * Fill memory with a known pattern.
			 */
			for (pattern = 1, offset = 0;
			     offset < num_words; pattern++,
				     offset++) {
				start[offset] = pattern;
				if ((offset % 1000000) == 0)
					WATCHDOG_RESET();
			}

			/*
			 * Check each location and invert it
			 * for the second pass.
			 */
			for (pattern = 1, offset = 0;
			     offset < num_words; pattern++,
				     offset++) {
				if ((offset % 1000000) == 0)
					WATCHDOG_RESET();
				temp = start[offset];
				if (temp != pattern) {
					printf("\nFAILURE (read/write) " \
					       "@ 0x%.8lx:" \
					       " expected 0x%.8lx," \
					       " actual 0x%.8lx)\n",
					       (ulong)&start[offset],
					       pattern, temp);
					errs++;
				}

				anti_pattern = ~pattern;
				start[offset] = anti_pattern;
			}

			/*
			 * Check each location for the inverted pattern
			 * and zero it.
			 */
			for (pattern = 1, offset = 0; offset < num_words;
			     pattern++,
				     offset++) {
				if ((offset % 1000000) == 0)
					WATCHDOG_RESET();
				anti_pattern = ~pattern;
				temp = start[offset];
				if (temp != anti_pattern) {
					printf("\nFAILURE (read/write):"\
					       " @ 0x%.8lx:"
					       " expected 0x%.8lx, "\
					       "actual 0x%.8lx)\n",\
					       (ulong)&start[offset],
					       anti_pattern,
					       temp);
					errs++;
				}
				start[offset] = 0;
			}
		}
	}
#endif
	return 0;
}

/*
  ==============================================================================
  ==============================================================================
  Global Stuff
  ==============================================================================
  ==============================================================================
*/

/* For spl mtest range testing, find the memory ranges (1G page table entries)
   that cover what is being tested */
void sw_test_page_fit(unsigned long in_addr, unsigned long in_len,
		      unsigned long mbist_addr[],
		      unsigned long mbist_len[])
{
	unsigned int i = 0, j = 0;
	unsigned long start_addr = 0;

	for (i = 0; i < 16; i++) {
		if (in_addr < (start_addr + 0x400000)) {
			if ((in_addr + in_len) <= (start_addr + 0x400000)) {
				mbist_addr[j] = in_addr;
				mbist_len[j] = in_len;
				mbist_len[j+1] = 0;
				return;
			} else {
				if (i == 15) {
					/* supports only 16 GB sysmem */
					return;
				}
				mbist_addr[j] = in_addr;
				mbist_len[j] = (start_addr + 0x400000)
					- in_addr;
				in_addr = start_addr + 0x400000;
				in_len = (mbist_addr[j] + in_len)
					- (start_addr + 0x400000);
				start_addr = start_addr + 0x400000;
				j++;
			}
		} else {
			start_addr = start_addr + 0x400000;
		}
	}
}

/* Create Page table entries and run spl_mtest on ranges provided
   in U-boot parameter file */
void run_spl_mtest_ranges(unsigned long in_addr, unsigned long in_len)
{
#if 0
	unsigned long *add_sw_addr, *add_sw_len;
	int j;

	add_sw_addr = malloc(3 * sizeof(unsigned long));
	add_sw_len = malloc(3 * sizeof(unsigned long));
	memset(add_sw_addr, 0, 3 * sizeof(unsigned long));
	memset(add_sw_len, 0, 3 * sizeof(unsigned long));

	printf("test_addr = 0x%llx, test_len = 0x%llx\n", (unsigned long long)in_addr*256, (unsigned long long)(in_len*256));

	sw_test_page_fit(in_addr, in_len, add_sw_addr, add_sw_len);
	for (j = 0; j < 3; j++) {
		unsigned long start_addr = 0, end_addr = 0;
		unsigned long val = 0;
		if (add_sw_len[j] != 0) {
			unsigned long *out;
			int count, ncount;
			if (((unsigned long long)(add_sw_addr[j]
						  + add_sw_len[j])*256) <= 0x40000000) {
				if ((global->flags
				     & PARAMETERS_GLOBAL_ENABLE_SW_MEM_MTEST)
				    && (global->flags
					& PARAMETERS_GLOBAL_ENABLE_SW_MEM_ADDR_TEST)
				    && (global->flags
					& PARAMETERS_GLOBAL_ENABLE_SW_MEM_DATA_TEST)) {
					if (spl_mtest((unsigned long *)
						      ((add_sw_addr[j]*256) + 0x40000000),
						      (unsigned long *)(((add_sw_addr[j]
									  + add_sw_len[j])*256) + 0x40000000-1),
						      1, spl_mtest_all)) {
						printf("SPL Memory Test FAILED\n");
					}
					continue;
				}
				if (global->flags
				    & PARAMETERS_GLOBAL_ENABLE_SW_MEM_MTEST) {
					if (spl_mtest((unsigned long *)
						      ((add_sw_addr[j]*256) + 0x40000000),
						      (unsigned long *)(((add_sw_addr[j]
									  + add_sw_len[j])*256) + 0x40000000-1),
						      1, spl_mtest_all)) {
						printf("SPL Memory MTest FAILED\n");
					}
				}
				if (global->flags &
				    PARAMETERS_GLOBAL_ENABLE_SW_MEM_ADDR_TEST) {
					if (spl_mtest((unsigned long *)
						      ((add_sw_addr[j]*256) + 0x40000000),
						      (unsigned long *)(((add_sw_addr[j]
									  + add_sw_len[j])*256) + 0x40000000-1),
						      1, spl_mtest_addr)) {
						printf("SPL Memory ADDR Test FAILED\n");
					}
				}
				if (global->flags &
				    PARAMETERS_GLOBAL_ENABLE_SW_MEM_DATA_TEST) {
					if (spl_mtest((unsigned long *)
						      ((add_sw_addr[j]*256) + 0x40000000),
						      (unsigned long *)(((add_sw_addr[j]
									  + add_sw_addr[j])*256) + 0x40000000-1),
						      1, spl_mtest_data)) {
						printf("SPL Memory DATA Test FAILED\n");
					}
				}
				continue;
			} else if ((((unsigned long long)add_sw_addr[j]*256)
				    >= 0x40000000)
				   && (((unsigned long long)(add_sw_addr[j]
							     + add_sw_len[j])*256) <= 0x80000000)) {
				start_addr = ((unsigned long long)
					      add_sw_addr[j]*256) - 0x40000000;
				val = 0x40040c52;
			} else if ((((unsigned long long)add_sw_addr[j]*256)
				    >= 0x80000000)
				   && (((unsigned long long)(add_sw_addr[j]
							     + add_sw_len[j])*256) <= 0xc0000000)) {
				start_addr = ((unsigned long long)
					      add_sw_addr[j]*256) - 0x80000000;
				val = 0x80040c52;
			} else if ((((unsigned long long)add_sw_addr[j]*256)
				    >= 0xc0000000)
				   && (((unsigned long long)(add_sw_addr[j]
							     + add_sw_len[j])*256) <= 0x100000000)) {
				start_addr = ((unsigned long long)
					      add_sw_addr[j]*256) - 0xc0000000;
				val = 0xc0040c52;
			} else if ((((unsigned long long)add_sw_addr[j]*256)
				    >= 0x100000000)
				   && (((unsigned long long)(add_sw_addr[j]
							     + add_sw_len[j])*256) <= 0x140000000)) {
				start_addr = ((unsigned long long)
					      add_sw_addr[j]*256) - 0x100000000;
				val = 0x00140c52;
			} else if ((((unsigned long long)add_sw_addr[j]*256)
				    >= 0x140000000)
				   && (((unsigned long long)(add_sw_addr[j]
							     + add_sw_len[j])*256) <= 0x180000000)) {
				start_addr = ((unsigned long long)
					      add_sw_addr[j]*256) - 0x140000000;
				val = 0x40140c52;
			} else if ((((unsigned long long)add_sw_addr[j]*256)
				    >= 0x180000000)
				   && (((unsigned long long)(add_sw_addr[j]
							     + add_sw_len[j])*256) <= 0x1c0000000)) {
				start_addr = ((unsigned long long)
					      add_sw_addr[j]*256) - 0x180000000;
				val = 0x80140c52;
			} else if ((((unsigned long long)add_sw_addr[j]*256)
				    >= 0x1c0000000)
				   && (((unsigned long long)(add_sw_addr[j]
							     + add_sw_len[j])*256) <= 0x200000000)) {
				start_addr = ((unsigned long long)
					      add_sw_addr[j]*256) - 0x1c0000000;
				val = 0xc0140c52;
			} else if ((((unsigned long long)add_sw_addr[j]*256)
				    >= 0x200000000)
				   && (((unsigned long long) (add_sw_addr[j]
							      + add_sw_len[j])*256) <= 0x240000000)) {
				start_addr = ((unsigned long long)
					      add_sw_addr[j]*256) - 0x200000000;
				val = 0x00240c52;
			} else if ((((unsigned long long)add_sw_addr[j]*256)
				    >= 0x240000000)
				   && (((unsigned long long)(add_sw_addr[j]
							     + add_sw_len[j])*256) <= 0x280000000)) {
				start_addr = ((unsigned long long)
					      add_sw_addr[j]*256) - 0x240000000;
				val = 0x40240c52;
			} else if ((((unsigned long long)add_sw_addr[j]*256)
				    >= 0x280000000)
				   && (((unsigned long long)(add_sw_addr[j]
							     + add_sw_len[j])*256) <= 0x2c0000000)) {
				start_addr = ((unsigned long long)
					      add_sw_addr[j]*256) - 0x280000000;
				val = 0x80240c52;
			} else if ((((unsigned long long)add_sw_addr[j]*256)
				    >= 0x2c0000000)
				   && (((unsigned long long)(add_sw_addr[j]
							     + add_sw_len[j])*256) <= 0x300000000)) {
				start_addr = ((unsigned long long)
					      add_sw_addr[j]*256) - 0x2c0000000;
				val = 0xc0240c52;
			} else if ((((unsigned long long)add_sw_addr[j]*256)
				    >= 0x300000000)
				   && (((unsigned long long)(add_sw_addr[j]
							     + add_sw_len[j])*256) <= 0x340000000)) {
				start_addr = ((unsigned long long)
					      add_sw_addr[j]*256) - 0x300000000;
				val = 0x00340c52;
			} else if ((((unsigned long long)add_sw_addr[j]*256)
				    >= 0x340000000)
				   && (((unsigned long long)(add_sw_addr[j]
							     + add_sw_len[j])*256) <= 0x380000000)) {
				start_addr = ((unsigned long long)
					      add_sw_addr[j]*256) - 0x340000000;
				val = 0x40340c52;
			} else if ((((unsigned long long)add_sw_addr[j]*256)
				    >= 0x380000000)
				   && (((unsigned long long)(add_sw_addr[j]
							     + add_sw_len[j])*256) <= 0x3c0000000)) {
				start_addr = ((unsigned long long)
					      add_sw_addr[j]*256) - 0x380000000;
				val = 0x80340c52;
			} else if ((((unsigned long long)add_sw_addr[j]*256)
				    >= 0x3c0000000)
				   && (((unsigned long long)(add_sw_addr[j]
							     + add_sw_len[j])*256) <= 0x400000000)) {
				start_addr = ((unsigned long long)
					      add_sw_addr[j]*256) - 0x3c0000000;
				val = 0xc0340c52;
			} else {
				printf("Unsupported memory range\n");
				continue;
			}
			end_addr = start_addr + (add_sw_len[j] * 256)-1;
			out = (unsigned long *)
				(secure_page_table + 0x3000);
			for (count = 0; count < 0x1000; ) {
				for (ncount = 0; ncount < 16; ncount++) {
					*out++ = val;
					count = count + 4;
				}
				val += 0x1000000;
			}
			mmu_page_table_flush((unsigned long)secure_page_table,
					     (unsigned long)secure_page_table +
					     PAGE_TABLE_SIZE);
			if ((global->flags
			     & PARAMETERS_GLOBAL_ENABLE_SW_MEM_MTEST)
			    && (global->flags
				& PARAMETERS_GLOBAL_ENABLE_SW_MEM_ADDR_TEST)
			    && (global->flags
				& PARAMETERS_GLOBAL_ENABLE_SW_MEM_DATA_TEST)) {
				if (spl_mtest(
					    (unsigned long *)(start_addr+0xc0000000),
					    (unsigned long *)(end_addr+0xc0000000),
					    1, spl_mtest_all)) {
					printf("SPL Memory Test FAILED\n");
				}
				continue;
			}
			if (global->flags
			    & PARAMETERS_GLOBAL_ENABLE_SW_MEM_MTEST) {
				if (spl_mtest(
					    (unsigned long *)(start_addr+0xc0000000),
					    (unsigned long *)(end_addr+0xc0000000),
					    1, spl_mtest_mtest)) {
					printf("SPL Memory MTest FAILED\n");
				}
			}
			if (global->flags
			    & PARAMETERS_GLOBAL_ENABLE_SW_MEM_ADDR_TEST) {
				if (spl_mtest(
					    (unsigned long *)(start_addr+0xc0000000),
					    (unsigned long *)(end_addr+0xc0000000),
					    1, spl_mtest_addr)) {
					printf("SPL Memory ADDR Test FAILED\n");
				}
			}
			if (global->flags
			    & PARAMETERS_GLOBAL_ENABLE_SW_MEM_DATA_TEST) {
				if (spl_mtest(
					    (unsigned long *)(start_addr+0xc0000000),
					    (unsigned long *)(end_addr+0xc0000000),
					    1, spl_mtest_data)) {
					printf("SPL Memory DATA Test FAILED\n");
				}
			}
		} else
			break;
	}
#endif
}

/*
  ------------------------------------------------------------------------------
  check_memory_ranges
*/

#if !defined(CONFIG_AXXIA_EMU) && !defined(CONFIG_AXXIA_SIM)
#if 0
static void
check_memory_ranges(void)
{
	unsigned long *ranges = (unsigned long *)&global->memory_ranges;
	int i, j;
	unsigned long *mbist_addr, *mbist_len;
	unsigned long *add_mbist_addr, *add_mbist_len;
	unsigned long *add_sw_addr, *add_sw_len;
	unsigned long *test_addr, *test_len;
	unsigned long *prot_addr, *prot_len;
	unsigned long memSize, dual_ddr, maskbits;
	unsigned ret;

	mbist_addr = malloc(32 * 3 * sizeof(unsigned long));
	add_mbist_addr = malloc(32 * sizeof(unsigned long));
	add_sw_addr = malloc(32 * sizeof(unsigned long));
	test_addr = malloc(8 * 3 * sizeof(unsigned long));
	mbist_len = malloc(32 * 3 * sizeof(unsigned long));
	add_mbist_len = malloc(32 * sizeof(unsigned long));
	add_sw_len = malloc(32 * sizeof(unsigned long));
	test_len = malloc(8 * 3 * sizeof(unsigned long));
	prot_addr = malloc(5 * sizeof(unsigned long));
	prot_len = malloc(5 * sizeof(unsigned long));

	memset(mbist_addr, 0, 32 * 3 * sizeof(unsigned long));
	memset(mbist_len, 0, 32 * 3 * sizeof(unsigned long));
	memset(add_mbist_addr, 0, 32 * sizeof(unsigned long));
	memset(add_mbist_len, 0, 32 * sizeof(unsigned long));
	memset(add_sw_addr, 0, 32 * sizeof(unsigned long));
	memset(add_sw_len, 0, 32 * sizeof(unsigned long));
	memset(test_addr, 0, 8 * sizeof(unsigned long));
	memset(test_len, 0, 8 * sizeof(unsigned long));
	memset(prot_addr, 0, 5 * sizeof(unsigned long));
	memset(prot_len, 0, 5 * sizeof(unsigned long));


	for (i = 0; i < 8; i++) {
		unsigned long long offset = (unsigned long long)*ranges++;
		unsigned long long length = (unsigned long long)*ranges++;

		offset <<= 20;
		length <<= 20;

		if (0ULL != length) {
			printf("Testing Memory From 0x%llx, 0x%llx bytes\n",
			       offset, length);
			mbist_addr[i] = offset/256;
			mbist_len[i] = length/256;
		} else {
			mbist_len[i] = 0;
			test_len[i] = 0;
			prot_len[i] = 0;
			break;
		}
	}
	memSize = sysmem->totalSize/256;

#ifdef CONFIG_HYBRID_MBIST

	if (sysmem->num_interfaces == 0x2)
		dual_ddr = 1;
	else
		dual_ddr = 0;

	if (sysmem->num_ranks_per_interface == 0x2) {
		maskbits = 4;
	} else if (sysmem->num_ranks_per_interface == 0x4) {
		maskbits = 5;
	} else {
		/* sysmem->num_ranks_per_interface is 1 */
		maskbits = 3;
	}

	ret = mbist_range(memSize, dual_ddr, maskbits, 1024,
			  mbist_addr, mbist_len,
			  test_addr, test_len, prot_addr, prot_len);
	if (ret != 0) {
		printf("mbist_range failed with %d\n", ret);
	} else {
		for (i = 0; i < 96; i++) {
			if (mbist_len[i] != 0) {
				mbist_power2(mbist_addr[i], mbist_len[i],
					     add_mbist_addr, add_mbist_len);
				for (j = 0; j < 32; j++) {
					if (add_mbist_len[j] != 0) {
						axxia_sysmem_bist(
							(unsigned long long)
							add_mbist_addr[j]*256,
							(unsigned long long)
							add_mbist_len[j]*256);
					} else {
						break;
					}
				}
			} else {
				break;
			}
		}
		for (i = 0; i < 96; i++) {
			if (test_len[i] != 0) {
				if ((test_addr[i]+test_len[i]) > memSize) {
					printf("Testing range exceeds System memory size\n");
				} else if (((unsigned long long)test_len[i]*256)
					   > 0x40000000) {
					printf("Testing length cannot exceed 1G \n");
				} else {
					run_spl_mtest_ranges(test_addr[i],
							     test_len[i]);
				}
			} else {
				break;
			}
		}
		for (i = 0; i < 5; i++) {
			if (prot_len[i] != 0)
				printf("prot_addr = 0x%lx, prot_len = 0x%lx\n", prot_addr[i], prot_len[i]);
			else
				break;
		}
	}
#else
	for (i = 0; i < 8; i++) {
		if (mbist_len[i] != 0) {
			if ((mbist_addr[i]+mbist_len[i]) > memSize) {
				printf("Testing range exceeds System memory size\n");
			} else if (((unsigned long long)mbist_len[i]*256)
				   > 0x40000000) {
				printf("Testing length cannot exceed 1G \n");
			} else {
				run_spl_mtest_ranges(mbist_addr[i],
						     mbist_len[i]);
			}
		} else
			break;
	}
#endif
}
#endif

#endif	/* CONFIG_AXXIA_EMU */

u32 spl_boot_device(void)
{
	return (u32) BOOT_DEVICE_SPI;
}


/*
  ------------------------------------------------------------------------------
  verify_image
*/

static int
verify_image(struct spi_flash *flash,
	     unsigned long flash_offset,
	     int secure_boot)
{
	struct image_header header;
	char *sbb_magic;
	unsigned char sbb_encrypted;
	unsigned int sbb_size;
	void *membase = (void *)0x1000;

	/*
	  The U-Boot SPI flash interface uses NULL in the in or out
	  address to indicate direction.  That being the case, it
	  isn't possible to copy from SPI flash to address 0 (base of
	  system memory).  Since the header has to be skipped at the
	  end anyway, with a memmove(), just start a bit above 0.
	*/

	/*
	  Must begin with a U-Boot mkimage header of some sort.
	*/

	spi_flash_read(flash, flash_offset,
		       sizeof(struct image_header), &header);
	spl_parse_image_header(&header);
	spi_flash_read(flash, flash_offset,
		       spl_image.size + sizeof(struct image_header),
		       membase);
	spl_image.load_addr += (unsigned long)membase;

	if (!image_check_magic(&header)) {
		puts("\tBad Magic!\n");

		return -1;
	}

	if (!image_check_target_arch(&header)) {
		puts("\tWrong Architecture!\n");

		return -1;
	}

	if (ntohl(header.ih_dcrc) !=
	    crc32(0, (unsigned char *)
		  (membase + sizeof(struct image_header)),
		  (spl_image.size - sizeof(struct image_header)))) {
		puts("\tBad Checksum!\n");

		return -1;
	}

	/*
	  If secure boot is enabled, verify.
	*/

	if (0 != secure_boot) {
#ifdef CONFIG_AXXIA_SIM
		memmove((void *)0,
			((void *)membase + sizeof(struct image_header) + 12),
			spl_image.size);

		return 0;
#else
		if (0 != sbb_verify_image(((void *)membase +
					   sizeof(struct image_header)),
					  (void *)0, 0, 1, 0)) {
			puts("\tInsecure!\n");

			return -1;
		} else {
			return 0;
		}
#endif
	}

	/*
	  If secure boot is not enabled, but the image is signed,
	  remove the secure boot header (12 bytes in the unencrypted
	  case).
	*/

	sbb_magic = (membase + sizeof(struct image_header));
	sbb_encrypted = *((unsigned char *)(membase +
					    sizeof(struct image_header) + 9));
	sbb_encrypted &= 1;

	if (0 == strncmp(sbb_magic, "SBB!", 4)) {
		if (0 != sbb_encrypted)
			return -1;

		sbb_size =
			ntohl(*((unsigned int *)(membase +
						 sizeof(struct image_header) +
						 4)));
		memmove((void *)0,
			((void *)membase + sizeof(struct image_header) + 12),
			sbb_size);

		return 0;
	}

	/*
	  Remove the mkimage header.
	*/

	memmove((void *)0, ((void *)membase + sizeof(struct image_header)),
		(spl_image.size - sizeof(struct image_header)));

	return 0;
}

/*
  ------------------------------------------------------------------------------
  jump_to_monitor
*/

static void
jump_to_monitor(void *address)
{
	void (*entry)(void);

	entry = (void (*)(void))address;
	cleanup_before_linux();
	entry();
	acp_failure(__FILE__, __func__, __LINE__);

	return;
}

/*
  ------------------------------------------------------------------------------
*/

static void
load_image(void)
{
	struct spi_flash *flash;
	int watchdog_timeout;
	int a_valid;
	int b_valid;
	unsigned long a_sequence = 0;
	unsigned long b_sequence = 0;
	int copy_to_use = 0;
	int sbb_enabled = 0;
	struct image_header header;

	/*
	 * Load U-Boot image from SPI flash into RAM
	 */

	flash = spi_flash_probe(CONFIG_SPL_SPI_BUS, CONFIG_SPL_SPI_CS,
				CONFIG_SF_DEFAULT_SPEED,
				CONFIG_SF_DEFAULT_MODE);

	if (!flash) {
		puts("SPI probe failed.\n");
		hang();
	}

	if (is_redundant_enabled()) {
		/*
		  Was the last reset caused by a watchdog timeout?
		*/

		watchdog_timeout = readl(SYSCON + 0xdc);
		watchdog_timeout = (0 != (watchdog_timeout & 0x4));

		/*
		  Is this a secure boot?
		*/

		sbb_enabled = (1 == is_sbb_enabled(0));

		/*
		  Is image A valid?
		*/

		puts("Checking U-Boot Image A\n");

		if (0 == verify_image(flash, CONFIG_UBOOT_OFFSET, sbb_enabled))
			a_valid = 1;
		else
			a_valid = 0;

		if (1 == a_valid) {
			char *temp;

			temp = getenv("uboot_a_sequence");

			if (NULL != temp)
				a_sequence = simple_strtoul(temp, NULL, 0);
			else
				a_sequence = 0;
		}

		/*
		  Is image B valid?
		*/

		puts("Checking U-Boot Image B\n");

		if (0 == verify_image(flash, CONFIG_UBOOT_OFFSET_REDUND,
				      sbb_enabled))
			b_valid = 1;
		else
			b_valid = 0;

		if (1 == b_valid) {
			char *temp;

			temp = getenv("uboot_b_sequence");

			if (NULL != temp)
				b_sequence = simple_strtoul(temp, NULL, 0);
			else
				b_sequence = 0;
		}

		if (0 == a_valid && 0 == b_valid) {
			acp_failure(__FILE__, __func__, __LINE__);
		} else if (0 == a_valid && 0 != b_valid) {
			copy_to_use = 1;
		} else if (0 != a_valid && 0 == b_valid) {
			copy_to_use = 0;
		} else {
			if (0xffffffff == a_sequence && b_sequence == 0)
				copy_to_use = 1;
			else if (b_sequence > a_sequence)
				copy_to_use = 1;

			if (0 != watchdog_timeout)
				copy_to_use = (0 == copy_to_use) ? 1 : 0;
		}

		printf("U-Boot: Watchdog %d A/B Valid %d/%d A/B Sequence %lu/%lu => %s\n",
		       watchdog_timeout, a_valid, b_valid,
		       a_sequence, b_sequence,
		       (0 == copy_to_use) ? "A" : "B");

		/*
		  If B was selected, do nothing, as it has already been
		  loaded, if A, reload.
		*/

		if (0 == copy_to_use &&
		    0 != verify_image(flash, CONFIG_UBOOT_OFFSET, sbb_enabled))
			acp_failure(__FILE__, __func__, __LINE__);
	} else {
		/* Load u-boot, mkimage header is 64 bytes. */
		spi_flash_read(flash, CONFIG_UBOOT_OFFSET, 0x40, &header);
		spl_parse_image_header(&header);
		spl_image.load_addr = 0;

		if (IH_MAGIC == image_get_magic(&header)) {
			/* Load a U-Boot Image, Verifying Checksum */
			spi_flash_read(flash, CONFIG_SYS_SPI_U_BOOT_OFFS +
				       sizeof(struct image_header),
				       spl_image.size,
				       (void *)0x1000);
			memmove((void *)0, (void *)0x1000, spl_image.size);

			if (ntohl(header.ih_dcrc) !=
			    crc32(0, (unsigned char *)0,
				  (spl_image.size -
				   sizeof(struct image_header)))) {
				puts("Bad U-Boot Image Checksums!\n");
				acp_failure(__FILE__, __func__, __LINE__);
			}
		} else {
			/* Load a U-Boot Binary */
			spi_flash_read(flash, CONFIG_SYS_SPI_U_BOOT_OFFS,
				       spl_image.size,
				       (void *)0x1000);
			memmove((void *)0, (void *)0x1000, spl_image.size);
		}

#ifdef CONFIG_AXXIA_SIM
		{
			void *header;
			char *sbb_magic;
			unsigned char sbb_encrypted;
			unsigned int sbb_size;

			header = malloc(12);
			memcpy(header, (void *)0, 12);
			sbb_magic = (void *)header;
			sbb_encrypted = *((unsigned char *)(header + 12));
			sbb_encrypted &= 1;

			if (0 == strncmp(sbb_magic, "SBB!", 4) &&
			    (0 == sbb_encrypted)) {
				sbb_size = ntohl(*((unsigned int *)4));
				memmove((void *)0, (void *)12, sbb_size);
				free(header);
			}
		}
#else
		if (0 != sbb_verify_image(0x00000000, 0x00000000, 0, 1, 0))
			acp_failure(__FILE__, __func__, __LINE__);
#endif
	}

#ifdef COPY_MONITOR_TO_RAM
	memcpy((void *)0x7ffc1000, (void *)0x8031001000, 0x10000);
	jump_to_monitor((void *)0x7ffc1000);
	/*asm volatile ("ldr x10, =0x7ffc1000\nret x10");*/
#else
	jump_to_monitor((void *)0x8031001000);
	/*asm volatile ("ldr x10, =0x8031001000\nret x10");*/
#endif
}

/*
  ------------------------------------------------------------------------------
  board_init_f

  Replaces the weakly defined board_init_f in arch/arm/lib/spl.c.
*/

void
board_init_f(ulong dummy)
{
	int rc;
	unsigned int value;
	unsigned int pvalue;
	int i;

#ifdef CONFIG_MEMORY_RETENTION
	int need_write;
#endif	/* CONFIG_MEMORY_RETENTION */

 	/* Clear bss. */
	memset(__bss_start, 0, __bss_end - __bss_start);

	/* Set global data pointer. */
	gd = &gdata;

#ifdef CONFIG_SYS_SPL_MALLOC_START
        mem_malloc_init((void *)CONFIG_SYS_SPL_MALLOC_START,
                        CONFIG_SYS_SPL_MALLOC_SIZE);
#endif

	/* read and clear reset status (write one to clear) */
	value = readl(SYSCON + 0x100);
	writel(value, (SYSCON + 0x100));

	/*
	 * if this is a power-up/pin reset then initialize
	 * persistent registers 
	 */

	if ((value & 0x00000001))
		for (i = 0; i < 9; i++)
			writel(0, (SYSCON + (0xdc + (4 * i))));

	/*
	 * Set bit 2 of 0xdc if the last reset was caused by a watchdog
	 * timeout; otherwise, clear it.
	 */

	pvalue = readl(SYSCON + 0xdc);

	if (0 != (value & 0x66))
		pvalue |= 0x4;
	else
		pvalue &= ~0x4;

	writel(pvalue, (SYSCON + 0xdc));
	gd->baudrate = CONFIG_BAUDRATE;
	serial_initialize();
	serial_init();
	gd->have_console = 1;

	puts("_______              _____            _____________________ \n"
	     "___    |___  _____  ____(_)_____ _    __  ___/__  __ \\__  / \n"
	     "__  /| |_  |/_/_  |/_/_  /_  __ `/    _____ \\__  /_/ /_  /  \n"
	     "_  ___ |_>  < __>  < _  / / /_/ /     ____/ /_  ____/_  /___\n"
	     "/_/  |_/_/|_| /_/|_| /_/  \\__,_/      /____/ /_/     /_____/\n\n");

#ifdef AXXIA_VERSION
	printf("Axxia Version: %s\n", AXXIA_VERSION);
#else
	printf("Axxia Version: UNKNOWN\n");
#endif

#ifdef AXXIA_ATF_VERSION
	printf("Axxia ATF Version: %s\n", AXXIA_ATF_VERSION);
#else
	printf("Axxia ATF Version: UNKNOWN\n");
#endif

#ifdef CONFIG_HW_WATCHDOG
	rc = start_watchdog(WATCHDOG_TIMEOUT_SECS);

	if (0 == rc)
		puts("Started Watchdog Timer\n");
	else
		puts("Failed to start watchdog timer!\n");
#endif	/* CONFIG_HW_WATCHDOG */

	rc = axxia_initialize();
	if (0 != rc)
		acp_failure(__FILE__, __func__, __LINE__);

#if !defined(CONFIG_AXXIA_EMU) && !defined(CONFIG_AXXIA_SIM)
	puts("");
	axxia_display_clocks();
#endif

#ifdef CONFIG_SPL_MTEST
	printf("Running the SPL Memory Test\n");
	if (spl_mtest((unsigned long *)0x40000000,
		      (unsigned long *)0x7fffffff, 10, spl_mtest_all)) {
		printf("SPL Memory Test FAILED\n");
	} else {
		printf("SPL Memory Test SUCCESSFUL\n");
	}
#endif	/* CONFIG_SPL_MTEST */

#ifdef SYSCACHE_ONLY_MODE
	printf("Syscache Only Mode!\n");

	{
		unsigned long value;
		unsigned long *address;

		address = (unsigned long *)0x40000000;

		for (;;) {
			value = *address;
			printf("Read 0x%x from 0x%p\n", value, address);
			value = ~value;
			*address = value;
			value = *address;
			printf("Read 0x%x from 0x%p\n", value, address);

			if ((unsigned long)address < 0x40800000)
				++address;
			else
				address = (unsigned long *)0x40000000;
		}
	}
#else  /* SYSCACHE_ONLY_MODE */

#if !defined(CONFIG_AXXIA_EMU) && !defined(CONFIG_AXXIA_SIM)
#if 0
	if (0 != (global->flags & PARAMETERS_GLOBAL_RUN_SMEM_BIST)) {
		printf("Testing Memory From 0, 0x%llx bytes\n",
		       sysmem->totalSize);
		axxia_sysmem_bist(0ULL, sysmem->totalSize);
	} else if (0 != (global->flags & PARAMETERS_GLOBAL_RUN_SMEM_RANGES)) {
		check_memory_ranges();
	}
#endif
#endif	/* CONFIG_AXXIA_EMU */

	printf("\nSystem Initialized\n\n");

#ifdef CONFIG_MEMORY_RETENTION
	need_write = 0;

	for (i = 0; i < sysmem->num_interfaces; i++) {
		phyRegs = retention + (i * DDR_PHY_REGS_SIZE);

		printf("checking phyRegs[%d] %p = %x\n", i, phyRegs, *phyRegs);

		if (*phyRegs == DDR_PHY_REGS_TAG_SAVE) {
			printf("Saved values for smId %d %p\n", i, phyRegs);
			*phyRegs = DDR_PHY_REGS_TAG_PROM;
			need_write = 1;
		}
	}

	if ( need_write) {
		printf("Writing DDR PHY registers to parameter space\n");
		write_parameters();
	}
#endif	/* CONFIG_MEMORY_RETENTION */

#endif	/* SYSCACHE_ONLY_MODE */

	/* Move the stack to ram. */
	asm volatile ("mov sp, %0" : : "r" (CONFIG_SYS_INIT_SP_ADDR));

	/*
	  For now, allow access from anywhere, to anywhere.
	*/

	/* MMAP-GPREG is 0x8032900000 (0x170.0.0) */
	/* MMAP-SCB is 0x8032000000 (0x170.1.0) */
	/* PERIPH-GPREG is 0x8080230000 (0x171.0.0) */
	/* PERIPH-SCB is 0x8080400000 (0x171.1.0) */
	/* TZC is 0x8004140000 (0x1d2.0.0) */

	/* 0x171.1.0xc = 0xffff */
	writel(0xffff, (PERIPH_SCB + 0xc));
	/* 0x171.1.0x10 = 0xffff */
	writel(0xffff, (PERIPH_SCB + 0x10));
	/* 0x170.1.0x54 = 0xffff */
	writel(0xffff, (MMAP_SCB + 0x54));
	/* 0x170.1.0x43800 0x2 */
	writel(0x2, (MMAP_SCB + 0x43800));
	/* 0x1d2.0.0x114 = 0xffffffff */
	writel(0xffffffff, (TZC + 0x114));
	/* 0x170.1.0x48 = 1 */
	writel(0x1, (MMAP_SCB + 0x48));

#ifdef CONFIG_SPL_ENV_SUPPORT
	mem_malloc_init((void *)CONFIG_SYS_MALLOC_BASE, CONFIG_SYS_MALLOC_SIZE);
	env_init();
	env_relocate();
#endif	/* CONFIG_SPL_ENV_SUPPORT */

	/*
	  Jump to the monitor.
	*/

	load_image();

	return;
}

/*
  ------------------------------------------------------------------------------
  spl_board_init
*/

void
spl_board_init(void)
{
	return;
}
