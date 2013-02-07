/*
 * dt.c
 *
 * Default device trees for LSI's ACP.
 *
 * Copyright (C) 2009 LSI Corporation
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
#include <common.h>

#if defined(ACP_ISS)
#if defined(ACP_X1V1)
#include "dtb/ACPISS344xV1.h"
#elif defined(ACP_X1V2)
#include "dtb/ACPISS344xV2.h"
#elif defined(CONFIG_ACP_342X)
#include "dtb/ACPISS342x.h"
#else
#error "Unknown Target!"
#endif
#elif defined(ACP_X1V1)
#include "dtb/ACP344xV1.h"
#elif defined(ACP_X1V2)
#include "dtb/ACP344xV2.h"
#elif defined(CONFIG_ACP_342X)
#include "dtb/ACP342x.h"
#elif defined(ACP_25xx)
#include "dtb/ACP25xx.h"
#endif

unsigned long *
get_acp_fdt(int group)
{
	if (ACP_NR_CORES > group) {
		return acp_fdt[group];
	}

	return NULL;
}
