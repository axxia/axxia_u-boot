/*
 * (C) Copyright 2008
 * LSI
 * John Jacques (john.jacques@lsi.com)
 *
 * Configuration settings for the LSI APP3K Development board.
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

#ifndef __CONFIG_H
#define __CONFIG_H

#define LSI_ARCH_APP3K

/*
  ======================================================================
  ======================================================================
  Reset Memory Map
  ======================================================================
  ======================================================================
*/

#define CONFIG_RESET_NOR_BASE       0x00000000
#define CONFIG_RESET_DDR2_0_BASE    0X10000000
#define CONFIG_RESET_DDR2_1_BASE    0X20000000
#define CONFIG_RESET_DDR2_2_BASE    0X30000000
#define CONFIG_RESET_DDR2_3_BASE    0X40000000
#define CONFIG_RESET_NOR_ALIAS_BASE 0x50000000
#define CONFIG_RESET_NAND_BASE      0x58000000
#define CONFIG_RESET_ASI_BASE       0x60000000
#define CONFIG_RESET_AEI_BASE       0x68000000
#define CONFIG_RESET_MAC_BASE       0x70000000
#define CONFIG_RESET_USB_BASE       0x78000000
#define CONFIG_RESET_PCI0_BASE      0x80000000
#define CONFIG_RESET_PCI1_BASE      0x90000000
#define CONFIG_RESET_PCI2_BASE      0xa0000000
#define CONFIG_RESET_PCI3_BASE      0xb0000000
#define CONFIG_RESET_APB_BASE       0xc0000000
#define CONFIG_RESET_PMR_BASE       0xc4000000
#define CONFIG_RESET_GPDMA_BASE     0xc8000000
#define CONFIG_RESET_SHMEM_BASE     0xe0000000
#define CONFIG_RESET_VIC_BASE       0xf0000000

/*
  I/O on the APB
*/

#define CONFIG_RESET_GPIO_0_BASE    ( CONFIG_RESET_APB_BASE + 0x00000000 )
#define CONFIG_RESET_GPIO_1_BASE    ( CONFIG_RESET_APB_BASE + 0x00001000 )
#define CONFIG_RESET_UART_BASE      ( CONFIG_RESET_APB_BASE + 0x00002000 )
#define CONFIG_RESET_I2C_BASE       ( CONFIG_RESET_APB_BASE + 0x00003000 )
#define CONFIG_RESET_SPI_BASE       ( CONFIG_RESET_APB_BASE + 0x00004000 )
#define CONFIG_RESET_CT_BASE        ( CONFIG_RESET_APB_BASE + 0x00005000 )
#define CONFIG_RESET_PCI_CFG_BASE   ( CONFIG_RESET_APB_BASE + 0x00006000 )
#define CONFIG_RESET_REMAP_BASE     ( CONFIG_RESET_APB_BASE + 0x00007000 )
#define CONFIG_RESET_DDR2_CFG_BASE  ( CONFIG_RESET_APB_BASE + 0x00008000 )
#define CONFIG_RESET_PL301_CFG_BASE ( CONFIG_RESET_APB_BASE + 0x00009000 )
#define CONFIG_RESET_TDM_CFG_BASE   ( CONFIG_RESET_APB_BASE + 0x0000b000 )

/*
  ======================================================================
  ======================================================================
  Normal Memory Map
  ======================================================================
  ======================================================================
*/

