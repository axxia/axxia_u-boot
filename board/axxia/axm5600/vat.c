/*
*  board/lsi/axxia-arm/vat.c
*
*  Copyright (C) 2014 LSI (john.jacques@lsi.com)
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

/*
==============================================================================
==============================================================================
Local Stuff
==============================================================================
==============================================================================
*/

/*
------------------------------------------------------------------------------
set_vat

Set the top 8 bits of the physical address of system memory
to the given value.
*/

static int
set_vat(unsigned long value)
{
	unsigned long buffer[4];
	int rc;

	rc = ncr_read(NCP_REGION_ID(0x16, 0x10), 0, 0x1000, 16, buffer);

	if (0 != rc)
		return -1;

	buffer[2] = value;
	rc = ncr_write(NCP_REGION_ID(0x16, 0x10), 0, 0x1000, 16, buffer);

	if (0 != rc)
		return -1;

	return 0;
}

/*
==============================================================================
==============================================================================
Global Stuff
==============================================================================
==============================================================================
*/

/*
------------------------------------------------------------------------------
set_vat_reset
*/

int
set_vat_reset(void)
{
	return set_vat(0x20);
}

/*
------------------------------------------------------------------------------
set_vat_mission
*/

int
set_vat_mission(void)
{
	return set_vat(0);
}
