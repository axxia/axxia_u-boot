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
	unsigned long value32;

	/* smc0 init */
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 255), 0x10, 0x0000000b));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 1), 0x000, 0x00000002));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x000, 0x00010100));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x004, 0x01010100));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x008, 0x00000100));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x00c, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x010, 0x00000001));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x014, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x018, 0x00010000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x01c, 0x00000001));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x020, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x024, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x028, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x02c, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x030, 0x01000001));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x034, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x038, 0x00010100));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x03c, 0x00000000));
    
	if (0 != sysmem->enableECC) {
		NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x694, 0x00000001));
	} else {
		NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x694, 0x00000000));
	}
    
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x054, 0x02000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x058, 0x03ff0000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x05c, 0x00ff0000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x060, 0x05000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x064, 0x00020706));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x068, 0x00000a00));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x078, 0x0c000000));

	switch (sysmem->topology)
	{
	case 1: /* single-rank */
		NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x07c, 0x00060100));
		break;
	case 3: /* dual-rank */
		NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x07c, 0x00060100));
		break;
	default:
		return -1;
		break;
	}

	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x080, 0x04080000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x084, 0x02010102));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x088, 0x04000804));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x08c, 0x00000002));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x090, 0x070d0303));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x094, 0x00000909));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x098, 0x0000001a));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x09c, 0x1b0d0000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x0a0, 0x2100000d));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x0a4, 0x00002e04));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x0a8, 0x0000280d));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x0ac, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x0e8, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x0ec, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x0f0, 0x2c000300));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x0f4, 0x04000300));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x0f8, 0x00200e00));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x104, 0x004b0000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x114, 0x1c2e1c2e));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x118, 0x01860200));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x124, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x148, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x150, 0x00060200));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x154, 0x00170000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x158, 0x020000fa));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x15c, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x174, 0x0000000a));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x178, 0x000001cf));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x17c, 0x00008000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x1f8, 0x000000ba));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x1fc, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x200, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x204, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x208, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x20c, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x210, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x214, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x218, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x21c, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x220, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x224, 0x00000001));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x228, 0x00000001));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x22c, 0x00000001));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x230, 0x00000001));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x234, 0x00000001));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x238, 0x00000001));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x23c, 0x00000001));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x240, 0x00000001));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x244, 0x00000001));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x248, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x24c, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x250, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x254, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x258, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x25c, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x260, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x264, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x268, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x26c, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x270, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x274, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x278, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x27c, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x288, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x28c, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x290, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x294, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x298, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x29c, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x2a0, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x2a4, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x2a8, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x2ac, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x2d0, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x2d4, 0x00010000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x2d8, 0x02020001));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x2dc, 0x00000104));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x2e0, 0x00020d02));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x2e4, 0x000a000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x2e8, 0x02510129));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x2ec, 0x0e140e14));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x2f0, 0x0e140e14));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x2f4, 0x00460046));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x2f8, 0x00460046));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x2fc, 0x00200020));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x300, 0x00200020));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x304, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x308, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x37c, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x380, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x384, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x388, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x38c, 0x02000404));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x390, 0x02000200));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x394, 0x0000fde7));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x398, 0x02000015));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x39c, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x3a0, 0x07070000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x3a8, 0x24101065));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x3ac, 0x00001370));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x3b0, 0x00000003));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x3b4, 0x13030154));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x3b8, 0x00001367));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x3bc, 0x000fff0c));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x3c0, 0x00000800));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x3c4, 0x000015b4));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x3c8, 0x00000005));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x3cc, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x3d0, 0x00000a0a));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x3d4, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x3e0, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x3e4, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x3e8, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x3ec, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x3f0, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x3f4, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x3f8, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x3fc, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x400, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x404, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x408, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x40c, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x410, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x414, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x458, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x45c, 0x00000001));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x460, 0x003fffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x464, 0x00000003));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x468, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x46c, 0x003fffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x470, 0x00000003));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x474, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x478, 0x003fffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x47c, 0x00000003));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x480, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x484, 0x003fffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x488, 0x00000003));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x518, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x51c, 0x000119cc));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x520, 0x01010002));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x524, 0x01010100));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x528, 0x0000000b));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x52c, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x534, 0x01020100));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x538, 0x08010000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x53c, 0x010e0d00));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x540, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x544, 0x00000040));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x548, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x54c, 0x06060000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x550, 0x00000001));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x554, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x558, 0x00000202));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x55c, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x560, 0x003fffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x564, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x568, 0x003fffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x56c, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x570, 0x003fffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x574, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x578, 0x003fffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x57c, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x580, 0x003fffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x584, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x588, 0x003fffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x58c, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x590, 0x003fffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x594, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x598, 0x003fffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x59c, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x5a0, 0x003fffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x5a4, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x5a8, 0x003fffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x5ac, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x5b0, 0x003fffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x5b4, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x5b8, 0x003fffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x5bc, 0xffffffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x5c0, 0xffff0000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x5c4, 0x0000ffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x5c8, 0xffffffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x5cc, 0xffff0000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x5d0, 0x0000ffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x5d4, 0x00ffff03));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x5d8, 0x0000ffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x5dc, 0x00ffff03));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x5e0, 0x0000ffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x5e4, 0x00ffff03));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x5e8, 0x0000ffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x5ec, 0x00ffff03));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x5f0, 0x0000ffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x5f4, 0x00ffff03));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x5f8, 0x0000ffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x5fc, 0x00ffff03));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x600, 0x0000ffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x604, 0x00ffff03));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x608, 0x0000ffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x60c, 0x00ffff03));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x610, 0x0000ffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x614, 0x00ffff03));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x618, 0x0000ffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x61c, 0x00ffff03));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x620, 0x0000ffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x624, 0x00ffff03));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x628, 0x0000ffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x62c, 0x00ffff03));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x630, 0x0000ffff));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x634, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x638, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x63c, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x640, 0x00000f00));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x644, 0x000f000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x648, 0x000f000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x64c, 0x000f000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x650, 0x000f000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x654, 0x000f000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x658, 0x000f000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x65c, 0x000f000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x660, 0x000f000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x664, 0x000f000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x668, 0x000f000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x66c, 0x000f000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x670, 0x000f000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x674, 0x000f000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x678, 0x000f000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x67c, 0x000f000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x680, 0x0000000f));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x68c, 0x00000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x690, 0x00040001));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x694, 0x00000001));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x000, 0x01010100));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x004, 0x01010101));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x09c, 0x1b040000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x1fc, 0x80000000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x094, 0x00000809));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 1), 0x000, 0x00000003));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 1), 0x004, 0x00000066));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 1), 0x010, 0x00000202));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 1), 0x020, 0x00000202));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 1), 0x030, 0x00000202));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 1), 0x040, 0x00000202));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 1), 0x050, 0x00000202));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 1), 0x060, 0x00000202));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 1), 0x070, 0x00000202));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 1), 0x080, 0x00000202));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 1), 0x090, 0x00000202));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x030, 0x01010001));

	do {
		NCP_CALL(ncr_read32(NCP_REGION_ID(node, 0), 0x410,
				    (ncp_uint32_t *)&value32));
		value32 &= 0x100;
	} while (0 == value32);

	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x3ec, 0x00000300));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x3e8, 0x02800001));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x3ec, 0x001a2000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x3e8, 0x02800000));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x3ec, 0x00000800));
	NCP_CALL(ncr_write32(NCP_REGION_ID(node, 0), 0x3e8, 0x02800002));

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

