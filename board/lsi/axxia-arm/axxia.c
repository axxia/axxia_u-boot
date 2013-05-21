/*
 *  board/lsi/axxia-arm/spl.c
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

#include <common.h>
#include <twl6035.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/mmc_host_def.h>

#include "mux_data.h"

DECLARE_GLOBAL_DATA_PTR;

const struct omap_sysinfo sysinfo = {
	"Board: OMAP5430 EVM\n"
};

/**
 * @brief board_init
 *
 * @return 0
 */
int
board_init(void)
{
	gd->bd->bi_boot_params = _parameters_start;

	return 0;
}

/*
  ------------------------------------------------------------------------------
  misc_init_r
*/

int
misc_init_r(void)
{
	unsigned long hold_cpu;
	int i;

	/*
	  Wake up core 1.
	*/

#if 0
	printf("%s:%d - Waking up core 1.\n", __FILE__, __LINE__);
	writel(0xab, (SYSCON + 0x1000));
	hold_cpu = readl(SYSCON + 0x1010);
	hold_cpu &= ~(1 << 1);
	writel(hold_cpu, (SYSCON + 0x1010));
#endif

	return 0;
}

void set_muxconf_regs_essential(void)
{
}

void set_muxconf_regs_non_essential(void)
{
}

/*
  ------------------------------------------------------------------------------
  board_early_init_f
*/

int
board_early_init_f(void)
{
	gd->ram_size = 0x40000000;
}

/*
  ------------------------------------------------------------------------------
  ft_board_setup
*/

void
ft_board_setup(void *blob, bd_t *bd)
{
	int i;
	char cpu_string[40];
	int node;
	const char *path;
	unsigned long release_addr;
	int rc;

	release_addr = htonl(_spin_table_start_ofs + spin_loop_release_offset);

	for (i = 1; i < 16; ++i) {
		sprintf(cpu_string, "/cpus/cpu@%d", i);
		node = fdt_path_offset(blob, cpu_string);

		if (0 > node)
			continue;

		rc = fdt_setprop(blob, node, "cpu-release-addr",
				 &release_addr, sizeof(unsigned long));

		if (0 != rc) {
			printf("%s:%d - Error setting property, %d!\n",
			       __FILE__, __LINE__, rc);
			continue;
		}
	}

	return;
}