#define CONFIG_NORMAL_DDR2_0_BASE    0X00000000
#define CONFIG_NORMAL_DDR2_1_BASE    0X10000000
#define CONFIG_NORMAL_DDR2_2_BASE    0X20000000
#define CONFIG_NORMAL_DDR2_3_BASE    0X30000000
#define CONFIG_NORMAL_NOR_ALIAS_BASE 0x50000000
#define CONFIG_NORMAL_NAND_BASE      0x58000000
#define CONFIG_NORMAL_ASI_BASE       0x60000000
#define CONFIG_NORMAL_AEI_BASE       0x68000000
#define CONFIG_NORMAL_MAC_BASE       0x70000000
#define CONFIG_NORMAL_USB_BASE       0x78000000
#define CONFIG_NORMAL_PCI0_BASE      0x80000000
#define CONFIG_NORMAL_PCI1_BASE      0x90000000
#define CONFIG_NORMAL_PCI2_BASE      0xa0000000
#define CONFIG_NORMAL_PCI3_BASE      0xb0000000
#define CONFIG_NORMAL_APB_BASE       0xc0000000
#define CONFIG_NORMAL_PMR_BASE       0xc4000000
#define CONFIG_NORMAL_GPDMA_BASE     0xc8000000
#define CONFIG_NORMAL_SHMEM_BASE     0xe0000000
#define CONFIG_NORMAL_VIC_BASE       0xf0000000

/*
  I/O on the APB
*/

#define CONFIG_NORMAL_GPIO_0_BASE    ( CONFIG_NORMAL_APB_BASE + 0x00000000 )
#define CONFIG_NORMAL_GPIO_1_BASE    ( CONFIG_NORMAL_APB_BASE + 0x00001000 )
#define CONFIG_NORMAL_UART_BASE      ( CONFIG_NORMAL_APB_BASE + 0x00002000 )
#define CONFIG_NORMAL_I2C_BASE       ( CONFIG_NORMAL_APB_BASE + 0x00003000 )
#define CONFIG_NORMAL_SPI_BASE       ( CONFIG_NORMAL_APB_BASE + 0x00004000 )
#define CONFIG_NORMAL_CT_BASE        ( CONFIG_NORMAL_APB_BASE + 0x00005000 )
#define CONFIG_NORMAL_PCI_CFG_BASE   ( CONFIG_NORMAL_APB_BASE + 0x00006000 )
#define CONFIG_NORMAL_REMAP_BASE     ( CONFIG_NORMAL_APB_BASE + 0x00007000 )
#define CONFIG_NORMAL_DDR2_CFG_BASE  ( CONFIG_NORMAL_APB_BASE + 0x00008000 )
#define CONFIG_NORMAL_PL301_CFG_BASE ( CONFIG_NORMAL_APB_BASE + 0x00009000 )
#define CONFIG_NORMAL_TDM_CFG_BASE   ( CONFIG_NORMAL_APB_BASE + 0x0000b000 )

/*
  ======================================================================
  ======================================================================
  Registers in the private memory region.
  ======================================================================
  ======================================================================
*/

#define PMR_SCU_BASE                ( CONFIG_NORMAL_PMR_BASE )
#define PMR_SCU_CONTROL             ( PMR_SCU_BASE + 0x000 )
#define PMR_SCU_CONFIGURATION       ( PMR_SCU_BASE + 0x004 )
#define PMR_SCU_STATUS              ( PMR_SCU_BASE + 0x008 )
#define PMR_SCU_INVALIDATE_ALL      ( PMR_SCU_BASE + 0x00c )
#define PMR_SCU_PM_CONTROL          ( PMR_SCU_BASE + 0x010 )
#define PMR_SCU_PM_EVENTS_0         ( PMR_SCU_BASE + 0x014 )
#define PMR_SCU_PM_EVENTS_1         ( PMR_SCU_BASE + 0x018 )
#define PMR_SCU_PM_COUNTER_0        ( PMR_SCU_BASE + 0x01c )
#define PMR_SCU_PM_COUNTER_1        ( PMR_SCU_BASE + 0x020 )
#define PMR_SCU_PM_COUNTER_2        ( PMR_SCU_BASE + 0x024 )
#define PMR_SCU_PM_COUNTER_3        ( PMR_SCU_BASE + 0x028 )
#define PMR_SCU_PM_COUNTER_4        ( PMR_SCU_BASE + 0x02c )
#define PMR_SCU_PM_COUNTER_5        ( PMR_SCU_BASE + 0x030 )
#define PMR_SCU_PM_COUNTER_6        ( PMR_SCU_BASE + 0x034 )
#define PMR_SCU_PM_COUNTER_7        ( PMR_SCU_BASE + 0x038 )

