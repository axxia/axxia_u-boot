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

#ifndef _NCP_PHY_REGS_2500_H_
#define _NCP_PHY_REGS_2500_H_

#ifdef __cplusplus
extern "C" {
#endif

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DPCONFIG0_BLx_r_t
 *  @brief CFG_SYSMEM_PHY_DPCONFIG0_BLx
 *  @details This register provides static configuration for individual DP hard macros.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DPCONFIG0_BLx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3116 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param autogtupdmode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Auto Gate Update Mode: 0 - default, auto updates are
 *        applied to all rank delay settings. After a read burst
 *        the phase of the gate is compared to read DQS. An
 *        adjustment +/- one tap is then applied to the all
 *        rank gate delays setting; 1 - auto updates are applied
 *        on a per rank basis. After a read burst the phase
 *        of the gate is compared to read DQS and saved along
 *        with the rank setting for that particular burst. An
 *        adjustment +/- one tap is then applied to the individual
 *        rank gate delays setting.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disautogtupd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Disable Auto Gate Update: 0 - default, no effect.
 *        Gate delays are automatically adjusted by comparing
 *        the phase of the gate and DQS signals; 1 - disables
 *        the automatic gate delay updates.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ovrdynodt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Override Dynamic ODT: 0 - default dynamic ODT, turn
 *        on PHY I/O ODT when read data is being received. This
 *        is controlled by the read DQS gate signal. For dynamic
 *        ODT, PHY_CONFIG2[3] (ODT_OFF) must also be set to
 *        0; 1 - Force PHY I/O ODT to be always on. (takes precedence
 *        over PHY_CONFIG2[3] ODT_OFF)
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd12 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param twobeatburst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Two Beat Burst: Legacy DDR1, 2 beat burst mode. 0
 *        - less than 4 beats per burst is not permitted (default
 *        mode); 1 - two beats per burst allowed for DDR1 operation.
 *        NOTES: 1) This mode affects the accuracy of DQS gate
 *        tracking and is only recommended for the slow operating
 *        frequency of DDR1. 2) Two beat burst mode can only
 *        be used when all rank delay settings are identical.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dyniorcvrpwr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Dynamic IO Receiver Power (LPR): 0 - LPR feed through
 *        to IO has control of the receiver power; 1 - IO receiver
 *        power controlled by DR_GATING_IN pin. Receiver power
 *        is applied at least 1.5 clk1x cycles before the read
 *        burst pre-amble and is switched off after the last
 *        negative edge data of the burst has been captured.
 *        During scan mode or gate training this register does
 *        not affect IO receiver power, the LPR feed through
 *        has direct control (0=power on). During bist mode
 *        and not scan mode the IO receiver power is forced
 *        on.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bypdlycells </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Bypass delay cell logic: TEST USE ONLY. Set to 1 for
 *        direct access to all delay cell settings. This bit
 *        will bypass all safe rank switching and VT update
 *        logic.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd83 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dw_phs_align </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> DW PHASE ALIGN: 0 - 90 degree alignment of DQS out
 *        (and DM out in X4 mode) to DQ out transitions; 1 -
 *        0 degree alignment of DQS out (and DM out in x4 mode)
 *        to DQ out transitions.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dw_x4mode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> DW_X4MODE: 0 - write X8 mode, (DM out is data mask);
 *        1 - write X4 mode, (DM out is DQ[7:4] write strobe).
 *        May also be selected via static control pin. DM can
 *        be used as a read data strobe and is controlled via
 *        the static control pins RANK_RX_MODE and the write
 *        rank selection.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_DPCONFIG0_BLx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3116                                  : 16;
     unsigned      autogtupdmode                             :  1;
     unsigned      disautogtupd                              :  1;
     unsigned      ovrdynodt                                 :  1;
     unsigned      rsvd12                                    :  1;
     unsigned      twobeatburst                              :  1;
     unsigned      dyniorcvrpwr                              :  1;
     unsigned      bypdlycells                               :  1;
     unsigned      rsvd83                                    :  6;
     unsigned      dw_phs_align                              :  1;
     unsigned      dw_x4mode                                 :  1;
     unsigned      rsvd0                                     :  1;
#else    /* Little Endian */
     unsigned      rsvd0                                     :  1;
     unsigned      dw_x4mode                                 :  1;
     unsigned      dw_phs_align                              :  1;
     unsigned      rsvd83                                    :  6;
     unsigned      bypdlycells                               :  1;
     unsigned      dyniorcvrpwr                              :  1;
     unsigned      twobeatburst                              :  1;
     unsigned      rsvd12                                    :  1;
     unsigned      ovrdynodt                                 :  1;
     unsigned      disautogtupd                              :  1;
     unsigned      autogtupdmode                             :  1;
     unsigned      rsvd3116                                  : 16;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DPCONFIG0_BLx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DPCONFIG2_BLx_r_t
 *  @brief CFG_SYSMEM_PHY_DPCONFIG2_BLx
 *  @details This register provides additional configuration for individual DP hard macros.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DPCONFIG2_BLx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3113 </td>
 *     <td width="20%" align="center"> 19 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gatevtwrap </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Gate VT Wrap: 0 - Normal operation VT buffer required
 *        in the GATE delay setting; 1 - Not supported.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param granularity </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Granularity: DQS and spare delay cell granularity.
 *        0 - The DQS and spare delay cells have a granularity
 *        of 512 (9 bits); 1 - The DQS and spare delay cells
 *        have a granularity of 1024 (10 bits).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enardpath </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Enable Read Path: Set HIGH to enable forwarding of
 *        read DQS signal and DQS gating logic. This register
 *        bit resets to 0 at power up for DQS delay cell initialization.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clrgate </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Set HIGH to clear DQS gating logic. This bit is write
 *        only and it is self-cleared after write. This register
 *        bit is powered up as '1' and then self clears to '0'.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gtlvlcfg </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Gate Training: Set HIGH to configure the DP hardmacro
 *        in DQS gate training mode. This bit must be set to
 *        HIGH prior to performing manual DQS gate training
 *        process.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvlcfg </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> WR Leveling Config: 1 - DP hardmacro is in write leveling
 *        mode. This bit must be set to HIGH prior to performing
 *        write leveling training process.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param applydat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Apply Data: 0 - reference clks with zero phase shift
 *        are applied to data paths; 1 - reference clks with
 *        90 degree phase shift are applied to data paths. This
 *        bit determines which reference clk is applied to the
 *        data input of the spare or read capture flops when
 *        bit 2 or 3 is set to 1.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param applyclk </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Apply Clock: 0 - reference clks with zero phase shift
 *        are applied to clk paths; 1 - reference clks with
 *        90 degree phase shift are applied to clk paths. This
 *        bit determines which reference clk is applied to the
 *        clk input of the spare or read capture flops when
 *        bit 2 or 3 is set to 1.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param refclk2sprff </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Mux Spare FF: 1 - mux in reference clock to spare
 *        flop.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param refclk2dqff </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Mux DQ FF: 1 - mux in reference clock to read capture
 *        flops.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rstsprff </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reset Spare FF: 1 - reset spare capture flop (s_spr). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rstdqff </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reset DQ FF: 1 - reset read capture flops (p_upp,
 *        n_upp, p_low, n_low).
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_DPCONFIG2_BLx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3113                                  : 19;
     unsigned      gatevtwrap                                :  1;
     unsigned      granularity                               :  1;
     unsigned      enardpath                                 :  1;
     unsigned      clrgate                                   :  1;
     unsigned      gtlvlcfg                                  :  1;
     unsigned      wrlvlcfg                                  :  1;
     unsigned      rsvd6                                     :  1;
     unsigned      applydat                                  :  1;
     unsigned      applyclk                                  :  1;
     unsigned      refclk2sprff                              :  1;
     unsigned      refclk2dqff                               :  1;
     unsigned      rstsprff                                  :  1;
     unsigned      rstdqff                                   :  1;
#else    /* Little Endian */
     unsigned      rstdqff                                   :  1;
     unsigned      rstsprff                                  :  1;
     unsigned      refclk2dqff                               :  1;
     unsigned      refclk2sprff                              :  1;
     unsigned      applyclk                                  :  1;
     unsigned      applydat                                  :  1;
     unsigned      rsvd6                                     :  1;
     unsigned      wrlvlcfg                                  :  1;
     unsigned      gtlvlcfg                                  :  1;
     unsigned      clrgate                                   :  1;
     unsigned      enardpath                                 :  1;
     unsigned      granularity                               :  1;
     unsigned      gatevtwrap                                :  1;
     unsigned      rsvd3113                                  : 19;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DPCONFIG2_BLx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_PUPPDQSDLY_BLxCSx_r_t
 *  @brief CFG_SYSMEM_PHY_PUPPDQSDLY_BLxCSx
 *  @details This register provides delay control to the positive edge upper read DQS delay cell inside each individual DP hardmacro. This is a rank based register so there are 8 copies of this register in each one per rank.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_PUPPDQSDLY_BLxCSx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd319 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tapdly </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Tap Delay: Read data strobe delay cell tap selection
 *        for positive edge upper nibble data.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_PUPPDQSDLY_BLxCSx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd319                                   : 23;
     unsigned      tapdly                                    :  9;
#else    /* Little Endian */
     unsigned      tapdly                                    :  9;
     unsigned      rsvd319                                   : 23;
#endif
} ncp_phy_CFG_SYSMEM_PHY_PUPPDQSDLY_BLxCSx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_NUPPDQSDLY_BLxCSx_r_t
 *  @brief CFG_SYSMEM_PHY_NUPPDQSDLY_BLxCSx
 *  @details This register provides delay control to the negative edge upper read DQS delay cell inside each individual DP hardmacro. This is a rank based register so there are 8 copies of this register in each one per rank.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_NUPPDQSDLY_BLxCSx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd319 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tapdly </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Tap Delay: Read data strobe delay cell tap selection
 *        for negative edge upper nibble data.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_NUPPDQSDLY_BLxCSx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd319                                   : 23;
     unsigned      tapdly                                    :  9;
#else    /* Little Endian */
     unsigned      tapdly                                    :  9;
     unsigned      rsvd319                                   : 23;
#endif
} ncp_phy_CFG_SYSMEM_PHY_NUPPDQSDLY_BLxCSx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_PLOWDQSDLY_BLxCSx_r_t
 *  @brief CFG_SYSMEM_PHY_PLOWDQSDLY_BLxCSx
 *  @details This register provides delay control to the positive edge lower read DQS delay cell inside each individual DP hardmacro. This is a rank based register so there are 8 copies of this register in each one per rank.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_PLOWDQSDLY_BLxCSx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd319 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tapdly </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Tap Delay: Read data strobe delay cell tap selection
 *        for positive edge lower nibble data.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_PLOWDQSDLY_BLxCSx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd319                                   : 23;
     unsigned      tapdly                                    :  9;
#else    /* Little Endian */
     unsigned      tapdly                                    :  9;
     unsigned      rsvd319                                   : 23;
#endif
} ncp_phy_CFG_SYSMEM_PHY_PLOWDQSDLY_BLxCSx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_NLOWDQSDLY_BLxCSx_r_t
 *  @brief CFG_SYSMEM_PHY_NLOWDQSDLY_BLxCSx
 *  @details This register provides delay control to the negative edge lower read DQS delay cell inside each individual DP hardmacro. This is a rank based register so there are 8 copies of this register in each one per rank.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_NLOWDQSDLY_BLxCSx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd319 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tapdly </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Tap Delay: Read data strobe delay cell tap selection
 *        for positive edge lower nibble data.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_NLOWDQSDLY_BLxCSx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd319                                   : 23;
     unsigned      tapdly                                    :  9;
#else    /* Little Endian */
     unsigned      tapdly                                    :  9;
     unsigned      rsvd319                                   : 23;
#endif
} ncp_phy_CFG_SYSMEM_PHY_NLOWDQSDLY_BLxCSx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_SPAREDLY_BLx_r_t
 *  @brief CFG_SYSMEM_PHY_SPAREDLY_BLx
 *  @details This register provides delay control to the spare delay cell inside each individual DP hardmacro.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_SPAREDLY_BLx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd319 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tapdly </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Tap Delay: Read data strobe delay cell tap selection
 *        for spare cell delay.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_SPAREDLY_BLx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd319                                   : 23;
     unsigned      tapdly                                    :  9;
#else    /* Little Endian */
     unsigned      tapdly                                    :  9;
     unsigned      rsvd319                                   : 23;
#endif
} ncp_phy_CFG_SYSMEM_PHY_SPAREDLY_BLx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_GTUPPCTRL_BLxCSx_r_t
 *  @brief CFG_SYSMEM_PHY_GTUPPCTRL_BLxCSx
 *  @details This register provides the upper nibble gate delay setting for the read DQS1 inside each individual DP hardmacro. This is a rank based register so there are 8 copies of this register in each hardmacro, one per rank.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_GTUPPCTRL_BLxCSx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3113 </td>
 *     <td width="20%" align="center"> 19 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param snglcycdly </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Single Cycle Delay: Single clk cycle delay setting
 *        for upper nibble gate delay.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param qrtrcycdly </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Quarter Cycle Delay: 1/4 cycle delay setting for upper
 *        nibble gate delay.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param finetapdly </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Fine Tap Delay: Read data strobe delay cell tap selection
 *        for upper nibble gate delay.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_GTUPPCTRL_BLxCSx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3113                                  : 19;
     unsigned      snglcycdly                                :  2;
     unsigned      qrtrcycdly                                :  2;
     unsigned      finetapdly                                :  9;
#else    /* Little Endian */
     unsigned      finetapdly                                :  9;
     unsigned      qrtrcycdly                                :  2;
     unsigned      snglcycdly                                :  2;
     unsigned      rsvd3113                                  : 19;
#endif
} ncp_phy_CFG_SYSMEM_PHY_GTUPPCTRL_BLxCSx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_GTLOWCTRL_BLxCSx_r_t
 *  @brief CFG_SYSMEM_PHY_GTLOWCTRL_BLxCSx
 *  @details This register provides the lower nibble gate delay setting for the read DQS0 inside each individual DP hardmacro. This is a rank based register so there are 8 copies of this register in each hardmacro, one per rank.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_GTLOWCTRL_BLxCSx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3113 </td>
 *     <td width="20%" align="center"> 19 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param snglcycdly </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Single Cycle Delay: Single clk cycle delay setting
 *        for lower nibble gate delay.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param qrtrcycdly </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Quarter Cycle Delay: 1/4 cycle delay setting for lower
 *        nibble gate delay.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param finetapdly </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Fine Tap Delay: Read data strobe delay cell tap selection
 *        for lower nibble gate delay.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_GTLOWCTRL_BLxCSx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3113                                  : 19;
     unsigned      snglcycdly                                :  2;
     unsigned      qrtrcycdly                                :  2;
     unsigned      finetapdly                                :  9;
#else    /* Little Endian */
     unsigned      finetapdly                                :  9;
     unsigned      qrtrcycdly                                :  2;
     unsigned      snglcycdly                                :  2;
     unsigned      rsvd3113                                  : 19;
#endif
} ncp_phy_CFG_SYSMEM_PHY_GTLOWCTRL_BLxCSx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_WRTLVLUPP_BLxCSx_r_t
 *  @brief CFG_SYSMEM_PHY_WRTLVLUPP_BLxCSx
 *  @details This register provides write leveling delay setting for the upper data nibble (DQ[7:4]) and upper strobe (DQS1) inside each individual DP hardmacro. This is a rank based register so there are 8 copies of this register in each hardmacro, one per rank.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_WRTLVLUPP_BLxCSx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd314 </td>
 *     <td width="20%" align="center"> 28 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvldly </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Write Level Delay: Static control of the number of
 *        90 degree phase shifts for DQS1 and DQ[7:4]
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_WRTLVLUPP_BLxCSx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd314                                   : 28;
     unsigned      wrlvldly                                  :  4;
#else    /* Little Endian */
     unsigned      wrlvldly                                  :  4;
     unsigned      rsvd314                                   : 28;
#endif
} ncp_phy_CFG_SYSMEM_PHY_WRTLVLUPP_BLxCSx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_WRTLVLLOW_BLxCSx_r_t
 *  @brief CFG_SYSMEM_PHY_WRTLVLLOW_BLxCSx
 *  @details This register provides write leveling delay setting for the lower data nibble (DQ[3:0]) and upper strobe (DQS0) inside each individual DP hardmacro. This is a rank based register so there are 8 copies of this register in each hardmacro, one per rank.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_WRTLVLLOW_BLxCSx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd314 </td>
 *     <td width="20%" align="center"> 28 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvldly </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Write Level Delay: Static control of the number of
 *        90 degree phase shifts for DQS0 and DQ[3:0]
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_WRTLVLLOW_BLxCSx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd314                                   : 28;
     unsigned      wrlvldly                                  :  4;
#else    /* Little Endian */
     unsigned      wrlvldly                                  :  4;
     unsigned      rsvd314                                   : 28;
#endif
} ncp_phy_CFG_SYSMEM_PHY_WRTLVLLOW_BLxCSx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DPPWRMGR_BLx_r_t
 *  @brief CFG_SYSMEM_PHY_DPPWRMGR_BLx
 *  @details This register provides power management for each individual DP hardmacro.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DPPWRMGR_BLx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd314 </td>
 *     <td width="20%" align="center"> 28 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pwrdn05xclktree </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Power Down 05x Clk Tree: 1 - powers down the 05x clk
 *        trees (write and read path).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pwrdnctrlclktree </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Power Down Ctrl Clk Tree: 1 - powers down the control
 *        clk trees.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pwrdnwrclktree </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Power Down Wr Clk Tree: 1 - powers down the write
 *        clk trees.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pwrdnrdclktree </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Power Down Rd Clk Tree: 1 - powers down the read clk
 *        trees.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_DPPWRMGR_BLx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd314                                   : 28;
     unsigned      pwrdn05xclktree                           :  1;
     unsigned      pwrdnctrlclktree                          :  1;
     unsigned      pwrdnwrclktree                            :  1;
     unsigned      pwrdnrdclktree                            :  1;
#else    /* Little Endian */
     unsigned      pwrdnrdclktree                            :  1;
     unsigned      pwrdnwrclktree                            :  1;
     unsigned      pwrdnctrlclktree                          :  1;
     unsigned      pwrdn05xclktree                           :  1;
     unsigned      rsvd314                                   : 28;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DPPWRMGR_BLx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DPGTSTAT_BLx_r_t
 *  @brief CFG_SYSMEM_PHY_DPGTSTAT_BLx
 *  @details This register provides DQS gating results information for each individual DP hardmacro.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DPGTSTAT_BLx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd312 </td>
 *     <td width="20%" align="center"> 30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqs0gtrslt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Read only. This bit provides DQS gating result of
 *        each individual DP hardmacro. A 1 on this bit means
 *        the DQS gate is opened during the high pulse period
 *        of the DQS signal. A 0 on this bit means the DQS gate
 *        is opened during the low pulse period of the DQS signal.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqs1gtrslt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Read only. This bit provides DM gating result of each
 *        individual DP hardmacro. A 1 on this bit means the
 *        DQS gate is opened during the high pulse period of
 *        the DQS signal. A 0 on this bit means the DQS gate
 *        is opened during the low pulse period of the DQS signal.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_DPGTSTAT_BLx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd312                                   : 30;
     unsigned      dqs0gtrslt                                :  1;
     unsigned      dqs1gtrslt                                :  1;
