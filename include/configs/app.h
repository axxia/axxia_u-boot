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

#ifndef __CONFIGS_APP_H
#define __CONFIGS_APP_H

/*
  ======================================================================
  ======================================================================
  ======================================================================
  This file may be included in C or assembler source!  Everything in
  this first section is only intended for use in C source files.
  ======================================================================
  ======================================================================
  ======================================================================
*/

#ifndef __ASSEMBLY__
#ifndef LANG_ASM

/*
  ----------------------------------------------------------------------
  ----------------------------------------------------------------------
  imath interface
  ----------------------------------------------------------------------
*/

typedef struct {

  unsigned long value;
  int shifted;

} inumber_t;

#define ISHIFT( n, s ) \
( ( ( 0 <= s ) ? \
( unsigned long ) ( n << s ) : ( unsigned long ) ( n >> ( -1 * s ) ) ) )

#define IVALUE( in ) ( ISHIFT( ( in )->value, ( -1 * ( in )->shifted ) ) )

void idisplay( inumber_t * );
void imaximize( inumber_t * );
void iminimize( inumber_t * );
void idivide( inumber_t *, inumber_t *, inumber_t * );
void imultiply( inumber_t *, inumber_t *, inumber_t * );

/*
  ----------------------------------------------------------------------
  ----------------------------------------------------------------------
  Watchdog Interface
  ----------------------------------------------------------------------
*/

int watchdog_start( void );
void watchdog_stop( void );
void watchdog_update( void );

/*
  ----------------------------------------------------------------------
  ----------------------------------------------------------------------
  PHY interface
  ----------------------------------------------------------------------
*/

#define BC_PHY_ID_HIGH_ID   0x40
#define BC_PHY_ID_LOW_ID    0x18
#define BC_PHY_ID_LOW_MODEL 0x1e

#define M_PHY_ID_HIGH_ID   0x22
#define M_PHY_ID_LOW_ID    0x05
#define M_PHY_ID_LOW_MODEL 0x20

/* PHY Registers */

/* -- control -- */

#define PHY_CONTROL 0x00

typedef union {

  unsigned short raw;

  struct {

    unsigned short                 : 7;
    unsigned short collision_test  : 1;
    unsigned short full_duplex     : 1; /* duplex */
    unsigned short restart_autoneg : 1;
    unsigned short isolate         : 1;
    unsigned short power_down      : 1;
    unsigned short autoneg_enable  : 1;
    unsigned short force100        : 1; /* speedBit0 */
    unsigned short loop_back       : 1;
    unsigned short soft_reset      : 1;

  } __attribute__ ( ( packed ) ) bits;

} __attribute__ ( ( packed ) ) phy_control_t;

/* -- status -- */

#define PHY_STATUS 0x01

typedef union {

  unsigned short raw;

  struct {

    unsigned short extd_reg_capable  : 1;
    unsigned short jabber_detect     : 1;
    unsigned short link_status       : 1; /* linkStatus */
    unsigned short autoneg_capable   : 1;
    unsigned short remote_fault      : 1; /* remoutFault */
    unsigned short autoneg_comp      : 1; /* autoNegDone */
    unsigned short mf_pream_suppress : 1;
    unsigned short                   : 4;
    unsigned short tenbt_capable     : 1;
    unsigned short bt_fdx_capable    : 1;
    unsigned short tx_capable        : 1;
    unsigned short tx_fdx_capable    : 1;
    unsigned short t4_capable        : 1;

  } __attribute__ ( ( packed ) ) bits;

} __attribute__ ( ( packed ) ) phy_status_t;

/* -- id_high -- */

#define PHY_ID_HIGH 0x02

typedef union {

  unsigned short raw;

  struct {

    unsigned short id : 16;

  } __attribute__ ( ( packed ) ) bits;

} __attribute__ ( ( packed ) ) phy_id_high_t;

/* -- id_low -- */

#define PHY_ID_LOW  0x03

typedef union {

  unsigned short raw;

  struct {

    unsigned short revision : 4;
    unsigned short model    : 6;
    unsigned short id       : 6;

  } __attribute__ ( ( packed ) ) bits;

} __attribute__ ( ( packed ) ) phy_id_low_t;

/* -- autoneg_advertise  -- */

#define PHY_AUTONEG_ADVERTISE 0x04

/* -- link_partner_ability -- */

