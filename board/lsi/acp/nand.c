/*
 * nand.c
 *
 * Driver for the NAND controller on LSI's ACP.
 * 
 * Copyright (C) 2009 LSI Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307	 USA
 *
 */

/*#define LSI_DEBUG*/
#define LSI_WARN
/*#define LSI_LOGIO*/
#include <config.h>
#ifndef NCR_TRACER
#include <common.h>
#include <malloc.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/nand.h>
#include <asm/errno.h>
#include <asm/io.h>

/*
  ===============================================================================
  ===============================================================================
  Controller Type, EP501, EP501G1, or EP501G3.
  ===============================================================================
  ===============================================================================
*/

#if defined(ACP_X1V1)
#define EP501
#elif defined(ACP_X1V2)
#define EP501G1
#elif defined(CONFIG_ACP_342X) || defined(ACP_25xx)
#define EP501G3
#else
#error "Unsupported ACP System Type!"
#endif

/*
  ===============================================================================
  ===============================================================================
  Some Oddities...

  -1-
  Reading EP501 registers while the device is calculating ECC will
  hang the AHB.	 As the only way to know that an ECC calculation is in
  progress is to read the "extra bits" added to the interrupt status
  register, this can cause problems.  To get around this, the
  PECC_BUSY signal from the controller is also available in a general
  purpose system register.  0x149.0.0xc/0x0020_0040_0000_c00c, bit 24.
  So, before reading the interrupt status register (or any other
  register for that matter) make sure the bit mentioned above is
  clear.  See BZ21212.

  -2-
  Extra bits have been added to the interrupt status register.	See
  BZ21196.  From that defect...

  == Bit 0
  This bit is set when un-correctable ECC is detected. This bit can be
  cleared by writing "0" to this register. Writing "1" has no
  effect. An interrupt is generated if this bit and the enable bit
  (bit 0) in the Interrupt Enable Register are "1". This bit is not
  set if ECC is disabled.

  == Bit 1
  This bit is set when correctable ECC is detected. This bit can be
  cleared by writing "0" to this register. Writing "1" has no
  effect. An interrupt is generated if this bit and the enable bit
  (bit 1) in the Interrupt Enable Register are "1". This bit is not
  set if ECC is disabled.

  == Bit 2
  This bit is set when a rising edge is detected on the non gated
  READY/BUSY# input from the NAND Flash. This bit can be cleared by
  writing a "0" to this register. Writing a "1" has no effect. An
  interrupt is generated if this bit and the enable bit (bit 2) in the
  Interrupt Enable Register are "1".

  == Bit 3
  This bit is set when a falling edge is detected on the non gated
  READY/BUSY# input from the NAND Flash. This bit can be cleared by
  writing a "0" to this register. Writing a "1" has no effect. An
  interrupt is generated if this bit and the enable bit (bit 3) in the
  Interrupt Enable Register are "1".

  == Bit 4
  This bit is set when a falling edge is detected on the PECC_BUSY
  signal which indicates when the NAND controller has taken control of
  the NAND Flash for ECC byte access. This bit can be cleared by
  writing a "0" to this register. Writing a "1" has no effect. An
  interrupt is generated if this bit and the enable bit (bit 4) in the
  Interrupt Enable Register are "1".

  == Bit 5
  This bit is read only and is the synchronized level on the non gated
  READY/BUSY# input from the NAND Flash. This bit can be used to poll
  the status of this signal and is not used to generate an interrupt.

  == Bit 6
  This bit is read only and indicates the level on the PECC_BUSY
  signal which indicates when the NAND controller has taken control of
  the NAND Flash for ECC byte access. This bit can be used to poll the
  level of this signal and is not used to generate an interrupt.

  ===============================================================================
  ===============================================================================
*/

lsi_ecc_mode_t ecc_mode;

const char *
get_ecc_mode_string(lsi_ecc_mode_t mode)

{
	switch (mode) {
	case LSI_NAND_ECC_MODE_OFF:
		return "LSI_NAND_ECC_MODE_OFF";
		break;
	case LSI_NAND_ECC_MODE_1BIT:
		return "LSI_NAND_ECC_MODE_1BIT";
		break;
	case LSI_NAND_ECC_MODE_4BIT:
		return "LSI_NAND_ECC_MODE_4BIT";
		break;
	case LSI_NAND_ECC_MODE_8BIT:
		return "LSI_NAND_ECC_MODE_8BIT";
		break;
	case LSI_NAND_ECC_MODE_12BIT:
		return "LSI_NAND_ECC_MODE_12BIT";
		break;
	default:
		return "Unknown ECC Mode";
		break;
	}
}

lsi_ecc_mode_t
get_ecc_mode(void)
{
	return ecc_mode;
}

void
set_ecc_mode(lsi_ecc_mode_t new_ecc_mode)
{
	unsigned long value;

	if (new_ecc_mode == ecc_mode) {
		printf("ECC mode is already set as requested.\n");
		return;
	}

#if defined(EP501)
	switch (new_ecc_mode) {
	case LSI_NAND_ECC_MODE_OFF:
		ecc_mode = LSI_NAND_ECC_MODE_OFF;
		break;
	case LSI_NAND_ECC_MODE_1BIT:
		ecc_mode = LSI_NAND_ECC_MODE_1BIT;
		break;
	default:
		printf("EP501 Only Supports ECC Modes off and 1bit\n");
		break;
	}
#elif defined(EP501G1)
	switch (new_ecc_mode) {
	case LSI_NAND_ECC_MODE_OFF:
		ecc_mode = LSI_NAND_ECC_MODE_OFF;
		value = readl(CONFIG_SYS_NAND_BASE + EP501G1_NAND_INTR_EN_REG);
		value |= 0x80;
		WRITEL(value, CONFIG_SYS_NAND_BASE + EP501G1_NAND_INTR_EN_REG);
		break;
	case LSI_NAND_ECC_MODE_1BIT:
		ecc_mode = LSI_NAND_ECC_MODE_1BIT;
		value = readl(CONFIG_SYS_NAND_BASE + EP501G1_NAND_INTR_EN_REG);
		value &= ~0x80;
		WRITEL(value, CONFIG_SYS_NAND_BASE + EP501G1_NAND_INTR_EN_REG);
		value = readl(CONFIG_SYS_NAND_BASE + EP501_NAND_CONFIG_REG);
		value &= ~0x800;
		WRITEL(value, CONFIG_SYS_NAND_BASE + EP501_NAND_CONFIG_REG);
		break;
	case LSI_NAND_ECC_MODE_4BIT:
		ecc_mode = LSI_NAND_ECC_MODE_4BIT;
		value = readl(CONFIG_SYS_NAND_BASE + EP501G1_NAND_INTR_EN_REG);
		value &= ~0x80;
		WRITEL(value, CONFIG_SYS_NAND_BASE + EP501G1_NAND_INTR_EN_REG);
		value = readl(CONFIG_SYS_NAND_BASE + EP501_NAND_CONFIG_REG);
		value &= ~0x800;
		value |= 0x800;
		WRITEL(value, CONFIG_SYS_NAND_BASE + EP501_NAND_CONFIG_REG);
		break;
	default:
		printf("EP501G1 Only Supports ECC Modes off, 1bit and 4bit\n");
		break;
	}
#elif defined(EP501G3)
	switch (new_ecc_mode) {
	case LSI_NAND_ECC_MODE_OFF:
		ecc_mode = LSI_NAND_ECC_MODE_OFF;
		value = readl(CONFIG_SYS_NAND_BASE + EP501G1_NAND_INTR_EN_REG);
		value |= 0x80;
		WRITEL(value, CONFIG_SYS_NAND_BASE + EP501G1_NAND_INTR_EN_REG);
		value = readl(CONFIG_SYS_NAND_BASE + EP501_NAND_CONFIG_REG);
		value &= ~0x1800;
		WRITEL(value, CONFIG_SYS_NAND_BASE + EP501_NAND_CONFIG_REG);
		break;
	case LSI_NAND_ECC_MODE_4BIT:
		ecc_mode = LSI_NAND_ECC_MODE_4BIT;
		value = readl(CONFIG_SYS_NAND_BASE + EP501G1_NAND_INTR_EN_REG);
		value &= ~0x80;
		WRITEL(value, CONFIG_SYS_NAND_BASE + EP501G1_NAND_INTR_EN_REG);
		value = readl(CONFIG_SYS_NAND_BASE + EP501_NAND_CONFIG_REG);
		value &= ~0x1800;
		value |= 0x800;
		WRITEL(value, CONFIG_SYS_NAND_BASE + EP501_NAND_CONFIG_REG);
		break;
	default:
		printf("EP501G3 Only Supports ECC Modes "
		       "off, 4bit, 8bit, and 12bit\n");
		printf("  8bit and 12bit have not been implemented.\n");
		break;
	}
#else
#error "Unsupported Controller!"
#endif
}

