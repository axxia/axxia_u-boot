/*
 *  common/cmd_lsi_ecc.c
 *
 *  Copyright (C) 2006 Agere Systems Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <common.h>
#include <command.h>
#include <configs/app3.h>
#include <linux/string.h>

#ifdef CONFIG_COMMANDS

/*
  Debugging...
*/

/*#define CMD_ECC_DEBUG_*/

#if defined( CMD_ECC_DEBUG_ )
#define DEBUG_PRINT( format, args... ) do { \
printf( "cmd_ecc:%s:%d - DEBUG - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else
#define DEBUG_PRINT( format, args... )
#endif

/*
  Warnings...
*/

#define CMD_ECC_WARN_

#if defined( CMD_ECC_WARN_ )
#define WARN_PRINT( format, args... ) do { \
printf( "cmd_ecc:%s:%d - WARN - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else
#define WARN_PRINT( )
#endif

/*
  Errors...
*/

#define ERROR_PRINT( format, args... ) do { \
printf( "cmd_ecc:%s:%d - ERROR - ",  __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );

/*
  ======================================================================
  ======================================================================
  ======================================================================
  Globals
  ======================================================================
  ======================================================================
  ======================================================================
*/

/*
  ======================================================================
  ======================================================================
  ======================================================================
  Local Functions
  ======================================================================
  ======================================================================
  ======================================================================
*/

/*
  ======================================================================
  ======================================================================
  ======================================================================
  Global Functions
  ======================================================================
  ======================================================================
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  do_ecc
*/

int do_ecc( cmd_tbl_t * command_table, int flag, int argc, char * argv [ ] ) {

#ifdef CONFIG_APP3XX

  DEBUG_PRINT( "flag=0x%x argc=%d\n", flag, argc );

  if( 1 == argc ) {

    /* Display the current state */

    printf( "ECC State: 0x%08x/0x%08x/0x%08x\n",
            * ( ( volatile unsigned long * ) 0x58000020 ),
            * ( ( volatile unsigned long * ) 0x58000018 ),
            * ( ( volatile unsigned long * ) 0x5800001c ) );

  } else if( 0 == strncmp( argv [ 1 ], "d", strlen( "d" ) ) ) {

    /* Disable ECC */

    * ( ( volatile unsigned long * ) 0x58000020 ) = 0;

  } else if( 0 == strncmp( argv [ 1 ], "e", strlen( "e" ) ) ) {

    /* Enable ECC */

    * ( ( volatile unsigned long * ) 0x58000020 ) |= 0x10;

  } else {

    printf( "%s", command_table->usage );

  }

#endif /* CONFIG_APP3XX */

  /* that's all */
  return 0;

}

/*
  ----------------------------------------------------------------------
*/

U_BOOT_CMD( ecc, 100, 0, do_ecc,
	    "ecc     - ECC control\n",
	    "           - Display the current ECC state\n" \
	    "d,isable   - Disable ECC\n" \
	    "e,nable    - Enable ECC\n" );

#endif /* CONFIG_COMMANDS */
