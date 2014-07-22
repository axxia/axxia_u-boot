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
#include <serial.h>
#include <malloc.h>
#include <spl.h>
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
}

/*
  ==============================================================================
  ==============================================================================
  Global Stuff
  ==============================================================================
  ==============================================================================
*/

/*
  ------------------------------------------------------------------------------
  reset_cpu_fabric

  This sequence switches the memory map from reset to mission, and
  resets some hardware elements, including the core.  After the 'wfi'
  instruction, execution will start at offset 0 in system memory.

  Does not return!
*/

void
reset_cpu_fabric(void)
{
	unsigned long value;

	WATCHDOG_RESET();
	set_vat_mission();

	/*
	  Don't use readl()/writel(), as those contain barriers.  The
	  barriers below are part of the sequence.
	*/

	/* syscontrol access key */
	*((unsigned long *)(SYSCON + 0x1000)) = 0xab;

	/* set the resetFab bit in reset_ctl */
	value = *((unsigned long *)(SYSCON + 0x1008));
	value |= 4;
	*((unsigned long *)(SYSCON + 0x1008)) = value;

	/* dsb */
	asm volatile ("mcr p15,0,%0,c7,c10,4" : : "r" (0));

	/* read back reset_ctl */
	value = *((unsigned long *)(SYSCON + 0x1008));

	/* dsb */
	asm volatile ("mcr p15,0,%0,c7,c10,4" : : "r" (0));

	/* isb */
	asm volatile ("mcr p15,0,%0,c7,c5,4" : : "r" (0));

	/* wfi */
	asm volatile ("wfi");

	/* isb */
	asm volatile ("mcr p15,0,%0,c7,c5,4" : : "r" (0));

	return;
}

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
	unsigned long *add_sw_addr, *add_sw_len;
	int j;

	add_sw_addr = malloc(3 * sizeof(unsigned long));
	add_sw_len = malloc(3 * sizeof(unsigned long));
	memset(add_sw_addr, 0, 3 * sizeof(unsigned long));
	memset(add_sw_len, 0, 3 * sizeof(unsigned long));

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
			out = (unsigned long *)(_page_table_start + 0x3000);
			for (count = 0; count < 0x1000; ) {
				for (ncount = 0; ncount < 16; ncount++) {
					*out++ = val;
					count = count + 4;
				}
				val += 0x1000000;
			}
			mmu_page_table_flush(_page_table_start,
				_page_table_end);
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
}

/*
  ------------------------------------------------------------------------------
  check_memory_ranges
*/

#ifndef CONFIG_AXXIA_EMU
static void
check_memory_ranges(void)
{
	unsigned long *ranges = (unsigned long *)&global->memory_ranges;
	int i;
	unsigned long *test_addr, *test_len;
	unsigned long memSize;

	test_addr = malloc(8 * sizeof(unsigned long));
	test_len = malloc(8 * sizeof(unsigned long));
	memset(test_addr, 0, 8 * sizeof(unsigned long));
	memset(test_len, 0, 8 * sizeof(unsigned long));

	for (i = 0; i < 8; i++) {
		unsigned long long offset = (unsigned long long)*ranges++;
		unsigned long long length = (unsigned long long)*ranges++;

		offset <<= 20;
		length <<= 20;

		if (0ULL != length) {
			printf("Testing Memory From 0x%llx, 0x%llx bytes\n",
				offset, length);
			test_addr[i] = offset/256;
			test_len[i] = length/256;
		} else {
			test_len[i] = 0;
			break;
		}
	}
	memSize = sysmem->totalSize/256;

	for (i = 0; i < 8; i++) {
		if (test_len[i] != 0) {
			if ((test_addr[i]+test_len[i]) > memSize) {
				printf("Testing range exceeds\
					 System memory size\n");
			} else if (((unsigned long long)test_len[i]*256)
				> 0x40000000) {
				printf("Testing length cannot exceed 1G \n");
			} else {
				run_spl_mtest_ranges(test_addr[i], test_len[i]);
			}
		} else
			break;
	}
}

#endif	/* CONFIG_AXXIA_EMU */

