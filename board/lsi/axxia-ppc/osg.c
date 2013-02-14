/*
 * osg.c
 *
 * Handles the partitioning of resources among OS groups.
 * 
 * Copyright (C) 2010 LSI Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

/*#define LSI_DEBUG*/
#define LSI_WARN
#include <config.h>
#ifdef CONFIG_ACP3
#include <common.h>
#include <exports.h>

DECLARE_GLOBAL_DATA_PTR;

/*
  ==============================================================================
  ==============================================================================
  Private
  ==============================================================================
  ==============================================================================
*/

typedef struct {
	acp_osg_spintable_state_t spintable_state;
	acp_osg_core_state_t core_state;
	int os_group;
} acp_osg_core_t;

typedef struct {
	unsigned long flags;
	unsigned long base;
	unsigned long size;
	void (*os)(unsigned long, unsigned long, unsigned long,
		   unsigned long, unsigned long);
	unsigned long arguments[5];
} acp_osg_group_t;

#define BOOT_MASK     0xf
#define BOOT_SHIFT    0
#define BOOT(flags)   (((flags) & BOOT_MASK) >> BOOT_SHIFT)

#define CORES_MASK    0xf0
#define CORES_SHIFT   4
#define CORES(flags)  (((flags) & CORES_MASK) >> CORES_SHIFT)

#define UART0_MASK    0x100
#define UART0_SHIFT   8
#define UART0(flags)  (((flags) & UART0_MASK) >> UART0_SHIFT)

#define UART1_MASK    0x200
#define UART1_SHIFT   9
#define UART1(flags)  (((flags) & UART1_MASK) >> UART1_SHIFT)

#define NAND_MASK     0x400
#define NAND_SHIFT    10
#define NAND(flags)   (((flags) & NAND_MASK) >> NAND_SHIFT)

#define NET_MASK      0x800
#define NET_SHIFT     11
#define NET(flags)    (((flags) & NET_MASK) >> NET_SHIFT)

#define PCIE0_MASK    0x1000
#define PCIE0_SHIFT   12
#define PCIE0(flags)  (((flags) & PCIE0_MASK) >> PCIE0_SHIFT)

#define PCIE1_MASK    0x2000
#define PCIE1_SHIFT   13
#define PCIE1(flags)  (((flags) & PCIE1_MASK) >> PCIE1_SHIFT)

#define PCIE2_MASK    0x4000
#define PCIE2_SHIFT   14
#define PCIE2(flags)  (((flags) & PCIE2_MASK) >> PCIE2_SHIFT)

#define SRIO_MASK     0x8000
#define SRIO_SHIFT    15
#define SRIO(flags)   (((flags) & SRIO_MASK) >> SRIO_SHIFT)

#define USB_MASK      0x10000
#define USB_SHIFT     16
#define USB(flags)    (((flags) & USB_MASK) >> USB_SHIFT)

#define PLX_MASK      0x20000
#define PLX_SHIFT     17
#define PLX(flags)    (((flags) & PLX_MASK) >> PLX_SHIFT)

#define SBB_MASK      0x40000
#define SBB_SHIFT     18
#define SBB(flags)    (((flags) & SBB_MASK) >> SBB_SHIFT)

static acp_osg_core_t *acp_osg_cores[] = {
	(void *)&__acp_osg_cores + (0 * sizeof(acp_osg_core_t)),
	(void *)&__acp_osg_cores + (1 * sizeof(acp_osg_core_t)),
	(void *)&__acp_osg_cores + (2 * sizeof(acp_osg_core_t)),
	(void *)&__acp_osg_cores + (3 * sizeof(acp_osg_core_t))
};

static acp_osg_group_t *acp_osg_groups[] = {
	(void *)&__acp_osg_groups + (0 * sizeof(acp_osg_group_t)),
	(void *)&__acp_osg_groups + (1 * sizeof(acp_osg_group_t)),
	(void *)&__acp_osg_groups + (2 * sizeof(acp_osg_group_t)),
	(void *)&__acp_osg_groups + (3 * sizeof(acp_osg_group_t))
};

static int current_group = 0;

/*
  ------------------------------------------------------------------------------
  acp_osg_flush
*/

