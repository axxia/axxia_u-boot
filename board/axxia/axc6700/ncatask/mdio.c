/*
 * mdio.c
 *
 * Basic MDIO access using the custom LSI controller.
 *
 * Copyright (C) 2009 LSI Corporation
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

/*#define DEBUG*/

#include <common.h>
#include <miiphy.h>
#include <malloc.h>
#include <asm/io.h>

#undef BZ33327_WA
/*#define BZ33327_WA*/

#define MDIO_REG_CTRL		0x00
#define MDIO_REG_STATUS		0x04
#define MDIO_REG_CLK_OFFSET	0x08
#define MDIO_REG_CLK_PERIOD	0x0c

static int initialize = 0;

extern int phy_by_index[];

unsigned short
mdio_read(int phy, int reg)
{
	u32 command;
#if defined(BZ33327_WA)
	u32 status;
#endif

#if defined(BZ33327_WA)
	/* Set the mdio_busy (status) bit.  */
	status = readl(CONFIG_AXXIA_MDIO0_BASE + MDIO_REG_STATUS);
	status |= 0x40000000;
	writel(status, CONFIG_AXXIA_MDIO0_BASE + MDIO_REG_STATUS);
#endif
	/* Write the command. */
	command = 0x10000000;	/* op_code: read */
	command |= (phy & 0x1f) << 16;
	command |= (reg & 0x1f) << 21;
	writel(command, CONFIG_AXXIA_MDIO0_BASE + MDIO_REG_CTRL);

#if defined(BZ33327_WA)
	/* Wait for the mdio_busy (status) bit to clear. */
	do {
		status = readl(CONFIG_AXXIA_MDIO0_BASE + MDIO_REG_STATUS);
	} while(0 != (status & 0x40000000));
#endif /* BZ33327_WA */

	/* Wait for the mdio_busy (control) bit to clear */
	do {
		command = readl(CONFIG_AXXIA_MDIO0_BASE + MDIO_REG_CTRL);
	} while ((command & 0x80000000) != 0);

	debug("mdio_read: phy@0x%x [%#x] -> %#x\n", phy, reg, command & 0xffff);
	return (command & 0xffff);
}

void
mdio_write(int phy, int reg, unsigned short value)
{
	u32 command;
#if defined(BZ33327_WA)
	u32 status;
#endif

	/* Wait for mdio_busy (control) to be clear. */
	do {
		command = readl(CONFIG_AXXIA_MDIO0_BASE + MDIO_REG_CTRL);
	} while ((command & 0x80000000) != 0);

#if defined(BZ33327_WA)
	/* Set the mdio_busy (status) bit */
	status = readl(CONFIG_AXXIA_MDIO0_BASE + MDIO_REG_STATUS);
	status |= 0x40000000;
	writel(status, CONFIG_AXXIA_MDIO0_BASE + MDIO_REG_STATUS);
#endif

	/* Write the command */
	command = 0x08000000;	/* op_code: write */
	/* Port addr which is device addr */
	command |= (phy & 0x1f) << 16;
	/* Regs within the device addr */
	command |= (reg & 0x1f) << 21;
	command |= value;
	writel(command, CONFIG_AXXIA_MDIO0_BASE + MDIO_REG_CTRL);

#if defined(BZ33327_WA)
	/* Wait for the mdio_busy (status) bit to clear */
	do {
		status = readl(CONFIG_AXXIA_MDIO0_BASE + MDIO_REG_STATUS);
	} while ((status & 0x40000000) != 0);
#endif

	/* Wait for the mdio_busy (control) bit to clear */
	do {
		command = readl(CONFIG_AXXIA_MDIO0_BASE + MDIO_REG_CTRL);
	} while ((command & 0x80000000) != 0);

	debug("mdio_write: phy@0x%x [%#x] <- %#x\n", phy, reg, value);
	return;
}

/*
  ----------------------------------------------------------------------
  mdio_initialize
*/

int
mdio_initialize(void)
{
	unsigned long offset, period;

    if(initialize)
		return 0;

	offset = getenv_ulong("mdio_clk_offset", 0, MDIO_CLK_OFFSET_DEFAULT);
	period = getenv_ulong("mdio_clk_period", 0, MDIO_CLK_PERIOD_DEFAULT);
	debug("MDIO: offset is 0x%lx, period is 0x%lx\n", offset, period);

	writel(offset, CONFIG_AXXIA_MDIO0_BASE + MDIO_REG_CLK_OFFSET);       
	writel(period, CONFIG_AXXIA_MDIO0_BASE + MDIO_REG_CLK_PERIOD);       

	/* Enable the MDIO Clock. */
	debug("MDIO: New clock enable control val 0x10 at 0x%lx", (unsigned long) (PERIPH_GPREG + 0x18));
	writel(0x10, PERIPH_GPREG + 0x18);

	initialize = 1;

	return 0;
}
