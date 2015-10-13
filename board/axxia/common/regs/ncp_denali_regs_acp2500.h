/*
 *  Copyright (C) 2014 LSI (john.jacques@lsi.com)
 *
 * This program is free software;you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation;either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY;without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program;if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _NCP_DENALI_REGS_2500_H_
#define _NCP_DENALI_REGS_2500_H_

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
 *   <td width="30%"> Initiate auto-refresh at boundary specified by the
 *        AUTO_REFRESH_MODE parameter. Set to 1 to trigger.
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
 *   <td width="30%"> Enable auto pre-charge mode of controller. Set to
 *        1 to enable.
 *   </td>
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
 *   <td width="30%"> Enable address collision detection as a rule for command
 *        queue placement. Set to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_00_t
 *
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
} ncp_denali_DENALI_CTL_00_t;

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
 *   <td width="30%"> Enable data checking with BIST operation. Set to 1
 *        to enable.
 *   </td>
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
 *   <td width="30%"> Enable address checking with BIST operation. Set to
 *        1 to enable.
 *   </td>
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
 *   <td width="30%"> Enable bank splitting as a rule for command queue
 *        placement. Set to 1 to enable.
 *   </td>
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
 *        command boundary. Set to 1 for command boundary.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_01_t
 *
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
 *     <td width="30%"> @param obsolete2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> PADDING_BITS </td>
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
 *   <td width="30%"> Allow controller to issue commands to other banks
 *        while a bank is in auto pre-charge. Set to 1 to enable.
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
 *   <td width="30%"> Initiate a BIST operation. Set to 1 to trigger. WRITE-ONLY </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_02_t
 *
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
} ncp_denali_DENALI_CTL_02_t;

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
 *     <td width="30%"> @param obsolete2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_disable_w_uc_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Controls auto-corruption of ECC when un-correctable
 *        errors occur in R/M/W operations. Set to 1 to disable
 *        corruption.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_03_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      reserved0                                 :  7;
     unsigned      ecc_disable_w_uc_err                      :  1;
     unsigned      obsolete0                                 : 16;
#else    /* Little Endian */
     unsigned      obsolete0                                 : 16;
     unsigned      ecc_disable_w_uc_err                      :  1;
     unsigned      reserved0                                 :  7;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_03_t;

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
 *   <td width="30%"> Force a write check. Xor the XOR_CHECK_BITS parameter
 *        with the ECC code and write to memory. Set to 1 to
 *        trigger. WRITE-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enable_quick_srefresh </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allow user to interrupt memory initialization to enter
 *        self-refresh mode. Set to 1 to allow interruption.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_04_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      fwc                                       :  1;
     unsigned      obsolete1                                 : 16;
     unsigned      reserved1                                 :  7;
     unsigned      enable_quick_srefresh                     :  1;
#else    /* Little Endian */
     unsigned      enable_quick_srefresh                     :  1;
     unsigned      reserved1                                 :  7;
     unsigned      obsolete1                                 : 16;
     unsigned      fwc                                       :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_04_t;

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
 *   <td width="30%"> Disable DRAM commands until the TDLL parameter has
 *        expired during initialization. Set to 1 to disable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_05_t
 *
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
} ncp_denali_DENALI_CTL_05_t;

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
 *     <td width="30%"> @param obsolete2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param placement_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enable placement logic for command queue. Set to 1
 *        to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_06_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      reserved0                                 :  7;
     unsigned      placement_en                              :  1;
     unsigned      obsolete0                                 : 16;
#else    /* Little Endian */
     unsigned      obsolete0                                 : 16;
     unsigned      placement_en                              :  1;
     unsigned      reserved0                                 :  7;
     unsigned      obsolete2                                 :  8;
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
 *        be used for the read leveling operation. Set to 1
 *        for negative edge.
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
 *   <td width="30%"> Enable the read leveling logic to find the DQ data
 *        eye. Set to 1 to enable.
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
 *        initialization. Set to 1 to enable.
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
 *   <td width="30%"> Enable priority as a rule for command queue placement.
 *        Set to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_07_t
 *
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
 *   <td width="30%"> User request to initiate gate training. Set to 1 to
 *        trigger. WRITE-ONLY
 *   </td>
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
 *   <td width="30%"> Enable the preamble check sequence during initial
 *        gate training. Set to 1 to enable.
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
 *   <td width="30%"> Enable gate training mode of the read leveling module
 *        in the MC. Set to 1 to enable.
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
 *   <td width="30%"> Enable the MC read leveling module. Set to 1 to enable. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_08_t
 *
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
 *        for data slice 3. Set to 1 to add delay.
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
 *        for data slice 2. Set to 1 to add delay.
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
 *        for data slice 1. Set to 1 to add delay.
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
 *        for data slice 0. Set to 1 to add delay.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_09_t
 *
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
 *        for data slice 7. Set to 1 to add delay.
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
 *        for data slice 6. Set to 1 to add delay.
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
 *        for data slice 5. Set to 1 to add delay.
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
 *        for data slice 4. Set to 1 to add delay.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_10_t
 *
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
 *   <td width="30%"> Enable registered DIMM operation of the controller.
 *        Set to 1 to enable.
 *   </td>
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
 *   <td width="30%"> Enable the half datapath feature of the controller.
 *        Set to 1 to enable.
 *   </td>
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
 *   <td width="30%"> User request to initiate read leveling. Set to 1 to
 *        trigger. WRITE-ONLY
 *   </td>
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
 *        for data slice 8. Set to 1 to add delay.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_11_t
 *
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
 *   <td width="30%"> Enable command swapping logic in execution unit. Set
 *        to 1 to enable.
 *   </td>
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
 *   <td width="30%"> Initiate command processing in the controller. Set
 *        to 1 to initiate.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rw_same_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enable read/write grouping as a rule for command queue
 *        placement. Set to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_12_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      swap_en                                   :  1;
     unsigned      reserved1                                 :  7;
     unsigned      start                                     :  1;
     unsigned      obsolete1                                 :  8;
     unsigned      reserved2                                 :  7;
     unsigned      rw_same_en                                :  1;
#else    /* Little Endian */
     unsigned      rw_same_en                                :  1;
     unsigned      reserved2                                 :  7;
     unsigned      obsolete1                                 :  8;
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
 *   <td width="30%"> Signals that software leveling is currently in progress.
 *        Value of 1 indicates operation complete. READ-ONLY
 *   </td>
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
 *        Set to 1 to trigger. WRITE-ONLY
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
 *   <td width="30%"> User request to exit software leveling. Set to 1 to
 *        exit. WRITE-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_13_t
 *
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
     unsigned      obsolete0                                 :  8;
#else    /* Little Endian */
     unsigned      obsolete0                                 :  8;
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
 *   <td width="30%"> Free-running or limited WRR latency counters. Set
 *        to 1 for free-running.
 *   </td>
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
 *   <td width="30%"> Issue auto-refresh commands to the DRAMs at the interval
 *        defined in the TREF parameter. Set to 1 to enable.
 *   </td>
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
 *   <td width="30%"> Allow the controller to execute auto pre-charge commands
 *        before the TRAS_MIN parameter expires. Set to 1 to
 *        enable.
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
 *        in the SW_LEVELING_MODE parameter. Set to 1 to trigger.
 *        WRITE-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_14_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      weighted_round_robin_latency_control      :  1;/* obsolete for 5500 */
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
 *   <td width="30%"> User request to initiate write leveling. Set to 1
 *        to trigger. WRITE-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param writeinterp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allow controller to interrupt a write burst to the
 *        DRAMs with a read command. Set to 1 to allow interruption.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_15_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      wrlvl_req                                 :  1;
     unsigned      obsolete1                                 : 16;
     unsigned      reserved1                                 :  7;
     unsigned      writeinterp                               :  1;
#else    /* Little Endian */
     unsigned      writeinterp                               :  1;
     unsigned      reserved1                                 :  7;
     unsigned      obsolete1                                 : 16;
     unsigned      wrlvl_req                                 :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_15_t;

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
 *     <td width="30%"> @param obsolete2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> PADDING_BITS </td>
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
 *        core. Set to 0 for asynchronous, set to 1 for 2:1
 *        port:core pseudo-sync, set to 2 for 1:2 port:core
 *        pseudo-sync, or set to 3 for synchronous.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_16_t
 *
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
} ncp_denali_DENALI_CTL_16_t;

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
 *     <td width="30%"> @param obsolete2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> PADDING_BITS </td>
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
 *        core. Set to 0 for asynchronous, set to 1 for 2:1
 *        port:core pseudo-sync, set to 2 for 1:2 port:core
 *        pseudo-sync, or set to 3 for synchronous.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_17_t
 *
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
} ncp_denali_DENALI_CTL_17_t;

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
 *     <td width="30%"> @param obsolete2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> PADDING_BITS </td>
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
 *        core. Set to 0 for asynchronous, set to 1 for 2:1
 *        port:core pseudo-sync, set to 2 for 1:2 port:core
 *        pseudo-sync, or set to 3 for synchronous.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_18_t
 *
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
} ncp_denali_DENALI_CTL_18_t;

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
 *     <td width="30%"> @param obsolete2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> PADDING_BITS </td>
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
 *        core. Set to 0 for asynchronous, set to 1 for 2:1
 *        port:core pseudo-sync, set to 2 for 1:2 port:core
 *        pseudo-sync, or set to 3 for synchronous.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_19_t
 *
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
} ncp_denali_DENALI_CTL_19_t;

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
 *     <td width="30%"> @param obsolete3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> PADDING_BITS </td>
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
 *   <td width="30%"> ECC error checking and correcting control. Set to
 *        0 to disable ECC, set to 1 for ECC reporting only,
 *        set to 2 for ECC removed, or set to 3 for ECC reporting
 *        and correcting.
 *   </td>
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
 *   <td width="30%"> BIST operation status (pass/fail). Bit (0) indicates
 *        data check status and bit (1) indicates address check
 *        status. Value of 1 is a passing result. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_20_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      rdlvl_cs                                  :  2;
     unsigned      reserved1                                 :  6;
     unsigned      ctrl_raw                                  :  2;/* obsolete for 5500 */
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
} ncp_denali_DENALI_CTL_20_t;

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
 *        exit. Bit (0) selects ZQCS and bit (1) selects ZQCL.
 *        Set either bit to 1 to enable.
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
 *   <td width="30%"> Per-port pair shared arbitration for WRR. Bit (0)
 *        controls ports 0 and 1, bit (1) controls ports 2 and
 *        3, etc. Set each bit to 1 to link.
 *   </td>
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
 *   <td width="30%"> Defines the leveling operation for software leveling.
 *        Set to 0 for none, set to 1 for write leveling, set
 *        to 2 for read leveling, or set to 3 for gate training.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_21_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      zq_on_sref_exit                           :  2;
     unsigned      reserved1                                 :  6;
     unsigned      wrlvl_cs                                  :  2;
     unsigned      reserved2                                 :  6;
     unsigned      weighted_round_robin_weight_sharing       :  2;/* obsolete for 5500 */
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
 *   <td width="30%"> Encoded burst length sent to DRAMs during initialization.
 *        Set to 1 for BL2, set to 2 for BL4, or set to 3 for
 *        BL8.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param age_count </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Initial value of master aging-rate counter for command
 *        aging.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zq_req </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> User request to initiate a ZQ calibration. Bit (0)
 *        controls ZQCS and bit (1) controls ZQCL. Set either
 *        bit to 1 to trigger. WRITE-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_22_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  5;
     unsigned      bstlen                                    :  3;
     unsigned      age_count                                 :  8;
     unsigned      obsolete1                                 :  8;
     unsigned      reserved1                                 :  6;
     unsigned      zq_req                                    :  2;
#else    /* Little Endian */
     unsigned      zq_req                                    :  2;
     unsigned      reserved1                                 :  6;
     unsigned      obsolete1                                 :  8;
     unsigned      age_count                                 :  8;
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
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lvl_status </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Status of write level, data eye training, and gate
 *        training requests. This is used with the LVL_REQ interrupt.
 *        Bit (0) correlates to a write leveling request, bit
 *        (1) correlates to a data eye training request, bit
 *        (2) correlates to a gate training request, and bit
 *        (3) is reserved. Value of 1 indicates request received.
 *        READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param command_age_count </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Initial value of individual command aging counters
 *        for command aging.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
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
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_23_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      lvl_status                                :  4;/* only 3 bits on 2500 */
     unsigned      command_age_count                         :  8;
     unsigned      obsolete1                                 :  8;
     unsigned      reserved1                                 :  5;
     unsigned      cke_delay                                 :  3;
#else    /* Little Endian */
     unsigned      cke_delay                                 :  3;
     unsigned      reserved1                                 :  5;
     unsigned      obsolete1                                 :  8;
     unsigned      command_age_count                         :  8;
     unsigned      lvl_status                                :  4;
     unsigned      reserved0                                 :  4;
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
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param q_fullness </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Quantity that determines command queue full. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param max_cs_reg </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Holds the maximum number of chip selects available.
 *        READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_24_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  5;
     unsigned      tcke                                      :  3;
     unsigned      reserved1                                 :  4;
     unsigned      q_fullness                                :  4;/* only 3 bites on 2500 */
     unsigned      obsolete1                                 :  8;
     unsigned      reserved2                                 :  5;
     unsigned      max_cs_reg                                :  3;
#else    /* Little Endian */
     unsigned      max_cs_reg                                :  3;
     unsigned      reserved2                                 :  5;
     unsigned      obsolete1                                 :  8;
     unsigned      q_fullness                                :  4;
     unsigned      reserved1                                 :  4;
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
 *        to different chip selects. Allowed programming dependent
 *        on memory system.
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
 *   <td width="30%"> DRAM TRTP value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trrd </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM TRRD value in cycles. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_25_t
 *
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
     unsigned      trrd                                      :  8;
#else    /* Little Endian */
     unsigned      trrd                                      :  8;
     unsigned      trtp                                      :  4;
     unsigned      reserved2                                 :  4;
     unsigned      w2r_diffcs_dly                            :  3;
     unsigned      reserved1                                 :  5;
     unsigned      w2r_samecs_dly                            :  3;
     unsigned      reserved0                                 :  5;
#endif
} ncp_denali_DENALI_CTL_25_t;

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
 *   <td width="30%"> Relative priority of priority 1 commands from port
 *        0.
 *   </td>
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
 *   <td width="30%"> Relative priority of priority 0 commands from port
 *        0.
 *   </td>
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
 *   <td width="30%"> Indicates which chip selects support address mirroring.
 *        Bit (0) controls cs0, bit (1) controls cs1, etc. Set
 *        each bit to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_26_t
 *
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
 *   <td width="30%"> Relative priority of priority 1 commands from port
 *        1.
 *   </td>
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
 *   <td width="30%"> Relative priority of priority 0 commands from port
 *        1.
 *   </td>
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
 *   <td width="30%"> Relative priority of priority 3 commands from port
 *        0.
 *   </td>
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
 *   <td width="30%"> Relative priority of priority 2 commands from port
 *        0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_27_t
 *
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

/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */
/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */
/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */
/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */
/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */
/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */

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
 *   <td width="30%"> Relative priority of priority 1 commands from port
 *        2.
 *   </td>
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
 *   <td width="30%"> Relative priority of priority 0 commands from port
 *        2.
 *   </td>
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
 *   <td width="30%"> Relative priority of priority 3 commands from port
 *        1.
 *   </td>
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
 *   <td width="30%"> Relative priority of priority 2 commands from port
 *        1.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_28_t
 *
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
/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */
/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */
/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */
/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */
/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */
/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */

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
 *   <td width="30%"> Relative priority of priority 1 commands from port
 *        3.
 *   </td>
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
 *   <td width="30%"> Relative priority of priority 0 commands from port
 *        3.
 *   </td>
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
 *   <td width="30%"> Relative priority of priority 3 commands from port
 *        2.
 *   </td>
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
 *   <td width="30%"> Relative priority of priority 2 commands from port
 *        2.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_29_t
 *
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
/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */
/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */
/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */
/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */
/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */
/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */

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
 *   <td width="30%"> Disable read/modify/write for aligned AXI transfers
 *        with ECC. Bit (0) controls port 0, bit (1) controls
 *        port 1, etc. Set each bit to 1 to disable.
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
 *   <td width="30%"> Relative priority of priority 3 commands from port
 *        3.
 *   </td>
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
 *   <td width="30%"> Relative priority of priority 2 commands from port
 *        3.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_30_t
 *
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
/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */
/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */
/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */
/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */
/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */
/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */

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
 *   <td width="30%"> Set value for the dfi_dram_clk_disable signal. Bit
 *        (0) controls cs0, bit (1) controls cs1, etc. Set each
 *        bit to 1 to disable.
 *   </td>
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_31_t
 *
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
} ncp_denali_DENALI_CTL_31_t;
/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */
/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */
/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */
/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */
/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */
/* TEMP TEMP TEMP TEMP TEMP TEMP TEMP TEMP */

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
 *        a read occurs on chip select 1. Set bit X to enable
 *        termination on csX when cs1 is performing a read.
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
 *        a read occurs on chip select 0. Set bit X to enable
 *        termination on csX when cs0 is performing a read.
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
 *   <td width="30%"> Holds the maximum width of column address in DRAMs.
 *        READ-ONLY
 *   </td>
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
 *   <td width="30%"> Number of auto-refresh commands to execute during
 *        DRAM initialization.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_32_t
 *
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
 *        a write occurs on chip select 1. Set bit X to enable
 *        termination on csX when cs1 is performing a write.
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
 *        a write occurs on chip select 0. Set bit X to enable
 *        termination on csX when cs0 is performing a write.
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
 *        a read occurs on chip select 3. Set bit X to enable
 *        termination on csX when cs3 is performing a read.
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
 *        a read occurs on chip select 2. Set bit X to enable
 *        termination on csX when cs2 is performing a read.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_33_t
 *
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
 *     <td width="30%"> @param rdlvl_dq_0_count </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Number of consecutive 0s that defines a 1 to 0 transition
 *        for read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param port_cmd_error_type </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Type of error and access type that caused the PORT
 *        command error. READ-ONLY
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
 *        a write occurs on chip select 3. Set bit X to enable
 *        termination on csX when cs3 is performing a write.
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
 *        a write occurs on chip select 2. Set bit X to enable
 *        termination on csX when cs2 is performing a write.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_34_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      rdlvl_dq_0_count                          :  4;
     unsigned      reserved1                                 :  5;
     unsigned      port_cmd_error_type                       :  3;
     unsigned      reserved2                                 :  4;
     unsigned      odt_wr_map_cs3                            :  4;
     unsigned      reserved3                                 :  4;
     unsigned      odt_wr_map_cs2                            :  4;
