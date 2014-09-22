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


#ifndef _NCP_NCA_REGS_H_
#define _NCP_NCA_REGS_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NCP_STD_TASKIO_LITE
#include <config.h>
#endif

/*! @struct ncp_nca_config_init_reg_t
 *  @brief NCA Config and Initialization Parameters
 *  @details This register defines some AXI burst beat numbers, enables, and soft reset signals
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_config_init_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_end_data_fill_off </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Turn off filling of dummy data on last quadword of
 *        an itask to make the last write 16 bytes.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_ack_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> cfg_ring_ack_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_compl_cnt_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> tfc_completion_count_reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_flush </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> tfc_flush </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> cpcq_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_accum_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> otask_accum_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_accum_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> itask_accum_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> tfc_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otbp_soft_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> otbp_soft_reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_soft_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> rbp_soft_reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> rbp_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_cons_ent </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> opcq_consecutive_entries_per_queue_to_send </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> opcq_entry_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ipcq_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> ipcq_entry_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> tpcq_entry_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rpcq_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> rpcq_entry_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_w_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> pgit_w_num_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_r_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> pgit_r_num_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 * </table>
 * Applies to: v2 --> ncp_nca_config_init_reg_t
 *
 * Implemented by: 
 *      config_init
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      itask_end_data_fill_off                   :  1;
     unsigned      cfg_ring_ack_timer_en                     :  1;
     unsigned      tfc_compl_cnt_reset                       :  1;
     unsigned      tfc_flush                                 :  1;
     unsigned      cpcq_en                                   :  1;
     unsigned      otask_accum_en                            :  1;
     unsigned      itask_accum_en                            :  1;
     unsigned      tfc_en                                    :  1;
     unsigned      otbp_soft_reset                           :  1;
     unsigned      rbp_soft_reset                            :  1;
     unsigned      rbp_en                                    :  1;
     unsigned      reserved1                                 :  4;
     unsigned      opcq_cons_ent                             :  4;
     unsigned      opcq_num_beat                             :  2;
     unsigned      ipcq_num_beat                             :  2;
     unsigned      tpcq_num_beat                             :  2;
     unsigned      rpcq_num_beat                             :  2;
     unsigned      pgit_w_num_beat                           :  2;
     unsigned      pgit_r_num_beat                           :  2;
#else    /* Little Endian */
     unsigned      pgit_r_num_beat                           :  2;
     unsigned      pgit_w_num_beat                           :  2;
     unsigned      rpcq_num_beat                             :  2;
     unsigned      tpcq_num_beat                             :  2;
     unsigned      ipcq_num_beat                             :  2;
     unsigned      opcq_num_beat                             :  2;
     unsigned      opcq_cons_ent                             :  4;
     unsigned      reserved1                                 :  4;
     unsigned      rbp_en                                    :  1;
     unsigned      rbp_soft_reset                            :  1;
     unsigned      otbp_soft_reset                           :  1;
     unsigned      tfc_en                                    :  1;
     unsigned      itask_accum_en                            :  1;
     unsigned      otask_accum_en                            :  1;
     unsigned      cpcq_en                                   :  1;
     unsigned      tfc_flush                                 :  1;
     unsigned      tfc_compl_cnt_reset                       :  1;
     unsigned      cfg_ring_ack_timer_en                     :  1;
     unsigned      itask_end_data_fill_off                   :  1;
     unsigned      reserved0                                 :  1;
#endif
} ncp_nca_config_init_reg_t;

/*! @struct ncp_nca_config_init_reg_v3_t
 *  @brief NCA Config and Initialization Parameters
 *  @details This register defines some AXI burst beat numbers, enables, and soft reset signals
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_config_init_reg_v3_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_end_data_fill_off </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Turn off filling of dummy data on last quadword of
 *        an itask to make the last write 16 bytes.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_ack_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> cfg_ring_ack_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_compl_cnt_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> tfc_completion_count_reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_flush </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> tfc_flush </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> cpcq_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_accum_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> otask_accum_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_accum_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> itask_accum_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> tfc_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otbp_soft_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> otbp_soft_reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_soft_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> rbp_soft_reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> rbp_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otbp_ext_mem_wen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Output task backpressure external memory write enable.
 *        Turning this bit on immediatly causes a write of otask_opcq_bp
 *        to axi memory at the address defined by otbp_bar_upper
 *        and otbp_bar_lower. Subsequent writes will occur any
 *        time the state of otask_opcq_bp changes.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_cons_ent </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> opcq_consecutive_entries_per_queue_to_send </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> opcq_entry_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ipcq_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> ipcq_entry_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> tpcq_entry_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rpcq_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> rpcq_entry_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_w_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> pgit_w_num_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_r_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> pgit_r_num_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 * </table>
 * Applies to: v3 --> ncp_nca_config_init_reg_v3_t
 *
 * Implemented by: 
 *      config_init
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      itask_end_data_fill_off                   :  1;
     unsigned      cfg_ring_ack_timer_en                     :  1;
     unsigned      tfc_compl_cnt_reset                       :  1;
     unsigned      tfc_flush                                 :  1;
     unsigned      cpcq_en                                   :  1;
     unsigned      otask_accum_en                            :  1;
     unsigned      itask_accum_en                            :  1;
     unsigned      tfc_en                                    :  1;
     unsigned      otbp_soft_reset                           :  1;
     unsigned      rbp_soft_reset                            :  1;
     unsigned      rbp_en                                    :  1;
     unsigned      otbp_ext_mem_wen                          :  1;
     unsigned      reserved1                                 :  3;
     unsigned      opcq_cons_ent                             :  4;
     unsigned      opcq_num_beat                             :  2;
     unsigned      ipcq_num_beat                             :  2;
     unsigned      tpcq_num_beat                             :  2;
     unsigned      rpcq_num_beat                             :  2;
     unsigned      pgit_w_num_beat                           :  2;
     unsigned      pgit_r_num_beat                           :  2;
#else    /* Little Endian */
     unsigned      pgit_r_num_beat                           :  2;
     unsigned      pgit_w_num_beat                           :  2;
     unsigned      rpcq_num_beat                             :  2;
     unsigned      tpcq_num_beat                             :  2;
     unsigned      ipcq_num_beat                             :  2;
     unsigned      opcq_num_beat                             :  2;
     unsigned      opcq_cons_ent                             :  4;
     unsigned      reserved1                                 :  3;
     unsigned      otbp_ext_mem_wen                          :  1;
     unsigned      rbp_en                                    :  1;
     unsigned      rbp_soft_reset                            :  1;
     unsigned      otbp_soft_reset                           :  1;
     unsigned      tfc_en                                    :  1;
     unsigned      itask_accum_en                            :  1;
     unsigned      otask_accum_en                            :  1;
     unsigned      cpcq_en                                   :  1;
     unsigned      tfc_flush                                 :  1;
     unsigned      tfc_compl_cnt_reset                       :  1;
     unsigned      cfg_ring_ack_timer_en                     :  1;
     unsigned      itask_end_data_fill_off                   :  1;
     unsigned      reserved0                                 :  1;
#endif
} ncp_nca_config_init_reg_v3_t;

/*! @struct ncp_nca_config_init_reg_acp2500_t
 *  @brief NCA Config and Initialization Parameters
 *  @details This register defines some AXI burst beat numbers, enables, and soft reset signals
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_config_init_reg_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_end_data_fill_off </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Turn off filling of dummy data on last quadword of
 *        an itask to make the last write 16 bytes.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_ack_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> cfg_ring_ack_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_compl_cnt_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> tfc_completion_count_reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_flush </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> tfc_flush </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> cpcq_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_accum_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> otask_accum_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_accum_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> itask_accum_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> tfc_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otbp_soft_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> otbp_soft_reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_soft_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> rbp_soft_reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> rbp_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otbp_ext_mem_wen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Output task backpressure external memory write enable.
 *        Turning this bit on immediatly causes a write of otask_opcq_bp
 *        to axi memory at the address defined by otbp_bar_upper
 *        and otbp_bar_lower. Subsequent writes will occur any
 *        time the state of otask_opcq_bp changes.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param spare </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> spare </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_exec_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> cpcq execution disable bit : NOTE: This bit is supposed
 *        to be used sparingly (for debugging etc.) to temporarily
 *        halt the execution from cfg request fifo of the cpcq
 *        entries
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_cons_ent </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> opcq_consecutive_entries_per_queue_to_send </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> opcq_entry_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ipcq_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> ipcq_entry_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> tpcq_entry_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rpcq_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> rpcq_entry_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_w_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> pgit_w_num_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_r_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> pgit_r_num_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_config_init_reg_acp2500_t
 *
 * Implemented by: 
 *      config_init
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      itask_end_data_fill_off                   :  1;
     unsigned      cfg_ring_ack_timer_en                     :  1;
     unsigned      tfc_compl_cnt_reset                       :  1;
     unsigned      tfc_flush                                 :  1;
     unsigned      cpcq_en                                   :  1;
     unsigned      otask_accum_en                            :  1;
     unsigned      itask_accum_en                            :  1;
     unsigned      tfc_en                                    :  1;
     unsigned      otbp_soft_reset                           :  1;
     unsigned      rbp_soft_reset                            :  1;
     unsigned      rbp_en                                    :  1;
     unsigned      otbp_ext_mem_wen                          :  1;
     unsigned      spare                                     :  2;
     unsigned      cpcq_exec_disable                         :  1;
     unsigned      opcq_cons_ent                             :  4;
     unsigned      opcq_num_beat                             :  2;
     unsigned      ipcq_num_beat                             :  2;
     unsigned      tpcq_num_beat                             :  2;
     unsigned      rpcq_num_beat                             :  2;
     unsigned      pgit_w_num_beat                           :  2;
     unsigned      pgit_r_num_beat                           :  2;
#else    /* Little Endian */
     unsigned      pgit_r_num_beat                           :  2;
     unsigned      pgit_w_num_beat                           :  2;
     unsigned      rpcq_num_beat                             :  2;
     unsigned      tpcq_num_beat                             :  2;
     unsigned      ipcq_num_beat                             :  2;
     unsigned      opcq_num_beat                             :  2;
     unsigned      opcq_cons_ent                             :  4;
     unsigned      cpcq_exec_disable                         :  1;
     unsigned      spare                                     :  2;
     unsigned      otbp_ext_mem_wen                          :  1;
     unsigned      rbp_en                                    :  1;
     unsigned      rbp_soft_reset                            :  1;
     unsigned      otbp_soft_reset                           :  1;
     unsigned      tfc_en                                    :  1;
     unsigned      itask_accum_en                            :  1;
     unsigned      otask_accum_en                            :  1;
     unsigned      cpcq_en                                   :  1;
     unsigned      tfc_flush                                 :  1;
     unsigned      tfc_compl_cnt_reset                       :  1;
     unsigned      cfg_ring_ack_timer_en                     :  1;
     unsigned      itask_end_data_fill_off                   :  1;
     unsigned      reserved0                                 :  1;
#endif
} ncp_nca_config_init_reg_acp2500_t;

/*! @struct ncp_nca_cfg_ring_parity_reg_t
 *  @brief NCA CFG Master Parity and CNAL ECC Register
 *  @details This register defines CFG Ring Parity Type , CNAL I/F ECC and Enables
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_cfg_ring_parity_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param singlebit_ecc_correct_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> CNAL I/F correct singlebit ECC enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param singlebit_ecc_detect_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> CNAL I/F detect singlebit ECC enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param multibit_ecc_detect_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CNAL I/F detect multibit ECC enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_par_err_rst_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> RESERVED: Do Not set this bit. cfg_ring_parity_err_reset_exec_enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_parity_type_ring2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> cfg_parity_type_ring2 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_parity_type_ring1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> cfg_parity_type_ring1 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_parity_type_ring0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> cfg_parity_type_ring0 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_parity_err_en_ring2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> cfg_parity_err_en_ring3 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_parity_err_en_ring1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> cfg_parity_err_en_ring1 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_parity_err_en_ring0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> cfg_parity_err_en_ring0 </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_cfg_ring_parity_reg_t
 *
 * Implemented by: 
 *      cfg_ring_parity
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 22;
     unsigned      singlebit_ecc_correct_en                  :  1;
     unsigned      singlebit_ecc_detect_en                   :  1;
     unsigned      multibit_ecc_detect_en                    :  1;
     unsigned      cfg_par_err_rst_en                        :  1;
     unsigned      cfg_parity_type_ring2                     :  1;
     unsigned      cfg_parity_type_ring1                     :  1;
     unsigned      cfg_parity_type_ring0                     :  1;
     unsigned      cfg_parity_err_en_ring2                   :  1;
     unsigned      cfg_parity_err_en_ring1                   :  1;
     unsigned      cfg_parity_err_en_ring0                   :  1;
#else    /* Little Endian */
     unsigned      cfg_parity_err_en_ring0                   :  1;
     unsigned      cfg_parity_err_en_ring1                   :  1;
     unsigned      cfg_parity_err_en_ring2                   :  1;
     unsigned      cfg_parity_type_ring0                     :  1;
     unsigned      cfg_parity_type_ring1                     :  1;
     unsigned      cfg_parity_type_ring2                     :  1;
     unsigned      cfg_par_err_rst_en                        :  1;
     unsigned      multibit_ecc_detect_en                    :  1;
     unsigned      singlebit_ecc_detect_en                   :  1;
     unsigned      singlebit_ecc_correct_en                  :  1;
     unsigned      reserved0                                 : 22;
#endif
} ncp_nca_cfg_ring_parity_reg_t;

/*! @struct ncp_nca_cnal_control_reg_t
 *  @brief NCA CFG Master's CNAL Control Register
 *  @details This register defines cnal_soft_reset bit
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_cnal_control_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 31 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cnal_soft_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> cnal_soft_reset: if set by sw, hw clears it when reset
 *        done
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_cnal_control_reg_t
 *
 * Implemented by: 
 *      cnal_control
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 31;
     unsigned      cnal_soft_reset                           :  1;
#else    /* Little Endian */
     unsigned      cnal_soft_reset                           :  1;
     unsigned      reserved0                                 : 31;
#endif
} ncp_nca_cnal_control_reg_t;

/*! @struct ncp_nca_cfg_ring_dbg_stat0_reg_t
 *  @brief NCA CFG Master Debug Status Register0
 *  @details This register holds some internal signals for Debug purpose
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_cfg_ring_dbg_stat0_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cmd_out </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> CFG cmd_out </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param data_out </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> CFG data_out </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rcfg_wcdar </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> read into CDAR </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rcfg_wbuff </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> read into Data BUFF </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rd_data_cnt </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> read data count </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rd_data_done </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> read data done indication </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param data_done </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> data done indication </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param timed_out </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> ACK time out indication </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param timer_state </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> timer state machine's state </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param state </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> main state machine's state </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_cfg_ring_dbg_stat0_reg_t
 *
 * Implemented by: 
 *      cfg_ring_dbg_stat0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      cmd_out                                   :  3;
     unsigned      data_out                                  :  8;
     unsigned      rcfg_wcdar                                :  1;
     unsigned      rcfg_wbuff                                :  1;
     unsigned      rd_data_cnt                               :  9;
     unsigned      rd_data_done                              :  1;
     unsigned      data_done                                 :  1;
     unsigned      timed_out                                 :  1;
     unsigned      timer_state                               :  3;
     unsigned      state                                     :  4;
#else    /* Little Endian */
     unsigned      state                                     :  4;
     unsigned      timer_state                               :  3;
     unsigned      timed_out                                 :  1;
     unsigned      data_done                                 :  1;
     unsigned      rd_data_done                              :  1;
     unsigned      rd_data_cnt                               :  9;
     unsigned      rcfg_wbuff                                :  1;
     unsigned      rcfg_wcdar                                :  1;
     unsigned      data_out                                  :  8;
     unsigned      cmd_out                                   :  3;
#endif
} ncp_nca_cfg_ring_dbg_stat0_reg_t;

/*! @struct ncp_nca_cfg_ring_dbg_stat1_reg_t
 *  @brief NCA CFG Master Debug Status Register1
 *  @details This register holds some internal signals for Debug purpose
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_cfg_ring_dbg_stat1_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param ring0_parity_in </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> CFG0_par_in </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ring1_parity_in </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> CFG1_par_in </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ring2_parity_in </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> CFG2_par_in </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmd_in </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> CFG_cmd_in </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param data_in </td>
 *     <td width="20%" align="center"> 26 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CFG data_in </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_cfg_ring_dbg_stat1_reg_t
 *
 * Implemented by: 
 *      cfg_ring_dbg_stat1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      ring0_parity_in                           :  1;
     unsigned      ring1_parity_in                           :  1;
     unsigned      ring2_parity_in                           :  1;
     unsigned      cmd_in                                    :  3;
     unsigned      data_in                                   : 26;
#else    /* Little Endian */
     unsigned      data_in                                   : 26;
     unsigned      cmd_in                                    :  3;
     unsigned      ring2_parity_in                           :  1;
     unsigned      ring1_parity_in                           :  1;
     unsigned      ring0_parity_in                           :  1;
#endif
} ncp_nca_cfg_ring_dbg_stat1_reg_t;

/*! @struct ncp_nca_int_param_grp_reg_t
 *  @brief Group INT PARAMS Register
 *  @details This register defines interrupt related parameters for a given group
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_int_param_grp_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wtask </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> how many task arrivals needed to be waited before
 *        generating a task arrival interrupt
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wtime </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> time in sysclk periods to be waited after the first
 *        task arrived before generating a task arrival interrupt
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_int_param_grp_reg_t
 *
 * Implemented by: 
 *      int_param_grp
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      wtask                                     :  4;
     unsigned      wtime                                     : 12;
#else    /* Little Endian */
     unsigned      wtime                                     : 12;
     unsigned      wtask                                     :  4;
     unsigned      reserved0                                 : 16;
#endif
} ncp_nca_int_param_grp_reg_t;

/*! @struct ncp_nca_int_status_data_reg0_t
 *  @brief INT Status Data Register0
 *  @details defines interrupt causing and/or related data
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_int_status_data_reg0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param double_bit_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> rbp_ecc_double-bit_error </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param single_bit_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> rbp_ecc_single-bit_error </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param buffer_size </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> rbp_ecc_error_rbp_buffer_size </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_drop_num </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> rbp_ecc_error_drop_entry_rbp_num </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_axi_resp </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> tpcq_entry_axi_resp </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_axi_err </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> tpcq_axi_read_er_tpcq_num </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rpcq_axi_resp </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> rpcq_entry_axi_resp </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rpcq_axi_err </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> rpcq_entry_axi_read_er_rbp_num </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_axi_resp </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> otask_data_axi_resp </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_axi_err </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> otask_data_axi_read_er_opcq_num </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_axi_resp </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> opcq_entry_axi_resp </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_axi_err </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> opcq_entry_axi_read_er_opcq_num </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_int_status_data_reg0_t
 *
 * Implemented by: 
 *      int_status_data_r0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      double_bit_error                          :  1;
     unsigned      single_bit_error                          :  1;
     unsigned      buffer_size                               :  2;
     unsigned      rbp_drop_num                              :  4;
     unsigned      tpcq_axi_resp                             :  2;
     unsigned      tpcq_axi_err                              :  4;
     unsigned      rpcq_axi_resp                             :  2;
     unsigned      rpcq_axi_err                              :  4;
     unsigned      otask_axi_resp                            :  2;
     unsigned      otask_axi_err                             :  4;
     unsigned      opcq_axi_resp                             :  2;
     unsigned      opcq_axi_err                              :  4;
#else    /* Little Endian */
     unsigned      opcq_axi_err                              :  4;
     unsigned      opcq_axi_resp                             :  2;
     unsigned      otask_axi_err                             :  4;
     unsigned      otask_axi_resp                            :  2;
     unsigned      rpcq_axi_err                              :  4;
     unsigned      rpcq_axi_resp                             :  2;
     unsigned      tpcq_axi_err                              :  4;
     unsigned      tpcq_axi_resp                             :  2;
     unsigned      rbp_drop_num                              :  4;
     unsigned      buffer_size                               :  2;
     unsigned      single_bit_error                          :  1;
     unsigned      double_bit_error                          :  1;
#endif
} ncp_nca_int_status_data_reg0_t;

/*! @struct ncp_nca_int_status_data_reg1_t
 *  @brief INT Status Data Register1
 *  @details defines interrupt causing and/or related data
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_int_status_data_reg1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_load_cpu_axi_read_er_resp </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> pgit_load_cpu_axi_read_er_resp </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_load_cpu_axi_read_er_group_num </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> pgit_load_cpu_axi_read_er_group_num </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_load_nca_axi_read_er_resp </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> pgit_load_nca_axi_read_er_resp </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_load_nca_axi_read_er_group_num </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> pgit_load_nca_axi_read_er_group_num </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_upload_nca_axi_write_er_resp </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> pgit_upload_nca_axi_write_er_resp </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_upload_nca_axi_write_er_group_num </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> pgit_upload_nca_axi_write_er_group_num </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ipcq_entry_axi_write_er_resp </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> ipcq_entry_axi_write_er_resp </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ipcq_entry_axi_write_er_group_num </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> ipcq_entry_axi_write_er_group_num </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_data_axi_write_er_resp </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> itask_data_axi_write_er_resp </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_data_axi_write_er_group_num </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> itask_data_axi_write_er_group_num </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_axi_read_err_resp </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> cpcq_axi_read_err_resp </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_axi_read_err_group_num </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> cpcq_axi_read_err_group_num </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_axi_write_err_resp </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> cmn_axi_write_err_resp </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_int_status_data_reg1_t
 *
 * Implemented by: 
 *      int_status_data_r1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      pgit_load_cpu_axi_read_er_resp            :  2;
     unsigned      pgit_load_cpu_axi_read_er_group_num       :  3;
     unsigned      pgit_load_nca_axi_read_er_resp            :  2;
     unsigned      pgit_load_nca_axi_read_er_group_num       :  3;
     unsigned      pgit_upload_nca_axi_write_er_resp         :  2;
     unsigned      pgit_upload_nca_axi_write_er_group_num    :  3;
     unsigned      ipcq_entry_axi_write_er_resp              :  2;
     unsigned      ipcq_entry_axi_write_er_group_num         :  3;
     unsigned      itask_data_axi_write_er_resp              :  2;
     unsigned      itask_data_axi_write_er_group_num         :  3;
     unsigned      cpcq_axi_read_err_resp                    :  2;
     unsigned      cpcq_axi_read_err_group_num               :  3;
     unsigned      cmn_axi_write_err_resp                    :  2;
#else    /* Little Endian */
     unsigned      cmn_axi_write_err_resp                    :  2;
     unsigned      cpcq_axi_read_err_group_num               :  3;
     unsigned      cpcq_axi_read_err_resp                    :  2;
     unsigned      itask_data_axi_write_er_group_num         :  3;
     unsigned      itask_data_axi_write_er_resp              :  2;
     unsigned      ipcq_entry_axi_write_er_group_num         :  3;
     unsigned      ipcq_entry_axi_write_er_resp              :  2;
     unsigned      pgit_upload_nca_axi_write_er_group_num    :  3;
     unsigned      pgit_upload_nca_axi_write_er_resp         :  2;
     unsigned      pgit_load_nca_axi_read_er_group_num       :  3;
     unsigned      pgit_load_nca_axi_read_er_resp            :  2;
     unsigned      pgit_load_cpu_axi_read_er_group_num       :  3;
     unsigned      pgit_load_cpu_axi_read_er_resp            :  2;
#endif
} ncp_nca_int_status_data_reg1_t;

/*! @struct ncp_nca_int_status_data_reg2_t
 *  @brief INT Status Data Register2
 *  @details defines interrupt causing and/or related data
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_int_status_data_reg2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param otask_data_overflow_opcq_num </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> output task data overflow oPCQ number </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_data_underflow_opcq_num </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> output task data underflow oPCQ number </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp_num </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> eng_cnal_if_int_grp_num. When eng_cnal_if_int_is_pio
 *        is clear, and at least one of the grp_interrupt_status_table.status_r1.eng_cnal_if_grp|0..5|_int
 *        bits is set, this field indicates for which group
 *        number the cnal_if_status register contains error
 *        data.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_is_pio </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> eng_cnal_if interrupt is pio mode. When this bit and
 *        the grp_interrupt_status_table.status_r2.eng_cnal_if_pio_int
 *        bit are both set, the cnal_if_status register contains
 *        error data for that interrupt.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp_num </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> cfg_ring_err_int_grp_num. When cfg_ring_err_int_is_pio
 *        is clear, and at least one of the grp_interrupt_status_table.status_r1.cfg_ring_err_grp|0..5|_int
 *        bits is set, this field indicates for which group
 *        number the cfg_ring_error_stat_r|0..1| registers contain
 *        error data.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_is_pio </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> cfg_ring_err interrupt is for pio mode. When this
 *        bit and the grp_interrupt_status_table.status_r2.cfg_ring_err_pio_int
 *        bit are both set, the cfg_ring_error_stat_r|0..1|
 *        registers contain error data for that interrupt.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otsd_axi_resp </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> otsd_axi_resp </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otsd_axi_err </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> otsd_axi_read_er_opcq_num </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_drop_no_rbuf_err_int_grp_num </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> itask_drop_no_rbuf_err_int_grp_num </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_drop_ipcq_err_int_grp_num </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> itask_drop_ipcq_err_int_grp_num </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_drop_entry_receive_buffer_pool_id </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> rbp_drop_entry_receive_buffer_pool_ID </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_int_status_data_reg2_t
 *
 * Implemented by: 
 *      int_status_data_r2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      otask_data_overflow_opcq_num              :  4;
     unsigned      otask_data_underflow_opcq_num             :  4;
     unsigned      eng_cnal_if_int_grp_num                   :  3;
     unsigned      eng_cnal_if_int_is_pio                    :  1;
     unsigned      cfg_ring_err_int_grp_num                  :  3;
     unsigned      cfg_ring_err_int_is_pio                   :  1;
     unsigned      otsd_axi_resp                             :  2;
     unsigned      otsd_axi_err                              :  4;
     unsigned      itask_drop_no_rbuf_err_int_grp_num        :  3;
     unsigned      itask_drop_ipcq_err_int_grp_num           :  3;
     unsigned      rbp_drop_entry_receive_buffer_pool_id     :  4;
#else    /* Little Endian */
     unsigned      rbp_drop_entry_receive_buffer_pool_id     :  4;
     unsigned      itask_drop_ipcq_err_int_grp_num           :  3;
     unsigned      itask_drop_no_rbuf_err_int_grp_num        :  3;
     unsigned      otsd_axi_err                              :  4;
     unsigned      otsd_axi_resp                             :  2;
     unsigned      cfg_ring_err_int_is_pio                   :  1;
     unsigned      cfg_ring_err_int_grp_num                  :  3;
     unsigned      eng_cnal_if_int_is_pio                    :  1;
     unsigned      eng_cnal_if_int_grp_num                   :  3;
     unsigned      otask_data_underflow_opcq_num             :  4;
     unsigned      otask_data_overflow_opcq_num              :  4;
#endif
} ncp_nca_int_status_data_reg2_t;

/*! @struct ncp_nca_int_status_data_reg3_t
 *  @brief INT Status Data Register3
 *  @details defines interrupt causing and/or related data
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_int_status_data_reg3_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_drop_buffer_id </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> rbp_drop_entry_buffer_id </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_int_status_data_reg3_t
 *
 * Implemented by: 
 *      int_status_data_r3
 */
 
typedef struct
{
     unsigned  int        rbp_drop_buffer_id;
} ncp_nca_int_status_data_reg3_t;

/*! @struct ncp_nca_int_status_data_reg4_t
 *  @brief INT Status Data Register4
 *  @details defines interrupt causing and/or related data
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_int_status_data_reg4_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param ita_idle </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> ita_idle </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_idle </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> rbp_idle </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_idle </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> tfc_idle </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_idle </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> ota_idle </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_idle </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> cpcq_idle </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_pgit_rfifo_stat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> cpcq_rfifo_overflow_underflow_status_pair </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_pgit_wfifo_stat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> cpcq_wfifo_overflow_underflow_status_pair </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_fifo_stat13 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> pgit_reng_rbf_fifo_overflow_underflow_status_pair7 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_fifo_stat12 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> pgit_reng_rbf_fifo_overflow_underflow_status_pair6 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_fifo_stat11 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> pgit_reng_rbf_fifo_overflow_underflow_status_pair5 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_fifo_stat10 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> pgit_reng_rbf_fifo_overflow_underflow_status_pair4 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_fifo_stat9 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> pgit_reng_rbf_fifo_overflow_underflow_status_pair3 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_fifo_stat8 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> pgit_reng_rbf_fifo_overflow_underflow_status_pair2 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_fifo_stat7 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> pgit_reng_rbf_fifo_overflow_underflow_status_pair1 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_fifo_stat6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> pgit_reng_rbf_fifo_overflow_underflow_status_pair0 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_fifo_stat5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> pgit_reng_req_fifo_overflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_fifo_stat4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> pgit_reng_req_fifo_underflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_fifo_stat3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> pgit_weng_wdb_fifo_overflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_fifo_stat2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> pgit_weng_wdb_fifo_underflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_fifo_stat1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> pgit_weng_req_fifo_overflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_fifo_stat0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> pgit_weng_req_fifo_underflow_status </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_int_status_data_reg4_t
 *
 * Implemented by: 
 *      int_status_data_r4
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      ita_idle                                  :  1;
     unsigned      rbp_idle                                  :  1;
     unsigned      tfc_idle                                  :  1;
     unsigned      ota_idle                                  :  1;
     unsigned      cpcq_idle                                 :  1;
     unsigned      reserved0                                 :  1;
     unsigned      cpcq_pgit_rfifo_stat                      :  2;
     unsigned      cpcq_pgit_wfifo_stat                      :  2;
     unsigned      pgit_fifo_stat13                          :  2;
     unsigned      pgit_fifo_stat12                          :  2;
     unsigned      pgit_fifo_stat11                          :  2;
     unsigned      pgit_fifo_stat10                          :  2;
     unsigned      pgit_fifo_stat9                           :  2;
     unsigned      pgit_fifo_stat8                           :  2;
     unsigned      pgit_fifo_stat7                           :  2;
     unsigned      pgit_fifo_stat6                           :  2;
     unsigned      pgit_fifo_stat5                           :  1;
     unsigned      pgit_fifo_stat4                           :  1;
     unsigned      pgit_fifo_stat3                           :  1;
     unsigned      pgit_fifo_stat2                           :  1;
     unsigned      pgit_fifo_stat1                           :  1;
     unsigned      pgit_fifo_stat0                           :  1;
#else    /* Little Endian */
     unsigned      pgit_fifo_stat0                           :  1;
     unsigned      pgit_fifo_stat1                           :  1;
     unsigned      pgit_fifo_stat2                           :  1;
     unsigned      pgit_fifo_stat3                           :  1;
     unsigned      pgit_fifo_stat4                           :  1;
     unsigned      pgit_fifo_stat5                           :  1;
     unsigned      pgit_fifo_stat6                           :  2;
     unsigned      pgit_fifo_stat7                           :  2;
     unsigned      pgit_fifo_stat8                           :  2;
     unsigned      pgit_fifo_stat9                           :  2;
     unsigned      pgit_fifo_stat10                          :  2;
     unsigned      pgit_fifo_stat11                          :  2;
     unsigned      pgit_fifo_stat12                          :  2;
     unsigned      pgit_fifo_stat13                          :  2;
     unsigned      cpcq_pgit_wfifo_stat                      :  2;
     unsigned      cpcq_pgit_rfifo_stat                      :  2;
     unsigned      reserved0                                 :  1;
     unsigned      cpcq_idle                                 :  1;
     unsigned      ota_idle                                  :  1;
     unsigned      tfc_idle                                  :  1;
     unsigned      rbp_idle                                  :  1;
     unsigned      ita_idle                                  :  1;
#endif
} ncp_nca_int_status_data_reg4_t;

/*! @struct ncp_nca_int_status_data_reg5_t
 *  @brief INT Status Data Register5
 *  @details defines interrupt causing and/or related data
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_int_status_data_reg5_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odb_fifo_overflow_status </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> odb_fifo_overflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odb_fifo_underflow_status </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> odb_fifo_underflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param idb_fifo_overflow_status </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> idb_fifo_overflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param idb_fifo_underflow_status </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> idb_fifo_underflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_fifo_stat3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> cmn_weng_req_fifo_overflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_fifo_stat2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> cmn_weng_req_fifo_underflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_fifo_stat1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> cmn_weng_wdb_fifo_overflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_fifo_stat0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> cmn_weng_wdb_fifo_underflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ita_fifo_stat15 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> tcri_data_fifo_overflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ita_fifo_stat14 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> tcri_data_fifo_underflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ita_fifo_stat13 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> itask_header_fifo_overflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ita_fifo_stat12 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> itask_header_fifo_underflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ita_fifo_stat11 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> itask_qid_fifo_overflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ita_fifo_stat10 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> itask_qid_fifo_underflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ita_fifo_stat9 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> itask_delete_tid_fifo_overflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ita_fifo_stat8 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> itask_delete_tid_fifo_underflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ita_fifo_stat7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> ipcq_pgitr_fifo_overflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ita_fifo_stat6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> ipcq_pgitr_fifo_underflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ita_fifo_stat5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> ipcq_pgitw_fifo_overflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ita_fifo_stat4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> ipcq_pgitw_fifo_underflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ita_fifo_stat3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> itask_weng_req_fifo_overflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ita_fifo_stat2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> itask_weng_req_fifo_underflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ita_fifo_stat1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> itask_weng_wdb_fifo_overflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ita_fifo_stat0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> itask_weng_wdb_fifo_underflow_status </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_int_status_data_reg5_t
 *
 * Implemented by: 
 *      int_status_data_r5
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  8;
     unsigned      odb_fifo_overflow_status                  :  1;
     unsigned      odb_fifo_underflow_status                 :  1;
     unsigned      idb_fifo_overflow_status                  :  1;
     unsigned      idb_fifo_underflow_status                 :  1;
     unsigned      cmn_fifo_stat3                            :  1;
     unsigned      cmn_fifo_stat2                            :  1;
     unsigned      cmn_fifo_stat1                            :  1;
     unsigned      cmn_fifo_stat0                            :  1;
     unsigned      ita_fifo_stat15                           :  1;
     unsigned      ita_fifo_stat14                           :  1;
     unsigned      ita_fifo_stat13                           :  1;
     unsigned      ita_fifo_stat12                           :  1;
     unsigned      ita_fifo_stat11                           :  1;
     unsigned      ita_fifo_stat10                           :  1;
     unsigned      ita_fifo_stat9                            :  1;
     unsigned      ita_fifo_stat8                            :  1;
     unsigned      ita_fifo_stat7                            :  1;
     unsigned      ita_fifo_stat6                            :  1;
     unsigned      ita_fifo_stat5                            :  1;
     unsigned      ita_fifo_stat4                            :  1;
     unsigned      ita_fifo_stat3                            :  1;
     unsigned      ita_fifo_stat2                            :  1;
     unsigned      ita_fifo_stat1                            :  1;
     unsigned      ita_fifo_stat0                            :  1;
#else    /* Little Endian */
     unsigned      ita_fifo_stat0                            :  1;
     unsigned      ita_fifo_stat1                            :  1;
     unsigned      ita_fifo_stat2                            :  1;
     unsigned      ita_fifo_stat3                            :  1;
     unsigned      ita_fifo_stat4                            :  1;
     unsigned      ita_fifo_stat5                            :  1;
     unsigned      ita_fifo_stat6                            :  1;
     unsigned      ita_fifo_stat7                            :  1;
     unsigned      ita_fifo_stat8                            :  1;
     unsigned      ita_fifo_stat9                            :  1;
     unsigned      ita_fifo_stat10                           :  1;
     unsigned      ita_fifo_stat11                           :  1;
     unsigned      ita_fifo_stat12                           :  1;
     unsigned      ita_fifo_stat13                           :  1;
     unsigned      ita_fifo_stat14                           :  1;
     unsigned      ita_fifo_stat15                           :  1;
     unsigned      cmn_fifo_stat0                            :  1;
     unsigned      cmn_fifo_stat1                            :  1;
     unsigned      cmn_fifo_stat2                            :  1;
     unsigned      cmn_fifo_stat3                            :  1;
     unsigned      idb_fifo_underflow_status                 :  1;
     unsigned      idb_fifo_overflow_status                  :  1;
     unsigned      odb_fifo_underflow_status                 :  1;
     unsigned      odb_fifo_overflow_status                  :  1;
     unsigned      reserved0                                 :  8;
#endif
} ncp_nca_int_status_data_reg5_t;

