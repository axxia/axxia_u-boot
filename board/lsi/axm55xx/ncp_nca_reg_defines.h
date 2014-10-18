/*
 *  Copyright (C) 2014 LSI (john.jacques@lsi.com)
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

#ifndef _NCP_NCA_REG_DEFINES_H_
#define _NCP_NCA_REG_DEFINES_H_

#ifdef __cplusplus
extern "C" {
#endif

#if 0 /* UBOOT */
#include "ncp_sal_types.h"
#endif


    /* NODE 0x16 , TARGET 0x0*/



#define     NCP_NCA_INT_PARAM_GRP_BASE                          (0x00000010)
#define     NCP_NCA_INT_PARAM_GRP(n)                            (0x00000010 + (4*(n)))
#define     NCP_NCA_INT_PARAM_GRP_COUNT                         (0x00000006)
#define     NCP_NCA_INT_PARAM_GRP_IDX(addr) \
                  (((addr) - NCP_NCA_INT_PARAM_GRP_BASE) / 4)       
#define     NCP_NCA_INT_PARAM_GRP_END                           (0x00000028)
#define     NCP_NCA_INT_PARAM_GRP_RANGE(addr) \
               (((addr) >= NCP_NCA_INT_PARAM_GRP_BASE) && \
                    ((addr) < NCP_NCA_INT_PARAM_GRP_END))


#define     NCP_NCA_INT_PARAM_GRP_55XX_BASE                     (0x00010300)
#define     NCP_NCA_INT_PARAM_GRP_55XX(n)                       (0x00010300 + (4*(n)))
#define     NCP_NCA_INT_PARAM_GRP_55XX_COUNT                    (0x00000010)
#define     NCP_NCA_INT_PARAM_GRP_55XX_IDX(addr) \
             (((addr) - NCP_NCA_INT_PARAM_GRP_55XX_BASE) / 4)  
#define     NCP_NCA_INT_PARAM_GRP_55XX_END                      (0x00010340)
#define     NCP_NCA_INT_PARAM_GRP_55XX_RANGE(addr) \
          (((addr) >= NCP_NCA_INT_PARAM_GRP_55XX_BASE) && \
          ((addr) < NCP_NCA_INT_PARAM_GRP_55XX_END))

#define     NCP_NCA_CONFIG_INIT                                 (0x00000028)
#define     NCP_NCA_CONFIG_INIT_32XX                            (0x00000028)
#define     NCP_NCA_CONFIG_INIT_25XX                            (0x00000028)
#define     NCP_NCA_CONFIG_INIT_55XX                            (0x00010010)
#define     NCP_NCA_PCQ_KICKSTART                               (0x0000002c)
#define     NCP_NCA_PCQ_KICKSTART_25XX                          (0x0000002c)
#define     NCP_NCA_PCQ_KICKSTART_55XX                          (0x00010018)
#define     NCP_NCA_PGIT_LOAD_GRP_INDEXES_34XX                  (0x00000030)
#define     NCP_NCA_HW_POKE_AND_TIMER_ENABLE                    (0x00000034)
#define     NCP_NCA_HW_POKE_AND_TIMER_ENABLE_55XX               (0x00010030)
#define     NCP_NCA_HW_UPLOAD_POKE_FLAGS                        (0x00000038)
#define     NCP_NCA_HW_UPLOAD_POKE_FLAGS_55XX                   (0x00010038)

#define     NCP_NCA_PGIT_GRP_LOAD_TIMER_BASE                    (0x00000040)
#define     NCP_NCA_PGIT_GRP_LOAD_TIMER(n)                      (0x00000040 + (4*(n)))
#define     NCP_NCA_PGIT_GRP_LOAD_TIMER_COUNT                   (0x00000006)
#define     NCP_NCA_PGIT_GRP_LOAD_TIMER_IDX(addr) \
            (((addr) - NCP_NCA_PGIT_GRP_LOAD_TIMER_BASE) / 4) 
#define     NCP_NCA_PGIT_GRP_LOAD_TIMER_END                     (0x00000058)
#define     NCP_NCA_PGIT_GRP_LOAD_TIMER_RANGE(addr) \
         (((addr) >= NCP_NCA_PGIT_GRP_LOAD_TIMER_BASE) && \
         ((addr) < NCP_NCA_PGIT_GRP_LOAD_TIMER_END))


#define     NCP_NCA_PGIT_GRP_LOAD_TIMER_55XX_BASE               (0x00010080)
#define     NCP_NCA_PGIT_GRP_LOAD_TIMER_55XX(n)                 (0x00010080 + (4*(n)))
#define     NCP_NCA_PGIT_GRP_LOAD_TIMER_55XX_COUNT              (0x00000010)
#define     NCP_NCA_PGIT_GRP_LOAD_TIMER_55XX_IDX(addr) \
       (((addr) - NCP_NCA_PGIT_GRP_LOAD_TIMER_55XX_BASE) / 4)
#define     NCP_NCA_PGIT_GRP_LOAD_TIMER_55XX_END                (0x000100c0)
#define     NCP_NCA_PGIT_GRP_LOAD_TIMER_55XX_RANGE(addr) \
    (((addr) >= NCP_NCA_PGIT_GRP_LOAD_TIMER_55XX_BASE) && \
    ((addr) < NCP_NCA_PGIT_GRP_LOAD_TIMER_55XX_END))


#define     NCP_NCA_PGIT_GRP_UPLOAD_TIMER_BASE                  (0x00000058)
#define     NCP_NCA_PGIT_GRP_UPLOAD_TIMER(n)                    (0x00000058 + (4*(n)))
#define     NCP_NCA_PGIT_GRP_UPLOAD_TIMER_COUNT                 (0x00000006)
#define     NCP_NCA_PGIT_GRP_UPLOAD_TIMER_IDX(addr) \
          (((addr) - NCP_NCA_PGIT_GRP_UPLOAD_TIMER_BASE) / 4)
#define     NCP_NCA_PGIT_GRP_UPLOAD_TIMER_END                   (0x00000070)
#define     NCP_NCA_PGIT_GRP_UPLOAD_TIMER_RANGE(addr) \
       (((addr) >= NCP_NCA_PGIT_GRP_UPLOAD_TIMER_BASE) && \
       ((addr) < NCP_NCA_PGIT_GRP_UPLOAD_TIMER_END))


#define     NCP_NCA_PGIT_GRP_UPLOAD_TIMER_55XX_BASE             (0x00010100)
#define     NCP_NCA_PGIT_GRP_UPLOAD_TIMER_55XX(n)               (0x00010100 + (4*(n)))
#define     NCP_NCA_PGIT_GRP_UPLOAD_TIMER_55XX_COUNT            (0x00000010)
#define     NCP_NCA_PGIT_GRP_UPLOAD_TIMER_55XX_IDX(addr) \
     (((addr) - NCP_NCA_PGIT_GRP_UPLOAD_TIMER_55XX_BASE) / 4)
#define     NCP_NCA_PGIT_GRP_UPLOAD_TIMER_55XX_END              (0x00010140)
#define     NCP_NCA_PGIT_GRP_UPLOAD_TIMER_55XX_RANGE(addr) \
  (((addr) >= NCP_NCA_PGIT_GRP_UPLOAD_TIMER_55XX_BASE) && \
  ((addr) < NCP_NCA_PGIT_GRP_UPLOAD_TIMER_55XX_END))


#define     NCP_NCA_DELAY_GRP_UPLOAD_TIMER_BASE                 (0x00000070)
#define     NCP_NCA_DELAY_GRP_UPLOAD_TIMER(n)                   (0x00000070 + (4*(n)))
#define     NCP_NCA_DELAY_GRP_UPLOAD_TIMER_COUNT                (0x00000006)
#define     NCP_NCA_DELAY_GRP_UPLOAD_TIMER_IDX(addr) \
         (((addr) - NCP_NCA_DELAY_GRP_UPLOAD_TIMER_BASE) / 4)
#define     NCP_NCA_DELAY_GRP_UPLOAD_TIMER_END                  (0x00000088)
#define     NCP_NCA_DELAY_GRP_UPLOAD_TIMER_RANGE(addr) \
      (((addr) >= NCP_NCA_DELAY_GRP_UPLOAD_TIMER_BASE) && \
      ((addr) < NCP_NCA_DELAY_GRP_UPLOAD_TIMER_END))


#define     NCP_NCA_DELAY_GRP_UPLOAD_TIMER_55XX_BASE            (0x00010180)
#define     NCP_NCA_DELAY_GRP_UPLOAD_TIMER_55XX(n)              (0x00010180 + (4*(n)))
#define     NCP_NCA_DELAY_GRP_UPLOAD_TIMER_55XX_COUNT           (0x00000010)
#define     NCP_NCA_DELAY_GRP_UPLOAD_TIMER_55XX_IDX(addr) \
    (((addr) - NCP_NCA_DELAY_GRP_UPLOAD_TIMER_55XX_BASE) / 4)
#define     NCP_NCA_DELAY_GRP_UPLOAD_TIMER_55XX_END             (0x000101c0)
#define     NCP_NCA_DELAY_GRP_UPLOAD_TIMER_55XX_RANGE(addr) \
 (((addr) >= NCP_NCA_DELAY_GRP_UPLOAD_TIMER_55XX_BASE) && \
  ((addr) < NCP_NCA_DELAY_GRP_UPLOAD_TIMER_55XX_END))

