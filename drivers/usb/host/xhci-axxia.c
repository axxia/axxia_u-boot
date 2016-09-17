
/*
 * This file is a conglomeration for DWC3-init sequence and further
 * axxia specific PHY-init sequence.
 */

#include <common.h>
#include <fdtdec.h>
#include <libfdt.h>
#include <malloc.h>
#include <usb.h>
#include <watchdog.h>
#include <asm/arch/cpu.h>
#include <asm/gpio.h>
#include <asm-generic/errno.h>
#include <linux/compat.h>
#include <linux/usb/dwc3.h>

#include "xhci.h"

/* Declare global data pointer */
DECLARE_GLOBAL_DATA_PTR;

/**
 * Contains pointers to register base addresses
 * for the usb controller.
 */
struct axxia_xhci {
	struct xhci_hccr *hcd;
	struct dwc3 *dwc3_reg;
};

static struct axxia_xhci axxia[CONFIG_USB_MAX_CONTROLLER_COUNT];

void dwc3_set_mode(struct dwc3 *dwc3_reg, u32 mode)
{
	clrsetbits_le32(&dwc3_reg->g_ctl,
			DWC3_GCTL_PRTCAPDIR(DWC3_GCTL_PRTCAP_OTG),
			DWC3_GCTL_PRTCAPDIR(mode));
}

static void dwc3_phy_reset(struct dwc3 *dwc3_reg)
{
	/* Assert USB3 PHY reset */
	setbits_le32(&dwc3_reg->g_usb3pipectl[0], DWC3_GUSB3PIPECTL_PHYSOFTRST);

	/* Assert USB2 PHY reset */
	setbits_le32(&dwc3_reg->g_usb2phycfg, DWC3_GUSB2PHYCFG_PHYSOFTRST);

	mdelay(100);

	/* Clear USB3 PHY reset */
#ifndef DISABLE_USB3
	clrbits_le32(&dwc3_reg->g_usb3pipectl[0],
		     DWC3_GUSB3PIPECTL_PHYSOFTRST);
#endif

	/* Clear USB2 PHY reset */
	clrbits_le32(&dwc3_reg->g_usb2phycfg, DWC3_GUSB2PHYCFG_PHYSOFTRST);

	mdelay(100);
}

static void dwc3_core_soft_reset(struct dwc3 *dwc3_reg)
{
	/* Before Resetting PHY, put Core in Reset */
	setbits_le32(&dwc3_reg->g_ctl, DWC3_GCTL_CORESOFTRESET);

	/* Reset the PHY */
	dwc3_phy_reset(dwc3_reg);

	/* After PHYs are stable we can take Core out of reset state */
	clrbits_le32(&dwc3_reg->g_ctl, DWC3_GCTL_CORESOFTRESET);
}

static int dwc3_core_init(struct dwc3 *dwc3_reg)
{
	u32 reg;
	u32 revision;
	unsigned int dwc3_hwparams1;

	revision = readl(&dwc3_reg->g_snpsid);
	/* This should read as U3 followed by revision number */
	if ((revision & DWC3_GSNPSID_MASK) != 0x55330000) {
		puts("this is not a DesignWare USB3 DRD Core\n");
		return -EINVAL;
	}

	dwc3_core_soft_reset(dwc3_reg);

	dwc3_hwparams1 = readl(&dwc3_reg->g_hwparams1);

	reg = readl(&dwc3_reg->g_ctl);
	reg &= ~DWC3_GCTL_SCALEDOWN_MASK;
	reg &= ~DWC3_GCTL_DISSCRAMBLE;
	switch (DWC3_GHWPARAMS1_EN_PWROPT(dwc3_hwparams1)) {
	case DWC3_GHWPARAMS1_EN_PWROPT_CLK:
		reg &= ~DWC3_GCTL_DSBLCLKGTNG;
		break;
	default:
		debug("No power optimization available\n");
	}

	/*
	 * WORKAROUND: DWC3 revisions <1.90a have a bug
	 * where the device can fail to connect at SuperSpeed
	 * and falls back to high-speed mode which causes
	 * the device to enter a Connect/Disconnect loop
	 */
	if ((revision & DWC3_REVISION_MASK) < 0x190a)
		reg |= DWC3_GCTL_U2RSTECN;

	writel(reg, &dwc3_reg->g_ctl);

	reg = readl(&dwc3_reg->g_usb3pipectl[0]);
	reg &= ~(1 << 18);
	writel(reg, &dwc3_reg->g_usb3pipectl[0]);

	return 0;
}

static int axxia_xhci_core_init(struct axxia_xhci *axxia)
{
	int ret;

	ret = dwc3_core_init(axxia->dwc3_reg);
	if (ret) {
		debug("failed to initialize core\n");
		return -EINVAL;
	}

	/* We are hard-coding DWC3 core to Host Mode */
	dwc3_set_mode(axxia->dwc3_reg, DWC3_GCTL_PRTCAP_HOST);

	return 0;
}

static void axxia_xhci_core_exit(struct axxia_xhci *axxia)
{
}

/*
  ------------------------------------------------------------------------------
  xhci_hcd_init
*/

int
xhci_hcd_init(int index, struct xhci_hccr **hccr, struct xhci_hcor **hcor)
{
	struct axxia_xhci *ctx;
	int ret;

	if (CONFIG_USB_MAX_CONTROLLER_COUNT <= index) {
		puts("XHCI: controller index out of range\n");

		return -EINVAL;
	}

	ctx = &axxia[index];

	if (0 == index)
		ctx->hcd = (struct xhci_hccr *)(0x9000000000);
	else if (1 == index)
		ctx->hcd = (struct xhci_hccr *)(0x9800000000);

	ctx->dwc3_reg = (struct dwc3 *)((char *)(ctx->hcd) + DWC3_REG_OFFSET);

	ret = axxia_xhci_core_init(ctx);

	if (ret) {
		printf("XHCI%d: failed to initialize controller\n", index);

		return -EINVAL;
	}

	*hccr = (ctx->hcd);
	*hcor = (struct xhci_hcor *)
		((uintptr_t)*hccr
		 + HC_LENGTH(xhci_readl(&(*hccr)->cr_capbase)));

	debug("Axxia-xhci%d: init hccr %lx and hcor %lx hc_length %ld\n",
	      index, (uintptr_t)*hccr, (uintptr_t)*hcor,
	      (uintptr_t)HC_LENGTH(xhci_readl(&(*hccr)->cr_capbase)));

	return 0;
}

void xhci_hcd_stop(int index)
{
	struct axxia_xhci *ctx = &axxia[index];

	axxia_xhci_core_exit(ctx);
}
