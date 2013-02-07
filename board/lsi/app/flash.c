/*
 * (C) Copyright 2004
 * Agere Systems, Inc. <www.agere.com>
 * John Jacques <jjacques@agere.com>
 * Michael W. Bringmann <mb@agere.com>
 *
 * (C) Copyright 2001
 * Kyle Harris, Nexus Technologies, Inc. kharris@nexus-tech.net
 *
 * (C) Copyright 2001
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * (C) Copyright 2003
 * Texas Instruments, <www.ti.com>
 * Kshitij Gupta <Kshitij@ti.com>
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
#include <linux/ctype.h>
#include <environment.h>
#include <asm/io.h>

#define FLASH_ACCESS_WORKAROUND_
#define ENABLE_MULTIBYTE_WRITE_

/*
  ======================================================================
  Extended address control.  MACROS and prototypes.
  ======================================================================
*/

/*
  Given an address (from the base of FLASH), returns the address to use.
*/

static unsigned long EAC_address_( unsigned long );

/*
  I'm adding the definitions here first.  Once all is working, I'll
  move them to flash.h.
*/

#define AMD_MANUFACT_ 0x0001

/* cfi */
#define FLASH_CFI_             0x00a0

/* am29lv640m, doral */
#define FLASH_AM640M_DORAL_    0x0097
#define AMD_ID_LV640M_DORAL_1_ 0x227e
#define AMD_ID_LV640M_DORAL_2_ 0x2212
#define AMD_ID_LV640M_DORAL_3_ 0x2201

/* sg29gl512, doral */
#define FLASH_SG29GL512_DORAL_ 0xc1
#define SG_ID_29GL512_1_DORAL_ 0x227e
#define SG_ID_29GL512_2_DORAL_ 0x2223
#define SG_ID_29GL512_3_DORAL_ 0x2201

/* am29lv640m */
#define FLASH_AM640M_    0x0096
#define AMD_ID_LV640M_1_ 0x227e
#define AMD_ID_LV640M_2_ 0x220c
#define AMD_ID_LV640M_3_ 0x2201

/* sg29gl01g */
#define FLASH_SG29GL01G_ 0xb0
#define SG_ID_29GL01G_1_ 0x7e
#define SG_ID_29GL01G_2_ 0x28
#define SG_ID_29GL01G_3_ 0x01

/* sg29gl512 */
#define FLASH_SG29GL512_ 0xb1
#define SG_ID_29GL512_1_ 0x7e
#define SG_ID_29GL512_2_ 0x23
#define SG_ID_29GL512_3_ 0x01

/* sg29gl256 */
#define FLASH_SG29GL256_ 0xb2
#define SG_ID_29GL256_1_ 0x7e
#define SG_ID_29GL256_2_ 0x12
#define SG_ID_29GL256_3_ 0x01

flash_info_t flash_info [ CFG_MAX_FLASH_BANKS ]; /* info for FLASH chips    */
static int multi_byte = -1;

#define FPW  ushort
#define FPWV vu_short

#define SWAP( value ) __swab16( value )

unsigned long app3xx_environment_buffer_ [ CFG_ENV_SIZE / 4 ];
#ifdef CFG_ENV_ADDR_REDUND
unsigned long app3xx_environment_buffer_redundant_ [ CFG_ENV_SIZE / 4 ];
#endif /* CFG_ENV_ADDR_REDUND */

/*#define __FLASH_C_VERIFY__*/

/*
  Debugging...
*/

/*#define DEBUG_*/