#else    /* Little Endian */
     unsigned      dqs1gtrslt                                :  1;
     unsigned      dqs0gtrslt                                :  1;
     unsigned      rsvd312                                   : 30;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DPGTSTAT_BLx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_ADRx_PHASE90SEL0_r_t
 *  @brief CFG_SYSMEM_PHY_ADRx_PHASE90SEL0
 *  @details This register provides output phase selection for addr/cmd/cntl output on bits 0 to 7 on each individual ADR hardmacro.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_ADRx_PHASE90SEL0_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3116 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param addr7phssel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Bit 7 Addr Phase Select: </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param addr6phssel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Bit 6 Addr Phase Select: </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param addr5phssel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Bit 5 Addr Phase Select: </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param addr4phssel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Bit 4 Addr Phase Select: </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param addr3phssel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Bit 3 Addr Phase Select: </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param addr2phssel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Bit 2 Addr Phase Select: </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param addr1phssel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Bit 1 Addr Phase Select: </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param addr0phssel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Bit 0 Addr Phase Select: </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_ADRx_PHASE90SEL0_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3116                                  : 16;
     unsigned      addr7phssel                               :  2;
     unsigned      addr6phssel                               :  2;
     unsigned      addr5phssel                               :  2;
     unsigned      addr4phssel                               :  2;
     unsigned      addr3phssel                               :  2;
     unsigned      addr2phssel                               :  2;
     unsigned      addr1phssel                               :  2;
     unsigned      addr0phssel                               :  2;
#else    /* Little Endian */
     unsigned      addr0phssel                               :  2;
     unsigned      addr1phssel                               :  2;
     unsigned      addr2phssel                               :  2;
     unsigned      addr3phssel                               :  2;
     unsigned      addr4phssel                               :  2;
     unsigned      addr5phssel                               :  2;
     unsigned      addr6phssel                               :  2;
     unsigned      addr7phssel                               :  2;
     unsigned      rsvd3116                                  : 16;
#endif
} ncp_phy_CFG_SYSMEM_PHY_ADRx_PHASE90SEL0_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_ADRx_PHASE90SEL1_r_t
 *  @brief CFG_SYSMEM_PHY_ADRx_PHASE90SEL1
 *  @details This register provides programmability for .
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_ADRx_PHASE90SEL1_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd318 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param addr11phssel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Bit 11 Addr Phase Select: ADR12 only, Reserved for
 *        ADR9.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param addr10phssel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Bit 10 Addr Phase Select: ADR12 only, Reserved for
 *        ADR9.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param addr9phssel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Bit 9 Addr Phase Select: ADR12 only, Reserved for
 *        ADR9.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param addr8phssel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Bit 8 Addr Phase Select: </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_ADRx_PHASE90SEL1_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd318                                   : 24;
     unsigned      addr11phssel                              :  2;
     unsigned      addr10phssel                              :  2;
     unsigned      addr9phssel                               :  2;
     unsigned      addr8phssel                               :  2;
#else    /* Little Endian */
     unsigned      addr8phssel                               :  2;
     unsigned      addr9phssel                               :  2;
     unsigned      addr10phssel                              :  2;
     unsigned      addr11phssel                              :  2;
     unsigned      rsvd318                                   : 24;
#endif
} ncp_phy_CFG_SYSMEM_PHY_ADRx_PHASE90SEL1_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_ADRx_FINEDLYSELxx_r_t
 *  @brief CFG_SYSMEM_PHY_ADRx_FINEDLYSELxx
 *  @details This register provides  output fine delay selection for addr/cmd/cntl output bit xx on each individual ADR hardmacro.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_ADRx_FINEDLYSELxx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd315 </td>
 *     <td width="20%" align="center"> 27 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param addrxxfinedly </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Bit xx Fine Delay Select: 32 tap delay cell, nominal
 *        10ps per tap.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_ADRx_FINEDLYSELxx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd315                                   : 27;
     unsigned      addrxxfinedly                             :  5;
#else    /* Little Endian */
     unsigned      addrxxfinedly                             :  5;
     unsigned      rsvd315                                   : 27;
#endif
} ncp_phy_CFG_SYSMEM_PHY_ADRx_FINEDLYSELxx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_BC_ADRx_FINEDLYSELxx_r_t
 *  @brief CFG_SYSMEM_PHY_BC_ADRx_FINEDLYSELxx
 *  @details This register provides a broadcast write to all fine delay select registers on each individual ADR hardmacro. A write to this register overwrites all fine delay select register values. Reads to this register are invalid.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_BC_ADRx_FINEDLYSELxx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd315 </td>
 *     <td width="20%" align="center"> 27 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param addrxxfinedly </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Bit xx Fine Delay Select: 32 tap delay cell, nominal
 *        10ps per tap.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_BC_ADRx_FINEDLYSELxx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd315                                   : 27;
     unsigned      addrxxfinedly                             :  5;
#else    /* Little Endian */
     unsigned      addrxxfinedly                             :  5;
     unsigned      rsvd315                                   : 27;
#endif
} ncp_phy_CFG_SYSMEM_PHY_BC_ADRx_FINEDLYSELxx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_ADRx_GTDLYCTRL_r_t
 *  @brief CFG_SYSMEM_PHY_ADRx_GTDLYCTRL
 *  @details This register provides gate delay control setting to the VT monitor feedback path inside each individual ADR hardmacro.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_ADRx_GTDLYCTRL_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3114 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param snglcycdly </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Single Cycle Delay: Single clk cycle delay setting
 *        for lower nibble gate delay.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param qrtrcycdly </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Quarter Cycle Delay: 1/4 cycle delay setting for lower
 *        nibble gate delay.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param finetapdly </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Fine Tap Delay: Read data strobe delay cell tap selection
 *        for lower nibble gate delay.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_ADRx_GTDLYCTRL_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3114                                  : 18;
     unsigned      snglcycdly                                :  3;
     unsigned      qrtrcycdly                                :  2;
     unsigned      finetapdly                                :  9;
#else    /* Little Endian */
     unsigned      finetapdly                                :  9;
     unsigned      qrtrcycdly                                :  2;
     unsigned      snglcycdly                                :  3;
     unsigned      rsvd3114                                  : 18;
#endif
} ncp_phy_CFG_SYSMEM_PHY_ADRx_GTDLYCTRL_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_ADRx_ADRPWRMGR_r_t
 *  @brief CFG_SYSMEM_PHY_ADRx_ADRPWRMGR
 *  @details This register provides power management for each individual ADR hardmacro.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_ADRx_ADRPWRMGR_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd314 </td>
 *     <td width="20%" align="center"> 28 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pwrdn05xclktree </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Power Down 05x Clk Tree: 1 - powers down the 05x clk
 *        trees.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pwrdnctrlclktree </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Power Down Ctrl Clk Tree: 1 - powers down the control
 *        clk trees.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pwrdnwrclktree </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Power Down Wr Clk Tree: 1 - powers down the write
 *        clk trees.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_ADRx_ADRPWRMGR_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd314                                   : 28;
     unsigned      pwrdn05xclktree                           :  1;
     unsigned      pwrdnctrlclktree                          :  1;
     unsigned      pwrdnwrclktree                            :  1;
     unsigned      rsvd0                                     :  1;
#else    /* Little Endian */
     unsigned      rsvd0                                     :  1;
     unsigned      pwrdnwrclktree                            :  1;
     unsigned      pwrdnctrlclktree                          :  1;
     unsigned      pwrdn05xclktree                           :  1;
     unsigned      rsvd314                                   : 28;
#endif
} ncp_phy_CFG_SYSMEM_PHY_ADRx_ADRPWRMGR_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_ADRx_ADRGTSTAT_r_t
 *  @brief CFG_SYSMEM_PHY_ADRx_ADRGTSTAT
 *  @details This register provides feedback measurement control and status for each individual ADR hardmacro. The feedback state machine automatically programs this register based on FB Loop Sel value in the PHYCONFIG0 register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_ADRx_ADRGTSTAT_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd314 </td>
 *     <td width="20%" align="center"> 28 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param selfbio </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Select FB TX/RX I/Os: These bits override the static
 *        control bits and will apply ODT to the receiving IO.
 *        For power saving, deselect the feedback loop in between
 *        measurements. ADR12: 000 - no feedback path, 001 -
 *        feedback TX ADR[5]/ RX ADR[4], 010 - feedback TX ADR[7]/
 *        RX ADR[6], 100 - feedback TX ADR[11]/ RX ADR[10];
 *        ADR9: 000 - no feedback path, 001 - feedback TX ADR[2]/
 *        RX ADR[1], 010 - feedback TX ADR[4]/ RX ADR[3], 100
 *        - feedback TX ADR[8]/ RX ADR[7].
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param genfbstat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Generate FB Pulse/Status: Write a 1 to this bit to
 *        generate a single feedback pulse through the selected
 *        feedback loop. Read this bit for the status of the
 *        gate to feedback pulse phase alignment. A 1 on this
 *        bit means the gate is opened during the high pulse
 *        period of the feedback signal. A 0 on this bit means
 *        the gate is opened during the low pulse period of
 *        the feedback signal. The feedback state machine uses
 *        this register.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_ADRx_ADRGTSTAT_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd314                                   : 28;
     unsigned      selfbio                                   :  3;
     unsigned      genfbstat                                 :  1;
#else    /* Little Endian */
     unsigned      genfbstat                                 :  1;
     unsigned      selfbio                                   :  3;
     unsigned      rsvd314                                   : 28;
#endif
} ncp_phy_CFG_SYSMEM_PHY_ADRx_ADRGTSTAT_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG0_r_t
 *  @brief CFG_SYSMEM_PHY_PHYCONFIG0
 *  @details This register provides static configuration settings for the PHY.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG0_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_num_smpls </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> The write leveling state machine uses this value to
 *        determine how many write leveling samples to take
 *        at a given write DQS delay setting. Repeated sampling
 *        filters out errors caused by jitter. The default setting
 *        is 4, which results in 4 to 7 samples. A setting of
 *        0 is invalid.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fbdpsel </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> FB DP Sel: This selects which DP hardmacro is used
 *        by the feedback state machine.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param twlotwloe </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> TWLO TWLOE: Value programmed to the register times
 *        4 is the number of PCLK_IN (clk_phy) cycles from the
 *        strobe to DQ to provide write level response.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fixedrl </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Fixed Rd Lat: In fixed read latency drain FIFO mode,
 *        this sets the delay from the MC_R_DATA_EN to when
 *        the read data is read from the read FIFO. See Read
 *        FIFO modes for more detail.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fbadrsel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> FB ADR Sel: Selects which ADR hardmacro has the feedback
 *        loop. This selection only has an effect when the feedback
 *        state machine runs. 00 - select ADR 0 for feedback
 *        loop, 01 - select ADR 1 for feedback loop, 10 - select
 *        ADR 2 for feedback loop, 11 - select ADR 3 for feedback
 *        loop. NOTE: The upper ADR hardmacros 4 and 5 cannot
 *        be selected for a feedback loop.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fblpsel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> FB Loop Sel: Selects which feedback loop is used within
 *        the selected ADR hardmacro. This value is encoded
 *        to 1-hot and then written to the selected ADR hardmacro
 *        ADRGTSTAT register by the feedback state machine.
 *        ADR12: 00 - feedback TX ADR[5]/ RX ADR[4], 01 - feedback
 *        TX ADR[7]/ RX ADR[6], 10 - feedback TX ADR[11]/ RX
 *        ADR[10], 11 - invalid; ADR9: 00 - feedback TX ADR[2]/
 *        RX ADR[1], 01 - feedback TX ADR[4]/ RX ADR[3], 10
 *        - feedback TX ADR[8]/ RX ADR[7], 11 - invalid.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rnkrcvmode </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Rank Rcv Mode: Rank receive mode (x4/x8) for each
 *        rank. Bit 3 controls rank 0 up to bit 10 which controls
 *        rank 7. 1 - sets the rank for x4 mode, 0 - sets the
 *        rank for x8 mode.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Data Rd Align Delay: DIAGNOSTIC ONLY. Set to 1 to
 *        tell 1/4 cycle initialization state machine to load
 *        aligned delays into the read DQS delay cells. Normally
 *        this should be set to 0 so that the 1/4 cycle delay
 *        is loaded into the delay cells.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd10 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG0_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      wrlvl_num_smpls                           :  3;
     unsigned      fbdpsel                                   :  4;
     unsigned      twlotwloe                                 :  4;
     unsigned      fixedrl                                   :  6;
     unsigned      fbadrsel                                  :  2;
     unsigned      fblpsel                                   :  2;
     unsigned      rnkrcvmode                                :  8;
     unsigned      rsvd2                                     :  1;
     unsigned      rsvd10                                    :  2;
#else    /* Little Endian */
     unsigned      rsvd10                                    :  2;
     unsigned      rsvd2                                     :  1;
     unsigned      rnkrcvmode                                :  8;
     unsigned      fblpsel                                   :  2;
     unsigned      fbadrsel                                  :  2;
     unsigned      fixedrl                                   :  6;
     unsigned      twlotwloe                                 :  4;
     unsigned      fbdpsel                                   :  4;
     unsigned      wrlvl_num_smpls                           :  3;
#endif
} ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG0_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG1_r_t
 *  @brief CFG_SYSMEM_PHY_PHYCONFIG1
 *  @details This register provides static configuration settings for the PHY.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG1_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3131 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bblclobber </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Bubble Clobber: Set this bit high to eliminate the
 *        possibility of a data bubble in self drain FIFO mode.
 *        This adds one clock cycle of latency through the read
 *        FIFO. For lowest latency (with the possibility of
 *        a data bubble), set this bit low. This bit has no
 *        effect in other FIFO modes.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrranksel </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Wr Rank Sel: This field represents an encoded rank
 *        from 0 to 7. When wrranksw is 0, the PHY uses thsi
 *        field to select the write rank. When wrranksw is 1,
 *        the PHY ignores the value of this field.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlatrank </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Wr Lat Rank: Determines the number of clks from a
 *        write command to when the rank select (decoded from
 *        CS) is presented to the DP hardmacro. Rank select
 *        must be presented to the DP two clk cycles before
 *        MC_W_DATA_EN is asserted.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrranksw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Write Rank SW: This bit is used in conjunction with
 *        the wrranksel field. 1 - the MC_CSN input value is
 *        used for write rank destination, 0 - the wrranksel
 *        is used for the write rank destination. NOTE: During
 *        the write leveling process, this bit must be 0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gttrnmode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Gate Train Mode: 1 - configure the PHY in gate training
 *        mode. This bit must remain set during the gate training
 *        process. 0 - normal operating mode.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pulsedqs </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Pulse DQS: Writing a 1 to this bit initiates a DQS
 *        pulse during DDR3 write leveling process. This bit
 *        is self-clearing.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvlmode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Wrlvl Mode: 1 - configure the PHY in write leveling
 *        mode. This bit turns on the output enable circuit
 *        of the I/O pad of the DQS signal. The DQS signal is
 *        driven low on the memory bus. It must be left a 1
 *        during the write leveling process.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ddr2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> DDR2: 1 - configure the PHY for DDR2 mode, 0 - configure
 *        the PHY for DDR3 mode.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd1615 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdranksel </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Rd Rank Sel: This field represents an encoded rank
 *        from 0 to 7. When rdranksw is 0, the PHY uses this
 *        field to select the read rank. When rdranksw is 1,
 *        the PHY ignores the value of this field.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdranksw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Rd Rank SW: This bit is used in conjunction with the
 *        rdranksel field. 1 - the MC_CSN input value is used
 *        for read rank source, 0 - the rdranksel field is used
 *        for the read rank source. NOTE: During the gate training
 *        process, this bit must be 0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd105 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param suppress_gttrnval </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Set this bit to 1 to suppress the MC_R_DATA_VALID
 *        signal during gate training mode. This bit has no
 *        effect when the GATE_TRAIN_MODE bit is set to 0. When
 *        this bit is set to a 0, the MC_R_DATA_VALID signal
 *        propagates normally through gate training mode.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mcerr_active </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> When this bit is set to 1, the MC_ERR_OUT signals
 *        reflect the value that is sampled on the corresponding
 *        ADDR_CMD_OUT pins. When this bit is set to 0, the
 *        MC_ERR_OUT signals are forced to a value of 1.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param track_gain </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> This field controls the gain of the quarter-cycle
 *        delay tracking state machine. Each delay update increments
 *        or decrements the read DQS delay by the number of
 *        taps programmed in this register.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG1_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3131                                  :  1;
     unsigned      bblclobber                                :  1;
     unsigned      wrranksel                                 :  3;
     unsigned      wrlatrank                                 :  5;
     unsigned      wrranksw                                  :  1;
     unsigned      gttrnmode                                 :  1;
     unsigned      pulsedqs                                  :  1;
     unsigned      wrlvlmode                                 :  1;
     unsigned      ddr2                                      :  1;
     unsigned      rsvd1615                                  :  2;
     unsigned      rdranksel                                 :  3;
     unsigned      rdranksw                                  :  1;
     unsigned      rsvd105                                   :  6;
     unsigned      suppress_gttrnval                         :  1;
     unsigned      mcerr_active                              :  1;
     unsigned      track_gain                                :  3;
#else    /* Little Endian */
     unsigned      track_gain                                :  3;
     unsigned      mcerr_active                              :  1;
     unsigned      suppress_gttrnval                         :  1;
     unsigned      rsvd105                                   :  6;
     unsigned      rdranksw                                  :  1;
     unsigned      rdranksel                                 :  3;
     unsigned      rsvd1615                                  :  2;
     unsigned      ddr2                                      :  1;
     unsigned      wrlvlmode                                 :  1;
     unsigned      pulsedqs                                  :  1;
     unsigned      gttrnmode                                 :  1;
     unsigned      wrranksw                                  :  1;
     unsigned      wrlatrank                                 :  5;
     unsigned      wrranksel                                 :  3;
     unsigned      bblclobber                                :  1;
     unsigned      rsvd3131                                  :  1;
#endif
} ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG1_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG3_BLx_r_t
 *  @brief CFG_SYSMEM_PHY_PHYCONFIG3_BLx
 *  @details This register provides static configuration settings for the PHY.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG3_BLx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3110 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlatrank </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Rd Lat Rank: This field is used to specify the latency
 *        from the read command until the decoded rank is applied
 *        to the DP8 hardmacro. If MC_R_DATA_EN starts on the
 *        same clk cycle as the read command, the value in this
 *        register should be equal to rdlatgate so that the
 *        rank information will arrive at the DP8 one clk cycle
 *        ahead of the read gate signal.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlatgate </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Rd Lat Gate: This field is used to specify the latency
 *        from MC_R_DATA_EN until the read gate signal is applied
 *        to the DP8 hardmacro. The read gate signal is further
 *        delayed independently for each data lane inside the
 *        DP8 hardmacro.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG3_BLx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3110                                  : 22;
     unsigned      rdlatrank                                 :  5;
     unsigned      rdlatgate                                 :  5;
#else    /* Little Endian */
     unsigned      rdlatgate                                 :  5;
     unsigned      rdlatrank                                 :  5;
     unsigned      rsvd3110                                  : 22;
