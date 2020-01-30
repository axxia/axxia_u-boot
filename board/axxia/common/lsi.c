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

/*
  ------------------------------------------------------------------------------
  get_ddr_init_type

  Return the type of the current DDR init.
*/

#ifdef CONFIG_AXXIA_ANY_XLF

/*
  The 6700 Version
*/

enum ddr_init_type
get_ddr_init_type(void)
{
#ifdef CONFIG_MEMORY_RETENTION
	if (0 == (global->flags & PARAMETERS_GLOBAL_ENABLE_RETENTION)) {
		/* DDR Retention is NOT Enabled... so 'cold' */
		return cold;
	} else {
		/* DDR Retention is Enabled */
		if (0 != (syscon_0x0dc & (1 << 0)))
			return planned;

		if (0 != (syscon_0x100 & (1 << 12)))
			return unplanned;
	}
#endif	/* CONFIG_MEMORY_RETENTION */
	return cold;
}
#else  /* CONFIG_AXXIA_ANY_XLF */

/*
  The 5600 Version
*/

enum ddr_init_type
get_ddr_init_type(void)
{
#ifdef CONFIG_MEMORY_RETENTION
	if (0 != (global->flags & PARAMETERS_GLOBAL_ENABLE_RETENTION) &&
	    0 != (syscon_0x0dc & (1 << 0)))
		return planned;
	else
		return cold;
#endif	/* CONFIG_MEMORY_RETENTION */
	return cold;
}
#endif /* CONFIG_AXXIA_ANY_XLF */

const char *
get_ddr_init_name(enum ddr_init_type type)
{
	int i = 0;
	static char *names[] = {
		"Unknown",
		"Cold Reset",
		"Planned Retention Reset",
		"Unplanned Retention Reset"
	};

	switch (type) {
	case cold:
		i = 1;
		break;
	case planned:
		i = 2;
		break;
	case unplanned:
		i = 3;
		break;
	default:
		break;
	}

	return names[i];
}
