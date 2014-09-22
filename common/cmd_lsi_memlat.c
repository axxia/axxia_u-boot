/*
 *  common/cmd_memlat.c
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

/*#define CMD_MEMLAT_DEBUG_*/

#if defined( CMD_MEMLAT_DEBUG_ )
#define DEBUG_PRINT( format, args... ) do { \
printf( "cmd_memlat:%s:%d - DEBUG - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else
#define DEBUG_PRINT( format, args... )
#endif

/*
  Warnings...
*/

#define CMD_MEMLAT_WARN_

#if defined( CMD_MEMLAT_WARN_ )
#define WARN_PRINT( format, args... ) do { \
printf( "cmd_memlat:%s:%d - WARN - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else
#define WARN_PRINT( )
#endif

/*
  Errors...
*/

#define ERROR_PRINT( format, args... ) do { \
printf( "cmd_memlat:%s:%d - ERROR - ",  __FUNCTION__, __LINE__ ); \
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
"memlat  - Memory Latency Benchmark\n"

#define USAGE_ \
"address length iterations\n" \
" - run the given test\n" \
"memlat default\n" \
" - run default tests"

typedef struct memlat_parameter {

  unsigned long length;
  unsigned long iterations;

} memlat_parameter_t;

#define KBYTES *1024

static memlat_parameter_t memlat_parameters_ [ ] = {

  { 256,  5000000 },
  { 384,  5000000 },
  { 512,  2000000 },
  { 768,  2000000 },              
  { 1 KBYTES , 1000000 },
  { 1536, 1000000 },         
  { 2 KBYTES , 500000 },
  { 3 KBYTES,  500000 },       
  { 4 KBYTES , 500000 },
  { 6 KBYTES , 200000 },
  { 8 KBYTES , 200000 },
  { 12 KBYTES ,100000 },
  { 16 KBYTES , 50000 },
  { 24 KBYTES , 20000 },
  { 32 KBYTES , 20000 },
  { 48 KBYTES , 10000 },
  { 64 KBYTES , 10000 },
  { 96 KBYTES ,  5000 },
  { 128 KBYTES , 5000 },
  { 192 KBYTES , 2000 },
  { 256 KBYTES , 1000 },
  { 384 KBYTES , 1000 },
  { 512 KBYTES ,  500 },
  { 768 KBYTES ,  200 },
  { 1024 KBYTES , 100 },
  { 1536 KBYTES ,  50 },
  { 2048 KBYTES ,  20 },
  { 3072 KBYTES ,  20 },
  { 4096 KBYTES ,  10 },
  { 6144 KBYTES ,  10 },
  { 8192 KBYTES ,  10 }

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
  initialize_list
*/

#define LARGE_NUMBER 0xffffabcd

static void initialize_list( void * address, unsigned long length ) {

  int index_;
  void * * list;

  list = address;
  list [ 0 ] = NULL;

  for( index_ = 1; length > index_; ++ index_ ) {

    /*
      Each element should be inserted at a pseudorandom location.  In
      order to make the traversal sequence platform independent, the
      call to rand() is replaced by a constant. Reasoning: since n is
      each time increasing, the series of insertion points will be
      weakly ordered.
    */
        
    unsigned long insertion_point_ = LARGE_NUMBER % index_;
    list [ index_ ] = list [ insertion_point_ ];
    list [ insertion_point_ ] = & ( list [ index_ ] );

  }

}

/*
  ----------------------------------------------------------------------
  list_length_test
*/

static void list_length_test( void * address, unsigned long length,
                              unsigned long iterations ) {

  unsigned long index_;

  for( index_ = 0; index_ < iterations; ++ index_ ) {

    unsigned long count_ = 1;
    void * * list = address;

    while( * list != NULL ) {

      list = * list;
      ++ count_;

    }

    if( count_ != length ) {

      ERROR_PRINT( "Error in length calculation!\n" );
      return;

    }

  }

  return;

}

/*
  ----------------------------------------------------------------------
*/

void memlat( void * address, unsigned long length, unsigned long iterations ) {

  inumber_t iticks;
  inumber_t ihz;
  inumber_t itime;
  inumber_t itransactions;
  inumber_t irate;

  initialize_list( address, length );
  reset_timer( );
  list_length_test( address, length, iterations );
  iticks.value = get_timer( 0 );
  iticks.shifted = 0;
  ihz.value = CFG_HZ;
  ihz.shifted = 0;
  idivide( & iticks, & ihz, & itime );
  itransactions.value = length * iterations;
  itransactions.shifted = 0;

  {

    inumber_t temp1_;
    inumber_t temp2_;

    idivide( & itime, & itransactions, & temp1_ );
    temp2_.value = 1000000000;
    temp2_.shifted = 0;
    imultiply( & temp1_, & temp2_, & irate );

    temp1_.value = itime.value;
    temp1_.shifted = itime.shifted;
    temp2_.value = 1000;
    temp2_.shifted = 0;
    imultiply( & temp1_, & temp2_, & itime );

  }

  printf( "length %lu iterations %lu time %lu msec rate %lu nsec/transaction\n",
          length, iterations, IVALUE( & itime ), IVALUE( & irate ) );

  /* that's all */
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
  do_memlat
*/

int do_memlat( cmd_tbl_t * command_table, int flag,
                   int argc, char * argv [ ] ) {

  DEBUG_PRINT( "flag=0x%x argc=%d\n", flag, argc );

  if( 4 == argc ) {

    unsigned long address;
    unsigned long length;
    unsigned long iterations;

    address = simple_strtoul( argv [ 1 ], NULL, 0 );
    length = simple_strtoul( argv [ 2 ], NULL, 0 );
    iterations = simple_strtoul( argv [ 3 ], NULL, 0 );
    DEBUG_PRINT( "address=0x%x length=0x%x/%d iterations=%d\n",
                 address, length, length, iterations );
    memlat( ( void * ) address, length, iterations );

  } else if( 2 == argc ) {

    unsigned long address_ = 0x2000000;

    if( 0 == strncmp( argv [ 1 ], "d", strlen( "d" ) ) ) {

      int index_;

      for( index_ = 0;
           index_ < ( sizeof(  memlat_parameters_ ) /
                      sizeof( memlat_parameter_t ) );
           ++ index_ ) {

        memlat( ( void * ) address_,
                ( memlat_parameters_ [ index_ ] ).length,
                ( memlat_parameters_ [ index_ ] ).iterations );

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

U_BOOT_CMD( memlat, 100, 0, do_memlat, DESCRIPTION_, USAGE_ );

#endif /* CONFIG_COMMANDS */