#endif
} ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG3_BLx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_WRLVLSMSTAT_r_t
 *  @brief CFG_SYSMEM_PHY_WRLVLSMSTAT
 *  @details This register provides write leveling overflow status for all DP hardmacros.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_WRLVLSMSTAT_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3118 </td>
 *     <td width="20%" align="center"> 14 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp8wrdqs1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> DP8 Wr DQS1 Dly Ovf: 1 - no transition found on DQ
 *        during write leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp8wrdqs0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DP8 Wr DQS0 Dly Ovf: 1 - no transition found on DQ
 *        during write leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp7wrdqs1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> DP7 Wr DQS1 Dly Ovf: 1 - no transition found on DQ
 *        during write leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp7wrdqs0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> DP7 Wr DQS0 Dly Ovf: 1 - no transition found on DQ
 *        during write leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp6wrdqs1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> DP6 Wr DQS1 Dly Ovf: 1 - no transition found on DQ
 *        during write leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp6wrdqs0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> DP6 Wr DQS0 Dly Ovf: 1 - no transition found on DQ
 *        during write leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp5wrdqs1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> DP5 Wr DQS1 Dly Ovf: 1 - no transition found on DQ
 *        during write leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp5wrdqs0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> DP5 Wr DQS0 Dly Ovf: 1 - no transition found on DQ
 *        during write leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp4wrdqs1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> DP4 Wr DQS1 Dly Ovf: 1 - no transition found on DQ
 *        during write leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp4wrdqs0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DP4 Wr DQS0 Dly Ovf: 1 - no transition found on DQ
 *        during write leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp3wrdqs1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> DP3 Wr DQS1 Dly Ovf: 1 - no transition found on DQ
 *        during write leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp3wrdqs0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> DP3 Wr DQS0 Dly Ovf: 1 - no transition found on DQ
 *        during write leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp2wrdqs1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> DP2 Wr DQS1 Dly Ovf: 1 - no transition found on DQ
 *        during write leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp2wrdqs0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> DP2 Wr DQS0 Dly Ovf: 1 - no transition found on DQ
 *        during write leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp1wrdqs1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> DP1 Wr DQS1 Dly Ovf: 1 - no transition found on DQ
 *        during write leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp1wrdqs0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> DP1 Wr DQS0 Dly Ovf: 1 - no transition found on DQ
 *        during write leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp0wrdqs1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> DP0 Wr DQS1 Dly Ovf: 1 - no transition found on DQ
 *        during write leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp0wrdqs0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DP0 Wr DQS0 Dly Ovf: 1 - no transition found on DQ
 *        during write leveling.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_WRLVLSMSTAT_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3118                                  : 14;
     unsigned      dp8wrdqs1ovf                              :  1;
     unsigned      dp8wrdqs0ovf                              :  1;
     unsigned      dp7wrdqs1ovf                              :  1;
     unsigned      dp7wrdqs0ovf                              :  1;
     unsigned      dp6wrdqs1ovf                              :  1;
     unsigned      dp6wrdqs0ovf                              :  1;
     unsigned      dp5wrdqs1ovf                              :  1;
     unsigned      dp5wrdqs0ovf                              :  1;
     unsigned      dp4wrdqs1ovf                              :  1;
     unsigned      dp4wrdqs0ovf                              :  1;
     unsigned      dp3wrdqs1ovf                              :  1;
     unsigned      dp3wrdqs0ovf                              :  1;
     unsigned      dp2wrdqs1ovf                              :  1;
     unsigned      dp2wrdqs0ovf                              :  1;
     unsigned      dp1wrdqs1ovf                              :  1;
     unsigned      dp1wrdqs0ovf                              :  1;
     unsigned      dp0wrdqs1ovf                              :  1;
     unsigned      dp0wrdqs0ovf                              :  1;
#else    /* Little Endian */
     unsigned      dp0wrdqs0ovf                              :  1;
     unsigned      dp0wrdqs1ovf                              :  1;
     unsigned      dp1wrdqs0ovf                              :  1;
     unsigned      dp1wrdqs1ovf                              :  1;
     unsigned      dp2wrdqs0ovf                              :  1;
     unsigned      dp2wrdqs1ovf                              :  1;
     unsigned      dp3wrdqs0ovf                              :  1;
     unsigned      dp3wrdqs1ovf                              :  1;
     unsigned      dp4wrdqs0ovf                              :  1;
     unsigned      dp4wrdqs1ovf                              :  1;
     unsigned      dp5wrdqs0ovf                              :  1;
     unsigned      dp5wrdqs1ovf                              :  1;
     unsigned      dp6wrdqs0ovf                              :  1;
     unsigned      dp6wrdqs1ovf                              :  1;
     unsigned      dp7wrdqs0ovf                              :  1;
     unsigned      dp7wrdqs1ovf                              :  1;
     unsigned      dp8wrdqs0ovf                              :  1;
     unsigned      dp8wrdqs1ovf                              :  1;
     unsigned      rsvd3118                                  : 14;
#endif
} ncp_phy_CFG_SYSMEM_PHY_WRLVLSMSTAT_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_RDLVLSTATPEDGE_r_t
 *  @brief CFG_SYSMEM_PHY_RDLVLSTATPEDGE
 *  @details This register provides read eye centering overflow status for all DP hardmacros. This status is generated by the read leveling state machine. The overflow status is reported for read eye centering performed for the positive edge of DQS as indicated by the rdlvledge bit in the phyconfig1 register of the dfi_rdlvl_edge DFI input. Read DQS delay overflowed and did not find the correct DQS centering during the read eye or data eye centering. These bits provide the status of the latest read leveling.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_RDLVLSTATPEDGE_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3118 </td>
 *     <td width="20%" align="center"> 14 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp8rdpdqs1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> DP8 Rd DQS1 P Dly Ovf: 1 - no center found for DQS
 *        p edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp8rdpdqs0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DP8 Rd DQS0 P Dly Ovf: 1 - no center found for DQS
 *        p edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp7rdpdqs1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> DP7 Rd DQS1 P Dly Ovf: 1 - no center found for DQS
 *        p edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp7rdpdqs0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> DP7 Rd DQS0 P Dly Ovf: 1 - no center found for DQS
 *        p edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp6rdpdqs1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> DP6 Rd DQS1 P Dly Ovf: 1 - no center found for DQS
 *        p edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp6rdpdqs0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> DP6 Rd DQS0 P Dly Ovf: 1 - no center found for DQS
 *        p edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp5rdpdqs1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> DP5 Rd DQS1 P Dly Ovf: 1 - no center found for DQS
 *        p edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp5rdpdqs0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> DP5 Rd DQS0 P Dly Ovf: 1 - no center found for DQS
 *        p edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp4rdpdqs1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> DP4 Rd DQS1 P Dly Ovf: 1 - no center found for DQS
 *        p edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp4rdpdqs0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DP4 Rd DQS0 P Dly Ovf: 1 - no center found for DQS
 *        p edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp3rdpdqs1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> DP3 Rd DQS1 P Dly Ovf: 1 - no center found for DQS
 *        p edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp3rdpdqs0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> DP3 Rd DQS0 P Dly Ovf: 1 - no center found for DQS
 *        p edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp2rdpdqs1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> DP2 Rd DQS1 P Dly Ovf: 1 - no center found for DQS
 *        p edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp2rdpdqs0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> DP2 Rd DQS0 P Dly Ovf: 1 - no center found for DQS
 *        p edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp1rdpdqs1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> DP1 Rd DQS1 P Dly Ovf: 1 - no center found for DQS
 *        p edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp1rdpdqs0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> DP1 Rd DQS0 P Dly Ovf: 1 - no center found for DQS
 *        p edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp0rdpdqs1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> DP0 Rd DQS1 P Dly Ovf: 1 - no center found for DQS
 *        p edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp0rdpdqs0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DP0 Rd DQS0 P Dly Ovf: 1 - no center found for DQS
 *        p edge during read leveling.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_RDLVLSTATPEDGE_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3118                                  : 14;
     unsigned      dp8rdpdqs1ovf                             :  1;
     unsigned      dp8rdpdqs0ovf                             :  1;
     unsigned      dp7rdpdqs1ovf                             :  1;
     unsigned      dp7rdpdqs0ovf                             :  1;
     unsigned      dp6rdpdqs1ovf                             :  1;
     unsigned      dp6rdpdqs0ovf                             :  1;
     unsigned      dp5rdpdqs1ovf                             :  1;
     unsigned      dp5rdpdqs0ovf                             :  1;
     unsigned      dp4rdpdqs1ovf                             :  1;
     unsigned      dp4rdpdqs0ovf                             :  1;
     unsigned      dp3rdpdqs1ovf                             :  1;
     unsigned      dp3rdpdqs0ovf                             :  1;
     unsigned      dp2rdpdqs1ovf                             :  1;
     unsigned      dp2rdpdqs0ovf                             :  1;
     unsigned      dp1rdpdqs1ovf                             :  1;
     unsigned      dp1rdpdqs0ovf                             :  1;
     unsigned      dp0rdpdqs1ovf                             :  1;
     unsigned      dp0rdpdqs0ovf                             :  1;
#else    /* Little Endian */
     unsigned      dp0rdpdqs0ovf                             :  1;
     unsigned      dp0rdpdqs1ovf                             :  1;
     unsigned      dp1rdpdqs0ovf                             :  1;
     unsigned      dp1rdpdqs1ovf                             :  1;
     unsigned      dp2rdpdqs0ovf                             :  1;
     unsigned      dp2rdpdqs1ovf                             :  1;
     unsigned      dp3rdpdqs0ovf                             :  1;
     unsigned      dp3rdpdqs1ovf                             :  1;
     unsigned      dp4rdpdqs0ovf                             :  1;
     unsigned      dp4rdpdqs1ovf                             :  1;
     unsigned      dp5rdpdqs0ovf                             :  1;
     unsigned      dp5rdpdqs1ovf                             :  1;
     unsigned      dp6rdpdqs0ovf                             :  1;
     unsigned      dp6rdpdqs1ovf                             :  1;
     unsigned      dp7rdpdqs0ovf                             :  1;
     unsigned      dp7rdpdqs1ovf                             :  1;
     unsigned      dp8rdpdqs0ovf                             :  1;
     unsigned      dp8rdpdqs1ovf                             :  1;
     unsigned      rsvd3118                                  : 14;
#endif
} ncp_phy_CFG_SYSMEM_PHY_RDLVLSTATPEDGE_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_RDLVLP2FDLY_BLx_r_t
 *  @brief CFG_SYSMEM_PHY_RDLVLP2FDLY_BLx
 *  @details This register provides the pass to fail point during read leveling or data eye centering for the latest read leveling.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_RDLVLP2FDLY_BLx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3110 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pass2fail </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Pass to Fail Delay </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_RDLVLP2FDLY_BLx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3110                                  : 22;
     unsigned      pass2fail                                 : 10;
#else    /* Little Endian */
     unsigned      pass2fail                                 : 10;
     unsigned      rsvd3110                                  : 22;
#endif
} ncp_phy_CFG_SYSMEM_PHY_RDLVLP2FDLY_BLx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_RDLVLF2PDLY_BLx_r_t
 *  @brief CFG_SYSMEM_PHY_RDLVLF2PDLY_BLx
 *  @details This register provides the fail to pass point during read leveling or data eye centering for the latest read leveling.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_RDLVLF2PDLY_BLx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3110 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fail2pass </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Fail to Pass Delay </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_RDLVLF2PDLY_BLx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3110                                  : 22;
     unsigned      fail2pass                                 : 10;
#else    /* Little Endian */
     unsigned      fail2pass                                 : 10;
     unsigned      rsvd3110                                  : 22;
#endif
} ncp_phy_CFG_SYSMEM_PHY_RDLVLF2PDLY_BLx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_GTTRAINSTAT0_r_t
 *  @brief CFG_SYSMEM_PHY_GTTRAINSTAT0
 *  @details This register provides gate training status for DP hardmacros 0 to 7. If any of these bits are set after the gate training state machine has run, then it failed to converge for that byte lane. Try a new value of Rd Lat in the PHYCONFIG3 register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_GTTRAINSTAT0_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dp7gtovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> DP7 Gate Ovf: 1 - gate delay overflow before finding
 *        a rising edge.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp7gtuvfs58 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> DP7 Gate UvfS58: 1 - gate delay underflow while subtracting
 *        5/8ths of cycle to check for preamble.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp7gtuvfs4q </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> DP7 Gate UvfS4Q: 1 - gate delay underflow while subtracting
 *        4 quarter cycles.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp7gtuvf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> DP7 Gate Uvf: 1 - gate delay underflow before finding
 *        a rising edge.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp6gtovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> DP6 Gate Ovf: 1 - gate delay overflow before finding
 *        a rising edge.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp6gtuvfs58 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> DP6 Gate UvfS58: 1 - gate delay underflow while subtracting
 *        5/8ths of cycle to check for preamble.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp6gtuvfs4q </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> DP6 Gate UvfS4Q: 1 - gate delay underflow while subtracting
 *        4 quarter cycles.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp6gtuvf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> DP6 Gate Uvf: 1 - gate delay underflow before finding
 *        a rising edge.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp5gtovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> DP5 Gate Ovf: 1 - gate delay overflow before finding
 *        a rising edge.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp5gtuvfs58 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> DP5 Gate UvfS58: 1 - gate delay underflow while subtracting
 *        5/8ths of cycle to check for preamble.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp5gtuvfs4q </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> DP5 Gate UvfS4Q: 1 - gate delay underflow while subtracting
 *        4 quarter cycles.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp5gtuvf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> DP5 Gate Uvf: 1 - gate delay underflow before finding
 *        a rising edge.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp4gtovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> DP4 Gate Ovf: 1 - gate delay overflow before finding
 *        a rising edge.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp4gtuvfs58 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> DP4 Gate UvfS58: 1 - gate delay underflow while subtracting
 *        5/8ths of cycle to check for preamble.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp4gtuvfs4q </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> DP4 Gate UvfS4Q: 1 - gate delay underflow while subtracting
 *        4 quarter cycles.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp4gtuvf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DP4 Gate Uvf: 1 - gate delay underflow before finding
 *        a rising edge.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp3gtovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> DP3 Gate Ovf: 1 - gate delay overflow before finding
 *        a rising edge.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp3gtuvfs58 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> DP3 Gate UvfS58: 1 - gate delay underflow while subtracting
 *        5/8ths of cycle to check for preamble.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp3gtuvfs4q </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> DP3 Gate UvfS4Q: 1 - gate delay underflow while subtracting
 *        4 quarter cycles.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp3gtuvf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> DP3 Gate Uvf: 1 - gate delay underflow before finding
 *        a rising edge.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp2gtovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> DP2 Gate Ovf: 1 - gate delay overflow before finding
 *        a rising edge.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp2gtuvfs58 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> DP2 Gate UvfS58: 1 - gate delay underflow while subtracting
 *        5/8ths of cycle to check for preamble.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp2gtuvfs4q </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> DP2 Gate UvfS4Q: 1 - gate delay underflow while subtracting
 *        4 quarter cycles.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp2gtuvf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DP2 Gate Uvf: 1 - gate delay underflow before finding
 *        a rising edge.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp1gtovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> DP1 Gate Ovf: 1 - gate delay overflow before finding
 *        a rising edge.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp1gtuvfs58 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> DP1 Gate UvfS58: 1 - gate delay underflow while subtracting
 *        5/8ths of cycle to check for preamble.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp1gtuvfs4q </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> DP1 Gate UvfS4Q: 1 - gate delay underflow while subtracting
 *        4 quarter cycles.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp1gtuvf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> DP1 Gate Uvf: 1 - gate delay underflow before finding
 *        a rising edge.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp0gtovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> DP0 Gate Ovf: 1 - gate delay overflow before finding
 *        a rising edge.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp0gtuvfs58 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> DP0 Gate UvfS58: 1 - gate delay underflow while subtracting
 *        5/8ths of cycle to check for preamble.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp0gtuvfs4q </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> DP0 Gate UvfS4Q: 1 - gate delay underflow while subtracting
 *        4 quarter cycles.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp0gtuvf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DP0 Gate Uvf: 1 - gate delay underflow before finding
 *        a rising edge.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_GTTRAINSTAT0_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      dp7gtovf                                  :  1;
     unsigned      dp7gtuvfs58                               :  1;
     unsigned      dp7gtuvfs4q                               :  1;
     unsigned      dp7gtuvf                                  :  1;
     unsigned      dp6gtovf                                  :  1;
     unsigned      dp6gtuvfs58                               :  1;
     unsigned      dp6gtuvfs4q                               :  1;
     unsigned      dp6gtuvf                                  :  1;
     unsigned      dp5gtovf                                  :  1;
     unsigned      dp5gtuvfs58                               :  1;
     unsigned      dp5gtuvfs4q                               :  1;
     unsigned      dp5gtuvf                                  :  1;
     unsigned      dp4gtovf                                  :  1;
     unsigned      dp4gtuvfs58                               :  1;
     unsigned      dp4gtuvfs4q                               :  1;
     unsigned      dp4gtuvf                                  :  1;
     unsigned      dp3gtovf                                  :  1;
     unsigned      dp3gtuvfs58                               :  1;
     unsigned      dp3gtuvfs4q                               :  1;
     unsigned      dp3gtuvf                                  :  1;
     unsigned      dp2gtovf                                  :  1;
     unsigned      dp2gtuvfs58                               :  1;
     unsigned      dp2gtuvfs4q                               :  1;
     unsigned      dp2gtuvf                                  :  1;
     unsigned      dp1gtovf                                  :  1;
     unsigned      dp1gtuvfs58                               :  1;
     unsigned      dp1gtuvfs4q                               :  1;
     unsigned      dp1gtuvf                                  :  1;
     unsigned      dp0gtovf                                  :  1;
     unsigned      dp0gtuvfs58                               :  1;
     unsigned      dp0gtuvfs4q                               :  1;
     unsigned      dp0gtuvf                                  :  1;
#else    /* Little Endian */
     unsigned      dp0gtuvf                                  :  1;
     unsigned      dp0gtuvfs4q                               :  1;
     unsigned      dp0gtuvfs58                               :  1;
     unsigned      dp0gtovf                                  :  1;
     unsigned      dp1gtuvf                                  :  1;
     unsigned      dp1gtuvfs4q                               :  1;
     unsigned      dp1gtuvfs58                               :  1;
     unsigned      dp1gtovf                                  :  1;
     unsigned      dp2gtuvf                                  :  1;
     unsigned      dp2gtuvfs4q                               :  1;
     unsigned      dp2gtuvfs58                               :  1;
     unsigned      dp2gtovf                                  :  1;
     unsigned      dp3gtuvf                                  :  1;
     unsigned      dp3gtuvfs4q                               :  1;
     unsigned      dp3gtuvfs58                               :  1;
     unsigned      dp3gtovf                                  :  1;
     unsigned      dp4gtuvf                                  :  1;
     unsigned      dp4gtuvfs4q                               :  1;
     unsigned      dp4gtuvfs58                               :  1;
     unsigned      dp4gtovf                                  :  1;
     unsigned      dp5gtuvf                                  :  1;
     unsigned      dp5gtuvfs4q                               :  1;
     unsigned      dp5gtuvfs58                               :  1;
     unsigned      dp5gtovf                                  :  1;
     unsigned      dp6gtuvf                                  :  1;
     unsigned      dp6gtuvfs4q                               :  1;
     unsigned      dp6gtuvfs58                               :  1;
     unsigned      dp6gtovf                                  :  1;
     unsigned      dp7gtuvf                                  :  1;
     unsigned      dp7gtuvfs4q                               :  1;
     unsigned      dp7gtuvfs58                               :  1;
     unsigned      dp7gtovf                                  :  1;