static void
acp_osg_flush(void)
{
	/* Flush the cores, groups, and system sections. */
	flush_cache((unsigned long)&__acp_osg_cores, 0x300);
}

/*
  ==============================================================================
  ==============================================================================
  Public
  ==============================================================================
  ==============================================================================
*/

/*
  ------------------------------------------------------------------------------
  acp_osg_get_spintable_state
*/

acp_osg_spintable_state_t
acp_osg_get_spintable_state(int core)
{
	return acp_osg_cores[core]->spintable_state;
}

/*
  ------------------------------------------------------------------------------
  acp_osg_set_spintable_state
*/

void
acp_osg_set_spintable_state(int core, acp_osg_spintable_state_t state)
{
	acp_osg_cores[core]->spintable_state = state;
	acp_osg_flush();
}

/*
  ------------------------------------------------------------------------------
  acp_osg_get_core_state
*/

acp_osg_core_state_t
acp_osg_get_core_state(int core)
{
	return acp_osg_cores[core]->core_state;
}

/*
  ------------------------------------------------------------------------------
  acp_osg_set_core_state
*/

void
acp_osg_set_core_state(int core, acp_osg_core_state_t state)
{
	acp_osg_cores[core]->core_state = state;
	acp_osg_flush();
}

/*
  ------------------------------------------------------------------------------
  acp_osg_readenv

  Initializes the global acp_os_groups arrays based on the
  environment, and verifies that the values are reasonable.

  NOTE: Should only be called ONCE by core 0 during a cold start.
*/

int
acp_osg_readenv(void)
{
	int core;
	int group;
	int save_env = 0;
	char *osmemory_string;
	unsigned long osmemory_value;
	char buffer[40];

	for (group = 0; group < ACP_MAX_OS_GROUPS; ++group) {
		memset(acp_osg_cores[group], 0, sizeof(acp_osg_core_t));
		acp_osg_groups[group] =
			(void *)&__acp_osg_groups +
			(group * sizeof(acp_osg_group_t));
		memset(acp_osg_groups[group], 0, sizeof(acp_osg_group_t));
	}

	osmemory_string = getenv("osmemory");

	if ((char *)0 == osmemory_string) {
		osmemory_value = OS_MEMORY_DEFAULT;
		sprintf(buffer, "0x%lx", osmemory_value);
		setenv("osmemory", buffer);
		save_env = 1;
	} else {
		osmemory_value = simple_strtoul(osmemory_string, NULL, 0);
	}

	if (get_sysmem_size() < osmemory_value) {
		printf("osmemory is larger than system memory, adjusting.\n");
		osmemory_value = get_sysmem_size();
		sprintf(buffer, "0x%lx", osmemory_value);
		setenv("osmemory", buffer);
		save_env = 1;
	}

	/* Update the scratch register for the RTE. */
#ifndef ACP_ISS
	ncr_write32(NCP_REGION_ID(0x22, 0xff), 0x20, osmemory_value);
#endif

	for (group = 0; group < ACP_MAX_OS_GROUPS; ++group) {
		char env_name[20];
		char *env_value;
		char *token;
		char *string;
		char *string_address;
		acp_osg_group_t *os_group = acp_osg_groups[group];

		/* Read the environment variable. */
		sprintf(env_name, "osgroup%d", group);
		env_value = getenv(env_name);

		if ((char *)0 == env_value) {
			WARN_PRINT("%s doesn't exist, creating it.\n", env_name);
			if (0 == group) {
				setenv(env_name, OS_GROUP0_DEFAULT);
			} else {
				setenv(env_name, "0:0:0");
			}
			save_env = 1;
			env_value = getenv(env_name);
		}

		DEBUG_PRINT("%s : %s\n", env_name, env_value);
		string = malloc(strlen(env_value));
		string_address = string;
		strcpy(string, env_value);

		/* Fill in the structure. */
		token = strsep(&string, ":");
		os_group->flags = simple_strtoul(token, NULL, 0);

		if (0 != BOOT(os_group->flags)) {
			token = strsep(&string, ":");
			os_group->base =
				simple_strtoul(token, NULL, 0);
			token = strsep(&string, ":");
			os_group->size = simple_strtoul(token, NULL, 0);

			if ((os_group->base + os_group->size) > osmemory_value) {
				WARN_PRINT("%s won't fit within osmemory.\n",
					   env_name);
				if (0 == group) {
					setenv(env_name, OS_GROUP0_DEFAULT);
				} else {
					setenv(env_name, "0:0:0");
				}
				save_env = 1;
				env_value = getenv(env_name);
			}
		}

		free(string_address);

		DEBUG_PRINT("%s : 0x%08x boot=%d cores=0x%x "
			    "base=0x%x size=0x%x\n",
			    env_name, os_group->flags,
			    BOOT(os_group->flags), CORES(os_group->flags),
			    os_group->base, os_group->size);
	}

	for (core = 0; core < ACP_MAX_CORES; ++core) {
		int group;
		int group_set = 0;
		acp_osg_core_t *osg_core = acp_osg_cores[core];

		/* Set the initial values for the cores. */
		osg_core->spintable_state = ACP_OSG_SPINTABLE_NOTAVAIL;
		osg_core->core_state = ACP_OSG_CORE_STATE_UNKNOWN;
		osg_core->os_group = -1;

		for (group = 0; group < ACP_MAX_OS_GROUPS; ++group) {
			acp_osg_group_t *osg_group = acp_osg_groups[group];

			DEBUG_PRINT("group=%d flags=0x%x CORES=0x%x core=%d\n",
				    group, osg_group->flags,
				    CORES(osg_group->flags), core);
			
			if (0 != ((1 << core) & CORES(osg_group->flags))) {
				if (0 != group_set) {
					printf("Core %d is already part of a "
					       "group!\n", group);
				} else {
					osg_core->os_group = group;
					group_set = 1;
				}
			}
		}

		DEBUG_PRINT("group %d : 0x%x 0x%x %d\n",
			    group, osg_core->spintable_state,
			    osg_core->core_state, osg_core->os_group);
	}

	acp_osg_flush();

	return save_env;
}

