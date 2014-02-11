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

/*#define DEBUG*/

#include <config.h>
#include <common.h>
#include <spi.h>
#include <spi_flash.h>
#include <malloc.h>

/*
  ==============================================================================
  ==============================================================================
  Private
  ==============================================================================
  ==============================================================================
*/

static void *parameters __attribute__ ((section ("data"))) = NULL;
static int copy_in_use __attribute__ ((section ("data"))) = 0;
static int parameters_read __attribute__ ((section ("data"))) = 0;

#if defined(CONFIG_AXXIA_PPC)
/*
  For PPC (34xx, 25xx, 35xx), use version 4 of the parameters.
*/
#ifdef CONFIG_SPL_BUILD
#define PARAMETERS_HEADER_ADDRESS \
	(LCM + (128 * 1024) - sizeof(parameters_header_t))
#define PARAMETERS_OFFSET ((128 * 1024) - PARAMETERS_SIZE)
#define PARAMETERS_ADDRESS (LCM + PARAMETERS_OFFSET)
#endif
#define PARAMETERS_SIZE (1024)
#define PARAMETERS_OFFSET_IN_FLASH PARAMETERS_OFFSET
#define PARAMETERS_VERSION 4
#elif defined(CONFIG_AXXIA_ARM)
/*
  For ARM (55xx), use version 7 of the parameters.
*/
#ifdef CONFIG_SPL_BUILD
#define PARAMETERS_HEADER_ADDRESS \
	(LSM + (256 * 1024) - sizeof(parameters_header_t))
#define PARAMETERS_OFFSET ((256 * 1024) - PARAMETERS_SIZE)
#define PARAMETERS_ADDRESS (LSM + PARAMETERS_OFFSET)
#endif
#define PARAMETERS_SIZE (4096)
#define PARAMETERS_OFFSET_IN_FLASH 0x40000
#define PARAMETERS_VERSION 7
#else
#error "Unknown Architecture!"
#endif

#ifdef CONFIG_SPL_BUILD
parameters_header_t *header __attribute__ ((section ("data"))) = NULL;
#else
parameters_header_t *header __attribute__ ((section ("data"))) = NULL;
#endif
parameters_global_t *global __attribute__ ((section ("data"))) = NULL;
parameters_pciesrio_t *pciesrio __attribute__ ((section ("data"))) = NULL;
parameters_voltage_t *voltage __attribute__ ((section ("data"))) = NULL;
parameters_clocks_t *clocks __attribute__ ((section ("data"))) = NULL;
parameters_sysmem_t *sysmem __attribute__ ((section ("data"))) = NULL;
#ifdef CONFIG_AXXIA_ARM
void *retention __attribute__ ((section ("data"))) = NULL;
#endif

/*
  ------------------------------------------------------------------------------
  verify_parameters
*/