#else    /* Little Endian */
     unsigned      odt_wr_map_cs2                            :  4;
     unsigned      reserved3                                 :  4;
     unsigned      odt_wr_map_cs3                            :  4;
     unsigned      reserved2                                 :  4;
     unsigned      port_cmd_error_type                       :  3;
     unsigned      reserved1                                 :  5;
     unsigned      rdlvl_dq_0_count                          :  4;
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
 *     <td width="30%"> @param obsolete3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_phy_wrlat </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Holds the calculated DFI tPHY_WRLAT timing parameter
 *        (in DFI PHY clocks), the maximum cycles between a
 *        write command and a dfi_wrdata_en assertion. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_ctrlupd_min </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reports the DFI tCTRLUPD_MIN timing parameter (in
 *        DFI clocks), the minimum cycles that dfi_ctrlupd_req
 *        must be asserted. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_dq_0_count </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of consecutive 0s that defines a 1 to 0 transition
 *        for gate training.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_35_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      reserved0                                 :  1;
     unsigned      tdfi_phy_wrlat                            :  7;/* only 5 bits on 2500 */
     unsigned      reserved1                                 :  4;
     unsigned      tdfi_ctrlupd_min                          :  4;
     unsigned      reserved2                                 :  4;
     unsigned      rdlvl_gate_dq_0_count                     :  4;
#else    /* Little Endian */
     unsigned      rdlvl_gate_dq_0_count                     :  4;
     unsigned      reserved2                                 :  4;
     unsigned      tdfi_ctrlupd_min                          :  4;
     unsigned      reserved1                                 :  4;
     unsigned      tdfi_phy_wrlat                            :  7;
     unsigned      reserved0                                 :  1;
     unsigned      obsolete3                                 :  8;
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
 *   <td width="30%"> DRAM TWTR value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trp </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DRAM TRP value in cycles. </td>
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_36_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      twtr                                      :  4;
     unsigned      reserved1                                 :  3;
     unsigned      trp                                       :  5;
     unsigned      tdfi_wrlvl_en                             :  8;
     unsigned      tdfi_rdlvl_en                             :  8;
#else    /* Little Endian */
     unsigned      tdfi_rdlvl_en                             :  8;
     unsigned      tdfi_wrlvl_en                             :  8;
     unsigned      trp                                       :  5;
     unsigned      reserved1                                 :  3;
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
 *   <td width="30%"> PADDING_BITS </td>
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
 *   <td width="30%"> Errors/warnings related to the WRR parameters. Bit
 *        (0) set indicates invalid port ordering specified,
 *        bit (1) set indicates invalid relative priority, bit
 *        (2) set indicates invalid priority for paired ports,
 *        and bit (3) set indicates invalid ordering for paired
 *        ports. READ-ONLY
 *   </td>
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
 *   <td width="30%"> DRAM WRLAT value in cycles. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_37_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      reserved0                                 :  4;
     unsigned      wrr_param_value_err                       :  4;/* obsolete on 5500 */
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
} ncp_denali_DENALI_CTL_37_t;

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
 *   <td width="30%"> Holds the maximum width of memory address bus. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param caslat_lin </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Sets latency from read command send to data receive
 *        from/to controller. Bit (0) is half-cycle increment
 *        and the upper bits define memory CAS latency for the
 *        controller.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_38_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      ocd_adjust_pdn_cs_0                       :  5;
     unsigned      reserved1                                 :  3;
     unsigned      max_row_reg                               :  5;
     unsigned      obsolete1                                 :  8;
     unsigned      reserved2                                 :  2;
     unsigned      caslat_lin                                :  6;
#else    /* Little Endian */
     unsigned      caslat_lin                                :  6;
     unsigned      reserved2                                 :  2;
     unsigned      obsolete1                                 :  8;
     unsigned      max_row_reg                               :  5;
     unsigned      reserved1                                 :  3;
     unsigned      ocd_adjust_pdn_cs_0                       :  5;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_38_t;

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
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdal </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> DRAM TDAL value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlat_adj </td>
 *     <td width="20%" align="center"> 7 </td>
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
 *   <td width="30%"> Type of command that caused an out-of-range interrupt.
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
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_39_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  2;
     unsigned      tdal                                      :  6;
     unsigned      reserved1                                 :  1;
     unsigned      rdlat_adj                                 :  7;/* only 6 bits on 2500 */
     unsigned      reserved2                                 :  2;
     unsigned      out_of_range_type                         :  6;
     unsigned      reserved3                                 :  3;
     unsigned      ocd_adjust_pup_cs_0                       :  5;
#else    /* Little Endian */
     unsigned      ocd_adjust_pup_cs_0                       :  5;
     unsigned      reserved3                                 :  3;
     unsigned      out_of_range_type                         :  6;
     unsigned      reserved2                                 :  2;
     unsigned      rdlat_adj                                 :  7;
     unsigned      reserved1                                 :  1;
     unsigned      tdal                                      :  6;
     unsigned      reserved0                                 :  2;
#endif
} ncp_denali_DENALI_CTL_39_t;

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
 *   <td width="30%"> DRAM TFAW value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_rddata_en </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Holds the calculated DFI tRDDATA_EN timing parameter
 *        (in DFI PHY clocks), the maximum cycles between a
 *        read command and a dfi_rddata_en assertion. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_phy_rdlat </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the DFI tPHY_RDLAT timing parameter (in DFI
 *        PHY clocks), the maximum cycles between a dfi_rddata_en
 *        assertion and a dfi_rddata_valid assertion.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_40_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  2;
     unsigned      tfaw                                      :  6;
     unsigned      obsolete2                                 :  8;
     unsigned      reserved1                                 :  1;
     unsigned      tdfi_rddata_en                            :  7;/* only 6 bits on 2500 */
     unsigned      reserved2                                 :  1;
     unsigned      tdfi_phy_rdlat                            :  7;/* only 6 bits on 2500 */
#else    /* Little Endian */
     unsigned      tdfi_phy_rdlat                            :  7;
     unsigned      reserved2                                 :  1;
     unsigned      tdfi_rddata_en                            :  7;
     unsigned      reserved1                                 :  1;
     unsigned      obsolete2                                 :  8;
     unsigned      tfaw                                      :  6;
     unsigned      reserved0                                 :  2;
#endif
} ncp_denali_DENALI_CTL_40_t;

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
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param twr_int </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DRAM TWR value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trc </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DRAM TRC value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tmrd </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM TMRD value in cycles. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_41_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  2;
     unsigned      addr_space                                :  6;
     unsigned      reserved1                                 :  2;
     unsigned      twr_int                                   :  6;/* obsolete on 5500 */
     unsigned      trc                                       :  8;
     unsigned      reserved2                                 :  3;
     unsigned      tmrd                                      :  5;
#else    /* Little Endian */
     unsigned      tmrd                                      :  5;
     unsigned      reserved2                                 :  3;
     unsigned      trc                                       :  8;
     unsigned      twr_int                                   :  6;
     unsigned      reserved1                                 :  2;
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
 *        in DLL until the DLL reset signal dll_rst_n may be
 *        asserted. If this signal is not being used by the
 *        PHY, this parameter may be ignored.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
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
 *     <td width="30%"> @param reserved1 </td>
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_42_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      dll_rst_adj_dly                           :  8;
     unsigned      obsolete2                                 :  8;
     unsigned      reserved0                                 :  2;
     unsigned      wlmrd                                     :  6;
     unsigned      reserved1                                 :  2;
     unsigned      wldqsen                                   :  6;
#else    /* Little Endian */
     unsigned      wldqsen                                   :  6;
     unsigned      reserved1                                 :  2;
     unsigned      wlmrd                                     :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete2                                 :  8;
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param out_of_range_length </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Length of command that caused an out-of-range interrupt.
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_43_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      out_of_range_length                       :  8;/* obsolete on 5500 */
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_44_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_45_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_46_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_47_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_48_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_49_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_50_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_51_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_52_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_53_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_54_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_55_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_56_t
 *
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
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_57_t
 *
 */

typedef struct
{
     unsigned  int                 obsolete0;
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
 *   <td width="30%"> Leveling response for data slice 3. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param swlvl_resp_2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Leveling response for data slice 2. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param swlvl_resp_1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Leveling response for data slice 1. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param swlvl_resp_0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Leveling response for data slice 0. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_58_t
 *
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
 *   <td width="30%"> Leveling response for data slice 7. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param swlvl_resp_6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Leveling response for data slice 6. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param swlvl_resp_5 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Leveling response for data slice 5. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param swlvl_resp_4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Leveling response for data slice 4. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_59_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
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
 *   <td width="30%"> Leveling response for data slice 8. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_60_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_61_t
 *
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
 *   <td width="30%"> DRAM TRCD value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tras_min </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DRAM TRAS_MIN value in cycles. </td>
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_62_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      trcd_int                                  :  8;/* obsolete in 5500 */
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
 *   <td width="30%"> PADDING_BITS </td>
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_63_t
 *
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
} ncp_denali_DENALI_CTL_63_t;

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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_64_t
 *
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_65_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_66_t
 *
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
 *   <td width="30%"> Source ID of command that caused an out-of-range interrupt.
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_67_t
 *
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
 *   <td width="30%"> Source ID of command that caused the PORT data error.
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
 *   <td width="30%"> Source ID of command that caused the PORT command
 *        error. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_68_t
 *
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
 *   <td width="30%"> Holds the DFI tPHYUPD_RESP timing parameter. If programmed
 *        to a non-zero, a timing violation will cause an interrupt
 *        and bit (6) set in the UPDATE_ERROR_STATUS parameter.
 *   </td>
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
 *   <td width="30%"> Holds the DFI tCTRLUPD_MAX timing parameter. If programmed
 *        to a non-zero, a timing violation will cause an interrupt
 *        and bit (1) set in the UPDATE_ERROR_STATUS parameter.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_69_t
 *
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
 *   <td width="30%"> DRAM TREF value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_phyupd_type0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Holds the DFI tPHYUPD_TYPE0 timing parameter. If programmed
 *        to a non-zero, a timing violation will cause an interrupt
 *        and bit (2) set in the UPDATE_ERROR_STATUS parameter.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_70_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  2;
     unsigned      tref                                      : 14;
     unsigned      tdfi_phyupd_type0                         : 16;
#else    /* Little Endian */
     unsigned      tdfi_phyupd_type0                         : 16;
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
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_71_t
 *
 */

typedef struct
{
     unsigned  int                 obsolete0;
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
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_72_t
 *
 */

typedef struct
{
     unsigned  int                 obsolete0;
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dll_rst_delay </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Minimum number of cycles required for DLL reset signal
 *        dll_rst_n to be held. If this signal is not being
 *        used by the PHY, this parameter may be ignored.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_73_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_74_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_75_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_76_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_77_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_78_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_79_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_80_t
 *
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
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_81_t
 *
 */

typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_81_t;

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
 *   <td width="30%"> DRAM TCPD value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_82_t
 *
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
} ncp_denali_DENALI_CTL_82_t;

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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_83_t
 *
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
 *   <td width="30%"> DRAM TPDEX value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdll </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM TDLL value in cycles. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_84_t
 *
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
 *   <td width="30%"> DRAM TXPDLL value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_85_t
 *
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
} ncp_denali_DENALI_CTL_85_t;

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
 *   <td width="30%"> DRAM TXSR value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param txsnr </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM TXSNR value in cycles. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_86_t
 *
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
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param version </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Holds the controller version number. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_87_t
 *
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
} ncp_denali_DENALI_CTL_87_t;

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
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_88_t
 *
 */

