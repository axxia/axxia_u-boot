/*
 *  Copyright (C) 2016 Intel (john.jacques@intel.com)
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
 */

#ifndef _NCP_MEMORY_CONTROLLER_REG_DEFINES_H_
#define _NCP_MEMORY_CONTROLLER_REG_DEFINES_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __UBOOT__
#include "ncp_sal_types.h"
#endif


    /* NODE 0x8 , TARGET 0x9*/


#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_00                 (0x00000000)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_01                 (0x00000004)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_02                 (0x00000008)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_03                 (0x0000000c)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_04                 (0x00000010)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_05                 (0x00000014)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_06                 (0x00000018)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_07                 (0x0000001c)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_08                 (0x00000020)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_09                 (0x00000024)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_10                 (0x00000028)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_11                 (0x0000002c)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_12                 (0x00000030)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_13                 (0x00000034)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_14                 (0x00000038)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_15                 (0x0000003c)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_16                 (0x00000040)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_17                 (0x00000044)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_18                 (0x00000048)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_19                 (0x0000004c)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_20                 (0x00000050)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_21                 (0x00000054)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_22                 (0x00000058)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_23                 (0x0000005c)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_24                 (0x00000060)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_25                 (0x00000064)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_26                 (0x00000068)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_27                 (0x0000006c)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_28                 (0x00000070)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_29                 (0x00000074)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_30                 (0x00000078)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_31                 (0x0000007c)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_32                 (0x00000080)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_33                 (0x00000084)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_34                 (0x00000088)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_35                 (0x0000008c)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_36                 (0x00000090)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_37                 (0x00000094)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_38                 (0x00000098)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_39                 (0x0000009c)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_40                 (0x000000a0)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_41                 (0x000000a4)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_42                 (0x000000a8)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_43                 (0x000000ac)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_44                 (0x000000b0)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_45                 (0x000000b4)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_46                 (0x000000b8)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_47                 (0x000000bc)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_48                 (0x000000c0)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_49                 (0x000000c4)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_50                 (0x000000c8)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_51                 (0x000000cc)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_52                 (0x000000d0)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_53                 (0x000000d4)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_54                 (0x000000d8)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_55                 (0x000000dc)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_56                 (0x000000e0)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_57                 (0x000000e4)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_58                 (0x000000e8)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_59                 (0x000000ec)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_60                 (0x000000f0)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_61                 (0x000000f4)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_62                 (0x000000f8)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_63                 (0x000000fc)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_64                 (0x00000100)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_65                 (0x00000104)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_66                 (0x00000108)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_67                 (0x0000010c)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_68                 (0x00000110)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_69                 (0x00000114)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_70                 (0x00000118)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_71                 (0x0000011c)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_72                 (0x00000120)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_73                 (0x00000124)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_74                 (0x00000128)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_75                 (0x0000012c)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_76                 (0x00000130)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_77                 (0x00000134)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_78                 (0x00000138)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_79                 (0x0000013c)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_80                 (0x00000140)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_81                 (0x00000144)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_82                 (0x00000148)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_83                 (0x0000014c)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_84                 (0x00000150)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_85                 (0x00000154)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_86                 (0x00000158)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_87                 (0x0000015c)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_88                 (0x00000160)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_89                 (0x00000164)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_90                 (0x00000168)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_91                 (0x0000016c)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_92                 (0x00000170)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_93                 (0x00000174)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_94                 (0x00000178)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_95                 (0x0000017c)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_96                 (0x00000180)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_97                 (0x00000184)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_98                 (0x00000188)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_99                 (0x0000018c)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_100                (0x00000190)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_101                (0x00000194)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_102                (0x00000198)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_103                (0x0000019c)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_104                (0x000001a0)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_105                (0x000001a4)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_106                (0x000001a8)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_107                (0x000001ac)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_108                (0x000001b0)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_109                (0x000001b4)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_110                (0x000001b8)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_111                (0x000001bc)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_112                (0x000001c0)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_113                (0x000001c4)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_114                (0x000001c8)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_115                (0x000001cc)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_116                (0x000001d0)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_117                (0x000001d4)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_118                (0x000001d8)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_119                (0x000001dc)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_120                (0x000001e0)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_121                (0x000001e4)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_122                (0x000001e8)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_123                (0x000001ec)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_124                (0x000001f0)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_125                (0x000001f4)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_126                (0x000001f8)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_127                (0x000001fc)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_128                (0x00000200)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_129                (0x00000204)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_130                (0x00000208)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_131                (0x0000020c)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_132                (0x00000210)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_133                (0x00000214)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_134                (0x00000218)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_135                (0x0000021c)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_136                (0x00000220)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_137                (0x00000224)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_138                (0x00000228)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_139                (0x0000022c)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_140                (0x00000230)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_141                (0x00000234)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_142                (0x00000238)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_143                (0x0000023c)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_144                (0x00000240)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_145                (0x00000244)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_146                (0x00000248)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_147                (0x0000024c)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_148                (0x00000250)
#define     NCP_MEMORY_CONTROLLER_DENALI_CTL_149                (0x00000254)
#ifdef __cplusplus
}
#endif

#endif /* _NCP_MEMORY_CONTROLLER_REG_DEFINES_H_ */
