/*
 * (C) Copyright 2008
 * LSI <www.lsi.com>
 * John Jacques <john.jacques@lsi.com>
 * Configuration settings for the LSI APP development boards.
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

#include <common.h>
#include <config.h>
#include <asm/io.h>

/*
  Debug
*/

#undef DEBUG
/*#define DEBUG*/
#if defined( DEBUG )
#define DEBUG_PRINT( format, args... ) do { \
printf( "pll:%s:%d - DEBUG - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else
#define DEBUG_PRINT( format, args... )
#endif

/*
  Warnings...
*/

#undef WARN
#define WARN
#if defined( WARN )
#define WARN_PRINT( format, args... ) do { \
printf( "pll:%s:%d - WARN - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else
#define WARN_PRINT( )
#endif

/*
  Errors...
*/

#define ERROR_PRINT( format, args... ) do { \
printf( "pll:%s:%d - ERROR - ",  __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );

#define read_watchdog_( offset ) \
( * ( ( volatile unsigned long * ) ( APP3XX_TIMER4_BASE + offset ) ) )

#define write_watchdog_( value, offset ) do { \
( ( * ( ( volatile unsigned long * ) ( APP3XX_TIMER4_BASE + offset ) ) ) = \
  ( unsigned long ) value ); \
} while( 0 );

static unsigned long count_ = 0;

/*
  ----------------------------------------------------------------------
  watchdog_initialize
*/

int watchdog_initialize( void ) {

  int return_code_ = 0;
  int timeout_;
  unsigned long control_ = 0;
  char * timeout_string_;

  DEBUG_PRINT( "Getting watchdog_timeout from the environment...\n" );
  timeout_string_ = getenv( "watchdog_timeout" );

  if( ( ( uchar * ) 0 == timeout_string_ ) ) {

    printf( "watchdog_timeout not set, setting to default.\n" );
    timeout_ = 0;

  } else {

    timeout_ = simple_strtoul( timeout_string_, NULL, 0 );

  }

  DEBUG_PRINT( "watchdog timeout is %d seconds.\n", timeout_ );

  /*
    The clock is driven by the ARM core.  With "prescaler" set to
    0x8, this gets divided by 256.  Each tick will be ( 256 / core
    clock ) seconds.  The desired timeout value will be ( count * (
    256 / core clock ) ).  To calculate the count, use ( timeout * (
    core clock / 256 ) ).
  */

#if defined LSI_ARCH_APP3K

  if( 0 != timeout_ ) {

    count_ = ( timeout_ * ( pll_get_clock( axi ) / 255 ) );
    __raw_writel( 0, ( CONFIG_RESET_PMR_BASE + 0x728 ) );
    __raw_writel( count_, ( CONFIG_RESET_PMR_BASE + 0x724 ) );
    control_ = 0x9 | ( 0xff << 8 );
    __raw_writel( control_, ( CONFIG_RESET_PMR_BASE + 0x728 ) );

  } else {

    __raw_writel( 0, ( CONFIG_RESET_PMR_BASE + 0x728 ) );

  }

#elif defined LSI_ARCH_APP3

  if( 2 <= APP3XX_REVISION ) {

    if( 0 != timeout_ ) {

      count_ = ( timeout_ * ( pll_get_clock( arm_core ) / 256 ) );
      write_watchdog_( 0, TIMER_CONTROL_OFFSET );
      write_watchdog_( count_, TIMER_LOAD_OFFSET );
      control_ = ( TIMER_CONTROL_ENABLE |
                   TIMER_CONTROL_SIZE |
                   TIMER_CONTROL_INTERRUPT_ENABLE |
                   0x8 );           /* Precount (divide by 256) */
      write_watchdog_( control_, TIMER_CONTROL_OFFSET );

    } else {

      write_watchdog_( 0, TIMER_CONTROL_OFFSET );

    }

  } else {

    WARN_PRINT( "Watchdog is only available on revision 2 or greater parts\n" );
    return_code_ = -1;

  }

#endif

  DEBUG_PRINT( "Watchdog Initialized\n" );
  return return_code_;

}

/*
  ----------------------------------------------------------------------
  watchdog_finalize
*/

void watchdog_finalize( void ) {

#if defined LSI_ARCH_APP3K
  __raw_writel( 0x12345678, ( CONFIG_RESET_PMR_BASE + 0x734 ) );
  __raw_writel( 0x87654321, ( CONFIG_RESET_PMR_BASE + 0x734 ) );
#elif defined LSI_ARCH_APP3
  write_watchdog_( 0, TIMER_CONTROL_OFFSET );
#endif
  DEBUG_PRINT( "Finalizing watchdog( )\n" );

  /* that's all */
  return;

}

/*
  ----------------------------------------------------------------------
  watchdog_slap
*/

void watchdog_slap( void ) {

#if defined LSI_ARCH_APP3K
  __raw_writel( count_, ( CONFIG_RESET_PMR_BASE + 0x724 ) );
#elif defined LSI_ARCH_APP3
  write_watchdog_( count_, TIMER_LOAD_OFFSET );
#endif

  return;

}

/*
  ----------------------------------------------------------------------
  watchdog_flag_get
*/

int watchdog_flag_get( void ) {

  int flag_;

#if defined LSI_ARCH_APP3K

  flag_ = ( __raw_readl( ( CONFIG_RESET_PMR_BASE + 0x730 ) ) & 0x1 );

#elif defined LSI_ARCH_APP3

  flag_ = ( 0 ==
            ( __raw_readl( CONFIG_NORMAL_HB_CONF_BASE + 0x4 ) & 0x80000000 ) );

#endif  /* LSI_ARCH_APP3 */

  return flag_;

}

/*
  ----------------------------------------------------------------------
  watchdog_flag_clear
*/

void watchdog_flag_clear( void ) {

#if defined LSI_ARCH_APP3K

  __raw_writel( 0x1, CONFIG_RESET_PMR_BASE + 0x730 );

#elif defined LSI_ARCH_APP3

  unsigned long temp_;

  temp_ = __raw_readl( CONFIG_NORMAL_HB_CONF_BASE );
  temp_ |= 0x800;
  __raw_writel( temp_, CONFIG_NORMAL_HB_CONF_BASE );
  temp_ &= ~ 0x800;
  __raw_writel( temp_, CONFIG_NORMAL_HB_CONF_BASE );

#endif

}