/*! @struct ncp_nca_int_status_data_reg6_t
 *  @brief INT Status Data Register6
 *  @details defines interrupt causing and/or related data
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_int_status_data_reg6_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo_stat10 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> rpcq_pgitr_fifo_overflow_underflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo_stat9 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> rpcq_pgitw_fifo_overflow_underflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo_stat8 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> rbp_reng_req_fifo_overflow_underflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo_stat7 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> rbp_reng_rbf_fifo_overflow_underflow_status_pair7 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo_stat6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> rbp_reng_rbf_fifo_overflow_underflow_status_pair6 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo_stat5 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> rbp_reng_rbf_fifo_overflow_underflow_status_pair5 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo_stat4 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> rbp_reng_rbf_fifo_overflow_underflow_status_pair4 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo_stat3 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> rbp_reng_rbf_fifo_overflow_underflow_status_pair3 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo_stat2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> rbp_reng_rbf_fifo_overflow_underflow_status_pair2 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo_stat1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> rbp_reng_rbf_fifo_overflow_underflow_status_pair1 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo_stat0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> rbp_reng_rbf_fifo_overflow_underflow_status_pair0 </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_int_status_data_reg6_t
 *
 * Implemented by: 
 *      int_status_data_r6
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 10;
     unsigned      rbp_fifo_stat10                           :  2;
     unsigned      rbp_fifo_stat9                            :  2;
     unsigned      rbp_fifo_stat8                            :  2;
     unsigned      rbp_fifo_stat7                            :  2;
     unsigned      rbp_fifo_stat6                            :  2;
     unsigned      rbp_fifo_stat5                            :  2;
     unsigned      rbp_fifo_stat4                            :  2;
     unsigned      rbp_fifo_stat3                            :  2;
     unsigned      rbp_fifo_stat2                            :  2;
     unsigned      rbp_fifo_stat1                            :  2;
     unsigned      rbp_fifo_stat0                            :  2;
#else    /* Little Endian */
     unsigned      rbp_fifo_stat0                            :  2;
     unsigned      rbp_fifo_stat1                            :  2;
     unsigned      rbp_fifo_stat2                            :  2;
     unsigned      rbp_fifo_stat3                            :  2;
     unsigned      rbp_fifo_stat4                            :  2;
     unsigned      rbp_fifo_stat5                            :  2;
     unsigned      rbp_fifo_stat6                            :  2;
     unsigned      rbp_fifo_stat7                            :  2;
     unsigned      rbp_fifo_stat8                            :  2;
     unsigned      rbp_fifo_stat9                            :  2;
     unsigned      rbp_fifo_stat10                           :  2;
     unsigned      reserved0                                 : 10;
#endif
} ncp_nca_int_status_data_reg6_t;

/*! @struct ncp_nca_int_status_data_reg7_t
 *  @brief INT Status Data Register7
 *  @details defines interrupt causing and/or related data
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_int_status_data_reg7_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_stat_reg0_15 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> otask_reng_rbf_fifo_overflow_underflow_status_pair7 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_stat_reg0_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> otask_reng_rbf_fifo_overflow_underflow_status_pair6 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_stat_reg0_13 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> otask_reng_rbf_fifo_overflow_underflow_status_pair5 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_stat_reg0_12 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> otask_reng_rbf_fifo_overflow_underflow_status_pair4 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_stat_reg0_11 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> otask_reng_rbf_fifo_overflow_underflow_status_pair3 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_stat_reg0_10 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> otask_reng_rbf_fifo_overflow_underflow_status_pair2 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_stat_reg0_9 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> otask_reng_rbf_fifo_overflow_underflow_status_pair1 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_stat_reg0_8 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> otask_reng_rbf_fifo_overflow_underflow_status_pair0 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_stat_reg0_7 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> opcq_reng_rbf_fifo_overflow_underflow_status_pair7 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_stat_reg0_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> opcq_reng_rbf_fifo_overflow_underflow_status_pair6 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_stat_reg0_5 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> opcq_reng_rbf_fifo_overflow_underflow_status_pair5 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_stat_reg0_4 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> opcq_reng_rbf_fifo_overflow_underflow_status_pair4 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_stat_reg0_3 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> opcq_reng_rbf_fifo_overflow_underflow_status_pair3 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_stat_reg0_2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> opcq_reng_rbf_fifo_overflow_underflow_status_pair2 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_stat_reg0_1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> opcq_reng_rbf_fifo_overflow_underflow_status_pair1 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_stat_reg0_0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> opcq_reng_rbf_fifo_overflow_underflow_status_pair0 </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_int_status_data_reg7_t
 *
 * Implemented by: 
 *      int_status_data_r7
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      ota_fifo_stat_reg0_15                     :  2;
     unsigned      ota_fifo_stat_reg0_14                     :  2;
     unsigned      ota_fifo_stat_reg0_13                     :  2;
     unsigned      ota_fifo_stat_reg0_12                     :  2;
     unsigned      ota_fifo_stat_reg0_11                     :  2;
     unsigned      ota_fifo_stat_reg0_10                     :  2;
     unsigned      ota_fifo_stat_reg0_9                      :  2;
     unsigned      ota_fifo_stat_reg0_8                      :  2;
     unsigned      ota_fifo_stat_reg0_7                      :  2;
     unsigned      ota_fifo_stat_reg0_6                      :  2;
     unsigned      ota_fifo_stat_reg0_5                      :  2;
     unsigned      ota_fifo_stat_reg0_4                      :  2;
     unsigned      ota_fifo_stat_reg0_3                      :  2;
     unsigned      ota_fifo_stat_reg0_2                      :  2;
     unsigned      ota_fifo_stat_reg0_1                      :  2;
     unsigned      ota_fifo_stat_reg0_0                      :  2;
#else    /* Little Endian */
     unsigned      ota_fifo_stat_reg0_0                      :  2;
     unsigned      ota_fifo_stat_reg0_1                      :  2;
     unsigned      ota_fifo_stat_reg0_2                      :  2;
     unsigned      ota_fifo_stat_reg0_3                      :  2;
     unsigned      ota_fifo_stat_reg0_4                      :  2;
     unsigned      ota_fifo_stat_reg0_5                      :  2;
     unsigned      ota_fifo_stat_reg0_6                      :  2;
     unsigned      ota_fifo_stat_reg0_7                      :  2;
     unsigned      ota_fifo_stat_reg0_8                      :  2;
     unsigned      ota_fifo_stat_reg0_9                      :  2;
     unsigned      ota_fifo_stat_reg0_10                     :  2;
     unsigned      ota_fifo_stat_reg0_11                     :  2;
     unsigned      ota_fifo_stat_reg0_12                     :  2;
     unsigned      ota_fifo_stat_reg0_13                     :  2;
     unsigned      ota_fifo_stat_reg0_14                     :  2;
     unsigned      ota_fifo_stat_reg0_15                     :  2;
#endif
} ncp_nca_int_status_data_reg7_t;

/*! @struct ncp_nca_int_status_data_reg8_t
 *  @brief INT Status Data Register8
 *  @details defines interrupt causing and/or related data
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_int_status_data_reg8_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param otsd_fifo_stat_reg1_7 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> otsd_reng_rbf_fifo_overflow_underflow_status_pair7 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otsd_fifo_stat_reg1_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> otsd_reng_rbf_fifo_overflow_underflow_status_pair6 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otsd_fifo_stat_reg1_5 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> otsd_reng_rbf_fifo_overflow_underflow_status_pair5 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otsd_fifo_stat_reg1_4 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> otsd_reng_rbf_fifo_overflow_underflow_status_pair4 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otsd_fifo_stat_reg1_3 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> otsd_reng_rbf_fifo_overflow_underflow_status_pair3 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otsd_fifo_stat_reg1_2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> otsd_reng_rbf_fifo_overflow_underflow_status_pair2 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otsd_fifo_stat_reg1_1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> otsd_reng_rbf_fifo_overflow_underflow_status_pair1 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otsd_fifo_stat_reg1_0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> otsd_reng_rbf_fifo_overflow_underflow_status_pair0 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otsd_fifo_stat_reg0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> otsd_reng_req_fifo_overflow_underflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_stat_reg1_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> opcq_entry_fifo_overflow_underflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_stat_reg1_5 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> opcq_index_fifo_overflow_underflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_stat_reg1_4 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> opcq_index_update_fifo_overflow_underflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_stat_reg1_3 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> opcq_pgitr_fifo_overflow_underflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_stat_reg1_2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> opcq_pgitw_fifo_overflow_underflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_stat_reg1_1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> otask_reng_req_fifo_overflow_underflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_stat_reg1_0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> opcq_reng_req_fifo_overflow_underflow_status </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_int_status_data_reg8_t
 *
 * Implemented by: 
 *      int_status_data_r8
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      otsd_fifo_stat_reg1_7                     :  2;
     unsigned      otsd_fifo_stat_reg1_6                     :  2;
     unsigned      otsd_fifo_stat_reg1_5                     :  2;
     unsigned      otsd_fifo_stat_reg1_4                     :  2;
     unsigned      otsd_fifo_stat_reg1_3                     :  2;
     unsigned      otsd_fifo_stat_reg1_2                     :  2;
     unsigned      otsd_fifo_stat_reg1_1                     :  2;
     unsigned      otsd_fifo_stat_reg1_0                     :  2;
     unsigned      otsd_fifo_stat_reg0                       :  2;
     unsigned      ota_fifo_stat_reg1_6                      :  2;
     unsigned      ota_fifo_stat_reg1_5                      :  2;
     unsigned      ota_fifo_stat_reg1_4                      :  2;
     unsigned      ota_fifo_stat_reg1_3                      :  2;
     unsigned      ota_fifo_stat_reg1_2                      :  2;
     unsigned      ota_fifo_stat_reg1_1                      :  2;
     unsigned      ota_fifo_stat_reg1_0                      :  2;
#else    /* Little Endian */
     unsigned      ota_fifo_stat_reg1_0                      :  2;
     unsigned      ota_fifo_stat_reg1_1                      :  2;
     unsigned      ota_fifo_stat_reg1_2                      :  2;
     unsigned      ota_fifo_stat_reg1_3                      :  2;
     unsigned      ota_fifo_stat_reg1_4                      :  2;
     unsigned      ota_fifo_stat_reg1_5                      :  2;
     unsigned      ota_fifo_stat_reg1_6                      :  2;
     unsigned      otsd_fifo_stat_reg0                       :  2;
     unsigned      otsd_fifo_stat_reg1_0                     :  2;
     unsigned      otsd_fifo_stat_reg1_1                     :  2;
     unsigned      otsd_fifo_stat_reg1_2                     :  2;
     unsigned      otsd_fifo_stat_reg1_3                     :  2;
     unsigned      otsd_fifo_stat_reg1_4                     :  2;
     unsigned      otsd_fifo_stat_reg1_5                     :  2;
     unsigned      otsd_fifo_stat_reg1_6                     :  2;
     unsigned      otsd_fifo_stat_reg1_7                     :  2;
#endif
} ncp_nca_int_status_data_reg8_t;

/*! @struct ncp_nca_int_status_data_reg9_t
 *  @brief INT Status Data Register9
 *  @details defines interrupt causing and/or related data
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_int_status_data_reg9_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_fifo_stat10 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> tpcq_pgitr_fifo_overflow_underflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_fifo_stat9 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> tpcq_pgitw_fifo_overflow_underflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_fifo_stat8 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> tfc_reng_req_fifo_overflow_underflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_fifo_stat7 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> tfc_reng_rbf_fifo_overflow_underflow_status_pair7 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_fifo_stat6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> tfc_reng_rbf_fifo_overflow_underflow_status_pair6 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_fifo_stat5 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> tfc_reng_rbf_fifo_overflow_underflow_status_pair5 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_fifo_stat4 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> tfc_reng_rbf_fifo_overflow_underflow_status_pair4 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_fifo_stat3 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> tfc_reng_rbf_fifo_overflow_underflow_status_pair3 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_fifo_stat2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> tfc_reng_rbf_fifo_overflow_underflow_status_pair2 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_fifo_stat1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> tfc_reng_rbf_fifo_overflow_underflow_status_pair1 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_fifo_stat0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> tfc_reng_rbf_fifo_overflow_underflow_status_pair0 </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_int_status_data_reg9_t
 *
 * Implemented by: 
 *      int_status_data_r9
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 10;
     unsigned      tfc_fifo_stat10                           :  2;
     unsigned      tfc_fifo_stat9                            :  2;
     unsigned      tfc_fifo_stat8                            :  2;
     unsigned      tfc_fifo_stat7                            :  2;
     unsigned      tfc_fifo_stat6                            :  2;
     unsigned      tfc_fifo_stat5                            :  2;
     unsigned      tfc_fifo_stat4                            :  2;
     unsigned      tfc_fifo_stat3                            :  2;
     unsigned      tfc_fifo_stat2                            :  2;
     unsigned      tfc_fifo_stat1                            :  2;
     unsigned      tfc_fifo_stat0                            :  2;
#else    /* Little Endian */
     unsigned      tfc_fifo_stat0                            :  2;
     unsigned      tfc_fifo_stat1                            :  2;
     unsigned      tfc_fifo_stat2                            :  2;
     unsigned      tfc_fifo_stat3                            :  2;
     unsigned      tfc_fifo_stat4                            :  2;
     unsigned      tfc_fifo_stat5                            :  2;
     unsigned      tfc_fifo_stat6                            :  2;
     unsigned      tfc_fifo_stat7                            :  2;
     unsigned      tfc_fifo_stat8                            :  2;
     unsigned      tfc_fifo_stat9                            :  2;
     unsigned      tfc_fifo_stat10                           :  2;
     unsigned      reserved0                                 : 10;
#endif
} ncp_nca_int_status_data_reg9_t;

/*! @struct ncp_nca_int_status_data_reg10_t
 *  @brief INT Status Data Register10
 *  @details defines interrupt causing and/or related data
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_int_status_data_reg10_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_reng_err_resp </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> configuration manager read engine AXI read error response </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_int_status_data_reg10_t
 *
 * Implemented by: 
 *      int_status_data_r10
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 30;
     unsigned      cmn_reng_err_resp                         :  2;
#else    /* Little Endian */
     unsigned      cmn_reng_err_resp                         :  2;
     unsigned      reserved0                                 : 30;
#endif
} ncp_nca_int_status_data_reg10_t;

/*! @struct ncp_nca_int_status_data_reg11_t
 *  @brief INT Status Data Register11
 *  @details defines interrupt causing and/or related data
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_int_status_data_reg11_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_cfg_req_fifo_ovf_unf_stat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> cmn_cfg_req_fifo_overflow_underflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_req_fifo_parity_err_stat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> cmn_reng_req_fifo_parity_error_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_rbf_fifo_parity_err_stat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> cmn_reng_rbf_fifo_parity_error_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_req_fifo_ovf_unf_stat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> cmn_reng_req_fifo_overflow_underflow_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_rbf_fifo_ovf_unf_stat1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> cmn_reng_rbf_fifo_overflow_underflow_status_pair1 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_rbf_fifo_ovf_unf_stat0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> cmn_reng_rbf_fifo_overflow_underflow_status_pair0 </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_int_status_data_reg11_t
 *
 * Implemented by: 
 *      int_status_data_r11
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      cmn_cfg_req_fifo_ovf_unf_stat             :  2;
     unsigned      cmn_req_fifo_parity_err_stat              :  1;
     unsigned      reserved1                                 :  6;
     unsigned      cmn_rbf_fifo_parity_err_stat              :  2;
     unsigned      cmn_req_fifo_ovf_unf_stat                 :  2;
     unsigned      reserved2                                 : 12;
     unsigned      cmn_rbf_fifo_ovf_unf_stat1                :  2;
     unsigned      cmn_rbf_fifo_ovf_unf_stat0                :  2;
#else    /* Little Endian */
     unsigned      cmn_rbf_fifo_ovf_unf_stat0                :  2;
     unsigned      cmn_rbf_fifo_ovf_unf_stat1                :  2;
     unsigned      reserved2                                 : 12;
     unsigned      cmn_req_fifo_ovf_unf_stat                 :  2;
     unsigned      cmn_rbf_fifo_parity_err_stat              :  2;
     unsigned      reserved1                                 :  6;
     unsigned      cmn_req_fifo_parity_err_stat              :  1;
     unsigned      cmn_cfg_req_fifo_ovf_unf_stat             :  2;
     unsigned      reserved0                                 :  3;
#endif
} ncp_nca_int_status_data_reg11_t;

/*! @struct ncp_nca_par_error_status0_reg_t
 *  @brief Parity Error Status Register 0
 *  @details defines Parity Error causing status
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_par_error_status0_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_weng_req_par_err_stat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> cmn_weng_req_fifo_par_err_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_weng_wdb_par_err_stat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> cmn_weng_wdb_fifo_par_err_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ita_weng_req_par_err_stat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> ita_weng_req_fifo_par_err_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ita_weng_wdb_par_err_stat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> ita_weng_wdb_fifo_par_err_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otsd_req_par_err_stat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> otsd_reng_req_fifo_par_err_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otsd_rbf_par_err_stat </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> otsd_reng_rbf_fifo_par_err_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_entry_par_err_stat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> opcq_entry_fifo_par_err_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_req_par_err_stat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> otask_reng_req_fifo_par_err_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_req_par_err_stat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> opcq_reng_req_fifo_par_err_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_rbf_par_err_stat </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> otask_reng_rbf_fifo_par_err_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_rbf_par_err_stat </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> opcq_reng_rbf_fifo_par_err_status </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_par_error_status0_reg_t
 *
 * Implemented by: 
 *      par_error_status0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      cmn_weng_req_par_err_stat                 :  1;
     unsigned      cmn_weng_wdb_par_err_stat                 :  1;
     unsigned      ita_weng_req_par_err_stat                 :  1;
     unsigned      ita_weng_wdb_par_err_stat                 :  1;
     unsigned      otsd_req_par_err_stat                     :  1;
     unsigned      otsd_rbf_par_err_stat                     :  8;
     unsigned      opcq_entry_par_err_stat                   :  1;
     unsigned      otask_req_par_err_stat                    :  1;
     unsigned      opcq_req_par_err_stat                     :  1;
     unsigned      otask_rbf_par_err_stat                    :  8;
     unsigned      opcq_rbf_par_err_stat                     :  8;
#else    /* Little Endian */
     unsigned      opcq_rbf_par_err_stat                     :  8;
     unsigned      otask_rbf_par_err_stat                    :  8;
     unsigned      opcq_req_par_err_stat                     :  1;
     unsigned      otask_req_par_err_stat                    :  1;
     unsigned      opcq_entry_par_err_stat                   :  1;
     unsigned      otsd_rbf_par_err_stat                     :  8;
     unsigned      otsd_req_par_err_stat                     :  1;
     unsigned      ita_weng_wdb_par_err_stat                 :  1;
     unsigned      ita_weng_req_par_err_stat                 :  1;
     unsigned      cmn_weng_wdb_par_err_stat                 :  1;
     unsigned      cmn_weng_req_par_err_stat                 :  1;
#endif
} ncp_nca_par_error_status0_reg_t;

/*! @struct ncp_nca_par_error_status1_reg_t
 *  @brief Parity Error Status Register 1
 *  @details defines Parity Error causing status
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_par_error_status1_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_weng_req_par_err_stat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> pgit_weng_req_fifo_par_err_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_weng_wdb_par_err_stat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> pgit_weng_wdb_fifo_par_err_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_reng_req_par_err_stat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> pgit_reng_req_fifo_par_err_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_reng_rbf_par_err_stat </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> pgit_reng_rbf_fifo_par_err_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_req_par_err_stat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> tfc_reng_req_fifo_par_err_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_rbf_par_err_stat </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> tfc_reng_rbf_fifo_par_err_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_req_par_err_stat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> rbp_reng_req_fifo_par_err_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_rbf_par_err_stat </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> rbp_reng_rbf_fifo_par_err_status </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_par_error_status1_reg_t
 *
 * Implemented by: 
 *      par_error_status1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      pgit_weng_req_par_err_stat                :  1;
     unsigned      pgit_weng_wdb_par_err_stat                :  1;
     unsigned      pgit_reng_req_par_err_stat                :  1;
     unsigned      pgit_reng_rbf_par_err_stat                :  8;
     unsigned      tfc_req_par_err_stat                      :  1;
     unsigned      tfc_rbf_par_err_stat                      :  8;
     unsigned      rbp_req_par_err_stat                      :  1;
     unsigned      rbp_rbf_par_err_stat                      :  8;
#else    /* Little Endian */
     unsigned      rbp_rbf_par_err_stat                      :  8;
     unsigned      rbp_req_par_err_stat                      :  1;
     unsigned      tfc_rbf_par_err_stat                      :  8;
     unsigned      tfc_req_par_err_stat                      :  1;
     unsigned      pgit_reng_rbf_par_err_stat                :  8;
     unsigned      pgit_reng_req_par_err_stat                :  1;
     unsigned      pgit_weng_wdb_par_err_stat                :  1;
     unsigned      pgit_weng_req_par_err_stat                :  1;
     unsigned      reserved0                                 :  3;
#endif
} ncp_nca_par_error_status1_reg_t;

/*! @struct ncp_nca_ipcq_almost_full_value_reg_t
 *  @brief iPCQ input task Almost-Full value register
 *  @details (max num of queue entries - curr num of queue entries) is defined by this reg
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_ipcq_almost_full_value_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ipcq_almost_full_value </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> ipcq_almost_full_value </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_ipcq_almost_full_value_reg_t
 *
 * Implemented by: 
 *      ipcq_almost_full_value
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      ipcq_almost_full_value                    : 16;
#else    /* Little Endian */
     unsigned      ipcq_almost_full_value                    : 16;
     unsigned      reserved0                                 : 16;
#endif
} ncp_nca_ipcq_almost_full_value_reg_t;

/*! @struct ncp_nca_cfg_ring_ack_timer_cnt_reg_t
 *  @brief CFG RING ACK Timer Register
 *  @details if enabled, this counter defines a Time-Out value for ACK responses
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_cfg_ring_ack_timer_cnt_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_ack_timer_timeout </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> cfg_ring_ack_timer_timeout_value </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_cfg_ring_ack_timer_cnt_reg_t
 *
 * Implemented by: 
 *      cfg_ring_ack_timer_cnt
 */
 
typedef struct
{
     unsigned  int      cfg_ring_ack_timer_timeout;
} ncp_nca_cfg_ring_ack_timer_cnt_reg_t;

/*! @struct ncp_nca_pcq_kickstart_reg_t
 *  @brief PCQ Kickstart Register
 *  @details NOT SUPPORTED FOR MISSION-MODE OPERATION.  This register is used by the CPU to directly write the CPU index in the NCA's PCQ logic for an oPCQ, tPCQ, rPCQ, or cPCQ.  Caution: a race condition could occur with a normal PGIT load.  A kicktart could be followed by a PGIT load with stale data.  The Kickstart Interface should be used for testing purposes only.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_pcq_kickstart_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param kickstart_index_num </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> kickstart_index_num </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param kickstart_pcq_sel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> kickstart_pcq_sel:00:oPCQ,01:tPCQ,10:rPCQ,11:cPCQ </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param kickstart_group_num </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> kickstart_group_num </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param kickstart_index </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> kickstart_index </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_pcq_kickstart_reg_t
 *
 * Implemented by: 
 *      pcq_kickstart
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      kickstart_index_num                       :  8;
     unsigned      kickstart_pcq_sel                         :  2;
     unsigned      kickstart_group_num                       :  3;
     unsigned      kickstart_index                           : 16;
#else    /* Little Endian */
     unsigned      kickstart_index                           : 16;
     unsigned      kickstart_group_num                       :  3;
     unsigned      kickstart_pcq_sel                         :  2;
     unsigned      kickstart_index_num                       :  8;
     unsigned      reserved0                                 :  3;
#endif
} ncp_nca_pcq_kickstart_reg_t;

/*! @struct ncp_nca_pgit_load_grp_indexes_reg_t
 *  @brief PGIT Load NCA and CPU Indexes Register
 *  @details CPU can write to this register to force the PGIT to load the group indexes
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_pgit_load_grp_indexes_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param load_nca_index_grp </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> load_nca_indexes </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param load_cpu_index_grp </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> load_cpu_indexes </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_pgit_load_grp_indexes_reg_t
 *
 * Implemented by: 
 *      pgit_load_grp_indexes
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 10;
     unsigned      load_nca_index_grp                        :  6;
     unsigned      reserved1                                 : 10;
     unsigned      load_cpu_index_grp                        :  6;
#else    /* Little Endian */
     unsigned      load_cpu_index_grp                        :  6;
     unsigned      reserved1                                 : 10;
     unsigned      load_nca_index_grp                        :  6;
     unsigned      reserved0                                 : 10;
#endif
} ncp_nca_pgit_load_grp_indexes_reg_t;

/*! @struct ncp_nca_pgit_grp_load_timer_reg_t
 *  @brief PGIT Group Load Timer Value to Load CPU Indexes
 *  @details This value is used to set the delay for the timer for the PGIT to load CPU Indexes when a hardware or software poke occurs.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_pgit_grp_load_timer_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param set_timer_cpu_load </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> number of sysclk cycles for the cpu timer to expire </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_pgit_grp_load_timer_reg_t
 *
 * Implemented by: 
 *      pgit_grp_load_timer
 */
 
typedef struct
{
     unsigned  int        set_timer_cpu_load;
} ncp_nca_pgit_grp_load_timer_reg_t;

/*! @struct ncp_nca_delay_grp_load_timer_reg_t
 *  @brief PGIT Poke Shorten Delay Value to Load CPU Indexes
 *  @details This value is used to shorten the delay for the timer for the PGIT to load CPU Indexes when a hardware poke occurs.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_delay_grp_load_timer_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param set_timer_delay_load </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> number of sysclk cycles for the nca timer to expire </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_delay_grp_load_timer_reg_t
 *
 * Implemented by: 
 *      delay_grp_load_timer
 */
 
typedef struct
{
     unsigned  int      set_timer_delay_load;
} ncp_nca_delay_grp_load_timer_reg_t;

/*! @struct ncp_nca_swpoke_delay_grp_load_timer_reg_t
 *  @brief PGIT Software Poke Shorten Delay Value to Load CPU Indexes
 *  @details This value is used to shorten the delay for the timer for the PGIT to load CPU Indexes when a software poke occurs.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_swpoke_delay_grp_load_timer_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param set_timer_delay_load </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> number of sysclk cycles for the nca timer to expire </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_swpoke_delay_grp_load_timer_reg_t
 *
 * Implemented by: 
 *      swpoke_delay_grp_load_timer
 */
 
typedef struct
{
     unsigned  int      set_timer_delay_load;
} ncp_nca_swpoke_delay_grp_load_timer_reg_t;

/*! @struct ncp_nca_ipcq_etne_delay_grp_load_timer_reg_t
 *  @brief PGIT iPCQ Empty to not Empty Poke Shorten Delay Value to Load CPU Indexes
 *  @details This value is used to shorten the delay for the timer for the PGIT to upload NCA Indexes when a poke occurs because an iPCQ in a group went from empty to not empty.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_ipcq_etne_delay_grp_load_timer_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param set_timer_delay_load </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> number of sysclk cycles for the nca timer to expire </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_ipcq_etne_delay_grp_load_timer_reg_t
 *
 * Implemented by: 
 *      ipcq_etne_delay_grp_load_timer
 */
 
typedef struct
{
     unsigned  int      set_timer_delay_load;
} ncp_nca_ipcq_etne_delay_grp_load_timer_reg_t;

/*! @struct ncp_nca_pgit_grp_upload_timer_reg_t
 *  @brief PGIT Group UpLoad Timer Value to Upload NCA Indexes
 *  @details This value is used to set the delay for the timer for the PGIT to upload NCA Indexes when a hardware poke occurs.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_pgit_grp_upload_timer_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param set_timer_nca_upload </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> number of sysclk cycles for the nca timer to expire </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_pgit_grp_upload_timer_reg_t
 *
 * Implemented by: 
 *      pgit_grp_upload_timer
 */
 
typedef struct
{
     unsigned  int      set_timer_nca_upload;
} ncp_nca_pgit_grp_upload_timer_reg_t;

/*! @struct ncp_nca_delay_grp_upload_timer_reg_t
 *  @brief PGIT Poke Shorten Delay Value to Upload NCA Indexes
 *  @details This value is used to shorten the delay for the timer for the PGIT to upload NCA Indexes when a hardware poke occurs.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_delay_grp_upload_timer_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param set_timer_delay_upload </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> number of sysclk cycles for the nca timer to expire </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_delay_grp_upload_timer_reg_t
 *
 * Implemented by: 
 *      delay_grp_upload_timer
 */
 
typedef struct
{
     unsigned  int      set_timer_delay_upload;
} ncp_nca_delay_grp_upload_timer_reg_t;

/*! @struct ncp_nca_itask_arrival_poke_grp_cnt_compare_reg_t
 *  @brief Input Task Arrival Poke Group Count Compare Register
 *  @details This register defines a count value for input tasks received for a given group that will trigger a poke to the PGIT upload and load timers.  The poke is disabled when the count is set to zero.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_itask_arrival_poke_grp_cnt_compare_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cnt_cmp_value </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> This field is compared to an internal counter that
 *        tracks the number of itasks received to  determine
 *        when to do a poke of the PGIT load  and upload timers.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_itask_arrival_poke_grp_cnt_compare_reg_t
 *
 * Implemented by: 
 *      itask_arrival_poke_grp_cnt_cmpr
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cnt_cmp_value                             :  8;
#else    /* Little Endian */
     unsigned      cnt_cmp_value                             :  8;
     unsigned      reserved0                                 : 24;
#endif
} ncp_nca_itask_arrival_poke_grp_cnt_compare_reg_t;

/*! @struct ncp_nca_otask_and_cpcq_entry_grp_cnt_compare_reg_t
 *  @brief Output Task and cPCQ Entry Group Count Compare Register
 *  @details This register defines a count value for output tasks and cPCQ entries processed for a given group that will trigger a poke to the PGIT upload and load timers.  The poke is disabled when the count is set to zero.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_otask_and_cpcq_entry_grp_cnt_compare_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cnt_cmp_value </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> This field is compared to an internal counter that
 *        tracks the number of otasks and cPCQ entries  processed
 *        to determine when to do a poke of the  PGIT load
 *        and upload timers.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_otask_and_cpcq_entry_grp_cnt_compare_reg_t
 *
 * Implemented by: 
 *      otask_and_cpcq_entry_grp_cnt_cmpr
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cnt_cmp_value                             :  8;
#else    /* Little Endian */
     unsigned      cnt_cmp_value                             :  8;
     unsigned      reserved0                                 : 24;
#endif
} ncp_nca_otask_and_cpcq_entry_grp_cnt_compare_reg_t;

/*! @struct ncp_nca_hw_poke_and_timer_enable_reg_t
 *  @brief Software Enable switches for Pointer Write and Read Pokes
 *  @details CPU can enable Pointer Load/Upload/Delay events
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_hw_poke_and_timer_enable_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hardware_load_poke_en </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> hardware_load_poke_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hardware_upload_poke_en </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> hardware_upload_poke_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_poke_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> cpcq_poke_enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_poke_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> tpcq_poke_enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_poke_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> opcq_poke_enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ipcq_poke_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> ipcq_poke_enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp5_load_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> grp5_load_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp4_load_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> grp4_load_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp3_load_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> grp3_load_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp2_load_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> grp2_load_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp1_load_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> grp1_load_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp0_load_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> grp0_load_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp5_upload_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> grp5_upload_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp4_upload_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> grp4_upload_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp3_upload_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> grp3_upload_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp2_upload_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> grp2_upload_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp1_upload_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> grp1_upload_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp0_upload_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> grp0_upload_timer_en </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_hw_poke_and_timer_enable_reg_t
 *
 * Implemented by: 
 *      hw_poke_and_timer_enable
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  2;
     unsigned      hardware_load_poke_en                     :  6;
     unsigned      reserved1                                 :  2;
     unsigned      hardware_upload_poke_en                   :  6;
     unsigned      cpcq_poke_enable                          :  1;
     unsigned      tpcq_poke_enable                          :  1;
     unsigned      opcq_poke_enable                          :  1;
     unsigned      ipcq_poke_enable                          :  1;
     unsigned      grp5_load_timer_en                        :  1;
     unsigned      grp4_load_timer_en                        :  1;
     unsigned      grp3_load_timer_en                        :  1;
     unsigned      grp2_load_timer_en                        :  1;
     unsigned      grp1_load_timer_en                        :  1;
     unsigned      grp0_load_timer_en                        :  1;
     unsigned      grp5_upload_timer_en                      :  1;
     unsigned      grp4_upload_timer_en                      :  1;
     unsigned      grp3_upload_timer_en                      :  1;
     unsigned      grp2_upload_timer_en                      :  1;
     unsigned      grp1_upload_timer_en                      :  1;
     unsigned      grp0_upload_timer_en                      :  1;
#else    /* Little Endian */
     unsigned      grp0_upload_timer_en                      :  1;
     unsigned      grp1_upload_timer_en                      :  1;
     unsigned      grp2_upload_timer_en                      :  1;
     unsigned      grp3_upload_timer_en                      :  1;
     unsigned      grp4_upload_timer_en                      :  1;
     unsigned      grp5_upload_timer_en                      :  1;
     unsigned      grp0_load_timer_en                        :  1;
     unsigned      grp1_load_timer_en                        :  1;
     unsigned      grp2_load_timer_en                        :  1;
     unsigned      grp3_load_timer_en                        :  1;
     unsigned      grp4_load_timer_en                        :  1;
     unsigned      grp5_load_timer_en                        :  1;
     unsigned      ipcq_poke_enable                          :  1;
     unsigned      opcq_poke_enable                          :  1;
     unsigned      tpcq_poke_enable                          :  1;
     unsigned      cpcq_poke_enable                          :  1;
     unsigned      hardware_upload_poke_en                   :  6;
     unsigned      reserved1                                 :  2;
     unsigned      hardware_load_poke_en                     :  6;
     unsigned      reserved0                                 :  2;
#endif
} ncp_nca_hw_poke_and_timer_enable_reg_t;

/*! @struct ncp_nca_hw_poke_flags_reg_t
 *  @brief HW POINTER POKE FLAGS
 *  @details Flags for HW Pointer Upload Poke events.  NOT SUPPORTED FOR MISSION-MODE OPERATION.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_hw_poke_flags_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 26 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hardware_grp5_upload_flag </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> hardware_grp5_upload_flag </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hardware_grp4_upload_flag </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> hardware_grp4_upload_flag </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hardware_grp3_upload_flag </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> hardware_grp3_upload_flag </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hardware_grp2_upload_flag </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> hardware_grp2_upload_flag </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hardware_grp1_upload_flag </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> hardware_grp1_upload_flag </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hardware_grp0_upload_flag </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> hardware_grp0_upload_flag </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_hw_poke_flags_reg_t
 *
 * Implemented by: 
 *      hw_upload_poke_flags
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 26;
     unsigned      hardware_grp5_upload_flag                 :  1;
     unsigned      hardware_grp4_upload_flag                 :  1;
     unsigned      hardware_grp3_upload_flag                 :  1;
     unsigned      hardware_grp2_upload_flag                 :  1;
     unsigned      hardware_grp1_upload_flag                 :  1;
     unsigned      hardware_grp0_upload_flag                 :  1;
#else    /* Little Endian */
     unsigned      hardware_grp0_upload_flag                 :  1;
     unsigned      hardware_grp1_upload_flag                 :  1;
     unsigned      hardware_grp2_upload_flag                 :  1;
     unsigned      hardware_grp3_upload_flag                 :  1;
     unsigned      hardware_grp4_upload_flag                 :  1;
     unsigned      hardware_grp5_upload_flag                 :  1;
     unsigned      reserved0                                 : 26;
#endif
} ncp_nca_hw_poke_flags_reg_t;

/*! @struct ncp_nca_num_of_cfg_nodes_reg_t
 *  @brief Number of CFG Loops
 *  @details keeps the number of CFG nodes on each CFG Loop
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_num_of_cfg_nodes_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param num_nodes_loop2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> max_num_of_cfg_nodes_loop2 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param num_nodes_loop1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> max_num_of_cfg_nodes_loop1 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param num_nodes_loop0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> max_num_of_cfg_nodes_loop0 </td>
 * </tr>
 * </table>
 * Applies to: v2 --> ncp_nca_num_of_cfg_nodes_reg_t
 *
 * Implemented by: 
 *      num_of_cfg_nodes
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  8;
     unsigned      num_nodes_loop2                           :  8;
     unsigned      num_nodes_loop1                           :  8;
     unsigned      num_nodes_loop0                           :  8;
#else    /* Little Endian */
     unsigned      num_nodes_loop0                           :  8;
     unsigned      num_nodes_loop1                           :  8;
     unsigned      num_nodes_loop2                           :  8;
     unsigned      reserved0                                 :  8;
