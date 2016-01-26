/*
 *  Copyright (C) 2016 Intel Corporation
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <config.h>
#include <common.h>
#include <asm/io.h>

#define GPDMA_TRACE

static unsigned int
greadl(unsigned long address)
{
#ifdef GPDMA_TRACE
	unsigned int v;
	v = readl(address);
	printf("GPDMA Read: 0x%llx contains 0x%x\n", (address - GPDMA0), v);
	return v;
#else
	return readl(address);
#endif
}

static void
gwritel(unsigned int value, unsigned long address)
{
#ifdef GPDMA_TRACE
	printf("GPDMA Write: Writing 0x%x to 0x%llx\n",
	       value, (address - GPDMA0));
#endif
	writel(value, address);
}

/*
  ==============================================================================
  ==============================================================================
  Private
  ==============================================================================
  ==============================================================================
*/

#define GPDMA_MAGIC 0xabcd1234UL

#define DMA_X_SRC_COUNT				0x00
#define DMA_Y_SRC_COUNT				0x04
#define DMA_X_MODIF_SRC				0x08
#define DMA_Y_MODIF_SRC				0x0c
#define DMA_SRC_CUR_ADDR			0x10
#define DMA_SRC_ACCESS				0x14
#define    DMA_SRC_ACCESS_BURST_TYPE		(1<<15)
#define    DMA_SRC_ACCESS_TAIL_LENGTH(x)	(((x) & 0xF) << 11)
#define    DMA_SRC_ACCESS_ROTATOR_LENGTH(x)	(((x) & 1F) << 6)
#define    DMA_SRC_ACCESS_SRC_SIZE(x)		(((x) & 7) << 3)
#define    DMA_SRC_ACCESS_SRC_BURST(x)		(((x) & 7) << 0)
#define DMA_SRC_MASK				0x18
#define DMA_X_DST_COUNT				0x1c
#define DMA_Y_DST_COUNT				0x20
#define DMA_X_MODIF_DST				0x24
#define DMA_Y_MODIF_DST				0x28
#define DMA_DST_CUR_ADDR			0x2C
#define DMA_DST_ACCESS				0x30
#define    DMA_DST_ACCESS_DST_SIZE(x)		(((x) & 7) << 3)
#define    DMA_DST_ACCESS_DST_BURST(x)		(((x) & 7) << 0)
#define DMA_NXT_DESCR				0x34
#define DMA_CHANNEL_CONFIG			0x38
#define    DMA_CONFIG_DST_SPACE(x)		(((x) & 7) << 26)
#define    DMA_CONFIG_SRC_SPACE(x)		(((x) & 7) << 23)
#define    DMA_CONFIG_PRIORITY_ROW		(1<<21)
#define    DMA_CONFIG_PRIORITY			(1<<20)
#define    DMA_CONFIG_LAST_BLOCK		(1<<15)
#define    DMA_CONFIG_CLEAR_FIFO		(1<<14)
#define    DMA_CONFIG_START_MEM_LOAD		(1<<13)
#define    DMA_CONFIG_STOP_DST_EOB		(1<<11)
#define    DMA_CONFIG_FULL_DESCR_ADDR		(1<<8)
#define    DMA_CONFIG_INT_DST_EOT		(1<<7)
#define    DMA_CONFIG_INT_DST_EOB		(1<<6)
#define    DMA_CONFIG_WAIT_FOR_TASK_CNT2	(1<<5)
#define    DMA_CONFIG_TASK_CNT2_RESET		(1<<4)
#define    DMA_CONFIG_WAIT_FOR_TASK_CNT1	(1<<3)
#define    DMA_CONFIG_TASK_CNT1_RESET		(1<<2)
#define    DMA_CONFIG_TX_EN			(1<<1)
#define    DMA_CONFIG_CHAN_EN			(1<<0)
#define DMA_STATUS				0x3C
#define    DMA_STATUS_WAIT_TASK_CNT2		(1<<20)
#define    DMA_STATUS_TASK_CNT2_OVERFLOW	(1<<19)
#define    DMA_STATUS_WAIT_TASK_CNT1		(1<<18)
#define    DMA_STATUS_TASK_CNT1_OVERFLOW	(1<<17)
#define    DMA_STATUS_CH_PAUS_WR_EN		(1<<16)
#define    DMA_STATUS_ERR_ACC_DESCR		(1<<14)
#define    DMA_STATUS_ERR_ACC_DST		(1<<13)
#define    DMA_STATUS_ERR_ACC_SRC		(1<<12)
#define    DMA_STATUS_ERR_OVERFLOW		(1<<9)
#define    DMA_STATUS_ERR_UNDERFLOW		(1<<8)
#define    DMA_STATUS_CH_PAUSE			(1<<7)
#define    DMA_STATUS_CH_WAITING		(1<<5)
#define    DMA_STATUS_CH_ACTIVE			(1<<4)
#define    DMA_STATUS_TR_COMPLETE		(1<<3)
#define    DMA_STATUS_BLK_COMPLETE		(1<<2)
#define    DMA_STATUS_UNALIGNED_READ		(1<<1)
#define    DMA_STATUS_UNALIGNED_WRITE		(1<<0)
#define    DMA_STATUS_UNALIGNED_ERR		(DMA_STATUS_UNALIGNED_READ | \
						 DMA_STATUS_UNALIGNED_WRITE)
