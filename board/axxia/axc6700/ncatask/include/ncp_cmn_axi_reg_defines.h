/**************************************************************************
 ** INTEL CONFIDENTIAL
 ** Copyright 2008 - 2015 Intel Corporation All Rights Reserved.
 **
 ** The source code contained or described herein and all documents related to 
 ** the source code ("Material") are owned by Intel Corporation or its 
 ** suppliers or licensors. Title to the Material remains with 
 ** Intel Corporation or its suppliers and licensors. 
 ** The Material contains trade secrets and proprietary and confidential
 ** information of Intel or its suppliers and licensors. The Material is 
 ** protected by worldwide copyright and trade secret laws and treaty 
 ** provisions. No part of the Material may be used, copied, reproduced, 
 ** modified, published, uploaded, posted, transmitted, distributed, or 
 ** disclosed in any way without Intel's prior express written permission.
 **
 ** No license under any patent, copyright, trade secret or other 
 ** intellectual property right is granted to or conferred upon you by 
 ** disclosure or delivery of the Materials, either expressly, by implication, 
 ** inducement, estoppel or otherwise. Any license under such intellectual 
 ** property rights must be express and approved by Intel in writing.
 **  **********************************************************************/


#ifndef _NCP_CMN_AXI_REG_DEFINES_H_
#define _NCP_CMN_AXI_REG_DEFINES_H_

