/*
 * board/lsi/common/parameters.c
 *
 * Inteface to access the parameter files.
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

/* #define DEBUG */
/* #define DISPLAY_PARAMETERS */

#include <config.h>
#include <common.h>
#include <spi.h>
#include <spi_flash.h>
#include <malloc.h>
#include <linux/ctype.h>

/*
  ==============================================================================
  ==============================================================================
  Private
  ==============================================================================
  ==============================================================================
*/

static void *parameters __attribute__ ((section("data")));
static int copy_in_use __attribute__ ((section("data")));
static int parameters_read __attribute__ ((section("data")));

#if defined(CONFIG_AXXIA_PPC)
/*
  For PPC (34xx, 25xx, 35xx), use version 4 of the parameters.
*/
#ifdef CONFIG_SPL_BUILD
#define PARAMETERS_HEADER_ADDRESS				\
	(LCM + (128 * 1024) - sizeof(parameters_header_t))
#define PARAMETERS_OFFSET ((128 * 1024) - PARAMETERS_SIZE)
#define PARAMETERS_ADDRESS (LCM + PARAMETERS_OFFSET)
#endif
#define PARAMETERS_SIZE (1024)
#define PARAMETERS_OFFSET_IN_FLASH PARAMETERS_OFFSET
#define PARAMETERS_VERSION 4
#elif defined(CONFIG_AXXIA_ARM)
/*
  For ARM (55xx), use version 9 of the parameters.
*/
#ifdef CONFIG_SPL_BUILD
#define PARAMETERS_HEADER_ADDRESS (LSM + (256 * 1024) - PARAMETERS_SIZE)
#define PARAMETERS_OFFSET ((256 * 1024) - PARAMETERS_SIZE)
#define PARAMETERS_ADDRESS (LSM + PARAMETERS_OFFSET)
#endif
#define PARAMETERS_SIZE (4096)
#define PARAMETERS_OFFSET_IN_FLASH 0x40000
#define PARAMETERS_VERSION 9
#else
#error "Unknown Architecture!"
#endif

parameters_header_t *header __attribute__ ((section("data"))) = NULL;
parameters_global_t *global __attribute__ ((section("data"))) = NULL;
parameters_pciesrio_t *pciesrio __attribute__ ((section("data"))) = NULL;
parameters_voltage_t *voltage __attribute__ ((section("data"))) = NULL;
parameters_clocks_t *clocks __attribute__ ((section("data"))) = NULL;
parameters_mem_t *sysmem __attribute__ ((section("data"))) = NULL;
parameters_mem_t *cmem __attribute__ ((section("data"))) = NULL;
#ifdef CONFIG_AXXIA_ARM
void *retention __attribute__ ((section("data"))) = NULL;
#endif

/*
  ------------------------------------------------------------------------------
  verify_parameters
*/

