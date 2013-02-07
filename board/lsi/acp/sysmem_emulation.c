/*
 *  Copyright (C) 2010 LSI Corporation
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

/*
  ==============================================================================
  ==============================================================================
  ==============================================================================
  Local Stuff
  ==============================================================================
  ==============================================================================
  ==============================================================================
*/

/*#define SYSCACHE_ACP3*/
/*#define SYSCACHE_ACP2*/

#if defined(SYSCACHE_ACP3) || defined(SYSCACHE_ACP2)
#warning "Overriding the default System Cache Version!"
#else
#if defined(ACP_25xx)
#define SYSCACHE_ACP2
#else
#define SYSCACHE_ACP3
#endif
#endif

unsigned long sc_nodes[] = {0x20, 0x1e, 0x21, 0x1d, 0x11, 0x12, 0x10, 0x13};

/*#define SYSMEM_ACP3*/
/*#define SYSMEM_ACP2*/

#if defined(SYSMEM_ACP3) || defined(SYSMEM_ACP2)
#warning "Overriding the default System Memory Version!"
#else
#if defined(ACP_25xx)
#define SYSMEM_ACP2
#else
#define SYSMEM_ACP3
#endif
#endif

#if defined(SYSMEM_ACP3) && defined(SYSMEM_ACP2)
#error "Only One SYSMEM Version at a Time!"
#endif

#if defined(SYSMEM_ACP3)
#define SYSMEM_MASK 0xff000000
#define SYSMEM_V0   0x00000000
#define SYSMEM_V1   0x01000000
#define SYSMEM_V2   0x02000000
#define SYSMEM_V3   0x03000000
#else
#if defined(SYSMEM_ACP2)
#define SYSMEM_V0   0x10000000
#define SYSMEM_V1   0x20000000
#endif
#endif

unsigned long sm_nodes[] = {0x22, 0x0f};

/*
  ==============================================================================
  System Cache
  ==============================================================================
*/

/*
  ------------------------------------------------------------------------------
  syscache_mode
*/

static int
syscache_mode(int num_sc_nodes, int mode)
{
	int rc = 0;
	int i;

	for (i = 0; i < num_sc_nodes; ++i) {
		rc |= ncr_write32(NCP_REGION_ID(sc_nodes[i], 0), 0x100, mode);
	}

	return rc;
}

/*
  ------------------------------------------------------------------------------
  initialize_syscache
*/

static int
initialize_syscache(int sm_version, int sc_version, int num_sc_nodes)
{
	int i;
	unsigned long munge;
#if defined(SYSCACHE_ACP3)
	unsigned long update_sc_control;
#endif

	/*
	  Figure out the "munge" value.
	*/

	munge = 0;

#if defined(SYSCACHE_ACP3)

	if (1 <= sc_version) {
		switch (num_sc_nodes) {
		case 1:
			munge = 0x110;
			break;
		case 2:
			munge = 0x115;
			break;
		default:
			break;
		}
	}

	ncr_read32(NCP_REGION_ID(0x20, 0), 0x4, &update_sc_control);

	if (0x003108ff == update_sc_control)
		update_sc_control = 0x008908ff;

#else

#ifdef ACP_25xx
	/* Per BZ38847, the munge value for 2500 is 0x106. */
	munge = 0x106;
#else
	munge = 0x115;
#endif

#endif

	for (i = 0; i < num_sc_nodes; ++i) {
		volatile unsigned long count = 0x10000000;
		unsigned long value;

		/*
		  Initialize Cache RAMs on both caches
		*/

		ncr_write32(NCP_REGION_ID(sc_nodes[i], 0), 0x18, 0x000ed);
		ncr_write32(NCP_REGION_ID(sc_nodes[i], 0), 0x18, 0x200ed);

		/* wait for completion... */
		while (0 < --count) {
			count = count; 
			ncr_read32(NCP_REGION_ID(sc_nodes[i], 0), 0x20, &value);

			if (0 == (value & 0x4))
				break;
		}

		/*
		  Initialize Cache address munge
		*/

		ncr_write32(NCP_REGION_ID(sc_nodes[i], 0), 0x14, munge);

		/*
		  Set the L3 Cache ID Registers
		*/

		ncr_read32(NCP_REGION_ID(sc_nodes[i], 0), 4, &value);
		value &= 0xff00ffff;
		value |= 0x00890000;
		ncr_write32(NCP_REGION_ID(sc_nodes[i], 0), 4, value);

#if defined(SYSCACHE_ACP2)
		ncr_read32(NCP_REGION_ID(sc_nodes[i], 0), 0x90, &value);
		value &= 0xfffffff0;
		value |= 0x00000009;
		ncr_write32(NCP_REGION_ID(sc_nodes[i], 0), 0x90, value);
#endif

		/*
		  BZ 29933 (V1 only)

		  Change the high water mark (the fifo_high_wm field in
		  mem_inf_write_scr_cmd_fifo_wm) to 4 (default is 5).
		*/
#if defined(SYSCACHE_ACP3)
		if (0 == sc_version) {
			ncr_write32(NCP_REGION_ID(sc_nodes[i], 1), 0x254,
				    0x00040004);
		}
#endif
	}

	return 0;
}

/*
  ==============================================================================
  System Memory
  ==============================================================================
*/

#if defined(SYSMEM_ACP3)

