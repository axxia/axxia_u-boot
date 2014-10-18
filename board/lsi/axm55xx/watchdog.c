/*
 *  board/lsi/axxia-arm/watchdog.c
 *
 *  Copyright (C) 2014 LSI (john.jacques@lsi.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <config.h>
#include <asm/io.h>

/*
  ==============================================================================
  ==============================================================================
  Public
  ==============================================================================
  ==============================================================================
*/

/*
  ------------------------------------------------------------------------------
  hw_watchdog_reset
*/

void
hw_watchdog_reset(void)
{
	writel(0xffffffff, (TIMER5 + TIMER_LOAD));
}

/*
  ------------------------------------------------------------------------------
  start_watchdog
*/

int
start_watchdog(void)
{
	unsigned long value;

	/* Unlock syscon. */
	writel(0xab, (SYSCON + 0x1000));

	/* Use reset map. */
	value = readl(SYSCON + 0x1004);
	value |= 0x40;
	writel(value, (SYSCON + 0x1004));

	/* Set reset_read_done (0x156.0x1.0xc). */
	writel(0x80000000, (SYSCON + 0x180c));

	/* Enable watchdog resets. */
	value = readl(SYSCON + 0x1008);
	value |= 0x80;
	writel(value, (SYSCON + 0x1008));

	/* Set up the timer. */
	writel(0, (TIMER5 + TIMER_CONTROL));
	writel(0xffffffff, (TIMER5 + TIMER_LOAD));
	writel(0xffffffff, (TIMER5 + TIMER_VALUE));
	writel(0xe2, (TIMER5 + TIMER_CONTROL));

	/* Lock syscon. */
	writel(0, (SYSCON + 0x1000));

	return 0;
}

/*
  ------------------------------------------------------------------------------
  stop_watchdog
*/

void
stop_watchdog(void)
{
	unsigned long reset_control;

	/* Unlock syscon. */
	writel(0xab, (SYSCON + 0x1000));

	/* Disable watchdog resets. */
	reset_control = readl(SYSCON + 0x1008);
	reset_control &= ~0x80;
	writel(reset_control, (SYSCON + 0x1008));

	/* Turn off the timer. */
	writel(0, (TIMER5 + TIMER_CONTROL));

	/* Lock syscon. */
	writel(0, (SYSCON + 0x1000));

	return;
}
