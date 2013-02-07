/*
 * spintable.c
 *
 * Handles all non-zero cores on LSI's ACP.
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

/*#define LSI_DEBUG*/
#include <config.h>
#ifdef CONFIG_ACP3
#include <common.h>
#include <malloc.h>
#include <libfdt.h>
#include <fdt_support.h>
#include <asm/io.h>
#include <asm/processor.h>

#define ALIGNMENT 32UL

acp_spintable_t *acp_spintable[ACP_NR_CORES];
static int core_up[] = {0, 0, 0, 0};

/*
  ----------------------------------------------------------------------
  acp_spintable_spin
*/

void
acp_spintable_spin( void )
{
	unsigned long core;
	unsigned long os_base;
	volatile acp_spintable_t * spintable;

	__asm__ __volatile__ ( "mfspr %0,0x11e" : "=r" ( core ) );
	acp_osg_set_core_state(core, ACP_OSG_CORE_STATE_WAITING_FOR_SPINTABLE);

	while (ACP_OSG_SPINTABLE_NOTAVAIL == acp_osg_get_spintable_state(core)) {
		isync();
	}

	spintable = acp_spintable [ core ];
	core_up [ core ] = 1;

	while( 0xff != dcr_read( 0xffc000a0 ) ) {
		dcr_write( 0, 0xffc000b0 );
	}

	acp_osg_set_core_state(core, ACP_OSG_CORE_STATE_SPINNING);

	while( ( unsigned long long ) 1 == spintable->entry_address ) {
		isync( );
	}

	acp_osg_set_core_state(core, ACP_OSG_CORE_STATE_RUNNING);
	mtspr( ccr0, spintable->ccr0_value );
	mtspr( ccr1, spintable->ccr1_value );
	mtspr( ccr2, spintable->ccr2_value );
	isync( );

	acp_spintable_jump( ( unsigned long ) spintable->r3_value,
			    ( unsigned long ) spintable->entry_address );

	return;
}

/*
  ----------------------------------------------------------------------
  acp_spintable_init
*/

int
acp_spintable_init(int core, int cold_start, unsigned long os_base_address)
{
#if !defined(ACP_CORE1ONLY)
	int group;
	char *nodes[] = {
		"/cpus/cpu@0",
		"/cpus/cpu@1",
		"/cpus/cpu@2",
		"/cpus/cpu@3"
	};
	acp_spintable_t *spintable;
	unsigned long long release_address;
	struct fdt_header *dt;
	const struct fdt_property *property;
	int nodeoffset;
	int retries = 100;

	/* Get the group this core belongs to. */
	if (-1 == (group = acp_osg_get_group(core)))
		acp_failure(__FILE__, __FUNCTION__, __LINE__);

	/* Get a pointer to the device tree. */
	if (NULL == (dt = (struct fdt_header *)get_acp_fdt(group)))
		acp_failure(__FILE__, __FUNCTION__, __LINE__);

	/* Map memory if necessary */
	if (-1 == acp_osg_map(group))
		acp_failure(__FILE__, __FUNCTION__, __LINE__);

	if (0 == os_base_address) {
		/* Allocate a spin table */
		if ((acp_spintable_t *) 0 ==
		    (spintable = malloc(sizeof(acp_spintable_t) + ALIGNMENT))) {
			printf("Error allocating memory for %s.\n", nodes[core]);
			return -1;
		}

		spintable = (acp_spintable_t *)
			((((unsigned long) (spintable) +
			   (ALIGNMENT - 1UL)) & ~(ALIGNMENT - 1UL)));
	} else {
		/*
		  Otherwise, put at 1K above os_base_address.
		*/
		spintable = (acp_spintable_t *)
			((unsigned long)os_base_address + 0x2000 +
			 (core * ALIGNMENT));
	}

	/* Get the "reg" property */
	if (0 > (nodeoffset = fdt_path_offset(dt, nodes[core]))) {
		printf("Error Getting Node (%s) Offset.\n", nodes[core]);
		return -1;
	}

	if( ( struct fdt_property * ) 0 ==
	    ( property =
	      fdt_get_property( dt, nodeoffset,
				"reg", NULL ) ) ) {
		printf( "Error Getting Node (%s) Property \"reg\".\n",
			nodes [ core ] );
		return -1;
	}

	/* Initialize the spin table */
	spintable->entry_address = 1;
	spintable->r3_value = *((unsigned long *) property->data);
	spintable->rsvd1_value = 0;
	spintable->pir_value = core;

	/* Set the pointer array entry */
	acp_spintable[core] = spintable;

	/* Set the "cpu-release-addr" property */
	release_address = (unsigned long long)spintable;

	if( 0 != fdt_find_and_setprop( dt,
				       nodes [ core ],
				       "cpu-release-addr",
				       & release_address,
				       sizeof( unsigned long long ),
				       1 ) ) {
		printf( "Error Setting \"cpu-release-addr\".\n" );
		return -1;
	}

	/* Get the core from the 1st stage by sending an IPI. */
	DEBUG_PRINT("Changing core %d spintable state.\n", core);
	acp_osg_set_spintable_state(core, ACP_OSG_SPINTABLE_AVAILABLE);

	if (0 != cold_start) {
		DEBUG_PRINT("Sending an IPI to core %d.\n", core);
		dcr_write((1 << core), 0xffc00040);
	}

	/* Wait for a response */
	while( 0 < retries ) {
		-- retries;
		if( 0 != core_up [ core ] ) break;
		udelay( 100 );
	}

	if( 0 == retries ) {
		printf( "Core %d is hung!\n", core );
	} else {
		DEBUG_PRINT("Core %d woke up!\n", core);
	}

	acp_osg_set_spintable_state(core, ACP_OSG_SPINTABLE_NOTAVAIL);

#endif /* !defined(ACP_CORE1ONLY) */

	return 0;
}

#endif /* CONFIG_ACP3 */
