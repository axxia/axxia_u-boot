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

/*
  -------------------------------------------------------------------------------
  v7_outer_cache_enable
*/

void
v7_outer_cache_enable(void)
{
}

/*
  -------------------------------------------------------------------------------
  v7_outer_cache_disable
*/

void
v7_outer_cache_disable(void)
{
}

/*
  -------------------------------------------------------------------------------
  v7_outer_cache_flush_all
*/

void
v7_outer_cache_flush_all(void)
{
#ifndef RUN_UNCACHED
	unsigned long hnf_offsets[] = {
		0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27
	};
	int i;
        unsigned long status, id;
	int retries;

	puts("Flushing L3 Cache\n");
	
	for (i = 0; i < (sizeof(hnf_offsets) / sizeof(unsigned long)); ++i) {
		/* set state SFONLY */
		writel(0x1, DICKENS + (0x10000 * hnf_offsets[i]) + 0x10);
	}

	for (i = 0; i < (sizeof(hnf_offsets) / sizeof(unsigned long)); ++i) {
		retries = 10000;

		do {
			status = readl(DICKENS +
				       (0x10000 * hnf_offsets[i]) + 0x18);
			udelay(1);
		} while ((0 < --retries) && (0x4 != (status & 0xf)));

		if (0 == retries)
			acp_failure(__FILE__, __FUNCTION__, __LINE__);
	}

	for (i = 0; i < (sizeof(hnf_offsets) / sizeof(unsigned long)); ++i) {
		/* set state ALL */
		writel(0x3, DICKENS + (0x10000 * hnf_offsets[i]) + 0x10);
	}

	for (i = 0; i < (sizeof(hnf_offsets) / sizeof(unsigned long)); ++i) {
		retries = 10000;

		do {
			status = readl(DICKENS +
				       (0x10000 * hnf_offsets[i]) + 0x18);
			udelay(1);
		} while ((0 < --retries) && (0xc != (status & 0xf)));

		if (0 == retries)
			acp_failure(__FILE__, __FUNCTION__, __LINE__);
	}
#endif

	return;
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
