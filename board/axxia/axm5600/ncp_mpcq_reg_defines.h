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
 *************************************************************************/



#ifndef _NCP_MPCQ_REG_DEFINES_H_
#define _NCP_MPCQ_REG_DEFINES_H_

#ifdef __cplusplus
extern "C" {
#endif

    /* NODE 0x0 , TARGET 0xffffffff*/


#define     NCP_MPCQ_CONTROL_VIRBASELSB                         (0x00000400)
#define     NCP_MPCQ_CONTROL_VIRBASEMSB                         (0x00000404)
#define     NCP_MPCQ_CONTROL_GLOBAL0                            (0x00000408)
#define     NCP_MPCQ_CONTROL_GLOBAL1                            (0x0000040c)
#define     NCP_MPCQ_ENABLE0                                    (0x00000410)
#define     NCP_MPCQ_ENABLE1                                    (0x00000414)
#define     NCP_MPCQ_ACTIVE0                                    (0x00000420)
#define     NCP_MPCQ_ACTIVE1                                    (0x00000424)
#define     NCP_MPCQ_INTERRUPT_STATUS0                          (0x00000010)
#define     NCP_MPCQ_INTERRUPT_STATUS0_ALARM_MASK               (0xffffffff)
#define     NCP_MPCQ_INTERRUPT_STATUS1                          (0x00000014)
#define     NCP_MPCQ_INTERRUPT_STATUS1_ALARM_MASK               (0xffffffff)
#define     NCP_MPCQ_INTERRUPT_STATUS2                          (0x00000018)
#define     NCP_MPCQ_INTERRUPT_STATUS2_SERVICE_MASK             (0xffffffff)
#define     NCP_MPCQ_INTERRUPT_STATUS3                          (0x0000001c)
#define     NCP_MPCQ_INTERRUPT_STATUS3_SERVICE_MASK             (0xffffffff)
#define     NCP_MPCQ_INTERRUPT_EN0                              (0x00000030)
#define     NCP_MPCQ_INTERRUPT_EN0_ALARM_MASK                   (0xffffffff)
#define     NCP_MPCQ_INTERRUPT_EN1                              (0x00000034)
#define     NCP_MPCQ_INTERRUPT_EN1_ALARM_MASK                   (0xffffffff)
#define     NCP_MPCQ_INTERRUPT_EN2                              (0x00000038)
#define     NCP_MPCQ_INTERRUPT_EN2_SERVICE_MASK                 (0xffffffff)
#define     NCP_MPCQ_INTERRUPT_EN3                              (0x0000003c)
#define     NCP_MPCQ_INTERRUPT_EN3_SERVICE_MASK                 (0xffffffff)
#define     NCP_MPCQ_INTERRUPT_FRC0                             (0x00000050)
#define     NCP_MPCQ_INTERRUPT_FRC0_ALARM_MASK                  (0xffffffff)
#define     NCP_MPCQ_INTERRUPT_FRC1                             (0x00000054)
#define     NCP_MPCQ_INTERRUPT_FRC1_ALARM_MASK                  (0xffffffff)
#define     NCP_MPCQ_INTERRUPT_FRC2                             (0x00000058)
#define     NCP_MPCQ_INTERRUPT_FRC2_SERVICE_MASK                (0xffffffff)
#define     NCP_MPCQ_INTERRUPT_FRC3                             (0x0000005c)
#define     NCP_MPCQ_INTERRUPT_FRC3_SERVICE_MASK                (0xffffffff)
#define     NCP_MPCQ_RAM_CONFIG_CONTROL                         (0x00800400)
#define     NCP_MPCQ_RAM_CONFIG_STATUS                          (0x00000010)
#define     NCP_MPCQ_RAM_CONFIG_STATUS_ALARM_MASK               (0x00000006)
#define     NCP_MPCQ_RAM_CONFIG_STATUS_SERVICE_MASK             (0x00000001)
#define     NCP_MPCQ_RAM_CONFIG_EN                              (0x00000030)
#define     NCP_MPCQ_RAM_CONFIG_EN_ALARM_MASK                   (0x00000006)
#define     NCP_MPCQ_RAM_CONFIG_EN_SERVICE_MASK                 (0x00000001)
#define     NCP_MPCQ_RAM_CONFIG_FRC                             (0x00000050)
#define     NCP_MPCQ_RAM_CONFIG_FRC_ALARM_MASK                  (0x00000006)
#define     NCP_MPCQ_RAM_CONFIG_FRC_SERVICE_MASK                (0x00000001)


#define     NCP_MPCQ_MME_MPCQ_RAM00_R_RAM_BASE                  (0x00900000)
#define     NCP_MPCQ_MME_MPCQ_RAM00_R_RAM(n)                    (0x00900000 + (32*(n)))
#define     NCP_MPCQ_MME_MPCQ_RAM00_R_RAM_ACCESS_SIZE           (0x00000020) /* Bytes */
#define     NCP_MPCQ_MME_MPCQ_RAM00_R_RAM_COUNT                 (0x00000040)
#define     NCP_MPCQ_MME_MPCQ_RAM00_R_RAM_IDX(addr) \
          (((addr) - NCP_MPCQ_MME_MPCQ_RAM00_R_RAM_BASE) / 32)
#define     NCP_MPCQ_MME_MPCQ_RAM00_R_RAM_END                   (0x00900800)
#define     NCP_MPCQ_MME_MPCQ_RAM00_R_RAM_RANGE(addr) \
       (((addr) >= NCP_MPCQ_MME_MPCQ_RAM00_R_RAM_BASE) && \
       ((addr) < NCP_MPCQ_MME_MPCQ_RAM00_R_RAM_END))

#ifdef __cplusplus
}
#endif

#endif /* _NCP_MPCQ_REG_DEFINES_H_ */
