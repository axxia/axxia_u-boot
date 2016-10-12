/*
 *  Copyright (C) 2016 Intel Corporation
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

#include <common.h>

#include "regs/cmem_56xx/ncp_memory_controller_regs.h"
#include "regs/cmem_56xx/ncp_memory_controller_reg_defines.h"

#include "regs/ncp_denali_5600_regs.h"
#include "regs/ncp_denali_5600_reg_defines.h"

int
handle_cmem_mpr(int interface, int page)
{
#if defined(CONFIG_AXXIA_ANY_56XX)
	unsigned int nodes[] = {0x8, 0x9};
#elif defined(CONFIG_AXXIA_ANY_XLF)
	unsigned int nodes[] = {0x8};
#endif
	unsigned int region;
	ncp_memory_controller_DENALI_CTL_34_t ctl_34;
	ncp_memory_controller_DENALI_CTL_84_t ctl_84;
	int i;
	ncp_uint32_t ctl_35[4];

	if ((interface > (sizeof(nodes) / sizeof(unsigned int))) ||
	    (3 < page) ||
	    (3 != sysmem->crc_mode)) {
		error("handl_smem_mpr(): Bad Input! (%d %d %d)\n",
		      interface, page, sysmem->crc_mode);

		return -1;
	}

	region = NCP_REGION_ID(nodes[interface], 0x9);

	/* Write the page. */
	ncr_read32(region, NCP_MEMORY_CONTROLLER_DENALI_CTL_34,
		   (ncp_uint32_t *)&ctl_34);
	ctl_34.read_mpr = 0;
	ctl_34.read_mpr |= ((sysmem->topology & 3) << 2) | (page & 3);
	ncr_write32(region, NCP_MEMORY_CONTROLLER_DENALI_CTL_34,
		    *((ncp_uint32_t *)&ctl_34));

	/* Trigger the read. */
	ncr_read32(region, NCP_MEMORY_CONTROLLER_DENALI_CTL_34,
		   (ncp_uint32_t *)&ctl_34);
	ctl_34.read_mpr |= 0x10;
	ncr_write32(region, NCP_MEMORY_CONTROLLER_DENALI_CTL_34,
		    *((ncp_uint32_t *)&ctl_34));

	/* Poll for MPR done. */
	ncr_poll(region, NCP_MEMORY_CONTROLLER_DENALI_CTL_84,
		 0x2000000, 0x2000000, 1000, 1000);

	ncr_read32(region, NCP_MEMORY_CONTROLLER_DENALI_CTL_84,
		   (ncp_uint32_t *)&ctl_84);
        printf("CTL_84 int_status = 0x%x\n", ctl_84.int_status);

	/* Display the results. */

	for (i = 0; i < 4; ++i) {
		ncr_read32(region,
			   (NCP_MEMORY_CONTROLLER_DENALI_CTL_35 + (8 * i)),
			   &(ctl_35[i]));
	}

        printf("\nDRAM-0 MPR Page[%d] info: ", page);

        for(i = 0; i < 4; i++)
		printf("MPR %d=0x%02x, ", i + 1, ctl_35[i] & 0xff);

        printf("\nDRAM-1 MPR Page[%d] info: ", page);

        for(i = 0; i < 4; i++)
		printf("MPR %d=0x%02x, ", i + 1, (ctl_35[i] & 0xff00) >> 8);

	puts("\n");

	return 0;
}

