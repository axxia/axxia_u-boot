/*
 *  board/axxia/common/pciesriosata.c
 *
 *  Copyright (C) 2015 Intel (sangeetha.rao@intel.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <config.h>
#include <common.h>
#include <asm/io.h>

/*
  Not all configurations are available for unit testing, so add the
  ability to trace all register accesses for comparison with known
  working cases.
*/

#ifdef TRACE_PEI_ACCESSES
static inline unsigned int
_pss_readl(uint32_t volatile *address)
{
	unsigned int value;

	value = readl(address);
	printf("pss_readl: Read 0x%x from 0x%010llx\n",
	       value, (unsigned long long)address);

	return value;
}
#define pss_readl(address) ({						\
			printf("%s:%d - ", __FILE__, __LINE__);		\
			_pss_readl((uint32_t volatile *)(address));	\
		})
static inline void
_pss_writel(unsigned int value, uint32_t volatile *address)
{
	writel(value, address);
	printf("pss_writel: wrote 0x%x to 0x%010llx\n",
	       value, (unsigned long long)address);
}
#define pss_writel(value, address) ({					\
			printf("%s:%d - ", __FILE__, __LINE__);		\
			_pss_writel((value), (uint32_t volatile *)(address)); \
		})
#else  /* TRACE_PEI_ACCESSES */
#define pss_readl(address) readl((address))
#define pss_writel(value, address) writel((value), (address))
#endif /* TRACE_PEI_ACCESSES */

/*
  Mode enumerations.
*/

enum SrioMode {
	SRIO0,
	SRIO1
};

enum SrioSpeed {
	SRIO_SPEED_1_25G,
	SRIO_SPEED_2_5G,
	SRIO_SPEED_3_125G,
	SRIO_SPEED_5G,
	SRIO_SPEED_6_25G
};

enum PCIMode {
	PEI0,
	PEI1,
	PEI2
};

enum PLLMode {
	PLLA,
	PLLB
};

enum PowerState {
	P0,
	P1,
	P2
};

enum Dir {
	TX,
	RX
};

/* PEI0x8 000/010 which is valid? */
enum port_config0 {
	pc0_PEI0x8 = 0x0,
	pc0_PEI0x4 = 0x1,
	pc0_PEI0x8_alt = 0x2,
	pc0_PEI0x2_PEI2x2 = 0x3,
	pc0_SRIO1x2_SRIO0x2 = 0x4,
	pc0_PEI0x2_SRIO0x2 = 0x7,
};

enum port_config1 {
	pc1_PEI0x8 = 0x0,
	pc1_PEI1x4 = 0x1,
	pc1_PEI1x2_SATA0x1_SATA1x1 = 0x2,
	pc1_PEI1x2_PEI2x2 = 0x3,
};

enum pipe_port {
	pp_disable = 0x0,
	pp_0 = 0x1,
	pp_0_1 = 0x2,
	pp_0_1_2_3 = 0x3,
};

enum pipe_nphy {
	one_phy = 0x0,
	two_phy = 0x1,
	three_phy = 0x2,
	four_phy = 0x3,
};

