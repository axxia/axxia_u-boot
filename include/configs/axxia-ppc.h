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

#ifndef __CONFIGS_AXXIA_PPC_H
#define __CONFIGS_AXXIA_PPC_H

#define CONFIG_SYS_LDSCRIPT "board/lsi/axxia-ppc/u-boot.lds"
#define CONFIG_SYS_TEXT_BASE 0x00004000

/*
  ==============================================================================
  Even though the hardware type should be defined in acp.h, the U-Boot config.mk
  file only looks here (for the 3rd stage) or in acp2.h (for the 2nd stage).
  So, the hardware type is defined here.
*/

#define CONFIG_ACP3 1
#define CONFIG_ACP   1		/* LSI ACP Board             */
#define CONFIG_476FP 1		/* Specific PPC476FP Support */
#define CONFIG_470   1		/* ... PPC47x family         */
#define CONFIG_4xx   1		/* ... PPC4xx family         */
#define CONFIG_BOOKE 1

#ifdef CONFIG_AXXIA_PCI
#define CONFIG_PCI 1
#define CONFIG_PCI_PNP 1                          /* do pci plug-and-play*/
#define CONFIG_CMD_PCI 1
#define CONFIG_PCI_SCAN_SHOW 1
#endif

#define ACP_PEI0 1
#define ACP_PEI1 1

#ifdef ACP_25xx
#define CONFIG_SYS_PCIE_NR_PORTS 2
#else
#define ACP_PEI2 1
#define CONFIG_SYS_PCIE_NR_PORTS 3
#endif

/* Board-specific PCI */
#define CONFIG_SYS_PCI_TARGET_INIT                 /* let board init pci target    */

#if defined(ACP_PEI0) && defined(ACP_PEI1) && defined(ACP_PEI2)
#define CONFIG_SYS_PCIE0_MEMBASE 0x30000000
#define CONFIG_SYS_PCIE1_MEMBASE 0x50000000
#define CONFIG_SYS_PCIE2_MEMBASE 0x70000000
#define CONFIG_PCIE0_PHY_START 0x20000000
#define CONFIG_PCIE1_PHY_START 0x40000000
#define CONFIG_PCIE2_PHY_START 0x60000000
#elif defined(ACP_PEI0) && defined(ACP_PEI1)
#define CONFIG_SYS_PCIE0_MEMBASE 0x30000000
#define CONFIG_SYS_PCIE1_MEMBASE 0x50000000
#define CONFIG_SYS_PCIE2_MEMBASE 0x0
#define CONFIG_PCIE0_PHY_START 0x20000000
#define CONFIG_PCIE1_PHY_START 0x40000000
#define CONFIG_PCIE2_PHY_START 0x0
#elif defined(ACP_PEI0)
#define CONFIG_SYS_PCIE0_MEMBASE 0x78000000
#define CONFIG_SYS_PCIE1_MEMBASE 0x0
#define CONFIG_SYS_PCIE2_MEMBASE 0x0
#define CONFIG_PCIE0_PHY_START 0x40000000
#define CONFIG_PCIE1_PHY_START 0x0
#define CONFIG_PCIE2_PHY_START 0x0
#endif

#define CONFIG_SYS_PCIE_MEMSIZE 0x100000

#define CONFIG_PCIE0_BUS_START 0xA0000000
#define CONFIG_PCIE1_BUS_START 0xB0000000
#define CONFIG_PCIE2_BUS_START 0xC0000000

#define CONFIG_SYS_PCIE0_CFGADDR PCIE0_CONFIG
#define CONFIG_SYS_PCIE1_CFGADDR PCIE1_CONFIG
#define CONFIG_SYS_PCIE2_CFGADDR PCIE2_CONFIG

#ifdef ACP_25xx
#define CONFIG_SYS_PCIE_NR_PORTS 2
#else
#define CONFIG_SYS_PCIE_NR_PORTS 3
#endif