#define PHY_LINK_PARTNER_ABILITY 0x05


/* -- lxt9785 -- */

#define LXT9785_PHY_QUICK_STATUS 0x11

typedef union {

  unsigned short raw;

  struct {

    unsigned short                  : 3;
    unsigned short error            : 1;
    unsigned short pause            : 1;
    unsigned short polarity         : 1;
    unsigned short fifo_error       : 1;
    unsigned short autoneg_complete : 1;
    unsigned short autoneg          : 1;
    unsigned short duplex_mode      : 1;
    unsigned short link             : 1;
    unsigned short collision_status : 1;
    unsigned short receive_status   : 1;
    unsigned short transmit_status  : 1;
    unsigned short speed            : 1;
    unsigned short                  : 1;

  } __attribute__ ( ( packed ) ) bits;

} __attribute__ ( ( packed ) ) lxt9785_quick_status_t;

/* -- -- */

#define BC_PHY_AUXILIARY_CONTROL_STATUS 0x18

typedef union {

  unsigned short raw;

  struct {

    unsigned short full_duplex        : 1;
    unsigned short speed              : 1;
    unsigned short force_speed        : 1;
    unsigned short autoneg_indication : 1;
    unsigned short edge_rate          : 2;
    unsigned short hsq_lsq            : 2;
    unsigned short                    : 6;
    unsigned short force_link         : 1;
    unsigned short jabber_disable     : 1;

  } __attribute__ ( ( packed ) ) bits;

} __attribute__ ( ( packed ) ) bc_phy_auxiliary_control_status_t;

/* -- -- */

#define M_PHY_AUXILIARY_CONTROL_STATUS_ 0x1f

typedef union {

  unsigned short raw;

  struct {

    unsigned short                    : 1;   /*bit 0*/
    unsigned short                    : 1;   /*bit 1*/
    unsigned short op_mode_indication : 3;   /*bit 2-4*/
    unsigned short                    : 1;   /*bit 5*/
    unsigned short                    : 1;   /*bit 6*/
    unsigned short autoneg_indication : 1;   /*bit 7*/
    unsigned short jabber_enable      : 1;   /*bit 8*/
    unsigned short                    : 1;   /*bit 9*/
    unsigned short                    : 1;   /*bit 10*/
    unsigned short force_link         : 1;   /*bit 11*/
    unsigned short                    : 1;   /*bit 12*/
    unsigned short                    : 1;   /*bit 13*/

  } __attribute__ ( ( packed ) ) bits;

} __attribute__ ( ( packed ) ) m_phy_auxiliary_control_status_t;

/* -- -- */

#define BC_PHY_INTERRUPT_ 0x1a

typedef union {

  unsigned short raw;

  struct {

    unsigned short status             : 1;
    unsigned short link_change        : 1;
    unsigned short speed_change       : 1;
    unsigned short duplex_change      : 1;
    unsigned short                    : 4;
    unsigned short mask               : 1;
    unsigned short link_mask          : 1;
    unsigned short speed_mask         : 1;
    unsigned short duplex_mask        : 1;
    unsigned short                    : 2;
    unsigned short enable             : 1;
    unsigned short duplex_led_enable  : 1;

  } __attribute__ ( ( packed ) ) bits;

} __attribute__ ( ( packed ) ) bc_phy_interrupt_t;

int phy_read( int, int, unsigned short *, int );
int phy_write( int, int, unsigned short );
unsigned short get_env_ad_value( void );

/*
  ----------------------------------------------------------------------
  ----------------------------------------------------------------------
  IBB (In Band Boot)
  ----------------------------------------------------------------------
*/

#ifdef IBB_ENABLED

#define AGNP5_WIDTH_8  0
#define AGNP5_WIDTH_16 1
#define AGNP5_WIDTH_32 2
#define AGNP5_WIDTH_64 3

int ibb_initialize( void );

void ibb_finalize( void );

int ibb_fill( int witdh,
              unsigned char node, unsigned char target, unsigned long offset,
              unsigned long value, unsigned long value1,
              unsigned long count );

int ibb_read( unsigned char node, unsigned char target, unsigned long offset,
              unsigned long * buffer,
              unsigned long count );

int ibb_reset( void );

int ibb_usleep( unsigned long useconds );

int ibb_write( unsigned char node, unsigned char target, unsigned long offset,
               unsigned long * buffer,
               unsigned long count );

