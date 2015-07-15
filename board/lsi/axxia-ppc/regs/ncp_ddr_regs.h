/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2013, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/



#ifndef _NCP_DDR_REGS_H_
#define _NCP_DDR_REGS_H_

#ifdef __cplusplus
extern "C" {
#endif


/*! @struct ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t
 *  @brief CFG_NTEMC_DDR_CTRL
 *  @details Main control for Tree Engine DDR controller
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param add_w2w </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Additional cycles to insert between writes and writes </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param add_r2r </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Additional cycles to insert between reads and reads </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param add_w2r </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Additional cycles to insert between writes and reads </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param add_r2w </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Additional cycles to insert between reads and writes </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param init_start </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> DFI 2.1 Init start to phy </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cntl_mode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> clear ecc status flags </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param phy_mc_wdly </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Phy write data delay input </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param byp_ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Prefetch bypass enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odt_prof </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> ODT profile </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odt_mode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> ODT mode </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zq_intv </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Short ZQCal interval basis </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zq_per </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> ZQ Calibration duration </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param auto_zq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Auto ZQCal short operation </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param scrub_ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> DRAM scrubbing enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ref_ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Refresh enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmdhist_ena </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> DDR cmd history enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lvl_edge </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Set the edge for read training </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lvl_rsp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reset training responses </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rd_gate_lvl </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Start initial rd gate leveling </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rd_lvl </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Start initial rd leveling </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrt_lvl </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Start initial wrt leveling </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ddr_cke </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> DRAM clock enable/power mode </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ddr_rstn </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> DDR3 only, DRAM reset_n </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param phy_clkdis </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Clock disable to a static level via phy control </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param idle_mode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> define if controller is active </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      add_w2w                                   :  2;
     unsigned      add_r2r                                   :  2;
     unsigned      add_w2r                                   :  2;
     unsigned      add_r2w                                   :  2;
     unsigned      init_start                                :  1;
     unsigned      cntl_mode                                 :  1;
     unsigned      phy_mc_wdly                               :  1;
     unsigned      byp_ena                                   :  1;
     unsigned      odt_prof                                  :  2;
     unsigned      odt_mode                                  :  2;
     unsigned      zq_intv                                   :  1;
     unsigned      zq_per                                    :  2;
     unsigned      auto_zq                                   :  1;
     unsigned      scrub_ena                                 :  1;
     unsigned      ref_ena                                   :  1;
     unsigned      cmdhist_ena                               :  1;
     unsigned      lvl_edge                                  :  1;
     unsigned      lvl_rsp                                   :  1;
     unsigned      rd_gate_lvl                               :  1;
     unsigned      rd_lvl                                    :  1;
     unsigned      wrt_lvl                                   :  1;
     unsigned      ddr_cke                                   :  1;
     unsigned      ddr_rstn                                  :  1;
     unsigned      phy_clkdis                                :  1;
     unsigned      idle_mode                                 :  1;
#else    /* Little Endian */
     unsigned      idle_mode                                 :  1;
     unsigned      phy_clkdis                                :  1;
     unsigned      ddr_rstn                                  :  1;
     unsigned      ddr_cke                                   :  1;
     unsigned      wrt_lvl                                   :  1;
     unsigned      rd_lvl                                    :  1;
     unsigned      rd_gate_lvl                               :  1;
     unsigned      lvl_rsp                                   :  1;
     unsigned      lvl_edge                                  :  1;
     unsigned      cmdhist_ena                               :  1;
     unsigned      ref_ena                                   :  1;
     unsigned      scrub_ena                                 :  1;
     unsigned      auto_zq                                   :  1;
     unsigned      zq_per                                    :  2;
     unsigned      zq_intv                                   :  1;
     unsigned      odt_mode                                  :  2;
     unsigned      odt_prof                                  :  2;
     unsigned      byp_ena                                   :  1;
     unsigned      phy_mc_wdly                               :  1;
     unsigned      cntl_mode                                 :  1;
     unsigned      init_start                                :  1;
     unsigned      add_r2w                                   :  2;
     unsigned      add_w2r                                   :  2;
     unsigned      add_r2r                                   :  2;
     unsigned      add_w2w                                   :  2;
#endif
} ncp_ddr_CFG_NTEMC_DDR_CTRL_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_DDR_STATUS_r_t
 *  @brief CFG_NTEMC_DDR_STATUS
 *  @details Main status for Tree Engine DDR controller
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_DDR_STATUS_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param meminitdone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> HW based memory/ecc init complete. This bit is cleared
 *        when the function is initiated.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param histptr </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Oldest ptr value for cmd history </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param memtst_rslt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> HW based memory test result </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param memtst_stat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> HW based memory test status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param scbdbeflg </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> scrub double bit error </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param scbsbeflg </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> scrub single bit error </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfgdbeflg </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> cfg double bit error </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfgsbeflg </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> cfg single bit error </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axidbeflg </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> axi double bit error </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axisbeflg </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> axi single bit error </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvlstat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> rd leveling status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvldone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> rd leveling finished </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdgtlvlstat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> rd gate leveling status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdgtlvldone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> rd gate leveling finished </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvlstat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> wr leveling status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvldone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> wr leveling finished </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ddr_stat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> controller idle status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param phy_stat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> phy init status </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_DDR_STATUS_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  9;
     unsigned      meminitdone                               :  1;
     unsigned      histptr                                   :  6;
     unsigned      memtst_rslt                               :  1;
     unsigned      memtst_stat                               :  1;
     unsigned      scbdbeflg                                 :  1;
     unsigned      scbsbeflg                                 :  1;
     unsigned      cfgdbeflg                                 :  1;
     unsigned      cfgsbeflg                                 :  1;
     unsigned      axidbeflg                                 :  1;
     unsigned      axisbeflg                                 :  1;
     unsigned      rdlvlstat                                 :  1;
     unsigned      rdlvldone                                 :  1;
     unsigned      rdgtlvlstat                               :  1;
     unsigned      rdgtlvldone                               :  1;
     unsigned      wrlvlstat                                 :  1;
     unsigned      wrlvldone                                 :  1;
     unsigned      ddr_stat                                  :  1;
     unsigned      phy_stat                                  :  1;