void setup_srio_mode(enum SrioMode mode, enum SrioSpeed speed)
{
	u32 regVal;
	u32 phy, lane, rate, width, pll;
	int i = 0;
	if (mode == SRIO0) {
		phy = 1;
		lane = 2;
	} else {
		phy = 0;
		lane = 0;
	}

	/* set wordmode to bypass for lane 0 and lane 1*/
	for (i = lane; i <= (lane + 1); i++) {
		/* set Tx word mode */
		ncr_read32(NCP_REGION_ID(0x115, 0), (0x18 + (i * 0x1c)),
			   &regVal);
		regVal &= (~(3 << 4));
		regVal |= (0 << 4);
		/* TX iboost level */
		regVal |= (15 << 12);
		ncr_write32(NCP_REGION_ID(0x115, 0), (0x18 + (i * 0x1c)),
			    regVal);

		/* control for setting the transmitter driver
		 * output pre-emphasis/post-emphasis and amplitude
		 */
		regVal = ((0 << 8) | (0 << 16) | (40 << 0) | (1 << 28));
		ncr_write32(NCP_REGION_ID(0x115, 0),
			    (0x18 + (i * 0x1c) + 0x8),
			    regVal);
		/* Tx width */
		ncr_read32(NCP_REGION_ID(0x115, 0),
			   (0x18 + (i * 0x1c) + 0x4), &regVal);
		regVal &= 0xffac8fcf;
		/* SEt the power state of the transmitter
		 * TX rate/width
		 */
		rate = (speed == SRIO_SPEED_1_25G) ? 3 :
			((speed == SRIO_SPEED_2_5G) ||
			 (speed == SRIO_SPEED_3_125G)) ? 2 : 1;
		width = 1;
		pll = 0;
		pll = ((speed == SRIO_SPEED_3_125G) ||
		       (speed == SRIO_SPEED_6_25G)) ? 1 : 0;
		regVal |= ((0x3 << 4) | (rate << 12) | (width << 16)
			   | (pll << 20) | (1 << 22));
		ncr_write32(NCP_REGION_ID(0x115, 0),
			    (0x18 + (i * 0x1c) + 0x4), regVal);

		if ((speed == SRIO_SPEED_3_125G) || (speed == SRIO_SPEED_6_25G))
			regVal = (0x550 << 8) | 0x22;
		else
			regVal = (0x540 << 8) | 0x2a;
		ncr_write32(NCP_REGION_ID(0x115, 0),
			    (0x18 + (i * 0x1c) + 0x10), regVal);
		ncr_read32(NCP_REGION_ID(0x115, 0),
			   (0x18 + (i * 0x1c) + 0x14), &regVal);
		regVal &= 0xff3c8fcf;
		regVal |= ((0x3 << 4) | (rate << 12) | (width << 16));
		if ((speed == SRIO_SPEED_5G) || (speed == SRIO_SPEED_6_25G))
			regVal |= ((1 << 22) | (1 << 23));
		ncr_write32(NCP_REGION_ID(0x115, 0),
			    (0x18 + (i * 0x1c) + 0x14), regVal);

	}
	/* set gearbox word clk sel for phy 1 lane 0/lane 1 */
	ncr_read32(NCP_REGION_ID(0x115, 0), (0xf8 + (phy * 0x18) + 0x14),
		   &regVal);
	regVal &= (~(0x7 << 20));
	if (speed == SRIO_SPEED_1_25G)
		regVal |= (0x2) << 20;
	else if ((speed == SRIO_SPEED_2_5G) || (speed == SRIO_SPEED_3_125G))
		regVal |= (0x1) << 20;
	ncr_write32(NCP_REGION_ID(0x115, 0), (0xf8 + (phy * 0x18) + 0x14),
		    regVal);
	ncr_read32(NCP_REGION_ID(0x115, 0), (0xf8 + (phy * 0x18) + 0x14),
		   &regVal);
	regVal &= (~(0x7 << 24));
	if (speed == SRIO_SPEED_1_25G)
		regVal |= (0x2) << 24;
	else if ((speed == SRIO_SPEED_2_5G) || (speed == SRIO_SPEED_3_125G))
		regVal |= (0x1) << 24;
	ncr_write32(NCP_REGION_ID(0x115, 0), (0xf8 + (phy * 0x18) + 0x14),
		    regVal);
	/* PLLA Settings */
	/* Enable ref clk, ref use_pad, ref_clk_div2_en */
	regVal = ((0x1) | ((0x1) << 1) | (0 << 2));
	/* Select ref range 78.1-104 MHz */
	regVal |= (0x6 << 4);
	/* Enable ref_clk_mplla_div2_en, ref_clk_mpllb_div2_en
	 * and ref_repeat_clk_en */
	regVal |= ((0x1 << 8) | (0x1 << 9) | (0 << 10));
	/* Set tx_vboost_lvl and vref_ctrl */
	regVal |= ((0x5 << 16) | (17 << 20));
	ncr_write32(NCP_REGION_ID(0x115, 0), (0xf8 + (phy * 0x18)),
		    regVal);

	/* MPLLA setting
	 * mplla_ssc_en                = 1'b0;
	 * mplla_div_clk_en            = 1'b0;
	 * mplla_ssc_range             = 3'h0;
	 * mplla_ssc_clk_sel   = 2'h2;
	 * mplla_div_multiplier        = 7'h0;
	 */
	/* MPLLA spread-spectrum clock (SSC) and
	 * div_clk enable */
	regVal = (0 | (0 << 2));
	/*  SSC range  and SSC clk select */
	regVal |= (0 << 20);
	/* mplla_div_multiplier */
	regVal |= (0 << 24);
	ncr_write32(NCP_REGION_ID(0x115, 0), (0xf8 + (phy * 0x18) + 0x8),
		    regVal);

	switch (speed) {
	case SRIO_SPEED_1_25G:
	case SRIO_SPEED_2_5G:
	case SRIO_SPEED_5G:
		/* 500 MHz PLLA */
		/* MPLLA settings
		 * mplla_force_en              = 1'b0;
		 * mplla_div8_clk_en   = 1'b0;
		 * mplla_div10_clk_en  = 1'b1;
		 * mplla_div16p5_clk_en        = 1'b0;
		 * mplla_multiplier            = 7'h20;
		 */
		ncr_read32(NCP_REGION_ID(0x115, 0), (0xf8 + (phy * 0x18) + 0x4),
			   &regVal);
		/* Disable MPLLA force, mplla_div8_clk_en
		 * Enable mplla_div10_clk_en
		 * and Disable mplla_div16p5_clk_en */
		/* MPLLA multiplier is 32 */
		regVal |= ((0x1 << 2) | (0x20 << 4));
		ncr_write32(NCP_REGION_ID(0x115, 0),
			    (0xf8 + (phy * 0x18) + 0x4),
			    regVal);
		/*
		 * mplla_fracn_ctrl            = 9'h0;
		 * mplla_bandwidth             = 7'h3a;
		 */
		ncr_read32(NCP_REGION_ID(0x115, 0),
			   (0xf8 + (phy * 0x18) + 0x10),
			   &regVal);
		regVal &= 0xffff0000;
		regVal |= (0x3a << 9);
		ncr_write32(NCP_REGION_ID(0x115, 0),
			    (0xf8 + (phy * 0x18) + 0x10),
			    regVal);
		break;
	case SRIO_SPEED_3_125G:
	case SRIO_SPEED_6_25G:
		/* 625 MHz PLLB */
		/* MPLLB settings
		 * mpllb_force_en              = 1'b0;
		 * mpllb_div8_clk_en   = 1'b0;
		 * mpllb_div10_clk_en  = 1'b1;
		 * mpllb_div16p5_clk_en        = 1'b0;
		 * mpllb_multiplier            = 7'h28;
		 */
		ncr_read32(NCP_REGION_ID(0x115, 0), (0xf8 + (phy * 0x18) + 0x4),
			   &regVal);
		/* Disable MPLLB force, mpllb_div8_clk_en
		 * Enable mpllb_div10_clk_en
		 * and Disable mpllb_div16p5_clk_en */
		/* MPLLB multiplier is 40 */
		regVal |= (((0x1 << 2) | (0x28 << 4))<<16);
		regVal |= ((0x1 << 2) | (0x20 << 4)); /* Is this needed*/
		ncr_write32(NCP_REGION_ID(0x115, 0),
			    (0xf8 + (phy * 0x18) + 0x4), regVal);
		/*
		 * mplla_fracn_ctrl            = 9'h0;
		 * mplla_bandwidth             = 7'h5b;
		 */
		ncr_read32(NCP_REGION_ID(0x115, 0),
			   (0xf8 + (phy * 0x18) + 0x10),
			   &regVal);
		regVal &= 0xffff;
		regVal |= ((0x5b << 9)<<16);
		regVal |= (0x3a << 9); /* Is this needed*/
		ncr_write32(NCP_REGION_ID(0x115, 0),
			    (0xf8 + (phy * 0x18) + 0x10),
			    regVal);
		if (speed == SRIO_SPEED_6_25G) {
			ncr_write32(NCP_REGION_ID(0x115, (phy + 1)),
				    0x16, 0x0010);
			ncr_write32(NCP_REGION_ID(0x115, (phy + 1)),
				    0x24, 0x001E);
			ncr_write32(NCP_REGION_ID(0x115, (phy + 1)),
				    0x26, 0x0000);
			ncr_write32(NCP_REGION_ID(0x115, (phy + 1)),
				    0x18, 0x0010);
			ncr_write32(NCP_REGION_ID(0x115, (phy + 1)),
				    0x44, 0x001E);
			ncr_write32(NCP_REGION_ID(0x115, (phy + 1)),
				    0x46, 0x0000);
		}
		break;
	}
}

