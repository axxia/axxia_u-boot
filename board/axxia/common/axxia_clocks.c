/*
 *  Copyright (C) 2015 Intel
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

/*
  ==============================================================================
  ==============================================================================
  Public Interface
  ==============================================================================
  ==============================================================================
*/

unsigned int pfuse __attribute__ ((section ("data")));

#ifndef CONFIG_AXXIA_EMU
#ifdef CONFIG_SPL_BUILD

#define PARAMETERS_CLOCKS_55XX_1P0_HARDCODE     0x00000001

/*
  ------------------------------------------------------------------------------
  pll_init_5500
*/

#define PARAMETER_MASK 0x3ffffff
#define CONTROL_MASK 0x3df300

static int
pll_init_5500(ncp_uint32_t region, ncp_uint32_t *parameters)
{
	int i, timeout = 10000;
	ncp_uint32_t value, prms;

	/*
	  Set the parameter value and reset the PLL, with
	  bypass and bypass_select (in the control register), set.

	  Enable the PLL.
	*/
	ncr_write32(region, 0x4, (parameters[1] & CONTROL_MASK) | 0xc00);
	prms = (parameters[0] & PARAMETER_MASK) | 0x80000000;
	ncr_write32(region, 0x0, prms);
	udelay(100);
	ncr_write32(region, 0x4, (parameters[1] & CONTROL_MASK) | 0xc02);

	/*
	  Enable clock_sync for DDR PLLs
	*/

	if ((region == NCP_REGION_ID(0x155, 6)) ||
	    (region == NCP_REGION_ID(0x155, 7)) ||
	    (region == NCP_REGION_ID(0x155, 8))) {
		prms |= 0x40000000;
		ncr_write32(region, 0x0, prms);
	}

	/*
	  Wait for pll_locked.
	*/
	do {
		ncr_read32(region, 0x20, &value);
	} while ((0 == (value & 0x80000000) &&
		  (0 < --timeout)));

	if (0 == timeout)
		return -1;

	/*
	  Clear bypass.
	*/
	ncr_write32(region, 0x4, (parameters[1] & CONTROL_MASK) | 0x402);

	/*
	  Clear the lock loss count and interrupt, and enable the count.
	*/
	ncr_write32(region, 0xc, 0);
	ncr_write32(region, 0x10, 1);
	prms |= 0x20000000;
	ncr_write32(region, 0x0, prms);

	/*
	  Set the divider and switch the clocks
	  CPUPLL has multiple switches.
	*/
	if (region == NCP_REGION_ID(0x155, 4)) {
		/* CPUPLL */
		if (0 != parameters[3]) {
			ncr_write32(NCP_REGION_ID(0x156,0), 0x8, parameters[3]);
			ncr_read32(NCP_REGION_ID(0x156,0), 0xc, &value);
			value |= 0x100000;
			ncr_write32(NCP_REGION_ID(0x156,0), 0xc, value);
			value &= ~0x100000;
			ncr_write32(NCP_REGION_ID(0x156,0), 0xc, value);
		}
		if (0 != parameters[2]) {
			/* Switch the cluster clocks individually */
			value = 0;
			for (i = 0; i < 4; i++) {
				value |= parameters[2] & (0x3 << (i * 2));
				ncr_write32(NCP_REGION_ID(0x156,0), 0x0, value);
				udelay(parameters[4]);
			}
		}
	} else {
		if (0 != parameters[3]) {
			ncr_read32(NCP_REGION_ID(0x156,0), 0xc, &value);
			value |= parameters[3];
			ncr_write32(NCP_REGION_ID(0x156,0), 0xc, value);
			value &= ~0x100000;
			ncr_write32(NCP_REGION_ID(0x156,0), 0xc, value);
		}
		if (0 != parameters[2]) {
			ncr_read32(NCP_REGION_ID(0x156,0), 0x4, &value);
			value |= parameters[2];
			ncr_write32(NCP_REGION_ID(0x156,0), 0x4, value);
			udelay(parameters[4]);
		}
	}

	return 0;
}

/*
  ------------------------------------------------------------------------------
  clocks_init
*/

