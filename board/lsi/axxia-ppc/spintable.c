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
static int core_up[] = {0, 0, 0, 0, 0, 0};

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
acp_spintable_init(void *fdt,
		   int core, int cold_start, unsigned long os_base_address)
{
#if !defined(ACP_CORE1ONLY)
	int group;
	char *nodes[] = {
		"/cpus/cpu@0",
		"/cpus/cpu@1",
		"/cpus/cpu@2",
		"/cpus/cpu@3",
		"/cpus/cpu@4",
		"/cpus/cpu@5"
	};
	acp_spintable_t *spintable;
	unsigned long long release_address;
	struct fdt_header *dt;
	const struct fdt_property *property;
	int nodeoffset;
	int retries = 1000;

	/* Get the group this core belongs to. */
#ifndef AXM_35xx
	if (-1 == (group = acp_osg_get_group(core)))
		acp_failure(__FILE__, __FUNCTION__, __LINE__);
#else
	/*AXM35xx supports SMP only */
	group = 0;
#endif

	/* Get a pointer to the device tree. */
	if (NULL == fdt) {
		if (NULL == (dt = (struct fdt_header *)get_acp_fdt(group)))
			acp_failure(__FILE__, __FUNCTION__, __LINE__);
	} else {
		dt = fdt;
	}

	/* Map memory if necessary */
	if (-1 == acp_osg_map(group))
		acp_failure(__FILE__, __FUNCTION__, __LINE__);

	/*spintable = (acp_spintable_t *)(0x2000 + (core * 0x40));*/
	spintable = (acp_spintable_t *)(((unsigned long)(&_spintables)) + (core * 0x40));

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

#ifdef ACP_25xx
#ifdef RESET_INSTEAD_OF_IPI
	/* Enable L2 1 and Core 1 */
	{
		unsigned temp;

		temp = dcr_read(0xd00);
		temp |= 0xab;
		dcr_write(temp, 0xd00);

		dcr_write(0x0, (DCR_RESET_BASE + 2));
		dcr_write(0x0, (DCR_RESET_BASE + 1));
	}
#else
	/* Wake up the L2 */
	dcr_write(0x84, 0x300 + (0x100 * core));
	dcr_write(0, 0x304 + (0x100 * core));

	/* Send an IPI */
	if (0 != cold_start) {
		printf("Sending an IPI to core %d: ", core);
		dcr_write((1 << core), 0xffc00040);
	}
#endif
#else
	/* Send an IPI */
	if (0 != cold_start) {
		printf("Sending an IPI to core %d: ", core);
		dcr_write((1 << core), 0xffc00040);
	}
#endif

	/* Wait for a response */
	while( 0 < retries ) {
		-- retries;
		if( 0 != core_up [ core ] ) break;
		udelay( 1000 );
	}

	if (0 != cold_start) {
		if( 0 == retries ) {
			printf("Hung\n");
		} else {
			printf("Up\n");
		}
	}

	acp_osg_set_spintable_state(core, ACP_OSG_SPINTABLE_NOTAVAIL);

#endif /* !defined(ACP_CORE1ONLY) */

	return 0;
}

#endif /* CONFIG_ACP3 */
