/*
 *  Copyright (C) 2010 LSI Corporation
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software;you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation;either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY;without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program;if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>

#include "ncp_sysmem_ext.h"
#include "regs/ncp_denali_regs.h"
#include "regs/ncp_denali_reg_defines.h"
#include "regs/ncp_phy_regs.h"
#include "regs/ncp_phy_reg_defines.h"

/*
  ==============================================================================
  ==============================================================================
  ==============================================================================
  Local Stuff
  ==============================================================================
  ==============================================================================
  ==============================================================================
*/

#define SMAV( regName, regField, newValue ) \
do { \
regName *tmpMask = (regName *)&mask;\
regName *tmpValue = (regName *)&value;\
tmpMask->regField = -1;\
tmpValue->regField = newValue;\
mb();\
} while( 0 );

#define SV( regName, regField, newValue ) \
do { \
regName *tmpValue = (regName *)&value;\
tmpValue->regField = newValue;\
mb();\
} while( 0 );

#undef USE_OLD_DELAY_TABLE
/*#define USE_OLD_DELAY_TABLE*/
#ifdef USE_OLD_DELAY_TABLE

typedef struct {
	unsigned long smId   :2;
	unsigned long offset :16;
	unsigned long value  :14;
} delay_table_t;

delay_table_t delay_table_v1_533[] = {
	{ 0, 0x042c, 0x0100 },   /*  SMEM0_CKE[0] ADR01 bit11   */
	{ 0, 0x0818, 0x0100 },   /*  SMEM0_CSB[0] ADR10 bit6   */
	{ 0, 0x0810, 0x0100 },   /*  SMEM0_ODT[0] ADR10 bit4   */
	{ 0, 0x0024, 0x0100 },   /*  SMEM0_CKE[1] ADR00 bit9   */
	{ 0, 0x0808, 0x0100 },   /*  SMEM0_CSB[1] ADR10 bit2   */
	{ 0, 0x0814, 0x0100 },   /*  SMEM0_ODT[1] ADR10 bit5   */
	{ 0, 0x0408, 0x0100 },   /*  SMEM0_CKE[2] ADR01 bit2   */
	{ 0, 0x0834, 0x0100 },   /*  SMEM0_CSB[2] ADR10 bit13   */
	{ 0, 0x0824, 0x0100 },   /*  SMEM0_ODT[2] ADR10 bit9   */
	{ 0, 0x041c, 0x0104 },   /*  SMEM0_CKE[3] ADR01 bit7   */
	{ 0, 0x000c, 0x0100 },   /*  SMEM0_CSB[3] ADR00 bit3   */
	{ 0, 0x082c, 0x0104 },   /*  SMEM0_ODT[3] ADR10 bit11   */
	{ 0, 0x0800, 0x0100 },   /*  SMEM0_ADDR[0] ADR10 bit0   */
	{ 0, 0x081c, 0x0104 },   /*  SMEM0_ADDR[1] ADR10 bit7   */
	{ 0, 0x040c, 0x0100 },   /*  SMEM0_ADDR[2] ADR01 bit3   */
	{ 0, 0x0020, 0x0104 },   /*  SMEM0_ADDR[3] ADR00 bit8   */
	{ 0, 0x0410, 0x0104 },   /*  SMEM0_ADDR[4] ADR01 bit4   */
	{ 0, 0x0418, 0x0104 },   /*  SMEM0_ADDR[5] ADR01 bit6   */
	{ 0, 0x0428, 0x0108 },   /*  SMEM0_ADDR[6] ADR01 bit10   */
	{ 0, 0x0838, 0x0114 },   /*  SMEM0_ADDR[7] ADR10 bit14   */
	{ 0, 0x0014, 0x010c },   /*  SMEM0_ADDR[8] ADR00 bit5   */
	{ 0, 0x0830, 0x010c },   /*  SMEM0_ADDR[9] ADR10 bit12   */
	{ 0, 0x080c, 0x0110 },   /*  SMEM0_ADDR[10] ADR10 bit3   */
	{ 0, 0x0028, 0x0104 },   /*  SMEM0_ADDR[11] ADR00 bit10   */
	{ 0, 0x0430, 0x0104 },   /*  SMEM0_ADDR[12] ADR01 bit12   */
	{ 0, 0x0008, 0x0108 },   /*  SMEM0_ADDR[13] ADR00 bit2   */
	{ 0, 0x043c, 0x010c },   /*  SMEM0_ADDR[14] ADR01 bit15   */
	{ 0, 0x0414, 0x010c },   /*  SMEM0_ADDR[15] ADR01 bit5   */
	{ 0, 0x0820, 0x0108 },   /*  SMEM0_BA[0] ADR10 bit8   */
	{ 0, 0x002c, 0x0108 },   /*  SMEM0_BA[1] ADR00 bit11   */
	{ 0, 0x0434, 0x0108 },   /*  SMEM0_BA[2] ADR01 bit13   */
	{ 0, 0x0438, 0x0100 },   /*  SMEM0_RESETB ADR01 bit14   */
	{ 0, 0x0828, 0x0108 },   /*  SMEM0_RASB ADR10 bit10   */
	{ 0, 0x0804, 0x0100 },   /*  SMEM0_CASB ADR10 bit1   */
	{ 0, 0x0010, 0x0104 },   /*  SMEM0_WEB ADR00 bit4   */
	{ 0, 0x8050, 0x0000 },   /*  SMEM0_DM[0]  CS0 */
	{ 0, 0x8850, 0x0000 },   /*  SMEM0_DM[0]  CS1 */
	{ 0, 0x9050, 0x0000 },   /*  SMEM0_DM[0]  CS2 */
	{ 0, 0x9850, 0x0000 },   /*  SMEM0_DM[0]  CS3 */
	{ 0, 0x8000, 0x0004 },   /*  SMEM0_DQ[0]  CS0 */
	{ 0, 0x8800, 0x0004 },   /*  SMEM0_DQ[0]  CS1 */
	{ 0, 0x9000, 0x0004 },   /*  SMEM0_DQ[0]  CS2 */
	{ 0, 0x9800, 0x0004 },   /*  SMEM0_DQ[0]  CS3 */
	{ 0, 0x8004, 0x0000 },   /*  SMEM0_DQ[1]  CS0 */
	{ 0, 0x8804, 0x0000 },   /*  SMEM0_DQ[1]  CS1 */
	{ 0, 0x9004, 0x0000 },   /*  SMEM0_DQ[1]  CS2 */
	{ 0, 0x9804, 0x0000 },   /*  SMEM0_DQ[1]  CS3 */
	{ 0, 0x8008, 0x0004 },   /*  SMEM0_DQ[2]  CS0 */
	{ 0, 0x8808, 0x0004 },   /*  SMEM0_DQ[2]  CS1 */
	{ 0, 0x9008, 0x0004 },   /*  SMEM0_DQ[2]  CS2 */
	{ 0, 0x9808, 0x0004 },   /*  SMEM0_DQ[2]  CS3 */
	{ 0, 0x800c, 0x0008 },   /*  SMEM0_DQ[3]  CS0 */
	{ 0, 0x880c, 0x0008 },   /*  SMEM0_DQ[3]  CS1 */
	{ 0, 0x900c, 0x0008 },   /*  SMEM0_DQ[3]  CS2 */
	{ 0, 0x980c, 0x0008 },   /*  SMEM0_DQ[3]  CS3 */
	{ 0, 0x8040, 0x0000 },   /*  SMEM0_DQ[4]  CS0 */
	{ 0, 0x8840, 0x0000 },   /*  SMEM0_DQ[4]  CS1 */
	{ 0, 0x9040, 0x0000 },   /*  SMEM0_DQ[4]  CS2 */
	{ 0, 0x9840, 0x0000 },   /*  SMEM0_DQ[4]  CS3 */
	{ 0, 0x8044, 0x0004 },   /*  SMEM0_DQ[5]  CS0 */
	{ 0, 0x8844, 0x0004 },   /*  SMEM0_DQ[5]  CS1 */
	{ 0, 0x9044, 0x0004 },   /*  SMEM0_DQ[5]  CS2 */
	{ 0, 0x9844, 0x0004 },   /*  SMEM0_DQ[5]  CS3 */
	{ 0, 0x8048, 0x0000 },   /*  SMEM0_DQ[6]  CS0 */
	{ 0, 0x8848, 0x0000 },   /*  SMEM0_DQ[6]  CS1 */
	{ 0, 0x9048, 0x0000 },   /*  SMEM0_DQ[6]  CS2 */
	{ 0, 0x9848, 0x0000 },   /*  SMEM0_DQ[6]  CS3 */
	{ 0, 0x804c, 0x0000 },   /*  SMEM0_DQ[7]  CS0 */
	{ 0, 0x884c, 0x0000 },   /*  SMEM0_DQ[7]  CS1 */
	{ 0, 0x904c, 0x0000 },   /*  SMEM0_DQ[7]  CS2 */
	{ 0, 0x984c, 0x0000 },   /*  SMEM0_DQ[7]  CS3 */
	{ 0, 0x80d0, 0x0008 },   /*  SMEM0_DM[1]  CS0 */
	{ 0, 0x88d0, 0x0008 },   /*  SMEM0_DM[1]  CS1 */
	{ 0, 0x90d0, 0x0008 },   /*  SMEM0_DM[1]  CS2 */
	{ 0, 0x98d0, 0x0008 },   /*  SMEM0_DM[1]  CS3 */
	{ 0, 0x8080, 0x0000 },   /*  SMEM0_DQ[8]  CS0 */
	{ 0, 0x8880, 0x0000 },   /*  SMEM0_DQ[8]  CS1 */
	{ 0, 0x9080, 0x0000 },   /*  SMEM0_DQ[8]  CS2 */
	{ 0, 0x9880, 0x0000 },   /*  SMEM0_DQ[8]  CS3 */
	{ 0, 0x8084, 0x0000 },   /*  SMEM0_DQ[9]  CS0 */
	{ 0, 0x8884, 0x0000 },   /*  SMEM0_DQ[9]  CS1 */
	{ 0, 0x9084, 0x0000 },   /*  SMEM0_DQ[9]  CS2 */
	{ 0, 0x9884, 0x0000 },   /*  SMEM0_DQ[9]  CS3 */
	{ 0, 0x8088, 0x0000 },   /*  SMEM0_DQ[10]  CS0 */
	{ 0, 0x8888, 0x0000 },   /*  SMEM0_DQ[10]  CS1 */
	{ 0, 0x9088, 0x0000 },   /*  SMEM0_DQ[10]  CS2 */
	{ 0, 0x9888, 0x0000 },   /*  SMEM0_DQ[10]  CS3 */
	{ 0, 0x808c, 0x0008 },   /*  SMEM0_DQ[11]  CS0 */
	{ 0, 0x888c, 0x0008 },   /*  SMEM0_DQ[11]  CS1 */
	{ 0, 0x908c, 0x0008 },   /*  SMEM0_DQ[11]  CS2 */
	{ 0, 0x988c, 0x0008 },   /*  SMEM0_DQ[11]  CS3 */
	{ 0, 0x80c0, 0x0008 },   /*  SMEM0_DQ[12]  CS0 */
	{ 0, 0x88c0, 0x0008 },   /*  SMEM0_DQ[12]  CS1 */
	{ 0, 0x90c0, 0x0008 },   /*  SMEM0_DQ[12]  CS2 */
	{ 0, 0x98c0, 0x0008 },   /*  SMEM0_DQ[12]  CS3 */
	{ 0, 0x80c4, 0x0000 },   /*  SMEM0_DQ[13]  CS0 */
	{ 0, 0x88c4, 0x0000 },   /*  SMEM0_DQ[13]  CS1 */
	{ 0, 0x90c4, 0x0000 },   /*  SMEM0_DQ[13]  CS2 */
	{ 0, 0x98c4, 0x0000 },   /*  SMEM0_DQ[13]  CS3 */
	{ 0, 0x80c8, 0x0000 },   /*  SMEM0_DQ[14]  CS0 */
	{ 0, 0x88c8, 0x0000 },   /*  SMEM0_DQ[14]  CS1 */
	{ 0, 0x90c8, 0x0000 },   /*  SMEM0_DQ[14]  CS2 */
	{ 0, 0x98c8, 0x0000 },   /*  SMEM0_DQ[14]  CS3 */
	{ 0, 0x80cc, 0x0000 },   /*  SMEM0_DQ[15]  CS0 */
	{ 0, 0x88cc, 0x0000 },   /*  SMEM0_DQ[15]  CS1 */
	{ 0, 0x90cc, 0x0000 },   /*  SMEM0_DQ[15]  CS2 */
	{ 0, 0x98cc, 0x0000 },   /*  SMEM0_DQ[15]  CS3 */
	{ 0, 0x8150, 0x0000 },   /*  SMEM0_DM[2]  CS0 */
	{ 0, 0x8950, 0x0000 },   /*  SMEM0_DM[2]  CS1 */
	{ 0, 0x9150, 0x0000 },   /*  SMEM0_DM[2]  CS2 */
	{ 0, 0x9950, 0x0000 },   /*  SMEM0_DM[2]  CS3 */
	{ 0, 0x8100, 0x0008 },   /*  SMEM0_DQ[16]  CS0 */
	{ 0, 0x8900, 0x0008 },   /*  SMEM0_DQ[16]  CS1 */
	{ 0, 0x9100, 0x0008 },   /*  SMEM0_DQ[16]  CS2 */
	{ 0, 0x9900, 0x0008 },   /*  SMEM0_DQ[16]  CS3 */
	{ 0, 0x8104, 0x0000 },   /*  SMEM0_DQ[17]  CS0 */
	{ 0, 0x8904, 0x0000 },   /*  SMEM0_DQ[17]  CS1 */
	{ 0, 0x9104, 0x0000 },   /*  SMEM0_DQ[17]  CS2 */
	{ 0, 0x9904, 0x0000 },   /*  SMEM0_DQ[17]  CS3 */
	{ 0, 0x8108, 0x0000 },   /*  SMEM0_DQ[18]  CS0 */
	{ 0, 0x8908, 0x0000 },   /*  SMEM0_DQ[18]  CS1 */
	{ 0, 0x9108, 0x0000 },   /*  SMEM0_DQ[18]  CS2 */
	{ 0, 0x9908, 0x0000 },   /*  SMEM0_DQ[18]  CS3 */
	{ 0, 0x810c, 0x0000 },   /*  SMEM0_DQ[19]  CS0 */
	{ 0, 0x890c, 0x0000 },   /*  SMEM0_DQ[19]  CS1 */
	{ 0, 0x910c, 0x0000 },   /*  SMEM0_DQ[19]  CS2 */
	{ 0, 0x990c, 0x0000 },   /*  SMEM0_DQ[19]  CS3 */
	{ 0, 0x8140, 0x0004 },   /*  SMEM0_DQ[20]  CS0 */
	{ 0, 0x8940, 0x0004 },   /*  SMEM0_DQ[20]  CS1 */
	{ 0, 0x9140, 0x0004 },   /*  SMEM0_DQ[20]  CS2 */
	{ 0, 0x9940, 0x0004 },   /*  SMEM0_DQ[20]  CS3 */
	{ 0, 0x8144, 0x0008 },   /*  SMEM0_DQ[21]  CS0 */
	{ 0, 0x8944, 0x0008 },   /*  SMEM0_DQ[21]  CS1 */
	{ 0, 0x9144, 0x0008 },   /*  SMEM0_DQ[21]  CS2 */
	{ 0, 0x9944, 0x0008 },   /*  SMEM0_DQ[21]  CS3 */
	{ 0, 0x8148, 0x0000 },   /*  SMEM0_DQ[22]  CS0 */
	{ 0, 0x8948, 0x0000 },   /*  SMEM0_DQ[22]  CS1 */
	{ 0, 0x9148, 0x0000 },   /*  SMEM0_DQ[22]  CS2 */
	{ 0, 0x9948, 0x0000 },   /*  SMEM0_DQ[22]  CS3 */
	{ 0, 0x814c, 0x0004 },   /*  SMEM0_DQ[23]  CS0 */
	{ 0, 0x894c, 0x0004 },   /*  SMEM0_DQ[23]  CS1 */
	{ 0, 0x914c, 0x0004 },   /*  SMEM0_DQ[23]  CS2 */
	{ 0, 0x994c, 0x0004 },   /*  SMEM0_DQ[23]  CS3 */
	{ 0, 0x81d0, 0x0004 },   /*  SMEM0_DM[3]  CS0 */
	{ 0, 0x89d0, 0x0004 },   /*  SMEM0_DM[3]  CS1 */
	{ 0, 0x91d0, 0x0004 },   /*  SMEM0_DM[3]  CS2 */
	{ 0, 0x99d0, 0x0004 },   /*  SMEM0_DM[3]  CS3 */
	{ 0, 0x8180, 0x0000 },   /*  SMEM0_DQ[24]  CS0 */
	{ 0, 0x8980, 0x0000 },   /*  SMEM0_DQ[24]  CS1 */
	{ 0, 0x9180, 0x0000 },   /*  SMEM0_DQ[24]  CS2 */
	{ 0, 0x9980, 0x0000 },   /*  SMEM0_DQ[24]  CS3 */
	{ 0, 0x8184, 0x0004 },   /*  SMEM0_DQ[25]  CS0 */
	{ 0, 0x8984, 0x0004 },   /*  SMEM0_DQ[25]  CS1 */
	{ 0, 0x9184, 0x0004 },   /*  SMEM0_DQ[25]  CS2 */
	{ 0, 0x9984, 0x0004 },   /*  SMEM0_DQ[25]  CS3 */
	{ 0, 0x8188, 0x0004 },   /*  SMEM0_DQ[26]  CS0 */
	{ 0, 0x8988, 0x0004 },   /*  SMEM0_DQ[26]  CS1 */
	{ 0, 0x9188, 0x0004 },   /*  SMEM0_DQ[26]  CS2 */
	{ 0, 0x9988, 0x0004 },   /*  SMEM0_DQ[26]  CS3 */
	{ 0, 0x818c, 0x0000 },   /*  SMEM0_DQ[27]  CS0 */
	{ 0, 0x898c, 0x0000 },   /*  SMEM0_DQ[27]  CS1 */
	{ 0, 0x918c, 0x0000 },   /*  SMEM0_DQ[27]  CS2 */
	{ 0, 0x998c, 0x0000 },   /*  SMEM0_DQ[27]  CS3 */
	{ 0, 0x81c0, 0x0004 },   /*  SMEM0_DQ[28]  CS0 */
	{ 0, 0x89c0, 0x0004 },   /*  SMEM0_DQ[28]  CS1 */
	{ 0, 0x91c0, 0x0004 },   /*  SMEM0_DQ[28]  CS2 */
	{ 0, 0x99c0, 0x0004 },   /*  SMEM0_DQ[28]  CS3 */
	{ 0, 0x81c4, 0x0000 },   /*  SMEM0_DQ[29]  CS0 */
	{ 0, 0x89c4, 0x0000 },   /*  SMEM0_DQ[29]  CS1 */
	{ 0, 0x91c4, 0x0000 },   /*  SMEM0_DQ[29]  CS2 */
	{ 0, 0x99c4, 0x0000 },   /*  SMEM0_DQ[29]  CS3 */
	{ 0, 0x81c8, 0x0004 },   /*  SMEM0_DQ[30]  CS0 */
	{ 0, 0x89c8, 0x0004 },   /*  SMEM0_DQ[30]  CS1 */
	{ 0, 0x91c8, 0x0004 },   /*  SMEM0_DQ[30]  CS2 */
	{ 0, 0x99c8, 0x0004 },   /*  SMEM0_DQ[30]  CS3 */
	{ 0, 0x81cc, 0x0000 },   /*  SMEM0_DQ[31]  CS0 */
	{ 0, 0x89cc, 0x0000 },   /*  SMEM0_DQ[31]  CS1 */
	{ 0, 0x91cc, 0x0000 },   /*  SMEM0_DQ[31]  CS2 */
	{ 0, 0x99cc, 0x0000 },   /*  SMEM0_DQ[31]  CS3 */
	{ 0, 0x8250, 0x0004 },   /*  SMEM0_DM[4]  CS0 */
	{ 0, 0x8a50, 0x0004 },   /*  SMEM0_DM[4]  CS1 */
	{ 0, 0x9250, 0x0004 },   /*  SMEM0_DM[4]  CS2 */
	{ 0, 0x9a50, 0x0004 },   /*  SMEM0_DM[4]  CS3 */
	{ 0, 0x8200, 0x0004 },   /*  SMEM0_DQ[32]  CS0 */
	{ 0, 0x8a00, 0x0004 },   /*  SMEM0_DQ[32]  CS1 */
	{ 0, 0x9200, 0x0004 },   /*  SMEM0_DQ[32]  CS2 */
	{ 0, 0x9a00, 0x0004 },   /*  SMEM0_DQ[32]  CS3 */
	{ 0, 0x8204, 0x0004 },   /*  SMEM0_DQ[33]  CS0 */
	{ 0, 0x8a04, 0x0004 },   /*  SMEM0_DQ[33]  CS1 */
	{ 0, 0x9204, 0x0004 },   /*  SMEM0_DQ[33]  CS2 */
	{ 0, 0x9a04, 0x0004 },   /*  SMEM0_DQ[33]  CS3 */
	{ 0, 0x8208, 0x0004 },   /*  SMEM0_DQ[34]  CS0 */
	{ 0, 0x8a08, 0x0004 },   /*  SMEM0_DQ[34]  CS1 */
	{ 0, 0x9208, 0x0004 },   /*  SMEM0_DQ[34]  CS2 */
	{ 0, 0x9a08, 0x0004 },   /*  SMEM0_DQ[34]  CS3 */
	{ 0, 0x820c, 0x0004 },   /*  SMEM0_DQ[35]  CS0 */
	{ 0, 0x8a0c, 0x0004 },   /*  SMEM0_DQ[35]  CS1 */
	{ 0, 0x920c, 0x0004 },   /*  SMEM0_DQ[35]  CS2 */
	{ 0, 0x9a0c, 0x0004 },   /*  SMEM0_DQ[35]  CS3 */
	{ 0, 0x8240, 0x0008 },   /*  SMEM0_DQ[36]  CS0 */
	{ 0, 0x8a40, 0x0008 },   /*  SMEM0_DQ[36]  CS1 */
	{ 0, 0x9240, 0x0008 },   /*  SMEM0_DQ[36]  CS2 */
	{ 0, 0x9a40, 0x0008 },   /*  SMEM0_DQ[36]  CS3 */
	{ 0, 0x8244, 0x0004 },   /*  SMEM0_DQ[37]  CS0 */
	{ 0, 0x8a44, 0x0004 },   /*  SMEM0_DQ[37]  CS1 */
	{ 0, 0x9244, 0x0004 },   /*  SMEM0_DQ[37]  CS2 */
	{ 0, 0x9a44, 0x0004 },   /*  SMEM0_DQ[37]  CS3 */
	{ 0, 0x8248, 0x0004 },   /*  SMEM0_DQ[38]  CS0 */
	{ 0, 0x8a48, 0x0004 },   /*  SMEM0_DQ[38]  CS1 */
	{ 0, 0x9248, 0x0004 },   /*  SMEM0_DQ[38]  CS2 */
	{ 0, 0x9a48, 0x0004 },   /*  SMEM0_DQ[38]  CS3 */
	{ 0, 0x824c, 0x0004 },   /*  SMEM0_DQ[39]  CS0 */
	{ 0, 0x8a4c, 0x0004 },   /*  SMEM0_DQ[39]  CS1 */
	{ 0, 0x924c, 0x0004 },   /*  SMEM0_DQ[39]  CS2 */
	{ 0, 0x9a4c, 0x0004 },   /*  SMEM0_DQ[39]  CS3 */
	{ 0, 0x82d0, 0x0000 },   /*  SMEM0_DM[5]  CS0 */
	{ 0, 0x8ad0, 0x0000 },   /*  SMEM0_DM[5]  CS1 */
	{ 0, 0x92d0, 0x0000 },   /*  SMEM0_DM[5]  CS2 */
	{ 0, 0x9ad0, 0x0000 },   /*  SMEM0_DM[5]  CS3 */
	{ 0, 0x8280, 0x0000 },   /*  SMEM0_DQ[40]  CS0 */
	{ 0, 0x8a80, 0x0000 },   /*  SMEM0_DQ[40]  CS1 */
	{ 0, 0x9280, 0x0000 },   /*  SMEM0_DQ[40]  CS2 */
	{ 0, 0x9a80, 0x0000 },   /*  SMEM0_DQ[40]  CS3 */
	{ 0, 0x8284, 0x0004 },   /*  SMEM0_DQ[41]  CS0 */
	{ 0, 0x8a84, 0x0004 },   /*  SMEM0_DQ[41]  CS1 */
	{ 0, 0x9284, 0x0004 },   /*  SMEM0_DQ[41]  CS2 */
	{ 0, 0x9a84, 0x0004 },   /*  SMEM0_DQ[41]  CS3 */
	{ 0, 0x8288, 0x0004 },   /*  SMEM0_DQ[42]  CS0 */
	{ 0, 0x8a88, 0x0004 },   /*  SMEM0_DQ[42]  CS1 */
	{ 0, 0x9288, 0x0004 },   /*  SMEM0_DQ[42]  CS2 */
	{ 0, 0x9a88, 0x0004 },   /*  SMEM0_DQ[42]  CS3 */
	{ 0, 0x828c, 0x0000 },   /*  SMEM0_DQ[43]  CS0 */
	{ 0, 0x8a8c, 0x0000 },   /*  SMEM0_DQ[43]  CS1 */
	{ 0, 0x928c, 0x0000 },   /*  SMEM0_DQ[43]  CS2 */
	{ 0, 0x9a8c, 0x0000 },   /*  SMEM0_DQ[43]  CS3 */
	{ 0, 0x82c0, 0x0004 },   /*  SMEM0_DQ[44]  CS0 */
	{ 0, 0x8ac0, 0x0004 },   /*  SMEM0_DQ[44]  CS1 */
	{ 0, 0x92c0, 0x0004 },   /*  SMEM0_DQ[44]  CS2 */
	{ 0, 0x9ac0, 0x0004 },   /*  SMEM0_DQ[44]  CS3 */
	{ 0, 0x82c4, 0x0000 },   /*  SMEM0_DQ[45]  CS0 */
	{ 0, 0x8ac4, 0x0000 },   /*  SMEM0_DQ[45]  CS1 */
	{ 0, 0x92c4, 0x0000 },   /*  SMEM0_DQ[45]  CS2 */
	{ 0, 0x9ac4, 0x0000 },   /*  SMEM0_DQ[45]  CS3 */
	{ 0, 0x82c8, 0x0004 },   /*  SMEM0_DQ[46]  CS0 */
	{ 0, 0x8ac8, 0x0004 },   /*  SMEM0_DQ[46]  CS1 */
	{ 0, 0x92c8, 0x0004 },   /*  SMEM0_DQ[46]  CS2 */
	{ 0, 0x9ac8, 0x0004 },   /*  SMEM0_DQ[46]  CS3 */
	{ 0, 0x82cc, 0x0004 },   /*  SMEM0_DQ[47]  CS0 */
	{ 0, 0x8acc, 0x0004 },   /*  SMEM0_DQ[47]  CS1 */
	{ 0, 0x92cc, 0x0004 },   /*  SMEM0_DQ[47]  CS2 */
	{ 0, 0x9acc, 0x0004 },   /*  SMEM0_DQ[47]  CS3 */
	{ 0, 0x8350, 0x0000 },   /*  SMEM0_DM[6]  CS0 */
	{ 0, 0x8b50, 0x0000 },   /*  SMEM0_DM[6]  CS1 */
	{ 0, 0x9350, 0x0000 },   /*  SMEM0_DM[6]  CS2 */
	{ 0, 0x9b50, 0x0000 },   /*  SMEM0_DM[6]  CS3 */
	{ 0, 0x8300, 0x0004 },   /*  SMEM0_DQ[48]  CS0 */
	{ 0, 0x8b00, 0x0004 },   /*  SMEM0_DQ[48]  CS1 */
	{ 0, 0x9300, 0x0004 },   /*  SMEM0_DQ[48]  CS2 */
	{ 0, 0x9b00, 0x0004 },   /*  SMEM0_DQ[48]  CS3 */
	{ 0, 0x8304, 0x0004 },   /*  SMEM0_DQ[49]  CS0 */
	{ 0, 0x8b04, 0x0004 },   /*  SMEM0_DQ[49]  CS1 */
	{ 0, 0x9304, 0x0004 },   /*  SMEM0_DQ[49]  CS2 */
	{ 0, 0x9b04, 0x0004 },   /*  SMEM0_DQ[49]  CS3 */
	{ 0, 0x8308, 0x0000 },   /*  SMEM0_DQ[50]  CS0 */
	{ 0, 0x8b08, 0x0000 },   /*  SMEM0_DQ[50]  CS1 */
	{ 0, 0x9308, 0x0000 },   /*  SMEM0_DQ[50]  CS2 */
	{ 0, 0x9b08, 0x0000 },   /*  SMEM0_DQ[50]  CS3 */
	{ 0, 0x830c, 0x0004 },   /*  SMEM0_DQ[51]  CS0 */
	{ 0, 0x8b0c, 0x0004 },   /*  SMEM0_DQ[51]  CS1 */
	{ 0, 0x930c, 0x0004 },   /*  SMEM0_DQ[51]  CS2 */
	{ 0, 0x9b0c, 0x0004 },   /*  SMEM0_DQ[51]  CS3 */
	{ 0, 0x8340, 0x0000 },   /*  SMEM0_DQ[52]  CS0 */
	{ 0, 0x8b40, 0x0000 },   /*  SMEM0_DQ[52]  CS1 */
	{ 0, 0x9340, 0x0000 },   /*  SMEM0_DQ[52]  CS2 */
	{ 0, 0x9b40, 0x0000 },   /*  SMEM0_DQ[52]  CS3 */
	{ 0, 0x8344, 0x0000 },   /*  SMEM0_DQ[53]  CS0 */
	{ 0, 0x8b44, 0x0000 },   /*  SMEM0_DQ[53]  CS1 */
	{ 0, 0x9344, 0x0000 },   /*  SMEM0_DQ[53]  CS2 */
	{ 0, 0x9b44, 0x0000 },   /*  SMEM0_DQ[53]  CS3 */
	{ 0, 0x8348, 0x0000 },   /*  SMEM0_DQ[54]  CS0 */
	{ 0, 0x8b48, 0x0000 },   /*  SMEM0_DQ[54]  CS1 */
	{ 0, 0x9348, 0x0000 },   /*  SMEM0_DQ[54]  CS2 */
	{ 0, 0x9b48, 0x0000 },   /*  SMEM0_DQ[54]  CS3 */
	{ 0, 0x834c, 0x0008 },   /*  SMEM0_DQ[55]  CS0 */
	{ 0, 0x8b4c, 0x0008 },   /*  SMEM0_DQ[55]  CS1 */
	{ 0, 0x934c, 0x0008 },   /*  SMEM0_DQ[55]  CS2 */
	{ 0, 0x9b4c, 0x0008 },   /*  SMEM0_DQ[55]  CS3 */
	{ 0, 0x83d0, 0x0004 },   /*  SMEM0_DM[7]  CS0 */
	{ 0, 0x8bd0, 0x0004 },   /*  SMEM0_DM[7]  CS1 */
	{ 0, 0x93d0, 0x0004 },   /*  SMEM0_DM[7]  CS2 */
	{ 0, 0x9bd0, 0x0004 },   /*  SMEM0_DM[7]  CS3 */
	{ 0, 0x8380, 0x0008 },   /*  SMEM0_DQ[56]  CS0 */
	{ 0, 0x8b80, 0x0008 },   /*  SMEM0_DQ[56]  CS1 */
	{ 0, 0x9380, 0x0008 },   /*  SMEM0_DQ[56]  CS2 */
	{ 0, 0x9b80, 0x0008 },   /*  SMEM0_DQ[56]  CS3 */
	{ 0, 0x8384, 0x0004 },   /*  SMEM0_DQ[57]  CS0 */
	{ 0, 0x8b84, 0x0004 },   /*  SMEM0_DQ[57]  CS1 */
	{ 0, 0x9384, 0x0004 },   /*  SMEM0_DQ[57]  CS2 */
	{ 0, 0x9b84, 0x0004 },   /*  SMEM0_DQ[57]  CS3 */
	{ 0, 0x8388, 0x0008 },   /*  SMEM0_DQ[58]  CS0 */
	{ 0, 0x8b88, 0x0008 },   /*  SMEM0_DQ[58]  CS1 */
	{ 0, 0x9388, 0x0008 },   /*  SMEM0_DQ[58]  CS2 */
	{ 0, 0x9b88, 0x0008 },   /*  SMEM0_DQ[58]  CS3 */
	{ 0, 0x838c, 0x0000 },   /*  SMEM0_DQ[59]  CS0 */
	{ 0, 0x8b8c, 0x0000 },   /*  SMEM0_DQ[59]  CS1 */
	{ 0, 0x938c, 0x0000 },   /*  SMEM0_DQ[59]  CS2 */
	{ 0, 0x9b8c, 0x0000 },   /*  SMEM0_DQ[59]  CS3 */
	{ 0, 0x83c0, 0x0000 },   /*  SMEM0_DQ[60]  CS0 */
	{ 0, 0x8bc0, 0x0000 },   /*  SMEM0_DQ[60]  CS1 */
	{ 0, 0x93c0, 0x0000 },   /*  SMEM0_DQ[60]  CS2 */
	{ 0, 0x9bc0, 0x0000 },   /*  SMEM0_DQ[60]  CS3 */
	{ 0, 0x83c4, 0x0000 },   /*  SMEM0_DQ[61]  CS0 */
	{ 0, 0x8bc4, 0x0000 },   /*  SMEM0_DQ[61]  CS1 */
	{ 0, 0x93c4, 0x0000 },   /*  SMEM0_DQ[61]  CS2 */
	{ 0, 0x9bc4, 0x0000 },   /*  SMEM0_DQ[61]  CS3 */
	{ 0, 0x83c8, 0x0000 },   /*  SMEM0_DQ[62]  CS0 */
	{ 0, 0x8bc8, 0x0000 },   /*  SMEM0_DQ[62]  CS1 */
	{ 0, 0x93c8, 0x0000 },   /*  SMEM0_DQ[62]  CS2 */
	{ 0, 0x9bc8, 0x0000 },   /*  SMEM0_DQ[62]  CS3 */
	{ 0, 0x83cc, 0x0000 },   /*  SMEM0_DQ[63]  CS0 */
	{ 0, 0x8bcc, 0x0000 },   /*  SMEM0_DQ[63]  CS1 */
	{ 0, 0x93cc, 0x0000 },   /*  SMEM0_DQ[63]  CS2 */
	{ 0, 0x9bcc, 0x0000 },   /*  SMEM0_DQ[63]  CS3 */
	{ 0, 0x8450, 0x0000 },   /*  SMEM0_DM[8]  CS0 */
	{ 0, 0x8c50, 0x0000 },   /*  SMEM0_DM[8]  CS1 */
	{ 0, 0x9450, 0x0000 },   /*  SMEM0_DM[8]  CS2 */
	{ 0, 0x9c50, 0x0000 },   /*  SMEM0_DM[8]  CS3 */
	{ 0, 0x8400, 0x0004 },   /*  SMEM0_CB[0]  CS0 */
	{ 0, 0x8c00, 0x0004 },   /*  SMEM0_CB[0]  CS1 */
	{ 0, 0x9400, 0x0004 },   /*  SMEM0_CB[0]  CS2 */
	{ 0, 0x9c00, 0x0004 },   /*  SMEM0_CB[0]  CS3 */
	{ 0, 0x8404, 0x0004 },   /*  SMEM0_CB[1]  CS0 */
	{ 0, 0x8c04, 0x0004 },   /*  SMEM0_CB[1]  CS1 */
	{ 0, 0x9404, 0x0004 },   /*  SMEM0_CB[1]  CS2 */
	{ 0, 0x9c04, 0x0004 },   /*  SMEM0_CB[1]  CS3 */
	{ 0, 0x8408, 0x0000 },   /*  SMEM0_CB[2]  CS0 */
	{ 0, 0x8c08, 0x0000 },   /*  SMEM0_CB[2]  CS1 */
	{ 0, 0x9408, 0x0000 },   /*  SMEM0_CB[2]  CS2 */
	{ 0, 0x9c08, 0x0000 },   /*  SMEM0_CB[2]  CS3 */
	{ 0, 0x840c, 0x0004 },   /*  SMEM0_CB[3]  CS0 */
	{ 0, 0x8c0c, 0x0004 },   /*  SMEM0_CB[3]  CS1 */
	{ 0, 0x940c, 0x0004 },   /*  SMEM0_CB[3]  CS2 */
	{ 0, 0x9c0c, 0x0004 },   /*  SMEM0_CB[3]  CS3 */
	{ 0, 0x8440, 0x0004 },   /*  SMEM0_CB[4]  CS0 */
	{ 0, 0x8c40, 0x0004 },   /*  SMEM0_CB[4]  CS1 */
	{ 0, 0x9440, 0x0004 },   /*  SMEM0_CB[4]  CS2 */
	{ 0, 0x9c40, 0x0004 },   /*  SMEM0_CB[4]  CS3 */
	{ 0, 0x8444, 0x0004 },   /*  SMEM0_CB[5]  CS0 */
	{ 0, 0x8c44, 0x0004 },   /*  SMEM0_CB[5]  CS1 */
	{ 0, 0x9444, 0x0004 },   /*  SMEM0_CB[5]  CS2 */
	{ 0, 0x9c44, 0x0004 },   /*  SMEM0_CB[5]  CS3 */
	{ 0, 0x8448, 0x0000 },   /*  SMEM0_CB[6]  CS0 */
	{ 0, 0x8c48, 0x0000 },   /*  SMEM0_CB[6]  CS1 */
	{ 0, 0x9448, 0x0000 },   /*  SMEM0_CB[6]  CS2 */
	{ 0, 0x9c48, 0x0000 },   /*  SMEM0_CB[6]  CS3 */
	{ 0, 0x844c, 0x0004 },   /*  SMEM0_CB[7]  CS0 */
	{ 0, 0x8c4c, 0x0004 },   /*  SMEM0_CB[7]  CS1 */
	{ 0, 0x944c, 0x0004 },   /*  SMEM0_CB[7]  CS2 */
	{ 0, 0x9c4c, 0x0004 },   /*  SMEM0_CB[7]  CS3 */
	{ 1, 0x042c, 0x010c },   /*  SMEM1_CKE[0] ADR01 bit11   */
	{ 1, 0x0818, 0x0100 },   /*  SMEM1_CSB[0] ADR10 bit6   */
	{ 1, 0x0810, 0x0104 },   /*  SMEM1_ODT[0] ADR10 bit4   */
	{ 1, 0x0024, 0x010c },   /*  SMEM1_CKE[1] ADR00 bit9   */
	{ 1, 0x0808, 0x0104 },   /*  SMEM1_CSB[1] ADR10 bit2   */
	{ 1, 0x0814, 0x0100 },   /*  SMEM1_ODT[1] ADR10 bit5   */
	{ 1, 0x0408, 0x0108 },   /*  SMEM1_CKE[2] ADR01 bit2   */
	{ 1, 0x0834, 0x0100 },   /*  SMEM1_CSB[2] ADR10 bit13   */
	{ 1, 0x0824, 0x0104 },   /*  SMEM1_ODT[2] ADR10 bit9   */
	{ 1, 0x041c, 0x0108 },   /*  SMEM1_CKE[3] ADR01 bit7   */
	{ 1, 0x000c, 0x0100 },   /*  SMEM1_CSB[3] ADR00 bit3   */
	{ 1, 0x082c, 0x0100 },   /*  SMEM1_ODT[3] ADR10 bit11   */
	{ 1, 0x0800, 0x010c },   /*  SMEM1_ADDR[0] ADR10 bit0   */
	{ 1, 0x081c, 0x0108 },   /*  SMEM1_ADDR[1] ADR10 bit7   */
	{ 1, 0x040c, 0x0100 },   /*  SMEM1_ADDR[2] ADR01 bit3   */
	{ 1, 0x0020, 0x010c },   /*  SMEM1_ADDR[3] ADR00 bit8   */
	{ 1, 0x0410, 0x0100 },   /*  SMEM1_ADDR[4] ADR01 bit4   */
	{ 1, 0x0418, 0x0100 },   /*  SMEM1_ADDR[5] ADR01 bit6   */
	{ 1, 0x0428, 0x0104 },   /*  SMEM1_ADDR[6] ADR01 bit10   */
	{ 1, 0x0838, 0x0108 },   /*  SMEM1_ADDR[7] ADR10 bit14   */
	{ 1, 0x0014, 0x0108 },   /*  SMEM1_ADDR[8] ADR00 bit5   */
	{ 1, 0x0830, 0x0110 },   /*  SMEM1_ADDR[9] ADR10 bit12   */
	{ 1, 0x080c, 0x0108 },   /*  SMEM1_ADDR[10] ADR10 bit3   */
	{ 1, 0x0028, 0x0110 },   /*  SMEM1_ADDR[11] ADR00 bit10   */
	{ 1, 0x0430, 0x0104 },   /*  SMEM1_ADDR[12] ADR01 bit12   */
	{ 1, 0x0008, 0x0100 },   /*  SMEM1_ADDR[13] ADR00 bit2   */
	{ 1, 0x043c, 0x0104 },   /*  SMEM1_ADDR[14] ADR01 bit15   */
	{ 1, 0x0414, 0x0104 },   /*  SMEM1_ADDR[15] ADR01 bit5   */
	{ 1, 0x0820, 0x0108 },   /*  SMEM1_BA[0] ADR10 bit8   */
	{ 1, 0x002c, 0x0104 },   /*  SMEM1_BA[1] ADR00 bit11   */
	{ 1, 0x0434, 0x0104 },   /*  SMEM1_BA[2] ADR01 bit13   */
	{ 1, 0x0438, 0x010c },   /*  SMEM1_RESETB ADR01 bit14   */
	{ 1, 0x0828, 0x0108 },   /*  SMEM1_RASB ADR10 bit10   */
	{ 1, 0x0804, 0x0108 },   /*  SMEM1_CASB ADR10 bit1   */
	{ 1, 0x0010, 0x0100 },   /*  SMEM1_WEB ADR00 bit4   */
	{ 1, 0x8050, 0x0008 },   /*  SMEM1_DM[0]  CS0 */
	{ 1, 0x8850, 0x0008 },   /*  SMEM1_DM[0]  CS1 */
	{ 1, 0x9050, 0x0008 },   /*  SMEM1_DM[0]  CS2 */
	{ 1, 0x9850, 0x0008 },   /*  SMEM1_DM[0]  CS3 */
	{ 1, 0x8000, 0x0000 },   /*  SMEM1_DQ[0]  CS0 */
	{ 1, 0x8800, 0x0000 },   /*  SMEM1_DQ[0]  CS1 */
	{ 1, 0x9000, 0x0000 },   /*  SMEM1_DQ[0]  CS2 */
	{ 1, 0x9800, 0x0000 },   /*  SMEM1_DQ[0]  CS3 */
	{ 1, 0x8004, 0x0004 },   /*  SMEM1_DQ[1]  CS0 */
	{ 1, 0x8804, 0x0004 },   /*  SMEM1_DQ[1]  CS1 */
	{ 1, 0x9004, 0x0004 },   /*  SMEM1_DQ[1]  CS2 */
	{ 1, 0x9804, 0x0004 },   /*  SMEM1_DQ[1]  CS3 */
	{ 1, 0x8008, 0x0004 },   /*  SMEM1_DQ[2]  CS0 */
	{ 1, 0x8808, 0x0004 },   /*  SMEM1_DQ[2]  CS1 */
	{ 1, 0x9008, 0x0004 },   /*  SMEM1_DQ[2]  CS2 */
	{ 1, 0x9808, 0x0004 },   /*  SMEM1_DQ[2]  CS3 */
	{ 1, 0x800c, 0x0000 },   /*  SMEM1_DQ[3]  CS0 */
	{ 1, 0x880c, 0x0000 },   /*  SMEM1_DQ[3]  CS1 */
	{ 1, 0x900c, 0x0000 },   /*  SMEM1_DQ[3]  CS2 */
	{ 1, 0x980c, 0x0000 },   /*  SMEM1_DQ[3]  CS3 */
	{ 1, 0x8040, 0x0000 },   /*  SMEM1_DQ[4]  CS0 */
	{ 1, 0x8840, 0x0000 },   /*  SMEM1_DQ[4]  CS1 */
	{ 1, 0x9040, 0x0000 },   /*  SMEM1_DQ[4]  CS2 */
	{ 1, 0x9840, 0x0000 },   /*  SMEM1_DQ[4]  CS3 */
	{ 1, 0x8044, 0x0000 },   /*  SMEM1_DQ[5]  CS0 */
	{ 1, 0x8844, 0x0000 },   /*  SMEM1_DQ[5]  CS1 */
	{ 1, 0x9044, 0x0000 },   /*  SMEM1_DQ[5]  CS2 */
	{ 1, 0x9844, 0x0000 },   /*  SMEM1_DQ[5]  CS3 */
	{ 1, 0x8048, 0x0000 },   /*  SMEM1_DQ[6]  CS0 */
	{ 1, 0x8848, 0x0000 },   /*  SMEM1_DQ[6]  CS1 */
	{ 1, 0x9048, 0x0000 },   /*  SMEM1_DQ[6]  CS2 */
	{ 1, 0x9848, 0x0000 },   /*  SMEM1_DQ[6]  CS3 */
	{ 1, 0x804c, 0x0004 },   /*  SMEM1_DQ[7]  CS0 */
	{ 1, 0x884c, 0x0004 },   /*  SMEM1_DQ[7]  CS1 */
	{ 1, 0x904c, 0x0004 },   /*  SMEM1_DQ[7]  CS2 */
	{ 1, 0x984c, 0x0004 },   /*  SMEM1_DQ[7]  CS3 */
	{ 1, 0x80d0, 0x0004 },   /*  SMEM1_DM[1]  CS0 */
	{ 1, 0x88d0, 0x0004 },   /*  SMEM1_DM[1]  CS1 */
	{ 1, 0x90d0, 0x0004 },   /*  SMEM1_DM[1]  CS2 */
	{ 1, 0x98d0, 0x0004 },   /*  SMEM1_DM[1]  CS3 */
	{ 1, 0x8080, 0x0004 },   /*  SMEM1_DQ[8]  CS0 */
	{ 1, 0x8880, 0x0004 },   /*  SMEM1_DQ[8]  CS1 */
	{ 1, 0x9080, 0x0004 },   /*  SMEM1_DQ[8]  CS2 */
	{ 1, 0x9880, 0x0004 },   /*  SMEM1_DQ[8]  CS3 */
	{ 1, 0x8084, 0x0004 },   /*  SMEM1_DQ[9]  CS0 */
	{ 1, 0x8884, 0x0004 },   /*  SMEM1_DQ[9]  CS1 */
	{ 1, 0x9084, 0x0004 },   /*  SMEM1_DQ[9]  CS2 */
	{ 1, 0x9884, 0x0004 },   /*  SMEM1_DQ[9]  CS3 */
	{ 1, 0x8088, 0x0004 },   /*  SMEM1_DQ[10]  CS0 */
	{ 1, 0x8888, 0x0004 },   /*  SMEM1_DQ[10]  CS1 */
	{ 1, 0x9088, 0x0004 },   /*  SMEM1_DQ[10]  CS2 */
	{ 1, 0x9888, 0x0004 },   /*  SMEM1_DQ[10]  CS3 */
	{ 1, 0x808c, 0x0004 },   /*  SMEM1_DQ[11]  CS0 */
	{ 1, 0x888c, 0x0004 },   /*  SMEM1_DQ[11]  CS1 */
	{ 1, 0x908c, 0x0004 },   /*  SMEM1_DQ[11]  CS2 */
	{ 1, 0x988c, 0x0004 },   /*  SMEM1_DQ[11]  CS3 */
	{ 1, 0x80c0, 0x0004 },   /*  SMEM1_DQ[12]  CS0 */
	{ 1, 0x88c0, 0x0004 },   /*  SMEM1_DQ[12]  CS1 */
	{ 1, 0x90c0, 0x0004 },   /*  SMEM1_DQ[12]  CS2 */
	{ 1, 0x98c0, 0x0004 },   /*  SMEM1_DQ[12]  CS3 */
	{ 1, 0x80c4, 0x0004 },   /*  SMEM1_DQ[13]  CS0 */
	{ 1, 0x88c4, 0x0004 },   /*  SMEM1_DQ[13]  CS1 */
	{ 1, 0x90c4, 0x0004 },   /*  SMEM1_DQ[13]  CS2 */
	{ 1, 0x98c4, 0x0004 },   /*  SMEM1_DQ[13]  CS3 */
	{ 1, 0x80c8, 0x0008 },   /*  SMEM1_DQ[14]  CS0 */
	{ 1, 0x88c8, 0x0008 },   /*  SMEM1_DQ[14]  CS1 */
	{ 1, 0x90c8, 0x0008 },   /*  SMEM1_DQ[14]  CS2 */
	{ 1, 0x98c8, 0x0008 },   /*  SMEM1_DQ[14]  CS3 */
	{ 1, 0x80cc, 0x0004 },   /*  SMEM1_DQ[15]  CS0 */
	{ 1, 0x88cc, 0x0004 },   /*  SMEM1_DQ[15]  CS1 */
	{ 1, 0x90cc, 0x0004 },   /*  SMEM1_DQ[15]  CS2 */
	{ 1, 0x98cc, 0x0004 },   /*  SMEM1_DQ[15]  CS3 */
	{ 1, 0x8150, 0x0004 },   /*  SMEM1_DM[2]  CS0 */
	{ 1, 0x8950, 0x0004 },   /*  SMEM1_DM[2]  CS1 */
	{ 1, 0x9150, 0x0004 },   /*  SMEM1_DM[2]  CS2 */
	{ 1, 0x9950, 0x0004 },   /*  SMEM1_DM[2]  CS3 */
	{ 1, 0x8100, 0x0004 },   /*  SMEM1_DQ[16]  CS0 */
	{ 1, 0x8900, 0x0004 },   /*  SMEM1_DQ[16]  CS1 */
	{ 1, 0x9100, 0x0004 },   /*  SMEM1_DQ[16]  CS2 */
	{ 1, 0x9900, 0x0004 },   /*  SMEM1_DQ[16]  CS3 */
	{ 1, 0x8104, 0x0000 },   /*  SMEM1_DQ[17]  CS0 */
	{ 1, 0x8904, 0x0000 },   /*  SMEM1_DQ[17]  CS1 */
	{ 1, 0x9104, 0x0000 },   /*  SMEM1_DQ[17]  CS2 */
	{ 1, 0x9904, 0x0000 },   /*  SMEM1_DQ[17]  CS3 */
	{ 1, 0x8108, 0x0000 },   /*  SMEM1_DQ[18]  CS0 */
	{ 1, 0x8908, 0x0000 },   /*  SMEM1_DQ[18]  CS1 */
	{ 1, 0x9108, 0x0000 },   /*  SMEM1_DQ[18]  CS2 */
	{ 1, 0x9908, 0x0000 },   /*  SMEM1_DQ[18]  CS3 */
	{ 1, 0x810c, 0x0000 },   /*  SMEM1_DQ[19]  CS0 */
	{ 1, 0x890c, 0x0000 },   /*  SMEM1_DQ[19]  CS1 */
	{ 1, 0x910c, 0x0000 },   /*  SMEM1_DQ[19]  CS2 */
	{ 1, 0x990c, 0x0000 },   /*  SMEM1_DQ[19]  CS3 */
	{ 1, 0x8140, 0x0000 },   /*  SMEM1_DQ[20]  CS0 */
	{ 1, 0x8940, 0x0000 },   /*  SMEM1_DQ[20]  CS1 */
	{ 1, 0x9140, 0x0000 },   /*  SMEM1_DQ[20]  CS2 */
	{ 1, 0x9940, 0x0000 },   /*  SMEM1_DQ[20]  CS3 */
	{ 1, 0x8144, 0x0000 },   /*  SMEM1_DQ[21]  CS0 */
	{ 1, 0x8944, 0x0000 },   /*  SMEM1_DQ[21]  CS1 */
	{ 1, 0x9144, 0x0000 },   /*  SMEM1_DQ[21]  CS2 */
	{ 1, 0x9944, 0x0000 },   /*  SMEM1_DQ[21]  CS3 */
	{ 1, 0x8148, 0x0000 },   /*  SMEM1_DQ[22]  CS0 */
	{ 1, 0x8948, 0x0000 },   /*  SMEM1_DQ[22]  CS1 */
	{ 1, 0x9148, 0x0000 },   /*  SMEM1_DQ[22]  CS2 */
	{ 1, 0x9948, 0x0000 },   /*  SMEM1_DQ[22]  CS3 */
	{ 1, 0x814c, 0x0000 },   /*  SMEM1_DQ[23]  CS0 */
	{ 1, 0x894c, 0x0000 },   /*  SMEM1_DQ[23]  CS1 */
	{ 1, 0x914c, 0x0000 },   /*  SMEM1_DQ[23]  CS2 */
	{ 1, 0x994c, 0x0000 },   /*  SMEM1_DQ[23]  CS3 */
	{ 1, 0x81d0, 0x0004 },   /*  SMEM1_DM[3]  CS0 */
	{ 1, 0x89d0, 0x0004 },   /*  SMEM1_DM[3]  CS1 */
	{ 1, 0x91d0, 0x0004 },   /*  SMEM1_DM[3]  CS2 */
	{ 1, 0x99d0, 0x0004 },   /*  SMEM1_DM[3]  CS3 */
	{ 1, 0x8180, 0x0000 },   /*  SMEM1_DQ[24]  CS0 */
	{ 1, 0x8980, 0x0000 },   /*  SMEM1_DQ[24]  CS1 */
	{ 1, 0x9180, 0x0000 },   /*  SMEM1_DQ[24]  CS2 */
	{ 1, 0x9980, 0x0000 },   /*  SMEM1_DQ[24]  CS3 */
	{ 1, 0x8184, 0x0004 },   /*  SMEM1_DQ[25]  CS0 */
	{ 1, 0x8984, 0x0004 },   /*  SMEM1_DQ[25]  CS1 */
	{ 1, 0x9184, 0x0004 },   /*  SMEM1_DQ[25]  CS2 */
	{ 1, 0x9984, 0x0004 },   /*  SMEM1_DQ[25]  CS3 */
	{ 1, 0x8188, 0x0004 },   /*  SMEM1_DQ[26]  CS0 */
	{ 1, 0x8988, 0x0004 },   /*  SMEM1_DQ[26]  CS1 */
	{ 1, 0x9188, 0x0004 },   /*  SMEM1_DQ[26]  CS2 */
	{ 1, 0x9988, 0x0004 },   /*  SMEM1_DQ[26]  CS3 */
	{ 1, 0x818c, 0x0000 },   /*  SMEM1_DQ[27]  CS0 */
	{ 1, 0x898c, 0x0000 },   /*  SMEM1_DQ[27]  CS1 */
	{ 1, 0x918c, 0x0000 },   /*  SMEM1_DQ[27]  CS2 */
	{ 1, 0x998c, 0x0000 },   /*  SMEM1_DQ[27]  CS3 */
	{ 1, 0x81c0, 0x0004 },   /*  SMEM1_DQ[28]  CS0 */
	{ 1, 0x89c0, 0x0004 },   /*  SMEM1_DQ[28]  CS1 */
	{ 1, 0x91c0, 0x0004 },   /*  SMEM1_DQ[28]  CS2 */
	{ 1, 0x99c0, 0x0004 },   /*  SMEM1_DQ[28]  CS3 */
	{ 1, 0x81c4, 0x0004 },   /*  SMEM1_DQ[29]  CS0 */
	{ 1, 0x89c4, 0x0004 },   /*  SMEM1_DQ[29]  CS1 */
	{ 1, 0x91c4, 0x0004 },   /*  SMEM1_DQ[29]  CS2 */
	{ 1, 0x99c4, 0x0004 },   /*  SMEM1_DQ[29]  CS3 */
	{ 1, 0x81c8, 0x0004 },   /*  SMEM1_DQ[30]  CS0 */
	{ 1, 0x89c8, 0x0004 },   /*  SMEM1_DQ[30]  CS1 */
	{ 1, 0x91c8, 0x0004 },   /*  SMEM1_DQ[30]  CS2 */
	{ 1, 0x99c8, 0x0004 },   /*  SMEM1_DQ[30]  CS3 */
	{ 1, 0x81cc, 0x0004 },   /*  SMEM1_DQ[31]  CS0 */
	{ 1, 0x89cc, 0x0004 },   /*  SMEM1_DQ[31]  CS1 */
	{ 1, 0x91cc, 0x0004 },   /*  SMEM1_DQ[31]  CS2 */
	{ 1, 0x99cc, 0x0004 },   /*  SMEM1_DQ[31]  CS3 */
	{ 1, 0x8250, 0x0004 },   /*  SMEM1_DM[4]  CS0 */
	{ 1, 0x8a50, 0x0004 },   /*  SMEM1_DM[4]  CS1 */
	{ 1, 0x9250, 0x0004 },   /*  SMEM1_DM[4]  CS2 */
	{ 1, 0x9a50, 0x0004 },   /*  SMEM1_DM[4]  CS3 */
	{ 1, 0x8200, 0x0000 },   /*  SMEM1_DQ[32]  CS0 */
	{ 1, 0x8a00, 0x0000 },   /*  SMEM1_DQ[32]  CS1 */
	{ 1, 0x9200, 0x0000 },   /*  SMEM1_DQ[32]  CS2 */
	{ 1, 0x9a00, 0x0000 },   /*  SMEM1_DQ[32]  CS3 */
	{ 1, 0x8204, 0x0004 },   /*  SMEM1_DQ[33]  CS0 */
	{ 1, 0x8a04, 0x0004 },   /*  SMEM1_DQ[33]  CS1 */
	{ 1, 0x9204, 0x0004 },   /*  SMEM1_DQ[33]  CS2 */
	{ 1, 0x9a04, 0x0004 },   /*  SMEM1_DQ[33]  CS3 */
	{ 1, 0x8208, 0x0004 },   /*  SMEM1_DQ[34]  CS0 */
	{ 1, 0x8a08, 0x0004 },   /*  SMEM1_DQ[34]  CS1 */
	{ 1, 0x9208, 0x0004 },   /*  SMEM1_DQ[34]  CS2 */
	{ 1, 0x9a08, 0x0004 },   /*  SMEM1_DQ[34]  CS3 */
	{ 1, 0x820c, 0x0004 },   /*  SMEM1_DQ[35]  CS0 */
	{ 1, 0x8a0c, 0x0004 },   /*  SMEM1_DQ[35]  CS1 */
	{ 1, 0x920c, 0x0004 },   /*  SMEM1_DQ[35]  CS2 */
	{ 1, 0x9a0c, 0x0004 },   /*  SMEM1_DQ[35]  CS3 */
	{ 1, 0x8240, 0x0000 },   /*  SMEM1_DQ[36]  CS0 */
	{ 1, 0x8a40, 0x0000 },   /*  SMEM1_DQ[36]  CS1 */
	{ 1, 0x9240, 0x0000 },   /*  SMEM1_DQ[36]  CS2 */
	{ 1, 0x9a40, 0x0000 },   /*  SMEM1_DQ[36]  CS3 */
	{ 1, 0x8244, 0x0004 },   /*  SMEM1_DQ[37]  CS0 */
	{ 1, 0x8a44, 0x0004 },   /*  SMEM1_DQ[37]  CS1 */
	{ 1, 0x9244, 0x0004 },   /*  SMEM1_DQ[37]  CS2 */
	{ 1, 0x9a44, 0x0004 },   /*  SMEM1_DQ[37]  CS3 */
	{ 1, 0x8248, 0x0004 },   /*  SMEM1_DQ[38]  CS0 */
	{ 1, 0x8a48, 0x0004 },   /*  SMEM1_DQ[38]  CS1 */
	{ 1, 0x9248, 0x0004 },   /*  SMEM1_DQ[38]  CS2 */
	{ 1, 0x9a48, 0x0004 },   /*  SMEM1_DQ[38]  CS3 */
	{ 1, 0x824c, 0x0000 },   /*  SMEM1_DQ[39]  CS0 */
	{ 1, 0x8a4c, 0x0000 },   /*  SMEM1_DQ[39]  CS1 */
	{ 1, 0x924c, 0x0000 },   /*  SMEM1_DQ[39]  CS2 */
	{ 1, 0x9a4c, 0x0000 },   /*  SMEM1_DQ[39]  CS3 */
	{ 1, 0x82d0, 0x0004 },   /*  SMEM1_DM[5]  CS0 */
	{ 1, 0x8ad0, 0x0004 },   /*  SMEM1_DM[5]  CS1 */
	{ 1, 0x92d0, 0x0004 },   /*  SMEM1_DM[5]  CS2 */
	{ 1, 0x9ad0, 0x0004 },   /*  SMEM1_DM[5]  CS3 */
	{ 1, 0x8280, 0x0000 },   /*  SMEM1_DQ[40]  CS0 */
	{ 1, 0x8a80, 0x0000 },   /*  SMEM1_DQ[40]  CS1 */
	{ 1, 0x9280, 0x0000 },   /*  SMEM1_DQ[40]  CS2 */
	{ 1, 0x9a80, 0x0000 },   /*  SMEM1_DQ[40]  CS3 */
	{ 1, 0x8284, 0x0000 },   /*  SMEM1_DQ[41]  CS0 */
	{ 1, 0x8a84, 0x0000 },   /*  SMEM1_DQ[41]  CS1 */
	{ 1, 0x9284, 0x0000 },   /*  SMEM1_DQ[41]  CS2 */
	{ 1, 0x9a84, 0x0000 },   /*  SMEM1_DQ[41]  CS3 */
	{ 1, 0x8288, 0x0000 },   /*  SMEM1_DQ[42]  CS0 */
	{ 1, 0x8a88, 0x0000 },   /*  SMEM1_DQ[42]  CS1 */
	{ 1, 0x9288, 0x0000 },   /*  SMEM1_DQ[42]  CS2 */
	{ 1, 0x9a88, 0x0000 },   /*  SMEM1_DQ[42]  CS3 */
	{ 1, 0x828c, 0x0000 },   /*  SMEM1_DQ[43]  CS0 */
	{ 1, 0x8a8c, 0x0000 },   /*  SMEM1_DQ[43]  CS1 */
	{ 1, 0x928c, 0x0000 },   /*  SMEM1_DQ[43]  CS2 */
	{ 1, 0x9a8c, 0x0000 },   /*  SMEM1_DQ[43]  CS3 */
	{ 1, 0x82c0, 0x0000 },   /*  SMEM1_DQ[44]  CS0 */
	{ 1, 0x8ac0, 0x0000 },   /*  SMEM1_DQ[44]  CS1 */
	{ 1, 0x92c0, 0x0000 },   /*  SMEM1_DQ[44]  CS2 */
	{ 1, 0x9ac0, 0x0000 },   /*  SMEM1_DQ[44]  CS3 */
	{ 1, 0x82c4, 0x0000 },   /*  SMEM1_DQ[45]  CS0 */
	{ 1, 0x8ac4, 0x0000 },   /*  SMEM1_DQ[45]  CS1 */
	{ 1, 0x92c4, 0x0000 },   /*  SMEM1_DQ[45]  CS2 */
	{ 1, 0x9ac4, 0x0000 },   /*  SMEM1_DQ[45]  CS3 */
	{ 1, 0x82c8, 0x0008 },   /*  SMEM1_DQ[46]  CS0 */
	{ 1, 0x8ac8, 0x0008 },   /*  SMEM1_DQ[46]  CS1 */
	{ 1, 0x92c8, 0x0008 },   /*  SMEM1_DQ[46]  CS2 */
	{ 1, 0x9ac8, 0x0008 },   /*  SMEM1_DQ[46]  CS3 */
	{ 1, 0x82cc, 0x0000 },   /*  SMEM1_DQ[47]  CS0 */
	{ 1, 0x8acc, 0x0000 },   /*  SMEM1_DQ[47]  CS1 */
	{ 1, 0x92cc, 0x0000 },   /*  SMEM1_DQ[47]  CS2 */
	{ 1, 0x9acc, 0x0000 },   /*  SMEM1_DQ[47]  CS3 */
	{ 1, 0x8350, 0x0004 },   /*  SMEM1_DM[6]  CS0 */
	{ 1, 0x8b50, 0x0004 },   /*  SMEM1_DM[6]  CS1 */
	{ 1, 0x9350, 0x0004 },   /*  SMEM1_DM[6]  CS2 */
	{ 1, 0x9b50, 0x0004 },   /*  SMEM1_DM[6]  CS3 */
	{ 1, 0x8300, 0x0000 },   /*  SMEM1_DQ[48]  CS0 */
	{ 1, 0x8b00, 0x0000 },   /*  SMEM1_DQ[48]  CS1 */
	{ 1, 0x9300, 0x0000 },   /*  SMEM1_DQ[48]  CS2 */
	{ 1, 0x9b00, 0x0000 },   /*  SMEM1_DQ[48]  CS3 */
	{ 1, 0x8304, 0x0000 },   /*  SMEM1_DQ[49]  CS0 */
	{ 1, 0x8b04, 0x0000 },   /*  SMEM1_DQ[49]  CS1 */
	{ 1, 0x9304, 0x0000 },   /*  SMEM1_DQ[49]  CS2 */
	{ 1, 0x9b04, 0x0000 },   /*  SMEM1_DQ[49]  CS3 */
	{ 1, 0x8308, 0x0000 },   /*  SMEM1_DQ[50]  CS0 */
	{ 1, 0x8b08, 0x0000 },   /*  SMEM1_DQ[50]  CS1 */
	{ 1, 0x9308, 0x0000 },   /*  SMEM1_DQ[50]  CS2 */
	{ 1, 0x9b08, 0x0000 },   /*  SMEM1_DQ[50]  CS3 */
	{ 1, 0x830c, 0x0004 },   /*  SMEM1_DQ[51]  CS0 */
	{ 1, 0x8b0c, 0x0004 },   /*  SMEM1_DQ[51]  CS1 */
	{ 1, 0x930c, 0x0004 },   /*  SMEM1_DQ[51]  CS2 */
	{ 1, 0x9b0c, 0x0004 },   /*  SMEM1_DQ[51]  CS3 */
	{ 1, 0x8340, 0x0000 },   /*  SMEM1_DQ[52]  CS0 */
	{ 1, 0x8b40, 0x0000 },   /*  SMEM1_DQ[52]  CS1 */
	{ 1, 0x9340, 0x0000 },   /*  SMEM1_DQ[52]  CS2 */
	{ 1, 0x9b40, 0x0000 },   /*  SMEM1_DQ[52]  CS3 */
	{ 1, 0x8344, 0x0000 },   /*  SMEM1_DQ[53]  CS0 */
	{ 1, 0x8b44, 0x0000 },   /*  SMEM1_DQ[53]  CS1 */
	{ 1, 0x9344, 0x0000 },   /*  SMEM1_DQ[53]  CS2 */
	{ 1, 0x9b44, 0x0000 },   /*  SMEM1_DQ[53]  CS3 */
	{ 1, 0x8348, 0x0004 },   /*  SMEM1_DQ[54]  CS0 */
	{ 1, 0x8b48, 0x0004 },   /*  SMEM1_DQ[54]  CS1 */
	{ 1, 0x9348, 0x0004 },   /*  SMEM1_DQ[54]  CS2 */
	{ 1, 0x9b48, 0x0004 },   /*  SMEM1_DQ[54]  CS3 */
	{ 1, 0x834c, 0x0000 },   /*  SMEM1_DQ[55]  CS0 */
	{ 1, 0x8b4c, 0x0000 },   /*  SMEM1_DQ[55]  CS1 */
	{ 1, 0x934c, 0x0000 },   /*  SMEM1_DQ[55]  CS2 */
	{ 1, 0x9b4c, 0x0000 },   /*  SMEM1_DQ[55]  CS3 */
	{ 1, 0x83d0, 0x0004 },   /*  SMEM1_DM[7]  CS0 */
	{ 1, 0x8bd0, 0x0004 },   /*  SMEM1_DM[7]  CS1 */
	{ 1, 0x93d0, 0x0004 },   /*  SMEM1_DM[7]  CS2 */
	{ 1, 0x9bd0, 0x0004 },   /*  SMEM1_DM[7]  CS3 */
	{ 1, 0x8380, 0x0000 },   /*  SMEM1_DQ[56]  CS0 */
	{ 1, 0x8b80, 0x0000 },   /*  SMEM1_DQ[56]  CS1 */
	{ 1, 0x9380, 0x0000 },   /*  SMEM1_DQ[56]  CS2 */
	{ 1, 0x9b80, 0x0000 },   /*  SMEM1_DQ[56]  CS3 */
	{ 1, 0x8384, 0x0004 },   /*  SMEM1_DQ[57]  CS0 */
	{ 1, 0x8b84, 0x0004 },   /*  SMEM1_DQ[57]  CS1 */
	{ 1, 0x9384, 0x0004 },   /*  SMEM1_DQ[57]  CS2 */
	{ 1, 0x9b84, 0x0004 },   /*  SMEM1_DQ[57]  CS3 */
	{ 1, 0x8388, 0x0000 },   /*  SMEM1_DQ[58]  CS0 */
	{ 1, 0x8b88, 0x0000 },   /*  SMEM1_DQ[58]  CS1 */
	{ 1, 0x9388, 0x0000 },   /*  SMEM1_DQ[58]  CS2 */
	{ 1, 0x9b88, 0x0000 },   /*  SMEM1_DQ[58]  CS3 */
	{ 1, 0x838c, 0x0004 },   /*  SMEM1_DQ[59]  CS0 */
	{ 1, 0x8b8c, 0x0004 },   /*  SMEM1_DQ[59]  CS1 */
	{ 1, 0x938c, 0x0004 },   /*  SMEM1_DQ[59]  CS2 */
	{ 1, 0x9b8c, 0x0004 },   /*  SMEM1_DQ[59]  CS3 */
	{ 1, 0x83c0, 0x0004 },   /*  SMEM1_DQ[60]  CS0 */
	{ 1, 0x8bc0, 0x0004 },   /*  SMEM1_DQ[60]  CS1 */
	{ 1, 0x93c0, 0x0004 },   /*  SMEM1_DQ[60]  CS2 */
	{ 1, 0x9bc0, 0x0004 },   /*  SMEM1_DQ[60]  CS3 */
	{ 1, 0x83c4, 0x0004 },   /*  SMEM1_DQ[61]  CS0 */
	{ 1, 0x8bc4, 0x0004 },   /*  SMEM1_DQ[61]  CS1 */
	{ 1, 0x93c4, 0x0004 },   /*  SMEM1_DQ[61]  CS2 */
	{ 1, 0x9bc4, 0x0004 },   /*  SMEM1_DQ[61]  CS3 */
	{ 1, 0x83c8, 0x0000 },   /*  SMEM1_DQ[62]  CS0 */
	{ 1, 0x8bc8, 0x0000 },   /*  SMEM1_DQ[62]  CS1 */
	{ 1, 0x93c8, 0x0000 },   /*  SMEM1_DQ[62]  CS2 */
	{ 1, 0x9bc8, 0x0000 },   /*  SMEM1_DQ[62]  CS3 */
	{ 1, 0x83cc, 0x0000 },   /*  SMEM1_DQ[63]  CS0 */
	{ 1, 0x8bcc, 0x0000 },   /*  SMEM1_DQ[63]  CS1 */
	{ 1, 0x93cc, 0x0000 },   /*  SMEM1_DQ[63]  CS2 */
	{ 1, 0x9bcc, 0x0000 },   /*  SMEM1_DQ[63]  CS3 */
	{ 1, 0x8450, 0x0004 },   /*  SMEM1_DM[8]  CS0 */
	{ 1, 0x8c50, 0x0004 },   /*  SMEM1_DM[8]  CS1 */
	{ 1, 0x9450, 0x0004 },   /*  SMEM1_DM[8]  CS2 */
	{ 1, 0x9c50, 0x0004 },   /*  SMEM1_DM[8]  CS3 */
	{ 1, 0x8400, 0x0008 },   /*  SMEM1_CB[0]  CS0 */
	{ 1, 0x8c00, 0x0008 },   /*  SMEM1_CB[0]  CS1 */
	{ 1, 0x9400, 0x0008 },   /*  SMEM1_CB[0]  CS2 */
	{ 1, 0x9c00, 0x0008 },   /*  SMEM1_CB[0]  CS3 */
	{ 1, 0x8404, 0x0004 },   /*  SMEM1_CB[1]  CS0 */
	{ 1, 0x8c04, 0x0004 },   /*  SMEM1_CB[1]  CS1 */
	{ 1, 0x9404, 0x0004 },   /*  SMEM1_CB[1]  CS2 */
	{ 1, 0x9c04, 0x0004 },   /*  SMEM1_CB[1]  CS3 */
	{ 1, 0x8408, 0x0000 },   /*  SMEM1_CB[2]  CS0 */
	{ 1, 0x8c08, 0x0000 },   /*  SMEM1_CB[2]  CS1 */
	{ 1, 0x9408, 0x0000 },   /*  SMEM1_CB[2]  CS2 */
	{ 1, 0x9c08, 0x0000 },   /*  SMEM1_CB[2]  CS3 */
	{ 1, 0x840c, 0x0000 },   /*  SMEM1_CB[3]  CS0 */
	{ 1, 0x8c0c, 0x0000 },   /*  SMEM1_CB[3]  CS1 */
	{ 1, 0x940c, 0x0000 },   /*  SMEM1_CB[3]  CS2 */
	{ 1, 0x9c0c, 0x0000 },   /*  SMEM1_CB[3]  CS3 */
	{ 1, 0x8440, 0x0008 },   /*  SMEM1_CB[4]  CS0 */
	{ 1, 0x8c40, 0x0008 },   /*  SMEM1_CB[4]  CS1 */
	{ 1, 0x9440, 0x0008 },   /*  SMEM1_CB[4]  CS2 */
	{ 1, 0x9c40, 0x0008 },   /*  SMEM1_CB[4]  CS3 */
	{ 1, 0x8444, 0x0004 },   /*  SMEM1_CB[5]  CS0 */
	{ 1, 0x8c44, 0x0004 },   /*  SMEM1_CB[5]  CS1 */
	{ 1, 0x9444, 0x0004 },   /*  SMEM1_CB[5]  CS2 */
	{ 1, 0x9c44, 0x0004 },   /*  SMEM1_CB[5]  CS3 */
	{ 1, 0x8448, 0x0008 },   /*  SMEM1_CB[6]  CS0 */
	{ 1, 0x8c48, 0x0008 },   /*  SMEM1_CB[6]  CS1 */
	{ 1, 0x9448, 0x0008 },   /*  SMEM1_CB[6]  CS2 */
	{ 1, 0x9c48, 0x0008 },   /*  SMEM1_CB[6]  CS3 */
	{ 1, 0x844c, 0x0008 },   /*  SMEM1_CB[7]  CS0 */
	{ 1, 0x8c4c, 0x0008 },   /*  SMEM1_CB[7]  CS1 */
	{ 1, 0x944c, 0x0008 },   /*  SMEM1_CB[7]  CS2 */
	{ 1, 0x9c4c, 0x0008 },   /*  SMEM1_CB[7]  CS3 */
};