void disable_ltssm(enum PCIMode mode)
{
	u32 val;

	switch (mode) {
	case PEI0:
		/* LTSSM Disable for PEI0 */
		val = pss_readl(PCIE0_CC_GPREG_BASE + 0x38);
		val &= (~(0x1));
		pss_writel(val, PCIE0_CC_GPREG_BASE + 0x38);
		break;
#if defined(ACP_PEI1)
	case PEI1:
		/* LTSSM Disable for PEI1 */
		val = pss_readl(PCIE1_CC_GPREG_BASE + 0x38);
		val &= (~(0x1));
		pss_writel(val, PCIE1_CC_GPREG_BASE + 0x38);
		break;
#endif
#if defined(ACP_PEI2)
	case PEI2:
		/* LTSSM Disable for PEI2 */
		val = pss_readl(PCIE2_CC_GPREG_BASE + 0x38);
		val &= (~(0x1));
		pss_writel(val, PCIE2_CC_GPREG_BASE + 0x38);
		break;
#endif
	default:
		printf("%s Unsupported PEI %d\n", __func__, mode);
	};
	mdelay(100);		/* TODO: Why is this needed? */
}

void set_sw_port_config0(enum port_config0 mode)
{
	u32 regVal;

	ncr_read32(NCP_REGION_ID(0x115, 0), 0, &regVal);
	regVal &= ~(0x7 << 26);
	regVal |= ((mode & 0x7) << 26);
	ncr_write32(NCP_REGION_ID(0x115, 0), 0, regVal);
}

void set_sw_port_config1(enum port_config1 mode)
{
	u32 regVal;

	ncr_read32(NCP_REGION_ID(0x115, 0), 0x4, &regVal);
	regVal &= ~(0x3 << 22);
	regVal |= ((mode & 0x3) << 22);
	ncr_write32(NCP_REGION_ID(0x115, 0), 0x4, regVal);
}

static void set_pipe_port_sel(enum pipe_port pp)
{
	u32 regVal;

	ncr_read32(NCP_REGION_ID(0x115, 0), 0x4, &regVal);
	regVal &= ~(0x3 << 24);
	regVal |= ((pp & 0x3) << 24);
	ncr_write32(NCP_REGION_ID(0x115, 0), 0x4, regVal);
}

static void set_pipe_nphy(enum pipe_nphy nphy)
{
	u32 regVal;

	ncr_read32(NCP_REGION_ID(0x115, 0), 0x4, &regVal);
	regVal &= ~(0x3 << 20);
	regVal |= ((nphy & 0x3) << 20);
	ncr_write32(NCP_REGION_ID(0x115, 0), 0x4, regVal);
}

#if !defined(CONFIG_AXXIA_ANY_XLF)
static void
set_srio_mode(enum SrioMode mode, unsigned int ctrl)
{
	u32 regVal;

	ncr_read32(NCP_REGION_ID(0x115, 0), 0, &regVal);
	if (SRIO0 == mode) {
		regVal &= ~(0x3 << 20);
		regVal |= ((ctrl & 0x3) << 20);
	} else {
		regVal &= ~(0x3 << 24);
		regVal |= ((ctrl & 0x3) << 24);
	}
	ncr_write32(NCP_REGION_ID(0x115, 0), 0, regVal);
}