#if !defined(USE_HOSTCC)
/* USB support */
#ifdef CONFIG_AXXIA_USB
#define CONFIG_CMD_USB 1
#define CONFIG_USB_EHCI 1
#define CONFIG_USB_STORAGE 1
#define CONFIG_CMD_USB_STORAGE 1
#define CONFIG_USB_ULPI 1
#define CONFIG_USB_ULPI_VIEWPORT 1
#define CONFIG_CMD_FAT 1
#define CONFIG_CMD_EXT2 1
#define CONFIG_DOS_PARTITION 1
#define CONFIG_SYS_PPC4XX_USB_ADDR (IO+0xA0000)
#define CONFIG_EHCI_IS_TDI 1
#define CONFIG_LSI_USB 1
#endif
#endif

/*
  ----------------------------------------------------------------------
*/

#define CONFIG_SMP
#define CFG_PROMPT		"ACP3=> "
#define CONFIG_SYS_PROMPT	"ACP3=> "
#define CFG_CBSIZE		1024
#define CONFIG_SYS_CBSIZE	1024
#define CFG_PBSIZE		(CFG_CBSIZE+sizeof(CFG_PROMPT)+16)
#define CONFIG_SYS_PBSIZE	(CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16)
#define CFG_MAXARGS		64
#define CONFIG_SYS_MAXARGS	64
#define CFG_BARGSIZE		CFG_CBSIZE
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE

#if defined(CONFIG_SPL_BUILD) && defined(CONFIG_LSI_TEST)
#error "CONFIG_LSI_TEST IS DEFINED!!!"
#endif

/*
  ----------------------------------------------------------------------
  Memory Layout

  U-Boot won't get moved to the top of RAM in this case. There will be
  two RAM segments.  1 Mb at address 0 (U-Boot text) and 3 Mbyte at
  0x100000.

  Note that CONFIG_SYS_MALLOC_BASE is the bottom of the heap, and the
  stack will grow downward from there.
*/

#define CONFIG_SYS_MALLOC_BASE (0x200000)
#ifdef ACP_ISS
#define CONFIG_SYS_MALLOC_SIZE (0x400000 - CONFIG_SYS_MALLOC_BASE - (64 * 1024)))
#else
#define CONFIG_SYS_MALLOC_SIZE (0x400000 - CONFIG_SYS_MALLOC_BASE)
#endif
#define CONFIG_SYS_STACK_BASE  (CONFIG_SYS_MALLOC_BASE)

#define CONFIG_SYS_MALLOC_LEN (CONFIG_SYS_MALLOC_SIZE)

#ifdef CONFIG_SPL_BUILD
#ifdef ACP_25xx
#define CFG_INIT_RAM_ADDR   0xf0a24000
#else
#define CFG_INIT_RAM_ADDR   0xf0a1fc00
#endif
#else
/* Early stack for each core. */
#define CFG_INIT_RAM_ADDR0  (CONFIG_SYS_STACK_BASE - 0x0000)
#define CFG_INIT_RAM_ADDR1  (CONFIG_SYS_STACK_BASE - 0x4000)
#define CFG_INIT_RAM_ADDR2  (CONFIG_SYS_STACK_BASE - 0x8000)
#define CFG_INIT_RAM_ADDR3  (CONFIG_SYS_STACK_BASE - 0xc000)
#endif

/*
  ----------------------------------------------------------------------
  Commands
*/

/*
  ======================================================================
  ======================================================================
  NAND
  ======================================================================
  ======================================================================
*/

#define ACP_NAND_4BIT_ECC
#define CONFIG_JFFS2_NAND
#define CONFIG_JFFS2_CMDLINE
#define CONFIG_CMD_SETGETDCR
#define CONFIG_CMD_JFFS2
#define CONFIG_CMD_ELF

/*
  ======================================================================
  ======================================================================
  NAND
  ======================================================================
  ======================================================================
*/

#define CONFIG_CMD_I2C
#define CONFIG_SYS_I2C_MULTI_EEPROMS
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN 1
#define CONFIG_HARD_I2C		/* Hardware I2C */
#define CONFIG_CMD_EEPROM