u32 spl_boot_device(void)
{
	return (u32) BOOT_DEVICE_SPI;
}

void
spl_board_init(void)
{
	int rc;

#ifndef CONFIG_AXXIA_EMU
	unsigned long value;
	unsigned long pvalue;
	int i;

	/* read and clear reset status (write one to clear) */
	ncr_read32(NCP_REGION_ID(0x156, 0), 0x100, (ncp_uint32_t *)&value);
	ncr_write32(NCP_REGION_ID(0x156, 0), 0x100, (ncp_uint32_t)value);

	/*
	 * if this is a power-up/pin reset then initialize
	 * persistent registers 
	 */

	if ((value & 0x00000001))
		for (i = 0; i < 9; i++)
			ncr_write32(NCP_REGION_ID(0x156, 0x00),
				    (0xdc + (4 * i)), 0);

	/*
	 * Set bit 2 of 0xdc if the last reset was caused by a watchdog
	 * timeout; otherwise, clear it.
	 */

	ncr_read32(NCP_REGION_ID(0x156, 0), 0xdc, (ncp_uint32_t *) &pvalue);

	if (0 != (value & 0xa))
		pvalue |= 0x4;
	else
		pvalue &= ~0x4;

	ncr_write32(NCP_REGION_ID(0x156, 0), 0xdc, pvalue);
#endif

	/*
	  The bootROM code leaves SPI device 0 selected, BZ 45907.
	  Deselect here.
	*/

	writel(0x1f, (unsigned long *)(SSP + SSP_CSR));

	gd->baudrate = CONFIG_BAUDRATE;
	serial_initialize();
	serial_init();

	puts("\n"
	     "   ___             _        __  __    ___            __    _______  __ \n"
	     "  / _ |__ ____ __ (_)__ _  / / / /___/ _ )___  ___  / /_  / __/ _ \\/ / \n"
	     " / __ |\\ \\ /\\ \\ // / _ `/ / /_/ /___/ _  / _ \\/ _ \\/ __/ _\\ \\/ ___/ /__\n"
	     "/_/ |_/_\\_\\/_\\_\\/_/\\_,_/  \\____/   /____/\\___/\\___/\\__/ /___/_/  /____/\n");
	printf("\nLSI Version: %s\n", get_lsi_version());

#ifdef CONFIG_HW_WATCHDOG
	rc = start_watchdog();

	if (0 == rc)
		puts("Started Watchdog Timer\n");
	else
		puts("Failed to start watchdog timer!\n");
#endif

	rc = axxia_initialize();
	if (0 != rc)
		acp_failure(__FILE__, __func__, __LINE__);

	axxia_display_clocks();

#ifdef CONFIG_SPL_MTEST
	printf("Running the SPL Memory Test\n");
	if (spl_mtest((unsigned long *)0x40000000,
		      (unsigned long *)0x7fffffff, 10, spl_mtest_all)) {
		printf("SPL Memory Test FAILED\n");
	} else {
		printf("SPL Memory Test SUCCESSFUL\n");
	}
#endif

#ifdef SYSCACHE_ONLY_MODE

	printf("Syscache Only Mode!\n");
	asm volatile ("1: b 1b");

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

#else

#ifndef CONFIG_AXXIA_EMU
	if (0 != (global->flags & PARAMETERS_GLOBAL_RUN_SMEM_BIST)) {
		printf("Testing Memory From 0, 0x%llx bytes\n",
		       sysmem->totalSize);
		axxia_sysmem_bist(0ULL, sysmem->totalSize);
	} else if (0 != (global->flags & PARAMETERS_GLOBAL_RUN_SMEM_RANGES)) {
		check_memory_ranges();
	}
#endif

	printf("System initialized\n");

#ifdef CONFIG_MEMORY_RETENTION
	{
		int i;
		int need_write = 0;
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
	}
#endif

#ifdef CONFIG_SPL_ENV_SUPPORT
	mem_malloc_init((0x40000000 + CONFIG_SYS_MALLOC_BASE),
			CONFIG_SYS_MALLOC_SIZE);
	env_init();
	env_relocate();
#endif

#endif
}

