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

#ifndef _NCP_PHY_REGS_H_
#define _NCP_PHY_REGS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*! @struct ncp_phy_CFG_SYSMEM_PRF_LAT_CNTLx_r_t
 *  @brief CFG_SYSMEM_PRF_LAT_CNTLx
 *  @details Configuration control for performance latency measurement
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PRF_LAT_CNTLx_r_t\n
 *   </td>
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
 *     <td width="30%"> @param prf_lat_ind </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Performance independent function </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param prf_lenval </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Request length </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param prf_len </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Measure for request length </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param prf_burst </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Measure for burst type </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param prf_pri </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Measure high or low priority requests </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param prf_last </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Measure to last or first cycle of response </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param prf_w_r </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Measure write or read latency </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param prf_portsel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> AXI port selection </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param prf_lat_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Performance latency reset measurements </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param prf_lat_ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Performance latency measurement enable </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 15;
     unsigned      prf_lat_ind                               :  1;
     unsigned      prf_lenval                                :  4;
     unsigned      prf_len                                   :  2;
     unsigned      prf_burst                                 :  2;
     unsigned      prf_pri                                   :  2;
     unsigned      prf_last                                  :  1;
     unsigned      prf_w_r                                   :  1;
     unsigned      prf_portsel                               :  2;
     unsigned      prf_lat_rst                               :  1;
     unsigned      prf_lat_ena                               :  1;
#else    /* Little Endian */
     unsigned      prf_lat_ena                               :  1;
     unsigned      prf_lat_rst                               :  1;
     unsigned      prf_portsel                               :  2;
     unsigned      prf_w_r                                   :  1;
     unsigned      prf_last                                  :  1;
     unsigned      prf_pri                                   :  2;
     unsigned      prf_burst                                 :  2;
     unsigned      prf_len                                   :  2;
     unsigned      prf_lenval                                :  4;
     unsigned      prf_lat_ind                               :  1;
     unsigned      reserved0                                 : 15;
#endif
} ncp_phy_CFG_SYSMEM_PRF_LAT_CNTLx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PRF_MINMAX_LATx_r_t
 *  @brief CFG_SYSMEM_PRF_MINMAX_LATx
 *  @details Min and Max latency measurement
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PRF_MINMAX_LATx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param prf_maxlat </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Maximum latency measurement </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param prf_minlat </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Minimum latency measurement </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      prf_maxlat                                : 16;
     unsigned      prf_minlat                                : 16;
#else    /* Little Endian */
     unsigned      prf_minlat                                : 16;
     unsigned      prf_maxlat                                : 16;
#endif
} ncp_phy_CFG_SYSMEM_PRF_MINMAX_LATx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PRF_REQ_CNTx_r_t
 *  @brief CFG_SYSMEM_PRF_REQ_CNTx
 *  @details The number of requests whose latency is accumulated
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PRF_REQ_CNTx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param prf_reqcnt </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Count of accumulated requests </td>
 * </tr>
 * </table>
 */
typedef struct
{
     unsigned  int                prf_reqcnt;
} ncp_phy_CFG_SYSMEM_PRF_REQ_CNTx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PRF_LATACCx_r_t
 *  @brief CFG_SYSMEM_PRF_LATACCx
 *  @details The lower half of the accumulated latency measurement
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PRF_LATACCx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param prf_latacc </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower half of accumulated request latency </td>
 * </tr>
 * </table>
 */
typedef struct
{
     unsigned  int                prf_latacc;
} ncp_phy_CFG_SYSMEM_PRF_LATACCx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PRF_TIMCNTx_r_t
 *  @brief CFG_SYSMEM_PRF_TIMCNTx
 *  @details The upper half of the accumulated latency measurement
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PRF_TIMCNTx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param prf_timcnt </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper half of accumulated request latency </td>
 * </tr>
 * </table>
 */
typedef struct
{
     unsigned  int                prf_timcnt;
} ncp_phy_CFG_SYSMEM_PRF_TIMCNTx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_ADRx_BITx_DLY_r_t
 *  @brief CFG_SYSMEM_PHY_ADRx_BITx_DLY
 *  @details Delay value for ADR_OUT BITx of instance ADRx
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_ADRx_BITx_DLY_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param adr_qtr_delay </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Address out quarter cycle delay </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param adr_fine_delay </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address out fine delay value, if PVT comp type = 0
 *        then bits[6:2] add increments of 1/128 mem clk auto
 *        scaled to PVT and bits[1:0] unused. If PVT comp type
 *        = 1 then bits [6:0] represent raw uncompensated delay.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 23;
     unsigned      adr_qtr_delay                             :  2;
     unsigned      adr_fine_delay                            :  7;
#else    /* Little Endian */
     unsigned      adr_fine_delay                            :  7;
     unsigned      adr_qtr_delay                             :  2;
     unsigned      reserved0                                 : 23;
#endif
} ncp_phy_CFG_SYSMEM_PHY_ADRx_BITx_DLY_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_ADRx_CONFIG_r_t
 *  @brief CFG_SYSMEM_PHY_ADRx_CONFIG
 *  @details Configuration control for instance ADRx
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_ADRx_CONFIG_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 29 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt_type_memclk </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> PVT compensation type for memclks. (same encoding
 *        per bit) bit2:memclk2, bit1:memclk1 NOTE: In raw uncompensated
 *        mode, PVT updates are prevented on the memclk and
 *        the delay lines do not glitch. Use this mode to prevent
 *        glitching the memory clock when delay is not required
 *        on memclk.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt_type </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PVT compensation type </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 29;
     unsigned      pvt_type_memclk                           :  2;
     unsigned      pvt_type                                  :  1;
#else    /* Little Endian */
     unsigned      pvt_type                                  :  1;
     unsigned      pvt_type_memclk                           :  2;
     unsigned      reserved0                                 : 29;
#endif
} ncp_phy_CFG_SYSMEM_PHY_ADRx_CONFIG_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_ADRxx_DLYCPCFRAC_r_t
 *  @brief CFG_SYSMEM_PHY_ADRxx_DLYCPCFRAC
 *  @details Provides read access to CPC fraction values in instance ADRxx
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_ADRxx_DLYCPCFRAC_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 25 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt_type </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPC fraction value for ADRxx hard macro. </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 25;
     unsigned      pvt_type                                  :  7;
#else    /* Little Endian */
     unsigned      pvt_type                                  :  7;
     unsigned      reserved0                                 : 25;
#endif
} ncp_phy_CFG_SYSMEM_PHY_ADRxx_DLYCPCFRAC_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DQxWRTDLY_BLxCSx_r_t
 *  @brief CFG_SYSMEM_PHY_DQxWRTDLY_BLxCSx
 *  @details Write leveling delay value for BITx of byte lane BLx for rank CSx
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DQxWRTDLY_BLxCSx_r_t\n
 *   </td>
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
 *     <td width="30%"> @param dat_qtr_delay </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Range: 0.00 to 2.75 clks. Data out quarter cycle delay </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dat_fine_delay </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data out fine delay value, if PVT comp type = 0 then
 *        bits[6:2] add increments of 1/128 mem clk auto scaled
 *        to PVT and bits[1:0] unused. If PVT comp type = 1
 *        then bits [6:0] represent raw uncompensated delay.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 21;
     unsigned      dat_qtr_delay                             :  4;
     unsigned      dat_fine_delay                            :  7;
#else    /* Little Endian */
     unsigned      dat_fine_delay                            :  7;
     unsigned      dat_qtr_delay                             :  4;
     unsigned      reserved0                                 : 21;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DQxWRTDLY_BLxCSx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_WRTLVLDBG_BLx_r_t
 *  @brief CFG_SYSMEM_PHY_WRTLVLDBG_BLx
 *  @details Write leveling SM Debug for byte lane BLx
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_WRTLVLDBG_BLx_r_t\n
 *   </td>
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
 *     <td width="30%"> @param wrt_lvl_dbg </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Debug field for write leveling state machine </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      wrt_lvl_dbg                               : 16;
#else    /* Little Endian */
     unsigned      wrt_lvl_dbg                               : 16;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_CFG_SYSMEM_PHY_WRTLVLDBG_BLx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_WRTLVLCTL_r_t
 *  @brief CFG_SYSMEM_PHY_WRTLVLCTL
 *  @details Write leveling control
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_WRTLVLCTL_r_t\n
 *   </td>
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
 *     <td width="30%"> @param en_quick_dlyshortgt_shutoff_chknsw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Chicken switch - 0 = Normal shutoff, 1 = quick shutoff. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param high_sw_rate_dqs_chknsw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Chicken switch - 0 = a single dqs pulse is used to
 *        sample the SDRAM clk via DQ during fine wrt leveling,
 *        1 = a continously switching pulse train is generated
 *        during fine wrt leveling and a random edge is used
 *        to sample the SDRAM clk based on the wait_cnt_chknsw
 *        field. The continously switching DQS is meant to approximate
 *        the behavior of DQS during functional writes.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wait_cnt_chknsw </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Chicken switch - provides a programmable wait time
 *        to account for tWLO+tWLOE to sample DQs during write
 *        leveling. The 4 bit value represents the most significant
 *        bits of a 6 bit counter that is kicked off when DQS
 *        is generated internally e.g. 0100(00) will count 16
 *        1x clocks.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrtlvlrsvd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param en_rdptr_clks </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> RESERVED, MUST be written to a 1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enh_dig_fltr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> 0 = normal digital filter, 1 = enhanced digital filter.
 *        In normal digital filter mode, once a rising edge
 *        is detected the write leveling sm will take 16 consecutive
 *        samples at this point before declaring a successful
 *        rising edge found. In enhanced digital filter mode,
 *        once the edge is detected the sm takes 14 consecutive
 *        samples, increment by 1/4 cycle for a single sample,
 *        decrement back for 1/4 cycle for the last sample before
 *        a successful edge detect is declared. It is used to
 *        guard against aliasing scenarios.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param max_dly_dlta </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Max delay delta limit 0, if during write leveling
 *        the delays are incremented past (INITIAL_STARTING_POINT
 *        + max_dly_dlta) then an error is flagged (rising_edge_not_found???).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param num_samp </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Number of samples </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt_type </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PVT compensation type </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      en_quick_dlyshortgt_shutoff_chknsw        :  1;
     unsigned      high_sw_rate_dqs_chknsw                   :  1;
     unsigned      wait_cnt_chknsw                           :  4;
     unsigned      wrtlvlrsvd                                :  1;
     unsigned      en_rdptr_clks                             :  1;
     unsigned      enh_dig_fltr                              :  1;
     unsigned      max_dly_dlta                              :  4;
     unsigned      num_samp                                  :  2;
     unsigned      pvt_type                                  :  1;
#else    /* Little Endian */
     unsigned      pvt_type                                  :  1;
     unsigned      num_samp                                  :  2;
     unsigned      max_dly_dlta                              :  4;
     unsigned      enh_dig_fltr                              :  1;
     unsigned      en_rdptr_clks                             :  1;
     unsigned      wrtlvlrsvd                                :  1;
     unsigned      wait_cnt_chknsw                           :  4;
     unsigned      high_sw_rate_dqs_chknsw                   :  1;
     unsigned      en_quick_dlyshortgt_shutoff_chknsw        :  1;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_CFG_SYSMEM_PHY_WRTLVLCTL_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_WRTLVLCTL_CPCFRAC_r_t
 *  @brief CFG_SYSMEM_PHY_WRTLVLCTL_CPCFRAC
 *  @details Write leveling control CPC fraction value
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_WRTLVLCTL_CPCFRAC_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 25 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpc_frac </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPC fraction value </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 25;
     unsigned      cpc_frac                                  :  7;
#else    /* Little Endian */
     unsigned      cpc_frac                                  :  7;
     unsigned      reserved0                                 : 25;
#endif
} ncp_phy_CFG_SYSMEM_PHY_WRTLVLCTL_CPCFRAC_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DQSxRDDLY_BLxCSx_r_t
 *  @brief CFG_SYSMEM_PHY_DQSxRDDLY_BLxCSx
 *  @details The read delay setting for DQSx of byte lane BLx for rank CSx
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DQSxRDDLY_BLxCSx_r_t\n
 *   </td>
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
 *     <td width="30%"> @param qtr_delay </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DQS delay value for functional operation using the
 *        read eye measurements or override value for DQS delay
 *        when written.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      qtr_delay                                 :  8;
#else    /* Little Endian */
     unsigned      qtr_delay                                 :  8;
     unsigned      reserved0                                 : 24;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DQSxRDDLY_BLxCSx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DQSxF2PDLY_BLxCSx_r_t
 *  @brief CFG_SYSMEM_PHY_DQSxF2PDLY_BLxCSx
 *  @details The fail to passing point DQS delay value for DQSx of byte lane BLx for rank CSx
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DQSxF2PDLY_BLxCSx_r_t\n
 *   </td>
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
 *     <td width="30%"> @param fp_delay </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DQS delay value that represents the left edge of the
 *        read data eye.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      fp_delay                                  :  8;
#else    /* Little Endian */
     unsigned      fp_delay                                  :  8;
     unsigned      reserved0                                 : 24;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DQSxF2PDLY_BLxCSx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DQSxP2FDLY_BLxCSx_r_t
 *  @brief CFG_SYSMEM_PHY_DQSxP2FDLY_BLxCSx
 *  @details The pass to failing point DQS delay value for DQSx of byte lane BLx for rank CSx
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DQSxP2FDLY_BLxCSx_r_t\n
 *   </td>
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
 *     <td width="30%"> @param pf_delay </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DQS delay value that represents the right edge of
 *        the read data eye.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      pf_delay                                  :  8;
#else    /* Little Endian */
     unsigned      pf_delay                                  :  8;
     unsigned      reserved0                                 : 24;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DQSxP2FDLY_BLxCSx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_RDDLYMODE_BLx_r_t
 *  @brief CFG_SYSMEM_PHY_RDDLYMODE_BLx
 *  @details Read leveling controls
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_RDDLYMODE_BLx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 17 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param inh_dqs_dly_update </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Chicken switch - not for general use. When this bit
 *        is set, the DQS delay value determined by the INIT
 *        Readeye Centering SM is not updated in the RDDLY_DQS_DELAY_REG.
 *        The INIT Readeye Centering SM does update all other
 *        registers.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqs_center_burst_win </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Beats of data used for INIT and periodic read eye
 *        centering. 00 = 1st, 2nd, 3rd, and 4th beats of data
 *        (legacy), 01 = 3rd, 4th, 5th and 6th beats of data,
 *        10 = 5th, 6th, 7th, and 8th beats of data, 11 = compare
 *        all 8 beats of data. Note, this field is only used
 *        for read eye centering (both init and periodic). This
 *        field does not affect the deskew function (neither
 *        init or periodic).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rt_dly_window </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> The number of delays from the initial P2F or F2P point
 *        to check when doing runtime DQS calibration. During
 *        run time deskew, this is added to the DQS delay value
 *        where the latest bit was located. Note, these 3 bits
 *        are the msbs of a 4 bit field. The least significant
 *        bit is hardcoded to a 1.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rd_eye_cpc_div </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> 0 = divide CPC_FRACTION by 2 for read eye centering,
 *        1 = divide CPC_FRACTION by 4 for read eye centering.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param md_cpc_frac_lmt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> When enabled, the maximum of the DQS and DQ delay
 *        is limited to 0xFE (max value of the delay line) or
 *        2*CPC_FRACTION + CPC_FRAC_MARG
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpc_frac_marg </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Additional margin to the CPC_FRACTION delay limit.
 *        Note, these 3 bits are the msbs of a 4 bit field.
 *        The least significant bit is hardcoded to a 1.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param deskew_cpc_div </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> 0 = divide CPC_FRACTION by 2 for deskew, 1 = divide
 *        CPC_FRACTION by 4 for deskew.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param conseq_pass_mode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> 0 = use the programmed value in ??? reg [4:0], 1 =
 *        use the lesser of the programmed value in CFG_SYSMEM_PHY_RDDLYMODE1_BLx
 *        reg [4:0] or the selected divided down CPC fraction
 *        in CFG_SYSMEM_PHY_RDDLYMODE_BLx reg
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param md_dis </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Disables all calibrations for the byte lane. Delay
 *        values will not be updated.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt_ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PVT compensation enable 0 = override values are raw
 *        delay, 1 = override values are PVT compensated, MUST
 *        WRITE to 0!
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 17;
     unsigned      inh_dqs_dly_update                        :  1;
     unsigned      dqs_center_burst_win                      :  2;
     unsigned      rt_dly_window                             :  3;
     unsigned      rd_eye_cpc_div                            :  1;
     unsigned      md_cpc_frac_lmt                           :  1;
     unsigned      cpc_frac_marg                             :  3;
     unsigned      deskew_cpc_div                            :  1;
     unsigned      conseq_pass_mode                          :  1;
     unsigned      md_dis                                    :  1;
     unsigned      pvt_ena                                   :  1;
#else    /* Little Endian */
     unsigned      pvt_ena                                   :  1;
     unsigned      md_dis                                    :  1;
     unsigned      conseq_pass_mode                          :  1;
     unsigned      deskew_cpc_div                            :  1;
     unsigned      cpc_frac_marg                             :  3;
     unsigned      md_cpc_frac_lmt                           :  1;
     unsigned      rd_eye_cpc_div                            :  1;
     unsigned      rt_dly_window                             :  3;
     unsigned      dqs_center_burst_win                      :  2;
     unsigned      inh_dqs_dly_update                        :  1;
     unsigned      reserved0                                 : 17;
