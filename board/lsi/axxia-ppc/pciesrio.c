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

#if (!defined(ACP_25xx) && !defined(AXM_35xx))

/*
  ==============================================================================
  ==============================================================================
  Pre-AXM2500 Interface
  ==============================================================================
  ==============================================================================
*/

/*
  ------------------------------------------------------------------------------
  pcie_lsdq_workaround

  ACP PCIe detect cycle does not have enough time to run, meaning that
  in some rare cases, the link may fail to be detected. This issue
  might be observed when configured as two x2 PCIe configurations or
  three x1 PCIe configurations.  (Advisory 37842).

  Workaround: For applications where the ACP is in RC mode:
      - Perform a soft reset by setting bit of the PEI Configuration register
      - Set bit 4 (LSDQ) in the LTSSM Configuration 1 Register to have LTSSM
        stay in detect quiet.
      - Clear bit 4 of LTSSM Configuration 1 Register to transition out of
        detect quiet
  
  For applications where the ACP is in EP mode, additional resistors
  to ground should be placed on the TX+ and TX- lanes. This allows the
  detect cycle to run correctly.
*/

void
pcie_lsdq_workaround(int pei)
{
	unsigned long addr;
	unsigned long ltssmConfig = 0;
	unsigned long peiConfig;

	switch (pei) {
	case 0:
		addr = PCIE0_CONFIG;
		break;
	case 1:
		addr = PCIE1_CONFIG;
		break;
	case 2:
		addr = PCIE2_CONFIG;
		break;
	default:
		break;
	}

	/* soft reset the PEI */
	peiConfig = acpreadio((void *)(addr + 0x1000));
	peiConfig = peiConfig | 0x1;
	acpwriteio(peiConfig, (void *)(addr + 0x1000));

	/* Set bit 4 to 0x1 */
	ltssmConfig = acpreadio((void *)(addr + 0x3300));
	ltssmConfig = ltssmConfig | (0x1 << 4);
	acpwriteio(ltssmConfig, (void *)(addr + 0x3300));

	/* delay for 10ms */
	mdelay(10);

	/* clear bit 4 */
	ltssmConfig = acpreadio((void *)(addr + 0x3300));
	ltssmConfig = (ltssmConfig & 0xffffffef);
	acpwriteio(ltssmConfig, (void *)(addr + 0x3300));

	return;
}

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
	unsigned long linkStatus;

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

	/* Check for Link Detection Problems (Advisory 37842). */
	mdelay(500);

	if ((new_control & 0x1) && (new_control & 0x1000)) {
		/* PEI0 is enabled  and in RC mode */
		/* check Link status */
		linkStatus = acpreadio(PCIE0_CONFIG+0x1004);
		printf("PEI0 Status = 0x%x\n", linkStatus);
		linkStatus = (linkStatus & 0x3f00) >> 8;

		if (linkStatus != 0xb) {
			printf("pcie_lsdq_workaround for PEI0 "
			       "linkStatus = 0x%x\n", linkStatus);
			pcie_lsdq_workaround(0);
		}
	}
	if (new_control & 0x2) {
		/* PEI1 is enabled */
		/* check Link status */
		linkStatus = acpreadio(PCIE1_CONFIG+0x1004);
		printf("PEI1 Status = 0x%x\n", linkStatus);
		linkStatus = (linkStatus & 0x3f00) >> 8;

		if (linkStatus != 0xb) {
			printf("pcie_lsdq_workaround for PEI1 "
			       "linkStatus = 0x%x\n", linkStatus);
			pcie_lsdq_workaround(1);
		}
	}
	if (new_control & 0x4) {
		/* PEI2 is enabled */
		/* check Link status */
		linkStatus = acpreadio(PCIE2_CONFIG+0x1004);
		printf("PEI2 Status = 0x%x\n", linkStatus);
		linkStatus = (linkStatus & 0x3f00) >> 8;

		if (linkStatus != 0xb) {
			printf("pcie_lsdq_workaround for PEI2 "
			       "linkStatus = 0x%x\n", linkStatus);
			pcie_lsdq_workaround(2);
		}
	}

	return 0;
#endif
}

#elif defined(ACP_25xx)

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

typedef struct {
	unsigned short offset;
	unsigned short value;
} rx_serdes_value_t;