#else

static unsigned short delay_table_offsets[] = {
	0x8, 0xc, 0x10, 0x14, 0x20, 0x24, 0x28, 0x2c, 0x408, 0x40c,
	0x410, 0x414, 0x418, 0x41c, 0x428, 0x42c, 0x430, 0x434, 0x438,
	0x43c, 0x800, 0x804, 0x808, 0x80c, 0x810, 0x814, 0x818, 0x81c,
	0x820, 0x824, 0x828, 0x82c, 0x830, 0x834, 0x838, 0x8000,
	0x8004, 0x8008, 0x800c, 0x8040, 0x8044, 0x8048, 0x804c,
	0x8050, 0x8080, 0x8084, 0x8088, 0x808c, 0x80c0, 0x80c4,
	0x80c8, 0x80cc, 0x80d0, 0x8100, 0x8104, 0x8108, 0x810c,
	0x8140, 0x8144, 0x8148, 0x814c, 0x8150, 0x8180, 0x8184,
	0x8188, 0x818c, 0x81c0, 0x81c4, 0x81c8, 0x81cc, 0x81d0,
	0x8200, 0x8204, 0x8208, 0x820c, 0x8240, 0x8244, 0x8248,
	0x824c, 0x8250, 0x8280, 0x8284, 0x8288, 0x828c, 0x82c0,
	0x82c4, 0x82c8, 0x82cc, 0x82d0, 0x8300, 0x8304, 0x8308,
	0x830c, 0x8340, 0x8344, 0x8348, 0x834c, 0x8350, 0x8380,
	0x8384, 0x8388, 0x838c, 0x83c0, 0x83c4, 0x83c8, 0x83cc,
	0x83d0, 0x8400, 0x8404, 0x8408, 0x840c, 0x8440, 0x8444,
	0x8448, 0x844c, 0x8450, 0x8800, 0x8804, 0x8808, 0x880c,
	0x8840, 0x8844, 0x8848, 0x884c, 0x8850, 0x8880, 0x8884,
	0x8888, 0x888c, 0x88c0, 0x88c4, 0x88c8, 0x88cc, 0x88d0,
	0x8900, 0x8904, 0x8908, 0x890c, 0x8940, 0x8944, 0x8948,
	0x894c, 0x8950, 0x8980, 0x8984, 0x8988, 0x898c, 0x89c0,
	0x89c4, 0x89c8, 0x89cc, 0x89d0, 0x8a00, 0x8a04, 0x8a08,
	0x8a0c, 0x8a40, 0x8a44, 0x8a48, 0x8a4c, 0x8a50, 0x8a80,
	0x8a84, 0x8a88, 0x8a8c, 0x8ac0, 0x8ac4, 0x8ac8, 0x8acc,
	0x8ad0, 0x8b00, 0x8b04, 0x8b08, 0x8b0c, 0x8b40, 0x8b44,
	0x8b48, 0x8b4c, 0x8b50, 0x8b80, 0x8b84, 0x8b88, 0x8b8c,
	0x8bc0, 0x8bc4, 0x8bc8, 0x8bcc, 0x8bd0, 0x8c00, 0x8c04,
	0x8c08, 0x8c0c, 0x8c40, 0x8c44, 0x8c48, 0x8c4c, 0x8c50,
	0x9000, 0x9004, 0x9008, 0x900c, 0x9040, 0x9044, 0x9048,
	0x904c, 0x9050, 0x9080, 0x9084, 0x9088, 0x908c, 0x90c0,
	0x90c4, 0x90c8, 0x90cc, 0x90d0, 0x9100, 0x9104, 0x9108,
	0x910c, 0x9140, 0x9144, 0x9148, 0x914c, 0x9150, 0x9180,
	0x9184, 0x9188, 0x918c, 0x91c0, 0x91c4, 0x91c8, 0x91cc,
	0x91d0, 0x9200, 0x9204, 0x9208, 0x920c, 0x9240, 0x9244,
	0x9248, 0x924c, 0x9250, 0x9280, 0x9284, 0x9288, 0x928c,
	0x92c0, 0x92c4, 0x92c8, 0x92cc, 0x92d0, 0x9300, 0x9304,
	0x9308, 0x930c, 0x9340, 0x9344, 0x9348, 0x934c, 0x9350,
	0x9380, 0x9384, 0x9388, 0x938c, 0x93c0, 0x93c4, 0x93c8,
	0x93cc, 0x93d0, 0x9400, 0x9404, 0x9408, 0x940c, 0x9440,
	0x9444, 0x9448, 0x944c, 0x9450, 0x9800, 0x9804, 0x9808,
	0x980c, 0x9840, 0x9844, 0x9848, 0x984c, 0x9850, 0x9880,
	0x9884, 0x9888, 0x988c, 0x98c0, 0x98c4, 0x98c8, 0x98cc,
	0x98d0, 0x9900, 0x9904, 0x9908, 0x990c, 0x9940, 0x9944,
	0x9948, 0x994c, 0x9950, 0x9980, 0x9984, 0x9988, 0x998c,
	0x99c0, 0x99c4, 0x99c8, 0x99cc, 0x99d0, 0x9a00, 0x9a04,
	0x9a08, 0x9a0c, 0x9a40, 0x9a44, 0x9a48, 0x9a4c, 0x9a50,
	0x9a80, 0x9a84, 0x9a88, 0x9a8c, 0x9ac0, 0x9ac4, 0x9ac8,
	0x9acc, 0x9ad0, 0x9b00, 0x9b04, 0x9b08, 0x9b0c, 0x9b40,
	0x9b44, 0x9b48, 0x9b4c, 0x9b50, 0x9b80, 0x9b84, 0x9b88,
	0x9b8c, 0x9bc0, 0x9bc4, 0x9bc8, 0x9bcc, 0x9bd0, 0x9c00,
	0x9c04, 0x9c08, 0x9c0c, 0x9c40, 0x9c44, 0x9c48, 0x9c4c,
	0x9c50
};

