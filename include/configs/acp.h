/*
 * (C) Copyright 2009 LSI Corporation <www.lsi.com>
 * John Jacques <john.jacques@lsi.com>
 * Configuration settings for the LSI ACP development boards.
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

#ifndef __CONFIGS_ACP_H
#define __CONFIGS_ACP_H

/*
  ==============================================================================
  Define the hardware.
*/

#define CONFIG_ACP   1		/* LSI ACP Board             */
#define CONFIG_476FP 1		/* Specific PPC476FP Support */
#define CONFIG_47x   1		/* ... PPC47x family         */
#define CONFIG_4xx   1		/* ... PPC4xx family         */

#define CONFIG_BOOKE 1

/*
  ==============================================================================
  Basic size reduction for the 2nd stage boot loader.
*/

#ifdef CONFIG_ACP2
#undef CONFIG_BOOTM_NETBSD
#undef CONFIG_BOOTM_RTEMS
#undef CONFIG_GZIP
#undef CONFIG_ZLIB
#endif /* CONFIG_ACP2 */

/*
  ======================================================================
  ======================================================================
  Splash
  ======================================================================
  ======================================================================
*/

#ifndef __ASSEMBLY__
void acp_splash( void );
#endif /* __ASSEMBLY__ */

/*
  ======================================================================
  ======================================================================
  Resets
  ======================================================================
  ======================================================================
*/

#define CONFIG_BOARD_RESET 1

#ifdef ACP_25xx
#define DCR_RESET_BASE 0x1700
#else
#define DCR_RESET_BASE 0xe00
#endif

/*
  ======================================================================
  ======================================================================
  Memory
  ======================================================================
  ======================================================================
*/

#define CONFIG_SYS_DCACHE_SIZE 32768
#define CONFIG_SYS_ICACHE_SIZE 32768
#define CONFIG_SYS_CACHELINE_SIZE 32

#define SYSMEM  0x00000000
#define IO      0xf0800000
#define LCM     0xf0a00000
#define ROM     0xf0b00000

#ifndef __ASSEMBLY__
unsigned long get_sysmem_size( void );
#endif /* __ASSEMBLY__ */

/*
  ======================================================================
  ======================================================================
  Don't  re-locate or do low-level initialization.
  ======================================================================
  ======================================================================
*/

#define CONFIG_SKIP_LOWLEVEL_INIT
#define CONFIG_SKIP_RELOCATE_UBOOT

/*
  ======================================================================
  ======================================================================
  Nuevo Conf Ring Access, see board/lsi/acp/ncr.c for the implementation
  ======================================================================
  ======================================================================
*/

#ifndef __ASSEMBLY__
#define NCP_REGION_ID( node, target ) \
( unsigned long ) ( ( ( ( node ) & 0xffff ) << 16 ) | ( ( target ) & 0xffff ) )
#define NCP_NODE_ID( region ) ( ( ( region ) >> 16 ) & 0xffff )
#define NCP_TARGET_ID( region ) ( ( region ) & 0xffff )
int ncr_read(unsigned long, unsigned long, int, void *);
int ncr_read8( unsigned long, unsigned long, unsigned char * );
int ncr_read32( unsigned long, unsigned long, unsigned long * );
int ncr_write(unsigned long, unsigned long, int, void *);
int ncr_write8( unsigned long, unsigned long, unsigned char );
int ncr_write32( unsigned long, unsigned long, unsigned long );
int ncr_modify32( unsigned long, unsigned long, unsigned long, unsigned long );
int ncr_and( unsigned long, unsigned long, unsigned long );
int ncr_or( unsigned long, unsigned long, unsigned long );
int ncr_poll( unsigned long, unsigned long, unsigned long,
	      unsigned long, unsigned long, unsigned long );
void ncr_tracer_enable( void );
void ncr_tracer_disable( void );
int ncr_tracer_is_enabled( void );
void ncr_enable( void );
void ncr_disable( void );
#endif

