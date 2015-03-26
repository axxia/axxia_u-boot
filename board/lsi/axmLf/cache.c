/*
 *  board/lsi/axxia-arm/cache.c
 *
 *  Copyright (C) 2013 LSI (john.jacques@lsi.com)
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
#include <common.h>
#include <asm/io.h>
#include <asm/armv7.h>

/*
  ------------------------------------------------------------------------------
  set_outer_cache_state

  Set the mode in (0x10000 * offset) + 0x10, bits 1:0.  Verify that it
  got set by reading (0x10000 * offset) + 0x18), bits 3:2.

  The modes are as follows.

  0b00 - OFF
  0b01 - SFONLY
  0b10 - HALF
  0b11 - FULL
*/

static int
set_outer_cache_state(unsigned int state)
{
#ifndef CONFIG_AXXIA_SIM
	int i;
        unsigned int status;
	int retries;
	unsigned int hnf_offsets[] = {
		0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27
	};

	if (0 != (state & ~0x3))
		return -1;

	for (i = 0; i < (sizeof(hnf_offsets) / sizeof(unsigned int)); ++i)
		writel(state, (DICKENS + (0x10000 * hnf_offsets[i]) + 0x10));

	for (i = 0; i < (sizeof(hnf_offsets) / sizeof(unsigned int)); ++i) {
		retries = 10000;

		do {
			status = readl(DICKENS +
				       (0x10000 * hnf_offsets[i]) + 0x18);
			udelay(1);
		} while ((0 < --retries) && ((state << 2) != (status & 0xf)));

		if (0 == retries)
			return -1;
	}
#endif

	return 0;
}

/*
  ==============================================================================
  ==============================================================================
  Outer Cache Functions
  ==============================================================================
  ==============================================================================
*/

/*
  ------------------------------------------------------------------------------
  v7_outer_cache_enable
*/

void
v7_outer_cache_enable(void)
{
}

/*
  ------------------------------------------------------------------------------
  v7_outer_cache_disable
*/

void
v7_outer_cache_disable(void)
{
}

/*
  ------------------------------------------------------------------------------
  v7_outer_cache_flush_all
*/

void
v7_outer_cache_flush_all(void)
{
#ifndef RUN_UNCACHED
	if (0 != set_outer_cache_state(0x1))
		acp_failure(__FILE__, __FUNCTION__, __LINE__);

	if (0 != set_outer_cache_state(0x3))
		acp_failure(__FILE__, __FUNCTION__, __LINE__);
#endif

	return;
}

void
flush_l3_cache(void)
{
	v7_outer_cache_flush_all();
}

/*
  ------------------------------------------------------------------------------
  v7_outer_cache_inval_all
*/

void
v7_outer_cache_inval_all(void)
{
}

/*
  ------------------------------------------------------------------------------
  v7_outer_cache_flush_range
*/

void
v7_outer_cache_flush_range(u32 start, u32 end)
{
	/*
	  flushRange: DCCMVAC using the VA for the cache line we want
	  to invalidate. Set CLIDR[26:24] to 3. (Step by 64B to
	  increment through the range)
	*/
}

/*
  ------------------------------------------------------------------------------
  v7_outer_cache_inval_range
*/

void
v7_outer_cache_inval_range(u32 start, u32 end)
{
	/*
	  invalidateRange: DCIMVAC using the VA for the cache line we
	  want to invalidate. Set CLIDR[26:24] to 3. (Step by 64B to
	  increment through the range)
	*/
}

/*
  ------------------------------------------------------------------------------
  enable_caches
*/

void
enable_caches(void)
{
#ifndef CONFIG_AXXIA_SIM
	icache_enable();
	dcache_enable();
#endif

	return;
}