static int
initialize_sysmem(int sm_version)
{
	switch (sysmem->topology) {
	case 1:
		sysmem_size = 30;
		break;
	case 3:
		sysmem_size = 31;
		break;
	default:
		printf("Unsupported Topoogy: 0x%08lx\n", sysmem->topology);
		return -1;
		break;
	}

	switch (sm_version) {
	case SYSMEM_V0:
	case SYSMEM_V1:
	case SYSMEM_V2:
	case SYSMEM_V3:
		break;
	default:
		printf("Unsupported System Memory Controller Version: 0x%08x\n",
		       sm_version);
		return -1;
		break;
	}

	if (SYSMEM_V0 == sm_version) {
		ncr_write32( NCP_REGION_ID( 34, 256 ), 0x010, 0x00000003 );
	} else {
		ncr_write32( NCP_REGION_ID( 34, 255 ), 0x010, 0x00000003 );
	}

	ncr_write32( NCP_REGION_ID( 34, 1 ), 0x000, 0x00000002 );

	switch( sm_version ) {
	case SYSMEM_V0:
	case SYSMEM_V1:
		ncr_write32(NCP_REGION_ID( 34, 0 ), 0x000, 0x00000101);
		break;
	case SYSMEM_V2:
		ncr_write32(NCP_REGION_ID( 34, 0 ), 0x000, 0x00010101);
		break;
	case SYSMEM_V3:
		ncr_write32(NCP_REGION_ID( 34, 0 ), 0x000, 0x00010100);
		break;
	}

	if (SYSMEM_V3 == sm_version) {
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x004, 0x01010101 );
	} else {
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x004, 0x01010100 );
	}

	if( SYSMEM_V3 == sm_version ) {
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x008, 0x00000100 );
	} else {
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x008, 0x00000000 );
	}

	switch( sm_version ) {
	case SYSMEM_V0:
	case SYSMEM_V1:
		ncr_write32( NCP_REGION_ID(34, 0), 0x00c, 0x01010101 );
		break;
	case SYSMEM_V2:
		ncr_write32( NCP_REGION_ID(34, 0), 0x00c, 0x01000101 );
		break;
	case SYSMEM_V3:
		ncr_write32( NCP_REGION_ID(34, 0), 0x00c, 0x01000000 );
		break;
	}

	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x010, 0x00000000 );
	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x014, 0x01000000 );

	switch( sm_version ) {
	case SYSMEM_V0:
		ncr_write32( NCP_REGION_ID(34, 0), 0x018, 0x00010101 );
		break;
	case SYSMEM_V1:
	case SYSMEM_V2:
		ncr_write32( NCP_REGION_ID(34, 0), 0x018, 0x00010100 );
		break;
	case SYSMEM_V3:
		ncr_write32( NCP_REGION_ID(34, 0), 0x018, 0x00010000 );
		break;
	}

	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x01c, 0x00000001 );
	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x020, 0x00000000 );
	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x024, 0x00000000 );
	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x028, 0x00000000 );
	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x02c, 0x00000000 );

	switch( sm_version ) {
	case SYSMEM_V0:
	case SYSMEM_V1:
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x030, 0x01000000 );
		break;
	case SYSMEM_V3:
	case SYSMEM_V2:
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x030, 0x01000001 );
		break;
	}

	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x034, 0x00000000 );
	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x038, 0x00010100 );
	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x03c, 0x00000000 );

	switch( sm_version ) {
	case SYSMEM_V0:
	case SYSMEM_V1:
	case SYSMEM_V2:
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x040, 0x02020000 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x044, 0x02020100 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x048, 0x02020200 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x04c, 0x02020300 );
		break;
	case SYSMEM_V3:
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x040, 0x00000000 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x044, 0x00000100 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x048, 0x00000200 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x04c, 0x00000300 );
		break;
	}

	switch (sm_version) {
	case SYSMEM_V0:
	case SYSMEM_V1:
		ncr_write32(NCP_REGION_ID(34, 0), 0x050, 0x01000000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x054, 0x01010000);
		break;
	case SYSMEM_V2:
		if (0 != sysmem->enableECC)
			ncr_write32(NCP_REGION_ID(34, 0), 0x050, 0x01000300);
		else
			ncr_write32(NCP_REGION_ID(34, 0), 0x050, 0x01000000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x054, 0x01010000);
		break;
	case SYSMEM_V3:
		if (0 != sysmem->enableECC)
			ncr_write32(NCP_REGION_ID(34, 0), 0x050, 0x00000300);
		else
			ncr_write32(NCP_REGION_ID(34, 0), 0x050, 0x00000000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x054, 0x01000000);
		break;
	}

	ncr_write32(NCP_REGION_ID(34, 0), 0x058, 0x03070200);
	ncr_write32(NCP_REGION_ID(34, 0), 0x05c, 0x00070300);
	ncr_write32(NCP_REGION_ID(34, 0), 0x060, 0x03070000);
	ncr_write32(NCP_REGION_ID(34, 0), 0x064, 0x00020404);

	switch (sm_version) {
	case SYSMEM_V0:
	case SYSMEM_V1:
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x068, 0x04040a00 );
		break;
	case SYSMEM_V2:
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x068, 0x04040a02 );
		break;
	case SYSMEM_V3:
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x068, 0x01010a02 );
		break;
	}

	switch( sm_version ) {
	case SYSMEM_V0:
	case SYSMEM_V1:
	case SYSMEM_V2:
		ncr_write32(NCP_REGION_ID(34, 0), 0x06c, 0x03030404);
		ncr_write32(NCP_REGION_ID(34, 0), 0x070, 0x02020303);
		ncr_write32(NCP_REGION_ID(34, 0), 0x074, 0x01010202);
		break;
	case SYSMEM_V3:
		ncr_write32(NCP_REGION_ID(34, 0), 0x06c, 0x01010101);
		ncr_write32(NCP_REGION_ID(34, 0), 0x070, 0x01010101);
		ncr_write32(NCP_REGION_ID(34, 0), 0x074, 0x01010101);
		break;;
	}

	switch( sm_version ) {
	case SYSMEM_V0:
	case SYSMEM_V1:
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x078, 0x0c0f0101 );
		break;
	case SYSMEM_V2:
	case SYSMEM_V3:
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x078, 0x0c000101 );
		break;
	}

	switch( sm_version ) {
	case SYSMEM_V0:
	case SYSMEM_V1:
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x07c, 0x00060106 );
		break;
	case SYSMEM_V2:
		switch (sysmem->topology) {
		case 1:
			ncr_write32(NCP_REGION_ID(34, 0), 0x07c, 0x00060106);
		case 3:
			ncr_write32(NCP_REGION_ID(34, 0), 0x07c, 0x00060306);
			break;
		}
		break;
	case SYSMEM_V3:
		switch (sysmem->topology) {
		case 1:
			ncr_write32(NCP_REGION_ID(34, 0), 0x07c, 0x00060100);
		case 3:
			ncr_write32(NCP_REGION_ID(34, 0), 0x07c, 0x00060300);
			break;
		}
		break;
	}

	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x080, 0x00000000 );
	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x084, 0x00000000 );
	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x088, 0x04000000 );
	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x08c, 0x02000a02 );
	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x090, 0x04070f0f );

	switch( sm_version ) {
	case SYSMEM_V0:
	case SYSMEM_V1:
		ncr_write32(NCP_REGION_ID(34, 0), 0x094, 0x03000606);
		break;
	case SYSMEM_V2:
	case SYSMEM_V3:
		ncr_write32(NCP_REGION_ID(34, 0 ), 0x094, 0x00000606 );
		break;
	}

	if (SYSMEM_V0 == sm_version)
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x098, 0x00000e06 );
	else
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x098, 0x00000e0c );

	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x09c, 0x0f070000 );
	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x0a0, 0x14020008 );
	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x0a4, 0x00081b04 );
	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x0a8, 0x00002819 );

	if (SYSMEM_V0 == sm_version) {
		ncr_write32(NCP_REGION_ID(34, 0), 0x0c0, 0x00000000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x0c4, 0x00000000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x0c8, 0x00000000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x0d0, 0x08000000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x0d4, 0x000000ff);
		ncr_write32(NCP_REGION_ID(34, 0), 0x0dc, 0x00000000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x0e0, 0x00000000);
	}

	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x0e4, 0x40000000 );
	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x0f0, 0x0a000300 );

	if (SYSMEM_V0 == sm_version)
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x0f4, 0x0500037f );
	else
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x0f4, 0x05000300 );

	switch (sm_version) {
	case SYSMEM_V0:
		ncr_write32(NCP_REGION_ID(34, 0), 0x0f8, 0x07140a7f);
		break;
	case SYSMEM_V1:
	case SYSMEM_V3:
		ncr_write32(NCP_REGION_ID(34, 0), 0x0f8, 0x07140a00);
		break;
	case SYSMEM_V2:
		ncr_write32(NCP_REGION_ID(34, 0), 0x0f8, 0x07140c00);
		break;
	}

	switch (sm_version) {
	case SYSMEM_V0:
	case SYSMEM_V1:
		ncr_write32(NCP_REGION_ID(34, 0), 0x0fc, 0x0000640a);
		break;
	case SYSMEM_V2:
		ncr_write32(NCP_REGION_ID(34, 0), 0x0fc, 0x00006403);
		break;
	case SYSMEM_V3:
		ncr_write32(NCP_REGION_ID(34, 0), 0x0fc, 0x00006400);
		break;
	}

	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x100, 0x00640064 );
	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x104, 0x00400064 );

	if (SYSMEM_V0 == sm_version) {
		ncr_write32(NCP_REGION_ID(34, 0), 0x108, 0x00000200);
	}

	if (SYSMEM_V2 == sm_version) {
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x118, 0x00bc0000 );
	} else {
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x118, 0x00ea0000 );
	}

	switch (sm_version) {
	case SYSMEM_V0:
	case SYSMEM_V1:
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x11c, 0x001c001c );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x120, 0x001c001c );
		break;
	case SYSMEM_V2:
	case SYSMEM_V3:
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x11c, 0x00000000 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x120, 0x00000000 );
		break;
	}

	switch (sm_version) {
	case SYSMEM_V0:
		ncr_write32(NCP_REGION_ID(34, 0), 0x124, 0x40020000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x128, 0x00004002);
		ncr_write32(NCP_REGION_ID(34, 0), 0x12c, 0x80000000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x130, 0x00008000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x134, 0xc0000000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x138, 0x0000c000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x13c, 0x02200000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x140, 0x00000220);
		ncr_write32(NCP_REGION_ID(34, 0), 0x144, 0x00000000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x148, 0x0000000f);
		break;
	case SYSMEM_V1:
		ncr_write32(NCP_REGION_ID(34, 0), 0x124, 0x00000000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x144, 0x00000000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x148, 0x0000000f);
		break;
	case SYSMEM_V2:
		ncr_write32(NCP_REGION_ID(34, 0), 0x124, 0x00000000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x144, 0x00000000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x148, 0x0041000f);
		break;
	case SYSMEM_V3:
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x124, 0x00000000 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x148, 0x00000000 );
		break;
	}

	switch (sm_version) {
	case SYSMEM_V0:
	case SYSMEM_V1:
		ncr_write32(NCP_REGION_ID(34, 0), 0x150, 0x00030200);
		ncr_write32(NCP_REGION_ID(34, 0), 0x154, 0x000a083c);
		ncr_write32(NCP_REGION_ID(34, 0), 0x158, 0x00050040);
		ncr_write32(NCP_REGION_ID(34, 0), 0x15c, 0x00040000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x160, 0x00000000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x164, 0x00000000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x168, 0x00000000);
		if (SYSMEM_V1 == sm_version)
			ncr_write32(NCP_REGION_ID(34, 0), 0x16c, 0x00000000);
		break;
	case SYSMEM_V2:
		ncr_write32(NCP_REGION_ID(34, 0), 0x150, 0x00040200);
		ncr_write32(NCP_REGION_ID(34, 0), 0x154, 0x000d4920);
		ncr_write32(NCP_REGION_ID(34, 0), 0x158, 0x02000041);
		ncr_write32(NCP_REGION_ID(34, 0), 0x15c, 0x00040000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x160, 0x00000000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x164, 0x00000000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x168, 0x00000000);
		break;
	case SYSMEM_V3:
		ncr_write32(NCP_REGION_ID(34, 0), 0x150, 0x00030200);
		ncr_write32(NCP_REGION_ID(34, 0), 0x154, 0x000a0000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x158, 0x00050040);
		ncr_write32(NCP_REGION_ID(34, 0), 0x15c, 0x00000000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x160, 0x00000000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x164, 0x00000000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x168, 0x00000000);
		break;
	}

	if (SYSMEM_V0 != sm_version) {
		ncr_write32(NCP_REGION_ID(34, 0), 0x16c, 0x00000000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x170, 0x00000000);
	}

	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x174, 0x00000006 );
	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x178, 0x0000010a );
	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x17c, 0x00000000 );

	switch (sm_version) {
	case SYSMEM_V0:
	case SYSMEM_V1:
		if (SYSMEM_V0 == sm_version) {
			ncr_write32( NCP_REGION_ID( 34, 0 ), 0x180, 0x00000000 );
		}
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x184, 0x0005220c );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x188, 0x0005220c );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x18c, 0x0005220c );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x190, 0x0005220c );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x194, 0x0005220c );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x198, 0x0005220c );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x19c, 0x0005220c );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x1a0, 0x0005220c );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x1a4, 0x0005220c );
		if (SYSMEM_V0 == sm_version) {
			ncr_write32(NCP_REGION_ID(34, 0), 0x1a8, 0x000f1133);
			ncr_write32(NCP_REGION_ID(34, 0), 0x1ac, 0xf5002a27);
			ncr_write32(NCP_REGION_ID(34, 0), 0x1b0, 0xf5002a27);
			ncr_write32(NCP_REGION_ID(34, 0), 0x1b4, 0xf5002a27);
			ncr_write32(NCP_REGION_ID(34, 0), 0x1b8, 0xf5002a27);
			ncr_write32(NCP_REGION_ID(34, 0), 0x1bc, 0xf5002a27);
			ncr_write32(NCP_REGION_ID(34, 0), 0x1c0, 0xf5002a27);
			ncr_write32(NCP_REGION_ID(34, 0), 0x1c4, 0xf5002a27);
			ncr_write32(NCP_REGION_ID(34, 0), 0x1c8, 0xf5002a27);
			ncr_write32(NCP_REGION_ID(34, 0), 0x1cc, 0xf5002a27);
			ncr_write32(NCP_REGION_ID(34, 0), 0x1d0, 0x08c00d01);
			ncr_write32(NCP_REGION_ID(34, 0), 0x1d4, 0x08c00d01);
			ncr_write32(NCP_REGION_ID(34, 0), 0x1d8, 0x08c00d01);
			ncr_write32(NCP_REGION_ID(34, 0), 0x1dc, 0x08c00d01);
			ncr_write32(NCP_REGION_ID(34, 0), 0x1e0, 0x08c00d01);
			ncr_write32(NCP_REGION_ID(34, 0), 0x1e4, 0x08c00d01);
			ncr_write32(NCP_REGION_ID(34, 0), 0x1e8, 0x08c00d01);
			ncr_write32(NCP_REGION_ID(34, 0), 0x1ec, 0x08c00d01);
			ncr_write32(NCP_REGION_ID(34, 0), 0x1f0, 0x08c00d01);
			ncr_write32(NCP_REGION_ID(34, 0), 0x1f4, 0x00000106);
		}
		break;
	case SYSMEM_V2:
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x184, 0x0001510c );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x188, 0x0001510c );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x18c, 0x0001510c );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x190, 0x0001510c );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x194, 0x0001510c );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x198, 0x0001510c );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x19c, 0x0001510c );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x1a0, 0x0001510c );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x1a4, 0x0001510c );
		break;
	default:
		break;
	}

	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x1f8, 0x0000006b );
	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x1fc, 0x00000000 );
	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x200, 0x00000000 );

	if (SYSMEM_V0 != sm_version ) {
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x224, 0x00000000 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x228, 0x00000000 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x22c, 0x00000000 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x230, 0x00000000 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x234, 0x00000000 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x238, 0x00000000 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x23c, 0x00000000 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x240, 0x00000000 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x244, 0x00000000 );
	}

	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x250, 0x00000000 );
	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x254, 0x00000000 );
	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x280, 0x00000000 );
	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x284, 0x00000000 );
	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x298, 0x00000000 );
	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x29c, 0x00000000 );
	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x2a0, 0x00000000 );
	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x2a4, 0x00000000 );
	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x2a8, 0x00000000 );
	ncr_write32( NCP_REGION_ID( 34, 0 ), 0x2ac, 0x00000000 );

	if (SYSMEM_V0 != sm_version ) {
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x2d0, 0x00000000 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x2d4, 0x00000000 );

		switch( sm_version ) {
		case SYSMEM_V1:
		case SYSMEM_V2:
			ncr_write32( NCP_REGION_ID( 34, 0 ), 0x2d8, 0x00010001 );
			ncr_write32( NCP_REGION_ID( 34, 0 ), 0x2dc, 0x00000104 );
			break;
		case SYSMEM_V3:
			ncr_write32( NCP_REGION_ID( 34, 0 ), 0x2d8, 0x00020002 );
			ncr_write32( NCP_REGION_ID( 34, 0 ), 0x2dc, 0x00000204 );
			break;
		}

		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x2e0, 0x00000700 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x2e4, 0x007f007f );

		if (SYSMEM_V1 == sm_version) {
			ncr_write32( NCP_REGION_ID( 34, 0 ), 0x2e8, 0x02000040 );
		} else {
			ncr_write32( NCP_REGION_ID( 34, 0 ), 0x2e8, 0x02000100 );
		}

		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x2ec, 0x02200220 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x2f0, 0x00000000 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x2f4, 0x40024002 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x2f8, 0x00000000 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x2fc, 0x80008000 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x300, 0x00000000 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x304, 0xc000c000 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x308, 0x00000000 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x31c, 0x22220000 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x320, 0x22222222 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x324, 0x22222222 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x328, 0x22222222 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x32c, 0x22222222 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x340, 0x00000000 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x344, 0x00000000 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x348, 0x00000000 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x34c, 0x00000000 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x350, 0x00000000 );

		if (SYSMEM_V1 == sm_version) {
			ncr_write32( NCP_REGION_ID( 34, 0 ), 0x354, 0x00100010 );
		} else {
			ncr_write32( NCP_REGION_ID( 34, 0 ), 0x354, 0xffff0010 );
		}

		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x368, 0x00000000 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x36c, 0x00000000 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x370, 0x00000000 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x374, 0x00000000 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x378, 0x00000000 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x37c, 0x00000040 );
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x384, 0x00000040 );

		switch( sm_version ) {
		case SYSMEM_V3:
			ncr_write32( NCP_REGION_ID( 34, 0 ), 0x38c, 0x10330404 );
			ncr_write32( NCP_REGION_ID( 34, 0 ), 0x390, 0x10331033 );
			ncr_write32( NCP_REGION_ID( 34, 0 ), 0x394, 0x0000083c );
			ncr_write32( NCP_REGION_ID( 34, 0 ), 0x398, 0x0000000a );
			ncr_write32( NCP_REGION_ID( 34, 0 ), 0x39c, 0x00000000 );
			ncr_write32( NCP_REGION_ID( 34, 0 ), 0x3a0, 0x00000000 );
			ncr_write32( NCP_REGION_ID( 34, 0 ), 0x3a4, 0x00000000 );
			ncr_write32( NCP_REGION_ID( 34, 0 ), 0x3a8, 0x00000000 );
			break;
		case SYSMEM_V2:
			ncr_write32( NCP_REGION_ID( 34, 0 ), 0x38c, 0x10330404 );
			ncr_write32( NCP_REGION_ID( 34, 0 ), 0x390, 0x10331033 );
			break;
		}
	}

	ncr_write32( NCP_REGION_ID( 34, 1 ), 0x000, 0x00000003 );
	ncr_write32( NCP_REGION_ID( 34, 1 ), 0x004, 0x00000066 );
	ncr_write32( NCP_REGION_ID( 34, 1 ), 0x00c, 0x00000507 );

	switch (sm_version) {
	case SYSMEM_V0:
	case SYSMEM_V1:
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x030, 0x01010000 );
		break;
	case SYSMEM_V2:
	case SYSMEM_V3:
		ncr_write32( NCP_REGION_ID( 34, 0 ), 0x030, 0x01010001 );
		break;
	}

	udelay( 1000 * 1000 );

	switch (sm_version) {
	case SYSMEM_V0:
		ncr_write32(NCP_REGION_ID(34, 0), 0x12c, 0x80080000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x130, 0x00008008);
		ncr_write32(NCP_REGION_ID(34, 0), 0x03c, 0x00000100);
		udelay(1000 * 1000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x124, 0x40030000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x128, 0x00004003);
		ncr_write32(NCP_REGION_ID(34, 0), 0x12c, 0x80080000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x130, 0x00008008);
		ncr_write32(NCP_REGION_ID(34, 0), 0x03c, 0x00000100);
		break;
	case SYSMEM_V1:
	case SYSMEM_V2:
	case SYSMEM_V3:
		if (SYSMEM_V1 != sm_version) {
			ncr_write32(NCP_REGION_ID(34, 0), 0x2f4, 0x80088008);
		}
		ncr_write32(NCP_REGION_ID(34, 0), 0x2fc, 0x80088008);
		ncr_write32(NCP_REGION_ID(34, 0), 0x03c, 0x00000100);
		udelay(1000 * 1000);
		ncr_write32(NCP_REGION_ID(34, 0), 0x2f4, 0x40034003);
		ncr_write32(NCP_REGION_ID(34, 0), 0x2fc, 0x80088008);
		ncr_write32(NCP_REGION_ID(34, 0), 0x03c, 0x00000100);
		break;
	}

	ncr_write32( NCP_REGION_ID( 34, 1 ), 0x010, 0x00000202 );
	ncr_write32( NCP_REGION_ID( 34, 1 ), 0x020, 0x00000202 );
	ncr_write32( NCP_REGION_ID( 34, 1 ), 0x030, 0x00000202 );
	ncr_write32( NCP_REGION_ID( 34, 1 ), 0x040, 0x00000202 );
	ncr_write32( NCP_REGION_ID( 34, 1 ), 0x050, 0x00000202 );
	ncr_write32( NCP_REGION_ID( 34, 1 ), 0x060, 0x00000202 );
	ncr_write32( NCP_REGION_ID( 34, 1 ), 0x070, 0x00000202 );
	ncr_write32( NCP_REGION_ID( 34, 1 ), 0x080, 0x00000202 );
	ncr_write32( NCP_REGION_ID( 34, 1 ), 0x090, 0x00000202 );

	return 0;
}