#endif
} ncp_nca_num_of_cfg_nodes_reg_t;

/*! @struct ncp_nca_num_of_cfg_nodes_reg_v3_t
 *  @brief Number of CFG Rings
 *  @details keeps the number of CFG nodes on each CFG Ring
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_num_of_cfg_nodes_reg_v3_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param num_nodes_ring2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> max_num_of_cfg_nodes_ring2 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param num_nodes_ring1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> max_num_of_cfg_nodes_ring1 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param num_nodes_ring0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> max_num_of_cfg_nodes_ring0 </td>
 * </tr>
 * </table>
 * Applies to: v3 acp2500 --> ncp_nca_num_of_cfg_nodes_reg_v3_t
 *
 * Implemented by: 
 *      num_of_cfg_nodes
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  8;
     unsigned      num_nodes_ring2                           :  8;
     unsigned      num_nodes_ring1                           :  8;
     unsigned      num_nodes_ring0                           :  8;
#else    /* Little Endian */
     unsigned      num_nodes_ring0                           :  8;
     unsigned      num_nodes_ring1                           :  8;
     unsigned      num_nodes_ring2                           :  8;
     unsigned      reserved0                                 :  8;
#endif
} ncp_nca_num_of_cfg_nodes_reg_v3_t;

/*! @struct ncp_nca_cfg_pio_cdr0_reg_t
 *  @brief PIO Mode Command Data Register 0
 *  @details PIO Mode CFG command descrption register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_cfg_pio_cdr0_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param start_done </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Start/Done, set to 1 to initiate a PIO operation,
 *        cleared when done
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sysmem_access_type </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Defines sysmem/cache access type for SM and CSM commands
 *        sysmem_access_type = 4'b0010; // Cacheable access,
 *        alloc cache , typically used for Regular Sysmem commands
 *        sysmem_access_type = 4'b1111; // Cacheable ATOMIC
 *        access, alloc cache , typically used for Coherent
 *        Sysmem commands
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param local_bit </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Local bit that defines Node's Own Address Space </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param status </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Execution Status : 00= inactive 01= ongoing execution
 *        10= completed with fail 11= completed with success
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param byte_swap_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Byte Swap Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_cmpl_int_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Interrupt Enable on CFG Command Completion </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmd_type </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> CPU CFG Command Type, encoded as: ring_reset = 4'b0001
 *        ring_status = 4'b0010 CRBR (cfg ring block read) =
 *        4'b0100 CRBW (cfg ring block write) = 4'b0101 CRSW
 *        (cfg ring scatter write) = 4'b0110 CRBF (cfg ring
 *        block fill) = 4'b0111 CRRMW (cfg ring read/modify/write)
 *        = 4'b1000 CRBBW (cfg ring broadcast block write) =
 *        4'b1001 CRBSW (cfg ring broadcast scatter write) =
 *        4'b1010 CRBBF (cfg ring broadcast block fill) = 4'b1011
 *        SMBR (sysmem block read) = 4'b1100 SMBW (sysmem block
 *        write) = 4'b1101 CSMBR (coherent sysmem block read)
 *        = 4'b1110 CSMBW (coherent sysmem block write) = 4'b1111
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbs </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data Buffer Size: length of Data Buffer in Bytes 0
 *        means 1 Byte
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_cfg_pio_cdr0_reg_t
 *
 * Implemented by: 
 *      cfg_pio_cdr0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      start_done                                :  1;
     unsigned      reserved0                                 :  2;
     unsigned      sysmem_access_type                        :  4;
     unsigned      local_bit                                 :  1;
     unsigned      status                                    :  2;
     unsigned      byte_swap_enable                          :  1;
     unsigned      cfg_cmpl_int_enable                       :  1;
     unsigned      cmd_type                                  :  4;
     unsigned      dbs                                       : 16;
#else    /* Little Endian */
     unsigned      dbs                                       : 16;
     unsigned      cmd_type                                  :  4;
     unsigned      cfg_cmpl_int_enable                       :  1;
     unsigned      byte_swap_enable                          :  1;
     unsigned      status                                    :  2;
     unsigned      local_bit                                 :  1;
     unsigned      sysmem_access_type                        :  4;
     unsigned      reserved0                                 :  2;
     unsigned      start_done                                :  1;
#endif
} ncp_nca_cfg_pio_cdr0_reg_t;

/*! @struct ncp_nca_cfg_pio_cdr1_reg_t
 *  @brief PIO Mode Command Data Register 1
 *  @details PIO Mode CFG command descrption register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_cfg_pio_cdr1_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param target_address </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> For CR* Commands : CFG Ring Target Address, For CS*
 *        and SM* Commands : System Memory Address Lower bits
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_cfg_pio_cdr1_reg_t
 *
 * Implemented by: 
 *      cfg_pio_cdr1
 */
 
typedef struct
{
     unsigned  int            target_address;
} ncp_nca_cfg_pio_cdr1_reg_t;

/*! @struct ncp_nca_cfg_pio_cdr2_reg_t
 *  @brief PIO Mode Command Data Register 2
 *  @details PIO Mode CFG command descrption register 2
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_cfg_pio_cdr2_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param target_node_id </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> For CR* Commands : CFG Ring Target Node ID, For CS*
 *        and SM* Commands : not applicable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param target_id_address_upper </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> For CR* Commands : CFG Ring Target ID, For CS* and
 *        SM* Commands : System Memory Address Upper bits with
 *        2 msb upper 0's
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_cfg_pio_cdr2_reg_t
 *
 * Implemented by: 
 *      cfg_pio_cdr2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      target_node_id                            :  8;
     unsigned      target_id_address_upper                   :  8;
#else    /* Little Endian */
     unsigned      target_id_address_upper                   :  8;
     unsigned      target_node_id                            :  8;
     unsigned      reserved0                                 : 16;
#endif
} ncp_nca_cfg_pio_cdr2_reg_t;

/*! @struct ncp_nca_cfg_ring_error_stat_reg0_t
 *  @brief CFG Ring Command Error Status Register 0
 *  @details CFG Ring Command Execution error status register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_cfg_ring_error_stat_reg0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param target_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Target_Error_detected </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param node_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Node_Error_detected </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param node_err_type_bit_3_2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Node Error_Type[3:2] when node error </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param time_out_err_or_node_err_type_bit1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> TimeOut Error indication at target error or Node Error_Type_Bit[1] </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param decode_err_or_node_err_type_bit0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Decode Error indication at target error or Node Error_Type_Bit[0] </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param local_bit </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Local Bit </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param instruction </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> CFG Ring instruction </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param inst_len </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Instruction lenght </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param node_id </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Target Node ID </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param target_id </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Target ID </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 --> ncp_nca_cfg_ring_error_stat_reg0_t
 *
 * Implemented by: 
 *      cfg_ring_error_stat_r0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      target_error                              :  1;
     unsigned      node_error                                :  1;
     unsigned      node_err_type_bit_3_2                     :  2;
     unsigned      time_out_err_or_node_err_type_bit1        :  1;
     unsigned      decode_err_or_node_err_type_bit0          :  1;
     unsigned      local_bit                                 :  1;
     unsigned      instruction                               :  3;
     unsigned      inst_len                                  :  6;
     unsigned      node_id                                   :  8;
     unsigned      target_id                                 :  8;
#else    /* Little Endian */
     unsigned      target_id                                 :  8;
     unsigned      node_id                                   :  8;
     unsigned      inst_len                                  :  6;
     unsigned      instruction                               :  3;
     unsigned      local_bit                                 :  1;
     unsigned      decode_err_or_node_err_type_bit0          :  1;
     unsigned      time_out_err_or_node_err_type_bit1        :  1;
     unsigned      node_err_type_bit_3_2                     :  2;
     unsigned      node_error                                :  1;
     unsigned      target_error                              :  1;
#endif
} ncp_nca_cfg_ring_error_stat_reg0_t;

/*! @struct ncp_nca_cfg_ring_error_stat_reg0_acp2500_t
 *  @brief CFG Ring Command Error Status Register 0
 *  @details CFG Ring Command Execution error status register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_cfg_ring_error_stat_reg0_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param target_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Target_Error_detected </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param node_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Node_Error_detected </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param node_err_type_bit_3_2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Node Error_Type[3:2] when node error </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param time_out_err_or_node_err_type_bit1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> TimeOut Error indication at target error or Node Error_Type_Bit[1] </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param decode_err_or_node_err_type_bit0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Decode Error indication at target error or Node Error_Type_Bit[0] </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param local_bit </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Local Bit </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param instruction </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> CFG Ring instruction </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param inst_len </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Instruction lenght </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ring_id </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Ring ID </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param node_id </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Target Node ID </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param target_id </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Target ID </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_cfg_ring_error_stat_reg0_acp2500_t
 *
 * Implemented by: 
 *      cfg_ring_error_stat_r0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      target_error                              :  1;
     unsigned      node_error                                :  1;
     unsigned      node_err_type_bit_3_2                     :  2;
     unsigned      time_out_err_or_node_err_type_bit1        :  1;
     unsigned      decode_err_or_node_err_type_bit0          :  1;
     unsigned      local_bit                                 :  1;
     unsigned      instruction                               :  3;
     unsigned      inst_len                                  :  6;
     unsigned      ring_id                                   :  2;
     unsigned      node_id                                   :  6;
     unsigned      target_id                                 :  8;
#else    /* Little Endian */
     unsigned      target_id                                 :  8;
     unsigned      node_id                                   :  6;
     unsigned      ring_id                                   :  2;
     unsigned      inst_len                                  :  6;
     unsigned      instruction                               :  3;
     unsigned      local_bit                                 :  1;
     unsigned      decode_err_or_node_err_type_bit0          :  1;
     unsigned      time_out_err_or_node_err_type_bit1        :  1;
     unsigned      node_err_type_bit_3_2                     :  2;
     unsigned      node_error                                :  1;
     unsigned      target_error                              :  1;
#endif
} ncp_nca_cfg_ring_error_stat_reg0_acp2500_t;

/*! @struct ncp_nca_cfg_ring_error_stat_reg1_t
 *  @brief CFG Ring Command Error Status Register 1
 *  @details CFG Ring Command Execution error status register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_cfg_ring_error_stat_reg1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrong_ack_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Wrong ACK received error </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param acktimeout_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> ACK Time-Out Error </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param unclaimed_header_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Unclaimed Header Error </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param parity_err_ring0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Parity Error Ring0 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param parity_err_ring1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Parity Error Ring1 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param parity_err_ring2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Parity Error Ring2 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param local_bit </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Local Bit </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param instruction </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> CFG Ring instruction </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param inst_len </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Instruction length </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param node_id </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Target Node ID </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param target_id </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Target ID </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 --> ncp_nca_cfg_ring_error_stat_reg1_t
 *
 * Implemented by: 
 *      cfg_ring_error_stat_r1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      wrong_ack_err                             :  1;
     unsigned      acktimeout_err                            :  1;
     unsigned      unclaimed_header_err                      :  1;
     unsigned      parity_err_ring0                          :  1;
     unsigned      parity_err_ring1                          :  1;
     unsigned      parity_err_ring2                          :  1;
     unsigned      local_bit                                 :  1;
     unsigned      instruction                               :  3;
     unsigned      inst_len                                  :  6;
     unsigned      node_id                                   :  8;
     unsigned      target_id                                 :  8;
#else    /* Little Endian */
     unsigned      target_id                                 :  8;
     unsigned      node_id                                   :  8;
     unsigned      inst_len                                  :  6;
     unsigned      instruction                               :  3;
     unsigned      local_bit                                 :  1;
     unsigned      parity_err_ring2                          :  1;
     unsigned      parity_err_ring1                          :  1;
     unsigned      parity_err_ring0                          :  1;
     unsigned      unclaimed_header_err                      :  1;
     unsigned      acktimeout_err                            :  1;
     unsigned      wrong_ack_err                             :  1;
#endif
} ncp_nca_cfg_ring_error_stat_reg1_t;

/*! @struct ncp_nca_cfg_ring_error_stat_reg1_acp2500_t
 *  @brief CFG Ring Command Error Status Register 1
 *  @details CFG Ring Command Execution error status register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_cfg_ring_error_stat_reg1_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrong_ack_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Wrong ACK received error </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param acktimeout_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> ACK Time-Out Error </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param unclaimed_header_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Unclaimed Header Error </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param parity_err_ring0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Parity Error Ring0 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param parity_err_ring1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Parity Error Ring1 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param parity_err_ring2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Parity Error Ring2 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param local_bit </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Local Bit </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param instruction </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> CFG Ring instruction </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param inst_len </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Instruction length </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ring_id </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Ring ID </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param node_id </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Target Node ID </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param target_id </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Target ID </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_cfg_ring_error_stat_reg1_acp2500_t
 *
 * Implemented by: 
 *      cfg_ring_error_stat_r1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      wrong_ack_err                             :  1;
     unsigned      acktimeout_err                            :  1;
     unsigned      unclaimed_header_err                      :  1;
     unsigned      parity_err_ring0                          :  1;
     unsigned      parity_err_ring1                          :  1;
     unsigned      parity_err_ring2                          :  1;
     unsigned      local_bit                                 :  1;
     unsigned      instruction                               :  3;
     unsigned      inst_len                                  :  6;
     unsigned      ring_id                                   :  2;
     unsigned      node_id                                   :  6;
     unsigned      target_id                                 :  8;
#else    /* Little Endian */
     unsigned      target_id                                 :  8;
     unsigned      node_id                                   :  6;
     unsigned      ring_id                                   :  2;
     unsigned      inst_len                                  :  6;
     unsigned      instruction                               :  3;
     unsigned      local_bit                                 :  1;
     unsigned      parity_err_ring2                          :  1;
     unsigned      parity_err_ring1                          :  1;
     unsigned      parity_err_ring0                          :  1;
     unsigned      unclaimed_header_err                      :  1;
     unsigned      acktimeout_err                            :  1;
     unsigned      wrong_ack_err                             :  1;
#endif
} ncp_nca_cfg_ring_error_stat_reg1_acp2500_t;

/*! @struct ncp_nca_cfg_ring_node_status_reg_t
 *  @brief CFG Ring Node Status Register
 *  @details This register holds the value returned when status is asked, write 1 to bit16 of NCA Interrupt Register at F000 to clear
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_cfg_ring_node_status_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param node_status </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Node Status </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_cfg_ring_node_status_reg_t
 *
 * Implemented by: 
 *      cfg_ring_node_status
 */
 
typedef struct
{
     unsigned  int               node_status;
} ncp_nca_cfg_ring_node_status_reg_t;

/*! @struct ncp_nca_cnal_if_status_reg_t
 *  @brief CNAL Interface SysMem Read/Write Status Register
 *  @details This register holds the value returned when CNAL I/F status is asked
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_cnal_if_status_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cnal_eng_cwd_ready </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> CMSI Write Data Ready </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cnal_eng_cwr_ready </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> CMSI Write Request Ready </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cnal_eng_crr_ready </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> CMSI Read Request Ready </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cnal_read_transaction_state </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> CNAL Interface Read transaction state </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cnal_write_transaction_state </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> CNAL Interface Write transaction state </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param read_resp_err_code </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CNAL Interface Read Response error </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param write_resp_err_code </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CNAL Interface Write Response error </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_single_l_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CNAL Interface lower word ECC Singlebit error </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_single_u_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CNAL Interface upper word ECC Singlebit error </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_multiple_l_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CNAL Interface lower word ECC Multibit error </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_multiple_u_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CNAL Interface upper word ECC Multibit error </td>
 * </tr>
 * </table>
 * Applies to: v2 --> ncp_nca_cnal_if_status_reg_t
 *
 * Implemented by: 
 *      cnal_if_status
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  8;
     unsigned      cnal_eng_cwd_ready                        :  1;
     unsigned      cnal_eng_cwr_ready                        :  1;
     unsigned      cnal_eng_crr_ready                        :  1;
     unsigned      cnal_read_transaction_state               :  7;
     unsigned      cnal_write_transaction_state              :  6;
     unsigned      read_resp_err_code                        :  2;
     unsigned      write_resp_err_code                       :  2;
     unsigned      ecc_single_l_err                          :  1;
     unsigned      ecc_single_u_err                          :  1;
     unsigned      ecc_multiple_l_err                        :  1;
     unsigned      ecc_multiple_u_err                        :  1;
#else    /* Little Endian */
     unsigned      ecc_multiple_u_err                        :  1;
     unsigned      ecc_multiple_l_err                        :  1;
     unsigned      ecc_single_u_err                          :  1;
     unsigned      ecc_single_l_err                          :  1;
     unsigned      write_resp_err_code                       :  2;
     unsigned      read_resp_err_code                        :  2;
     unsigned      cnal_write_transaction_state              :  6;
     unsigned      cnal_read_transaction_state               :  7;
     unsigned      cnal_eng_crr_ready                        :  1;
     unsigned      cnal_eng_cwr_ready                        :  1;
     unsigned      cnal_eng_cwd_ready                        :  1;
     unsigned      reserved0                                 :  8;
#endif
} ncp_nca_cnal_if_status_reg_t;

/*! @struct ncp_nca_pcq_grp_reg0_t
 *  @brief PCQ Group Register0
 *  @details PCQ Group Base Initialization Register0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_pcq_grp_reg0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param num_out_queues </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of oPCQs (CPU Output Queues) </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param num_in_queues </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of iPCQs (CPU Input Queues) </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_pcq_grp_reg0_t
 *
 * Implemented by: 
 *      pcq_grp_r0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  8;
     unsigned      num_out_queues                            :  8;
     unsigned      reserved1                                 :  8;
     unsigned      num_in_queues                             :  8;
#else    /* Little Endian */
     unsigned      num_in_queues                             :  8;
     unsigned      reserved1                                 :  8;
     unsigned      num_out_queues                            :  8;
     unsigned      reserved0                                 :  8;
#endif
} ncp_nca_pcq_grp_reg0_t;

/*! @struct ncp_nca_pcq_grp_reg1_t
 *  @brief PCQ Group Register1
 *  @details PCQ Group Base Initialization Register1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_pcq_grp_reg1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param num_config_queues </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of cPCQs (CPU Configuration Queues) </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param num_rx_buffer_pool_queues </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Number of rPCQs (CPU receive buffer pool/receive buffer
 *        Queues
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param num_tcomp_queues </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of tPCQs (CPU Task Completion Queues) </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_pcq_grp_reg1_t
 *
 * Implemented by: 
 *      pcq_grp_r1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  8;
     unsigned      num_config_queues                         :  8;
     unsigned      num_rx_buffer_pool_queues                 :  8;
     unsigned      num_tcomp_queues                          :  8;
#else    /* Little Endian */
     unsigned      num_tcomp_queues                          :  8;
     unsigned      num_rx_buffer_pool_queues                 :  8;
     unsigned      num_config_queues                         :  8;
     unsigned      reserved0                                 :  8;
#endif
} ncp_nca_pcq_grp_reg1_t;

/*! @struct ncp_nca_pcq_grp_reg2_t
 *  @brief PCQ Group Register2
 *  @details PCQ Group Base Initialization Register 2
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_pcq_grp_reg2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 26 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_bar_upper </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> NCA PCQ Group Index Table Base Address Register UPPER
 *        BITS[37:32]
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_pcq_grp_reg2_t
 *
 * Implemented by: 
 *      pcq_grp_r2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 26;
     unsigned      pgit_bar_upper                            :  6;
#else    /* Little Endian */
     unsigned      pgit_bar_upper                            :  6;
     unsigned      reserved0                                 : 26;
#endif
} ncp_nca_pcq_grp_reg2_t;

/*! @struct ncp_nca_pcq_grp_reg3_t
 *  @brief PCQ Group Register3
 *  @details PCQ Group Base Initialization Register3
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_pcq_grp_reg3_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_bar_lower </td>
 *     <td width="20%" align="center"> 26 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> NCA PCQ Group Index Table Base Address Register LOWER
 *        BITS[31:6]
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zeros </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 6 Zeros in the lower 6 bits of the BAR </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_pcq_grp_reg3_t
 *
 * Implemented by: 
 *      pcq_grp_r3
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      pgit_bar_lower                            : 26;
     unsigned      zeros                                     :  6;
#else    /* Little Endian */
     unsigned      zeros                                     :  6;
     unsigned      pgit_bar_lower                            : 26;
#endif
} ncp_nca_pcq_grp_reg3_t;

/*! @struct ncp_nca_pcq_grp_reg4_t
 *  @brief PCQ Group Register4
 *  @details PCQ Group Base Initialization Register 4
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_pcq_grp_reg4_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 26 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu_pgit_bar_upper </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU PCQ Group Index Table Base Address Register UPPER
 *        BITS[37:32]
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_pcq_grp_reg4_t
 *
 * Implemented by: 
 *      pcq_grp_r4
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 26;
     unsigned      cpu_pgit_bar_upper                        :  6;
#else    /* Little Endian */
     unsigned      cpu_pgit_bar_upper                        :  6;
     unsigned      reserved0                                 : 26;
#endif
} ncp_nca_pcq_grp_reg4_t;

/*! @struct ncp_nca_pcq_grp_reg5_t
 *  @brief PCQ Group Register5
 *  @details PCQ Group Base Initialization Register 5
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_pcq_grp_reg5_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cpu_pgit_bar_lower </td>
 *     <td width="20%" align="center"> 26 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU PCQ Group Index Table Base Address Register LOWER
 *        BITS[31:6]
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zeros </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 6 Zeros in the lower 6 bits of the BAR </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_pcq_grp_reg5_t
 *
 * Implemented by: 
 *      pcq_grp_r5
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      cpu_pgit_bar_lower                        : 26;
     unsigned      zeros                                     :  6;
#else    /* Little Endian */
     unsigned      zeros                                     :  6;
     unsigned      cpu_pgit_bar_lower                        : 26;
#endif
} ncp_nca_pcq_grp_reg5_t;

/*! @struct ncp_nca_PCQ_desc_reg0_t
 *  @brief PCQ descriptor Register0
 *  @details Register 0 of the PCQ Queue descriptor
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_PCQ_desc_reg0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param number_of_queue_entries </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> The number of Queue entries in the queue </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enable_bit </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Enable 0->queue is disabled, 1->queue is enabled </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbpid </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Receive Buffer Pool ID </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param qentry_bar_upper </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PCQ Queue Entry Base Address UPPER BITS[37:32] </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_PCQ_desc_reg0_t
 *
 * Implemented by: 
 *      PCQ_desc_r0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      number_of_queue_entries                   : 16;
     unsigned      enable_bit                                :  1;
     unsigned      rbpid                                     :  4;
     unsigned      reserved0                                 :  5;
     unsigned      qentry_bar_upper                          :  6;
#else    /* Little Endian */
     unsigned      qentry_bar_upper                          :  6;
     unsigned      reserved0                                 :  5;
     unsigned      rbpid                                     :  4;
     unsigned      enable_bit                                :  1;
     unsigned      number_of_queue_entries                   : 16;
#endif
} ncp_nca_PCQ_desc_reg0_t;

/*! @struct ncp_nca_PCQ_desc_reg1_t
 *  @brief PCQ descriptor Register1
 *  @details Register 1 of the PCQ Queue descriptor
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_PCQ_desc_reg1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param qentry_bar_lower </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PCQ Queue Entry Base Address LOWER BITS[31:0] </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_PCQ_desc_reg1_t
 *
 * Implemented by: 
 *      PCQ_desc_r1
 */
 
typedef struct
{
     unsigned  int          qentry_bar_lower;
} ncp_nca_PCQ_desc_reg1_t;

/*! @struct ncp_nca_PCQ_stat_reg0_t
 *  @brief PCQ Status Register0
 *  @details Register 0 of the PCQ Status
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_PCQ_stat_reg0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cpu_index </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> CPU Index </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param nca_index </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> NCA Index </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_PCQ_stat_reg0_t
 *
 * Implemented by: 
 *      PCQ_stat_r0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      cpu_index                                 : 16;
     unsigned      nca_index                                 : 16;
#else    /* Little Endian */
     unsigned      nca_index                                 : 16;
     unsigned      cpu_index                                 : 16;
#endif
} ncp_nca_PCQ_stat_reg0_t;

/*! @struct ncp_nca_PCQ_stat_reg1_t
 *  @brief PCQ Status Register1
 *  @details Register 1 of the PCQ Status
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_PCQ_stat_reg1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param almost_full </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> almost_full </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param full </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> full </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param empty </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> empty </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param depth </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> depth </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_PCQ_stat_reg1_t
 *
 * Implemented by: 
 *      PCQ_stat_r1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 13;
     unsigned      almost_full                               :  1;
     unsigned      full                                      :  1;
     unsigned      empty                                     :  1;
     unsigned      depth                                     : 16;
#else    /* Little Endian */
     unsigned      depth                                     : 16;
     unsigned      empty                                     :  1;
     unsigned      full                                      :  1;
     unsigned      almost_full                               :  1;
     unsigned      reserved0                                 : 13;
#endif
} ncp_nca_PCQ_stat_reg1_t;

/*! @struct ncp_nca_rcv_buff_pool_size_reg_a_t
 *  @brief NCA Receive Buffer Pool Size
 *  @details receive buffer pool
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rcv_buff_pool_size_reg_a_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rbuff_size_0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Size 0 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbuff_size_1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Size 1 </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_rcv_buff_pool_size_reg_a_t
 *
 * Implemented by: 
 *      size_0_1_r
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rbuff_size_0                              : 16;
     unsigned      rbuff_size_1                              : 16;
#else    /* Little Endian */
     unsigned      rbuff_size_1                              : 16;
     unsigned      rbuff_size_0                              : 16;
#endif
} ncp_nca_rcv_buff_pool_size_reg_a_t;

/*! @struct ncp_nca_rcv_buff_pool_size_reg_b_t
 *  @brief NCA Receive Buffer Pool Size
 *  @details receive buffer pool
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rcv_buff_pool_size_reg_b_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rbuff_size_2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Size 2 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbuff_size_3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Size 3 </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_rcv_buff_pool_size_reg_b_t
 *
 * Implemented by: 
 *      size_2_3_r
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rbuff_size_2                              : 16;
     unsigned      rbuff_size_3                              : 16;
#else    /* Little Endian */
     unsigned      rbuff_size_3                              : 16;
     unsigned      rbuff_size_2                              : 16;
#endif
} ncp_nca_rcv_buff_pool_size_reg_b_t;

/*! @struct ncp_nca_cdar_entry_t
 *  @brief PIO mode data word
 *  @details CDAR local memory for PIO mode
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_cdar_entry_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param pio_mode_word </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PIO mode word entry </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_cdar_entry_t
 *
 * Implemented by: 
 *      cdar_memory
 */
 
typedef struct
{
     unsigned  int             pio_mode_word;
} ncp_nca_cdar_entry_t;

/*! @struct ncp_nca_cdar_entry_last_word_t
 *  @brief PIO mode last data word
 *  @details CDAR local memory word 129 for PIO mode
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_cdar_entry_last_word_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param pio_mode_word_129 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PIO mode word 129 entry </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_cdar_entry_last_word_t
 *
 * Implemented by: 
 *      cdar_word_129
 */
 
typedef struct
{
     unsigned  int         pio_mode_word_129;
} ncp_nca_cdar_entry_last_word_t;

/*! @struct ncp_nca_itask_drop_count_ipcq_er_t
 *  @brief Input Task Drop Count iPCQ Error
 *  @details Counts the number of input tasks dropped due to an iPCQ error.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_itask_drop_count_ipcq_er_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param itask_drop_cnt_ipcq_er </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> iPCQ errors include queue disabled, bad queue indexes
 *        (c or n index >= queue depth), and queue full
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_itask_drop_count_ipcq_er_t
 *
 * Implemented by: 
 *      itask_drop_cnt_ipcq_er
 */
 
typedef struct
{
     unsigned  int      itask_drop_cnt_ipcq_er;
} ncp_nca_itask_drop_count_ipcq_er_t;

/*! @struct ncp_nca_itask_drop_count_no_buffer_t
 *  @brief Input Task Drop Count No Buffer
 *  @details Counts the number of input tasks dropped due to no receive buffer being available.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_itask_drop_count_no_buffer_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param itask_drop_cnt_no_buf </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> number of inut tasks dropped because no receive buffer
 *        was available
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_itask_drop_count_no_buffer_t
 *
 * Implemented by: 
 *      itask_drop_cnt_no_buf
 */
 
typedef struct
{
     unsigned  int      itask_drop_cnt_no_buf;
} ncp_nca_itask_drop_count_no_buffer_t;

/*! @struct ncp_nca_otask_length_compare_reg_t
 *  @brief Ouput Task Length Compare Register
 *  @details Used in conjucnction with the otask_length_capture register to detect when an output task has a length >= the otask_length_compare_value field of this register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_otask_length_compare_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param otask_len_compare_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Output task length compare enable. When this bit is
 *        set, output task length compare is enabled
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 14 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_length_compare_value </td>
 *     <td width="20%" align="center"> 17 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Output task length compare value. </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_otask_length_compare_reg_t
 *
 * Implemented by: 
 *      otask_length_compare
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      otask_len_compare_en                      :  1;
     unsigned      reserved0                                 : 14;
     unsigned      otask_length_compare_value                : 17;
#else    /* Little Endian */
     unsigned      otask_length_compare_value                : 17;
     unsigned      reserved0                                 : 14;
     unsigned      otask_len_compare_en                      :  1;
#endif
} ncp_nca_otask_length_compare_reg_t;

/*! @struct ncp_nca_otask_length_capture_reg_t
 *  @brief Ouput Task Length Capture Register
 *  @details Used in conjunction with the otask_length_compare_reg.  If the otask_length_compare_reg otask_len_compare_en bit is set, the otask_len_exceeded bit of this register is clear, and the length of the current output task being sent by the NCA is >= to the otask_length_compare_reg otask_length_compare_value field, then the otask_len_exceeded bit of this register is set, and the otask_length_capt_value field of this register is set to the length of the output task.  Once the otask_len_exceeded bit is set, comparing is stopped until the otask_len_exceeded bit is cleared by software
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_otask_length_capture_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param otask_len_exceeded </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Output task length exceeded. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 14 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_length_capt_value </td>
 *     <td width="20%" align="center"> 17 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Output task length captured value. </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_otask_length_capture_reg_t
 *
 * Implemented by: 
 *      otask_length_capture
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      otask_len_exceeded                        :  1;
     unsigned      reserved0                                 : 14;
     unsigned      otask_length_capt_value                   : 17;
#else    /* Little Endian */
     unsigned      otask_length_capt_value                   : 17;
     unsigned      reserved0                                 : 14;
     unsigned      otask_len_exceeded                        :  1;
#endif
} ncp_nca_otask_length_capture_reg_t;

/*! @struct ncp_nca_otask_opcq_backpressure_t
 *  @brief Output Task oPCQ Backpressure
 *  @details Indicates when backpressure is asserted by the destinations fed by the oPCQs.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_otask_opcq_backpressure_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param otask_dest_bp </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Each bit corresponds to an output task destination.
 *        Software can monitor this register to determine when
 *        backpressure is being applied by the corresponding
 *        destination.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_otask_opcq_backpressure_t
 *
 * Implemented by: 
 *      otask_opcq_bp
 */
 
typedef struct
{
     unsigned  int             otask_dest_bp;
} ncp_nca_otask_opcq_backpressure_t;

/*! @struct ncp_nca_rcv_buf_pool_tsi_bp_t
 *  @brief Receive Buffer Pool Input Task Backpressure
 *  @details Indicates when backpressure is asserted to the task start interface for the corresponding iPCQ because no receive buffers are available.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rcv_buf_pool_tsi_bp_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_depth_ipcq_bp </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Each bit corresponds to an iPCQ, and indicates when
 *        bacpressure is applied to the task start interface
 *        for that iPCQ because no receive buffers are available
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_rcv_buf_pool_tsi_bp_t
 *
 * Implemented by: 
 *      rbp_itask_bp
 */
 
typedef struct
{
     unsigned  int         rbp_depth_ipcq_bp;
} ncp_nca_rcv_buf_pool_tsi_bp_t;

/*! @struct ncp_nca_tfc_count_reg_t
 *  @brief Task Flow Completion Counters
 *  @details Register 0 of the PCQ Queue descriptor
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_tfc_count_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param xmit_complete_counter </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Xmit Complete Counter </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param completion_counter </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Completion Counter </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_tfc_count_reg_t
 *
 * Implemented by: 
 *      tfc_count_r
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      xmit_complete_counter                     : 16;
     unsigned      completion_counter                        : 16;
#else    /* Little Endian */
     unsigned      completion_counter                        : 16;
     unsigned      xmit_complete_counter                     : 16;
#endif
} ncp_nca_tfc_count_reg_t;

/*! @struct ncp_nca_rbp_depths_reg0_t
 *  @brief Receive Buffer Pool Depths Register0
 *  @details Receive Buffer Pool Depths for Size0 and Size1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_depths_reg0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_depth_size0 </td>
 *     <td width="20%" align="center"> 11 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Pool Depth Size0[10:0] </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_depth_size1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Pool Depth Size1[9:0] </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 --> ncp_nca_rbp_depths_reg0_t
 *
 * Implemented by: 
 *      rbp_depths_r0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  5;
     unsigned      rbp_depth_size0                           : 11;
     unsigned      reserved1                                 :  6;
     unsigned      rbp_depth_size1                           : 10;
#else    /* Little Endian */
     unsigned      rbp_depth_size1                           : 10;
     unsigned      reserved1                                 :  6;
     unsigned      rbp_depth_size0                           : 11;
     unsigned      reserved0                                 :  5;
#endif
} ncp_nca_rbp_depths_reg0_t;

/*! @struct ncp_nca_rbp_depths_reg0_acp2500_t
 *  @brief Receive Buffer Pool Depths Register0
 *  @details Receive Buffer Pool Depths for Size0 and Size1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_depths_reg0_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_depth_size0 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Pool Depth Size0[11:0] </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_depth_size1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Pool Depth Size1[10:0] </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_rbp_depths_reg0_acp2500_t
 *
 * Implemented by: 
 *      rbp_depths_r0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      rbp_depth_size0                           : 12;
     unsigned      reserved1                                 :  5;
     unsigned      rbp_depth_size1                           : 11;
#else    /* Little Endian */
     unsigned      rbp_depth_size1                           : 11;
     unsigned      reserved1                                 :  5;
     unsigned      rbp_depth_size0                           : 12;
     unsigned      reserved0                                 :  4;
#endif
} ncp_nca_rbp_depths_reg0_acp2500_t;

/*! @struct ncp_nca_rbp_depths_reg1_t
 *  @brief Receive Buffer Pool Depths Register1
 *  @details Receive Buffer Pool Depths for Size2 and Size3
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_depths_reg1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_depth_size2 </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Pool Depth Size2[8:0] </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_depth_size3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Pool Depth Size3[7:0] </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 --> ncp_nca_rbp_depths_reg1_t
 *
 * Implemented by: 
 *      rbp_depths_r1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      rbp_depth_size2                           :  9;
     unsigned      reserved1                                 :  8;
     unsigned      rbp_depth_size3                           :  8;
#else    /* Little Endian */
     unsigned      rbp_depth_size3                           :  8;
     unsigned      reserved1                                 :  8;
     unsigned      rbp_depth_size2                           :  9;
     unsigned      reserved0                                 :  7;
#endif
} ncp_nca_rbp_depths_reg1_t;

/*! @struct ncp_nca_rbp_depths_reg1_acp2500_t
 *  @brief Receive Buffer Pool Depths Register1
 *  @details Receive Buffer Pool Depths for Size2 and Size3
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_depths_reg1_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_depth_size2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Pool Depth Size2[9:0] </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_depth_size3 </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Pool Depth Size3[8:0] </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_rbp_depths_reg1_acp2500_t
 *
 * Implemented by: 
 *      rbp_depths_r1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      rbp_depth_size2                           : 10;
     unsigned      reserved1                                 :  7;
     unsigned      rbp_depth_size3                           :  9;
#else    /* Little Endian */
     unsigned      rbp_depth_size3                           :  9;
     unsigned      reserved1                                 :  7;
     unsigned      rbp_depth_size2                           : 10;
     unsigned      reserved0                                 :  6;
#endif
} ncp_nca_rbp_depths_reg1_acp2500_t;

/*! @struct ncp_nca_rbp_itask_bp_en_reg_t
 *  @brief Receive Buffer Pool Input Task Backpressure Enable
 *  @details Used in conjunction with rbp_itask_bp_incld_bsiz_reg. Enables NCA to TIL input task backpressure on a per iPCQ basis when receive buffers are not available.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_itask_bp_en_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_itask_bp_en </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Each bit corresponds to an iPCQ. </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_rbp_itask_bp_en_reg_t
 *
 * Implemented by: 
 *      rbp_itask_bp_en
 */
 
