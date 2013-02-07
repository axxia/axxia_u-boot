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
#include <asm/io.h>
#include <config.h>

#define mb( ) __asm__ __volatile__ ( "" : : : "memory" )

/*
 * Externally visible Prototypes
 */
void set_peripheral_regs(void);
void ether__init(void);

/*
 * Local Prototypes
 */

static unsigned long dram_size( volatile unsigned long * base );

static inline void delay(unsigned long loops)
{
  __asm__ volatile("1:\n"
                   "subs %0, %1, #1\n"
                   "bne 1b":"=r" (loops):"0" (loops));
}

/*
 * Miscellaneous platform dependent initializations
 */

int board_init(void)
{
  DECLARE_GLOBAL_DATA_PTR;
  register u32 i;

  /* Architecture number of LSI APP Boards */
  gd->bd->bi_arch_number = CONFIG_APP_ARCHNO;

  /* Address of boot parameters */
  gd->bd->bi_boot_params = PHYS_RAM_BASE+0x0100;

  /* Core revision number (see ARM AppNote 99)
   *   opcode_2  Purpose
   *     0       ID code register
   *     1       Shadow register - Instr & Data Cache type & size
   *     2       Shadow register - Tightly coupled RAM type & size
   */
  asm("mrc p15, 0, %0, c0, c0, 0":"=r" (i));
  /*gd->bd->bi_revision_number = i;*/
  /* printf("\nbi_revision_number=%lx\n", gd->bd->bi_revision_number); */

  /* Set the GPIO Mux Configuration Register */
  * ( ( volatile unsigned long * ) ( GPIO_MUX ) ) = GPIO_MUX_DEFAULT;

  /* Configure peripherals */
  set_peripheral_regs();

  icache_enable();

  ether__init();

  /*
    Set the MDIO clock.
  */

  {

    char * mdio_clock_speed_string_ = ( char * ) 0;
    unsigned long mdio_clock_speed_;
    unsigned long mdio_divisor_;

    if( ( char * ) 0 == ( mdio_clock_speed_string_ = getenv( "mdio_clock" ) ) ) {

      mdio_clock_speed_ = MDIO_CLOCK_DEFAULT;

    } else {

      mdio_clock_speed_ = simple_strtoul( mdio_clock_speed_string_, NULL, 0 );

    }

#if defined( LSI_ARCH_APP3K )
    mdio_divisor_ = ( pll_get_clock( axi ) / mdio_clock_speed_ );
#elif defined( LSI_ARCH_APP3 )
    mdio_divisor_ = ( pll_get_clock( arm_core ) / mdio_clock_speed_ );
#endif

    __raw_writel( mdio_divisor_, MDIO_CLK );
    mb( );

  }

  return 0;
}

/******************************************************************************
 Routine:ether__init
 Description: Take the Ethernet controller out of reset and appropriately
              initialize it.
******************************************************************************/
void ether__init(void)
{
}

/******************************************************************************
 Routine: dram_init
 Description: Size, initialize, etc. the DRAM available to the board.
******************************************************************************/

int dram_init(void)
{
  DECLARE_GLOBAL_DATA_PTR;

  gd->bd->bi_dram[0].start = PHYS_RAM_BASE;
  gd->bd->bi_dram[0].size = dram_size( u32REG( PHYS_RAM_BASE ) );

  return 0;
}

/*
  ----------------------------------------------------------------------
  dram_size

  N.B. Attempting to access 0x70000000 will cause a data abort!
*/

#define CHUNK_ 0x800000         /* Minimum: 8 Mbytes */

#ifdef LSI_ARCH_APP3K
#define MAX_ 0x40000000         /* Maximum: 1 Gbytes */
#else
#define MAX_ 0x10000000         /* Maximum: 256 Mbytes */
#endif

unsigned long dram_size( volatile unsigned long * base ) {

#if 0

  return 512 * 1024 * 1024;

#else

  unsigned long size_;

  volatile unsigned long * address_0_;
  volatile unsigned long * address_1_;
  unsigned long backup_ [ 2 ];
  unsigned long value_ [ 2 ];

  for( size_ = CHUNK_; ( size_ * 2 ) <= MAX_; size_ += CHUNK_ ) {

    address_0_ = base + ( size_ / sizeof( unsigned long ) );
    -- address_0_;
    backup_ [ 0 ] = * address_0_;
    * address_0_ = 0x1234abcd;
    address_1_ = base + ( ( size_ * 2 ) / sizeof( unsigned long ) );
    -- address_1_;
    backup_ [ 1 ] = * address_1_;
    * address_1_ = ~ 0x1234abcd;
    value_ [ 0 ] = * address_0_;
    value_ [ 1 ] = * address_1_;
    * address_0_ = backup_ [ 0 ];
    * address_1_ = backup_ [ 1 ];

    if( value_ [ 0 ] == value_ [ 1 ] ) {

      break;

    }

  }

  if( MAX_ < ( size_ * 2 ) ) { size_ = MAX_; }

  return size_;

#endif

}

/******************************************************************************
 Routine: set_peripheral_regs
 Description: Setting up the configuration registers
              specific to the hardware
******************************************************************************/
void set_peripheral_regs( void ) {

  /* Set each registers to its reset value; */

  /* System clock */
  *TIMER0_LOAD   = TIMER0_LOAD_VALUE;
  *TIMER0_CONTROL= TIMER0_CONTROL_VALUE;

}

/*
  ----------------------------------------------------------------------
  app_init
*/

int app_init( void ) {

  return 0;

}


/*
  ----------------------------------------------------------------------
  misc_init_r

  Miscellaneous additional platform-dependent init that is performed
  when CONFIG_MISC_INIT_R is defined.
*/

int misc_init_r( void ) {

  uchar * mtdparts_string_ = ( uchar * ) 0;
  uchar * mtdids_string_ = ( uchar * ) 0;
  int save_env_ = 0;

  if( ( uchar * ) 0 == ( mtdids_string_ = getenv( "mtdids" ) ) ||
      0 != strcmp( mtdids_string_, MTDIDS_DEFAULT ) ) {

    setenv( "mtdids", MTDIDS_DEFAULT );
    save_env_ = 1;

  }

  if( ( uchar * ) 0 == ( mtdparts_string_ = getenv( "mtdparts" ) ) ||
      0 != strncmp( mtdparts_string_, MTDPARTS_REQUIRED,
                    strlen( MTDPARTS_REQUIRED ) ) ) {

    setenv( "mtdparts", MTDPARTS_DEFAULT );
    save_env_ = 1;

  }

  if( 1 == save_env_ ) {

    saveenv( );

  }

  return 0;

}

/*
  ----------------------------------------------------------------------
  get_board_rev
*/

u32 get_board_rev( void ) {

  return 0;

}

/*
  ----------------------------------------------------------------------
  app_is_pci_sm
*/

int app_is_pci_sm( void ) {

#ifdef LSI_ARCH_APP3K

  char * pci_mode_string_ = ( char * ) 0;

  if( ( char * ) 0 == ( pci_mode_string_ = getenv( "pci_mode" ) ) ) {

    /* If pci_mode isn't set, assume that the arm is not the pci master */
    return 0;

  }

  if( 0 == strncmp( pci_mode_string_, "auto", strlen( "auto" ) ) ) {

    unsigned short dp_tadr;

    dp_tadr = pll_read( 0x8c );

    if( 0 == ( 0x2 & dp_tadr ) ) {

      return 0;

    }

    return 1;

  } else if( 0 == strncmp( pci_mode_string_, "on", strlen( "on" ) ) ) {

    return 1;

  }

#endif

  return 0;

}