#endif
} ncp_phy_CFG_SYSMEM_PHY_RDDLYMODE_BLx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_RDDLYMODE1_BLx_r_t
 *  @brief CFG_SYSMEM_PHY_RDDLYMODE1_BLx
 *  @details Additional read leveling controls
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_RDDLYMODE1_BLx_r_t\n
 *   </td>
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
 *     <td width="30%"> @param state_101_chknsw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Chicken switch: 0 = allow RDDLY state machine to enter
 *        state 101, 1 = prevent RDDLY state machine from entering
 *        state 101.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param single_bit_mpr </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> One bit per rank to indicate a single bit MPR DDR3
 *        module. 0 = MPR pattern provided on all DQ pins, 1
 *        = single bit MPR on least significant DQ. Bit 14 corresponds
 *        to Rank 7, ... Bit 7 corresponds to Rank 0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param consec_pass </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The number of consecutive passes required when determining
 *        the fail to pass (F2P) point in DQS centering. Also
 *        used in deskew for the number of consecutive 1s that
 *        need to be sampled before looking for the falling
 *        edge of DQ. Note, for slow PVT corners this value
 *        should be reduced or use the conseq_pass_mode=1 setting
 *        in CFG_SYSMEM_PHY_RDDLYMODE_BLx reg.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      state_101_chknsw                          :  1;
     unsigned      single_bit_mpr                            :  8;
     unsigned      reserved1                                 :  2;
     unsigned      consec_pass                               :  5;
#else    /* Little Endian */
     unsigned      consec_pass                               :  5;
     unsigned      reserved1                                 :  2;
     unsigned      single_bit_mpr                            :  8;
     unsigned      state_101_chknsw                          :  1;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_CFG_SYSMEM_PHY_RDDLYMODE1_BLx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_CMPDLYx_x_BLx_r_t
 *  @brief CFG_SYSMEM_PHY_CMPDLYx_x_BLx
 *  @details Compare value for even/odd cycle x on byte lane BLx
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_CMPDLYx_x_BLx_r_t\n
 *   </td>
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
 *     <td width="30%"> @param cmp_value </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data compare value for read eye algorithm for read
 *        cycle x.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cmp_value                                 :  8;
#else    /* Little Endian */
     unsigned      cmp_value                                 :  8;
     unsigned      reserved0                                 : 24;
#endif
} ncp_phy_CFG_SYSMEM_PHY_CMPDLYx_x_BLx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DQxRDDLY_BLxCSx_r_t
 *  @brief CFG_SYSMEM_PHY_DQxRDDLY_BLxCSx
 *  @details The DQ delay setting for bit DQx on byte lane BLx for rank CSx.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DQxRDDLY_BLxCSx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 25 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq_delay </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The DQ delay setting for given bit of byte lane and
 *        rank. This value is the result of the deskew algorithm,
 *        or if written, an override value.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 25;
     unsigned      dq_delay                                  :  7;
#else    /* Little Endian */
     unsigned      dq_delay                                  :  7;
     unsigned      reserved0                                 : 25;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DQxRDDLY_BLxCSx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_LATDQSDLY_BLxCSx_r_t
 *  @brief CFG_SYSMEM_PHY_LATDQSDLY_BLxCSx
 *  @details Initial DQS value for periodic deskew.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_LATDQSDLY_BLxCSx_r_t\n
 *   </td>
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
 *     <td width="30%"> @param dq_dqs_delay </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DQS delay value from previous run of deskew algorithm.
 *        This is not the functional DQS delay. It is an indicator
 *        of the position of the latest DQ and the point at
 *        which the next periodic deskew will start.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      dq_dqs_delay                              :  8;
#else    /* Little Endian */
     unsigned      dq_dqs_delay                              :  8;
     unsigned      reserved0                                 : 24;
#endif
} ncp_phy_CFG_SYSMEM_PHY_LATDQSDLY_BLxCSx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_LATDQEYE_BLxCSx_r_t
 *  @brief CFG_SYSMEM_PHY_LATDQEYE_BLxCSx
 *  @details Indicates the last arriving DQ in byte lane BLx for rank CSx
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_LATDQEYE_BLxCSx_r_t\n
 *   </td>
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
 *     <td width="30%"> @param latest_dq </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Whichever bit is 1 is the last to arrive </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      latest_dq                                 :  8;
#else    /* Little Endian */
     unsigned      latest_dq                                 :  8;
     unsigned      reserved0                                 : 24;
#endif
} ncp_phy_CFG_SYSMEM_PHY_LATDQEYE_BLxCSx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_RDDLY_ERR_r_t
 *  @brief CFG_SYSMEM_PHY_RDDLY_ERR
 *  @details Initial deskew and read eye centering errors. Error bits are reset when register is read, or on the restart of the initial deskew or initial read eye centering. The error bits are not reset at the restart of periodic deskew or read eye centering.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_RDDLY_ERR_r_t\n
 *   </td>
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
 *     <td width="30%"> @param dq_delay_ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Asserted if any one of the DQ delays reaches its max
 *        value before the right edge of the data eye is found.
 *        Updated when Init Deskew state machine finishes.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param no_eye_detect </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> No eye detected by initial read eye centering (passfail
 *        == failpass). Updated when Init Read Eye Centering
 *        state machine finishes.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param read_eye_ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> The pass to fail was not found before the max value.
 *        See md_cpc_frac_lmt. Updated when Init Read Eye Centering
 *        state machine finishes.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param deskew_ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The first falling edge of DQ was not detected before
 *        DQS delay limit. See md_cpc_frac_lmt. Updated when
 *        Init Deskew state machine finishes.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 28;
     unsigned      dq_delay_ovf                              :  1;
     unsigned      no_eye_detect                             :  1;
     unsigned      read_eye_ovf                              :  1;
     unsigned      deskew_ovf                                :  1;
#else    /* Little Endian */
     unsigned      deskew_ovf                                :  1;
     unsigned      read_eye_ovf                              :  1;
     unsigned      no_eye_detect                             :  1;
     unsigned      dq_delay_ovf                              :  1;
     unsigned      reserved0                                 : 28;
#endif
} ncp_phy_CFG_SYSMEM_PHY_RDDLY_ERR_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DQSxGTDLY_BLxCSx_r_t
 *  @brief CFG_SYSMEM_PHY_DQSxGTDLY_BLxCSx
 *  @details Range: 0.00 to 3.75 clks. Amount of delay to insert in quarter clk units between the receipt of RD_EXPECTED signal from MASTER_CNTL and the start of the DQS gating pulse. Read gate delay for DQSx of byte lane BLx for rank CSx.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DQSxGTDLY_BLxCSx_r_t\n
 *   </td>
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
 *     <td width="30%"> @param gt_dly </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Range: 0.00 to 3.75 clks. Amount of delay to insert
 *        in quarter clk units between the receipt of RD_EXPECTED
 *        signal from MASTER_CNTL and the start of the DQS gating
 *        pulse. Read gate delay for DQSx of byte lane BLx for
 *        rank CSx.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 28;
     unsigned      gt_dly                                    :  4;
#else    /* Little Endian */
     unsigned      gt_dly                                    :  4;
     unsigned      reserved0                                 : 28;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DQSxGTDLY_BLxCSx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_RDCALIEMCTERM_r_t
 *  @brief CFG_SYSMEM_PHY_RDCALIEMCTERM
 *  @details DQS 0/1 IE and MCTERM control register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_RDCALIEMCTERM_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 25 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mcterm_dqs_1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> MCTERM DQS 1 Override - 0 = mcterm dynamically controlled,
 *        1 = mcterm constantly enabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ie_dqs_1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> IE DQS1 Static Override - 0 = ie dynamically controlled,
 *        1 = ie constantly enabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mcterm_dqs_0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> MCTERM DQS 0 Override - 0 = mcterm dynamically controlled,
 *        1 = mcterm constantly enabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ie_dqs_0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> IE DQS0 Static Override - 0 = ie dynamically controlled,
 *        1 = ie constantly enabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ie_mcterm_off </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> IE/MCTERM Assertion Offset - Specifies how many clk2x
 *        cycles that the assertion of ie and mcterm precede
 *        the arrival of read data when dynamic ie or mcterm
 *        generation is enabled. This value is valid for both
 *        dqs0 and dqs1.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 25;
     unsigned      mcterm_dqs_1                              :  1;
     unsigned      ie_dqs_1                                  :  1;
     unsigned      mcterm_dqs_0                              :  1;
     unsigned      ie_dqs_0                                  :  1;
     unsigned      ie_mcterm_off                             :  3;
#else    /* Little Endian */
     unsigned      ie_mcterm_off                             :  3;
     unsigned      ie_dqs_0                                  :  1;
     unsigned      mcterm_dqs_0                              :  1;
     unsigned      ie_dqs_1                                  :  1;
     unsigned      mcterm_dqs_1                              :  1;
     unsigned      reserved0                                 : 25;
#endif
} ncp_phy_CFG_SYSMEM_PHY_RDCALIEMCTERM_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_RDCALRDDLYOVR_r_t
 *  @brief CFG_SYSMEM_PHY_RDCALRDDLYOVR
 *  @details During read calibration HW assist, the RDDLY cores are used to validate (or invalidate) potential dqs rank delay settings.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_RDCALRDDLYOVR_r_t\n
 *   </td>
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
 *     <td width="30%"> @param jit_filter_ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> 0 = jitter filter disabled. The hardware will attempt
 *        to find a preamble once at each Rank/DQS_Delay setting.
 *        1 = jitter filter enabled. The hardware will attempt
 *        to find a preamble at each Rank/DQS_Delay setting
 *        multiple times (in multiples of 8).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param jit_filter_loop_cnt </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Upper 3 bits of the N times loop counter. N = 8 when
 *        the jit_filter_loop_cnt = 0, N = 16 when the jit_filter_loop_cnt
 *        = 1, ... N = 64 when the jit_filter_loop_cnt = 7.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param use_ports_not_reg </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> 0 = use register bits for deskew/dqscentering enables
 *        (bits 10:9 of this reg), 1 = use ports for deskew/dqscentering
 *        enables.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param deskew_ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> 1 = RDDLY deskew will be run during read calibration. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqscenter_ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> 1 = RDDLY read eye dqs centering will be run during
 *        read calibration.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dataintegrity_ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> 0 = RDCAL will rely solely on preamble detect sequence
 *        to determine whether the current dqs rank delay settings
 *        are valid, 1 = RDCAL will perform a full data integrity
 *        check of a BL8 read and verify that the JEDEC 01010101
 *        training pattern is captured properly with the current
 *        dqs rank delay settings being evaluated.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqsdelay_ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> 0 = RDCAL will use the default DQS delay value provided
 *        by RDDLY during the scan for a read preamble, 1 =
 *        RDCAL will adjust the DQS delay value from 0 thru
 *        CPC_FRACTION[6:0] using increments of dqsdly_step
 *        while scanning for a read preamble.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqsdly_step </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Amount to use for DQS delay value adjustment during
 *        DQSDELAY iterations. A value of 0x0 will disable DQSDELAY
 *        iterations and instead force the DQS delay to a value
 *        of 0 during the scan for a read preamble.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      jit_filter_ena                            :  1;
     unsigned      jit_filter_loop_cnt                       :  3;
     unsigned      use_ports_not_reg                         :  1;
     unsigned      deskew_ena                                :  1;
     unsigned      dqscenter_ena                             :  1;
     unsigned      dataintegrity_ena                         :  1;
     unsigned      dqsdelay_ena                              :  1;
     unsigned      dqsdly_step                               :  7;
#else    /* Little Endian */
     unsigned      dqsdly_step                               :  7;
     unsigned      dqsdelay_ena                              :  1;
     unsigned      dataintegrity_ena                         :  1;
     unsigned      dqscenter_ena                             :  1;
     unsigned      deskew_ena                                :  1;
     unsigned      use_ports_not_reg                         :  1;
     unsigned      jit_filter_loop_cnt                       :  3;
     unsigned      jit_filter_ena                            :  1;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_CFG_SYSMEM_PHY_RDCALRDDLYOVR_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_RDCALDQSACTIVE_r_t
 *  @brief CFG_SYSMEM_PHY_RDCALDQSACTIVE
 *  @details DQS ACTIVE enable information from the RDCALBYTECNTL cores.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_RDCALDQSACTIVE_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqsactive </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DQSACTIVE bit from each DPRDS nibble lane. Auto-updated
 *        during read calibration algorithm. 0 = corresponding
 *        nibble lane disabled, 1 = corresponding nibble lane
 *        enabled. Indicates which nibble lanes are currently
 *        running an active read calibration algorithm. These
 *        are likely to be a subset of the MC_RC_DQS_GROUP enables
 *        as the DQSACTIVE is an internal state machine variable
 *        that will auto-disable a nibble once: a) valid DQS
 *        gate setting found or b) underflow error detected
 *        while searching for DQS gate setting.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 23;
     unsigned      dqsactive                                 :  9;
#else    /* Little Endian */
     unsigned      dqsactive                                 :  9;
     unsigned      reserved0                                 : 23;
#endif
} ncp_phy_CFG_SYSMEM_PHY_RDCALDQSACTIVE_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_RDCALDATERR_r_t
 *  @brief CFG_SYSMEM_PHY_RDCALDATERR
 *  @details DATAERROR information from the RDCAL cores.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_RDCALDATERR_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dataerror </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data integrity error detect from each DPRDS nibble
 *        lane. 0 = no error detected, 1 = error for corresponding
 *        nibble lane. Auto clears the next time the read calibration
 *        algorithm is run on each corresponding nibble lane.
 *        During a normal read calibration algorithm, several
 *        data integrity errors are likely to be detected (and
 *        cleared) as the DQS gate settings are scanned. As
 *        a result, attempting to observe this register while
 *        the algorithm is running will not provide useful information.
 *        Instead, once the read calibration algorithm finishes
 *        with the expected RC_MC_DONE signal, and an error
 *        interrupt is asserted, this register can be interrogated
 *        by firmware to determine which nibble lane(s) failed
 *        data integrity checking (if enabled via 'dataintegrity_enable'
 *        field within RDDLY-OVVERIDE register).
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 23;
     unsigned      dataerror                                 :  9;
#else    /* Little Endian */
     unsigned      dataerror                                 :  9;
     unsigned      reserved0                                 : 23;
#endif
} ncp_phy_CFG_SYSMEM_PHY_RDCALDATERR_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_RDCALDQSDLY_r_t
 *  @brief CFG_SYSMEM_PHY_RDCALDQSDLY
 *  @details DQS delay override value used during read calibration (if enabled). This is automatically updated during read calibration and visibly provided for debug purposes only.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_RDCALDQSDLY_r_t\n
 *   </td>
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
 *     <td width="30%"> @param dqsdly_override </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DQS delay override value used during read calibration
 *        (if enabled). This is automatically updated during
 *        read calibration and visibly provided for debug purposes
 *        only.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      dqsdly_override                           :  8;
#else    /* Little Endian */
     unsigned      dqsdly_override                           :  8;
     unsigned      reserved0                                 : 24;
#endif
} ncp_phy_CFG_SYSMEM_PHY_RDCALDQSDLY_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_RDCALDQSGRP_r_t
 *  @brief CFG_SYSMEM_PHY_RDCALDQSGRP
 *  @details DQS group information for read calibration hardware assist.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_RDCALDQSGRP_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mc_rc_dqs_group </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The enable mask for byte lanes 0 to 9. 0 = disable
 *        nibble lane/DQS group for hardware assist algorithm,
 *        1 = enable nibble lane for hardware assist. The group
 *        this represents is controlled by the MODE_DEBUG_RCDQSGRP_ENABLE.
 *        If enabled, then this register is used (unaltered)
 *        to configure which group(s) will be processed by the
 *        next calibration request. If disabled, then this register
 *        automatically updates on the cycle that the calibration
 *        request occurs. If disabled, then this register will
 *        automatically update with the hardware MC_RC_DQS_GROUP_I
 *        pins on the cycle that the MC_RC_REQ_I request occurs.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 23;
     unsigned      mc_rc_dqs_group                           :  9;
#else    /* Little Endian */
     unsigned      mc_rc_dqs_group                           :  9;
     unsigned      reserved0                                 : 23;
