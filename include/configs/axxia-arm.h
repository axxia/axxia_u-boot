/*
 * (C) Copyright 2009-2013
 * LSI <www.lsi.com>
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

#ifndef __CONFIGS_AXXIA_ARM_H
#define __CONFIGS_AXXIA_ARM_H

#define CONFIG_AXXIA_ARM

/* #define NCR_TRACER */

#ifndef __ASSEMBLY__
#include <linux/types.h>
#include <asm/sizes.h>
#endif

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define NCP_BIG_ENDIAN
#endif

#ifndef __ASSEMBLY__
void acp_failure(const char *, const char *, const int);
int axxia_initialize(void);
void display_va_attr(void *);
void axxia_mtest_check_ecc(void);
#endif	/* __ASSEMBLY__ */

/*
  ==============================================================================
  ==============================================================================
*/

/*#define SYSCACHE_ONLY_MODE*/

#ifdef SYSCACHE_ONLY_MODE
#ifndef __ASSEMBLY__
void ncr_l3tags(void);
#endif
#endif

/****** BIST *************/
#ifndef __ASSEMBLY__
enum bistType {
	data = 0,
	addr = 1,
	both = 2
};

int axxia_sysmem_bist(unsigned long long address,
	unsigned long long sysmem_size,
	enum bistType type);

unsigned int mbist_range(
	unsigned long memsize, unsigned long dual_ddr,
	unsigned long maskbits, unsigned long mbist_multiple,
	unsigned long mbist_addr[], unsigned long mbist_len[],
	unsigned long test_addr[], unsigned long test_len[],
	unsigned long prot_addr[], unsigned long prot_len[]);

void mbist_power2(unsigned long in_addr, unsigned long in_len,
	unsigned long mbist_addr[], unsigned long mbist_len[]);
#endif

/*
  ==============================================================================
  ==============================================================================
  Version
  ==============================================================================
  ==============================================================================
*/

#ifndef __ASSEMBLY__
int is_asic( void );
#endif /* __ASSEMBLY__ */

/*
 * High Level Configuration Options
 */
#define CONFIG_ARMV7	/* This is an ARM V7 CPU core */
#define CONFIG_AXXIA_ARM	/* in a TI OMAP core */
#define CONFIG_AXXIA
#define CONFIG_ACP
#define CONFIG_AXXIA_USB

#define CONFIG_SYS_HZ           1000    /* decrementer freq: 1 ms ticks */

#ifdef CONFIG_AXXIA_EMU
#define SYSTIMER_RATE		4096000
#else  /* CONFIG_AXXIA_EMU */
#define SYSTIMER_RATE		256000000
#endif	/* CONFIG_AXXIA_EMU */

#define CONFIG_SYS_UBOOT_START       0
#define CONFIG_SYS_SPI_U_BOOT_OFFS   SZ_1M

/*
   Flash
 */
#define CONFIG_SPI_FLASH
#define CONFIG_SPI_FLASH_SPANSION

/*
  ==============================================================================
  ==============================================================================
  GPIO
  ==============================================================================
  ==============================================================================
*/

#ifndef __ASSEMBLY__
#define CONFIG_CMD_GPIO
#define CONFIG_AXXIA_GPIO

typedef enum { AXXIA_GPIO_0, AXXIA_GPIO_1 } axxia_gpio_t;

int axxia_gpio_get_direction(axxia_gpio_t gpio, int pin);
int axxia_gpio_set_direction(axxia_gpio_t gpio, int pin, int direction);
int axxia_gpio_get(axxia_gpio_t gpio, int pin);
int axxia_gpio_set(axxia_gpio_t gpio, int pin, int value);
#endif	/* __ASSEMBLY__ */

/*
  ==============================================================================
  ==============================================================================
  I2C
  ==============================================================================
  ==============================================================================
*/

#ifndef __ASSEMBLY__
#define CONFIG_CMD_I2C
#define CONFIG_AXXIA_AXM_I2C
#define CONFIG_CMD_SDRAM
#define CONFIG_AXXIA_I2C
#define CONFIG_I2C_MULTI_BUS
#define CONFIG_SYS_MAX_I2C_BUS 4
#define CONFIG_SYS_I2C_SPEED 100000


