/*
 * Driver for Axxia MDIO controller.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <config.h>
#include <common.h>
#include <asm/io.h>
#include <miiphy.h>
#include <malloc.h>

#undef BZ33327_WA
/*#define BZ33327_WA*/

#define MDIO_REG_CTRL		0x00
#define MDIO_REG_STATUS		0x04
#define MDIO_REG_CLK_OFFSET	0x08
#define MDIO_REG_CLK_PERIOD	0x0c

static int
axxia_mdio_read(struct mii_dev *bus, int addr, int devad, int reg)
{
	void __iomem *base = bus->priv;
	u32 command;
#if defined(BZ33327_WA)
	u32 status;
#endif

#if defined(BZ33327_WA)
	/* Set the mdio_busy (status) bit.  */
	status = readl(base + MDIO_REG_STATUS);
	status |= 0x40000000;
	writel(status, base + MDIO_REG_STATUS);
#endif
	/* Write the command. */
	command = 0x10000000;	/* op_code: read */
	command |= (addr & 0x1f) << 16;
	command |= (reg & 0x1f) << 21;
	writel(command, base + MDIO_REG_CTRL);

#if defined(BZ33327_WA)
	/* Wait for the mdio_busy (status) bit to clear. */
	do {
		status = readl(base + MDIO_REG_STATUS);
	} while(0 != (status & 0x40000000));
#endif /* BZ33327_WA */

	/* Wait for the mdio_busy (control) bit to clear */
	do {
		command = readl(base + MDIO_REG_CTRL);
	} while ((command & 0x80000000) != 0);

	debug("mdio_read: phy@0x%x [%#x] -> %#x\n", addr, reg, command & 0xffff);
	return (command & 0xffff);
}

static int
axxia_mdio_write(struct mii_dev *bus, int addr, int devad, int reg, u16 val)
{
	void __iomem *base = bus->priv;
	u32 command;
#if defined(BZ33327_WA)
	u32 status;
#endif

	/* Wait for mdio_busy (control) to be clear. */
	do {
		command = readl(base + MDIO_REG_CTRL);
	} while ((command & 0x80000000) != 0);

#if defined(BZ33327_WA)
	/* Set the mdio_busy (status) bit */
	status = readl(base + MDIO_REG_STATUS);
	status |= 0x40000000;
	writel(status, base + MDIO_REG_STATUS);
#endif

	/* Write the command */
	command = 0x08000000;	/* op_code: write */
	/* Port addr which is device addr */
	command |= (addr & 0x1f) << 16;
	/* Regs within the device addr */
	command |= (reg & 0x1f) << 21;
	command |= val;
	writel(command, base + MDIO_REG_CTRL);

#if defined(BZ33327_WA)
	/* Wait for the mdio_busy (status) bit to clear */
	do {
		status = readl(base + MDIO_REG_STATUS);
	} while ((status & 0x40000000) != 0);
#endif

	/* Wait for the mdio_busy (control) bit to clear */
	do {
		command = readl(base + MDIO_REG_CTRL);
	} while ((command & 0x80000000) != 0);

	debug("mdio_write: phy@0x%x [%#x] <- %#x\n", addr, reg, val);
	return 0;
}

static int
axxia_mdio_reset(struct mii_dev *bus)
{
	return 0;
}

int
axxia_mdio_init(void)
{
	static int initialized;
	unsigned long offset, period;
#ifdef CONFIG_AXXIA_MDIO0_BASE
	struct mii_dev *dev0;
#endif
#ifdef CONFIG_AXXIA_MDIO1_BASE
	struct mii_dev *dev1;
#endif

	if (initialized)
		return 0;

	offset = getenv_ulong("mdio_clk_offset", 0, MDIO_CLK_OFFSET_DEFAULT);
	period = getenv_ulong("mdio_clk_period", 0, MDIO_CLK_PERIOD_DEFAULT);
	debug("MDIO: offset is %#lx, period is %#lx\n", offset, period);

#ifdef CONFIG_AXXIA_MDIO0_BASE
	dev0 = mdio_alloc();
	snprintf(dev0->name, MDIO_NAME_LEN, "axxia-mdio0");
	dev0->priv = (void *)CONFIG_AXXIA_MDIO0_BASE;
	dev0->read = axxia_mdio_read;
	dev0->write = axxia_mdio_write;
	dev0->reset = axxia_mdio_reset;

	if (mdio_register(dev0) < 0) {
		debug("Failed to register MDIO %s\n", dev0->name);
		free(dev0);

		return -1;
	}

	writel(offset, dev0->priv + MDIO_REG_CLK_OFFSET);
	writel(period, dev0->priv + MDIO_REG_CLK_PERIOD);

	/* Enable the MDIO Clock. */
#ifndef CONFIG_TARGET_EMULATION
#ifdef CONFIG_AXXIA_ANY_56XX
	writel(0x10, PERIPH_GPREG + 0x18);
#endif
#endif

	/*
	  Set the RGMII Clock Pad Skew

	  This is PHY specific, and may only apply to Victoria/Waco.
	*/

#ifdef CONFIG_TARGET_HARDWARE
	dev0->write(dev0, 7, 0, 0xd, 2);
	dev0->write(dev0, 7, 0, 0xe, 8);
	dev0->write(dev0, 7, 0, 0xd, 0x4002);
	dev0->write(dev0, 7, 0, 0xe, 0x3ff);
#endif

#endif	/* CONFIG_AXXIA_MDIO0_BASE */

#ifdef CONFIG_AXXIA_MDIO1_BASE
	dev1 = mdio_alloc();
	snprintf(dev1->name, MDIO_NAME_LEN, "axxia-mdio1");
	dev1->priv = (void *)CONFIG_AXXIA_MDIO1_BASE;
	dev1->read = axxia_mdio_read;
	dev1->write = axxia_mdio_write;
	dev1->reset = axxia_mdio_reset;

	if (mdio_register(dev1) < 0) {
		debug("Failed to register MDIO %s\n", dev1->name);
		free(dev1);

		return -1;
	}

	writel(offset, dev1->priv + MDIO_REG_CLK_OFFSET);
	writel(period, dev1->priv + MDIO_REG_CLK_PERIOD);
#endif	/* CONFIG_AXXIA_MDIO0_BASE */

	initialized = 1;

	return 0;
}
