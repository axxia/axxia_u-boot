/*
 * (C) Copyright 2008
 * LSI <www.lsi.com>
 * John Jacques <john.jacques@lsi.com>
 * Configuration settings for the LSI APP development boards.
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
#include <configs/app3.h>

/*
  Debugging...
*/

#undef DEBUG
/*#define DEBUG*/
#if defined( DEBUG )
#define DEBUG_PRINT( format, args... ) do { \
printf( "pll:%s:%d - DEBUG - ", __FUNCTION__, __LINE__ ); \
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
printf( "pll:%s:%d - WARN - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else
#define WARN_PRINT( )
#endif

/*
  Errors...
*/

#define ERROR_PRINT( format, args... ) do { \
printf( "pll:%s:%d - ERROR - ",  __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );

/*
  ======================================================================
  Important Registers
  ======================================================================
*/

#define PLL_CMD            ( CONFIG_NORMAL_ASI_BASE + 0x100 )
#define PLL_CMD_STRT_DN    0x80000000
#define PLL_CMD_RD_WRT_FLG 0x00000004

#define PLL_ADDR     ( CONFIG_NORMAL_ASI_BASE + 0x104 )
#if defined( LSI_ARCH_APP3K )
#define PLL_ADDR_MSK 0xff
#elif defined( LSI_ARCH_APP3 )
#define PLL_ADDR_MSK 0x7f
#else
#error "Unknown Architecture"
#endif

#define PLL_DATA     ( CONFIG_NORMAL_ASI_BASE + 0x108 )
#define PLL_DATA_MSK 0xff

#define PLL_CONFIGURE        0x00
#define PLL_UPDATE_FLASH     0x01
#define PLL_DO_NOTHING       0x02
#define PLL_CHANGE_CLOCKS    0x03

/*
  ======================================================================
  Data Structures
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  reconfig control register
*/

union pll_reconfig_control_ {

  unsigned char raw;

  struct {

    unsigned char scratch_bits   : 4;
    unsigned char reconfig_core  : 1;
    unsigned char reconfig_ram   : 1;
    unsigned char reset_chip     : 1;
    unsigned char start_reconfig : 1;

  } bits;

};

typedef union pll_reconfig_control_ pll_reconfig_control_t;

/*
  ----------------------------------------------------------------------
  pll control register 0
*/

union pll_control0_ {

  unsigned char raw;

  struct {

    unsigned char core_clock_R  : 4;
    unsigned char core_OEB      : 1;
    unsigned char core_clock_OD : 1;
    unsigned char core_bypass   : 1;
    unsigned char core_PD       : 1;

  } bits;

};

typedef union pll_control0_ pll_control0_t;

union pll_control1_ {

  unsigned char raw;

  struct {

    unsigned char core_clock_F : 6;
    unsigned char              : 2;

  } bits;

};

typedef union pll_control1_ pll_control1_t;

union pll_misc_config_ {

  unsigned char raw;

  struct {

    unsigned char disable_ipsec        : 1;
    unsigned char disable_ipsec_select : 1;
    unsigned char                      : 4;
    unsigned char pll0_ref_clk_select  : 1;
    unsigned char pll1_ref_clk_select  : 1;

  } bits;

};

typedef union pll_misc_config_ pll_misc_config_t;

union pll_select_ {

  unsigned char raw;

  struct {

    unsigned char mux1_control : 3;
    unsigned char pll_select   : 1;
    unsigned char mux2_control : 2;
    unsigned char              : 2;

  } bits;

};

typedef union pll_select_ pll_select_t;

union pll_bypass_ {

  unsigned char raw;

  struct {

    unsigned char mult_taps        : 5;
    unsigned char                  : 1;
    unsigned char test_clk_is_ddr2 : 1;
    unsigned char test_clk_sel     : 1;

  } bits;

};

typedef union pll_bypass_ pll_bypass_t;

#if defined( LSI_ARCH_APP3K )

#define NUMBER_OF_REGISTERS 14

union pll_registers_ {

  unsigned char raw [ NUMBER_OF_REGISTERS ];

  struct {

    unsigned char pll0_control0;
    unsigned char pll0_control1;
    unsigned char core_select;
    unsigned char axi_select;
    unsigned char arm_ddr_select;
    unsigned char mac_select;
    unsigned char ipsec_select;
    unsigned char bypass_delay;
    unsigned char pll1_control0;
    unsigned char pll1_control1;
    unsigned char ddr_select;
    unsigned char output_select;
    unsigned char rmii_select;
    unsigned char sds_select;

  } named;

};

typedef union pll_registers_ pll_registers_t;

#define NUMBER_OF_CLOCKS 11

union pll_clocks_ {

  unsigned long raw [ NUMBER_OF_CLOCKS ];

  struct {

    unsigned long pll_0;
    unsigned long pll_1;
    unsigned long core;
    unsigned long ddr;
    unsigned long axi;
    unsigned long arm_ddr;
    unsigned long mac;
    unsigned long ipsec;
    unsigned long output;
    unsigned long rmii;
    unsigned long sds;

  } named;

};

typedef union pll_clocks_ pll_clocks_t;

#define RECONFIG_CONTROL_OFFSET 0x3c
#define MISC_CONFIG_OFFSET      0x90

#define PLL0_CONTROL0_INDEX    0
#define PLL0_CONTROL1_INDEX    1
#define CORE_SELECT_INDEX      2
#define AXI_SELECT_INDEX       3
#define ARM_DDR_SELECT_INDEX   4
#define MAC_SELECT_INDEX       5
#define IPSEC_SELECT_INDEX     6
#define BYPASS_INDEX           7
#define PLL1_CONTROL0_INDEX    8
#define PLL1_CONTROL1_INDEX    9
#define DDR2_SELECT_INDEX     10
#define OUTPUT_SELECT_INDEX   11
#define RMII_SELECT_INDEX     12
#define SDS_SELECT_INDEX      13

#define PLL0_CONTROL0_OFFSET  0x00
#define PLL0_CONTROL1_OFFSET  0x04
#define CORE_SELECT_OFFSET    0x08
#define AXI_SELECT_OFFSET     0x0c
#define ARM_DDR_SELECT_OFFSET 0x10
#define MAC_SELECT_OFFSET     0x14
#define IPSEC_SELECT_OFFSET   0x18
#define BYPASS_OFFSET         0x1c
#define PLL1_CONTROL0_OFFSET  0x20
#define PLL1_CONTROL1_OFFSET  0x24
#define DDR2_SELECT_OFFSET    0x28
#define OUTPUT_SELECT_OFFSET  0x2c
#define RMII_SELECT_OFFSET    0x30
#define SDS_SELECT_OFFSET     0x80

static int offset_by_index_ [ ] = {

  PLL0_CONTROL0_OFFSET, PLL0_CONTROL1_OFFSET, CORE_SELECT_OFFSET,
  AXI_SELECT_OFFSET, ARM_DDR_SELECT_OFFSET, MAC_SELECT_OFFSET,
  IPSEC_SELECT_OFFSET, BYPASS_OFFSET, PLL1_CONTROL0_OFFSET, PLL1_CONTROL1_OFFSET,
  DDR2_SELECT_OFFSET, OUTPUT_SELECT_OFFSET, RMII_SELECT_OFFSET,
  SDS_SELECT_OFFSET

};

#elif defined( LSI_ARCH_APP3 )

#define NUMBER_OF_REGISTERS 13

union pll_registers_ {

  unsigned char raw [ NUMBER_OF_REGISTERS ];

  struct {

    unsigned char pll0_control0;
    unsigned char pll0_control1;
    unsigned char core_select;
    unsigned char arm_select;
    unsigned char arm_ddr_select;
    unsigned char mac_select;
    unsigned char host_select;
    unsigned char bypass_delay;
    unsigned char pll1_control0;
    unsigned char pll1_control1;
    unsigned char ddr_select;
    unsigned char output_select;
    unsigned char rmii_select;

  } named;

};

typedef union pll_registers_ pll_registers_t;

#define NUMBER_OF_CLOCKS 10

union pll_clocks_ {

  unsigned long raw [ NUMBER_OF_CLOCKS ];

  struct {

    unsigned long pll_0;
    unsigned long pll_1;
    unsigned long core;
    unsigned long ddr;
    unsigned long arm_core;
    unsigned long arm_ddr;
    unsigned long mac;
    unsigned long host;
    unsigned long output;
    unsigned long rmii;

  } named;

};

typedef union pll_clocks_ pll_clocks_t;

#define RECONFIG_CONTROL_OFFSET 0x3c

#define PLL0_CONTROL0_INDEX    0
#define PLL0_CONTROL1_INDEX    1
#define CORE_SELECT_INDEX      2
#define ARM_CORE_SELECT_INDEX  3
#define ARM_DDR_SELECT_INDEX   4
#define MAC_SELECT_INDEX       5
#define HOST_SELECT_INDEX      6
#define BYPASS_INDEX           7
#define PLL1_CONTROL0_INDEX    8
#define PLL1_CONTROL1_INDEX    9
#define DDR2_SELECT_INDEX     10
#define OUTPUT_SELECT_INDEX   11
#define RMII_SELECT_INDEX     12

#define PLL0_CONTROL0_OFFSET        0x00
#define PLL0_CONTROL1_OFFSET        0x04
#define CORE_SELECT_OFFSET          0x08
#define ARM_CORE_SELECT_OFFSET      0x0c
#define ARM_DDR_SELECT_OFFSET       0x10
#define MAC_SELECT_OFFSET           0x14
#define HOST_SELECT_OFFSET          0x18
#define BYPASS_OFFSET               0x1c
#define PLL1_CONTROL0_OFFSET        0x20
#define PLL1_CONTROL1_OFFSET        0x24
#define DDR2_SELECT_OFFSET          0x28
#define OUTPUT_SELECT_OFFSET        0x2c
#define RMII_SELECT_OFFSET          0x30

static int offset_by_index_ [ ] = {

  PLL0_CONTROL0_OFFSET, PLL0_CONTROL1_OFFSET, CORE_SELECT_OFFSET,
  ARM_CORE_SELECT_OFFSET, ARM_DDR_SELECT_OFFSET, MAC_SELECT_OFFSET,
  HOST_SELECT_OFFSET, BYPASS_OFFSET, PLL1_CONTROL0_OFFSET, PLL1_CONTROL1_OFFSET,
  DDR2_SELECT_OFFSET, OUTPUT_SELECT_OFFSET, RMII_SELECT_OFFSET

};

#else
#error "Unknown Architecture"
#endif

/*
  ======================================================================
  Globals
  ======================================================================
*/

static char * env_name_ = "pll_registers";
#define ENV_LENGTH_ 256

/*
  ======================================================================
  Static Function Prototypes
  ======================================================================
*/

static int get_next_offset_( int );
static void get_current_registers_( pll_registers_t * );
static void get_next_registers_( pll_registers_t * );
static void set_next_registers_( const pll_registers_t * );
static void get_env_registers_( pll_registers_t * );
static void set_env_registers_( const pll_registers_t * );
static int compare_registers_( const pll_registers_t *,
                               const pll_registers_t * );

static unsigned long get_vco_( int, pll_registers_t * );
static unsigned long get_speed_( pll_select_t * );
static void set_select_( unsigned long, pll_select_t * );
static int get_select_index_( pll_clock_t );
static unsigned long get_reference_( void );
static unsigned long get_pci_( void );

/*
  ======================================================================
  Static Functions
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  get_next_offset_
*/

static int get_next_offset_( int offset ) {

  int next_offset_ = ( offset + 0x40 );

#if defined( LSI_ARCH_APP3K )

  if( SDS_SELECT_OFFSET == offset ) {

    next_offset_ = ( offset + 4 );

  }

#endif

  return next_offset_;

}

/*
  ----------------------------------------------------------------------
  get_current_registers_
*/

static void get_current_registers_( pll_registers_t * pll_registers ) {

  int index_;

  for( index_ = 0; index_ < NUMBER_OF_REGISTERS; ++ index_ ) {

    pll_registers->raw [ index_ ] =
      pll_read( offset_by_index_ [ index_ ] );

  }

  /* that's all */
  return;

}

/*
  ----------------------------------------------------------------------
  get_next_registers_
*/

static void get_next_registers_( pll_registers_t * pll_registers ) {

  int index_;

  for( index_ = 0; index_ < NUMBER_OF_REGISTERS; ++ index_ ) {

    pll_registers->raw [ index_ ] =
      pll_read( get_next_offset_( offset_by_index_ [ index_ ] ) );

  }

  /* that's all */
  return;

}

/*
  ----------------------------------------------------------------------
  set_next_registers_
*/

static void set_next_registers_( const pll_registers_t * pll_registers ) {

  int index_;

  for( index_ = 0; index_ < NUMBER_OF_REGISTERS; ++ index_ ) {

    DEBUG_PRINT( "Writing 0x%x to 0x%x\n",
                 pll_registers->raw [ index_ ],
                 ( get_next_offset_( offset_by_index_ [ index_ ] ) ) );
    pll_write( ( get_next_offset_( offset_by_index_ [ index_ ] ) ),
               pll_registers->raw [ index_ ] );

  }

  /* that's all */
  return;

}

/*
  ----------------------------------------------------------------------
  get_env_registers_
*/

static void get_env_registers_( pll_registers_t * pll_registers ) {

  char * value_str_;

  value_str_ = getenv( env_name_ );

  if( ( ( char * ) 0 == value_str_ ) ||
      ( ENV_LENGTH_ <= strlen( value_str_ ) ) ) {

    WARN_PRINT( "%s is not set or corrupt, using current registers\n",
                env_name_ );
    get_current_registers_( pll_registers );
    set_env_registers_( pll_registers );

  } else {

    char value_str_buffer_ [ ENV_LENGTH_ ];
    char * value_str_buffer_ptr_;
    char * this_value_;
    int index_ = 0;

    strcpy( value_str_buffer_, value_str_ );
    value_str_buffer_ptr_ = & value_str_buffer_ [ 0 ];

    while( NULL != ( this_value_ =
                     strsep( & value_str_buffer_ptr_, "|" ) ) ) {

      pll_registers->raw [ index_ ] =
        ( unsigned short ) simple_strtoul( this_value_, NULL, 0 );
      DEBUG_PRINT( "index_=%d value=0x%x\n",
                   index_, pll_registers->raw [ index_ ] );
      ++ index_;

    }

  }

  /* that's all */
  return;

}

/*
  ----------------------------------------------------------------------
  set_env_registers_
*/

static void set_env_registers_( const pll_registers_t * pll_registers ) {

  char buffer_ [ ENV_LENGTH_ ];
  int index_;

  buffer_ [ 0 ] = ( char ) 0;

  for( index_ = 0; index_ < NUMBER_OF_REGISTERS; ++ index_ ) {

    sprintf( buffer_, "%s0x%02x|", buffer_, pll_registers->raw [ index_ ] );

  }

  buffer_ [ ( strlen( buffer_ ) - 1 ) ] = ( char ) 0;
  setenv( env_name_, buffer_ );

  /* that's all */
  return;

}

/*
  ----------------------------------------------------------------------
  compare_registers_
*/

static int compare_registers_( const pll_registers_t * a,
                               const pll_registers_t * b ) {

  int index_;

  for( index_ = 0; NUMBER_OF_REGISTERS > index_; ++ index_ ) {

    DEBUG_PRINT( "a->raw[%d]=0x%x b->raw[%d]=0x%x\n",
                 index_, a->raw [ index_ ], index_, b->raw [ index_ ] );
    if( a->raw [ index_ ] < b->raw [ index_ ] ) { return -1; }
    if( a->raw [ index_ ] > b->raw [ index_ ] ) { return 1; }

  }

  return 0;

}

/*
  ----------------------------------------------------------------------
  get_vco_
*/

static unsigned long get_vco_( int pll, pll_registers_t * registers ) {

  unsigned long vco_;
  unsigned long input_;
  pll_control0_t pll_control0_;
  pll_control1_t pll_control1_;
  pll_misc_config_t pll_misc_config_;

#ifdef LSI_ARCH_APP3K
  pll_misc_config_.raw = pll_read( MISC_CONFIG_OFFSET );
#endif  /* LSI_ARCH_APP3K */

  if( 0 == pll ) {

    pll_control0_.raw = registers->named.pll0_control0;
    pll_control1_.raw = registers->named.pll0_control1;

#ifdef LSI_ARCH_APP3K

    if( 0 == pll_misc_config_.bits.pll0_ref_clk_select ) {

      input_ = get_pci_( );

    } else {

      input_ = get_reference_( );

    }

#else

    input_ = get_reference_( );

#endif

  } else {

    pll_control0_.raw = registers->named.pll1_control0;
    pll_control1_.raw = registers->named.pll1_control1;

#ifdef LSI_ARCH_APP3K

    if( 0 == pll_misc_config_.bits.pll1_ref_clk_select ) {

      input_ = get_pci_( );

    } else {

      input_ = get_reference_( );

    }

#else

    input_ = get_reference_( );

#endif

  }

  vco_ = ( get_reference_( ) / ( pll_control0_.bits.core_clock_R + 1 ) )
    * 2 * ( pll_control1_.bits.core_clock_F + 2 );
  if( 0 != pll_control0_.bits.core_clock_OD ) { vco_ /= 2; }

  /* that's all */
  return vco_;

}

/*
  ----------------------------------------------------------------------
  get_speed_
*/

static unsigned long get_speed_( pll_select_t * pll_select ) {

  unsigned long speed_ = 0;
  unsigned long reference_;
  pll_registers_t current_registers_;

  get_current_registers_( & current_registers_ );
  reference_ = get_reference_( );
  speed_ = get_vco_( pll_select->bits.pll_select, & current_registers_ );

  switch( pll_select->bits.mux1_control ) {
  case 0: speed_ = reference_; break;
  case 1: break;
  case 2: speed_ /= 2; break;
  case 3: speed_ /= 3; break;
  case 4: speed_ /= 4; break;
  case 5: speed_ /= 5; break;
  case 6: speed_ = reference_ * 2; break;
  case 7: default: ERROR_PRINT( "mux1_control: Bad Value\n" ); break;
  }

  /* Note: This includes the final divide by 2. */
  switch( pll_select->bits.mux2_control ) {
  case 0: break;
  case 1: speed_ /= 2; break;
  case 2: speed_ /= 4; break;
  case 3: speed_ /= 8; break;
  default: ERROR_PRINT( "mux2_control: Bad Value\n" ); break;
  }

  /* that's all */
  return speed_;

}

/*
  ----------------------------------------------------------------------
  set_select_
*/

static void set_select_( unsigned long new_speed, pll_select_t * select ) {

  unsigned long ref_, vco_0_, vco_1_;
  unsigned long ref_speed_, pll_0_speed_, pll_1_speed_;
  unsigned long pll_index_, ref_index_, pll_0_index_, pll_1_index_;
  unsigned long ref_divisors_ [ ] = { 8, 4, 2, 1 };
  unsigned long pll_divisors_ [ ] = { 40, 32, 24, 20, 16, 12, 10, 8, 6, 4, 2 };
  pll_registers_t current_registers_;

  struct mux_values_ {

    int mux1;
    int mux2;

  };

  struct mux_values_ pll_mux_values_ [ 11 ] = {

    { 5, 3 },                   /* ( pll / 40 ) */
    { 4, 3 },                   /* ( pll / 32 ) */
    { 3, 3 },                   /* ( pll / 24 ) */
    { 5, 2 },                   /* ( pll / 20 ) */
    { 4, 2 },                   /* ( pll / 16 ) */
    { 3, 2 },                   /* ( pll / 12 ) */
    { 5, 1 },                   /* ( pll / 10 ) */
    { 4, 1 },                   /* ( pll /  8 ) */
    { 3, 1 },                   /* ( pll /  6 ) */
    { 2, 1 },                   /* ( pll /  4 ) */
    { 1, 1 }                    /* ( pll /  2 ) */

  };

  /*
    get the sources
  */

  get_current_registers_( & current_registers_ );
  ref_ = get_reference_( );
  vco_0_ = get_vco_( 0, & current_registers_ );
  vco_1_ = get_vco_( 1, & current_registers_ );
  DEBUG_PRINT( "new_speed=%u ref_=%d vco_0_=%d vco_1_=%d\n",
               new_speed, ref_, vco_0_, vco_1_ );

  /*
    if using the reference clock...
  */

  ref_index_ = 0;

  do {

    ref_speed_ = ref_ / ( ref_divisors_ [ ref_index_ ] );
    if( ref_speed_ >= new_speed ) { break; }
    ++ ref_index_;

  } while( ( ref_index_ <
             ( sizeof( ref_divisors_ ) / sizeof( unsigned long ) ) ) );

  if( ref_index_ == ( sizeof( ref_divisors_ ) / sizeof( unsigned long ) ) ) {

    -- ref_index_;

  }

  while( ref_speed_ > new_speed ) {

    if( 0 == ref_index_ ) { break; } /* can't get any slower */
    -- ref_index_;
    ref_speed_ = ref_ / ( ref_divisors_ [ ref_index_ ] );

  }

  DEBUG_PRINT( "ref_index_=%d ref_speed_=%d\n", ref_index_, ref_speed_ );

  /*
    if using pll 0...
  */

  pll_0_index_ = 0;

  do {

    pll_0_speed_ = vco_0_ / ( pll_divisors_ [ pll_0_index_ ] );
    if( pll_0_speed_ >= new_speed ) { break; }
    ++ pll_0_index_;

  } while( ( pll_0_index_ <
             ( sizeof( pll_divisors_ ) / sizeof( unsigned long ) ) ) );

  if( pll_0_index_ == ( sizeof( pll_divisors_ ) / sizeof( unsigned long ) ) ) {

    -- pll_0_index_;

  }

  while( pll_0_speed_ > new_speed ) {

    if( 0 == pll_0_index_ ) { break; } /* can't get any slower */
    -- pll_0_index_;
    pll_0_speed_ = vco_0_ / ( pll_divisors_ [ pll_0_index_ ] );

  }

  DEBUG_PRINT( "pll_0_index_=%d pll_0_speed_=%d\n",
               pll_0_index_, pll_0_speed_ );

  /*
    if using pll 1...
  */

  pll_1_index_ = 0;

  do {

    pll_1_speed_ = vco_1_ / ( pll_divisors_ [ pll_1_index_ ] );
    if( pll_1_speed_ >= new_speed ) { break; }
    ++ pll_1_index_;

  } while( ( pll_1_index_ <
             ( sizeof( pll_divisors_ ) / sizeof( unsigned long ) ) ) );

  if( pll_1_index_ == ( sizeof( pll_divisors_ ) / sizeof( unsigned long ) ) ) {

    -- pll_1_index_;

  }

  while( pll_1_speed_ > new_speed ) {

    if( 0 == pll_1_index_ ) { break; } /* can't get any slower */
    -- pll_1_index_;
    pll_1_speed_ = vco_1_ / ( pll_divisors_ [ pll_1_index_ ] );

  }

  DEBUG_PRINT( "pll_1_index_=%d pll_1_speed_=%d\n",
               pll_1_index_, pll_1_speed_ );

  /*
    pick the closest match (prefer a pll).
  */

  {

    int diff0_, diff1_;

    diff0_ = new_speed - pll_0_speed_;
    if( 0 > diff0_ ) { diff0_ *= -1; }
    diff1_ = new_speed - pll_1_speed_;
    if( 0 > diff1_ ) { diff1_ *= -1; }

    DEBUG_PRINT( "diff0_=%d diff1_=%d\n", diff0_, diff1_ );

    if( diff0_ <= diff1_ ) {

      /* use pll 0 */

      select->bits.pll_select = 0;
      pll_index_ = pll_0_index_;

    } else {

      /* use pll 1 */

      select->bits.pll_select = 1;
      pll_index_ = pll_1_index_;

    }

  }

  /* set the remaining fields in the select register */
  select->bits.mux1_control = ( pll_mux_values_ [ pll_index_ ] ).mux1;
  select->bits.mux2_control = ( pll_mux_values_ [ pll_index_ ] ).mux2;
  DEBUG_PRINT( "select=0x%x/0x%x/%d/0x%x\n",
               select->raw, select->bits.mux1_control, select->bits.pll_select,
               select->bits.mux2_control );

  /* that's all */
  return;

}

/*
  ----------------------------------------------------------------------
  get_select_index_
*/

static int get_select_index_( pll_clock_t clock ) {

  int return_value_ = -1;

  switch( clock ) {
  case core:
    return_value_ = CORE_SELECT_INDEX;
    break;
  case ddr:
    return_value_ = DDR2_SELECT_INDEX;
    break;
  case arm_ddr:
    return_value_ = ARM_DDR_SELECT_INDEX;
    break;
  case mac:
    return_value_ = MAC_SELECT_INDEX;
    break;
  case output:
    return_value_ = OUTPUT_SELECT_INDEX;
    break;
  case rmii:
    return_value_ = RMII_SELECT_INDEX;
    break;
#if defined( LSI_ARCH_APP3K )
  case axi:
    return_value_ = AXI_SELECT_INDEX;
    break;
  case ipsec:
    return_value_ = IPSEC_SELECT_INDEX;
    break;
  case sds:
    return_value_ = SDS_SELECT_INDEX;
    break;
#elif defined( LSI_ARCH_APP3 )
  case arm_core:
    return_value_ = ARM_CORE_SELECT_INDEX;
    break;
  case host:
    return_value_ = HOST_SELECT_INDEX;
    break;
#else
#error "Unknown Architecture"
#endif
  default:
    ERROR_PRINT( "WHAT!?!?!?!\n" );
    break;
  }

  return return_value_;

}

/*
  ----------------------------------------------------------------------
  get_reference_
*/

static unsigned long get_reference_( void ) {

  /* that's all */
  return APP3XX_REF_CLOCK;

}

/*
  ----------------------------------------------------------------------
  get_pci_
*/

#ifdef LSI_ARCH_APP3K

static unsigned long get_pci_( void ) {

  /* that's all */
  return APP3XX_PCI_CLOCK;

}

#endif

/*
  ======================================================================
  ======================================================================
  ======================================================================
  ======================================================================
  ======================================================================
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  pll_read
*/

unsigned char pll_read( unsigned offset ) {

  int retries_ = 100;
  unsigned char value_;

  * ( ( volatile unsigned long * ) PLL_ADDR ) =
    ( unsigned char ) ( offset & PLL_ADDR_MSK );
  * ( ( volatile unsigned long * ) PLL_CMD ) = PLL_CMD_STRT_DN;

  while( PLL_CMD_STRT_DN ==
         ( * ( ( volatile unsigned long * ) PLL_CMD ) & PLL_CMD_STRT_DN ) ) {

    -- retries_;

    if( 0 == retries_ ) {

      ERROR_PRINT( "PLL Read Failed (offset=0x%x/%d)\n", offset, offset );
      break;

    }

  }

  value_ = ( unsigned char ) ( * ( ( volatile unsigned long * ) PLL_DATA ) );

  /* that's all */
  return value_;

}

/*
  ----------------------------------------------------------------------
  pll_write
*/

void pll_write( unsigned offset, unsigned char value ) {

  int retries_ = 100;

  * ( ( volatile unsigned long * ) PLL_ADDR ) =
    ( unsigned char ) ( offset & PLL_ADDR_MSK );
  * ( ( volatile unsigned long * ) PLL_DATA ) =
    ( ( unsigned char ) value & PLL_DATA_MSK );
  * ( ( volatile unsigned long * ) PLL_CMD ) =
    ( PLL_CMD_STRT_DN | PLL_CMD_RD_WRT_FLG );

  while( PLL_CMD_STRT_DN ==
         ( * ( ( volatile unsigned long * ) PLL_CMD ) & PLL_CMD_STRT_DN ) ) {

    -- retries_;

    if( 0 == retries_ ) {

      ERROR_PRINT( "PLL Write Failed (offset=0x%x/%d value=0x%x/%d)\n",
                   offset, offset, value, value );
      break;

    }

  }

  /* that's all */
  return;

}

/*
  ----------------------------------------------------------------------
  pll_get_pll
*/

unsigned long pll_get_pll( pll_pll_t pll ) {

  unsigned long speed_ = 0;
  pll_registers_t current_registers_;

  get_current_registers_( & current_registers_ );

  if( IS_ASIC ) {

    speed_ = get_vco_( ( pll == pll_0 ) ? 0 : 1, & current_registers_ );

  }

  /* that's all */
  return speed_;

}

/*
  ----------------------------------------------------------------------
  pll_get_next_pll
*/

unsigned long pll_get_next_pll( pll_pll_t pll ) {

  unsigned long speed_ = 0;
  pll_registers_t next_registers_;

  get_next_registers_( & next_registers_ );

  if( IS_ASIC ) {

    speed_ = get_vco_( ( pll == pll_0 ) ? 0 : 1, & next_registers_ );

  }

  /* that's all */
  return speed_;

}

/*
  ----------------------------------------------------------------------
  pll_get_env_pll
*/

unsigned long pll_get_env_pll( pll_pll_t pll ) {

  unsigned long speed_ = 0;
  pll_registers_t env_registers_;

  get_env_registers_( & env_registers_ );

  if( IS_ASIC ) {

    speed_ = get_vco_( ( pll == pll_0 ) ? 0 : 1, & env_registers_ );

  }

  /* that's all */
  return speed_;

}

/*
  ----------------------------------------------------------------------
  pll_set_pll
*/

#define PLL_MAX 1000000000
#define PLL_MIN  500000000

int pll_set_pll( pll_pll_t pll, unsigned long new_speed ) {

  pll_control0_t pll_0_;
  pll_control1_t pll_1_;
  unsigned long reference_;

  /*
    check requested speed
  */

  if( ( PLL_MAX < new_speed ) || ( ( PLL_MIN / 2 ) > new_speed ) ) {

    ERROR_PRINT( "Requested speed (%d) out of range!\n", new_speed );
    return -1;

  }

  /*
    initialize variables
  */

  reference_ = get_reference_( );
  pll_0_.raw = 0;
  pll_1_.raw = 0;

  /*
    if the requested frequency is between 250 MHz and 500 MHz, use
    the core_clock_OD (output divide).
  */

  if( ( ( PLL_MIN / 2 ) <= new_speed ) && ( PLL_MIN > new_speed ) ) {

    pll_0_.bits.core_clock_OD = 1;

  }
  
  /*
    first divisor (must end up between 10 and 50 MHz)
  */

  pll_0_.bits.core_clock_R = 1;

  while( 50000000 < ( reference_ / pll_0_.bits.core_clock_R ) ) {

    if( 15 == pll_0_.bits.core_clock_R ) {

      ERROR_PRINT( "Reference clock (%d) too fast!\n", reference_ );
      return -1;

    } else {

      ++ pll_0_.bits.core_clock_R;

    }

  }

  /*
    second divisor and the output divider (must end up
    between 250 MHz and 1 GHz ).
  */

  pll_1_.bits.core_clock_F =
    ( new_speed / ( ( reference_ / ( pll_0_.bits.core_clock_R + 1 ) ) * 2 ) );
  if( 0 != pll_0_.bits.core_clock_OD ) { pll_1_.bits.core_clock_F *= 2; }
  pll_1_.bits.core_clock_F -= 2;
  DEBUG_PRINT( "speed(requested)=%d speed(actual)=%d core_clock_OD=%d " \
               "core_clock_R=%d core_clock_F=%d\n",
               new_speed,
               ( ( reference_ / ( pll_0_.bits.core_clock_R + 1 ) )
                 * 2 * ( pll_1_.bits.core_clock_F + 2 ) ) /
               ( 0 == pll_0_.bits.core_clock_OD ? 1 : 2 ),
               pll_0_.bits.core_clock_OD, pll_0_.bits.core_clock_R,
               pll_1_.bits.core_clock_F );

  /*
    write the "next" register and update the environment
  */

  {

    pll_registers_t env_registers_;

    get_env_registers_( & env_registers_ );

    if( pll_0 == pll ) {

      pll_write( get_next_offset_( offset_by_index_ [ PLL0_CONTROL0_INDEX ] ),
                 pll_0_.raw );
      pll_write( get_next_offset_( offset_by_index_ [ PLL0_CONTROL1_INDEX ] ),
                 pll_1_.raw );

      if( ( env_registers_.raw [ PLL0_CONTROL0_INDEX ] !=
            pll_0_.raw ) ||
          ( env_registers_.raw [ PLL0_CONTROL1_INDEX ] !=
            pll_1_.raw ) ) {

        env_registers_.raw [ PLL0_CONTROL0_INDEX ] = pll_0_.raw;
        env_registers_.raw [ PLL0_CONTROL1_INDEX ] = pll_1_.raw;
        set_env_registers_( & env_registers_ );
        WARN_PRINT( "Environment changed, \"saveenv\" to make it permanent\n" );

      }

    } else {

      pll_write( get_next_offset_( offset_by_index_ [ PLL1_CONTROL0_INDEX ] ),
                 pll_0_.raw );
      pll_write( get_next_offset_( offset_by_index_ [ PLL1_CONTROL1_INDEX ] ),
                 pll_1_.raw );

      if( ( env_registers_.raw [ PLL1_CONTROL0_INDEX ] != pll_0_.raw ) ||
          ( env_registers_.raw [ PLL1_CONTROL1_INDEX ] != pll_1_.raw ) ) {

        env_registers_.raw [ PLL1_CONTROL0_INDEX ] = pll_0_.raw;
        env_registers_.raw [ PLL1_CONTROL1_INDEX ] = pll_1_.raw;
        set_env_registers_( & env_registers_ );
        WARN_PRINT( "Environment changed, \"saveenv\" to make it permanent\n" );

      }

    }

  }

  /* that's all */
  return 0;

}

/*
  ----------------------------------------------------------------------
  pll_get_clock
*/

unsigned long pll_get_clock( pll_clock_t clock ) {

  unsigned long speed_ = 0;

  if( IS_ASIC ) {

    pll_registers_t pll_registers_;
    pll_select_t pll_select_;

#if defined( LSI_ARCH_APP3 )

    if( host == clock ) {

      char * host_clock_string_ = ( char * ) 0;

      host_clock_string_ = getenv( "host_clock" );

      if( ( char * ) 0 != host_clock_string_ ) {

        speed_ = simple_strtoul( host_clock_string_, NULL, 0 );

      } else {

        speed_ = 33333333;   /* Default is 33 MHz */

      }

      return speed_;

    }

#endif

    /* Use the PLL registers to determing the speed. */
    get_current_registers_( & pll_registers_ );
    pll_select_.raw = pll_registers_.raw [ get_select_index_( clock ) ];
    speed_ = get_speed_( & pll_select_ );

  } else {

#ifdef LSI_ARCH_APP3K

    switch( clock ) {
    case core:
      speed_ = 33333333;
      break;
    case ddr:
      speed_ = 33333333;
      break;
    case axi:
      speed_ = 8333333;
      break;
    case arm_ddr:
      speed_ = 33333333;
      break; 
    case mac:
      speed_ = 33333333;
      break; 
    case ipsec:
      speed_ = 0;
      break;
    case output:
      speed_ = 0;
      break;
    case rmii:
      speed_ = 0;
      break;
    case sds:
      speed_ = 0;
      break;
    default:
      ERROR_PRINT( "WHAT!?!?!?!\n" );
      break;
    }

#else  /* LSI_ARCH_APP3K */

    switch( clock ) {
    case core:
      speed_ = 33333333;
      break;
    case ddr:
      speed_ = 33333333;
      break;
    case arm_core:
      speed_ = 33333333;
      break;
    case arm_ddr:
      speed_ = 33333333;
      break; 
    case mac:
      speed_ = 33333333;
      break; 
    case host:
      speed_ = 16000000;
      break;
    case output:
      speed_ = 0;
      break;
    case rmii:
      speed_ = 0;
      break;
    default:
      ERROR_PRINT( "WHAT!?!?!?!\n" );
      break;
    }

#endif

  }

  /* that's all */
  return speed_;

}

/*
  ----------------------------------------------------------------------
  pll_get_next_clock
*/

unsigned long pll_get_next_clock( pll_clock_t clock ) {

  unsigned long speed_ = 0;

  if( IS_ASIC ) {

    pll_registers_t pll_registers_;
    pll_select_t pll_select_;

    /* Use the PLL registers to determing the speed. */
    get_next_registers_( & pll_registers_ );
    pll_select_.raw = pll_registers_.raw [ get_select_index_( clock ) ];
    speed_ = get_speed_( & pll_select_ );

  } else {

    switch( clock ) {
    case core:
      speed_ = 33333333;
      break;
    case ddr:
      speed_ = 33333333;
      break;
    case arm_ddr:
      speed_ = 33333333;
      break;
#if defined( LSI_ARCH_APP3K )
    case axi:
      speed_ = 8333333;
      break;
#elif defined( LSI_ARCH_APP3 )
    case arm_core:
      speed_ = 33333333;
      break;
    case host:
      speed_ = 16000000;
      break;
#else
#error "Unknown Architecture"
#endif
    default:
      ERROR_PRINT( "WHAT!?!?!?!\n" );
      break;
    }

  }

  /* that's all */
  return speed_;

}

/*
  ----------------------------------------------------------------------
  pll_get_env_clock
*/

unsigned long pll_get_env_clock( pll_clock_t clock ) {

  unsigned long speed_ = 0;

  if( IS_ASIC ) {

    pll_registers_t pll_registers_;
    pll_select_t pll_select_;

    /* Use the PLL registers to determing the speed. */
    get_env_registers_( & pll_registers_ );
    pll_select_.raw = pll_registers_.raw [ get_select_index_( clock ) ];
    speed_ = get_speed_( & pll_select_ );

  } else {

    switch( clock ) {
    case core:
      speed_ = 33333333;
      break;
    case ddr:
      speed_ = 33333333;
      break;
    case arm_ddr:
      speed_ = 33333333;
      break;
#if defined( LSI_ARCH_APP3K )
    case axi:
      speed_ = 8333333;
      break;
#elif defined( LSI_ARCH_APP3 )
    case arm_core:
      speed_ = 33333333;
      break;
    case host:
      speed_ = 16000000;
      break;
#else
#error "Unknown Architecture"
#endif
    default:
      ERROR_PRINT( "WHAT!?!?!?!\n" );
      break;
    }

  }

  /* that's all */
  return speed_;

}

/*
  ----------------------------------------------------------------------
  pll_set_clock
*/

int pll_set_clock( pll_clock_t clock, unsigned long new_speed ) {

  pll_registers_t pll_registers_;
  pll_registers_t env_registers_;
  pll_select_t pll_select_;

  /* only possible on the ASIC */
  if( IS_FPGA ) { return -1; }
  DEBUG_PRINT( "new_speed=%d\n", new_speed );

  /* set up the select register and write to 'next' */
  get_current_registers_( & pll_registers_ );
  pll_select_.raw = pll_registers_.raw [ get_select_index_( clock ) ];
  set_select_( new_speed, & pll_select_ );
  pll_write( get_next_offset_( offset_by_index_ [ get_select_index_( clock ) ] ),
             pll_select_.raw );
  get_env_registers_( & env_registers_ );

  if( env_registers_.raw [ get_select_index_( clock ) ] != pll_select_.raw ) {

    env_registers_.raw [ get_select_index_( clock ) ] = pll_select_.raw;
    set_env_registers_( & env_registers_ );
    WARN_PRINT( "Environment changed, \"saveenv\" to make it permanent\n" );

  }

  /* that's all */
  return 0;

}

/*
  ----------------------------------------------------------------------
  pll_reset
*/

void pll_reset( int reconfig ) {

  pll_reconfig_control_t reconfig_control_;

  /*
    N.B. Reset (in the PLL reconfiguration control register)
    doesn't work at present.  Just jump to address 0x00000000
    in FLASH.
  */

  void ( * uboot ) ( void );
#if defined( LSI_ARCH_APP3K )
  uboot = ( void ( * ) ( void ) ) CONFIG_NORMAL_NOR_ALIAS_BASE;
#elif defined( LSI_ARCH_APP3 )
  uboot = ( void ( * ) ( void ) ) get_boot_address( );
#endif

  if( IS_ASIC ) {

    printf( "Resetting [reconfig=%d]\n", reconfig );
    reconfig_control_.raw = pll_read( RECONFIG_CONTROL_OFFSET );
    reconfig_control_.bits.reconfig_core = 0;
    reconfig_control_.bits.reconfig_ram = 0;
    reconfig_control_.bits.reset_chip = 0;
    reconfig_control_.bits.start_reconfig = 0;

    if( 0 != reconfig ) {

      reconfig_control_.bits.scratch_bits = PLL_CHANGE_CLOCKS;

    } else {

      reconfig_control_.bits.scratch_bits = 0;

    }

    pll_write( RECONFIG_CONTROL_OFFSET, reconfig_control_.raw );

  }

#if defined( LSI_ARCH_APP3K )
  nor_set_direct( );
#elif defined( LSI_ARCH_APP3 )
  REMAP_RESET( );
#endif

  udelay( 10000 );
  cleanup_before_linux( );
  uboot( );

}

/*
  ----------------------------------------------------------------------
  pll_equalize
*/

void pll_equalize( void ) {

  pll_registers_t pll_registers_;

  if( IS_FPGA ) {

    printf( "PLL registers are only available on the ASIC\n" );

  } else {

    get_current_registers_( & pll_registers_ );
    set_next_registers_( & pll_registers_ );

  }

  /* that's all */
  return;

}

/*
  ----------------------------------------------------------------------
  pll_display
*/

void pll_display( void ) {

  int index_;
  pll_registers_t pll_current_registers_;
  pll_registers_t pll_next_registers_;
  pll_registers_t pll_env_registers_;

  if( IS_FPGA ) {

    printf( "PLL registers are only available on the ASIC\n" );

  } else {

    get_current_registers_( & pll_current_registers_ );
    get_next_registers_( & pll_next_registers_ );
    get_env_registers_( & pll_env_registers_ );
    printf( "---- PLL Registers ----\n" );
    printf( "  Current       Next          Environment\n" );
    printf( "  Offset:Value  Offset:Value  Value\n" );

    for( index_ = 0; index_ < NUMBER_OF_REGISTERS; ++ index_ ) {

      printf( "  0x%02x:0x%02x     0x%02x:0x%02x     0x%02x\n",
              ( offset_by_index_ [ index_ ] ),
              pll_current_registers_.raw [ index_ ],
              get_next_offset_( offset_by_index_ [ index_ ] ),
              pll_next_registers_.raw [ index_ ],
              pll_env_registers_.raw [ index_ ] );

    }

    printf( "Reconfig Control (0x%02x) is 0x%02x\n",
            RECONFIG_CONTROL_OFFSET, pll_read( RECONFIG_CONTROL_OFFSET ) );
    printf( "---- Clocks (MHz) ----\n" );
    printf( "           Current/Next/Environment\n" );
    printf( "    PLL 0: %d/%d/%d\n",
            get_vco_( 0, & pll_current_registers_ ) / 1000000,
            get_vco_( 0, & pll_next_registers_ ) / 1000000,
            get_vco_( 0, & pll_env_registers_ ) / 1000000 );
    printf( "    PLL 1: %d/%d/%d\n",
            get_vco_( 1, & pll_current_registers_ ) / 1000000,
            get_vco_( 1, & pll_next_registers_ ) / 1000000,
            get_vco_( 1, & pll_env_registers_ ) / 1000000 );
    printf( "Reference: %d\n", get_reference_( ) / 1000000 );
    printf( "     Core: %d/%d/%d\n",
            pll_get_clock( core ) / 1000000,
            pll_get_next_clock( core ) / 1000000,
            pll_get_env_clock( core ) / 1000000 );
    printf( "      DDR: %d/%d/%d\n",
            pll_get_clock( ddr ) / 1000000,
            pll_get_next_clock( ddr ) / 1000000,
            pll_get_env_clock( ddr ) / 1000000 );
    printf( "  ARM DDR: %d/%d/%d\n",
            pll_get_clock( arm_ddr ) / 1000000,
            pll_get_next_clock( arm_ddr ) / 1000000,
            pll_get_env_clock( arm_ddr ) / 1000000 );
#if defined( LSI_ARCH_APP3K )
    printf( " ARM Core: %d/%d/%d\n",
            ( pll_get_clock( axi ) * 2 ) / 1000000,
            ( pll_get_next_clock( axi ) * 2 ) / 1000000,
            ( pll_get_env_clock( axi ) * 2 ) / 1000000 );
    printf( "      AXI: %d/%d/%d\n",
            pll_get_clock( axi ) / 1000000,
            pll_get_next_clock( axi ) / 1000000,
            pll_get_env_clock( axi ) / 1000000 );
    printf( "    IPSEC: %d/%d/%d\n",
            pll_get_clock( ipsec ) / 1000000,
            pll_get_next_clock( ipsec ) / 1000000,
            pll_get_env_clock( ipsec ) / 1000000 );
    printf( "      SDS: %d/%d/%d\n",
            pll_get_clock( sds ) / 1000000,
            pll_get_next_clock( sds ) / 1000000,
            pll_get_env_clock( sds ) / 1000000 );
#elif defined( LSI_ARCH_APP3 )
    printf( " ARM Core: %d/%d/%d\n",
            pll_get_clock( arm_core ) / 1000000,
            pll_get_next_clock( arm_core ) / 1000000,
            pll_get_env_clock( arm_core ) / 1000000 );
    printf( "     Host: %d/%d/%d\n",
            pll_get_clock( host ) / 1000000,
            pll_get_next_clock( host ) / 1000000,
            pll_get_env_clock( host ) / 1000000 );
#else
#error "Unknown Architecture"
#endif
    printf( "      MAC: %d/%d/%d\n",
            pll_get_clock( mac ) / 1000000,
            pll_get_next_clock( mac ) / 1000000,
            pll_get_env_clock( mac ) / 1000000 );
    printf( "   Output: %d/%d/%d\n",
            pll_get_clock( output ) / 1000000,
            pll_get_next_clock( output ) / 1000000,
            pll_get_env_clock( output ) / 1000000 );
    printf( "     RMII: %d/%d/%d\n",
            pll_get_clock( rmii ) / 1000000,
            pll_get_next_clock( rmii ) / 1000000,
            pll_get_env_clock( rmii ) / 1000000 );

  }

  /* that's all */
  return;

}

/*
  ----------------------------------------------------------------------
  pll_setup_clocks
*/

int pll_setup_clocks( void ) {

  pll_registers_t current_registers_;
  pll_registers_t next_registers_;
  pll_registers_t env_registers_;
  pll_reconfig_control_t reconfig_control_;

  DEBUG_PRINT( "beginning\n" );

  /* only possible on the ASICs */

  if( IS_FPGA ) { return 0; }

  /* get the registers */

  get_current_registers_( & current_registers_ );
  get_next_registers_( & next_registers_ );
  get_env_registers_( & env_registers_ );

  /* switch on the scratch register */

  reconfig_control_.raw = pll_read( RECONFIG_CONTROL_OFFSET );
  DEBUG_PRINT( "scratch=0x%x\n", reconfig_control_.bits.scratch_bits );

  switch( reconfig_control_.bits.scratch_bits ) {

  default:

    ERROR_PRINT( "Unknown Command in Scratch Register, 0x%x/%d!\n",
                 reconfig_control_.bits.scratch_bits,
                 reconfig_control_.bits.scratch_bits );

    break;

  case PLL_CONFIGURE:

    DEBUG_PRINT( "Configure from FLASH\n" );

    if( 0 != compare_registers_( & current_registers_, & env_registers_ ) ) {

      set_next_registers_( & env_registers_ );
      pll_reset( 1 );

    }

    break;

  case PLL_UPDATE_FLASH:

    DEBUG_PRINT( "Update FLASH from next\n" );

    if( 0 != compare_registers_( & next_registers_, & env_registers_ ) ) {

      set_env_registers_( & next_registers_ );
      saveenv( );
      reconfig_control_.bits.scratch_bits = PLL_DO_NOTHING;
      pll_write( RECONFIG_CONTROL_OFFSET, reconfig_control_.raw );
      pll_reset( 0 );

    }

    break;

  case PLL_DO_NOTHING:

    DEBUG_PRINT( "Don't do anything\n" );

    break;

  }

  /*
    setup the PLL so that a reboot before the RTE gets
    involved won't change anything.
  */

  pll_equalize( );
  reconfig_control_.bits.reconfig_core = 0;
  reconfig_control_.bits.reconfig_ram = 0;
  pll_write( RECONFIG_CONTROL_OFFSET, reconfig_control_.raw );

  DEBUG_PRINT( "end\n" );

  /* that's all */
  return 0;

}
