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
			}

			/*
			 * Check each location and invert it
			 * for the second pass.
			 */
			for (pattern = 1, offset = 0;
			     offset < num_words; pattern++,
				     offset++) {
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
  ------------------------------------------------------------------------------
  fix_up_vat
*/

static int
fix_up_vat(void)
{
	unsigned long buffer[4];
	int rc;

	rc = ncr_read(NCP_REGION_ID(0x16, 0x10), 0, 0x1000, 16, buffer);

	if (0 != rc)
		return -1;

	buffer[2] = 0;
	rc = ncr_write(NCP_REGION_ID(0x16, 0x10), 0, 0x1000, 16, buffer);

	if (0 != rc)
		return -1;

	return 0;
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

	fix_up_vat();

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
		unsigned long start_addr=0, end_addr=0;
		unsigned long val=0;
		if (test_len[i] != 0) {
			if ((test_addr[i]+test_len[i]) > memSize) {
				printf("Testing range exceeds System memory size\n");
			} else if (((unsigned long long)test_len[i]*256) > 0x40000000) {
				printf("Testing length cannot exceed 1G \n");
			} else {
				unsigned long *out;
				int count, ncount;
				if (((unsigned long long)(test_addr[i]+test_len[i])*256) < 0x40000000) {
					if ((global->flags & PARAMETERS_GLOBAL_ENABLE_SW_MEM_MTEST) &&
						(global->flags & PARAMETERS_GLOBAL_ENABLE_SW_MEM_ADDR_TEST) &&
						(global->flags & PARAMETERS_GLOBAL_ENABLE_SW_MEM_DATA_TEST)) {
						if (spl_mtest((unsigned long *)((test_addr[i]*256)+0x40000000),
	     						(unsigned long *)(((test_addr[i]+test_len[i])*256)
							+ 0x40000000), 1, spl_mtest_all)) {
							printf("SPL Memory Test FAILED\n");
						}
						continue;
					}
					if (global->flags & PARAMETERS_GLOBAL_ENABLE_SW_MEM_MTEST) {
						if (spl_mtest((unsigned long *)((test_addr[i]*256)+0x40000000),
	     						(unsigned long *)(((test_addr[i]+test_len[i])*256)
							+ 0x40000000), 1, spl_mtest_all)) {
							printf("SPL Memory MTest FAILED\n");
						}
					}
					if (global->flags & PARAMETERS_GLOBAL_ENABLE_SW_MEM_ADDR_TEST) {
						if (spl_mtest((unsigned long *)((test_addr[i]*256)+0x40000000),
	     						(unsigned long *)(((test_addr[i]+test_len[i])*256)
							+ 0x40000000), 1, spl_mtest_addr)) {
							printf("SPL Memory ADDR Test FAILED\n");
						}
					}
					if (global->flags & PARAMETERS_GLOBAL_ENABLE_SW_MEM_DATA_TEST) {
						if (spl_mtest((unsigned long *)((test_addr[i]*256)+0x40000000),
	     						(unsigned long *)(((test_addr[i]+test_len[i])*256)
							+ 0x40000000), 1, spl_mtest_data)) {
							printf("SPL Memory DATA Test FAILED\n");
						}
					}
					continue;
				} else if ((((unsigned long long)test_addr[i]*256) >= 0x40000000) 
						&& (((unsigned long long)(test_addr[i]+test_len[i])*256) < 0x80000000)) {
					start_addr = ((unsigned long long)test_addr[i]*256) - 0x40000000;
					end_addr = start_addr + (test_len[i] * 256);
					val= 0x40040c52;	
				} else if ((((unsigned long long)test_addr[i]*256) >= 0x80000000) 
						&& (((unsigned long long)(test_addr[i]+test_len[i])*256) < 0xc0000000)) {
					start_addr = ((unsigned long long)test_addr[i]*256) - 0x80000000;
					end_addr = start_addr + (test_len[i] * 256);
					val= 0x80040c52;
				} else if ((((unsigned long long)test_addr[i]*256) >= 0xc0000000) 
						&& (((unsigned long long)(test_addr[i]+test_len[i])*256) < 0x100000000)) {
					start_addr = ((unsigned long long)test_addr[i]*256) - 0xc0000000;
					end_addr = start_addr + (test_len[i] * 256);
					val= 0xc0040c52;
				} else if ((((unsigned long long)test_addr[i]*256) >= 0x100000000) 
						&& (((unsigned long long)(test_addr[i]+test_len[i])*256) < 0x140000000)) {
					start_addr = ((unsigned long long)test_addr[i]*256) - 0x100000000;
					end_addr = start_addr + (test_len[i] * 256);
					val= 0x00140c52;
				} else if ((((unsigned long long)test_addr[i]*256) >= 0x140000000) 
						&& (((unsigned long long)(test_addr[i]+test_len[i])*256) < 0x180000000)) {
					start_addr = ((unsigned long long)test_addr[i]*256) - 0x140000000;
					end_addr = start_addr + (test_len[i] * 256);
					val= 0x40140c52;
				} else if ((((unsigned long long)test_addr[i]*256) >= 0x180000000) 
						&& (((unsigned long long)(test_addr[i]+test_len[i])*256) < 0x1c0000000)) {
					start_addr = ((unsigned long long)test_addr[i]*256) - 0x180000000;
					end_addr = start_addr + (test_len[i] * 256);
					val= 0x80140c52;
				} else if ((((unsigned long long)test_addr[i]*256) >= 0x1c0000000) 
						&& (((unsigned long long)(test_addr[i]+test_len[i])*256) < 0x200000000)) {
					start_addr = ((unsigned long long)test_addr[i]*256) - 0x1c0000000;
					end_addr = start_addr + (test_len[i] * 256);
					val= 0xc0140c52;
				} else if ((((unsigned long long)test_addr[i]*256) >= 0x200000000) 
						&& (((unsigned long long)(test_addr[i]+test_len[i])*256) < 0x240000000)) {
					start_addr = ((unsigned long long)test_addr[i]*256) - 0x200000000;
					end_addr = start_addr + (test_len[i] * 256);
					val= 0x00240c52;
				} else if ((((unsigned long long)test_addr[i]*256) >= 0x240000000) 
						&& (((unsigned long long)(test_addr[i]+test_len[i])*256) < 0x280000000)) {
					start_addr = ((unsigned long long)test_addr[i]*256) - 0x240000000;
					end_addr = start_addr + (test_len[i] * 256);
					val= 0x40240c52;
				} else if ((((unsigned long long)test_addr[i]*256) >= 0x280000000) 
						&& (((unsigned long long)(test_addr[i]+test_len[i])*256) < 0x2c0000000)) {
					start_addr = ((unsigned long long)test_addr[i]*256) - 0x280000000;
					end_addr = start_addr + (test_len[i] * 256);
					val= 0x80240c52;
				} else if ((((unsigned long long)test_addr[i]*256) >= 0x2c0000000) 
						&& (((unsigned long long)(test_addr[i]+test_len[i])*256) < 0x300000000)) {
					start_addr = ((unsigned long long)test_addr[i]*256) - 0x2c0000000;
					end_addr = start_addr + (test_len[i] * 256);
					val= 0xc0240c52;
				} else if ((((unsigned long long)test_addr[i]*256) >= 0x300000000) 
						&& (((unsigned long long)(test_addr[i]+test_len[i])*256) < 0x340000000)) {
					start_addr = ((unsigned long long)test_addr[i]*256) - 0x300000000;
					end_addr = start_addr + (test_len[i] * 256);
					val= 0x00340c52;
				} else if ((((unsigned long long)test_addr[i]*256) >= 0x340000000) 
						&& (((unsigned long long)(test_addr[i]+test_len[i])*256) < 0x380000000)) {
					start_addr = ((unsigned long long)test_addr[i]*256) - 0x340000000;
					end_addr = start_addr + (test_len[i] * 256);
					val= 0x40340c52;
				} else if ((((unsigned long long)test_addr[i]*256) >= 0x380000000) 
						&& (((unsigned long long)(test_addr[i]+test_len[i])*256) < 0x3c0000000)) {
					start_addr = ((unsigned long long)test_addr[i]*256) - 0x380000000;
					end_addr = start_addr + (test_len[i] * 256);
					val= 0x80340c52;	
				} else if ((((unsigned long long)test_addr[i]*256) >= 0x3c0000000) 
						&& (((unsigned long long)(test_addr[i]+test_len[i])*256) < 0x400000000)) {
					start_addr = ((unsigned long long)test_addr[i]*256) - 0x380000000;
					end_addr = start_addr + (test_len[i] * 256);
					val= 0xc0340c52;	
				} else {
					printf("Unsupported memory range\n");
					continue;
				}

				out = (unsigned long *)(_page_table_start + 0x3000);

				for (count=0; count<0x1000; count++) {
					for(ncount=0;ncount<16;ncount++){
						*out++ = val;
						++count;
					}
					val += 0x1000000;
				}
				mmu_page_table_flush(_page_table_start, _page_table_end); 
				if ((global->flags & PARAMETERS_GLOBAL_ENABLE_SW_MEM_MTEST) &&
					(global->flags & PARAMETERS_GLOBAL_ENABLE_SW_MEM_ADDR_TEST) &&
					(global->flags & PARAMETERS_GLOBAL_ENABLE_SW_MEM_DATA_TEST)) {
					if (spl_mtest((unsigned long *)(start_addr+0xc0000000),
						(unsigned long *)(end_addr+0xc0000000),
						 1, spl_mtest_all)) {
						printf("SPL Memory Test FAILED\n");
					}
					continue;
				}
				if (global->flags & PARAMETERS_GLOBAL_ENABLE_SW_MEM_MTEST) {
					if (spl_mtest((unsigned long *)(start_addr+0xc0000000),
						(unsigned long *)(end_addr+0xc0000000),
						 1, spl_mtest_mtest)) {
						printf("SPL Memory MTest FAILED\n");
					}
				}
				if (global->flags & PARAMETERS_GLOBAL_ENABLE_SW_MEM_ADDR_TEST) {
					if (spl_mtest((unsigned long *)(start_addr+0xc0000000),
						(unsigned long *)(end_addr+0xc0000000),
						 1, spl_mtest_addr)) {
						printf("SPL Memory ADDR Test FAILED\n");
					}
				}
				if (global->flags & PARAMETERS_GLOBAL_ENABLE_SW_MEM_DATA_TEST) {
					if (spl_mtest((unsigned long *)(start_addr+0xc0000000),
						(unsigned long *)(end_addr+0xc0000000),
						 1, spl_mtest_data)) {
						printf("SPL Memory DATA Test FAILED\n");
					}
				}
			}
		} else {
			break;
		}
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

	rc = axxia_initialize();
	if (0 != rc)
		acp_failure(__FILE__, __func__, __LINE__);

	axxia_display_clocks();

#ifdef CONFIG_SPL_MTEST
	printf("Running the SPL Memory Test\n");
	if (spl_mtest((unsigned long *)0x40000000,
		      (unsigned long *)0x7fffffff, 10, all)) {
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

#ifdef CONFIG_HW_WATCHDOG
	rc = start_watchdog();

	if (0 == rc)
		puts("Started Watchdog Timer\n");
	else
		puts("Failed to start watchdog timer!\n");
#endif

#ifdef CONFIG_SPL_ENV_SUPPORT
	mem_malloc_init((0x40000000 + CONFIG_SYS_MALLOC_BASE),
			CONFIG_SYS_MALLOC_SIZE);
	env_init();
	env_relocate();
#endif

#endif
}

void spl_spi_load_image(void)
{
	struct spi_flash *flash;
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

	/* Load u-boot, mkimage header is 64 bytes. */
	spi_flash_read(flash, CONFIG_SYS_SPI_U_BOOT_OFFS, 0x40, &header);
	spl_parse_image_header(&header);
	/* Need offset as SDRAM is virtually mapped to 0x40000000 */
	spl_image.load_addr = 0x40000000;
	spi_flash_read(flash, CONFIG_SYS_SPI_U_BOOT_OFFS,
		       spl_image.size, (void *)spl_image.load_addr);

#ifndef CONFIG_AXXIA_EMU
	if (0 != sbb_verify_image(0x00000000, 0x00000000, 0))
		acp_failure(__FILE__, __func__, __LINE__);
#endif
}

void
jump_to_image_no_args(struct spl_image_info *spl_image)
{
	reset_cpu_fabric();
	acp_failure(__FILE__, __func__, __LINE__);
}
