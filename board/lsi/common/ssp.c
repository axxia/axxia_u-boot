/*
 * board/lsi/common/ssp.c
 *
 * Simple driver for the SSP controller in LSI's Axxia (ARM PL022).
 *
 * Copyright (C) 2009-2013 LSI Corporation
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

/*
  ==============================================================================
  ==============================================================================
  Private
  ==============================================================================
  ==============================================================================
*/

#include <config.h>
#include <common.h>
#include <exports.h>
#include <asm/io.h>

#define LARGE_ADDRESS_SIZE 1

static int device = -1;

/*
  ------------------------------------------------------------------------------
  ssp_failure
*/

static int
ssp_failure(const char *file, const char *function, const int line)
{
	printf("ERROR: %s, %s, %d\n", file, function, line);

	return -1;
}

#define SSP_FAILURE() ssp_failure(__FILE__, __FUNCTION__, __LINE__)

/*
  ------------------------------------------------------------------------------
  ssp_select_device
*/

static void
ssp_select_device(void)
{
	writel((0x1f &~ (1 << device)), (unsigned long *)(SSP + SSP_CSR));
}

/*
  ----------------------------------------------------------------------
  ssp_deselect_all
*/

static void
ssp_deselect_all(void)
{
	writel(0x1f, (unsigned long *)(SSP + SSP_CSR));
}

/*
  ----------------------------------------------------------------------
  ssp_write_device
*/

static int
ssp_write_device(unsigned short input, unsigned char *output)
{
	int retries = 10000;
	unsigned long value;

	/* Send the command to the device. */
	writel(input, (unsigned long *)(SSP + SSP_DR));

	/* Get the response from the receive buffer. */
	while (0 == (readl((unsigned long *)(SSP + SSP_SR)) & 4) &&
	       0 < --retries)
		;

	if (0 == retries)
		return SSP_FAILURE();

	value = readl((unsigned long *)(SSP + SSP_DR));

	if (NULL != output)
		*output = (unsigned char)(value & 0xff);

	return 0;
}

/*
  ======================================================================
  ======================================================================
  Public
  ======================================================================
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  ssp_read
*/

int
ssp_read(void *buffer, unsigned long offset, unsigned long length)
{
	int rc;
	unsigned char *output = (unsigned char *)buffer;

	ssp_select_device();
	rc = ssp_write_device(3, NULL);

#ifdef LARGE_ADDRESS_SIZE
	rc |= ssp_write_device((offset & 0x00ff0000) >> 16, NULL);
	rc |= ssp_write_device((offset & 0x0000ff00) >> 8, NULL);
	rc |= ssp_write_device(offset & 0x000000ff, NULL);
#else
	rc |= ssp_write_device((offset & 0x10000) >> 16, NULL);
	rc |= ssp_write_device((offset & 0xff00 ) >> 8, NULL);
	rc |= ssp_write_device(offset & 0xff, NULL);
#endif

	while (0 == rc &&
	       0 < length--) {
		unsigned char value;

		rc |= ssp_write_device(0, &value);
		*output++ = value;
	}

	ssp_deselect_all();

	if (0 != rc)
		return SSP_FAILURE();

	return 0;
}

/*
  ------------------------------------------------------------------------------
  ssp_set_speed
*/

int
ssp_set_speed(unsigned long *new_speed)
{
	unsigned long input_clock;
	unsigned long output_clock;
	unsigned long scr;
	unsigned long cpsdvsr;

	if (SSP_MAXIMUM_CLOCK < *new_speed) {
		printf("ssp: Requested speed (%lu) is greater than the maximum "
		       "speed (%lu).\n"
		       "     Setting speed to maximum.\n",
		       *new_speed, SSP_MAXIMUM_CLOCK);
		*new_speed = SSP_MAXIMUM_CLOCK;
	}

	if (0 != acp_clock_get(clock_peripheral, &input_clock))
		return -1;	/* Input clock not available. */

	input_clock *= 1000;

#if !defined(CONFIG_AXXIA_25xx) && \
  !defined(CONFIG_AXXIA_55xx_EMU) && \
  !defined(CONFIG_AXXIA_55xx)
	/*
	  Set up timer 0.
	*/

	writel(0, (unsigned long *)(TIMER0 + TIMER_CONTROL));
	writel(1, (unsigned long *)(TIMER0 + TIMER_LOAD));
	writel(0xc0, (unsigned long *)(TIMER0 + TIMER_CONTROL));
#endif

	/*
	  Output Clock is Input Clock divided by CPSDVSR (in the
	  SSPCPSR register, incorrectly called CPSDVR in the
	  description of SSPCR0) multiplied by the SCR plus 1.

	  Output Clock = Input Clock / (CPSDVSR * (1 + SCR))

	  Calculate the closest output clock available.
	*/

	output_clock = input_clock / *new_speed;

	/*
	  cpsdvsr must be even, and between 2 and 254.
	  scr must be between 0 and 255.
	*/

	cpsdvsr = output_clock / 1;
	cpsdvsr &= ~1;

	if (2 > cpsdvsr)
		cpsdvsr = 2;

	scr = output_clock / cpsdvsr;

	if (0 < scr)
		--scr;

	if (255 < scr)
		scr = 255;

	output_clock = input_clock / (cpsdvsr * (1 + scr));
	*new_speed = output_clock;

	/*
	  Set up the SSP.
	*/

	writel(((scr << 16) | 0x07), (unsigned long *)(SSP + SSP_CR0));
	writel(cpsdvsr, (unsigned long *)(SSP + SSP_CPSR));
	writel(2, (unsigned long *)(SSP + SSP_CR1));
	writel(0x1f, (unsigned long *)(SSP + SSP_CSR));

	return 0;
}

/*
  ------------------------------------------------------------------------------
  ssp_init
*/

int
ssp_init(int input_device)
{
	unsigned long ssp_speed = SSP_DEFAULT_CLOCK;

	device = input_device;

	if (0 != ssp_set_speed(&ssp_speed))
		return -1;

	/*
	  Clear out the SSP fifo.
	*/

	for (;;) {
		unsigned long status;

		status = readl(SSP + SSP_SR);

		if (3 == status)
			break;

		(void)readl(SSP + SSP_DR);
	}

	return 0;
}
