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


#ifndef _NCP_SYSCON_XLF_REGS_H_
#define _NCP_SYSCON_XLF_REGS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*! @struct ncp_syscon_cpu_cs_r_xlf_t
 *  @brief CPU Cluster Clock Switch Control Register
 *  @details This register controls the clock switches for the CPU clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_cpu_cs_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param clk_cpu7_sel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Logical CPU cluster 7 clock switch select </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clk_cpu6_sel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Logical CPU cluster 6 clock switch select </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clk_cpu5_sel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Logical CPU cluster 5 clock switch select </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clk_cpu4_sel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Logical CPU cluster 4 clock switch select </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clk_cpu3_sel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Logical CPU cluster 3 clock switch select </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clk_cpu2_sel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Logical CPU cluster 2 clock switch select </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clk_cpu1_sel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Logical CPU cluster 1 clock switch select </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clk_cpu0_sel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Logical CPU cluster 0 clock switch select </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_cpu_cs_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      clk_cpu7_sel                              :  2;
     unsigned      clk_cpu6_sel                              :  2;
     unsigned      clk_cpu5_sel                              :  2;
     unsigned      clk_cpu4_sel                              :  2;
     unsigned      clk_cpu3_sel                              :  2;
     unsigned      clk_cpu2_sel                              :  2;
     unsigned      clk_cpu1_sel                              :  2;
     unsigned      clk_cpu0_sel                              :  2;
#else    /* Little Endian */
     unsigned      clk_cpu0_sel                              :  2;
     unsigned      clk_cpu1_sel                              :  2;
     unsigned      clk_cpu2_sel                              :  2;
     unsigned      clk_cpu3_sel                              :  2;
     unsigned      clk_cpu4_sel                              :  2;
     unsigned      clk_cpu5_sel                              :  2;
     unsigned      clk_cpu6_sel                              :  2;
     unsigned      clk_cpu7_sel                              :  2;
     unsigned      reserved0                                 : 16;
#endif
} ncp_syscon_cpu_cs_r_xlf_t;

/*! @struct ncp_syscon_dsp_cs_r_xlf_t
 *  @brief DSP Cluster Clock Switch Control Register
 *  @details This register controls the clock switches for the DSP clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_dsp_cs_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param clk_cpu3_sel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Logical DSP cluster 3 clock switch select </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clk_cpu2_sel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Logical DSP cluster 2 clock switch select </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clk_cpu1_sel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Logical DSP cluster 1 clock switch select </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clk_cpu0_sel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Logical DSP cluster 0 clock switch select </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_dsp_cs_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      clk_cpu3_sel                              :  2;
     unsigned      clk_cpu2_sel                              :  2;
     unsigned      clk_cpu1_sel                              :  2;
     unsigned      clk_cpu0_sel                              :  2;
#else    /* Little Endian */
     unsigned      clk_cpu0_sel                              :  2;
     unsigned      clk_cpu1_sel                              :  2;
     unsigned      clk_cpu2_sel                              :  2;
     unsigned      clk_cpu3_sel                              :  2;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_dsp_cs_r_xlf_t;

/*! @struct ncp_syscon_sys_cs_r_xlf_t
 *  @brief System Clock Switch Control Register
 *  @details This register controls the system clock switches for the other clocks.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_sys_cs_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param clk_time_ref_sel </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Determines which clock is muxed onto clk_time_ref. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clk_sys2x_sel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Determines which clock is muxed onto clk_sys2x. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clk_per_sel </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Determines which clock is muxed onto clk_per. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clk_nuevo_sel </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Determines which clock is muxed onto clk_nuevo. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clk_nrcp1_sel </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Determines which clock is muxed onto clk_nrcp1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clk_nrcp_sel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Determines which clock is muxed onto clk_nrcp. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clk_fes_sel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Determines which clock is muxed onto clk_fes. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clk_fab_sel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Determines which clock is muxed onto clk_fab. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clk_dec_sel </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Determines which clock is muxed onto clk_dec. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clk_bcn_sel </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Determines which clock is muxed onto clk_bcn. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clk_mmc_sel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Determines which clock is muxed onto clk_atclk. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_sys_cs_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      clk_time_ref_sel                          :  1;
     unsigned      clk_sys2x_sel                             :  2;
     unsigned      clk_per_sel                               :  1;
     unsigned      clk_nuevo_sel                             :  1;
     unsigned      clk_nrcp1_sel                             :  1;
     unsigned      clk_nrcp_sel                              :  2;
     unsigned      clk_fes_sel                               :  2;
     unsigned      clk_fab_sel                               :  2;
     unsigned      clk_dec_sel                               :  1;
     unsigned      clk_bcn_sel                               :  1;
     unsigned      clk_mmc_sel                               :  2;
#else    /* Little Endian */
     unsigned      clk_mmc_sel                               :  2;
     unsigned      clk_bcn_sel                               :  1;
     unsigned      clk_dec_sel                               :  1;
     unsigned      clk_fab_sel                               :  2;
     unsigned      clk_fes_sel                               :  2;
     unsigned      clk_nrcp_sel                              :  2;
     unsigned      clk_nrcp1_sel                             :  1;
     unsigned      clk_nuevo_sel                             :  1;
     unsigned      clk_per_sel                               :  1;
     unsigned      clk_sys2x_sel                             :  2;
     unsigned      clk_time_ref_sel                          :  1;
     unsigned      reserved0                                 : 16;
#endif
} ncp_syscon_sys_cs_r_xlf_t;

/*! @struct ncp_syscon_stop_clk_cpu_r_xlf_t
 *  @brief Stop Clock CPU Register
 *  @details This register controls whether or not the individual CPU cluster clocks are gated off.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_stop_clk_cpu_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param stop_clk_cpu7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> If set, forces logical CPU cluster 7's clock to 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param stop_clk_cpu6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> If set, forces logical CPU cluster 6's clock to 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param stop_clk_cpu5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> If set, forces logical CPU cluster 5's clock to 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param stop_clk_cpu4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> If set, forces logical CPU cluster 4's clock to 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param stop_clk_cpu3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> If set, forces logical CPU cluster 3's clock to 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param stop_clk_cpu2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> If set, forces logical CPU cluster 2's clock to 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param stop_clk_cpu1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> If set, forces logical CPU cluster 1's clock to 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param stop_clk_cpu0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> If set, forces logical CPU cluster 0's clock to 0. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_stop_clk_cpu_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      stop_clk_cpu7                             :  1;
     unsigned      stop_clk_cpu6                             :  1;
     unsigned      stop_clk_cpu5                             :  1;
     unsigned      stop_clk_cpu4                             :  1;
     unsigned      stop_clk_cpu3                             :  1;
     unsigned      stop_clk_cpu2                             :  1;
     unsigned      stop_clk_cpu1                             :  1;
     unsigned      stop_clk_cpu0                             :  1;
#else    /* Little Endian */
     unsigned      stop_clk_cpu0                             :  1;
     unsigned      stop_clk_cpu1                             :  1;
     unsigned      stop_clk_cpu2                             :  1;
     unsigned      stop_clk_cpu3                             :  1;
     unsigned      stop_clk_cpu4                             :  1;
     unsigned      stop_clk_cpu5                             :  1;
     unsigned      stop_clk_cpu6                             :  1;
     unsigned      stop_clk_cpu7                             :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_stop_clk_cpu_r_xlf_t;

/*! @struct ncp_syscon_stop_clk_dsp_r_xlf_t
 *  @brief Stop Clock DSP Register
 *  @details This register controls whether or not the individual DSP cluster clocks are gated off.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_stop_clk_dsp_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param stop_clk_dsp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> If set, forces logical DSP cluster 3's clock to 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param stop_clk_dsp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> If set, forces logical DSP cluster 2's clock to 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param stop_clk_dsp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> If set, forces logical DSP cluster 1's clock to 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param stop_clk_dsp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> If set, forces logical DSP cluster 0's clock to 0. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_stop_clk_dsp_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 28;
     unsigned      stop_clk_dsp3                             :  1;
     unsigned      stop_clk_dsp2                             :  1;
     unsigned      stop_clk_dsp1                             :  1;
     unsigned      stop_clk_dsp0                             :  1;
#else    /* Little Endian */
     unsigned      stop_clk_dsp0                             :  1;
     unsigned      stop_clk_dsp1                             :  1;
     unsigned      stop_clk_dsp2                             :  1;
     unsigned      stop_clk_dsp3                             :  1;
     unsigned      reserved0                                 : 28;
#endif
} ncp_syscon_stop_clk_dsp_r_xlf_t;

/*! @struct ncp_syscon_stop_clk_r_xlf_t
 *  @brief Stop System Clock Register
 *  @details This register controls whether or not various system clocks are gated off.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_stop_clk_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param run_ifr_clks </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> If set, all IFR clocks are enabled, otherwise all
 *        IFR clocks are forced to 0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param stop_clk_ref_out </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> If set, forces CLK_REF_OUT to 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param stop_pll1out </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> If set, forces PLL1OUT to 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param stop_clk_time_ref </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> If set, forces clk_time_ref to 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param stop_clk_pclk </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> If set, forces clk_pclk to 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param stop_clk_nuevo </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> If set, forces clk_nuevo to 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param stop_clk_nrcp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> If set, forces clk_nrcp1 to 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param stop_clk_nrcp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> If set, forces clk_nrcp to 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param stop_clk_bcn </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> If set, forces clk_bcn to 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param stop_clk_fes </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> If set, forces clk_fes to 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param stop_clk_atclk </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> If set, forces clk_atclk to 0. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_stop_clk_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 21;
     unsigned      run_ifr_clks                              :  1;
     unsigned      stop_clk_ref_out                          :  1;
     unsigned      stop_pll1out                              :  1;
     unsigned      stop_clk_time_ref                         :  1;
     unsigned      stop_clk_pclk                             :  1;
     unsigned      stop_clk_nuevo                            :  1;
     unsigned      stop_clk_nrcp1                            :  1;
     unsigned      stop_clk_nrcp                             :  1;
     unsigned      stop_clk_bcn                              :  1;
     unsigned      stop_clk_fes                              :  1;
     unsigned      stop_clk_atclk                            :  1;
#else    /* Little Endian */
     unsigned      stop_clk_atclk                            :  1;
     unsigned      stop_clk_fes                              :  1;
     unsigned      stop_clk_bcn                              :  1;
     unsigned      stop_clk_nrcp                             :  1;
     unsigned      stop_clk_nrcp1                            :  1;
     unsigned      stop_clk_nuevo                            :  1;
     unsigned      stop_clk_pclk                             :  1;
     unsigned      stop_clk_time_ref                         :  1;
     unsigned      stop_pll1out                              :  1;
     unsigned      stop_clk_ref_out                          :  1;
     unsigned      run_ifr_clks                              :  1;
     unsigned      reserved0                                 : 21;
#endif
} ncp_syscon_stop_clk_r_xlf_t;

/*! @struct ncp_syscon_pll1out_div_r_xlf_t
 *  @brief PLL1OUT Clock Divider Register
 *  @details This register controls the divider used for the PLL1OUT output clock.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pll1out_div_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param div_load </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Toggling this value from 0 to 1 will cause the divider
 *        value to be updated.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param div_m1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Divider value used is this value + 1. Should only
 *        be changed while div_load is 0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pll1out_div_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 26;
     unsigned      div_load                                  :  1;
     unsigned      div_m1                                    :  5;
#else    /* Little Endian */
     unsigned      div_m1                                    :  5;
     unsigned      div_load                                  :  1;
     unsigned      reserved0                                 : 26;
#endif
} ncp_syscon_pll1out_div_r_xlf_t;

/*! @struct ncp_syscon_gic_disable_r_xlf_t
 *  @brief GIC Disable Register.
 *  @details Interrupt controller disables.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_gic_disable_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param gic7_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Disable interrupt controller functionality for cluster7. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gic6_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Disable interrupt controller functionality for cluster6. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gic5_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Disable interrupt controller functionality for cluster5. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gic4_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Disable interrupt controller functionality for cluster4. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gic3_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Disable interrupt controller functionality for cluster3. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gic2_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Disable interrupt controller functionality for cluster2. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gic1_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Disable interrupt controller functionality for cluster1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gic0_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Disable interrupt controller functionality for cluster0. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_gic_disable_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      gic7_disable                              :  1;
     unsigned      gic6_disable                              :  1;
     unsigned      gic5_disable                              :  1;
     unsigned      gic4_disable                              :  1;
     unsigned      gic3_disable                              :  1;
     unsigned      gic2_disable                              :  1;
     unsigned      gic1_disable                              :  1;
     unsigned      gic0_disable                              :  1;
#else    /* Little Endian */
     unsigned      gic0_disable                              :  1;
     unsigned      gic1_disable                              :  1;
     unsigned      gic2_disable                              :  1;
     unsigned      gic3_disable                              :  1;
     unsigned      gic4_disable                              :  1;
     unsigned      gic5_disable                              :  1;
     unsigned      gic6_disable                              :  1;
     unsigned      gic7_disable                              :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_gic_disable_r_xlf_t;

/*! @struct ncp_syscon_cp15sdisable_r_xlf_t
 *  @brief CPU Cluster Access Disable Register
 *  @details When a bit is set, disables write access to specific secure registers in the corresponding CPU cluster.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_cp15sdisable_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_acc_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU cluster7 access disable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_acc_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU cluster6 access disable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_acc_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU cluster5 access disable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_acc_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU cluster4 access disable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_acc_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU cluster3 access disable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_acc_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU cluster2 access disable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_acc_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU cluster1 access disable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_acc_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU cluster0 access disable. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_cp15sdisable_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_acc_disable                      :  1;
     unsigned      cluster6_acc_disable                      :  1;
     unsigned      cluster5_acc_disable                      :  1;
     unsigned      cluster4_acc_disable                      :  1;
     unsigned      cluster3_acc_disable                      :  1;
     unsigned      cluster2_acc_disable                      :  1;
     unsigned      cluster1_acc_disable                      :  1;
     unsigned      cluster0_acc_disable                      :  1;
#else    /* Little Endian */
     unsigned      cluster0_acc_disable                      :  1;
     unsigned      cluster1_acc_disable                      :  1;
     unsigned      cluster2_acc_disable                      :  1;
     unsigned      cluster3_acc_disable                      :  1;
     unsigned      cluster4_acc_disable                      :  1;
     unsigned      cluster5_acc_disable                      :  1;
     unsigned      cluster6_acc_disable                      :  1;
     unsigned      cluster7_acc_disable                      :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_cp15sdisable_r_xlf_t;

/*! @struct ncp_syscon_l1rstdisable_r_xlf_t
 *  @brief CPU Cluster L1 Reset Disable Register
 *  @details When a bit is set, the L1 for the corresponding CPU cluster does not auto-initialize after reset.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_l1rstdisable_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_l1_rst_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU cluster7 L1 auto-initialize after reset disable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_l1_rst_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU cluster6 L1 auto-initialize after reset disable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_l1_rst_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU cluster5 L1 auto-initialize after reset disable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_l1_rst_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU cluster4 L1 auto-initialize after reset disable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_l1_rst_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU cluster3 L1 auto-initialize after reset disable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_l1_rst_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU cluster2 L1 auto-initialize after reset disable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_l1_rst_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU cluster1 L1 auto-initialize after reset disable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_l1_rst_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU cluster0 L1 auto-initialize after reset disable. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_l1rstdisable_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_l1_rst_disable                   :  1;
     unsigned      cluster6_l1_rst_disable                   :  1;
     unsigned      cluster5_l1_rst_disable                   :  1;
     unsigned      cluster4_l1_rst_disable                   :  1;
     unsigned      cluster3_l1_rst_disable                   :  1;
     unsigned      cluster2_l1_rst_disable                   :  1;
     unsigned      cluster1_l1_rst_disable                   :  1;
     unsigned      cluster0_l1_rst_disable                   :  1;
#else    /* Little Endian */
     unsigned      cluster0_l1_rst_disable                   :  1;
     unsigned      cluster1_l1_rst_disable                   :  1;
     unsigned      cluster2_l1_rst_disable                   :  1;
     unsigned      cluster3_l1_rst_disable                   :  1;
     unsigned      cluster4_l1_rst_disable                   :  1;
     unsigned      cluster5_l1_rst_disable                   :  1;
     unsigned      cluster6_l1_rst_disable                   :  1;
     unsigned      cluster7_l1_rst_disable                   :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_l1rstdisable_r_xlf_t;

/*! @struct ncp_syscon_l2rstdisable_r_xlf_t
 *  @brief CPU Cluster L2 Reset Disable Register
 *  @details When a bit is set, the L2 for the corresponding CPU cluster does not auto-initialize after reset.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_l2rstdisable_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_l2_rst_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU cluster7 L2 auto-initialize after reset disable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_l2_rst_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU cluster6 L2 auto-initialize after reset disable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_l2_rst_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU cluster5 L2 auto-initialize after reset disable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_l2_rst_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU cluster4 L2 auto-initialize after reset disable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_l2_rst_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU cluster3 L2 auto-initialize after reset disable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_l2_rst_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU cluster2 L2 auto-initialize after reset disable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_l2_rst_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU cluster1 L2 auto-initialize after reset disable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_l2_rst_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU cluster0 L2 auto-initialize after reset disable. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_l2rstdisable_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_l2_rst_disable                   :  1;
     unsigned      cluster6_l2_rst_disable                   :  1;
     unsigned      cluster5_l2_rst_disable                   :  1;
     unsigned      cluster4_l2_rst_disable                   :  1;
     unsigned      cluster3_l2_rst_disable                   :  1;
     unsigned      cluster2_l2_rst_disable                   :  1;
     unsigned      cluster1_l2_rst_disable                   :  1;
     unsigned      cluster0_l2_rst_disable                   :  1;
#else    /* Little Endian */
     unsigned      cluster0_l2_rst_disable                   :  1;
     unsigned      cluster1_l2_rst_disable                   :  1;
     unsigned      cluster2_l2_rst_disable                   :  1;
     unsigned      cluster3_l2_rst_disable                   :  1;
     unsigned      cluster4_l2_rst_disable                   :  1;
     unsigned      cluster5_l2_rst_disable                   :  1;
     unsigned      cluster6_l2_rst_disable                   :  1;
     unsigned      cluster7_l2_rst_disable                   :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_l2rstdisable_r_xlf_t;

/*! @struct ncp_syscon_debug_sw_en_r_xlf_t
 *  @brief CPU Debug Software Enable Register
 *  @details This register contains the bits that enable software debugging for the CPU clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_debug_sw_en_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param dbgswen_cpu3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU cluster3 software debug enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgswen_cpu2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU cluster2 software debug enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgswen_cpu1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU cluster1 software debug enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgswen_cpu0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU cluster0 software debug enable. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_debug_sw_en_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 28;
     unsigned      dbgswen_cpu3                              :  1;
     unsigned      dbgswen_cpu2                              :  1;
     unsigned      dbgswen_cpu1                              :  1;
     unsigned      dbgswen_cpu0                              :  1;
#else    /* Little Endian */
     unsigned      dbgswen_cpu0                              :  1;
     unsigned      dbgswen_cpu1                              :  1;
     unsigned      dbgswen_cpu2                              :  1;
     unsigned      dbgswen_cpu3                              :  1;
     unsigned      reserved0                                 : 28;
#endif
} ncp_syscon_debug_sw_en_r_xlf_t;

/*! @struct ncp_syscon_cdc_debug_sw_en_r_xlf_t
 *  @brief CDC Debug Software Enable Register
 *  @details This register contains the bits that enable software debugging for the FES and CDC clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_cdc_debug_sw_en_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param dbgswen_fes </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> FES software debug enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgswen_cdc3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CDC cluster3 software debug enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgswen_cdc2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CDC cluster2 software debug enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgswen_cdc1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CDC cluster1 software debug enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgswen_cdc0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CDC cluster0 software debug enable. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_cdc_debug_sw_en_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 27;
     unsigned      dbgswen_fes                               :  1;
     unsigned      dbgswen_cdc3                              :  1;
     unsigned      dbgswen_cdc2                              :  1;
     unsigned      dbgswen_cdc1                              :  1;
     unsigned      dbgswen_cdc0                              :  1;
#else    /* Little Endian */
     unsigned      dbgswen_cdc0                              :  1;
     unsigned      dbgswen_cdc1                              :  1;
     unsigned      dbgswen_cdc2                              :  1;
     unsigned      dbgswen_cdc3                              :  1;
     unsigned      dbgswen_fes                               :  1;
     unsigned      reserved0                                 : 27;
#endif
} ncp_syscon_cdc_debug_sw_en_r_xlf_t;

/*! @struct ncp_syscon_sei_r_xlf_t
 *  @brief CPU Fast Interrupt Request Register.
 *  @details Per CPU Interrupt request.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_sei_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cpu31_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Generate interrupt request for CPU31. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu30_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Generate interrupt request for CPU30. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu29_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Generate interrupt request for CPU29. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu28_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Generate interrupt request for CPU28. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu27_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Generate interrupt request for CPU27. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu26_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Generate interrupt request for CPU26. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu25_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Generate interrupt request for CPU25. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu24_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Generate interrupt request for CPU24. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu23_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Generate interrupt request for CPU23. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu22_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Generate interrupt request for CPU22. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu21_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Generate interrupt request for CPU21. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu20_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Generate interrupt request for CPU20. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu19_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Generate interrupt request for CPU19. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu18_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Generate interrupt request for CPU18. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu17_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Generate interrupt request for CPU17. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu16_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Generate interrupt request for CPU16. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu15_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Generate interrupt request for CPU15. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu14_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Generate interrupt request for CPU14. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu13_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Generate interrupt request for CPU13. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu12_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Generate interrupt request for CPU12. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu11_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Generate interrupt request for CPU11. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu10_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Generate interrupt request for CPU10. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu9_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Generate interrupt request for CPU9. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu8_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Generate interrupt request for CPU8. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu7_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Generate interrupt request for CPU7. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu6_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Generate interrupt request for CPU6. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu5_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Generate interrupt request for CPU5. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu4_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Generate interrupt request for CPU4. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu3_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Generate interrupt request for CPU3. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu2_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Generate interrupt request for CPU2. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu1_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Generate interrupt request for CPU1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu0_sei </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Generate interrupt request for CPU0. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_sei_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      cpu31_sei                                 :  1;
     unsigned      cpu30_sei                                 :  1;
     unsigned      cpu29_sei                                 :  1;
     unsigned      cpu28_sei                                 :  1;
     unsigned      cpu27_sei                                 :  1;
     unsigned      cpu26_sei                                 :  1;
     unsigned      cpu25_sei                                 :  1;
     unsigned      cpu24_sei                                 :  1;
     unsigned      cpu23_sei                                 :  1;
     unsigned      cpu22_sei                                 :  1;
     unsigned      cpu21_sei                                 :  1;
     unsigned      cpu20_sei                                 :  1;
     unsigned      cpu19_sei                                 :  1;
     unsigned      cpu18_sei                                 :  1;
     unsigned      cpu17_sei                                 :  1;
     unsigned      cpu16_sei                                 :  1;
     unsigned      cpu15_sei                                 :  1;
     unsigned      cpu14_sei                                 :  1;
     unsigned      cpu13_sei                                 :  1;
     unsigned      cpu12_sei                                 :  1;
     unsigned      cpu11_sei                                 :  1;
     unsigned      cpu10_sei                                 :  1;
     unsigned      cpu9_sei                                  :  1;
     unsigned      cpu8_sei                                  :  1;
     unsigned      cpu7_sei                                  :  1;
     unsigned      cpu6_sei                                  :  1;
     unsigned      cpu5_sei                                  :  1;
     unsigned      cpu4_sei                                  :  1;
     unsigned      cpu3_sei                                  :  1;
     unsigned      cpu2_sei                                  :  1;
     unsigned      cpu1_sei                                  :  1;
     unsigned      cpu0_sei                                  :  1;
#else    /* Little Endian */
     unsigned      cpu0_sei                                  :  1;
     unsigned      cpu1_sei                                  :  1;
     unsigned      cpu2_sei                                  :  1;
     unsigned      cpu3_sei                                  :  1;
     unsigned      cpu4_sei                                  :  1;
     unsigned      cpu5_sei                                  :  1;
     unsigned      cpu6_sei                                  :  1;
     unsigned      cpu7_sei                                  :  1;
     unsigned      cpu8_sei                                  :  1;
     unsigned      cpu9_sei                                  :  1;
     unsigned      cpu10_sei                                 :  1;
     unsigned      cpu11_sei                                 :  1;
     unsigned      cpu12_sei                                 :  1;
     unsigned      cpu13_sei                                 :  1;
     unsigned      cpu14_sei                                 :  1;
     unsigned      cpu15_sei                                 :  1;
     unsigned      cpu16_sei                                 :  1;
     unsigned      cpu17_sei                                 :  1;
     unsigned      cpu18_sei                                 :  1;
     unsigned      cpu19_sei                                 :  1;
     unsigned      cpu20_sei                                 :  1;
     unsigned      cpu21_sei                                 :  1;
     unsigned      cpu22_sei                                 :  1;
     unsigned      cpu23_sei                                 :  1;
     unsigned      cpu24_sei                                 :  1;
     unsigned      cpu25_sei                                 :  1;
     unsigned      cpu26_sei                                 :  1;
     unsigned      cpu27_sei                                 :  1;
     unsigned      cpu28_sei                                 :  1;
     unsigned      cpu29_sei                                 :  1;
     unsigned      cpu30_sei                                 :  1;
     unsigned      cpu31_sei                                 :  1;
#endif
} ncp_syscon_sei_r_xlf_t;

/*! @struct ncp_syscon_pfuse_r_xlf_t
 *  @brief System Control Parallel Fuse Register
 *  @details This register contains the critical system control fuse values (fuse words 0x43-0x40) that are read
        and latched at powerup by the fuse download controller.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pfuse_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param disable_sec0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> If either disable_sec0 or disable_sec1 are set, the
 *        functionality of the MACSEC, PKA, SBB, SPP and
 *        TRNG logic as well as the ELM encryption logic are
 *        disabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_sec1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> If either disable_sec0 or disable_sec1 are set, the
 *        functionality of the MACSEC, PKA, SBB, SPP and TRNG
 *        logic as well as the ELM encryption logic are disabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_custom </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> If set, disable the EAC, FC, and FES core logic. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_rifs </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> If set, disable the core logic for the radio interfaces
 *        (RIF0/1 and ERIF0/1).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_cdcs </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> If set, disable the core logic for the DSPs. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> RESERVED </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mtc_selftest_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> If set, disable the inclusion of the AXM itself from
 *        MTC testing and force the values in  the MTC Control
 *        register to 0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> RESERVED </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param secure_boot_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> If set, indicates Secure Boot Mode is enabled. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param redundant_stage2_boot </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> If set, indicates Redundant Stage 2 Boot mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param psm_wait_16k </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> If set, wait 16K clocks between PSM states (instead
 *        of 64 clocks).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param chip_version_major </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Chip major version number. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param chip_version_minor </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Chip minor version number. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param chip_type </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Chip type. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pfuse_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      disable_sec0                              :  1;
     unsigned      disable_sec1                              :  1;
     unsigned      disable_custom                            :  1;
     unsigned      disable_rifs                              :  1;
     unsigned      disable_cdcs                              :  1;
     unsigned      reserved0                                 :  9;
     unsigned      mtc_selftest_disable                      :  1;
     unsigned      reserved1                                 :  3;
     unsigned      secure_boot_enable                        :  1;
     unsigned      redundant_stage2_boot                     :  1;
     unsigned      psm_wait_16k                              :  1;
     unsigned      chip_version_major                        :  3;
     unsigned      chip_version_minor                        :  3;
     unsigned      chip_type                                 :  5;
#else    /* Little Endian */
     unsigned      chip_type                                 :  5;
     unsigned      chip_version_minor                        :  3;
     unsigned      chip_version_major                        :  3;
     unsigned      psm_wait_16k                              :  1;
     unsigned      redundant_stage2_boot                     :  1;
     unsigned      secure_boot_enable                        :  1;
     unsigned      reserved1                                 :  3;
     unsigned      mtc_selftest_disable                      :  1;
     unsigned      reserved0                                 :  9;
     unsigned      disable_cdcs                              :  1;
     unsigned      disable_rifs                              :  1;
     unsigned      disable_custom                            :  1;
     unsigned      disable_sec1                              :  1;
     unsigned      disable_sec0                              :  1;
#endif
} ncp_syscon_pfuse_r_xlf_t;

/*! @struct ncp_syscon_fuse_stat_r_xlf_t
 *  @brief Fuse Status Register
 *  @details status for the various fuse download controllers.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_fuse_stat_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param fdc_done </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> LSI_EFUSE_POSM download complete. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sms_done </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Star Memory System BIST complete. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ecm_done </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> ECM fuse download complete. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_fuse_stat_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 29;
     unsigned      fdc_done                                  :  1;
     unsigned      sms_done                                  :  1;
     unsigned      ecm_done                                  :  1;
#else    /* Little Endian */
     unsigned      ecm_done                                  :  1;
     unsigned      sms_done                                  :  1;
     unsigned      fdc_done                                  :  1;
     unsigned      reserved0                                 : 29;
#endif
} ncp_syscon_fuse_stat_r_xlf_t;

/*! @struct ncp_syscon_scratch_r_xlf_t
 *  @brief Scratch Register
 *  @details This register is 32b of R/W data that is reset to 0.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_scratch_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param scratch </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Scratch data. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_scratch_r_xlf_t
 *
 */
 
typedef struct
{
     unsigned  int                   scratch;
} ncp_syscon_scratch_r_xlf_t;

/*! @struct ncp_syscon_nmi_enable_r_xlf_t
 *  @brief DSP Non-Maskable Interrupt Enable Register
 *  @details This register contains pin and CFG Non-Maskable Interrupt control.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_nmi_enable_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param write_lock </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> If set, disables any further writes to this register
 *        until after a chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param nmi_req_pin </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Current state of the NMI_FES_DSP_REQ pin. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param nmi_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Writing a 1 to this bit generates a 64 clock cycle
 *        pulse on the nmi inputs that are enabled by the other
 *         bits in this register, irrespective of the setting
 *        of the write_lock bit. Reads always return a 0 for
 *        this  bit.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu_nmi_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> If set, gic_ppi21 is enabled for all CPUs. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fes_nmi_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> If set, the FES NMI is enabled. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dsp3_nmi_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> If set, DSP cluster 3's NMI is enabled. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dsp2_nmi_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> If set, DSP cluster 2's NMI is enabled. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dsp1_nmi_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> If set, DSP cluster 1's NMI is enabled. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dsp0_nmi_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> If set, DSP cluster 0's NMI is enabled. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_nmi_enable_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      write_lock                                :  1;
     unsigned      nmi_req_pin                               :  1;
     unsigned      nmi_req                                   :  1;
     unsigned      reserved0                                 : 23;
     unsigned      cpu_nmi_enable                            :  1;
     unsigned      fes_nmi_enable                            :  1;
     unsigned      dsp3_nmi_enable                           :  1;
     unsigned      dsp2_nmi_enable                           :  1;
     unsigned      dsp1_nmi_enable                           :  1;
     unsigned      dsp0_nmi_enable                           :  1;
#else    /* Little Endian */
     unsigned      dsp0_nmi_enable                           :  1;
     unsigned      dsp1_nmi_enable                           :  1;
     unsigned      dsp2_nmi_enable                           :  1;
     unsigned      dsp3_nmi_enable                           :  1;
     unsigned      fes_nmi_enable                            :  1;
     unsigned      cpu_nmi_enable                            :  1;
     unsigned      reserved0                                 : 23;
     unsigned      nmi_req                                   :  1;
     unsigned      nmi_req_pin                               :  1;
     unsigned      write_lock                                :  1;
#endif
} ncp_syscon_nmi_enable_r_xlf_t;

/*! @struct ncp_syscon_spare_c_r_xlf_t
 *  @brief Spare Chip Control Register
 *  @details This register contains spare critical control bits that are reset by a pin, system, or chip reset.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_spare_c_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param spare </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Spare control bits. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_spare_c_r_xlf_t
 *
 */
 
typedef struct
{
     unsigned  int                     spare;
} ncp_syscon_spare_c_r_xlf_t;

/*! @struct ncp_syscon_spare_s_r_xlf_t
 *  @brief Spare System Control Register
 *  @details This register contains spare critical control bits that are reset only by a pin or system reset.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_spare_s_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param spare </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Spare control bits. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_spare_s_r_xlf_t
 *
 */
 
typedef struct
{
     unsigned  int                     spare;
} ncp_syscon_spare_s_r_xlf_t;

/*! @struct ncp_syscon_spare_p_r_xlf_t
 *  @brief Spare Pin Control Register
 *  @details This register contains spare critical control bits that are reset only by a pin reset.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_spare_p_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param spare </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Spare control bits. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_spare_p_r_xlf_t
 *
 */
 
typedef struct
{
     unsigned  int                     spare;
} ncp_syscon_spare_p_r_xlf_t;

/*! @struct ncp_syscon_pscratch_r_xlf_t
 *  @brief Persistent Scratch Register
 *  @details This register is 32b of R/W data that is never reset by anything.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pscratch_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param pscratch </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Persistent scratch data. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pscratch_r_xlf_t
 *
 */
 
typedef struct
{
     unsigned  int                  pscratch;
} ncp_syscon_pscratch_r_xlf_t;

/*! @struct ncp_syscon_reset_status_r_xlf_t
 *  @brief Reset Status Register
 *  @details This register holds the sticky status of what initiated the various system and chip resets.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_reset_status_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param fabric_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> A fabric reset occurred. This was due to a reset_system
 *        sequence (if pin_reset, wd*_sys_reset, mtc_sys_reset,
 *         or cfg_sys_reset is also set), or a reset_chip
 *        sequence (if wd*_chip_reset, mtc_chip_reset, cfg_chip_reset,
 *        or  dbg_chip_reset is also set), or resetZero being
 *        asserted (if cfg_zeroize_reset is also set), or due
 *        to a  zeroization event with zeroize_with_reset
 *        enabled (if none of the other bits mentioned here
 *        are also set).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_zeroize_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> A zeroize reset was requested by writing the resetZero
 *        bit. This bit is reset by a pin, system or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cdbgrstreq_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> A debug logic reset due to a Coresight debug logic
 *        reset request ocurred. This bit is reset by a pin,
 *        system or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param chip_reset_wo_sm </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> A chip reset ocurred while the reset_chip_wo_sm bit
 *        was also set. This bit is reset by a pin or system
 *        reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param nstim_chip_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> A chip reset due to a NS timer expiration chip reset
 *        request ocurred. This bit is reset by a pin or system
 *        reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_chip_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> A chip reset due to a warm reset chip reset request
 *        ocurred. This bit is reset by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_chip_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> A chip reset due to a debug logic chip reset request
 *        ocurred. This bit is reset by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mtc_chip_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> A chip reset due to an MTC event ocurred. This bit
 *        is reset by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_chip_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> A chip reset due to a cfg write of the chip reset
 *        bit ocurred. This bit is reset by a pin or system
 *        reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wd1_chip_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> A chip reset due to a watchdog timer 1 expiration
 *        ocurred. This bit is reset by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wd0_chip_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> A chip reset due to a watchdog timer 0 expiration
 *        ocurred. This bit is reset by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mtc_sys_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> A system reset due to an MTC event ocurred. This bit
 *        is reset by a pin reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_sys_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> A system reset due to a cfg write of the system reset
 *        bit ocurred. This bit is reset by a pin reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wd1_sys_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> A system reset due to a watchdog timer 1 expiration
 *        ocurred. This bit is reset by a pin reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wd0_sys_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> A system reset due to a watchdog timer 0 expiration
 *        ocurred. This bit is reset by a pin reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pin_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> A pin reset ocurred </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_reset_status_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      fabric_reset                              :  1;
     unsigned      cfg_zeroize_reset                         :  1;
     unsigned      cdbgrstreq_reset                          :  1;
     unsigned      chip_reset_wo_sm                          :  1;
     unsigned      nstim_chip_reset                          :  1;
     unsigned      warm_chip_reset                           :  1;
     unsigned      dbg_chip_reset                            :  1;
     unsigned      mtc_chip_reset                            :  1;
     unsigned      cfg_chip_reset                            :  1;
     unsigned      wd1_chip_reset                            :  1;
     unsigned      wd0_chip_reset                            :  1;
     unsigned      mtc_sys_reset                             :  1;
     unsigned      cfg_sys_reset                             :  1;
     unsigned      wd1_sys_reset                             :  1;
     unsigned      wd0_sys_reset                             :  1;
     unsigned      pin_reset                                 :  1;
#else    /* Little Endian */
     unsigned      pin_reset                                 :  1;
     unsigned      wd0_sys_reset                             :  1;
     unsigned      wd1_sys_reset                             :  1;
     unsigned      cfg_sys_reset                             :  1;
     unsigned      mtc_sys_reset                             :  1;
     unsigned      wd0_chip_reset                            :  1;
     unsigned      wd1_chip_reset                            :  1;
     unsigned      cfg_chip_reset                            :  1;
     unsigned      mtc_chip_reset                            :  1;
     unsigned      dbg_chip_reset                            :  1;
     unsigned      warm_chip_reset                           :  1;
     unsigned      nstim_chip_reset                          :  1;
     unsigned      chip_reset_wo_sm                          :  1;
     unsigned      cdbgrstreq_reset                          :  1;
     unsigned      cfg_zeroize_reset                         :  1;
     unsigned      fabric_reset                              :  1;
     unsigned      reserved0                                 : 16;
#endif
} ncp_syscon_reset_status_r_xlf_t;

/*! @struct ncp_syscon_reset_status_force_r_xlf_t
 *  @brief Reset Status Force Register
 *  @details This address is an alias for the Reset Status register that allows normal CFG R/W (as opposed to the Clear-On-Write-One
	behavior if the Reset Status register address is used).  This allows CFG to set bits for testing purposes.  Reading this
	address returns the current value of the Reset Status register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_reset_status_force_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param fabric_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> A fabric reset occurred. This was due to a reset_system
 *        sequence (if pin_reset, wd*_sys_reset, mtc_sys_reset
 *        or  cfg_sys_reset is also set), or a reset_chip
 *        sequence (if wd*_chip_reset, mtc_chip_reset, cfg_chip_reset,
 *        or  dbg_chip_reset is also set), or resetZero being
 *        asserted (if cfg_zeroize_reset is also set), or due
 *        to a  zeroization event with zeroize_with_reset
 *        enabled (if none of the other bits mentioned here
 *        are also set).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_zeroize_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> A zeroize reset was requested by writing the resetZero
 *        bit. This bit is reset by a pin, system or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cdbgrstreq_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> A debug logic reset due to a Coresight debug logic
 *        reset request ocurred. This bit is reset by a pin,
 *        system or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param nstim_chip_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> A chip reset due to a NS timer expiration chip reset
 *        request ocurred. This bit is reset by a pin or system
 *        reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_chip_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> A chip reset due to a warm reset chip reset request
 *        ocurred. This bit is reset by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_chip_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> A chip reset due to a debug logic chip reset request
 *        ocurred. This bit is reset by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mtc_chip_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> A chip reset due to an MTC event ocurred. This bit
 *        is reset by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_chip_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> A chip reset due to a cfg write of the chip reset
 *        bit ocurred. This bit is reset by a pin or system
 *        reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wd1_chip_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> A chip reset due to a watchdog timer 1 expiration
 *        ocurred. This bit is reset by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wd0_chip_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> A chip reset due to a watchdog timer 0 expiration
 *        ocurred. This bit is reset by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mtc_sys_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> A system reset due to an MTC event ocurred. This bit
 *        is reset by a pin reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_sys_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> A system reset due to a cfg write of the system reset
 *        bit ocurred. This bit is reset by a pin reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wd1_sys_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> A system reset due to a watchdog timer 1 expiration
 *        ocurred. This bit is reset by a pin reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wd0_sys_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> A system reset due to a watchdog timer 0 expiration
 *        ocurred. This bit is reset by a pin reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pin_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> A pin reset ocurred </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_reset_status_force_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 17;
     unsigned      fabric_reset                              :  1;
     unsigned      cfg_zeroize_reset                         :  1;
     unsigned      cdbgrstreq_reset                          :  1;
     unsigned      nstim_chip_reset                          :  1;
     unsigned      warm_chip_reset                           :  1;
     unsigned      dbg_chip_reset                            :  1;
     unsigned      mtc_chip_reset                            :  1;
     unsigned      cfg_chip_reset                            :  1;
     unsigned      wd1_chip_reset                            :  1;
     unsigned      wd0_chip_reset                            :  1;
     unsigned      mtc_sys_reset                             :  1;
     unsigned      cfg_sys_reset                             :  1;
     unsigned      wd1_sys_reset                             :  1;
     unsigned      wd0_sys_reset                             :  1;
     unsigned      pin_reset                                 :  1;
#else    /* Little Endian */
     unsigned      pin_reset                                 :  1;
     unsigned      wd0_sys_reset                             :  1;
     unsigned      wd1_sys_reset                             :  1;
     unsigned      cfg_sys_reset                             :  1;
     unsigned      mtc_sys_reset                             :  1;
     unsigned      wd0_chip_reset                            :  1;
     unsigned      wd1_chip_reset                            :  1;
     unsigned      cfg_chip_reset                            :  1;
     unsigned      mtc_chip_reset                            :  1;
     unsigned      dbg_chip_reset                            :  1;
     unsigned      warm_chip_reset                           :  1;
     unsigned      nstim_chip_reset                          :  1;
     unsigned      cdbgrstreq_reset                          :  1;
     unsigned      cfg_zeroize_reset                         :  1;
     unsigned      fabric_reset                              :  1;
     unsigned      reserved0                                 : 17;
#endif
} ncp_syscon_reset_status_force_r_xlf_t;

/*! @struct ncp_syscon_reset_core_status_r_xlf_t
 *  @brief Reset Core Status Register
 *  @details This register holds the sticky status of any of the core reset bits having been asserted.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_reset_core_status_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core31 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Core reset was asserted for CPU31. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core30 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Core reset was asserted for CPU30. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core29 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Core reset was asserted for CPU29. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core28 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Core reset was asserted for CPU28. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core27 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Core reset was asserted for CPU27. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core26 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Core reset was asserted for CPU26. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core25 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Core reset was asserted for CPU25. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core24 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Core reset was asserted for CPU24. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core23 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Core reset was asserted for CPU23. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core22 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Core reset was asserted for CPU22. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core21 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Core reset was asserted for CPU21. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core20 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Core reset was asserted for CPU20. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core19 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Core reset was asserted for CPU19. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core18 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Core reset was asserted for CPU18. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core17 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Core reset was asserted for CPU17. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core16 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Core reset was asserted for CPU16. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core15 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Core reset was asserted for CPU15. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core14 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Core reset was asserted for CPU14. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core13 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Core reset was asserted for CPU13. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core12 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Core reset was asserted for CPU12. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core11 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Core reset was asserted for CPU11. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core10 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Core reset was asserted for CPU10. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core9 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Core reset was asserted for CPU9. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core8 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Core reset was asserted for CPU8. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Core reset was asserted for CPU7. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Core reset was asserted for CPU6. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Core reset was asserted for CPU5. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Core reset was asserted for CPU4. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Core reset was asserted for CPU3. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Core reset was asserted for CPU2. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Core reset was asserted for CPU1. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Core reset was asserted for CPU0. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_reset_core_status_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reset_core31                              :  1;
     unsigned      reset_core30                              :  1;
     unsigned      reset_core29                              :  1;
     unsigned      reset_core28                              :  1;
     unsigned      reset_core27                              :  1;
     unsigned      reset_core26                              :  1;
     unsigned      reset_core25                              :  1;
     unsigned      reset_core24                              :  1;
     unsigned      reset_core23                              :  1;
     unsigned      reset_core22                              :  1;
     unsigned      reset_core21                              :  1;
     unsigned      reset_core20                              :  1;
     unsigned      reset_core19                              :  1;
     unsigned      reset_core18                              :  1;
     unsigned      reset_core17                              :  1;
     unsigned      reset_core16                              :  1;
     unsigned      reset_core15                              :  1;
     unsigned      reset_core14                              :  1;
     unsigned      reset_core13                              :  1;
     unsigned      reset_core12                              :  1;
     unsigned      reset_core11                              :  1;
     unsigned      reset_core10                              :  1;
     unsigned      reset_core9                               :  1;
     unsigned      reset_core8                               :  1;
     unsigned      reset_core7                               :  1;
     unsigned      reset_core6                               :  1;
     unsigned      reset_core5                               :  1;
     unsigned      reset_core4                               :  1;
     unsigned      reset_core3                               :  1;
     unsigned      reset_core2                               :  1;
     unsigned      reset_core1                               :  1;
     unsigned      reset_core0                               :  1;
#else    /* Little Endian */
     unsigned      reset_core0                               :  1;
     unsigned      reset_core1                               :  1;
     unsigned      reset_core2                               :  1;
     unsigned      reset_core3                               :  1;
     unsigned      reset_core4                               :  1;
     unsigned      reset_core5                               :  1;
     unsigned      reset_core6                               :  1;
     unsigned      reset_core7                               :  1;
     unsigned      reset_core8                               :  1;
     unsigned      reset_core9                               :  1;
     unsigned      reset_core10                              :  1;
     unsigned      reset_core11                              :  1;
     unsigned      reset_core12                              :  1;
     unsigned      reset_core13                              :  1;
     unsigned      reset_core14                              :  1;
     unsigned      reset_core15                              :  1;
     unsigned      reset_core16                              :  1;
     unsigned      reset_core17                              :  1;
     unsigned      reset_core18                              :  1;
     unsigned      reset_core19                              :  1;
     unsigned      reset_core20                              :  1;
     unsigned      reset_core21                              :  1;
     unsigned      reset_core22                              :  1;
     unsigned      reset_core23                              :  1;
     unsigned      reset_core24                              :  1;
     unsigned      reset_core25                              :  1;
     unsigned      reset_core26                              :  1;
     unsigned      reset_core27                              :  1;
     unsigned      reset_core28                              :  1;
     unsigned      reset_core29                              :  1;
     unsigned      reset_core30                              :  1;
     unsigned      reset_core31                              :  1;
#endif
} ncp_syscon_reset_core_status_r_xlf_t;

/*! @struct ncp_syscon_reset_core_status_force_r_xlf_t
 *  @brief Reset Core Status Force Register
 *  @details This address is an alias for the Reset Core Status register that allows normal CFG R/W (as opposed to the
	Clear-On-Write-One behavior if the Reset Core Status register address is used).  This allows CFG to set bits for
	testing purposes.  Reading this address returns the current value of the Reset Core Status register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_reset_core_status_force_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core31 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Core reset was asserted for CPU31. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core30 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Core reset was asserted for CPU30. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core29 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Core reset was asserted for CPU29. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core28 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Core reset was asserted for CPU28. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core27 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Core reset was asserted for CPU27. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core26 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Core reset was asserted for CPU26. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core25 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Core reset was asserted for CPU25. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core24 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Core reset was asserted for CPU24. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core23 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Core reset was asserted for CPU23. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core22 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Core reset was asserted for CPU22. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core21 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Core reset was asserted for CPU21. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core20 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Core reset was asserted for CPU20. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core19 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Core reset was asserted for CPU19. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core18 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Core reset was asserted for CPU18. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core17 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Core reset was asserted for CPU17. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core16 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Core reset was asserted for CPU16. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core15 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Core reset was asserted for CPU15. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core14 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Core reset was asserted for CPU14. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core13 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Core reset was asserted for CPU13. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core12 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Core reset was asserted for CPU12. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core11 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Core reset was asserted for CPU11. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core10 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Core reset was asserted for CPU10. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core9 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Core reset was asserted for CPU9. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core8 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Core reset was asserted for CPU8. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Core reset was asserted for CPU7. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Core reset was asserted for CPU6. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Core reset was asserted for CPU5. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Core reset was asserted for CPU4. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Core reset was asserted for CPU3. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Core reset was asserted for CPU2. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Core reset was asserted for CPU1. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_core0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Core reset was asserted for CPU0. This bit is cleared
 *        by a pin, system, or chip reset.
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_reset_core_status_force_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reset_core31                              :  1;
     unsigned      reset_core30                              :  1;
     unsigned      reset_core29                              :  1;
     unsigned      reset_core28                              :  1;
     unsigned      reset_core27                              :  1;
     unsigned      reset_core26                              :  1;
     unsigned      reset_core25                              :  1;
     unsigned      reset_core24                              :  1;
     unsigned      reset_core23                              :  1;
     unsigned      reset_core22                              :  1;
     unsigned      reset_core21                              :  1;
     unsigned      reset_core20                              :  1;
     unsigned      reset_core19                              :  1;
     unsigned      reset_core18                              :  1;
     unsigned      reset_core17                              :  1;
     unsigned      reset_core16                              :  1;
     unsigned      reset_core15                              :  1;
     unsigned      reset_core14                              :  1;
     unsigned      reset_core13                              :  1;
     unsigned      reset_core12                              :  1;
     unsigned      reset_core11                              :  1;
     unsigned      reset_core10                              :  1;
     unsigned      reset_core9                               :  1;
     unsigned      reset_core8                               :  1;
     unsigned      reset_core7                               :  1;
     unsigned      reset_core6                               :  1;
     unsigned      reset_core5                               :  1;
     unsigned      reset_core4                               :  1;
     unsigned      reset_core3                               :  1;
     unsigned      reset_core2                               :  1;
     unsigned      reset_core1                               :  1;
     unsigned      reset_core0                               :  1;
#else    /* Little Endian */
     unsigned      reset_core0                               :  1;
     unsigned      reset_core1                               :  1;
     unsigned      reset_core2                               :  1;
     unsigned      reset_core3                               :  1;
     unsigned      reset_core4                               :  1;
     unsigned      reset_core5                               :  1;
     unsigned      reset_core6                               :  1;
     unsigned      reset_core7                               :  1;
     unsigned      reset_core8                               :  1;
     unsigned      reset_core9                               :  1;
     unsigned      reset_core10                              :  1;
     unsigned      reset_core11                              :  1;
     unsigned      reset_core12                              :  1;
     unsigned      reset_core13                              :  1;
     unsigned      reset_core14                              :  1;
     unsigned      reset_core15                              :  1;
     unsigned      reset_core16                              :  1;
     unsigned      reset_core17                              :  1;
     unsigned      reset_core18                              :  1;
     unsigned      reset_core19                              :  1;
     unsigned      reset_core20                              :  1;
     unsigned      reset_core21                              :  1;
     unsigned      reset_core22                              :  1;
     unsigned      reset_core23                              :  1;
     unsigned      reset_core24                              :  1;
     unsigned      reset_core25                              :  1;
     unsigned      reset_core26                              :  1;
     unsigned      reset_core27                              :  1;
     unsigned      reset_core28                              :  1;
     unsigned      reset_core29                              :  1;
     unsigned      reset_core30                              :  1;
     unsigned      reset_core31                              :  1;
#endif
} ncp_syscon_reset_core_status_force_r_xlf_t;

/*! @struct ncp_syscon_core_dbg_reset_status_r_xlf_t
 *  @brief Core Debug Reset Status Register
 *  @details This register holds the sticky status of any debug initiated core reset bits having been asserted.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_core_dbg_reset_status_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core31 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU31. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core30 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU30. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core29 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU29. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core28 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU28. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core27 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU27. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core26 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU26. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core25 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU25. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core24 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU24. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core23 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU23. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core22 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU22. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core21 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU21. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core20 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU20. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core19 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU19. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core18 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU18. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core17 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU17. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core16 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU16. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core15 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU15. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core14 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU14. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core13 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU13. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core12 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU12. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core11 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU11. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core10 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU10. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core9 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU9. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core8 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU8. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU7. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU6. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU5. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU4. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU3. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU2. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU1. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU0. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_core_dbg_reset_status_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      dbg_reset_core31                          :  1;
     unsigned      dbg_reset_core30                          :  1;
     unsigned      dbg_reset_core29                          :  1;
     unsigned      dbg_reset_core28                          :  1;
     unsigned      dbg_reset_core27                          :  1;
     unsigned      dbg_reset_core26                          :  1;
     unsigned      dbg_reset_core25                          :  1;
     unsigned      dbg_reset_core24                          :  1;
     unsigned      dbg_reset_core23                          :  1;
     unsigned      dbg_reset_core22                          :  1;
     unsigned      dbg_reset_core21                          :  1;
     unsigned      dbg_reset_core20                          :  1;
     unsigned      dbg_reset_core19                          :  1;
     unsigned      dbg_reset_core18                          :  1;
     unsigned      dbg_reset_core17                          :  1;
     unsigned      dbg_reset_core16                          :  1;
     unsigned      dbg_reset_core15                          :  1;
     unsigned      dbg_reset_core14                          :  1;
     unsigned      dbg_reset_core13                          :  1;
     unsigned      dbg_reset_core12                          :  1;
     unsigned      dbg_reset_core11                          :  1;
     unsigned      dbg_reset_core10                          :  1;
     unsigned      dbg_reset_core9                           :  1;
     unsigned      dbg_reset_core8                           :  1;
     unsigned      dbg_reset_core7                           :  1;
     unsigned      dbg_reset_core6                           :  1;
     unsigned      dbg_reset_core5                           :  1;
     unsigned      dbg_reset_core4                           :  1;
     unsigned      dbg_reset_core3                           :  1;
     unsigned      dbg_reset_core2                           :  1;
     unsigned      dbg_reset_core1                           :  1;
     unsigned      dbg_reset_core0                           :  1;
#else    /* Little Endian */
     unsigned      dbg_reset_core0                           :  1;
     unsigned      dbg_reset_core1                           :  1;
     unsigned      dbg_reset_core2                           :  1;
     unsigned      dbg_reset_core3                           :  1;
     unsigned      dbg_reset_core4                           :  1;
     unsigned      dbg_reset_core5                           :  1;
     unsigned      dbg_reset_core6                           :  1;
     unsigned      dbg_reset_core7                           :  1;
     unsigned      dbg_reset_core8                           :  1;
     unsigned      dbg_reset_core9                           :  1;
     unsigned      dbg_reset_core10                          :  1;
     unsigned      dbg_reset_core11                          :  1;
     unsigned      dbg_reset_core12                          :  1;
     unsigned      dbg_reset_core13                          :  1;
     unsigned      dbg_reset_core14                          :  1;
     unsigned      dbg_reset_core15                          :  1;
     unsigned      dbg_reset_core16                          :  1;
     unsigned      dbg_reset_core17                          :  1;
     unsigned      dbg_reset_core18                          :  1;
     unsigned      dbg_reset_core19                          :  1;
     unsigned      dbg_reset_core20                          :  1;
     unsigned      dbg_reset_core21                          :  1;
     unsigned      dbg_reset_core22                          :  1;
     unsigned      dbg_reset_core23                          :  1;
     unsigned      dbg_reset_core24                          :  1;
     unsigned      dbg_reset_core25                          :  1;
     unsigned      dbg_reset_core26                          :  1;
     unsigned      dbg_reset_core27                          :  1;
     unsigned      dbg_reset_core28                          :  1;
     unsigned      dbg_reset_core29                          :  1;
     unsigned      dbg_reset_core30                          :  1;
     unsigned      dbg_reset_core31                          :  1;
#endif
} ncp_syscon_core_dbg_reset_status_r_xlf_t;

/*! @struct ncp_syscon_core_dbg_reset_status_force_r_xlf_t
 *  @brief Core Debug Reset Status Force Register
 *  @details This address is an alias for the Core Debug Reset Status register that allows normal CFG R/W (as opposed to the
	Clear-On-Write-One behavior if the Core Debug Reset Status register address is used).  This allows CFG to set
	bits for testing purposes.  Reading this address returns the current value of the Core Debug Reset Status register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_core_dbg_reset_status_force_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core31 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU31. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core30 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU30. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core29 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU29. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core28 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU28. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core27 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU27. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core26 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU26. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core25 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU25. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core24 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU24. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core23 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU23. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core22 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU22. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core21 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU21. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core20 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU20. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core19 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU19. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core18 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU18. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core17 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU17. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core16 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU16. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core15 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU15. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core14 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU14. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core13 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU13. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core12 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU12. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core11 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU11. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core10 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU10. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core9 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU9. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core8 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU8. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU7. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU6. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU5. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU4. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU3. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU2. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU1. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbg_reset_core0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Core debug reset was asserted for CPU0. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_core_dbg_reset_status_force_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      dbg_reset_core31                          :  1;
     unsigned      dbg_reset_core30                          :  1;
     unsigned      dbg_reset_core29                          :  1;
     unsigned      dbg_reset_core28                          :  1;
     unsigned      dbg_reset_core27                          :  1;
     unsigned      dbg_reset_core26                          :  1;
     unsigned      dbg_reset_core25                          :  1;
     unsigned      dbg_reset_core24                          :  1;
     unsigned      dbg_reset_core23                          :  1;
     unsigned      dbg_reset_core22                          :  1;
     unsigned      dbg_reset_core21                          :  1;
     unsigned      dbg_reset_core20                          :  1;
     unsigned      dbg_reset_core19                          :  1;
     unsigned      dbg_reset_core18                          :  1;
     unsigned      dbg_reset_core17                          :  1;
     unsigned      dbg_reset_core16                          :  1;
     unsigned      dbg_reset_core15                          :  1;
     unsigned      dbg_reset_core14                          :  1;
     unsigned      dbg_reset_core13                          :  1;
     unsigned      dbg_reset_core12                          :  1;
     unsigned      dbg_reset_core11                          :  1;
     unsigned      dbg_reset_core10                          :  1;
     unsigned      dbg_reset_core9                           :  1;
     unsigned      dbg_reset_core8                           :  1;
     unsigned      dbg_reset_core7                           :  1;
     unsigned      dbg_reset_core6                           :  1;
     unsigned      dbg_reset_core5                           :  1;
     unsigned      dbg_reset_core4                           :  1;
     unsigned      dbg_reset_core3                           :  1;
     unsigned      dbg_reset_core2                           :  1;
     unsigned      dbg_reset_core1                           :  1;
     unsigned      dbg_reset_core0                           :  1;
#else    /* Little Endian */
     unsigned      dbg_reset_core0                           :  1;
     unsigned      dbg_reset_core1                           :  1;
     unsigned      dbg_reset_core2                           :  1;
     unsigned      dbg_reset_core3                           :  1;
     unsigned      dbg_reset_core4                           :  1;
     unsigned      dbg_reset_core5                           :  1;
     unsigned      dbg_reset_core6                           :  1;
     unsigned      dbg_reset_core7                           :  1;
     unsigned      dbg_reset_core8                           :  1;
     unsigned      dbg_reset_core9                           :  1;
     unsigned      dbg_reset_core10                          :  1;
     unsigned      dbg_reset_core11                          :  1;
     unsigned      dbg_reset_core12                          :  1;
     unsigned      dbg_reset_core13                          :  1;
     unsigned      dbg_reset_core14                          :  1;
     unsigned      dbg_reset_core15                          :  1;
     unsigned      dbg_reset_core16                          :  1;
     unsigned      dbg_reset_core17                          :  1;
     unsigned      dbg_reset_core18                          :  1;
     unsigned      dbg_reset_core19                          :  1;
     unsigned      dbg_reset_core20                          :  1;
     unsigned      dbg_reset_core21                          :  1;
     unsigned      dbg_reset_core22                          :  1;
     unsigned      dbg_reset_core23                          :  1;
     unsigned      dbg_reset_core24                          :  1;
     unsigned      dbg_reset_core25                          :  1;
     unsigned      dbg_reset_core26                          :  1;
     unsigned      dbg_reset_core27                          :  1;
     unsigned      dbg_reset_core28                          :  1;
     unsigned      dbg_reset_core29                          :  1;
     unsigned      dbg_reset_core30                          :  1;
     unsigned      dbg_reset_core31                          :  1;
#endif
} ncp_syscon_core_dbg_reset_status_force_r_xlf_t;

/*! @struct ncp_syscon_core_warm_reset_status_r_xlf_t
 *  @brief Core Warm Reset Status Register
 *  @details This register holds the sticky status of any warm reset bits having been asserted.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_core_warm_reset_status_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core31 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU31. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core30 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU30. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core29 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU29. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core28 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU28. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core27 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU27. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core26 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU26. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core25 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU25. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core24 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU24. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core23 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU23. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core22 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU22. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core21 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU21. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core20 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU20. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core19 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU19. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core18 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU18. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core17 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU17. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core16 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU16. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core15 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU15. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core14 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU14. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core13 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU13. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core12 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU12. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core11 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU11. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core10 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU10. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core9 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU9. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core8 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU8. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU7. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU6. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU5. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU4. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU3. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU2. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU1. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU0. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_core_warm_reset_status_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      warm_reset_core31                         :  1;
     unsigned      warm_reset_core30                         :  1;
     unsigned      warm_reset_core29                         :  1;
     unsigned      warm_reset_core28                         :  1;
     unsigned      warm_reset_core27                         :  1;
     unsigned      warm_reset_core26                         :  1;
     unsigned      warm_reset_core25                         :  1;
     unsigned      warm_reset_core24                         :  1;
     unsigned      warm_reset_core23                         :  1;
     unsigned      warm_reset_core22                         :  1;
     unsigned      warm_reset_core21                         :  1;
     unsigned      warm_reset_core20                         :  1;
     unsigned      warm_reset_core19                         :  1;
     unsigned      warm_reset_core18                         :  1;
     unsigned      warm_reset_core17                         :  1;
     unsigned      warm_reset_core16                         :  1;
     unsigned      warm_reset_core15                         :  1;
     unsigned      warm_reset_core14                         :  1;
     unsigned      warm_reset_core13                         :  1;
     unsigned      warm_reset_core12                         :  1;
     unsigned      warm_reset_core11                         :  1;
     unsigned      warm_reset_core10                         :  1;
     unsigned      warm_reset_core9                          :  1;
     unsigned      warm_reset_core8                          :  1;
     unsigned      warm_reset_core7                          :  1;
     unsigned      warm_reset_core6                          :  1;
     unsigned      warm_reset_core5                          :  1;
     unsigned      warm_reset_core4                          :  1;
     unsigned      warm_reset_core3                          :  1;
     unsigned      warm_reset_core2                          :  1;
     unsigned      warm_reset_core1                          :  1;
     unsigned      warm_reset_core0                          :  1;
#else    /* Little Endian */
     unsigned      warm_reset_core0                          :  1;
     unsigned      warm_reset_core1                          :  1;
     unsigned      warm_reset_core2                          :  1;
     unsigned      warm_reset_core3                          :  1;
     unsigned      warm_reset_core4                          :  1;
     unsigned      warm_reset_core5                          :  1;
     unsigned      warm_reset_core6                          :  1;
     unsigned      warm_reset_core7                          :  1;
     unsigned      warm_reset_core8                          :  1;
     unsigned      warm_reset_core9                          :  1;
     unsigned      warm_reset_core10                         :  1;
     unsigned      warm_reset_core11                         :  1;
     unsigned      warm_reset_core12                         :  1;
     unsigned      warm_reset_core13                         :  1;
     unsigned      warm_reset_core14                         :  1;
     unsigned      warm_reset_core15                         :  1;
     unsigned      warm_reset_core16                         :  1;
     unsigned      warm_reset_core17                         :  1;
     unsigned      warm_reset_core18                         :  1;
     unsigned      warm_reset_core19                         :  1;
     unsigned      warm_reset_core20                         :  1;
     unsigned      warm_reset_core21                         :  1;
     unsigned      warm_reset_core22                         :  1;
     unsigned      warm_reset_core23                         :  1;
     unsigned      warm_reset_core24                         :  1;
     unsigned      warm_reset_core25                         :  1;
     unsigned      warm_reset_core26                         :  1;
     unsigned      warm_reset_core27                         :  1;
     unsigned      warm_reset_core28                         :  1;
     unsigned      warm_reset_core29                         :  1;
     unsigned      warm_reset_core30                         :  1;
     unsigned      warm_reset_core31                         :  1;
#endif
} ncp_syscon_core_warm_reset_status_r_xlf_t;

/*! @struct ncp_syscon_core_warm_reset_status_force_r_xlf_t
 *  @brief Core Warm Reset Status Force Register
 *  @details This address is an alias for the Core Warm Reset Status register that allows normal CFG R/W (as opposed to
	the Clear-On-Write-One behavior if the Core Warm Reset Status register address is used).  This allows CFG
	to set bits for testing purposes.  Reading this address returns the current value of the Core Warm Reset Status register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_core_warm_reset_status_force_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core31 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU31. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core30 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU30. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core29 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU29. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core28 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU28. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core27 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU27. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core26 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU26. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core25 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU25. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core24 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU24. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core23 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU23. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core22 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU22. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core21 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU21. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core20 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU20. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core19 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU19. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core18 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU18. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core17 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU17. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core16 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU16. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core15 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU15. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core14 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU14. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core13 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU13. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core12 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU12. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core11 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU11. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core10 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU10. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core9 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU9. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core8 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU8. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU7. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU6. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU5. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU4. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU3. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU2. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU1. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Core warm reset was asserted for CPU0. This bit is
 *        cleared by a pin or system reset.
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_core_warm_reset_status_force_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      warm_reset_core31                         :  1;
     unsigned      warm_reset_core30                         :  1;
     unsigned      warm_reset_core29                         :  1;
     unsigned      warm_reset_core28                         :  1;
     unsigned      warm_reset_core27                         :  1;
     unsigned      warm_reset_core26                         :  1;
     unsigned      warm_reset_core25                         :  1;
     unsigned      warm_reset_core24                         :  1;
     unsigned      warm_reset_core23                         :  1;
     unsigned      warm_reset_core22                         :  1;
     unsigned      warm_reset_core21                         :  1;
     unsigned      warm_reset_core20                         :  1;
     unsigned      warm_reset_core19                         :  1;
     unsigned      warm_reset_core18                         :  1;
     unsigned      warm_reset_core17                         :  1;
     unsigned      warm_reset_core16                         :  1;
     unsigned      warm_reset_core15                         :  1;
     unsigned      warm_reset_core14                         :  1;
     unsigned      warm_reset_core13                         :  1;
     unsigned      warm_reset_core12                         :  1;
     unsigned      warm_reset_core11                         :  1;
     unsigned      warm_reset_core10                         :  1;
     unsigned      warm_reset_core9                          :  1;
     unsigned      warm_reset_core8                          :  1;
     unsigned      warm_reset_core7                          :  1;
     unsigned      warm_reset_core6                          :  1;
     unsigned      warm_reset_core5                          :  1;
     unsigned      warm_reset_core4                          :  1;
     unsigned      warm_reset_core3                          :  1;
     unsigned      warm_reset_core2                          :  1;
     unsigned      warm_reset_core1                          :  1;
     unsigned      warm_reset_core0                          :  1;
#else    /* Little Endian */
     unsigned      warm_reset_core0                          :  1;
     unsigned      warm_reset_core1                          :  1;
     unsigned      warm_reset_core2                          :  1;
     unsigned      warm_reset_core3                          :  1;
     unsigned      warm_reset_core4                          :  1;
     unsigned      warm_reset_core5                          :  1;
     unsigned      warm_reset_core6                          :  1;
     unsigned      warm_reset_core7                          :  1;
     unsigned      warm_reset_core8                          :  1;
     unsigned      warm_reset_core9                          :  1;
     unsigned      warm_reset_core10                         :  1;
     unsigned      warm_reset_core11                         :  1;
     unsigned      warm_reset_core12                         :  1;
     unsigned      warm_reset_core13                         :  1;
     unsigned      warm_reset_core14                         :  1;
     unsigned      warm_reset_core15                         :  1;
     unsigned      warm_reset_core16                         :  1;
     unsigned      warm_reset_core17                         :  1;
     unsigned      warm_reset_core18                         :  1;
     unsigned      warm_reset_core19                         :  1;
     unsigned      warm_reset_core20                         :  1;
     unsigned      warm_reset_core21                         :  1;
     unsigned      warm_reset_core22                         :  1;
     unsigned      warm_reset_core23                         :  1;
     unsigned      warm_reset_core24                         :  1;
     unsigned      warm_reset_core25                         :  1;
     unsigned      warm_reset_core26                         :  1;
     unsigned      warm_reset_core27                         :  1;
     unsigned      warm_reset_core28                         :  1;
     unsigned      warm_reset_core29                         :  1;
     unsigned      warm_reset_core30                         :  1;
     unsigned      warm_reset_core31                         :  1;
#endif
} ncp_syscon_core_warm_reset_status_force_r_xlf_t;

/*! @struct ncp_syscon_core_nstim_reset_status_r_xlf_t
 *  @brief Core NS Timer Reset Status Register
 *  @details This register holds the sticky status of any reset bits having been asserted due to a NS timer expiration.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_core_nstim_reset_status_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core31 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU31. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core30 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU30. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core29 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU29. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core28 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU28. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core27 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU27. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core26 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU26. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core25 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU25. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core24 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU24. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core23 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU23. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core22 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU22. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core21 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU21. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core20 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU20. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core19 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU19. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core18 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU18. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core17 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU17. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core16 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU16. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core15 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU15. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core14 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU14. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core13 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU13. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core12 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU12. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core11 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU11. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core10 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU10. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core9 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU9. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core8 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU8. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU7. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU6. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU5. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU4. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU3. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU2. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU1. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU0. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_core_nstim_reset_status_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      warm_reset_core31                         :  1;
     unsigned      warm_reset_core30                         :  1;
     unsigned      warm_reset_core29                         :  1;
     unsigned      warm_reset_core28                         :  1;
     unsigned      warm_reset_core27                         :  1;
     unsigned      warm_reset_core26                         :  1;
     unsigned      warm_reset_core25                         :  1;
     unsigned      warm_reset_core24                         :  1;
     unsigned      warm_reset_core23                         :  1;
     unsigned      warm_reset_core22                         :  1;
     unsigned      warm_reset_core21                         :  1;
     unsigned      warm_reset_core20                         :  1;
     unsigned      warm_reset_core19                         :  1;
     unsigned      warm_reset_core18                         :  1;
     unsigned      warm_reset_core17                         :  1;
     unsigned      warm_reset_core16                         :  1;
     unsigned      warm_reset_core15                         :  1;
     unsigned      warm_reset_core14                         :  1;
     unsigned      warm_reset_core13                         :  1;
     unsigned      warm_reset_core12                         :  1;
     unsigned      warm_reset_core11                         :  1;
     unsigned      warm_reset_core10                         :  1;
     unsigned      warm_reset_core9                          :  1;
     unsigned      warm_reset_core8                          :  1;
     unsigned      warm_reset_core7                          :  1;
     unsigned      warm_reset_core6                          :  1;
     unsigned      warm_reset_core5                          :  1;
     unsigned      warm_reset_core4                          :  1;
     unsigned      warm_reset_core3                          :  1;
     unsigned      warm_reset_core2                          :  1;
     unsigned      warm_reset_core1                          :  1;
     unsigned      warm_reset_core0                          :  1;
#else    /* Little Endian */
     unsigned      warm_reset_core0                          :  1;
     unsigned      warm_reset_core1                          :  1;
     unsigned      warm_reset_core2                          :  1;
     unsigned      warm_reset_core3                          :  1;
     unsigned      warm_reset_core4                          :  1;
     unsigned      warm_reset_core5                          :  1;
     unsigned      warm_reset_core6                          :  1;
     unsigned      warm_reset_core7                          :  1;
     unsigned      warm_reset_core8                          :  1;
     unsigned      warm_reset_core9                          :  1;
     unsigned      warm_reset_core10                         :  1;
     unsigned      warm_reset_core11                         :  1;
     unsigned      warm_reset_core12                         :  1;
     unsigned      warm_reset_core13                         :  1;
     unsigned      warm_reset_core14                         :  1;
     unsigned      warm_reset_core15                         :  1;
     unsigned      warm_reset_core16                         :  1;
     unsigned      warm_reset_core17                         :  1;
     unsigned      warm_reset_core18                         :  1;
     unsigned      warm_reset_core19                         :  1;
     unsigned      warm_reset_core20                         :  1;
     unsigned      warm_reset_core21                         :  1;
     unsigned      warm_reset_core22                         :  1;
     unsigned      warm_reset_core23                         :  1;
     unsigned      warm_reset_core24                         :  1;
     unsigned      warm_reset_core25                         :  1;
     unsigned      warm_reset_core26                         :  1;
     unsigned      warm_reset_core27                         :  1;
     unsigned      warm_reset_core28                         :  1;
     unsigned      warm_reset_core29                         :  1;
     unsigned      warm_reset_core30                         :  1;
     unsigned      warm_reset_core31                         :  1;
#endif
} ncp_syscon_core_nstim_reset_status_r_xlf_t;

/*! @struct ncp_syscon_core_nstim_reset_status_force_r_xlf_t
 *  @brief Core NS Timer Reset Status Force Register
 *  @details This address is an alias for the Core NS Timer Reset Status register that allows normal CFG R/W (as opposed to the
	Clear-On-Write-One behavior if the Core NS Timer Reset Status register address is used).  This allows CFG to set bits
	for testing purposes.  Reading this address returns the current value of the Core NS Timer Reset Status register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_core_nstim_reset_status_force_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core31 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU31. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core30 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU30. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core29 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU29. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core28 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU28. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core27 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU27. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core26 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU26. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core25 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU25. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core24 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU24. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core23 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU23. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core22 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU22. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core21 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU21. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core20 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU20. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core19 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU19. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core18 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU18. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core17 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU17. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core16 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU16. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core15 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU15. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core14 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU14. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core13 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU13. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core12 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU12. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core11 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU11. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core10 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU10. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core9 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU9. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core8 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU8. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU7. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU6. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU5. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU4. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU3. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU2. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU1. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warm_reset_core0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Core NS timer reset was asserted for CPU0. This bit
 *        is cleared by a pin or system reset.
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_core_nstim_reset_status_force_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      warm_reset_core31                         :  1;
     unsigned      warm_reset_core30                         :  1;
     unsigned      warm_reset_core29                         :  1;
     unsigned      warm_reset_core28                         :  1;
     unsigned      warm_reset_core27                         :  1;
     unsigned      warm_reset_core26                         :  1;
     unsigned      warm_reset_core25                         :  1;
     unsigned      warm_reset_core24                         :  1;
     unsigned      warm_reset_core23                         :  1;
     unsigned      warm_reset_core22                         :  1;
     unsigned      warm_reset_core21                         :  1;
     unsigned      warm_reset_core20                         :  1;
     unsigned      warm_reset_core19                         :  1;
     unsigned      warm_reset_core18                         :  1;
     unsigned      warm_reset_core17                         :  1;
     unsigned      warm_reset_core16                         :  1;
     unsigned      warm_reset_core15                         :  1;
     unsigned      warm_reset_core14                         :  1;
     unsigned      warm_reset_core13                         :  1;
     unsigned      warm_reset_core12                         :  1;
     unsigned      warm_reset_core11                         :  1;
     unsigned      warm_reset_core10                         :  1;
     unsigned      warm_reset_core9                          :  1;
     unsigned      warm_reset_core8                          :  1;
     unsigned      warm_reset_core7                          :  1;
     unsigned      warm_reset_core6                          :  1;
     unsigned      warm_reset_core5                          :  1;
     unsigned      warm_reset_core4                          :  1;
     unsigned      warm_reset_core3                          :  1;
     unsigned      warm_reset_core2                          :  1;
     unsigned      warm_reset_core1                          :  1;
     unsigned      warm_reset_core0                          :  1;
#else    /* Little Endian */
     unsigned      warm_reset_core0                          :  1;
     unsigned      warm_reset_core1                          :  1;
     unsigned      warm_reset_core2                          :  1;
     unsigned      warm_reset_core3                          :  1;
     unsigned      warm_reset_core4                          :  1;
     unsigned      warm_reset_core5                          :  1;
     unsigned      warm_reset_core6                          :  1;
     unsigned      warm_reset_core7                          :  1;
     unsigned      warm_reset_core8                          :  1;
     unsigned      warm_reset_core9                          :  1;
     unsigned      warm_reset_core10                         :  1;
     unsigned      warm_reset_core11                         :  1;
     unsigned      warm_reset_core12                         :  1;
     unsigned      warm_reset_core13                         :  1;
     unsigned      warm_reset_core14                         :  1;
     unsigned      warm_reset_core15                         :  1;
     unsigned      warm_reset_core16                         :  1;
     unsigned      warm_reset_core17                         :  1;
     unsigned      warm_reset_core18                         :  1;
     unsigned      warm_reset_core19                         :  1;
     unsigned      warm_reset_core20                         :  1;
     unsigned      warm_reset_core21                         :  1;
     unsigned      warm_reset_core22                         :  1;
     unsigned      warm_reset_core23                         :  1;
     unsigned      warm_reset_core24                         :  1;
     unsigned      warm_reset_core25                         :  1;
     unsigned      warm_reset_core26                         :  1;
     unsigned      warm_reset_core27                         :  1;
     unsigned      warm_reset_core28                         :  1;
     unsigned      warm_reset_core29                         :  1;
     unsigned      warm_reset_core30                         :  1;
     unsigned      warm_reset_core31                         :  1;
#endif
} ncp_syscon_core_nstim_reset_status_force_r_xlf_t;

/*! @struct ncp_syscon_baddr_r_xlf_t
 *  @brief CPU Reset Vector Base Address Register
 *  @details This value is used to set bits [23:16] of the CPU's reset vector base address.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_baddr_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param baddr </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Base address used for RVBARADD[23:16] </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_baddr_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      baddr                                     :  8;
#else    /* Little Endian */
     unsigned      baddr                                     :  8;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_baddr_r_xlf_t;

/*! @struct ncp_syscon_key_r_xlf_t
 *  @brief Critical Control Write Key Register
 *  @details This register contains the key that must be written to the value 8'hAB before writes can be done to certain
	other critical system control registers.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_key_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param write_key </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Critical Control Write Key. Must be 0xAB to write
 *        critical control registers
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_key_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      write_key                                 :  8;
#else    /* Little Endian */
     unsigned      write_key                                 :  8;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_key_r_xlf_t;

/*! @struct ncp_syscon_lor_r_xlf_t
 *  @brief Latch-On-Reset Configuration Register
 *  @details This register contains control fields that are loaded from the chip pins only on a system reset (latch on reset).
        They are not modified by a chip reset and can be changed by doing a CFG write before a chip reset to have the
        newly written values take effect.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_lor_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param pur_devid </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> On System Reset, pur_devid is asynchronously loaded
 *        with the value determined by the pullup or pulldown
 *        resistors on the TESTO_DATA3126_PUR_DEVID pins.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pur_cfg </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> On System Reset, pur_cfg is asynchronously loaded
 *        with the value determined by the pullup or pulldown
 *        resistors on the TESTO_DATA2519_PUR_CFG pins.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bootmode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> On System Reset, bootMode is asynchronously loaded
 *        with the value determined by the pullup or pulldown
 *        resistor on the TESTO_DATA18_BOOT_MODE pin and controls
 *        the boot mode: 0: Boot using the internal ARM subsystem.
 *        1: Boot using an external processor.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param boottarget </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> On System Reset, bootTarget is asynchronously loaded
 *        with the value determined by the pullup or pulldown
 *         resistor on the TESTO_DATA17_BOOT_TARGET pin and
 *        selects which system memory map is used for the ARM
 *        subsystem:  0: Use mission mode system memory map
 *        with reset vector=0x00_0000_0000, PERIPHBASE=0x20_0100_0000
 *         1: Use powerup system memory map with reset_vector=0x00_FFFF_0000,
 *        PERIPHBASE=0x00_0100_0000
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_lor_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 17;
     unsigned      pur_devid                                 :  6;
     unsigned      pur_cfg                                   :  7;
     unsigned      bootmode                                  :  1;
     unsigned      boottarget                                :  1;
#else    /* Little Endian */
     unsigned      boottarget                                :  1;
     unsigned      bootmode                                  :  1;
     unsigned      pur_cfg                                   :  7;
     unsigned      pur_devid                                 :  6;
     unsigned      reserved0                                 : 17;
#endif
} ncp_syscon_lor_r_xlf_t;

/*! @struct ncp_syscon_reset_ctl_r_xlf_t
 *  @brief Reset Control Register
 *  @details Setting bits in this register generate a system, chip, or fabric reset or control how a watchdog timer expiration is treated.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_reset_ctl_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param resetfes </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> If set, hold the FES in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param debug_tap_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> If set, disables boundary scan access to the SERDES
 *        PHYs. This bit overrides the functionality of the
 *         debug_tap_enable bit and, once set, can only be
 *        reset by a chip reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param debug_tap_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> If set, allows boundary scan access to the SERDES
 *        PHYs.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_nowait </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> If set, chip or system resets generated by writing
 *        the resetChip or resetSystem bits assert immediately
 *         instead of waiting 1K clocks before asserting.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cdbgrstreq_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> If set, allows a Coresight debug logic reset request
 *        to generate a reset of the debug logic.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warmrst_stretch </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> The number of clocks to stretch any syscon generated
 *        warm reset pulse.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param coresight_ap_deviceen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Enable AP mode for coresight. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param coresight_ls_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Enable light sleep mode for the coresight RAMs. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param coresight_ds_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Enable deep sleep mode for the coresight RAMs. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param coresight_sd_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enable shutdown mode for the coresight RAMs. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_debug_apb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> When a 1 is written to this bit, the coresight reset_debug_apb_n
 *        is asserted unconditionally to hold  the APB master
 *        in reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_debug_ccn </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> When a 1 is written to this bit, the coresight reset_debug_ccn_n
 *        is asserted unconditionally to hold  the fabric
 *        trace logic in reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_debug_dap </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> When a 1 is written to this bit, the coresight reset_debug_dap_n
 *        is asserted unconditionally to hold  the DAP memory-mapped
 *        interface logic in reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_debug_soc </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> When a 1 is written to this bit, the coresight reset_debug_soc_n
 *        is asserted unconditionally to hold  the system
 *        trace, trigger and buffer interface logic in reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param etb_lsleep_disable_dt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Disable light sleep mode for the coresight DT RAMs
 *        (RAMs are in light sleep after a chip reset).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param etb_lsleep_disable_stm </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Disable light sleep mode for the coresight STM RAMs
 *        (RAMs are in light sleep after a chip reset).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wd1_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> When a 1 is written to this bit, a watchdog timer
 *        1 expiration is enabled to cause a system or chip
 *        reset  depending on the setting of the wd1_reset_select
 *        bit.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wd0_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> When a 1 is written to this bit, a watchdog timer
 *        0 expiration is enabled to cause a system or chip
 *        reset  depending on the setting of the wd0_reset_select
 *        bit.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wd1_reset_select </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Watchdog Timer 1 reset select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wd0_reset_select </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Watchdog Timer 0 reset select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param nstimrstreq_chip_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> If set, causes the assertion of any enabled NS Timer
 *        expiration to generate a chip reset instead  of
 *        just a cpu reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param warmrstreq_chip_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> If set, causes the assertion of any enabled WARMRSTREQ
 *        bit to generate a chip reset instead  of just a
 *        cpu reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq_chip_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> If set, causes the assertion of any enabled DBGRSTREQ
 *        bit to generate a chip reset instead  of just a
 *        cpu reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param resetzero </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> When a leading edge is detected on this bit, a zeroize
 *        reset is generated and the resets for  all of the
 *        EIOAs in the system with embedded MACSECs are also
 *        asserted. This bit is cleared after  the resets
 *        are generated.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param resetchip </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> When a 1 is written to this bit, a chip reset sequence
 *        is generated. If the reset_nowait bit is also  set,
 *        the sequence starts immediately, otherise we wait
 *        1K clocks before initiating the sequence.  This
 *        bit is cleared after the reset is generated.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param resetsystem </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> When a 1 is written to this bit, a system reset is
 *        generated. If the reset_nowait bit is also set, the
 *        sequence starts immediately, otherise we wait 1K clocks
 *        before initiating the sequence.  This bit is cleared
 *        after the reset is generated.
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_reset_ctl_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      resetfes                                  :  1;
     unsigned      debug_tap_disable                         :  1;
     unsigned      debug_tap_enable                          :  1;
     unsigned      reset_nowait                              :  1;
     unsigned      cdbgrstreq_enable                         :  1;
     unsigned      warmrst_stretch                           :  6;
     unsigned      coresight_ap_deviceen                     :  1;
     unsigned      coresight_ls_enable                       :  1;
     unsigned      coresight_ds_enable                       :  1;
     unsigned      coresight_sd_enable                       :  1;
     unsigned      hold_debug_apb                            :  1;
     unsigned      hold_debug_ccn                            :  1;
     unsigned      hold_debug_dap                            :  1;
     unsigned      hold_debug_soc                            :  1;
     unsigned      etb_lsleep_disable_dt                     :  1;
     unsigned      etb_lsleep_disable_stm                    :  1;
     unsigned      wd1_reset_enable                          :  1;
     unsigned      wd0_reset_enable                          :  1;
     unsigned      wd1_reset_select                          :  1;
     unsigned      wd0_reset_select                          :  1;
     unsigned      nstimrstreq_chip_enable                   :  1;
     unsigned      warmrstreq_chip_enable                    :  1;
     unsigned      dbgrstreq_chip_enable                     :  1;
     unsigned      resetzero                                 :  1;
     unsigned      resetchip                                 :  1;
     unsigned      resetsystem                               :  1;
#else    /* Little Endian */
     unsigned      resetsystem                               :  1;
     unsigned      resetchip                                 :  1;
     unsigned      resetzero                                 :  1;
     unsigned      dbgrstreq_chip_enable                     :  1;
     unsigned      warmrstreq_chip_enable                    :  1;
     unsigned      nstimrstreq_chip_enable                   :  1;
     unsigned      wd0_reset_select                          :  1;
     unsigned      wd1_reset_select                          :  1;
     unsigned      wd0_reset_enable                          :  1;
     unsigned      wd1_reset_enable                          :  1;
     unsigned      etb_lsleep_disable_stm                    :  1;
     unsigned      etb_lsleep_disable_dt                     :  1;
     unsigned      hold_debug_soc                            :  1;
     unsigned      hold_debug_dap                            :  1;
     unsigned      hold_debug_ccn                            :  1;
     unsigned      hold_debug_apb                            :  1;
     unsigned      coresight_sd_enable                       :  1;
     unsigned      coresight_ds_enable                       :  1;
     unsigned      coresight_ls_enable                       :  1;
     unsigned      coresight_ap_deviceen                     :  1;
     unsigned      warmrst_stretch                           :  6;
     unsigned      cdbgrstreq_enable                         :  1;
     unsigned      reset_nowait                              :  1;
     unsigned      debug_tap_enable                          :  1;
     unsigned      debug_tap_disable                         :  1;
     unsigned      resetfes                                  :  1;
     unsigned      reserved0                                 :  1;
#endif
} ncp_syscon_reset_ctl_r_xlf_t;

/*! @struct ncp_syscon_reset_cpu_r_xlf_t
 *  @brief Reset CPU Register
 *  @details Setting a bit in this register when it was previously a 0 causes a reset sequence for the associated CPU core, and
	possibly its associated local debug, global debug, and L2 logic (see the Allow PTM Reset, Allow L2 Reset, and
	Allow Debug Reset registers for details). 
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_reset_cpu_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu31 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Enable CPU31 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu30 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Enable CPU30 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu29 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Enable CPU29 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu28 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Enable CPU28 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu27 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Enable CPU27 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu26 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Enable CPU26 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu25 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Enable CPU25 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu24 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Enable CPU24 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu23 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Enable CPU23 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu22 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Enable CPU22 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu21 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Enable CPU21 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu20 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Enable CPU20 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu19 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Enable CPU19 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu18 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Enable CPU18 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu17 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Enable CPU17 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu16 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enable CPU16 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu15 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Enable CPU15 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu14 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Enable CPU14 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu13 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Enable CPU13 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu12 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Enable CPU12 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu11 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Enable CPU11 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu10 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Enable CPU10 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu9 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Enable CPU9 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu8 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enable CPU8 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Enable CPU7 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Enable CPU6 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Enable CPU5 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Enable CPU4 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Enable CPU3 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Enable CPU2 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Enable CPU1 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_cpu0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enable CPU0 reset sequence on leading edge. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_reset_cpu_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reset_cpu31                               :  1;
     unsigned      reset_cpu30                               :  1;
     unsigned      reset_cpu29                               :  1;
     unsigned      reset_cpu28                               :  1;
     unsigned      reset_cpu27                               :  1;
     unsigned      reset_cpu26                               :  1;
     unsigned      reset_cpu25                               :  1;
     unsigned      reset_cpu24                               :  1;
     unsigned      reset_cpu23                               :  1;
     unsigned      reset_cpu22                               :  1;
     unsigned      reset_cpu21                               :  1;
     unsigned      reset_cpu20                               :  1;
     unsigned      reset_cpu19                               :  1;
     unsigned      reset_cpu18                               :  1;
     unsigned      reset_cpu17                               :  1;
     unsigned      reset_cpu16                               :  1;
     unsigned      reset_cpu15                               :  1;
     unsigned      reset_cpu14                               :  1;
     unsigned      reset_cpu13                               :  1;
     unsigned      reset_cpu12                               :  1;
     unsigned      reset_cpu11                               :  1;
     unsigned      reset_cpu10                               :  1;
     unsigned      reset_cpu9                                :  1;
     unsigned      reset_cpu8                                :  1;
     unsigned      reset_cpu7                                :  1;
     unsigned      reset_cpu6                                :  1;
     unsigned      reset_cpu5                                :  1;
     unsigned      reset_cpu4                                :  1;
     unsigned      reset_cpu3                                :  1;
     unsigned      reset_cpu2                                :  1;
     unsigned      reset_cpu1                                :  1;
     unsigned      reset_cpu0                                :  1;
#else    /* Little Endian */
     unsigned      reset_cpu0                                :  1;
     unsigned      reset_cpu1                                :  1;
     unsigned      reset_cpu2                                :  1;
     unsigned      reset_cpu3                                :  1;
     unsigned      reset_cpu4                                :  1;
     unsigned      reset_cpu5                                :  1;
     unsigned      reset_cpu6                                :  1;
     unsigned      reset_cpu7                                :  1;
     unsigned      reset_cpu8                                :  1;
     unsigned      reset_cpu9                                :  1;
     unsigned      reset_cpu10                               :  1;
     unsigned      reset_cpu11                               :  1;
     unsigned      reset_cpu12                               :  1;
     unsigned      reset_cpu13                               :  1;
     unsigned      reset_cpu14                               :  1;
     unsigned      reset_cpu15                               :  1;
     unsigned      reset_cpu16                               :  1;
     unsigned      reset_cpu17                               :  1;
     unsigned      reset_cpu18                               :  1;
     unsigned      reset_cpu19                               :  1;
     unsigned      reset_cpu20                               :  1;
     unsigned      reset_cpu21                               :  1;
     unsigned      reset_cpu22                               :  1;
     unsigned      reset_cpu23                               :  1;
     unsigned      reset_cpu24                               :  1;
     unsigned      reset_cpu25                               :  1;
     unsigned      reset_cpu26                               :  1;
     unsigned      reset_cpu27                               :  1;
     unsigned      reset_cpu28                               :  1;
     unsigned      reset_cpu29                               :  1;
     unsigned      reset_cpu30                               :  1;
     unsigned      reset_cpu31                               :  1;
#endif
} ncp_syscon_reset_cpu_r_xlf_t;

/*! @struct ncp_syscon_hold_cpu_r_xlf_t
 *  @brief Hold CPU Reset Register
 *  @details Setting a bit in this register holds the associated CPU core in reset after a system, chip or fabric reset is deasserted.
	During a system or chip reset, all bits except for the hold_cpu0 bit are set to 1. The hold_cpu0 bit is loaded with the
	value of the BOOT_MODE pin during system reset, or with the value of the bootMode bit in the Latch-On-Reset register
	during a chip reset.
	If the CPU Reset Timer register is enabled either before or after bits are set in this register, the set bits will be
	automatically reset when the CPU Reset Timer counts down to 0.  Note that if the CPU Reset Timer is enabled before
	any bits are set in this register or the Powerup CPU Reset register, then the CPU Reset Timer will not start decrementing
	until at least one bit in either of these registers is set.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_hold_cpu_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu31 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Hold CPU31 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu30 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Hold CPU30 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu29 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Hold CPU29 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu28 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Hold CPU28 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu27 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Hold CPU27 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu26 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Hold CPU26 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu25 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Hold CPU25 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu24 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Hold CPU24 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu23 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Hold CPU23 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu22 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Hold CPU22 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu21 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Hold CPU21 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu20 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Hold CPU20 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu19 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Hold CPU19 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu18 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Hold CPU18 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu17 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Hold CPU17 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu16 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Hold CPU16 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu15 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Hold CPU15 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu14 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Hold CPU14 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu13 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Hold CPU13 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu12 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Hold CPU12 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu11 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Hold CPU11 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu10 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Hold CPU10 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu9 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Hold CPU9 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu8 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Hold CPU8 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Hold CPU7 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Hold CPU6 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Hold CPU5 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Hold CPU4 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Hold CPU3 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Hold CPU2 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Hold CPU1 core in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_cpu0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Hold CPU0 core in reset </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_hold_cpu_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      hold_cpu31                                :  1;
     unsigned      hold_cpu30                                :  1;
     unsigned      hold_cpu29                                :  1;
     unsigned      hold_cpu28                                :  1;
     unsigned      hold_cpu27                                :  1;
     unsigned      hold_cpu26                                :  1;
     unsigned      hold_cpu25                                :  1;
     unsigned      hold_cpu24                                :  1;
     unsigned      hold_cpu23                                :  1;
     unsigned      hold_cpu22                                :  1;
     unsigned      hold_cpu21                                :  1;
     unsigned      hold_cpu20                                :  1;
     unsigned      hold_cpu19                                :  1;
     unsigned      hold_cpu18                                :  1;
     unsigned      hold_cpu17                                :  1;
     unsigned      hold_cpu16                                :  1;
     unsigned      hold_cpu15                                :  1;
     unsigned      hold_cpu14                                :  1;
     unsigned      hold_cpu13                                :  1;
     unsigned      hold_cpu12                                :  1;
     unsigned      hold_cpu11                                :  1;
     unsigned      hold_cpu10                                :  1;
     unsigned      hold_cpu9                                 :  1;
     unsigned      hold_cpu8                                 :  1;
     unsigned      hold_cpu7                                 :  1;
     unsigned      hold_cpu6                                 :  1;
     unsigned      hold_cpu5                                 :  1;
     unsigned      hold_cpu4                                 :  1;
     unsigned      hold_cpu3                                 :  1;
     unsigned      hold_cpu2                                 :  1;
     unsigned      hold_cpu1                                 :  1;
     unsigned      hold_cpu0                                 :  1;
#else    /* Little Endian */
     unsigned      hold_cpu0                                 :  1;
     unsigned      hold_cpu1                                 :  1;
     unsigned      hold_cpu2                                 :  1;
     unsigned      hold_cpu3                                 :  1;
     unsigned      hold_cpu4                                 :  1;
     unsigned      hold_cpu5                                 :  1;
     unsigned      hold_cpu6                                 :  1;
     unsigned      hold_cpu7                                 :  1;
     unsigned      hold_cpu8                                 :  1;
     unsigned      hold_cpu9                                 :  1;
     unsigned      hold_cpu10                                :  1;
     unsigned      hold_cpu11                                :  1;
     unsigned      hold_cpu12                                :  1;
     unsigned      hold_cpu13                                :  1;
     unsigned      hold_cpu14                                :  1;
     unsigned      hold_cpu15                                :  1;
     unsigned      hold_cpu16                                :  1;
     unsigned      hold_cpu17                                :  1;
     unsigned      hold_cpu18                                :  1;
     unsigned      hold_cpu19                                :  1;
     unsigned      hold_cpu20                                :  1;
     unsigned      hold_cpu21                                :  1;
     unsigned      hold_cpu22                                :  1;
     unsigned      hold_cpu23                                :  1;
     unsigned      hold_cpu24                                :  1;
     unsigned      hold_cpu25                                :  1;
     unsigned      hold_cpu26                                :  1;
     unsigned      hold_cpu27                                :  1;
     unsigned      hold_cpu28                                :  1;
     unsigned      hold_cpu29                                :  1;
     unsigned      hold_cpu30                                :  1;
     unsigned      hold_cpu31                                :  1;
#endif
} ncp_syscon_hold_cpu_r_xlf_t;

/*! @struct ncp_syscon_pwrup_cpu_rst_r_xlf_t
 *  @brief Powerup CPU Reset Register
 *  @details If a bit is set, it asserts the nCPUPORESET for the associated CPU.
	If the CPU Reset Timer register is enabled either before or after bits are set in this register, the set bits will be
	automatically reset when the CPU Reset Timer counts down to 0.  Note that if the CPU Reset Timer is enabled before
	any bits are set in this register or the Hold CPU Reset register, then the CPU Reset Timer will not start decrementing
	until at least one bit in either of these registers is set.
	Using the CPU powerdown sequence controlled by the CPU Powerdown Request register will set bits in this register.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwrup_cpu_rst_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param por_core31 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Assert poweron reset for CPU31 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core30 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Assert poweron reset for CPU30 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core29 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Assert poweron reset for CPU29 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core28 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Assert poweron reset for CPU28 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core27 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Assert poweron reset for CPU27 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core26 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Assert poweron reset for CPU26 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core25 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Assert poweron reset for CPU25 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core24 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Assert poweron reset for CPU24 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core23 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Assert poweron reset for CPU23 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core22 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Assert poweron reset for CPU22 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core21 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Assert poweron reset for CPU21 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core20 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Assert poweron reset for CPU20 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core19 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Assert poweron reset for CPU19 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core18 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Assert poweron reset for CPU18 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core17 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Assert poweron reset for CPU17 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core16 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Assert poweron reset for CPU16 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core15 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Assert poweron reset for CPU15 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core14 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Assert poweron reset for CPU14 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core13 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Assert poweron reset for CPU13 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core12 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Assert poweron reset for CPU12 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core11 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Assert poweron reset for CPU11 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core10 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Assert poweron reset for CPU10 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core9 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Assert poweron reset for CPU9 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core8 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Assert poweron reset for CPU8 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Assert poweron reset for CPU7 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Assert poweron reset for CPU6 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Assert poweron reset for CPU5 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Assert poweron reset for CPU4 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Assert poweron reset for CPU3 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Assert poweron reset for CPU2 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Assert poweron reset for CPU1 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param por_core0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Assert poweron reset for CPU0 </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwrup_cpu_rst_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      por_core31                                :  1;
     unsigned      por_core30                                :  1;
     unsigned      por_core29                                :  1;
     unsigned      por_core28                                :  1;
     unsigned      por_core27                                :  1;
     unsigned      por_core26                                :  1;
     unsigned      por_core25                                :  1;
     unsigned      por_core24                                :  1;
     unsigned      por_core23                                :  1;
     unsigned      por_core22                                :  1;
     unsigned      por_core21                                :  1;
     unsigned      por_core20                                :  1;
     unsigned      por_core19                                :  1;
     unsigned      por_core18                                :  1;
     unsigned      por_core17                                :  1;
     unsigned      por_core16                                :  1;
     unsigned      por_core15                                :  1;
     unsigned      por_core14                                :  1;
     unsigned      por_core13                                :  1;
     unsigned      por_core12                                :  1;
     unsigned      por_core11                                :  1;
     unsigned      por_core10                                :  1;
     unsigned      por_core9                                 :  1;
     unsigned      por_core8                                 :  1;
     unsigned      por_core7                                 :  1;
     unsigned      por_core6                                 :  1;
     unsigned      por_core5                                 :  1;
     unsigned      por_core4                                 :  1;
     unsigned      por_core3                                 :  1;
     unsigned      por_core2                                 :  1;
     unsigned      por_core1                                 :  1;
     unsigned      por_core0                                 :  1;
#else    /* Little Endian */
     unsigned      por_core0                                 :  1;
     unsigned      por_core1                                 :  1;
     unsigned      por_core2                                 :  1;
     unsigned      por_core3                                 :  1;
     unsigned      por_core4                                 :  1;
     unsigned      por_core5                                 :  1;
     unsigned      por_core6                                 :  1;
     unsigned      por_core7                                 :  1;
     unsigned      por_core8                                 :  1;
     unsigned      por_core9                                 :  1;
     unsigned      por_core10                                :  1;
     unsigned      por_core11                                :  1;
     unsigned      por_core12                                :  1;
     unsigned      por_core13                                :  1;
     unsigned      por_core14                                :  1;
     unsigned      por_core15                                :  1;
     unsigned      por_core16                                :  1;
     unsigned      por_core17                                :  1;
     unsigned      por_core18                                :  1;
     unsigned      por_core19                                :  1;
     unsigned      por_core20                                :  1;
     unsigned      por_core21                                :  1;
     unsigned      por_core22                                :  1;
     unsigned      por_core23                                :  1;
     unsigned      por_core24                                :  1;
     unsigned      por_core25                                :  1;
     unsigned      por_core26                                :  1;
     unsigned      por_core27                                :  1;
     unsigned      por_core28                                :  1;
     unsigned      por_core29                                :  1;
     unsigned      por_core30                                :  1;
     unsigned      por_core31                                :  1;
#endif
} ncp_syscon_pwrup_cpu_rst_r_xlf_t;

/*! @struct ncp_syscon_hold_l2_r_xlf_t
 *  @brief Hold L2 Reset Register
 *  @details Setting a bit in this register holds the associated CPU cluster's L2 logic in reset.
	Using the CPU powerdown sequence controlled by the CPU Powerdown Request register will set bits in this register.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_hold_l2_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param hold_l27 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Hold CPU cluster7's L2 logic in reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_l26 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Hold CPU cluster6's L2 logic in reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_l25 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Hold CPU cluster5's L2 logic in reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_l24 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Hold CPU cluster4's L2 logic in reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_l23 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Hold CPU cluster3's L2 logic in reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_l22 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Hold CPU cluster2's L2 logic in reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_l21 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Hold CPU cluster1's L2 logic in reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_l20 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Hold CPU cluster0's L2 logic in reset </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_hold_l2_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      hold_l27                                  :  1;
     unsigned      hold_l26                                  :  1;
     unsigned      hold_l25                                  :  1;
     unsigned      hold_l24                                  :  1;
     unsigned      hold_l23                                  :  1;
     unsigned      hold_l22                                  :  1;
     unsigned      hold_l21                                  :  1;
     unsigned      hold_l20                                  :  1;
#else    /* Little Endian */
     unsigned      hold_l20                                  :  1;
     unsigned      hold_l21                                  :  1;
     unsigned      hold_l22                                  :  1;
     unsigned      hold_l23                                  :  1;
     unsigned      hold_l24                                  :  1;
     unsigned      hold_l25                                  :  1;
     unsigned      hold_l26                                  :  1;
     unsigned      hold_l27                                  :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_hold_l2_r_xlf_t;

/*! @struct ncp_syscon_hold_dbg_r_xlf_t
 *  @brief Hold Debug Reset Register
 *  @details Setting a bit in this register holds the associated CPU cluster's debug logic in reset.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_hold_dbg_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param hold_dbg7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Hold CPU cluster7's debug logic in reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_dbg6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Hold CPU cluster6's debug logic in reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_dbg5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Hold CPU cluster5's debug logic in reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_dbg4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Hold CPU cluster4's debug logic in reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_dbg3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Hold CPU cluster3's debug logic in reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_dbg2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Hold CPU cluster2's debug logic in reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_dbg1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Hold CPU cluster1's debug logic in reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_dbg0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Hold CPU cluster0's debug logic in reset </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_hold_dbg_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      hold_dbg7                                 :  1;
     unsigned      hold_dbg6                                 :  1;
     unsigned      hold_dbg5                                 :  1;
     unsigned      hold_dbg4                                 :  1;
     unsigned      hold_dbg3                                 :  1;
     unsigned      hold_dbg2                                 :  1;
     unsigned      hold_dbg1                                 :  1;
     unsigned      hold_dbg0                                 :  1;
#else    /* Little Endian */
     unsigned      hold_dbg0                                 :  1;
     unsigned      hold_dbg1                                 :  1;
     unsigned      hold_dbg2                                 :  1;
     unsigned      hold_dbg3                                 :  1;
     unsigned      hold_dbg4                                 :  1;
     unsigned      hold_dbg5                                 :  1;
     unsigned      hold_dbg6                                 :  1;
     unsigned      hold_dbg7                                 :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_hold_dbg_r_xlf_t;

/*! @struct ncp_syscon_allow_ptm_r_xlf_t
 *  @brief Allow PTM Reset Register
 *  @details If a bit is set, the corresponding CPU's Breakpointing, Watchdog and Trace logic will also be reset whenever
	the corresponding reset_cpu bit from the CPU Reset Register is asserted.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_allow_ptm_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm31 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Allow CPU31's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU31
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm30 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Allow CPU30's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU30
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm29 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Allow CPU29's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU29
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm28 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Allow CPU28's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU28
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm27 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Allow CPU27's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU27
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm26 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Allow CPU26's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU26
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm25 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Allow CPU25's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU25
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm24 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Allow CPU24's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU24
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm23 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Allow CPU23's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU23
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm22 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Allow CPU22's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU22
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm21 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Allow CPU21's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU21
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm20 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Allow CPU20's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU20
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm19 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Allow CPU19's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU19
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm18 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Allow CPU18's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU18
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm17 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Allow CPU17's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU17
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm16 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Allow CPU16's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU16
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm15 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Allow CPU15's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU15
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm14 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Allow CPU14's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU14
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm13 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Allow CPU13's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU13
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm12 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Allow CPU12's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU12
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm11 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Allow CPU11's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU11
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm10 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Allow CPU10's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU10
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm9 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Allow CPU9's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU9
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm8 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allow CPU8's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU8
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Allow CPU7's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU7
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Allow CPU6's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU6
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Allow CPU5's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU5
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Allow CPU4's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU4
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Allow CPU3's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU3
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Allow CPU2's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU2
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Allow CPU1's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU1
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_ptm0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allow CPU0's Breakpoint, Watchdog and Trace logic
 *        to be reset along with CPU0
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_allow_ptm_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      allow_ptm31                               :  1;
     unsigned      allow_ptm30                               :  1;
     unsigned      allow_ptm29                               :  1;
     unsigned      allow_ptm28                               :  1;
     unsigned      allow_ptm27                               :  1;
     unsigned      allow_ptm26                               :  1;
     unsigned      allow_ptm25                               :  1;
     unsigned      allow_ptm24                               :  1;
     unsigned      allow_ptm23                               :  1;
     unsigned      allow_ptm22                               :  1;
     unsigned      allow_ptm21                               :  1;
     unsigned      allow_ptm20                               :  1;
     unsigned      allow_ptm19                               :  1;
     unsigned      allow_ptm18                               :  1;
     unsigned      allow_ptm17                               :  1;
     unsigned      allow_ptm16                               :  1;
     unsigned      allow_ptm15                               :  1;
     unsigned      allow_ptm14                               :  1;
     unsigned      allow_ptm13                               :  1;
     unsigned      allow_ptm12                               :  1;
     unsigned      allow_ptm11                               :  1;
     unsigned      allow_ptm10                               :  1;
     unsigned      allow_ptm9                                :  1;
     unsigned      allow_ptm8                                :  1;
     unsigned      allow_ptm7                                :  1;
     unsigned      allow_ptm6                                :  1;
     unsigned      allow_ptm5                                :  1;
     unsigned      allow_ptm4                                :  1;
     unsigned      allow_ptm3                                :  1;
     unsigned      allow_ptm2                                :  1;
     unsigned      allow_ptm1                                :  1;
     unsigned      allow_ptm0                                :  1;
#else    /* Little Endian */
     unsigned      allow_ptm0                                :  1;
     unsigned      allow_ptm1                                :  1;
     unsigned      allow_ptm2                                :  1;
     unsigned      allow_ptm3                                :  1;
     unsigned      allow_ptm4                                :  1;
     unsigned      allow_ptm5                                :  1;
     unsigned      allow_ptm6                                :  1;
     unsigned      allow_ptm7                                :  1;
     unsigned      allow_ptm8                                :  1;
     unsigned      allow_ptm9                                :  1;
     unsigned      allow_ptm10                               :  1;
     unsigned      allow_ptm11                               :  1;
     unsigned      allow_ptm12                               :  1;
     unsigned      allow_ptm13                               :  1;
     unsigned      allow_ptm14                               :  1;
     unsigned      allow_ptm15                               :  1;
     unsigned      allow_ptm16                               :  1;
     unsigned      allow_ptm17                               :  1;
     unsigned      allow_ptm18                               :  1;
     unsigned      allow_ptm19                               :  1;
     unsigned      allow_ptm20                               :  1;
     unsigned      allow_ptm21                               :  1;
     unsigned      allow_ptm22                               :  1;
     unsigned      allow_ptm23                               :  1;
     unsigned      allow_ptm24                               :  1;
     unsigned      allow_ptm25                               :  1;
     unsigned      allow_ptm26                               :  1;
     unsigned      allow_ptm27                               :  1;
     unsigned      allow_ptm28                               :  1;
     unsigned      allow_ptm29                               :  1;
     unsigned      allow_ptm30                               :  1;
     unsigned      allow_ptm31                               :  1;
#endif
} ncp_syscon_allow_ptm_r_xlf_t;

/*! @struct ncp_syscon_allow_l2_r_xlf_t
 *  @brief Allow L2 Reset Register
 *  @details If a bit is set, the corresponding CPU cluster's L2 will also be reset whenever the corresponding reset_cpu bits from
	the CPU Reset Register are asserted together for all four CPUs that are part of that cluster.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_allow_l2_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param allow_l27 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Allow CPU cluster 7's L2 to be reset when CPU31-28
 *        are all being reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_l26 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Allow CPU cluster 6's L2 to be reset when CPU27-24
 *        are all being reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_l25 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Allow CPU cluster 5's L2 to be reset when CPU23-20
 *        are all being reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_l24 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Allow CPU cluster 4's L2 to be reset when CPU19-16
 *        are all being reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_l23 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Allow CPU cluster 3's L2 to be reset when CPU15-12
 *        are all being reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_l22 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Allow CPU cluster 2's L2 to be reset when CPU11-8
 *        are all being reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_l21 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Allow CPU cluster 1's L2 to be reset when CPU7-4 are
 *        all being reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_l20 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allow CPU cluster 0's L2 to be reset when CPU3-0 are
 *        all being reset.
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_allow_l2_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      allow_l27                                 :  1;
     unsigned      allow_l26                                 :  1;
     unsigned      allow_l25                                 :  1;
     unsigned      allow_l24                                 :  1;
     unsigned      allow_l23                                 :  1;
     unsigned      allow_l22                                 :  1;
     unsigned      allow_l21                                 :  1;
     unsigned      allow_l20                                 :  1;
#else    /* Little Endian */
     unsigned      allow_l20                                 :  1;
     unsigned      allow_l21                                 :  1;
     unsigned      allow_l22                                 :  1;
     unsigned      allow_l23                                 :  1;
     unsigned      allow_l24                                 :  1;
     unsigned      allow_l25                                 :  1;
     unsigned      allow_l26                                 :  1;
     unsigned      allow_l27                                 :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_allow_l2_r_xlf_t;

/*! @struct ncp_syscon_allow_dbg_r_xlf_t
 *  @brief Allow Debug Reset Register
 *  @details If a bit is set, the corresponding CPU cluster's shared debug and cross trigger logic will also be reset whenever
	a corresponding reset_cpu bit from the CPU Reset Register is asserted for any CPU that is part of that cluster.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_allow_dbg_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param allow_dbg7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Allow CPU cluster 7's shared debug and cross trigger
 *        logic to be reset when any CPU31-28 is being reset
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_dbg6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Allow CPU cluster 6's shared debug and cross trigger
 *        logic to be reset when any CPU27-24 is being reset
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_dbg5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Allow CPU cluster 5's shared debug and cross trigger
 *        logic to be reset when any CPU23-20 is being reset
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_dbg4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Allow CPU cluster 4's shared debug and cross trigger
 *        logic to be reset when any CPU19-16 is being reset
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_dbg3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Allow CPU cluster 3's shared debug and cross trigger
 *        logic to be reset when any CPU15-12 is being reset
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_dbg2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Allow CPU cluster 2's shared debug and cross trigger
 *        logic to be reset when any CPU11-8 is being reset
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_dbg1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Allow CPU cluster 1's shared debug and cross trigger
 *        logic to be reset when any CPU7-4 is being reset
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_dbg0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allow CPU cluster 0's shared debug and cross trigger
 *        logic to be reset when any CPU3-0 is being reset
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_allow_dbg_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      allow_dbg7                                :  1;
     unsigned      allow_dbg6                                :  1;
     unsigned      allow_dbg5                                :  1;
     unsigned      allow_dbg4                                :  1;
     unsigned      allow_dbg3                                :  1;
     unsigned      allow_dbg2                                :  1;
     unsigned      allow_dbg1                                :  1;
     unsigned      allow_dbg0                                :  1;
#else    /* Little Endian */
     unsigned      allow_dbg0                                :  1;
     unsigned      allow_dbg1                                :  1;
     unsigned      allow_dbg2                                :  1;
     unsigned      allow_dbg3                                :  1;
     unsigned      allow_dbg4                                :  1;
     unsigned      allow_dbg5                                :  1;
     unsigned      allow_dbg6                                :  1;
     unsigned      allow_dbg7                                :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_allow_dbg_r_xlf_t;

/*! @struct ncp_syscon_dbgrstreq_enable_r_xlf_t
 *  @brief DBGRSTREQ Enable Register
 *  @details If a bit is set, a warm reset request from the debug logic (DBGRSTREQ) is enabled to cause a reset of just the
	corresponding CPU core.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_dbgrstreq_enable_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq31_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU31 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq30_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU30 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq29_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU29 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq28_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU28 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq27_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU27 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq26_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU26 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq25_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU25 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq24_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU24 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq23_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU23 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq22_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU22 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq21_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU21 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq20_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU20 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq19_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU19 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq18_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU18 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq17_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU17 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq16_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU16 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq15_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU15 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq14_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU14 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq13_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU13 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq12_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU12 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq11_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU11 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq10_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU10 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq9_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU9 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq8_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU8 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq7_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU7 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq6_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU6 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq5_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU5 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq4_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU4 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq3_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU3 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq2_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU2 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq1_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU1 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dbgrstreq0_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enable DBGRSTREQ to reset CPU0 </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_dbgrstreq_enable_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      dbgrstreq31_enable                        :  1;
     unsigned      dbgrstreq30_enable                        :  1;
     unsigned      dbgrstreq29_enable                        :  1;
     unsigned      dbgrstreq28_enable                        :  1;
     unsigned      dbgrstreq27_enable                        :  1;
     unsigned      dbgrstreq26_enable                        :  1;
     unsigned      dbgrstreq25_enable                        :  1;
     unsigned      dbgrstreq24_enable                        :  1;
     unsigned      dbgrstreq23_enable                        :  1;
     unsigned      dbgrstreq22_enable                        :  1;
     unsigned      dbgrstreq21_enable                        :  1;
     unsigned      dbgrstreq20_enable                        :  1;
     unsigned      dbgrstreq19_enable                        :  1;
     unsigned      dbgrstreq18_enable                        :  1;
     unsigned      dbgrstreq17_enable                        :  1;
     unsigned      dbgrstreq16_enable                        :  1;
     unsigned      dbgrstreq15_enable                        :  1;
     unsigned      dbgrstreq14_enable                        :  1;
     unsigned      dbgrstreq13_enable                        :  1;
     unsigned      dbgrstreq12_enable                        :  1;
     unsigned      dbgrstreq11_enable                        :  1;
     unsigned      dbgrstreq10_enable                        :  1;
     unsigned      dbgrstreq9_enable                         :  1;
     unsigned      dbgrstreq8_enable                         :  1;
     unsigned      dbgrstreq7_enable                         :  1;
     unsigned      dbgrstreq6_enable                         :  1;
     unsigned      dbgrstreq5_enable                         :  1;
     unsigned      dbgrstreq4_enable                         :  1;
     unsigned      dbgrstreq3_enable                         :  1;
     unsigned      dbgrstreq2_enable                         :  1;
     unsigned      dbgrstreq1_enable                         :  1;
     unsigned      dbgrstreq0_enable                         :  1;
#else    /* Little Endian */
     unsigned      dbgrstreq0_enable                         :  1;
     unsigned      dbgrstreq1_enable                         :  1;
     unsigned      dbgrstreq2_enable                         :  1;
     unsigned      dbgrstreq3_enable                         :  1;
     unsigned      dbgrstreq4_enable                         :  1;
     unsigned      dbgrstreq5_enable                         :  1;
     unsigned      dbgrstreq6_enable                         :  1;
     unsigned      dbgrstreq7_enable                         :  1;
     unsigned      dbgrstreq8_enable                         :  1;
     unsigned      dbgrstreq9_enable                         :  1;
     unsigned      dbgrstreq10_enable                        :  1;
     unsigned      dbgrstreq11_enable                        :  1;
     unsigned      dbgrstreq12_enable                        :  1;
     unsigned      dbgrstreq13_enable                        :  1;
     unsigned      dbgrstreq14_enable                        :  1;
     unsigned      dbgrstreq15_enable                        :  1;
     unsigned      dbgrstreq16_enable                        :  1;
     unsigned      dbgrstreq17_enable                        :  1;
     unsigned      dbgrstreq18_enable                        :  1;
     unsigned      dbgrstreq19_enable                        :  1;
     unsigned      dbgrstreq20_enable                        :  1;
     unsigned      dbgrstreq21_enable                        :  1;
     unsigned      dbgrstreq22_enable                        :  1;
     unsigned      dbgrstreq23_enable                        :  1;
     unsigned      dbgrstreq24_enable                        :  1;
     unsigned      dbgrstreq25_enable                        :  1;
     unsigned      dbgrstreq26_enable                        :  1;
     unsigned      dbgrstreq27_enable                        :  1;
     unsigned      dbgrstreq28_enable                        :  1;
     unsigned      dbgrstreq29_enable                        :  1;
     unsigned      dbgrstreq30_enable                        :  1;
     unsigned      dbgrstreq31_enable                        :  1;
#endif
} ncp_syscon_dbgrstreq_enable_r_xlf_t;

/*! @struct ncp_syscon_warm_reset_enable_r_xlf_t
 *  @brief Warm Reset Enable Register
 *  @details If a bit is set, allows the WARMRSTREQ from the specified CPU to generate a reset_cpu sequence for that CPU.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_warm_reset_enable_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cpu31_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Enable CPU31's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu30_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Enable CPU30's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu29_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Enable CPU29's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu28_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Enable CPU28's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu27_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Enable CPU27's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu26_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Enable CPU26's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu25_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Enable CPU25's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu24_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Enable CPU24's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu23_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Enable CPU23's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu22_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Enable CPU22's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu21_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Enable CPU21's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu20_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Enable CPU20's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu19_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Enable CPU19's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu18_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Enable CPU18's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu17_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Enable CPU17's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu16_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enable CPU16's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu15_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Enable CPU15's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu14_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Enable CPU14's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu13_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Enable CPU13's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu12_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Enable CPU12's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu11_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Enable CPU11's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu10_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Enable CPU10's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu9_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Enable CPU9's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu8_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enable CPU8's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu7_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Enable CPU7's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu6_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Enable CPU6's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu5_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Enable CPU5's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu4_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Enable CPU4's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu3_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Enable CPU3's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu2_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Enable CPU2's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu1_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Enable CPU1's warm reset request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu0_warm_reset_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enable CPU0's warm reset request. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_warm_reset_enable_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      cpu31_warm_reset_enable                   :  1;
     unsigned      cpu30_warm_reset_enable                   :  1;
     unsigned      cpu29_warm_reset_enable                   :  1;
     unsigned      cpu28_warm_reset_enable                   :  1;
     unsigned      cpu27_warm_reset_enable                   :  1;
     unsigned      cpu26_warm_reset_enable                   :  1;
     unsigned      cpu25_warm_reset_enable                   :  1;
     unsigned      cpu24_warm_reset_enable                   :  1;
     unsigned      cpu23_warm_reset_enable                   :  1;
     unsigned      cpu22_warm_reset_enable                   :  1;
     unsigned      cpu21_warm_reset_enable                   :  1;
     unsigned      cpu20_warm_reset_enable                   :  1;
     unsigned      cpu19_warm_reset_enable                   :  1;
     unsigned      cpu18_warm_reset_enable                   :  1;
     unsigned      cpu17_warm_reset_enable                   :  1;
     unsigned      cpu16_warm_reset_enable                   :  1;
     unsigned      cpu15_warm_reset_enable                   :  1;
     unsigned      cpu14_warm_reset_enable                   :  1;
     unsigned      cpu13_warm_reset_enable                   :  1;
     unsigned      cpu12_warm_reset_enable                   :  1;
     unsigned      cpu11_warm_reset_enable                   :  1;
     unsigned      cpu10_warm_reset_enable                   :  1;
     unsigned      cpu9_warm_reset_enable                    :  1;
     unsigned      cpu8_warm_reset_enable                    :  1;
     unsigned      cpu7_warm_reset_enable                    :  1;
     unsigned      cpu6_warm_reset_enable                    :  1;
     unsigned      cpu5_warm_reset_enable                    :  1;
     unsigned      cpu4_warm_reset_enable                    :  1;
     unsigned      cpu3_warm_reset_enable                    :  1;
     unsigned      cpu2_warm_reset_enable                    :  1;
     unsigned      cpu1_warm_reset_enable                    :  1;
     unsigned      cpu0_warm_reset_enable                    :  1;
#else    /* Little Endian */
     unsigned      cpu0_warm_reset_enable                    :  1;
     unsigned      cpu1_warm_reset_enable                    :  1;
     unsigned      cpu2_warm_reset_enable                    :  1;
     unsigned      cpu3_warm_reset_enable                    :  1;
     unsigned      cpu4_warm_reset_enable                    :  1;
     unsigned      cpu5_warm_reset_enable                    :  1;
     unsigned      cpu6_warm_reset_enable                    :  1;
     unsigned      cpu7_warm_reset_enable                    :  1;
     unsigned      cpu8_warm_reset_enable                    :  1;
     unsigned      cpu9_warm_reset_enable                    :  1;
     unsigned      cpu10_warm_reset_enable                   :  1;
     unsigned      cpu11_warm_reset_enable                   :  1;
     unsigned      cpu12_warm_reset_enable                   :  1;
     unsigned      cpu13_warm_reset_enable                   :  1;
     unsigned      cpu14_warm_reset_enable                   :  1;
     unsigned      cpu15_warm_reset_enable                   :  1;
     unsigned      cpu16_warm_reset_enable                   :  1;
     unsigned      cpu17_warm_reset_enable                   :  1;
     unsigned      cpu18_warm_reset_enable                   :  1;
     unsigned      cpu19_warm_reset_enable                   :  1;
     unsigned      cpu20_warm_reset_enable                   :  1;
     unsigned      cpu21_warm_reset_enable                   :  1;
     unsigned      cpu22_warm_reset_enable                   :  1;
     unsigned      cpu23_warm_reset_enable                   :  1;
     unsigned      cpu24_warm_reset_enable                   :  1;
     unsigned      cpu25_warm_reset_enable                   :  1;
     unsigned      cpu26_warm_reset_enable                   :  1;
     unsigned      cpu27_warm_reset_enable                   :  1;
     unsigned      cpu28_warm_reset_enable                   :  1;
     unsigned      cpu29_warm_reset_enable                   :  1;
     unsigned      cpu30_warm_reset_enable                   :  1;
     unsigned      cpu31_warm_reset_enable                   :  1;
#endif
} ncp_syscon_warm_reset_enable_r_xlf_t;

/*! @struct ncp_syscon_disable_r_xlf_t
 *  @brief Disable Module Register.
 *  @details When set the corresponding module will be disabled.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_disable_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param disable_custom </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> If set, disables the EAC and FC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_cdc3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> If set, disables the cdc3. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_cdc2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> If set, disables the cdc2. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_cdc1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> If set, disables the cdc1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_cdc0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> If set, disables the cdc0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_pcx </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> If set, disables the pcx. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_sbb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> If set, disables the sbb, otherwise the OR of the
 *        disable_sec* fuses or fuse force bits determines whether
 *        or  not the the sbb is disabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_rif1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> If set, disables the rif1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_rif0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> If set, disables the rif0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_pci0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> If set, disables the pci0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_isbs1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> If set, disables the isbs1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_isbs0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> If set, disables the isbs0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_isb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> If set, disables the isb. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_fes </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> If set, disables the fes. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_erif1_comp_decomp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> If set, disables the erif1 compression and decompression
 *        logic.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_erif0_comp_decomp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> If set, disables the erif0 compression and decompression
 *        logic.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_eioasm1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> If set, disables the eioasm1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_eioasm0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> If set, disables the eioasm0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_eioas1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> If set, disables the eioas1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_eioas0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> If set, disables the eioas0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_eioamh </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> If set, disables the eioamh. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_eioam </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> If set, disables the eioam. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_dpi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> If set, disables the dpi. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_dec </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> If set, disables the dec. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_ccms </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> If set, disables the ccms. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_ccm </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> If set, disables the ccm. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_disable_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      disable_custom                            :  1;
     unsigned      disable_cdc3                              :  1;
     unsigned      disable_cdc2                              :  1;
     unsigned      disable_cdc1                              :  1;
     unsigned      disable_cdc0                              :  1;
     unsigned      disable_pcx                               :  1;
     unsigned      disable_sbb                               :  1;
     unsigned      disable_rif1                              :  1;
     unsigned      disable_rif0                              :  1;
     unsigned      disable_pci0                              :  1;
     unsigned      disable_isbs1                             :  1;
     unsigned      disable_isbs0                             :  1;
     unsigned      disable_isb                               :  1;
     unsigned      disable_fes                               :  1;
     unsigned      disable_erif1_comp_decomp                 :  1;
     unsigned      disable_erif0_comp_decomp                 :  1;
     unsigned      disable_eioasm1                           :  1;
     unsigned      disable_eioasm0                           :  1;
     unsigned      disable_eioas1                            :  1;
     unsigned      disable_eioas0                            :  1;
     unsigned      disable_eioamh                            :  1;
     unsigned      disable_eioam                             :  1;
     unsigned      disable_dpi                               :  1;
     unsigned      disable_dec                               :  1;
     unsigned      disable_ccms                              :  1;
     unsigned      disable_ccm                               :  1;
#else    /* Little Endian */
     unsigned      disable_ccm                               :  1;
     unsigned      disable_ccms                              :  1;
     unsigned      disable_dec                               :  1;
     unsigned      disable_dpi                               :  1;
     unsigned      disable_eioam                             :  1;
     unsigned      disable_eioamh                            :  1;
     unsigned      disable_eioas0                            :  1;
     unsigned      disable_eioas1                            :  1;
     unsigned      disable_eioasm0                           :  1;
     unsigned      disable_eioasm1                           :  1;
     unsigned      disable_erif0_comp_decomp                 :  1;
     unsigned      disable_erif1_comp_decomp                 :  1;
     unsigned      disable_fes                               :  1;
     unsigned      disable_isb                               :  1;
     unsigned      disable_isbs0                             :  1;
     unsigned      disable_isbs1                             :  1;
     unsigned      disable_pci0                              :  1;
     unsigned      disable_rif0                              :  1;
     unsigned      disable_rif1                              :  1;
     unsigned      disable_sbb                               :  1;
     unsigned      disable_pcx                               :  1;
     unsigned      disable_cdc0                              :  1;
     unsigned      disable_cdc1                              :  1;
     unsigned      disable_cdc2                              :  1;
     unsigned      disable_cdc3                              :  1;
     unsigned      disable_custom                            :  1;
     unsigned      reserved0                                 :  6;
#endif
} ncp_syscon_disable_r_xlf_t;

/*! @struct ncp_syscon_reset_fes_r_xlf_t
 *  @brief Reset FES Register
 *  @details This register controls the resets for FES module. 
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_reset_fes_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param allow_fes_dbg </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> If set, reset the FES debug logic whenever the FES
 *        core logic is reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_fes_ptm </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> If set, reset the FES trace logic whenever the FES
 *        core logic is reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_fes_por </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> If set, hold the FES powerup logic in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_fes_dbg </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> If set, hold the FES debug logic in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_fes </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> If set, hold the FES core logic in reset. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_reset_fes_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 27;
     unsigned      allow_fes_dbg                             :  1;
     unsigned      allow_fes_ptm                             :  1;
     unsigned      hold_fes_por                              :  1;
     unsigned      hold_fes_dbg                              :  1;
     unsigned      hold_fes                                  :  1;
#else    /* Little Endian */
     unsigned      hold_fes                                  :  1;
     unsigned      hold_fes_dbg                              :  1;
     unsigned      hold_fes_por                              :  1;
     unsigned      allow_fes_ptm                             :  1;
     unsigned      allow_fes_dbg                             :  1;
     unsigned      reserved0                                 : 27;
#endif
} ncp_syscon_reset_fes_r_xlf_t;

/*! @struct ncp_syscon_reset_dsp_r_xlf_t
 *  @brief Reset DSP Register
 *  @details Setting a bit in this register when it was previously a 0 causes a reset sequence for the associated DSP cluster.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_reset_dsp_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param reset_dsp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Enable DSP Cluster 3 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_dsp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Enable DSP Cluster 2 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_dsp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Enable DSP Cluster 1 reset sequence on leading edge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reset_dsp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enable DSP Cluster 0 reset sequence on leading edge. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_reset_dsp_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 28;
     unsigned      reset_dsp3                                :  1;
     unsigned      reset_dsp2                                :  1;
     unsigned      reset_dsp1                                :  1;
     unsigned      reset_dsp0                                :  1;
#else    /* Little Endian */
     unsigned      reset_dsp0                                :  1;
     unsigned      reset_dsp1                                :  1;
     unsigned      reset_dsp2                                :  1;
     unsigned      reset_dsp3                                :  1;
     unsigned      reserved0                                 : 28;
#endif
} ncp_syscon_reset_dsp_r_xlf_t;

/*! @struct ncp_syscon_hold_dsp_r_xlf_t
 *  @brief Hold DSP Reset Register
 *  @details Setting a bit in this register holds the associated DSP cluster in reset.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_hold_dsp_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param hold_dsp3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Hold DSP Cluster 3 in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_dsp2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Hold DSP Cluster 2 in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_dsp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Hold DSP Cluster 1 in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_dsp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Hold DSP Cluster 0 in reset. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_hold_dsp_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 28;
     unsigned      hold_dsp3                                 :  1;
     unsigned      hold_dsp2                                 :  1;
     unsigned      hold_dsp1                                 :  1;
     unsigned      hold_dsp0                                 :  1;
#else    /* Little Endian */
     unsigned      hold_dsp0                                 :  1;
     unsigned      hold_dsp1                                 :  1;
     unsigned      hold_dsp2                                 :  1;
     unsigned      hold_dsp3                                 :  1;
     unsigned      reserved0                                 : 28;
#endif
} ncp_syscon_hold_dsp_r_xlf_t;

/*! @struct ncp_syscon_hold_dsp_dbg_r_xlf_t
 *  @brief Hold DSP Debug Logic Reset Register
 *  @details Setting a bit in this register holds the associated DSP cluster's debug logic in reset.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_hold_dsp_dbg_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param hold_dsp_dbg3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Hold DSP Cluster 3's debug logic in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_dsp_dbg2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Hold DSP Cluster 2's debug logic in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_dsp_dbg1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Hold DSP Cluster 1's debug logic in reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_dsp_dbg0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Hold DSP Cluster 0's debug logic in reset. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_hold_dsp_dbg_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 28;
     unsigned      hold_dsp_dbg3                             :  1;
     unsigned      hold_dsp_dbg2                             :  1;
     unsigned      hold_dsp_dbg1                             :  1;
     unsigned      hold_dsp_dbg0                             :  1;
#else    /* Little Endian */
     unsigned      hold_dsp_dbg0                             :  1;
     unsigned      hold_dsp_dbg1                             :  1;
     unsigned      hold_dsp_dbg2                             :  1;
     unsigned      hold_dsp_dbg3                             :  1;
     unsigned      reserved0                                 : 28;
#endif
} ncp_syscon_hold_dsp_dbg_r_xlf_t;

/*! @struct ncp_syscon_allow_dsp_dbg_r_xlf_t
 *  @brief Allow DSP Debug Logic Reset Register
 *  @details Setting a bit in this register allows the associated DSP cluster's debug logic to be reset whenever the DSP cluster is reset.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_allow_dsp_dbg_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param allow_dsp_dbg3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Aloow DSP Cluster 3's debug logic to be reset when
 *        the cluster is reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_dsp_dbg2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Aloow DSP Cluster 2's debug logic to be reset when
 *        the cluster is reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_dsp_dbg1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Aloow DSP Cluster 1's debug logic to be reset when
 *        the cluster is reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_dsp_dbg0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Aloow DSP Cluster 0's debug logic to be reset when
 *        the cluster is reset.
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_allow_dsp_dbg_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 28;
     unsigned      allow_dsp_dbg3                            :  1;
     unsigned      allow_dsp_dbg2                            :  1;
     unsigned      allow_dsp_dbg1                            :  1;
     unsigned      allow_dsp_dbg0                            :  1;
#else    /* Little Endian */
     unsigned      allow_dsp_dbg0                            :  1;
     unsigned      allow_dsp_dbg1                            :  1;
     unsigned      allow_dsp_dbg2                            :  1;
     unsigned      allow_dsp_dbg3                            :  1;
     unsigned      reserved0                                 : 28;
#endif
} ncp_syscon_allow_dsp_dbg_r_xlf_t;

/*! @struct ncp_syscon_reset_wo_sm_r_xlf_t
 *  @brief Reset Chip Without Sysmem Register
 *  @details Setting bit 0 in this register prevents the system memory controllers and PHYs from being reset by any chip reset sequence.
	Note that setting this bit will immediately also raise the shields_up indication to the memory controllers and will
	prevent any further accesses to system memory until after a pin, system, or chip reset has been completed.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_reset_wo_sm_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param reset_chip_wo_sm </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> If set, prevents reset_chip from resetting the system
 *        memory controllers or PHYs. This bit is automatically
 *         reset 4 clocks after a chip reset sequence is completed.
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_reset_wo_sm_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 31;
     unsigned      reset_chip_wo_sm                          :  1;
#else    /* Little Endian */
     unsigned      reset_chip_wo_sm                          :  1;
     unsigned      reserved0                                 : 31;
#endif
} ncp_syscon_reset_wo_sm_r_xlf_t;

/*! @struct ncp_syscon_zero_ctl_r_xlf_t
 *  @brief Zeroization Control Register
 *  @details If this leading edge is detected on a write to this register bit, it causes a software zeroization request.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_zero_ctl_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param hold_elm_zeroize </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Hold ELM zeroize asserted. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_lsm_zeroize </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Hold LSM zeroize asserted. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_trng_zeroize </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Hold TRNG zeroize asserted. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_pka_zeroize </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Hold PKA zeroize asserted. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_sbb_zeroize </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Hold SBB zeroize asserted. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_spp_zeroize </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Hold SPP zeroize asserted. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zero_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Request zeroization of all sensitive data structures. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_zero_ctl_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 25;
     unsigned      hold_elm_zeroize                          :  1;
     unsigned      hold_lsm_zeroize                          :  1;
     unsigned      hold_trng_zeroize                         :  1;
     unsigned      hold_pka_zeroize                          :  1;
     unsigned      hold_sbb_zeroize                          :  1;
     unsigned      hold_spp_zeroize                          :  1;
     unsigned      zero_req                                  :  1;
#else    /* Little Endian */
     unsigned      zero_req                                  :  1;
     unsigned      hold_spp_zeroize                          :  1;
     unsigned      hold_sbb_zeroize                          :  1;
     unsigned      hold_pka_zeroize                          :  1;
     unsigned      hold_trng_zeroize                         :  1;
     unsigned      hold_lsm_zeroize                          :  1;
     unsigned      hold_elm_zeroize                          :  1;
     unsigned      reserved0                                 : 25;
#endif
} ncp_syscon_zero_ctl_r_xlf_t;

/*! @struct ncp_syscon_zero_stat_r_xlf_t
 *  @brief Zeroization Status Register
 *  @details This register contains read-only status associated with the authentication and zeroization functions.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_zero_stat_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param jtag_auth_pass </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> JTAG authentification pass. If this bit is one, then
 *        the authentification process successfully completed
 *        and there has not been an deauthentification since
 *        then.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param jtag_auth_fail_count </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> JTAG authentification fail count. Number of times
 *        that an authentification attempt was attempted but
 *        failed.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sw_rev_auth_pass </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> SW revision authentification pass. If this bit is
 *        one, then the authentification process successfully
 *        completed and there has not been an deauthentification
 *        since then.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sw_rev_auth_fail_count </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> SW revision authentification fail count. Number of
 *        times that an authentification attempt was attempted
 *        but failed.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param jtag_debug_level </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> JTAG debug level. The current state of the JTAG debug
 *        level.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ecm_zero_done </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> ECM zeroization complete. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lsm_zero_busy </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> LSM zeroization in progress. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pka_zero_busy </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> PKA zeroization in progress. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trng_zero_busy </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> TRNG zeroization in progress. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_zero_stat_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      jtag_auth_pass                            :  1;
     unsigned      jtag_auth_fail_count                      :  3;
     unsigned      sw_rev_auth_pass                          :  1;
     unsigned      sw_rev_auth_fail_count                    :  3;
     unsigned      reserved0                                 :  2;
     unsigned      jtag_debug_level                          :  2;
     unsigned      reserved1                                 : 12;
     unsigned      ecm_zero_done                             :  1;
     unsigned      lsm_zero_busy                             :  1;
     unsigned      pka_zero_busy                             :  1;
     unsigned      trng_zero_busy                            :  1;
     unsigned      reserved2                                 :  4;
#else    /* Little Endian */
     unsigned      reserved2                                 :  4;
     unsigned      trng_zero_busy                            :  1;
     unsigned      pka_zero_busy                             :  1;
     unsigned      lsm_zero_busy                             :  1;
     unsigned      ecm_zero_done                             :  1;
     unsigned      reserved1                                 : 12;
     unsigned      jtag_debug_level                          :  2;
     unsigned      reserved0                                 :  2;
     unsigned      sw_rev_auth_fail_count                    :  3;
     unsigned      sw_rev_auth_pass                          :  1;
     unsigned      jtag_auth_fail_count                      :  3;
     unsigned      jtag_auth_pass                            :  1;
#endif
} ncp_syscon_zero_stat_r_xlf_t;

/*! @struct ncp_syscon_fuse_force_r_xlf_t
 *  @brief Fuse Force Register
 *  @details This register contains overrides for several of the fuse values.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 	CAUTION: Register bits that affect the ECM should only be updated when the ECM is not processing a request.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_fuse_force_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param disable_sec </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> If set, forces the disable of the ELM, PKA, SBB, SPP,
 *        and TRNG security functions, otherwise an OR of the
 *        disable_sec* fuse values determines whether or not
 *        security functions are enabled or disabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_macsec </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> If set, forces the disable of the ELM, SBB, and macsec
 *        security functions, otherwise an OR of the disable_sec*
 *        fuse values determines whether or not security functions
 *        are enabled or disabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rewa </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> If set, forces write authentication for fuse bits
 *        in group 1, otherwise the REWA fuse value determines
 *        whether or notwrite authentication is required.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rewa2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> If set, forces write authentication for fuse bits
 *        in group 2, otherwise the REWA2 fuse value determines
 *        whether or not write authentication is required.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param encryption_mode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> If a bit is set, it is ORed with the fuse value to
 *        determine the chip encrytion mode. Note that the disable_sec*
 *        force bits or fuse values will override this setting
 *        and force it to 0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fuse_force_write_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> If set, disables any further writes to the Fuse Force
 *        or Fuse Force 2 registers. Once set, this bit can
 *        only be cleared by a system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param secure_boot </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> If set, enables secure boot mode, otherwise the fuse
 *        value determines whether or not secure boot mode is
 *        enabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param secure_axis_enable </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> If a bit is set, it is ORed with the fuse value to
 *        determine the axis security mode.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zeroize_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> If set, enables the zeroize pin, otherwise the fuse
 *        value determines whether or not the zeroize pin is
 *        enabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zeroize_after_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> If set, enables zeroization after any reset, otherwise
 *        the fuse value determines whether or not zeroization
 *        occurs after reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zeroize_with_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> If set, allows any zeroization request to cause a
 *        fabric reset sequence and to reset all of the EIOAs,
 *        otherwise the fuse value determines whether or not
 *        the resets are generated.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mtc_self_test_disable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> If set, disables MTC self test, otherwise the fuse
 *        value determines whether or not MTC self test is enabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param jtag_debug_level </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> If a bit is set, it is ORed with the fuse value to
 *        determine the jtag debug level setting.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_custom </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> If set, disable the EAC and FC core logic, otherwise
 *        the disable_custom fuse value and the disable_custom
 *        bit value in the Disable Module register determine
 *        whether or not the EAC and FC core logic is disabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_cdc3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> If set, disable the CDC3 core logic, otherwise the
 *        disable_cdcs fuse value and the disable_cdc3 bit value
 *        in the Disable Module register determine whether
 *        or not the CDC3 core logic is disabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_cdc2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> If set, disable the CDC2 core logic, otherwise the
 *        disable_cdcs fuse value and the disable_cdc2 bit value
 *        in the Disable Module register determine whether
 *        or not the CDC2 core logic is disabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_cdc1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> If set, disable the CDC1 core logic, otherwise the
 *        disable_cdcs fuse value and the disable_cdc1 bit value
 *        in the Disable Module register determine whether
 *        or not the CDC1 core logic is disabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_cdc0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> If set, disable the CDC0 core logic, otherwise the
 *        disable_cdcs fuse value and the disable_cdc0 bit value
 *        in the Disable Module register determine whether
 *        or not the CDC0 core logic is disabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fips_test_enable_i </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> If set, forces the fips_test_enable_i signal, otherwise
 *        the fuse value determines the state of the fips_test_enable_i
 *        signal.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_rif1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> If set, disable the RIF1 core logic, otherwise the
 *        disable_rifs fuse value and the disable_rif1 bit value
 *        in the Disable Module register determine whether
 *        or not the RIF1 core logic is disabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_rif0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> If set, disable the RIF0 core logic, otherwise the
 *        disable_rifs fuse value and the disable_rif0 bit value
 *        in the Disable Module register determine whether
 *        or not the RIF0 core logic is disabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_erif1_comp_decomp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> If set, disable the ERIF1 compression and decompression
 *        logic, otherwise the disable_rifs fuse value and the
 *        disable_erif1_comp_decomp bit value in the Disable
 *        Module register determine whether or not the ERIF1
 *        compression and decompression logic is disabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_erif0_comp_decomp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> If set, disable the ERIF0 compression and decompression
 *        logic, otherwise the disable_rifs fuse value and the
 *        disable_erif0_comp_decomp bit value in the Disable
 *        Module register determine whether or not the ERIF0
 *        compression and decompression logic is disabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param jtag_resecure </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> If set, the JTAG security level override is disabled,
 *        otherwise the fuse value determines whether or not
 *        the JTAG security level override is disabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_fes </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> If set, disable the FES core logic, otherwise the
 *        disable_custom fuse value and the disable_fes bit
 *        value in the Disable Module register determine whether
 *        or not the FES core logic is disabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param psm_wait_16k </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> If set, the PSM waits 16K clocks between states, otherwise
 *        the psm_wait_16k fuse value determines whether or
 *        not the wait is 16K or 64 clocks.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param psm_includes_force </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> If set, reads of the pfuse register reflect the value
 *        after ORing in any relevant fuse force bits. Otherwise,
 *        reads of the pfuse register reflect the actual fuse
 *        values.
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_fuse_force_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      disable_sec                               :  1;
     unsigned      disable_macsec                            :  1;
     unsigned      rewa                                      :  1;
     unsigned      rewa2                                     :  1;
     unsigned      encryption_mode                           :  2;
     unsigned      reserved0                                 :  1;
     unsigned      fuse_force_write_disable                  :  1;
     unsigned      secure_boot                               :  1;
     unsigned      reserved1                                 :  1;
     unsigned      secure_axis_enable                        :  2;
     unsigned      zeroize_enable                            :  1;
     unsigned      zeroize_after_reset                       :  1;
     unsigned      zeroize_with_reset                        :  1;
     unsigned      mtc_self_test_disable                     :  1;
     unsigned      jtag_debug_level                          :  2;
     unsigned      disable_custom                            :  1;
     unsigned      disable_cdc3                              :  1;
     unsigned      disable_cdc2                              :  1;
     unsigned      disable_cdc1                              :  1;
     unsigned      disable_cdc0                              :  1;
     unsigned      fips_test_enable_i                        :  1;
     unsigned      disable_rif1                              :  1;
     unsigned      disable_rif0                              :  1;
     unsigned      disable_erif1_comp_decomp                 :  1;
     unsigned      disable_erif0_comp_decomp                 :  1;
     unsigned      jtag_resecure                             :  1;
     unsigned      disable_fes                               :  1;
     unsigned      psm_wait_16k                              :  1;
     unsigned      psm_includes_force                        :  1;
#else    /* Little Endian */
     unsigned      psm_includes_force                        :  1;
     unsigned      psm_wait_16k                              :  1;
     unsigned      disable_fes                               :  1;
     unsigned      jtag_resecure                             :  1;
     unsigned      disable_erif0_comp_decomp                 :  1;
     unsigned      disable_erif1_comp_decomp                 :  1;
     unsigned      disable_rif0                              :  1;
     unsigned      disable_rif1                              :  1;
     unsigned      fips_test_enable_i                        :  1;
     unsigned      disable_cdc0                              :  1;
     unsigned      disable_cdc1                              :  1;
     unsigned      disable_cdc2                              :  1;
     unsigned      disable_cdc3                              :  1;
     unsigned      disable_custom                            :  1;
     unsigned      jtag_debug_level                          :  2;
     unsigned      mtc_self_test_disable                     :  1;
     unsigned      zeroize_with_reset                        :  1;
     unsigned      zeroize_after_reset                       :  1;
     unsigned      zeroize_enable                            :  1;
     unsigned      secure_axis_enable                        :  2;
     unsigned      reserved1                                 :  1;
     unsigned      secure_boot                               :  1;
     unsigned      fuse_force_write_disable                  :  1;
     unsigned      reserved0                                 :  1;
     unsigned      encryption_mode                           :  2;
     unsigned      rewa2                                     :  1;
     unsigned      rewa                                      :  1;
     unsigned      disable_macsec                            :  1;
     unsigned      disable_sec                               :  1;
#endif
} ncp_syscon_fuse_force_r_xlf_t;

/*! @struct ncp_syscon_fuse_force2_r_xlf_t
 *  @brief Fuse Force 2 Register
 *  @details This register contains overrides for several of the fuse values.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 	CAUTION: Register bits that affect the ECM should only be updated when the ECM is not processing a request.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_fuse_force2_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param hash </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> If a bit is set, it is ORed with the ECM HASH3-0 fuse
 *        values to determine the value of the Hash Algorithm,
 *        otherwise the ECM HASH3-0 fuse bit values specify
 *        the Hash Algorithm value.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param salg </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> If a bit is set, it is ORed with the ECM SALG3-0 fuse
 *        values to determine the value of the Signature Algorithm,
 *        otherwise the ECM SALG3-0 fuse bit values specify
 *        the Signature Algorithm value.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param srk2_revoke </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> If set, forces the revocation of Storage Root Key
 *        Copy 2, otherwise the ECM KAKpub2revk fuse bit value
 *        determines whether or not Storage Root Key Copy 2
 *        is revoked.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param srk1_revoke </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> If set, forces the revocation of Storage Root Key
 *        Copy 1, otherwise the ECM KAKpub1revk fuse bit value
 *        determines whether or not Storage Root Key Copy 1
 *        is revoked.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param srk0_revoke </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> If set, forces the revocation of Storage Root Key
 *        Copy 0, otherwise the ECM KAKpub0revk fuse bit value
 *        determines whether or not Storage Root Key Copy 0
 *        is revoked.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ffk_resecure </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> If set, resecures the revocation of Fuse Force Keys
 *        even if the revocation has been overridden, otherwise
 *        the ECM FFKRORS fuse bit value determines whether
 *        or not Fuse Force Keys are revoked.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ffk_revoke </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> If set, forces the revocation of Fuse Force Keys,
 *        otherwise the ECM FFrevk fuse bit value determines
 *        whether or not Fuse Force Keys are revoked.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param redundant_stage2_boot </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> If set, forces Redundant Stage 2 Boot mode, otherwise
 *        the ECM RS2B fuse bit value determines whether or
 *        not the device is in Redundant Stage 2 Boot mode.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sbek2_revoke </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> If set, forces the revocation of Secure Boot Encryption
 *        Key Copy 2, otherwise the ECM KAKpub2revk fuse bit
 *        value determines whether or not Secure Boot Encryption
 *        Key Copy 2 is revoked.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sbek1_revoke </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> If set, forces the revocation of Secure Boot Encryption
 *        Key Copy 1, otherwise the ECM KAKpub1revk fuse bit
 *        value determines whether or not Secure Boot Encryption
 *        Key Copy 1 is revoked.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sbek0_revoke </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> If set, forces the revocation of Secure Boot Encryption
 *        Key Copy 0, otherwise the ECM KAKpub0revk fuse bit
 *        value determines whether or not Secure Boot Encryption
 *        Key Copy 0 is revoked.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pkak2_revoke </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> If set, forces the revocation of Public Key Authentication
 *        Key Copy 2, otherwise the ECM KAKpub2revk fuse bit
 *        value determines whether or not Public Key Authentication
 *        Key Copy 2 is revoked.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pkak1_revoke </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> If set, forces the revocation of Public Key Authentication
 *        Key Copy 1, otherwise the ECM KAKpub1revk fuse bit
 *        value determines whether or not Public Key Authentication
 *        Key Copy 1 is revoked.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pkak0_revoke </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> If set, forces the revocation of Public Key Authentication
 *        Key Copy 0, otherwise the ECM KAKpub0revk fuse bit
 *        value determines whether or not Public Key Authentication
 *        Key Copy 0 is revoked.
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_fuse_force2_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      hash                                      :  4;
     unsigned      salg                                      :  4;
     unsigned      reserved1                                 :  1;
     unsigned      srk2_revoke                               :  1;
     unsigned      srk1_revoke                               :  1;
     unsigned      srk0_revoke                               :  1;
     unsigned      reserved2                                 :  2;
     unsigned      ffk_resecure                              :  1;
     unsigned      ffk_revoke                                :  1;
     unsigned      reserved3                                 :  3;
     unsigned      redundant_stage2_boot                     :  1;
     unsigned      reserved4                                 :  1;
     unsigned      sbek2_revoke                              :  1;
     unsigned      sbek1_revoke                              :  1;
     unsigned      sbek0_revoke                              :  1;
     unsigned      reserved5                                 :  1;
     unsigned      pkak2_revoke                              :  1;
     unsigned      pkak1_revoke                              :  1;
     unsigned      pkak0_revoke                              :  1;
#else    /* Little Endian */
     unsigned      pkak0_revoke                              :  1;
     unsigned      pkak1_revoke                              :  1;
     unsigned      pkak2_revoke                              :  1;
     unsigned      reserved5                                 :  1;
     unsigned      sbek0_revoke                              :  1;
     unsigned      sbek1_revoke                              :  1;
     unsigned      sbek2_revoke                              :  1;
     unsigned      reserved4                                 :  1;
     unsigned      redundant_stage2_boot                     :  1;
     unsigned      reserved3                                 :  3;
     unsigned      ffk_revoke                                :  1;
     unsigned      ffk_resecure                              :  1;
     unsigned      reserved2                                 :  2;
     unsigned      srk0_revoke                               :  1;
     unsigned      srk1_revoke                               :  1;
     unsigned      srk2_revoke                               :  1;
     unsigned      reserved1                                 :  1;
     unsigned      salg                                      :  4;
     unsigned      hash                                      :  4;
     unsigned      reserved0                                 :  4;
#endif
} ncp_syscon_fuse_force2_r_xlf_t;

/*! @struct ncp_syscon_hold_infra_r_xlf_t
 *  @brief Hold CPU Cluster Infrastructure Reset Register
 *  @details Setting a bit in this register holds the associated CPU cluster's debug logic in reset.
	Using the CPU powerdown sequence controlled by the CPU Powerdown Request register will set bits in this register.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_hold_infra_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param hold_dbg7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Hold CPU cluster7's debug logic in reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_dbg6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Hold CPU cluster6's debug logic in reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_dbg5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Hold CPU cluster5's debug logic in reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_dbg4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Hold CPU cluster4's debug logic in reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_dbg3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Hold CPU cluster3's debug logic in reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_dbg2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Hold CPU cluster2's debug logic in reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_dbg1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Hold CPU cluster1's debug logic in reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_dbg0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Hold CPU cluster0's debug logic in reset </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_hold_infra_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      hold_dbg7                                 :  1;
     unsigned      hold_dbg6                                 :  1;
     unsigned      hold_dbg5                                 :  1;
     unsigned      hold_dbg4                                 :  1;
     unsigned      hold_dbg3                                 :  1;
     unsigned      hold_dbg2                                 :  1;
     unsigned      hold_dbg1                                 :  1;
     unsigned      hold_dbg0                                 :  1;
#else    /* Little Endian */
     unsigned      hold_dbg0                                 :  1;
     unsigned      hold_dbg1                                 :  1;
     unsigned      hold_dbg2                                 :  1;
     unsigned      hold_dbg3                                 :  1;
     unsigned      hold_dbg4                                 :  1;
     unsigned      hold_dbg5                                 :  1;
     unsigned      hold_dbg6                                 :  1;
     unsigned      hold_dbg7                                 :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_hold_infra_r_xlf_t;

/*! @struct ncp_syscon_hold_stream_r_xlf_t
 *  @brief Hold CPU Cluster Streaming Interface Reset Register
 *  @details Setting a bit in this register holds the associated CPU cluster's streaming GIC interface logic in reset.
	Using the CPU powerdown sequence controlled by the CPU Powerdown Request register will set bits in this register.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_hold_stream_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param hold_stream7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Hold CPU cluster7's GIC streaming interface logic
 *        in reset
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_stream6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Hold CPU cluster6's GIC streaming interface logic
 *        in reset
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_stream5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Hold CPU cluster5's GIC streaming interface logic
 *        in reset
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_stream4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Hold CPU cluster4's GIC streaming interface logic
 *        in reset
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_stream3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Hold CPU cluster3's GIC streaming interface logic
 *        in reset
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_stream2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Hold CPU cluster2's GIC streaming interface logic
 *        in reset
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_stream1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Hold CPU cluster1's GIC streaming interface logic
 *        in reset
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_stream0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Hold CPU cluster0's GIC streaming interface logic
 *        in reset
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_hold_stream_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      hold_stream7                              :  1;
     unsigned      hold_stream6                              :  1;
     unsigned      hold_stream5                              :  1;
     unsigned      hold_stream4                              :  1;
     unsigned      hold_stream3                              :  1;
     unsigned      hold_stream2                              :  1;
     unsigned      hold_stream1                              :  1;
     unsigned      hold_stream0                              :  1;
#else    /* Little Endian */
     unsigned      hold_stream0                              :  1;
     unsigned      hold_stream1                              :  1;
     unsigned      hold_stream2                              :  1;
     unsigned      hold_stream3                              :  1;
     unsigned      hold_stream4                              :  1;
     unsigned      hold_stream5                              :  1;
     unsigned      hold_stream6                              :  1;
     unsigned      hold_stream7                              :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_hold_stream_r_xlf_t;

/*! @struct ncp_syscon_hold_dssb_r_xlf_t
 *  @brief Hold CPU Cluster DSSB Reset Register
 *  @details Setting a bit in this register holds the associated CPU cluster's fabric DSSB interface logic in reset.
	Using the CPU powerdown sequence controlled by the CPU Powerdown Request register will set bits in this register.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_hold_dssb_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param hold_dssb7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Hold CPU cluster7's DSSB interface logic in reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_dssb6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Hold CPU cluster6's DSSB interface logic in reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_dssb5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Hold CPU cluster5's DSSB interface logic in reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_dssb4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Hold CPU cluster4's DSSB interface logic in reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_dssb3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Hold CPU cluster3's DSSB interface logic in reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_dssb2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Hold CPU cluster2's DSSB interface logic in reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_dssb1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Hold CPU cluster1's DSSB interface logic in reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hold_dssb0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Hold CPU cluster0's DSSB interface logic in reset </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_hold_dssb_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      hold_dssb7                                :  1;
     unsigned      hold_dssb6                                :  1;
     unsigned      hold_dssb5                                :  1;
     unsigned      hold_dssb4                                :  1;
     unsigned      hold_dssb3                                :  1;
     unsigned      hold_dssb2                                :  1;
     unsigned      hold_dssb1                                :  1;
     unsigned      hold_dssb0                                :  1;
#else    /* Little Endian */
     unsigned      hold_dssb0                                :  1;
     unsigned      hold_dssb1                                :  1;
     unsigned      hold_dssb2                                :  1;
     unsigned      hold_dssb3                                :  1;
     unsigned      hold_dssb4                                :  1;
     unsigned      hold_dssb5                                :  1;
     unsigned      hold_dssb6                                :  1;
     unsigned      hold_dssb7                                :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_hold_dssb_r_xlf_t;

/*! @struct ncp_syscon_cpu_rst_timer_r_xlf_t
 *  @brief CPU Reset Deassertion Timer Register
 *  @details This register contains a 31b count value and an enable bit.  If the enable bit is set and at least one bit in either
	the Hold CPU Reset or Powerup CPU Reset registers is already set (or is subsequently set), then the count value will
	decrement each peripheral clock until it reaches 0.  When the count reaches 0, the enable bit will be reset and
	any bits that were set in the Hold CPU Reset or Powerup CPU Reset registers will also be reset.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_cpu_rst_timer_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cpu_reset_deassert_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Deassertion timer enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu_reset_deassert_timer </td>
 *     <td width="20%" align="center"> 31 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Deassertion timer value </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_cpu_rst_timer_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      cpu_reset_deassert_enable                 :  1;
     unsigned      cpu_reset_deassert_timer                  : 31;
#else    /* Little Endian */
     unsigned      cpu_reset_deassert_timer                  : 31;
     unsigned      cpu_reset_deassert_enable                 :  1;
#endif
} ncp_syscon_cpu_rst_timer_r_xlf_t;

/*! @struct ncp_syscon_rmc_rst_timer_r_xlf_t
 *  @brief Module Reset Deassertion Timer Register
 *  @details This register contains a 31b count value and an enable bit.  If the enable bit is set and at least one bit in the
	Reset Module register is already set (or is subsequently set), then the count value will decrement each peripheral
	clock until it reaches 0.  When the count reaches 0, the enable bit will be reset and any bits that were set in the
	Reset Module register will also be reset.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_rmc_rst_timer_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rmc_reset_deassert_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Deassertion timer enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rmc_reset_deassert_timer </td>
 *     <td width="20%" align="center"> 31 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Deassertion timer value </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_rmc_rst_timer_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rmc_reset_deassert_enable                 :  1;
     unsigned      rmc_reset_deassert_timer                  : 31;
#else    /* Little Endian */
     unsigned      rmc_reset_deassert_timer                  : 31;
     unsigned      rmc_reset_deassert_enable                 :  1;
#endif
} ncp_syscon_rmc_rst_timer_r_xlf_t;

/*! @struct ncp_syscon_rac_rst_timer_r_xlf_t
 *  @brief Peripheral Reset Deassertion Timer Register
 *  @details This register contains a 31b count value and an enable bit.  If the enable bit is set and at least one bit in the
	Reset Peripheral register is already set (or is subsequently set), then the count value will decrement each peripheral
	clock until it reaches 0.  When the count reaches 0, the enable bit will be reset and any bits that were set in the
	Reset Peripheral register will also be reset.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_rac_rst_timer_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rac_reset_deassert_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Deassertion timer enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rac_reset_deassert_timer </td>
 *     <td width="20%" align="center"> 31 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Deassertion timer value </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_rac_rst_timer_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rac_reset_deassert_enable                 :  1;
     unsigned      rac_reset_deassert_timer                  : 31;
#else    /* Little Endian */
     unsigned      rac_reset_deassert_timer                  : 31;
     unsigned      rac_reset_deassert_enable                 :  1;
#endif
} ncp_syscon_rac_rst_timer_r_xlf_t;

/*! @struct ncp_syscon_mtc_ctl_r_xlf_t
 *  @brief MTC Event Control Register
 *  @details This register is reset by a pin, system or chip reset and contains control for MTC events. Note that, if the
	mtc_self_test_disable fuse is set the values in this register are forced to 0.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_mtc_ctl_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param mtc_event_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> If set, enables MTC events. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mtc_chip_reset_enable1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> If set and the mtc_event_enable is also set, will
 *        cause a chip reset when mtc_done is asserted with
 *        the  mtc_status field set to 0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mtc_chip_reset_enable0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> If set and the mtc_event_enable is also set, will
 *        cause a chip reset when mtc_done is asserted with
 *        the  mtc_status field set to 2.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mtc_system_reset_enable1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> If set and the mtc_event_enable is also set, will
 *        cause a system reset when mtc_done is asserted with
 *        the  mtc_status field set to 0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mtc_system_reset_enable0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> If set and the mtc_event_enable is also set, will
 *        cause a system reset when mtc_done is asserted with
 *        the  mtc_status field set to 1 or 3.
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_mtc_ctl_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 27;
     unsigned      mtc_event_enable                          :  1;
     unsigned      mtc_chip_reset_enable1                    :  1;
     unsigned      mtc_chip_reset_enable0                    :  1;
     unsigned      mtc_system_reset_enable1                  :  1;
     unsigned      mtc_system_reset_enable0                  :  1;
#else    /* Little Endian */
     unsigned      mtc_system_reset_enable0                  :  1;
     unsigned      mtc_system_reset_enable1                  :  1;
     unsigned      mtc_chip_reset_enable0                    :  1;
     unsigned      mtc_chip_reset_enable1                    :  1;
     unsigned      mtc_event_enable                          :  1;
     unsigned      reserved0                                 : 27;
#endif
} ncp_syscon_mtc_ctl_r_xlf_t;

/*! @struct ncp_syscon_mtc_status_r_xlf_t
 *  @brief MTC Event Status Register
 *  @details This register is reset only by a pin reset and contains the status for MTC events.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_mtc_status_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param mtc_done </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> If set, indicates the mtc_status field is valid. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mtc_status </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> If mtc_done is set, this field indicates the status
 *        for the last MTC event.
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_mtc_status_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 29;
     unsigned      mtc_done                                  :  1;
     unsigned      mtc_status                                :  2;
#else    /* Little Endian */
     unsigned      mtc_status                                :  2;
     unsigned      mtc_done                                  :  1;
     unsigned      reserved0                                 : 29;
#endif
} ncp_syscon_mtc_status_r_xlf_t;

/*! @struct ncp_syscon_allow_timer_r_xlf_t
 *  @brief Allow Non-Secure Physical Timer Reset Register
 *  @details If a bit is set, allows the expiration of the specified CPU's non-secure physical timer to generate a reset_cpu sequence
	for that CPU.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_allow_timer_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer31 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Allow CPU31 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer30 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Allow CPU30 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer29 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Allow CPU29 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer28 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Allow CPU28 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer27 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Allow CPU27 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer26 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Allow CPU26 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer25 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Allow CPU25 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer24 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Allow CPU24 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer23 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Allow CPU23 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer22 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Allow CPU22 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer21 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Allow CPU21 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer20 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Allow CPU20 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer19 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Allow CPU19 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer18 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Allow CPU18 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer17 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Allow CPU17 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer16 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Allow CPU16 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer15 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Allow CPU15 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer14 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Allow CPU14 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer13 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Allow CPU13 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer12 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Allow CPU12 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer11 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Allow CPU11 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer10 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Allow CPU10 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer9 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Allow CPU9 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer8 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allow CPU8 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Allow CPU7 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Allow CPU6 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Allow CPU5 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Allow CPU4 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Allow CPU3 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Allow CPU2 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Allow CPU1 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allow_timer0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allow CPU0 to be reset if it's non-secure physical
 *        timer expires
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_allow_timer_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      allow_timer31                             :  1;
     unsigned      allow_timer30                             :  1;
     unsigned      allow_timer29                             :  1;
     unsigned      allow_timer28                             :  1;
     unsigned      allow_timer27                             :  1;
     unsigned      allow_timer26                             :  1;
     unsigned      allow_timer25                             :  1;
     unsigned      allow_timer24                             :  1;
     unsigned      allow_timer23                             :  1;
     unsigned      allow_timer22                             :  1;
     unsigned      allow_timer21                             :  1;
     unsigned      allow_timer20                             :  1;
     unsigned      allow_timer19                             :  1;
     unsigned      allow_timer18                             :  1;
     unsigned      allow_timer17                             :  1;
     unsigned      allow_timer16                             :  1;
     unsigned      allow_timer15                             :  1;
     unsigned      allow_timer14                             :  1;
     unsigned      allow_timer13                             :  1;
     unsigned      allow_timer12                             :  1;
     unsigned      allow_timer11                             :  1;
     unsigned      allow_timer10                             :  1;
     unsigned      allow_timer9                              :  1;
     unsigned      allow_timer8                              :  1;
     unsigned      allow_timer7                              :  1;
     unsigned      allow_timer6                              :  1;
     unsigned      allow_timer5                              :  1;
     unsigned      allow_timer4                              :  1;
     unsigned      allow_timer3                              :  1;
     unsigned      allow_timer2                              :  1;
     unsigned      allow_timer1                              :  1;
     unsigned      allow_timer0                              :  1;
#else    /* Little Endian */
     unsigned      allow_timer0                              :  1;
     unsigned      allow_timer1                              :  1;
     unsigned      allow_timer2                              :  1;
     unsigned      allow_timer3                              :  1;
     unsigned      allow_timer4                              :  1;
     unsigned      allow_timer5                              :  1;
     unsigned      allow_timer6                              :  1;
     unsigned      allow_timer7                              :  1;
     unsigned      allow_timer8                              :  1;
     unsigned      allow_timer9                              :  1;
     unsigned      allow_timer10                             :  1;
     unsigned      allow_timer11                             :  1;
     unsigned      allow_timer12                             :  1;
     unsigned      allow_timer13                             :  1;
     unsigned      allow_timer14                             :  1;
     unsigned      allow_timer15                             :  1;
     unsigned      allow_timer16                             :  1;
     unsigned      allow_timer17                             :  1;
     unsigned      allow_timer18                             :  1;
     unsigned      allow_timer19                             :  1;
     unsigned      allow_timer20                             :  1;
     unsigned      allow_timer21                             :  1;
     unsigned      allow_timer22                             :  1;
     unsigned      allow_timer23                             :  1;
     unsigned      allow_timer24                             :  1;
     unsigned      allow_timer25                             :  1;
     unsigned      allow_timer26                             :  1;
     unsigned      allow_timer27                             :  1;
     unsigned      allow_timer28                             :  1;
     unsigned      allow_timer29                             :  1;
     unsigned      allow_timer30                             :  1;
     unsigned      allow_timer31                             :  1;
#endif
} ncp_syscon_allow_timer_r_xlf_t;

/*! @struct ncp_syscon_pwr_AINACTS_r_xlf_t
 *  @brief ACP Active Register
 *  @details Using the CPU powerdown sequence controlled by the CPU Powerdown Request register will set bits in this register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_AINACTS_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_ainacts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_ainacts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_ainacts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_ainacts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_ainacts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_ainacts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_ainacts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_ainacts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_AINACTS_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_ainacts                          :  1;
     unsigned      cluster6_ainacts                          :  1;
     unsigned      cluster5_ainacts                          :  1;
     unsigned      cluster4_ainacts                          :  1;
     unsigned      cluster3_ainacts                          :  1;
     unsigned      cluster2_ainacts                          :  1;
     unsigned      cluster1_ainacts                          :  1;
     unsigned      cluster0_ainacts                          :  1;
#else    /* Little Endian */
     unsigned      cluster0_ainacts                          :  1;
     unsigned      cluster1_ainacts                          :  1;
     unsigned      cluster2_ainacts                          :  1;
     unsigned      cluster3_ainacts                          :  1;
     unsigned      cluster4_ainacts                          :  1;
     unsigned      cluster5_ainacts                          :  1;
     unsigned      cluster6_ainacts                          :  1;
     unsigned      cluster7_ainacts                          :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_AINACTS_r_xlf_t;

/*! @struct ncp_syscon_pwr_CPUQREQ_r_xlf_t
 *  @brief CPU Clock Disable Request Register
 *  @details If a bit is set, the corresponding CPU is requested to disable its clocks.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_CPUQREQ_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cpu31_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> CPU 31 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu30_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> CPU 30 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu29_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> CPU 29 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu28_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> CPU 28 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu27_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> CPU 27 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu26_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> CPU 26 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu25_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> CPU 25 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu24_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> CPU 24 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu23_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> CPU 23 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu22_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> CPU 22 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu21_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> CPU 21 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu20_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> CPU 20 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu19_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> CPU 19 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu18_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> CPU 18 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu17_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> CPU 17 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu16_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> CPU 16 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu15_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> CPU 15 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu14_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> CPU 14 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu13_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> CPU 13 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu12_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> CPU 12 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu11_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> CPU 11 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu10_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> CPU 10 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu9_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> CPU 9 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu8_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> CPU 8 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu7_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU 7 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu6_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU 6 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu5_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU 5 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu4_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU 4 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu3_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU 3 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu2_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU 2 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu1_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU 1 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu0_qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU 0 clock disable request. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_CPUQREQ_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      cpu31_qreq                                :  1;
     unsigned      cpu30_qreq                                :  1;
     unsigned      cpu29_qreq                                :  1;
     unsigned      cpu28_qreq                                :  1;
     unsigned      cpu27_qreq                                :  1;
     unsigned      cpu26_qreq                                :  1;
     unsigned      cpu25_qreq                                :  1;
     unsigned      cpu24_qreq                                :  1;
     unsigned      cpu23_qreq                                :  1;
     unsigned      cpu22_qreq                                :  1;
     unsigned      cpu21_qreq                                :  1;
     unsigned      cpu20_qreq                                :  1;
     unsigned      cpu19_qreq                                :  1;
     unsigned      cpu18_qreq                                :  1;
     unsigned      cpu17_qreq                                :  1;
     unsigned      cpu16_qreq                                :  1;
     unsigned      cpu15_qreq                                :  1;
     unsigned      cpu14_qreq                                :  1;
     unsigned      cpu13_qreq                                :  1;
     unsigned      cpu12_qreq                                :  1;
     unsigned      cpu11_qreq                                :  1;
     unsigned      cpu10_qreq                                :  1;
     unsigned      cpu9_qreq                                 :  1;
     unsigned      cpu8_qreq                                 :  1;
     unsigned      cpu7_qreq                                 :  1;
     unsigned      cpu6_qreq                                 :  1;
     unsigned      cpu5_qreq                                 :  1;
     unsigned      cpu4_qreq                                 :  1;
     unsigned      cpu3_qreq                                 :  1;
     unsigned      cpu2_qreq                                 :  1;
     unsigned      cpu1_qreq                                 :  1;
     unsigned      cpu0_qreq                                 :  1;
#else    /* Little Endian */
     unsigned      cpu0_qreq                                 :  1;
     unsigned      cpu1_qreq                                 :  1;
     unsigned      cpu2_qreq                                 :  1;
     unsigned      cpu3_qreq                                 :  1;
     unsigned      cpu4_qreq                                 :  1;
     unsigned      cpu5_qreq                                 :  1;
     unsigned      cpu6_qreq                                 :  1;
     unsigned      cpu7_qreq                                 :  1;
     unsigned      cpu8_qreq                                 :  1;
     unsigned      cpu9_qreq                                 :  1;
     unsigned      cpu10_qreq                                :  1;
     unsigned      cpu11_qreq                                :  1;
     unsigned      cpu12_qreq                                :  1;
     unsigned      cpu13_qreq                                :  1;
     unsigned      cpu14_qreq                                :  1;
     unsigned      cpu15_qreq                                :  1;
     unsigned      cpu16_qreq                                :  1;
     unsigned      cpu17_qreq                                :  1;
     unsigned      cpu18_qreq                                :  1;
     unsigned      cpu19_qreq                                :  1;
     unsigned      cpu20_qreq                                :  1;
     unsigned      cpu21_qreq                                :  1;
     unsigned      cpu22_qreq                                :  1;
     unsigned      cpu23_qreq                                :  1;
     unsigned      cpu24_qreq                                :  1;
     unsigned      cpu25_qreq                                :  1;
     unsigned      cpu26_qreq                                :  1;
     unsigned      cpu27_qreq                                :  1;
     unsigned      cpu28_qreq                                :  1;
     unsigned      cpu29_qreq                                :  1;
     unsigned      cpu30_qreq                                :  1;
     unsigned      cpu31_qreq                                :  1;
#endif
} ncp_syscon_pwr_CPUQREQ_r_xlf_t;

/*! @struct ncp_syscon_pwr_CSYSREQ_APB_r_xlf_t
 *  @brief CPU Cluster APB Bridge Powerup Request Register
 *  @details If a bit is set, the corresponding CPU cluster is requested to powerup its APB bridges.
         Using the CPU powerdown sequence controlled by the CPU Powerdown Request register will reset bits in this register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_CSYSREQ_APB_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_csysreq_apb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 APB bridge powerup request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_csysreq_apb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 APB bridge powerup request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_csysreq_apb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 APB bridge powerup request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_csysreq_apb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 APB bridge powerup request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_csysreq_apb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 APB bridge powerup request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_csysreq_apb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 APB bridge powerup request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_csysreq_apb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 APB bridge powerup request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_csysreq_apb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 APB bridge powerup request. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_CSYSREQ_APB_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_csysreq_apb                      :  1;
     unsigned      cluster6_csysreq_apb                      :  1;
     unsigned      cluster5_csysreq_apb                      :  1;
     unsigned      cluster4_csysreq_apb                      :  1;
     unsigned      cluster3_csysreq_apb                      :  1;
     unsigned      cluster2_csysreq_apb                      :  1;
     unsigned      cluster1_csysreq_apb                      :  1;
     unsigned      cluster0_csysreq_apb                      :  1;
#else    /* Little Endian */
     unsigned      cluster0_csysreq_apb                      :  1;
     unsigned      cluster1_csysreq_apb                      :  1;
     unsigned      cluster2_csysreq_apb                      :  1;
     unsigned      cluster3_csysreq_apb                      :  1;
     unsigned      cluster4_csysreq_apb                      :  1;
     unsigned      cluster5_csysreq_apb                      :  1;
     unsigned      cluster6_csysreq_apb                      :  1;
     unsigned      cluster7_csysreq_apb                      :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_CSYSREQ_APB_r_xlf_t;

/*! @struct ncp_syscon_pwr_CSYSREQ_ATB_r_xlf_t
 *  @brief CPU Cluster ATB Bridge Powerup Request Register
 *  @details If a bit is set, the corresponding CPU cluster is requested to powerup its ATB bridges.
         Using the CPU powerdown sequence controlled by the CPU Powerdown Request register will reset bits in this register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_CSYSREQ_ATB_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_csysreq_atb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 ATB bridge powerup request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_csysreq_atb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 ATB bridge powerup request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_csysreq_atb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 ATB bridge powerup request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_csysreq_atb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 ATB bridge powerup request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_csysreq_atb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 ATB bridge powerup request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_csysreq_atb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 ATB bridge powerup request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_csysreq_atb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 ATB bridge powerup request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_csysreq_atb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 ATB bridge powerup request. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_CSYSREQ_ATB_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_csysreq_atb                      :  1;
     unsigned      cluster6_csysreq_atb                      :  1;
     unsigned      cluster5_csysreq_atb                      :  1;
     unsigned      cluster4_csysreq_atb                      :  1;
     unsigned      cluster3_csysreq_atb                      :  1;
     unsigned      cluster2_csysreq_atb                      :  1;
     unsigned      cluster1_csysreq_atb                      :  1;
     unsigned      cluster0_csysreq_atb                      :  1;
#else    /* Little Endian */
     unsigned      cluster0_csysreq_atb                      :  1;
     unsigned      cluster1_csysreq_atb                      :  1;
     unsigned      cluster2_csysreq_atb                      :  1;
     unsigned      cluster3_csysreq_atb                      :  1;
     unsigned      cluster4_csysreq_atb                      :  1;
     unsigned      cluster5_csysreq_atb                      :  1;
     unsigned      cluster6_csysreq_atb                      :  1;
     unsigned      cluster7_csysreq_atb                      :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_CSYSREQ_ATB_r_xlf_t;

/*! @struct ncp_syscon_pwr_CSYSREQ_CNT_r_xlf_t
 *  @brief CPU Cluster System Counter Bridge Powerup Request Register
 *  @details If a bit is set, the corresponding CPU cluster is requested to powerup its system counter bridges.
         Using the CPU powerdown sequence controlled by the CPU Powerdown Request register will reset bits in this register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_CSYSREQ_CNT_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_csysreq_cnt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 system counter bridge powerup request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_csysreq_cnt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 system counter bridge powerup request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_csysreq_cnt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 system counter bridge powerup request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_csysreq_cnt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 system counter bridge powerup request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_csysreq_cnt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 system counter bridge powerup request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_csysreq_cnt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 system counter bridge powerup request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_csysreq_cnt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 system counter bridge powerup request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_csysreq_cnt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 system counter bridge powerup request. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_CSYSREQ_CNT_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_csysreq_cnt                      :  1;
     unsigned      cluster6_csysreq_cnt                      :  1;
     unsigned      cluster5_csysreq_cnt                      :  1;
     unsigned      cluster4_csysreq_cnt                      :  1;
     unsigned      cluster3_csysreq_cnt                      :  1;
     unsigned      cluster2_csysreq_cnt                      :  1;
     unsigned      cluster1_csysreq_cnt                      :  1;
     unsigned      cluster0_csysreq_cnt                      :  1;
#else    /* Little Endian */
     unsigned      cluster0_csysreq_cnt                      :  1;
     unsigned      cluster1_csysreq_cnt                      :  1;
     unsigned      cluster2_csysreq_cnt                      :  1;
     unsigned      cluster3_csysreq_cnt                      :  1;
     unsigned      cluster4_csysreq_cnt                      :  1;
     unsigned      cluster5_csysreq_cnt                      :  1;
     unsigned      cluster6_csysreq_cnt                      :  1;
     unsigned      cluster7_csysreq_cnt                      :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_CSYSREQ_CNT_r_xlf_t;

/*! @struct ncp_syscon_pwr_CSYSREQ_TS_r_xlf_t
 *  @brief CPU Cluster Timestamp Bridge Powerup Request Register
 *  @details If a bit is set, the corresponding CPU cluster is requested to powerup its timestamp bridges.
         Using the CPU powerdown sequence controlled by the CPU Powerdown Request register will reset bits in this register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_CSYSREQ_TS_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_csysreq_ts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 timestamp bridge powerup request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_csysreq_ts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 timestamp bridge powerup request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_csysreq_ts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 timestamp bridge powerup request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_csysreq_ts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 timestamp bridge powerup request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_csysreq_ts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 timestamp bridge powerup request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_csysreq_ts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 timestamp bridge powerup request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_csysreq_ts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 timestamp bridge powerup request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_csysreq_ts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 timestamp bridge powerup request. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_CSYSREQ_TS_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_csysreq_ts                       :  1;
     unsigned      cluster6_csysreq_ts                       :  1;
     unsigned      cluster5_csysreq_ts                       :  1;
     unsigned      cluster4_csysreq_ts                       :  1;
     unsigned      cluster3_csysreq_ts                       :  1;
     unsigned      cluster2_csysreq_ts                       :  1;
     unsigned      cluster1_csysreq_ts                       :  1;
     unsigned      cluster0_csysreq_ts                       :  1;
#else    /* Little Endian */
     unsigned      cluster0_csysreq_ts                       :  1;
     unsigned      cluster1_csysreq_ts                       :  1;
     unsigned      cluster2_csysreq_ts                       :  1;
     unsigned      cluster3_csysreq_ts                       :  1;
     unsigned      cluster4_csysreq_ts                       :  1;
     unsigned      cluster5_csysreq_ts                       :  1;
     unsigned      cluster6_csysreq_ts                       :  1;
     unsigned      cluster7_csysreq_ts                       :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_CSYSREQ_TS_r_xlf_t;

/*! @struct ncp_syscon_pwr_DBGPWRDUP_r_xlf_t
 *  @brief CPU Powered Up Status Register
 *  @details If a bit is set, the corresponding CPU is indicated as powered up to the debug logic.
         Using the CPU powerdown sequence controlled by the CPU Powerdown Request register will reset bits in this register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_DBGPWRDUP_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cpu7_dbgpwrdup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU 7 powered up for debug. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu6_dbgpwrdup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU 6 powered up for debug. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu5_dbgpwrdup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU 5 powered up for debug. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu4_dbgpwrdup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU 4 powered up for debug. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu3_dbgpwrdup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU 3 powered up for debug. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu2_dbgpwrdup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU 2 powered up for debug. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu1_dbgpwrdup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU 1 powered up for debug. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu0_dbgpwrdup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU 0 powered up for debug. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_DBGPWRDUP_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cpu7_dbgpwrdup                            :  1;
     unsigned      cpu6_dbgpwrdup                            :  1;
     unsigned      cpu5_dbgpwrdup                            :  1;
     unsigned      cpu4_dbgpwrdup                            :  1;
     unsigned      cpu3_dbgpwrdup                            :  1;
     unsigned      cpu2_dbgpwrdup                            :  1;
     unsigned      cpu1_dbgpwrdup                            :  1;
     unsigned      cpu0_dbgpwrdup                            :  1;
#else    /* Little Endian */
     unsigned      cpu0_dbgpwrdup                            :  1;
     unsigned      cpu1_dbgpwrdup                            :  1;
     unsigned      cpu2_dbgpwrdup                            :  1;
     unsigned      cpu3_dbgpwrdup                            :  1;
     unsigned      cpu4_dbgpwrdup                            :  1;
     unsigned      cpu5_dbgpwrdup                            :  1;
     unsigned      cpu6_dbgpwrdup                            :  1;
     unsigned      cpu7_dbgpwrdup                            :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_DBGPWRDUP_r_xlf_t;

/*! @struct ncp_syscon_pwr_ISOLATECPU_r_xlf_t
 *  @brief CPU Power Isolation Register
 *  @details If a bit is set, the corresponding CPU's logic is isolated from other power domains.
         Using the CPU powerdown sequence controlled by the CPU Powerdown Request register will set bits in this register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_ISOLATECPU_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cpu31_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> CPU 31 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu30_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> CPU 30 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu29_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> CPU 29 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu28_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> CPU 28 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu27_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> CPU 27 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu26_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> CPU 26 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu25_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> CPU 25 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu24_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> CPU 24 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu23_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> CPU 23 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu22_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> CPU 22 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu21_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> CPU 21 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu20_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> CPU 20 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu19_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> CPU 19 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu18_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> CPU 18 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu17_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> CPU 17 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu16_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> CPU 16 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu15_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> CPU 15 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu14_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> CPU 14 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu13_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> CPU 13 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu12_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> CPU 12 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu11_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> CPU 11 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu10_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> CPU 10 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu9_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> CPU 9 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu8_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> CPU 8 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu7_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU 7 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu6_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU 6 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu5_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU 5 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu4_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU 4 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu3_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU 3 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu2_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU 2 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu1_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU 1 power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu0_isolatecpu </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU 0 power isolation enable </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_ISOLATECPU_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      cpu31_isolatecpu                          :  1;
     unsigned      cpu30_isolatecpu                          :  1;
     unsigned      cpu29_isolatecpu                          :  1;
     unsigned      cpu28_isolatecpu                          :  1;
     unsigned      cpu27_isolatecpu                          :  1;
     unsigned      cpu26_isolatecpu                          :  1;
     unsigned      cpu25_isolatecpu                          :  1;
     unsigned      cpu24_isolatecpu                          :  1;
     unsigned      cpu23_isolatecpu                          :  1;
     unsigned      cpu22_isolatecpu                          :  1;
     unsigned      cpu21_isolatecpu                          :  1;
     unsigned      cpu20_isolatecpu                          :  1;
     unsigned      cpu19_isolatecpu                          :  1;
     unsigned      cpu18_isolatecpu                          :  1;
     unsigned      cpu17_isolatecpu                          :  1;
     unsigned      cpu16_isolatecpu                          :  1;
     unsigned      cpu15_isolatecpu                          :  1;
     unsigned      cpu14_isolatecpu                          :  1;
     unsigned      cpu13_isolatecpu                          :  1;
     unsigned      cpu12_isolatecpu                          :  1;
     unsigned      cpu11_isolatecpu                          :  1;
     unsigned      cpu10_isolatecpu                          :  1;
     unsigned      cpu9_isolatecpu                           :  1;
     unsigned      cpu8_isolatecpu                           :  1;
     unsigned      cpu7_isolatecpu                           :  1;
     unsigned      cpu6_isolatecpu                           :  1;
     unsigned      cpu5_isolatecpu                           :  1;
     unsigned      cpu4_isolatecpu                           :  1;
     unsigned      cpu3_isolatecpu                           :  1;
     unsigned      cpu2_isolatecpu                           :  1;
     unsigned      cpu1_isolatecpu                           :  1;
     unsigned      cpu0_isolatecpu                           :  1;
#else    /* Little Endian */
     unsigned      cpu0_isolatecpu                           :  1;
     unsigned      cpu1_isolatecpu                           :  1;
     unsigned      cpu2_isolatecpu                           :  1;
     unsigned      cpu3_isolatecpu                           :  1;
     unsigned      cpu4_isolatecpu                           :  1;
     unsigned      cpu5_isolatecpu                           :  1;
     unsigned      cpu6_isolatecpu                           :  1;
     unsigned      cpu7_isolatecpu                           :  1;
     unsigned      cpu8_isolatecpu                           :  1;
     unsigned      cpu9_isolatecpu                           :  1;
     unsigned      cpu10_isolatecpu                          :  1;
     unsigned      cpu11_isolatecpu                          :  1;
     unsigned      cpu12_isolatecpu                          :  1;
     unsigned      cpu13_isolatecpu                          :  1;
     unsigned      cpu14_isolatecpu                          :  1;
     unsigned      cpu15_isolatecpu                          :  1;
     unsigned      cpu16_isolatecpu                          :  1;
     unsigned      cpu17_isolatecpu                          :  1;
     unsigned      cpu18_isolatecpu                          :  1;
     unsigned      cpu19_isolatecpu                          :  1;
     unsigned      cpu20_isolatecpu                          :  1;
     unsigned      cpu21_isolatecpu                          :  1;
     unsigned      cpu22_isolatecpu                          :  1;
     unsigned      cpu23_isolatecpu                          :  1;
     unsigned      cpu24_isolatecpu                          :  1;
     unsigned      cpu25_isolatecpu                          :  1;
     unsigned      cpu26_isolatecpu                          :  1;
     unsigned      cpu27_isolatecpu                          :  1;
     unsigned      cpu28_isolatecpu                          :  1;
     unsigned      cpu29_isolatecpu                          :  1;
     unsigned      cpu30_isolatecpu                          :  1;
     unsigned      cpu31_isolatecpu                          :  1;
#endif
} ncp_syscon_pwr_ISOLATECPU_r_xlf_t;

/*! @struct ncp_syscon_pwr_ISOLATETOP_r_xlf_t
 *  @brief CPU Cluster Top Power Isolation Register
 *  @details If a bit is set, the corresponding CPU cluster's top logic is isolated from other power domains.
         Using the CPU powerdown sequence controlled by the CPU Powerdown Request register will set bits in this register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_ISOLATETOP_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_isolatetop </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 top power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_isolatetop </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 top power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_isolatetop </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 top power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_isolatetop </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 top power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_isolatetop </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 top power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_isolatetop </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 top power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_isolatetop </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 top power isolation enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_isolatetop </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 top power isolation enable </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_ISOLATETOP_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_isolatetop                       :  1;
     unsigned      cluster6_isolatetop                       :  1;
     unsigned      cluster5_isolatetop                       :  1;
     unsigned      cluster4_isolatetop                       :  1;
     unsigned      cluster3_isolatetop                       :  1;
     unsigned      cluster2_isolatetop                       :  1;
     unsigned      cluster1_isolatetop                       :  1;
     unsigned      cluster0_isolatetop                       :  1;
#else    /* Little Endian */
     unsigned      cluster0_isolatetop                       :  1;
     unsigned      cluster1_isolatetop                       :  1;
     unsigned      cluster2_isolatetop                       :  1;
     unsigned      cluster3_isolatetop                       :  1;
     unsigned      cluster4_isolatetop                       :  1;
     unsigned      cluster5_isolatetop                       :  1;
     unsigned      cluster6_isolatetop                       :  1;
     unsigned      cluster7_isolatetop                       :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_ISOLATETOP_r_xlf_t;

/*! @struct ncp_syscon_pwr_L2FLUSHREQ_r_xlf_t
 *  @brief CPU Cluster L2 Flush Request Register
 *  @details If a bit is set, the corresponding CPU cluster's L2 is requested to initiate a flush operation.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_L2FLUSHREQ_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_l2flushreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 L2 flush request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_l2flushreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 L2 flush request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_l2flushreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 L2 flush request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_l2flushreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 L2 flush request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_l2flushreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 L2 flush request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_l2flushreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 L2 flush request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_l2flushreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 L2 flush request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_l2flushreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 L2 flush request. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_L2FLUSHREQ_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_l2flushreq                       :  1;
     unsigned      cluster6_l2flushreq                       :  1;
     unsigned      cluster5_l2flushreq                       :  1;
     unsigned      cluster4_l2flushreq                       :  1;
     unsigned      cluster3_l2flushreq                       :  1;
     unsigned      cluster2_l2flushreq                       :  1;
     unsigned      cluster1_l2flushreq                       :  1;
     unsigned      cluster0_l2flushreq                       :  1;
#else    /* Little Endian */
     unsigned      cluster0_l2flushreq                       :  1;
     unsigned      cluster1_l2flushreq                       :  1;
     unsigned      cluster2_l2flushreq                       :  1;
     unsigned      cluster3_l2flushreq                       :  1;
     unsigned      cluster4_l2flushreq                       :  1;
     unsigned      cluster5_l2flushreq                       :  1;
     unsigned      cluster6_l2flushreq                       :  1;
     unsigned      cluster7_l2flushreq                       :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_L2FLUSHREQ_r_xlf_t;

/*! @struct ncp_syscon_pwr_L2QREQ_r_xlf_t
 *  @brief CPU Cluster L2 Clock Disable Request Register
 *  @details If a bit is set, the corresponding CPU cluster's L2 is requested to disable its clocks.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_L2QREQ_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_l2qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 L2 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_l2qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 L2 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_l2qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 L2 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_l2qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 L2 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_l2qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 L2 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_l2qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 L2 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_l2qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 L2 clock disable request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_l2qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 L2 clock disable request. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_L2QREQ_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_l2qreq                           :  1;
     unsigned      cluster6_l2qreq                           :  1;
     unsigned      cluster5_l2qreq                           :  1;
     unsigned      cluster4_l2qreq                           :  1;
     unsigned      cluster3_l2qreq                           :  1;
     unsigned      cluster2_l2qreq                           :  1;
     unsigned      cluster1_l2qreq                           :  1;
     unsigned      cluster0_l2qreq                           :  1;
#else    /* Little Endian */
     unsigned      cluster0_l2qreq                           :  1;
     unsigned      cluster1_l2qreq                           :  1;
     unsigned      cluster2_l2qreq                           :  1;
     unsigned      cluster3_l2qreq                           :  1;
     unsigned      cluster4_l2qreq                           :  1;
     unsigned      cluster5_l2qreq                           :  1;
     unsigned      cluster6_l2qreq                           :  1;
     unsigned      cluster7_l2qreq                           :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_L2QREQ_r_xlf_t;

/*! @struct ncp_syscon_pwr_PREQ_r_xlf_t
 *  @brief CPU Cluster Power State Change Request Register
 *  @details If a bit is set, the corresponding CPU cluster is requested to initiate a power state change to the state
	 specified in the corresponding field of the CPU Cluster Requested Power State register.
         Using the CPU powerdown sequence controlled by the CPU Powerdown Request register will set and/or reset bits
	 in this register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_PREQ_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_preq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_preq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_preq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_preq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_preq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_preq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_preq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_preq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 power state change request. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_PREQ_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_preq                             :  1;
     unsigned      cluster6_preq                             :  1;
     unsigned      cluster5_preq                             :  1;
     unsigned      cluster4_preq                             :  1;
     unsigned      cluster3_preq                             :  1;
     unsigned      cluster2_preq                             :  1;
     unsigned      cluster1_preq                             :  1;
     unsigned      cluster0_preq                             :  1;
#else    /* Little Endian */
     unsigned      cluster0_preq                             :  1;
     unsigned      cluster1_preq                             :  1;
     unsigned      cluster2_preq                             :  1;
     unsigned      cluster3_preq                             :  1;
     unsigned      cluster4_preq                             :  1;
     unsigned      cluster5_preq                             :  1;
     unsigned      cluster6_preq                             :  1;
     unsigned      cluster7_preq                             :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_PREQ_r_xlf_t;

/*! @struct ncp_syscon_pwr_PSTATE_r_xlf_t
 *  @brief CPU Cluster Requested Power State Register
 *  @details Each field contains the power state being requested for the corresponding CPU cluster if that cluster is
	 currently requesting a power state change through the CPU Cluster Power State Change Request register.
         Using the CPU powerdown sequence controlled by the CPU Powerdown Request register will reset bits in this register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_PSTATE_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_pstate </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 requested power state. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_pstate </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 requested power state. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_pstate </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 requested power state. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_pstate </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 requested power state. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_pstate </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 requested power state. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_pstate </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 requested power state. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_pstate </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 requested power state. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_pstate </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 requested power state. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_PSTATE_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_pstate                           :  1;
     unsigned      cluster6_pstate                           :  1;
     unsigned      cluster5_pstate                           :  1;
     unsigned      cluster4_pstate                           :  1;
     unsigned      cluster3_pstate                           :  1;
     unsigned      cluster2_pstate                           :  1;
     unsigned      cluster1_pstate                           :  1;
     unsigned      cluster0_pstate                           :  1;
#else    /* Little Endian */
     unsigned      cluster0_pstate                           :  1;
     unsigned      cluster1_pstate                           :  1;
     unsigned      cluster2_pstate                           :  1;
     unsigned      cluster3_pstate                           :  1;
     unsigned      cluster4_pstate                           :  1;
     unsigned      cluster5_pstate                           :  1;
     unsigned      cluster6_pstate                           :  1;
     unsigned      cluster7_pstate                           :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_PSTATE_r_xlf_t;

/*! @struct ncp_syscon_pwr_PWRDNREQ_ACP_r_xlf_t
 *  @brief CPU Cluster ACP Powerdown Request Register
 *  @details If a bit is set, the corresponding CPU cluster is requested to powerdown its ACP logic.
         Using the CPU powerdown sequence controlled by the CPU Powerdown Request register will set bits in this register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_PWRDNREQ_ACP_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_pwrdnreq_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 ACP powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_pwrdnreq_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 ACP powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_pwrdnreq_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 ACP powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_pwrdnreq_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 ACP powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_pwrdnreq_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 ACP powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_pwrdnreq_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 ACP powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_pwrdnreq_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 ACP powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_pwrdnreq_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 ACP powerdown request. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_PWRDNREQ_ACP_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_pwrdnreq_acp                     :  1;
     unsigned      cluster6_pwrdnreq_acp                     :  1;
     unsigned      cluster5_pwrdnreq_acp                     :  1;
     unsigned      cluster4_pwrdnreq_acp                     :  1;
     unsigned      cluster3_pwrdnreq_acp                     :  1;
     unsigned      cluster2_pwrdnreq_acp                     :  1;
     unsigned      cluster1_pwrdnreq_acp                     :  1;
     unsigned      cluster0_pwrdnreq_acp                     :  1;
#else    /* Little Endian */
     unsigned      cluster0_pwrdnreq_acp                     :  1;
     unsigned      cluster1_pwrdnreq_acp                     :  1;
     unsigned      cluster2_pwrdnreq_acp                     :  1;
     unsigned      cluster3_pwrdnreq_acp                     :  1;
     unsigned      cluster4_pwrdnreq_acp                     :  1;
     unsigned      cluster5_pwrdnreq_acp                     :  1;
     unsigned      cluster6_pwrdnreq_acp                     :  1;
     unsigned      cluster7_pwrdnreq_acp                     :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_PWRDNREQ_ACP_r_xlf_t;

/*! @struct ncp_syscon_pwr_PWRDNREQ_ICCT_r_xlf_t
 *  @brief CPU Cluster ICCT Powerdown Request Register
 *  @details If a bit is set, the corresponding CPU cluster is requested to powerdown its GIC ICCT streaming interface.
         Using the CPU powerdown sequence controlled by the CPU Powerdown Request register will set bits in this register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_PWRDNREQ_ICCT_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_pwrdnreq_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 GIC ICCT powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_pwrdnreq_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 GIC ICCT powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_pwrdnreq_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 GIC ICCT powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_pwrdnreq_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 GIC ICCT powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_pwrdnreq_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 GIC ICCT powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_pwrdnreq_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 GIC ICCT powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_pwrdnreq_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 GIC ICCT powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_pwrdnreq_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 GIC ICCT powerdown request. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_PWRDNREQ_ICCT_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_pwrdnreq_icct                    :  1;
     unsigned      cluster6_pwrdnreq_icct                    :  1;
     unsigned      cluster5_pwrdnreq_icct                    :  1;
     unsigned      cluster4_pwrdnreq_icct                    :  1;
     unsigned      cluster3_pwrdnreq_icct                    :  1;
     unsigned      cluster2_pwrdnreq_icct                    :  1;
     unsigned      cluster1_pwrdnreq_icct                    :  1;
     unsigned      cluster0_pwrdnreq_icct                    :  1;
#else    /* Little Endian */
     unsigned      cluster0_pwrdnreq_icct                    :  1;
     unsigned      cluster1_pwrdnreq_icct                    :  1;
     unsigned      cluster2_pwrdnreq_icct                    :  1;
     unsigned      cluster3_pwrdnreq_icct                    :  1;
     unsigned      cluster4_pwrdnreq_icct                    :  1;
     unsigned      cluster5_pwrdnreq_icct                    :  1;
     unsigned      cluster6_pwrdnreq_icct                    :  1;
     unsigned      cluster7_pwrdnreq_icct                    :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_PWRDNREQ_ICCT_r_xlf_t;

/*! @struct ncp_syscon_pwr_PWRDNREQ_ICDT_r_xlf_t
 *  @brief CPU Cluster ICDT Powerdown Request Register
 *  @details If a bit is set, the corresponding CPU cluster is requested to powerdown its GIC ICDT streaming interface.
         Using the CPU powerdown sequence controlled by the CPU Powerdown Request register will set bits in this register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_PWRDNREQ_ICDT_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_pwrdnreq_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 GIC ICDT powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_pwrdnreq_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 GIC ICDT powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_pwrdnreq_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 GIC ICDT powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_pwrdnreq_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 GIC ICDT powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_pwrdnreq_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 GIC ICDT powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_pwrdnreq_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 GIC ICDT powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_pwrdnreq_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 GIC ICDT powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_pwrdnreq_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 GIC ICDT powerdown request. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_PWRDNREQ_ICDT_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_pwrdnreq_icdt                    :  1;
     unsigned      cluster6_pwrdnreq_icdt                    :  1;
     unsigned      cluster5_pwrdnreq_icdt                    :  1;
     unsigned      cluster4_pwrdnreq_icdt                    :  1;
     unsigned      cluster3_pwrdnreq_icdt                    :  1;
     unsigned      cluster2_pwrdnreq_icdt                    :  1;
     unsigned      cluster1_pwrdnreq_icdt                    :  1;
     unsigned      cluster0_pwrdnreq_icdt                    :  1;
#else    /* Little Endian */
     unsigned      cluster0_pwrdnreq_icdt                    :  1;
     unsigned      cluster1_pwrdnreq_icdt                    :  1;
     unsigned      cluster2_pwrdnreq_icdt                    :  1;
     unsigned      cluster3_pwrdnreq_icdt                    :  1;
     unsigned      cluster4_pwrdnreq_icdt                    :  1;
     unsigned      cluster5_pwrdnreq_icdt                    :  1;
     unsigned      cluster6_pwrdnreq_icdt                    :  1;
     unsigned      cluster7_pwrdnreq_icdt                    :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_PWRDNREQ_ICDT_r_xlf_t;

/*! @struct ncp_syscon_pwr_PWRUPCPU_r_xlf_t
 *  @brief CPU Powerup Request Register
 *  @details If a bit is set, the corresponding CPU is requested to powerup.
         Using the CPU powerdown sequence controlled by the CPU Powerdown Request register will reset bits in this register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_PWRUPCPU_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cpu31_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> CPU 31 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu30_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> CPU 30 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu29_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> CPU 29 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu28_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> CPU 28 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu27_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> CPU 27 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu26_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> CPU 26 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu25_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> CPU 25 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu24_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> CPU 24 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu23_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> CPU 23 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu22_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> CPU 22 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu21_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> CPU 21 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu20_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> CPU 20 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu19_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> CPU 19 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu18_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> CPU 18 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu17_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> CPU 17 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu16_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> CPU 16 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu15_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> CPU 15 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu14_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> CPU 14 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu13_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> CPU 13 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu12_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> CPU 12 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu11_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> CPU 11 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu10_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> CPU 10 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu9_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> CPU 9 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu8_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> CPU 8 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu7_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU 7 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu6_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU 6 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu5_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU 5 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu4_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU 4 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu3_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU 3 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu2_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU 2 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu1_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU 1 powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu0_pwrup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU 0 powerup enable. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_PWRUPCPU_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      cpu31_pwrup                               :  1;
     unsigned      cpu30_pwrup                               :  1;
     unsigned      cpu29_pwrup                               :  1;
     unsigned      cpu28_pwrup                               :  1;
     unsigned      cpu27_pwrup                               :  1;
     unsigned      cpu26_pwrup                               :  1;
     unsigned      cpu25_pwrup                               :  1;
     unsigned      cpu24_pwrup                               :  1;
     unsigned      cpu23_pwrup                               :  1;
     unsigned      cpu22_pwrup                               :  1;
     unsigned      cpu21_pwrup                               :  1;
     unsigned      cpu20_pwrup                               :  1;
     unsigned      cpu19_pwrup                               :  1;
     unsigned      cpu18_pwrup                               :  1;
     unsigned      cpu17_pwrup                               :  1;
     unsigned      cpu16_pwrup                               :  1;
     unsigned      cpu15_pwrup                               :  1;
     unsigned      cpu14_pwrup                               :  1;
     unsigned      cpu13_pwrup                               :  1;
     unsigned      cpu12_pwrup                               :  1;
     unsigned      cpu11_pwrup                               :  1;
     unsigned      cpu10_pwrup                               :  1;
     unsigned      cpu9_pwrup                                :  1;
     unsigned      cpu8_pwrup                                :  1;
     unsigned      cpu7_pwrup                                :  1;
     unsigned      cpu6_pwrup                                :  1;
     unsigned      cpu5_pwrup                                :  1;
     unsigned      cpu4_pwrup                                :  1;
     unsigned      cpu3_pwrup                                :  1;
     unsigned      cpu2_pwrup                                :  1;
     unsigned      cpu1_pwrup                                :  1;
     unsigned      cpu0_pwrup                                :  1;
#else    /* Little Endian */
     unsigned      cpu0_pwrup                                :  1;
     unsigned      cpu1_pwrup                                :  1;
     unsigned      cpu2_pwrup                                :  1;
     unsigned      cpu3_pwrup                                :  1;
     unsigned      cpu4_pwrup                                :  1;
     unsigned      cpu5_pwrup                                :  1;
     unsigned      cpu6_pwrup                                :  1;
     unsigned      cpu7_pwrup                                :  1;
     unsigned      cpu8_pwrup                                :  1;
     unsigned      cpu9_pwrup                                :  1;
     unsigned      cpu10_pwrup                               :  1;
     unsigned      cpu11_pwrup                               :  1;
     unsigned      cpu12_pwrup                               :  1;
     unsigned      cpu13_pwrup                               :  1;
     unsigned      cpu14_pwrup                               :  1;
     unsigned      cpu15_pwrup                               :  1;
     unsigned      cpu16_pwrup                               :  1;
     unsigned      cpu17_pwrup                               :  1;
     unsigned      cpu18_pwrup                               :  1;
     unsigned      cpu19_pwrup                               :  1;
     unsigned      cpu20_pwrup                               :  1;
     unsigned      cpu21_pwrup                               :  1;
     unsigned      cpu22_pwrup                               :  1;
     unsigned      cpu23_pwrup                               :  1;
     unsigned      cpu24_pwrup                               :  1;
     unsigned      cpu25_pwrup                               :  1;
     unsigned      cpu26_pwrup                               :  1;
     unsigned      cpu27_pwrup                               :  1;
     unsigned      cpu28_pwrup                               :  1;
     unsigned      cpu29_pwrup                               :  1;
     unsigned      cpu30_pwrup                               :  1;
     unsigned      cpu31_pwrup                               :  1;
#endif
} ncp_syscon_pwr_PWRUPCPU_r_xlf_t;

/*! @struct ncp_syscon_pwr_PWRUPTOP_r_xlf_t
 *  @brief CPU Cluster Top Powerup Request Register
 *  @details If a bit is set, the corresponding CPU cluster is requested to powerup its top logic.
         Using the CPU powerdown sequence controlled by the CPU Powerdown Request register will reset bits in this register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_PWRUPTOP_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_pwruptop </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 top powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_pwruptop </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 top powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_pwruptop </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 top powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_pwruptop </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 top powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_pwruptop </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 top powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_pwruptop </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 top powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_pwruptop </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 top powerup enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_pwruptop </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 top powerup enable. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_PWRUPTOP_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_pwruptop                         :  1;
     unsigned      cluster6_pwruptop                         :  1;
     unsigned      cluster5_pwruptop                         :  1;
     unsigned      cluster4_pwruptop                         :  1;
     unsigned      cluster3_pwruptop                         :  1;
     unsigned      cluster2_pwruptop                         :  1;
     unsigned      cluster1_pwruptop                         :  1;
     unsigned      cluster0_pwruptop                         :  1;
#else    /* Little Endian */
     unsigned      cluster0_pwruptop                         :  1;
     unsigned      cluster1_pwruptop                         :  1;
     unsigned      cluster2_pwruptop                         :  1;
     unsigned      cluster3_pwruptop                         :  1;
     unsigned      cluster4_pwruptop                         :  1;
     unsigned      cluster5_pwruptop                         :  1;
     unsigned      cluster6_pwruptop                         :  1;
     unsigned      cluster7_pwruptop                         :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_PWRUPTOP_r_xlf_t;

/*! @struct ncp_syscon_pwr_SINACT_r_xlf_t
 *  @brief CPU Cluster Snoop Inactive Register
 *  @details If a bit is set, the corresponding CPU cluster's L2 is signaled that their are no outstanding snoops and it
	 can deactivate its TX and RX snoop links.
         Using the CPU powerdown sequence controlled by the CPU Powerdown Request register will set bits in this register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_SINACT_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_sinact </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 snoop inactive. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_sinact </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 snoop inactive. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_sinact </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 snoop inactive. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_sinact </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 snoop inactive. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_sinact </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 snoop inactive. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_sinact </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 snoop inactive. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_sinact </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 snoop inactive. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_sinact </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 snoop inactive. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_SINACT_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_sinact                           :  1;
     unsigned      cluster6_sinact                           :  1;
     unsigned      cluster5_sinact                           :  1;
     unsigned      cluster4_sinact                           :  1;
     unsigned      cluster3_sinact                           :  1;
     unsigned      cluster2_sinact                           :  1;
     unsigned      cluster1_sinact                           :  1;
     unsigned      cluster0_sinact                           :  1;
#else    /* Little Endian */
     unsigned      cluster0_sinact                           :  1;
     unsigned      cluster1_sinact                           :  1;
     unsigned      cluster2_sinact                           :  1;
     unsigned      cluster3_sinact                           :  1;
     unsigned      cluster4_sinact                           :  1;
     unsigned      cluster5_sinact                           :  1;
     unsigned      cluster6_sinact                           :  1;
     unsigned      cluster7_sinact                           :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_SINACT_r_xlf_t;

/*! @struct ncp_syscon_gic_cpu_active_r_xlf_t
 *  @brief GIC CPU Active Register
 *  @details If a bit is set, this indicates to the GIC that the corresponding CPU is active and able to accept interrupts.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_gic_cpu_active_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cpu31_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> CPU 31 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu30_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> CPU 30 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu29_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> CPU 29 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu28_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> CPU 28 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu27_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> CPU 27 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu26_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> CPU 26 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu25_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> CPU 25 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu24_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> CPU 24 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu23_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> CPU 23 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu22_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> CPU 22 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu21_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> CPU 21 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu20_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> CPU 20 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu19_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> CPU 19 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu18_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> CPU 18 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu17_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> CPU 17 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu16_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> CPU 16 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu15_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> CPU 15 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu14_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> CPU 14 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu13_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> CPU 13 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu12_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> CPU 12 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu11_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> CPU 11 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu10_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> CPU 10 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu9_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> CPU 9 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu8_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> CPU 8 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu7_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU 7 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu6_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU 6 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu5_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU 5 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu4_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU 4 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu3_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU 3 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu2_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU 2 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu1_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU 1 active indication to the GIC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu0_gic_cpu_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU 0 active indication to the GIC. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_gic_cpu_active_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      cpu31_gic_cpu_active                      :  1;
     unsigned      cpu30_gic_cpu_active                      :  1;
     unsigned      cpu29_gic_cpu_active                      :  1;
     unsigned      cpu28_gic_cpu_active                      :  1;
     unsigned      cpu27_gic_cpu_active                      :  1;
     unsigned      cpu26_gic_cpu_active                      :  1;
     unsigned      cpu25_gic_cpu_active                      :  1;
     unsigned      cpu24_gic_cpu_active                      :  1;
     unsigned      cpu23_gic_cpu_active                      :  1;
     unsigned      cpu22_gic_cpu_active                      :  1;
     unsigned      cpu21_gic_cpu_active                      :  1;
     unsigned      cpu20_gic_cpu_active                      :  1;
     unsigned      cpu19_gic_cpu_active                      :  1;
     unsigned      cpu18_gic_cpu_active                      :  1;
     unsigned      cpu17_gic_cpu_active                      :  1;
     unsigned      cpu16_gic_cpu_active                      :  1;
     unsigned      cpu15_gic_cpu_active                      :  1;
     unsigned      cpu14_gic_cpu_active                      :  1;
     unsigned      cpu13_gic_cpu_active                      :  1;
     unsigned      cpu12_gic_cpu_active                      :  1;
     unsigned      cpu11_gic_cpu_active                      :  1;
     unsigned      cpu10_gic_cpu_active                      :  1;
     unsigned      cpu9_gic_cpu_active                       :  1;
     unsigned      cpu8_gic_cpu_active                       :  1;
     unsigned      cpu7_gic_cpu_active                       :  1;
     unsigned      cpu6_gic_cpu_active                       :  1;
     unsigned      cpu5_gic_cpu_active                       :  1;
     unsigned      cpu4_gic_cpu_active                       :  1;
     unsigned      cpu3_gic_cpu_active                       :  1;
     unsigned      cpu2_gic_cpu_active                       :  1;
     unsigned      cpu1_gic_cpu_active                       :  1;
     unsigned      cpu0_gic_cpu_active                       :  1;
#else    /* Little Endian */
     unsigned      cpu0_gic_cpu_active                       :  1;
     unsigned      cpu1_gic_cpu_active                       :  1;
     unsigned      cpu2_gic_cpu_active                       :  1;
     unsigned      cpu3_gic_cpu_active                       :  1;
     unsigned      cpu4_gic_cpu_active                       :  1;
     unsigned      cpu5_gic_cpu_active                       :  1;
     unsigned      cpu6_gic_cpu_active                       :  1;
     unsigned      cpu7_gic_cpu_active                       :  1;
     unsigned      cpu8_gic_cpu_active                       :  1;
     unsigned      cpu9_gic_cpu_active                       :  1;
     unsigned      cpu10_gic_cpu_active                      :  1;
     unsigned      cpu11_gic_cpu_active                      :  1;
     unsigned      cpu12_gic_cpu_active                      :  1;
     unsigned      cpu13_gic_cpu_active                      :  1;
     unsigned      cpu14_gic_cpu_active                      :  1;
     unsigned      cpu15_gic_cpu_active                      :  1;
     unsigned      cpu16_gic_cpu_active                      :  1;
     unsigned      cpu17_gic_cpu_active                      :  1;
     unsigned      cpu18_gic_cpu_active                      :  1;
     unsigned      cpu19_gic_cpu_active                      :  1;
     unsigned      cpu20_gic_cpu_active                      :  1;
     unsigned      cpu21_gic_cpu_active                      :  1;
     unsigned      cpu22_gic_cpu_active                      :  1;
     unsigned      cpu23_gic_cpu_active                      :  1;
     unsigned      cpu24_gic_cpu_active                      :  1;
     unsigned      cpu25_gic_cpu_active                      :  1;
     unsigned      cpu26_gic_cpu_active                      :  1;
     unsigned      cpu27_gic_cpu_active                      :  1;
     unsigned      cpu28_gic_cpu_active                      :  1;
     unsigned      cpu29_gic_cpu_active                      :  1;
     unsigned      cpu30_gic_cpu_active                      :  1;
     unsigned      cpu31_gic_cpu_active                      :  1;
#endif
} ncp_syscon_gic_cpu_active_r_xlf_t;

/*! @struct ncp_syscon_gic_reactivate_r_xlf_t
 *  @brief GIC Reactivate CPUs Enable Register
 *  @details If a bit is set, when a leading edge is seen on the pwr_CLKEN signal for the corresponding CPU cluster, after a
	 delay (in reference cloks) specified by the GIC Reactivate Counter register, all of the bits in the GIC CPU Active
	 register for the CPUs in that CPU cluster will be set.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_gic_reactivate_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_gic_reactivate </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU cluster 7 GIC reactivate enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_gic_reactivate </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU cluster 6 GIC reactivate enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_gic_reactivate </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU cluster 5 GIC reactivate enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_gic_reactivate </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU cluster 4 GIC reactivate enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_gic_reactivate </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU cluster 3 GIC reactivate enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_gic_reactivate </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU cluster 2 GIC reactivate enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_gic_reactivate </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU cluster 1 GIC reactivate enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_gic_reactivate </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU cluster 0 GIC reactivate enable. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_gic_reactivate_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_gic_reactivate                   :  1;
     unsigned      cluster6_gic_reactivate                   :  1;
     unsigned      cluster5_gic_reactivate                   :  1;
     unsigned      cluster4_gic_reactivate                   :  1;
     unsigned      cluster3_gic_reactivate                   :  1;
     unsigned      cluster2_gic_reactivate                   :  1;
     unsigned      cluster1_gic_reactivate                   :  1;
     unsigned      cluster0_gic_reactivate                   :  1;
#else    /* Little Endian */
     unsigned      cluster0_gic_reactivate                   :  1;
     unsigned      cluster1_gic_reactivate                   :  1;
     unsigned      cluster2_gic_reactivate                   :  1;
     unsigned      cluster3_gic_reactivate                   :  1;
     unsigned      cluster4_gic_reactivate                   :  1;
     unsigned      cluster5_gic_reactivate                   :  1;
     unsigned      cluster6_gic_reactivate                   :  1;
     unsigned      cluster7_gic_reactivate                   :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_gic_reactivate_r_xlf_t;

/*! @struct ncp_syscon_gic_reactivate_cnt_r_xlf_t
 *  @brief GIC Reactivate CPUs Counter Register
 *  @details This register contains the number of clocks the system should wait after detecting the rising edge on the
	 pwr_CLKEN line for a CPU cluster before setting all the bits corresponding to the related CPUs in the GIC CPU
	 Active register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_gic_reactivate_cnt_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param gic_reactivate_cnt </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> GIC reactivate wait count. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_gic_reactivate_cnt_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 25;
     unsigned      gic_reactivate_cnt                        :  7;
#else    /* Little Endian */
     unsigned      gic_reactivate_cnt                        :  7;
     unsigned      reserved0                                 : 25;
#endif
} ncp_syscon_gic_reactivate_cnt_r_xlf_t;

/*! @struct ncp_syscon_pwr_CACTIVE_APB_r_xlf_t
 *  @brief CPU Cluster APB Bridge Active Status Register
 *  @details This read-only status register contains the current state of the APB bridge activity bits for each of the CPU clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_CACTIVE_APB_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_cactive_apb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 APB bridge is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_cactive_apb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 APB bridge is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_cactive_apb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 APB bridge is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_cactive_apb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 APB bridge is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_cactive_apb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 APB bridge is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_cactive_apb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 APB bridge is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_cactive_apb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 APB bridge is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_cactive_apb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 APB bridge is active indication. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_CACTIVE_APB_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_cactive_apb                      :  1;
     unsigned      cluster6_cactive_apb                      :  1;
     unsigned      cluster5_cactive_apb                      :  1;
     unsigned      cluster4_cactive_apb                      :  1;
     unsigned      cluster3_cactive_apb                      :  1;
     unsigned      cluster2_cactive_apb                      :  1;
     unsigned      cluster1_cactive_apb                      :  1;
     unsigned      cluster0_cactive_apb                      :  1;
#else    /* Little Endian */
     unsigned      cluster0_cactive_apb                      :  1;
     unsigned      cluster1_cactive_apb                      :  1;
     unsigned      cluster2_cactive_apb                      :  1;
     unsigned      cluster3_cactive_apb                      :  1;
     unsigned      cluster4_cactive_apb                      :  1;
     unsigned      cluster5_cactive_apb                      :  1;
     unsigned      cluster6_cactive_apb                      :  1;
     unsigned      cluster7_cactive_apb                      :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_CACTIVE_APB_r_xlf_t;

/*! @struct ncp_syscon_pwr_CACTIVE_ATB_r_xlf_t
 *  @brief CPU Cluster ATB Bridge Active Status Register
 *  @details This read-only status register contains the current state of the ATB bridge activity bits for each of the CPU clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_CACTIVE_ATB_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_cactive_atb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 ATB bridge is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_cactive_atb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 ATB bridge is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_cactive_atb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 ATB bridge is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_cactive_atb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 ATB bridge is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_cactive_atb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 ATB bridge is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_cactive_atb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 ATB bridge is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_cactive_atb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 ATB bridge is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_cactive_atb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 ATB bridge is active indication. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_CACTIVE_ATB_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_cactive_atb                      :  1;
     unsigned      cluster6_cactive_atb                      :  1;
     unsigned      cluster5_cactive_atb                      :  1;
     unsigned      cluster4_cactive_atb                      :  1;
     unsigned      cluster3_cactive_atb                      :  1;
     unsigned      cluster2_cactive_atb                      :  1;
     unsigned      cluster1_cactive_atb                      :  1;
     unsigned      cluster0_cactive_atb                      :  1;
#else    /* Little Endian */
     unsigned      cluster0_cactive_atb                      :  1;
     unsigned      cluster1_cactive_atb                      :  1;
     unsigned      cluster2_cactive_atb                      :  1;
     unsigned      cluster3_cactive_atb                      :  1;
     unsigned      cluster4_cactive_atb                      :  1;
     unsigned      cluster5_cactive_atb                      :  1;
     unsigned      cluster6_cactive_atb                      :  1;
     unsigned      cluster7_cactive_atb                      :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_CACTIVE_ATB_r_xlf_t;

/*! @struct ncp_syscon_pwr_CACTIVE_CNT_r_xlf_t
 *  @brief CPU Cluster System Counter Bridge Active Status Register
 *  @details This read-only status register contains the current state of the system counter bridge activity bits for each of the CPU clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_CACTIVE_CNT_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_cactive_cnt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 system counter bridge is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_cactive_cnt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 system counter bridge is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_cactive_cnt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 system counter bridge is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_cactive_cnt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 system counter bridge is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_cactive_cnt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 system counter bridge is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_cactive_cnt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 system counter bridge is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_cactive_cnt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 system counter bridge is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_cactive_cnt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 system counter bridge is active indication. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_CACTIVE_CNT_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_cactive_cnt                      :  1;
     unsigned      cluster6_cactive_cnt                      :  1;
     unsigned      cluster5_cactive_cnt                      :  1;
     unsigned      cluster4_cactive_cnt                      :  1;
     unsigned      cluster3_cactive_cnt                      :  1;
     unsigned      cluster2_cactive_cnt                      :  1;
     unsigned      cluster1_cactive_cnt                      :  1;
     unsigned      cluster0_cactive_cnt                      :  1;
#else    /* Little Endian */
     unsigned      cluster0_cactive_cnt                      :  1;
     unsigned      cluster1_cactive_cnt                      :  1;
     unsigned      cluster2_cactive_cnt                      :  1;
     unsigned      cluster3_cactive_cnt                      :  1;
     unsigned      cluster4_cactive_cnt                      :  1;
     unsigned      cluster5_cactive_cnt                      :  1;
     unsigned      cluster6_cactive_cnt                      :  1;
     unsigned      cluster7_cactive_cnt                      :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_CACTIVE_CNT_r_xlf_t;

/*! @struct ncp_syscon_pwr_CACTIVE_TS_r_xlf_t
 *  @brief CPU Cluster Timestamp Bridge Active Status Register
 *  @details This read-only status register contains the current state of the timestamp bridge activity bits for each of the CPU clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_CACTIVE_TS_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_cactive_ts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 timestamp bridge is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_cactive_ts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 timestamp bridge is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_cactive_ts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 timestamp bridge is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_cactive_ts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 timestamp bridge is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_cactive_ts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 timestamp bridge is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_cactive_ts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 timestamp bridge is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_cactive_ts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 timestamp bridge is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_cactive_ts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 timestamp bridge is active indication. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_CACTIVE_TS_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_cactive_ts                       :  1;
     unsigned      cluster6_cactive_ts                       :  1;
     unsigned      cluster5_cactive_ts                       :  1;
     unsigned      cluster4_cactive_ts                       :  1;
     unsigned      cluster3_cactive_ts                       :  1;
     unsigned      cluster2_cactive_ts                       :  1;
     unsigned      cluster1_cactive_ts                       :  1;
     unsigned      cluster0_cactive_ts                       :  1;
#else    /* Little Endian */
     unsigned      cluster0_cactive_ts                       :  1;
     unsigned      cluster1_cactive_ts                       :  1;
     unsigned      cluster2_cactive_ts                       :  1;
     unsigned      cluster3_cactive_ts                       :  1;
     unsigned      cluster4_cactive_ts                       :  1;
     unsigned      cluster5_cactive_ts                       :  1;
     unsigned      cluster6_cactive_ts                       :  1;
     unsigned      cluster7_cactive_ts                       :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_CACTIVE_TS_r_xlf_t;

/*! @struct ncp_syscon_pwr_CACTIVEM_ACP_r_xlf_t
 *  @brief CPU Cluster ACP Bridge Master Interface Active Status Register
 *  @details This read-only status register contains the current state of the ACP bridge master interface activity bits for each
	 of the CPU clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_CACTIVEM_ACP_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_cactivem_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 ACP bridge master interface is active
 *        indication.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_cactivem_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 ACP bridge master interface is active
 *        indication.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_cactivem_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 ACP bridge master interface is active
 *        indication.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_cactivem_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 ACP bridge master interface is active
 *        indication.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_cactivem_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 ACP bridge master interface is active
 *        indication.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_cactivem_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 ACP bridge master interface is active
 *        indication.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_cactivem_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 ACP bridge master interface is active
 *        indication.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_cactivem_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 ACP bridge master interface is active
 *        indication.
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_CACTIVEM_ACP_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_cactivem_acp                     :  1;
     unsigned      cluster6_cactivem_acp                     :  1;
     unsigned      cluster5_cactivem_acp                     :  1;
     unsigned      cluster4_cactivem_acp                     :  1;
     unsigned      cluster3_cactivem_acp                     :  1;
     unsigned      cluster2_cactivem_acp                     :  1;
     unsigned      cluster1_cactivem_acp                     :  1;
     unsigned      cluster0_cactivem_acp                     :  1;
#else    /* Little Endian */
     unsigned      cluster0_cactivem_acp                     :  1;
     unsigned      cluster1_cactivem_acp                     :  1;
     unsigned      cluster2_cactivem_acp                     :  1;
     unsigned      cluster3_cactivem_acp                     :  1;
     unsigned      cluster4_cactivem_acp                     :  1;
     unsigned      cluster5_cactivem_acp                     :  1;
     unsigned      cluster6_cactivem_acp                     :  1;
     unsigned      cluster7_cactivem_acp                     :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_CACTIVEM_ACP_r_xlf_t;

/*! @struct ncp_syscon_pwr_CACTIVEM_ICCT_r_xlf_t
 *  @brief CPU Cluster GIC ICCT Bridge Master Interface Active Status Register
 *  @details This read-only status register contains the current state of the GIC ICCT bridge master interface activity bits
	 for each of the CPU clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_CACTIVEM_ICCT_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_cactivem_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 GIC ICCT master interface is active
 *        indication.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_cactivem_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 GIC ICCT master interface is active
 *        indication.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_cactivem_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 GIC ICCT master interface is active
 *        indication.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_cactivem_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 GIC ICCT master interface is active
 *        indication.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_cactivem_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 GIC ICCT master interface is active
 *        indication.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_cactivem_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 GIC ICCT master interface is active
 *        indication.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_cactivem_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 GIC ICCT master interface is active
 *        indication.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_cactivem_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 GIC ICCT master interface is active
 *        indication.
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_CACTIVEM_ICCT_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_cactivem_icct                    :  1;
     unsigned      cluster6_cactivem_icct                    :  1;
     unsigned      cluster5_cactivem_icct                    :  1;
     unsigned      cluster4_cactivem_icct                    :  1;
     unsigned      cluster3_cactivem_icct                    :  1;
     unsigned      cluster2_cactivem_icct                    :  1;
     unsigned      cluster1_cactivem_icct                    :  1;
     unsigned      cluster0_cactivem_icct                    :  1;
#else    /* Little Endian */
     unsigned      cluster0_cactivem_icct                    :  1;
     unsigned      cluster1_cactivem_icct                    :  1;
     unsigned      cluster2_cactivem_icct                    :  1;
     unsigned      cluster3_cactivem_icct                    :  1;
     unsigned      cluster4_cactivem_icct                    :  1;
     unsigned      cluster5_cactivem_icct                    :  1;
     unsigned      cluster6_cactivem_icct                    :  1;
     unsigned      cluster7_cactivem_icct                    :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_CACTIVEM_ICCT_r_xlf_t;

/*! @struct ncp_syscon_pwr_CACTIVEM_ICDT_r_xlf_t
 *  @brief CPU Cluster GIC ICDT Bridge Master Interface Active Status Register
 *  @details This read-only status register contains the current state of the GIC ICDT bridge master interface activity bits
	 for each of the CPU clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_CACTIVEM_ICDT_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_cactivem_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 GIC ICDT master interface is active
 *        indication.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_cactivem_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 GIC ICDT master interface is active
 *        indication.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_cactivem_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 GIC ICDT master interface is active
 *        indication.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_cactivem_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 GIC ICDT master interface is active
 *        indication.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_cactivem_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 GIC ICDT master interface is active
 *        indication.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_cactivem_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 GIC ICDT master interface is active
 *        indication.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_cactivem_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 GIC ICDT master interface is active
 *        indication.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_cactivem_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 GIC ICDT master interface is active
 *        indication.
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_CACTIVEM_ICDT_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_cactivem_icdt                    :  1;
     unsigned      cluster6_cactivem_icdt                    :  1;
     unsigned      cluster5_cactivem_icdt                    :  1;
     unsigned      cluster4_cactivem_icdt                    :  1;
     unsigned      cluster3_cactivem_icdt                    :  1;
     unsigned      cluster2_cactivem_icdt                    :  1;
     unsigned      cluster1_cactivem_icdt                    :  1;
     unsigned      cluster0_cactivem_icdt                    :  1;
#else    /* Little Endian */
     unsigned      cluster0_cactivem_icdt                    :  1;
     unsigned      cluster1_cactivem_icdt                    :  1;
     unsigned      cluster2_cactivem_icdt                    :  1;
     unsigned      cluster3_cactivem_icdt                    :  1;
     unsigned      cluster4_cactivem_icdt                    :  1;
     unsigned      cluster5_cactivem_icdt                    :  1;
     unsigned      cluster6_cactivem_icdt                    :  1;
     unsigned      cluster7_cactivem_icdt                    :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_CACTIVEM_ICDT_r_xlf_t;

/*! @struct ncp_syscon_pwr_CACTIVES_ACP_r_xlf_t
 *  @brief CPU Cluster ACP Bridge Slave Interface Active Status Register
 *  @details This read-only status register contains the current state of the ACP bridge slave interface activity bits for each
	 of the CPU clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_CACTIVES_ACP_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_cactives_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 ACP bridge slave interface is active
 *        indication.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_cactives_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 ACP bridge slave interface is active
 *        indication.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_cactives_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 ACP bridge slave interface is active
 *        indication.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_cactives_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 ACP bridge slave interface is active
 *        indication.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_cactives_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 ACP bridge slave interface is active
 *        indication.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_cactives_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 ACP bridge slave interface is active
 *        indication.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_cactives_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 ACP bridge slave interface is active
 *        indication.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_cactives_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 ACP bridge slave interface is active
 *        indication.
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_CACTIVES_ACP_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_cactives_acp                     :  1;
     unsigned      cluster6_cactives_acp                     :  1;
     unsigned      cluster5_cactives_acp                     :  1;
     unsigned      cluster4_cactives_acp                     :  1;
     unsigned      cluster3_cactives_acp                     :  1;
     unsigned      cluster2_cactives_acp                     :  1;
     unsigned      cluster1_cactives_acp                     :  1;
     unsigned      cluster0_cactives_acp                     :  1;
#else    /* Little Endian */
     unsigned      cluster0_cactives_acp                     :  1;
     unsigned      cluster1_cactives_acp                     :  1;
     unsigned      cluster2_cactives_acp                     :  1;
     unsigned      cluster3_cactives_acp                     :  1;
     unsigned      cluster4_cactives_acp                     :  1;
     unsigned      cluster5_cactives_acp                     :  1;
     unsigned      cluster6_cactives_acp                     :  1;
     unsigned      cluster7_cactives_acp                     :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_CACTIVES_ACP_r_xlf_t;

/*! @struct ncp_syscon_pwr_CACTIVES_ICCT_r_xlf_t
 *  @brief CPU Cluster GIC ICCT Bridge Slave Interface Active Status Register
 *  @details This read-only status register contains the current state of the GIC ICCT bridge slave interface activity bits
	 for each of the CPU clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_CACTIVES_ICCT_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_cactives_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 GIC ICCT slave interface is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_cactives_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 GIC ICCT slave interface is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_cactives_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 GIC ICCT slave interface is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_cactives_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 GIC ICCT slave interface is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_cactives_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 GIC ICCT slave interface is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_cactives_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 GIC ICCT slave interface is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_cactives_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 GIC ICCT slave interface is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_cactives_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 GIC ICCT slave interface is active indication. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_CACTIVES_ICCT_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_cactives_icct                    :  1;
     unsigned      cluster6_cactives_icct                    :  1;
     unsigned      cluster5_cactives_icct                    :  1;
     unsigned      cluster4_cactives_icct                    :  1;
     unsigned      cluster3_cactives_icct                    :  1;
     unsigned      cluster2_cactives_icct                    :  1;
     unsigned      cluster1_cactives_icct                    :  1;
     unsigned      cluster0_cactives_icct                    :  1;
#else    /* Little Endian */
     unsigned      cluster0_cactives_icct                    :  1;
     unsigned      cluster1_cactives_icct                    :  1;
     unsigned      cluster2_cactives_icct                    :  1;
     unsigned      cluster3_cactives_icct                    :  1;
     unsigned      cluster4_cactives_icct                    :  1;
     unsigned      cluster5_cactives_icct                    :  1;
     unsigned      cluster6_cactives_icct                    :  1;
     unsigned      cluster7_cactives_icct                    :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_CACTIVES_ICCT_r_xlf_t;

/*! @struct ncp_syscon_pwr_CACTIVES_ICDT_r_xlf_t
 *  @brief CPU Cluster GIC ICDT Bridge Slave Interface Active Status Register
 *  @details This read-only status register contains the current state of the GIC ICDT bridge slave interface activity bits
	 for each of the CPU clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_CACTIVES_ICDT_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_cactives_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 GIC ICDT slave interface is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_cactives_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 GIC ICDT slave interface is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_cactives_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 GIC ICDT slave interface is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_cactives_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 GIC ICDT slave interface is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_cactives_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 GIC ICDT slave interface is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_cactives_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 GIC ICDT slave interface is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_cactives_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 GIC ICDT slave interface is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_cactives_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 GIC ICDT slave interface is active indication. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_CACTIVES_ICDT_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_cactives_icdt                    :  1;
     unsigned      cluster6_cactives_icdt                    :  1;
     unsigned      cluster5_cactives_icdt                    :  1;
     unsigned      cluster4_cactives_icdt                    :  1;
     unsigned      cluster3_cactives_icdt                    :  1;
     unsigned      cluster2_cactives_icdt                    :  1;
     unsigned      cluster1_cactives_icdt                    :  1;
     unsigned      cluster0_cactives_icdt                    :  1;
#else    /* Little Endian */
     unsigned      cluster0_cactives_icdt                    :  1;
     unsigned      cluster1_cactives_icdt                    :  1;
     unsigned      cluster2_cactives_icdt                    :  1;
     unsigned      cluster3_cactives_icdt                    :  1;
     unsigned      cluster4_cactives_icdt                    :  1;
     unsigned      cluster5_cactives_icdt                    :  1;
     unsigned      cluster6_cactives_icdt                    :  1;
     unsigned      cluster7_cactives_icdt                    :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_CACTIVES_ICDT_r_xlf_t;

/*! @struct ncp_syscon_pwr_CPUQACTIVE_r_xlf_t
 *  @brief CPU Active Status Register
 *  @details This read-only status register contains the current state of the activity bits for each of the CPUs.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_CPUQACTIVE_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cpu31_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> CPU 31 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu30_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> CPU 30 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu29_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> CPU 29 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu28_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> CPU 28 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu27_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> CPU 27 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu26_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> CPU 26 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu25_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> CPU 25 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu24_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> CPU 24 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu23_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> CPU 23 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu22_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> CPU 22 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu21_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> CPU 21 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu20_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> CPU 20 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu19_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> CPU 19 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu18_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> CPU 18 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu17_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> CPU 17 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu16_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> CPU 16 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu15_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> CPU 15 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu14_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> CPU 14 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu13_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> CPU 13 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu12_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> CPU 12 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu11_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> CPU 11 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu10_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> CPU 10 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu9_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> CPU 9 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu8_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> CPU 8 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu7_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU 7 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu6_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU 6 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu5_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU 5 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu4_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU 4 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu3_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU 3 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu2_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU 2 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu1_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU 1 active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu0_cpuqactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU 0 active indication. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_CPUQACTIVE_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      cpu31_cpuqactive                          :  1;
     unsigned      cpu30_cpuqactive                          :  1;
     unsigned      cpu29_cpuqactive                          :  1;
     unsigned      cpu28_cpuqactive                          :  1;
     unsigned      cpu27_cpuqactive                          :  1;
     unsigned      cpu26_cpuqactive                          :  1;
     unsigned      cpu25_cpuqactive                          :  1;
     unsigned      cpu24_cpuqactive                          :  1;
     unsigned      cpu23_cpuqactive                          :  1;
     unsigned      cpu22_cpuqactive                          :  1;
     unsigned      cpu21_cpuqactive                          :  1;
     unsigned      cpu20_cpuqactive                          :  1;
     unsigned      cpu19_cpuqactive                          :  1;
     unsigned      cpu18_cpuqactive                          :  1;
     unsigned      cpu17_cpuqactive                          :  1;
     unsigned      cpu16_cpuqactive                          :  1;
     unsigned      cpu15_cpuqactive                          :  1;
     unsigned      cpu14_cpuqactive                          :  1;
     unsigned      cpu13_cpuqactive                          :  1;
     unsigned      cpu12_cpuqactive                          :  1;
     unsigned      cpu11_cpuqactive                          :  1;
     unsigned      cpu10_cpuqactive                          :  1;
     unsigned      cpu9_cpuqactive                           :  1;
     unsigned      cpu8_cpuqactive                           :  1;
     unsigned      cpu7_cpuqactive                           :  1;
     unsigned      cpu6_cpuqactive                           :  1;
     unsigned      cpu5_cpuqactive                           :  1;
     unsigned      cpu4_cpuqactive                           :  1;
     unsigned      cpu3_cpuqactive                           :  1;
     unsigned      cpu2_cpuqactive                           :  1;
     unsigned      cpu1_cpuqactive                           :  1;
     unsigned      cpu0_cpuqactive                           :  1;
#else    /* Little Endian */
     unsigned      cpu0_cpuqactive                           :  1;
     unsigned      cpu1_cpuqactive                           :  1;
     unsigned      cpu2_cpuqactive                           :  1;
     unsigned      cpu3_cpuqactive                           :  1;
     unsigned      cpu4_cpuqactive                           :  1;
     unsigned      cpu5_cpuqactive                           :  1;
     unsigned      cpu6_cpuqactive                           :  1;
     unsigned      cpu7_cpuqactive                           :  1;
     unsigned      cpu8_cpuqactive                           :  1;
     unsigned      cpu9_cpuqactive                           :  1;
     unsigned      cpu10_cpuqactive                          :  1;
     unsigned      cpu11_cpuqactive                          :  1;
     unsigned      cpu12_cpuqactive                          :  1;
     unsigned      cpu13_cpuqactive                          :  1;
     unsigned      cpu14_cpuqactive                          :  1;
     unsigned      cpu15_cpuqactive                          :  1;
     unsigned      cpu16_cpuqactive                          :  1;
     unsigned      cpu17_cpuqactive                          :  1;
     unsigned      cpu18_cpuqactive                          :  1;
     unsigned      cpu19_cpuqactive                          :  1;
     unsigned      cpu20_cpuqactive                          :  1;
     unsigned      cpu21_cpuqactive                          :  1;
     unsigned      cpu22_cpuqactive                          :  1;
     unsigned      cpu23_cpuqactive                          :  1;
     unsigned      cpu24_cpuqactive                          :  1;
     unsigned      cpu25_cpuqactive                          :  1;
     unsigned      cpu26_cpuqactive                          :  1;
     unsigned      cpu27_cpuqactive                          :  1;
     unsigned      cpu28_cpuqactive                          :  1;
     unsigned      cpu29_cpuqactive                          :  1;
     unsigned      cpu30_cpuqactive                          :  1;
     unsigned      cpu31_cpuqactive                          :  1;
#endif
} ncp_syscon_pwr_CPUQACTIVE_r_xlf_t;

/*! @struct ncp_syscon_pwr_CPUQACCEPT_r_xlf_t
 *  @brief CPU Clock State Change Request Accepted Status Register
 *  @details This read-only status register contains the current state of the inverted, active-low CPUQACCEPTn response bits
	 for each of the CPUs.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_CPUQACCEPT_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cpu31_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> CPU 31 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu30_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> CPU 30 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu29_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> CPU 29 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu28_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> CPU 28 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu27_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> CPU 27 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu26_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> CPU 26 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu25_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> CPU 25 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu24_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> CPU 24 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu23_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> CPU 23 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu22_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> CPU 22 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu21_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> CPU 21 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu20_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> CPU 20 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu19_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> CPU 19 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu18_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> CPU 18 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu17_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> CPU 17 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu16_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> CPU 16 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu15_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> CPU 15 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu14_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> CPU 14 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu13_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> CPU 13 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu12_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> CPU 12 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu11_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> CPU 11 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu10_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> CPU 10 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu9_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> CPU 9 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu8_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> CPU 8 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu7_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU 7 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu6_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU 6 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu5_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU 5 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu4_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU 4 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu3_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU 3 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu2_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU 2 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu1_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU 1 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu0_cpuqaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU 0 accepted clock state change request. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_CPUQACCEPT_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      cpu31_cpuqaccept                          :  1;
     unsigned      cpu30_cpuqaccept                          :  1;
     unsigned      cpu29_cpuqaccept                          :  1;
     unsigned      cpu28_cpuqaccept                          :  1;
     unsigned      cpu27_cpuqaccept                          :  1;
     unsigned      cpu26_cpuqaccept                          :  1;
     unsigned      cpu25_cpuqaccept                          :  1;
     unsigned      cpu24_cpuqaccept                          :  1;
     unsigned      cpu23_cpuqaccept                          :  1;
     unsigned      cpu22_cpuqaccept                          :  1;
     unsigned      cpu21_cpuqaccept                          :  1;
     unsigned      cpu20_cpuqaccept                          :  1;
     unsigned      cpu19_cpuqaccept                          :  1;
     unsigned      cpu18_cpuqaccept                          :  1;
     unsigned      cpu17_cpuqaccept                          :  1;
     unsigned      cpu16_cpuqaccept                          :  1;
     unsigned      cpu15_cpuqaccept                          :  1;
     unsigned      cpu14_cpuqaccept                          :  1;
     unsigned      cpu13_cpuqaccept                          :  1;
     unsigned      cpu12_cpuqaccept                          :  1;
     unsigned      cpu11_cpuqaccept                          :  1;
     unsigned      cpu10_cpuqaccept                          :  1;
     unsigned      cpu9_cpuqaccept                           :  1;
     unsigned      cpu8_cpuqaccept                           :  1;
     unsigned      cpu7_cpuqaccept                           :  1;
     unsigned      cpu6_cpuqaccept                           :  1;
     unsigned      cpu5_cpuqaccept                           :  1;
     unsigned      cpu4_cpuqaccept                           :  1;
     unsigned      cpu3_cpuqaccept                           :  1;
     unsigned      cpu2_cpuqaccept                           :  1;
     unsigned      cpu1_cpuqaccept                           :  1;
     unsigned      cpu0_cpuqaccept                           :  1;
#else    /* Little Endian */
     unsigned      cpu0_cpuqaccept                           :  1;
     unsigned      cpu1_cpuqaccept                           :  1;
     unsigned      cpu2_cpuqaccept                           :  1;
     unsigned      cpu3_cpuqaccept                           :  1;
     unsigned      cpu4_cpuqaccept                           :  1;
     unsigned      cpu5_cpuqaccept                           :  1;
     unsigned      cpu6_cpuqaccept                           :  1;
     unsigned      cpu7_cpuqaccept                           :  1;
     unsigned      cpu8_cpuqaccept                           :  1;
     unsigned      cpu9_cpuqaccept                           :  1;
     unsigned      cpu10_cpuqaccept                          :  1;
     unsigned      cpu11_cpuqaccept                          :  1;
     unsigned      cpu12_cpuqaccept                          :  1;
     unsigned      cpu13_cpuqaccept                          :  1;
     unsigned      cpu14_cpuqaccept                          :  1;
     unsigned      cpu15_cpuqaccept                          :  1;
     unsigned      cpu16_cpuqaccept                          :  1;
     unsigned      cpu17_cpuqaccept                          :  1;
     unsigned      cpu18_cpuqaccept                          :  1;
     unsigned      cpu19_cpuqaccept                          :  1;
     unsigned      cpu20_cpuqaccept                          :  1;
     unsigned      cpu21_cpuqaccept                          :  1;
     unsigned      cpu22_cpuqaccept                          :  1;
     unsigned      cpu23_cpuqaccept                          :  1;
     unsigned      cpu24_cpuqaccept                          :  1;
     unsigned      cpu25_cpuqaccept                          :  1;
     unsigned      cpu26_cpuqaccept                          :  1;
     unsigned      cpu27_cpuqaccept                          :  1;
     unsigned      cpu28_cpuqaccept                          :  1;
     unsigned      cpu29_cpuqaccept                          :  1;
     unsigned      cpu30_cpuqaccept                          :  1;
     unsigned      cpu31_cpuqaccept                          :  1;
#endif
} ncp_syscon_pwr_CPUQACCEPT_r_xlf_t;

/*! @struct ncp_syscon_pwr_CPUQDENY_r_xlf_t
 *  @brief CPU Clock State Change Request Denied Status Register
 *  @details This read-only status register contains the current state of the CPUQDENY response bits
	 for each of the CPUs.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_CPUQDENY_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cpu31_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> CPU 31 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu30_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> CPU 30 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu29_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> CPU 29 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu28_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> CPU 28 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu27_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> CPU 27 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu26_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> CPU 26 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu25_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> CPU 25 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu24_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> CPU 24 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu23_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> CPU 23 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu22_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> CPU 22 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu21_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> CPU 21 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu20_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> CPU 20 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu19_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> CPU 19 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu18_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> CPU 18 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu17_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> CPU 17 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu16_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> CPU 16 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu15_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> CPU 15 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu14_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> CPU 14 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu13_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> CPU 13 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu12_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> CPU 12 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu11_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> CPU 11 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu10_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> CPU 10 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu9_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> CPU 9 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu8_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> CPU 8 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu7_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU 7 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu6_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU 6 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu5_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU 5 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu4_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU 4 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu3_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU 3 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu2_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU 2 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu1_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU 1 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu0_cpuqdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU 0 denied clock state change request. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_CPUQDENY_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      cpu31_cpuqdeny                            :  1;
     unsigned      cpu30_cpuqdeny                            :  1;
     unsigned      cpu29_cpuqdeny                            :  1;
     unsigned      cpu28_cpuqdeny                            :  1;
     unsigned      cpu27_cpuqdeny                            :  1;
     unsigned      cpu26_cpuqdeny                            :  1;
     unsigned      cpu25_cpuqdeny                            :  1;
     unsigned      cpu24_cpuqdeny                            :  1;
     unsigned      cpu23_cpuqdeny                            :  1;
     unsigned      cpu22_cpuqdeny                            :  1;
     unsigned      cpu21_cpuqdeny                            :  1;
     unsigned      cpu20_cpuqdeny                            :  1;
     unsigned      cpu19_cpuqdeny                            :  1;
     unsigned      cpu18_cpuqdeny                            :  1;
     unsigned      cpu17_cpuqdeny                            :  1;
     unsigned      cpu16_cpuqdeny                            :  1;
     unsigned      cpu15_cpuqdeny                            :  1;
     unsigned      cpu14_cpuqdeny                            :  1;
     unsigned      cpu13_cpuqdeny                            :  1;
     unsigned      cpu12_cpuqdeny                            :  1;
     unsigned      cpu11_cpuqdeny                            :  1;
     unsigned      cpu10_cpuqdeny                            :  1;
     unsigned      cpu9_cpuqdeny                             :  1;
     unsigned      cpu8_cpuqdeny                             :  1;
     unsigned      cpu7_cpuqdeny                             :  1;
     unsigned      cpu6_cpuqdeny                             :  1;
     unsigned      cpu5_cpuqdeny                             :  1;
     unsigned      cpu4_cpuqdeny                             :  1;
     unsigned      cpu3_cpuqdeny                             :  1;
     unsigned      cpu2_cpuqdeny                             :  1;
     unsigned      cpu1_cpuqdeny                             :  1;
     unsigned      cpu0_cpuqdeny                             :  1;
#else    /* Little Endian */
     unsigned      cpu0_cpuqdeny                             :  1;
     unsigned      cpu1_cpuqdeny                             :  1;
     unsigned      cpu2_cpuqdeny                             :  1;
     unsigned      cpu3_cpuqdeny                             :  1;
     unsigned      cpu4_cpuqdeny                             :  1;
     unsigned      cpu5_cpuqdeny                             :  1;
     unsigned      cpu6_cpuqdeny                             :  1;
     unsigned      cpu7_cpuqdeny                             :  1;
     unsigned      cpu8_cpuqdeny                             :  1;
     unsigned      cpu9_cpuqdeny                             :  1;
     unsigned      cpu10_cpuqdeny                            :  1;
     unsigned      cpu11_cpuqdeny                            :  1;
     unsigned      cpu12_cpuqdeny                            :  1;
     unsigned      cpu13_cpuqdeny                            :  1;
     unsigned      cpu14_cpuqdeny                            :  1;
     unsigned      cpu15_cpuqdeny                            :  1;
     unsigned      cpu16_cpuqdeny                            :  1;
     unsigned      cpu17_cpuqdeny                            :  1;
     unsigned      cpu18_cpuqdeny                            :  1;
     unsigned      cpu19_cpuqdeny                            :  1;
     unsigned      cpu20_cpuqdeny                            :  1;
     unsigned      cpu21_cpuqdeny                            :  1;
     unsigned      cpu22_cpuqdeny                            :  1;
     unsigned      cpu23_cpuqdeny                            :  1;
     unsigned      cpu24_cpuqdeny                            :  1;
     unsigned      cpu25_cpuqdeny                            :  1;
     unsigned      cpu26_cpuqdeny                            :  1;
     unsigned      cpu27_cpuqdeny                            :  1;
     unsigned      cpu28_cpuqdeny                            :  1;
     unsigned      cpu29_cpuqdeny                            :  1;
     unsigned      cpu30_cpuqdeny                            :  1;
     unsigned      cpu31_cpuqdeny                            :  1;
#endif
} ncp_syscon_pwr_CPUQDENY_r_xlf_t;

/*! @struct ncp_syscon_pwr_CSYSACK_APB_r_xlf_t
 *  @brief CPU Cluster APB Bridge Powerup Acknowledge Status Register
 *  @details This read-only status register contains the current state of the acknowledge bits for an APB bridge powerup
	 request for each of the CPU clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_CSYSACK_APB_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_csysack_apb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 APB bridge powerup acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_csysack_apb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 APB bridge powerup acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_csysack_apb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 APB bridge powerup acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_csysack_apb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 APB bridge powerup acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_csysack_apb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 APB bridge powerup acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_csysack_apb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 APB bridge powerup acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_csysack_apb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 APB bridge powerup acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_csysack_apb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 APB bridge powerup acknowledge. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_CSYSACK_APB_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_csysack_apb                      :  1;
     unsigned      cluster6_csysack_apb                      :  1;
     unsigned      cluster5_csysack_apb                      :  1;
     unsigned      cluster4_csysack_apb                      :  1;
     unsigned      cluster3_csysack_apb                      :  1;
     unsigned      cluster2_csysack_apb                      :  1;
     unsigned      cluster1_csysack_apb                      :  1;
     unsigned      cluster0_csysack_apb                      :  1;
#else    /* Little Endian */
     unsigned      cluster0_csysack_apb                      :  1;
     unsigned      cluster1_csysack_apb                      :  1;
     unsigned      cluster2_csysack_apb                      :  1;
     unsigned      cluster3_csysack_apb                      :  1;
     unsigned      cluster4_csysack_apb                      :  1;
     unsigned      cluster5_csysack_apb                      :  1;
     unsigned      cluster6_csysack_apb                      :  1;
     unsigned      cluster7_csysack_apb                      :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_CSYSACK_APB_r_xlf_t;

/*! @struct ncp_syscon_pwr_CSYSACK_ATB_r_xlf_t
 *  @brief CPU Cluster ATB Bridge Powerup Acknowledge Status Register
 *  @details This read-only status register contains the current state of the acknowledge bits for an ATB bridge powerup
	 request for each of the CPU clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_CSYSACK_ATB_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_csysack_atb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 ATB bridge powerup acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_csysack_atb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 ATB bridge powerup acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_csysack_atb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 ATB bridge powerup acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_csysack_atb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 ATB bridge powerup acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_csysack_atb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 ATB bridge powerup acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_csysack_atb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 ATB bridge powerup acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_csysack_atb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 ATB bridge powerup acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_csysack_atb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 ATB bridge powerup acknowledge. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_CSYSACK_ATB_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_csysack_atb                      :  1;
     unsigned      cluster6_csysack_atb                      :  1;
     unsigned      cluster5_csysack_atb                      :  1;
     unsigned      cluster4_csysack_atb                      :  1;
     unsigned      cluster3_csysack_atb                      :  1;
     unsigned      cluster2_csysack_atb                      :  1;
     unsigned      cluster1_csysack_atb                      :  1;
     unsigned      cluster0_csysack_atb                      :  1;
#else    /* Little Endian */
     unsigned      cluster0_csysack_atb                      :  1;
     unsigned      cluster1_csysack_atb                      :  1;
     unsigned      cluster2_csysack_atb                      :  1;
     unsigned      cluster3_csysack_atb                      :  1;
     unsigned      cluster4_csysack_atb                      :  1;
     unsigned      cluster5_csysack_atb                      :  1;
     unsigned      cluster6_csysack_atb                      :  1;
     unsigned      cluster7_csysack_atb                      :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_CSYSACK_ATB_r_xlf_t;

/*! @struct ncp_syscon_pwr_CSYSACK_CNT_r_xlf_t
 *  @brief CPU Cluster System Counter Bridge Powerup Acknowledge Status Register
 *  @details This read-only status register contains the current state of the acknowledge bits for a system counter bridge powerup
	 request for each of the CPU clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_CSYSACK_CNT_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_csysack_cnt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 system counter bridge powerup acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_csysack_cnt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 system counter bridge powerup acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_csysack_cnt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 system counter bridge powerup acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_csysack_cnt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 system counter bridge powerup acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_csysack_cnt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 system counter bridge powerup acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_csysack_cnt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 system counter bridge powerup acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_csysack_cnt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 system counter bridge powerup acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_csysack_cnt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 system counter bridge powerup acknowledge. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_CSYSACK_CNT_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_csysack_cnt                      :  1;
     unsigned      cluster6_csysack_cnt                      :  1;
     unsigned      cluster5_csysack_cnt                      :  1;
     unsigned      cluster4_csysack_cnt                      :  1;
     unsigned      cluster3_csysack_cnt                      :  1;
     unsigned      cluster2_csysack_cnt                      :  1;
     unsigned      cluster1_csysack_cnt                      :  1;
     unsigned      cluster0_csysack_cnt                      :  1;
#else    /* Little Endian */
     unsigned      cluster0_csysack_cnt                      :  1;
     unsigned      cluster1_csysack_cnt                      :  1;
     unsigned      cluster2_csysack_cnt                      :  1;
     unsigned      cluster3_csysack_cnt                      :  1;
     unsigned      cluster4_csysack_cnt                      :  1;
     unsigned      cluster5_csysack_cnt                      :  1;
     unsigned      cluster6_csysack_cnt                      :  1;
     unsigned      cluster7_csysack_cnt                      :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_CSYSACK_CNT_r_xlf_t;

/*! @struct ncp_syscon_pwr_CSYSACK_TS_r_xlf_t
 *  @brief CPU Cluster Timestamp Bridge Powerup Acknowledge Status Register
 *  @details This read-only status register contains the current state of the acknowledge bits for a timestamp bridge powerup
	 request for each of the CPU clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_CSYSACK_TS_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_csysack_ts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 timestamp bridge powerup acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_csysack_ts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 timestamp bridge powerup acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_csysack_ts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 timestamp bridge powerup acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_csysack_ts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 timestamp bridge powerup acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_csysack_ts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 timestamp bridge powerup acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_csysack_ts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 timestamp bridge powerup acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_csysack_ts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 timestamp bridge powerup acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_csysack_ts </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 timestamp bridge powerup acknowledge. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_CSYSACK_TS_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_csysack_ts                       :  1;
     unsigned      cluster6_csysack_ts                       :  1;
     unsigned      cluster5_csysack_ts                       :  1;
     unsigned      cluster4_csysack_ts                       :  1;
     unsigned      cluster3_csysack_ts                       :  1;
     unsigned      cluster2_csysack_ts                       :  1;
     unsigned      cluster1_csysack_ts                       :  1;
     unsigned      cluster0_csysack_ts                       :  1;
#else    /* Little Endian */
     unsigned      cluster0_csysack_ts                       :  1;
     unsigned      cluster1_csysack_ts                       :  1;
     unsigned      cluster2_csysack_ts                       :  1;
     unsigned      cluster3_csysack_ts                       :  1;
     unsigned      cluster4_csysack_ts                       :  1;
     unsigned      cluster5_csysack_ts                       :  1;
     unsigned      cluster6_csysack_ts                       :  1;
     unsigned      cluster7_csysack_ts                       :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_CSYSACK_TS_r_xlf_t;

/*! @struct ncp_syscon_pwr_L2FLUSHDONE_r_xlf_t
 *  @brief CPU Cluster L2 Flush Done Status Register
 *  @details This read-only status register contains the current state of the flush complete bits for for each of the CPU cluster L2s.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_L2FLUSHDONE_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_l2flushdone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 L2 flush complete. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_l2flushdone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 L2 flush complete. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_l2flushdone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 L2 flush complete. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_l2flushdone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 L2 flush complete. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_l2flushdone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 L2 flush complete. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_l2flushdone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 L2 flush complete. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_l2flushdone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 L2 flush complete. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_l2flushdone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 L2 flush complete. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_L2FLUSHDONE_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_l2flushdone                      :  1;
     unsigned      cluster6_l2flushdone                      :  1;
     unsigned      cluster5_l2flushdone                      :  1;
     unsigned      cluster4_l2flushdone                      :  1;
     unsigned      cluster3_l2flushdone                      :  1;
     unsigned      cluster2_l2flushdone                      :  1;
     unsigned      cluster1_l2flushdone                      :  1;
     unsigned      cluster0_l2flushdone                      :  1;
#else    /* Little Endian */
     unsigned      cluster0_l2flushdone                      :  1;
     unsigned      cluster1_l2flushdone                      :  1;
     unsigned      cluster2_l2flushdone                      :  1;
     unsigned      cluster3_l2flushdone                      :  1;
     unsigned      cluster4_l2flushdone                      :  1;
     unsigned      cluster5_l2flushdone                      :  1;
     unsigned      cluster6_l2flushdone                      :  1;
     unsigned      cluster7_l2flushdone                      :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_L2FLUSHDONE_r_xlf_t;

/*! @struct ncp_syscon_pwr_L2QACTIVE_r_xlf_t
 *  @brief CPU Cluster L2 Active Status Register
 *  @details This read-only status register contains the current state of the L2 activity bits for each of the CPU clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_L2QACTIVE_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_l2qactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 L2 is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_l2qactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 L2 is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_l2qactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 L2 is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_l2qactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 L2 is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_l2qactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 L2 is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_l2qactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 L2 is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_l2qactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 L2 is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_l2qactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 L2 is active indication. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_L2QACTIVE_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_l2qactive                        :  1;
     unsigned      cluster6_l2qactive                        :  1;
     unsigned      cluster5_l2qactive                        :  1;
     unsigned      cluster4_l2qactive                        :  1;
     unsigned      cluster3_l2qactive                        :  1;
     unsigned      cluster2_l2qactive                        :  1;
     unsigned      cluster1_l2qactive                        :  1;
     unsigned      cluster0_l2qactive                        :  1;
#else    /* Little Endian */
     unsigned      cluster0_l2qactive                        :  1;
     unsigned      cluster1_l2qactive                        :  1;
     unsigned      cluster2_l2qactive                        :  1;
     unsigned      cluster3_l2qactive                        :  1;
     unsigned      cluster4_l2qactive                        :  1;
     unsigned      cluster5_l2qactive                        :  1;
     unsigned      cluster6_l2qactive                        :  1;
     unsigned      cluster7_l2qactive                        :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_L2QACTIVE_r_xlf_t;

/*! @struct ncp_syscon_pwr_L2QACCEPT_r_xlf_t
 *  @brief CPU Cluster Clock State Change Request Accepted Status Register
 *  @details This read-only status register contains the current state of the inverted, active-low L2QACCEPTn response bits
	 for each of the CPU clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_L2QACCEPT_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_l2qaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU cluster 7 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_l2qaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU cluster 6 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_l2qaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU cluster 5 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_l2qaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU cluster 4 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_l2qaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU cluster 3 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_l2qaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU cluster 2 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_l2qaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU cluster 1 accepted clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_l2qaccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU cluster 0 accepted clock state change request. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_L2QACCEPT_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_l2qaccept                        :  1;
     unsigned      cluster6_l2qaccept                        :  1;
     unsigned      cluster5_l2qaccept                        :  1;
     unsigned      cluster4_l2qaccept                        :  1;
     unsigned      cluster3_l2qaccept                        :  1;
     unsigned      cluster2_l2qaccept                        :  1;
     unsigned      cluster1_l2qaccept                        :  1;
     unsigned      cluster0_l2qaccept                        :  1;
#else    /* Little Endian */
     unsigned      cluster0_l2qaccept                        :  1;
     unsigned      cluster1_l2qaccept                        :  1;
     unsigned      cluster2_l2qaccept                        :  1;
     unsigned      cluster3_l2qaccept                        :  1;
     unsigned      cluster4_l2qaccept                        :  1;
     unsigned      cluster5_l2qaccept                        :  1;
     unsigned      cluster6_l2qaccept                        :  1;
     unsigned      cluster7_l2qaccept                        :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_L2QACCEPT_r_xlf_t;

/*! @struct ncp_syscon_pwr_L2QDENY_r_xlf_t
 *  @brief CPU Cluster Clock State Change Request Denied Status Register
 *  @details This read-only status register contains the current state of the L2QDENY response bits
	 for each of the CPU clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_L2QDENY_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_l2qdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU cluster 7 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_l2qdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU cluster 6 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_l2qdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU cluster 5 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_l2qdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU cluster 4 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_l2qdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU cluster 3 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_l2qdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU cluster 2 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_l2qdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU cluster 1 denied clock state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_l2qdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU cluster 0 denied clock state change request. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_L2QDENY_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_l2qdeny                          :  1;
     unsigned      cluster6_l2qdeny                          :  1;
     unsigned      cluster5_l2qdeny                          :  1;
     unsigned      cluster4_l2qdeny                          :  1;
     unsigned      cluster3_l2qdeny                          :  1;
     unsigned      cluster2_l2qdeny                          :  1;
     unsigned      cluster1_l2qdeny                          :  1;
     unsigned      cluster0_l2qdeny                          :  1;
#else    /* Little Endian */
     unsigned      cluster0_l2qdeny                          :  1;
     unsigned      cluster1_l2qdeny                          :  1;
     unsigned      cluster2_l2qdeny                          :  1;
     unsigned      cluster3_l2qdeny                          :  1;
     unsigned      cluster4_l2qdeny                          :  1;
     unsigned      cluster5_l2qdeny                          :  1;
     unsigned      cluster6_l2qdeny                          :  1;
     unsigned      cluster7_l2qdeny                          :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_L2QDENY_r_xlf_t;

/*! @struct ncp_syscon_pwr_PACTIVE_r_xlf_t
 *  @brief CPU Cluster Power Active Status Register
 *  @details This read-only status register contains the current state of the power activity bits for each of the CPU clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_PACTIVE_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_pactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_pactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_pactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_pactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_pactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_pactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_pactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_pactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 is active indication. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_PACTIVE_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_pactive                          :  1;
     unsigned      cluster6_pactive                          :  1;
     unsigned      cluster5_pactive                          :  1;
     unsigned      cluster4_pactive                          :  1;
     unsigned      cluster3_pactive                          :  1;
     unsigned      cluster2_pactive                          :  1;
     unsigned      cluster1_pactive                          :  1;
     unsigned      cluster0_pactive                          :  1;
#else    /* Little Endian */
     unsigned      cluster0_pactive                          :  1;
     unsigned      cluster1_pactive                          :  1;
     unsigned      cluster2_pactive                          :  1;
     unsigned      cluster3_pactive                          :  1;
     unsigned      cluster4_pactive                          :  1;
     unsigned      cluster5_pactive                          :  1;
     unsigned      cluster6_pactive                          :  1;
     unsigned      cluster7_pactive                          :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_PACTIVE_r_xlf_t;

/*! @struct ncp_syscon_pwr_PACCEPT_r_xlf_t
 *  @brief CPU Cluster Power State Change Request Accepted Status Register
 *  @details This read-only status register contains the current state of the PACCEPT response bits
	 for each of the CPU clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_PACCEPT_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_paccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU cluster 7 accepted power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_paccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU cluster 6 accepted power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_paccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU cluster 5 accepted power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_paccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU cluster 4 accepted power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_paccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU cluster 3 accepted power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_paccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU cluster 2 accepted power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_paccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU cluster 1 accepted power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_paccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU cluster 0 accepted power state change request. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_PACCEPT_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_paccept                          :  1;
     unsigned      cluster6_paccept                          :  1;
     unsigned      cluster5_paccept                          :  1;
     unsigned      cluster4_paccept                          :  1;
     unsigned      cluster3_paccept                          :  1;
     unsigned      cluster2_paccept                          :  1;
     unsigned      cluster1_paccept                          :  1;
     unsigned      cluster0_paccept                          :  1;
#else    /* Little Endian */
     unsigned      cluster0_paccept                          :  1;
     unsigned      cluster1_paccept                          :  1;
     unsigned      cluster2_paccept                          :  1;
     unsigned      cluster3_paccept                          :  1;
     unsigned      cluster4_paccept                          :  1;
     unsigned      cluster5_paccept                          :  1;
     unsigned      cluster6_paccept                          :  1;
     unsigned      cluster7_paccept                          :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_PACCEPT_r_xlf_t;

/*! @struct ncp_syscon_pwr_PDENY_r_xlf_t
 *  @brief CPU Cluster Power State Change Request Denied Status Register
 *  @details This read-only status register contains the current state of the PDENY response bits
	 for each of the CPU clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_PDENY_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_pdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU cluster 7 denied power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_pdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU cluster 6 denied power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_pdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU cluster 5 denied power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_pdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU cluster 4 denied power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_pdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU cluster 3 denied power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_pdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU cluster 2 denied power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_pdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU cluster 1 denied power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_pdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU cluster 0 denied power state change request. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_PDENY_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_pdeny                            :  1;
     unsigned      cluster6_pdeny                            :  1;
     unsigned      cluster5_pdeny                            :  1;
     unsigned      cluster4_pdeny                            :  1;
     unsigned      cluster3_pdeny                            :  1;
     unsigned      cluster2_pdeny                            :  1;
     unsigned      cluster1_pdeny                            :  1;
     unsigned      cluster0_pdeny                            :  1;
#else    /* Little Endian */
     unsigned      cluster0_pdeny                            :  1;
     unsigned      cluster1_pdeny                            :  1;
     unsigned      cluster2_pdeny                            :  1;
     unsigned      cluster3_pdeny                            :  1;
     unsigned      cluster4_pdeny                            :  1;
     unsigned      cluster5_pdeny                            :  1;
     unsigned      cluster6_pdeny                            :  1;
     unsigned      cluster7_pdeny                            :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_PDENY_r_xlf_t;

/*! @struct ncp_syscon_pwr_PWRDNACK_ACP_r_xlf_t
 *  @brief CPU Cluster ACP Powerdown Acknowledge Register
 *  @details This read-only status register contains the current state of the ACP logic powerdown acknowledge bits
	 for each of the CPU clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_PWRDNACK_ACP_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_pwrdnack_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 ACP powerdown acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_pwrdnack_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 ACP powerdown acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_pwrdnack_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 ACP powerdown acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_pwrdnack_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 ACP powerdown acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_pwrdnack_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 ACP powerdown acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_pwrdnack_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 ACP powerdown acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_pwrdnack_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 ACP powerdown acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_pwrdnack_acp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 ACP powerdown acknowledge. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_PWRDNACK_ACP_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_pwrdnack_acp                     :  1;
     unsigned      cluster6_pwrdnack_acp                     :  1;
     unsigned      cluster5_pwrdnack_acp                     :  1;
     unsigned      cluster4_pwrdnack_acp                     :  1;
     unsigned      cluster3_pwrdnack_acp                     :  1;
     unsigned      cluster2_pwrdnack_acp                     :  1;
     unsigned      cluster1_pwrdnack_acp                     :  1;
     unsigned      cluster0_pwrdnack_acp                     :  1;
#else    /* Little Endian */
     unsigned      cluster0_pwrdnack_acp                     :  1;
     unsigned      cluster1_pwrdnack_acp                     :  1;
     unsigned      cluster2_pwrdnack_acp                     :  1;
     unsigned      cluster3_pwrdnack_acp                     :  1;
     unsigned      cluster4_pwrdnack_acp                     :  1;
     unsigned      cluster5_pwrdnack_acp                     :  1;
     unsigned      cluster6_pwrdnack_acp                     :  1;
     unsigned      cluster7_pwrdnack_acp                     :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_PWRDNACK_ACP_r_xlf_t;

/*! @struct ncp_syscon_pwr_PWRDNACK_ICCT_r_xlf_t
 *  @brief CPU Cluster ICCT Powerdown Acknowledge Register
 *  @details This read-only status register contains the current state of the GIC ICCT logic powerdown acknowledge bits
	 for each of the CPU clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_PWRDNACK_ICCT_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_pwrdnack_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 GIC ICCT powerdown acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_pwrdnack_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 GIC ICCT powerdown acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_pwrdnack_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 GIC ICCT powerdown acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_pwrdnack_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 GIC ICCT powerdown acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_pwrdnack_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 GIC ICCT powerdown acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_pwrdnack_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 GIC ICCT powerdown acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_pwrdnack_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 GIC ICCT powerdown acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_pwrdnack_icct </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 GIC ICCT powerdown acknowledge. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_PWRDNACK_ICCT_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_pwrdnack_icct                    :  1;
     unsigned      cluster6_pwrdnack_icct                    :  1;
     unsigned      cluster5_pwrdnack_icct                    :  1;
     unsigned      cluster4_pwrdnack_icct                    :  1;
     unsigned      cluster3_pwrdnack_icct                    :  1;
     unsigned      cluster2_pwrdnack_icct                    :  1;
     unsigned      cluster1_pwrdnack_icct                    :  1;
     unsigned      cluster0_pwrdnack_icct                    :  1;
#else    /* Little Endian */
     unsigned      cluster0_pwrdnack_icct                    :  1;
     unsigned      cluster1_pwrdnack_icct                    :  1;
     unsigned      cluster2_pwrdnack_icct                    :  1;
     unsigned      cluster3_pwrdnack_icct                    :  1;
     unsigned      cluster4_pwrdnack_icct                    :  1;
     unsigned      cluster5_pwrdnack_icct                    :  1;
     unsigned      cluster6_pwrdnack_icct                    :  1;
     unsigned      cluster7_pwrdnack_icct                    :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_PWRDNACK_ICCT_r_xlf_t;

/*! @struct ncp_syscon_pwr_PWRDNACK_ICDT_r_xlf_t
 *  @brief CPU Cluster ICDT Powerdown Acknowledge Register
 *  @details This read-only status register contains the current state of the GIC ICDT logic powerdown acknowledge bits
	 for each of the CPU clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_PWRDNACK_ICDT_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_pwrdnack_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 GIC ICDT powerdown acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_pwrdnack_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 GIC ICDT powerdown acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_pwrdnack_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 GIC ICDT powerdown acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_pwrdnack_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 GIC ICDT powerdown acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_pwrdnack_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 GIC ICDT powerdown acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_pwrdnack_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 GIC ICDT powerdown acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_pwrdnack_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 GIC ICDT powerdown acknowledge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_pwrdnack_icdt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 GIC ICDT powerdown acknowledge. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_PWRDNACK_ICDT_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_pwrdnack_icdt                    :  1;
     unsigned      cluster6_pwrdnack_icdt                    :  1;
     unsigned      cluster5_pwrdnack_icdt                    :  1;
     unsigned      cluster4_pwrdnack_icdt                    :  1;
     unsigned      cluster3_pwrdnack_icdt                    :  1;
     unsigned      cluster2_pwrdnack_icdt                    :  1;
     unsigned      cluster1_pwrdnack_icdt                    :  1;
     unsigned      cluster0_pwrdnack_icdt                    :  1;
#else    /* Little Endian */
     unsigned      cluster0_pwrdnack_icdt                    :  1;
     unsigned      cluster1_pwrdnack_icdt                    :  1;
     unsigned      cluster2_pwrdnack_icdt                    :  1;
     unsigned      cluster3_pwrdnack_icdt                    :  1;
     unsigned      cluster4_pwrdnack_icdt                    :  1;
     unsigned      cluster5_pwrdnack_icdt                    :  1;
     unsigned      cluster6_pwrdnack_icdt                    :  1;
     unsigned      cluster7_pwrdnack_icdt                    :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_PWRDNACK_ICDT_r_xlf_t;

/*! @struct ncp_syscon_pwr_SMPEN_r_xlf_t
 *  @brief CPU SMPEN Register
 *  @details This read-only status register contains the current state of the SMPEN bits for each of the CPUs.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_SMPEN_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cpu31_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> CPU 31 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu30_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> CPU 30 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu29_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> CPU 29 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu28_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> CPU 28 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu27_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> CPU 27 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu26_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> CPU 26 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu25_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> CPU 25 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu24_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> CPU 24 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu23_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> CPU 23 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu22_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> CPU 22 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu21_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> CPU 21 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu20_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> CPU 20 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu19_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> CPU 19 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu18_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> CPU 18 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu17_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> CPU 17 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu16_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> CPU 16 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu15_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> CPU 15 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu14_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> CPU 14 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu13_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> CPU 13 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu12_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> CPU 12 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu11_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> CPU 11 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu10_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> CPU 10 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu9_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> CPU 9 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu8_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> CPU 8 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu7_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU 7 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu6_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU 6 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu5_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU 5 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu4_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU 4 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu3_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU 3 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu2_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU 2 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu1_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU 1 SMPEN. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu0_smpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU 0 SMPEN. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_SMPEN_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      cpu31_smpen                               :  1;
     unsigned      cpu30_smpen                               :  1;
     unsigned      cpu29_smpen                               :  1;
     unsigned      cpu28_smpen                               :  1;
     unsigned      cpu27_smpen                               :  1;
     unsigned      cpu26_smpen                               :  1;
     unsigned      cpu25_smpen                               :  1;
     unsigned      cpu24_smpen                               :  1;
     unsigned      cpu23_smpen                               :  1;
     unsigned      cpu22_smpen                               :  1;
     unsigned      cpu21_smpen                               :  1;
     unsigned      cpu20_smpen                               :  1;
     unsigned      cpu19_smpen                               :  1;
     unsigned      cpu18_smpen                               :  1;
     unsigned      cpu17_smpen                               :  1;
     unsigned      cpu16_smpen                               :  1;
     unsigned      cpu15_smpen                               :  1;
     unsigned      cpu14_smpen                               :  1;
     unsigned      cpu13_smpen                               :  1;
     unsigned      cpu12_smpen                               :  1;
     unsigned      cpu11_smpen                               :  1;
     unsigned      cpu10_smpen                               :  1;
     unsigned      cpu9_smpen                                :  1;
     unsigned      cpu8_smpen                                :  1;
     unsigned      cpu7_smpen                                :  1;
     unsigned      cpu6_smpen                                :  1;
     unsigned      cpu5_smpen                                :  1;
     unsigned      cpu4_smpen                                :  1;
     unsigned      cpu3_smpen                                :  1;
     unsigned      cpu2_smpen                                :  1;
     unsigned      cpu1_smpen                                :  1;
     unsigned      cpu0_smpen                                :  1;
#else    /* Little Endian */
     unsigned      cpu0_smpen                                :  1;
     unsigned      cpu1_smpen                                :  1;
     unsigned      cpu2_smpen                                :  1;
     unsigned      cpu3_smpen                                :  1;
     unsigned      cpu4_smpen                                :  1;
     unsigned      cpu5_smpen                                :  1;
     unsigned      cpu6_smpen                                :  1;
     unsigned      cpu7_smpen                                :  1;
     unsigned      cpu8_smpen                                :  1;
     unsigned      cpu9_smpen                                :  1;
     unsigned      cpu10_smpen                               :  1;
     unsigned      cpu11_smpen                               :  1;
     unsigned      cpu12_smpen                               :  1;
     unsigned      cpu13_smpen                               :  1;
     unsigned      cpu14_smpen                               :  1;
     unsigned      cpu15_smpen                               :  1;
     unsigned      cpu16_smpen                               :  1;
     unsigned      cpu17_smpen                               :  1;
     unsigned      cpu18_smpen                               :  1;
     unsigned      cpu19_smpen                               :  1;
     unsigned      cpu20_smpen                               :  1;
     unsigned      cpu21_smpen                               :  1;
     unsigned      cpu22_smpen                               :  1;
     unsigned      cpu23_smpen                               :  1;
     unsigned      cpu24_smpen                               :  1;
     unsigned      cpu25_smpen                               :  1;
     unsigned      cpu26_smpen                               :  1;
     unsigned      cpu27_smpen                               :  1;
     unsigned      cpu28_smpen                               :  1;
     unsigned      cpu29_smpen                               :  1;
     unsigned      cpu30_smpen                               :  1;
     unsigned      cpu31_smpen                               :  1;
#endif
} ncp_syscon_pwr_SMPEN_r_xlf_t;

/*! @struct ncp_syscon_pwr_STANDBYWFE_r_xlf_t
 *  @brief CPU Standby Wait For Event Status Register
 *  @details This read-only status register contains the current state of the Wait-For-Event indication for each of the CPUs
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_STANDBYWFE_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cpu31_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> CPU 31 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu30_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> CPU 30 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu29_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> CPU 29 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu28_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> CPU 28 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu27_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> CPU 27 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu26_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> CPU 26 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu25_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> CPU 25 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu24_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> CPU 24 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu23_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> CPU 23 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu22_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> CPU 22 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu21_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> CPU 21 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu20_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> CPU 20 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu19_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> CPU 19 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu18_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> CPU 18 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu17_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> CPU 17 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu16_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> CPU 16 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu15_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> CPU 15 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu14_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> CPU 14 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu13_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> CPU 13 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu12_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> CPU 12 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu11_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> CPU 11 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu10_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> CPU 10 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu9_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> CPU 9 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu8_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> CPU 8 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu7_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU 7 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu6_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU 6 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu5_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU 5 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu4_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU 4 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu3_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU 3 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu2_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU 2 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu1_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU 1 waiting for event. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu0_standbywfe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU 0 waiting for event. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_STANDBYWFE_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      cpu31_standbywfe                          :  1;
     unsigned      cpu30_standbywfe                          :  1;
     unsigned      cpu29_standbywfe                          :  1;
     unsigned      cpu28_standbywfe                          :  1;
     unsigned      cpu27_standbywfe                          :  1;
     unsigned      cpu26_standbywfe                          :  1;
     unsigned      cpu25_standbywfe                          :  1;
     unsigned      cpu24_standbywfe                          :  1;
     unsigned      cpu23_standbywfe                          :  1;
     unsigned      cpu22_standbywfe                          :  1;
     unsigned      cpu21_standbywfe                          :  1;
     unsigned      cpu20_standbywfe                          :  1;
     unsigned      cpu19_standbywfe                          :  1;
     unsigned      cpu18_standbywfe                          :  1;
     unsigned      cpu17_standbywfe                          :  1;
     unsigned      cpu16_standbywfe                          :  1;
     unsigned      cpu15_standbywfe                          :  1;
     unsigned      cpu14_standbywfe                          :  1;
     unsigned      cpu13_standbywfe                          :  1;
     unsigned      cpu12_standbywfe                          :  1;
     unsigned      cpu11_standbywfe                          :  1;
     unsigned      cpu10_standbywfe                          :  1;
     unsigned      cpu9_standbywfe                           :  1;
     unsigned      cpu8_standbywfe                           :  1;
     unsigned      cpu7_standbywfe                           :  1;
     unsigned      cpu6_standbywfe                           :  1;
     unsigned      cpu5_standbywfe                           :  1;
     unsigned      cpu4_standbywfe                           :  1;
     unsigned      cpu3_standbywfe                           :  1;
     unsigned      cpu2_standbywfe                           :  1;
     unsigned      cpu1_standbywfe                           :  1;
     unsigned      cpu0_standbywfe                           :  1;
#else    /* Little Endian */
     unsigned      cpu0_standbywfe                           :  1;
     unsigned      cpu1_standbywfe                           :  1;
     unsigned      cpu2_standbywfe                           :  1;
     unsigned      cpu3_standbywfe                           :  1;
     unsigned      cpu4_standbywfe                           :  1;
     unsigned      cpu5_standbywfe                           :  1;
     unsigned      cpu6_standbywfe                           :  1;
     unsigned      cpu7_standbywfe                           :  1;
     unsigned      cpu8_standbywfe                           :  1;
     unsigned      cpu9_standbywfe                           :  1;
     unsigned      cpu10_standbywfe                          :  1;
     unsigned      cpu11_standbywfe                          :  1;
     unsigned      cpu12_standbywfe                          :  1;
     unsigned      cpu13_standbywfe                          :  1;
     unsigned      cpu14_standbywfe                          :  1;
     unsigned      cpu15_standbywfe                          :  1;
     unsigned      cpu16_standbywfe                          :  1;
     unsigned      cpu17_standbywfe                          :  1;
     unsigned      cpu18_standbywfe                          :  1;
     unsigned      cpu19_standbywfe                          :  1;
     unsigned      cpu20_standbywfe                          :  1;
     unsigned      cpu21_standbywfe                          :  1;
     unsigned      cpu22_standbywfe                          :  1;
     unsigned      cpu23_standbywfe                          :  1;
     unsigned      cpu24_standbywfe                          :  1;
     unsigned      cpu25_standbywfe                          :  1;
     unsigned      cpu26_standbywfe                          :  1;
     unsigned      cpu27_standbywfe                          :  1;
     unsigned      cpu28_standbywfe                          :  1;
     unsigned      cpu29_standbywfe                          :  1;
     unsigned      cpu30_standbywfe                          :  1;
     unsigned      cpu31_standbywfe                          :  1;
#endif
} ncp_syscon_pwr_STANDBYWFE_r_xlf_t;

/*! @struct ncp_syscon_pwr_STANDBYWFI_r_xlf_t
 *  @brief CPU Standby Wait For Interrupt Status Register
 *  @details This read-only status register contains the current state of the Wait-For-Interrupt indication for each of the CPUs
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_STANDBYWFI_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cpu31_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> CPU 31 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu30_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> CPU 30 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu29_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> CPU 29 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu28_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> CPU 28 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu27_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> CPU 27 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu26_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> CPU 26 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu25_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> CPU 25 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu24_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> CPU 24 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu23_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> CPU 23 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu22_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> CPU 22 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu21_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> CPU 21 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu20_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> CPU 20 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu19_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> CPU 19 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu18_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> CPU 18 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu17_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> CPU 17 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu16_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> CPU 16 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu15_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> CPU 15 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu14_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> CPU 14 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu13_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> CPU 13 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu12_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> CPU 12 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu11_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> CPU 11 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu10_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> CPU 10 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu9_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> CPU 9 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu8_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> CPU 8 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu7_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU 7 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu6_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU 6 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu5_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU 5 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu4_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU 4 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu3_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU 3 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu2_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU 2 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu1_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU 1 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu0_standbywfi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU 0 waiting for interrupt. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_STANDBYWFI_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      cpu31_standbywfi                          :  1;
     unsigned      cpu30_standbywfi                          :  1;
     unsigned      cpu29_standbywfi                          :  1;
     unsigned      cpu28_standbywfi                          :  1;
     unsigned      cpu27_standbywfi                          :  1;
     unsigned      cpu26_standbywfi                          :  1;
     unsigned      cpu25_standbywfi                          :  1;
     unsigned      cpu24_standbywfi                          :  1;
     unsigned      cpu23_standbywfi                          :  1;
     unsigned      cpu22_standbywfi                          :  1;
     unsigned      cpu21_standbywfi                          :  1;
     unsigned      cpu20_standbywfi                          :  1;
     unsigned      cpu19_standbywfi                          :  1;
     unsigned      cpu18_standbywfi                          :  1;
     unsigned      cpu17_standbywfi                          :  1;
     unsigned      cpu16_standbywfi                          :  1;
     unsigned      cpu15_standbywfi                          :  1;
     unsigned      cpu14_standbywfi                          :  1;
     unsigned      cpu13_standbywfi                          :  1;
     unsigned      cpu12_standbywfi                          :  1;
     unsigned      cpu11_standbywfi                          :  1;
     unsigned      cpu10_standbywfi                          :  1;
     unsigned      cpu9_standbywfi                           :  1;
     unsigned      cpu8_standbywfi                           :  1;
     unsigned      cpu7_standbywfi                           :  1;
     unsigned      cpu6_standbywfi                           :  1;
     unsigned      cpu5_standbywfi                           :  1;
     unsigned      cpu4_standbywfi                           :  1;
     unsigned      cpu3_standbywfi                           :  1;
     unsigned      cpu2_standbywfi                           :  1;
     unsigned      cpu1_standbywfi                           :  1;
     unsigned      cpu0_standbywfi                           :  1;
#else    /* Little Endian */
     unsigned      cpu0_standbywfi                           :  1;
     unsigned      cpu1_standbywfi                           :  1;
     unsigned      cpu2_standbywfi                           :  1;
     unsigned      cpu3_standbywfi                           :  1;
     unsigned      cpu4_standbywfi                           :  1;
     unsigned      cpu5_standbywfi                           :  1;
     unsigned      cpu6_standbywfi                           :  1;
     unsigned      cpu7_standbywfi                           :  1;
     unsigned      cpu8_standbywfi                           :  1;
     unsigned      cpu9_standbywfi                           :  1;
     unsigned      cpu10_standbywfi                          :  1;
     unsigned      cpu11_standbywfi                          :  1;
     unsigned      cpu12_standbywfi                          :  1;
     unsigned      cpu13_standbywfi                          :  1;
     unsigned      cpu14_standbywfi                          :  1;
     unsigned      cpu15_standbywfi                          :  1;
     unsigned      cpu16_standbywfi                          :  1;
     unsigned      cpu17_standbywfi                          :  1;
     unsigned      cpu18_standbywfi                          :  1;
     unsigned      cpu19_standbywfi                          :  1;
     unsigned      cpu20_standbywfi                          :  1;
     unsigned      cpu21_standbywfi                          :  1;
     unsigned      cpu22_standbywfi                          :  1;
     unsigned      cpu23_standbywfi                          :  1;
     unsigned      cpu24_standbywfi                          :  1;
     unsigned      cpu25_standbywfi                          :  1;
     unsigned      cpu26_standbywfi                          :  1;
     unsigned      cpu27_standbywfi                          :  1;
     unsigned      cpu28_standbywfi                          :  1;
     unsigned      cpu29_standbywfi                          :  1;
     unsigned      cpu30_standbywfi                          :  1;
     unsigned      cpu31_standbywfi                          :  1;
#endif
} ncp_syscon_pwr_STANDBYWFI_r_xlf_t;

/*! @struct ncp_syscon_pwr_STANDBYWFIL2_r_xlf_t
 *  @brief CPU Cluster L2 Standby Wait For Interrupt Status Register
 *  @details This read-only status register contains the current state of the Wait-For-Interrupt indication for each of the
	 CPU cluster L2s
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_STANDBYWFIL2_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_standbywfil2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU cluster 7 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_standbywfil2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU cluster 6 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_standbywfil2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU cluster 5 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_standbywfil2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU cluster 4 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_standbywfil2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU cluster 3 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_standbywfil2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU cluster 2 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_standbywfil2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU cluster 1 waiting for interrupt. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_standbywfil2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU cluster 0 waiting for interrupt. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_STANDBYWFIL2_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_standbywfil2                     :  1;
     unsigned      cluster6_standbywfil2                     :  1;
     unsigned      cluster5_standbywfil2                     :  1;
     unsigned      cluster4_standbywfil2                     :  1;
     unsigned      cluster3_standbywfil2                     :  1;
     unsigned      cluster2_standbywfil2                     :  1;
     unsigned      cluster1_standbywfil2                     :  1;
     unsigned      cluster0_standbywfil2                     :  1;
#else    /* Little Endian */
     unsigned      cluster0_standbywfil2                     :  1;
     unsigned      cluster1_standbywfil2                     :  1;
     unsigned      cluster2_standbywfil2                     :  1;
     unsigned      cluster3_standbywfil2                     :  1;
     unsigned      cluster4_standbywfil2                     :  1;
     unsigned      cluster5_standbywfil2                     :  1;
     unsigned      cluster6_standbywfil2                     :  1;
     unsigned      cluster7_standbywfil2                     :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_STANDBYWFIL2_r_xlf_t;

/*! @struct ncp_syscon_gic_wake_request_r_xlf_t
 *  @brief GIC Wake Request Register
 *  @details This read-only register contains the current GIC wake request status for each of the CPUs.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_gic_wake_request_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cpu31_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> CPU 31 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu30_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> CPU 30 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu29_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> CPU 29 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu28_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> CPU 28 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu27_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> CPU 27 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu26_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> CPU 26 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu25_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> CPU 25 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu24_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> CPU 24 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu23_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> CPU 23 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu22_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> CPU 22 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu21_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> CPU 21 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu20_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> CPU 20 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu19_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> CPU 19 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu18_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> CPU 18 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu17_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> CPU 17 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu16_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> CPU 16 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu15_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> CPU 15 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu14_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> CPU 14 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu13_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> CPU 13 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu12_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> CPU 12 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu11_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> CPU 11 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu10_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> CPU 10 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu9_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> CPU 9 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu8_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> CPU 8 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu7_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU 7 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu6_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU 6 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu5_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU 5 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu4_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU 4 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu3_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU 3 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu2_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU 2 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu1_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU 1 GIC wake request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu0_gic_wake_request </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU 0 GIC wake request. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_gic_wake_request_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      cpu31_gic_wake_request                    :  1;
     unsigned      cpu30_gic_wake_request                    :  1;
     unsigned      cpu29_gic_wake_request                    :  1;
     unsigned      cpu28_gic_wake_request                    :  1;
     unsigned      cpu27_gic_wake_request                    :  1;
     unsigned      cpu26_gic_wake_request                    :  1;
     unsigned      cpu25_gic_wake_request                    :  1;
     unsigned      cpu24_gic_wake_request                    :  1;
     unsigned      cpu23_gic_wake_request                    :  1;
     unsigned      cpu22_gic_wake_request                    :  1;
     unsigned      cpu21_gic_wake_request                    :  1;
     unsigned      cpu20_gic_wake_request                    :  1;
     unsigned      cpu19_gic_wake_request                    :  1;
     unsigned      cpu18_gic_wake_request                    :  1;
     unsigned      cpu17_gic_wake_request                    :  1;
     unsigned      cpu16_gic_wake_request                    :  1;
     unsigned      cpu15_gic_wake_request                    :  1;
     unsigned      cpu14_gic_wake_request                    :  1;
     unsigned      cpu13_gic_wake_request                    :  1;
     unsigned      cpu12_gic_wake_request                    :  1;
     unsigned      cpu11_gic_wake_request                    :  1;
     unsigned      cpu10_gic_wake_request                    :  1;
     unsigned      cpu9_gic_wake_request                     :  1;
     unsigned      cpu8_gic_wake_request                     :  1;
     unsigned      cpu7_gic_wake_request                     :  1;
     unsigned      cpu6_gic_wake_request                     :  1;
     unsigned      cpu5_gic_wake_request                     :  1;
     unsigned      cpu4_gic_wake_request                     :  1;
     unsigned      cpu3_gic_wake_request                     :  1;
     unsigned      cpu2_gic_wake_request                     :  1;
     unsigned      cpu1_gic_wake_request                     :  1;
     unsigned      cpu0_gic_wake_request                     :  1;
#else    /* Little Endian */
     unsigned      cpu0_gic_wake_request                     :  1;
     unsigned      cpu1_gic_wake_request                     :  1;
     unsigned      cpu2_gic_wake_request                     :  1;
     unsigned      cpu3_gic_wake_request                     :  1;
     unsigned      cpu4_gic_wake_request                     :  1;
     unsigned      cpu5_gic_wake_request                     :  1;
     unsigned      cpu6_gic_wake_request                     :  1;
     unsigned      cpu7_gic_wake_request                     :  1;
     unsigned      cpu8_gic_wake_request                     :  1;
     unsigned      cpu9_gic_wake_request                     :  1;
     unsigned      cpu10_gic_wake_request                    :  1;
     unsigned      cpu11_gic_wake_request                    :  1;
     unsigned      cpu12_gic_wake_request                    :  1;
     unsigned      cpu13_gic_wake_request                    :  1;
     unsigned      cpu14_gic_wake_request                    :  1;
     unsigned      cpu15_gic_wake_request                    :  1;
     unsigned      cpu16_gic_wake_request                    :  1;
     unsigned      cpu17_gic_wake_request                    :  1;
     unsigned      cpu18_gic_wake_request                    :  1;
     unsigned      cpu19_gic_wake_request                    :  1;
     unsigned      cpu20_gic_wake_request                    :  1;
     unsigned      cpu21_gic_wake_request                    :  1;
     unsigned      cpu22_gic_wake_request                    :  1;
     unsigned      cpu23_gic_wake_request                    :  1;
     unsigned      cpu24_gic_wake_request                    :  1;
     unsigned      cpu25_gic_wake_request                    :  1;
     unsigned      cpu26_gic_wake_request                    :  1;
     unsigned      cpu27_gic_wake_request                    :  1;
     unsigned      cpu28_gic_wake_request                    :  1;
     unsigned      cpu29_gic_wake_request                    :  1;
     unsigned      cpu30_gic_wake_request                    :  1;
     unsigned      cpu31_gic_wake_request                    :  1;
#endif
} ncp_syscon_gic_wake_request_r_xlf_t;

/*! @struct ncp_syscon_psm_wait_cnt_r_xlf_t
 *  @brief PSM Wait Counter Register
 *  @details This read-only register contains the current values of the 6b and 14b maximal length LFSR counters that are
	used to determine how many reference clocks we wait between state transition in the powerup state machine.
	If the psm_waits_16k fuse or fuse force value is set, we use the 14b counter to wait 16K clocks, otherwise
	we use the 6b counter to wait 64 clocks.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_psm_wait_cnt_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param psm_wait_lfsr_16k </td>
 *     <td width="20%" align="center"> 14 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> 14b LFSR wait counter value. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param psm_wait_lfsr_64 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 6b LFSR wait counter value. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_psm_wait_cnt_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 10;
     unsigned      psm_wait_lfsr_16k                         : 14;
     unsigned      reserved1                                 :  2;
     unsigned      psm_wait_lfsr_64                          :  6;
#else    /* Little Endian */
     unsigned      psm_wait_lfsr_64                          :  6;
     unsigned      reserved1                                 :  2;
     unsigned      psm_wait_lfsr_16k                         : 14;
     unsigned      reserved0                                 : 10;
#endif
} ncp_syscon_psm_wait_cnt_r_xlf_t;

/*! @struct ncp_syscon_pwr_enable_self_pwrdn_r_xlf_t
 *  @brief CPU Self Powerdown Enable Register
 *  @details If a bit is set in this register, the corresponding CPU is enabled to use use the hardware controlled by the CPU
	 Powerdown Request register to powerdown itself and potentially its cluster's L2 and other logic.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_enable_self_pwrdn_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cpu31_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> CPU 31 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu30_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> CPU 30 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu29_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> CPU 29 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu28_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> CPU 28 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu27_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> CPU 27 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu26_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> CPU 26 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu25_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> CPU 25 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu24_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> CPU 24 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu23_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> CPU 23 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu22_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> CPU 22 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu21_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> CPU 21 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu20_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> CPU 20 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu19_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> CPU 19 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu18_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> CPU 18 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu17_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> CPU 17 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu16_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> CPU 16 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu15_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> CPU 15 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu14_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> CPU 14 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu13_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> CPU 13 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu12_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> CPU 12 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu11_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> CPU 11 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu10_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> CPU 10 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu9_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> CPU 9 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu8_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> CPU 8 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu7_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU 7 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu6_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU 6 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu5_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU 5 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu4_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU 4 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu3_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU 3 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu2_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU 2 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu1_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU 1 self powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu0_self_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU 0 self powerdown enable. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_enable_self_pwrdn_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      cpu31_self_pwrdn_enable                   :  1;
     unsigned      cpu30_self_pwrdn_enable                   :  1;
     unsigned      cpu29_self_pwrdn_enable                   :  1;
     unsigned      cpu28_self_pwrdn_enable                   :  1;
     unsigned      cpu27_self_pwrdn_enable                   :  1;
     unsigned      cpu26_self_pwrdn_enable                   :  1;
     unsigned      cpu25_self_pwrdn_enable                   :  1;
     unsigned      cpu24_self_pwrdn_enable                   :  1;
     unsigned      cpu23_self_pwrdn_enable                   :  1;
     unsigned      cpu22_self_pwrdn_enable                   :  1;
     unsigned      cpu21_self_pwrdn_enable                   :  1;
     unsigned      cpu20_self_pwrdn_enable                   :  1;
     unsigned      cpu19_self_pwrdn_enable                   :  1;
     unsigned      cpu18_self_pwrdn_enable                   :  1;
     unsigned      cpu17_self_pwrdn_enable                   :  1;
     unsigned      cpu16_self_pwrdn_enable                   :  1;
     unsigned      cpu15_self_pwrdn_enable                   :  1;
     unsigned      cpu14_self_pwrdn_enable                   :  1;
     unsigned      cpu13_self_pwrdn_enable                   :  1;
     unsigned      cpu12_self_pwrdn_enable                   :  1;
     unsigned      cpu11_self_pwrdn_enable                   :  1;
     unsigned      cpu10_self_pwrdn_enable                   :  1;
     unsigned      cpu9_self_pwrdn_enable                    :  1;
     unsigned      cpu8_self_pwrdn_enable                    :  1;
     unsigned      cpu7_self_pwrdn_enable                    :  1;
     unsigned      cpu6_self_pwrdn_enable                    :  1;
     unsigned      cpu5_self_pwrdn_enable                    :  1;
     unsigned      cpu4_self_pwrdn_enable                    :  1;
     unsigned      cpu3_self_pwrdn_enable                    :  1;
     unsigned      cpu2_self_pwrdn_enable                    :  1;
     unsigned      cpu1_self_pwrdn_enable                    :  1;
     unsigned      cpu0_self_pwrdn_enable                    :  1;
#else    /* Little Endian */
     unsigned      cpu0_self_pwrdn_enable                    :  1;
     unsigned      cpu1_self_pwrdn_enable                    :  1;
     unsigned      cpu2_self_pwrdn_enable                    :  1;
     unsigned      cpu3_self_pwrdn_enable                    :  1;
     unsigned      cpu4_self_pwrdn_enable                    :  1;
     unsigned      cpu5_self_pwrdn_enable                    :  1;
     unsigned      cpu6_self_pwrdn_enable                    :  1;
     unsigned      cpu7_self_pwrdn_enable                    :  1;
     unsigned      cpu8_self_pwrdn_enable                    :  1;
     unsigned      cpu9_self_pwrdn_enable                    :  1;
     unsigned      cpu10_self_pwrdn_enable                   :  1;
     unsigned      cpu11_self_pwrdn_enable                   :  1;
     unsigned      cpu12_self_pwrdn_enable                   :  1;
     unsigned      cpu13_self_pwrdn_enable                   :  1;
     unsigned      cpu14_self_pwrdn_enable                   :  1;
     unsigned      cpu15_self_pwrdn_enable                   :  1;
     unsigned      cpu16_self_pwrdn_enable                   :  1;
     unsigned      cpu17_self_pwrdn_enable                   :  1;
     unsigned      cpu18_self_pwrdn_enable                   :  1;
     unsigned      cpu19_self_pwrdn_enable                   :  1;
     unsigned      cpu20_self_pwrdn_enable                   :  1;
     unsigned      cpu21_self_pwrdn_enable                   :  1;
     unsigned      cpu22_self_pwrdn_enable                   :  1;
     unsigned      cpu23_self_pwrdn_enable                   :  1;
     unsigned      cpu24_self_pwrdn_enable                   :  1;
     unsigned      cpu25_self_pwrdn_enable                   :  1;
     unsigned      cpu26_self_pwrdn_enable                   :  1;
     unsigned      cpu27_self_pwrdn_enable                   :  1;
     unsigned      cpu28_self_pwrdn_enable                   :  1;
     unsigned      cpu29_self_pwrdn_enable                   :  1;
     unsigned      cpu30_self_pwrdn_enable                   :  1;
     unsigned      cpu31_self_pwrdn_enable                   :  1;
#endif
} ncp_syscon_pwr_enable_self_pwrdn_r_xlf_t;

/*! @struct ncp_syscon_pwr_pwrdn_cpu_r_xlf_t
 *  @brief CPU Powerdown Request Register
 *  @details If a bit is set in this register and the corresponding bit is set in the CPU Self Powerdown Enable register,
	 the corresponding CPU will be powered down by the hardware once its SMPEN indication is deasserted and its
	 STANDBYWFI indication is asserted.  If the bit for this CPU's cluster is also set in the Cluster Powerdown
	 Enable register, then the hardware will also powerdown the associated L2 and all bridge logic in the
	 cluster once the L2 has asserted its STANDBYWFIL2 indication.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_pwrdn_cpu_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cpu31_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> CPU 31 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu30_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> CPU 30 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu29_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> CPU 29 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu28_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> CPU 28 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu27_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> CPU 27 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu26_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> CPU 26 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu25_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> CPU 25 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu24_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> CPU 24 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu23_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> CPU 23 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu22_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> CPU 22 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu21_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> CPU 21 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu20_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> CPU 20 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu19_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> CPU 19 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu18_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> CPU 18 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu17_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> CPU 17 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu16_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> CPU 16 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu15_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> CPU 15 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu14_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> CPU 14 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu13_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> CPU 13 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu12_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> CPU 12 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu11_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> CPU 11 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu10_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> CPU 10 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu9_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> CPU 9 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu8_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> CPU 8 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu7_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU 7 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu6_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU 6 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu5_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU 5 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu4_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU 4 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu3_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU 3 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu2_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU 2 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu1_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU 1 powerdown request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu0_pwrdn_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU 0 powerdown request. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_pwrdn_cpu_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      cpu31_pwrdn_req                           :  1;
     unsigned      cpu30_pwrdn_req                           :  1;
     unsigned      cpu29_pwrdn_req                           :  1;
     unsigned      cpu28_pwrdn_req                           :  1;
     unsigned      cpu27_pwrdn_req                           :  1;
     unsigned      cpu26_pwrdn_req                           :  1;
     unsigned      cpu25_pwrdn_req                           :  1;
     unsigned      cpu24_pwrdn_req                           :  1;
     unsigned      cpu23_pwrdn_req                           :  1;
     unsigned      cpu22_pwrdn_req                           :  1;
     unsigned      cpu21_pwrdn_req                           :  1;
     unsigned      cpu20_pwrdn_req                           :  1;
     unsigned      cpu19_pwrdn_req                           :  1;
     unsigned      cpu18_pwrdn_req                           :  1;
     unsigned      cpu17_pwrdn_req                           :  1;
     unsigned      cpu16_pwrdn_req                           :  1;
     unsigned      cpu15_pwrdn_req                           :  1;
     unsigned      cpu14_pwrdn_req                           :  1;
     unsigned      cpu13_pwrdn_req                           :  1;
     unsigned      cpu12_pwrdn_req                           :  1;
     unsigned      cpu11_pwrdn_req                           :  1;
     unsigned      cpu10_pwrdn_req                           :  1;
     unsigned      cpu9_pwrdn_req                            :  1;
     unsigned      cpu8_pwrdn_req                            :  1;
     unsigned      cpu7_pwrdn_req                            :  1;
     unsigned      cpu6_pwrdn_req                            :  1;
     unsigned      cpu5_pwrdn_req                            :  1;
     unsigned      cpu4_pwrdn_req                            :  1;
     unsigned      cpu3_pwrdn_req                            :  1;
     unsigned      cpu2_pwrdn_req                            :  1;
     unsigned      cpu1_pwrdn_req                            :  1;
     unsigned      cpu0_pwrdn_req                            :  1;
#else    /* Little Endian */
     unsigned      cpu0_pwrdn_req                            :  1;
     unsigned      cpu1_pwrdn_req                            :  1;
     unsigned      cpu2_pwrdn_req                            :  1;
     unsigned      cpu3_pwrdn_req                            :  1;
     unsigned      cpu4_pwrdn_req                            :  1;
     unsigned      cpu5_pwrdn_req                            :  1;
     unsigned      cpu6_pwrdn_req                            :  1;
     unsigned      cpu7_pwrdn_req                            :  1;
     unsigned      cpu8_pwrdn_req                            :  1;
     unsigned      cpu9_pwrdn_req                            :  1;
     unsigned      cpu10_pwrdn_req                           :  1;
     unsigned      cpu11_pwrdn_req                           :  1;
     unsigned      cpu12_pwrdn_req                           :  1;
     unsigned      cpu13_pwrdn_req                           :  1;
     unsigned      cpu14_pwrdn_req                           :  1;
     unsigned      cpu15_pwrdn_req                           :  1;
     unsigned      cpu16_pwrdn_req                           :  1;
     unsigned      cpu17_pwrdn_req                           :  1;
     unsigned      cpu18_pwrdn_req                           :  1;
     unsigned      cpu19_pwrdn_req                           :  1;
     unsigned      cpu20_pwrdn_req                           :  1;
     unsigned      cpu21_pwrdn_req                           :  1;
     unsigned      cpu22_pwrdn_req                           :  1;
     unsigned      cpu23_pwrdn_req                           :  1;
     unsigned      cpu24_pwrdn_req                           :  1;
     unsigned      cpu25_pwrdn_req                           :  1;
     unsigned      cpu26_pwrdn_req                           :  1;
     unsigned      cpu27_pwrdn_req                           :  1;
     unsigned      cpu28_pwrdn_req                           :  1;
     unsigned      cpu29_pwrdn_req                           :  1;
     unsigned      cpu30_pwrdn_req                           :  1;
     unsigned      cpu31_pwrdn_req                           :  1;
#endif
} ncp_syscon_pwr_pwrdn_cpu_r_xlf_t;

/*! @struct ncp_syscon_pwr_pwrdn_cluster_r_xlf_t
 *  @brief CPU Cluster Powerdown Enable Register
 *  @details If a bit is set in this register, when a CPU in the corresponding cluster is powered down using the CPU
	 Powerdown Request register, the L2 and all of its associated logic will also be powered down.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pwr_pwrdn_cluster_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU cluster 7 powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU cluster 6 powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU cluster 5 powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU cluster 4 powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU cluster 3 powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU cluster 2 powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU cluster 1 powerdown enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_pwrdn_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU cluster 0 powerdown enable. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pwr_pwrdn_cluster_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_pwrdn_enable                     :  1;
     unsigned      cluster6_pwrdn_enable                     :  1;
     unsigned      cluster5_pwrdn_enable                     :  1;
     unsigned      cluster4_pwrdn_enable                     :  1;
     unsigned      cluster3_pwrdn_enable                     :  1;
     unsigned      cluster2_pwrdn_enable                     :  1;
     unsigned      cluster1_pwrdn_enable                     :  1;
     unsigned      cluster0_pwrdn_enable                     :  1;
#else    /* Little Endian */
     unsigned      cluster0_pwrdn_enable                     :  1;
     unsigned      cluster1_pwrdn_enable                     :  1;
     unsigned      cluster2_pwrdn_enable                     :  1;
     unsigned      cluster3_pwrdn_enable                     :  1;
     unsigned      cluster4_pwrdn_enable                     :  1;
     unsigned      cluster5_pwrdn_enable                     :  1;
     unsigned      cluster6_pwrdn_enable                     :  1;
     unsigned      cluster7_pwrdn_enable                     :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_pwr_pwrdn_cluster_r_xlf_t;

/*! @struct ncp_syscon_pdsm_state_ia_r_xlf_t
 *  @brief Powerdown State Machine Indirect Address Register
 *  @details The value is this register determines which CPU's powerdown state machine state register is accessed by reads
	 or writes to the Powerdown State Machine Indirect Data register.  Writing a number to this register and then
	 doing a read or write to the Powerdown State Machine Indirect Data register's address will read or write
	 the state register for the numbered CPU.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pdsm_state_ia_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cpu_number </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU number to access. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pdsm_state_ia_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 27;
     unsigned      cpu_number                                :  5;
#else    /* Little Endian */
     unsigned      cpu_number                                :  5;
     unsigned      reserved0                                 : 27;
#endif
} ncp_syscon_pdsm_state_ia_r_xlf_t;

/*! @struct ncp_syscon_pdsm_state_id_r_xlf_t
 *  @brief Powerdown State Machine Indirect Data Register
 *  @details This address is used as an indirect means of accessing the per CPU Powerdown State Machine state registers.
	 The number of the targeted CPU must first be written to the Powerdown State Machine Indirect Address register
	 and then reads or writes to this register will be directed to the referenced CPU's state register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pdsm_state_id_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param pdsm_state </td>
 *     <td width="20%" align="center"> 15 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Powerdown SM current state register for the targeted
 *        CPU.
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pdsm_state_id_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 17;
     unsigned      pdsm_state                                : 15;
#else    /* Little Endian */
     unsigned      pdsm_state                                : 15;
     unsigned      reserved0                                 : 17;
#endif
} ncp_syscon_pdsm_state_id_r_xlf_t;

/*! @struct ncp_syscon_cdc_preq_r_xlf_t
 *  @brief DSP Cluster Power State Change Request Register
 *  @details If a bit is set, the corresponding DSP cluster is requested to initiate a power state change to the state
	 specified in the corresponding field of the DSP Cluster Requested Power State register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_cdc_preq_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cdc3_preq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> DSP Cluster 3 power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cdc2_preq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> DSP Cluster 2 power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cdc1_preq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> DSP Cluster 1 power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cdc0_preq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DSP Cluster 0 power state change request. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_cdc_preq_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 28;
     unsigned      cdc3_preq                                 :  1;
     unsigned      cdc2_preq                                 :  1;
     unsigned      cdc1_preq                                 :  1;
     unsigned      cdc0_preq                                 :  1;
#else    /* Little Endian */
     unsigned      cdc0_preq                                 :  1;
     unsigned      cdc1_preq                                 :  1;
     unsigned      cdc2_preq                                 :  1;
     unsigned      cdc3_preq                                 :  1;
     unsigned      reserved0                                 : 28;
#endif
} ncp_syscon_cdc_preq_r_xlf_t;

/*! @struct ncp_syscon_cdc_pstate_r_xlf_t
 *  @brief DSP Cluster Requested Power State Register
 *  @details Each field contains the power state being requested for the corresponding DSP cluster if that cluster is
	 currently requesting a power state change through the DSP Cluster Power State Change Request register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_cdc_pstate_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cdc3_pstate </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> DSP Cluster 3 requested power state. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cdc2_pstate </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> DSP Cluster 2 requested power state. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cdc1_pstate </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> DSP Cluster 1 requested power state. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cdc0_pstate </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DSP Cluster 0 requested power state. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_cdc_pstate_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 28;
     unsigned      cdc3_pstate                               :  1;
     unsigned      cdc2_pstate                               :  1;
     unsigned      cdc1_pstate                               :  1;
     unsigned      cdc0_pstate                               :  1;
#else    /* Little Endian */
     unsigned      cdc0_pstate                               :  1;
     unsigned      cdc1_pstate                               :  1;
     unsigned      cdc2_pstate                               :  1;
     unsigned      cdc3_pstate                               :  1;
     unsigned      reserved0                                 : 28;
#endif
} ncp_syscon_cdc_pstate_r_xlf_t;

/*! @struct ncp_syscon_cdc_qactive_r_xlf_t
 *  @brief DSP Cluster Clock Active Status Register
 *  @details This read-only status register contains the current state of the clock activity bits for each of the DSP clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_cdc_qactive_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cdc3_qactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> DSP Cluster 3 clock is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cdc2_qactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> DSP Cluster 2 clock is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cdc1_qactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> DSP Cluster 1 clock is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cdc0_qactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DSP Cluster 0 clock is active indication. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_cdc_qactive_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 28;
     unsigned      cdc3_qactive                              :  1;
     unsigned      cdc2_qactive                              :  1;
     unsigned      cdc1_qactive                              :  1;
     unsigned      cdc0_qactive                              :  1;
#else    /* Little Endian */
     unsigned      cdc0_qactive                              :  1;
     unsigned      cdc1_qactive                              :  1;
     unsigned      cdc2_qactive                              :  1;
     unsigned      cdc3_qactive                              :  1;
     unsigned      reserved0                                 : 28;
#endif
} ncp_syscon_cdc_qactive_r_xlf_t;

/*! @struct ncp_syscon_cdc_pactive_r_xlf_t
 *  @brief DSP Cluster Active Status Register
 *  @details This read-only status register contains the current state of the activity bits for each of the DSP clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_cdc_pactive_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cdc3_pactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> DSP Cluster 3 is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cdc2_pactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> DSP Cluster 2 is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cdc1_pactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> DSP Cluster 1 is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cdc0_pactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DSP Cluster 0 is active indication. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_cdc_pactive_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 28;
     unsigned      cdc3_pactive                              :  1;
     unsigned      cdc2_pactive                              :  1;
     unsigned      cdc1_pactive                              :  1;
     unsigned      cdc0_pactive                              :  1;
#else    /* Little Endian */
     unsigned      cdc0_pactive                              :  1;
     unsigned      cdc1_pactive                              :  1;
     unsigned      cdc2_pactive                              :  1;
     unsigned      cdc3_pactive                              :  1;
     unsigned      reserved0                                 : 28;
#endif
} ncp_syscon_cdc_pactive_r_xlf_t;

/*! @struct ncp_syscon_cdc_paccept_r_xlf_t
 *  @brief DSP Cluster Power State Change Request Accepted Status Register
 *  @details This read-only status register contains the current state of the PACCEPT response bits
	 for each of the DSP clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_cdc_paccept_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cdc3_paccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> DSP cluster 3 accepted power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cdc2_paccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> DSP cluster 2 accepted power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cdc1_paccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> DSP cluster 1 accepted power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cdc0_paccept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DSP cluster 0 accepted power state change request. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_cdc_paccept_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 28;
     unsigned      cdc3_paccept                              :  1;
     unsigned      cdc2_paccept                              :  1;
     unsigned      cdc1_paccept                              :  1;
     unsigned      cdc0_paccept                              :  1;
#else    /* Little Endian */
     unsigned      cdc0_paccept                              :  1;
     unsigned      cdc1_paccept                              :  1;
     unsigned      cdc2_paccept                              :  1;
     unsigned      cdc3_paccept                              :  1;
     unsigned      reserved0                                 : 28;
#endif
} ncp_syscon_cdc_paccept_r_xlf_t;

/*! @struct ncp_syscon_cdc_pdeny_r_xlf_t
 *  @brief DSP Cluster Power State Change Request Denied Status Register
 *  @details This read-only status register contains the current state of the PDENY response bits
	 for each of the DSP clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_cdc_pdeny_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cdc3_pdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> DSP cluster 3 denied power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cdc2_pdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> DSP cluster 2 denied power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cdc1_pdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> DSP cluster 1 denied power state change request. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cdc0_pdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DSP cluster 0 denied power state change request. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_cdc_pdeny_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 28;
     unsigned      cdc3_pdeny                                :  1;
     unsigned      cdc2_pdeny                                :  1;
     unsigned      cdc1_pdeny                                :  1;
     unsigned      cdc0_pdeny                                :  1;
#else    /* Little Endian */
     unsigned      cdc0_pdeny                                :  1;
     unsigned      cdc1_pdeny                                :  1;
     unsigned      cdc2_pdeny                                :  1;
     unsigned      cdc3_pdeny                                :  1;
     unsigned      reserved0                                 : 28;
#endif
} ncp_syscon_cdc_pdeny_r_xlf_t;

/*! @struct ncp_syscon_pch_cmd_r_xlf_t
 *  @brief Fabric Power State Command Register
 *  @details This register contains the commands and their associated valid indications that determine the desired
	power state to which we'd like the fabric to transition.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pch_cmd_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param pch_v_logic </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Power state command valid for fabric logic. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_cmd_logic </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Power state command for fabric logic. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_v_sf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Power state command valid for fabric snoop filter. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_cmd_sf </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Power state command for fabric snoop filter. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_v_ram1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Power state command valid for fabric RAMs (ways [15:8]). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_cmd_ram1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Power state command for fabric RAMs (ways [15:8]). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_v_ram0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Power state command valid for fabric RAMs (ways [7:0]). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_cmd_ram0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Power state command for fabric RAMs (ways [7:0]). </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pch_cmd_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      pch_v_logic                               :  1;
     unsigned      reserved1                                 :  1;
     unsigned      pch_cmd_logic                             :  2;
     unsigned      pch_v_sf                                  :  1;
     unsigned      reserved2                                 :  1;
     unsigned      pch_cmd_sf                                :  2;
     unsigned      pch_v_ram1                                :  1;
     unsigned      reserved3                                 :  1;
     unsigned      pch_cmd_ram1                              :  2;
     unsigned      pch_v_ram0                                :  1;
     unsigned      reserved4                                 :  1;
     unsigned      pch_cmd_ram0                              :  2;
#else    /* Little Endian */
     unsigned      pch_cmd_ram0                              :  2;
     unsigned      reserved4                                 :  1;
     unsigned      pch_v_ram0                                :  1;
     unsigned      pch_cmd_ram1                              :  2;
     unsigned      reserved3                                 :  1;
     unsigned      pch_v_ram1                                :  1;
     unsigned      pch_cmd_sf                                :  2;
     unsigned      reserved2                                 :  1;
     unsigned      pch_v_sf                                  :  1;
     unsigned      pch_cmd_logic                             :  2;
     unsigned      reserved1                                 :  1;
     unsigned      pch_v_logic                               :  1;
     unsigned      reserved0                                 : 16;
#endif
} ncp_syscon_pch_cmd_r_xlf_t;

/*! @struct ncp_syscon_pch_sm_r_xlf_t
 *  @brief Fabric Power State Machine State  Register
 *  @details This register contains the current fabric power state machine states.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pch_sm_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param pch_sm_logic </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Power state machine state for fabric logic. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_sm_sf </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Power state machine state for fabric snoop filter. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_sm_ram1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Power state machine state for fabric RAMs (ways [15:8]). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_sm_ram0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Power state machine state for fabric RAMs (ways [7:0]). </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pch_sm_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      pch_sm_logic                              :  4;
     unsigned      pch_sm_sf                                 :  4;
     unsigned      pch_sm_ram1                               :  4;
     unsigned      pch_sm_ram0                               :  4;
#else    /* Little Endian */
     unsigned      pch_sm_ram0                               :  4;
     unsigned      pch_sm_ram1                               :  4;
     unsigned      pch_sm_sf                                 :  4;
     unsigned      pch_sm_logic                              :  4;
     unsigned      reserved0                                 : 16;
#endif
} ncp_syscon_pch_sm_r_xlf_t;

/*! @struct ncp_syscon_pch_cstate_r_xlf_t
 *  @brief Fabric Current Power State Register
 *  @details This register contains the current fabric power state.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pch_cstate_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_cstate_logic </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Current power state for fabric logic. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_cstate_sf </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Current power state for fabric snoop filter. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_cstate_ram1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Current power state for fabric RAMs (ways [15:8]). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_cstate_ram0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Current power state for fabric RAMs (ways [7:0]). </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pch_cstate_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 18;
     unsigned      pch_cstate_logic                          :  2;
     unsigned      reserved1                                 :  2;
     unsigned      pch_cstate_sf                             :  2;
     unsigned      reserved2                                 :  2;
     unsigned      pch_cstate_ram1                           :  2;
     unsigned      reserved3                                 :  2;
     unsigned      pch_cstate_ram0                           :  2;
#else    /* Little Endian */
     unsigned      pch_cstate_ram0                           :  2;
     unsigned      reserved3                                 :  2;
     unsigned      pch_cstate_ram1                           :  2;
     unsigned      reserved2                                 :  2;
     unsigned      pch_cstate_sf                             :  2;
     unsigned      reserved1                                 :  2;
     unsigned      pch_cstate_logic                          :  2;
     unsigned      reserved0                                 : 18;
#endif
} ncp_syscon_pch_cstate_r_xlf_t;

/*! @struct ncp_syscon_pch_state_r_xlf_t
 *  @brief Fabric Request Power State Change Register
 *  @details This register contains the requested fabric power state change being requested (driven on PSTATE).
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pch_state_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_state_logic </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Requested power state for fabric logic. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_state_sf </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Requested power state for fabric snoop filter. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_state_ram1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Requested power state for fabric RAMs (ways [15:8]). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_state_ram0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Requested power state for fabric RAMs (ways [7:0]). </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pch_state_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 18;
     unsigned      pch_state_logic                           :  2;
     unsigned      reserved1                                 :  2;
     unsigned      pch_state_sf                              :  2;
     unsigned      reserved2                                 :  2;
     unsigned      pch_state_ram1                            :  2;
     unsigned      reserved3                                 :  2;
     unsigned      pch_state_ram0                            :  2;
#else    /* Little Endian */
     unsigned      pch_state_ram0                            :  2;
     unsigned      reserved3                                 :  2;
     unsigned      pch_state_ram1                            :  2;
     unsigned      reserved2                                 :  2;
     unsigned      pch_state_sf                              :  2;
     unsigned      reserved1                                 :  2;
     unsigned      pch_state_logic                           :  2;
     unsigned      reserved0                                 : 18;
#endif
} ncp_syscon_pch_state_r_xlf_t;

/*! @struct ncp_syscon_pch_req_r_xlf_t
 *  @brief Fabric Power State Change Request Register
 *  @details This register contains the valid bits that indicate a fabric power state change is requested (driven on PREQ).
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pch_req_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param pch_req_logic </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Power state change requested for fabric logic. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_req_sf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Power state change requested for fabric snoop filter. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_req_ram1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Power state change requested for fabric RAMs (ways
 *        [15:8]).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_req_ram0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Power state change requested for fabric RAMs (ways
 *        [7:0]).
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pch_req_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 28;
     unsigned      pch_req_logic                             :  1;
     unsigned      pch_req_sf                                :  1;
     unsigned      pch_req_ram1                              :  1;
     unsigned      pch_req_ram0                              :  1;
#else    /* Little Endian */
     unsigned      pch_req_ram0                              :  1;
     unsigned      pch_req_ram1                              :  1;
     unsigned      pch_req_sf                                :  1;
     unsigned      pch_req_logic                             :  1;
     unsigned      reserved0                                 : 28;
#endif
} ncp_syscon_pch_req_r_xlf_t;

/*! @struct ncp_syscon_pch_stat_r_xlf_t
 *  @brief Fabric Power State Status Register
 *  @details This register contains the read-only status of the power state change state machine and the
	associated status and response signals from the fabric (PACTIVE, PDENY, PACCEPT).
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pch_stat_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param pch_tocnt </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Fabric power up timeout counter value. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_pwrd_up_logic </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Fabric logic powered up on system startup. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_pwrd_up_sf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Fabric snoop filter powered up on system startup. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_pwrd_up_ram1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Fabric RAMs (ways [15:8]) powered up on system startup. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_pwrd_up_ram0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Fabric RAMs (ways [7:0]) powered up on system startup. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_active_logic </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Fabric logic active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_active_sf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Fabric snoop filter active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_active_ram1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Fabric RAMs (ways [15:8]) active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_active_ram0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Fabric RAMs (ways [7:0]) active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_deny_logic </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Power state change request denied for fabric logic. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_deny_sf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Power state change request denied for fabric snoop
 *        filter.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_deny_ram1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Power state change request denied for fabric RAMs
 *        (ways [15:8]).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_deny_ram0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Power state change request denied for fabric RAMs
 *        (ways [7:0]).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_accept_logic </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Power state change request accepted for fabric logic. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_accept_sf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Power state change request accepted for fabric snoop
 *        filter.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_accept_ram1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Power state change request accepted for fabric RAMs
 *        (ways [15:8]).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pch_accept_ram0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Power state change request accepted for fabric RAMs
 *        (ways [7:0]).
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pch_stat_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      pch_tocnt                                 : 10;
     unsigned      pch_pwrd_up_logic                         :  1;
     unsigned      pch_pwrd_up_sf                            :  1;
     unsigned      pch_pwrd_up_ram1                          :  1;
     unsigned      pch_pwrd_up_ram0                          :  1;
     unsigned      pch_active_logic                          :  1;
     unsigned      pch_active_sf                             :  1;
     unsigned      pch_active_ram1                           :  1;
     unsigned      pch_active_ram0                           :  1;
     unsigned      pch_deny_logic                            :  1;
     unsigned      pch_deny_sf                               :  1;
     unsigned      pch_deny_ram1                             :  1;
     unsigned      pch_deny_ram0                             :  1;
     unsigned      pch_accept_logic                          :  1;
     unsigned      pch_accept_sf                             :  1;
     unsigned      pch_accept_ram1                           :  1;
     unsigned      pch_accept_ram0                           :  1;
#else    /* Little Endian */
     unsigned      pch_accept_ram0                           :  1;
     unsigned      pch_accept_ram1                           :  1;
     unsigned      pch_accept_sf                             :  1;
     unsigned      pch_accept_logic                          :  1;
     unsigned      pch_deny_ram0                             :  1;
     unsigned      pch_deny_ram1                             :  1;
     unsigned      pch_deny_sf                               :  1;
     unsigned      pch_deny_logic                            :  1;
     unsigned      pch_active_ram0                           :  1;
     unsigned      pch_active_ram1                           :  1;
     unsigned      pch_active_sf                             :  1;
     unsigned      pch_active_logic                          :  1;
     unsigned      pch_pwrd_up_ram0                          :  1;
     unsigned      pch_pwrd_up_ram1                          :  1;
     unsigned      pch_pwrd_up_sf                            :  1;
     unsigned      pch_pwrd_up_logic                         :  1;
     unsigned      pch_tocnt                                 : 10;
     unsigned      reserved0                                 :  6;
#endif
} ncp_syscon_pch_stat_r_xlf_t;

/*! @struct ncp_syscon_pch_wait_r_xlf_t
 *  @brief Fabric Power State Wait Register
 *  @details This register contains the delay values used to wait for RAM power state changes.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pch_wait_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wake_slp </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Number of clk_ref clocks to wait before leaving the
 *        SLP state
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wake_off </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of clk_ref clocks to wait before leaving the
 *        OFF state
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param setup_slp </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Number of clk_ref clocks to wait before entering the
 *        SLP state
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param setup_off </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of clk_ref clocks to wait before entering the
 *        OFF state
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pch_wait_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      wake_slp                                  :  8;
     unsigned      wake_off                                  :  8;
     unsigned      setup_slp                                 :  8;
     unsigned      setup_off                                 :  8;
#else    /* Little Endian */
     unsigned      setup_off                                 :  8;
     unsigned      setup_slp                                 :  8;
     unsigned      wake_off                                  :  8;
     unsigned      wake_slp                                  :  8;
#endif
} ncp_syscon_pch_wait_r_xlf_t;

/*! @struct ncp_syscon_pch_pwr_r_xlf_t
 *  @brief Fabric Power Sleep Mode Register
 *  @details This register contains the current state of the RAM power down signals and the sleep mode control.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_pch_pwr_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param slpmode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Sleep mode to use during dynamic retention (0:none,
 *        1:light, 2:deep).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enable_sf_ls </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> State of the enable light sleep for fabric snoop filter. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enable_sf_ds </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> State of the enable deep sleep for fabric snoop filter. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enable_sf_sd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> State of the enable shutdown for fabric snoop filter. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enable_l3ram1_ls </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> State of the enable light sleep for fabric RAMs (ways
 *        [15:8]).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enable_l3ram1_ds </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> State of the enable deep sleep for fabric RAMs (ways
 *        [15:8]).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enable_l3ram1_sd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> State of the enable shutdown for fabric RAMs (ways
 *        [15:8]
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enable_l3ram0_ls </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> State of the enable light sleep for fabric RAMs (ways
 *        [7:0]).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enable_l3ram0_ds </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> State of the enable deep sleep for fabric RAMs (ways
 *        [7:0]).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enable_l3ram0_sd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> State of the enable shutdown for fabric RAMs (ways
 *        [7:0]
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pch_pwr_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 18;
     unsigned      slpmode                                   :  2;
     unsigned      reserved1                                 :  1;
     unsigned      enable_sf_ls                              :  1;
     unsigned      enable_sf_ds                              :  1;
     unsigned      enable_sf_sd                              :  1;
     unsigned      reserved2                                 :  1;
     unsigned      enable_l3ram1_ls                          :  1;
     unsigned      enable_l3ram1_ds                          :  1;
     unsigned      enable_l3ram1_sd                          :  1;
     unsigned      reserved3                                 :  1;
     unsigned      enable_l3ram0_ls                          :  1;
     unsigned      enable_l3ram0_ds                          :  1;
     unsigned      enable_l3ram0_sd                          :  1;
#else    /* Little Endian */
     unsigned      enable_l3ram0_sd                          :  1;
     unsigned      enable_l3ram0_ds                          :  1;
     unsigned      enable_l3ram0_ls                          :  1;
     unsigned      reserved3                                 :  1;
     unsigned      enable_l3ram1_sd                          :  1;
     unsigned      enable_l3ram1_ds                          :  1;
     unsigned      enable_l3ram1_ls                          :  1;
     unsigned      reserved2                                 :  1;
     unsigned      enable_sf_sd                              :  1;
     unsigned      enable_sf_ds                              :  1;
     unsigned      enable_sf_ls                              :  1;
     unsigned      reserved1                                 :  1;
     unsigned      slpmode                                   :  2;
     unsigned      reserved0                                 : 18;
#endif
} ncp_syscon_pch_pwr_r_xlf_t;

/*! @struct ncp_syscon_qch_QACTIVE_r_xlf_t
 *  @brief CPU Cluster Clock Active Status Register
 *  @details This read-only status register contains the current state of the clock activity bits for each of the CPU clusters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_qch_QACTIVE_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cluster7_qactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> CPU Cluster 7 clock is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_qactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU Cluster 6 clock is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_qactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CPU Cluster 5 clock is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_qactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU Cluster 4 clock is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_qactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CPU Cluster 3 clock is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_qactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CPU Cluster 2 clock is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_qactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> CPU Cluster 1 clock is active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_qactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU Cluster 0 clock is active indication. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_qch_QACTIVE_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      cluster7_qactive                          :  1;
     unsigned      cluster6_qactive                          :  1;
     unsigned      cluster5_qactive                          :  1;
     unsigned      cluster4_qactive                          :  1;
     unsigned      cluster3_qactive                          :  1;
     unsigned      cluster2_qactive                          :  1;
     unsigned      cluster1_qactive                          :  1;
     unsigned      cluster0_qactive                          :  1;
#else    /* Little Endian */
     unsigned      cluster0_qactive                          :  1;
     unsigned      cluster1_qactive                          :  1;
     unsigned      cluster2_qactive                          :  1;
     unsigned      cluster3_qactive                          :  1;
     unsigned      cluster4_qactive                          :  1;
     unsigned      cluster5_qactive                          :  1;
     unsigned      cluster6_qactive                          :  1;
     unsigned      cluster7_qactive                          :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_qch_QACTIVE_r_xlf_t;

/*! @struct ncp_syscon_qch_ctl_r_xlf_t
 *  @brief Fabric Clock Control Register
 *  @details This register contains the control for the fabric clock.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_qch_ctl_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param qch_sm_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Fabric clock control state machine enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param no_clk_stop </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Don't actually turn off the clocks in the STOP state. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param qactive_thresh </td>
 *     <td width="20%" align="center"> 20 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of fabric clocks QACTIVE must be deasserted
 *        before a request to turn off the fabric clock is
 *        initiated by the clock control state machine (if enabled).
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_qch_ctl_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 10;
     unsigned      qch_sm_enable                             :  1;
     unsigned      no_clk_stop                               :  1;
     unsigned      qactive_thresh                            : 20;
#else    /* Little Endian */
     unsigned      qactive_thresh                            : 20;
     unsigned      no_clk_stop                               :  1;
     unsigned      qch_sm_enable                             :  1;
     unsigned      reserved0                                 : 10;
#endif
} ncp_syscon_qch_ctl_r_xlf_t;

/*! @struct ncp_syscon_qch_req_r_xlf_t
 *  @brief Fabric Clock Disable Request Register
 *  @details This register contains the bit (driven on QREQ_CLKCTL) to request turning off the fabric clock.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_qch_req_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param olyclken </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Fabric clock enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param qreq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Fabric clock disable request. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_qch_req_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 30;
     unsigned      olyclken                                  :  1;
     unsigned      qreq                                      :  1;
#else    /* Little Endian */
     unsigned      qreq                                      :  1;
     unsigned      olyclken                                  :  1;
     unsigned      reserved0                                 : 30;
#endif
} ncp_syscon_qch_req_r_xlf_t;

/*! @struct ncp_syscon_qch_stat_r_xlf_t
 *  @brief Fabric Clock Disable Status Register
 *  @details This register contains the sticky counter overflow indications and the read-only status of the
	fabric clock control state, response and status (QACTIVE_CLKCTL, QDENY_CLKCTL, QACCEPTn_CLKCTL).
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_qch_stat_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param qch_sm </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Fabric clock control state machine state. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param qactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Fabric clock active indication. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param qdeny </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Fabric clock disable request denied. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param qacceptn </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Fabric clock disable request accepted (active low). </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_qch_stat_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 25;
     unsigned      qch_sm                                    :  3;
     unsigned      reserved1                                 :  1;
     unsigned      qactive                                   :  1;
     unsigned      qdeny                                     :  1;
     unsigned      qacceptn                                  :  1;
#else    /* Little Endian */
     unsigned      qacceptn                                  :  1;
     unsigned      qdeny                                     :  1;
     unsigned      qactive                                   :  1;
     unsigned      reserved1                                 :  1;
     unsigned      qch_sm                                    :  3;
     unsigned      reserved0                                 : 25;
#endif
} ncp_syscon_qch_stat_r_xlf_t;

/*! @struct ncp_syscon_cnt_ctl_r_xlf_t
 *  @brief Counter Control Register
 *  @details This register contains the control for the counters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_cnt_ctl_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cnt_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Global counter enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fcnt_overflow </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> The free running counter overflowed. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gcnt2_overflow </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> The general purpose counter 2 overflowed. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gcnt1_overflow </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> The general purpose counter 1 overflowed. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gcnt0_overflow </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> The general purpose counter 0 overflowed. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gcnt2_sel </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> General purpose counter 2 increment select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gcnt1_sel </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> General purpose counter 1 increment select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gcnt0_sel </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> General purpose counter 0 increment select. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_cnt_ctl_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      cnt_enable                                :  1;
     unsigned      reserved0                                 :  3;
     unsigned      fcnt_overflow                             :  1;
     unsigned      gcnt2_overflow                            :  1;
     unsigned      gcnt1_overflow                            :  1;
     unsigned      gcnt0_overflow                            :  1;
     unsigned      gcnt2_sel                                 :  8;
     unsigned      gcnt1_sel                                 :  8;
     unsigned      gcnt0_sel                                 :  8;
#else    /* Little Endian */
     unsigned      gcnt0_sel                                 :  8;
     unsigned      gcnt1_sel                                 :  8;
     unsigned      gcnt2_sel                                 :  8;
     unsigned      gcnt0_overflow                            :  1;
     unsigned      gcnt1_overflow                            :  1;
     unsigned      gcnt2_overflow                            :  1;
     unsigned      fcnt_overflow                             :  1;
     unsigned      reserved0                                 :  3;
     unsigned      cnt_enable                                :  1;
#endif
} ncp_syscon_cnt_ctl_r_xlf_t;

/*! @struct ncp_syscon_qch_cnt_ctl_r_xlf_t
 *  @brief QCH Counter Control Register
 *  @details This register contains the control for the QCH counters.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_qch_cnt_ctl_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param qch_cnt_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Global counter enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param qch_fcnt_overflow </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> The free running counter overflowed. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param qch_gcnt1_overflow </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> The general purpose counter 1 overflowed. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param qch_gcnt0_overflow </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> The general purpose counter 0 overflowed. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param qch_gcnt1_sel </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> General purpose counter 1 increment select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param qch_gcnt0_sel </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> General purpose counter 0 increment select. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_qch_cnt_ctl_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      qch_cnt_enable                            :  1;
     unsigned      reserved0                                 : 18;
     unsigned      qch_fcnt_overflow                         :  1;
     unsigned      qch_gcnt1_overflow                        :  1;
     unsigned      qch_gcnt0_overflow                        :  1;
     unsigned      qch_gcnt1_sel                             :  5;
     unsigned      qch_gcnt0_sel                             :  5;
#else    /* Little Endian */
     unsigned      qch_gcnt0_sel                             :  5;
     unsigned      qch_gcnt1_sel                             :  5;
     unsigned      qch_gcnt0_overflow                        :  1;
     unsigned      qch_gcnt1_overflow                        :  1;
     unsigned      qch_fcnt_overflow                         :  1;
     unsigned      reserved0                                 : 18;
     unsigned      qch_cnt_enable                            :  1;
#endif
} ncp_syscon_qch_cnt_ctl_r_xlf_t;

/*! @struct ncp_syscon_bootmsgs_r_xlf_t
 *  @brief Boot Message Chip Reset Register
 *  @details This register is reset only by a pin or system reset and contains information for the boot process after a chip reset.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_bootmsgs_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param bootmsg </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Information for boot process. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_bootmsgs_r_xlf_t
 *
 */
 
typedef struct
{
     unsigned  int                   bootmsg;
} ncp_syscon_bootmsgs_r_xlf_t;

/*! @struct ncp_syscon_bootmsgp_r_xlf_t
 *  @brief Boot Message System Reset Register
 *  @details This register is reset only by a pin reset and contains information for the boot process after a system reset.
	Since this is a very critical register there is protection against an accidental writing of this register and the Critical
	Control Write Key register must first be setup to contain the correct key before any write will have an effect.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_bootmsgp_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param bootmsg </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Information for boot process. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_bootmsgp_r_xlf_t
 *
 */
 
typedef struct
{
     unsigned  int                   bootmsg;
} ncp_syscon_bootmsgp_r_xlf_t;

/*! @struct ncp_syscon_nmi_pulse_enable_a_r_xlf_t
 *  @brief NMI Pulse Enable Register
 *  @details This register is reset only by a system reset and controls the NMI pulse generation logic.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_nmi_pulse_enable_a_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param write_lock </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> If set, disables any further writes to this register
 *        until after a system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 25 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu_nmi_pulse_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> If set, enable CPU NMI pulse logic. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fes_nmi_pulse_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> If set, enable FES NMI pulse logic. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_nmi_pulse_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> If set, enable DSP Cluster 3's NMI pulse logic. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_nmi_pulse_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> If set, enable DSP Cluster 2's NMI pulse logic. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_nmi_pulse_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> If set, enable DSP Cluster 1's NMI pulse logic. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_nmi_pulse_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> If set, enable DSP Cluster 0's NMI pulse logic. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_nmi_pulse_enable_a_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      write_lock                                :  1;
     unsigned      reserved0                                 : 25;
     unsigned      cpu_nmi_pulse_enable                      :  1;
     unsigned      fes_nmi_pulse_enable                      :  1;
     unsigned      cluster3_nmi_pulse_enable                 :  1;
     unsigned      cluster2_nmi_pulse_enable                 :  1;
     unsigned      cluster1_nmi_pulse_enable                 :  1;
     unsigned      cluster0_nmi_pulse_enable                 :  1;
#else    /* Little Endian */
     unsigned      cluster0_nmi_pulse_enable                 :  1;
     unsigned      cluster1_nmi_pulse_enable                 :  1;
     unsigned      cluster2_nmi_pulse_enable                 :  1;
     unsigned      cluster3_nmi_pulse_enable                 :  1;
     unsigned      fes_nmi_pulse_enable                      :  1;
     unsigned      cpu_nmi_pulse_enable                      :  1;
     unsigned      reserved0                                 : 25;
     unsigned      write_lock                                :  1;
#endif
} ncp_syscon_nmi_pulse_enable_a_r_xlf_t;

/*! @struct ncp_syscon_nmi_pulse_enable_b_r_xlf_t
 *  @brief NMI Pulse Enable Register
 *  @details This register is reset only by a system reset and controls the NMI pulse generation logic.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_nmi_pulse_enable_b_r_xlf_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param write_lock </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> If set, disables any further writes to this register
 *        until after a system reset.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 25 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpu_nmi_pulse_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> If set, enable CPU NMI pulse logic. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fes_nmi_pulse_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> If set, enable FES NMI pulse logic. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_nmi_pulse_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> If set, enable DSP Cluster 3's NMI pulse logic. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_nmi_pulse_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> If set, enable DSP Cluster 2's NMI pulse logic. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_nmi_pulse_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> If set, enable DSP Cluster 1's NMI pulse logic. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_nmi_pulse_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> If set, enable DSP Cluster 0's NMI pulse logic. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_nmi_pulse_enable_b_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      write_lock                                :  1;
     unsigned      reserved0                                 : 25;
     unsigned      cpu_nmi_pulse_enable                      :  1;
     unsigned      fes_nmi_pulse_enable                      :  1;
     unsigned      cluster3_nmi_pulse_enable                 :  1;
     unsigned      cluster2_nmi_pulse_enable                 :  1;
     unsigned      cluster1_nmi_pulse_enable                 :  1;
     unsigned      cluster0_nmi_pulse_enable                 :  1;
#else    /* Little Endian */
     unsigned      cluster0_nmi_pulse_enable                 :  1;
     unsigned      cluster1_nmi_pulse_enable                 :  1;
     unsigned      cluster2_nmi_pulse_enable                 :  1;
     unsigned      cluster3_nmi_pulse_enable                 :  1;
     unsigned      fes_nmi_pulse_enable                      :  1;
     unsigned      cpu_nmi_pulse_enable                      :  1;
     unsigned      reserved0                                 : 25;
     unsigned      write_lock                                :  1;
#endif
} ncp_syscon_nmi_pulse_enable_b_r_xlf_t;

/*! @struct ncp_syscon_nmi_pulse_trigger_r_xlf_t
 *  @brief NMI Pulse Trigger Register
 *  @details Writing a 1 to a bit in this register generates a 64 clk_ref NMI pulse for the associated module if the
	corresponding NMI Pulse Enable register bit is also set.  Reads to this register always return 0.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_nmi_pulse_trigger_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param cpu_nmi_pulse_trigger </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Generate a CPU NMI pulse. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fes_nmi_pulse_trigger </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Generate a FES NMI pulse. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_nmi_pulse_trigger </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Generate a DSP Cluster 3 NMI pulse. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_nmi_pulse_trigger </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Generate a DSP Cluster 2 NMI pulse. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_nmi_pulse_trigger </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Generate a DSP Cluster 1 NMI pulse. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_nmi_pulse_trigger </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Generate a DSP Cluster 0 NMI pulse. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_nmi_pulse_trigger_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 26;
     unsigned      cpu_nmi_pulse_trigger                     :  1;
     unsigned      fes_nmi_pulse_trigger                     :  1;
     unsigned      cluster3_nmi_pulse_trigger                :  1;
     unsigned      cluster2_nmi_pulse_trigger                :  1;
     unsigned      cluster1_nmi_pulse_trigger                :  1;
     unsigned      cluster0_nmi_pulse_trigger                :  1;
#else    /* Little Endian */
     unsigned      cluster0_nmi_pulse_trigger                :  1;
     unsigned      cluster1_nmi_pulse_trigger                :  1;
     unsigned      cluster2_nmi_pulse_trigger                :  1;
     unsigned      cluster3_nmi_pulse_trigger                :  1;
     unsigned      fes_nmi_pulse_trigger                     :  1;
     unsigned      cpu_nmi_pulse_trigger                     :  1;
     unsigned      reserved0                                 : 26;
#endif
} ncp_syscon_nmi_pulse_trigger_r_xlf_t;

/*! @struct ncp_syscon_interrupt_status_r_xlf_t
 *  @brief Interrupt Status Register
 *  @details This register holds interrupt status
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_interrupt_status_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param gic_fatal_ecc </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> The GIC reported a fatal ECC error on its internal
 *        RAM. Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param jtag_debug_auth_limit </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> The number of failed jtag debug authentication attempts
 *        reached the allowed limit (4). Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param efuse_write_auth_limit </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> The number of failed efuse write authentication attempts
 *        reached the allowed limit (4). Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lsm_zero_after_reset_sent </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> The zeroization after reset request has been sent
 *        out to the LSM. Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pka_zero_after_reset_sent </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> The zeroization after reset request has been sent
 *        out to the PKA. Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zeroize_sent </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> The zeroization request has been sent out to all modules.
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sw_zeroize_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> A zeroization request was received from software.
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pin_zeroize_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> A zeroization request was received from the ZEROIZE_REQ
 *        pin. Status
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_interrupt_status_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      gic_fatal_ecc                             :  1;
     unsigned      jtag_debug_auth_limit                     :  1;
     unsigned      efuse_write_auth_limit                    :  1;
     unsigned      lsm_zero_after_reset_sent                 :  1;
     unsigned      pka_zero_after_reset_sent                 :  1;
     unsigned      zeroize_sent                              :  1;
     unsigned      sw_zeroize_req                            :  1;
     unsigned      pin_zeroize_req                           :  1;
#else    /* Little Endian */
     unsigned      pin_zeroize_req                           :  1;
     unsigned      sw_zeroize_req                            :  1;
     unsigned      zeroize_sent                              :  1;
     unsigned      pka_zero_after_reset_sent                 :  1;
     unsigned      lsm_zero_after_reset_sent                 :  1;
     unsigned      efuse_write_auth_limit                    :  1;
     unsigned      jtag_debug_auth_limit                     :  1;
     unsigned      gic_fatal_ecc                             :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_interrupt_status_r_xlf_t;

/*! @struct ncp_syscon_interrupt_en_r_xlf_t
 *  @brief Interrupt Enable Register
 *  @details This register enables interrupts
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_interrupt_en_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param gic_fatal_ecc </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> The GIC reported a fatal ECC error on its internal
 *        RAM. Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param jtag_debug_auth_limit </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> The number of failed jtag debug authentication attempts
 *        reached the allowed limit (4). Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param efuse_write_auth_limit </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> The number of failed efuse write authentication attempts
 *        reached the allowed limit (4). Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lsm_zero_after_reset_sent </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> The zeroization after reset request has been sent
 *        out to the LSM. Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pka_zero_after_reset_sent </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> The zeroization after reset request has been sent
 *        out to the PKA. Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zeroize_sent </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> The zeroization request has been sent out to all modules.
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sw_zeroize_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> A zeroization request was received from software.
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pin_zeroize_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> A zeroization request was received from the ZEROIZE_REQ
 *        pin. Enable
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_interrupt_en_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      gic_fatal_ecc                             :  1;
     unsigned      jtag_debug_auth_limit                     :  1;
     unsigned      efuse_write_auth_limit                    :  1;
     unsigned      lsm_zero_after_reset_sent                 :  1;
     unsigned      pka_zero_after_reset_sent                 :  1;
     unsigned      zeroize_sent                              :  1;
     unsigned      sw_zeroize_req                            :  1;
     unsigned      pin_zeroize_req                           :  1;
#else    /* Little Endian */
     unsigned      pin_zeroize_req                           :  1;
     unsigned      sw_zeroize_req                            :  1;
     unsigned      zeroize_sent                              :  1;
     unsigned      pka_zero_after_reset_sent                 :  1;
     unsigned      lsm_zero_after_reset_sent                 :  1;
     unsigned      efuse_write_auth_limit                    :  1;
     unsigned      jtag_debug_auth_limit                     :  1;
     unsigned      gic_fatal_ecc                             :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_interrupt_en_r_xlf_t;

/*! @struct ncp_syscon_interrupt_force_r_xlf_t
 *  @brief Interrupt Force Register
 *  @details This address is an alias for the Interrupt Status register
		that allows normal CFG writes (as opposed to the Clear-On-Write-One
		behavior if the Interrupt Status register address is used).  This
		allows CFG to set interrupt bits for testing purposes.  Reading this
		address returns the current value of the Interrupt Status Register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_syscon_interrupt_force_r_xlf_t\n
 *   </td>
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
 *     <td width="30%"> @param gic_fatal_ecc </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> The GIC reported a fatal ECC error on its internal
 *        RAM. Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param jtag_debug_auth_limit </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> The number of failed jtag debug authentication attempts
 *        reached the allowed limit (4). Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param efuse_write_auth_limit </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> The number of failed efuse write authentication attempts
 *        reached the allowed limit (4). Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lsm_zero_after_reset_sent </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> The zeroization after reset request has been sent
 *        out to the LSM. Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pka_zero_after_reset_sent </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> The zeroization after reset request has been sent
 *        out to the PKA. Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zeroize_sent </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> The zeroization request has been sent out to all modules.
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sw_zeroize_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> A zeroization request was received from software.
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pin_zeroize_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> A zeroization request was received from the ZEROIZE_REQ
 *        pin. Force
 *   </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_interrupt_force_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      gic_fatal_ecc                             :  1;
     unsigned      jtag_debug_auth_limit                     :  1;
     unsigned      efuse_write_auth_limit                    :  1;
     unsigned      lsm_zero_after_reset_sent                 :  1;
     unsigned      pka_zero_after_reset_sent                 :  1;
     unsigned      zeroize_sent                              :  1;
     unsigned      sw_zeroize_req                            :  1;
     unsigned      pin_zeroize_req                           :  1;
#else    /* Little Endian */
     unsigned      pin_zeroize_req                           :  1;
     unsigned      sw_zeroize_req                            :  1;
     unsigned      zeroize_sent                              :  1;
     unsigned      pka_zero_after_reset_sent                 :  1;
     unsigned      lsm_zero_after_reset_sent                 :  1;
     unsigned      efuse_write_auth_limit                    :  1;
     unsigned      jtag_debug_auth_limit                     :  1;
     unsigned      gic_fatal_ecc                             :  1;
     unsigned      reserved0                                 : 24;
#endif
} ncp_syscon_interrupt_force_r_xlf_t;

/*! @struct ncp_syscon_event_enb_r_xlf_t
 *  @brief Multi-word data structure
 *  <table width="70%" align="center">
 *   <tr>
 *     <td colspan="4" align="center">
 *       struct ncp_syscon_event_enb_r_xlf_t
 *     </td>
 *   </tr>
 *   <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *   </tr>
 *   <tr>
 *     <td width="30%"> @param cluster7_7_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> cluster7 enable event from cluster7. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster7_6_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> cluster7 enable event from cluster6. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster7_5_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> cluster7 enable event from cluster5. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster7_4_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> cluster7 enable event from cluster4. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster7_3_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> cluster7 enable event from cluster3. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster7_2_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> cluster7 enable event from cluster2. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster7_1_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> cluster7 enable event from cluster1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster7_0_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> cluster7 enable event from cluster0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_7_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> cluster6 enable event from cluster7. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_6_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> cluster6 enable event from cluster6. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_5_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> cluster6 enable event from cluster5. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_4_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> cluster6 enable event from cluster4. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_3_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> cluster6 enable event from cluster3. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_2_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> cluster6 enable event from cluster2. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_1_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> cluster6 enable event from cluster1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_0_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> cluster6 enable event from cluster0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_7_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> cluster5 enable event from cluster7. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_6_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> cluster5 enable event from cluster6. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_5_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> cluster5 enable event from cluster5. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_4_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> cluster5 enable event from cluster4. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_3_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> cluster5 enable event from cluster3. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_2_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> cluster5 enable event from cluster2. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_1_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> cluster5 enable event from cluster1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_0_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> cluster5 enable event from cluster0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_7_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> cluster4 enable event from cluster7. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_6_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> cluster4 enable event from cluster6. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_5_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> cluster4 enable event from cluster5. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_4_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> cluster4 enable event from cluster4. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_3_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> cluster4 enable event from cluster3. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_2_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> cluster4 enable event from cluster2. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_1_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> cluster4 enable event from cluster1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_0_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> cluster4 enable event from cluster0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_7_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> cluster3 enable event from cluster7. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_6_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> cluster3 enable event from cluster6. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_5_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> cluster3 enable event from cluster5. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_4_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> cluster3 enable event from cluster4. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_3_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> cluster3 enable event from cluster3. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_2_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> cluster3 enable event from cluster2. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_1_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> cluster3 enable event from cluster1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_0_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> cluster3 enable event from cluster0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_7_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> cluster2 enable event from cluster7. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_6_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> cluster2 enable event from cluster6. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_5_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> cluster2 enable event from cluster5. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_4_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> cluster2 enable event from cluster4. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_3_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> cluster2 enable event from cluster3. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_2_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> cluster2 enable event from cluster2. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_1_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> cluster2 enable event from cluster1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_0_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> cluster2 enable event from cluster0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_7_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> cluster1 enable event from cluster7. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_6_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> cluster1 enable event from cluster6. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_5_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> cluster1 enable event from cluster5. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_4_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> cluster1 enable event from cluster4. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_3_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> cluster1 enable event from cluster3. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_2_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> cluster1 enable event from cluster2. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_1_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> cluster1 enable event from cluster1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_0_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> cluster1 enable event from cluster0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_7_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> cluster0 enable event from cluster7. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_6_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> cluster0 enable event from cluster6. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_5_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> cluster0 enable event from cluster5. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_4_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> cluster0 enable event from cluster4. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_3_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> cluster0 enable event from cluster3. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_2_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> cluster0 enable event from cluster2. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_1_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> cluster0 enable event from cluster1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_0_event_enb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> cluster0 enable event from cluster0. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_event_enb_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
          /* word 0 */
     unsigned      cluster7_7_event_enb                      :  1;
     unsigned      cluster7_6_event_enb                      :  1;
     unsigned      cluster7_5_event_enb                      :  1;
     unsigned      cluster7_4_event_enb                      :  1;
     unsigned      cluster7_3_event_enb                      :  1;
     unsigned      cluster7_2_event_enb                      :  1;
     unsigned      cluster7_1_event_enb                      :  1;
     unsigned      cluster7_0_event_enb                      :  1;
     unsigned      cluster6_7_event_enb                      :  1;
     unsigned      cluster6_6_event_enb                      :  1;
     unsigned      cluster6_5_event_enb                      :  1;
     unsigned      cluster6_4_event_enb                      :  1;
     unsigned      cluster6_3_event_enb                      :  1;
     unsigned      cluster6_2_event_enb                      :  1;
     unsigned      cluster6_1_event_enb                      :  1;
     unsigned      cluster6_0_event_enb                      :  1;
     unsigned      cluster5_7_event_enb                      :  1;
     unsigned      cluster5_6_event_enb                      :  1;
     unsigned      cluster5_5_event_enb                      :  1;
     unsigned      cluster5_4_event_enb                      :  1;
     unsigned      cluster5_3_event_enb                      :  1;
     unsigned      cluster5_2_event_enb                      :  1;
     unsigned      cluster5_1_event_enb                      :  1;
     unsigned      cluster5_0_event_enb                      :  1;
     unsigned      cluster4_7_event_enb                      :  1;
     unsigned      cluster4_6_event_enb                      :  1;
     unsigned      cluster4_5_event_enb                      :  1;
     unsigned      cluster4_4_event_enb                      :  1;
     unsigned      cluster4_3_event_enb                      :  1;
     unsigned      cluster4_2_event_enb                      :  1;
     unsigned      cluster4_1_event_enb                      :  1;
     unsigned      cluster4_0_event_enb                      :  1;
          /* word 1 */
     unsigned      cluster3_7_event_enb                      :  1;
     unsigned      cluster3_6_event_enb                      :  1;
     unsigned      cluster3_5_event_enb                      :  1;
     unsigned      cluster3_4_event_enb                      :  1;
     unsigned      cluster3_3_event_enb                      :  1;
     unsigned      cluster3_2_event_enb                      :  1;
     unsigned      cluster3_1_event_enb                      :  1;
     unsigned      cluster3_0_event_enb                      :  1;
     unsigned      cluster2_7_event_enb                      :  1;
     unsigned      cluster2_6_event_enb                      :  1;
     unsigned      cluster2_5_event_enb                      :  1;
     unsigned      cluster2_4_event_enb                      :  1;
     unsigned      cluster2_3_event_enb                      :  1;
     unsigned      cluster2_2_event_enb                      :  1;
     unsigned      cluster2_1_event_enb                      :  1;
     unsigned      cluster2_0_event_enb                      :  1;
     unsigned      cluster1_7_event_enb                      :  1;
     unsigned      cluster1_6_event_enb                      :  1;
     unsigned      cluster1_5_event_enb                      :  1;
     unsigned      cluster1_4_event_enb                      :  1;
     unsigned      cluster1_3_event_enb                      :  1;
     unsigned      cluster1_2_event_enb                      :  1;
     unsigned      cluster1_1_event_enb                      :  1;
     unsigned      cluster1_0_event_enb                      :  1;
     unsigned      cluster0_7_event_enb                      :  1;
     unsigned      cluster0_6_event_enb                      :  1;
     unsigned      cluster0_5_event_enb                      :  1;
     unsigned      cluster0_4_event_enb                      :  1;
     unsigned      cluster0_3_event_enb                      :  1;
     unsigned      cluster0_2_event_enb                      :  1;
     unsigned      cluster0_1_event_enb                      :  1;
     unsigned      cluster0_0_event_enb                      :  1;
#else    /* Little Endian */
          /* word 0 */
     unsigned      cluster4_0_event_enb                      :  1;
     unsigned      cluster4_1_event_enb                      :  1;
     unsigned      cluster4_2_event_enb                      :  1;
     unsigned      cluster4_3_event_enb                      :  1;
     unsigned      cluster4_4_event_enb                      :  1;
     unsigned      cluster4_5_event_enb                      :  1;
     unsigned      cluster4_6_event_enb                      :  1;
     unsigned      cluster4_7_event_enb                      :  1;
     unsigned      cluster5_0_event_enb                      :  1;
     unsigned      cluster5_1_event_enb                      :  1;
     unsigned      cluster5_2_event_enb                      :  1;
     unsigned      cluster5_3_event_enb                      :  1;
     unsigned      cluster5_4_event_enb                      :  1;
     unsigned      cluster5_5_event_enb                      :  1;
     unsigned      cluster5_6_event_enb                      :  1;
     unsigned      cluster5_7_event_enb                      :  1;
     unsigned      cluster6_0_event_enb                      :  1;
     unsigned      cluster6_1_event_enb                      :  1;
     unsigned      cluster6_2_event_enb                      :  1;
     unsigned      cluster6_3_event_enb                      :  1;
     unsigned      cluster6_4_event_enb                      :  1;
     unsigned      cluster6_5_event_enb                      :  1;
     unsigned      cluster6_6_event_enb                      :  1;
     unsigned      cluster6_7_event_enb                      :  1;
     unsigned      cluster7_0_event_enb                      :  1;
     unsigned      cluster7_1_event_enb                      :  1;
     unsigned      cluster7_2_event_enb                      :  1;
     unsigned      cluster7_3_event_enb                      :  1;
     unsigned      cluster7_4_event_enb                      :  1;
     unsigned      cluster7_5_event_enb                      :  1;
     unsigned      cluster7_6_event_enb                      :  1;
     unsigned      cluster7_7_event_enb                      :  1;
          /* word 1 */
     unsigned      cluster0_0_event_enb                      :  1;
     unsigned      cluster0_1_event_enb                      :  1;
     unsigned      cluster0_2_event_enb                      :  1;
     unsigned      cluster0_3_event_enb                      :  1;
     unsigned      cluster0_4_event_enb                      :  1;
     unsigned      cluster0_5_event_enb                      :  1;
     unsigned      cluster0_6_event_enb                      :  1;
     unsigned      cluster0_7_event_enb                      :  1;
     unsigned      cluster1_0_event_enb                      :  1;
     unsigned      cluster1_1_event_enb                      :  1;
     unsigned      cluster1_2_event_enb                      :  1;
     unsigned      cluster1_3_event_enb                      :  1;
     unsigned      cluster1_4_event_enb                      :  1;
     unsigned      cluster1_5_event_enb                      :  1;
     unsigned      cluster1_6_event_enb                      :  1;
     unsigned      cluster1_7_event_enb                      :  1;
     unsigned      cluster2_0_event_enb                      :  1;
     unsigned      cluster2_1_event_enb                      :  1;
     unsigned      cluster2_2_event_enb                      :  1;
     unsigned      cluster2_3_event_enb                      :  1;
     unsigned      cluster2_4_event_enb                      :  1;
     unsigned      cluster2_5_event_enb                      :  1;
     unsigned      cluster2_6_event_enb                      :  1;
     unsigned      cluster2_7_event_enb                      :  1;
     unsigned      cluster3_0_event_enb                      :  1;
     unsigned      cluster3_1_event_enb                      :  1;
     unsigned      cluster3_2_event_enb                      :  1;
     unsigned      cluster3_3_event_enb                      :  1;
     unsigned      cluster3_4_event_enb                      :  1;
     unsigned      cluster3_5_event_enb                      :  1;
     unsigned      cluster3_6_event_enb                      :  1;
     unsigned      cluster3_7_event_enb                      :  1;
#endif
} ncp_syscon_event_enb_r_xlf_t;

/*! @struct ncp_syscon_pmu_sel_r_xlf_t
 *  @brief Multi-word data structure
 *  <table width="70%" align="center">
 *   <tr>
 *     <td colspan="4" align="center">
 *       struct ncp_syscon_pmu_sel_r_xlf_t
 *     </td>
 *   </tr>
 *   <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *   </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster7_pmu_sel </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> CPU cluster7 PMU data select </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster6_pmu_sel </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CPU cluster6 PMU data select </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_pmu_sel_5_2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 4 bits of cluster5_pmu_sel. CPU cluster5 PMU data
 *        select
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster5_pmu_sel_1_0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> 2 bits of cluster5_pmu_sel. CPU cluster5 PMU data
 *        select
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster4_pmu_sel </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> CPU cluster4 PMU data select </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster3_pmu_sel </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> CPU cluster3 PMU data select </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster2_pmu_sel </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> CPU cluster2 PMU data select </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster1_pmu_sel </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CPU cluster1 PMU data select </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cluster0_pmu_sel </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CPU cluster0 PMU data select </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_pmu_sel_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
          /* word 0 */
     unsigned      reserved0                                 : 16;
     unsigned      cluster7_pmu_sel                          :  6;
     unsigned      cluster6_pmu_sel                          :  6;
     unsigned      cluster5_pmu_sel_5_2                      :  4;
          /* word 1 */
     unsigned      cluster5_pmu_sel_1_0                      :  2;
     unsigned      cluster4_pmu_sel                          :  6;
     unsigned      cluster3_pmu_sel                          :  6;
     unsigned      cluster2_pmu_sel                          :  6;
     unsigned      cluster1_pmu_sel                          :  6;
     unsigned      cluster0_pmu_sel                          :  6;
#else    /* Little Endian */
          /* word 0 */
     unsigned      cluster5_pmu_sel_5_2                      :  4;
     unsigned      cluster6_pmu_sel                          :  6;
     unsigned      cluster7_pmu_sel                          :  6;
     unsigned      reserved0                                 : 16;
          /* word 1 */
     unsigned      cluster0_pmu_sel                          :  6;
     unsigned      cluster1_pmu_sel                          :  6;
     unsigned      cluster2_pmu_sel                          :  6;
     unsigned      cluster3_pmu_sel                          :  6;
     unsigned      cluster4_pmu_sel                          :  6;
     unsigned      cluster5_pmu_sel_1_0                      :  2;
#endif
} ncp_syscon_pmu_sel_r_xlf_t;

/*! @struct ncp_syscon_persist_r_xlf_t
 *  @brief Multi-word data structure
 *  <table width="70%" align="center">
 *   <tr>
 *     <td colspan="4" align="center">
 *       struct ncp_syscon_persist_r_xlf_t
 *     </td>
 *   </tr>
 *   <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *   </tr>
 *   <tr>
 *     <td width="30%"> @param persist_255_224 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 32 bits of persist. Persistent data. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param persist_223_192 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 32 bits of persist. Persistent data. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param persist_191_160 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 32 bits of persist. Persistent data. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param persist_159_128 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 32 bits of persist. Persistent data. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param persist_127_96 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 32 bits of persist. Persistent data. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param persist_95_64 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 32 bits of persist. Persistent data. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param persist_63_32 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 32 bits of persist. Persistent data. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param persist_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 32 bits of persist. Persistent data. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_persist_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
          /* word 0 */
     unsigned      persist_255_224                           : 32;
          /* word 1 */
     unsigned      persist_223_192                           : 32;
          /* word 2 */
     unsigned      persist_191_160                           : 32;
          /* word 3 */
     unsigned      persist_159_128                           : 32;
          /* word 4 */
     unsigned      persist_127_96                            : 32;
          /* word 5 */
     unsigned      persist_95_64                             : 32;
          /* word 6 */
     unsigned      persist_63_32                             : 32;
          /* word 7 */
     unsigned      persist_31_0                              : 32;
#else    /* Little Endian */
          /* word 0 */
     unsigned      persist_255_224                           : 32;
          /* word 1 */
     unsigned      persist_223_192                           : 32;
          /* word 2 */
     unsigned      persist_191_160                           : 32;
          /* word 3 */
     unsigned      persist_159_128                           : 32;
          /* word 4 */
     unsigned      persist_127_96                            : 32;
          /* word 5 */
     unsigned      persist_95_64                             : 32;
          /* word 6 */
     unsigned      persist_63_32                             : 32;
          /* word 7 */
     unsigned      persist_31_0                              : 32;
#endif
} ncp_syscon_persist_r_xlf_t;

/*! @struct ncp_syscon_reset_mod_r_xlf_t
 *  @brief Multi-word data structure
 *  <table width="70%" align="center">
 *   <tr>
 *     <td colspan="4" align="center">
 *       struct ncp_syscon_reset_mod_r_xlf_t
 *     </td>
 *   </tr>
 *   <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *   </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0_38_7 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 32 bits of reserved0. Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0_6_0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> 7 bits of reserved0. Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pcie_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> PCIe PHY reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param treemem_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Tree Memory Fabric reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tmgr_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> VPP Timer ManaGeR (TMGR) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param scnt_dist_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> System Counter Distribution logic reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmem_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Tree Memory Controller reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmem_phy_io_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Tree Memory PHY IO reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param spp_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> VPP Security Protocol Processor (SPP) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param smc3_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> System Memory Controller 3 (SM3) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param smem3_phy_io_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> System Memory 3 PHY IO reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param smc2_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> System Memory Controller 2 (SM2) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param smem2_phy_io_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> System Memory 2 PHY IO reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param smc1_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> System Memory Controller 1 (SM1) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param smem1_phy_io_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> System Memory 1 PHY IO reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param smc0_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> System Memory Controller 0 (SM0) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param smem0_phy_io_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> System Memory 0 PHY IO reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gic500_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Generic Interrupt Controller (GIC) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param elm3_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> System memory 3 Encryption Module (ELM3) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param elm2_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> System memory 2 Encryption Module (ELM2) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param elm1_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> System memory 1 Encryption Module (ELM1) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param elm0_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> System memory 0 Encryption Module (ELM0) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sed_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> VPP Stream Editor (SED) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rif1_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> VPP Radio Interface 1 (RIF1) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rif0_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> VPP Radio Interface 0 (RIF0) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param amxs_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Mixed signal component reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pic_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> VPP Packet Inspection and Checksum (PIC) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pab_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> VPP Packet Assembly Block (PAB) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pcx_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Packet Classification Switching (PCX) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pbm_tq_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Switch TQ Memory Manager (PBM_TQ) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pbm_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Switch Data Memory Manager (PBM) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tq_nic_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Switch TQ Nuevo InterConnect (NIC) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tq_pb_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Switch TQ Packet Buffer reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param data_nic_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Switch Data Nuevo InterConnect (NIC) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param data_pb_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Switch Data Packet Buffer reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ncapd_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> VPP NCAPD NLINK 13 (NCAPD_NLINKD) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ncapc_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> VPP NCAPD NLINK 12 (NCAPD_NLINKC) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ncapb_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> VPP NCAPD NLINK 11 (NCAPD_NLINKB) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ncapa_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> VPP NCAPD NLINK 10 (NCAPD_NLINKA) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ncap9_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> VPP NCAP NLINK 9 (NCAP_NLINK9) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ncap8_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> VPP NCAP NLINK 8 (NCAP_NLINK8) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ncap7_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> VPP NCAP NLINK 7 (NCAP_NLINK7) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ncap6_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> VPP NCAP NLINK 6 (NCAP_NLINK6) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ncap5_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> VPP NCAP NLINK 5 (NCAP_NLINK5) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ncap4_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> VPP NCAP NLINK 4 (NCAP_NLINK4) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ncap3_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> VPP NCAP NLINK 3 (NCAP_NLINK3) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ncap2_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> VPP NCAP NLINK 2 (NCAP_NLINK2) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ncap1_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> VPP NCAP NLINK 1 (NCAP_NLINK1) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ncap0_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> VPP NCAP NLINK 0 (NCAV3_NLINK0) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mtm_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> VPP Modular Traffic Manager (MTM) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mppy_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> VPP Modular Packet Processor (MPPY) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mme_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> VPP Memory Manager (MME) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param isb_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> VPP InterSystem Bridge (ISB) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eshim_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> VPP Ethernet Shim (ESHIM) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param erif0_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> VPP Ethernet Radio Interface 0 (ERIF0) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ioctl_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> I/O control reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fes_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> VPP Front End Subsystem (FES) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param erif1_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> VPP Ethernet Radio Interface 1 (ERIF1) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eioa_phy14_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> VPP EIOA PHY 14 reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eioa_phy13_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> VPP EIOA PHY 13 reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eioa_phy12_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> VPP EIOA PHY 12 reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eioa_phy11_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Switch EIOA PHY 11 reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eioa_phy10_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Switch EIOA PHY 10 reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eioa_phy9_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Switch EIOA PHY 9 reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eioa_phy8_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Switch EIOA PHY 8 reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eioa_phy7_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Switch EIOA PHY 7 reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eioa_phy6_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Switch EIOA PHY 6 reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eioa_phy5_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Switch EIOA PHY 5 reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eioa_phy4_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Switch EIOA PHY 4 reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eioa_phy3_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Switch EIOA PHY 3 reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eioa_phy2_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Switch EIOA PHY 2 reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eioa_phy1_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Switch EIOA PHY 1 reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eioa_phy0_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Switch EIOA PHY 0 reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dpi_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> VPP Deep Packet Inspection (DPI) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dec_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> VPP Turbo Decoder (DEC) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param nlink5_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Switch NLINK 5 (COWS2_NLINK5) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param nlink4_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Switch NLINK 4 (COWS2_NLINK4) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param nlink3_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Switch NLINK 3 (COWS2_NLINK3) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param nlink2_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Switch NLINK 2 (COWS2_NLINK2) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param nlink1_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Switch NLINK 1 (COWS2_NLINK1) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param nlink0_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Switch NLINK 0 (COWS2_NLINK0) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ccm_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> VPP Congestion Control Manager (CCM) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param isbs1_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Switch InterSystem Bridge 1 (ISBS1) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param isbs0_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Switch InterSystem Bridge 0 (ISBS0) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ccms_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Switch Congestion Control Manager (CCMS) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eioasm1_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Switch Ethernet I/O Adapter 3 (EIOASM1) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eioasm0_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Switch Ethernet I/O Adapter 2 (EIOASM0) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eioas1_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Switch Ethernet I/O Adapter 1 (EIOAS1) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eioas0_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Switch Ethernet I/O Adapter 0 (EIOAS0) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eioamh_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> VPP Ethernet I/O Adapter 1 (EIOAMH) reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eioam_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> VPP Ethernet I/O Adapter 0 (EIOAM) reset </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_reset_mod_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
          /* word 0 */
     unsigned      reserved0_38_7                            : 32;
          /* word 1 */
     unsigned      reserved0_6_0                             :  7;
     unsigned      pcie_rst                                  :  1;
     unsigned      treemem_rst                               :  1;
     unsigned      tmgr_rst                                  :  1;
     unsigned      scnt_dist_rst                             :  1;
     unsigned      cmem_rst                                  :  1;
     unsigned      cmem_phy_io_rst                           :  1;
     unsigned      spp_rst                                   :  1;
     unsigned      smc3_rst                                  :  1;
     unsigned      smem3_phy_io_rst                          :  1;
     unsigned      smc2_rst                                  :  1;
     unsigned      smem2_phy_io_rst                          :  1;
     unsigned      smc1_rst                                  :  1;
     unsigned      smem1_phy_io_rst                          :  1;
     unsigned      smc0_rst                                  :  1;
     unsigned      smem0_phy_io_rst                          :  1;
     unsigned      gic500_rst                                :  1;
     unsigned      elm3_rst                                  :  1;
     unsigned      elm2_rst                                  :  1;
     unsigned      elm1_rst                                  :  1;
     unsigned      elm0_rst                                  :  1;
     unsigned      sed_rst                                   :  1;
     unsigned      rif1_rst                                  :  1;
     unsigned      rif0_rst                                  :  1;
     unsigned      amxs_rst                                  :  1;
     unsigned      pic_rst                                   :  1;
          /* word 2 */
     unsigned      pab_rst                                   :  1;
     unsigned      pcx_rst                                   :  1;
     unsigned      pbm_tq_rst                                :  1;
     unsigned      pbm_rst                                   :  1;
     unsigned      tq_nic_rst                                :  1;
     unsigned      tq_pb_rst                                 :  1;
     unsigned      data_nic_rst                              :  1;
     unsigned      data_pb_rst                               :  1;
     unsigned      ncapd_rst                                 :  1;
     unsigned      ncapc_rst                                 :  1;
     unsigned      ncapb_rst                                 :  1;
     unsigned      ncapa_rst                                 :  1;
     unsigned      ncap9_rst                                 :  1;
     unsigned      ncap8_rst                                 :  1;
     unsigned      ncap7_rst                                 :  1;
     unsigned      ncap6_rst                                 :  1;
     unsigned      ncap5_rst                                 :  1;
     unsigned      ncap4_rst                                 :  1;
     unsigned      ncap3_rst                                 :  1;
     unsigned      ncap2_rst                                 :  1;
     unsigned      ncap1_rst                                 :  1;
     unsigned      ncap0_rst                                 :  1;
     unsigned      mtm_rst                                   :  1;
     unsigned      mppy_rst                                  :  1;
     unsigned      mme_rst                                   :  1;
     unsigned      isb_rst                                   :  1;
     unsigned      eshim_rst                                 :  1;
     unsigned      erif0_rst                                 :  1;
     unsigned      ioctl_rst                                 :  1;
     unsigned      fes_rst                                   :  1;
     unsigned      erif1_rst                                 :  1;
     unsigned      eioa_phy14_rst                            :  1;
          /* word 3 */
     unsigned      eioa_phy13_rst                            :  1;
     unsigned      eioa_phy12_rst                            :  1;
     unsigned      eioa_phy11_rst                            :  1;
     unsigned      eioa_phy10_rst                            :  1;
     unsigned      eioa_phy9_rst                             :  1;
     unsigned      eioa_phy8_rst                             :  1;
     unsigned      eioa_phy7_rst                             :  1;
     unsigned      eioa_phy6_rst                             :  1;
     unsigned      eioa_phy5_rst                             :  1;
     unsigned      eioa_phy4_rst                             :  1;
     unsigned      eioa_phy3_rst                             :  1;
     unsigned      eioa_phy2_rst                             :  1;
     unsigned      eioa_phy1_rst                             :  1;
     unsigned      eioa_phy0_rst                             :  1;
     unsigned      dpi_rst                                   :  1;
     unsigned      dec_rst                                   :  1;
     unsigned      nlink5_rst                                :  1;
     unsigned      nlink4_rst                                :  1;
     unsigned      nlink3_rst                                :  1;
     unsigned      nlink2_rst                                :  1;
     unsigned      nlink1_rst                                :  1;
     unsigned      nlink0_rst                                :  1;
     unsigned      ccm_rst                                   :  1;
     unsigned      isbs1_rst                                 :  1;
     unsigned      isbs0_rst                                 :  1;
     unsigned      ccms_rst                                  :  1;
     unsigned      eioasm1_rst                               :  1;
     unsigned      eioasm0_rst                               :  1;
     unsigned      eioas1_rst                                :  1;
     unsigned      eioas0_rst                                :  1;
     unsigned      eioamh_rst                                :  1;
     unsigned      eioam_rst                                 :  1;
#else    /* Little Endian */
          /* word 0 */
     unsigned      reserved0_38_7                            : 32;
          /* word 1 */
     unsigned      pic_rst                                   :  1;
     unsigned      amxs_rst                                  :  1;
     unsigned      rif0_rst                                  :  1;
     unsigned      rif1_rst                                  :  1;
     unsigned      sed_rst                                   :  1;
     unsigned      elm0_rst                                  :  1;
     unsigned      elm1_rst                                  :  1;
     unsigned      elm2_rst                                  :  1;
     unsigned      elm3_rst                                  :  1;
     unsigned      gic500_rst                                :  1;
     unsigned      smem0_phy_io_rst                          :  1;
     unsigned      smc0_rst                                  :  1;
     unsigned      smem1_phy_io_rst                          :  1;
     unsigned      smc1_rst                                  :  1;
     unsigned      smem2_phy_io_rst                          :  1;
     unsigned      smc2_rst                                  :  1;
     unsigned      smem3_phy_io_rst                          :  1;
     unsigned      smc3_rst                                  :  1;
     unsigned      spp_rst                                   :  1;
     unsigned      cmem_phy_io_rst                           :  1;
     unsigned      cmem_rst                                  :  1;
     unsigned      scnt_dist_rst                             :  1;
     unsigned      tmgr_rst                                  :  1;
     unsigned      treemem_rst                               :  1;
     unsigned      pcie_rst                                  :  1;
     unsigned      reserved0_6_0                             :  7;
          /* word 2 */
     unsigned      eioa_phy14_rst                            :  1;
     unsigned      erif1_rst                                 :  1;
     unsigned      fes_rst                                   :  1;
     unsigned      ioctl_rst                                 :  1;
     unsigned      erif0_rst                                 :  1;
     unsigned      eshim_rst                                 :  1;
     unsigned      isb_rst                                   :  1;
     unsigned      mme_rst                                   :  1;
     unsigned      mppy_rst                                  :  1;
     unsigned      mtm_rst                                   :  1;
     unsigned      ncap0_rst                                 :  1;
     unsigned      ncap1_rst                                 :  1;
     unsigned      ncap2_rst                                 :  1;
     unsigned      ncap3_rst                                 :  1;
     unsigned      ncap4_rst                                 :  1;
     unsigned      ncap5_rst                                 :  1;
     unsigned      ncap6_rst                                 :  1;
     unsigned      ncap7_rst                                 :  1;
     unsigned      ncap8_rst                                 :  1;
     unsigned      ncap9_rst                                 :  1;
     unsigned      ncapa_rst                                 :  1;
     unsigned      ncapb_rst                                 :  1;
     unsigned      ncapc_rst                                 :  1;
     unsigned      ncapd_rst                                 :  1;
     unsigned      data_pb_rst                               :  1;
     unsigned      data_nic_rst                              :  1;
     unsigned      tq_pb_rst                                 :  1;
     unsigned      tq_nic_rst                                :  1;
     unsigned      pbm_rst                                   :  1;
     unsigned      pbm_tq_rst                                :  1;
     unsigned      pcx_rst                                   :  1;
     unsigned      pab_rst                                   :  1;
          /* word 3 */
     unsigned      eioam_rst                                 :  1;
     unsigned      eioamh_rst                                :  1;
     unsigned      eioas0_rst                                :  1;
     unsigned      eioas1_rst                                :  1;
     unsigned      eioasm0_rst                               :  1;
     unsigned      eioasm1_rst                               :  1;
     unsigned      ccms_rst                                  :  1;
     unsigned      isbs0_rst                                 :  1;
     unsigned      isbs1_rst                                 :  1;
     unsigned      ccm_rst                                   :  1;
     unsigned      nlink0_rst                                :  1;
     unsigned      nlink1_rst                                :  1;
     unsigned      nlink2_rst                                :  1;
     unsigned      nlink3_rst                                :  1;
     unsigned      nlink4_rst                                :  1;
     unsigned      nlink5_rst                                :  1;
     unsigned      dec_rst                                   :  1;
     unsigned      dpi_rst                                   :  1;
     unsigned      eioa_phy0_rst                             :  1;
     unsigned      eioa_phy1_rst                             :  1;
     unsigned      eioa_phy2_rst                             :  1;
     unsigned      eioa_phy3_rst                             :  1;
     unsigned      eioa_phy4_rst                             :  1;
     unsigned      eioa_phy5_rst                             :  1;
     unsigned      eioa_phy6_rst                             :  1;
     unsigned      eioa_phy7_rst                             :  1;
     unsigned      eioa_phy8_rst                             :  1;
     unsigned      eioa_phy9_rst                             :  1;
     unsigned      eioa_phy10_rst                            :  1;
     unsigned      eioa_phy11_rst                            :  1;
     unsigned      eioa_phy12_rst                            :  1;
     unsigned      eioa_phy13_rst                            :  1;
#endif
} ncp_syscon_reset_mod_r_xlf_t;

/*! @struct ncp_syscon_reset_axis_r_xlf_t
 *  @brief Multi-word data structure
 *  <table width="70%" align="center">
 *   <tr>
 *     <td colspan="4" align="center">
 *       struct ncp_syscon_reset_axis_r_xlf_t
 *     </td>
 *   </tr>
 *   <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *   </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0_63_32 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 32 bits of reserved0. Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 32 bits of reserved0. Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param usb1_phy_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> USB1 PHY reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param usb1_phy_fab_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> USB1 PHY Fabric reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param usb0_phy_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> USB0 PHY reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param usb0_phy_fab_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> USB0 PHY Fabric reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ccn512_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> CCN512 AXI reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param usb1_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> USB1 Controller reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param nrcp_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> NRCP reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpm_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Critical Path Monitor reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param usb1_fabric_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> USB1 Fabric reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param usb0_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> USB0 Controller reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param usb0_fabric_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> USB0 Fabric reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param uart_2_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> UART[2] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param uart_1_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> UART[1] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param uart_0_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> UART[0] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param timer_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Timers reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ssp2_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> SSP[2] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ssp1_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> SSP[1] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ssp0_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> SSP[0] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param smb_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> SMB reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mtc_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> MTC reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mdio1_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> MDIO[1] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mdio0_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> MDIO[0] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param i2c_11_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> I2C[11] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param i2c_10_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> I2C[10] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param i2c_9_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> I2C[9] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param i2c_8_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> I2C[8] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param i2c_7_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> I2C[7] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param i2c_6_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> I2C[6] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param i2c_5_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> I2C[5] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param i2c_4_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> I2C[4] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param i2c_3_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> I2C[3] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param i2c_2_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> I2C[2] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param i2c_1_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> I2C[1] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param i2c_0_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> I2C[0] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gpio_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> GPIO reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gemac_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> GEMAC reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fc_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> FC reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param periph_fabric_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Periph Fabric reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eac_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> EAC reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi_pci_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> AXIS PCI reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pci_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> AXIS PCI core reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pci_fabric_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> AXIS PCI Fabric reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trng_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> TRNG reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sbb_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> SBB reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pka__rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> PKA reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lsm_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> LSM reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param jtag2axi_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> JTAG2AXI reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gpdma_1_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> GPDMA[1] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gpdma_0_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> GPDMA[0] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gic490_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> GIC490 reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mmap_fabric_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Memory Map Fabric reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2ser12_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> AXI2SER[11] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2ser11_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> AXI2SER[10] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2ser10_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> AXI2SER[9] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2ser9_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> AXI2SER[8] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2ser8_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> AXI2SER[7] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2ser6_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> AXI2SER[6] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2ser5_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> AXI2SER[5] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2ser4_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> AXI2SER[4] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2ser3_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> AXI2SER[3] reset. Note that this register bit is not
 *        wired directly to the reset signal itself. The act
 *        of  writing a 1 to this bit kicks off a sequence
 *        that waits 112 clk_per clocks and then asserts the
 *        reset for  16 clk_per clocks before deasserting
 *        it. This is treated specially because AXI2SER[3] is
 *        the bridge to  the system control logic containing
 *        this register and, without this behavior, we would
 *        not be able to write  this bit back to a zero. Software
 *        also needs to ensure there has been enough time for
 *        the reset sequence  to complete after writing this
 *        bit to a 1 before attempting another access through
 *        AXI2SER[3]. Software  is not required to write this
 *        bit back to a 0 and the bit is not reset by the AXI2SER[3]
 *        reset sequence.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2ser2_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> AXI2SER[2] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2ser1_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> AXI2SER[1] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi2ser0_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> AXI2SER[0] reset </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param awlock_rst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> AWLOCK reset </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_reset_axis_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
          /* word 0 */
     unsigned      reserved0_63_32                           : 32;
          /* word 1 */
     unsigned      reserved0_31_0                            : 32;
          /* word 2 */
     unsigned      usb1_phy_rst                              :  1;
     unsigned      usb1_phy_fab_rst                          :  1;
     unsigned      usb0_phy_rst                              :  1;
     unsigned      usb0_phy_fab_rst                          :  1;
     unsigned      ccn512_rst                                :  1;
     unsigned      usb1_rst                                  :  1;
     unsigned      nrcp_rst                                  :  1;
     unsigned      cpm_rst                                   :  1;
     unsigned      usb1_fabric_rst                           :  1;
     unsigned      usb0_rst                                  :  1;
     unsigned      usb0_fabric_rst                           :  1;
     unsigned      uart_2_rst                                :  1;
     unsigned      uart_1_rst                                :  1;
     unsigned      uart_0_rst                                :  1;
     unsigned      timer_rst                                 :  1;
     unsigned      ssp2_rst                                  :  1;
     unsigned      ssp1_rst                                  :  1;
     unsigned      ssp0_rst                                  :  1;
     unsigned      smb_rst                                   :  1;
     unsigned      mtc_rst                                   :  1;
     unsigned      mdio1_rst                                 :  1;
     unsigned      mdio0_rst                                 :  1;
     unsigned      i2c_11_rst                                :  1;
     unsigned      i2c_10_rst                                :  1;
     unsigned      i2c_9_rst                                 :  1;
     unsigned      i2c_8_rst                                 :  1;
     unsigned      i2c_7_rst                                 :  1;
     unsigned      i2c_6_rst                                 :  1;
     unsigned      i2c_5_rst                                 :  1;
     unsigned      i2c_4_rst                                 :  1;
     unsigned      i2c_3_rst                                 :  1;
     unsigned      i2c_2_rst                                 :  1;
          /* word 3 */
     unsigned      i2c_1_rst                                 :  1;
     unsigned      i2c_0_rst                                 :  1;
     unsigned      gpio_rst                                  :  1;
     unsigned      gemac_rst                                 :  1;
     unsigned      fc_rst                                    :  1;
     unsigned      periph_fabric_rst                         :  1;
     unsigned      eac_rst                                   :  1;
     unsigned      axi_pci_rst                               :  1;
     unsigned      pci_rst                                   :  1;
     unsigned      pci_fabric_rst                            :  1;
     unsigned      trng_rst                                  :  1;
     unsigned      sbb_rst                                   :  1;
     unsigned      pka__rst                                  :  1;
     unsigned      lsm_rst                                   :  1;
     unsigned      jtag2axi_rst                              :  1;
     unsigned      gpdma_1_rst                               :  1;
     unsigned      gpdma_0_rst                               :  1;
     unsigned      gic490_rst                                :  1;
     unsigned      mmap_fabric_rst                           :  1;
     unsigned      axi2ser12_rst                             :  1;
     unsigned      axi2ser11_rst                             :  1;
     unsigned      axi2ser10_rst                             :  1;
     unsigned      axi2ser9_rst                              :  1;
     unsigned      axi2ser8_rst                              :  1;
     unsigned      axi2ser6_rst                              :  1;
     unsigned      axi2ser5_rst                              :  1;
     unsigned      axi2ser4_rst                              :  1;
     unsigned      axi2ser3_rst                              :  1;
     unsigned      axi2ser2_rst                              :  1;
     unsigned      axi2ser1_rst                              :  1;
     unsigned      axi2ser0_rst                              :  1;
     unsigned      awlock_rst                                :  1;
#else    /* Little Endian */
          /* word 0 */
     unsigned      reserved0_63_32                           : 32;
          /* word 1 */
     unsigned      reserved0_31_0                            : 32;
          /* word 2 */
     unsigned      i2c_2_rst                                 :  1;
     unsigned      i2c_3_rst                                 :  1;
     unsigned      i2c_4_rst                                 :  1;
     unsigned      i2c_5_rst                                 :  1;
     unsigned      i2c_6_rst                                 :  1;
     unsigned      i2c_7_rst                                 :  1;
     unsigned      i2c_8_rst                                 :  1;
     unsigned      i2c_9_rst                                 :  1;
     unsigned      i2c_10_rst                                :  1;
     unsigned      i2c_11_rst                                :  1;
     unsigned      mdio0_rst                                 :  1;
     unsigned      mdio1_rst                                 :  1;
     unsigned      mtc_rst                                   :  1;
     unsigned      smb_rst                                   :  1;
     unsigned      ssp0_rst                                  :  1;
     unsigned      ssp1_rst                                  :  1;
     unsigned      ssp2_rst                                  :  1;
     unsigned      timer_rst                                 :  1;
     unsigned      uart_0_rst                                :  1;
     unsigned      uart_1_rst                                :  1;
     unsigned      uart_2_rst                                :  1;
     unsigned      usb0_fabric_rst                           :  1;
     unsigned      usb0_rst                                  :  1;
     unsigned      usb1_fabric_rst                           :  1;
     unsigned      cpm_rst                                   :  1;
     unsigned      nrcp_rst                                  :  1;
     unsigned      usb1_rst                                  :  1;
     unsigned      ccn512_rst                                :  1;
     unsigned      usb0_phy_fab_rst                          :  1;
     unsigned      usb0_phy_rst                              :  1;
     unsigned      usb1_phy_fab_rst                          :  1;
     unsigned      usb1_phy_rst                              :  1;
          /* word 3 */
     unsigned      awlock_rst                                :  1;
     unsigned      axi2ser0_rst                              :  1;
     unsigned      axi2ser1_rst                              :  1;
     unsigned      axi2ser2_rst                              :  1;
     unsigned      axi2ser3_rst                              :  1;
     unsigned      axi2ser4_rst                              :  1;
     unsigned      axi2ser5_rst                              :  1;
     unsigned      axi2ser6_rst                              :  1;
     unsigned      axi2ser8_rst                              :  1;
     unsigned      axi2ser9_rst                              :  1;
     unsigned      axi2ser10_rst                             :  1;
     unsigned      axi2ser11_rst                             :  1;
     unsigned      axi2ser12_rst                             :  1;
     unsigned      mmap_fabric_rst                           :  1;
     unsigned      gic490_rst                                :  1;
     unsigned      gpdma_0_rst                               :  1;
     unsigned      gpdma_1_rst                               :  1;
     unsigned      jtag2axi_rst                              :  1;
     unsigned      lsm_rst                                   :  1;
     unsigned      pka__rst                                  :  1;
     unsigned      sbb_rst                                   :  1;
     unsigned      trng_rst                                  :  1;
     unsigned      pci_fabric_rst                            :  1;
     unsigned      pci_rst                                   :  1;
     unsigned      axi_pci_rst                               :  1;
     unsigned      eac_rst                                   :  1;
     unsigned      periph_fabric_rst                         :  1;
     unsigned      fc_rst                                    :  1;
     unsigned      gemac_rst                                 :  1;
     unsigned      gpio_rst                                  :  1;
     unsigned      i2c_0_rst                                 :  1;
     unsigned      i2c_1_rst                                 :  1;
#endif
} ncp_syscon_reset_axis_r_xlf_t;

/*! @struct ncp_syscon_fcnt_r_xlf_t
 *  @brief Multi-word data structure
 *  <table width="70%" align="center">
 *   <tr>
 *     <td colspan="4" align="center">
 *       struct ncp_syscon_fcnt_r_xlf_t
 *     </td>
 *   </tr>
 *   <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *   </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fcnt_47_32 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 16 bits of fcnt. Number of reference clocks. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fcnt_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 32 bits of fcnt. Number of reference clocks. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_fcnt_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
          /* word 0 */
     unsigned      reserved0                                 : 16;
     unsigned      fcnt_47_32                                : 16;
          /* word 1 */
     unsigned      fcnt_31_0                                 : 32;
#else    /* Little Endian */
          /* word 0 */
     unsigned      fcnt_47_32                                : 16;
     unsigned      reserved0                                 : 16;
          /* word 1 */
     unsigned      fcnt_31_0                                 : 32;
#endif
} ncp_syscon_fcnt_r_xlf_t;

/*! @struct ncp_syscon_gcnt_r_xlf_t
 *  @brief Multi-word data structure
 *  <table width="70%" align="center">
 *   <tr>
 *     <td colspan="4" align="center">
 *       struct ncp_syscon_gcnt_r_xlf_t
 *     </td>
 *   </tr>
 *   <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *   </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gcnt_47_32 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 16 bits of gcnt. Number of events. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gcnt_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 32 bits of gcnt. Number of events. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_gcnt_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
          /* word 0 */
     unsigned      reserved0                                 : 16;
     unsigned      gcnt_47_32                                : 16;
          /* word 1 */
     unsigned      gcnt_31_0                                 : 32;
#else    /* Little Endian */
          /* word 0 */
     unsigned      gcnt_47_32                                : 16;
     unsigned      reserved0                                 : 16;
          /* word 1 */
     unsigned      gcnt_31_0                                 : 32;
#endif
} ncp_syscon_gcnt_r_xlf_t;

/*! @struct ncp_syscon_qch_fcnt_r_xlf_t
 *  @brief Multi-word data structure
 *  <table width="70%" align="center">
 *   <tr>
 *     <td colspan="4" align="center">
 *       struct ncp_syscon_qch_fcnt_r_xlf_t
 *     </td>
 *   </tr>
 *   <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *   </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param qch_fcnt_47_32 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 16 bits of qch_fcnt. Number of fabric clocks. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param qch_fcnt_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 32 bits of qch_fcnt. Number of fabric clocks. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_qch_fcnt_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
          /* word 0 */
     unsigned      reserved0                                 : 16;
     unsigned      qch_fcnt_47_32                            : 16;
          /* word 1 */
     unsigned      qch_fcnt_31_0                             : 32;
#else    /* Little Endian */
          /* word 0 */
     unsigned      qch_fcnt_47_32                            : 16;
     unsigned      reserved0                                 : 16;
          /* word 1 */
     unsigned      qch_fcnt_31_0                             : 32;
#endif
} ncp_syscon_qch_fcnt_r_xlf_t;

/*! @struct ncp_syscon_qch_gcnt_r_xlf_t
 *  @brief Multi-word data structure
 *  <table width="70%" align="center">
 *   <tr>
 *     <td colspan="4" align="center">
 *       struct ncp_syscon_qch_gcnt_r_xlf_t
 *     </td>
 *   </tr>
 *   <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *   </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param qch_gcnt_47_32 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 16 bits of qch_gcnt. Number of events. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param qch_gcnt_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> 32 bits of qch_gcnt. Number of events. </td>
 * </tr>
 * </table>
 * Applies to: xlf --> ncp_syscon_qch_gcnt_r_xlf_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
          /* word 0 */
     unsigned      reserved0                                 : 16;
     unsigned      qch_gcnt_47_32                            : 16;
          /* word 1 */
     unsigned      qch_gcnt_31_0                             : 32;
#else    /* Little Endian */
          /* word 0 */
     unsigned      qch_gcnt_47_32                            : 16;
     unsigned      reserved0                                 : 16;
          /* word 1 */
     unsigned      qch_gcnt_31_0                             : 32;
#endif
} ncp_syscon_qch_gcnt_r_xlf_t;

#ifdef __cplusplus
}
#endif

#endif /* _NCP_SYSCON_XLF_REGS_H_ */
