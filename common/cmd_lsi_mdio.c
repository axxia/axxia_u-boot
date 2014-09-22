/*
 *  common/cmd_lsi_mdio.c
 *
 *  Copyright (C) 2009 LSI
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

#include <config.h>
#include <common.h>
#include <command.h>
#include <net.h>
#include <linux/string.h>
#include <asm/io.h>
#include <malloc.h>

extern void phy_debug(void);

/*
  ======================================================================
  ======================================================================
  ======================================================================
  Globals
  ======================================================================
  ======================================================================
  ======================================================================
*/

/*
  ======================================================================
  ======================================================================
  ======================================================================
  Local Functions
  ======================================================================
  ======================================================================
  ======================================================================
*/

static int
decode_range(const char *input, int minimum, int maximum, int range[2])
{
	char *string;
	char *token;

	if (NULL == (string = malloc(strlen(input))))
		return -1;

	strcpy(string, input);

	if (0 == strcmp(string, "-1")) {
		range[0] = minimum;
		range[1] = maximum;
	} else {
		token = strsep(&string, "-");

		if (NULL == token)
			return -2;

		range[0] = simple_strtol(token, NULL, 16);
		token = strsep(&string, "-");

		if (NULL == token)
			range[1] = range[0];
		else
			range[1] = simple_strtol(token, NULL, 16);

		if (range[0] > range[1]) {
			int temp;

			temp = range[0];
			range[0] = range[1];
			range[1] = temp;
		}

		if ((minimum > range[0]) || (maximum < range[1]))
			return -1;
	}

	free(string);

	return 0;
}

/*
  ======================================================================
  ======================================================================
  ======================================================================
  Global Functions
  ======================================================================
  ======================================================================
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  do_mdio
*/

int
do_mdio(cmd_tbl_t *command_table, int flag, int argc, char * const argv[])
{
	mdio_initialize();

	if ((0 == strncmp(argv[1], "r", strlen("r"))) && (4 == argc)) {
		/*
		  mdio read
		*/

		int device_range[2];
		int register_range[2];
		int i;
		int j;

		if (0 != decode_range(argv[2], 0, 31, device_range))
			return -1;

		if (0 > device_range[0] || 31 < device_range[1])
			return -1;

		if (0 != decode_range(argv[3], 0, 31, register_range))
			return -1;

		if (0 > register_range[0] || 31 < register_range[1])
			return -1;

		for (i = device_range[0]; i <= device_range[1]; ++i) {
			for (j = register_range[0]; j <= register_range[1]; ++j) {
				printf("0x%02x[0x%02x]:0x%x\n",
				       i, j, mdio_read(i, j));
			}
		}
	} else if ((0 == strncmp(argv[1], "w", strlen("w")))) {
		/* write */

		if (5 == argc) {
			int phy;
			int reg;
			int value;

			phy = simple_strtol((argv[2]), NULL, 16);
			reg = simple_strtol((argv[3]), NULL, 16);
			value = simple_strtol((argv[4]), NULL, 16);
			mdio_write(phy, reg, value);
		} else {
			printf("Usage: mdio write phy reg value\n");
		}
	} else if ((0 == strncmp(argv[1], "d", strlen("d")))) {
		phy_debug();
	} else {
		printf("%s", command_table->usage);
	}

	return 0;
}

/*
  ----------------------------------------------------------------------
*/

U_BOOT_CMD(mdio, 5, 0, do_mdio,
	   "mdio	- mdio access\n",
	   "read  device|device-range register|register-range\n"
	   "write device|device-range register value\n");
