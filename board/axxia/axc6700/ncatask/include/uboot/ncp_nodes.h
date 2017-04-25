/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/

/*! @file      ncp_nodes.h
    @brief     Lists all the Node IDs within the NCP.
*/


#ifndef __NCP_NODES_H__
#define __NCP_NODES_H__

/*! 
 * Node definitions for all nodes/engines in NCP/X1. 
 * IMPORTANT: Please get in touch with node/engine owner BEFORE changing this!!
 * This needs to be kept in-sync with HW.
 */

#define NCP_NODE_NTIMC(n)           (((n) <= 7 ) ? (n) : (n) + 0x42)  /* Nodes 0x00 - 0x07 */
#define NCP_NODE_NTEMC(n)           (0x08+(n))   /* Nodes 0x08 & 0x09 */
#define NCP_NODE_X1_ECID             0x0A
#define NCP_NODE_SPP                 0x0B
#define NCP_NODE_SED                 0x0C
#define NCP_NODE_DDR1_PLL            0x0D
#define NCP_NODE_DPI                 0x0E
#define NCP_NODE_DPI_HFA             0x0E
#define NCP_NODE_SM1                 0x0F
#define NCP_NODE_SC6                 0x10
#define NCP_NODE_SC4                 0x11
#define NCP_NODE_SC5                 0x12
#define NCP_NODE_SC7                 0x13
#define NCP_NODE_MTM                 0x14
#define NCP_NODE_EXPANDER            0x14
#define NCP_NODE_MME                 0x15
#define NCP_NODE_MMB                 0x15
#define NCP_NODE_NCA                 0x16
#define NCP_NODE_EIOA1               0x17
#define NCP_NODE_NIC                 0x18
#define NCP_NODE_TIMER               0x19
#define NCP_NODE_MPP                 0x1A
#define NCP_NODE_PIC                 0x1B
#define NCP_NODE_PAB_TOP             0x1C
#define NCP_NODE_SC3                 0x1D
#define NCP_NODE_SC1                 0x1E
#define NCP_NODE_EIOA0               0x1F
#define NCP_NODE_SC0                 0x20
#define NCP_NODE_SC2                 0x21
#define NCP_NODE_SM0                 0x22
#define NCP_NODE_DDR0_PLL            0x23
#define NCP_NODE_EIOA_ACL_BL         0x24
#define NCP_NODE_TDMIOA              0x25
#define NCP_NODE_EIOA2               0x28
#define NCP_NODE_EIOA3               0x29
#define NCP_NODE_EIOA4               0x2A
#define NCP_NODE_EIOA5               0x2B
#define NCP_NODE_EIOA6               0x2C
#define NCP_NODE_EIOA7               0x2D

#define NCP_NODE_PCX                 0x2E

#define NCP_NODE_CCM                 0x2F
#define NCP_NODE_CCMS                0x30

#define NCP_NODE_ISB                 0x31
#define NCP_NODE_ISBS                0x32
#define NCP_NODE_PBM                 0x33
#define NCP_NODE_ISBS1               0x35
#define NCP_NODE_PBM_TQ              0x36
#define NCP_NODE_DEC                 0x3E

#define NCP_NODE_ERIF0               0x40
#define NCP_NODE_ERIF1               0x41
#define NCP_NODE_RIF0                0x44
#define NCP_NODE_RIF1                0x45

#define NCP_NODE_PKA                 0x103

#define NCP_NODE_EIOA_PHY0           0x110
#define NCP_NODE_EIOA_PHY1           0x111
#define NCP_NODE_EIOA_PHY2           0x112
#define NCP_NODE_EIOA_PHY3           0x113
#define NCP_NODE_EIOA_PHY4           0x114
#define NCP_NODE_EIOA_PHY5           0x116
#define NCP_NODE_EIOA_PHY6           0x117
#define NCP_NODE_EIOA_PHY7           0x118
#define NCP_NODE_EIOA_PHY8           0x119
#define NCP_NODE_EIOA_PHY9           0x11a
#define NCP_NODE_EIOA_PHY10          0x11b
#define NCP_NODE_EIOA_PHY11          0x11c
#define NCP_NODE_EIOA_PHY12          0x11d
#define NCP_NODE_EIOA_PHY13          0x11e
#define NCP_NODE_EIOA_PHY14          0x11f

