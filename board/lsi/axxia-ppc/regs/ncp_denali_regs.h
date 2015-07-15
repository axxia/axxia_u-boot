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

#ifndef _NCP_DENALI_REGS_H_
#define _NCP_DENALI_REGS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*! @struct ncp_denali_DENALI_CTL_00_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_00_t\n
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
 *     <td width="30%"> @param arefresh </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Trigger auto-refresh at boundary specified by AUTO_REFRESH_MODE.
 *        WRITE-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ap </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enable auto pre-charge mode of controller. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param addr_cmp_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enable address collision detection for cmd queue placement
 *        logic.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param active_aging </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enable command aging in the command queue. </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_00
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      arefresh                                  :  1;
     unsigned      reserved1                                 :  7;
     unsigned      ap                                        :  1;
     unsigned      reserved2                                 :  7;
     unsigned      addr_cmp_en                               :  1;
     unsigned      reserved3                                 :  7;
     unsigned      active_aging                              :  1;
#else    /* Little Endian */
     unsigned      active_aging                              :  1;
     unsigned      reserved3                                 :  7;
     unsigned      addr_cmp_en                               :  1;
     unsigned      reserved2                                 :  7;
     unsigned      ap                                        :  1;
     unsigned      reserved1                                 :  7;
     unsigned      arefresh                                  :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_00_t;

/*! @struct ncp_denali_DENALI_CTL_00_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_00_v2_t\n
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
 *     <td width="30%"> @param arefresh </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Trigger auto-refresh at boundary specified by AUTO_REFRESH_MODE.
 *        WRITE-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ap </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enable auto pre-charge mode of controller. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param addr_cmp_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enable address collision detection for cmd queue placement
 *        logic.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_00
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      arefresh                                  :  1;
     unsigned      reserved1                                 :  7;
     unsigned      ap                                        :  1;
     unsigned      reserved2                                 :  7;
     unsigned      addr_cmp_en                               :  1;
     unsigned      obsolete0                                 :  8;
#else    /* Little Endian */
     unsigned      obsolete0                                 :  8;
     unsigned      addr_cmp_en                               :  1;
     unsigned      reserved2                                 :  7;
     unsigned      ap                                        :  1;
     unsigned      reserved1                                 :  7;
     unsigned      arefresh                                  :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_00_v2_t;

/*! @struct ncp_denali_DENALI_CTL_01_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_01_t\n
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
 *     <td width="30%"> @param bist_data_check </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Enable data checking with BIST operation. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bist_addr_check </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enable address checking with BIST operation. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bank_split_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enable bank splitting for cmd queue placement logic. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param auto_refresh_mode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Define auto-refresh to occur at next burst or next
 *        cmd boundary.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_01
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      bist_data_check                           :  1;
     unsigned      reserved1                                 :  7;
     unsigned      bist_addr_check                           :  1;
     unsigned      reserved2                                 :  7;
     unsigned      bank_split_en                             :  1;
     unsigned      reserved3                                 :  7;
     unsigned      auto_refresh_mode                         :  1;
#else    /* Little Endian */
     unsigned      auto_refresh_mode                         :  1;
     unsigned      reserved3                                 :  7;
     unsigned      bank_split_en                             :  1;
     unsigned      reserved2                                 :  7;
     unsigned      bist_addr_check                           :  1;
     unsigned      reserved1                                 :  7;
     unsigned      bist_data_check                           :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_01_t;

/*! @struct ncp_denali_DENALI_CTL_02_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_02_t\n
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
 *     <td width="30%"> @param dll_bypass_mode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Enable the DLL bypass feature of the controller. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dlllockreg </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Status of DLL lock coming out of master delay. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param concurrentap </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allow controller to issue cmds to other banks while
 *        a bank is in auto pre-charge.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bist_go </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Initiate a BIST operation. WRITE-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_02
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      dll_bypass_mode                           :  1;
     unsigned      reserved1                                 :  7;
     unsigned      dlllockreg                                :  1;
     unsigned      reserved2                                 :  7;
     unsigned      concurrentap                              :  1;
     unsigned      reserved3                                 :  7;
     unsigned      bist_go                                   :  1;
#else    /* Little Endian */
     unsigned      bist_go                                   :  1;
     unsigned      reserved3                                 :  7;
     unsigned      concurrentap                              :  1;
     unsigned      reserved2                                 :  7;
     unsigned      dlllockreg                                :  1;
     unsigned      reserved1                                 :  7;
     unsigned      dll_bypass_mode                           :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_02_t;

/*! @struct ncp_denali_DENALI_CTL_02_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_02_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param concurrentap </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allow controller to issue cmds to other banks while
 *        a bank is in auto pre-charge.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bist_go </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Initiate a BIST operation. WRITE-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_02
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 : 16;
     unsigned      reserved0                                 :  7;
     unsigned      concurrentap                              :  1;
     unsigned      reserved1                                 :  7;
     unsigned      bist_go                                   :  1;
#else    /* Little Endian */
     unsigned      bist_go                                   :  1;
     unsigned      reserved1                                 :  7;
     unsigned      concurrentap                              :  1;
     unsigned      reserved0                                 :  7;
     unsigned      obsolete2                                 : 16;
#endif
} ncp_denali_DENALI_CTL_02_v2_t;

/*! @struct ncp_denali_DENALI_CTL_03_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_03_t\n
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
 *     <td width="30%"> @param eight_bank_mode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Number of banks on the DRAM(s). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_disable_w_uc_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Controls auto-corruption of ECC when un-correctable
 *        errors occur in R/M/W operations.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param drive_dq_dqs </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Sets DQ/DQS output enable behavior when controller
 *        is idle.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqs_n_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Set DQS pin as single-ended or differential. </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_03
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      eight_bank_mode                           :  1;
     unsigned      reserved1                                 :  7;
     unsigned      ecc_disable_w_uc_err                      :  1;
     unsigned      reserved2                                 :  7;
     unsigned      drive_dq_dqs                              :  1;
     unsigned      reserved3                                 :  7;
     unsigned      dqs_n_en                                  :  1;
#else    /* Little Endian */
     unsigned      dqs_n_en                                  :  1;
     unsigned      reserved3                                 :  7;
     unsigned      drive_dq_dqs                              :  1;
     unsigned      reserved2                                 :  7;
     unsigned      ecc_disable_w_uc_err                      :  1;
     unsigned      reserved1                                 :  7;
     unsigned      eight_bank_mode                           :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_03_t;

/*! @struct ncp_denali_DENALI_CTL_03_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_03_v2_t\n
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
 *     <td width="30%"> @param eight_bank_mode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Number of banks on the DRAM(s). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_disable_w_uc_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Controls auto-corruption of ECC when un-correctable
 *        errors occur in R/M/W operations.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_03
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      eight_bank_mode                           :  1;
     unsigned      reserved1                                 :  7;
     unsigned      ecc_disable_w_uc_err                      :  1;
     unsigned      obsolete0                                 : 16;
#else    /* Little Endian */
     unsigned      obsolete0                                 : 16;
     unsigned      ecc_disable_w_uc_err                      :  1;
     unsigned      reserved1                                 :  7;
     unsigned      eight_bank_mode                           :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_03_v2_t;

/*! @struct ncp_denali_DENALI_CTL_04_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_04_t\n
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
 *     <td width="30%"> @param fwc </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Force a write check. Xor XOR_CHECK_BITS with ecc code
 *        and write to memory. WRITE-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fast_write </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Define when write cmds are issued to DRAM devices. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param en_wr_leveling </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enables the MC write leveling module. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enable_quick_srefresh </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allow user to interrupt memory initialization to enter
 *        self-refresh mode.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_04
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      fwc                                       :  1;
     unsigned      reserved1                                 :  7;
     unsigned      fast_write                                :  1;
     unsigned      reserved2                                 :  7;
     unsigned      en_wr_leveling                            :  1;
     unsigned      reserved3                                 :  7;
     unsigned      enable_quick_srefresh                     :  1;
#else    /* Little Endian */
     unsigned      enable_quick_srefresh                     :  1;
     unsigned      reserved3                                 :  7;
     unsigned      en_wr_leveling                            :  1;
     unsigned      reserved2                                 :  7;
     unsigned      fast_write                                :  1;
     unsigned      reserved1                                 :  7;
     unsigned      fwc                                       :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_04_t;

/*! @struct ncp_denali_DENALI_CTL_04_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_04_v2_t\n
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
 *     <td width="30%"> @param fwc </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Force a write check. Xor XOR_CHECK_BITS with ecc code
 *        and write to memory. WRITE-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fast_write </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Define when write cmds are issued to DRAM devices. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enable_quick_srefresh </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allow user to interrupt memory initialization to enter
 *        self-refresh mode.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_04
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      fwc                                       :  1;
     unsigned      reserved1                                 :  7;
     unsigned      fast_write                                :  1;
     unsigned      obsolete1                                 :  8;
     unsigned      reserved2                                 :  7;
     unsigned      enable_quick_srefresh                     :  1;
#else    /* Little Endian */
     unsigned      enable_quick_srefresh                     :  1;
     unsigned      reserved2                                 :  7;
     unsigned      obsolete1                                 :  8;
     unsigned      fast_write                                :  1;
     unsigned      reserved1                                 :  7;
     unsigned      fwc                                       :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_04_v2_t;

/*! @struct ncp_denali_DENALI_CTL_05_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_05_t\n
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
 *     <td width="30%"> @param no_cmd_init </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Disable DRAM cmds until TDLL has expired during initialization. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param intrptwritea </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Allow the controller to interrupt a combined write
 *        with auto pre-charge cmd with another write cmd.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param intrptreada </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allow the controller to interrupt a combined read
 *        with auto pre-charge cmd with another read cmd.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param intrptapburst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allow the controller to interrupt an auto pre-charge
 *        cmd with another cmd.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_05
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      no_cmd_init                               :  1;
     unsigned      reserved1                                 :  7;
     unsigned      intrptwritea                              :  1;
     unsigned      reserved2                                 :  7;
     unsigned      intrptreada                               :  1;
     unsigned      reserved3                                 :  7;
     unsigned      intrptapburst                             :  1;
#else    /* Little Endian */
     unsigned      intrptapburst                             :  1;
     unsigned      reserved3                                 :  7;
     unsigned      intrptreada                               :  1;
     unsigned      reserved2                                 :  7;
     unsigned      intrptwritea                              :  1;
     unsigned      reserved1                                 :  7;
     unsigned      no_cmd_init                               :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_05_t;

/*! @struct ncp_denali_DENALI_CTL_05_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_05_v2_t\n
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
 *     <td width="30%"> @param no_cmd_init </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Disable DRAM cmds until TDLL has expired during initialization. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_05
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      no_cmd_init                               :  1;
     unsigned      obsolete0                                 : 24;
#else    /* Little Endian */
     unsigned      obsolete0                                 : 24;
     unsigned      no_cmd_init                               :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_05_v2_t;

/*! @struct ncp_denali_DENALI_CTL_06_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_06_t\n
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
 *     <td width="30%"> @param power_down </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Disable clock enable and set DRAMs in power-down state. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param placement_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enable placement logic for cmd queue. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odt_alt_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enable use of non-DFI odt_alt signal. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_06
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      power_down                                :  1;
     unsigned      reserved1                                 :  7;
     unsigned      placement_en                              :  1;
     unsigned      reserved2                                 :  7;
     unsigned      odt_alt_en                                :  1;
     unsigned      obsolete0                                 :  8;
#else    /* Little Endian */
     unsigned      obsolete0                                 :  8;
     unsigned      odt_alt_en                                :  1;
     unsigned      reserved2                                 :  7;
     unsigned      placement_en                              :  1;
     unsigned      reserved1                                 :  7;
     unsigned      power_down                                :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_06_t;

/*! @struct ncp_denali_DENALI_CTL_07_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_07_t\n
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
 *     <td width="30%"> @param rdlvl_edge </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Specifies the read DQS edge positive or negative to
 *        be used for the read leveling operation.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_begin_delay_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enables the read leveling logic to find the DQ data
 *        eye.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pwrup_srefresh_exit </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allow powerup via self-refresh instead of full memory
 *        initialization.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param priority_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enable priority for cmd queue placement logic. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_07
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      rdlvl_edge                                :  1;
     unsigned      reserved1                                 :  7;
     unsigned      rdlvl_begin_delay_en                      :  1;
     unsigned      reserved2                                 :  7;
     unsigned      pwrup_srefresh_exit                       :  1;
     unsigned      reserved3                                 :  7;
     unsigned      priority_en                               :  1;
#else    /* Little Endian */
     unsigned      priority_en                               :  1;
     unsigned      reserved3                                 :  7;
     unsigned      pwrup_srefresh_exit                       :  1;
     unsigned      reserved2                                 :  7;
     unsigned      rdlvl_begin_delay_en                      :  1;
     unsigned      reserved1                                 :  7;
     unsigned      rdlvl_edge                                :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_07_t;

/*! @struct ncp_denali_DENALI_CTL_08_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_08_t\n
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
 *     <td width="30%"> @param rdlvl_gate_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> User request to initiate gate training. WRITE-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_preamble_check_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enables the preamble check sequence during initial
 *        gate training.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enables gate training mode of the read leveling module
 *        in the MC.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enables the MC read leveling module. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_08
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      rdlvl_gate_req                            :  1;
     unsigned      reserved1                                 :  7;
     unsigned      rdlvl_gate_preamble_check_en              :  1;
     unsigned      reserved2                                 :  7;
     unsigned      rdlvl_gate_en                             :  1;
     unsigned      reserved3                                 :  7;
     unsigned      rdlvl_en                                  :  1;
#else    /* Little Endian */
     unsigned      rdlvl_en                                  :  1;
     unsigned      reserved3                                 :  7;
     unsigned      rdlvl_gate_en                             :  1;
     unsigned      reserved2                                 :  7;
     unsigned      rdlvl_gate_preamble_check_en              :  1;
     unsigned      reserved1                                 :  7;
     unsigned      rdlvl_gate_req                            :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_08_t;

/*! @struct ncp_denali_DENALI_CTL_09_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_09_t\n
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
 *     <td width="30%"> @param rdlvl_offset_dir_3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Direction of the read level midpoint delay offset
 *        for data slice 3.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_offset_dir_2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Direction of the read level midpoint delay offset
 *        for data slice 2.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_offset_dir_1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Direction of the read level midpoint delay offset
 *        for data slice 1.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_offset_dir_0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Direction of the read level midpoint delay offset
 *        for data slice 0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_09
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      rdlvl_offset_dir_3                        :  1;
     unsigned      reserved1                                 :  7;
     unsigned      rdlvl_offset_dir_2                        :  1;
     unsigned      reserved2                                 :  7;
     unsigned      rdlvl_offset_dir_1                        :  1;
     unsigned      reserved3                                 :  7;
     unsigned      rdlvl_offset_dir_0                        :  1;
#else    /* Little Endian */
     unsigned      rdlvl_offset_dir_0                        :  1;
     unsigned      reserved3                                 :  7;
     unsigned      rdlvl_offset_dir_1                        :  1;
     unsigned      reserved2                                 :  7;
     unsigned      rdlvl_offset_dir_2                        :  1;
     unsigned      reserved1                                 :  7;
     unsigned      rdlvl_offset_dir_3                        :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_09_t;

/*! @struct ncp_denali_DENALI_CTL_10_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_10_t\n
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
 *     <td width="30%"> @param rdlvl_offset_dir_7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Direction of the read level midpoint delay offset
 *        for data slice 7.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_offset_dir_6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Direction of the read level midpoint delay offset
 *        for data slice 6.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_offset_dir_5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Direction of the read level midpoint delay offset
 *        for data slice 5.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_offset_dir_4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Direction of the read level midpoint delay offset
 *        for data slice 4.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_10
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      rdlvl_offset_dir_7                        :  1;
     unsigned      reserved1                                 :  7;
     unsigned      rdlvl_offset_dir_6                        :  1;
     unsigned      reserved2                                 :  7;
     unsigned      rdlvl_offset_dir_5                        :  1;
     unsigned      reserved3                                 :  7;
     unsigned      rdlvl_offset_dir_4                        :  1;
#else    /* Little Endian */
     unsigned      rdlvl_offset_dir_4                        :  1;
     unsigned      reserved3                                 :  7;
     unsigned      rdlvl_offset_dir_5                        :  1;
     unsigned      reserved2                                 :  7;
     unsigned      rdlvl_offset_dir_6                        :  1;
     unsigned      reserved1                                 :  7;
     unsigned      rdlvl_offset_dir_7                        :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_10_t;

/*! @struct ncp_denali_DENALI_CTL_11_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_11_t\n
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
 *     <td width="30%"> @param reg_dimm_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Enable registered DIMM operation of the controller. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reduc </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enable the half datapath feature of the controller. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> User request to initiate read leveling. WRITE-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_offset_dir_8 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Direction of the read level midpoint delay offset
 *        for data slice 8.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_11
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      reg_dimm_enable                           :  1;
     unsigned      reserved1                                 :  7;
     unsigned      reduc                                     :  1;
     unsigned      reserved2                                 :  7;
     unsigned      rdlvl_req                                 :  1;
     unsigned      reserved3                                 :  7;
     unsigned      rdlvl_offset_dir_8                        :  1;
#else    /* Little Endian */
     unsigned      rdlvl_offset_dir_8                        :  1;
     unsigned      reserved3                                 :  7;
     unsigned      rdlvl_req                                 :  1;
     unsigned      reserved2                                 :  7;
     unsigned      reduc                                     :  1;
     unsigned      reserved1                                 :  7;
     unsigned      reg_dimm_enable                           :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_11_t;

/*! @struct ncp_denali_DENALI_CTL_12_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_12_t\n
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
 *     <td width="30%"> @param swap_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Enable command swapping logic in execution unit. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param start </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Initiate cmd processing in the controller. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param srefresh </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Place DRAMs in self-refresh mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rw_same_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enable read/write grouping for cmd queue placement
 *        logic.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_12
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      swap_en                                   :  1;
     unsigned      reserved1                                 :  7;
     unsigned      start                                     :  1;
     unsigned      reserved2                                 :  7;
     unsigned      srefresh                                  :  1;
     unsigned      reserved3                                 :  7;
     unsigned      rw_same_en                                :  1;
#else    /* Little Endian */
     unsigned      rw_same_en                                :  1;
     unsigned      reserved3                                 :  7;
     unsigned      srefresh                                  :  1;
     unsigned      reserved2                                 :  7;
     unsigned      start                                     :  1;
     unsigned      reserved1                                 :  7;
     unsigned      swap_en                                   :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_12_t;