typedef struct
{
     unsigned  int                 obsolete0;
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param int_ack </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Clear mask of the INT_STATUS parameter. WRITE-ONLY </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_89_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      int_ack                                   : 24;
#else    /* Little Endian */
     unsigned      int_ack                                   : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_89_t;

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
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_90_t
 *
 */

typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_90_t;

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
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_91_t
 *
 */

typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_91_t;

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
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_92_t
 *
 */

typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_92_t;

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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tinit </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM TINIT value in cycles. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_93_t
 *
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
 *   <td width="30%"> Number of cycles after reset before CKE will be active. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_94_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_95_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_96_t
 *
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
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_97_t
 *
 */

typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_97_t;

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
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_98_t
 *
 */

typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_98_t;

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
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_99_t
 *
 */

typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_99_t;

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
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_100_t
 *
 */

typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_100_t;

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
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_101_t
 *
 */

typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_101_t;

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
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_102_t
 *
 */

typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_102_t;

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
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_103_t
 *
 */

typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_103_t;

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
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_104_t
 *
 */

typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_104_t;

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
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_105_t
 *
 */

typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_105_t;

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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_106_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_107_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_108_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_109_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_110_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_111_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_112_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_113_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_114_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_115_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_116_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_117_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_118_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_119_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_120_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_121_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_122_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_123_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_124_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_125_t
 *
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
 *   <td width="30%"> Duration of memory reset during power-on initialization. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_126_t
 *
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_127_t
 *
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_128_t
 *
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
 *   <td width="30%"> User-defined input register 0. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_129_t
 *
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
 *   <td width="30%"> User-defined input register 1. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_130_t
 *
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
 *   <td width="30%"> User-defined input register 2. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_131_t
 *
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
 *   <td width="30%"> User-defined input register 3. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_132_t
 *
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
 *   <td width="30%"> User-defined input register 4. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_133_t
 *
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
 *   <td width="30%"> User-defined input register 5. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_134_t
 *
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
 *   <td width="30%"> User-defined input register 6. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_135_t
 *
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
 *   <td width="30%"> User-defined input register 7. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_136_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_delay_0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for write data slice 0. This
 *        is read-only if the WRLVL_EN parameter is 1. If both
 *        the WRLVL_EN and the WRLVL_REG_EN parameters are 0,
 *        this can only be programmed during initialization
 *        or through software leveling. If the WRLVL_EN parameter
 *        is 0 and the WRLVL_REG_EN parameter is 1, this can
 *        be programmed at any time.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_137_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_delay_1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for write data slice 1. This
 *        is read-only if the WRLVL_EN parameter is 1. If both
 *        the WRLVL_EN and the WRLVL_REG_EN parameters are 0,
 *        this can only be programmed during initialization
 *        or through software leveling. If the WRLVL_EN parameter
 *        is 0 and the WRLVL_REG_EN parameter is 1, this can
 *        be programmed at any time.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_138_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_delay_2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for write data slice 2. This
 *        is read-only if the WRLVL_EN parameter is 1. If both
 *        the WRLVL_EN and the WRLVL_REG_EN parameters are 0,
 *        this can only be programmed during initialization
 *        or through software leveling. If the WRLVL_EN parameter
 *        is 0 and the WRLVL_REG_EN parameter is 1, this can
 *        be programmed at any time.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_139_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_delay_3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for write data slice 3. This
 *        is read-only if the WRLVL_EN parameter is 1. If both
 *        the WRLVL_EN and the WRLVL_REG_EN parameters are 0,
 *        this can only be programmed during initialization
 *        or through software leveling. If the WRLVL_EN parameter
 *        is 0 and the WRLVL_REG_EN parameter is 1, this can
 *        be programmed at any time.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_140_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_delay_4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for write data slice 4. This
 *        is read-only if the WRLVL_EN parameter is 1. If both
 *        the WRLVL_EN and the WRLVL_REG_EN parameters are 0,
 *        this can only be programmed during initialization
 *        or through software leveling. If the WRLVL_EN parameter
 *        is 0 and the WRLVL_REG_EN parameter is 1, this can
 *        be programmed at any time.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_141_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_delay_5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for write data slice 5. This
 *        is read-only if the WRLVL_EN parameter is 1. If both
 *        the WRLVL_EN and the WRLVL_REG_EN parameters are 0,
 *        this can only be programmed during initialization
 *        or through software leveling. If the WRLVL_EN parameter
 *        is 0 and the WRLVL_REG_EN parameter is 1, this can
 *        be programmed at any time.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_142_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_delay_6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for write data slice 6. This
 *        is read-only if the WRLVL_EN parameter is 1. If both
 *        the WRLVL_EN and the WRLVL_REG_EN parameters are 0,
 *        this can only be programmed during initialization
 *        or through software leveling. If the WRLVL_EN parameter
 *        is 0 and the WRLVL_REG_EN parameter is 1, this can
 *        be programmed at any time.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_143_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_delay_7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for write data slice 7. This
 *        is read-only if the WRLVL_EN parameter is 1. If both
 *        the WRLVL_EN and the WRLVL_REG_EN parameters are 0,
 *        this can only be programmed during initialization
 *        or through software leveling. If the WRLVL_EN parameter
 *        is 0 and the WRLVL_REG_EN parameter is 1, this can
 *        be programmed at any time.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_144_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_delay_8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for write data slice 8. This
 *        is read-only if the WRLVL_EN parameter is 1. If both
 *        the WRLVL_EN and the WRLVL_REG_EN parameters are 0,
 *        this can only be programmed during initialization
 *        or through software leveling. If the WRLVL_EN parameter
 *        is 0 and the WRLVL_REG_EN parameter is 1, this can
 *        be programmed at any time.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_145_t
 *
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_146_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bist_fail_addr </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address of BIST error. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_147_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  4;
     unsigned      bist_fail_addr                            :  4;/* only 3 bits on 2500 */
#else    /* Little Endian */
     unsigned      bist_fail_addr                            :  4;
     unsigned      reserved0                                 :  4;
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_148_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bist_start_address </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start BIST checking at this address. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_149_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  4;
     unsigned      bist_start_address                        :  4;/* only 3 bits on 2500 */
#else    /* Little Endian */
     unsigned      bist_start_address                        :  4;
     unsigned      reserved0                                 :  4;
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_150_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_c_addr </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address of correctable ECC event. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_151_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  4;
     unsigned      ecc_c_addr                                :  4;/* only 3 bits on 2500 */
#else    /* Little Endian */
     unsigned      ecc_c_addr                                :  4;
     unsigned      reserved0                                 :  4;
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_152_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_u_addr </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address of uncorrectable ECC event. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_153_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  4;
     unsigned      ecc_u_addr                                :  4;/* only 3 bits on 2500 */
#else    /* Little Endian */
     unsigned      ecc_u_addr                                :  4;
     unsigned      reserved0                                 :  4;
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
 *   <td width="30%"> Address of command that caused an out-of-range interrupt.
 *        READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_154_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param out_of_range_addr </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address of command that caused an out-of-range interrupt.
 *        READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_155_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  4;
     unsigned      out_of_range_addr                         :  4;/* only 3 bits on 2500 */
#else    /* Little Endian */
     unsigned      out_of_range_addr                         :  4;
     unsigned      reserved0                                 :  4;
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
 *   <td width="30%"> Address of command that caused the PORT command error.
 *        READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_156_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param port_cmd_error_addr </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address of command that caused the PORT command error.
 *        READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_157_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  4;
     unsigned      port_cmd_error_addr                       :  4;/* only 3 bits on 2500 */
#else    /* Little Endian */
     unsigned      port_cmd_error_addr                       :  4;
     unsigned      reserved0                                 :  4;
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
 *   <td width="30%"> Holds the error associated with the read level error
 *        or gate training error interrupt. Uppermost bit corresponds
 *        to a TDFI_RDLVL_RESP violation. Next uppermost bit
 *        corresponds to a TDFI_RDLVL_MAX violation. Lower bits
 *        are reserved. Value of 1 indicates an error. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_158_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
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
 *   <td width="30%"> Holds the error associated with the read level error
 *        or gate training error interrupt. Uppermost bit corresponds
 *        to a TDFI_RDLVL_RESP violation. Next uppermost bit
 *        corresponds to a TDFI_RDLVL_MAX violation. Lower bits
 *        are reserved. Value of 1 indicates an error. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_159_t
 *
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
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_160_t
 *
 */

typedef struct
{
     unsigned  int                 obsolete0;
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
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_161_t
 *
 */

typedef struct
{
     unsigned  int                 obsolete0;
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_162_t
 *
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_163_t
 *
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_164_t
 *
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_165_t
 *
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
 *   <td width="30%"> Mask for the dfi_rdlvl_resp signal during gate training. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_166_t
 *
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
 *   <td width="30%"> Mask for the dfi_rdlvl_resp signal during gate training. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_167_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_resp_mask </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Mask for the dfi_rdlvl_resp signal during gate training. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_168_t
 *
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
 *   <td width="30%"> Mask for the dfi_rdlvl_resp signal during read leveling. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_169_t
 *
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
 *   <td width="30%"> Mask for the dfi_rdlvl_resp signal during read leveling. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_170_t
 *
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_resp_mask </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Mask for the dfi_rdlvl_resp signal during read leveling. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_171_t
 *
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
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_172_t
 *
 */

typedef struct
{
     unsigned  int                 obsolete0;
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
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_173_t
 *
 */

typedef struct
{
     unsigned  int                 obsolete0;
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
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_174_t
 *
 */

typedef struct
{
     unsigned  int                 obsolete0;
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
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_175_t
 *
 */

typedef struct
{
     unsigned  int                 obsolete0;
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
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_176_t
 *
 */

typedef struct
{
     unsigned  int                 obsolete0;
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
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_177_t
 *
 */

typedef struct
{
     unsigned  int                 obsolete0;
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
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_178_t
 *
 */

typedef struct
{
     unsigned  int                 obsolete0;
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
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_179_t
 *
 */

typedef struct
{
     unsigned  int                 obsolete0;
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
 *     <td width="30%"> @param obsolete3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_reg_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enable the dfi_rdlvl_delay_X signals to be programmed
 *        when hardware and software leveling are disabled.
 *        Set to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_reg_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enable the dfi_rdlvl_gate_delay_X signals to be programmed
 *        when hardware and software leveling are disabled.
 *        Set to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_180_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      reserved0                                 :  7;
     unsigned      rdlvl_reg_en                              :  1;
     unsigned      reserved1                                 :  7;
     unsigned      rdlvl_gate_reg_en                         :  1;
     unsigned      obsolete0                                 :  8;
#else    /* Little Endian */
     unsigned      obsolete0                                 :  8;
     unsigned      rdlvl_gate_reg_en                         :  1;
     unsigned      reserved1                                 :  7;
     unsigned      rdlvl_reg_en                              :  1;
     unsigned      reserved0                                 :  7;
     unsigned      obsolete3                                 :  8;
#endif
} ncp_denali_DENALI_CTL_180_t;

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
 *   <td width="30%"> Indicates that a ZQ command is currently in progress.
 *        Value of 1 indicates command in progress. READ-ONLY
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
 *   <td width="30%"> Selects whether a ZQCS command will calibrate just
 *        one chip select or all chip selects. Set to 1 for
 *        1 chip select.
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
 *   <td width="30%"> Enable the dfi_wrlvl_delay_X signals to be programmed
 *        when hardware and software leveling are disabled.
 *        Set to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_181_t
 *
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
     unsigned      obsolete0                                 :  8;
#else    /* Little Endian */
     unsigned      obsolete0                                 :  8;
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
 *   <td width="30%"> Additional delay to insert between reads and writes
 *        to the same chip select. Program to a non-zero value.
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
 *   <td width="30%"> Additional delay to insert between reads and writes
 *        to different chip selects. Program to a non-zero value.
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
 *   <td width="30%"> Additional delay to insert between two reads to the
 *        same chip select. Any value including 0x0 supported.
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
 *   <td width="30%"> Additional delay to insert between reads and reads
 *        to different chip selects. Program to a non-zero value.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_182_t
 *
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
 *     <td width="30%"> @param obsolete3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> PADDING_BITS </td>
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
 *   <td width="30%"> Additional delay to insert between two writes to the
 *        same chip select. Any value including 0x0 supported.
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
 *        to different chip selects. Program to a non-zero value.
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
 *   <td width="30%"> DRAM CAS-to-CAS value in cycles. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_183_t
 *
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
} ncp_denali_DENALI_CTL_183_t;

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
 *   <td width="30%"> PADDING_BITS </td>
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
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trp_ab </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DRAM TRP all bank value in cycles. </td>
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_184_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      reserved0                                 :  2;
     unsigned      add_odt_clk_difftype_diffcs               :  6;
     unsigned      reserved1                                 :  3;
     unsigned      trp_ab                                    :  5;
     unsigned      reserved2                                 :  4;
     unsigned      add_odt_clk_sametype_diffcs               :  4;
#else    /* Little Endian */
     unsigned      add_odt_clk_sametype_diffcs               :  4;
     unsigned      reserved2                                 :  4;
     unsigned      trp_ab                                    :  5;
     unsigned      reserved1                                 :  3;
     unsigned      add_odt_clk_difftype_diffcs               :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete3                                 :  8;
#endif
} ncp_denali_DENALI_CTL_184_t;

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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_185_t
 *
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
 *   <td width="30%"> Number of clock cycles needed for a ZQINIT command. </td>
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_186_t
 *
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
 *   <td width="30%"> Data to program into memory mode register 0 for chip
 *        select 1.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr0_data_0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 0 for chip
 *        select 0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_187_t
 *
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
 *   <td width="30%"> Data to program into memory mode register 0 for chip
 *        select 3.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr0_data_2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 0 for chip
 *        select 2.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_188_t
 *
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_189_t
 *
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_190_t
 *
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_191_t
 *
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_192_t
 *
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_193_t
 *
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_194_t
 *
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
 *        for data slice 1. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_begin_delay_0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for first 1 to 0 DQ transition
 *        for data slice 0. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_195_t
 *
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
 *        for data slice 3. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_begin_delay_2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for first 1 to 0 DQ transition
 *        for data slice 2. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_196_t
 *
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
 *        for data slice 5. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_begin_delay_4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for first 1 to 0 DQ transition
 *        for data slice 4. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_197_t
 *
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
 *        for data slice 7. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_begin_delay_6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for first 1 to 0 DQ transition
 *        for data slice 6. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_198_t
 *
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
 *        within the DQ data eye for data slice 0. This is read-only
 *        if the RDLVL_EN parameter is 1. If both the RDLVL_EN
 *        and the RDLVL_REG_EN parameters are 0, this can only
 *        be programmed during initialization or through software
 *        leveling. If the RDLVL_EN parameter is 0 and the RDLVL_REG_EN
 *        parameter is 1, this can be programmed at any time.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_begin_delay_8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for first 1 to 0 DQ transition
 *        for data slice 8. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_199_t
 *
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
 *        within the DQ data eye for data slice 2. This is read-only
 *        if the RDLVL_EN parameter is 1. If both the RDLVL_EN
 *        and the RDLVL_REG_EN parameters are 0, this can only
 *        be programmed during initialization or through software
 *        leveling. If the RDLVL_EN parameter is 0 and the RDLVL_REG_EN
 *        parameter is 1, this can be programmed at any time.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_delay_1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements where read DQS is placed
 *        within the DQ data eye for data slice 1. This is read-only
 *        if the RDLVL_EN parameter is 1. If both the RDLVL_EN
 *        and the RDLVL_REG_EN parameters are 0, this can only
 *        be programmed during initialization or through software
 *        leveling. If the RDLVL_EN parameter is 0 and the RDLVL_REG_EN
 *        parameter is 1, this can be programmed at any time.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_200_t
 *
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
 *        within the DQ data eye for data slice 4. This is read-only
 *        if the RDLVL_EN parameter is 1. If both the RDLVL_EN
 *        and the RDLVL_REG_EN parameters are 0, this can only
 *        be programmed during initialization or through software
 *        leveling. If the RDLVL_EN parameter is 0 and the RDLVL_REG_EN
 *        parameter is 1, this can be programmed at any time.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_delay_3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements where read DQS is placed
 *        within the DQ data eye for data slice 3. This is read-only
 *        if the RDLVL_EN parameter is 1. If both the RDLVL_EN
 *        and the RDLVL_REG_EN parameters are 0, this can only
 *        be programmed during initialization or through software
 *        leveling. If the RDLVL_EN parameter is 0 and the RDLVL_REG_EN
 *        parameter is 1, this can be programmed at any time.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_201_t
 *
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
 *        within the DQ data eye for data slice 6. This is read-only
 *        if the RDLVL_EN parameter is 1. If both the RDLVL_EN
 *        and the RDLVL_REG_EN parameters are 0, this can only
 *        be programmed during initialization or through software
 *        leveling. If the RDLVL_EN parameter is 0 and the RDLVL_REG_EN
 *        parameter is 1, this can be programmed at any time.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_delay_5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements where read DQS is placed
 *        within the DQ data eye for data slice 5. This is read-only
 *        if the RDLVL_EN parameter is 1. If both the RDLVL_EN
 *        and the RDLVL_REG_EN parameters are 0, this can only
 *        be programmed during initialization or through software
 *        leveling. If the RDLVL_EN parameter is 0 and the RDLVL_REG_EN
 *        parameter is 1, this can be programmed at any time.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_202_t
 *
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
 *        within the DQ data eye for data slice 8. This is read-only
 *        if the RDLVL_EN parameter is 1. If both the RDLVL_EN
 *        and the RDLVL_REG_EN parameters are 0, this can only
 *        be programmed during initialization or through software
 *        leveling. If the RDLVL_EN parameter is 0 and the RDLVL_REG_EN
 *        parameter is 1, this can be programmed at any time.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_delay_7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements where read DQS is placed
 *        within the DQ data eye for data slice 7. This is read-only
 *        if the RDLVL_EN parameter is 1. If both the RDLVL_EN
 *        and the RDLVL_REG_EN parameters are 0, this can only
 *        be programmed during initialization or through software
 *        leveling. If the RDLVL_EN parameter is 0 and the RDLVL_REG_EN
 *        parameter is 1, this can be programmed at any time.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_203_t
 *
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
 *        for data slice 1. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_end_delay_0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for first 0 to 1 DQ transition
 *        for data slice 0. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_204_t
 *
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
 *        for data slice 3. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_end_delay_2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for first 0 to 1 DQ transition
 *        for data slice 2. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_205_t
 *
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
 *        for data slice 5. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_end_delay_4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for first 0 to 1 DQ transition
 *        for data slice 4. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_206_t
 *
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
 *        for data slice 7. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_end_delay_6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for first 0 to 1 DQ transition
 *        for data slice 6. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_207_t
 *
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
 *        rising edge of DQS for data slice 0. This is read-only
 *        if the RDLVL_GATE_EN parameter is 1. If both the RDLVL_GATE_EN
 *        and the RDLVL_GATE_REG_EN parameters are 0, this can
 *        only be programmed during initialization or through
 *        software leveling. If the RDLVL_GATE_EN parameter
 *        is 0 and the RDLVL_GATE_REG_EN parameter is 1, this
 *        can be programmed at any time.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_end_delay_8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements for first 0 to 1 DQ transition
 *        for data slice 8. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_208_t
 *
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
 *        rising edge of DQS for data slice 2. This is read-only
 *        if the RDLVL_GATE_EN parameter is 1. If both the RDLVL_GATE_EN
 *        and the RDLVL_GATE_REG_EN parameters are 0, this can
 *        only be programmed during initialization or through
 *        software leveling. If the RDLVL_GATE_EN parameter
 *        is 0 and the RDLVL_GATE_REG_EN parameter is 1, this
 *        can be programmed at any time.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_delay_1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements where gate is aligned to
 *        rising edge of DQS for data slice 1. This is read-only
 *        if the RDLVL_GATE_EN parameter is 1. If both the RDLVL_GATE_EN
 *        and the RDLVL_GATE_REG_EN parameters are 0, this can
 *        only be programmed during initialization or through
 *        software leveling. If the RDLVL_GATE_EN parameter
 *        is 0 and the RDLVL_GATE_REG_EN parameter is 1, this
 *        can be programmed at any time.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_209_t
 *
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
 *        rising edge of DQS for data slice 4. This is read-only
 *        if the RDLVL_GATE_EN parameter is 1. If both the RDLVL_GATE_EN
 *        and the RDLVL_GATE_REG_EN parameters are 0, this can
 *        only be programmed during initialization or through
 *        software leveling. If the RDLVL_GATE_EN parameter
 *        is 0 and the RDLVL_GATE_REG_EN parameter is 1, this
 *        can be programmed at any time.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_delay_3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements where gate is aligned to
 *        rising edge of DQS for data slice 3. This is read-only
 *        if the RDLVL_GATE_EN parameter is 1. If both the RDLVL_GATE_EN
 *        and the RDLVL_GATE_REG_EN parameters are 0, this can
 *        only be programmed during initialization or through
 *        software leveling. If the RDLVL_GATE_EN parameter
 *        is 0 and the RDLVL_GATE_REG_EN parameter is 1, this
 *        can be programmed at any time.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_210_t
 *
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
 *        rising edge of DQS for data slice 6. This is read-only
 *        if the RDLVL_GATE_EN parameter is 1. If both the RDLVL_GATE_EN
 *        and the RDLVL_GATE_REG_EN parameters are 0, this can
 *        only be programmed during initialization or through
 *        software leveling. If the RDLVL_GATE_EN parameter
 *        is 0 and the RDLVL_GATE_REG_EN parameter is 1, this
 *        can be programmed at any time.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_delay_5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements where gate is aligned to
 *        rising edge of DQS for data slice 5. This is read-only
 *        if the RDLVL_GATE_EN parameter is 1. If both the RDLVL_GATE_EN
 *        and the RDLVL_GATE_REG_EN parameters are 0, this can
 *        only be programmed during initialization or through
 *        software leveling. If the RDLVL_GATE_EN parameter
 *        is 0 and the RDLVL_GATE_REG_EN parameter is 1, this
 *        can be programmed at any time.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_211_t
 *
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
 *        rising edge of DQS for data slice 8. This is read-only
 *        if the RDLVL_GATE_EN parameter is 1. If both the RDLVL_GATE_EN
 *        and the RDLVL_GATE_REG_EN parameters are 0, this can
 *        only be programmed during initialization or through
 *        software leveling. If the RDLVL_GATE_EN parameter
 *        is 0 and the RDLVL_GATE_REG_EN parameter is 1, this
 *        can be programmed at any time.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_delay_7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of delay elements where gate is aligned to
 *        rising edge of DQS for data slice 7. This is read-only
 *        if the RDLVL_GATE_EN parameter is 1. If both the RDLVL_GATE_EN
 *        and the RDLVL_GATE_REG_EN parameters are 0, this can
 *        only be programmed during initialization or through
 *        software leveling. If the RDLVL_GATE_EN parameter
 *        is 0 and the RDLVL_GATE_REG_EN parameter is 1, this
 *        can be programmed at any time.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_212_t
 *
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_213_t
 *
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
 *   <td width="30%"> Calculated midpoint of DQ delay for data slice 1.
 *        READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_midpoint_delay_0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Calculated midpoint of DQ delay for data slice 0.
 *        READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_214_t
 *
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
 *   <td width="30%"> Calculated midpoint of DQ delay for data slice 3.
 *        READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_midpoint_delay_2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Calculated midpoint of DQ delay for data slice 2.
 *        READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_215_t
 *
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
 *   <td width="30%"> Calculated midpoint of DQ delay for data slice 5.
 *        READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_midpoint_delay_4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Calculated midpoint of DQ delay for data slice 4.
 *        READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_216_t
 *
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
 *   <td width="30%"> Calculated midpoint of DQ delay for data slice 7.
 *        READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_midpoint_delay_6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Calculated midpoint of DQ delay for data slice 6.
 *        READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_217_t
 *
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
 *   <td width="30%"> Calculated midpoint of DQ delay for data slice 8.
 *        READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_218_t
 *
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_219_t
 *
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_220_t
 *
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_221_t
 *
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_222_t
 *
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
 *        and read level response for the PHY Evaluation mode.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_223_t
 *
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_224_t
 *
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
 *        and write level response for the PHY Evaluation mode.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_225_t
 *
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_226_t
 *
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
 *     <td width="30%"> @param tdfi_phyupd_type1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Holds the DFI tPHYUPD_TYPE1 timing parameter. If programmed
 *        to a non-zero, a timing violation will cause an interrupt
 *        and bit (3) set in the UPDATE_ERROR_STATUS parameter.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
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
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tbst_int_interval </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM burst interrupt interval value in cycles. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_227_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      tdfi_phyupd_type1                         : 16;
     unsigned      reserved0                                 :  3;
     unsigned      tckesr                                    :  5;
     unsigned      reserved1                                 :  5;
     unsigned      tbst_int_interval                         :  3;
#else    /* Little Endian */
     unsigned      tbst_int_interval                         :  3;
     unsigned      reserved1                                 :  5;
     unsigned      tckesr                                    :  5;
     unsigned      reserved0                                 :  3;
     unsigned      tdfi_phyupd_type1                         : 16;
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
 *     <td width="30%"> @param tdfi_phyupd_type3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Holds the DFI tPHYUPD_TYPE3 timing parameter. If programmed
 *        to a non-zero, a timing violation will cause an interrupt
 *        and bit (5) set in the UPDATE_ERROR_STATUS parameter.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_phyupd_type2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Holds the DFI tPHYUPD_TYPE2 timing parameter. If programmed
 *        to a non-zero, a timing violation will cause an interrupt
 *        and bit (4) set in the UPDATE_ERROR_STATUS parameter.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_228_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      tdfi_phyupd_type3                         : 16;
     unsigned      tdfi_phyupd_type2                         : 16;
#else    /* Little Endian */
     unsigned      tdfi_phyupd_type2                         : 16;
     unsigned      tdfi_phyupd_type3                         : 16;
#endif
} ncp_denali_DENALI_CTL_228_t;

/*! @struct ncp_denali_DENALI_CTL_229_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_229_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tras_max </td>
 *     <td width="20%" align="center"> 17 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM TRAS_MAX value in cycles. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_229_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  7;
     unsigned      tras_max                                  : 17;
#else    /* Little Endian */
     unsigned      tras_max                                  : 17;
     unsigned      reserved0                                 :  7;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_229_t;

/*! @struct ncp_denali_DENALI_CTL_230_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_230_t\n
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
 *   <td width="30%"> Additional delay to insert between read and write
 *        transaction types to the same chip select to meet
 *        ODT timing requirements.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trfc </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM TRFC value in cycles. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_230_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      add_odt_clk_r2w_samecs                    :  4;
     unsigned      obsolete1                                 :  8;
     unsigned      reserved1                                 :  6;
     unsigned      trfc                                      : 10;
#else    /* Little Endian */
     unsigned      trfc                                      : 10;
     unsigned      reserved1                                 :  6;
     unsigned      obsolete1                                 :  8;
     unsigned      add_odt_clk_r2w_samecs                    :  4;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_230_t;

/*! @struct ncp_denali_DENALI_CTL_231_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_231_t\n
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
 *   <td width="30%"> Enable the MC write leveling module. Set to 1 to enable. </td>
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
 *   <td width="30%"> Additional delay to insert between write and read
 *        transaction types to the same chip select to meet
 *        ODT timing requirements. Any value including 0x0 supported.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_231_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      wrlvl_refresh_interval                    : 16;/* obsolete in 5500 */
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
} ncp_denali_DENALI_CTL_231_t;

/*! @struct ncp_denali_DENALI_CTL_232_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_232_t\n
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
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cke_status </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Register access to cke_status signal. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_232_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      tdfi_rdlvl_load                           :  8;
     unsigned      tdfi_wrlvl_load                           :  8;
     unsigned      reserved0                                 :  7;
     unsigned      mem_rst_valid                             :  1;
     unsigned      reserved1                                 :  4;
     unsigned      cke_status                                :  4;
#else    /* Little Endian */
     unsigned      cke_status                                :  4;
     unsigned      reserved1                                 :  4;
     unsigned      mem_rst_valid                             :  1;
     unsigned      reserved0                                 :  7;
     unsigned      tdfi_wrlvl_load                           :  8;
     unsigned      tdfi_rdlvl_load                           :  8;
#endif
} ncp_denali_DENALI_CTL_232_t;

/*! @struct ncp_denali_DENALI_CTL_233_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_233_t\n
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_233_t
 *
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
} ncp_denali_DENALI_CTL_233_t;

/*! @struct ncp_denali_DENALI_CTL_234_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_234_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdimm_ctl_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> RDIMM 32882 control word values for DIMM 0. Bits (3:0)
 *        correlate to control word 0, bits (7:4) correlate
 *        to control word 1, etc.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_234_t
 *
 */

typedef struct
{
     unsigned  int               rdimm_ctl_0;
} ncp_denali_DENALI_CTL_234_t;

/*! @struct ncp_denali_DENALI_CTL_235_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_235_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdimm_ctl_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> RDIMM 32882 control word values for DIMM 0. Bits (3:0)
 *        correlate to control word 0, bits (7:4) correlate
 *        to control word 1, etc.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_235_t
 *
 */

typedef struct
{
     unsigned  int               rdimm_ctl_0;
} ncp_denali_DENALI_CTL_235_t;

/*! @struct ncp_denali_DENALI_CTL_236_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_236_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cs_map_dimm_0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines which chip selects are contained on DIMM 0.
 *        Bit (0) controls cs0, bit (1) controls cs1, etc. Set
 *        each bit to 1 to enable for DIMM 0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_236_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  4;
     unsigned      cs_map_dimm_0                             :  4;
#else    /* Little Endian */
     unsigned      cs_map_dimm_0                             :  4;
     unsigned      reserved0                                 :  4;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_236_t;

/*! @struct ncp_denali_DENALI_CTL_237_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_237_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdimm_ctl_1 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> RDIMM 32882 control word values for DIMM 1. Bits (3:0)
 *        correlate to control word 0, bits (7:4) correlate
 *        to control word 1, etc.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_237_t
 *
 */

typedef struct
{
     unsigned  int               rdimm_ctl_1;
} ncp_denali_DENALI_CTL_237_t;

/*! @struct ncp_denali_DENALI_CTL_238_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_238_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdimm_ctl_1 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> RDIMM 32882 control word values for DIMM 1. Bits (3:0)
 *        correlate to control word 0, bits (7:4) correlate
 *        to control word 1, etc.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_238_t
 *
 */

typedef struct
{
     unsigned  int               rdimm_ctl_1;
} ncp_denali_DENALI_CTL_238_t;

/*! @struct ncp_denali_DENALI_CTL_239_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_239_t\n
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
 *     <td width="30%"> @param rdimm_cww_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Triggers a control word write to all SSTE32882 DIMMs
 *        specified in the RDIMM_CW_MAP parameter with the values
 *        in the RDIMM_CTL_X parameter(s). Ignored during initialization
 *        because an automatic control word write happens during
 *        initialization. WRITE-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdimm_cw_map </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines which SSTE32882 control words will be updated
 *        during initialization. Bit (0) correlates to control
 *        word 0, bit (1) correlates to control word 1, etc.
 *        Set each bit to 1 to write.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cs_map_dimm_1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines which chip selects are contained on DIMM 1.
 *        Bit (0) controls cs0, bit (1) controls cs1, etc. Set
 *        each bit to 1 to enable for DIMM 1.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_239_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      rdimm_cww_req                             :  1;
     unsigned      rdimm_cw_map                              : 16;
     unsigned      reserved1                                 :  4;
     unsigned      cs_map_dimm_1                             :  4;
#else    /* Little Endian */
     unsigned      cs_map_dimm_1                             :  4;
     unsigned      reserved1                                 :  4;
     unsigned      rdimm_cw_map                              : 16;
     unsigned      rdimm_cww_req                             :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_239_t;

/*! @struct ncp_denali_DENALI_CTL_240_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_240_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdimm_tmrd </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Holds the TMRD value in cycles for the SSTE32882 on
 *        the registered DIMM. This is the delay required from
 *        a control word write to another control word write
 *        or to a DRAM access.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdimm_cw_hold_cke_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines if the CKE value will be held or asserted
 *        for all DDR3 RDIMM control word accesses. Set to 1
 *        to hold current value.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_240_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 : 16;
     unsigned      reserved0                                 :  4;
     unsigned      rdimm_tmrd                                :  4;
     unsigned      reserved1                                 :  7;
     unsigned      rdimm_cw_hold_cke_en                      :  1;
#else    /* Little Endian */
     unsigned      rdimm_cw_hold_cke_en                      :  1;
     unsigned      reserved1                                 :  7;
     unsigned      rdimm_tmrd                                :  4;
     unsigned      reserved0                                 :  4;
     unsigned      obsolete2                                 : 16;
#endif
} ncp_denali_DENALI_CTL_240_t;

/*! @struct ncp_denali_DENALI_CTL_241_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_241_t\n
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
 *     <td width="30%"> @param reg_dimm_parity_error </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Contains one hot indication of registered DIMM parity
 *        errors. Bit (0) correlates to DIMM0, bit (1) correlates
 *        to DIMM1, etc. Value of 1 indicates an error on that
 *        DIMM. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdimm_tstab </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Holds the TSTAB value in cycles for the SSTE32882
 *        on the registered DIMM. This is the delay required
 *        from a control word write to CW2 or CW10 to another
 *        control word write or to a DRAM access.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_241_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      reg_dimm_parity_error                     :  2;/* obsolete in 5500 */
     unsigned      rdimm_tstab                               : 24;
#else    /* Little Endian */
     unsigned      rdimm_tstab                               : 24;
     unsigned      reg_dimm_parity_error                     :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_241_t;

/*! @struct ncp_denali_DENALI_CTL_242_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_242_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param txard </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DRAM TXARD value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tref_interval </td>
 *     <td width="20%" align="center"> 14 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the number of cycles between refreshes to
 *        different chip selects.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_242_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      txard                                     : 16;
     unsigned      reserved0                                 :  2;
     unsigned      tref_interval                             : 14;
#else    /* Little Endian */
     unsigned      tref_interval                             : 14;
     unsigned      reserved0                                 :  2;
     unsigned      txard                                     : 16;
#endif
} ncp_denali_DENALI_CTL_242_t;

/*! @struct ncp_denali_DENALI_CTL_243_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_243_t\n
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
 *     <td width="30%"> @param lowpower_refresh_enable </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Enable refreshes while in low power mode. Bit (0)
 *        controls cs0, bit (1) controls cs1, etc. Set each
 *        bit to 1 to disable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param srefresh_exit_no_refresh </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Disables the automatic refresh request associated
 *        with self-refresh exit. Set to 1 to disable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param txards </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM TXARDS value in cycles. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_243_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      lowpower_refresh_enable                   :  4;
     unsigned      reserved1                                 :  7;
     unsigned      srefresh_exit_no_refresh                  :  1;
     unsigned      txards                                    : 16;
#else    /* Little Endian */
     unsigned      txards                                    : 16;
     unsigned      srefresh_exit_no_refresh                  :  1;
     unsigned      reserved1                                 :  7;
     unsigned      lowpower_refresh_enable                   :  4;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_243_t;

/*! @struct ncp_denali_DENALI_CTL_244_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_244_t\n
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
 *     <td width="30%"> @param lp_state </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Low power state status register. Bits (4:0) indicate
 *        the current low power state and bit (5) set indicates
 *        that status bits are valid. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lp_cmd </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Low power software command request interface. Bit
 *        (0) controls exit, bit (1) controls entry, bits (4:2)
 *        define the low power state, bit (5) controls memory
 *        clock gating, bit (6) controls controller clock gating,
 *        and bit (7) controls lock. WRITE-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cksrx </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Clock stable delay on self-refresh exit. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cksre </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Clock hold delay on self-refresh entry. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_244_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  2;
     unsigned      lp_state                                  :  6;
     unsigned      lp_cmd                                    :  8;
     unsigned      reserved1                                 :  4;
     unsigned      cksrx                                     :  4;
     unsigned      reserved2                                 :  4;
     unsigned      cksre                                     :  4;
#else    /* Little Endian */
     unsigned      cksre                                     :  4;
     unsigned      reserved2                                 :  4;
     unsigned      cksrx                                     :  4;
     unsigned      reserved1                                 :  4;
     unsigned      lp_cmd                                    :  8;
     unsigned      lp_state                                  :  6;
     unsigned      reserved0                                 :  2;
#endif
} ncp_denali_DENALI_CTL_244_t;

/*! @struct ncp_denali_DENALI_CTL_245_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_245_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lp_auto_exit_en </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enable auto exit from each of the low power states
 *        when a read or write command enters the command queue.
 *        Bit (0) controls power-down, bit (1) controls self-refresh,
 *        and bit (2) controls self-refresh with memory and
 *        controller clock gating. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lp_auto_entry_en </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enable auto entry into each of the low power states
 *        when the associated idle timer expires. Bit (0) controls
 *        power-down, bit (1) controls self-refresh, and bit
 *        (2) controls self-refresh with memory and controller
 *        clock gating. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lp_arb_state </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reports on the state of the arbiter. Bits (2:0) indicate
 *        which interface has control of the low power control
 *        module and bit (3) indicates if the software programmable
 *        interface has an active lock on the arbiter. For bits
 *        (2:0), value of 0 indicates module is idle, value
 *        of 1 indicates software programmable interface is
 *        in control, value of 2 indicates external pin interface
 *        is in control, value of 3 indicates automatic interface
 *        is in control, value of 4 indicates dynamic power
 *        control per chip select interface is in control, and
 *        value of 5 indicates that the internal memory controller
 *        is in control. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_245_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      reserved0                                 :  5;
     unsigned      lp_auto_exit_en                           :  3;
     unsigned      reserved1                                 :  5;
     unsigned      lp_auto_entry_en                          :  3;
     unsigned      reserved2                                 :  4;
     unsigned      lp_arb_state                              :  4;
#else    /* Little Endian */
     unsigned      lp_arb_state                              :  4;
     unsigned      reserved2                                 :  4;
     unsigned      lp_auto_entry_en                          :  3;
     unsigned      reserved1                                 :  5;
     unsigned      lp_auto_exit_en                           :  3;
     unsigned      reserved0                                 :  5;
     unsigned      obsolete3                                 :  8;
#endif
} ncp_denali_DENALI_CTL_245_t;

/*! @struct ncp_denali_DENALI_CTL_246_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_246_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_246_t
 *
 */

typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_246_t;

/*! @struct ncp_denali_DENALI_CTL_247_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_247_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_247_t
 *
 */

typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_247_t;

/*! @struct ncp_denali_DENALI_CTL_248_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_248_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lp_auto_sr_idle </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of refreshes counted until the controller will
 *        place memory in self-refresh.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_248_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      lp_auto_sr_idle                           :  8;
#else    /* Little Endian */
     unsigned      lp_auto_sr_idle                           :  8;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_248_t;

/*! @struct ncp_denali_DENALI_CTL_249_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_249_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved for future use. Must be cleared to 0x0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lp_auto_sr_mc_gate_idle </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of refreshes counted until the controller will
 *        place memory in self-refresh with controller and memory
 *        clock gating.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_249_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      reserved0                                 :  2;
     unsigned      reserved2                                 :  6;
     unsigned      obsolete1                                 :  8;
     unsigned      lp_auto_sr_mc_gate_idle                   :  8;
#else    /* Little Endian */
     unsigned      lp_auto_sr_mc_gate_idle                   :  8;
     unsigned      obsolete1                                 :  8;
     unsigned      reserved2                                 :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete3                                 :  8;
#endif
} ncp_denali_DENALI_CTL_249_t;