#define AI2C_REG_I2C_X7_GLOBAL_CONTROL     (0x0000)   /*!< Offset to reg
                                                        Global Control */
#define AI2C_REG_I2C_X7_INTERRUPT_STATUS   (0x0004)   /*!< Offset to reg
                                                        Interrupt Status */
#define AI2C_REG_I2C_X7_INTERRUPT_ENABLE   (0x0008)   /*!< Offset to reg
                                                        Interrupt Enable */
#define AI2C_REG_I2C_X7_WAIT_TIMER_CONTROL (0x000C)   /*!< Offset to reg
                                                        Wait Timer Control */
#define AI2C_REG_I2C_X7_IBML_TIMEOUT       (0x0010)   /*!< Offset to reg
                                                        IBML Timeout */
#define AI2C_REG_I2C_X7_IBML_LOW_MEXT      (0x0014)   /*!< Offset to reg
                                                        IBML Low MEXT */
#define AI2C_REG_I2C_X7_IBML_LOW_SEXT      (0x0018)   /*!< Offset to reg
                                                        IBML Low SEXT */
#define AI2C_REG_I2C_X7_TIMER_CLOCK_DIV    (0x001C)   /*!< Offset to reg
                                                        Timer Clock Division */
#define AI2C_REG_I2C_X7_I2C_BUS_MONITOR    (0x0020)   /*!< Offset to reg I2C
                                                        Bus Monitor */
#define AI2C_REG_I2C_X7_SOFT_RESET         (0x0024)   /*!< Offset to reg Soft
                                                        Reset */
#define AI2C_REG_I2C_X7_MST_COMMAND        (0x0028)   /*!< Offset to reg
                                                        Master Command */
#define AI2C_REG_I2C_X7_MST_RX_XFER        (0x002C)   /*!< Offset to reg
                                                        Master Receive
                                                        Transfer */
#define AI2C_REG_I2C_X7_MST_TX_XFER        (0x0030)   /*!< Offset to reg
                                                        Master Transmit
                                                        Transfer */
#define AI2C_REG_I2C_X7_MST_ADDR_1         (0x0034)   /*!< Offset to reg
                                                        Master Address 1 */
#define AI2C_REG_I2C_X7_MST_ADDR_2         (0x0038)   /*!< Offset to reg
                                                        Master Address 2 */
#define AI2C_REG_I2C_X7_MST_DATA           (0x003C)   /*!< Offset to reg
                                                        Master Data */
#define AI2C_REG_I2C_X7_MST_TX_FIFO        (0x0040)   /*!< Offset to reg
                                                        Master Transmit FIFO */
#define AI2C_REG_I2C_X7_MST_RX_FIFO        (0x0044)   /*!< Offset to reg
                                                        Master Receive FIFO */
#define AI2C_REG_I2C_X7_MST_INT_ENABLE     (0x0048)   /*!< Offset to reg
                                                        Master Interrupt
                                                        Enable */
#define AI2C_REG_I2C_X7_MST_INT_STATUS     (0x004C)   /*!< Offset to reg
                                                        Master Interrupt
                                                        Status */
#define AI2C_REG_I2C_X7_MST_TX_BYTES_XFRD  (0x0050)   /*!< Offset to reg
                                                        Master TX Bytes
                                                        Transferred */
#define AI2C_REG_I2C_X7_MST_RX_BYTES_XFRD  (0x0054)   /*!< Offset to reg
                                                        Master RX Bytes
                                                        Transferred */
#define AI2C_REG_I2C_X7_SLV_ADDR_DEC_CTL   (0x0058)   /*!< Offset to reg
                                                        Slave Address
                                                        Decrement Ctl */
#define AI2C_REG_I2C_X7_SLV_ADDR_1         (0x005C)   /*!< Offset to reg
                                                        Slave Address 1 */
#define AI2C_REG_I2C_X7_SLV_ADDR_2         (0x0060)   /*!< Offset to reg
                                                        Slave Address 2 */