#endif
} ncp_phy_CFG_SYSMEM_PHY_RDCALDQSGRP_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_RDCALGLBDLY_r_t
 *  @brief CFG_SYSMEM_PHY_RDCALGLBDLY
 *  @details DQS gate delay hardware assist global settings.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_RDCALGLBDLY_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 17 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param observed_rank_delay </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Range: 0.00 to 3.75 clks. Largest value written to
 *        the various DQS_GATE_RANK_DELAY fields. All register
 *        writes to those fields are snooped. This register
 *        updates automatically if the value written is larger
 *        than the value currently stored in the OBSERVED_RANK_DELAY
 *        field. This register is used when computing 1x_latency
 *        = OBSERVED_RANK_DELAY + DQS_GATE_GLOBAL_OFFSET + RD_FIFO_DELAY.
 *        Note that the sum is always rounded down so any fraction
 *        after adding (b11.11) + (b11.11) + (b1) will be truncated,
 *        i.e. b11.01 + b11.01 + b1 = b111.10 = 7 1x clks of
 *        latency.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param max_rank_delay </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Range: 0.00 to 3.75 clks. Largest delay used by DQS_GATE_RANK_DELAY
 *        hardware assist when scanning for the DQS 0001 preamble.
 *        For a read BL8, the DQS window is 5 clk cycles wide.
 *        The DQS preamble detect takes 4 samples over 1 clk
 *        period. Since the DQS has an unknown value when not
 *        being driven, it is important that only valid portions
 *        of the read BL8 window be used when sampling DQS.
 *        As long as the DQS_GATE_GLOBAL_OFFSET is set properly
 *        to account for common sources of delay, 5 clk cycles
 *        is sufficiently large to allow scanning the full range
 *        of 0.00 to 3.75 clks, e.g. 5 - 1 - 3.75 > 0. A positive
 *        side effect of optimally setting this register's value,
 *        along with optimally setting DQS_GATE_GLOBAL_OFFSET,
 *        results in minimizing the read calibration algorithm
 *        runtime.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqs_gate_global_offset </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Range: 0.00 to 3.75 clks. Amount of common delay to
 *        insert between receipt of RD_EXPECTED_2X signal and
 *        the start of the DQS gating pulse. This common delay,
 *        set by firmware, is stored once and applied globally
 *        to all DQ/DQS groups across all ranks. Factors such
 *        as memory clock delay settings, common DQS delay settings,
 *        common I/O book delay and minimum round trip propagation
 *        delay due to PKG/PCB routing are normally included.
 *        While the optimal value is system configuration dependent,
 *        it can remain at the default 0000 value if worst case
 *        delay between RD_EXPECTED_2X and set_dqs_gate is guaranteed
 *        to always be less than or equal to MAX_RANK_DELAY
 *        clk cycles. A positive side effect,, along with optimally
 *        setting MAX_RANK_DELAY, results in minimizing the
 *        read calibration algorithm runtime.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rd_fifo_dly </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 1X latency = the number of memory clk cycles to wait
 *        after RD_EXPECTED_1X (CL + AL) before returning data
 *        to the memory controller. The 1X latency = OBSERVED_RANK_DELAY
 *        + DQS_GATE_GLOBAL_OFFSET + RD_FIFO_DLY. This register
 *        along with the other two fields control the generation
 *        of FIFOREADVALID that is broadcast to all the datapath
 *        read cores. FIFOREADVALID indicates when the internal
 *        FIFO read pointers should be incremented. The memory
 *        controller should be sampling the data returned from
 *        the phy on the cycle after FIFOREADVALID is asserted.
 *        A hardware assist mode can be enabled that will automatically
 *        set the RD_FIFO_DLY based on the sampled relationship
 *        between all dqs_gate signals and the RD_EXPECTED_1X
 *        signal. Since the fifo only contains 8 entries, incorrectly
 *        setting this register value can result in either buffer
 *        overrun or underrun.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 17;
     unsigned      observed_rank_delay                       :  4;
     unsigned      max_rank_delay                            :  4;
     unsigned      dqs_gate_global_offset                    :  4;
     unsigned      rd_fifo_dly                               :  3;
#else    /* Little Endian */
     unsigned      rd_fifo_dly                               :  3;
     unsigned      dqs_gate_global_offset                    :  4;
     unsigned      max_rank_delay                            :  4;
     unsigned      observed_rank_delay                       :  4;
     unsigned      reserved0                                 : 17;
#endif
} ncp_phy_CFG_SYSMEM_PHY_RDCALGLBDLY_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_RDCALOBSRNKDLY_r_t
 *  @brief CFG_SYSMEM_PHY_RDCALOBSRNKDLY
 *  @details DQS preamble detected information from hardware assist.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_RDCALOBSRNKDLY_r_t\n
 *   </td>
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
 *     <td width="30%"> @param observed_rank_delay </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Range: 0.00 to 3.75 clks. Largest value written to
 *        the various DQS_GATE_RANK_DELAY fields. All register
 *        writes to those fields are snooped. This register
 *        updates automatically if the value written is larger
 *        than the value currently stored in the OBSERVED_RANK_DELAY
 *        field. This register is used when computing 1x_latency
 *        = OBSERVED_RANK_DELAY + DQS_GATE_GLOBAL_OFFSET + RD_FIFO_DELAY.
 *        Note that the sum is always rounded down so any fraction
 *        after adding (b11.11) + (b11.11) + (b1) will be truncated,
 *        i.e. b11.01 + b11.01 + b1 = b111.10 = 7 1x clks of
 *        latency.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 28;
     unsigned      observed_rank_delay                       :  4;
#else    /* Little Endian */
     unsigned      observed_rank_delay                       :  4;
     unsigned      reserved0                                 : 28;
#endif
} ncp_phy_CFG_SYSMEM_PHY_RDCALOBSRNKDLY_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_RDCALPREMB_r_t
 *  @brief CFG_SYSMEM_PHY_RDCALPREMB
 *  @details DQS preamble detected information from hardware assist.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_RDCALPREMB_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqs_preamb_det_a </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PREAMBLE_DETECTED bit from each nibble lane, 0 to
 *        8. 0 = no read preamble detected since reset, 1 =
 *        DQS 0001 read preamble detected for the corresponding
 *        nibble lanes. Must reset the corresponding nibble
 *        lane in order to clear the PREAMBLE_DETECTED bit.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 23;
     unsigned      dqs_preamb_det_a                          :  9;
#else    /* Little Endian */
     unsigned      dqs_preamb_det_a                          :  9;
     unsigned      reserved0                                 : 23;
#endif
} ncp_phy_CFG_SYSMEM_PHY_RDCALPREMB_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_RDCALCFG1_r_t
 *  @brief CFG_SYSMEM_PHY_RDCALCFG1
 *  @details Provides RDCAL configuration.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_RDCALCFG1_r_t\n
 *   </td>
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
 *     <td width="30%"> @param preamb_det_timeshf_ctl </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> 00 = always disabled, 01 = Reserved, 10 = dynamically
 *        enabled (controlled by hw), 11 = always enabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqsgate_det_algo_ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> 0 = sticky valid preamble detect algorithm, 1 = DQS_Gate
 *        valid preamble detect algorithm.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ext_preamb_det_mode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> 0 = preamble detect modes 2 or 3 (zeroes before a
 *        one), 1 = preamble detect modes 3,4,5, or 6 (zeroes
 *        before a one). This bits is used to qualify the preamble_detect_mode.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqs_dc_off_ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> 0 = DQS receiver differential offset disabled at all
 *        times, 1 = Enable DQS differential offset controls.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqs_dc_off_static </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> 0 = if enabled by dqs_recv_dc_off_mstr_ena, DC offset
 *        will be controlled dynamically by the hw based on
 *        the calibration mode (e.g. enabled for first pass
 *        preamble detection and disabled for second pass preamble
 *        detection refinement), 1 = if enabled by dqs_recv_dc_off_mstr_ena,
 *        DC offset will be enabled at all times (regardless
 *        of the calibration mode).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqs_off_value </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Receiver differential DC voltage offset value. 000
 *        = 80mV, 001 = 120mV, 010 = 160mV, 011 = 200mV, 1xx
 *        = Reserved.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param refine_off_mode_ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> 0 = Single pass of RDCAL preamble detection using
 *        the max_rank_delay (the PDM mode is defined by the
 *        preamble_detect_mode), 1 = Two passes of RDCAL preamble
 *        detection enabled. The first preamble detection pass
 *        is defined by the refine_offset_preamble_detect_mode
 *        and where max_rank_delay is used as the largest rank
 *        delay when scanning for the DQS preamble. The second
 *        preamble detection pass will employ PDMyy (where yy
 *        is defined by the preamble_detect_mode) in addition,
 *        the 2nd pass will use the refine_off in place of max_rank_delay.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param refine_off_mode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> This field is only valid when refine_off_mode_ena
 *        is enabled. Used during the first preamble detection
 *        pass. 00 = 0000001 preamble sequence detect, 01 =
 *        000001 preamble sequence detect, 10 = 00001 preamble
 *        sequence detect, 11 = 0001 preamble detect sequence.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param refine_off_pol </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> 0 = Subtract refine offset, 1 = Add refine offset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param refine_off </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> +7 to -7 will be added to the current dqs_gate_rank_delay
 *        value (on a per rank / per byte / per nibble basis)
 *        to begin scanning for a DQS preamble when either:
 *        a) hardware transitions between 1st and 2nd pass of
 *        read calibration preamble detection (i.e. refine_off_mode
 *        enabled for 2 passes) or b) refine only debug mode
 *        is enabled and refine_off_mode is disabled.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      preamb_det_timeshf_ctl                    :  2;
     unsigned      dqsgate_det_algo_ena                      :  1;
     unsigned      ext_preamb_det_mode                       :  1;
     unsigned      dqs_dc_off_ena                            :  1;
     unsigned      dqs_dc_off_static                         :  1;
     unsigned      dqs_off_value                             :  3;
     unsigned      refine_off_mode_ena                       :  1;
     unsigned      refine_off_mode                           :  2;
     unsigned      refine_off_pol                            :  1;
     unsigned      refine_off                                :  3;
#else    /* Little Endian */
     unsigned      refine_off                                :  3;
     unsigned      refine_off_pol                            :  1;
     unsigned      refine_off_mode                           :  2;
     unsigned      refine_off_mode_ena                       :  1;
     unsigned      dqs_off_value                             :  3;
     unsigned      dqs_dc_off_static                         :  1;
     unsigned      dqs_dc_off_ena                            :  1;
     unsigned      ext_preamb_det_mode                       :  1;
     unsigned      dqsgate_det_algo_ena                      :  1;
     unsigned      preamb_det_timeshf_ctl                    :  2;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_CFG_SYSMEM_PHY_RDCALCFG1_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_RDCALCFG2_r_t
 *  @brief CFG_SYSMEM_PHY_RDCALCFG2
 *  @details Provides additional RDCAL configuration.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_RDCALCFG2_r_t\n
 *   </td>
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
 *     <td width="30%"> @param rdcalrsvd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved, must be written as zero </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param jitter_fltr_allpass_ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Chicken switch. 0 = never allow jitter filter to run
 *        during 1st pass and use rddlyoverride[15] register
 *        to control whether last pass of RDCAL uses the jitter
 *        filter, 1 = enable jitter filter for all passes of
 *        RDCAL.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param phase_rot_cmp_ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> 0 = test chip version compatibility mode, 1 = enable
 *        phase rotator compare function.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param phase_rot_margin_pol </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> 0 = subtract, 1 = add. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param phase_rot_margin </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 00 = 0*cpc_fraction, 01 = 0.25*cpc_fraction, 10 =
 *        0.50*cpc_fraction, 11 = 0.75*cpc_fraction.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      rdcalrsvd                                 :  1;
     unsigned      reserved1                                 : 10;
     unsigned      jitter_fltr_allpass_ena                   :  1;
     unsigned      phase_rot_cmp_ena                         :  1;
     unsigned      phase_rot_margin_pol                      :  1;
     unsigned      phase_rot_margin                          :  2;
#else    /* Little Endian */
     unsigned      phase_rot_margin                          :  2;
     unsigned      phase_rot_margin_pol                      :  1;
     unsigned      phase_rot_cmp_ena                         :  1;
     unsigned      jitter_fltr_allpass_ena                   :  1;
     unsigned      reserved1                                 : 10;
     unsigned      rdcalrsvd                                 :  1;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_CFG_SYSMEM_PHY_RDCALCFG2_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_RDCALBYTEERRDQS_r_t
 *  @brief CFG_SYSMEM_PHY_RDCALBYTEERRDQS
 *  @details Provides byte level error information for each nibble.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_RDCALBYTEERRDQS_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param byte_error_dqs_n </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Indicates on a per byte basis whether nibble n reported
 *        an error and was unable to complete read calibration
 *        properly. The output port RDCAL_BYTE_ERROR_O is bitwise
 *        OR'd expression of these two nibble n registers. This
 *        register is read only and reading from the register
 *        will have no effect on the RDCAL_BYTE_ERROR_O outputs.
 *        Asserting reset_recover or re-running read calibration
 *        are the only two mechanisms to clear the bits in this
 *        register. Only two possible errors are reported in
 *        these fields: preamble not found or data integrity
 *        error detected. NOTE: the contents of these registers
 *        are only valid upon completion of read calibration.
 *        Attempting to read these registers while read calibration
 *        is in progress will return unpredictable read data.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 23;
     unsigned      byte_error_dqs_n                          :  9;
#else    /* Little Endian */
     unsigned      byte_error_dqs_n                          :  9;
     unsigned      reserved0                                 : 23;
#endif
} ncp_phy_CFG_SYSMEM_PHY_RDCALBYTEERRDQS_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_RDCALMISC_r_t
 *  @brief CFG_SYSMEM_PHY_RDCALMISC
 *  @details Miscellaneous RDCAL information from hardware assist.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_RDCALMISC_r_t\n
 *   </td>
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
 *     <td width="30%"> @param rc_iteration_count </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Number of additional reads that should be attempted
 *        for each DQS gating delay value during read calibration.
 *        Since the algorithm scans various DQS gating delay
 *        values to search for the read preamble, jitter effects
 *        may cause difficulty in environments with challenging
 *        DQS signal integrity. Only one passing preamble detect
 *        is necessary to properly set the DQS gating window
 *        start, due to implicit guardband, so increasing the
 *        read iteration count can provide a degree of jitter
 *        immunity. This value represents the 3 msbs of a 5
 *        bit counter. total_count = rc_iteration_count,3'b11
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mc_rc_rank </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Rank that was processed by RD_CALIBRATION_CNTL_DQS_GATE
 *        hardware assist algorithm during the last read calibration.
 *        When mode_debug_rcdqsgrp_enable field in the RD_CAL_CNTL_CONFIG_REG
 *        is enabled, then this register is used, unaltered,
 *        to configure which rank will be processed by the next
 *        read calibration request. When mode_debug_rcdqsgrp_enable
 *        field is disabled, then this register will automatically
 *        update with the hardware MC_RC_RANK pins on the cycle
 *        that the calibration request occurs.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 22;
     unsigned      rc_iteration_count                        :  3;
     unsigned      mc_rc_rank                                :  3;
     unsigned      reserved1                                 :  4;
#else    /* Little Endian */
     unsigned      reserved1                                 :  4;
     unsigned      mc_rc_rank                                :  3;
     unsigned      rc_iteration_count                        :  3;
     unsigned      reserved0                                 : 22;
#endif
} ncp_phy_CFG_SYSMEM_PHY_RDCALMISC_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_RDCALBYTSTA_r_t
 *  @brief CFG_SYSMEM_PHY_RDCALBYTSTA
 *  @details Read calibration byte status information from hardware assist.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_RDCALBYTSTA_r_t\n
 *   </td>
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
 *     <td width="30%"> @param preamble_not_found_err </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> 0 = no error, 1 = HW assist could not fine a DQS preamble
 *        for at least one DQ/DQS group. bit[15] is nibble1,
 *        bit[14] is nibble0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reg_wrt_collision_detected </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> A register write was attempted while the state machines
 *        were active.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dprds_busy_error_nibble1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Once the read pipeline goes idle, all busys should
 *        de-assert. During RDCAL, if the BUSYOUT from the DPRDS
 *        doesn't de-assert in a reasonable length of time then
 *        a BUSY_ERROR is flagged which will cause the algorithm
 *        to retry with a different set of timing values.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dprds_busy_error_nibble0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Once the read pipeline goes idle, all busys should
 *        de-assert. During RDCAL, if the BUSYOUT from the DPRDS
 *        doesn't de-assert in a reasonable length of time then
 *        a BUSY_ERROR is flagged which will cause the algorithm
 *        to retry with a different set of timing values.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rd_cal_stat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Byte level state machine status. 0 = idle, 1 = busy. </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      preamble_not_found_err                    :  2;
     unsigned      reserved1                                 :  1;
     unsigned      reg_wrt_collision_detected                :  1;
     unsigned      dprds_busy_error_nibble1                  :  1;
     unsigned      dprds_busy_error_nibble0                  :  1;
     unsigned      reserved2                                 :  9;
     unsigned      rd_cal_stat                               :  1;