#endif
} ncp_phy_CFG_SYSMEM_PHY_GTTRAINSTAT0_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_GTTRAINSTAT1_r_t
 *  @brief CFG_SYSMEM_PHY_GTTRAINSTAT1
 *  @details This register provides gate training status for DP hardmacro 8. If any of these bits are set after the gate training state machine has run, then it failed to converge for that byte lane. Try a new value of Rd Lat in the PHYCONFIG3 register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_GTTRAINSTAT1_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd314 </td>
 *     <td width="20%" align="center"> 28 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp8gtovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> DP8 Gate Ovf: 1 - gate delay overflow before finding
 *        a rising edge.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp8gtuvfs58 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> DP8 Gate UvfS58: 1 - gate delay underflow while subtracting
 *        5/8ths of cycle to check for preamble.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp8gtuvfs4q </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> DP8 Gate UvfS4Q: 1 - gate delay underflow while subtracting
 *        4 quarter cycles.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp8gtuvf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DP8 Gate Uvf: 1 - gate delay underflow before finding
 *        a rising edge.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_GTTRAINSTAT1_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd314                                   : 28;
     unsigned      dp8gtovf                                  :  1;
     unsigned      dp8gtuvfs58                               :  1;
     unsigned      dp8gtuvfs4q                               :  1;
     unsigned      dp8gtuvf                                  :  1;
#else    /* Little Endian */
     unsigned      dp8gtuvf                                  :  1;
     unsigned      dp8gtuvfs4q                               :  1;
     unsigned      dp8gtuvfs58                               :  1;
     unsigned      dp8gtovf                                  :  1;
     unsigned      rsvd314                                   : 28;
#endif
} ncp_phy_CFG_SYSMEM_PHY_GTTRAINSTAT1_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DATBYTEDIS_r_t
 *  @brief CFG_SYSMEM_PHY_DATBYTEDIS
 *  @details This register provides current status for the DFI DATA BYTE DISABLEs and DFI INIT START supplied by the memory controller.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DATBYTEDIS_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3117 </td>
 *     <td width="20%" align="center"> 15 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param initstart </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reflects the value that is driven on the Dfi_Init_Start
 *        input.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd159 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param datbytdis </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reflects the value captured at the Dfi_Data_Byte_Disable
 *        inputs at the rising edge of the Dfi_Init_Start input.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_DATBYTEDIS_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3117                                  : 15;
     unsigned      initstart                                 :  1;
     unsigned      rsvd159                                   :  7;
     unsigned      datbytdis                                 :  9;
#else    /* Little Endian */
     unsigned      datbytdis                                 :  9;
     unsigned      rsvd159                                   :  7;
     unsigned      initstart                                 :  1;
     unsigned      rsvd3117                                  : 15;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DATBYTEDIS_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_RDDSKWSTAT_r_t
 *  @brief CFG_SYSMEM_PHY_RDDSKWSTAT
 *  @details This register provides status for the read leveling state machine with bit de-skew turned on. If one of these bits are set, then read DQ delay underflowed and did not complete bit alignment. These bits provide the status of the latest run de-skew result.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_RDDSKWSTAT_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3118 </td>
 *     <td width="20%" align="center"> 14 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp8rddsk1uvf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> DP8 Rd Deskew Upper Nibble Delay Uvf: 1 - deskew delay
 *        underflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp8rddsk0uvf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DP8 Rd Deskew Lower Nibble Delay Uvf: 1 - deskew delay
 *        underflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp7rddsk1uvf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> DP7 Rd Deskew Upper Nibble Delay Uvf: 1 - deskew delay
 *        underflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp7rddsk0uvf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> DP7 Rd Deskew Lower Nibble Delay Uvf: 1 - deskew delay
 *        underflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp6rddsk1uvf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> DP6 Rd Deskew Upper Nibble Delay Uvf: 1 - deskew delay
 *        underflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp6rddsk0uvf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> DP6 Rd Deskew Lower Nibble Delay Uvf: 1 - deskew delay
 *        underflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp5rddsk1uvf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> DP5 Rd Deskew Upper Nibble Delay Uvf: 1 - deskew delay
 *        underflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp5rddsk0uvf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> DP5 Rd Deskew Lower Nibble Delay Uvf: 1 - deskew delay
 *        underflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp4rddsk1uvf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> DP4 Rd Deskew Upper Nibble Delay Uvf: 1 - deskew delay
 *        underflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp4rddsk0uvf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DP4 Rd Deskew Lower Nibble Delay Uvf: 1 - deskew delay
 *        underflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp3rddsk1uvf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> DP3 Rd Deskew Upper Nibble Delay Uvf: 1 - deskew delay
 *        underflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp3rddsk0uvf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> DP3 Rd Deskew Lower Nibble Delay Uvf: 1 - deskew delay
 *        underflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp2rddsk1uvf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> DP2 Rd Deskew Upper Nibble Delay Uvf: 1 - deskew delay
 *        underflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp2rddsk0uvf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> DP2 Rd Deskew Lower Nibble Delay Uvf: 1 - deskew delay
 *        underflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp1rddsk1uvf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> DP1 Rd Deskew Upper Nibble Delay Uvf: 1 - deskew delay
 *        underflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp1rddsk0uvf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> DP1 Rd Deskew Lower Nibble Delay Uvf: 1 - deskew delay
 *        underflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp0rddsk1uvf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> DP0 Rd Deskew Upper Nibble Delay Uvf: 1 - deskew delay
 *        underflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp0rddsk0uvf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DP0 Rd Deskew Lower Nibble Delay Uvf: 1 - deskew delay
 *        underflow during read leveling.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_RDDSKWSTAT_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3118                                  : 14;
     unsigned      dp8rddsk1uvf                              :  1;
     unsigned      dp8rddsk0uvf                              :  1;
     unsigned      dp7rddsk1uvf                              :  1;
     unsigned      dp7rddsk0uvf                              :  1;
     unsigned      dp6rddsk1uvf                              :  1;
     unsigned      dp6rddsk0uvf                              :  1;
     unsigned      dp5rddsk1uvf                              :  1;
     unsigned      dp5rddsk0uvf                              :  1;
     unsigned      dp4rddsk1uvf                              :  1;
     unsigned      dp4rddsk0uvf                              :  1;
     unsigned      dp3rddsk1uvf                              :  1;
     unsigned      dp3rddsk0uvf                              :  1;
     unsigned      dp2rddsk1uvf                              :  1;
     unsigned      dp2rddsk0uvf                              :  1;
     unsigned      dp1rddsk1uvf                              :  1;
     unsigned      dp1rddsk0uvf                              :  1;
     unsigned      dp0rddsk1uvf                              :  1;
     unsigned      dp0rddsk0uvf                              :  1;
#else    /* Little Endian */
     unsigned      dp0rddsk0uvf                              :  1;
     unsigned      dp0rddsk1uvf                              :  1;
     unsigned      dp1rddsk0uvf                              :  1;
     unsigned      dp1rddsk1uvf                              :  1;
     unsigned      dp2rddsk0uvf                              :  1;
     unsigned      dp2rddsk1uvf                              :  1;
     unsigned      dp3rddsk0uvf                              :  1;
     unsigned      dp3rddsk1uvf                              :  1;
     unsigned      dp4rddsk0uvf                              :  1;
     unsigned      dp4rddsk1uvf                              :  1;
     unsigned      dp5rddsk0uvf                              :  1;
     unsigned      dp5rddsk1uvf                              :  1;
     unsigned      dp6rddsk0uvf                              :  1;
     unsigned      dp6rddsk1uvf                              :  1;
     unsigned      dp7rddsk0uvf                              :  1;
     unsigned      dp7rddsk1uvf                              :  1;
     unsigned      dp8rddsk0uvf                              :  1;
     unsigned      dp8rddsk1uvf                              :  1;
     unsigned      rsvd3118                                  : 14;
#endif
} ncp_phy_CFG_SYSMEM_PHY_RDDSKWSTAT_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_RDDSKWFATALSTAT_r_t
 *  @brief CFG_SYSMEM_PHY_RDDSKWFATALSTAT
 *  @details This register provides status for the read leveling state machine with bit de-skew turned on. If one of these bits are set, then read DQ delay overflowed and did not detect a transition in the DQ lines. This could be related to the training patterns which need transitions in every bit.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_RDDSKWFATALSTAT_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3118 </td>
 *     <td width="20%" align="center"> 14 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp8rddsk1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> DP8 Rd Deskew Upper Nibble Delay Ovf: 1 - deskew delay
 *        overflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp8rddsk0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DP8 Rd Deskew Lower Nibble Delay Ovf: 1 - deskew delay
 *        overflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp7rddsk1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> DP7 Rd Deskew Upper Nibble Delay Ovf: 1 - deskew delay
 *        overflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp7rddsk0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> DP7 Rd Deskew Lower Nibble Delay Ovf: 1 - deskew delay
 *        overflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp6rddsk1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> DP6 Rd Deskew Upper Nibble Delay Ovf: 1 - deskew delay
 *        overflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp6rddsk0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> DP6 Rd Deskew Lower Nibble Delay Ovf: 1 - deskew delay
 *        overflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp5rddsk1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> DP5 Rd Deskew Upper Nibble Delay Ovf: 1 - deskew delay
 *        overflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp5rddsk0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> DP5 Rd Deskew Lower Nibble Delay Ovf: 1 - deskew delay
 *        overflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp4rddsk1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> DP4 Rd Deskew Upper Nibble Delay Ovf: 1 - deskew delay
 *        overflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp4rddsk0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DP4 Rd Deskew Lower Nibble Delay Ovf: 1 - deskew delay
 *        overflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp3rddsk1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> DP3 Rd Deskew Upper Nibble Delay Ovf: 1 - deskew delay
 *        overflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp3rddsk0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> DP3 Rd Deskew Lower Nibble Delay Ovf: 1 - deskew delay
 *        overflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp2rddsk1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> DP2 Rd Deskew Upper Nibble Delay Ovf: 1 - deskew delay
 *        overflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp2rddsk0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> DP2 Rd Deskew Lower Nibble Delay Ovf: 1 - deskew delay
 *        overflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp1rddsk1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> DP1 Rd Deskew Upper Nibble Delay Ovf: 1 - deskew delay
 *        overflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp1rddsk0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> DP1 Rd Deskew Lower Nibble Delay Ovf: 1 - deskew delay
 *        overflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp0rddsk1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> DP0 Rd Deskew Upper Nibble Delay Ovf: 1 - deskew delay
 *        overflow during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp0rddsk0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DP0 Rd Deskew Lower Nibble Delay Ovf: 1 - deskew delay
 *        overflow during read leveling.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_RDDSKWFATALSTAT_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3118                                  : 14;
     unsigned      dp8rddsk1ovf                              :  1;
     unsigned      dp8rddsk0ovf                              :  1;
     unsigned      dp7rddsk1ovf                              :  1;
     unsigned      dp7rddsk0ovf                              :  1;
     unsigned      dp6rddsk1ovf                              :  1;
     unsigned      dp6rddsk0ovf                              :  1;
     unsigned      dp5rddsk1ovf                              :  1;
     unsigned      dp5rddsk0ovf                              :  1;
     unsigned      dp4rddsk1ovf                              :  1;
     unsigned      dp4rddsk0ovf                              :  1;
     unsigned      dp3rddsk1ovf                              :  1;
     unsigned      dp3rddsk0ovf                              :  1;
     unsigned      dp2rddsk1ovf                              :  1;
     unsigned      dp2rddsk0ovf                              :  1;
     unsigned      dp1rddsk1ovf                              :  1;
     unsigned      dp1rddsk0ovf                              :  1;
     unsigned      dp0rddsk1ovf                              :  1;
     unsigned      dp0rddsk0ovf                              :  1;
#else    /* Little Endian */
     unsigned      dp0rddsk0ovf                              :  1;
     unsigned      dp0rddsk1ovf                              :  1;
     unsigned      dp1rddsk0ovf                              :  1;
     unsigned      dp1rddsk1ovf                              :  1;
     unsigned      dp2rddsk0ovf                              :  1;
     unsigned      dp2rddsk1ovf                              :  1;
     unsigned      dp3rddsk0ovf                              :  1;
     unsigned      dp3rddsk1ovf                              :  1;
     unsigned      dp4rddsk0ovf                              :  1;
     unsigned      dp4rddsk1ovf                              :  1;
     unsigned      dp5rddsk0ovf                              :  1;
     unsigned      dp5rddsk1ovf                              :  1;
     unsigned      dp6rddsk0ovf                              :  1;
     unsigned      dp6rddsk1ovf                              :  1;
     unsigned      dp7rddsk0ovf                              :  1;
     unsigned      dp7rddsk1ovf                              :  1;
     unsigned      dp8rddsk0ovf                              :  1;
     unsigned      dp8rddsk1ovf                              :  1;
     unsigned      rsvd3118                                  : 14;
#endif
} ncp_phy_CFG_SYSMEM_PHY_RDDSKWFATALSTAT_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_RDLVLSTATNEDGE_r_t
 *  @brief CFG_SYSMEM_PHY_RDLVLSTATNEDGE
 *  @details This register provides read eye centering overflow status for all DP hardmacros. This status is generated by the read leveling state machine. The overflow status is reported for read eye centering performed for the negative edge of DQS as indicated by the rdlvledge bit in the phyconfig1 register of the dfi_rdlvl_edge DFI input. Read DQS delay overflowed and did not find the correct DQS centering during the read eye or data eye centering. These bits provide the status of the latest read leveling.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_RDLVLSTATNEDGE_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3118 </td>
 *     <td width="20%" align="center"> 14 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp8rdndqs1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> DP8 Rd DQS1 N Dly Ovf: 1 - no center found for DQS
 *        n edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp8rdndqs0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DP8 Rd DQS0 N Dly Ovf: 1 - no center found for DQS
 *        n edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp7rdndqs1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> DP7 Rd DQS1 N Dly Ovf: 1 - no center found for DQS
 *        n edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp7rdndqs0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> DP7 Rd DQS0 N Dly Ovf: 1 - no center found for DQS
 *        n edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp6rdndqs1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> DP6 Rd DQS1 N Dly Ovf: 1 - no center found for DQS
 *        n edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp6rdndqs0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> DP6 Rd DQS0 N Dly Ovf: 1 - no center found for DQS
 *        n edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp5rdndqs1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> DP5 Rd DQS1 N Dly Ovf: 1 - no center found for DQS
 *        n edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp5rdndqs0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> DP5 Rd DQS0 N Dly Ovf: 1 - no center found for DQS
 *        n edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp4rdndqs1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> DP4 Rd DQS1 N Dly Ovf: 1 - no center found for DQS
 *        n edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp4rdndqs0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DP4 Rd DQS0 N Dly Ovf: 1 - no center found for DQS
 *        n edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp3rdndqs1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> DP3 Rd DQS1 N Dly Ovf: 1 - no center found for DQS
 *        n edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp3rdndqs0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> DP3 Rd DQS0 N Dly Ovf: 1 - no center found for DQS
 *        n edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp2rdndqs1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> DP2 Rd DQS1 N Dly Ovf: 1 - no center found for DQS
 *        n edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp2rdndqs0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> DP2 Rd DQS0 N Dly Ovf: 1 - no center found for DQS
 *        n edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp1rdndqs1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> DP1 Rd DQS1 N Dly Ovf: 1 - no center found for DQS
 *        n edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp1rdndqs0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> DP1 Rd DQS0 N Dly Ovf: 1 - no center found for DQS
 *        n edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp0rdndqs1ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> DP0 Rd DQS1 N Dly Ovf: 1 - no center found for DQS
 *        n edge during read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp0rdndqs0ovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DP0 Rd DQS0 N Dly Ovf: 1 - no center found for DQS
 *        n edge during read leveling.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_RDLVLSTATNEDGE_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3118                                  : 14;
     unsigned      dp8rdndqs1ovf                             :  1;
     unsigned      dp8rdndqs0ovf                             :  1;
     unsigned      dp7rdndqs1ovf                             :  1;
     unsigned      dp7rdndqs0ovf                             :  1;
     unsigned      dp6rdndqs1ovf                             :  1;
     unsigned      dp6rdndqs0ovf                             :  1;
     unsigned      dp5rdndqs1ovf                             :  1;
     unsigned      dp5rdndqs0ovf                             :  1;
     unsigned      dp4rdndqs1ovf                             :  1;
     unsigned      dp4rdndqs0ovf                             :  1;
     unsigned      dp3rdndqs1ovf                             :  1;
     unsigned      dp3rdndqs0ovf                             :  1;
     unsigned      dp2rdndqs1ovf                             :  1;
     unsigned      dp2rdndqs0ovf                             :  1;
     unsigned      dp1rdndqs1ovf                             :  1;
     unsigned      dp1rdndqs0ovf                             :  1;
     unsigned      dp0rdndqs1ovf                             :  1;
     unsigned      dp0rdndqs0ovf                             :  1;
#else    /* Little Endian */
     unsigned      dp0rdndqs0ovf                             :  1;
     unsigned      dp0rdndqs1ovf                             :  1;
     unsigned      dp1rdndqs0ovf                             :  1;
     unsigned      dp1rdndqs1ovf                             :  1;
     unsigned      dp2rdndqs0ovf                             :  1;
     unsigned      dp2rdndqs1ovf                             :  1;
     unsigned      dp3rdndqs0ovf                             :  1;
     unsigned      dp3rdndqs1ovf                             :  1;
     unsigned      dp4rdndqs0ovf                             :  1;
     unsigned      dp4rdndqs1ovf                             :  1;
     unsigned      dp5rdndqs0ovf                             :  1;
     unsigned      dp5rdndqs1ovf                             :  1;
     unsigned      dp6rdndqs0ovf                             :  1;
     unsigned      dp6rdndqs1ovf                             :  1;
     unsigned      dp7rdndqs0ovf                             :  1;
     unsigned      dp7rdndqs1ovf                             :  1;
     unsigned      dp8rdndqs0ovf                             :  1;
     unsigned      dp8rdndqs1ovf                             :  1;
     unsigned      rsvd3118                                  : 14;
