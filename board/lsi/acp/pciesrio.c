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

#ifndef ACP_25xx

/*
  ==============================================================================
  ==============================================================================
  Pre-AXM2500 Interface
  ==============================================================================
  ==============================================================================
*/

/*
  -------------------------------------------------------------------------------
  pciesrio_set_control

  Note that there is no correct way to re-configure after changing
  from the initial/default setting of 0.

  BZ34471, BZ37018

  The steps are as follows.

  1. Disable all the macs, this is controlled by bit 3-0 in the pci_srio_phy_ctrl
  2. Change the configuration  bits as desired bit 12 ep/rc, bit 9-8
     sw_port_configuration
  3. Place the Phy in reset bit 31
  4. Take the Phy out reset bit
  5. Enable macs that are needed bits 3-0

*/

int
pciesrio_setcontrol_acp34xx(unsigned long new_control)
{
#if !defined(ACP_EMU) && !defined(ACP_ISS) && !defined(ACP_X1V1)
	unsigned long old_control;

	if (0 != (new_control & ~0x00003f8f)) {
		printf("Invalid PHY control value: 0x%08lx\n", new_control);
		return -1;
	}

	old_control = acpreadio((void *)GPREG_PHY_CTRL0);

	if (0 != old_control) {
		printf("Old PHY0 Controler MSUT be 0!\n");
		return -1;
	}

	new_control = old_control | new_control;
	printf("Switching PHY0 Control from 0x%08lx to 0x%08lx\n",
	       old_control, new_control);

	/* Write bits 12:8. (step 2.) */
	acpwriteio((new_control & 0x1f00), (void *)GPREG_PHY_CTRL0);

	/* Write bit 31. (step 3.) */
	acpwriteio(((new_control & 0x1f00) | 0x80000000),
		   (void *)GPREG_PHY_CTRL0);

	/* Clear bit 31. (step 4.) */
	acpwriteio((new_control & 0x1f00), (void *)GPREG_PHY_CTRL0);
	udelay(1000);

	/* Enable MACs that are specified in the parameter. (step 5.) */
	acpwriteio((new_control & 0x1f0f), (void *)GPREG_PHY_CTRL0);

	return 0;
#endif
}

#else

/*
  ==============================================================================
  ==============================================================================
  AXM2500 Interface
  ==============================================================================
  ==============================================================================
*/

/*
  ------------------------------------------------------------------------------
  pciesrio_setcontrol_axm25xx

  Valid values for "new_control" are as follows.

  Control     Description

  0x00000001  PEI0 EP x4[L3:0]
  0x00080003  PEI0 EP x2[L3:2], PEI1 RC x2[L1:0]
  0x00400001  PEI0 RC x4[L3:0]
  0x00480003  PEI0 RC x2[L3:2], PEI1 RC x2[L1:0]

  0x00040008  sRIO x4[L3:0] [SRIO host with ID 0]
  0x00140008  sRIO x4[L3:0] [SRIO host with ID 1]
  0x00240008  sRIO x4[L3:0] [SRIO not a host]
  0x00340008  sRIO x4[L3:0] [RESERVED]

  0x000c000b  PEI0 EP x1[L3], PEI1 RC x1[L2], sRIO x1[L0] [SRIO host with ID 0]
  0x001c000b  PEI0 EP x1[L3], PEI1 RC x1[L2], sRIO x1[L0] [SRIO host with ID 1]
  0x002c000b  PEI0 EP x1[L3], PEI1 RC x1[L2], sRIO x1[L0] [SRIO not a host]
  0x003c000b  PEI0 EP x1[L3], PEI1 RC x1[L2], sRIO x1[L0] [RESERVED]
  0x004c000b  PEI0 RC x1[L3], PEI1 RC x1[L2], sRIO x1[L0] [SRIO host with ID 0]
  0x005c000b  PEI0 RC x1[L3], PEI1 RC x1[L2], sRIO x1[L0] [SRIO host with ID 1]
  0x006c000b  PEI0 RC x1[L3], PEI1 RC x1[L2], sRIO x1[L0] [SRIO not a host]
  0x007c000b  PEI0 RC x1[L3], PEI1 RC x1[L2], sRIO x1[L0] [RESERVED]
*/