typedef struct
{
     unsigned  int           rbp_itask_bp_en;
} ncp_nca_rbp_itask_bp_en_reg_t;

/*! @struct ncp_nca_rbp_itask_bp_incld_bsiz_reg_t
 *  @brief Receive Buffer Pool Input Task Backpressure Included Buffer Size
 *  @details Used in conjunction with rbp_itask_bp_en_reg. Selects buffer sizes to be included to generate backpressure.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_itask_bp_incld_bsiz_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 28 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_itask_bp_incld_bsiz </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Each bit corresponds to a receive buffer pool size.
 *        At least one bit must be set for receive buffer pool
 *        NCA to TIL input task backpressure to be asserted
 *        for any iPCQ.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_rbp_itask_bp_incld_bsiz_reg_t
 *
 * Implemented by: 
 *      rbp_itask_bp_incld_bsiz
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 28;
     unsigned      rbp_itask_bp_incld_bsiz                   :  4;
#else    /* Little Endian */
     unsigned      rbp_itask_bp_incld_bsiz                   :  4;
     unsigned      reserved0                                 : 28;
#endif
} ncp_nca_rbp_itask_bp_incld_bsiz_reg_t;

/*! @struct ncp_nca_pio_lock_reg_t
 *  @brief NCA PIO Lock Register
 *  @details Provides a semaphore mechanism for multiprocessor sharing of the configuration interface in PIO mode.  Address bits 6:2 form the ID address which indicates the ID of the processor accessing this register.  A processor reads this register to acquire control.  Reading a 0 indicates that the processor has control, and the register bit selected by the ID address is set.  Reading other than zero means that the interface is not available.  The processor in control must write anything to its ID address to clear the register to allow control to pass to another processor.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_pio_lock_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param proc_id </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Only one bit will ever be set at a time. Indicates
 *        ID of processor that has control of configuration
 *        interface.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_pio_lock_reg_t
 *
 * Implemented by: 
 *      nca_pio_lock
 */
 
typedef struct
{
     unsigned  int                   proc_id;
} ncp_nca_pio_lock_reg_t;

/*! @struct ncp_nca_otbp_bar_reg0_t
 *  @brief Output Task Backpressure Base Address Register0
 *  @details Upper 6 bits of address where output task backpressure is written into AXI memory.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_otbp_bar_reg0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 26 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otbp_bar_upper </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Output Task Backpressure Base Address UPPER BITS[37:32] </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_otbp_bar_reg0_t
 *
 * Implemented by: 
 *      otbp_bar_upper
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 26;
     unsigned      otbp_bar_upper                            :  6;
#else    /* Little Endian */
     unsigned      otbp_bar_upper                            :  6;
     unsigned      reserved0                                 : 26;
#endif
} ncp_nca_otbp_bar_reg0_t;

/*! @struct ncp_nca_otbp_bar_reg1_t
 *  @brief Output Task Backpressure Base Address Register1
 *  @details Lower 32 bits of address where output task backpressure is written into AXI memory.  Bits 1:0 are don't care.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_otbp_bar_reg1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param otbp_bar_lower </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Output Task Backpressure Base Address LOWER BITS[31:0] </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_otbp_bar_reg1_t
 *
 * Implemented by: 
 *      otbp_bar_lower
 */
 
typedef struct
{
     unsigned  int            otbp_bar_lower;
} ncp_nca_otbp_bar_reg1_t;

/*! @struct ncp_nca_software_pgit_load_poke_reg_t
 *  @brief PGIT Software Load Poke Register
 *  @details CPU can write to this register to force the shortening of the delay (using delay_grp_load_timer register) for the current cycle of the timer for the PGIT to load CPU Indexes.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_software_pgit_load_poke_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 26 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param software_load_poke_grp </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Poke the PGIT CPU index load timers. Each bit corresponds
 *        to a PCQ group.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_software_pgit_load_poke_reg_t
 *
 * Implemented by: 
 *      pgit_software_load_poke_reg
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 26;
     unsigned      software_load_poke_grp                    :  6;
#else    /* Little Endian */
     unsigned      software_load_poke_grp                    :  6;
     unsigned      reserved0                                 : 26;
#endif
} ncp_nca_software_pgit_load_poke_reg_t;

/*! @struct ncp_nca_hw_load_poke_flags_reg_t
 *  @brief HW POINTER POKE FLAGS
 *  @details Flags for HW Pointer Load Poke events.  NOT SUPPORTED FOR MISSION-MODE OPERATION.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_hw_load_poke_flags_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 26 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hardware_grp5_load_flag </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> hardware_grp5_load_flag </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hardware_grp4_load_flag </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> hardware_grp4_load_flag </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hardware_grp3_load_flag </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> hardware_grp3_load_flag </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hardware_grp2_load_flag </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> hardware_grp2_load_flag </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hardware_grp1_load_flag </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> hardware_grp1_load_flag </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hardware_grp0_load_flag </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> hardware_grp0_load_flag </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_hw_load_poke_flags_reg_t
 *
 * Implemented by: 
 *      hw_load_poke_flags
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 26;
     unsigned      hardware_grp5_load_flag                   :  1;
     unsigned      hardware_grp4_load_flag                   :  1;
     unsigned      hardware_grp3_load_flag                   :  1;
     unsigned      hardware_grp2_load_flag                   :  1;
     unsigned      hardware_grp1_load_flag                   :  1;
     unsigned      hardware_grp0_load_flag                   :  1;
#else    /* Little Endian */
     unsigned      hardware_grp0_load_flag                   :  1;
     unsigned      hardware_grp1_load_flag                   :  1;
     unsigned      hardware_grp2_load_flag                   :  1;
     unsigned      hardware_grp3_load_flag                   :  1;
     unsigned      hardware_grp4_load_flag                   :  1;
     unsigned      hardware_grp5_load_flag                   :  1;
     unsigned      reserved0                                 : 26;
#endif
} ncp_nca_hw_load_poke_flags_reg_t;

/*! @struct ncp_nca_overall_int_stat_reg_t
 *  @brief Overall Interrupt Status Register
 *  @details This register provides status to indicate when corresponding bits in the grp_interrupt_status_table and the grp_interrupt_enable_table are both set.  Any such pairing causes one of the nca_mpic interrupt pins to be asserted if enabled.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_overall_int_stat_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param non_grp_int_grp_int_reg_1_or_2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> At least one non-group interrupt status and enable
 *        bit pair = 'b11 in grp_interrupt_status/enable_table...status/en_r|1..2|
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp5_int_grp_int_reg1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> At least one group 5 interrupt status and enable bit
 *        pair = 'b11 in grp_interrupt_status/enable_table...status/en_r1
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp4_int_grp_int_reg1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> At least one group 4 interrupt status and enable bit
 *        pair = 'b11 in grp_interrupt_status/enable_table...status/en_r1
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp3_int_grp_int_reg1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> At least one group 3 interrupt status and enable bit
 *        pair = 'b11 in grp_interrupt_status/enable_table...status/en_r1
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp2_int_grp_int_reg1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> At least one group 2 interrupt status and enable bit
 *        pair = 'b11 in grp_interrupt_status/enable_table...status/en_r1
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp1_int_grp_int_reg1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> At least one group 1 interrupt status and enable bit
 *        pair = 'b11 in grp_interrupt_status/enable_table...status/en_r1
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp0_int_grp_int_reg1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> At least one group 0 interrupt status and enable bit
 *        pair = 'b11 in grp_interrupt_status/enable_table...status/en_r1
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp_int_reg0_int </td>
 *     <td width="20%" align="center"> 25 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> These bits correspond to the interrupt status and
 *        enable bit pairs in grp_interrupt_status/enable_table...status/en_r0.
 *        Each bit is set for every corresponding status and
 *        enable pair that = 'b11. These interrupts are service
 *        interrupts that indicate input task arrival, output
 *        task delivery, etc.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_overall_int_stat_reg_t
 *
 * Implemented by: 
 *      overall_int_stat
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      non_grp_int_grp_int_reg_1_or_2            :  1;
     unsigned      grp5_int_grp_int_reg1                     :  1;
     unsigned      grp4_int_grp_int_reg1                     :  1;
     unsigned      grp3_int_grp_int_reg1                     :  1;
     unsigned      grp2_int_grp_int_reg1                     :  1;
     unsigned      grp1_int_grp_int_reg1                     :  1;
     unsigned      grp0_int_grp_int_reg1                     :  1;
     unsigned      grp_int_reg0_int                          : 25;
#else    /* Little Endian */
     unsigned      grp_int_reg0_int                          : 25;
     unsigned      grp0_int_grp_int_reg1                     :  1;
     unsigned      grp1_int_grp_int_reg1                     :  1;
     unsigned      grp2_int_grp_int_reg1                     :  1;
     unsigned      grp3_int_grp_int_reg1                     :  1;
     unsigned      grp4_int_grp_int_reg1                     :  1;
     unsigned      grp5_int_grp_int_reg1                     :  1;
     unsigned      non_grp_int_grp_int_reg_1_or_2            :  1;
#endif
} ncp_nca_overall_int_stat_reg_t;

/*! @struct ncp_nca_mpic_ctrl_reg_t
 *  @brief MPIC Interrupt Control Register
 *  @details Provides control for the state of the NCA's 6 interrupt outputs that connect to the MPIC (microprocessor interrupt controller).
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_mpic_ctrl_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sel </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Select. Maps the non group related interrupts to one
 *        of the 6 MPIC interrupt outputs. If this field is
 *        set to a value > 5, the interrupts are mapped to MPIC
 *        interrupt pin 0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param int_en </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Interrupt Enable. Each bit enables the corresponding
 *        MPIC interrupt output.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_mpic_ctrl_reg_t
 *
 * Implemented by: 
 *      mpic_ctrl
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 21;
     unsigned      sel                                       :  3;
     unsigned      reserved1                                 :  2;
     unsigned      int_en                                    :  6;
#else    /* Little Endian */
     unsigned      int_en                                    :  6;
     unsigned      reserved1                                 :  2;
     unsigned      sel                                       :  3;
     unsigned      reserved0                                 : 21;
#endif
} ncp_nca_mpic_ctrl_reg_t;

/*! @struct ncp_nca_status_reg0_t
 *  @brief Interrupt Status Register
 *  @details This register holds interrupt status.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_status_reg0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_inst_compl_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> configuration instruction complete interrupt Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> input tasks have arrived for group 5 Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> input tasks have arrived for group 4 Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> input tasks have arrived for group 3 Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> input tasks have arrived for group 2 Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> input tasks have arrived for group 1 Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> input tasks have arrived for group 0 Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 5
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 4
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 3
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 2
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 1
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 0
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 5
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 4
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 3
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 2
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 1
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 0
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 5
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 4
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 3
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 2
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 1
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 0
 *        Status
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_status_reg0_t
 *
 * Implemented by: 
 *      status_r0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      cfg_inst_compl_int                        :  1;
     unsigned      itask_arrival_int_grp5                    :  1;
     unsigned      itask_arrival_int_grp4                    :  1;
     unsigned      itask_arrival_int_grp3                    :  1;
     unsigned      itask_arrival_int_grp2                    :  1;
     unsigned      itask_arrival_int_grp1                    :  1;
     unsigned      itask_arrival_int_grp0                    :  1;
     unsigned      opcq_complete_int_grp5                    :  1;
     unsigned      opcq_complete_int_grp4                    :  1;
     unsigned      opcq_complete_int_grp3                    :  1;
     unsigned      opcq_complete_int_grp2                    :  1;
     unsigned      opcq_complete_int_grp1                    :  1;
     unsigned      opcq_complete_int_grp0                    :  1;
     unsigned      tpcq_complete_int_grp5                    :  1;
     unsigned      tpcq_complete_int_grp4                    :  1;
     unsigned      tpcq_complete_int_grp3                    :  1;
     unsigned      tpcq_complete_int_grp2                    :  1;
     unsigned      tpcq_complete_int_grp1                    :  1;
     unsigned      tpcq_complete_int_grp0                    :  1;
     unsigned      cpcq_complete_int_grp5                    :  1;
     unsigned      cpcq_complete_int_grp4                    :  1;
     unsigned      cpcq_complete_int_grp3                    :  1;
     unsigned      cpcq_complete_int_grp2                    :  1;
     unsigned      cpcq_complete_int_grp1                    :  1;
     unsigned      cpcq_complete_int_grp0                    :  1;
#else    /* Little Endian */
     unsigned      cpcq_complete_int_grp0                    :  1;
     unsigned      cpcq_complete_int_grp1                    :  1;
     unsigned      cpcq_complete_int_grp2                    :  1;
     unsigned      cpcq_complete_int_grp3                    :  1;
     unsigned      cpcq_complete_int_grp4                    :  1;
     unsigned      cpcq_complete_int_grp5                    :  1;
     unsigned      tpcq_complete_int_grp0                    :  1;
     unsigned      tpcq_complete_int_grp1                    :  1;
     unsigned      tpcq_complete_int_grp2                    :  1;
     unsigned      tpcq_complete_int_grp3                    :  1;
     unsigned      tpcq_complete_int_grp4                    :  1;
     unsigned      tpcq_complete_int_grp5                    :  1;
     unsigned      opcq_complete_int_grp0                    :  1;
     unsigned      opcq_complete_int_grp1                    :  1;
     unsigned      opcq_complete_int_grp2                    :  1;
     unsigned      opcq_complete_int_grp3                    :  1;
     unsigned      opcq_complete_int_grp4                    :  1;
     unsigned      opcq_complete_int_grp5                    :  1;
     unsigned      itask_arrival_int_grp0                    :  1;
     unsigned      itask_arrival_int_grp1                    :  1;
     unsigned      itask_arrival_int_grp2                    :  1;
     unsigned      itask_arrival_int_grp3                    :  1;
     unsigned      itask_arrival_int_grp4                    :  1;
     unsigned      itask_arrival_int_grp5                    :  1;
     unsigned      cfg_inst_compl_int                        :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_nca_status_reg0_t;

/*! @struct ncp_nca_en_reg0_t
 *  @brief Interrupt Enable Register
 *  @details This register enables interrupts
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_en_reg0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_inst_compl_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> configuration instruction complete interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> input tasks have arrived for group 5 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> input tasks have arrived for group 4 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> input tasks have arrived for group 3 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> input tasks have arrived for group 2 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> input tasks have arrived for group 1 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> input tasks have arrived for group 0 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 5
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 4
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 3
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 2
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 1
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 0
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 5
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 4
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 3
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 2
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 1
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 0
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 5
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 4
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 3
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 2
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 1
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 0
 *        Enable
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_en_reg0_t
 *
 * Implemented by: 
 *      en_r0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      cfg_inst_compl_int                        :  1;
     unsigned      itask_arrival_int_grp5                    :  1;
     unsigned      itask_arrival_int_grp4                    :  1;
     unsigned      itask_arrival_int_grp3                    :  1;
     unsigned      itask_arrival_int_grp2                    :  1;
     unsigned      itask_arrival_int_grp1                    :  1;
     unsigned      itask_arrival_int_grp0                    :  1;
     unsigned      opcq_complete_int_grp5                    :  1;
     unsigned      opcq_complete_int_grp4                    :  1;
     unsigned      opcq_complete_int_grp3                    :  1;
     unsigned      opcq_complete_int_grp2                    :  1;
     unsigned      opcq_complete_int_grp1                    :  1;
     unsigned      opcq_complete_int_grp0                    :  1;
     unsigned      tpcq_complete_int_grp5                    :  1;
     unsigned      tpcq_complete_int_grp4                    :  1;
     unsigned      tpcq_complete_int_grp3                    :  1;
     unsigned      tpcq_complete_int_grp2                    :  1;
     unsigned      tpcq_complete_int_grp1                    :  1;
     unsigned      tpcq_complete_int_grp0                    :  1;
     unsigned      cpcq_complete_int_grp5                    :  1;
     unsigned      cpcq_complete_int_grp4                    :  1;
     unsigned      cpcq_complete_int_grp3                    :  1;
     unsigned      cpcq_complete_int_grp2                    :  1;
     unsigned      cpcq_complete_int_grp1                    :  1;
     unsigned      cpcq_complete_int_grp0                    :  1;
#else    /* Little Endian */
     unsigned      cpcq_complete_int_grp0                    :  1;
     unsigned      cpcq_complete_int_grp1                    :  1;
     unsigned      cpcq_complete_int_grp2                    :  1;
     unsigned      cpcq_complete_int_grp3                    :  1;
     unsigned      cpcq_complete_int_grp4                    :  1;
     unsigned      cpcq_complete_int_grp5                    :  1;
     unsigned      tpcq_complete_int_grp0                    :  1;
     unsigned      tpcq_complete_int_grp1                    :  1;
     unsigned      tpcq_complete_int_grp2                    :  1;
     unsigned      tpcq_complete_int_grp3                    :  1;
     unsigned      tpcq_complete_int_grp4                    :  1;
     unsigned      tpcq_complete_int_grp5                    :  1;
     unsigned      opcq_complete_int_grp0                    :  1;
     unsigned      opcq_complete_int_grp1                    :  1;
     unsigned      opcq_complete_int_grp2                    :  1;
     unsigned      opcq_complete_int_grp3                    :  1;
     unsigned      opcq_complete_int_grp4                    :  1;
     unsigned      opcq_complete_int_grp5                    :  1;
     unsigned      itask_arrival_int_grp0                    :  1;
     unsigned      itask_arrival_int_grp1                    :  1;
     unsigned      itask_arrival_int_grp2                    :  1;
     unsigned      itask_arrival_int_grp3                    :  1;
     unsigned      itask_arrival_int_grp4                    :  1;
     unsigned      itask_arrival_int_grp5                    :  1;
     unsigned      cfg_inst_compl_int                        :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_nca_en_reg0_t;

/*! @struct ncp_nca_force_reg0_t
 *  @brief Interrupt Force Register
 *  @details This address is an alias for the Interrupt Status register that allows normal CFG writes (as opposed to the Clear-On-Write-One behavior if the Interrupt Status register address is used). This allows CFG to set interrupt bits for testing purposes. Reading this address returns the current value of the Interrupt Status Register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_force_reg0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_inst_compl_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> configuration instruction complete interrupt Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> input tasks have arrived for group 5 Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> input tasks have arrived for group 4 Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> input tasks have arrived for group 3 Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> input tasks have arrived for group 2 Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> input tasks have arrived for group 1 Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> input tasks have arrived for group 0 Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 5
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 4
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 3
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 2
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 1
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 0
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 5
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 4
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 3
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 2
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 1
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 0
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 5
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 4
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 3
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 2
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 1
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 0
 *        Force
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_force_reg0_t
 *
 * Implemented by: 
 *      frc_r0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      cfg_inst_compl_int                        :  1;
     unsigned      itask_arrival_int_grp5                    :  1;
     unsigned      itask_arrival_int_grp4                    :  1;
     unsigned      itask_arrival_int_grp3                    :  1;
     unsigned      itask_arrival_int_grp2                    :  1;
     unsigned      itask_arrival_int_grp1                    :  1;
     unsigned      itask_arrival_int_grp0                    :  1;
     unsigned      opcq_complete_int_grp5                    :  1;
     unsigned      opcq_complete_int_grp4                    :  1;
     unsigned      opcq_complete_int_grp3                    :  1;
     unsigned      opcq_complete_int_grp2                    :  1;
     unsigned      opcq_complete_int_grp1                    :  1;
     unsigned      opcq_complete_int_grp0                    :  1;
     unsigned      tpcq_complete_int_grp5                    :  1;
     unsigned      tpcq_complete_int_grp4                    :  1;
     unsigned      tpcq_complete_int_grp3                    :  1;
     unsigned      tpcq_complete_int_grp2                    :  1;
     unsigned      tpcq_complete_int_grp1                    :  1;
     unsigned      tpcq_complete_int_grp0                    :  1;
     unsigned      cpcq_complete_int_grp5                    :  1;
     unsigned      cpcq_complete_int_grp4                    :  1;
     unsigned      cpcq_complete_int_grp3                    :  1;
     unsigned      cpcq_complete_int_grp2                    :  1;
     unsigned      cpcq_complete_int_grp1                    :  1;
     unsigned      cpcq_complete_int_grp0                    :  1;
#else    /* Little Endian */
     unsigned      cpcq_complete_int_grp0                    :  1;
     unsigned      cpcq_complete_int_grp1                    :  1;
     unsigned      cpcq_complete_int_grp2                    :  1;
     unsigned      cpcq_complete_int_grp3                    :  1;
     unsigned      cpcq_complete_int_grp4                    :  1;
     unsigned      cpcq_complete_int_grp5                    :  1;
     unsigned      tpcq_complete_int_grp0                    :  1;
     unsigned      tpcq_complete_int_grp1                    :  1;
     unsigned      tpcq_complete_int_grp2                    :  1;
     unsigned      tpcq_complete_int_grp3                    :  1;
     unsigned      tpcq_complete_int_grp4                    :  1;
     unsigned      tpcq_complete_int_grp5                    :  1;
     unsigned      opcq_complete_int_grp0                    :  1;
     unsigned      opcq_complete_int_grp1                    :  1;
     unsigned      opcq_complete_int_grp2                    :  1;
     unsigned      opcq_complete_int_grp3                    :  1;
     unsigned      opcq_complete_int_grp4                    :  1;
     unsigned      opcq_complete_int_grp5                    :  1;
     unsigned      itask_arrival_int_grp0                    :  1;
     unsigned      itask_arrival_int_grp1                    :  1;
     unsigned      itask_arrival_int_grp2                    :  1;
     unsigned      itask_arrival_int_grp3                    :  1;
     unsigned      itask_arrival_int_grp4                    :  1;
     unsigned      itask_arrival_int_grp5                    :  1;
     unsigned      cfg_inst_compl_int                        :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_nca_force_reg0_t;

/*! @struct ncp_nca_status_reg1_t
 *  @brief Interrupt Status Register
 *  @details This register holds interrupt status.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_status_reg1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_fifo_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> configuration manager fifo error interrupt Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_reng_axi_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> configuration manager read engine axi error interrupt
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_data_overflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> output task data overflow interrupt Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_data_undeflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> output task data undeflow interrupt Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> cnal access error interrupt group5 Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> cnal access error interrupt group4 Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> cnal access error interrupt group3 Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> cnal access error interrupt group2 Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> cnal access error interrupt group1 Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> cnal access error interrupt group0 Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> configuration ring error interrupt group5 Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> configuration ring error interrupt group4 Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> configuration ring error interrupt group3 Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> configuration ring error interrupt group2 Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> configuration ring error interrupt group1 Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> configuration ring error interrupt group0 Status </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_status_reg1_t
 *
 * Implemented by: 
 *      status_r1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      cmn_fifo_err_int                          :  1;
     unsigned      cmn_reng_axi_err_int                      :  1;
     unsigned      otask_data_overflow_int                   :  1;
     unsigned      otask_data_undeflow_int                   :  1;
     unsigned      eng_cnal_if_int_grp5                      :  1;
     unsigned      eng_cnal_if_int_grp4                      :  1;
     unsigned      eng_cnal_if_int_grp3                      :  1;
     unsigned      eng_cnal_if_int_grp2                      :  1;
     unsigned      eng_cnal_if_int_grp1                      :  1;
     unsigned      eng_cnal_if_int_grp0                      :  1;
     unsigned      cfg_ring_err_int_grp5                     :  1;
     unsigned      cfg_ring_err_int_grp4                     :  1;
     unsigned      cfg_ring_err_int_grp3                     :  1;
     unsigned      cfg_ring_err_int_grp2                     :  1;
     unsigned      cfg_ring_err_int_grp1                     :  1;
     unsigned      cfg_ring_err_int_grp0                     :  1;
#else    /* Little Endian */
     unsigned      cfg_ring_err_int_grp0                     :  1;
     unsigned      cfg_ring_err_int_grp1                     :  1;
     unsigned      cfg_ring_err_int_grp2                     :  1;
     unsigned      cfg_ring_err_int_grp3                     :  1;
     unsigned      cfg_ring_err_int_grp4                     :  1;
     unsigned      cfg_ring_err_int_grp5                     :  1;
     unsigned      eng_cnal_if_int_grp0                      :  1;
     unsigned      eng_cnal_if_int_grp1                      :  1;
     unsigned      eng_cnal_if_int_grp2                      :  1;
     unsigned      eng_cnal_if_int_grp3                      :  1;
     unsigned      eng_cnal_if_int_grp4                      :  1;
     unsigned      eng_cnal_if_int_grp5                      :  1;
     unsigned      otask_data_undeflow_int                   :  1;
     unsigned      otask_data_overflow_int                   :  1;
     unsigned      cmn_reng_axi_err_int                      :  1;
     unsigned      cmn_fifo_err_int                          :  1;
     unsigned      reserved0                                 : 16;
#endif
} ncp_nca_status_reg1_t;

/*! @struct ncp_nca_en_reg1_t
 *  @brief Interrupt Enable Register
 *  @details This register enables interrupts
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_en_reg1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_fifo_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> configuration manager fifo error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_reng_axi_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> configuration manager read engine axi error interrupt
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_data_overflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> output task data overflow interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_data_undeflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> output task data undeflow interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> cnal access error interrupt group5 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> cnal access error interrupt group4 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> cnal access error interrupt group3 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> cnal access error interrupt group2 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> cnal access error interrupt group1 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> cnal access error interrupt group0 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> configuration ring error interrupt group5 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> configuration ring error interrupt group4 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> configuration ring error interrupt group3 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> configuration ring error interrupt group2 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> configuration ring error interrupt group1 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> configuration ring error interrupt group0 Enable </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_en_reg1_t
 *
 * Implemented by: 
 *      en_r1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      cmn_fifo_err_int                          :  1;
     unsigned      cmn_reng_axi_err_int                      :  1;
     unsigned      otask_data_overflow_int                   :  1;
     unsigned      otask_data_undeflow_int                   :  1;
     unsigned      eng_cnal_if_int_grp5                      :  1;
     unsigned      eng_cnal_if_int_grp4                      :  1;
     unsigned      eng_cnal_if_int_grp3                      :  1;
     unsigned      eng_cnal_if_int_grp2                      :  1;
     unsigned      eng_cnal_if_int_grp1                      :  1;
     unsigned      eng_cnal_if_int_grp0                      :  1;
     unsigned      cfg_ring_err_int_grp5                     :  1;
     unsigned      cfg_ring_err_int_grp4                     :  1;
     unsigned      cfg_ring_err_int_grp3                     :  1;
     unsigned      cfg_ring_err_int_grp2                     :  1;
     unsigned      cfg_ring_err_int_grp1                     :  1;
     unsigned      cfg_ring_err_int_grp0                     :  1;
#else    /* Little Endian */
     unsigned      cfg_ring_err_int_grp0                     :  1;
     unsigned      cfg_ring_err_int_grp1                     :  1;
     unsigned      cfg_ring_err_int_grp2                     :  1;
     unsigned      cfg_ring_err_int_grp3                     :  1;
     unsigned      cfg_ring_err_int_grp4                     :  1;
     unsigned      cfg_ring_err_int_grp5                     :  1;
     unsigned      eng_cnal_if_int_grp0                      :  1;
     unsigned      eng_cnal_if_int_grp1                      :  1;
     unsigned      eng_cnal_if_int_grp2                      :  1;
     unsigned      eng_cnal_if_int_grp3                      :  1;
     unsigned      eng_cnal_if_int_grp4                      :  1;
     unsigned      eng_cnal_if_int_grp5                      :  1;
     unsigned      otask_data_undeflow_int                   :  1;
     unsigned      otask_data_overflow_int                   :  1;
     unsigned      cmn_reng_axi_err_int                      :  1;
     unsigned      cmn_fifo_err_int                          :  1;
     unsigned      reserved0                                 : 16;
#endif
} ncp_nca_en_reg1_t;

/*! @struct ncp_nca_force_reg1_t
 *  @brief Interrupt Force Register
 *  @details This address is an alias for the Interrupt Status register that allows normal CFG writes (as opposed to the Clear-On-Write-One behavior if the Interrupt Status register address is used). This allows CFG to set interrupt bits for testing purposes. Reading this address returns the current value of the Interrupt Status Register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_force_reg1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_fifo_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> configuration manager fifo error interrupt Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_reng_axi_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> configuration manager read engine axi error interrupt
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_data_overflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> output task data overflow interrupt Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_data_undeflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> output task data undeflow interrupt Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> cnal access error interrupt group5 Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> cnal access error interrupt group4 Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> cnal access error interrupt group3 Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> cnal access error interrupt group2 Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> cnal access error interrupt group1 Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> cnal access error interrupt group0 Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> configuration ring error interrupt group5 Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> configuration ring error interrupt group4 Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> configuration ring error interrupt group3 Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> configuration ring error interrupt group2 Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> configuration ring error interrupt group1 Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> configuration ring error interrupt group0 Force </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_force_reg1_t
 *
 * Implemented by: 
 *      frc_r1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      cmn_fifo_err_int                          :  1;
     unsigned      cmn_reng_axi_err_int                      :  1;
     unsigned      otask_data_overflow_int                   :  1;
     unsigned      otask_data_undeflow_int                   :  1;
     unsigned      eng_cnal_if_int_grp5                      :  1;
     unsigned      eng_cnal_if_int_grp4                      :  1;
     unsigned      eng_cnal_if_int_grp3                      :  1;
     unsigned      eng_cnal_if_int_grp2                      :  1;
     unsigned      eng_cnal_if_int_grp1                      :  1;
     unsigned      eng_cnal_if_int_grp0                      :  1;
     unsigned      cfg_ring_err_int_grp5                     :  1;
     unsigned      cfg_ring_err_int_grp4                     :  1;
     unsigned      cfg_ring_err_int_grp3                     :  1;
     unsigned      cfg_ring_err_int_grp2                     :  1;
     unsigned      cfg_ring_err_int_grp1                     :  1;
     unsigned      cfg_ring_err_int_grp0                     :  1;
#else    /* Little Endian */
     unsigned      cfg_ring_err_int_grp0                     :  1;
     unsigned      cfg_ring_err_int_grp1                     :  1;
     unsigned      cfg_ring_err_int_grp2                     :  1;
     unsigned      cfg_ring_err_int_grp3                     :  1;
     unsigned      cfg_ring_err_int_grp4                     :  1;
     unsigned      cfg_ring_err_int_grp5                     :  1;
     unsigned      eng_cnal_if_int_grp0                      :  1;
     unsigned      eng_cnal_if_int_grp1                      :  1;
     unsigned      eng_cnal_if_int_grp2                      :  1;
     unsigned      eng_cnal_if_int_grp3                      :  1;
     unsigned      eng_cnal_if_int_grp4                      :  1;
     unsigned      eng_cnal_if_int_grp5                      :  1;
     unsigned      otask_data_undeflow_int                   :  1;
     unsigned      otask_data_overflow_int                   :  1;
     unsigned      cmn_reng_axi_err_int                      :  1;
     unsigned      cmn_fifo_err_int                          :  1;
     unsigned      reserved0                                 : 16;
#endif
} ncp_nca_force_reg1_t;

/*! @struct ncp_nca_status_reg2_t
 *  @brief Interrupt Status Register
 *  @details This register holds interrupt status.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_status_reg2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> CMN fifo overflow/underflow interrupt Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> CMN fifo parity error interrupt Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cow_interrupt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> COW interrupt Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param smon_interrupt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> statistics counters interrupt Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> task flow completion fifo parity error interrupt Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> receive buffer pool fifo parity error interrupt Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> output task accumulator fifo parity error interrupt
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ita_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> input task accumulator fifo parity error interrupt
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> PGIT fifo parity error interrupt Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo_ecc_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> receive buffer pool ECC interrupt Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> task flow completion fifo overflow/underflow interrupt
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> receive buffer pool fifo overflow/underflow interrupt
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> output task accumulator fifo overflow/underflow interrupt
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ita_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> input task accumulator fifo overflow/underflow interrupt
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> PGIT fifo overflow/underflow interrupt Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_drop_no_rbuf_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> itask drop no receive buffer available interrupt Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_drop_ipcq_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> itask drop iPCQ error interrupt Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_data_axi_write_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> itask data axi write error interrupt Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ipcq_entry_axi_write_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> iPCQ entry axi write error interrupt Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_upload_nca_axi_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> PGIT upload nca axi write error interrupt Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_load_nca_axi_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> PGIT load nca axi read error interrupt Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_load_cpu_axi_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> PGIT load cpu axi read error interrupt Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_drop_entry_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> receive buffer pool drop interrupt Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_entry_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> tpcq axi read error Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rpcq_entry_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> rpcq axi read error Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_data_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> otask axi read error Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_entry_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> opcq axi read error Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> eng_cnal_if interrupt Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> config ring error interrupt Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otsd_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> otsd axi read error interrupt Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_axi_write_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> configuration master node axi write error interrupt
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> cPCQ axi read error interrupt Status </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_status_reg2_t
 *
 * Implemented by: 
 *      status_r2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      cmn_fifo_overflow_underflow_int           :  1;
     unsigned      cmn_fifo_par_err_int                      :  1;
     unsigned      cow_interrupt                             :  1;
     unsigned      smon_interrupt                            :  1;
     unsigned      tfc_fifo_par_err_int                      :  1;
     unsigned      rbp_fifo_par_err_int                      :  1;
     unsigned      ota_fifo_par_err_int                      :  1;
     unsigned      ita_fifo_par_err_int                      :  1;
     unsigned      pgit_fifo_par_err_int                     :  1;
     unsigned      rbp_fifo_ecc_int                          :  1;
     unsigned      tfc_fifo_overflow_underflow_int           :  1;
     unsigned      rbp_fifo_overflow_underflow_int           :  1;
     unsigned      ota_fifo_overflow_underflow_int           :  1;
     unsigned      ita_fifo_overflow_underflow_int           :  1;
     unsigned      pgit_fifo_overflow_underflow_int          :  1;
     unsigned      itask_drop_no_rbuf_er_int                 :  1;
     unsigned      itask_drop_ipcq_er_int                    :  1;
     unsigned      itask_data_axi_write_er_int               :  1;
     unsigned      ipcq_entry_axi_write_er_int               :  1;
     unsigned      pgit_upload_nca_axi_er_int                :  1;
     unsigned      pgit_load_nca_axi_er_int                  :  1;
     unsigned      pgit_load_cpu_axi_er_int                  :  1;
     unsigned      rbp_drop_entry_int                        :  1;
     unsigned      tpcq_entry_axi_read_int                   :  1;
     unsigned      rpcq_entry_axi_read_int                   :  1;
     unsigned      otask_data_axi_read_int                   :  1;
     unsigned      opcq_entry_axi_read_int                   :  1;
     unsigned      eng_cnal_if_int                           :  1;
     unsigned      cfg_ring_err_int                          :  1;
     unsigned      otsd_axi_read_int                         :  1;
     unsigned      cmn_axi_write_int                         :  1;
     unsigned      cpcq_axi_read_int                         :  1;
#else    /* Little Endian */
     unsigned      cpcq_axi_read_int                         :  1;
     unsigned      cmn_axi_write_int                         :  1;
     unsigned      otsd_axi_read_int                         :  1;
     unsigned      cfg_ring_err_int                          :  1;
     unsigned      eng_cnal_if_int                           :  1;
     unsigned      opcq_entry_axi_read_int                   :  1;
     unsigned      otask_data_axi_read_int                   :  1;
     unsigned      rpcq_entry_axi_read_int                   :  1;
     unsigned      tpcq_entry_axi_read_int                   :  1;
     unsigned      rbp_drop_entry_int                        :  1;
     unsigned      pgit_load_cpu_axi_er_int                  :  1;
     unsigned      pgit_load_nca_axi_er_int                  :  1;
     unsigned      pgit_upload_nca_axi_er_int                :  1;
     unsigned      ipcq_entry_axi_write_er_int               :  1;
     unsigned      itask_data_axi_write_er_int               :  1;
     unsigned      itask_drop_ipcq_er_int                    :  1;
     unsigned      itask_drop_no_rbuf_er_int                 :  1;
     unsigned      pgit_fifo_overflow_underflow_int          :  1;
     unsigned      ita_fifo_overflow_underflow_int           :  1;
     unsigned      ota_fifo_overflow_underflow_int           :  1;
     unsigned      rbp_fifo_overflow_underflow_int           :  1;
     unsigned      tfc_fifo_overflow_underflow_int           :  1;
     unsigned      rbp_fifo_ecc_int                          :  1;
     unsigned      pgit_fifo_par_err_int                     :  1;
     unsigned      ita_fifo_par_err_int                      :  1;
     unsigned      ota_fifo_par_err_int                      :  1;
     unsigned      rbp_fifo_par_err_int                      :  1;
     unsigned      tfc_fifo_par_err_int                      :  1;
     unsigned      smon_interrupt                            :  1;
     unsigned      cow_interrupt                             :  1;
     unsigned      cmn_fifo_par_err_int                      :  1;
     unsigned      cmn_fifo_overflow_underflow_int           :  1;
