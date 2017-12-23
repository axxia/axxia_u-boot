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



#ifndef _NCP_NHA_REG_DEFINES_H_
#define _NCP_NHA_REG_DEFINES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ncp_sal_types.h"


    /* NODE 0x18f , TARGET 0xffffffff*/


#define     NCP_NHA_CFG1                                        (0x00000000)
#define     NCP_NHA_CFG1_ACP2500                                (0x00000000)
#define     NCP_NHA_CFG2                                        (0x00000004)
#define     NCP_NHA_CFG3                                        (0x00000008)
#define     NCP_NHA_CFG3_ACP2500                                (0x00000008)
#define     NCP_NHA_CFG4                                        (0x0000000c)
#define     NCP_NHA_CFG4_ACP2500                                (0x0000000c)
#define     NCP_NHA_MIN_ARADDR                                  (0x0000001c)
#define     NCP_NHA_MAX_ARADDR                                  (0x00000020)
#define     NCP_NHA_MIN_AWADDR                                  (0x00000024)
#define     NCP_NHA_MAX_AWADDR                                  (0x00000028)
#define     NCP_NHA_LAM_DEBUG1                                  (0x0000002c)
#define     NCP_NHA_LAM_DEBUG2                                  (0x00000030)
#define     NCP_NHA_MAST_PRIORITY                               (0x00000034)
#define     NCP_NHA_COUNTER_OVFL                                (0x00000038)
#define     NCP_NHA_COUNTER_CTL                                 (0x0000003c)
#define     NCP_NHA_COUNTER_CTL_ACP2500                         (0x0000003c)
#define     NCP_NHA_CLK_COUNT                                   (0x00000040)
#define     NCP_NHA_CLK_COUNT_LS_ACP2500                        (0x00000040)
#define     NCP_NHA_COUNTER0                                    (0x00000044)
#define     NCP_NHA_COUNTER0_LS_ACP2500                         (0x00000044)
#define     NCP_NHA_COUNTER1                                    (0x00000048)
#define     NCP_NHA_COUNTER1_LS_ACP2500                         (0x00000048)
#define     NCP_NHA_COUNTER2                                    (0x0000004c)
#define     NCP_NHA_COUNTER2_LS_ACP2500                         (0x0000004c)
#define     NCP_NHA_COUNTER3                                    (0x00000050)
#define     NCP_NHA_COUNTER3_LS_ACP2500                         (0x00000050)
#define     NCP_NHA_ARID_FREELIST                               (0x00000054)
#define     NCP_NHA_AWID_FREELIST                               (0x00000058)
#define     NCP_NHA_RCT_CNT                                     (0x0000005c)
#define     NCP_NHA_RCT_CNT_ACP2500                             (0x0000005c)
#define     NCP_NHA_WCT_CNT                                     (0x00000060)
#define     NCP_NHA_WCT_CNT_ACP2500                             (0x00000060)
#define     NCP_NHA_SPEC_READ_ALLOW                             (0x0000007c)
#define     NCP_NHA_CRFIFO_HIGH_WM                              (0x00000080)
#define     NCP_NHA_CR_FIFO_STAT                                (0x00000084)
#define     NCP_NHA_WPM_WDATA_FIFO_HIGH_WM_V2                   (0x00000088)
#define     NCP_NHA_WPM_WRITE_DATA_FIFO_STAT                    (0x0000008c)
#define     NCP_NHA_WRITE_REQUEST_FIFO_STAT_ACP2500             (0x0000008c)
#define     NCP_NHA_LCM_READ_REQUEST_FIFO_STAT                  (0x00000090)
#define     NCP_NHA_LCM_WRITE_REQUEST_FIFO_STAT                 (0x00000094)
#define     NCP_NHA_LCM_WRITE_DATA_FIFO_STAT                    (0x00000098)
#define     NCP_NHA_LCM_READ_RESPONSE_FIFO_STAT                 (0x0000009c)
#define     NCP_NHA_LCM_WRITE_RESPONSE_FIFO_STAT                (0x000000a0)
#define     NCP_NHA_CC_ARFIFO_HIGH_WM                           (0x000000a4)
#define     NCP_NHA_CC_READ_REQUEST_FIFO_STAT                   (0x000000a8)
#define     NCP_NHA_CC_AWFIFO_HIGH_WM                           (0x000000ac)
#define     NCP_NHA_CC_WRITE_REQUEST_FIFO_STAT                  (0x000000b0)
#define     NCP_NHA_CC_WFIFO_HIGH_WM                            (0x000000b4)
#define     NCP_NHA_CC_WRITE_DATA_FIFO_STAT                     (0x000000b8)
#define     NCP_NHA_CC_RFIFO_HIGH_WM                            (0x000000bc)
#define     NCP_NHA_CC_READ_RESPONSE_FIFO_STAT                  (0x000000c0)
#define     NCP_NHA_CC_BFIFO_HIGH_WM                            (0x000000c4)
#define     NCP_NHA_CC_WRITE_RESPONSE_FIFO_STAT                 (0x000000c8)
#define     NCP_NHA_CC_GONOGOFIFO_HIGH_WM                       (0x000000cc)
#define     NCP_NHA_CC_GONOGO_FIFO_STAT                         (0x000000d0)
#define     NCP_NHA_NR_FIFO_STAT                                (0x000000d4)
#define     NCP_NHA_READ_HOLDING_FIFO_STAT_ACP2500              (0x000000d4)
#define     NCP_NHA_CPM_SYNDROME0                               (0x00000100)
#define     NCP_NHA_CPM_SYNDROME1                               (0x00000104)
#define     NCP_NHA_CPM_SYNDROME2                               (0x00000108)
#define     NCP_NHA_CPM_SYNDROME3                               (0x0000010c)
#define     NCP_NHA_RPM_SYNDROME0                               (0x00000110)
#define     NCP_NHA_RPM_SYNDROME1                               (0x00000114)
#define     NCP_NHA_WPM_SYNDROME0                               (0x0000011c)
#define     NCP_NHA_WPM_SYNDROME1                               (0x00000120)
#define     NCP_NHA_WPM_SYNDROME2                               (0x00000124)
#define     NCP_NHA_WPM_SYNDROME3                               (0x00000128)
#define     NCP_NHA_WPM_SYNDROME4                               (0x0000012c)
#define     NCP_NHA_WPM_SYNDROME5                               (0x00000130)
#define     NCP_NHA_WPM_SYNDROME6                               (0x00000134)
#define     NCP_NHA_WPM_SYNDROME7                               (0x00000138)
#define     NCP_NHA_WPM_SYNDROME8                               (0x0000013c)
#define     NCP_NHA_CPM_RCT_S0CNT                               (0x00000140)
#define     NCP_NHA_CPM_RCT_S0CNT_ACP2500                       (0x00000140)
#define     NCP_NHA_CPM_RCT_S1CNT                               (0x00000144)
#define     NCP_NHA_CPM_RCT_S1CNT_ACP2500                       (0x00000144)
#define     NCP_NHA_CPM_RCT_S2CNT                               (0x00000148)
#define     NCP_NHA_CPM_RCT_S2CNT_ACP2500                       (0x00000148)
#define     NCP_NHA_CPM_RCT_S3CNT                               (0x0000014c)
#define     NCP_NHA_CPM_RCT_S3CNT_ACP2500                       (0x0000014c)
#define     NCP_NHA_CPM_RCT_S4CNT_V2                            (0x00000150)
#define     NCP_NHA_CPM_RCT_S5CNT_V2                            (0x00000154)
#define     NCP_NHA_CPM_RCT_S6CNT_V2                            (0x00000158)
#define     NCP_NHA_CPM_RCT_S7CNT_V2                            (0x0000015c)
#define     NCP_NHA_CPM_WCT_S0CNT                               (0x00000160)
#define     NCP_NHA_CPM_WCT_S0CNT_ACP2500                       (0x00000200)
#define     NCP_NHA_CPM_WCT_S1CNT                               (0x00000164)
#define     NCP_NHA_CPM_WCT_S1CNT_ACP2500                       (0x00000204)
#define     NCP_NHA_CPM_WCT_S2CNT                               (0x00000168)
#define     NCP_NHA_CPM_WCT_S2CNT_ACP2500                       (0x00000208)
#define     NCP_NHA_CPM_WCT_S3CNT                               (0x0000016c)
#define     NCP_NHA_CPM_WCT_S3CNT_ACP2500                       (0x0000020c)
#define     NCP_NHA_CPM_WCT_S4CNT_V2                            (0x00000170)
#define     NCP_NHA_CPM_WCT_S5CNT_V2                            (0x00000174)
#define     NCP_NHA_CPM_WCT_S6CNT_V2                            (0x00000178)
#define     NCP_NHA_CPM_WCT_S7CNT_V2                            (0x0000017c)
#define     NCP_NHA_LCM_CFG                                     (0x00000200)
#define     NCP_NHA_LCM_CFG_ACP2500                             (0x00000300)
#define     NCP_NHA_CLKSYS_COUNTER_CTL                          (0x00000204)
#define     NCP_NHA_CLKSYS_COUNTER_CTL_ACP2500                  (0x00000304)
#define     NCP_NHA_CLKSYS_CLK_COUNT                            (0x00000208)
#define     NCP_NHA_CPM_WCT_S2CNT_ACP2500                       (0x00000208)
#define     NCP_NHA_CLKSYS_COUNTER0                             (0x0000020c)
#define     NCP_NHA_CPM_WCT_S3CNT_ACP2500                       (0x0000020c)
#define     NCP_NHA_CLKSYS_COUNTER1_V2                          (0x00000210)
#define     NCP_NHA_CLKSYS_COUNTER_OVFL                         (0x00000214)
#define     NCP_NHA_CLKSYS_COUNTER_OVFL_ACP2500                 (0x00000314)
#define     NCP_NHA_LCM_WM                                      (0x00000218)
#define     NCP_NHA_LCM_WM_ACP2500                              (0x00000318)
#define     NCP_NHA_LCM_BANK0_FIFO_STAT_V2                      (0x00000240)
#define     NCP_NHA_LCM_BANK1_FIFO_STAT_V2                      (0x00000244)
#define     NCP_NHA_LCM_BANK2_FIFO_STAT_V2                      (0x00000248)
#define     NCP_NHA_LCM_BANK3_FIFO_STAT_V2                      (0x0000024c)
#define     NCP_NHA_LCM_UNORDERED_READ_FIFO_STAT_V2             (0x00000250)
#define     NCP_NHA_LCM_ORDERED_READ_FIFO_STAT_V2               (0x00000254)
#define     NCP_NHA_LCM_READ_STATUS                             (0x00000280)
#define     NCP_NHA_LCM_READ_STATUS_ACP2500                     (0x00000388)
#define     NCP_NHA_LCM_READ_DATA0                              (0x00000284)
#define     NCP_NHA_LCM_READ_DATA0_ACP2500                      (0x0000038c)
#define     NCP_NHA_LCM_READ_DATA1                              (0x00000288)
#define     NCP_NHA_LCM_READ_DATA1_ACP2500                      (0x00000390)
#define     NCP_NHA_LCM_READ_DATA2                              (0x0000028c)
#define     NCP_NHA_LCM_READ_DATA2_ACP2500                      (0x00000394)
#define     NCP_NHA_LCM_READ_DATA3                              (0x00000290)
#define     NCP_NHA_LCM_READ_DATA3_ACP2500                      (0x00000398)
#define     NCP_NHA_LCM_ERRORS_STATUS                           (0x00000294)
#define     NCP_NHA_WPM_WRITE_DATA5_FIFO_STAT_ACP2500           (0x00000294)
#define     NCP_NHA_LCM_ERRORS_FORCE                            (0x00000298)
#define     NCP_NHA_WPM_WRITE_DATA6_FIFO_STAT_ACP2500           (0x00000298)
#define     NCP_NHA_CLK_COUNT_MS_ACP2500                        (0x00000064)
#define     NCP_NHA_COUNTER0_MS_ACP2500                         (0x00000068)
#define     NCP_NHA_COUNTER1_MS_ACP2500                         (0x0000006c)
#define     NCP_NHA_COUNTER2_MS_ACP2500                         (0x00000070)
#define     NCP_NHA_COUNTER3_MS_ACP2500                         (0x00000074)
#define     NCP_NHA_WRITE_HOLDING_FIFO_STAT_ACP2500             (0x000000d8)
#define     NCP_NHA_CACHE_READ_FIFO_HIGH_WM_ACP2500             (0x000000dc)
#define     NCP_NHA_CACHE_READ_FIFO_STAT_ACP2500                (0x000000e0)
#define     NCP_NHA_AMAP_LSTATUS_ACP2500                        (0x000001c0)
#define     NCP_NHA_AMAP_PSTATUS_ACP2500                        (0x000001c4)
#define     NCP_NHA_AMAP_MSTATUS_ACP2500                        (0x000001c8)
#define     NCP_NHA_WPM_WRITE_DATA0_FIFO_STAT_ACP2500           (0x00000280)
#define     NCP_NHA_WPM_WRITE_DATA1_FIFO_STAT_ACP2500           (0x00000284)
#define     NCP_NHA_WPM_WRITE_DATA2_FIFO_STAT_ACP2500           (0x00000288)
#define     NCP_NHA_WPM_WRITE_DATA3_FIFO_STAT_ACP2500           (0x0000028c)
#define     NCP_NHA_WPM_WRITE_DATA4_FIFO_STAT_ACP2500           (0x00000290)
#define     NCP_NHA_WPM_WRITE_DATA7_FIFO_STAT_ACP2500           (0x0000029c)
#define     NCP_NHA_WPM_WRITE_DATA8_FIFO_STAT_ACP2500           (0x000002a0)
#define     NCP_NHA_WPM_WRITE_DATA9_FIFO_STAT_ACP2500           (0x000002a4)
#define     NCP_NHA_WPM_WRITE_DATA10_FIFO_STAT_ACP2500          (0x000002a8)
#define     NCP_NHA_WPM_WRITE_DATA11_FIFO_STAT_ACP2500          (0x000002ac)
#define     NCP_NHA_WPM_WRITE_DATA12_FIFO_STAT_ACP2500          (0x000002b0)
#define     NCP_NHA_WPM_WRITE_DATA13_FIFO_STAT_ACP2500          (0x000002b4)
#define     NCP_NHA_WPM_WRITE_DATA14_FIFO_STAT_ACP2500          (0x000002b8)
#define     NCP_NHA_WPM_WRITE_DATA15_FIFO_STAT_ACP2500          (0x000002bc)
#define     NCP_NHA_CLKSYS_CLK_COUNT_LS_ACP2500                 (0x00000308)
#define     NCP_NHA_CLKSYS_COUNTER0_LS_ACP2500                  (0x0000030c)
#define     NCP_NHA_CLKSYS_COUNTER1_LS_ACP2500                  (0x00000310)
#define     NCP_NHA_CLKSYS_CLK_COUNT_MS_ACP2500                 (0x0000031c)
#define     NCP_NHA_CLKSYS_COUNTER0_MS_ACP2500                  (0x00000320)
#define     NCP_NHA_CLKSYS_COUNTER1_MS_ACP2500                  (0x00000324)
#define     NCP_NHA_INT_STATUS                                  (0x00000010)
#define     NCP_NHA_INT_STATUS_ALARM_MASK                       (0xf3df7ffd)
#define     NCP_NHA_INT_STATUS_SERVICE_MASK                     (0x0c208002)
#define     NCP_NHA_INT_ACP2500_STATUS_ACP2500                  (0x00000010)
#define     NCP_NHA_INT_ACP2500_STATUS_ACP2500_ALARM_MASK       (0xf3df7fff)
#define     NCP_NHA_INT_ACP2500_STATUS_ACP2500_SERVICE_MASK     (0x0c208000)
#define     NCP_NHA_INT_EN                                      (0x00000014)
#define     NCP_NHA_INT_EN_ALARM_MASK                           (0xf3df7ffd)
#define     NCP_NHA_INT_EN_SERVICE_MASK                         (0x0c208002)
#define     NCP_NHA_INT_ACP2500_EN_ACP2500                      (0x00000014)
#define     NCP_NHA_INT_ACP2500_EN_ACP2500_ALARM_MASK           (0xf3df7fff)
#define     NCP_NHA_INT_ACP2500_EN_ACP2500_SERVICE_MASK         (0x0c208000)
#define     NCP_NHA_INT_FRC                                     (0x00000018)
#define     NCP_NHA_INT_FRC_ALARM_MASK                          (0xf3df7ffd)
#define     NCP_NHA_INT_FRC_SERVICE_MASK                        (0x0c208002)
#define     NCP_NHA_INT_ACP2500_FRC_ACP2500                     (0x00000018)
#define     NCP_NHA_INT_ACP2500_FRC_ACP2500_ALARM_MASK          (0xf3df7fff)
#define     NCP_NHA_INT_ACP2500_FRC_ACP2500_SERVICE_MASK        (0x0c208000)


