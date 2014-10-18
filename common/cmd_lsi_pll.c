/*
 *  common/cmd_pll.c
 *
 *  Copyright (C) 2005 Agere Systems Inc.
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

#ifdef CONFIG_COMMANDS

/*
  Debugging...
*/

/*#define CMD_PLL_DEBUG_*/

#if defined( CMD_PLL_DEBUG_ )
#define DEBUG_PRINT( format, args... ) do { \
printf( "cmd_pll:%s:%d - DEBUG - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else
#define DEBUG_PRINT( format, args... )
#endif

/*
  Warnings...
*/

#define CMD_PLL_WARN_

#if defined( CMD_PLL_WARN_ )
#define WARN_PRINT( format, args... ) do { \
printf( "cmd_pll:%s:%d - WARN - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else
#define WARN_PRINT( )
#endif

/*
  Errors...
*/

#define ERROR_PRINT( format, args... ) do { \
printf( "cmd_pll:%s:%d - ERROR - ",  __FUNCTION__, __LINE__ ); \
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

#define DESCRIPTION_ "pll     - PLL register access\n"

#define USAGE_ \
"display\n" \
" - display registers and clocks, current, next, and environmental\n" \
"pll setup\n" \
" - run the setup algorithm\n" \
"pll equalize\n" \
" - copy the current registers to the next registers\n" \
"pll read offset\n" \
" - read offset\n" \
"pll write offset value\n" \
" - write value to offset" \
"pll reset reconfig\n" \
" - reset the boot loader and reconfigure (if reconfig is non-zero)\n" \
"pll set name frequency\n" \
" - set the given clock or pll to the given\n" \
" - frequency (next registers and environment)"

/*
  ======================================================================
  ======================================================================
  ======================================================================
  Static Functions
  ======================================================================
  ======================================================================
  ======================================================================
*/

/*
  ======================================================================
  ======================================================================
  ======================================================================
  The Command
  ======================================================================
  ======================================================================
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  do_pll
*/
int do_pll( cmd_tbl_t * command_table, int flag, int argc, char * argv [ ] ) {

#ifdef CONFIG_APP3XX

  DEBUG_PRINT( "flag=0x%x argc=%d\n", flag, argc );

  if( 0 == strcmp( argv [ 1 ], "display" ) ) {

    /* pll display */
    pll_display( );

  } else if( 0 == strcmp( argv [ 1 ], "setup" ) ) {

    /* pll setup */
    pll_setup_clocks( );

  } else if( 0 == strcmp( argv [ 1 ], "equalize" ) ) {

    /* pll equalize */
    pll_equalize( );

  } else if( 0 == strcmp( argv [ 1 ], "read" ) ) {

    /* pll read */

    int offset_ = simple_strtoul( argv[ 2 ], NULL, 16 );

    printf( "pll regsiter 0x%02x contains 0x%02x\n",
            offset_, pll_read( offset_ ) );

  } else if( 0 == strcmp( argv [ 1 ], "write" ) ) {

    /* pll write */
    pll_write( simple_strtoul( argv[ 2 ], NULL, 16 ),
               simple_strtoul( argv[ 3 ], NULL, 16 ) );

  } else if( 0 == strcmp( argv [ 1 ], "reset" ) ) {

    /* pll reset */
    pll_reset( simple_strtoul( argv[ 2 ], NULL, 16 ) );

  } else if( 0 == strcmp( argv [ 1 ], "set" ) ) {

    int worked_ = 0;

    DEBUG_PRINT( "pll set ...\n" );

    if( 4 == argc ) {

      unsigned long value_ = simple_strtoul( argv [ 3 ], NULL, 0 );

      /* pll set */

      if( 0 == strcmp( argv [ 2 ], "core" ) ) {

        pll_set_clock( core, value_ );
        worked_ = 1;

      } else if( 0 == strcmp( argv [ 2 ], "ddr" ) ) {

        pll_set_clock( ddr, value_ );
        worked_ = 1;

      } else if( 0 == strcmp( argv [ 2 ], "arm_ddr" ) ) {

        pll_set_clock( arm_ddr, value_ );
        worked_ = 1;

      } else if( 0 == strcmp( argv [ 2 ], "mac" ) ) {

        pll_set_clock( mac, value_ );
        worked_ = 1;
#if defined( LSI_ARCH_APP3K )
      } else if( 0 == strcmp( argv [ 2 ], "axi" ) ) {

        pll_set_clock( axi, value_ );
        worked_ = 1;
#elif defined( LSI_ARCH_APP3 )
      } else if( 0 == strcmp( argv [ 2 ], "arm_core" ) ) {

        pll_set_clock( arm_core, value_ );
        worked_ = 1;

      } else if( 0 == strcmp( argv [ 2 ], "host" ) ) {

        pll_set_clock( host, value_ );
        worked_ = 1;
#else
#error "Unknown Architecture"
#endif
      } else if( 0 == strcmp( argv [ 2 ], "output" ) ) {

        pll_set_clock( output, value_ );
        worked_ = 1;

      } else if( 0 == strcmp( argv [ 2 ], "rmii" ) ) {

        pll_set_clock( rmii, value_ );
        worked_ = 1;

      } else if( 0 == strcmp( argv [ 2 ], "pll_0" ) ) {

        DEBUG_PRINT( "pll set pll_0 %d\n", value_ );
        pll_set_pll( pll_0, value_ );
        worked_ = 1;

      } else if( 0 == strcmp( argv [ 2 ], "pll_1" ) ) {

        DEBUG_PRINT( "pll set pll_1 %d\n", value_ );
        pll_set_pll( pll_1, value_ );
        worked_ = 1;

      }

    }

    if( 0 == worked_ ) {

      printf( "pll set (clock OR pll) name frequency\n" );

    }

  } else {

    printf( "Unknown command: pll %s\n", argv [ 1 ] );

  }

#endif /* CONFIG_APP3XX */

  /* that's all */
  return 0;

}

/*
  ----------------------------------------------------------------------
*/

U_BOOT_CMD( pll, 4, 0, do_pll, DESCRIPTION_, USAGE_ );

#endif /* CONFIG_COMMANDS */
