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

/*#define LSI_DEBUG*/
#define LSI_WARNING
/*#define LSI_LOGIO*/
#include <config.h>
#include <common.h>
#include <asm/io.h>

/*
  ======================================================================
  ======================================================================
  Local
  ======================================================================
  ======================================================================
*/

#undef BZ33327_WA
#define BZ33327_WA

/*
  ======================================================================
  ======================================================================
  Global
  ======================================================================
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  mdio_initialize
*/

int
mdio_initialize(void)
{
#ifdef AXM_35xx
	unsigned long per_clock;
	unsigned long mdio_clk_value;
	int rc;
#endif
	if (is_asic()) {
#ifndef AXM_35xx
		WRITEL(0x10, MDIO_CLK_OFFSET);
		WRITEL(0x2c, MDIO_CLK_PERIOD);
#else
		/* 1MHz MDIO clock which is 1000 ns MDIO clock period */
		do {
			for (;;) {
				int rc;
				rc = acp_clock_get(clock_peripheral, &per_clock);
				if (0 == rc) {
					break;
				}
			}
		} while (0 == per_clock);

		/* (MDIO period/clk_per period/2) */
		mdio_clk_value = (per_clock/1000)/2;
		
		WRITEL(mdio_clk_value, MDIO_CLK_OFFSET);
		WRITEL(mdio_clk_value, MDIO_CLK_PERIOD);

#endif

	} else {
		WRITEL(5, MDIO_CLK_OFFSET);
		WRITEL(0x0c, MDIO_CLK_PERIOD);
	}

	return 0;
}

/*
  ----------------------------------------------------------------------
  mdio_read
*/

unsigned short
mdio_read(int phy, int reg)
{
	unsigned long command = 0;
	unsigned long status;

	DEBUG_PRINT("phy=0x%x reg=0x%x\n", phy, reg);

	/* Wait for mdio_busy (control) to be clear. */

	do {
		command = READL(MDIO_CONTROL_RD_DATA);
	} while(0 != (command & 0x80000000));

#if defined(BZ33327_WA)

	/* Set the mdio_busy (status) bit. */
	status = READL(MDIO_STATUS_RD_DATA);
	status |= 0x40000000;
	WRITEL(status, MDIO_STATUS_RD_DATA);

#endif /* BZ33327_WA */

	/* Write the command.*/
	command = 0x10000000;	/* op_code: read */
	command |= (reg & 0x1f) << 21; /* device_addr (target register) */
	command |= (phy & 0x1f) << 16; /* port_addr (target device) */
	WRITEL(command, MDIO_CONTROL_RD_DATA);

#if defined(BZ33327_WA)

	/* Wait for the mdio_busy (status) bit to clear. */

	do {
		status = READL(MDIO_STATUS_RD_DATA);
	} while(0 != (status & 0x40000000));

#endif /* BZ33327_WA */

	/* Wait for the mdio_busy (control) bit to clear. */

	do {
		command = READL(MDIO_CONTROL_RD_DATA);
	} while(0 != (command & 0x80000000));

	return (unsigned short)(command & 0xffff);
}

/*
  ----------------------------------------------------------------------
  mdio_write
*/

void
mdio_write(int phy, int reg, unsigned short value)
{
	unsigned long command = 0;
	unsigned long status;

	DEBUG_PRINT("phy=0x%x reg=0x%x value=0x%x\n", phy, reg, value);

	/* Wait for mdio_busy (control) to be clear. */

	do {
		command = READL(MDIO_CONTROL_RD_DATA);
	} while (0 != (command & 0x80000000));

#if defined(BZ33327_WA)

	/* Set the mdio_busy (status) bit. */
	status = READL(MDIO_STATUS_RD_DATA);
	status |= 0x40000000;
	WRITEL(status, MDIO_STATUS_RD_DATA);

#endif /* BZ33327_WA */

	/* Write the command. */
	command = 0x08000000;	/* op_code: write */
	command |= (reg & 0x1f) << 21; /* device_addr (target register) */
	command |= (phy & 0x1f) << 16; /* port_addr (target device) */
	command |= (value & 0xffff); /* value */
	WRITEL(command, MDIO_CONTROL_RD_DATA);

#if defined(BZ33327_WA)

	/* Wait for the mdio_busy (status) bit to clear. */

	do {
		status = READL(MDIO_STATUS_RD_DATA);
	} while (0 != (status & 0x40000000));

#endif /* BZ33327_WA */

	/* Wait for the mdio_busy (control) bit to clear. */

	do {
		command = READL(MDIO_CONTROL_RD_DATA);
	} while (0 != (command & 0x80000000));

	return;
}