int
pciesrio_setcontrol_axm25xx(unsigned long new_control)
{
	int srioHSSSpeed;

	printf("Setting PCI/SRIO to 0x%08x\n", new_control);

	if (0x8 == (new_control & 0x8)) {
		srioHSSSpeed = dcr_read(0xd0f);
		srioHSSSpeed &= 0x3;
	}

	/*
	  RX Serdes Configuration for All Control Values
	*/

	ncr_write32(NCP_REGION_ID(0x115, 0), 0x26c, 0x00080000);
	ncr_write16(NCP_REGION_ID(0x115, 1), 0x026, 0x000000fe);
	ncr_write16(NCP_REGION_ID(0x115, 1), 0x226, 0x000000fe);
	ncr_write16(NCP_REGION_ID(0x115, 1), 0x626, 0x000000fe);
	ncr_write16(NCP_REGION_ID(0x115, 1), 0x826, 0x000000fe);
	ncr_write16(NCP_REGION_ID(0x115, 1), 0x02a, 0x00000e64);
	ncr_write16(NCP_REGION_ID(0x115, 1), 0x22a, 0x00000e64);
	ncr_write16(NCP_REGION_ID(0x115, 1), 0x62a, 0x00000e64);
	ncr_write16(NCP_REGION_ID(0x115, 1), 0x82a, 0x00000e64);
	udelay(100000);

	switch (new_control) {
		/* PCIe Only Modes */
	case 0x00000001:
	case 0x00080003:
	case 0x00400001:
	case 0x00480003:
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, new_control | 0x20);
		udelay(100000);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x208, 0xffffffff);
		udelay(100000);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x228, 0x00000100);
		udelay(100000);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, new_control);
		udelay(100000);
		break;

		/* sRIO Only Modes */
	case 0x00040008:
	case 0x00140008:
	case 0x00240008:
	case 0x00340008:
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, new_control | 0x40);
		udelay(100000);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x208, 0x77777777);
		udelay(100000);

		if (2 > srioHSSSpeed)
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x234, 0x06126527);
		else
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x234, 0x08176527);

		udelay(100000);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x228, 0x00000001);
		udelay(100000);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, new_control);
		udelay(100000);
		break;

		/* Mixed Modes */
	case 0x000c000b:
	case 0x001c000b:
	case 0x002c000b:
	case 0x003c000b:
	case 0x004c000b:
	case 0x005c000b:
	case 0x006c000b:
	case 0x007c000b:
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, new_control | 0x60);
		udelay(100000);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x208, 0x7fff7fff);
		udelay(100000);

		if (2 > srioHSSSpeed)
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x234, 0x06126527);
		else
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x234, 0x08176527);

		udelay(100000);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x228, 0x00000000);
		udelay(100000);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, new_control);
		udelay(100000);
		break;
	default:
		return -1;
		break;
	}

	return 0;
}

#endif

/*
  ==============================================================================
  ==============================================================================
  Public Interface
  ==============================================================================
  ==============================================================================
*/

/*
  ------------------------------------------------------------------------------
  pciesrio_setcontrol
*/

int
pciesrio_setcontrol(unsigned long control)
{
#if defined(ACP_25xx)
	return pciesrio_setcontrol_axm25xx(control);
#else
	return pciesrio_setcontrol_acp34xx(control);
#endif
}

/*
  ------------------------------------------------------------------------------
  pciesrio_init

  If "parameters" is 0x80000000, use the reset configuration pins to determine
  the setting.  Otherwise, just use the given control value(s).
*/

int
pciesrio_init(unsigned long parameter)
{
	int boot_mode;
	int pci_srio_select;
	int pci_srio_mode;
	unsigned long control;

#if defined(ACP_25xx)
	control = dcr_read(0xd0f);
	boot_mode = (control & 0x100) >> 8;
	pci_srio_select = (control & 0x10) >> 4;
	pci_srio_mode = (control & 0xc) >> 2;
#else
	control = dcr_read(DCR_RESET_BASE);
	boot_mode = (control & 0x80000000) >> 31;
	pci_srio_select = (control & 0x4000) >> 14;
	pci_srio_mode = (control & 0x3000) >> 12;
#endif

	printf("pci_srio_select=0x%x pci_srio_mode=0x%x\n",
	       pci_srio_select, pci_srio_mode);

	if (0 != boot_mode) {
		/*
		  Hardware sets up PCIe/SRIO when in external boot mode.
		*/

		printf("PCIe/SRIO Setup Ignored in External Boot Mode\n");
		return 0;
	}

	if (0x80000000 != parameter) {
		pciesrio_setcontrol(parameter);
		return 0;
	}

#ifdef ACP_25xx

	/*
	  For the AXM2500, the three bits (pci_srio_select and
	  pci_srio_mode) will indicate the following control values.
	  For a description of the resulting configuration, see
	  pciesrio_setcontrol_axm25xx() above.

	  Select     Mode        Control

	     0b0     0b00     0x00240008
	     0b0     0b01     0x00040008
	     0b0     0b10     0x002c000b
	     0b0     0b11     0x004c000b
	     0b1     0b00     0x00000001
	     0b1     0b01     0x00400001
	     0b1     0b10     0x00080003
	     0b1     0b11     0x00480003
	*/

	switch ((pci_srio_select << 2) | (pci_srio_mode)) {
	case 0x0:
		control = 0x00240008;
		break;
	case 0x1:
		control = 0x00040008;
		break;
	case 0x2:
		control = 0x002c000b;
		break;
	case 0x3:
		control = 0x004c000b;
		break;
	case 0x4:
		control = 0x00000001;
		break;
	case 0x5:
		control = 0x00400001;
		break;
	case 0x6:
		control = 0x00080003;
		break;
	case 0x7:
		control = 0x00480003;
		break;
	default:
		return -1;
		break;
	}
#else
	switch (pci_srio_select) {
	case 0:
		/* SRIO */
		switch (pci_srio_mode) {
		case 0:
			control = 0x0108;
			break;
		case 1:
			control = 0x0508;
			break;
		case 2:
			control = 0x0908;
			break;
		case 3:
			control = 0x0d08;
			break;
		default:
			/* Not possible since pci_srio_mode is anded with 0x3. */
			break;
		}
		break;
	case 1:
		/* PCI */
		switch (pci_srio_mode) {
		case 0:
			control = 0x0001;
			break;
		case 1:
			control = 0x1001;
			break;
		case 2:
			control = 0x0201;
			break;
		case 3:
			control = 0x0301;
			break;
		default:
			/* Not possible since pci_srio_mode is anded with 0x3. */
			break;
		}
		break;
	default:
		/* Not possible since pci_srio_select is anded with one bit. */
		break;
	}
#endif

	return pciesrio_setcontrol(control);
}