#endif /* IBB_ENABLED */

/*
  ----------------------------------------------------------------------
  ----------------------------------------------------------------------
  PLL
  ----------------------------------------------------------------------
*/

unsigned char pll_read( unsigned );
void pll_write( unsigned, unsigned char );
void pll_reset( int );
void pll_equalize( void );
void pll_display( void );
unsigned long pll_get_pll( pll_pll_t );
unsigned long pll_get_next_pll( pll_pll_t );
unsigned long pll_get_env_pll( pll_pll_t );
int pll_set_pll( pll_pll_t, unsigned long );
unsigned long pll_get_clock( pll_clock_t );
unsigned long pll_get_next_clock( pll_clock_t );
unsigned long pll_get_env_clock( pll_clock_t );
int pll_set_clock( pll_clock_t, unsigned long );
int pll_setup_clocks( void );

/*
  ----------------------------------------------------------------------
  ----------------------------------------------------------------------
  Miscellaneous
  ----------------------------------------------------------------------
*/

#define IO_BUF_CTRL         0x3e00001c
#define IO_BUF_CTRL_DEFAULT 0x2400cb88

#define FEAC         0x3e000060
#define FEAC_DEFAULT 0

#define MDIO_CLOCK_DEFAULT 1250000

extern unsigned long _started_in_ram; /* Set in the startup code... */

unsigned long get_boot_address( void );
unsigned long get_io_buf_ctrl( void );
void set_io_buf_ctrl( void );
unsigned long get_gpio_mux( void );
void set_gpio_mux( void );
unsigned long get_feac( void );
void set_feac( void );
unsigned long get_feac_flip_bits( void );
void set_feac_flip_bits( void );
int app3_init( void );
unsigned char app3xx_flash_readb( unsigned long );
void app3xx_flash_update_ram( void );

extern const char board_type_info [ ];
extern const char board_env_size_info [ ];
extern const char board_memory_type_info [ ];
extern const char board_memory_density_info [ ];
extern const char board_name_info [ ];

#endif /* LANG_ASM */
#endif /* __ASSEMBLY__ */

/*
  ----------------------------------------------------------------------
  ----------------------------------------------------------------------
  High Level Configuration Options
  ----------------------------------------------------------------------
*/

#define CONFIG_APP          1
#define CONFIG_APP_ARCHNO   457
#define CONFIG_APP_PLATFORM 1

#define CONFIG_APP3XX       1   /* incorporated into an instance of
                                 * the APP3XX architecture. */
#define CONFIG_APP3XX_ARCHNO    457

#ifdef  CONFIG_APP3XX_SIMULATOR
#define CONFIG_IDENT_STRING_XTRA    "Simulator "
#define CONFIG_APP3XX_ARMULATOR     1
#else
#define CONFIG_IDENT_STRING_XTRA
#endif

/*
  ======================================================================
  ASIC or FPGA...
*/

#define APP3XX_REVISION_REGISTER \
( * ( ( volatile unsigned long * ) ( CONFIG_NORMAL_ASI_BASE + 0xc ) ) )
#define IS_ASIC ( 0 == ( APP3XX_REVISION_REGISTER & 0x80000000 ) )
#define IS_FPGA ( 0 != ( APP3XX_REVISION_REGISTER & 0x80000000 ) )
#define APP3XX_REVISION ( APP3XX_REVISION_REGISTER & 0x1f )
#define APP3XX_RELEASE  ( ( APP3XX_REVISION_REGISTER & 0xe0 ) >> 5 )

#undef  CONFIG_USE_IRQ             /* We don't need IRQ/FIQ stuff */
#define CONFIG_MISC_INIT_R         /* We have a misc_init_r() function. */
#define CONFIG_CMDLINE_TAG       1 /* Enable passing of ATAGs to kernel*/
#define CONFIG_SETUP_MEMORY_TAGS 1 /* Send memory definition to kernel */
#define CONFIG_REVISION_TAG      1 /* Send core/board rev to kernel */
#define CONFIG_INITRD_TAG        1 /* Send initrd definition to kernel */

/*
 * Size of malloc() pool
 */

#define IBB_MAX_SIZE ( 1024 * 1024 )
#define CFG_MALLOC_LEN ( 2048 * 1024 )
#define CFG_GBL_DATA_SIZE 256

/* Memory controller, etc.                                        */