/*
  ======================================================================
  ======================================================================
  I2C
  ======================================================================
  ======================================================================
*/

#define I2C_MTC      (IO + 0x3000)
#define I2C_MRC      (IO + 0x3004)
#define I2C_MTS      (IO + 0x3008)
#define I2C_MRS      (IO + 0x300c)
#define I2C_MIE      (IO + 0x3010)
#define I2C_MIC      (IO + 0x3014)
#define I2C_MIS      (IO + 0x3018)
#define I2C_MCC      (IO + 0x301c)
#define I2C_MSTSHC   (IO + 0x3020)
#define I2C_MSPSHC   (IO + 0x3024)
#define I2C_MDSHC    (IO + 0x3028)
#define I2C_MBPM     (IO + 0x302c)
#define I2C_MSLVADDR (IO + 0x3030)
#define I2C_TXD0     (IO + 0x3034)
#define I2C_TXD1     (IO + 0x3038)
#define I2C_RXD0     (IO + 0x303c)
#define I2C_RXD1     (IO + 0x3040)

#define CONFIG_SYS_I2C_SPEED 300000
#define CONFIG_SYS_I2C_SLAVE 0x50

#ifndef __ASSEMBLY__
void i2c_init(int, int);
int i2c_probe(unsigned char);
int i2c_read(unsigned char, unsigned int, int, unsigned char *, int);
int i2c_write(unsigned char, unsigned int, int, unsigned char *, int);
#endif /* __ASSEMBLY__ */

/*
  ======================================================================
  ======================================================================
  Device Tree...
  ======================================================================
  ======================================================================
*/

#ifndef CONFIG_SPL_BUILD
#define CONFIG_OF_LIBFDT
#define CONFIG_FIT
#ifndef __ASSEMBLY__
unsigned long *get_acp_fdt(int);
#endif
#endif	/* CONFIG_SPL_BUILD */

/*
  ======================================================================
  ======================================================================
  SMP/AMP Stuff
  ======================================================================
  ======================================================================
*/

#define ACP_MAX_CORES 4
#if defined(CONFIG_AXXIA_342X) || defined(ACP_25xx)
#define ACP_NR_CORES 2
#define OS_GROUP0_DEFAULT "0xd31:0:0x100"
#else
#define ACP_NR_CORES 4
#define OS_GROUP0_DEFAULT "0xdf1:0:0x100"
#endif
#define OS_MEMORY_DEFAULT 0x100

#ifndef __ASSEMBLY__
#ifndef CONFIG_SPL_BUILD

typedef struct {
	volatile unsigned int lock;
} acp_spinlock_t;

#define ACP_DEFINE_SPINLOCK(lock) acp_spinlock_t lock = { 0 }

static inline unsigned long
__acp_spin_trylock(acp_spinlock_t *lock)
{
	unsigned long tmp;
	unsigned long token;

	token = 1;

	__asm__ __volatile__ ("1:  lwarx    %0,0,%2\n" \
			      "    cmpwi    0,%0,0\n"  \
			      "    bne-     2f\n"      \
			      "    stwcx.   %1,0,%2\n" \
                              "    bne-     1b\n"      \
			      "2:           \n"
			      : "=&r" (tmp)
			      : "r" (token), "r" (&lock->lock)
			      : "cr0", "memory");

	return tmp;
}

static inline void
acp_spin_lock(acp_spinlock_t *lock)
{
	if (0 == __acp_spin_trylock(lock))
		return;

	while (0 != __acp_spin_trylock(lock))
		;
}

static inline void
acp_spin_unlock(acp_spinlock_t *lock)
{
	__asm__ __volatile__ ("lwsync" : : : "memory");
	lock->lock = 0;
}

void acp_lock_stage3(void);
void acp_unlock_stage3(void);

typedef struct {
	unsigned long long entry_address;
	unsigned long long r3_value;
	unsigned long rsvd1_value;
	unsigned long pir_value;
	unsigned long ccr0_value;
	unsigned long ccr1_value;
	unsigned long ccr2_value;
} acp_spintable_t;