/*! @struct ncp_denali_DENALI_CTL_13_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_13_t\n
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
 *     <td width="30%"> @param swlvl_op_done </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Signals that software leveling is complete. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param swlvl_load </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> User request to load delays and execute software leveling.
 *        WRITE-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param swlvl_exit </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> User request to exit software leveling. WRITE-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param swap_port_rw_same_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> No meaning for this MC. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_13
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      swlvl_op_done                             :  1;
     unsigned      reserved1                                 :  7;
     unsigned      swlvl_load                                :  1;
     unsigned      reserved2                                 :  7;
     unsigned      swlvl_exit                                :  1;
     unsigned      reserved3                                 :  7;
     unsigned      swap_port_rw_same_en                      :  1;
#else    /* Little Endian */
     unsigned      swap_port_rw_same_en                      :  1;
     unsigned      reserved3                                 :  7;
     unsigned      swlvl_exit                                :  1;
     unsigned      reserved2                                 :  7;
     unsigned      swlvl_load                                :  1;
     unsigned      reserved1                                 :  7;
     unsigned      swlvl_op_done                             :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_13_t;

/*! @struct ncp_denali_DENALI_CTL_14_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_14_t\n
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
 *     <td width="30%"> @param weighted_round_robin_latency_control </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Free-running or limited WRR latency counters. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tref_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Issue auto-refresh cmds to the DRAMs every TREF cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tras_lockout </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allow the controller to execute auto pre-charge cmds
 *        before TRAS_MIN expires.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param swlvl_start </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> User request to initiate software leveling of type
 *        in SW_LEVELING_MODE. WRITE-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_14
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      weighted_round_robin_latency_control      :  1;
     unsigned      reserved1                                 :  7;
     unsigned      tref_enable                               :  1;
     unsigned      reserved2                                 :  7;
     unsigned      tras_lockout                              :  1;
     unsigned      reserved3                                 :  7;
     unsigned      swlvl_start                               :  1;
#else    /* Little Endian */
     unsigned      swlvl_start                               :  1;
     unsigned      reserved3                                 :  7;
     unsigned      tras_lockout                              :  1;
     unsigned      reserved2                                 :  7;
     unsigned      tref_enable                               :  1;
     unsigned      reserved1                                 :  7;
     unsigned      weighted_round_robin_latency_control      :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_14_t;

/*! @struct ncp_denali_DENALI_CTL_15_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_15_t\n
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
 *     <td width="30%"> @param wrlvl_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> User request to initiate write leveling. WRITE-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_interval_ct_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enable write leveling interval counter. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param write_modereg </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Write mode register data to the DRAMs. WRITE-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param writeinterp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allow controller to interrupt a write burst to the
 *        DRAMs with a read cmd.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_15
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      wrlvl_req                                 :  1;
     unsigned      reserved1                                 :  7;
     unsigned      wrlvl_interval_ct_en                      :  1;
     unsigned      reserved2                                 :  7;
     unsigned      write_modereg                             :  1;
     unsigned      reserved3                                 :  7;
     unsigned      writeinterp                               :  1;
#else    /* Little Endian */
     unsigned      writeinterp                               :  1;
     unsigned      reserved3                                 :  7;
     unsigned      write_modereg                             :  1;
     unsigned      reserved2                                 :  7;
     unsigned      wrlvl_interval_ct_en                      :  1;
     unsigned      reserved1                                 :  7;
     unsigned      wrlvl_req                                 :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_15_t;

/*! @struct ncp_denali_DENALI_CTL_15_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_15_v2_t\n
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
 *     <td width="30%"> @param wrlvl_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> User request to initiate write leveling. WRITE-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param write_modereg </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Write mode register data to the DRAMs. WRITE-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param writeinterp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allow controller to interrupt a write burst to the
 *        DRAMs with a read cmd.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_15
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      wrlvl_req                                 :  1;
     unsigned      obsolete2                                 :  8;
     unsigned      reserved1                                 :  7;
     unsigned      write_modereg                             :  1;
     unsigned      reserved2                                 :  7;
     unsigned      writeinterp                               :  1;
#else    /* Little Endian */
     unsigned      writeinterp                               :  1;
     unsigned      reserved2                                 :  7;
     unsigned      write_modereg                             :  1;
     unsigned      reserved1                                 :  7;
     unsigned      obsolete2                                 :  8;
     unsigned      wrlvl_req                                 :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_15_v2_t;

/*! @struct ncp_denali_DENALI_CTL_16_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_16_t\n
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
 *     <td width="30%"> @param axi0_w_priority </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Priority of write cmds from AXI port 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_r_priority </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Priority of read cmds from AXI port 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_port_ordering </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reassigned port order for port 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_fifo_type_reg </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Clock domain relativity between AXI port 0 and Databahn
 *        core.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_16
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      axi0_w_priority                           :  2;
     unsigned      reserved1                                 :  6;
     unsigned      axi0_r_priority                           :  2;
     unsigned      reserved2                                 :  6;
     unsigned      axi0_port_ordering                        :  2;
     unsigned      reserved3                                 :  6;
     unsigned      axi0_fifo_type_reg                        :  2;
#else    /* Little Endian */
     unsigned      axi0_fifo_type_reg                        :  2;
     unsigned      reserved3                                 :  6;
     unsigned      axi0_port_ordering                        :  2;
     unsigned      reserved2                                 :  6;
     unsigned      axi0_r_priority                           :  2;
     unsigned      reserved1                                 :  6;
     unsigned      axi0_w_priority                           :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_16_t;

/*! @struct ncp_denali_DENALI_CTL_16_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_16_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_port_ordering </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reassigned port order for port 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_fifo_type_reg </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Clock domain relativity between AXI port 0 and Databahn
 *        core.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_16
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_port_ordering                        :  2;
     unsigned      reserved1                                 :  6;
     unsigned      axi0_fifo_type_reg                        :  2;
#else    /* Little Endian */
     unsigned      axi0_fifo_type_reg                        :  2;
     unsigned      reserved1                                 :  6;
     unsigned      axi0_port_ordering                        :  2;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete2                                 : 16;
#endif
} ncp_denali_DENALI_CTL_16_v2_t;

/*! @struct ncp_denali_DENALI_CTL_17_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_17_t\n
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
 *     <td width="30%"> @param axi1_w_priority </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Priority of write cmds from AXI port 1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi1_r_priority </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Priority of read cmds from AXI port 1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi1_port_ordering </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reassigned port order for port 1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi1_fifo_type_reg </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Clock domain relativity between AXI port 1 and Databahn
 *        core.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_17
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      axi1_w_priority                           :  2;
     unsigned      reserved1                                 :  6;
     unsigned      axi1_r_priority                           :  2;
     unsigned      reserved2                                 :  6;
     unsigned      axi1_port_ordering                        :  2;
     unsigned      reserved3                                 :  6;
     unsigned      axi1_fifo_type_reg                        :  2;
#else    /* Little Endian */
     unsigned      axi1_fifo_type_reg                        :  2;
     unsigned      reserved3                                 :  6;
     unsigned      axi1_port_ordering                        :  2;
     unsigned      reserved2                                 :  6;
     unsigned      axi1_r_priority                           :  2;
     unsigned      reserved1                                 :  6;
     unsigned      axi1_w_priority                           :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_17_t;

/*! @struct ncp_denali_DENALI_CTL_17_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_17_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi1_port_ordering </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reassigned port order for port 1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi1_fifo_type_reg </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Clock domain relativity between AXI port 1 and Databahn
 *        core.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_17
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi1_port_ordering                        :  2;
     unsigned      reserved1                                 :  6;
     unsigned      axi1_fifo_type_reg                        :  2;
#else    /* Little Endian */
     unsigned      axi1_fifo_type_reg                        :  2;
     unsigned      reserved1                                 :  6;
     unsigned      axi1_port_ordering                        :  2;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete2                                 : 16;
#endif
} ncp_denali_DENALI_CTL_17_v2_t;

/*! @struct ncp_denali_DENALI_CTL_18_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_18_t\n
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
 *     <td width="30%"> @param axi2_w_priority </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Priority of write cmds from AXI port 2. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2_r_priority </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Priority of read cmds from AXI port 2. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2_port_ordering </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reassigned port order for port 2. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2_fifo_type_reg </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Clock domain relativity between AXI port 2 and Databahn
 *        core.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_18
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      axi2_w_priority                           :  2;
     unsigned      reserved1                                 :  6;
     unsigned      axi2_r_priority                           :  2;
     unsigned      reserved2                                 :  6;
     unsigned      axi2_port_ordering                        :  2;
     unsigned      reserved3                                 :  6;
     unsigned      axi2_fifo_type_reg                        :  2;
#else    /* Little Endian */
     unsigned      axi2_fifo_type_reg                        :  2;
     unsigned      reserved3                                 :  6;
     unsigned      axi2_port_ordering                        :  2;
     unsigned      reserved2                                 :  6;
     unsigned      axi2_r_priority                           :  2;
     unsigned      reserved1                                 :  6;
     unsigned      axi2_w_priority                           :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_18_t;

/*! @struct ncp_denali_DENALI_CTL_18_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_18_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2_port_ordering </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reassigned port order for port 2. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2_fifo_type_reg </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Clock domain relativity between AXI port 2 and Databahn
 *        core.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_18
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi2_port_ordering                        :  2;
     unsigned      reserved1                                 :  6;
     unsigned      axi2_fifo_type_reg                        :  2;
#else    /* Little Endian */
     unsigned      axi2_fifo_type_reg                        :  2;
     unsigned      reserved1                                 :  6;
     unsigned      axi2_port_ordering                        :  2;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete2                                 : 16;
#endif
} ncp_denali_DENALI_CTL_18_v2_t;

/*! @struct ncp_denali_DENALI_CTL_19_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_19_t\n
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
 *     <td width="30%"> @param axi3_w_priority </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Priority of write cmds from AXI port 3. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi3_r_priority </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Priority of read cmds from AXI port 3. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi3_port_ordering </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reassigned port order for port 3. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi3_fifo_type_reg </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Clock domain relativity between AXI port 3 and Databahn
 *        core.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_19
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      axi3_w_priority                           :  2;
     unsigned      reserved1                                 :  6;
     unsigned      axi3_r_priority                           :  2;
     unsigned      reserved2                                 :  6;
     unsigned      axi3_port_ordering                        :  2;
     unsigned      reserved3                                 :  6;
     unsigned      axi3_fifo_type_reg                        :  2;
#else    /* Little Endian */
     unsigned      axi3_fifo_type_reg                        :  2;
     unsigned      reserved3                                 :  6;
     unsigned      axi3_port_ordering                        :  2;
     unsigned      reserved2                                 :  6;
     unsigned      axi3_r_priority                           :  2;
     unsigned      reserved1                                 :  6;
     unsigned      axi3_w_priority                           :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_19_t;

/*! @struct ncp_denali_DENALI_CTL_19_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_19_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi3_port_ordering </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reassigned port order for port 3. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi3_fifo_type_reg </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Clock domain relativity between AXI port 3 and Databahn
 *        core.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_19
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi3_port_ordering                        :  2;
     unsigned      reserved1                                 :  6;
     unsigned      axi3_fifo_type_reg                        :  2;
#else    /* Little Endian */
     unsigned      axi3_fifo_type_reg                        :  2;
     unsigned      reserved1                                 :  6;
     unsigned      axi3_port_ordering                        :  2;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete2                                 : 16;
#endif
} ncp_denali_DENALI_CTL_19_v2_t;

/*! @struct ncp_denali_DENALI_CTL_20_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_20_t\n
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
 *     <td width="30%"> @param rtt_0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> On-Die termination resistance setting for all DRAM
 *        devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_cs </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Specifies the target chip select for the read leveling
 *        operation.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ctrl_raw </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> ECC error checking and correcting control. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bist_result </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> BIST operation status (pass/fail). READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_20
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      rtt_0                                     :  2;
     unsigned      reserved1                                 :  6;
     unsigned      rdlvl_cs                                  :  2;
     unsigned      reserved2                                 :  6;
     unsigned      ctrl_raw                                  :  2;
     unsigned      reserved3                                 :  6;
     unsigned      bist_result                               :  2;
#else    /* Little Endian */
     unsigned      bist_result                               :  2;
     unsigned      reserved3                                 :  6;
     unsigned      ctrl_raw                                  :  2;
     unsigned      reserved2                                 :  6;
     unsigned      rdlvl_cs                                  :  2;
     unsigned      reserved1                                 :  6;
     unsigned      rtt_0                                     :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_20_t;

/*! @struct ncp_denali_DENALI_CTL_20_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_20_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_cs </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Specifies the target chip select for the read leveling
 *        operation.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ctrl_raw </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> ECC error checking and correcting control. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bist_result </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> BIST operation status (pass/fail). READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_20
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      rdlvl_cs                                  :  2;
     unsigned      reserved1                                 :  6;
     unsigned      ctrl_raw                                  :  2;
     unsigned      reserved2                                 :  6;
     unsigned      bist_result                               :  2;
#else    /* Little Endian */
     unsigned      bist_result                               :  2;
     unsigned      reserved2                                 :  6;
     unsigned      ctrl_raw                                  :  2;
     unsigned      reserved1                                 :  6;
     unsigned      rdlvl_cs                                  :  2;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete3                                 :  8;
#endif
} ncp_denali_DENALI_CTL_20_v2_t;

/*! @struct ncp_denali_DENALI_CTL_21_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_21_t\n
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
 *     <td width="30%"> @param zq_on_sref_exit </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines the type of ZQ calibration performed at self-refresh
 *        exit.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_cs </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Specifies the target chip select for the write leveling
 *        operation.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param weighted_round_robin_weight_sharing </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Per-port pair shared arbitration for WRR. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sw_leveling_mode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the leveling operation for software leveling. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_21
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      zq_on_sref_exit                           :  2;
     unsigned      reserved1                                 :  6;
     unsigned      wrlvl_cs                                  :  2;
     unsigned      reserved2                                 :  6;
     unsigned      weighted_round_robin_weight_sharing       :  2;
     unsigned      reserved3                                 :  6;
     unsigned      sw_leveling_mode                          :  2;
#else    /* Little Endian */
     unsigned      sw_leveling_mode                          :  2;
     unsigned      reserved3                                 :  6;
     unsigned      weighted_round_robin_weight_sharing       :  2;
     unsigned      reserved2                                 :  6;
     unsigned      wrlvl_cs                                  :  2;
     unsigned      reserved1                                 :  6;
     unsigned      zq_on_sref_exit                           :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_21_t;

/*! @struct ncp_denali_DENALI_CTL_22_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_22_t\n
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
 *     <td width="30%"> @param bstlen </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Encoded burst length sent to DRAMs during initialization. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param age_count </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Initial value of master aging-rate counter for cmd
 *        aging.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param addr_pins </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Difference between number of addr pins available and
 *        number being used.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zq_req </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> User request to initiate a ZQ calibration. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_22
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  5;
     unsigned      bstlen                                    :  3;
     unsigned      reserved1                                 :  5;
     unsigned      age_count                                 :  3;
     unsigned      reserved2                                 :  5;
     unsigned      addr_pins                                 :  3;
     unsigned      reserved3                                 :  6;
     unsigned      zq_req                                    :  2;
#else    /* Little Endian */
     unsigned      zq_req                                    :  2;
     unsigned      reserved3                                 :  6;
     unsigned      addr_pins                                 :  3;
     unsigned      reserved2                                 :  5;
     unsigned      age_count                                 :  3;
     unsigned      reserved1                                 :  5;
     unsigned      bstlen                                    :  3;
     unsigned      reserved0                                 :  5;
#endif
} ncp_denali_DENALI_CTL_22_t;

/*! @struct ncp_denali_DENALI_CTL_23_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_23_t\n
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
 *     <td width="30%"> @param lvl_status </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Status of write level, read level, and gate training
 *        requests. This is used with the LVL_REQ interrupt.
 *        READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param command_age_count </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Initial value of individual cmd aging counters for
 *        cmd aging.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param column_size </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Difference between number of column pins available
 *        and number being used.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cke_delay </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Additional cycles to delay CKE for status reporting. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_23
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  5;
     unsigned      lvl_status                                :  3;
     unsigned      reserved1                                 :  5;
     unsigned      command_age_count                         :  3;
     unsigned      reserved2                                 :  5;
     unsigned      column_size                               :  3;
     unsigned      reserved3                                 :  5;
     unsigned      cke_delay                                 :  3;
#else    /* Little Endian */
     unsigned      cke_delay                                 :  3;
     unsigned      reserved3                                 :  5;
     unsigned      column_size                               :  3;
     unsigned      reserved2                                 :  5;
     unsigned      command_age_count                         :  3;
     unsigned      reserved1                                 :  5;
     unsigned      lvl_status                                :  3;
     unsigned      reserved0                                 :  5;
#endif
} ncp_denali_DENALI_CTL_23_t;

/*! @struct ncp_denali_DENALI_CTL_24_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_24_t\n
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
 *     <td width="30%"> @param tcke </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Minimum CKE pulse width. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param q_fullness </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Quantity that determines cmd queue full. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param port_data_error_type </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Type of error and access type that caused the PORT
 *        data error. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param max_cs_reg </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Maximum number of chip selects available. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_24
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  5;
     unsigned      tcke                                      :  3;
     unsigned      reserved1                                 :  5;
     unsigned      q_fullness                                :  3;
     unsigned      reserved2                                 :  5;
     unsigned      port_data_error_type                      :  3;
     unsigned      reserved3                                 :  5;
     unsigned      max_cs_reg                                :  3;
#else    /* Little Endian */
     unsigned      max_cs_reg                                :  3;
     unsigned      reserved3                                 :  5;
     unsigned      port_data_error_type                      :  3;
     unsigned      reserved2                                 :  5;
     unsigned      q_fullness                                :  3;
     unsigned      reserved1                                 :  5;
     unsigned      tcke                                      :  3;
     unsigned      reserved0                                 :  5;
#endif
} ncp_denali_DENALI_CTL_24_t;