#elif defined(SYSMEM_ACP2)

static int
initialize_sysmem(int sm_version)
{
	/*
	  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	  ncp_sysmem_init_fpga_2500()
	  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	*/

	/*
	  ncpRead    0.769.0.0x0000000000 1
	  ncpRead    0.769.0.0x0000000004 1
	  ncpRead    0.34.255.0x0000000000 1
	  ncpRead    0.769.0.0x0000000018 1
	  ncpRead    0.24.255.0x0000000004 1
	*/

	NCR_TRACE("# Initializing Denali acp2500 memory controller\n");
	ncr_write32(NCP_REGION_ID(0x22, 255), 0x10, 0x00000003);
	ncr_write32(NCP_REGION_ID(0x22, 1), 0x000, 0x00000002);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x000, 0x00010100);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x004, 0x01010101);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x008, 0x00000100);

	if (SYSMEM_V0 == sm_version)
		ncr_write32(NCP_REGION_ID(0x22, 0), 0x00c, 0x01000000);
	else
		ncr_write32(NCP_REGION_ID(0x22, 0), 0x00c, 0x01000000);

	ncr_write32(NCP_REGION_ID(0x22, 0), 0x010, 0x00000000);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x014, 0x01000000);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x018, 0x00010000);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x01c, 0x00000001);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x020, 0x00000000);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x024, 0x00000000);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x028, 0x00000000);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x02c, 0x00010000);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x030, 0x01000001);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x034, 0x00000000);

	/* Defect 36670: Enable tras_lockout */
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x038, 0x00000100);

	ncr_write32(NCP_REGION_ID(0x22, 0), 0x03c, 0x00000000);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x040, 0x00000000);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x044, 0x00000100);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x048, 0x00000200);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x04c, 0x00000300);

	if (sysmem->enableECC) {
		ncr_write32(NCP_REGION_ID(0x22, 0), 0x50, 0x00000300);
	} else {
		ncr_write32(NCP_REGION_ID(0x22, 0), 0x50, 0x00000000);
	}
        
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x054, 0x02000000);

	if (SYSMEM_V0 == sm_version) {
		ncr_write32(NCP_REGION_ID(0x22, 0), 0x058, 0x03070200);
		ncr_write32(NCP_REGION_ID(0x22, 0), 0x05c, 0x00070100);
	} else {
		ncr_write32(NCP_REGION_ID(0x22, 0), 0x058, 0x03070000);
		ncr_write32(NCP_REGION_ID(0x22, 0), 0x05c, 0x00070000);
	}

	ncr_write32(NCP_REGION_ID(0x22, 0), 0x060, 0x03070000);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x064, 0x00020404);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x068, 0x01010a02);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x06c, 0x01010101);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x070, 0x01010101);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x074, 0x01010101);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x078, 0x0c000101);
	
	switch (sysmem->topology) {
	case 1: /* single-rank */
		ncr_write32(NCP_REGION_ID(0x22, 0), 0x07c, 0x00060100);
		sysmem_size = 29;
		break;

	case 3: /* dual-rank */
		ncr_write32(NCP_REGION_ID(0x22, 0), 0x07c, 0x00060300);
		sysmem_size = 30;
		break;

	default:
		printf("Unsupported Topoogy: 0x%08lx\n", sysmem->topology);
		return -1;
		break;
	}

	ncr_write32(NCP_REGION_ID(0x22, 0), 0x080, 0x00000000);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x084, 0x00000000);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x088, 0x04000000);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x08c, 0x00000002);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x090, 0x04090f0f);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x094, 0x00000506);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x098, 0x0000000c);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x09c, 0x15070000);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x0a0, 0x18000008);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x0a4, 0x000c2504);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x0a8, 0x00002819);

	if (SYSMEM_V0 == sm_version)
		ncr_write32(NCP_REGION_ID(0x22, 0), 0x0e4, 0x40000000);

	ncr_write32(NCP_REGION_ID(0x22, 0), 0x0f0, 0x0a000300);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x0f4, 0x05000300);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x0f8, 0x091c0c00);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x0fc, 0x00006400);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x100, 0x00640064);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x104, 0x00400064);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x118, 0x00ea0000);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x11c, 0x00000000);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x120, 0x00000000);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x124, 0x00000000);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x148, 0x00000000);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x150, 0x00050200);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x154, 0x00140000);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x158, 0x02000060);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x164, 0x00000000);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x174, 0x00000008);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x178, 0x0000010a);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x17c, 0x00008000);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x1f8, 0x0000006b);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x1fc, 0x00000000);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x200, 0x00000000);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x2d0, 0x00000000);

	if (SYSMEM_V0 == sm_version)
		ncr_write32(NCP_REGION_ID(0x22, 0), 0x2d4, 0x00000000);
	else
		ncr_write32(NCP_REGION_ID(0x22, 0), 0x2d4, 0x00010000);

	ncr_write32(NCP_REGION_ID(0x22, 0), 0x2d8, 0x02020001);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x2dc, 0x00000104);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x2e0, 0x00000900);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x2e4, 0x007f007f);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x2e8, 0x02000100);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x2ec, 0x02200220);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x2f4, 0x40024002);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x2fc, 0x80008000);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x304, 0xc000c000);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x38c, 0x10330504);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x390, 0x10331033);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x394, 0x0000036d);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x398, 0x00000002);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x3b0, 0x00000003);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x3bc, 0x0000000c);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x3c8, 0x00000005);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x45c, 0x00000000);

	if (SYSMEM_V0 == sm_version) {
		ncr_write32(NCP_REGION_ID(0x22, 0), 0x520, 0x00010003);
	} else {
		ncr_write32(NCP_REGION_ID(0x22, 0), 0x520, 0x01000002);
		ncr_write32(NCP_REGION_ID(0x22, 0), 0x528, 0x00000003);
		ncr_write32(NCP_REGION_ID(0x22, 0), 0x530, 0x00000040);
		ncr_write32(NCP_REGION_ID(0x22, 0), 0x534, 0x01010200);
		ncr_write32(NCP_REGION_ID(0x22, 0), 0x538, 0x05000000);
	}

	ncr_write32(NCP_REGION_ID(0x22, 0), 0x1fc, 0x80000000);
	ncr_write32(NCP_REGION_ID(0x22, 1), 0x000, 0x00000003);
	ncr_write32(NCP_REGION_ID(0x22, 1), 0x004, 0x00000066);
	ncr_write32(NCP_REGION_ID(0x22, 1), 0x00c, 0x00000507);
	ncr_write32(NCP_REGION_ID(0x22, 1), 0x10, 0x00000202);
	ncr_write32(NCP_REGION_ID(0x22, 1), 0x20, 0x00000202);
	ncr_write32(NCP_REGION_ID(0x22, 1), 0x30, 0x00000202);
	ncr_write32(NCP_REGION_ID(0x22, 1), 0x40, 0x00000202);
	ncr_write32(NCP_REGION_ID(0x22, 1), 0x50, 0x00000202);
	ncr_write32(NCP_REGION_ID(0x22, 1), 0x60, 0x00000202);
	ncr_write32(NCP_REGION_ID(0x22, 1), 0x70, 0x00000202);
	ncr_write32(NCP_REGION_ID(0x22, 1), 0x80, 0x00000202);
	ncr_write32(NCP_REGION_ID(0x22, 1), 0x90, 0x00000202);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x030, 0x01010001);

	ncr_poll(NCP_REGION_ID(0x22, 0), 0x410,
		 0x0200, 0x0200, 1000000, 10000);

	ncr_write32(NCP_REGION_ID(0x22, 0), 0x164, 0x00080000);

	ncr_write32(NCP_REGION_ID(0x22, 0), 0x3ec, 0x00000300);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x3e8, 0x02800001);

	ncr_poll(NCP_REGION_ID(0x22, 0), 0x410,
		 0x00080000, 0x00080000, 100, 100);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x164, 0x00080000);

	ncr_write32(NCP_REGION_ID(0x22, 0), 0x3f0, 0x00000003);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x3e8, 0x02800101);

	ncr_poll(NCP_REGION_ID(0x22, 0), 0x410,
		 0x00080000, 0x00080000, 100, 100);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x164, 0x00080000);

	ncr_write32(NCP_REGION_ID(0x22, 0), 0x3ec, 0x001a2000);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x3e8, 0x02800000);

	ncr_poll(NCP_REGION_ID(0x22, 0), 0x410,
		 0x00080000, 0x00080000, 100, 100);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x164, 0x00080000);

	ncr_write32(NCP_REGION_ID(0x22, 0), 0x3f0, 0x00001a20);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x3e8, 0x02800100);

	ncr_poll(NCP_REGION_ID(0x22, 0), 0x410,
		 0x00080000, 0x00080000, 100, 100);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x164, 0x00080000);

	ncr_write32(NCP_REGION_ID(0x22, 0), 0x3ec, 0x00000800);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x3e8, 0x02800002);

	ncr_poll(NCP_REGION_ID(0x22, 0), 0x410,
		 0x00080000, 0x00080000, 100, 100);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x164, 0x00080000);

	ncr_write32(NCP_REGION_ID(0x22, 0), 0x3f0, 0x00000008);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x3e8, 0x02800102);

	ncr_poll(NCP_REGION_ID(0x22, 0), 0x410,
		 0x00080000, 0x00080000, 100, 100);
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x164, 0x00080000);

	/* Defect 36670: Enable tras_lockout */
	ncr_write32(NCP_REGION_ID(0x22, 0), 0x038, 0x00010100);

	/* ncpRead    0.24.255.0x0000000004 1 */

	return 0;
}

