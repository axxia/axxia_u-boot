/*
 * common/cmd_sbb.c
 *
 * (C) Copyright 2014
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
#include <common.h>
#include <command.h>
#include <malloc.h>
#include <nand.h>

/*
  ======================================================================
  Local
  ======================================================================
*/

/*
  ======================================================================
  Public
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  do_sbb
*/
  
int
do_sbb(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned long source;
	unsigned long destination;

	if (0 == strncmp(argv[1], "v", strlen("v"))) {
		int safe = 0;

		if ((5 == argc) && (0 == strncmp(argv[4], "s", strlen("s"))))
			safe = 1;

		source = simple_strtoul(argv[2], NULL, 16);
		destination = simple_strtoul(argv[3], NULL, 16);

		if (0 ==
		    sbb_verify_image((void *)source, (void *)destination, safe,
				     1, 1))
			return 0;
		else
			return -1;
	}

	return -1;
}

/*
  ======================================================================
  Command Definitions
  ======================================================================
*/

U_BOOT_CMD(sbb, 5, 0, do_sbb,
	   "Provide access to the SBB (Secure Boot Block) functionality.",
	   "validate source destination\n"
	   "       v,alidate -- Validate image (safe for double read).\n"
	   "          source -- Source address.\n"
	   "     destination -- Destination address. Can be same as source.");
