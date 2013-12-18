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

#define CONFIG_AXXIA_PPC

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
#define CONFIG_AXXIA_PPC
#define CONFIG_476FP 1		/* Specific PPC476FP Support */
#define CONFIG_470   1		/* ... PPC47x family         */
#define CONFIG_4xx   1		/* ... PPC4xx family         */
#define CONFIG_BOOKE 1

#ifndef __ASSEMBLY__

#include <asm/io.h>

/* Debug */
extern int lsi_debug_enable;

#ifdef LSI_DEBUG
#define LSI_DEBUG_ENABLE() {lsi_debug_enable = 1;}
#define LSI_DEBUG_DISABLE() {lsi_debug_enable = 0;}
#define LSI_DEBUG_ENABLED() (1 == lsi_debug_enable)
#define DEBUG_PRINT( format, args... ) do { \
if (0 != lsi_debug_enable) { ;\
printf( "%s:%s:%d - DEBUG - ", __FILE__, __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} ; \
} while( 0 );
#define DEBUG_CODE( code ) { code }
#else  /* LSI_DEBUG */
#define LSI_DEBUG_ENABLE() {}
#define LSI_DEBUG_DISABLE() {}
#define LSI_DEBUG_ENABLED() 0
#define DEBUG_PRINT( format, args... )
#define DEBUG_CODE( code )
#endif /* LSI_DEBUG */

