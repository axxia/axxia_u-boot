/*
 * (C) Copyright 2008
 * LSI <www.lsi.com>
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
#include <config.h>
#include <asm/io.h>

/*
  Debugging...
*/

#undef DEBUG
/*#define DEBUG*/
#if defined( DEBUG )
#define DEBUG_PRINT( format, args... ) do { \
printf( "phy:%s:%d - DEBUG - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else
#define DEBUG_PRINT( format, args... )
#endif

/*
  Warnings...
*/

#define PHY_WARN_

#if defined( PHY_WARN_ )
#define WARN_PRINT( format, args... ) do { \
printf( "phy:%s:%d - WARN - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else
#define WARN_PRINT( )
#endif

/*
  Errors...
*/

#define ERROR_PRINT( format, args... ) do { \
printf( "phy:%s:%d - ERROR - ",  __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );

/*
  ======================================================================
  Globals
  ======================================================================
*/

#define mb( ) __asm__ __volatile__ ( "" : : : "memory" )

/*
  ======================================================================
  Implementation of the Interface Defined in include/configs/app3xx.h
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  phy_read

  Returns -1 if unsuccessful, the (short) value otherwise.
*/

int phy_read( int phy, int reg, unsigned short * value, int delay ) {

  int return_code_ = -1;
  unsigned long command_;
  volatile unsigned long status_;

  /*
    ++ Defect Workaround ++

    See 14809 for v1.x and 18016 v2.0

    Sometimes the MDIO_STAT_ACK bit is already set before starting a
    read.  This bit should be cleared by reading (as in the loop that
    checks for it below).  Reading the bit before starting the read (by
    writing the read command to the command register) keeps the following
    code from thinking the read is complete prematurly).

    To use the 'phy test' command (see common/cmd_phy.c) comment out the
    following read!
  */

  status_ = __raw_readl( MDIO_STAT );

  command_ =
    ( MDIO_CMD_TYPE_MDIO | MDIO_CMD_OP_READ | ( phy << 4 ) | ( reg << 9 ) );
  __raw_writel( command_, MDIO_CMD );
  mb( );

  do {

    status_ = __raw_readl( MDIO_STAT );

  } while( 0 == ( status_ & MDIO_STAT_ACK ) );

  /* Once the acknowledge bit is set (without an error) read the data. */
  if( 0 == ( status_ & MDIO_STAT_ERR ) ) {

    /*
      Once upon a time there was a defect (14809) which required, as a
      work around, a delay of something like 1 msecs here...

      The delay argument is ONLY FOR TESTING.
    */

    if( 0 != delay ) { udelay( delay ); }

    * value = __raw_readl( MDIO_DATA );
    return_code_ = 0;

  }

  if( 0 != return_code_ ) {

    DEBUG_PRINT( "PHY read failed: phy=0x%x reg=0x%x command_=0x%x\n",
                 phy, reg, command_ );

  }

  /* that's all */
  return return_code_;

}

/*
  ----------------------------------------------------------------------
  phy_write
*/

int phy_write( int phy, int reg, unsigned short value ) {

  int return_code_ = -1;
  unsigned long command_;
  volatile unsigned long status_;

  /*
    ++ Defect Workaround ++

    See 14809 for v1.x and 18016 v2.0

    Sometimes the MDIO_STAT_ACK bit is already set before starting a
    read.  This bit should be cleared by reading (as in the loop that
    checks for it below).  Reading the bit before starting the read (by
    writing the read command to the command register) keeps the following
    code from thinking the read is complete prematurly).

    To use the 'phy test' command (see common/cmd_phy.c) comment out the
    following read!
  */

  status_ = __raw_readl( MDIO_STAT );

  __raw_writel( value, MDIO_DATA );
  mb( );
  command_ =
    ( MDIO_CMD_TYPE_MDIO | MDIO_CMD_OP_WRITE | ( phy << 4 ) | ( reg << 9 ) );
  __raw_writel( command_, MDIO_CMD );
  mb( );

  do {

    status_ = __raw_readl( MDIO_STAT );

  } while( 0 == ( status_ & MDIO_STAT_ACK ) );

  if( 0 == ( status_ & MDIO_STAT_ERR ) ) {

    return_code_ = 0;

  }

  if( 0 != return_code_ ) {

    WARN_PRINT( "PHY write failed: phy=0x%x reg=0x%x value=0x%x\n",
                phy, reg, value );

  }

  /* That's all */
  return return_code_;

}
