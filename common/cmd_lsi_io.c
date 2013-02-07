/*
 * common/cmd_lsi_io.c
 *
 * (C) Copyright 2010
 * LSI, john.jacques@lsi.com
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

#include <config.h>

#ifdef CONFIG_ACP

#include <common.h>
#include <command.h>

/*
  ======================================================================
  Local Stuff
  ======================================================================
*/

/*
  ======================================================================
  U-Boot Stuff
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  do_io
*/
  
int
do_io(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	int rc = 1;
	int i;
	int n;
	unsigned long address;

	if (3 <= argc)
		address = simple_strtoul(argv[2], NULL, 0);

	if (0 == strncmp(argv[1], "r", strlen("r"))) {
		if (4 == argc)
			n = simple_strtoul(argv[3], NULL, 0);
		else
			n = 1;

		for (i = 0; i < n; ++i) {
			printf("0x%08x contains 0x%08x\n",
			       address, acpreadio((unsigned long *)address));
			address += 4;
		}

		rc = 0;
	} else if (0 == strncmp(argv[1], "w", strlen("w"))) {
		rc = 0;

		for (i = 3; i < argc; ++i) {
			unsigned long value;

			value = simple_strtoul(argv[i], NULL, 0);
			printf("writing 0x%08x to 0x%08x\n", value, address);
			acpwriteio(value, (unsigned long *)address);
			address += 4;
		}
	}

	if (0 != rc) {
#ifndef CFG_NOHELP
		printf("%s", cmdtp->usage);
#endif
	}

	return rc;
}

/*
  ======================================================================
  Command Definitions
  ======================================================================
*/

U_BOOT_CMD(io, CONFIG_SYS_MAXARGS, 0, do_io,
	   "io read|write (byte swapped)",
	   "r,ead address [number] -- Read from IO space.\n" \
	   "w,write address value [value...] -- Write to IO space.");

#endif /* CONFIG_ACP */