#define DMA_TASK_CNT_1				0x40
#define DMA_TASK_CNT_2				0x44
#define DMA_MODE_CONFIG				0x48
#define DMA_CURR_DESCR				0x4c
#define DMA_PREV_DESCR				0x50
#define DMA_SRC_ADDR_SEG			0x54
#define DMA_DST_ADDR_SEG			0x58
#define DMA_DESCR_ADDR_SEG			0x5c

#define DMA_STATUS_ERROR		(DMA_STATUS_ERR_ACC_DESCR | \
					 DMA_STATUS_ERR_ACC_DST   | \
					 DMA_STATUS_ERR_ACC_SRC   | \
					 DMA_STATUS_ERR_OVERFLOW  | \
					 DMA_STATUS_ERR_UNDERFLOW | \
					 DMA_STATUS_UNALIGNED_ERR)

#define DMA_STATUS_CLEAR		(DMA_STATUS_CH_PAUS_WR_EN | \
					 DMA_STATUS_TR_COMPLETE   | \
					 DMA_STATUS_BLK_COMPLETE)

#define DMA_CONFIG_END			(DMA_CONFIG_LAST_BLOCK | \
					 DMA_CONFIG_INT_DST_EOT)

#define DMA_CONFIG_ONE_SHOT(__ext)	(DMA_CONFIG_DST_SPACE((__ext)) | \
					 DMA_CONFIG_SRC_SPACE((__ext)) | \
					 DMA_CONFIG_TX_EN              | \
					 DMA_CONFIG_CHAN_EN)

#define DMA_CONFIG_DSC_LOAD		(DMA_CONFIG_START_MEM_LOAD  | \
					 DMA_CONFIG_FULL_DESCR_ADDR | \
					 DMA_CONFIG_CHAN_EN)

#define GEN_STAT                                0xf00
#define   GEN_STAT_CH0_ACTIVE                   (1<<0)
#define   GEN_STAT_CH1_ACTIVE                   (1<<2)
#define   GEN_STAT_CH1_ACTIVE                   (1<<2)
#define   GEN_STAT_CH0_ERROR                    (1<<16)
#define   GEN_STAT_CH1_ERROR                    (1<<17)
#define GEN_CONFIG                              0xf04
#define  GEN_CONFIG_EXT_MEM                     (1<<19)
#define  GEN_CONFIG_INT_EDGE(_ch)               (1<<(_ch))
#define SOFT_RESET                              0xf08

/*
  ==============================================================================
  ==============================================================================
  Public
  ==============================================================================
  ==============================================================================
*/

/*
  ------------------------------------------------------------------------------
  gpdma_reset
*/

int
gpdma_reset(void)
{
	/*
	  Use the full reset of all changes.
	*/

	writel(GPDMA_MAGIC, GPDMA0 + SOFT_RESET);

	return 0;
}

/*
  ------------------------------------------------------------------------------
  gpdma_xfer

  Do a direct DMA (no descriptors) transfer.
*/