/*
  -------------------------------------------------------------------------------
  acp_osg_group_get_res
*/

unsigned long
acp_osg_group_get_res(int group, acp_osg_group_res_t res)
{
	unsigned long rv = 0;
	acp_osg_group_t *acp_osg_group = acp_osg_groups[group];

	switch(res) {
	case ACP_OS_BOOT_CORE:
		rv = BOOT(acp_osg_group->flags);
		break;
	case ACP_OS_CORES:
		rv = CORES(acp_osg_group->flags);
		break;
	case ACP_OS_BASE:
		rv = acp_osg_groups[group]->base;
		break;
	case ACP_OS_SIZE:
		rv = acp_osg_groups[group]->size;
		break;
	case ACP_OS_UART0:
		rv = UART0(acp_osg_group->flags);
		break;
	case ACP_OS_UART1:
		rv = UART1(acp_osg_group->flags);
		break;
	case ACP_OS_NAND:
		rv = NAND(acp_osg_group->flags);
		break;
	case ACP_OS_FEMAC:
		rv = NET(acp_osg_group->flags);
		break;
	case ACP_OS_PCIE0:
		rv = PCIE0(acp_osg_group->flags);
		break;
	case ACP_OS_PCIE1:
		rv = PCIE1(acp_osg_group->flags);
		break;
#ifndef ACP_25xx
	case ACP_OS_PCIE2:
		rv = PCIE2(acp_osg_group->flags);
		break;
#endif
	case ACP_OS_SRIO:
		rv = SRIO(acp_osg_group->flags);
		break;
	case ACP_OS_USB:
		rv = USB(acp_osg_group->flags);
		break;
	case ACP_OS_PLX:
		rv = PLX(acp_osg_group->flags);
		break;
	case ACP_OS_SBB:
		rv = SBB(acp_osg_group->flags);
		break;
	case ACP_OS_FDT:
		rv = (unsigned long)get_acp_fdt(group);
		break;
	default:
		break;
	}

	return rv;
}

/*
  -------------------------------------------------------------------------------
  acp_osg_group_set_res
*/