/*
  ======================================================================
  ======================================================================
  DCR Access, see board/lsi/acp/dcr.c for the implementation
  ======================================================================
  ======================================================================
*/

#ifndef __ASSEMBLY__
unsigned long dcr_read( unsigned long );
void dcr_write( unsigned long, unsigned long );
#endif

/*
  ======================================================================
  ======================================================================
  Utilities (see board/lsi/acp/util.S)
  ======================================================================
  ======================================================================
*/

#ifndef __ASSEMBLY__
void mmtest( unsigned long, unsigned long, unsigned long );
#endif

/*
  ======================================================================
  ======================================================================
  NAND
  ======================================================================
  ======================================================================
*/

#ifndef NCR_TRACER
#define CONFIG_CMD_SAVEENV
#define CFG_MAX_NAND_DEVICE        1
#define CONFIG_SYS_MAX_NAND_DEVICE 1
#define MAX_NAND_CHIPS             CFG_MAX_NAND_DEVICE
#define CFG_NAND_BASE              (IO+0x40000)
#define CONFIG_SYS_NAND_BASE       (IO+0x40000)
#define CONFIG_SYS_FLASH_BASE      (IO+0x40000)
#define MTDIDS_DEFAULT		"nand0=acp-nand"
#define MTDPARTS_DEFAULT	"mtdparts=acp-nand:512K(2ndStage),512K(env-0),512K(env-1),512K(3rdStage),4M(linux),200M(linux_fs),32M(ose),16M(ose_backup),-(ose_storage)"
#define MTDPARTS_REQUIRED       "mtdparts=acp-nand:512K(2ndStage),512K(env-0),512K(env-1),512K(3rdStage)"
#endif

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

#if defined(ACP_25xx)
#define TIMER0 (IO+0x29000)
#define TIMER1 (IO+0x29020)
#define TIMER2 (IO+0x29040)
#define TIMER3 (IO+0x29060)
#define TIMER4 (IO+0x29080)
#define TIMER5 (IO+0x290a0)
#define TIMER6 (IO+0x290c0)
#define TIMER7 (IO+0x290e0)
#else
#define TIMER0 (IO+0x8000)
#define TIMER1 (IO+0x8020)
#define TIMER2 (IO+0x8040)
#define TIMER3 (IO+0x8060)
#define TIMER4 (IO+0x8080)
#define TIMER5 (IO+0x80a0)
#define TIMER6 (IO+0x80c0)
#define TIMER7 (IO+0x80e0)
#endif

/*
  ======================================================================
  ======================================================================
  APB (AMBA PL011) UARTs
  ======================================================================
  ======================================================================
*/

#define CONFIG_BAUDRATE 9600
#define CFG_BAUDRATE_TABLE   { 9600, 19200, 38400, 57600, 115200 }
#define CONFIG_SYS_BAUDRATE_TABLE   { 9600, 19200, 38400, 57600, 115200 }

#ifdef ACP_EMU
#define UART_CLOCK_SPEED  3250000
#else
#define UART_CLOCK_SPEED 25000000
#endif

#define	UART011_DR		0x0000
#define	UART011_ECR		0x0004
#define	UART011_FR		0x0018
#define	UART011_ILPR		0x0020
#define	UART011_IBRD		0x0024
#define	UART011_FBRD		0x0028
#define	UART011_LCR_H		0x002C
#define	UART011_CR		0x0030
#define	UART011_IFLS		0x0034
#define	UART011_IMSC		0x0038
#define	UART011_RIS		0x003C
#define	UART011_MIS		0x0040
#define	UART011_ICR		0x0044
#define	UART011_DMACR		0x0048

#define FCR_FIFO_EN     	0x01		/* Fifo enable */
#define FCR_RXSR        	0x02		/* Receiver soft reset */
#define FCR_TXSR        	0x04		/* Transmitter soft reset */