#define PMR_CII_BASE                ( CONFIG_NORMAL_PMR_BASE + 0x100 )
#define PMR_CII_CONTROL             ( PMR_CII_BASE + 0x000 )
#define PMR_CII_PRIORITY_MASK       ( PMR_CII_BASE + 0x004 )
#define PMR_CII_BINARY_POINT        ( PMR_CII_BASE + 0x008 )
#define PMR_CII_INT_ACK             ( PMR_CII_BASE + 0x00c )
#define PMR_CII_END_OF_INT          ( PMR_CII_BASE + 0x010 )
#define PMR_CII_RUNNING_PRI         ( PMR_CII_BASE + 0x014 )
#define PMR_CII_HIGHEST_PENDING_INT ( PMR_CII_BASE + 0x018 )

#define PMR_GID_BASE                ( CONFIG_NORMAL_PMR_BASE + 0x1000 )
#define PMR_GID_CONTROL             ( PMR_GID_BASE + 0x000 )
#define PMR_GID_CONTROLLER_TYPE     ( PMR_GID_BASE + 0x004 )
#define PMR_GID_SET_ENABLE_00_31    ( PMR_GID_BASE + 0x100 )
#define PMR_GID_SET_ENABLE_32_63    ( PMR_GID_BASE + 0x104 )
#define PMR_GID_CLEAR_ENABLE_00_31  ( PMR_GID_BASE + 0x180 )
#define PMR_GID_CLEAR_ENABLE_32_63  ( PMR_GID_BASE + 0x184 )
#define PMR_GID_SET_PENDING_00_31   ( PMR_GID_BASE + 0x200 )
#define PMR_GID_SET_PENDING_32_63   ( PMR_GID_BASE + 0x204 )
#define PMR_GID_CLEAR_PENDING_00_31 ( PMR_GID_BASE + 0x280 )
#define PMR_GID_CLEAR_PENDING_32_63 ( PMR_GID_BASE + 0x284 )
#define PMR_GID_ACTIVE_00_31        ( PMR_GID_BASE + 0x300 )
#define PMR_GID_ACTIVE_32_63        ( PMR_GID_BASE + 0x304 )
#define PMR_GID_PRIORITY_00_03      ( PMR_GID_BASE + 0x400 )
#define PMR_GID_PRIORITY_04_07      ( PMR_GID_BASE + 0x404 )
#define PMR_GID_PRIORITY_08_11      ( PMR_GID_BASE + 0x408 )
#define PMR_GID_PRIORITY_12_15      ( PMR_GID_BASE + 0x40c )
#define PMR_GID_PRIORITY_16_19      ( PMR_GID_BASE + 0x410 )
#define PMR_GID_PRIORITY_20_23      ( PMR_GID_BASE + 0x414 )
#define PMR_GID_PRIORITY_24_27      ( PMR_GID_BASE + 0x418 )
#define PMR_GID_PRIORITY_28_31      ( PMR_GID_BASE + 0x41c )
#define PMR_GID_PRIORITY_32_35      ( PMR_GID_BASE + 0x420 )
#define PMR_GID_PRIORITY_36_39      ( PMR_GID_BASE + 0x424 )
#define PMR_GID_PRIORITY_40_43      ( PMR_GID_BASE + 0x428 )
#define PMR_GID_PRIORITY_44_47      ( PMR_GID_BASE + 0x42c )
#define PMR_GID_PRIORITY_48_51      ( PMR_GID_BASE + 0x430 )
#define PMR_GID_PRIORITY_52_55      ( PMR_GID_BASE + 0x434 )
#define PMR_GID_PRIORITY_56_59      ( PMR_GID_BASE + 0x438 )
#define PMR_GID_PRIORITY_60_63      ( PMR_GID_BASE + 0x43c )
#define PMR_GID_CPU_TARGET_00_03    ( PMR_GID_BASE + 0x800 )
#define PMR_GID_CPU_TARGET_04_07    ( PMR_GID_BASE + 0x804 )
#define PMR_GID_CPU_TARGET_08_11    ( PMR_GID_BASE + 0x808 )
#define PMR_GID_CPU_TARGET_12_15    ( PMR_GID_BASE + 0x80c )
#define PMR_GID_CPU_TARGET_16_19    ( PMR_GID_BASE + 0x810 )
#define PMR_GID_CPU_TARGET_20_23    ( PMR_GID_BASE + 0x814 )
#define PMR_GID_CPU_TARGET_24_27    ( PMR_GID_BASE + 0x818 )
#define PMR_GID_CPU_TARGET_28_31    ( PMR_GID_BASE + 0x81c )
#define PMR_GID_CPU_TARGET_32_35    ( PMR_GID_BASE + 0x820 )
#define PMR_GID_CPU_TARGET_36_39    ( PMR_GID_BASE + 0x824 )
#define PMR_GID_CPU_TARGET_40_43    ( PMR_GID_BASE + 0x828 )
#define PMR_GID_CPU_TARGET_44_47    ( PMR_GID_BASE + 0x82c )
#define PMR_GID_CPU_TARGET_48_51    ( PMR_GID_BASE + 0x830 )
#define PMR_GID_CPU_TARGET_52_55    ( PMR_GID_BASE + 0x834 )
#define PMR_GID_CPU_TARGET_56_59    ( PMR_GID_BASE + 0x838 )
#define PMR_GID_CPU_TARGET_60_63    ( PMR_GID_BASE + 0x83c )
#define PMR_GID_CONFIG_00_15        ( PMR_GID_BASE + 0xc00 )
#define PMR_GID_CONFIG_16_31        ( PMR_GID_BASE + 0xc04 )
#define PMR_GID_CONFIG_32_47        ( PMR_GID_BASE + 0xc08 )
#define PMR_GID_CONFIG_48_63        ( PMR_GID_BASE + 0xc0c )
#define PMR_GID_SOFTWARE_INTERRUPT  ( PMR_GID_BASE + 0xf00 )