void
acp_osg_group_set_res(int group, acp_osg_group_res_t res, unsigned long value)
{
	switch(res) {
	case ACP_OS_BOOT_CORE:
		acp_osg_groups[group]->flags &= ~BOOT_MASK;
		acp_osg_groups[group]->flags |=
			((value << BOOT_SHIFT) & BOOT_MASK);
		break;
	case ACP_OS_CORES:
		acp_osg_groups[group]->flags &= ~CORES_MASK;
		acp_osg_groups[group]->flags |=
			((value << CORES_SHIFT) & CORES_MASK);
		break;
	case ACP_OS_BASE:
		acp_osg_groups[group]->base = value;
		break;
	case ACP_OS_SIZE:
		acp_osg_groups[group]->size = value;
		break;
	case ACP_OS_UART0:
		acp_osg_groups[group]->flags &= ~UART0_MASK;
		acp_osg_groups[group]->flags |=
			((value << UART0_SHIFT) & UART0_MASK);
		break;
	case ACP_OS_UART1:
		acp_osg_groups[group]->flags &= ~UART1_MASK;
		acp_osg_groups[group]->flags |=
			((value << UART1_SHIFT) & UART1_MASK);
		break;
	case ACP_OS_NAND:
		acp_osg_groups[group]->flags &= ~NAND_MASK;
		acp_osg_groups[group]->flags |=
			((value << NAND_SHIFT) & NAND_MASK);
		break;
	case ACP_OS_FEMAC:
		acp_osg_groups[group]->flags &= ~NET_MASK;
		acp_osg_groups[group]->flags |=
			((value << NET_SHIFT) & NET_MASK);
		break;
	case ACP_OS_PCIE0:
		acp_osg_groups[group]->flags &= ~PCIE0_MASK;
		acp_osg_groups[group]->flags |=
			((value << PCIE0_SHIFT) & PCIE0_MASK);
		break;
	case ACP_OS_PCIE1:
		acp_osg_groups[group]->flags &= ~PCIE1_MASK;
		acp_osg_groups[group]->flags |=
			((value << PCIE1_SHIFT) & PCIE1_MASK);
		break;
#ifndef ACP_25xx
	case ACP_OS_PCIE2:
		acp_osg_groups[group]->flags &= ~PCIE2_MASK;
		acp_osg_groups[group]->flags |=
			((value << PCIE2_SHIFT) & PCIE2_MASK);
		break;
#endif
	case ACP_OS_SRIO:
		acp_osg_groups[group]->flags &= ~SRIO_MASK;
		acp_osg_groups[group]->flags |=
			((value << SRIO_SHIFT) & SRIO_MASK);
		break;
	case ACP_OS_USB:
		acp_osg_groups[group]->flags &= ~USB_MASK;
		acp_osg_groups[group]->flags |=
			((value << USB_SHIFT) & USB_MASK);
		break;
	case ACP_OS_PLX:
		acp_osg_groups[group]->flags &= ~PLX_MASK;
		acp_osg_groups[group]->flags |=
			((value << PLX_SHIFT) & PLX_MASK);
		break;
	case ACP_OS_SBB:
		acp_osg_groups[group]->flags &= ~SBB_MASK;
		acp_osg_groups[group]->flags |=
			((value << SBB_SHIFT) & SBB_MASK);
		break;
	case ACP_OS_FDT:
		printf("The address of the device tree cannot be changed.\n");
		break;
	}

	acp_osg_flush();

	return;
}

/*
  ------------------------------------------------------------------------------
  acp_osg_get_group
*/

int
acp_osg_get_group(int core)
{
	int group;

	for (group = 0; group < ACP_NR_CORES; ++group) {
		if (0 != ((1 << core) & CORES(acp_osg_groups[group]->flags)))
			return group;
	}

	return -1;
}

/*
  ------------------------------------------------------------------------------
  acp_osg_is_group_boot_core
*/

int
acp_osg_is_group_boot_core(int group)
{
	unsigned long pir_value;

	__asm__ __volatile__ ("mfspr %0,0x11e" : "=r" (pir_value));

	return ((1 << pir_value) == BOOT(acp_osg_groups[group]->flags));
}

/*
  ------------------------------------------------------------------------------
  acp_osg_is_boot_core
*/

