/*
 *  Copyright (C) 2015 Intel Corporation
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

#ifndef _NCP_ELM_REG_DEFINES_H_
#define _NCP_ELM_REG_DEFINES_H_

#ifdef __cplusplus
extern "C" {
#endif


    /* NODE 0x0 , TARGET 0xffffffff*/


#define     NCP_ELM_APB_BRIDGE_STATUS                           (0x00000000)
#define     NCP_ELM_CONTROL                                     (0x00000004)
#define     NCP_ELM_STATUS                                      (0x00000008)
#define     NCP_ELM_PARAMS                                      (0x0000000c)
#define     NCP_ELM_SYSMEM_MAX_ADDR                             (0x00000010)
#define     NCP_ELM_REENCRYPT_THRESH_ADDR                       (0x00000014)
#define     NCP_ELM_ZEROIZE                                     (0x00000018)
#define     NCP_ELM_SYSMEM_ADDR_MUNGE                           (0x0000001c)
#define     NCP_ELM_SYSMEM_INIT_CACHE_ADDR                      (0x00000040)
#define     NCP_ELM_SYSMEM_INIT_CACHE_COUNT                     (0x00000044)
#define     NCP_ELM_SYSMEM_INIT_DATA                            (0x00000048)
#define     NCP_ELM_SYSMEM_WRITE_LEVEL_CTL                      (0x0000004c)
#define     NCP_ELM_SYSMEM_WRITE_LEVEL_READ_0                   (0x00000050)
#define     NCP_ELM_SYSMEM_WRITE_LEVEL_READ_1                   (0x00000054)
#define     NCP_ELM_CRYPTO_RANGE_START_0                        (0x00000100)
#define     NCP_ELM_CRYPTO_RANGE_SIZE_0                         (0x00000104)
#define     NCP_ELM_CRYPTO_RANGE_START_1                        (0x00000108)
#define     NCP_ELM_CRYPTO_RANGE_SIZE_1                         (0x0000010c)
#define     NCP_ELM_CRYPTO_RANGE_START_2                        (0x00000110)
#define     NCP_ELM_CRYPTO_RANGE_SIZE_2                         (0x00000114)
#define     NCP_ELM_CRYPTO_RANGE_START_3                        (0x00000118)
#define     NCP_ELM_CRYPTO_RANGE_SIZE_3                         (0x0000011c)
#define     NCP_ELM_SM_READ_REQ                                 (0x00000200)
#define     NCP_ELM_SM_READ_RESP_LAST                           (0x00000204)
#define     NCP_ELM_SM_READ_REQ_BEAT                            (0x00000208)
#define     NCP_ELM_SM_READ_RESP_BEAT                           (0x0000020c)
#define     NCP_ELM_SM_WRITE_REQ_BEAT                           (0x00000210)
#define     NCP_ELM_SM_WRITE_DATA_BEAT                          (0x00000214)
#define     NCP_ELM_SM_WRITE_REQ                                (0x00000218)
#define     NCP_ELM_SM_WRITE_DATA_LAST                          (0x0000021c)
#define     NCP_ELM_SM_WRITE_RESP                               (0x00000220)
#define     NCP_ELM_SM_CNT_CTL                                  (0x00000230)
#define     NCP_ELM_AW_SMON00_SBSX_MON                          (0x00000300)
#define     NCP_ELM_AW_SMON01_SBSX_MON                          (0x00000304)
#define     NCP_ELM_AW_SMON02_SBSX_MON                          (0x00000308)
#define     NCP_ELM_AW_SMON03_SBSX_MON                          (0x0000030c)
#define     NCP_ELM_AW_SMON04_SBSX_MON                          (0x00000310)
#define     NCP_ELM_AW_SMON05_SBSX_MON                          (0x00000314)
#define     NCP_ELM_AW_SMON06_SBSX_MON                          (0x00000318)
#define     NCP_ELM_AW_SMON07_SBSX_MON                          (0x0000031c)
#define     NCP_ELM_SBSX_WRT_ADR_FIFO_FIFO_STAT                 (0x00002000)
#define     NCP_ELM_SBSX_WRT_ADR_FIFO_FIFO_WM                   (0x00002004)
#define     NCP_ELM_SBSX_WRT_DATA_FIFO_FIFO_STAT                (0x00002008)
#define     NCP_ELM_SBSX_WRT_DATA_FIFO_FIFO_WM                  (0x0000200c)
#define     NCP_ELM_SBSX_WRT_RESP_FIFO_FIFO_STAT                (0x00002010)
#define     NCP_ELM_SBSX_WRT_RESP_FIFO_FIFO_WM                  (0x00002014)
#define     NCP_ELM_SBSX_READ_ADR_FIFO_FIFO_STAT                (0x00002018)
#define     NCP_ELM_SBSX_READ_ADR_FIFO_FIFO_WM                  (0x0000201c)
#define     NCP_ELM_SBSX_READ_RESP_FIFO_FIFO_STAT               (0x00002020)
#define     NCP_ELM_SBSX_READ_RESP_FIFO_FIFO_WM                 (0x00002024)
#define     NCP_ELM_SM_DEBUG_CTL                                (0x00008000)
#define     NCP_ELM_SM_DEBUG_WRITE_STATUS                       (0x00008004)
#define     NCP_ELM_SM_DEBUG_AW_STATUS                          (0x00008010)
#define     NCP_ELM_SM_DEBUG_W_STATUS                           (0x00008014)
#define     NCP_ELM_SM_DEBUG_B_STATUS                           (0x00008018)
#define     NCP_ELM_SM_DEBUG_B_RAM                              (0x00008020)
#define     NCP_ELM_SM_DEBUG_AW_RAM_0                           (0x00008030)
#define     NCP_ELM_SM_DEBUG_AW_RAM_1                           (0x00008034)
#define     NCP_ELM_SM_DEBUG_AW_RAM_2                           (0x00008038)
#define     NCP_ELM_SM_DEBUG_W_RAM_0                            (0x00008040)
#define     NCP_ELM_SM_DEBUG_W_RAM_1                            (0x00008044)
#define     NCP_ELM_SM_DEBUG_W_RAM_2                            (0x00008048)
#define     NCP_ELM_SM_DEBUG_W_RAM_3                            (0x0000804c)
#define     NCP_ELM_SM_DEBUG_W_RAM_4                            (0x00008050)
#define     NCP_ELM_SM_DEBUG_W_RAM_5                            (0x00008054)
#define     NCP_ELM_SM_DEBUG_W_RAM_6                            (0x00008058)
#define     NCP_ELM_SM_DEBUG_W_RAM_7                            (0x0000805c)
#define     NCP_ELM_SM_DEBUG_W_RAM_8                            (0x00008060)
#define     NCP_ELM_SM_DEBUG_W_RAM_9                            (0x00008064)
#define     NCP_ELM_SM_DEBUG_AW_ID_FIFO_FIFO_STAT               (0x00008070)
#define     NCP_ELM_SM_DEBUG_READ_STATUS                        (0x00008104)
#define     NCP_ELM_SM_DEBUG_AR_STATUS                          (0x00008110)
#define     NCP_ELM_SM_DEBUG_R_STATUS                           (0x00008114)
#define     NCP_ELM_SM_DEBUG_AR_RAM_0                           (0x00008130)
#define     NCP_ELM_SM_DEBUG_AR_RAM_1                           (0x00008134)
#define     NCP_ELM_SM_DEBUG_AR_RAM_2                           (0x00008138)
#define     NCP_ELM_SM_DEBUG_R_RAM_0                            (0x00008140)
#define     NCP_ELM_SM_DEBUG_R_RAM_1                            (0x00008144)
#define     NCP_ELM_SM_DEBUG_R_RAM_2                            (0x00008148)
#define     NCP_ELM_SM_DEBUG_R_RAM_3                            (0x0000814c)
#define     NCP_ELM_SM_DEBUG_R_RAM_4                            (0x00008150)
#define     NCP_ELM_SM_DEBUG_R_RAM_5                            (0x00008154)
#define     NCP_ELM_SM_DEBUG_R_RAM_6                            (0x00008158)
#define     NCP_ELM_SM_DEBUG_R_RAM_7                            (0x0000815c)
#define     NCP_ELM_SM_DEBUG_R_RAM_8                            (0x00008160)
#define     NCP_ELM_CRYPTO_KEY_SEED_0                           (0x00000080)
#define     NCP_ELM_CRYPTO_KEY_SEED_1                           (0x00000084)
#define     NCP_ELM_CRYPTO_KEY_SEED_2                           (0x00000088)
#define     NCP_ELM_CRYPTO_KEY_SEED_3                           (0x0000008c)
#define     NCP_ELM_INTERRUPT_STATUS                            (0x00001000)
#define     NCP_ELM_INTERRUPT_STATUS_ALARM_MASK                 (0x0003fd7f)
#define     NCP_ELM_INTERRUPT_STATUS_SERVICE_MASK               (0x00040280)
#define     NCP_ELM_INTERRUPT_EN                                (0x00001010)
#define     NCP_ELM_INTERRUPT_EN_ALARM_MASK                     (0x0003fd7f)
#define     NCP_ELM_INTERRUPT_EN_SERVICE_MASK                   (0x00040280)
#define     NCP_ELM_INTERRUPT_FRC                               (0x00001020)
#define     NCP_ELM_INTERRUPT_FRC_ALARM_MASK                    (0x0003fd7f)
#define     NCP_ELM_INTERRUPT_FRC_SERVICE_MASK                  (0x00040280)
#ifdef __cplusplus
}
#endif

#endif /* _NCP_ELM_REG_DEFINES_H_ */