#define     NCP_NCA_PAR_ERROR_STATUS0_34XX                      (0x00000088)
#define     NCP_NCA_PAR_ERROR_STATUS1_34XX                      (0x0000008c)
#define     NCP_NCA_CFG_RING_PARITY                             (0x00000090)
#define     NCP_NCA_CFG_RING_DBG_STAT0                          (0x00000094)
#define     NCP_NCA_CFG_RING_DBG_STAT1                          (0x00000098)
#define     NCP_NCA_CNAL_IF_STATUS                              (0x0000009c)
#define     NCP_NCA_CNAL_CONTROL                                (0x000000a0)
#define     NCP_NCA_NUM_OF_CFG_NODES                            (0x000000e0)
#define     NCP_NCA_NUM_OF_CFG_NODES_32XX                       (0x000000e0)
#define     NCP_NCA_CFG_RING_ERROR_STAT_R0                      (0x000000e4)
#define     NCP_NCA_CFG_RING_ERROR_STAT_R0_25XX                 (0x000000e4)
#define     NCP_NCA_CFG_RING_ERROR_STAT_R1                      (0x000000e8)
#define     NCP_NCA_CFG_RING_ERROR_STAT_R1_25XX                 (0x000000e8)
#define     NCP_NCA_CFG_RING_NODE_STATUS                        (0x000000ec)
#define     NCP_NCA_CFG_PIO_CDR0                                (0x000000f0)
#define     NCP_NCA_CFG_PIO_CDR1                                (0x000000f4)
#define     NCP_NCA_CFG_PIO_CDR2                                (0x000000f8)
#define     NCP_NCA_CFG_PIO_CDR2_55XX                           (0x000000f8)
#define     NCP_NCA_CFG_RING_ACK_TIMER_CNT                      (0x000000fc)
#define     NCP_NCA_IPCQ_ALMOST_FULL_VALUE                      (0x00000100)

#define     NCP_NCA_CDAR_MEMORY_BASE                            (0x00001000)
#define     NCP_NCA_CDAR_MEMORY(n)                              (0x00001000 + (4*(n)))
#define     NCP_NCA_CDAR_MEMORY_COUNT                           (0x00000080)
#define     NCP_NCA_CDAR_MEMORY_IDX(addr) \
                    (((addr) - NCP_NCA_CDAR_MEMORY_BASE) / 4)         
#define     NCP_NCA_CDAR_MEMORY_END                             (0x00001200)
#define     NCP_NCA_CDAR_MEMORY_RANGE(addr) \
                 (((addr) >= NCP_NCA_CDAR_MEMORY_BASE) && \
                        ((addr) < NCP_NCA_CDAR_MEMORY_END))

#define     NCP_NCA_CDAR_WORD_129                               (0x00001200)

#define     NCP_NCA_TFC_COUNT_R_34XX_BASE                       (0x00001240)
#define     NCP_NCA_TFC_COUNT_R_34XX(n)                         (0x00001240 + (4*(n)))
#define     NCP_NCA_TFC_COUNT_R_34XX_COUNT                      (0x0000000c)
#define     NCP_NCA_TFC_COUNT_R_34XX_IDX(addr) \
               (((addr) - NCP_NCA_TFC_COUNT_R_34XX_BASE) / 4)    
#define     NCP_NCA_TFC_COUNT_R_34XX_END                        (0x00001270)
#define     NCP_NCA_TFC_COUNT_R_34XX_RANGE(addr) \
            (((addr) >= NCP_NCA_TFC_COUNT_R_34XX_BASE) && \
              ((addr) < NCP_NCA_TFC_COUNT_R_34XX_END))

#define     NCP_NCA_RBP_ITASK_BP_EN_34XX                        (0x000012e0)
#define     NCP_NCA_RBP_ITASK_BP_INCLD_BSIZ_34XX                (0x000012e4)
#define     NCP_NCA_AW_SMON00_NCA_TASK_SMON                     (0x00001300)
#define     NCP_NCA_AW_SMON00_NCA_TASK_SMON_25XX                (0x00001300)
#define     NCP_NCA_AW_SMON00_NCA_TASK_SMON_55XX                (0x00013700)
#define     NCP_NCA_AW_SMON01_NCA_TASK_SMON                     (0x00001304)
#define     NCP_NCA_AW_SMON01_NCA_TASK_SMON_55XX                (0x00013704)
#define     NCP_NCA_AW_SMON02_NCA_TASK_SMON                     (0x00001308)
#define     NCP_NCA_AW_SMON02_NCA_TASK_SMON_55XX                (0x00013708)
#define     NCP_NCA_AW_SMON03_NCA_TASK_SMON                     (0x0000130c)
#define     NCP_NCA_AW_SMON03_NCA_TASK_SMON_55XX                (0x0001370c)
#define     NCP_NCA_AW_SMON04_NCA_TASK_SMON                     (0x00001310)
#define     NCP_NCA_AW_SMON04_NCA_TASK_SMON_55XX                (0x00013710)
#define     NCP_NCA_AW_SMON05_NCA_TASK_SMON                     (0x00001314)
#define     NCP_NCA_AW_SMON05_NCA_TASK_SMON_55XX                (0x00013714)
#define     NCP_NCA_AW_SMON06_NCA_TASK_SMON                     (0x00001318)
#define     NCP_NCA_AW_SMON06_NCA_TASK_SMON_55XX                (0x00013718)
#define     NCP_NCA_AW_SMON07_NCA_TASK_SMON                     (0x0000131c)
#define     NCP_NCA_AW_SMON07_NCA_TASK_SMON_55XX                (0x0001371c)
#define     NCP_NCA_ITASK_DROP_CNT_IPCQ_ER                      (0x00001320)
#define     NCP_NCA_ITASK_DROP_CNT_IPCQ_ER_55XX                 (0x00013720)
#define     NCP_NCA_ITASK_DROP_CNT_NO_BUF                       (0x00001324)
#define     NCP_NCA_ITASK_DROP_CNT_NO_BUF_55XX                  (0x00013724)
#define     NCP_NCA_OTASK_LENGTH_COMPARE                        (0x00001328)
#define     NCP_NCA_OTASK_LENGTH_COMPARE_55XX                   (0x00013728)
#define     NCP_NCA_OTASK_LENGTH_CAPTURE                        (0x0000132c)
#define     NCP_NCA_OTASK_LENGTH_CAPTURE_55XX                   (0x0001372c)
#define     NCP_NCA_RBP_ITASK_BP_34XX                           (0x00001330)
#define     NCP_NCA_OTASK_OPCQ_BP                               (0x00001334)
#define     NCP_NCA_OTASK_OPCQ_BP_55XX                          (0x00013734)
#define     NCP_NCA_OTBP_BAR_UPPER_34XX                         (0x00001340)
#define     NCP_NCA_OTBP_BAR_LOWER_34XX                         (0x00001344)
#define     NCP_NCA_PGIT_SOFTWARE_LOAD_POKE_REG                 (0x00001348)
#define     NCP_NCA_PGIT_SOFTWARE_LOAD_POKE_REG_55XX            (0x000137c0)
#define     NCP_NCA_HW_LOAD_POKE_FLAGS                          (0x0000134c)
#define     NCP_NCA_HW_LOAD_POKE_FLAGS_55XX                     (0x00010034)

#define     NCP_NCA_DELAY_GRP_LOAD_TIMER_BASE                   (0x00001350)
#define     NCP_NCA_DELAY_GRP_LOAD_TIMER(n)                     (0x00001350 + (4*(n)))
#define     NCP_NCA_DELAY_GRP_LOAD_TIMER_COUNT                  (0x00000006)
#define     NCP_NCA_DELAY_GRP_LOAD_TIMER_IDX(addr) \
           (((addr) - NCP_NCA_DELAY_GRP_LOAD_TIMER_BASE) / 4)
#define     NCP_NCA_DELAY_GRP_LOAD_TIMER_END                    (0x00001368)
#define     NCP_NCA_DELAY_GRP_LOAD_TIMER_RANGE(addr) \
        (((addr) >= NCP_NCA_DELAY_GRP_LOAD_TIMER_BASE) && \
        ((addr) < NCP_NCA_DELAY_GRP_LOAD_TIMER_END))


#define     NCP_NCA_DELAY_GRP_LOAD_TIMER_55XX_BASE              (0x00013800)
#define     NCP_NCA_DELAY_GRP_LOAD_TIMER_55XX(n)                (0x00013800 + (4*(n)))
#define     NCP_NCA_DELAY_GRP_LOAD_TIMER_55XX_COUNT             (0x00000010)
#define     NCP_NCA_DELAY_GRP_LOAD_TIMER_55XX_IDX(addr) \
      (((addr) - NCP_NCA_DELAY_GRP_LOAD_TIMER_55XX_BASE) / 4)
#define     NCP_NCA_DELAY_GRP_LOAD_TIMER_55XX_END               (0x00013840)
#define     NCP_NCA_DELAY_GRP_LOAD_TIMER_55XX_RANGE(addr) \
   (((addr) >= NCP_NCA_DELAY_GRP_LOAD_TIMER_55XX_BASE) && \
   ((addr) < NCP_NCA_DELAY_GRP_LOAD_TIMER_55XX_END))


#define     NCP_NCA_SWPOKE_DELAY_GRP_LOAD_TIMER_BASE            (0x00001370)
#define     NCP_NCA_SWPOKE_DELAY_GRP_LOAD_TIMER(n)              (0x00001370 + (4*(n)))
#define     NCP_NCA_SWPOKE_DELAY_GRP_LOAD_TIMER_COUNT           (0x00000006)
#define     NCP_NCA_SWPOKE_DELAY_GRP_LOAD_TIMER_IDX(addr) \
    (((addr) - NCP_NCA_SWPOKE_DELAY_GRP_LOAD_TIMER_BASE) / 4)
#define     NCP_NCA_SWPOKE_DELAY_GRP_LOAD_TIMER_END             (0x00001388)
#define     NCP_NCA_SWPOKE_DELAY_GRP_LOAD_TIMER_RANGE(addr) \
 (((addr) >= NCP_NCA_SWPOKE_DELAY_GRP_LOAD_TIMER_BASE) && \
  ((addr) < NCP_NCA_SWPOKE_DELAY_GRP_LOAD_TIMER_END))


#define     NCP_NCA_SWPOKE_DELAY_GRP_LOAD_TIMER_55XX_BASE       (0x00013880)
#define     NCP_NCA_SWPOKE_DELAY_GRP_LOAD_TIMER_55XX(n)         (0x00013880 + (4*(n)))
#define     NCP_NCA_SWPOKE_DELAY_GRP_LOAD_TIMER_55XX_COUNT      (0x00000010)
#define     NCP_NCA_SWPOKE_DELAY_GRP_LOAD_TIMER_55XX_IDX(addr) \
  (((addr) - NCP_NCA_SWPOKE_DELAY_GRP_LOAD_TIMER_55XX_BASE) / 4)
