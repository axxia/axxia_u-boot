/*
 * common/cmd_lsi_osg.c
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

#ifndef CONFIG_SPL_BUILD

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
  do_osg
*/
  
int
do_osg(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	int rc = 1;
	int group;

	if (0 == strncmp(argv[1], "b", strlen("b"))) {
		int core;

		__asm__ __volatile__ ("mfspr %0,0x11e" : "=r" (core));
		group = acp_osg_get_group(core);
		acp_osg_jump_to_os(group);
	} else if (0 == strncmp(argv[1], "d", strlen("d"))) {
		int i;

		for (i = 0; i < ACP_NR_CORES; ++i) {
			acp_osg_dump(i);
		}

		rc = 0;
	} else if (0 == strncmp(argv[1], "s", strlen("s"))) {
		if (3 == argc) {
			int group;

			group = simple_strtoul(argv[2], NULL, 16);
			acp_osg_set_current(group);
			working_fdt = (struct fdt_header *)get_acp_fdt(group);
			rc = 0;
		}
	} else if (0 == strncmp(argv[1], "g", strlen("g"))) {
		printf("OSG Current Group: %d\n", acp_osg_get_current());
		rc = 0;
	}

	if (0 != rc) {
		printf("%s", cmdtp->usage);
	}

	return rc;
}

/*
  ======================================================================
  Command Definitions
  ======================================================================
*/

U_BOOT_CMD(osg, CONFIG_SYS_MAXARGS, 0, do_osg,
	   "osg boot|display|set|get",
	   "osg b,oot [group] - boot the given, or current group.\n" \
	   "osg d,isplay - display the group structures.\n" \
	   "osg s,et - set the current group (for bootm etc.).\n" \
	   "osg g,et - get the current group.\n");

#endif /* CONFIG_SPL_BUILD */
