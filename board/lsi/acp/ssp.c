/*
 * ssp.c
 *
 * Simple driver for the SSP controller in LSI's ACP.
 *
 * Copyright (C) 2009 LSI Corporation
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

/*#define LSI_LOGIO*/
#include <config.h>

#include <common.h>

#define SECTOR_SIZE 0x10000 

static int device = -1;
static int read_only = -1;
static int is_flash = -1;

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
	WRITEL((0x1f &~ (1 << device)), (unsigned long *)(SSP + SSP_CSR));
}

/*
  ----------------------------------------------------------------------
  ssp_deselect_all
*/

static void
ssp_deselect_all(void)
{
	WRITEL(0x1f, (unsigned long *)(SSP + SSP_CSR));
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
	WRITEL(input, (unsigned long *)(SSP + SSP_DR));

	/* Get the response from the receive buffer. */
	while (0 == (READL((unsigned long *)(SSP + SSP_SR)) & 4) &&
	       0 < --retries)
		;

	if (0 == retries)
		return SSP_FAILURE();

	value = READL((unsigned long *)(SSP + SSP_DR));

	if (NULL != output)
		*output = (unsigned char)(value & 0xff);

	return 0;
}

/*
  ----------------------------------------------------------------------
  read_status
*/

static int
read_status(unsigned char *status)
{
	int rc;

	ssp_select_device();
	rc = ssp_write_device(5, NULL);
	rc |= ssp_write_device(0, status);
	ssp_deselect_all();

	return rc;
}

/*
  ----------------------------------------------------------------------
  write_enable
*/

static int
write_enable(void)
{
	int rc;

	ssp_select_device();
	rc = ssp_write_device(6, NULL);
	ssp_deselect_all();

	return rc;
}

/*
  ----------------------------------------------------------------------
  write_disable
*/

static int
write_disable(void)
{
	int rc;

	ssp_select_device();
	rc = ssp_write_device(4, NULL);
	ssp_deselect_all();

	return rc;
}

/*
  ------------------------------------------------------------------------------
  ssp_internal_write
*/

static int
ssp_internal_write(void *buffer, unsigned long offset, unsigned long length)
{
	int rc;
	unsigned char *input = (unsigned char *)buffer;
	int reenable_logio = 0;

	if (LSI_LOGIO_ENABLED()) {
		printf("Writing 0x%lx bytes to offset 0x%lx\n", length, offset);
		reenable_logio = 1;
		LSI_LOGIO_DISABLE();
	}

	while (0 < length) {
		int this_write;
		int this_written = 0;

		write_enable();
		ssp_select_device();
		rc |= ssp_write_device(2, NULL);

#if defined(CONFIG_LSI_SERIAL_FLASH)
		if (0 != is_flash) {
			rc |= ssp_write_device((offset & 0x00ff0000) >> 16,
					       NULL);
			rc |= ssp_write_device((offset & 0x0000ff00) >> 8, NULL);
			rc |= ssp_write_device(offset & 0x000000ff, NULL);
		} else {
#else
			rc |= ssp_write_device((offset & 0x10000) >> 16, NULL);
			rc |= ssp_write_device((offset & 0xff00 ) >> 8, NULL);
			rc |= ssp_write_device(offset & 0xff, NULL);
#endif
#if defined(CONFIG_LSI_SERIAL_FLASH)
		}
#endif

		this_write = 256 - ( offset % 256 );

		while (0 == rc &&
		       this_written < this_write &&
		       0 < length) {
			rc |= ssp_write_device(*input++, NULL);
			++this_written;
			--length;
			++offset;
		}

		if (0 != rc)
			return SSP_FAILURE();

		ssp_deselect_all();

		if (1 == is_flash) {
			int retries = 700;
			unsigned char status;

			do {
				udelay(10);
				rc |= read_status(&status);
			} while (0 == rc &&
				 0 < --retries &&
				 0 != (status & 1));

			if (0 != rc)
				return SSP_FAILURE();

			if (0 == retries)
				return SSP_FAILURE();
		} else {
			udelay( 5000 );	/* TODO: Why the delay? */
		}
	}

	if (0 != reenable_logio) {
		printf("Write completed.\n");
		LSI_LOGIO_ENABLE();
	}

	return 0;
}

