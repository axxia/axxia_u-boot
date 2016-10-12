/*
 * common/cmd_extmemmpr.c
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

#include <config.h>
#include <common.h>
#include <command.h>

/*
  ======================================================================
  Public
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  do_extmemmpr
*/
  
int
do_extmemmpr(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	char *memory;
	unsigned long interface;
	unsigned long page;
	unsigned long max_interface;

	if (argc != 4) {
		printf("%s", cmdtp->usage);

		return -1;
	}

	memory = argv[1];
	interface = simple_strtoul(argv[2], NULL, 0);
	page = simple_strtoul(argv[3], NULL, 0);

	if (3 < page) {
		printf("Page must be 0...3.\n");
		printf("%s", cmdtp->usage);

		return -1;
	}

	if (0 == strncmp(memory, "cmem", strlen("cmem"))) {
#if defined(CONFIG_AXXIA_ANY_56XX)
		max_interface = 2;
#elif defined(CONFIG_AXXIA_ANY_XLF)
		max_interface = 1;
#else
#error "Axxia Target Not Handled!"
#endif

		if (max_interface <= interface) {
			printf("Interface Out of Range!\n");
			printf("%s", cmdtp->usage);

			return -1;
		}

		handle_cmem_mpr((int)interface, (int)page);
	} else if (0 == strncmp(memory, "smem", strlen("smem"))) {
#if defined(CONFIG_AXXIA_ANY_56XX)
		max_interface = 2;
#elif defined(CONFIG_AXXIA_ANY_XLF)
		max_interface = 4;
#else
#error "Axxia Target Not Handled!"
#endif

		if (max_interface <= interface) {
			printf("Interface Out of Range!\n");
			printf("%s", cmdtp->usage);

			return -1;
		}

		handle_smem_mpr((int)interface, (int)page);
	} else {
		printf("Unknown Memory Type!\n");
		printf("%s", cmdtp->usage);

		return -1;
	}

	return 0;
}

/*
  ======================================================================
  Command Definitions
  ======================================================================
*/

U_BOOT_CMD(extmemmpr, 4, 0, do_extmemmpr,
	   "extmemmpr cmem|smem interface page\n",
	   "     cmem|smem - choose the external memory\n" \
	   "     interface - specify the interface\n" \
	   "     page      - specify the JEDEC MPR page\n");