#define     NCP_NCA_SWPOKE_DELAY_GRP_LOAD_TIMER_55XX_END        (0x000138c0)
#define     NCP_NCA_SWPOKE_DELAY_GRP_LOAD_TIMER_55XX_RANGE(addr) \
 (((addr) >= NCP_NCA_SWPOKE_DELAY_GRP_LOAD_TIMER_55XX_BASE) && \
  ((addr) < NCP_NCA_SWPOKE_DELAY_GRP_LOAD_TIMER_55XX_END))


#define     NCP_NCA_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_BASE         (0x00001390)
#define     NCP_NCA_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER(n)           (0x00001390 + (4*(n)))
#define     NCP_NCA_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_COUNT        (0x00000006)
#define     NCP_NCA_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_IDX(addr) \
  (((addr) - NCP_NCA_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_BASE) / 4)
#define     NCP_NCA_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_END          (0x000013a8)
#define     NCP_NCA_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_RANGE(addr) \
 (((addr) >= NCP_NCA_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_BASE) && \
  ((addr) < NCP_NCA_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_END))


#define     NCP_NCA_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_55XX_BASE    (0x00013900)
#define     NCP_NCA_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_55XX(n)      (0x00013900 + (4*(n)))
#define     NCP_NCA_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_55XX_COUNT   (0x00000010)
#define     NCP_NCA_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_55XX_IDX(addr) \
  (((addr) - NCP_NCA_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_55XX_BASE) / 4)
#define     NCP_NCA_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_55XX_END     (0x00013940)
#define     NCP_NCA_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_55XX_RANGE(addr) \
 (((addr) >= NCP_NCA_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_55XX_BASE) && \
  ((addr) < NCP_NCA_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_55XX_END))


#define     NCP_NCA_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_BASE        (0x000013b0)
#define     NCP_NCA_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR(n)          (0x000013b0 + (4*(n)))
#define     NCP_NCA_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_COUNT       (0x00000006)
#define     NCP_NCA_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_IDX(addr) \
  (((addr) - NCP_NCA_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_BASE) / 4)
#define     NCP_NCA_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_END         (0x000013c8)
#define     NCP_NCA_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_RANGE(addr) \
 (((addr) >= NCP_NCA_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_BASE) && \
  ((addr) < NCP_NCA_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_END))


#define     NCP_NCA_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_55XX_BASE   (0x00013980)
#define     NCP_NCA_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_55XX(n)     (0x00013980 + (4*(n)))
#define     NCP_NCA_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_55XX_COUNT  (0x00000010)
#define     NCP_NCA_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_55XX_IDX(addr) \
  (((addr) - NCP_NCA_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_55XX_BASE) / 4)
#define     NCP_NCA_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_55XX_END    (0x000139c0)
#define     NCP_NCA_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_55XX_RANGE(addr) \
 (((addr) >= NCP_NCA_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_55XX_BASE) && \
  ((addr) < NCP_NCA_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_55XX_END))


#define     NCP_NCA_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_BASE      (0x000013d0)
#define     NCP_NCA_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR(n)        (0x000013d0 + (4*(n)))
#define     NCP_NCA_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_COUNT     (0x00000006)
#define     NCP_NCA_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_IDX(addr) \
  (((addr) - NCP_NCA_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_BASE) / 4)
#define     NCP_NCA_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_END       (0x000013e8)
#define     NCP_NCA_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_RANGE(addr) \
 (((addr) >= NCP_NCA_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_BASE) && \
  ((addr) < NCP_NCA_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_END))


#define     NCP_NCA_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_55XX_BASE  (0x00013a00)
#define     NCP_NCA_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_55XX(n)   (0x00013a00 + (4*(n)))
#define     NCP_NCA_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_55XX_COUNT  (0x00000010)
#define     NCP_NCA_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_55XX_IDX(addr) \
  (((addr) - NCP_NCA_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_55XX_BASE) / 4)
#define     NCP_NCA_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_55XX_END  (0x00013a40)
#define     NCP_NCA_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_55XX_RANGE(addr) \
 (((addr) >= NCP_NCA_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_55XX_BASE) && \
  ((addr) < NCP_NCA_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_55XX_END))

#define     NCP_NCA_FIFO_FULL_EMPTY_STATUS_REG0_34XX            (0x00001400)
#define     NCP_NCA_FIFO_FULL_EMPTY_STATUS_REG1_34XX            (0x00001404)
#define     NCP_NCA_FIFO_FULL_EMPTY_STATUS_REG2_34XX            (0x00001408)
#define     NCP_NCA_FIFO_FULL_EMPTY_STATUS_REG3_34XX            (0x0000140c)
#define     NCP_NCA_FIFO_FULL_EMPTY_STATUS_REG4_34XX            (0x00001410)
#define     NCP_NCA_FIFO_FULL_EMPTY_STATUS_REG5_34XX            (0x00001414)
#define     NCP_NCA_FIFO_FULL_EMPTY_STATUS_REG6_34XX            (0x00001418)
#define     NCP_NCA_TFC_UNORDERED_MODE_34XX                     (0x00001500)
#define     NCP_NCA_OVERALL_INT_STAT_34XX                       (0x0000f000)
#define     NCP_NCA_MPIC_CTRL                                   (0x0000f004)
#define     NCP_NCA_MPIC_CTRL_55XX                              (0x0001f000)
#define     NCP_NCA_INT_STATUS_DATA_R0_34XX                     (0x0000f050)
#define     NCP_NCA_INT_STATUS_DATA_R1_34XX                     (0x0000f054)
#define     NCP_NCA_INT_STATUS_DATA_R2_34XX                     (0x0000f058)
#define     NCP_NCA_INT_STATUS_DATA_R3_34XX                     (0x0000f05c)
#define     NCP_NCA_INT_STATUS_DATA_R4_34XX                     (0x0000f060)
#define     NCP_NCA_INT_STATUS_DATA_R5_34XX                     (0x0000f064)
#define     NCP_NCA_INT_STATUS_DATA_R6_34XX                     (0x0000f068)
#define     NCP_NCA_INT_STATUS_DATA_R7_34XX                     (0x0000f06c)
#define     NCP_NCA_INT_STATUS_DATA_R8_34XX                     (0x0000f070)
#define     NCP_NCA_INT_STATUS_DATA_R9_34XX                     (0x0000f074)
#define     NCP_NCA_INT_STATUS_DATA_R10_34XX                    (0x0000f078)
#define     NCP_NCA_INT_STATUS_DATA_R11_34XX                    (0x0000f07c)

#define     NCP_NCA_PIO_LOCK_BASE                               (0x0000ff80)
#define     NCP_NCA_PIO_LOCK(n)                                 (0x0000ff80 + (4*(n)))
#define     NCP_NCA_PIO_LOCK_COUNT                              (0x00000020)
#define     NCP_NCA_PIO_LOCK_IDX(addr) \
                       (((addr) - NCP_NCA_PIO_LOCK_BASE) / 4)            
#define     NCP_NCA_PIO_LOCK_END                                (0x00010000)
#define     NCP_NCA_PIO_LOCK_RANGE(addr) \
                    (((addr) >= NCP_NCA_PIO_LOCK_BASE) && \
                              ((addr) < NCP_NCA_PIO_LOCK_END))