#define MCR_DTR         	0x01
#define MCR_RTS         	0x02
#define MCR_DMA_EN      	0x04
#define MCR_TX_DFR      	0x08

#define LCR_WLS_MSK	0x03		/* character length slect mask */
#define LCR_WLS_5	0x00		/* 5 bit character length */
#define LCR_WLS_6	0x01		/* 6 bit character length */
#define LCR_WLS_7	0x02		/* 7 bit character length */
#define LCR_WLS_8	0x03		/* 8 bit character length */
#define LCR_STB		0x04 /* Number of stop Bits, off = 1, on = 1.5 or 2) */
#define LCR_PEN		0x08		/* Parity eneble */
#define LCR_EPS		0x10		/* Even Parity Select */
#define LCR_STKP	0x20		/* Stick Parity */
#define LCR_SBRK	0x40		/* Set Break */
#define LCR_BKSE	0x80		/* Bank select enable */

#define FR_RXFE     0x10
#define FR_TXFF     0x20
#define FR_RXFF     0x40
#define FR_TXFE     0x80

#define LCR_8N1		0x0070

#define LCRVAL LCR_8N1		/* 8 data, 1 stop, no parity */
#define MCRVAL (MCR_DTR | MCR_RTS) /* RTS/DTR */
#define FCRVAL (FCR_FIFO_EN | FCR_RXSR | FCR_TXSR) /* Clear & enable FIFOs */

#if defined(ACP_25xx)
#define UART0_ADDRESS (IO+0x24000)
#define UART1_ADDRESS (IO+0x25000)
#else
#define UART0_ADDRESS (IO+0x4000)
#define UART1_ADDRESS (IO+0x5000)
#endif

/*
  ======================================================================
  ======================================================================
  ARM PrimeCell Synchronous Serial Port (PL022)
  ======================================================================
  ======================================================================
*/

#if defined(ACP_25xx)
#define SSP (IO+0x22000)
#else
#define SSP (IO+0x2000)
#endif

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

/*
  ======================================================================
  ======================================================================
  Console
  ======================================================================
  ======================================================================
*/

#define CFG_ACP_SERIAL

/*
  ======================================================================
  ======================================================================
  Other Addresses
  ======================================================================
  ======================================================================
*/

#if !defined(ACP_25xx)
#define APB2RC (IO+0xa000)
#endif

#define NCA (IO+0x120000)

/*
  ======================================================================
  ======================================================================
  MDIO
  ======================================================================
  ======================================================================
*/

#if defined(ACP_25xx)
#define MDIO_CONTROL_RD_DATA (IO+0x2a000)
#define MDIO_STATUS_RD_DATA  (IO+0x2a004)
#define MDIO_CLK_OFFSET      (IO+0x2a008)
#define MDIO_CLK_PERIOD      (IO+0x2a00c)
#else
#define MDIO_CONTROL_RD_DATA (IO+0x9000)
#define MDIO_STATUS_RD_DATA  (IO+0x9004)
#define MDIO_CLK_OFFSET      (IO+0x9008)
#define MDIO_CLK_PERIOD      (IO+0x900c)
#endif

#ifndef __ASSEMBLY__
int mdio_initialize( void );
unsigned short mdio_read( int phy, int reg );
void mdio_write( int phy, int reg, unsigned short value );
#endif

/*
  ======================================================================
  ======================================================================
  GP-REG
  ======================================================================
  ======================================================================
*/