#if defined(CONFIG_LSI_SERIAL_FLASH)

/*
  ------------------------------------------------------------------------------
  serial_flash_sector_erase
*/

static int
serial_flash_sector_erase(unsigned long offset)
{
	int rc;
	int retries = 1000000;
	unsigned long sector_offset;
	unsigned char status;

	sector_offset = (offset / SECTOR_SIZE) * SECTOR_SIZE;

	write_enable();
	ssp_select_device();
	rc = ssp_write_device(0xd8, NULL);
	rc |= ssp_write_device((sector_offset & 0x00ff0000) >> 16, NULL);
	rc |= ssp_write_device((sector_offset & 0x0000ff00 ) >> 8, NULL);
	rc |= ssp_write_device(sector_offset & 0x000000ff, NULL);
	ssp_deselect_all();

	do {
		rc |= read_status(&status);
	} while (0 == rc &&
		 0 != (status & 1) &&
		 0 < --retries);

	if (0 != rc || 0 == retries)
		return SSP_FAILURE();

	return 0;
}

/*
  ------------------------------------------------------------------------------
  serial_flash_erase
*/

static int
serial_flash_erase(unsigned long offset, unsigned long length)
{
	int rc = 0;
	void *buffer;

	/*
	  Handle offset not on a sector boundary.
	*/

	if (0 != offset % SECTOR_SIZE) {
		unsigned long sector_offset;
		void *buffer;

		sector_offset = (offset / SECTOR_SIZE) * SECTOR_SIZE;
		buffer = malloc(SECTOR_SIZE);

		if (NULL == buffer)
			return SSP_FAILURE();

		rc = ssp_read(buffer, sector_offset, SECTOR_SIZE);
		rc |= serial_flash_sector_erase(sector_offset);
		rc |= ssp_internal_write(buffer, sector_offset,
					 offset % SECTOR_SIZE);
		free(buffer);

		if (0 != rc)
			return SSP_FAILURE();

		length -= SECTOR_SIZE - (offset % SECTOR_SIZE);
		offset += SECTOR_SIZE - (offset % SECTOR_SIZE);
	}

	/*
	  Sectors to be fully erased.
	*/

	while (0 == rc &&
	       SECTOR_SIZE <= length) {
		rc |= serial_flash_sector_erase(offset);
		offset += SECTOR_SIZE;
		length -= SECTOR_SIZE;
	}

	if (0 != rc)
		return SSP_FAILURE();

	/*
	  Handle erasing a partial sector.
	*/

	if (0 != length) {
		unsigned long sector_offset;
		void *buffer;

		sector_offset = (offset / SECTOR_SIZE) * SECTOR_SIZE;
		buffer = malloc(SECTOR_SIZE);

		if (NULL == buffer)
			return SSP_FAILURE();

		rc = ssp_read(buffer, sector_offset, SECTOR_SIZE);
		rc |= serial_flash_sector_erase(sector_offset);
		rc |= ssp_internal_write((buffer + length),
					 (sector_offset + length),
					 SECTOR_SIZE - length);
		free(buffer);

		if (0 != rc)
			return SSP_FAILURE();
	}

	return 0;
}

#endif /* defined(CONFIG_LSI_SERIAL_FLASH) */

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
	int reenable_logio = 0;

	if (LSI_LOGIO_ENABLED()) {
		printf("Reading 0x%lx bytes from offset 0x%lx\n",
		       length, offset);
		reenable_logio = 1;
		LSI_LOGIO_DISABLE();
	}

	ssp_select_device();
	rc = ssp_write_device(3, NULL);

#if defined(CONFIG_LSI_SERIAL_FLASH)
	if (0 != is_flash) {
		rc |= ssp_write_device((offset & 0x00ff0000) >> 16, NULL);
		rc |= ssp_write_device((offset & 0x0000ff00) >> 8, NULL);
		rc |= ssp_write_device(offset & 0x000000ff, NULL);
	} else {
#else
		rc |= ssp_write_device((offset & 0x10000) >> 16, NULL);
		rc |= ssp_write_device((offset & 0xff00 ) >> 8, NULL);
		rc |= ssp_write_device(offset & 0xff, NULL);
#endif
#if defined(CONFIG_LSI_SERIAL_FLASH)
	}
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

	if (0 != reenable_logio) {
		printf("Read completed.\n");
		LSI_LOGIO_ENABLE();
	}

	return 0;
}