/**************************************************************************
 * Hardware drivers
 **************************************************************************/

#define u8REG(x)    ((volatile unsigned char *)(x))
#define u16REG(x)   ((volatile unsigned short *)(x))
#define u32REG(x)   ((volatile unsigned long *)(x))

/*
 * Remap & Pause
 */

#define CFG_REMAP_PAUSE          (CONFIG_NORMAL_REMAP_BASE+0x0000)
                    /* write, 32, pause core */
#define CFG_REMAP_REMAP          (CONFIG_NORMAL_REMAP_BASE+0x0004)
                    /* read/write, 1, drive REMAP */
#define CFG_REMAP_RESETSTATUS    (CONFIG_NORMAL_REMAP_BASE+0x0008)
                    /* read/write, 8, check/set the reset status of device */
#define CFG_REMAP_RESETSTATUSCLR (CONFIG_NORMAL_REMAP_BASE+0x00C)
                    /* write, 8, clear bits in reset status */
#define REMAP_ENABLE             u32REG(CFG_REMAP_REMAP)

#define REMAP_RESET( ) { * REMAP_ENABLE = 0; }
#define REMAP_NORMAL( ) { * REMAP_ENABLE = 1; }

/*
 * 10M/100M Ethernet Interface
 */

#define CONFIG_DRIVER_APP3XXNIC
#define APP3XXNIC_REGISTER_BASE     0x40000000
#define APP3XXNIC_DMA_REGISTER_BASE 0x48000000

/*
 * Select serial console configuration
 */

#define CFG_APP3_SERIAL
#define CONFIG_ENV_OVERWRITE /* Allow to overwrite serial and ethaddr */
#define CONFIG_CONS_INDEX    1
#define CONFIG_BAUDRATE      38400 /* to match kernal amba def or 19200 */
#define CFG_BAUDRATE_TABLE   { 9600, 19200, 38400, 57600, 115200 }
#define CFG_NS16550_REG_SIZE -4
/*
 * GPIO configuration.  See ARM PrimeCell General Purpose Input/Output (PL061)
 *                      Technical Reference Manual (ARM DDI 0190B) for details.
 */

#define CONFIG_GPIO_PL061   1   /* Enable GPIO driver          */

#define GPIODATA_first      u8REG(CONFIG_NORMAL_GPIO_0_BASE+0x0000)
#define GPIODATA            u8REG(CONFIG_NORMAL_GPIO_0_BASE+0x03FC)
#define GPIODIR             u8REG(CONFIG_NORMAL_GPIO_0_BASE+0x0400)
#define GPIOIS              u8REG(CONFIG_NORMAL_GPIO_0_BASE+0x0404)
#define GPIOIBE             u8REG(CONFIG_NORMAL_GPIO_0_BASE+0x0408)
#define GPIOIEV             u8REG(CONFIG_NORMAL_GPIO_0_BASE+0x040C)
#define GPIOIE              u8REG(CONFIG_NORMAL_GPIO_0_BASE+0x0410)
#define GPIOIRIS            u8REG(CONFIG_NORMAL_GPIO_0_BASE+0x0414)
#define GPIOIMIS            u8REG(CONFIG_NORMAL_GPIO_0_BASE+0x0418)
#define GPIOIC              u8REG(CONFIG_NORMAL_GPIO_0_BASE+0x041C)
#define GPIOAFSEL           u8REG(CONFIG_NORMAL_GPIO_0_BASE+0x0420)
#define GPIOPeriphID0       u8REG(CONFIG_NORMAL_GPIO_0_BASE+0x0FE0)
#define GPIOPeriphID1       u8REG(CONFIG_NORMAL_GPIO_0_BASE+0x0FE4)
#define GPIOPeriphID2       u8REG(CONFIG_NORMAL_GPIO_0_BASE+0x0FE8)
#define GPIOPeriphID3       u8REG(CONFIG_NORMAL_GPIO_0_BASE+0x0FEC)
#define GPIOCellID0         u8REG(CONFIG_NORMAL_GPIO_0_BASE+0x0FF0)
#define GPIOCellID1         u8REG(CONFIG_NORMAL_GPIO_0_BASE+0x0FF4)
#define GPIOCellID2         u8REG(CONFIG_NORMAL_GPIO_0_BASE+0x0FF8)
#define GPIOCellID3         u8REG(CONFIG_NORMAL_GPIO_0_BASE+0x0FFC)