/*! @struct ncp_denali_DENALI_CTL_250_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_250_t\n
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
 *     <td width="30%"> @param write_modereg </td>
 *     <td width="20%" align="center"> 26 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Write mode register data to the DRAMs. Bits (7:0)
 *        define the mode register number if bit (23) is set,
 *        bits (15:8) define the chip select if bit (24) is
 *        clear, bits (23:16) define which mode register/s to
 *        write, bit (24) defines whether all chip selects will
 *        be written, and bit (25) triggers the write.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_250_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      write_modereg                             : 26;
#else    /* Little Endian */
     unsigned      write_modereg                             : 26;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_250_t;

/*! @struct ncp_denali_DENALI_CTL_251_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_251_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mrsingle_data_0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Data to program into memory mode register single write
 *        to chip select 0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mrw_status </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Write mode register status. Bit (0) set indicates
 *        a WRITE_MODEREG parameter programming error. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_251_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      mrsingle_data_0                           : 16;
     unsigned      mrw_status                                :  8;
#else    /* Little Endian */
     unsigned      mrw_status                                :  8;
     unsigned      mrsingle_data_0                           : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_251_t;

/*! @struct ncp_denali_DENALI_CTL_252_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_252_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param mrsingle_data_2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Data to program into memory mode register single write
 *        to chip select 2.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mrsingle_data_1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register single write
 *        to chip select 1.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_252_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      mrsingle_data_2                           : 16;
     unsigned      mrsingle_data_1                           : 16;
#else    /* Little Endian */
     unsigned      mrsingle_data_1                           : 16;
     unsigned      mrsingle_data_2                           : 16;
#endif
} ncp_denali_DENALI_CTL_252_t;

/*! @struct ncp_denali_DENALI_CTL_253_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_253_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mrsingle_data_3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register single write
 *        to chip select 3.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_253_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      mrsingle_data_3                           : 16;
#else    /* Little Endian */
     unsigned      mrsingle_data_3                           : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_253_t;

/*! @struct ncp_denali_DENALI_CTL_254_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_254_t\n
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
 *   <td width="30%"> Mask applied to data for BIST error checking. Bit
 *        (0) controls memory data path bit (0), bit (1) controls
 *        memory data path bit (1), etc. Set each bit to 1 to
 *        mask.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_254_t
 *
 */

typedef struct
{
     unsigned  int            bist_data_mask;
} ncp_denali_DENALI_CTL_254_t;

/*! @struct ncp_denali_DENALI_CTL_255_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_255_t\n
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
 *   <td width="30%"> Mask applied to data for BIST error checking. Bit
 *        (0) controls memory data path bit (0), bit (1) controls
 *        memory data path bit (1), etc. Set each bit to 1 to
 *        mask.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_255_t
 *
 */

typedef struct
{
     unsigned  int            bist_data_mask;
} ncp_denali_DENALI_CTL_255_t;

/*! @struct ncp_denali_DENALI_CTL_256_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_256_t\n
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
 *   <td width="30%"> Mask applied to data for BIST error checking. Bit
 *        (0) controls memory data path bit (0), bit (1) controls
 *        memory data path bit (1), etc. Set each bit to 1 to
 *        mask.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_256_t
 *
 */

typedef struct
{
     unsigned  int            bist_data_mask;
} ncp_denali_DENALI_CTL_256_t;

/*! @struct ncp_denali_DENALI_CTL_257_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_257_t\n
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
 *   <td width="30%"> Mask applied to data for BIST error checking. Bit
 *        (0) controls memory data path bit (0), bit (1) controls
 *        memory data path bit (1), etc. Set each bit to 1 to
 *        mask.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_257_t
 *
 */

typedef struct
{
     unsigned  int            bist_data_mask;
} ncp_denali_DENALI_CTL_257_t;

/*! @struct ncp_denali_DENALI_CTL_258_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_258_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param xor_check_bits </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Value to xor with generated ECC codes for forced write
 *        check.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_258_t
 *
 */

typedef struct
{
     unsigned  int            xor_check_bits;
} ncp_denali_DENALI_CTL_258_t;

/*! @struct ncp_denali_DENALI_CTL_259_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_259_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param controller_busy </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Indicator that the controller is processing a command.
 *        Evaluates all ports for outstanding transactions.
 *        Value of 1 indicates controller busy. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param inhibit_dram_cmd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Inhibit read/write command traffic and associated
 *        bank commands. Set to 1 to inhibit.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_259_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 : 16;
     unsigned      reserved0                                 :  7;
     unsigned      controller_busy                           :  1;
     unsigned      reserved1                                 :  7;
     unsigned      inhibit_dram_cmd                          :  1;
#else    /* Little Endian */
     unsigned      inhibit_dram_cmd                          :  1;
     unsigned      reserved1                                 :  7;
     unsigned      controller_busy                           :  1;
     unsigned      reserved0                                 :  7;
     unsigned      obsolete2                                 : 16;
#endif
} ncp_denali_DENALI_CTL_259_t;

/*! @struct ncp_denali_DENALI_CTL_260_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_260_t\n
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
 *     <td width="30%"> @param int_status </td>
 *     <td width="20%" align="center"> 26 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Status of interrupt features in the controller. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_260_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      int_status                                : 26;/* only 25 bits on 2500 */
#else    /* Little Endian */
     unsigned      int_status                                : 26;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_260_t;

/*! @struct ncp_denali_DENALI_CTL_261_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_261_t\n
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
 *     <td width="30%"> @param int_mask </td>
 *     <td width="20%" align="center"> 26 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Mask for controller_int signals from the INT_STATUS
 *        parameter.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_261_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      int_mask                                  : 26;/* only 25 bits on 2500 */
#else    /* Little Endian */
     unsigned      int_mask                                  : 26;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_261_t;

/*! @struct ncp_denali_DENALI_CTL_262_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_262_t\n
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_262_t
 *
 */

typedef struct
{
     unsigned  int             bist_exp_data;
} ncp_denali_DENALI_CTL_262_t;

/*! @struct ncp_denali_DENALI_CTL_263_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_263_t\n
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_263_t
 *
 */

typedef struct
{
     unsigned  int             bist_exp_data;
} ncp_denali_DENALI_CTL_263_t;

/*! @struct ncp_denali_DENALI_CTL_264_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_264_t\n
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_264_t
 *
 */

typedef struct
{
     unsigned  int             bist_exp_data;
} ncp_denali_DENALI_CTL_264_t;

/*! @struct ncp_denali_DENALI_CTL_265_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_265_t\n
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_265_t
 *
 */