static unsigned short delay_table_values[] = {
	0x0, 0x4, 0x8, 0x100, 0x104, 0x108, 0x10c, 0x110, 0x114
};

typedef struct {
	unsigned short offset :12;
	unsigned short value  :4;
} delay_table_t;

delay_table_t delay_table_sm0[] = {
	{0xf, 0x3}, {0x1a, 0x3}, {0x18, 0x3}, {0x5, 0x3}, {0x16, 0x3},
	{0x19, 0x3}, {0x8, 0x3}, {0x21, 0x3}, {0x1d, 0x3}, {0xd, 0x4},
	{0x1, 0x3}, {0x1f, 0x4}, {0x14, 0x3}, {0x1b, 0x4}, {0x9, 0x3},
	{0x4, 0x4}, {0xa, 0x4}, {0xc, 0x4}, {0xe, 0x5}, {0x22, 0x8},
	{0x3, 0x6}, {0x20, 0x6}, {0x17, 0x7}, {0x6, 0x4}, {0x10, 0x4},
	{0x0, 0x5}, {0x13, 0x6}, {0xb, 0x6}, {0x1c, 0x5}, {0x7, 0x5},
	{0x11, 0x5}, {0x12, 0x3}, {0x1e, 0x5}, {0x15, 0x3}, {0x2, 0x4},
	{0x2b, 0x0}, {0x7c, 0x0}, {0xcd, 0x0}, {0x11e, 0x0}, {0x23, 0x1},
	{0x74, 0x1}, {0xc5, 0x1}, {0x116, 0x1}, {0x24, 0x0}, {0x75, 0x0},
	{0xc6, 0x0}, {0x117, 0x0}, {0x25, 0x1}, {0x76, 0x1}, {0xc7, 0x1},
	{0x118, 0x1}, {0x26, 0x2}, {0x77, 0x2}, {0xc8, 0x2}, {0x119, 0x2},
	{0x27, 0x0}, {0x78, 0x0}, {0xc9, 0x0}, {0x11a, 0x0}, {0x28, 0x1},
	{0x79, 0x1}, {0xca, 0x1}, {0x11b, 0x1}, {0x29, 0x0}, {0x7a, 0x0},
	{0xcb, 0x0}, {0x11c, 0x0}, {0x2a, 0x0}, {0x7b, 0x0}, {0xcc, 0x0},
	{0x11d, 0x0}, {0x34, 0x2}, {0x85, 0x2}, {0xd6, 0x2}, {0x127, 0x2},
	{0x2c, 0x0}, {0x7d, 0x0}, {0xce, 0x0}, {0x11f, 0x0}, {0x2d, 0x0},
	{0x7e, 0x0}, {0xcf, 0x0}, {0x120, 0x0}, {0x2e, 0x0}, {0x7f, 0x0},
	{0xd0, 0x0}, {0x121, 0x0}, {0x2f, 0x2}, {0x80, 0x2}, {0xd1, 0x2},
	{0x122, 0x2}, {0x30, 0x2}, {0x81, 0x2}, {0xd2, 0x2}, {0x123, 0x2},
	{0x31, 0x0}, {0x82, 0x0}, {0xd3, 0x0}, {0x124, 0x0}, {0x32, 0x0},
	{0x83, 0x0}, {0xd4, 0x0}, {0x125, 0x0}, {0x33, 0x0}, {0x84, 0x0},
	{0xd5, 0x0}, {0x126, 0x0}, {0x3d, 0x0}, {0x8e, 0x0}, {0xdf, 0x0},
	{0x130, 0x0}, {0x35, 0x2}, {0x86, 0x2}, {0xd7, 0x2}, {0x128, 0x2},
	{0x36, 0x0}, {0x87, 0x0}, {0xd8, 0x0}, {0x129, 0x0}, {0x37, 0x0},
	{0x88, 0x0}, {0xd9, 0x0}, {0x12a, 0x0}, {0x38, 0x0}, {0x89, 0x0},
	{0xda, 0x0}, {0x12b, 0x0}, {0x39, 0x1}, {0x8a, 0x1}, {0xdb, 0x1},
	{0x12c, 0x1}, {0x3a, 0x2}, {0x8b, 0x2}, {0xdc, 0x2}, {0x12d, 0x2},
	{0x3b, 0x0}, {0x8c, 0x0}, {0xdd, 0x0}, {0x12e, 0x0}, {0x3c, 0x1},
	{0x8d, 0x1}, {0xde, 0x1}, {0x12f, 0x1}, {0x46, 0x1}, {0x97, 0x1},
	{0xe8, 0x1}, {0x139, 0x1}, {0x3e, 0x0}, {0x8f, 0x0}, {0xe0, 0x0},
	{0x131, 0x0}, {0x3f, 0x1}, {0x90, 0x1}, {0xe1, 0x1}, {0x132, 0x1},
	{0x40, 0x1}, {0x91, 0x1}, {0xe2, 0x1}, {0x133, 0x1}, {0x41, 0x0},
	{0x92, 0x0}, {0xe3, 0x0}, {0x134, 0x0}, {0x42, 0x1}, {0x93, 0x1},
	{0xe4, 0x1}, {0x135, 0x1}, {0x43, 0x0}, {0x94, 0x0}, {0xe5, 0x0},
	{0x136, 0x0}, {0x44, 0x1}, {0x95, 0x1}, {0xe6, 0x1}, {0x137, 0x1},
	{0x45, 0x0}, {0x96, 0x0}, {0xe7, 0x0}, {0x138, 0x0}, {0x4f, 0x1},
	{0xa0, 0x1}, {0xf1, 0x1}, {0x142, 0x1}, {0x47, 0x1}, {0x98, 0x1},
	{0xe9, 0x1}, {0x13a, 0x1}, {0x48, 0x1}, {0x99, 0x1}, {0xea, 0x1},
	{0x13b, 0x1}, {0x49, 0x1}, {0x9a, 0x1}, {0xeb, 0x1}, {0x13c, 0x1},
	{0x4a, 0x1}, {0x9b, 0x1}, {0xec, 0x1}, {0x13d, 0x1}, {0x4b, 0x2},
	{0x9c, 0x2}, {0xed, 0x2}, {0x13e, 0x2}, {0x4c, 0x1}, {0x9d, 0x1},
	{0xee, 0x1}, {0x13f, 0x1}, {0x4d, 0x1}, {0x9e, 0x1}, {0xef, 0x1},
	{0x140, 0x1}, {0x4e, 0x1}, {0x9f, 0x1}, {0xf0, 0x1}, {0x141, 0x1},
	{0x58, 0x0}, {0xa9, 0x0}, {0xfa, 0x0}, {0x14b, 0x0}, {0x50, 0x0},
	{0xa1, 0x0}, {0xf2, 0x0}, {0x143, 0x0}, {0x51, 0x1}, {0xa2, 0x1},
	{0xf3, 0x1}, {0x144, 0x1}, {0x52, 0x1}, {0xa3, 0x1}, {0xf4, 0x1},
	{0x145, 0x1}, {0x53, 0x0}, {0xa4, 0x0}, {0xf5, 0x0}, {0x146, 0x0},
	{0x54, 0x1}, {0xa5, 0x1}, {0xf6, 0x1}, {0x147, 0x1}, {0x55, 0x0},
	{0xa6, 0x0}, {0xf7, 0x0}, {0x148, 0x0}, {0x56, 0x1}, {0xa7, 0x1},
	{0xf8, 0x1}, {0x149, 0x1}, {0x57, 0x1}, {0xa8, 0x1}, {0xf9, 0x1},
	{0x14a, 0x1}, {0x61, 0x0}, {0xb2, 0x0}, {0x103, 0x0}, {0x154, 0x0},
	{0x59, 0x1}, {0xaa, 0x1}, {0xfb, 0x1}, {0x14c, 0x1}, {0x5a, 0x1},
	{0xab, 0x1}, {0xfc, 0x1}, {0x14d, 0x1}, {0x5b, 0x0}, {0xac, 0x0},
	{0xfd, 0x0}, {0x14e, 0x0}, {0x5c, 0x1}, {0xad, 0x1}, {0xfe, 0x1},
	{0x14f, 0x1}, {0x5d, 0x0}, {0xae, 0x0}, {0xff, 0x0}, {0x150, 0x0},
	{0x5e, 0x0}, {0xaf, 0x0}, {0x100, 0x0}, {0x151, 0x0}, {0x5f, 0x0},
	{0xb0, 0x0}, {0x101, 0x0}, {0x152, 0x0}, {0x60, 0x2}, {0xb1, 0x2},
	{0x102, 0x2}, {0x153, 0x2}, {0x6a, 0x1}, {0xbb, 0x1}, {0x10c, 0x1},
	{0x15d, 0x1}, {0x62, 0x2}, {0xb3, 0x2}, {0x104, 0x2}, {0x155, 0x2},
	{0x63, 0x1}, {0xb4, 0x1}, {0x105, 0x1}, {0x156, 0x1}, {0x64, 0x2},
	{0xb5, 0x2}, {0x106, 0x2}, {0x157, 0x2}, {0x65, 0x0}, {0xb6, 0x0},
	{0x107, 0x0}, {0x158, 0x0}, {0x66, 0x0}, {0xb7, 0x0}, {0x108, 0x0},
	{0x159, 0x0}, {0x67, 0x0}, {0xb8, 0x0}, {0x109, 0x0}, {0x15a, 0x0},
	{0x68, 0x0}, {0xb9, 0x0}, {0x10a, 0x0}, {0x15b, 0x0}, {0x69, 0x0},
	{0xba, 0x0}, {0x10b, 0x0}, {0x15c, 0x0}, {0x73, 0x0}, {0xc4, 0x0},
	{0x115, 0x0}, {0x166, 0x0}, {0x6b, 0x1}, {0xbc, 0x1}, {0x10d, 0x1},
	{0x15e, 0x1}, {0x6c, 0x1}, {0xbd, 0x1}, {0x10e, 0x1}, {0x15f, 0x1},
	{0x6d, 0x0}, {0xbe, 0x0}, {0x10f, 0x0}, {0x160, 0x0}, {0x6e, 0x1},
	{0xbf, 0x1}, {0x110, 0x1}, {0x161, 0x1}, {0x6f, 0x1}, {0xc0, 0x1},
	{0x111, 0x1}, {0x162, 0x1}, {0x70, 0x1}, {0xc1, 0x1}, {0x112, 0x1},
	{0x163, 0x1}, {0x71, 0x0}, {0xc2, 0x0}, {0x113, 0x0}, {0x164, 0x0},
	{0x72, 0x1}, {0xc3, 0x1}, {0x114, 0x1},	{0x165, 0x1}
};