#else    /* Little Endian */
     unsigned      phy_stat                                  :  1;
     unsigned      ddr_stat                                  :  1;
     unsigned      wrlvldone                                 :  1;
     unsigned      wrlvlstat                                 :  1;
     unsigned      rdgtlvldone                               :  1;
     unsigned      rdgtlvlstat                               :  1;
     unsigned      rdlvldone                                 :  1;
     unsigned      rdlvlstat                                 :  1;
     unsigned      axisbeflg                                 :  1;
     unsigned      axidbeflg                                 :  1;
     unsigned      cfgsbeflg                                 :  1;
     unsigned      cfgdbeflg                                 :  1;
     unsigned      scbsbeflg                                 :  1;
     unsigned      scbdbeflg                                 :  1;
     unsigned      memtst_stat                               :  1;
     unsigned      memtst_rslt                               :  1;
     unsigned      histptr                                   :  6;
     unsigned      meminitdone                               :  1;
     unsigned      reserved0                                 :  9;
#endif
} ncp_ddr_CFG_NTEMC_DDR_STATUS_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_DESL_r_t
 *  @brief CFG_NTEMC_DESL
 *  @details Deselected values for the external DDR control outputs
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_DESL_r_t\n
 *   </td>
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
 *     <td width="30%"> @param desl_cmd </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> deselected DDR command is NOP </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param desl_badr </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> deselected DDR bank address bits </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param desl_adr </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> deselected DDR address bits </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_DESL_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  8;
     unsigned      desl_cmd                                  :  4;
     unsigned      reserved1                                 :  1;
     unsigned      desl_badr                                 :  3;
     unsigned      desl_adr                                  : 16;
#else    /* Little Endian */
     unsigned      desl_adr                                  : 16;
     unsigned      desl_badr                                 :  3;
     unsigned      reserved1                                 :  1;
     unsigned      desl_cmd                                  :  4;
     unsigned      reserved0                                 :  8;
#endif
} ncp_ddr_CFG_NTEMC_DESL_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_MRS_r_t
 *  @brief CFG_NTEMC_MRS
 *  @details SW DDR command register for MRSx, Ref, ZQCal operations. See the appropriate DDR2/3 spec for MRS field mappings. CKE must be 1 for every cmd except power down.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_MRS_r_t\n
 *   </td>
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
 *     <td width="30%"> @param mrs_cke </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> MRS CKE, CKE=0 with a refresh cmd or NOP puts the
 *        external DRAM in powerdown mode, CKE will be held
 *        low until a NOP with CKE=1 is issued.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mrs_cmd </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> MRS DDR command bits, CSN/RASN/CASN/WEN </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mrs_badr </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> MRS DDR bank address bits </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mrs_adr </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MRS DDR address bits </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_MRS_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      mrs_cke                                   :  1;
     unsigned      mrs_cmd                                   :  4;
     unsigned      reserved1                                 :  1;
     unsigned      mrs_badr                                  :  3;
     unsigned      mrs_adr                                   : 16;
#else    /* Little Endian */
     unsigned      mrs_adr                                   : 16;
     unsigned      mrs_badr                                  :  3;
     unsigned      reserved1                                 :  1;
     unsigned      mrs_cmd                                   :  4;
     unsigned      mrs_cke                                   :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_ddr_CFG_NTEMC_MRS_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_ISSUE_MRS_r_t
 *  @brief cfg_ntemc_issue_mrs
 *  @details Write only register to issue an sdram cmd from the mrs register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_ISSUE_MRS_r_t\n
 *   </td>
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
 *     <td width="30%"> @param init_cmd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> SW initiated sdram cmd issue of the mrs register </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_ISSUE_MRS_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 31;
     unsigned      init_cmd                                  :  1;
#else    /* Little Endian */
     unsigned      init_cmd                                  :  1;
     unsigned      reserved0                                 : 31;
