/*
 * board/lsi/acp/version.c
 *
 * Copyright (C) 2010 LSI Corporation
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <config.h>

#ifdef CONFIG_ACP

/*
  is_asic
*/

int
is_asic(void)
{
#if 0
#if !defined(ACP_ISS) && !defined(ACP_EMU)
	return 1;
#else
	return 0;
#endif
#endif

	return 0;
}

#if 0

unsigned long
get_sysmem_size(void)
{
#if defined(ACP_ISS)
	return 256 * 1024;
#else
	unsigned long size = 0;

#if defined(CONFIG_ACP3)
	char *env_memory;

	env_memory = getenv("memory");

	if ((char *)0 != env_memory) {
		size = simple_strtoul(env_memory, (char **)0, 0);
	} else {
		size = 1024 * 1024;
	}
#else
	size = (1 << (sysmem_size - 20));
#endif
	return size;
#endif
}
#endif

#endif /* CONFIG_ACP */