#define NCP_NODE_TRNG                0x121
#define NCP_NODE_SSP                 0x142
#define NCP_NODE_I2C_0               0x143
#define NCP_NODE_I2C_1               0x14c
#define NCP_NODE_I2C_2               0x152
#define NCP_NODE_AXIS_APB2SER0       0x153
#define NCP_NODE_AXIS_APB2SER1       0x154
#define NCP_NODE_AXIS_APB2SER2       0x155
#define NCP_NODE_AXIS_AXI2SER2       0x155
#define NCP_NODE_AXIS_APB2SER_CLK    0x155
#define NCP_NODE_AXIS_APB2SER3       0x156
#define NCP_NODE_AXIS_AXI2SER3       0x156
#define NCP_NODE_SMB_0               0x15C

#define NCP_NODE_AXIS_AXI2SER5       0x165
#define NCP_NODE_AXIS_AXI2SER8       0x168
#define NCP_NODE_AXI2SER9_CDC        0x169

#define NCP_NODE_L2_0                0x183
#define NCP_NODE_L2_1                0x184
#define NCP_NODE_L2_2                0x185
#define NCP_NODE_L2_4                0x186

#define NCP_NODE_PPC_ITRACE          0x187
#define NCP_NODE_L2_0_TRACE          0x188
#define NCP_NODE_L2_1_TRACE          0x189
#define NCP_NODE_L2_2_TRACE          0x18a
#define NCP_NODE_L2_3_TRACE          0x18b
#define NCP_NODE_LAM_ITRACE          0x18c
#define NCP_NODE_SYSCON_CLK          0x18d
#define NCP_NODE_SYSCON_RST          0x18e
#define NCP_NODE_APB2SER             0x1d1



#define NCP_NODE_I2C_PROTOCOL        0x210
#define NCP_NODE_I2C_1_PROTOCOL      0x211
#define NCP_NODE_I2C_2_PROTOCOL      0x212
#define NCP_NODE_SMB_0_PROTOCOL      0x218
#define NCP_NODE_LBM_EXT_DEVICES     0x220

#define NCP_NODE_I2C_3_PROTOCOL      0x213
#define NCP_NODE_I2C_4_PROTOCOL      0x214
#define NCP_NODE_I2C_5_PROTOCOL      0x215
#define NCP_NODE_I2C_6_PROTOCOL      0x216
#define NCP_NODE_I2C_7_PROTOCOL      0x217
#define NCP_NODE_I2C_8_PROTOCOL      0x219
#define NCP_NODE_I2C_9_PROTOCOL      0x21a
#define NCP_NODE_I2C_10_PROTOCOL      0x21b
#define NCP_NODE_I2C_11_PROTOCOL      0x21c


#define NCP_NODE_SYSCACHE(n)       \
             ((n) == 0)  ? 0x20 :  \
	     (((n) == 1) ? 0x1e :  \
	     (((n) == 2) ? 0x21 :  \
	     (((n) == 3) ? 0x1d :  \
	     (((n) == 4) ? 0x11 :  \
	     (((n) == 5) ? 0x12 :  \
	     (((n) == 6) ? 0x10 :  \
	     (((n) == 7) ? 0x13 :  \
	     0xffff)))))))

#define NCP_SYSCACHE_NUM_NODES       8
#define NCP_SYSMEM_NUM_NODES         2
#define NCP_TREEMEM_NUM_NODES        2

#define NCP_EXTMEM_NUM_NODES    (NCP_SYSMEM_NUM_NODES + NCP_TREEMEM_NUM_NODES)

/*!
 * Module node type values that appear in the module info 0
 * register for each of the modules.
 */
#define NCP_NODE_TYPE_DPI       0
#define NCP_NODE_TYPE_EIOA      1
#define NCP_NODE_TYPE_MMB       2
#define NCP_NODE_TYPE_MPP       3
#define NCP_NODE_TYPE_MTM       4
#define NCP_NODE_TYPE_NCA       5
#define NCP_NODE_TYPE_NIC       6
#define NCP_NODE_TYPE_NTEMC     7
#define NCP_NODE_TYPE_NTIMC     8
#define NCP_NODE_TYPE_PAB       9
#define NCP_NODE_TYPE_PIC       10
#define NCP_NODE_TYPE_SC        11
#define NCP_NODE_TYPE_SED       12
#define NCP_NODE_TYPE_SM        13
#define NCP_NODE_TYPE_SPP       14
#define NCP_NODE_TYPE_TIMER     15
#define NCP_NODE_TYPE_X1_ECID   16
#define NCP_NODE_TYPE_DDR_PLL   17


#endif /* __NCP_NODES_H__ */