#define AI2C_REG_I2C_X7_SLV_RX_CTL         (0x0064)   /*!< Offset to reg
                                                        Slave Receive Control */
#define AI2C_REG_I2C_X7_SLV_DATA           (0x0068)   /*!< Offset to reg
                                                        Slave Data */
#define AI2C_REG_I2C_X7_SLV_RX_FIFO        (0x006C)   /*!< Offset to reg
                                                        Slave Receive FIFO */
#define AI2C_REG_I2C_X7_SLV_INT_ENABLE     (0x0070)   /*!< Offset to reg
                                                        Slave Interrupt
                                                        Enable */
#define AI2C_REG_I2C_X7_SLV_INT_STATUS     (0x0074)   /*!< Offset to reg
                                                        Slave Interrupt
                                                        Status */
#define AI2C_REG_I2C_X7_SLV_READ_DUMMY     (0x0078)   /*!< Offset to reg
                                                        Slave Read Dummy */
#define AI2C_REG_I2C_X7_SCL_HIGH_PERIOD    (0x0080)   /*!< Offset to reg
                                                        SCL High Period */
#define AI2C_REG_I2C_X7_SCL_LOW_PERIOD     (0x0084)   /*!< Offset to reg
                                                        SCL Low Period */
#define AI2C_REG_I2C_X7_SPIKE_FLTR_LEN     (0x0088)   /*!< Offset to reg
                                                        Spike Filter Length */
#define AI2C_REG_I2C_X7_SDA_SETUP_TIME     (0x008C)   /*!< Offset to reg
                                                        SDA Setup Time */
#define AI2C_REG_I2C_X7_SDA_HOLD_TIME      (0x0090)   /*!< Offset to reg
                                                        SDA Hold Time */
#define AI2C_REG_I2C_X7_SMB_ALERT          (0x0094)   /*!< Offset to reg
                                                        SMB Alert */
#define AI2C_REG_I2C_X7_UDID_W7            (0x0098)   /*!< Offset to reg
                                                        UDID W7 */
#define AI2C_REG_I2C_X7_UDID_W7_DEFAULT    (0x00000008) /*!< Def value reg
                                                        UDID W7 */
#define AI2C_REG_I2C_X7_UDID_W6            (0x009C)   /*!< Offset to reg
                                                        UDID W6 */
#define AI2C_REG_I2C_X7_UDID_W5            (0x00A0)   /*!< Offset to reg
                                                        UDID W5 */
#define AI2C_REG_I2C_X7_UDID_W4            (0x00A4)   /*!< Offset to reg
                                                        UDID W4 */
#define AI2C_REG_I2C_X7_UDID_W4_DEFAULT    (0x00000004) /*!< Def value reg
                                                        UDID W4 */
#define AI2C_REG_I2C_X7_UDID_W3            (0x00A8)   /*!< Offset to reg
                                                        UDID W3 */
#define AI2C_REG_I2C_X7_UDID_W2            (0x00AC)   /*!< Offset to reg
                                                        UDID W2 */
#define AI2C_REG_I2C_X7_UDID_W1            (0x00B0)   /*!< Offset to reg
                                                        UDID W1 */
#define AI2C_REG_I2C_X7_UDID_W0            (0x00B4)   /*!< Offset to reg
                                                        UDID W0 */
#define AI2C_REG_I2C_X7_ARPPEC_CFG_STAT    (0x00B8)   /*!< Offset to reg
                                                        ARPPEC Cfg Status */
#define AI2C_REG_I2C_X7_SLV_ARP_INT_ENABLE (0x00BC)   /*!< Offset to reg
                                                        Slave ARP Interrupt
                                                        Enable */
#define AI2C_REG_I2C_X7_SLV_ARP_INT_STATUS (0x00C0)   /*!< Offset to reg
                                                        Slave ARP Interrupt
                                                        Slave ARP Interrupt
                                                        Status */
#define AI2C_REG_I2C_X7_MST_ARP_INT_ENABLE (0x00C4)   /*!< Offset to reg
                                                        Master ARP Interrupt
                                                        Enable */