static int
verify_parameters(void *parameters, int quiet)
{
	parameters_header_t *lheader;

	lheader = parameters;

	/* Check for the magic number. */

	if (PARAMETERS_MAGIC != ntohl(lheader->magic)) {
		if (0 == quiet)
			printf("Parameter table has wrong magic number!\n");

		return -1;
	}

	/* Verify the checksum. */

	if (crc32(0, (parameters + 12), (ntohl(lheader->size) - 12)) !=
	    ntohl(lheader->checksum)) {
		if (0 == quiet)
			printf("Parameter table is corrupt. 0x%08x!=0x%08x\n",
			       ntohl(lheader->checksum),
			       crc32(0, (parameters + 12),
				     (ntohl(lheader->size) - 12)));

		return -1;
	}

	/* Check the version. */

	if (PARAMETERS_VERSION != ntohl(lheader->version)) {
		if (0 == quiet)
			printf("Parameter table should be version %d, not %lu!\n",
			       PARAMETERS_VERSION, lheader->version);

		return -1;
	}

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
  read_parameters
*/

int
read_parameters(void)
{
#ifdef CONFIG_AXXIA_ARM
	int i;
	unsigned *buffer;
	unsigned char *description;
#endif
	int rc;
	struct spi_flash *flash;

#ifdef CONFIG_SPL_BUILD
	parameters = (void *)PARAMETERS_ADDRESS;
#else
	parameters = malloc(PARAMETERS_SIZE);
	memset(parameters, 0, PARAMETERS_SIZE);
#endif

	header = parameters;

	/*
	  Try LSM first, to allow for board repair when the serial
	  EEPROM contains a valid but incorrect (unusable) parameter
	  table.
	*/

	/* Verify that the paramater table is valid. */
	if (0 == verify_parameters(parameters, 1)) {
		flash = spi_flash_probe(0, 0, CONFIG_SF_DEFAULT_SPEED,
					CONFIG_SF_DEFAULT_MODE);

		if (!flash)
			return -1;

		rc = spi_flash_erase(flash,
				     CONFIG_PARAMETER_OFFSET,
				     flash->sector_size);

		if (0 == rc) {
			rc = spi_flash_write(flash,
					     CONFIG_PARAMETER_OFFSET,
					     PARAMETERS_SIZE, parameters);

			if (0 != rc) {
				printf("%s:%d - Write Failed!\n",
				       __FILE__, __LINE__);

				return -1;
			}
		} else {
			printf("%s:%d - Erase Failed!\n", __FILE__, __LINE__);

			return -1;
		}

		rc = spi_flash_erase(flash,
				     CONFIG_PARAMETER_OFFSET_REDUND,
				     flash->sector_size);

		if (0 == rc) {
			rc = spi_flash_write(flash,
					     CONFIG_PARAMETER_OFFSET_REDUND,
					     PARAMETERS_SIZE, parameters);

			if (0 != rc) {
				printf("%s:%d - Write Failed!\n",
				       __FILE__, __LINE__);

				return -1;
			}
		} else {
			printf("%s:%d - Erase Failed!\n", __FILE__, __LINE__);

			return -1;
		}
	} else {
#ifdef CONFIG_REDUNDANT_PARAMETERS
		int watchdog_timeout;
		int a_valid;
		int b_valid;
		int a_sequence = 0;
		int b_sequence = 0;

		ncr_read32(NCP_REGION_ID(0x156, 0), 0xdc,
			   (ncp_uint32_t *)&watchdog_timeout);
		watchdog_timeout = ((watchdog_timeout & 0x4) >> 2);

		flash = spi_flash_probe(0, 0, CONFIG_SF_DEFAULT_SPEED,
					CONFIG_SF_DEFAULT_MODE);

		if (!flash)
			return -1;

		spi_flash_read(flash, CONFIG_PARAMETER_OFFSET,
			       PARAMETERS_SIZE, parameters);

		if (0 == verify_parameters(parameters, 0)) {
			a_valid = 1;
			buffer = parameters;

			for (i = 0; i < (PARAMETERS_SIZE / 4); ++i) {
				*buffer = ntohl(*buffer);
				++buffer;
			}

			global = (parameters_global_t *)
				(parameters + header->globalOffset);

			a_sequence = global->sequence;
		} else {
			a_valid = 0;
		}

		spi_flash_read(flash, CONFIG_PARAMETER_OFFSET_REDUND,
			       PARAMETERS_SIZE, parameters);

		if (0 == verify_parameters(parameters, 0)) {
			b_valid = 1;
			buffer = parameters;

			for (i = 0; i < (PARAMETERS_SIZE / 4); ++i) {
				*buffer = ntohl(*buffer);
				++buffer;
			}

			global = (parameters_global_t *)
				(parameters + header->globalOffset);

			b_sequence = global->sequence;
		} else {
			b_valid = 0;
		}

		if (0 == a_valid && 0 == b_valid) {
			acp_failure(__FILE__, __func__, __LINE__);
		} else if (0 == a_valid && 0 != b_valid) {
			copy_in_use = 1;
		} else if (0 != a_valid && 0 == b_valid) {
			copy_in_use = 0;
		} else {
			if (0xffffffff == a_sequence && b_sequence == 0)
				copy_in_use = 1;
			else if (b_sequence > a_sequence)
				copy_in_use = 1;
			else
				copy_in_use = 0;

			if (0 != watchdog_timeout)
				copy_in_use = (0 == copy_in_use) ? 1 : 0;
		}

		printf("Parameters: Watchdog %d A/B Valid %d/%d A/B Sequence %d/%d => %s\n",
		       watchdog_timeout, a_valid, b_valid,
		       a_sequence, b_sequence,
		       (0 == copy_in_use) ? "A" : "B");

		if (0 == copy_in_use)
			spi_flash_read(flash, CONFIG_PARAMETER_OFFSET,
				       PARAMETERS_SIZE, parameters);
		else
			spi_flash_read(flash, CONFIG_PARAMETER_OFFSET_REDUND,
				       PARAMETERS_SIZE, parameters);
#else  /* CONFIG_REDUNDANT_PARAMETERS */
		flash = spi_flash_probe(0, 0, CONFIG_SF_DEFAULT_SPEED,
					CONFIG_SF_DEFAULT_MODE);

		if (!flash)
			return -1;

		spi_flash_read(flash, CONFIG_PARAMETER_OFFSET,
			       PARAMETERS_SIZE, parameters);

		if (0 != verify_parameters(parameters, 0)) {
			printf("Primary Parameters Corrupt, using Backup!\n");

			/* Try the redunant copy. */
			spi_flash_read(flash, CONFIG_PARAMETER_OFFSET_REDUND,
				       PARAMETERS_SIZE, parameters);

			if (0 != verify_parameters(parameters, 0)) {
				printf("Backup Parameters Corrupt!\n");

				return -1;
			}

			copy_in_use = 1;
		} else {
			copy_in_use = 0;
		}
#endif	/* CONFIG_REDUNDANT_PARAMETERS */
	}

	parameters_read = 1;

#ifdef CONFIG_AXXIA_ARM
	buffer = parameters;

	for (i = 0; i < (PARAMETERS_SIZE / 4); ++i) {
		*buffer = ntohl(*buffer);
		++buffer;
	}
#endif

#ifdef DISPLAY_PARAMETERS
	printf("-- -- Header\n"
	       "0x%08lx 0x%08lx 0x%08lx 0x%08lx 0x%08lx\n"
	       "0x%08lx 0x%08lx\n"
	       "0x%08lx 0x%08lx\n"
	       "0x%08lx 0x%08lx\n"
	       "0x%08lx 0x%08lx\n"
	       "0x%08lx 0x%08lx\n"
	       "0x%08lx 0x%08lx\n"
	       "0x%08lx 0x%08lx\n",
	       header->magic, header->size, header->checksum, header->version,
	       header->chipType,
	       header->globalOffset, header->globalSize,
	       header->voltageOffset, header->voltageSize,
	       header->clocksOffset, header->clocksSize,
	       header->pciesrioOffset, header->pciesrioSize,
	       header->systemMemoryOffset, header->systemMemorySize,
	       header->classifierMemoryOffset, header->classifierMemorySize,
	       header->systemMemoryRetentionOffset,
	       header->systemMemoryRetentionSize);
#endif

	global = (parameters_global_t *)(parameters + header->globalOffset);
	pciesrio = (parameters_pciesrio_t *)
		(parameters + header->pciesrioOffset);
	voltage = (parameters_voltage_t *)(parameters + header->voltageOffset);
	clocks = (parameters_clocks_t *)(parameters + header->clocksOffset);
	sysmem = (parameters_mem_t *)(parameters + header->systemMemoryOffset);
#ifdef CONFIG_AXXIA_ARM
	retention = (void *)(parameters + header->systemMemoryRetentionOffset);
#endif

#ifdef DISPLAY_PARAMETERS
	printf("version=%u flags=0x%x\n", global->version, global->flags);
#endif

	printf("Parameter Table Version: %lu\n", header->version);

	description = (unsigned char *)&global->description[0];

	if (0 != *description && isprint(*description)) {
		i = 0;
		puts("            Description: ");

		while (0 != *description && isprint(*description) && i++ < 128)
			putc(*description++);

		puts("\n");
	}

	return 0;
}

#ifdef CONFIG_MEMORY_RETENTION

/*
  ------------------------------------------------------------------------------
  write_parameters
*/

int
write_parameters(void)
{
#ifdef CONFIG_AXXIA_ARM
	struct spi_flash *flash = NULL;
	void *compare = NULL;
	unsigned *buffer;
	int i;
	int rc = -1;

	if (0 == parameters_read) {
		printf("Parameters haven't been read!\n");
		return -1;
	}

	compare = malloc(PARAMETERS_SIZE);

	if (NULL == compare) {
		printf("%s:%d - Couldn't Allocate Memory!\n",
		       __FILE__, __LINE__);
		goto release_and_return;
	}

	flash = spi_flash_probe(0, 0,
				CONFIG_SF_DEFAULT_SPEED,
				CONFIG_SF_DEFAULT_MODE);

	if (NULL == flash) {
		printf("%s:%d - SF Probe Failed!\n", __FILE__, __LINE__);
		goto release_and_return;
	}

	rc = spi_flash_read(flash,
			    (0 == copy_in_use) ?
			    CONFIG_PARAMETER_OFFSET :
			    CONFIG_PARAMETER_OFFSET_REDUND,
			    PARAMETERS_SIZE, compare);

	if (rc) {
		printf("%s:%d - Error reading Serial Flash!\n",
		       __FILE__, __LINE__);
		goto release_and_return;
	}

#ifdef CONFIG_AXXIA_ARM
	buffer = compare;

	for (i = 0; i < (PARAMETERS_SIZE / 4); ++i) {
		*buffer = ntohl(*buffer);
		++buffer;
	}
#endif

	rc = memcmp(compare, parameters, PARAMETERS_SIZE);
	debug("%s:%d - rc=%d\n", __FILE__, __LINE__, rc);

#ifdef DEBUG
	{
		unsigned *a = parameters;
		unsigned *b = compare;

		printf("compare is at 0x%p\n"
		       "parameters are at 0x%p\n",
		       compare, parameters);

		printf("-- Offset --\n"
		       "     global = 0x%lx\n"
		       "   pciesrio = 0x%lx\n"
		       "    voltage = 0x%lx\n"
		       "     clocks = 0x%lx\n"
		       "     sysmem = 0x%lx\n"
		       "       cmem = 0x%lx\n"
		       "  retention = 0x%lx\n",
		       header->globalOffset,
		       header->pciesrioOffset,
		       header->voltageOffset,
		       header->clocksOffset,
		       header->systemMemoryOffset,
		       header->classifierMemoryOffset,
		       header->systemMemoryRetentionOffset);

		for (i = 0; i < (PARAMETERS_SIZE / 4); ++i) {

			if (*a != *b) {
				printf("MISMATCH at 0x%04x: 0x%08x != 0x%08x\n",
				       (i * 4), *a, *b);
			}

			++a;
			++b;
		}
	}
#endif

	if (0 == rc)
		goto release_and_return;

#ifdef CONFIG_AXXIA_ARM
	buffer = parameters;

	for (i = 0; i < (PARAMETERS_SIZE / 4); ++i) {
		*buffer = htonl(*buffer);
		++buffer;
	}
#endif

	/* Update the Checksum */
	debug("%s:%d - header->size=0x%lx header->checksum=0x%lx\n",
	      __FILE__, __LINE__, header->size, header->checksum);
	header->checksum =
		htonl(crc32(0, (parameters + 12),
			    (ntohl(header->size) - 12)));
	debug("%s:%d - header->checksum=0x%lx\n",
	      __FILE__, __LINE__, header->checksum);

#ifdef CONFIG_REDUNDANT_PARAMETERS
	/* Write the DDR Parameters */
	rc = spi_flash_erase(flash,
			     (0 == copy_in_use) ?
			     CONFIG_PARAMETER_OFFSET :
			     CONFIG_PARAMETER_OFFSET_REDUND,
			     flash->sector_size);

	if (0 == rc) {
		debug("Writing...\n");
		rc = spi_flash_write(flash,
				     (0 == copy_in_use) ?
				     CONFIG_PARAMETER_OFFSET :
				     CONFIG_PARAMETER_OFFSET_REDUND,
				     PARAMETERS_SIZE, parameters);
	} else {
		printf("%s:%d - Erase Failed!\n", __FILE__, __LINE__);
		return -1;
	}
#else  /* CONFIG_REDUNDANT_PARAMETERS */
	/* Write to the copy NOT in use first. */
	debug("Erasing...\n");
	rc = spi_flash_erase(flash,
			     (0 == copy_in_use) ?
			     CONFIG_PARAMETER_OFFSET_REDUND :
			     CONFIG_PARAMETER_OFFSET,
			     flash->sector_size);

	if (0 == rc) {
		debug("Writing...\n");
		rc = spi_flash_write(flash,
				     (0 == copy_in_use) ?
				     CONFIG_PARAMETER_OFFSET_REDUND :
				     CONFIG_PARAMETER_OFFSET,
				     PARAMETERS_SIZE, parameters);
	} else {
		printf("%s:%d - Erase Failed!\n", __FILE__, __LINE__);
		return -1;
	}

	/* Once that's done, update the other copy. */
	debug("Erasing...\n");
	rc = spi_flash_erase(flash,
			     (0 == copy_in_use) ?
			     CONFIG_PARAMETER_OFFSET :
			     CONFIG_PARAMETER_OFFSET_REDUND,
			     flash->sector_size);

	if (0 == rc) {
		debug("Writing...\n");
		rc = spi_flash_write(flash,
				     (0 == copy_in_use) ?
				     CONFIG_PARAMETER_OFFSET :
				     CONFIG_PARAMETER_OFFSET_REDUND,
				     PARAMETERS_SIZE, parameters);
	} else {
		printf("%s:%d - Erase Failed!\n", __FILE__, __LINE__);
		return -1;
	}
#endif	/* CONFIG_REDUNDANT_PARAMETERS */

#ifdef CONFIG_AXXIA_ARM
	buffer = parameters;

	for (i = 0; i < (PARAMETERS_SIZE / 4); ++i) {
		*buffer = ntohl(*buffer);
		++buffer;
	}
#endif

release_and_return:

	if (NULL != compare)
		free(compare);

	if (NULL != flash)
		spi_flash_free(flash);

	debug("%s:%d - rc=%d\n", __FILE__, __LINE__, rc);

	return rc;
#else
	return 0;
#endif
}

#endif	/* CONFIG_MEMORY_RETENTION */