#define     NCP_NHA_AMAP_TABLE_ACP2500_SEGMENT_ACP2500_BASE     (0x00000180)
#define     NCP_NHA_AMAP_TABLE_ACP2500_SEGMENT_ACP2500(n)       (0x00000180 + (16*(n)))
#define     NCP_NHA_AMAP_TABLE_ACP2500_SEGMENT_ACP2500_ACCESS_SIZE  (0x00000010) /* Bytes */
#define     NCP_NHA_AMAP_TABLE_ACP2500_SEGMENT_ACP2500_COUNT    (0x00000004)
#define     NCP_NHA_AMAP_TABLE_ACP2500_SEGMENT_ACP2500_IDX(addr) \
  (((addr) - NCP_NHA_AMAP_TABLE_ACP2500_SEGMENT_ACP2500_BASE) / 16)
#define     NCP_NHA_AMAP_TABLE_ACP2500_SEGMENT_ACP2500_END      (0x000001c0)
#define     NCP_NHA_AMAP_TABLE_ACP2500_SEGMENT_ACP2500_RANGE(addr) \
 (((addr) >= NCP_NHA_AMAP_TABLE_ACP2500_SEGMENT_ACP2500_BASE) && \
  ((addr) < NCP_NHA_AMAP_TABLE_ACP2500_SEGMENT_ACP2500_END))

#define     NCP_NHA_LCM_INT_ACP2500_STATUS_ACP2500              (0x000003d0)
#define     NCP_NHA_LCM_INT_ACP2500_STATUS_ACP2500_ALARM_MASK   (0x0000000d)
#define     NCP_NHA_LCM_INT_ACP2500_STATUS_ACP2500_SERVICE_MASK  (0x00000002)
#define     NCP_NHA_LCM_INT_ACP2500_EN_ACP2500                  (0x000003d4)
#define     NCP_NHA_LCM_INT_ACP2500_EN_ACP2500_ALARM_MASK       (0x0000000d)
#define     NCP_NHA_LCM_INT_ACP2500_EN_ACP2500_SERVICE_MASK     (0x00000002)
#define     NCP_NHA_LCM_INT_ACP2500_FRC_ACP2500                 (0x000003d8)
#define     NCP_NHA_LCM_INT_ACP2500_FRC_ACP2500_ALARM_MASK      (0x0000000d)
#define     NCP_NHA_LCM_INT_ACP2500_FRC_ACP2500_SERVICE_MASK    (0x00000002)
#ifdef __cplusplus
}
#endif

#endif /* _NCP_NHA_REG_DEFINES_H_ */