#else    /* Little Endian */
     unsigned      rd_cal_stat                               :  1;
     unsigned      reserved2                                 :  9;
     unsigned      dprds_busy_error_nibble0                  :  1;
     unsigned      dprds_busy_error_nibble1                  :  1;
     unsigned      reg_wrt_collision_detected                :  1;
     unsigned      reserved1                                 :  1;
     unsigned      preamble_not_found_err                    :  2;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_CFG_SYSMEM_PHY_RDCALBYTSTA_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_RDCALCTLSTA_r_t
 *  @brief CFG_SYSMEM_PHY_RDCALCTLSTA
 *  @details Read calibration status information from hardware assist.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_RDCALCTLSTA_r_t\n
 *   </td>
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
 *     <td width="30%"> @param interrupt_flag </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> OR function of bits 9 and 14 of this register. 0 =
 *        no interrupt, 1 = interrupt active. Clear by reading
 *        this register.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param preamble_not_found_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> 0 = no error, 1 = HW assist could not find a DQS preamble
 *        (based on configured PREAMBLE_DETECT_MODE) for at
 *        least one DQ/DQS group. Examine RDCAL_PREAMBLE and
 *        RDCAL_DATAERR registers to identify missing preambles.
 *        Clear by reading this register.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reg_wrt_collision_detected </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> A register write was attempted while the state machines
 *        were active.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param deskew_err_detect </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> 0 = no error, 1 = RDDLY detected an error during attempted
 *        deskew operation. Check ??? register for more information.
 *        Clears on read.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqscenter_err_detect </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> 0 = no error, 1 = RDDLY detected an error during attempted
 *        dqs center operation. Check ??? register for more
 *        information. Clears on read.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dat_err_detect </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> 0 = no error, 1 = final DQS gate settings resulted
 *        in a data integrity check error. Check CFG_SYSMEM_PHY_RDCALDATERR
 *        register for more information. Clears on read.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param internal_deskew_err </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> 0 = no error, 1 = at least 1 of the final DQS_GATE_RANK_DELAY
 *        settings resulted in RDDLY DQ deskew error. If no
 *        data integrity errors were detected, this should be
 *        treated as a warning. Such warnings occur most often
 *        when the far right edge of the data eye cannot be
 *        found when operating in fast PVT corners. May indicate
 *        non-ideal DQ deskew results on the affected bytes/nibbles.
 *        Bit 8 corresponds to DQS1 and bit 7 corresponds to
 *        DQS0. Check CFG_SYSMEM_PHY_RDCALDQSGRP, CFG_SYSMEM_PHY_RDCALRDDLYOVR,
 *        CFG_SYSMEM_PHY_RDCALDATERR, CFG_SYSMEM_PHY_RDDLY_ERR
 *        registers for more information. Clears automatically
 *        when read calibration algorithm starts.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param internal_dqscenter_err </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> 0 = no error, 1 = at least 1 of the final DQS_GATE_RANK_DELAY
 *        settings resulted in RDDLY DQS centering error. If
 *        no data integrity errors were detected, this should
 *        be treated as a warning. Such warnings occur most
 *        often when the far right edge of the data eye cannot
 *        be found when operating in fast PVT corners. May indicate
 *        non-ideal DQS centering results on the affected bytes/nibbles.
 *        Bit 6 corresponds to DQS1 and bit 5 corresponds to
 *        DQS0. Check CFG_SYSMEM_PHY_RDCALDQSGRP, CFG_SYSMEM_PHY_RDCALRDDLYOVR,
 *        CFG_SYSMEM_PHY_RDCALDATERR, CFG_SYSMEM_PHY_RDDLY_ERR
 *        registers for more information. Clears automatically
 *        when read calibration algorithm starts.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param internal_preamb_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> 0 = no error, 1 = at least 1 active byte/nibble failed
 *        to find a read preamble. Check CFG_SYSMEM_PHY_RDCALDQSGRP
 *        and CFG_SYSMEM_PHY_RDCALPREMB registers for more information.
 *        Clears automatically when read calibration algorithm
 *        starts.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rd_cal_stat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Byte level state machine status. 0 = idle, 1 = busy. </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      interrupt_flag                            :  1;
     unsigned      preamble_not_found_err                    :  1;
     unsigned      reserved1                                 :  1;
     unsigned      reg_wrt_collision_detected                :  1;
     unsigned      deskew_err_detect                         :  1;
     unsigned      dqscenter_err_detect                      :  1;
     unsigned      dat_err_detect                            :  1;
     unsigned      internal_deskew_err                       :  2;
     unsigned      internal_dqscenter_err                    :  2;
     unsigned      internal_preamb_err                       :  1;
     unsigned      reserved2                                 :  3;
     unsigned      rd_cal_stat                               :  1;
#else    /* Little Endian */
     unsigned      rd_cal_stat                               :  1;
     unsigned      reserved2                                 :  3;
     unsigned      internal_preamb_err                       :  1;
     unsigned      internal_dqscenter_err                    :  2;
     unsigned      internal_deskew_err                       :  2;
     unsigned      dat_err_detect                            :  1;
     unsigned      dqscenter_err_detect                      :  1;
     unsigned      deskew_err_detect                         :  1;
     unsigned      reg_wrt_collision_detected                :  1;
     unsigned      reserved1                                 :  1;
     unsigned      preamble_not_found_err                    :  1;
     unsigned      interrupt_flag                            :  1;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_CFG_SYSMEM_PHY_RDCALCTLSTA_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_RDCALCTLCFG_r_t
 *  @brief CFG_SYSMEM_PHY_RDCALCTLCFG
 *  @details Read calibration control for hardware assist.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_RDCALCTLCFG_r_t\n
 *   </td>
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
 *     <td width="30%"> @param seq_det_cs </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Chicken switch. 0 = only the configured sequence [14:13]
 *        will be used for preamble detection, 1 = for high
 *        jitter environments, preamble sequence detector will
 *        allow the current [14:13] or larger sequences to trigger
 *        preamble detection.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param preamble_detect_mode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> The encoded value of this field is dependent on the
 *        value of EXTENDED PREAMBLE DETECT MODE on ???. When
 *        EXTENDED PREAMBLE DETECT MODE = 0 then b00/b01 are
 *        reserved, b10 - 001 preamble sequence detect, b11
 *        - 0001 preamble sequence detect. When EXTENDED PREAMBLE
 *        DETECT MODE = 1 then b00 - 0000001 preamble sequence
 *        detect, b01 - 000001 preamble sequence detect, b10
 *        - 00001 preamble sequence detect, b11 - 0001 preamble
 *        sequence detect.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mode_debug_rcdqsgrp_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> 0 = MC_RC_RANK and MC_RC_DQSGROUP fields are automatically
 *        overridden by hardware pin values upon read calibration
 *        request. 1 = MC_RC_RANK and MC_RC_DQSGROUP fields
 *        remain static thereby allowing register writes to
 *        configure which dqs groups will be processed during
 *        the next read calibration request.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqs_gate_guardband_polarity </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> 0 = subtract DQS_GATE_GUARDBAND, 1 = add DQS_GATE_GUARDBAND. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqs_gate_guardband </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Range: 0.00 to 1.75 clks. Guardband offset in quarter
 *        cycle increments added/subtracted to/from all hardware
 *        assisted DQS_GATE_RANK_DELAY settings prior to updating
 *        register.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mode </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Bit 3: Reserved. Bit 2: Reserved. Bit 1: DQS_GATE_RANK_DELAY
 *        hardware assist enable. Bit 0: Reserved.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      seq_det_cs                                :  1;
     unsigned      preamble_detect_mode                      :  2;
     unsigned      mode_debug_rcdqsgrp_enable                :  1;
     unsigned      dqs_gate_guardband_polarity               :  1;
     unsigned      dqs_gate_guardband                        :  3;
     unsigned      reserved1                                 :  4;
     unsigned      mode                                      :  4;
#else    /* Little Endian */
     unsigned      mode                                      :  4;
     unsigned      reserved1                                 :  4;
     unsigned      dqs_gate_guardband                        :  3;
     unsigned      dqs_gate_guardband_polarity               :  1;
     unsigned      mode_debug_rcdqsgrp_enable                :  1;
     unsigned      preamble_detect_mode                      :  2;
     unsigned      seq_det_cs                                :  1;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_CFG_SYSMEM_PHY_RDCALCTLCFG_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DFICNTLLAT_r_t
 *  @brief CFG_SYSMEM_PHY_DFICNTLLAT
 *  @details This register provides programmability for the defined DFI read and write data latency parameters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DFICNTLLAT_r_t\n
 *   </td>
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
 *     <td width="30%"> @param rd_rqst_dly </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Number of clock cycles delay added between read request
 *        to the read command during read calibration and read
 *        eye centering.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dm_ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Data mask feature enable. It is expected that this
 *        feature is only enabled when all DIMMs connected are
 *        in x8 mode.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlat </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> DFI write latency tphy_wrlat. It is the same for all
 *        ranks.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlat </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DFI read latency tphy_rdlat. It is the same for all
 *        ranks.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 19;
     unsigned      rd_rqst_dly                               :  2;
     unsigned      dm_ena                                    :  1;
     unsigned      wrlat                                     :  5;
     unsigned      rdlat                                     :  5;
#else    /* Little Endian */
     unsigned      rdlat                                     :  5;
     unsigned      wrlat                                     :  5;
     unsigned      dm_ena                                    :  1;
     unsigned      rd_rqst_dly                               :  2;
     unsigned      reserved0                                 : 19;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DFICNTLLAT_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_CPCMODE_r_t
 *  @brief CFG_SYSMEM_CPCMODE
 *  @details This register provides debug info concerning the CPC config mode.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_CPCMODE_r_t\n
 *   </td>
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
 *     <td width="30%"> @param cpc_avgmode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Not currently supported, spare </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpc_cfgmode </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> For debug use only, TBD. </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 26;
     unsigned      cpc_avgmode                               :  2;
     unsigned      cpc_cfgmode                               :  4;
#else    /* Little Endian */
     unsigned      cpc_cfgmode                               :  4;
     unsigned      cpc_avgmode                               :  2;
     unsigned      reserved0                                 : 26;
#endif
} ncp_phy_CFG_SYSMEM_PHY_CPCMODE_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_CPC_ERRBUS_ADRCMD_r_t
 *  @brief CFG_SYSMEM_CPC_ERRBUS_ADRCMD
 *  @details This register provides detailed error information about the CPC algorithm. A read of this register clears all bits! Re-initiation of the CPC algorithm followed by the absence of an error will also clear the bit corresponding to that location.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_CPC_ERRBUS_ADRCMD_r_t\n
 *   </td>
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
 *     <td width="30%"> @param cpc_unferr_cmd3bit1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPC underflow error for address command VREG regions
 *        3, 2, 1, 0. 0 = no CPC error, 1 = CPC error occurred.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpc_unferr_cmd3bit0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPC underflow error for address command VREG regions
 *        3, 2, 1, 0. 0 = no CPC error, 1 = CPC error occurred.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpc_unferr_cmd2bit1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPC underflow error for address command VREG regions
 *        3, 2, 1, 0. 0 = no CPC error, 1 = CPC error occurred.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpc_unferr_cmd2bit0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPC underflow error for address command VREG regions
 *        3, 2, 1, 0. 0 = no CPC error, 1 = CPC error occurred.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpc_unferr_cmd1bit1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPC underflow error for address command VREG regions
 *        3, 2, 1, 0. 0 = no CPC error, 1 = CPC error occurred.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpc_unferr_cmd1bit0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPC underflow error for address command VREG regions
 *        3, 2, 1, 0. 0 = no CPC error, 1 = CPC error occurred.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpc_unferr_cmd0bit1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPC underflow error for address command VREG regions
 *        3, 2, 1, 0. 0 = no CPC error, 1 = CPC error occurred.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpc_unferr_cmd0bit0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPC underflow error for address command VREG regions
 *        3, 2, 1, 0. 0 = no CPC error, 1 = CPC error occurred.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cpc_unferr_cmd3bit1                       :  1;
     unsigned      cpc_unferr_cmd3bit0                       :  1;
     unsigned      cpc_unferr_cmd2bit1                       :  1;
     unsigned      cpc_unferr_cmd2bit0                       :  1;
     unsigned      cpc_unferr_cmd1bit1                       :  1;
     unsigned      cpc_unferr_cmd1bit0                       :  1;
     unsigned      cpc_unferr_cmd0bit1                       :  1;
     unsigned      cpc_unferr_cmd0bit0                       :  1;
#else    /* Little Endian */
     unsigned      cpc_unferr_cmd0bit0                       :  1;
     unsigned      cpc_unferr_cmd0bit1                       :  1;
     unsigned      cpc_unferr_cmd1bit0                       :  1;
     unsigned      cpc_unferr_cmd1bit1                       :  1;
     unsigned      cpc_unferr_cmd2bit0                       :  1;
     unsigned      cpc_unferr_cmd2bit1                       :  1;
     unsigned      cpc_unferr_cmd3bit0                       :  1;
     unsigned      cpc_unferr_cmd3bit1                       :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_phy_CFG_SYSMEM_PHY_CPC_ERRBUS_ADRCMD_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_CPC_ERRBUS_BYTES_r_t
 *  @brief CFG_SYSMEM_CPC_ERRBUS_BYTES
 *  @details This register provides detailed error information about the CPC algorithm. A read of this register clears all bits! Re-initiation of the CPC algorithm followed by the absence of an error will also clear the bit corresponding to that location.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_CPC_ERRBUS_BYTES_r_t\n
 *   </td>
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
 *     <td width="30%"> @param cpc_unferr_dqs1bit1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPC underflow error for bytes. 0 = no CPC error, 1
 *        = CPC error occurred.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpc_unferr_dqs1bit0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPC underflow error for bytes. 0 = no CPC error, 1
 *        = CPC error occurred.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpc_unferr_dqs0bit1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPC underflow error for bytes. 0 = no CPC error, 1
 *        = CPC error occurred.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpc_unferr_dqs0bit0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPC underflow error for bytes. 0 = no CPC error, 1
 *        = CPC error occurred.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 28;
     unsigned      cpc_unferr_dqs1bit1                       :  1;
     unsigned      cpc_unferr_dqs1bit0                       :  1;
     unsigned      cpc_unferr_dqs0bit1                       :  1;
     unsigned      cpc_unferr_dqs0bit0                       :  1;
#else    /* Little Endian */
     unsigned      cpc_unferr_dqs0bit0                       :  1;
     unsigned      cpc_unferr_dqs0bit1                       :  1;
     unsigned      cpc_unferr_dqs1bit0                       :  1;
     unsigned      cpc_unferr_dqs1bit1                       :  1;
     unsigned      reserved0                                 : 28;
#endif
} ncp_phy_CFG_SYSMEM_PHY_CPC_ERRBUS_BYTES_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DFICNTLCPCCNTL_r_t
 *  @brief CFG_SYSMEM_PHY_DFICNTLCPCCNTL
 *  @details This register provides phy level update enables, intervals and phy DFI status.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DFICNTLCPCCNTL_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param init_train_complt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> The PHY will write a 1 to this bit when it detects
 *        the first rising edge on the dfi_ctrlupd_req after
 *        the PHY reset. This is used to indicate that the MC
 *        completed the initial training and is ready for memory
 *        writes and reads. Software can also set and reset
 *        this bit to allow or perform the initial training
 *        again if needed.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param phy_init_complt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Firmware should write a 1 to this bit after it completes
 *        the initialization of the PHY. This bit drives dfi_init_complete
 *        and will indicate to the controller that PHY initialization
 *        is complete and is ready for initial DFI training
 *        sequences.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param phy_upd_intf_ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> 0 = PHY update interface is disabled and CPC and runtime
 *        read level updates are performed during control update
 *        interval, 1 = PHY update interface is enabled to perform
 *        CPC and runtime read leveling updates.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpc_upd_intv </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> 00 = run CPC update for every other update event,
 *        01 = run CPC update every 3rd update event, 10 = run
 *        CPC update every 5th update event, 11 = run CPC update
 *        every 9th update event. Update event is defined by
 *        the update interval setting. During all other update
 *        events not used by CPC updates are used for the runtime
 *        read leveling updates.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param upd_intv </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> 00 = CPC/runtime read level update happens during
 *        every control update request, 01 = CPC/runtime read
 *        level update happens during every 4 control update
 *        requests, 10 = CPC/runtime read level update happens
 *        during every 16 control update requests, 11 = CPC/runtime
 *        read level update happens during every 64 control
 *        update requests.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param auto_cpc_upd_ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> 0 = disable periodic CPC updates, 1 = enable automatic
 *        periodic CPC updates depending on the update interval
 *        and CPC update interval settings.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpc_upd_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Firmware CPC update request. This is self cleared
 *        after the CPC update is done.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 23;
     unsigned      init_train_complt                         :  1;
     unsigned      phy_init_complt                           :  1;
     unsigned      phy_upd_intf_ena                          :  1;
     unsigned      cpc_upd_intv                              :  2;
     unsigned      upd_intv                                  :  2;
     unsigned      auto_cpc_upd_ena                          :  1;
     unsigned      cpc_upd_req                               :  1;
#else    /* Little Endian */
     unsigned      cpc_upd_req                               :  1;
     unsigned      auto_cpc_upd_ena                          :  1;
     unsigned      upd_intv                                  :  2;
     unsigned      cpc_upd_intv                              :  2;
     unsigned      phy_upd_intf_ena                          :  1;
     unsigned      phy_init_complt                           :  1;
     unsigned      init_train_complt                         :  1;
     unsigned      reserved0                                 : 23;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DFICNTLCPCCNTL_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DFICNTLCPCREQMSK0_r_t
 *  @brief CFG_SYSMEM_PHY_DFICNTLCPCREQMSK0
 *  @details This register provides byte lane granularity enables for CPC updates.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DFICNTLCPCREQMSK0_r_t\n
 *   </td>
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
 *     <td width="30%"> @param dqs1_grpmska </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Individual byte lane masks for dqs1 CPC updates. Bit
 *        9 for byte lane 0 up to bit 15 for byte lane 6. 0
 *        = enable periodic CPC updates, 1 = no periodic CPC
 *        updates.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqs0_grpmsk </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Individual byte lane masks for dqs0 CPC updates. Bit
 *        0 for byte lane 0 up to bit 8 for byte lane 8. 0 =
 *        enable periodic CPC updates, 1 = no periodic CPC updates.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      dqs1_grpmska                              :  7;
     unsigned      dqs0_grpmsk                               :  9;
