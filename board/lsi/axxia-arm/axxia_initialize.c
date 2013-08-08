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

#include <common.h>

#include "../common/ncp_sysmem_ext.h"
#include "../common/ncp_sysmem_lsiphy.h"

/*
  ===============================================================================
  ===============================================================================
  Local
  ===============================================================================
  ===============================================================================
*/

unsigned long sysmem_size = 1;
unsigned long reset_enabled = 1;
unsigned long ncp_sm_phy_reg_restore = 1;
unsigned long ncp_sm_phy_reg_dump = 1;
                                                                                
#if defined (CONFIG_AXXIA_55XX_EMU)
#include "sysmem_emulation.c"
#else                                                                           
#include "../common/sysmem_asic_common.c"
#include "../common/ncp_sysmem_init_lsiphy.c"
#include "../common/ncp_elm.c"
#endif

/*
  ==============================================================================
  ==============================================================================
  Public Interface
  ==============================================================================
  ==============================================================================
*/

/*
  ------------------------------------------------------------------------------
  axxia_initialize
*/

int
axxia_initialize(void)
{
	int returnCode = 0;
	int i;

	if (0 != read_parameters())
		acp_failure(__FILE__, __FUNCTION__, __LINE__);

	/*
	  =======
	  Voltage
	  =======
	*/

#ifdef CONFIG_AXXIA_55XX
#ifndef CONFIG_AXXIA_EMU
	if (0 == (global->flags & PARAMETERS_GLOBAL_IGNORE_VOLTAGE))
		if (0 != (returnCode = voltage_init()))
			goto acp_init_return;
#endif
#endif

	/*
	  =========
	  PCIe/SRIO
	  =========
	*/

#ifdef CONFIG_AXXIA_55XX
#ifndef CONFIG_AXXIA_EMU
	if (0 == (global->flags & PARAMETERS_GLOBAL_IGNORE_PCIESRIO))
		if (0 != (returnCode = pciesrio_init()))
			goto acp_init_return;
#endif
#endif

	/*
	  =============
	  System Memory
	  =============
	*/

	if (0 == (global->flags & PARAMETERS_GLOBAL_IGNORE_SYSMEM))
		if (0 != (returnCode = sysmem_init()))
			goto acp_init_return;

 acp_init_return:

	return returnCode;
}
