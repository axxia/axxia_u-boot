/*
*  Copyright (C) 2013 LSI Corporation
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
#include <asm/io.h>

/*
==============================================================================
==============================================================================
Public Interface
==============================================================================
==============================================================================
*/

/*
------------------------------------------------------------------------------
calc_chip_vrun

Returns Vrun in mV.
*/

unsigned long
calc_chip_vrun(void)
{
	unsigned long avs_version;
	int offset;
	unsigned long bin;
	int voltage = 0;

	avs_version = readl(SYSCON + 0x4d8);

	if (127 < avs_version)
		offset = 0;
	else
		/*
		  When the offset table is available, read it.
		*/
		offset = 0;

	/* Make sure any offset is between -100 and 100. */
	if (-100 > offset || 100 < offset)
		offset = 0;

	/* Get the bin; slow, medium, or fast. */
	bin = readl(SYSCON + 0x4dc);

	switch (bin) {
	case 1:
		/* slow bin */
		voltage = readl(SYSCON + 0x4c0);
		break;
	case 2:
		/* fast bin */
		voltage = readl(SYSCON + 0x4c4);
		break;
	case 3:
		/* medium bin */
		voltage = readl(SYSCON + 0x4c8);
		break;
	default:
		return V_SAFE;
		break;
	}

	if (200 <= voltage) {
		puts("** Voltage Returned For Bin Is Out Of Range **\n");
		acp_failure(__FILE__, __func__, __LINE__);
	}

	voltage = 800 + voltage + offset;

	return voltage;
}

/*
------------------------------------------------------------------------------
set_vrm_to_vrun

The LSI implementation.  May be replaced by a board specific function.
*/

int __weak
set_vrm_to_vrun(unsigned long v_run)
{
	printf("To set the voltage to %lu mV, implement set_vrm_to_vrun().\n",
	       v_run);

	return 0;
}

/*
------------------------------------------------------------------------------
voltage_init
*/

int
voltage_init(void)
{
	if (0 != set_vrm_to_vrun(calc_chip_vrun()))
		return -1;

	return 0;
}
