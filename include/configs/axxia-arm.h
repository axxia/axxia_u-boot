/* 1
 * (C) Copyright 2010
 * Texas Instruments Incorporated.
 * Sricharan R	  <r.sricharan@ti.com>
 *
 * Derived from OMAP4 done by:
 *	Aneesh V <aneesh@ti.com>
 *
 * Configuration settings for the TI EVM5430 board.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#ifndef __ASSEMBLY__
#include <linux/types.h>
#endif


#if 0
#include <configs/axxia.h>
#endif


/*
  ======================================================================
  ======================================================================
  Version
  ======================================================================
  ======================================================================
*/

#ifndef __ASSEMBLY__
int is_asic( void );
#endif /* __ASSEMBLY__ */

/*
 * High Level Configuration Options
 */
#define CONFIG_ARMV7	/* This is an ARM V7 CPU core */
#define CONFIG_OMAP	/* in a TI OMAP core */
#define CONFIG_AXXIA_ARM	/* in a TI OMAP core */
#define CONFIG_ACP
#define CONFIG_OMAP54XX	/* which is a 54XX */
#define CONFIG_OMAP5430	/* which is in a 5430 */
#define CONFIG_5430EVM	/* working with EVM */
#define CONFIG_OMAP_GPIO

#define CONFIG_SYS_HZ           1000    /* decrementer freq: 1 ms ticks */
#define SYSTIMER_RATE		4096000

#define SYSMEM  0x00000000
#define IO      0x80080000
/* #define LCM     0xf0a00000
#define ROM     0xf0b00000 */

#if 0

#ifndef __ASSEMBLY__
#include <common.h>
#include <asm/io.h>

extern int lsi_logio_enable;

#ifdef LSI_LOGIO
#define LSI_LOGIO_ENABLE() {lsi_logio_enable = 1;}
#define LSI_LOGIO_DISABLE() {lsi_logio_enable = 0;}
#define LSI_LOGIO_ENABLED() (1 == lsi_logio_enable)
static inline unsigned long _READL(const char *, int, unsigned long);
static inline unsigned long
_READL(const char *file, int line, unsigned long address)
{
        unsigned long value;
        value = readl(address);

        if (0 != lsi_logio_enable)

                printf("%s:%d - Read 0x%08lx from 0x%08lx\n",
                       file, line, value, address);

        return value;
}
#define READL(address) _READL(__FILE__, __LINE__, (address))
static inline void _WRITEL(const char *, int, unsigned long, unsigned long);
static inline void
_WRITEL(const char *file, int line, unsigned long value, unsigned long address)
{
        writel(value, address);

        if (0 != lsi_logio_enable)
                printf( "%s:%d - Wrote 0x%08lx to 0x%08lx\n",
                        file, line, value, address);

        return;
}
#define WRITEL(value, address) _WRITEL(__FILE__, __LINE__, (value), (address))
#else  /* LSI_LOGIO */
#define LSI_LOGIO_ENABLE() {}
#define LSI_LOGIO_DISABLE() {}
#define LSI_LOGIO_ENABLED() 0
#define READL(address) readl((address))
#define WRITEL(value, address) writel((value), (address))
#endif /* LSI_LOGIO */
#endif
#endif




/* Get CPU defs */
#include <asm/arch/cpu.h>
#include <asm/arch/omap.h>

#if 0
/* Display CPU and Board Info */
#define CONFIG_DISPLAY_CPUINFO
#define CONFIG_DISPLAY_BOARDINFO
#endif

/* Clock Defines */
#define V_OSCK			19200000	/* Clock output from T2 */
#define V_SCLK	V_OSCK

#define CONFIG_MISC_INIT_R

#define CONFIG_OF_LIBFDT

#define CONFIG_CMDLINE_TAG /* enable passing of ATAGs */
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG

/*
 * Size of malloc() pool
 * Total Size Environment - 128k
 * Malloc - add 256k
 */