typedef struct
{
     unsigned  int             bist_exp_data;
} ncp_denali_DENALI_CTL_265_t;

/*! @struct ncp_denali_DENALI_CTL_266_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_266_t\n
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_266_t
 *
 */

typedef struct
{
     unsigned  int             bist_exp_data;
} ncp_denali_DENALI_CTL_266_t;

/*! @struct ncp_denali_DENALI_CTL_267_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_267_t\n
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_267_t
 *
 */

typedef struct
{
     unsigned  int             bist_exp_data;
} ncp_denali_DENALI_CTL_267_t;

/*! @struct ncp_denali_DENALI_CTL_268_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_268_t\n
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_268_t
 *
 */

typedef struct
{
     unsigned  int             bist_exp_data;
} ncp_denali_DENALI_CTL_268_t;

/*! @struct ncp_denali_DENALI_CTL_269_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_269_t\n
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_269_t
 *
 */

typedef struct
{
     unsigned  int             bist_exp_data;
} ncp_denali_DENALI_CTL_269_t;

/*! @struct ncp_denali_DENALI_CTL_270_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_270_t\n
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_270_t
 *
 */

typedef struct
{
     unsigned  int            bist_fail_data;
} ncp_denali_DENALI_CTL_270_t;

/*! @struct ncp_denali_DENALI_CTL_271_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_271_t\n
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_271_t
 *
 */

typedef struct
{
     unsigned  int            bist_fail_data;
} ncp_denali_DENALI_CTL_271_t;

/*! @struct ncp_denali_DENALI_CTL_272_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_272_t\n
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_272_t
 *
 */

typedef struct
{
     unsigned  int            bist_fail_data;
} ncp_denali_DENALI_CTL_272_t;

/*! @struct ncp_denali_DENALI_CTL_273_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_273_t\n
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_273_t
 *
 */

typedef struct
{
     unsigned  int            bist_fail_data;
} ncp_denali_DENALI_CTL_273_t;

/*! @struct ncp_denali_DENALI_CTL_274_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_274_t\n
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_274_t
 *
 */

typedef struct
{
     unsigned  int            bist_fail_data;
} ncp_denali_DENALI_CTL_274_t;

/*! @struct ncp_denali_DENALI_CTL_275_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_275_t\n
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_275_t
 *
 */

typedef struct
{
     unsigned  int            bist_fail_data;
} ncp_denali_DENALI_CTL_275_t;

/*! @struct ncp_denali_DENALI_CTL_276_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_276_t\n
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_276_t
 *
 */

typedef struct
{
     unsigned  int            bist_fail_data;
} ncp_denali_DENALI_CTL_276_t;

/*! @struct ncp_denali_DENALI_CTL_277_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_277_t\n
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
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_277_t
 *
 */

typedef struct
{
     unsigned  int            bist_fail_data;
} ncp_denali_DENALI_CTL_277_t;

/*! @struct ncp_denali_DENALI_CTL_278_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_278_t\n
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
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved for future use. Must be cleared to 0x0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_error_status </td>
 *     <td width="20%" align="center"> 20 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Holds the error associated with the write level error
 *        interrupt. Bits (1:0) correspond to data slice 0,
 *        bits (3:2) correspond to data slice 1, etc. Value
 *        of 0 indicates success, value of 1 indicates no rising
 *        edge found, and value of 2 indicates no falling edge
 *        found. Uppermost bit corresponds to a TDFI_WRLVL_RESP
 *        violation. Next uppermost bit corresponds to a TDFI_WRLVL_MAX
 *        violation. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_278_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      reserved1                                 :  1;
     unsigned      reserved2                                 :  4;
     unsigned      wrlvl_error_status                        : 20;
#else    /* Little Endian */
     unsigned      wrlvl_error_status                        : 20;
     unsigned      reserved2                                 :  4;
     unsigned      reserved1                                 :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_278_t;

/*! @struct ncp_denali_DENALI_CTL_279_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_279_t\n
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
 *     <td width="30%"> @param axi0_start_addr_0 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Start address of port 0 address range 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param port_addr_protection_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enable port address range protection logic and interrupt
 *        generation. Set to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_279_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      axi0_start_addr_0                         : 21;
     unsigned      reserved1                                 :  7;
     unsigned      port_addr_protection_en                   :  1;
#else    /* Little Endian */
     unsigned      port_addr_protection_en                   :  1;
     unsigned      reserved1                                 :  7;
     unsigned      axi0_start_addr_0                         : 21;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_279_t;

/*! @struct ncp_denali_DENALI_CTL_280_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_280_t\n
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
 *     <td width="30%"> @param axi0_range_type_0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        0. Set to 0 for no access, set to 1 for read-only,
 *        set to 2 for write-only, or set to 3 for read and
 *        write.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_end_addr_0 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 0. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_280_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_type_0                         :  2;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_end_addr_0                           : 21;
#else    /* Little Endian */
     unsigned      axi0_end_addr_0                           : 21;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_type_0                         :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_280_t;

/*! @struct ncp_denali_DENALI_CTL_281_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_281_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_id_check_bits_0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed IDs for port 0 address range 0. Bit (0) correlates
 *        to requestor 0, bit (1) correlates to requestor 1,
 *        etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_prot_bits_0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        0. Set to 0 for asynchronous, set to 1 for 2:1 port:core
 *        pseudo-sync, set to 2 for 1:2 port:core pseudo-sync,
 *        or set to 3 for synchronous.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_281_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      axi0_range_id_check_bits_0                : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_prot_bits_0                    :  2;
#else    /* Little Endian */
     unsigned      axi0_range_prot_bits_0                    :  2;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_id_check_bits_0                : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_281_t;

/*! @struct ncp_denali_DENALI_CTL_282_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_282_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_start_addr_1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 1. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_282_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  3;
     unsigned      axi0_start_addr_1                         : 21;
#else    /* Little Endian */
     unsigned      axi0_start_addr_1                         : 21;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_282_t;

/*! @struct ncp_denali_DENALI_CTL_283_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_283_t\n
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
 *     <td width="30%"> @param axi0_range_type_1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        1. Set to 0 for no access, set to 1 for read-only,
 *        set to 2 for write-only, or set to 3 for read and
 *        write.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_end_addr_1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 1. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_283_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_type_1                         :  2;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_end_addr_1                           : 21;
#else    /* Little Endian */
     unsigned      axi0_end_addr_1                           : 21;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_type_1                         :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_283_t;

/*! @struct ncp_denali_DENALI_CTL_284_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_284_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_id_check_bits_1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed IDs for port 0 address range 1. Bit (0) correlates
 *        to requestor 0, bit (1) correlates to requestor 1,
 *        etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_prot_bits_1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        1. Set to 0 for asynchronous, set to 1 for 2:1 port:core
 *        pseudo-sync, set to 2 for 1:2 port:core pseudo-sync,
 *        or set to 3 for synchronous.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_284_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      axi0_range_id_check_bits_1                : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_prot_bits_1                    :  2;
#else    /* Little Endian */
     unsigned      axi0_range_prot_bits_1                    :  2;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_id_check_bits_1                : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_284_t;

/*! @struct ncp_denali_DENALI_CTL_285_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_285_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_start_addr_2 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 2. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_285_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  3;
     unsigned      axi0_start_addr_2                         : 21;
#else    /* Little Endian */
     unsigned      axi0_start_addr_2                         : 21;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_285_t;

/*! @struct ncp_denali_DENALI_CTL_286_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_286_t\n
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
 *     <td width="30%"> @param axi0_range_type_2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        2. Set to 0 for no access, set to 1 for read-only,
 *        set to 2 for write-only, or set to 3 for read and
 *        write.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_end_addr_2 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 2. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_286_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_type_2                         :  2;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_end_addr_2                           : 21;
#else    /* Little Endian */
     unsigned      axi0_end_addr_2                           : 21;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_type_2                         :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_286_t;

/*! @struct ncp_denali_DENALI_CTL_287_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_287_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_id_check_bits_2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed IDs for port 0 address range 2. Bit (0) correlates
 *        to requestor 0, bit (1) correlates to requestor 1,
 *        etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_prot_bits_2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        2. Set to 0 for asynchronous, set to 1 for 2:1 port:core
 *        pseudo-sync, set to 2 for 1:2 port:core pseudo-sync,
 *        or set to 3 for synchronous.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_287_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      axi0_range_id_check_bits_2                : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_prot_bits_2                    :  2;
#else    /* Little Endian */
     unsigned      axi0_range_prot_bits_2                    :  2;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_id_check_bits_2                : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_287_t;

/*! @struct ncp_denali_DENALI_CTL_288_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_288_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_start_addr_3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 3. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_288_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  3;
     unsigned      axi0_start_addr_3                         : 21;
#else    /* Little Endian */
     unsigned      axi0_start_addr_3                         : 21;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_288_t;

/*! @struct ncp_denali_DENALI_CTL_289_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_289_t\n
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
 *     <td width="30%"> @param axi0_range_type_3 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        3. Set to 0 for no access, set to 1 for read-only,
 *        set to 2 for write-only, or set to 3 for read and
 *        write.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_end_addr_3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 3. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_289_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_type_3                         :  2;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_end_addr_3                           : 21;
#else    /* Little Endian */
     unsigned      axi0_end_addr_3                           : 21;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_type_3                         :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_289_t;

/*! @struct ncp_denali_DENALI_CTL_290_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_290_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_id_check_bits_3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed IDs for port 0 address range 3. Bit (0) correlates
 *        to requestor 0, bit (1) correlates to requestor 1,
 *        etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_prot_bits_3 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        3. Set to 0 for asynchronous, set to 1 for 2:1 port:core
 *        pseudo-sync, set to 2 for 1:2 port:core pseudo-sync,
 *        or set to 3 for synchronous.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_290_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      axi0_range_id_check_bits_3                : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_prot_bits_3                    :  2;
#else    /* Little Endian */
     unsigned      axi0_range_prot_bits_3                    :  2;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_id_check_bits_3                : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_290_t;

/*! @struct ncp_denali_DENALI_CTL_291_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_291_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi1_start_addr_0 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 1 address range 0. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_291_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  3;
     unsigned      axi1_start_addr_0                         : 21;
#else    /* Little Endian */
     unsigned      axi1_start_addr_0                         : 21;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_291_t;

/*! @struct ncp_denali_DENALI_CTL_292_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_292_t\n
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
 *     <td width="30%"> @param axi1_range_type_0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Allowed transaction types for port 1 address range
 *        0. Set to 0 for no access, set to 1 for read-only,
 *        set to 2 for write-only, or set to 3 for read and
 *        write.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi1_end_addr_0 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 1 address range 0. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_292_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      axi1_range_type_0                         :  2;
     unsigned      reserved1                                 :  3;
     unsigned      axi1_end_addr_0                           : 21;
#else    /* Little Endian */
     unsigned      axi1_end_addr_0                           : 21;
     unsigned      reserved1                                 :  3;
     unsigned      axi1_range_type_0                         :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_292_t;

/*! @struct ncp_denali_DENALI_CTL_293_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_293_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi1_range_id_check_bits_0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed IDs for port 1 address range 0. Bit (0) correlates
 *        to requestor 0, bit (1) correlates to requestor 1,
 *        etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi1_range_prot_bits_0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 1 address range
 *        0. Set to 0 for asynchronous, set to 1 for 2:1 port:core
 *        pseudo-sync, set to 2 for 1:2 port:core pseudo-sync,
 *        or set to 3 for synchronous.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_293_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      axi1_range_id_check_bits_0                : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi1_range_prot_bits_0                    :  2;
#else    /* Little Endian */
     unsigned      axi1_range_prot_bits_0                    :  2;
     unsigned      reserved0                                 :  6;
     unsigned      axi1_range_id_check_bits_0                : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_293_t;

/*! @struct ncp_denali_DENALI_CTL_294_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_294_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi1_start_addr_1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 1 address range 1. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_294_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  3;
     unsigned      axi1_start_addr_1                         : 21;
#else    /* Little Endian */
     unsigned      axi1_start_addr_1                         : 21;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_294_t;

/*! @struct ncp_denali_DENALI_CTL_295_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_295_t\n
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
 *     <td width="30%"> @param axi1_range_type_1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Allowed transaction types for port 1 address range
 *        1. Set to 0 for no access, set to 1 for read-only,
 *        set to 2 for write-only, or set to 3 for read and
 *        write.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi1_end_addr_1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 1 address range 1. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_295_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      axi1_range_type_1                         :  2;
     unsigned      reserved1                                 :  3;
     unsigned      axi1_end_addr_1                           : 21;
#else    /* Little Endian */
     unsigned      axi1_end_addr_1                           : 21;
     unsigned      reserved1                                 :  3;
     unsigned      axi1_range_type_1                         :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_295_t;

/*! @struct ncp_denali_DENALI_CTL_296_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_296_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi1_range_id_check_bits_1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed IDs for port 1 address range 1. Bit (0) correlates
 *        to requestor 0, bit (1) correlates to requestor 1,
 *        etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi1_range_prot_bits_1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 1 address range
 *        1. Set to 0 for asynchronous, set to 1 for 2:1 port:core
 *        pseudo-sync, set to 2 for 1:2 port:core pseudo-sync,
 *        or set to 3 for synchronous.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_296_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      axi1_range_id_check_bits_1                : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi1_range_prot_bits_1                    :  2;
#else    /* Little Endian */
     unsigned      axi1_range_prot_bits_1                    :  2;
     unsigned      reserved0                                 :  6;
     unsigned      axi1_range_id_check_bits_1                : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_296_t;

/*! @struct ncp_denali_DENALI_CTL_297_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_297_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi1_start_addr_2 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 1 address range 2. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_297_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  3;
     unsigned      axi1_start_addr_2                         : 21;
#else    /* Little Endian */
     unsigned      axi1_start_addr_2                         : 21;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_297_t;

/*! @struct ncp_denali_DENALI_CTL_298_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_298_t\n
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
 *     <td width="30%"> @param axi1_range_type_2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Allowed transaction types for port 1 address range
 *        2. Set to 0 for no access, set to 1 for read-only,
 *        set to 2 for write-only, or set to 3 for read and
 *        write.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi1_end_addr_2 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 1 address range 2. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_298_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      axi1_range_type_2                         :  2;
     unsigned      reserved1                                 :  3;
     unsigned      axi1_end_addr_2                           : 21;
#else    /* Little Endian */
     unsigned      axi1_end_addr_2                           : 21;
     unsigned      reserved1                                 :  3;
     unsigned      axi1_range_type_2                         :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_298_t;

/*! @struct ncp_denali_DENALI_CTL_299_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_299_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi1_range_id_check_bits_2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed IDs for port 1 address range 2. Bit (0) correlates
 *        to requestor 0, bit (1) correlates to requestor 1,
 *        etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi1_range_prot_bits_2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 1 address range
 *        2. Set to 0 for asynchronous, set to 1 for 2:1 port:core
 *        pseudo-sync, set to 2 for 1:2 port:core pseudo-sync,
 *        or set to 3 for synchronous.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_299_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      axi1_range_id_check_bits_2                : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi1_range_prot_bits_2                    :  2;
#else    /* Little Endian */
     unsigned      axi1_range_prot_bits_2                    :  2;
     unsigned      reserved0                                 :  6;
     unsigned      axi1_range_id_check_bits_2                : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_299_t;

/*! @struct ncp_denali_DENALI_CTL_300_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_300_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi1_start_addr_3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 1 address range 3. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_300_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  3;
     unsigned      axi1_start_addr_3                         : 21;
#else    /* Little Endian */
     unsigned      axi1_start_addr_3                         : 21;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_300_t;

/*! @struct ncp_denali_DENALI_CTL_301_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_301_t\n
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
 *     <td width="30%"> @param axi1_range_type_3 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Allowed transaction types for port 1 address range
 *        3. Set to 0 for no access, set to 1 for read-only,
 *        set to 2 for write-only, or set to 3 for read and
 *        write.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi1_end_addr_3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 1 address range 3. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_301_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      axi1_range_type_3                         :  2;
     unsigned      reserved1                                 :  3;
     unsigned      axi1_end_addr_3                           : 21;
#else    /* Little Endian */
     unsigned      axi1_end_addr_3                           : 21;
     unsigned      reserved1                                 :  3;
     unsigned      axi1_range_type_3                         :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_301_t;

/*! @struct ncp_denali_DENALI_CTL_302_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_302_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi1_range_id_check_bits_3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed IDs for port 1 address range 3. Bit (0) correlates
 *        to requestor 0, bit (1) correlates to requestor 1,
 *        etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi1_range_prot_bits_3 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 1 address range
 *        3. Set to 0 for asynchronous, set to 1 for 2:1 port:core
 *        pseudo-sync, set to 2 for 1:2 port:core pseudo-sync,
 *        or set to 3 for synchronous.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_302_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      axi1_range_id_check_bits_3                : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi1_range_prot_bits_3                    :  2;
#else    /* Little Endian */
     unsigned      axi1_range_prot_bits_3                    :  2;
     unsigned      reserved0                                 :  6;
     unsigned      axi1_range_id_check_bits_3                : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_302_t;

/*! @struct ncp_denali_DENALI_CTL_303_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_303_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2_start_addr_0 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 2 address range 0. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_303_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  3;
     unsigned      axi2_start_addr_0                         : 21;
#else    /* Little Endian */
     unsigned      axi2_start_addr_0                         : 21;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_303_t;

/*! @struct ncp_denali_DENALI_CTL_304_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_304_t\n
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
 *     <td width="30%"> @param axi2_range_type_0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Allowed transaction types for port 2 address range
 *        0. Set to 0 for no access, set to 1 for read-only,
 *        set to 2 for write-only, or set to 3 for read and
 *        write.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2_end_addr_0 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 2 address range 0. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_304_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      axi2_range_type_0                         :  2;
     unsigned      reserved1                                 :  3;
     unsigned      axi2_end_addr_0                           : 21;
#else    /* Little Endian */
     unsigned      axi2_end_addr_0                           : 21;
     unsigned      reserved1                                 :  3;
     unsigned      axi2_range_type_0                         :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_304_t;

/*! @struct ncp_denali_DENALI_CTL_305_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_305_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2_range_id_check_bits_0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed IDs for port 2 address range 0. Bit (0) correlates
 *        to requestor 0, bit (1) correlates to requestor 1,
 *        etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2_range_prot_bits_0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 2 address range
 *        0. Set to 0 for asynchronous, set to 1 for 2:1 port:core
 *        pseudo-sync, set to 2 for 1:2 port:core pseudo-sync,
 *        or set to 3 for synchronous.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_305_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      axi2_range_id_check_bits_0                : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi2_range_prot_bits_0                    :  2;
#else    /* Little Endian */
     unsigned      axi2_range_prot_bits_0                    :  2;
     unsigned      reserved0                                 :  6;
     unsigned      axi2_range_id_check_bits_0                : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_305_t;

/*! @struct ncp_denali_DENALI_CTL_306_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_306_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2_start_addr_1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 2 address range 1. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_306_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  3;
     unsigned      axi2_start_addr_1                         : 21;
#else    /* Little Endian */
     unsigned      axi2_start_addr_1                         : 21;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_306_t;