extern acp_spintable_t * acp_spintable [ ACP_NR_CORES ];

int acp_spintable_init(int, int, unsigned long);
void acp_spintable_spin( void );
void acp_spintable_jump( unsigned long, unsigned long );

typedef enum {
	ACP_OSG_SPINTABLE_NOTAVAIL,
	ACP_OSG_SPINTABLE_AVAILABLE
} acp_osg_spintable_state_t;

typedef enum {
	ACP_OSG_CORE_STATE_UNKNOWN,
	ACP_OSG_CORE_STATE_ASLEEP,
	ACP_OSG_CORE_STATE_WAITING_FOR_SPINTABLE,
	ACP_OSG_CORE_STATE_SPINNING,
	ACP_OSG_CORE_STATE_RUNNING
} acp_osg_core_state_t;

acp_osg_spintable_state_t acp_osg_get_spintable_state(int);
void acp_osg_set_spintable_state(int, acp_osg_spintable_state_t);

acp_osg_core_state_t acp_osg_get_core_state(int);
void acp_osg_set_core_state(int, acp_osg_core_state_t);

#define ACP_MAX_OS_GROUPS ACP_MAX_CORES

int acp_osg_readenv(void);

typedef enum {
	ACP_OS_BOOT_CORE, ACP_OS_CORES, ACP_OS_BASE, ACP_OS_SIZE,
	ACP_OS_UART0, ACP_OS_UART1, ACP_OS_NAND, ACP_OS_FEMAC,
	ACP_OS_PCIE0, ACP_OS_PCIE1, ACP_OS_PCIE2, ACP_OS_SRIO,
	ACP_OS_USB, ACP_OS_PLX, ACP_OS_SBB, ACP_OS_FDT
} acp_osg_group_res_t;

unsigned long acp_osg_group_get_res(int, acp_osg_group_res_t);
void acp_osg_group_set_res(int, acp_osg_group_res_t, unsigned long);
int acp_osg_get_group(int);
int acp_osg_is_group_boot_core(int);
int acp_osg_is_boot_core(int);
int acp_osg_set_os(int, void (*)(unsigned long, unsigned long, unsigned long,
				 unsigned long, unsigned long),
		   unsigned long, unsigned long, unsigned long, unsigned long,
		   unsigned long);
int acp_osg_jump_to_os(int);
int acp_osg_dump(int);
int acp_osg_get_current(void);
void acp_osg_set_current(int);
int acp_osg_initialize(void);
int acp_osg_map(int);

#define CONFIG_LSI_OSG 1

#endif	/* CONFIG_SPL_BUILD */
#endif	/* __ASSEMBLY__ */

/*
  ======================================================================
  ======================================================================
  OSE
  ======================================================================
  ======================================================================
*/

#ifndef __ASSEMBLY__
extern unsigned long _ose_strings_0;
extern unsigned long _ose_strings_1;
extern unsigned long _ose_strings_2;
extern unsigned long _ose_strings_3;
#define OSE_STRINGS_SIZE 0x400
int ose_init( void );
int ose_add_string( int core, const char * string );
#endif /* __ASSEMBLY */

/*
  ======================================================================
  ======================================================================
  OS Access
  ======================================================================
  ======================================================================
*/

#ifndef __ASSEMBLY__
int os_access_init( void );
void * os_access_get_address( void );
#endif /* __ASSEMBLY */

/*
  ======================================================================
  ======================================================================
  Clocks
  ======================================================================
  ======================================================================
*/

#ifndef __ASSEMBLY__
int acp_clock_update_dt(void);
#endif /* __ASSEMBLY__ */

/*
  ======================================================================
  ======================================================================
  EIOA
  ======================================================================
  ======================================================================
*/

#ifndef __ASSEMBLY__
int eioa_ethernet_configure(void);
#endif /* __ASSEMBLY__ */

/*
  ======================================================================
  ======================================================================
  VxWorks
  ======================================================================
  ======================================================================
*/

