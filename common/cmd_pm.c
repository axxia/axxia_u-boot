/*
 *  common/cmd_pm.c
 *
 *  Copyright (C) 2007 LSI
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
#include <config.h>
#include <linux/string.h>

#if CONFIG_COMMANDS

/*
  Debugging...
*/

#undef DEBUG
#define DEBUG

#if defined( DEBUG )
#define DEBUG_PRINT( format, args... ) do { \
printf( "cmd_membw:%s:%d - DEBUG - ", __FUNCTION__, __LINE__ ); \
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
printf( "cmd_membw:%s:%d - WARN - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else
#define WARN_PRINT( )
#endif

/*
  Errors...
*/

#define ERROR_PRINT( format, args... ) do { \
printf( "cmd_membw:%s:%d - ERROR - ",  __FUNCTION__, __LINE__ ); \
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

#define DESCRIPTION_ \
"pm      - Performance Monitoring\n"

#define USAGE_ \
"start -- parameter parameter\n" \
"stop  -- \n"

#define CONTROL_REGISTER 0
#define CYCLE_COUNTER 1
#define COUNT_0 2
#define COUNT_1 3

typedef union {

  unsigned long raw;

  struct {

    unsigned long           : 4;
    unsigned long EvtCount1 : 8;
    unsigned long EvtCount0 : 8;
    unsigned long           : 1;
    unsigned long Flag      : 3;
    unsigned long           : 1;
    unsigned long IntEn     : 3;
    unsigned long D         : 1;
    unsigned long C         : 1;
    unsigned long E         : 1;
    unsigned long P         : 1;

  } __attribute__ ( ( packed ) ) bits;

} pm_control_t;

#if 0
static unsigned long parameter1;
static unsigned long parameter2;
#endif

/*
  ======================================================================
  ======================================================================
  ======================================================================
  Local Functions
  ======================================================================
  ======================================================================
  ======================================================================
*/

#ifdef AGERE_ARCH_APP3K

/*
  ----------------------------------------------------------------------
  read_pm
*/

static unsigned long read_pm( int opcode_2 ) {

  unsigned long value;

  switch( opcode_2 ) {

  case 0:
    __asm__ __volatile__ ( "mrc p15,0,%0,c15,c12,0\n"
                           : "=r" (value)
                           :
                           : "memory" );
    break;

  case 1:
    __asm__ __volatile__ ( "mrc p15,0,%0,c15,c12,1\n"
                           : "=r" (value)
                           :
                           : "memory" );
    break;

  case 2:
    __asm__ __volatile__ ( "mrc p15,0,%0,c15,c12,2\n"
                           : "=r" (value)
                           :
                           : "memory" );
    break;

  case 3:
    __asm__ __volatile__ ( "mrc p15,0,%0,c15,c12,3\n"
                           : "=r" (value)
                           :
                           : "memory" );
    break;

  default:
    ERROR_PRINT( "Invalid Opcode_2\n" );
    break;

  }

  return value;

}

/*
  ----------------------------------------------------------------------
  write_pm
*/

static void write_pm( int opcode_2, unsigned long value ) {

  switch( opcode_2 ) {

  case 0:
    __asm__ __volatile__ ( "mcr p15,0,%0,c15,c12,0\n"
                           : "=r" (value)
                           :
                           : "memory" );
    break;

  case 1:
    __asm__ __volatile__ ( "mcr p15,0,%0,c15,c12,1\n"
                           : "=r" (value)
                           :
                           : "memory" );
    break;

  case 2:
    __asm__ __volatile__ ( "mcr p15,0,%0,c15,c12,2\n"
                           : "=r" (value)
                           :
                           : "memory" );
    break;

  case 3:
    __asm__ __volatile__ ( "mcr p15,0,%0,c15,c12,3\n"
                           : "=r" (value)
                           :
                           : "memory" );
    break;

  default:
    ERROR_PRINT( "Invalid Opcode_2\n" );
    break;

  }

  return;

}

#endif /* AGERE_ARCH_APP3K */

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
  do_pm
*/

int do_pm( cmd_tbl_t * command_table, int flag, int argc, char * argv [ ] ) {

#ifdef AGERE_ARCH_APP3K

  DEBUG_PRINT( "flag=0x%x argc=%d\n", flag, argc );

  {

    printf( "0x%x\n", read_pm( 0 ) );
    printf( "0x%x\n", read_pm( 1 ) );
    printf( "0x%x\n", read_pm( 2 ) );

  }

#if 0

  if( ( 0 == strncmp( argv [ 1 ], "sta", strlen( "sta" ) ) ) &&
      ( 4 == argc ) ) {

    parameter1 = simple_strtoul( argv [ 1 ], NULL, 0 );
    parameter2 = simple_strtoul( argv [ 2 ], NULL, 0 );

  } else if( ( 0 == strncmp( argv [ 1 ], "sto", strlen( "sto" ) ) ) &&
             ( 2 == argc ) ) {
  } else {

    printf( "%s", USAGE_ );

  }

#endif

#endif /* AGERE_ARCH_APP3K */

  /* that's all */
  return 0;

}

/*
  ----------------------------------------------------------------------
*/

U_BOOT_CMD( pm, 100, 0, do_pm, DESCRIPTION_, USAGE_ );

#endif /* CONFIG_COMMANDS */