#else

#error "Unknown System Memory Controller!"

#endif

/*
  ==============================================================================
  ==============================================================================
  ==============================================================================
  Global Stuff
  ==============================================================================
  ==============================================================================
  ==============================================================================
*/

int
sysmem_init(void)
{
	int i;
	unsigned long sm_version;
	unsigned long sc_version;
	unsigned long num_sc_nodes;
	unsigned long value;
	int forced_encryption = 0;

#ifdef DISPLAY_PARAMETERS
	printf("sysmem: 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx\n"
	       "        0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx\n"
	       "        0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx\n"
	       "        0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx\n",
	       sysmem->version, sysmem->autoDetect,
	       sysmem->numInterfaces, sysmem->numRanksPerInterface,
	       sysmem->topology, sysmem->sdram_device_density,
	       sysmem->sdram_device_width, sysmem->primary_bus_width,
	       sysmem->CAS_latency, sysmem->CAS_write_latency,
	       sysmem->enableECC, sysmem->enableDeskew,
	       sysmem->enableRdlvl, sysmem->enableAutoCpc,
	       sysmem->minPhyCalibrationDelay,
	       sysmem->min_ctrl_roundtrip_delay, sysmem->singleBitMpr,
	       sysmem->rdcalCompareEven, sysmem->rdcalCompareOdd,
	       sysmem->phy_rdlat, sysmem->added_rank_switch_delay,
	       sysmem->high_temp_dram, sysmem->sdram_rtt_nom,
	       sysmem->sdram_rtt_wr, sysmem->sdram_data_drv_imp,
	       sysmem->phy_adr_imp, sysmem->phy_dat_imp,
	       sysmem->phy_rcv_imp, sysmem->sysCacheMode,
	       sysmem->syscacheDisable, sysmem->halfmemMode);
#endif

	/* Get the version of the System Memory controller. */
	ncr_read32(NCP_REGION_ID(0x22, 0), 0x214, &sm_version);
	sm_version &= 0xff000000;

	/* Get the version of the System Cache controller. */
	ncr_read32(NCP_REGION_ID(0x20, 0xff), 0, &sc_version);
	sc_version &= 0xffff;

	/* Figure out the number of System Cache Nodes from 0x18.0xff.0x4. */
	ncr_read32(NCP_REGION_ID(0x18, 0xff), 0x4, &num_sc_nodes);
	num_sc_nodes = (num_sc_nodes >> 8) & 0xff;

	/*
	  Disable System Cache
	*/

	syscache_mode(num_sc_nodes, 1);

	/*
	  Initialize the System Memory Controller
	*/

	initialize_sysmem(sm_version);

	/*
	  Enable System Cache
	*/

#if !defined(ACP_DISABLE_L3)
	if (!sysmem->syscacheDisable)
		/*
		  TODO: This should only be done for
		  architectures before ACP2500V2!
		  See BZ38534.
		*/
		syscache_mode(num_sc_nodes, 8);
#endif

	/*
	  Initialize the System Cache Nodes
	*/

	initialize_syscache(sm_version, sc_version, num_sc_nodes);

	/*
	  Handle DRAM Encryption...
	*/

	/* 1. Initialize system memory (see above). */

	/* 2. Make sure encryption logic is present. */
	ncr_read32(NCP_REGION_ID(sc_nodes[0], 0), 0x98, &value);

	if (0x80000100 == (value & 0x80000100)) {
		int ranged_encryption = 0;

		printf("Setting up System Memory Encryption.\n");

		/* 3. Determine encryption mode. */
		ncr_read32(NCP_REGION_ID(sc_nodes[0], 8), 8, &value);
		printf("crypto status: 0x%08x\n", value);

		switch ((value & 0x300) >> 8) {
		case 0:
		case 1:
			printf("No Encryption\n");
			break;
		case 2:
			printf("Ranged Encryption\n");
			ranged_encryption = 1;
			break;
		case 3:
			printf("Forced Encryption\n");
			forced_encryption = 1;
			break;
		default:
			break;
		}

		if (0 != ranged_encryption || 0 != forced_encryption) {
			unsigned long keys[(num_sc_nodes * 4)];

			/* 4. Set option encryption emulation modes. */
#if 0
			if (0 != ranged_encryption) {
				printf("Faking forced encryption mode.\n");

				for (i = 0; i < num_sc_nodes; ++i) {
					ncr_read32(NCP_REGION_ID(sc_nodes[i],
								 8),
						   0, &value);
					value |= 0x20;
					ncr_write32(NCP_REGION_ID(sc_nodes[i],
								  8),
						    0, value);
				}
			}
#endif

			/* 5. Verify that the TRNG is initialized. */
#if !defined(ACP_EMU)
#else
			/* There is no TRNG in emulation... */
			value = 0x44bb1283;

			for (i = 0; i < (num_sc_nodes * 4); ++i) {
				keys[i] = value;
				value = (~value << 1) | (i & 1);
			}
#endif
			/* 6. Initialize encryption keys. */
			for (i = 0; i < num_sc_nodes; ++i) {
				int j = i * 4;

				ncr_write32(NCP_REGION_ID(sc_nodes[i], 8), 0x10,
					    keys[j++]);
				ncr_write32(NCP_REGION_ID(sc_nodes[i], 8), 0x14,
					    keys[j++]);
				ncr_write32(NCP_REGION_ID(sc_nodes[i], 8), 0x18,
					    keys[j++]);
				ncr_write32(NCP_REGION_ID(sc_nodes[i], 8), 0x1c,
					    keys[j]);
			}

			if (0 != ranged_encryption) {
				/* 7. Set encryption ranges. */
			}

			/* 8. Change re-encryption rate. */
			/* 9. Enable encryption. */
			for (i = 0; i < num_sc_nodes; ++i) {
				ncr_read32(NCP_REGION_ID(sc_nodes[i], 8), 0,
					   &value);
				value |= 1;
				ncr_write32(NCP_REGION_ID(sc_nodes[i], 8), 0,
					    value);
			}
		}
	}

	/* Clear System Memory. */
	fill_sysmem(0ULL, (1ULL << sysmem_size), num_sc_nodes);

	/* Set NHA */
	dcr_write(0x33774000, 0xf00);

	return 0;
}