#define GPIO_NUM_PINS       8
#define GPIO_PIN0           0   /* Indexes to individual pins/leds */
#define GPIO_PIN1           1
#define GPIO_PIN2           2
#define GPIO_PIN3           3
#define GPIO_PIN4           4
#define GPIO_PIN5           5
#define GPIO_PIN6           6
#define GPIO_PIN7           7

#define GPIO_HIGH           1
#define GPIO_LOW            0

#define GPIO_DEBUG_WRITE(v) gpio_write(v)

/*
 * I2C Configuration
 */

#undef  CONFIG_HARD_I2C
#undef  CONFIG_SOFT_I2C
#define CFG_I2C_SPEED       400000  /* I2C speed and slave address ? */
#define CFG_I2C_SLAVE       0x7f

/*
 * SPI Configuration
 */

#define CONFIG_SPI                      /* enable SPI driver            */
#define CONFIG_SPI_X                    /* 16 bit EEPROM addressing     */


/*
 * Timers - See the ARM AMBA Design Kit, Technical Reference Manual
 */

#define APP3XX_TIMER0_BASE      (CONFIG_NORMAL_CT_BASE + 0x0000) /* Linux Tick */
#define APP3XX_TIMER1_BASE      (CONFIG_NORMAL_CT_BASE + 0x0020) /* UART */
#define APP3XX_TIMER2_BASE      (CONFIG_NORMAL_CT_BASE + 0x0040) /* I2C */
#define APP3XX_TIMER3_BASE      (CONFIG_NORMAL_CT_BASE + 0x0060) /* SPI */
#define APP3XX_TIMER4_BASE      (CONFIG_NORMAL_CT_BASE + 0x0080) /* Watchdog */
#define APP3XX_TIMER5_BASE      (CONFIG_NORMAL_CT_BASE + 0x00a0) /* Linux Statistics */
#define APP3XX_TIMER6_BASE      (CONFIG_NORMAL_CT_BASE + 0x00c0) /* Linux High Res */
#define APP3XX_TIMER7_BASE      (CONFIG_NORMAL_CT_BASE + 0x00e0) /* Unused */

#define TIMER_LOAD_OFFSET       0x0000
#define TIMER_VALUE_OFFSET      0x0004
#define TIMER_CONTROL_OFFSET    0x0008
#define TIMER_INTCLR_OFFSET     0x000C
#define TIMER_RIS_OFFSET        0x0010
#define TIMER_MIS_OFFSET        0x0014
#define TIMER_BGLOAD_OFFSET     0x0018

#define TIMER_CONTROL_ENABLE           0x80
#define TIMER_CONTROL_MODE             0x40
#define TIMER_CONTROL_INTERRUPT_ENABLE 0x20
#define TIMER_CONTROL_OUTPUT_MODE      0x10
#define TIMER_CONTROL_PRESCALER        0x0c
#define TIMER_CONTROL_SIZE             0x02
#define TIMER_CONTROL_ONE_SHOT         0x01

    /* The APP350 has 8 timers, that can be driven by the RefClk.
     * This time is further subdivided by a local divisor.
     * We need to use TIMER2 for UART etc. as TIMER1 is dedicated
     * to the core tick uses.
     */

#define TIMER0_LOAD     u32REG(APP3XX_TIMER0_BASE+TIMER_LOAD_OFFSET)
#define TIMER0_VALUE    u32REG(APP3XX_TIMER0_BASE+TIMER_VALUE_OFFSET)
#define TIMER0_CONTROL  u32REG(APP3XX_TIMER0_BASE+TIMER_CONTROL_OFFSET)
#define TIMER0_INTCLR   u32REG(APP3XX_TIMER0_BASE+TIMER_INTCLR_OFFSET)
#define TIMER0_RIS      u32REG(APP3XX_TIMER0_BASE+TIMER_RIS_OFFSET)
#define TIMER0_MIS      u32REG(APP3XX_TIMER0_BASE+TIMER_MIS_OFFSET)
#define TIMER0_BGLOAD   u32REG(APP3XX_TIMER0_BASE+TIMER_BGLOAD_OFFSET)