#if defined(ACP_25xx)
#define GPREG_GPDMA             (IO+0x00)
#define GPREG_MAC               (IO+0x04)
#define GPREG_USB               (IO+0x08)
#define GPREG_STATUS            (IO+0x0c)
#define GPREG_PCI_SRIO_PHY_CTRL (IO+0x10)
#define GPREG_PHY_CTRL0         (IO+0x14)
#define GPREG_PHY_CTRL1         (IO+0x18)
#define GPREG_PHY_CTRL2         (IO+0x1c)
#define GPREG_PHY_STAT0         (IO+0x20)
#define GPREG_PHY_STAT1         (IO+0x24)
#define GPREG_MISC_CTRL         (IO+0x28)
#else
#define GPREG_GPDMA  (IO+0xc000)
#define GPREG_MAC    (IO+0xc004)
#define GPREG_USB    (IO+0xc008)
#define GPREG_STATUS (IO+0xc00c)
#if defined(ACP_X1V2) || defined(CONFIG_ACP_342X)
#define GPREG_PCI_SRIO_PHY_CTRL (IO+0xc010)
#define GPREG_PHY_CTRL0         (IO+0xc014)
#define GPREG_PHY_CTRL1         (IO+0xc018)
#define GPREG_PHY_CTRL2         (IO+0xc01c)
#define GPREG_PHY_STAT0         (IO+0xc020)
#define GPREG_PHY_STAT1         (IO+0xc024)
#define GPREG_MISC_CTRL         (IO+0xc028)
#endif
#endif

/*
  ======================================================================
  ======================================================================
  SBB
  ======================================================================
  ======================================================================
*/

#if defined(ACP_25xx)
#define CONFIG_LSI_SBB 1
#ifndef __ASSEMBLY__
int sbb_verify_image(void *, void *, int);
int sbb_encrypt_image(void *, void *, int);
int sbb_decrypt_range(void *, void *, int);
#endif
#endif

/*
  ======================================================================
  ======================================================================
  PCIe Configuration
  ======================================================================
  ======================================================================
*/

#if defined(ACP_25xx)
#define PCIE0_CONFIG (IO+0x180000)
#define PCIE1_CONFIG (IO+0x188000)
#else
#if !defined(ACP_X1V1) && !defined(ACP_ISS)
#define PCIE0_CONFIG (IO+0xc0000)
#define PCIE1_CONFIG (IO+0xc8000)
#define PCIE2_CONFIG (IO+0xd0000)
#endif
#endif

/*
  ======================================================================
  ======================================================================
  Non-Volatile Storage
  ======================================================================
  ======================================================================
*/

#if defined(ACP_ISS) || defined(NCR_TRACER) || defined(ACP2_SYSMEM_TEST)
#undef CONFIG_LSI_NAND
#undef CONFIG_LSI_NAND_ENV
#undef CONFIG_LSI_SERIAL_FLASH
#undef CONFIG_LSI_SERIAL_FLASH_ENV
#define CONFIG_SYS_NO_FLASH
#define CONFIG_CMD_ENV
#define CONFIG_ENV_IS_IN_NVRAM
#define CONFIG_ENV_SIZE           (64 * 1024)
#define CONFIG_ENV_ADDR           ((4 * 1024 * 1024) - CONFIG_ENV_SIZE)
#define CONFIG_SYS_MAX_FLASH_SECT 1024
#define CONFIG_SYS_MAX_FLASH_BANKS 4
#endif

#if defined(CONFIG_LSI_NAND)
#define CONFIG_FLASH_CFI_DRIVER      1
#define CONFIG_SYS_FLASH_CFI         1
#define CONFIG_CMD_NAND
#elif defined(CONFIG_LSI_SERIAL_FLASH)
#endif