#define LSI_NAND_PECC_BUSY_REGISTER GPREG_STATUS

#if defined(ACP_X1V1)
#define LSI_NAND_PECC_BUSY_MASK	    (1<<25)
#elif defined(ACP_X1V2) || defined(CONFIG_ACP_342X)
#define LSI_NAND_PECC_BUSY_MASK	    (1<<28)
#elif defined(ACP_25xx)
#define LSI_NAND_PECC_BUSY_MASK	    (1<<23)
#endif

#define NAND_CMD_START_ECC_READ	    0x23
#define NAND_CMD_RNDOUTSTART	    0xE0

#define NAND_CMD_CE_OFF_501	    0xEE
#define NAND_CMD_CE_OFF_501G1	    0xEE
#define NAND_CMD_CE_OFF_501G3	    0xFE
static int nand_cmd_ce_off;

typedef union {
	unsigned long raw;

	struct {
#if __BYTE_ORDER == __BIG_ENDIAN
		unsigned long th  : 8;
		unsigned long trp : 8;
		unsigned long twp : 8;
		unsigned long ts  : 8;
#else
		unsigned long ts  : 8;
		unsigned long twp : 8;
		unsigned long trp : 8;
		unsigned long th  : 8;
#endif
	} __attribute__ ( ( packed ) ) bits;
} __attribute__ ( ( packed ) ) nand_timing_control_register_0_t;

typedef union {
	unsigned long raw;

	struct {
#if __BYTE_ORDER == __BIG_ENDIAN
		unsigned long twb : 8;
		unsigned long trr : 8;
		unsigned long trh : 8;
		unsigned long twh : 8;
#else
		unsigned long twh : 8;
		unsigned long trh : 8;
		unsigned long trr : 8;
		unsigned long twb : 8;
#endif
	} __attribute__ ( ( packed ) ) bits;
} __attribute__ ( ( packed ) ) nand_timing_control_register_1_t;

#ifdef EP501G3
typedef union {
	unsigned long raw;

	struct {
#if __BYTE_ORDER == __BIG_ENDIAN
		unsigned long      : 8;
		unsigned long trhw : 8;
		unsigned long twhr : 8;
		unsigned long tccs : 8;
#else
		unsigned long tccs : 8;
		unsigned long twhr : 8;
		unsigned long trhw : 8;
		unsigned long      : 8;
#endif
	} __attribute__ ( ( packed ) ) bits;
} __attribute__ ( ( packed ) ) nand_timing_control_register_2_t;
#endif

/*
  ===============================================================================
  ===============================================================================
  Concerning ECC

  The EP501 only supports 1 bit ECC mode.  The EP501G1 supports both 1
  bit and 4 bit modes.  The EP501G3 supports 4 bit, 8 bit, and 12 bit.
  The NAND part normally used on ACP boards has 2K pages (supported by
  all three controllers) with 64 bytes of OOB.  For a 2K page, 1 bit
  ECC uses 12 bytes, 4 bit ECC uses 32 bytes, 8 bit ECC uses 64 bytes
  and 12 bit ECC uses 80 bytes.  In order to to keep the bad block
  markers (first two bytes) and leave some OOB available for file
  systems etc., this driver only supports 1 bit ECC or 4 bit ECC.

  For now, the EP501 version will use 1 bit ECC (only option), the
  EP501G1 version will use 4 bit (for compabitility with the EP501G3)
  and the EP501G3 versions will use 4 bit (due to the amount of OOB
  required and for compatibility with the EP501G1).

  EP501

  The driver has not been tested with small page (512 byte) devices.
  The only usable option is 2K.  So, the OOB should be 64 bytes.  The
  first 2 bytes are reserved for marking bad blocks.  The last 12
  bytes are reserved for ECC.  All other bytes are free.  See
  lsi_ep501_2k_ecclayout below.

  EP501G1

  This driver has been tested with 2K and 4K page sizes using 1 bit
  and 4 bit ECC.
  ===============================================================================
  ===============================================================================
*/

static int correct_cecc = 1;

void
set_correct_cecc(int value) {
	correct_cecc = value;
}

static int display_cecc = 1;

void
set_display_cecc(int value) {
	display_cecc = value;
}

static int display_ucecc = 1;

void
set_display_ucecc(int value) {
	display_ucecc = value;
}

static uint8_t scan_ff_pattern[] = {0xff, 0xff};

#if defined(EP501)

static struct nand_ecclayout lsi_2k_1bit_ecclayout = {
	.eccbytes = 12,
	.eccpos = {	       
		52, 53, 54, 55, 56, 57, 
		58, 59, 60, 61, 62, 63},
	.oobfree = {{2, 50}}
};

static struct nand_ecclayout lsi_4k_1bit_ecclayout = {
	.eccbytes = 24,
	.eccpos = {	       
		52, 53, 54, 55, 56, 57, 
		58, 59, 60, 61, 62, 63},
	.oobfree = {{2, 50}}
};

#endif

#if defined(EP501G1) || defined(EP501G3)

static struct nand_ecclayout lsi_2k_4bit_ecclayout = {
	.eccbytes = 32,
	.eccpos = {
		32, 33, 34, 35, 36, 37, 38, 39,
		40, 41, 42, 43, 44, 45, 46, 47,
		48, 49, 50, 51, 52, 53, 54, 55,
		56, 57, 58, 59, 60, 61, 62, 63},
	.oobfree = {{6,26}}
};

static struct nand_bbt_descr lsi_2k_4bit_bbt_descr = {
#ifdef ACP_EMU
	.options = NAND_BBT_SCAN2NDPAGE,
#else
	.options = NAND_BBT_SCANEMPTY |	NAND_BBT_SCANALLPAGES | \
	NAND_BBT_SCAN2NDPAGE,
#endif
        .offs = 5,
        .len = 1,
        .pattern = scan_ff_pattern
};

#if defined(EP501G3)
static struct nand_ecclayout lsi_4k_4bit_ecclayout = {
	.eccbytes = 64,
	.eccpos = {
		160,  161,  162,  163,  164,  165,  166,  167,
		168,  169,  170,  171,  172,  173,  174,  175,
		176,  177,  178,  179,  180,  181,  182,  183,
		184,  185,  186,  187,  188,  189,  190,  191,
		192,  193,  194,  195,  196,  197,  198,  199,
		200,  201,  202,  203,  204,  205,  206,  207,
		208,  209,  210,  211,  212,  213,  214,  215,
		216,  217,  218,  219,  220,  221,  222,  223
	},
	.oobfree = {{2, 62}}
};
#endif 

#if defined(EP501G1)
static struct nand_ecclayout lsi_4k_4bit_ecclayout = {
	.eccbytes = 64,
	.eccpos = {
		64,  65,  66,  67,  68,  69,  70,  71,
		72,  73,  74,  75,  76,  77,  78,  79,
		80,  81,  82,  83,  84,  85,  86,  87,
		88,  89,  90,  91,  92,  93,  94,  95,
		96,  97,  98,  99, 100, 101, 102, 103,
		104, 105, 106, 107, 108, 109, 110, 111,
		112, 113, 114, 115, 116, 117, 118, 119,
		120, 121, 122, 123, 124, 125, 126, 127
	},
	.oobfree = {{2, 62}}
};
#endif 