int
clocks_init( void )
{
	ncp_uint32_t value;

#ifdef DISPLAY_PARAMETERS
	printf("-- -- Clocks\n"
	       "0x%lx\n"
	       "0x%lx 0x%lx 0x%lx 0x%lx 0x%lx\n"
	       "0x%lx 0x%lx 0x%lx 0x%lx 0x%lx\n"
	       "0x%lx 0x%lx 0x%lx 0x%lx 0x%lx\n"
	       "0x%lx 0x%lx 0x%lx 0x%lx 0x%lx\n"
	       "0x%lx 0x%lx 0x%lx 0x%lx 0x%lx\n"
	       "0x%lx 0x%lx 0x%lx 0x%lx 0x%lx\n"
	       "0x%lx 0x%lx 0x%lx 0x%lx\n"
	       "0x%lx 0x%lx 0x%lx 0x%lx\n",
	       clocks->flags,
	       clocks->syspll_prms, clocks->syspll_ctrl, clocks->syspll_csw,
	       clocks->syspll_div, clocks->syspll_psd, clocks->cpupll_prms,
	       clocks->cpupll_ctrl, clocks->cpupll_csw, clocks->cpupll_div,
	       clocks->cpupll_psd, clocks->sm0pll_prms, clocks->sm0pll_ctrl,
	       clocks->sm0pll_csw, clocks->sm0pll_div, clocks->sm0pll_psd,
	       clocks->sm1pll_prms, clocks->sm1pll_ctrl, clocks->sm1pll_csw,
	       clocks->sm1pll_div, clocks->sm1pll_psd, clocks->tmpll_prms,
	       clocks->tmpll_ctrl, clocks->tmpll_csw, clocks->tmpll_div,
	       clocks->tmpll_psd, clocks->fabpll_prms, clocks->fabpll_ctrl,
	       clocks->fabpll_csw, clocks->fabpll_div, clocks->fabpll_psd,
	       clocks->nrcpinput_csw, clocks->nrcpinput_div,
	       clocks->per_csw, clocks->per_div, clocks->emmc_csw,
	       clocks->emmc_div, clocks->debug_csw, clocks->stop_csw);
#endif


	/*
	  ----------------------------------------------------------------------
	  PLL Setup
	  ----------------------------------------------------------------------
	*/

	/* fabpll */
	if ((0 == ((pfuse & 0x7e0) >> 5)) &&
	    (clocks->flags & PARAMETERS_CLOCKS_55XX_1P0_HARDCODE))
	{
		clocks->fabpll_prms = 0x20000d1;
		clocks->fabpll_ctrl = 0x20c100;
		clocks->fabpll_csw  = 0x10;
		clocks->fabpll_div  = 0x0;
	}
	if (0 != pll_init_5500(NCP_REGION_ID(0x155, 3), &clocks->fabpll_prms))
		return -1;


	/* cpupll */
	if (0 != pll_init_5500(NCP_REGION_ID(0x155, 4), &clocks->cpupll_prms))
		return -1;

	/* Debug Clock Setup */
	ncr_read32(NCP_REGION_ID(0x156,0), 0x4, &value);
	value |= clocks->debug_csw;
	value |= clocks->stop_csw;
	ncr_write32(NCP_REGION_ID(0x156,0), 0x4, value);

	/* syspll */
	if ((0 == ((pfuse & 0x7e0) >> 5)) &&
	    (clocks->flags & PARAMETERS_CLOCKS_55XX_1P0_HARDCODE))
	{
		clocks->syspll_prms = 0x2981804;
		clocks->syspll_ctrl = 0x209100;
		clocks->syspll_csw  = 0x4;
		clocks->syspll_div  = 0x0;
	}
	if (0 != pll_init_5500(NCP_REGION_ID(0x155, 5), &clocks->syspll_prms))
		return -1;

	/* NRCP input clock select */
	if (0 != clocks->nrcpinput_div) {
		ncr_read32(NCP_REGION_ID(0x156,0), 0xc, &value);
		value |= clocks->nrcpinput_div;
		ncr_write32(NCP_REGION_ID(0x156,0), 0xc, value);
		value &= ~0x100000;
		ncr_write32(NCP_REGION_ID(0x156,0), 0xc, value);
	}

	if (0 != clocks->nrcpinput_csw) {
		ncr_read32(NCP_REGION_ID(0x156,0), 0x4, &value);
		value |= clocks->nrcpinput_csw;
		ncr_write32(NCP_REGION_ID(0x156,0), 0x4, value);
		udelay(clocks->cpupll_psd);
	}

	/* DDR */
	/*
	  Enable protected writes and put the DDRs in reset.
	  0x156.0.0x1038 - Reset Module Register
	  smem[0,1]_phy_rst, smem[0,1]_phy_io_rst
	  cmem_phy_rst, cmem[0,1]_phy_io_rst
	*/
	ncr_write32(NCP_REGION_ID(0x156, 0), 0x1000, 0x000000ab);
	ncr_write32(NCP_REGION_ID(0x156, 0), 0x1038, 0x01e00000);
	ncr_write32(NCP_REGION_ID(0x156, 0), 0x103c, 0x24000008);
	udelay(1000);


	/* sm0pll */
	if (0 != pll_init_5500(NCP_REGION_ID(0x155, 6), &clocks->sm0pll_prms))
		return -1;

	/* sm1pll */
	if (0 != pll_init_5500(NCP_REGION_ID(0x155, 7), &clocks->sm1pll_prms))
		return -1;

	/* Set the peripheral clock */
	if (0 != clocks->per_div) {
		ncr_read32(NCP_REGION_ID(0x156,0), 0xc, &value);
		value |= clocks->per_div;
		ncr_write32(NCP_REGION_ID(0x156,0), 0xc, value);
		value &= ~0x100000;
		ncr_write32(NCP_REGION_ID(0x156,0), 0xc, value);
	}
	if (0 != clocks->per_csw) {
		ncr_read32(NCP_REGION_ID(0x156,0), 0x4, &value);
		value |= clocks->per_csw;
		ncr_write32(NCP_REGION_ID(0x156,0), 0x4, value);
		udelay(clocks->sm1pll_psd);
	}

	/* Set the emmc clock */
	if (0 != clocks->emmc_div) {
		ncr_read32(NCP_REGION_ID(0x156,0), 0xc, &value);
		value |= clocks->emmc_div;
		ncr_write32(NCP_REGION_ID(0x156,0), 0xc, value);
		value &= ~0x100000;
		ncr_write32(NCP_REGION_ID(0x156,0), 0xc, value);
	}
	if (0 != clocks->emmc_csw) {
		ncr_read32(NCP_REGION_ID(0x156,0), 0x4, &value);
		value |= clocks->emmc_csw;
		ncr_write32(NCP_REGION_ID(0x156,0), 0x4, value);
		udelay(clocks->sm1pll_psd);
	}

	/* tm0pll */
	if (0 != pll_init_5500(NCP_REGION_ID(0x155, 8), &clocks->tmpll_prms))
		return -1;

	/*
	  Take DDRs out of reset and disable protected writes.
	*/
	ncr_write32(NCP_REGION_ID(0x156, 0), 0x1038, 0x0);
	ncr_write32(NCP_REGION_ID(0x156, 0), 0x103c, 0x0);
	ncr_write32(NCP_REGION_ID(0x156, 0), 0x1000, 0x0);

	return 0;
}

