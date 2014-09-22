/*
 * common/cmd_lsi_clocks.c
 *
 * (C) Copyright 2013
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

#ifndef CONFIG_SPL_BUILD

#include <config.h>
#include <common.h>
#include <command.h>

/*
  ======================================================================
  Local Stuff
  ======================================================================
*/

/*
  ======================================================================
  Global Stuff
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  do_clocks
*/
  
int
do_clocks(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	axxia_display_clocks();

	return CMD_RET_SUCCESS;
}

U_BOOT_CMD(clocks, 1, 0, do_clocks,
	   "clocks\n",
	   "Displays the current frequency of the PLLs and clocks\n"
	   "and indicates if lock has been lost.\n");

#endif /* CONFIG_SPL_BUILD */