#endif
} ncp_ddr_CFG_NTEMC_ISSUE_MRS_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_DRAM_TYPE_r_t
 *  @brief CFG_NTEMC_DRAM_TYPE
 *  @details Density and CL/AL/CWL settings for the target DRAM. AL must always be set to CL-1.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_DRAM_TYPE_r_t\n
 *   </td>
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
 *     <td width="30%"> @param type_rdadj </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> RDadj: takes other phy to dram factors into account </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param type_wradj </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> WRTadj: takes other phy to dram factors into account </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ddr_type </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> DRAM type </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param type_ba </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> number of bank addr bits </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param type_row </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> number of row addr bits </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param type_col </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> number of column addr bits </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param type_cwl </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> CWL </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param type_al </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> AL setting </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param type_cl </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CL setting </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_DRAM_TYPE_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      type_rdadj                                :  5;
     unsigned      type_wradj                                :  5;
     unsigned      ddr_type                                  :  1;
     unsigned      type_ba                                   :  1;
     unsigned      type_row                                  :  3;
     unsigned      type_col                                  :  2;
     unsigned      type_cwl                                  :  4;
     unsigned      type_al                                   :  4;
     unsigned      type_cl                                   :  4;
#else    /* Little Endian */
     unsigned      type_cl                                   :  4;
     unsigned      type_al                                   :  4;
     unsigned      type_cwl                                  :  4;
     unsigned      type_col                                  :  2;
     unsigned      type_row                                  :  3;
     unsigned      type_ba                                   :  1;
     unsigned      ddr_type                                  :  1;
     unsigned      type_wradj                                :  5;
     unsigned      type_rdadj                                :  5;
     unsigned      reserved0                                 :  3;
#endif
} ncp_ddr_CFG_NTEMC_DRAM_TYPE_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_SPECVAL1_r_t
 *  @brief CFG_NTEMC_SPECVAL1
 *  @details First group of DRAM timing parameters: tRP, tRFC, tREFI
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_SPECVAL1_r_t\n
 *   </td>
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
 *     <td width="30%"> @param trp </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> tRP: min precharge period </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trfc </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> tRFC: min refresh to active/refresh time </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trefi </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> tREFI: avg refresh interval </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_SPECVAL1_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      trp                                       :  5;
     unsigned      trfc                                      : 10;
     unsigned      trefi                                     : 16;
#else    /* Little Endian */
     unsigned      trefi                                     : 16;
     unsigned      trfc                                      : 10;
     unsigned      trp                                       :  5;
     unsigned      reserved0                                 :  1;
#endif
} ncp_ddr_CFG_NTEMC_SPECVAL1_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_SPECVAL2_r_t
 *  @brief CFG_NTEMC_SPECVAL2
 *  @details Second group of DRAM timing parameters: tRAS, tRC, tFAW, tRTP, tWTR, tWR
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_SPECVAL2_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param tras </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> tRAS: min active to precharge time </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trc </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> tRC: min active to active/refresh time </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfaw </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> tFAW: min four activate window </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trtp </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> tRTP: min internal read to precharge delay </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param twtr </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> tWTR: min internal write to read delay </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param twr </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> tWR: write recovery time </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_SPECVAL2_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      tras                                      :  6;
     unsigned      trc                                       :  7;
     unsigned      tfaw                                      :  7;
     unsigned      trtp                                      :  4;
     unsigned      twtr                                      :  4;
     unsigned      twr                                       :  4;
#else    /* Little Endian */
     unsigned      twr                                       :  4;
     unsigned      twtr                                      :  4;
     unsigned      trtp                                      :  4;
     unsigned      tfaw                                      :  7;
     unsigned      trc                                       :  7;
     unsigned      tras                                      :  6;
#endif
} ncp_ddr_CFG_NTEMC_SPECVAL2_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_SPECVAL3_r_t
 *  @brief CFG_NTEMC_SPECVAL3
 *  @details Third group of DRAM timing parameters: tMPRR, tWLDQSEN, tWLMRD, tMRD, tMOD, tRRD
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_SPECVAL3_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param twldqsen </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> tWLDQSEN: DQS output enable delay after write leveling
 *        programmed
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param twlmrd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> tWLMRD: min time to first DQS edge after write leveling
 *        programmed
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tmrd </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> tMRD: min mode reg set cmd cycle time </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tmod </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> tMOD: min mode reg set cmd update time </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trrd </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> tRRD: min active to active command time </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_SPECVAL3_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  9;
     unsigned      twldqsen                                  :  6;
     unsigned      twlmrd                                    :  6;
     unsigned      tmrd                                      :  3;
     unsigned      tmod                                      :  4;
     unsigned      trrd                                      :  4;
#else    /* Little Endian */
     unsigned      trrd                                      :  4;
     unsigned      tmod                                      :  4;
     unsigned      tmrd                                      :  3;
     unsigned      twlmrd                                    :  6;
     unsigned      twldqsen                                  :  6;
     unsigned      reserved0                                 :  9;
#endif
} ncp_ddr_CFG_NTEMC_SPECVAL3_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_SPECVAL4_r_t
 *  @brief CFG_NTEMC_SPECVAL4
 *  @details Fourth group of DRAM timing parameters: scrubbing period, auto ZQCal period
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_SPECVAL4_r_t\n
 *   </td>
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
 *     <td width="30%"> @param scrub_per </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> This is the scrubbing period based on refresh req
 *        periods
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zqcal_per </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> This is the auto ZQCal period based either on clks
 *        or refresh req periods
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_SPECVAL4_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      scrub_per                                 : 12;
     unsigned      zqcal_per                                 : 16;
#else    /* Little Endian */
     unsigned      zqcal_per                                 : 16;
     unsigned      scrub_per                                 : 12;
     unsigned      reserved0                                 :  4;