static struct nand_bbt_descr lsi_4k_4bit_bbt_descr = {
#ifdef ACP_EMU
	.options = 0,
#else
	.options =  NAND_BBT_SCANEMPTY ,
#endif
        .offs = 0,
        .len = 2,
        .pattern = scan_ff_pattern
};

#endif

#if defined(EP501G3)

static struct nand_ecclayout lsi_8k_4bit_ecclayout = {
	.eccbytes = 128,
	.eccpos = {
		128, 129, 130, 131, 132, 133, 134, 135,
		136, 137, 138, 139, 140, 141, 142, 143,
		144, 145, 146, 147, 148, 149, 150, 151,
		152, 153, 154, 155, 156, 157, 158, 159,
		160, 161, 162, 163, 164, 165, 166, 167,
		168, 169, 170, 171, 172, 173, 174, 175,
		176, 177, 178, 179, 180, 181, 182, 183,
		184, 185, 186, 187, 188, 189, 190, 191,
		192, 193, 194, 195, 196, 197, 198, 199,
		200, 201, 202, 203, 204, 205, 206, 207,
		208, 209, 210, 211, 212, 213, 214, 215,
		216, 217, 218, 219, 220, 221, 222, 223,
		224, 225, 226, 227, 228, 229, 230, 231,
		232, 233, 234, 235, 236, 237, 238, 239,
		240, 241, 242, 243, 244, 245, 246, 247,
		248, 249, 250, 251, 252, 253, 254, 255
	},
	.oobfree = {{2, 126}}
};

#endif

/*
  ------------------------------------------------------------------------------
  lsi_nand_select_chip
*/

static void
lsi_nand_select_chip(struct mtd_info *mtd, int chip)
{
	DEBUG_PRINT( "chip=%d\n", chip );
}

/*
  ------------------------------------------------------------------------------
  lsi_nand_cmd_ctrl
*/

static void
lsi_nand_cmd_ctrl(struct mtd_info *mtd, int cmd, unsigned int ctrl)
{
	struct nand_chip *chip = mtd->priv;

	DEBUG_PRINT("cmd=0x%x\n", cmd);
	WRITEL(cmd, (chip->IO_ADDR_W + EP501_NAND_CMD_REG));

	return;
}

/*
  ------------------------------------------------------------------------------
  lsi_nand_dev_ready
*/

static int
lsi_nand_dev_ready(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd->priv;    
	int ready = 0;

	DEBUG_PRINT("\n");
	ready =	READL(chip->IO_ADDR_R + EP501_NAND_INTR_STATUS_REG) &
		NAND_STATUS_TRUE_READY;
	DEBUG_PRINT("ready=%d\n", ready);

	return ready;
}

/*
  ------------------------------------------------------------------------------
  lsi_nand_cmdfunc
*/

static void
lsi_nand_cmdfunc(struct mtd_info *mtd,
		 unsigned int command, int column, int page)
{
	register struct nand_chip *chip = mtd->priv;
	unsigned int status = 0;

	DEBUG_PRINT("command=0x%x, column = 0x%x, page = %d\n",
		    command, column, page);
	command &= 0xff;

	/* Emulate NAND_CMD_READOOB */
	if (command == NAND_CMD_READOOB) {
		column += mtd->writesize;
		command = NAND_CMD_READ0;
	}

	/* return if unhandled command is issued */
	if (command != NAND_CMD_READ0 &&
	    command != NAND_CMD_SEQIN &&
	    command != NAND_CMD_ERASE1 &&
	    command != NAND_CMD_STATUS &&
	    command != NAND_CMD_READID &&
	    command != NAND_CMD_RESET &&
	    command != NAND_CMD_START_ECC_READ &&
	    command != NAND_CMD_PAGEPROG &&
	    command != NAND_CMD_ERASE2) {
		ERROR_PRINT("Unhandled Command 0x%x, Page 0x%x, Column 0x%x\n",
			    command, page, column);
		return;
	}
    
	/* Command latch cycle */
	lsi_nand_cmd_ctrl(mtd, command, 0);

	if (column != -1 || page != -1) {
		unsigned long index = 0;
		unsigned long extended_index = 0;

		/*
		  Since the ACP uses 8 bit device access, only that
		  mode is supported.
		*/

#if defined(EP501)
		/* column number */
		if (column != -1)
			index = column & 0xfff;

		/* page and block number */
		if (page != -1)
			index += ((page & 0x7ffff) << 12);
#elif defined(EP501G1)
		/* column number */
		if (-1 != column) {
			switch (mtd->writesize) {
			case 512:
				index |= (column & 0x1ff);
				break;
			case 2048:
				index |= (column & 0xfff);
				break;
			case 4096:
				index |= (column & 0x1fff);
				break;
			default:
				break;
			}
		}

		/* page and block number */
		if (-1 != page) {
			switch (mtd->writesize) {
			case 512:
				index |= (page & 0x7fffff) << 9;
				break;
			case 2048:
				index |= (page & 0xfffff) << 12;
				extended_index |= (page & 0xfff00000);
				break;
			case 4096:
				index |= (page & 0x7ffff) << 13;
				extended_index |= (page & 0xfff80000);
				break;
			default:
				break;
			}
		}
#elif defined(EP501G3)
		/* column number */
		if (-1 != column) {
			switch (mtd->writesize) {
			case 2048:
				index |= (column & 0xfff);
				break;
			case 4096:
				index |= (column & 0x1fff);
				break;
			case 8192:
				index |= (column & 0x3fff);
				break;
			default:
				break;
			}
		}

		/* page and block number */
		if (-1 != page) {
			switch (mtd->writesize) {
			case 2048:
				index |= (page & 0xfffff) << 12;
				extended_index |= (page & 0xfff00000);
				break;
			case 4096:
				index |= (page & 0x7ffff) << 13;
				extended_index |= (page & 0xfff80000);
				break;
			case 8192:
				index |= (page & 0x3ffff) << 14;
				extended_index |= (page & 0xfffc0000);
				break;
			default:
				break;
			}
		}
#else
#error "Unsupported ACP System Type!"
#endif

		/* write index reg */
		WRITEL(index,
		       chip->IO_ADDR_W + EP501_NAND_INDEX_REG);

		/* write ext index reg */
		WRITEL(extended_index,
		       chip->IO_ADDR_W + EP501_NAND_EXT_INDEX_REG);
	}

	/* for read command, send 0xe0 so data is populated */
	if(command == NAND_CMD_READ0) {
		lsi_nand_cmd_ctrl(mtd, NAND_CMD_RNDOUTSTART, 0);

		do {
			status = READL(LSI_NAND_PECC_BUSY_REGISTER);
		} while(0 != (status & LSI_NAND_PECC_BUSY_MASK));

		/* wait until CHIP_BUSY goes low */
		do {
			status = lsi_nand_dev_ready(mtd);
		} while(!status);
	} else if(command == NAND_CMD_STATUS) {
		udelay(chip->chip_delay);
	}

	return;
}

/*
  ------------------------------------------------------------------------------
  lsi_nand_read_buf
*/

static void
lsi_nand_read_buf(struct mtd_info *mtd, uint8_t *buf, int len)
{
	int i = 0;
	struct nand_chip *chip = mtd->priv;
	uint32_t *p = (uint32_t *)buf;

	DEBUG_PRINT( "\n" );

	if (LSI_LOGIO_ENABLED())
		printf("Reading NAND Buffer (len=%d)...\n", len);

	for (i = 0; i < (len >> 2); i++) {
            p[i] = readl(chip->IO_ADDR_R);
	}

	return;
}

/*
  ------------------------------------------------------------------------------
  lsi_nand_write_buf
*/