#define     NCP_NCA_SMON_MUXA_MUXB_SEL_25XX                     (0x00001338)
#define     NCP_NCA_SMON_MUXA_MUXB_SEL_55XX                     (0x00013738)
#define     NCP_NCA_MAX_OUTSTANDING_AXIM_OPS_25XX               (0x00001504)
#define     NCP_NCA_AXIM_OP_COUNTER_CTL_25XX                    (0x00001510)
#define     NCP_NCA_CLK_COUNTER_LS_25XX                         (0x00001514)
#define     NCP_NCA_CLK_COUNTER_LS_55XX                         (0x00018814)
#define     NCP_NCA_AXIM_OP_COUNTER0_LS_25XX                    (0x00001518)
#define     NCP_NCA_AXIM_OP_COUNTER1_LS_25XX                    (0x0000151c)
#define     NCP_NCA_AXIM_OP_COUNTER2_LS_25XX                    (0x00001520)
#define     NCP_NCA_AXIM_OP_COUNTER3_LS_25XX                    (0x00001524)
#define     NCP_NCA_AXIM_OUTSTANDING_ROP_COUNT0_25XX            (0x00001528)
#define     NCP_NCA_AXIM_OUTSTANDING_ROP_COUNT1_25XX            (0x0000152c)
#define     NCP_NCA_AXIM_OUTSTANDING_ROP_COUNT2_25XX            (0x00001530)
#define     NCP_NCA_AXIM_OUTSTANDING_RDATA_COUNT0_25XX          (0x00001534)
#define     NCP_NCA_AXIM_OUTSTANDING_RDATA_COUNT1_25XX          (0x00001538)
#define     NCP_NCA_AXIM_OUTSTANDING_WOP_COUNT0_25XX            (0x0000153c)
#define     NCP_NCA_AXIM_OUTSTANDING_WOP_COUNT1_25XX            (0x00001540)
#define     NCP_NCA_CLK_COUNTER_MS_25XX                         (0x00001544)
#define     NCP_NCA_CLK_COUNTER_MS_55XX                         (0x00018840)
#define     NCP_NCA_AXIM_OP_COUNTER0_MS_25XX                    (0x00001548)
#define     NCP_NCA_AXIM_OP_COUNTER1_MS_25XX                    (0x0000154c)
#define     NCP_NCA_AXIM_OP_COUNTER2_MS_25XX                    (0x00001550)
#define     NCP_NCA_AXIM_OP_COUNTER3_MS_25XX                    (0x00001554)
#define     NCP_NCA_AXIM_VALID_READY_25XX                       (0x00001558)
#define     NCP_NCA_CONFIG_INIT_WOCLR_25XX                      (0x0000f200)
#define     NCP_NCA_CONFIG_INIT_WOCLR_55XX                      (0x0001f200)
#define     NCP_NCA_HW_POKE_AND_TIMER_ENABLE_WOCLR_25XX         (0x0000f20c)
#define     NCP_NCA_HW_POKE_AND_TIMER_ENABLE_WOCLR_55XX         (0x0001f210)
#define     NCP_NCA_MPIC_CTRL_WOCLR_25XX                        (0x0000f230)
#define     NCP_NCA_MPIC_CTRL_WOCLR_55XX                        (0x0001f238)
#define     NCP_NCA_CONFIG_INIT_WOSET_25XX                      (0x0000f300)
#define     NCP_NCA_CONFIG_INIT_WOSET_55XX                      (0x0001f300)
#define     NCP_NCA_PGIT_LOAD_GRP_INDEXES_WOSET_25XX            (0x0000f308)
#define     NCP_NCA_HW_POKE_AND_TIMER_ENABLE_WOSET_25XX         (0x0000f30c)
#define     NCP_NCA_HW_POKE_AND_TIMER_ENABLE_WOSET_55XX         (0x0001f310)
#define     NCP_NCA_PGIT_SOFTWARE_LOAD_POKE_REG_WOSET_25XX      (0x0000f310)
#define     NCP_NCA_PGIT_SOFTWARE_LOAD_POKE_REG_WOSET_55XX      (0x0001f330)
#define     NCP_NCA_MPIC_CTRL_WOSET_25XX                        (0x0000f330)
#define     NCP_NCA_MPIC_CTRL_WOSET_55XX                        (0x0001f338)
#define     NCP_NCA_PIO_LOCK_COWN_25XX                          (0x0000ff00)
#define     NCP_NCA_IDLE_STATUS_55XX                            (0x00010014)
#define     NCP_NCA_MEM_INIT_DONE_55XX                          (0x0001001c)
#define     NCP_NCA_NPGIT_LOAD_CPU_GRP_INDEXES_55XX             (0x00010020)
#define     NCP_NCA_NPGIT_INIT_GRP_INDEXES_55XX                 (0x00010028)
#define     NCP_NCA_GRP_LOAD_POKE_ENABLE_55XX                   (0x00010040)
#define     NCP_NCA_GRP_LOAD_TIMER_ENABLE_55XX                  (0x00010044)
#define     NCP_NCA_GRP_UPLOAD_POKE_ENABLE_55XX                 (0x00010048)
#define     NCP_NCA_GRP_UPLOAD_TIMER_ENABLE_55XX                (0x0001004c)
#define     NCP_NCA_MME_INPUT_FIFO_HWM_55XX                     (0x00010070)
#define     NCP_NCA_MME_CTL_55XX                                (0x00010074)
#define     NCP_NCA_CFG_PIO_CDR3_55XX                           (0x00010270)
#define     NCP_NCA_SYS_MEM_TTYPE_55XX                          (0x00010280)
#define     NCP_NCA_AXI_MEM_TTYPE_55XX                          (0x00010284)
#define     NCP_NCA_MME_BUF_FETCH_EN_SIZE0_55XX                 (0x00010290)
#define     NCP_NCA_MME_BUF_FETCH_EN_SIZE1_55XX                 (0x00010294)
#define     NCP_NCA_MME_BUF_FETCH_EN_SIZE2_55XX                 (0x00010298)
#define     NCP_NCA_MME_BUF_FETCH_EN_SIZE3_55XX                 (0x0001029c)
#define     NCP_NCA_OTBP_VI_UPPER_55XX                          (0x00013780)
#define     NCP_NCA_OTBP_VI_LOWER_55XX                          (0x00013784)
#define     NCP_NCA_OTA_CPU_VPP_XLAT_TABLE_IN_FIFO_STAT_55XX    (0x00014200)
#define     NCP_NCA_OTA_CPU_VPP_XLAT_TABLE_ECC_TEST_55XX        (0x00014204)
#define     NCP_NCA_ITA_CPU_VPP_XLAT_TABLE_IN_FIFO_STAT_55XX    (0x00014a00)
#define     NCP_NCA_ITA_CPU_VPP_XLAT_TABLE_ECC_TEST_55XX        (0x00014a04)
#define     NCP_NCA_ITA_VPP_CPU_XLAT_TABLE_IN_FIFO_STAT_55XX    (0x00015200)
#define     NCP_NCA_ITA_VPP_CPU_XLAT_TABLE_ECC_TEST_55XX        (0x00015204)

#define     NCP_NCA_OPCQ_ENTRY_PREFETCH_BUF_FIFO_STATUS_FIFO_STAT_55XX_BASE  (0x00017000)
#define     NCP_NCA_OPCQ_ENTRY_PREFETCH_BUF_FIFO_STATUS_FIFO_STAT_55XX(n)  (0x00017000 + (4*(n)))
#define     NCP_NCA_OPCQ_ENTRY_PREFETCH_BUF_FIFO_STATUS_FIFO_STAT_55XX_COUNT  (0x00000020)
#define     NCP_NCA_OPCQ_ENTRY_PREFETCH_BUF_FIFO_STATUS_FIFO_STAT_55XX_IDX(addr) \
  (((addr) - NCP_NCA_OPCQ_ENTRY_PREFETCH_BUF_FIFO_STATUS_FIFO_STAT_55XX_BASE) / 4)
#define     NCP_NCA_OPCQ_ENTRY_PREFETCH_BUF_FIFO_STATUS_FIFO_STAT_55XX_END  (0x00017080)
#define     NCP_NCA_OPCQ_ENTRY_PREFETCH_BUF_FIFO_STATUS_FIFO_STAT_55XX_RANGE(addr) \
 (((addr) >= NCP_NCA_OPCQ_ENTRY_PREFETCH_BUF_FIFO_STATUS_FIFO_STAT_55XX_BASE) && \
  ((addr) < NCP_NCA_OPCQ_ENTRY_PREFETCH_BUF_FIFO_STATUS_FIFO_STAT_55XX_END))


#define     NCP_NCA_REC_VIRT_PIPE_CTRL_TABLE_55XX_BASE          (0x00017200)
#define     NCP_NCA_REC_VIRT_PIPE_CTRL_TABLE_55XX(n)            (0x00017200 + (4*(n)))
#define     NCP_NCA_REC_VIRT_PIPE_CTRL_TABLE_55XX_COUNT         (0x00000040)
#define     NCP_NCA_REC_VIRT_PIPE_CTRL_TABLE_55XX_IDX(addr) \
  (((addr) - NCP_NCA_REC_VIRT_PIPE_CTRL_TABLE_55XX_BASE) / 4)
#define     NCP_NCA_REC_VIRT_PIPE_CTRL_TABLE_55XX_END           (0x00017300)
#define     NCP_NCA_REC_VIRT_PIPE_CTRL_TABLE_55XX_RANGE(addr) \
 (((addr) >= NCP_NCA_REC_VIRT_PIPE_CTRL_TABLE_55XX_BASE) && \
  ((addr) < NCP_NCA_REC_VIRT_PIPE_CTRL_TABLE_55XX_END))