int
pciesrio_setcontrol_axm25xx(unsigned long new_control)
{
	int srioHSSSpeed;
	int i;
	char * env_value;
	unsigned short chResetVal;
	rx_serdes_value_t rx_serdes_values[] = {
		{0x0026, 0x00ff},
		{0x0226, 0x00ff},
		{0x0626, 0x00ff},
		{0x0826, 0x00ff},
		{0x002a, 0x0b50},
		{0x022a, 0x0b50},
		{0x062a, 0x0b50},
		{0x082a, 0x0b50},
		{0x005e, 0x7d98},
		{0x025e, 0x7d98},
		{0x065e, 0x7d98},
		{0x085e, 0x7d98},
		{0x008c, 0x2040},
		{0x028c, 0x2040},
		{0x068c, 0x2040},
		{0x088c, 0x2040},
		{0x008c, 0x2000},
		{0x028c, 0x2000},
		{0x068c, 0x2000},
		{0x088c, 0x2000},
		{0x00ba, 0x0061},
		{0x02ba, 0x0061},
		{0x06ba, 0x0061},
		{0x08ba, 0x0061},
		{0x0052, 0x2a43},
		{0x0252, 0x2a43}, 
		{0x0652, 0x2a43},
		{0x0852, 0x2a43},
		{0x0084, 0x001b},
		{0x0284, 0x001b},
		{0x0684, 0x001b},
		{0x0884, 0x001b},
		{0x008a, 0x1bd0},
		{0x028a, 0x1bd0},
		{0x068a, 0x1bd0},
		{0x088a, 0x1bd0},
		{0x0078, 0x1006},
		{0x0278, 0x1006},
		{0x0678, 0x1006},
		{0x0878, 0x1006},
		{0x0080, 0x4204},
		{0x0280, 0x4204},
		{0x0680, 0x4204},
		{0x0880, 0x4204},
		{0x0066, 0x3623},
		{0x0266, 0x3623},
		{0x0666, 0x3623},
		{0x0866, 0x3623},
		{0x007a, 0x5204},
		{0x027a, 0x5204},
		{0x067a, 0x5204},
		{0x087a, 0x5204},
		{0x007e, 0x4202},
		{0x027e, 0x4202},
		{0x067e, 0x4202},
		{0x087e, 0x4202},
		{0x00a4, 0x3001},
		{0x02a4, 0x3001},
		{0x06a4, 0x3001},
		{0x08a4, 0x3001},
		{0x009a, 0x5320},
		{0x029a, 0x5320},
		{0x069a, 0x5320},
		{0x089a, 0x5320}
	};

	printf("Setting PCI/SRIO to 0x%08lx\n", new_control);

	/*
	  RX Serdes Configuration for All Control Values
	*/

	ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, 0x00000080);
	udelay(100000);
	ncr_write32(NCP_REGION_ID(0x115, 0), 0x208, 0xffffffff);

	ncr_write32(NCP_REGION_ID(0x115, 0), 0x26c, 0x000c0000);

	/* Assert the channel resets during the optimum setting sequence
	 * clear bits 15,14,1,0 
	 */

		switch (new_control) {
		/* PCIe Only Modes */
	case 0x00000001:
	case 0x00400001:
	case 0x00080003:
	case 0x00480003:
		ncr_read16(NCP_REGION_ID(0x115,1), 0x0, &chResetVal);
		ncr_write16(NCP_REGION_ID(0x115,1), 0x0, (chResetVal & 0x3ffc));
		ncr_read16(NCP_REGION_ID(0x115,1), 0x200, &chResetVal);
		ncr_write16(NCP_REGION_ID(0x115,1), 0x200, (chResetVal & 0x3ffc));
		ncr_read16(NCP_REGION_ID(0x115,1), 0x600, &chResetVal);
		ncr_write16(NCP_REGION_ID(0x115,1), 0x600, (chResetVal & 0x3ffc));
		ncr_read16(NCP_REGION_ID(0x115,1), 0x800, &chResetVal);
		ncr_write16(NCP_REGION_ID(0x115,1), 0x800, (chResetVal & 0x3ffc));
		break;
		/* sRIO Only Modes */
	case 0x00040008:
	case 0x00140008:
	case 0x00240008:
	case 0x00340008:
		srioHSSSpeed = dcr_read(0xd0f);
		srioHSSSpeed &= 0x3;
		if (srioHSSSpeed == 0) {
			ncr_write16(NCP_REGION_ID(0x115,1), 0x0, 0x390c);
			ncr_write16(NCP_REGION_ID(0x115,1), 0x200, 0x390c);
			ncr_write16(NCP_REGION_ID(0x115,1), 0x600, 0x390c);
			ncr_write16(NCP_REGION_ID(0x115,1), 0x800, 0x390c);
		} else if (srioHSSSpeed == 1) {
			ncr_write16(NCP_REGION_ID(0x115,1), 0x0, 0x3b0c);
			ncr_write16(NCP_REGION_ID(0x115,1), 0x200, 0x3b0c);
			ncr_write16(NCP_REGION_ID(0x115,1), 0x600, 0x3b0c);
			ncr_write16(NCP_REGION_ID(0x115,1), 0x800, 0x3b0c);
		} else {
			ncr_write16(NCP_REGION_ID(0x115,1), 0x0, 0x3a0c);
			ncr_write16(NCP_REGION_ID(0x115,1), 0x200, 0x3a0c);
			ncr_write16(NCP_REGION_ID(0x115,1), 0x600, 0x3a0c);
			ncr_write16(NCP_REGION_ID(0x115,1), 0x800, 0x3a0c);
		}
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
		srioHSSSpeed = dcr_read(0xd0f);
		srioHSSSpeed &= 0x3;
		if (srioHSSSpeed == 0) {
			ncr_write16(NCP_REGION_ID(0x115,1), 0x0, 0x390c);
			ncr_write16(NCP_REGION_ID(0x115,1), 0x200, 0x3b0c);
			ncr_write16(NCP_REGION_ID(0x115,1), 0x600, 0x3b0c);
			ncr_write16(NCP_REGION_ID(0x115,1), 0x800, 0x3b0c);
		} else if (srioHSSSpeed == 1) {
			ncr_write16(NCP_REGION_ID(0x115,1), 0x0, 0x3b0c);
			ncr_write16(NCP_REGION_ID(0x115,1), 0x200, 0x3b0c);
			ncr_write16(NCP_REGION_ID(0x115,1), 0x600, 0x3b0c);
			ncr_write16(NCP_REGION_ID(0x115,1), 0x800, 0x3b0c);
		} else {
			ncr_write16(NCP_REGION_ID(0x115,1), 0x0, 0x3a0c);
			ncr_write16(NCP_REGION_ID(0x115,1), 0x200, 0x3b0c);
			ncr_write16(NCP_REGION_ID(0x115,1), 0x600, 0x3b0c);
			ncr_write16(NCP_REGION_ID(0x115,1), 0x800, 0x3b0c);
		}
		break;
	default:
		return -1;
		break;
	}


	for (i = 0;
	     i < sizeof(rx_serdes_values) / sizeof(rx_serdes_value_t);
	     ++i) {
		ncr_write16(NCP_REGION_ID(0x115, 1),
			    rx_serdes_values[i].offset,
			    rx_serdes_values[i].value);
	}

	/*
	set 26 R/W dsbl_g12_rx_p1_pd Disable the Gen1/Gen2 configuration RX_P1_PD signal. 0x0
	for pipe0 and pipe 1
	*/
	ncr_write32(NCP_REGION_ID(0x115, 2), 0x02c, 0x05008249);
	ncr_write32(NCP_REGION_ID(0x115, 3), 0x02c, 0x05008249);

	udelay(100000);

	switch (new_control) {
		/* PCIe Only Modes */
	case 0x00000001:
	case 0x00400001:
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x42e, 0x0042);
		ncr_write16(NCP_REGION_ID(0x115, 1), 0xc2e, 0x0042);
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x402, 0x1a0c);
		ncr_write16(NCP_REGION_ID(0x115, 1), 0xc02, 0x1a0c);
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x08e, 0x0487);
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x28e, 0x0487);
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x68e, 0x0487);
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x88e, 0x0487);
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x01e, 0xc000);
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x21e, 0xc000);
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x61e, 0xc000);
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x81e, 0xc000);

		/* De-Assert the channel resets during the optimum setting sequence
		 * set bits 15,14,1,0
		 */

		ncr_read16(NCP_REGION_ID(0x115,1), 0x0, &chResetVal);
		ncr_write16(NCP_REGION_ID(0x115,1), 0x0, (chResetVal | 0xc003));
		ncr_read16(NCP_REGION_ID(0x115,1), 0x200, &chResetVal);
		ncr_write16(NCP_REGION_ID(0x115,1), 0x200, (chResetVal | 0xc003));
		ncr_read16(NCP_REGION_ID(0x115,1), 0x600, &chResetVal);
		ncr_write16(NCP_REGION_ID(0x115,1), 0x600, (chResetVal | 0xc003));
		ncr_read16(NCP_REGION_ID(0x115,1), 0x800, &chResetVal);
		ncr_write16(NCP_REGION_ID(0x115,1), 0x800, (chResetVal | 0xc003));

		ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, new_control | 0x20);
		udelay(100000);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x208, 0xffffffff);
		udelay(100000);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x228, 0x00000000);
		udelay(100000);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, new_control);
		udelay(100000);
		break;
	case 0x00080003:
	case 0x00480003:
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x42e, 0x0042);
		ncr_write16(NCP_REGION_ID(0x115, 1), 0xc2e, 0x0042);
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x402, 0x1a0c);
		ncr_write16(NCP_REGION_ID(0x115, 1), 0xc02, 0x1a0c);
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x08e, 0x0487);
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x28e, 0x0487);
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x68e, 0x0487);
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x88e, 0x0487);
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x01e, 0xc000);
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x21e, 0xc000);
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x61e, 0xc000);
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x81e, 0xc000);

		/* De-Assert the channel resets during the optimum setting sequence
	 	 * set bits 15,14,1,0 
	 	 */
		ncr_read16(NCP_REGION_ID(0x115,1), 0x0, &chResetVal);
		ncr_write16(NCP_REGION_ID(0x115,1), 0x0, (chResetVal | 0xc003));
		ncr_read16(NCP_REGION_ID(0x115,1), 0x200, &chResetVal);
		ncr_write16(NCP_REGION_ID(0x115,1), 0x200, (chResetVal | 0xc003));
		ncr_read16(NCP_REGION_ID(0x115,1), 0x600, &chResetVal);
		ncr_write16(NCP_REGION_ID(0x115,1), 0x600, (chResetVal | 0xc003));
		ncr_read16(NCP_REGION_ID(0x115,1), 0x800, &chResetVal);
		ncr_write16(NCP_REGION_ID(0x115,1), 0x800, (chResetVal | 0xc003));


		ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, new_control | 0x20);
		udelay(100000);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x208, 0x77ff77ff);
		udelay(100000);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x228, 0x00000000);
		udelay(100000);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, new_control);
		udelay(100000);
		break;

		/* sRIO Only Modes */
	case 0x00040008:
	case 0x00140008:
	case 0x00240008:
	case 0x00340008:
		srioHSSSpeed = dcr_read(0xd0f);
		srioHSSSpeed &= 0x3;

		/* enable control override */
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x042e, 0x0052);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x208, 0xffffffff);

		if (srioHSSSpeed == 0) {
			/* 1.25 Gbps rate */
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0408, 0x0612);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0404, 0x4028);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x040c, 0x3029);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0402, 0x070c);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0430, 0x9412);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0434, 0x0007);

			/* enable PLL */
			/* reorder PLL selection */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x244, 0x11111111);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0422, 0x0555);
		} else if (srioHSSSpeed == 1) {
			/* 2.5 Gbps rate */
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0408, 0x0612);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0404, 0x4028);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x040c, 0x3029);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0402, 0x070c);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0430, 0x9412);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0434, 0x0007);	

			/* enable PLL */
			/* reorder PLL selection */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x244, 0x33333333);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0422, 0x0555);
		} else {
			/* 3.125 Gbps rate */
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0408, 0x030a);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0404, 0x4038);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x040c, 0x3029);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0402, 0x070c);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0430, 0xd40a);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0434, 0x0007);	

			/* enable PLL */
			/* reorder PLL selection */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x244, 0x22222222);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0422, 0x0555);
		}
		/* De-Assert the channel resets during the optimum setting sequence
		 * set bits 15,14,1,0 
		 */

		/*
		ncr_read16(NCP_REGION_ID(0x115,1), 0x0, &chResetVal);
		ncr_write16(NCP_REGION_ID(0x115,1), 0x0, (chResetVal | 0xc003));
		ncr_read16(NCP_REGION_ID(0x115,1), 0x200, &chResetVal);
		ncr_write16(NCP_REGION_ID(0x115,1), 0x200, (chResetVal | 0xc003));
		ncr_read16(NCP_REGION_ID(0x115,1), 0x600, &chResetVal);
		ncr_write16(NCP_REGION_ID(0x115,1), 0x600, (chResetVal | 0xc003));
		ncr_read16(NCP_REGION_ID(0x115,1), 0x800, &chResetVal);
		ncr_write16(NCP_REGION_ID(0x115,1), 0x800, (chResetVal | 0xc003));
		*/

		ncr_write16(NCP_REGION_ID(0x115,1), 0x0, 0xf90f);
		ncr_write16(NCP_REGION_ID(0x115,1), 0x200, 0xf90f);
		ncr_write16(NCP_REGION_ID(0x115,1), 0x600, 0xf90f);
		ncr_write16(NCP_REGION_ID(0x115,1), 0x800, 0xf90f);

		ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, new_control | 0x60);
		udelay(100000);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x228, 0x00000100);
		udelay(100000);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, new_control | 0x40);
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
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x42e, 0x0042);
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x402, 0x1a0c);
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x28e, 0x0487);
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x68e, 0x0487);
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x88e, 0x0487);
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x21e, 0xc000);
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x61e, 0xc000);
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x81e, 0xc000);

		srioHSSSpeed = dcr_read(0xd0f);
		srioHSSSpeed &= 0x3;

		/* enable control override */
		ncr_write16(NCP_REGION_ID(0x115, 1), 0x0c2e, 0x0052);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x208, 0xfff7fff7);

		if (srioHSSSpeed == 0) {
			/* 1.25 Gbps rate */
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0c08, 0x0612);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0c04, 0x4028);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0c0c, 0x3029);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0c02, 0x070c);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0c30, 0x9412);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0c34, 0x0007);

			/* enable PLL */
			/* reorder PLL selection */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x244, 0x11111111);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0c22, 0x0555);
		} else if (srioHSSSpeed == 1) {
			/* 2.5 Gbps rate */
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0c08, 0x0612);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0c04, 0x4028);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0c0c, 0x3029);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0c02, 0x070c);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0c30, 0x9412);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0c34, 0x0007);

			/* enable PLL */
			/* reorder PLL selection */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x244, 0x11131113);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0c22, 0x0555);
		} else {
			/* 3.125 Gbps rate */
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0c08, 0x030a);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0c04, 0x4038);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0c0c, 0x3029);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0c02, 0x070c);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0c30, 0xd40a);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0c34, 0x0007);

			/* enable PLL */
			/* reorder PLL selection */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x244, 0x11121112);
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x0c22, 0x0555);
		}

        /* De-Assert the channel resets during the optimum setting sequence
         * set bits 15,14,1,0
         */
        ncr_read16(NCP_REGION_ID(0x115,1), 0x0, &chResetVal);
        ncr_write16(NCP_REGION_ID(0x115,1), 0x0, (chResetVal | 0xc003));
        ncr_read16(NCP_REGION_ID(0x115,1), 0x200, &chResetVal);
        ncr_write16(NCP_REGION_ID(0x115,1), 0x200, (chResetVal | 0xc003));
        ncr_read16(NCP_REGION_ID(0x115,1), 0x600, &chResetVal);
        ncr_write16(NCP_REGION_ID(0x115,1), 0x600, (chResetVal | 0xc003));
        ncr_read16(NCP_REGION_ID(0x115,1), 0x800, &chResetVal);
        ncr_write16(NCP_REGION_ID(0x115,1), 0x800, (chResetVal | 0xc003));



		ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, new_control | 0x60);
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