static void
lsi_nand_write_buf(struct mtd_info *mtd, const uint8_t *buf, int len)
{
	int i = 0;
	struct nand_chip *chip = mtd->priv;
	uint32_t *p = (uint32_t *)buf;

	DEBUG_PRINT( "\n" );

	if (LSI_LOGIO_ENABLED()) {
		printf("Writing NAND Buffer (len=%d)...\n", len);
	}

	for (i = 0; i < (len >> 2); i++){
		writel(p[i], chip->IO_ADDR_W);
	}

	return;
}

/*
  ------------------------------------------------------------------------------
  lsi_nand_verify_buf
*/

static int
lsi_nand_verify_buf(struct mtd_info *mtd, const uint8_t *buf, int len)
{
	int i;
	struct nand_chip *chip = mtd->priv;
	uint32_t *p = (uint32_t *)buf;

	DEBUG_PRINT( "\n" );

	for (i = 0; i < (len >> 2); i++) {
		udelay(chip->chip_delay);
		if (p[i] != READL(chip->IO_ADDR_R))
			return -EFAULT;
	}

	return 0;
}

/*
  ------------------------------------------------------------------------------
  lsi_nand_read_status
*/

static int
lsi_nand_read_status(struct mtd_info *mtd)
{    
	struct nand_chip *chip = mtd->priv;

	DEBUG_PRINT( "\n" );
	lsi_nand_cmd_ctrl(mtd, NAND_CMD_STATUS, 0);

	return (READL(chip->IO_ADDR_R + EP501_NAND_STATUS0_REG) & 0xff);
}

/*
  ------------------------------------------------------------------------------
  lsi_nand_waitfunc
*/

static int
lsi_nand_waitfunc(struct mtd_info *mtd, struct nand_chip *chip)
{
	int status;

	DEBUG_PRINT( "\n" );

	do {
		status = READL(LSI_NAND_PECC_BUSY_REGISTER);
	} while (0 != (status & LSI_NAND_PECC_BUSY_MASK));

	while (!lsi_nand_dev_ready(mtd))
		;

	do {
		status = lsi_nand_read_status(mtd);
	} while (0 == (status & NAND_STATUS_READY));

	if (status & NAND_STATUS_FAIL) {
		printf("Failed for index 0x%x/0x%x: 0x%x\n",
		       READL(chip->IO_ADDR_R + EP501_NAND_INDEX_REG),
		       READL(chip->IO_ADDR_W + EP501_NAND_EXT_INDEX_REG),
		       status);
	}

	DEBUG_PRINT("status=%d\n", status);

	return status;
}

/*
  ------------------------------------------------------------------------------
  lsi_nand_ecc_hwctl

  Hardware ECC is always enabled.
*/

static void
lsi_nand_ecc_hwctl(struct mtd_info *mtd, int mode)
{
	DEBUG_PRINT( "\n" );
	return;
}

/*
  ------------------------------------------------------------------------------
  lsi_nand_ecc_calculate
*/

static int
lsi_nand_ecc_calculate(struct mtd_info *mtd,
		       const uint8_t *dat, uint8_t *ecc_code)
{
	struct nand_chip *chip = mtd->priv;
	int cmd;
	int state = 0;

	DEBUG_PRINT( "\n" );

	/* get the current operation by reading the cmd register */
	cmd = READL(chip->IO_ADDR_R + EP501_NAND_CMD_REG);

	/* start ECC calculation */
	if(cmd == NAND_CMD_RNDOUTSTART) {
		chip->cmdfunc(mtd, NAND_CMD_START_ECC_READ, -1, -1);
		state = FL_READING;
	} else if(cmd == NAND_CMD_SEQIN) {
		chip->cmdfunc(mtd, NAND_CMD_PAGEPROG, -1, -1);
		state = FL_WRITING;
	}

	/* wait for PECC_BUSY to go down */
	return chip->waitfunc(mtd, chip);
}

/*
  ------------------------------------------------------------------------------
  lsi_nand_ecc_correct
*/

static int
lsi_nand_ecc_correct(struct mtd_info *mtd,
		     uint8_t *dat, uint8_t *read_ecc, uint8_t *calc_ecc)
{
	DEBUG_PRINT( "\n" );
	return 0;
}

#if defined(EP501G1) || defined(EP501G3)
#if defined(ACP_NAND_4BIT_ECC)

static short *a_to_i;
static short *i_to_a;
static short **err_loc_ply;

static void
generate(short *alpha_of, short *index_of)
{
	int i;
	int gg = 0x5af;

	alpha_of[0] = 1;

	for (i = 1; i < 8192; ++i) {
		int value;

		value = (alpha_of[(i - 1)] << 1);

		if (0 != ((alpha_of[(i - 1)]) & 0x1000)) {
			alpha_of[i] = ((value ^ gg) & 0x1fff);
		} else {
			alpha_of[i] = (value & 0x1fff);
		}

		if (8191 == i)
			alpha_of[i] = 0;
	}

	for (i = 0; i < 8191; ++i) {
		index_of[alpha_of[i]] = i;
	}

	index_of[alpha_of[8191]] = -1;

	return;
}

/*
  ----------------------------------------------------------------------
  fix_section

  Based on example code from Eureka (the NAND controller manufacturer).

  err_loc_ply, at almost 40k, is a bit much for the U-Boot stack.  It
  gets allocated during initialization.
*/