static void
set_srio_speed(enum SrioMode mode, enum SrioSpeed speed)
{
	u32 regVal;

	ncr_read32(NCP_REGION_ID(0x115, 0x0), 0x4, &regVal);
	if (SRIO0 == mode) {
		regVal &= ~(0x7 << 12);
		regVal |= ((speed & 0x7) << 12);
	} else {
		regVal &= ~(0x7 << 16);
		regVal |= ((speed & 0x7) << 16);
	}
	ncr_write32(NCP_REGION_ID(0x115, 0), 0x4, regVal);
}
#endif

static void set_pei0_rc_mode(u32 rc)
{
	u32 regVal;

	ncr_read32(NCP_REGION_ID(0x115, 0x0), 0x0, &regVal);
	if (rc)
		regVal |= (0x1 << 22);
	else
		regVal &= ~(0x1 << 22);
	ncr_write32(NCP_REGION_ID(0x115, 0x0), 0x0, regVal);
}

void enable_reset(u32 phy)
{
	u32 regVal;

#if defined(CONFIG_ANY_XLF)
	if (0 != phy)
		return;
#endif

	if (phy == 0) {
		ncr_read32(NCP_REGION_ID(0x115, 0), 0, &regVal);
		regVal |= (1 << 5);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0, regVal);
	} else if (phy == 1) {
		ncr_read32(NCP_REGION_ID(0x115, 0), 0, &regVal);
		regVal |= (1 << 14);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0, regVal);
	} else if (phy == 2) {
		ncr_read32(NCP_REGION_ID(0x115, 0), 0x4, &regVal);
		regVal |= (1 << 19);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x4, regVal);
	} else if (phy == 3) {
		ncr_read32(NCP_REGION_ID(0x115, 0), 0x4, &regVal);
		regVal |= (1 << 29);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x4, regVal);
	}
}

static void release_reset(u32 phy)
{
	u32 regVal;

#if defined(CONFIG_ANY_XLF)
	if (0 != phy)
		return;
#endif

	if (phy == 0) {
		ncr_read32(NCP_REGION_ID(0x115, 0), 0, &regVal);
		regVal &= (~(1 << 5));
		ncr_write32(NCP_REGION_ID(0x115, 0), 0, regVal);
	} else if (phy == 1) {
		ncr_read32(NCP_REGION_ID(0x115, 0), 0, &regVal);
		regVal &= (~(1 << 14));
		ncr_write32(NCP_REGION_ID(0x115, 0), 0, regVal);
	} else if (phy == 2) {
		ncr_read32(NCP_REGION_ID(0x115, 0), 0x4, &regVal);
		regVal &= (~(1 << 19));
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x4, regVal);
	} else if (phy == 3) {
		ncr_read32(NCP_REGION_ID(0x115, 0), 0x4, &regVal);
		regVal &= (~(1 << 29));
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x4, regVal);
	}
}

#if !defined(CONFIG_AXXIA_ANY_XLF)
static int
check_pll_lock(enum PLLMode mode, u32 phy)
{
	u32 regVal;
	int count = 0;

	ncr_read32(NCP_REGION_ID(0x115, 0), 0x184 + (phy * 8), &regVal);
	regVal &= (1 << (20 + mode));

	do {
		/* 100 ms delay */
		mdelay(100);
		ncr_read32(NCP_REGION_ID(0x115, 0), 0x184 + (phy * 8),
			   &regVal);
		regVal &= (1 << (20 + mode));
	} while ((!regVal) && (count++ < 5));

	return regVal;
}

static int
release_srio_reset(enum SrioMode mode, enum SrioSpeed speed)
{
	u32 phy;
	enum PLLMode pll;

	switch (mode) {
	case SRIO0:
		phy = 1;
		break;
	case SRIO1:
		phy = 0;
		break;
	default:
		printf("Wrong SRIO%d\n", mode);
		return 1;
	}

	release_reset(phy);
	pll = PLLA;
	if ((SRIO_SPEED_3_125G == speed) ||
	    (SRIO_SPEED_6_25G == speed))
		pll = PLLB;
	if (!check_pll_lock(pll, phy)) {
		printf("%s didn't lock\n", pll == PLLA ? "PLLA" : "PLLB");
		return 1;
	}
	return 0;
}

static int
check_ack(u32 phy, u32 lane, enum Dir dir)
{
	u32 regVal;
	int count = 0;

	ncr_read32(NCP_REGION_ID(0x115, 0), 0x184 + (phy * 8), &regVal);
	if (dir == TX)
		regVal &= (1 << (0 + lane));
	else
		regVal &= (1 << (16 + lane));

	do {
		/* 100 ms delay */
		mdelay(100);
		ncr_read32(NCP_REGION_ID(0x115, 0), 0x184 + (phy * 8),
			   &regVal);
		if (dir == TX)
			regVal &= (1 << (0 + lane));
		else
			regVal &= (1 << (16 + lane));
	} while ((!regVal) && (count++ < 5));

	return regVal;
}
#endif

