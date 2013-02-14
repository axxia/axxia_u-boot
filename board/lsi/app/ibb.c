/*
  ibb.c

  Hooks for the RTE functions required by the "In Band Boot" feature.
*/

#include <common.h>
#include <configs/app3.h>

#ifdef IBB_ENABLED

#include <agere_np5_dev.h>
#include <agere_app3_regs.h>
#include <agere_release_id.h>

/*
  Debugging...
*/

#undef DEBUG
/*#define DEBUG*/
#if defined( DEBUG )
#define DEBUG_PRINT( format, args... ) do { \
printf( "ibb:%s:%d - DEBUG - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else
#define DEBUG_PRINT( format, args... )
#endif

/*
  Warnings...
*/

#define IBB_WARN_

#if defined( IBB_WARN_ )
#define WARN_PRINT( format, args... ) do { \
printf( "ibb:%s:%d - WARN - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else
#define WARN_PRINT( )
#endif

/*
  Errors...
*/

#define ERROR_PRINT( format, args... ) do { \
printf( "ibb:%s:%d - ERROR - ",  __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );

/*
  ======================================================================
  Globals
  ======================================================================
*/

static ag_np5_dev_hdl_t handle_ = ( ag_np5_dev_hdl_t ) 0;

/*
  ======================================================================
  Implementation of the Interface Defined in include/configs/app3xx.h
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  ibb_initailize
*/

int ibb_initialize( void ) {

  int return_code_;

  /* display version information */
  printf( "RTE Version: %s\n", release_id );

  /* get a device handle */

#ifdef DEBUG
  printf( "-->initialize\n" );
#endif /* DEBUG */

  if( 0 != ( return_code_ = ag_np5_dev_init( ) ) ) {

    ag_status_print( "ag_np5_dev_init( ) failed", return_code_ );
    return -1;

  }

#ifdef DEBUG
  printf( "-->open\n" );
#endif /* DEBUG */

  if( 0 != ( return_code_ = ag_np5_dev_open( 0, 0, & handle_ ) ) ) {

    ag_status_print( "ag_np5_dev_open( ) failed", return_code_ );
    return -1;

  }

  /* that's all */
  return 0;

}

/*
  ----------------------------------------------------------------------
  ibb_finalize
*/

void ibb_finalize( void ) {

  int return_code_;

#ifdef DEBUG
  printf( "-->close\n" );
#endif /* DEBUG */

  if( 0 != ( return_code_ = ag_np5_dev_close( handle_ ) ) ) {

    ag_status_print( "ag_np5_dev_close( ) failed", return_code_ );

  }

  /* that's all */
  return;

}

/*
  ----------------------------------------------------------------------
  ibb_fill
*/

int ibb_fill( int width,
              unsigned char node, unsigned char target, unsigned long offset,
              unsigned long value, unsigned long value1,
              unsigned long count ) {

  /* make sure the device driver is initialized */
  if( ( ag_np5_dev_hdl_t * ) 0 == handle_ ) {

    ERROR_PRINT( "Invalid Handle\n" );
    return -1;

  }

#ifdef DEBUG
  printf( "-->fill %d %d.%d.0x%x %d 0x%x 0x%x\n", width, node, target, offset, count );
#endif /* DEBUG */

  if( AGNP5_WIDTH_64 == width ) {

    ag_np5_dev_fill64_t value_;

    value_.data [ 0 ] = value;
    value_.data [ 1 ] = value1;

    if( AG_ST_SUCCESS !=
        ag_np5_dev_block_fill64( handle_, AG_NP5_REGION_ID( node, target ),
                                 offset, value_, count, 0 ) ) {

      ERROR_PRINT( "Fill Failed: %d.%d.0x%x\n", node, target, offset );
      return -1;

    }

  } else {

    if( AG_ST_SUCCESS !=
        ag_np5_dev_block_fill32( handle_, AG_NP5_REGION_ID( node, target ),
                                 offset, value, count, 0 ) ) {

      ERROR_PRINT( "Fill Failed: %d.%d.0x%x\n", node, target, offset );
      return -1;

    }

  }

  /* that's all */
  return 0;

}

/*
  ----------------------------------------------------------------------
  ibb_read
*/

int ibb_read( unsigned char node, unsigned char target, unsigned long offset,
              unsigned long * buffer,
              unsigned long count ) {

  /* make sure the device driver is initialized */
  if( ( ag_np5_dev_hdl_t * ) 0 == handle_ ) {

    ERROR_PRINT( "Invalid Handle\n" );
    return -1;

  }

#ifdef DEBUG
  printf( "-->read %d.%d.0x%x %d\n", node, target, offset, count );
#endif /* DEBUG */

  if( AG_ST_SUCCESS !=
      ag_np5_dev_block_read32( handle_, AG_NP5_REGION_ID( node, target ),
                               offset, ( void * ) buffer, count, 0 ) ) {

    ERROR_PRINT( "Read Failed: %d.%d.0x%x\n", node, target, offset );
    return -1;

  }

  /* that's all */
  return 0;

}

/*
  ----------------------------------------------------------------------
*/

int ibb_reset( void ) {

  /* make sure the device driver is initialized */
  if( ( ag_np5_dev_hdl_t * ) 0 == handle_ ) {

    ERROR_PRINT( "Invalid Handle\n" );
    return -1;

  }

#ifdef DEBUG
  printf( "-->reset\n" );
#endif /* DEBUG */

  if( AG_ST_SUCCESS != ag_np5_dev_reset( handle_ ) ) {

    ERROR_PRINT( "Reset Failed: \n" );
    return -1;

  }

  /* that's all */
  return 0;

}

/*
  ----------------------------------------------------------------------
  ibb_usleep
*/

int ibb_usleep( unsigned long useconds ) {

#ifdef DEBUG
   printf( "-->usleep\n" );
#endif /* DEBUG */

  udelay( useconds );

  /* that's all */
  return 0;

}

/*
  ----------------------------------------------------------------------
  ibb_write
*/

int ibb_write( unsigned char node, unsigned char target, unsigned long offset,
               unsigned long * buffer,
               unsigned long count ) {

  /* make sure the device driver is initialized */
  if( ( ag_np5_dev_hdl_t * ) 0 == handle_ ) {

    ERROR_PRINT( "Invalid Handle\n" );
    return -1;

  }

#ifdef DEBUG
 {
   int index_;

   printf( "-->write %d.%d.0x%x %d ", node, target, offset, count );

   for( index_ = 0; index_ < count; ++ index_ ) {

     printf( "0x%x ", buffer [ index_ ] );

   }

   printf( "\n" );

 }
#endif /* DEBUG */

  if( AG_ST_SUCCESS !=
      ag_np5_dev_block_write32( handle_,
                                AG_NP5_REGION_ID( node, target ), offset,
                                ( ag_uint32_t * ) buffer, count, 0 ) ) {

    ERROR_PRINT( "Write Failed: %d.%d.0x%x\n", node, target, offset );
    return -1;

  }

  /* that's all */
  return 0;

}

#endif /* IBB_ENABLED */