#if defined(ACP_X1V1) || defined(CONFIG_AXXIA_344X)

delay_table_t delay_table_sm1[] = {
	{0xf, 0x6}, {0x1a, 0x3}, {0x18, 0x4}, {0x5, 0x6}, {0x16, 0x4},
	{0x19, 0x3}, {0x8, 0x5}, {0x21, 0x3}, {0x1d, 0x4}, {0xd, 0x5},
	{0x1, 0x3}, {0x1f, 0x3}, {0x14, 0x6}, {0x1b, 0x5}, {0x9, 0x3},
	{0x4, 0x6}, {0xa, 0x3}, {0xc, 0x3}, {0xe, 0x4}, {0x22, 0x5},
	{0x3, 0x5}, {0x20, 0x7}, {0x17, 0x5}, {0x6, 0x7}, {0x10, 0x4},
	{0x0, 0x3}, {0x13, 0x4}, {0xb, 0x4}, {0x1c, 0x5}, {0x7, 0x4},
	{0x11, 0x4}, {0x12, 0x6}, {0x1e, 0x5}, {0x15, 0x5}, {0x2, 0x3},
	{0x2b, 0x2}, {0x7c, 0x2}, {0xcd, 0x2}, {0x11e, 0x2}, {0x23, 0x0},
	{0x74, 0x0}, {0xc5, 0x0}, {0x116, 0x0}, {0x24, 0x1}, {0x75, 0x1},
	{0xc6, 0x1}, {0x117, 0x1}, {0x25, 0x1}, {0x76, 0x1}, {0xc7, 0x1},
	{0x118, 0x1}, {0x26, 0x0}, {0x77, 0x0}, {0xc8, 0x0}, {0x119, 0x0},
	{0x27, 0x0}, {0x78, 0x0}, {0xc9, 0x0}, {0x11a, 0x0}, {0x28, 0x0},
	{0x79, 0x0}, {0xca, 0x0}, {0x11b, 0x0}, {0x29, 0x0}, {0x7a, 0x0},
	{0xcb, 0x0}, {0x11c, 0x0}, {0x2a, 0x1}, {0x7b, 0x1}, {0xcc, 0x1},
	{0x11d, 0x1}, {0x34, 0x1}, {0x85, 0x1}, {0xd6, 0x1}, {0x127, 0x1},
	{0x2c, 0x1}, {0x7d, 0x1}, {0xce, 0x1}, {0x11f, 0x1}, {0x2d, 0x1},
	{0x7e, 0x1}, {0xcf, 0x1}, {0x120, 0x1}, {0x2e, 0x1}, {0x7f, 0x1},
	{0xd0, 0x1}, {0x121, 0x1}, {0x2f, 0x1}, {0x80, 0x1}, {0xd1, 0x1},
	{0x122, 0x1}, {0x30, 0x1}, {0x81, 0x1}, {0xd2, 0x1}, {0x123, 0x1},
	{0x31, 0x1}, {0x82, 0x1}, {0xd3, 0x1}, {0x124, 0x1}, {0x32, 0x2},
	{0x83, 0x2}, {0xd4, 0x2}, {0x125, 0x2}, {0x33, 0x1}, {0x84, 0x1},
	{0xd5, 0x1}, {0x126, 0x1}, {0x3d, 0x1}, {0x8e, 0x1}, {0xdf, 0x1},
	{0x130, 0x1}, {0x35, 0x1}, {0x86, 0x1}, {0xd7, 0x1}, {0x128, 0x1},
	{0x36, 0x0}, {0x87, 0x0}, {0xd8, 0x0}, {0x129, 0x0}, {0x37, 0x0},
	{0x88, 0x0}, {0xd9, 0x0}, {0x12a, 0x0}, {0x38, 0x0}, {0x89, 0x0},
	{0xda, 0x0}, {0x12b, 0x0}, {0x39, 0x0}, {0x8a, 0x0}, {0xdb, 0x0},
	{0x12c, 0x0}, {0x3a, 0x0}, {0x8b, 0x0}, {0xdc, 0x0}, {0x12d, 0x0},
	{0x3b, 0x0}, {0x8c, 0x0}, {0xdd, 0x0}, {0x12e, 0x0}, {0x3c, 0x0},
	{0x8d, 0x0}, {0xde, 0x0}, {0x12f, 0x0}, {0x46, 0x1}, {0x97, 0x1},
	{0xe8, 0x1}, {0x139, 0x1}, {0x3e, 0x0}, {0x8f, 0x0}, {0xe0, 0x0},
	{0x131, 0x0}, {0x3f, 0x1}, {0x90, 0x1}, {0xe1, 0x1}, {0x132, 0x1},
	{0x40, 0x1}, {0x91, 0x1}, {0xe2, 0x1}, {0x133, 0x1}, {0x41, 0x0},
	{0x92, 0x0}, {0xe3, 0x0}, {0x134, 0x0}, {0x42, 0x1}, {0x93, 0x1},
	{0xe4, 0x1}, {0x135, 0x1}, {0x43, 0x1}, {0x94, 0x1}, {0xe5, 0x1},
	{0x136, 0x1}, {0x44, 0x1}, {0x95, 0x1}, {0xe6, 0x1}, {0x137, 0x1},
	{0x45, 0x1}, {0x96, 0x1}, {0xe7, 0x1}, {0x138, 0x1}, {0x4f, 0x1},
	{0xa0, 0x1}, {0xf1, 0x1}, {0x142, 0x1}, {0x47, 0x0}, {0x98, 0x0},
	{0xe9, 0x0}, {0x13a, 0x0}, {0x48, 0x1}, {0x99, 0x1}, {0xea, 0x1},
	{0x13b, 0x1}, {0x49, 0x1}, {0x9a, 0x1}, {0xeb, 0x1}, {0x13c, 0x1},
	{0x4a, 0x1}, {0x9b, 0x1}, {0xec, 0x1}, {0x13d, 0x1}, {0x4b, 0x0},
	{0x9c, 0x0}, {0xed, 0x0}, {0x13e, 0x0}, {0x4c, 0x1}, {0x9d, 0x1},
	{0xee, 0x1}, {0x13f, 0x1}, {0x4d, 0x1}, {0x9e, 0x1}, {0xef, 0x1},
	{0x140, 0x1}, {0x4e, 0x0}, {0x9f, 0x0}, {0xf0, 0x0}, {0x141, 0x0},
	{0x58, 0x1}, {0xa9, 0x1}, {0xfa, 0x1}, {0x14b, 0x1}, {0x50, 0x0},
	{0xa1, 0x0}, {0xf2, 0x0}, {0x143, 0x0}, {0x51, 0x0}, {0xa2, 0x0},
	{0xf3, 0x0}, {0x144, 0x0}, {0x52, 0x0}, {0xa3, 0x0}, {0xf4, 0x0},
	{0x145, 0x0}, {0x53, 0x0}, {0xa4, 0x0}, {0xf5, 0x0}, {0x146, 0x0},
	{0x54, 0x0}, {0xa5, 0x0}, {0xf6, 0x0}, {0x147, 0x0}, {0x55, 0x0},
	{0xa6, 0x0}, {0xf7, 0x0}, {0x148, 0x0}, {0x56, 0x2}, {0xa7, 0x2},
	{0xf8, 0x2}, {0x149, 0x2}, {0x57, 0x0}, {0xa8, 0x0}, {0xf9, 0x0},
	{0x14a, 0x0}, {0x61, 0x1}, {0xb2, 0x1}, {0x103, 0x1}, {0x154, 0x1},
	{0x59, 0x0}, {0xaa, 0x0}, {0xfb, 0x0}, {0x14c, 0x0}, {0x5a, 0x0},
	{0xab, 0x0}, {0xfc, 0x0}, {0x14d, 0x0}, {0x5b, 0x0}, {0xac, 0x0},
	{0xfd, 0x0}, {0x14e, 0x0}, {0x5c, 0x1}, {0xad, 0x1}, {0xfe, 0x1},
	{0x14f, 0x1}, {0x5d, 0x0}, {0xae, 0x0}, {0xff, 0x0}, {0x150, 0x0},
	{0x5e, 0x0}, {0xaf, 0x0}, {0x100, 0x0}, {0x151, 0x0}, {0x5f, 0x1},
	{0xb0, 0x1}, {0x101, 0x1}, {0x152, 0x1}, {0x60, 0x0}, {0xb1, 0x0},
	{0x102, 0x0}, {0x153, 0x0}, {0x6a, 0x1}, {0xbb, 0x1}, {0x10c, 0x1},
	{0x15d, 0x1}, {0x62, 0x0}, {0xb3, 0x0}, {0x104, 0x0}, {0x155, 0x0},
	{0x63, 0x1}, {0xb4, 0x1}, {0x105, 0x1}, {0x156, 0x1}, {0x64, 0x0},
	{0xb5, 0x0}, {0x106, 0x0}, {0x157, 0x0}, {0x65, 0x1}, {0xb6, 0x1},
	{0x107, 0x1}, {0x158, 0x1}, {0x66, 0x1}, {0xb7, 0x1}, {0x108, 0x1},
	{0x159, 0x1}, {0x67, 0x1}, {0xb8, 0x1}, {0x109, 0x1}, {0x15a, 0x1},
	{0x68, 0x0}, {0xb9, 0x0}, {0x10a, 0x0}, {0x15b, 0x0}, {0x69, 0x0},
	{0xba, 0x0}, {0x10b, 0x0}, {0x15c, 0x0}, {0x73, 0x1}, {0xc4, 0x1},
	{0x115, 0x1}, {0x166, 0x1}, {0x6b, 0x2}, {0xbc, 0x2}, {0x10d, 0x2},
	{0x15e, 0x2}, {0x6c, 0x1}, {0xbd, 0x1}, {0x10e, 0x1}, {0x15f, 0x1},
	{0x6d, 0x0}, {0xbe, 0x0}, {0x10f, 0x0}, {0x160, 0x0}, {0x6e, 0x0},
	{0xbf, 0x0}, {0x110, 0x0}, {0x161, 0x0}, {0x6f, 0x2}, {0xc0, 0x2},
	{0x111, 0x2}, {0x162, 0x2}, {0x70, 0x1}, {0xc1, 0x1}, {0x112, 0x1},
	{0x163, 0x1}, {0x71, 0x2}, {0xc2, 0x2}, {0x113, 0x2}, {0x164, 0x2},
	{0x72, 0x2}, {0xc3, 0x2}, {0x114, 0x2}, {0x165, 0x2}
};

