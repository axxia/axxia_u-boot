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

#include "ehci.h"
#include "ehci-core.h"

/*
 * Create the appropriate control structures to manage
 * a new EHCI host controller.
 */
int ehci_hcd_init(void)
{
	u32 vct_hccr;
	u32 vct_hcor;
	int ret;
	unsigned long core;
       int USB_TXFIFOTHRES, VUSB_HS_TX_BURST;
	int hwtxbuf, txfulltuning;

	/* USB workaround */
	/* Set plb6_hpc count to 0x400 */
	dcr_write(0x400, 0x10d);

      /* Setup GPREG for USB to enable the 6-bit address line */
        writel(0x0, GPREG_USB);

	hccr = (struct ehci_hccr *)(CONFIG_SYS_PPC4XX_USB_ADDR+0x100);
        hcor = (struct ehci_hcor *)((uint32_t) hccr +
                HC_LENGTH(ehci_readl(&hccr->cr_capbase)));

#ifndef AXM_35xx

	hwtxbuf = ehci_readl(CONFIG_SYS_PPC4XX_USB_ADDR+0x10);
	txfulltuning = ehci_readl(CONFIG_SYS_PPC4XX_USB_ADDR+0x164);

	/* fix Bugzilla #31874     */
	/* fix Bugzilla #32212     */
	VUSB_HS_TX_BURST =    ehci_readl(CONFIG_SYS_PPC4XX_USB_ADDR+0x10) & 0x0f;
	USB_TXFIFOTHRES = (32 << 16);
	txfulltuning = (txfulltuning  & 0xffc0ffff) | USB_TXFIFOTHRES;

	writel( txfulltuning, CONFIG_SYS_PPC4XX_USB_ADDR+0x164);

#endif
	return 0;
}

/*
 * Destroy the appropriate control structures corresponding
 * the the EHCI host controller.
 */
int ehci_hcd_stop(void)
{
	return 0;
}