/*! @struct ncp_denali_DENALI_CTL_25_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_25_t\n
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
 *     <td width="30%"> @param w2r_samecs_dly </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Additional clocks of delay to insert between writes
 *        and reads to the same chip select.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param w2r_diffcs_dly </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Additional clocks of delay to insert between writes
 *        and reads to different chip selects.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trtp </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DRAM TRTP parameter in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trrd </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM TRRD parameter in cycles. </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_25
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  5;
     unsigned      w2r_samecs_dly                            :  3;
     unsigned      reserved1                                 :  5;
     unsigned      w2r_diffcs_dly                            :  3;
     unsigned      reserved2                                 :  5;
     unsigned      trtp                                      :  3;
     unsigned      reserved3                                 :  5;
     unsigned      trrd                                      :  3;
#else    /* Little Endian */
     unsigned      trrd                                      :  3;
     unsigned      reserved3                                 :  5;
     unsigned      trtp                                      :  3;
     unsigned      reserved2                                 :  5;
     unsigned      w2r_diffcs_dly                            :  3;
     unsigned      reserved1                                 :  5;
     unsigned      w2r_samecs_dly                            :  3;
     unsigned      reserved0                                 :  5;
#endif
} ncp_denali_DENALI_CTL_25_t;

/*! @struct ncp_denali_DENALI_CTL_25_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_25_v2_t\n
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
 *     <td width="30%"> @param w2r_samecs_dly </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Additional delay to insert between writes and reads
 *        to the same chip select.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param w2r_diffcs_dly </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Additional delay to insert between writes and reads
 *        to different chip selects.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trtp </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DRAM TRTP parameter in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trrd </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM TRRD parameter in cycles. </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_25
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  5;
     unsigned      w2r_samecs_dly                            :  3;
     unsigned      reserved1                                 :  5;
     unsigned      w2r_diffcs_dly                            :  3;
     unsigned      reserved2                                 :  4;
     unsigned      trtp                                      :  4;
     unsigned      reserved3                                 :  5;
     unsigned      trrd                                      :  3;
#else    /* Little Endian */
     unsigned      trrd                                      :  3;
     unsigned      reserved3                                 :  5;
     unsigned      trtp                                      :  4;
     unsigned      reserved2                                 :  4;
     unsigned      w2r_diffcs_dly                            :  3;
     unsigned      reserved1                                 :  5;
     unsigned      w2r_samecs_dly                            :  3;
     unsigned      reserved0                                 :  5;
#endif
} ncp_denali_DENALI_CTL_25_v2_t;

/*! @struct ncp_denali_DENALI_CTL_26_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_26_t\n
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
 *     <td width="30%"> @param axi0_priority1_relative_priority </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Relative priority of priority 1 cmds from port 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_priority0_relative_priority </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Relative priority of priority 0 cmds from port 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param aprebit </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Location of the auto pre-charge bit in the DRAM address. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param address_mirroring </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Indicates which chip selects support address mirroring. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_26
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      axi0_priority1_relative_priority          :  4;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_priority0_relative_priority          :  4;
     unsigned      reserved2                                 :  4;
     unsigned      aprebit                                   :  4;
     unsigned      reserved3                                 :  4;
     unsigned      address_mirroring                         :  4;
#else    /* Little Endian */
     unsigned      address_mirroring                         :  4;
     unsigned      reserved3                                 :  4;
     unsigned      aprebit                                   :  4;
     unsigned      reserved2                                 :  4;
     unsigned      axi0_priority0_relative_priority          :  4;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_priority1_relative_priority          :  4;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_26_t;

/*! @struct ncp_denali_DENALI_CTL_27_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_27_t\n
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
 *     <td width="30%"> @param axi1_priority1_relative_priority </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Relative priority of priority 1 cmds from port 1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi1_priority0_relative_priority </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Relative priority of priority 0 cmds from port 1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_priority3_relative_priority </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Relative priority of priority 3 cmds from port 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_priority2_relative_priority </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Relative priority of priority 2 cmds from port 0. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_27
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      axi1_priority1_relative_priority          :  4;
     unsigned      reserved1                                 :  4;
     unsigned      axi1_priority0_relative_priority          :  4;
     unsigned      reserved2                                 :  4;
     unsigned      axi0_priority3_relative_priority          :  4;
     unsigned      reserved3                                 :  4;
     unsigned      axi0_priority2_relative_priority          :  4;
#else    /* Little Endian */
     unsigned      axi0_priority2_relative_priority          :  4;
     unsigned      reserved3                                 :  4;
     unsigned      axi0_priority3_relative_priority          :  4;
     unsigned      reserved2                                 :  4;
     unsigned      axi1_priority0_relative_priority          :  4;
     unsigned      reserved1                                 :  4;
     unsigned      axi1_priority1_relative_priority          :  4;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_27_t;

/*! @struct ncp_denali_DENALI_CTL_28_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_28_t\n
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
 *     <td width="30%"> @param axi2_priority1_relative_priority </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Relative priority of priority 1 cmds from port 2. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2_priority0_relative_priority </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Relative priority of priority 0 cmds from port 2. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi1_priority3_relative_priority </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Relative priority of priority 3 cmds from port 1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi1_priority2_relative_priority </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Relative priority of priority 2 cmds from port 1. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_28
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      axi2_priority1_relative_priority          :  4;
     unsigned      reserved1                                 :  4;
     unsigned      axi2_priority0_relative_priority          :  4;
     unsigned      reserved2                                 :  4;
     unsigned      axi1_priority3_relative_priority          :  4;
     unsigned      reserved3                                 :  4;
     unsigned      axi1_priority2_relative_priority          :  4;
#else    /* Little Endian */
     unsigned      axi1_priority2_relative_priority          :  4;
     unsigned      reserved3                                 :  4;
     unsigned      axi1_priority3_relative_priority          :  4;
     unsigned      reserved2                                 :  4;
     unsigned      axi2_priority0_relative_priority          :  4;
     unsigned      reserved1                                 :  4;
     unsigned      axi2_priority1_relative_priority          :  4;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_28_t;

/*! @struct ncp_denali_DENALI_CTL_29_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_29_t\n
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
 *     <td width="30%"> @param axi3_priority1_relative_priority </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Relative priority of priority 1 cmds from port 3. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi3_priority0_relative_priority </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Relative priority of priority 0 cmds from port 3. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2_priority3_relative_priority </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Relative priority of priority 3 cmds from port 2. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2_priority2_relative_priority </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Relative priority of priority 2 cmds from port 2. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_29
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      axi3_priority1_relative_priority          :  4;
     unsigned      reserved1                                 :  4;
     unsigned      axi3_priority0_relative_priority          :  4;
     unsigned      reserved2                                 :  4;
     unsigned      axi2_priority3_relative_priority          :  4;
     unsigned      reserved3                                 :  4;
     unsigned      axi2_priority2_relative_priority          :  4;
#else    /* Little Endian */
     unsigned      axi2_priority2_relative_priority          :  4;
     unsigned      reserved3                                 :  4;
     unsigned      axi2_priority3_relative_priority          :  4;
     unsigned      reserved2                                 :  4;
     unsigned      axi3_priority0_relative_priority          :  4;
     unsigned      reserved1                                 :  4;
     unsigned      axi3_priority1_relative_priority          :  4;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_29_t;

/*! @struct ncp_denali_DENALI_CTL_30_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_30_t\n
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
 *     <td width="30%"> @param burst_on_fly_bit </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Identifies the burst-on-fly bit in the mode registers. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi_aligned_strobe_disable </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> isabled read-modify-write for aligned AXI transfers
 *        with ECC
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi3_priority3_relative_priority </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Relative priority of priority 3 cmds from port 3. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi3_priority2_relative_priority </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Relative priority of priority 2 cmds from port 3. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_30
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      burst_on_fly_bit                          :  4;
     unsigned      reserved1                                 :  4;
     unsigned      axi_aligned_strobe_disable                :  4;
     unsigned      reserved2                                 :  4;
     unsigned      axi3_priority3_relative_priority          :  4;
     unsigned      reserved3                                 :  4;
     unsigned      axi3_priority2_relative_priority          :  4;
#else    /* Little Endian */
     unsigned      axi3_priority2_relative_priority          :  4;
     unsigned      reserved3                                 :  4;
     unsigned      axi3_priority3_relative_priority          :  4;
     unsigned      reserved2                                 :  4;
     unsigned      axi_aligned_strobe_disable                :  4;
     unsigned      reserved1                                 :  4;
     unsigned      burst_on_fly_bit                          :  4;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_30_t;

/*! @struct ncp_denali_DENALI_CTL_31_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_31_t\n
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
 *     <td width="30%"> @param dram_clk_disable </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Set value for the dfi_dram_clk_disable signal. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dram_class </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the mode of operation of the controller. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cs_map </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines which chip selects are active. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param caslat </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Encoded CAS latency sent to DRAMs during initialization. </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_31
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      dram_clk_disable                          :  4;
     unsigned      reserved1                                 :  4;
     unsigned      dram_class                                :  4;
     unsigned      reserved2                                 :  4;
     unsigned      cs_map                                    :  4;
     unsigned      reserved3                                 :  4;
     unsigned      caslat                                    :  4;
#else    /* Little Endian */
     unsigned      caslat                                    :  4;
     unsigned      reserved3                                 :  4;
     unsigned      cs_map                                    :  4;
     unsigned      reserved2                                 :  4;
     unsigned      dram_class                                :  4;
     unsigned      reserved1                                 :  4;
     unsigned      dram_clk_disable                          :  4;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_31_t;

/*! @struct ncp_denali_DENALI_CTL_31_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_31_v2_t\n
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
 *     <td width="30%"> @param dram_clk_disable </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Set value for the dfi_dram_clk_disable signal. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dram_class </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the mode of operation of the controller. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cs_map </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines which chip selects are active. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_31
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      dram_clk_disable                          :  4;
     unsigned      reserved1                                 :  4;
     unsigned      dram_class                                :  4;
     unsigned      reserved2                                 :  4;
     unsigned      cs_map                                    :  4;
     unsigned      obsolete0                                 :  8;
#else    /* Little Endian */
     unsigned      obsolete0                                 :  8;
     unsigned      cs_map                                    :  4;
     unsigned      reserved2                                 :  4;
     unsigned      dram_class                                :  4;
     unsigned      reserved1                                 :  4;
     unsigned      dram_clk_disable                          :  4;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_31_v2_t;

/*! @struct ncp_denali_DENALI_CTL_32_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_32_t\n
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
 *     <td width="30%"> @param odt_rd_map_cs1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Determines which chip(s) will have termination when
 *        a read occurs on chip 1.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odt_rd_map_cs0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Determines which chip(s) will have termination when
 *        a read occurs on chip 0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param max_col_reg </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Maximum width of column address in DRAMs. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param initaref </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of auto-refresh cmds to execute during DRAM
 *        initialization.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_32
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      odt_rd_map_cs1                            :  4;
     unsigned      reserved1                                 :  4;
     unsigned      odt_rd_map_cs0                            :  4;
     unsigned      reserved2                                 :  4;
     unsigned      max_col_reg                               :  4;
     unsigned      reserved3                                 :  4;
     unsigned      initaref                                  :  4;
#else    /* Little Endian */
     unsigned      initaref                                  :  4;
     unsigned      reserved3                                 :  4;
     unsigned      max_col_reg                               :  4;
     unsigned      reserved2                                 :  4;
     unsigned      odt_rd_map_cs0                            :  4;
     unsigned      reserved1                                 :  4;
     unsigned      odt_rd_map_cs1                            :  4;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_32_t;

/*! @struct ncp_denali_DENALI_CTL_33_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_33_t\n
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
 *     <td width="30%"> @param odt_wr_map_cs1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Determines which chip(s) will have termination when
 *        a write occurs on chip 1.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odt_wr_map_cs0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Determines which chip(s) will have termination when
 *        a write occurs on chip 0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odt_rd_map_cs3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Determines which chip(s) will have termination when
 *        a read occurs on chip 3.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odt_rd_map_cs2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Determines which chip(s) will have termination when
 *        a read occurs on chip 2.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_33
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      odt_wr_map_cs1                            :  4;
     unsigned      reserved1                                 :  4;
     unsigned      odt_wr_map_cs0                            :  4;
     unsigned      reserved2                                 :  4;
     unsigned      odt_rd_map_cs3                            :  4;
     unsigned      reserved3                                 :  4;
     unsigned      odt_rd_map_cs2                            :  4;
#else    /* Little Endian */
     unsigned      odt_rd_map_cs2                            :  4;
     unsigned      reserved3                                 :  4;
     unsigned      odt_rd_map_cs3                            :  4;
     unsigned      reserved2                                 :  4;
     unsigned      odt_wr_map_cs0                            :  4;
     unsigned      reserved1                                 :  4;
     unsigned      odt_wr_map_cs1                            :  4;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_33_t;

/*! @struct ncp_denali_DENALI_CTL_34_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_34_t\n
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
 *     <td width="30%"> @param rdlvl_dq_zero_count </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Number of consecutive 0s that defines a 1 to 0 transition
 *        for read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param port_cmd_error_type </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Type of error and access type that caused the PORT
 *        cmd error. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odt_wr_map_cs3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Determines which chip(s) will have termination when
 *        a write occurs on chip 3.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odt_wr_map_cs2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Determines which chip(s) will have termination when
 *        a write occurs on chip 2.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_34
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      rdlvl_dq_zero_count                       :  4;
     unsigned      reserved1                                 :  4;
     unsigned      port_cmd_error_type                       :  4;
     unsigned      reserved2                                 :  4;
     unsigned      odt_wr_map_cs3                            :  4;
     unsigned      reserved3                                 :  4;
     unsigned      odt_wr_map_cs2                            :  4;
#else    /* Little Endian */
     unsigned      odt_wr_map_cs2                            :  4;
     unsigned      reserved3                                 :  4;
     unsigned      odt_wr_map_cs3                            :  4;
     unsigned      reserved2                                 :  4;
     unsigned      port_cmd_error_type                       :  4;
     unsigned      reserved1                                 :  4;
     unsigned      rdlvl_dq_zero_count                       :  4;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_34_t;

/*! @struct ncp_denali_DENALI_CTL_35_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_35_t\n
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
 *     <td width="30%"> @param tdfi_phy_wrlat_base </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Sets DFI base value for the tPHY_WRLAT timing parameter. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_phy_wrlat </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Holds the calculated DFI tPHY_WRLAT timing parameter.
 *        READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_ctrlupd_min </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Holds the DFI tCTRLUPD_MIN timing parameter. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_dq_zero_count </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of consecutive 0s that defines a 1 to 0 transition
 *        for gate training.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_35
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      tdfi_phy_wrlat_base                       :  4;
     unsigned      reserved1                                 :  4;
     unsigned      tdfi_phy_wrlat                            :  4;
     unsigned      reserved2                                 :  4;
     unsigned      tdfi_ctrlupd_min                          :  4;
     unsigned      reserved3                                 :  4;
     unsigned      rdlvl_gate_dq_zero_count                  :  4;
#else    /* Little Endian */
     unsigned      rdlvl_gate_dq_zero_count                  :  4;
     unsigned      reserved3                                 :  4;
     unsigned      tdfi_ctrlupd_min                          :  4;
     unsigned      reserved2                                 :  4;
     unsigned      tdfi_phy_wrlat                            :  4;
     unsigned      reserved1                                 :  4;
     unsigned      tdfi_phy_wrlat_base                       :  4;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_35_t;

/*! @struct ncp_denali_DENALI_CTL_36_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_36_t\n
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
 *     <td width="30%"> @param twtr </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> DRAM TWTR parameter in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trp </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DRAM TRP parameter in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_wrlvl_en </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Minimum number of cycles from write leveling enable
 *        assertion to the first write leveling load.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_rdlvl_en </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Minimum number of cycles from read leveling enable
 *        assertion to the first read leveling load.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_36
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      twtr                                      :  4;
     unsigned      reserved1                                 :  4;
     unsigned      trp                                       :  4;
     unsigned      tdfi_wrlvl_en                             :  8;
     unsigned      tdfi_rdlvl_en                             :  8;
#else    /* Little Endian */
     unsigned      tdfi_rdlvl_en                             :  8;
     unsigned      tdfi_wrlvl_en                             :  8;
     unsigned      trp                                       :  4;
     unsigned      reserved1                                 :  4;
     unsigned      twtr                                      :  4;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_36_t;

/*! @struct ncp_denali_DENALI_CTL_37_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_37_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrr_param_value_err </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Errors/warnings related to the WRR parameters. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlat_adj </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Adjustment value for PHY write timing. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlat </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM WRLAT parameter in cycles. </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_37
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      reserved0                                 :  4;
     unsigned      wrr_param_value_err                       :  4;
     unsigned      reserved1                                 :  4;
     unsigned      wrlat_adj                                 :  4;
     unsigned      reserved2                                 :  4;
     unsigned      wrlat                                     :  4;
#else    /* Little Endian */
     unsigned      wrlat                                     :  4;
     unsigned      reserved2                                 :  4;
     unsigned      wrlat_adj                                 :  4;
     unsigned      reserved1                                 :  4;
     unsigned      wrr_param_value_err                       :  4;
     unsigned      reserved0                                 :  4;
     unsigned      obsolete3                                 :  8;
#endif
} ncp_denali_DENALI_CTL_37_t;

/*! @struct ncp_denali_DENALI_CTL_37_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_37_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrr_param_value_err </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Errors/warnings related to the WRR parameters. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlat_adj </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Adjustment value for PHY write timing. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlat </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM WRLAT parameter in cycles. </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_37
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      reserved0                                 :  4;
     unsigned      wrr_param_value_err                       :  4;
     unsigned      reserved1                                 :  3;
     unsigned      wrlat_adj                                 :  5;
     unsigned      reserved2                                 :  3;
     unsigned      wrlat                                     :  5;
#else    /* Little Endian */
     unsigned      wrlat                                     :  5;
     unsigned      reserved2                                 :  3;
     unsigned      wrlat_adj                                 :  5;
     unsigned      reserved1                                 :  3;
     unsigned      wrr_param_value_err                       :  4;
     unsigned      reserved0                                 :  4;
     unsigned      obsolete3                                 :  8;
#endif
} ncp_denali_DENALI_CTL_37_v2_t;