static int
verify_parameters(void *parameters)
{
	parameters_header_t *lheader;

	lheader = parameters + PARAMETERS_SIZE - sizeof(parameters_header_t);

	/* Check for the magic number. */

	if (PARAMETERS_MAGIC != ntohl(lheader->magic)) {
		printf("Parameter table has wrong magic number!\n");
		return -1;
	}

	/* Verify the checksum. */

	if (crc32(0, parameters, (ntohl(lheader->size) - 12)) !=
	    ntohl(lheader->checksum) ) {
		printf("Parameter table is corrupt. 0x%08x!=0x%08x\n",
		       ntohl(lheader->checksum),
		       crc32(0, parameters, (ntohl(lheader->size) - 12)));
		return -1;
	}

	/* Check the version. */

	if (PARAMETERS_VERSION != ntohl(lheader->version)) {
		printf("Parameter table should be version %d, not %d!\n",
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
  -------------------------------------------------------------------------------
  read_parameters
*/

int
read_parameters(void)
{
#ifdef CONFIG_AXXIA_ARM
	int i;
	unsigned *buffer;
#endif

#ifdef CONFIG_SPL_BUILD
	parameters = (void *)PARAMETERS_ADDRESS;
#else
	parameters = malloc(PARAMETERS_SIZE);
	memset(parameters, 0, PARAMETERS_SIZE);
#endif

	header = parameters + PARAMETERS_SIZE - sizeof(parameters_header_t);

	/*
	  Try LSM first, to allow for board repair when the serial
	  EEPROM contains a valid but incorrect (unusable) parameter
	  table.
	*/

	/* Verify that the paramater table is valid. */
	if (PARAMETERS_MAGIC != ntohl(header->magic)) {
		struct spi_flash *flash;

		flash = spi_flash_probe(0, 0, CONFIG_SF_DEFAULT_SPEED,
					CONFIG_SF_DEFAULT_MODE);

		if (!flash)
			return -1;

		spi_flash_read(flash, CONFIG_PARAMETER_OFFSET,
			       PARAMETERS_SIZE, parameters);

		if (0 != verify_parameters(parameters)) {
			printf("Primary Parameters are Corrupt, using Backup!\n");

			/* Try the redunant copy. */
			spi_flash_read(flash, CONFIG_PARAMETER_OFFSET_REDUND,
				       PARAMETERS_SIZE, parameters);

			if (0 != verify_parameters(parameters)) {
				printf("Backup Parameters are Corrupt!\n");
				return -1;
			}

			copy_in_use = 1;
		} else {
			copy_in_use = 0;
		}
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
	       "0x%08lx 0x%08lx 0x%08lx 0x%08lx\n"
	       "0x%08lx 0x%08lx\n"
	       "0x%08lx 0x%08lx\n"
	       "0x%08lx 0x%08lx\n"
	       "0x%08lx 0x%08lx\n"
	       "0x%08lx 0x%08lx\n",
	       header->magic,
	       header->size,
	       header->checksum,
	       header->version,
	       header->globalOffset,
	       header->globalSize,
	       header->pciesrioOffset,
	       header->pciesrioSize,
	       header->voltageOffset,
	       header->voltageSize,
	       header->clocksOffset,
	       header->clocksSize,
	       header->sysmemOffset,
	       header->sysmemSize);
#endif

	global = (parameters_global_t *)(parameters + header->globalOffset);
	pciesrio = (parameters_pciesrio_t *)(parameters + header->pciesrioOffset);
	voltage = (parameters_voltage_t *)(parameters + header->voltageOffset);
	clocks = (parameters_clocks_t *)(parameters + header->clocksOffset);
	sysmem = (parameters_sysmem_t *)(parameters + header->sysmemOffset);
#ifdef CONFIG_AXXIA_ARM
	retention = (void *)(parameters + header->retentionOffset);
#endif

#ifdef DISPLAY_PARAMETERS
	printf("version=%lu flags=0x%lx\n", global->version, global->flags);
#endif

	printf("Parameter Table Version %u\n", global->version);

	return 0;
}

#ifdef CONFIG_MEMORY_RETENTION

/*
  -------------------------------------------------------------------------------
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
				CONFIG_SF_DEFAULT_SPEED, CONFIG_SF_DEFAULT_MODE);

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
		       "     global = 0x%x\n"
		       "   pciesrio = 0x%x\n"
		       "    voltage = 0x%x\n"
		       "     clocks = 0x%x\n"
		       "     sysmem = 0x%x\n"
		       "  retention = 0x%x\n",
		       parameters + header->globalOffset,
		       parameters + header->pciesrioOffset,
		       parameters + header->voltageOffset,
		       parameters + header->clocksOffset,
		       parameters + header->sysmemOffset,
		       parameters + header->retentionOffset);

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

	debug("%s:%d - header->size=0x%x header->checksum=0x%x\n",
	      __FILE__, __LINE__, header->size, header->checksum);
	header->checksum =
		htonl(crc32(0, parameters, (ntohl(header->size) - 12)));
	debug("%s:%d - header->checksum=0x%x\n",
	      __FILE__, __LINE__, header->checksum);

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