#define CONFIG_ENV_SIZE			(128 << 10)
/* Vector Base */
#define CONFIG_SYS_CA9_VECTOR_BASE	SRAM_ROM_VECT_BASE

/*
 * Hardware drivers
 */

#if 0
/*
 * serial port - NS16550 compatible
 */
#define V_NS16550_CLK			48000000

#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	(-4)
#define CONFIG_SYS_NS16550_CLK		V_NS16550_CLK
#define CONFIG_CONS_INDEX		3
#define CONFIG_SYS_NS16550_COM3		UART3_BASE

#endif

#define CONFIG_SYS_PROMPT       "ACP3=> "
#if 0
//#define CONFIG_SYS_CBSIZE       1024
//#define CONFIG_SYS_PBSIZE       (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16)
//#define CONFIG_SYS_MAXARGS      64
//#define CONFIG_SYS_BARGSIZE     CONFIG_SYS_CBSIZE

#endif

#define CFG_PROMPT              "ACP3=> "
#define CFG_CBSIZE              1024
#define CFG_PBSIZE              (CFG_CBSIZE+sizeof(CFG_PROMPT)+16)
#define CFG_MAXARGS             64
#define CFG_BARGSIZE            CFG_CBSIZE


#define UART_CLOCK_SPEED	2*1024*1024	/* 2 Mb/s */
/* #define CONFIG_BAUDRATE			115200 */
#define CONFIG_BAUDRATE			9600
/* #define CONFIG_SYS_BAUDRATE_TABLE	{4800, 9600, 19200, 38400, 57600,\
					115200} */
#ifndef __ASSEMBLY__
int serial_early_init(void);
#endif


#define UART011_DR              0x0000
#define UART011_ECR             0x0004
#define UART011_FR              0x0018
#define UART011_ILPR            0x0020
#define UART011_IBRD            0x0024
#define UART011_FBRD            0x0028
#define UART011_LCR_H           0x002C
#define UART011_CR              0x0030
#define UART011_IFLS            0x0034
#define UART011_IMSC            0x0038
#define UART011_RIS             0x003C
#define UART011_MIS             0x0040
#define UART011_ICR             0x0044
#define UART011_DMACR           0x0048
#define FCR_FIFO_EN             0x01            /* Fifo enable */
#define FCR_RXSR                0x02            /* Receiver soft reset */
#define FCR_TXSR                0x04            /* Transmitter soft reset */

#define MCR_DTR                 0x01
#define MCR_RTS                 0x02

#define MCR_DMA_EN              0x04
#define MCR_TX_DFR              0x08

#define LCR_WLS_MSK     0x03            /* character length slect mask */
#define LCR_WLS_5       0x00            /* 5 bit character length */
#define LCR_WLS_6       0x01            /* 6 bit character length */
#define LCR_WLS_7       0x02            /* 7 bit character length */
#define LCR_WLS_8       0x03            /* 8 bit character length */
#define LCR_STB         0x04 /* Number of stop Bits, off = 1, on = 1.5 or 2) */
#define LCR_PEN         0x08            /* Parity eneble */
#define LCR_EPS         0x10            /* Even Parity Select */
#define LCR_STKP        0x20            /* Stick Parity */
#define LCR_SBRK        0x40            /* Set Break */
#define LCR_BKSE        0x80            /* Bank select enable */
#define FR_RXFE     0x10
#define FR_TXFF     0x20
#define FR_RXFF     0x40
#define FR_TXFE     0x80
#define LCR_8N1         0x0070

#define LCRVAL LCR_8N1          /* 8 data, 1 stop, no parity */
#define MCRVAL (MCR_DTR | MCR_RTS) /* RTS/DTR */
#define FCRVAL (FCR_FIFO_EN | FCR_RXSR | FCR_TXSR) /* Clear & enable FIFOs */

