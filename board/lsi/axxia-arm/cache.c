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
  ===============================================================================
  ===============================================================================
  Outer Cache Functions
  ===============================================================================
  ===============================================================================
*/

static const unsigned char hnf_offsets[] = {
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27
};

static int l3_enabled = 1;

static void
set_pstate(unsigned long req_state, unsigned long act_state)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(hnf_offsets); ++i) {
		/* set state */
		writel(req_state, DICKENS + (0x10000 * hnf_offsets[i]) + 0x10);
	}

	for (i = 0; i < ARRAY_SIZE(hnf_offsets); ++i) {
		int retries = 10000;
		unsigned long status;

		do {
			status = readl(DICKENS + (0x10000 * hnf_offsets[i]) + 0x18);
			udelay(1);
		} while ((0 < --retries) && (act_state != (status & 0xf)));

		if (0 == retries)
			acp_failure(__FILE__, __FUNCTION__, __LINE__);
	}
}

/*
  -------------------------------------------------------------------------------
  v7_outer_cache_enable
*/

void
v7_outer_cache_enable(void)
{
#ifndef RUN_UNCACHED
	set_pstate(0x03, 0xc);
	l3_enabled = 1;
#endif
}

/*
  -------------------------------------------------------------------------------
  v7_outer_cache_disable
*/

void
v7_outer_cache_disable(void)
{
	set_pstate(0x00, 0x00);
	l3_enabled = 0;
}

/*
  -------------------------------------------------------------------------------
  v7_outer_cache_flush_all
*/

void
v7_outer_cache_flush_all(void)
{
#ifndef RUN_UNCACHED
	if (l3_enabled) {
		set_pstate(0x00, 0x00);
		set_pstate(0x03, 0xc);
	}
#endif
}

/*
  -------------------------------------------------------------------------------
  v7_outer_cache_inval_all
*/

void
v7_outer_cache_inval_all(void)
{
}

/*
  -------------------------------------------------------------------------------
  v7_outer_cache_flush_range
*/

void
v7_outer_cache_flush_range(u32 start, u32 end)
{
}

/*
  -------------------------------------------------------------------------------
  v7_outer_cache_inval_range
*/

void
v7_outer_cache_inval_range(u32 start, u32 end)
{
}