#ifdef SINGLE_SMEM_MODE
		value = readl(ELM0 + 0x4);
		value &= 0xfffffdff;
		writel(value, (ELM0 + 0x4));
		value = readl(ELM0 + 0x4);
		printf("%s:%d - 0x%08x\n", __FILE__, __LINE__, value); /* ZZZ */
#endif


	if (sysmem->enableECC) {
		/* 
		 * initialize all of sysmem through the ELMs
		 * start each ELM before checking completion so they
		 * all run in parallel
		 */

		/* elm0 */
		writel(0x00000000, (ELM0 + 0x40));
		writel(0x00ffffff, (ELM0 + 0x44));
		writel(0x00000000, (ELM0 + 0x48));

#ifndef SINGLE_SMEM_MODE

		/* elm1 */
		writel(0x00000000, (ELM1 + 0x40));
		writel(0x00ffffff, (ELM1 + 0x44));
		writel(0x00000000, (ELM1 + 0x48));

#endif

		/* poll elm0 for completion */
		do {
			value = readl(ELM0 + 0x44);
		} while (0 != (value & 0x1fffffff));

#ifndef SINGLE_SMEM_MODE

		/* poll elm1 for completion */
		do {
			value = readl(ELM1 + 0x44);
		} while (0 != (value & 0x1fffffff));

#endif
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

	rc = initialize_memory_node(0x22);

	if (0 != rc)
		return -1;

#ifndef SINGLE_SMEM_MODE

	rc = initialize_memory_node(0xf);

	if (0 != rc)
		return -1;

#endif

	rc = initialize_elm();

	if (0 != rc)
		return -1;

	return 0;
}
