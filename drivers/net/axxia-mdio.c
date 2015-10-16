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
#define BZ33327_WA

#define MDIO_REG_CTRL		0x00
#define MDIO_REG_STATUS		0x04
#define MDIO_REG_CLK_OFFSET	0x08
#define MDIO_REG_CLK_PERIOD	0x0c

static int
axxia_mdio_read(struct mii_dev *bus, int addr, int devad, int reg)
{
	void __iomem *base = bus->priv;
	u32 command, status;

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

	debug("mdio_read: phy@%x [%#x] -> %#x\n", addr, reg, command & 0xffff);

	return (command & 0xffff);
}

static int
axxia_mdio_write(struct mii_dev *bus, int addr, int devad, int reg, u16 val)
{
	void __iomem *base = bus->priv;
	u32 command, status;

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
	command |= (addr & 0x1f) << 16;
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

	debug("mdio_write: phy@%x [%#x] <- %#x\n", addr, reg, val);
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
	struct mii_dev *dev;

	if (initialized)
		return 0;

	offset = getenv_ulong("mdio_clk_offset", 0, MDIO_CLK_OFFSET_DEFAULT);
	period = getenv_ulong("mdio_clk_period", 0, MDIO_CLK_PERIOD_DEFAULT);
	debug("MDIO: offset is %#lx, period is %#lx\n", offset, period);

	dev = mdio_alloc();
	snprintf(dev->name, MDIO_NAME_LEN, "axxia-mdio");
	dev->priv = (void *)CONFIG_AXXIA_MDIO_BASE;
	dev->read = axxia_mdio_read;
	dev->write = axxia_mdio_write;
	dev->reset = axxia_mdio_reset;
	if (mdio_register(dev) < 0) {
		debug("Failed to register MDIO %s\n", dev->name);
		free(dev);
		return -1;
	}
	writel(offset, dev->priv + MDIO_REG_CLK_OFFSET);
	writel(period, dev->priv + MDIO_REG_CLK_PERIOD);
	initialized = 1;
	return 0;
}