#define CONFIG_SYS_VXWORKS_BOOT_ADDR 0x1000
#define CONFIG_SYS_VXWORKS_BOOT_DEVICE "lsiMac(0,0)"

/*
  ======================================================================
  ======================================================================
  Non-Volatile Storage...
  ======================================================================
  ======================================================================
*/

/*
  By default, the 3rd stage always supports NAND flash.  To turn off
  NAND flash support, comment out the following.
*/

#define CONFIG_LSI_NAND
#define ACP_NAND_4BIT_ECC

/*
  By default, the 3rd stage always supports serial flash.  To turn off
  NAND flash support, comment out the following.
*/

#define CONFIG_LSI_SERIAL_FLASH

/*
  By default, the U-Boot environment is stored in NAND for all targets
  except AXM2500.  To switch to serial flash, defined
  CONFIG_LIS_SERIAL_FLASH_ENV.
*/

#ifdef ACP_25xx
#define CONFIG_LSI_SERIAL_FLASH_ENV
#endif

#ifndef CONFIG_LSI_SERIAL_FLASH_ENV
#define CONFIG_LSI_NAND_ENV
#endif

/*
  ======================================================================
  ======================================================================
  Network
  ======================================================================
  ======================================================================
*/

#ifndef CONFIG_SPL_BUILD
#define CONFIG_LSI_NET

#if defined(ACP_ISS) || defined(NCR_TRACER) || defined(ACP2_SYSMEM_TEST)
#undef CONFIG_LSI_NET
#endif

#if defined(CONFIG_LSI_NET)
#define CONFIG_CMD_NET
#define CONFIG_CMD_DHCP
#define APP3XXNIC_RX_BASE  (IO+0x80000)
#define APP3XXNIC_TX_BASE  (IO+0x81000)
#define APP3XXNIC_DMA_BASE (IO+0x82000)
#endif

/*#define CONFIG_LSI_EIOA*/
#endif	/* CONFIG_SPL_BUILD */

/*
  ======================================================================
  ======================================================================
  Task I/O Lite
  ======================================================================
  ======================================================================
*/

#define NCP_SYSMEM_BARRIER()  __asm__ __volatile__(".long 0x7c0004ac")
#define NULL ((void *)0)
#define FALSE 0
#define TRUE (!FALSE)
#define NCP_TASKIO_UBOOT_ENV

/*
  ======================================================================
  ======================================================================
  System Memory Initialization (SPL Only)
  ======================================================================
  ======================================================================
*/

#ifdef CONFIG_SPL_BUILD
#define NCR_TRACE(format, args...) {}
#endif

/*
  ======================================================================
  ======================================================================
  Errata
  ======================================================================
  ======================================================================
*/

#if 0
#define CONFIG_SATA_SIL3114
#define CONFIG_SYS_SATA_MAX_DEVICE 1
#define CONFIG_CMD_SATA
#define CONFIG_DOS_PARTITION
#define CONFIG_CMD_FAT
#define CONFIG_SUPPORT_VFAT
#define CONFIG_CMD_EXT2
#define CONFIG_LIBATA
#endif

#define CONFIG_MTD_DEVICE 1
#define CONFIG_CMD_MTDPARTS 1
#ifndef CONFIG_SPL_BUILD
#define CONFIG_LSI_TEST 1
#endif
#define CONFIG_CMD_DBG 1

#define CFG_LONGHELP
#define CONFIG_SYS_LONGHELP
#define CONFIG_CMD_CACHE
#define CONFIG_CMD_MEMORY
#define CONFIG_CMD_MTEST
#define CFG_MEMTEST_START 0x4000000
#define CONFIG_SYS_MEMTEST_START 0x4000000
#define CFG_MEMTEST_END   0x5000000
#define CONFIG_SYS_MEMTEST_END   0x5000000
#define CONFIG_SYS_ALT_MEMTEST

#define CONFIG_CMD_BDI
#define CONFIG_CMD_LOADB
#define CONFIG_SYS_BOOTM_LEN 0x4000000