/*
  ======================================================================
  ======================================================================
  Definitions for the IBB build of the RTE
  NOTE:  The RTE will add 0x20000000 to the following.
  ======================================================================
  ======================================================================
*/

#define APP3XX_ASI_OFFSET       0x00000000
#define APP3XX_HB_CS0_NB_OFFSET 0x10000000
#define APP3XX_HB_CS0_B_OFFSET  0x12000000
#define APP3XX_HB_CS1_NB_OFFSET 0x14000000
#define APP3XX_HB_CS1_B_OFFSET  0x16000000
#define APP3XX_HB_CS2_NB_OFFSET 0x18000000
#define APP3XX_HB_CS2_B_OFFSET  0x1a000000
#define APP3XX_HB_CS3_NB_OFFSET 0x1c000000
#define APP3XX_HB_CONF_OFFSET   0x1e000000
#define APP3XX_NIC_RX_OFFSET    0x20000000
#define APP3XX_NIC_TX_OFFSET    0x20020000
#define APP3XX_NIC_DMA_OFFSET   0x20040000
#define APP3XX_MEMC_OFFSET      0x30000000
#define APP3XX_MEMC2_OFFSET     0x38000000
#define APP3XX_APB_OFFSET       0x60000000
#define APP3XX_VIC_OFFSET       0xd0000000

#define APP3XX_GPIO_OFFSET  0x00000000
#define APP3XX_GPIO_BASE    (APP3XX_APB_OFFSET+APP3XX_PHYS_GPIO_OFFSET)
#define APP3XX_UART_OFFSET  0x01000000
#define APP3XX_UART_BASE    CONFIG_NORMAL_UART_BASE
#define APP3XX_I2C_OFFSET   0x02000000
#define APP3XX_I2C_BASE     (APP3XX_APB_OFFSET+APP3XX_PHYS_I2C_OFFSET)
#define APP3XX_SPI_OFFSET   0x03000000
#define APP3XX_SPI_BASE     (APP3XX_APB_OFFSET+APP3XX_PHYS_SPI_OFFSET)
#define APP3XX_CT_OFFSET    0x04000000
#define APP3XX_CT_BASE      (APP3XX_APB_OFFSET+APP3XX_PHYS_CT_OFFSET)
#define APP3XX_REMAP_OFFSET 0x06000000
#define APP3XX_REMAP_BASE   (APP3XX_APB_OFFSET+APP3XX_PHYS_REMAP_OFFSET)

