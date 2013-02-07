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

#undef DEBUG
/*#define DEBUG*/
#ifdef DEBUG
#define DEBUG_PRINT( format, args... ) do { \
printf( "cmd_ssp:%s:%d - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else
#define DEBUG_PRINT( format, args... )
#endif

/*
  ======================================================================
  Local Stuff
*/

/*
  ----------------------------------------------------------------------
  dump
*/

static int
dump( unsigned long offset, unsigned long length )
{
	DEBUG_PRINT( "offset=0x%lx/%ld length=%ld\n", offset, offset, length );

	return 0;
}

/*
  ----------------------------------------------------------------------
  fill
*/

static int
fill( unsigned long offset, unsigned long length, unsigned char pattern )
{
	DEBUG_PRINT( "offset=0x%lx/%ld length=%ld pattern=0x%x\n",
		     offset, offset, length, pattern );

	

	return 0;
}

/*
  ----------------------------------------------------------------------
  read
*/

static int
read( unsigned long offset, unsigned long address, unsigned long length )
{
	DEBUG_PRINT( "offset=0x%lx/%ld address=0x%lx/%ld length=%ld\n",
		     offset, offset, address, address, length );
	ssp_init(0, 0);
	ssp_read( ( void * ) address, offset, length );

	return 0;
}

/*
  ----------------------------------------------------------------------
  write
*/

static int
write( unsigned long address, unsigned long offset, unsigned long length )
{
	DEBUG_PRINT( "address=0x%lx/%ld offset=0x%lx/%ld length=%ld\n",
		     address, address, offset, offset, length );

	ssp_init(0, 0);
	return ssp_write((void *)address, offset, length, 0);
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
	unsigned long offset;
	unsigned long address;
	unsigned long length;
	unsigned char pattern;
	int return_code = 1;

	DEBUG_PRINT( "flag=%d argc=%d\n", flag, argc );

	if( 0 == strncmp( argv[1], "d", strlen( "d" ) ) ) {
		if( 4 == argc ) {
			offset = simple_strtoul( argv[2], NULL, 16 );
			length = simple_strtoul( argv[3], NULL, 16 );
			return_code = dump( offset, length );
		}
	} else if( 0 == strncmp( argv[1], "f", strlen( "f" ) ) ) {
		if( 0 == strncmp( argv[2], "a", strlen( "a" ) ) &&
		    4 == argc ) {
			offset = simple_strtoul( argv[3], NULL, 16 );
			pattern = ( unsigned char ) ( offset & 0xff );
			offset = 0;
			length = 128 * 1024;
		} else if( 5 == argc ) {
			offset = simple_strtoul( argv[4], NULL, 16 );
			pattern = ( unsigned char ) ( offset & 0xff );
			offset = simple_strtoul( argv[2], NULL, 16 );
			length = simple_strtoul( argv[3], NULL, 16 );
		}
		return_code = fill( offset, length, pattern );
	} else if( 0 == strncmp( argv[1], "h", strlen( "h" ) ) ) {
#ifndef CFG_NOHELP
#ifdef CFG_LONGHELP
		printf( "%s", cmdtp->help );
#else
		printf( "%s", cmdtp->usage );
#endif
#endif
		return_code = 0;
	} else if( 0 == strncmp( argv[1], "i", strlen( "i" ) ) ) {
		return_code = ssp_init(0, 0);
	} else if( 0 == strncmp( argv[1], "r", strlen( "r" ) ) ) {
		if( 5 == argc ) {
			offset = simple_strtoul( argv[2], NULL, 16 );
			address = simple_strtoul( argv[3], NULL, 16 );
			length = simple_strtoul( argv[4], NULL, 16 );
			return_code = read( offset, address, length );
		}
	} else if( 0 == strncmp( argv[1], "w", strlen( "w" ) ) ) {
		if( 5 == argc ) {
			address = simple_strtoul( argv[2], NULL, 16 );
			offset = simple_strtoul( argv[3], NULL, 16 );
			length = simple_strtoul( argv[4], NULL, 16 );
			return_code = write( address, offset, length );
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

U_BOOT_CMD( ssp, 5, 0, do_ssp,
	    "ssp dump|fill|help|read|write [arguments]\n",
	    "d,ump offset length\n" \
	    "\tdump length bytes starting at offset\n" \
	    "f,ill [all | offset length] pattern\n" \
	    "\tfill the device with the given pattern\n" \
	    "h,elp\n" \
	    "i,nitialize\n" \
	    "\tdisplay this help screen\n" \
	    "r,ead offset address length\n" \
	    "\tread length bytes from offset to address\n" \
	    "w,rite address offset length\n" \
	    "\twrite length bytes from address to offset\n");

#endif /* CONFIG_ACP */