#elif defined(AXM_35xx)

int
pciesrio_setcontrol_axm35xx(unsigned long new_control)
{
	int srio0_speed = 0, divMode0 = 0;
	int i = 0;
	char *env_value;
	unsigned short chResetVal;

	printf("Setting PCI/SRIO to 0x%08lx\n", new_control);

	/* Change the default of los_freeze_bypass to '0' */
	ncr_write32(NCP_REGION_ID(0x115, 0), 0x26c, 0x007c0001);


	if ((new_control & 0x8) == 0x8) {
		/* SRIO0 enabled */
		srio0_speed = (((new_control >> 4) & 0x7) << 12);
		switch ((new_control >> 4) & 0x7) {
		case 0:
			printf("SRIO0 -- 1.25 Gbps\n");
			/* 1.25 Gbps */
			divMode0 = 0x11111111;
			break;
		case 1:
			printf("SRIO0 -- 2.5 Gbps\n");
			/* 2.5 Gbps */
			if (((new_control >> 26) & 0x6) == 0x6) {
				/* SRIO0x1 mode */
				divMode0 = 0x11131113;
			} else {
				/* SRIO0x4 mode */
				divMode0 = 0x33333333;
			}
			break;
		case 2:
			printf("SRIO0 -- 3.125 Gbps\n");
			/* 3.125 Gbps */
			if (((new_control >> 26) & 0x6) == 0x6) {
				/* SRIO0x1 mode */
				divMode0 = 0x11121112;
			} else {
				/* SRIO0x4 mode */
				divMode0 = 0x22222222;
			}
			if (((new_control >> 26) & 0x6) == 0x6) {
				/* SRIO0 x1 mode */
				ncr_write32(NCP_REGION_ID(0x115, 0), 0x234,
				0x030A7507);
			} else {
				/* SRIO0x4 mode */
				ncr_write32(NCP_REGION_ID(0x115, 0), 0x230,
				0x030A7527);
			}
			break;
		default:
			printf("Invalid SRIO0 speed\n");
			return 1;
		}
	}

	if ((new_control == 0x400001) ||
		(new_control == 0x00000001)) {
		/*  PEI0 RC 0x4 mode or PEI0 EP mode */
		/* soft reset the phy, pipe, link layer */
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, 0x80);

		udelay(100000);
		/* PLL B disable */
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x228, 0x100);

		/* High Serdes reset_a */
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, 0x21);

		ncr_write32(NCP_REGION_ID(0x115, 0), 0x208, 0xffffffff);

		/* wr pll_a_ctrl  0x230 0x03176403 */
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x230, 0x03176403);

		/* enable PEI0 */
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, new_control);
	} else if (((new_control & 0x1c00000f) == 0x10000005)
		|| ((new_control & 0x1c00000f) == 0x10000001)
		|| ((new_control & 0x1c00000f) == 0x10000004)) {
		/* PEI0x2, PEI1x2 */
		/* wr ctrl10       0x228 0x00000000 */
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x228, 0x0);

		if ((new_control & 0x1c00000f) == 0x10000001) {
			/* only PEI0 is enabled */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, 0x10000061);
		} else if ((new_control & 0x1c00000f) == 0x10000004) {
			/* only PEI1 is enabled */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, 0x10000062);
		} else {
			/* both PEI0/PEI1 are enabled */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, 0x10000063);
		}

		/* wr ctrl2         0x208 0x77ff77ff */
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x208, 0x77ff77ff);

		/* wr_pll_a_ctrl 0x230 0x03176403 */
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x230, 0x03176403);

		/* wr_pll_b_ctrl 0x234 0x03176423 */
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x234, 0x03176423);

		switch (new_control & 0x1c00000f) {
		case 0x10000001:
			/* only PEI0 is enabled */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x200,
				(new_control & 0x1c40000f));
			break;
		case 0x10000004:
			/* only PEI1 is enabled */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x200,
				((new_control & 0x1c400000) | 0x2));
			break;
		default:
			/* both PEI0/PEI1 are enabled */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x200,
				((new_control & 0x1c400000) | 0x3));
			break;
		}

	} else if (((new_control & 0x1c00000f) == 0x18000007)
		|| ((new_control & 0x1c00000f) == 0x18000008)
		|| ((new_control & 0x1c00000f) == 0x18000006)
		|| ((new_control & 0x1c00000f) == 0x18000005)
		|| ((new_control & 0x1c00000f) == 0x18000004)
		|| ((new_control & 0x1c00000f) == 0x18000003)
		|| ((new_control & 0x1c00000f) == 0x18000002)
		|| ((new_control & 0x1c00000f) == 0x18000001)
		|| ((new_control & 0x1c00000f) == 0x1800000f)) {
		/* SRIO0x1, PEI0x1, PEI1x1, PEI2x1 */
		if (new_control & 0x8) {
			/* Power up PLLA/PLLB */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x228, 0x0);
		} else {
			/* Keep PLLB powered down if SRIOx1 not enabled*/
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x228, 0x100);
		}

		/* wr ctrl0         0x200 0x18000067 */
		if ((new_control & 0x1c00000f) == 0x18000001) {
			/* only PEI0 is enabled */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, 0x18000061);
		} else if ((new_control & 0x1c00000f) == 0x18000003) {
			/* PEI2 and PEI0 is enabled */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, 0x18000065);
		} else if ((new_control & 0x1c00000f) == 0x18000005) {
			/* PEI0 and PEI1 is enabled */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, 0x18000063);
		} else if ((new_control & 0x1c00000f) == 0x18000006) {
			/* PEI2 and PEI1 is enabled */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, 0x18000066);
		} else if ((new_control & 0x1c00000f) == 0x18000004) {
			/* only PEI1 is enabled */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, 0x18000062);
		} else if ((new_control & 0x1c00000f) == 0x18000002) {
			/* only PEI2 is enabled */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, 0x18000064);
		} else if ((new_control & 0x1c00000f) == 0x18000007) {
			/* All 3 PEIs are enabled */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, 0x18000067);
		} else if (((new_control & 0x1c00000f) == 0x1800000f)
			|| ((new_control & 0x1c00000f) == 0x18000008)) {
			/* All 3 PEIs and SRIO0 are enabled -- SRIO0x1
			 or SRIO0x1 mode */
			if ((new_control & 0xf) == 0x8) {
				/* SRIO0 x1 only mode */
				ncr_write32(NCP_REGION_ID(0x115, 0), 0x200,
					0x18000068);
			} else {
				ncr_write32(NCP_REGION_ID(0x115, 0), 0x200,
					0x1800006f);
			}
			/* configure PLLB since SRIOx1 is enabled */
			if (((new_control >> 4) & 0x7) != 0x2) {
				/* SRIO speed is not 3.125 Gbps */
				ncr_write32(NCP_REGION_ID(0x115, 0), 0x234,
					0x06126507);
			}
			/* Program SRIO0 speed */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x204,
				srio0_speed);
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x244, divMode0);
		}

		/* wr ctrl11       0x22c 0x000000EF */
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x22c, 0xef);

		/* wr ctrl2         0x208 0xFFF7FFF7 */
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x208, 0xFFF7FFF7);

		ncr_write32(NCP_REGION_ID(0x115, 0), 0x230, 0x03176403);

		switch (new_control & 0x1c00000f) {
		case 0x18000001:
		case 0x18000007:
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x200,
				(new_control & 0x1c40000f) | 0x40);
			break;
		case 0x18000003:
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x200,
				(new_control & 0x1c400000) | 0x45);
			break;
		case 0x18000005:
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x200,
				(new_control & 0x1c400000) | 0x43);
			break;
		case 0x18000006:
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x200,
				(new_control & 0x1c400000) | 0x46);
			break;
		case 0x18000002:
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x200,
				(new_control & 0x1c400000) | 0x44);
			break;
		case 0x18000004:
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x200,
				(new_control & 0x1c400000) | 0x42);
			break;
		case 0x1800000f:
		case 0x18000008:
			/* All 3 PEIs and SRIO0 are enabled or only
			 * SRIO0 is enabled */
			/* host or agent mode provided by user */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x200,
				new_control & 0x1c70000f);
			break;
		}

	} else if ((new_control & 0x1c00000f) == 0x08000008) {
		/* SRIO0 x4 mode  */
		/* PLL B disable */
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x228, 0x100);

		/* wr ctrl0         0x200 0x08000028 */
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, 0x08000028);

		/* wr ctrl2         0x208 0xFFFFFFFF */
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x208, 0xFFFFFFFF);

		/* Program SRIO0 speed */
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x204, srio0_speed);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x244, divMode0);

		if (((new_control >> 4) & 0x7) != 0x2) {
			/* SRIO speed is not 3.125 Gbps */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x230, 0x06126527);
		}

		/* Only SRIO0 is enabled, host or agent mode provided
			   by user */
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x200,
				new_control & 0x1c30000f);

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
#elif defined(AXM_35xx)
	return pciesrio_setcontrol_axm35xx(control);
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

#if 0
	printf("%s:%d - 0x%08x\n", __FILE__, __LINE__,
	       (pci_srio_select << 2) | (pci_srio_mode));
#endif

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
		/*
		  Not possible since pci_srio_mode is anded with 0x3 and
		  pci_srio_select is anded with 0x1.
		*/
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
		/* Not possible since pci_srio_select is anded with 0x1. */
		break;
	}
#endif

	return pciesrio_setcontrol(control);
}