#endif
} ncp_nca_status_reg2_t;

/*! @struct ncp_nca_en_reg2_t
 *  @brief Interrupt Enable Register
 *  @details This register enables interrupts
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_en_reg2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> CMN fifo overflow/underflow interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> CMN fifo parity error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cow_interrupt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> COW interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param smon_interrupt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> statistics counters interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> task flow completion fifo parity error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> receive buffer pool fifo parity error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> output task accumulator fifo parity error interrupt
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ita_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> input task accumulator fifo parity error interrupt
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> PGIT fifo parity error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo_ecc_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> receive buffer pool ECC interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> task flow completion fifo overflow/underflow interrupt
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> receive buffer pool fifo overflow/underflow interrupt
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> output task accumulator fifo overflow/underflow interrupt
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ita_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> input task accumulator fifo overflow/underflow interrupt
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> PGIT fifo overflow/underflow interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_drop_no_rbuf_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> itask drop no receive buffer available interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_drop_ipcq_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> itask drop iPCQ error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_data_axi_write_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> itask data axi write error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ipcq_entry_axi_write_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> iPCQ entry axi write error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_upload_nca_axi_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> PGIT upload nca axi write error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_load_nca_axi_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> PGIT load nca axi read error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_load_cpu_axi_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> PGIT load cpu axi read error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_drop_entry_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> receive buffer pool drop interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_entry_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> tpcq axi read error Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rpcq_entry_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> rpcq axi read error Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_data_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> otask axi read error Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_entry_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> opcq axi read error Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> eng_cnal_if interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> config ring error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otsd_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> otsd axi read error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_axi_write_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> configuration master node axi write error interrupt
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> cPCQ axi read error interrupt Enable </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_en_reg2_t
 *
 * Implemented by: 
 *      en_r2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      cmn_fifo_overflow_underflow_int           :  1;
     unsigned      cmn_fifo_par_err_int                      :  1;
     unsigned      cow_interrupt                             :  1;
     unsigned      smon_interrupt                            :  1;
     unsigned      tfc_fifo_par_err_int                      :  1;
     unsigned      rbp_fifo_par_err_int                      :  1;
     unsigned      ota_fifo_par_err_int                      :  1;
     unsigned      ita_fifo_par_err_int                      :  1;
     unsigned      pgit_fifo_par_err_int                     :  1;
     unsigned      rbp_fifo_ecc_int                          :  1;
     unsigned      tfc_fifo_overflow_underflow_int           :  1;
     unsigned      rbp_fifo_overflow_underflow_int           :  1;
     unsigned      ota_fifo_overflow_underflow_int           :  1;
     unsigned      ita_fifo_overflow_underflow_int           :  1;
     unsigned      pgit_fifo_overflow_underflow_int          :  1;
     unsigned      itask_drop_no_rbuf_er_int                 :  1;
     unsigned      itask_drop_ipcq_er_int                    :  1;
     unsigned      itask_data_axi_write_er_int               :  1;
     unsigned      ipcq_entry_axi_write_er_int               :  1;
     unsigned      pgit_upload_nca_axi_er_int                :  1;
     unsigned      pgit_load_nca_axi_er_int                  :  1;
     unsigned      pgit_load_cpu_axi_er_int                  :  1;
     unsigned      rbp_drop_entry_int                        :  1;
     unsigned      tpcq_entry_axi_read_int                   :  1;
     unsigned      rpcq_entry_axi_read_int                   :  1;
     unsigned      otask_data_axi_read_int                   :  1;
     unsigned      opcq_entry_axi_read_int                   :  1;
     unsigned      eng_cnal_if_int                           :  1;
     unsigned      cfg_ring_err_int                          :  1;
     unsigned      otsd_axi_read_int                         :  1;
     unsigned      cmn_axi_write_int                         :  1;
     unsigned      cpcq_axi_read_int                         :  1;
#else    /* Little Endian */
     unsigned      cpcq_axi_read_int                         :  1;
     unsigned      cmn_axi_write_int                         :  1;
     unsigned      otsd_axi_read_int                         :  1;
     unsigned      cfg_ring_err_int                          :  1;
     unsigned      eng_cnal_if_int                           :  1;
     unsigned      opcq_entry_axi_read_int                   :  1;
     unsigned      otask_data_axi_read_int                   :  1;
     unsigned      rpcq_entry_axi_read_int                   :  1;
     unsigned      tpcq_entry_axi_read_int                   :  1;
     unsigned      rbp_drop_entry_int                        :  1;
     unsigned      pgit_load_cpu_axi_er_int                  :  1;
     unsigned      pgit_load_nca_axi_er_int                  :  1;
     unsigned      pgit_upload_nca_axi_er_int                :  1;
     unsigned      ipcq_entry_axi_write_er_int               :  1;
     unsigned      itask_data_axi_write_er_int               :  1;
     unsigned      itask_drop_ipcq_er_int                    :  1;
     unsigned      itask_drop_no_rbuf_er_int                 :  1;
     unsigned      pgit_fifo_overflow_underflow_int          :  1;
     unsigned      ita_fifo_overflow_underflow_int           :  1;
     unsigned      ota_fifo_overflow_underflow_int           :  1;
     unsigned      rbp_fifo_overflow_underflow_int           :  1;
     unsigned      tfc_fifo_overflow_underflow_int           :  1;
     unsigned      rbp_fifo_ecc_int                          :  1;
     unsigned      pgit_fifo_par_err_int                     :  1;
     unsigned      ita_fifo_par_err_int                      :  1;
     unsigned      ota_fifo_par_err_int                      :  1;
     unsigned      rbp_fifo_par_err_int                      :  1;
     unsigned      tfc_fifo_par_err_int                      :  1;
     unsigned      smon_interrupt                            :  1;
     unsigned      cow_interrupt                             :  1;
     unsigned      cmn_fifo_par_err_int                      :  1;
     unsigned      cmn_fifo_overflow_underflow_int           :  1;
#endif
} ncp_nca_en_reg2_t;

/*! @struct ncp_nca_force_reg2_t
 *  @brief Interrupt Force Register
 *  @details This address is an alias for the Interrupt Status register that allows normal CFG writes (as opposed to the Clear-On-Write-One behavior if the Interrupt Status register address is used). This allows CFG to set interrupt bits for testing purposes. Reading this address returns the current value of the Interrupt Status Register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_force_reg2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> CMN fifo overflow/underflow interrupt Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> CMN fifo parity error interrupt Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cow_interrupt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> COW interrupt Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param smon_interrupt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> statistics counters interrupt Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> task flow completion fifo parity error interrupt Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> receive buffer pool fifo parity error interrupt Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> output task accumulator fifo parity error interrupt
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ita_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> input task accumulator fifo parity error interrupt
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> PGIT fifo parity error interrupt Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo_ecc_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> receive buffer pool ECC interrupt Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> task flow completion fifo overflow/underflow interrupt
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> receive buffer pool fifo overflow/underflow interrupt
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> output task accumulator fifo overflow/underflow interrupt
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ita_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> input task accumulator fifo overflow/underflow interrupt
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> PGIT fifo overflow/underflow interrupt Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_drop_no_rbuf_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> itask drop no receive buffer available interrupt Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_drop_ipcq_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> itask drop iPCQ error interrupt Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_data_axi_write_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> itask data axi write error interrupt Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ipcq_entry_axi_write_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> iPCQ entry axi write error interrupt Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_upload_nca_axi_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> PGIT upload nca axi write error interrupt Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_load_nca_axi_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> PGIT load nca axi read error interrupt Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_load_cpu_axi_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> PGIT load cpu axi read error interrupt Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_drop_entry_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> receive buffer pool drop interrupt Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_entry_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> tpcq axi read error Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rpcq_entry_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> rpcq axi read error Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_data_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> otask axi read error Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_entry_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> opcq axi read error Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> eng_cnal_if interrupt Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> config ring error interrupt Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otsd_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> otsd axi read error interrupt Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_axi_write_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> configuration master node axi write error interrupt
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> cPCQ axi read error interrupt Force </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_force_reg2_t
 *
 * Implemented by: 
 *      frc_r2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      cmn_fifo_overflow_underflow_int           :  1;
     unsigned      cmn_fifo_par_err_int                      :  1;
     unsigned      cow_interrupt                             :  1;
     unsigned      smon_interrupt                            :  1;
     unsigned      tfc_fifo_par_err_int                      :  1;
     unsigned      rbp_fifo_par_err_int                      :  1;
     unsigned      ota_fifo_par_err_int                      :  1;
     unsigned      ita_fifo_par_err_int                      :  1;
     unsigned      pgit_fifo_par_err_int                     :  1;
     unsigned      rbp_fifo_ecc_int                          :  1;
     unsigned      tfc_fifo_overflow_underflow_int           :  1;
     unsigned      rbp_fifo_overflow_underflow_int           :  1;
     unsigned      ota_fifo_overflow_underflow_int           :  1;
     unsigned      ita_fifo_overflow_underflow_int           :  1;
     unsigned      pgit_fifo_overflow_underflow_int          :  1;
     unsigned      itask_drop_no_rbuf_er_int                 :  1;
     unsigned      itask_drop_ipcq_er_int                    :  1;
     unsigned      itask_data_axi_write_er_int               :  1;
     unsigned      ipcq_entry_axi_write_er_int               :  1;
     unsigned      pgit_upload_nca_axi_er_int                :  1;
     unsigned      pgit_load_nca_axi_er_int                  :  1;
     unsigned      pgit_load_cpu_axi_er_int                  :  1;
     unsigned      rbp_drop_entry_int                        :  1;
     unsigned      tpcq_entry_axi_read_int                   :  1;
     unsigned      rpcq_entry_axi_read_int                   :  1;
     unsigned      otask_data_axi_read_int                   :  1;
     unsigned      opcq_entry_axi_read_int                   :  1;
     unsigned      eng_cnal_if_int                           :  1;
     unsigned      cfg_ring_err_int                          :  1;
     unsigned      otsd_axi_read_int                         :  1;
     unsigned      cmn_axi_write_int                         :  1;
     unsigned      cpcq_axi_read_int                         :  1;
#else    /* Little Endian */
     unsigned      cpcq_axi_read_int                         :  1;
     unsigned      cmn_axi_write_int                         :  1;
     unsigned      otsd_axi_read_int                         :  1;
     unsigned      cfg_ring_err_int                          :  1;
     unsigned      eng_cnal_if_int                           :  1;
     unsigned      opcq_entry_axi_read_int                   :  1;
     unsigned      otask_data_axi_read_int                   :  1;
     unsigned      rpcq_entry_axi_read_int                   :  1;
     unsigned      tpcq_entry_axi_read_int                   :  1;
     unsigned      rbp_drop_entry_int                        :  1;
     unsigned      pgit_load_cpu_axi_er_int                  :  1;
     unsigned      pgit_load_nca_axi_er_int                  :  1;
     unsigned      pgit_upload_nca_axi_er_int                :  1;
     unsigned      ipcq_entry_axi_write_er_int               :  1;
     unsigned      itask_data_axi_write_er_int               :  1;
     unsigned      itask_drop_ipcq_er_int                    :  1;
     unsigned      itask_drop_no_rbuf_er_int                 :  1;
     unsigned      pgit_fifo_overflow_underflow_int          :  1;
     unsigned      ita_fifo_overflow_underflow_int           :  1;
     unsigned      ota_fifo_overflow_underflow_int           :  1;
     unsigned      rbp_fifo_overflow_underflow_int           :  1;
     unsigned      tfc_fifo_overflow_underflow_int           :  1;
     unsigned      rbp_fifo_ecc_int                          :  1;
     unsigned      pgit_fifo_par_err_int                     :  1;
     unsigned      ita_fifo_par_err_int                      :  1;
     unsigned      ota_fifo_par_err_int                      :  1;
     unsigned      rbp_fifo_par_err_int                      :  1;
     unsigned      tfc_fifo_par_err_int                      :  1;
     unsigned      smon_interrupt                            :  1;
     unsigned      cow_interrupt                             :  1;
     unsigned      cmn_fifo_par_err_int                      :  1;
     unsigned      cmn_fifo_overflow_underflow_int           :  1;
#endif
} ncp_nca_force_reg2_t;

/*! @struct ncp_nca_awfifo_full_empty_status_reg0_t
 *  @brief FIFO Full Empty Status Register0
 *  @details Value of the full and empty flags for the fifos indicated
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_awfifo_full_empty_status_reg0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_rfifo_full_empty_pair </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> cpcq_pgit_rfifo_full_empty_status_pair </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_wfifo_full_empty_pair </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> cpcq_pgit_wfifo_full_empty_status_pair </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_reng_rbf_fifo_full_empty_pair7 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> pgit_reng_rbf_fifo_full_empty_status_pair7 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_reng_rbf_fifo_full_empty_pair6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> pgit_reng_rbf_fifo_full_empty_status_pair6 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_reng_rbf_fifo_full_empty_pair5 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> pgit_reng_rbf_fifo_full_empty_status_pair5 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_reng_rbf_fifo_full_empty_pair4 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> pgit_reng_rbf_fifo_full_empty_status_pair4 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_reng_rbf_fifo_full_empty_pair3 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> pgit_reng_rbf_fifo_full_empty_status_pair3 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_reng_rbf_fifo_full_empty_pair2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> pgit_reng_rbf_fifo_full_empty_status_pair2 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_reng_rbf_fifo_full_empty_pair1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> pgit_reng_rbf_fifo_full_empty_status_pair1 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_reng_rbf_fifo_full_empty_pair0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> pgit_reng_rbf_fifo_full_empty_status_pair0 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_reng_req_fifo_full </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> pgit_reng_req_fifo_full_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_reng_req_fifo_empty </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> pgit_reng_req_fifo_empty_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_weng_wdb_fifo_full </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> pgit_weng_wdb_fifo_full_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_weng_wdb_fifo_empty </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> pgit_weng_wdb_fifo_empty_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_weng_req_fifo_full </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> pgit_weng_req_fifo_full_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_weng_req_fifo_empty </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> pgit_weng_req_fifo_empty_status </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_awfifo_full_empty_status_reg0_t
 *
 * Implemented by: 
 *      fifo_full_empty_status_reg0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      cpcq_rfifo_full_empty_pair                :  2;
     unsigned      cpcq_wfifo_full_empty_pair                :  2;
     unsigned      pgit_reng_rbf_fifo_full_empty_pair7       :  2;
     unsigned      pgit_reng_rbf_fifo_full_empty_pair6       :  2;
     unsigned      pgit_reng_rbf_fifo_full_empty_pair5       :  2;
     unsigned      pgit_reng_rbf_fifo_full_empty_pair4       :  2;
     unsigned      pgit_reng_rbf_fifo_full_empty_pair3       :  2;
     unsigned      pgit_reng_rbf_fifo_full_empty_pair2       :  2;
     unsigned      pgit_reng_rbf_fifo_full_empty_pair1       :  2;
     unsigned      pgit_reng_rbf_fifo_full_empty_pair0       :  2;
     unsigned      pgit_reng_req_fifo_full                   :  1;
     unsigned      pgit_reng_req_fifo_empty                  :  1;
     unsigned      pgit_weng_wdb_fifo_full                   :  1;
     unsigned      pgit_weng_wdb_fifo_empty                  :  1;
     unsigned      pgit_weng_req_fifo_full                   :  1;
     unsigned      pgit_weng_req_fifo_empty                  :  1;
#else    /* Little Endian */
     unsigned      pgit_weng_req_fifo_empty                  :  1;
     unsigned      pgit_weng_req_fifo_full                   :  1;
     unsigned      pgit_weng_wdb_fifo_empty                  :  1;
     unsigned      pgit_weng_wdb_fifo_full                   :  1;
     unsigned      pgit_reng_req_fifo_empty                  :  1;
     unsigned      pgit_reng_req_fifo_full                   :  1;
     unsigned      pgit_reng_rbf_fifo_full_empty_pair0       :  2;
     unsigned      pgit_reng_rbf_fifo_full_empty_pair1       :  2;
     unsigned      pgit_reng_rbf_fifo_full_empty_pair2       :  2;
     unsigned      pgit_reng_rbf_fifo_full_empty_pair3       :  2;
     unsigned      pgit_reng_rbf_fifo_full_empty_pair4       :  2;
     unsigned      pgit_reng_rbf_fifo_full_empty_pair5       :  2;
     unsigned      pgit_reng_rbf_fifo_full_empty_pair6       :  2;
     unsigned      pgit_reng_rbf_fifo_full_empty_pair7       :  2;
     unsigned      cpcq_wfifo_full_empty_pair                :  2;
     unsigned      cpcq_rfifo_full_empty_pair                :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_nca_awfifo_full_empty_status_reg0_t;

/*! @struct ncp_nca_awfifo_full_empty_status_reg1_t
 *  @brief FIFO Full Empty Status Register1
 *  @details Value of the full and empty flags for the fifos indicated
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_awfifo_full_empty_status_reg1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odb_fifo_full </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> odb_fifo_full_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odb_fifo_empty </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> odb_fifo_empty_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param idb_fifo_full </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> idb_fifo_full_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param idb_fifo_empty </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> idb_fifo_empty_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_weng_req_fifo_full </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> cmn_weng_req_fifo_full_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_weng_req_fifo_empty </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> cmn_weng_req_fifo_empty_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_weng_wdb_fifo_full </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> cmn_weng_wdb_fifo_full_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_weng_wdb_fifo_empty </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> cmn_weng_wdb_fifo_empty_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tcri_data_fifo_full </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> tcri_data_fifo_full_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tcri_data_fifo_empty </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> tcri_data_fifo_empty_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_header_fifo_full </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> itask_header_fifo_full_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_header_fifo_empty </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> itask_header_fifo_empty_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_qid_fifo_full </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> itask_qid_fifo_full_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_qid_fifo_empty </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> itask_qid_fifo_empty_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_delete_tid_fifo_full </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> itask_delete_tid_fifo_full_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_delete_tid_fifo_empty </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> itask_delete_tid_fifo_empty_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ipcq_pgitr_fifo_full </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> ipcq_pgitr_fifo_full_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ipcq_pgitr_fifo_empty </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> ipcq_pgitr_fifo_empty_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ipcq_pgitw_fifo_full </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> ipcq_pgitw_fifo_full_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ipcq_pgitw_fifo_empty </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> ipcq_pgitw_fifo_empty_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_weng_req_fifo_full </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> itask_weng_req_fifo_full_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_weng_req_fifo_empty </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> itask_weng_req_fifo_empty_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_weng_wdb_fifo_full </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> itask_weng_wdb_fifo_full_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_weng_wdb_fifo_empty </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> itask_weng_wdb_fifo_empty_status </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_awfifo_full_empty_status_reg1_t
 *
 * Implemented by: 
 *      fifo_full_empty_status_reg1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  8;
     unsigned      odb_fifo_full                             :  1;
     unsigned      odb_fifo_empty                            :  1;
     unsigned      idb_fifo_full                             :  1;
     unsigned      idb_fifo_empty                            :  1;
     unsigned      cmn_weng_req_fifo_full                    :  1;
     unsigned      cmn_weng_req_fifo_empty                   :  1;
     unsigned      cmn_weng_wdb_fifo_full                    :  1;
     unsigned      cmn_weng_wdb_fifo_empty                   :  1;
     unsigned      tcri_data_fifo_full                       :  1;
     unsigned      tcri_data_fifo_empty                      :  1;
     unsigned      itask_header_fifo_full                    :  1;
     unsigned      itask_header_fifo_empty                   :  1;
     unsigned      itask_qid_fifo_full                       :  1;
     unsigned      itask_qid_fifo_empty                      :  1;
     unsigned      itask_delete_tid_fifo_full                :  1;
     unsigned      itask_delete_tid_fifo_empty               :  1;
     unsigned      ipcq_pgitr_fifo_full                      :  1;
     unsigned      ipcq_pgitr_fifo_empty                     :  1;
     unsigned      ipcq_pgitw_fifo_full                      :  1;
     unsigned      ipcq_pgitw_fifo_empty                     :  1;
     unsigned      itask_weng_req_fifo_full                  :  1;
     unsigned      itask_weng_req_fifo_empty                 :  1;
     unsigned      itask_weng_wdb_fifo_full                  :  1;
     unsigned      itask_weng_wdb_fifo_empty                 :  1;
#else    /* Little Endian */
     unsigned      itask_weng_wdb_fifo_empty                 :  1;
     unsigned      itask_weng_wdb_fifo_full                  :  1;
     unsigned      itask_weng_req_fifo_empty                 :  1;
     unsigned      itask_weng_req_fifo_full                  :  1;
     unsigned      ipcq_pgitw_fifo_empty                     :  1;
     unsigned      ipcq_pgitw_fifo_full                      :  1;
     unsigned      ipcq_pgitr_fifo_empty                     :  1;
     unsigned      ipcq_pgitr_fifo_full                      :  1;
     unsigned      itask_delete_tid_fifo_empty               :  1;
     unsigned      itask_delete_tid_fifo_full                :  1;
     unsigned      itask_qid_fifo_empty                      :  1;
     unsigned      itask_qid_fifo_full                       :  1;
     unsigned      itask_header_fifo_empty                   :  1;
     unsigned      itask_header_fifo_full                    :  1;
     unsigned      tcri_data_fifo_empty                      :  1;
     unsigned      tcri_data_fifo_full                       :  1;
     unsigned      cmn_weng_wdb_fifo_empty                   :  1;
     unsigned      cmn_weng_wdb_fifo_full                    :  1;
     unsigned      cmn_weng_req_fifo_empty                   :  1;
     unsigned      cmn_weng_req_fifo_full                    :  1;
     unsigned      idb_fifo_empty                            :  1;
     unsigned      idb_fifo_full                             :  1;
     unsigned      odb_fifo_empty                            :  1;
     unsigned      odb_fifo_full                             :  1;
     unsigned      reserved0                                 :  8;
#endif
} ncp_nca_awfifo_full_empty_status_reg1_t;

/*! @struct ncp_nca_awfifo_full_empty_status_reg2_t
 *  @brief FIFO Full Empty Status Register2
 *  @details Value of the full and empty flags for the fifos indicated
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_awfifo_full_empty_status_reg2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rpcq_pgitr_fifo_full_empty_pair </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> rpcq_pgitr_fifo_full_empty_status_pair </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rpcq_pgitw_fifo_full_empty_pair </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> rpcq_pgitw_fifo_full_empty_status_pair </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_reng_req_fifo_full_empty_pair </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> rbp_reng_req_fifo_full_empty_status_pair </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_reng_rbf_fifo_full_empty_pair7 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> rbp_reng_rbf_fifo_full_empty_status_pair7 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_reng_rbf_fifo_full_empty_pair6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> rbp_reng_rbf_fifo_full_empty_status_pair6 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_reng_rbf_fifo_full_empty_pair5 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> rbp_reng_rbf_fifo_full_empty_status_pair5 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_reng_rbf_fifo_full_empty_pair4 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> rbp_reng_rbf_fifo_full_empty_status_pair4 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_reng_rbf_fifo_full_empty_pair3 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> rbp_reng_rbf_fifo_full_empty_status_pair3 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_reng_rbf_fifo_full_empty_pair2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> rbp_reng_rbf_fifo_full_empty_status_pair2 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_reng_rbf_fifo_full_empty_pair1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> rbp_reng_rbf_fifo_full_empty_status_pair1 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_reng_rbf_fifo_full_empty_pair0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> rbp_reng_rbf_fifo_full_empty_status_pair0 </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_awfifo_full_empty_status_reg2_t
 *
 * Implemented by: 
 *      fifo_full_empty_status_reg2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 10;
     unsigned      rpcq_pgitr_fifo_full_empty_pair           :  2;
     unsigned      rpcq_pgitw_fifo_full_empty_pair           :  2;
     unsigned      rbp_reng_req_fifo_full_empty_pair         :  2;
     unsigned      rbp_reng_rbf_fifo_full_empty_pair7        :  2;
     unsigned      rbp_reng_rbf_fifo_full_empty_pair6        :  2;
     unsigned      rbp_reng_rbf_fifo_full_empty_pair5        :  2;
     unsigned      rbp_reng_rbf_fifo_full_empty_pair4        :  2;
     unsigned      rbp_reng_rbf_fifo_full_empty_pair3        :  2;
     unsigned      rbp_reng_rbf_fifo_full_empty_pair2        :  2;
     unsigned      rbp_reng_rbf_fifo_full_empty_pair1        :  2;
     unsigned      rbp_reng_rbf_fifo_full_empty_pair0        :  2;
#else    /* Little Endian */
     unsigned      rbp_reng_rbf_fifo_full_empty_pair0        :  2;
     unsigned      rbp_reng_rbf_fifo_full_empty_pair1        :  2;
     unsigned      rbp_reng_rbf_fifo_full_empty_pair2        :  2;
     unsigned      rbp_reng_rbf_fifo_full_empty_pair3        :  2;
     unsigned      rbp_reng_rbf_fifo_full_empty_pair4        :  2;
     unsigned      rbp_reng_rbf_fifo_full_empty_pair5        :  2;
     unsigned      rbp_reng_rbf_fifo_full_empty_pair6        :  2;
     unsigned      rbp_reng_rbf_fifo_full_empty_pair7        :  2;
     unsigned      rbp_reng_req_fifo_full_empty_pair         :  2;
     unsigned      rpcq_pgitw_fifo_full_empty_pair           :  2;
     unsigned      rpcq_pgitr_fifo_full_empty_pair           :  2;
     unsigned      reserved0                                 : 10;
#endif
} ncp_nca_awfifo_full_empty_status_reg2_t;

/*! @struct ncp_nca_awfifo_full_empty_status_reg3_t
 *  @brief FIFO Full Empty Status Register3
 *  @details Value of the full and empty flags for the fifos indicated
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_awfifo_full_empty_status_reg3_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param otask_reng_rbf_fifo_full_empty_pair7 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> otask_reng_rbf_fifo_full_empty_status_pair7 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_reng_rbf_fifo_full_empty_pair6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> otask_reng_rbf_fifo_full_empty_status_pair6 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_reng_rbf_fifo_full_empty_pair5 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> otask_reng_rbf_fifo_full_empty_status_pair5 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_reng_rbf_fifo_full_empty_pair4 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> otask_reng_rbf_fifo_full_empty_status_pair4 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_reng_rbf_fifo_full_empty_pair3 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> otask_reng_rbf_fifo_full_empty_status_pair3 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_reng_rbf_fifo_full_empty_pair2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> otask_reng_rbf_fifo_full_empty_status_pair2 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_reng_rbf_fifo_full_empty_pair1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> otask_reng_rbf_fifo_full_empty_status_pair1 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_reng_rbf_fifo_full_empty_pair0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> otask_reng_rbf_fifo_full_empty_status_pair0 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_reng_rbf_fifo_full_empty_pair7 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> opcq_reng_rbf_fifo_full_empty_status_pair7 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_reng_rbf_fifo_full_empty_pair6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> opcq_reng_rbf_fifo_full_empty_status_pair6 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_reng_rbf_fifo_full_empty_pair5 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> opcq_reng_rbf_fifo_full_empty_status_pair5 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_reng_rbf_fifo_full_empty_pair4 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> opcq_reng_rbf_fifo_full_empty_status_pair4 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_reng_rbf_fifo_full_empty_pair3 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> opcq_reng_rbf_fifo_full_empty_status_pair3 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_reng_rbf_fifo_full_empty_pair2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> opcq_reng_rbf_fifo_full_empty_status_pair2 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_reng_rbf_fifo_full_empty_pair1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> opcq_reng_rbf_fifo_full_empty_status_pair1 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_reng_rbf_fifo_full_empty_pair0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> opcq_reng_rbf_fifo_full_empty_status_pair0 </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_awfifo_full_empty_status_reg3_t
 *
 * Implemented by: 
 *      fifo_full_empty_status_reg3
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      otask_reng_rbf_fifo_full_empty_pair7      :  2;
     unsigned      otask_reng_rbf_fifo_full_empty_pair6      :  2;
     unsigned      otask_reng_rbf_fifo_full_empty_pair5      :  2;
     unsigned      otask_reng_rbf_fifo_full_empty_pair4      :  2;
     unsigned      otask_reng_rbf_fifo_full_empty_pair3      :  2;
     unsigned      otask_reng_rbf_fifo_full_empty_pair2      :  2;
     unsigned      otask_reng_rbf_fifo_full_empty_pair1      :  2;
     unsigned      otask_reng_rbf_fifo_full_empty_pair0      :  2;
     unsigned      opcq_reng_rbf_fifo_full_empty_pair7       :  2;
     unsigned      opcq_reng_rbf_fifo_full_empty_pair6       :  2;
     unsigned      opcq_reng_rbf_fifo_full_empty_pair5       :  2;
     unsigned      opcq_reng_rbf_fifo_full_empty_pair4       :  2;
     unsigned      opcq_reng_rbf_fifo_full_empty_pair3       :  2;
     unsigned      opcq_reng_rbf_fifo_full_empty_pair2       :  2;
     unsigned      opcq_reng_rbf_fifo_full_empty_pair1       :  2;
     unsigned      opcq_reng_rbf_fifo_full_empty_pair0       :  2;
#else    /* Little Endian */
     unsigned      opcq_reng_rbf_fifo_full_empty_pair0       :  2;
     unsigned      opcq_reng_rbf_fifo_full_empty_pair1       :  2;
     unsigned      opcq_reng_rbf_fifo_full_empty_pair2       :  2;
     unsigned      opcq_reng_rbf_fifo_full_empty_pair3       :  2;
     unsigned      opcq_reng_rbf_fifo_full_empty_pair4       :  2;
     unsigned      opcq_reng_rbf_fifo_full_empty_pair5       :  2;
     unsigned      opcq_reng_rbf_fifo_full_empty_pair6       :  2;
     unsigned      opcq_reng_rbf_fifo_full_empty_pair7       :  2;
     unsigned      otask_reng_rbf_fifo_full_empty_pair0      :  2;
     unsigned      otask_reng_rbf_fifo_full_empty_pair1      :  2;
     unsigned      otask_reng_rbf_fifo_full_empty_pair2      :  2;
     unsigned      otask_reng_rbf_fifo_full_empty_pair3      :  2;
     unsigned      otask_reng_rbf_fifo_full_empty_pair4      :  2;
     unsigned      otask_reng_rbf_fifo_full_empty_pair5      :  2;
     unsigned      otask_reng_rbf_fifo_full_empty_pair6      :  2;
     unsigned      otask_reng_rbf_fifo_full_empty_pair7      :  2;
#endif
} ncp_nca_awfifo_full_empty_status_reg3_t;

/*! @struct ncp_nca_awfifo_full_empty_status_reg4_t
 *  @brief FIFO Full Empty Status Register4
 *  @details Value of the full and empty flags for the fifos indicated
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_awfifo_full_empty_status_reg4_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param otsd_reng_rbf_fifo_full_empty_pair7 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> otsd_reng_rbf_fifo_full_empty_status_pair7 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otsd_reng_rbf_fifo_full_empty_pair6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> otsd_reng_rbf_fifo_full_empty_status_pair6 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otsd_reng_rbf_fifo_full_empty_pair5 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> otsd_reng_rbf_fifo_full_empty_status_pair5 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otsd_reng_rbf_fifo_full_empty_pair4 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> otsd_reng_rbf_fifo_full_empty_status_pair4 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otsd_reng_rbf_fifo_full_empty_pair3 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> otsd_reng_rbf_fifo_full_empty_status_pair3 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otsd_reng_rbf_fifo_full_empty_pair2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> otsd_reng_rbf_fifo_full_empty_status_pair2 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otsd_reng_rbf_fifo_full_empty_pair1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> otsd_reng_rbf_fifo_full_empty_status_pair1 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otsd_reng_rbf_fifo_full_empty_pair0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> otsd_reng_rbf_fifo_full_empty_status_pair0 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otsd_reng_req_fifo_full_empty_pair </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> otsd_reng_req_fifo_full_empty_status_pair </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_entry_fifo_full_empty_pair </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> opcq_entry_fifo_full_empty_status_pair </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_index_fifo_full_empty_pair </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> opcq_index_fifo_full_empty_status_pair </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_index_update_fifo_full_empty_pair </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> opcq_index_update_fifo_full_empty_status_pair </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_pgitr_fifo_full_empty_pair </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> opcq_pgitr_fifo_full_empty_status_pair </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_pgitw_fifo_full_empty_pair </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> opcq_pgitw_fifo_full_empty_status_pair </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_reng_req_fifo_full_empty_pair </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> otask_reng_req_fifo_full_empty_status_pair </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_reng_req_fifo_full_empty_pair </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> opcq_reng_req_fifo_full_empty_status_pair </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_awfifo_full_empty_status_reg4_t
 *
 * Implemented by: 
 *      fifo_full_empty_status_reg4
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      otsd_reng_rbf_fifo_full_empty_pair7       :  2;
     unsigned      otsd_reng_rbf_fifo_full_empty_pair6       :  2;
     unsigned      otsd_reng_rbf_fifo_full_empty_pair5       :  2;
     unsigned      otsd_reng_rbf_fifo_full_empty_pair4       :  2;
     unsigned      otsd_reng_rbf_fifo_full_empty_pair3       :  2;
     unsigned      otsd_reng_rbf_fifo_full_empty_pair2       :  2;
     unsigned      otsd_reng_rbf_fifo_full_empty_pair1       :  2;
     unsigned      otsd_reng_rbf_fifo_full_empty_pair0       :  2;
     unsigned      otsd_reng_req_fifo_full_empty_pair        :  2;
     unsigned      opcq_entry_fifo_full_empty_pair           :  2;
     unsigned      opcq_index_fifo_full_empty_pair           :  2;
     unsigned      opcq_index_update_fifo_full_empty_pair    :  2;
     unsigned      opcq_pgitr_fifo_full_empty_pair           :  2;
     unsigned      opcq_pgitw_fifo_full_empty_pair           :  2;
     unsigned      otask_reng_req_fifo_full_empty_pair       :  2;
     unsigned      opcq_reng_req_fifo_full_empty_pair        :  2;
#else    /* Little Endian */
     unsigned      opcq_reng_req_fifo_full_empty_pair        :  2;
     unsigned      otask_reng_req_fifo_full_empty_pair       :  2;
     unsigned      opcq_pgitw_fifo_full_empty_pair           :  2;
     unsigned      opcq_pgitr_fifo_full_empty_pair           :  2;
     unsigned      opcq_index_update_fifo_full_empty_pair    :  2;
     unsigned      opcq_index_fifo_full_empty_pair           :  2;
     unsigned      opcq_entry_fifo_full_empty_pair           :  2;
     unsigned      otsd_reng_req_fifo_full_empty_pair        :  2;
     unsigned      otsd_reng_rbf_fifo_full_empty_pair0       :  2;
     unsigned      otsd_reng_rbf_fifo_full_empty_pair1       :  2;
     unsigned      otsd_reng_rbf_fifo_full_empty_pair2       :  2;
     unsigned      otsd_reng_rbf_fifo_full_empty_pair3       :  2;
     unsigned      otsd_reng_rbf_fifo_full_empty_pair4       :  2;
     unsigned      otsd_reng_rbf_fifo_full_empty_pair5       :  2;
     unsigned      otsd_reng_rbf_fifo_full_empty_pair6       :  2;
     unsigned      otsd_reng_rbf_fifo_full_empty_pair7       :  2;
#endif
} ncp_nca_awfifo_full_empty_status_reg4_t;

