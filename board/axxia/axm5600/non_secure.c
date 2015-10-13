
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

#define ARM_GICV2_DIST_CTRL		0x00
#define ARM_GICV2_DIST_TYPE		0x04
#define ARM_GICV2_DIST_SEC_REG		0x80

#define ARM_GICV2_CPU_CTRL		0x00

#define ARM_GICV2_ICCPMR		0x04

#if 0
static unsigned long read_nsacr(void)
{
	unsigned long val;
	asm volatile("mrc p15, 0, %0, c1, c1, 2": "=r" (val));
	return val;
}

static void write_nsacr(unsigned long val)
{
	asm volatile("mcr p15, 0, %0, c1, c1, 2": : "r" (val));
}
#endif

void non_secure_init(void)
{
#if 0
	unsigned long addr, type, num_regs;
	unsigned long nsacr, ctrl;
	int i;

	addr = GIC_DIST_BASE;
	type = readl(addr + ARM_GICV2_DIST_TYPE);
	num_regs = (type & 0x1f) + 1;

	/* Set all interrupts to be non-secure */
	addr = GIC_DIST_BASE + ARM_GICV2_DIST_SEC_REG;
	for (i = 0; i < num_regs; i++) {
		writel(0xffffffff, addr);
		addr += 4;
	}

	/* Set GIC priority mask bit [7] = 1 */
	addr = GIC_CPU_BASE;
	writel(0x80, addr + ARM_GICV2_ICCPMR);

	/* Set NSACR to allow coprocessor access from non-secure */
	nsacr = read_nsacr();
	nsacr |= 0x43fff;
	write_nsacr(nsacr);

	/* Enable group 1 interrupts on CPU interface */
	addr = GIC_CPU_BASE + ARM_GICV2_CPU_CTRL;
	ctrl = readl(addr);
	writel(ctrl | 0x2, addr);

	/* Disable group 0 interrupts and enable group 1 interrupts on Dist */
	addr = GIC_DIST_BASE + ARM_GICV2_DIST_CTRL;
	ctrl = readl(addr);
	ctrl = (ctrl & ~0x1) | 0x2;
	writel(ctrl | 0x1, addr);
#endif
}
