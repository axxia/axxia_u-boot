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
#include <watchdog.h>
#include <asm/io.h>

/*
  ==============================================================================
  ==============================================================================
  ==============================================================================
  Local Stuff
  ==============================================================================
  ==============================================================================
  ==============================================================================
*/

#undef NCP_CALL
#define NCP_CALL(s) do {				\
    ncpStatus = (s);					\
    if (ncpStatus != 0) {				\
      printf("ncpStatus=%d\n", (int) ncpStatus);	\
      printf("%s:%s:%d\n",				\
	     __FILE__, __FUNCTION__, __LINE__);		\
      goto ncp_return;					\
    }							\
  } while (0);

/*
  ------------------------------------------------------------------------------
  initialize_memory_node
*/

static int
initialize_memory_node(int node)
{
	int ncpStatus = 0;

	/* smcN init */
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x00,       0x00000600));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x04,       0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x08,       0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x0c,       0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x10,       0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x14,       0x0000000a));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x18,       0x0002d362));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x1c,       0x00071073));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x20,       0x091a0200));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x24,       0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x28,       0x04040000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x2c,       0x2e000600));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x30,       0x0d070720));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x34,       0x04070721));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x38,       0x00fde70e));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x3c,       0x000e0505));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x40,       0x008b0e0d));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x44,       0x0101010e));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x48,       0x0d031b01));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x4c,       0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x50,       0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x54,       0x01010000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x58,       0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x5c,       0x24000065));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x60,       0x00001370));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x64,       0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x68,       0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x6c,       0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x70,       0x13000154));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x74,       0x00001367));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x78,       0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x7c,       0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x80,       0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x84,       0x00000fff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x88,       0x00080000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x8c,       0x030015b4));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x90,       0x1004010c));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x94,       0x00001020));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x98,       0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x9c,       0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0xa0,       0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0xa4,      0x00150100/*0x00f10100*/));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0xa8,      0x00000186/*0x00001c2e*/));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0xac,      0x00000005));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0xb0,      0x00170006));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0xb4,      0x00fa0200));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0xb8,      0x00010000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0xbc,      0x000a0a00));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0xc0,      0x02000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0xc4,      0x001f0403));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0xc8,      0x00040003));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0xcc,      0x00000007));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0xd0,      0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0xd4,      0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0xd8,      0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0xdc,      0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0xe0,      0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0xe4,      0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0xe8,      0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0xec,      0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0xf0,      0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0xf4,      0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0xf8,      0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0xfc,      0x00000000));

	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x100,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x104,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x108,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x10c,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x110,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x114,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x118,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x11c,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x120,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x124,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x128,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x12c,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x130,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x134,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x138,     0x00000e14));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x13c,     0x00000046));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x140,     0x00000020));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x144,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x148,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x14c,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x150,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x154,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x158,     0x00000e14));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x15c,     0x00000046));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x160,     0x00000020));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x164,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x168,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x16c,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x170,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x174,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x178,     0x01010000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x17c,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x180,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x184,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x188,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x18c,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x190,     0x00000000));
	if(sysmem->enableECC)
	{
		NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x194,     0x00000001));
	}
	else
	{
		NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x194,     0x00000000));
	}
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x198,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x19c,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x1a0,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x1a4,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x1a8,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x1ac,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x1b0,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x1b4,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x1b8,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x1bc,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x1c0,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x1c4,     0x00025100));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x1c8,     0x004b0129));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x1cc,     0x00000200));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x1d0,     0x00000040));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x1d4,     0x03010100));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x1d8,     0x0a000001));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x1dc,     0x0101ffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x1e0,     0x01010101));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x1e4,     0x01010101));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x1e8,     0x00000108));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x1ec,     0x00010c0f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x1f0,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x1f4,     0x01000100));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x1f8,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x1fc,     0x00000000));

	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x200,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x204,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x208,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x20c,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x210,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x214,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x218,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x21c,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x220,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x224,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x228,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x22c,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x230,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x234,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x238,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x23c,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x240,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x244,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x248,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x24c,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x250,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x254,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x258,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x25c,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x260,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x264,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x268,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x26c,     0x02040108));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x270,     0x01060608));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x274,     0x02020400));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x278,     0x02000202));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x27c,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x280,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x284,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x288,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x28c,     0x280d0000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x290,     0x01000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x294,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x298,     0x000f0001));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x29c,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x2a0,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x2a4,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x2a8,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x2ac,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x2b0,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x2b4,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x2b8,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x2bc,     0x01000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x2c0,     0x00000001));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x2c4,     0x00000100));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x2c8,     0x00010f0f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x2cc,     0x67676700));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x2d0,     0x67676767));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x2d4,     0x67676767));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x2d8,     0x67676767));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x2dc,     0x67676767));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x2e0,     0x67676767));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x2e4,     0x67676767));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x2e8,     0x67676767));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x2ec,     0x67676767));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x2f0,     0x08000067));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x2f4,     0x00010008));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x2f8,     0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x2fc,     0x00ffffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x300,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x304,        0x00ffffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x308,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x30c,        0x00ffffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x310,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x314,        0x00ffffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x318,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x31c,        0x00ffffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x320,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x324,        0x00ffffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x328,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x32c,        0x00ffffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x330,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x334,        0x00ffffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x338,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x33c,        0x00ffffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x340,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x344,        0x00ffffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x348,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x34c,        0x00ffffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x350,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x354,        0x00ffffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x358,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x35c,        0x00ffffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x360,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x364,        0x00ffffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x368,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x36c,        0x00ffffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x370,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x374,        0x03ffffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x378,        0xffffffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x37c,        0x000f000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x380,        0x00ffff03));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x384,        0x000fffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x388,        0x0003000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x38c,        0xffffffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x390,        0x000f000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x394,        0x00ffff03));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x398,        0x000fffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x39c,        0x0003000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x3a0,        0xffffffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x3a4,        0x000f000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x3a8,        0x00ffff03));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x3ac,        0x000fffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x3b0,        0x0003000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x3b4,        0xffffffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x3b8,        0x000f000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x3bc,        0x00ffff03));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x3c0,        0x000fffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x3c4,        0x0003000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x3c8,        0xffffffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x3cc,        0x000f000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x3d0,        0x00ffff03));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x3d4,        0x000fffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x3d8,        0x0003000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x3dc,        0xffffffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x3e0,        0x000f000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x3e4,        0x00ffff03));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x3e8,        0x000fffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x3ec,        0x0003000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x3f0,        0xffffffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x3f4,        0x000f000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x3f8,        0x00ffff03));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x3fc,        0x000fffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x400,        0x0003000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x404,        0xffffffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x408,        0x000f000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x40c,        0x00ffff03));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x410,        0x000fffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x414,        0x0000000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x418,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x41c,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x420,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x424,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x428,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x42c,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x430,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x434,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x438,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x43c,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x440,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x444,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x448,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x44c,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x450,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x454,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x458,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x45c,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x460,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x464,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x468,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x46c,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x470,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x474,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x478,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x47c,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x480,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x484,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x488,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x48c,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x490,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x494,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x498,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x49c,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x4a0,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x4a4,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x4a8,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x4ac,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x4b0,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x4b4,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x4b8,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x4bc,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x4c0,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x4c4,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x4c8,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x4cc,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x4d0,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x4d4,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x4d8,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x4dc,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x4e0,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x4e4,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x4e8,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x4ec,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x4f0,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x4f4,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x4f8,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x4fc,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x500,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x504,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x508,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x50c,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x510,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x514,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x518,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x51c,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x520,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x524,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x528,        0x00000f00));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x52c,        0x00385c00));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x530,        0x02000200));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x534,        0x02000200));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x538,        0x0000385c));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x53c,        0x000119cc));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x540,        0x0002090d));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x544,        0x000a0a01));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x548,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x54c,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x550,        0x00000f0a));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x554,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x558,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x55c,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x560,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x564,        0x0c010000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x568,        0x00000108));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x56c,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x570,        0x0000000a));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x574,        0x00000e14));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x578,        0x00000046));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x57c,        0x00000020));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x580,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x584,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x588,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x58c,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x590,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x594,        0x00000e14));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x598,        0x00000046));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x59c,        0x00000020));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x5a0,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x5a4,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x5a8,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x5ac,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x5b0,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x5b4,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x5b8,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x5bc,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x5c0,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x5c4,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x5c8,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x5cc,        0x01040200));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x5d0,        0x67676708));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x5d4,        0x67676767));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x5d8,        0x67676767));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x5dc,        0x67676767));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x5e0,        0x67676767));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x5e4,        0x67676767));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x5e8,        0x67676767));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x5ec,        0x67676767));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x5f0,        0x67676767));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x5f4,        0x00000067));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x5f8,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x5fc,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x600,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x604,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x608,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x60c,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x610,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x614,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x618,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x61c,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x620,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x624,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x628,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x62c,        0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x630,        0x01000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x634,        0x00000000));

	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 1),0x000,        0x00000003));

	/* CFG_FPGA_PHY_LATENCY setup RL=6, WL=6 tomatch dll disable mode */
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 1),0x004,        0x00000066));

	/* CFG_FPGA_PHY_LVL_RESP_DLYS 0x22.0x1.0x00c 0x00000507 not necessary unless attempting training */

	/* CFG_FPGA_PHY_BYTELNx_DLYS set the fixed sampling point for DRAM reads */
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 1),0x010,        0x00000202));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 1),0x020,        0x00000202));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 1),0x030,        0x00000202));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 1),0x040,        0x00000202));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 1),0x050,        0x00000202));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 1),0x060,        0x00000202));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 1),0x070,        0x00000202));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 1),0x080,        0x00000202));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 1),0x090,        0x00000202));

	/* start MC init operation */
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x000,        0x00000601));

	/* poll for memory init operation */
	NCP_CALL(ncr_poll(NCP_REGION_ID(node, 0), 0x5b8,  0x0100,  0x0100,  1000000,  10000));

	/*  start DFI init 0x22.0x0.0x5f8 0x80000000
	    poll for DFI init complete ncpPoll -l 10000 -t 1000000 0x22.0x0.0x5b8 0x40000000 0x0100 */

	/* setup value for MR1 */
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x144,        0x00000003));
	/* writemodereg */
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x0e0,        0x02800001));
	/* setup value for MR0 */
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x144,        0x00001a20));
	/* writemodereg */
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x0e0,        0x02800000));
	/* setup value for MR2 */
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x144,        0x00000008));
	/* writemodereg */
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0),0x0e0,        0x02800002));