int
acp_osg_is_boot_core(int core)
{
	if (SYSTEM_BOOTCORE == core)
		return 1;

#if defined(ACP_X2V1) || defined(ACP_25xx)
	if ((0 != ((1 << core) & BOOT(acp_osg_groups[0]->flags))) ||
	    (0 != ((1 << core) & BOOT(acp_osg_groups[1]->flags)))) {
		return 1;
	}
#else
	if ((0 != ((1 << core) & BOOT(acp_osg_groups[0]->flags))) ||
	    (0 != ((1 << core) & BOOT(acp_osg_groups[1]->flags))) ||
	    (0 != ((1 << core) & BOOT(acp_osg_groups[2]->flags))) ||
	    (0 != ((1 << core) & BOOT(acp_osg_groups[3]->flags)))) {
		return 1;
	}
#endif

	return 0;
}

/*
  ------------------------------------------------------------------------------
  acp_osg_set_os
*/

int
acp_osg_set_os(int group,
	       void (*os)(unsigned long, unsigned long, unsigned long,
			  unsigned long, unsigned long),
	       unsigned long arg0, unsigned long arg1, unsigned long arg2,
	       unsigned long arg3, unsigned long arg4)
{
	acp_osg_groups[group]->os = os;
	acp_osg_groups[group]->arguments[0] = arg0;
	acp_osg_groups[group]->arguments[1] = arg1;
	acp_osg_groups[group]->arguments[2] = arg2;
	acp_osg_groups[group]->arguments[3] = arg3;
	acp_osg_groups[group]->arguments[4] = arg4;

	return 0;
}

/*
  ------------------------------------------------------------------------------
  acp_osg_jump_to_os
*/

int
acp_osg_jump_to_os(int group)
{
	void (*os)(unsigned long, unsigned long, unsigned long,
		   unsigned long, unsigned long);

	os = acp_osg_groups[group]->os;

	/* Release the stage 3 lock. */
	acp_unlock_stage3();

	/* Clear the MSR */
	__asm__ __volatile__ ("lis            6,0\n"   \
			      "mtmsr          6");

	/* Jump to the OS. */
	(*os)(acp_osg_groups[group]->arguments[0],
	      acp_osg_groups[group]->arguments[1],
	      acp_osg_groups[group]->arguments[2],
	      acp_osg_groups[group]->arguments[3],
	      acp_osg_groups[group]->arguments[4]);

	acp_failure(__FILE__, __FUNCTION__, __LINE__);

	return 0;
}

/*
  ------------------------------------------------------------------------------
  acp_osg_get_current
*/

int
acp_osg_get_current(void)
{
	return current_group;
}

/*
  ------------------------------------------------------------------------------
  acp_osg_set_current
*/

void
acp_osg_set_current(int group)
{
	current_group = group;
}

/*
  ------------------------------------------------------------------------------
  acp_osg_dump
*/

int
acp_osg_dump(int group)
{
	printf("OS Group %d\n"
	       "  flags: 0x%08lx\n"
	       "   base: 0x%08lx\n"
	       "   size: 0x%08lx\n"
	       "     os: 0x%08lx(0x%08lx, 0x%08lx, 0x%08lx, 0x%08lx, 0x%08lx)\n"
	       "    fdt: 0x%08lx\n",
	       group, acp_osg_groups[group]->flags, acp_osg_groups[group]->base,
	       acp_osg_groups[group]->size,
	       (unsigned long)acp_osg_groups[group]->os,
	       acp_osg_groups[group]->arguments[0],
	       acp_osg_groups[group]->arguments[1],
	       acp_osg_groups[group]->arguments[2],
	       acp_osg_groups[group]->arguments[3],
	       acp_osg_groups[group]->arguments[4],
	       (unsigned long)get_acp_fdt(group));

	return 0;
}

/*
  ------------------------------------------------------------------------------
  acp_osg_update_dt
*/