/*! @struct ncp_denali_DENALI_CTL_38_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_38_t\n
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
 *     <td width="30%"> @param ocd_adjust_pdn_cs_0 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> OCD pull-down adjust setting for DRAMs for chip select
 *        0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param max_row_reg </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Maximum width of memory address bus. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param caslat_lin_gate </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Adjusts data capture gate open by half cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param caslat_lin </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Sets latency from read cmd send to data receive from/to
 *        controller.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_38
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      ocd_adjust_pdn_cs_0                       :  5;
     unsigned      reserved1                                 :  3;
     unsigned      max_row_reg                               :  5;
     unsigned      reserved2                                 :  3;
     unsigned      caslat_lin_gate                           :  5;
     unsigned      reserved3                                 :  3;
     unsigned      caslat_lin                                :  5;
#else    /* Little Endian */
     unsigned      caslat_lin                                :  5;
     unsigned      reserved3                                 :  3;
     unsigned      caslat_lin_gate                           :  5;
     unsigned      reserved2                                 :  3;
     unsigned      max_row_reg                               :  5;
     unsigned      reserved1                                 :  3;
     unsigned      ocd_adjust_pdn_cs_0                       :  5;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_38_t;

/*! @struct ncp_denali_DENALI_CTL_38_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_38_v2_t\n
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
 *     <td width="30%"> @param ocd_adjust_pdn_cs_0 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> OCD pull-down adjust setting for DRAMs for chip select
 *        0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param max_row_reg </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Maximum width of memory address bus. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param caslat_lin_gate </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Adjusts data capture gate open by half cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param caslat_lin </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Sets latency from read cmd send to data receive from/to
 *        controller.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_38
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      ocd_adjust_pdn_cs_0                       :  5;
     unsigned      reserved1                                 :  3;
     unsigned      max_row_reg                               :  5;
     unsigned      reserved2                                 :  2;
     unsigned      caslat_lin_gate                           :  6;
     unsigned      reserved3                                 :  2;
     unsigned      caslat_lin                                :  6;
#else    /* Little Endian */
     unsigned      caslat_lin                                :  6;
     unsigned      reserved3                                 :  2;
     unsigned      caslat_lin_gate                           :  6;
     unsigned      reserved2                                 :  2;
     unsigned      max_row_reg                               :  5;
     unsigned      reserved1                                 :  3;
     unsigned      ocd_adjust_pdn_cs_0                       :  5;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_38_v2_t;

/*! @struct ncp_denali_DENALI_CTL_39_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_39_t\n
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
 *     <td width="30%"> @param tdal </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> DRAM TDAL parameter in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlat_adj </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Adjustment value for PHY read timing. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param out_of_range_type </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Type of cmd that caused an Out-of-Range interrupt.
 *        READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ocd_adjust_pup_cs_0 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> OCD pull-up adjust setting for DRAMs for chip select
 *        0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_39
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      tdal                                      :  5;
     unsigned      reserved1                                 :  3;
     unsigned      rdlat_adj                                 :  5;
     unsigned      reserved2                                 :  2;
     unsigned      out_of_range_type                         :  6;
     unsigned      reserved3                                 :  3;
     unsigned      ocd_adjust_pup_cs_0                       :  5;
#else    /* Little Endian */
     unsigned      ocd_adjust_pup_cs_0                       :  5;
     unsigned      reserved3                                 :  3;
     unsigned      out_of_range_type                         :  6;
     unsigned      reserved2                                 :  2;
     unsigned      rdlat_adj                                 :  5;
     unsigned      reserved1                                 :  3;
     unsigned      tdal                                      :  5;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_39_t;

/*! @struct ncp_denali_DENALI_CTL_39_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_39_v2_t\n
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
 *     <td width="30%"> @param tdal </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> DRAM TDAL parameter in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlat_adj </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Adjustment value for PHY read timing. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param out_of_range_type </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Type of cmd that caused an Out-of-Range interrupt.
 *        READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ocd_adjust_pup_cs_0 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> OCD pull-up adjust setting for DRAMs for chip select
 *        0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_39
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      tdal                                      :  5;
     unsigned      reserved1                                 :  2;
     unsigned      rdlat_adj                                 :  6;
     unsigned      reserved2                                 :  2;
     unsigned      out_of_range_type                         :  6;
     unsigned      reserved3                                 :  3;
     unsigned      ocd_adjust_pup_cs_0                       :  5;
#else    /* Little Endian */
     unsigned      ocd_adjust_pup_cs_0                       :  5;
     unsigned      reserved3                                 :  3;
     unsigned      out_of_range_type                         :  6;
     unsigned      reserved2                                 :  2;
     unsigned      rdlat_adj                                 :  6;
     unsigned      reserved1                                 :  2;
     unsigned      tdal                                      :  5;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_39_v2_t;

/*! @struct ncp_denali_DENALI_CTL_40_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_40_t\n
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
 *     <td width="30%"> @param tfaw </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> DRAM TFAW parameter in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_rddata_en_base </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Sets DFI base value for the tRDDATA_EN timing parameter. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_rddata_en </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Holds the calculated DFI tRDDATA_EN timing parameter.
 *        READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_phy_rdlat </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Holds the tPHY_RDLAT timing parameter. </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_40
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  2;
     unsigned      tfaw                                      :  6;
     unsigned      reserved1                                 :  3;
     unsigned      tdfi_rddata_en_base                       :  5;
     unsigned      reserved2                                 :  3;
     unsigned      tdfi_rddata_en                            :  5;
     unsigned      reserved3                                 :  3;
     unsigned      tdfi_phy_rdlat                            :  5;
#else    /* Little Endian */
     unsigned      tdfi_phy_rdlat                            :  5;
     unsigned      reserved3                                 :  3;
     unsigned      tdfi_rddata_en                            :  5;
     unsigned      reserved2                                 :  3;
     unsigned      tdfi_rddata_en_base                       :  5;
     unsigned      reserved1                                 :  3;
     unsigned      tfaw                                      :  6;
     unsigned      reserved0                                 :  2;
#endif
} ncp_denali_DENALI_CTL_40_t;

/*! @struct ncp_denali_DENALI_CTL_40_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_40_v2_t\n
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
 *     <td width="30%"> @param tfaw </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> DRAM TFAW parameter in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_rddata_en_base </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Sets DFI base value for the tRDDATA_EN timing parameter. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_rddata_en </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Holds the calculated DFI tRDDATA_EN timing parameter.
 *        READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_phy_rdlat </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Holds the tPHY_RDLAT timing parameter. </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_40
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  2;
     unsigned      tfaw                                      :  6;
     unsigned      reserved1                                 :  2;
     unsigned      tdfi_rddata_en_base                       :  6;
     unsigned      reserved2                                 :  2;
     unsigned      tdfi_rddata_en                            :  6;
     unsigned      reserved3                                 :  2;
     unsigned      tdfi_phy_rdlat                            :  6;
#else    /* Little Endian */
     unsigned      tdfi_phy_rdlat                            :  6;
     unsigned      reserved3                                 :  2;
     unsigned      tdfi_rddata_en                            :  6;
     unsigned      reserved2                                 :  2;
     unsigned      tdfi_rddata_en_base                       :  6;
     unsigned      reserved1                                 :  2;
     unsigned      tfaw                                      :  6;
     unsigned      reserved0                                 :  2;
#endif
} ncp_denali_DENALI_CTL_40_v2_t;

/*! @struct ncp_denali_DENALI_CTL_41_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_41_t\n
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
 *     <td width="30%"> @param addr_space </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Sets the number of address bits to check during BIST
 *        operation.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param twr_int </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DRAM TWR parameter in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trc </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DRAM TRC parameter in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tmrd </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM TMRD parameter in cycles. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_41
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  2;
     unsigned      addr_space                                :  6;
     unsigned      reserved1                                 :  3;
     unsigned      twr_int                                   :  5;
     unsigned      reserved2                                 :  2;
     unsigned      trc                                       :  6;
     unsigned      reserved3                                 :  3;
     unsigned      tmrd                                      :  5;
#else    /* Little Endian */
     unsigned      tmrd                                      :  5;
     unsigned      reserved3                                 :  3;
     unsigned      trc                                       :  6;
     unsigned      reserved2                                 :  2;
     unsigned      twr_int                                   :  5;
     unsigned      reserved1                                 :  3;
     unsigned      addr_space                                :  6;
     unsigned      reserved0                                 :  2;
#endif
} ncp_denali_DENALI_CTL_41_t;

/*! @struct ncp_denali_DENALI_CTL_42_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_42_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dll_rst_adj_dly </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Minimum number of cycles after setting master delay
 *        in DLL until reset is released.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dll_lock </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of delay elements in master DLL lock. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wlmrd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Delay from issuing MRS to first write leveling strobe. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wldqsen </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Delay from issuing MRS to first DQS strobe for write
 *        leveling.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_42
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      dll_rst_adj_dly                           :  8;
     unsigned      reserved0                                 :  1;
     unsigned      dll_lock                                  :  7;
     unsigned      reserved1                                 :  2;
     unsigned      wlmrd                                     :  6;
     unsigned      reserved2                                 :  2;
     unsigned      wldqsen                                   :  6;
#else    /* Little Endian */
     unsigned      wldqsen                                   :  6;
     unsigned      reserved2                                 :  2;
     unsigned      wlmrd                                     :  6;
     unsigned      reserved1                                 :  2;
     unsigned      dll_lock                                  :  7;
     unsigned      reserved0                                 :  1;
     unsigned      dll_rst_adj_dly                           :  8;
#endif
} ncp_denali_DENALI_CTL_42_t;

/*! @struct ncp_denali_DENALI_CTL_43_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_43_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param out_of_range_length </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Length of cmd that caused an Out-of-Range interrupt.
 *        READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_u_synd </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Syndrome for uncorrectable ECC event. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_c_synd </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Syndrome for correctable ECC event. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_43
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      out_of_range_length                       :  8;
     unsigned      ecc_u_synd                                :  8;
     unsigned      ecc_c_synd                                :  8;
#else    /* Little Endian */
     unsigned      ecc_c_synd                                :  8;
     unsigned      ecc_u_synd                                :  8;
     unsigned      out_of_range_length                       :  8;
     unsigned      obsolete3                                 :  8;
#endif
} ncp_denali_DENALI_CTL_43_t;

/*! @struct ncp_denali_DENALI_CTL_44_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_44_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_44
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_44_t;

/*! @struct ncp_denali_DENALI_CTL_45_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_45_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_45
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_45_t;

/*! @struct ncp_denali_DENALI_CTL_46_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_46_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_46
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_46_t;

/*! @struct ncp_denali_DENALI_CTL_47_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_47_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_47
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_47_t;

/*! @struct ncp_denali_DENALI_CTL_48_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_48_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_48
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_48_t;

/*! @struct ncp_denali_DENALI_CTL_49_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_49_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_49
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_49_t;

/*! @struct ncp_denali_DENALI_CTL_50_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_50_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_50
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_50_t;

/*! @struct ncp_denali_DENALI_CTL_51_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_51_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_51
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_51_t;

/*! @struct ncp_denali_DENALI_CTL_52_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_52_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_52
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_52_t;

/*! @struct ncp_denali_DENALI_CTL_53_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_53_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_53
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_53_t;

/*! @struct ncp_denali_DENALI_CTL_54_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_54_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_54
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_54_t;

/*! @struct ncp_denali_DENALI_CTL_55_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_55_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_55
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_55_t;

/*! @struct ncp_denali_DENALI_CTL_56_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_56_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_56
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_56_t;

/*! @struct ncp_denali_DENALI_CTL_57_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_57_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param refresh_per_zq </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Number of refreshes counted between automatic ZQCS
 *        commands.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_57
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      refresh_per_zq                            :  8;
     unsigned      obsolete0                                 : 24;
#else    /* Little Endian */
     unsigned      obsolete0                                 : 24;
     unsigned      refresh_per_zq                            :  8;
#endif
} ncp_denali_DENALI_CTL_57_t;

/*! @struct ncp_denali_DENALI_CTL_58_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_58_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param swlvl_resp_3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Leveling response for data slice 3. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param swlvl_resp_2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Leveling response for data slice 2. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param swlvl_resp_1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Leveling response for data slice 1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param swlvl_resp_0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Leveling response for data slice 0. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_58
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      swlvl_resp_3                              :  8;
     unsigned      swlvl_resp_2                              :  8;
     unsigned      swlvl_resp_1                              :  8;
     unsigned      swlvl_resp_0                              :  8;
#else    /* Little Endian */
     unsigned      swlvl_resp_0                              :  8;
     unsigned      swlvl_resp_1                              :  8;
     unsigned      swlvl_resp_2                              :  8;
     unsigned      swlvl_resp_3                              :  8;
#endif
} ncp_denali_DENALI_CTL_58_t;

/*! @struct ncp_denali_DENALI_CTL_59_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_59_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param swlvl_resp_7 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Leveling response for data slice 7. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param swlvl_resp_6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Leveling response for data slice 6. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param swlvl_resp_5 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Leveling response for data slice 5. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param swlvl_resp_4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Leveling response for data slice 4. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_59
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      swlvl_resp_7                              :  8;
     unsigned      swlvl_resp_6                              :  8;
     unsigned      swlvl_resp_5                              :  8;
     unsigned      swlvl_resp_4                              :  8;
#else    /* Little Endian */
     unsigned      swlvl_resp_4                              :  8;
     unsigned      swlvl_resp_5                              :  8;
     unsigned      swlvl_resp_6                              :  8;
     unsigned      swlvl_resp_7                              :  8;
#endif
} ncp_denali_DENALI_CTL_59_t;

/*! @struct ncp_denali_DENALI_CTL_60_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_60_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_rdlvl_resplat </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Number of cycles after a read level strobe until the
 *        response is valid.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_rdlvl_dll </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Minimum number of cycles for read leveling delay line
 *        to update after a load.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param swlvl_resp_8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Leveling response for data slice 8. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_60
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      tdfi_rdlvl_resplat                        :  8;
     unsigned      obsolete2                                 :  8;
     unsigned      tdfi_rdlvl_dll                            :  8;
     unsigned      swlvl_resp_8                              :  8;
#else    /* Little Endian */
     unsigned      swlvl_resp_8                              :  8;
     unsigned      tdfi_rdlvl_dll                            :  8;
     unsigned      obsolete2                                 :  8;
     unsigned      tdfi_rdlvl_resplat                        :  8;
#endif
} ncp_denali_DENALI_CTL_60_t;

/*! @struct ncp_denali_DENALI_CTL_61_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_61_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_wrlvl_resplat </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Number of cycles after a write level strobe until
 *        the response is valid.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_wrlvl_dll </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Minimum number of cycles for write leveling delay
 *        line to update after a load.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_61
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      tdfi_wrlvl_resplat                        :  8;
     unsigned      obsolete2                                 :  8;
     unsigned      tdfi_wrlvl_dll                            :  8;
     unsigned      obsolete0                                 :  8;
#else    /* Little Endian */
     unsigned      obsolete0                                 :  8;
     unsigned      tdfi_wrlvl_dll                            :  8;
     unsigned      obsolete2                                 :  8;
     unsigned      tdfi_wrlvl_resplat                        :  8;
#endif
} ncp_denali_DENALI_CTL_61_t;

/*! @struct ncp_denali_DENALI_CTL_62_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_62_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param trcd_int </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> DRAM TRCD parameter in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tras_min </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DRAM TRAS_MIN parameter in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tmod </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Number of clock cycles after MRS command and before
 *        any other command.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_62
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      trcd_int                                  :  8;
     unsigned      tras_min                                  :  8;
     unsigned      tmod                                      :  8;
     unsigned      obsolete0                                 :  8;
#else    /* Little Endian */
     unsigned      obsolete0                                 :  8;
     unsigned      tmod                                      :  8;
     unsigned      tras_min                                  :  8;
     unsigned      trcd_int                                  :  8;
#endif
} ncp_denali_DENALI_CTL_62_t;

/*! @struct ncp_denali_DENALI_CTL_63_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_63_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_priority_relax </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Counter value to trigger priority relax on port 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trfc </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM TRFC parameter in cycles. </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_63
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_priority_relax                       : 10;
     unsigned      trfc                                      :  8;
#else    /* Little Endian */
     unsigned      trfc                                      :  8;
     unsigned      axi0_priority_relax                       : 10;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_63_t;

/*! @struct ncp_denali_DENALI_CTL_63_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_63_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_priority_relax </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Counter value to trigger priority relax on port 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_63
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_priority_relax                       : 10;
     unsigned      obsolete0                                 :  8;
#else    /* Little Endian */
     unsigned      obsolete0                                 :  8;
     unsigned      axi0_priority_relax                       : 10;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_63_v2_t;

/*! @struct ncp_denali_DENALI_CTL_64_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_64_t\n
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
 *     <td width="30%"> @param axi2_priority_relax </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Counter value to trigger priority relax on port 2. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi1_priority_relax </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Counter value to trigger priority relax on port 1. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_64
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      axi2_priority_relax                       : 10;
     unsigned      reserved1                                 :  6;
     unsigned      axi1_priority_relax                       : 10;
#else    /* Little Endian */
     unsigned      axi1_priority_relax                       : 10;
     unsigned      reserved1                                 :  6;
     unsigned      axi2_priority_relax                       : 10;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_64_t;

/*! @struct ncp_denali_DENALI_CTL_65_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_65_t\n
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
 *     <td width="30%"> @param zqcs </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of clock cycles needed for a ZQCS command. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi3_priority_relax </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Counter value to trigger priority relax on port 3. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_65
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      zqcs                                      : 12;
     unsigned      reserved1                                 :  6;
     unsigned      axi3_priority_relax                       : 10;
#else    /* Little Endian */
     unsigned      axi3_priority_relax                       : 10;
     unsigned      reserved1                                 :  6;
     unsigned      zqcs                                      : 12;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_65_t;

/*! @struct ncp_denali_DENALI_CTL_66_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_66_t\n
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
 *     <td width="30%"> @param ecc_c_id </td>
 *     <td width="20%" align="center"> 14 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Source ID associated with correctable ECC event. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_66
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  2;
     unsigned      ecc_c_id                                  : 14;
     unsigned      obsolete0                                 : 16;
#else    /* Little Endian */
     unsigned      obsolete0                                 : 16;
     unsigned      ecc_c_id                                  : 14;
     unsigned      reserved0                                 :  2;