#else    /* Little Endian */
     unsigned      dqs0_grpmsk                               :  9;
     unsigned      dqs1_grpmska                              :  7;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DFICNTLCPCREQMSK0_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DFICNTLCPCREQMSK1_r_t
 *  @brief CFG_SYSMEM_PHY_DFICNTLCPCREQMSK1
 *  @details This register provides the remaining byte lane granularity enables and single data rate macro enables for CPC updates.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DFICNTLCPCREQMSK1_r_t\n
 *   </td>
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
 *     <td width="30%"> @param adr_blkmsk </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Individual ADR macro masks for CPC updates. Bit 2
 *        for ADR0 up to bit 5 for ADR3. 0 = enable periodic
 *        CPC updates, 1 = no periodic CPC updates.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqs1_grpmskb </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Individual byte lane masks for dqs1 CPC updates. Bit
 *        0 for byte lane 7 up to bit 1 for byte lane 8. 0 =
 *        enable periodic CPC updates, 1 = no periodic CPC updates.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 26;
     unsigned      adr_blkmsk                                :  4;
     unsigned      dqs1_grpmskb                              :  2;
#else    /* Little Endian */
     unsigned      dqs1_grpmskb                              :  2;
     unsigned      adr_blkmsk                                :  4;
     unsigned      reserved0                                 : 26;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DFICNTLCPCREQMSK1_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DFICNTLCPCUPDSTAT0_r_t
 *  @brief CFG_SYSMEM_PHY_DFICNTLCPCUPDSTAT0
 *  @details This register provides byte lane granularity for CPC update status.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DFICNTLCPCUPDSTAT0_r_t\n
 *   </td>
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
 *     <td width="30%"> @param dqs1_updstata </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Individual byte lane dqs1 CPC update status. Bit 9
 *        for byte lane 0 up to bit 15 for byte lane 6. 0 =
 *        recent CPC update run resulted in an error, 1 = CPC
 *        update run successful.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqs0_updstat </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Individual byte lane dqs0 CPC update status. Bit 0
 *        for byte lane 0 up to bit 8 for byte lane 8. 0 = recent
 *        CPC update run resulted in an error, 1 = CPC update
 *        run successful.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      dqs1_updstata                             :  7;
     unsigned      dqs0_updstat                              :  9;
#else    /* Little Endian */
     unsigned      dqs0_updstat                              :  9;
     unsigned      dqs1_updstata                             :  7;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DFICNTLCPCUPDSTAT0_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DFICNTLCPCUPDSTAT1_r_t
 *  @brief CFG_SYSMEM_PHY_DFICNTLCPCUPDSTAT1
 *  @details This register provides the remaining byte lane granularity and single data rate macros CPC update status.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DFICNTLCPCUPDSTAT1_r_t\n
 *   </td>
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
 *     <td width="30%"> @param adr_updstat </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Individual ADR macro CPC update status. Bit 2 for
 *        ADR0 up to bit 5 for ADR3. 0 = recent CPC update run
 *        resulted in an error, 1 = CPC update run successful.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqs1_updstatb </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Individual byte lane dqs1 CPC update status. Bit 0
 *        for byte lane 7 up to bit 1 for byte lane 8. 0 = recent
 *        CPC update run resulted in an error, 1 = CPC update
 *        run successful.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 26;
     unsigned      adr_updstat                               :  4;
     unsigned      dqs1_updstatb                             :  2;
#else    /* Little Endian */
     unsigned      dqs1_updstatb                             :  2;
     unsigned      adr_updstat                               :  4;
     unsigned      reserved0                                 : 26;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DFICNTLCPCUPDSTAT1_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DFICNTLWLDQS0GRP_r_t
 *  @brief CFG_SYSMEM_PHY_DFICNTLWLDQS0GRP
 *  @details This register provides byte lane granularity write level delay adjustment enables.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DFICNTLWLDQS0GRP_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wldqs0_ena </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Individual byte lane dqs0 write level cycle adjust
 *        enables. Bit 0 for byte lane 0 up to bit 8 for byte
 *        lane 8. 0 = no delay adjust is performed, 1 = if this
 *        bit and the write cycle adjust bit of WRLVL_CNTL are
 *        set, then delay adjust is performed.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 23;
     unsigned      wldqs0_ena                                :  9;
#else    /* Little Endian */
     unsigned      wldqs0_ena                                :  9;
     unsigned      reserved0                                 : 23;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DFICNTLWLDQS0GRP_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DFICNTLWLDQS1GRP_r_t
 *  @brief CFG_SYSMEM_PHY_DFICNTLWLDQS1GRP
 *  @details This register also provides byte lane granularity write level delay adjustment enables.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DFICNTLWLDQS1GRP_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wldqs1_ena </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Individual byte lane dqs1 write level cycle adjust
 *        enables. Bit 0 for byte lane 0 up to bit 8 for byte
 *        lane 8. 0 = no delay adjust is performed, 1 = if this
 *        bit and the write cycle adjust bit of WRLVL_CNTL are
 *        set, then delay adjust is performed.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 23;
     unsigned      wldqs1_ena                                :  9;
#else    /* Little Endian */
     unsigned      wldqs1_ena                                :  9;
     unsigned      reserved0                                 : 23;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DFICNTLWLDQS1GRP_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DFICNTLWLCNTL_r_t
 *  @brief CFG_SYSMEM_PHY_DFICNTLWLCNTL
 *  @details This register provides the write level delay adjustment enable, polarity and phy req enable.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DFICNTLWLCNTL_r_t\n
 *   </td>
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
 *     <td width="30%"> @param cyc_adj_rank </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Write level cycle adjust rank. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_dly_delta </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> The delta amount by which the write level delay is
 *        adjusted. 0 = the write level delay is decremented
 *        by 1 clk, 1 = the write level delay is incremented
 *        by 1 clk.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_adj </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Write level adjust enable. A firmware write of 1 in
 *        conjunction with the separate byte lane enables will
 *        perform a write level delay adjustment.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> A firmware write of 1 allows the PHY to assert a write
 *        level request to the controller for write leveling.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 26;
     unsigned      cyc_adj_rank                              :  3;
     unsigned      wrlvl_dly_delta                           :  1;
     unsigned      wrlvl_adj                                 :  1;
     unsigned      wrlvl_req                                 :  1;
#else    /* Little Endian */
     unsigned      wrlvl_req                                 :  1;
     unsigned      wrlvl_adj                                 :  1;
     unsigned      wrlvl_dly_delta                           :  1;
     unsigned      cyc_adj_rank                              :  3;
     unsigned      reserved0                                 : 26;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DFICNTLWLCNTL_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DFICNTLWLSTAT1_r_t
 *  @brief CFG_SYSMEM_PHY_DFICNTLWLSTAT1
 *  @details This register provides the fine write level status.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DFICNTLWLSTAT1_r_t\n
 *   </td>
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
 *     <td width="30%"> @param wr_lvl_sm_active1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> 0 = wrt leveling sm idle, 1 = wrt leveling sm active. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq_nibble_data1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> SDRAM clock samples per nibble straight from the memory
 *        device.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param active_nibble1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Current nibble that the wrt leveling sm is working
 *        on.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wr_lvl_sm1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Write leveling state machine states </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reg_wr_collision_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Error, register write attempted while wrt leveling
 *        sm active.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param riseedge_notfound_err </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Error, rising edge not found. bit 0 is low order nibble,
 *        bit 1 is high order nibble.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      wr_lvl_sm_active1                         :  1;
     unsigned      dq_nibble_data1                           :  2;
     unsigned      active_nibble1                            :  1;
     unsigned      wr_lvl_sm1                                :  9;
     unsigned      reg_wr_collision_err                      :  1;
     unsigned      riseedge_notfound_err                     :  2;
#else    /* Little Endian */
     unsigned      riseedge_notfound_err                     :  2;
     unsigned      reg_wr_collision_err                      :  1;
     unsigned      wr_lvl_sm1                                :  9;
     unsigned      active_nibble1                            :  1;
     unsigned      dq_nibble_data1                           :  2;
     unsigned      wr_lvl_sm_active1                         :  1;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DFICNTLWLSTAT1_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DFICNTLWLSTAT2_r_t
 *  @brief CFG_SYSMEM_PHY_DFICNTLWLSTAT2
 *  @details This register provides the write level status.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DFICNTLWLSTAT2_r_t\n
 *   </td>
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
 *     <td width="30%"> @param wr_lvl_sm_active2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> 0 = wrt leveling sm idle, 1 = wrt leveling sm active. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq_nibble_data2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> SDRAM clock samples per nibble straight from the memory
 *        device.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param active_nibble2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Current nibble that the wrt leveling sm is working
 *        on.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wr_lvl_sm2 </td>
 *     <td width="20%" align="center"> 11 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Write leveling state machine states </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zero_detected </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Zero detected indication from wrt leveling sm (internal
 *        state latch).
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      wr_lvl_sm_active2                         :  1;
     unsigned      dq_nibble_data2                           :  2;
     unsigned      active_nibble2                            :  1;
     unsigned      wr_lvl_sm2                                : 11;
     unsigned      zero_detected                             :  1;
#else    /* Little Endian */
     unsigned      zero_detected                             :  1;
     unsigned      wr_lvl_sm2                                : 11;
     unsigned      active_nibble2                            :  1;
     unsigned      dq_nibble_data2                           :  2;
     unsigned      wr_lvl_sm_active2                         :  1;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DFICNTLWLSTAT2_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DFICNTLWLERR_r_t
 *  @brief CFG_SYSMEM_PHY_DFICNTLWLERR
 *  @details This register provides the write level errors across all byte lanes.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DFICNTLWLERR_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 29 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reg_wr_collision_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Error, register write attempted while wrt leveling
 *        sm active OR'd result of all byte lanes.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param riseedge_notfound_err </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Error, rising edge not found. bit 0 is the OR of all
 *        low order nibbles, bit 1 is the OR of all high order
 *        nibbles.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 29;
     unsigned      reg_wr_collision_err                      :  1;
     unsigned      riseedge_notfound_err                     :  2;
#else    /* Little Endian */
     unsigned      riseedge_notfound_err                     :  2;
     unsigned      reg_wr_collision_err                      :  1;
     unsigned      reserved0                                 : 29;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DFICNTLWLERR_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DFICNTLWLERRMSK_r_t
 *  @brief CFG_SYSMEM_PHY_DFICNTLWLERRMSK
 *  @details This register provides the cumulative write level error masks.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DFICNTLWLERRMSK_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 29 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reg_wr_collision_errmsk </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Error mask, 0 = do not mask, 1 = mask error for register
 *        write attempted while wrt leveling sm active OR'd
 *        result of all byte lanes.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param riseedge_notfound_errmsk </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Error mask, 0 = do not mask, 1 = mask error for rising
 *        edge not found. bit 0 is the OR of all low order nibbles,
 *        bit 1 is the OR of all high order nibbles.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 29;
     unsigned      reg_wr_collision_errmsk                   :  1;
     unsigned      riseedge_notfound_errmsk                  :  2;
#else    /* Little Endian */
     unsigned      riseedge_notfound_errmsk                  :  2;
     unsigned      reg_wr_collision_errmsk                   :  1;
     unsigned      reserved0                                 : 29;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DFICNTLWLERRMSK_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DFICNTLRDLCNTL_r_t
 *  @brief CFG_SYSMEM_PHY_DFICNTLRDLCNTL
 *  @details This register provides the read leveling controls.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DFICNTLRDLCNTL_r_t\n
 *   </td>
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
 *     <td width="30%"> @param runtime_dskew_ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> 0 = do not run periodic deskew, 1 = run periodic read
 *        deskew update whenever the runtime read level update
 *        is done for VT tracking.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param runtime_rdlvl_ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> 0 = do not run periodic read leveling update, 1 =
 *        run periodic read leveling update for VT tracking.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param init_post_dskew_ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Post-deskew enable. 0 = do not perform deskew algorithm
 *        after read eye training during the initial read leveling,
 *        1 = perform deskew after read eye training during
 *        the initial read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param init_pre_dskew_ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Pre-deskew enable. 0 = do not perform deskew algorithm
 *        before read eye training during the initial read leveling,
 *        1 = perform deskew before read eye training during
 *        the initial read leveling.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 28;
     unsigned      runtime_dskew_ena                         :  1;
     unsigned      runtime_rdlvl_ena                         :  1;
     unsigned      init_post_dskew_ena                       :  1;
     unsigned      init_pre_dskew_ena                        :  1;
#else    /* Little Endian */
     unsigned      init_pre_dskew_ena                        :  1;
     unsigned      init_post_dskew_ena                       :  1;
     unsigned      runtime_rdlvl_ena                         :  1;
     unsigned      runtime_dskew_ena                         :  1;
     unsigned      reserved0                                 : 28;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DFICNTLRDLCNTL_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_MSTRCTLCFG5_r_t
 *  @brief CFG_SYSMEM_PHY_MSTRCTLCFG5
 *  @details This register provides alternate reference selects/enable. There is a table to describe the applicable settings. It specifies an item CE0DLT, but not where it comes from.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_MSTRCTLCFG5_r_t\n
 *   </td>
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
 *     <td width="30%"> @param vref_alt_ref_sel_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> VREF alternate reference select enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_alt_ref_sel1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> VREF alternate reference select 1 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_alt_ref_sel0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> VREF alternate reference select 0 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ie_oe_chknsw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Chicken Switch: not currently supported </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 28;
     unsigned      vref_alt_ref_sel_en                       :  1;
     unsigned      vref_alt_ref_sel1                         :  1;
     unsigned      vref_alt_ref_sel0                         :  1;
     unsigned      ie_oe_chknsw                              :  1;
#else    /* Little Endian */
     unsigned      ie_oe_chknsw                              :  1;
     unsigned      vref_alt_ref_sel0                         :  1;
     unsigned      vref_alt_ref_sel1                         :  1;
     unsigned      vref_alt_ref_sel_en                       :  1;
     unsigned      reserved0                                 : 28;
#endif
} ncp_phy_CFG_SYSMEM_PHY_MSTRCTLCFG5_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_ADRxx_VREGCTL0_r_t
 *  @brief CFG_SYSMEM_PHY_ADRxx_VREGCTL0
 *  @details This register provides voltage regulation information for the single data rate macros
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_ADRxx_VREGCTL0_r_t\n
 *   </td>
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
 *     <td width="30%"> @param vregrsrvpin0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved for lab characterization only. Turns bandgap
 *        off.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vregchdyn </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Chicken switch - control loop replica to change loop
 *        gain. 00 = 0%, 01 = +15%, 10 = +30%, 11 = 45%
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vregchcml </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vregtestmux </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for lab characterization only. This selects
 *        the testmux output.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vregrange </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Configures the default width of the PFET transistor
 *        in UREG and UREGMASTER. 00 = 1.5V, 01 = 1.35V, 10
 *        = not used, 11 = 1.25V
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vregc </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 01100 = 0.992V See the section on voltage regulators
 *        for more information. Use of voltages beyond 1.1V
 *        will likely reduce the life span of the phy.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      vregrsrvpin0                              :  1;
     unsigned      vregchdyn                                 :  2;
     unsigned      vregchcml                                 :  2;
     unsigned      vregtestmux                               :  4;
     unsigned      vregrange                                 :  2;
     unsigned      vregc                                     :  5;
#else    /* Little Endian */
     unsigned      vregc                                     :  5;
     unsigned      vregrange                                 :  2;
     unsigned      vregtestmux                               :  4;
     unsigned      vregchcml                                 :  2;
     unsigned      vregchdyn                                 :  2;
     unsigned      vregrsrvpin0                              :  1;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_CFG_SYSMEM_PHY_ADRxx_VREGCTL0_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_ADRxx_VREGCTL1_r_t
 *  @brief CFG_SYSMEM_PHY_ADRxx_VREGCTL1
 *  @details This register provides voltage regulation information for the single data rate macros
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_ADRxx_VREGCTL1_r_t\n
 *   </td>
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
 *     <td width="30%"> @param vregrsrvpin1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param uregrsrvctrl </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved for lab characterization only. Bit 2 turns
 *        off slew control in the UREG. Bits 1,0 not used.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vregrsvd1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      vregrsrvpin1                              :  5;
     unsigned      uregrsrvctrl                              :  3;
     unsigned      vregrsvd1                                 :  8;
#else    /* Little Endian */
     unsigned      vregrsvd1                                 :  8;
     unsigned      uregrsrvctrl                              :  3;
     unsigned      vregrsrvpin1                              :  5;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_CFG_SYSMEM_PHY_ADRxx_VREGCTL1_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_ADRxx_VREGCTL2_r_t
 *  @brief CFG_SYSMEM_PHY_ADRxx_VREGCTL2
 *  @details This register provides voltage regulation information for the single data rate macros
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_ADRxx_VREGCTL2_r_t\n
 *   </td>
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
 *     <td width="30%"> @param vregrsvd2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vcntlselectret </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved for lab characterization only. This bit indicates
 *        which of the VREG replicas is selected by the VREG,
 *        when VCNTLSELECT is 0 the VCNTLREPL is selected and
 *        when 1 the VCNTLGATECTRL is selected. The output controlled
 *        by this bit is affected by the VCNTLRESETIN signal
 *        when it is asserted. When SYSRESET is asserted the
 *        output signal will become 1.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vcntlgatectrlret </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for lab characterization only. PFET strength
 *        control to the VREG DAC. This bus is affected by the
 *        PO_FENCE signal when it is asserted. When the RESET
 *        signal is asserted, the VCNTLREPLRET bus will assume
 *        a value of 1111. AKA BusA. This bus is connected to
 *        the VREG block, through a level shifter, also this
 *        signal is connected to the VREG register interface.
 *        This signal is sourced from the C800CLK domain. When
 *        VCNTLRESETIN is active or CE0TEOVERRIDE is active
 *        or CE0DLT is active then the VCNTLREPLRET bus is set
 *        to 0000.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vcntlreplret </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved for lab characterization only. Replica PFET
 *        strength control to the VREG DAC. This bus is affected
 *        by the PO_FENCE signal when it is asserted. When the
 *        RESET signal is asserted, the VCNTLREPLRET bus will
 *        assume a value of 1111. AKA BusA. This bus is connected
 *        to the VREG block, through a level shifter, also this
 *        signal is connected to the VREG register interface.
 *        This signal is sourced from the C800CLK domain. When
 *        VCNTLRESETIN is active or CE0TEOVERRIDE is active
 *        or CE0DLT is active then the VCNTLREPLRET bus is set
 *        to 0000.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      vregrsvd2                                 :  7;
     unsigned      vcntlselectret                            :  1;
     unsigned      vcntlgatectrlret                          :  4;
     unsigned      vcntlreplret                              :  4;
