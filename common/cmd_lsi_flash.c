/*
 *  common/cmd_app3_flash.c
 *
 *  Copyright (C) 2006 Agere Systems Inc.
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
#include <malloc.h>

extern flash_info_t flash_info [ ];

#ifdef CONFIG_COMMANDS

/*
  Debugging...
*/

#undef DEBUG
/*#define DEBUG*/
#ifdef DEBUG
#define DEBUG_PRINT( format, args... ) do { \
printf( "cmd_app3_flash:%s:%d - DEBUG - ", __FUNCTION__, __LINE__ ); \
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
#ifdef WARN
#define WARN_PRINT( format, args... ) do { \
printf( "cmd_app3_flash:%s:%d - WARN - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else
#define WARN_PRINT( )
#endif

/*
  Errors...
*/

#define ERROR_PRINT( format, args... ) do { \
printf( "cmd_app3_flash:%s:%d - ERROR - ",  __FUNCTION__, __LINE__ ); \
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

/*
  ======================================================================
  ======================================================================
  ======================================================================
  Local Functions
  ======================================================================
  ======================================================================
  ======================================================================
*/

static void erase_sector_( flash_info_t * flash_info, int sector ) {

  unsigned long sector_size_;

  sector_size_ = ( flash_info->size / flash_info->sector_count );

  if( 0 != flash_info->protect [ sector ] ) {

    flash_sect_protect( 0, flash_info->start [ sector ],
                        ( flash_info->start [ sector ] + sector_size_ - 1 ) );
    flash_erase( flash_info, sector, sector );
    flash_sect_protect( 1, flash_info->start [ sector ],
                        ( flash_info->start [ sector ] + sector_size_ - 1 ) );

  } else {

    flash_erase( flash_info, sector, sector );

  }

}

static int do_read_( unsigned long bank,
                     unsigned long offset, unsigned long address,
                     unsigned long size ) {

  printf( "Reading %d bytes from bank %d at offset 0x%x to 0x%x\n",
          size, bank, offset, address );

  if( FLASH_UNKNOWN == ( flash_info [ ( bank - 1 ) ] ).flash_id ) {

    ERROR_PRINT( "FLASH bank %d is not valid\n", bank );
    return -1;

  }

  if( ( offset + size ) >= ( flash_info [ ( bank - 1 ) ] ).size ) {

    ERROR_PRINT( "Out of range!\n", bank );
    return -1;

  }

  while( 0 < size -- ) {

    * ( ( unsigned char * ) address ) =
      app3xx_flash_readb( ( ( flash_info [ ( bank - 1 ) ] ).start [ 0 ] +
                            offset ) );
    ++ address;
    ++ offset;

  }

  return 0;

}

static int do_write_( unsigned long bank,
                      unsigned long address, unsigned long offset,
                      unsigned long size ) {

  int first_sector_;
  int last_sector_;
  unsigned long sector_size_;
  flash_info_t * flash_info_ = & ( flash_info [ ( bank - 1 ) ] );

  printf( "Writing %d bytes to bank %d from 0x%x to offset 0x%x\n",
          size, bank, address, offset );

  if( FLASH_UNKNOWN == flash_info_->flash_id ) {

    ERROR_PRINT( "FLASH bank %d is not valid\n", bank );
    return -1;

  }

  if( ( offset + size ) >= flash_info_->size ) {

    ERROR_PRINT( "Out of range!\n" );
    return -1;

  }

  sector_size_ = ( flash_info_->size / flash_info_->sector_count );
  first_sector_ = offset / sector_size_;

  DEBUG_PRINT( "size=%u address=%u offset=%u first_sector_=%d\n",
               size, address, offset, first_sector_ );

  if( 0 != ( offset % sector_size_ ) ) {

    /*
      Handle unaligned writes at the beginning.
    */

    unsigned char * buffer_;

    if( ( unsigned char * ) 0 ==
        ( buffer_ = ( unsigned char * ) malloc( sector_size_ ) ) ) {

      ERROR_PRINT( "malloc( ) failed\n" );
      return -1;

    }

    DEBUG_PRINT( "Handling unaligned write at beginning.\n" );
    do_read_( bank, ( first_sector_ * sector_size_ ),
              ( unsigned long ) buffer_, sector_size_ );
    memcpy( ( void * ) ( buffer_ + ( offset % sector_size_ ) ),
            ( void * ) address,
            sector_size_ - ( offset % sector_size_ ) );
    erase_sector_( flash_info_, first_sector_ );

    if( 0 != write_buff( flash_info_, buffer_, ( first_sector_ * sector_size_ ),
                         sector_size_ ) ) {

      ERROR_PRINT( "Write Failed\n" );
      return -1;

    }

    free( buffer_ );
    address += ( sector_size_ - ( offset % sector_size_ ) );
    size -= ( sector_size_ - ( offset % sector_size_ ) );
    offset += ( sector_size_ - ( offset % sector_size_ ) );
    ++ first_sector_;

  }

  DEBUG_PRINT( "size=%u address=%u offset=%u first_sector_=%d\n",
               size, address, offset, first_sector_ );

  if( sector_size_ <= size ) {

    /*
      Handle aligned writes.
    */

    int sector_;
    int bytes_to_write_;

    DEBUG_PRINT( "Handling aligned writes.\n" );
    last_sector_ = first_sector_ + ( ( size - 1 ) / sector_size_ );
    bytes_to_write_ = ( ( last_sector_ - first_sector_ + 1 ) * sector_size_ );
    DEBUG_PRINT( "first_sector_=%u last_sector_=%u bytes_to_write_=%u\n",
                 first_sector_, last_sector_, bytes_to_write_ );

    for( sector_ = first_sector_; sector_ <= last_sector_; ++ sector_ ) {

      erase_sector_( flash_info_, sector_ );

    }

    if( 0 != write_buff( flash_info_, ( unsigned char * ) address, offset,
                         bytes_to_write_ ) ) {

      ERROR_PRINT( "Write Failed\n" );
      return -1;

    }

    address += bytes_to_write_;
    size -= bytes_to_write_;
    offset += bytes_to_write_;
    first_sector_ += ( last_sector_ - first_sector_ + 1);

  }

  DEBUG_PRINT( "size=%u address=%u offset=%u first_sector_=%d\n",
               size, address, offset, first_sector_ );

  if( 0 < size ) {

    /*
      Handle unaligned writes at the end.
    */

    unsigned char * buffer_;

    if( ( unsigned char * ) 0 ==
        ( buffer_ = ( unsigned char * ) malloc( sector_size_ ) ) ) {

      ERROR_PRINT( "malloc( ) failed\n" );
      return -1;

    }

    DEBUG_PRINT( "Handling unaligned writes at the end.\n" );
    do_read_( bank, ( first_sector_ * sector_size_ ),
              ( unsigned long ) buffer_, sector_size_ );
    memcpy( ( void * ) ( buffer_ + ( offset % sector_size_ ) ),
            ( void * ) address,
            sector_size_ - ( offset % sector_size_ ) );
    erase_sector_( flash_info_, first_sector_ );

    if( 0 != write_buff( flash_info_, buffer_, ( first_sector_ * sector_size_ ),
                         sector_size_ ) ) {

      ERROR_PRINT( "Write Failed\n" );
      return -1;

    }

    free( buffer_ );

  }

  return 0;

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
  app_flash_get
*/

int
app_flash_get( const char * partition,
	       unsigned long offset, unsigned long address, unsigned long size )
{

  /*
    mtdparts mtdparts=app3k-nor:512k(u-boot),256k(u-boot-env-0),256k(u-boot-env-1),1M(ibb),-(unused-nor);app3k-nand:6M(bootA),6M(bootB),506M(fsA),-(fsB)
    mtdids nor0=app3k-nor,nand0=app3k-nand
  */

  int return_code_ = -1;
  char * mtdparts_env_;

  if( ( char * ) 0 != ( mtdparts_env_ = getenv( "mtdparts" ) ) ) {

    char * mtdparts_buffer_ = strdup( mtdparts_env_ );
    char * partition_string_  = strtok( mtdparts_buffer_, "=" );
    partition_string_ = strtok( ( char * ) 0, ":" );

    while( ( char * ) 0 != partition_string_ ) {

      printf( "Device: %s\n", partition_string_ );

      for( ; ; ) {

	partition_string_ = strtok( ( char * ) 0, ",;:" );
	if( ( char * ) 0 == strchr( partition_string_, '(' ) ) { break; }
	printf( "Partitions: %s\n", partition_string_ );

      }

    }

    free( mtdparts_buffer_ );
    return_code_ = 0;

  }

  return return_code_;

}

/*
  ----------------------------------------------------------------------
  do_app3_flash
*/

int do_app3_flash( cmd_tbl_t * command_table, int flag,
                   int argc, char * argv [ ] ) {

#ifdef CONFIG_APP3XX

  DEBUG_PRINT( "flag=0x%x argc=%d\n", flag, argc );

  if( 0 == strncmp( argv [ 1 ], "i", strlen( "i" ) ) ) {

    set_feac( );
    set_feac_flip_bits( );
    flash_init( );
    printf( "feac=0x%lx feac_flip_bits=0x%lx gpio_mux=0x%lx\n",
            get_feac( ), get_feac_flip_bits( ), get_gpio_mux( ) );

  } else if( 0 == strncmp( argv [ 1 ], "r", strlen( "r" ) ) ) {

    if( 6 == argc ) {

      unsigned long bank_;
      unsigned long offset_;
      unsigned long address_;
      unsigned long size_;

      bank_ = simple_strtoul( ( argv [ 2 ] ), NULL, 16 );
      offset_ = simple_strtoul( ( argv [ 3 ] ), NULL, 16 );
      address_ = simple_strtoul( ( argv [ 4 ] ), NULL, 16 );
      size_ = simple_strtoul( ( argv [ 5 ] ), NULL, 16 );

      DEBUG_PRINT( "reading %d bytes from FLASH:%d (0x%08x) to RAM (0x%08x)\n",
                   size_, bank_, offset_, address_ );
      do_read_( bank_, offset_, address_, size_ );

    } else {

      printf( "%s", cmdtp->usage );

    }

  } else if( 0 == strncmp( argv [ 1 ], "w", strlen( "w" ) ) ) {

    if( 6 == argc ) {

      unsigned long bank_;
      unsigned long address_;
      unsigned long offset_;
      unsigned long size_;

      bank_ = simple_strtoul( ( argv [ 2 ] ), NULL, 16 );
      address_ = simple_strtoul( ( argv [ 3 ] ), NULL, 16 );
      offset_ = simple_strtoul( ( argv [ 4 ] ), NULL, 16 );
      size_ = simple_strtoul( ( argv [ 5 ] ), NULL, 16 );

      DEBUG_PRINT( "writing %d bytes from RAM (0x%08x) to FLASH:%d (0x%08x)\n",
                   size_, address_, bank_, offset_ );
      do_write_( bank_, address_, offset_, size_ );

    } else {

      printf( "%s", cmdtp->usage );

    }

  } else {

    printf( "%s", cmdtp->usage );

  }

#endif /* CONFIG_APP3XX */

  /* that's all */
  return 0;

}

/*
  ----------------------------------------------------------------------
*/

U_BOOT_CMD( flash, 100, 0, do_app3_flash,
	    "flash - FLASH access\n",
	    "i,nit\n" \
	    "          re-initialize the FLASH driver (NOR only)\n" \
	    "g,et partition offset address size\n" \
	    "          Use mtdparts to find the partition to read from\n" \
	    "r,ead  bank offset address size\n" \
	    "          read FLASH (offset) -> RAM (address) (NOR only)\n" \
	    "w,rite bank address offset size\n" \
	    "          write FLASH (offset) -> RAM (address) (NOR only)\n" );

#endif /* CONFIG_COMMANDS */