#endif
} ncp_ddr_CFG_NTEMC_SPECVAL4_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_DFI_TIMING1_r_t
 *  @brief CFG_NTEMC_DFI_TIMING1
 *  @details First group of DFI timing parameters: controller to PHY timing parameters for reads and writes
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_DFI_TIMING1_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param tclk_ena </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> tCLK_ENA: max cycles from deassertion of clk_disable
 *        to first valid rising edge of external DRAM clk
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tclk_dis </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> tCLK_DIS: max cycles from assertion of clk_disable
 *        to external DRAM clk held deasserted
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 11 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tphy_rdlat </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> tPHY_RDLAT: maximum number of cycles between rddata_en
 *        assertion and rddata_valid
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trddataen </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> tRDDATAEN: rddata_en is asserted RDDATAEN cycles after
 *        the rd cmd on the DFI interface
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tphy_wrlat </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> tPHY_WRLAT: wrdata_en is asserted WRLAT cycles after
 *        the wrt cmd on the DFI interface
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tctrl_dly </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> tCTRL_DLY: Delay between assertion/de-assertion of
 *        dfi signal to external DRAM interface
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_DFI_TIMING1_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      tclk_ena                                  :  2;
     unsigned      tclk_dis                                  :  2;
     unsigned      reserved0                                 : 11;
     unsigned      tphy_rdlat                                :  3;
     unsigned      trddataen                                 :  5;
     unsigned      tphy_wrlat                                :  5;
     unsigned      tctrl_dly                                 :  4;
#else    /* Little Endian */
     unsigned      tctrl_dly                                 :  4;
     unsigned      tphy_wrlat                                :  5;
     unsigned      trddataen                                 :  5;
     unsigned      tphy_rdlat                                :  3;
     unsigned      reserved0                                 : 11;
     unsigned      tclk_dis                                  :  2;
     unsigned      tclk_ena                                  :  2;
#endif
} ncp_ddr_CFG_NTEMC_DFI_TIMING1_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_DFI_TIMING2_r_t
 *  @brief CFG_NTEMC_DFI_TIMING2
 *  @details Second group of DFI timing parameters: controller to PHY timing parameters for update requests and DRAM clk control
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_DFI_TIMING2_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param tphyupd_rsp </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> tPHYUPD_RSP: max cycles after assertion of phyupd_req
 *        to assertion of phyupd_ack
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tctlupd_max </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> tCTLUPD_MAX: max cycles that ctrlupd_req may be asserted </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tctlupd_min </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> tCTLUPD_MIN: min cycles that ctrlupd_req must be asserted </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tctlupd_intv </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> tCTLUPD_INTV: max number of refresh cycles that the
 *        controller may wait between assertions of ctrlupd_req
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_DFI_TIMING2_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      tphyupd_rsp                               : 12;
     unsigned      tctlupd_max                               :  4;
     unsigned      tctlupd_min                               :  3;
     unsigned      tctlupd_intv                              : 13;
#else    /* Little Endian */
     unsigned      tctlupd_intv                              : 13;
     unsigned      tctlupd_min                               :  3;
     unsigned      tctlupd_max                               :  4;
     unsigned      tphyupd_rsp                               : 12;
#endif
} ncp_ddr_CFG_NTEMC_DFI_TIMING2_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_DFI_TIMING3_r_t
 *  @brief CFG_NTEMC_DFI_TIMING3
 *  @details Third group of DFI timing parameters: controller training state machines to PHY training state machines
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_DFI_TIMING3_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param trdlvl_max </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> tRDLVL_MAX: max cycles to wait for a response to a
 *        read level enabling signal, rdlvl_en
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_DFI_TIMING3_r_t
 *
 */
 
typedef struct
{
     unsigned  int                trdlvl_max;
} ncp_ddr_CFG_NTEMC_DFI_TIMING3_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_DFI_TIMING4_r_t
 *  @brief CFG_NTEMC_DFI_TIMING4
 *  @details Fourth group of DFI timing parameters: controller training state machines to PHY training state machines
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_DFI_TIMING4_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param twrlvl_max </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> tWRLVL_MAX: max cycles to wait for a response to a
 *        write level enabling signal, wrlvl_en
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_DFI_TIMING4_r_t
 *
 */
 
typedef struct
{
     unsigned  int                twrlvl_max;
} ncp_ddr_CFG_NTEMC_DFI_TIMING4_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_DFI_TIMING5_r_t
 *  @brief CFG_NTEMC_DFI_TIMING5
 *  @details Fifth group of DFI timing parameters: controller training state machines to PHY training state machines
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_DFI_TIMING5_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param twrlvl_en </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> tWRLVL_EN: min cycles between assertion of dfi_wrlvl_en
 *        to the first write strobe
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trdlvl_en </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> tRDLVL_EN: min cycles between assertion of dfi_rdlvl_en
 *        or dfi_rdlvl_gate_en to the first read cmd
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param twrlvl_ww </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> tWRLVL_WW: min cycles for write leveling write strobe
 *        to write strobe delay
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trdlvl_rr </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> tRDLVL_RR: min cycles for read leveling read cmd to
 *        read cmd delay
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_DFI_TIMING5_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      twrlvl_en                                 :  6;
     unsigned      trdlvl_en                                 :  6;
     unsigned      twrlvl_ww                                 : 10;
     unsigned      trdlvl_rr                                 : 10;