#define UART0_ADDRESS (IO+0x0)
#define UART1_ADDRESS (IO+0x1000)
#define UART2_ADDRESS (IO+0x2000)
#define UART3_ADDRESS (IO+0x3000)

#define CONFIG_LSI_SSP 1
#define CONFIG_SYS_MAX_FLASH_SECT    1024
#define CONFIG_LSI_SERIAL_FLASH 1
/* #define CONFIG_LSI_SERIAL_FLASH_ENV */
 /* #define CONFIG_ENV_IS_NOWHERE */
#if 0
#define CONFIG_ENV_IS_IN_SERIAL_FLASH   1
#define CONFIG_REDUNDAND_ENVIRONMENT     1
#define CONFIG_SYS_REDUNDAND_ENVIRONMENT 1
#define CONFIG_ENV_OFFSET                (512*1024)
/* #define CONFIG_ENV_SIZE                  (128*1024) */
#define CONFIG_ENV_RANGE                 (512*1024)
#define CONFIG_ENV_OFFSET_REDUND         (CONFIG_ENV_OFFSET + CONFIG_ENV_RANGE)
#define CONFIG_ENV_SIZE_REDUND            CONFIG_ENV_SIZE
#endif


#define TIMER0 (IO+0x1000)
#define TIMER1 (IO+0x1020)
#define TIMER2 (IO+0x1040)
#define TIMER3 (IO+0x1060)
#define TIMER4 (IO+0x1080)
#define TIMER5 (IO+0x10a0)
#define TIMER6 (IO+0x10c0)
#define TIMER7 (IO+0x10e0)

/*
  ======================================================================
  ======================================================================
  APB (AMBA) Dual Input Timers
  ======================================================================
  ======================================================================
*/

#define TIMER_LOAD                     0x00
#define TIMER_VALUE                    0x04
#define TIMER_CONTROL                  0x08
#define TIMER_CONTROL_ENABLE           0x80
#define TIMER_CONTROL_MODE             0x40
#define TIMER_CONTROL_INTERRUPT_ENABLE 0x20
#define TIMER_CONTROL_OUTPUT_MODE      0x10
#define TIMER_CONTROL_PRESCALER        0x0c
#define TIMER_CONTROL_SIZE             0x02
#define TIMER_CONTROL_ONE_SHOT         0x01
#define TIMER_INTCLR                   0x0C
#define TIMER_RIS                      0x10
#define TIMER_MIS                      0x14
#define TIMER_BGLOAD                   0x18




#define SSP (IO+0x8000)

#define SSP_CR0       0x000
#define SSP_CR1       0x004
#define SSP_DR        0x008
#define SSP_SR        0x00c
#define SSP_CPSR      0x010
#define SSP_IMSC      0x014
#define SSP_RIS       0x018
#define SSP_MIS       0x01c
#define SSP_ICR       0x020
#define SSP_DMACR     0x024
#define SSP_CSR       0x030
#define SSP_PERIPHID0 0xfe0
#define SSP_PERIPHID1 0xfe4
#define SSP_PERIPHID2 0xfe8
#define SSP_PERIPHID3 0xfec
#define SSP_PCELLID0  0xff0
#define SSP_PCELLID1  0xff4
#define SSP_PCELLID2  0xff8
#define SSP_PCELLID3  0xffc

#ifndef __ASSEMBLY__
int ssp_read(void *, unsigned long, unsigned long);
int ssp_write(void *, unsigned long, unsigned long, int);
int ssp_init(int, int);
#endif


#if 0
/* I2C  */
#define CONFIG_HARD_I2C
#define CONFIG_SYS_I2C_SPEED		100000
#define CONFIG_SYS_I2C_SLAVE		1
#define CONFIG_DRIVER_OMAP34XX_I2C
#define CONFIG_I2C_MULTI_BUS
#endif

/* TWL6035 */
#ifndef CONFIG_SPL_BUILD
#if 0
#define CONFIG_TWL6035_POWER
#endif
#endif

