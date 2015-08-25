/*
 * (C) Copyright 2013
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

#ifndef __CONFIGS_AXXIA_56XX_SIM_H
#define __CONFIGS_AXXIA_56XX_SIM_H

/*#define CONFIG_AXXIA_56XX_SIM_V_1_0*/
#define CONFIG_AXXIA_56XX_SIM
#define CONFIG_AXXIA_SIM
#define ARM64

#define CONFIG_AXXIA_AXM_I2C

#define CONFIG_USB_XHCI_AXXIA

#define CONFIG_CMD_USB 1
#define CONFIG_USB_XHCI 1
#define CONFIG_SYS_USB_XHCI_MAX_ROOT_PORTS 1
#define CONFIG_USB_STORAGE 1
#define CONFIG_CMD_USB_STORAGE 1
#define CONFIG_CMD_EXT2 1
#define CONFIG_CMD_EXT4 1
#define CONFIG_DOS_PARTITION 1


/*
  ==============================================================================
  ==============================================================================
  Constants
  ==============================================================================
  ==============================================================================
*/

#define CONFIG_BAUDRATE    9600


/********** FEMAC PHY ADDRESS *************/
#define CONFIG_AXXIA_PHY_ADDRESS 0x3


/* HACK: Define it until cache coherency is figured out */
/* #define USE_CACHE_SYNC */

/*
  ==============================================================================
  ==============================================================================
  Non-Volatile Storage
  ==============================================================================
  ==============================================================================
*/

#define CONFIG_AXXIA_SERIAL_FLASH /* Include support for SPI flash. */

#define CONFIG_AXXIA_SERIAL_FLASH_ENV
#define CONFIG_ENV_IS_IN_SPI_FLASH

#define CONFIG_PARAMETER_OFFSET          (512 * 1024)
#define CONFIG_PARAMETER_SIZE            (64 * 1024)
#define CONFIG_PARAMETER_RANGE           (64 * 1024)
#define CONFIG_PARAMETER_OFFSET_REDUND \
	(CONFIG_PARAMETER_OFFSET + CONFIG_PARAMETER_RANGE)
#define CONFIG_PARAMETER_SIZE_REDUND     CONFIG_PARAMETER_SIZE
#define CONFIG_PARAMETER_RANGE_REDUND    CONFIG_PARAMETER_RANGE

#define CONFIG_SYS_REDUNDAND_ENVIRONMENT
#define CONFIG_ENV_OFFSET \
	(CONFIG_PARAMETER_OFFSET_REDUND + CONFIG_PARAMETER_RANGE_REDUND)
#define CONFIG_ENV_SECT_SIZE             (64 * 1024)
#define CONFIG_ENV_SIZE                  (64 * 1024)
#define CONFIG_ENV_SECT_SIZE             (64 * 1024)
#define CONFIG_ENV_RANGE                 (64 * 1024)
#define CONFIG_ENV_OFFSET_REDUND         (CONFIG_ENV_OFFSET + CONFIG_ENV_RANGE)
#define CONFIG_ENV_SIZE_REDUND            CONFIG_ENV_SIZE
#define CONFIG_ENV_RANGE_REDUND           CONFIG_ENV_RANGE

#define CONFIG_UBOOT_OFFSET              (1 * 1024 * 1024)
#define CONFIG_UBOOT_SIZE                (2 * 1024 * 1024)
#define CONFIG_UBOOT_OFFSET_REDUND       (3 * 1024 * 1024)
#define CONFIG_UBOOT_SIZE_REDUND         CONFIG_UBOOT_SIZE

/*
  ==============================================================================
  ==============================================================================
  I2C
  ==============================================================================
  ==============================================================================
*/

#ifndef __ASSEMBLY__
#define CONFIG_CMD_I2C
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
  Features.
  ==============================================================================
  ==============================================================================
*/

#define CONFIG_GICV3
#define GICD_BASE (0x8010000000)
#define GICR_BASE (0x8010200000)

#define CONFIG_SYS_CNTR_FREQ 62500000

#define CONFIG_EXTRA_ENV_SETTINGS		\
	"loadaddr=0x80100000\0"			\
	"kernel_addr=0x100000\0"		\
	"ramdisk_addr=0x800000\0"		\
	"ramdisk_size=0x2000000\0"		\
	"fdt_high=0xffffffffffffffff\0"		\
	"initrd_high=0xffffffffffffffff\0"	\
	"kernel_start=0x581200000\0"		\
	"kernel_load=0x806f0000\0"		\
	"kernel_size=0x1000000\0"		\
	"console=ttyAMA0,115200n8\0"

#define CONFIG_BOOTARGS		"root=/dev/vda console=ttyAMA0,115200 " \
				"earlycon=pl011,0x8080000000 " \
				"mem=2G"
#define CONFIG_BOOTCOMMAND	"bootm 4010000 - 4000000"
#define CONFIG_BOOTDELAY	3

#define V_MIN   795
#define V_SAFE  940
#define V_MAX  1050

/*#define CONFIG_MEMORY_RETENTION*/

#define SSP_DEFAULT_CLOCK  1000000

#define CONFIG_AXXIA_PCI
#define CONFIG_SPL_PCI_SUPPORT

/*#define CONFIG_AXXIA_FEMAC*/
/*#define CONFIG_AXXIA_EIOA*/

#include <configs/axm56xx_common.h>

#endif	/* __CONFIGS_AXXIA_56XX_SIM_H */