#endif
} ncp_phy_CFG_SYSMEM_PHY_RDLVLSTATNEDGE_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_RDLVLCONFIG_r_t
 *  @brief CFG_SYSMEM_PHY_RDLVLCONFIG
 *  @details This register provides configuration for the read leveling state machine.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_RDLVLCONFIG_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3122 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvlnib </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Rdlvl Nibble: If rdlvlnibblemode is 0, then this bit
 *        determines which DQS nibble the RLSM works on. 0 -
 *        lower nibble, 1 - upper nibble.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvledge </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Rdlvl Edge: If rdlvlautoedgemode is 0, then this bit
 *        determines which DQS edge the RLSM works on. 0 - P
 *        edge, 1 - N edge.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd19 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvlnibblemode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Rdlvl Auto Nibble Mode: 1 - The RLSM completes DQS
 *        centering on both the upper and lower data nibbles,
 *        0 - The RLSM only completes DQS centering on the nibble
 *        specified by the RDLVL_NIBBLE bit setting.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvlautoedgemode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Rdlvl Auto Edge Mode: 1 - The RLSM completes DQS centering
 *        on both the P and N edges, 0 - The RLSM only completes
 *        DQS centering on the DQS edge specified by the RDLVL_EDGE
 *        bit setting.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvlbc4mode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Rdlvl BC4 Mode: 1 - BC4 bursts used for read leveling,
 *        0 - BL8 bursts used for read leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd15 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_jmp_taps </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> The RLSM uses a binary search algorithm. This value
 *        determines the initial jump size. A default value
 *        of 3 should work for the highest frequency. For lower
 *        frequencies, increase the jump size to speed up the
 *        RLSM.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd11 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param minrdeyewin </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Min Readeye Window: This field is used to validate
 *        the eye opening during read leveling or data eye centering.
 *        State machine makes sure that eye is open that long
 *        before it can find the Pass to Fail point.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param numsamples </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Num Samples: This value is used by read leveling and
 *        deskew state machines to perform how many consecutive
 *        samples read/sampled data should be passed before
 *        declaring it as Pass. Used to filter out jitter and
 *        do better centering.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_RDLVLCONFIG_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3122                                  : 10;
     unsigned      rdlvlnib                                  :  1;
     unsigned      rdlvledge                                 :  1;
     unsigned      rsvd19                                    :  1;
     unsigned      rdlvlnibblemode                           :  1;
     unsigned      rdlvlautoedgemode                         :  1;
     unsigned      rdlvlbc4mode                              :  1;
     unsigned      rsvd15                                    :  1;
     unsigned      rdlvl_jmp_taps                            :  3;
     unsigned      rsvd11                                    :  1;
     unsigned      minrdeyewin                               :  3;
     unsigned      numsamples                                :  8;
#else    /* Little Endian */
     unsigned      numsamples                                :  8;
     unsigned      minrdeyewin                               :  3;
     unsigned      rsvd11                                    :  1;
     unsigned      rdlvl_jmp_taps                            :  3;
     unsigned      rsvd15                                    :  1;
     unsigned      rdlvlbc4mode                              :  1;
     unsigned      rdlvlautoedgemode                         :  1;
     unsigned      rdlvlnibblemode                           :  1;
     unsigned      rsvd19                                    :  1;
     unsigned      rdlvledge                                 :  1;
     unsigned      rdlvlnib                                  :  1;
     unsigned      rsvd3122                                  : 10;
#endif
} ncp_phy_CFG_SYSMEM_PHY_RDLVLCONFIG_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_RDLVLCMPDATEVN_r_t
 *  @brief CFG_SYSMEM_PHY_RDLVLCMPDATEVN
 *  @details This register provides the read leveling state machine a compare value for data read during positive edge read leveling or read eye centering..
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_RDLVLCMPDATEVN_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdcmpdatevn3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Read Compare Data Even from 4th positive edge </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdcmpdatevn2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Read Compare Data Even from 3rd positive edge </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdcmpdatevn1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Read Compare Data Even from 2nd positive edge </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdcmpdatevn0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Read Compare Data Even from 1st positive edge </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_RDLVLCMPDATEVN_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdcmpdatevn3                              :  8;
     unsigned      rdcmpdatevn2                              :  8;
     unsigned      rdcmpdatevn1                              :  8;
     unsigned      rdcmpdatevn0                              :  8;
#else    /* Little Endian */
     unsigned      rdcmpdatevn0                              :  8;
     unsigned      rdcmpdatevn1                              :  8;
     unsigned      rdcmpdatevn2                              :  8;
     unsigned      rdcmpdatevn3                              :  8;
#endif
} ncp_phy_CFG_SYSMEM_PHY_RDLVLCMPDATEVN_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_RDLVLCMPDATODD_r_t
 *  @brief CFG_SYSMEM_PHY_RDLVLCMPDATODD
 *  @details This register provides the read leveling state machine a compare value for data read during negative edge read leveling or read eye centering.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_RDLVLCMPDATODD_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdcmpdatodd3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Read Compare Data Odd from 4th negative edge </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdcmpdatodd2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Read Compare Data Odd from 3rd negative edge </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdcmpdatodd1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Read Compare Data Odd from 2nd negative edge </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdcmpdatodd0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Read Compare Data Odd from 1st negative edge </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_RDLVLCMPDATODD_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rdcmpdatodd3                              :  8;
     unsigned      rdcmpdatodd2                              :  8;
     unsigned      rdcmpdatodd1                              :  8;
     unsigned      rdcmpdatodd0                              :  8;
#else    /* Little Endian */
     unsigned      rdcmpdatodd0                              :  8;
     unsigned      rdcmpdatodd1                              :  8;
     unsigned      rdcmpdatodd2                              :  8;
     unsigned      rdcmpdatodd3                              :  8;
#endif
} ncp_phy_CFG_SYSMEM_PHY_RDLVLCMPDATODD_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG2_r_t
 *  @brief CFG_SYSMEM_PHY_PHYCONFIG2
 *  @details This register provides static configuration of the PHY.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG2_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param clrfifo </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Clear FIFO: 1 - reset the write and read pointers
 *        of the read FIFO inside the PHY. NOTE: this is a self-clearing
 *        bit.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fifomode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> FIFO Mode: 0 - configures the read FIFO in self drain
 *        FIFO mode, 1 - ??????
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fifoena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> FIFO Enable: This is a clk gating control bit to the
 *        read FIFO and latency logic within the PHY. 1 - enables
 *        the read data FIFO, gate latency delay block, and
 *        fixed latency delay block within the PHY, 0 - power
 *        savings when no read or write commands are being issued.
 *        NOTE: set this bit high during gate training.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvlfifomode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Rdlvl FIFO Mode: 0 - normal operation, 1 - the read
 *        data FIFO will only accept data from a single read
 *        command that comes after the rdlvlenard bit is set.
 *        Set this bit when read data is to be accessed through
 *        the PHY register interface (used for data eye training
 *        in DFI PHY Eval Mode).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvlenard </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Rdlvl Allow Rd: When rdlvlfifomode=1, then this bit
 *        controls the read gate signal. 1 - allow data from
 *        the next read command to enter the FIFO. NOTE: this
 *        is a self-clearing bit.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fixlatfifoena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Fixed Latency FIFO Ena: 1 - configures the read FIFO
 *        in fixed latency drain FIFO mode, 0 - configures the
 *        read FIFO in manual drain FIFO mode.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdrankmap </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Rd Rank Map: </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrrankmap </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Wr Rank Map: </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param freqchanprotoena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Freq Change Protocol Ena: 1 - Enables PHY to support
 *        DFI2.1 frequency change protocol request initiated
 *        by the memory controller, 0 - PHY ignores any frequency
 *        change request.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp8ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> DP8 Enable: 1 - allow state machines to operate on
 *        this hardmacro, 0 - disable state machines on this
 *        hardmacro.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp7ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> DP7 Enable: 1 - allow state machines to operate on
 *        this hardmacro, 0 - disable state machines on this
 *        hardmacro.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp6ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> DP6 Enable: 1 - allow state machines to operate on
 *        this hardmacro, 0 - disable state machines on this
 *        hardmacro.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp5ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> DP5 Enable: 1 - allow state machines to operate on
 *        this hardmacro, 0 - disable state machines on this
 *        hardmacro.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp4ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DP4 Enable: 1 - allow state machines to operate on
 *        this hardmacro, 0 - disable state machines on this
 *        hardmacro.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp3ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> DP3 Enable: 1 - allow state machines to operate on
 *        this hardmacro, 0 - disable state machines on this
 *        hardmacro.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp2ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> DP2 Enable: 1 - allow state machines to operate on
 *        this hardmacro, 0 - disable state machines on this
 *        hardmacro.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp1ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> DP1 Enable: 1 - allow state machines to operate on
 *        this hardmacro, 0 - disable state machines on this
 *        hardmacro.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dp0ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> DP0 Enable: 1 - allow state machines to operate on
 *        this hardmacro, 0 - disable state machines on this
 *        hardmacro.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dfimanwrlvl </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> DFI Manual Wrlvl: 1 - In DFI PHY Eval Mode, prevents
 *        the write leveling state machine from automatically
 *        running so that write leveling can be performed by
 *        firmware.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dfimangt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> DFI Manual Gate Train: 1 - In DFI PHY Eval Mode, prevents
 *        the gate training state machine from automatically
 *        running so that gate training can be performed by
 *        firmware.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dfimanrdlvl </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> DFI Manual Rdlvl: 1 - In DFI PHY Eval Mode, prevents
 *        the read leveling state machine from automatically
 *        running so that read leveling can be performed by
 *        firmware.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vtmargin </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> VT Margin: 1 - Allows the gate training state machine
 *        to have additional margin for VT compensation process.
 *        Typically, there is no need for additional margin.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dfi_bitdskw_ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> When the RLSM is used in DFI training PHY eval mode,
 *        set this bit to 1 to let the RLSM run read bit de-skew
 *        along with DQS centering. Use this feature only if
 *        the training pattern toggles all DQ bits.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fbgating </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> FB Gating: When the feedback state machine runs, it
 *        takes a reference measurement for later gate tracking.
 *        If this bit is set, the FBSM also programs the rank0
 *        read gate delay in each DP8 hardmacro.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rstnio </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> RSTN IO: 1 - Explicitly forces the IO on the ADR hardmacro
 *        to its initial reset states. This bit is ANDed with
 *        RSTN_IO_IN and a delayed version of RSTN.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param frcinit </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Force Init: 1 - Forces re-initialization of the internal
 *        state machines. This bit performs a soft reset type
 *        of function to the internal state machines which unconditionally
 *        jump back to the initial state.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odtoff </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> ODT Off: 1 - disable dynamic control of ODT and permanently
 *        disable ODT of the I/O buffer, 0 - allow dynamic on-die
 *        termination control to the PHY I/O buffers. The DP
 *        hardmacro automatically turns on ODT of the I/O receiver
 *        on memory reads. It turns off ODT automatically after
 *        memory reads. (see also dpconfig0[13] override dynamic
 *        ODT)
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dfiwrlvlphymode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> DFI Wrlvl PHY Mode: 1 - Write leveling performed in
 *        PHY Eval Mode, 0 - write leveling performed in MC
 *        Eval Mode.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dfigttrainmode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> DFI Gate Train PHY Mode: 1 - Gate training performed
 *        in PHY Eval Mode, 0 - gate training performed in MC
 *        Eval Mode.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dfirdlvlphymode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DFI Rdlvl PHY Mode: 1 - Read leveling performed in
 *        PHY Eval Mode, 0 - read leveling performed in MC Eval
 *        Mode.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG2_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      clrfifo                                   :  1;
     unsigned      fifomode                                  :  1;
     unsigned      fifoena                                   :  1;
     unsigned      rdlvlfifomode                             :  1;
     unsigned      rdlvlenard                                :  1;
     unsigned      fixlatfifoena                             :  1;
     unsigned      rdrankmap                                 :  2;
     unsigned      wrrankmap                                 :  2;
     unsigned      freqchanprotoena                          :  1;
     unsigned      dpen                                      :  9;
     unsigned      dfimanwrlvl                               :  1;
     unsigned      dfimangt                                  :  1;
     unsigned      dfimanrdlvl                               :  1;
     unsigned      vtmargin                                  :  1;
     unsigned      dfi_bitdskw_ena                           :  1;
     unsigned      fbgating                                  :  1;
     unsigned      rstnio                                    :  1;
     unsigned      frcinit                                   :  1;
     unsigned      odtoff                                    :  1;
     unsigned      dfiwrlvlphymode                           :  1;
     unsigned      dfigttrainmode                            :  1;
     unsigned      dfirdlvlphymode                           :  1;
#else    /* Little Endian */
     unsigned      dfirdlvlphymode                           :  1;
     unsigned      dfigttrainmode                            :  1;
     unsigned      dfiwrlvlphymode                           :  1;
     unsigned      odtoff                                    :  1;
     unsigned      frcinit                                   :  1;
     unsigned      rstnio                                    :  1;
     unsigned      fbgating                                  :  1;
     unsigned      dfi_bitdskw_ena                           :  1;
     unsigned      vtmargin                                  :  1;
     unsigned      dfimanrdlvl                               :  1;
     unsigned      dfimangt                                  :  1;
     unsigned      dfimanwrlvl                               :  1;
     unsigned      dpen                                      :  9;
     unsigned      freqchanprotoena                          :  1;
     unsigned      wrrankmap                                 :  2;
     unsigned      rdrankmap                                 :  2;
     unsigned      fixlatfifoena                             :  1;
     unsigned      rdlvlenard                                :  1;
     unsigned      rdlvlfifomode                             :  1;
     unsigned      fifoena                                   :  1;
     unsigned      fifomode                                  :  1;
     unsigned      clrfifo                                   :  1;
#endif
} ncp_phy_CFG_SYSMEM_PHY_PHYCONFIG2_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_SMCTRL_r_t
 *  @brief CFG_SYSMEM_PHY_SMCTRL
 *  @details This register provides control for the initialization and tracking state machines as well as DFI training.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_SMCTRL_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3126 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clrfreqchng </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Clear Frequency Change: This bit only applies when
 *        autorestart=0. When this bit is 1, the hardware generates
 *        dfi_init_complete. Firmware should set this bit after
 *        it has performed all the initialization steps after
 *        the frequency has been changed.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd2419 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clrwrlvl </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Clear Wrlvl: In DFI2.0 PHY Eval mode, this bit controls
 *        the dfi_wrlvl_resp outputs. Set this bit to 1 to issue
 *        dfi_wrlvl_resp, signaling that the PHY has finished
 *        with write leveling. The memory controller will then
 *        deassert dfi_wrlvl_en. When dfi_wrlvl_en is deasserted,
 *        then dfi_wrlvl_resp is deasserted and this bit will
 *        self-clear.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clrgt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Clear Gate: In DFI2.0 PHY Eval mode, this bit controls
 *        the dfi_rdlvl_resp outputs. Set this bit to 1 to issue
 *        dfi_rdlvl_resp, signaling that the PHY has finished
 *        with gate training. The memory controller will then
 *        deassert dfi_rdlvl_gate_en. When dfi_rdlvl_gate_en
 *        is deasserted, then dfi_rdlvl_resp is deasserted and
 *        this bit will self-clear.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clrrdlvl </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Clear Rdlvl: In DFI2.0 PHY Eval mode, this bit controls
 *        the dfi_rdlvl_resp outputs. Set this bit to 1 to issue
 *        dfi_rdlvl_resp, signaling that the PHY has finished
 *        with read leveling. The memory controller will then
 *        deassert dfi_rdlvl_en. When dfi_rdlvl_en is deasserted,
 *        then dfi_rdlvl_resp is deasserted and this bit will
 *        self-clear.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param autorestart </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> DFI Auto Restart: This bit only applies when freqchanprotoena=1.
 *        When the PHY acknowledge frequency change requested
 *        by the memory controller and this bit is set, after
 *        the frequency is changed the PHY will automatically
 *        reload the initial setting of smcontrol register and
 *        start initialization. Once done, it asserts dfi_init_complete
 *        signal. If this bit is 0 then the PHY will not start
 *        re-initialization and wait for firmware interaction.
 *        Once firmware performs all necessary tasks (quarter
 *        cycle initialization, etc) it should set the clrfreqchng
 *        bit to assert dfi_init_complete.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd1411 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param initqrtr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Init Quarter Train: 1 - starts the read clock path
 *        quarter cycle delay initialization state machine.
 *        NOTE: when all DP8 hardmacro read DQS delay cells
 *        have been set, then this bit will self-clear.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param initfb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Init Feedback Train: 1 - starts the feedback read
 *        gate initialization state machine. NOTE: when the
 *        state machine is finished, then this bit will self-clear.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param initwrlvl </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Init Wrlvl Train: 1 - starts the write leveling state
 *        machine. NOTE: when the state machine is finished
 *        and all DP8 hardmacro write DQS delays (for the selected
 *        rank) are loaded, then this bit will self-clear.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param initgt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Init Gate Train: 1 - starts the gate training state
 *        machine. NOTE: when the state machine is finished
 *        and all DP8 hardmacro read DQS gate delays (for the
 *        selected rank) are loaded, then this bit will self-clear.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param initrdsq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Init Rd Deskew Train: 1 - starts the read bit de-skew
 *        state machine. NOTE: when the state machine is finished
 *        and all DP8 hardmacro read bit alignment registers
 *        (for the selected rank) are loaded, then this bit
 *        will self-clear.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param initrdlvl </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Init Rdlvl Train: 1 - starts the read leveling state
 *        machine (data eye centering). NOTE: when the state
 *        machine is finished and all DP8 hardmacro read DQS
 *        delays (for the selected rank) are loaded, then this
 *        bit will self-clear.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param initdfitrain </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Init DFI Train: 1 - allow DFI training to proceed.
 *        NOTE: when the DFI update request has been received
 *        from the memory controller, then this bit will self-clear.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param initratiotrain </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Init Ratio Train: 1 - calculate ratio values for tracking.
 *        This comes after DFI training since it will use the
 *        DFI result in the ratio. NOTE: this bit self-clears
 *        after the calculation is complete.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trackqrtr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Track Quarter Cycle: 0 - stop quarter cycle VT tracking,
 *        1 - start quarter cycle VT tracking.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tracklp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Track Loop: 0 - stop read DQS gate VT tracking by
 *        the feedback state machine, 1 - start read DQS gate
 *        VT tracking by the feedback state machine.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vtccntena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> VTC Count Enable: 0 - holds the VTC (Voltage Temperature
 *        Compensation) state machine in the Wait VT state,
 *        1 - allows the VTC to exit the Wait VT state.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_SMCTRL_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3126                                  :  6;
     unsigned      clrfreqchng                               :  1;
     unsigned      rsvd2419                                  :  6;
     unsigned      clrwrlvl                                  :  1;
     unsigned      clrgt                                     :  1;
     unsigned      clrrdlvl                                  :  1;
     unsigned      autorestart                               :  1;
     unsigned      rsvd1411                                  :  4;
     unsigned      initqrtr                                  :  1;
     unsigned      initfb                                    :  1;
     unsigned      initwrlvl                                 :  1;
     unsigned      initgt                                    :  1;
     unsigned      initrdsq                                  :  1;
     unsigned      initrdlvl                                 :  1;
     unsigned      initdfitrain                              :  1;
     unsigned      initratiotrain                            :  1;
     unsigned      trackqrtr                                 :  1;
     unsigned      tracklp                                   :  1;
     unsigned      vtccntena                                 :  1;
#else    /* Little Endian */
     unsigned      vtccntena                                 :  1;
     unsigned      tracklp                                   :  1;
     unsigned      trackqrtr                                 :  1;
     unsigned      initratiotrain                            :  1;
     unsigned      initdfitrain                              :  1;
     unsigned      initrdlvl                                 :  1;
     unsigned      initrdsq                                  :  1;
     unsigned      initgt                                    :  1;
     unsigned      initwrlvl                                 :  1;
     unsigned      initfb                                    :  1;
     unsigned      initqrtr                                  :  1;
     unsigned      rsvd1411                                  :  4;
     unsigned      autorestart                               :  1;
     unsigned      clrrdlvl                                  :  1;
     unsigned      clrgt                                     :  1;
     unsigned      clrwrlvl                                  :  1;
     unsigned      rsvd2419                                  :  6;
     unsigned      clrfreqchng                               :  1;
     unsigned      rsvd3126                                  :  6;