#if 0
/* MMC */
#define CONFIG_GENERIC_MMC
#define CONFIG_MMC
#define CONFIG_OMAP_HSMMC
/* #define CONFIG_DOS_PARTITION */

/* MMC ENV related defines */
#define CONFIG_ENV_IS_IN_MMC
#define CONFIG_SYS_MMC_ENV_DEV		1	/* SLOT2: eMMC(1) */
#define CONFIG_ENV_OFFSET		0xE0000
#define CONFIG_CMD_SAVEENV

#define CONFIG_SYS_CONSOLE_IS_IN_ENV
#endif

/* Flash */
#define CONFIG_SYS_NO_FLASH

/* Cache */
#define CONFIG_SYS_CACHELINE_SIZE	64
#define CONFIG_SYS_CACHELINE_SHIFT	6

/* commands to include */
#include <config_cmd_default.h>

/* Enabled commands */
#define CONFIG_CMD_EXT2		/* EXT2 Support                 */
#define CONFIG_CMD_FAT		/* FAT support                  */
#if 0
#define CONFIG_CMD_I2C		/* I2C serial bus support	*/
#define CONFIG_CMD_MMC		/* MMC support                  */
#endif
#define CONFIG_CMD_SAVEENV

/* Disabled commands */
#undef CONFIG_CMD_NET
#undef CONFIG_CMD_NFS
#undef CONFIG_CMD_FPGA		/* FPGA configuration Support   */
#undef CONFIG_CMD_IMLS		/* List all found images        */

/*
 * Environment setup
 */

#define CONFIG_BOOTDELAY	3

#define CONFIG_ENV_OVERWRITE

#define CONFIG_EXTRA_ENV_SETTINGS \
	"loadaddr=0x82000000\0" \
	"console=ttyO2,115200n8\0" \
	"usbtty=cdc_acm\0" \
	"vram=16M\0" \
	"mmcdev=0\0" \
	"mmcroot=/dev/mmcblk0p2 rw\0" \
	"mmcrootfstype=ext3 rootwait\0" \
	"mmcargs=setenv bootargs console=${console} " \
		"vram=${vram} " \
		"root=${mmcroot} " \
		"rootfstype=${mmcrootfstype}\0" \
	"loadbootscript=fatload mmc ${mmcdev} ${loadaddr} boot.scr\0" \
	"bootscript=echo Running bootscript from mmc${mmcdev} ...; " \
		"source ${loadaddr}\0" \
	"loaduimage=fatload mmc ${mmcdev} ${loadaddr} uImage\0" \
	"mmcboot=echo Booting from mmc${mmcdev} ...; " \
		"run mmcargs; " \
		"bootm ${loadaddr}\0" \

#define CONFIG_BOOTCOMMAND \
	"mmc dev ${mmcdev}; if mmc rescan; then " \
		"if run loadbootscript; then " \
			"run bootscript; " \
		"else " \
			"if run loaduimage; then " \
				"run mmcboot; " \
			"fi; " \
		"fi; " \
	"fi"

#define CONFIG_AUTO_COMPLETE		1

/*
 * Miscellaneous configurable options
 */

#define CONFIG_SYS_LONGHELP	/* undef to save memory */
/* #define CONFIG_SYS_HUSH_PARSER */	/* use "hush" command parser */ 
#define CONFIG_SYS_CBSIZE		256
/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + \
					sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS		16
/* Boot Argument Buffer Size */
#define CONFIG_SYS_BARGSIZE		(CONFIG_SYS_CBSIZE)

/*
 * memtest setup
 */
#define CONFIG_SYS_MEMTEST_START	0x80000000
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START + (32 << 20))

/* Default load address */
#define CONFIG_SYS_LOAD_ADDR		0x80000000