#endif
} ncp_denali_DENALI_CTL_66_t;

/*! @struct ncp_denali_DENALI_CTL_67_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_67_t\n
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
 *     <td width="30%"> @param out_of_range_source_id </td>
 *     <td width="20%" align="center"> 14 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Source ID of cmd that caused an Out-of-Range interrupt.
 *        READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_u_id </td>
 *     <td width="20%" align="center"> 14 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Source ID associated with the uncorrectable ECC event.
 *        READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_67
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  2;
     unsigned      out_of_range_source_id                    : 14;
     unsigned      reserved1                                 :  2;
     unsigned      ecc_u_id                                  : 14;
#else    /* Little Endian */
     unsigned      ecc_u_id                                  : 14;
     unsigned      reserved1                                 :  2;
     unsigned      out_of_range_source_id                    : 14;
     unsigned      reserved0                                 :  2;
#endif
} ncp_denali_DENALI_CTL_67_t;

/*! @struct ncp_denali_DENALI_CTL_68_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_68_t\n
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
 *     <td width="30%"> @param port_data_error_id </td>
 *     <td width="20%" align="center"> 14 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Source ID of cmd that caused the PORT data error.
 *        READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param port_cmd_error_id </td>
 *     <td width="20%" align="center"> 14 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Source ID of cmd that caused the PORT cmd error. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_68
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  2;
     unsigned      port_data_error_id                        : 14;
     unsigned      reserved1                                 :  2;
     unsigned      port_cmd_error_id                         : 14;
#else    /* Little Endian */
     unsigned      port_cmd_error_id                         : 14;
     unsigned      reserved1                                 :  2;
     unsigned      port_data_error_id                        : 14;
     unsigned      reserved0                                 :  2;
#endif
} ncp_denali_DENALI_CTL_68_t;

/*! @struct ncp_denali_DENALI_CTL_69_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_69_t\n
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
 *     <td width="30%"> @param tdfi_phyupd_resp </td>
 *     <td width="20%" align="center"> 14 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Holds the DFI tPHYUPD_RESP timing parameter. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_ctrlupd_max </td>
 *     <td width="20%" align="center"> 14 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Holds the DFI tCTRLUPD_MAX timing parameter. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_69
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  2;
     unsigned      tdfi_phyupd_resp                          : 14;
     unsigned      reserved1                                 :  2;
     unsigned      tdfi_ctrlupd_max                          : 14;
#else    /* Little Endian */
     unsigned      tdfi_ctrlupd_max                          : 14;
     unsigned      reserved1                                 :  2;
     unsigned      tdfi_phyupd_resp                          : 14;
     unsigned      reserved0                                 :  2;
#endif
} ncp_denali_DENALI_CTL_69_t;

/*! @struct ncp_denali_DENALI_CTL_70_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_70_t\n
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
 *     <td width="30%"> @param tref </td>
 *     <td width="20%" align="center"> 14 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DRAM TREF parameter in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_phyupd_type0 </td>
 *     <td width="20%" align="center"> 14 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Holds the DFI tPHYUPD_TYPE0 timing parameter. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_70
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  2;
     unsigned      tref                                      : 14;
     unsigned      reserved1                                 :  2;
     unsigned      tdfi_phyupd_type0                         : 14;
#else    /* Little Endian */
     unsigned      tdfi_phyupd_type0                         : 14;
     unsigned      reserved1                                 :  2;
     unsigned      tref                                      : 14;
     unsigned      reserved0                                 :  2;
#endif
} ncp_denali_DENALI_CTL_70_t;

/*! @struct ncp_denali_DENALI_CTL_71_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_71_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param axi1_en_size_lt_width_instr </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Allow narrow instructions from AXI port 1 requestors
 *        with bit enabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_en_size_lt_width_instr </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allow narrow instructions from AXI port 0 requestors
 *        with bit enabled.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_71
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      axi1_en_size_lt_width_instr               : 16;
     unsigned      axi0_en_size_lt_width_instr               : 16;
#else    /* Little Endian */
     unsigned      axi0_en_size_lt_width_instr               : 16;
     unsigned      axi1_en_size_lt_width_instr               : 16;
#endif
} ncp_denali_DENALI_CTL_71_t;

/*! @struct ncp_denali_DENALI_CTL_72_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_72_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param axi3_en_size_lt_width_instr </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Allow narrow instructions from AXI port 3 requestors
 *        with bit enabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2_en_size_lt_width_instr </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allow narrow instructions from AXI port 2 requestors
 *        with bit enabled.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_72
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      axi3_en_size_lt_width_instr               : 16;
     unsigned      axi2_en_size_lt_width_instr               : 16;
#else    /* Little Endian */
     unsigned      axi2_en_size_lt_width_instr               : 16;
     unsigned      axi3_en_size_lt_width_instr               : 16;
#endif
} ncp_denali_DENALI_CTL_72_t;

/*! @struct ncp_denali_DENALI_CTL_73_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_73_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dll_rst_delay </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Minimum number of cycles required for DLL reset. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_73
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      dll_rst_delay                             : 16;
#else    /* Little Endian */
     unsigned      dll_rst_delay                             : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_73_t;

/*! @struct ncp_denali_DENALI_CTL_74_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_74_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_74
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_74_t;

/*! @struct ncp_denali_DENALI_CTL_75_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_75_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_75
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_75_t;

/*! @struct ncp_denali_DENALI_CTL_76_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_76_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_76
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_76_t;

/*! @struct ncp_denali_DENALI_CTL_77_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_77_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_77
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_77_t;

/*! @struct ncp_denali_DENALI_CTL_78_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_78_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_78
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_78_t;

/*! @struct ncp_denali_DENALI_CTL_79_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_79_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_79
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_79_t;

/*! @struct ncp_denali_DENALI_CTL_80_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_80_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_80
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_80_t;

/*! @struct ncp_denali_DENALI_CTL_81_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_81_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param refresh_per_rdlvl </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of refreshes counted between automatic read
 *        leveling commands.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_81
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      refresh_per_rdlvl                         : 16;
     unsigned      obsolete0                                 : 16;
#else    /* Little Endian */
     unsigned      obsolete0                                 : 16;
     unsigned      refresh_per_rdlvl                         : 16;
#endif
} ncp_denali_DENALI_CTL_81_t;

/*! @struct ncp_denali_DENALI_CTL_81_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_81_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_81
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_81_v2_t;

/*! @struct ncp_denali_DENALI_CTL_82_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_82_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param tcpd </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DRAM TCPD parameter in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param refresh_per_rdlvl_gate </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of refreshes counted between automatic gate
 *        training commands.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_82
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      tcpd                                      : 16;
     unsigned      refresh_per_rdlvl_gate                    : 16;
#else    /* Little Endian */
     unsigned      refresh_per_rdlvl_gate                    : 16;
     unsigned      tcpd                                      : 16;
#endif
} ncp_denali_DENALI_CTL_82_t;

/*! @struct ncp_denali_DENALI_CTL_82_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_82_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param tcpd </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DRAM TCPD parameter in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_82
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      tcpd                                      : 16;
     unsigned      obsolete0                                 : 16;
#else    /* Little Endian */
     unsigned      obsolete0                                 : 16;
     unsigned      tcpd                                      : 16;
#endif
} ncp_denali_DENALI_CTL_82_v2_t;

/*! @struct ncp_denali_DENALI_CTL_83_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_83_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_83
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_83_t;

/*! @struct ncp_denali_DENALI_CTL_84_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_84_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param tpdex </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DRAM TPDEX parameter in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdll </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM TDLL parameter in cycles. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_84
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      tpdex                                     : 16;
     unsigned      tdll                                      : 16;
#else    /* Little Endian */
     unsigned      tdll                                      : 16;
     unsigned      tpdex                                     : 16;
#endif
} ncp_denali_DENALI_CTL_84_t;

/*! @struct ncp_denali_DENALI_CTL_85_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_85_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param txpdll </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DRAM TXPDLL parameter in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tras_max </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM TRAS_MAX parameter in cycles. </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_85
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      txpdll                                    : 16;
     unsigned      tras_max                                  : 16;
#else    /* Little Endian */
     unsigned      tras_max                                  : 16;
     unsigned      txpdll                                    : 16;
#endif
} ncp_denali_DENALI_CTL_85_t;

/*! @struct ncp_denali_DENALI_CTL_85_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_85_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param txpdll </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DRAM TXPDLL parameter in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_85
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      txpdll                                    : 16;
     unsigned      obsolete0                                 : 16;
#else    /* Little Endian */
     unsigned      obsolete0                                 : 16;
     unsigned      txpdll                                    : 16;
#endif
} ncp_denali_DENALI_CTL_85_v2_t;

/*! @struct ncp_denali_DENALI_CTL_86_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_86_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param txsr </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DRAM TXSR parameter in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param txsnr </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM TXSNR parameter in cycles. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_86
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      txsr                                      : 16;
     unsigned      txsnr                                     : 16;
#else    /* Little Endian */
     unsigned      txsnr                                     : 16;
     unsigned      txsr                                      : 16;
#endif
} ncp_denali_DENALI_CTL_86_t;

/*! @struct ncp_denali_DENALI_CTL_87_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_87_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_interval </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of refreshes counted between automatic write
 *        leveling commands.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param version </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Controller version number. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_87
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      wrlvl_interval                            : 16;
     unsigned      version                                   : 16;
#else    /* Little Endian */
     unsigned      version                                   : 16;
     unsigned      wrlvl_interval                            : 16;
#endif
} ncp_denali_DENALI_CTL_87_t;

/*! @struct ncp_denali_DENALI_CTL_87_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_87_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param version </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Controller version number. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_87
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      version                                   : 16;
#else    /* Little Endian */
     unsigned      version                                   : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_87_v2_t;

/*! @struct ncp_denali_DENALI_CTL_88_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_88_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param xor_check_bits </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Value to xor with generated ECC codes for forced write
 *        check.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_88
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      xor_check_bits                            : 16;
#else    /* Little Endian */
     unsigned      xor_check_bits                            : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_88_t;

/*! @struct ncp_denali_DENALI_CTL_89_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_89_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param int_ack </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Clear mask of the INT_STATUS parameter. WRITE-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_89
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      int_ack                                   : 18;
#else    /* Little Endian */
     unsigned      int_ack                                   : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_89_t;

/*! @struct ncp_denali_DENALI_CTL_89_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_89_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param int_ack </td>
 *     <td width="20%" align="center"> 20 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Clear mask of the INT_STATUS parameter. WRITE-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_89
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  4;
     unsigned      int_ack                                   : 20;
#else    /* Little Endian */
     unsigned      int_ack                                   : 20;
     unsigned      reserved0                                 :  4;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_89_v2_t;

/*! @struct ncp_denali_DENALI_CTL_90_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_90_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param int_mask </td>
 *     <td width="20%" align="center"> 19 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Mask for controller_int signals from the INT_STATUS
 *        parameter.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_90
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  5;
     unsigned      int_mask                                  : 19;
#else    /* Little Endian */
     unsigned      int_mask                                  : 19;
     unsigned      reserved0                                 :  5;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_90_t;

/*! @struct ncp_denali_DENALI_CTL_90_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_90_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param int_mask </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Mask for controller_int signals from the INT_STATUS
 *        parameter.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_90
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  3;
     unsigned      int_mask                                  : 21;
#else    /* Little Endian */
     unsigned      int_mask                                  : 21;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_90_v2_t;

/*! @struct ncp_denali_DENALI_CTL_91_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_91_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param int_status </td>
 *     <td width="20%" align="center"> 19 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Status of interrupt features in the controller. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_91
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  5;
     unsigned      int_status                                : 19;
#else    /* Little Endian */
     unsigned      int_status                                : 19;
     unsigned      reserved0                                 :  5;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_91_t;

/*! @struct ncp_denali_DENALI_CTL_91_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_91_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param int_status </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Status of interrupt features in the controller. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_91
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  3;
     unsigned      int_status                                : 21;
#else    /* Little Endian */
     unsigned      int_status                                : 21;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_91_v2_t;

/*! @struct ncp_denali_DENALI_CTL_92_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_92_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_status </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Holds the status from the most recent write leveling
 *        operation. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_92
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      wrlvl_status                              : 18;
#else    /* Little Endian */
     unsigned      wrlvl_status                              : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_92_t;

/*! @struct ncp_denali_DENALI_CTL_92_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_92_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_status </td>
 *     <td width="20%" align="center"> 20 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Holds the status from the most recent write leveling
 *        operation. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_92
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  4;
     unsigned      wrlvl_status                              : 20;
#else    /* Little Endian */
     unsigned      wrlvl_status                              : 20;
     unsigned      reserved0                                 :  4;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_92_v2_t;

/*! @struct ncp_denali_DENALI_CTL_93_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_93_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tinit </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM TINIT parameter in cycles. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_93
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      tinit                                     : 24;
#else    /* Little Endian */
     unsigned      tinit                                     : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_93_t;

/*! @struct ncp_denali_DENALI_CTL_94_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_94_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cke_inactive </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Duration of memory RESET during power-on initialization. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_94
 */
 
typedef struct
{
     unsigned  int              cke_inactive;
} ncp_denali_DENALI_CTL_94_t;

/*! @struct ncp_denali_DENALI_CTL_95_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_95_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dfi_wrlvl_max_delay </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Maximum number of elements for the write level delay
 *        line.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_95
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      dfi_wrlvl_max_delay                       : 16;
#else    /* Little Endian */
     unsigned      dfi_wrlvl_max_delay                       : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_95_t;

/*! @struct ncp_denali_DENALI_CTL_96_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_96_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_96
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_96_t;

/*! @struct ncp_denali_DENALI_CTL_97_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_97_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dll_ctrl_reg_0_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Controls the DLL bypass logic, Dll start point and
 *        holds the read DQS delay settings for data slice 0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_97
 */
 
typedef struct
{
     unsigned  int          dll_ctrl_reg_0_0;
} ncp_denali_DENALI_CTL_97_t;

/*! @struct ncp_denali_DENALI_CTL_97_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_97_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_97
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_97_v2_t;

/*! @struct ncp_denali_DENALI_CTL_98_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_98_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dll_ctrl_reg_0_1 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Controls the DLL bypass logic, Dll start point and
 *        holds the read DQS delay settings for data slice 1.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_98
 */
 
typedef struct
{
     unsigned  int          dll_ctrl_reg_0_1;
} ncp_denali_DENALI_CTL_98_t;

/*! @struct ncp_denali_DENALI_CTL_98_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_98_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_98
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_98_v2_t;

/*! @struct ncp_denali_DENALI_CTL_99_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_99_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dll_ctrl_reg_0_2 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Controls the DLL bypass logic, Dll start point and
 *        holds the read DQS delay settings for data slice 2.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_99
 */
 
typedef struct
{
     unsigned  int          dll_ctrl_reg_0_2;
} ncp_denali_DENALI_CTL_99_t;

/*! @struct ncp_denali_DENALI_CTL_99_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_99_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_99
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_99_v2_t;

/*! @struct ncp_denali_DENALI_CTL_100_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_100_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dll_ctrl_reg_0_3 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Controls the DLL bypass logic, Dll start point and
 *        holds the read DQS delay settings for data slice 3.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_100
 */
 
typedef struct
{
     unsigned  int          dll_ctrl_reg_0_3;
} ncp_denali_DENALI_CTL_100_t;

/*! @struct ncp_denali_DENALI_CTL_100_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_100_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_100
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_100_v2_t;

/*! @struct ncp_denali_DENALI_CTL_101_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_101_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dll_ctrl_reg_0_4 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Controls the DLL bypass logic, Dll start point and
 *        holds the read DQS delay settings for data slice 4.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_101
 */
 
typedef struct
{
     unsigned  int          dll_ctrl_reg_0_4;
} ncp_denali_DENALI_CTL_101_t;

/*! @struct ncp_denali_DENALI_CTL_101_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_101_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_101
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_101_v2_t;

/*! @struct ncp_denali_DENALI_CTL_102_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_102_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dll_ctrl_reg_0_5 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Controls the DLL bypass logic, Dll start point and
 *        holds the read DQS delay settings for data slice 5.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_102
 */
 
typedef struct
{
     unsigned  int          dll_ctrl_reg_0_5;
} ncp_denali_DENALI_CTL_102_t;

/*! @struct ncp_denali_DENALI_CTL_102_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_102_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_102
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_102_v2_t;

/*! @struct ncp_denali_DENALI_CTL_103_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_103_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dll_ctrl_reg_0_6 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Controls the DLL bypass logic, Dll start point and
 *        holds the read DQS delay settings for data slice 6.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_103
 */
 
typedef struct
{
     unsigned  int          dll_ctrl_reg_0_6;
} ncp_denali_DENALI_CTL_103_t;

/*! @struct ncp_denali_DENALI_CTL_103_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_103_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_103
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_103_v2_t;

/*! @struct ncp_denali_DENALI_CTL_104_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_104_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dll_ctrl_reg_0_7 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Controls the DLL bypass logic, Dll start point and
 *        holds the read DQS delay settings for data slice 7.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_104
 */
 
typedef struct
{
     unsigned  int          dll_ctrl_reg_0_7;
} ncp_denali_DENALI_CTL_104_t;

/*! @struct ncp_denali_DENALI_CTL_104_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_104_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_104
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_104_v2_t;

/*! @struct ncp_denali_DENALI_CTL_105_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_105_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dll_ctrl_reg_0_8 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Controls the DLL bypass logic, Dll start point and
 *        holds the read DQS delay settings for data slice 8.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_105
 */
 
typedef struct
{
     unsigned  int          dll_ctrl_reg_0_8;
} ncp_denali_DENALI_CTL_105_t;