/*! @struct ncp_denali_DENALI_CTL_307_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_307_t\n
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
 *     <td width="30%"> @param axi2_range_type_1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Allowed transaction types for port 2 address range
 *        1. Set to 0 for no access, set to 1 for read-only,
 *        set to 2 for write-only, or set to 3 for read and
 *        write.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2_end_addr_1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 2 address range 1. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_307_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      axi2_range_type_1                         :  2;
     unsigned      reserved1                                 :  3;
     unsigned      axi2_end_addr_1                           : 21;
#else    /* Little Endian */
     unsigned      axi2_end_addr_1                           : 21;
     unsigned      reserved1                                 :  3;
     unsigned      axi2_range_type_1                         :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_307_t;

/*! @struct ncp_denali_DENALI_CTL_308_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_308_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2_range_id_check_bits_1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed IDs for port 2 address range 1. Bit (0) correlates
 *        to requestor 0, bit (1) correlates to requestor 1,
 *        etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2_range_prot_bits_1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 2 address range
 *        1. Set to 0 for asynchronous, set to 1 for 2:1 port:core
 *        pseudo-sync, set to 2 for 1:2 port:core pseudo-sync,
 *        or set to 3 for synchronous.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_308_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      axi2_range_id_check_bits_1                : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi2_range_prot_bits_1                    :  2;
#else    /* Little Endian */
     unsigned      axi2_range_prot_bits_1                    :  2;
     unsigned      reserved0                                 :  6;
     unsigned      axi2_range_id_check_bits_1                : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_308_t;

/*! @struct ncp_denali_DENALI_CTL_309_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_309_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2_start_addr_2 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 2 address range 2. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_309_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  3;
     unsigned      axi2_start_addr_2                         : 21;
#else    /* Little Endian */
     unsigned      axi2_start_addr_2                         : 21;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_309_t;

/*! @struct ncp_denali_DENALI_CTL_310_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_310_t\n
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
 *     <td width="30%"> @param axi2_range_type_2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Allowed transaction types for port 2 address range
 *        2. Set to 0 for no access, set to 1 for read-only,
 *        set to 2 for write-only, or set to 3 for read and
 *        write.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2_end_addr_2 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 2 address range 2. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_310_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      axi2_range_type_2                         :  2;
     unsigned      reserved1                                 :  3;
     unsigned      axi2_end_addr_2                           : 21;
#else    /* Little Endian */
     unsigned      axi2_end_addr_2                           : 21;
     unsigned      reserved1                                 :  3;
     unsigned      axi2_range_type_2                         :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_310_t;

/*! @struct ncp_denali_DENALI_CTL_311_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_311_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2_range_id_check_bits_2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed IDs for port 2 address range 2. Bit (0) correlates
 *        to requestor 0, bit (1) correlates to requestor 1,
 *        etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2_range_prot_bits_2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 2 address range
 *        2. Set to 0 for asynchronous, set to 1 for 2:1 port:core
 *        pseudo-sync, set to 2 for 1:2 port:core pseudo-sync,
 *        or set to 3 for synchronous.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_311_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      axi2_range_id_check_bits_2                : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi2_range_prot_bits_2                    :  2;
#else    /* Little Endian */
     unsigned      axi2_range_prot_bits_2                    :  2;
     unsigned      reserved0                                 :  6;
     unsigned      axi2_range_id_check_bits_2                : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_311_t;

/*! @struct ncp_denali_DENALI_CTL_312_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_312_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2_start_addr_3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 2 address range 3. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_312_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  3;
     unsigned      axi2_start_addr_3                         : 21;
#else    /* Little Endian */
     unsigned      axi2_start_addr_3                         : 21;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_312_t;

/*! @struct ncp_denali_DENALI_CTL_313_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_313_t\n
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
 *     <td width="30%"> @param axi2_range_type_3 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Allowed transaction types for port 2 address range
 *        3. Set to 0 for no access, set to 1 for read-only,
 *        set to 2 for write-only, or set to 3 for read and
 *        write.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2_end_addr_3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 2 address range 3. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_313_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      axi2_range_type_3                         :  2;
     unsigned      reserved1                                 :  3;
     unsigned      axi2_end_addr_3                           : 21;
#else    /* Little Endian */
     unsigned      axi2_end_addr_3                           : 21;
     unsigned      reserved1                                 :  3;
     unsigned      axi2_range_type_3                         :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_313_t;

/*! @struct ncp_denali_DENALI_CTL_314_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_314_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2_range_id_check_bits_3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed IDs for port 2 address range 3. Bit (0) correlates
 *        to requestor 0, bit (1) correlates to requestor 1,
 *        etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2_range_prot_bits_3 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 2 address range
 *        3. Set to 0 for asynchronous, set to 1 for 2:1 port:core
 *        pseudo-sync, set to 2 for 1:2 port:core pseudo-sync,
 *        or set to 3 for synchronous.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_314_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      axi2_range_id_check_bits_3                : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi2_range_prot_bits_3                    :  2;
#else    /* Little Endian */
     unsigned      axi2_range_prot_bits_3                    :  2;
     unsigned      reserved0                                 :  6;
     unsigned      axi2_range_id_check_bits_3                : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_314_t;

/*! @struct ncp_denali_DENALI_CTL_315_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_315_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi3_start_addr_0 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 3 address range 0. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_315_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  3;
     unsigned      axi3_start_addr_0                         : 21;
#else    /* Little Endian */
     unsigned      axi3_start_addr_0                         : 21;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_315_t;

/*! @struct ncp_denali_DENALI_CTL_316_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_316_t\n
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
 *     <td width="30%"> @param axi3_range_type_0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Allowed transaction types for port 3 address range
 *        0. Set to 0 for no access, set to 1 for read-only,
 *        set to 2 for write-only, or set to 3 for read and
 *        write.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi3_end_addr_0 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 3 address range 0. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_316_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      axi3_range_type_0                         :  2;
     unsigned      reserved1                                 :  3;
     unsigned      axi3_end_addr_0                           : 21;
#else    /* Little Endian */
     unsigned      axi3_end_addr_0                           : 21;
     unsigned      reserved1                                 :  3;
     unsigned      axi3_range_type_0                         :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_316_t;

/*! @struct ncp_denali_DENALI_CTL_317_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_317_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi3_range_id_check_bits_0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed IDs for port 3 address range 0. Bit (0) correlates
 *        to requestor 0, bit (1) correlates to requestor 1,
 *        etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi3_range_prot_bits_0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 3 address range
 *        0. Set to 0 for asynchronous, set to 1 for 2:1 port:core
 *        pseudo-sync, set to 2 for 1:2 port:core pseudo-sync,
 *        or set to 3 for synchronous.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_317_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      axi3_range_id_check_bits_0                : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi3_range_prot_bits_0                    :  2;
#else    /* Little Endian */
     unsigned      axi3_range_prot_bits_0                    :  2;
     unsigned      reserved0                                 :  6;
     unsigned      axi3_range_id_check_bits_0                : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_317_t;

/*! @struct ncp_denali_DENALI_CTL_318_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_318_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi3_start_addr_1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 3 address range 1. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_318_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  3;
     unsigned      axi3_start_addr_1                         : 21;
#else    /* Little Endian */
     unsigned      axi3_start_addr_1                         : 21;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_318_t;

/*! @struct ncp_denali_DENALI_CTL_319_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_319_t\n
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
 *     <td width="30%"> @param axi3_range_type_1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Allowed transaction types for port 3 address range
 *        1. Set to 0 for no access, set to 1 for read-only,
 *        set to 2 for write-only, or set to 3 for read and
 *        write.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi3_end_addr_1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 3 address range 1. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_319_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      axi3_range_type_1                         :  2;
     unsigned      reserved1                                 :  3;
     unsigned      axi3_end_addr_1                           : 21;
#else    /* Little Endian */
     unsigned      axi3_end_addr_1                           : 21;
     unsigned      reserved1                                 :  3;
     unsigned      axi3_range_type_1                         :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_319_t;

/*! @struct ncp_denali_DENALI_CTL_320_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_320_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi3_range_id_check_bits_1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed IDs for port 3 address range 1. Bit (0) correlates
 *        to requestor 0, bit (1) correlates to requestor 1,
 *        etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi3_range_prot_bits_1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 3 address range
 *        1. Set to 0 for asynchronous, set to 1 for 2:1 port:core
 *        pseudo-sync, set to 2 for 1:2 port:core pseudo-sync,
 *        or set to 3 for synchronous.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_320_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      axi3_range_id_check_bits_1                : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi3_range_prot_bits_1                    :  2;
#else    /* Little Endian */
     unsigned      axi3_range_prot_bits_1                    :  2;
     unsigned      reserved0                                 :  6;
     unsigned      axi3_range_id_check_bits_1                : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_320_t;

/*! @struct ncp_denali_DENALI_CTL_321_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_321_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi3_start_addr_2 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 3 address range 2. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_321_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  3;
     unsigned      axi3_start_addr_2                         : 21;
#else    /* Little Endian */
     unsigned      axi3_start_addr_2                         : 21;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_321_t;

/*! @struct ncp_denali_DENALI_CTL_322_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_322_t\n
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
 *     <td width="30%"> @param axi3_range_type_2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Allowed transaction types for port 3 address range
 *        2. Set to 0 for no access, set to 1 for read-only,
 *        set to 2 for write-only, or set to 3 for read and
 *        write.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi3_end_addr_2 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 3 address range 2. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_322_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      axi3_range_type_2                         :  2;
     unsigned      reserved1                                 :  3;
     unsigned      axi3_end_addr_2                           : 21;
#else    /* Little Endian */
     unsigned      axi3_end_addr_2                           : 21;
     unsigned      reserved1                                 :  3;
     unsigned      axi3_range_type_2                         :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_322_t;

/*! @struct ncp_denali_DENALI_CTL_323_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_323_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi3_range_id_check_bits_2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed IDs for port 3 address range 2. Bit (0) correlates
 *        to requestor 0, bit (1) correlates to requestor 1,
 *        etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi3_range_prot_bits_2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 3 address range
 *        2. Set to 0 for asynchronous, set to 1 for 2:1 port:core
 *        pseudo-sync, set to 2 for 1:2 port:core pseudo-sync,
 *        or set to 3 for synchronous.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_323_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      axi3_range_id_check_bits_2                : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi3_range_prot_bits_2                    :  2;
#else    /* Little Endian */
     unsigned      axi3_range_prot_bits_2                    :  2;
     unsigned      reserved0                                 :  6;
     unsigned      axi3_range_id_check_bits_2                : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_323_t;

/*! @struct ncp_denali_DENALI_CTL_324_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_324_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi3_start_addr_3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 3 address range 3. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_324_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  3;
     unsigned      axi3_start_addr_3                         : 21;
#else    /* Little Endian */
     unsigned      axi3_start_addr_3                         : 21;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_324_t;

/*! @struct ncp_denali_DENALI_CTL_325_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_325_t\n
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
 *     <td width="30%"> @param axi3_range_type_3 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Allowed transaction types for port 3 address range
 *        3. Set to 0 for no access, set to 1 for read-only,
 *        set to 2 for write-only, or set to 3 for read and
 *        write.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi3_end_addr_3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 3 address range 3. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_325_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      axi3_range_type_3                         :  2;
     unsigned      reserved1                                 :  3;
     unsigned      axi3_end_addr_3                           : 21;
#else    /* Little Endian */
     unsigned      axi3_end_addr_3                           : 21;
     unsigned      reserved1                                 :  3;
     unsigned      axi3_range_type_3                         :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_325_t;

/*! @struct ncp_denali_DENALI_CTL_326_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_326_t\n
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
 *     <td width="30%"> @param update_error_status </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Identifies the source of any DFI MC-initiated or PHY-initiated
 *        update errors. Value of 1 indicates a timing violation
 *        of the associated timing parameter. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi3_range_id_check_bits_3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed IDs for port 3 address range 3. Bit (0) correlates
 *        to requestor 0, bit (1) correlates to requestor 1,
 *        etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi3_range_prot_bits_3 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 3 address range
 *        3. Set to 0 for asynchronous, set to 1 for 2:1 port:core
 *        pseudo-sync, set to 2 for 1:2 port:core pseudo-sync,
 *        or set to 3 for synchronous.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_326_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      update_error_status                       :  7;
     unsigned      axi3_range_id_check_bits_3                : 16;
     unsigned      reserved1                                 :  6;
     unsigned      axi3_range_prot_bits_3                    :  2;
#else    /* Little Endian */
     unsigned      axi3_range_prot_bits_3                    :  2;
     unsigned      reserved1                                 :  6;
     unsigned      axi3_range_id_check_bits_3                : 16;
     unsigned      update_error_status                       :  7;
     unsigned      reserved0                                 :  1;
#endif
} ncp_denali_DENALI_CTL_326_t;

/*! @struct ncp_denali_DENALI_CTL_327_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_327_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_ctrlupd_interval </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Holds the DFI tCTRLUPD_INTERVAL timing parameter.
 *        If programmed to a non-zero, a timing violation will
 *        cause an interrupt and bit (0) set in the UPDATE_ERROR_STATUS
 *        parameter.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_327_t
 *
 */

typedef struct
{
     unsigned  int      tdfi_ctrlupd_interval;
} ncp_denali_DENALI_CTL_327_t;

/*! @struct ncp_denali_DENALI_CTL_328_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_328_t\n
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
 *     <td width="30%"> @param tdfi_phy_wrdata </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Holds the DFI 2.1 tPHY_WRDATA timing parameter in
 *        DFI PHY clocks.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_dram_clk_enable </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Delay from DFI clock enable to memory clock enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_dram_clk_disable </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Delay from DFI clock disable to memory clock disable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_ctrl_delay </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Delay from DFI command to memory command. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_328_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  5;
     unsigned      tdfi_phy_wrdata                           :  3;
     unsigned      reserved1                                 :  4;
     unsigned      tdfi_dram_clk_enable                      :  4;
     unsigned      reserved2                                 :  4;
     unsigned      tdfi_dram_clk_disable                     :  4;
     unsigned      reserved3                                 :  4;
     unsigned      tdfi_ctrl_delay                           :  4;
#else    /* Little Endian */
     unsigned      tdfi_ctrl_delay                           :  4;
     unsigned      reserved3                                 :  4;
     unsigned      tdfi_dram_clk_disable                     :  4;
     unsigned      reserved2                                 :  4;
     unsigned      tdfi_dram_clk_enable                      :  4;
     unsigned      reserved1                                 :  4;
     unsigned      tdfi_phy_wrdata                           :  3;
     unsigned      reserved0                                 :  5;
#endif
} ncp_denali_DENALI_CTL_328_t;

/*! @struct ncp_denali_DENALI_CTL_329_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_329_t\n
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
 *     <td width="30%"> @param disable_rw_group_w_bnk_conflict </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Disables placement to read/write group when grouping
 *        creates a bank collision. Bit (0) controls placement
 *        next to bank conflict command and bit (1) controls
 *        placement 2 away from bank conflict command. Set each
 *        bit to 1 to disable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param w2r_split_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enable splitting of commands to the same chip select
 *        from a write to a read command as a rule for command
 *        queue placement.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cs_same_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enable chip select grouping when read/write grouping
 *        as a rule for command queue placement. This is only
 *        valid when the RW_SAME_EN parameter is set. Set to
 *        1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_329_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      disable_rw_group_w_bnk_conflict           :  2;
     unsigned      reserved1                                 :  7;
     unsigned      w2r_split_en                              :  1;
     unsigned      reserved2                                 :  7;
     unsigned      cs_same_en                                :  1;
     unsigned      obsolete0                                 :  8;
#else    /* Little Endian */
     unsigned      obsolete0                                 :  8;
     unsigned      cs_same_en                                :  1;
     unsigned      reserved2                                 :  7;
     unsigned      w2r_split_en                              :  1;
     unsigned      reserved1                                 :  7;
     unsigned      disable_rw_group_w_bnk_conflict           :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_329_t;

/*! @struct ncp_denali_DENALI_CTL_330_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_330_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lp_auto_mem_gate_en </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enable memory clock gating when entering a low power
 *        state via the auto low power counters. Bit (0) controls
 *        power-down, and bit (1) controls self-refresh. Set
 *        each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param in_order_accept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Forces the controller to accept commands in the order
 *        in which they are placed in the command queue.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param num_q_entries_act_disable </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of queue entries in which ACT requests will
 *        be disabled. Setting to X will disable ACT requests
 *        from the X entries lowest in the command queue.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_330_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      lp_auto_mem_gate_en                       :  2;
     unsigned      reserved1                                 :  7;
     unsigned      in_order_accept                           :  1;
     unsigned      reserved2                                 :  4;
     unsigned      num_q_entries_act_disable                 :  4;/* only 3 bits on 2500 */
#else    /* Little Endian */
     unsigned      num_q_entries_act_disable                 :  4;
     unsigned      reserved2                                 :  4;
     unsigned      in_order_accept                           :  1;
     unsigned      reserved1                                 :  7;
     unsigned      lp_auto_mem_gate_en                       :  2;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete3                                 :  8;
#endif
} ncp_denali_DENALI_CTL_330_t;

/*! @struct ncp_denali_DENALI_CTL_331_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_331_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lp_auto_pd_idle </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the idle time until the controller will place
 *        memory in active power-down.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_331_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      reserved0                                 :  4;
     unsigned      lp_auto_pd_idle                           : 12;
#else    /* Little Endian */
     unsigned      lp_auto_pd_idle                           : 12;
     unsigned      reserved0                                 :  4;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_331_t;

/*! @struct ncp_denali_DENALI_CTL_332_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_332_t\n
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
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of refreshes allowed between automatic ZQCS
 *        commands.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_332_t
 *
 */

typedef struct
{
     unsigned  int            refresh_per_zq;
} ncp_denali_DENALI_CTL_332_t;

/*! @struct ncp_denali_DENALI_CTL_333_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_333_t\n
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
 *     <td width="30%"> @param rw_same_page_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Enable page grouping when read/write grouping as a
 *        rule for command queue placement. This is only valid
 *        when the RW_SAME_EN parameter is set. Set to 1 to
 *        enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param col_diff </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Difference between number of column pins available
 *        and number being used.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param row_diff </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Difference between number of address pins available
 *        and number being used.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bank_diff </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Encoded number of banks on the DRAM(s). </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_333_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      rw_same_page_en                           :  1;
     unsigned      reserved1                                 :  5;
     unsigned      col_diff                                  :  3;
     unsigned      reserved2                                 :  5;
     unsigned      row_diff                                  :  3;
     unsigned      reserved3                                 :  6;
     unsigned      bank_diff                                 :  2;
#else    /* Little Endian */
     unsigned      bank_diff                                 :  2;
     unsigned      reserved3                                 :  6;
     unsigned      row_diff                                  :  3;
     unsigned      reserved2                                 :  5;
     unsigned      col_diff                                  :  3;
     unsigned      reserved1                                 :  5;
     unsigned      rw_same_page_en                           :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_333_t;

