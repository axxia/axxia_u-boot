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

#define CONFIG_SYS_LDSCRIPT "board/lsi/acp/u-boot-acp2.lds"

#define CONFIG_ACP2 1

/*#define NCR_TRACER*/

#ifdef CONFIG_FIT
#error "CONFIG_FIT is DEFINED!!!"
#endif

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

#undef CONFIG_CMD_IMPORTENV
#undef CONFIG_CMD_EXPORTENV

#ifndef __ASSEMBLY__
extern unsigned long sysmem_size;
#endif

#define CONFIG_CMD_SETGETDCR

#ifndef __ASSEMBLY__
int acp_init( void );
#endif /* __ASSEMBLY__ */

#define CONFIG_BOOTM_UBOOT

/* Note that this adds almost 0x3000 bytes! */
#if 0
#if defined(ACP_EMU)
#define CONFIG_CMD_MEMORY
#define CFG_MEMTEST_START 0x4000000
#define CONFIG_SYS_MEMTEST_START 0x4000000
#define CFG_MEMTEST_END   0x5000000
#define CONFIG_SYS_MEMTEST_END   0x5000000
#endif
#endif

#ifdef ACP_EMU
#define CONFIG_LSI_TEST 1
#endif

/* Note that this adds about 0x300 bytes. */
/*#define CONFIG_CMD_SOURCE 1*/

/*
  ======================================================================
  ======================================================================
  NAND
  ======================================================================
  ======================================================================
*/

#define ACP_NAND_4BIT_ECC

/*
  ======================================================================
  ======================================================================
  Network
  ======================================================================
  ======================================================================
*/

#if !defined(NCR_TRACER)
#if 0
#define CONFIG_LSI_NET
#define CONFIG_CMD_NET
#define CONFIG_CMD_DHCP
#endif
#define APP3XXNIC_RX_BASE  (IO+0x80000)
#define APP3XXNIC_TX_BASE  (IO+0x81000)
#define APP3XXNIC_DMA_BASE (IO+0x82000)
#endif /* NCR_TRACER */

/*
  ----------------------------------------------------------------------
  Include the ACP common header.
*/

#include <configs/acp.h>

#endif	/* __CONFIGS_ACP2_H */