#define AI2C_REG_I2C_X7_MST_ARP_INT_STATUS (0x00C8)   /*!< Offset to reg
                                                        Master ARP Interrupt
                                                        Status */
/*
** Unused                                  0x00CC - 0x00FC
*/




#endif	/* __ASSEMBLY__ */

/*
  ==============================================================================
  ==============================================================================
  IO (Peripheral Mapping)
  ==============================================================================
  ==============================================================================
*/

#define DICKENS (0x80000000)
#define IO      (0x90000000)

#define UART0_ADDRESS (IO + 0x80000)
#define UART1_ADDRESS (IO + 0x81000)
#define UART2_ADDRESS (IO + 0x82000)
#define UART3_ADDRESS (IO + 0x83000)

#define SCB (IO + 0x96000)

#define MME_POKE (IO + 0x10040000)
#define NCA (IO + 0x10100000)

#define ELM0 (IO + 0x60000)
#define ELM1 (IO + 0x70000)

#define SYSCON  (IO + 0x30000)

#define I2C0_ADDRESS (IO + 0x84000)
#define I2C1_ADDRESS (IO + 0x85000)
#define I2C2_ADDRESS (IO + 0x86000)
#define I2C3_ADDRESS (IO + 0x87000)

#define I2C0	I2C0_ADDRESS
#define I2C1	I2C1_ADDRESS
#define I2C2	I2C2_ADDRESS
#define I2C3	I2C3_ADDRESS

#define GPIO0_ADDRESS (IO + 0x92000)
#define GPIO1_ADDRESS (IO + 0x93000)

#define GPREG        (IO + 0x94000)
#define GPREG_GPDMA  (GPREG + 0x00)
#define GPREG_MAC    (GPREG + 0x04)
#define GPREG_USB    (GPREG + 0x08)
#define GPREG_STATUS (GPREG + 0x0c)

#define GIC_DIST_BASE (DICKENS + 0x1001000)
#define GIC_CPU_BASE  (DICKENS + 0x1002000)

#define SRIO_GPREG (IO+0x10000000+0x147000)

#define APB2_SER0_BASE (IO)
#define APB2_SER3_BASE (IO + 0x30000)
#define NCP_APB2SER_INDIRECT_COMMAND_0      (0x00000000)
#define NCP_APB2SER_INDIRECT_COMMAND_1      (0x00000004)
#define NCP_APB2SER_INDIRECT_READ_DATA_0    (0x00000008)
#define NCP_APB2SER_INDIRECT_READ_DATA_1    (0x0000000c)


/*
  ==============================================================================
  ==============================================================================
  PCI
  ==============================================================================
  ==============================================================================
*/
#ifdef CONFIG_AXXIA_PCI
#define CONFIG_PCI 1
#define CONFIG_PCI_PNP 1                          /* do pci plug-and-play*/
#define CONFIG_CMD_PCI 1
#define CONFIG_PCI_SCAN_SHOW 1

#define ACP_PEI0 1
#define ACP_PEI1 1

#define CONFIG_SYS_PCIE_NR_PORTS 2

#define PCIE0_CONFIG (IO+0x10000000+0x120000)
#define PCIE1_CONFIG (IO+0x10000000+0x130000)

#define CONFIG_SYS_PCIE0_MEMBASE 0xd0000000
#define CONFIG_SYS_PCIE1_MEMBASE 0xf0000000
#define CONFIG_PCIE0_PHY_START   0xc0000000
#define CONFIG_PCIE1_PHY_START   0xe0000000

#define CONFIG_SYS_PCIE_MEMSIZE 0x100000

#define CONFIG_PCIE0_BUS_START 0x80000000
#define CONFIG_PCIE1_BUS_START 0xc0000000

#define CONFIG_SYS_PCIE0_CFGADDR PCIE0_CONFIG
#define CONFIG_SYS_PCIE1_CFGADDR PCIE1_CONFIG
#endif

/*
  ==============================================================================
  ==============================================================================
  USB
  ==============================================================================
  ==============================================================================
*/

