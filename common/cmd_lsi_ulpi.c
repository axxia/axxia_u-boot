/*
 * common/cmd_lsi_ulpi.c
 *
 * (C) Copyright 2009
 * LSI, sangeetha.rao@lsi.com
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
#include <usb/ulpi.h>

/*
  ======================================================================
  Local Stuff
*/

/*
  ----------------------------------------------------------------------
  read
*/

static int
read(unsigned long offset)
{
	int rc;
	struct ulpi_viewport ulpi_vp;
	unsigned short *reg;

	ulpi_vp.viewport_addr = CONFIG_USB_ADDR+ 0x170;
	ulpi_vp.port_num = 0x0;
	reg = (unsigned short *)offset;

	rc = ulpi_read(&ulpi_vp, (u8 *)reg);

	if (rc == ULPI_ERROR) {
		printf("Reading offset 0x%lx FAILED\n", offset);
		return CMD_RET_FAILURE;
	}
	printf("offset 0x%lx = 0x%x\n", offset, rc);
	return CMD_RET_SUCCESS;
}

/*
  ----------------------------------------------------------------------
  write
*/

static int
write(unsigned long offset, unsigned long value)
{
	int rc;
	struct ulpi_viewport ulpi_vp;

	ulpi_vp.viewport_addr = CONFIG_USB_ADDR+ 0x170;
	ulpi_vp.port_num = 0x0;

	printf("Writing offset 0x%lx = 0x%lx\n", offset, value);
	rc = ulpi_write(&ulpi_vp, (u8 *)offset, value);

	if (1 == rc) {
		printf("FAILED\n");
		return CMD_RET_FAILURE;
	}

	printf("PASSED\n");
	return CMD_RET_SUCCESS;

}


/*
  ======================================================================
  U-Boot Stuff
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  do_ulpi
*/
  
int
do_ulpi(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned long offset;
	unsigned long value;
	int rc = CMD_RET_USAGE;

	if( 0 == strncmp( argv[1], "r", strlen( "r" ) ) ) {
		if( 3 == argc ) {
			offset = simple_strtoul( argv[2], NULL, 16 );
			return read(offset);
		}
	} else if( 0 == strncmp( argv[1], "w", strlen( "w" ) ) ) {
		if( 4 == argc ) {
			offset = simple_strtoul( argv[2], NULL, 16 );
			value = simple_strtoul( argv[3], NULL, 16 );
			return write(offset, value );
		}
	}

	return rc;
}

/*
  ======================================================================
  Command Definitions
  ======================================================================
*/

U_BOOT_CMD(ulpi, 6, 0, do_ulpi,
	   "ulpi read|write [arguments]\n",
	   "r,ead offset\n"
	   "\tread from offset\n"
	   "w,rite to offset value\n"
	   "\twrite to offset value\n");