/* Use General purpose timer 1 */
#define CONFIG_SYS_TIMERBASE		GPT2_BASE
#define CONFIG_SYS_PTV			2	/* Divisor: 2^(PTV+1) => 8 */
#define CONFIG_SYS_HZ			1000

/*
 * SDRAM Memory Map
 * Even though we use two CS all the memory
 * is mapped to one contiguous block
 */
#define CONFIG_NR_DRAM_BANKS	1

#define CONFIG_SYS_SDRAM_BASE		0x00000000

/*#define CONFIG_SYS_INIT_SP_ADDR         (NON_SECURE_SRAM_END - GENERATED_GBL_DATA_SIZE) */
#define CONFIG_SYS_INIT_SP_ADDR         0x300000
#define CONFIG_SYS_MALLOC_BASE		CONFIG_SYS_INIT_SP_ADDR
#define CONFIG_SYS_MALLOC_SIZE (0x400000 - CONFIG_SYS_MALLOC_BASE)
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_SYS_MALLOC_SIZE)

#define CONFIG_SYS_EMIF_PRECALCULATED_TIMING_REGS

/* Defines for SDRAM init */
#ifndef CONFIG_SYS_EMIF_PRECALCULATED_TIMING_REGS
#define CONFIG_SYS_AUTOMATIC_SDRAM_DETECTION
#define CONFIG_SYS_DEFAULT_LPDDR2_TIMINGS
#endif


/*
  ======================================================================
  ======================================================================
  MDIO
  ======================================================================
  ======================================================================
*/

#define MDIO_CONTROL_RD_DATA (IO+0x10000)
#define MDIO_STATUS_RD_DATA  (IO+0x10004)
#define MDIO_CLK_OFFSET      (IO+0x10008)
#define MDIO_CLK_PERIOD      (IO+0x1000c)

#ifndef __ASSEMBLY__
int mdio_initialize( void );
unsigned short mdio_read( int phy, int reg );
void mdio_write( int phy, int reg, unsigned short value );
#endif


/*
  ======================================================================
  ======================================================================
  Network
  ======================================================================
  ======================================================================
*/
#define CONFIG_LSI_NET

#ifndef __ASSEMBLY__
extern unsigned char ethernet_address[6];
#endif

#if defined(ACP_ISS) || defined(NCR_TRACER) || defined(ACP2_SYSMEM_TEST)
#undef CONFIG_LSI_NET
#endif

#if defined(CONFIG_LSI_NET)
#define CONFIG_CMD_NET
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_PING
#define APP3XXNIC_RX_BASE  (IO+0xA0000)
#define APP3XXNIC_TX_BASE  (IO+0xA1000)
#define APP3XXNIC_DMA_BASE (IO+0xA2000)
#endif

/*
  ======================================================================
  ======================================================================
  Networking
  ======================================================================
  ======================================================================
*/
#ifndef __ASSEMBLY__

/*
  Standard PHY Registers
*/

/* -- control -- */

#define PHY_CONTROL 0x00

typedef union {
  unsigned short raw;


  struct {
#if 0
    unsigned short soft_reset      : 1;
    unsigned short loop_back       : 1;
    unsigned short force100        : 1; /* speedBit0 */
    unsigned short autoneg_enable  : 1;
    unsigned short power_down      : 1;
    unsigned short isolate         : 1;
    unsigned short restart_autoneg : 1;
    unsigned short full_duplex     : 1; /* duplex */
    unsigned short collision_test  : 1;
    unsigned short unused          : 7;
#else  /* __BIG_ENDIAN */
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
#endif /* __BIG_ENDIAN */
  } __attribute__ ( ( packed ) ) bits;
} __attribute__ ( ( packed ) ) phy_control_t;

/* -- status -- */

#define PHY_STATUS 0x01