#else    /* Little Endian */
     unsigned      trdlvl_rr                                 : 10;
     unsigned      twrlvl_ww                                 : 10;
     unsigned      trdlvl_en                                 :  6;
     unsigned      twrlvl_en                                 :  6;
#endif
} ncp_ddr_CFG_NTEMC_DFI_TIMING5_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_LOGBANKDEPTH_r_t
 *  @brief cfg_ntemc_logbankdepth
 *  @details Thermometer style depth gauge for logical bank queues
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_LOGBANKDEPTH_r_t\n
 *   </td>
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
 *     <td width="30%"> @param logbnkdepth </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> thermometer style depth gauge </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_LOGBANKDEPTH_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      logbnkdepth                               :  8;
#else    /* Little Endian */
     unsigned      logbnkdepth                               :  8;
     unsigned      reserved0                                 : 24;
#endif
} ncp_ddr_CFG_NTEMC_LOGBANKDEPTH_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_PREFETCHVAL_r_t
 *  @brief cfg_ntemc_prefetchvals
 *  @details Vector of the bank request prefetch register valids
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_PREFETCHVAL_r_t\n
 *   </td>
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
 *     <td width="30%"> @param prefvals </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> vector of bank request prefetch register valids </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_PREFETCHVAL_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      prefvals                                  :  8;
#else    /* Little Endian */
     unsigned      prefvals                                  :  8;
     unsigned      reserved0                                 : 24;
#endif
} ncp_ddr_CFG_NTEMC_PREFETCHVAL_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_AXI_ECC_ERR_ADDR_r_t
 *  @brief CFG_NTEMC_AXI_ECC_ERR_ADDR
 *  @details SBE or DBE address for AXI read requests
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_AXI_ECC_ERR_ADDR_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param axidbe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Address captured by DBE </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axieccadr </td>
 *     <td width="20%" align="center"> 31 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> AXI address that experienced an ECC error </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_AXI_ECC_ERR_ADDR_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      axidbe                                    :  1;
     unsigned      axieccadr                                 : 31;
#else    /* Little Endian */
     unsigned      axieccadr                                 : 31;
     unsigned      axidbe                                    :  1;
#endif
} ncp_ddr_CFG_NTEMC_AXI_ECC_ERR_ADDR_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_CFG_ECC_ERR_ADDR_r_t
 *  @brief CFG_NTEMC_CFG_ECC_ERR_ADDR
 *  @details SBE or DBE address for config read requests
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_CFG_ECC_ERR_ADDR_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cfgdbe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Address captured by DBE </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfgeccadr </td>
 *     <td width="20%" align="center"> 31 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Config address that experienced an ECC error </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_CFG_ECC_ERR_ADDR_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      cfgdbe                                    :  1;
     unsigned      cfgeccadr                                 : 31;
#else    /* Little Endian */
     unsigned      cfgeccadr                                 : 31;
     unsigned      cfgdbe                                    :  1;
#endif
} ncp_ddr_CFG_NTEMC_CFG_ECC_ERR_ADDR_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_SCRUB_ECC_ERR_ADDR_r_t
 *  @brief CFG_NTEMC_SCRUB_ECC_ERR_ADDR
 *  @details SBE or DBE address for scrub read requests
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_SCRUB_ECC_ERR_ADDR_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param scbdbe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Address captured by DBE </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param scbeccadr </td>
 *     <td width="20%" align="center"> 31 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Scrub address that experienced an ECC error </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_SCRUB_ECC_ERR_ADDR_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      scbdbe                                    :  1;
     unsigned      scbeccadr                                 : 31;
#else    /* Little Endian */
     unsigned      scbeccadr                                 : 31;
     unsigned      scbdbe                                    :  1;
#endif
} ncp_ddr_CFG_NTEMC_SCRUB_ECC_ERR_ADDR_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_AXI_ECC_ERR_SYNU_r_t
 *  @brief CFG_NTEMC_AXI_ECC_ERR_SYNU
 *  @details SBE AXI upper syndrome
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_AXI_ECC_ERR_SYNU_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param upp_syn </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> the bit corrected within bytes 7 through 4 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_AXI_ECC_ERR_SYNU_r_t
 *
 */
 
typedef struct
{
     unsigned  int                   upp_syn;
} ncp_ddr_CFG_NTEMC_AXI_ECC_ERR_SYNU_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_AXI_ECC_ERR_SYNL_r_t
 *  @brief CFG_NTEMC_AXI_ECC_ERR_SYNL
 *  @details SBE AXI lower syndrome
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_AXI_ECC_ERR_SYNL_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param low_syn </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> the bit corrected within bytes 3 through 0 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_AXI_ECC_ERR_SYNL_r_t
 *
 */
 
typedef struct
{
     unsigned  int                   low_syn;
} ncp_ddr_CFG_NTEMC_AXI_ECC_ERR_SYNL_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_CFG_ECC_ERR_SYNU_r_t
 *  @brief CFG_NTEMC_CFG_ECC_ERR_SYNU
 *  @details SBE config upper syndrome
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_CFG_ECC_ERR_SYNU_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param upp_syn </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> the bit corrected within bytes 7 through 4 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_CFG_ECC_ERR_SYNU_r_t
 *
 */
 