#endif /* ACP_X1V1 || CONFIG_AXXIA_344X */

#endif

static unsigned long rank_address_map [ 2 ] [ 2 ] = {
    { 0x300, 0x100 },
    { 0x400, 0x600 }
};

/*
  ------------------------------------------------------------------------------
  debug_dump
*/

static void
debug_dump(unsigned long smNode, unsigned long mstrctlerrs)
{
#ifdef SM_DEBUG_MODE
	unsigned long node;
	unsigned long offset;
	unsigned long value;
	unsigned long *pOff;

	unsigned long rdcal_regs[] = {0x1bff8,          /* RDCALCTLSTA */
				      0x1bf94, 0x1bfd4, /* RDCALBYTEERRDQS */
				      0x1bfb0, 0x1bff0, /* RDCALPREMB */
				      0x1bfa0, 0x1bfe0, /* RDCALDATERR */
				      0};


	printf("\n\n\tmstrctlerrs=0x%08x\n", mstrctlerrs);


	if (mstrctlerrs & 0x10) {
		/* read cal status/error registers */
		pOff =  &rdcal_regs[0];
		while (*pOff) {
			ncr_read32(NCP_REGION_ID(smNode, 1), *pOff, &value);
			printf("0x%03x.1.0x%04x = 0x%08x\n",
			       smNode, *pOff, value);
			pOff++;
		}

		for (offset = 0x1800c;offset <= 0x1840c;offset += 0x80) {
			ncr_read32(NCP_REGION_ID(smNode, 1), offset, &value);
			printf("0x%03x.1.0x%04x = 0x%08x\n",
			       smNode, offset, value);
		}
	}



	if (mstrctlerrs & 0x08) {
		/* write leveling errors */
		for (offset = 0x8034;offset <= 0x8434;offset += 0x80) {
			ncr_read32(NCP_REGION_ID(smNode, 1), offset, &value);
			printf("0x%03x.1.0x%04x = 0x%08x\n",
			       smNode, offset, value);
			ncr_read32(NCP_REGION_ID(smNode, 1), (offset + 4),
				   &value);
			printf("0x%03x.1.0x%04x = 0x%08x\n",
			       smNode, (offset + 4), value);
		}
	}

#endif
}