int
handle_smem_mpr(int interface, int page)
{
#if defined(CONFIG_AXXIA_ANY_56XX)
	unsigned int nodes[] = {0x22, 0xf};
#elif defined(CONFIG_AXXIA_ANY_XLF)
	unsigned int nodes[] = {0x22, 0xf, 0x23, 0x24};
#endif
	unsigned int region;
	ncp_denali_DENALI_CTL_57_5600_t ctl_57;
	ncp_denali_DENALI_CTL_366_5600_t ctl_366;
	ncp_denali_DENALI_CTL_367_5600_t ctl_367;
	int i;
	ncp_uint32_t ctl_58[4];
	ncp_uint32_t ctl_59[4];
	ncp_uint32_t ctl_60[4];

	if ((interface > (sizeof(nodes) / sizeof(unsigned int))) ||
	    (3 < page) ||
	    (3 != sysmem->crc_mode)) {
		error("handl_smem_mpr(): Bad Input! (%d %d %d)\n",
		      interface, page, sysmem->crc_mode);

		return -1;
	}

	region = NCP_REGION_ID(nodes[interface], 0);

	/* Write the page. */
	ncr_read32(region, NCP_DENALI_CTL_57_5600, (ncp_uint32_t *)&ctl_57);
	ctl_57.read_mpr = 0;
	ctl_57.read_mpr |= ((sysmem->topology & 3) << 2) | (page & 3);
	ncr_write32(region, NCP_DENALI_CTL_57_5600, *((ncp_uint32_t *)&ctl_57));

	/* Trigger the read. */
	ncr_read32(region, NCP_DENALI_CTL_57_5600, (ncp_uint32_t *)&ctl_57);
	ctl_57.read_mpr |= 0x10;
	ncr_write32(region, NCP_DENALI_CTL_57_5600, *((ncp_uint32_t *)&ctl_57));

	/* Poll for MPR done. */
	ncr_poll(region, NCP_DENALI_CTL_366_5600,
		 0x4000000, 0x4000000, 1000, 1000);

	ncr_read32(region, NCP_DENALI_CTL_366_5600, (ncp_uint32_t *)&ctl_366);
        printf("CTL_366 int_status = 0x%x\n", ctl_366.int_status);
        ncr_read32(region, NCP_DENALI_CTL_366_5600, (ncp_uint32_t *)&ctl_367);
        printf("CTL_367 int_status = 0x%x\n", ctl_367.int_status);

	/* Display the results. */

	for (i = 0; i < 4; ++i) {
		ncr_read32(region, (NCP_DENALI_CTL_58_5600 + (0x14 * i)),
			   &(ctl_58[i]));
		ncr_read32(region, (NCP_DENALI_CTL_59_5600 + (0x14 * i)),
			   &(ctl_59[i]));
		ncr_read32(region, (NCP_DENALI_CTL_60_5600 + (0x14 * i)),
			   &(ctl_60[i]));
	}

        printf("\nDRAM-0 MPR Page[%d] info: ", page);

        for(i = 0; i < 4; i++)
		printf("MPR %d=0x%02x, ", i + 1, ctl_58[i] & 0xff);

        printf("\nDRAM-1 MPR Page[%d] info: ", page);

        for(i = 0; i < 4; i++)
		printf("MPR %d=0x%02x, ", i + 1, (ctl_58[i] & 0xff00) >> 8);

        printf("\nDRAM-2 MPR Page[%d] info: ", page);

        for(i = 0; i < 4; i++)
		printf("MPR %d=0x%02x, ", i + 1, (ctl_58[i] & 0xff0000) >> 16);

        printf("\nDRAM-3 MPR Page[%d] info: ", page);

        for(i = 0; i < 4; i++)
		printf("MPR %d=0x%02x, ",
		       i + 1, (ctl_58[i] & 0xff000000) >> 24);

        printf("\nDRAM-4 MPR Page[%d] info: ", page);

        for(i = 0; i < 4; i++)
		printf("MPR %d=0x%02x, ", i + 1, ctl_59[i] & 0xff);

        printf("\nDRAM-5 MPR Page[%d] info: ", page);

        for(i = 0; i < 4; i++)
		printf("MPR %d=0x%02x, ", i + 1, (ctl_59[i] & 0xff00) >> 8);

        printf("\nDRAM-6 MPR Page[%d] info: ", page);

        for(i = 0; i < 4; i++)
		printf("MPR %d=0x%02x, ", i + 1, (ctl_59[i] & 0xff0000) >> 16);

        printf("\nDRAM-7 MPR Page[%d] info: ", page);

        for(i = 0; i < 4; i++)
		printf("MPR %d=0x%02x, ",
		       i + 1, (ctl_59[i] & 0xff000000) >> 24);

        printf("\nDRAM-8 MPR Page[%d] info: ", page);

        for(i = 0; i < 4; i++)
		printf("MPR %d=0x%02x, ", i + 1, ctl_60[i] & 0xff);

	puts("\n");

	return 0;
}