ncp_return:

	return ncpStatus;
}

/*
  ------------------------------------------------------------------------------
  initialize_elm
*/

static int
initialize_elm(void)
{
	unsigned long value;

	/*
	 * TEMP HACK: we re-use the cacheDisable config attribute
	 * to disable initializing the ELM munge registers 
	 */

	/*if (0 == sysmem->syscach) {*/
		/* set ELM munge regsiter */
		writel(0x0380ffff, (ELM0 + 0x1c));
		writel(0x0380ffff, (ELM1 + 0x1c));
		/*}*/

	if (sysmem->enableECC) {
		/* 
		 * initialize all of sysmem through the ELMs
		 * start each ELM before checking completion so they
		 * all run in parallel
		 */

		/* elm0 */
		writel(0x00000000, (ELM0 + 0x40));
		writel(0x01ffffff, (ELM0 + 0x44));
		writel(0x00000000, (ELM0 + 0x48));

		/* elm1 */
		writel(0x00000000, (ELM1 + 0x40));
		writel(0x01ffffff, (ELM1 + 0x44));
		writel(0x00000000, (ELM1 + 0x48));

		/* poll elm0 for completion */
		do {
			value = readl(ELM0 + 0x44);
			udelay(100);
			WATCHDOG_RESET();
		} while (0 != (value & 0x1fffffff));

		/* poll elm1 for completion */
		do {
			value = readl(ELM1 + 0x44);
			udelay(100);
			WATCHDOG_RESET();
		} while (0 != (value & 0x1fffffff));
	}

	return 0;
}