/* USB support */
#ifdef CONFIG_AXXIA_USB
#define CONFIG_CMD_USB 1
#define CONFIG_USB_EHCI 1
#define CONFIG_USB_STORAGE 1
#define CONFIG_CMD_USB_STORAGE 1
#define CONFIG_USB_ULPI 1
#define CONFIG_USB_ULPI_VIEWPORT 1
#define CONFIG_CMD_EXT2 1
#define CONFIG_CMD_EXT4 1
#define CONFIG_DOS_PARTITION 1
#define CONFIG_USB_ADDR (IO+0x140000)
#define CONFIG_EHCI_IS_TDI 1
#define CONFIG_CMD_LSI_ULPI 1
#endif

#ifndef __ASSEMBLY__
int usb_phy_init(void);
#endif

/*
  ==============================================================================
  ==============================================================================
  Memory
  ==============================================================================
  ==============================================================================
*/

#define SYSMEM  0x00000000

#ifndef __ASSEMBLY__
int sysmem_init(void);
#endif


#ifdef CONFIG_SPL_BUILD
#ifdef NCR_TRACER
#define NCR_TRACE( format, args... ) do { \
if( 0 != ncr_tracer_is_enabled( ) ) { \
printf( format, ##args ); \
} \
} while( 0 );
#define NCP_COMMENT( format, args... ) do { \
if( 0 != ncr_tracer_is_enabled( ) ) { \
printf( "# " format "\n", ##args ); \
} \
} while( 0 );
#else
#define NCR_TRACE( format, args... )
#define NCP_COMMENT( format, args... )
#endif
#endif


#ifdef CONFIG_SPL_BUILD
#define LSM     0x20000000
#endif

#define CONFIG_NET_RETRY_COUNT 20
#define CONFIG_FIT

#define CONFIG_BOARD_EARLY_INIT_F
#define CONFIG_ARCH_EARLY_INIT_R
#define CONFIG_OF_BOARD_SETUP

#define LDSSCRIPT "board/lsi/axxia-arm/u-boot.lds"

#ifndef __ASSEMBLY__
extern unsigned long spin_loop_release_offset;
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

#define CONFIG_SYS_PROMPT       "=> "
#define CFG_CBSIZE              4096
#define CFG_MAXARGS             64
#define CFG_BARGSIZE            CFG_CBSIZE


#define UART_CLOCK_SPEED	2000000
#define CONFIG_SYS_BAUDRATE_TABLE {4800, 9600, 19200, 38400, 57600, 115200}

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

#define CONFIG_LSI_SSP 1
#define CONFIG_SYS_MAX_FLASH_SECT    1024

#define TIMER0 (IO+0x91000)
#define TIMER1 (IO+0x91020)
#define TIMER2 (IO+0x91040)
#define TIMER3 (IO+0x91060)
#define TIMER4 (IO+0x91080)
#define TIMER5 (IO+0x910a0)	/* Watchdog */
#define TIMER6 (IO+0x910c0)
#define TIMER7 (IO+0x910e0)

/*
  ==============================================================================
  ==============================================================================
  APB (AMBA) Dual Input Timers
  ==============================================================================
  ==============================================================================
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

#define SSP (IO+0x88000)

/* Flash */
#define CONFIG_SYS_NO_FLASH

/* Cache */
#define CONFIG_SYS_CACHELINE_SIZE	64
#define CONFIG_SYS_CACHELINE_SHIFT	6

/* commands to include */
#include <config_cmd_default.h>

#define CONFIG_CMDLINE_EDITING

/* Enabled commands */
#if 0
#define CONFIG_CMD_MMC		/* MMC support                  */
#endif
#define CONFIG_CMD_I2C		/* I2C serial bus support	*/
#define CONFIG_CMD_SPI		/* I2C serial bus support	*/
#define CONFIG_CMD_SF 		/* Serial flash commands        */
#define CONFIG_CMD_SAVEENV