#else    /* Little Endian */
     unsigned      vcntlreplret                              :  4;
     unsigned      vcntlgatectrlret                          :  4;
     unsigned      vcntlselectret                            :  1;
     unsigned      vregrsvd2                                 :  7;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_CFG_SYSMEM_PHY_ADRxx_VREGCTL2_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_ADRxx_VREGCTL3_r_t
 *  @brief CFG_SYSMEM_PHY_ADRxx_VREGCTL3
 *  @details This register provides voltage regulation information for the single data rate macros
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_ADRxx_VREGCTL3_r_t\n
 *   </td>
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
 *     <td width="30%"> @param ecoa0cswitch </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vregrsvd3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vcntlselect </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for lab characterization only. This input
 *        bus is used for replacing the value of the SELECT
 *        output when the DIAG and WRREG are asserted. The value
 *        of this bus has to be stable before the WRREG signal
 *        is asserted. This signal is sampled continuously when
 *        the DIAG and WRREG are both active.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vcntldiag </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for lab characterization only. This active
 *        high signal turns on the diagnostic mode of the VREG
 *        control macro;in this mode, the VREG control will
 *        stop performing calibrations. It is required that
 *        when reading the VCNTLREPLET, VCNTLGATECTRLRET, VCNTLSETECTRET
 *        signals from the register interface the VCNTLDIAG
 *        signal must be active. Before the VCNTLWRREG can be
 *        asserted, the VCNTLDIAG signal should be active for
 *        a minimum of 500us when the memory clock is 800MHz
 *        or 1ms when the clock is 400MHz.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vcntlwrreg </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved for lab characterization only. When this
 *        active high signal is asserted and the DIAG signal
 *        is also asserted, the VCNTLREPL, VCNTLGATECNTL, and
 *        VCNTLSELECT buses will replace the current value of
 *        the REPL, GATECTRL, and SELECT outputs. This signal
 *        should be active for at least 2us when the memory
 *        clock is 800MHz or 4us when the memory clock is 400MHz.
 *        Once the DIAG signal is deasserted, the register or
 *        registers affected by this write will revert to their
 *        state before DIAG was asserted.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vcntlgatecntl </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for lab characterization only. This input
 *        bus is used for replacing the value of the VCNTLGATECNTL
 *        output when the VCNTLDIAG and ACNTLWRREG are asserted.
 *        The value of this bus has to be stable before the
 *        VCNTLWRREG signal is asserted. This bus is sampled
 *        continuously when the VCNTLDIAG and VCNTLWRREG are
 *        both active.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vcntlrepl </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved for lab characterization only. This input
 *        bus is used for replacing the value of the VCNTLREPL
 *        output when the VCNTLDIAG and ACNTLWRREG are asserted.
 *        The value of this bus has to be stable before the
 *        VCNTLWRREG signal is asserted. This bus is sampled
 *        continuously when the VCNTLDIAG and VCNTLWRREG are
 *        both active.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      ecoa0cswitch                              :  1;
     unsigned      vregrsvd3                                 :  4;
     unsigned      vcntlselect                               :  1;
     unsigned      vcntldiag                                 :  1;
     unsigned      vcntlwrreg                                :  1;
     unsigned      vcntlgatecntl                             :  4;
     unsigned      vcntlrepl                                 :  4;
#else    /* Little Endian */
     unsigned      vcntlrepl                                 :  4;
     unsigned      vcntlgatecntl                             :  4;
     unsigned      vcntlwrreg                                :  1;
     unsigned      vcntldiag                                 :  1;
     unsigned      vcntlselect                               :  1;
     unsigned      vregrsvd3                                 :  4;
     unsigned      ecoa0cswitch                              :  1;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_CFG_SYSMEM_PHY_ADRxx_VREGCTL3_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_WRLVLx_VREGCTL0_r_t
 *  @brief CFG_SYSMEM_PHY_WRLVLx_VREGCTL0
 *  @details This register provides voltage regulation information for the double data rate byte lane macros
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_WRLVLx_VREGCTL0_r_t\n
 *   </td>
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
 *     <td width="30%"> @param vregrsrvpin0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved for lab characterization only. Turns bandgap
 *        off.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vregchdyn </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Chicken switch - control loop replica to change loop
 *        gain. 00 = 0%, 01 = +15%, 10 = +30%, 11 = 45%
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vregchcml </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vregtestmux </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for lab characterization only. This selects
 *        the testmux output.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vregrange </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Configures the default width of the PFET transistor
 *        in UREG and UREGMASTER. 00 = 1.5V, 01 = 1.35V, 10
 *        = not used, 11 = 1.25V
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vregc </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 01100 = 0.992V See the section on voltage regulators
 *        for more information. Use of voltages beyond 1.1V
 *        will likely reduce the life span of the phy.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      vregrsrvpin0                              :  1;
     unsigned      vregchdyn                                 :  2;
     unsigned      vregchcml                                 :  2;
     unsigned      vregtestmux                               :  4;
     unsigned      vregrange                                 :  2;
     unsigned      vregc                                     :  5;
#else    /* Little Endian */
     unsigned      vregc                                     :  5;
     unsigned      vregrange                                 :  2;
     unsigned      vregtestmux                               :  4;
     unsigned      vregchcml                                 :  2;
     unsigned      vregchdyn                                 :  2;
     unsigned      vregrsrvpin0                              :  1;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_CFG_SYSMEM_PHY_WRLVLx_VREGCTL0_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_WRLVLx_VREGCTL1_r_t
 *  @brief CFG_SYSMEM_PHY_WRLVLx_VREGCTL1
 *  @details This register provides voltage regulation information for the double data rate byte lane macros
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_WRLVLx_VREGCTL1_r_t\n
 *   </td>
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
 *     <td width="30%"> @param vregrsrvpin1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param uregrsrvctrl </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved for lab characterization only. Bit 2 turns
 *        off slew control in the UREG. Bits 1,0 not used.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vregrsvd1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      vregrsrvpin1                              :  5;
     unsigned      uregrsrvctrl                              :  3;
     unsigned      vregrsvd1                                 :  8;
#else    /* Little Endian */
     unsigned      vregrsvd1                                 :  8;
     unsigned      uregrsrvctrl                              :  3;
     unsigned      vregrsrvpin1                              :  5;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_CFG_SYSMEM_PHY_WRLVLx_VREGCTL1_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_WRLVLx_VREGCTL2_r_t
 *  @brief CFG_SYSMEM_PHY_WRLVLx_VREGCTL2
 *  @details This register provides voltage regulation information for the double data rate byte lane macros
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_WRLVLx_VREGCTL2_r_t\n
 *   </td>
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
 *     <td width="30%"> @param vregrsvd2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vcntlselectret </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved for lab characterization only. This bit indicates
 *        which of the VREG replicas is selected by the VREG,
 *        when VCNTLSELECT is 0 the VCNTLREPL is selected and
 *        when 1 the VCNTLGATECTRL is selected. The output controlled
 *        by this bit is affected by the VCNTLRESETIN signal
 *        when it is asserted. When SYSRESET is asserted the
 *        output signal will become 1.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vcntlgatectrlret </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for lab characterization only. PFET strength
 *        control to the VREG DAC. This bus is affected by the
 *        PO_FENCE signal when it is asserted. When the RESET
 *        signal is asserted, the VCNTLREPLRET bus will assume
 *        a value of 1111. AKA BusA. This bus is connected to
 *        the VREG block, through a level shifter, also this
 *        signal is connected to the VREG register interface.
 *        This signal is sourced from the C800CLK domain. When
 *        VCNTLRESETIN is active or CE0TEOVERRIDE is active
 *        or CE0DLT is active then the VCNTLREPLRET bus is set
 *        to 0000.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vcntlreplret </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved for lab characterization only. Replica PFET
 *        strength control to the VREG DAC. This bus is affected
 *        by the PO_FENCE signal when it is asserted. When the
 *        RESET signal is asserted, the VCNTLREPLRET bus will
 *        assume a value of 1111. AKA BusA. This bus is connected
 *        to the VREG block, through a level shifter, also this
 *        signal is connected to the VREG register interface.
 *        This signal is sourced from the C800CLK domain. When
 *        VCNTLRESETIN is active or CE0TEOVERRIDE is active
 *        or CE0DLT is active then the VCNTLREPLRET bus is set
 *        to 0000.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      vregrsvd2                                 :  7;
     unsigned      vcntlselectret                            :  1;
     unsigned      vcntlgatectrlret                          :  4;
     unsigned      vcntlreplret                              :  4;
#else    /* Little Endian */
     unsigned      vcntlreplret                              :  4;
     unsigned      vcntlgatectrlret                          :  4;
     unsigned      vcntlselectret                            :  1;
     unsigned      vregrsvd2                                 :  7;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_CFG_SYSMEM_PHY_WRLVLx_VREGCTL2_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_WRLVLx_VREGCTL3_r_t
 *  @brief CFG_SYSMEM_PHY_WRLVLx_VREGCTL3
 *  @details This register provides voltage regulation information for the double data rate byte lane macros
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_WRLVLx_VREGCTL3_r_t\n
 *   </td>
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
 *     <td width="30%"> @param ecoa0cswitch </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Chicken switch to IE not OE/delay line enable control.
 *        Turns off the switching of CML stages in IO. When
 *        using this mode, the user must also enable the IE
 *        DQS0&1 Static Override bits in the RDCAL Master Control
 *        IE/MCTERM BYTE Register.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vregrsvd3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vcntlselect </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for lab characterization only. This input
 *        bus is used for replacing the value of the SELECT
 *        output when the DIAG and WRREG are asserted. The value
 *        of this bus has to be stable before the WRREG signal
 *        is asserted. This signal is sampled continuously when
 *        the DIAG and WRREG are both active.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vcntldiag </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for lab characterization only. This active
 *        high signal turns on the diagnostic mode of the VREG
 *        control macro;in this mode, the VREG control will
 *        stop performing calibrations. It is required that
 *        when reading the VCNTLREPLET, VCNTLGATECTRLRET, VCNTLSETECTRET
 *        signals from the register interface the VCNTLDIAG
 *        signal must be active. Before the VCNTLWRREG can be
 *        asserted, the VCNTLDIAG signal should be active for
 *        a minimum of 500us when the memory clock is 800MHz
 *        or 1ms when the clock is 400MHz.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vcntlwrreg </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved for lab characterization only. When this
 *        active high signal is asserted and the DIAG signal
 *        is also asserted, the VCNTLREPL, VCNTLGATECNTL, and
 *        VCNTLSELECT buses will replace the current value of
 *        the REPL, GATECTRL, and SELECT outputs. This signal
 *        should be active for at least 2us when the memory
 *        clock is 800MHz or 4us when the memory clock is 400MHz.
 *        Once the DIAG signal is deasserted, the register or
 *        registers affected by this write will revert to their
 *        state before DIAG was asserted.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vcntlgatecntl </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for lab characterization only. This input
 *        bus is used for replacing the value of the VCNTLGATECNTL
 *        output when the VCNTLDIAG and ACNTLWRREG are asserted.
 *        The value of this bus has to be stable before the
 *        VCNTLWRREG signal is asserted. This bus is sampled
 *        continuously when the VCNTLDIAG and VCNTLWRREG are
 *        both active.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vcntlrepl </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved for lab characterization only. This input
 *        bus is used for replacing the value of the VCNTLREPL
 *        output when the VCNTLDIAG and ACNTLWRREG are asserted.
 *        The value of this bus has to be stable before the
 *        VCNTLWRREG signal is asserted. This bus is sampled
 *        continuously when the VCNTLDIAG and VCNTLWRREG are
 *        both active.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      ecoa0cswitch                              :  1;
     unsigned      vregrsvd3                                 :  4;
     unsigned      vcntlselect                               :  1;
     unsigned      vcntldiag                                 :  1;
     unsigned      vcntlwrreg                                :  1;
     unsigned      vcntlgatecntl                             :  4;
     unsigned      vcntlrepl                                 :  4;
#else    /* Little Endian */
     unsigned      vcntlrepl                                 :  4;
     unsigned      vcntlgatecntl                             :  4;
     unsigned      vcntlwrreg                                :  1;
     unsigned      vcntldiag                                 :  1;
     unsigned      vcntlselect                               :  1;
     unsigned      vregrsvd3                                 :  4;
     unsigned      ecoa0cswitch                              :  1;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_CFG_SYSMEM_PHY_WRLVLx_VREGCTL3_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_MSTRCTLCFG4_r_t
 *  @brief CFG_SYSMEM_PHY_MSTRCTLCFG4
 *  @details This register provides voltage regulation information for the single data rate macros
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_MSTRCTLCFG4_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 20 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vreg_cfgmode_a3 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> 000 = Vreg output will be ~85% of Vdd, 001 = Vreg
 *        output will be ~90% of Vdd, 010 = Vreg output will
 *        be ~95% of Vdd, 011 = Vreg output will be ~Vdd, 100
 *        = Vreg output will be ~107% of Vdd, 101 = Vreg output
 *        will be ~114% of Vdd, 110 = Vreg output will be ~122%
 *        of Vdd, 111 = Vreg output will be ~132% of Vdd.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vreg_cfgmode_a2 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> 000 = Vreg output will be ~85% of Vdd, 001 = Vreg
 *        output will be ~90% of Vdd, 010 = Vreg output will
 *        be ~95% of Vdd, 011 = Vreg output will be ~Vdd, 100
 *        = Vreg output will be ~107% of Vdd, 101 = Vreg output
 *        will be ~114% of Vdd, 110 = Vreg output will be ~122%
 *        of Vdd, 111 = Vreg output will be ~132% of Vdd.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vreg_cfgmode_a1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> 000 = Vreg output will be ~85% of Vdd, 001 = Vreg
 *        output will be ~90% of Vdd, 010 = Vreg output will
 *        be ~95% of Vdd, 011 = Vreg output will be ~Vdd, 100
 *        = Vreg output will be ~107% of Vdd, 101 = Vreg output
 *        will be ~114% of Vdd, 110 = Vreg output will be ~122%
 *        of Vdd, 111 = Vreg output will be ~132% of Vdd.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vreg_cfgmode_a0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 000 = Vreg output will be ~85% of Vdd, 001 = Vreg
 *        output will be ~90% of Vdd, 010 = Vreg output will
 *        be ~95% of Vdd, 011 = Vreg output will be ~Vdd, 100
 *        = Vreg output will be ~107% of Vdd, 101 = Vreg output
 *        will be ~114% of Vdd, 110 = Vreg output will be ~122%
 *        of Vdd, 111 = Vreg output will be ~132% of Vdd.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 20;
     unsigned      vreg_cfgmode_a3                           :  3;
     unsigned      vreg_cfgmode_a2                           :  3;
     unsigned      vreg_cfgmode_a1                           :  3;
     unsigned      vreg_cfgmode_a0                           :  3;
#else    /* Little Endian */
     unsigned      vreg_cfgmode_a0                           :  3;
     unsigned      vreg_cfgmode_a1                           :  3;
     unsigned      vreg_cfgmode_a2                           :  3;
     unsigned      vreg_cfgmode_a3                           :  3;
     unsigned      reserved0                                 : 20;
#endif
} ncp_phy_CFG_SYSMEM_PHY_MSTRCTLCFG4_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_MSTRCTLVREGCFG_r_t
 *  @brief CFG_SYSMEM_PHY_MSTRCTLVREGCFG
 *  @details This register provides voltage regulation information for the data path macros
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_MSTRCTLVREGCFG_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 29 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vreg_cfgmode </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 000 = Vreg output will be ~85% of Vdd, 001 = Vreg
 *        output will be ~90% of Vdd, 010 = Vreg output will
 *        be ~95% of Vdd, 011 = Vreg output will be ~Vdd, 100
 *        = Vreg output will be ~107% of Vdd, 101 = Vreg output
 *        will be ~114% of Vdd, 110 = Vreg output will be ~122%
 *        of Vdd, 111 = Vreg output will be ~132% of Vdd.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 29;
     unsigned      vreg_cfgmode                              :  3;
#else    /* Little Endian */
     unsigned      vreg_cfgmode                              :  3;
     unsigned      reserved0                                 : 29;
