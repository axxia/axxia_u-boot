
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
#include <asm/io.h>
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

static int axxia_dwc3_core_soft_reset(struct dwc3 *dwc3_reg)
{
	unsigned int value;
	unsigned long address;
	int timeout;

	address = (unsigned long)(dwc3_reg);
	address -= DWC3_REG_OFFSET;
	value = readl(address + 0x20);
	value |= (1 << 1);
	writel(value, (address + 0x20));

	/*
	  The HCRST gets cleared by hardware after about 160 reads
	  (based on experimentation).
	*/

	timeout = 1000;

	do {
		value = readl(address + 0x20);
		--timeout;
	} while ((0 != (value & (1 << 1))) && 0 < timeout);

	if (0 == timeout)
		return -1;

	return 0;
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

	if (0 != axxia_dwc3_core_soft_reset(dwc3_reg)) {
		puts("reset timeout\n");

		return -EINVAL;
	}

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
		ctx->hcd = (struct xhci_hccr *)AXXIA_USB0_CONFIG;
	else if (1 == index)
		ctx->hcd = (struct xhci_hccr *)AXXIA_USB1_CONFIG;

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