/* Disabled commands */
#undef CONFIG_CMD_NET
#undef CONFIG_CMD_NFS
#undef CONFIG_CMD_FPGA		/* FPGA configuration Support   */
#undef CONFIG_CMD_IMLS		/* List all found images        */

/*
 * Environment setup
 */

#define CONFIG_ENV_OVERWRITE
#define CONFIG_AUTO_COMPLETE 1

/*
 * Miscellaneous configurable options
 */

#define CONFIG_SYS_LONGHELP	/* undef to save memory */
/* #define CONFIG_SYS_HUSH_PARSER */	/* use "hush" command parser */ 
#define CONFIG_SYS_CBSIZE		2048
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
#define CONFIG_SYS_EMIF_PRECALCULATED_TIMING_REGS

/* Defines for SDRAM init */
#ifndef CONFIG_SYS_EMIF_PRECALCULATED_TIMING_REGS
#define CONFIG_SYS_AUTOMATIC_SDRAM_DETECTION
#define CONFIG_SYS_DEFAULT_LPDDR2_TIMINGS
#endif

/*
  ==============================================================================
  ==============================================================================
  Memory Layout

  U-Boot is expected to reside completely in the first 4 Mb of system
  memory.  The SPL uses memory in that range as stack and heap.  Since
  the U-Boot image will be written to system memory at offset 0, 4 Mb
  minus the size of U-Boot (CONFIG_SYS_MONITOR_LEN) is the amount of
  memory available for stack and heap.

  So, the defines below should take the following into account.

  == SPL ==

  This is the reset memory map.  System memory is at 0x20_0000_0000, and is uninitialized when the SPL starts.

  -----------------    0x2000_0000 (LSM)
  - SPL Binary    -
  -               -
  -----------------    CONFIG_SYS_SPL_MALLOC_START
  - Heap          -
  -               -
  -----------------    CONFIG_SYS_SPL_MALLOC_START + CONFIG_SYS_SPL_MALLOC_SIZE
  - Stack         -
  -               -
  -----------------    CONFIG_SPL_STACK (8 Kb Below End of LSM)
  - Parameters A  -
  -               -
  -----------------    4 Kb Below End of LSM
  - Parameters B  -
  -               -
  -----------------    End of LSM


  -----------------    0x4000_0000
  - U-Boot Binary -
  -               -
  -----------------    CONFIG_SYS_MONITOR_LEN
  - Stack         -
  -               -
  -----------------    CONFIG_SYS_INIT_SP_ADDR
  - Heap          -
  -               -
  -----------------    0x0040_0000

  == U-Boot ==

  This is the mission mode memory map.  System memory is at 0.

  -----------------    0x20_2000_0000 (LSM)
  - Unused        -
  -               -
  -----------------    End of LSM


  -----------------    0x0000_0000
  - U-Boot Binary -
  -               -
  -----------------    CONFIG_SYS_MONITOR_LEN
  - Stack         -
  -               -
  -----------------    CONFIG_SYS_INIT_SP_ADDR
  - Heap          -
  -               -
  -----------------    0x0040_0000 - 0x0004_0000
  - Uncached      -
  - 256 Kb        -
  -----------------    0x0040_0000

  A few notes.

  1 - The SPL uses part of LSM as heap and stack while system memory
      is being initialized.  Once system memory has been initialized,
      the SPL heap and stack will be placed in system memory.
  2 - The FEMAC (debug network interface) requires memory for DMA that
      is not cached.  That's the purpose of the last 256 Kb above.

  ==============================================================================
  ==============================================================================
*/

#define CONFIG_SYS_SPL_MALLOC_START	(LSM + SZ_256K - SZ_8K - SZ_4K - SZ_16K)
#define CONFIG_SYS_SPL_MALLOC_SIZE	SZ_16K
#define CONFIG_SPL_STACK		(LSM + (256 * 1024) - (8 * 1024))

#define CONFIG_SYS_MONITOR_LEN          0x200000
#define CONFIG_SYS_INIT_SP_ADDR         (CONFIG_SYS_MONITOR_LEN + 0x80000)
#define CONFIG_SYS_MALLOC_BASE		CONFIG_SYS_INIT_SP_ADDR
#define CONFIG_SYS_MALLOC_LEN \
  (0x400000 - CONFIG_SYS_MALLOC_BASE - 0x40000 - CONFIG_ENV_SIZE)