typedef struct
{
     unsigned  int                   upp_syn;
} ncp_ddr_CFG_NTEMC_CFG_ECC_ERR_SYNU_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_CFG_ECC_ERR_SYNL_r_t
 *  @brief CFG_NTEMC_CFG_ECC_ERR_SYNL
 *  @details SBE config lower syndrome
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_CFG_ECC_ERR_SYNL_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param low_syn </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> the bit corrected within bytes 3 through 0 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_CFG_ECC_ERR_SYNL_r_t
 *
 */
 
typedef struct
{
     unsigned  int                   low_syn;
} ncp_ddr_CFG_NTEMC_CFG_ECC_ERR_SYNL_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_SCRUB_ECC_ERR_SYNU_r_t
 *  @brief CFG_NTEMC_SCRUB_ECC_ERR_SYNU
 *  @details SBE scrub upper syndrome
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_SCRUB_ECC_ERR_SYNU_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param upp_syn </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> the bit corrected within bytes 7 through 4 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_SCRUB_ECC_ERR_SYNU_r_t
 *
 */
 
typedef struct
{
     unsigned  int                   upp_syn;
} ncp_ddr_CFG_NTEMC_SCRUB_ECC_ERR_SYNU_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_SCRUB_ECC_ERR_SYNL_r_t
 *  @brief CFG_NTEMC_SCRUB_ECC_ERR_SYNL
 *  @details SBE scrub lower syndrome
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_SCRUB_ECC_ERR_SYNL_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param low_syn </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> the bit corrected within bytes 3 through 0 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_SCRUB_ECC_ERR_SYNL_r_t
 *
 */
 
typedef struct
{
     unsigned  int                   low_syn;
} ncp_ddr_CFG_NTEMC_SCRUB_ECC_ERR_SYNL_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_ECC_CTRL_r_t
 *  @brief CFG_NTEMC_ECC_CTRL
 *  @details control for ecc behavior
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_ECC_CTRL_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 14 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bl_disable </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Bytelane disables </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param seleccbit </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Flip selected ecc bit </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param seldatabit </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Flip selected data bit </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_mc </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Multicycle ECC generation/correction enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_mode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> ECC mode </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_err_mode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Force ECC error mode </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_ECC_CTRL_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 14;
     unsigned      bl_disable                                :  2;
     unsigned      reserved1                                 :  3;
     unsigned      seleccbit                                 :  3;
     unsigned      seldatabit                                :  6;
     unsigned      ecc_mc                                    :  1;
     unsigned      ecc_mode                                  :  1;
     unsigned      ecc_err_mode                              :  2;
#else    /* Little Endian */
     unsigned      ecc_err_mode                              :  2;
     unsigned      ecc_mode                                  :  1;
     unsigned      ecc_mc                                    :  1;
     unsigned      seldatabit                                :  6;
     unsigned      seleccbit                                 :  3;
     unsigned      reserved1                                 :  3;
     unsigned      bl_disable                                :  2;
     unsigned      reserved0                                 : 14;
#endif
} ncp_ddr_CFG_NTEMC_ECC_CTRL_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_FRCD_ERR_ADDR_r_t
 *  @brief CFG_NTEMC_FRCD_ERR_ADDR
 *  @details address of single forced ECC error
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_FRCD_ERR_ADDR_r_t\n
 *   </td>
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
 *     <td width="30%"> @param frceccadr </td>
 *     <td width="20%" align="center"> 31 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> address forced to experience an ECC error </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_FRCD_ERR_ADDR_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      frceccadr                                 : 31;
#else    /* Little Endian */
     unsigned      frceccadr                                 : 31;
     unsigned      reserved0                                 :  1;
#endif
} ncp_ddr_CFG_NTEMC_FRCD_ERR_ADDR_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_HW_TEST_CTRL_r_t
 *  @brief CFG_NTEMC_HW_TEST_CTRL
 *  @details HW test controls and status
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_HW_TEST_CTRL_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hwmeminit </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Initialize memory/ecc with HW test data registers
 *        value. Set the test pattern select to hw_tst_reg,
 *        set test mode to all wrts then all rds, set number
 *        of operations to 32. Memory Init completion will be
 *        reflected in the status register and this bit will
 *        self-clear.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ena_max1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> DEBUG: Enable debug max addr limit for HW memory test </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param max1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DEBUG: Max Addr bit plus one for HW memory test address
 *        limit, value must be > 6.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param num_ops </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Number of reads or writes before switching in mixed
 *        mode, value must be 4,8,16 or 32 for either mixed
 *        or non-mixed mode.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clrhwerr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Clear hw test error </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param loopdir </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Scope loop write or read </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fail_mode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> HW memory fail mode </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param test_mode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> HW memory test mode </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param test_patt </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> HW memory test pattern </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param scope_lp </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> HW scope loop enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param test_ena </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> HW memory test enable </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_HW_TEST_CTRL_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  9;
     unsigned      hwmeminit                                 :  1;
     unsigned      ena_max1                                  :  1;
     unsigned      max1                                      :  5;
     unsigned      num_ops                                   :  6;
     unsigned      clrhwerr                                  :  1;
     unsigned      loopdir                                   :  1;
     unsigned      fail_mode                                 :  1;
     unsigned      test_mode                                 :  1;
     unsigned      test_patt                                 :  2;
     unsigned      scope_lp                                  :  2;
     unsigned      test_ena                                  :  2;
