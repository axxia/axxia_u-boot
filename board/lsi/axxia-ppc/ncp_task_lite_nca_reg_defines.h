/*
 *  Copyright (C) 2011 LSI Corporation
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */


#ifndef _NCP_NCA_REG_DEFINES_H_
#define _NCP_NCA_REG_DEFINES_H_

#ifdef __cplusplus
extern "C" {
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

#define     NCP_NCA_CONFIG_INIT                                 (0x00000028)
#define     NCP_NCA_CONFIG_INIT_V3                              (0x00000028)
#define     NCP_NCA_CONFIG_INIT_ACP2500                         (0x00000028)
#define     NCP_NCA_PCQ_KICKSTART                               (0x0000002c)
#define     NCP_NCA_PGIT_LOAD_GRP_INDEXES                       (0x00000030)
#define     NCP_NCA_HW_POKE_AND_TIMER_ENABLE                    (0x00000034)
#define     NCP_NCA_HW_UPLOAD_POKE_FLAGS                        (0x00000038)

#define     NCP_NCA_PGIT_GRP_LOAD_TIMER_BASE                    (0x00000040)
#define     NCP_NCA_PGIT_GRP_LOAD_TIMER(n)                      (0x00000040 + (4*(n)))
#define     NCP_NCA_PGIT_GRP_LOAD_TIMER_COUNT                   (0x00000006)
#define     NCP_NCA_PGIT_GRP_LOAD_TIMER_IDX(addr) \
            (((addr) - NCP_NCA_PGIT_GRP_LOAD_TIMER_BASE) / 4) 
#define     NCP_NCA_PGIT_GRP_LOAD_TIMER_END                     (0x00000058)
#define     NCP_NCA_PGIT_GRP_LOAD_TIMER_RANGE(addr) \
         (((addr) >= NCP_NCA_PGIT_GRP_LOAD_TIMER_BASE) && \
         ((addr) < NCP_NCA_PGIT_GRP_LOAD_TIMER_END))


#define     NCP_NCA_PGIT_GRP_UPLOAD_TIMER_BASE                  (0x00000058)
#define     NCP_NCA_PGIT_GRP_UPLOAD_TIMER(n)                    (0x00000058 + (4*(n)))
#define     NCP_NCA_PGIT_GRP_UPLOAD_TIMER_COUNT                 (0x00000006)
#define     NCP_NCA_PGIT_GRP_UPLOAD_TIMER_IDX(addr) \
          (((addr) - NCP_NCA_PGIT_GRP_UPLOAD_TIMER_BASE) / 4)
#define     NCP_NCA_PGIT_GRP_UPLOAD_TIMER_END                   (0x00000070)
#define     NCP_NCA_PGIT_GRP_UPLOAD_TIMER_RANGE(addr) \
       (((addr) >= NCP_NCA_PGIT_GRP_UPLOAD_TIMER_BASE) && \
       ((addr) < NCP_NCA_PGIT_GRP_UPLOAD_TIMER_END))


#define     NCP_NCA_DELAY_GRP_UPLOAD_TIMER_BASE                 (0x00000070)
#define     NCP_NCA_DELAY_GRP_UPLOAD_TIMER(n)                   (0x00000070 + (4*(n)))
#define     NCP_NCA_DELAY_GRP_UPLOAD_TIMER_COUNT                (0x00000006)
#define     NCP_NCA_DELAY_GRP_UPLOAD_TIMER_IDX(addr) \
         (((addr) - NCP_NCA_DELAY_GRP_UPLOAD_TIMER_BASE) / 4)
#define     NCP_NCA_DELAY_GRP_UPLOAD_TIMER_END                  (0x00000088)
#define     NCP_NCA_DELAY_GRP_UPLOAD_TIMER_RANGE(addr) \
      (((addr) >= NCP_NCA_DELAY_GRP_UPLOAD_TIMER_BASE) && \
      ((addr) < NCP_NCA_DELAY_GRP_UPLOAD_TIMER_END))

#define     NCP_NCA_PAR_ERROR_STATUS0                           (0x00000088)
#define     NCP_NCA_PAR_ERROR_STATUS1                           (0x0000008c)
#define     NCP_NCA_CFG_RING_PARITY                             (0x00000090)
#define     NCP_NCA_CFG_RING_DBG_STAT0                          (0x00000094)
#define     NCP_NCA_CFG_RING_DBG_STAT1                          (0x00000098)
#define     NCP_NCA_CNAL_IF_STATUS                              (0x0000009c)
#define     NCP_NCA_CNAL_CONTROL                                (0x000000a0)
#define     NCP_NCA_NUM_OF_CFG_NODES                            (0x000000e0)
#define     NCP_NCA_NUM_OF_CFG_NODES_V3                         (0x000000e0)
#define     NCP_NCA_CFG_RING_ERROR_STAT_R0                      (0x000000e4)
#define     NCP_NCA_CFG_RING_ERROR_STAT_R0_ACP2500              (0x000000e4)
#define     NCP_NCA_CFG_RING_ERROR_STAT_R1                      (0x000000e8)
#define     NCP_NCA_CFG_RING_ERROR_STAT_R1_ACP2500              (0x000000e8)
#define     NCP_NCA_CFG_RING_NODE_STATUS                        (0x000000ec)
#define     NCP_NCA_CFG_PIO_CDR0                                (0x000000f0)
#define     NCP_NCA_CFG_PIO_CDR1                                (0x000000f4)
#define     NCP_NCA_CFG_PIO_CDR2                                (0x000000f8)
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

#define     NCP_NCA_TFC_COUNT_R_BASE                            (0x00001240)
#define     NCP_NCA_TFC_COUNT_R(n)                              (0x00001240 + (4*(n)))
#define     NCP_NCA_TFC_COUNT_R_COUNT                           (0x0000000c)
#define     NCP_NCA_TFC_COUNT_R_IDX(addr) \
                    (((addr) - NCP_NCA_TFC_COUNT_R_BASE) / 4)         
#define     NCP_NCA_TFC_COUNT_R_END                             (0x00001270)
#define     NCP_NCA_TFC_COUNT_R_RANGE(addr) \
                 (((addr) >= NCP_NCA_TFC_COUNT_R_BASE) && \
                        ((addr) < NCP_NCA_TFC_COUNT_R_END))

#define     NCP_NCA_RBP_ITASK_BP_EN                             (0x000012e0)
#define     NCP_NCA_RBP_ITASK_BP_INCLD_BSIZ                     (0x000012e4)
#define     NCP_NCA_AW_SMON00_NCA_TASK_SMON                     (0x00001300)
#define     NCP_NCA_AW_SMON01_NCA_TASK_SMON                     (0x00001304)
#define     NCP_NCA_AW_SMON02_NCA_TASK_SMON                     (0x00001308)
#define     NCP_NCA_AW_SMON03_NCA_TASK_SMON                     (0x0000130c)
#define     NCP_NCA_AW_SMON04_NCA_TASK_SMON                     (0x00001310)
#define     NCP_NCA_AW_SMON05_NCA_TASK_SMON                     (0x00001314)
#define     NCP_NCA_AW_SMON06_NCA_TASK_SMON                     (0x00001318)
#define     NCP_NCA_AW_SMON07_NCA_TASK_SMON                     (0x0000131c)
#define     NCP_NCA_ITASK_DROP_CNT_IPCQ_ER                      (0x00001320)
#define     NCP_NCA_ITASK_DROP_CNT_NO_BUF                       (0x00001324)
#define     NCP_NCA_OTASK_LENGTH_COMPARE                        (0x00001328)
#define     NCP_NCA_OTASK_LENGTH_CAPTURE                        (0x0000132c)
#define     NCP_NCA_RBP_ITASK_BP                                (0x00001330)
#define     NCP_NCA_OTASK_OPCQ_BP                               (0x00001334)
#define     NCP_NCA_OTBP_BAR_UPPER                              (0x00001340)
#define     NCP_NCA_OTBP_BAR_LOWER                              (0x00001344)
#define     NCP_NCA_PGIT_SOFTWARE_LOAD_POKE_REG                 (0x00001348)
#define     NCP_NCA_HW_LOAD_POKE_FLAGS                          (0x0000134c)

#define     NCP_NCA_DELAY_GRP_LOAD_TIMER_BASE                   (0x00001350)
#define     NCP_NCA_DELAY_GRP_LOAD_TIMER(n)                     (0x00001350 + (4*(n)))
#define     NCP_NCA_DELAY_GRP_LOAD_TIMER_COUNT                  (0x00000006)
#define     NCP_NCA_DELAY_GRP_LOAD_TIMER_IDX(addr) \
           (((addr) - NCP_NCA_DELAY_GRP_LOAD_TIMER_BASE) / 4)
#define     NCP_NCA_DELAY_GRP_LOAD_TIMER_END                    (0x00001368)
#define     NCP_NCA_DELAY_GRP_LOAD_TIMER_RANGE(addr) \
        (((addr) >= NCP_NCA_DELAY_GRP_LOAD_TIMER_BASE) && \
        ((addr) < NCP_NCA_DELAY_GRP_LOAD_TIMER_END))


#define     NCP_NCA_SWPOKE_DELAY_GRP_LOAD_TIMER_BASE            (0x00001370)
#define     NCP_NCA_SWPOKE_DELAY_GRP_LOAD_TIMER(n)              (0x00001370 + (4*(n)))
#define     NCP_NCA_SWPOKE_DELAY_GRP_LOAD_TIMER_COUNT           (0x00000006)
#define     NCP_NCA_SWPOKE_DELAY_GRP_LOAD_TIMER_IDX(addr) \
    (((addr) - NCP_NCA_SWPOKE_DELAY_GRP_LOAD_TIMER_BASE) / 4)
#define     NCP_NCA_SWPOKE_DELAY_GRP_LOAD_TIMER_END             (0x00001388)
#define     NCP_NCA_SWPOKE_DELAY_GRP_LOAD_TIMER_RANGE(addr) \
 (((addr) >= NCP_NCA_SWPOKE_DELAY_GRP_LOAD_TIMER_BASE) && \
  ((addr) < NCP_NCA_SWPOKE_DELAY_GRP_LOAD_TIMER_END))


#define     NCP_NCA_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_BASE         (0x00001390)
#define     NCP_NCA_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER(n)           (0x00001390 + (4*(n)))
#define     NCP_NCA_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_COUNT        (0x00000006)
#define     NCP_NCA_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_IDX(addr) \
  (((addr) - NCP_NCA_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_BASE) / 4)
#define     NCP_NCA_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_END          (0x000013a8)
#define     NCP_NCA_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_RANGE(addr) \
 (((addr) >= NCP_NCA_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_BASE) && \
  ((addr) < NCP_NCA_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_END))


#define     NCP_NCA_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_BASE        (0x000013b0)
#define     NCP_NCA_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR(n)          (0x000013b0 + (4*(n)))
#define     NCP_NCA_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_COUNT       (0x00000006)
#define     NCP_NCA_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_IDX(addr) \
  (((addr) - NCP_NCA_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_BASE) / 4)
#define     NCP_NCA_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_END         (0x000013c8)
#define     NCP_NCA_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_RANGE(addr) \
 (((addr) >= NCP_NCA_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_BASE) && \
  ((addr) < NCP_NCA_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_END))


#define     NCP_NCA_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_BASE      (0x000013d0)
#define     NCP_NCA_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR(n)        (0x000013d0 + (4*(n)))
#define     NCP_NCA_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_COUNT     (0x00000006)
#define     NCP_NCA_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_IDX(addr) \
  (((addr) - NCP_NCA_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_BASE) / 4)
#define     NCP_NCA_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_END       (0x000013e8)
#define     NCP_NCA_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_RANGE(addr) \
 (((addr) >= NCP_NCA_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_BASE) && \
  ((addr) < NCP_NCA_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_END))

#define     NCP_NCA_FIFO_FULL_EMPTY_STATUS_REG0                 (0x00001400)
#define     NCP_NCA_FIFO_FULL_EMPTY_STATUS_REG1                 (0x00001404)
#define     NCP_NCA_FIFO_FULL_EMPTY_STATUS_REG2                 (0x00001408)
#define     NCP_NCA_FIFO_FULL_EMPTY_STATUS_REG3                 (0x0000140c)
#define     NCP_NCA_FIFO_FULL_EMPTY_STATUS_REG4                 (0x00001410)
#define     NCP_NCA_FIFO_FULL_EMPTY_STATUS_REG5                 (0x00001414)
#define     NCP_NCA_FIFO_FULL_EMPTY_STATUS_REG6                 (0x00001418)
#define     NCP_NCA_TFC_UNORDERED_MODE                          (0x00001500)
#define     NCP_NCA_OVERALL_INT_STAT                            (0x0000f000)
#define     NCP_NCA_MPIC_CTRL                                   (0x0000f004)
#define     NCP_NCA_INT_STATUS_DATA_R0                          (0x0000f050)
#define     NCP_NCA_INT_STATUS_DATA_R1                          (0x0000f054)
#define     NCP_NCA_INT_STATUS_DATA_R2                          (0x0000f058)
#define     NCP_NCA_INT_STATUS_DATA_R3                          (0x0000f05c)
#define     NCP_NCA_INT_STATUS_DATA_R4                          (0x0000f060)
#define     NCP_NCA_INT_STATUS_DATA_R5                          (0x0000f064)
#define     NCP_NCA_INT_STATUS_DATA_R6                          (0x0000f068)
#define     NCP_NCA_INT_STATUS_DATA_R7                          (0x0000f06c)
#define     NCP_NCA_INT_STATUS_DATA_R8                          (0x0000f070)
#define     NCP_NCA_INT_STATUS_DATA_R9                          (0x0000f074)
#define     NCP_NCA_INT_STATUS_DATA_R10                         (0x0000f078)
#define     NCP_NCA_INT_STATUS_DATA_R11                         (0x0000f07c)

#define     NCP_NCA_PIO_LOCK_BASE                               (0x0000ff80)
#define     NCP_NCA_PIO_LOCK(n)                                 (0x0000ff80 + (4*(n)))
#define     NCP_NCA_PIO_LOCK_COUNT                              (0x00000020)
#define     NCP_NCA_PIO_LOCK_IDX(addr) \
                       (((addr) - NCP_NCA_PIO_LOCK_BASE) / 4)            
#define     NCP_NCA_PIO_LOCK_END                                (0x00010000)
#define     NCP_NCA_PIO_LOCK_RANGE(addr) \
                    (((addr) >= NCP_NCA_PIO_LOCK_BASE) && \
                              ((addr) < NCP_NCA_PIO_LOCK_END))

#define     NCP_NCA_MAX_OUTSTANDING_AXIM_OPS_ACP2500            (0x00001504)
#define     NCP_NCA_AXIM_OP_COUNTER_CTL_ACP2500                 (0x00001510)
#define     NCP_NCA_CLK_COUNTER_LS_ACP2500                      (0x00001514)
#define     NCP_NCA_AXIM_OP_COUNTER0_LS_ACP2500                 (0x00001518)
#define     NCP_NCA_AXIM_OP_COUNTER1_LS_ACP2500                 (0x0000151c)
#define     NCP_NCA_AXIM_OP_COUNTER2_LS_ACP2500                 (0x00001520)
#define     NCP_NCA_AXIM_OP_COUNTER3_LS_ACP2500                 (0x00001524)
#define     NCP_NCA_AXIM_OUTSTANDING_ROP_COUNT0_ACP2500         (0x00001528)
#define     NCP_NCA_AXIM_OUTSTANDING_ROP_COUNT1_ACP2500         (0x0000152c)
#define     NCP_NCA_AXIM_OUTSTANDING_ROP_COUNT2_ACP2500         (0x00001530)
#define     NCP_NCA_AXIM_OUTSTANDING_RDATA_COUNT0_ACP2500       (0x00001534)
#define     NCP_NCA_AXIM_OUTSTANDING_RDATA_COUNT1_ACP2500       (0x00001538)
#define     NCP_NCA_AXIM_OUTSTANDING_WOP_COUNT0_ACP2500         (0x0000153c)
#define     NCP_NCA_AXIM_OUTSTANDING_WOP_COUNT1_ACP2500         (0x00001540)
#define     NCP_NCA_CLK_COUNTER_MS_ACP2500                      (0x00001544)
#define     NCP_NCA_AXIM_OP_COUNTER0_MS_ACP2500                 (0x00001548)
#define     NCP_NCA_AXIM_OP_COUNTER1_MS_ACP2500                 (0x0000154c)
#define     NCP_NCA_AXIM_OP_COUNTER2_MS_ACP2500                 (0x00001550)
#define     NCP_NCA_AXIM_OP_COUNTER3_MS_ACP2500                 (0x00001554)
#define     NCP_NCA_AXIM_VALID_READY_ACP2500                    (0x00001558)
#define     NCP_NCA_CONFIG_INIT_WOCLR_ACP2500                   (0x0000f200)
#define     NCP_NCA_HW_POKE_AND_TIMER_ENABLE_WOCLR_ACP2500      (0x0000f20c)
#define     NCP_NCA_MPIC_CTRL_WOCLR_ACP2500                     (0x0000f230)
#define     NCP_NCA_CONFIG_INIT_WOSET_ACP2500                   (0x0000f300)
#define     NCP_NCA_PGIT_LOAD_GRP_INDEXES_WOSET_ACP2500         (0x0000f308)
#define     NCP_NCA_HW_POKE_AND_TIMER_ENABLE_WOSET_ACP2500      (0x0000f30c)
#define     NCP_NCA_PGIT_SOFTWARE_LOAD_POKE_REG_WOSET_ACP2500   (0x0000f310)
#define     NCP_NCA_MPIC_CTRL_WOSET_ACP2500                     (0x0000f330)
#define     NCP_NCA_PIO_LOCK_COWN_ACP2500                       (0x0000ff00)
#define     NCP_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R0(n)            (0x00000200 + (32*(n)))
#define     NCP_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R1(n)            (0x00000204 + (32*(n)))
#define     NCP_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R2(n)            (0x00000208 + (32*(n)))
#define     NCP_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R3(n)            (0x0000020c + (32*(n)))
#define     NCP_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R4(n)            (0x00000210 + (32*(n)))
#define     NCP_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R5(n)            (0x00000214 + (32*(n)))
#define     NCP_NCA_PCQ_DESC_RPCQ_R0(n)                         (0x00000300 + (8*(n)))
#define     NCP_NCA_PCQ_DESC_RPCQ_R1(n)                         (0x00000304 + (8*(n)))
#define     NCP_NCA_PCQ_STAT_RPCQ_R0(n)                         (0x00000380 + (8*(n)))
#define     NCP_NCA_PCQ_STAT_RPCQ_R1(n)                         (0x00000384 + (8*(n)))
#define     NCP_NCA_PCQ_DESC_TPCQ_R0(n)                         (0x00000400 + (8*(n)))
#define     NCP_NCA_PCQ_DESC_TPCQ_R1(n)                         (0x00000404 + (8*(n)))
#define     NCP_NCA_PCQ_STAT_TPCQ_R0(n)                         (0x00000480 + (8*(n)))
#define     NCP_NCA_PCQ_STAT_TPCQ_R1(n)                         (0x00000484 + (8*(n)))
#define     NCP_NCA_PCQ_DESC_CPCQ_R0(n)                         (0x00000500 + (8*(n)))
#define     NCP_NCA_PCQ_DESC_CPCQ_R1(n)                         (0x00000504 + (8*(n)))
#define     NCP_NCA_PCQ_STAT_CPCQ_R0(n)                         (0x00000580 + (8*(n)))
#define     NCP_NCA_PCQ_STAT_CPCQ_R1(n)                         (0x00000584 + (8*(n)))
#define     NCP_NCA_PCQ_DESC_OPCQ_R0(n)                         (0x00000600 + (8*(n)))
#define     NCP_NCA_PCQ_DESC_OPCQ_R1(n)                         (0x00000604 + (8*(n)))
#define     NCP_NCA_PCQ_STAT_OPCQ_R0(n)                         (0x00000680 + (8*(n)))
#define     NCP_NCA_PCQ_STAT_OPCQ_R1(n)                         (0x00000684 + (8*(n)))
#define     NCP_NCA_RCV_BUFF_POOL_SIZE_0_1_R(n)                 (0x00000700 + (8*(n)))
#define     NCP_NCA_RCV_BUFF_POOL_SIZE_2_3_R(n)                 (0x00000704 + (8*(n)))
#define     NCP_NCA_PCQ_DESC_IPCQ_R0(n)                         (0x00000800 + (8*(n)))
#define     NCP_NCA_PCQ_DESC_IPCQ_R1(n)                         (0x00000804 + (8*(n)))
#define     NCP_NCA_PCQ_STAT_IPCQ_R0(n)                         (0x00000900 + (8*(n)))
#define     NCP_NCA_PCQ_STAT_IPCQ_R1(n)                         (0x00000904 + (8*(n)))
#define     NCP_NCA_RBP_DEPTHS_R0(n)                            (0x00001280 + (8*(n)))
#define     NCP_NCA_RBP_DEPTHS_ACP2500_R0_ACP2500(n)            (0x00001280 + (8*(n)))
#define     NCP_NCA_RBP_DEPTHS_R1(n)                            (0x00001284 + (8*(n)))
#define     NCP_NCA_RBP_DEPTHS_ACP2500_R1_ACP2500(n)            (0x00001284 + (8*(n)))
#define     NCP_NCA_GRP_INTERRUPT_STATUS_TABLE_STATUS_R0        (0x0000f010)
#define     NCP_NCA_GRP_INTERRUPT_STATUS_TABLE_STATUS_R1        (0x0000f014)
#define     NCP_NCA_GRP_INTERRUPT_STATUS_TABLE_STATUS_R2        (0x0000f018)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_EN_R0            (0x0000f020)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_EN_R1            (0x0000f024)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_EN_R2            (0x0000f028)
#define     NCP_NCA_GRP_INTERRUPT_FORCE_TABLE_FRC_R0            (0x0000f030)
#define     NCP_NCA_GRP_INTERRUPT_FORCE_TABLE_FRC_R1            (0x0000f034)
#define     NCP_NCA_GRP_INTERRUPT_FORCE_TABLE_FRC_R2            (0x0000f038)
#define     NCP_NCA_RBP_FIFO_RANGE_ACP2500_FIFO0_RANGE_SIZE0_ACP2500  (0x00001600)
#define     NCP_NCA_RBP_FIFO_RANGE_ACP2500_FIFO0_RANGE_SIZE1_ACP2500  (0x00001604)
#define     NCP_NCA_RBP_FIFO_RANGE_ACP2500_FIFO0_RANGE_SIZE2_ACP2500  (0x00001608)
#define     NCP_NCA_RBP_FIFO_RANGE_ACP2500_FIFO0_RANGE_SIZE3_ACP2500  (0x0000160c)
#define     NCP_NCA_RBP_FIFO_RANGE_ACP2500_FIFO1_RANGE_SIZE0_ACP2500  (0x00001610)
#define     NCP_NCA_RBP_FIFO_RANGE_ACP2500_FIFO1_RANGE_SIZE1_ACP2500  (0x00001614)
#define     NCP_NCA_RBP_FIFO_RANGE_ACP2500_FIFO1_RANGE_SIZE2_ACP2500  (0x00001618)
#define     NCP_NCA_RBP_FIFO_RANGE_ACP2500_FIFO1_RANGE_SIZE3_ACP2500  (0x0000161c)
#define     NCP_NCA_RBP_FIFO_RANGE_ACP2500_FIFO2_RANGE_SIZE0_ACP2500  (0x00001620)
#define     NCP_NCA_RBP_FIFO_RANGE_ACP2500_FIFO2_RANGE_SIZE1_ACP2500  (0x00001624)
#define     NCP_NCA_RBP_FIFO_RANGE_ACP2500_FIFO2_RANGE_SIZE2_ACP2500  (0x00001628)
#define     NCP_NCA_RBP_FIFO_RANGE_ACP2500_FIFO2_RANGE_SIZE3_ACP2500  (0x0000162c)
#define     NCP_NCA_RBP_FIFO_RANGE_ACP2500_FIFO3_RANGE_SIZE0_ACP2500  (0x00001630)
#define     NCP_NCA_RBP_FIFO_RANGE_ACP2500_FIFO3_RANGE_SIZE1_ACP2500  (0x00001634)
#define     NCP_NCA_RBP_FIFO_RANGE_ACP2500_FIFO3_RANGE_SIZE2_ACP2500  (0x00001638)
#define     NCP_NCA_RBP_FIFO_RANGE_ACP2500_FIFO3_RANGE_SIZE3_ACP2500  (0x0000163c)
#define     NCP_NCA_RBP_FIFO_RANGE_ACP2500_FIFO4_RANGE_SIZE0_ACP2500  (0x00001640)
#define     NCP_NCA_RBP_FIFO_RANGE_ACP2500_FIFO4_RANGE_SIZE1_ACP2500  (0x00001644)
#define     NCP_NCA_RBP_FIFO_RANGE_ACP2500_FIFO4_RANGE_SIZE2_ACP2500  (0x00001648)
#define     NCP_NCA_RBP_FIFO_RANGE_ACP2500_FIFO4_RANGE_SIZE3_ACP2500  (0x0000164c)
#define     NCP_NCA_RBP_FIFO_RANGE_ACP2500_FIFO5_RANGE_SIZE0_ACP2500  (0x00001650)
#define     NCP_NCA_RBP_FIFO_RANGE_ACP2500_FIFO5_RANGE_SIZE1_ACP2500  (0x00001654)
#define     NCP_NCA_RBP_FIFO_RANGE_ACP2500_FIFO5_RANGE_SIZE2_ACP2500  (0x00001658)
#define     NCP_NCA_RBP_FIFO_RANGE_ACP2500_FIFO5_RANGE_SIZE3_ACP2500  (0x0000165c)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOCLR_ACP2500_EN_R0_WOCLR_ACP2500  (0x0000f240)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOCLR_ACP2500_EN_R1_WOCLR_ACP2500  (0x0000f244)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOCLR_ACP2500_EN_R2_WOCLR_ACP2500  (0x0000f248)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOSET_ACP2500_EN_R0_WOSET_ACP2500  (0x0000f340)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOSET_ACP2500_EN_R1_WOSET_ACP2500  (0x0000f344)
#define     NCP_NCA_GRP_INTERRUPT_ENABLE_TABLE_WOSET_ACP2500_EN_R2_WOSET_ACP2500  (0x0000f348)
#ifdef __cplusplus
}
#endif

#endif /* _NCP_NCA_REG_DEFINES_H_ */