static int
fix_section(struct mtd_info *mtd, int page, int section, unsigned long offset,
	    void *data, short *syndromes_in)
{
	int i, j, elp_sum;
	short syndromes[9];
	int Matrix_a[11];
	int Matrix_b[11];
	int Matrix_c[12];
	int Element[7];
	int alpha;
	int temp_index;
	int data_location, rev_location;
	int result_byte, result_bit;
	int err_location[20];
	int err_count;
	int d_flg;
	int block_length, data_length;

	if (LSI_LOGIO_ENABLED()) {
		unsigned char *in = data;

		printf("offset=%lu\n", offset);

		for (i = 0; i < 32; ++i) {
			puts("        ");

			for (j = 0; j < 16; ++j) {
				printf("%02x%s", *in++, j == 7 ? "  " : " ");
			}

			puts("\n");
		}
	}
				
	/* correct 4 bits in 512 bytes */
	data_length = 4096;
	block_length = 8191;

	/* Clear arrays.*/
	memset((void *)Matrix_a, 0, (sizeof(int) * 11));
	memset((void *)Matrix_b, 0, (sizeof(int) * 11));
	memset((void *)Matrix_c, 0, (sizeof(int) * 12));
	memset((void *)Element, 0, (sizeof(int) * 7));
	memset((void *)err_location, 0, (sizeof(int) * 20));

	/* If there are no errors, just return.	*/
	j = 0;

	for (i = 0; i < 8; ++i) {
		if (0 != syndromes_in[i]) {
			j = 1;
			break;
		}
	}

	if (0 == j)
		return 0;

	/*
	  Decode.
	*/

	memcpy((void *)syndromes, (void *)syndromes_in, sizeof(short) * 9);
	d_flg = 0;

	/* Initialise table entries. */
	for (i = 0; i < 8; i++)
		syndromes[i] = i_to_a[syndromes[i]];

	Matrix_c[0] = 0;
	Matrix_c[1] = syndromes[0];
	err_loc_ply[0][0] = 1;
	err_loc_ply[1][0] = 1;
	for (i = 1; i < 8; i++) {
		err_loc_ply[0][i] = 0;
		err_loc_ply[1][i] = 0;
	}
	Matrix_a[0] = 0;
	Matrix_a[1] = 0;
	Matrix_b[0] = -1;
	Matrix_b[1] = 0;
	alpha = -1;

	do {
		// skip even loops
		alpha += 2;

		if (Matrix_c[alpha] != -1) {
			temp_index = alpha - 2;

			if (temp_index<0)
				temp_index=0;

			while ((Matrix_c[temp_index] == -1) && (temp_index > 0))
				temp_index=temp_index-2;

			if (temp_index < 0)
				temp_index = 0;

			if (temp_index > 0) {
				j = temp_index;

				do {
					j = j-2;

					if (j < 0)
						j = 0;

					if ((Matrix_c[j] != -1) &&
					    (Matrix_b[temp_index] < Matrix_b[j]))
						temp_index = j;
				} while (j > 0);
			}

			if (Matrix_a[alpha] >
			    Matrix_a[temp_index] + alpha - temp_index)
				Matrix_a[alpha + 2] = Matrix_a[alpha];
			else
				Matrix_a[alpha + 2] = Matrix_a[temp_index] +
					alpha - temp_index;

			for (i = 0; i < 8; ++i) {
				err_loc_ply[alpha + 2][i] = 0;
			}

			for (i = 0; i <= Matrix_a[temp_index]; i++) {
				if (err_loc_ply[temp_index][i] != 0)
					err_loc_ply[alpha + 2]
						[i + alpha - temp_index] =
						a_to_i[(Matrix_c[alpha] + 
							block_length -
							Matrix_c[temp_index] +
							i_to_a[err_loc_ply
							       [temp_index]
							       [i]]) %
						       block_length];
			}

			for (i = 0; i <= Matrix_a[alpha]; i++) {
				err_loc_ply[alpha + 2][i] ^=
					err_loc_ply[alpha][i];
			}
		} else {
			Matrix_a[alpha + 2] = Matrix_a[alpha];

			for (i = 0; i <= Matrix_a[alpha]; i++) {
				err_loc_ply[alpha + 2][i] =
					err_loc_ply[alpha][i];
			}
		}

		Matrix_b[alpha + 2] = alpha+1 - Matrix_a[alpha + 2];

		// Form (alpha+2)th discrepancy.
		if (alpha < 8) {
			if (syndromes[alpha + 1] != -1) {
				Matrix_c[alpha + 2] =
					a_to_i[syndromes[alpha + 1]];
			} else {
				Matrix_c[alpha + 2] = 0;
			}

			for (i = 1; i <= Matrix_a[alpha + 2]; i++) {
				if ((syndromes[alpha + 1 - i] != -1) &&
				    (err_loc_ply[alpha + 2][i] != 0))
					Matrix_c[alpha + 2] ^=
						a_to_i[(syndromes[alpha +
								  1 - i] +
							i_to_a[err_loc_ply
							       [alpha + 2]
							       [i]]) %
						       block_length];
			}

			Matrix_c[alpha + 2] = i_to_a[Matrix_c[alpha + 2]];
		}
	} while ((alpha < 7) && (Matrix_a[alpha + 2] <= 4));

	alpha=alpha+2;
	Matrix_a[7] = Matrix_a[alpha];

	if (Matrix_a[7] <= 4) {
		for (i = 1; i <= Matrix_a[7]; i++) {
			Element[i] = i_to_a[err_loc_ply[alpha][i]];
		}

		err_count = 0 ;

		for (i = 1; i <= block_length; i++) {
			elp_sum = 1 ;
			for (j = 1; j <= Matrix_a[7]; j++)
				if (Element[j] != -1) {
					Element[j] = (Element[j] + j) %
						block_length ;
					elp_sum ^= a_to_i[Element[j]] ;
				}

			if (!elp_sum) {
				err_location[err_count] = block_length - i ;
				err_count++ ;
			}
		}

		if (err_count == Matrix_a[7]) {
			d_flg = 1 ;
		}
	}

	if (d_flg == 0) {
		/* Too many bit errors to decode. */
		++mtd->ecc_stats.failed;
		return -1;
	}

	for (i=0; i<err_count; i++) {
		if (err_location[i] >= 52)
			data_location = err_location[i] - 52;
		else
			data_location = err_location[i] + data_length;

		if (data_location <= 4095) {
			rev_location = 4095 - data_location;
			result_bit = rev_location%8;
			result_byte = (rev_location - result_bit)/8;

			if (0 != display_cecc) {
				printf("Corrected ECC Error: page 0x%x "
				       "offset 0x%lx byte 0x%x bit %d\n",
				       page, offset, result_byte, result_bit);
			}

			if (0 != correct_cecc) {
				++mtd->ecc_stats.corrected;
				result_byte =
					(result_byte & 0xfffffffc) |
					((result_byte & 0x3) ^ 0x3);
				*((unsigned char *)(data + result_byte)) ^=
					(1 << result_bit);
			}
		} else {
			/*
			  This indicates a bit flipped in the
			  checksums, and will get fixed by the
			  controller.  It DOES count toward the number
			  of error bits that can be corrected in a
			  section, so update the statistics.
			 */

			++mtd->ecc_stats.corrected;

			rev_location = 4147 - data_location;
			result_bit = rev_location%8;
			result_byte = (rev_location - result_bit)/8;

			if (0 != display_cecc) {
				printf("BCH: page=0x%x section=0x%x "
				       "data_location=0x%x rev_location=0x%x "
				       "byte=%d bit=%d\n",
				       page, section, data_location,
				       rev_location, result_byte, result_bit);
			}
		}
	}

	return 0;
}

#endif /* ACP_NAND_4BIT_ECC */
#endif /* EP501G1 || EP501G3 */

#if defined(EP501G1) || defined(EP501G3)

/*
  ----------------------------------------------------------------------
  is_page_erased
*/

static int
is_page_erased(struct nand_chip *chip)
{
	int i;
	unsigned char *data;
	int is_blank;
	struct nand_ecclayout *ecc;

	ecc = chip->ecc.layout;
	data = chip->oob_poi;
	is_blank = 1;

	for (i = 0; i < ecc->eccbytes; ++i) {
		if (0xff != data[ecc->eccpos[i]]) {
			is_blank = 0;
			break;
		}
	}

	return is_blank;
}

#endif

/*
  ------------------------------------------------------------------------------
  report_ecc_errors
*/

#if defined(EP501)

static int
report_ecc_errors(struct mtd_info *mtd, struct nand_chip *chip,
		  uint8_t *buffer, int page)
{
	int rc = 0;
	unsigned long ecc_status;
	typedef struct page_wise_ecc_status_st {
		unsigned bit    :3;
		unsigned byte   :9;
		unsigned status :2;
		unsigned rsvd   :18;
	} page_wise_ecc_status_t;
	page_wise_ecc_status_t *page_wise_ecc_status =
		(page_wise_ecc_status_t *)&ecc_status;
	unsigned long offset;
	int i;

	DEBUG_PRINT("page=0x%x\n", page);

	/* Make sure ECC is enabled. */
	if (LSI_NAND_ECC_MODE_NONE == ecc_mode)
		goto report_ecc_errors_end;

	for (i = 0; i < (mtd->writesize >> 9); i++) {
		/*
		  Read the status register once for each section (512 bytes).
		*/
		ecc_status = READL(chip->IO_ADDR_R + EP501_NAND_PECC_REG);
		offset = (i << 9) + page_wise_ecc_status->byte;

		switch (page_wise_ecc_status->status) {
		case 0:
			break;
		case 1:
			if (0 != display_cecc)
				ERROR_PRINT("Corrected ECC Error: "
					    "Offset 0x%08x Bit %d\n",
					    (page * mtd->writesize) + offset,
					    page_wise_ecc_status->bit);

			buffer[offset] ^= (1 << page_wise_ecc_status->bit);
			break;
		case 2:
			ERROR_PRINT("Uncorrectable ECC Error: "
				    "Offset 0x%08x Bit %d\n",
				    (page * mtd->writesize) + offset,
				    page_wise_ecc_status->bit);
			rc = -1;
			break;
		default:
			ERROR_PRINT("Unexpected Error!\n");
			rc = -1;
			break;
		}
	}

	return rc;
}

#elif defined(EP501G1)

