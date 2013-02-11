/*
 *  Copyright (C) 2009 LSI Corporation
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

#include <common.h>

/*
  ===============================================================================
  ===============================================================================
  Private Interface
  ===============================================================================
  ===============================================================================
*/

#if defined(ACP_25xx)

static unsigned long
get_pll(unsigned long prms, unsigned long seldiv)
{
	unsigned long frequency;
	unsigned long postdiv;
	unsigned long fbdiv;
	unsigned long refdiv;

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

#else

static unsigned char ps[] = {1, 3, 2, 4};

static unsigned char idiv[] = {
	1, 16, 17, 30, 13, 18, 7, 31, 14, 11, 19, 21, 27, 8, 23, 32,
	15, 29, 12, 6, 10, 20, 26, 22, 28, 5, 9, 25, 4, 24, 3, 2};

static unsigned char odiv[] = {
	1, 2, 28, 27, 22, 21, 30, 29, 24, 23, 12, 11, 16, 15, 32, 31,
	26, 25, 20, 19, 10, 9, 14, 13, 18, 17, 8, 7, 6, 5, 4, 3};

static unsigned char mult[] = {
	1, 123, 117, 251, 245, 69, 111, 125, 119, 95, 105, 197, 239,
	163, 63, 253, 247, 187, 57, 223, 233, 207, 157, 71, 113, 15,
	89, 37, 191, 19, 99, 127, 121, 109, 93, 61, 185, 155, 13, 97,
	107, 11, 9, 81, 31, 49, 83, 199, 241, 33, 181, 143, 217, 173,
	51, 165, 65, 85, 151, 147, 227, 41, 201, 255, 249, 243, 195,
	237, 221, 231, 35, 189, 59, 183, 79, 29, 141, 215, 145, 225,
	235, 219, 27, 139, 137, 135, 175, 209, 159, 53, 45, 177, 211,
	23, 167, 73, 115, 67, 103, 161, 55, 205, 87, 17, 91, 153, 7,
	47, 179, 171, 149, 39, 193, 229, 77, 213, 25, 133, 43, 21,
	101, 203, 5, 169, 75, 131, 3, 129, 1, 250, 244, 124, 118, 196,
	238, 252, 246, 222, 232, 70, 112, 36, 190, 126, 120, 60, 184,
	96, 106, 80, 30, 198, 240, 142, 216, 164, 64, 146, 226, 254,
	248, 236, 220, 188, 58, 28, 140, 224, 234, 138, 136, 208, 158,
	176, 210, 72, 114, 160, 54, 16, 90, 46, 178, 38, 192, 212, 24,
	20, 100, 168, 74, 128, 122, 116, 68, 110, 94, 104, 162, 62,
	186, 56, 206, 156, 14, 88, 18, 98, 108, 92, 154, 12, 10, 8,
	48, 82, 32, 180, 172, 50, 84, 150, 40, 200, 242, 194, 230, 34,
	182, 78, 214, 144, 218, 26, 134, 174, 52, 44, 22, 166, 66,
	102, 204, 86, 152, 6, 170, 148, 228, 76, 132, 42, 202, 4, 130,
	2
};

#define PREDIV(value)       (idiv[(((value) & 0xfc000000) >> 26)])
#define MULTINT(value)      (((value) & 0x00000ffe) >> 1)
#define MULTINT_PRE(value)  (ps[((MULTINT((value)) & 0x300) >> 8)])
#define MULTINT_MAIN(value) (mult[(MULTINT((value)) & 0xff)])
#define RANGEA(value)       (((value) & 0x03f80000) >> 19)
#define RANGEA_PRE(value)   (ps[((RANGEA((value)) & 0x60) >> 5)])
#define RANGEA_MAIN(value)  (odiv[(RANGEA((value)) & 0x1f)])
#define RANGEB(value)       (((value) & 0x0007f000) >> 12)
#define RANGEB_PRE(value)   (ps[((RANGEB((value)) & 0x60) >> 5)])
#define RANGEB_MAIN(value)  (odiv[(RANGEB((value)) & 0x1f)])
#if 0
#define MULTFRAC(tune2, tune3) \
((((tune3 >> 8) & 0xFFFF00) | (tune2 & 0xFF)) / (16777216))
#endif

/*
  ------------------------------------------------------------------------------
  get_ppc_pll

  Assumes the the PPC PLL is locked...
*/

static int
get_ppc_pll(unsigned long *dco, unsigned long *pllouta, unsigned long *plloutb)
{
	unsigned long ctrl;

	ctrl = dcr_read(0xd02);

	*dco = (CLK_REF0 / 1000 / PREDIV(ctrl));
	*dco *= (MULTINT_PRE(ctrl) * MULTINT_MAIN(ctrl));
	*pllouta = *dco / (RANGEA_PRE(ctrl) * RANGEA_MAIN(ctrl));
	*plloutb = *dco / (RANGEA_PRE(ctrl) * RANGEB_MAIN(ctrl));

	return 0;
}

#endif

/*
  ===============================================================================
  ===============================================================================
  Public Interface
  ===============================================================================
  ===============================================================================
*/

/*
  -------------------------------------------------------------------------------
  acp_clock_get
*/

#if defined(ACP_ISS) || defined(ACP_EMU)

int
acp_clock_get(acp_clock_t clock, unsigned long *frequency)
{
	*frequency = 0ULL;

	/*
	  Clocks are only available on the ASIC.
	*/

	switch (clock) {
	case clock_peripheral:
		*frequency = 6500;
		break;
	case clock_ppc:
		*frequency = 12500;
		break;
	default:
		return -1;
		break;
	}

	return 0;
}

#else

/*
  ------------------------------------------------------------------------------
  acp_clock_get
*/

int
acp_clock_get(acp_clock_t clock, unsigned long *frequency)
{
#if defined(ACP_25xx)
	unsigned long mcgc;
	unsigned long mcgc1;
	unsigned long prms;

	switch (clock) {
	case clock_sys:
		mcgc = dcr_read(0xd00);

		if (0 == (mcgc & 0x30000000)) {
			*frequency = CLK_REF0 / 1000;
		} else {
			prms = dcr_read(0xd40);
			*frequency = get_pll(prms, ((mcgc & 0xf0000) >> 16) + 1);
		}
		break;
	case clock_ppc:
		mcgc = dcr_read(0xd00);

		if (0 == (mcgc & 0xc0000000)) {
			*frequency = CLK_REF0 / 1000;
		} else {
			prms = dcr_read(0xd50);
			*frequency = get_pll(prms,
					     ((mcgc & 0xf00000) >> 20) + 1);
		}
		break;
	case clock_ddr:
		prms = dcr_read(0xd70);
		*frequency = get_pll(prms, 1);
		break;
	case clock_peripheral:
		mcgc1 = dcr_read(0xd01);

		switch (((mcgc1 & 0xc000) >> 14) & 0x3) {
		case 0x0:
			*frequency = CLK_REF0 / 1000;
			break;
		case 0x1:
			mcgc = dcr_read(0xd00);
			prms = dcr_read(0xd50);
			*frequency = get_pll(prms, ((mcgc & 0xf000) >> 12) + 1);
			break;
		case 0x2:
		case 0x3:
			mcgc = dcr_read(0xd00);
			prms = dcr_read(0xd40);
			*frequency = get_pll(prms, ((mcgc1 & 0xf00) >> 8) + 1);
			break;
		default:
			break;
		}
		break;
	default:
		return -1;
		break;
	}

	return 0;
#else
	unsigned long mcgc;
	unsigned long mcgs;
	unsigned long dco = 0;
	unsigned long pllouta;
	unsigned long plloutb;

	*frequency = 0ULL;

	mcgc = dcr_read(0xd00);
	mcgs = dcr_read(0xd01);

	switch (clock) {
	case clock_ppc:
		if (0 == (mcgc & 0xc0000000)) {
			/* ppc_clk is clk_ref0 */
			*frequency = CLK_REF0 / 1000;
		} else if (0 == get_ppc_pll(&dco, &pllouta, &plloutb)) {
			if (1 == ((mcgc & 0xc0000000) >> 30)) {
				*frequency = pllouta;
			} else {
				*frequency = pllouta / 2;
			}
		} else {
			return -1;
		}
		break;
	case clock_peripheral:
		if (0 == (mcgc & 0x08000000)) {
			/* clk_per is clk_ref0 */
			*frequency = CLK_REF0 / 1000;
 		} else {
			/* clk_per is clk_pllb_ppc */
			if (0 == (mcgs & 0x80000000) ||
			    (0 == dco &&
			     0 != get_ppc_pll(&dco, &pllouta, &plloutb))) {
				return -1;
			}

			*frequency = plloutb;
		}
		break;
	default:
		return -1;
		break;
	}

	return 0;
#endif
}

#if defined(ACP_25xx)
void
axm2500_pll_check_lock(void)
{
	int i;
	int offset = 0xd40;
	unsigned long pll_stat;
	unsigned long dcr_pllctl_int_status;
	char *pll_names[] = {"SYS", "PPC", "TM", "SM"};

	for (i = 0; i < 4; ++i) {
		pll_stat = dcr_read(offset + 0xa);
		dcr_pllctl_int_status = dcr_read(offset + 0x4);

		if (0 == (pll_stat & 0x80000000UL)) {
			printf("%s PLL is NOT locked!\n",
			       pll_names[(offset - 0xd40)/0x10]);
		}

		if (0 != (dcr_pllctl_int_status & 1)) {
			printf("%s lost lock at some point...\n",
			       pll_names[(offset - 0xd40)/0x10]);
			dcr_pllctl_int_status &= ~0x1UL;
			dcr_write(dcr_pllctl_int_status, (offset + 0x4));
		}

		offset += 0x10;
	}
}
#endif

/*
  ==============================================================================
  ==============================================================================
  ==============================================================================
  ==============================================================================
  ==============================================================================
*/

#ifdef CONFIG_ACP3

/*
  ------------------------------------------------------------------------------
  acp_clock_set_gpio
*/

static void
acp_clock_set_gpio(int value)
{
#ifdef CLOCK_LOCK_VERIFY_GPIO
	static int first_time = 1;
	static int last_value = 0x10;

	if (1 == first_time) {
		acpwriteio(0x0, (IO + 0x0410));	/* Disable Interrupts */
		acpwriteio(0x0, (IO + 0x1410));
		acpwriteio(0x0, (IO + 0x0420));	/* Disable Hardware Control */
		acpwriteio(0x0, (IO + 0x1420));
		acpwriteio(0x0d, (IO + 0x0400)); /* Set [3:2] to Output */
		acpwriteio(0x06, (IO + 0x1400)); /* Set [2:1] to Output */
		first_time = 0;
		last_value = 0xf;
	}

	if ((value & 0x1) != (last_value & 0x1))
		acpwriteio((0 == (value & 0x1)) ? 0x0 : 0x4,
			   (IO + (0x4 << 2)));

	if ((value & 0x2) != (last_value & 0x2))
		acpwriteio((0 == (value & 0x2)) ? 0x0 : 0x8,
			   (IO + (0x8 << 2)));

	if ((value & 0x4) != (last_value & 0x4))
		acpwriteio((0 == (value & 0x4)) ? 0x0 : 0x2,
			   (IO + 0x1000 + (0x2 << 2)));

	if ((value & 0x8) != (last_value & 0x8))
		acpwriteio((0 == (value & 0x8)) ? 0x0 : 0x4,
			   (IO + 0x1000 + (0x4 << 2)));

	last_value = value;

#endif /* CLOCK_LOCK_VERIFY_GPIO */
	return;
}

/*
  ------------------------------------------------------------------------------
  acp_clock_lock_verify
*/

int
acp_clock_lock_verify(int max_errors, int max_reads)
{
	unsigned long sysppc;
	unsigned long ddr0;
	unsigned long ddr1;
	unsigned long phy_pei_sta0;
	int this_state = 0;
	static int first_time = 1;
	static int toggle = 1;
	static unsigned long reads = 1;
	static unsigned long failures[] = {1, 1, 1, 1, 1, 1, 1};
	static unsigned long successes[] = {1, 1, 1, 1, 1, 1, 1};

	if (1 == first_time) {
		reads = 0;
		failures[0] = 0;
		failures[1] = 0;
		failures[2] = 0;
		failures[3] = 0;
		failures[4] = 0;
		failures[5] = 0;
		failures[6] = 0;
		successes[0] = 0;
		successes[1] = 0;
		successes[2] = 0;
		successes[3] = 0;
		successes[4] = 0;
		successes[5] = 0;
		successes[6] = 0;
		first_time = 0;
		acp_clock_set_gpio(0xf);
	}

#ifdef CLOCK_LOCK_VERIFY_GPIO
	acpwriteio(toggle, (IO + (0x01 << 2)));
#endif /* CLOCK_LOCK_VERIFY_GPIO */
	toggle ^= 1;
	sysppc = dcr_read(0xd01);
	ncr_read32(NCP_REGION_ID(0x23, 0), 0x1c, &ddr0);
	ncr_read32(NCP_REGION_ID(0xd, 0), 0x1c, &ddr1);
#ifndef ACP_X1V1
	phy_pei_sta0 = acpreadio((void *)(PCIE0_CONFIG + 0x10cc));
#else
	phy_pei_sta0 = 0;
#endif
	this_state = (phy_pei_sta0 >> 24) | (sysppc >> 28) | (ddr1 << 1) | ddr0;
	++reads;
	acp_clock_set_gpio(this_state);

	/* DDR0 */
	if ((this_state & 0x1) == 0x1)
		++successes[0];
	else
		++failures[0];

	/* DDR1 */
	if ((this_state & 0x2) == 0x2)
		++successes[1];
	else
		++failures[1];

	/* SYS */
	if ((this_state & 0x4) == 0x4)
		++successes[2];
	else
		++failures[2];
	/* PPC */
	if ((this_state & 0x8) == 0x8)
		++successes[3];
	else
		++failures[3];

	/* PHY PEI PLL B */
	if ((this_state & 0x10) == 0x10)
		++successes[4];
	else
		++failures[4];

	/* PHY PEI PLL A */
	if ((this_state & 0x20) == 0x20)
		++successes[5];
	else
		++failures[5];

	/* PHY PEI ENABLED PLL */
	if ((this_state & 0x40) == 0x40)
		++successes[6];
	else
		++failures[6];

	mb();

	if (((0 <= max_reads) && (max_reads <= reads)) ||
	    ((0 <= max_errors) &&
	     ((max_errors <= failures[0]) ||
	      (max_errors <= failures[1]) ||
	      (max_errors <= failures[2]) ||
	      (max_errors <= failures[3])))) {
		printf("0x%lx:"
		       "0x%lx/0x%lx:"
		       "0x%lx/0x%lx:"
		       "0x%lx/0x%lx:"
		       "0x%lx/0x%lx:"
		       "0x%lx/0x%lx:"
		       "0x%lx/0x%lx:"
		       "0x%lx/0x%lx\n",
		       reads,
		       successes[6], failures[6],
		       successes[5], failures[5],
		       successes[4], failures[4],
		       successes[3], failures[3],
		       successes[2], failures[2],
		       successes[1], failures[1],
		       successes[0], failures[0]);
		reads = 0;
		failures[0] = 0;
		failures[1] = 0;
		failures[2] = 0;
		failures[3] = 0;
		failures[4] = 0;
		failures[5] = 0;
		failures[6] = 0;
		successes[0] = 0;
		successes[1] = 0;
		successes[2] = 0;
		successes[3] = 0;
		successes[4] = 0;
		successes[5] = 0;
		successes[6] = 0;
	}

	return 0;
}

#endif
#endif
