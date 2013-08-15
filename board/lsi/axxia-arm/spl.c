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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <common.h>
#include <asm/spl.h>

/*
  ==============================================================================
  ==============================================================================
  Local Stuff
  ==============================================================================
  ==============================================================================
*/

/*
  -------------------------------------------------------------------------------
  spl_mtest
*/

#ifdef CONFIG_SPL_MTEST

static void
spl_mtest(unsigned long *start, unsigned long *end)
{
	vu_long	*addr;
	ulong	val;
	ulong	readback;
	ulong	errs = 0;
	int iterations = 1;
	int iteration_limit;
	vu_long	len;
	vu_long	offset;
	vu_long	test_offset;
	vu_long	pattern;
	vu_long	temp;
	vu_long	anti_pattern;
	vu_long	num_words;
	vu_long *dummy = NULL;	/* yes, this is address 0x0, not NULL */
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
	iteration_limit = 0;

	printf ("Testing %08x ... %08x:\n", (uint)start, (uint)end);

	for (;;) {
		if (ctrlc()) {
			putc ('\n');
			return 1;
		}

		if (iteration_limit && iterations > iteration_limit) {
			printf("Tested %d iteration(s) with %lu errors.\n",
			       iterations-1, errs);
			return errs != 0;
		}

		printf("Iteration: %6d\r", iterations);
		debug("\n");
		iterations++;

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
		for (j = 0; j < sizeof(bitpattern)/sizeof(bitpattern[0]); j++) {
			val = bitpattern[j];
			for(; val != 0; val <<= 1) {
				*addr  = val;
				/* clear the test data off of the bus */
				*dummy  = ~val;
				readback = *addr;
				if(readback != val) {
					printf ("FAILURE (data line): "
						"expected %08lx, actual %08lx\n",
						val, readback);
					errs++;
					if (ctrlc()) {
						putc ('\n');
						return 1;
					}
				}
				*addr  = ~val;
				*dummy  = val;
				readback = *addr;
				if(readback != ~val) {
					printf ("FAILURE (data line): "
						"Is %08lx, should be %08lx\n",
						readback, ~val);
					errs++;
					if (ctrlc()) {
						putc ('\n');
						return 1;
					}
				}
			}
		}

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
		 *              memory region by performing a walking
		 *              1's test on the relevant bits of the
		 *              address and checking for aliasing.
		 *              This test will find single-bit
		 *              address failures such as stuck -high,
		 *              stuck-low, and shorted pins. The base
		 *              address and size of the region are
		 *              selected by the caller.
		 *
		 * Notes:	For best results, the selected base
		 *              address should have enough LSB 0's to
		 *              guarantee single address bit changes.
		 *              For example, to test a 64-Kbyte
		 *              region, select a base address on a
		 *              64-Kbyte boundary. Also, select the
		 *              region size as a power-of-two if at
		 *              all possible.
		 *
		 * Returns:     0 if the test succeeds, 1 if the test fails.
		 */
		len = ((ulong)end - (ulong)start)/sizeof(vu_long);
		pattern = (vu_long) 0xaaaaaaaa;
		anti_pattern = (vu_long) 0x55555555;

		debug("%s:%d: length = 0x%.8lx\n",
		      __FUNCTION__, __LINE__,
		      len);
		/*
		 * Write the default pattern at each of the
		 * power-of-two offsets.
		 */
		for (offset = 1; offset < len; offset <<= 1) {
			start[offset] = pattern;
		}

		/*
		 * Check for address bits stuck high.
		 */
		test_offset = 0;
		start[test_offset] = anti_pattern;

		for (offset = 1; offset < len; offset <<= 1) {
			temp = start[offset];
			if (temp != pattern) {
				printf ("\nFAILURE: Address bit stuck high "
					"@ 0x%.8lx:"
					" expected 0x%.8lx, actual 0x%.8lx\n",
					(ulong)&start[offset], pattern, temp);
				errs++;
				if (ctrlc()) {
					putc ('\n');
					return 1;
				}
			}
		}
		start[test_offset] = pattern;

		/*
		 * Check for addr bits stuck low or shorted.
		 */
		for (test_offset = 1; test_offset < len; test_offset <<= 1) {
			start[test_offset] = anti_pattern;

			for (offset = 1; offset < len; offset <<= 1) {
				temp = start[offset];
				if ((temp != pattern) &&
				    (offset != test_offset)) {
					printf ("\nFAILURE: Address bit stuck "
						"low or shorted @"
						" 0x%.8lx: expected 0x%.8lx, "
						"actual 0x%.8lx\n",
						(ulong)&start[offset], pattern,
						temp);
					errs++;
					if (ctrlc()) {
						putc ('\n');
						return 1;
					}
				}
			}
			start[test_offset] = pattern;
		}

		/*
		 * Description: Test the integrity of a physical
		 *		memory device by performing an
		 *		increment/decrement test over the
		 *		entire region. In the process every
		 *		storage bit in the device is tested
		 *		as a zero and a one. The base address
		 *		and the size of the region are
		 *		selected by the caller.
		 *
		 * Returns:     0 if the test succeeds, 1 if the test fails.
		 */
		num_words = ((ulong)end - (ulong)start)/sizeof(vu_long) + 1;

		/*
		 * Fill memory with a known pattern.
		 */
		for (pattern = 1, offset = 0; offset < num_words; pattern++,
			     offset++) {
			start[offset] = pattern;
		}

		/*
		 * Check each location and invert it for the second pass.
		 */
		for (pattern = 1, offset = 0; offset < num_words; pattern++,
			     offset++) {
			temp = start[offset];
			if (temp != pattern) {
				printf ("\nFAILURE (read/write) @ 0x%.8lx:"
					" expected 0x%.8lx, actual 0x%.8lx)\n",
					(ulong)&start[offset], pattern, temp);
				errs++;
				if (ctrlc()) {
					putc ('\n');
					return 1;
				}
			}

			anti_pattern = ~pattern;
			start[offset] = anti_pattern;
		}

		/*
		 * Check each location for the inverted pattern and zero it.
		 */
		for (pattern = 1, offset = 0; offset < num_words; pattern++,
			     offset++) {
			anti_pattern = ~pattern;
			temp = start[offset];
			if (temp != anti_pattern) {
				printf ("\nFAILURE (read/write): @ 0x%.8lx:"
					" expected 0x%.8lx, actual 0x%.8lx)\n",
					(ulong)&start[offset], anti_pattern,
					temp);
				errs++;
				if (ctrlc()) {
					putc ('\n');
					return 1;
				}
			}
			start[offset] = 0;
		}
	}
}

