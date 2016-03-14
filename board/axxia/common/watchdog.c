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

#include <common.h>
#include <asm/io.h>

static unsigned int count = 0xffffffff;

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
	writel(count, (TIMER5 + TIMER_LOAD));
}

/*
------------------------------------------------------------------------------
start_watchdog
*/

int
start_watchdog(unsigned int timeout)
{
	unsigned int value;
	unsigned int per_clock_hz;
	unsigned long long new_count;

	/* Set 'count'. */
	if (0 != acp_clock_get(clock_peripheral, &per_clock_hz))
		return -1;

	new_count = timeout * per_clock_hz * 1000;

	if (0xffffffffULL < new_count)
		return -2;

	count = (unsigned int)new_count;

	/* Unlock syscon. */
	writel(0xab, (SYSCON + 0x2000));

	/* Disable the timer. */
	writel(0, (TIMER5 + TIMER_CONTROL));

	/* Enable watchdog 0, system reset. */
	value = readl(SYSCON + 0x2008);
	value |= 0x140;
	writel(value, (SYSCON + 0x2008));

	/* Set up and enable the timer. */
	writel(count, (TIMER5 + TIMER_LOAD));
	writel(count, (TIMER5 + TIMER_VALUE));
	writel(0xe2, (TIMER5 + TIMER_CONTROL));

	/* Lock syscon. */
	writel(0, (SYSCON + 0x2000));

#ifdef MAKE_WATCHDOG_PERMANENT
	/* Write 0x4 to 0x171.1.0x900 */
	writel(0x2, (PERIPH_SCB + 0x100000 + 0x900));
#endif

	return 0;
}

/*
------------------------------------------------------------------------------
stop_watchdog
*/

void
stop_watchdog(void)
{
#ifndef MAKE_WATCHDOG_PERMANENT
	unsigned long reset_control;

	/* Turn off the timer. */
	writel(0, (TIMER5 + TIMER_CONTROL));

	/* Unlock syscon. */
	writel(0xab, (SYSCON + 0x2000));

	/* Disable watchdog resets. */
	reset_control = readl(SYSCON + 0x2008);
	reset_control &= ~0x140;
	writel(reset_control, (SYSCON + 0x2008));

	/* Lock syscon. */
	writel(0, (SYSCON + 0x2000));
#endif	/* MAKE_WATCHDOG_PERMANENT */

	return;
}

/*
  ------------------------------------------------------------------------------
  hw_watchdog_init
*/

void
hw_watchdog_init(void)
{
	start_watchdog(WATCHDOG_TIMEOUT_SECS);

	return;
}