/*
  ======================================================================
  ======================================================================
  Ram
  ======================================================================
  ======================================================================
*/

#define PHYS_RAM_BASE CONFIG_NORMAL_DDR2_0_BASE
#define CFG_LOAD_ADDR CONFIG_NORMAL_DDR2_0_BASE
#define CONFIG_NR_DRAM_BANKS 1

/*
  ======================================================================
  ======================================================================
  Flash
  ======================================================================
  ======================================================================
*/

#define CFG_FLASH_BASE 0

/*
  ======================================================================
  ======================================================================
  Commands
  ======================================================================
  ======================================================================
*/

#define CONFIG_CMD_LSI_ECC y
#define CONFIG_CMD_LSI_IBB y
#define CONFIG_CMD_LSI_ISU y
#define CONFIG_CMD_LSI_PHY y
#define CONFIG_CMD_LSI_PLL y
#define CONFIG_CMD_LSI_FLASH y
#define CONFIG_CMD_LSI_MEMBW y
#define CONFIG_CMD_LSI_MEMLAT y

/*
  ======================================================================
  ======================================================================
  PLL
  ======================================================================
  ======================================================================
*/

#ifndef __ASSEMBLY__
#ifndef LANG_ASM

enum pll_clock_ { core, ddr, axi, arm_ddr, mac, ipsec, output, rmii, sds };
typedef enum pll_clock_ pll_clock_t;

enum pll_pll_ { pll_0, pll_1 };
typedef enum pll_pll_ pll_pll_t;

#define CFG_PVT 7               /* 2 ^ ( pvt + 1 ), divide by 256 */
#define CFG_HZ  ( ( pll_get_clock( axi ) ) / ( 2 << CFG_PVT ) )

#endif /* LANG_ASM */
#endif /* __ASSEMBLY__ */

/*
  ======================================================================
  ======================================================================
  MDIO
  ======================================================================
  ======================================================================
*/

/* MDIO Registers */

#define MDIO_DATA ( CONFIG_NORMAL_AEI_BASE + 0x28 )
#define MDIO_CLK  ( CONFIG_NORMAL_AEI_BASE + 0x30 )

/* MDIO Command Register */

#define MDIO_CMD               ( CONFIG_NORMAL_AEI_BASE + 0x24 )
#define MDIO_CMD_TYPE_INACTIVE 0x1
#define MDIO_CMD_TYPE_MDIO     0x2
#define MDIO_CMD_OP_READ       0x4
#define MDIO_CMD_OP_WRITE      0x8

/* MDIO Status Register */

#define MDIO_STAT     ( CONFIG_NORMAL_AEI_BASE + 0x2c )
#define MDIO_STAT_ACK 0x1
#define MDIO_STAT_ERR 0x2

/*
  GPIO lines are a bit overused.  Many have multiple purposes, and
  with flash extended addressing even those can be overridden!  For
  serial and network interfaces to work, the following is required.
  0x54141555
*/

#define GPIO_MUX         ( CONFIG_NORMAL_AEI_BASE + 0x18 )
#define GPIO_MUX_DEFAULT 0x54141555

/*
  ======================================================================
  All clocks on the ASIC boards depend on the input reference clock.
  If the reference clock is known, the rest of the clocks can be
  calculated from the PLL registers.
*/

#define APP3XX_REF_CLOCK 33461000
/*#define APP3XX_REF_CLOCK 33333333*/
#define APP3XX_PCI_CLOCK 33333333