#define CONFIG_EXTRA_ENV_SETTINGS \
"bootargs3=root=/dev/issblk3 rw lpj=15990784\0" \
"bootcmd3=bootm c00000\0" \
"osgroup0=0xf1:0x100:0x100\0"

#ifndef __ASSEMBLY__
extern unsigned long _core_copy_beginning;
extern unsigned long _core_copy_end;
extern unsigned long _core_copy_core0;
extern unsigned long _core_copy_core1;
extern unsigned long _core_copy_core2;
extern unsigned long _core_copy_core3;

extern unsigned long __acp_osg_cores;
extern unsigned long __acp_osg_groups;
extern unsigned long __acp_system_section;
#endif

#define CONFIG_CMD_SOURCE 1

#ifndef __ASSEMBLY__
#include <linux/types.h>
#endif

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
  Nuevo Conf Ring Access, see board/lsi/axxia-ppc/ncr.c for the implementation
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
int ncr_read16( unsigned long, unsigned long, unsigned short * );
int ncr_read32( unsigned long, unsigned long, unsigned long * );
int ncr_write(unsigned long, unsigned long, int, void *);
int ncr_write8( unsigned long, unsigned long, unsigned char );
int ncr_write16( unsigned long, unsigned long, unsigned short );
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
  DCR Access, see board/lsi/axxia-ppc/dcr.c for the implementation
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
  Utilities (see board/lsi/axxi-ppc/util.S)
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
#define GPREG_PCI_SRIO_PHY_CTRL (IO+0xc010)
#define GPREG_PHY_CTRL0         (IO+0xc014)
#define GPREG_PHY_CTRL1         (IO+0xc018)
#define GPREG_PHY_CTRL2         (IO+0xc01c)
#define GPREG_PHY_STAT0         (IO+0xc020)
#define GPREG_PHY_STAT1         (IO+0xc024)
#define GPREG_MISC_CTRL         (IO+0xc028)
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
int sbb_desecure_range(int, void *, size_t);

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
#define CONFIG_SYS_MAX_FLASH_SECT    1024
#define CONFIG_SYS_MAX_FLASH_BANKS   4
#else
#define CONFIG_SYS_NO_FLASH
#endif

#if defined(CONFIG_LSI_NAND_ENV)
#if !defined(CONFIG_LSI_NAND)
#error "CONFIG_LSI_NAND must be defined for CONFIG_LSI_NAND_ENV"
#endif
#define CONFIG_CMD_ENV
#define CONFIG_ENV_IS_IN_NAND        1
#define CONFIG_REDUNDAND_ENVIRONMENT 1
#define CONFIG_ENV_OFFSET            (512*1024)
#define CONFIG_ENV_SIZE              (128*1024)
#define CONFIG_ENV_RANGE             (512*1024)
#define CONFIG_ENV_OFFSET_REDUND     (CONFIG_ENV_OFFSET + CONFIG_ENV_RANGE)
#define CONFIG_ENV_SIZE_REDUND       CONFIG_ENV_SIZE
#elif defined(CONFIG_LSI_SERIAL_FLASH_ENV)
#if !defined(CONFIG_LSI_SERIAL_FLASH)
#error "CONFIG_LSI_SERIAL_FLASH must be defined for CONFIG_LSI_SERIAL_FLASH_ENV"
#endif
#define CONFIG_ENV_IS_IN_SERIAL_FLASH
#define CONFIG_REDUNDAND_ENVIRONMENT     1
#define CONFIG_SYS_REDUNDAND_ENVIRONMENT 1
#define CONFIG_ENV_OFFSET                (512*1024)
#define CONFIG_ENV_SIZE                  (128*1024)
#define CONFIG_ENV_RANGE                 (512*1024)
#define CONFIG_ENV_OFFSET_REDUND         (CONFIG_ENV_OFFSET + CONFIG_ENV_RANGE)
#define CONFIG_ENV_SIZE_REDUND            CONFIG_ENV_SIZE
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
  ======================================================================
  ======================================================================
  Clocks
  ======================================================================
  ======================================================================