static int
acp_osg_update_dt(void *input, int group)
{
	int rc = -1;
	struct fdt_header *dt = input;
	char *core[] = {
		"/cpus/cpu@0",
		"/cpus/cpu@1",
		"/cpus/cpu@2",
		"/cpus/cpu@3"
	};
	unsigned long ppc_clk;
	unsigned long clk_per;
	int i;
	unsigned long value;
	unsigned long group_base_address;

	/*
	  ============================================================
	  Remove "memreserve" if the base address is not 0.
	*/

	group_base_address =
	  (acp_osg_group_get_res(group, ACP_OS_BASE) * 1024 * 1024);

	if (0 != group_base_address) {
		rc = fdt_del_mem_rsv(dt, 0);
		rc |= fdt_add_mem_rsv(dt,
				      (unsigned long long)group_base_address,
				      0x400000ULL);

		if (0 != rc) {
			printf("Error Updating Reserved Memory 0\n");
			return -1;
		}
	}

	/*
	  ============================================================
	  Set "dcr-parent" to point to the boot core.
	*/

	value = acp_osg_group_get_res(group, ACP_OS_BOOT_CORE);
	rc = fdt_find_and_setprop(dt, "/", "dcr-parent",
				  (void *)&value, sizeof(unsigned long), 1);

	if (0 != rc) {
		printf("Error setting dcr-parent for group %d.\n", group);
		return -1;
	}

	/*
	  ============================================================
	  Update the clocks, PPC and peripheral.
	*/
	
	if ((0 != acp_clock_get(clock_ppc, &ppc_clk)) ||
	    (0 != acp_clock_get(clock_peripheral, &clk_per))) {
		return -1;
	}

	/* Internally, clocks are stored in KHz.  Convert to Hz. */
	ppc_clk *= 1000;
	clk_per *= 1000;

	for (i = 0; i < ACP_NR_CORES; ++i) {
		rc = fdt_find_and_setprop(dt, core[i],
					  "clock-frequency",
					  (void *)&ppc_clk,
					  sizeof(unsigned long), 1);
		rc |= fdt_find_and_setprop(dt, core[i],
					   "timebase-frequency",
					   (void *)&ppc_clk,
					   sizeof(unsigned long), 1);

		if (0 != rc) {
			printf("Error Setting Clocks for %s\n", core[i]);
			return -1;
		}
	}

	rc = fdt_find_and_setprop(dt, "/plb/opb/serial@00404000",
				  "clock-frequency",
				  (void *)&clk_per, sizeof(unsigned long), 1);
	rc |= fdt_find_and_setprop(dt, "/plb/opb/serial@00405000",
				   "clock-frequency",
				   (void *)&clk_per, sizeof(unsigned long), 1);

	if (0 != rc) {
		printf("Error setting up the UARTs\n");
		return -1;
	}

	/*
	  ============================================================
	  Update the peripherals.
	*/

	if (0 != acp_osg_group_get_res(group, ACP_OS_UART0)) {
		value = 1;
		rc = fdt_find_and_setprop(dt, "/plb/opb/serial@00404000",
					  "enabled", (void *)&value,
					  sizeof(unsigned long), 1);
		rc |= fdt_find_and_setprop(dt, "/plb/opb/serial@00404000",
					   "current-speed",
					   (void *)&gd->baudrate,
					   sizeof(unsigned long), 1);

		if (0 != rc)
			return -1;
	}

	if (0 != acp_osg_group_get_res(group, ACP_OS_UART1)) {
		value = 1;
		rc = fdt_find_and_setprop(dt, "/plb/opb/serial@00405000",
					  "enabled", (void *)&value,
					  sizeof(unsigned long), 1);
		rc |= fdt_find_and_setprop(dt, "/plb/opb/serial@00405000",
					   "current-speed",
					   (void *)&gd->baudrate,
					   sizeof(unsigned long), 1);

		if (0 != rc)
			return -1;
	}

	if (0 != acp_osg_group_get_res(group, ACP_OS_NAND)) {
		value = 1;
		rc = fdt_find_and_setprop(dt, "/plb/opb/nand@00440000",
					  "enabled", (void *)&value,
					  sizeof(unsigned long), 1);

		if (0 != rc)
			return -1;
	}

	if (0 != acp_osg_group_get_res(group, ACP_OS_FEMAC)) {
		int ethaddr_size;
		char ethaddr_string[18];
		unsigned char ethaddr[6];
		char *string;
		char *endp;

		value = 1;
		rc = fdt_find_and_setprop(dt, "/plb/opb/femac@00480000",
					  "enabled", (void *)&value,
					  sizeof(unsigned long), 1);

		if (0 != rc)
			return -1;

		ethaddr_size = getenv_r("ethaddr",
					ethaddr_string, sizeof(ethaddr_string));

		if (18 > ethaddr_size) {
			printf("Error Getting ethaddr.\n");
			return -1;
		}

		string = ethaddr_string;

		for (i = 0; i < 6; ++i) {
			ethaddr[i] = simple_strtoul(string, &endp, 16);

			if (endp == string) {
				/* No digits available. */
				printf("Error parsing ethaddr.\n");
				return -1;
			}

			if (0 != * endp)
				string = (endp + 1);
		}

		rc = fdt_find_and_setprop(dt, "/plb/opb/femac@00480000",
					  "mac-address", (void *)ethaddr,
					  (sizeof(unsigned char) * 6), 1);

		if (0 != rc) {
			printf("Error setting up the FEMAC.\n");
			return -1;
		}
	}

	if (0 != acp_osg_group_get_res(group, ACP_OS_PCIE0)) {
		int nodeoffset;
		const struct fdt_property *property;
		unsigned long *dma_ranges;

		value = 1;
		rc = fdt_find_and_setprop(dt, "/pciex@f00c0000",
					  "enabled", (void *)&value,
					  sizeof(unsigned long), 1);

		if (0 != rc)
			return -1;

		if (0 > (nodeoffset = fdt_path_offset(dt, "/pciex@f00c0000")))
			return -1;

		if (NULL == (property = fdt_get_property(dt, nodeoffset,
							 "dma-ranges", NULL)))
			return -1;

		dma_ranges = (unsigned long *)property->data;
		dma_ranges[6] = (acp_osg_group_get_res(group, ACP_OS_SIZE) *
				 1024 * 1024);

		rc = fdt_find_and_setprop(dt, "/pciex@f00c0000",
					  "dma-ranges", (void *)dma_ranges,
					  (sizeof(unsigned long) * 7), 1);

		if (0 != rc)
			return -1;

		/*
		  If plx is set to set, enable it in the device tree.
		*/

		if (0 != acp_osg_group_get_res(group, ACP_OS_PLX)) {
			value = 1;

			rc = fdt_find_and_setprop(dt, "/pciex@f00c0000",
						  "plx", (void *)&value,
						  sizeof(unsigned long), 1);

			if (0 != rc)
				return -1;
		}
	}

	if (0 != acp_osg_group_get_res(group, ACP_OS_PCIE1)) {
		int nodeoffset;
		const struct fdt_property *property;
		unsigned long *dma_ranges;

		value = 1;
		rc = fdt_find_and_setprop(dt, "/pciex@f00c8000",
					  "enabled", (void *)&value,
					  sizeof(unsigned long), 1);

		if (0 != rc)
			return -1;

		if (0 > (nodeoffset = fdt_path_offset(dt, "/pciex@f00c8000")))
			return -1;

		if (NULL == (property = fdt_get_property(dt, nodeoffset,
							 "dma-ranges", NULL)))
			return -1;

		dma_ranges = (unsigned long *)property->data;
		dma_ranges[6] = (acp_osg_group_get_res(group, ACP_OS_SIZE) *
				 1024 * 1024);

		rc = fdt_find_and_setprop(dt, "/pciex@f00c8000",
					  "dma-ranges", (void *)dma_ranges,
					  (sizeof(unsigned long) * 7), 1);

		if (0 != rc)
			return -1;

		/*
		  If plx is set to set, enable it in the device tree.
		*/

		if (0 != acp_osg_group_get_res(group, ACP_OS_PLX)) {
			value = 1;

			rc = fdt_find_and_setprop(dt, "/pciex@f00c8000",
						  "plx", (void *)&value,
						  sizeof(unsigned long), 1);

			if (0 != rc)
				return -1;
		}
	}

#ifndef ACP_25xx

	if (0 != acp_osg_group_get_res(group, ACP_OS_PCIE2)) {
		int nodeoffset;
		const struct fdt_property *property;
		unsigned long *dma_ranges;

		value = 1;
		rc = fdt_find_and_setprop(dt, "/pciex@f00d0000",
					  "enabled", (void *)&value,
					  sizeof(unsigned long), 1);

		if (0 != rc)
			return -1;

		if (0 > (nodeoffset = fdt_path_offset(dt, "/pciex@f00d0000")))
			return -1;

		if (NULL == (property = fdt_get_property(dt, nodeoffset,
							 "dma-ranges", NULL)))
			return -1;

		dma_ranges = (unsigned long *)property->data;
		dma_ranges[6] = (acp_osg_group_get_res(group, ACP_OS_SIZE) *
				 1024 * 1024);

		rc = fdt_find_and_setprop(dt, "/pciex@f00d0000",
					  "dma-ranges", (void *)dma_ranges,
					  (sizeof(unsigned long) * 7), 1);

		if (0 != rc)
			return -1;

		/*
		  If plx is set to set, enable it in the device tree.
		*/

		if (0 != acp_osg_group_get_res(group, ACP_OS_PLX)) {
			value = 1;

			rc = fdt_find_and_setprop(dt, "/pciex@f00d0000",
						  "plx", (void *)&value,
						  sizeof(unsigned long), 1);

			if (0 != rc)
				return -1;
		}
	}

#endif

	if (0 != acp_osg_group_get_res(group, ACP_OS_SRIO)) {
		value = 1;
		rc = fdt_find_and_setprop(dt, "/rapidio@f0020000",
					  "enabled", (void *)&value,
					  sizeof(unsigned long), 1);

		if (0 != rc)
			return -1;
	}

	/* USB */
	if (0 != acp_osg_group_get_res(group, ACP_OS_USB)) {
		value = 1;
	} else {
		value = 0;
	}

	rc = fdt_find_and_setprop(dt, "/plb/opb/usb@004a4000",
				  "enabled", (void *)&value,
				  sizeof(unsigned long), 1);

	if (0 != rc)
		return -1;

#ifdef ACP_25xx
	/* SBB */
	if (0 != acp_osg_group_get_res(group, ACP_OS_SBB)) {
		value = 1;
	} else {
		value = 0;
	}

	rc = fdt_find_and_setprop(dt, "/plb/opb/sbb",
				  "enabled", (void *)&value,
				  sizeof(unsigned long), 1);

	if (0 != rc)
		return -1;
#endif

	return rc;
}

