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
	unsigned offsets_a0[] = {
		/* A0 */
		(0x45 << 16 | 0x210), /* xp5, dev1 */
		(0x46 << 16 | 0x110), /* xp6, dev0 */
		(0x48 << 16 | 0x210), /* xp8, dev1 */
		(0x49 << 16 | 0x110), /* xp9, dev0 */
		(0x4e << 16 | 0x210), /* xp14, dev1 */
		(0x4f << 16 | 0x110), /* xp15, dev0 */
		(0x51 << 16 | 0x210), /* xp17, dev1 */
		(0x40 << 16 | 0x110)  /* xp0, dev0 */
	};
	unsigned offsets_b0[] = {
		/* B0 */
		(0x40 << 16 | 0x110), /* xp0, dev0 */
		(0x45 << 16 | 0x210), /* xp5, dev1 */
		(0x46 << 16 | 0x110), /* xp6, dev0 */
		(0x47 << 16 | 0x110), /* xp7, dev0 */
		(0x49 << 16 | 0x110), /* xp9, dev0 */
		(0x4e << 16 | 0x210), /* xp14, dev1 */
		(0x50 << 16 | 0x110), /* xp16, dev0 */
		(0x51 << 16 | 0x210)  /* xp17, dev1 */
	};

	for (i = 0; i < 8; ++i) {
		sprintf(env_name, "cluster_%d_qos", i);
		env_qos = getenv(env_name);
		unsigned offset;

		if (NULL != env_qos) {
			unsigned long value = simple_strtoul(env_qos, NULL, 0);

			if (0 != (~QOS_CONTROL_MASK & value)) {
				error("Bad QoS Control Value: 0x%lx\n", value);

				continue;
			}

			if (0 != is_xlf_a0())
				offset = offsets_a0[i];
			else
				offset = offsets_b0[i];

			writel(value, (DICKENS + offset));
			debug("QoS: Wrote 0x%lx to 0x%lx (%s)\n",
			      value, (DICKENS + offset), env_name);
		}
	}

	return 0;
}
