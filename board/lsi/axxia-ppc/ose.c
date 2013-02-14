/*
 * ose.c
 *
 * Copyright (C) 2010 LSI Corporation
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <config.h>

#ifdef CONFIG_ACP3

#include <common.h>

#undef DEBUG
/*#define DEBUG*/
#if defined( DEBUG )
#define DEBUG_PRINT( format, args... ) do { \
printf( "%s:%d - ", __FILE__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else
#define DEBUG_PRINT( format, args... )
#endif

/*
  ==============================================================================
  ==============================================================================
  Public Interface
  ==============================================================================
  ==============================================================================
*/

/*
  ------------------------------------------------------------------------------
  ose_add_string
*/

int
ose_add_string( int core, const char * input )
{
	char * output;
	int index;

	switch( core ) {
	case 0:
		output = ( char * ) ( 0x1000 );
		break;
	case 1:
		output = ( char * ) ( 0x1400 );
		break;
	case 2:
		output = ( char * ) ( 0x1800 );
		break;
	case 3:
		output = ( char * ) ( 0x1c00 );
		break;
	default:
		return -1;
		break;
	}

	index = OSE_STRINGS_SIZE;

	while( ( 0 == output [index ] ) && ( 0 < index ) ) {
		-- index;
	}

	if( 0 != index ) {
		index += 2;
	}

	strcpy( ( char * ) & ( output [ index ] ), input );
	index += strlen( input );
	output [ index ] = 0;

	return 0;
}

/*
  ------------------------------------------------------------------------------
  ose_init
*/

int
ose_init( void )
{
	memset( ( void * ) ( 0x1000 ), 0, OSE_STRINGS_SIZE * 4 );
	return 0;
}

#endif /* CONFIG_ACP3 */
