/*
 *  common/cmd_defect.c
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
#include <asm/io.h>
#include <malloc.h>

#if CONFIG_COMMANDS

/*
  Debugging...
*/

#undef DEBUG
/*#define DEBUG*/
#if defined( DEBUG )
#define DEBUG_PRINT( format, args... ) do { \
printf( "cmd_defect:%s:%d - DEBUG - ", __FUNCTION__, __LINE__ ); \
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
printf( "cmd_defect:%s:%d - WARN - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else
#define WARN_PRINT( format, args... )
#endif

/*
  Errors...
*/

#define ERROR_PRINT( format, args... ) do { \
printf( "cmd_defect:%s:%d - ERROR - ",  __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );

/*
  ======================================================================
  ======================================================================
  ======================================================================
  template
  ======================================================================
  ======================================================================
  ======================================================================
*/

#define DEFECT_TEMPLATE
#ifdef DEFECT_TEMPLATE

static const char defect_template_name [ ] = "template";

static void defect_template( int argc, char * argv [ ] ) {

  DEBUG_PRINT( "Handling %d arguments.\n", argc );

  return;

}

#endif

/*
  ======================================================================
  ======================================================================
  ======================================================================
  unknown
  ======================================================================
  ======================================================================
  ======================================================================
*/

#define DEFECT_UNKNOWN
#ifdef DEFECT_UNKNOWN

static const char defect_unknown_name [ ] = "unknown";

static void defect_unknown( int argc, char * argv [ ] ) {

  if( 4 == argc ) {

    unsigned long address_;
    unsigned long size_;
    unsigned long pattern_;
    unsigned long scratch_save_;

    address_ = simple_strtoul( argv [ 1 ], NULL, 0 );
    size_ = simple_strtoul( argv [ 2 ], NULL, 0 );
    pattern_ = simple_strtoul( argv [ 3 ], NULL, 0 );
    DEBUG_PRINT( "Running the unknown test at 0x%08x, 0x%x bytes.\n",
                 address_, size_ );
    scratch_save_ = __raw_readl( CONFIG_NORMAL_AEI_BASE + 0x14 );

    /* fill with writes to scratch */

    {

      unsigned long index_;

      for( index_ = address_; index_ < ( address_ + size_ ); index_ += 4 ) {

        * ( ( unsigned long * ) ( index_ ) ) = pattern_;
        __raw_writel( index_, ( CONFIG_NORMAL_AEI_BASE + 0x14 ) );

      }

    }

    /* compare */

    {

      unsigned long index_;

      for( index_ = address_; index_ < ( address_ + size_ ); index_ += 4 ) {

        if( pattern_ != * ( ( unsigned long * ) ( index_ ) ) ) {

          ERROR_PRINT( "Test failed at 0x%x!  0x%x != 0x%x\n",
                       index_, pattern_, * ( ( unsigned long * ) ( index_ ) ) );

        }

      }

    }

    __raw_writel( scratch_save_, ( CONFIG_NORMAL_AEI_BASE + 0x14 ) );

  } else {

    ERROR_PRINT( "Usage: defect unknown address size pattern\n" );

  }

  return;

}

#endif

/*
  ======================================================================
  ======================================================================
  ======================================================================
  memcpy
  ======================================================================
  ======================================================================
  ======================================================================
*/

#define DEFECT_MEMCPY
#ifdef DEFECT_MEMCPY

static const char defect_memcpy_name [ ] = "memcpy";

static void defect_memcpy( int argc, char * argv [ ] ) {

  unsigned char address_ [ 8 ] =
    { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88  };
  void * buffer_;

  buffer_ = malloc( 2 * sizeof( unsigned long ) );
  memcpy( buffer_, address_, 8 );
  printf( "%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
          ( ( unsigned char * ) buffer_ ) [ 0 ],
          ( ( unsigned char * ) buffer_ ) [ 1 ],
          ( ( unsigned char * ) buffer_ ) [ 2 ],
          ( ( unsigned char * ) buffer_ ) [ 3 ],
          ( ( unsigned char * ) buffer_ ) [ 4 ],
          ( ( unsigned char * ) buffer_ ) [ 5 ],
          ( ( unsigned char * ) buffer_ ) [ 6 ],
          ( ( unsigned char * ) buffer_ ) [ 7 ] );
  printf( "0x%08x 0x%08x\n",
          ( ( unsigned long * ) buffer_ ) [ 0 ],
          ( ( unsigned long * ) buffer_ ) [ 1 ] );
  free( buffer_ );

  return;

}

#endif

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
  do_defect
*/

int do_defect( cmd_tbl_t * command_table, int flag,
               int argc, char * argv [ ] ) {

  int new_argc_;
  char * * new_argv_;

  DEBUG_PRINT( "flag=0x%x argc=%d\n", flag, argc );
  new_argc_ = argc - 1;
  new_argv_ = & ( argv [ 1 ] );

  /*
    ======================================================================
    template
  */

#ifdef DEFECT_TEMPLATE

  if( 0 == strncmp( argv [ 1 ],
                    defect_template_name,
                    strlen( defect_template_name ) ) ) {

    defect_template( new_argc_, new_argv_ );
    return 0;

  }

#endif /* DEFECT_TEMPLATE */

  /*
    ======================================================================
    unknown
  */

#ifdef DEFECT_UNKNOWN

  if( 0 == strncmp( argv [ 1 ],
                    defect_unknown_name,
                    strlen( defect_unknown_name ) ) ) {

    defect_unknown( new_argc_, new_argv_ );
    return 0;

  }

#endif /* DEFECT_UNKNOWN */

  /*
    ======================================================================
    memcpy
  */

#ifdef DEFECT_MEMCPY

  if( 0 == strncmp( argv [ 1 ],
                    defect_memcpy_name,
                    strlen( defect_memcpy_name ) ) ) {

    defect_memcpy( new_argc_, new_argv_ );
    return 0;

  }

#endif /* DEFECT_MEMCPY */

  printf( "%s\n", command_table->usage );

  /* that's all */
  return 0;

}

/*
  ----------------------------------------------------------------------
*/

U_BOOT_CMD( defect, 100, 0, do_defect,
	    "defect  - illustrate various defects.\n",
	    "Rebuild U-Boot with the indicated defect defined in common/cmd_defect.c" );
#endif /* CONFIG_COMMANDS */