#if defined(CONFIG_LSI_NAND_ENV)
#if !defined(CONFIG_LSI_NAND)
#error "CONFIG_LSI_NAND must be defined for CONFIG_LSI_NAND_ENV"
#endif
#define CONFIG_CMD_ENV
#define CONFIG_ENV_IS_IN_NAND        1
#define CONFIG_REDUNDAND_ENVIRONMENT 1
#define CONFIG_SYS_MAX_FLASH_SECT    1024
#define CONFIG_SYS_MAX_FLASH_BANKS   4
#define CONFIG_ENV_OFFSET            (512*1024)
#define CONFIG_ENV_SIZE              (128*1024)
#define CONFIG_ENV_RANGE             (512*1024)
#define CONFIG_ENV_OFFSET_REDUND     (CONFIG_ENV_OFFSET + CONFIG_ENV_RANGE)
#define CONFIG_ENV_SIZE_REDUND       CONFIG_ENV_SIZE
#elif defined(CONFIG_LSI_SERIAL_FLASH_ENV)
#if !defined(CONFIG_LSI_SERIAL_FLASH)
#error "CONFIG_LSI_SERIAL_FLASH must be defined for CONFIG_LSI_SERIAL_FLASH_ENV"
#endif
#define CONFIG_SYS_NO_FLASH
#define CONFIG_ENV_IS_IN_SERIAL_FLASH
#define CONFIG_REDUNDAND_ENVIRONMENT     1
#define CONFIG_SYS_REDUNDAND_ENVIRONMENT 1
#define CONFIG_ENV_OFFSET                (512 * 1024)
#define CONFIG_ENV_SIZE                  (128 * 1024)
#define CONFIG_ENV_RANGE                 (512 * 1024)
#define CONFIG_ENV_OFFSET_REDUND         (CONFIG_ENV_OFFSET + CONFIG_ENV_RANGE)
#define CONFIG_ENV_SIZE_REDUND            CONFIG_ENV_SIZE
#endif

/*
  ======================================================================
  ======================================================================
  IO
  ======================================================================
  ======================================================================
*/

#ifndef __ASSEMBLY__
unsigned long acpreadio( const volatile unsigned long * );
void acpwriteio( unsigned long, volatile unsigned long * );
#endif /* __ASSEMBLY__ */

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
  ======================================================================
  ======================================================================
  Clocks
  ======================================================================
  ======================================================================
*/

#ifndef __ASSEMBLY__
#define CLK_REF0 125000000
typedef enum { ppc, peripheral } acp_clock_t;
int acp_clock_get(acp_clock_t, unsigned long *);
#endif /* __ASSEMBLY__ */

/*
  ======================================================================
  ======================================================================
  Networking
  ======================================================================
  ======================================================================
*/

#ifndef __ASSEMBLY__
#include <asm/types.h>
#include <asm/u-boot.h>

extern unsigned char ethernet_address[6];

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
#endif /* __ASSEMBLY__ */

/*
  ======================================================================
  ======================================================================
  25xx Bring Up Test...
  ======================================================================
  ======================================================================
*/

#ifdef ACP_25xx

/*
#define PPC_RUN_ON_REF
*/

/*
#define PPC_PLL_FREQ 1100000000
#define PPC_PLL_PARAMETER 0xa0240551
*/

/*
#define PPC_PLL_FREQ  900000000
#define PPC_PLL_PARAMETER 0xa02202d1
*/

#define PPC_PLL_FREQ  800000000
#define PPC_PLL_PARAMETER 0xa02405d2

/*#define DISABLE_CORE_1*/

/*#define EXTRA_SYSMEM_INIT_UDELAY 5000*/

/*#define UDELAY_AFTER_PLL_INIT 1000000*/

/*#define DISABLE_RESET*/

#endif	/* ACP_25xx */

/*
  ======================================================================
  ======================================================================
  Errata
  ======================================================================
  ======================================================================
*/

#define SYSTEM_BOOTCORE 0

/*
  The 1st stage leaves both L1 caches disabled and all memory in the
  WIMG=0101 state.  L3 is in the reset state.

  Use the following to set ILIID and WIMG (the ACP_CACHE_TLB value)
  and whether the L3 cache gets enabled after initializing system
  memory.

  Setting bit 17 will disable the L1 instruction cache, bit 18 the data.

  Bits 11:8 are WIMG.

  So, to disable both L1 caches, and L2, 0x00030507.

  The default is 0x00000207.
*/

/*#define ACP_CACHE_TLB 0x00030507*/
/*#define ACP_CACHE_TLB 0x00000507*/
/*#define ACP_CACHE_TLB 0x00030207*/
#define ACP_CACHE_TLB 0x00000207
/*#define ACP_DISABLE_L3*/