void set_tx_clk_ready(void)
{
	u32 regVal;

	ncr_read32(NCP_REGION_ID(0x115, 0), 0x8, &regVal);
	regVal |= 0xff;
	ncr_write32(NCP_REGION_ID(0x115, 0), 0x8, regVal);
}

/* RX clock and data recovery */
int check_rx_valid(u32 phy, u32 lane)
{
	u32 regVal;
	int count = 0;

	ncr_read32(NCP_REGION_ID(0x115, 0), 0x184 + (phy * 8), &regVal);
	regVal &= (1 << (24 + (4 * lane)));

	do {
		/* 100 ms delay */
		mdelay(100);
		ncr_read32(NCP_REGION_ID(0x115, 0), 0x184 + (phy * 8), &regVal);
		regVal &= (1 << (24 + (4 * lane)));
	} while ((!regVal) && (count++ < 5));

	return regVal;
}

/*
  ------------------------------------------------------------------------------
  powerup_lane
*/

#if !defined(CONFIG_AXXIA_ANY_XLF)
static int
powerup_lane(u32 phy, u32 lane, enum PowerState state, enum Dir dir)
{
	u32 regVal, powerVal;
	u32 offset;
	int ret;

	if (dir == TX)
		offset = 0x18 + (((phy * 2) + lane) * 0x1c) + 0x4;
	else
		offset = 0x18 + (((phy * 2) + lane) * 0x1c) + 0x14;

	ncr_read32(NCP_REGION_ID(0x115, 0), offset, &regVal);
	regVal &= 0xffffffce;
	/* New Transmitter setting request */
	powerVal = (state == P2) ? 3 : ((state == P1) ? 2 : 0);
	regVal |= (powerVal << 4) | (1 << 0);
	ncr_write32(NCP_REGION_ID(0x115, 0), offset, regVal);

	/* Check if ack is set */
	ret = check_ack(phy, lane, dir);
	ncr_read32(NCP_REGION_ID(0x115, 0), offset, &regVal);
	regVal &= ~(1 << 0);
	ncr_write32(NCP_REGION_ID(0x115, 0), offset, regVal);

	return ret;
}
#endif

#if !defined(CONFIG_AXXIA_ANY_XLF)
static int
powerup_srio_lanes(enum SrioMode mode, enum PowerState state)
{
	u32 lane;
	u32 phy;

	switch (mode) {
	case SRIO0:
		phy = 1;
		break;
	case SRIO1:
		phy = 0;
		break;
	default:
		printf("Wrong SRIO%d\n", mode);
		return 1;
	}

	/* Power up TX/RX lanes */
	for (lane = 0; lane < 2; lane++) {
		if (!powerup_lane(phy, lane, state, TX)) {
			printf("TX powerup failed for PHY%d LANE%d\n",
			       phy, lane);
			return 1;
		}
		if (!powerup_lane(phy, lane, state, RX)) {
			printf("RX powerup failed for PHY%d LANE%d\n",
			       phy, lane);
			return 1;
		}
	}
	return 0;
}
#endif

/*
  ------------------------------------------------------------------------------
  enable_lane
*/

#if !defined(CONFIG_AXXIA_ANY_XLF)
static void
enable_lane(u32 phy, u32 lane, enum Dir dir)
{
	u32 regVal;
	u32 offset;

	if (TX == dir)
		offset = 0x18 + (((phy * 2) + lane) * 0x1c);
	else
		offset = 0x18 + (((phy * 2) + lane) * 0x1c) + 0x14;

	ncr_read32(NCP_REGION_ID(0x115, 0), offset, &regVal);

	if (TX ==dir)
		regVal |= (1 << 25);
	else
		regVal |= (1 << 21);

	ncr_write32(NCP_REGION_ID(0x115, 0), offset, regVal);

	return;
}
#endif

/*
  ------------------------------------------------------------------------------
  update_settings
*/