/*! @struct ncp_nca_awfifo_full_empty_status_reg5_t
 *  @brief FIFO Full Empty Status Register5
 *  @details Value of the full and empty flags for the fifos indicated
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_awfifo_full_empty_status_reg5_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_pgitr_fifo_full_empty_pair </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> tpcq_pgitr_fifo_full_empty_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_pgitw_fifo_full_empty_pair </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> tpcq_pgitw_fifo_full_empty_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_reng_req_fifo_full_empty_pair </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> tfc_reng_req_fifo_full_empty_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_reng_rbf_fifo_full_empty_pair7 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> tfc_reng_rbf_fifo_full_empty_status_pair7 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_reng_rbf_fifo_full_empty_pair6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> tfc_reng_rbf_fifo_full_empty_status_pair6 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_reng_rbf_fifo_full_empty_pair5 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> tfc_reng_rbf_fifo_full_empty_status_pair5 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_reng_rbf_fifo_full_empty_pair4 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> tfc_reng_rbf_fifo_full_empty_status_pair4 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_reng_rbf_fifo_full_empty_pair3 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> tfc_reng_rbf_fifo_full_empty_status_pair3 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_reng_rbf_fifo_full_empty_pair2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> tfc_reng_rbf_fifo_full_empty_status_pair2 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_reng_rbf_fifo_full_empty_pair1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> tfc_reng_rbf_fifo_full_empty_status_pair1 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_reng_rbf_fifo_full_empty_pair0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> tfc_reng_rbf_fifo_full_empty_status_pair0 </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_awfifo_full_empty_status_reg5_t
 *
 * Implemented by: 
 *      fifo_full_empty_status_reg5
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 10;
     unsigned      tpcq_pgitr_fifo_full_empty_pair           :  2;
     unsigned      tpcq_pgitw_fifo_full_empty_pair           :  2;
     unsigned      tfc_reng_req_fifo_full_empty_pair         :  2;
     unsigned      tfc_reng_rbf_fifo_full_empty_pair7        :  2;
     unsigned      tfc_reng_rbf_fifo_full_empty_pair6        :  2;
     unsigned      tfc_reng_rbf_fifo_full_empty_pair5        :  2;
     unsigned      tfc_reng_rbf_fifo_full_empty_pair4        :  2;
     unsigned      tfc_reng_rbf_fifo_full_empty_pair3        :  2;
     unsigned      tfc_reng_rbf_fifo_full_empty_pair2        :  2;
     unsigned      tfc_reng_rbf_fifo_full_empty_pair1        :  2;
     unsigned      tfc_reng_rbf_fifo_full_empty_pair0        :  2;
#else    /* Little Endian */
     unsigned      tfc_reng_rbf_fifo_full_empty_pair0        :  2;
     unsigned      tfc_reng_rbf_fifo_full_empty_pair1        :  2;
     unsigned      tfc_reng_rbf_fifo_full_empty_pair2        :  2;
     unsigned      tfc_reng_rbf_fifo_full_empty_pair3        :  2;
     unsigned      tfc_reng_rbf_fifo_full_empty_pair4        :  2;
     unsigned      tfc_reng_rbf_fifo_full_empty_pair5        :  2;
     unsigned      tfc_reng_rbf_fifo_full_empty_pair6        :  2;
     unsigned      tfc_reng_rbf_fifo_full_empty_pair7        :  2;
     unsigned      tfc_reng_req_fifo_full_empty_pair         :  2;
     unsigned      tpcq_pgitw_fifo_full_empty_pair           :  2;
     unsigned      tpcq_pgitr_fifo_full_empty_pair           :  2;
     unsigned      reserved0                                 : 10;
#endif
} ncp_nca_awfifo_full_empty_status_reg5_t;

/*! @struct ncp_nca_awfifo_full_empty_status_reg6_t
 *  @brief FIFO Full Empty Status Register6
 *  @details Value of the full and empty flags for the fifos indicated
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_awfifo_full_empty_status_reg6_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_cfg_req_fifo_full_empty_pair </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> cmn_cfg_req_fifo_full_empty_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_reng_req_fifo_full_empty_pair </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> cmn_reng_req_fifo_full_empty_status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_reng_rbf_fifo_full_empty_pair1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> cmn_reng_rbf_fifo_full_empty_status_pair1 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_reng_rbf_fifo_full_empty_pair0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> cmn_reng_rbf_fifo_full_empty_status_pair0 </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_awfifo_full_empty_status_reg6_t
 *
 * Implemented by: 
 *      fifo_full_empty_status_reg6
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      cmn_cfg_req_fifo_full_empty_pair          :  2;
     unsigned      reserved1                                 :  9;
     unsigned      cmn_reng_req_fifo_full_empty_pair         :  2;
     unsigned      reserved2                                 : 12;
     unsigned      cmn_reng_rbf_fifo_full_empty_pair1        :  2;
     unsigned      cmn_reng_rbf_fifo_full_empty_pair0        :  2;
#else    /* Little Endian */
     unsigned      cmn_reng_rbf_fifo_full_empty_pair0        :  2;
     unsigned      cmn_reng_rbf_fifo_full_empty_pair1        :  2;
     unsigned      reserved2                                 : 12;
     unsigned      cmn_reng_req_fifo_full_empty_pair         :  2;
     unsigned      reserved1                                 :  9;
     unsigned      cmn_cfg_req_fifo_full_empty_pair          :  2;
     unsigned      reserved0                                 :  3;
#endif
} ncp_nca_awfifo_full_empty_status_reg6_t;

/*! @struct ncp_nca_tfc_unordered_mode_reg_t
 *  @brief Task Flow Completion Unordered Mode Register
 *  @details Enables task flow completion to operate in unordered mode.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_tfc_unordered_mode_reg_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 31 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_unordered_mode_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Task flow completion unordered mode enable. </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_tfc_unordered_mode_reg_t
 *
 * Implemented by: 
 *      tfc_unordered_mode
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 31;
     unsigned      tfc_unordered_mode_en                     :  1;
#else    /* Little Endian */
     unsigned      tfc_unordered_mode_en                     :  1;
     unsigned      reserved0                                 : 31;
#endif
} ncp_nca_tfc_unordered_mode_reg_t;

/*! @struct ncp_nca_AW_smon01_nca_task_smon_r_t
 *  @brief AW_smon CONTROL1 register
 *  @details This is used to configure the operation of the 2 internal counters in the SMON
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_AW_smon01_nca_task_smon_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mode1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> select input signal for SMON1 engine </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mode0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> select input signal for SMON0 engine </td>
 * </tr>
 * </table>
 * Applies to: v2 v3 acp2500 --> ncp_nca_AW_smon01_nca_task_smon_r_t
 *
 * Implemented by: 
 *      AW_SMON01_nca_task_smon
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      mode1                                     :  8;
     unsigned      mode0                                     :  8;
#else    /* Little Endian */
     unsigned      mode0                                     :  8;
     unsigned      mode1                                     :  8;
     unsigned      reserved0                                 : 16;
#endif
} ncp_nca_AW_smon01_nca_task_smon_r_t;

/*! @struct ncp_nca_config_init_woclr_reg_acp2500_t
 *  @brief NCA Config and Initialization Parameters
 *  @details This is an alias of the config_init register which performs write one to clear.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_config_init_woclr_reg_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_end_data_fill_off </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Turn off filling of dummy data on last quadword of
 *        an itask to make the last write 16 bytes.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_ack_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> cfg_ring_ack_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_compl_cnt_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> tfc_completion_count_reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_flush </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> tfc_flush </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> cpcq_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_accum_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> otask_accum_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_accum_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> itask_accum_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> tfc_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otbp_soft_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> otbp_soft_reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_soft_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> rbp_soft_reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> rbp_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otbp_ext_mem_wen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Output task backpressure external memory write enable.
 *        Turning this bit on immediatly causes a write of otask_opcq_bp
 *        to axi memory at the address defined by otbp_bar_upper
 *        and otbp_bar_lower. Subsequent writes will occur any
 *        time the state of otask_opcq_bp changes.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param spare </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> spare </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_exec_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> cpcq execution disable bit : NOTE: This bit is supposed
 *        to be used sparingly (for debugging etc.) to temporarily
 *        halt the execution from cfg request fifo of the cpcq
 *        entries
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_cons_ent </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> opcq_consecutive_entries_per_queue_to_send </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> opcq_entry_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ipcq_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> ipcq_entry_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> tpcq_entry_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rpcq_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> rpcq_entry_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_w_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> pgit_w_num_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_r_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> pgit_r_num_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_config_init_woclr_reg_acp2500_t
 *
 * Implemented by: 
 *      config_init_woclr
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      itask_end_data_fill_off                   :  1;
     unsigned      cfg_ring_ack_timer_en                     :  1;
     unsigned      tfc_compl_cnt_reset                       :  1;
     unsigned      tfc_flush                                 :  1;
     unsigned      cpcq_en                                   :  1;
     unsigned      otask_accum_en                            :  1;
     unsigned      itask_accum_en                            :  1;
     unsigned      tfc_en                                    :  1;
     unsigned      otbp_soft_reset                           :  1;
     unsigned      rbp_soft_reset                            :  1;
     unsigned      rbp_en                                    :  1;
     unsigned      otbp_ext_mem_wen                          :  1;
     unsigned      spare                                     :  2;
     unsigned      cpcq_exec_disable                         :  1;
     unsigned      opcq_cons_ent                             :  4;
     unsigned      opcq_num_beat                             :  2;
     unsigned      ipcq_num_beat                             :  2;
     unsigned      tpcq_num_beat                             :  2;
     unsigned      rpcq_num_beat                             :  2;
     unsigned      pgit_w_num_beat                           :  2;
     unsigned      pgit_r_num_beat                           :  2;
#else    /* Little Endian */
     unsigned      pgit_r_num_beat                           :  2;
     unsigned      pgit_w_num_beat                           :  2;
     unsigned      rpcq_num_beat                             :  2;
     unsigned      tpcq_num_beat                             :  2;
     unsigned      ipcq_num_beat                             :  2;
     unsigned      opcq_num_beat                             :  2;
     unsigned      opcq_cons_ent                             :  4;
     unsigned      cpcq_exec_disable                         :  1;
     unsigned      spare                                     :  2;
     unsigned      otbp_ext_mem_wen                          :  1;
     unsigned      rbp_en                                    :  1;
     unsigned      rbp_soft_reset                            :  1;
     unsigned      otbp_soft_reset                           :  1;
     unsigned      tfc_en                                    :  1;
     unsigned      itask_accum_en                            :  1;
     unsigned      otask_accum_en                            :  1;
     unsigned      cpcq_en                                   :  1;
     unsigned      tfc_flush                                 :  1;
     unsigned      tfc_compl_cnt_reset                       :  1;
     unsigned      cfg_ring_ack_timer_en                     :  1;
     unsigned      itask_end_data_fill_off                   :  1;
     unsigned      reserved0                                 :  1;
#endif
} ncp_nca_config_init_woclr_reg_acp2500_t;

/*! @struct ncp_nca_config_init_woset_reg_acp2500_t
 *  @brief NCA Config and Initialization Parameters
 *  @details This is an alias of the config_init register which performs write one to set.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_config_init_woset_reg_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_end_data_fill_off </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Turn off filling of dummy data on last quadword of
 *        an itask to make the last write 16 bytes.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_ack_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> cfg_ring_ack_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_compl_cnt_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> tfc_completion_count_reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_flush </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> tfc_flush </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> cpcq_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_accum_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> otask_accum_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_accum_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> itask_accum_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> tfc_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otbp_soft_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> otbp_soft_reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_soft_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> rbp_soft_reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> rbp_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otbp_ext_mem_wen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Output task backpressure external memory write enable.
 *        Turning this bit on immediatly causes a write of otask_opcq_bp
 *        to axi memory at the address defined by otbp_bar_upper
 *        and otbp_bar_lower. Subsequent writes will occur any
 *        time the state of otask_opcq_bp changes.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param spare </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> spare </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_exec_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> cpcq execution disable bit : NOTE: This bit is supposed
 *        to be used sparingly (for debugging etc.) to temporarily
 *        halt the execution from cfg request fifo of the cpcq
 *        entries
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_cons_ent </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> opcq_consecutive_entries_per_queue_to_send </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> opcq_entry_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ipcq_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> ipcq_entry_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> tpcq_entry_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rpcq_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> rpcq_entry_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_w_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> pgit_w_num_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_r_num_beat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> pgit_r_num_beats_per_burst:00:1,01:2,10:4,11:8 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_config_init_woset_reg_acp2500_t
 *
 * Implemented by: 
 *      config_init_woset
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      itask_end_data_fill_off                   :  1;
     unsigned      cfg_ring_ack_timer_en                     :  1;
     unsigned      tfc_compl_cnt_reset                       :  1;
     unsigned      tfc_flush                                 :  1;
     unsigned      cpcq_en                                   :  1;
     unsigned      otask_accum_en                            :  1;
     unsigned      itask_accum_en                            :  1;
     unsigned      tfc_en                                    :  1;
     unsigned      otbp_soft_reset                           :  1;
     unsigned      rbp_soft_reset                            :  1;
     unsigned      rbp_en                                    :  1;
     unsigned      otbp_ext_mem_wen                          :  1;
     unsigned      spare                                     :  2;
     unsigned      cpcq_exec_disable                         :  1;
     unsigned      opcq_cons_ent                             :  4;
     unsigned      opcq_num_beat                             :  2;
     unsigned      ipcq_num_beat                             :  2;
     unsigned      tpcq_num_beat                             :  2;
     unsigned      rpcq_num_beat                             :  2;
     unsigned      pgit_w_num_beat                           :  2;
     unsigned      pgit_r_num_beat                           :  2;
#else    /* Little Endian */
     unsigned      pgit_r_num_beat                           :  2;
     unsigned      pgit_w_num_beat                           :  2;
     unsigned      rpcq_num_beat                             :  2;
     unsigned      tpcq_num_beat                             :  2;
     unsigned      ipcq_num_beat                             :  2;
     unsigned      opcq_num_beat                             :  2;
     unsigned      opcq_cons_ent                             :  4;
     unsigned      cpcq_exec_disable                         :  1;
     unsigned      spare                                     :  2;
     unsigned      otbp_ext_mem_wen                          :  1;
     unsigned      rbp_en                                    :  1;
     unsigned      rbp_soft_reset                            :  1;
     unsigned      otbp_soft_reset                           :  1;
     unsigned      tfc_en                                    :  1;
     unsigned      itask_accum_en                            :  1;
     unsigned      otask_accum_en                            :  1;
     unsigned      cpcq_en                                   :  1;
     unsigned      tfc_flush                                 :  1;
     unsigned      tfc_compl_cnt_reset                       :  1;
     unsigned      cfg_ring_ack_timer_en                     :  1;
     unsigned      itask_end_data_fill_off                   :  1;
     unsigned      reserved0                                 :  1;
#endif
} ncp_nca_config_init_woset_reg_acp2500_t;

/*! @struct ncp_nca_pgit_load_grp_indexes_woset_reg_acp2500_t
 *  @brief PGIT Load NCA and CPU Indexes Register
 *  @details This is an alias of the pgit_load_grp_indexes register which performs write one to set.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_pgit_load_grp_indexes_woset_reg_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param load_nca_index_grp </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> load_nca_indexes </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param load_cpu_index_grp </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> load_cpu_indexes </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_pgit_load_grp_indexes_woset_reg_acp2500_t
 *
 * Implemented by: 
 *      pgit_load_grp_indexes_woset
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 10;
     unsigned      load_nca_index_grp                        :  6;
     unsigned      reserved1                                 : 10;
     unsigned      load_cpu_index_grp                        :  6;
#else    /* Little Endian */
     unsigned      load_cpu_index_grp                        :  6;
     unsigned      reserved1                                 : 10;
     unsigned      load_nca_index_grp                        :  6;
     unsigned      reserved0                                 : 10;
#endif
} ncp_nca_pgit_load_grp_indexes_woset_reg_acp2500_t;

/*! @struct ncp_nca_otask_grp_cnt_compare_reg_acp2500_t
 *  @brief Output Task Group Count Compare Register
 *  @details This register defines a count value for output tasks processed for a given group that will trigger a poke to the PGIT upload and load timers.  The poke is disabled when the count is set to zero.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_otask_grp_cnt_compare_reg_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cnt_cmp_value </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> This field is compared to an internal counter that
 *        tracks the number of otasks processed to determine
 *        when to do a poke of the PGIT load and upload timers.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_otask_grp_cnt_compare_reg_acp2500_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cnt_cmp_value                             :  8;
#else    /* Little Endian */
     unsigned      cnt_cmp_value                             :  8;
     unsigned      reserved0                                 : 24;
#endif
} ncp_nca_otask_grp_cnt_compare_reg_acp2500_t;

/*! @struct ncp_nca_hw_poke_and_timer_enable_reg_woclr_acp2500_t
 *  @brief Software Enable switches for Pointer Write and Read Pokes
 *  @details This is an alias of the hw_poke_and_timer_enable register which performs write one to clear.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_hw_poke_and_timer_enable_reg_woclr_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hardware_load_poke_en </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> hardware_load_poke_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hardware_upload_poke_en </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> hardware_upload_poke_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_poke_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> cpcq_poke_enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_poke_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> tpcq_poke_enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_poke_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> opcq_poke_enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ipcq_poke_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> ipcq_poke_enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp5_load_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> grp5_load_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp4_load_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> grp4_load_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp3_load_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> grp3_load_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp2_load_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> grp2_load_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp1_load_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> grp1_load_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp0_load_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> grp0_load_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp5_upload_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> grp5_upload_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp4_upload_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> grp4_upload_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp3_upload_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> grp3_upload_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp2_upload_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> grp2_upload_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp1_upload_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> grp1_upload_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp0_upload_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> grp0_upload_timer_en </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_hw_poke_and_timer_enable_reg_woclr_acp2500_t
 *
 * Implemented by: 
 *      hw_poke_and_timer_enable_woclr
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  2;
     unsigned      hardware_load_poke_en                     :  6;
     unsigned      reserved1                                 :  2;
     unsigned      hardware_upload_poke_en                   :  6;
     unsigned      cpcq_poke_enable                          :  1;
     unsigned      tpcq_poke_enable                          :  1;
     unsigned      opcq_poke_enable                          :  1;
     unsigned      ipcq_poke_enable                          :  1;
     unsigned      grp5_load_timer_en                        :  1;
     unsigned      grp4_load_timer_en                        :  1;
     unsigned      grp3_load_timer_en                        :  1;
     unsigned      grp2_load_timer_en                        :  1;
     unsigned      grp1_load_timer_en                        :  1;
     unsigned      grp0_load_timer_en                        :  1;
     unsigned      grp5_upload_timer_en                      :  1;
     unsigned      grp4_upload_timer_en                      :  1;
     unsigned      grp3_upload_timer_en                      :  1;
     unsigned      grp2_upload_timer_en                      :  1;
     unsigned      grp1_upload_timer_en                      :  1;
     unsigned      grp0_upload_timer_en                      :  1;
#else    /* Little Endian */
     unsigned      grp0_upload_timer_en                      :  1;
     unsigned      grp1_upload_timer_en                      :  1;
     unsigned      grp2_upload_timer_en                      :  1;
     unsigned      grp3_upload_timer_en                      :  1;
     unsigned      grp4_upload_timer_en                      :  1;
     unsigned      grp5_upload_timer_en                      :  1;
     unsigned      grp0_load_timer_en                        :  1;
     unsigned      grp1_load_timer_en                        :  1;
     unsigned      grp2_load_timer_en                        :  1;
     unsigned      grp3_load_timer_en                        :  1;
     unsigned      grp4_load_timer_en                        :  1;
     unsigned      grp5_load_timer_en                        :  1;
     unsigned      ipcq_poke_enable                          :  1;
     unsigned      opcq_poke_enable                          :  1;
     unsigned      tpcq_poke_enable                          :  1;
     unsigned      cpcq_poke_enable                          :  1;
     unsigned      hardware_upload_poke_en                   :  6;
     unsigned      reserved1                                 :  2;
     unsigned      hardware_load_poke_en                     :  6;
     unsigned      reserved0                                 :  2;
#endif
} ncp_nca_hw_poke_and_timer_enable_reg_woclr_acp2500_t;

/*! @struct ncp_nca_hw_poke_and_timer_enable_reg_woset_acp2500_t
 *  @brief Software Enable switches for Pointer Write and Read Pokes
 *  @details This is an alias of the hw_poke_and_timer_enable register which performs write one to set.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_hw_poke_and_timer_enable_reg_woset_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hardware_load_poke_en </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> hardware_load_poke_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hardware_upload_poke_en </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> hardware_upload_poke_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_poke_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> cpcq_poke_enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_poke_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> tpcq_poke_enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_poke_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> opcq_poke_enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ipcq_poke_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> ipcq_poke_enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp5_load_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> grp5_load_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp4_load_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> grp4_load_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp3_load_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> grp3_load_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp2_load_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> grp2_load_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp1_load_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> grp1_load_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp0_load_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> grp0_load_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp5_upload_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> grp5_upload_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp4_upload_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> grp4_upload_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp3_upload_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> grp3_upload_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp2_upload_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> grp2_upload_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp1_upload_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> grp1_upload_timer_en </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param grp0_upload_timer_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> grp0_upload_timer_en </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_hw_poke_and_timer_enable_reg_woset_acp2500_t
 *
 * Implemented by: 
 *      hw_poke_and_timer_enable_woset
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  2;
     unsigned      hardware_load_poke_en                     :  6;
     unsigned      reserved1                                 :  2;
     unsigned      hardware_upload_poke_en                   :  6;
     unsigned      cpcq_poke_enable                          :  1;
     unsigned      tpcq_poke_enable                          :  1;
     unsigned      opcq_poke_enable                          :  1;
     unsigned      ipcq_poke_enable                          :  1;
     unsigned      grp5_load_timer_en                        :  1;
     unsigned      grp4_load_timer_en                        :  1;
     unsigned      grp3_load_timer_en                        :  1;
     unsigned      grp2_load_timer_en                        :  1;
     unsigned      grp1_load_timer_en                        :  1;
     unsigned      grp0_load_timer_en                        :  1;
     unsigned      grp5_upload_timer_en                      :  1;
     unsigned      grp4_upload_timer_en                      :  1;
     unsigned      grp3_upload_timer_en                      :  1;
     unsigned      grp2_upload_timer_en                      :  1;
     unsigned      grp1_upload_timer_en                      :  1;
     unsigned      grp0_upload_timer_en                      :  1;
#else    /* Little Endian */
     unsigned      grp0_upload_timer_en                      :  1;
     unsigned      grp1_upload_timer_en                      :  1;
     unsigned      grp2_upload_timer_en                      :  1;
     unsigned      grp3_upload_timer_en                      :  1;
     unsigned      grp4_upload_timer_en                      :  1;
     unsigned      grp5_upload_timer_en                      :  1;
     unsigned      grp0_load_timer_en                        :  1;
     unsigned      grp1_load_timer_en                        :  1;
     unsigned      grp2_load_timer_en                        :  1;
     unsigned      grp3_load_timer_en                        :  1;
     unsigned      grp4_load_timer_en                        :  1;
     unsigned      grp5_load_timer_en                        :  1;
     unsigned      ipcq_poke_enable                          :  1;
     unsigned      opcq_poke_enable                          :  1;
     unsigned      tpcq_poke_enable                          :  1;
     unsigned      cpcq_poke_enable                          :  1;
     unsigned      hardware_upload_poke_en                   :  6;
     unsigned      reserved1                                 :  2;
     unsigned      hardware_load_poke_en                     :  6;
     unsigned      reserved0                                 :  2;
#endif
} ncp_nca_hw_poke_and_timer_enable_reg_woset_acp2500_t;

/*! @struct ncp_nca_pio_lock_cown_reg_acp2500_t
 *  @brief NCA PIO Lock Current Owner Register
 *  @details This register provides the ability to read the nca_pio_lock register without engaging the semaphore mechanism.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_pio_lock_cown_reg_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param proc_id </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Only one bit will ever be set at a time. Indicates
 *        ID of processor that has control of configuration
 *        interface.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_pio_lock_cown_reg_acp2500_t
 *
 * Implemented by: 
 *      nca_pio_lock_cown
 */
 
typedef struct
{
     unsigned  int                   proc_id;
} ncp_nca_pio_lock_cown_reg_acp2500_t;

/*! @struct ncp_nca_software_pgit_load_poke_woset_reg_acp2500_t
 *  @brief PGIT Software Load Poke Register
 *  @details This is an alias of the pgit_software_load_poke_reg register which performs write one to set.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_software_pgit_load_poke_woset_reg_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 26 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param software_load_poke_grp </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Poke the PGIT CPU index load timers. Each bit corresponds
 *        to a PCQ group.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_software_pgit_load_poke_woset_reg_acp2500_t
 *
 * Implemented by: 
 *      pgit_software_load_poke_reg_woset
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 26;
     unsigned      software_load_poke_grp                    :  6;
#else    /* Little Endian */
     unsigned      software_load_poke_grp                    :  6;
     unsigned      reserved0                                 : 26;
#endif
} ncp_nca_software_pgit_load_poke_woset_reg_acp2500_t;

/*! @struct ncp_nca_mpic_ctrl_reg_woclr_acp2500_t
 *  @brief MPIC Interrupt Control Register
 *  @details This is an alias of the mpic_ctrl register which performs write one to clear.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_mpic_ctrl_reg_woclr_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sel </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Select. Maps the non group related interrupts to one
 *        of the 6 MPIC interrupt outputs. If this field is
 *        set to a value > 5, the interrupts are mapped to MPIC
 *        interrupt pin 0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param int_en </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Interrupt Enable. Each bit enables the corresponding
 *        MPIC interrupt output.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_mpic_ctrl_reg_woclr_acp2500_t
 *
 * Implemented by: 
 *      mpic_ctrl_woclr
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 21;
     unsigned      sel                                       :  3;
     unsigned      reserved1                                 :  2;
     unsigned      int_en                                    :  6;
#else    /* Little Endian */
     unsigned      int_en                                    :  6;
     unsigned      reserved1                                 :  2;
     unsigned      sel                                       :  3;
     unsigned      reserved0                                 : 21;
#endif
} ncp_nca_mpic_ctrl_reg_woclr_acp2500_t;

/*! @struct ncp_nca_mpic_ctrl_reg_woset_acp2500_t
 *  @brief MPIC Interrupt Control Register
 *  @details This is an alias of the mpic_ctrl register which performs write one to set.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_mpic_ctrl_reg_woset_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sel </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Select. Maps the non group related interrupts to one
 *        of the 6 MPIC interrupt outputs. If this field is
 *        set to a value > 5, the interrupts are mapped to MPIC
 *        interrupt pin 0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param int_en </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Interrupt Enable. Each bit enables the corresponding
 *        MPIC interrupt output.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_mpic_ctrl_reg_woset_acp2500_t
 *
 * Implemented by: 
 *      mpic_ctrl_woset
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 21;
     unsigned      sel                                       :  3;
     unsigned      reserved1                                 :  2;
     unsigned      int_en                                    :  6;
#else    /* Little Endian */
     unsigned      int_en                                    :  6;
     unsigned      reserved1                                 :  2;
     unsigned      sel                                       :  3;
     unsigned      reserved0                                 : 21;
#endif
} ncp_nca_mpic_ctrl_reg_woset_acp2500_t;

/*! @struct ncp_nca_en_reg0_woclr_acp2500_t
 *  @brief Interrupt Enable Register
 *  @details This is an alias of grp_interrupt_enable_table.en_r0 which performs write one to clear.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_en_reg0_woclr_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_inst_compl_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> configuration instruction complete interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> input tasks have arrived for group 5 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> input tasks have arrived for group 4 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> input tasks have arrived for group 3 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> input tasks have arrived for group 2 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> input tasks have arrived for group 1 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> input tasks have arrived for group 0 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 5
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 4
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 3
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 2
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 1
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 0
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 5
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 4
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 3
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 2
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 1
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 0
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 5
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 4
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 3
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 2
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 1
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 0
 *        Enable
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_en_reg0_woclr_acp2500_t
 *
 * Implemented by: 
 *      en_r0_woclr
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      cfg_inst_compl_int                        :  1;
     unsigned      itask_arrival_int_grp5                    :  1;
     unsigned      itask_arrival_int_grp4                    :  1;
     unsigned      itask_arrival_int_grp3                    :  1;
     unsigned      itask_arrival_int_grp2                    :  1;
     unsigned      itask_arrival_int_grp1                    :  1;
     unsigned      itask_arrival_int_grp0                    :  1;
     unsigned      opcq_complete_int_grp5                    :  1;
     unsigned      opcq_complete_int_grp4                    :  1;
     unsigned      opcq_complete_int_grp3                    :  1;
     unsigned      opcq_complete_int_grp2                    :  1;
     unsigned      opcq_complete_int_grp1                    :  1;
     unsigned      opcq_complete_int_grp0                    :  1;
     unsigned      tpcq_complete_int_grp5                    :  1;
     unsigned      tpcq_complete_int_grp4                    :  1;
     unsigned      tpcq_complete_int_grp3                    :  1;
     unsigned      tpcq_complete_int_grp2                    :  1;
     unsigned      tpcq_complete_int_grp1                    :  1;
     unsigned      tpcq_complete_int_grp0                    :  1;
     unsigned      cpcq_complete_int_grp5                    :  1;
     unsigned      cpcq_complete_int_grp4                    :  1;
     unsigned      cpcq_complete_int_grp3                    :  1;
     unsigned      cpcq_complete_int_grp2                    :  1;
     unsigned      cpcq_complete_int_grp1                    :  1;
     unsigned      cpcq_complete_int_grp0                    :  1;
#else    /* Little Endian */
     unsigned      cpcq_complete_int_grp0                    :  1;
     unsigned      cpcq_complete_int_grp1                    :  1;
     unsigned      cpcq_complete_int_grp2                    :  1;
     unsigned      cpcq_complete_int_grp3                    :  1;
     unsigned      cpcq_complete_int_grp4                    :  1;
     unsigned      cpcq_complete_int_grp5                    :  1;
     unsigned      tpcq_complete_int_grp0                    :  1;
     unsigned      tpcq_complete_int_grp1                    :  1;
     unsigned      tpcq_complete_int_grp2                    :  1;
     unsigned      tpcq_complete_int_grp3                    :  1;
     unsigned      tpcq_complete_int_grp4                    :  1;
     unsigned      tpcq_complete_int_grp5                    :  1;
     unsigned      opcq_complete_int_grp0                    :  1;
     unsigned      opcq_complete_int_grp1                    :  1;
     unsigned      opcq_complete_int_grp2                    :  1;
     unsigned      opcq_complete_int_grp3                    :  1;
     unsigned      opcq_complete_int_grp4                    :  1;
     unsigned      opcq_complete_int_grp5                    :  1;
     unsigned      itask_arrival_int_grp0                    :  1;
     unsigned      itask_arrival_int_grp1                    :  1;
     unsigned      itask_arrival_int_grp2                    :  1;
     unsigned      itask_arrival_int_grp3                    :  1;
     unsigned      itask_arrival_int_grp4                    :  1;
     unsigned      itask_arrival_int_grp5                    :  1;
     unsigned      cfg_inst_compl_int                        :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_nca_en_reg0_woclr_acp2500_t;

/*! @struct ncp_nca_en_reg0_woset_acp2500_t
 *  @brief Interrupt Enable Register
 *  @details This is an alias of grp_interrupt_enable_table.en_r0 which performs write one to set.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_en_reg0_woset_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_inst_compl_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> configuration instruction complete interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> input tasks have arrived for group 5 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> input tasks have arrived for group 4 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> input tasks have arrived for group 3 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> input tasks have arrived for group 2 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> input tasks have arrived for group 1 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_arrival_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> input tasks have arrived for group 0 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 5
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 4
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 3
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 2
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 1
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_complete_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> oPCQ completed entry processing interrupt group 0
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 5
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 4
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 3
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 2
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 1
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_complete_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> tPCQ completed entry processing interrupt group 0
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 5
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 4
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 3
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 2
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 1
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_complete_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> cPCQ completed entry processing interrupt group 0
 *        Enable
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_en_reg0_woset_acp2500_t
 *
 * Implemented by: 
 *      en_r0_woset
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      cfg_inst_compl_int                        :  1;
     unsigned      itask_arrival_int_grp5                    :  1;
     unsigned      itask_arrival_int_grp4                    :  1;
     unsigned      itask_arrival_int_grp3                    :  1;
     unsigned      itask_arrival_int_grp2                    :  1;
     unsigned      itask_arrival_int_grp1                    :  1;
     unsigned      itask_arrival_int_grp0                    :  1;
     unsigned      opcq_complete_int_grp5                    :  1;
     unsigned      opcq_complete_int_grp4                    :  1;
     unsigned      opcq_complete_int_grp3                    :  1;
     unsigned      opcq_complete_int_grp2                    :  1;
     unsigned      opcq_complete_int_grp1                    :  1;
     unsigned      opcq_complete_int_grp0                    :  1;
     unsigned      tpcq_complete_int_grp5                    :  1;
     unsigned      tpcq_complete_int_grp4                    :  1;
     unsigned      tpcq_complete_int_grp3                    :  1;
     unsigned      tpcq_complete_int_grp2                    :  1;
     unsigned      tpcq_complete_int_grp1                    :  1;
     unsigned      tpcq_complete_int_grp0                    :  1;
     unsigned      cpcq_complete_int_grp5                    :  1;
     unsigned      cpcq_complete_int_grp4                    :  1;
     unsigned      cpcq_complete_int_grp3                    :  1;
     unsigned      cpcq_complete_int_grp2                    :  1;
     unsigned      cpcq_complete_int_grp1                    :  1;
     unsigned      cpcq_complete_int_grp0                    :  1;
#else    /* Little Endian */
     unsigned      cpcq_complete_int_grp0                    :  1;
     unsigned      cpcq_complete_int_grp1                    :  1;
     unsigned      cpcq_complete_int_grp2                    :  1;
     unsigned      cpcq_complete_int_grp3                    :  1;
     unsigned      cpcq_complete_int_grp4                    :  1;
     unsigned      cpcq_complete_int_grp5                    :  1;
     unsigned      tpcq_complete_int_grp0                    :  1;
     unsigned      tpcq_complete_int_grp1                    :  1;
     unsigned      tpcq_complete_int_grp2                    :  1;
     unsigned      tpcq_complete_int_grp3                    :  1;
     unsigned      tpcq_complete_int_grp4                    :  1;
     unsigned      tpcq_complete_int_grp5                    :  1;
     unsigned      opcq_complete_int_grp0                    :  1;
     unsigned      opcq_complete_int_grp1                    :  1;
     unsigned      opcq_complete_int_grp2                    :  1;
     unsigned      opcq_complete_int_grp3                    :  1;
     unsigned      opcq_complete_int_grp4                    :  1;
     unsigned      opcq_complete_int_grp5                    :  1;
     unsigned      itask_arrival_int_grp0                    :  1;
     unsigned      itask_arrival_int_grp1                    :  1;
     unsigned      itask_arrival_int_grp2                    :  1;
     unsigned      itask_arrival_int_grp3                    :  1;
     unsigned      itask_arrival_int_grp4                    :  1;
     unsigned      itask_arrival_int_grp5                    :  1;
     unsigned      cfg_inst_compl_int                        :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_nca_en_reg0_woset_acp2500_t;

/*! @struct ncp_nca_en_reg1_woclr_acp2500_t
 *  @brief Interrupt Enable Register
 *  @details This is an alias of grp_interrupt_enable_table.en_r1 which performs write one to clear.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_en_reg1_woclr_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_fifo_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> configuration manager fifo error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_reng_axi_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> configuration manager read engine axi error interrupt
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_data_overflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> output task data overflow interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_data_undeflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> output task data undeflow interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> cnal access error interrupt group5 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> cnal access error interrupt group4 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> cnal access error interrupt group3 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> cnal access error interrupt group2 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> cnal access error interrupt group1 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> cnal access error interrupt group0 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> configuration ring error interrupt group5 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> configuration ring error interrupt group4 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> configuration ring error interrupt group3 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> configuration ring error interrupt group2 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> configuration ring error interrupt group1 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> configuration ring error interrupt group0 Enable </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_en_reg1_woclr_acp2500_t
 *
 * Implemented by: 
 *      en_r1_woclr
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      cmn_fifo_err_int                          :  1;
     unsigned      cmn_reng_axi_err_int                      :  1;
     unsigned      otask_data_overflow_int                   :  1;
     unsigned      otask_data_undeflow_int                   :  1;
     unsigned      eng_cnal_if_int_grp5                      :  1;
     unsigned      eng_cnal_if_int_grp4                      :  1;
     unsigned      eng_cnal_if_int_grp3                      :  1;
     unsigned      eng_cnal_if_int_grp2                      :  1;
     unsigned      eng_cnal_if_int_grp1                      :  1;
     unsigned      eng_cnal_if_int_grp0                      :  1;
     unsigned      cfg_ring_err_int_grp5                     :  1;
     unsigned      cfg_ring_err_int_grp4                     :  1;
     unsigned      cfg_ring_err_int_grp3                     :  1;
     unsigned      cfg_ring_err_int_grp2                     :  1;
     unsigned      cfg_ring_err_int_grp1                     :  1;
     unsigned      cfg_ring_err_int_grp0                     :  1;
#else    /* Little Endian */
     unsigned      cfg_ring_err_int_grp0                     :  1;
     unsigned      cfg_ring_err_int_grp1                     :  1;
     unsigned      cfg_ring_err_int_grp2                     :  1;
     unsigned      cfg_ring_err_int_grp3                     :  1;
     unsigned      cfg_ring_err_int_grp4                     :  1;
     unsigned      cfg_ring_err_int_grp5                     :  1;
     unsigned      eng_cnal_if_int_grp0                      :  1;
     unsigned      eng_cnal_if_int_grp1                      :  1;
     unsigned      eng_cnal_if_int_grp2                      :  1;
     unsigned      eng_cnal_if_int_grp3                      :  1;
     unsigned      eng_cnal_if_int_grp4                      :  1;
     unsigned      eng_cnal_if_int_grp5                      :  1;
     unsigned      otask_data_undeflow_int                   :  1;
     unsigned      otask_data_overflow_int                   :  1;
     unsigned      cmn_reng_axi_err_int                      :  1;
     unsigned      cmn_fifo_err_int                          :  1;
     unsigned      reserved0                                 : 16;