/*! @struct ncp_denali_DENALI_CTL_334_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_334_t\n
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
 *     <td width="30%"> @param todtl_2cmd </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> DRAM delay requirement from ODT de-assertion to next
 *        non-write, non-read command.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ctrlupd_req_per_aref_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enable an automatic controller-initiated update (dfi_ctrlupd_req)
 *        after every refresh. Set to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ctrlupd_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Assert the DFI controller-initiated update request
 *        signal dfi_ctrlupd_req. Set to 1 to trigger. WRITE-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_rd_interleave </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Disable read data interleaving for commands from the
 *        same port, regardless of the requestor ID.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_denali_DENALI_CTL_334_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      todtl_2cmd                                :  5;
     unsigned      reserved1                                 :  7;
     unsigned      ctrlupd_req_per_aref_en                   :  1;
     unsigned      reserved2                                 :  7;
     unsigned      ctrlupd_req                               :  1;
     unsigned      reserved3                                 :  7;
     unsigned      disable_rd_interleave                     :  1;
#else    /* Little Endian */
     unsigned      disable_rd_interleave                     :  1;
     unsigned      reserved3                                 :  7;
     unsigned      ctrlupd_req                               :  1;
     unsigned      reserved2                                 :  7;
     unsigned      ctrlupd_req_per_aref_en                   :  1;
     unsigned      reserved1                                 :  7;
     unsigned      todtl_2cmd                                :  5;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_334_t;

/*! @struct ncp_denali_DENALI_CTL_335_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_335_t\n
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
 *     <td width="30%"> @param optimal_rmodw_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Enables optimized RMODW logic in the controller. A
 *        value of 1 enables optimized RMODW operation. All
 *        RMODW operations are still supported in a non-optimal
 *        manner when the value is 0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param twr </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DRAM TWR value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trcd </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DRAM TRCD value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param additive_lat </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM additive latency value in cycles. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_335_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      optimal_rmodw_en                          :  1;
     unsigned      reserved1                                 :  2;
     unsigned      twr                                       :  6;
     unsigned      trcd                                      :  8;
     unsigned      reserved2                                 :  3;
     unsigned      additive_lat                              :  5;
#else    /* Little Endian */
     unsigned      additive_lat                              :  5;
     unsigned      reserved2                                 :  3;
     unsigned      trcd                                      :  8;
     unsigned      twr                                       :  6;
     unsigned      reserved1                                 :  2;
     unsigned      optimal_rmodw_en                          :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_335_t;

/*! @struct ncp_denali_DENALI_CTL_336_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_336_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved for future use. Must be cleared to 0x0. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_336_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved                                  :  7;
     unsigned      reserved0                                 :  1;
#else    /* Little Endian */
     unsigned      reserved0                                 :  1;
     unsigned      reserved                                  :  7;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_336_t;

/*! @struct ncp_denali_DENALI_CTL_337_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_337_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param zq_interval </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of long count sequences allowed between automatic
 *        ZQCS commands.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_337_t
 *
 */

typedef struct
{
     unsigned  int               zq_interval;
} ncp_denali_DENALI_CTL_337_t;

/*! @struct ncp_denali_DENALI_CTL_338_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_338_t\n
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
 *     <td width="30%"> @param int_ack </td>
 *     <td width="20%" align="center"> 25 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Clear mask of the INT_STATUS parameter. WRITE-ONLY </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_338_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      int_ack                                   : 25;
#else    /* Little Endian */
     unsigned      int_ack                                   : 25;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_338_t;

/*! @struct ncp_denali_DENALI_CTL_339_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_339_t\n
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
 *     <td width="30%"> @param todth_rd </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines the DRAM minimum ODT high time after an ODT
 *        assertion for a read command.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param todth_wr </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the DRAM minimum ODT high time after an ODT
 *        assertion for a write command.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param out_of_range_length </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Length of command that caused an out-of-range interrupt.
 *        READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_339_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      todth_rd                                  :  4;
     unsigned      reserved1                                 :  4;
     unsigned      todth_wr                                  :  4;
     unsigned      reserved2                                 :  3;
     unsigned      out_of_range_length                       : 13;
#else    /* Little Endian */
     unsigned      out_of_range_length                       : 13;
     unsigned      reserved2                                 :  3;
     unsigned      todth_wr                                  :  4;
     unsigned      reserved1                                 :  4;
     unsigned      todth_rd                                  :  4;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_339_t;

/*! @struct ncp_denali_DENALI_CTL_340_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_340_t\n
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
 *   <td width="30%"> Number of long count sequences counted between automatic
 *        write leveling commands.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odt_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enable support of DRAM ODT. When enabled, controller
 *        will assert and de-assert ODT output to DRAM as needed.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_340_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      wrlvl_interval                            : 16;
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  7;
     unsigned      odt_en                                    :  1;
#else    /* Little Endian */
     unsigned      odt_en                                    :  1;
     unsigned      reserved0                                 :  7;
     unsigned      obsolete1                                 :  8;
     unsigned      wrlvl_interval                            : 16;
#endif
} ncp_denali_DENALI_CTL_340_t;

/*! @struct ncp_denali_DENALI_CTL_341_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_341_t\n
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
 *     <td width="30%"> @param axi0_fixed_port_priority_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines the priority control for AXI port 0 as per-port
 *        or per-command. Set to 1 for per-port with priority
 *        defined through the AXI.18._R_PRIORITY and AXI.18._W_PRIORITY
 *        parameters. Clear to 0 for per-command.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_all_strobes_used_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enables use of the AWALLSTRB signal for AXI port 0.
 *        Set to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved for future use. Must be cleared to 0x0. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_341_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      axi0_fixed_port_priority_enable           :  1;
     unsigned      reserved1                                 :  7;
     unsigned      axi0_all_strobes_used_enable              :  1;
     unsigned      reserved2                                 :  7;
     unsigned      reserved                                  :  9;
#else    /* Little Endian */
     unsigned      reserved                                  :  9;
     unsigned      reserved2                                 :  7;
     unsigned      axi0_all_strobes_used_enable              :  1;
     unsigned      reserved1                                 :  7;
     unsigned      axi0_fixed_port_priority_enable           :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_341_t;

/*! @struct ncp_denali_DENALI_CTL_342_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_342_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_w_priority </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Priority of write commands from AXI port 0. 0 is the
 *        highest priority.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_r_priority </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Priority of read commands from AXI port 0. 0 is the
 *        highest priority.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_342_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 : 16;
     unsigned      reserved0                                 :  4;
     unsigned      axi0_w_priority                           :  4;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_r_priority                           :  4;
#else    /* Little Endian */
     unsigned      axi0_r_priority                           :  4;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_w_priority                           :  4;
     unsigned      reserved0                                 :  4;
     unsigned      obsolete2                                 : 16;
#endif
} ncp_denali_DENALI_CTL_342_t;

/*! @struct ncp_denali_DENALI_CTL_343_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_343_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_start_addr_4 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 4. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_343_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  2;
     unsigned      axi0_start_addr_4                         : 22;
#else    /* Little Endian */
     unsigned      axi0_start_addr_4                         : 22;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_343_t;

/*! @struct ncp_denali_DENALI_CTL_344_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_344_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_end_addr_4 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 4. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_344_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  2;
     unsigned      axi0_end_addr_4                           : 22;
#else    /* Little Endian */
     unsigned      axi0_end_addr_4                           : 22;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_344_t;

/*! @struct ncp_denali_DENALI_CTL_345_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_345_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_start_addr_5 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 5. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_345_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  2;
     unsigned      axi0_start_addr_5                         : 22;
#else    /* Little Endian */
     unsigned      axi0_start_addr_5                         : 22;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_345_t;

/*! @struct ncp_denali_DENALI_CTL_346_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_346_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_end_addr_5 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 5. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_346_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  2;
     unsigned      axi0_end_addr_5                           : 22;
#else    /* Little Endian */
     unsigned      axi0_end_addr_5                           : 22;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_346_t;

/*! @struct ncp_denali_DENALI_CTL_347_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_347_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_start_addr_6 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 6. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_347_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  2;
     unsigned      axi0_start_addr_6                         : 22;
#else    /* Little Endian */
     unsigned      axi0_start_addr_6                         : 22;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_347_t;

/*! @struct ncp_denali_DENALI_CTL_348_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_348_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_end_addr_6 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 6. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_348_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  2;
     unsigned      axi0_end_addr_6                           : 22;
#else    /* Little Endian */
     unsigned      axi0_end_addr_6                           : 22;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_348_t;

/*! @struct ncp_denali_DENALI_CTL_349_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_349_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_start_addr_7 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 7. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_349_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  2;
     unsigned      axi0_start_addr_7                         : 22;
#else    /* Little Endian */
     unsigned      axi0_start_addr_7                         : 22;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_349_t;

/*! @struct ncp_denali_DENALI_CTL_350_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_350_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_end_addr_7 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 7. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_350_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  2;
     unsigned      axi0_end_addr_7                           : 22;
#else    /* Little Endian */
     unsigned      axi0_end_addr_7                           : 22;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_350_t;

/*! @struct ncp_denali_DENALI_CTL_351_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_351_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_start_addr_8 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 8. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_351_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  2;
     unsigned      axi0_start_addr_8                         : 22;
#else    /* Little Endian */
     unsigned      axi0_start_addr_8                         : 22;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_351_t;

/*! @struct ncp_denali_DENALI_CTL_352_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_352_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_end_addr_8 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 8. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_352_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  2;
     unsigned      axi0_end_addr_8                           : 22;
#else    /* Little Endian */
     unsigned      axi0_end_addr_8                           : 22;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_352_t;

/*! @struct ncp_denali_DENALI_CTL_353_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_353_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_start_addr_9 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 9. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_353_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  2;
     unsigned      axi0_start_addr_9                         : 22;
#else    /* Little Endian */
     unsigned      axi0_start_addr_9                         : 22;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_353_t;

/*! @struct ncp_denali_DENALI_CTL_354_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_354_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_end_addr_9 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 9. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_354_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  2;
     unsigned      axi0_end_addr_9                           : 22;
#else    /* Little Endian */
     unsigned      axi0_end_addr_9                           : 22;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_354_t;

/*! @struct ncp_denali_DENALI_CTL_355_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_355_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_start_addr_10 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 10. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_355_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  2;
     unsigned      axi0_start_addr_10                        : 22;
#else    /* Little Endian */
     unsigned      axi0_start_addr_10                        : 22;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_355_t;

/*! @struct ncp_denali_DENALI_CTL_356_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_356_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_end_addr_10 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 10. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_356_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  2;
     unsigned      axi0_end_addr_10                          : 22;
#else    /* Little Endian */
     unsigned      axi0_end_addr_10                          : 22;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_356_t;

/*! @struct ncp_denali_DENALI_CTL_357_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_357_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_start_addr_11 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 11. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_357_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  2;
     unsigned      axi0_start_addr_11                        : 22;
#else    /* Little Endian */
     unsigned      axi0_start_addr_11                        : 22;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_357_t;

/*! @struct ncp_denali_DENALI_CTL_358_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_358_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_end_addr_11 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 11. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_358_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  2;
     unsigned      axi0_end_addr_11                          : 22;
#else    /* Little Endian */
     unsigned      axi0_end_addr_11                          : 22;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_358_t;

/*! @struct ncp_denali_DENALI_CTL_359_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_359_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_start_addr_12 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 12. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_359_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  2;
     unsigned      axi0_start_addr_12                        : 22;
#else    /* Little Endian */
     unsigned      axi0_start_addr_12                        : 22;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_359_t;

/*! @struct ncp_denali_DENALI_CTL_360_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_360_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_end_addr_12 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 12. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_360_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  2;
     unsigned      axi0_end_addr_12                          : 22;
#else    /* Little Endian */
     unsigned      axi0_end_addr_12                          : 22;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_360_t;

/*! @struct ncp_denali_DENALI_CTL_361_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_361_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_start_addr_13 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 13. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_361_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  2;
     unsigned      axi0_start_addr_13                        : 22;
#else    /* Little Endian */
     unsigned      axi0_start_addr_13                        : 22;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_361_t;

/*! @struct ncp_denali_DENALI_CTL_362_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_362_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_end_addr_13 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 13. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_362_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  2;
     unsigned      axi0_end_addr_13                          : 22;
#else    /* Little Endian */
     unsigned      axi0_end_addr_13                          : 22;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_362_t;

/*! @struct ncp_denali_DENALI_CTL_363_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_363_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_start_addr_14 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 14. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_363_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  2;
     unsigned      axi0_start_addr_14                        : 22;
#else    /* Little Endian */
     unsigned      axi0_start_addr_14                        : 22;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_363_t;

/*! @struct ncp_denali_DENALI_CTL_364_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_364_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_end_addr_14 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 14. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_364_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  2;
     unsigned      axi0_end_addr_14                          : 22;
#else    /* Little Endian */
     unsigned      axi0_end_addr_14                          : 22;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_364_t;

/*! @struct ncp_denali_DENALI_CTL_365_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_365_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_start_addr_15 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 15. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_365_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  2;
     unsigned      axi0_start_addr_15                        : 22;
#else    /* Little Endian */
     unsigned      axi0_start_addr_15                        : 22;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_365_t;

/*! @struct ncp_denali_DENALI_CTL_366_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_366_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_end_addr_15 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 15. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_366_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  2;
     unsigned      axi0_end_addr_15                          : 22;
#else    /* Little Endian */
     unsigned      axi0_end_addr_15                          : 22;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_366_t;

/*! @struct ncp_denali_DENALI_CTL_367_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_367_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Allowed write IDs for port 0 address range 0. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed read IDs for port 0 address range 0. Bit (0)
 *        correlates to requestor 0, bit (1) correlates to requestor
 *        1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_367_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      axi0_range_wid_check_bits_0               : 16;
     unsigned      axi0_range_rid_check_bits_0               : 16;
#else    /* Little Endian */
     unsigned      axi0_range_rid_check_bits_0               : 16;
     unsigned      axi0_range_wid_check_bits_0               : 16;
#endif
} ncp_denali_DENALI_CTL_367_t;

/*! @struct ncp_denali_DENALI_CTL_368_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_368_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Allowed read IDs for port 0 address range 1. Bit (0)
 *        correlates to requestor 0, bit (1) correlates to requestor
 *        1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_368_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      axi0_range_rid_check_bits_1               : 16;
     unsigned      obsolete0                                 : 16;
#else    /* Little Endian */
     unsigned      obsolete0                                 : 16;
     unsigned      axi0_range_rid_check_bits_1               : 16;
#endif
} ncp_denali_DENALI_CTL_368_t;

/*! @struct ncp_denali_DENALI_CTL_369_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_369_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed write IDs for port 0 address range 1. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_369_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      axi0_range_wid_check_bits_1               : 16;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_1               : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_369_t;

/*! @struct ncp_denali_DENALI_CTL_370_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_370_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Allowed write IDs for port 0 address range 2. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed read IDs for port 0 address range 2. Bit (0)
 *        correlates to requestor 0, bit (1) correlates to requestor
 *        1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_370_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      axi0_range_wid_check_bits_2               : 16;
     unsigned      axi0_range_rid_check_bits_2               : 16;
#else    /* Little Endian */
     unsigned      axi0_range_rid_check_bits_2               : 16;
     unsigned      axi0_range_wid_check_bits_2               : 16;
#endif
} ncp_denali_DENALI_CTL_370_t;

/*! @struct ncp_denali_DENALI_CTL_371_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_371_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Allowed read IDs for port 0 address range 3. Bit (0)
 *        correlates to requestor 0, bit (1) correlates to requestor
 *        1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_371_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      axi0_range_rid_check_bits_3               : 16;
     unsigned      obsolete0                                 : 16;
#else    /* Little Endian */
     unsigned      obsolete0                                 : 16;
     unsigned      axi0_range_rid_check_bits_3               : 16;
#endif
} ncp_denali_DENALI_CTL_371_t;

/*! @struct ncp_denali_DENALI_CTL_372_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_372_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed write IDs for port 0 address range 3. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_372_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      axi0_range_wid_check_bits_3               : 16;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_3               : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_372_t;

/*! @struct ncp_denali_DENALI_CTL_373_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_373_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed read IDs for port 0 address range 4. Bit (0)
 *        correlates to requestor 0, bit (1) correlates to requestor
 *        1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_prot_bits_4 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        4. Set to 0 for privileged and secure only, set to
 *        1 for secure (with or without privileged), set to
 *        2 for privileged (with or without secure), or set
 *        to 3 for full access.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_373_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      axi0_range_rid_check_bits_4               : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_prot_bits_4                    :  2;
#else    /* Little Endian */
     unsigned      axi0_range_prot_bits_4                    :  2;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_rid_check_bits_4               : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_373_t;

/*! @struct ncp_denali_DENALI_CTL_374_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_374_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed write IDs for port 0 address range 4. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_374_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      axi0_range_wid_check_bits_4               : 16;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_4               : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_374_t;

/*! @struct ncp_denali_DENALI_CTL_375_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_375_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed read IDs for port 0 address range 5. Bit (0)
 *        correlates to requestor 0, bit (1) correlates to requestor
 *        1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_prot_bits_5 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        5. Set to 0 for privileged and secure only, set to
 *        1 for secure (with or without privileged), set to
 *        2 for privileged (with or without secure), or set
 *        to 3 for full access.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_375_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      axi0_range_rid_check_bits_5               : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_prot_bits_5                    :  2;
#else    /* Little Endian */
     unsigned      axi0_range_prot_bits_5                    :  2;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_rid_check_bits_5               : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_375_t;

/*! @struct ncp_denali_DENALI_CTL_376_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_376_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed write IDs for port 0 address range 5. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_376_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      axi0_range_wid_check_bits_5               : 16;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_5               : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_376_t;

/*! @struct ncp_denali_DENALI_CTL_377_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_377_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed read IDs for port 0 address range 6. Bit (0)
 *        correlates to requestor 0, bit (1) correlates to requestor
 *        1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_prot_bits_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        6. Set to 0 for privileged and secure only, set to
 *        1 for secure (with or without privileged), set to
 *        2 for privileged (with or without secure), or set
 *        to 3 for full access.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_377_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      axi0_range_rid_check_bits_6               : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_prot_bits_6                    :  2;
#else    /* Little Endian */
     unsigned      axi0_range_prot_bits_6                    :  2;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_rid_check_bits_6               : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_377_t;

/*! @struct ncp_denali_DENALI_CTL_378_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_378_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed write IDs for port 0 address range 6. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_378_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      axi0_range_wid_check_bits_6               : 16;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_6               : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_378_t;

/*! @struct ncp_denali_DENALI_CTL_379_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_379_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed read IDs for port 0 address range 7. Bit (0)
 *        correlates to requestor 0, bit (1) correlates to requestor
 *        1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_prot_bits_7 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        7. Set to 0 for privileged and secure only, set to
 *        1 for secure (with or without privileged), set to
 *        2 for privileged (with or without secure), or set
 *        to 3 for full access.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_379_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      axi0_range_rid_check_bits_7               : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_prot_bits_7                    :  2;
#else    /* Little Endian */
     unsigned      axi0_range_prot_bits_7                    :  2;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_rid_check_bits_7               : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_379_t;