#ifdef __cplusplus
extern "C" {
#endif


    /* NODE 0x101 , TARGET 0xffffffff*/


#define     NCP_CMN_AXI_CFG_RING_PARITY                         (0x00000090)
#define     NCP_CMN_AXI_CFG_RING_DBG_STAT0                      (0x00000094)
#define     NCP_CMN_AXI_CFG_RING_DBG_STAT1                      (0x00000098)
#define     NCP_CMN_AXI_CNAL_IF_STATUS                          (0x0000009c)
#define     NCP_CMN_AXI_CNAL_CONTROL                            (0x000000a0)
#define     NCP_CMN_AXI_NUM_OF_CFG_NODES                        (0x000000e0)
#define     NCP_CMN_AXI_CFG_RING_ERROR_STAT_R0                  (0x000000e4)
#define     NCP_CMN_AXI_CFG_RING_ERROR_STAT_R1                  (0x000000e8)
#define     NCP_CMN_AXI_CFG_RING_NODE_STATUS                    (0x000000ec)
#define     NCP_CMN_AXI_CFG_PIO_CDR0                            (0x000000f0)
#define     NCP_CMN_AXI_CFG_PIO_CDR1                            (0x000000f4)
#define     NCP_CMN_AXI_CFG_PIO_CDR2                            (0x000000f8)
#define     NCP_CMN_AXI_CFG_RING_ACK_TIMER_CNT                  (0x000000fc)

#define     NCP_CMN_AXI_CDAR_MEMORY_BASE                        (0x00001000)
#define     NCP_CMN_AXI_CDAR_MEMORY(n)                          (0x00001000 + (4*(n)))
#define     NCP_CMN_AXI_CDAR_MEMORY_COUNT                       (0x00000080)
#define     NCP_CMN_AXI_CDAR_MEMORY_IDX(addr) \
                (((addr) - NCP_CMN_AXI_CDAR_MEMORY_BASE) / 4)     
#define     NCP_CMN_AXI_CDAR_MEMORY_END                         (0x00001200)
#define     NCP_CMN_AXI_CDAR_MEMORY_RANGE(addr) \
             (((addr) >= NCP_CMN_AXI_CDAR_MEMORY_BASE) && \
                ((addr) < NCP_CMN_AXI_CDAR_MEMORY_END))

#define     NCP_CMN_AXI_CDAR_WORD_129                           (0x00001200)
#define     NCP_CMN_AXI_NCA_PIO_LOCK_COWN                       (0x0000ff00)

#define     NCP_CMN_AXI_NCA_PIO_LOCK_BASE                       (0x0000ff80)
#define     NCP_CMN_AXI_NCA_PIO_LOCK(n)                         (0x0000ff80 + (4*(n)))
#define     NCP_CMN_AXI_NCA_PIO_LOCK_COUNT                      (0x00000020)
#define     NCP_CMN_AXI_NCA_PIO_LOCK_IDX(addr) \
               (((addr) - NCP_CMN_AXI_NCA_PIO_LOCK_BASE) / 4)    
#define     NCP_CMN_AXI_NCA_PIO_LOCK_END                        (0x00010000)
#define     NCP_CMN_AXI_NCA_PIO_LOCK_RANGE(addr) \
            (((addr) >= NCP_CMN_AXI_NCA_PIO_LOCK_BASE) && \
              ((addr) < NCP_CMN_AXI_NCA_PIO_LOCK_END))

#define     NCP_CMN_AXI_CONFIG_INIT                             (0x00010010)
#define     NCP_CMN_AXI_CFG_PIO_CDR3                            (0x00010270)

#define     NCP_CMN_AXI_SW_SCRATCH_BASE                         (0x0001ff00)
#define     NCP_CMN_AXI_SW_SCRATCH(n)                           (0x0001ff00 + (4*(n)))
#define     NCP_CMN_AXI_SW_SCRATCH_COUNT                        (0x00000040)
#define     NCP_CMN_AXI_SW_SCRATCH_IDX(addr) \
                 (((addr) - NCP_CMN_AXI_SW_SCRATCH_BASE) / 4)      
#define     NCP_CMN_AXI_SW_SCRATCH_END                          (0x00020000)
#define     NCP_CMN_AXI_SW_SCRATCH_RANGE(addr) \
              (((addr) >= NCP_CMN_AXI_SW_SCRATCH_BASE) && \
                  ((addr) < NCP_CMN_AXI_SW_SCRATCH_END))

#define     NCP_CMN_AXI_PARAM_NUM_OUTSTANDING_CPCQ_REQS         (0x00020090)
#define     NCP_CMN_AXI_AW_SMON00_CMN_SMON                      (0x000200e0)
#define     NCP_CMN_AXI_AW_SMON01_CMN_SMON                      (0x000200e4)
#define     NCP_CMN_AXI_AW_SMON02_CMN_SMON                      (0x000200e8)
#define     NCP_CMN_AXI_AW_SMON03_CMN_SMON                      (0x000200ec)
#define     NCP_CMN_AXI_AW_SMON04_CMN_SMON                      (0x000200f0)
#define     NCP_CMN_AXI_AW_SMON05_CMN_SMON                      (0x000200f4)
#define     NCP_CMN_AXI_AW_SMON06_CMN_SMON                      (0x000200f8)
#define     NCP_CMN_AXI_AW_SMON07_CMN_SMON                      (0x000200fc)
#define     NCP_CMN_AXI_CFG_ENABLESECURE                        (0x00020100)
#define     NCP_CMN_AXI_CFG_TTYPE_SYSTEM_0_R                    (0x00020114)
#define     NCP_CMN_AXI_CFG_TTYPE_EXTERNAL_0_R                  (0x00020118)
#define     NCP_CMN_AXI_CFG_TTYPE_SYSTEM_1_R                    (0x0002011c)
#define     NCP_CMN_AXI_PIO_CPCQ_ARB_CONTROL                    (0x00020120)
#define     NCP_CMN_AXI_CFG_MAX_OUTSTANDING_CPCQS               (0x00020124)
#define     NCP_CMN_AXI_COUNTER_RESET                           (0x00020128)
#define     NCP_CMN_AXI_PIO_ISSUED_INSTRUCTIONS_CNT             (0x000206f0)
#define     NCP_CMN_AXI_PIO_COMPLETED_INSTRUCTIONS_CNT          (0x000206f4)
#define     NCP_CMN_AXI_CPCQ_ISSUED_INSTRUCTIONS_CNT            (0x000206f8)
#define     NCP_CMN_AXI_CPCQ_COMPLETED_INSTRUCTIONS_CNT         (0x000206fc)
#define     NCP_CMN_AXI_PIO_CPCQ_ARB_STATUS                     (0x00020818)
#define     NCP_CMN_AXI_SM_VAR_DELAY_STATE                      (0x0002081c)
#define     NCP_CMN_AXI_AXI_RSTATE                              (0x00020820)
#define     NCP_CMN_AXI_CSTATE                                  (0x00020824)
#define     NCP_CMN_AXI_SPLIT_STATE                             (0x00020828)
#define     NCP_CMN_AXI_AXI_READ_STATE                          (0x0002082c)
#define     NCP_CMN_AXI_AXI_WRITE_STATE                         (0x00020830)
#define     NCP_CMN_AXI_RENG_READ_OP_STATE                      (0x00020834)
#define     NCP_CMN_AXI_WENG_WRITE_OP_STATE                     (0x00020838)
#define     NCP_CMN_AXI_OUTSTANDING_CPCQS_COUNT                 (0x0002083c)
#define     NCP_CMN_AXI_OUTSTANDING_CPCQS_COUNTER_STATUS        (0x00020840)
#define     NCP_CMN_AXI_RENG_EXT_MEM_REORDER_BUF_FIFO_STATUS_00  (0x00020e00)
#define     NCP_CMN_AXI_RENG_EXT_MEM_REORDER_BUF_FIFO_CONTROL_00  (0x00020e04)
#define     NCP_CMN_AXI_RENG_EXT_MEM_REORDER_BUF_FIFO_STATUS_01  (0x00020e08)
#define     NCP_CMN_AXI_RENG_EXT_MEM_REORDER_BUF_FIFO_CONTROL_01  (0x00020e0c)
#define     NCP_CMN_AXI_RENG_SYS_MEM_REORDER_BUF_FIFO_STATUS_00  (0x00020e10)
#define     NCP_CMN_AXI_RENG_SYS_MEM_REORDER_BUF_FIFO_CONTROL_00  (0x00020e14)
#define     NCP_CMN_AXI_RENG_SYS_MEM_REORDER_BUF_FIFO_STATUS_01  (0x00020e18)
#define     NCP_CMN_AXI_RENG_SYS_MEM_REORDER_BUF_FIFO_CONTROL_01  (0x00020e1c)
#define     NCP_CMN_AXI_RENG_REQ_FIFO_STATUS                    (0x00020e20)
#define     NCP_CMN_AXI_RENG_REQ_FIFO_CONTROL                   (0x00020e24)
#define     NCP_CMN_AXI_WENG_WDB_FIFO_STATUS                    (0x00020e28)
#define     NCP_CMN_AXI_WENG_WDB_FIFO_CONTROL                   (0x00020e2c)
#define     NCP_CMN_AXI_WENG_REQ_FIFO_STATUS                    (0x00020e30)
#define     NCP_CMN_AXI_WENG_REQ_FIFO_CONTROL                   (0x00020e34)
#define     NCP_CMN_AXI_CPCQ_REQ_FIFO_STATUS                    (0x00020e38)
#define     NCP_CMN_AXI_CPCQ_REQ_FIFO_CONTROL                   (0x00020e3c)
#define     NCP_CMN_AXI_CPCQ_REQ_BRESP_FIFO_STATUS              (0x00020e40)
#define     NCP_CMN_AXI_CPCQ_REQ_BRESP_FIFO_CONTROL             (0x00020e44)
#define     NCP_CMN_AXI_CPCQ_RESP_FIFO_STATUS                   (0x00020e48)
#define     NCP_CMN_AXI_CPCQ_RESP_FIFO_CONTROL                  (0x00020e4c)
#define     NCP_CMN_AXI_CFG_SETUP                               (0x00020ffc)
#define     NCP_CMN_AXI_GRP_INTERRUPT_STATUS_TABLE_STATUS_R0    (0x0001f020)
#define     NCP_CMN_AXI_GRP_INTERRUPT_STATUS_TABLE_STATUS_R1    (0x0001f024)
#define     NCP_CMN_AXI_GRP_INTERRUPT_STATUS_TABLE_STATUS_R2    (0x0001f028)
#define     NCP_CMN_AXI_GRP_INTERRUPT_STATUS_TABLE_STATUS_R3    (0x0001f02c)
#define     NCP_CMN_AXI_GRP_INTERRUPT_ENABLE_TABLE_EN_R0        (0x0001f030)
#define     NCP_CMN_AXI_GRP_INTERRUPT_ENABLE_TABLE_EN_R1        (0x0001f034)
#define     NCP_CMN_AXI_GRP_INTERRUPT_ENABLE_TABLE_EN_R2        (0x0001f038)
#define     NCP_CMN_AXI_GRP_INTERRUPT_ENABLE_TABLE_EN_R3        (0x0001f03c)
#define     NCP_CMN_AXI_GRP_INTERRUPT_FORCE_TABLE_FRC_R0        (0x0001f040)
#define     NCP_CMN_AXI_GRP_INTERRUPT_FORCE_TABLE_FRC_R1        (0x0001f044)
#define     NCP_CMN_AXI_GRP_INTERRUPT_FORCE_TABLE_FRC_R2        (0x0001f048)
#define     NCP_CMN_AXI_GRP_INTERRUPT_FORCE_TABLE_FRC_R3        (0x0001f04c)
#define     NCP_CMN_AXI_INT_REG0_STATUS                         (0x00020010)
#define     NCP_CMN_AXI_INT_REG0_EN                             (0x00020030)
#define     NCP_CMN_AXI_INT_REG0_FRC                            (0x00020050)
#define     NCP_CMN_AXI_INTERFACE_BITS                          (0x00020004)
#define     NCP_CMN_AXI_INTERFACE_BITS_ACCESS_SIZE              (0x00000008) /* Bytes */
#ifdef __cplusplus
}
#endif

#endif /* _NCP_CMN_AXI_REG_DEFINES_H_ */