static void
update_settings(void)
{
	int i;
	unsigned int region;
	int number_of_serdes;

	/*
	  Make sure the parameters are version 2...
	*/

	if (2 != pciesrio->version)
		return;

	region = NCP_REGION_ID(0x115, 0);

#if defined(CONFIG_AXXIA_ANY_56XX)
	number_of_serdes = 4;
#elif defined(CONFIG_AXXIA_ANY_XLF)
	number_of_serdes = 1;
#else
#error "Invalid Target!"
#endif

	/*
	  Set per serdes values.
	*/

	for (i = 0; i < number_of_serdes; ++i) {
		unsigned int offset;
		unsigned int pic;
		unsigned int ref_range;
		unsigned int value;

#if defined(CONFIG_AXXIA_ANY_56XX)
		offset = (0xf8 + (i * 0x18));
#elif defined(CONFIG_AXXIA_ANY_XLF)
		offset = 0x44;
#endif

		if (0 != (pciesrio->primary_input_clock & (0xff << (i * 8))))
			pic = 2;
		else
			pic = 0;

		ref_range = (pciesrio->input_ref_clock_range &
			     (0xff << (i * 8))) >> (i * 8);

		ncr_read32(region, offset, &value);
		debug("0x%x.0x%x.0x%x : 0x%x => ",
		      NCP_NODE_ID(region), NCP_TARGET_ID(region), offset,
		      value);
		value &= ~0x72;
		value |= pic;
		value |= ref_range << 4;
		debug("0x%x\n", value);
		ncr_write32(region, offset, value);
	}

	/*
	  Set per lane values.
	*/

	for (i = 0; i < (number_of_serdes * 2); ++i) {
		unsigned int offset;
		unsigned int main;
		unsigned int pre;
		unsigned int post;
		unsigned int boost;
		unsigned int value;

		if (4 > i) {
			main = pciesrio->lane_0_eq_main;
			pre = pciesrio->lane_0_eq_pre;
			post = pciesrio->lane_0_eq_post;
			boost = pciesrio->lane_0_vboost;
		} else {
			main = pciesrio->lane_1_eq_main;
			pre = pciesrio->lane_1_eq_pre;
			post = pciesrio->lane_1_eq_post;
			boost = pciesrio->lane_1_vboost;
		}

		switch (i % 4) {
		case 0:
			main &= 0x3f;
			pre &= 0x3f;
			post &= 0x3f;
			boost &= 0x3f;
			break;
		case 1:
			main = (main & 0x3f00) >> 8;
			pre = (pre & 0x3f00) >> 8;
			post = (post & 0x3f00) >> 8;
			boost = (boost & 0x3f00) >> 8;
			break;
		case 2:
			main = (main & 0x3f0000) >> 16;
			pre = (pre & 0x3f0000) >> 16;
			post = (post & 0x3f0000) >> 16;
			boost = (boost & 0x3f0000) >> 16;
			break;
		case 3:
			main = (main & 0x3f000000) >> 24;
			pre = (pre & 0x3f000000) >> 24;
			post = (post & 0x3f000000) >> 24;
			boost = (boost & 0x3f000000) >> 24;
			break;
		default:
			printf("Error setting coefficients!\n");
			break;
		}

#if defined(CONFIG_AXXIA_ANY_56XX)
		offset = 0x18 + (i * 0x1c);
#elif defined(CONFIG_AXXIA_ANY_XLF)
		offset = 0xc + (i * 0x1c);
#endif

#if defined(CONFIG_AXXIA_ANY_56XX)
		ncr_read32(region, offset, &value);
		debug("0x%x.0x%x.0x%x : 0x%x => ",
		      NCP_NODE_ID(region), NCP_TARGET_ID(region), offset,
		      value);
		value &= ~(1 << 11);

		if (0 != boost)
			value |= (1 << 11);

		debug("0x%x\n", value);
		ncr_write32(region, offset, value);

#endif

		offset += 0x8;

		ncr_read32(region, offset, &value);
		debug("0x%x.0x%x.0x%x : 0x%x => ",
		      NCP_NODE_ID(region), NCP_TARGET_ID(region), offset,
		      value);
		value &= ~0x3f3f3f;
		value |= ((post << 16) | (pre << 8) | main);
		debug("0x%x\n", value);
		ncr_write32(region, offset, value);
	}

	return;
}

#if !defined(CONFIG_AXXIA_ANY_XLF)
static void
enable_srio_lanes(enum SrioMode mode)
{
	u32 lane;
	u32 phy;

	switch (mode) {
	case SRIO0:
		phy = 1;
		break;
	case SRIO1:
		phy = 0;
		break;
	default:
		printf("Wrong SRIO%d\n", mode);
		return;
	}

	for (lane = 0; lane < 2; lane++) {
		enable_lane(phy, lane, TX);
		enable_lane(phy, lane, RX);
	}
}
#endif

/*
  ------------------------------------------------------------------------------
  get_config
*/

static inline unsigned
get_config(unsigned control)
{
	return (0xf & (control >> 22));
}

/*
  ------------------------------------------------------------------------------
  verify_control
*/

static int
verify_control(unsigned control)
{
	unsigned config;

	if (0x80000000 == control)
		return 0;

#if defined(CONFIG_AXXIA_ANY_56XX)
	if (0 != (control & ~0x7c3ff9f))
		return -1;

	config = get_config(control);

	if (1 != config && 2 != config && 3 != config && 4 != config)
		return -1;
#elif defined(CONFIG_AXXIA_ANY_XLF)
	if (0 != (control & ~0xc00081))
		return -1;

	config = get_config(control);

	if (1 != config && 2 != config)
		return -1;
#endif

	return 0;
}

/*
  ==============================================================================
  ==============================================================================
  Public
  ==============================================================================
  ==============================================================================
*/

/*
  ------------------------------------------------------------------------------
  pei_setup
*/