#if defined(CONFIG_ANY_XLF)
#define GPDMA0_AXPROT_OVERRIDE 0x45800
#else
#define GPDMA0_AXPROT_OVERRIDE 0x48800
#endif

int
gpdma_xfer(void *dest, void *src, size_t size, int secure)
{
	unsigned int gpdma0_axprot_override;
	unsigned int gpdma0_status;
	unsigned int gpdma0_channel_config;

	/* Make sure no other transactions are in process. */
	gpdma0_status = greadl(GPDMA0 + DMA_STATUS);

	if (0 != (gpdma0_status & DMA_STATUS_CH_ACTIVE))
		return -1;

	/* Clear status bits. */
	gwritel((DMA_STATUS_TR_COMPLETE | DMA_STATUS_BLK_COMPLETE),
		GPDMA0 + DMA_STATUS);

	/* Set gpdma0_axprot_override to secure or non-secure. */
	gpdma0_axprot_override = readl(MMAP_SCB + GPDMA0_AXPROT_OVERRIDE);

	if (0 == secure)
		writel(3, MMAP_SCB + GPDMA0_AXPROT_OVERRIDE);
	else
		writel(2, MMAP_SCB + GPDMA0_AXPROT_OVERRIDE);

	/* Set up the segment registers (top 8 bits of address). */
	gwritel((((unsigned long)dest & 0xff00000000) >> 32),
		GPDMA0 + DMA_DST_ADDR_SEG);
	gwritel((((unsigned long)src & 0xff00000000) >> 32),
		GPDMA0 + DMA_SRC_ADDR_SEG);

	/* Set up the rest of the address. */
	gwritel(((unsigned long)dest & 0xffffffff), GPDMA0 + DMA_DST_CUR_ADDR);
	gwritel(((unsigned long)src & 0xffffffff), GPDMA0 + DMA_SRC_CUR_ADDR);

	/* Make sure the destination is cachable. 0x170.0.0 */

	/*
	  Per conversation...

	  SRC_SIZE = 128 bits
	  SRC_BURST = 4
	  MODIF_SRC = 63 (64 bytes)
	  SRC_COUNT = size / 64
	  Y_SRC_COUNT = 0
	  Y_MODIF_SRC doesn't matter
	  SRC_MASK = all 1s
	*/

	gwritel((DMA_SRC_ACCESS_SRC_BURST(0) | DMA_SRC_ACCESS_SRC_SIZE(0)),
		GPDMA0 + DMA_SRC_ACCESS);
	gwritel((DMA_SRC_ACCESS_SRC_BURST(0) | DMA_SRC_ACCESS_SRC_SIZE(0)),
		GPDMA0 + DMA_DST_ACCESS);
	gwritel(0xffffffff, GPDMA0 + DMA_SRC_MASK);
	gwritel(64, GPDMA0 + DMA_X_MODIF_SRC);
	gwritel(64, GPDMA0 + DMA_X_MODIF_DST);
	gwritel((size / 64), GPDMA0 + DMA_X_SRC_COUNT);
	gwritel(0, GPDMA0 + DMA_Y_SRC_COUNT);
	gwritel((size / 64), GPDMA0 + DMA_X_DST_COUNT);
	gwritel(0, GPDMA0 + DMA_Y_DST_COUNT);

	/* Start the transfer. */
	gpdma0_channel_config = greadl(GPDMA0 + DMA_CHANNEL_CONFIG);
	gpdma0_channel_config |= 3;
	gwritel(gpdma0_channel_config, GPDMA0 + DMA_CHANNEL_CONFIG);

	do {
		mdelay(1000);
		printf("COUNTS: 0x%x 0x%x\n",
		       readl(GPDMA0 + DMA_X_SRC_COUNT),
		       readl(GPDMA0 + DMA_X_DST_COUNT));
	} while (0 == (greadl(GPDMA0 + DMA_STATUS) & 1));

	/* Restore gpdma0_axprot_override. */
	writel(gpdma0_axprot_override, MMAP_SCB + GPDMA0_AXPROT_OVERRIDE);

	return 0;
}