/*
  ==============================================================================
  ==============================================================================
  ==============================================================================
  Global Stuff
  ==============================================================================
  ==============================================================================
  ==============================================================================
*/

/*
  ------------------------------------------------------------------------------
  sysmem_init
*/

int
sysmem_init(void)
{
	int rc;

#ifdef SINGLE_SMEM_MODE

	unsigned long offset;

	offset = DICKENS | (0x20 << 16);
	writel(0x4, (offset + 0x8));

	offset = DICKENS | (0x21 << 16);
	writel(0x4, (offset + 0x8));

	offset = DICKENS | (0x22 << 16);
	writel(0x4, (offset + 0x8));

	offset = DICKENS | (0x23 << 16);
	writel(0x4, (offset + 0x8));

	offset = DICKENS | (0x24 << 16);
	writel(0x4, (offset + 0x8));

	offset = DICKENS | (0x25 << 16);
	writel(0x4, (offset + 0x8));

	offset = DICKENS | (0x26 << 16);
	writel(0x4, (offset + 0x8));

	offset = DICKENS | (0x27 << 16);
	writel(0x4, (offset + 0x8));

#endif

/* #define DISPLAY_PARAMETERS */
#ifdef DISPLAY_PARAMETERS
    {
      unsigned *p;
        int i;
    	printf("-- -- Sysmem Parameters \n");

        printf("version=0x%08x\n", sysmem->version);
        printf("ddrClockSpeedMHz=0x%08x\n", sysmem->ddrClockSpeedMHz);
        printf("auto_detect=0x%08x\n", sysmem->auto_detect);
        printf("num_interfaces=0x%08x\n", sysmem->num_interfaces);
        printf("num_ranks_per_interface=0x%08x\n", sysmem->num_ranks_per_interface);
        printf("primary_bus_width=0x%08x\n", sysmem->primary_bus_width);
        printf("topology=0x%08x\n", sysmem->topology);
        printf("min_ctrl_roundtrip_delay=0x%08x\n", sysmem->min_ctrl_roundtrip_delay);
	printf("phy_rdlat=0x%08x\n", sysmem->phy_rdlat);
        printf("added_rank_switch_delay=0x%08x\n", sysmem->added_rank_switch_delay);
        printf("zqcs_interval=0x%08x\n", sysmem->zqcs_interval);
        printf("enableECC=0x%08x\n", sysmem->enableECC);
        printf("enable_runtime_updates=0x%08x\n", sysmem->enable_runtime_updates);
        printf("dramPrechargePolicy=0x%08x\n", sysmem->dramPrechargePolicy);
        printf("open_page_size=0x%08x\n", sysmem->open_page_size);
        printf("syscacheControl=0x%08x\n", sysmem->syscacheControl);
        printf("sdram_device_density=0x%08x\n", sysmem->sdram_device_density);
        printf("sdram_device_width=0x%08x\n", sysmem->sdram_device_width);
        printf("CAS_latency=0x%08x\n", sysmem->CAS_latency);
        printf("CAS_write_latency=0x%08x\n", sysmem->CAS_write_latency);
        printf("address_mirroring=0x%08x\n", sysmem->address_mirroring);
        printf("registeredDIMM=0x%08x\n", sysmem->registeredDIMM);
        printf("rdimm_ctl_0_0=0x%08x\n", sysmem->rdimm_ctl_0_0);
        printf("rdimm_ctl_0_1=0x%08x\n", sysmem->rdimm_ctl_0_1);
        printf("rdimm_msic=0x%08x\n", sysmem->rdimm_misc);
        printf("write_ODT_ctl=0x%08x\n", sysmem->write_ODT_ctl);
        printf("read_ODT_ctl=0x%08x\n", sysmem->read_ODT_ctl);
        printf("single_bit_mpr=0x%08x\n", sysmem->single_bit_mpr);
        printf("high_temp_dram=0x%08x\n", sysmem->high_temp_dram);
            
        for (i = 0; i < 2; i++) {

          p = (unsigned *) sysmem->per_mem[i].sdram_rtt_nom;
          printf("RTTnom=0x%08x\n", *p++);
          printf("RTTwr=0x%08x\n", *p++);
          printf("drvimp=0x%08x\n", *p++);

          printf("phy_min_cal_delay=0x%08x\n", sysmem->per_mem[i].phy_min_cal_delay);
          printf("phy_adr_phase_select=0x%08x\n", sysmem->per_mem[i].phy_adr_phase_select);
          printf("phy_dp_io_vref_set=0x%08x\n", sysmem->per_mem[i].phy_dp_io_vref_set);
          printf("phy_adr_io_vref_set=0x%08x\n", sysmem->per_mem[i].phy_adr_io_vref_set);
          printf("phy_rdlvl_cmp_even=0x%08x\n", sysmem->per_mem[i].phy_rdlvl_cmp_even);
          printf("phy_rdlvl_cmp_odd=0x%08x\n", sysmem->per_mem[i].phy_rdlvl_cmp_odd);
          printf("phy_write_align_finetune=0x%08x\n", sysmem->per_mem[i].phy_write_align_finetune);
        }
    }
#endif

	rc = initialize_memory_node(0x22);

	if (0 != rc)
		return -1;

	rc = initialize_memory_node(0xf);

	if (0 != rc)
		return -1;

	rc = initialize_memory_node(0x23);

	if (0 != rc)
		return -1;

	rc = initialize_memory_node(0x24);

	if (0 != rc)
		return -1;

	rc = initialize_elm();

	if (0 != rc)
		return -1;

	return 0;
}
