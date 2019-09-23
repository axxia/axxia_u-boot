/*
 * board/lsi/common/lsi.c
 *
 * Copyright (C) 2013 LSI Corporation
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software;you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation;either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY;without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program;if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <config.h>

#ifdef CONFIG_LSI

int lsi_logio_enable = -1;
int lsi_debug_enable = -1;

#endif	/* CONFIG_LSI */

/*
  ------------------------------------------------------------------------------
  is_xlf_a0

  Detect A0 parts, which need to be configured slightly differently.
  Display a warning if the part is unfused, and assume !A0 in that
  case.
*/

#ifdef CONFIG_AXXIA_ANY_XLF

int
is_xlf_a0(void)
{
	if (0 == pfuse) {
		unsigned int value;

		/* Handle Un-Fused Parts */
		ncr_read32(NCP_REGION_ID(0x16, 0xff), 0, &value);

		if (1 == ((value >> 8) & 0x7))
			return 0; /* B0 */
	} else if (0 != ((pfuse & 0x700) >> 8)) {
		return 0;	/* B0 */
	}

	return 1;		/* A0 */
}

#endif	/* CONFIG_AXXIA_ANY_XLF */