#define TIMER1_LOAD     u32REG(APP3XX_TIMER1_BASE+TIMER_LOAD_OFFSET)
#define TIMER1_VALUE    u32REG(APP3XX_TIMER1_BASE+TIMER_VALUE_OFFSET)
#define TIMER1_CONTROL  u32REG(APP3XX_TIMER1_BASE+TIMER_CONTROL_OFFSET)
#define TIMER1_INTCLR   u32REG(APP3XX_TIMER1_BASE+TIMER_INTCLR_OFFSET)
#define TIMER1_RIS      u32REG(APP3XX_TIMER1_BASE+TIMER_RIS_OFFSET)
#define TIMER1_MIS      u32REG(APP3XX_TIMER1_BASE+TIMER_MIS_OFFSET)
#define TIMER1_BGLOAD   u32REG(APP3XX_TIMER1_BASE+TIMER_BGLOAD_OFFSET)

#define TIMER7_LOAD     u32REG(APP3XX_TIMER7_BASE+TIMER_LOAD_OFFSET)
#define TIMER7_VALUE    u32REG(APP3XX_TIMER7_BASE+TIMER_VALUE_OFFSET)
#define TIMER7_CONTROL  u32REG(APP3XX_TIMER7_BASE+TIMER_CONTROL_OFFSET)
#define TIMER7_INTCLR   u32REG(APP3XX_TIMER7_BASE+TIMER_INTCLR_OFFSET)
#define TIMER7_RIS      u32REG(APP3XX_TIMER7_BASE+TIMER_RIS_OFFSET)
#define TIMER7_MIS      u32REG(APP3XX_TIMER7_BASE+TIMER_MIS_OFFSET)
#define TIMER7_BGLOAD   u32REG(APP3XX_TIMER7_BASE+TIMER_BGLOAD_OFFSET)

#undef  CFG_CLKS_IN_HZ      /* everything, incl board info, in Hz */

/*
  For a 33MHz input, 33000000 / 256  = 128906 counts per second
*/

#define TIMER0_LOAD_VALUE    0xffffffff
#define TIMER0_CONTROL_VALUE 0xca;
                /* 0x80 = Timer Enable (1, enabled)
                 * 0x40 = Timer Mode   (1, periodic mode)
                 * 0x20 = Interrupt enable (0, disabled)
                 * 0x10 = CUSTOM: clock toggle mode
                 *        1 = divide effective rate in half
                 * 0x0C = TimerPrescale bits (10, div by 256)
                 * 0x02 = Timer Size (1, 32 bits)
                 * 0x01 = One Shot Count (0, wrapping mode)
                 */

/**************************************************************************
 * Available commands (autoboot & other)
 **************************************************************************/

#define CONFIG_CMD_ENV
#define CONFIG_CMD_FLASH

#ifdef LSI_ARCH_APP3
#define CONFIG_COMMANDS (CONFIG_CMD_DFL|CFG_CMD_CACHE|CFG_CMD_PING|CFG_CMD_DHCP|CFG_CMD_PLL|CFG_CMD_IBB|CFG_CMD_PHY|CFG_CMD_APP3_FLASH|CFG_CMD_ELF|CFG_CMD_ENV|CFG_CMD_FLASH)
#endif

#define CONFIG_BOOTP_MASK CONFIG_BOOTP_DEFAULT

/**********************************************************************
 * Use the extra memory test...
 **********************************************************************/

#define CFG_MEMTEST_START 0x60001000
#define CFG_MEMTEST_END   0x61001000
#define CFG_ALT_MEMTEST
#define CFG_MEMTEST_SCRATCH 0x60001000

/*
  ======================================================================
  Boot options for the various targets...
  ======================================================================
*/

/*
  Common boot options.

  Note: The kernel expects to have the 'initrd' image within the
        range of the RAM specified to it at 'bootm' time.  This
        means that we must copy the 'initrd' image from whatever
        location it resides at to RAM first.
*/

#define CONFIG_BOOT_RETRY_TIME  -60 /* Feature is defined but not enabled */

#define CONFIG_BOOTDELAY   5
#define CONFIG_BOOTCOMMAND "bootm"
#define CONFIG_BOOTARGS    "console=ttyAMA0,38400n8 ip=dhcp reboot=s root=/dev/nfs"

#if defined(CONFIG_COMMANDS) && defined(CFG_CMD_KGDB)
#define CONFIG_KGDB_BAUDRATE    115200  /* speed to run kgdb serial port */
#define CONFIG_KGDB_SER_INDEX   1       /* which serial port to use */
#endif


