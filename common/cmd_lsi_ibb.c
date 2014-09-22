/*
 *  common/cmd_ibb.c
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

#ifdef IBB_ENABLED

#include <command.h>

#ifdef CONFIG_COMMANDS

#include <malloc.h>
#include <net.h>
#include <configs/app3.h>
#include <linux/string.h>

extern int gunzip( void *, int, unsigned char *, int * );

/*
  Debugging...
*/

#undef DEBUG
/*#define DEBUG*/
#if defined( DEBUG )
#define DEBUG_PRINT( format, args... ) do { \
printf( "cmd_ibb:%s:%d - DEBUG - ", __FUNCTION__, __LINE__ ); \
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
printf( "cmd_ibb:%s:%d - WARN - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else
#define WARN_PRINT( )
#endif

/*
  Errors...
*/

#define ERROR_PRINT( format, args... ) do { \
printf( "cmd_ibb:%s:%d - ERROR - ",  __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );

#ifndef DEBUG
/*#define PROGRESS_*/
#endif

/*
  | cccc iiii wwdp nnnn nnnn tttt t000 0000 |
  c=command, i=instance, w=width, d, p, n=node, t=target

  Then offset, count, value(s) in long words each except for agNp5Reset
  which needs no offset, count, or value(s).
*/

#define AGNP5FILL 0x001
#define AGNP5READ 0x002
#define AGNP5RESET 0x003
#define AGNP5USLEEP 0x004
#define AGNP5WRITE 0x005

#define GET_COMMAND( word ) \
( ( ( word ) & 0xf0000000 ) >> 28 )
#define SET_COMMAND( value, word ) \
( ( word ) = ( ( ( ( value ) & 0x0f ) << 28 ) | ( ( word ) & 0x0fffffff ) ) )

#define GET_INSTANCE( word ) \
( ( ( word ) & 0x0f000000 ) >> 24 )
#define SET_INSTANCE( value, word ) \
( ( word ) = ( ( ( ( value ) & 0x0f ) << 24 ) | ( ( word ) & 0xf0ffffff ) ) )

#define GET_WIDTH( word ) \
( ( ( word ) & 0x00c00000 ) >> 22 )
#define SET_WIDTH( value, word ) \
( ( word ) = ( ( ( ( value ) & 0x03 ) << 22 ) | ( ( word ) & 0xff3fffff ) ) )

#define GET_NODE( word ) \
( ( ( word ) & 0x000ff000 ) >> 12 )
#define SET_NODE( value, word ) \
( ( word ) = ( ( ( ( value ) & 0xff ) << 12 ) | ( ( word ) & 0xfff00fff ) ) )

#define GET_TARGET( word ) \
( ( ( word ) & 0x00000f80 ) >>  7 )
#define SET_TARGET( value, word ) \
( ( word ) = ( ( ( ( value ) & 0x1f ) <<  7 ) | ( ( word ) & 0xfffff07f ) ) )

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
  ibb_configure_
*/

static void
ibb_configure_( unsigned long address )
{

  image_header_t * image_header_ = ( image_header_t * ) address;
  unsigned char * compressed_data_;
  int length_;
  unsigned long ibb_size_ = 0;

  DEBUG_PRINT( "Configuring from 0x%08x\n", address );

  /* initialize the "limited" rte driver */

  if( 0 != ibb_initialize( ) ) {

    ERROR_PRINT( "ibb_initialize( ) failed!\n" );
    return;

  }

  /* verify the magic number */

  if( IH_MAGIC != ntohl( image_header_->ih_magic ) ) {

    ibb_finalize( );
    ERROR_PRINT( "Bad Magic Number, 0x%x (should be 0x%x)\n",
                 ntohl( image_header_->ih_magic ), IH_MAGIC );
    return;

  }

  DEBUG_PRINT( "Verified magic number\n" );

  /* verify the header checksum */

  {

    unsigned long checksum_ = ntohl( image_header_->ih_hcrc );
    image_header_->ih_hcrc = 0;

    if( crc32( 0, ( char * ) image_header_, sizeof( image_header_t ) ) !=
        checksum_ ) {

      ibb_finalize( );
      ERROR_PRINT( "Bad Header Checksum\n" );
      return;

    }

    image_header_->ih_hcrc = htonl( checksum_ );

  }

  DEBUG_PRINT( "Verified header checksum\n" );

  /* verify the size */

  if( htonl( image_header_->ih_size ) > IBB_MAX_SIZE ) {

    ibb_finalize( );
    ERROR_PRINT( "Configuration size is too large (>0x%x/%d)\n",
                 IBB_MAX_SIZE, IBB_MAX_SIZE );
    return;

  }

  DEBUG_PRINT( "Verified size\n" );

  /* verify the data checksum */

  compressed_data_ = ( unsigned char * ) ( ( unsigned long ) image_header_ +
                                           sizeof( image_header_t ) );

  {

    if( crc32( 0, compressed_data_, htonl( image_header_->ih_size ) ) !=
        ntohl( image_header_->ih_dcrc ) ) {

      ibb_finalize( );
      ERROR_PRINT( "Bad Data Checksum\n" );
      return;

    }

  }

  DEBUG_PRINT( "Verified data checksum\n" );

  /* expand compressed_data_ */

  {

    length_ = htonl( image_header_->ih_size );

    if( gunzip( ( void * ) ntohl( image_header_->ih_load ), IBB_MAX_SIZE,
                compressed_data_, & length_ ) != 0 ) {

      ibb_finalize( );
      free( ( void * ) compressed_data_ );
      ERROR_PRINT( "gunzip( ) failed\n");
      return;

    }

  }

  DEBUG_PRINT( "Expanded configuration to 0x%x\n",
               htonl( image_header_->ih_load ) );

  /* do it */

  {

    unsigned long * configuration_ =
      ( unsigned long * ) htonl( image_header_->ih_load );
    unsigned long command_;
    unsigned long offset_;
    unsigned long count_;
    unsigned long value_;
    unsigned long value1_;
    unsigned long useconds_;
#ifdef PROGRESS_
    char props_ [ ] = { '|', '/', '-', '\\', '|', '/', '-', '\\' };
    int current_prop_ = 0;
#endif /* PROGRESS_ */

    DEBUG_PRINT( "configuration_=0x%x length_=0x%x/%d\n",
                 configuration_, length_, length_ );
    printf( "Loading NP Configuration: %s\n", image_header_->ih_name );
#ifdef PROGRESS_
    printf( "%c", props_ [ ++ current_prop_ ] );
    if( current_prop_ ==
        ( sizeof( props_ ) / sizeof( char ) ) ) { current_prop_ = 0; }
#endif /* PROGRESS_ */

    while( length_ >
           ( ( ( unsigned long ) configuration_ ) -
             htonl( image_header_->ih_load ) ) ) {

      command_ = * configuration_ ++;
#ifdef DEBUG
      {
        char * commands_ [ ] = {
          "UNKNOWN", "AGNP5FILL", "AGNP5READ", "AGNP5RESET", "AGNP5USLEEP",
          "AGNP5WRITE"
        };
        printf( "%s", commands_ [ GET_COMMAND( command_ ) ] );
      }
#endif /* DEBUG */

      switch( GET_COMMAND( command_ ) ) {

      case AGNP5FILL:
        offset_ = * configuration_ ++;
        count_ = * configuration_ ++;
        value_ = * configuration_ ++;

        if( AGNP5_WIDTH_64 == GET_WIDTH( command_ ) ) {

          value1_ = * configuration_ ++;

#ifdef DEBUG
          printf( " -w64 %d.%d.0x%x 0x%x 0x%x %d\n", GET_NODE( command_ ),
                  GET_TARGET( command_ ), offset_, value_, value1_, count_ );
#endif /* DEBUG */

        } else {

#ifdef DEBUG
          printf( " %d.%d.0x%x 0x%x %d\n", GET_NODE( command_ ),
                  GET_TARGET( command_ ), offset_, value_, count_ );
#endif /* DEBUG */

        }

        if( 0 != ibb_fill( GET_WIDTH( command_ ),
                           GET_NODE( command_ ), GET_TARGET( command_ ),
                           offset_, value_, value1_, count_ ) ) {

          ERROR_PRINT( "ibb_fill() failed\n" );

        }

        break;

      case AGNP5READ:
        offset_ = * configuration_ ++;
        count_ = * configuration_ ++;
#ifdef DEBUG
        printf( " %d.%d.0x%x %d : ", GET_NODE( command_ ),
                GET_TARGET( command_ ), offset_, count_ );
#endif /* DEBUG */

        {

          unsigned long * buffer_;

          if( ( unsigned long * ) 0 ==
              ( buffer_ =
                ( unsigned long * ) malloc( sizeof( unsigned long ) *
                                            count_ ) ) ) {

            ERROR_PRINT( "Unable to allocate buffer for read (%d bytes).\n",
                         sizeof( unsigned long ) * count_ );

          } else {

            if( 255 != GET_NODE( command_ ) ) {

              if( 0 != ibb_read( GET_NODE( command_ ), GET_TARGET( command_ ),
                                 offset_,  buffer_, count_ ) ) {

                ERROR_PRINT( "ibb_read() failed\n" );

              }

            }

#ifdef DEBUG
            {
              int index_;
              for( index_ = 0; index_ < count_; ++ index_ ) {
                printf( "0x%x ", buffer_ [ index_ ] );
              }
              printf( "\n" );
            }
#endif /* DEBUG */

            free( buffer_ );

          }

        }

        break;

      case AGNP5RESET:
#ifdef DEBUG
        printf( "\n" );
#endif /* DEBUG */

        if( 0 != ibb_reset( ) ) {

          ERROR_PRINT( "ibb_reset() failed\n" );

        }

        break;

      case AGNP5USLEEP:

        useconds_ = * configuration_ ++;

#ifdef DEBUG
        printf( " %d\n", useconds_ );
#endif /* DEBUG */

        if( 0 != ibb_usleep( useconds_ ) ) {

          ERROR_PRINT( "ibb_usleep() failed\n" );

        }

        break;

      case AGNP5WRITE:
        offset_ = * configuration_ ++;
        count_ = * configuration_ ++;

#ifdef DEBUG
        {
          unsigned long * values_ = configuration_;
          int number_ = 0;
          printf( " %d.%d.0x%08x", GET_NODE( command_ ), GET_TARGET( command_ ),
                  offset_ );
          while( number_ ++ < count_ ) {
            printf( " 0x%08x", ( * values_ )  );
            ++ values_;
          }
          printf( "\n" );
        }
#endif /* DEBUG */

        if( 255 != GET_NODE( command_ ) ) {

          if( 0 != ibb_write( GET_NODE( command_ ), GET_TARGET( command_ ),
                              offset_, configuration_, count_ ) ) {

            ERROR_PRINT( "ibb_write() failed\n" );

          }

        }

        configuration_ += count_;

        break;

      default:
        ibb_finalize( );
        ERROR_PRINT( "Parsing error\n" );
        return;
        break;

      }

#ifdef PROGRESS_
      printf( "\b\b\b%c", props_ [ current_prop_ ++ ] );
      if( current_prop_ ==
          ( sizeof( props_ ) / sizeof( char ) ) ) { current_prop_ = 0; }
#endif /* PROGRESS_ */

    }

#ifdef PROGRESS_
    printf( "\n" );
#endif /* PROGRESS_ */

  }

  /* that's all */

  return;

}

/*
  ----------------------------------------------------------------------
  ibb_configure_by_mtd_
*/

static void
ibb_configure_by_mtd_( void ) {

  /* figure out where the configuration image is in flash */

  if( 0 != app_flash_get( "ibb", 0, 0x100000, 0x100000 ) ) {

    ERROR_PRINT( "Could not read ibb partition!\n" );

  }

  return 0;

}

#endif /* IBB_ENABLED */

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
  do_ibb
*/

int
do_ibb( cmd_tbl_t * command_table, int flag, int argc, char * argv [ ] )
{

#ifdef CONFIG_APP3XX
#ifdef IBB_ENABLED

  DEBUG_PRINT( "flag=0x%x argc=%d\n", flag, argc );

  if( 0 == strncmp( argv [ 1 ], "c", strlen( "c" ) ) ) {

    if( 2 == argc ) {

      ibb_configure_by_mtd_( );

    } else if( 3 == argc ) {

      unsigned long address_ = simple_strtoul( ( argv [ 2 ] ), NULL, 0 );
      ibb_configure_( address_ );

    } else {
    }

  } else if( ( 0 == strncmp( argv [ 1 ], "i", strlen( "i" ) ) ) ) {

    int return_code_;

    if( 0 != ( return_code_ = ibb_initialize( ) ) ) {

      ERROR_PRINT( "ibb_initialize( ) failed: %d\n", return_code_ );

    }

  } else if( 0 == strncmp( argv [ 1 ], "fin", strlen( "fin" ) ) ) {

    ibb_finalize( );

  } else if( 0 == strncmp( argv [ 1 ], "fil", strlen( "fil" ) ) ) {

    /*
      agNp5Fill
    */

    if( 5 == argc ) {

      unsigned char node_;
      unsigned char target_;
      unsigned long offset_;
      char * token_;
      unsigned long value_;
      unsigned long count_ = 0;

      /* Get the node.target.offset */

      token_ = strsep( & ( argv [ 2 ] ), "." );
      node_ = simple_strtoul( token_, NULL, 0 );
      token_ = strsep( & ( argv [ 2 ] ), "." );
      target_ = simple_strtoul( token_, NULL, 0 );
      token_ = strsep( & ( argv [ 2 ] ), "." );
      offset_ = simple_strtoul( token_, NULL, 0 );
      value_ = simple_strtoul( ( argv [ 3 ] ), NULL, 0 );
      count_ = simple_strtoul( ( argv [ 4 ] ), NULL, 0 );

      DEBUG_PRINT( "ibb_fill( %d, %d, %d, 0x%x, %d )\n",
                   node_, target_, offset_, value_, count_ );

      if( 0 != ibb_fill( AGNP5_WIDTH_32,
                         node_, target_, offset_, value_, 0, count_ ) ) {

        ERROR_PRINT( "ibb_fill( ) failed\n" );

      }

    } else {

      printf( "Usage: ibb fill n.t.o value count\n" );

    }

  } else if( 0 == strncmp( argv [ 1 ], "rea", strlen( "rea" ) ) ) {

    /*
      agNp5Read n.t.o count
    */

    if( 4 == argc ) {

      unsigned char node_;
      unsigned char target_;
      unsigned long offset_;
      unsigned long count_;
      char * token_;
      unsigned long * buffer_;

      /* Get the node.target.offset */

      token_ = strsep( & ( argv [ 2 ] ), "." );
      node_ = simple_strtoul( token_, NULL, 0 );
      token_ = strsep( & ( argv [ 2 ] ), "." );
      target_ = simple_strtoul( token_, NULL, 0 );
      token_ = strsep( & ( argv [ 2 ] ), "." );
      offset_ = simple_strtoul( token_, NULL, 0 );
      count_ = simple_strtoul( ( argv [ 3 ] ), NULL, 0 );

      if( ( void * ) 0 !=
          ( buffer_ = malloc( count_ * sizeof( unsigned long ) ) ) ) {

        int index_;

        if( 0 != ibb_read( node_, target_, offset_, buffer_, count_ ) ) {

          ERROR_PRINT( "ibb_read() failed\n" );

        }

        for( index_ = 0; index_ < count_; ++ index_ ) {

          if( 0 == ( index_ % 4 ) ) {

            if( 0 != index_ ) {

              puts( "\n" );

            }

            printf( "0x%08x : ", ( index_ * 4 ) );

          }

          printf( "0x%08x ", buffer_ [ index_ ] );

        }

        printf( "\n" );

        free( ( void * ) buffer_ );

      } else {

        printf( "ibb read: Unable to allocate %d bytes!\n",
                ( ( argc - 3 ) * sizeof( unsigned long ) ) );

      }

    } else {

      printf( "Usage: ibb read n.t.o count\n" );

    }

  } else if( 0 == strncmp( argv [ 1 ], "res", strlen( "res" ) ) ) {

    /*
      agNp5Reset
    */

    if( 0 != ibb_reset( ) ) {

      ERROR_PRINT( "ibb_reset( ) failed\n" );

    }

  } else if( 0 == strncmp( argv [ 1 ], "w", strlen( "w" ) ) ) {

    /*
      agNp5Write
    */

    if( 4 <= argc ) {

      unsigned char node_;
      unsigned char target_;
      unsigned long offset_;
      char * token_;
      unsigned long * buffer_;
      unsigned long count_ = 0;

      /* Get the node.target.offset */

      token_ = strsep( & ( argv [ 2 ] ), "." );
      node_ = simple_strtoul( token_, NULL, 0 );
      token_ = strsep( & ( argv [ 2 ] ), "." );
      target_ = simple_strtoul( token_, NULL, 0 );
      token_ = strsep( & ( argv [ 2 ] ), "." );
      offset_ = simple_strtoul( token_, NULL, 0 );

      if( ( void * ) 0 !=
          ( buffer_ = malloc( ( argc - 3 ) * sizeof( unsigned long ) ) ) ) {

        int index_ = 0;

        while( ( argc - 3 ) > index_ ) {

          buffer_ [ index_ ] =
            simple_strtoul( ( argv [ ( index_ + 3 ) ] ), NULL, 0 );
          ++ index_;
          ++ count_;

        }

        if( 0 != ibb_write( node_, target_, offset_, buffer_, count_ ) ) {

          ERROR_PRINT( "ibb_write() failed\n" );

        }

        free( ( void * ) buffer_ );

      } else {

        printf( "ibb write: Unable to allocate %d bytes!\n",
                ( ( argc - 3 ) * sizeof( unsigned long ) ) );

      }

    } else {

      printf( "Usage: ibb write n.t.o value1 [value2] [value3] ... \n" );

    }

  } else {

    printf( "Unknown command: ibb %s\n", argv [ 1 ] );

  }

#else  /* IBB_ENABLED */

  printf( "IBB is not enabled!\n" );

#endif /* IBB_ENABLED */

#endif /* CONFIG_APP3XX */

  /* that's all */
  return 0;

}

/*
  ----------------------------------------------------------------------
*/

U_BOOT_CMD( ibb, 100, 0, do_ibb,
	    "ibb     - in band boot\n",
	    "c,onfigure  [address]\n" \
	    "          Apply the configuration currently in flash (ibb partition),\n" \
	    "          if no address is given, or at the given address.\n" \
	    "i,nitialize -- call ibb_initialize().\n" \
	    "fin,alize   -- call ibb_finalize().\n" \
	    "fil,l       -- call ibb_fill().\n" \
	    "rea,d       -- call ibb_read().\n" \
	    "res,et      -- call ibb_reset().\n" \
	    "w,rite      -- call ibb_write().\n" );

#endif /* CONFIG_COMMANDS */