static int
report_ecc_errors(struct mtd_info *mtd, struct nand_chip *chip,
		  uint8_t *buffer, int page)
{
	int rc = 0;
	unsigned long bch_status;
	int is_blank = 1;
	int i;

	DEBUG_PRINT("page=0x%x\n", page);

	/* Make sure ECC is enabled. */
	if (LSI_NAND_ECC_MODE_OFF == ecc_mode) {
		DEBUG_PRINT("ECC is not enabled.\n");
		goto report_ecc_errors_end;
	}

	/* If there are no errors, return. */
	bch_status = READL(chip->IO_ADDR_R + EP501G1_NAND_BCH_STATUS);

	/* No ECC errors, return... */
	if (0 == bch_status) {
		DEBUG_PRINT("No ECC errors.\n");
		goto report_ecc_errors_end;
	}

	if (buffer == NULL) {
		DEBUG_PRINT("Buffer is NULL.\n");
		goto report_ecc_errors_end;
	}

	/* Ignore fully erased blocks. */
	is_blank = is_page_erased(chip);

	if (0 != is_blank)
		goto report_ecc_errors_end;

#if !defined(ACP_NAND_4BIT_ECC)

	if (0 != display_cecc) {
		static int stage2_ecc_displayed = 0;

		if (0 == stage2_ecc_displayed) {
			printf("ECC Error: No Correction in the 2nd Stage.\n");
			stage2_ecc_displayed = 1;
		}
	}

	rc = -1;

#else

	int num_sections;
	int section;
	int syndrome;
	short syndromes[16][8];

	num_sections = (mtd->writesize / 512);

	/* Read the syndrome registers and split them into syndromes. */
	for (section = 0; section < num_sections; ++section) {
		unsigned long address;
		unsigned long value;

		address = EP501G1_NAND_SYN_R12_S0 + (section * 0x10);

		for (syndrome = 0; syndrome < 8; syndrome += 2) {
			value = READL(chip->IO_ADDR_R + address +
				      (syndrome * 2));
			syndromes[section][syndrome] = (value & 0x1fff);
			syndromes[section][syndrome + 1] =
				((value & 0x1fff0000) >> 16);
		}
	}

	/* Debug output (BCH status register and syndromes). */
#if 0
	printf("BCH Status Register: 0x%02lx\n", bch_status);

	for (section = 0; section < num_sections; ++section) {
		printf("Syndromes, Section %d: ", section);

		for (syndrome = 0;
		     syndrome < (num_sections * 2); ++syndrome) {
			printf("0x%04lx ", syndromes[section][syndrome]);
		}

		printf("\n");
	}
#endif

	DEBUG_PRINT("num_sections=%d bch_status=0x%x\n",
		    num_sections, bch_status);

	for (i = 0; i < num_sections; ++i) {
		if ((1 << i) == (bch_status & (1 << i))) {
			unsigned long offset;

			offset = (page * mtd->writesize) + (512 * i);
			rc = fix_section(mtd, page, i, offset,
					 (void *)(buffer + (512 * i)),
					 (int *)syndromes[i]);

			if ((0 != display_ucecc) && (-1 == rc))
				printf("Uncorrectable ECC Error: Page %d\n",
				       page);
		}
	}

#endif /* ACP_NAND_4BIT_ECC */

 report_ecc_errors_end:
	return rc;
}

#elif defined(EP501G3)

static int
report_ecc_errors(struct mtd_info *mtd, struct nand_chip *chip,
		  uint8_t *buffer, int page)
{
	int rc = 0;
	unsigned long value;
	unsigned long bch_status;
	int i;
	int is_blank = 1;

	DEBUG_PRINT("page=0x%x\n", page);

	/* Make sure ECC is enabled. */
	if (LSI_NAND_ECC_MODE_OFF == ecc_mode) {
		DEBUG_PRINT("ECC is not enabled!\n");
		goto report_ecc_errors_end;
	}

	/* Verify 4-bit mode in the EP501G3 case. */
	value = (READL(chip->IO_ADDR_R + EP501_NAND_CONFIG_REG) & 0x1800) >> 11;

	if (1 != value) {
		printf("Only 4-Bit ECC is supported.\n");
		rc = -1;
		goto report_ecc_errors_end;
	}

	/* If there are no errors, return. */
	bch_status = READL(chip->IO_ADDR_R + EP501G1_NAND_BCH_STATUS);

	if (0 == bch_status) {
		DEBUG_PRINT("No errors in the BCH_STATUS register.\n");
		goto report_ecc_errors_end;
	}

	if (buffer == NULL) {
		DEBUG_PRINT("buffer is NULL\n");
		goto report_ecc_errors_end;
	}

	/* Ignore fully erased blocks. */
	is_blank = is_page_erased(chip);

	if (0 != is_blank)
		goto report_ecc_errors_end;

#if !defined(ACP_NAND_4BIT_ECC)

	unsigned long interrupt_status;

	interrupt_status = READL(chip->IO_ADDR_R + EP501G3_NAND_INTR_STATUS_REG);

	if (0x40 == (interrupt_status & 0x40)) {
		if (0 != display_cecc) {
			printf("ECC Error(s): "
			       "No Correction in the 2nd Stage.\n");
			display_cecc = 0;
		}

		interrupt_status &= ~0x40;
		WRITEL(interrupt_status,
		       chip->IO_ADDR_R + EP501G3_NAND_INTR_STATUS_REG);
		rc = -1;
	}

#else
	int num_sections;
	int section;
	int syndrome;
	short syndromes[16][8];

	num_sections = (mtd->writesize / 512);

	/* Read the syndrome registers and split them into syndromes. */
	for (section = 0; section < num_sections; ++section) {
		unsigned long address;
		unsigned long value;

		address = EP501G1_NAND_SYN_R12_S0 + (section * 0x10);

		for (syndrome = 0; syndrome < 8; syndrome += 2, address += 4) {
			value = READL(chip->IO_ADDR_R + address);
			syndromes[section][syndrome] =
				(short)(value & 0x1fff);
			syndromes[section][syndrome + 1] =
				(short)((value & 0x1fff0000) >> 16);
		}
	}

	/* Debug output (BCH status register and syndromes). */
#if 0
	printf("Page 0x%x BCH Status: 0x%02lx\n", page, bch_status);

	for (section = 0; section < num_sections; ++section) {
		printf("Syndromes, Section %d: ", section);

		for (syndrome = 0;
		     syndrome < (num_sections * 2); ++syndrome) {
			printf("0x%04x ",
			       (syndromes[section][syndrome] & 0x1fff));
		}

		printf("\n");
	}
#endif

	for (i = 0; i < num_sections; ++i) {
		if ((1 << i) == (bch_status & (1 << i))) {
			unsigned long offset;

			offset = (page * mtd->writesize) + (512 * i);
			rc = fix_section(mtd, page, i, offset,
					 (void *)(buffer + (512 * i)),
					 (short *)syndromes[i]);

			if ((0 != display_ucecc) && (-1 == rc))
				printf("Uncorrectable ECC Error: Page %d\n",
				       page);
		}
	}

#endif /* ACP_NAND_4BIT_ECC */

 report_ecc_errors_end:
	return rc;
}

#else
#error "Unsupported NAND Controller!"
#endif

/*
  ------------------------------------------------------------------------------
  lsi_nand_ecc_read_page
*/

static int
lsi_nand_ecc_read_page(struct mtd_info *mtd,
		       struct nand_chip *chip, uint8_t *buf, int page)
{
	DEBUG_PRINT("ecc_read_page: page = %d\n", page);

	/* read the page */
	chip->read_buf(mtd, buf, mtd->writesize);		

	/* read oob data */
	chip->read_buf(mtd, chip->oob_poi, mtd->oobsize);

	/* start ECC calculations */
	chip->ecc.calculate(mtd, NULL, NULL);

	/* Read the ECC Status and see if there were any errors */
	report_ecc_errors(mtd, chip, buf, page);

	/* cmd to controller to turn off CE */
	chip->cmd_ctrl(mtd, nand_cmd_ce_off, 0);

	chip->waitfunc(mtd, chip);
    
	return 0;
}

/*
  ------------------------------------------------------------------------------
  lsi_nand_ecc_read_oob
*/

