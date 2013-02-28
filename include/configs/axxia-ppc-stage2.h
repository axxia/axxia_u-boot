 /*
 * (C) Copyright 2009
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

#ifndef __CONFIGS_ACP2_H
#define __CONFIGS_ACP2_H

#define CONFIG_ACP2 1
//#define CONFIG_SPD 1

#ifdef CONFIG_FIT
#error "CONFIG_FIT is DEFINED!!!"
#endif

/*
  ------------------------------------------------------------------------------
  Special Functionality for Testing...
*/

//#define NCR_TRACER
/*#define ACP2_SYSMEM_TEST*/
#ifdef ACP_25xx
#define ACP2_PCIE_TEST
#endif

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

/*#define PRESET_ECC_LEVELING*/
/*#define SM_BYTELANE_TEST_DEBUG*/
/*#define SM_ECC_BYTELANE_TEST_DEBUG*/
/*#define SM_DEBUG_MODE*/
/*#define SM_REG_DUMP*/
/*#define DISPLAY_PARAMETERS*/
/*#define VID_VERBOSE*/

/*
  ----------------------------------------------------------------------
*/

#define CFG_PROMPT		"ACP2=> "
#define CONFIG_SYS_PROMPT	"ACP2=> "
#define CFG_CBSIZE		256
#define CONFIG_SYS_CBSIZE	256
#define CFG_PBSIZE		(CFG_CBSIZE+sizeof(CFG_PROMPT)+16)
#define CONFIG_SYS_PBSIZE	(CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16)
#define CFG_MAXARGS		64
#define CONFIG_SYS_MAXARGS	64
#define CFG_BARGSIZE		CFG_CBSIZE
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE

#ifdef ACP2_SYSMEM_TEST
#if !defined(ACP_25xx) && !defined(USE_HOSTCC)
#error "Only Possible on 2500!!!"
#endif

/*
  ----------------------------------------------------------------------
  Memory Layout with NO SYSTEM MEMORY

  In this case, just try to get to the prompt...
*/

#define CFG_MALLOC_BASE 0xf0a24000
#define CFG_MALLOC_LEN 0x4000
#define CFG_INIT_RAM_ADDR 0xf0a24000

#else
/*
  ----------------------------------------------------------------------
  Memory Layout

  U-Boot won't get moved to the top of RAM in this case. There will be
  two RAM segments.  128 Kbytes at address 0 (U-Boot text) and 1 Mbyte
  at 0x10000000. The 1M segment will hold the third stage boot loader
  (see acp3.h).  Until control gets transferred to the third stage
  boot loader, use the the 1M segment for malloc, board info data and
  global data.
*/

#define CFG_MALLOC_BASE     0x00300000
#define CFG_MALLOC_LEN      (1024 * 1024)
#ifdef ACP_25xx
#define CFG_INIT_RAM_ADDR   0xf0a24000
#else
#define CFG_INIT_RAM_ADDR   0xf0a1fc00
#endif
#endif	/* ACP2_SYSMEM_TEST */

/*
  ----------------------------------------------------------------------
  Parameter Storage 
*/
 
#ifdef ACP_25xx
#define PARAMETERS_OFFSET (127 * 1024)
#define PARAMETERS_ADDRESS (LCM + PARAMETERS_OFFSET)
#define PARAMETERS_SIZE (1024)

#define CANNED_PHY_REGS_OFFSET (PARAMETERS_OFFSET + 512)
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

#endif
/*
  ----------------------------------------------------------------------
  Reduce memory usage...
*/

#define CFG_NOHELP

/*
  ======================================================================
  ======================================================================
  Errata
  ======================================================================
  ======================================================================
*/

#ifndef __ASSEMBLY__
extern unsigned long sysmem_size;
extern unsigned long reset_enabled;
extern unsigned long sm_phy_reg_restore;
extern unsigned long sm_phy_reg_dump;
#endif

#define CONFIG_CMD_SETGETDCR

#ifndef __ASSEMBLY__
int acp_init( void );
#endif /* __ASSEMBLY__ */

#ifndef ACP2_SYSMEM_TEST
#define CONFIG_BOOTM_UBOOT
#endif

/* Note that this adds almost 0x3000 bytes! */
#if defined(ACP_25xx)
#define CONFIG_CMD_MEMORY
#define CONFIG_CMD_MTEST
#define CFG_MEMTEST_START 0
#define CONFIG_SYS_MEMTEST_START 0
#define CFG_MEMTEST_END   0x10000000
#define CONFIG_SYS_MEMTEST_END   0x10000000
#define CONFIG_SYS_ALT_MEMTEST
#endif

#if defined(ACP_EMU) || defined(ACP2_PCIE_TEST)
#define CONFIG_LSI_TEST 1
#endif

/* Note that this adds about 0x300 bytes. */
/*#define CONFIG_CMD_SOURCE 1*/

/*
  ======================================================================
  ======================================================================
  Non-Volatile Storage...
  ======================================================================
  ======================================================================
*/

/*
  The 2nd stage can only support either NAND or Serial FLASH.  The
  environment must be stored on the supported device.  By default, the
  supported device is Serial FLASH in the AXM2500 and NAND in all
  other cases.
*/

#if defined(ACP_25xx) || defined(CONFIG_SPD)
#define CONFIG_SYS_NO_FLASH
#define CONFIG_LSI_SERIAL_FLASH
#define CONFIG_LSI_SERIAL_FLASH_ENV
#else
#define CONFIG_LSI_NAND
#define ACP_NAND_4BIT_ECC
#define CONFIG_LSI_NAND_ENV
#endif

#if defined(CONFIG_SPD)
#define CONFIG_HARD_I2C         /* Hardware I2C */
#define CONFIG_CMD_I2C
#define CONFIG_SYS_I2C_MULTI_EEPROMS
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN 1
#define CONFIG_CMD_EEPROM
#if defined(ACP_25xx)
#define CONFIG_I2C_MULTI_BUS
#define CONFIG_SYS_MAX_I2C_BUS 2
#endif
#endif

/*
  ======================================================================
  ======================================================================
  Network
  ======================================================================
  ======================================================================
*/

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

/*
  ----------------------------------------------------------------------
  Include the ACP common header.
*/

#include <configs/axxia-ppc.h>

#endif	/* __CONFIGS_ACP2_H */