#else    /* Little Endian */
     unsigned      test_ena                                  :  2;
     unsigned      scope_lp                                  :  2;
     unsigned      test_patt                                 :  2;
     unsigned      test_mode                                 :  1;
     unsigned      fail_mode                                 :  1;
     unsigned      loopdir                                   :  1;
     unsigned      clrhwerr                                  :  1;
     unsigned      num_ops                                   :  6;
     unsigned      max1                                      :  5;
     unsigned      ena_max1                                  :  1;
     unsigned      hwmeminit                                 :  1;
     unsigned      reserved0                                 :  9;
#endif
} ncp_ddr_CFG_NTEMC_HW_TEST_CTRL_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_HW_TEST_DATA_UPR_r_t
 *  @brief CFG_NTEMC_HW_TEST_DATA_UPR
 *  @details HW test data source bytes 7 through 4, used for array testing, scope loop, memory initialization
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_HW_TEST_DATA_UPR_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param upp_test </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> HW test data bytes 7 through 4 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_HW_TEST_DATA_UPR_r_t
 *
 */
 
typedef struct
{
     unsigned  int                  upp_test;
} ncp_ddr_CFG_NTEMC_HW_TEST_DATA_UPR_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_HW_TEST_DATA_LWR_r_t
 *  @brief CFG_NTEMC_TEST_DATA_LWR
 *  @details HW test data source bytes 3 through 0, used for array testing, scope loop, memory initialization
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_HW_TEST_DATA_LWR_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param low_test </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> HW test data bytes 3 through 0 </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_HW_TEST_DATA_LWR_r_t
 *
 */
 
typedef struct
{
     unsigned  int                  low_test;
} ncp_ddr_CFG_NTEMC_HW_TEST_DATA_LWR_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_LD_SCRUB_r_t
 *  @brief CFG_NTEMC_LD_SCRUB
 *  @details loads the next scrub location addr ram with the contents of the scrub addr reg
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_LD_SCRUB_r_t\n
 *   </td>
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
 *     <td width="30%"> @param ldscrub </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> flag to initiate the next scrub addr load. SW sets
 *        it and HW resets it
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_LD_SCRUB_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 31;
     unsigned      ldscrub                                   :  1;
#else    /* Little Endian */
     unsigned      ldscrub                                   :  1;
     unsigned      reserved0                                 : 31;
#endif
} ncp_ddr_CFG_NTEMC_LD_SCRUB_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_LD_HWTEST_r_t
 *  @brief CFG_NTEMC_LD_HWTEST
 *  @details loads the initial address used in hwtest with the contents of the scrub addr reg
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_LD_HWTEST_r_t\n
 *   </td>
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
 *     <td width="30%"> @param ldhwtest </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DEBUG: flag to override the initial hw test address
 *        value. SW sets it and HW resets it
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_LD_HWTEST_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 31;
     unsigned      ldhwtest                                  :  1;
#else    /* Little Endian */
     unsigned      ldhwtest                                  :  1;
     unsigned      reserved0                                 : 31;
#endif
} ncp_ddr_CFG_NTEMC_LD_HWTEST_r_t;

/*! @struct ncp_ddr_CFG_SCRUB_ADDR_r_t
 *  @brief CFG_TEST_ADDR
 *  @details Multi-purpose address reg or can be loaded for HW based scope loop testing
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_SCRUB_ADDR_r_t\n
 *   </td>
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
 *     <td width="30%"> @param scrub_addr </td>
 *     <td width="20%" align="center"> 31 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> multi-purpose address register </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_SCRUB_ADDR_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      scrub_addr                                : 31;
#else    /* Little Endian */
     unsigned      scrub_addr                                : 31;
     unsigned      reserved0                                 :  1;
#endif
} ncp_ddr_CFG_SCRUB_ADDR_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_DDR_SM_STATUS_r_t
 *  @brief CFG_NTEMC_DDR_SM_STATE
 *  @details DDR controller state machines' encoded states
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_DDR_SM_STATUS_r_t\n
 *   </td>
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
 *     <td width="30%"> @param ddrtrngsm </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> current state of dfi training intf sm </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ddrarbsm </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> current state of axi/cfg ddr arbiter sm </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axiunlsm </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> current state of axi logical bank q sm </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfgreqsm </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> current state of cfg rqst conversion sm </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_DDR_SM_STATUS_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  5;
     unsigned      ddrtrngsm                                 :  3;
     unsigned      reserved1                                 :  4;
     unsigned      ddrarbsm                                  :  4;
     unsigned      reserved2                                 :  6;
     unsigned      axiunlsm                                  :  2;
     unsigned      reserved3                                 :  3;
     unsigned      cfgreqsm                                  :  5;
#else    /* Little Endian */
     unsigned      cfgreqsm                                  :  5;
     unsigned      reserved3                                 :  3;
     unsigned      axiunlsm                                  :  2;
     unsigned      reserved2                                 :  6;
     unsigned      ddrarbsm                                  :  4;
     unsigned      reserved1                                 :  4;
     unsigned      ddrtrngsm                                 :  3;
     unsigned      reserved0                                 :  5;