int
lsi_nand_ecc_read_oob(struct mtd_info *mtd, struct nand_chip *chip,
		      int page, int sndcmd)
{
	DEBUG_PRINT( "\n" );

	if (sndcmd) {
		chip->cmdfunc(mtd, NAND_CMD_READOOB, 0, page);
		sndcmd = 0;
	}
    
	/* read oob data */
	chip->read_buf(mtd, chip->oob_poi, mtd->oobsize);
    
	if (LSI_NAND_ECC_MODE_OFF != ecc_mode) {
		/* start ECC calculations */
		chip->ecc.calculate(mtd, NULL, NULL);

		/* Read the ECC Status and see if there were any errors */
		report_ecc_errors(mtd, chip, NULL, page);
	}

	/* cmd to controller to turn off CE */
	chip->cmd_ctrl(mtd, nand_cmd_ce_off, 0);
    
	chip->waitfunc(mtd, chip);

	return sndcmd;
}

/*
  ------------------------------------------------------------------------------
  lsi_nand_ecc_write_page
*/


static void
lsi_nand_ecc_write_page(struct mtd_info *mtd, struct nand_chip *chip,
			const uint8_t *buf)
{
	int i, eccsize = chip->ecc.size;
	int eccbytes = chip->ecc.bytes;
	int eccsteps = chip->ecc.steps;
	uint8_t *ecc_calc = chip->buffers->ecccalc;
	int ecctotal = chip->ecc.total;
	const uint8_t *p = buf;

	for (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize) {
		chip->ecc.hwctl(mtd, NAND_ECC_WRITE);
		chip->write_buf(mtd, p, eccsize);
		chip->write_buf(mtd, chip->oob_poi, ecctotal);
		if (LSI_NAND_ECC_MODE_OFF != ecc_mode) {
			chip->ecc.calculate(mtd, p, &ecc_calc[i]);
		} else {
			chip->cmdfunc(mtd, NAND_CMD_PAGEPROG, -1, -1);
			chip->waitfunc(mtd, chip);
		}
	}

	/* cmd to controller to turn off CE */
	chip->cmd_ctrl(mtd, nand_cmd_ce_off, 0);
}

/*
  ------------------------------------------------------------------------------
  lsi_nand_ecc_write_oob
*/

static int
lsi_nand_ecc_write_oob(struct mtd_info *mtd, struct nand_chip *chip, int page)
{
	int rc;
	int ecctotal = chip->ecc.total;	

	DEBUG_PRINT("page=0x%x\n", page);

	/* start OOB write */
	chip->cmdfunc(mtd, NAND_CMD_SEQIN, mtd->writesize, page);

	/*  Write the oob. Note that the last 12 bytes are used by HW ECC. */
	chip->write_buf(mtd, chip->oob_poi, ecctotal);


	if (LSI_NAND_ECC_MODE_OFF != ecc_mode) {
		/* calculate ECC */
		chip->ecc.calculate(mtd, NULL, NULL);
	}

	/* cmd to controller to turn off CE */
	chip->cmd_ctrl(mtd, nand_cmd_ce_off, 0);

	rc = (chip->dev_ready(mtd) & NAND_STATUS_FAIL) ? -EIO : 0;
	DEBUG_PRINT("ready & NAND_STATUS_FAIL = %d\n", rc);

	return rc;
}

/*
  ------------------------------------------------------------------------------
  lsi_nand_set_config_501
*/

#if defined(EP501)
static int
lsi_nand_set_config_501(struct mtd_info *mtd, struct nand_chip *chip)
{
	unsigned long config = 0;
	unsigned long mbits;

	mbits = ((chip->chipsize >> 20) * 8);

	/* The EP501 only supports 512 and 2k page sizes. */
	if (512 != mtd->writesize && 2048 != mtd->writesize)
		return -1;

	while (64 < mbits) {
		++config; /* 0b000=64Mbit, 0b001=128Mbit, etc. */
		mbits >>= 1;
	}

	if (512 < mtd->writesize)
		config |= 0x100; /* large block */

	config |= 0x200;	/* not write protected */
	chip->ecc.layout = &lsi_2k_1bit_ecclayout;
	chip->ecc.size = mtd->writesize;
	chip->ecc.bytes = chip->ecc.layout->eccbytes;
	DEBUG_PRINT("config=0x%lx\n", config);
	WRITEL(config, chip->IO_ADDR_W + EP501_NAND_CONFIG_REG);

	return 0;
}

/*
  ------------------------------------------------------------------------------
  lsi_nand_set_config_501g1
*/

#elif defined(EP501G1)
static int
lsi_nand_set_config_501g1(struct mtd_info *mtd, struct nand_chip *chip)
{
	unsigned long config = 0;
	unsigned long mbits;

	mbits = ((chip->chipsize >> 20) * 8);

	/* The EP501G1 only supports 512, 2k, and 4k page sizes, */
	if (512 != mtd->writesize &&
	    2048 != mtd->writesize &&
	    4096 != mtd->writesize)
		return -1;

	/* and device sizes as follows. */
	if (512 == mtd->writesize) {
		switch (mbits) {
		case 64:                 break;
		case 128:   config |= 1; break;
		case 256:   config |= 2; break;
		case 512:   config |= 3; break;
		case 1024:  config |= 4; break;
		case 2048:  config |= 5; break;
		case 4096:  config |= 6; break;
		case 8192:  config |= 7; break;
		default:
			return -1;
			break;
		}
	} else {
		switch (mbits) {
		case 512:   config |= 3; break;
		case 1024:  config |= 4; break;
		case 2048:  config |= 5; break;
		case 4096:  config |= 6; break;
		case 8192:  config |= 7; break;
		case 16384:              break;
		case 32768: config |= 1; break;
		case 65536: config |= 2; break;
		default:
			return -1;
			break;
		}
	}

	switch (mtd->writesize) {
	case 512:
		break;
	case 2048:
		config |= 0x1 << 8;
		chip->ecc.layout = &lsi_2k_4bit_ecclayout;
		chip->badblock_pattern = &lsi_2k_4bit_bbt_descr;
		break;
	case 4096:
		config |= 0x2 << 8;
		chip->ecc.layout = &lsi_4k_4bit_ecclayout;
		chip->badblock_pattern = &lsi_4k_4bit_bbt_descr;
		break;
	default:
		return -1;
		break;
	}

	config |= 1 << 10; /* not write protected */
	config |= 1 << 11; /* 4 bit ECC */

	if (512 < mtd->writesize)
		config |= 1 << 12; /* 3 cycle row address */

	chip->ecc.size = mtd->writesize;
	chip->ecc.bytes = chip->ecc.layout->eccbytes;
	chip->ecc.total = chip->ecc.layout->eccbytes;
	DEBUG_PRINT("config=0x%lx\n", config);
	WRITEL(config, chip->IO_ADDR_W + EP501_NAND_CONFIG_REG);

	return 0;
}

/*
  ------------------------------------------------------------------------------
  lsi_nand_set_config_501g3
*/