#define     NCP_NCA_REC_VIRT_PIPE_CTRL_TABLE_ECC_TEST_55XX      (0x00017300)
#define     NCP_NCA_OTA_FIFO_FULL_EMPTY_STATUS_REG0_55XX        (0x00018000)
#define     NCP_NCA_OTA_FIFO_FULL_EMPTY_STATUS_REG1_55XX        (0x00018004)
#define     NCP_NCA_OTA_FIFO_FULL_EMPTY_STATUS_REG2_55XX        (0x00018008)
#define     NCP_NCA_OTA_FIFO_FULL_EMPTY_STATUS_REG3_55XX        (0x0001800c)
#define     NCP_NCA_OTA_FIFO_FULL_EMPTY_STATUS_REG4_55XX        (0x00018010)
#define     NCP_NCA_ITA_FIFO_FULL_EMPTY_STATUS_REG0_55XX        (0x00018014)
#define     NCP_NCA_ITA_FIFO_FULL_EMPTY_STATUS_REG1_55XX        (0x00018018)
#define     NCP_NCA_ITA_FIFO_FULL_EMPTY_STATUS_REG2_55XX        (0x0001801c)
#define     NCP_NCA_NPGIT_FIFO_FULL_EMPTY_STATUS_REG0_55XX      (0x00018020)
#define     NCP_NCA_NPGIT_FIFO_FULL_EMPTY_STATUS_REG1_55XX      (0x00018024)
#define     NCP_NCA_NPGIT_FIFO_FULL_EMPTY_STATUS_REG2_55XX      (0x00018028)
#define     NCP_NCA_MPB_INPUT_FIFO_FULL_EMPTY_STATUS_55XX       (0x0001802c)
#define     NCP_NCA_CMN_FIFO_FULL_EMPTY_STATUS_55XX             (0x00018030)
#define     NCP_NCA_OTA_FIFO_OVERFLOW_UNDERFLOW_STATUS_REG0_55XX  (0x00018100)
#define     NCP_NCA_OTA_FIFO_OVERFLOW_UNDERFLOW_STATUS_REG1_55XX  (0x00018104)
#define     NCP_NCA_OTA_FIFO_OVERFLOW_UNDERFLOW_STATUS_REG2_55XX  (0x00018108)
#define     NCP_NCA_OTA_FIFO_OVERFLOW_UNDERFLOW_STATUS_REG3_55XX  (0x0001810c)
#define     NCP_NCA_OTA_FIFO_OVERFLOW_UNDERFLOW_STATUS_REG4_55XX  (0x00018110)
#define     NCP_NCA_ITA_FIFO_OVERFLOW_UNDERFLOW_STATUS_REG0_55XX  (0x00018114)
#define     NCP_NCA_ITA_FIFO_OVERFLOW_UNDERFLOW_STATUS_REG1_55XX  (0x00018118)
#define     NCP_NCA_ITA_FIFO_OVERFLOW_UNDERFLOW_STATUS_REG2_55XX  (0x0001811c)
#define     NCP_NCA_NPGIT_FIFO_OVERFLOW_UNDERFLOW_STATUS_REG0_55XX  (0x00018120)
#define     NCP_NCA_NPGIT_FIFO_OVERFLOW_UNDERFLOW_STATUS_REG1_55XX  (0x00018124)
#define     NCP_NCA_NPGIT_FIFO_OVERFLOW_UNDERFLOW_STATUS_REG2_55XX  (0x00018128)
#define     NCP_NCA_MPB_INPUT_FIFO_OVERFLOW_UNDERFLOW_STATUS_55XX  (0x0001812c)
#define     NCP_NCA_CMN_FIFO_OVERFLOW_UNDERFLOW_STATUS_55XX     (0x00018130)
#define     NCP_NCA_OTA_FIFO_PAR_ERR_STATUS_REG0_55XX           (0x00018200)
#define     NCP_NCA_OTA_FIFO_PAR_ERR_STATUS_REG1_55XX           (0x00018204)
#define     NCP_NCA_OTA_FIFO_PAR_ERR_STATUS_REG2_55XX           (0x00018208)
#define     NCP_NCA_ITA_FIFO_PAR_ERR_STATUS_55XX                (0x0001820c)
#define     NCP_NCA_NPGIT_FIFO_PAR_ERR_STATUS_55XX              (0x00018210)
#define     NCP_NCA_MPB_INPUT_FIFO_PAR_ERR_STATUS_55XX          (0x00018214)
#define     NCP_NCA_CMN_FIFO_PAR_ERR_STATUS_55XX                (0x00018218)
#define     NCP_NCA_OTA_INT_STAT_REG0_55XX                      (0x00018300)
#define     NCP_NCA_OTA_INT_STAT_REG1_55XX                      (0x00018304)
#define     NCP_NCA_ITA_INT_STAT_55XX                           (0x00018400)
#define     NCP_NCA_NPGIT_INT_STAT_55XX                         (0x00018500)
#define     NCP_NCA_MPB_INT_STAT_55XX                           (0x00018600)
#define     NCP_NCA_CMN_INT_STAT_55XX                           (0x00018700)
#define     NCP_NCA_XLAT_ERR_55XX                               (0x00018780)
#define     NCP_NCA_ECC_ERR_55XX                                (0x000187b0)
#define     NCP_NCA_MAX_OUTSTANDING_MEM_OPS_55XX                (0x00018800)
#define     NCP_NCA_MEM_OP_COUNTER_CTL_55XX                     (0x00018810)
#define     NCP_NCA_MEM_OP_COUNTER0_LS_55XX                     (0x00018818)
#define     NCP_NCA_MEM_OP_COUNTER1_LS_55XX                     (0x0001881c)
#define     NCP_NCA_MEM_OP_COUNTER2_LS_55XX                     (0x00018820)
#define     NCP_NCA_MEM_OP_COUNTER3_LS_55XX                     (0x00018824)
#define     NCP_NCA_MEM_OUTSTANDING_ROP_COUNT0_55XX             (0x00018828)
#define     NCP_NCA_MEM_OUTSTANDING_ROP_COUNT1_55XX             (0x0001882c)
#define     NCP_NCA_MEM_OUTSTANDING_RDATA_COUNT0_55XX           (0x00018830)
#define     NCP_NCA_MEM_OUTSTANDING_RDATA_COUNT1_55XX           (0x00018834)
#define     NCP_NCA_MEM_OUTSTANDING_WOP_COUNT0_55XX             (0x00018838)
#define     NCP_NCA_MEM_OUTSTANDING_WOP_COUNT1_55XX             (0x0001883c)
#define     NCP_NCA_MEM_OP_COUNTER0_MS_55XX                     (0x00018844)
#define     NCP_NCA_MEM_OP_COUNTER1_MS_55XX                     (0x00018848)
#define     NCP_NCA_MEM_OP_COUNTER2_MS_55XX                     (0x0001884c)
#define     NCP_NCA_MEM_OP_COUNTER3_MS_55XX                     (0x00018850)
#define     NCP_NCA_MEM_VALID_READY_55XX                        (0x00018854)
#define     NCP_NCA_GRP_LOAD_POKE_ENABLE_WOCLR_55XX             (0x0001f220)
#define     NCP_NCA_GRP_LOAD_TIMER_ENABLE_WOCLR_55XX            (0x0001f224)
#define     NCP_NCA_GRP_UPLOAD_POKE_ENABLE_WOCLR_55XX           (0x0001f228)
#define     NCP_NCA_GRP_UPLOAD_TIMER_ENABLE_WOCLR_55XX          (0x0001f22c)
#define     NCP_NCA_MME_BUF_FETCH_EN_SIZE0_WOCLR_55XX           (0x0001f260)
#define     NCP_NCA_MME_BUF_FETCH_EN_SIZE1_WOCLR_55XX           (0x0001f264)
#define     NCP_NCA_MME_BUF_FETCH_EN_SIZE2_WOCLR_55XX           (0x0001f268)
#define     NCP_NCA_MME_BUF_FETCH_EN_SIZE3_WOCLR_55XX           (0x0001f26c)
#define     NCP_NCA_GRP_LOAD_POKE_ENABLE_WOSET_55XX             (0x0001f320)
#define     NCP_NCA_GRP_LOAD_TIMER_ENABLE_WOSET_55XX            (0x0001f324)
#define     NCP_NCA_GRP_UPLOAD_POKE_ENABLE_WOSET_55XX           (0x0001f328)
#define     NCP_NCA_GRP_UPLOAD_TIMER_ENABLE_WOSET_55XX          (0x0001f32c)
#define     NCP_NCA_MME_BUF_FETCH_EN_SIZE0_WOSET_55XX           (0x0001f360)
#define     NCP_NCA_MME_BUF_FETCH_EN_SIZE1_WOSET_55XX           (0x0001f364)
#define     NCP_NCA_MME_BUF_FETCH_EN_SIZE2_WOSET_55XX           (0x0001f368)
#define     NCP_NCA_MME_BUF_FETCH_EN_SIZE3_WOSET_55XX           (0x0001f36c)
#define     NCP_NCA_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R0(n)        (0x00000200 + (32*(n)))
#define     NCP_NCA_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R0_55XX(n)   (0x00010400 + (32*(n)))
#define     NCP_NCA_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R1(n)        (0x00000204 + (32*(n)))
#define     NCP_NCA_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R1_55XX(n)   (0x00010404 + (32*(n)))
#define     NCP_NCA_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R2(n)        (0x00000208 + (32*(n)))
#define     NCP_NCA_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R2_55XX(n)   (0x00010408 + (32*(n)))
#define     NCP_NCA_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R3(n)        (0x0000020c + (32*(n)))
#define     NCP_NCA_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R3_55XX(n)   (0x0001040c + (32*(n)))
#define     NCP_NCA_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R4(n)        (0x00000210 + (32*(n)))
#define     NCP_NCA_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R4_55XX(n)   (0x00010410 + (32*(n)))
#define     NCP_NCA_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R5(n)        (0x00000214 + (32*(n)))
#define     NCP_NCA_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R5_55XX(n)   (0x00010414 + (32*(n)))
#define     NCP_NCA_PCQ_DESC_RPCQ_34XX_R0_34XX(n)               (0x00000300 + (8*(n)))
#define     NCP_NCA_PCQ_DESC_RPCQ_34XX_R1_34XX(n)               (0x00000304 + (8*(n)))
#define     NCP_NCA_PCQ_STAT_RPCQ_34XX_R0_34XX(n)               (0x00000380 + (8*(n)))
#define     NCP_NCA_PCQ_STAT_RPCQ_34XX_R1_34XX(n)               (0x00000384 + (8*(n)))
#define     NCP_NCA_PCQ_DESC_TPCQ_34XX_R0_34XX(n)               (0x00000400 + (8*(n)))
#define     NCP_NCA_PCQ_DESC_TPCQ_34XX_R1_34XX(n)               (0x00000404 + (8*(n)))
#define     NCP_NCA_PCQ_STAT_TPCQ_34XX_R0_34XX(n)               (0x00000480 + (8*(n)))
#define     NCP_NCA_PCQ_STAT_TPCQ_34XX_R1_34XX(n)               (0x00000484 + (8*(n)))
#define     NCP_NCA_PCQ_DESC_CPCQ_R0(n)                         (0x00000500 + (8*(n)))
#define     NCP_NCA_PCQ_DESC_CPCQ_R0_55XX(n)                    (0x00010800 + (16*(n)))
#define     NCP_NCA_PCQ_DESC_CPCQ_R1(n)                         (0x00000504 + (8*(n)))
#define     NCP_NCA_PCQ_DESC_CPCQ_R1_55XX(n)                    (0x00010804 + (16*(n)))
#define     NCP_NCA_PCQ_DESC_CPCQ_R2_55XX(n)                    (0x00010808 + (16*(n)))
#define     NCP_NCA_PCQ_DESC_CPCQ_R3_55XX(n)                    (0x0001080c + (16*(n)))
#define     NCP_NCA_PCQ_STAT_CPCQ_R0(n)                         (0x00000580 + (8*(n)))
#define     NCP_NCA_PCQ_STAT_CPCQ_R1(n)                         (0x00000584 + (8*(n)))
#define     NCP_NCA_PCQ_DESC_OPCQ_R0(n)                         (0x00000600 + (8*(n)))
#define     NCP_NCA_PCQ_DESC_OPCQ_R0_55XX(n)                    (0x00011000 + (16*(n)))
#define     NCP_NCA_PCQ_DESC_OPCQ_R1(n)                         (0x00000604 + (8*(n)))
#define     NCP_NCA_PCQ_DESC_OPCQ_R1_55XX(n)                    (0x00011004 + (16*(n)))
#define     NCP_NCA_PCQ_DESC_OPCQ_R2_55XX(n)                    (0x00011008 + (16*(n)))
#define     NCP_NCA_PCQ_DESC_OPCQ_R3_55XX(n)                    (0x0001100c + (16*(n)))
#define     NCP_NCA_PCQ_STAT_OPCQ_R0(n)                         (0x00000680 + (8*(n)))
#define     NCP_NCA_PCQ_STAT_OPCQ_R1(n)                         (0x00000684 + (8*(n)))
#define     NCP_NCA_RCV_BUFF_POOL_34XX_SIZE_0_1_R_34XX(n)       (0x00000700 + (8*(n)))
#define     NCP_NCA_RCV_BUFF_POOL_34XX_SIZE_2_3_R_34XX(n)       (0x00000704 + (8*(n)))
#define     NCP_NCA_PCQ_DESC_IPCQ_R0(n)                         (0x00000800 + (8*(n)))
#define     NCP_NCA_PCQ_DESC_IPCQ_R0_55XX(n)                    (0x00011800 + (16*(n)))
#define     NCP_NCA_PCQ_DESC_IPCQ_R1(n)                         (0x00000804 + (8*(n)))
#define     NCP_NCA_PCQ_DESC_IPCQ_R1_55XX(n)                    (0x00011804 + (16*(n)))
#define     NCP_NCA_PCQ_DESC_IPCQ_R2_55XX(n)                    (0x00011808 + (16*(n)))
#define     NCP_NCA_PCQ_DESC_IPCQ_R3_55XX(n)                    (0x0001180c + (16*(n)))
#define     NCP_NCA_PCQ_STAT_IPCQ_R0(n)                         (0x00000900 + (8*(n)))
#define     NCP_NCA_PCQ_STAT_IPCQ_R1(n)                         (0x00000904 + (8*(n)))
#define     NCP_NCA_RBP_DEPTHS_34XX_R0_34XX(n)                  (0x00001280 + (8*(n)))
#define     NCP_NCA_RBP_DEPTHS_34XX_R0_25XX(n)                  (0x00001280 + (8*(n)))
#define     NCP_NCA_RBP_DEPTHS_34XX_R1_34XX(n)                  (0x00001284 + (8*(n)))
#define     NCP_NCA_RBP_DEPTHS_34XX_R1_25XX(n)                  (0x00001284 + (8*(n)))
#define     NCP_NCA_GRP_INTERRUPT_STATUS_TABLE_STATUS_R0        (0x0000f010)
#define     NCP_NCA_GRP_INTERRUPT_STATUS_TABLE_STATUS_R0_SERVICE_MASK  (0x01ffffff)
#define     NCP_NCA_GRP_INTERRUPT_STATUS_TABLE_STATUS_R0_55XX   (0x0001f020)
#define     NCP_NCA_GRP_INTERRUPT_STATUS_TABLE_STATUS_R0_55XX_SERVICE_MASK  (0xffffffff)
#define     NCP_NCA_GRP_INTERRUPT_STATUS_TABLE_STATUS_R1        (0x0000f014)
#define     NCP_NCA_GRP_INTERRUPT_STATUS_TABLE_STATUS_R1_ALARM_MASK  (0x0000ffff)
#define     NCP_NCA_GRP_INTERRUPT_STATUS_TABLE_STATUS_R1_55XX   (0x0001f024)
#define     NCP_NCA_GRP_INTERRUPT_STATUS_TABLE_STATUS_R1_55XX_SERVICE_MASK  (0x0001ffff)
#define     NCP_NCA_GRP_INTERRUPT_STATUS_TABLE_STATUS_R2        (0x0000f018)
#define     NCP_NCA_GRP_INTERRUPT_STATUS_TABLE_STATUS_R2_ALARM_MASK  (0xefffffff)
#define     NCP_NCA_GRP_INTERRUPT_STATUS_TABLE_STATUS_R2_SERVICE_MASK  (0x10000000)
#define     NCP_NCA_GRP_INTERRUPT_STATUS_TABLE_STATUS_R2_55XX   (0x0001f028)
#define     NCP_NCA_GRP_INTERRUPT_STATUS_TABLE_STATUS_R2_55XX_ALARM_MASK  (0xffffffff)
#define     NCP_NCA_GRP_INTERRUPT_STATUS_TABLE_STATUS_R3_55XX   (0x0001f02c)
#define     NCP_NCA_GRP_INTERRUPT_STATUS_TABLE_STATUS_R3_55XX_ALARM_MASK  (0x7f7fffff)
#define     NCP_NCA_GRP_INTERRUPT_STATUS_TABLE_STATUS_R3_55XX_SERVICE_MASK  (0x00800000)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_EN_R0            (0x0000f020)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_EN_R0_SERVICE_MASK  (0x01ffffff)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_EN_R0_55XX       (0x0001f030)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_EN_R0_55XX_SERVICE_MASK  (0xffffffff)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_EN_R1            (0x0000f024)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_EN_R1_ALARM_MASK  (0x0000ffff)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_EN_R1_55XX       (0x0001f034)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_EN_R1_55XX_SERVICE_MASK  (0x0001ffff)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_EN_R2            (0x0000f028)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_EN_R2_ALARM_MASK  (0xefffffff)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_EN_R2_SERVICE_MASK  (0x10000000)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_EN_R2_55XX       (0x0001f038)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_EN_R2_55XX_ALARM_MASK  (0xffffffff)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_EN_R3_55XX       (0x0001f03c)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_EN_R3_55XX_ALARM_MASK  (0x7f7fffff)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_EN_R3_55XX_SERVICE_MASK  (0x00800000)
#define     NCP_NCA_GRP_INTERRUPT_FORCE_TABLE_FRC_R0            (0x0000f030)
#define     NCP_NCA_GRP_INTERRUPT_FORCE_TABLE_FRC_R0_SERVICE_MASK  (0x01ffffff)
#define     NCP_NCA_GRP_INTERRUPT_FORCE_TABLE_FRC_R0_55XX       (0x0001f040)
#define     NCP_NCA_GRP_INTERRUPT_FORCE_TABLE_FRC_R0_55XX_SERVICE_MASK  (0xffffffff)
#define     NCP_NCA_GRP_INTERRUPT_FORCE_TABLE_FRC_R1            (0x0000f034)
#define     NCP_NCA_GRP_INTERRUPT_FORCE_TABLE_FRC_R1_ALARM_MASK  (0x0000ffff)
#define     NCP_NCA_GRP_INTERRUPT_FORCE_TABLE_FRC_R1_55XX       (0x0001f044)
#define     NCP_NCA_GRP_INTERRUPT_FORCE_TABLE_FRC_R1_55XX_SERVICE_MASK  (0x0001ffff)
#define     NCP_NCA_GRP_INTERRUPT_FORCE_TABLE_FRC_R2            (0x0000f038)
#define     NCP_NCA_GRP_INTERRUPT_FORCE_TABLE_FRC_R2_ALARM_MASK  (0xefffffff)
#define     NCP_NCA_GRP_INTERRUPT_FORCE_TABLE_FRC_R2_SERVICE_MASK  (0x10000000)
#define     NCP_NCA_GRP_INTERRUPT_FORCE_TABLE_FRC_R2_55XX       (0x0001f048)
#define     NCP_NCA_GRP_INTERRUPT_FORCE_TABLE_FRC_R2_55XX_ALARM_MASK  (0xffffffff)
#define     NCP_NCA_GRP_INTERRUPT_FORCE_TABLE_FRC_R3_55XX       (0x0001f04c)
#define     NCP_NCA_GRP_INTERRUPT_FORCE_TABLE_FRC_R3_55XX_ALARM_MASK  (0x7f7fffff)
#define     NCP_NCA_GRP_INTERRUPT_FORCE_TABLE_FRC_R3_55XX_SERVICE_MASK  (0x00800000)
#define     NCP_NCA_RBP_FIFO_RANGE_25XX_SIZE0_25XX(n)           (0x00001600 + (16*(n)))
#define     NCP_NCA_RBP_FIFO_RANGE_25XX_SIZE1_25XX(n)           (0x00001604 + (16*(n)))
#define     NCP_NCA_RBP_FIFO_RANGE_25XX_SIZE2_25XX(n)           (0x00001608 + (16*(n)))
#define     NCP_NCA_RBP_FIFO_RANGE_25XX_SIZE3_25XX(n)           (0x0000160c + (16*(n)))
#define     NCP_NCA_NCA_PARAMETERS_25XX_MAX_NUM_CFG_NODES_LOOP0_25XX  (0x00001700)