/*
  ------------------------------------------------------------------------------
  delay_dump
*/

static void
delay_dump(unsigned long line, unsigned long smNode)
{
#ifdef SM_DEBUG_MODE
	unsigned long offset;
	unsigned long value;

	printf("\n\n\tLine %d: Delay Values for Node 0x%03x\n", line, smNode);

	for (offset = 0x8000;offset <= 0x800c;offset += 4) {
		ncr_read32(NCP_REGION_ID(smNode, 1), offset, &value);
		printf("0x%03x.1.0x%04x = 0x%08x\n", smNode, offset, value);
		ncr_read32(NCP_REGION_ID(smNode, 1), (offset + 0x280), &value);
		printf("0x%03x.1.0x%04x = 0x%08x\n",
		       smNode, (offset + 0x280), value);
	}

	for (offset = 0x8040;offset <= 0x804c;
	     offset += 4) {
		ncr_read32(NCP_REGION_ID(smNode, 1), offset, &value);
		printf("0x%03x.1.0x%04x = 0x%08x\n", smNode, offset, value);
		ncr_read32(NCP_REGION_ID(smNode, 1), (offset + 0x280), &value);
		printf("0x%03x.1.0x%04x = 0x%08x\n",
		       smNode, (offset + 0x280), value);
	}
#endif
}

/*
  ------------------------------------------------------------------------------
  sm_bytelane_test
*/

static int
sm_bytelane_test(void * foo, unsigned long address, int pattern, unsigned long *bad_bl_bad,
		 unsigned long *bad_bl_early, unsigned long *bad_bl_late,
		 unsigned long num_bls)
{
	int i;
	int j;
	unsigned char *cdar = (unsigned char *)(NCA + 0x1060);
	unsigned long *cdar32 = (unsigned long *)(NCA + 0x1000);
	unsigned char value;
	unsigned long value32 = 0x01010101UL;
	unsigned long offset = num_bls * 2;

	/* The RTE writes the opposite pattern first... */

	/* Write. */
	for (i = 0;i < (128 / num_bls);++i) {
		unsigned long temp;

		if (0 == pattern)
			temp = value32;
		else
			temp = ~value32;

		*cdar32++ = temp;

		NCR_TRACE("ncpWrite  -w8 0.512.1.0x00%08lx " \
			  "0x%02x 0x%02x 0x%02x 0x%02x\n",
			  (address + (num_bls * i)),
			  (unsigned char )((temp & 0xff000000) >> 24),
			  (unsigned char )((temp & 0x00ff0000) >> 16),
			  (unsigned char )((temp & 0x0000ff00) >>  8),
			  (unsigned char )(temp & 0x000000ff));

		if (num_bls == 8) {
			*cdar32++ = temp;
			NCR_TRACE("ncpWrite  -w8 0.512.1.0x00%08lx " \
				  "0x%02x 0x%02x 0x%02x 0x%02x\n",
				  (address + 4 + (8 * i)),
				  (unsigned char )((temp & 0xff000000) >> 24),
				  (unsigned char )((temp & 0x00ff0000) >> 16),
				  (unsigned char )((temp & 0x0000ff00) >>  8),
				  (unsigned char )(temp & 0x000000ff));
		}

		if (0x80808080UL > value32)
			value32 = value32 << 1;
		else
			value32 = 0x01010101UL;

	}

#ifdef SM_BYTELANE_TEST_DEBUG
	{
		int index;

		for (index = 0;index < (128 / 4);++index) {
			printf("<%03d:0x%08lx>", (index * 4),
			       *((unsigned long *)(NCA + 0x1000 + (index * 4))));
		}

		printf("\n");
	}
#endif

	ncr_write( NCP_REGION_ID( 512, 1 ), address, 128, NULL );

	if (0 != (pattern & 0x2))
		return 0;

	/* Read back and compare. */
	ncr_read( NCP_REGION_ID( 512, 1 ), address, 128, NULL );
	NCR_TRACE("ncpRead   -w8 0.512.1.0x00%08lx 128\n", address);

#ifdef SM_BYTELANE_TEST_DEBUG
	{
		int index;

		for (index = 0;index < (128 / 4);++index) {
			printf("(%03d:0x%08lx)", (index * 4),
			       *((unsigned long *)(NCA + 0x1000 + (index * 4))));
		}

		printf("\n");
	}
#endif
	*bad_bl_bad = 0;
	*bad_bl_early = 0;
	*bad_bl_late = 0;
	j = 0;

	for (i = 0;i < num_bls;++i) {
		value = (8 == num_bls) ? 0x10 : 0x01;

		if (0 != pattern)
			value = ~value;

#ifdef SM_BYTELANE_TEST_DEBUG
		printf("i=%d j=%d value=0x%02x "
		       "cdar=0x%08x/0x%02x/0x%02x/0x%02x\n",
		       i, j, value, cdar, *cdar, *(cdar - offset),
		       *(cdar + offset));
#endif

		if (value != *cdar) {
			if (*(cdar - offset) == value)
				*bad_bl_early |= 1 << i;
			else if (*(cdar + offset) == value)
				*bad_bl_late |= 1 << i;
			else
				*bad_bl_bad |= 1 << i;
		}

		++cdar;
		++j;
	}

#ifdef SM_BYTELANE_TEST_DEBUG
	printf("*bad_bl_bad=0x%x *bad_bl_early=0x%x *bad_bl_late=0x%x\n",
	       *bad_bl_bad, *bad_bl_early, *bad_bl_late);
#endif

	return 0;
}

/*
  ------------------------------------------------------------------------------
  sm_ecc_bytelane_test
*/

static int
sm_ecc_bytelane_test(void *foo, unsigned long region, unsigned long address,
		     unsigned long node, int pattern, unsigned long ecc_mask,
		     unsigned long *bad_bl)
{
	unsigned long value;
	unsigned long temp;
	int i;
	int rc;

	/* clear ECC interrupt status bits */
	ncr_read32( region, NCP_DENALI_CTL_91, & value );
#ifdef SM_ECC_BYTELANE_TEST_DEBUG
	printf( "region=0x%08lx value=0x%08lx\n", region, value );
#endif /* SM_ECC_BYTELANE_TEST_DEBUG */
	value &= ecc_mask;
	ncr_write32( region, NCP_DENALI_CTL_89, value );

	/* Write. */
	value = 0x01010101;

	for (i = 0;i < 128 ;i += 8) {
		unsigned long this_value;

		if (0 == pattern)
			this_value = value;
		else
			this_value = ~value;

		*((unsigned long *)(NCA + 0x1000 + i)) = this_value;
		*((unsigned long *)(NCA + 0x1004 + i)) = this_value;
		NCR_TRACE("ncpWrite  -w8 0.512.1.0x00%08lx " \
			  "0x%02x 0x%02x 0x%02x 0x%02x\n",
			  (address + i),
			  (unsigned char )((this_value & 0xff000000) >> 24),
			  (unsigned char )((this_value & 0x00ff0000) >> 16),
			  (unsigned char )((this_value & 0x0000ff00) >>  8),
			  (unsigned char )(this_value & 0x000000ff));
		NCR_TRACE("ncpWrite  -w8 0.512.1.0x00%08lx " \
			  "0x%02x 0x%02x 0x%02x 0x%02x\n",
			  (address + 4 + i),
			  (unsigned char )((this_value & 0xff000000) >> 24),
			  (unsigned char )((this_value & 0x00ff0000) >> 16),
			  (unsigned char )((this_value & 0x0000ff00) >>  8),
			  (unsigned char )(this_value & 0x000000ff));

		if (value < 0x80808080)
			value <<= 1;
		else
			value = 0x01010101;
	}

#ifdef SM_ECC_BYTELANE_TEST_DEBUG
	{
		int index;

		for (index = 0;index < (128 / 4);++index) {
			printf("<%03d:0x%08lx>", (index * 4),
			       *((unsigned long *)(NCA + 0x1000 + (index * 4))));
		}

		printf("\n");
	}
#endif /* SM_ECC_BYTELANE_TEST_DEBUG */

	ncr_write( NCP_REGION_ID( 512, 1 ), address, 128, NULL );

	/*
	  ncr_read() returns the contents of "CFG Ring Command Error
	  Status Register 0" after the operation.

	  The top 6 bits are all that matter;but the layout changed
	  as of X1V2.  See the definition of 0x101.0.0xe4 for details.

	  In X1V1, the RTE returns NCP_ST_DEV_PIO_DECODE_ERR when the
	  "decode_error" bit is set.

	  In X1V2 and later, the RTE returns NCP_ST_DEV_PIO_DECODE_ERR
	  when both the "target_error" and
	  "decode_err_or_node_err_type_bit0" bits are set.

	  In the following, both NCP_ST_SUCCESS, and
	  NCP_ST_DEV_PIO_DECODE_ERR should be acceptable;any other
	  return code is an error.
	*/

#define NCR_ERROR_BIT_MASK 0xfc000000
#ifdef ACP_X1V1
#define NCP_ST_DEV_PIO_DECODE_ERR 0x40000000
#else
#define NCP_ST_DEV_PIO_DECODE_ERR 0x84000000
#endif

	/* Read, Ignoring the Value Read */
	rc = ncr_read( NCP_REGION_ID( node, 5 ), 0, 128/4, NULL );

	if (-1 == rc)
		rc = in_be32(NCA + 0xe4);

	NCR_TRACE( "ncpRead    0.%lu.5.0x0000000000 32\n", node );

#ifdef SM_ECC_BYTELANE_TEST_DEBUG
	{
		int index;

		for (index = 0;index < (128 / 4);++index) {
			printf("(%03d:0x%08lx)", (index * 4),
			       *((unsigned long *)(NCA + 0x1000 + (index * 4))));
		}

		printf("\n");
	}
#endif /* SM_ECC_BYTELANE_TEST_DEBUG */

	if ((0 != rc) &&
	    (NCP_ST_DEV_PIO_DECODE_ERR != (rc & NCR_ERROR_BIT_MASK))) {
		printf("%s:%s:%d - rc=0x%x\n",
		       __FILE__, __FUNCTION__, __LINE__, rc);
		return -1;
	}

	/*
	  If the interrupt status below is 0, the data just read back
	  should be compared to what was written.  Since there isn't a
	  place to store it, compare it now (since the following
	  config ring accesses will overwrite the first few words).
	 */
	{
		value = 0x01010101;
		rc = 0;

		for (i = 0;i < 128 ;i += 8) {
			unsigned long this_value;

			if (0 == pattern)
				this_value = value;
			else
				this_value = ~value;

			temp = *((unsigned long *)(NCA + 0x1000 + i));

			if (temp != this_value) {
				rc = 0x1ff;
			}

			temp = *((unsigned long *)(NCA + 0x1004 + i));

			if (temp != this_value) {
				rc = 0x1ff;
			}

			if (value < 0x80808080)
				value <<= 1;
			else
				value = 0x01010101;
		}
	}

	/* Clear any ACK errors created during initialization. */
	ncr_read32( NCP_REGION_ID( node, 0 ), 0, &temp);
	ncr_write32( NCP_REGION_ID( node, 0 ), 0, temp);

	/* Check the interrupt status. */
	ncr_read32( region, NCP_DENALI_CTL_91, & value );
#ifdef SM_ECC_BYTELANE_TEST_DEBUG
	printf("NCP_DENALI_CTL_91: 0x%lx\n", value);
#endif /* SM_ECC_BYTELANE_TEST_DEBUG */
	value &= ecc_mask;

	if (0 != value) {
		*bad_bl = 0x100;
	} else if (0 != rc) {
		*bad_bl = 0x1ff;
	}

	return 0;
}

/*
  ------------------------------------------------------------------------------
  phy_status_check
*/