#if defined( DEBUG_ )
#define DEBUG_PRINT( format, args... ) do { \
printf( "flash.c:%s:%d - DEBUG - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else
#define DEBUG_PRINT( format, args... )
#endif

/*
  Warnings...
*/

#define WARN_

#if defined( WARN_ )
#define WARN_PRINT( format, args... ) do { \
printf( "flash.c:%s:%d - WARN - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else
#define WARN_PRINT( formatm args... )
#endif

/*
  Errors...
*/

#define ERROR_PRINT( format, args... ) do { \
printf( "flash.c:%s:%d - ERROR - ",  __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );

typedef struct {

  int ( * erase ) ( flash_info_t *,
                    int, int );
  int ( * write ) ( flash_info_t *,
                    unsigned char *, unsigned long, unsigned long );
  unsigned char ( * read_8 ) ( unsigned long );
  unsigned short ( * read_16 ) ( unsigned long );
  unsigned long ( * read_32 ) ( unsigned long );

} app3_flash_ops_t;

static app3_flash_ops_t ops_;
static int ready_ = 0;
unsigned long feac_flip_bits = 0;
static int interleave_ = 0;

/*
  ======================================================================
  APP3K Indirect Access
*/

typedef union {

  unsigned long raw;

  struct {

    unsigned long clock_wait          :  8;
    unsigned long write_protect       :  1;
    unsigned long reset               :  1;
#if defined( LSI_ARCH_APP3K )
    unsigned long web_late            :  1;
    unsigned long nand_flash_select   :  1;
    unsigned long nor_disable_direct  :  1;
    unsigned long nor_flash_respond   :  1;
    unsigned long nor_flash_interrupt :  1;
    unsigned long                     : 17;
#elif defined( LSI_ARCH_APP3 )
    unsigned long                     : 22;
#else
#error "Unknown Architecture"
#endif

  } __attribute__ ( ( packed ) ) bits;

} __attribute__ ( ( packed ) ) flash_controller_configuration_t;

#define HI_NOR_IND_CMD_AD 0x6800006c

typedef union {

  unsigned long raw;

  struct {

    unsigned long req_addr  : 26;
    unsigned long req_size  :  4; /* 0=16bytes, 1=1byte, ..., 15=15bytes */
    unsigned long req_type  :  1; /* 0=read 1=write */
    unsigned long req_valid :  1; /* 1=start, cleared by hw when complete */

  } __attribute__ ( ( packed ) ) bits;

} __attribute__ ( ( packed ) ) ni_nor_ind_cmd_ad_t;

#define TO_REQ_SIZE( bytes ) ( ( bytes == 16 ) ? 0 : bytes )
#define FROM_REQ_SIZE( req_size ) ( ( req_size == 0 ) ? 16 : req_size )

#define HI_NOR_IND_DAT0 0x68000070
#define HI_NOR_IND_DAT1 0x68000074
#define HI_NOR_IND_DAT2 0x68000078
#define HI_NOR_IND_DAT3 0x6800007c

/*
  ----------------------------------------------------------------------
  app3k_read_
*/

static int app3k_read_( void * address, unsigned long offset, int number ) {

  ni_nor_ind_cmd_ad_t cmd_ad_;

  //DEBUG_PRINT( "address=0x%x offset=0x%x number=%d\n", address, offset, number );

  while( 0 < number ) {

    unsigned long data_ [ 4 ];

    cmd_ad_.raw = 0;
    cmd_ad_.bits.req_addr = offset;
    cmd_ad_.bits.req_size = TO_REQ_SIZE( ( 16 <= number ) ? 16 : number );
    number -= FROM_REQ_SIZE( cmd_ad_.bits.req_size );
    cmd_ad_.bits.req_type = 0;
    cmd_ad_.bits.req_valid = 1;
    writel( cmd_ad_.raw, HI_NOR_IND_CMD_AD );
    while( 0 != ( readl( HI_NOR_IND_CMD_AD ) & 0x80000000 ) );
    data_ [ 0 ] = readl( HI_NOR_IND_DAT0 );
    data_ [ 1 ] = readl( HI_NOR_IND_DAT1 );
    data_ [ 2 ] = readl( HI_NOR_IND_DAT2 );
    data_ [ 3 ] = readl( HI_NOR_IND_DAT3 );
#if 0
    DEBUG_PRINT( "%d bytes, 0x%x 0x%x 0x%x 0x%x\n",
                 FROM_REQ_SIZE( cmd_ad_.bits.req_size ),
                 data_ [ 0 ], data_ [ 1 ],
                 data_ [ 2 ], data_ [ 3 ] );
#endif
    memcpy( address, ( void * ) & ( data_ [ 0 ] ),
            FROM_REQ_SIZE( cmd_ad_.bits.req_size ) );
    address += FROM_REQ_SIZE( cmd_ad_.bits.req_size );
    offset += FROM_REQ_SIZE( cmd_ad_.bits.req_size );

  }

  return 0;

}

/*
  ----------------------------------------------------------------------
  app3k_write_
*/

static int app3k_write_( const void * address, unsigned long offset,
                         int number ) {

  ni_nor_ind_cmd_ad_t cmd_ad_;

  //DEBUG_PRINT( "address=0x%x offset=0x%x number=%d\n", address, offset, number );

  while( 0 < number ) {

    unsigned long data_ [ 4 ];

    memset( ( void * ) & ( data_ [ 0 ] ), 0, sizeof( data_ ) );
    cmd_ad_.raw = 0;
    cmd_ad_.bits.req_size = TO_REQ_SIZE( ( 16 <= number ) ? 16 : number );
    number -= FROM_REQ_SIZE( cmd_ad_.bits.req_size );
    memcpy( ( void * ) & ( data_ [ 0 ] ), address,
            FROM_REQ_SIZE( cmd_ad_.bits.req_size ) );
    cmd_ad_.bits.req_addr = offset;
    cmd_ad_.bits.req_type = 1;
    cmd_ad_.bits.req_valid = 1;
    writel( data_ [ 0 ], HI_NOR_IND_DAT0 );
    writel( data_ [ 1 ], HI_NOR_IND_DAT1 );
    writel( data_ [ 2 ], HI_NOR_IND_DAT2 );
    writel( data_ [ 3 ], HI_NOR_IND_DAT3 );
    //DEBUG_PRINT( "%d bytes, 0x%x 0x%x 0x%x 0x%x\n", FROM_REQ_SIZE( cmd_ad_.bits.req_size ), data_ [ 0 ], data_ [ 1 ], data_ [ 2 ], data_ [ 3 ] );
    writel( cmd_ad_.raw, HI_NOR_IND_CMD_AD );
    while( 0 != ( readl( HI_NOR_IND_CMD_AD ) & 0x80000000 ) );
    address += FROM_REQ_SIZE( cmd_ad_.bits.req_size );
    offset += FROM_REQ_SIZE( cmd_ad_.bits.req_size );

  }

  return 0;

}
    

/*
  ======================================================================
  Extended address control.  Implementation.
  ======================================================================
*/

static unsigned long EAC_address_( unsigned long address ) {

  address ^= feac_flip_bits;

  if( 0x10000000 <= address ) {

    address &= ~ 0xf0000000;
    address |= 0xb0000000;

  }

  return address;

}

/*
 */

static inline unsigned long mkaddr_( int il, int order ) {

  if( 2 == il ) {

    if( 1 == order ) {

      return 0x555;

    } else {

      return 0xaaa;

    }

  } else {

    if( 1 == order ) {

      return 0x2aa;

    } else {

      return 0x555;

    }

  }

}

static inline unsigned long mkcmd_( int il, int command ) {

  if( 2 == il ) {

    return ( command << 8 | command );

  }

  return command;

}

static unsigned long max_size_( void ) {

#if defined( LSI_ARCH_APP3K )

  return ( 1 << 25 );

#elif defined( LSI_ARCH_APP3 )

  unsigned long feac_ = get_feac( );
  unsigned long size_ = ( 1 << 25 );

  if( 0 != ( feac_ & 0x10 ) ) { size_ <<= 1; }
  if( 0 != ( feac_ & 0x200 ) ) { size_ <<= 1; }
  if( 0 != ( feac_ & 0x4000 ) ) { size_ <<= 1; }
  if( 0 != ( feac_ & 0x80000 ) ) { size_ <<= 1; }

  return size_;

#else
#error "Unknown Architecture"
#endif

}

/*
  ======================================================================
  ======================================================================
  ======================================================================
  Custom Part Template...
  ======================================================================
  ======================================================================
  ======================================================================
*/

#if 0

static void custom_control_write_( unsigned long, unsigned long,
                                   unsigned long );
static int custom_data_write_( flash_info_t *, unsigned long, unsigned short );
static int custom_erase_sector_( flash_info_t *, int, int );
static int custom_write_( flash_info_t *, unsigned char *, unsigned long,
                          unsigned long );
static unsigned char custom_readb_( unsigned long );
static unsigned short custom_readw_( unsigned long );
static unsigned long custom_readl_( unsigned long );
static int custom_detect_( void );

/*
  ----------------------------------------------------------------------
  custom_control_write_
*/

static void custom_control_write_( unsigned long base,
                                   unsigned long offset,
                                   unsigned long value ) {
}

/*
  ----------------------------------------------------------------------
  custom_control_read_
*/

static unsigned long custom_control_read_( unsigned long base,
                                           unsigned long offset ) {

  return 0;

}

/*
  ----------------------------------------------------------------------
  custom_data_write_
*/

static int custom_data_write_( flash_info_t * info,
                               unsigned long address,
                               unsigned short value ) {

  return 1;

}

/*
  ----------------------------------------------------------------------
  custom_erase_sector_
*/

static int custom_erase_sector_( flash_info_t * info, int first, int last ) {

  return -1;

}

/*
  ----------------------------------------------------------------------
  custom_write_
*/

static int custom_write_( flash_info_t * info,
                          unsigned char * source,
                          unsigned long address,
                          unsigned long count ) {

  return 2;

}

/*
  ----------------------------------------------------------------------
  custom_readb_
*/

static unsigned char custom_readb_( unsigned long address ) {

  return 0;

}

/*
  ----------------------------------------------------------------------
  custom_readw_
*/

static unsigned short custom_readw_( unsigned long address ) {

  return 0;

}

/*
  ----------------------------------------------------------------------
  custom_readl_
*/

static unsigned long custom_readl_( unsigned long address ) {

  return 0;

}

#endif

/*
  ----------------------------------------------------------------------
  custom_detect_
*/

static int custom_detect_( void ) {

  ERROR_PRINT( "Fill This In for Custom Flash Devices!\n" );
  return -1;

}

/*
  ======================================================================
  ======================================================================
  ======================================================================
  Common FLASH Interface...
  ======================================================================
  ======================================================================
  ======================================================================
*/

static void cfi_control_write_( unsigned long, unsigned long, unsigned long );
static int cfi_erase_sector_( flash_info_t *, int, int );
static int cfi_write_( flash_info_t *, unsigned char *, unsigned long,
                       unsigned long );
static unsigned char cfi_readb_( unsigned long );
static unsigned short cfi_readw_( unsigned long );
static unsigned long cfi_readl_( unsigned long );
static int cfi_detect_( void );

#if defined( LSI_ARCH_APP3K )

/*
  ----------------------------------------------------------------------
  cfi_control_write_
*/

static void cfi_control_write_( unsigned long base,
                                unsigned long offset,
                                unsigned long value ) {

  unsigned long address_ = base + ( offset << 1 );

  DEBUG_PRINT( "address:0x%08x value=0x%x\n", address_, value );
  app3k_write_( & value, address_, 1 );
  __asm__ __volatile__ ( "" : : : "memory" );

  return;

}

/*
  ----------------------------------------------------------------------
  cfi_readb_
*/

static unsigned char cfi_readb_( unsigned long address ) {

  unsigned char value_;

  app3k_read_( ( void * ) & value_, address, 1 );
  DEBUG_PRINT( "address=0x%x value_=0x%x\n", address, value_ );

  return value_;

}

/*
  ----------------------------------------------------------------------
  cfi_readw_
*/

static unsigned short cfi_readw_( unsigned long address ) {

  unsigned short value_;

  app3k_read_( ( void * ) & value_, address, 2 );
  //DEBUG_PRINT( "value_=0x%x\n", value_ );

  return value_;

}

/*
  ----------------------------------------------------------------------
  cfi_readl_
*/

static unsigned long cfi_readl_( unsigned long address ) {

  unsigned long value_;

  app3k_read_( ( void * ) & value_, address, 4 );
  //DEBUG_PRINT( "value_=0x%x\n", value_ );

  return value_;

}

/*
  ----------------------------------------------------------------------
  cfi_data_write_
*/

static int cfi_data_write_( flash_info_t * info,
                            unsigned long address,
                            unsigned char value ) {

  unsigned long base_ = info->start [ 0 ];
  unsigned long status_;
  int flag_;

  /* See if the value is already written. */

  {

    unsigned char current_value_;

    current_value_ = cfi_readb_( address );

    if( current_value_ == value ) {

      DEBUG_PRINT( "The address already contains the value!\n" );
      return 0;

    }

  }

  /* Check if FLASH is (sufficiently) erased. */

  {

    unsigned char current_value_;

    current_value_ = cfi_readb_( address );

    if( ( current_value_ & value ) != value ) {

      WARN_PRINT( "FLASH not erased at address 0x%08x\n", address );
      return 2;

    }

  }

  /* disable interrupts */
  flag_ = disable_interrupts( );

  /* write setup */
  cfi_control_write_( base_, mkaddr_( interleave_, 0 ),
                      mkcmd_( interleave_, 0xaa ) );
  cfi_control_write_( base_, mkaddr_( interleave_, 1 ),
                      mkcmd_( interleave_, 0x55 ) );
  cfi_control_write_( base_, mkaddr_( interleave_, 0 ),
                      mkcmd_( interleave_, 0xa0 ) );
  cfi_control_write_( address, 0, value );

  /* arm simple, non interrupt dependent timer */
  reset_timer_masked( );

  /* wait while polling the status register */
  while( ( ( status_ =
             cfi_readb_( address ) ) & mkcmd_( interleave_, 0x80 ) ) !=
         ( value & mkcmd_( interleave_, 0x80 ) ) ) {

    if( get_timer_masked( ) > CFG_FLASH_WRITE_TOUT ) {

      ERROR_PRINT( "Timed out writing 0x%04x to 0x%08x\n", value, address );
      cfi_control_write_( base_, 0, mkcmd_( interleave_, 0xf0 ) );
      if( 0 != flag_ ) { enable_interrupts( ); }
      return 1;

    }

  }

  cfi_control_write_( base_, 0, mkcmd_( interleave_, 0xf0 ) );
  if( 0 != flag_ ) { enable_interrupts( ); }
  return 0;

}

/*
  ----------------------------------------------------------------------
  write_buffer_write_
*/

#ifdef ENABLE_MULTIBYTE_WRITE_

static int write_buffer_write_( unsigned long base_address,
                                unsigned long sector_address,
                                unsigned long data_address,
                                void * data,
                                int count ) {

  int status_;
  int flag_;
  int return_code_ = 0;

  /* disable interrupts */
  flag_ = disable_interrupts( );

  cfi_control_write_( base_address, mkaddr_( interleave_, 0 ),
                      mkcmd_( interleave_, 0xaa ) );
  cfi_control_write_( base_address, mkaddr_( interleave_, 1 ),
                      mkcmd_( interleave_, 0x55 ) );
  cfi_control_write_( sector_address, 0, 0x25 );
  cfi_control_write_( sector_address, 0, ( count - 1 ) );

  while( 0 < count ) {

    cfi_control_write_( data_address, 0, * ( ( unsigned char * ) data ) );
    ++ data;
    -- count;
    ++ data_address;

  }

  -- data_address;
  -- data;
  cfi_control_write_( sector_address, 0, 0x29 );
  reset_timer_masked( );

  /* wait while polling the status register */
  while( ( ( status_ =
             cfi_readb_( ( data_address - base_address ) ) ) &
           mkcmd_( interleave_, 0x80 ) ) !=
         ( * ( ( unsigned char * ) data ) & mkcmd_( interleave_, 0x80 ) ) ) {

    if( get_timer_masked( ) > CFG_FLASH_WRITE_TOUT ) {

      ERROR_PRINT( "Timed out multi-byte writing 0x%x to 0x%08x\n",
                   * ( ( unsigned char * ) data ), data_address );
      cfi_control_write_( base_address, mkaddr_( interleave_, 0 ),
                          mkcmd_( interleave_, 0xaa ) );
      cfi_control_write_( base_address, mkaddr_( interleave_, 1 ),
                          mkcmd_( interleave_, 0x55 ) );
      cfi_control_write_( base_address, 0, mkcmd_( interleave_, 0xf0 ) );
      return_code_ = 1;
      break;

    }

  }

#if 0

  for( ; ; ) {

    if( get_timer_masked( ) > CFG_FLASH_WRITE_TOUT ) {

      ERROR_PRINT( "Timed out multi-byte writing 0x%x to 0x%08x\n",
                   * ( ( unsigned char * ) data ), data_address );
      return_code_ = 1;
      break;

    }

    status_ = cfi_readb_( ( data_address - base_address ) );

    if( ( status_ & 0x80 ) == ( * ( ( unsigned char * ) data ) & 0x80 ) ) {

      break;

    }

    if( ( 0x20 == ( status_ & 0x20 ) ) || ( 0x02 == ( status_ & 0x02 ) ) ) {

      status_ = cfi_readb_( ( data_address - base_address ) );

      if( ( status_ & 0x80 ) == ( * ( ( unsigned char * ) data ) & 0x80 ) ) {

        break;

      } else {

        ERROR_PRINT( "Second DQ7 match failed!\n" );
        return_code_ = 1;
        break;

      }

    } else {

      continue;

    }

  }

#endif

  /* reset to read mode */
  cfi_control_write_( base_address, mkaddr_( interleave_, 0 ),
                      mkcmd_( interleave_, 0xaa ) );
  cfi_control_write_( base_address, mkaddr_( interleave_, 1 ),
                      mkcmd_( interleave_, 0x55 ) );
  cfi_control_write_( base_address, 0, mkcmd_( interleave_, 0xf0 ) );

  /* enable interrupts */
  if( 0 != flag_ ) { enable_interrupts( ); }

  /* return */
  return return_code_;

}

#endif /* ENABLE_MULTIBYTE_WRITE_ */

/*
  ----------------------------------------------------------------------
  cfi_write_
*/

static int cfi_write_( flash_info_t * info,
                       unsigned char * source,
                       unsigned long address,
                       unsigned long count ) {

  unsigned long odd_data_ = 0;
  int return_code_ = 0;

#ifdef __FLASH_C_VERIFY__

  unsigned char * save_source = source;
  unsigned long save_address = address;
  unsigned long save_count = count;

#endif /* __FLASH_C_VERIFY__ */

  if( info->flash_id != FLASH_CFI_ ) {

    WARN_PRINT( "Only works for CFI flash.\n" );
    return_code_ = 1;

  }

  if( 0 == count ) {

    return 0;

  }

#ifdef ENABLE_MULTIBYTE_WRITE_

  if( 0 != multi_byte ) {

    while( 0 < count ) {

      unsigned long bytes_to_write_;
      unsigned long sector_start_;
      unsigned long sector_end_;
      int sector_ = 0;

      while( ( address >= info->start [ sector_ ] ) &&
             ( sector_ < CFG_MAX_FLASH_SECT ) ) {

        ++ sector_;

      }

      -- sector_;
      sector_start_ = info->start [ sector_ ];

      if( sector_ < info->sector_count ) {

        sector_end_ = ( info->start [ ( sector_ + 1 ) ] - 1 );

      } else {

        sector_end_ = info->size - 1;

      }

      bytes_to_write_ = ( multi_byte < count ) ? multi_byte : count;

      if( bytes_to_write_ > ( multi_byte - ( address % multi_byte ) ) ) {

        bytes_to_write_ = ( multi_byte - ( address % multi_byte ) );

      }

      if( 0 !=
          ( return_code_ =
            write_buffer_write_( info->start [ 0 ], sector_start_,
                                 address, ( void * ) source,
                                 bytes_to_write_ ) ) ) {

        ERROR_PRINT( "write_buffer_write_( , 0x%x, 0x%x, 0x%x, %d ) " \
                     "returned %d\n", sector_start_, address,
                     ( void * ) source, bytes_to_write_, return_code_ );
        return return_code_;

      }

      count -= bytes_to_write_;
      address += bytes_to_write_;
      source += bytes_to_write_;

    }

  } else

#endif /* ENABLE_MULTIBYTE_WRITE_ */

  {

    while( 0 < count ) {

      if( ( return_code_ =
            cfi_data_write_( info, address,
                             * ( unsigned char * ) source ) ) != 0 ) {

        ERROR_PRINT( "cfi_data_write_( , 0x%08x, 0x%02x ) returned %d\n",
                     address, * ( unsigned char * ) source, return_code_ );
        return return_code_;

      }

      -- count;
      ++ address;
      ++ source;

    }

  }

#ifdef __FLASH_C_VERIFY__

  /*
    Verify
  */

  {

    unsigned char * correct_ = save_source;
    unsigned long address_ = save_address;

    address_ += info->start [ 0 ];

    for( ; address_ < ( save_address + info->start [ 0 ] + save_count );
         ++ address_ ) {

      unsigned char questionable_ = cfi_readb_( address_ );

      if( * correct_ != questionable_ ) {

        ERROR_PRINT( "Mismatch at 0x%08x: 0x%02x != 0x%02x\n",
                     address_, * correct_, questionable_ );

      }

      ++ correct_;

    }

  }

#endif /* __FLASH_C_VERIFY__ */

  return return_code_;

}

#elif defined( LSI_ARCH_APP3 )

/*
  ----------------------------------------------------------------------
  cfi_control_write_
*/

static void cfi_control_write_( unsigned long base,
                                unsigned long offset,
                                unsigned long value ) {

  unsigned long address_ = base + ( offset << 1 );
  unsigned long real_address_ = EAC_address_( address_ );

  REMAP_RESET( );
  //DEBUG_PRINT( "address:0x%08x/0x%08x value=0x%x\n", address_, real_address_, value );
  ( * ( ( volatile unsigned short * ) ( real_address_ ) ) = value );
  REMAP_NORMAL( );
  __asm__ __volatile__ ( "" : : : "memory" );

  return;

}

/*
  ----------------------------------------------------------------------
  cfi_readb_
*/

static unsigned char cfi_readb_( unsigned long address ) {

  unsigned char value_ = 0xff;
  unsigned long address_ = EAC_address_( address );

  REMAP_RESET( );

#ifdef FLASH_ACCESS_WORKAROUND_

  {

    unsigned long workaround_value_;

    workaround_value_ =
      * ( ( volatile unsigned long * ) ( ( address_ / 4 ) * 4 ) );
    //DEBUG_PRINT( "workaround_value_=0x%08x index=%d\n", workaround_value_, ( address_ % 4 ) );

    switch( ( address_ % 4 ) ) {

    case 0:
      value_ = ( workaround_value_ & 0xff );
      //DEBUG_PRINT( "workaround_value_=0x%x value_=0x%x\n", workaround_value_, value_ );
      break;

    case 1:
      value_ = ( ( workaround_value_ & 0xff00 ) >> 8 );
      DEBUG_PRINT( "workaround_value_=0x%x value_=0x%x\n",
                   workaround_value_, value_ );
      break;

    case 2:
      value_ = ( ( workaround_value_ & 0xff0000 ) >> 16 );
      DEBUG_PRINT( "workaround_value_=0x%x value_=0x%x\n",
                   workaround_value_, value_ );
      break;

    case 3:
      value_ = ( ( workaround_value_ & 0xff000000 ) >> 24 );
      DEBUG_PRINT( "workaround_value_=0x%x value_=0x%x\n",
                   workaround_value_, value_ );
      break;

    default:
      ERROR_PRINT( "Access Error!  address=0x%x width=8\n", address );
      break;

    }

  }

#else  /* FLASH_ACCESS_WORKAROUND_ */

  value_ = * ( ( volatile unsigned char * ) address_ );

#endif /* FLASH_ACCESS_WORKAROUND_ */

  REMAP_NORMAL( );
  DEBUG_PRINT( "value_=0x%x\n", value_ );

  return value_;

}

/*
  ----------------------------------------------------------------------
  cfi_readw_
*/

static unsigned short cfi_readw_( unsigned long address ) {

  unsigned short value_ = 0xffff;
  unsigned long address_ = EAC_address_( address );

  REMAP_RESET( );

#ifdef FLASH_ACCESS_WORKAROUND_

  {

    unsigned long workaround_value_;

    workaround_value_ =
      * ( ( volatile unsigned long * ) ( ( address_ / 4 ) * 4 ) );

    switch( ( address_ % 4 ) ) {

    case 0:
      value_ = ( workaround_value_ & 0xffff );
      DEBUG_PRINT( "workaround_value_=0x%x value_=0x%x\n",
                   workaround_value_, value_ );
      break;

    case 2:
      value_ = ( ( workaround_value_ & 0xffff0000 ) >> 16 );
      //DEBUG_PRINT( "workaround_value_=0x%x value_=0x%x\n", workaround_value_, value_ );
      break;

    default:
      ERROR_PRINT( "Alignment Error!  address=0x%x width=16\n", address );
      break;

    }

  }

#else  /* FLASH_ACCESS_WORKAROUND_ */

  value_ = * ( ( volatile unsigned short * ) address_ );

#endif /* FLASH_ACCESS_WORKAROUND_ */

  REMAP_NORMAL( );
  //DEBUG_PRINT( "value_=0x%x\n", value_ );

  return value_;

}

/*
  ----------------------------------------------------------------------
  cfi_readl_
*/

static unsigned long cfi_readl_( unsigned long address ) {

  unsigned long value_;

  REMAP_RESET( );
  value_ =
    * ( ( volatile unsigned long * ) EAC_address_( address ) );
  REMAP_NORMAL( );

  return value_;

}

/*
  ----------------------------------------------------------------------
  cfi_data_write_
*/

static int cfi_data_write_( flash_info_t * info,
                            unsigned long address,
                            unsigned short value ) {

  unsigned long base_ = info->start [ 0 ];
  unsigned long status_;
  int flag_;

  /* See if the value is already written. */

  {

    unsigned short current_value_;

    current_value_ = cfi_readw_( address );

    if( current_value_ == value ) {

      //DEBUG_PRINT( "The address already contains the value!\n" );
      return 0;

    }

  }

  /* Check if FLASH is (sufficiently) erased. */

  {

    unsigned short current_value_;

    current_value_ = cfi_readw_( address );

    if( ( current_value_ & value ) != value ) {

      WARN_PRINT( "FLASH not erased at address 0x%08x\n", address );
      return 2;

    }

  }

  /* disable interrupts */
  flag_ = disable_interrupts( );

  /* write setup */
  cfi_control_write_( base_, mkaddr_( interleave_, 0 ),
                      mkcmd_( interleave_, 0xaa ) );
  cfi_control_write_( base_, mkaddr_( interleave_, 1 ),
                      mkcmd_( interleave_, 0x55 ) );
  cfi_control_write_( base_, mkaddr_( interleave_, 0 ),
                      mkcmd_( interleave_, 0xa0 ) );
  cfi_control_write_( address, 0, value );

  /* arm simple, non interrupt dependent timer */
  reset_timer_masked( );

  /* wait while polling the status register */
  while( ( ( status_ =
             cfi_readw_( address ) ) & mkcmd_( interleave_, 0x80 ) ) !=
         ( value & mkcmd_( interleave_, 0x80 ) ) ) {

    if( get_timer_masked( ) > CFG_FLASH_WRITE_TOUT ) {

      ERROR_PRINT( "Timed out writing 0x%04x to 0x%08x\n", value, address );
      cfi_control_write_( base_, 0, mkcmd_( interleave_, 0xf0 ) );
      if( 0 != flag_ ) { enable_interrupts( ); }
      return 1;

    }

  }

  cfi_control_write_( base_, 0, mkcmd_( interleave_, 0xf0 ) );
  if( 0 != flag_ ) { enable_interrupts( ); }
  return 0;

}

/*
  ----------------------------------------------------------------------
  write_buffer_write_
*/

#ifdef ENABLE_MULTIBYTE_WRITE_

static int write_buffer_write_( unsigned long base_address,
                                unsigned long sector_address,
                                unsigned long data_address,
                                void * data,
                                int count ) {

  int status_;
  int flag_;
  int return_code_ = 0;

  /* disable interrupts */
  flag_ = disable_interrupts( );

  cfi_control_write_( base_address, mkaddr_( interleave_, 0 ),
                      mkcmd_( interleave_, 0xaa ) );
  cfi_control_write_( base_address, mkaddr_( interleave_, 1 ),
                      mkcmd_( interleave_, 0x55 ) );
  cfi_control_write_( sector_address, 0, mkcmd_( interleave_, 0x25 ) );
  cfi_control_write_( sector_address, 0,
                      mkcmd_( interleave_, ( ( count / 2 ) - 1 ) ) );

  while( 0 < count ) {

    cfi_control_write_( data_address, 0, * ( ( unsigned short * ) data ) );
    data += 2;
    count -= 2;
    data_address += 2;

  }

  data_address -= 2;
  data -= 2;
  cfi_control_write_( sector_address, 0, mkcmd_( interleave_, 0x29 ) );
  reset_timer_masked( );

  /* wait while polling the status register */
  while( ( ( status_ =
             cfi_readw_( ( data_address - base_address ) ) ) &
           mkcmd_( interleave_, 0x80 ) ) !=
         ( * ( ( unsigned short * ) data ) & mkcmd_( interleave_, 0x80 ) ) ) {
#if 0
    printf( "status_=0x%x/0x%x data=0x%x/0x%x\n",
            status_, ( status_ & mkcmd_( interleave_, 0x80 ) ),
            ( unsigned short * ) data,
            ( * ( ( unsigned short * ) data ) & mkcmd_( interleave_, 0x80 ) ) );
#endif
    if( get_timer_masked( ) > ( CFG_FLASH_WRITE_TOUT * 20 ) ) {

      ERROR_PRINT( "Timed out multi-byte writing 0x%x to 0x%08x\n",
                   * ( ( unsigned char * ) data ), data_address );
      cfi_control_write_( base_address, mkaddr_( interleave_, 0 ),
                          mkcmd_( interleave_, 0xaa ) );
      cfi_control_write_( base_address, mkaddr_( interleave_, 1 ),
                          mkcmd_( interleave_, 0x55 ) );
      cfi_control_write_( base_address, 0, mkcmd_( interleave_, 0xf0 ) );
      return_code_ = 1;
      break;

    }

  }
#if 0
  printf( "status_=0x%x/0x%x data=0x%x/0x%x\n",
          status_, ( status_ & mkcmd_( interleave_, 0x80 ) ),
          ( unsigned short * ) data,
          ( * ( ( unsigned short * ) data ) & mkcmd_( interleave_, 0x80 ) ) );
#endif
#if 0

  for( ; ; ) {

    if( get_timer_masked( ) > CFG_FLASH_WRITE_TOUT ) {

      ERROR_PRINT( "Timed out multi-byte writing 0x%x to 0x%08x\n",
                   * ( ( unsigned char * ) data ), data_address );
      return_code_ = 1;
      break;

    }

    status_ = cfi_readb_( ( data_address - base_address ) );

    if( ( status_ & 0x80 ) == ( * ( ( unsigned char * ) data ) & 0x80 ) ) {

      break;

    }

    if( ( 0x20 == ( status_ & 0x20 ) ) || ( 0x02 == ( status_ & 0x02 ) ) ) {

      status_ = cfi_readb_( ( data_address - base_address ) );

      if( ( status_ & 0x80 ) == ( * ( ( unsigned char * ) data ) & 0x80 ) ) {

        break;

      } else {

        ERROR_PRINT( "Second DQ7 match failed!\n" );
        return_code_ = 1;
        break;

      }

    } else {

      continue;

    }

  }

#endif

  /* reset to read mode */
  cfi_control_write_( base_address, mkaddr_( interleave_, 0 ),
                      mkcmd_( interleave_, 0xaa ) );
  cfi_control_write_( base_address, mkaddr_( interleave_, 1 ),
                      mkcmd_( interleave_, 0x55 ) );
  cfi_control_write_( base_address, 0, mkcmd_( interleave_, 0xf0 ) );

  /* enable interrupts */
  if( 0 != flag_ ) { enable_interrupts( ); }

  /* return */
  return return_code_;

}

#endif /* ENABLE_MULTIBYTE_WRITE_ */

/*
  ----------------------------------------------------------------------
  cfi_write_
*/

static int cfi_write_( flash_info_t * info,
                       unsigned char * source,
                       unsigned long address,
                       unsigned long count ) {

  int return_code_ = 0;
  unsigned char odd_data_;

#ifdef __FLASH_C_VERIFY__

  unsigned char * save_source = source;
  unsigned long save_address = address;
  unsigned long save_count = count;

#endif /* __FLASH_C_VERIFY__ */

  if( info->flash_id != FLASH_CFI_ ) {

    WARN_PRINT( "Only works for CFI flash.\n" );
    return_code_ = 1;

  }

  if( 0 == count ) {

    return 0;

  }

  address += info->start [ 0 ];

  /*
    Handle unaligned start byte.
  */

  if( 0 != ( address & 1 ) ) {

    unsigned long temp_ = cfi_readl_( ( address / 4 ) * 4 );

    switch( address % 4 ) {

    case 1:
      odd_data_ = ( unsigned char ) ( temp_ & 0xff ) | * source;
      break;

    case 3:
      odd_data_ = ( ( unsigned char ) ( temp_ & 0xff0000 ) ) >> 16 | * source;
      break;

    }

    if( ( return_code_ =
          cfi_data_write_( info, ( address & ~ 1 ), odd_data_ ) ) != 0 ) {

      ERROR_PRINT( "cfi_data_write_( , 0x%08x, 0x%04x ) returned %d\n",
                   ( address & ~ 1 ), odd_data_, return_code_ );
      return return_code_;

    }

    -- count;
    ++ source;
    ++ address;

  }

  /*
    Handle aligned bytes.
  */

#ifdef ENABLE_MULTIBYTE_WRITE_

  if( 0 != multi_byte ) {

    unsigned base_ = info->start [ 0 ];

    while( 0 < count ) {

      unsigned long bytes_to_write_;
      unsigned long sector_start_;
      unsigned long sector_end_;
      int sector_ = 0;

      while( ( address >= info->start [ sector_ ] ) &&
             ( sector_ < CFG_MAX_FLASH_SECT ) ) {

        ++ sector_;

      }

      -- sector_;
      sector_start_ = info->start [ sector_ ];

      if( sector_ < info->sector_count ) {

        sector_end_ = ( info->start [ ( sector_ + 1 ) ] - 1 );

      } else {

        sector_end_ = info->size - 1;

      }

      bytes_to_write_ = ( multi_byte < count ) ? multi_byte : count;

      if( bytes_to_write_ > ( multi_byte - ( address % multi_byte ) ) ) {

        bytes_to_write_ = ( multi_byte - ( address % multi_byte ) );

      }

      bytes_to_write_ -= ( bytes_to_write_ % 2 );

      if( 0 !=
          ( return_code_ =
            write_buffer_write_( info->start [ 0 ], sector_start_,
                                 address, ( void * ) source,
                                 bytes_to_write_ ) ) ) {

        ERROR_PRINT( "write_buffer_write_( , 0x%x, 0x%x, 0x%x, %d ) " \
                     "returned %d\n", sector_start_, address,
                     ( void * ) source, bytes_to_write_, return_code_ );
        return return_code_;

      }

      count -= bytes_to_write_;
      address += bytes_to_write_;
      source += bytes_to_write_;

    }

  } else

#endif /* ENABLE_MULTIBYTE_WRITE_ */

  {

    while( 1 < count ) {

      if( ( return_code_ =
            cfi_data_write_( info, address, * ( ushort * ) source ) ) != 0 ) {

        ERROR_PRINT( "cfi_data_write_( , 0x%08x, 0x%04x ) returned %d\n",
                     address, * ( ushort * ) source, return_code_ );
        return return_code_;

      }

      source += 2;
      count -= 2;
      address += 2;

    }

  }

  /*
    Handle unaligned end bytes.
  */

  if( 0 != count ) {

    unsigned long temp_ = cfi_readl_( ( address / 4 ) * 4 );

    switch( address % 4 ) {

    case 1:
      odd_data_ = ( unsigned char ) ( temp_ & 0xff ) | * source;
      break;

    case 3:
      odd_data_ = ( ( unsigned char ) ( temp_ & 0xff0000 ) ) >> 16 | * source;
      break;

    }

    if( ( return_code_ =
          cfi_data_write_( info, ( address & ~ 1 ), odd_data_ ) ) != 0 ) {

      ERROR_PRINT( "cfi_data_write_( , 0x%08x, 0x%04x ) returned %d\n",
                   ( address & ~ 1 ), odd_data_, return_code_ );
      return return_code_;

    }

  }

#ifdef __FLASH_C_VERIFY__

  /*
    Verify
  */

  {

    unsigned char * correct_ = save_source;
    unsigned long address_ = save_address;

    address_ += info->start [ 0 ];

    for( ; address_ < ( save_address + info->start [ 0 ] + save_count );
         ++ address_ ) {

      unsigned char questionable_ = cfi_readb_( address_ );

      if( * correct_ != questionable_ ) {

        ERROR_PRINT( "Mismatch at 0x%08x: 0x%02x != 0x%02x\n",
                     address_, * correct_, questionable_ );

      }

      ++ correct_;

    }

  }

#endif /* __FLASH_C_VERIFY__ */

  return return_code_;

}

#else
#error "Unknown Architecture"
#endif

static int cfi_erase_sector_( flash_info_t * info,
                              int first, int last ) {

  int return_code_ = 0;
  int flags_, sector_;
  ulong start_, last_;
  unsigned long base_ = info->start [ 0 ];

#ifdef APP3K_NONOR
  return 1;
#endif

  if( ( first < 0 ) || ( first > last ) ) {

    WARN_PRINT( "No sectors to erase\n" );
    return_code_ = 1;

  } else {

    if( info->flash_id != FLASH_CFI_ ) {

      WARN_PRINT( "Only works for CFI flash.\n" );
      return_code_ = 1;

    }

    start_ = get_timer( 0 );
    last_ = start_;

    /* Disable interrupts */
    flags_ = disable_interrupts( );

    /* Start erase on unprotected sectors */
    for( sector_ = first; sector_ <= last; ++ sector_ ) {

      if( info->protect [ sector_ ] == 0 ) {

        unsigned long address_ = info->start [ sector_ ];
        unsigned long status_;

        //DEBUG_PRINT( "Erasing sector %d\n", sector_ );

        /* arm simple, non interrupt dependent timer */
        reset_timer_masked( );

        cfi_control_write_( base_, mkaddr_( interleave_, 0 ),
                            mkcmd_( interleave_, 0xaa ) );
        cfi_control_write_( base_, mkaddr_( interleave_, 1 ),
                            mkcmd_( interleave_, 0x55 ) );
        cfi_control_write_( base_, mkaddr_( interleave_, 0 ),
                            mkcmd_( interleave_, 0x80 ) );
        cfi_control_write_( base_, mkaddr_( interleave_, 0 ),
                            mkcmd_( interleave_, 0xaa ) );
        cfi_control_write_( base_, mkaddr_( interleave_, 1 ),
                            mkcmd_( interleave_, 0x55 ) );
        cfi_control_write_( address_, 0, mkcmd_( interleave_, 0x30 ) );

        while( ( ( status_ =
                   cfi_readw_( address_ ) ) & mkcmd_( interleave_, 0x80 ) ) !=
               mkcmd_( interleave_, 0x80 ) ) {

          if( get_timer_masked( ) > CFG_FLASH_ERASE_TOUT ) {

            WARN_PRINT( "Sector erase timed out.\n" );

            /*
              suspend erase (this is the ONLY command allowed
              during an erase)
            */

            cfi_control_write_( base_, 0, mkcmd_( interleave_, 0xb0 ) );
            cfi_control_write_( base_, 0, mkcmd_( interleave_, 0xf0 ) );
            return_code_ = 1;
            if( 0 != flags_ ) { enable_interrupts( ); }
            break;

          }

        }

        /* resest to read mode */
        cfi_control_write_( base_, 0, mkcmd_( interleave_, 0xf0 ) );
        //DEBUG_PRINT( "done\n" );

#ifdef __FLASH_C_VERIFY__

        /*
          Verify
        */

        {

          unsigned long verify_address_ = address_;

          for( ; verify_address_ <
                 ( address_ + ( info->size / info->sector_count ) );
               verify_address_ += 4 ) {

            unsigned long value_;

            value_ = cfi_readl_( verify_address_ );

            if( 0xffffffff != value_ ) {

              ERROR_PRINT( "Not Erased at 0x%lx\n", verify_address_ );
              return_code_ = 1;
              break;

            }

          }

          if( 0 != return_code_ ) {

            break;

          }

        }

#endif /* __FLASH_C_VERIFY__ */

      } else {

        WARN_PRINT( "Sector %d is protected!\n", sector_ );

      }

    }

    if( 0 != flags_ ) { enable_interrupts( ); }
  
  }

  return return_code_;

}

/*
  ----------------------------------------------------------------------
  cfi_detect_
*/

static int cfi_detect_( void ) {

  int return_code_ = -1;
  int device_ = 0;
  unsigned long base_ = 0;
  int il_ = 1;
  unsigned long detected_size_ = 0;

#ifdef APP3K_NONOR
  return -1;
#endif

  /* Clear flash_info */

  {

    int index_;

    for( index_ = 0; index_ < CFG_MAX_FLASH_BANKS; ++ index_ ) {

      memset( ( void * ) & ( flash_info [ index_ ] ), 0,
              sizeof( flash_info_t ) );
      ( flash_info [ index_ ] ).flash_id = FLASH_UNKNOWN;

    }

  }

  /* Detect FLASH and fill in flash_info */

  for( ; ; ) {

    int detected_ = 0;
    int size_ = 0;
    int erase_regions_;

    //DEBUG_PRINT( "il_=%d base_=0x%x detected_=%d\n", il_, base_, detected_ );

    while( il_ <= 2 ) {

      //DEBUG_PRINT( "base_=0x%x il_=%d\n", base_, il_ );

      if( ( 'Q' == cfi_readb_( base_ + ( 0x10 << il_ ) ) ) &&
          ( 'R' == cfi_readb_( base_ + ( 0x11 << il_ ) ) ) &&
          ( 'Y' == cfi_readb_( base_ + ( 0x12 << il_ ) ) ) ) {

        /*
          If the device at this base_ is already in query mode, this is
          an alias for the previous device.
        */

        //DEBUG_PRINT( "Aliasing...\n" );
        break;

      }

      //DEBUG_PRINT( "Writing Query Command\n" );
      cfi_control_write_( base_,
                          mkaddr_( il_, 0 ),
                          mkcmd_( il_, 0x98 ) );

      if( ( 'Q' == cfi_readb_( base_ + ( 0x10 << il_ ) ) ) &&
          ( 'R' == cfi_readb_( base_ + ( 0x11 << il_ ) ) ) &&
          ( 'Y' == cfi_readb_( base_ + ( 0x12 << il_ ) ) ) ) {

        {

          int multi_byte_;

          multi_byte_ = ( 1 <<
                          ( ( cfi_readb_( base_ + ( 0x2b << il_ ) ) << 8 ) |
                            cfi_readb_( base_ + ( 0x2a << il_ ) ) ) );

          if( -1 == multi_byte ) {

            multi_byte = multi_byte_;

          } else if( multi_byte != multi_byte_ ) {

            WARN_PRINT( "Multi-Byte Writes Disabled.\n" );
            multi_byte = 0;

          }

        }

        size_ = ( 1 << cfi_readb_( base_ + ( 0x27 << il_ ) ) );
        size_ *= il_;

        if( ( size_ + detected_size_ ) > max_size_( ) ) {

          WARN_PRINT( "Reducing size, not enough address lines.\n" );
          size_ = ( max_size_( ) - detected_size_ );

        }

        detected_size_ += size_;
        erase_regions_ = cfi_readb_( base_ + ( 0x2c << il_ ) );
        //DEBUG_PRINT( "CFI device at 0x%08x: %d Mbytes %d erase region(s)\n", base_, ( size_ / 1024 / 1024 ), erase_regions_ );
        detected_ = 1;
        return_code_ = 0;

        {

          int erase_region_;
          flash_info_t * flash_ = & ( flash_info [ device_ ] );
          unsigned long location_ = base_;
          int sector_ = 0;
          int regions_detected_size_ = 0;

          flash_->flash_id = FLASH_CFI_;
          flash_->sector_count = 0;
          flash_->size = size_;
          memset( ( void * ) & flash_->start, 0, sizeof( flash_->start ) );
          memset( ( void * ) & flash_->protect, 0, sizeof( flash_->protect ) );

          for( erase_region_ = 1; erase_region_ <= erase_regions_;
               ++ erase_region_ ) {

            int number_of_sectors_;
            int sector_size_;
            int index_;
            int offset_ = ( 0x2d + ( ( erase_region_ - 1 ) * 4 ) );

            number_of_sectors_ =
              1 +
              ( ( cfi_readb_( base_ + ( ( offset_ + 1 ) << il_ ) ) << 8 ) |
                cfi_readb_( base_ + ( offset_ << il_ ) ) );
            sector_size_ =
              256 * il_ *
              ( ( cfi_readb_( base_ + ( ( offset_ + 3 ) << il_ ) ) << 8 ) |
                cfi_readb_( base_ + ( ( offset_ + 2 ) << il_ ) ) );
            //DEBUG_PRINT( "Setting up erase region %d: %d %d Kbyte sector(s)\n",                         erase_region_, number_of_sectors_,                         ( sector_size_ / 1024 ) );

            if( ( ( number_of_sectors_ * sector_size_ ) +
                  regions_detected_size_ ) > size_ ) {

              WARN_PRINT( "Reducing the number of sectors, " \
                          "not enough address lines.\n" );
              number_of_sectors_ =
                ( size_ - regions_detected_size_ ) / sector_size_;
              

            }

            regions_detected_size_ += ( number_of_sectors_ * sector_size_ );
            flash_->sector_count += number_of_sectors_;

            for( index_ = 0; index_ < number_of_sectors_; ++ index_ ) {

              flash_->start [ sector_ ++ ] = location_;
              location_ += sector_size_;

            }

          }

        }

        ++ device_;
        break;

      }

      ++ il_;

    }

    if( 0 == detected_ ) {

      break;

    }

    if( max_size_( ) == detected_size_ ) {

      break;

    }

    base_ += size_;

  }

  if( 0 == return_code_ ) {

    int index_ = 0;

    interleave_ = il_;
    ops_.erase = cfi_erase_sector_;
    ops_.write = cfi_write_;
    ops_.read_8 = cfi_readb_;
    ops_.read_16 = cfi_readw_;
    ops_.read_32 = cfi_readl_;

    while( index_ < CFG_MAX_FLASH_BANKS ) {

      flash_info_t * flash_ = & ( flash_info [ index_ ] );

      if( FLASH_UNKNOWN != flash_->flash_id ) {

        cfi_control_write_( flash_->start [ 0 ], 0,
                            mkcmd_( interleave_, 0xf0 ) );

      }

      ++ index_;

    }

  }

  return return_code_;

}

/*
  ======================================================================
  ======================================================================
  Static Functions
  ======================================================================
  ======================================================================
*/

static void inline spin_wheel( void );

/*
  ----------------------------------------------------------------------
  spin_wheel
*/

static void inline spin_wheel( void ) {

  static int index_ = 0;
  static char characters_ [ ] = "\\/-";

  printf( "\010%c", characters_ [ ( index_ % 3 ) ] );

  return;

}

/*
  ======================================================================
  ======================================================================
  U-Boot Interface
  ======================================================================
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  app3xx_flash_readb
*/

unsigned char app3xx_flash_readb( unsigned long address ) {

  if( 0 == ready_ ) {

    ERROR_PRINT( "FLASH isn't ready!\n" );

  } else {

    return ops_.read_8( address );

  }

  return 0;

}

/*
  ----------------------------------------------------------------------
  app3xx_flash_readw
*/

unsigned short app3xx_flash_readw( unsigned long address ) {

  if( 0 == ready_ ) {

    ERROR_PRINT( "FLASH isn't ready!\n" );

  } else {

    return ops_.read_16( address );

  }

  return 0;

}

/*
  ----------------------------------------------------------------------
  app3xx_flash_readl
*/

unsigned long app3xx_flash_readl( unsigned long address ) {

  if( 0 == ready_ ) {

    ERROR_PRINT( "FLASH isn't ready!\n" );

  } else {

    return ops_.read_32( address );

  }

  return 0;

}

/*
  ----------------------------------------------------------------------
  app3xx_flash_update_ram

  N.B. This has to work before flash_init( )!
*/

void app3xx_flash_update_ram( void ) {

#ifdef APP3K_NONOR
  return;
#endif

#if defined( LSI_ARCH_APP3K )

  flash_controller_configuration_t configuration_;

  configuration_.raw = 0;
  configuration_.bits.clock_wait = 0x14;
  configuration_.bits.write_protect = 1;
  configuration_.bits.reset =1;
  configuration_.bits.web_late = 0;
  configuration_.bits.nand_flash_select = 1;
  configuration_.bits.nor_disable_direct = 1;
  configuration_.bits.nor_flash_respond = 1;
  configuration_.bits.nor_flash_interrupt = 0;
  //DEBUG_PRINT( "configuration_.raw = 0x%x\n", configuration_.raw );
  writel( configuration_.raw, 0x68000010 );
  /*writel( 0x400UL, 0x60000180UL );*/
  app3k_read_( ( void * ) & ( app3xx_environment_buffer_ [ 0 ] ),
               CFG_ENV_OFFSET,
               CFG_ENV_SIZE );
  /*writel( 0x401UL, 0x60000180UL );*/

#ifdef CFG_ENV_ADDR_REDUND
  app3k_read_( ( void * ) & ( app3xx_environment_buffer_redundant_ [ 0 ] ),
               CFG_ENV_OFFSET_REDUND,
               CFG_ENV_SIZE_REDUND );
#endif /* CFG_ENV_ADDR_REDUND */

  /*writel( 0x402UL, 0x60000180UL );*/

#elif defined( LSI_ARCH_APP3 )

  int index_;
  unsigned long gpio_mux_;

  /*
    A number of assumptions follow.

    -1-
    The sector size is an even number of longs.  This should always be true...
    -2-
    The value in GPIO_MUX_DEFAULT will allow access to the base of the first
    bank of flash.
  */

  gpio_mux_ = * ( ( volatile unsigned long * ) ( GPIO_MUX ) );
  * ( ( volatile unsigned long * ) ( GPIO_MUX ) ) = GPIO_MUX_DEFAULT;
  __asm__ __volatile__ ( "" : : : "memory" );

  REMAP_RESET( );

  {

    unsigned long * destination_ =
      ( unsigned long * ) & ( app3xx_environment_buffer_ [ 0 ] );
    unsigned long * source_ = ( unsigned long * ) CFG_ENV_OFFSET;

    for( index_ = 0; index_ < ( CFG_ENV_SIZE / 4 ); ++ index_ ) {

      * destination_ = * source_;
      ++ destination_;
      ++ source_;

    }

#ifdef CFG_ENV_ADDR_REDUND

    destination_ =
      ( unsigned long * ) & ( app3xx_environment_buffer_redundant_ [ 0 ] );
    source_ = ( unsigned long * ) CFG_ENV_OFFSET_REDUND;

    for( index_ = 0; index_ < ( CFG_ENV_SIZE / 4 ); ++ index_ ) {

      * destination_ = * source_;
      ++ destination_;
      ++ source_;

    }

#endif /* CFG_ENV_ADDR_REDUND */

  }
      
  REMAP_NORMAL( );

  * ( ( volatile unsigned long * ) ( GPIO_MUX ) ) = gpio_mux_;
  __asm__ __volatile__ ( "" : : : "memory" );

#else
#error "Unknown Architecture"
#endif

}

/*
  ----------------------------------------------------------------------
  flash_print_info
*/

void flash_print_info( flash_info_t * info ) {

  int index_;

#ifdef APP3K_NONOR
  printf( "Flash intentionally disabled in software.\n" );
  return;
#endif

  if( info->flash_id == FLASH_UNKNOWN ) {

    printf( "Missing or unknown FLASH type\n" );

  } else {

    switch( info->flash_id & FLASH_TYPEMASK ) {

    case FLASH_AM640M_:
      printf("Amd29LV640M\n");
      break;

    case FLASH_AM640M_DORAL_:
      printf("Amd29LV640M (Doral)\n");
      break;

    case FLASH_SG29GL01G_:
      printf( "Sg29GL01G x 2\n" );
      break;

    case FLASH_SG29GL512_:
      printf( "Sg29GL512 x 2\n" );
      break;

    case FLASH_SG29GL256_:
      printf( "Sg29GL256 x 2\n" );
      break;

    case FLASH_CFI_:
      printf( "CFI FLASH\n" );
      break;

    default:
      printf("Unknown Chip Type\n");
      break;

    }

    printf( "  Size: %ld MB in %d Sectors\n",
            info->size >> 20, info->sector_count );
    printf( "  Sector Start Addresses:" );

    for( index_ = 0; index_ < info->sector_count; ++ index_ ) {

      if( ( index_ % 5 ) == 0 ) {

        printf("\n   ");

      }

      printf( " %08lX%s",
              info->start [ index_ ],
              info->protect [ index_ ] ? " (RO)" : "     " );

    }

    printf( "\n" );

  }

  return;

}

/*
  ----------------------------------------------------------------------
  flash_erase
*/

int flash_erase( flash_info_t * info, int first, int last ) {

  if( 1 == ready_ ) {

    return ops_.erase( info, first, last );

  } else {

    ERROR_PRINT( "No FLASH Available!\n" );
    return 1;

  }

}

/*
  ----------------------------------------------------------------------
  write_buff

  Copy memory to flash, returns codes are:

  0 - OK
  1 - write timeout
  2 - Flash not erased
  4 - Flash not identified
*/

int write_buff( flash_info_t * info, uchar * source, ulong address,
                ulong count ) {

  //DEBUG_PRINT( "address=0x%lx\n", address );

  if( 1 == ready_ ) {

    return ops_.write( info, ( void * ) source, address, count );

  } else {

    ERROR_PRINT( "No FLASH Available!\n" );
    return 4;

  }

}

/*
  ----------------------------------------------------------------------
  flash_init
*/

unsigned long flash_init( void ) {

  ulong size_ = 0;

#ifdef APP3K_NONOR
  return 0;
#endif

#ifdef LSI_ARCH_APP3K

  flash_controller_configuration_t configuration_;

  configuration_.raw = 0;
  configuration_.bits.clock_wait = 0x14;
  configuration_.bits.write_protect = 1;
  configuration_.bits.reset =1;
  configuration_.bits.web_late = 0;
  configuration_.bits.nand_flash_select = 1;
  configuration_.bits.nor_disable_direct = 1;
  configuration_.bits.nor_flash_respond = 1;
  configuration_.bits.nor_flash_interrupt = 0;
  //DEBUG_PRINT( "configuration_.raw = 0x%x\n", configuration_.raw );
  * ( ( volatile unsigned long * ) 0x68000010 ) = configuration_.raw;

#endif /* LSI_ARCH_APP3K */

#ifdef LSI_ARCH_APP3

  set_io_buf_ctrl( );
  set_gpio_mux( );
  set_feac( );
  set_feac_flip_bits( );

#endif /* LSI_ARCH_APP3 */

  if( 0 == cfi_detect_( ) ) {

    printf( "Detected CFI\n" );

  } else if( 0 == custom_detect_( ) ) {

    printf( "Detected Custom\n" );

  } else {

    ERROR_PRINT( "No Known FLASH Detected\n" );
    return 0;
  }

  set_feac_flip_bits( );
  ready_ = 1;

  size_ = ( flash_info [ 0 ] ).size;

  if( FLASH_UNKNOWN != ( flash_info [ 1 ] ).flash_id ) {

    size_ += ( flash_info [ 1 ] ).size;

  }

  /*
    Protect monitor and environment sectors
  */

  flash_protect( FLAG_PROTECT_SET,
                 CFG_FLASH_BASE,
                 CFG_FLASH_BASE + CFG_MONITOR_LEN - 1,
                 & flash_info [ 0 ] );
  flash_protect( FLAG_PROTECT_SET,
                 CFG_ENV_ADDR,
                 CFG_ENV_ADDR + CFG_ENV_SIZE - 1,
                 & flash_info [ 0 ] );
#ifdef CFG_ENV_ADDR_REDUND
  flash_protect( FLAG_PROTECT_SET,
                 CFG_ENV_ADDR_REDUND,
                 CFG_ENV_ADDR_REDUND + CFG_ENV_SIZE_REDUND - 1,
                 & flash_info [ 0 ] );
#endif /* CFG_ENV_ADDR_REDUND */

  /* that's all */
  return size_;

}

/*
  ======================================================================
  ======================================================================
  Extended Address Control
  ======================================================================
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  get_io_buf_ctrl
*/

unsigned long get_io_buf_ctrl( void ) {

  return * ( ( volatile unsigned long * ) ( IO_BUF_CTRL ) );

}

/*
  ----------------------------------------------------------------------
  set_io_buf_ctrl
*/

void set_io_buf_ctrl( void ) {

  unsigned long io_buf_ctrl_;
  char * io_buf_ctrl_string_ = ( char * ) 0;

  if( ( char * ) 0 ==
      ( io_buf_ctrl_string_ = getenv( "io_buffer_control" ) ) ) {

    io_buf_ctrl_ = IO_BUF_CTRL_DEFAULT;

  } else {

    io_buf_ctrl_ = simple_strtoul( io_buf_ctrl_string_, NULL, 16 );

  }

  * ( ( volatile unsigned long * ) ( IO_BUF_CTRL ) ) = io_buf_ctrl_;

}

/*
  ----------------------------------------------------------------------
  get_gpio_mux
*/

unsigned long get_gpio_mux( void ) {

  return * ( ( volatile unsigned long * ) ( GPIO_MUX ) );

}

/*
  ----------------------------------------------------------------------
  set_gpio_mux
*/

void set_gpio_mux( void ) {

  unsigned long gpio_mux_;
  char * gpio_mux_string_ = ( char * ) 0;

  if( ( char * ) 0 == ( gpio_mux_string_ = getenv( "gpio_mux" ) ) ) {

    gpio_mux_ = GPIO_MUX_DEFAULT;

  } else {

    gpio_mux_ = simple_strtoul( gpio_mux_string_, NULL, 16 );

  }

  * ( ( volatile unsigned long * ) ( GPIO_MUX ) ) = gpio_mux_;

}

/*
  ----------------------------------------------------------------------
  get_feac
*/

unsigned long get_feac( void ) {

  return * ( ( volatile unsigned long * ) ( FEAC ) );

}

/*
  ----------------------------------------------------------------------
  set_feac
*/

void set_feac( void ) {

  unsigned long feac_;
  char * feac_string_ = ( char * ) 0;

  if( ( char * ) 0 == ( feac_string_ = getenv( "feac" ) ) ) {

    feac_ = 0;

  } else {

    feac_ = simple_strtoul( feac_string_, NULL, 16 );

  }

  * ( ( volatile unsigned long * ) ( FEAC ) ) = feac_;

}

/*
  ----------------------------------------------------------------------
  get_feac_flip_bits
*/

unsigned long get_feac_flip_bits( void ) {

  return feac_flip_bits;

}

/*
  ----------------------------------------------------------------------
  set_feac_flip_bits
*/

void set_feac_flip_bits( void ) {

  char * flip_bits_string_ = ( char * ) 0;

  if( ( char * ) 0 == ( flip_bits_string_ = getenv( "feac_flip_bits" ) ) ) {

    feac_flip_bits = 0;

  } else {

    feac_flip_bits = simple_strtoul( flip_bits_string_, NULL, 16 );

  }

}

/*
  get_boot_address
*/

unsigned long get_boot_address( void ) {

  if( 0 != ready_ ) {

    return EAC_address_( 0 );

  } else {

    return 0;

  }

}

/*
  nor_set_direct
*/

void nor_set_direct( void ) {

#ifdef LSI_ARCH_APP3K

  flash_controller_configuration_t configuration_;

  configuration_.raw = 0;
  configuration_.bits.clock_wait = 0x14;
  configuration_.bits.write_protect = 1;
  configuration_.bits.reset =1;
  configuration_.bits.web_late = 0;
  configuration_.bits.nand_flash_select = 1;
  configuration_.bits.nor_disable_direct = 0;
  configuration_.bits.nor_flash_respond = 1;
  configuration_.bits.nor_flash_interrupt = 0;
  //DEBUG_PRINT( "configuration_.raw = 0x%x\n", configuration_.raw );
  * ( ( volatile unsigned long * ) 0x68000010 ) = configuration_.raw;

#endif

}  