/*
  ------------------------------------------------------------------------------
  verify_image
*/

#ifdef CONFIG_REDUNDANT_UBOOT
static int
verify_image(struct spi_flash *flash,
	     unsigned long flash_offset,
	     int secure_boot)
{
	struct image_header header;
	void *membase = (void *)0x40000000UL;

	if (secure_boot) {
		/*
		  Size is not available in this case (using a secure
		  image), so copy 2 Mb.
		*/
		spi_flash_read(flash, flash_offset,
			       CONFIG_SYS_MONITOR_LEN, membase);

		if (0 != sbb_verify_image(0, 0, 0, 0, 0)) {
			puts("\tInsecure!\n");

			return -1;
		}

		memcpy((void *)&header, membase, sizeof(struct image_header));
		spl_parse_image_header(&header);
	} else {
		spi_flash_read(flash, flash_offset,
			       sizeof(struct image_header), &header);
		spl_parse_image_header(&header);
		spi_flash_read(flash, flash_offset,
			       spl_image.size + sizeof(struct image_header),
			       membase);
	}

	/*
	  The base of system memory (0x40000000UL) should now contains
	  a U-Boot image.
	*/

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
	  Remove the header.
	*/

	memmove(membase, (membase + sizeof(struct image_header)),
		(spl_image.size - sizeof(struct image_header)));

	return 0;
}
#endif

/*
  ------------------------------------------------------------------------------
*/

void spl_spi_load_image(void)
{
	struct spi_flash *flash;
#ifdef CONFIG_REDUNDANT_UBOOT	
	int watchdog_timeout;
	int a_valid;
	int b_valid;
	unsigned long a_sequence = 0;
	unsigned long b_sequence = 0;
	int copy_to_use = 0;
	int sbb_enabled = 0;
#else  /* CONFIG_REDUNDANT_UBOOT */
	struct image_header header;
#endif	/* CONFIG_REDUNDANT_UBOOT */

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

#ifdef CONFIG_REDUNDANT_UBOOT

	/*
	  Was the last reset caused by a watchdog timeout?
	*/

	ncr_read32(NCP_REGION_ID(0x156, 0), 0xdc,
		   (ncp_uint32_t *)&watchdog_timeout);
	watchdog_timeout = ((watchdog_timeout & 0x4) >> 2);

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

	if (0 == verify_image(flash, CONFIG_UBOOT_OFFSET_REDUND, sbb_enabled))
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

#else  /* CONFIG_REDUNDANT_UBOOT */

	/* Load u-boot, mkimage header is 64 bytes. */
	spi_flash_read(flash, CONFIG_UBOOT_OFFSET, 0x40, &header);
	spl_parse_image_header(&header);
	/* Note that, in the SPL, SDRAM is virtually mapped to 0x40000000. */
	spl_image.load_addr = 0x40000000;

	if (IH_MAGIC == image_get_magic(&header)) {
		/* Load a U-Boot Image, Verifying Checksum */
		spi_flash_read(flash, CONFIG_SYS_SPI_U_BOOT_OFFS +
			       sizeof(struct image_header),
			       spl_image.size, (void *)spl_image.load_addr);

		if (ntohl(header.ih_dcrc) !=
		    crc32(0, (unsigned char *)0x40000000,
			  (spl_image.size - sizeof(struct image_header)))) {
			puts("Bad U-Boot Image Checksums!\n");
			acp_failure(__FILE__, __func__, __LINE__);
		}
	} else {
		/* Load a U-Boot Binary */
		spi_flash_read(flash, CONFIG_SYS_SPI_U_BOOT_OFFS,
			       spl_image.size, (void *)spl_image.load_addr);
	}


#ifndef CONFIG_AXXIA_EMU
	if (0 != sbb_verify_image(0x00000000, 0x00000000, 0, 1, 1))
		acp_failure(__FILE__, __func__, __LINE__);
#endif

#endif	/* CONFIG_REDUNDANT_UBOOT */
}

void
jump_to_image_no_args(struct spl_image_info *spl_image)
{
	reset_cpu_fabric();
	acp_failure(__FILE__, __func__, __LINE__);
}