#endif
} ncp_nca_en_reg1_woclr_acp2500_t;

/*! @struct ncp_nca_en_reg1_woset_acp2500_t
 *  @brief Interrupt Enable Register
 *  @details This is an alias of grp_interrupt_enable_table.en_r1 which performs write one to set.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_en_reg1_woset_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_fifo_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> configuration manager fifo error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_reng_axi_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> configuration manager read engine axi error interrupt
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_data_overflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> output task data overflow interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_data_undeflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> output task data undeflow interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> cnal access error interrupt group5 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> cnal access error interrupt group4 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> cnal access error interrupt group3 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> cnal access error interrupt group2 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> cnal access error interrupt group1 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> cnal access error interrupt group0 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> configuration ring error interrupt group5 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> configuration ring error interrupt group4 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> configuration ring error interrupt group3 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> configuration ring error interrupt group2 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> configuration ring error interrupt group1 Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int_grp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> configuration ring error interrupt group0 Enable </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_en_reg1_woset_acp2500_t
 *
 * Implemented by: 
 *      en_r1_woset
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      cmn_fifo_err_int                          :  1;
     unsigned      cmn_reng_axi_err_int                      :  1;
     unsigned      otask_data_overflow_int                   :  1;
     unsigned      otask_data_undeflow_int                   :  1;
     unsigned      eng_cnal_if_int_grp5                      :  1;
     unsigned      eng_cnal_if_int_grp4                      :  1;
     unsigned      eng_cnal_if_int_grp3                      :  1;
     unsigned      eng_cnal_if_int_grp2                      :  1;
     unsigned      eng_cnal_if_int_grp1                      :  1;
     unsigned      eng_cnal_if_int_grp0                      :  1;
     unsigned      cfg_ring_err_int_grp5                     :  1;
     unsigned      cfg_ring_err_int_grp4                     :  1;
     unsigned      cfg_ring_err_int_grp3                     :  1;
     unsigned      cfg_ring_err_int_grp2                     :  1;
     unsigned      cfg_ring_err_int_grp1                     :  1;
     unsigned      cfg_ring_err_int_grp0                     :  1;
#else    /* Little Endian */
     unsigned      cfg_ring_err_int_grp0                     :  1;
     unsigned      cfg_ring_err_int_grp1                     :  1;
     unsigned      cfg_ring_err_int_grp2                     :  1;
     unsigned      cfg_ring_err_int_grp3                     :  1;
     unsigned      cfg_ring_err_int_grp4                     :  1;
     unsigned      cfg_ring_err_int_grp5                     :  1;
     unsigned      eng_cnal_if_int_grp0                      :  1;
     unsigned      eng_cnal_if_int_grp1                      :  1;
     unsigned      eng_cnal_if_int_grp2                      :  1;
     unsigned      eng_cnal_if_int_grp3                      :  1;
     unsigned      eng_cnal_if_int_grp4                      :  1;
     unsigned      eng_cnal_if_int_grp5                      :  1;
     unsigned      otask_data_undeflow_int                   :  1;
     unsigned      otask_data_overflow_int                   :  1;
     unsigned      cmn_reng_axi_err_int                      :  1;
     unsigned      cmn_fifo_err_int                          :  1;
     unsigned      reserved0                                 : 16;
#endif
} ncp_nca_en_reg1_woset_acp2500_t;

/*! @struct ncp_nca_en_reg2_woclr_acp2500_t
 *  @brief Interrupt Enable Register
 *  @details This is an alias of grp_interrupt_enable_table.en_r2 which performs write one to clear.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_en_reg2_woclr_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> CMN fifo overflow/underflow interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> CMN fifo parity error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cow_interrupt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> COW interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param smon_interrupt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> statistics counters interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> task flow completion fifo parity error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> receive buffer pool fifo parity error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> output task accumulator fifo parity error interrupt
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ita_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> input task accumulator fifo parity error interrupt
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> PGIT fifo parity error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo_ecc_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> receive buffer pool ECC interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> task flow completion fifo overflow/underflow interrupt
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> receive buffer pool fifo overflow/underflow interrupt
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> output task accumulator fifo overflow/underflow interrupt
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ita_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> input task accumulator fifo overflow/underflow interrupt
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> PGIT fifo overflow/underflow interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_drop_no_rbuf_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> itask drop no receive buffer available interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_drop_ipcq_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> itask drop iPCQ error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_data_axi_write_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> itask data axi write error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ipcq_entry_axi_write_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> iPCQ entry axi write error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_upload_nca_axi_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> PGIT upload nca axi write error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_load_nca_axi_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> PGIT load nca axi read error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_load_cpu_axi_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> PGIT load cpu axi read error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_drop_entry_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> receive buffer pool drop interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_entry_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> tpcq axi read error Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rpcq_entry_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> rpcq axi read error Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_data_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> otask axi read error Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_entry_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> opcq axi read error Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> eng_cnal_if interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> config ring error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otsd_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> otsd axi read error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_axi_write_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> configuration master node axi write error interrupt
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> cPCQ axi read error interrupt Enable </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_en_reg2_woclr_acp2500_t
 *
 * Implemented by: 
 *      en_r2_woclr
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      cmn_fifo_overflow_underflow_int           :  1;
     unsigned      cmn_fifo_par_err_int                      :  1;
     unsigned      cow_interrupt                             :  1;
     unsigned      smon_interrupt                            :  1;
     unsigned      tfc_fifo_par_err_int                      :  1;
     unsigned      rbp_fifo_par_err_int                      :  1;
     unsigned      ota_fifo_par_err_int                      :  1;
     unsigned      ita_fifo_par_err_int                      :  1;
     unsigned      pgit_fifo_par_err_int                     :  1;
     unsigned      rbp_fifo_ecc_int                          :  1;
     unsigned      tfc_fifo_overflow_underflow_int           :  1;
     unsigned      rbp_fifo_overflow_underflow_int           :  1;
     unsigned      ota_fifo_overflow_underflow_int           :  1;
     unsigned      ita_fifo_overflow_underflow_int           :  1;
     unsigned      pgit_fifo_overflow_underflow_int          :  1;
     unsigned      itask_drop_no_rbuf_er_int                 :  1;
     unsigned      itask_drop_ipcq_er_int                    :  1;
     unsigned      itask_data_axi_write_er_int               :  1;
     unsigned      ipcq_entry_axi_write_er_int               :  1;
     unsigned      pgit_upload_nca_axi_er_int                :  1;
     unsigned      pgit_load_nca_axi_er_int                  :  1;
     unsigned      pgit_load_cpu_axi_er_int                  :  1;
     unsigned      rbp_drop_entry_int                        :  1;
     unsigned      tpcq_entry_axi_read_int                   :  1;
     unsigned      rpcq_entry_axi_read_int                   :  1;
     unsigned      otask_data_axi_read_int                   :  1;
     unsigned      opcq_entry_axi_read_int                   :  1;
     unsigned      eng_cnal_if_int                           :  1;
     unsigned      cfg_ring_err_int                          :  1;
     unsigned      otsd_axi_read_int                         :  1;
     unsigned      cmn_axi_write_int                         :  1;
     unsigned      cpcq_axi_read_int                         :  1;
#else    /* Little Endian */
     unsigned      cpcq_axi_read_int                         :  1;
     unsigned      cmn_axi_write_int                         :  1;
     unsigned      otsd_axi_read_int                         :  1;
     unsigned      cfg_ring_err_int                          :  1;
     unsigned      eng_cnal_if_int                           :  1;
     unsigned      opcq_entry_axi_read_int                   :  1;
     unsigned      otask_data_axi_read_int                   :  1;
     unsigned      rpcq_entry_axi_read_int                   :  1;
     unsigned      tpcq_entry_axi_read_int                   :  1;
     unsigned      rbp_drop_entry_int                        :  1;
     unsigned      pgit_load_cpu_axi_er_int                  :  1;
     unsigned      pgit_load_nca_axi_er_int                  :  1;
     unsigned      pgit_upload_nca_axi_er_int                :  1;
     unsigned      ipcq_entry_axi_write_er_int               :  1;
     unsigned      itask_data_axi_write_er_int               :  1;
     unsigned      itask_drop_ipcq_er_int                    :  1;
     unsigned      itask_drop_no_rbuf_er_int                 :  1;
     unsigned      pgit_fifo_overflow_underflow_int          :  1;
     unsigned      ita_fifo_overflow_underflow_int           :  1;
     unsigned      ota_fifo_overflow_underflow_int           :  1;
     unsigned      rbp_fifo_overflow_underflow_int           :  1;
     unsigned      tfc_fifo_overflow_underflow_int           :  1;
     unsigned      rbp_fifo_ecc_int                          :  1;
     unsigned      pgit_fifo_par_err_int                     :  1;
     unsigned      ita_fifo_par_err_int                      :  1;
     unsigned      ota_fifo_par_err_int                      :  1;
     unsigned      rbp_fifo_par_err_int                      :  1;
     unsigned      tfc_fifo_par_err_int                      :  1;
     unsigned      smon_interrupt                            :  1;
     unsigned      cow_interrupt                             :  1;
     unsigned      cmn_fifo_par_err_int                      :  1;
     unsigned      cmn_fifo_overflow_underflow_int           :  1;
#endif
} ncp_nca_en_reg2_woclr_acp2500_t;

/*! @struct ncp_nca_en_reg2_woset_acp2500_t
 *  @brief Interrupt Enable Register
 *  @details This is an alias of grp_interrupt_enable_table.en_r2 which performs write one to set.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_en_reg2_woset_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> CMN fifo overflow/underflow interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> CMN fifo parity error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cow_interrupt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> COW interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param smon_interrupt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> statistics counters interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> task flow completion fifo parity error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> receive buffer pool fifo parity error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> output task accumulator fifo parity error interrupt
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ita_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> input task accumulator fifo parity error interrupt
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_fifo_par_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> PGIT fifo parity error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo_ecc_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> receive buffer pool ECC interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfc_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> task flow completion fifo overflow/underflow interrupt
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> receive buffer pool fifo overflow/underflow interrupt
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ota_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> output task accumulator fifo overflow/underflow interrupt
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ita_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> input task accumulator fifo overflow/underflow interrupt
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_fifo_overflow_underflow_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> PGIT fifo overflow/underflow interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_drop_no_rbuf_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> itask drop no receive buffer available interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_drop_ipcq_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> itask drop iPCQ error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param itask_data_axi_write_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> itask data axi write error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ipcq_entry_axi_write_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> iPCQ entry axi write error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_upload_nca_axi_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> PGIT upload nca axi write error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_load_nca_axi_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> PGIT load nca axi read error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgit_load_cpu_axi_er_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> PGIT load cpu axi read error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_drop_entry_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> receive buffer pool drop interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpcq_entry_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> tpcq axi read error Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rpcq_entry_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> rpcq axi read error Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otask_data_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> otask axi read error Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opcq_entry_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> opcq axi read error Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eng_cnal_if_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> eng_cnal_if interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_ring_err_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> config ring error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param otsd_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> otsd axi read error interrupt Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmn_axi_write_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> configuration master node axi write error interrupt
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpcq_axi_read_int </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> cPCQ axi read error interrupt Enable </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_en_reg2_woset_acp2500_t
 *
 * Implemented by: 
 *      en_r2_woset
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      cmn_fifo_overflow_underflow_int           :  1;
     unsigned      cmn_fifo_par_err_int                      :  1;
     unsigned      cow_interrupt                             :  1;
     unsigned      smon_interrupt                            :  1;
     unsigned      tfc_fifo_par_err_int                      :  1;
     unsigned      rbp_fifo_par_err_int                      :  1;
     unsigned      ota_fifo_par_err_int                      :  1;
     unsigned      ita_fifo_par_err_int                      :  1;
     unsigned      pgit_fifo_par_err_int                     :  1;
     unsigned      rbp_fifo_ecc_int                          :  1;
     unsigned      tfc_fifo_overflow_underflow_int           :  1;
     unsigned      rbp_fifo_overflow_underflow_int           :  1;
     unsigned      ota_fifo_overflow_underflow_int           :  1;
     unsigned      ita_fifo_overflow_underflow_int           :  1;
     unsigned      pgit_fifo_overflow_underflow_int          :  1;
     unsigned      itask_drop_no_rbuf_er_int                 :  1;
     unsigned      itask_drop_ipcq_er_int                    :  1;
     unsigned      itask_data_axi_write_er_int               :  1;
     unsigned      ipcq_entry_axi_write_er_int               :  1;
     unsigned      pgit_upload_nca_axi_er_int                :  1;
     unsigned      pgit_load_nca_axi_er_int                  :  1;
     unsigned      pgit_load_cpu_axi_er_int                  :  1;
     unsigned      rbp_drop_entry_int                        :  1;
     unsigned      tpcq_entry_axi_read_int                   :  1;
     unsigned      rpcq_entry_axi_read_int                   :  1;
     unsigned      otask_data_axi_read_int                   :  1;
     unsigned      opcq_entry_axi_read_int                   :  1;
     unsigned      eng_cnal_if_int                           :  1;
     unsigned      cfg_ring_err_int                          :  1;
     unsigned      otsd_axi_read_int                         :  1;
     unsigned      cmn_axi_write_int                         :  1;
     unsigned      cpcq_axi_read_int                         :  1;
#else    /* Little Endian */
     unsigned      cpcq_axi_read_int                         :  1;
     unsigned      cmn_axi_write_int                         :  1;
     unsigned      otsd_axi_read_int                         :  1;
     unsigned      cfg_ring_err_int                          :  1;
     unsigned      eng_cnal_if_int                           :  1;
     unsigned      opcq_entry_axi_read_int                   :  1;
     unsigned      otask_data_axi_read_int                   :  1;
     unsigned      rpcq_entry_axi_read_int                   :  1;
     unsigned      tpcq_entry_axi_read_int                   :  1;
     unsigned      rbp_drop_entry_int                        :  1;
     unsigned      pgit_load_cpu_axi_er_int                  :  1;
     unsigned      pgit_load_nca_axi_er_int                  :  1;
     unsigned      pgit_upload_nca_axi_er_int                :  1;
     unsigned      ipcq_entry_axi_write_er_int               :  1;
     unsigned      itask_data_axi_write_er_int               :  1;
     unsigned      itask_drop_ipcq_er_int                    :  1;
     unsigned      itask_drop_no_rbuf_er_int                 :  1;
     unsigned      pgit_fifo_overflow_underflow_int          :  1;
     unsigned      ita_fifo_overflow_underflow_int           :  1;
     unsigned      ota_fifo_overflow_underflow_int           :  1;
     unsigned      rbp_fifo_overflow_underflow_int           :  1;
     unsigned      tfc_fifo_overflow_underflow_int           :  1;
     unsigned      rbp_fifo_ecc_int                          :  1;
     unsigned      pgit_fifo_par_err_int                     :  1;
     unsigned      ita_fifo_par_err_int                      :  1;
     unsigned      ota_fifo_par_err_int                      :  1;
     unsigned      rbp_fifo_par_err_int                      :  1;
     unsigned      tfc_fifo_par_err_int                      :  1;
     unsigned      smon_interrupt                            :  1;
     unsigned      cow_interrupt                             :  1;
     unsigned      cmn_fifo_par_err_int                      :  1;
     unsigned      cmn_fifo_overflow_underflow_int           :  1;
#endif
} ncp_nca_en_reg2_woset_acp2500_t;

/*! @struct ncp_nca_max_outstanding_axim_ops_reg_acp2500_t
 *  @brief Maximum Outstanding AXI Master Operations
 *  @details This register sets the maximum number of outstanding axi master read and write operations allowed for many of the NCA's data types.  The value in each field is set to one less than the desired number of outstanding operations allowed (0 = 1, 1 = 2, 2 = 3, etc.)
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_max_outstanding_axim_ops_reg_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param max_outstanding_am_itask_data_wops </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Maximum number of outstanding input task data write
 *        operations allowed (0 = 1, 1 = 2, 2 = 3, etc.)
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param max_outstanding_am_pgit_wops </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Maximum number of outstanding PCQ group index table
 *        write operations allowed (0 = 1, 1 = 2, 2 = 3, etc.)
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param max_outstanding_am_pgit_rops </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Maximum number of outstanding PCQ group index table
 *        read operations allowed (0 = 1, 1 = 2, 2 = 3, etc.)
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param max_outstanding_am_otask_data_rops </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Maximum number of outstanding output task data read
 *        operations allowed (0 = 1, 1 = 2, 2 = 3, etc.)
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param max_outstanding_am_otsd_rops </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Maximum number of outstanding output task segment
 *        descriptor read operations allowed (0 = 1, 1 = 2,
 *        2 = 3, etc.)
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param max_outstanding_am_opcq_entry_rops </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Maximum number of outstanding oPCQ entry read operations
 *        allowed (0 = 1, 1 = 2, 2 = 3, etc.)
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param max_outstanding_am_tpcq_entry_rops </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Maximum number of outstanding tPCQ entry read operations
 *        allowed (0 = 1, 1 = 2, 2 = 3, etc.)
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param max_outstanding_am_rpcq_entry_rops </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Maximum number of outstanding rPCQ entry read operations
 *        allowed (0 = 1, 1 = 2, 2 = 3, etc.)
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_max_outstanding_axim_ops_reg_acp2500_t
 *
 * Implemented by: 
 *      max_outstanding_axim_ops
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      max_outstanding_am_itask_data_wops        :  4;
     unsigned      reserved0                                 :  1;
     unsigned      max_outstanding_am_pgit_wops              :  3;
     unsigned      reserved1                                 :  1;
     unsigned      max_outstanding_am_pgit_rops              :  3;
     unsigned      max_outstanding_am_otask_data_rops        :  4;
     unsigned      max_outstanding_am_otsd_rops              :  4;
     unsigned      max_outstanding_am_opcq_entry_rops        :  4;
     unsigned      max_outstanding_am_tpcq_entry_rops        :  4;
     unsigned      max_outstanding_am_rpcq_entry_rops        :  4;
#else    /* Little Endian */
     unsigned      max_outstanding_am_rpcq_entry_rops        :  4;
     unsigned      max_outstanding_am_tpcq_entry_rops        :  4;
     unsigned      max_outstanding_am_opcq_entry_rops        :  4;
     unsigned      max_outstanding_am_otsd_rops              :  4;
     unsigned      max_outstanding_am_otask_data_rops        :  4;
     unsigned      max_outstanding_am_pgit_rops              :  3;
     unsigned      reserved1                                 :  1;
     unsigned      max_outstanding_am_pgit_wops              :  3;
     unsigned      reserved0                                 :  1;
     unsigned      max_outstanding_am_itask_data_wops        :  4;
#endif
} ncp_nca_max_outstanding_axim_ops_reg_acp2500_t;

/*! @struct ncp_nca_axim_op_counter_ctl_reg_acp2500_t
 *  @brief AXI Master Operation Counter Control Register
 *  @details Controls the AXI Master Operation Counters
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_axim_op_counter_ctl_reg_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clk_cnt_ovfl </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Indicates when the clock counter has overflowed (1:
 *        Overflow, 0: No overflow).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cnt3_ovfl </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Indicates when AXI master operation counter 3 has
 *        overflowed (1: Overflow, 0: No overflow).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cnt2_ovfl </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Indicates when AXI master operation counter 2 has
 *        overflowed (1: Overflow, 0: No overflow).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cnt1_ovfl </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Indicates when AXI master operation counter 1 has
 *        overflowed (1: Overflow, 0: No overflow).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cnt0_ovfl </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Indicates when AXI master operation counter 0 has
 *        overflowed (1: Overflow, 0: No overflow).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cnt3_sel </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> AXI master operation counter 3 increment select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cnt2_sel </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> AXI master operation counter 2 increment select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cnt1_sel </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> AXI master operation counter 1 increment select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cnt0_sel </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> AXI master operation counter 0 increment select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cnt_lat_mode </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Counter latency mode. Puts the AXI master operation
 *        counters in latency mode, and selects a type of access.
 *        When in latency mode, AXI master operation counter0
 *        contains the minimum latency seen, AXI master operation
 *        counter1 contains the maximum latency seen, AXI
 *        master operation counter2 contains the total latency
 *        seen, and AXI master operation counter3 contains
 *        the number of transactions seen for ID 0 of the selected
 *        type of access.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param spare </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Spare bits. They can be written and read, but are
 *        currently unconnected.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cnt_halt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> If set, halt all AXI master operation counters when
 *        any counter overflows (>2**48-1). Note that the overflow
 *        indication for each counter is available as the *_ovfl
 *        bits of this register
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cnt_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enable all AXI master operation counters (1: run,
 *        0: stop).
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_axim_op_counter_ctl_reg_acp2500_t
 *
 * Implemented by: 
 *      axim_op_counter_ctl
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      clk_cnt_ovfl                              :  1;
     unsigned      cnt3_ovfl                                 :  1;
     unsigned      cnt2_ovfl                                 :  1;
     unsigned      cnt1_ovfl                                 :  1;
     unsigned      cnt0_ovfl                                 :  1;
     unsigned      cnt3_sel                                  :  4;
     unsigned      cnt2_sel                                  :  4;
     unsigned      cnt1_sel                                  :  4;
     unsigned      cnt0_sel                                  :  4;
     unsigned      cnt_lat_mode                              :  4;
     unsigned      spare                                     :  2;
     unsigned      cnt_halt                                  :  1;
     unsigned      cnt_enable                                :  1;
#else    /* Little Endian */
     unsigned      cnt_enable                                :  1;
     unsigned      cnt_halt                                  :  1;
     unsigned      spare                                     :  2;
     unsigned      cnt_lat_mode                              :  4;
     unsigned      cnt0_sel                                  :  4;
     unsigned      cnt1_sel                                  :  4;
     unsigned      cnt2_sel                                  :  4;
     unsigned      cnt3_sel                                  :  4;
     unsigned      cnt0_ovfl                                 :  1;
     unsigned      cnt1_ovfl                                 :  1;
     unsigned      cnt2_ovfl                                 :  1;
     unsigned      cnt3_ovfl                                 :  1;
     unsigned      clk_cnt_ovfl                              :  1;
     unsigned      reserved0                                 :  3;
#endif
} ncp_nca_axim_op_counter_ctl_reg_acp2500_t;

/*! @struct ncp_nca_clk_counter_ls_reg_acp2500_t
 *  @brief Clock Counter LS Register
 *  @details Contains the lower 32 bits of the 48b clock counter value.  It is used by internal logic when the cnt_lat_mode field of the the axim_op_counter_ctl register is selecting a latency mode item.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_clk_counter_ls_reg_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param count_ls </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Current clock count[31:0] </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_clk_counter_ls_reg_acp2500_t
 *
 * Implemented by: 
 *      clk_counter_ls
 */
 
typedef struct
{
     unsigned  int                  count_ls;
} ncp_nca_clk_counter_ls_reg_acp2500_t;

/*! @struct ncp_nca_clk_counter_ms_reg_acp2500_t
 *  @brief Clock Counter MS Register
 *  @details Contains the upper 16 bits of the 48b clock counter value.  It is used by internal logic when the cnt_lat_mode field of the the axim_op_counter_ctl register is selecting a latency mode item.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_clk_counter_ms_reg_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param count_ls </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Current clock count[47:32] </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_clk_counter_ms_reg_acp2500_t
 *
 * Implemented by: 
 *      clk_counter_ms
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      count_ls                                  : 16;
#else    /* Little Endian */
     unsigned      count_ls                                  : 16;
     unsigned      reserved0                                 : 16;
#endif
} ncp_nca_clk_counter_ms_reg_acp2500_t;

/*! @struct ncp_nca_axim_op_counter0_ls_reg_acp2500_t
 *  @brief AXI Master Operation Counter0 LS Register
 *  @details Contains the lower 32 bits of the 48b AXI master operation counter0 value.  Contains the minimum latency seen when the cnt_lat_mode field of the the axim_op_counter_ctl register is selecting a latency mode item.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_axim_op_counter0_ls_reg_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param count_ls </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Current AXI Master Operation Counter0 count[31:0] </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_axim_op_counter0_ls_reg_acp2500_t
 *
 * Implemented by: 
 *      axim_op_counter0_ls
 */
 
typedef struct
{
     unsigned  int                  count_ls;
} ncp_nca_axim_op_counter0_ls_reg_acp2500_t;

/*! @struct ncp_nca_axim_op_counter1_ls_reg_acp2500_t
 *  @brief AXI Master Operation Counter1 LS Register
 *  @details Contains the lower 32 bits of the 48b AXI master operation counter1 value.  Contains the maximum latency seen when the cnt_lat_mode field of the the axim_op_counter_ctl register is selecting a latency mode item.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_axim_op_counter1_ls_reg_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param count_ls </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Current AXI Master Operation Counter1 count[31:0] </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_axim_op_counter1_ls_reg_acp2500_t
 *
 * Implemented by: 
 *      axim_op_counter1_ls
 */
 
typedef struct
{
     unsigned  int                  count_ls;
} ncp_nca_axim_op_counter1_ls_reg_acp2500_t;

/*! @struct ncp_nca_axim_op_counter2_ls_reg_acp2500_t
 *  @brief AXI Master Operation Counter2 LS Register
 *  @details Contains the lower 32 bits of the 48b AXI master operation counter2 value.  Contains the total latency seen when the cnt_lat_mode field of the the axim_op_counter_ctl register is selecting a latency mode item.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_axim_op_counter2_ls_reg_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param count_ls </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Current AXI Master Operation Counter2 count[31:0] </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_axim_op_counter2_ls_reg_acp2500_t
 *
 * Implemented by: 
 *      axim_op_counter2_ls
 */
 
typedef struct
{
     unsigned  int                  count_ls;
} ncp_nca_axim_op_counter2_ls_reg_acp2500_t;

/*! @struct ncp_nca_axim_op_counter3_ls_reg_acp2500_t
 *  @brief AXI Master Operation Counter3 LS Register
 *  @details Contains the lower 32 bits of the 48b AXI master operation counter3 value.  Contains the number of transactions seen for ID 0 of the selected type of access when the cnt_lat_mode field of the the axim_op_counter_ctl register is selecting a latency mode item.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_axim_op_counter3_ls_reg_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param count_ls </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Current AXI Master Operation Counter3 count[31:0] </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_axim_op_counter3_ls_reg_acp2500_t
 *
 * Implemented by: 
 *      axim_op_counter3_ls
 */
 
typedef struct
{
     unsigned  int                  count_ls;
} ncp_nca_axim_op_counter3_ls_reg_acp2500_t;

/*! @struct ncp_nca_axim_op_counter0_ms_reg_acp2500_t
 *  @brief AXI Master Operation Counter0 MS Register
 *  @details Contains the upper 16 bits of the 48b AXI master operation counter0 value.  Contains the minimum latency seen when the cnt_lat_mode field of the the axim_op_counter_ctl register is selecting a latency mode item.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_axim_op_counter0_ms_reg_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param count_ms </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Current AXI Master Operation Counter0 count[47:32] </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_axim_op_counter0_ms_reg_acp2500_t
 *
 * Implemented by: 
 *      axim_op_counter0_ms
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      count_ms                                  : 16;
#else    /* Little Endian */
     unsigned      count_ms                                  : 16;
     unsigned      reserved0                                 : 16;
#endif
} ncp_nca_axim_op_counter0_ms_reg_acp2500_t;

/*! @struct ncp_nca_axim_op_counter1_ms_reg_acp2500_t
 *  @brief AXI Master Operation Counter1 MS Register
 *  @details Contains the upper 16 bits of the 48b AXI master operation counter1 value.  Contains the maximum latency seen when the cnt_lat_mode field of the the axim_op_counter_ctl register is selecting a latency mode item.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_axim_op_counter1_ms_reg_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param count_ms </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Current AXI Master Operation Counter1 count[47:32] </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_axim_op_counter1_ms_reg_acp2500_t
 *
 * Implemented by: 
 *      axim_op_counter1_ms
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      count_ms                                  : 16;
#else    /* Little Endian */
     unsigned      count_ms                                  : 16;
     unsigned      reserved0                                 : 16;
#endif
} ncp_nca_axim_op_counter1_ms_reg_acp2500_t;

/*! @struct ncp_nca_axim_op_counter2_ms_reg_acp2500_t
 *  @brief AXI Master Operation Counter2 MS Register
 *  @details Contains the upper 16 bits of the 48b AXI master operation counter2 value.  Contains the total latency seen when the cnt_lat_mode field of the the axim_op_counter_ctl register is selecting a latency mode item.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_axim_op_counter2_ms_reg_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param count_ms </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Current AXI Master Operation Counter2 count[47:32] </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_axim_op_counter2_ms_reg_acp2500_t
 *
 * Implemented by: 
 *      axim_op_counter2_ms
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      count_ms                                  : 16;
#else    /* Little Endian */
     unsigned      count_ms                                  : 16;
     unsigned      reserved0                                 : 16;
#endif
} ncp_nca_axim_op_counter2_ms_reg_acp2500_t;

/*! @struct ncp_nca_axim_op_counter3_ms_reg_acp2500_t
 *  @brief AXI Master Operation Counter3 MS Register
 *  @details Contains the upper 16 bits of the 48b AXI master operation counter3 value.  Contains the number of transactions seen for ID 0 of the selected type of access when the cnt_lat_mode field of the the axim_op_counter_ctl register is selecting a latency mode item.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_axim_op_counter3_ms_reg_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param count_ms </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Current AXI Master Operation Counter3 count[47:32] </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_axim_op_counter3_ms_reg_acp2500_t
 *
 * Implemented by: 
 *      axim_op_counter3_ms
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      count_ms                                  : 16;
#else    /* Little Endian */
     unsigned      count_ms                                  : 16;
     unsigned      reserved0                                 : 16;
#endif
} ncp_nca_axim_op_counter3_ms_reg_acp2500_t;

/*! @struct ncp_nca_axim_outstanding_rop_count0_reg_acp2500_t
 *  @brief AXI Master Outstanding Read Operation Counter0
 *  @details Contains counts for the number of outstanding AXI master read operations for various data types.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_axim_outstanding_rop_count0_reg_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param outstanding_cmn_rops </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Outstanding configuration master node read operations </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param outstanding_cpcq_rops </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Outstanding cPCQ entry read operations </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param outstanding_tpcq_rops </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Outstanding tPCQ entry read operations </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param outstanding_rpcq_rops </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Outstanding rPCQ entry read operations </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param outstanding_opcq_rops </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Outstanding oPCQ entry read operations </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param outstanding_pgit_rops </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Outstanding PCQ group index table read operations </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param outstanding_otsd_rops </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Outstanding output task segment descriptor read operations </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_axim_outstanding_rop_count0_reg_acp2500_t
 *
 * Implemented by: 
 *      axim_outstanding_rop_count0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      outstanding_cmn_rops                      :  4;
     unsigned      outstanding_cpcq_rops                     :  4;
     unsigned      outstanding_tpcq_rops                     :  5;
     unsigned      outstanding_rpcq_rops                     :  5;
     unsigned      outstanding_opcq_rops                     :  5;
     unsigned      outstanding_pgit_rops                     :  4;
     unsigned      outstanding_otsd_rops                     :  5;
#else    /* Little Endian */
     unsigned      outstanding_otsd_rops                     :  5;
     unsigned      outstanding_pgit_rops                     :  4;
     unsigned      outstanding_opcq_rops                     :  5;
     unsigned      outstanding_rpcq_rops                     :  5;
     unsigned      outstanding_tpcq_rops                     :  5;
     unsigned      outstanding_cpcq_rops                     :  4;
     unsigned      outstanding_cmn_rops                      :  4;
#endif
} ncp_nca_axim_outstanding_rop_count0_reg_acp2500_t;

/*! @struct ncp_nca_axim_outstanding_rop_count1_reg_acp2500_t
 *  @brief AXI Master Outstanding Read Operation Counter1
 *  @details Contains counts for the number of outstanding AXI master read operations for various data types.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_axim_outstanding_rop_count1_reg_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 27 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param outstanding_otask_rops </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Outstanding output task data read operations </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_axim_outstanding_rop_count1_reg_acp2500_t
 *
 * Implemented by: 
 *      axim_outstanding_rop_count1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 27;
     unsigned      outstanding_otask_rops                    :  5;
#else    /* Little Endian */
     unsigned      outstanding_otask_rops                    :  5;
     unsigned      reserved0                                 : 27;
#endif
} ncp_nca_axim_outstanding_rop_count1_reg_acp2500_t;

/*! @struct ncp_nca_axim_outstanding_rop_count2_reg_acp2500_t
 *  @brief AXI Master Outstanding Read Operation Counter2
 *  @details Contains a count for the total number of outstanding AXI master read operations.  It also contains a high water mark field that records the maximum number of outstanding read operations observed.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_axim_outstanding_rop_count2_reg_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param outstanding_total_rops_hwm </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Outstanding total read operations high water mark </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param outstanding_total_rops </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Outstanding total read operations </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_axim_outstanding_rop_count2_reg_acp2500_t
 *
 * Implemented by: 
 *      axim_outstanding_rop_count2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      outstanding_total_rops_hwm                : 16;
     unsigned      outstanding_total_rops                    : 16;
#else    /* Little Endian */
     unsigned      outstanding_total_rops                    : 16;
     unsigned      outstanding_total_rops_hwm                : 16;
#endif
} ncp_nca_axim_outstanding_rop_count2_reg_acp2500_t;

/*! @struct ncp_nca_axim_outstanding_rdata_count0_reg_acp2500_t
 *  @brief AXI Master Outstanding Read Data Counter0
 *  @details Contains counts for the number of outstanding AXI master read data quadwords for various data types.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_axim_outstanding_rdata_count0_reg_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param outstanding_rpcq_rdata </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Outstanding number of read data quadwords for rPCQ
 *        entries
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param outstanding_opcq_rdata </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Outstanding number of read data quadwords for oPCQ
 *        entries
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param outstanding_pgit_rdata </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Outstanding number of read data quadwords for the
 *        PCQ group index table
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param outstanding_otsd_rdata </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Outstanding number of read data quadwords for output
 *        task segment descriptors
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_axim_outstanding_rdata_count0_reg_acp2500_t
 *
 * Implemented by: 
 *      axim_outstanding_rdata_count0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      outstanding_rpcq_rdata                    :  8;
     unsigned      outstanding_opcq_rdata                    :  8;
     unsigned      outstanding_pgit_rdata                    :  8;
     unsigned      outstanding_otsd_rdata                    :  8;
#else    /* Little Endian */
     unsigned      outstanding_otsd_rdata                    :  8;
     unsigned      outstanding_pgit_rdata                    :  8;
     unsigned      outstanding_opcq_rdata                    :  8;
     unsigned      outstanding_rpcq_rdata                    :  8;
#endif
} ncp_nca_axim_outstanding_rdata_count0_reg_acp2500_t;

/*! @struct ncp_nca_axim_outstanding_rdata_count1_reg_acp2500_t
 *  @brief AXI Master Outstanding Read Data Counter1
 *  @details Contains counts for the number of outstanding AXI master read data quadwords for various data types.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_axim_outstanding_rdata_count1_reg_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param outstanding_otask_rdata </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Outstanding number of read data quadwords for output
 *        task data
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param outstanding_cmn_rdata </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Outstanding number of read data quadwords for the
 *        configuration master node
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param outstanding_cpcq_rdata </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Outstanding number of read data quadwords for cPCQ
 *        entries
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param outstanding_tpcq_rdata </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Outstanding number of read data quadwords for tPCQ
 *        entries
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_axim_outstanding_rdata_count1_reg_acp2500_t
 *
 * Implemented by: 
 *      axim_outstanding_rdata_count1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      outstanding_otask_rdata                   :  8;
     unsigned      outstanding_cmn_rdata                     :  8;
     unsigned      outstanding_cpcq_rdata                    :  8;
     unsigned      outstanding_tpcq_rdata                    :  8;
#else    /* Little Endian */
     unsigned      outstanding_tpcq_rdata                    :  8;
     unsigned      outstanding_cpcq_rdata                    :  8;
     unsigned      outstanding_cmn_rdata                     :  8;
     unsigned      outstanding_otask_rdata                   :  8;
#endif
} ncp_nca_axim_outstanding_rdata_count1_reg_acp2500_t;