#endif
} ncp_ddr_CFG_NTEMC_DDR_SM_STATUS_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_HWTEST_FAILADDR_r_t
 *  @brief CFG_NTEMC_HWTEST_FAILADDR
 *  @details First read address for hw test data compare failure
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_HWTEST_FAILADDR_r_t\n
 *   </td>
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
 *     <td width="30%"> @param hwtstfailaddr </td>
 *     <td width="20%" align="center"> 31 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> read address of first hw test data compare failure </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_HWTEST_FAILADDR_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      hwtstfailaddr                             : 31;
#else    /* Little Endian */
     unsigned      hwtstfailaddr                             : 31;
     unsigned      reserved0                                 :  1;
#endif
} ncp_ddr_CFG_NTEMC_HWTEST_FAILADDR_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_HWTEST_FAILEXPU_r_t
 *  @brief CFG_NTEMC_HWTEST_FAILEXPU
 *  @details Upper bytes of expected data for hw test data compare failure
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_HWTEST_FAILEXPU_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param hwtstexpdatu </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> upper bytes of expected data for first hw test data
 *        compare failure
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_HWTEST_FAILEXPU_r_t
 *
 */
 
typedef struct
{
     unsigned  int              hwtstexpdatu;
} ncp_ddr_CFG_NTEMC_HWTEST_FAILEXPU_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_HWTEST_FAILEXPL_r_t
 *  @brief CFG_NTEMC_HWTEST_FAILEXPL
 *  @details Lower bytes of expected data for hw test data compare failure
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_HWTEST_FAILEXPL_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param hwtstexpdatl </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> lower bytes of expected data for first hw test data
 *        compare failure
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_HWTEST_FAILEXPL_r_t
 *
 */
 
typedef struct
{
     unsigned  int              hwtstexpdatl;
} ncp_ddr_CFG_NTEMC_HWTEST_FAILEXPL_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_HWTEST_FAILACTU_r_t
 *  @brief CFG_NTEMC_HWTEST_FAILACTU
 *  @details Upper bytes of actual data for hw test data compare failure
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_HWTEST_FAILACTU_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param hwtstactdatu </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> upper bytes of actual data for first hw test data
 *        compare failure
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_HWTEST_FAILACTU_r_t
 *
 */
 
typedef struct
{
     unsigned  int              hwtstactdatu;
} ncp_ddr_CFG_NTEMC_HWTEST_FAILACTU_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_HWTEST_FAILACTL_r_t
 *  @brief CFG_NTEMC_HWTEST_FAILACTL
 *  @details Lower bytes of actual data for hw test data compare failure
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_HWTEST_FAILACTL_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param hwtstactdatl </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> lower bytes of actual data for first hw test data
 *        compare failure
 *   </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_HWTEST_FAILACTL_r_t
 *
 */
 
typedef struct
{
     unsigned  int              hwtstactdatl;
} ncp_ddr_CFG_NTEMC_HWTEST_FAILACTL_r_t;

/*! @struct ncp_ddr_CFG_NTEMC_PHY_DEBUG_STATUS_r_t
 *  @brief CFG_NTEMC_PHY_DEBUG_STATUS
 *  @details Calibration state machine debug info from phy
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_ddr_CFG_NTEMC_PHY_DEBUG_STATUS_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param phydebug </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> current state of phy calibration sm </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CFG_NTEMC_PHY_DEBUG_STATUS_r_t
 *
 */
 
typedef struct
{
     unsigned  int                  phydebug;
} ncp_ddr_CFG_NTEMC_PHY_DEBUG_STATUS_r_t;

/*! @struct ncp_ddr_CMDHIST_memory_r_t
 *  @brief Multi-word data structure
 *  <table width="70%" align="center">
 *   <tr>
 *     <td colspan="4" align="center">
 *       struct ncp_ddr_CMDHIST_memory_r_t
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
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmd_histts </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> saturating delta clock count </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmd_histsrc </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> command source AXI,CFG </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmd_histrowcmd </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> activate (row) cmd or any single cmd of csn,rasn,casn,wen </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmd_histcolcmd </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> read/write (col) cmd of csn,rasn,casn,wen </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmd_histap </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> AP bit, applicable for reads/writes/precharges </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmd_histaddr </td>
 *     <td width="20%" align="center"> 31 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> command's address when applicable </td>
 * </tr>
 * </table>
 * Applies to: acp2500 --> ncp_ddr_CMDHIST_memory_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
          /* word 0 */
     unsigned      reserved0                                 : 10;
     unsigned      cmd_histts                                : 12;
     unsigned      cmd_histsrc                               :  2;
     unsigned      cmd_histrowcmd                            :  4;
     unsigned      cmd_histcolcmd                            :  4;
          /* word 1 */
     unsigned      cmd_histap                                :  1;
     unsigned      cmd_histaddr                              : 31;
#else    /* Little Endian */
          /* word 0 */
     unsigned      cmd_histcolcmd                            :  4;
     unsigned      cmd_histrowcmd                            :  4;
     unsigned      cmd_histsrc                               :  2;
     unsigned      cmd_histts                                : 12;
     unsigned      reserved0                                 : 10;
          /* word 1 */
     unsigned      cmd_histaddr                              : 31;
     unsigned      cmd_histap                                :  1;
#endif
} ncp_ddr_CMDHIST_memory_r_t;

#ifdef __cplusplus
}
#endif

#endif /* _NCP_DDR_REGS_H_ */