/* Warning */
#ifdef LSI_WARN
#define WARN_PRINT( format, args... ) do { \
printf( "%s:%s:%d - WARN - ", __FILE__, __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#define WARN_CODE( code ) { code }
#else  /* LSI_WARN */
#define WARN_PRINT( format, args... )
#define WARN_CODE( code )
#endif /* LSI_WARN */

/* Error */
#define ERROR_PRINT( format, args... ) do { \
printf( "%s:%s:%d - ERROR - ", __FILE__, __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#define ERROR_CODE( code ) { code }

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


#ifdef CONFIG_AXXIA_PCI
#define CONFIG_PCI 1
#define CONFIG_PCI_PNP 1                          /* do pci plug-and-play*/
#define CONFIG_CMD_PCI 1
#define CONFIG_PCI_SCAN_SHOW 1
#endif

#define ACP_PEI0 1
#define ACP_PEI1 1

#ifdef CONFIG_AXXIA_25xx
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

#ifdef CONFIG_AXXIA_25xx
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
#define CONFIG_CMD_EXT4 1	
#define CONFIG_DOS_PARTITION 1
#define CONFIG_USB_ADDR (IO+0xA0000)
#define CONFIG_EHCI_IS_TDI 1
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

#define CONFIG_SYS_MALLOC_BASE (0x280000)
#define CONFIG_SYS_MALLOC_SIZE (0x400000 - CONFIG_SYS_MALLOC_BASE)
#define CONFIG_SYS_STACK_BASE  (CONFIG_SYS_MALLOC_BASE - (ACP_MAX_CORES * 0x400))
#define CONFIG_SYS_MALLOC_LEN (CONFIG_SYS_MALLOC_SIZE)

#ifdef CONFIG_SPL_BUILD
#ifdef CONFIG_AXXIA_25xx
#define CFG_INIT_RAM_ADDR   0xf0a24000
#else
#define CFG_INIT_RAM_ADDR   0xf0a1fc00
#endif
#else
/* Early stack for each core. */
#define CFG_INIT_RAM_ADDR0  (CONFIG_SYS_STACK_BASE)
#define CFG_INIT_RAM_ADDR1  (CONFIG_SYS_STACK_BASE + 0x400)
#define CFG_INIT_RAM_ADDR2  (CONFIG_SYS_STACK_BASE + 0x800)
#define CFG_INIT_RAM_ADDR3  (CONFIG_SYS_STACK_BASE + 0xc00)
#endif

/*
  ======================================================================
  ======================================================================
  NAND
  ======================================================================
  ======================================================================
*/

#define CONFIG_LSI_NAND

#ifndef __ASSEMBLY__
#include <linux/mtd/mtd.h>
#include <linux/mtd/nand.h>
typedef enum {
	LSI_NAND_ECC_MODE_OFF,
	LSI_NAND_ECC_MODE_1BIT,
	LSI_NAND_ECC_MODE_4BIT,
	LSI_NAND_ECC_MODE_8BIT,
	LSI_NAND_ECC_MODE_12BIT
} lsi_ecc_mode_t;

const char *get_ecc_mode_string(lsi_ecc_mode_t);
lsi_ecc_mode_t get_ecc_mode(void);
void set_ecc_mode(lsi_ecc_mode_t);

int lsi_nand_set_config(struct mtd_info *, struct nand_chip *);
void set_correct_cecc(int);
void set_display_cecc(int);
void set_display_ucecc(int);
#endif /* __ASSEMBLY__ */

#define EP501_NAND_DATA_REG         0x0000
#define EP501_NAND_CMD_REG          0x8000
#define EP501_NAND_INDEX_REG        0x8004
#define EP501_NAND_STATUS0_REG      0x8008
#define EP501_NAND_STATUS1_REG      0x800C
#define EP501_NAND_ID0_REG          0x8010
#define EP501_NAND_ID1_REG          0x8014
#define EP501_NAND_ID2_REG          0x8018
#define EP501_NAND_ID3_REG          0x801C
#define EP501_NAND_ID4_REG          0x8020
#define EP501_NAND_ID5_REG          0x8024
#define EP501_NAND_ID6_REG          0x8028
#define EP501_NAND_ID7_REG          0x802C
#define EP501_NAND_INTR_EN_REG      0x8030
#define EP501_NAND_INTR_STATUS_REG  0x8034
#define EP501_NAND_INTR_REG         0x8038
#define EP501_NAND_ECC_ADDR_LOG_REG 0x803C
#define EP501_NAND_ECC_VAL_REG      0x8040
#define EP501_NAND_ECC_INJECT_REG   0x8044
#define EP501_NAND_EXT_INDEX_REG    0x8048
#define EP501_NAND_TIMING0_REG      0x804C
#define EP501_NAND_TIMING1_REG      0x8050
#define EP501_NAND_CONFIG_REG       0x8054
#define EP501_NAND_PECC_REG         0x8058

#define EP501G1_NAND_DATA_REG         0x0000
#define EP501G1_NAND_CMD_REG          0x8000
#define EP501G1_NAND_INDEX_REG        0x8004
#define EP501G1_NAND_STATUS0_REG      0x8008
#define EP501G1_NAND_ID0_REG          0x8010
#define EP501G1_NAND_ID2_REG          0x8018
#define EP501G1_NAND_ID4_REG          0x8020
#define EP501G1_NAND_ID6_REG          0x8028
#define EP501G1_NAND_INTR_EN_REG      0x8030
#define EP501G1_NAND_INTR_STATUS_REG  0x8034
#define EP501G1_NAND_INTR_REG         0x8038
#define EP501G1_NAND_EXT_INDEX_REG    0x8048
#define EP501G1_NAND_TIMING0_REG      0x804C
#define EP501G1_NAND_TIMING1_REG      0x8050
#define EP501G1_NAND_CONFIG_REG       0x8054
#define EP501G1_NAND_1BIT_ECC0_STATUS 0x8058
#define EP501G1_NAND_1BIT_ECC1_STATUS 0x805c
#define EP501G1_NAND_1BIT_ECC2_STATUS 0x8060
#define EP501G1_NAND_1BIT_ECC3_STATUS 0x8064
#define EP501G1_NAND_1BIT_ECC4_STATUS 0x8068
#define EP501G1_NAND_1BIT_ECC5_STATUS 0x806c
#define EP501G1_NAND_1BIT_ECC6_STATUS 0x8070
#define EP501G1_NAND_1BIT_ECC7_STATUS 0x8074
#define EP501G1_NAND_BCH_STATUS       0x807c
#define EP501G1_NAND_SYN_R12_S0       0x8080
#define EP501G1_NAND_SYN_R34_S0       0x8084
#define EP501G1_NAND_SYN_R56_S0       0x8088
#define EP501G1_NAND_SYN_R78_S0       0x808c
#define EP501G1_NAND_SYN_R12_S1       0x8090
#define EP501G1_NAND_SYN_R34_S1       0x8094
#define EP501G1_NAND_SYN_R56_S1       0x8098
#define EP501G1_NAND_SYN_R78_S1       0x809c
#define EP501G1_NAND_SYN_R12_S2       0x80a0
#define EP501G1_NAND_SYN_R34_S2       0x80a4
#define EP501G1_NAND_SYN_R56_S2       0x80a8
#define EP501G1_NAND_SYN_R78_S2       0x80ac
#define EP501G1_NAND_SYN_R12_S3       0x80b0
#define EP501G1_NAND_SYN_R34_S3       0x80b4
#define EP501G1_NAND_SYN_R56_S3       0x80b8
#define EP501G1_NAND_SYN_R78_S3       0x80bc
#define EP501G1_NAND_SYN_R12_S4       0x80c0
#define EP501G1_NAND_SYN_R34_S4       0x80c4
#define EP501G1_NAND_SYN_R56_S4       0x80c8
#define EP501G1_NAND_SYN_R78_S4       0x80cc
#define EP501G1_NAND_SYN_R12_S5       0x80d0
#define EP501G1_NAND_SYN_R34_S5       0x80d4
#define EP501G1_NAND_SYN_R56_S5       0x80d8
#define EP501G1_NAND_SYN_R78_S5       0x80dc
#define EP501G1_NAND_SYN_R12_S6       0x80e0
#define EP501G1_NAND_SYN_R34_S6       0x80e4
#define EP501G1_NAND_SYN_R56_S6       0x80e8
#define EP501G1_NAND_SYN_R78_S6       0x80ec
#define EP501G1_NAND_SYN_R12_S7       0x80f0
#define EP501G1_NAND_SYN_R34_S7       0x80f4
#define EP501G1_NAND_SYN_R56_S7       0x80f8
#define EP501G1_NAND_SYN_R78_S7       0x80fc

#define EP501G3_NAND_DATA_REG         0x0000
#define EP501G3_NAND_CMD_REG          0x8000
#define EP501G3_NAND_INDEX_REG        0x8004
#define EP501G3_NAND_STATUS0_REG      0x8008
#define EP501G3_NAND_ID0_REG          0x8010
#define EP501G3_NAND_ID2_REG          0x8018
#define EP501G3_NAND_ID4_REG          0x8020
#define EP501G3_NAND_ID6_REG          0x8028
#define EP501G3_NAND_INTR_EN_REG      0x8030
#define EP501G3_NAND_INTR_STATUS_REG  0x8034
#define EP501G3_NAND_INTR_REG         0x8038
#define EP501G3_NAND_EXT_INDEX_REG    0x8048
#define EP501G3_NAND_TIMING0_REG      0x804C
#define EP501G3_NAND_TIMING1_REG      0x8050
#define EP501G3_NAND_CONFIG_REG       0x8054
#define EP501G3_NAND_TIMING2_REG      0x805c
#define EP501G3_NAND_BCH_STATUS       0x807c
#define EP501G3_NAND_SYN_R12_S0       0x8080
#define EP501G3_NAND_SYN_R34_S0       0x8084
#define EP501G3_NAND_SYN_R56_S0       0x8088
#define EP501G3_NAND_SYN_R78_S0       0x808c
#define EP501G3_NAND_SYN_R12_S1       0x8090
#define EP501G3_NAND_SYN_R34_S1       0x8094
#define EP501G3_NAND_SYN_R56_S1       0x8098
#define EP501G3_NAND_SYN_R78_S1       0x809c
#define EP501G3_NAND_SYN_R12_S2       0x80a0
#define EP501G3_NAND_SYN_R34_S2       0x80a4
#define EP501G3_NAND_SYN_R56_S2       0x80a8
#define EP501G3_NAND_SYN_R78_S2       0x80ac
#define EP501G3_NAND_SYN_R12_S3       0x80b0
#define EP501G3_NAND_SYN_R34_S3       0x80b4
#define EP501G3_NAND_SYN_R56_S3       0x80b8
#define EP501G3_NAND_SYN_R78_S3       0x80bc
#define EP501G3_NAND_SYN_R12_S4       0x80c0
#define EP501G3_NAND_SYN_R34_S4       0x80c4
#define EP501G3_NAND_SYN_R56_S4       0x80c8
#define EP501G3_NAND_SYN_R78_S4       0x80cc
#define EP501G3_NAND_SYN_R12_S5       0x80d0
#define EP501G3_NAND_SYN_R34_S5       0x80d4
#define EP501G3_NAND_SYN_R56_S5       0x80d8
#define EP501G3_NAND_SYN_R78_S5       0x80dc
#define EP501G3_NAND_SYN_R12_S6       0x80e0
#define EP501G3_NAND_SYN_R34_S6       0x80e4
#define EP501G3_NAND_SYN_R56_S6       0x80e8
#define EP501G3_NAND_SYN_R78_S6       0x80ec
#define EP501G3_NAND_SYN_R12_S7       0x80f0
#define EP501G3_NAND_SYN_R34_S7       0x80f4
#define EP501G3_NAND_SYN_R56_S7       0x80f8
#define EP501G3_NAND_SYN_R78_S7       0x80fc
#define EP501G3_NAND_SYN_R12_S8       0x8100
#define EP501G3_NAND_SYN_R34_S8       0x8104
#define EP501G3_NAND_SYN_R56_S8       0x8108
#define EP501G3_NAND_SYN_R78_S8       0x810c
#define EP501G3_NAND_SYN_R12_S9       0x8110
#define EP501G3_NAND_SYN_R34_S9       0x8114
#define EP501G3_NAND_SYN_R56_S9       0x8118
#define EP501G3_NAND_SYN_R78_S9       0x811c
#define EP501G3_NAND_SYN_R12_S10      0x8120
#define EP501G3_NAND_SYN_R34_S10      0x8124
#define EP501G3_NAND_SYN_R56_S10      0x8128
#define EP501G3_NAND_SYN_R78_S10      0x812c
#define EP501G3_NAND_SYN_R12_S11      0x8130
#define EP501G3_NAND_SYN_R34_S11      0x8134
#define EP501G3_NAND_SYN_R56_S11      0x8138
#define EP501G3_NAND_SYN_R78_S11      0x813c
#define EP501G3_NAND_SYN_R12_S12      0x8140
#define EP501G3_NAND_SYN_R34_S12      0x8144
#define EP501G3_NAND_SYN_R56_S12      0x8148
#define EP501G3_NAND_SYN_R78_S12      0x814c
#define EP501G3_NAND_SYN_R12_S13      0x8150
#define EP501G3_NAND_SYN_R34_S13      0x8154
#define EP501G3_NAND_SYN_R56_S13      0x8158
#define EP501G3_NAND_SYN_R78_S13      0x815c
#define EP501G3_NAND_SYN_R12_S14      0x8160
#define EP501G3_NAND_SYN_R34_S14      0x8164
#define EP501G3_NAND_SYN_R56_S14      0x8168
#define EP501G3_NAND_SYN_R78_S14      0x816c
#define EP501G3_NAND_SYN_R12_S15      0x8170
#define EP501G3_NAND_SYN_R34_S15      0x8174
#define EP501G3_NAND_SYN_R56_S15      0x8178
#define EP501G3_NAND_SYN_R78_S15      0x817c

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
#ifdef CONFIG_AXXIA_PPC
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
#else
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
#endif
  } __attribute__ ( ( packed ) ) bits;
} __attribute__ ( ( packed ) ) phy_control_t;