#endif

#ifndef CONFIG_AXXIA_SIM
static ncp_uint32_t
get_pll(ncp_uint32_t prms, ncp_uint32_t seldiv)
{
	ncp_uint32_t frequency;
	ncp_uint32_t postdiv;
	ncp_uint32_t fbdiv;
	ncp_uint32_t refdiv;

	postdiv = (prms & 0xf) + 1;
	fbdiv = ((prms & 0xfff0) >> 4) + 3;
	refdiv = ((prms & 0x1f0000) >> 16) + 1;
	frequency =  CLK_REF0 / 1000;
	frequency *= fbdiv;
	frequency /= refdiv;
	frequency /= postdiv;
	frequency /= seldiv;

	return frequency;
}
#endif

#endif

/*
  ------------------------------------------------------------------------------
  axxia_clock_get
*/

int
acp_clock_get(acp_clock_t clock, ncp_uint32_t *frequency)
{
#if defined(CONFIG_AXXIA_SIM)

	switch (clock) {
	case clock_system:
		*frequency = 387000;
		break;
	case clock_peripheral:
		*frequency = 200000;
		break;
	case clock_core:
		*frequency = 1400000;
		break;
	case clock_emmc:
		*frequency = 200000;
		break;
	default:
		*frequency = 0ULL;
		return -1;
		break;
	}
	return 0;

#elif defined(CONFIG_AXXIA_EMU)

	switch (clock) {
	case clock_system:
		*frequency = 4096;
		break;
	case clock_peripheral:
		*frequency = 2000;
		break;
	case clock_core:
		*frequency = 2000;
		break;
	case clock_emmc:
		*frequency = 2000;
		break;
	default:
		*frequency = 0ULL;
		return -1;
		break;
	}

	return 0;

#else
	ncp_uint32_t csw;
	ncp_uint32_t div;
	ncp_uint32_t prms;

	switch (clock) {
	case clock_fab:
		ncr_read32(NCP_REGION_ID(0x156,0), 0x4, &csw);

		if (0 == (csw & 0x00000030)) {
			*frequency = CLK_REF0 / 1000;
		} else if (1 == (csw & 0x00000030)) {
			ncr_read32(NCP_REGION_ID(0x155,3), 0x0, &prms);
			*frequency = get_pll(prms, 1);
		} else {
			ncr_read32(NCP_REGION_ID(0x155,3), 0x0, &prms);
			ncr_read32(NCP_REGION_ID(0x156,0), 0xc, &div);
			*frequency = get_pll(prms,
					     ((div & 0xf00) >> 8) + 1);
		}
		break;
	case clock_system:
		ncr_read32(NCP_REGION_ID(0x156,0), 0x4, &csw);

		if (0 == (csw & 0x0000000c)) {
			*frequency = CLK_REF0 / 1000;
		} else if (1 == (csw & 0x0000000c)) {
			ncr_read32(NCP_REGION_ID(0x155,5), 0x0, &prms);
			*frequency = get_pll(prms, 1);
		} else {
			ncr_read32(NCP_REGION_ID(0x155,5), 0x0, &prms);
			ncr_read32(NCP_REGION_ID(0x156,0), 0xc, &div);
			*frequency = get_pll(prms,
					     ((div & 0xf0) >> 4) + 1);
		}
		break;

	case clock_core:  /* returns cluster0 speed */
		ncr_read32(NCP_REGION_ID(0x156,0), 0x0, &csw);

		if (0 == (csw & 0x00000003)) {
			*frequency = CLK_REF0 / 1000;
		} else if (1 == (csw & 0x00000003)) {
			ncr_read32(NCP_REGION_ID(0x155,4), 0x0, &prms);
			*frequency = get_pll(prms, 1);
		} else {
			ncr_read32(NCP_REGION_ID(0x155,4), 0x0, &prms);
			ncr_read32(NCP_REGION_ID(0x156,0), 0x8, &div);
			*frequency = get_pll(prms, (div & 0xf) + 1);
		}
		break;

	case clock_memory:   /* returns sm0 speed */
		ncr_read32(NCP_REGION_ID(0x155,6), 0x0, &prms);
		*frequency = get_pll(prms, 1);
		break;

	case clock_treemem:
		ncr_read32(NCP_REGION_ID(0x155,8), 0x0, &prms);
		*frequency = get_pll(prms, 1);
		break;

	case clock_peripheral:
		ncr_read32(NCP_REGION_ID(0x156,0), 0x4, &csw);

		if (0 == (csw & 0x00000040)) {
			*frequency = CLK_REF0 / 1000;
		} else {
			ncr_read32(NCP_REGION_ID(0x155,7), 0x0, &prms);
			ncr_read32(NCP_REGION_ID(0x156,0), 0xc, &div);
			*frequency = get_pll(prms,
					     ((div & 0xf000) >> 12) + 1);
		}
		break;

	case clock_emmc:
		ncr_read32(NCP_REGION_ID(0x156,0), 0x4, &csw);

		if (0 == (csw & 0x00000100)) {
			*frequency = CLK_REF0 / 1000;
		} else {
			ncr_read32(NCP_REGION_ID(0x155,7), 0x0, &prms);
			ncr_read32(NCP_REGION_ID(0x156,0), 0xc, &div);
			*frequency = get_pll(prms,
					     ((div & 0xf0000) >> 16) + 1);
		}
		break;

	default:
		return -1;
		break;
	}

#endif

	return 0;
}

