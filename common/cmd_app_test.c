/*
 *  common/cmd_app3_test.c
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

#if CONFIG_COMMANDS

/*
  Debugging...
*/

/*#define CMD_APP3_TEST_DEBUG_*/

#if defined( CMD_APP3_TEST_DEBUG_ )
#define DEBUG_PRINT( format, args... ) do { \
printf( "cmd_app3_test:%s:%d - DEBUG - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else
#define DEBUG_PRINT( format, args... )
#endif

/*
  Warnings...
*/

#define CMD_APP3_TEST_WARN_

#if defined( CMD_APP3_TEST_WARN_ )
#define WARN_PRINT( format, args... ) do { \
printf( "cmd_app3_test:%s:%d - WARN - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else
#define WARN_PRINT( )
#endif

/*
  Errors...
*/

#define ERROR_PRINT( format, args... ) do { \
printf( "cmd_app3_test:%s:%d - ERROR - ",  __FUNCTION__, __LINE__ ); \
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
  ----------------------------------------------------------------------
  apb_
*/

static void apb_( void ) {

  unsigned long index_;
  volatile unsigned long value_;

  printf( "\nRunning the APB test.\n" );

  for( index_ = 0; index_ < 1000000; ++ index_ ) {

    value_ = ( unsigned long ) TIMER0_VALUE;

  }

  return;

}

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
  do_app3_test
*/

int do_app3_test( cmd_tbl_t * command_table, int flag,
                  int argc, char * argv [ ] ) {

  DEBUG_PRINT( "flag=0x%x argc=%d\n", flag, argc );

  if( 0 == strncmp( argv [ 1 ], "apb", strlen( "apb" ) ) ) {

    apb_( );

  } else {

    printf( "%s", command_table->usage );

  }

  /* that's all */
  return 0;

}

/*
  ----------------------------------------------------------------------
*/

U_BOOT_CMD( app3_test, 100, 0, do_app3_test,
	    "app3_test     - run system test\n",
	    "apb -- Run the APB test\n" );

#endif /* CONFIG_COMMANDS */
