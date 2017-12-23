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


#ifndef _NCP_NCAP_REG_DEFINES_H_
#define _NCP_NCAP_REG_DEFINES_H_

#ifdef __cplusplus
extern "C" {
#endif


    /* NODE 0x0 , TARGET 0xffffffff*/


#define     NCP_NCAP_CONFIG_INIT                                (0x00010010)
#define     NCP_NCAP_IDLE_STATUS                                (0x00010014)
#define     NCP_NCAP_SCRATCH                                    (0x00010018)
#define     NCP_NCAP_PGITM_LOAD_CPU_GRP_INDEXES                 (0x00010020)
#define     NCP_NCAP_PGITM_INIT_GRP_INDEXES                     (0x00010028)
#define     NCP_NCAP_HW_POKE_AND_TIMER_ENABLE                   (0x00010030)
#define     NCP_NCAP_GRP_LOAD_POKE_ENABLE                       (0x00010040)
#define     NCP_NCAP_GRP_LOAD_TIMER_ENABLE                      (0x00010044)
#define     NCP_NCAP_GRP_UPLOAD_POKE_ENABLE                     (0x00010048)
#define     NCP_NCAP_GRP_UPLOAD_TIMER_ENABLE                    (0x0001004c)

#define     NCP_NCAP_PGIT_GRP_LOAD_TIMER_BASE                   (0x00010080)
#define     NCP_NCAP_PGIT_GRP_LOAD_TIMER(n)                     (0x00010080 + (4*(n)))
#define     NCP_NCAP_PGIT_GRP_LOAD_TIMER_COUNT                  (0x00000008)
#define     NCP_NCAP_PGIT_GRP_LOAD_TIMER_IDX(addr) \
           (((addr) - NCP_NCAP_PGIT_GRP_LOAD_TIMER_BASE) / 4)
#define     NCP_NCAP_PGIT_GRP_LOAD_TIMER_END                    (0x000100a0)
#define     NCP_NCAP_PGIT_GRP_LOAD_TIMER_RANGE(addr) \
        (((addr) >= NCP_NCAP_PGIT_GRP_LOAD_TIMER_BASE) && \
        ((addr) < NCP_NCAP_PGIT_GRP_LOAD_TIMER_END))


#define     NCP_NCAP_PGIT_GRP_UPLOAD_TIMER_BASE                 (0x00010100)
#define     NCP_NCAP_PGIT_GRP_UPLOAD_TIMER(n)                   (0x00010100 + (4*(n)))
#define     NCP_NCAP_PGIT_GRP_UPLOAD_TIMER_COUNT                (0x00000008)
#define     NCP_NCAP_PGIT_GRP_UPLOAD_TIMER_IDX(addr) \
         (((addr) - NCP_NCAP_PGIT_GRP_UPLOAD_TIMER_BASE) / 4)
#define     NCP_NCAP_PGIT_GRP_UPLOAD_TIMER_END                  (0x00010120)
#define     NCP_NCAP_PGIT_GRP_UPLOAD_TIMER_RANGE(addr) \
      (((addr) >= NCP_NCAP_PGIT_GRP_UPLOAD_TIMER_BASE) && \
      ((addr) < NCP_NCAP_PGIT_GRP_UPLOAD_TIMER_END))


#define     NCP_NCAP_DELAY_GRP_UPLOAD_TIMER_BASE                (0x00010180)
#define     NCP_NCAP_DELAY_GRP_UPLOAD_TIMER(n)                  (0x00010180 + (4*(n)))
#define     NCP_NCAP_DELAY_GRP_UPLOAD_TIMER_COUNT               (0x00000008)
#define     NCP_NCAP_DELAY_GRP_UPLOAD_TIMER_IDX(addr) \
        (((addr) - NCP_NCAP_DELAY_GRP_UPLOAD_TIMER_BASE) / 4)
#define     NCP_NCAP_DELAY_GRP_UPLOAD_TIMER_END                 (0x000101a0)
#define     NCP_NCAP_DELAY_GRP_UPLOAD_TIMER_RANGE(addr) \
     (((addr) >= NCP_NCAP_DELAY_GRP_UPLOAD_TIMER_BASE) && \
     ((addr) < NCP_NCAP_DELAY_GRP_UPLOAD_TIMER_END))

#define     NCP_NCAP_IPM_TTYPE                                  (0x00010270)
#define     NCP_NCAP_OPM_TTYPE                                  (0x00010278)
#define     NCP_NCAP_MPM_TTYPE                                  (0x0001027c)
#define     NCP_NCAP_PGITM_TTYPE                                (0x00010280)
#define     NCP_NCAP_GRP_RST                                    (0x00010290)
#define     NCP_NCAP_PCQ_DESCR_ENHANCED                         (0x00010298)

#define     NCP_NCAP_INT_PARAM_GRP_BASE                         (0x00010300)
#define     NCP_NCAP_INT_PARAM_GRP(n)                           (0x00010300 + (4*(n)))
#define     NCP_NCAP_INT_PARAM_GRP_COUNT                        (0x00000008)
#define     NCP_NCAP_INT_PARAM_GRP_IDX(addr) \
                 (((addr) - NCP_NCAP_INT_PARAM_GRP_BASE) / 4)      
#define     NCP_NCAP_INT_PARAM_GRP_END                          (0x00010320)
#define     NCP_NCAP_INT_PARAM_GRP_RANGE(addr) \
              (((addr) >= NCP_NCAP_INT_PARAM_GRP_BASE) && \
                  ((addr) < NCP_NCAP_INT_PARAM_GRP_END))

#define     NCP_NCAP_AW_SMON00_NCAP_TASK_SMON                   (0x00018000)
#define     NCP_NCAP_AW_SMON01_NCAP_TASK_SMON                   (0x00018004)
#define     NCP_NCAP_AW_SMON02_NCAP_TASK_SMON                   (0x00018008)
#define     NCP_NCAP_AW_SMON03_NCAP_TASK_SMON                   (0x0001800c)
#define     NCP_NCAP_AW_SMON04_NCAP_TASK_SMON                   (0x00018010)
#define     NCP_NCAP_AW_SMON05_NCAP_TASK_SMON                   (0x00018014)
#define     NCP_NCAP_AW_SMON06_NCAP_TASK_SMON                   (0x00018018)
#define     NCP_NCAP_AW_SMON07_NCAP_TASK_SMON                   (0x0001801c)
#define     NCP_NCAP_IPCQ_ENTRY_DROP_CNT_IPCQ_ER                (0x00018020)
#define     NCP_NCAP_SMON_MUXA_MUXB_SEL                         (0x00018038)
#define     NCP_NCAP_AW_SMON00_NCAP_TASK_SMON1                  (0x00018040)
#define     NCP_NCAP_AW_SMON01_NCAP_TASK_SMON1                  (0x00018044)
#define     NCP_NCAP_AW_SMON02_NCAP_TASK_SMON1                  (0x00018048)
#define     NCP_NCAP_AW_SMON03_NCAP_TASK_SMON1                  (0x0001804c)
#define     NCP_NCAP_AW_SMON04_NCAP_TASK_SMON1                  (0x00018050)
#define     NCP_NCAP_AW_SMON05_NCAP_TASK_SMON1                  (0x00018054)
#define     NCP_NCAP_AW_SMON06_NCAP_TASK_SMON1                  (0x00018058)
#define     NCP_NCAP_AW_SMON07_NCAP_TASK_SMON1                  (0x0001805c)
#define     NCP_NCAP_SMON1_MUXA_MUXB_SEL                        (0x00018078)
#define     NCP_NCAP_PGIT_SOFTWARE_LOAD_POKE_REG                (0x000180c0)

#define     NCP_NCAP_DELAY_GRP_LOAD_TIMER_BASE                  (0x00018100)
#define     NCP_NCAP_DELAY_GRP_LOAD_TIMER(n)                    (0x00018100 + (4*(n)))
#define     NCP_NCAP_DELAY_GRP_LOAD_TIMER_COUNT                 (0x00000008)
#define     NCP_NCAP_DELAY_GRP_LOAD_TIMER_IDX(addr) \
          (((addr) - NCP_NCAP_DELAY_GRP_LOAD_TIMER_BASE) / 4)
#define     NCP_NCAP_DELAY_GRP_LOAD_TIMER_END                   (0x00018120)
#define     NCP_NCAP_DELAY_GRP_LOAD_TIMER_RANGE(addr) \
       (((addr) >= NCP_NCAP_DELAY_GRP_LOAD_TIMER_BASE) && \
       ((addr) < NCP_NCAP_DELAY_GRP_LOAD_TIMER_END))


#define     NCP_NCAP_SWPOKE_DELAY_GRP_LOAD_TIMER_BASE           (0x00018180)
#define     NCP_NCAP_SWPOKE_DELAY_GRP_LOAD_TIMER(n)             (0x00018180 + (4*(n)))
#define     NCP_NCAP_SWPOKE_DELAY_GRP_LOAD_TIMER_COUNT          (0x00000008)
#define     NCP_NCAP_SWPOKE_DELAY_GRP_LOAD_TIMER_IDX(addr) \
   (((addr) - NCP_NCAP_SWPOKE_DELAY_GRP_LOAD_TIMER_BASE) / 4)
#define     NCP_NCAP_SWPOKE_DELAY_GRP_LOAD_TIMER_END            (0x000181a0)
#define     NCP_NCAP_SWPOKE_DELAY_GRP_LOAD_TIMER_RANGE(addr) \
 (((addr) >= NCP_NCAP_SWPOKE_DELAY_GRP_LOAD_TIMER_BASE) && \
  ((addr) < NCP_NCAP_SWPOKE_DELAY_GRP_LOAD_TIMER_END))


#define     NCP_NCAP_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_BASE        (0x00018200)
#define     NCP_NCAP_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER(n)          (0x00018200 + (4*(n)))
#define     NCP_NCAP_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_COUNT       (0x00000008)
#define     NCP_NCAP_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_IDX(addr) \
  (((addr) - NCP_NCAP_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_BASE) / 4)
#define     NCP_NCAP_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_END         (0x00018220)
#define     NCP_NCAP_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_RANGE(addr) \
 (((addr) >= NCP_NCAP_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_BASE) && \
  ((addr) < NCP_NCAP_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_END))


#define     NCP_NCAP_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_BASE       (0x00018280)
#define     NCP_NCAP_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR(n)         (0x00018280 + (4*(n)))
#define     NCP_NCAP_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_COUNT      (0x00000008)
#define     NCP_NCAP_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_IDX(addr) \
  (((addr) - NCP_NCAP_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_BASE) / 4)
#define     NCP_NCAP_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_END        (0x000182a0)
#define     NCP_NCAP_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_RANGE(addr) \
 (((addr) >= NCP_NCAP_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_BASE) && \
  ((addr) < NCP_NCAP_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_END))


#define     NCP_NCAP_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_BASE     (0x00018300)
#define     NCP_NCAP_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR(n)       (0x00018300 + (4*(n)))
#define     NCP_NCAP_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_COUNT    (0x00000008)
#define     NCP_NCAP_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_IDX(addr) \
  (((addr) - NCP_NCAP_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_BASE) / 4)
#define     NCP_NCAP_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_END      (0x00018320)
#define     NCP_NCAP_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_RANGE(addr) \
 (((addr) >= NCP_NCAP_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_BASE) && \
  ((addr) < NCP_NCAP_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_END))

#define     NCP_NCAP_OPM_INT_STAT0                              (0x00018400)
#define     NCP_NCAP_IPM_INT_STAT                               (0x00018480)
#define     NCP_NCAP_NPGIT_INT_STAT0                            (0x00018500)
#define     NCP_NCAP_NPGIT_INT_STAT1                            (0x00018504)
#define     NCP_NCAP_MPM_INT_STAT                               (0x00018600)
#define     NCP_NCAP_MAX_OUTSTANDING_MEM_OPS                    (0x00018700)
#define     NCP_NCAP_OPM_MII_PAR_GEN_POLARITY                   (0x0001a000)
#define     NCP_NCAP_OPM_MOI_PAR_CHK_POLARITY                   (0x0001a004)
#define     NCP_NCAP_OPM_NUM_BEATS_PER_BURST                    (0x0001a008)
#define     NCP_NCAP_OPM_NUM_ENTRIES_PER_REQUEST                (0x0001a00c)
#define     NCP_NCAP_OPCQ_CREDIT_MAX_VALUE                      (0x0001a010)
#define     NCP_NCAP_OPM_SEND_CREDITS                           (0x0001a014)
#define     NCP_NCAP_OPM_SEND_CREDITS_ARB_CTRL                  (0x0001a018)
#define     NCP_NCAP_OPM_MII_WDATA_FLIP                         (0x0001a01c)
#define     NCP_NCAP_OPM_GRP_RST_STATUS                         (0x0001a020)
#define     NCP_NCAP_OPQ_DESCR_CBIT_OVERIDE                     (0x0001a024)
#define     NCP_NCAP_OPQ_DESCR_CPA_OVERIDE                      (0x0001a028)
#define     NCP_NCAP_OPM_MII_BAD_RESP_CNT                       (0x0001a200)
#define     NCP_NCAP_OPM_MOI_PARER_DETECT_CNT                   (0x0001a204)
#define     NCP_NCAP_OPM_SEND_CREDIT_OVFL_CNT                   (0x0001a208)
#define     NCP_NCAP_OPM_NUM_CREDITS_BEFORE_OVFL                (0x0001a20c)
#define     NCP_NCAP_OPM_OPCQ_ENTRY_CFLAG_ER_CNT                (0x0001a210)
#define     NCP_NCAP_OPM_OPCQ_ENTRY_CPA_ER_CNT                  (0x0001a214)

#define     NCP_NCAP_OPCQ_ENTRY_COUNTS_BASE                     (0x0001a280)
#define     NCP_NCAP_OPCQ_ENTRY_COUNTS(n)                       (0x0001a280 + (4*(n)))
#define     NCP_NCAP_OPCQ_ENTRY_COUNTS_COUNT                    (0x00000010)
#define     NCP_NCAP_OPCQ_ENTRY_COUNTS_IDX(addr) \
             (((addr) - NCP_NCAP_OPCQ_ENTRY_COUNTS_BASE) / 4)  
#define     NCP_NCAP_OPCQ_ENTRY_COUNTS_END                      (0x0001a2c0)
#define     NCP_NCAP_OPCQ_ENTRY_COUNTS_RANGE(addr) \
          (((addr) >= NCP_NCAP_OPCQ_ENTRY_COUNTS_BASE) && \
          ((addr) < NCP_NCAP_OPCQ_ENTRY_COUNTS_END))


#define     NCP_NCAP_OPCQ_ENTRY_COUNTS_COR_BASE                 (0x0001a300)
#define     NCP_NCAP_OPCQ_ENTRY_COUNTS_COR(n)                   (0x0001a300 + (4*(n)))
#define     NCP_NCAP_OPCQ_ENTRY_COUNTS_COR_COUNT                (0x00000010)
#define     NCP_NCAP_OPCQ_ENTRY_COUNTS_COR_IDX(addr) \
         (((addr) - NCP_NCAP_OPCQ_ENTRY_COUNTS_COR_BASE) / 4)
#define     NCP_NCAP_OPCQ_ENTRY_COUNTS_COR_END                  (0x0001a340)
#define     NCP_NCAP_OPCQ_ENTRY_COUNTS_COR_RANGE(addr) \
      (((addr) >= NCP_NCAP_OPCQ_ENTRY_COUNTS_COR_BASE) && \
      ((addr) < NCP_NCAP_OPCQ_ENTRY_COUNTS_COR_END))

#define     NCP_NCAP_GET_OPCQ_ENTRY_STATE                       (0x0001a400)
#define     NCP_NCAP_OPM_OPCQ_STATE                             (0x0001a404)
#define     NCP_NCAP_OPM_READ_WRITE_ENGINE_STATE                (0x0001a408)
#define     NCP_NCAP_OPM_MII_STATE                              (0x0001a40c)

#define     NCP_NCAP_OPCQ_NUM_ENTRIES_OUTSTANDING_BASE          (0x0001a480)
#define     NCP_NCAP_OPCQ_NUM_ENTRIES_OUTSTANDING(n)            (0x0001a480 + (4*(n)))
#define     NCP_NCAP_OPCQ_NUM_ENTRIES_OUTSTANDING_COUNT         (0x00000004)
#define     NCP_NCAP_OPCQ_NUM_ENTRIES_OUTSTANDING_IDX(addr) \
  (((addr) - NCP_NCAP_OPCQ_NUM_ENTRIES_OUTSTANDING_BASE) / 4)
#define     NCP_NCAP_OPCQ_NUM_ENTRIES_OUTSTANDING_END           (0x0001a490)
#define     NCP_NCAP_OPCQ_NUM_ENTRIES_OUTSTANDING_RANGE(addr) \
 (((addr) >= NCP_NCAP_OPCQ_NUM_ENTRIES_OUTSTANDING_BASE) && \
  ((addr) < NCP_NCAP_OPCQ_NUM_ENTRIES_OUTSTANDING_END))


#define     NCP_NCAP_OPCQ_FC_RSP_CNT_BASE                       (0x0001a500)
#define     NCP_NCAP_OPCQ_FC_RSP_CNT(n)                         (0x0001a500 + (4*(n)))
#define     NCP_NCAP_OPCQ_FC_RSP_CNT_COUNT                      (0x00000004)
#define     NCP_NCAP_OPCQ_FC_RSP_CNT_IDX(addr) \
               (((addr) - NCP_NCAP_OPCQ_FC_RSP_CNT_BASE) / 4)    
#define     NCP_NCAP_OPCQ_FC_RSP_CNT_END                        (0x0001a510)
#define     NCP_NCAP_OPCQ_FC_RSP_CNT_RANGE(addr) \
            (((addr) >= NCP_NCAP_OPCQ_FC_RSP_CNT_BASE) && \
              ((addr) < NCP_NCAP_OPCQ_FC_RSP_CNT_END))

#define     NCP_NCAP_OPM_OPCQ_ENTRY_LL_FIFO_STATUS              (0x0001a800)
#define     NCP_NCAP_OPM_WENG_REQ_FIFO_STAT                     (0x0001a804)
#define     NCP_NCAP_OPM_WENG_WDB_FIFO_STAT                     (0x0001a808)
#define     NCP_NCAP_OPCQ_ENTRY_RENG_REQ_FIFO_STAT              (0x0001a80c)
#define     NCP_NCAP_OPM_PGITR_FIFO_STAT                        (0x0001a810)
#define     NCP_NCAP_OPM_PGITW_FIFO_STAT                        (0x0001a814)
#define     NCP_NCAP_OPM_BRSP_FIFO_STAT                         (0x0001a818)
#define     NCP_NCAP_OPM_ATFC_LL_FIFO_STATUS                    (0x0001a81c)
#define     NCP_NCAP_OPM_MOI_ADDR_FIFO_STAT                     (0x0001a820)
#define     NCP_NCAP_OPM_MOI_DATA_FIFO_STAT                     (0x0001a824)

#define     NCP_NCAP_OPCQ_ENTRY_RENG_MEM_RBF_FIFO_STAT_BASE     (0x0001a880)
#define     NCP_NCAP_OPCQ_ENTRY_RENG_MEM_RBF_FIFO_STAT(n)       (0x0001a880 + (4*(n)))
#define     NCP_NCAP_OPCQ_ENTRY_RENG_MEM_RBF_FIFO_STAT_COUNT    (0x00000010)
#define     NCP_NCAP_OPCQ_ENTRY_RENG_MEM_RBF_FIFO_STAT_IDX(addr) \
  (((addr) - NCP_NCAP_OPCQ_ENTRY_RENG_MEM_RBF_FIFO_STAT_BASE) / 4)
#define     NCP_NCAP_OPCQ_ENTRY_RENG_MEM_RBF_FIFO_STAT_END      (0x0001a8c0)
#define     NCP_NCAP_OPCQ_ENTRY_RENG_MEM_RBF_FIFO_STAT_RANGE(addr) \
 (((addr) >= NCP_NCAP_OPCQ_ENTRY_RENG_MEM_RBF_FIFO_STAT_BASE) && \
  ((addr) < NCP_NCAP_OPCQ_ENTRY_RENG_MEM_RBF_FIFO_STAT_END))


#define     NCP_NCAP_OPCQ_INDEX_UPDATE_FIFO_STATUS_FIFO_STAT_BASE  (0x0001a900)
#define     NCP_NCAP_OPCQ_INDEX_UPDATE_FIFO_STATUS_FIFO_STAT(n)  (0x0001a900 + (4*(n)))
#define     NCP_NCAP_OPCQ_INDEX_UPDATE_FIFO_STATUS_FIFO_STAT_COUNT  (0x00000010)
#define     NCP_NCAP_OPCQ_INDEX_UPDATE_FIFO_STATUS_FIFO_STAT_IDX(addr) \
  (((addr) - NCP_NCAP_OPCQ_INDEX_UPDATE_FIFO_STATUS_FIFO_STAT_BASE) / 4)
#define     NCP_NCAP_OPCQ_INDEX_UPDATE_FIFO_STATUS_FIFO_STAT_END  (0x0001a940)
#define     NCP_NCAP_OPCQ_INDEX_UPDATE_FIFO_STATUS_FIFO_STAT_RANGE(addr) \
 (((addr) >= NCP_NCAP_OPCQ_INDEX_UPDATE_FIFO_STATUS_FIFO_STAT_BASE) && \
  ((addr) < NCP_NCAP_OPCQ_INDEX_UPDATE_FIFO_STATUS_FIFO_STAT_END))

#define     NCP_NCAP_IPM_MII_PAR_GEN_POLARITY                   (0x0001b000)
#define     NCP_NCAP_IPM_MOI_PAR_CHK_POLARITY                   (0x0001b004)
#define     NCP_NCAP_IPM_NUM_BEATS_PER_BURST                    (0x0001b008)
#define     NCP_NCAP_IPCQ_ALMOST_FULL_VALUE                     (0x0001b00c)
#define     NCP_NCAP_IPCQ_ALMOST_EMPTY_VALUE                    (0x0001b010)
#define     NCP_NCAP_CONSIDER_IPCQ_ALMOST_EMPTY                 (0x0001b014)
#define     NCP_NCAP_IPCQ_CREDIT_MAX_VALUE                      (0x0001b018)
#define     NCP_NCAP_APCQ_NUM_ENTRIES_PER_REQUEST               (0x0001b01c)
#define     NCP_NCAP_IPM_MOI_WDATA_FLIP                         (0x0001b020)
#define     NCP_NCAP_IPM_GRP_RST_STATUS                         (0x0001b024)
#define     NCP_NCAP_APCQ_DESCR_ATFC_BITS                       (0x0001b028)
#define     NCP_NCAP_APCQ_DESCR_CMPLT_BITS                      (0x0001b02c)
#define     NCP_NCAP_APCQ_DESCR_CPA_BITS                        (0x0001b030)
#define     NCP_NCAP_IPM_MII_BAD_RESP_CNT                       (0x0001b200)
#define     NCP_NCAP_IPM_MOI_PARER_DETECT_CNT                   (0x0001b204)

#define     NCP_NCAP_IPM_MOI_PARER_DETECT_DATA_BASE             (0x0001b208)
#define     NCP_NCAP_IPM_MOI_PARER_DETECT_DATA(n)               (0x0001b208 + (4*(n)))
#define     NCP_NCAP_IPM_MOI_PARER_DETECT_DATA_COUNT            (0x00000004)
#define     NCP_NCAP_IPM_MOI_PARER_DETECT_DATA_IDX(addr) \
     (((addr) - NCP_NCAP_IPM_MOI_PARER_DETECT_DATA_BASE) / 4)
#define     NCP_NCAP_IPM_MOI_PARER_DETECT_DATA_END              (0x0001b218)
#define     NCP_NCAP_IPM_MOI_PARER_DETECT_DATA_RANGE(addr) \
  (((addr) >= NCP_NCAP_IPM_MOI_PARER_DETECT_DATA_BASE) && \
  ((addr) < NCP_NCAP_IPM_MOI_PARER_DETECT_DATA_END))

#define     NCP_NCAP_IPM_IPCQ_ENTRY_DROP_CNT                    (0x0001b218)

#define     NCP_NCAP_IPM_IPCQ_ENTRY_DROP_DATA_BASE              (0x0001b21c)
#define     NCP_NCAP_IPM_IPCQ_ENTRY_DROP_DATA(n)                (0x0001b21c + (4*(n)))
#define     NCP_NCAP_IPM_IPCQ_ENTRY_DROP_DATA_COUNT             (0x00000004)
#define     NCP_NCAP_IPM_IPCQ_ENTRY_DROP_DATA_IDX(addr) \
      (((addr) - NCP_NCAP_IPM_IPCQ_ENTRY_DROP_DATA_BASE) / 4)
#define     NCP_NCAP_IPM_IPCQ_ENTRY_DROP_DATA_END               (0x0001b22c)
#define     NCP_NCAP_IPM_IPCQ_ENTRY_DROP_DATA_RANGE(addr) \
   (((addr) >= NCP_NCAP_IPM_IPCQ_ENTRY_DROP_DATA_BASE) && \
   ((addr) < NCP_NCAP_IPM_IPCQ_ENTRY_DROP_DATA_END))

#define     NCP_NCAP_IPM_MOI_WRONG_ENDIAN_CNT                   (0x0001b22c)

#define     NCP_NCAP_IPM_MOI_WRONG_ENDIAN_DATA_BASE             (0x0001b230)
#define     NCP_NCAP_IPM_MOI_WRONG_ENDIAN_DATA(n)               (0x0001b230 + (4*(n)))
#define     NCP_NCAP_IPM_MOI_WRONG_ENDIAN_DATA_COUNT            (0x00000004)
#define     NCP_NCAP_IPM_MOI_WRONG_ENDIAN_DATA_IDX(addr) \
     (((addr) - NCP_NCAP_IPM_MOI_WRONG_ENDIAN_DATA_BASE) / 4)
#define     NCP_NCAP_IPM_MOI_WRONG_ENDIAN_DATA_END              (0x0001b240)
#define     NCP_NCAP_IPM_MOI_WRONG_ENDIAN_DATA_RANGE(addr) \
  (((addr) >= NCP_NCAP_IPM_MOI_WRONG_ENDIAN_DATA_BASE) && \
  ((addr) < NCP_NCAP_IPM_MOI_WRONG_ENDIAN_DATA_END))

#define     NCP_NCAP_IPM_CREDIT_OVERFLOW_CNT                    (0x0001b240)
#define     NCP_NCAP_IPM_IPCQ_ID_RAM_PARER_CNT                  (0x0001b244)

#define     NCP_NCAP_IPCQ_ENTRY_COUNTS_BASE                     (0x0001b280)
#define     NCP_NCAP_IPCQ_ENTRY_COUNTS(n)                       (0x0001b280 + (4*(n)))
#define     NCP_NCAP_IPCQ_ENTRY_COUNTS_COUNT                    (0x00000008)
#define     NCP_NCAP_IPCQ_ENTRY_COUNTS_IDX(addr) \
             (((addr) - NCP_NCAP_IPCQ_ENTRY_COUNTS_BASE) / 4)  
#define     NCP_NCAP_IPCQ_ENTRY_COUNTS_END                      (0x0001b2a0)
#define     NCP_NCAP_IPCQ_ENTRY_COUNTS_RANGE(addr) \
          (((addr) >= NCP_NCAP_IPCQ_ENTRY_COUNTS_BASE) && \
          ((addr) < NCP_NCAP_IPCQ_ENTRY_COUNTS_END))


#define     NCP_NCAP_IPCQ_ENTRY_COUNTS_COR_BASE                 (0x0001b300)
#define     NCP_NCAP_IPCQ_ENTRY_COUNTS_COR(n)                   (0x0001b300 + (4*(n)))
#define     NCP_NCAP_IPCQ_ENTRY_COUNTS_COR_COUNT                (0x00000008)
#define     NCP_NCAP_IPCQ_ENTRY_COUNTS_COR_IDX(addr) \
         (((addr) - NCP_NCAP_IPCQ_ENTRY_COUNTS_COR_BASE) / 4)
#define     NCP_NCAP_IPCQ_ENTRY_COUNTS_COR_END                  (0x0001b320)
#define     NCP_NCAP_IPCQ_ENTRY_COUNTS_COR_RANGE(addr) \
      (((addr) >= NCP_NCAP_IPCQ_ENTRY_COUNTS_COR_BASE) && \
      ((addr) < NCP_NCAP_IPCQ_ENTRY_COUNTS_COR_END))

#define     NCP_NCAP_GET_APCQ_ENTRY_STATE                       (0x0001b400)
#define     NCP_NCAP_IPM_IPCQ_STATE                             (0x0001b404)
#define     NCP_NCAP_IPM_APCQ_STATE                             (0x0001b408)
#define     NCP_NCAP_IPM_READ_WRITE_ENGINE_STATE                (0x0001b40c)
#define     NCP_NCAP_IPM_MII_STATE                              (0x0001b410)
#define     NCP_NCAP_IPM_OUTSTAND_ENTRY_WR_CNTS                 (0x0001b414)

#define     NCP_NCAP_IPCQ_NUM_ENTRIES_OUTSTANDING_BASE          (0x0001b480)
#define     NCP_NCAP_IPCQ_NUM_ENTRIES_OUTSTANDING(n)            (0x0001b480 + (4*(n)))
#define     NCP_NCAP_IPCQ_NUM_ENTRIES_OUTSTANDING_COUNT         (0x00000002)
#define     NCP_NCAP_IPCQ_NUM_ENTRIES_OUTSTANDING_IDX(addr) \
  (((addr) - NCP_NCAP_IPCQ_NUM_ENTRIES_OUTSTANDING_BASE) / 4)
#define     NCP_NCAP_IPCQ_NUM_ENTRIES_OUTSTANDING_END           (0x0001b488)
#define     NCP_NCAP_IPCQ_NUM_ENTRIES_OUTSTANDING_RANGE(addr) \
 (((addr) >= NCP_NCAP_IPCQ_NUM_ENTRIES_OUTSTANDING_BASE) && \
  ((addr) < NCP_NCAP_IPCQ_NUM_ENTRIES_OUTSTANDING_END))


#define     NCP_NCAP_APCQ_NUM_ENTRIES_OUTSTANDING_BASE          (0x0001b4a0)
#define     NCP_NCAP_APCQ_NUM_ENTRIES_OUTSTANDING(n)            (0x0001b4a0 + (4*(n)))
#define     NCP_NCAP_APCQ_NUM_ENTRIES_OUTSTANDING_COUNT         (0x00000002)
#define     NCP_NCAP_APCQ_NUM_ENTRIES_OUTSTANDING_IDX(addr) \
  (((addr) - NCP_NCAP_APCQ_NUM_ENTRIES_OUTSTANDING_BASE) / 4)
#define     NCP_NCAP_APCQ_NUM_ENTRIES_OUTSTANDING_END           (0x0001b4a8)
#define     NCP_NCAP_APCQ_NUM_ENTRIES_OUTSTANDING_RANGE(addr) \
 (((addr) >= NCP_NCAP_APCQ_NUM_ENTRIES_OUTSTANDING_BASE) && \
  ((addr) < NCP_NCAP_APCQ_NUM_ENTRIES_OUTSTANDING_END))

#define     NCP_NCAP_IPM_WENG_REQ_FIFO_STAT                     (0x0001b800)
#define     NCP_NCAP_IPM_WENG_WDB_FIFO_STAT                     (0x0001b804)
#define     NCP_NCAP_IPCQ_PGITR_FIFO_STAT                       (0x0001b808)
#define     NCP_NCAP_IPCQ_PGITW_FIFO_STAT                       (0x0001b80c)
#define     NCP_NCAP_APCQ_PGITR_FIFO_STAT                       (0x0001b810)
#define     NCP_NCAP_APCQ_PGITW_FIFO_STAT                       (0x0001b814)
#define     NCP_NCAP_IPM_BRSP_FIFO_STAT                         (0x0001b818)
#define     NCP_NCAP_IPM_MOI_ADDR_FIFO_STAT                     (0x0001b81c)
#define     NCP_NCAP_IPM_MOI_DATA_FIFO_STAT                     (0x0001b820)
#define     NCP_NCAP_IPM_IPCQ_ENTRY_LL_FIFO_STATUS              (0x0001b824)

#define     NCP_NCAP_IPCQ_ENTRY_BUFFER_FIFO_STATUS_FIFO_STAT_BASE  (0x0001b880)
#define     NCP_NCAP_IPCQ_ENTRY_BUFFER_FIFO_STATUS_FIFO_STAT(n)  (0x0001b880 + (4*(n)))
#define     NCP_NCAP_IPCQ_ENTRY_BUFFER_FIFO_STATUS_FIFO_STAT_COUNT  (0x00000008)
#define     NCP_NCAP_IPCQ_ENTRY_BUFFER_FIFO_STATUS_FIFO_STAT_IDX(addr) \
  (((addr) - NCP_NCAP_IPCQ_ENTRY_BUFFER_FIFO_STATUS_FIFO_STAT_BASE) / 4)
#define     NCP_NCAP_IPCQ_ENTRY_BUFFER_FIFO_STATUS_FIFO_STAT_END  (0x0001b8a0)
#define     NCP_NCAP_IPCQ_ENTRY_BUFFER_FIFO_STATUS_FIFO_STAT_RANGE(addr) \
 (((addr) >= NCP_NCAP_IPCQ_ENTRY_BUFFER_FIFO_STATUS_FIFO_STAT_BASE) && \
  ((addr) < NCP_NCAP_IPCQ_ENTRY_BUFFER_FIFO_STATUS_FIFO_STAT_END))

#define     NCP_NCAP_MPM_MII_PAR_GEN_POLARITY                   (0x0001c000)
#define     NCP_NCAP_MPM_MOI_PAR_CHK_POLARITY                   (0x0001c004)
#define     NCP_NCAP_MPM_NUM_BEATS_PER_BURST                    (0x0001c008)
#define     NCP_NCAP_MPB_REQ_STALL_CNT_VALUE                    (0x0001c00c)
#define     NCP_NCAP_MPB_REQ_SEND_CREDIT_MAX_VALUE              (0x0001c010)
#define     NCP_NCAP_MPB_REQ_SEND_CREDITS                       (0x0001c014)
#define     NCP_NCAP_MPM_MOI_WDATA_FLIP                         (0x0001c018)
#define     NCP_NCAP_MPM_GRP_RST_STATUS                         (0x0001c01c)
#define     NCP_NCAP_MPM_MII_BAD_RESP_CNT                       (0x0001c200)
#define     NCP_NCAP_MPM_MOI_PARER_DETECT_CNT                   (0x0001c204)

#define     NCP_NCAP_MPM_MOI_PARER_DETECT_DATA_BASE             (0x0001c208)
#define     NCP_NCAP_MPM_MOI_PARER_DETECT_DATA(n)               (0x0001c208 + (4*(n)))
#define     NCP_NCAP_MPM_MOI_PARER_DETECT_DATA_COUNT            (0x00000004)
#define     NCP_NCAP_MPM_MOI_PARER_DETECT_DATA_IDX(addr) \
     (((addr) - NCP_NCAP_MPM_MOI_PARER_DETECT_DATA_BASE) / 4)
#define     NCP_NCAP_MPM_MOI_PARER_DETECT_DATA_END              (0x0001c218)
#define     NCP_NCAP_MPM_MOI_PARER_DETECT_DATA_RANGE(addr) \
  (((addr) >= NCP_NCAP_MPM_MOI_PARER_DETECT_DATA_BASE) && \
  ((addr) < NCP_NCAP_MPM_MOI_PARER_DETECT_DATA_END))

#define     NCP_NCAP_MPM_SEND_CREDIT_OVFL_CNT                   (0x0001c218)
#define     NCP_NCAP_MPM_NUM_CREDITS_BEFORE_OVFL                (0x0001c21c)
#define     NCP_NCAP_MPM_BUFFER_REQ_COUNT                       (0x0001c220)
#define     NCP_NCAP_MPM_BUFFER_REQ_COUNT_COR                   (0x0001c224)
#define     NCP_NCAP_MPM_BUFFER_NACK_COUNT                      (0x0001c228)
#define     NCP_NCAP_MPM_BUFFER_NACK_COUNT_COR                  (0x0001c22c)
#define     NCP_NCAP_MPM_BUFFER_DROP_FIFO_FULL_CNT              (0x0001c230)

#define     NCP_NCAP_MPM_BUFFER_DROP_DATA_BASE                  (0x0001c234)
#define     NCP_NCAP_MPM_BUFFER_DROP_DATA(n)                    (0x0001c234 + (4*(n)))
#define     NCP_NCAP_MPM_BUFFER_DROP_DATA_COUNT                 (0x00000004)
#define     NCP_NCAP_MPM_BUFFER_DROP_DATA_IDX(addr) \
          (((addr) - NCP_NCAP_MPM_BUFFER_DROP_DATA_BASE) / 4)
#define     NCP_NCAP_MPM_BUFFER_DROP_DATA_END                   (0x0001c244)
#define     NCP_NCAP_MPM_BUFFER_DROP_DATA_RANGE(addr) \
       (((addr) >= NCP_NCAP_MPM_BUFFER_DROP_DATA_BASE) && \
       ((addr) < NCP_NCAP_MPM_BUFFER_DROP_DATA_END))

#define     NCP_NCAP_MPM_BUFFER_DROP_REQ_ADDR_ER_CNT            (0x0001c244)

#define     NCP_NCAP_MPM_BUFFER_DROP_REQ_ADDR_ER_DATA_BASE      (0x0001c248)
#define     NCP_NCAP_MPM_BUFFER_DROP_REQ_ADDR_ER_DATA(n)        (0x0001c248 + (4*(n)))
#define     NCP_NCAP_MPM_BUFFER_DROP_REQ_ADDR_ER_DATA_COUNT     (0x00000004)
#define     NCP_NCAP_MPM_BUFFER_DROP_REQ_ADDR_ER_DATA_IDX(addr) \
  (((addr) - NCP_NCAP_MPM_BUFFER_DROP_REQ_ADDR_ER_DATA_BASE) / 4)
#define     NCP_NCAP_MPM_BUFFER_DROP_REQ_ADDR_ER_DATA_END       (0x0001c258)
#define     NCP_NCAP_MPM_BUFFER_DROP_REQ_ADDR_ER_DATA_RANGE(addr) \
 (((addr) >= NCP_NCAP_MPM_BUFFER_DROP_REQ_ADDR_ER_DATA_BASE) && \
  ((addr) < NCP_NCAP_MPM_BUFFER_DROP_REQ_ADDR_ER_DATA_END))

#define     NCP_NCAP_MPM_MPCQ_STATE                             (0x0001c400)
#define     NCP_NCAP_MPM_WRITE_ENGINE_STATE                     (0x0001c404)
#define     NCP_NCAP_MPM_MII_STATE                              (0x0001c408)
#define     NCP_NCAP_MPM_OUTSTAND_MBWS_CNTS                     (0x0001c40c)
#define     NCP_NCAP_MPM_WENG_REQ_FIFO_STAT                     (0x0001c800)
#define     NCP_NCAP_MPM_WENG_WDB_FIFO_STAT                     (0x0001c804)
#define     NCP_NCAP_MPCQ_PGITR_FIFO_STAT                       (0x0001c808)
#define     NCP_NCAP_MPCQ_PGITW_FIFO_STAT                       (0x0001c80c)
#define     NCP_NCAP_MPM_RSP_FIFO_STAT                          (0x0001c810)
#define     NCP_NCAP_MPM_BRSP_FIFO_STAT                         (0x0001c814)
#define     NCP_NCAP_MPM_REQ_LL_FIFO_STATUS                     (0x0001c818)
#define     NCP_NCAP_MPM_MOI_ADDR_FIFO_STAT                     (0x0001c81c)
#define     NCP_NCAP_MPM_MOI_DATA_FIFO_STAT                     (0x0001c820)

#define     NCP_NCAP_MPCQ_NUM_ENTRIES_OUTSTANDING_BASE          (0x0001cc00)
#define     NCP_NCAP_MPCQ_NUM_ENTRIES_OUTSTANDING(n)            (0x0001cc00 + (4*(n)))
#define     NCP_NCAP_MPCQ_NUM_ENTRIES_OUTSTANDING_COUNT         (0x00000030)
#define     NCP_NCAP_MPCQ_NUM_ENTRIES_OUTSTANDING_IDX(addr) \
  (((addr) - NCP_NCAP_MPCQ_NUM_ENTRIES_OUTSTANDING_BASE) / 4)
#define     NCP_NCAP_MPCQ_NUM_ENTRIES_OUTSTANDING_END           (0x0001ccc0)
#define     NCP_NCAP_MPCQ_NUM_ENTRIES_OUTSTANDING_RANGE(addr) \
 (((addr) >= NCP_NCAP_MPCQ_NUM_ENTRIES_OUTSTANDING_BASE) && \
  ((addr) < NCP_NCAP_MPCQ_NUM_ENTRIES_OUTSTANDING_END))


#define     NCP_NCAP_MPCQ_ENTRY_COUNTS_BASE                     (0x0001d000)
#define     NCP_NCAP_MPCQ_ENTRY_COUNTS(n)                       (0x0001d000 + (4*(n)))
#define     NCP_NCAP_MPCQ_ENTRY_COUNTS_COUNT                    (0x000000c0)
#define     NCP_NCAP_MPCQ_ENTRY_COUNTS_IDX(addr) \
             (((addr) - NCP_NCAP_MPCQ_ENTRY_COUNTS_BASE) / 4)  
#define     NCP_NCAP_MPCQ_ENTRY_COUNTS_END                      (0x0001d300)
#define     NCP_NCAP_MPCQ_ENTRY_COUNTS_RANGE(addr) \
          (((addr) >= NCP_NCAP_MPCQ_ENTRY_COUNTS_BASE) && \
          ((addr) < NCP_NCAP_MPCQ_ENTRY_COUNTS_END))


#define     NCP_NCAP_MPCQ_ENTRY_COUNTS_COR_BASE                 (0x0001d400)
#define     NCP_NCAP_MPCQ_ENTRY_COUNTS_COR(n)                   (0x0001d400 + (4*(n)))
#define     NCP_NCAP_MPCQ_ENTRY_COUNTS_COR_COUNT                (0x000000c0)
#define     NCP_NCAP_MPCQ_ENTRY_COUNTS_COR_IDX(addr) \
         (((addr) - NCP_NCAP_MPCQ_ENTRY_COUNTS_COR_BASE) / 4)
#define     NCP_NCAP_MPCQ_ENTRY_COUNTS_COR_END                  (0x0001d700)
#define     NCP_NCAP_MPCQ_ENTRY_COUNTS_COR_RANGE(addr) \
      (((addr) >= NCP_NCAP_MPCQ_ENTRY_COUNTS_COR_BASE) && \
      ((addr) < NCP_NCAP_MPCQ_ENTRY_COUNTS_COR_END))


#define     NCP_NCAP_MPCQ_OUTSTAND_BUF_REQS_BASE                (0x0001d800)
#define     NCP_NCAP_MPCQ_OUTSTAND_BUF_REQS(n)                  (0x0001d800 + (4*(n)))
#define     NCP_NCAP_MPCQ_OUTSTAND_BUF_REQS_COUNT               (0x00000030)
#define     NCP_NCAP_MPCQ_OUTSTAND_BUF_REQS_IDX(addr) \
        (((addr) - NCP_NCAP_MPCQ_OUTSTAND_BUF_REQS_BASE) / 4)
#define     NCP_NCAP_MPCQ_OUTSTAND_BUF_REQS_END                 (0x0001d8c0)
#define     NCP_NCAP_MPCQ_OUTSTAND_BUF_REQS_RANGE(addr) \
     (((addr) >= NCP_NCAP_MPCQ_OUTSTAND_BUF_REQS_BASE) && \
     ((addr) < NCP_NCAP_MPCQ_OUTSTAND_BUF_REQS_END))

#define     NCP_NCAP_PGIT_MEM_PAR_CHK_POLARITY                  (0x0001e000)
#define     NCP_NCAP_PGIT_MEM_PAR_GEN_POLARITY                  (0x0001e004)
#define     NCP_NCAP_PGITM_NUM_BEATS_PER_BURST                  (0x0001e008)
#define     NCP_NCAP_PGITM_GRP_RST_STATUS                       (0x0001e00c)
#define     NCP_NCAP_PGIT_READ_WRITE_ENGINE_STATE               (0x0001e200)
#define     NCP_NCAP_PGIT_SEL_AND_UPLOAD_STATE                  (0x0001e204)
#define     NCP_NCAP_PGIT_ACCESS_STATE                          (0x0001e208)
#define     NCP_NCAP_PGIT_WENG_REQ_FIFO_STAT                    (0x0001e400)
#define     NCP_NCAP_PGIT_WENG_WDB_FIFO_STAT                    (0x0001e404)
#define     NCP_NCAP_PGIT_RENG_REQ_FIFO_STAT                    (0x0001e408)

#define     NCP_NCAP_PGIT_RENG_MEM_RBF_FIFO_STAT_BASE           (0x0001e480)
#define     NCP_NCAP_PGIT_RENG_MEM_RBF_FIFO_STAT(n)             (0x0001e480 + (4*(n)))
#define     NCP_NCAP_PGIT_RENG_MEM_RBF_FIFO_STAT_COUNT          (0x0000000c)
#define     NCP_NCAP_PGIT_RENG_MEM_RBF_FIFO_STAT_IDX(addr) \
   (((addr) - NCP_NCAP_PGIT_RENG_MEM_RBF_FIFO_STAT_BASE) / 4)
#define     NCP_NCAP_PGIT_RENG_MEM_RBF_FIFO_STAT_END            (0x0001e4b0)
#define     NCP_NCAP_PGIT_RENG_MEM_RBF_FIFO_STAT_RANGE(addr) \
 (((addr) >= NCP_NCAP_PGIT_RENG_MEM_RBF_FIFO_STAT_BASE) && \
  ((addr) < NCP_NCAP_PGIT_RENG_MEM_RBF_FIFO_STAT_END))

#define     NCP_NCAP_GIC_CTRL                                   (0x0001f000)
#define     NCP_NCAP_INT_OUTPUT_MODE                            (0x0001f008)
#define     NCP_NCAP_EDGET_INT_PL                               (0x0001f00c)
#define     NCP_NCAP_CONFIG_INIT_WOCLR                          (0x0001f200)
#define     NCP_NCAP_HW_POKE_AND_TIMER_ENABLE_WOCLR             (0x0001f210)
#define     NCP_NCAP_GRP_LOAD_POKE_ENABLE_WOCLR                 (0x0001f220)
#define     NCP_NCAP_GRP_LOAD_TIMER_ENABLE_WOCLR                (0x0001f224)
#define     NCP_NCAP_GRP_UPLOAD_POKE_ENABLE_WOCLR               (0x0001f228)
#define     NCP_NCAP_GRP_UPLOAD_TIMER_ENABLE_WOCLR              (0x0001f22c)
#define     NCP_NCAP_GIC_CTRL_WOCLR                             (0x0001f238)
#define     NCP_NCAP_CONFIG_INIT_WOSET                          (0x0001f300)
#define     NCP_NCAP_HW_POKE_AND_TIMER_ENABLE_WOSET             (0x0001f310)
#define     NCP_NCAP_GRP_LOAD_POKE_ENABLE_WOSET                 (0x0001f320)
#define     NCP_NCAP_GRP_LOAD_TIMER_ENABLE_WOSET                (0x0001f324)
#define     NCP_NCAP_GRP_UPLOAD_POKE_ENABLE_WOSET               (0x0001f328)
#define     NCP_NCAP_GRP_UPLOAD_TIMER_ENABLE_WOSET              (0x0001f32c)
#define     NCP_NCAP_PGIT_SOFTWARE_LOAD_POKE_REG_WOSET          (0x0001f330)
#define     NCP_NCAP_GIC_CTRL_WOSET                             (0x0001f338)
#define     NCP_NCAP_PCQ_INIT_TABLE_GRP_PCQ_GRP_R0(n)           (0x00010400 + (32*(n)))
#define     NCP_NCAP_PCQ_INIT_TABLE_GRP_PCQ_GRP_R1(n)           (0x00010404 + (32*(n)))
#define     NCP_NCAP_PCQ_INIT_TABLE_GRP_PCQ_GRP_R2(n)           (0x00010408 + (32*(n)))
#define     NCP_NCAP_PCQ_INIT_TABLE_GRP_PCQ_GRP_R3(n)           (0x0001040c + (32*(n)))
#define     NCP_NCAP_PCQ_INIT_TABLE_GRP_PCQ_GRP_R4(n)           (0x00010410 + (32*(n)))
#define     NCP_NCAP_PCQ_DESC_IPCQ_R0(n)                        (0x00011000 + (16*(n)))
#define     NCP_NCAP_PCQ_DESC_IPCQ_R1(n)                        (0x00011004 + (16*(n)))
#define     NCP_NCAP_PCQ_DESC_IPCQ_R2(n)                        (0x00011008 + (16*(n)))
#define     NCP_NCAP_PCQ_DESC_IPCQ_R3(n)                        (0x0001100c + (16*(n)))
#define     NCP_NCAP_PCQ_STAT_IPCQ_R0(n)                        (0x00011400 + (8*(n)))
#define     NCP_NCAP_PCQ_STAT_IPCQ_R1(n)                        (0x00011404 + (8*(n)))
#define     NCP_NCAP_PCQ_DESC_APCQ_R0(n)                        (0x00011800 + (16*(n)))
#define     NCP_NCAP_PCQ_DESC_APCQ_R1(n)                        (0x00011804 + (16*(n)))
#define     NCP_NCAP_PCQ_DESC_APCQ_R2(n)                        (0x00011808 + (16*(n)))
#define     NCP_NCAP_PCQ_DESC_APCQ_R3(n)                        (0x0001180c + (16*(n)))
#define     NCP_NCAP_PCQ_STAT_APCQ_R0(n)                        (0x00011c00 + (8*(n)))
#define     NCP_NCAP_PCQ_STAT_APCQ_R1(n)                        (0x00011c04 + (8*(n)))
#define     NCP_NCAP_PCQ_DESC_OPCQ_R0(n)                        (0x00012000 + (16*(n)))
#define     NCP_NCAP_PCQ_DESC_OPCQ_R1(n)                        (0x00012004 + (16*(n)))
#define     NCP_NCAP_PCQ_DESC_OPCQ_R2(n)                        (0x00012008 + (16*(n)))
#define     NCP_NCAP_PCQ_DESC_OPCQ_R3(n)                        (0x0001200c + (16*(n)))
#define     NCP_NCAP_PCQ_STAT_OPCQ_R0(n)                        (0x00012800 + (8*(n)))
#define     NCP_NCAP_PCQ_STAT_OPCQ_R1(n)                        (0x00012804 + (8*(n)))
#define     NCP_NCAP_PCQ_DESC_MPCQ_R0(n)                        (0x00014000 + (16*(n)))
#define     NCP_NCAP_PCQ_DESC_MPCQ_R1(n)                        (0x00014004 + (16*(n)))
#define     NCP_NCAP_PCQ_DESC_MPCQ_R2(n)                        (0x00014008 + (16*(n)))
#define     NCP_NCAP_PCQ_DESC_MPCQ_R3(n)                        (0x0001400c + (16*(n)))
#define     NCP_NCAP_PCQ_STAT_MPCQ_R0(n)                        (0x00016000 + (8*(n)))
#define     NCP_NCAP_PCQ_STAT_MPCQ_R1(n)                        (0x00016004 + (8*(n)))
#if 0
#define     NCP_NCAP_PARAMETERS_NUM_PCQ_GROUPS                  (0x00018800)
#endif
#define     NCP_NCAP_PARAMETERS_NUM_MPC_QUEUES                  (0x00018804)
#define     NCP_NCAP_PARAMETERS_NUM_OPC_QUEUES                  (0x00018808)
#define     NCP_NCAP_PARAMETERS_NUM_IPC_QUEUES                  (0x0001880c)
#define     NCP_NCAP_PARAMETERS_NUM_CPU_INTERRUPTS              (0x00018810)
#define     NCP_NCAP_PARAMETERS_NUM_HW_INTERRUPTS               (0x00018814)
#define     NCP_NCAP_PARAMETERS_ACP_NUM_RIDS_WIDTH              (0x00018818)
#define     NCP_NCAP_PARAMETERS_ACP_NUM_WIDS_WIDTH              (0x0001881c)
#define     NCP_NCAP_PARAMETERS_ACP_ADDR_WIDTH_REG              (0x00018820)
#define     NCP_NCAP_PARAMETERS_OPCQ_NLINK_CREDITS              (0x00018824)
#define     NCP_NCAP_PARAMETERS_IPCQ_NLINK_CREDITS              (0x00018828)
#define     NCP_NCAP_PARAMETERS_MPCQ_NLINK_CREDITS              (0x0001882c)
#define     NCP_NCAP_PARAMETERS_NUM_PCQ_GROUPS                  (0x00018830)
#define     NCP_NCAP_PARAMETERS_NUM_PCQ_GROUPS_WIDTH            (0x00018834)
#define     NCP_NCAP_PARAMETERS_VI_WIDTH                        (0x00018838)
#define     NCP_NCAP_PARAMETERS_NUM_MEM_POOLS                   (0x0001883c)
#define     NCP_NCAP_PARAMETERS_NUM_MEM_POOLS_WIDTH             (0x00018840)
#define     NCP_NCAP_PARAMETERS_POOLID_WIDTH                    (0x00018844)
#define     NCP_NCAP_PARAMETERS_NCAPD_OPTIONS                   (0x00018848)
#define     NCP_NCAP_OPM_HWM_OPCQ_ENTRY_LL_FIFO_HWM             (0x0001ac00)
#define     NCP_NCAP_OPM_HWM_WENG_REQ_FIFO_HWM                  (0x0001ac04)
#define     NCP_NCAP_OPM_HWM_WENG_WDB_FIFO_HWM                  (0x0001ac08)
#define     NCP_NCAP_OPM_HWM_OPCQ_ENTRY_RENG_REQ_FIFO_HWM       (0x0001ac0c)
#define     NCP_NCAP_OPM_HWM_PCQ_PGITR_FIFO_HWM                 (0x0001ac10)
#define     NCP_NCAP_OPM_HWM_PCQ_PGITW_FIFO_HWM                 (0x0001ac14)
#define     NCP_NCAP_OPM_HWM_BRSP_FIFO_HWM                      (0x0001ac18)
#define     NCP_NCAP_OPM_HWM_ATFC_LL_FIFO_HWM                   (0x0001ac1c)
#define     NCP_NCAP_OPM_HWM_MOI_ADDR_FIFO_HWM                  (0x0001ac20)
#define     NCP_NCAP_OPM_HWM_MOI_DATA_FIFO_HWM                  (0x0001ac24)
#define     NCP_NCAP_IPM_HWM_WENG_REQ_FIFO_HWM                  (0x0001bc00)
#define     NCP_NCAP_IPM_HWM_WENG_WDB_FIFO_HWM                  (0x0001bc04)
#define     NCP_NCAP_IPM_HWM_IPCQ_PGITR_FIFO_HWM                (0x0001bc08)
#define     NCP_NCAP_IPM_HWM_IPCQ_PGITW_FIFO_HWM                (0x0001bc0c)
#define     NCP_NCAP_IPM_HWM_APCQ_PGITR_FIFO_HWM                (0x0001bc10)
#define     NCP_NCAP_IPM_HWM_APCQ_PGITW_FIFO_HWM                (0x0001bc14)
#define     NCP_NCAP_IPM_HWM_BRSP_FIFO_HWM                      (0x0001bc18)
#define     NCP_NCAP_IPM_HWM_MOI_DATA_FIFO_HWM                  (0x0001bc1c)
#define     NCP_NCAP_IPM_HWM_IPCQ_ENTRY_BUF_FIFO_HWM            (0x0001bc20)
#define     NCP_NCAP_MPM_HWM_REG_WENG_REQ_FIFO_HWM              (0x0001ca00)
#define     NCP_NCAP_MPM_HWM_REG_WENG_WDB_FIFO_HWM              (0x0001ca04)
#define     NCP_NCAP_MPM_HWM_REG_MPCQ_PGITR_FIFO_HWM            (0x0001ca08)
#define     NCP_NCAP_MPM_HWM_REG_MPCQ_PGITW_FIFO_HWM            (0x0001ca0c)
#define     NCP_NCAP_MPM_HWM_REG_RSP_FIFO_HWM                   (0x0001ca10)
#define     NCP_NCAP_MPM_HWM_REG_BRSP_FIFO_HWM                  (0x0001ca14)
#define     NCP_NCAP_MPM_HWM_REG_MPB_REQ_LL_FIFO_HWM            (0x0001ca18)
#define     NCP_NCAP_MPM_HWM_REG_MOI_ADDR_FIFO_HWM              (0x0001ca1c)
#define     NCP_NCAP_MPM_HWM_REG_MOI_DATA_FIFO_HWM              (0x0001ca20)
#define     NCP_NCAP_PGIT_READ_WRITE_ENGINE_HWM_WENG_REQ_FIFO_HWM  (0x0001e600)
#define     NCP_NCAP_PGIT_READ_WRITE_ENGINE_HWM_WENG_WDB_FIFO_HWM  (0x0001e604)
#define     NCP_NCAP_PGIT_READ_WRITE_ENGINE_HWM_RENG_REQ_FIFO_HWM  (0x0001e608)
#define     NCP_NCAP_DRIVING_INT_STATUS_TABLE_R0                (0x0001f010)
#define     NCP_NCAP_DRIVING_INT_STATUS_TABLE_R0_SERVICE_MASK   (0x00ff00ff)
#define     NCP_NCAP_DRIVING_INT_STATUS_TABLE_R1                (0x0001f014)
#define     NCP_NCAP_DRIVING_INT_STATUS_TABLE_R1_ALARM_MASK     (0x007fffff)
#define     NCP_NCAP_GRP_INTERRUPT_STATUS_TABLE_STATUS_R0       (0x0001f020)
#define     NCP_NCAP_GRP_INTERRUPT_STATUS_TABLE_STATUS_R0_SERVICE_MASK  (0x00ff00ff)
#define     NCP_NCAP_GRP_INTERRUPT_STATUS_TABLE_STATUS_R1       (0x0001f024)
#define     NCP_NCAP_GRP_INTERRUPT_STATUS_TABLE_STATUS_R1_ALARM_MASK  (0x007fffff)
#define     NCP_NCAP_GRP_INTERRUPT_ENABLE_TABLE_EN_R0           (0x0001f030)
#define     NCP_NCAP_GRP_INTERRUPT_ENABLE_TABLE_EN_R0_SERVICE_MASK  (0x00ff00ff)
#define     NCP_NCAP_GRP_INTERRUPT_ENABLE_TABLE_EN_R1           (0x0001f034)
#define     NCP_NCAP_GRP_INTERRUPT_ENABLE_TABLE_EN_R1_ALARM_MASK  (0x007fffff)
#define     NCP_NCAP_GRP_INTERRUPT_FORCE_TABLE_FRC_R0           (0x0001f040)
#define     NCP_NCAP_GRP_INTERRUPT_FORCE_TABLE_FRC_R0_SERVICE_MASK  (0x00ff00ff)
#define     NCP_NCAP_GRP_INTERRUPT_FORCE_TABLE_FRC_R1           (0x0001f044)
#define     NCP_NCAP_GRP_INTERRUPT_FORCE_TABLE_FRC_R1_ALARM_MASK  (0x007fffff)
#define     NCP_NCAP_GRP_INTERRUPT_ENABLE_TABLE_WOCLR_EN_R0_WOCLR  (0x0001f240)
#define     NCP_NCAP_GRP_INTERRUPT_ENABLE_TABLE_WOCLR_EN_R0_WOCLR_SERVICE_MASK  (0x00ff00ff)
#define     NCP_NCAP_GRP_INTERRUPT_ENABLE_TABLE_WOCLR_EN_R1_WOCLR  (0x0001f244)
#define     NCP_NCAP_GRP_INTERRUPT_ENABLE_TABLE_WOCLR_EN_R1_WOCLR_ALARM_MASK  (0x007fffff)
#define     NCP_NCAP_GRP_INTERRUPT_ENABLE_TABLE_WOSET_EN_R0_WOSET  (0x0001f340)
#define     NCP_NCAP_GRP_INTERRUPT_ENABLE_TABLE_WOSET_EN_R0_WOSET_SERVICE_MASK  (0x00ff00ff)
#define     NCP_NCAP_GRP_INTERRUPT_ENABLE_TABLE_WOSET_EN_R1_WOSET  (0x0001f344)
#define     NCP_NCAP_GRP_INTERRUPT_ENABLE_TABLE_WOSET_EN_R1_WOSET_ALARM_MASK  (0x007fffff)

#define     NCP_NCAP_CAAL_NCAP_MEM_BASE                         (0x00000000)
#define     NCP_NCAP_CAAL_NCAP_MEM_END                          (0x00002000)
#define     NCP_NCAP_CAAL_NCAP_MEM_RANGE(addr) \
              (((addr) >= NCP_NCAP_CAAL_NCAP_MEM_BASE) && \
                  ((addr) < NCP_NCAP_CAAL_NCAP_MEM_END))

#ifdef __cplusplus
}
#endif

#endif /* _NCP_NCAP_REG_DEFINES_H_ */
