/*
 * Architected Timer setup for SMDK5250 board based on EXYNOS5
 *
 * Copyright (C) 2012 Christoffer Dall <cdall@cs.columbia.edu>
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <config.h>
#include <asm/io.h>

void arch_timer_init(void)
{
#if 0
	unsigned long cpuid, freq;
	asm volatile("mrc	p15, 0, %[cpuid], c0, c1, 1":
		     [cpuid] "=r" (cpuid));

	if ((cpuid >> 16) & 1) {
		freq = 256000000;
		asm volatile("mcr p15, 0, %[freq], c14, c0, 0" : :
			     [freq] "r" (freq));
	}
#endif
}