#elif defined(EP501G3)
static int
lsi_nand_set_config_501g3(struct mtd_info *mtd, struct nand_chip *chip)
{
	unsigned long config;
	unsigned long mbits;

	mbits = ((chip->chipsize >> 20) * 8);

	/* The EP501G3 only supports 2k, 4k, and 8k page sizes, */
	if (2048 != mtd->writesize &&
	    4096 != mtd->writesize &&
	    8192 != mtd->writesize)
		return -1;

	/* and device sizes as follows. */
	if (65536 == mbits)
		config = 2;
	else if (32768 == mbits)
		config = 1;
	else if (16384 == mbits)
		config = 0;
	else if (8192 == mbits)
		config = 7;
	else if (4096 == mbits)
		config = 6;
	else if (2048 == mbits)
		config = 5;
	else if (1024 == mbits)
		config = 4;
	else if (512 == mbits)
		config = 3;
	else {
		printf("Invalid Device Size: 0x%lx\n", mbits);
		return -1;
	}

	switch (mtd->writesize) {
	case 2048:
		config |= 0x1 << 8;
		chip->ecc.layout = &lsi_2k_4bit_ecclayout;
		chip->badblock_pattern = &lsi_2k_4bit_bbt_descr;
		break;
	case 4096:
		config |= 0x2 << 8;
		chip->ecc.layout = &lsi_4k_4bit_ecclayout;
		chip->badblock_pattern = &lsi_4k_4bit_bbt_descr;
		break;
	case 8192:
		config |= 0x3 << 8;
		chip->ecc.layout = &lsi_8k_4bit_ecclayout;
		break;
	default:
		return -1;
		break;
	}

	config |= 1 << 10; /* not write protected */
	config |= 1 << 13; /* 3 cycle row address */

	/*
	  2K/4bit  - 32 bytes (8192)
	  2K/8bit  - 64 bytes (16384)
	  2K/12bit - 80 bytes (24576)
	  ...
	  8K/12bit - 320 bytes (98304)
	*/

	if (mtd->oobsize < chip->ecc.layout->eccbytes) {
		ERROR_PRINT("ECC requires %d bytes, "
			    "only %d are available.\n",
			    chip->ecc.layout->eccbytes, mtd->oobsize);
		return -1;
	}

	config |= 1 << 11; /* 4 bit ECC */
	mtd->oobavail = mtd->oobsize - chip->ecc.layout->eccbytes;
	mtd->oobavail -= (mtd->oobavail % 4);
	config |= (mtd->oobavail / 4) << 16;	
	chip->ecc.size = mtd->writesize;
	chip->ecc.bytes = chip->ecc.layout->eccbytes;
	chip->ecc.total = chip->ecc.layout->eccbytes;
	DEBUG_PRINT("config=0x%lx\n", config);
	WRITEL(config, chip->IO_ADDR_W + EP501_NAND_CONFIG_REG);

	return 0;
}
#else
#error "Unsupported ACP System Type!"
#endif

/*
  ==============================================================================
  ==============================================================================
  ==============================================================================
  Public Interface
  ==============================================================================
  ==============================================================================
  ==============================================================================
*/

/*
  ------------------------------------------------------------------------------
  lsi_nand_set_config
*/

int
lsi_nand_set_config(struct mtd_info *mtd, struct nand_chip *chip)
{
#if defined(EP501)
	return lsi_nand_set_config_501(mtd, chip);
#elif defined(EP501G1)
	return lsi_nand_set_config_501g1(mtd, chip);
#elif defined(EP501G3)
	return lsi_nand_set_config_501g3(mtd, chip);
#else
#error "Unsupported ACP System Type!"
#endif

}

/*
  ----------------------------------------------------------------------
  board_nand_init

  Called by the MTD layer...
*/

int
board_nand_init(struct nand_chip *chip)
{
	int i;

	LSI_DEBUG_DISABLE();
	LSI_LOGIO_DISABLE();
	DEBUG_PRINT( "\n" );

#if defined(ACP_NAND_4BIT_ECC)
	/*
	  Generate the "alpha of" and "index of" tables for 4 bit ECC.
	*/

	a_to_i = NULL;
	i_to_a = NULL;

	if ((NULL == (a_to_i = malloc(sizeof(short) * 8192))) ||
	    (NULL == (i_to_a = malloc(sizeof(short) * 8192)))) {
		if (NULL != a_to_i)
			free(a_to_i);

		if (NULL != i_to_a)
			free(i_to_a);

		ERROR_PRINT("Couldn't allocate memory for ECC!\n");
		return -1;
	}

	generate(a_to_i, i_to_a);

	err_loc_ply = malloc(100 * sizeof(short *));

	/*
	  Allocate the error location array used in fix_section()
	  above.  Putting this on the stack seems a bit much.
	*/

	for (i = 0; i < 100; ++i) {
		err_loc_ply[i] = malloc(100 * sizeof(short));
	}
#endif

#if defined(EP501)
	nand_cmd_ce_off = NAND_CMD_CE_OFF_501;
	set_ecc_mode(LSI_NAND_ECC_MODE_1BIT);
#elif defined(EP501G1)
	nand_cmd_ce_off = NAND_CMD_CE_OFF_501G1;
	set_ecc_mode(LSI_NAND_ECC_MODE_4BIT);
#elif defined(EP501G3)
	nand_cmd_ce_off = NAND_CMD_CE_OFF_501G3;
	set_ecc_mode(LSI_NAND_ECC_MODE_4BIT);
#else
#error "Unsupported ACP System Type!"
#endif

	/* init chip callbacks */
	chip->write_buf = lsi_nand_write_buf;
	chip->read_buf = lsi_nand_read_buf;
	chip->verify_buf = lsi_nand_verify_buf;
	chip->cmd_ctrl = lsi_nand_cmd_ctrl;
	chip->dev_ready = lsi_nand_dev_ready;
	chip->cmdfunc = lsi_nand_cmdfunc;
	chip->waitfunc = lsi_nand_waitfunc;
	chip->select_chip = lsi_nand_select_chip;
	chip->chip_delay = 10;
	chip->options = NAND_USE_FLASH_BBT;

	/* initialize ECC */
	chip->ecc.mode = NAND_ECC_HW;
	chip->ecc.steps = 1;
	chip->ecc.hwctl = lsi_nand_ecc_hwctl;
	chip->ecc.calculate = lsi_nand_ecc_calculate;
	chip->ecc.correct = lsi_nand_ecc_correct;
	chip->ecc.read_page = lsi_nand_ecc_read_page;
	chip->ecc.read_oob = lsi_nand_ecc_read_oob;
	chip->ecc.write_page = lsi_nand_ecc_write_page;
	chip->ecc.write_oob = lsi_nand_ecc_write_oob;

	/* clear any existing ECC status */
	WRITEL(0x0, chip->IO_ADDR_W + EP501_NAND_INTR_STATUS_REG);

	/* enable ECC */
#if defined(EP501G3)
	set_ecc_mode(LSI_NAND_ECC_MODE_OFF);
	set_ecc_mode(LSI_NAND_ECC_MODE_4BIT);
#else
	WRITEL(0x0, chip->IO_ADDR_W + EP501_NAND_INTR_EN_REG);
#endif

	/*
	  ======================================================================
	  Timing Control

	  This may need to be changed, based on the devices used.  Each field is
	  described below.
	*/

	/*
	  TCR0 - NAND Timing Control Register 0
	*/

	{
		nand_timing_control_register_0_t tcr0;

		/* TH [31:24] - CLE, CE & ALE hold Time */
		tcr0.bits.th = 0x08;

		/* TRP [23:16] - Read Pulse Width */
		tcr0.bits.trp = 0x0c;

		/* TWP [15:8] - Write Pulse Width */
		tcr0.bits.twp = 0x0c;

		/* TS [7:0] - Setup Time for CLE, CE & ALE */
		tcr0.bits.ts = 0x05;

		WRITEL( tcr0.raw, ( chip->IO_ADDR_W + EP501_NAND_TIMING0_REG ) );
	}

	/*
	  TCR1 - NAND Timing Control Register 1
	*/

	{
		nand_timing_control_register_1_t tcr1;

		/* TWB [31:24] - WE Rising Edge to RY/BY Falling Edge */
		tcr1.bits.twb = 0x1e;

		/* TRR [23:16] - RY/BY Rising Edge To Read Falling Edge */
		tcr1.bits.trr = 0x07;

		/* TRH [15:8] - Read Pulse High Time */
		tcr1.bits.trh = 0x03;

		/* TWH [7:0] - Write Pulse High Time */
		tcr1.bits.twh = 0x03;

		WRITEL( tcr1.raw, ( chip->IO_ADDR_W + EP501_NAND_TIMING1_REG) );

	}

	/*
	  TCR2 - NAND Timing Control Register 2 (EP501G3 Only)
	*/

#ifdef EP501G3
	{
		nand_timing_control_register_2_t tcr2;

		/*
		  Conservetive value for 2k page and 4k page to switch columns.
		*/

		tcr2.bits.tccs = 0x28;
		tcr2.bits.twhr = 0x10;
		tcr2.bits.trhw = 0x14;
		WRITEL(tcr2.raw, (chip->IO_ADDR_W + EP501G3_NAND_TIMING2_REG));
	}
#endif

	return 0;
}

#endif /* NCR_TRACER */
