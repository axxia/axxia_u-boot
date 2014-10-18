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

int pciesrio_setcontrol(unsigned long new_control);

typedef struct {
unsigned short offset;
unsigned short value;
} rx_serdes_value_t;


/*
===============================================================================
===============================================================================
Public Interface
===============================================================================
===============================================================================
*/

/************************************************************************************
# Bits 30,29: Indicates PCIe1 controller configuration
#            0 - indicates PCIe1x4 on SerDes ch 0,1,2,3
#            1 - indicates PCIe1x2 on SerDes ch 2,3
#            2 - indicates PCIe1x1 on SerDes ch 3 
# Bits 28:26: Indicates PCIe0/SRIO controller configuration
#            0 - indicates PCIe0x4 on SerDes ch 0,1,2,3
#            1 - indicates PCIe0x2 on SerDes ch 2,3
#            2 - indicates SRIO0x2, PCIe0x2 on SerDes ch 2,3
#            4 - indicates SRIO0x2 on SerDes ch 0,1 and SRIO1x2 on ch2,3
#            5 - indicates SRIO0x1 on SerDes ch 0, SRIO1x1 on ch 2, PCIe0x1 on ch3
# Bits 25, 24: If SRIO1 is configured,
#            0 - indicates Host with ID 0,
#            1 - indicates Host with ID 1,
#            2 - indicates not a host (agent)
#            3 - RESERVED
# Bit 23: If PCIe1 is configured,
#            0 - indicates END_POINT
#            1 - indicates ROOT_COMPLEX
# Bit 22: If PCIe0 is configured,
#            0 - indicates END_POINT
#            1 - indicates ROOT_COMPLEX
# Bits 20, 21: If SRIO0 is configured,
#            0 - indicates Host with ID 0,
#            1 - indicates Host with ID 1,
#            2 - indicates not a host (agent)
#            3 - RESERVED
# Bit 10 : Enable SRIO1 controller
# Bits 9:7 : SRIO1 speed selection
#       0 -  indicates 1.25 Gbps
#       1 -  indicates 2.5 Gbps
#       2 -  indicates 3.125 Gbps
#       3 -  indicates 5 Gbps
#       4 -  indicates 6.25 Gbps
# Bits 6:4 : SRIO0 speed selection
#       0 -  indicates 1.25 Gbps
#       1 -  indicates 2.5 Gbps
#       2 -  indicates 3.125 Gbps
#       3 -  indicates 5 Gbps
#       4 -  indicates 6.25 Gbps
# Bit  3  : Enable SRIO0 controller
# Bit  2  : Enable PCIe1 controller
# Bit  0  : Enable PCIe0 controller


Control         Description

0x00000001      PEI0 EP x4 L[3:0]
0x00400001      PEI0 RC x4 L[3:0]
0x00000004      PEI1 EP x4 L[3:0]
0x00800004      PEI1 RC x4 L[3:0]

0x00000005      PEI0 EP x4 L[3:0] PEI1 EP x4 L[3:0]
0x00400005      PEI0 RC x4 L[3:0] PEI1 EP x4 L[3:0]
0x00800005      PEI0 EP x4 L[3:0] PEI1 RC x4 L[3:0]
0x00c00005      PEI0 RC x4 L[3:0] PEI1 RC x4 L[3:0]

0x20000005      PEI0 EP x4 L[3:0] PEI1 EP x2 L[3:2]
0x20400005      PEI0 RC x4 L[3:0] PEI1 EP x2 L[3:2]
0x20800005      PEI0 EP x4 L[3:0] PEI1 RC x2 L[3:2]
0x20c00005      PEI0 RC x4 L[3:0] PEI1 RC x2 L[3:2]

0x40000005      PEI0 EP x4 L[3:0] PEI1 EP x1 L[3]
0x40400005      PEI0 RC x4 L[3:0] PEI1 EP x1 L[3]
0x40800005      PEI0 EP x4 L[3:0] PEI1 RC x1 L[3]
0x40c00005      PEI0 RC x4 L[3:0] PEI1 RC x1 L[3]

0x04000001      PEI0 EP x2 L[3:2]
0x04400001      PEI0 RC x2 L[3:2]
0x20000004      PEI1 EP x2 L[3:2]
0x20800004      PEI1 RC x2 L[3:2]

0x04000005      PEI0 EP x2 L[3:2] PEI1 EP x4 L[3:0]
0x04400005      PEI0 RC x2 L[3:2] PEI1 EP x4 L[3:0]
0x04800005      PEI0 EP x2 L[3:2] PEI1 RC x4 L[3:0]
0x04c00005      PEI0 RC x2 L[3:2] PEI1 RC x4 L[3:0]

0x24000005      PEI0 EP x2 L[3:2] PEI1 EP x2 L[3:2]
0x24400005      PEI0 RC x2 L[3:2] PEI1 EP x2 L[3:2]
0x24800005      PEI0 EP x2 L[3:2] PEI1 RC x2 L[3:2]
0x24c00005      PEI0 RC x2 L[3:2] PEI1 RC x2 L[3:2]

0x44000005      PEI0 EP x2 L[3:2] PEI1 EP x1 L[3]
0x44400005      PEI0 RC x2 L[3:2] PEI1 EP x1 L[3]
0x44800005      PEI0 EP x2 L[3:2] PEI1 RC x1 L[3]
0x44c00005      PEI0 RC x2 L[3:2] PEI1 RC x1 L[3]

0x08000009      PEI0 EP x2 L[3:2] SRIO0 x2 L[1:0] [SRIO0 host ID0]
0x08400009      PEI0 RC x2 L[3:2] SRIO0 x2 L[1:0] [SRIO0 host ID0]

0x08100009      PEI0 EP x2 L[3:2] SRIO0 x2 L[1:0] [SRIO0 host ID1]
0x08500009      PEI0 RC x2 L[3:2] SRIO0 x2 L[1:0] [SRIO0 host ID1]

0x08200009      PEI0 EP x2 L[3:2] SRIO0 x2 L[1:0] [SRIO0 not a host]
0x08600009      PEI0 RC x2 L[3:2] SRIO0 x2 L[1:0] [SRIO0 not a host]

0x0800000d      PEI0 EP x2 L[3:2] SRIO0 x2 L[1:0] PEI1 EP x4 L[3:0] [SRIO0 host ID0]
0x0810000d      PEI0 EP x2 L[3:2] SRIO0 x2 L[1:0] PEI1 EP x4 L[3:0] [SRIO0 host ID1]
0x0820000d      PEI0 EP x2 L[3:2] SRIO0 x2 L[1:0] PEI1 EP x4 L[3:0] [SRIO0 not a host]

0x0880000d      PEI0 EP x2 L[3:2] SRIO0 x2 L[1:0] PEI1 RC x4 L[3:0] [SRIO0 host ID0]
0x0890000d      PEI0 EP x2 L[3:2] SRIO0 x2 L[1:0] PEI1 RC x4 L[3:0] [SRIO0 host ID1]
0x08a0000d      PEI0 EP x2 L[3:2] SRIO0 x2 L[1:0] PEI1 RC x4 L[3:0] [SRIO0 not a host]

0x0840000d      PEI0 RC x2 L[3:2] SRIO0 x2 L[1:0] PEI1 EP x4 L[3:0] [SRIO0 host ID0]
0x0850000d      PEI0 RC x2 L[3:2] SRIO0 x2 L[1:0] PEI1 EP x4 L[3:0] [SRIO0 host ID1]
0x0860000d      PEI0 RC x2 L[3:2] SRIO0 x2 L[1:0] PEI1 EP x4 L[3:0] [SRIO0 not a host]

0x08c0000d      PEI0 RC x2 L[3:2] SRIO0 x2 L[1:0] PEI1 RC x4 L[3:0] [SRIO0 host ID0]
0x08d0000d      PEI0 RC x2 L[3:2] SRIO0 x2 L[1:0] PEI1 RC x4 L[3:0] [SRIO0 host ID1]
0x08e0000d      PEI0 RC x2 L[3:2] SRIO0 x2 L[1:0] PEI1 RC x4 L[3:0] [SRIO0 not a host]

0x2800000d      PEI0 EP x2 L[3:2] SRIO0 x2 L[1:0] PEI1 EP x2 L[3:2] [SRIO0 host ID0]
0x2810000d      PEI0 EP x2 L[3:2] SRIO0 x2 L[1:0] PEI1 EP x2 L[3:2] [SRIO0 host ID1]
0x2820000d      PEI0 EP x2 L[3:2] SRIO0 x2 L[1:0] PEI1 EP x2 L[3:2] [SRIO0 not a host]

0x2840000d      PEI0 RC x2 L[3:2] SRIO0 x2 L[1:0] PEI1 EP x2 L[3:2] [SRIO0 host ID0]
0x2850000d      PEI0 RC x2 L[3:2] SRIO0 x2 L[1:0] PEI1 EP x2 L[3:2] [SRIO0 host ID1]
0x2860000d      PEI0 RC x2 L[3:2] SRIO0 x2 L[1:0] PEI1 EP x2 L[3:2] [SRIO0 not a host]

0x2880000d      PEI0 EP x2 L[3:2] SRIO0 x2 L[1:0] PEI1 RC x2 L[3:2] [SRIO0 host ID0]
0x2890000d      PEI0 EP x2 L[3:2] SRIO0 x2 L[1:0] PEI1 RC x2 L[3:2] [SRIO0 host ID1]
0x28a0000d      PEI0 EP x2 L[3:2] SRIO0 x2 L[1:0] PEI1 RC x2 L[3:2] [SRIO0 not a host]

0x28c0000d      PEI0 RC x2 L[3:2] SRIO0 x2 L[1:0] PEI1 RC x2 L[3:2] [SRIO0 host ID0]
0x28d0000d      PEI0 RC x2 L[3:2] SRIO0 x2 L[1:0] PEI1 RC x2 L[3:2] [SRIO0 host ID1]
0x28e0000d      PEI0 RC x2 L[3:2] SRIO0 x2 L[1:0] PEI1 RC x2 L[3:2] [SRIO0 not a host] 

0x4800000d      PEI0 EP x2 L[3:2] SRIO0 x2 L[1:0] PEI1 EP x1 L[3] [SRIO0 host ID0]
0x4810000d      PEI0 EP x2 L[3:2] SRIO0 x2 L[1:0] PEI1 EP x1 L[3] [SRIO0 host ID1]
0x4820000d      PEI0 EP x2 L[3:2] SRIO0 x2 L[1:0] PEI1 EP x1 L[3] [SRIO0 not a host]

0x4840000d      PEI0 RC x2 L[3:2] SRIO0 x2 L[1:0] PEI1 EP x1 L[3] [SRIO0 host ID0]
0x4850000d      PEI0 RC x2 L[3:2] SRIO0 x2 L[1:0] PEI1 EP x1 L[3] [SRIO0 host ID1]
0x4860000d      PEI0 RC x2 L[3:2] SRIO0 x2 L[1:0] PEI1 EP x1 L[3] [SRIO0 not a host]

0x4880000d      PEI0 EP x2 L[3:2] SRIO0 x2 L[1:0] PEI1 RC x1 L[3] [SRIO0 host ID0]
0x4890000d      PEI0 EP x2 L[3:2] SRIO0 x2 L[1:0] PEI1 RC x1 L[3] [SRIO0 host ID1]
0x48a0000d      PEI0 EP x2 L[3:2] SRIO0 x2 L[1:0] PEI1 RC x1 L[3] [SRIO0 not a host]

0x48c0000d      PEI0 RC x2 L[3:2] SRIO0 x2 L[1:0] PEI1 RC x1 L[3] [SRIO0 host ID0]
0x48d0000d      PEI0 RC x2 L[3:2] SRIO0 x2 L[1:0] PEI1 RC x1 L[3] [SRIO0 host ID1]
0x48e0000d      PEI0 RC x2 L[3:2] SRIO0 x2 L[1:0] PEI1 RC x1 L[3] [SRIO0 not a host]

0x10000408      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID0, SRIO1 host ID0]
0x11000408      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID0, SRIO1 host ID1]
0x12000408      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID0, SRIO1 not a host]
0x10100408      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID1, SRIO1 host ID0]
0x11100408      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID1, SRIO1 host ID1]
0x12100408      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID1, SRIO1 not a host]
0x10200408      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 not a host, SRIO1 host ID0]
0x11200408      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 not a host, SRIO1 host ID1]
0x12200408      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 not a host, SRIO1 not a host]


0x1000040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID0, SRIO1 host ID0] PEI1 EP x4 L[3:0]
0x1080040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID0, SRIO1 host ID0] PEI1 RC x4 L[3:0]

0x1100040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID0, SRIO1 host ID1] PEI1 EP x4 L[3:0]
0x1180040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID0, SRIO1 host ID1] PEI1 RC x4 L[3:0]

0x1200040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID0, SRIO1 not a host] PEI1 EP x4 L[3:0]
0x1280040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID0, SRIO1 not a host] PEI1 RC x4 L[3:0]

0x1010040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID1, SRIO1 host ID0] PEI1 EP x4 L[3:0]
0x1090040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID1, SRIO1 host ID0] PEI1 RC x4 L[3:0]

0x1110040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID1, SRIO1 host ID1] PEI1 EP x4 L[3:0]
0x1190040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID1, SRIO1 host ID1] PEI1 RC x4 L[3:0]

0x1210040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID1, SRIO1 not a host] PEI1 EP x4 L[3:0]
0x1290040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID1, SRIO1 not a host] PEI1 RC x4 L[3:0]

0x1020040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 not a host, SRIO1 host ID0] PEI1 EP x4 L[3:0]
0x10a0040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 not a host, SRIO1 host ID0] PEI1 RC x4 L[3:0]

0x1120040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 not a host, SRIO1 host ID1] PEI1 EP x4 L[3:0]
0x11a0040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 not a host, SRIO1 host ID1] PEI1 RC x4 L[3:0]

0x1220040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 not a host, SRIO1 not a host] PEI1 EP x4 L[3:0]
0x12a0040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 not a host, SRIO1 not a host] PEI1 RC x4 L[3:0]

0x3000040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID0, SRIO1 host ID0] PEI1 EP x2 L[3:2]
0x3080040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID0, SRIO1 host ID0] PEI1 RC x2 L[3:2]

0x3100040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID0, SRIO1 host ID1] PEI1 EP x2 L[3:2]
0x3180040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID0, SRIO1 host ID1] PEI1 RC x2 L[3:2]

0x3200040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID0, SRIO1 not a host] PEI1 EP x2 L[3:2]
0x3280040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID0, SRIO1 not a host] PEI1 RC x2 L[3:2]

0x3010040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID1, SRIO1 host ID0] PEI1 EP x2 L[3:2]
0x3090040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID1, SRIO1 host ID0] PEI1 RC x2 L[3:2]

0x3110040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID1, SRIO1 host ID1] PEI1 EP x2 L[3:2]
0x3190040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID1, SRIO1 host ID1] PEI1 RC x2 L[3:2]

0x3210040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID1, SRIO1 not a host] PEI1 EP x2 L[3:2]
0x3290040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID1, SRIO1 not a host] PEI1 RC x2 L[3:2]

0x3020040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 not a host, SRIO1 host ID0] PEI1 EP x2 L[3:2]
0x30a0040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 not a host, SRIO1 host ID0] PEI1 RC x2 L[3:2]

0x3120040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 not a host, SRIO1 host ID1] PEI1 EP x2 L[3:2]
0x31a0040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 not a host, SRIO1 host ID1] PEI1 RC x2 L[3:2]

0x3220040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 not a host, SRIO1 not a host] PEI1 EP x2 L[3:2]
0x32a0040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 not a host, SRIO1 not a host] PEI1 RC x2 L[3:2]

0x5000040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID0, SRIO1 host ID0] PEI1 EP x1 L[3]
0x5080040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID0, SRIO1 host ID0] PEI1 RC x1 L[3]

0x5100040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID0, SRIO1 host ID1] PEI1 EP x1 L[3]
0x5180040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID0, SRIO1 host ID1] PEI1 RC x1 L[3]

0x5200040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID0, SRIO1 not a host] PEI1 EP x1 L[3]
0x5280040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID0, SRIO1 not a host] PEI1 RC x1 L[3]

0x5010040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID1, SRIO1 host ID0] PEI1 EP x1 L[3]
0x5090040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID1, SRIO1 host ID0] PEI1 RC x1 L[3]

0x5110040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID1, SRIO1 host ID1] PEI1 EP x1 L[3]
0x5190040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID1, SRIO1 host ID1] PEI1 RC x1 L[3]

0x5210040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID1, SRIO1 not a host] PEI1 EP x1 L[3]
0x5290040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 host ID1, SRIO1 not a host] PEI1 RC x1 L[3]

0x5020040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 not a host, SRIO1 host ID0] PEI1 EP x1 L[3]
0x50a0040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 not a host, SRIO1 host ID0] PEI1 RC x1 L[3]

0x5120040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 not a host, SRIO1 host ID1] PEI1 EP x1 L[3]
0x51a0040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 not a host, SRIO1 host ID1] PEI1 RC x1 L[3]

0x5220040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 not a host, SRIO1 not a host] PEI1 EP x1 L[3]
0x52a0040c      SRIO0 x2 L[0:1] SRIO1 x2 L[2:3] [SRIO0 not a host, SRIO1 not a host] PEI1 RC x1 L[3]

0x14000409      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID0, SRIO1 host ID0]
0x15000409      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID0, SRIO1 host ID1]
0x16000409      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID0, SRIO1 not a host]
0x14100409      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID1, SRIO1 host ID0]
0x15100409      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID1, SRIO1 host ID1]
0x16100409      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID1, SRIO1 not a host]
0x14200409      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 not a host, SRIO1 host ID0]
0x15200409      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 not a host, SRIO1 host ID1]
0x16200409      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 not a host, SRIO1 not a host]

0x14400409      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID0, SRIO1 host ID0]
0x15400409      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID0, SRIO1 host ID1]
0x16400409      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID0, SRIO1 not a host]
0x14400409      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID1, SRIO1 host ID0]
0x15400409      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID1, SRIO1 host ID1]
0x16400409      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID1, SRIO1 not a host]
0x14400409      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 not a host, SRIO1 host ID0]
0x15400409      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 not a host, SRIO1 host ID1]
0x16400409      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 not a host, SRIO1 not a host]

0x1400040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID0, SRIO1 host ID0] PEI1 EP x4 L[3:0]
0x1480040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID0, SRIO1 host ID0] PEI1 RC x4 L[3:0]
0x1440040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID0, SRIO1 host ID0] PEI1 EP x4 L[3:0]
0x14c0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID0, SRIO1 host ID0] PEI1 RC x4 L[3:0]

0x1500040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID0, SRIO1 host ID1] PEI1 EP x4 L[3:0]
0x1580040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID0, SRIO1 host ID1] PEI1 RC x4 L[3:0]
0x1540040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID0, SRIO1 host ID1] PEI1 EP x4 L[3:0]
0x15c0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID0, SRIO1 host ID1] PEI1 RC x4 L[3:0]

0x1600040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID0, SRIO1 not a host] PEI1 EP x4 L[3:0]
0x1680040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID0, SRIO1 not a host] PEI1 RC x4 L[3:0]
0x1640040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID0, SRIO1 not a host] PEI1 EP x4 L[3:0]
0x16c0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID0, SRIO1 not a host] PEI1 RC x4 L[3:0]

0x1410040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID1, SRIO1 host ID0] PEI1 EP x4 L[3:0]
0x1490040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID1, SRIO1 host ID0] PEI1 RC x4 L[3:0]
0x1450040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID1, SRIO1 host ID0] PEI1 EP x4 L[3:0]
0x14d0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID1, SRIO1 host ID0] PEI1 RC x4 L[3:0]

0x1510040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID1, SRIO1 host ID1] PEI1 EP x4 L[3:0]
0x1590040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID1, SRIO1 host ID1] PEI1 RC x4 L[3:0]
0x1550040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID1, SRIO1 host ID1] PEI1 EP x4 L[3:0]
0x15d0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID1, SRIO1 host ID1] PEI1 RC x4 L[3:0]

0x1610040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID1, SRIO1 not a host] PEI1 EP x4 L[3:0]
0x1690040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID1, SRIO1 not a host] PEI1 RC x4 L[3:0]
0x1650040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID1, SRIO1 not a host] PEI1 EP x4 L[3:0]
0x16d0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID1, SRIO1 not a host] PEI1 RC x4 L[3:0]

0x1420040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 not a host, SRIO1 host ID0] PEI1 EP x4 L[3:0]
0x14a0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 not a host, SRIO1 host ID0] PEI1 RC x4 L[3:0]
0x1460040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 not a host, SRIO1 host ID0] PEI1 EP x4 L[3:0]
0x14e0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 not a host, SRIO1 host ID0] PEI1 RC x4 L[3:0]

0x1520040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 not a host, SRIO1 host ID1] PEI1 EP x4 L[3:0]
0x15a0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 not a host, SRIO1 host ID1] PEI1 RC x4 L[3:0]
0x1560040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 not a host, SRIO1 host ID1] PEI1 EP x4 L[3:0]
0x15e0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 not a host, SRIO1 host ID1] PEI1 RC x4 L[3:0]

0x1620040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 not a host, SRIO1 not a host] PEI1 EP x4 L[3:0]
0x16a0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 not a host, SRIO1 not a host] PEI1 RC x4 L[3:0]
0x1660040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 not a host, SRIO1 not a host] PEI1 EP x4 L[3:0]
0x16e0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 not a host, SRIO1 not a host] PEI1 RC x4 L[3:0]

0x3400040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID0, SRIO1 host ID0] PEI1 EP x2 L[3:2]
0x3480040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID0, SRIO1 host ID0] PEI1 RC x2 L[3:2]
0x3440040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID0, SRIO1 host ID0] PEI1 EP x2 L[3:2]
0x34c0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID0, SRIO1 host ID0] PEI1 RC x2 L[3:2]

0x3500040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID0, SRIO1 host ID1] PEI1 EP x2 L[3:2]
0x3580040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID0, SRIO1 host ID1] PEI1 RC x2 L[3:2]
0x3540040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID0, SRIO1 host ID1] PEI1 EP x2 L[3:2]
0x35c0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID0, SRIO1 host ID1] PEI1 RC x2 L[3:2]

0x3600040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID0, SRIO1 not a host] PEI1 EP x2 L[3:2]
0x3680040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID0, SRIO1 not a host] PEI1 RC x2 L[3:2]
0x3640040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID0, SRIO1 not a host] PEI1 EP x2 L[3:2]
0x36c0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID0, SRIO1 not a host] PEI1 RC x2 L[3:2]

0x3410040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID1, SRIO1 host ID0] PEI1 EP x2 L[3:2]
0x3490040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID1, SRIO1 host ID0] PEI1 RC x2 L[3:2]
0x3450040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID1, SRIO1 host ID0] PEI1 EP x2 L[3:2]
0x34d0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID1, SRIO1 host ID0] PEI1 RC x2 L[3:2]

0x3510040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID1, SRIO1 host ID1] PEI1 EP x2 L[3:2]
0x3590040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID1, SRIO1 host ID1] PEI1 RC x2 L[3:2]
0x3550040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID1, SRIO1 host ID1] PEI1 EP x2 L[3:2]
0x35d0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID1, SRIO1 host ID1] PEI1 RC x2 L[3:2]

0x3610040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID1, SRIO1 not a host] PEI1 EP x2 L[3:2]
0x3690040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID1, SRIO1 not a host] PEI1 RC x2 L[3:2]
0x3650040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID1, SRIO1 not a host] PEI1 EP x2 L[3:2]
0x36d0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID1, SRIO1 not a host] PEI1 RC x2 L[3:2]

0x3420040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 not a host, SRIO1 host ID0] PEI1 EP x2 L[3:2]
0x34a0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 not a host, SRIO1 host ID0] PEI1 RC x2 L[3:2]
0x3460040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 not a host, SRIO1 host ID0] PEI1 EP x2 L[3:2]
0x34e0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 not a host, SRIO1 host ID0] PEI1 RC x2 L[3:2]

0x3520040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 not a host, SRIO1 host ID1] PEI1 EP x2 L[3:2]
0x35a0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 not a host, SRIO1 host ID1] PEI1 RC x2 L[3:2]
0x3560040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 not a host, SRIO1 host ID1] PEI1 EP x2 L[3:2]
0x35e0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 not a host, SRIO1 host ID1] PEI1 RC x2 L[3:2]

0x3620040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 not a host, SRIO1 not a host] PEI1 EP x2 L[3:2]
0x36a0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 not a host, SRIO1 not a host] PEI1 RC x2 L[3:2]
0x3660040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 not a host, SRIO1 not a host] PEI1 EP x2 L[3:2]
0x36e0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 not a host, SRIO1 not a host] PEI1 RC x2 L[3:2]

0x5400040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID0, SRIO1 host ID0] PEI1 EP x1 L[3]
0x5480040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID0, SRIO1 host ID0] PEI1 RC x1 L[3]
0x5440040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID0, SRIO1 host ID0] PEI1 EP x1 L[3]
0x54c0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID0, SRIO1 host ID0] PEI1 RC x1 L[3]

0x5500040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID0, SRIO1 host ID1] PEI1 EP x1 L[3]
0x5580040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID0, SRIO1 host ID1] PEI1 RC x1 L[3]
0x5540040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID0, SRIO1 host ID1] PEI1 EP x1 L[3]
0x55c0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID0, SRIO1 host ID1] PEI1 RC x1 L[3]

0x5600040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID0, SRIO1 not a host] PEI1 EP x1 L[3]
0x5680040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID0, SRIO1 not a host] PEI1 RC x1 L[3]
0x5640040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID0, SRIO1 not a host] PEI1 EP x1 L[3]
0x56c0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID0, SRIO1 not a host] PEI1 RC x1 L[3]

0x5410040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID1, SRIO1 host ID0] PEI1 EP x1 L[3]
0x5490040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID1, SRIO1 host ID0] PEI1 RC x1 L[3]
0x5450040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID1, SRIO1 host ID0] PEI1 EP x1 L[3]
0x54d0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID1, SRIO1 host ID0] PEI1 RC x1 L[3]

0x5510040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID1, SRIO1 host ID1] PEI1 EP x1 L[3]
0x5590040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID1, SRIO1 host ID1] PEI1 RC x1 L[3]
0x5550040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID1, SRIO1 host ID1] PEI1 EP x1 L[3]
0x55d0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID1, SRIO1 host ID1] PEI1 RC x1 L[3]

0x5610040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID1, SRIO1 not a host] PEI1 EP x1 L[3]
0x5690040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 host ID1, SRIO1 not a host] PEI1 RC x1 L[3]
0x5650040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID1, SRIO1 not a host] PEI1 EP x1 L[3]
0x56d0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 host ID1, SRIO1 not a host] PEI1 RC x1 L[3]

0x5420040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 not a host, SRIO1 host ID0] PEI1 EP x1 L[3]
0x54a0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 not a host, SRIO1 host ID0] PEI1 RC x1 L[3]
0x5460040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 not a host, SRIO1 host ID0] PEI1 EP x1 L[3]
0x54e0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 not a host, SRIO1 host ID0] PEI1 RC x1 L[3]

0x5520040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 not a host, SRIO1 host ID1] PEI1 EP x1 L[3]
0x55a0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 not a host, SRIO1 host ID1] PEI1 RC x1 L[3]
0x5560040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 not a host, SRIO1 host ID1] PEI1 EP x1 L[3]
0x55e0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 not a host, SRIO1 host ID1] PEI1 RC x1 L[3]

0x5620040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 not a host, SRIO1 not a host] PEI1 EP x1 L[3]
0x56a0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 EP x1 L[3] [SRIO0 not a host, SRIO1 not a host] PEI1 RC x1 L[3]
0x5660040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 not a host, SRIO1 not a host] PEI1 EP x1 L[3]
0x56e0040d      SRIO0 x1 L[0] SRIO1 x1 L[2] PEI0 RC x1 L[3] [SRIO0 not a host, SRIO1 not a host] PEI1 RC x1 L[3]

0x40000004      PEI1 EP x1 L[3]
0x40800004      PEI1 RC x1 L[3]

*********************************************************************************************************/