/* -- status -- */

#define PHY_STATUS 0x01

typedef union {
  unsigned short raw;

  struct {
#ifdef CONFIG_AXXIA_PPC
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
#endif
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
#ifdef CONFIG_AXXIA_PPC
    unsigned short id       : 6;
    unsigned short model    : 6;
    unsigned short revision : 4;
#else
    unsigned short revision : 4;
    unsigned short model    : 6;
    unsigned short id       : 6;
#endif
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

int phy_duplex( int );
int phy_link( int );
int phy_renegotiate( int, int );
int phy_speed( int );
void dump_packet(const char *, void *, int);

#endif /* __ASSEMBLY__ */

#define CONFIG_SYS_PKTALIGN 128
#define ARCH_DMA_MINALIGN 128

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
#ifndef CONFIG_SPL_BUILD
#define CONFIG_JFFS2_NAND
#define CONFIG_JFFS2_CMDLINE
#define CONFIG_CMD_SETGETDCR
#define CONFIG_CMD_JFFS2
#define CONFIG_CMD_ELF
#endif

/*
  ======================================================================
  ======================================================================
  NAND
  ======================================================================
  ======================================================================
*/

/*
  ======================================================================
  ======================================================================
  I2C
  ======================================================================
  ======================================================================
*/
#define CONFIG_AXXIA_ACP_I2C
#define CONFIG_HARD_I2C         /* Hardware I2C */
#define CONFIG_CMD_I2C
#define CONFIG_SYS_I2C_MULTI_EEPROMS
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN 1
#define CONFIG_CMD_EEPROM
#if defined(CONFIG_AXXIA_25xx)
#define CONFIG_I2C_MULTI_BUS
#define CONFIG_SYS_MAX_I2C_BUS 2
#endif

#ifdef CONFIG_AXXIA_25xx
#define I2C0 (IO + 0x27000)
#define I2C1 (IO + 0x28000)
#else
#define I2C0 (IO + 0x3000)
#endif

#define I2C_MTC         0x00
#define I2C_MRC         0x04
#define I2C_MTS         0x08
#define I2C_MRS         0x0c
#define I2C_MIE         0x10
#define I2C_MIC         0x14
#define I2C_MIS         0x18
#define I2C_MCC         0x1c
#define I2C_MSTSHC      0x20
#define I2C_MSPSHC      0x24
#define I2C_MDSHC       0x28
#define I2C_MBPM        0x2c
#define I2C_MSLVADDR    0x30
#define I2C_TXD0        0x34
#define I2C_TXD1        0x38
#define I2C_RXD0        0x3c
#define I2C_RXD1        0x40

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
#define CONFIG_OF_BOARD_SETUP
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
#if defined(CONFIG_AXXIA_344X)
#define ACP_NR_CORES 4
#elif defined(CONFIG_AXXIA_342X) || defined(CONFIG_AXXIA_25xx)
#define ACP_NR_CORES 2
#else
#define ACP_NR_CORES 1
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

int acp_spintable_init(int, int);
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
	ACP_OS_USB, ACP_OS_PLX, ACP_OS_SBB, ACP_OS_SSP, ACP_OS_I2C,
	ACP_OS_FDT
} acp_osg_group_res_t;

unsigned long long acp_osg_group_get_res(int, acp_osg_group_res_t);
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

#define ACP_NAND_4BIT_ECC

/*
  By default, the U-Boot environment is stored in NAND for all targets
  except AXM2500.  To switch to serial flash, defined
  CONFIG_LIS_SERIAL_FLASH_ENV.
*/

#ifdef CONFIG_AXXIA_25xx
#define CONFIG_AXXIA_SERIAL_FLASH_ENV
#endif

#ifndef CONFIG_AXXIA_SERIAL_FLASH_ENV
#define CONFIG_LSI_NAND_ENV
#endif

/*
  ======================================================================
  ======================================================================
  Network
  ======================================================================
  ======================================================================
*/

#define APP3XXNIC_RX_BASE  (IO+0x80000)
#define APP3XXNIC_TX_BASE  (IO+0x81000)
#define APP3XXNIC_DMA_BASE (IO+0x82000)

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
/* #define NCP_COMMENT( format, args... ) */
#define NCP_COMMENT( format, args... ) printf( "# " format "\n", ##args ); /* TEMP DEBUG */
#endif
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

#ifdef CONFIG_AXXIA_25xx
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

#define CANNED_PHY_REGS_OFFSET  (PARAMETERS_OFFSET + 512)
#define CANNED_PHY_REGS_ADDRESS (LCM + CANNED_PHY_REGS_OFFSET)

#define CANNED_PHY_REGS_TAG_SAVE 0x53415645
#define CANNED_PHY_REGS_TAG_PROM 0x50524f4d





/*
  ----------------------------------------------------------------------
  ACP2500 sysmem init compile time options 
 */

/*
 * NCP_SM_PHY_REG_RESTORE: 
 *   if defined, enable sysmem PHY register save/restore capability
 */
/* #define NCP_SM_PHY_REG_RESTORE  */

/* 
 * NCP_SM_PHY_REG_DUMP: 
 *   if defined, enable dumping of sysmem PHY registers 
 *   upon completion of the sysmem init sequence
 */
#define NCP_SM_PHY_REG_DUMP

/* 
 * NCP_SM_WRLVL_DUP
 *   if defined, will only run the write leveling training
 *   on rank0, and will duplicate the write delays for rank1.
 *   This is a workaround for a problem with the original 
 *   Odessa board design. 
 */
#define NCP_SM_WRLVL_DUP



/*
  ----------------------------------------------------------------------
  ACP2500 sysmem init compile time options 
 */

/*
 * NCP_SM_PHY_REG_RESTORE: 
 *   if defined, enable sysmem PHY register save/restore capability
 */
/* #define NCP_SM_PHY_REG_RESTORE  */

/* 
 * NCP_SM_PHY_REG_DUMP: 
 *   if defined, enable dumping of sysmem PHY registers 
 *   upon completion of the sysmem init sequence
 */
#define NCP_SM_PHY_REG_DUMP

/* 
 * NCP_SM_WRLVL_DUP
 *   if defined, will only run the write leveling training
 *   on rank0, and will duplicate the write delays for rank1.
 *   This is a workaround for a problem with the original 
 *   Odessa board design. 
 */
#define NCP_SM_WRLVL_DUP



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

#if defined(CONFIG_AXXIA_25xx)
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

#if defined(CONFIG_AXXIA_25xx)
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

#if defined(CONFIG_AXXIA_25xx)
#define SSP (IO+0x22000)
#else
#define SSP (IO+0x2000)
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

#if !defined(CONFIG_AXXIA_25xx)
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

#if defined(CONFIG_AXXIA_25xx)
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

#if defined(CONFIG_AXXIA_25xx)
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

#if defined(CONFIG_AXXIA_25xx)
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

#if defined(CONFIG_AXXIA_25xx)
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

#if defined(NCR_TRACER)
#undef CONFIG_AXXIA_NAND
#undef CONFIG_LSI_NAND_ENV
#undef CONFIG_AXXIA_SERIAL_FLASH
#undef CONFIG_AXXIA_SERIAL_FLASH_ENV
#define CONFIG_SYS_NO_FLASH
#define CONFIG_CMD_ENV
#define CONFIG_ENV_IS_IN_NVRAM
#define CONFIG_ENV_SIZE           (64 * 1024)
#define CONFIG_ENV_ADDR           ((4 * 1024 * 1024) - CONFIG_ENV_SIZE)
#define CONFIG_SYS_MAX_FLASH_SECT 1024
#define CONFIG_SYS_MAX_FLASH_BANKS 4
#endif

#if defined(CONFIG_AXXIA_NAND)
#define CONFIG_FLASH_CFI_DRIVER      1
#define CONFIG_SYS_FLASH_CFI         1
#define CONFIG_CMD_NAND
#define CONFIG_SYS_MAX_FLASH_SECT    1024
#define CONFIG_SYS_MAX_FLASH_BANKS   4
#else
#define CONFIG_SYS_NO_FLASH
#endif

#if defined(CONFIG_LSI_NAND_ENV)
#if !defined(CONFIG_AXXIA_NAND)
#error "CONFIG_AXXIA_NAND must be defined for CONFIG_LSI_NAND_ENV"
#endif
#define CONFIG_CMD_ENV
#define CONFIG_ENV_IS_IN_NAND        1
#define CONFIG_REDUNDAND_ENVIRONMENT 1
#define CONFIG_ENV_OFFSET            (512*1024)
#define CONFIG_ENV_SIZE              (128*1024)
#define CONFIG_ENV_RANGE             (512*1024)
#define CONFIG_ENV_OFFSET_REDUND     (CONFIG_ENV_OFFSET + CONFIG_ENV_RANGE)
#define CONFIG_ENV_SIZE_REDUND       CONFIG_ENV_SIZE
#elif defined(CONFIG_AXXIA_SERIAL_FLASH_ENV)
#if !defined(CONFIG_AXXIA_SERIAL_FLASH)
#error "CONFIG_AXXIA_SERIAL_FLASH must be defined for CONFIG_AXXIA_SERIAL_FLASH_ENV"
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
#ifdef CONFIG_AXXIA_25xx
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
int lsi_eioa_eth_init(struct eth_device *, bd_t *);

void lsi_femac_eth_halt(struct eth_device *);
void lsi_eioa_eth_halt(struct eth_device *);

int lsi_femac_eth_send(struct eth_device *, volatile void *, int);
int lsi_eioa_eth_send(struct eth_device *, volatile void *, int);

int lsi_femac_eth_rx(struct eth_device *);
int lsi_eioa_eth_rx(struct eth_device *);

void lsi_net_receive_test(struct eth_device *);
void lsi_net_loopback_test(struct eth_device *);

void lsi_femac_receive_test(struct eth_device *);
void lsi_eioa_receive_test(struct eth_device *);
void lsi_femac_loopback_test(struct eth_device *);
void lsi_eioa_loopback_test(struct eth_device *);

int lsi_femac_write_hwaddr(struct eth_device *);

#endif /* __ASSEMBLY__ */

/*
  ======================================================================
  ======================================================================
  25xx Bring Up Test...
  ======================================================================
  ======================================================================
*/

#ifdef CONFIG_AXXIA_25xx

/*#define SM_PLL_533_MHZ*/

/*#define RESET_INSTEAD_OF_IPI*/

/*#define DISABLE_RESET*/

/*#define PPCPLL_STEP_TEST*/

#endif	/* CONFIG_AXXIA_25xx */

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
#elif defined(CONFIG_AXXIA_25xx)
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
  Boot From NAND
*/

#define CONFIG_SPL_NAND_SUPPORT
/*#define CONFIG_SPL_NAND_SIMPLE*/
/*#define CONFIG_SPL_NAND_DRIVERS*/
/*#define CONFIG_SPL_NAND_LOAD*/
#define CONFIG_SPL_NAND_ECC
#define CONFIG_SPL_NAND_BASE

#define CONFIG_SYS_NAND_U_BOOT_OFFS 0x180000
#define CONFIG_SYS_NAND_U_BOOT_START 0
#define CONFIG_SYS_NAND_U_BOOT_SIZE 0x200000
#define CONFIG_SYS_NAND_U_BOOT_DST  0x400000
#define CONFIG_SYS_NAND_PAGE_SIZE   0x40000
#define CONFIG_SYS_NAND_BLOCK_SIZE  0x40000

#define CONFIG_SYS_NAND_ECCSIZE 512
#define CONFIG_SYS_NAND_ECCBYTES 32
#define CONFIG_SYS_NAND_ECCPOS { 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63}
#define CONFIG_SYS_NAND_PAGE_COUNT 32
#define CONFIG_SYS_NAND_BAD_BLOCK_POS 0
#define CONFIG_SYS_NAND_OOBSIZE 16
#define CFG_NAND_BASE              (IO+0x40000)
#define CONFIG_SYS_NAND_BASE       (IO+0x40000)
#define CONFIG_SYS_NAND_HW_ECC_OOBFIRST

/*
  ----------------------------------------------------------------------
  Include the ACP common header.
*/

#include <configs/axxia.h>

#endif	/* __CONFIGS_AXXIA_PPC_H */