/*! @struct ncp_denali_DENALI_CTL_380_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_380_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed write IDs for port 0 address range 7. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_380_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      axi0_range_wid_check_bits_7               : 16;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_7               : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_380_t;

/*! @struct ncp_denali_DENALI_CTL_381_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_381_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed read IDs for port 0 address range 8. Bit (0)
 *        correlates to requestor 0, bit (1) correlates to requestor
 *        1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_prot_bits_8 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        8. Set to 0 for privileged and secure only, set to
 *        1 for secure (with or without privileged), set to
 *        2 for privileged (with or without secure), or set
 *        to 3 for full access.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_381_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      axi0_range_rid_check_bits_8               : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_prot_bits_8                    :  2;
#else    /* Little Endian */
     unsigned      axi0_range_prot_bits_8                    :  2;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_rid_check_bits_8               : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_381_t;

/*! @struct ncp_denali_DENALI_CTL_382_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_382_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed write IDs for port 0 address range 8. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_382_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      axi0_range_wid_check_bits_8               : 16;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_8               : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_382_t;

/*! @struct ncp_denali_DENALI_CTL_383_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_383_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_9 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed read IDs for port 0 address range 9. Bit (0)
 *        correlates to requestor 0, bit (1) correlates to requestor
 *        1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_prot_bits_9 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        9. Set to 0 for privileged and secure only, set to
 *        1 for secure (with or without privileged), set to
 *        2 for privileged (with or without secure), or set
 *        to 3 for full access.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_383_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      axi0_range_rid_check_bits_9               : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_prot_bits_9                    :  2;
#else    /* Little Endian */
     unsigned      axi0_range_prot_bits_9                    :  2;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_rid_check_bits_9               : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_383_t;

/*! @struct ncp_denali_DENALI_CTL_384_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_384_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_9 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed write IDs for port 0 address range 9. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_384_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      axi0_range_wid_check_bits_9               : 16;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_9               : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_384_t;

/*! @struct ncp_denali_DENALI_CTL_385_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_385_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_10 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed read IDs for port 0 address range 10. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_prot_bits_10 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        10. Set to 0 for privileged and secure only, set to
 *        1 for secure (with or without privileged), set to
 *        2 for privileged (with or without secure), or set
 *        to 3 for full access.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_385_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      axi0_range_rid_check_bits_10              : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_prot_bits_10                   :  2;
#else    /* Little Endian */
     unsigned      axi0_range_prot_bits_10                   :  2;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_rid_check_bits_10              : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_385_t;

/*! @struct ncp_denali_DENALI_CTL_386_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_386_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_10 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed write IDs for port 0 address range 10. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_386_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      axi0_range_wid_check_bits_10              : 16;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_10              : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_386_t;

/*! @struct ncp_denali_DENALI_CTL_387_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_387_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_11 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed read IDs for port 0 address range 11. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_prot_bits_11 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        11. Set to 0 for privileged and secure only, set to
 *        1 for secure (with or without privileged), set to
 *        2 for privileged (with or without secure), or set
 *        to 3 for full access.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_387_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      axi0_range_rid_check_bits_11              : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_prot_bits_11                   :  2;
#else    /* Little Endian */
     unsigned      axi0_range_prot_bits_11                   :  2;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_rid_check_bits_11              : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_387_t;

/*! @struct ncp_denali_DENALI_CTL_388_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_388_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_11 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed write IDs for port 0 address range 11. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_388_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      axi0_range_wid_check_bits_11              : 16;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_11              : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_388_t;

/*! @struct ncp_denali_DENALI_CTL_389_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_389_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed read IDs for port 0 address range 12. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_prot_bits_12 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        12. Set to 0 for privileged and secure only, set to
 *        1 for secure (with or without privileged), set to
 *        2 for privileged (with or without secure), or set
 *        to 3 for full access.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_389_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      axi0_range_rid_check_bits_12              : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_prot_bits_12                   :  2;
#else    /* Little Endian */
     unsigned      axi0_range_prot_bits_12                   :  2;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_rid_check_bits_12              : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_389_t;

/*! @struct ncp_denali_DENALI_CTL_390_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_390_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed write IDs for port 0 address range 12. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_390_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      axi0_range_wid_check_bits_12              : 16;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_12              : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_390_t;

/*! @struct ncp_denali_DENALI_CTL_391_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_391_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_13 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed read IDs for port 0 address range 13. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_prot_bits_13 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        13. Set to 0 for privileged and secure only, set to
 *        1 for secure (with or without privileged), set to
 *        2 for privileged (with or without secure), or set
 *        to 3 for full access.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_391_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      axi0_range_rid_check_bits_13              : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_prot_bits_13                   :  2;
#else    /* Little Endian */
     unsigned      axi0_range_prot_bits_13                   :  2;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_rid_check_bits_13              : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_391_t;

/*! @struct ncp_denali_DENALI_CTL_392_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_392_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_13 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed write IDs for port 0 address range 13. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_392_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      axi0_range_wid_check_bits_13              : 16;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_13              : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_392_t;

/*! @struct ncp_denali_DENALI_CTL_393_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_393_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_14 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed read IDs for port 0 address range 14. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_prot_bits_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        14. Set to 0 for privileged and secure only, set to
 *        1 for secure (with or without privileged), set to
 *        2 for privileged (with or without secure), or set
 *        to 3 for full access.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_393_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      axi0_range_rid_check_bits_14              : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_prot_bits_14                   :  2;
#else    /* Little Endian */
     unsigned      axi0_range_prot_bits_14                   :  2;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_rid_check_bits_14              : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_393_t;

/*! @struct ncp_denali_DENALI_CTL_394_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_394_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_14 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed write IDs for port 0 address range 14. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_394_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      axi0_range_wid_check_bits_14              : 16;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_14              : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_394_t;

/*! @struct ncp_denali_DENALI_CTL_395_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_395_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_15 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed read IDs for port 0 address range 15. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_prot_bits_15 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        15. Set to 0 for privileged and secure only, set to
 *        1 for secure (with or without privileged), set to
 *        2 for privileged (with or without secure), or set
 *        to 3 for full access.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_395_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      axi0_range_rid_check_bits_15              : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_prot_bits_15                   :  2;
#else    /* Little Endian */
     unsigned      axi0_range_prot_bits_15                   :  2;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_rid_check_bits_15              : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_395_t;

/*! @struct ncp_denali_DENALI_CTL_396_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_396_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_15 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed write IDs for port 0 address range 15. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_396_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      axi0_range_wid_check_bits_15              : 16;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_15              : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_396_t;

/*! @struct ncp_denali_DENALI_CTL_397_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_397_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_interval </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of long count sequences counted between automatic
 *        gate training commands.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_interval </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of long count sequences counted between automatic
 *        data eye training commands.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_397_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdlvl_gate_interval                       : 16;
     unsigned      rdlvl_interval                            : 16;
#else    /* Little Endian */
     unsigned      rdlvl_interval                            : 16;
     unsigned      rdlvl_gate_interval                       : 16;
#endif
} ncp_denali_DENALI_CTL_397_t;

/*! @struct ncp_denali_DENALI_CTL_398_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_398_t\n
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
 *     <td width="30%"> @param ecc_c_id </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Source ID associated with correctable ECC event. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_u_id </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Source ID associated with the uncorrectable ECC event.
 *        READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_398_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      ecc_c_id                                  : 12;
     unsigned      reserved1                                 :  4;
     unsigned      ecc_u_id                                  : 12;
#else    /* Little Endian */
     unsigned      ecc_u_id                                  : 12;
     unsigned      reserved1                                 :  4;
     unsigned      ecc_c_id                                  : 12;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_398_t;

/*! @struct ncp_denali_DENALI_CTL_399_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_399_t\n
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
 *     <td width="30%"> @param port_cmd_error_id </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Source ID of command that caused the PORT command
 *        error. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param out_of_range_source_id </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Source ID of command that caused an out-of-range interrupt.
 *        READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_399_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      port_cmd_error_id                         : 12;
     unsigned      reserved1                                 :  4;
     unsigned      out_of_range_source_id                    : 12;
#else    /* Little Endian */
     unsigned      out_of_range_source_id                    : 12;
     unsigned      reserved1                                 :  4;
     unsigned      port_cmd_error_id                         : 12;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_399_t;

/*! @struct ncp_denali_DENALI_CTL_400_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_400_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_0 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_address_range_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Determines if port 0 will use the axi.0._arregion
 *        / axi.0._awregion signals or the AXI.0._START_ADDR_Z
 *        / AXI.0._END_ADDR_Z parameters to define the region/range.
 *        Set to 1 for parameter control.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_400_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      reserved0                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_0     : 12;
     unsigned      reserved1                                 :  7;
     unsigned      axi0_address_range_enable                 :  1;
#else    /* Little Endian */
     unsigned      axi0_address_range_enable                 :  1;
     unsigned      reserved1                                 :  7;
     unsigned      axi0_range_rid_check_bits_id_lookup_0     : 12;
     unsigned      reserved0                                 :  4;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_400_t;

/*! @struct ncp_denali_DENALI_CTL_401_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_401_t\n
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
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_1.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_0 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_401_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_1     : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_wid_check_bits_id_lookup_0     : 12;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_id_lookup_0     : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_1     : 12;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_401_t;

/*! @struct ncp_denali_DENALI_CTL_402_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_402_t\n
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
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_2.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_1.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_402_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_2     : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_wid_check_bits_id_lookup_1     : 12;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_id_lookup_1     : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_2     : 12;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_402_t;

/*! @struct ncp_denali_DENALI_CTL_403_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_403_t\n
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
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_3 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_3.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_2.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_403_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_3     : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_wid_check_bits_id_lookup_2     : 12;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_id_lookup_2     : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_3     : 12;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_403_t;

/*! @struct ncp_denali_DENALI_CTL_404_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_404_t\n
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
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_4.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_3 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_3.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_404_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_4     : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_wid_check_bits_id_lookup_3     : 12;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_id_lookup_3     : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_4     : 12;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_404_t;

/*! @struct ncp_denali_DENALI_CTL_405_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_405_t\n
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
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_5 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_5.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_4.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_405_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_5     : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_wid_check_bits_id_lookup_4     : 12;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_id_lookup_4     : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_5     : 12;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_405_t;

/*! @struct ncp_denali_DENALI_CTL_406_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_406_t\n
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
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_6 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_6.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_5 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_5.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_406_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_6     : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_wid_check_bits_id_lookup_5     : 12;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_id_lookup_5     : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_6     : 12;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_406_t;

/*! @struct ncp_denali_DENALI_CTL_407_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_407_t\n
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
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_7 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_7.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_6 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_6.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_407_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_7     : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_wid_check_bits_id_lookup_6     : 12;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_id_lookup_6     : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_7     : 12;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_407_t;

/*! @struct ncp_denali_DENALI_CTL_408_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_408_t\n
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
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_8 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_8.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_7 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_7.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_408_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_8     : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_wid_check_bits_id_lookup_7     : 12;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_id_lookup_7     : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_8     : 12;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_408_t;

/*! @struct ncp_denali_DENALI_CTL_409_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_409_t\n
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
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_9 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_9.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_8 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_8.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_409_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_9     : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_wid_check_bits_id_lookup_8     : 12;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_id_lookup_8     : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_9     : 12;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_409_t;

/*! @struct ncp_denali_DENALI_CTL_410_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_410_t\n
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
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_10 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_10.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_9 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_9.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_410_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_10    : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_wid_check_bits_id_lookup_9     : 12;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_id_lookup_9     : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_10    : 12;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_410_t;

/*! @struct ncp_denali_DENALI_CTL_411_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_411_t\n
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
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_11 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_11.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_10 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_10.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_411_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_11    : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_wid_check_bits_id_lookup_10    : 12;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_id_lookup_10    : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_11    : 12;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_411_t;

/*! @struct ncp_denali_DENALI_CTL_412_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_412_t\n
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
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_12 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_12.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_11 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_11.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_412_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_12    : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_wid_check_bits_id_lookup_11    : 12;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_id_lookup_11    : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_12    : 12;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_412_t;

/*! @struct ncp_denali_DENALI_CTL_413_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_413_t\n
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
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_13 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_13.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_12 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_12.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_413_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_13    : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_wid_check_bits_id_lookup_12    : 12;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_id_lookup_12    : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_13    : 12;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_413_t;

/*! @struct ncp_denali_DENALI_CTL_414_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_414_t\n
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
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_14 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_14.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_13 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_13.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_414_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_14    : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_wid_check_bits_id_lookup_13    : 12;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_id_lookup_13    : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_14    : 12;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_414_t;

/*! @struct ncp_denali_DENALI_CTL_415_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_415_t\n
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
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_15 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_15.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_14 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_14.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_415_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_15    : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_wid_check_bits_id_lookup_14    : 12;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_id_lookup_14    : 12;
     unsigned      reserved1                                 :  4;
     unsigned      axi0_range_rid_check_bits_id_lookup_15    : 12;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_415_t;

/*! @struct ncp_denali_DENALI_CTL_416_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_416_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param read_data_fifo_ptr_width </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reports the width of the controller core read data
 *        queue pointer. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param read_data_fifo_depth </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reports the depth of the controller core read data
 *        queue. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_15 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_15.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_416_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      read_data_fifo_ptr_width                  :  8;
     unsigned      read_data_fifo_depth                      :  8;
     unsigned      reserved0                                 :  4;
     unsigned      axi0_range_wid_check_bits_id_lookup_15    : 12;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_id_lookup_15    : 12;
     unsigned      reserved0                                 :  4;
     unsigned      read_data_fifo_depth                      :  8;
     unsigned      read_data_fifo_ptr_width                  :  8;
#endif
} ncp_denali_DENALI_CTL_416_t;

/*! @struct ncp_denali_DENALI_CTL_417_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_417_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param memcd_rmodw_fifo_ptr_width </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reports the width of the controller core read/modify/write
 *        FIFO pointer. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param memcd_rmodw_fifo_depth </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reports the depth of the controller core read/modify/write
 *        FIFO. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param write_data_fifo_ptr_width </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reports the width of the controller core write data
 *        latency queue pointer. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param write_data_fifo_depth </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reports the depth of the controller core write data
 *        latency queue. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_417_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      memcd_rmodw_fifo_ptr_width                :  8;
     unsigned      memcd_rmodw_fifo_depth                    :  8;
     unsigned      write_data_fifo_ptr_width                 :  8;
     unsigned      write_data_fifo_depth                     :  8;
#else    /* Little Endian */
     unsigned      write_data_fifo_depth                     :  8;
     unsigned      write_data_fifo_ptr_width                 :  8;
     unsigned      memcd_rmodw_fifo_depth                    :  8;
     unsigned      memcd_rmodw_fifo_ptr_width                :  8;
#endif
} ncp_denali_DENALI_CTL_417_t;

/*! @struct ncp_denali_DENALI_CTL_418_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_418_t\n
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
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_rdfifo_log2_depth </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reports the depth of the AXI port 0 Read Data FIFO.
 *        Value is the log2 value of the depth. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_cmdfifo_log2_depth </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reports the depth of the AXI port 0 Command FIFO.
 *        Value is the log2 value of the depth. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param async_cdc_stages </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reports the number of synchronizer delays specified
 *        for the asynchronous boundary crossings. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_418_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      axi0_rdfifo_log2_depth                    :  8;
     unsigned      axi0_cmdfifo_log2_depth                   :  8;
     unsigned      async_cdc_stages                          :  8;
#else    /* Little Endian */
     unsigned      async_cdc_stages                          :  8;
     unsigned      axi0_cmdfifo_log2_depth                   :  8;
     unsigned      axi0_rdfifo_log2_depth                    :  8;
     unsigned      obsolete3                                 :  8;
#endif
} ncp_denali_DENALI_CTL_418_t;

/*! @struct ncp_denali_DENALI_CTL_419_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_419_t\n
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
 *     <td width="30%"> @param ca_parity_error </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Contains one hot indication of registered DIMM parity
 *        errors. Bit (0) correlates to DIMM0, bit (1) correlates
 *        to DIMM1, etc. Value of 1 indicates an error on that
 *        DIMM. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved for future use. Must be cleared to 0x0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_wr_array_log2_depth </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reports the depth of the AXI port 0 Write Data Array.
 *        Value is the log2 value of the depth. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_wrcmd_proc_fifo_log2_depth </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reports the depth of the AXI port 0 Write Command
 *        Processing FIFO. Value is the log2 value of the depth.
 *        READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_419_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      ca_parity_error                           :  2;
     unsigned      reserved1                                 :  7;
     unsigned      reserved2                                 :  1;
     unsigned      axi0_wr_array_log2_depth                  :  8;
     unsigned      axi0_wrcmd_proc_fifo_log2_depth           :  8;
#else    /* Little Endian */
     unsigned      axi0_wrcmd_proc_fifo_log2_depth           :  8;
     unsigned      axi0_wr_array_log2_depth                  :  8;
     unsigned      reserved2                                 :  1;
     unsigned      reserved1                                 :  7;
     unsigned      ca_parity_error                           :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_419_t;

/*! @struct ncp_denali_DENALI_CTL_420_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_420_t\n
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
 *     <td width="30%"> @param long_count_mask </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reduces the length of the long counter from 1024 cycles.
 *        The only supported values are 0x00 (1024 cycles),
 *        0x10 (512 clocks), 0x18 (256 clocks), 0x1C (128 clocks),
 *        0x1E (64 clocks) and 0x1F (32 clocks).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rd_to_odth </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the delay from a read command to ODT assertion. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wr_to_odth </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the delay from a write command to ODT assertion. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wr_order_req </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Determines if the controller can re-order write commands
 *        from the same source ID and/or the same port. Bit
 *        (0) controls source ID usage and bit (1) controls
 *        port ID usage. Set each bit to 1 to enable usage in
 *        placement logic.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_420_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      long_count_mask                           :  5;
     unsigned      reserved1                                 :  2;
     unsigned      rd_to_odth                                :  6;
     unsigned      reserved2                                 :  2;
     unsigned      wr_to_odth                                :  6;
     unsigned      reserved3                                 :  6;
     unsigned      wr_order_req                              :  2;
#else    /* Little Endian */
     unsigned      wr_order_req                              :  2;
     unsigned      reserved3                                 :  6;
     unsigned      wr_to_odth                                :  6;
     unsigned      reserved2                                 :  2;
     unsigned      rd_to_odth                                :  6;
     unsigned      reserved1                                 :  2;
     unsigned      long_count_mask                           :  5;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_420_t;

/*! @struct ncp_denali_DENALI_CTL_421_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_421_t\n
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
 *     <td width="30%"> @param ecc_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> ECC error checking and correcting control. Set to
 *        0 to disable ECC or set to 1 for ECC reporting and
 *        correcting.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_denali_DENALI_CTL_421_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 31;
     unsigned      ecc_en                                    :  1;
#else    /* Little Endian */
     unsigned      ecc_en                                    :  1;
     unsigned      reserved0                                 : 31;
#endif
} ncp_denali_DENALI_CTL_421_t;

#ifdef __cplusplus
}
#endif

#endif /* _NCP_DENALI_REGS_2500_H_ */
