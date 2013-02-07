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
pciesrio_set_control(unsigned long new_control)
{
#if !defined(ACP_EMU) && !defined(ACP_ISS) && !defined(ACP_X1V1)
	unsigned long old_control;

	if (0 != (new_control & ~0x00003f8f)) {
		printf("Invalid PHY control value: 0x%08lx\n", new_control);
		return -1;
	}

	old_control = acpreadio((void *)GPREG_PHY_CTRL0);
	printf("Switching PHY0 Control from 0x%08lx to 0x%08lx\n",
	       old_control, new_control);

	if ((0 != old_control) && (new_control != old_control)) {
		printf("WARNING: Switchting from one non-zero control setting "
		       "to another is NOT supported.\n");
		/* This is Old Code, not correct! */
		acpwriteio((new_control & 0x00001f00), (void *)GPREG_PHY_CTRL0);
		udelay(1);
		acpwriteio((0x80000000 | (new_control & 0x00001f00)),
			   (void *)GPREG_PHY_CTRL0);
		udelay(1);
		acpwriteio((new_control & 0x00001f00), (void *)GPREG_PHY_CTRL0);
		udelay(1);
		acpwriteio((new_control & 0x00001f0f), (void *)GPREG_PHY_CTRL0);
		udelay(1);
	} else {
		unsigned long value;

		/* phy_ctl0 contains 0. (step 1.) */

		/* Write bits 12:8. (step 2.) */
		acpwriteio((new_control & 0x1f00),
			   (void *)GPREG_PHY_CTRL0);
		DEBUG_PRINT("Step 2: PHY_CTRL0=0x%x\n",
			    acpreadio((void *)GPREG_PHY_CTRL0));

		/* Write bit 31. (step 3.) */
		acpwriteio(((new_control & 0x1f00) | 0x80000000),
			   (void *)GPREG_PHY_CTRL0);
		DEBUG_PRINT("Step 3: PHY_CTRL0=0x%x\n",
			    acpreadio((void *)GPREG_PHY_CTRL0));

		/* Clear bit 31. (step 4.) */
		acpwriteio((new_control & 0x1f00),
			   (void *)GPREG_PHY_CTRL0);
		udelay(1000);
		DEBUG_PRINT("Step 4: PHY_CTRL0=0x%x\n",
			    acpreadio((void *)GPREG_PHY_CTRL0));

		/* Enable MACs that are specified in the parameter. (step 5.) */
		acpwriteio((new_control & 0x1f0f),
			   (void *)GPREG_PHY_CTRL0);
		DEBUG_PRINT("Step 5: PHY_CTRL0=0x%x\n",
			    acpreadio((void *)GPREG_PHY_CTRL0));
	}

	return 0;
#endif
}