/*
-------------------------------------------------------------------------------
pciesrio_init
*/

int
pciesrio_init(unsigned long parameter)
{
	if (0x80000000 != parameter) {
		pciesrio_setcontrol(parameter);
	}
	return 0;
}

int pciesrio_setcontrol(unsigned long new_control)
{
	int i;
	int pci_srio_mode, srio0_speed=0, srio1_speed=0;
	int divMode0=0, divMode1=0;
	unsigned long phy0_ctrl, phy1_ctrl;
	unsigned long pei0_config, pei1_config;	
	unsigned short value;
	rx_serdes_value_t rx_serdes_values[] = {
		{0x00ba, 0x0072},
		{0x02ba, 0x0072},
		{0x06ba, 0x0072},
		{0x08ba, 0x0072},
		{0x008e, 0x0487},
		{0x028e, 0x0487},
		{0x068e, 0x0487},
		{0x088e, 0x0487},
		{0x001e, 0xc001},
		{0x021e, 0xc001},
		{0x061e, 0xc001},
		{0x081e, 0xc001}
	};
	unsigned short v1_0 = 0;

	if (0 == ((pfuse & 0x7e0) >> 5))
		v1_0 = 1;

	phy0_ctrl = new_control & 0x1f700409;
	phy1_ctrl = new_control & 0x60800004;

	if ((phy0_ctrl & 0x8) || (phy0_ctrl & 0x400) || (phy0_ctrl & 0x1)) {

		/* SRIO0/SRIO1/PEI0 modes */

		/* soft reset the phy, pipe, link layer */
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, 0x80);

		udelay(100000);

		/* ncpWrite 0x115.0x0.0x228 0x00000101  # power down PLLA and PLLB */
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x228, 0x00000101);
		
		/* setup AXM55xx for PEI0_sRIO0_sRIO1 specified lane width and reset PLLA/B */
		pci_srio_mode = phy0_ctrl | 0x60;
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x200, pci_srio_mode);

		if (phy0_ctrl & 0x1) {	
			/* PEI0 enabled */
			/* wr pll_a_ctrl  0x230 0x03176403 */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x230, 0x03176403);
		
			if ((phy0_ctrl & 0x04000000) || (phy0_ctrl & 0x08000000)) {
				/* PEI0x2 uses PLL B */
				ncr_write32(NCP_REGION_ID(0x115, 0), 0x234, 0x03176423);
				if (phy0_ctrl & 0x08000000) {
					/* SRIO0x2 uses PLLA */
					ncr_write32(NCP_REGION_ID(0x115, 0), 0x230,0x06126527 );
				}
			}
		} else {
			/* SRIO0 uses PLLA instead PLLB */
			/* ncpWrite 0x115.0x0.0x230 0x06126527 */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x230,0x06126527 );
		}

		if (phy0_ctrl & 0x8) {
			/* setup SRIO0 speed */
			srio0_speed = (new_control & 0x70) << 8;
			printf("new_control = 0x%lx\n",new_control);
			printf("srio0_speed = 0x%x\n", srio0_speed);

			switch ((new_control & 0x70) >> 4) {
				case 0:
					printf("SRIO0 -- 1.25 Gbps\n");
					/* 1.25 Gbps */
					divMode0 = 0x00110011;
					break;
				case 1:
					printf("SRIO0 -- 2.5 Gbps\n");
					/* 2.5 Gbps */
					divMode0 = 0x00330033;
					break;
				case 2:
					printf("SRIO0 -- 3.125 Gbps\n");
					/* 3.125 Gbps */
					divMode0 = 0x00220022;
					if ((phy0_ctrl & 0x10000000) || (phy0_ctrl & 0x08000000)) {
						/* SRIO0x2 on SerDes ch 0,1 */
						ncr_write32(NCP_REGION_ID(0x115, 0), 0x230,0x030A7527 );
					}
					break;
				case 3:
					printf("SRIO0 -- 5 Gbps\n");
					/* 5 Gbps*/
					divMode0 = 0x00220022;
					if ((phy0_ctrl & 0x10000000) || (phy0_ctrl & 0x08000000)) {
						/* SRIO0x2 on SerDes ch 0,1 */
						ncr_write32(NCP_REGION_ID(0x115, 0), 0x230,0x06126527 );
					}
					break;
				case 4:
					printf("SRIO0 -- 6.25 Gbps\n");
					/* 6.25 Gbps */
					divMode0 = 0x0;
					if ((phy0_ctrl & 0x10000000) || (phy0_ctrl & 0x08000000)) {
						/* SRIO0x2 on SerDes ch 0,1 */
						ncr_write32(NCP_REGION_ID(0x115, 0), 0x230,0x030A7234 );
					}
					break;
				default:
					/* invalid srio speed */
					printf("Invalid SRIO0 speed\n");
					return 1;
			}
		}
		if (phy0_ctrl & 0x400) {
			/* setup SRIO1 speed */
			srio1_speed = (new_control & 0x380) << 9;

			/* SRIO1 uses PLL B. If PEI0 is enabled then SRIO0 also uses PLL B*/
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x234,0x06126507 );

			switch ((new_control & 0x380) >> 7) {
				case 0:
					printf("SRIO1 -- 1.25 Gbps\n");
					/* 1.25 Gbps */
					divMode1 = 0x11001100;
					break;
				case 1:
					printf("SRIO1 -- 2.5 Gbps\n");
					/* 2.5 Gbps */
					divMode1 = 0x33003300;
					break;
				case 2:
					printf("SRIO1 -- 3.125 Gbps\n");
					/* 3.125 Gbps */
					divMode1 = 0x22002200;
					if ((phy0_ctrl & 0x10000000) || (phy0_ctrl & 0x08000000)) {
						/* SRIO1x2 on SerDes ch 2,3 */
						ncr_write32(NCP_REGION_ID(0x115, 0), 0x234,0x030A7214 );
					}
					break;
				case 3:
					printf("SRIO1 -- 5 Gbps\n");
					/* 5 Gbps*/
					divMode1 = 0x22002200;
					if ((phy0_ctrl & 0x10000000) || (phy0_ctrl & 0x08000000)) {
						/* SRIO1x2 on SerDes ch 2,3 */
						ncr_write32(NCP_REGION_ID(0x115, 0), 0x234,0x06126214 );
					}
					break;
				case 4:
					printf("SRIO1 -- 6.25 Gbps\n");
					/* 6.25 Gbps */
					divMode1 = 0x0;
					if ((phy0_ctrl & 0x10000000) || (phy0_ctrl & 0x08000000)) {
						/* SRIO1x2 on SerDes ch 2,3 */
						ncr_write32(NCP_REGION_ID(0x115, 0), 0x234,0x030A7214 );
					}
					break;
				default:
					/* invalid srio speed */
					printf("Invalid SRIO1 speed\n");
					return 1;
			}
		}

		if ((phy0_ctrl & 0x8) || (phy0_ctrl & 0x400))  {
			/* # setup speed for both sRIO0 and sRIO1 */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x204,(srio0_speed | srio1_speed));
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x244,(divMode0|divMode1));

			/* ncpWrite 0x115.0x0.0x22c 0x0000000F # the rest are all PLL settings. */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x22c,0x0000000F );
		}

		/* PLL A/PLL B settings */
		switch ((phy0_ctrl & 0x1c000000) >> 26) {
		case 0x0:
			/* PCIe0x4 on SerDes ch 0,1,2,3 */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x208,0xFFFFFFFF );
			break;
		case 0x1:
			/* PCIe0x2 on SerDes ch 2,3 */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x208,0x77007700 );
			break;
		case 0x2:
			/* SRIO0x2, PCIe0x2 SerDes ch 2, 3 */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x208,0x77FF77FF );
			break;
		case 0x4:
			/* SRIO0x2 on SerDes ch 0, 1, SRIO1x2 SerDes ch 2, 3 */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x208,0x77FF77FF );
			break;
		case 0x5:
			/* SRIO0x1 on SerDes ch 0, SRIO1x1 SerDes ch 2, PCIe0x1 on ch 3*/
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x208,0xF707F707 );
			break;
		default:
			printf("Invalid PEI0/SRIO configuration\n");
			return 1;
		}

		
		/* SRIO workaround if SRIO speed is 6.25 Gb/s 
		 * and SRIO0x2,SRIO1x2 
		 * or SRIO0x2 PCIe0x2
		 * or SRIO0x1 SRIO1x1, PCIe0x1*/	
		if (((phy0_ctrl & 0x10000000) && (((new_control & 0x70) >> 4) == 0x4) && 
				(((new_control & 0x380) >> 7) == 0x4))
			|| ((phy0_ctrl & 0x80000000) 
				&& (((new_control & 0x70) >> 4) == 0x4))
			|| ((phy0_ctrl & 0x14000000) 
				&& (((new_control & 0x70) >> 4) == 0x4) 
				&& (((new_control & 0x380) >> 7) == 0x4))) {
			ncr_write16(NCP_REGION_ID(0x115, 1), 0xba,0x0062 );
			ncr_write16(NCP_REGION_ID(0x115, 1), 0xc,0x2400 );
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x2ba,0x0062 );
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x20c,0x2400 );

			/* following enable eyefinder in the Serdes */
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x1e,0x8001 );
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x21e,0x8001 );
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x61e,0x8001 );
			ncr_write16(NCP_REGION_ID(0x115, 1), 0x81e,0x8001 );
		}

		if (phy0_ctrl & 0x1) {	
			if (v1_0) {	
				/* Applicable only to v1.0 device */
				/* ncpWrite 0x115.0x0.0x214 0x00F00A0A */
				ncr_write32(NCP_REGION_ID(0x115, 0), 0x214, 0x00F00A0A);
				for (i = 0;
	     			i < sizeof(rx_serdes_values) / sizeof(rx_serdes_value_t);
	     			++i) {
					ncr_write16(NCP_REGION_ID(0x115, 1),
			   		 	rx_serdes_values[i].offset,
			   		 	rx_serdes_values[i].value);
				}
			}
			if ((phy0_ctrl & 0x1c000000) == 0) {
				/* PEI0 x4 mode -- PLLA used -- power only PLLA */
				ncr_write32(NCP_REGION_ID(0x115, 0), 0x228,0x00000100 );
			} else {
				ncr_write32(NCP_REGION_ID(0x115, 0), 0x228,0x00000000 );
			}
		} else if (phy0_ctrl & 0x400) {
			/* SRIO1 enabled */
			/* ncpWrite 0x115.0x0.0x228 0x00000000  # power up PLLA and PLLB */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x228,0x00000000 );
		} else {
			/* SRIO1 not enabled, only SRIO0 is used */
			/* ncpWrite 0x115.0x0.0x228 0x00000000  # power up only PLLA */
			ncr_write32(NCP_REGION_ID(0x115, 0), 0x228,0x00000100 );
		} 

		/* 100 ms delay */
		udelay(100000);
		ncr_write32(NCP_REGION_ID(0x115, 0), 0x200,phy0_ctrl);

		/* 100 ms delay */
		udelay(100000);

		if (v1_0) {
			/* Applicable only to v1.0 */
			/* Force Gen1 speed */
			pei0_config = readl((void *)(PCIE0_CONFIG + 0x1000));
			pei0_config = pei0_config | 0x00040000;
			writel(pei0_config, (void *)(PCIE0_CONFIG + 0x1000));
		}

		if ((new_control & 0x00000004) != 0x00000004) {
			/* only PEI0 is being used */
			/* only HSS5 is used. Powerdown HSS6 */
			/* pd_pin_override 0x115.0x4.0xba bit 4 */
			ncr_read16(NCP_REGION_ID(0x115, 4), 0xba, &value);
			value = value | (0x1 << 4);
			ncr_write16(NCP_REGION_ID(0x115, 4), 0xba, value);
			ncr_read16(NCP_REGION_ID(0x115, 4), 0x2ba, &value);
			value = value | (0x1 << 4);
			ncr_write16(NCP_REGION_ID(0x115, 4), 0x2ba, value);
			ncr_read16(NCP_REGION_ID(0x115, 4), 0x6ba, &value);
			value = value | (0x1 << 4);
			ncr_write16(NCP_REGION_ID(0x115, 4), 0x6ba, value);
			ncr_read16(NCP_REGION_ID(0x115, 4), 0x8ba, &value);
			value = value | (0x1 << 4);
			ncr_write16(NCP_REGION_ID(0x115, 4), 0x8ba, value);

			/* rxpd_r2a 0x115.0x4.0x1c bit 14 */
			ncr_read16(NCP_REGION_ID(0x115, 4), 0x1c, &value);
			value = value | (0x1 << 14);
			ncr_write16(NCP_REGION_ID(0x115, 4), 0x1c, value);
			ncr_read16(NCP_REGION_ID(0x115, 4), 0x21c, &value);
			value = value | (0x1 << 14);
			ncr_write16(NCP_REGION_ID(0x115, 4), 0x21c, value);
			ncr_read16(NCP_REGION_ID(0x115, 4), 0x61c, &value);
			value = value | (0x1 << 14);
			ncr_write16(NCP_REGION_ID(0x115, 4), 0x61c, value);
			ncr_read16(NCP_REGION_ID(0x115, 4), 0x81c, &value);
			value = value | (0x1 << 14);
			ncr_write16(NCP_REGION_ID(0x115, 4), 0x81c, value);

			/* txpd_r2a 0x115.0x4.0x10 bit 10 */
			ncr_read16(NCP_REGION_ID(0x115, 4), 0x10, &value);
			value = value | (0x1 << 10);
			ncr_write16(NCP_REGION_ID(0x115, 4), 0x10, value);
			ncr_read16(NCP_REGION_ID(0x115, 4), 0x210, &value);
			value = value | (0x1 << 10);
			ncr_write16(NCP_REGION_ID(0x115, 4), 0x210, value);
			ncr_read16(NCP_REGION_ID(0x115, 4), 0x610, &value);
			value = value | (0x1 << 10);
			ncr_write16(NCP_REGION_ID(0x115, 4), 0x610, value);
			ncr_read16(NCP_REGION_ID(0x115, 4), 0x810, &value);
			value = value | (0x1 << 10);
			ncr_write16(NCP_REGION_ID(0x115, 4), 0x810, value);

		}
	} 

	if (new_control & 0x00000004) {
		/* Check bit 2 as this determines PEI1 state */

		/* soft reset the phy, pipe, link layer */
		ncr_write32(NCP_REGION_ID(0x115, 3), 0x200, 0x80);
		udelay(100000);

		ncr_write32(NCP_REGION_ID(0x115, 3), 0x228, 0x00000001);
	
		/* PLL A /PLL B config */	
		ncr_write32(NCP_REGION_ID(0x115, 3), 0x208,0xFFFFFFFF );

		/* wr pll_a_ctrl  0x230 0x03176403 */
		ncr_write32(NCP_REGION_ID(0x115, 3), 0x230, 0x03176403);

		if (v1_0) {
			/* Applicable only to v1.0 */
			for (i = 0;
	     		i < sizeof(rx_serdes_values) / sizeof(rx_serdes_value_t);
	     		++i) {
				ncr_write16(NCP_REGION_ID(0x115, 4),
					rx_serdes_values[i].offset,
					rx_serdes_values[i].value);
			}
		}

		/* ncpWrite 0x115.0x0.0x228 0x00000000  # power up PLLA */
		ncr_write32(NCP_REGION_ID(0x115, 3), 0x228,0x00000000 );

		/* 100 ms delay */
		udelay(100000);

		phy1_ctrl = (((phy1_ctrl & 0x60000000) >> 3) | ((phy1_ctrl & 0x00800000) >> 1) | 0x1);
		/* PCIE1 */
		ncr_write32(NCP_REGION_ID(0x115, 3), 0x200, phy1_ctrl);

		if (v1_0) {
			/* Force Gen1 speed */
			pei1_config = readl((void *)(PCIE1_CONFIG + 0x1000));
			pei1_config = pei1_config | 0x00040000;
			writel(pei1_config, (void *)(PCIE1_CONFIG + 0x1000));
		}
	}

	return 0;
}
