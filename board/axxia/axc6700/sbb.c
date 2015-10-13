/*
 * sbb.c
 *
 * Interface to the SBB (Secure Boot Block)
 *
 * Copyright (C) 2014 LSI Corporation
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

#include <config.h>
#include <common.h>
#include <asm/io.h>

/*
  ==============================================================================
  ==============================================================================
  Local
  ==============================================================================
  ==============================================================================
*/

#define SBB_BASE        (0x8032910000)

/*
  ------------------------------------------------------------------------------
  lock_sbb
*/

static int
lock_sbb(void)
{
	unsigned long value;

	value = readl(SBB_BASE + 0x800);

	if (0 == value)
		return -1;

	return 0;
}

/*
  ------------------------------------------------------------------------------
  unlock_sbb
*/

static void
unlock_sbb(void)
{
	writel(0xffffffff, (SBB_BASE + 0x800));
}

/*
  ------------------------------------------------------------------------------
  report_errors

  For X9/XLF, and error would be indicated by any of the bits 0x06a4f7a8
  being set.
*/

static int
report_errors(unsigned long sbb_interrupt_status, int verbose)
{
	int rc = 0;

	/*
	  In all other cases, display the error string(s).
	*/

	if (0 != (sbb_interrupt_status & (1 << 3))) {
		if (0 != verbose)
			printf("SBB Error: Invalid SBKEK\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & (1 << 5))) {
		if (0 != verbose)
			printf("SBB Error: Secure Boot is Disabled\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & (1 << 7))) {
		if (0 != verbose)
			printf("SBB Error: Invalid Object ID\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & (1 << 8))) {
		if (0 != verbose)
			printf("SBB Error: Invalid Length\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & (1 << 9))) {
		if (0 != verbose)
			printf("SBB Error: Invalid Padding\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & (1 << 10))) {
		if (0 != verbose)
			printf("SBB Error: Unaligned Data\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & (1 << 12))) {
		if (0 != verbose)
			printf("SBB Error: Invalid Boot Image\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & (1 << 13))) {
		if (0 != verbose)
			printf("SBB Error: ECDSA initialization failed\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & (1 << 14))) {
		if (0 != verbose)
			printf("SBB Error: Invalid Version Number\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & (1 << 15))) {
		if (0 != verbose)
			printf("SBB Error: Unaligned Address\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & (1 << 18))) {
		if (0 != verbose)
			printf("SBB Error: Invalid Key ID\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & (1 << 21))) {
		if (0 != verbose)
			printf("SBB Error: Invalid Key\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & (1 << 23))) {
		if (0 != verbose)
			printf("SBB Error: Invalid KAKPUB\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & (1 << 25))) {
		if (0 != verbose)
			printf("SBB Error: Invalid Key Type\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & (1 << 26))) {
		if (0 != verbose)
			printf("SBB Error: Expired Key\n");

		rc = -1;
	}

	return rc;
}

/*
  ------------------------------------------------------------------------------
  run_sbb_function
*/

static int
run_sbb_function(int function,
		 unsigned long *parameters, int number_of_parameters,
		 int verbose)
{
	int i;
	unsigned long value;
	int sbb_enabled;

	/* Make sure SBB is enabled. */
	sbb_enabled = is_sbb_enabled(verbose);

	if (-1 == sbb_enabled || 0 == sbb_enabled)
		return -1;

	/* Get the semaphore. */
	if (0 != lock_sbb())
		return -1;

	/* Write the input parameters. */
	for (i = 0; i < number_of_parameters; ++i) {
		writel(parameters[i], (SBB_BASE + 0x838 + (i * 4)));
	}

	/* Clear the interrupt status registers. */
	writel(0xffffffff, (SBB_BASE + 0xe04));

	/* Write the function. */
	writel(function, (SBB_BASE + 0x804));

	if (function != readl(SBB_BASE + 0x804))
		return -1;

	/* Wait for the "done" bit. */
	value = readl(SBB_BASE + 0xe04);

	while (0 == (value & 1)) {
		udelay(1000);

		if (ctrlc()) {
			unlock_sbb();
			return -1;
		}

		value = readl(SBB_BASE + 0xe04);
	}

	/* Release the semaphore. */
	unlock_sbb();

	/* Check for errors. */
	if (0 != report_errors(value, verbose))
		return -1;

	return 0;
}

/*
  ==============================================================================
  ==============================================================================
  Public
  ==============================================================================
  ==============================================================================
*/

/*
  ------------------------------------------------------------------------------
  is_sbb_enabled

  Returns 1 if enabled, 0 if not, -1 if errror.
*/

int
is_sbb_enabled(int verbose)
{
	if (0 == (pfuse & (1 << 13))) {
		if (0 != verbose)
			printf("Secure Boot Disabled\n");

		return 0;
	}

	if (0 != verbose)
		printf("Secure Boot Enabled\n");

	return 1;
}

/*
  ------------------------------------------------------------------------------
  sbb_verify_image
*/

int
sbb_verify_image(void *source, void *destination,
		 int safe, int invalidate, int verbose)
{
	unsigned long parameters[4];
	int sbb_enabled;

	/* If SBB is disabled, return success */
	sbb_enabled = is_sbb_enabled(verbose);

	if (1 != sbb_enabled)
		return sbb_enabled;

	/* Set up the parameters. */
	parameters[0] = 0;
	parameters[1] = (unsigned long)source;
	parameters[2] = 0;
	parameters[3] = (unsigned long)destination;

	/* Run the function. */
	if (0 != run_sbb_function((0 == safe) ? 1 : 11,
				  parameters, 4, verbose)) {
		if (0 != invalidate)
			memset((void *)destination, 0, 16);

		return -1;
	}

	if (0 != verbose)
		printf("SBB: Image Verification Successful\n");

	return 0;
}
