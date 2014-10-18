/*
 * (C) Copyright 2010, Chris Zhang <chris@seamicro.com>
 *
 * Author: Chris Zhang <chris@seamicro.com>
 * This code is based on ehci freescale driver
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */
#include <common.h>
#include <usb.h>
#include <asm/io.h>

#include "ehci.h"

/*
 * Create the appropriate control structures to manage
 * a new EHCI host controller.
 */
int ehci_hcd_init(int index, enum usb_init_type init,
		  struct ehci_hccr **hccr, struct ehci_hcor **hcor)
{
#ifndef CONFIG_AXXIA_ARM
	int ret;
	int USB_TXFIFOTHRES, VUSB_HS_TX_BURST;
	int hwtxbuf, txfulltuning, deviceMode;
#endif

	/* Setup GPREG for USB to enable the 6-bit address line */
        writel(0x0, GPREG_USB);

	*hccr = (struct ehci_hccr *)(CONFIG_USB_ADDR+0x100);
        *hcor = (struct ehci_hcor *)((uint32_t) *hccr +
				     HC_LENGTH(ehci_readl(&(*hccr)->cr_capbase)));
#if defined(CONFIG_AXXIA_ARM) && defined(RUN_UNCACHED)
	/* Setup hprot for non-cacheable/non-bufferable for USB DMA */
	writel(0x0, GPREG+0x74);
#endif

#ifndef CONFIG_AXXIA_ARM
	hwtxbuf = ehci_readl(CONFIG_USB_ADDR+0x10);
	txfulltuning = ehci_readl(CONFIG_USB_ADDR+0x164);

	/* fix Bugzilla #31874     */
	/* fix Bugzilla #32212     */
	VUSB_HS_TX_BURST =    ehci_readl(CONFIG_USB_ADDR+0x10) & 0x0f;
	USB_TXFIFOTHRES = (32 << 16);
	txfulltuning = (txfulltuning  & 0xffc0ffff) | USB_TXFIFOTHRES;

	writel( txfulltuning, CONFIG_USB_ADDR+0x164);

      	deviceMode = ehci_readl(CONFIG_USB_ADDR+0x1A8);

        if ((deviceMode & 0x3) == 0x2) {
                /* device mode */
                writel(0x0, CONFIG_USB_ADDR + 0x90);
        } else if ((deviceMode & 0x3) == 0x3) {
                /* host mode */
                writel(0x6, CONFIG_USB_ADDR + 0x90);
        }
#endif

	return 0;
}

/*
 * Destroy the appropriate control structures corresponding
 * the the EHCI host controller.
 */
int ehci_hcd_stop(int index)
{
	int cmd, status;
	int count = 10;

	cmd = ehci_readl(CONFIG_USB_ADDR+0x140);
	cmd &= ~CMD_RUN;
	ehci_writel(CONFIG_USB_ADDR+0x140, cmd);

	do {
		udelay(100);
		status = ehci_readl(CONFIG_USB_ADDR+0x144);
		count--;
	} while ((count > 0) && ((status & STS_HALT)!=STS_HALT));

	if ((status & STS_HALT) == STS_HALT) {
		printf("USB HostController successfully stopped\n");
	} else {
		printf("USB HostController couldn't be stopped\n");
	}

	return 0;
}