/*! @struct ncp_denali_DENALI_CTL_105_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_105_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_105
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_105_v2_t;

/*! @struct ncp_denali_DENALI_CTL_106_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_106_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_106
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_106_t;

/*! @struct ncp_denali_DENALI_CTL_107_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_107_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_107
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_107_t;

/*! @struct ncp_denali_DENALI_CTL_108_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_108_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_108
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_108_t;

/*! @struct ncp_denali_DENALI_CTL_109_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_109_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_109
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_109_t;

/*! @struct ncp_denali_DENALI_CTL_110_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_110_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_110
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_110_t;

/*! @struct ncp_denali_DENALI_CTL_111_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_111_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_111
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_111_t;

/*! @struct ncp_denali_DENALI_CTL_112_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_112_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_112
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_112_t;

/*! @struct ncp_denali_DENALI_CTL_113_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_113_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_113
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_113_t;

/*! @struct ncp_denali_DENALI_CTL_114_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_114_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_114
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_114_t;

/*! @struct ncp_denali_DENALI_CTL_115_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_115_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_115
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_115_t;

/*! @struct ncp_denali_DENALI_CTL_116_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_116_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_116
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_116_t;

/*! @struct ncp_denali_DENALI_CTL_117_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_117_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_117
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_117_t;

/*! @struct ncp_denali_DENALI_CTL_118_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_118_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_118
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_118_t;

/*! @struct ncp_denali_DENALI_CTL_119_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_119_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_119
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_119_t;

/*! @struct ncp_denali_DENALI_CTL_120_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_120_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_120
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_120_t;

/*! @struct ncp_denali_DENALI_CTL_121_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_121_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_121
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_121_t;

/*! @struct ncp_denali_DENALI_CTL_122_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_122_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_122
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_122_t;

/*! @struct ncp_denali_DENALI_CTL_123_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_123_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_123
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_123_t;

/*! @struct ncp_denali_DENALI_CTL_124_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_124_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_124
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_124_t;

/*! @struct ncp_denali_DENALI_CTL_125_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_125_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_125
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_125_t;

/*! @struct ncp_denali_DENALI_CTL_126_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_126_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param trst_pwron </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Duration of memory RESET during power-on initialization. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_126
 */
 
typedef struct
{
     unsigned  int                trst_pwron;
} ncp_denali_DENALI_CTL_126_t;

/*! @struct ncp_denali_DENALI_CTL_127_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_127_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param user_def_reg_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> User-defined output register 0. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_127
 */
 
typedef struct
{
     unsigned  int            user_def_reg_0;
} ncp_denali_DENALI_CTL_127_t;

/*! @struct ncp_denali_DENALI_CTL_128_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_128_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param user_def_reg_1 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> User-defined output register 1. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_128
 */
 
typedef struct
{
     unsigned  int            user_def_reg_1;
} ncp_denali_DENALI_CTL_128_t;

/*! @struct ncp_denali_DENALI_CTL_129_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_129_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param user_def_reg_ro_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> User-defined input register 0. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_129
 */
 
typedef struct
{
     unsigned  int         user_def_reg_ro_0;
} ncp_denali_DENALI_CTL_129_t;

/*! @struct ncp_denali_DENALI_CTL_130_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_130_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param user_def_reg_ro_1 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> User-defined input register 1. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_130
 */
 
typedef struct
{
     unsigned  int         user_def_reg_ro_1;
} ncp_denali_DENALI_CTL_130_t;

/*! @struct ncp_denali_DENALI_CTL_131_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_131_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param user_def_reg_ro_2 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> User-defined input register 2. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_131
 */
 
typedef struct
{
     unsigned  int         user_def_reg_ro_2;
} ncp_denali_DENALI_CTL_131_t;

/*! @struct ncp_denali_DENALI_CTL_132_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_132_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param user_def_reg_ro_3 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> User-defined input register 3. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_132
 */
 
typedef struct
{
     unsigned  int         user_def_reg_ro_3;
} ncp_denali_DENALI_CTL_132_t;

/*! @struct ncp_denali_DENALI_CTL_133_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_133_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param user_def_reg_ro_4 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> User-defined input register 4. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_133
 */
 
typedef struct
{
     unsigned  int         user_def_reg_ro_4;
} ncp_denali_DENALI_CTL_133_t;

/*! @struct ncp_denali_DENALI_CTL_134_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_134_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param user_def_reg_ro_5 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> User-defined input register 5. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_134
 */
 
typedef struct
{
     unsigned  int         user_def_reg_ro_5;
} ncp_denali_DENALI_CTL_134_t;

/*! @struct ncp_denali_DENALI_CTL_135_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_135_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param user_def_reg_ro_6 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> User-defined input register 6. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_135
 */
 
typedef struct
{
     unsigned  int         user_def_reg_ro_6;
} ncp_denali_DENALI_CTL_135_t;

/*! @struct ncp_denali_DENALI_CTL_136_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_136_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param user_def_reg_ro_7 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> User-defined input register 7. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_136
 */
 
typedef struct
{
     unsigned  int         user_def_reg_ro_7;
} ncp_denali_DENALI_CTL_136_t;

/*! @struct ncp_denali_DENALI_CTL_137_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_137_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_delay_0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for write data slice 0. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_137
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      wrlvl_delay_0                             : 16;
#else    /* Little Endian */
     unsigned      wrlvl_delay_0                             : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_137_t;

/*! @struct ncp_denali_DENALI_CTL_138_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_138_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_delay_1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for write data slice 1. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_138
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      wrlvl_delay_1                             : 16;
#else    /* Little Endian */
     unsigned      wrlvl_delay_1                             : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_138_t;

/*! @struct ncp_denali_DENALI_CTL_139_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_139_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_delay_2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for write data slice 2. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_139
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      wrlvl_delay_2                             : 16;
#else    /* Little Endian */
     unsigned      wrlvl_delay_2                             : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_139_t;

/*! @struct ncp_denali_DENALI_CTL_140_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_140_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_delay_3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for write data slice 3. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_140
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      wrlvl_delay_3                             : 16;
#else    /* Little Endian */
     unsigned      wrlvl_delay_3                             : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_140_t;

/*! @struct ncp_denali_DENALI_CTL_141_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_141_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_delay_4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for write data slice 4. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_141
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      wrlvl_delay_4                             : 16;
#else    /* Little Endian */
     unsigned      wrlvl_delay_4                             : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_141_t;

/*! @struct ncp_denali_DENALI_CTL_142_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_142_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_delay_5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for write data slice 5. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_142
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      wrlvl_delay_5                             : 16;
#else    /* Little Endian */
     unsigned      wrlvl_delay_5                             : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_142_t;

/*! @struct ncp_denali_DENALI_CTL_143_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_143_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_delay_6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for write data slice 6. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_143
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      wrlvl_delay_6                             : 16;
#else    /* Little Endian */
     unsigned      wrlvl_delay_6                             : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_143_t;

/*! @struct ncp_denali_DENALI_CTL_144_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_144_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_delay_7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for write data slice 7. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_144
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      wrlvl_delay_7                             : 16;
#else    /* Little Endian */
     unsigned      wrlvl_delay_7                             : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_144_t;

/*! @struct ncp_denali_DENALI_CTL_145_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_145_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_delay_8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for write data slice 8. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_145
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      wrlvl_delay_8                             : 16;
#else    /* Little Endian */
     unsigned      wrlvl_delay_8                             : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_145_t;

/*! @struct ncp_denali_DENALI_CTL_146_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_146_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param bist_fail_addr </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address of BIST error. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_146
 */
 
typedef struct
{
     unsigned  int            bist_fail_addr;
} ncp_denali_DENALI_CTL_146_t;

/*! @struct ncp_denali_DENALI_CTL_147_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_147_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bist_fail_addr </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address of BIST error. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_147
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  3;
     unsigned      bist_fail_addr                            :  5;
#else    /* Little Endian */
     unsigned      bist_fail_addr                            :  5;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_147_t;

/*! @struct ncp_denali_DENALI_CTL_148_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_148_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param bist_start_address </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start BIST checking at this address. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_148
 */
 
typedef struct
{
     unsigned  int        bist_start_address;
} ncp_denali_DENALI_CTL_148_t;

/*! @struct ncp_denali_DENALI_CTL_149_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_149_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bist_start_address </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start BIST checking at this address. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_149
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  3;
     unsigned      bist_start_address                        :  5;
#else    /* Little Endian */
     unsigned      bist_start_address                        :  5;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_149_t;

/*! @struct ncp_denali_DENALI_CTL_150_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_150_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_c_addr </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address of correctable ECC event. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_150
 */
 
typedef struct
{
     unsigned  int                ecc_c_addr;
} ncp_denali_DENALI_CTL_150_t;

/*! @struct ncp_denali_DENALI_CTL_151_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_151_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_c_addr </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address of correctable ECC event. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_151
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  3;
     unsigned      ecc_c_addr                                :  5;
#else    /* Little Endian */
     unsigned      ecc_c_addr                                :  5;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_151_t;

/*! @struct ncp_denali_DENALI_CTL_152_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_152_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_u_addr </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address of uncorrectable ECC event. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_152
 */
 
typedef struct
{
     unsigned  int                ecc_u_addr;
} ncp_denali_DENALI_CTL_152_t;

/*! @struct ncp_denali_DENALI_CTL_153_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_153_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_u_addr </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address of uncorrectable ECC event. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_153
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  3;
     unsigned      ecc_u_addr                                :  5;
#else    /* Little Endian */
     unsigned      ecc_u_addr                                :  5;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_153_t;

/*! @struct ncp_denali_DENALI_CTL_154_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_154_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param out_of_range_addr </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address of cmd that caused an Out-of-Range interrupt.
 *        READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_154
 */
 
typedef struct
{
     unsigned  int         out_of_range_addr;
} ncp_denali_DENALI_CTL_154_t;

/*! @struct ncp_denali_DENALI_CTL_155_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_155_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param out_of_range_addr </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address of cmd that caused an Out-of-Range interrupt.
 *        READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_155
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  3;
     unsigned      out_of_range_addr                         :  5;
#else    /* Little Endian */
     unsigned      out_of_range_addr                         :  5;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_155_t;

/*! @struct ncp_denali_DENALI_CTL_156_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_156_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param port_cmd_error_addr </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address of port that caused the PORT cmd error. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_156
 */
 
typedef struct
{
     unsigned  int       port_cmd_error_addr;
} ncp_denali_DENALI_CTL_156_t;

/*! @struct ncp_denali_DENALI_CTL_157_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_157_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param port_cmd_error_addr </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address of port that caused the PORT cmd error. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_157
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  3;
     unsigned      port_cmd_error_addr                       :  5;
#else    /* Little Endian */
     unsigned      port_cmd_error_addr                       :  5;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_157_t;

/*! @struct ncp_denali_DENALI_CTL_158_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_158_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_error_status </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies the source of any read leveling errors. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_158
 */
 
typedef struct
{
     unsigned  int        rdlvl_error_status;
} ncp_denali_DENALI_CTL_158_t;

/*! @struct ncp_denali_DENALI_CTL_159_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_159_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_error_status </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies the source of any read leveling errors. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_159
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      rdlvl_error_status                        :  6;
#else    /* Little Endian */
     unsigned      rdlvl_error_status                        :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_159_t;

/*! @struct ncp_denali_DENALI_CTL_160_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_160_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param bist_data_mask </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Mask applied to data for BIST error checking. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_160
 */
 
typedef struct
{
     unsigned  int            bist_data_mask;
} ncp_denali_DENALI_CTL_160_t;

/*! @struct ncp_denali_DENALI_CTL_161_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_161_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param bist_data_mask </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Mask applied to data for BIST error checking. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_161
 */
 
typedef struct
{
     unsigned  int            bist_data_mask;
} ncp_denali_DENALI_CTL_161_t;

/*! @struct ncp_denali_DENALI_CTL_162_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_162_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_c_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data associated with correctable ECC event. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_162
 */
 
typedef struct
{
     unsigned  int                ecc_c_data;
} ncp_denali_DENALI_CTL_162_t;

/*! @struct ncp_denali_DENALI_CTL_163_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_163_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_c_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data associated with correctable ECC event. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_163
 */
 
typedef struct
{
     unsigned  int                ecc_c_data;
} ncp_denali_DENALI_CTL_163_t;

/*! @struct ncp_denali_DENALI_CTL_164_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_164_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_u_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data associated with uncorrectable ECC event. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_164
 */
 
typedef struct
{
     unsigned  int                ecc_u_data;
} ncp_denali_DENALI_CTL_164_t;

/*! @struct ncp_denali_DENALI_CTL_165_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_165_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_u_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data associated with uncorrectable ECC event. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_165
 */
 
typedef struct
{
     unsigned  int                ecc_u_data;
} ncp_denali_DENALI_CTL_165_t;

/*! @struct ncp_denali_DENALI_CTL_166_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_166_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_resp_mask </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Mask for dfi_rdlvl_resp during gate training. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_166
 */
 
typedef struct
{
     unsigned  int      rdlvl_gate_resp_mask;
} ncp_denali_DENALI_CTL_166_t;

/*! @struct ncp_denali_DENALI_CTL_167_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_167_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_resp_mask </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Mask for dfi_rdlvl_resp during gate training. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_167
 */
 
typedef struct
{
     unsigned  int      rdlvl_gate_resp_mask;
} ncp_denali_DENALI_CTL_167_t;

/*! @struct ncp_denali_DENALI_CTL_168_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_168_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_resp_mask </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Mask for dfi_rdlvl_resp during gate training. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_168
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      rdlvl_gate_resp_mask                      :  8;
#else    /* Little Endian */
     unsigned      rdlvl_gate_resp_mask                      :  8;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_168_t;

/*! @struct ncp_denali_DENALI_CTL_169_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_169_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_resp_mask </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Mask for dfi_rdlvl_resp during read leveling. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_169
 */
 
typedef struct
{
     unsigned  int           rdlvl_resp_mask;
} ncp_denali_DENALI_CTL_169_t;

/*! @struct ncp_denali_DENALI_CTL_170_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_170_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_resp_mask </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Mask for dfi_rdlvl_resp during read leveling. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_170
 */
 
typedef struct
{
     unsigned  int           rdlvl_resp_mask;
} ncp_denali_DENALI_CTL_170_t;

/*! @struct ncp_denali_DENALI_CTL_171_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_171_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_resp_mask </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Mask for dfi_rdlvl_resp during read leveling. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_171
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      rdlvl_resp_mask                           :  8;
#else    /* Little Endian */
     unsigned      rdlvl_resp_mask                           :  8;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_171_t;

/*! @struct ncp_denali_DENALI_CTL_172_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_172_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param bist_exp_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Expected data on BIST error. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_172
 */
 
typedef struct
{
     unsigned  int             bist_exp_data;
} ncp_denali_DENALI_CTL_172_t;

/*! @struct ncp_denali_DENALI_CTL_173_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_173_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param bist_exp_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Expected data on BIST error. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_173
 */
 
typedef struct
{
     unsigned  int             bist_exp_data;
} ncp_denali_DENALI_CTL_173_t;

/*! @struct ncp_denali_DENALI_CTL_174_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_174_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param bist_exp_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Expected data on BIST error. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_174
 */
 
typedef struct
{
     unsigned  int             bist_exp_data;
} ncp_denali_DENALI_CTL_174_t;

/*! @struct ncp_denali_DENALI_CTL_175_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_175_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param bist_exp_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Expected data on BIST error. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_175
 */
 
typedef struct
{
     unsigned  int             bist_exp_data;
} ncp_denali_DENALI_CTL_175_t;

/*! @struct ncp_denali_DENALI_CTL_176_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_176_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param bist_fail_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Actual data on BIST error. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_176
 */
 
typedef struct
{
     unsigned  int            bist_fail_data;
} ncp_denali_DENALI_CTL_176_t;

/*! @struct ncp_denali_DENALI_CTL_177_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_177_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param bist_fail_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Actual data on BIST error. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_177
 */
 
typedef struct
{
     unsigned  int            bist_fail_data;
} ncp_denali_DENALI_CTL_177_t;

/*! @struct ncp_denali_DENALI_CTL_178_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_178_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param bist_fail_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Actual data on BIST error. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_178
 */
 
typedef struct
{
     unsigned  int            bist_fail_data;
} ncp_denali_DENALI_CTL_178_t;

/*! @struct ncp_denali_DENALI_CTL_179_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_179_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param bist_fail_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Actual data on BIST error. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_179
 */
 
typedef struct
{
     unsigned  int            bist_fail_data;
} ncp_denali_DENALI_CTL_179_t;

/*! @struct ncp_denali_DENALI_CTL_180_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_180_t\n
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
 *     <td width="30%"> @param resync_dll </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Initiate a DLL resync. WRITE-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_reg_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enables direct register control of the dfi_rdlvl_delay
 *        signal; used when HW and SW leveling are disabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_reg_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enables direct register control of the dfi_rdlvl_gate_delay
 *        signal; used when HW and SW leveling are disabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param concurrentap_wr_only </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Limit concurrent auto-precharge by waiting for the
 *        write recovery time, tWR, to complete after a write
 *        before issuing a read.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_180
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      resync_dll                                :  1;
     unsigned      reserved1                                 :  7;
     unsigned      rdlvl_reg_en                              :  1;
     unsigned      reserved2                                 :  7;
     unsigned      rdlvl_gate_reg_en                         :  1;
     unsigned      reserved3                                 :  7;
     unsigned      concurrentap_wr_only                      :  1;
#else    /* Little Endian */
     unsigned      concurrentap_wr_only                      :  1;
     unsigned      reserved3                                 :  7;
     unsigned      rdlvl_gate_reg_en                         :  1;
     unsigned      reserved2                                 :  7;
     unsigned      rdlvl_reg_en                              :  1;
     unsigned      reserved1                                 :  7;
     unsigned      resync_dll                                :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_180_t;

/*! @struct ncp_denali_DENALI_CTL_180_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_180_v2_t\n
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
 *     <td width="30%"> @param resync_dll </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Initiate a DLL resync. WRITE-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_reg_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enables the dfi_rdlvl_delay signal to be programmed
 *        when HW and SW leveling are disabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_reg_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enables the dfi_rdlvl_gate_delay signal to be programmed
 *        when HW and SW leveling are disabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_180
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      resync_dll                                :  1;
     unsigned      reserved1                                 :  7;
     unsigned      rdlvl_reg_en                              :  1;
     unsigned      reserved2                                 :  7;
     unsigned      rdlvl_gate_reg_en                         :  1;
     unsigned      obsolete0                                 :  8;
#else    /* Little Endian */
     unsigned      obsolete0                                 :  8;
     unsigned      rdlvl_gate_reg_en                         :  1;
     unsigned      reserved2                                 :  7;
     unsigned      rdlvl_reg_en                              :  1;
     unsigned      reserved1                                 :  7;
     unsigned      resync_dll                                :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_180_v2_t;