int
pei_setup(unsigned int control)
{
	unsigned int rc_mode;
#if !defined(CONFIG_AXXIA_ANY_XLF)
	unsigned int srio0_mode;
	unsigned int srio1_mode;
	unsigned int srio0_speed;
	unsigned int srio1_speed;
	unsigned int srio0_ctrl;
	unsigned int srio1_ctrl;
	unsigned int pei1_mode;
	unsigned int pei2_mode;
#endif
	unsigned int pei0_mode;
	u32 reg_val = 0;
	int phy;

#if !defined(CONFIG_AXXIA_ANY_XLF)
	srio0_mode = (control & 0x8) >> 3;
	srio1_mode = (control & 0x10) >> 4;

	srio0_speed = (control & 0x7000) >> 12;
	srio1_speed = (control & 0x38000) >> 15;

	srio0_ctrl = (control & 0x300) >> 8;
	srio1_ctrl = (control & 0xc00) >> 10;

	pei1_mode = (control & 0x2) >> 1;
	pei2_mode = (control & 0x4) >> 2;
#endif

	pei0_mode = (control & 0x1);

	rc_mode = (control & 0x80) >> 7;

	disable_ltssm(PEI0);

	for (phy = 0; phy < 4; phy++)
		enable_reset(phy);

	/* Disable all interfaces */
	ncr_read32(NCP_REGION_ID(0x115, 0), 0, &reg_val);
	reg_val &= ~(0xf | (0x1 << 10) | (0x3 << 29));
	ncr_write32(NCP_REGION_ID(0x115, 0), 0, reg_val);
	mdelay(100);		/* TODO: Why is this needed? */

#if defined(TRACE_PEI_ACCESSES)
	printf("%s:%d - get_config(0x%x) = 0x%x\n",
	       __FILE__, __LINE__, control, get_config(control));
#endif

	switch (get_config(control)) {
	case 1:
#if defined(CONFIG_AXXIA_ANY_56XX)
		/*
		  PEI0x4  (HSS10-ch0,1; HSS11-ch0,1)
		  PEI1x4  (HSS12-ch0,1; HSS13-ch0,1)
		*/

		set_sw_port_config0(pc0_PEI0x4);
		set_sw_port_config1(pc1_PEI1x4);
		set_pei0_rc_mode(rc_mode);
		set_pipe_port_sel(pp_0_1);
		set_pipe_nphy(four_phy);

		if (pei0_mode)
			for (phy = 0; phy < 2; phy++)
				release_reset(phy);
		if (pei1_mode)
			for (phy = 2; phy < 4; phy++)
				release_reset(phy);

		ncr_read32(NCP_REGION_ID(0x115, 0), 0x0, &reg_val);
		reg_val |= (pei0_mode << 0) | (pei1_mode << 1);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x0, reg_val);
#elif defined(CONFIG_AXXIA_ANY_XLF)
		/*
		  PEI0x2  (HSS15-ch0,1)
		*/

		set_pei0_rc_mode(rc_mode);
		set_pipe_port_sel(pp_0);
		set_pipe_nphy(four_phy);

		if (pei0_mode)
			for (phy = 0; phy < 2; phy++)
				release_reset(phy);

		ncr_read32(NCP_REGION_ID(0x115, 0), 0x0, &reg_val);
		reg_val |= (pei0_mode << 0);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x0, reg_val);
#endif
		break;
	case 2:
#if defined(CONFIG_AXXIA_ANY_56XX)
		/*
		  PEI0x2  (HSS10-ch0,1)
		  PEI2x2  (HSS11-ch0,1)
		  PEI1x2  (HSS12-ch0,1)
		  UNUSED  (HSS13-ch0,1)
		*/

		set_sw_port_config0(pc0_PEI0x2_PEI2x2);
		set_sw_port_config1(pc1_PEI1x2_PEI2x2);
		set_pei0_rc_mode(rc_mode);
		set_pipe_port_sel(pp_0_1_2_3);

		if (pei0_mode)
			release_reset(0);
		if (pei1_mode)
			release_reset(1);
		if (pei2_mode)
			release_reset(2);

		/* Enable PEI0/PEI1/PEI2 */
		ncr_read32(NCP_REGION_ID(0x115, 0), 0, &reg_val);
		reg_val |= (pei0_mode << 0) | (pei1_mode << 1) |
			(pei2_mode << 2);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0, reg_val);
#elif defined(CONFIG_AXXIA_ANY_XLF)
		/*
		  PEI0x1  (HSS15-ch0)
		*/

		set_pei0_rc_mode(rc_mode);
		set_pipe_port_sel(pp_0);
		set_pipe_nphy(four_phy);

		if (pei0_mode)
			for (phy = 0; phy < 2; phy++)
				release_reset(phy);

		ncr_read32(NCP_REGION_ID(0x115, 0), 0x0, &reg_val);
		reg_val |= (pei0_mode << 0);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x0, reg_val);
#endif
		break;