#endif
} ncp_phy_CFG_SYSMEM_PHY_SMCTRL_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_STAT_r_t
 *  @brief CFG_SYSMEM_PHY_STAT
 *  @details This register provides status on the PHY internal state machines and the DFI training interface.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_STAT_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3127 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Reserved. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param waitphyfreqchng </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Wait PHY Frequency Change: frequency change request
 *        is received from the memory controller, PHY responded
 *        with acknowledgement and is waiting for the frequency
 *        change to occur.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param freqchnginit </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Frequency Change Init: PHY initialization is in progress
 *        after a frequency change.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dfiwrlvlcsn </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> DFI Wrlvl CSN: indicates which of the write leveling
 *        chip selects is active.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dfirdlvlcsn </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> DFI Rdlvl CSN: indicates which of the read leveling
 *        chip selects is active.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dfiwrlvl </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> DFI Wrlvl: indicates that the memory controller is
 *        requesting write leveling from the PHY.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dfigate </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> DFI Rdlvl Gate: indicates that the memory controller
 *        is requesting gate training from the PHY.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dfirdlvl </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DFI Rdlvl: indicates that the memory controller is
 *        requesting read leveling from the PHY.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd1511 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param qrtractive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Quarter Active: indicates that the quarter cycle initialization
 *        state machine is running.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fbactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> FB Active: indicates that the feedback read gate initialization
 *        state machine is running.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvlactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Wrlvl Active: indicates that the write leveling state
 *        machine is running.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gateactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Gate Train Active: indicates that the read DQS gating
 *        delay initialization state machine is running.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rddskactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Rd Deskew Active: indicates that the read deskew or
 *        bit alignment state machine is running.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvlactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Rdlvl Active: indicates that the read leveling or
 *        read data eye centering state machine is running.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dfiactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> DFI Active: indicates that the SM control is in the
 *        init DFI state and DFI training may begin.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ratioactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Ratio Active: indicates that the delay ratio state
 *        machine is running.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trackqrtractive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Track Quarter Cycle Active: indicates that the quarter
 *        cycle delay tracking state machine is running.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tracklpactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Track Loop Active: indicates that the feedback read
 *        gate tracking state machine is running.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vtccntactive </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> VTC Count Active: indicates that the SM control is
 *        in the Wait VT state.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_STAT_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3127                                  :  5;
     unsigned      waitphyfreqchng                           :  1;
     unsigned      freqchnginit                              :  1;
     unsigned      dfiwrlvlcsn                               :  3;
     unsigned      dfirdlvlcsn                               :  3;
     unsigned      dfiwrlvl                                  :  1;
     unsigned      dfigate                                   :  1;
     unsigned      dfirdlvl                                  :  1;
     unsigned      rsvd1511                                  :  5;
     unsigned      qrtractive                                :  1;
     unsigned      fbactive                                  :  1;
     unsigned      wrlvlactive                               :  1;
     unsigned      gateactive                                :  1;
     unsigned      rddskactive                               :  1;
     unsigned      rdlvlactive                               :  1;
     unsigned      dfiactive                                 :  1;
     unsigned      ratioactive                               :  1;
     unsigned      trackqrtractive                           :  1;
     unsigned      tracklpactive                             :  1;
     unsigned      vtccntactive                              :  1;
#else    /* Little Endian */
     unsigned      vtccntactive                              :  1;
     unsigned      tracklpactive                             :  1;
     unsigned      trackqrtractive                           :  1;
     unsigned      ratioactive                               :  1;
     unsigned      dfiactive                                 :  1;
     unsigned      rdlvlactive                               :  1;
     unsigned      rddskactive                               :  1;
     unsigned      gateactive                                :  1;
     unsigned      wrlvlactive                               :  1;
     unsigned      fbactive                                  :  1;
     unsigned      qrtractive                                :  1;
     unsigned      rsvd1511                                  :  5;
     unsigned      dfirdlvl                                  :  1;
     unsigned      dfigate                                   :  1;
     unsigned      dfiwrlvl                                  :  1;
     unsigned      dfirdlvlcsn                               :  3;
     unsigned      dfiwrlvlcsn                               :  3;
     unsigned      freqchnginit                              :  1;
     unsigned      waitphyfreqchng                           :  1;
     unsigned      rsvd3127                                  :  5;
#endif
} ncp_phy_CFG_SYSMEM_PHY_STAT_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_USRSYSCODE_r_t
 *  @brief CFG_SYSMEM_PHY_USRSYSCODE
 *  @details This register provides a means for firmware to read the version of the Coreware elements.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_USRSYSCODE_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param syscode </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> System Code: This field is a static readable representation
 *        of the parameter P708_SYSTEM_CODE. The default value
 *        is the last 4 digits of the Coreware number of this
 *        PHY in binary coded decimal format (0708).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param phyvers </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PHY Version: This field is a static readable representation
 *        of the parameter P708_PHY_VERSION. The default value
 *        is the version number of this PHY in binary coded
 *        decimal format (01.00 for version 1.0).
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_USRSYSCODE_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      syscode                                   : 16;
     unsigned      phyvers                                   : 16;
#else    /* Little Endian */
     unsigned      phyvers                                   : 16;
     unsigned      syscode                                   : 16;
#endif
} ncp_phy_CFG_SYSMEM_PHY_USRSYSCODE_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_PVTCONFIG0_r_t
 *  @brief CFG_SYSMEM_PHY_PVTCONFIG0
 *  @details This register provides control to the external PVT cell(s) for the PHY.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_PVTCONFIG0_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3126 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt0crp </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> PVT0 CRP: CRP status bits from external PVT cell 0.
 *        NOTE: read only.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt0crn </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> PVT0 CRN: CRN status bits from external PVT cell 0.
 *        NOTE: read only.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd15 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvtdfiautoupd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> PVT DFI Auto Update: 1 - toggles CKEXT for every DFI
 *        update request.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt0selextpvt0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> PVT0 SELEXTPVT[0]: drives SELEXTPVT output to external
 *        PVT cell.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt0vselextck0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> PVT0 VSELEXTCK[0]: drives VSELEXTCK output to external
 *        PVT cell.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt0lp0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> PVT0 LP[0]: drives LP output to external PVT cell. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt0crp4ext0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> PVT0 CRP4EXT[0]: drives CRP4EXT output to external
 *        PVT cell.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt0crp3ext0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> PVT0 CRP3EXT[0]: drives CRP3EXT output to external
 *        PVT cell.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt0crp2ext0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> PVT0 CRP2EXT[0]: drives CRP2EXT output to external
 *        PVT cell.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt0crp1ext0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> PVT0 CRP1EXT[0]: drives CRP1EXT output to external
 *        PVT cell.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt0crp0ext0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> PVT0 CRP0EXT[0]: drives CRP0EXT output to external
 *        PVT cell.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt0crn4ext0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> PVT0 CRN4EXT[0]: drives CRN4EXT output to external
 *        PVT cell.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt0crn3ext0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> PVT0 CRN3EXT[0]: drives CRN3EXT output to external
 *        PVT cell.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt0crn2ext0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> PVT0 CRN2EXT[0]: drives CRN2EXT output to external
 *        PVT cell.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt0crn1ext0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> PVT0 CRN1EXT[0]: drives CRN1EXT output to external
 *        PVT cell.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt0crn0ext0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> PVT0 CRN0EXT[0]: drives CRN0EXT output to external
 *        PVT cell.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt0ckext0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PVT0 CKEXT[0]: drives CKEXT output to external PVT
 *        cell.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_PVTCONFIG0_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3126                                  :  6;
     unsigned      pvt0crp                                   :  5;
     unsigned      pvt0crn                                   :  5;
     unsigned      rsvd15                                    :  1;
     unsigned      pvtdfiautoupd                             :  1;
     unsigned      pvt0selextpvt0                            :  1;
     unsigned      pvt0vselextck0                            :  1;
     unsigned      pvt0lp0                                   :  1;
     unsigned      pvt0crp4ext0                              :  1;
     unsigned      pvt0crp3ext0                              :  1;
     unsigned      pvt0crp2ext0                              :  1;
     unsigned      pvt0crp1ext0                              :  1;
     unsigned      pvt0crp0ext0                              :  1;
     unsigned      pvt0crn4ext0                              :  1;
     unsigned      pvt0crn3ext0                              :  1;
     unsigned      pvt0crn2ext0                              :  1;
     unsigned      pvt0crn1ext0                              :  1;
     unsigned      pvt0crn0ext0                              :  1;
     unsigned      pvt0ckext0                                :  1;
#else    /* Little Endian */
     unsigned      pvt0ckext0                                :  1;
     unsigned      pvt0crn0ext0                              :  1;
     unsigned      pvt0crn1ext0                              :  1;
     unsigned      pvt0crn2ext0                              :  1;
     unsigned      pvt0crn3ext0                              :  1;
     unsigned      pvt0crn4ext0                              :  1;
     unsigned      pvt0crp0ext0                              :  1;
     unsigned      pvt0crp1ext0                              :  1;
     unsigned      pvt0crp2ext0                              :  1;
     unsigned      pvt0crp3ext0                              :  1;
     unsigned      pvt0crp4ext0                              :  1;
     unsigned      pvt0lp0                                   :  1;
     unsigned      pvt0vselextck0                            :  1;
     unsigned      pvt0selextpvt0                            :  1;
     unsigned      pvtdfiautoupd                             :  1;
     unsigned      rsvd15                                    :  1;
     unsigned      pvt0crn                                   :  5;
     unsigned      pvt0crp                                   :  5;
     unsigned      rsvd3126                                  :  6;
#endif
} ncp_phy_CFG_SYSMEM_PHY_PVTCONFIG0_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_PVTCONFIG1_r_t
 *  @brief CFG_SYSMEM_PHY_PVTCONFIG1
 *  @details This register provides control to the external PVT cell(s) for the PHY.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_PVTCONFIG1_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3126 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt1crp </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> PVT1 CRP: CRP status bits from external PVT cell 1.
 *        NOTE: read only.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt1crn </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> PVT1 CRN: CRN status bits from external PVT cell 1.
 *        NOTE: read only.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd1514 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt1selextpvt1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> PVT1 SELEXTPVT[1]: drives SELEXTPVT output to external
 *        PVT cell.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt1vselextck1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> PVT1 VSELEXTCK[1]: drives VSELEXTCK output to external
 *        PVT cell.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt1lp1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> PVT1 LP[1]: drives LP output to external PVT cell. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt1crp4ext1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> PVT1 CRP4EXT[1]: drives CRP4EXT output to external
 *        PVT cell.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt1crp3ext1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> PVT1 CRP3EXT[1]: drives CRP3EXT output to external
 *        PVT cell.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt1crp2ext1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> PVT1 CRP2EXT[1]: drives CRP2EXT output to external
 *        PVT cell.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt1crp1ext1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> PVT1 CRP1EXT[1]: drives CRP1EXT output to external
 *        PVT cell.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt1crp0ext1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> PVT1 CRP0EXT[1]: drives CRP0EXT output to external
 *        PVT cell.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt1crn4ext1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> PVT1 CRN4EXT[1]: drives CRN4EXT output to external
 *        PVT cell.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt1crn3ext1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> PVT1 CRN3EXT[1]: drives CRN3EXT output to external
 *        PVT cell.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt1crn2ext1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> PVT1 CRN2EXT[1]: drives CRN2EXT output to external
 *        PVT cell.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt1crn1ext1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> PVT1 CRN1EXT[1]: drives CRN1EXT output to external
 *        PVT cell.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt1crn0ext1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> PVT1 CRN0EXT[1]: drives CRN0EXT output to external
 *        PVT cell.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pvt1ckext1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PVT1 CKEXT[1]: drives CKEXT output to external PVT
 *        cell.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_PVTCONFIG1_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3126                                  :  6;
     unsigned      pvt1crp                                   :  5;
     unsigned      pvt1crn                                   :  5;
     unsigned      rsvd1514                                  :  2;
     unsigned      pvt1selextpvt1                            :  1;
     unsigned      pvt1vselextck1                            :  1;
     unsigned      pvt1lp1                                   :  1;
     unsigned      pvt1crp4ext1                              :  1;
     unsigned      pvt1crp3ext1                              :  1;
     unsigned      pvt1crp2ext1                              :  1;
     unsigned      pvt1crp1ext1                              :  1;
     unsigned      pvt1crp0ext1                              :  1;
     unsigned      pvt1crn4ext1                              :  1;
     unsigned      pvt1crn3ext1                              :  1;
     unsigned      pvt1crn2ext1                              :  1;
     unsigned      pvt1crn1ext1                              :  1;
     unsigned      pvt1crn0ext1                              :  1;
     unsigned      pvt1ckext1                                :  1;
#else    /* Little Endian */
     unsigned      pvt1ckext1                                :  1;
     unsigned      pvt1crn0ext1                              :  1;
     unsigned      pvt1crn1ext1                              :  1;
     unsigned      pvt1crn2ext1                              :  1;
     unsigned      pvt1crn3ext1                              :  1;
     unsigned      pvt1crn4ext1                              :  1;
     unsigned      pvt1crp0ext1                              :  1;
     unsigned      pvt1crp1ext1                              :  1;
     unsigned      pvt1crp2ext1                              :  1;
     unsigned      pvt1crp3ext1                              :  1;
     unsigned      pvt1crp4ext1                              :  1;
     unsigned      pvt1lp1                                   :  1;
     unsigned      pvt1vselextck1                            :  1;
     unsigned      pvt1selextpvt1                            :  1;
     unsigned      rsvd1514                                  :  2;
     unsigned      pvt1crn                                   :  5;
     unsigned      pvt1crp                                   :  5;
     unsigned      rsvd3126                                  :  6;
#endif
} ncp_phy_CFG_SYSMEM_PHY_PVTCONFIG1_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DPIOVREFSET_r_t
 *  @brief CFG_SYSMEM_PHY_DPIOVREFSET
 *  @details This register provides control to external VREF cells that are connected to DP8 hardmacros and DP hardmacro I/O settings.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DPIOVREFSET_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3127 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param see_dm </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Controls the single-ended enable bit on all DP hardmacro
 *        DM I/Os. This bit is only used for the DDR23CR I/O
 *        type.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param see_dqs </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Controls the single-ended enable bit on all DP hardmacro
 *        DQS I/Os. This bit is only used for the DDR23CR I/O
 *        type.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dpvrefodtimp </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> DP VREF ODTIMP: drives DP_VREF_ODTIMP output to external
 *        VREF cell(s).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dpvrefodte </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> DP VREF ODTE: drives DP_VREF_ODTE output to external
 *        VREF cell(s).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dpvreflp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> DP VREF LP: drives DP_VREF_LP output to external VREF
 *        cell(s).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dpenivref </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> DP ENIVREF: controls ENIVREF setting on all DP I/Os. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dppu30ke </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> DP PU30KE: controls PU30KE setting on all DP I/Os. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dppd30ke </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> DP PD30KE: controls PD30KE setting on all DP I/Os. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sldm </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> SL DM: controls SL setting on all DP DM I/Os. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sldqs </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> SL DQS: controls SL setting on all DP DQS I/Os. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sldq </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> SL DQ: controls SL setting on all DP DQ I/Os. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odtimpdm </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> ODTIMP DM: controls ODTIMP setting on all DP DM I/Os. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odtimpdqs </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> ODTIMP DQS: controls ODTIMP setting on all DP DQS
 *        I/Os.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odtimpdq </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> ODTIMP DQ: controls ODTIMP setting on all DP DQ I/Os. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param drvdm </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> DRV DM: controls DRV setting on all DP DM I/Os. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param drvdqs </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> DRV DQS: controls DRV setting on all DP DQS I/Os. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param drvdq </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRV DQ: controls DRV setting on all DP DQ I/Os. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_DPIOVREFSET_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3127                                  :  5;
     unsigned      see_dm                                    :  1;
     unsigned      see_dqs                                   :  1;
     unsigned      dpvrefodtimp                              :  2;
     unsigned      dpvrefodte                                :  1;
     unsigned      dpvreflp                                  :  1;
     unsigned      dpenivref                                 :  1;
     unsigned      dppu30ke                                  :  1;
     unsigned      dppd30ke                                  :  1;
     unsigned      sldm                                      :  2;
     unsigned      sldqs                                     :  2;
     unsigned      sldq                                      :  2;
     unsigned      odtimpdm                                  :  2;
     unsigned      odtimpdqs                                 :  2;
     unsigned      odtimpdq                                  :  2;
     unsigned      drvdm                                     :  2;
     unsigned      drvdqs                                    :  2;
     unsigned      drvdq                                     :  2;
#else    /* Little Endian */
     unsigned      drvdq                                     :  2;
     unsigned      drvdqs                                    :  2;
     unsigned      drvdm                                     :  2;
     unsigned      odtimpdq                                  :  2;
     unsigned      odtimpdqs                                 :  2;
     unsigned      odtimpdm                                  :  2;
     unsigned      sldq                                      :  2;
     unsigned      sldqs                                     :  2;
     unsigned      sldm                                      :  2;
     unsigned      dppd30ke                                  :  1;
     unsigned      dppu30ke                                  :  1;
     unsigned      dpenivref                                 :  1;
     unsigned      dpvreflp                                  :  1;
     unsigned      dpvrefodte                                :  1;
     unsigned      dpvrefodtimp                              :  2;
     unsigned      see_dqs                                   :  1;
     unsigned      see_dm                                    :  1;
     unsigned      rsvd3127                                  :  5;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DPIOVREFSET_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_ADRx_ADRIOSET_1ST_r_t
 *  @brief CFG_SYSMEM_PHY_ADRx_ADRIOSET_1ST
 *  @details This register provides control to ADR hardmacro I/O settings. This register is repeated for each individual ADR hardmacro.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_ADRx_ADRIOSET_1ST_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3122 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param adr_vref_odtimp </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Drives the ADR_VREF_ODTIMP output to the external
 *        VREF cells.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param adr_vref_odte </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Drives the ADR_VREF_ODTE output to the external VREF
 *        cells.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param adr_vref_lp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Drives the ADR_VREF_LP output to the external VREF
 *        cells.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param adr_odtimp </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> ODTIMP setting for all of the I/Os on the ADR hardmacro. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd1512 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param adrslck1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> ADR SL CK1: SL setting for one pair of ADR I/Os. ADR12
 *        - bits[11:10], ADR9 - not connected.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param adrslck0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> ADR SL CK0: SL setting for one pair of ADR I/Os. ADR12
 *        - bits[5:4], ADR9 - bits[8:7].
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param adrslac </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> ADR SL AC: SL setting for ADR I/Os not connected to
 *        ADR_SL0_CK0 or ADR_SL0_CK1.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param adrdrvck1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> ADR DRV CK1: DRV setting for one pair of ADR I/Os.
 *        ADR12 - bits[11:10], ADR9 - not connected.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param adrdrvck0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> ADR DRV CK0: DRV setting for one pair of ADR I/Os.
 *        ADR12 - bits[5:4], ADR9 - bits[8:7].
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param adrdrvac </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> ADR DRV AC: DRV setting for ADR I/Os not connected
 *        to ADR_DRV_CK0 or ADR_DRV_CK1.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_ADRx_ADRIOSET_1ST_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3122                                  : 10;
     unsigned      adr_vref_odtimp                           :  2;
     unsigned      adr_vref_odte                             :  1;
     unsigned      adr_vref_lp                               :  1;
     unsigned      adr_odtimp                                :  2;
     unsigned      rsvd1512                                  :  4;
     unsigned      adrslck1                                  :  2;
     unsigned      adrslck0                                  :  2;
     unsigned      adrslac                                   :  2;
     unsigned      adrdrvck1                                 :  2;
     unsigned      adrdrvck0                                 :  2;
     unsigned      adrdrvac                                  :  2;