typedef union {
  unsigned short raw;

  struct {
#if 0
    unsigned short t4_capable        : 1;
    unsigned short tx_fdx_capable    : 1;
    unsigned short tx_capable        : 1;
    unsigned short bt_fdx_capable    : 1;
    unsigned short tenbt_capable     : 1;
    unsigned short unused            : 4;
    unsigned short mf_pream_suppress : 1;
    unsigned short autoneg_comp      : 1; /* autoNegDone */
    unsigned short remote_fault      : 1; /* remoutFault */
    unsigned short autoneg_capable   : 1;
    unsigned short link_status       : 1; /* linkStatus */
    unsigned short jabber_detect     : 1;
    unsigned short extd_reg_capable  : 1;
#else
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
#endif /* __BIG_ENDIAN */
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
#if 0
    unsigned short id       : 6;
    unsigned short model    : 6;
    unsigned short revision : 4;
#else  /* __BIG_ENDIAN */
    unsigned short revision : 4;
    unsigned short model    : 6;
    unsigned short id       : 6;
#endif /* __BIG_ENDIAN */
  } __attribute__ ( ( packed ) ) bits;
} __attribute__ ( ( packed ) ) phy_id_low_t;

/* -- autoneg_advertise  -- */

#define PHY_AUTONEG_ADVERTISE 0x04

/* -- link_partner_ability -- */

#define PHY_LINK_PARTNER_ABILITY 0x05

/*
  Auto-negotiation Advertisement Values.
*/

#define PHY_AUTONEG_ADVERTISE_100FULL 0x101
#define PHY_AUTONEG_ADVERTISE_100     0x081
#define PHY_AUTONEG_ADVERTISE_10FULL  0x041
#define PHY_AUTONEG_ADVERTISE_10      0x021
#if 0
int axxia_phy_duplex( int );
int axxia_phy_link( int );
int axxia_phy_renegotiate( int, int );
int axxia_phy_reset( int );
int axxia_phy_speed( int );
void dump_packet(const char *, void *, int);
#endif

#endif /* __ASSEMBLY__ */



#ifndef __ASSEMBLY__
#include <asm/types.h>
#include <asm/u-boot.h>

void eth_getenv_enetaddrg(const char *, unsigned char [6]);

int lsi_femac_eth_init(bd_t *);
int acp_eioa_eth_init(bd_t *);

void lsi_femac_eth_halt(void);
void acp_eioa_eth_halt(void);
int lsi_femac_eth_send(volatile void *, int);
int acp_eioa_eth_send(volatile void *, int);

int lsi_femac_eth_rx(void);
int acp_eioa_eth_rx(void);

void lsi_net_receive_test(void);
void lsi_net_loopback_test(void);

void lsi_femac_receive_test(void);
void acp_eioa_receive_test(void);
void lsi_femac_loopback_test(void);
void acp_eioa_loopback_test(void);

#if 0
int axxia_eth_init(bd_t *);
void axxia_eth_halt(void);
int axxia_eth_send(volatile void *, int);
int axxia_eth_rx(void);
#endif

int phy_duplex( int );
int phy_link( int );
int phy_renegotiate( int, int );
int axxia_phy_reset( int );
int phy_speed( int );
void dump_packet(const char *, void *, int);

#endif /* __ASSEMBLY__ */

/* Defines for SPL */
#define CONFIG_SPL
#define CONFIG_SPL_FRAMEWORK
#define CONFIG_SPL_TEXT_BASE		0x20000000
#define CONFIG_SPL_MAX_SIZE		0x19000	/* 100K */
#define CONFIG_SPL_STACK		CONFIG_SYS_INIT_SP_ADDR
#define CONFIG_SPL_DISPLAY_PRINT

#define CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_SECTOR	0x300 /* address 0x60000 */
#define CONFIG_SYS_MMC_SD_FAT_BOOT_PARTITION	1
#define CONFIG_SYS_U_BOOT_MAX_SIZE_SECTORS	0x200 /* 256 KB */
#define CONFIG_SPL_FAT_LOAD_PAYLOAD_NAME	"u-boot.img"

