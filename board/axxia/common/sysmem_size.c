/*
 * sysmem_size.c
 *
 * Copyright (C) 2010 LSI Corporation
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software;you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation;either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY;without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program;if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>

/*
  ------------------------------------------------------------------------------
  sysmem_size
*/

unsigned long long
sysmem_size(void)
{
	unsigned long long sdram_capacity_bytes;
	unsigned long sdram_device_width_bits;
	unsigned long primary_bus_width_bits;
#if !defined(CONFIG_SPL_BUILD)
	int rc;

	/*
	  In the U-Boot case (not SPL), reading the parameters is
	  required to determine the amount of memory available.
	*/

	rc = read_parameters();
#endif	/* CONFIG_SPL_BUILD */

	/*
	  For now, when in simulation, with no parameter file, just
	  assume 4 GB.
	*/

#if defined(CONFIG_AXXIA_SIM)
	if (0 == parameters_avail()) {
		printf("Running with no parameters, guessing 4G of memory\n");
		sysmem->totalSize = (4ULL * (1ULL << 30));

		return sysmem->totalSize;
	}
#endif

#if !defined(CONFIG_SPL_BUILD)
	if (0 != rc)
		acp_failure(__FILE__, __FUNCTION__, __LINE__);
#endif

	sdram_capacity_bytes =
		(1 << sysmem->sdram_device_density) *
		((256 * 1024 * 1024) / 8);
	sdram_device_width_bits = 4 * (1 << sysmem->sdram_device_width);
	primary_bus_width_bits = 8 * (1 << sysmem->primary_bus_width);
	sdram_capacity_bytes =
		sysmem->numInterfaces * sysmem->numRanks *
		sdram_capacity_bytes *
		(primary_bus_width_bits / sdram_device_width_bits);
	sysmem->totalSize = sdram_capacity_bytes;

	return sysmem->totalSize;
}