#else    /* Little Endian */
     unsigned      adrdrvac                                  :  2;
     unsigned      adrdrvck0                                 :  2;
     unsigned      adrdrvck1                                 :  2;
     unsigned      adrslac                                   :  2;
     unsigned      adrslck0                                  :  2;
     unsigned      adrslck1                                  :  2;
     unsigned      rsvd1512                                  :  4;
     unsigned      adr_odtimp                                :  2;
     unsigned      adr_vref_lp                               :  1;
     unsigned      adr_vref_odte                             :  1;
     unsigned      adr_vref_odtimp                           :  2;
     unsigned      rsvd3122                                  : 10;
#endif
} ncp_phy_CFG_SYSMEM_PHY_ADRx_ADRIOSET_1ST_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_ADRx_ADRIOSET_r_t
 *  @brief CFG_SYSMEM_PHY_ADRx_ADRIOSET
 *  @details This register provides control to ADR hardmacro I/O settings. This register is repeated for each individual ADR hardmacro.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_ADRx_ADRIOSET_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3112 </td>
 *     <td width="20%" align="center"> 20 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param adrslck1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> ADR SL CK1: SL setting for one pair of ADR I/Os. ADR12
 *        - bits[11:10], ADR9 - not connected.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param adrslck0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> ADR SL CK0: SL setting for one pair of ADR I/Os. ADR12
 *        - bits[5:4], ADR9 - bits[8:7].
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param adrslac </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> ADR SL AC: SL setting for ADR I/Os not connected to
 *        ADR_SL0_CK0 or ADR_SL0_CK1.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param adrdrvck1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> ADR DRV CK1: DRV setting for one pair of ADR I/Os.
 *        ADR12 - bits[11:10], ADR9 - not connected.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param adrdrvck0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> ADR DRV CK0: DRV setting for one pair of ADR I/Os.
 *        ADR12 - bits[5:4], ADR9 - bits[8:7].
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param adrdrvac </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> ADR DRV AC: DRV setting for ADR I/Os not connected
 *        to ADR_DRV_CK0 or ADR_DRV_CK1.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_ADRx_ADRIOSET_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3112                                  : 20;
     unsigned      adrslck1                                  :  2;
     unsigned      adrslck0                                  :  2;
     unsigned      adrslac                                   :  2;
     unsigned      adrdrvck1                                 :  2;
     unsigned      adrdrvck0                                 :  2;
     unsigned      adrdrvac                                  :  2;
#else    /* Little Endian */
     unsigned      adrdrvac                                  :  2;
     unsigned      adrdrvck0                                 :  2;
     unsigned      adrdrvck1                                 :  2;
     unsigned      adrslac                                   :  2;
     unsigned      adrslck0                                  :  2;
     unsigned      adrslck1                                  :  2;
     unsigned      rsvd3112                                  : 20;
#endif
} ncp_phy_CFG_SYSMEM_PHY_ADRx_ADRIOSET_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_ADRx_ADRIOPUPD_r_t
 *  @brief CFG_SYSMEM_PHY_ADRx_ADRIOPUPD
 *  @details This register provides control to ADR hardmacro I/O settings. This register is repeated for each individual ADR hardmacro.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_ADRx_ADRIOPUPD_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3124 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param adrpu30ke </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> ADR PU30KE: PU30KE setting for ADR I/Os. One bit per
 *        I/O. For ADR9, bits[23:21] are unused.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param adrpd30ke </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> ADR PD30KE: PD30KE setting for ADR I/Os. One bit per
 *        I/O. For ADR9, bits[11:9] are unused.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_ADRx_ADRIOPUPD_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3124                                  :  8;
     unsigned      adrpu30ke                                 : 12;
     unsigned      adrpd30ke                                 : 12;
#else    /* Little Endian */
     unsigned      adrpd30ke                                 : 12;
     unsigned      adrpu30ke                                 : 12;
     unsigned      rsvd3124                                  :  8;
#endif
} ncp_phy_CFG_SYSMEM_PHY_ADRx_ADRIOPUPD_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_WRLVLRESP_BLx_r_t
 *  @brief CFG_SYSMEM_PHY_WRLVLRESP_BLx
 *  @details This register provides DQ bit states on the memory bus sampled by an individual DP hardmacro during write leveling training process.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_WRLVLRESP_BLx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3116 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvlndq </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> WR Level NDQ: The 8 bit field contains DQ bit states
 *        on the memory bus sampled by the negative edge of
 *        the reference clock inside the DP hardmacro.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvlpdq </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> WR Level PDQ: The 8 bit field contains DQ bit states
 *        on the memory bus sampled by the positive edge of
 *        the reference clock inside the DP hardmacro.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_WRLVLRESP_BLx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3116                                  : 16;
     unsigned      wrlvlndq                                  :  8;
     unsigned      wrlvlpdq                                  :  8;
#else    /* Little Endian */
     unsigned      wrlvlpdq                                  :  8;
     unsigned      wrlvlndq                                  :  8;
     unsigned      rsvd3116                                  : 16;
#endif
} ncp_phy_CFG_SYSMEM_PHY_WRLVLRESP_BLx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DPRDDAT_BLx_r_t
 *  @brief CFG_SYSMEM_PHY_DPRDDAT_BLx
 *  @details This register provides access to read data output from the read data FIFO.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DPRDDAT_BLx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dpreaddata3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> DP Read Data: data captured on 4th edge (pos or neg).
 *        Use this register in conjunction with the rdlvlfifomode
 *        and rdlvlenard bits in the phyconfig2 register.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dpreaddata2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DP Read Data: data captured on 3rd edge (pos or neg).
 *        Use this register in conjunction with the rdlvlfifomode
 *        and rdlvlenard bits in the phyconfig2 register.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dpreaddata1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DP Read Data: data captured on 2nd edge (pos or neg).
 *        Use this register in conjunction with the rdlvlfifomode
 *        and rdlvlenard bits in the phyconfig2 register.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dpreaddata0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DP Read Data: data captured on 1st edge (pos or neg).
 *        Use this register in conjunction with the rdlvlfifomode
 *        and rdlvlenard bits in the phyconfig2 register.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_DPRDDAT_BLx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      dpreaddata3                               :  8;
     unsigned      dpreaddata2                               :  8;
     unsigned      dpreaddata1                               :  8;
     unsigned      dpreaddata0                               :  8;
#else    /* Little Endian */
     unsigned      dpreaddata0                               :  8;
     unsigned      dpreaddata1                               :  8;
     unsigned      dpreaddata2                               :  8;
     unsigned      dpreaddata3                               :  8;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DPRDDAT_BLx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DPSPARESTAT_r_t
 *  @brief CFG_SYSMEM_PHY_DPSPARESTAT
 *  @details This register provides access to read status output from each DP hardmacro spare delay cell. NOTE: for debug only.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DPSPARESTAT_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd319 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sparestat </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Spare Status: one bit per DP hardmacro instance. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_DPSPARESTAT_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd319                                   : 23;
     unsigned      sparestat                                 :  9;
#else    /* Little Endian */
     unsigned      sparestat                                 :  9;
     unsigned      rsvd319                                   : 23;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DPSPARESTAT_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DPIOLPRCTRL_BLx_r_t
 *  @brief CFG_SYSMEM_PHY_DPIOLPRCTRL_BLx
 *  @details This register provides power down control to the individual I/Os of each individual DP hardmacro.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DPIOLPRCTRL_BLx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3110 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lprdm </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> LPR DM: 1 - power down DM receive buffer. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpr7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> LPR 7: 1 - power down DQ7 receive buffer. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpr6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> LPR 6: 1 - power down DQ6 receive buffer. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpr5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> LPR 5: 1 - power down DQ5 receive buffer. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpr4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> LPR 4: 1 - power down DQ4 receive buffer. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lprdqs </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> LPR DQS: 1 - power down DQS receive buffer. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpr3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> LPR 3: 1 - power down DQ3 receive buffer. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpr2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> LPR 2: 1 - power down DQ2 receive buffer. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpr1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> LPR 1: 1 - power down DQ1 receive buffer. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpr0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> LPR 0: 1 - power down DQ0 receive buffer. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_DPIOLPRCTRL_BLx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3110                                  : 22;
     unsigned      lprdm                                     :  1;
     unsigned      lpr7                                      :  1;
     unsigned      lpr6                                      :  1;
     unsigned      lpr5                                      :  1;
     unsigned      lpr4                                      :  1;
     unsigned      lprdqs                                    :  1;
     unsigned      lpr3                                      :  1;
     unsigned      lpr2                                      :  1;
     unsigned      lpr1                                      :  1;
     unsigned      lpr0                                      :  1;
#else    /* Little Endian */
     unsigned      lpr0                                      :  1;
     unsigned      lpr1                                      :  1;
     unsigned      lpr2                                      :  1;
     unsigned      lpr3                                      :  1;
     unsigned      lprdqs                                    :  1;
     unsigned      lpr4                                      :  1;
     unsigned      lpr5                                      :  1;
     unsigned      lpr6                                      :  1;
     unsigned      lpr7                                      :  1;
     unsigned      lprdm                                     :  1;
     unsigned      rsvd3110                                  : 22;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DPIOLPRCTRL_BLx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_ADRx_AD9_ADRIOLPRCTRL_r_t
 *  @brief CFG_SYSMEM_PHY_ADRx_AD9_ADRIOLPRCTRL
 *  @details This register provides power down control to the individual I/Os of each individual ADR hardmacro.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_ADRx_AD9_ADRIOLPRCTRL_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3125 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enivref8 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> ENIVREF 8: 1 - enable ADR 8 receive buffer internal
 *        VREF.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enivref7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> ENIVREF 7: 1 - enable ADR 7 receive buffer internal
 *        VREF.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enivref6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> ENIVREF 6: 1 - enable ADR 6 receive buffer internal
 *        VREF.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enivref5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> ENIVREF 5: 1 - enable ADR 5 receive buffer internal
 *        VREF.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enivref4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> ENIVREF 4: 1 - enable ADR 4 receive buffer internal
 *        VREF.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enivref3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> ENIVREF 3: 1 - enable ADR 3 receive buffer internal
 *        VREF.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enivref2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> ENIVREF 2: 1 - enable ADR 2 receive buffer internal
 *        VREF.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enivref1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> ENIVREF 1: 1 - enable ADR 1 receive buffer internal
 *        VREF.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enivref0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> ENIVREF 0: 1 - enable ADR 0 receive buffer internal
 *        VREF.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd159 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpr8 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> LPR 8: 1 - power down ADR 8 receive buffer. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpr7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> LPR 7: 1 - power down ADR 7 receive buffer. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpr6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> LPR 6: 1 - power down ADR 6 receive buffer. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpr5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> LPR 5: 1 - power down ADR 5 receive buffer. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpr4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> LPR 4: 1 - power down ADR 4 receive buffer. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpr3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> LPR 3: 1 - power down ADR 3 receive buffer. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpr2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> LPR 2: 1 - power down ADR 2 receive buffer. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpr1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> LPR 1: 1 - power down ADR 1 receive buffer. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpr0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> LPR 0: 1 - power down ADR 0 receive buffer. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_ADRx_AD9_ADRIOLPRCTRL_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3125                                  :  7;
     unsigned      enivref8                                  :  1;
     unsigned      enivref7                                  :  1;
     unsigned      enivref6                                  :  1;
     unsigned      enivref5                                  :  1;
     unsigned      enivref4                                  :  1;
     unsigned      enivref3                                  :  1;
     unsigned      enivref2                                  :  1;
     unsigned      enivref1                                  :  1;
     unsigned      enivref0                                  :  1;
     unsigned      rsvd159                                   :  7;
     unsigned      lpr8                                      :  1;
     unsigned      lpr7                                      :  1;
     unsigned      lpr6                                      :  1;
     unsigned      lpr5                                      :  1;
     unsigned      lpr4                                      :  1;
     unsigned      lpr3                                      :  1;
     unsigned      lpr2                                      :  1;
     unsigned      lpr1                                      :  1;
     unsigned      lpr0                                      :  1;
#else    /* Little Endian */
     unsigned      lpr0                                      :  1;
     unsigned      lpr1                                      :  1;
     unsigned      lpr2                                      :  1;
     unsigned      lpr3                                      :  1;
     unsigned      lpr4                                      :  1;
     unsigned      lpr5                                      :  1;
     unsigned      lpr6                                      :  1;
     unsigned      lpr7                                      :  1;
     unsigned      lpr8                                      :  1;
     unsigned      rsvd159                                   :  7;
     unsigned      enivref0                                  :  1;
     unsigned      enivref1                                  :  1;
     unsigned      enivref2                                  :  1;
     unsigned      enivref3                                  :  1;
     unsigned      enivref4                                  :  1;
     unsigned      enivref5                                  :  1;
     unsigned      enivref6                                  :  1;
     unsigned      enivref7                                  :  1;
     unsigned      enivref8                                  :  1;
     unsigned      rsvd3125                                  :  7;
#endif
} ncp_phy_CFG_SYSMEM_PHY_ADRx_AD9_ADRIOLPRCTRL_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_ADRx_AD12_ADRIOLPRCTRL_r_t
 *  @brief CFG_SYSMEM_PHY_ADRx_AD12_ADRIOLPRCTRL
 *  @details This register provides power down control to the individual I/Os of each individual ADR hardmacro.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_ADRx_AD12_ADRIOLPRCTRL_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3128 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enivref11 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> ENIVREF 11: 1 - enable ADR 11 receive buffer internal
 *        VREF.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enivref10 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> ENIVREF 10: 1 - enable ADR 10 receive buffer internal
 *        VREF.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enivref9 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> ENIVREF 9: 1 - enable ADR 9 receive buffer internal
 *        VREF.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enivref8 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> ENIVREF 8: 1 - enable ADR 8 receive buffer internal
 *        VREF.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enivref7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> ENIVREF 7: 1 - enable ADR 7 receive buffer internal
 *        VREF.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enivref6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> ENIVREF 6: 1 - enable ADR 6 receive buffer internal
 *        VREF.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enivref5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> ENIVREF 5: 1 - enable ADR 5 receive buffer internal
 *        VREF.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enivref4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> ENIVREF 4: 1 - enable ADR 4 receive buffer internal
 *        VREF.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enivref3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> ENIVREF 3: 1 - enable ADR 3 receive buffer internal
 *        VREF.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enivref2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> ENIVREF 2: 1 - enable ADR 2 receive buffer internal
 *        VREF.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enivref1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> ENIVREF 1: 1 - enable ADR 1 receive buffer internal
 *        VREF.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enivref0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> ENIVREF 0: 1 - enable ADR 0 receive buffer internal
 *        VREF.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd1512 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpr11 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> LPR 11: 1 - power down ADR 11 receive buffer. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpr10 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> LPR 10: 1 - power down ADR 10 receive buffer. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpr9 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> LPR 9: 1 - power down ADR 9 receive buffer. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpr8 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> LPR 8: 1 - power down ADR 8 receive buffer. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpr7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> LPR 7: 1 - power down ADR 7 receive buffer. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpr6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> LPR 6: 1 - power down ADR 6 receive buffer. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpr5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> LPR 5: 1 - power down ADR 5 receive buffer. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpr4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> LPR 4: 1 - power down ADR 4 receive buffer. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpr3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> LPR 3: 1 - power down ADR 3 receive buffer. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpr2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> LPR 2: 1 - power down ADR 2 receive buffer. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpr1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> LPR 1: 1 - power down ADR 1 receive buffer. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpr0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> LPR 0: 1 - power down ADR 0 receive buffer. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_ADRx_AD12_ADRIOLPRCTRL_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3128                                  :  4;
     unsigned      enivref11                                 :  1;
     unsigned      enivref10                                 :  1;
     unsigned      enivref9                                  :  1;
     unsigned      enivref8                                  :  1;
     unsigned      enivref7                                  :  1;
     unsigned      enivref6                                  :  1;
     unsigned      enivref5                                  :  1;
     unsigned      enivref4                                  :  1;
     unsigned      enivref3                                  :  1;
     unsigned      enivref2                                  :  1;
     unsigned      enivref1                                  :  1;
     unsigned      enivref0                                  :  1;
     unsigned      rsvd1512                                  :  4;
     unsigned      lpr11                                     :  1;
     unsigned      lpr10                                     :  1;
     unsigned      lpr9                                      :  1;
     unsigned      lpr8                                      :  1;
     unsigned      lpr7                                      :  1;
     unsigned      lpr6                                      :  1;
     unsigned      lpr5                                      :  1;
     unsigned      lpr4                                      :  1;
     unsigned      lpr3                                      :  1;
     unsigned      lpr2                                      :  1;
     unsigned      lpr1                                      :  1;
     unsigned      lpr0                                      :  1;
#else    /* Little Endian */
     unsigned      lpr0                                      :  1;
     unsigned      lpr1                                      :  1;
     unsigned      lpr2                                      :  1;
     unsigned      lpr3                                      :  1;
     unsigned      lpr4                                      :  1;
     unsigned      lpr5                                      :  1;
     unsigned      lpr6                                      :  1;
     unsigned      lpr7                                      :  1;
     unsigned      lpr8                                      :  1;
     unsigned      lpr9                                      :  1;
     unsigned      lpr10                                     :  1;
     unsigned      lpr11                                     :  1;
     unsigned      rsvd1512                                  :  4;
     unsigned      enivref0                                  :  1;
     unsigned      enivref1                                  :  1;
     unsigned      enivref2                                  :  1;
     unsigned      enivref3                                  :  1;
     unsigned      enivref4                                  :  1;
     unsigned      enivref5                                  :  1;
     unsigned      enivref6                                  :  1;
     unsigned      enivref7                                  :  1;
     unsigned      enivref8                                  :  1;
     unsigned      enivref9                                  :  1;
     unsigned      enivref10                                 :  1;
     unsigned      enivref11                                 :  1;
     unsigned      rsvd3128                                  :  4;
#endif
} ncp_phy_CFG_SYSMEM_PHY_ADRx_AD12_ADRIOLPRCTRL_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_FBLOWUPPOFF_BLx_r_t
 *  @brief CFG_SYSMEM_PHY_FBLOWUPPOFF_BLx
 *  @details This register provides delay offset information for the feedback state machine to be used in feedback DQS gating scheme.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_FBLOWUPPOFF_BLx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3110 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fblowoff </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> FB Lower Offset: The 5 bit field provides PCB trace
 *        delay skew information of the DQS0 signal to the feedback
 *        state machine in a single rank environment.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fbuppoff </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> FB Upper Offset: The 5 bit field provides PCB trace
 *        delay skew information of the DM or DQS1 signal to
 *        the feedback state machine in a single rank environment.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_FBLOWUPPOFF_BLx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3110                                  : 22;
     unsigned      fblowoff                                  :  5;
     unsigned      fbuppoff                                  :  5;
#else    /* Little Endian */
     unsigned      fbuppoff                                  :  5;
     unsigned      fblowoff                                  :  5;
     unsigned      rsvd3110                                  : 22;