#endif
} ncp_phy_CFG_SYSMEM_PHY_MSTRCTLVREGCFG_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_MSTRCTLCFG3_r_t
 *  @brief CFG_SYSMEM_PHY_MSTRCTLCFG3
 *  @details This register provides voltage regulation information for some of the data path macros
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_MSTRCTLCFG3_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 20 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vreg_cfgmode_d8 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> 000 = approximately standard Vdd voltage, 001-110
 *        = between standard Vdd and 1.15V, 111 = approximately
 *        1.15V
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vreg_cfgmode_d7 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> 000 = approximately standard Vdd voltage, 001-110
 *        = between standard Vdd and 1.15V, 111 = approximately
 *        1.15V
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vreg_cfgmode_d6 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> 000 = approximately standard Vdd voltage, 001-110
 *        = between standard Vdd and 1.15V, 111 = approximately
 *        1.15V
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vreg_cfgmode_d5 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 000 = approximately standard Vdd voltage, 001-110
 *        = between standard Vdd and 1.15V, 111 = approximately
 *        1.15V
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 20;
     unsigned      vreg_cfgmode_d8                           :  3;
     unsigned      vreg_cfgmode_d7                           :  3;
     unsigned      vreg_cfgmode_d6                           :  3;
     unsigned      vreg_cfgmode_d5                           :  3;
#else    /* Little Endian */
     unsigned      vreg_cfgmode_d5                           :  3;
     unsigned      vreg_cfgmode_d6                           :  3;
     unsigned      vreg_cfgmode_d7                           :  3;
     unsigned      vreg_cfgmode_d8                           :  3;
     unsigned      reserved0                                 : 20;
#endif
} ncp_phy_CFG_SYSMEM_PHY_MSTRCTLCFG3_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_MSTRCTLCFG2_r_t
 *  @brief CFG_SYSMEM_PHY_MSTRCTLCFG2
 *  @details This register provides voltage regulation information for the rest of the data path macros
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_MSTRCTLCFG2_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 17 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vreg_cfgmode_d4 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> 000 = approximately standard Vdd voltage, 001-110
 *        = between standard Vdd and 1.15V, 111 = approximately
 *        1.15V
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vreg_cfgmode_d3 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> 000 = approximately standard Vdd voltage, 001-110
 *        = between standard Vdd and 1.15V, 111 = approximately
 *        1.15V
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vreg_cfgmode_d2 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> 000 = approximately standard Vdd voltage, 001-110
 *        = between standard Vdd and 1.15V, 111 = approximately
 *        1.15V
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vreg_cfgmode_d1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> 000 = approximately standard Vdd voltage, 001-110
 *        = between standard Vdd and 1.15V, 111 = approximately
 *        1.15V
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vreg_cfgmode_d0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 000 = approximately standard Vdd voltage, 001-110
 *        = between standard Vdd and 1.15V, 111 = approximately
 *        1.15V
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 17;
     unsigned      vreg_cfgmode_d4                           :  3;
     unsigned      vreg_cfgmode_d3                           :  3;
     unsigned      vreg_cfgmode_d2                           :  3;
     unsigned      vreg_cfgmode_d1                           :  3;
     unsigned      vreg_cfgmode_d0                           :  3;
#else    /* Little Endian */
     unsigned      vreg_cfgmode_d0                           :  3;
     unsigned      vreg_cfgmode_d1                           :  3;
     unsigned      vreg_cfgmode_d2                           :  3;
     unsigned      vreg_cfgmode_d3                           :  3;
     unsigned      vreg_cfgmode_d4                           :  3;
     unsigned      reserved0                                 : 17;
#endif
} ncp_phy_CFG_SYSMEM_PHY_MSTRCTLCFG2_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_MSTRCTLCFG1_r_t
 *  @brief CFG_SYSMEM_PHY_MSTRCTLCFG1
 *  @details This register provides the output enable controls for DQ, DQS and dram CLK
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_MSTRCTLCFG1_r_t\n
 *   </td>
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
 *     <td width="30%"> @param rd_fifo_auto_rst_chknsw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Chicken Switch. 0 = allow RD FIFO to auto reset pointers
 *        on rank switch, 1 = prevent RD FIFO auto reset of
 *        pointers on rank switch.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rank_override </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Rank override mode. (virtual 2 cycle gap) 0 = PHY
 *        will use rank provided to MASTERCNTL on RANK_I, qualified
 *        with CMD_VALID for read/write commands, 1 = PHY will
 *        use rank provided in rank_override_value field of
 *        this register for ALL read/write commands. When rank_override
 *        is enabled, the PHY will calculate new delay settings
 *        for the first cmd of each type (once for read, once
 *        for write). Further updates of the delay settings
 *        will not occur because the PHY will only see the overridden
 *        rank value, and therefore not see a rank switch.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rank_override_value </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Rank override value </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rd_n_cyc_gap </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Changes RD path behavior. 00 = 2 cycle gap switching,
 *        01 = 2.5 cycle gap (chicken switch intended for debug
 *        use), 10 = 3 cycle gap switching, 11 = do not use
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqs1_enamode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> 00 = coincident mode: in this mode the enable is asserted
 *        coincident with the leading edge of the first DQ/DQS
 *        bit and deasserted coincident with the trailing edge
 *        of the last DQ/DQS bit, 01 = quarter ahead/quarter
 *        behind: in this mode the enable is asserted a quarter
 *        of a memclk ahead of the leading edge of the first
 *        DQ/DQS bit and deasserted a quarter memclk behind
 *        the trailing edge of the last DQ/DQS bit, 10 = quarter
 *        ahead/half behind: in this mode the enable is asserted
 *        a quarter of a memclk ahead of the leading edge of
 *        the first DQ/DQS bit and deasserted half of a memclk
 *        behind the trailing edge of the last DQ/DQS bit
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqs1_coremode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> 0 = DCPIN is configured to be a DQ, 1 = DCPIN is configured
 *        to be a DQS/MEMCLK
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqs0_enamode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> 00 = coincident mode: in this mode the enable is asserted
 *        coincident with the leading edge of the first DQ/DQS
 *        bit and deasserted coincident with the trailing edge
 *        of the last DQ/DQS bit, 01 = quarter ahead/quarter
 *        behind: in this mode the enable is asserted a quarter
 *        of a memclk ahead of the leading edge of the first
 *        DQ/DQS bit and deasserted a quarter memclk behind
 *        the trailing edge of the last DQ/DQS bit, 10 = quarter
 *        ahead/half behind: in this mode the enable is asserted
 *        a quarter of a memclk ahead of the leading edge of
 *        the first DQ/DQS bit and deasserted half of a memclk
 *        behind the trailing edge of the last DQ/DQS bit
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqs0_coremode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> 0 = DCPIN is configured to be a DQ, 1 = DCPIN is configured
 *        to be a DQS/MEMCLK
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq_enamode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> 00 = coincident mode: in this mode the enable is asserted
 *        coincident with the leading edge of the first DQ/DQS
 *        bit and deasserted coincident with the trailing edge
 *        of the last DQ/DQS bit, 01 = quarter ahead/quarter
 *        behind: in this mode the enable is asserted a quarter
 *        of a memclk ahead of the leading edge of the first
 *        DQ/DQS bit and deasserted a quarter memclk behind
 *        the trailing edge of the last DQ/DQS bit, 10 = quarter
 *        ahead/half behind: in this mode the enable is asserted
 *        a quarter of a memclk ahead of the leading edge of
 *        the first DQ/DQS bit and deasserted half of a memclk
 *        behind the trailing edge of the last DQ/DQS bit
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq_coremode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 0 = DCPIN is configured to be a DQ, 1 = DCPIN is configured
 *        to be a DQS/MEMCLK
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      rd_fifo_auto_rst_chknsw                   :  1;
     unsigned      rank_override                             :  1;
     unsigned      rank_override_value                       :  3;
     unsigned      rd_n_cyc_gap                              :  2;
     unsigned      dqs1_enamode                              :  2;
     unsigned      dqs1_coremode                             :  1;
     unsigned      dqs0_enamode                              :  2;
     unsigned      dqs0_coremode                             :  1;
     unsigned      dq_enamode                                :  2;
     unsigned      dq_coremode                               :  1;
#else    /* Little Endian */
     unsigned      dq_coremode                               :  1;
     unsigned      dq_enamode                                :  2;
     unsigned      dqs0_coremode                             :  1;
     unsigned      dqs0_enamode                              :  2;
     unsigned      dqs1_coremode                             :  1;
     unsigned      dqs1_enamode                              :  2;
     unsigned      rd_n_cyc_gap                              :  2;
     unsigned      rank_override_value                       :  3;
     unsigned      rank_override                             :  1;
     unsigned      rd_fifo_auto_rst_chknsw                   :  1;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_CFG_SYSMEM_PHY_MSTRCTLCFG1_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_MSTRCTLCFG0_r_t
 *  @brief CFG_SYSMEM_PHY_MSTRCTLCFG0
 *  @details DDR mode, rank pairing, chicken switches
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_MSTRCTLCFG0_r_t\n
 *   </td>
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
 *     <td width="30%"> @param ureg_dvdd_rnge1_chknsw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Chicken Switch. 0 = normal operation, 1 = adds more
 *        PFET strength.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ureg_dvdd_rnge0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> 0 = normal operation, 1 = adds more PFET strength
 *        at lower DVDD range. When DVDD is at 1.35V this pin
 *        should be set high.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ureg_rst_chknsw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Chicken Switch. Unsupported </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param async_2_cyc_chknsw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Chicken Switch. 0 = allow 2 cycle async delay switching
 *        on writes, 1 = prevent 2 cycle async delay switching
 *        on writes.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rank_dly_chknsw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Chicken Switch. 0 = allow rank delay switching on
 *        writes, 1 = DO NOT allow rank delay switching on writes.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rank_map_mode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Defines rank pairing for write leveling and read per
 *        bit DQ deskew. 00 = 0/4 1/5 2/6 3/7, 01 = 0/2 1/3
 *        4/6 5/7, 10 = 0/1 2/3 4/5 6/7
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mem_dev_mode </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Device data width on a rank basis. Bit 0 is rank 0
 *        up to bit 7 is rank 7. 0 = x4 width, 1 = x8 width.
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      ureg_dvdd_rnge1_chknsw                    :  1;
     unsigned      ureg_dvdd_rnge0                           :  1;
     unsigned      ureg_rst_chknsw                           :  1;
     unsigned      async_2_cyc_chknsw                        :  1;
     unsigned      rank_dly_chknsw                           :  1;
     unsigned      rank_map_mode                             :  2;
     unsigned      reserved1                                 :  1;
     unsigned      mem_dev_mode                              :  8;
#else    /* Little Endian */
     unsigned      mem_dev_mode                              :  8;
     unsigned      reserved1                                 :  1;
     unsigned      rank_map_mode                             :  2;
     unsigned      rank_dly_chknsw                           :  1;
     unsigned      async_2_cyc_chknsw                        :  1;
     unsigned      ureg_rst_chknsw                           :  1;
     unsigned      ureg_dvdd_rnge0                           :  1;
     unsigned      ureg_dvdd_rnge1_chknsw                    :  1;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_CFG_SYSMEM_PHY_MSTRCTLCFG0_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_MSTRCTLEMSK_r_t
 *  @brief CFG_SYSMEM_PHY_MSTRCTLEMSK
 *  @details Hardware assist error mask
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_MSTRCTLEMSK_r_t\n
 *   </td>
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
 *     <td width="30%"> @param rd_cal_err_msk </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Read calibration algorithm error mask </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wr_lvl_err_msk </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Write leveling algorithm error mask </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rd_dly_err_msk </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Read delay algorithm error mask </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmd_dly_err_msk </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Address/command delay algorithm error mask </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpc_err_msk </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Clock period calculator algorithm error mask </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 27;
     unsigned      rd_cal_err_msk                            :  1;
     unsigned      wr_lvl_err_msk                            :  1;
     unsigned      rd_dly_err_msk                            :  1;
     unsigned      cmd_dly_err_msk                           :  1;
     unsigned      cpc_err_msk                               :  1;
#else    /* Little Endian */
     unsigned      cpc_err_msk                               :  1;
     unsigned      cmd_dly_err_msk                           :  1;
     unsigned      rd_dly_err_msk                            :  1;
     unsigned      wr_lvl_err_msk                            :  1;
     unsigned      rd_cal_err_msk                            :  1;
     unsigned      reserved0                                 : 27;
#endif
} ncp_phy_CFG_SYSMEM_PHY_MSTRCTLEMSK_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_MSTRCTLERRS_r_t
 *  @brief CFG_SYSMEM_PHY_MSTRCTLERRS
 *  @details Hardware assist errors
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_MSTRCTLERRS_r_t\n
 *   </td>
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
 *     <td width="30%"> @param rd_cal_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Read calibration algorithm error </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wr_lvl_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Write leveling algorithm error </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rd_dly_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Read delay algorithm error </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmd_dly_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Address/command delay algorithm error </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpc_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Clock period calculator algorithm error </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 27;
     unsigned      rd_cal_err                                :  1;
     unsigned      wr_lvl_err                                :  1;
     unsigned      rd_dly_err                                :  1;
     unsigned      cmd_dly_err                               :  1;
     unsigned      cpc_err                                   :  1;
#else    /* Little Endian */
     unsigned      cpc_err                                   :  1;
     unsigned      cmd_dly_err                               :  1;
     unsigned      rd_dly_err                                :  1;
     unsigned      wr_lvl_err                                :  1;
     unsigned      rd_cal_err                                :  1;
     unsigned      reserved0                                 : 27;
#endif
} ncp_phy_CFG_SYSMEM_PHY_MSTRCTLERRS_r_t;

/*! @struct ncp_phy_phy_error2_r_t
 *  @brief PHY Error Status Register 2
 *  @details PHY generated errors
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_phy_error2_r_t\n
 *   </td>
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
 *     <td width="30%"> @param cpc_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Clock period calculator algorithm error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmd_dly_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address/command delay algorithm error. </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 30;
     unsigned      cpc_err                                   :  1;
     unsigned      cmd_dly_err                               :  1;
#else    /* Little Endian */
     unsigned      cmd_dly_err                               :  1;
     unsigned      cpc_err                                   :  1;
     unsigned      reserved0                                 : 30;
#endif
} ncp_phy_phy_error2_r_t;

/*! @struct ncp_phy_phy_error1_r_t
 *  @brief PHY Error Status Register 1
 *  @details PHY generated errors
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_phy_error1_r_t\n
 *   </td>
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
 *     <td width="30%"> @param rddlya_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Read delay algorithm error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvla_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Write leveling algorithm error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdcala_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Read calibration algorithm error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_err </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Per byte lane write leveling error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rddly_err_8_5 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Per byte lane read delay error. </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      rddlya_err                                :  1;
     unsigned      wrlvla_err                                :  1;
     unsigned      rdcala_err                                :  1;
     unsigned      wrlvl_err                                 :  9;
     unsigned      rddly_err_8_5                             :  4;
#else    /* Little Endian */
     unsigned      rddly_err_8_5                             :  4;
     unsigned      wrlvl_err                                 :  9;
     unsigned      rdcala_err                                :  1;
     unsigned      wrlvla_err                                :  1;
     unsigned      rddlya_err                                :  1;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_phy_error1_r_t;

/*! @struct ncp_phy_phy_error0_r_t
 *  @brief PHY Error Status Register 0
 *  @details PHY generated errors
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_phy_error0_r_t\n
 *   </td>
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
 *     <td width="30%"> @param rddly_err_4_0 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Per byte lane read delay error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdcal_err </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Per byte lane read calibration error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mctrl_fsm_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> DDR32MASTERCNTL00 FSM error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param phy_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Any PHY error occurred. </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      rddly_err_4_0                             :  5;
     unsigned      rdcal_err                                 :  9;
     unsigned      mctrl_fsm_err                             :  1;
     unsigned      phy_err                                   :  1;
#else    /* Little Endian */
     unsigned      phy_err                                   :  1;
     unsigned      mctrl_fsm_err                             :  1;
     unsigned      rdcal_err                                 :  9;
     unsigned      rddly_err_4_0                             :  5;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_phy_error0_r_t;

/*! @struct ncp_phy_phy_error2_force_r_t
 *  @brief PHY Error Force Register 2
 *  @details This register forces PHY errors
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_phy_error2_force_r_t\n
 *   </td>
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
 *     <td width="30%"> @param frc_cpc_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Force cpc_err </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param frc_cmd_dly_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Force cmd_dly_err </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 30;
     unsigned      frc_cpc_err                               :  1;
     unsigned      frc_cmd_dly_err                           :  1;
#else    /* Little Endian */
     unsigned      frc_cmd_dly_err                           :  1;
     unsigned      frc_cpc_err                               :  1;
     unsigned      reserved0                                 : 30;
#endif
} ncp_phy_phy_error2_force_r_t;

/*! @struct ncp_phy_phy_error1_force_r_t
 *  @brief PHY Error Force Register 1
 *  @details This register forces PHY errors
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_phy_error1_force_r_t\n
 *   </td>
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
 *     <td width="30%"> @param frc_rddlya_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Force rddlya_err </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param frc_wrlvla_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Force wrlvla_err </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param frc_rdcala_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Force rdcala_err </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param frc_wrlvl_err </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Force wrlvl_err </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param frc_rddly_err_9_5 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Force rddly_err_9_5 </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      frc_rddlya_err                            :  1;
     unsigned      frc_wrlvla_err                            :  1;
     unsigned      frc_rdcala_err                            :  1;
     unsigned      frc_wrlvl_err                             :  9;
     unsigned      frc_rddly_err_9_5                         :  4;
#else    /* Little Endian */
     unsigned      frc_rddly_err_9_5                         :  4;
     unsigned      frc_wrlvl_err                             :  9;
     unsigned      frc_rdcala_err                            :  1;
     unsigned      frc_wrlvla_err                            :  1;
     unsigned      frc_rddlya_err                            :  1;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_phy_error1_force_r_t;