#define     NCP_NCA_NCA_PARAMETERS_25XX_NODE_IN_RING0_55XX_BASE  (0x00019800)
#define     NCP_NCA_NCA_PARAMETERS_25XX_NODE_IN_RING0_55XX(n)   (0x00019800 + (4*(n)))
#define     NCP_NCA_NCA_PARAMETERS_25XX_NODE_IN_RING0_55XX_COUNT  (0x00000008)
#define     NCP_NCA_NCA_PARAMETERS_25XX_NODE_IN_RING0_55XX_IDX(addr) \
  (((addr) - NCP_NCA_NCA_PARAMETERS_25XX_NODE_IN_RING0_55XX_BASE) / 4)
#define     NCP_NCA_NCA_PARAMETERS_25XX_NODE_IN_RING0_55XX_END  (0x00019820)
#define     NCP_NCA_NCA_PARAMETERS_25XX_NODE_IN_RING0_55XX_RANGE(addr) \
 (((addr) >= NCP_NCA_NCA_PARAMETERS_25XX_NODE_IN_RING0_55XX_BASE) && \
  ((addr) < NCP_NCA_NCA_PARAMETERS_25XX_NODE_IN_RING0_55XX_END))

#define     NCP_NCA_NCA_PARAMETERS_25XX_MAX_NUM_CFG_NODES_LOOP1_25XX  (0x00001704)
#define     NCP_NCA_NCA_PARAMETERS_25XX_MAX_NUM_CFG_NODES_LOOP2_25XX  (0x00001708)
#define     NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING0_25XX     (0x0000170c)

#define     NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING0_55XX_BASE  (0x00019860)
#define     NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING0_55XX(n)  (0x00019860 + (4*(n)))
#define     NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING0_55XX_COUNT  (0x00000008)
#define     NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING0_55XX_IDX(addr) \
  (((addr) - NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING0_55XX_BASE) / 4)
#define     NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING0_55XX_END  (0x00019880)
#define     NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING0_55XX_RANGE(addr) \
 (((addr) >= NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING0_55XX_BASE) && \
  ((addr) < NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING0_55XX_END))