/*
  ------------------------------------------------------------------------------
  acp_osg_initialize
*/

int
acp_osg_initialize(void)
{
	struct fdt_header *dt;
	int group;

	/*
	  Check for invalid configurations.
	*/

	/*
	  Update each group's device tree individually.
	*/

	for (group = 0; group < ACP_NR_CORES; ++group) {
		dt = (struct fdt_header *)get_acp_fdt(group);

		if (0 != acp_osg_update_dt(dt, group)) {
			printf("Error Updating OS Group %d.\n", group);
			return -1;
		}
	}

	return 0;
}

/*
  ------------------------------------------------------------------------------
  acp_osg_map
*/

int
acp_osg_map(int group_index)
{
	unsigned long address;
	unsigned long size;
	unsigned long word0;
	unsigned long word1;
	unsigned long word2;
	unsigned long long temp;
	acp_osg_group_t *group;

	if (0 > group_index || ACP_MAX_OS_GROUPS <= group_index)
		return -1;

	group = acp_osg_groups[group_index];
	address = (group->base * 1024 * 1024);
	size = group->size * 1024 * 1024;

	/*
	  At present, the "resolution" of OS groups is 256M...
	*/

	if (0 != (size % 0x10000000UL))
		return -1;

	if (0 != (address % 0x10000000UL))
		return -1;

	while (0 < size) {
		if (0UL != address) {
			word0 = address | 0x9f0;
			word1 = address;
			word2 = 0x00030207;

			__asm__ __volatile__ ( "tlbwe %1,%0,0\n"               \
					       "tlbwe %2,%0,1\n"               \
					       "tlbwe %3,%0,2\n"               \
					       "isync\n" : :
					       "r" (0x80000000),
					       "r" (word0),
					       "r" (word1),
					       "r" (word2) :
					       "memory" );
		}

		size -= 0x10000000UL;
		address += 0x10000000UL;
	}

	return 0;
}

#endif /* CONFIG_ACP3 */