/*! @struct ncp_nca_axim_outstanding_wop_count0_reg_acp2500_t
 *  @brief AXI Master Outstanding Write Operation Counter0
 *  @details Contains counts for the number of outstanding AXI master write operations for various data types.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_axim_outstanding_wop_count0_reg_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 19 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param outstanding_itask_wops </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Outstanding input task data and iPCQ entry write operations </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param outstanding_cmn_wops </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Outstanding configuration master node write operations </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param outstanding_pgit_wops </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Outstanding PCQ group index table write operations </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_axim_outstanding_wop_count0_reg_acp2500_t
 *
 * Implemented by: 
 *      axim_outstanding_wop_count0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 19;
     unsigned      outstanding_itask_wops                    :  5;
     unsigned      outstanding_cmn_wops                      :  4;
     unsigned      outstanding_pgit_wops                     :  4;
#else    /* Little Endian */
     unsigned      outstanding_pgit_wops                     :  4;
     unsigned      outstanding_cmn_wops                      :  4;
     unsigned      outstanding_itask_wops                    :  5;
     unsigned      reserved0                                 : 19;
#endif
} ncp_nca_axim_outstanding_wop_count0_reg_acp2500_t;

/*! @struct ncp_nca_axim_outstanding_wop_count1_reg_acp2500_t
 *  @brief AXI Master Outstanding Write Operation Counter1
 *  @details Contains a count for the total number of outstanding AXI master write operations.  It also contains a high water mark field that records the maximum number of outstanding write operations observed.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_axim_outstanding_wop_count1_reg_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param outstanding_total_wops_hwm </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Outstanding total write operations high water mark </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param outstanding_total_wops </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Outstanding total write operations </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_axim_outstanding_wop_count1_reg_acp2500_t
 *
 * Implemented by: 
 *      axim_outstanding_wop_count1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      outstanding_total_wops_hwm                : 16;
     unsigned      outstanding_total_wops                    : 16;
#else    /* Little Endian */
     unsigned      outstanding_total_wops                    : 16;
     unsigned      outstanding_total_wops_hwm                : 16;
#endif
} ncp_nca_axim_outstanding_wop_count1_reg_acp2500_t;

/*! @struct ncp_nca_axim_valid_ready_reg_acp2500_t
 *  @brief AXI Master Valid Ready
 *  @details Shows the state of all of the AXI master valid and ready signals
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_axim_valid_ready_reg_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axim_bvalid </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> AXI master write response valid </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axim_bready </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> AXI master write response ready </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axim_wvalid </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> AXI master data write valid </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axim_wready </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> AXI master data write ready </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axim_awvalid </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> AXI master address write valid </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axim_awready </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> AXI master address write ready </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axim_rvalid </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> AXI master data read valid </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axim_rready </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> AXI master data read ready </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axim_arvalid </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> AXI master address read valid </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axim_arready </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> AXI master address read ready </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_axim_valid_ready_reg_acp2500_t
 *
 * Implemented by: 
 *      axim_valid_ready
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 22;
     unsigned      axim_bvalid                               :  1;
     unsigned      axim_bready                               :  1;
     unsigned      axim_wvalid                               :  1;
     unsigned      axim_wready                               :  1;
     unsigned      axim_awvalid                              :  1;
     unsigned      axim_awready                              :  1;
     unsigned      axim_rvalid                               :  1;
     unsigned      axim_rready                               :  1;
     unsigned      axim_arvalid                              :  1;
     unsigned      axim_arready                              :  1;
#else    /* Little Endian */
     unsigned      axim_arready                              :  1;
     unsigned      axim_arvalid                              :  1;
     unsigned      axim_rready                               :  1;
     unsigned      axim_rvalid                               :  1;
     unsigned      axim_awready                              :  1;
     unsigned      axim_awvalid                              :  1;
     unsigned      axim_wready                               :  1;
     unsigned      axim_wvalid                               :  1;
     unsigned      axim_bready                               :  1;
     unsigned      axim_bvalid                               :  1;
     unsigned      reserved0                                 : 22;
#endif
} ncp_nca_axim_valid_ready_reg_acp2500_t;

/*! @struct ncp_nca_rbp_fifo0_range_reg_size0_acp2500_t
 *  @brief Receive Buffer Pool FIFO 0 Range Size0
 *  @details Receive Buffer Pool FIFO 0 start and end range pointers for size 0.  These pointers define the start and end address for receive buffer pool FIFO 0 within the RAM for size0 buffers.  This RAM is 1536 deep.  Writing these pointers sets the FIFO to empty.  It is software's responsibility to set the ranges for all of the FIFOs so that none overlap or are beyond the range of the RAM.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_fifo0_range_reg_size0_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo0_range_start_size0 </td>
 *     <td width="20%" align="center"> 11 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 0 range start pointer for
 *        size0
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo0_range_end_size0 </td>
 *     <td width="20%" align="center"> 11 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 0 range end pointer for size0 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_rbp_fifo0_range_reg_size0_acp2500_t
 *
 * Implemented by: 
 *      rbp_fifo0_range_size0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  5;
     unsigned      rbp_fifo0_range_start_size0               : 11;
     unsigned      reserved1                                 :  5;
     unsigned      rbp_fifo0_range_end_size0                 : 11;
#else    /* Little Endian */
     unsigned      rbp_fifo0_range_end_size0                 : 11;
     unsigned      reserved1                                 :  5;
     unsigned      rbp_fifo0_range_start_size0               : 11;
     unsigned      reserved0                                 :  5;
#endif
} ncp_nca_rbp_fifo0_range_reg_size0_acp2500_t;

/*! @struct ncp_nca_rbp_fifo0_range_reg_size1_acp2500_t
 *  @brief Receive Buffer Pool FIFO 0 Range Size1
 *  @details Receive Buffer Pool FIFO 0 start and end range pointers for size 1.  These pointers define the start and end address for receive buffer pool FIFO 0 within the RAM for size1 buffers.  This RAM is 768 deep.  Writing these pointers sets the FIFO to empty.  It is software's responsibility to set the ranges for all of the FIFOs so that none overlap or are beyond the range of the RAM.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_fifo0_range_reg_size1_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo0_range_start_size1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 0 range start pointer for
 *        size1
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo0_range_end_size1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 0 range end pointer for size1 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_rbp_fifo0_range_reg_size1_acp2500_t
 *
 * Implemented by: 
 *      rbp_fifo0_range_size1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      rbp_fifo0_range_start_size1               : 10;
     unsigned      reserved1                                 :  6;
     unsigned      rbp_fifo0_range_end_size1                 : 10;
#else    /* Little Endian */
     unsigned      rbp_fifo0_range_end_size1                 : 10;
     unsigned      reserved1                                 :  6;
     unsigned      rbp_fifo0_range_start_size1               : 10;
     unsigned      reserved0                                 :  6;
#endif
} ncp_nca_rbp_fifo0_range_reg_size1_acp2500_t;

/*! @struct ncp_nca_rbp_fifo0_range_reg_size2_acp2500_t
 *  @brief Receive Buffer Pool FIFO 0 Range Size2
 *  @details Receive Buffer Pool FIFO 0 start and end range pointers for size 2.  These pointers define the start and end address for receive buffer pool FIFO 0 within the RAM for size2 buffers.  This RAM is 384 deep.  Writing these pointers sets the FIFO to empty.  It is software's responsibility to set the ranges for all of the FIFOs so that none overlap or are beyond the range of the RAM.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_fifo0_range_reg_size2_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo0_range_start_size2 </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 0 range start pointer for
 *        size2
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo0_range_end_size2 </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 0 range end pointer for size2 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_rbp_fifo0_range_reg_size2_acp2500_t
 *
 * Implemented by: 
 *      rbp_fifo0_range_size2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      rbp_fifo0_range_start_size2               :  9;
     unsigned      reserved1                                 :  7;
     unsigned      rbp_fifo0_range_end_size2                 :  9;
#else    /* Little Endian */
     unsigned      rbp_fifo0_range_end_size2                 :  9;
     unsigned      reserved1                                 :  7;
     unsigned      rbp_fifo0_range_start_size2               :  9;
     unsigned      reserved0                                 :  7;
#endif
} ncp_nca_rbp_fifo0_range_reg_size2_acp2500_t;

/*! @struct ncp_nca_rbp_fifo0_range_reg_size3_acp2500_t
 *  @brief Receive Buffer Pool FIFO 0 Range Size3
 *  @details Receive Buffer Pool FIFO 0 start and end range pointers for size 3.  These pointers define the start and end address for receive buffer pool FIFO 0 within the RAM for size3 buffers.  This RAM is 192 deep.  Writing these pointers sets the FIFO to empty.  It is software's responsibility to set the ranges for all of the FIFOs so that none overlap or are beyond the range of the RAM.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_fifo0_range_reg_size3_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo0_range_start_size3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 0 range start pointer for
 *        size3
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo0_range_end_size3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 0 range end pointer for size3 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_rbp_fifo0_range_reg_size3_acp2500_t
 *
 * Implemented by: 
 *      rbp_fifo0_range_size3
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  8;
     unsigned      rbp_fifo0_range_start_size3               :  8;
     unsigned      reserved1                                 :  8;
     unsigned      rbp_fifo0_range_end_size3                 :  8;
#else    /* Little Endian */
     unsigned      rbp_fifo0_range_end_size3                 :  8;
     unsigned      reserved1                                 :  8;
     unsigned      rbp_fifo0_range_start_size3               :  8;
     unsigned      reserved0                                 :  8;
#endif
} ncp_nca_rbp_fifo0_range_reg_size3_acp2500_t;

/*! @struct ncp_nca_rbp_fifo1_range_reg_size0_acp2500_t
 *  @brief Receive Buffer Pool FIFO 1 Range Size0
 *  @details Receive Buffer Pool FIFO 1 start and end range pointers for size 0.  These pointers define the start and end address for receive buffer pool FIFO 1 within the RAM for size0 buffers.  This RAM is 1536 deep.  Writing these pointers sets the FIFO to empty.  It is software's responsibility to set the ranges for all of the FIFOs so that none overlap or are beyond the range of the RAM.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_fifo1_range_reg_size0_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo1_range_start_size0 </td>
 *     <td width="20%" align="center"> 11 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 1 range start pointer for
 *        size0
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo1_range_end_size0 </td>
 *     <td width="20%" align="center"> 11 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 1 range end pointer for size0 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_rbp_fifo1_range_reg_size0_acp2500_t
 *
 * Implemented by: 
 *      rbp_fifo1_range_size0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  5;
     unsigned      rbp_fifo1_range_start_size0               : 11;
     unsigned      reserved1                                 :  5;
     unsigned      rbp_fifo1_range_end_size0                 : 11;
#else    /* Little Endian */
     unsigned      rbp_fifo1_range_end_size0                 : 11;
     unsigned      reserved1                                 :  5;
     unsigned      rbp_fifo1_range_start_size0               : 11;
     unsigned      reserved0                                 :  5;
#endif
} ncp_nca_rbp_fifo1_range_reg_size0_acp2500_t;

/*! @struct ncp_nca_rbp_fifo1_range_reg_size1_acp2500_t
 *  @brief Receive Buffer Pool FIFO 1 Range Size1
 *  @details Receive Buffer Pool FIFO 1 start and end range pointers for size 1.  These pointers define the start and end address for receive buffer pool FIFO 1 within the RAM for size1 buffers.  This RAM is 768 deep.  Writing these pointers sets the FIFO to empty.  It is software's responsibility to set the ranges for all of the FIFOs so that none overlap or are beyond the range of the RAM.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_fifo1_range_reg_size1_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo1_range_start_size1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 1 range start pointer for
 *        size1
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo1_range_end_size1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 1 range end pointer for size1 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_rbp_fifo1_range_reg_size1_acp2500_t
 *
 * Implemented by: 
 *      rbp_fifo1_range_size1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      rbp_fifo1_range_start_size1               : 10;
     unsigned      reserved1                                 :  6;
     unsigned      rbp_fifo1_range_end_size1                 : 10;
#else    /* Little Endian */
     unsigned      rbp_fifo1_range_end_size1                 : 10;
     unsigned      reserved1                                 :  6;
     unsigned      rbp_fifo1_range_start_size1               : 10;
     unsigned      reserved0                                 :  6;
#endif
} ncp_nca_rbp_fifo1_range_reg_size1_acp2500_t;

/*! @struct ncp_nca_rbp_fifo1_range_reg_size2_acp2500_t
 *  @brief Receive Buffer Pool FIFO 1 Range Size2
 *  @details Receive Buffer Pool FIFO 1 start and end range pointers for size 2.  These pointers define the start and end address for receive buffer pool FIFO 1 within the RAM for size2 buffers.  This RAM is 384 deep.  Writing these pointers sets the FIFO to empty.  It is software's responsibility to set the ranges for all of the FIFOs so that none overlap or are beyond the range of the RAM.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_fifo1_range_reg_size2_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo1_range_start_size2 </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 1 range start pointer for
 *        size2
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo1_range_end_size2 </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 1 range end pointer for size2 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_rbp_fifo1_range_reg_size2_acp2500_t
 *
 * Implemented by: 
 *      rbp_fifo1_range_size2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      rbp_fifo1_range_start_size2               :  9;
     unsigned      reserved1                                 :  7;
     unsigned      rbp_fifo1_range_end_size2                 :  9;
#else    /* Little Endian */
     unsigned      rbp_fifo1_range_end_size2                 :  9;
     unsigned      reserved1                                 :  7;
     unsigned      rbp_fifo1_range_start_size2               :  9;
     unsigned      reserved0                                 :  7;
#endif
} ncp_nca_rbp_fifo1_range_reg_size2_acp2500_t;

/*! @struct ncp_nca_rbp_fifo1_range_reg_size3_acp2500_t
 *  @brief Receive Buffer Pool FIFO 1 Range Size3
 *  @details Receive Buffer Pool FIFO 1 start and end range pointers for size 3.  These pointers define the start and end address for receive buffer pool FIFO 1 within the RAM for size3 buffers.  This RAM is 192 deep.  Writing these pointers sets the FIFO to empty.  It is software's responsibility to set the ranges for all of the FIFOs so that none overlap or are beyond the range of the RAM.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_fifo1_range_reg_size3_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo1_range_start_size3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 1 range start pointer for
 *        size3
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo1_range_end_size3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 1 range end pointer for size3 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_rbp_fifo1_range_reg_size3_acp2500_t
 *
 * Implemented by: 
 *      rbp_fifo1_range_size3
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  8;
     unsigned      rbp_fifo1_range_start_size3               :  8;
     unsigned      reserved1                                 :  8;
     unsigned      rbp_fifo1_range_end_size3                 :  8;
#else    /* Little Endian */
     unsigned      rbp_fifo1_range_end_size3                 :  8;
     unsigned      reserved1                                 :  8;
     unsigned      rbp_fifo1_range_start_size3               :  8;
     unsigned      reserved0                                 :  8;
#endif
} ncp_nca_rbp_fifo1_range_reg_size3_acp2500_t;

/*! @struct ncp_nca_rbp_fifo2_range_reg_size0_acp2500_t
 *  @brief Receive Buffer Pool FIFO 2 Range Size0
 *  @details Receive Buffer Pool FIFO 2 start and end range pointers for size 0.  These pointers define the start and end address for receive buffer pool FIFO 2 within the RAM for size0 buffers.  This RAM is 1536 deep.  Writing these pointers sets the FIFO to empty.  It is software's responsibility to set the ranges for all of the FIFOs so that none overlap or are beyond the range of the RAM.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_fifo2_range_reg_size0_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo2_range_start_size0 </td>
 *     <td width="20%" align="center"> 11 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 2 range start pointer for
 *        size0
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo2_range_end_size0 </td>
 *     <td width="20%" align="center"> 11 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 2 range end pointer for size0 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_rbp_fifo2_range_reg_size0_acp2500_t
 *
 * Implemented by: 
 *      rbp_fifo2_range_size0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  5;
     unsigned      rbp_fifo2_range_start_size0               : 11;
     unsigned      reserved1                                 :  5;
     unsigned      rbp_fifo2_range_end_size0                 : 11;
#else    /* Little Endian */
     unsigned      rbp_fifo2_range_end_size0                 : 11;
     unsigned      reserved1                                 :  5;
     unsigned      rbp_fifo2_range_start_size0               : 11;
     unsigned      reserved0                                 :  5;
#endif
} ncp_nca_rbp_fifo2_range_reg_size0_acp2500_t;

/*! @struct ncp_nca_rbp_fifo2_range_reg_size1_acp2500_t
 *  @brief Receive Buffer Pool FIFO 2 Range Size1
 *  @details Receive Buffer Pool FIFO 2 start and end range pointers for size 1.  These pointers define the start and end address for receive buffer pool FIFO 2 within the RAM for size1 buffers.  This RAM is 768 deep.  Writing these pointers sets the FIFO to empty.  It is software's responsibility to set the ranges for all of the FIFOs so that none overlap or are beyond the range of the RAM.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_fifo2_range_reg_size1_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo2_range_start_size1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 2 range start pointer for
 *        size1
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo2_range_end_size1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 2 range end pointer for size1 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_rbp_fifo2_range_reg_size1_acp2500_t
 *
 * Implemented by: 
 *      rbp_fifo2_range_size1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      rbp_fifo2_range_start_size1               : 10;
     unsigned      reserved1                                 :  6;
     unsigned      rbp_fifo2_range_end_size1                 : 10;
#else    /* Little Endian */
     unsigned      rbp_fifo2_range_end_size1                 : 10;
     unsigned      reserved1                                 :  6;
     unsigned      rbp_fifo2_range_start_size1               : 10;
     unsigned      reserved0                                 :  6;
#endif
} ncp_nca_rbp_fifo2_range_reg_size1_acp2500_t;

/*! @struct ncp_nca_rbp_fifo2_range_reg_size2_acp2500_t
 *  @brief Receive Buffer Pool FIFO 2 Range Size2
 *  @details Receive Buffer Pool FIFO 2 start and end range pointers for size 2.  These pointers define the start and end address for receive buffer pool FIFO 2 within the RAM for size2 buffers.  This RAM is 384 deep.  Writing these pointers sets the FIFO to empty.  It is software's responsibility to set the ranges for all of the FIFOs so that none overlap or are beyond the range of the RAM.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_fifo2_range_reg_size2_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo2_range_start_size2 </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 2 range start pointer for
 *        size2
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo2_range_end_size2 </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 2 range end pointer for size2 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_rbp_fifo2_range_reg_size2_acp2500_t
 *
 * Implemented by: 
 *      rbp_fifo2_range_size2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      rbp_fifo2_range_start_size2               :  9;
     unsigned      reserved1                                 :  7;
     unsigned      rbp_fifo2_range_end_size2                 :  9;
#else    /* Little Endian */
     unsigned      rbp_fifo2_range_end_size2                 :  9;
     unsigned      reserved1                                 :  7;
     unsigned      rbp_fifo2_range_start_size2               :  9;
     unsigned      reserved0                                 :  7;
#endif
} ncp_nca_rbp_fifo2_range_reg_size2_acp2500_t;

/*! @struct ncp_nca_rbp_fifo2_range_reg_size3_acp2500_t
 *  @brief Receive Buffer Pool FIFO 2 Range Size3
 *  @details Receive Buffer Pool FIFO 2 start and end range pointers for size 3.  These pointers define the start and end address for receive buffer pool FIFO 2 within the RAM for size3 buffers.  This RAM is 192 deep.  Writing these pointers sets the FIFO to empty.  It is software's responsibility to set the ranges for all of the FIFOs so that none overlap or are beyond the range of the RAM.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_fifo2_range_reg_size3_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo2_range_start_size3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 2 range start pointer for
 *        size3
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo2_range_end_size3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 2 range end pointer for size3 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_rbp_fifo2_range_reg_size3_acp2500_t
 *
 * Implemented by: 
 *      rbp_fifo2_range_size3
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  8;
     unsigned      rbp_fifo2_range_start_size3               :  8;
     unsigned      reserved1                                 :  8;
     unsigned      rbp_fifo2_range_end_size3                 :  8;
#else    /* Little Endian */
     unsigned      rbp_fifo2_range_end_size3                 :  8;
     unsigned      reserved1                                 :  8;
     unsigned      rbp_fifo2_range_start_size3               :  8;
     unsigned      reserved0                                 :  8;
#endif
} ncp_nca_rbp_fifo2_range_reg_size3_acp2500_t;

/*! @struct ncp_nca_rbp_fifo3_range_reg_size0_acp2500_t
 *  @brief Receive Buffer Pool FIFO 3 Range Size0
 *  @details Receive Buffer Pool FIFO 3 start and end range pointers for size 0.  These pointers define the start and end address for receive buffer pool FIFO 3 within the RAM for size0 buffers.  This RAM is 1536 deep.  Writing these pointers sets the FIFO to empty.  It is software's responsibility to set the ranges for all of the FIFOs so that none overlap or are beyond the range of the RAM.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_fifo3_range_reg_size0_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo3_range_start_size0 </td>
 *     <td width="20%" align="center"> 11 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 3 range start pointer for
 *        size0
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo3_range_end_size0 </td>
 *     <td width="20%" align="center"> 11 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 3 range end pointer for size0 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_rbp_fifo3_range_reg_size0_acp2500_t
 *
 * Implemented by: 
 *      rbp_fifo3_range_size0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  5;
     unsigned      rbp_fifo3_range_start_size0               : 11;
     unsigned      reserved1                                 :  5;
     unsigned      rbp_fifo3_range_end_size0                 : 11;
#else    /* Little Endian */
     unsigned      rbp_fifo3_range_end_size0                 : 11;
     unsigned      reserved1                                 :  5;
     unsigned      rbp_fifo3_range_start_size0               : 11;
     unsigned      reserved0                                 :  5;
#endif
} ncp_nca_rbp_fifo3_range_reg_size0_acp2500_t;

/*! @struct ncp_nca_rbp_fifo3_range_reg_size1_acp2500_t
 *  @brief Receive Buffer Pool FIFO 3 Range Size1
 *  @details Receive Buffer Pool FIFO 3 start and end range pointers for size 1.  These pointers define the start and end address for receive buffer pool FIFO 3 within the RAM for size1 buffers.  This RAM is 768 deep.  Writing these pointers sets the FIFO to empty.  It is software's responsibility to set the ranges for all of the FIFOs so that none overlap or are beyond the range of the RAM.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_fifo3_range_reg_size1_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo3_range_start_size1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 3 range start pointer for
 *        size1
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo3_range_end_size1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 3 range end pointer for size1 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_rbp_fifo3_range_reg_size1_acp2500_t
 *
 * Implemented by: 
 *      rbp_fifo3_range_size1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      rbp_fifo3_range_start_size1               : 10;
     unsigned      reserved1                                 :  6;
     unsigned      rbp_fifo3_range_end_size1                 : 10;
#else    /* Little Endian */
     unsigned      rbp_fifo3_range_end_size1                 : 10;
     unsigned      reserved1                                 :  6;
     unsigned      rbp_fifo3_range_start_size1               : 10;
     unsigned      reserved0                                 :  6;
#endif
} ncp_nca_rbp_fifo3_range_reg_size1_acp2500_t;

/*! @struct ncp_nca_rbp_fifo3_range_reg_size2_acp2500_t
 *  @brief Receive Buffer Pool FIFO 3 Range Size2
 *  @details Receive Buffer Pool FIFO 3 start and end range pointers for size 2.  These pointers define the start and end address for receive buffer pool FIFO 3 within the RAM for size2 buffers.  This RAM is 384 deep.  Writing these pointers sets the FIFO to empty.  It is software's responsibility to set the ranges for all of the FIFOs so that none overlap or are beyond the range of the RAM.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_fifo3_range_reg_size2_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo3_range_start_size2 </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 3 range start pointer for
 *        size2
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo3_range_end_size2 </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 3 range end pointer for size2 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_rbp_fifo3_range_reg_size2_acp2500_t
 *
 * Implemented by: 
 *      rbp_fifo3_range_size2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      rbp_fifo3_range_start_size2               :  9;
     unsigned      reserved1                                 :  7;
     unsigned      rbp_fifo3_range_end_size2                 :  9;
#else    /* Little Endian */
     unsigned      rbp_fifo3_range_end_size2                 :  9;
     unsigned      reserved1                                 :  7;
     unsigned      rbp_fifo3_range_start_size2               :  9;
     unsigned      reserved0                                 :  7;
#endif
} ncp_nca_rbp_fifo3_range_reg_size2_acp2500_t;

/*! @struct ncp_nca_rbp_fifo3_range_reg_size3_acp2500_t
 *  @brief Receive Buffer Pool FIFO 3 Range Size3
 *  @details Receive Buffer Pool FIFO 3 start and end range pointers for size 3.  These pointers define the start and end address for receive buffer pool FIFO 3 within the RAM for size3 buffers.  This RAM is 192 deep.  Writing these pointers sets the FIFO to empty.  It is software's responsibility to set the ranges for all of the FIFOs so that none overlap or are beyond the range of the RAM.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_fifo3_range_reg_size3_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo3_range_start_size3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 3 range start pointer for
 *        size3
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo3_range_end_size3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 3 range end pointer for size3 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_rbp_fifo3_range_reg_size3_acp2500_t
 *
 * Implemented by: 
 *      rbp_fifo3_range_size3
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  8;
     unsigned      rbp_fifo3_range_start_size3               :  8;
     unsigned      reserved1                                 :  8;
     unsigned      rbp_fifo3_range_end_size3                 :  8;
#else    /* Little Endian */
     unsigned      rbp_fifo3_range_end_size3                 :  8;
     unsigned      reserved1                                 :  8;
     unsigned      rbp_fifo3_range_start_size3               :  8;
     unsigned      reserved0                                 :  8;
#endif
} ncp_nca_rbp_fifo3_range_reg_size3_acp2500_t;

/*! @struct ncp_nca_rbp_fifo4_range_reg_size0_acp2500_t
 *  @brief Receive Buffer Pool FIFO 4 Range Size0
 *  @details Receive Buffer Pool FIFO 4 start and end range pointers for size 0.  These pointers define the start and end address for receive buffer pool FIFO 4 within the RAM for size0 buffers.  This RAM is 1536 deep.  Writing these pointers sets the FIFO to empty.  It is software's responsibility to set the ranges for all of the FIFOs so that none overlap or are beyond the range of the RAM.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_fifo4_range_reg_size0_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo4_range_start_size0 </td>
 *     <td width="20%" align="center"> 11 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 4 range start pointer for
 *        size0
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo4_range_end_size0 </td>
 *     <td width="20%" align="center"> 11 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 4 range end pointer for size0 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_rbp_fifo4_range_reg_size0_acp2500_t
 *
 * Implemented by: 
 *      rbp_fifo4_range_size0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  5;
     unsigned      rbp_fifo4_range_start_size0               : 11;
     unsigned      reserved1                                 :  5;
     unsigned      rbp_fifo4_range_end_size0                 : 11;
#else    /* Little Endian */
     unsigned      rbp_fifo4_range_end_size0                 : 11;
     unsigned      reserved1                                 :  5;
     unsigned      rbp_fifo4_range_start_size0               : 11;
     unsigned      reserved0                                 :  5;
#endif
} ncp_nca_rbp_fifo4_range_reg_size0_acp2500_t;

/*! @struct ncp_nca_rbp_fifo4_range_reg_size1_acp2500_t
 *  @brief Receive Buffer Pool FIFO 4 Range Size1
 *  @details Receive Buffer Pool FIFO 4 start and end range pointers for size 1.  These pointers define the start and end address for receive buffer pool FIFO 4 within the RAM for size1 buffers.  This RAM is 768 deep.  Writing these pointers sets the FIFO to empty.  It is software's responsibility to set the ranges for all of the FIFOs so that none overlap or are beyond the range of the RAM.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_fifo4_range_reg_size1_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo4_range_start_size1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 4 range start pointer for
 *        size1
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo4_range_end_size1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 4 range end pointer for size1 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_rbp_fifo4_range_reg_size1_acp2500_t
 *
 * Implemented by: 
 *      rbp_fifo4_range_size1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      rbp_fifo4_range_start_size1               : 10;
     unsigned      reserved1                                 :  6;
     unsigned      rbp_fifo4_range_end_size1                 : 10;
#else    /* Little Endian */
     unsigned      rbp_fifo4_range_end_size1                 : 10;
     unsigned      reserved1                                 :  6;
     unsigned      rbp_fifo4_range_start_size1               : 10;
     unsigned      reserved0                                 :  6;
#endif
} ncp_nca_rbp_fifo4_range_reg_size1_acp2500_t;

/*! @struct ncp_nca_rbp_fifo4_range_reg_size2_acp2500_t
 *  @brief Receive Buffer Pool FIFO 4 Range Size2
 *  @details Receive Buffer Pool FIFO 4 start and end range pointers for size 2.  These pointers define the start and end address for receive buffer pool FIFO 4 within the RAM for size2 buffers.  This RAM is 384 deep.  Writing these pointers sets the FIFO to empty.  It is software's responsibility to set the ranges for all of the FIFOs so that none overlap or are beyond the range of the RAM.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_fifo4_range_reg_size2_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo4_range_start_size2 </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 4 range start pointer for
 *        size2
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo4_range_end_size2 </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 4 range end pointer for size2 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_rbp_fifo4_range_reg_size2_acp2500_t
 *
 * Implemented by: 
 *      rbp_fifo4_range_size2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      rbp_fifo4_range_start_size2               :  9;
     unsigned      reserved1                                 :  7;
     unsigned      rbp_fifo4_range_end_size2                 :  9;
#else    /* Little Endian */
     unsigned      rbp_fifo4_range_end_size2                 :  9;
     unsigned      reserved1                                 :  7;
     unsigned      rbp_fifo4_range_start_size2               :  9;
     unsigned      reserved0                                 :  7;
#endif
} ncp_nca_rbp_fifo4_range_reg_size2_acp2500_t;

/*! @struct ncp_nca_rbp_fifo4_range_reg_size3_acp2500_t
 *  @brief Receive Buffer Pool FIFO 4 Range Size3
 *  @details Receive Buffer Pool FIFO 4 start and end range pointers for size 3.  These pointers define the start and end address for receive buffer pool FIFO 4 within the RAM for size3 buffers.  This RAM is 192 deep.  Writing these pointers sets the FIFO to empty.  It is software's responsibility to set the ranges for all of the FIFOs so that none overlap or are beyond the range of the RAM.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_fifo4_range_reg_size3_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo4_range_start_size3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 4 range start pointer for
 *        size3
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo4_range_end_size3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 4 range end pointer for size3 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_rbp_fifo4_range_reg_size3_acp2500_t
 *
 * Implemented by: 
 *      rbp_fifo4_range_size3
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  8;
     unsigned      rbp_fifo4_range_start_size3               :  8;
     unsigned      reserved1                                 :  8;
     unsigned      rbp_fifo4_range_end_size3                 :  8;
#else    /* Little Endian */
     unsigned      rbp_fifo4_range_end_size3                 :  8;
     unsigned      reserved1                                 :  8;
     unsigned      rbp_fifo4_range_start_size3               :  8;
     unsigned      reserved0                                 :  8;
#endif
} ncp_nca_rbp_fifo4_range_reg_size3_acp2500_t;

/*! @struct ncp_nca_rbp_fifo5_range_reg_size0_acp2500_t
 *  @brief Receive Buffer Pool FIFO 5 Range Size0
 *  @details Receive Buffer Pool FIFO 5 start and end range pointers for size 0.  These pointers define the start and end address for receive buffer pool FIFO 5 within the RAM for size0 buffers.  This RAM is 1536 deep.  Writing these pointers sets the FIFO to empty.  It is software's responsibility to set the ranges for all of the FIFOs so that none overlap or are beyond the range of the RAM.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_fifo5_range_reg_size0_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo5_range_start_size0 </td>
 *     <td width="20%" align="center"> 11 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 5 range start pointer for
 *        size0
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo5_range_end_size0 </td>
 *     <td width="20%" align="center"> 11 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 5 range end pointer for size0 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_rbp_fifo5_range_reg_size0_acp2500_t
 *
 * Implemented by: 
 *      rbp_fifo5_range_size0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  5;
     unsigned      rbp_fifo5_range_start_size0               : 11;
     unsigned      reserved1                                 :  5;
     unsigned      rbp_fifo5_range_end_size0                 : 11;
#else    /* Little Endian */
     unsigned      rbp_fifo5_range_end_size0                 : 11;
     unsigned      reserved1                                 :  5;
     unsigned      rbp_fifo5_range_start_size0               : 11;
     unsigned      reserved0                                 :  5;
#endif
} ncp_nca_rbp_fifo5_range_reg_size0_acp2500_t;

/*! @struct ncp_nca_rbp_fifo5_range_reg_size1_acp2500_t
 *  @brief Receive Buffer Pool FIFO 5 Range Size1
 *  @details Receive Buffer Pool FIFO 5 start and end range pointers for size 1.  These pointers define the start and end address for receive buffer pool FIFO 5 within the RAM for size1 buffers.  This RAM is 768 deep.  Writing these pointers sets the FIFO to empty.  It is software's responsibility to set the ranges for all of the FIFOs so that none overlap or are beyond the range of the RAM.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_fifo5_range_reg_size1_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo5_range_start_size1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 5 range start pointer for
 *        size1
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo5_range_end_size1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 5 range end pointer for size1 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_rbp_fifo5_range_reg_size1_acp2500_t
 *
 * Implemented by: 
 *      rbp_fifo5_range_size1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      rbp_fifo5_range_start_size1               : 10;
     unsigned      reserved1                                 :  6;
     unsigned      rbp_fifo5_range_end_size1                 : 10;
#else    /* Little Endian */
     unsigned      rbp_fifo5_range_end_size1                 : 10;
     unsigned      reserved1                                 :  6;
     unsigned      rbp_fifo5_range_start_size1               : 10;
     unsigned      reserved0                                 :  6;
#endif
} ncp_nca_rbp_fifo5_range_reg_size1_acp2500_t;

/*! @struct ncp_nca_rbp_fifo5_range_reg_size2_acp2500_t
 *  @brief Receive Buffer Pool FIFO 5 Range Size2
 *  @details Receive Buffer Pool FIFO 5 start and end range pointers for size 2.  These pointers define the start and end address for receive buffer pool FIFO 5 within the RAM for size2 buffers.  This RAM is 384 deep.  Writing these pointers sets the FIFO to empty.  It is software's responsibility to set the ranges for all of the FIFOs so that none overlap or are beyond the range of the RAM.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_fifo5_range_reg_size2_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo5_range_start_size2 </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 5 range start pointer for
 *        size2
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo5_range_end_size2 </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 5 range end pointer for size2 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_rbp_fifo5_range_reg_size2_acp2500_t
 *
 * Implemented by: 
 *      rbp_fifo5_range_size2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      rbp_fifo5_range_start_size2               :  9;
     unsigned      reserved1                                 :  7;
     unsigned      rbp_fifo5_range_end_size2                 :  9;
#else    /* Little Endian */
     unsigned      rbp_fifo5_range_end_size2                 :  9;
     unsigned      reserved1                                 :  7;
     unsigned      rbp_fifo5_range_start_size2               :  9;
     unsigned      reserved0                                 :  7;
#endif
} ncp_nca_rbp_fifo5_range_reg_size2_acp2500_t;

/*! @struct ncp_nca_rbp_fifo5_range_reg_size3_acp2500_t
 *  @brief Receive Buffer Pool FIFO 5 Range Size3
 *  @details Receive Buffer Pool FIFO 5 start and end range pointers for size 3.  These pointers define the start and end address for receive buffer pool FIFO 5 within the RAM for size3 buffers.  This RAM is 192 deep.  Writing these pointers sets the FIFO to empty.  It is software's responsibility to set the ranges for all of the FIFOs so that none overlap or are beyond the range of the RAM.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_nca_rbp_fifo5_range_reg_size3_acp2500_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo5_range_start_size3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 5 range start pointer for
 *        size3
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rbp_fifo5_range_end_size3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Receive Buffer Pool FIFO 5 range end pointer for size3 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_nca_rbp_fifo5_range_reg_size3_acp2500_t
 *
 * Implemented by: 
 *      rbp_fifo5_range_size3
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  8;
     unsigned      rbp_fifo5_range_start_size3               :  8;
     unsigned      reserved1                                 :  8;
     unsigned      rbp_fifo5_range_end_size3                 :  8;
#else    /* Little Endian */
     unsigned      rbp_fifo5_range_end_size3                 :  8;
     unsigned      reserved1                                 :  8;
     unsigned      rbp_fifo5_range_start_size3               :  8;
     unsigned      reserved0                                 :  8;
#endif
} ncp_nca_rbp_fifo5_range_reg_size3_acp2500_t;

#ifdef __cplusplus
}
#endif

#endif /* _NCP_NCA_REGS_H_ */
