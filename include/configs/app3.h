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

#ifndef __CONFIG_H
#define __CONFIG_H

#define LSI_ARCH_APP3

/*
  ======================================================================
  ======================================================================
  Reset Memory Map
  ======================================================================
  ======================================================================
*/

#define CONFIG_RESET_FLASH_BASE      0x00000000
#define CONFIG_RESET_ASI_BASE        0x20000000
#define CONFIG_RESET_HB_CS0_NB_BASE  0x30000000
#define CONFIG_RESET_HB_CS0_B_BASE   0x32000000
#define CONFIG_RESET_HB_CS1_NB_BASE  0x34000000
#define CONFIG_RESET_HB_CS1_B_BASE   0x36000000
#define CONFIG_RESET_HB_CS2_NB_BASE  0x38000000
#define CONFIG_RESET_HB_CS2_B_BASE   0x3a000000
#define CONFIG_RESET_HB_CS3_NB_BASE  0x3c000000
#define CONFIG_RESET_HB_CONF_BASE    0x3e000000
#define CONFIG_RESET_AEI_BASE        CONFIG_RESET_HB_CONF_BASE
#define CONFIG_RESET_NIC_RX_BASE     0x40000000
#define CONFIG_RESET_NIC_TX_BASE     0x40020000
#define CONFIG_RESET_NIC_DMA_BASE    0x40040000
#define CONFIG_RESET_MEMC_BASE       0x50000000
#define CONFIG_RESET_DRAM0_BASE      0x60000000
#define CONFIG_RESET_APB_BASE        0x80000000
#define CONFIG_RESET_VIC_BASE        0xF0000000

/* I/O devices: note that most of these require 4KB register space */
#define CONFIG_RESET_GPIO_0_BASE (CONFIG_RESET_APB_BASE+0x00000000)
#define CONFIG_RESET_UART_BASE   (CONFIG_RESET_APB_BASE+0x01000000)
#define CONFIG_RESET_I2C_BASE    (CONFIG_RESET_APB_BASE+0x02000000)
#define CONFIG_RESET_SPI_BASE    (CONFIG_RESET_APB_BASE+0x03000000)
#define CONFIG_RESET_CT_BASE     (CONFIG_RESET_APB_BASE+0x04000000)
#define CONFIG_RESET_WDT_BASE    (CONFIG_RESET_APB_BASE+0x05000000)
#define CONFIG_RESET_REMAP_BASE  (CONFIG_RESET_APB_BASE+0x06000000)
#define CONFIG_RESET_GPIO_1_BASE (CONFIG_RESET_APB_BASE+0x08000000)

/*
  ======================================================================
  ======================================================================
  Normal Memory Map
  ======================================================================
  ======================================================================
*/

#define CONFIG_NORMAL_FLASH_BASE     0x10000000
#define CONFIG_NORMAL_ASI_BASE       CONFIG_RESET_ASI_BASE
#define CONFIG_NORMAL_HB_CS0_NB_BASE CONFIG_RESET_HB_CS0_NB_BASE
#define CONFIG_NORMAL_HB_CS0_B_BASE  CONFIG_RESET_HB_CS0_B_BASE
#define CONFIG_NORMAL_HB_CS1_NB_BASE CONFIG_RESET_HB_CS1_NB_BASE
#define CONFIG_NORMAL_HB_CS1_B_BASE  CONFIG_RESET_HB_CS1_B_BASE
#define CONFIG_NORMAL_HB_CS2_NB_BASE CONFIG_RESET_HB_CS2_NB_BASE
#define CONFIG_NORMAL_HB_CS2_B_BASE  CONFIG_RESET_HB_CS2_B_BASE
#define CONFIG_NORMAL_HB_CS3_NB_BASE CONFIG_RESET_HB_CS3_NB_BASE
#define CONFIG_NORMAL_HB_CONF_BASE   CONFIG_RESET_HB_CONF_BASE
#define CONFIG_NORMAL_AEI_BASE       CONFIG_NORMAL_HB_CONF_BASE
#define CONFIG_NORMAL_NIC_RX_BASE    CONFIG_RESET_NIC_RX_BASE
#define CONFIG_NORMAL_NIC_TX_BASE    CONFIG_RESET_NIC_TX_BASE
#define CONFIG_NORMAL_NIC_DMA_BASE   CONFIG_RESET_NIC_DMA_BASE
#define CONFIG_NORMAL_MEMC_BASE      CONFIG_RESET_MEMC_BASE
#define CONFIG_NORMAL_DRAM0_BASE     CONFIG_RESET_DRAM0_BASE
#define CONFIG_NORMAL_APB_BASE       CONFIG_RESET_APB_BASE
#define CONFIG_NORMAL_VIC_BASE       CONFIG_RESET_VIC_BASE

