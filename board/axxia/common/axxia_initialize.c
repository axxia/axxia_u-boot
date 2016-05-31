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
#include <serial.h>

/*
==============================================================================
==============================================================================
Local
==============================================================================
==============================================================================
*/

unsigned *phyRegs;

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
	int rc;

	/*
	  ===============
	  Read Parameters
	  ===============
	*/

	rc = read_parameters();

#if !defined(CONFIG_AXXIA_SIM)
	if (0 != rc)
		acp_failure(__FILE__, __FUNCTION__, __LINE__);
#else
	/*
	  For now, in simulation, don't require a parameter file.  If
	  there is no parameter file, simply return success.
	*/

	if (0 != rc)
		return 0;
#endif

	/*
	  =======
	  Voltage
	  =======
	*/

#if !defined(CONFIG_AXXIA_EMU)
	if (0 != (global->flags & PARAMETERS_GLOBAL_SET_VOLTAGE))
		if (0 != voltage_init())
			acp_failure(__FILE__, __FUNCTION__, __LINE__);
#endif

	/*
	  ======
	  Clocks
	  ======
	*/

#if !defined(CONFIG_AXXIA_EMU)
	if (0 != (global->flags & PARAMETERS_GLOBAL_SET_CLOCKS))
		if (0 != clocks_init())
			acp_failure(__FILE__, __FUNCTION__, __LINE__);
#endif

	serial_initialize();
	serial_init();
	(void)sysmem_size();

	/*
	  =============
	  System Memory
	  =============
	*/

#ifndef SYSCACHE_ONLY_MODE
#if !defined(CONFIG_AXXIA_SIM)	/* TODO: Get this working in simulation */
	extern void __asm_disable_l3_cache(void);
	extern void __asm_enable_l3_cache(void);

	if ((0 != (global->flags & PARAMETERS_GLOBAL_SET_SMEM)) &&
	    (0 == sysmem->ddrRecovery)) {
		ncr_tracer_enable();

		if (0 != sysmem_init())
			acp_failure(__FILE__, __FUNCTION__, __LINE__);

		ncr_tracer_disable();
	}
#endif
#endif

	/*
	  ===========
	  Tree Memory
	  ===========
	*/

#if !defined(CONFIG_AXXIA_EMU)
	if ((0 != (global->flags & PARAMETERS_GLOBAL_SET_CMEM))) {
		ncr_tracer_enable();

		if (0 != cmem_init())
			acp_failure(__FILE__, __FUNCTION__, __LINE__);

		ncr_tracer_disable();
	}
#endif

	/*
	  =========
	  PCIe/SRIO
	  =========
	*/

#if !defined(CONFIG_AXXIA_EMU) && !defined(CONFIG_AXXIA_SIM)
#if 0
	if (0 != (global->flags & PARAMETERS_GLOBAL_SET_PEI))
		if (0 != pciesrio_init(pciesrio->control))
			acp_failure(__FILE__, __FUNCTION__, __LINE__);
#endif
#endif

	return 0;
}
