/*
 * common/cmd_ncr.c
 *
 * (C) Copyright 2016
 * Intel, john.jacques@intel.com
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <command.h>
#include <asm/io.h>

/*
  ------------------------------------------------------------------------------
  do_ncr_read
*/

static int
do_ncr_read(unsigned long node, unsigned long target, unsigned long offset,
	    int width)
{
	unsigned long value32;
	unsigned short value16;
	unsigned char value8;
	int rc;

	switch (width) {
	case 4:
		rc = ncr_read(NCP_REGION_ID(node, target),
			      0, offset, width, &value32);
		break;
	case 2:
		rc = ncr_read(NCP_REGION_ID(node, target),
			      0, offset, width, &value16);
		break;
	case 1:
		rc = ncr_read(NCP_REGION_ID(node, target),
			      0, offset, width, &value8);
		break;
	default:
		printf("Invalid Width!\n");
		return -1;
		break;
	}

	if (0 != rc) {
		printf("ncr read failed: %d\n", rc);
		return -1;
	}

	printf("0x%lx.0x%lx.0x%lx : ", node, target, offset);

	switch (width) {
	case 4:
		printf("0x%08lx\n", value32);
		break;
	case 2:
		printf("0x%08x\n", value16);
		break;
	case 1:
		printf("0x%08x\n", value8);
		break;
	default:
		/* Invalid Width is Handled Above */
		break;
	}

	return 0;
}

/*
  ------------------------------------------------------------------------------
  do_ncr_write
*/

static int
do_ncr_write(unsigned long node, unsigned long target, unsigned long offset,
	     int width, unsigned long value)
{
	unsigned short value16;
	unsigned char value8;
	int rc;

	switch (width) {
	case 4:
		rc = ncr_write(NCP_REGION_ID(node, target),
			       0, offset, width, &value);
		break;
	case 2:
		value16 = (unsigned short)value;
		rc = ncr_write(NCP_REGION_ID(node, target),
			       0, offset, width, &value16);
		break;
	case 1:
		value8 = (unsigned char)value;
		rc = ncr_write(NCP_REGION_ID(node, target),
			       0, offset, width, &value8);
		break;
	default:
		printf("Invalid Width!\n");
		return -1;
		break;
	}

	if (0 != rc) {
		printf("ncr write failed : %d\n", rc);
		return -1;
	}

	return 0;
}

/*
  ----------------------------------------------------------------------
  do_ncr
*/

int
do_ncr(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned node;
	unsigned target;
	unsigned offset;
	int width;
	unsigned number;
	char *token;
	int rc;
	char *input = argv[2];

	width = cmd_get_data_size(argv[0], 4);

	if (0 == strncmp(argv[1], "h", strlen("h"))) {
		printf("%s", cmdtp->usage);
		return 0;
	}

	token = strsep(&input, ".");
	node = simple_strtoul(token, NULL, 0);
	token = strsep(&input, ".");
	target = simple_strtoul(token, NULL, 0);
	token = strsep(&input, ".");
	offset = simple_strtoul(token, NULL, 0);

	if (0 == strncmp(argv[1], "r", strlen("r"))) {
		if (4 == argc)
			number = simple_strtoul(argv[3], NULL, 0);
		else
			number = 1;

		while (0 < number--) {
			rc = do_ncr_read(node, target, offset, width);

			if (0 != rc)
				return -1;

			offset += 4;
		}

		return 0;
	} else if (0 == strncmp(argv[1], "w", strlen("w"))) {
		int index;
		unsigned long value;

		if (4 > argc) {
			printf("Too few arguments for a write!\n");
			return -1;
		}

		index = 3;

		while (4 <= argc--) {
			value = simple_strtoul(argv[index++], NULL, 0);
			rc = do_ncr_write(node, target, offset, width, value);

			if (0 != rc)
				return -1;

			offset += 4;
		}

		return 0;
	}

	printf("%s", cmdtp->usage);

	return -1;
}

/*
  ======================================================================
  Command Definitions
  ======================================================================
*/

U_BOOT_CMD(ncr, CONFIG_SYS_MAXARGS, 0, do_ncr,
	    "ncr[.l|.w|.b] help|read|write [arguments]\n",
	    "h,elp\n" \
	    "r,ead node.target.offset [number]\n" \
	    "\tread number values from node.target.offset\n" \
	    "\tdefault length is 1\n" \
	    "w,rite node.target.offset value [value2 ...]\n" \
	    "\twrite value(s) to node.target.offset\n" \
	    "Use .l, .w, or .b for 32, 16, or 8 bit access. Default is 32.\n");