#define CONFIG_SPL_LIBCOMMON_SUPPORT
#define CONFIG_SPL_LIBDISK_SUPPORT
#define CONFIG_SPL_I2C_SUPPORT
/* #define CONFIG_SPL_MMC_SUPPORT */
#define CONFIG_SPL_FAT_SUPPORT
#define CONFIG_SPL_LIBGENERIC_SUPPORT
#define CONFIG_SPL_SERIAL_SUPPORT
#define CONFIG_SPL_LDSCRIPT "$(CPUDIR)/omap-common/u-boot-spl.lds"

/*
 * 64 bytes before this address should be set aside for u-boot.img's
 * header. That is 80E7FFC0--0x80E80000 should not be used for any
 * other needs.
 */
#define CONFIG_SYS_TEXT_BASE		0x00000000

/*
 * BSS and malloc area 64MB into memory to allow enough
 * space for the kernel at the beginning of memory
 */
#define CONFIG_SPL_BSS_START_ADDR	0x84000000
#define CONFIG_SPL_BSS_MAX_SIZE		0x100000	/* 1 MB */
#define CONFIG_SYS_SPL_MALLOC_START	0x84100000
#define CONFIG_SYS_SPL_MALLOC_SIZE	0x100000	/* 1 MB */

#if 0
#define CONFIG_ENV_IS_NOWHERE
#endif

#if 1
#define CONFIG_LSI_SERIAL_FLASH_ENV
#define CONFIG_ENV_IS_IN_SERIAL_FLASH   1
#define CONFIG_REDUNDAND_ENVIRONMENT     1
#define CONFIG_SYS_REDUNDAND_ENVIRONMENT 1
#define CONFIG_ENV_OFFSET                (512*1024)
/* #define CONFIG_ENV_SIZE                  (128*1024) */
#define CONFIG_ENV_RANGE                 (512*1024)
#define CONFIG_ENV_OFFSET_REDUND         (CONFIG_ENV_OFFSET + CONFIG_ENV_RANGE)
#define CONFIG_ENV_SIZE_REDUND            CONFIG_ENV_SIZE
#endif

#if 0
#ifndef __ASSEMBLY__
#include <common.h>
#include <asm/io.h>

extern int lsi_logio_enable;

#ifdef LSI_LOGIO
#define LSI_LOGIO_ENABLE() {lsi_logio_enable = 1;}
#define LSI_LOGIO_DISABLE() {lsi_logio_enable = 0;}
#define LSI_LOGIO_ENABLED() (1 == lsi_logio_enable)
static inline unsigned long _READL(const char *, int, unsigned long);
static inline unsigned long
_READL(const char *file, int line, unsigned long address)
{
        unsigned long value;
        value = readl(address);

        if (0 != lsi_logio_enable)

                printf("%s:%d - Read 0x%08lx from 0x%08lx\n",
                       file, line, value, address);

        return value;
}
#define READL(address) _READL(__FILE__, __LINE__, (address))
static inline void _WRITEL(const char *, int, unsigned long, unsigned long);
static inline void
_WRITEL(const char *file, int line, unsigned long value, unsigned long address)
{
        writel(value, address);

        if (0 != lsi_logio_enable)
                printf( "%s:%d - Wrote 0x%08lx to 0x%08lx\n",
                        file, line, value, address);

        return;
}
#define WRITEL(value, address) _WRITEL(__FILE__, __LINE__, (value), (address))
#else  /* LSI_LOGIO */
#define LSI_LOGIO_ENABLE() {}
#define LSI_LOGIO_DISABLE() {}
#define LSI_LOGIO_ENABLED() 0
#define READL(address) readl((address))
#define WRITEL(value, address) writel((value), (address))
#endif /* LSI_LOGIO */
#endif

#endif

/*
  ----------------------------------------------------------------------
  Include the LSI common header.
*/

#if 0
#include <configs/lsi.h>
#endif


#endif /* __CONFIG_H */
