/*
 * board/lsi/common/spi_flash.c
 *
 * Simple driver for serial SPI Flash.
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
#include <config.h>
#include <common.h>
#include <exports.h>
#include <asm/sizes.h>
#include <spi.h>

#define SECTOR_SIZE   SZ_64K

static struct spi_slave *flash;

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

static int
ssp_read_write(struct spi_slave *spi,
	       const u8 *cmd, size_t cmd_len,
	       const u8 *data_out, u8 *data_in,
	       size_t data_len)
{
	unsigned long flags = SPI_XFER_BEGIN;
	int ret;

	if (data_len == 0)
		flags |= SPI_XFER_END;

	ret = spi_xfer(spi, cmd_len * 8, cmd, NULL, flags);
	if (ret) {
		debug("spi_flash: Failed to send command (%zu bytes): %d\n", cmd_len, ret);
	} else if (data_len != 0) {
		ret = spi_xfer(spi, data_len * 8, data_out, data_in, SPI_XFER_END);
		if (ret)
			printf("spi_flash: Failed to xfr %zu bytes of data: %d\n", data_len, ret);
	}

	return ret;

}

static void
ssp_cmd_offset(u8 cmd, unsigned int offset, u8 *buf)
{
	buf[0] = cmd;
	buf[1] = (offset >> 16) & 0xff;
	buf[2] = (offset >>  8) & 0xff;
	buf[3] = (offset >>  0) & 0xff;
}

/*
  ----------------------------------------------------------------------
  read_status
*/

static int
read_status(unsigned char *status)
{
	u8 cmd = 0x05;
	return ssp_read_write(flash, &cmd, 1, NULL, status, 1);
}

/*
  ----------------------------------------------------------------------
  write_enable
 */

static int
write_enable(void)
{
	u8 cmd = 0x06;
	return ssp_read_write(flash, &cmd, 1, NULL, NULL, 0);
}

/*
  ------------------------------------------------------------------------------
  sector_erase
 */
static int
sector_erase(unsigned long offset)
{
	int rc;
	int retries = 1000000;
	unsigned long sector_offset;
	unsigned char status = 0;
	u8 cmd[4];

	sector_offset = (offset / SECTOR_SIZE) * SECTOR_SIZE;

	write_enable();

	ssp_cmd_offset(0xd8, sector_offset, cmd);
	ssp_read_write(flash, cmd, sizeof cmd, NULL, NULL, 0);

	do {
		rc = read_status(&status);
	} while (0 == rc && 0 != (status & 1) && 0 < --retries);

	if (0 != rc || 0 == retries)
		return SSP_FAILURE();

	return 0;
}

/*
  ------------------------------------------------------------------------------
  ssp_internal_write
*/

static int
ssp_internal_write(void *buffer, unsigned long offset, unsigned long length)
{
	u8 *out = (unsigned char *)buffer;
	int rc;

	write_enable();

	while (0 < length) {
		int chunk = 256 - (offset % 256);
		u8 cmd[4];
		int retries = 700;
		unsigned char status = 0;

		ssp_cmd_offset(0x02, offset, cmd);
		rc = ssp_read_write(flash, cmd, sizeof cmd, NULL, out, chunk);
		if (rc != 0)
			SSP_FAILURE();

		out += chunk;
		length -= chunk;
		offset += chunk;

		do {
			udelay(10);
			rc = read_status(&status);
		} while (0 == rc && 0 < --retries && 0 != (status & 1));

		if (0 != rc)
			return SSP_FAILURE();

		if (0 == retries)
			return SSP_FAILURE();
	}

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
		rc |= sector_erase(sector_offset);
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
	while (0 == rc && SECTOR_SIZE <= length) {
		rc |= sector_erase(offset);
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
		rc |= sector_erase(sector_offset);
		rc |= ssp_internal_write((buffer + length),
					 (sector_offset + length),
					 SECTOR_SIZE - length);
		free(buffer);

		if (0 != rc)
			return SSP_FAILURE();
	}

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
	u8 cmd[4];
	ssp_cmd_offset(0x03, offset, cmd);
	return ssp_read_write(flash, cmd, sizeof cmd, NULL, buffer, length);
}

/*
  ----------------------------------------------------------------------
  ssp_write
*/

int
ssp_write(void *buffer, unsigned long offset, unsigned long length, int verify)
{
	int rc = 0;

	rc = serial_flash_erase(offset, length);
	if (0 != rc)
		return SSP_FAILURE();
	
	rc = ssp_internal_write(buffer, offset, length);
	if (0 != rc)
		return SSP_FAILURE();

	return 0;
}

/*
  ------------------------------------------------------------------------------
  ssp_init
*/

int
ssp_init(int device, int input_read_only)
{
	u8 cmd_id = 0x9f;
	u8 devid[4];
	int rc;

	flash = spi_setup_slave(0, device, SSP_DEFAULT_CLOCK, 0);
	if (!flash)
		return -1;

	rc = spi_claim_bus(flash);
	if (rc < 0)
		return rc;

	memset(devid, 0, sizeof devid);

	rc = ssp_read_write(flash, &cmd_id, sizeof cmd_id, NULL, devid, sizeof devid);
	if (rc < 0)
		return rc;

	printf("ssp: Flash ID: %02x %02x %02x %02x\n",
	      devid[0], devid[1], devid[2], devid[3]);

	return 0;
}