/* I/O devices: note that most of these require 4KB register space */
#define CONFIG_NORMAL_GPIO_0_BASE        (CONFIG_NORMAL_APB_BASE+0x00000000)
#define CONFIG_NORMAL_UART_BASE          (CONFIG_NORMAL_APB_BASE+0x01000000)
#define CONFIG_NORMAL_I2C_BASE           (CONFIG_NORMAL_APB_BASE+0x02000000)
#define CONFIG_NORMAL_SPI_BASE           (CONFIG_NORMAL_APB_BASE+0x03000000)
#define CONFIG_NORMAL_CT_BASE            (CONFIG_NORMAL_APB_BASE+0x04000000)
#define CONFIG_NORMAL_WDT_BASE           (CONFIG_NORMAL_APB_BASE+0x05000000)
#define CONFIG_NORMAL_REMAP_BASE         (CONFIG_NORMAL_APB_BASE+0x06000000)
#define CONFIG_NORMAL_GPIO_1_BASE        (CONFIG_NORMAL_APB_BASE+0x08000000)

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

#define PHYS_RAM_BASE CONFIG_NORMAL_DRAM0_BASE
#define CFG_LOAD_ADDR CONFIG_NORMAL_DRAM0_BASE
#define CONFIG_NR_DRAM_BANKS 1

/*
  ======================================================================
  ======================================================================
  Flash
  ======================================================================
  ======================================================================
*/

#define CFG_FLASH_BASE CONFIG_RESET_FLASH_BASE

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

enum pll_clock_ { core, ddr, arm_core, arm_ddr, mac, host, output, rmii };
typedef enum pll_clock_ pll_clock_t;

enum pll_pll_ { pll_0, pll_1 };
typedef enum pll_pll_ pll_pll_t;

#define CFG_PVT         7   /* 2^(pvt+1), divide by 256 */
#define CFG_HZ          ((pll_get_clock(arm_core))/(2 << CFG_PVT))

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

#define MDIO_DATA 0x3e000028
#define MDIO_CLK  0x3e000030

/* MDIO Command Register */

#define MDIO_CMD               0x3e000024
#define MDIO_CMD_TYPE_INACTIVE 0x1
#define MDIO_CMD_TYPE_MDIO     0x2
#define MDIO_CMD_OP_READ       0x4
#define MDIO_CMD_OP_WRITE      0x8

/* MDIO Status Register */

#define MDIO_STAT     0x3e00002c
#define MDIO_STAT_ACK 0x1
#define MDIO_STAT_ERR 0x2

/*
  GPIO lines are a bit overused.  Many have multiple purposes, and
  with flash extended addressing even those can be overridden!  For
  serial and network interfaces to work, the following is required.
  0x54141555
*/

#define GPIO_MUX         ( CONFIG_NORMAL_HB_CONF_BASE + 0x18 )
#define GPIO_MUX_DEFAULT 0x54141555

/*
  ======================================================================
  All clocks on the ASIC boards depend on the input reference clock.
  If the reference clock is known, the rest of the clocks can be
  calculated from the PLL registers.
*/

#define APP3XX_REF_CLOCK 33333333

/* JFFS2 related definitions */
#define CONFIG_JFFS2_CMDLINE
#define MTDIDS_DEFAULT		"nor0=app3-nor"
#define MTDPARTS_DEFAULT	"mtdparts=app3-nor:256k(u-boot),256k(u-boot-env-0),256k(u-boot-env-1),1M(ibb),-(unused-nor)"
#define MTDPARTS_REQUIRED   "mtdparts=app3-nor:256k(u-boot),256k(u-boot-env-0),256k(u-boot-env-1)"

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

#define CFG_MONITOR_LEN ( 0x40000 )

/*
  ======================================================================
  ======================================================================
  Commands
  ======================================================================
  ======================================================================
*/

#include <config_cmd_default.h>

#define CONFIG_COMMANDS
#define CONFIG_CMD_DFL
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