#define     NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING1_25XX     (0x00001710)

#define     NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING1_55XX_BASE  (0x00019880)
#define     NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING1_55XX(n)  (0x00019880 + (4*(n)))
#define     NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING1_55XX_COUNT  (0x00000008)
#define     NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING1_55XX_IDX(addr) \
  (((addr) - NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING1_55XX_BASE) / 4)
#define     NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING1_55XX_END  (0x000198a0)
#define     NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING1_55XX_RANGE(addr) \
 (((addr) >= NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING1_55XX_BASE) && \
  ((addr) < NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING1_55XX_END))

#define     NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING2_25XX     (0x00001714)

#define     NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING2_55XX_BASE  (0x000198a0)
#define     NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING2_55XX(n)  (0x000198a0 + (4*(n)))
#define     NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING2_55XX_COUNT  (0x00000008)
#define     NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING2_55XX_IDX(addr) \
  (((addr) - NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING2_55XX_BASE) / 4)
#define     NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING2_55XX_END  (0x000198c0)
#define     NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING2_55XX_RANGE(addr) \
 (((addr) >= NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING2_55XX_BASE) && \
  ((addr) < NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING2_55XX_END))

#define     NCP_NCA_NCA_PARAMETERS_25XX_AXI_ADDR_WIDTH_25XX     (0x00001718)
#define     NCP_NCA_NCA_PARAMETERS_25XX_AXI_M_RID_WIDTH_25XX    (0x0000171c)
#define     NCP_NCA_NCA_PARAMETERS_25XX_AXI_M_WID_WIDTH_25XX    (0x00001720)

#define     NCP_NCA_NCA_PARAMETERS_25XX_NODE_IN_RING1_55XX_BASE  (0x00019820)
#define     NCP_NCA_NCA_PARAMETERS_25XX_NODE_IN_RING1_55XX(n)   (0x00019820 + (4*(n)))
#define     NCP_NCA_NCA_PARAMETERS_25XX_NODE_IN_RING1_55XX_COUNT  (0x00000008)
#define     NCP_NCA_NCA_PARAMETERS_25XX_NODE_IN_RING1_55XX_IDX(addr) \
  (((addr) - NCP_NCA_NCA_PARAMETERS_25XX_NODE_IN_RING1_55XX_BASE) / 4)
#define     NCP_NCA_NCA_PARAMETERS_25XX_NODE_IN_RING1_55XX_END  (0x00019840)
#define     NCP_NCA_NCA_PARAMETERS_25XX_NODE_IN_RING1_55XX_RANGE(addr) \
 (((addr) >= NCP_NCA_NCA_PARAMETERS_25XX_NODE_IN_RING1_55XX_BASE) && \
  ((addr) < NCP_NCA_NCA_PARAMETERS_25XX_NODE_IN_RING1_55XX_END))

#define     NCP_NCA_NCA_PARAMETERS_25XX_AXI_SZ_WIDTH_25XX       (0x00001724)
#define     NCP_NCA_NCA_PARAMETERS_25XX_AXI_SZ_WIDTH_55XX       (0x000198f4)
#define     NCP_NCA_NCA_PARAMETERS_25XX_AXI_M_DATA_WIDTH_25XX   (0x00001728)
#define     NCP_NCA_NCA_PARAMETERS_25XX_AXI_RESP_WIDTH_25XX     (0x0000172c)
#define     NCP_NCA_NCA_PARAMETERS_25XX_AXI_RESP_WIDTH_55XX     (0x000198f8)
#define     NCP_NCA_NCA_PARAMETERS_25XX_AXI_M_BYTE_LANES_WIDTH_25XX  (0x00001730)
#define     NCP_NCA_NCA_PARAMETERS_25XX_AXI_S_RID_WIDTH_25XX    (0x00001734)
#define     NCP_NCA_NCA_PARAMETERS_25XX_AXI_S_WID_WIDTH_25XX    (0x00001738)
#define     NCP_NCA_NCA_PARAMETERS_25XX_NUM_IPC_QUEUES_25XX     (0x0000173c)
#define     NCP_NCA_NCA_PARAMETERS_25XX_NUM_IPC_QUEUES_55XX     (0x00019904)
#define     NCP_NCA_NCA_PARAMETERS_25XX_NUM_OPC_QUEUES_25XX     (0x00001740)
#define     NCP_NCA_NCA_PARAMETERS_25XX_NUM_OPC_QUEUES_55XX     (0x000198fc)
#define     NCP_NCA_NCA_PARAMETERS_25XX_NUM_TPC_QUEUES_25XX     (0x00001744)
#define     NCP_NCA_NCA_PARAMETERS_25XX_NUM_RPC_QUEUES_25XX     (0x00001748)
#define     NCP_NCA_NCA_PARAMETERS_25XX_NUM_CPC_QUEUES_25XX     (0x0000174c)
#define     NCP_NCA_NCA_PARAMETERS_25XX_NUM_CPC_QUEUES_55XX     (0x00019900)
#define     NCP_NCA_NCA_PARAMETERS_25XX_NUM_RBUF_POOLS_25XX     (0x00001750)
#define     NCP_NCA_NCA_PARAMETERS_25XX_RBP_SIZ0_RAM_DEPTH_25XX  (0x00001754)
#define     NCP_NCA_NCA_PARAMETERS_25XX_RBP_SIZ1_RAM_DEPTH_25XX  (0x00001758)
#define     NCP_NCA_NCA_PARAMETERS_25XX_RBP_SIZ2_RAM_DEPTH_25XX  (0x0000175c)
#define     NCP_NCA_NCA_PARAMETERS_25XX_RBP_SIZ3_RAM_DEPTH_25XX  (0x00001760)

#define     NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING0_55XX_BASE  (0x00019860)
#define     NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING0_55XX(n)  (0x00019860 + (4*(n)))
#define     NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING0_55XX_COUNT  (0x00000008)
#define     NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING0_55XX_IDX(addr) \
  (((addr) - NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING0_55XX_BASE) / 4)
#define     NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING0_55XX_END  (0x00019880)
#define     NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING0_55XX_RANGE(addr) \
 (((addr) >= NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING0_55XX_BASE) && \
  ((addr) < NCP_NCA_NCA_PARAMETERS_25XX_BC_NODES_RING0_55XX_END))


#define     NCP_NCA_NCA_PARAMETERS_25XX_NODE_IN_RING2_55XX_BASE  (0x00019840)
#define     NCP_NCA_NCA_PARAMETERS_25XX_NODE_IN_RING2_55XX(n)   (0x00019840 + (4*(n)))
#define     NCP_NCA_NCA_PARAMETERS_25XX_NODE_IN_RING2_55XX_COUNT  (0x00000008)
#define     NCP_NCA_NCA_PARAMETERS_25XX_NODE_IN_RING2_55XX_IDX(addr) \
  (((addr) - NCP_NCA_NCA_PARAMETERS_25XX_NODE_IN_RING2_55XX_BASE) / 4)
#define     NCP_NCA_NCA_PARAMETERS_25XX_NODE_IN_RING2_55XX_END  (0x00019860)
#define     NCP_NCA_NCA_PARAMETERS_25XX_NODE_IN_RING2_55XX_RANGE(addr) \
 (((addr) >= NCP_NCA_NCA_PARAMETERS_25XX_NODE_IN_RING2_55XX_BASE) && \
  ((addr) < NCP_NCA_NCA_PARAMETERS_25XX_NODE_IN_RING2_55XX_END))