/*! @struct ncp_denali_DENALI_CTL_181_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_181_t\n
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
 *     <td width="30%"> @param zq_in_progress </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Read-only register indicating when a ZQ command is
 *        currently in progress.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zqcs_rotate </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Selects ZQCS usage, rotate single ZQCS or all ZQCS.
 *        If using ZQCS Rotate, must program REFRESH_PER_ZQ
 *        for timing between single ZQCS commands such that
 *        each CS will be selected for ZQCS every REFRESH_PER_ZQ*CS
 *        time.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_reg_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enables direct register control of the dfi_wrlvl_delay
 *        signal; used when HW and SW leveling are disabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param resync_dll_per_aref_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enables automatic DLL resyncs after every </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_181
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      zq_in_progress                            :  1;
     unsigned      reserved1                                 :  7;
     unsigned      zqcs_rotate                               :  1;
     unsigned      reserved2                                 :  7;
     unsigned      wrlvl_reg_en                              :  1;
     unsigned      reserved3                                 :  7;
     unsigned      resync_dll_per_aref_en                    :  1;
#else    /* Little Endian */
     unsigned      resync_dll_per_aref_en                    :  1;
     unsigned      reserved3                                 :  7;
     unsigned      wrlvl_reg_en                              :  1;
     unsigned      reserved2                                 :  7;
     unsigned      zqcs_rotate                               :  1;
     unsigned      reserved1                                 :  7;
     unsigned      zq_in_progress                            :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_181_t;

/*! @struct ncp_denali_DENALI_CTL_182_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_182_t\n
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
 *     <td width="30%"> @param r2w_samecs_dly </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Additional clocks of delay to insert between reads
 *        and writes to the same chip select.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param r2w_diffcs_dly </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Additional clocks of delay to insert between reads
 *        and writes to different chip selects.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param r2r_samecs_dly </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Additional clocks of delay to insert between reads
 *        and reads to the same chip select.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param r2r_diffcs_dly </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Additional clocks of delay to insert between reads
 *        and reads to different chip selects.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_182
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  5;
     unsigned      r2w_samecs_dly                            :  3;
     unsigned      reserved1                                 :  5;
     unsigned      r2w_diffcs_dly                            :  3;
     unsigned      reserved2                                 :  5;
     unsigned      r2r_samecs_dly                            :  3;
     unsigned      reserved3                                 :  5;
     unsigned      r2r_diffcs_dly                            :  3;
#else    /* Little Endian */
     unsigned      r2r_diffcs_dly                            :  3;
     unsigned      reserved3                                 :  5;
     unsigned      r2r_samecs_dly                            :  3;
     unsigned      reserved2                                 :  5;
     unsigned      r2w_diffcs_dly                            :  3;
     unsigned      reserved1                                 :  5;
     unsigned      r2w_samecs_dly                            :  3;
     unsigned      reserved0                                 :  5;
#endif
} ncp_denali_DENALI_CTL_182_t;

/*! @struct ncp_denali_DENALI_CTL_183_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_183_t\n
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
 *     <td width="30%"> @param add_odt_clk_difftype_samecs </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Additional clocks of delay to insert between different
 *        transaction types (r/w) to the same chip select to
 *        meet ODT timing requirements.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param w2w_samecs_dly </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Additional clocks of delay to insert between writes
 *        and writes to the same chip select.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param w2w_diffcs_dly </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Additional clocks of delay to insert between writes
 *        and writes to different chip selects.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tccd </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM CAS-to-CAS parameter in cycles. </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_183
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      add_odt_clk_difftype_samecs               :  4;
     unsigned      reserved1                                 :  5;
     unsigned      w2w_samecs_dly                            :  3;
     unsigned      reserved2                                 :  5;
     unsigned      w2w_diffcs_dly                            :  3;
     unsigned      reserved3                                 :  3;
     unsigned      tccd                                      :  5;
#else    /* Little Endian */
     unsigned      tccd                                      :  5;
     unsigned      reserved3                                 :  3;
     unsigned      w2w_diffcs_dly                            :  3;
     unsigned      reserved2                                 :  5;
     unsigned      w2w_samecs_dly                            :  3;
     unsigned      reserved1                                 :  5;
     unsigned      add_odt_clk_difftype_samecs               :  4;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_183_t;

/*! @struct ncp_denali_DENALI_CTL_183_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_183_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param w2w_samecs_dly </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Additional delay to insert between writes and writes
 *        to the same chip select.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param w2w_diffcs_dly </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Additional delay to insert between writes and writes
 *        to different chip selects.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tccd </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM CAS-to-CAS parameter in cycles. </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_183
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      reserved0                                 :  5;
     unsigned      w2w_samecs_dly                            :  3;
     unsigned      reserved1                                 :  5;
     unsigned      w2w_diffcs_dly                            :  3;
     unsigned      reserved2                                 :  3;
     unsigned      tccd                                      :  5;
#else    /* Little Endian */
     unsigned      tccd                                      :  5;
     unsigned      reserved2                                 :  3;
     unsigned      w2w_diffcs_dly                            :  3;
     unsigned      reserved1                                 :  5;
     unsigned      w2w_samecs_dly                            :  3;
     unsigned      reserved0                                 :  5;
     unsigned      obsolete3                                 :  8;
#endif
} ncp_denali_DENALI_CTL_183_v2_t;

/*! @struct ncp_denali_DENALI_CTL_184_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_184_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param add_odt_clk_difftype_diffcs </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Additional clocks of delay to insert between different
 *        transaction types (r/w) to different chip selects
 *        to meet ODT timing requirements.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trp_ab </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DRAM TRP All Bank parameter in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param add_odt_clk_sametype_diffcs </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Additional clocks of delay to insert between same
 *        transaction types (r/w) to different chip selects
 *        to meet ODT timing requirements.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 
 *
 * Implemented by: 
 *      DENALI_CTL_184
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      reserved0                                 :  3;
     unsigned      add_odt_clk_difftype_diffcs               :  5;
     unsigned      reserved1                                 :  4;
     unsigned      trp_ab                                    :  4;
     unsigned      reserved2                                 :  4;
     unsigned      add_odt_clk_sametype_diffcs               :  4;
#else    /* Little Endian */
     unsigned      add_odt_clk_sametype_diffcs               :  4;
     unsigned      reserved2                                 :  4;
     unsigned      trp_ab                                    :  4;
     unsigned      reserved1                                 :  4;
     unsigned      add_odt_clk_difftype_diffcs               :  5;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete3                                 :  8;
#endif
} ncp_denali_DENALI_CTL_184_t;

/*! @struct ncp_denali_DENALI_CTL_184_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_184_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> MPT </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param add_odt_clk_difftype_diffcs </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Additional delay to insert between different transaction
 *        types to different chip selects to meet ODT timing
 *        requirements.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trp_ab </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DRAM TRP All Bank parameter in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param add_odt_clk_sametype_diffcs </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Additional delay to insert between same transaction
 *        types to different chip selects to meet ODT timing
 *        requirements.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_184
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      reserved0                                 :  2;
     unsigned      add_odt_clk_difftype_diffcs               :  6;
     unsigned      reserved1                                 :  4;
     unsigned      trp_ab                                    :  4;
     unsigned      reserved2                                 :  4;
     unsigned      add_odt_clk_sametype_diffcs               :  4;
#else    /* Little Endian */
     unsigned      add_odt_clk_sametype_diffcs               :  4;
     unsigned      reserved2                                 :  4;
     unsigned      trp_ab                                    :  4;
     unsigned      reserved1                                 :  4;
     unsigned      add_odt_clk_difftype_diffcs               :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete3                                 :  8;
#endif
} ncp_denali_DENALI_CTL_184_v2_t;

/*! @struct ncp_denali_DENALI_CTL_185_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_185_t\n
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
 *     <td width="30%"> @param tdfi_wrlvl_ww </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Minimum number of cycles between write level strobes. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_rdlvl_rr </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Minimum number of cycles between read commands for
 *        read leveling.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_185
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      tdfi_wrlvl_ww                             : 10;
     unsigned      reserved1                                 :  6;
     unsigned      tdfi_rdlvl_rr                             : 10;
#else    /* Little Endian */
     unsigned      tdfi_rdlvl_rr                             : 10;
     unsigned      reserved1                                 :  6;
     unsigned      tdfi_wrlvl_ww                             : 10;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_185_t;

/*! @struct ncp_denali_DENALI_CTL_186_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_186_t\n
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
 *     <td width="30%"> @param zqinit </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of clock cycles needed for a ZQ command. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zqcl </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of clock cycles needed for a ZQCL command. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_186
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      zqinit                                    : 12;
     unsigned      reserved1                                 :  4;
     unsigned      zqcl                                      : 12;
#else    /* Little Endian */
     unsigned      zqcl                                      : 12;
     unsigned      reserved1                                 :  4;
     unsigned      zqinit                                    : 12;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_186_t;

/*! @struct ncp_denali_DENALI_CTL_187_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_187_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param mr0_data_1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> MRS data to program to memory mode register 0 for
 *        chip select 1.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr0_data_0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MRS data to program to memory mode register 0 for
 *        chip select 0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_187
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      mr0_data_1                                : 16;
     unsigned      mr0_data_0                                : 16;
#else    /* Little Endian */
     unsigned      mr0_data_0                                : 16;
     unsigned      mr0_data_1                                : 16;
#endif
} ncp_denali_DENALI_CTL_187_t;

/*! @struct ncp_denali_DENALI_CTL_188_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_188_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param mr0_data_3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> MRS data to program to memory mode register 0 for
 *        chip select 3.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr0_data_2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MRS data to program to memory mode register 0 for
 *        chip select 2.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_188
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      mr0_data_3                                : 16;
     unsigned      mr0_data_2                                : 16;
#else    /* Little Endian */
     unsigned      mr0_data_2                                : 16;
     unsigned      mr0_data_3                                : 16;
#endif
} ncp_denali_DENALI_CTL_188_t;

/*! @struct ncp_denali_DENALI_CTL_189_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_189_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param mr1_data_1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Data to program into memory mode register 1 for chip
 *        select 1.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr1_data_0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 1 for chip
 *        select 0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_189
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      mr1_data_1                                : 16;
     unsigned      mr1_data_0                                : 16;
#else    /* Little Endian */
     unsigned      mr1_data_0                                : 16;
     unsigned      mr1_data_1                                : 16;
#endif
} ncp_denali_DENALI_CTL_189_t;

/*! @struct ncp_denali_DENALI_CTL_190_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_190_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param mr1_data_3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Data to program into memory mode register 1 for chip
 *        select 3.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr1_data_2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 1 for chip
 *        select 2.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_190
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      mr1_data_3                                : 16;
     unsigned      mr1_data_2                                : 16;
#else    /* Little Endian */
     unsigned      mr1_data_2                                : 16;
     unsigned      mr1_data_3                                : 16;
#endif
} ncp_denali_DENALI_CTL_190_t;

/*! @struct ncp_denali_DENALI_CTL_191_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_191_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param mr2_data_1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Data to program into memory mode register 2 for chip
 *        select 1.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr2_data_0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 2 for chip
 *        select 0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_191
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      mr2_data_1                                : 16;
     unsigned      mr2_data_0                                : 16;
#else    /* Little Endian */
     unsigned      mr2_data_0                                : 16;
     unsigned      mr2_data_1                                : 16;
#endif
} ncp_denali_DENALI_CTL_191_t;

/*! @struct ncp_denali_DENALI_CTL_192_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_192_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param mr2_data_3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Data to program into memory mode register 2 for chip
 *        select 3.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr2_data_2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 2 for chip
 *        select 2.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_192
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      mr2_data_3                                : 16;
     unsigned      mr2_data_2                                : 16;
#else    /* Little Endian */
     unsigned      mr2_data_2                                : 16;
     unsigned      mr2_data_3                                : 16;
#endif
} ncp_denali_DENALI_CTL_192_t;

/*! @struct ncp_denali_DENALI_CTL_193_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_193_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param mr3_data_1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Data to program into memory mode register 3 for chip
 *        select 1.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr3_data_0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 3 for chip
 *        select 0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_193
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      mr3_data_1                                : 16;
     unsigned      mr3_data_0                                : 16;
#else    /* Little Endian */
     unsigned      mr3_data_0                                : 16;
     unsigned      mr3_data_1                                : 16;
#endif
} ncp_denali_DENALI_CTL_193_t;

/*! @struct ncp_denali_DENALI_CTL_194_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_194_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param mr3_data_3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Data to program into memory mode register 3 for chip
 *        select 3.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr3_data_2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 3 for chip
 *        select 2.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_194
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      mr3_data_3                                : 16;
     unsigned      mr3_data_2                                : 16;
#else    /* Little Endian */
     unsigned      mr3_data_2                                : 16;
     unsigned      mr3_data_3                                : 16;
#endif
} ncp_denali_DENALI_CTL_194_t;

/*! @struct ncp_denali_DENALI_CTL_195_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_195_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_begin_delay_1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of delay elements for first 1 to 0 DQ transition
 *        for data slice 1.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_begin_delay_0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for first 1 to 0 DQ transition
 *        for data slice 0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_195
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_begin_delay_1                       : 16;
     unsigned      rdlvl_begin_delay_0                       : 16;
#else    /* Little Endian */
     unsigned      rdlvl_begin_delay_0                       : 16;
     unsigned      rdlvl_begin_delay_1                       : 16;
#endif
} ncp_denali_DENALI_CTL_195_t;

/*! @struct ncp_denali_DENALI_CTL_196_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_196_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_begin_delay_3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of delay elements for first 1 to 0 DQ transition
 *        for data slice 3.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_begin_delay_2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for first 1 to 0 DQ transition
 *        for data slice 2.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_196
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_begin_delay_3                       : 16;
     unsigned      rdlvl_begin_delay_2                       : 16;
#else    /* Little Endian */
     unsigned      rdlvl_begin_delay_2                       : 16;
     unsigned      rdlvl_begin_delay_3                       : 16;
#endif
} ncp_denali_DENALI_CTL_196_t;

/*! @struct ncp_denali_DENALI_CTL_197_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_197_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_begin_delay_5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of delay elements for first 1 to 0 DQ transition
 *        for data slice 5.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_begin_delay_4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for first 1 to 0 DQ transition
 *        for data slice 4.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_197
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_begin_delay_5                       : 16;
     unsigned      rdlvl_begin_delay_4                       : 16;
#else    /* Little Endian */
     unsigned      rdlvl_begin_delay_4                       : 16;
     unsigned      rdlvl_begin_delay_5                       : 16;
#endif
} ncp_denali_DENALI_CTL_197_t;

/*! @struct ncp_denali_DENALI_CTL_198_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_198_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_begin_delay_7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of delay elements for first 1 to 0 DQ transition
 *        for data slice 7.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_begin_delay_6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for first 1 to 0 DQ transition
 *        for data slice 6.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_198
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_begin_delay_7                       : 16;
     unsigned      rdlvl_begin_delay_6                       : 16;
#else    /* Little Endian */
     unsigned      rdlvl_begin_delay_6                       : 16;
     unsigned      rdlvl_begin_delay_7                       : 16;
#endif
} ncp_denali_DENALI_CTL_198_t;

/*! @struct ncp_denali_DENALI_CTL_199_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_199_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_delay_0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of delay elements where read DQS is placed
 *        within the DQ data eye for data slice 0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_begin_delay_8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for first 1 to 0 DQ transition
 *        for data slice 8.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_199
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_delay_0                             : 16;
     unsigned      rdlvl_begin_delay_8                       : 16;
#else    /* Little Endian */
     unsigned      rdlvl_begin_delay_8                       : 16;
     unsigned      rdlvl_delay_0                             : 16;
#endif
} ncp_denali_DENALI_CTL_199_t;

/*! @struct ncp_denali_DENALI_CTL_200_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_200_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_delay_2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of delay elements where read DQS is placed
 *        within the DQ data eye for data slice 2.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_delay_1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements where read DQS is placed
 *        within the DQ data eye for data slice 1.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_200
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_delay_2                             : 16;
     unsigned      rdlvl_delay_1                             : 16;
#else    /* Little Endian */
     unsigned      rdlvl_delay_1                             : 16;
     unsigned      rdlvl_delay_2                             : 16;
#endif
} ncp_denali_DENALI_CTL_200_t;

/*! @struct ncp_denali_DENALI_CTL_201_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_201_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_delay_4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of delay elements where read DQS is placed
 *        within the DQ data eye for data slice 4.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_delay_3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements where read DQS is placed
 *        within the DQ data eye for data slice 3.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_201
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_delay_4                             : 16;
     unsigned      rdlvl_delay_3                             : 16;
#else    /* Little Endian */
     unsigned      rdlvl_delay_3                             : 16;
     unsigned      rdlvl_delay_4                             : 16;
#endif
} ncp_denali_DENALI_CTL_201_t;

/*! @struct ncp_denali_DENALI_CTL_202_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_202_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_delay_6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of delay elements where read DQS is placed
 *        within the DQ data eye for data slice 6.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_delay_5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements where read DQS is placed
 *        within the DQ data eye for data slice 5.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_202
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_delay_6                             : 16;
     unsigned      rdlvl_delay_5                             : 16;
#else    /* Little Endian */
     unsigned      rdlvl_delay_5                             : 16;
     unsigned      rdlvl_delay_6                             : 16;
#endif
} ncp_denali_DENALI_CTL_202_t;

/*! @struct ncp_denali_DENALI_CTL_203_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_203_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_delay_8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of delay elements where read DQS is placed
 *        within the DQ data eye for data slice 8.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_delay_7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements where read DQS is placed
 *        within the DQ data eye for data slice 7.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_203
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_delay_8                             : 16;
     unsigned      rdlvl_delay_7                             : 16;
#else    /* Little Endian */
     unsigned      rdlvl_delay_7                             : 16;
     unsigned      rdlvl_delay_8                             : 16;
#endif
} ncp_denali_DENALI_CTL_203_t;

/*! @struct ncp_denali_DENALI_CTL_204_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_204_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_end_delay_1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of delay elements for first 0 to 1 DQ transition
 *        for data slice 1.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_end_delay_0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for first 0 to 1 DQ transition
 *        for data slice 0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_204
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_end_delay_1                         : 16;
     unsigned      rdlvl_end_delay_0                         : 16;
#else    /* Little Endian */
     unsigned      rdlvl_end_delay_0                         : 16;
     unsigned      rdlvl_end_delay_1                         : 16;
