/*
 * common/cmd_lsi_ssp.c
 *
 * (C) Copyright 2009
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
*/

/*
  ----------------------------------------------------------------------
  read
*/

static int
read(unsigned long device,
     unsigned long address, unsigned long offset, unsigned long size)
{
	ssp_init(device, 1);
	ssp_read((void *)address, offset, size);

	return 0;
}

/*
  ----------------------------------------------------------------------
  write
*/

static int
write( unsigned long device,
       unsigned long address, unsigned long offset, unsigned long size )
{
	ssp_init(device, 0);
	return ssp_write((void *)address, offset, size, 0);
}


/*
  ======================================================================
  U-Boot Stuff
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  do_ssp
*/
  
int
do_ssp( cmd_tbl_t * cmdtp, int flag, int argc, char * argv [ ] )
{
	unsigned long device;
	unsigned long address;
	unsigned long offset;
	unsigned long size;
	int return_code = 1;

	if( 0 == strncmp( argv[1], "h", strlen( "h" ) ) ) {
#ifndef CFG_NOHELP
#ifdef CFG_LONGHELP
		printf( "%s", cmdtp->help );
#else
		printf( "%s", cmdtp->usage );
#endif
#endif
		return_code = 0;
	} else if( 0 == strncmp( argv[1], "r", strlen( "r" ) ) ) {
		if( 6 == argc ) {
			device = simple_strtoul( argv[2], NULL, 16 );
			address = simple_strtoul( argv[3], NULL, 16 );
			offset = simple_strtoul( argv[4], NULL, 16 );
			size = simple_strtoul( argv[5], NULL, 16 );
			return_code = read( device, address, offset, size );
		}
	} else if( 0 == strncmp( argv[1], "w", strlen( "w" ) ) ) {
		if( 6 == argc ) {
			device = simple_strtoul( argv[2], NULL, 16 );
			address = simple_strtoul( argv[3], NULL, 16 );
			offset = simple_strtoul( argv[4], NULL, 16 );
			size = simple_strtoul( argv[5], NULL, 16 );
			return_code = write( device, address, offset, size );
		}


	}

	if( 0 != return_code ) {
#ifndef CFG_NOHELP
		printf( "%s", cmdtp->usage );
#endif
	}

	return return_code;
}

/*
  ======================================================================
  Command Definitions
  ======================================================================
*/

U_BOOT_CMD( ssp, 6, 0, do_ssp,
	    "ssp help|read|write [arguments]\n",
	    "h,elp\n" \
	    "\tdisplay this help screen\n" \
	    "r,ead device address offset size\n" \
	    "\tread size bytes from offset to address\n" \
	    "w,rite device address offset size\n" \
	    "\twrite size bytes from address to offset\n");

#endif /* CONFIG_ACP */