#if defined(CONFIG_AXXIA_ANY_56XX)
	case 3:
		/*
		  PEI0x2  (HSS10-ch0,1)
		  SRIO0x2 (HSS11-ch0,1)
		  UNUSED  (HSS12-ch0,1)
		  PEI2x2  (HSS13-ch0,1)
		  INFO: Formerly case 6...
		*/

		set_pei0_rc_mode(rc_mode);
		set_sw_port_config0(pc0_PEI0x2_SRIO0x2);
		set_sw_port_config1(pc1_PEI1x2_PEI2x2);
		set_pipe_port_sel(pp_0_1_2_3);
		set_pipe_nphy(three_phy);

		if (pei0_mode)
			release_reset(0);
		if (pei1_mode)
			release_reset(2);
		if (pei2_mode)
			release_reset(3);

		/* Enable PEI0/PEI1/PEI2 */
		ncr_read32(NCP_REGION_ID(0x115, 0), 0, &reg_val);
		reg_val |= (pei0_mode << 0) | (pei1_mode << 1) |
			(pei2_mode << 2);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0, reg_val);

		set_srio_mode(SRIO0, srio0_ctrl);
		set_srio_speed(SRIO0, srio0_speed);
		if (srio0_mode) {
			printf("Set up sRIO0 -- %d\n", srio0_speed);
			setup_srio_mode(SRIO0, srio0_speed);
			if (release_srio_reset(SRIO0, srio0_speed))
				srio0_mode = 0;
		}

		if (srio0_mode && powerup_srio_lanes(SRIO0, P1))
			srio0_mode = 0;

		/* Set TX clock ready */
		if (srio0_mode) {
			set_tx_clk_ready();

			if (powerup_srio_lanes(SRIO0, P0))
				srio0_mode = 0;
		}
		if (srio0_mode)
			enable_srio_lanes(SRIO0);

		/* Enable SRIO0 */
		ncr_read32(NCP_REGION_ID(0x115, 0), 0, &reg_val);
		reg_val |= (srio0_mode << 3);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0, reg_val);
		break;
	case 4:
		/*
		  SRIO1x2 (HSS10-ch0,1)
		  SRIO0x2 (HSS11-ch0,1)
		  UNUSED  (HSS12-ch0,1)
		  PEI2x2  (HSS13-ch0,1)
		*/

		set_sw_port_config0(pc0_SRIO1x2_SRIO0x2);
		set_sw_port_config1(pc1_PEI1x2_PEI2x2);
		set_pipe_port_sel(pp_0_1_2_3);

		if (pei1_mode)
			release_reset(2);
		if (pei2_mode)
			release_reset(3);

		/* Enable PEI1/PEI2 */
		ncr_read32(NCP_REGION_ID(0x115, 0), 0, &reg_val);
		reg_val |= (pei1_mode << 1) | (pei2_mode << 2);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0, reg_val);

		set_srio_mode(SRIO0, srio0_ctrl);
		set_srio_mode(SRIO1, srio1_ctrl);
		set_srio_speed(SRIO0, srio0_speed);
		set_srio_speed(SRIO1, srio1_speed);
		if (srio0_mode) {
			printf("Set up sRIO0 -- %d\n", srio0_speed);
			setup_srio_mode(SRIO0, srio0_speed);
			if (release_srio_reset(SRIO0, srio0_speed))
				srio0_mode = 0;
		}
		if (srio1_mode) {
			printf("Set up sRIO1 -- %d\n", srio1_speed);
			setup_srio_mode(SRIO1, srio1_speed);
			if (release_srio_reset(SRIO1, srio1_speed))
				srio1_mode = 0;
		}
		printf("Enabling sRIO .");
		/* Power up TX/RX lanes */
		if (srio0_mode && powerup_srio_lanes(SRIO0, P1))
			srio0_mode = 0;
		if (srio1_mode && powerup_srio_lanes(SRIO1, P1))
			srio1_mode = 0;

		printf(".");
		/* Set TX clock ready */
		if (srio0_mode || srio1_mode)
			set_tx_clk_ready();

		/* Power up TX/RX lanes */
		if (srio0_mode && powerup_srio_lanes(SRIO0, P0))
			srio0_mode = 0;
		if (srio1_mode && powerup_srio_lanes(SRIO1, P0))
			srio1_mode = 0;
		printf(".");

		if (srio0_mode)
			enable_srio_lanes(SRIO0);
		if (srio1_mode)
			enable_srio_lanes(SRIO1);
		printf(".");
		/* Enable SRIO0/SRIO1 */
		ncr_read32(NCP_REGION_ID(0x115, 0), 0, &reg_val);
		reg_val |= (srio0_mode << 3) | (srio1_mode << 10);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0, reg_val);
		printf("Done\n");
		break;
#endif
	default:
		error("Configuration not Handled: 0x%x\n", get_config(control));
		break;
	}

	return 0;
}

/*
 *  pciesrio_init
 */
int
pciesrio_init(unsigned int control)
{
#ifdef DISPLAY_PARAMETERS
	printf("-- -- PCIe/SRIO\n"
	       "0x%x, 0x%x\n",
	       pciesrio->version, pciesrio->control);

	if (2 == pciesrio->version) {
		printf("0x%x 0x%x\n"
		       "0x%x, 0x%x, 0x%x 0x%x\n"
		       "0x%x, 0x%x, 0x%x 0x%x\n",
		       pciesrio->primary_input_clock,
		       pciesrio->input_ref_clock_range,
		       pciesrio->lane_0_eq_main,
		       pciesrio->lane_0_eq_pre,
		       pciesrio->lane_0_eq_post,
		       pciesrio->lane_0_vboost,
		       pciesrio->lane_1_eq_main,
		       pciesrio->lane_1_eq_pre,
		       pciesrio->lane_1_eq_post,
		       pciesrio->lane_1_vboost);
	}
#endif	/* DISPLAY_PARAMETERS */

	if (0 != verify_control(control)) {
		error("Invalid Control Value: 0x%x\n", control);

		return -1;
	}

	if (0x80000000 != control) {
#ifdef TRACE_PEI_ACCESSES
		printf("%s:%d - Starting Trace: 0x%x\n",
		       __FILE__, __LINE__, control);
		ncr_tracer_enable();
#endif
		pei_setup(control);
		update_settings();
#ifdef TRACE_PEI_ACCESSES
		ncr_tracer_disable();
		printf("%s:%d - Trace is Over\n", __FILE__, __LINE__);
#endif
	}

	return 0;
}
