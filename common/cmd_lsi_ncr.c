/*
 * common/cmd_lsi_ncr.c
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
#include <asm/io.h>

#undef DEBUG
/*#define DEBUG*/
#ifdef DEBUG
#define DEBUG_PRINT( format, args... ) do { \
printf( "cmd_lsi_ncr:%s:%d - ", __FUNCTION__, __LINE__ ); \
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
  ======================================================================
  U-Boot Stuff
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  do_ncr
*/
  
int
do_ncr( cmd_tbl_t * cmdtp, int flag, int argc, char * argv [ ] )
{
	int return_code = 1;

	DEBUG_PRINT( "flag=%d argc=%d\n", flag, argc );

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
		unsigned node;
		unsigned target;
		unsigned offset;
		unsigned length = 1;
		char * token;
		int index;

		token = strsep( & ( argv [ 2 ] ), "." );
		node = simple_strtoul( token, NULL, 0 );
		token = strsep( & ( argv [ 2 ] ), "." );
		target = simple_strtoul( token, NULL, 0 );
		token = strsep( & ( argv [ 2 ] ), "." );
		offset = simple_strtoul( token, NULL, 0 );

		if( 4 == argc ) {
			length = simple_strtoul( argv [ 3 ], NULL, 0 );
		}

		DEBUG_PRINT( "Read %d values from 0x%x.0x%x.0x%x\n",
			     length, node, target, offset );

		if( ( 0x100 > node ) || ( 0x200 == node && 1 == target ) ) {
			for( index = 0; index < length; ++ index ) {
				unsigned long value;

				ncr_read32( NCP_REGION_ID( node, target ),
					    offset, ( void * ) & value );
				printf( "0x%x.0x%x.0x%x : 0x%lx\n",
					node, target, offset, value );
				offset += 4;
			}
		} else {
			/*
			  Nodes from 0x100 on are "virtual".  Only some are
			  handled!
			*/
			unsigned long base;

			switch( NCP_REGION_ID( node, target ) ) {
			case NCP_REGION_ID( 0x100, 0x4 ):
				base = ( IO + 0xc0000 );
				return_code = 0;
				break;
			default:
				printf( "Unhandled Virtual Region!\n" );
				break;
			}

			if( 0 == return_code ) {
				for( index = 0; index < length; ++ index ) {
					printf( "0x%x.0x%x.0x%x <0x%x> : " \
						"0x%lx\n",
						node, target, offset,
						( base + offset ),
						readl( base + offset ) );
					offset += 4;
				}
			}
		}

		return_code = 0;
	} else if( 0 == strncmp( argv[1], "w", strlen( "w" ) ) ) {
		unsigned node;
		unsigned target;
		unsigned offset;
		char * token;
		int index;

		token = strsep( & ( argv [ 2 ] ), "." );
		node = simple_strtoul( token, NULL, 0 );
		token = strsep( & ( argv [ 2 ] ), "." );
		target = simple_strtoul( token, NULL, 0 );
		token = strsep( & ( argv [ 2 ] ), "." );
		offset = simple_strtoul( token, NULL, 0 );

		if( ( 0x100 > node ) || ( 0x200 == node && 1 == target ) ) {
			for( index = 0; index < ( argc - 3 ); ++ index ) {
				unsigned long value;

				value =
				  simple_strtoul( argv [ 3 + index ], NULL, 0 );
				DEBUG_PRINT( "Writing 0x%lx to 0x%x.0x%x.0x%x\n",
					     value, node, target, offset );
				ncr_write32( NCP_REGION_ID( node, target ),
					     offset, value );
				offset += 4;
			}
		} else {
			/*
			  Nodes from 0x100 on are "virtual".  Only some are
			  handled!
			*/
			unsigned long base;

			switch( NCP_REGION_ID( node, target ) ) {
			case NCP_REGION_ID( 0x100, 0x4 ):
				base = ( IO + 0xc0000 );
				return_code = 0;
				break;
			default:
				printf( "Unhandled Virtual Region!\n" );
				break;
			}

			if( 0 == return_code ) {
				for( index = 0; index < ( argc - 3 );
				     ++ index ) {
					unsigned long value;

					value =
					  simple_strtoul( argv [ 3 + index ],
							  NULL, 0 );
					DEBUG_PRINT( "Writing 0x%lx to 0x%x." \
						     "0x%x.0x%x <0x%x>\n",
						     value, node, target, offset,
						     ( base + offset ) );
					writel( value, ( base + offset ) );
					offset += 4;
				}
			}
		}

		return_code = 0;
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

U_BOOT_CMD( ncr, 5, 0, do_ncr,
	    "ncr help|read|write [arguments]\n",
	    "h,elp\n" \
	    "r,ead node.target.offset width number\n" \
	    "\tread number values of width bytes from node.target.offset\n" \
	    "w,rite node.target.offset width value\n" \
	    "\twrite value of size width bytes to node.target.offset\n" );


#endif /* CONFIG_ACP */
