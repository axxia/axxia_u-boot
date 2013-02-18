/*
 * (C) Copyright 2009 LSI Corporation <www.lsi.com>
 * John Jacques <john.jacques@lsi.com>
 * Configuration settings for LSI development boards.
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

#ifndef __CONFIGS_LSI_H
#define __CONFIGS_LSI_H

#define CONFIG_LSI 1

/*
  ======================================================================
  ======================================================================
  Version
  ======================================================================
  ======================================================================
*/

#ifndef __ASSEMBLY__
const char *get_lsi_version(void);
#endif /* __ASSEMBLY__ */

/*
  ======================================================================
  ======================================================================
  NAND
  ======================================================================
  ======================================================================
*/

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
#if 1
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
#if 1
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
#if 1
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

int phy_duplex( int );
int phy_link( int );
int phy_renegotiate( int, int );
int phy_speed( int );
void dump_packet(const char *, void *, int);

#endif /* __ASSEMBLY__ */

#define CONFIG_SYS_PKTALIGN 128
#define ARCH_DMA_MINALIGN 128

/*
  ======================================================================
  ======================================================================
  Debug/Warn/Error
  ======================================================================
  ======================================================================
*/

#ifndef __ASSEMBLY__

#include <common.h>
#include <asm/io.h>

/* Debug */
extern int lsi_debug_enable;

#ifdef LSI_DEBUG
#define LSI_DEBUG_ENABLE() {lsi_debug_enable = 1;}
#define LSI_DEBUG_DISABLE() {lsi_debug_enable = -1;}
#define LSI_DEBUG_ENABLED() (1 == lsi_debug_enable)
#define DEBUG_PRINT( format, args... ) do { \
if (LSI_DEBUG_ENABLED()) { ;				   \
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

extern int lsi_logio_enable;

#ifdef LSI_LOGIO
#define LSI_LOGIO_ENABLE() {lsi_logio_enable = 1;}
#define LSI_LOGIO_DISABLE() {lsi_logio_enable = -1;}
#define LSI_LOGIO_ENABLED() (1 == lsi_logio_enable)
static inline unsigned long _READL(const char *, int, unsigned long);
static inline unsigned long
_READL(const char *file, int line, unsigned long address)
{
	unsigned long value;
	value = readl(address);

	if (LSI_LOGIO_ENABLED())
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

	if (LSI_LOGIO_ENABLEd())
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

#endif /* __ASSEMBLY__ */

/*
  ======================================================================
  ======================================================================
  Errata
  ======================================================================
  ======================================================================
*/

#if 0
#ifndef __ASSEMBLY__
#define mdelay( n ) do { \
unsigned long msec = ( n ); \
while( msec-- ) udelay( 1000 ); \
} while( 0 );
#endif /* __ASSEMBLY__ */
#endif

#endif /* __CONFIGS_LSI_H */
