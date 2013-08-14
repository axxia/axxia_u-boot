/*
 *  board/lsi/axxia-arm/axxia.c
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
#include <twl6035.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/mmc_host_def.h>

#include "mux_data.h"

DECLARE_GLOBAL_DATA_PTR;

const struct omap_sysinfo sysinfo = {
	"Board: OMAP5430 EVM\n"
};

/*
  ==============================================================================
  ==============================================================================
  Private
  ==============================================================================
  ==============================================================================
*/

/*
  ------------------------------------------------------------------------------
  set_sdcr
*/

int
set_sdcr(void)
{
	char *env_sdcr;
	unsigned long sdcr_value;
	unsigned long sdcr_offsets[] = {
		0x00, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27
	};
	int i;

	if (NULL == (env_sdcr = getenv("sdcr")))
		sdcr_value = DEFAULT_SDCR_VALUE;
	else
		sdcr_value = simple_strtoul(env_sdcr, NULL, 16);

	printf("SDCR: 0x%lx\n", sdcr_value);

	for (i = 0; i < (sizeof(sdcr_offsets) / sizeof(unsigned long)); ++i) {
		int retries = 1000;
		int offset;

		offset = DICKENS | (sdcr_offsets[i] << 16);
		writel(sdcr_value, (offset + 0x210));

		do {
			--retries;
		} while (0 < retries && sdcr_value != readl(offset + 0x200));

		if (0 == retries)
			return -1;
	}

	return 0;
}

/*
  -------------------------------------------------------------------------------
  cluster_power
*/
#if 0
static int
cluster_power(void)
{
	char *cluster_enable_env;
	unsigned long cluster_enable;

	if (NULL == (cluster_enable_env = getenv("cluster_enable")))
		cluster_enable = 0xf;
	else
		cluster_enable = simple_strtoul(cluster_enable_env);

	/*
	  How many clusters should be up?
	*/
	return;
}
#endif

/*
  ==============================================================================
  ==============================================================================
  Public
  ==============================================================================
  ==============================================================================
*/

/**
 * @brief board_init
 *
 * @return 0
 */
int
board_init(void)
{
	return 0;
}

/*
  ------------------------------------------------------------------------------
  misc_init_r
*/

int
misc_init_r(void)
{
	if (0 != set_sdcr())
		acp_failure(__FILE__, __FUNCTION__, __LINE__);

	return 0;
}

void set_muxconf_regs_essential(void)
{
	return;
}

void set_muxconf_regs_non_essential(void)
{
	return;
}

/*
  ------------------------------------------------------------------------------
  board_early_init_f
*/

int
board_early_init_f(void)
{
	gd->ram_size = 0x40000000;

	return 0;
}

/*
  ------------------------------------------------------------------------------
  arch_early_init_r
*/

int
arch_early_init_r(void)
{
	return 0;
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