/*
  Clock Lock Verification.
*/

/*#define CLOCK_LOCK_VERIFY_EARLY*/
/*#define CLOCK_LOCK_VERIFY_GPIO*/

#ifndef __ASSEMBLY__
int acp_clock_lock_verify(int, int);
#endif

#if defined(ACP_X1V1)
#define CCR0_DEFAULT 0x01604040
#define CCR1_DEFAULT 0x00000400
#define CCR2_DEFAULT 0x04000000
#elif defined(ACP_25xx)
#define CCR0_DEFAULT 0x00200000
#define CCR1_DEFAULT 0x00000000
#define CCR2_DEFAULT 0x00000000
#else
#define CCR0_DEFAULT 0x00200000
#define CCR1_DEFAULT 0x00000000
#define CCR2_DEFAULT 0x00000000
#endif

#ifndef ACP2_SYSMEM_TEST
#define CONFIG_LSI_SSP 1
#define CONFIG_LSI_MDIO 1
#define CONFIG_LSI_IO 1
#endif
#define CONFIG_LSI_NCR 1

#define NCP_BIG_ENDIAN 1

#ifndef __ASSEMBLY__
#define mb() {__asm__ __volatile__ ("sync" : : : "memory");}
void acp_failure( const char *, const char *, const int );
void acp_failure_exception(unsigned long, unsigned long);
void acp_failure_enable_console(void);
void acp_failure_disable_console(void);
extern unsigned long perf_clock;
void acp_reset(int argc, char *argv[]);
int serial_early_init(void);
#endif /* __ASSEMBLY__ */

#define CONFIG_COMMANDS
#define CFG_SDRAM_BASE 0
#define CONFIG_SYS_SDRAM_BASE 0
#define CONFIG_SYS_CLK_FREQ	33333333    /* external freq to pll	*/
#define CONFIG_CMD_BOOTD

/*
  bootp/dhcp
*/


#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_DNS
#define CONFIG_BOOTP_BOOTFILESIZE

/*
 * Miscellaneous configurable options
 */
#ifdef ACP_ISS
#define CONFIG_BOOTDELAY	1	/* autoboot after 5 seconds	*/
#else
#define CONFIG_BOOTDELAY	5	/* autoboot after 5 seconds	*/
#endif
#define CFG_LOAD_ADDR		0x400000  /* default load address	*/
#define CONFIG_SYS_LOAD_ADDR	0x400000  /* default load address	*/
#define CFG_HZ			1000	/* decrementer freq: 1 ms ticks	*/
#define CONFIG_SYS_HZ		1000	/* decrementer freq: 1 ms ticks	*/
#define CONFIG_ZERO_BOOTDELAY_CHECK	/* check for keypress on bootdelay==0 */
#define CONFIG_VERSION_VARIABLE 	/* include version env variable */
#define CFG_CONSOLE_INFO_QUIET		/* don't print console @ startup*/
#define CONFIG_LOADS_ECHO		/* echo on for serial download	*/
#define CFG_LOADS_BAUD_CHANGE		/* allow baudrate change	*/
#define CONFIG_ENV_OVERWRITE    1       /* allow etheraddr to be changed */

/*
 * For booting Linux, the board info and command line data
 * have to be in the first 8 MB of memory, since this is
 * the maximum mapped by the Linux kernel during initialization.
 */
#define CFG_BOOTMAPSZ		(8 << 20) /* Initial Memory map for Linux */
#define CONFIG_SYS_BOOTMAPSZ		(8 << 20) /* Initial Memory map for Linux */

#define xstr(s)	str(s)
#define str(s)	#s

#ifndef __ASSEMBLY__
extern unsigned long _bss_start;
extern unsigned long _bss_end;
#endif

/*
  ----------------------------------------------------------------------
  Include the LSI common header.
*/

#include <configs/lsi.h>

#endif /* __CONFIGS_ACP_H */