/*
  ----------------------------------------------------------------------
  ssp_write
*/

int
ssp_write(void *buffer, unsigned long offset, unsigned long length, int verify)
{
	int rc = 0;
	unsigned char *input = (unsigned char *)buffer;
	unsigned char *vinput = (unsigned char *)buffer;
	unsigned long voffset = offset;
	unsigned long vlength = length;

	/*
	  If this is serial flash, erase first.
	*/

	if (1 == is_flash) {
		rc = serial_flash_erase(offset, length);

		if (0 != rc)
			return SSP_FAILURE();
	}
	
	rc = ssp_internal_write(buffer, offset, length);

	if (0 != rc)
		return SSP_FAILURE();

	/*
	  If requested, verify.
	*/

	if (0 != verify) {
		ssp_select_device();
		rc = ssp_write_device(3, NULL);

#if defined(CONFIG_LSI_SERIAL_FLASH)
		if (0 != is_flash) {
			rc |= ssp_write_device((voffset & 0x00ff0000) >> 16,
					       NULL);
			rc |= ssp_write_device((voffset & 0x0000ff00) >> 8,
					       NULL);
			rc |= ssp_write_device(voffset & 0x000000ff,
					       NULL);
		} else {
#else
			rc |= ssp_write_device((voffset & 0x10000) >> 16, NULL);
			rc |= ssp_write_device((voffset & 0xff00 ) >> 8, NULL);
			rc |= ssp_write_device(voffset & 0xff, NULL);
#endif
#if defined(CONFIG_LSI_SERIAL_FLASH)
		}
#endif

		while (0 == rc &&
		       0 < vlength--) {
			unsigned char value;

			rc |= ssp_write_device(0, &value);

			if (0 != rc ||
			    *vinput++ != value)
				return SSP_FAILURE();
		}

		ssp_deselect_all();
	}

	return 0;
}

/*
  ----------------------------------------------------------------------
  ssp_init
*/

int
ssp_init(int input_device, int input_read_only)
{
#if defined(CONFIG_LSI_SERIAL_FLASH)
	int rc;
	int i;
	unsigned char value[3];
#endif
	int reenable_logio = 0;

	device = input_device;

	WRITEL(0x3107, (unsigned long *)(SSP + SSP_CR0));
	WRITEL(2, (unsigned long *)(SSP + SSP_CR1));
	WRITEL(2, (unsigned long *)(SSP + SSP_CPSR));
	WRITEL(0x1f, (unsigned long *)(SSP + SSP_CSR));

	if (0 != input_read_only) {
		read_only = 1;
		return 0;
	}

	read_only = 0;

#if defined(CONFIG_LSI_SERIAL_FLASH)
	/*
	  In order to write, decide if this is EEPROM or serial flash.
	*/

	if (LSI_LOGIO_ENABLED()) {
		reenable_logio = 1;
		LSI_LOGIO_DISABLE();
	}

	ssp_select_device();
	rc = ssp_write_device(0x9f, NULL);

	/* Skip the manufacturer bytes. */
	for (i = 0; i < 16; ++i)
		rc |= ssp_write_device(0, NULL);

	/* Check for 'Q', 'R', and 'Y' at the beginning of identification. */
	rc |= ssp_write_device(0, &value[0]);
	rc |= ssp_write_device(0, &value[1]);
	rc |= ssp_write_device(0, &value[2]);

	ssp_deselect_all();

	if (0 != reenable_logio) {
		LSI_LOGIO_ENABLE();
	}

	if (0 != rc)
		return SSP_FAILURE();

	if ('Q' == value[0] && 'R' == value[1] && 'Y' == value[2])
		is_flash = 1;
	else
		is_flash = 0;

	if (0 != is_flash)
		WRITEL(0x907, (unsigned long *)(SSP + SSP_CR0));
#endif


	return 0;
}