/*
  ==============================================================================
  ==============================================================================
  MDIO
  ==============================================================================
  ==============================================================================
*/

#define MDIO_CONTROL_RD_DATA (IO+0x90000)
#define MDIO_STATUS_RD_DATA  (IO+0x90004)
#define MDIO_CLK_OFFSET      (IO+0x90008)
#define MDIO_CLK_PERIOD      (IO+0x9000c)

#ifndef __ASSEMBLY__
int mdio_initialize( void );
unsigned short mdio_read( int phy, int reg );
void mdio_write( int phy, int reg, unsigned short value );
#endif

/*
  SPI
*/
#define CONFIG_PL022_SPI
#define CONFIG_SYS_SPI_CLK  spi_get_per_clk()
#define CONFIG_SYS_SPI_BASE (IO+0x88000)

/*
  ==============================================================================
  ==============================================================================
  Network
  ==============================================================================
  ==============================================================================
*/

#ifndef __ASSEMBLY__
extern unsigned char ethernet_address[6];
#endif

#define APP3XXNIC_RX_BASE  (IO+0x120000)
#define APP3XXNIC_TX_BASE  (IO+0x121000)
#define APP3XXNIC_DMA_BASE (IO+0x122000)

/*
  ==============================================================================
  ==============================================================================
  Networking
  ==============================================================================
  ==============================================================================
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
#define PHY_AUXILIARY_MODE3 0x1d
#define PHY_BCM_TEST_REG 0x1f

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

#if 0
#define FALSE 0
#define TRUE (!FALSE)
#endif

#ifndef __ASSEMBLY__
#include <asm/types.h>
#include <asm/u-boot.h>

struct eth_device;

int lsi_femac_eth_init(struct eth_device *, bd_t *);
int lsi_eioa_eth_init(struct eth_device *, bd_t *);

void lsi_femac_eth_halt(struct eth_device *);
void lsi_eioa_eth_halt(struct eth_device *);

int lsi_femac_eth_send(struct eth_device *, void *, int);
int lsi_eioa_eth_send(struct eth_device *, void *, int);

int lsi_femac_eth_rx(struct eth_device *);
int lsi_eioa_eth_rx(struct eth_device *);

void lsi_net_receive_test(struct eth_device *);
void lsi_net_loopback_test(struct eth_device *, int);

void lsi_femac_receive_test(struct eth_device *);
void lsi_eioa_receive_test(struct eth_device *);

void lsi_femac_loopback_test(struct eth_device *, int);
void lsi_eioa_loopback_test(struct eth_device *);

int lsi_femac_write_hwaddr(struct eth_device *);

#if 0
int axxia_eth_init(bd_t *);
void axxia_eth_halt(void);
int axxia_eth_send(volatile void *, int);
int axxia_eth_rx(void);
#endif

void axxia_dump_packet(const char *header, void *packet, int length);
void axxia_dump_packet_rx(const char *header, void *packet, int length);
void axxia_dump_packet_tx(const char *header, void *packet, int length);

int phy_duplex( int );
int phy_link( int );
int phy_set( int, int, int );
int phy_renegotiate( int, int );
int phy_loopback( int, int );
int axxia_phy_reset( int );
int phy_speed( int );
void dump_packet(const char *, void *, int);

#endif /* __ASSEMBLY__ */

/*
  Normally, U-Boot is built in ARM mode.  Uncomment the following to
  build in THUMB mode.
*/

/*#define CONFIG_SYS_THUMB_BUILD*/

/*#define CONFIG_HW_WATCHDOG*/

#ifndef __ASSEMBLY__
int start_watchdog(void);
void stop_watchdog(void);
#endif

/*
  ==============================================================================
  ==============================================================================
  SPL
  ==============================================================================
  ==============================================================================
*/