static int
phy_status_check(unsigned long smId, unsigned long enableECC)
{
	unsigned long value;
	unsigned long node = sm_nodes[smId];
	unsigned long region = NCP_REGION_ID(node, 1);
	ncp_phy_CFG_SYSMEM_PHY_MSTRCTLERRS_r_t *mstrctlerrs =
		(ncp_phy_CFG_SYSMEM_PHY_MSTRCTLERRS_r_t *)&value;

	ncr_read32(region, NCP_PHY_CFG_SYSMEM_PHY_MSTRCTLERRS, &value);

	if (0 != mstrctlerrs->rd_cal_err) {
#ifdef SM_REG_DUMP
		int i;
		unsigned long offsets[] = {
			NCP_PHY_CFG_SYSMEM_PHY_RDCALCTLSTA,
			NCP_PHY_CFG_SYSMEM_PHY_RDCALBYTEERRDQS_0,
			NCP_PHY_CFG_SYSMEM_PHY_RDCALBYTEERRDQS_1,
			NCP_PHY_CFG_SYSMEM_PHY_RDCALPREMB_0,
			NCP_PHY_CFG_SYSMEM_PHY_RDCALPREMB_1,
			NCP_PHY_CFG_SYSMEM_PHY_RDDLY_ERR_BL0,
			NCP_PHY_CFG_SYSMEM_PHY_RDDLY_ERR_BL1,
			NCP_PHY_CFG_SYSMEM_PHY_RDDLY_ERR_BL2,
			NCP_PHY_CFG_SYSMEM_PHY_RDDLY_ERR_BL3,
			NCP_PHY_CFG_SYSMEM_PHY_RDDLY_ERR_BL4,
			NCP_PHY_CFG_SYSMEM_PHY_RDDLY_ERR_BL5,
			NCP_PHY_CFG_SYSMEM_PHY_RDDLY_ERR_BL6,
			NCP_PHY_CFG_SYSMEM_PHY_RDDLY_ERR_BL7,
			NCP_PHY_CFG_SYSMEM_PHY_RDDLY_ERR_BL8
		};
		unsigned long rdcalbyteerrdqs_0;
		unsigned long rdcalbyteerrdqs_1;

		NCR_TRACE("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
		ncr_read32(region, NCP_PHY_CFG_SYSMEM_PHY_RDCALBYTEERRDQS_0,
			   &rdcalbyteerrdqs_0);
		ncr_read32(region, NCP_PHY_CFG_SYSMEM_PHY_RDCALBYTEERRDQS_1,
			   &rdcalbyteerrdqs_1);

		if ((0 == enableECC) &&
		    (0 == (rdcalbyteerrdqs_0 & ~0x100)) &&
		    (0 == (rdcalbyteerrdqs_0 & ~0x100))) {
			/*
			  If ECC is not enabled, ignore errors on the
			  ECC byte lane.
			*/
			return 0;
		}

		for (i = 0;i < sizeof(offsets)/sizeof(unsigned long);++i) {
			ncr_read32(region, offsets[i], &value);
			printf("0.%lx.1.%010lx: %08lx\n",
			       node, offsets[i], value);
		}

		NCR_TRACE( "%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__ );
#endif
		debug_dump(sm_nodes[smId], *((unsigned long *)&mstrctlerrs));
		return -1;
	} else if (0 != mstrctlerrs->wr_lvl_err  ||
		   0 != mstrctlerrs->rd_dly_err  ||
		   0 != mstrctlerrs->cmd_dly_err ||
		   0 != mstrctlerrs->cpc_err) {
		NCR_TRACE( "%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__ );
		debug_dump(sm_nodes[smId], *((unsigned long *)&mstrctlerrs));
		return -1;
	}

	return 0;
}

/*
  ------------------------------------------------------------------------------
  phy_training_run
*/

static int
phy_training_run( unsigned long smId,
		  unsigned long ctlRegion, unsigned long phyRegion,
		  unsigned long rank, ncp_sm_phy_training_mode_t mode,
		  unsigned long enableECC )
{
	unsigned long mask;
	unsigned long value;
	unsigned long trainLoops;

	/*
	 * Initialize the leveling response registers to zero.
	 * TODO: It's not clear whether the h/w does this for us
	 * or not, but since these registers are defined as read/write
	 * we'll initialize them to zero just in case.
	 */
	ncr_write32( ctlRegion, NCP_DENALI_CTL_58, 0 );
	ncr_write32( ctlRegion, NCP_DENALI_CTL_59, 0 );
	ncr_write32( ctlRegion, NCP_DENALI_CTL_60, 0 );

	/* read-leveling chip_select */
	mask = value = 0;
	SMAV( ncp_denali_DENALI_CTL_20_t, rdlvl_cs, rank );
	ncr_modify32( ctlRegion, NCP_DENALI_CTL_20, mask, value );

	/* write-leveling chip_select and mode */
	mask = value = 0;
	SMAV( ncp_denali_DENALI_CTL_21_t, wrlvl_cs, rank );
	SMAV( ncp_denali_DENALI_CTL_21_t, sw_leveling_mode, mode );
	ncr_modify32( ctlRegion, NCP_DENALI_CTL_21, mask, value );

	/* set the start bit */
	mask = value = 0;
	SMAV( ncp_denali_DENALI_CTL_14_t, swlvl_start, 1);
	ncr_modify32( ctlRegion, NCP_DENALI_CTL_14, mask, value );

	/* poll for the OP_DONE bit */
	{
		ncp_denali_DENALI_CTL_13_t ctl_13_mask = { 0 };
		ncp_denali_DENALI_CTL_13_t ctl_13_value = { 0 };
		ctl_13_mask.swlvl_op_done = 1;
		ctl_13_value.swlvl_op_done = 1;
		mb();
		if (0 != ncr_poll(ctlRegion, NCP_DENALI_CTL_13,
				  *((unsigned long *)&ctl_13_mask),
				  *((unsigned long *)&ctl_13_value),
				  10, 100)) {
			NCR_TRACE("%s:%s:%d\n",
				  __FILE__, __FUNCTION__, __LINE__);
			return -1;
		}
	}

#define NCP_PHY_MAX_TRAIN_LOOPS 100000

	trainLoops = 0;

	while( trainLoops < NCP_PHY_MAX_TRAIN_LOOPS ) {
		ncp_denali_DENALI_CTL_60_t ctl_60;

		/* set the load bit */
		mask = value = 0;
		SMAV( ncp_denali_DENALI_CTL_13_t, swlvl_load, 1 );
		ncr_modify32( ctlRegion, NCP_DENALI_CTL_13, mask, value );

		/* poll for the OP_DONE bit */
		{
			ncp_denali_DENALI_CTL_13_t ctl_13_mask = { 0 };
			ncp_denali_DENALI_CTL_13_t ctl_13_value = { 0 };
			ctl_13_mask.swlvl_op_done = 1;
			ctl_13_value.swlvl_op_done = 1;
			mb();
			if (0 != ncr_poll(ctlRegion, NCP_DENALI_CTL_13,
					  *((unsigned long *)&ctl_13_mask),
					  *((unsigned long *)&ctl_13_value),
					  10, 100)) {
				NCR_TRACE("%s:%s:%d\n",
					  __FILE__, __FUNCTION__, __LINE__);
				return -2;
			}
		}

		/*
		 * read the leveling response registers
		 * we'll check the values after completing the training
		 * operation.
		 */
		ncr_read32( ctlRegion, NCP_DENALI_CTL_58, & mask );
		ncr_read32( ctlRegion, NCP_DENALI_CTL_59, & value );
		ncr_read32( ctlRegion, NCP_DENALI_CTL_60,
			    ( unsigned long * ) & ctl_60 );

		/*
		 * Now check the leveling response registers.
		 * if the training operation completed succesfully then at least
		 * one of these ought to be non-zero. If they're all zero then
		 * the training operation must have timed out so we return an
		 * error.
		 */
		if( ( mask | value | ctl_60.swlvl_resp_8 ) != 0 ) {
			break;
		}

		++ trainLoops;
	}

	if( NCP_PHY_MAX_TRAIN_LOOPS <= trainLoops ) {
		return -3;
	}

	/* set the exit bit */
	mask = value = 0;
	SMAV( ncp_denali_DENALI_CTL_13_t, swlvl_exit, 1);
	ncr_modify32( ctlRegion, NCP_DENALI_CTL_13, 0x100, 0x10100 );

	/* poll for the OP_DONE bit */
	{
		ncp_denali_DENALI_CTL_13_t ctl_13_mask = { 0 };
		ncp_denali_DENALI_CTL_13_t ctl_13_value = { 0 };
		ctl_13_mask.swlvl_op_done = 1;
		ctl_13_value.swlvl_op_done = 1;
		mb();
		if (0 != ncr_poll(ctlRegion, NCP_DENALI_CTL_13,
				  *((unsigned long *)&ctl_13_mask),
				  *((unsigned long *)&ctl_13_value),
				  10, 100)) {
			NCR_TRACE("%s:%s:%d\n",
				  __FILE__, __FUNCTION__, __LINE__);
			return -4;
		}
	}

	if( 0 != phy_status_check( smId, enableECC ) ) {
		NCR_TRACE( "%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__ );
		return -5;
	}

	return 0;
}

/*
  ------------------------------------------------------------------------------
  phy_coarse_write_leveling
*/

static int
phy_coarse_write_leveling( unsigned long smId,
			   unsigned long rank, unsigned long address,
			   unsigned long enableECC,
			   unsigned long num_bls)
{
	unsigned long bad_bl[3];
	int i;
	ncp_phy_CFG_SYSMEM_PHY_DFICNTLWLDQS0GRP_r_t wl_dqs0 = { 0 };
	ncp_phy_CFG_SYSMEM_PHY_DFICNTLWLDQS1GRP_r_t wl_dqs1 = { 0 };
	ncp_phy_CFG_SYSMEM_PHY_DFICNTLWLCNTL_r_t wl_cntl = { 0 };
	ncp_phy_CFG_SYSMEM_PHY_DFICNTLWLCNTL_r_t wl_cntlMask = { 0 };
	unsigned long ctlRegion = NCP_REGION_ID( sm_nodes [ smId ], 0 );
	unsigned long phyRegion = NCP_REGION_ID( sm_nodes [ smId ], 1 );
	unsigned long mask;
	unsigned long value;
	unsigned long ecc_mask;

	NCR_TRACE("# sysmem phy coarse write leveling\n");

	sm_bytelane_test(NULL, address, 3, &bad_bl[0], &bad_bl[1], &bad_bl[2],
			 num_bls);
	sm_bytelane_test(NULL, address, 0, &bad_bl[0], &bad_bl[1], &bad_bl[2],
			 num_bls);

	if (0 != bad_bl[0]) {
		sm_bytelane_test(NULL, address, 1,
				 &bad_bl[0], &bad_bl[1], &bad_bl[2], num_bls);
		sm_bytelane_test(NULL, address, 0,
				 &bad_bl[0], &bad_bl[1], &bad_bl[2], num_bls);
	}

	if (0 != bad_bl[0]) {
		NCR_TRACE( "%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__ );
		return -1;
	}

	for (i = 1;i < 3;++i) {
		if (0 != bad_bl[i]) {
			/* set the mask with the bad bytelanes */
			wl_dqs0.wldqs0_ena = bad_bl[i];
			wl_dqs1.wldqs1_ena = bad_bl[i];
			ncr_write32(phyRegion,
				    NCP_PHY_CFG_SYSMEM_PHY_DFICNTLWLDQS0GRP,
				    *(unsigned long *)&wl_dqs0);
			ncr_write32(phyRegion,
				    NCP_PHY_CFG_SYSMEM_PHY_DFICNTLWLDQS1GRP,
				    *(unsigned long *)&wl_dqs1);

			/* set the control register */
			wl_cntl.cyc_adj_rank = rank;
			wl_cntl.wrlvl_req = 1;
			wl_cntl.wrlvl_adj = 1;
			wl_cntl.wrlvl_dly_delta = (i == 1) ? 1 : 0;
			ncr_write32(phyRegion,
				    NCP_PHY_CFG_SYSMEM_PHY_DFICNTLWLCNTL,
				    *(unsigned long *)&wl_cntl);
			wl_cntlMask.wrlvl_req = 1;

			if (0 != ncr_poll(phyRegion,
					  NCP_PHY_CFG_SYSMEM_PHY_DFICNTLWLCNTL,
					  *(unsigned long *)&wl_cntlMask,
					  0, 100, 100)) {
				NCR_TRACE("%s:%s:%d\n",
					  __FILE__, __FUNCTION__, __LINE__);
				return -2;
			}
		}
	}

	sm_bytelane_test(NULL, address, 1, &bad_bl[0], &bad_bl[1], &bad_bl[2],
			 num_bls);

	if (0 != bad_bl[0] || 0 != bad_bl[1] || 0 != bad_bl[2]) {
		NCR_TRACE("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
		return -3;
	}

	if (0 != phy_status_check(smId, enableECC)) {
		NCR_TRACE("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
		return -4;
	}

#ifdef PRESET_ECC_LEVELING
	if (0 != enableECC) {
		/* set the mask with the bad bytelanes */
		wl_dqs0.wldqs0_ena = 0x100;
		wl_dqs1.wldqs1_ena = 0x100;
		ncr_write32(phyRegion,
			    NCP_PHY_CFG_SYSMEM_PHY_DFICNTLWLDQS0GRP,
			    *(unsigned long *)&wl_dqs0);
		ncr_write32(phyRegion,
			    NCP_PHY_CFG_SYSMEM_PHY_DFICNTLWLDQS1GRP,
			    *(unsigned long *)&wl_dqs1);

		for (i = 0;i < enableECC;++i) {
			/* set the control register */
			wl_cntl.cyc_adj_rank = rank;
			wl_cntl.wrlvl_req = 1;
			wl_cntl.wrlvl_adj = 1;
			wl_cntl.wrlvl_dly_delta = 1;
			wl_cntlMask.wrlvl_req = 1;
			ncr_write32(phyRegion,
				    NCP_PHY_CFG_SYSMEM_PHY_DFICNTLWLCNTL,
				    *(unsigned long *)&wl_cntl);

			if( 0 !=
			    ncr_poll( phyRegion,
				      NCP_PHY_CFG_SYSMEM_PHY_DFICNTLWLCNTL,
				      * ( unsigned long * ) & wl_cntlMask, 0,
				      100, 100 ) ) {
				NCR_TRACE( "%s:%s:%d\n",
					   __FILE__, __FUNCTION__, __LINE__ );
				return -5;
			}
		}

		/* Enable ECC */
		NCR_TRACE( "# enabling ECC\n" );
		mask = value = 0;
		SMAV( ncp_denali_DENALI_CTL_20_t, ctrl_raw, 3 );
		ncr_modify32( ctlRegion, NCP_DENALI_CTL_20, mask, value );
	}
#else
	if (0 != enableECC) {
		unsigned long ecc_bad_bl;
		unsigned long node;

		NCR_TRACE("# sysmem phy coarse write leveling - ECC bytelane\n");
		node = sc_nodes[((address & 0x700) >> 8)];

		if (0 != ncr_tracer_is_enabled()) {
			ncr_tracer_disable();
			ncr_read32( ctlRegion, NCP_DENALI_CTL_133, & value );
			ncr_tracer_enable();
		}

		if( 2 == ( value >> 24 ) )
			ecc_mask = 0x3c;
		else
			ecc_mask = 0x78;

		/* enable ECC reporting with no correction */
		mask = value = 0;
		SMAV( ncp_denali_DENALI_CTL_20_t, ctrl_raw, 1 );
		ncr_modify32( ctlRegion, NCP_DENALI_CTL_20, mask, value );

		if (0 != ncr_tracer_is_enabled()) {
			ncr_tracer_disable();
			sm_ecc_bytelane_test(NULL, ctlRegion, address, node,
					     1, ecc_mask, &ecc_bad_bl);
			ncr_tracer_enable();
		} else {
			sm_ecc_bytelane_test(NULL, ctlRegion, address, node,
					     1, ecc_mask, &ecc_bad_bl);
		}

		ecc_bad_bl = 0;
		sm_ecc_bytelane_test(NULL, ctlRegion, address, node, 0, ecc_mask,
				     &ecc_bad_bl);

		/*for (i = 0;i < 3;++ i) {*/
		for (i = 0;i < 5;++ i) {
#ifdef SM_ECC_BYTELANE_TEST_DEBUG
			printf( "ecc_bad_bl=0x%x i=%d\n", ecc_bad_bl, i );
#endif /* SM_ECC_BYTELANE_TEST_DEBUG */
			if (0 == ecc_bad_bl) { break;}

			/* set the mask with the bad bytelanes */
			wl_dqs0.wldqs0_ena = ecc_bad_bl;
			wl_dqs1.wldqs1_ena = ecc_bad_bl;
			ncr_write32(phyRegion,
				    NCP_PHY_CFG_SYSMEM_PHY_DFICNTLWLDQS0GRP,
				    *(unsigned long *)&wl_dqs0);
			ncr_write32(phyRegion,
				    NCP_PHY_CFG_SYSMEM_PHY_DFICNTLWLDQS1GRP,
				    *(unsigned long *)&wl_dqs1);

			/* set the control register */
			wl_cntl.cyc_adj_rank = rank;
			wl_cntl.wrlvl_req = 1;
			wl_cntl.wrlvl_adj = 1;
			/*wl_cntl.wrlvl_dly_delta = (i < 1) ? 1 : 0;*/
			wl_cntl.wrlvl_dly_delta = (i < 2) ? 1 : 0;
			wl_cntlMask.wrlvl_req = 1;
#ifdef SM_ECC_BYTELANE_TEST_DEBUG
			printf( "DFICNTLWLCNTL 0x%x wrlvl_dly_delta=%d\n",
				*(unsigned long *)&wl_cntl,
				wl_cntl.wrlvl_dly_delta);
#endif /* SM_ECC_BYTELANE_TEST_DEBUG */
			ncr_write32(phyRegion,
				    NCP_PHY_CFG_SYSMEM_PHY_DFICNTLWLCNTL,
				    *(unsigned long *)&wl_cntl);

			if( 0 !=
			    ncr_poll( phyRegion,
				      NCP_PHY_CFG_SYSMEM_PHY_DFICNTLWLCNTL,
				      * ( unsigned long * ) & wl_cntlMask, 0,
				      100, 100 ) ) {
				NCR_TRACE( "%s:%s:%d\n",
					   __FILE__, __FUNCTION__, __LINE__ );
				return -5;
			}

			ecc_bad_bl = 0;
			sm_ecc_bytelane_test(NULL, ctlRegion, address, node, 1,
					     ecc_mask, &ecc_bad_bl);
			sm_ecc_bytelane_test(NULL, ctlRegion, address, node, 0,
					     ecc_mask, &ecc_bad_bl);
		}

		if (0 != ecc_bad_bl) {
			NCR_TRACE( "%s:%s:%d\n",
				   __FILE__, __FUNCTION__, __LINE__ );
			return -6;
		}

		/* Enable ECC */
		NCR_TRACE( "# enabling ECC\n" );
		mask = value = 0;
		SMAV( ncp_denali_DENALI_CTL_20_t, ctrl_raw, 3 );
		ncr_modify32( ctlRegion, NCP_DENALI_CTL_20, mask, value );
	}
#endif

	if( 0 != phy_status_check( smId, enableECC ) ) {
		NCR_TRACE( "%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__ );
		return -7;
	}

	return 0;
}

/*
  ------------------------------------------------------------------------------
  phy_read_fifo_delay_optimization
*/

static int
phy_read_fifo_delay_optimization( unsigned long smId, unsigned long address,
				  unsigned long num_bls,
				  unsigned long enableECC )
{
	unsigned long ctlRegion = NCP_REGION_ID( sm_nodes [ smId ], 0 );
	unsigned long phyRegion = NCP_REGION_ID( sm_nodes [ smId ], 1 );
	unsigned long scNode = sc_nodes[((address & 0x700) >> 8)];
	unsigned long eccMask;
	ncp_phy_CFG_SYSMEM_PHY_RDCALGLBDLY_r_t glb_dly;
	unsigned long rd_fifo_dly;
	unsigned long bad_bl[3];

	NCR_TRACE( "# sysmem %lu read fifo delay optimization\n", smId );

	if (0 != ncr_tracer_is_enabled()) {
		ncr_tracer_disable();
		ncr_read32(ctlRegion, NCP_DENALI_CTL_133, &eccMask);
		ncr_tracer_enable();
	}

	if (2 == (eccMask >> 24))
		eccMask = 0x3c;
	else
		eccMask = 0x78;

	/* get the current rd_fifo_dly. it ought to be 7 from the
	 * gate_training setup.
	 */
	ncr_read32( phyRegion, NCP_PHY_CFG_SYSMEM_PHY_RDCALGLBDLY,
		    ( ( unsigned long * ) & glb_dly ) );
	rd_fifo_dly = glb_dly.rd_fifo_dly;

	bad_bl[0] = 0;
	sm_ecc_bytelane_test( NULL, ctlRegion, address, scNode, 0, eccMask,
			      &bad_bl[0]);
	bad_bl[0] = 0;
	sm_ecc_bytelane_test( NULL, ctlRegion, address, scNode, 1, eccMask,
			      &bad_bl[0]);

	while (0 == bad_bl[0] && rd_fifo_dly > 2) {
		--rd_fifo_dly;
		glb_dly.rd_fifo_dly = rd_fifo_dly;
		ncr_write32( phyRegion, NCP_PHY_CFG_SYSMEM_PHY_RDCALGLBDLY,
			     * ( ( unsigned long * ) & glb_dly ) );

		bad_bl[0] = 0;
		sm_ecc_bytelane_test( NULL, ctlRegion, address, scNode, 0, eccMask,
				      &bad_bl[0]);
		bad_bl[0] = 0;
		sm_ecc_bytelane_test( NULL, ctlRegion, address, scNode, 1, eccMask,
				      &bad_bl[0]);
	}

	if (0 != bad_bl[0])
		/* Add 2 to the delay if the above ended with a failure, */
		glb_dly.rd_fifo_dly = rd_fifo_dly + 2;
	else
		/* and add one if not. */
		glb_dly.rd_fifo_dly = rd_fifo_dly + 1;

	ncr_write32( phyRegion, NCP_PHY_CFG_SYSMEM_PHY_RDCALGLBDLY,
		     * ( ( unsigned long * ) & glb_dly ) );

	/* run the test one more time - it better work! */
	bad_bl[0] = 0;
	sm_ecc_bytelane_test( NULL, ctlRegion, address, scNode, 0, eccMask,
			      &bad_bl[0]);
	bad_bl[0] = 0;
	sm_ecc_bytelane_test( NULL, ctlRegion, address, scNode, 1, eccMask,
			      &bad_bl[0]);

	if( 0 != bad_bl[0] || 0 != phy_status_check( smId, enableECC ) ) {
		NCR_TRACE( "%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__ );
		return -1;
	}

	return 0;
}

/*
  ------------------------------------------------------------------------------
  phy_runtime_adj
*/

static int
phy_runtime_adj( unsigned long smId, unsigned long topology,
		 unsigned long singleBitMpr, unsigned long enableDeskew,
		 unsigned long enableRdlvl, unsigned long enableAutoCpc,
		 unsigned long enableECC )
{
	unsigned long ctlRegion = NCP_REGION_ID( sm_nodes [ smId ], 0 );
	unsigned long phyRegion = NCP_REGION_ID( sm_nodes [ smId ], 1 );
	unsigned long mask, value;

	/* Set initial training complete */
	mask = value = 0;
	SMAV( ncp_phy_CFG_SYSMEM_PHY_DFICNTLCPCCNTL_r_t,
	      init_train_complt, 1 );
	ncr_modify32( phyRegion, NCP_PHY_CFG_SYSMEM_PHY_DFICNTLCPCCNTL,
		      mask, value );

	mask = value = 0;
	SMAV( ncp_denali_DENALI_CTL_21_t, sw_leveling_mode, 0 );
	ncr_modify32( ctlRegion, NCP_DENALI_CTL_21, mask, value );

	switch( topology ) {
	case 1:
		value = 0x00010000;
		break;
	case 3:
	case 5:
		value = 0x00020000;
		break;
	case 15:
		value = 0x00030000;
		break;
	default:
		NCR_TRACE( "%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__ );
		return -1;
	}

	ncr_write32( ctlRegion, 0x1fc, value );

	mask = value = 0;
	SMAV( ncp_denali_DENALI_CTL_08_t, rdlvl_en, 1 );
	ncr_modify32( ctlRegion, NCP_DENALI_CTL_08, mask, value );

	mask = value = 0;

	if( 0 != enableDeskew && 0 == singleBitMpr ) {
		SMAV( ncp_phy_CFG_SYSMEM_PHY_DFICNTLRDLCNTL_r_t,
		      runtime_dskew_ena, 1 );
	}

	if( 0 != enableRdlvl ) {
		SMAV( ncp_phy_CFG_SYSMEM_PHY_DFICNTLRDLCNTL_r_t,
		      runtime_rdlvl_ena, 1 );
	}

	SMAV( ncp_phy_CFG_SYSMEM_PHY_DFICNTLRDLCNTL_r_t,
	      init_post_dskew_ena, 0 );
	SMAV( ncp_phy_CFG_SYSMEM_PHY_DFICNTLRDLCNTL_r_t,
	      init_pre_dskew_ena, 0 );
	ncr_modify32( phyRegion, NCP_PHY_CFG_SYSMEM_PHY_DFICNTLRDLCNTL,
		      mask, value );

	/* auto-cpc control */
	if( 0 != enableAutoCpc ) {
		mask = value = 0;
		SMAV( ncp_phy_CFG_SYSMEM_PHY_DFICNTLCPCCNTL_r_t,
		      cpc_upd_intv, 3 );
		SMAV( ncp_phy_CFG_SYSMEM_PHY_DFICNTLCPCCNTL_r_t,
		      upd_intv, 3 );
		SMAV( ncp_phy_CFG_SYSMEM_PHY_DFICNTLCPCCNTL_r_t,
		      auto_cpc_upd_ena, 1 );
		ncr_modify32( phyRegion, NCP_PHY_CFG_SYSMEM_PHY_DFICNTLCPCCNTL,
			      mask, value );
	}

	ncr_write32( ctlRegion, 0x114, 0x3fff );

	/* clear ECC interrupt status bits */
	ncr_read32( ctlRegion, NCP_DENALI_CTL_91, & value );
#ifdef ACP_X1V1
	value &= 0x3feff;
#else
	value &= 0x7fdff;
#endif
	ncr_write32( ctlRegion, NCP_DENALI_CTL_89, value );

	if( 0 != phy_status_check( smId, enableECC ) ) {
		NCR_TRACE( "%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__ );
		return -2;
	}

	return 0;
}

/*
  ==============================================================================
  ==============================================================================
  ==============================================================================
  System Memory Initialization
  ==============================================================================
  ==============================================================================
  ==============================================================================
*/

int
ncp_sysmem_init_ibmphy(
        void *   dev,
        int    smId,
        parameters_sysmem_t *sysmem)
{
	unsigned long num_sc_nodes;
	unsigned long controller;
	unsigned long phy;
	unsigned long mask;
	unsigned long value;
	unsigned long ctl_26 = 0;
	unsigned long ctl_32 = 0;
	unsigned long ctl_33 = 0;
	unsigned long ctl_34 = 0;
	unsigned long munge_reg;
	unsigned long num_bls;
    ncp_uint8_t   *tRFC_vals = tRFC_vals_533;

	int i, j;
	int rc;


	if (sysmem->primary_bus_width == 2) {
		num_bls = 4;
	} else {
		num_bls = 8;
	}

	/*
	  Initialize all system memories.  This is ncp_sysmem_init_asic( ).
	*/

		delay_table_t *delay_table;
		int delay_table_size;

		/* Static PHY Setup (ncp_sm_phy_static_init) */
		NCR_TRACE( "# sysmem %d PHY static init\n", smId );
		controller = NCP_REGION_ID( sm_nodes [ smId ], 0 );
		phy = NCP_REGION_ID( sm_nodes [ smId ], 1 );

		/* NCP_PHY_CTL6 */
		mask = value = 0;
		SMAV( ncp_phy_phy_ctl6_r_t, mode_1p2v_adr, 0 );
		SMAV( ncp_phy_phy_ctl6_r_t, mode_1p2v_dat, 0 );
		SMAV( ncp_phy_phy_ctl6_r_t, zcntl_enb_rcv, 1 );
		SMAV( ncp_phy_phy_ctl6_r_t, zcntl_enb_dp,  1 );
		SMAV( ncp_phy_phy_ctl6_r_t, zcntl_enb_adr, 1 );
		SMAV( ncp_phy_phy_ctl6_r_t, cal_enb_rcv,   1 );
		SMAV( ncp_phy_phy_ctl6_r_t, cal_enb_dat,   1 );
		SMAV( ncp_phy_phy_ctl6_r_t, cal_enb_adr,   1 );
		SMAV( ncp_phy_phy_ctl6_r_t, imped_dat,     sysmem->phy_dat_imp );
		SMAV( ncp_phy_phy_ctl6_r_t, imped_rcv,     sysmem->phy_rcv_imp );
		SMAV( ncp_phy_phy_ctl6_r_t, imped_adr,     sysmem->phy_adr_imp );
		ncr_modify32( phy, NCP_PHY_CTL6, mask, value );

		/* NCP_PHY_CTL7 */
		mask = value = 0;
		SMAV( ncp_phy_phy_ctl7_r_t, rd_ptr_init, 4 );
		ncr_modify32( phy, NCP_PHY_CTL7, mask, value );

		/* NCP_PHY_CFG_SYSMEM_PHY_DFICNTLLAT */
		mask = value = 0;
		SMAV( ncp_phy_CFG_SYSMEM_PHY_DFICNTLLAT_r_t, dm_ena, 1 );
		SMAV( ncp_phy_CFG_SYSMEM_PHY_DFICNTLLAT_r_t,
		      wrlat, sysmem->CAS_write_latency );
		SMAV( ncp_phy_CFG_SYSMEM_PHY_DFICNTLLAT_r_t,
		      rdlat, sysmem->CAS_latency );
		ncr_modify32( phy, NCP_PHY_CFG_SYSMEM_PHY_DFICNTLLAT,
			      mask, value );

		/* NCP_PHY_CFG_SYSMEM_PHY_RDCALGLBDLY */
		mask = value = 0;
		SMAV( ncp_phy_CFG_SYSMEM_PHY_RDCALGLBDLY_r_t,
		      max_rank_delay, 0xf );
		SMAV( ncp_phy_CFG_SYSMEM_PHY_RDCALGLBDLY_r_t, rd_fifo_dly, 5);
		SMAV( ncp_phy_CFG_SYSMEM_PHY_RDCALGLBDLY_r_t,
		      dqs_gate_global_offset, sysmem->min_phy_cal_delay);
		ncr_modify32( phy, NCP_PHY_CFG_SYSMEM_PHY_RDCALGLBDLY,
			      mask, value );

		/* NCP_PHY_CFG_SYSMEM_PHY_MSTRCTLCFG0 */
		mask = value = 0;
		SMAV( ncp_phy_CFG_SYSMEM_PHY_MSTRCTLCFG0_r_t,
		      rank_map_mode, 2 );
		SMAV( ncp_phy_CFG_SYSMEM_PHY_MSTRCTLCFG0_r_t,
		      mem_dev_mode, 0xff );
		ncr_modify32( phy, NCP_PHY_CFG_SYSMEM_PHY_MSTRCTLCFG0,
			      mask, value );

		/* NCP_PHY_CFG_SYSMEM_PHY_MSTRCTLCFG1 */
		mask = value = 0;
		if( 2 == sysmem->version ) {
			SMAV( ncp_phy_CFG_SYSMEM_PHY_MSTRCTLCFG1_r_t,
			      rd_n_cyc_gap, 2 );
		} else {
			SMAV( ncp_phy_CFG_SYSMEM_PHY_MSTRCTLCFG1_r_t,
			      rd_n_cyc_gap, 0 );
		}
		SMAV( ncp_phy_CFG_SYSMEM_PHY_MSTRCTLCFG1_r_t,
		      dqs1_coremode, 0 );
		SMAV( ncp_phy_CFG_SYSMEM_PHY_MSTRCTLCFG1_r_t, dqs0_enamode, 0 );
		ncr_modify32( phy, NCP_PHY_CFG_SYSMEM_PHY_MSTRCTLCFG1,
			      mask, value );

		if( 0 != sysmem->single_bit_mpr ) {
			/* disable read calibration deskew */
			mask = value = 0;
			SMAV( ncp_phy_CFG_SYSMEM_PHY_RDCALRDDLYOVR_r_t,
			      deskew_ena, 0 );
			SMAV( ncp_phy_CFG_SYSMEM_PHY_RDCALRDDLYOVR_r_t,
			      dqsdly_step, 1 );
			ncr_modify32( phy,
				      NCP_PHY_CFG_SYSMEM_PHY_RDCALRDDLYOVR,
				      mask, value );

			/*  set the compare even/odd registers */
			for( j = 0;j < 9;++ j ) {
				unsigned long offset;

				offset =
					NCP_PHY_CFG_SYSMEM_PHY_CMPEVEN_0_BL( j );

				ncr_write32( phy, offset,
					     sysmem->rdcal_cmp_even );
				offset += 4;
				ncr_write32( phy, offset,
					     sysmem->rdcal_cmp_odd );
				offset += 4;
				ncr_write32( phy, offset,
					     sysmem->rdcal_cmp_even );
				offset += 4;
				ncr_write32( phy, offset,
					     sysmem->rdcal_cmp_odd );
			}
		} else {
			/* not single-bit MPR, enable deskew for calibration */
			mask = value = 0;
			SMAV( ncp_phy_CFG_SYSMEM_PHY_DFICNTLRDLCNTL_r_t,
			      init_post_dskew_ena, 1);
			SMAV( ncp_phy_CFG_SYSMEM_PHY_DFICNTLRDLCNTL_r_t,
			      init_pre_dskew_ena,  1);
			ncr_modify32( phy,
				      NCP_PHY_CFG_SYSMEM_PHY_DFICNTLRDLCNTL,
				      mask, value );
		}

		if( 0 == sysmem->enableECC ) {
			/* Mask errors from the ECC bytelane. */
			mask = value = 0;

			SMAV( ncp_phy_CFG_SYSMEM_PHY_DFICNTLWLERRMSK_r_t,
			      riseedge_notfound_errmsk, 2);

			ncr_modify32( phy,
				      NCP_PHY_CFG_SYSMEM_PHY_DFICNTLWLERRMSK_BL8,
				      mask, value );
		}

		/* Check for errors. */
		if( 0 != phy_status_check( smId, sysmem->enableECC ) ) {
			printf( "%d: PHY Static Initialization\n", smId );
			acp_failure( __FILE__, __FUNCTION__, __LINE__ );
		}

		/*
		  CPC Initialization (ncp_sm_phy_cpc_cal)
		*/

		NCR_TRACE( "# sysmem %d CPC calibration\n", smId );

		/* NCP_PHY_CFG_SYSMEM_PHY_ADR0_CONFIG */
		mask = value = 0;
		SMAV( ncp_phy_CFG_SYSMEM_PHY_ADRx_CONFIG_r_t, pvt_type, 0);
		ncr_modify32( phy, NCP_PHY_CFG_SYSMEM_PHY_ADR0_CONFIG,
			      mask, value );

		/* NCP_PHY_CFG_SYSMEM_PHY_ADR1_CONFIG */
		mask = value = 0;
		SMAV( ncp_phy_CFG_SYSMEM_PHY_ADRx_CONFIG_r_t, pvt_type, 0);
		ncr_modify32( phy, NCP_PHY_CFG_SYSMEM_PHY_ADR1_CONFIG,
			      mask, value );

		/* NCP_PHY_CFG_SYSMEM_PHY_ADR2_CONFIG */
		mask = value = 0;
		SMAV( ncp_phy_CFG_SYSMEM_PHY_ADRx_CONFIG_r_t, pvt_type, 0);
		ncr_modify32( phy, NCP_PHY_CFG_SYSMEM_PHY_ADR2_CONFIG,
			      mask, value );

		/* NCP_PHY_CFG_SYSMEM_PHY_DFICNTLCPCREQMSK1 */
		mask = value = 0;
		SMAV( ncp_phy_CFG_SYSMEM_PHY_DFICNTLCPCREQMSK1_r_t,
		      adr_blkmsk, 0x0008 );
		ncr_modify32( phy, NCP_PHY_CFG_SYSMEM_PHY_DFICNTLCPCREQMSK1,
			      mask, value );

		/* CFG_SYSMEM_PHY_DFICNTLCPCCNTL */
		/* This starts the algorithm */
		mask = value = 0;
		SMAV( ncp_phy_CFG_SYSMEM_PHY_DFICNTLCPCCNTL_r_t,
		      cpc_upd_intv, 0 );
		SMAV( ncp_phy_CFG_SYSMEM_PHY_DFICNTLCPCCNTL_r_t, upd_intv, 0 );
		SMAV( ncp_phy_CFG_SYSMEM_PHY_DFICNTLCPCCNTL_r_t,
		      cpc_upd_req, 1 );
		ncr_modify32( phy, NCP_PHY_CFG_SYSMEM_PHY_DFICNTLCPCCNTL,
			      mask, value );

		/* poll for completion */
		mask = value = 0;
		SMAV( ncp_phy_CFG_SYSMEM_PHY_DFICNTLCPCCNTL_r_t,
		      cpc_upd_req, 0 );

		if( 0 != ncr_poll( phy, NCP_PHY_CFG_SYSMEM_PHY_DFICNTLCPCCNTL,
				   mask, value, 10000, 100 ) ) {
			printf( "%d: ncr_poll( ) failed.\n", smId );
			acp_failure( __FILE__, __FUNCTION__, __LINE__ );
		}

		/* Check for errors. */
		if( 0 != phy_status_check( smId, sysmem->enableECC ) ) {
			printf( "%d: CPC Calibration.\n", smId );
			acp_failure( __FILE__, __FUNCTION__, __LINE__ );
		}

		/*
		  SDR Timing (ncp_sm_phy_sdr_timing_setup)
		*/

		NCR_TRACE( "# sysmem phy delay register setup "
			   "for X1 533MHz DDR\n" );

		/* Set up the delay registers. */
#ifdef USE_OLD_DELAY_TABLE
		delay_table = delay_table_v1_533;
		delay_table_size = sizeof(delay_table_v1_533) /
			sizeof(delay_table_t);
#else
#if defined(ACP_X1V1) || defined(CONFIG_AXXIA_344X)
		if (0 == smId) {
			delay_table = delay_table_sm0;
			delay_table_size = sizeof(delay_table_sm0) /
				sizeof(delay_table_t);
		} else {
			delay_table = delay_table_sm1;
			delay_table_size = sizeof(delay_table_sm1) /
				sizeof(delay_table_t);
		}
#else
		if (0 != smId)
			acp_failure(__FILE__, __FUNCTION__, __LINE__);

		delay_table = delay_table_sm0;
		delay_table_size = sizeof(delay_table_sm0) /
			sizeof(delay_table_t);
#endif
#endif

		for (j = 0;j < delay_table_size;++j) {
#ifdef USE_OLD_DELAY_TABLE
			if (smId != delay_table->smId) {
				++delay_table;
				continue;
			}

			mask = delay_table->offset;
			value = delay_table->value;
#else
			mask = delay_table_offsets[delay_table->offset];
			value = delay_table_values[delay_table->value];
#endif
			ncr_write32( phy, mask, value );
			++delay_table;
		}

		/* Set the PHY initialization complete bit. */
		mask = value = 0;
		SMAV( ncp_phy_CFG_SYSMEM_PHY_DFICNTLCPCCNTL_r_t,
		      phy_init_complt, 1 );
		ncr_modify32( phy, NCP_PHY_CFG_SYSMEM_PHY_DFICNTLCPCCNTL,
			      mask, value );

		/* Check for errors. */
		if( 0 != phy_status_check( smId, sysmem->enableECC ) ) {
			printf( "%d: PHY Delay Register Setup.\n", smId );
			acp_failure( __FILE__, __FUNCTION__, __LINE__ );
		}

		/*
		  Intialize the Memory Controller (ncp_sm_denali_init)
		*/

		NCR_TRACE( "# sysmem %d denali controller init\n", smId );

		/* include the common RTE/u-boot controller init code */
#define topology sysmem->topology
#define primary_bus_width sysmem->primary_bus_width
#define sdram_device_density sysmem->sdram_device_density
#define sdram_device_width sysmem->sdram_device_width
#define added_rank_switch_delay sysmem->added_rank_switch_delay
#define CAS_latency sysmem->CAS_latency
#define min_ctrl_roundtrip_delay sysmem->min_ctrl_roundtrip_delay
#define phy_rdlat sysmem->phy_rdlat
#define high_temp_dram sysmem->high_temp_dram
#define sdram_rtt_nom sysmem->sdram_rtt_nom
#define sdram_data_drv_imp sysmem->sdram_data_drv_imp
#define sdram_rtt_wr sysmem->sdram_rtt_wr
#define CAS_write_latency sysmem->CAS_write_latency
#define version sysmem->version
#define address_mirroring sysmem->address_mirroring
#include "ncp_sm_denali_init.h"
#undef topology
#undef primary_bus_width
#undef sdram_device_density
#undef sdram_device_width
#undef added_rank_switch_delay
#undef CAS_latency
#undef min_ctrl_roundtrip_delay
#undef phy_rdlat
#undef high_temp_dram
#undef sdram_rtt_nom
#undef sdram_data_drv_imp
#undef sdram_rtt_wr
#undef CAS_write_latency
#undef version

		/*
		  Read Calibration and Fine Write Leveling
		*/

		for( j = 0;j < 4 ;++ j ) {
			if( 0 == ( sysmem->topology & ( 1 << j ) ) ) {
				continue;
			}

			NCR_TRACE( "# Sysmem %d PHY gate training rank %d\n",
				   smId, j );

			/* Read calibration */
			rc = phy_training_run(smId, controller, phy, j,
					      NCP_SYSMEM_PHY_GATE_TRAINING,
					      sysmem->enableECC);
			if( 0 != rc) {
				printf( "%d: Read Calibration Error: %d\n",
					smId, rc);
				acp_failure( __FILE__, __FUNCTION__, __LINE__ );
			}

			NCR_TRACE( "# Sysmem %d PHY write leveling rank %d\n",
				   smId, j );

			/* Fine write leveling */
			rc = phy_training_run(smId, controller, phy, j,
					      NCP_SYSMEM_PHY_WRITE_LEVELING,
					      sysmem->enableECC);

			if (0 != rc) {
				printf( "%d: Fine Write Leveling Error: %d\n",
					smId, rc);
				acp_failure( __FILE__, __FUNCTION__, __LINE__ );
			}

			delay_dump(__LINE__, sm_nodes[i]);
		}

		/*
		  Coarse Write Leveling and Read FIFO Delay Optimization
		*/

		for( j = 0;j < 4;j += 2 ) {
			unsigned long address;

			if( 0 == ( sysmem->topology & ( 1 << j ) ) ) {
				continue;
			}

			address = rank_address_map [ smId ] [ ( j / 2 ) ];

			/* Coarse write leveling */
			rc = phy_coarse_write_leveling( smId, j, address,
							sysmem->enableECC ,
							num_bls);
			if ( 0 != rc) {
				printf( "%d: Coarse Write Leveling Error %d\n",
					smId, rc  );
				acp_failure( __FILE__, __FUNCTION__, __LINE__ );
			}

			/* Read FIFO delay optimization */
			if( 0 !=
			    phy_read_fifo_delay_optimization( smId,
							      address, num_bls,
							      sysmem->enableECC ) ) {
				printf( "%d: Read FIFO Delay Optimization\n",
					smId );
				acp_failure( __FILE__, __FUNCTION__, __LINE__ );
			}
		}

		NCR_TRACE( "# sysmem %d PHY runtime adjustment\n", smId );

		if (0 != phy_runtime_adj(smId, sysmem->topology,
					 sysmem->single_bit_mpr,
					 sysmem->enable_deskew,
					 sysmem->enable_rdlvl,
					 sysmem->enable_auto_cpc,
					 sysmem->enableECC)) {
			printf( "%d: PHY runtime adjustment failure\n", smId );
			acp_failure( __FILE__, __FUNCTION__, __LINE__ );
		}

	return 0;
}
