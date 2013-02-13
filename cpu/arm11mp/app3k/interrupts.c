/*
 * cpu/arm1136/app3k/interrupts.c
 *
 * (C) Copyright 2008
 * LSI Corporation <www.lsi.com>
 * John Jacques <john.jacques@lsi.com>
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

#include <common.h>
#include <asm/io.h>
#include <config.h>

#define READ_TIMER ( * TIMER0_VALUE )
#define TIMER_LOAD_VALUE TIMER0_LOAD_VALUE

static ulong timestamp;
static ulong lastdec;

/*
  ----------------------------------------------------------------------
  interrupt_init
*/

int interrupt_init( void )
{

  int32_t value_;

  /*
    initialize lastdec and timestamp
  */

  reset_timer_masked( );

  return 0;

}

/*
  ----------------------------------------------------------------------
  reset_timer
*/

void reset_timer( void )
{

  reset_timer_masked( );

}

/*
  ----------------------------------------------------------------------
  get_timer
*/

ulong get_timer( ulong base )
{

  return get_timer_masked( ) - base;

}

/*
  ----------------------------------------------------------------------
  set_timer
*/

void set_timer( ulong new_timestamp )
{

  timestamp = new_timestamp;

}

/*
  ----------------------------------------------------------------------
  udelay

  delay x usecs AND perserve advance timstamp value
*/

void udelay( unsigned long usecs )
{

  ulong tmo_;
  ulong tmp_;

  if( usecs >= 1000 ) {

    /*
      if the delay is large, don't overflow...
    */

    tmo_ = usecs / 1000;
    tmo_ *= CFG_HZ;
    tmo_ /= 1000;

  } else {

    tmo_ = usecs * CFG_HZ;
    tmo_ /= ( 1000 * 1000 );

  }

  tmp_ = get_timer (0);         /* get current timestamp */

  if( ( tmo_ + tmp_ + 1 ) < tmp_ ) {

    /*
      if setting this forward will roll the time stamp reset the
      advancing timestamp to 0 and update lastdec.
    */
     
    reset_timer_masked( );

  } else {

    /*
      set wake up time
    */

    tmo_ += tmp_;

  }

  /*
    loop till event
  */

  while( get_timer_masked( ) < tmo_ ) ;

}

/*
  ----------------------------------------------------------------------
  reset_timer_masked
*/

void reset_timer_masked( void )
{

  /*
    capture the current value of the decrementing timer
  */

  lastdec = readl( TIMER0_VALUE );

  /*
    reset "advancing" timestamp
  */

  timestamp = 0;

}

/*
  ----------------------------------------------------------------------
  get_timer_masked
*/

ulong get_timer_masked (void)
{

  ulong now_ = readl( TIMER0_VALUE );

  if( lastdec >= now_ ) {

    /*
      no roll over
    */

    timestamp += lastdec - now_;

  } else {

    /*
      roll over
    */

    timestamp += lastdec + ( TIMER0_LOAD_VALUE - now_ );

  }

  lastdec = now_;

  return timestamp;

}

/*
  ----------------------------------------------------------------------
  udelay_masked

  waits for the specified delay value and then resets timestamp
*/

void udelay_masked( unsigned long usecs )
{

  ulong tmo_;
  ulong endtime_;
  signed long difference_;

  if( usecs >= 1000 ) {

    /*
      if the delay is large, don't overflow...
    */

    tmo_ = usecs / 1000;
    tmo_ *= CFG_HZ;
    tmo_ /= 1000;

  } else {

    tmo_ = usecs * CFG_HZ;
    tmo_ /= ( 1000 * 1000 );

  }

  endtime_ = get_timer_masked( ) + tmo_;

  do {

    ulong now_ = get_timer_masked( );

    difference_ = endtime_ - now_;

  } while( difference_ >= 0 );

}

/*
  ----------------------------------------------------------------------
  get_ticks

  This function is derived from PowerPC code (read timebase as long
  long).  On ARM it just returns the timer value.

*/

unsigned long long get_ticks( void )
{

  return get_timer( TIMER0_LOAD_VALUE );

}

/*
  ----------------------------------------------------------------------
  get tbclk

  This function is derived from PowerPC code (timebase clock
  frequency).  On ARM it returns the number of timer ticks per second.
*/

ulong get_tbclk( void )
{

  return CFG_HZ;

}

/*
  ----------------------------------------------------------------------
  reset_cpu
*/

void reset_cpu( ulong address )
{

  pll_reset( 0 );

}