/* NAND related defines are here */
#define CFG_MAX_NAND_DEVICE 1
#define NAND_MAX_CHIPS 1
#define CFG_NAND_BASE (CONFIG_NORMAL_NAND_BASE)

/*
 * NAND controller register offsets
 */

#define APP3K_NAND_DATA_REG             0x00000000
#define APP3K_NAND_CMD_REG              0x00008000
#define APP3K_NAND_INDEX_REG            0x00008004
#define APP3K_NAND_STATUS1_REG          0x00008008
#define APP3K_NAND_STATUS2_REG          0x0000800C
#define APP3K_NAND_ID0_REG              0x00008010
#define APP3K_NAND_ID1_REG              0x00008014
#define APP3K_NAND_ID2_REG              0x00008018
#define APP3K_NAND_ID3_REG              0x0000801C
#define APP3K_NAND_ID4_REG              0x00008020
#define APP3K_NAND_ID5_REG              0x00008024
#define APP3K_NAND_ID6_REG              0x00008028
#define APP3K_NAND_ID7_REG              0x0000802C
#define APP3K_NAND_INTR_EN_REG          0x00008030
#define APP3K_NAND_INTR_STATUS_REG      0x00008034
#define APP3K_NAND_INTR_REG             0x00008038
#define APP3K_NAND_ECC_ADDR_LOG_REG     0x0000803C
#define APP3K_NAND_ECC_VAL_REG          0x00008040
#define APP3K_NAND_ECC_INJECT_REG       0x00008044
#define APP3K_NAND_EXT_INDEX_REG        0x00008048
#define APP3K_NAND_TIMING1_REG          0x0000804C
#define APP3K_NAND_TIMING2_REG          0x00008050
#define APP3K_NAND_CONFIG_REG           0x00008054
#define APP3K_NAND_PECC_REG             0x00008058

/*
 * AEI register offset definitions 
 */

#define APP3K_AEI_LLP_CS_CTRL (CONFIG_NORMAL_AEI_BASE + 0xcc)

/* JFFS2 related definitions */
#define CONFIG_JFFS2_NAND
#define CONFIG_JFFS2_CMDLINE
#define MTDIDS_DEFAULT		"nor0=app3k-nor,nand0=app3k-nand"
#define MTDPARTS_DEFAULT	"mtdparts=app3k-nor:512k(u-boot),256k(u-boot-env-0),256k(u-boot-env-1),512k(ibb);app3k-nand:3M(bootA),3M(bootB),50M(fsA),50M(fsB)"
#define MTDPARTS_REQUIRED   "mtdparts=app3k-nor:512k(u-boot),256k(u-boot-env-0),256k(u-boot-env-1)"

/*
 * Default environment variables.
 */

#define CONFIG_EXTRA_ENV_SETTINGS \
"ad_value=0x61\0" \
"loadaddr=d00000\0" \
"bootaddr=0x1100\0" \
""

/*
  ======================================================================
  ======================================================================
  Set the amount of NOR FLASH set aside for the U-Boot binary.
  ======================================================================
  ======================================================================
*/

#define CFG_MONITOR_LEN ( 0x80000 )

/*
  ======================================================================
  ======================================================================
  Commands
  ======================================================================
  ======================================================================
*/

#include <config_cmd_default.h>

#define CONFIG_COMMANDS
#define CONFIG_CMD_JFFS2
#define CONFIG_CMD_DFL
#define CONFIG_CMD_NAND
#define CONFIG_CMD_CACHE
#define CONFIG_CMD_PING
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_PLL
#define CONFIG_CMD_IBB
#define CONFIG_CMD_PHY
#define CONFIG_CMD_APP3_FLASH
#define CONFIG_CMD_ELF
#define CONFIG_CMD_ENV
#define CONFIG_CMD_FLASH

/*
  ======================================================================
  ======================================================================
  Include all the common definitions (app3 and app3k).
  ======================================================================
  ======================================================================
*/

#include <configs/app.h>

#endif  /* __CONFIG_H */