#endif
} ncp_phy_CFG_SYSMEM_PHY_FBLOWUPPOFF_BLx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_VTCCOUNT_r_t
 *  @brief CFG_SYSMEM_PHY_VTCCOUNT
 *  @details This register controls the delay between tracking updates. If vtccntena=1, the time spent in the wait_vt state is equal to the number specified by vtccount. If the vtccntena=0, then the state machine control will stall in the wait_vt state.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_VTCCOUNT_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param vtccount </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> VTC Count: Number of clk_phy_cal cycles to wait between
 *        tracking updates.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_VTCCOUNT_r_t
 *
 */
 
typedef struct
{
     unsigned  int                  vtccount;
} ncp_phy_CFG_SYSMEM_PHY_VTCCOUNT_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_ALIGN_DELAYS_r_t
 *  @brief CFG_SYSMEM_PHY_ALIGN_DELAYS
 *  @details This register provides debug control to the PHY.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_ALIGN_DELAYS_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param n_upp_align </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Aligned delay for the negative edge, lower upper delay
 *        cell.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param n_low_align </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Aligned delay for the negative edge, lower nibble
 *        delay cell.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param p_upp_align </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Aligned delay for the positive edge, lower upper delay
 *        cell.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param p_low_align </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Aligned delay for the positive edge, lower nibble
 *        delay cell.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_ALIGN_DELAYS_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      n_upp_align                               :  8;
     unsigned      n_low_align                               :  8;
     unsigned      p_upp_align                               :  8;
     unsigned      p_low_align                               :  8;
#else    /* Little Endian */
     unsigned      p_low_align                               :  8;
     unsigned      p_upp_align                               :  8;
     unsigned      n_low_align                               :  8;
     unsigned      n_upp_align                               :  8;
#endif
} ncp_phy_CFG_SYSMEM_PHY_ALIGN_DELAYS_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DEBUG_r_t
 *  @brief CFG_SYSMEM_PHY_DEBUG
 *  @details This register provides debug control to the PHY.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DEBUG_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3110 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param debugdpid </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Debug DP ID: Selects which DP status to be placed
 *        on pi_diagnosis bus.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd32 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param debugsel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Debug Sel: The 2 bit field selects which debug registers
 *        to be MUXed out at pi_diagnosis ports.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_DEBUG_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3110                                  : 24;
     unsigned      debugdpid                                 :  4;
     unsigned      rsvd32                                    :  2;
     unsigned      debugsel                                  :  2;
#else    /* Little Endian */
     unsigned      debugsel                                  :  2;
     unsigned      rsvd32                                    :  2;
     unsigned      debugdpid                                 :  4;
     unsigned      rsvd3110                                  : 24;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DEBUG_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DEBUGDLYCTRL_r_t
 *  @brief CFG_SYSMEM_PHY_DEBUGDLYCTRL
 *  @details This register provides debug information of the PHY feedback state machine and delay cell control module and its associated state machines. NOTE: may be available only for testchip debug.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DEBUGDLYCTRL_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3117 </td>
 *     <td width="20%" align="center"> 15 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dcmupralign </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DCM Upper Align Max: 1 - any of DQ[7:4] bit alignment
 *        setting is at its max value (all 1s).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dcmlwralign </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> DCM Lower Align Max: 1 - any of DQ[3:0] bit alignment
 *        setting is at its max value (all 1s).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dcmcalcpupp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> DCM Calculate P UPP ratio: 1 - positive edge upper
 *        nibble ratio (PUPP/Spare) is being calculated.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dcmcalcnupp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> DCM Calculate N UPP ratio: 1 - negative edge upper
 *        nibble ratio (PUPP/Spare) is being calculated.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dcmcalcplow </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> DCM Calculate P LOW ratio: 1 - positive edge lower
 *        nibble ratio (PUPP/Spare) is being calculated.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dcmcalcnlow </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> DCM Calculate N LOW ratio: 1 - negative edge lower
 *        nibble ratio (PUPP/Spare) is being calculated.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param divsmstate </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Div SM State </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param initsmphase </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Init SM Phase </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param initsmstate </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Init SM State </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_DEBUGDLYCTRL_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3117                                  : 15;
     unsigned      dcmupralign                               :  1;
     unsigned      dcmlwralign                               :  1;
     unsigned      dcmcalcpupp                               :  1;
     unsigned      dcmcalcnupp                               :  1;
     unsigned      dcmcalcplow                               :  1;
     unsigned      dcmcalcnlow                               :  1;
     unsigned      divsmstate                                :  3;
     unsigned      initsmphase                               :  2;
     unsigned      initsmstate                               :  6;
#else    /* Little Endian */
     unsigned      initsmstate                               :  6;
     unsigned      initsmphase                               :  2;
     unsigned      divsmstate                                :  3;
     unsigned      dcmcalcnlow                               :  1;
     unsigned      dcmcalcplow                               :  1;
     unsigned      dcmcalcnupp                               :  1;
     unsigned      dcmcalcpupp                               :  1;
     unsigned      dcmlwralign                               :  1;
     unsigned      dcmupralign                               :  1;
     unsigned      rsvd3117                                  : 15;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DEBUGDLYCTRL_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DEBUGWLRLPG_r_t
 *  @brief CFG_SYSMEM_PHY_DEBUGWLRLPG
 *  @details This register provides debug information on PHY programmable gate training state machine. NOTE: may be available only for testchip debug.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DEBUGWLRLPG_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3119 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wlsmstate </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> WL SM State </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd1513 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param resmstate </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> RE SM State </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd7 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgsmstate </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Gate Train SM State </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_DEBUGWLRLPG_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3119                                  : 12;
     unsigned      wlsmstate                                 :  4;
     unsigned      rsvd1513                                  :  3;
     unsigned      resmstate                                 :  5;
     unsigned      rsvd7                                     :  2;
     unsigned      pgsmstate                                 :  6;
#else    /* Little Endian */
     unsigned      pgsmstate                                 :  6;
     unsigned      rsvd7                                     :  2;
     unsigned      resmstate                                 :  5;
     unsigned      rsvd1513                                  :  3;
     unsigned      wlsmstate                                 :  4;
     unsigned      rsvd3119                                  : 12;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DEBUGWLRLPG_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_DEBUGCSFBSM_r_t
 *  @brief CFG_SYSMEM_PHY_DEBUGCSFBSM
 *  @details This register provides debug information on PHY feedback state machine and hardmacro register bus access. NOTE: may be available only for testchip debug.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_DEBUGCSFBSM_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param hmcs </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Hardmacro Chip Selects: One bit per hardmacro. Max
 *        number of DP hardmacros is 9. Max number of the ADR
 *        hardmacros is 6. Each DP has a separate chip select
 *        for its own external register interface. The order
 *        of the chip selects is [ap_cs, ext_reg_cs, dp_cs].
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fbsmuvf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> FBSM Underflow: 1 - After FBSM runs, it has failed
 *        to converge because the generated pulse was not feeding
 *        back properly (tie-1). Double check if the feedback
 *        location is what is indicated in fbapsel and fblpsel
 *        of phyconfig0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fbsmovf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> FBSM Overflow: 1 - After FBSM runs, it has failed
 *        to converge because either no pulse was generated
 *        or the generated pulse was not feeding back properly
 *        (tie-0). Double check if the feedback location is
 *        what is indicated in fbapsel and fblpsel of phyconfig0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fbsmstate </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Feedback SM State </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_DEBUGCSFBSM_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      hmcs                                      : 24;
     unsigned      fbsmuvf                                   :  1;
     unsigned      fbsmovf                                   :  1;
     unsigned      fbsmstate                                 :  6;
#else    /* Little Endian */
     unsigned      fbsmstate                                 :  6;
     unsigned      fbsmovf                                   :  1;
     unsigned      fbsmuvf                                   :  1;
     unsigned      hmcs                                      : 24;
#endif
} ncp_phy_CFG_SYSMEM_PHY_DEBUGCSFBSM_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_BISTCTRL_r_t
 *  @brief CFG_SYSMEM_PHY_BISTCTRL
 *  @details This register provides control to the BIST logic inside the PHY. NOTE: This register is for debug only.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_BISTCTRL_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param bist_lat </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> BIST Latency: Latency value for the ADR expected pattern.
 *        The expected ADR value is delayed by the latency value
 *        before it is compared with the data coming out of
 *        ADR hardmacro.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bisthmsel </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> BIST Hardmacro Select: BIST procedure runs on the
 *        corresponding hardmacro.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bist_eye_width </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> BIST Eye Width: Data eye width required for the BIST
 *        pass criteria for the DP hardmacro.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bist_patt_type </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> BIST Pattern Type: </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bist_lpbk </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> BIST Loopback: chooses whether data is looped back
 *        before or through the buffers.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bist_type </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> BIST Type: chooses between brief or extensive BIST
 *        procedure.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bist_contpatt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> BIST Continuous Pattern: enables the BIST pattern
 *        generator when BIST is not enabled. When BIST is enabled,
 *        the pattern generator is enabled automatically.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd41 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param runbist </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Run BIST: starts the BIST SM. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_BISTCTRL_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      bist_lat                                  :  3;
     unsigned      bisthmsel                                 : 16;
     unsigned      bist_eye_width                            :  3;
     unsigned      bist_patt_type                            :  2;
     unsigned      bist_lpbk                                 :  1;
     unsigned      bist_type                                 :  1;
     unsigned      bist_contpatt                             :  1;
     unsigned      rsvd41                                    :  4;
     unsigned      runbist                                   :  1;
#else    /* Little Endian */
     unsigned      runbist                                   :  1;
     unsigned      rsvd41                                    :  4;
     unsigned      bist_contpatt                             :  1;
     unsigned      bist_type                                 :  1;
     unsigned      bist_lpbk                                 :  1;
     unsigned      bist_patt_type                            :  2;
     unsigned      bist_eye_width                            :  3;
     unsigned      bisthmsel                                 : 16;
     unsigned      bist_lat                                  :  3;
#endif
} ncp_phy_CFG_SYSMEM_PHY_BISTCTRL_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_BISTSTAT_r_t
 *  @brief CFG_SYSMEM_PHY_BISTSTAT
 *  @details This register provides overall BIST status information. NOTE: This register is for debug only.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_BISTSTAT_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param bistdone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> BIST Done </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3016 </td>
 *     <td width="20%" align="center"> 15 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bistpasshm </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> BIST Passed HM: each bit shows the passing status
 *        of one hardmacro. Starting with bit [0], each bit
 *        corresponds to DP8 instances, ADR9 instances, and
 *        ADR12 instances in that order. A 1 indicates passed.
 *        Any remaining bits without a corresponding hardmacro
 *        are always set to a value of 1.
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_BISTSTAT_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      bistdone                                  :  1;
     unsigned      rsvd3016                                  : 15;
     unsigned      bistpasshm                                : 16;
#else    /* Little Endian */
     unsigned      bistpasshm                                : 16;
     unsigned      rsvd3016                                  : 15;
     unsigned      bistdone                                  :  1;
#endif
} ncp_phy_CFG_SYSMEM_PHY_BISTSTAT_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_BIST_PATT0_BLx_r_t
 *  @brief CFG_SYSMEM_PHY_BIST_PATT0_BLx
 *  @details This register provides the specific BIST result of the DP hardmacro. NOTE: This register is for debug only.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_BIST_PATT0_BLx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param bistforcevalue </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> BIST Force Value for bits[11:4] </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bistforce </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> BIST Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bistinvert </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> BIST Invert </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_BIST_PATT0_BLx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      bistforcevalue                            :  8;
     unsigned      bistforce                                 : 12;
     unsigned      bistinvert                                : 12;
#else    /* Little Endian */
     unsigned      bistinvert                                : 12;
     unsigned      bistforce                                 : 12;
     unsigned      bistforcevalue                            :  8;
#endif
} ncp_phy_CFG_SYSMEM_PHY_BIST_PATT0_BLx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_ADRx_BIST_PATT1_r_t
 *  @brief CFG_SYSMEM_PHY_ADRx_BIST_PATT1
 *  @details This register provides the specific BIST result of the ADR hardmacro. NOTE: This register is for debug only.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_ADRx_BIST_PATT1_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3128 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Reserved </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bist_shift2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> BIST Shift2 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bist_shift1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> BIST Shift1 </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bistforcevalue </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> BIST Force Value for bits [3:0] </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_ADRx_BIST_PATT1_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3128                                  :  4;
     unsigned      bist_shift2                               : 12;
     unsigned      bist_shift1                               : 12;
     unsigned      bistforcevalue                            :  4;
#else    /* Little Endian */
     unsigned      bistforcevalue                            :  4;
     unsigned      bist_shift1                               : 12;
     unsigned      bist_shift2                               : 12;
     unsigned      rsvd3128                                  :  4;
#endif
} ncp_phy_CFG_SYSMEM_PHY_ADRx_BIST_PATT1_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_PUPPRATIO_BLxCSx_r_t
 *  @brief CFG_SYSMEM_PHY_PUPPRATIO_BLxCSx
 *  @details This register contains the calculated delay ratio between the P upper DQS delay cell and the spare delay cell. The initialization state machine calculates this ratio.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_PUPPRATIO_BLxCSx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3113 </td>
 *     <td width="20%" align="center"> 19 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param puppratio </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> P Upper Ratio </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_PUPPRATIO_BLxCSx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3113                                  : 19;
     unsigned      puppratio                                 : 13;
#else    /* Little Endian */
     unsigned      puppratio                                 : 13;
     unsigned      rsvd3113                                  : 19;
#endif
} ncp_phy_CFG_SYSMEM_PHY_PUPPRATIO_BLxCSx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_NUPPRATIO_BLxCSx_r_t
 *  @brief CFG_SYSMEM_PHY_NUPPRATIO_BLxCSx
 *  @details This register contains the calculated delay ratio between the N upper DQS delay cell and the spare delay cell. The initialization state machine calculates this ratio.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_NUPPRATIO_BLxCSx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3113 </td>
 *     <td width="20%" align="center"> 19 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param nuppratio </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> N Upper Ratio </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_NUPPRATIO_BLxCSx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3113                                  : 19;
     unsigned      nuppratio                                 : 13;
#else    /* Little Endian */
     unsigned      nuppratio                                 : 13;
     unsigned      rsvd3113                                  : 19;
#endif
} ncp_phy_CFG_SYSMEM_PHY_NUPPRATIO_BLxCSx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_PLOWRATIO_BLxCSx_r_t
 *  @brief CFG_SYSMEM_PHY_PLOWRATIO_BLxCSx
 *  @details This register contains the calculated delay ratio between the P lower DQS delay cell and the spare delay cell. The initialization state machine calculates this ratio.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_PLOWRATIO_BLxCSx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3113 </td>
 *     <td width="20%" align="center"> 19 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param plowratio </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> P Lower Ratio </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_PLOWRATIO_BLxCSx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3113                                  : 19;
     unsigned      plowratio                                 : 13;
#else    /* Little Endian */
     unsigned      plowratio                                 : 13;
     unsigned      rsvd3113                                  : 19;
#endif
} ncp_phy_CFG_SYSMEM_PHY_PLOWRATIO_BLxCSx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_NLOWRATIO_BLxCSx_r_t
 *  @brief CFG_SYSMEM_PHY_NLOWRATIO_BLxCSx
 *  @details This register contains the calculated delay ratio between the N lower DQS delay cell and the spare delay cell. The initialization state machine calculates this ratio.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_NLOWRATIO_BLxCSx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd3113 </td>
 *     <td width="20%" align="center"> 19 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param nlowratio </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> N Lower Ratio </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_NLOWRATIO_BLxCSx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd3113                                  : 19;
     unsigned      nlowratio                                 : 13;
#else    /* Little Endian */
     unsigned      nlowratio                                 : 13;
     unsigned      rsvd3113                                  : 19;
#endif
} ncp_phy_CFG_SYSMEM_PHY_NLOWRATIO_BLxCSx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_WRTALIGNDQx_BLxCSx_r_t
 *  @brief CFG_SYSMEM_PHY_WRTALIGNDQx_BLxCSx
 *  @details This register contains the alignment value for the write bit delay for DQ, DQS, and DM.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_WRTALIGNDQx_BLxCSx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd317 </td>
 *     <td width="20%" align="center"> 25 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrbitalign </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Write Bit Align Delay for DQ/DQS/DM. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_WRTALIGNDQx_BLxCSx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd317                                   : 25;
     unsigned      wrbitalign                                :  7;
#else    /* Little Endian */
     unsigned      wrbitalign                                :  7;
     unsigned      rsvd317                                   : 25;
#endif
} ncp_phy_CFG_SYSMEM_PHY_WRTALIGNDQx_BLxCSx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_WRTALIGNLOW_BC_BLxCSx_r_t
 *  @brief CFG_SYSMEM_PHY_WRTALIGNLOW_BC_BLxCSx
 *  @details This register provides the broadcast write for write bit delay for DQ[3:0] and DQS[0] per byte lane and rank.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_WRTALIGNLOW_BC_BLxCSx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd317 </td>
 *     <td width="20%" align="center"> 25 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrbitalign </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Write Bit Align Delay for DQ/DQS/DM. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_WRTALIGNLOW_BC_BLxCSx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd317                                   : 25;
     unsigned      wrbitalign                                :  7;
#else    /* Little Endian */
     unsigned      wrbitalign                                :  7;
     unsigned      rsvd317                                   : 25;
#endif
} ncp_phy_CFG_SYSMEM_PHY_WRTALIGNLOW_BC_BLxCSx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_WRTALIGNUPP_BC_BLxCSx_r_t
 *  @brief CFG_SYSMEM_PHY_WRTALIGNUPP_BC_BLxCSx
 *  @details This register provides the broadcast write for write bit delay for DQ[7:4] and DM per byte lane and rank.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_WRTALIGNUPP_BC_BLxCSx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd317 </td>
 *     <td width="20%" align="center"> 25 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrbitalign </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Write Bit Align Delay for DQ/DQS/DM. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_WRTALIGNUPP_BC_BLxCSx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd317                                   : 25;
     unsigned      wrbitalign                                :  7;
#else    /* Little Endian */
     unsigned      wrbitalign                                :  7;
     unsigned      rsvd317                                   : 25;
#endif
} ncp_phy_CFG_SYSMEM_PHY_WRTALIGNUPP_BC_BLxCSx_r_t;

/*! @struct ncp_phy_CFG_SYSMEM_PHY_RDALIGNDQx_BLxCSx_r_t
 *  @brief CFG_SYSMEM_PHY_RDALIGNDQx_BLxCSx
 *  @details This register contains the alignment value for the read bit delay for DQs. It is the ones complement of the number of fine delay taps required for delay, e.g. 11111 = 0 delay and 00000 = max delay of 31 taps.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CFG_SYSMEM_PHY_RDALIGNDQx_BLxCSx_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd315 </td>
 *     <td width="20%" align="center"> 27 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved, write with 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdbitalign </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Read Bit Align Delay for DQ. </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_phy_CFG_SYSMEM_PHY_RDALIGNDQx_BLxCSx_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rsvd315                                   : 27;
     unsigned      rdbitalign                                :  5;
#else    /* Little Endian */
     unsigned      rdbitalign                                :  5;
     unsigned      rsvd315                                   : 27;
#endif
} ncp_phy_CFG_SYSMEM_PHY_RDALIGNDQx_BLxCSx_r_t;

#ifdef __cplusplus
}
#endif

#endif /* _NCP_PHY_REGS_2500_H_ */