/**************************************************************************
 * Miscellaneous configurable options
 **************************************************************************/

#define CFG_LONGHELP            /* undef to save memory     */
#define CFG_PROMPT  "APP3 # "   /* Monitor Command Prompt   */
#define CFG_CBSIZE  1024        /* Console I/O Buffer Size  */
                                /* Print Buffer Size */
#define CFG_PBSIZE  (CFG_CBSIZE+sizeof(CFG_PROMPT)+16)
#define CFG_MAXARGS 256         /* max number of command args   */
#define CFG_BARGSIZE CFG_CBSIZE /* Boot Argument Buffer Size    */

/**************************************************************************
 * APP350 Interrupt Registers
 **************************************************************************/

#define CONFIG_INTERRUPT_UNDEFINED  0   /* FIQ */
#define CONFIG_INTERRUPT_UART       1   /* IRQ Vectored */
#define CONFIG_INTERRUPT_I2C        2   /* IRQ Vectored */
#define CONFIG_INTERRUPT_SPI        3   /* IRQ Vectored */
#define CONFIG_INTERRUPT_HOST_BUS   4   /* IRQ Vectored */
#define CONFIG_INTERRUPT_ASI        5   /* IRQ Vectored */
#define CONFIG_INTERRUPT_CT         8   /* IRQ Vectored */
#define CONFIG_INTERRUPT_MAC_RX     9   /* IRQ Vectored */
#define CONFIG_INTERRUPT_MAC_TX    10   /* IRQ Vectored */
#define CONFIG_INTERRUPT_MAC_DMA   11   /* IRQ Vectored */
#define CONFIG_INTERRUPT_EXT       12   /* IRQ Vectored */

/**************************************************************************
 * Stack sizes
 *
 * The stack sizes are set up in start.S using the settings below.
 **************************************************************************/

#define CONFIG_STACKSIZE        (512*1024)  /* regular stack */
#ifdef CONFIG_USE_IRQ
#define CONFIG_STACKSIZE_IRQ    (4*1024)    /* IRQ stack */
#define CONFIG_STACKSIZE_FIQ    (4*1024)    /* FIQ stack */
#endif

/**************************************************************************
 * FLASH
 **************************************************************************/

#define CFG_MAX_FLASH_BANKS  2 /* max number of memory banks */
#define CFG_MAX_FLASH_SECT   1024 /* number of sectors */
#define PHYS_FLASH_1         CFG_FLASH_BASE
#define PHYS_FLASH_SIZE      0x0800000 /* 8 MB */
#define CFG_OR_TIMING_FLASH

/* timeout values are in ticks */

#define CFG_FLASH_ERASE_TOUT (20*CFG_HZ) /* Timeout for Flash Erase */
#define CFG_FLASH_WRITE_TOUT (20*CFG_HZ) /* Timeout for Flash Write */

/*

  ---------- FLASH Layout ----------

  For one binary of the boot loader to work on many boards, the amount
  of flash set aside for the boot loader (CFG_MONITOR_LEN) and each
  copy of the environment (CFG_ENV_SECT_SIZE) must be at least as
  large as one flash sector, and if larger, evenly divisible by the
  size of one flash sector.  At present, the largest sector size on
  any supported board is 256 Kbytes, thus the following.

  The size of the binary, CFG_MONITOR_LEN, is defined in app3.h and
  app3k.h.

*/

#define CFG_ENV_IS_IN_FLASH       1
#define CFG_REDUNDAND_ENVIRONMENT 1
#define CFG_ENV_SECT_SIZE         ( BOARD_ENV_SIZE )
#define CFG_ENV_OFFSET            ( CFG_MONITOR_LEN )
#define CFG_ENV_ADDR              ( CFG_FLASH_BASE + CFG_ENV_OFFSET )
#define CFG_ENV_SIZE              CFG_ENV_SECT_SIZE
#define CFG_ENV_OFFSET_REDUND     ( CFG_ENV_OFFSET + CFG_ENV_SIZE )
#define CFG_ENV_ADDR_REDUND       ( CFG_FLASH_BASE + CFG_ENV_OFFSET_REDUND )
#define CFG_ENV_SIZE_REDUND       CFG_ENV_SECT_SIZE

/*#define __HAVE_ARCH_MEMSET 1*/

#endif  /* __CONFIGS_APP_H */