#define     NCP_NCA_NCA_PARAMETERS_25XX_ACEL_M_PORTS_55XX       (0x000198c0)
#define     NCP_NCA_NCA_PARAMETERS_25XX_AXI3_M_PORTS_55XX       (0x000198c4)
#define     NCP_NCA_NCA_PARAMETERS_25XX_AXI3_M_RID_WIDTH_55XX   (0x000198c8)
#define     NCP_NCA_NCA_PARAMETERS_25XX_AXI3_M_WID_WIDTH_55XX   (0x000198cc)
#define     NCP_NCA_NCA_PARAMETERS_25XX_AXI3_M_ADDR_WIDTH_55XX  (0x000198d0)
#define     NCP_NCA_NCA_PARAMETERS_25XX_AXI3_M_DATA_WIDTH_55XX  (0x000198d4)
#define     NCP_NCA_NCA_PARAMETERS_25XX_AXI3_M_STRB_WIDTH_55XX  (0x000198d8)
#define     NCP_NCA_NCA_PARAMETERS_25XX_AXI3_S_PORTS_55XX       (0x000198dc)
#define     NCP_NCA_NCA_PARAMETERS_25XX_AXI3_S_RID_WIDTH_55XX   (0x000198e0)
#define     NCP_NCA_NCA_PARAMETERS_25XX_AXI3_S_WID_WIDTH_55XX   (0x000198e4)
#define     NCP_NCA_NCA_PARAMETERS_25XX_AXI3_S_ADDR_WIDTH_55XX  (0x000198e8)
#define     NCP_NCA_NCA_PARAMETERS_25XX_AXI3_S_DATA_WIDTH_55XX  (0x000198ec)
#define     NCP_NCA_NCA_PARAMETERS_25XX_AXI3_S_STRB_WIDTH_55XX  (0x000198f0)
#define     NCP_NCA_NCA_PARAMETERS_25XX_NUM_CPU_INTERRUPTS_55XX  (0x00019908)
#define     NCP_NCA_NCA_PARAMETERS_25XX_NUM_HW_INTERRUPTS_55XX  (0x0001990c)
#define     NCP_NCA_NCA_PARAMETERS_25XX_NUM_PCQ_GROUPS_55XX     (0x00019910)
#define     NCP_NCA_NCA_PARAMETERS_25XX_NUM_PCQ_GROUPS_WIDTH_55XX  (0x00019914)
#define     NCP_NCA_NCA_PARAMETERS_25XX_VI_WIDTH_55XX           (0x00019918)
#define     NCP_NCA_NCA_PARAMETERS_25XX_POOLID_WIDTH_55XX       (0x0001991c)
#define     NCP_NCA_NCA_PARAMETERS_25XX_NUM_MEM_POOLS_55XX      (0x00019920)
#define     NCP_NCA_NCA_PARAMETERS_25XX_NUM_MEM_POOLS_WIDTH_55XX  (0x00019924)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOCLR_25XX_EN_R0_WOCLR_25XX  (0x0000f240)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOCLR_25XX_EN_R0_WOCLR_25XX_SERVICE_MASK  (0x01ffffff)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOCLR_25XX_EN_R0_WOCLR_55XX  (0x0001f240)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOCLR_25XX_EN_R0_WOCLR_55XX_SERVICE_MASK  (0xffffffff)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOCLR_25XX_EN_R1_WOCLR_25XX  (0x0000f244)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOCLR_25XX_EN_R1_WOCLR_25XX_ALARM_MASK  (0x0000ffff)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOCLR_25XX_EN_R1_WOCLR_55XX  (0x0001f244)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOCLR_25XX_EN_R1_WOCLR_55XX_SERVICE_MASK  (0x0001ffff)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOCLR_25XX_EN_R2_WOCLR_25XX  (0x0000f248)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOCLR_25XX_EN_R2_WOCLR_25XX_ALARM_MASK  (0xefffffff)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOCLR_25XX_EN_R2_WOCLR_25XX_SERVICE_MASK  (0x10000000)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOCLR_25XX_EN_R2_WOCLR_55XX  (0x0001f248)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOCLR_25XX_EN_R2_WOCLR_55XX_ALARM_MASK  (0xffffffff)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOCLR_25XX_EN_R3_WOCLR_55XX  (0x0001f24c)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOCLR_25XX_EN_R3_WOCLR_55XX_ALARM_MASK  (0x7f7fffff)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOCLR_25XX_EN_R3_WOCLR_55XX_SERVICE_MASK  (0x00800000)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOSET_25XX_EN_R0_WOSET_25XX  (0x0000f340)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOSET_25XX_EN_R0_WOSET_25XX_SERVICE_MASK  (0x01ffffff)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOSET_25XX_EN_R0_WOSET_55XX  (0x0001f340)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOSET_25XX_EN_R0_WOSET_55XX_SERVICE_MASK  (0xffffffff)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOSET_25XX_EN_R1_WOSET_25XX  (0x0000f344)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOSET_25XX_EN_R1_WOSET_25XX_ALARM_MASK  (0x0000ffff)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOSET_25XX_EN_R1_WOSET_55XX  (0x0001f344)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOSET_25XX_EN_R1_WOSET_55XX_SERVICE_MASK  (0x0001ffff)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOSET_25XX_EN_R2_WOSET_25XX  (0x0000f348)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOSET_25XX_EN_R2_WOSET_25XX_ALARM_MASK  (0xefffffff)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOSET_25XX_EN_R2_WOSET_25XX_SERVICE_MASK  (0x10000000)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOSET_25XX_EN_R2_WOSET_55XX  (0x0001f348)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOSET_25XX_EN_R2_WOSET_55XX_ALARM_MASK  (0xffffffff)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOSET_25XX_EN_R3_WOSET_55XX  (0x0001f34c)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOSET_25XX_EN_R3_WOSET_55XX_ALARM_MASK  (0x7f7fffff)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOSET_25XX_EN_R3_WOSET_55XX_SERVICE_MASK  (0x00800000)
#define     NCP_NCA_PCQ_DESC_APCQ_55XX_R0_55XX(n)               (0x00012800 + (16*(n)))
#define     NCP_NCA_PCQ_DESC_APCQ_55XX_R1_55XX(n)               (0x00012804 + (16*(n)))
#define     NCP_NCA_PCQ_DESC_APCQ_55XX_R2_55XX(n)               (0x00012808 + (16*(n)))
#define     NCP_NCA_PCQ_DESC_APCQ_55XX_R3_55XX(n)               (0x0001280c + (16*(n)))
#define     NCP_NCA_PCQ_STAT_APCQ_55XX_R0_55XX(n)               (0x00013000 + (8*(n)))
#define     NCP_NCA_PCQ_STAT_APCQ_55XX_R1_55XX(n)               (0x00013004 + (8*(n)))
#define     NCP_NCA_MPB_FIFO_RANGE_55XX_SIZE0_55XX(n)           (0x00019000 + (16*(n)))
#define     NCP_NCA_MPB_FIFO_RANGE_55XX_SIZE1_55XX(n)           (0x00019004 + (16*(n)))
#define     NCP_NCA_MPB_FIFO_RANGE_55XX_SIZE2_55XX(n)           (0x00019008 + (16*(n)))
#define     NCP_NCA_MPB_FIFO_RANGE_55XX_SIZE3_55XX(n)           (0x0001900c + (16*(n)))
#define     NCP_NCA_MPB_DEPTHS_55XX_R0_55XX(n)                  (0x00019400 + (8*(n)))
#define     NCP_NCA_MPB_DEPTHS_55XX_R1_55XX(n)                  (0x00019404 + (8*(n)))
#define     NCP_NCA_DRIVING_INT_STATUS_TABLE_55XX_R0_55XX       (0x0001f010)
#define     NCP_NCA_DRIVING_INT_STATUS_TABLE_55XX_R0_55XX_SERVICE_MASK  (0xffffffff)
#define     NCP_NCA_DRIVING_INT_STATUS_TABLE_55XX_R1_55XX       (0x0001f014)
#define     NCP_NCA_DRIVING_INT_STATUS_TABLE_55XX_R1_55XX_SERVICE_MASK  (0x0001ffff)
#define     NCP_NCA_DRIVING_INT_STATUS_TABLE_55XX_R2_55XX       (0x0001f018)
#define     NCP_NCA_DRIVING_INT_STATUS_TABLE_55XX_R2_55XX_ALARM_MASK  (0xffffffff)
#define     NCP_NCA_DRIVING_INT_STATUS_TABLE_55XX_R3_55XX       (0x0001f01c)
#define     NCP_NCA_DRIVING_INT_STATUS_TABLE_55XX_R3_55XX_ALARM_MASK  (0x7f7fffff)
#define     NCP_NCA_DRIVING_INT_STATUS_TABLE_55XX_R3_55XX_SERVICE_MASK  (0x00800000)


#define     NCP_NCA_OTA_CPU_VPP_XLAT_TABLE_55XX_BASE            (0x00014000)
#define     NCP_NCA_OTA_CPU_VPP_XLAT_TABLE_55XX(n)              (0x00014000 + (16*(n)))
#define     NCP_NCA_OTA_CPU_VPP_XLAT_TABLE_55XX_ACCESS_SIZE     (0x00000010) /* Bytes */
#define     NCP_NCA_OTA_CPU_VPP_XLAT_TABLE_55XX_COUNT           (0x00000018)
#define     NCP_NCA_OTA_CPU_VPP_XLAT_TABLE_55XX_IDX(addr) \
    (((addr) - NCP_NCA_OTA_CPU_VPP_XLAT_TABLE_55XX_BASE) / 16)
#define     NCP_NCA_OTA_CPU_VPP_XLAT_TABLE_55XX_END             (0x00014180)
#define     NCP_NCA_OTA_CPU_VPP_XLAT_TABLE_55XX_RANGE(addr) \
 (((addr) >= NCP_NCA_OTA_CPU_VPP_XLAT_TABLE_55XX_BASE) && \
  ((addr) < NCP_NCA_OTA_CPU_VPP_XLAT_TABLE_55XX_END))



#define     NCP_NCA_ITA_CPU_VPP_XLAT_TABLE_55XX_BASE            (0x00014800)
#define     NCP_NCA_ITA_CPU_VPP_XLAT_TABLE_55XX(n)              (0x00014800 + (16*(n)))
#define     NCP_NCA_ITA_CPU_VPP_XLAT_TABLE_55XX_ACCESS_SIZE     (0x00000010) /* Bytes */
#define     NCP_NCA_ITA_CPU_VPP_XLAT_TABLE_55XX_COUNT           (0x00000018)
#define     NCP_NCA_ITA_CPU_VPP_XLAT_TABLE_55XX_IDX(addr) \
    (((addr) - NCP_NCA_ITA_CPU_VPP_XLAT_TABLE_55XX_BASE) / 16)
#define     NCP_NCA_ITA_CPU_VPP_XLAT_TABLE_55XX_END             (0x00014980)
#define     NCP_NCA_ITA_CPU_VPP_XLAT_TABLE_55XX_RANGE(addr) \
 (((addr) >= NCP_NCA_ITA_CPU_VPP_XLAT_TABLE_55XX_BASE) && \
  ((addr) < NCP_NCA_ITA_CPU_VPP_XLAT_TABLE_55XX_END))



#define     NCP_NCA_ITA_VPP_CPU_XLAT_TABLE_55XX_BASE            (0x00015000)
#define     NCP_NCA_ITA_VPP_CPU_XLAT_TABLE_55XX(n)              (0x00015000 + (16*(n)))
#define     NCP_NCA_ITA_VPP_CPU_XLAT_TABLE_55XX_ACCESS_SIZE     (0x00000010) /* Bytes */
#define     NCP_NCA_ITA_VPP_CPU_XLAT_TABLE_55XX_COUNT           (0x00000008)
#define     NCP_NCA_ITA_VPP_CPU_XLAT_TABLE_55XX_IDX(addr) \
    (((addr) - NCP_NCA_ITA_VPP_CPU_XLAT_TABLE_55XX_BASE) / 16)
#define     NCP_NCA_ITA_VPP_CPU_XLAT_TABLE_55XX_END             (0x00015080)
#define     NCP_NCA_ITA_VPP_CPU_XLAT_TABLE_55XX_RANGE(addr) \
 (((addr) >= NCP_NCA_ITA_VPP_CPU_XLAT_TABLE_55XX_BASE) && \
  ((addr) < NCP_NCA_ITA_VPP_CPU_XLAT_TABLE_55XX_END))

#ifdef __cplusplus
}
#endif

#endif /* _NCP_NCA_REG_DEFINES_H_ */