/*
  ------------------------------------------------------------------------------
*/

void
axxia_display_clocks(void)
{
	ncp_uint32_t speed;
	ncp_uint32_t loss_count0;
	ncp_uint32_t loss_count1;

	acp_clock_get(clock_system, &speed);
	speed /= 1000;
	ncr_read32(NCP_REGION_ID(0x155, 5), 0xc, &loss_count0);
	printf("    System: %4u MHz Loss of Lock Count %u\n",
	       speed, loss_count0);

	acp_clock_get(clock_core, &speed);
	speed /= 1000;
	ncr_read32(NCP_REGION_ID(0x155, 4), 0xc, &loss_count0);
	printf("       Cpu: %4u MHz Loss of Lock Count %u\n",
	       speed, loss_count0);

	acp_clock_get(clock_memory, &speed);
	speed /= 1000;
	ncr_read32(NCP_REGION_ID(0x155, 6), 0xc, &loss_count0);
	ncr_read32(NCP_REGION_ID(0x155, 7), 0xc, &loss_count1);
	printf("    Memory: %4u MHz Loss of Lock Count %u/%u\n",
	       speed, loss_count0, loss_count1);

	acp_clock_get(clock_fab, &speed);
	speed /= 1000;
	ncr_read32(NCP_REGION_ID(0x155, 3), 0xc, &loss_count0);
	printf("    Fabric: %4u MHz Loss of Lock Count %u\n",
	       speed, loss_count0);

	acp_clock_get(clock_treemem, &speed);
	speed /= 1000;
	ncr_read32(NCP_REGION_ID(0x155, 8), 0xc, &loss_count0);
	printf("      Tree: %4u MHz Loss of Lock Count %u\n",
	       speed, loss_count0);

	acp_clock_get(clock_peripheral, &speed);
	speed /= 1000;
	printf("Peripheral: %4u MHz\n", speed);

	acp_clock_get(clock_emmc, &speed);
	speed /= 1000;
	printf("   SD/eMMC: %4u MHz\n", speed);

	return;
}
