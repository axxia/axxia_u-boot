/*
 *  common/cmd_membw.c
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

#include <config.h>

#if defined( CONFIG_COMMANDS ) && ! defined( CONFIG_ACP )

#include <common.h>
#include <command.h>

#if defined( LSI_ARCH_APP3 )
#include <configs/app3.h>
#elif defined( LSI_ARCH_APP3K )
#include <configs/app3k.h>
#endif

#include <linux/string.h>

/*
  Debugging...
*/

/*#define CMD_MEMBW_DEBUG_*/

#if defined( CMD_MEMBW_DEBUG_ )
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

#define CMD_MEMBW_WARN_

#if defined( CMD_MEMBW_WARN_ )
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
"membw   - Memory Bandwidth Benchmark\n"

#define USAGE_ \
"address1 address2 size iterations\n" \
" - run one test using the given arguments\n" \
"membw default\n" \
" - run default tests"

typedef struct membw_parameter {

  unsigned long size;
  unsigned long iterations;

} membw_parameter_t;

#define KBYTES *1024

static membw_parameter_t membw_parameters_ [ ] = {

    { 1 KBYTES , 10000000 },
    { 1536     , 10000000 },
    { 2 KBYTES , 10000000 },
    { 3 KBYTES , 10000000 },
    { 4 KBYTES ,  5000000 },
    { 6 KBYTES ,  5000000 },
    { 8 KBYTES ,  2000000 },
    { 12 KBYTES , 2000000 },
    { 16 KBYTES , 1000000 },
    { 24 KBYTES , 1000000 },
    { 32 KBYTES ,  500000 },
    { 48 KBYTES ,  500000 },
    { 64 KBYTES ,  200000 },
    { 96 KBYTES ,  200000 },
    { 128 KBYTES , 100000 },
    { 192 KBYTES , 100000 },
    { 256 KBYTES ,  50000 },
    { 384 KBYTES ,  50000 },
    { 512 KBYTES ,  20000 },
    { 768 KBYTES ,  20000 },
    { 1024 KBYTES , 10000 },
    { 1536 KBYTES , 10000 },
    { 2048 KBYTES ,  5000 },
    { 3072 KBYTES ,  5000 },
    { 4096 KBYTES ,  2000 },
    { 6144 KBYTES ,  2000 },
    { 8192 KBYTES ,  1000 },
    { 12288 KBYTES , 1000 },
    { 16384 KBYTES ,  500 }

};

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
  membw
*/

void membw( void * address1, void * address2,
            unsigned long size, unsigned long iterations )
{

  unsigned long index_;
  void * source_;
  void * destination_;
  inumber_t iticks;
  inumber_t ihz;
  inumber_t itime;
  inumber_t isize;
  inumber_t irate;
  inumber_t temp1_;
  inumber_t temp2_;

  source_ = address1;
  destination_ = address2;
  reset_timer( );

  for( index_ = 0; index_ < iterations; ++ index_ ) {

    void * temp_;

    memcpy( destination_, source_, size );
    temp_ = source_;
    source_ = destination_;
    destination_ = temp_;

  }

  iticks.value = get_timer( 0 );
  iticks.shifted = 0;
  ihz.value = CFG_HZ;
  ihz.shifted = 0;
  temp1_.value = size;
  temp1_.shifted = 0;
  temp2_.value = iterations;
  temp2_.shifted = 0;
  imultiply( & temp1_, & temp2_, & isize );
  idivide( & iticks, & ihz, & itime );
  idivide( & isize, & itime, & temp1_ );
  temp2_.value = 1024;
  temp2_.shifted = 0;
  idivide( & temp1_, & temp2_, & irate );
  temp1_.value = itime.value;
  temp1_.shifted = itime.shifted;
  temp2_.value = 1000;
  temp2_.shifted = 0;
  imultiply( & temp1_, & temp2_, & itime );

  printf( "size %lu iterations %lu time %lu msec rate %lu Kbyte/sec\n",
          size, iterations, IVALUE( & itime ), IVALUE( & irate ) );

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
  do_membw
*/

int do_membw( cmd_tbl_t * command_table, int flag, int argc, char * argv [ ] ) {

  DEBUG_PRINT( "flag=0x%x argc=%d\n", flag, argc );

  if( 5 == argc ) {

    unsigned long address1;
    unsigned long address2;
    unsigned long size;
    unsigned long iterations;

    address1 = simple_strtoul( argv [ 1 ], NULL, 0 );
    address2 = simple_strtoul( argv [ 2 ], NULL, 0 );
    size = simple_strtoul( argv [ 3 ], NULL, 0 );
    iterations = simple_strtoul( argv [ 4 ], NULL, 0 );
    DEBUG_PRINT( "address1=0x%x address2=0x%x size=0x%x/%d iterations=%d\n",
                 address1, address2, size, size, iterations );
    membw( ( void * ) address1, ( void * ) address2, size, iterations );

  } else if( 2 == argc ) {

    unsigned long address1_ = 0x10000;
    unsigned long address2_ = 0x2000000;

    if( 0 == strncmp( argv [ 1 ], "d", strlen( "d" ) ) ) {

      int index_;

      for( index_ = 0;
           index_ < ( sizeof(  membw_parameters_ ) /
                      sizeof( membw_parameter_t ) );
           ++ index_ ) {

        membw( ( void * ) address1_, ( void * ) address2_,
               ( membw_parameters_ [ index_ ] ).size,
               ( membw_parameters_ [ index_ ] ).iterations );

      }

    }

  } else {

    printf( "%s", USAGE_ );

  }

  /* that's all */
  return 0;

}

/*
  ----------------------------------------------------------------------
*/

U_BOOT_CMD( membw, 100, 0, do_membw, DESCRIPTION_, USAGE_ );

#endif /* CONFIG_COMMANDS */