#endif
} ncp_denali_DENALI_CTL_204_t;

/*! @struct ncp_denali_DENALI_CTL_205_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_205_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_end_delay_3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of delay elements for first 0 to 1 DQ transition
 *        for data slice 3.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_end_delay_2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for first 0 to 1 DQ transition
 *        for data slice 2.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_205
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_end_delay_3                         : 16;
     unsigned      rdlvl_end_delay_2                         : 16;
#else    /* Little Endian */
     unsigned      rdlvl_end_delay_2                         : 16;
     unsigned      rdlvl_end_delay_3                         : 16;
#endif
} ncp_denali_DENALI_CTL_205_t;

/*! @struct ncp_denali_DENALI_CTL_206_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_206_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_end_delay_5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of delay elements for first 0 to 1 DQ transition
 *        for data slice 5.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_end_delay_4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for first 0 to 1 DQ transition
 *        for data slice 4.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_206
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_end_delay_5                         : 16;
     unsigned      rdlvl_end_delay_4                         : 16;
#else    /* Little Endian */
     unsigned      rdlvl_end_delay_4                         : 16;
     unsigned      rdlvl_end_delay_5                         : 16;
#endif
} ncp_denali_DENALI_CTL_206_t;

/*! @struct ncp_denali_DENALI_CTL_207_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_207_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_end_delay_7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of delay elements for first 0 to 1 DQ transition
 *        for data slice 7.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_end_delay_6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for first 0 to 1 DQ transition
 *        for data slice 6.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_207
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_end_delay_7                         : 16;
     unsigned      rdlvl_end_delay_6                         : 16;
#else    /* Little Endian */
     unsigned      rdlvl_end_delay_6                         : 16;
     unsigned      rdlvl_end_delay_7                         : 16;
#endif
} ncp_denali_DENALI_CTL_207_t;

/*! @struct ncp_denali_DENALI_CTL_208_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_208_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_delay_0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of delay elements where gate is aligned to
 *        rising edge of DQS for data slice 0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_end_delay_8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for first 0 to 1 DQ transition
 *        for data slice 8.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_208
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_gate_delay_0                        : 16;
     unsigned      rdlvl_end_delay_8                         : 16;
#else    /* Little Endian */
     unsigned      rdlvl_end_delay_8                         : 16;
     unsigned      rdlvl_gate_delay_0                        : 16;
#endif
} ncp_denali_DENALI_CTL_208_t;

/*! @struct ncp_denali_DENALI_CTL_209_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_209_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_delay_2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of delay elements where gate is aligned to
 *        rising edge of DQS for data slice 2.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_delay_1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements where gate is aligned to
 *        rising edge of DQS for data slice 1.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_209
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_gate_delay_2                        : 16;
     unsigned      rdlvl_gate_delay_1                        : 16;
#else    /* Little Endian */
     unsigned      rdlvl_gate_delay_1                        : 16;
     unsigned      rdlvl_gate_delay_2                        : 16;
#endif
} ncp_denali_DENALI_CTL_209_t;

/*! @struct ncp_denali_DENALI_CTL_210_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_210_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_delay_4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of delay elements where gate is aligned to
 *        rising edge of DQS for data slice 4.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_delay_3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements where gate is aligned to
 *        rising edge of DQS for data slice 3.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_210
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_gate_delay_4                        : 16;
     unsigned      rdlvl_gate_delay_3                        : 16;
#else    /* Little Endian */
     unsigned      rdlvl_gate_delay_3                        : 16;
     unsigned      rdlvl_gate_delay_4                        : 16;
#endif
} ncp_denali_DENALI_CTL_210_t;

/*! @struct ncp_denali_DENALI_CTL_211_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_211_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_delay_6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of delay elements where gate is aligned to
 *        rising edge of DQS for data slice 6.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_delay_5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements where gate is aligned to
 *        rising edge of DQS for data slice 5.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_211
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_gate_delay_6                        : 16;
     unsigned      rdlvl_gate_delay_5                        : 16;
#else    /* Little Endian */
     unsigned      rdlvl_gate_delay_5                        : 16;
     unsigned      rdlvl_gate_delay_6                        : 16;
#endif
} ncp_denali_DENALI_CTL_211_t;

/*! @struct ncp_denali_DENALI_CTL_212_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_212_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_delay_8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of delay elements where gate is aligned to
 *        rising edge of DQS for data slice 8.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_delay_7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements where gate is aligned to
 *        rising edge of DQS for data slice 7.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_212
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_gate_delay_8                        : 16;
     unsigned      rdlvl_gate_delay_7                        : 16;
#else    /* Little Endian */
     unsigned      rdlvl_gate_delay_7                        : 16;
     unsigned      rdlvl_gate_delay_8                        : 16;
#endif
} ncp_denali_DENALI_CTL_212_t;

/*! @struct ncp_denali_DENALI_CTL_213_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_213_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_max_delay </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Maximum number of elements for the read level delay
 *        line.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_max_delay </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Maximum number of elements for the gate delay. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_213
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_max_delay                           : 16;
     unsigned      rdlvl_gate_max_delay                      : 16;
#else    /* Little Endian */
     unsigned      rdlvl_gate_max_delay                      : 16;
     unsigned      rdlvl_max_delay                           : 16;
#endif
} ncp_denali_DENALI_CTL_213_t;

/*! @struct ncp_denali_DENALI_CTL_214_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_214_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_midpoint_delay_1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Calculated midpoint of DQ delay for data slice 1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_midpoint_delay_0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Calculated midpoint of DQ delay for data slice 0. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_214
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_midpoint_delay_1                    : 16;
     unsigned      rdlvl_midpoint_delay_0                    : 16;
#else    /* Little Endian */
     unsigned      rdlvl_midpoint_delay_0                    : 16;
     unsigned      rdlvl_midpoint_delay_1                    : 16;
#endif
} ncp_denali_DENALI_CTL_214_t;

/*! @struct ncp_denali_DENALI_CTL_215_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_215_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_midpoint_delay_3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Calculated midpoint of DQ delay for data slice 3. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_midpoint_delay_2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Calculated midpoint of DQ delay for data slice 2. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_215
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_midpoint_delay_3                    : 16;
     unsigned      rdlvl_midpoint_delay_2                    : 16;
#else    /* Little Endian */
     unsigned      rdlvl_midpoint_delay_2                    : 16;
     unsigned      rdlvl_midpoint_delay_3                    : 16;
#endif
} ncp_denali_DENALI_CTL_215_t;

/*! @struct ncp_denali_DENALI_CTL_216_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_216_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_midpoint_delay_5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Calculated midpoint of DQ delay for data slice 5. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_midpoint_delay_4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Calculated midpoint of DQ delay for data slice 4. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_216
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_midpoint_delay_5                    : 16;
     unsigned      rdlvl_midpoint_delay_4                    : 16;
#else    /* Little Endian */
     unsigned      rdlvl_midpoint_delay_4                    : 16;
     unsigned      rdlvl_midpoint_delay_5                    : 16;
#endif
} ncp_denali_DENALI_CTL_216_t;

/*! @struct ncp_denali_DENALI_CTL_217_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_217_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_midpoint_delay_7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Calculated midpoint of DQ delay for data slice 7. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_midpoint_delay_6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Calculated midpoint of DQ delay for data slice 6. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_217
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_midpoint_delay_7                    : 16;
     unsigned      rdlvl_midpoint_delay_6                    : 16;
#else    /* Little Endian */
     unsigned      rdlvl_midpoint_delay_6                    : 16;
     unsigned      rdlvl_midpoint_delay_7                    : 16;
#endif
} ncp_denali_DENALI_CTL_217_t;

/*! @struct ncp_denali_DENALI_CTL_218_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_218_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_offset_delay_0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Offset the read level midpoint delay for data slice
 *        0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_midpoint_delay_8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Calculated midpoint of DQ delay for data slice 8. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_218
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_offset_delay_0                      : 16;
     unsigned      rdlvl_midpoint_delay_8                    : 16;
#else    /* Little Endian */
     unsigned      rdlvl_midpoint_delay_8                    : 16;
     unsigned      rdlvl_offset_delay_0                      : 16;
#endif
} ncp_denali_DENALI_CTL_218_t;

/*! @struct ncp_denali_DENALI_CTL_219_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_219_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_offset_delay_2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Offset the read level midpoint delay for data slice
 *        2.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_offset_delay_1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Offset the read level midpoint delay for data slice
 *        1.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_219
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_offset_delay_2                      : 16;
     unsigned      rdlvl_offset_delay_1                      : 16;
#else    /* Little Endian */
     unsigned      rdlvl_offset_delay_1                      : 16;
     unsigned      rdlvl_offset_delay_2                      : 16;
#endif
} ncp_denali_DENALI_CTL_219_t;

/*! @struct ncp_denali_DENALI_CTL_220_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_220_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_offset_delay_4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Offset the read level midpoint delay for data slice
 *        4.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_offset_delay_3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Offset the read level midpoint delay for data slice
 *        3.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_220
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_offset_delay_4                      : 16;
     unsigned      rdlvl_offset_delay_3                      : 16;
#else    /* Little Endian */
     unsigned      rdlvl_offset_delay_3                      : 16;
     unsigned      rdlvl_offset_delay_4                      : 16;
#endif
} ncp_denali_DENALI_CTL_220_t;

/*! @struct ncp_denali_DENALI_CTL_221_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_221_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_offset_delay_6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Offset the read level midpoint delay for data slice
 *        6.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_offset_delay_5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Offset the read level midpoint delay for data slice
 *        5.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_221
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_offset_delay_6                      : 16;
     unsigned      rdlvl_offset_delay_5                      : 16;
#else    /* Little Endian */
     unsigned      rdlvl_offset_delay_5                      : 16;
     unsigned      rdlvl_offset_delay_6                      : 16;
#endif
} ncp_denali_DENALI_CTL_221_t;

/*! @struct ncp_denali_DENALI_CTL_222_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_222_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_offset_delay_8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Offset the read level midpoint delay for data slice
 *        8.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_offset_delay_7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Offset the read level midpoint delay for data slice
 *        7.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_222
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_offset_delay_8                      : 16;
     unsigned      rdlvl_offset_delay_7                      : 16;
#else    /* Little Endian */
     unsigned      rdlvl_offset_delay_7                      : 16;
     unsigned      rdlvl_offset_delay_8                      : 16;
#endif
} ncp_denali_DENALI_CTL_222_t;

/*! @struct ncp_denali_DENALI_CTL_223_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_223_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_rdlvl_max </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Maximum number of cycles between read level enable
 *        and read level response for PHY Eval mode.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_223
 */
 
typedef struct
{
     unsigned  int            tdfi_rdlvl_max;
} ncp_denali_DENALI_CTL_223_t;

/*! @struct ncp_denali_DENALI_CTL_224_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_224_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_rdlvl_resp </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Maximum number of cycles between read level request
 *        and read level mode enabled.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_224
 */
 
typedef struct
{
     unsigned  int           tdfi_rdlvl_resp;
} ncp_denali_DENALI_CTL_224_t;

/*! @struct ncp_denali_DENALI_CTL_225_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_225_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_wrlvl_max </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Maximum number of cycles between write level enable
 *        and write level response for PHY Eval mode.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_225
 */
 
typedef struct
{
     unsigned  int            tdfi_wrlvl_max;
} ncp_denali_DENALI_CTL_225_t;

/*! @struct ncp_denali_DENALI_CTL_226_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_226_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_wrlvl_resp </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Maximum number of cycles between write level request
 *        and write level mode enabled.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_226
 */
 
typedef struct
{
     unsigned  int           tdfi_wrlvl_resp;
} ncp_denali_DENALI_CTL_226_t;

/*! @struct ncp_denali_DENALI_CTL_227_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_227_t\n
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
 *     <td width="30%"> @param tdfi_phyupd_type1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Holds the DFI tPHYUPD_TYPE1 timing parameter. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tckesr </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Minimum CKE low pulse width during a self-refresh. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tbst_int_interval </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM burst interrupt interval in cycles. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_227
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  2;
     unsigned      tdfi_phyupd_type1                         : 14;
     unsigned      reserved1                                 :  3;
     unsigned      tckesr                                    :  5;
     unsigned      reserved2                                 :  5;
     unsigned      tbst_int_interval                         :  3;
#else    /* Little Endian */
     unsigned      tbst_int_interval                         :  3;
     unsigned      reserved2                                 :  5;
     unsigned      tckesr                                    :  5;
     unsigned      reserved1                                 :  3;
     unsigned      tdfi_phyupd_type1                         : 14;
     unsigned      reserved0                                 :  2;
#endif
} ncp_denali_DENALI_CTL_227_t;

/*! @struct ncp_denali_DENALI_CTL_228_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_228_t\n
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
 *     <td width="30%"> @param tdfi_phyupd_type3 </td>
 *     <td width="20%" align="center"> 14 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Holds the DFI tPHYUPD_TYPE3 timing parameter. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_phyupd_type2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Holds the DFI tPHYUPD_TYPE2 timing parameter. </td>
 * </tr>
 * </table>
 * Applies to: v1 v2 
 *
 * Implemented by: 
 *      DENALI_CTL_228
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  2;
     unsigned      tdfi_phyupd_type3                         : 14;
     unsigned      reserved1                                 :  2;
     unsigned      tdfi_phyupd_type2                         : 14;
#else    /* Little Endian */
     unsigned      tdfi_phyupd_type2                         : 14;
     unsigned      reserved1                                 :  2;
     unsigned      tdfi_phyupd_type3                         : 14;
     unsigned      reserved0                                 :  2;
#endif
} ncp_denali_DENALI_CTL_228_t;

/*! @struct ncp_denali_DENALI_CTL_229_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_229_v2_t\n
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
 *     <td width="20%" align="center"> 15 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tras_max </td>
 *     <td width="20%" align="center"> 17 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM TRAS_MAX parameter in cycles. </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_229
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 15;
     unsigned      tras_max                                  : 17;
#else    /* Little Endian */
     unsigned      tras_max                                  : 17;
     unsigned      reserved0                                 : 15;
#endif
} ncp_denali_DENALI_CTL_229_v2_t;

/*! @struct ncp_denali_DENALI_CTL_230_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_230_v2_t\n
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
 *     <td width="30%"> @param add_odt_clk_r2w_samecs </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Additional delay to insert between RD and WR transaction
 *        types to the same chip select to meet ODT timing requirements.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmdlat_reduc_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enable latency reduction within the IO cells of the
 *        PHY.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trfc </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM TRFC parameter in cycles. </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_230
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      add_odt_clk_r2w_samecs                    :  4;
     unsigned      reserved1                                 :  7;
     unsigned      cmdlat_reduc_en                           :  1;
     unsigned      reserved2                                 :  6;
     unsigned      trfc                                      : 10;
#else    /* Little Endian */
     unsigned      trfc                                      : 10;
     unsigned      reserved2                                 :  6;
     unsigned      cmdlat_reduc_en                           :  1;
     unsigned      reserved1                                 :  7;
     unsigned      add_odt_clk_r2w_samecs                    :  4;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_230_v2_t;

/*! @struct ncp_denali_DENALI_CTL_231_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_231_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_refresh_interval </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of refreshes counted between automatic write
 *        leveling commands.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enables the MC write leveling module. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param add_odt_clk_w2r_samecs </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Additional delay to insert between WR and RD transaction
 *        types to the same chip select to meet ODT timing requirements.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_231
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      wrlvl_refresh_interval                    : 16;
     unsigned      reserved0                                 :  7;
     unsigned      wrlvl_en                                  :  1;
     unsigned      reserved1                                 :  4;
     unsigned      add_odt_clk_w2r_samecs                    :  4;
#else    /* Little Endian */
     unsigned      add_odt_clk_w2r_samecs                    :  4;
     unsigned      reserved1                                 :  4;
     unsigned      wrlvl_en                                  :  1;
     unsigned      reserved0                                 :  7;
     unsigned      wrlvl_refresh_interval                    : 16;
#endif
} ncp_denali_DENALI_CTL_231_v2_t;

/*! @struct ncp_denali_DENALI_CTL_232_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_232_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_rdlvl_load </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Minimum number of cycles for read leveling delay to
 *        load.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_wrlvl_load </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Minimum number of cycles for write leveling delay
 *        to load.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mem_rst_valid </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Register access to mem_rst_valid signal. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cke_status </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Register access to cke_status signal. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_232
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      tdfi_rdlvl_load                           :  8;
     unsigned      tdfi_wrlvl_load                           :  8;
     unsigned      reserved0                                 :  7;
     unsigned      mem_rst_valid                             :  1;
     unsigned      reserved1                                 :  7;
     unsigned      cke_status                                :  1;
#else    /* Little Endian */
     unsigned      cke_status                                :  1;
     unsigned      reserved1                                 :  7;
     unsigned      mem_rst_valid                             :  1;
     unsigned      reserved0                                 :  7;
     unsigned      tdfi_wrlvl_load                           :  8;
     unsigned      tdfi_rdlvl_load                           :  8;
#endif
} ncp_denali_DENALI_CTL_232_v2_t;

/*! @struct ncp_denali_DENALI_CTL_233_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_233_v2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_refresh_interval </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of refreshes counted between automatic gate
 *        training commands.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_refresh_interval </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of refreshes counted between automatic read
 *        leveling commands.
 *   </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_233
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_gate_refresh_interval               : 16;
     unsigned      rdlvl_refresh_interval                    : 16;
#else    /* Little Endian */
     unsigned      rdlvl_refresh_interval                    : 16;
     unsigned      rdlvl_gate_refresh_interval               : 16;
#endif
} ncp_denali_DENALI_CTL_233_v2_t;

/*! @struct ncp_denali_DENALI_CTL_234_v2_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_234_v2_t\n
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
 *     <td width="30%"> @param phy_dll_bypass_mode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enable the DLL bypass feature of the PHY. </td>
 * </tr>
 * </table>
 * Applies to: v2 
 *
 * Implemented by: 
 *      DENALI_CTL_234
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 31;
     unsigned      phy_dll_bypass_mode                       :  1;
#else    /* Little Endian */
     unsigned      phy_dll_bypass_mode                       :  1;
     unsigned      reserved0                                 : 31;
#endif
} ncp_denali_DENALI_CTL_234_v2_t;

#ifdef __cplusplus
}
#endif

#endif /* _NCP_DENALI_REGS_H_ */
