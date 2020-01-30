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
#include "ncp_sysmem_ext.h"

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
ncp_st_t
ncp_elm_init(ncp_dev_hdl_t, ncp_sm_parms_t *);

void dickens_init(void);

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

#if !defined(CONFIG_TARGET_EMULATION)
	if (0 != (global->flags & PARAMETERS_GLOBAL_SET_VOLTAGE))
		if (0 != voltage_init())
			acp_failure(__FILE__, __FUNCTION__, __LINE__);
#endif

	/*
	  ======
	  Clocks
	  ======
	*/

#if !defined(CONFIG_TARGET_EMULATION)
	if (0 != (global->flags & PARAMETERS_GLOBAL_SET_CLOCKS)) {
		int skip_ddr_plls = 0;

		if (cold != get_ddr_init_type())
			skip_ddr_plls = 1;

		if (0 != clocks_init(skip_ddr_plls))
			acp_failure(__FILE__, __FUNCTION__, __LINE__);
	}
#endif

	serial_initialize();
	serial_init();


	/*
	  ===========
	  Tree Memory
	  ===========
	*/


#if !defined(CONFIG_AXXIA_EMU)
    cmem->totalSize = 0;
	if ((0 != (global->flags & PARAMETERS_GLOBAL_SET_CMEM))) {
#if !defined(TRACE_PEI_ACCESSES)
		ncr_tracer_enable();
#endif

		if (0 != cmem_init())
			acp_failure(__FILE__, __FUNCTION__, __LINE__);

#if !defined(TRACE_PEI_ACCESSES)
		ncr_tracer_disable();
#endif
	}
#endif

	/*
	  =============
	  System Memory
	  =============
	*/

	sysmem->totalSize = 0;

	(void)sysmem_size();

#ifdef CONFIG_MEMORY_RETENTION
#ifdef CONFIG_AXXIA_ANY_XLF
	if (0 != (global->flags & PARAMETERS_GLOBAL_ENABLE_RETENTION) &&
	    0 != (global->flags & PARAMETERS_GLOBAL_ENABLE_SELF_REFRESH)) {
		printf("DDR Retention, with Self Refresh, Enabled\n");
	} else if (0 != (global->flags & PARAMETERS_GLOBAL_ENABLE_RETENTION)) {
		printf("DDR Retention, without Self Refresh, Enabled\n");
	} else {
		printf("DDR Retention Disabled\n");
	}
#else  /* CONFIG_AXXIA_ANY_XLF */
	if (0 != (global->flags & PARAMETERS_GLOBAL_ENABLE_RETENTION))
		printf("DDR Retention Enabled\n");
	else
		printf("DDR Retention Disabled\n");
#endif /* CONFIG_AXXIA_ANY_XLF */
#else  /* CONFIG_MEMORY_RETENTION */
	printf("DDR Retention Disabled\n");
#endif	/* CONFIG_MEMORY_RETENTION */

#if !defined(SYSCACHE_ONLY_MODE) && !defined(CONFIG_TARGET_EMULATION)
	if (0 != (global->flags & PARAMETERS_GLOBAL_SET_SMEM)) {
		printf("DDR Init Type: %s\n",
		       get_ddr_init_name(get_ddr_init_type()));

#ifdef CONFIG_AXXIA_ANY_XLF
		if (planned == get_ddr_init_type() ||
		    unplanned == get_ddr_init_type()) {
			/*
			  In either sort of retention reset,
			  reset_chip_wo_sm in reset_wo_sm needs to be
			  clear.
			*/
			writel(0xab, (SYSCON + 0x2000));
			writel(0, (SYSCON + 0x204c));
			writel(0, (SYSCON + 0x2000));
		}
#endif	/* CONFIG_AXXIA_ANY_XLF */

		if (planned == get_ddr_init_type()) {
			ncp_uint32_t version_save;

			printf("initializing ELMs for ddrRecovery\n");

			/* Initialize Dickens and the ELMs */
			version_save = sysmem->version;
#if defined(CONFIG_AXXIA_56XX) || defined(CONFIG_AXXIA_56XX_SIM)
			sysmem->version = NCP_CHIP_ACP56xx;
#elif defined(CONFIG_AXXIA_XLF) || defined(CONFIG_AXXIA_XLF_SIM)
			sysmem->version = NCP_CHIP_ACPXLF;
#else
#error "Invalid Chip Type!"
#endif

			dickens_init();

			rc = ncp_elm_init(NULL, sysmem);

			sysmem->version = version_save;

			if (NCP_ST_SUCCESS != rc) {
				printf("Initializing ELMs Failed!\n");

				return -1;
			}
		} else {
#if !defined(TRACE_PEI_ACCESSES)
			ncr_tracer_enable();
#endif

			if (0 != sysmem_init())
				acp_failure(__FILE__, __FUNCTION__, __LINE__);

#if !defined(TRACE_PEI_ACCESSES)
			ncr_tracer_disable();
#endif
		}

#ifdef CONFIG_MEMORY_RETENTION
#ifdef CONFIG_AXXIA_ANY_XLF
		/*
		  If memory retention is enabled, set reset_chip_wo_sm
		  in reset_wo_sm.
		*/
		writel(0xab, (SYSCON + 0x2000));
		writel(1, (SYSCON + 0x204c));
		writel(0, (SYSCON + 0x2000));
#endif	/* CONFIG_AXXIA_ANY_XLF */
#endif	/* CONFIG_MEMORY_RETENTION */
	}
#elif defined(CONFIG_TARGET_EMULATION)
	if ((0 != (global->flags & PARAMETERS_GLOBAL_SET_SMEM)) &&
            (cold == get_ddr_init_type())) {
		ncr_tracer_enable();

                if (0 != sysmem_init())
                        acp_failure(__FILE__, __FUNCTION__, __LINE__);

                ncr_tracer_disable();
        }
#endif

	return 0;
}