/* Defines for SPL */
#define CONFIG_SPL_FRAMEWORK
#define CONFIG_SPL_BOARD_INIT
#define CONFIG_SPL_TEXT_BASE		0x20000000
#define CONFIG_SPL_MAX_SIZE		0x19000	/* 100K */
#define CONFIG_SPL_DISPLAY_PRINT

#define CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_SECTOR	0x300 /* address 0x60000 */
#define CONFIG_SYS_MMC_SD_FAT_BOOT_PARTITION	1
#define CONFIG_SYS_U_BOOT_MAX_SIZE_SECTORS	0x200 /* 256 KB */
#define CONFIG_SPL_FAT_LOAD_PAYLOAD_NAME	"u-boot.img"

#define CONFIG_SPL_SPI_BUS		0
#define CONFIG_SPL_SPI_CS		0
#define CONFIG_SF_DEFAULT_SPEED         25000000
#define CONFIG_SF_DEFAULT_MODE          SPI_MODE_0

#define CONFIG_SPL_SPI_LOAD
#define CONFIG_SPL_SPI_SUPPORT
#define CONFIG_SPL_SPI_FLASH_SUPPORT
#define CONFIG_SPL_LIBCOMMON_SUPPORT
#define CONFIG_SPL_LIBDISK_SUPPORT
#define CONFIG_SPL_I2C_SUPPORT
#define CONFIG_SPL_GPIO_SUPPORT
/* #define CONFIG_SPL_MMC_SUPPORT */
#define CONFIG_SPL_FAT_SUPPORT
#define CONFIG_SPL_LIBGENERIC_SUPPORT
#define CONFIG_SPL_SERIAL_SUPPORT
#define CONFIG_SPL_ENV_SUPPORT
#define CONFIG_SPL_CRC32_SUPPORT
#define CONFIG_SPL_LDSCRIPT "board/lsi/axxia-arm/u-boot-spl.lds"

/*
 * 64 bytes before this address should be set aside for u-boot.img's
 * header. That is 80E7FFC0--0x80E80000 should not be used for any
 * other needs.
 */

#ifdef CONFIG_SYSCACHE_ONLY
#define CONFIG_SYS_TEXT_BASE		0x40000000
#else
#define CONFIG_SYS_TEXT_BASE		0x00000000
#endif

#define CONFIG_AXXIA_SERIAL_FLASH_ENV
#define CONFIG_ENV_OFFSET_REDUND         (CONFIG_ENV_OFFSET + CONFIG_ENV_RANGE)
#define CONFIG_ENV_SIZE_REDUND            CONFIG_ENV_SIZE

/*
  ==============================================================================
  ==============================================================================
  Errata
  ==============================================================================
  ==============================================================================
*/

#ifndef __ASSEMBLY__
void axxia_display_clocks(void);
int clocks_init(void);
int voltage_init(void);
int pciesrio_init(unsigned long);
int is_sbb_enabled(int);
int sbb_image_max_length(void *, size_t *);
int sbb_verify_image(void *, void *, size_t, int, int, int);
extern unsigned long pfuse;
void enter_ns(void);
void enter_hyp(void);
void setup_page_tables(void *);
int set_vat_reset(void);
int set_vat_mission(void);
#endif

/*
  Normally, U-Boot is built in ARM mode.  Uncomment the following to
  build in THUMB mode.
*/

/*#define CONFIG_SYS_THUMB_BUILD*/

#ifndef __ASSEMBLY__
#ifdef CONFIG_MEMORY_RETENTION
extern void *retention;
extern unsigned *phyRegs;
#define DDR_PHY_REGS_TAG_SAVE 0x53415645
#define DDR_PHY_REGS_TAG_PROM 0x50524f4d
#define DDR_PHY_REGS_SIZE     128
#endif
#endif

#define CCN_QOS_RNI6_SO_DEFAULT 0x00cc000c

/*
  ==============================================================================
  ==============================================================================
  Include the common Axxia header.
  ==============================================================================
  ==============================================================================
*/

#include <configs/axxia.h>


#endif /* __CONFIGS_AXXIA_ARM_H */