*/

#ifndef __ASSEMBLY__
#define CLK_REF0 125000000
typedef enum {
	clock_sys, clock_ppc, clock_ddr, clock_peripheral
} acp_clock_t;
int acp_clock_get(acp_clock_t, unsigned long *);
#ifdef ACP_25xx
void axm2500_pll_check_lock(void);
#endif
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

struct eth_device;

extern unsigned char ethernet_address[6];

void eth_getenv_enetaddrg(const char *, unsigned char [6]);

int lsi_femac_eth_init(struct eth_device *, bd_t *);
int acp_eioa_eth_init(struct eth_device *, bd_t *);

void lsi_femac_eth_halt(struct eth_device *);
void acp_eioa_eth_halt(struct eth_device *);

int lsi_femac_eth_send(struct eth_device *, volatile void *, int);
int acp_eioa_eth_send(struct eth_device *, volatile void *, int);

int lsi_femac_eth_recv(struct eth_device *);
int acp_eioa_eth_recv(struct eth_device *);

void lsi_net_receive_test(void);
void lsi_net_loopback_test(void);

void lsi_femac_receive_test(struct eth_device *);
void acp_eioa_receive_test(struct eth_device *);
void lsi_femac_loopback_test(struct eth_device *);
void acp_eioa_loopback_test(struct eth_device *);
#endif /* __ASSEMBLY__ */

/*
  ======================================================================
  ======================================================================
  25xx Bring Up Test...
  ======================================================================
  ======================================================================
*/

#ifdef ACP_25xx

/*#define SM_PLL_533_MHZ*/

/*#define RESET_INSTEAD_OF_IPI*/

/*#define DISABLE_RESET*/

/*#define PPCPLL_STEP_TEST*/

#endif	/* ACP_25xx */

/*
  ======================================================================
  ======================================================================
  Errata
  ======================================================================
  ======================================================================
*/

#define CONFIG_NET_DO_NOT_TRY_ANOTHER

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
#define CONFIG_CMD_MISC         1

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
  ==============================================================================
  ==============================================================================
  SPL
  ==============================================================================
  ==============================================================================
*/

#define CONFIG_SPL
#define CONFIG_SPL_FRAMEWORK
#define CONFIG_SPL_TEXT_BASE		0xf0a00020
#define CONFIG_SPL_MAX_SIZE		0x19000	/* 100K */
#define CONFIG_SPL_STACK		CONFIG_SYS_INIT_SP_ADDR
#define CONFIG_SPL_DISPLAY_PRINT

#define CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_SECTOR	0x300 /* address 0x60000 */
#define CONFIG_SYS_U_BOOT_MAX_SIZE_SECTORS	0x200 /* 256 KB */
#define CONFIG_SYS_MMC_SD_FAT_BOOT_PARTITION	1
#define CONFIG_SPL_FAT_LOAD_PAYLOAD_NAME	"u-boot.img"

#define CONFIG_SPL_LIBCOMMON_SUPPORT
/*#define CONFIG_SPL_LIBDISK_SUPPORT*/
/*#define CONFIG_SPL_I2C_SUPPORT*/
/*#define CONFIG_SPL_MMC_SUPPORT*/
/*#define CONFIG_SPL_FAT_SUPPORT*/
#define CONFIG_SPL_LIBGENERIC_SUPPORT
#define CONFIG_SPL_SERIAL_SUPPORT
#define CONFIG_SPL_LDSCRIPT "board/lsi/axxia-ppc/u-boot-spl.lds"

#define CONFIG_SPL_BSS_START_ADDR	0x00200000
#define CONFIG_SPL_BSS_MAX_SIZE		0x00100000
#define CONFIG_SYS_SPL_MALLOC_START	0x00300000
#define CONFIG_SYS_SPL_MALLOC_SIZE	0x00100000

/*
  ----------------------------------------------------------------------
  Include the ACP common header.
*/

#include <configs/axxia.h>

#endif	/* __CONFIGS_AXXIA_PPC_H */