#endif

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
  -------------------------------------------------------------------------------
  check_memory_ranges
*/

static void
check_memory_ranges(void)
{
	unsigned long *ranges = &global->memory_check_ranges;
	int i;

	for (i = 0; i < 8; ++i) {
		unsigned long long offset = (unsigned long long)*ranges++;
		unsigned long long length = (unsigned long long)*ranges++;

		offset <<= 8;
		length <<= 8;

		if (0ULL != length) {
			printf("Testing Memory From 0x%llx, 0x%llx bytes\n",
			       offset, length);
			axxia_sysmem_bist(offset, length);
		}
	}
}

/*
  ------------------------------------------------------------------------------
  board_init_f

  This function is declared "void __weak" in arch/arm/lib/spl.c.  It's
  overridden here to handle the SPL boot on Axxia ARM systems.
*/

DECLARE_GLOBAL_DATA_PTR;
extern gd_t gdata;

void
board_init_f(ulong bootflag)
{
	int rc;

	/* Clear BSS */
	memset(__bss_start, 0, __bss_end__ - __bss_start);

	/* Set the global data pointer. */
	gd = &gdata;

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
		acp_failure(__FILE__, __FUNCTION__, __LINE__);

	axxia_display_clocks();

#ifdef CONFIG_SPL_MTEST
	printf("Running the SPL Memory Test, Ctrl-C to Continue\n");

	spl_mtest((unsigned long *)0x40000000,
		  (unsigned long *)0x7fffffff);
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

	if (0 != (global->flags & PARAMETERS_GLOBAL_DDR_RANGE_TEST))
		check_memory_ranges();

	printf("System initialized\n");
	ssp_init(0, 1);
	rc = ssp_read((void *)0x40000000, 0x100000, 0x200000);
	printf("U-Boot Copied\n");
	reset_cpu_fabric();
	acp_failure(__FILE__, __FUNCTION__, __LINE__);

#endif

	return;
}