/*! @struct ncp_phy_phy_error0_force_r_t
 *  @brief PHY Error Force Register 0
 *  @details This register forces PHY errors
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_phy_error0_force_r_t\n
 *   </td>
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
 *     <td width="30%"> @param frc_rddly_err_4_0 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Force rddly_err_4_0 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param frc_rdcal_err </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Force rdcal_err </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param frc_mctrl_fsm_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Force mctrl_fsm_err </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param frc_phy_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Force phy_err </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      frc_rddly_err_4_0                         :  5;
     unsigned      frc_rdcal_err                             :  9;
     unsigned      frc_mctrl_fsm_err                         :  1;
     unsigned      frc_phy_err                               :  1;
#else    /* Little Endian */
     unsigned      frc_phy_err                               :  1;
     unsigned      frc_mctrl_fsm_err                         :  1;
     unsigned      frc_rdcal_err                             :  9;
     unsigned      frc_rddly_err_4_0                         :  5;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_phy_error0_force_r_t;

/*! @struct ncp_phy_phy_ctl6_r_t
 *  @brief PHY Control Register 6
 *  @details This register contains fields that control the PHY setup
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_phy_ctl6_r_t\n
 *   </td>
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
 *     <td width="30%"> @param mode_1p2v_adr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Use 1.2V (instead of 1.5V) mode for the address and
 *        control buffers.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mode_1p2v_dat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Use 1.2V (instead of 1.5V) mode for the data buffers. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param imped_adr </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Impedence setting for the address and control pins. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param imped_dat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Impedence setting for the data pins (drive). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param imped_rcv </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Impedence setting for the data pins (receive). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cal_enb_adr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Enable the calibration cell for the address and control
 *        pins.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cal_enb_dat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Enable the calibration cell for the data pins (drive). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cal_enb_rcv </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Enable the calibration cell for the data pins (receive). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zcntl_enb_adr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Enable the ZCNTL cell for the address and control
 *        pins.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zcntl_enb_dp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Enable the ZCNTL cell for the data pins (drive). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zcntl_enb_rcv </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enable the ZCNTL cell for the data pins (receive). </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      mode_1p2v_adr                             :  1;
     unsigned      mode_1p2v_dat                             :  1;
     unsigned      imped_adr                                 :  2;
     unsigned      imped_dat                                 :  2;
     unsigned      imped_rcv                                 :  2;
     unsigned      reserved1                                 :  1;
     unsigned      cal_enb_adr                               :  1;
     unsigned      cal_enb_dat                               :  1;
     unsigned      cal_enb_rcv                               :  1;
     unsigned      reserved2                                 :  1;
     unsigned      zcntl_enb_adr                             :  1;
     unsigned      zcntl_enb_dp                              :  1;
     unsigned      zcntl_enb_rcv                             :  1;
#else    /* Little Endian */
     unsigned      zcntl_enb_rcv                             :  1;
     unsigned      zcntl_enb_dp                              :  1;
     unsigned      zcntl_enb_adr                             :  1;
     unsigned      reserved2                                 :  1;
     unsigned      cal_enb_rcv                               :  1;
     unsigned      cal_enb_dat                               :  1;
     unsigned      cal_enb_adr                               :  1;
     unsigned      reserved1                                 :  1;
     unsigned      imped_rcv                                 :  2;
     unsigned      imped_dat                                 :  2;
     unsigned      imped_adr                                 :  2;
     unsigned      mode_1p2v_dat                             :  1;
     unsigned      mode_1p2v_adr                             :  1;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_phy_ctl6_r_t;

/*! @struct ncp_phy_phy_ctl7_r_t
 *  @brief PHY Control Register 7
 *  @details This register contains fields that control the PHY setup
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_phy_ctl7_r_t\n
 *   </td>
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
 *     <td width="30%"> @param dqs_slew8 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> DQS slew control for byte lane 8. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqs_slew7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> DQS slew control for byte lane 7. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqs_slew6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> DQS slew control for byte lane 6. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqs_slew5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> DQS slew control for byte lane 5. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqs_slew4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DQS slew control for byte lane 4. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqs_slew3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> DQS slew control for byte lane 3. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqs_slew2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> DQS slew control for byte lane 2. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqs_slew1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> DQS slew control for byte lane 1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqs_slew0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> DQS slew control for byte lane 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rd_ptr_init </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Read pointer initialization value (must be setup prior
 *        to PHY reset).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wr_coming </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enable the write buffers (must be asserted at least
 *        1 clock before the write and remain high for the entire
 *        write cycle).
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 19;
     unsigned      dqs_slew8                                 :  1;
     unsigned      dqs_slew7                                 :  1;
     unsigned      dqs_slew6                                 :  1;
     unsigned      dqs_slew5                                 :  1;
     unsigned      dqs_slew4                                 :  1;
     unsigned      dqs_slew3                                 :  1;
     unsigned      dqs_slew2                                 :  1;
     unsigned      dqs_slew1                                 :  1;
     unsigned      dqs_slew0                                 :  1;
     unsigned      rd_ptr_init                               :  3;
     unsigned      wr_coming                                 :  1;
#else    /* Little Endian */
     unsigned      wr_coming                                 :  1;
     unsigned      rd_ptr_init                               :  3;
     unsigned      dqs_slew0                                 :  1;
     unsigned      dqs_slew1                                 :  1;
     unsigned      dqs_slew2                                 :  1;
     unsigned      dqs_slew3                                 :  1;
     unsigned      dqs_slew4                                 :  1;
     unsigned      dqs_slew5                                 :  1;
     unsigned      dqs_slew6                                 :  1;
     unsigned      dqs_slew7                                 :  1;
     unsigned      dqs_slew8                                 :  1;
     unsigned      reserved0                                 : 19;
#endif
} ncp_phy_phy_ctl7_r_t;

/*! @struct ncp_phy_phy_ctl8_r_t
 *  @brief PHY Control Register 8
 *  @details This register contains fields that control the PHY setup
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_phy_ctl8_r_t\n
 *   </td>
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
 *     <td width="30%"> @param dq_vref0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> DQ VREF control for byte lane 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq_slew8 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> DQ slew control for byte lane 8. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq_slew7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> DQ slew control for byte lane 7. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq_slew6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> DQ slew control for byte lane 6. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq_slew5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DQ slew control for byte lane 5. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq_slew4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> DQ slew control for byte lane 4. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq_slew3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> DQ slew control for byte lane 3. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq_slew2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> DQ slew control for byte lane 2. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq_slew1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> DQ slew control for byte lane 1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq_slew0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> DQ slew control for byte lane 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param adr16_1_slew </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> ADR16_1 slew control. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param adr16_0_slew </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> ADR16_0 slew control. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param adr12_slew </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> ADR12 slew control. </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      dq_vref0                                  :  4;
     unsigned      dq_slew8                                  :  1;
     unsigned      dq_slew7                                  :  1;
     unsigned      dq_slew6                                  :  1;
     unsigned      dq_slew5                                  :  1;
     unsigned      dq_slew4                                  :  1;
     unsigned      dq_slew3                                  :  1;
     unsigned      dq_slew2                                  :  1;
     unsigned      dq_slew1                                  :  1;
     unsigned      dq_slew0                                  :  1;
     unsigned      adr16_1_slew                              :  1;
     unsigned      adr16_0_slew                              :  1;
     unsigned      adr12_slew                                :  1;
#else    /* Little Endian */
     unsigned      adr12_slew                                :  1;
     unsigned      adr16_0_slew                              :  1;
     unsigned      adr16_1_slew                              :  1;
     unsigned      dq_slew0                                  :  1;
     unsigned      dq_slew1                                  :  1;
     unsigned      dq_slew2                                  :  1;
     unsigned      dq_slew3                                  :  1;
     unsigned      dq_slew4                                  :  1;
     unsigned      dq_slew5                                  :  1;
     unsigned      dq_slew6                                  :  1;
     unsigned      dq_slew7                                  :  1;
     unsigned      dq_slew8                                  :  1;
     unsigned      dq_vref0                                  :  4;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_phy_ctl8_r_t;

/*! @struct ncp_phy_phy_ctl9_r_t
 *  @brief PHY Control Register 9
 *  @details This register contains fields that control the PHY setup
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_phy_ctl9_r_t\n
 *   </td>
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
 *     <td width="30%"> @param dq_vref4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> DQ VREF control for byte lane 4. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq_vref3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DQ VREF control for byte lane 3. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq_vref2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> DQ VREF control for byte lane 2. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq_vref1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DQ VREF control for byte lane 1. </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      dq_vref4                                  :  4;
     unsigned      dq_vref3                                  :  4;
     unsigned      dq_vref2                                  :  4;
     unsigned      dq_vref1                                  :  4;
#else    /* Little Endian */
     unsigned      dq_vref1                                  :  4;
     unsigned      dq_vref2                                  :  4;
     unsigned      dq_vref3                                  :  4;
     unsigned      dq_vref4                                  :  4;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_phy_ctl9_r_t;

/*! @struct ncp_phy_phy_ctl10_r_t
 *  @brief PHY Control Register 10
 *  @details This register contains fields that control the PHY setup
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_phy_ctl10_r_t\n
 *   </td>
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
 *     <td width="30%"> @param dq_vref8 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> DQ VREF control for byte lane 8. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq_vref7 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DQ VREF control for byte lane 7. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq_vref6 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> DQ VREF control for byte lane 6. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq_vref5 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DQ VREF control for byte lane 5. </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      dq_vref8                                  :  4;
     unsigned      dq_vref7                                  :  4;
     unsigned      dq_vref6                                  :  4;
     unsigned      dq_vref5                                  :  4;
#else    /* Little Endian */
     unsigned      dq_vref5                                  :  4;
     unsigned      dq_vref6                                  :  4;
     unsigned      dq_vref7                                  :  4;
     unsigned      dq_vref8                                  :  4;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_phy_ctl10_r_t;


/*
 * NOTE!!!!
 * The following definitions are specific to the TREEMEM PHY.
 * These have been cut'n'pasted from the treemem header files,
 * instead of including a whole 'nother (mostly duplicate)
 * header file
 */


/*! @struct ncp_phy_phy_ctl2_r_t
 *  @brief PHY Control Register 2
 *  @details This register contains fields that control the PHY setup
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_phy_ctl2_r_t\n
 *   </td>
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
 *     <td width="30%"> @param mode_1p2v_adr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Use 1.2V (instead of 1.5V) mode for the address and
 *        control buffers.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mode_1p2v_dat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Use 1.2V (instead of 1.5V) mode for the data buffers. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param imped_adr </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Impedence setting for the address and control pins. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param imped_dat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Impedence setting for the data pins (drive). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param imped_rcv </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Impedence setting for the data pins (receive). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cal_enb_adr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Enable the calibration cell for the address and control
 *        pins.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cal_enb_dat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Enable the calibration cell for the data pins (drive). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cal_enb_rcv </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Enable the calibration cell for the data pins (receive). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zcntl_enb_adr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Enable the ZCNTL cell for the address and control
 *        pins.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zcntl_enb_dp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Enable the ZCNTL cell for the data pins (drive). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zcntl_enb_rcv </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enable the ZCNTL cell for the data pins (receive). </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      mode_1p2v_adr                             :  1;
     unsigned      mode_1p2v_dat                             :  1;
     unsigned      imped_adr                                 :  2;
     unsigned      imped_dat                                 :  2;
     unsigned      imped_rcv                                 :  2;
     unsigned      reserved1                                 :  1;
     unsigned      cal_enb_adr                               :  1;
     unsigned      cal_enb_dat                               :  1;
     unsigned      cal_enb_rcv                               :  1;
     unsigned      reserved2                                 :  1;
     unsigned      zcntl_enb_adr                             :  1;
     unsigned      zcntl_enb_dp                              :  1;
     unsigned      zcntl_enb_rcv                             :  1;
#else    /* Little Endian */
     unsigned      zcntl_enb_rcv                             :  1;
     unsigned      zcntl_enb_dp                              :  1;
     unsigned      zcntl_enb_adr                             :  1;
     unsigned      reserved2                                 :  1;
     unsigned      cal_enb_rcv                               :  1;
     unsigned      cal_enb_dat                               :  1;
     unsigned      cal_enb_adr                               :  1;
     unsigned      reserved1                                 :  1;
     unsigned      imped_rcv                                 :  2;
     unsigned      imped_dat                                 :  2;
     unsigned      imped_adr                                 :  2;
     unsigned      mode_1p2v_dat                             :  1;
     unsigned      mode_1p2v_adr                             :  1;
     unsigned      reserved0                                 : 16;
#endif
} ncp_phy_phy_ctl2_r_t;

/*! @struct ncp_phy_phy_ctl3_r_t
 *  @brief PHY Control Register 3
 *  @details This register contains fields that control the PHY setup
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_phy_ctl3_r_t\n
 *   </td>
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
 *     <td width="30%"> @param dq_slew1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> DQ slew control for byte lane 1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq_slew0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DQ slew control for byte lane 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param adr16_slew </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> ADR16 slew control. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param adr12_slew </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> ADR12 slew control. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqs_slew1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> DQS slew control for byte lane 1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqs_slew0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> DQS slew control for byte lane 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rd_ptr_init </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Read pointer initialization value (must be setup prior
 *        to PHY reset).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wr_coming </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enable the write buffers (must be asserted at least
 *        1 clock before the write and remain high for the entire
 *        write cycle).
 *   </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 22;
     unsigned      dq_slew1                                  :  1;
     unsigned      dq_slew0                                  :  1;
     unsigned      adr16_slew                                :  1;
     unsigned      adr12_slew                                :  1;
     unsigned      dqs_slew1                                 :  1;
     unsigned      dqs_slew0                                 :  1;
     unsigned      rd_ptr_init                               :  3;
     unsigned      wr_coming                                 :  1;
#else    /* Little Endian */
     unsigned      wr_coming                                 :  1;
     unsigned      rd_ptr_init                               :  3;
     unsigned      dqs_slew0                                 :  1;
     unsigned      dqs_slew1                                 :  1;
     unsigned      adr12_slew                                :  1;
     unsigned      adr16_slew                                :  1;
     unsigned      dq_slew0                                  :  1;
     unsigned      dq_slew1                                  :  1;
     unsigned      reserved0                                 : 22;
#endif
} ncp_phy_phy_ctl3_r_t;

/*! @struct ncp_phy_phy_ctl4_r_t
 *  @brief PHY Control Register 4
 *  @details This register contains fields that control the PHY setup
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_phy_ctl4_r_t\n
 *   </td>
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
 *     <td width="30%"> @param dq_vref1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> DQ VREF control for byte lane 1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq_vref0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DQ VREF control for byte lane 0. </td>
 * </tr>
 * </table>
 */
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      dq_vref1                                  :  4;
     unsigned      dq_vref0                                  :  4;
#else    /* Little Endian */
     unsigned      dq_vref0                                  :  4;
     unsigned      dq_vref1                                  :  4;
     unsigned      reserved0                                 : 24;
#endif
} ncp_phy_phy_ctl4_r_t;



/*! @struct ncp_phy_phy_error_r_t
 *  @brief PHY Error Status Register
 *  @details PHY generated errors
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_phy_error_r_t\n
 *   </td>
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
 *     <td width="30%"> @param cpc_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Clock period calculator algorithm error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmd_dly_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Address/command delay algorithm error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rddlya_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Read delay algorithm error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvla_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Write leveling algorithm error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdcala_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Read calibration algorithm error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_err </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Per byte lane write leveling error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rddly_err </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Per byte lane read delay error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdcal_err </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Per byte lane read calibration error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mctrl_fsm_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> DDR32MASTERCNTL00 FSM error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param phy_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Any PHY error occurred. </td>
 * </tr>
 * </table>
 * Applies to: v1
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 19;
     unsigned      cpc_err                                   :  1;
     unsigned      cmd_dly_err                               :  1;
     unsigned      rddlya_err                                :  1;
     unsigned      wrlvla_err                                :  1;
     unsigned      rdcala_err                                :  1;
     unsigned      wrlvl_err                                 :  2;
     unsigned      rddly_err                                 :  2;
     unsigned      rdcal_err                                 :  2;
     unsigned      mctrl_fsm_err                             :  1;
     unsigned      phy_err                                   :  1;
#else    /* Little Endian */
     unsigned      phy_err                                   :  1;
     unsigned      mctrl_fsm_err                             :  1;
     unsigned      rdcal_err                                 :  2;
     unsigned      rddly_err                                 :  2;
     unsigned      wrlvl_err                                 :  2;
     unsigned      rdcala_err                                :  1;
     unsigned      wrlvla_err                                :  1;
     unsigned      rddlya_err                                :  1;
     unsigned      cmd_dly_err                               :  1;
     unsigned      cpc_err                                   :  1;
     unsigned      reserved0                                 : 19;
#endif
} ncp_phy_phy_error_r_t;


#ifdef __cplusplus
}
#endif

#endif /* _NCP_PHY_REGS_H_ */
