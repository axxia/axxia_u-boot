/*
 *  board/axxia/axc6700/qos.c
 *
 *  Copyright (C) 2017 Intel (john.jacques@intel.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307	 USA
 */

#include <common.h>
#include <asm/io.h>

/*
  ------------------------------------------------------------------------------
  axxia_set_qos
*/

#define QOS_CONTROL_MASK 0xf007f

int
axxia_set_qos(void)
{
	char *env_qos;
	char env_name[20];
	int i;
	unsigned offsets[] = {
		(0x40 << 16 | 0x110),
		(0x45 << 16 | 0x210),
		(0x46 << 16 | 0x110),
		(0x48 << 16 | 0x210),
		(0x49 << 16 | 0x110),
		(0x4e << 16 | 0x210),
		(0x4f << 16 | 0x110),
		(0x51 << 16 | 0x210)
	};

	for (i = 0; i < 8; ++i) {
		sprintf(env_name, "cluster_%d_qos", i);
		env_qos = getenv(env_name);

		if (NULL != env_qos) {
			unsigned long value = simple_strtoul(env_qos, NULL, 0);

			if (0 != (~QOS_CONTROL_MASK & value)) {
				error("Bad QoS Control Value: 0x%lx\n", value);

				continue;
			}

			writel(value, (DICKENS + offsets[i]));
			debug("QoS: Wrote 0x%lx to 0x%lx (%s)\n",
			      value, (DICKENS + offsets[i]), env_name);
		}
	}

	return 0;
}
