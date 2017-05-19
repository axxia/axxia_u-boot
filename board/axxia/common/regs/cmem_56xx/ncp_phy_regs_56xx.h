/*
 *  Copyright (C) 2016 Intel (john.jacques@intel.com)
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

#ifndef _NCP_PHY_REGS_H_
#define _NCP_PHY_REGS_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __UBOOT__
#include "ncp_sal_types.h"
#endif

/*! @struct ncp_phy_RIDR_t
 *  @brief null
 *  @details Revision Identification Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_RIDR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param udrid </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> User-Defined Revision ID. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param phymjr </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> PHY Major Revision. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param phymdr </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> PHY Moderate Revision. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param phymnr </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> PHY Minor Revision. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pubmjr </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> PUB Major Revision. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pubmdr </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> PUB Moderate Revision. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pubmnr </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PUB Minor Revision. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_RIDR_t
 *
 * Implemented by: 
 *      RIDR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      udrid                                     :  8;
     unsigned      phymjr                                    :  4;
     unsigned      phymdr                                    :  4;
     unsigned      phymnr                                    :  4;
     unsigned      pubmjr                                    :  4;
     unsigned      pubmdr                                    :  4;
     unsigned      pubmnr                                    :  4;
#else    /* Little Endian */
     unsigned      pubmnr                                    :  4;
     unsigned      pubmdr                                    :  4;
     unsigned      pubmjr                                    :  4;
     unsigned      phymnr                                    :  4;
     unsigned      phymdr                                    :  4;
     unsigned      phymjr                                    :  4;
     unsigned      udrid                                     :  8;
#endif
} ncp_phy_RIDR_t;

/*! @struct ncp_phy_PIR_t
 *  @brief null
 *  @details PHY Initialization Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_PIR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zcalbyp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Impedance Calibration Bypass. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dcalpse </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Digital Delay Line (DDL) Calibration Pause. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_28_20 </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdimminit </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> RDIMM Initialization. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ctldinit </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Controller DRAM Initialization. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> HOST VREF Training. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param srd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Static Read Training. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wreye </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Write Data Eye Training. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdeye </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Read Data Eye Training. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrdskw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Write Data Bit Deskew. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rddskw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Read Data Bit Deskew. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wladj </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Write Leveling Adjust. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param qsgate </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Read DQS Gate Training. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wl </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Write Leveling. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param draminit </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DRAM Initialization. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dramrst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> DRAM Reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param phyrst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> PHY Reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dcal </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Digital Delay Line (DDL) Calibration. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pllinit </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> PLL Initialiazation. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ca </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CA Training. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zcal </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Impedance Calibration. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param init </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Initialization Trigger. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_PIR_t
 *
 * Implemented by: 
 *      PIR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31                               :  1;
     unsigned      zcalbyp                                   :  1;
     unsigned      dcalpse                                   :  1;
     unsigned      reserved_28_20                            :  9;
     unsigned      rdimminit                                 :  1;
     unsigned      ctldinit                                  :  1;
     unsigned      vref                                      :  1;
     unsigned      srd                                       :  1;
     unsigned      wreye                                     :  1;
     unsigned      rdeye                                     :  1;
     unsigned      wrdskw                                    :  1;
     unsigned      rddskw                                    :  1;
     unsigned      wladj                                     :  1;
     unsigned      qsgate                                    :  1;
     unsigned      wl                                        :  1;
     unsigned      draminit                                  :  1;
     unsigned      dramrst                                   :  1;
     unsigned      phyrst                                    :  1;
     unsigned      dcal                                      :  1;
     unsigned      pllinit                                   :  1;
     unsigned      reserved_3                                :  1;
     unsigned      ca                                        :  1;
     unsigned      zcal                                      :  1;
     unsigned      init                                      :  1;
#else    /* Little Endian */
     unsigned      init                                      :  1;
     unsigned      zcal                                      :  1;
     unsigned      ca                                        :  1;
     unsigned      reserved_3                                :  1;
     unsigned      pllinit                                   :  1;
     unsigned      dcal                                      :  1;
     unsigned      phyrst                                    :  1;
     unsigned      dramrst                                   :  1;
     unsigned      draminit                                  :  1;
     unsigned      wl                                        :  1;
     unsigned      qsgate                                    :  1;
     unsigned      wladj                                     :  1;
     unsigned      rddskw                                    :  1;
     unsigned      wrdskw                                    :  1;
     unsigned      rdeye                                     :  1;
     unsigned      wreye                                     :  1;
     unsigned      srd                                       :  1;
     unsigned      vref                                      :  1;
     unsigned      ctldinit                                  :  1;
     unsigned      rdimminit                                 :  1;
     unsigned      reserved_28_20                            :  9;
     unsigned      dcalpse                                   :  1;
     unsigned      zcalbyp                                   :  1;
     unsigned      reserved_31                               :  1;
#endif
} ncp_phy_PIR_t;

/*! @struct ncp_phy_PGCR0_t
 *  @brief null
 *  @details PHY General Configuration Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_PGCR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param adcp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Address Copy. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_30_27 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param phyfrst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> PHY FIFO Reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param oscacdl </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Oscillator Mode Address/Command Delay Line Select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param oscwddl </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Oscillator Mode Write-Data Delay Line Select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_21 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param oscwdl </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Oscillator Mode Write-Leveling Delay Line Select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtosel </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Digital Test Output Select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param acwlpon </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Address/Command Write leveling Pipeline Always On. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param oscdiv </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Oscillator Mode Division. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param oscen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Oscillator Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dltst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Delay Line Test Start. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dltmode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Delay Line Test Mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clrtstat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Clear Training Status Registers. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clrperr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Clear Partiy Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param initfsmbyp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Initialization Bypass. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pllfsmbyp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> PLL FSM Bypass. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clrzcal </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Clear Impedance Calibration. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param icpc </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Initialization Complete Pin Configuration. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_PGCR0_t
 *
 * Implemented by: 
 *      PGCR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      adcp                                      :  1;
     unsigned      reserved_30_27                            :  4;
     unsigned      phyfrst                                   :  1;
     unsigned      oscacdl                                   :  2;
     unsigned      oscwddl                                   :  2;
     unsigned      reserved_21                               :  1;
     unsigned      oscwdl                                    :  2;
     unsigned      dtosel                                    :  5;
     unsigned      acwlpon                                   :  1;
     unsigned      oscdiv                                    :  4;
     unsigned      oscen                                     :  1;
     unsigned      dltst                                     :  1;
     unsigned      dltmode                                   :  1;
     unsigned      clrtstat                                  :  1;
     unsigned      clrperr                                   :  1;
     unsigned      initfsmbyp                                :  1;
     unsigned      pllfsmbyp                                 :  1;
     unsigned      clrzcal                                   :  1;
     unsigned      icpc                                      :  1;
#else    /* Little Endian */
     unsigned      icpc                                      :  1;
     unsigned      clrzcal                                   :  1;
     unsigned      pllfsmbyp                                 :  1;
     unsigned      initfsmbyp                                :  1;
     unsigned      clrperr                                   :  1;
     unsigned      clrtstat                                  :  1;
     unsigned      dltmode                                   :  1;
     unsigned      dltst                                     :  1;
     unsigned      oscen                                     :  1;
     unsigned      oscdiv                                    :  4;
     unsigned      acwlpon                                   :  1;
     unsigned      dtosel                                    :  5;
     unsigned      oscwdl                                    :  2;
     unsigned      reserved_21                               :  1;
     unsigned      oscwddl                                   :  2;
     unsigned      oscacdl                                   :  2;
     unsigned      phyfrst                                   :  1;
     unsigned      reserved_30_27                            :  4;
     unsigned      adcp                                      :  1;
#endif
} ncp_phy_PGCR0_t;

/*! @struct ncp_phy_PGCR1_t
 *  @brief null
 *  @details PHY General Configuration Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_PGCR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param lbmode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Loopback Mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lbgdqs </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Loopback DQS Gating. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lbdqss </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Loopback DQS Shift. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param iolb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> I/O Loop-Back Select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dlyldtm </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Delay Load Timing. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param phyhrst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> PHY High-Speed Reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param acvldtrn </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> AC Loopback Valid Train. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param acvlddly </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> AC Loopback Valid Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_20 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved. Returns zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_19 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved. Returns zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param updmstrc0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> DFI Update Master Channel 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpmstrc0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Low-Power Master Channel 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param acpddc </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> AC Power-Down with Dual Channels. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dualchn </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Dual Channel Configuration. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fdepth </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Filter Depth. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpfdepth </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Low-Pass Filter Depth. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpfen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Low-Pass Filter Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mdlen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Master Delay Line Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ioddrm </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> I/O DDR Mode (D3F I/O Only). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pubmode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Enables, if set, the PUB to control the interface
 *        to the PHY and SDRAM.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ddlbypmode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Controls DDL Bypass Modes. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wluncrt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Write Level Uncertainty Region. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wlstep </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Write Leveling Step. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wlmode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Write Leveling (Software) Mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtomode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Digital Test Output Mode. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_PGCR1_t
 *
 * Implemented by: 
 *      PGCR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      lbmode                                    :  1;
     unsigned      lbgdqs                                    :  2;
     unsigned      lbdqss                                    :  1;
     unsigned      iolb                                      :  1;
     unsigned      dlyldtm                                   :  1;
     unsigned      phyhrst                                   :  1;
     unsigned      acvldtrn                                  :  1;
     unsigned      acvlddly                                  :  3;
     unsigned      reserved_20                               :  1;
     unsigned      reserved_19                               :  1;
     unsigned      updmstrc0                                 :  1;
     unsigned      lpmstrc0                                  :  1;
     unsigned      acpddc                                    :  1;
     unsigned      dualchn                                   :  1;
     unsigned      fdepth                                    :  2;
     unsigned      lpfdepth                                  :  2;
     unsigned      lpfen                                     :  1;
     unsigned      mdlen                                     :  1;
     unsigned      ioddrm                                    :  2;
     unsigned      pubmode                                   :  1;
     unsigned      ddlbypmode                                :  2;
     unsigned      wluncrt                                   :  1;
     unsigned      wlstep                                    :  1;
     unsigned      wlmode                                    :  1;
     unsigned      dtomode                                   :  1;
#else    /* Little Endian */
     unsigned      dtomode                                   :  1;
     unsigned      wlmode                                    :  1;
     unsigned      wlstep                                    :  1;
     unsigned      wluncrt                                   :  1;
     unsigned      ddlbypmode                                :  2;
     unsigned      pubmode                                   :  1;
     unsigned      ioddrm                                    :  2;
     unsigned      mdlen                                     :  1;
     unsigned      lpfen                                     :  1;
     unsigned      lpfdepth                                  :  2;
     unsigned      fdepth                                    :  2;
     unsigned      dualchn                                   :  1;
     unsigned      acpddc                                    :  1;
     unsigned      lpmstrc0                                  :  1;
     unsigned      updmstrc0                                 :  1;
     unsigned      reserved_19                               :  1;
     unsigned      reserved_20                               :  1;
     unsigned      acvlddly                                  :  3;
     unsigned      acvldtrn                                  :  1;
     unsigned      phyhrst                                   :  1;
     unsigned      dlyldtm                                   :  1;
     unsigned      iolb                                      :  1;
     unsigned      lbdqss                                    :  1;
     unsigned      lbgdqs                                    :  2;
     unsigned      lbmode                                    :  1;
#endif
} ncp_phy_PGCR1_t;

/*! @struct ncp_phy_PGCR2_t
 *  @brief null
 *  @details PHY General Configuration Register 2
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_PGCR2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_29 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fxdlatincr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Fixed Latency programmable Increment. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtpmxtmr </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Data Training PUB Mode Exit Timer. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fxdlat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Fixed Latency. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param nobub </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> No Bubbles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trefprd </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Refresh Period. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_PGCR2_t
 *
 * Implemented by: 
 *      PGCR2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_29                            :  3;
     unsigned      fxdlatincr                                :  1;
     unsigned      dtpmxtmr                                  :  8;
     unsigned      fxdlat                                    :  1;
     unsigned      nobub                                     :  1;
     unsigned      trefprd                                   : 18;
#else    /* Little Endian */
     unsigned      trefprd                                   : 18;
     unsigned      nobub                                     :  1;
     unsigned      fxdlat                                    :  1;
     unsigned      dtpmxtmr                                  :  8;
     unsigned      fxdlatincr                                :  1;
     unsigned      reserved_31_29                            :  3;
#endif
} ncp_phy_PGCR2_t;

/*! @struct ncp_phy_PGCR3_t
 *  @brief null
 *  @details PHY General Configuration Register 3
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_PGCR3_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param lpwakeup_thrsh </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Low Power Wakeup Threshold. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdbiclsel </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Read DBI CAS Latency Select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdbi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Read Data Bus Inversion Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wdbi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Write Data Bus Inversion Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param prfbyp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> PUB Read FIFO Bypass. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cken </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> CK Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gatedxrdclk </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Enable Clock Gating for DX ddr_clk. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gatedxddrclk </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Enable Clock Gating for DX ctl_rd_clk. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gatedxctlclk </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Enable Clock Gating for DX ctl_clk. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disacoe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Disables the Output Enables for all 35 bit AC. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gateacrdclk </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Enable Clock Gating for AC ctl_rd_clk. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gateacddrclk </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Enable Clock Gating for AC ddr_clk. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gateacctlclk </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Enable Clock Gating for AC ctl_clk. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lbgsdqs </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Load GSDQS LCDL with 2x the calibrated GSDQSPRD value
 *        (equivalent to one CK period).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdbicl </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Read DBI CAS Latency. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdmode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> DATX8 Receive FIFO Read Mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disrst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> When set, disables the synchronous clear of DFI FIFOs
 *        that is triggered automatically during a controller
 *        of PHY requested VT-update, or by the built-in VT-update
 *        request issued at the start of a training sequence.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param clklevel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Selects the level to which clocks will be stalled
 *        when clock gating is enabled in PHY.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_PGCR3_t
 *
 * Implemented by: 
 *      PGCR3
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      lpwakeup_thrsh                            :  4;
     unsigned      rdbiclsel                                 :  1;
     unsigned      rdbi                                      :  1;
     unsigned      wdbi                                      :  1;
     unsigned      prfbyp                                    :  1;
     unsigned      cken                                      :  8;
     unsigned      gatedxrdclk                               :  1;
     unsigned      gatedxddrclk                              :  1;
     unsigned      gatedxctlclk                              :  1;
     unsigned      disacoe                                   :  1;
     unsigned      gateacrdclk                               :  1;
     unsigned      gateacddrclk                              :  1;
     unsigned      gateacctlclk                              :  1;
     unsigned      lbgsdqs                                   :  1;
     unsigned      rdbicl                                    :  3;
     unsigned      rdmode                                    :  2;
     unsigned      disrst                                    :  1;
     unsigned      clklevel                                  :  2;
#else    /* Little Endian */
     unsigned      clklevel                                  :  2;
     unsigned      disrst                                    :  1;
     unsigned      rdmode                                    :  2;
     unsigned      rdbicl                                    :  3;
     unsigned      lbgsdqs                                   :  1;
     unsigned      gateacctlclk                              :  1;
     unsigned      gateacddrclk                              :  1;
     unsigned      gateacrdclk                               :  1;
     unsigned      disacoe                                   :  1;
     unsigned      gatedxctlclk                              :  1;
     unsigned      gatedxddrclk                              :  1;
     unsigned      gatedxrdclk                               :  1;
     unsigned      cken                                      :  8;
     unsigned      prfbyp                                    :  1;
     unsigned      wdbi                                      :  1;
     unsigned      rdbi                                      :  1;
     unsigned      rdbiclsel                                 :  1;
     unsigned      lpwakeup_thrsh                            :  4;
#endif
} ncp_phy_PGCR3_t;

/*! @struct ncp_phy_PGCR4_t
 *  @brief null
 *  @details PHY General Configuration Register 4
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_PGCR4_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param acrdmode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> AC Loopback FIFO Read Mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param acdccbyp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> AC Duty Cycle Correction Bypass. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param acddlld </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> AC DDL Delay Select Dymainc Load. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param acddlbyp </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> AC DDL Bypass. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_21 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxddlld </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DATX8 DDL Delay Select Dymainc Load. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxddlbyp </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DATX8 DDL Bypass. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_PGCR4_t
 *
 * Implemented by: 
 *      PGCR4
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      acrdmode                                  :  1;
     unsigned      acdccbyp                                  :  1;
     unsigned      acddlld                                   :  1;
     unsigned      acddlbyp                                  :  5;
     unsigned      reserved_23_21                            :  3;
     unsigned      dxddlld                                   :  5;
     unsigned      dxddlbyp                                  : 16;
#else    /* Little Endian */
     unsigned      dxddlbyp                                  : 16;
     unsigned      dxddlld                                   :  5;
     unsigned      reserved_23_21                            :  3;
     unsigned      acddlbyp                                  :  5;
     unsigned      acddlld                                   :  1;
     unsigned      acdccbyp                                  :  1;
     unsigned      acrdmode                                  :  1;
#endif
} ncp_phy_PGCR4_t;

/*! @struct ncp_phy_PGCR5_t
 *  @brief null
 *  @details PHY General Configuration Register 5
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_PGCR5_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_24 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param frqat </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Frequency A Ratio Term. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_PGCR5_t
 *
 * Implemented by: 
 *      PGCR5
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_24                            :  8;
     unsigned      frqat                                     :  8;
     unsigned      reserved_15_0                             : 16;
#else    /* Little Endian */
     unsigned      reserved_15_0                             : 16;
     unsigned      frqat                                     :  8;
     unsigned      reserved_31_24                            :  8;
#endif
} ncp_phy_PGCR5_t;

/*! @struct ncp_phy_PGCR6_t
 *  @brief null
 *  @details PHY General Configuration Register 6
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_PGCR6_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_24 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved. Returns zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dldlmt </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Delay Line VT Drift Limit. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Returns zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param acdlvt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> AC Address/Command Delay LCDL VT Compensation. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param acbvt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Address/Command Bit Delay VT Compensation. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odtbvt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> ODT Bit Delay VT Compensation. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ckebvt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> CKE Bit Delay VT Compensation. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param csnbvt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> CSN Bit Delay VT Compensation. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ckbvt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> CK Bit Delay VT Compensation. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved. Returns zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fvt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Forced VT Compensation Trigger. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param inhvt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> VT Calculation Inhibit. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_PGCR6_t
 *
 * Implemented by: 
 *      PGCR6
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_24                            :  8;
     unsigned      dldlmt                                    :  8;
     unsigned      reserved_15_14                            :  2;
     unsigned      acdlvt                                    :  1;
     unsigned      acbvt                                     :  1;
     unsigned      odtbvt                                    :  1;
     unsigned      ckebvt                                    :  1;
     unsigned      csnbvt                                    :  1;
     unsigned      ckbvt                                     :  1;
     unsigned      reserved_7_2                              :  6;
     unsigned      fvt                                       :  1;
     unsigned      inhvt                                     :  1;
#else    /* Little Endian */
     unsigned      inhvt                                     :  1;
     unsigned      fvt                                       :  1;
     unsigned      reserved_7_2                              :  6;
     unsigned      ckbvt                                     :  1;
     unsigned      csnbvt                                    :  1;
     unsigned      ckebvt                                    :  1;
     unsigned      odtbvt                                    :  1;
     unsigned      acbvt                                     :  1;
     unsigned      acdlvt                                    :  1;
     unsigned      reserved_15_14                            :  2;
     unsigned      dldlmt                                    :  8;
     unsigned      reserved_31_24                            :  8;
#endif
} ncp_phy_PGCR6_t;

/*! @struct ncp_phy_PGCR7_t
 *  @brief null
 *  @details PHY General Configuration Register 7
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_PGCR7_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dxrsvd </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> These bits are reserved for future DATX8 special PHY
 *        modes but the registers are already connected to existing
 *        (unused) DATX8 phy_mode bits.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxrclkmd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> DATX8 read Clock Mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxqsgsel </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> DQS Gate Select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxdtosel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> DATX8 Digital Test Output Select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxgsmd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Read DQS gating status mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxddlldt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> DX DDL Load Type. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxqsdbyp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Read DQS/DQS_N delay load bypass mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxgdbyp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Read DQS gate delay load bypass mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxtmode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DATX8 Test Mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved. Returns zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param acrsvd_7_5 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> These bits are reserved for future AC special PHY
 *        modes but the registers are already connected to existing
 *        (unused) AC phy_mode bits.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param acrclkmd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> AC read Clock Mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param acdldt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> AC DDL Load Type. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param acrsvd_2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> This bit is reserved for future AC special PHY modes
 *        but the register is already connected to existing
 *        (unused) AC phy_mode bits.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param acdtosel </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> AC Digital Test Output Select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param actmode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> AC Test Mode. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_PGCR7_t
 *
 * Implemented by: 
 *      PGCR7
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      dxrsvd                                    :  7;
     unsigned      dxrclkmd                                  :  1;
     unsigned      dxqsgsel                                  :  1;
     unsigned      dxdtosel                                  :  2;
     unsigned      dxgsmd                                    :  1;
     unsigned      dxddlldt                                  :  1;
     unsigned      dxqsdbyp                                  :  1;
     unsigned      dxgdbyp                                   :  1;
     unsigned      dxtmode                                   :  1;
     unsigned      reserved_15_8                             :  8;
     unsigned      acrsvd_7_5                                :  3;
     unsigned      acrclkmd                                  :  1;
     unsigned      acdldt                                    :  1;
     unsigned      acrsvd_2                                  :  1;
     unsigned      acdtosel                                  :  1;
     unsigned      actmode                                   :  1;
#else    /* Little Endian */
     unsigned      actmode                                   :  1;
     unsigned      acdtosel                                  :  1;
     unsigned      acrsvd_2                                  :  1;
     unsigned      acdldt                                    :  1;
     unsigned      acrclkmd                                  :  1;
     unsigned      acrsvd_7_5                                :  3;
     unsigned      reserved_15_8                             :  8;
     unsigned      dxtmode                                   :  1;
     unsigned      dxgdbyp                                   :  1;
     unsigned      dxqsdbyp                                  :  1;
     unsigned      dxddlldt                                  :  1;
     unsigned      dxgsmd                                    :  1;
     unsigned      dxdtosel                                  :  2;
     unsigned      dxqsgsel                                  :  1;
     unsigned      dxrclkmd                                  :  1;
     unsigned      dxrsvd                                    :  7;
#endif
} ncp_phy_PGCR7_t;

/*! @struct ncp_phy_PGSR0_t
 *  @brief null
 *  @details PHY General Status Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_PGSR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param aplock </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> AC PLL Lock. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param srderr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Static Read Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cawrn </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> CA Training Warning. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param caerr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> CA Training Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param weerr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Write Eye Training Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reerr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Read Eye Training Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wderr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Write Bit Deskew Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rderr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Read Bit Deskew Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wlaerr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Write Leveling Adjustment Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param qsgerr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> DQS Gate Training Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wlerr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Write Leveling Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zcerr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Impedance Calibration Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param verr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> VREF Training Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_18_15 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved. Returns zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vdone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> HOST VREF Training Done. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param srddone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Static Read Done. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cadone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> CA Training Done. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wedone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Write Eye Training Done. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param redone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Read Eye Training Done. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wddone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Write Bit Deskew Done. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rddone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Read Bit Deskew Done. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wladone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Write Leveling Adjustment Done. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param qsgdone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> DQS Gate Training Done. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wldone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Write Leveling Done. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param didone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> DRAM Initialization Done. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zcdone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Impedance Calibration Done. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dcdone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Digital Delay Line (DDL) Calibration Done. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pldone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> PLL Lock Done. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param idone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Initialization Done. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_PGSR0_t
 *
 * Implemented by: 
 *      PGSR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      aplock                                    :  1;
     unsigned      srderr                                    :  1;
     unsigned      cawrn                                     :  1;
     unsigned      caerr                                     :  1;
     unsigned      weerr                                     :  1;
     unsigned      reerr                                     :  1;
     unsigned      wderr                                     :  1;
     unsigned      rderr                                     :  1;
     unsigned      wlaerr                                    :  1;
     unsigned      qsgerr                                    :  1;
     unsigned      wlerr                                     :  1;
     unsigned      zcerr                                     :  1;
     unsigned      verr                                      :  1;
     unsigned      reserved_18_15                            :  4;
     unsigned      vdone                                     :  1;
     unsigned      srddone                                   :  1;
     unsigned      cadone                                    :  1;
     unsigned      wedone                                    :  1;
     unsigned      redone                                    :  1;
     unsigned      wddone                                    :  1;
     unsigned      rddone                                    :  1;
     unsigned      wladone                                   :  1;
     unsigned      qsgdone                                   :  1;
     unsigned      wldone                                    :  1;
     unsigned      didone                                    :  1;
     unsigned      zcdone                                    :  1;
     unsigned      dcdone                                    :  1;
     unsigned      pldone                                    :  1;
     unsigned      idone                                     :  1;
#else    /* Little Endian */
     unsigned      idone                                     :  1;
     unsigned      pldone                                    :  1;
     unsigned      dcdone                                    :  1;
     unsigned      zcdone                                    :  1;
     unsigned      didone                                    :  1;
     unsigned      wldone                                    :  1;
     unsigned      qsgdone                                   :  1;
     unsigned      wladone                                   :  1;
     unsigned      rddone                                    :  1;
     unsigned      wddone                                    :  1;
     unsigned      redone                                    :  1;
     unsigned      wedone                                    :  1;
     unsigned      cadone                                    :  1;
     unsigned      srddone                                   :  1;
     unsigned      vdone                                     :  1;
     unsigned      reserved_18_15                            :  4;
     unsigned      verr                                      :  1;
     unsigned      zcerr                                     :  1;
     unsigned      wlerr                                     :  1;
     unsigned      qsgerr                                    :  1;
     unsigned      wlaerr                                    :  1;
     unsigned      rderr                                     :  1;
     unsigned      wderr                                     :  1;
     unsigned      reerr                                     :  1;
     unsigned      weerr                                     :  1;
     unsigned      caerr                                     :  1;
     unsigned      cawrn                                     :  1;
     unsigned      srderr                                    :  1;
     unsigned      aplock                                    :  1;
#endif
} ncp_phy_PGSR0_t;

/*! @struct ncp_phy_PGSR1_t
 *  @brief null
 *  @details PHY General Status Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_PGSR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param parerr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> RDIMM Parity Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vtstop </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> VT Stop. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_29_25 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Reserved. Returns zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dltcode </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Delay Line Test Code. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dltdone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Delay Line Test Done. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_PGSR1_t
 *
 * Implemented by: 
 *      PGSR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      parerr                                    :  1;
     unsigned      vtstop                                    :  1;
     unsigned      reserved_29_25                            :  5;
     unsigned      dltcode                                   : 24;
     unsigned      dltdone                                   :  1;
#else    /* Little Endian */
     unsigned      dltdone                                   :  1;
     unsigned      dltcode                                   : 24;
     unsigned      reserved_29_25                            :  5;
     unsigned      vtstop                                    :  1;
     unsigned      parerr                                    :  1;
#endif
} ncp_phy_PGSR1_t;

/*! @struct ncp_phy_PTR0_t
 *  @brief null
 *  @details PHY Timing Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_PTR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param tpllpd </td>
 *     <td width="20%" align="center"> 11 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> PLL Power-Down Time. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpllgs </td>
 *     <td width="20%" align="center"> 15 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> PLL Gear Shift Time. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tphyrst </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PHY Reset Time. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_PTR0_t
 *
 * Implemented by: 
 *      PTR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      tpllpd                                    : 11;
     unsigned      tpllgs                                    : 15;
     unsigned      tphyrst                                   :  6;
#else    /* Little Endian */
     unsigned      tphyrst                                   :  6;
     unsigned      tpllgs                                    : 15;
     unsigned      tpllpd                                    : 11;
#endif
} ncp_phy_PTR0_t;

/*! @struct ncp_phy_PTR1_t
 *  @brief null
 *  @details PHY Timing Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_PTR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param tplllock </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> PLL Lock Time. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_13 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved. Returns zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tpllrst </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PLL Reset Time. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_PTR1_t
 *
 * Implemented by: 
 *      PTR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      tplllock                                  : 16;
     unsigned      reserved_15_13                            :  3;
     unsigned      tpllrst                                   : 13;
#else    /* Little Endian */
     unsigned      tpllrst                                   : 13;
     unsigned      reserved_15_13                            :  3;
     unsigned      tplllock                                  : 16;
#endif
} ncp_phy_PTR1_t;

/*! @struct ncp_phy_PTR2_t
 *  @brief null
 *  @details PHY Timing Register 2
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_PTR2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_20 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param twldlys </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Write Leveling Delay Settling Time. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tcalh </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Calibration Hold Time. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tcals </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Calibration Setup Time. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tcalon </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Calibration On Time. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_PTR2_t
 *
 * Implemented by: 
 *      PTR2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_20                            : 12;
     unsigned      twldlys                                   :  5;
     unsigned      tcalh                                     :  5;
     unsigned      tcals                                     :  5;
     unsigned      tcalon                                    :  5;
#else    /* Little Endian */
     unsigned      tcalon                                    :  5;
     unsigned      tcals                                     :  5;
     unsigned      tcalh                                     :  5;
     unsigned      twldlys                                   :  5;
     unsigned      reserved_31_20                            : 12;
#endif
} ncp_phy_PTR2_t;

/*! @struct ncp_phy_PTR3_t
 *  @brief null
 *  @details PHY Timing Register 3
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_PTR3_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdinit1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> DRAM Initialization Time 1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdinit0 </td>
 *     <td width="20%" align="center"> 20 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM Initialization Time 0. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_PTR3_t
 *
 * Implemented by: 
 *      PTR3
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      tdinit1                                   : 10;
     unsigned      tdinit0                                   : 20;
#else    /* Little Endian */
     unsigned      tdinit0                                   : 20;
     unsigned      tdinit1                                   : 10;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_PTR3_t;

/*! @struct ncp_phy_PTR4_t
 *  @brief null
 *  @details PHY Timing Register 4
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_PTR4_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_29 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdinit3 </td>
 *     <td width="20%" align="center"> 11 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> DRAM Initialization Time 3. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdinit2 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM Initialization Time 2. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_PTR4_t
 *
 * Implemented by: 
 *      PTR4
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_29                            :  3;
     unsigned      tdinit3                                   : 11;
     unsigned      tdinit2                                   : 18;
#else    /* Little Endian */
     unsigned      tdinit2                                   : 18;
     unsigned      tdinit3                                   : 11;
     unsigned      reserved_31_29                            :  3;
#endif
} ncp_phy_PTR4_t;

/*! @struct ncp_phy_PLLCR0_t
 *  @brief null
 *  @details PLL Control Register 0 (Type B PLL Only)
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_PLLCR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param pllbyp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> PLL Bypass. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pllrst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> PLL Rest. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pllpd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> PLL Power Down. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rstopm </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Reference Stop Mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param frqsel </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> PLL Frequency Select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rlockm </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Relock Mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cppc </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Charge Pump Proportional Current Control. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpic </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Charge Pump Integrating Current Control. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gshift </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Gear Shift. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param atoen </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Analog Test Enable (ATOEN). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param atc </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Analog Test Control. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtc </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Digital Test Control. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_PLLCR0_t
 *
 * Implemented by: 
 *      PLLCR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      pllbyp                                    :  1;
     unsigned      pllrst                                    :  1;
     unsigned      pllpd                                     :  1;
     unsigned      rstopm                                    :  1;
     unsigned      frqsel                                    :  4;
     unsigned      rlockm                                    :  1;
     unsigned      cppc                                      :  6;
     unsigned      cpic                                      :  4;
     unsigned      gshift                                    :  1;
     unsigned      atoen                                     :  4;
     unsigned      atc                                       :  4;
     unsigned      dtc                                       :  4;
#else    /* Little Endian */
     unsigned      dtc                                       :  4;
     unsigned      atc                                       :  4;
     unsigned      atoen                                     :  4;
     unsigned      gshift                                    :  1;
     unsigned      cpic                                      :  4;
     unsigned      cppc                                      :  6;
     unsigned      rlockm                                    :  1;
     unsigned      frqsel                                    :  4;
     unsigned      rstopm                                    :  1;
     unsigned      pllpd                                     :  1;
     unsigned      pllrst                                    :  1;
     unsigned      pllbyp                                    :  1;
#endif
} ncp_phy_PLLCR0_t;

/*! @struct ncp_phy_PLLCR1_t
 *  @brief null
 *  @details PLL Control Register 1 (Type B PLL Only)
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_PLLCR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param pllprog </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Connects to the PLL PLL_PROG bus. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bypvregcp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Bypass PLL vreg_cp </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bypvregdig </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Bypass PLL vreg_dig </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bypvdd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> PLL VDD voltage level control </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lockps </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Lock Detector Phase Select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lockcs </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Lock Detector Counter Select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lockds </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lock Detector Select. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_PLLCR1_t
 *
 * Implemented by: 
 *      PLLCR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      pllprog                                   : 16;
     unsigned      reserved_15_6                             : 10;
     unsigned      bypvregcp                                 :  1;
     unsigned      bypvregdig                                :  1;
     unsigned      bypvdd                                    :  1;
     unsigned      lockps                                    :  1;
     unsigned      lockcs                                    :  1;
     unsigned      lockds                                    :  1;
#else    /* Little Endian */
     unsigned      lockds                                    :  1;
     unsigned      lockcs                                    :  1;
     unsigned      lockps                                    :  1;
     unsigned      bypvdd                                    :  1;
     unsigned      bypvregdig                                :  1;
     unsigned      bypvregcp                                 :  1;
     unsigned      reserved_15_6                             : 10;
     unsigned      pllprog                                   : 16;
#endif
} ncp_phy_PLLCR1_t;

/*! @struct ncp_phy_PLLCR2_t
 *  @brief null
 *  @details PLL Control Register 2 (Type B PLL Only)
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_PLLCR2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param pllctrl_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Connects to bits [31:0] of the PLL general control
 *        bus PLL_CTRL.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_PLLCR2_t
 *
 * Implemented by: 
 *      PLLCR2
 */
 
typedef struct
{
     unsigned  int              pllctrl_31_0;
} ncp_phy_PLLCR2_t;

/*! @struct ncp_phy_PLLCR3_t
 *  @brief null
 *  @details PLL Control Register 3 (Type B PLL Only)
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_PLLCR3_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param pllctrl_63_32 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Connects to bits [63:32] of the PLL general control
 *        bus PLL_CTRL.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_PLLCR3_t
 *
 * Implemented by: 
 *      PLLCR3
 */
 
typedef struct
{
     unsigned  int             pllctrl_63_32;
} ncp_phy_PLLCR3_t;

/*! @struct ncp_phy_PLLCR4_t
 *  @brief null
 *  @details PLL Control Register 4 (Type B PLL Only)
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_PLLCR4_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param pllctrl_95_64 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Connects to bits [95:64] of the PLL general control
 *        bus PLL_CTRL.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_PLLCR4_t
 *
 * Implemented by: 
 *      PLLCR4
 */
 
typedef struct
{
     unsigned  int             pllctrl_95_64;
} ncp_phy_PLLCR4_t;

/*! @struct ncp_phy_PLLCR5_t
 *  @brief null
 *  @details PLL Control Register 5 (Type B PLL Only)
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_PLLCR5_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pllctrl_103_96 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Connects to bits [103:96] of the PLL general control
 *        bus PLL_CTRL.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_PLLCR5_t
 *
 * Implemented by: 
 *      PLLCR5
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_8                             : 24;
     unsigned      pllctrl_103_96                            :  8;
#else    /* Little Endian */
     unsigned      pllctrl_103_96                            :  8;
     unsigned      reserved_31_8                             : 24;
#endif
} ncp_phy_PLLCR5_t;

/*! @struct ncp_phy_PLLCR_t
 *  @brief null
 *  @details PLL Control Register (Type A PLL Only)
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_PLLCR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_PLLCR_t
 *
 * Implemented by: 
 *      PLLCR
 */
 
typedef struct
{
     unsigned  int             reserved_31_0;
} ncp_phy_PLLCR_t;

/*! @struct ncp_phy_DXCCR_t
 *  @brief null
 *  @details DATX8 Common Configuration Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DXCCR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rkloop </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Rank looping (per-rank eye centering) enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_28_24 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxdccbyp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> DATX8 Duty Cycle Correction Bypass. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param qscnten </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> QS Counter Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param udqiom </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Unused DQ I/O Mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_20_18 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param msbudq </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Most Significant Byte Unused DQs. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxsr </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Data Slew Rate (D3F I/O Only). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqsnres </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> DQS_N Resistor. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqsres </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> DQS Resistor. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqsglb </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Read DQS Gate I/O Loopback. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mdlen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Master Delay Line Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxiom </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Data I/O Mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxodt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data On-Die Termination. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DXCCR_t
 *
 * Implemented by: 
 *      DXCCR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      rkloop                                    :  1;
     unsigned      reserved_28_24                            :  5;
     unsigned      dxdccbyp                                  :  1;
     unsigned      qscnten                                   :  1;
     unsigned      udqiom                                    :  1;
     unsigned      reserved_20_18                            :  3;
     unsigned      msbudq                                    :  3;
     unsigned      dxsr                                      :  2;
     unsigned      dqsnres                                   :  4;
     unsigned      dqsres                                    :  4;
     unsigned      dqsglb                                    :  2;
     unsigned      mdlen                                     :  1;
     unsigned      dxiom                                     :  1;
     unsigned      dxodt                                     :  1;
#else    /* Little Endian */
     unsigned      dxodt                                     :  1;
     unsigned      dxiom                                     :  1;
     unsigned      mdlen                                     :  1;
     unsigned      dqsglb                                    :  2;
     unsigned      dqsres                                    :  4;
     unsigned      dqsnres                                   :  4;
     unsigned      dxsr                                      :  2;
     unsigned      msbudq                                    :  3;
     unsigned      reserved_20_18                            :  3;
     unsigned      udqiom                                    :  1;
     unsigned      qscnten                                   :  1;
     unsigned      dxdccbyp                                  :  1;
     unsigned      reserved_28_24                            :  5;
     unsigned      rkloop                                    :  1;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_DXCCR_t;

/*! @struct ncp_phy_DSGCR_t
 *  @brief null
 *  @details DDR System General Configuration Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DSGCR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_24 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param phyzuen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> PHY Impedance Update Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rrrmode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Read Path Rise-to-Rise Mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rstoe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> SDRAM Reset Output Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sdrmode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Single Data Rate Mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrrmode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Write Path Rise-to-Rise Mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param atoae </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> ATO Analog Test Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtooe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DTO Output Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtoiom </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> DTO I/O Mode, </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtopdr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> DTO Power Down Receiver. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtopdd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> DTO Power Down Driver. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtoodt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> DTO On-Die Termination. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param puad </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> PHY Update Acknowledge Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqsgx </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> DQS Gate Extension. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cuaen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Controller Update Acknowledge Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lppllpd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Low Power PLL Power Down. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpiopd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Low Power I/O Power Down. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ctlzuen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Controller Impedance Update Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bdisen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Byte Disable Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param puren </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PHY Update Request Enable. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DSGCR_t
 *
 * Implemented by: 
 *      DSGCR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_24                            :  8;
     unsigned      phyzuen                                   :  1;
     unsigned      rrrmode                                   :  1;
     unsigned      rstoe                                     :  1;
     unsigned      sdrmode                                   :  2;
     unsigned      wrrmode                                   :  1;
     unsigned      atoae                                     :  1;
     unsigned      dtooe                                     :  1;
     unsigned      dtoiom                                    :  1;
     unsigned      dtopdr                                    :  1;
     unsigned      dtopdd                                    :  1;
     unsigned      dtoodt                                    :  1;
     unsigned      puad                                      :  4;
     unsigned      dqsgx                                     :  2;
     unsigned      cuaen                                     :  1;
     unsigned      lppllpd                                   :  1;
     unsigned      lpiopd                                    :  1;
     unsigned      ctlzuen                                   :  1;
     unsigned      bdisen                                    :  1;
     unsigned      puren                                     :  1;
#else    /* Little Endian */
     unsigned      puren                                     :  1;
     unsigned      bdisen                                    :  1;
     unsigned      ctlzuen                                   :  1;
     unsigned      lpiopd                                    :  1;
     unsigned      lppllpd                                   :  1;
     unsigned      cuaen                                     :  1;
     unsigned      dqsgx                                     :  2;
     unsigned      puad                                      :  4;
     unsigned      dtoodt                                    :  1;
     unsigned      dtopdd                                    :  1;
     unsigned      dtopdr                                    :  1;
     unsigned      dtoiom                                    :  1;
     unsigned      dtooe                                     :  1;
     unsigned      atoae                                     :  1;
     unsigned      wrrmode                                   :  1;
     unsigned      sdrmode                                   :  2;
     unsigned      rstoe                                     :  1;
     unsigned      rrrmode                                   :  1;
     unsigned      phyzuen                                   :  1;
     unsigned      reserved_31_24                            :  8;
#endif
} ncp_phy_DSGCR_t;

/*! @struct ncp_phy_ODTCR_t
 *  @brief null
 *  @details ODT Configuration Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ODTCR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_28 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrodt_rsvd </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrodt </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Write ODT. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_12 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdodt_rsvd </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdodt </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Read ODT. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ODTCR_t
 *
 * Implemented by: 
 *      ODTCR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_28                            :  4;
     unsigned      wrodt_rsvd                                : 10;
     unsigned      wrodt                                     :  2;
     unsigned      reserved_15_12                            :  4;
     unsigned      rdodt_rsvd                                : 10;
     unsigned      rdodt                                     :  2;
#else    /* Little Endian */
     unsigned      rdodt                                     :  2;
     unsigned      rdodt_rsvd                                : 10;
     unsigned      reserved_15_12                            :  4;
     unsigned      wrodt                                     :  2;
     unsigned      wrodt_rsvd                                : 10;
     unsigned      reserved_31_28                            :  4;
#endif
} ncp_phy_ODTCR_t;

/*! @struct ncp_phy_AACR_t
 *  @brief null
 *  @details Anti-Aging Control Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_AACR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param aaoenc </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Anti-Aging PAD Output Enable Control. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param aaenc </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Anti-Aging Enable Control. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param aatr </td>
 *     <td width="20%" align="center"> 30 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Anti-Aging Toggle Rate. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_AACR_t
 *
 * Implemented by: 
 *      AACR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      aaoenc                                    :  1;
     unsigned      aaenc                                     :  1;
     unsigned      aatr                                      : 30;
#else    /* Little Endian */
     unsigned      aatr                                      : 30;
     unsigned      aaenc                                     :  1;
     unsigned      aaoenc                                    :  1;
#endif
} ncp_phy_AACR_t;

/*! @struct ncp_phy_GPR0_t
 *  @brief null
 *  @details General Purpose Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_GPR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param gpr0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> General Purpose Register 0. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_GPR0_t
 *
 * Implemented by: 
 *      GPR0
 */
 
typedef struct
{
     unsigned  int                      gpr0;
} ncp_phy_GPR0_t;

/*! @struct ncp_phy_GPR1_t
 *  @brief null
 *  @details General Purpose Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_GPR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param gpr1 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> General Purpose Register 1. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_GPR1_t
 *
 * Implemented by: 
 *      GPR1
 */
 
typedef struct
{
     unsigned  int                      gpr1;
} ncp_phy_GPR1_t;

/*! @struct ncp_phy_DCR_t
 *  @brief null
 *  @details DRAM Configuration Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DCR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ubg </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Un-used Bank Group. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param udimm </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Un-buffered DIMM Address Mirroring. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ddr2t </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> DDR 2T Timing. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param nosra </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> No Simultaneous Rank Access. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_26_18 </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bytemask </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Byte Mask. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ddrtype </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DDR Type. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mprdq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Multi-Purpose Register (MPR) DQ (DDR3 Only). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pdq </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Primary DQ (DDR3 Only). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ddr8bnk </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> DDR 8-Bank. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ddrmd </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DDR Mode. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DCR_t
 *
 * Implemented by: 
 *      DCR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31                               :  1;
     unsigned      ubg                                       :  1;
     unsigned      udimm                                     :  1;
     unsigned      ddr2t                                     :  1;
     unsigned      nosra                                     :  1;
     unsigned      reserved_26_18                            :  9;
     unsigned      bytemask                                  :  8;
     unsigned      ddrtype                                   :  2;
     unsigned      mprdq                                     :  1;
     unsigned      pdq                                       :  3;
     unsigned      ddr8bnk                                   :  1;
     unsigned      ddrmd                                     :  3;
#else    /* Little Endian */
     unsigned      ddrmd                                     :  3;
     unsigned      ddr8bnk                                   :  1;
     unsigned      pdq                                       :  3;
     unsigned      mprdq                                     :  1;
     unsigned      ddrtype                                   :  2;
     unsigned      bytemask                                  :  8;
     unsigned      reserved_26_18                            :  9;
     unsigned      nosra                                     :  1;
     unsigned      ddr2t                                     :  1;
     unsigned      udimm                                     :  1;
     unsigned      ubg                                       :  1;
     unsigned      reserved_31                               :  1;
#endif
} ncp_phy_DCR_t;

/*! @struct ncp_phy_DTPR0_t
 *  @brief null
 *  @details DRAM Timing Parameters Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DTPR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_28 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trrd </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Activate to activate command delay (different banks). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tras </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Activate to precharge command delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trp </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Precharge command period. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trtp </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Internal read to precharge command delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DTPR0_t
 *
 * Implemented by: 
 *      DTPR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_28                            :  4;
     unsigned      trrd                                      :  4;
     unsigned      reserved_23                               :  1;
     unsigned      tras                                      :  7;
     unsigned      reserved_15                               :  1;
     unsigned      trp                                       :  7;
     unsigned      reserved_7_4                              :  4;
     unsigned      trtp                                      :  4;
#else    /* Little Endian */
     unsigned      trtp                                      :  4;
     unsigned      reserved_7_4                              :  4;
     unsigned      trp                                       :  7;
     unsigned      reserved_15                               :  1;
     unsigned      tras                                      :  7;
     unsigned      reserved_23                               :  1;
     unsigned      trrd                                      :  4;
     unsigned      reserved_31_28                            :  4;
#endif
} ncp_phy_DTPR0_t;

/*! @struct ncp_phy_DTPR1_t
 *  @brief null
 *  @details DRAM Timing Parameters Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DTPR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param twlmrd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Minimum delay from when write leveling mode is programmed
 *        to the first DQS/DQS_N rising edge.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_22 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tfaw </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> 4-bank activate period. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_11 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tmod </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Load mode update delay (DDR4 and DDR3 only). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tmrd </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Load mode cycle time. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DTPR1_t
 *
 * Implemented by: 
 *      DTPR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      twlmrd                                    :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      tfaw                                      :  6;
     unsigned      reserved_15_11                            :  5;
     unsigned      tmod                                      :  3;
     unsigned      reserved_7_2                              :  6;
     unsigned      tmrd                                      :  2;
#else    /* Little Endian */
     unsigned      tmrd                                      :  2;
     unsigned      reserved_7_2                              :  6;
     unsigned      tmod                                      :  3;
     unsigned      reserved_15_11                            :  5;
     unsigned      tfaw                                      :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      twlmrd                                    :  6;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_DTPR1_t;

/*! @struct ncp_phy_DTPR2_t
 *  @brief null
 *  @details DRAM Timing Parameters Register 2
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DTPR2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_29 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trtw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Read to Write command delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_27_25 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trtodt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Read to ODT delay (DDR3 only). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_20 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tcke </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> CKE minimum pulse width. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_10 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param txs </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Self refresh exit delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DTPR2_t
 *
 * Implemented by: 
 *      DTPR2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_29                            :  3;
     unsigned      trtw                                      :  1;
     unsigned      reserved_27_25                            :  3;
     unsigned      trtodt                                    :  1;
     unsigned      reserved_23_20                            :  4;
     unsigned      tcke                                      :  4;
     unsigned      reserved_15_10                            :  6;
     unsigned      txs                                       : 10;
#else    /* Little Endian */
     unsigned      txs                                       : 10;
     unsigned      reserved_15_10                            :  6;
     unsigned      tcke                                      :  4;
     unsigned      reserved_23_20                            :  4;
     unsigned      trtodt                                    :  1;
     unsigned      reserved_27_25                            :  3;
     unsigned      trtw                                      :  1;
     unsigned      reserved_31_29                            :  3;
#endif
} ncp_phy_DTPR2_t;

/*! @struct ncp_phy_DTPR3_t
 *  @brief null
 *  @details DRAM Timing Parameters Register 3
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DTPR3_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param tofdx </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> ODT turn-off delay extension. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tccd </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Read to read and write to write command delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdllk </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DLL locking time. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_11 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdqsckmax </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Maximum DQS output access time from CK/CK_N (LPDDR2/3
 *        only).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdqsck </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DQS output access time from CK/CK_N (LPDDR2/3 only). </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DTPR3_t
 *
 * Implemented by: 
 *      DTPR3
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      tofdx                                     :  3;
     unsigned      tccd                                      :  3;
     unsigned      tdllk                                     : 10;
     unsigned      reserved_15_11                            :  5;
     unsigned      tdqsckmax                                 :  3;
     unsigned      reserved_7_3                              :  5;
     unsigned      tdqsck                                    :  3;
#else    /* Little Endian */
     unsigned      tdqsck                                    :  3;
     unsigned      reserved_7_3                              :  5;
     unsigned      tdqsckmax                                 :  3;
     unsigned      reserved_15_11                            :  5;
     unsigned      tdllk                                     : 10;
     unsigned      tccd                                      :  3;
     unsigned      tofdx                                     :  3;
#endif
} ncp_phy_DTPR3_t;

/*! @struct ncp_phy_DTPR4_t
 *  @brief null
 *  @details DRAM Timing Parameters Register 4
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DTPR4_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param taond_taofd </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> ODT turn-on/turn-off delays (DDR2 only). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_27_26 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trfc </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Refresh-to-Refresh. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_12 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param twlo </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Write leveling output delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_5 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param txp </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Power down exit delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DTPR4_t
 *
 * Implemented by: 
 *      DTPR4
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      taond_taofd                               :  2;
     unsigned      reserved_27_26                            :  2;
     unsigned      trfc                                      : 10;
     unsigned      reserved_15_12                            :  4;
     unsigned      twlo                                      :  4;
     unsigned      reserved_7_5                              :  3;
     unsigned      txp                                       :  5;
#else    /* Little Endian */
     unsigned      txp                                       :  5;
     unsigned      reserved_7_5                              :  3;
     unsigned      twlo                                      :  4;
     unsigned      reserved_15_12                            :  4;
     unsigned      trfc                                      : 10;
     unsigned      reserved_27_26                            :  2;
     unsigned      taond_taofd                               :  2;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_DTPR4_t;

/*! @struct ncp_phy_DTPR5_t
 *  @brief null
 *  @details DRAM Timing Parameters Register 5
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DTPR5_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_24 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trc </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Activate to activate command delay (same bank). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trcd </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Activate to read or write delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_5 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param twtr </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Internal write to read command delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DTPR5_t
 *
 * Implemented by: 
 *      DTPR5
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_24                            :  8;
     unsigned      trc                                       :  8;
     unsigned      reserved_15                               :  1;
     unsigned      trcd                                      :  7;
     unsigned      reserved_7_5                              :  3;
     unsigned      twtr                                      :  5;
#else    /* Little Endian */
     unsigned      twtr                                      :  5;
     unsigned      reserved_7_5                              :  3;
     unsigned      trcd                                      :  7;
     unsigned      reserved_15                               :  1;
     unsigned      trc                                       :  8;
     unsigned      reserved_31_24                            :  8;
#endif
} ncp_phy_DTPR5_t;

/*! @struct ncp_phy_DTPR6_t
 *  @brief null
 *  @details DRAM Timing Parameters Register 6
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DTPR6_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param pubwlen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> PUB Write Latency Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pubrlen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> PUB Read Latency Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_29_14 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pubwl </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Write Latency. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pubrl </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Read Latency. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DTPR6_t
 *
 * Implemented by: 
 *      DTPR6
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      pubwlen                                   :  1;
     unsigned      pubrlen                                   :  1;
     unsigned      reserved_29_14                            : 16;
     unsigned      pubwl                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      pubrl                                     :  6;
#else    /* Little Endian */
     unsigned      pubrl                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      pubwl                                     :  6;
     unsigned      reserved_29_14                            : 16;
     unsigned      pubrlen                                   :  1;
     unsigned      pubwlen                                   :  1;
#endif
} ncp_phy_DTPR6_t;

/*! @struct ncp_phy_RDIMMGCR0_t
 *  @brief null
 *  @details RDIMM General Configuration Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_RDIMMGCR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param mirror </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> RDIMM Mirror. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param qcsen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> RDMIMM Quad CS Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mirroroe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> MIRROR Output Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param qcsenoe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> QCSEN_N Output Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdimmiom </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> RDIMM Outputs I/O Mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdimmpdr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> RDIMM Outputs Power Down Receiver. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdimmpdd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> RDIMM Outputs Power Down Driver. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdimmodt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> RDIMM Outputs On-Die Termination. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param erroutoe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> ERROUT_N Output Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param erroutiom </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> ERROUT_N I/O Mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param erroutpdr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> ERROUT_N Power Down Receiver. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param erroutpdd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> ERROUT_N Power Down Driver. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param erroutodt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> ERROUT_N On-Die Termination. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_18 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pariniom </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> PAR_IN I/O Mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param parinpdr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> PAR_IN Power Down Receiver. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param parinodt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> PAR_IN On-Die Termination. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_13_3 </td>
 *     <td width="20%" align="center"> 11 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param soperr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Stop on Parity Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param errnoreg </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Parity Error No Registering. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdimm </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Registered DIMM. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_RDIMMGCR0_t
 *
 * Implemented by: 
 *      RDIMMGCR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      mirror                                    :  1;
     unsigned      qcsen                                     :  1;
     unsigned      mirroroe                                  :  1;
     unsigned      qcsenoe                                   :  1;
     unsigned      rdimmiom                                  :  1;
     unsigned      rdimmpdr                                  :  1;
     unsigned      rdimmpdd                                  :  1;
     unsigned      rdimmodt                                  :  1;
     unsigned      erroutoe                                  :  1;
     unsigned      erroutiom                                 :  1;
     unsigned      erroutpdr                                 :  1;
     unsigned      erroutpdd                                 :  1;
     unsigned      erroutodt                                 :  1;
     unsigned      reserved_18                               :  1;
     unsigned      pariniom                                  :  1;
     unsigned      parinpdr                                  :  1;
     unsigned      reserved_15                               :  1;
     unsigned      parinodt                                  :  1;
     unsigned      reserved_13_3                             : 11;
     unsigned      soperr                                    :  1;
     unsigned      errnoreg                                  :  1;
     unsigned      rdimm                                     :  1;
#else    /* Little Endian */
     unsigned      rdimm                                     :  1;
     unsigned      errnoreg                                  :  1;
     unsigned      soperr                                    :  1;
     unsigned      reserved_13_3                             : 11;
     unsigned      parinodt                                  :  1;
     unsigned      reserved_15                               :  1;
     unsigned      parinpdr                                  :  1;
     unsigned      pariniom                                  :  1;
     unsigned      reserved_18                               :  1;
     unsigned      erroutodt                                 :  1;
     unsigned      erroutpdd                                 :  1;
     unsigned      erroutpdr                                 :  1;
     unsigned      erroutiom                                 :  1;
     unsigned      erroutoe                                  :  1;
     unsigned      rdimmodt                                  :  1;
     unsigned      rdimmpdd                                  :  1;
     unsigned      rdimmpdr                                  :  1;
     unsigned      rdimmiom                                  :  1;
     unsigned      qcsenoe                                   :  1;
     unsigned      mirroroe                                  :  1;
     unsigned      qcsen                                     :  1;
     unsigned      mirror                                    :  1;
#endif
} ncp_phy_RDIMMGCR0_t;

/*! @struct ncp_phy_RDIMMGCR1_t
 *  @brief null
 *  @details RDIMM General Configuration Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_RDIMMGCR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_29 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param a17bid </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Address [17] B-side Inversion Disable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_27 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tbcmrd_l2 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Command word to command word programming delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tbcmrd_l </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Command word to command word programming delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_19 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tbcmrd </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Command word to command word programming delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tbcstab </td>
 *     <td width="20%" align="center"> 14 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Stabilization time. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_RDIMMGCR1_t
 *
 * Implemented by: 
 *      RDIMMGCR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_29                            :  3;
     unsigned      a17bid                                    :  1;
     unsigned      reserved_27                               :  1;
     unsigned      tbcmrd_l2                                 :  3;
     unsigned      reserved_23                               :  1;
     unsigned      tbcmrd_l                                  :  3;
     unsigned      reserved_19                               :  1;
     unsigned      tbcmrd                                    :  3;
     unsigned      reserved_15_14                            :  2;
     unsigned      tbcstab                                   : 14;
#else    /* Little Endian */
     unsigned      tbcstab                                   : 14;
     unsigned      reserved_15_14                            :  2;
     unsigned      tbcmrd                                    :  3;
     unsigned      reserved_19                               :  1;
     unsigned      tbcmrd_l                                  :  3;
     unsigned      reserved_23                               :  1;
     unsigned      tbcmrd_l2                                 :  3;
     unsigned      reserved_27                               :  1;
     unsigned      a17bid                                    :  1;
     unsigned      reserved_31_29                            :  3;
#endif
} ncp_phy_RDIMMGCR1_t;

/*! @struct ncp_phy_RDIMMGCR2_t
 *  @brief null
 *  @details RDIMM General Configuration Register 2
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_RDIMMGCR2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param crinit </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Control Registers Initialization Enable. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_RDIMMGCR2_t
 *
 * Implemented by: 
 *      RDIMMGCR2
 */
 
typedef struct
{
     unsigned  int                    crinit;
} ncp_phy_RDIMMGCR2_t;

/*! @struct ncp_phy_RDIMMCR0_t
 *  @brief null
 *  @details RDIMM Control Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_RDIMMCR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rc7 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Control Word 7. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rc6 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Control Word 6 (Comman space Control Word). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rc5 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Control Word 5 (CK Driver Characteristics Control
 *        Word).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rc4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Control Word 4 (ODT and CKE Signals Driver Characteristics
 *        Control Word).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rc3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Control Word 3 (CA and CS Signals Driver Characteristics
 *        Control Word).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rc2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Control Word 2 (Timing and IBT Control Word). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rc1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Control Word 1 (Clock Driver Enable Control Word). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rc0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Control Word 0 (Global Features Control Word). </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_RDIMMCR0_t
 *
 * Implemented by: 
 *      RDIMMCR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rc7                                       :  4;
     unsigned      rc6                                       :  4;
     unsigned      rc5                                       :  4;
     unsigned      rc4                                       :  4;
     unsigned      rc3                                       :  4;
     unsigned      rc2                                       :  4;
     unsigned      rc1                                       :  4;
     unsigned      rc0                                       :  4;
#else    /* Little Endian */
     unsigned      rc0                                       :  4;
     unsigned      rc1                                       :  4;
     unsigned      rc2                                       :  4;
     unsigned      rc3                                       :  4;
     unsigned      rc4                                       :  4;
     unsigned      rc5                                       :  4;
     unsigned      rc6                                       :  4;
     unsigned      rc7                                       :  4;
#endif
} ncp_phy_RDIMMCR0_t;

/*! @struct ncp_phy_RDIMMCR1_t
 *  @brief null
 *  @details RDIMM Control Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_RDIMMCR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rc15 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Control Word 15. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rc14 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Control Word 14 (Parity Control Word). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rc13 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Control Word 13 (DIMM Configuration Control Word). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rc12 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Control Word 12 (Training Control Word). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rc11 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Control Word 11 (Operating Voltage VDD and VREFCA
 *        Source Control Word).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rc10 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Control Word 10 (RDIMM Operating Speed Control Word). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rc9 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Control Word 9 (Power Saving Settings Control Word). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rc8 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Control Word 8 (Input/Output Configuration Control
 *        Word).
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_RDIMMCR1_t
 *
 * Implemented by: 
 *      RDIMMCR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rc15                                      :  4;
     unsigned      rc14                                      :  4;
     unsigned      rc13                                      :  4;
     unsigned      rc12                                      :  4;
     unsigned      rc11                                      :  4;
     unsigned      rc10                                      :  4;
     unsigned      rc9                                       :  4;
     unsigned      rc8                                       :  4;
#else    /* Little Endian */
     unsigned      rc8                                       :  4;
     unsigned      rc9                                       :  4;
     unsigned      rc10                                      :  4;
     unsigned      rc11                                      :  4;
     unsigned      rc12                                      :  4;
     unsigned      rc13                                      :  4;
     unsigned      rc14                                      :  4;
     unsigned      rc15                                      :  4;
#endif
} ncp_phy_RDIMMCR1_t;

/*! @struct ncp_phy_RDIMMCR2_t
 *  @brief null
 *  @details RDIMM Control Register 2
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_RDIMMCR2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rc4x </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Control Word RC4x </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rc3x </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Control Word RC3x </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rc2x </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Control Word RC2x </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rc1x </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Control Word RC1x </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_RDIMMCR2_t
 *
 * Implemented by: 
 *      RDIMMCR2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rc4x                                      :  8;
     unsigned      rc3x                                      :  8;
     unsigned      rc2x                                      :  8;
     unsigned      rc1x                                      :  8;
#else    /* Little Endian */
     unsigned      rc1x                                      :  8;
     unsigned      rc2x                                      :  8;
     unsigned      rc3x                                      :  8;
     unsigned      rc4x                                      :  8;
#endif
} ncp_phy_RDIMMCR2_t;

/*! @struct ncp_phy_RDIMMCR3_t
 *  @brief null
 *  @details RDIMM Control Register 3
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_RDIMMCR3_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rc8x </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Control Word RC8x </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rc7x </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Control Word RC7x </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rc6x </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Control Word RC6x </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rc5x </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Control Word RC5x </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_RDIMMCR3_t
 *
 * Implemented by: 
 *      RDIMMCR3
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rc8x                                      :  8;
     unsigned      rc7x                                      :  8;
     unsigned      rc6x                                      :  8;
     unsigned      rc5x                                      :  8;
#else    /* Little Endian */
     unsigned      rc5x                                      :  8;
     unsigned      rc6x                                      :  8;
     unsigned      rc7x                                      :  8;
     unsigned      rc8x                                      :  8;
#endif
} ncp_phy_RDIMMCR3_t;

/*! @struct ncp_phy_RDIMMCR4_t
 *  @brief null
 *  @details RDIMM Control Register 4
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_RDIMMCR4_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rcxx </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved for future use. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rcbx </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Control Word RCBx </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rcax </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Control Word RCAx </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rc9x </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Control Word RC5x </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_RDIMMCR4_t
 *
 * Implemented by: 
 *      RDIMMCR4
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rcxx                                      :  8;
     unsigned      rcbx                                      :  8;
     unsigned      rcax                                      :  8;
     unsigned      rc9x                                      :  8;
#else    /* Little Endian */
     unsigned      rc9x                                      :  8;
     unsigned      rcax                                      :  8;
     unsigned      rcbx                                      :  8;
     unsigned      rcxx                                      :  8;
#endif
} ncp_phy_RDIMMCR4_t;

/*! @struct ncp_phy_SCHCR0_t
 *  @brief null
 *  @details Scheduler Command Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_SCHCR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_25 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param schdqv </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Scheduler Command DQ Value. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_12 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sp_cmd </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Special Command codes. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmd </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Specifies the Command to be issued. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param schtrig </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Mode Register Command Trigger. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_SCHCR0_t
 *
 * Implemented by: 
 *      SCHCR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_25                            :  7;
     unsigned      schdqv                                    :  9;
     unsigned      reserved_15_12                            :  4;
     unsigned      sp_cmd                                    :  4;
     unsigned      cmd                                       :  4;
     unsigned      schtrig                                   :  4;
#else    /* Little Endian */
     unsigned      schtrig                                   :  4;
     unsigned      cmd                                       :  4;
     unsigned      sp_cmd                                    :  4;
     unsigned      reserved_15_12                            :  4;
     unsigned      schdqv                                    :  9;
     unsigned      reserved_31_25                            :  7;
#endif
} ncp_phy_SCHCR0_t;

/*! @struct ncp_phy_SCHCR1_t
 *  @brief null
 *  @details Scheduler Command Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_SCHCR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param scrnk </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Scheduler Rank Address. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param scaddr </td>
 *     <td width="20%" align="center"> 20 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Scheduler Command Address. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param scbg </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Scheduler Command Bank Group. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param scbk </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Scheduler Command Bank Address. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param allrank </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> All Ranks enabled. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_1_0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_SCHCR1_t
 *
 * Implemented by: 
 *      SCHCR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      scrnk                                     :  4;
     unsigned      scaddr                                    : 20;
     unsigned      scbg                                      :  2;
     unsigned      scbk                                      :  2;
     unsigned      reserved_3                                :  1;
     unsigned      allrank                                   :  1;
     unsigned      reserved_1_0                              :  2;
#else    /* Little Endian */
     unsigned      reserved_1_0                              :  2;
     unsigned      allrank                                   :  1;
     unsigned      reserved_3                                :  1;
     unsigned      scbk                                      :  2;
     unsigned      scbg                                      :  2;
     unsigned      scaddr                                    : 20;
     unsigned      scrnk                                     :  4;
#endif
} ncp_phy_SCHCR1_t;

/*! @struct ncp_phy_MR0_t
 *  @brief null
 *  @details DDR3 Mode Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_MR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved. These are JEDEC reserved bits and are recommended
 *        by JEDEC to be programmed to 0x0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Power-Down Control. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wr </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Write Recovery and Read to Precharge. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DLL Reset. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tm </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Operating Mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cl_6_4 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CAS Latency. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Burst Type. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cl_2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CAS Latency. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bl </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Burst Length. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_MR0_t
 *
 * Implemented by: 
 *      MR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_16                            : 16;
     unsigned      rsvd                                      :  3;
     unsigned      pd                                        :  1;
     unsigned      wr                                        :  3;
     unsigned      dr                                        :  1;
     unsigned      tm                                        :  1;
     unsigned      cl_6_4                                    :  3;
     unsigned      bt                                        :  1;
     unsigned      cl_2                                      :  1;
     unsigned      bl                                        :  2;
#else    /* Little Endian */
     unsigned      bl                                        :  2;
     unsigned      cl_2                                      :  1;
     unsigned      bt                                        :  1;
     unsigned      cl_6_4                                    :  3;
     unsigned      tm                                        :  1;
     unsigned      dr                                        :  1;
     unsigned      wr                                        :  3;
     unsigned      pd                                        :  1;
     unsigned      rsvd                                      :  3;
     unsigned      reserved_31_16                            : 16;
#endif
} ncp_phy_MR0_t;

/*! @struct ncp_phy_MR1_t
 *  @brief null
 *  @details DDR3 Mode Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_MR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd_15_13 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved. These are JEDEC reserved bits and are recommended
 *        by JEDEC to be programmed to 0x0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param qoff </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Output Enable/Disable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdqs </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Termination Data Strobe. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd_10 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved. This is a JEDEC reserved bit for DDR3 and
 *        is recommended by JEDEC to be programmed to 0x0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rtt_9 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> On Die Termination. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd_8 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved. This is a JEDEC reserved bit for DDR3 and
 *        is recommended by JEDEC to be programmed to 0x0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param level </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Write Leveling Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rtt_6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> On Die Termination. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dic_5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Output Driver Impedance Control. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param al </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Posted CAS Additive Latency. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rtt_2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> On Die Termination. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dic_1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Output Driver Impedance Control. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param de </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DLL Enable/Disable. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_MR1_t
 *
 * Implemented by: 
 *      MR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_16                            : 16;
     unsigned      rsvd_15_13                                :  3;
     unsigned      qoff                                      :  1;
     unsigned      tdqs                                      :  1;
     unsigned      rsvd_10                                   :  1;
     unsigned      rtt_9                                     :  1;
     unsigned      rsvd_8                                    :  1;
     unsigned      level                                     :  1;
     unsigned      rtt_6                                     :  1;
     unsigned      dic_5                                     :  1;
     unsigned      al                                        :  2;
     unsigned      rtt_2                                     :  1;
     unsigned      dic_1                                     :  1;
     unsigned      de                                        :  1;
#else    /* Little Endian */
     unsigned      de                                        :  1;
     unsigned      dic_1                                     :  1;
     unsigned      rtt_2                                     :  1;
     unsigned      al                                        :  2;
     unsigned      dic_5                                     :  1;
     unsigned      rtt_6                                     :  1;
     unsigned      level                                     :  1;
     unsigned      rsvd_8                                    :  1;
     unsigned      rtt_9                                     :  1;
     unsigned      rsvd_10                                   :  1;
     unsigned      tdqs                                      :  1;
     unsigned      qoff                                      :  1;
     unsigned      rsvd_15_13                                :  3;
     unsigned      reserved_31_16                            : 16;
#endif
} ncp_phy_MR1_t;

/*! @struct ncp_phy_MR2_t
 *  @brief null
 *  @details DDR3 Mode Register 2
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_MR2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd_15_11 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> These are JEDEC reserved bits and are recommended
 *        by JEDEC to be programmed to 0x0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rttwr </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Dynamic ODT. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd_8 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved. This bit is JEDEC reserved and is recommended
 *        by JEDEC to be programmed to 0x0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param srt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Self-Refresh Temperature Range. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param asr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Auto Self-Refresh. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cwl </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CAS Write Latency. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pasr </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Partial Array Self Refresh. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_MR2_t
 *
 * Implemented by: 
 *      MR2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_16                            : 16;
     unsigned      rsvd_15_11                                :  5;
     unsigned      rttwr                                     :  2;
     unsigned      rsvd_8                                    :  1;
     unsigned      srt                                       :  1;
     unsigned      asr                                       :  1;
     unsigned      cwl                                       :  3;
     unsigned      pasr                                      :  3;
#else    /* Little Endian */
     unsigned      pasr                                      :  3;
     unsigned      cwl                                       :  3;
     unsigned      asr                                       :  1;
     unsigned      srt                                       :  1;
     unsigned      rsvd_8                                    :  1;
     unsigned      rttwr                                     :  2;
     unsigned      rsvd_15_11                                :  5;
     unsigned      reserved_31_16                            : 16;
#endif
} ncp_phy_MR2_t;

/*! @struct ncp_phy_MR3_t
 *  @brief null
 *  @details DDR3 Mode Register 3
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_MR3_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> These are JEDEC reserved bits and are recommended
 *        by JEDEC to be programmed to 0x0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mpr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Multi-Purpose Register Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mprloc </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Multi-Purpose Register (MPR) Location. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_MR3_t
 *
 * Implemented by: 
 *      MR3
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_16                            : 16;
     unsigned      rsvd                                      : 13;
     unsigned      mpr                                       :  1;
     unsigned      mprloc                                    :  2;
#else    /* Little Endian */
     unsigned      mprloc                                    :  2;
     unsigned      mpr                                       :  1;
     unsigned      rsvd                                      : 13;
     unsigned      reserved_31_16                            : 16;
#endif
} ncp_phy_MR3_t;

/*! @struct ncp_phy_MR4_t
 *  @brief null
 *  @details DDR4 Mode Register 4
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_MR4_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd_15_13 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> These are JEDEC reserved bits and are recommended
 *        by JEDEC to be programmed to 0x0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Write Preamble. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Read Preamble. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rptm </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Read Preamble Training Mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sra </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Self Refresh Abort. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cs2cmdl </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> CS to Command Latency Mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> These are JEDEC reserved bits and are recommended
 *        by JEDEC to be programmed to 0x0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ivm </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Internakl Vref Monitor. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tcrm </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Temperature Controlled Refresh Mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tcrr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Temperature Controlled Refresh Range. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mpdm </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Maximum Power Down Mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd_0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> These are JEDEC reserved bits and are recommended
 *        by JEDEC to be programmed to 0x0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_MR4_t
 *
 * Implemented by: 
 *      MR4
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_16                            : 16;
     unsigned      rsvd_15_13                                :  3;
     unsigned      wrp                                       :  1;
     unsigned      rdp                                       :  1;
     unsigned      rptm                                      :  1;
     unsigned      sra                                       :  1;
     unsigned      cs2cmdl                                   :  3;
     unsigned      rsvd                                      :  1;
     unsigned      ivm                                       :  1;
     unsigned      tcrm                                      :  1;
     unsigned      tcrr                                      :  1;
     unsigned      mpdm                                      :  1;
     unsigned      rsvd_0                                    :  1;
#else    /* Little Endian */
     unsigned      rsvd_0                                    :  1;
     unsigned      mpdm                                      :  1;
     unsigned      tcrr                                      :  1;
     unsigned      tcrm                                      :  1;
     unsigned      ivm                                       :  1;
     unsigned      rsvd                                      :  1;
     unsigned      cs2cmdl                                   :  3;
     unsigned      sra                                       :  1;
     unsigned      rptm                                      :  1;
     unsigned      rdp                                       :  1;
     unsigned      wrp                                       :  1;
     unsigned      rsvd_15_13                                :  3;
     unsigned      reserved_31_16                            : 16;
#endif
} ncp_phy_MR4_t;

/*! @struct ncp_phy_MR5_t
 *  @brief null
 *  @details DDR4 Mode Register 5
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_MR5_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> These are JEDEC reserved bits and are recommended
 *        by JEDEC to be programmed to 0x0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdbi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Read DBI. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wdbi </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Write DBI. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dm </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Data Mask. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cappe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> CA parity Persistent Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rttpark </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> RTT_PARK. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odtibpd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> ODT Input Buffer during Power Down mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param capes </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> C/A Parity Error Status. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param crcec </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CRC Error Clear. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param capm </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> C/A Parity Latency Mode. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_MR5_t
 *
 * Implemented by: 
 *      MR5
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_16                            : 16;
     unsigned      rsvd                                      :  3;
     unsigned      rdbi                                      :  1;
     unsigned      wdbi                                      :  1;
     unsigned      dm                                        :  1;
     unsigned      cappe                                     :  1;
     unsigned      rttpark                                   :  3;
     unsigned      odtibpd                                   :  1;
     unsigned      capes                                     :  1;
     unsigned      crcec                                     :  1;
     unsigned      capm                                      :  3;
#else    /* Little Endian */
     unsigned      capm                                      :  3;
     unsigned      crcec                                     :  1;
     unsigned      capes                                     :  1;
     unsigned      odtibpd                                   :  1;
     unsigned      rttpark                                   :  3;
     unsigned      cappe                                     :  1;
     unsigned      dm                                        :  1;
     unsigned      wdbi                                      :  1;
     unsigned      rdbi                                      :  1;
     unsigned      rsvd                                      :  3;
     unsigned      reserved_31_16                            : 16;
#endif
} ncp_phy_MR5_t;

/*! @struct ncp_phy_MR6_t
 *  @brief null
 *  @details DDR4 Mode Register 6
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_MR6_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd_15_13 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> These are JEDEC reserved bits and are recommended
 *        by JEDEC to be programmed to 0x0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tccdl </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> CAS_n to CAS_n command delay for same bank group (tCCD_L). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd_9_8 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> These are JEDEC reserved bits and are recommended
 *        by JEDEC to be programmed to 0x0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vddqten </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> VrefDQ Training Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vdqtrg </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> VrefDQ Training Range. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vdqtval </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> VrefDQ Training Values. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_MR6_t
 *
 * Implemented by: 
 *      MR6
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_16                            : 16;
     unsigned      rsvd_15_13                                :  3;
     unsigned      tccdl                                     :  3;
     unsigned      rsvd_9_8                                  :  2;
     unsigned      vddqten                                   :  1;
     unsigned      vdqtrg                                    :  1;
     unsigned      vdqtval                                   :  6;
#else    /* Little Endian */
     unsigned      vdqtval                                   :  6;
     unsigned      vdqtrg                                    :  1;
     unsigned      vddqten                                   :  1;
     unsigned      rsvd_9_8                                  :  2;
     unsigned      tccdl                                     :  3;
     unsigned      rsvd_15_13                                :  3;
     unsigned      reserved_31_16                            : 16;
#endif
} ncp_phy_MR6_t;

/*! @struct ncp_phy_MR7_t
 *  @brief null
 *  @details DDR4 Mode Register 7
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_MR7_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd_15_0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserve for future use. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_MR7_t
 *
 * Implemented by: 
 *      MR7
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_16                            : 16;
     unsigned      rsvd_15_0                                 : 16;
#else    /* Little Endian */
     unsigned      rsvd_15_0                                 : 16;
     unsigned      reserved_31_16                            : 16;
#endif
} ncp_phy_MR7_t;

/*! @struct ncp_phy_MR11_t
 *  @brief null
 *  @details LPDDR3 Mode Register 11
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_MR11_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved.Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsvd </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> These are JEDEC reserved bits and are recommended
 *        by JEDEC to be programmed to 0x0
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pdctl </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Power Down control. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqodt </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> On Die Termination. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_MR11_t
 *
 * Implemented by: 
 *      MR11
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_8                             : 24;
     unsigned      rsvd                                      :  5;
     unsigned      pdctl                                     :  1;
     unsigned      dqodt                                     :  2;
#else    /* Little Endian */
     unsigned      dqodt                                     :  2;
     unsigned      pdctl                                     :  1;
     unsigned      rsvd                                      :  5;
     unsigned      reserved_31_8                             : 24;
#endif
} ncp_phy_MR11_t;

/*! @struct ncp_phy_DTCR0_t
 *  @brief null
 *  @details Data Training Configuration Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DTCR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rfshdt </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Refresh During Training. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_27_26 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtdrs </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Data Training Debug Rank Select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtexg </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Data Training with Early/Extended Gate. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtexd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Data Training Extended Write DQS. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtdstp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Data Training Debug Step. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtden </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Data Training Debug Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtdbs </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Data Training Debug Byte Select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtrdbitr </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Data Training read DBI deskewing configuration. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtbdc </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Data Training Bit Deskew Centering. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtwbddm </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Data Training Write Bit Deskew Data Mask. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rfshent </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Refreshes Issued During Entry to Training: </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtcmpd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Data Training Compare Data. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtmpr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Data Training Using MPR (DDR3 Only). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_5_4 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtrptn </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data Training Repeat Number. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DTCR0_t
 *
 * Implemented by: 
 *      DTCR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      rfshdt                                    :  4;
     unsigned      reserved_27_26                            :  2;
     unsigned      dtdrs                                     :  2;
     unsigned      dtexg                                     :  1;
     unsigned      dtexd                                     :  1;
     unsigned      dtdstp                                    :  1;
     unsigned      dtden                                     :  1;
     unsigned      dtdbs                                     :  4;
     unsigned      dtrdbitr                                  :  2;
     unsigned      dtbdc                                     :  1;
     unsigned      dtwbddm                                   :  1;
     unsigned      rfshent                                   :  4;
     unsigned      dtcmpd                                    :  1;
     unsigned      dtmpr                                     :  1;
     unsigned      reserved_5_4                              :  2;
     unsigned      dtrptn                                    :  4;
#else    /* Little Endian */
     unsigned      dtrptn                                    :  4;
     unsigned      reserved_5_4                              :  2;
     unsigned      dtmpr                                     :  1;
     unsigned      dtcmpd                                    :  1;
     unsigned      rfshent                                   :  4;
     unsigned      dtwbddm                                   :  1;
     unsigned      dtbdc                                     :  1;
     unsigned      dtrdbitr                                  :  2;
     unsigned      dtdbs                                     :  4;
     unsigned      dtden                                     :  1;
     unsigned      dtdstp                                    :  1;
     unsigned      dtexd                                     :  1;
     unsigned      dtexg                                     :  1;
     unsigned      dtdrs                                     :  2;
     unsigned      reserved_27_26                            :  2;
     unsigned      rfshdt                                    :  4;
#endif
} ncp_phy_DTCR0_t;

/*! @struct ncp_phy_DTCR1_t
 *  @brief null
 *  @details Data Training Configuration Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DTCR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param ranken_rsvd </td>
 *     <td width="20%" align="center"> 14 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Rank Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ranken </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Rank Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtrank </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Data Training Rank. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_11 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvlgdiff </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Read Leveling Gate Sampling Difference. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvlgs </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Read Leveling Gate Shift. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdprmvl_trn </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Read Preamble Training Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvlen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Read Leveling Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bsten </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Basic Gate Training Enable. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DTCR1_t
 *
 * Implemented by: 
 *      DTCR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      ranken_rsvd                               : 14;
     unsigned      ranken                                    :  2;
     unsigned      reserved_15_14                            :  2;
     unsigned      dtrank                                    :  2;
     unsigned      reserved_11                               :  1;
     unsigned      rdlvlgdiff                                :  3;
     unsigned      reserved_7                                :  1;
     unsigned      rdlvlgs                                   :  3;
     unsigned      reserved_3                                :  1;
     unsigned      rdprmvl_trn                               :  1;
     unsigned      rdlvlen                                   :  1;
     unsigned      bsten                                     :  1;
#else    /* Little Endian */
     unsigned      bsten                                     :  1;
     unsigned      rdlvlen                                   :  1;
     unsigned      rdprmvl_trn                               :  1;
     unsigned      reserved_3                                :  1;
     unsigned      rdlvlgs                                   :  3;
     unsigned      reserved_7                                :  1;
     unsigned      rdlvlgdiff                                :  3;
     unsigned      reserved_11                               :  1;
     unsigned      dtrank                                    :  2;
     unsigned      reserved_15_14                            :  2;
     unsigned      ranken                                    :  2;
     unsigned      ranken_rsvd                               : 14;
#endif
} ncp_phy_DTCR1_t;

/*! @struct ncp_phy_DTAR0_t
 *  @brief null
 *  @details Data Training Address Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DTAR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mprloc </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Multi-Purpose Register (MPR) Location. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtbgbk1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Data Training Bank Group and Bank Address. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtbgbk0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Data Training Bank Group and Bank Address. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_19_18 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtrow </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data Training Row Address. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DTAR0_t
 *
 * Implemented by: 
 *      DTAR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      mprloc                                    :  2;
     unsigned      dtbgbk1                                   :  4;
     unsigned      dtbgbk0                                   :  4;
     unsigned      reserved_19_18                            :  2;
     unsigned      dtrow                                     : 18;
#else    /* Little Endian */
     unsigned      dtrow                                     : 18;
     unsigned      reserved_19_18                            :  2;
     unsigned      dtbgbk0                                   :  4;
     unsigned      dtbgbk1                                   :  4;
     unsigned      mprloc                                    :  2;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_DTAR0_t;

/*! @struct ncp_phy_DTAR1_t
 *  @brief null
 *  @details Data Training Address Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DTAR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_25 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtcol1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Data Training Column Address. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_9 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtcol0 </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data Training Column Address. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DTAR1_t
 *
 * Implemented by: 
 *      DTAR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_25                            :  7;
     unsigned      dtcol1                                    :  9;
     unsigned      reserved_15_9                             :  7;
     unsigned      dtcol0                                    :  9;
#else    /* Little Endian */
     unsigned      dtcol0                                    :  9;
     unsigned      reserved_15_9                             :  7;
     unsigned      dtcol1                                    :  9;
     unsigned      reserved_31_25                            :  7;
#endif
} ncp_phy_DTAR1_t;

/*! @struct ncp_phy_DTAR2_t
 *  @brief null
 *  @details Data Training Address Register 2
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DTAR2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_25 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtcol3 </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Data Training Column Address. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_9 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtcol2 </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data Training Column Address. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DTAR2_t
 *
 * Implemented by: 
 *      DTAR2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_25                            :  7;
     unsigned      dtcol3                                    :  9;
     unsigned      reserved_15_9                             :  7;
     unsigned      dtcol2                                    :  9;
#else    /* Little Endian */
     unsigned      dtcol2                                    :  9;
     unsigned      reserved_15_9                             :  7;
     unsigned      dtcol3                                    :  9;
     unsigned      reserved_31_25                            :  7;
#endif
} ncp_phy_DTAR2_t;

/*! @struct ncp_phy_DTDR0_t
 *  @brief null
 *  @details Data Training Data Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DTDR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dtbyte3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Data Training Data. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtbyte2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Data Training Data. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtbyte1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Data Training Data. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtbyte0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data Training Data. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DTDR0_t
 *
 * Implemented by: 
 *      DTDR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      dtbyte3                                   :  8;
     unsigned      dtbyte2                                   :  8;
     unsigned      dtbyte1                                   :  8;
     unsigned      dtbyte0                                   :  8;
#else    /* Little Endian */
     unsigned      dtbyte0                                   :  8;
     unsigned      dtbyte1                                   :  8;
     unsigned      dtbyte2                                   :  8;
     unsigned      dtbyte3                                   :  8;
#endif
} ncp_phy_DTDR0_t;

/*! @struct ncp_phy_DTDR1_t
 *  @brief null
 *  @details Data Training Data Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DTDR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dtbyte7 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Data Training Data. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtbyte6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Data Training Data. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtbyte5 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Data Training Data. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtbyte4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data Training Data. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DTDR1_t
 *
 * Implemented by: 
 *      DTDR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      dtbyte7                                   :  8;
     unsigned      dtbyte6                                   :  8;
     unsigned      dtbyte5                                   :  8;
     unsigned      dtbyte4                                   :  8;
#else    /* Little Endian */
     unsigned      dtbyte4                                   :  8;
     unsigned      dtbyte5                                   :  8;
     unsigned      dtbyte6                                   :  8;
     unsigned      dtbyte7                                   :  8;
#endif
} ncp_phy_DTDR1_t;

/*! @struct ncp_phy_DTEDR0_t
 *  @brief null
 *  @details Data Training Eye Data Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DTEDR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dtwbmx </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Data Training Write BDL Shift Maximum. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtwbmn </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Data Training Write BDL Shift Minimum. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtwlmx </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Data Training WDQ LCDL Maximum. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtwlmn </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data Training WDQ LCDL Minimum. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DTEDR0_t
 *
 * Implemented by: 
 *      DTEDR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      dtwbmx                                    :  8;
     unsigned      dtwbmn                                    :  6;
     unsigned      dtwlmx                                    :  9;
     unsigned      dtwlmn                                    :  9;
#else    /* Little Endian */
     unsigned      dtwlmn                                    :  9;
     unsigned      dtwlmx                                    :  9;
     unsigned      dtwbmn                                    :  6;
     unsigned      dtwbmx                                    :  8;
#endif
} ncp_phy_DTEDR0_t;

/*! @struct ncp_phy_DTEDR1_t
 *  @brief null
 *  @details Data Training Eye Data Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DTEDR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dtrbmx </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Data Training Read BDL Shift Maximum. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtrbmn </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Data Training Read BDL Shift Minimum. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtrlmx </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Data Training RDQS LCDL Maximum. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtrlmn </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data Training RDQS LCDL Minimum. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DTEDR1_t
 *
 * Implemented by: 
 *      DTEDR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      dtrbmx                                    :  8;
     unsigned      dtrbmn                                    :  6;
     unsigned      dtrlmx                                    :  9;
     unsigned      dtrlmn                                    :  9;
#else    /* Little Endian */
     unsigned      dtrlmn                                    :  9;
     unsigned      dtrlmx                                    :  9;
     unsigned      dtrbmn                                    :  6;
     unsigned      dtrbmx                                    :  8;
#endif
} ncp_phy_DTEDR1_t;

/*! @struct ncp_phy_DTEDR2_t
 *  @brief null
 *  @details Data Training Eye Data Register 2
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DTEDR2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dtrbmx </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Data Training Read BDL Shift Maximum. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtrbmn </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Data Training Read BDL Shift Minimum. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtrlmx </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Data Training RDQSN LCDL Maximum. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dtrlmn </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data Training RDQSN LCDL Minimum. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DTEDR2_t
 *
 * Implemented by: 
 *      DTEDR2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      dtrbmx                                    :  8;
     unsigned      dtrbmn                                    :  6;
     unsigned      dtrlmx                                    :  9;
     unsigned      dtrlmn                                    :  9;
#else    /* Little Endian */
     unsigned      dtrlmn                                    :  9;
     unsigned      dtrlmx                                    :  9;
     unsigned      dtrbmn                                    :  6;
     unsigned      dtrbmx                                    :  8;
#endif
} ncp_phy_DTEDR2_t;

/*! @struct ncp_phy_VTDR_t
 *  @brief null
 *  @details VREF Training Data Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_VTDR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hvrefmx </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> DRAM DQ VREF Maximum. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_22 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hvrefmn </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DRAM DQ VREF Minimum. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dvrefmx </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DRAM DQ VREF Maximum. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dvrefmn </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM DQ VREF Minimum. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_VTDR_t
 *
 * Implemented by: 
 *      VTDR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      hvrefmx                                   :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      hvrefmn                                   :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dvrefmx                                   :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dvrefmn                                   :  6;
#else    /* Little Endian */
     unsigned      dvrefmn                                   :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dvrefmx                                   :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      hvrefmn                                   :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      hvrefmx                                   :  6;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_VTDR_t;

/*! @struct ncp_phy_CATR0_t
 *  @brief null
 *  @details CA Training Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CATR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_21 </td>
 *     <td width="20%" align="center"> 11 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cacd </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Minimum time (in terms of number of dram clocks) between
 *        two consectuve CA calibration command .
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_13 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param caadr </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Minimum time (in terms of number of dram clocks) PUB
 *        should wait before sampling the CA response after
 *        Calibration command has been sent to the memory.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ca1byte1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> CA_1 Response Byte Lane 1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ca1byte0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CA_1 Response Byte Lane 0. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_CATR0_t
 *
 * Implemented by: 
 *      CATR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_21                            : 11;
     unsigned      cacd                                      :  5;
     unsigned      reserved_15_13                            :  3;
     unsigned      caadr                                     :  5;
     unsigned      ca1byte1                                  :  4;
     unsigned      ca1byte0                                  :  4;
#else    /* Little Endian */
     unsigned      ca1byte0                                  :  4;
     unsigned      ca1byte1                                  :  4;
     unsigned      caadr                                     :  5;
     unsigned      reserved_15_13                            :  3;
     unsigned      cacd                                      :  5;
     unsigned      reserved_31_21                            : 11;
#endif
} ncp_phy_CATR0_t;

/*! @struct ncp_phy_CATR1_t
 *  @brief null
 *  @details CA Training Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_CATR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_28 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ca0byte1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> CA_0 Response Byte Lane 1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ca0byte0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> CA_0 Response Byte Lane 0. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param camrz </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Minimum time (in terms of number of dram clocks) for
 *        DRAM DQ going tristate after MRW CA exit calibration
 *        command.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cackeh </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Minimum time (in terms of number of dram clocks) for
 *        CKE high after last CA calibration response is driven
 *        by memory.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cackel </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Minimum time (in terms of number of dram clocks) for
 *        CKE going low after CA calibration mode is programmed.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param caext </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Minimum time (in terms of number of dram clocks) for
 *        CA calibration exit command after CKE is high.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param caent </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Minimum time (in terms of number of dram clocks) for
 *        first CA calibration command after CKE is low.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_CATR1_t
 *
 * Implemented by: 
 *      CATR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_28                            :  4;
     unsigned      ca0byte1                                  :  4;
     unsigned      ca0byte0                                  :  4;
     unsigned      camrz                                     :  4;
     unsigned      cackeh                                    :  4;
     unsigned      cackel                                    :  4;
     unsigned      caext                                     :  4;
     unsigned      caent                                     :  4;
#else    /* Little Endian */
     unsigned      caent                                     :  4;
     unsigned      caext                                     :  4;
     unsigned      cackel                                    :  4;
     unsigned      cackeh                                    :  4;
     unsigned      camrz                                     :  4;
     unsigned      ca0byte0                                  :  4;
     unsigned      ca0byte1                                  :  4;
     unsigned      reserved_31_28                            :  4;
#endif
} ncp_phy_CATR1_t;

/*! @struct ncp_phy_DQSDR0_t
 *  @brief null
 *  @details DQS Drift Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DQSDR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dftdly </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Number of delay taps by which the DQS gate LCDL will
 *        be updated when DQS drift is detected.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dftzqup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Drift Impedance Update. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dftddlup </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Drift DDL Update. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_25_22 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dftrdspc </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Drift Read Spacing. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dftb2brd </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Drift Back-to-Back Reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dftidlrd </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Drift Idle Reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_11_8 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dftgpulse </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Gate Pulse Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dftupmode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> DQS Drift Update Mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dftdtmode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> DQS Drift Detection Mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dftdten </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DQS Drift Detection Enable. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DQSDR0_t
 *
 * Implemented by: 
 *      DQSDR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      dftdly                                    :  4;
     unsigned      dftzqup                                   :  1;
     unsigned      dftddlup                                  :  1;
     unsigned      reserved_25_22                            :  4;
     unsigned      dftrdspc                                  :  2;
     unsigned      dftb2brd                                  :  4;
     unsigned      dftidlrd                                  :  4;
     unsigned      reserved_11_8                             :  4;
     unsigned      dftgpulse                                 :  4;
     unsigned      dftupmode                                 :  2;
     unsigned      dftdtmode                                 :  1;
     unsigned      dftdten                                   :  1;
#else    /* Little Endian */
     unsigned      dftdten                                   :  1;
     unsigned      dftdtmode                                 :  1;
     unsigned      dftupmode                                 :  2;
     unsigned      dftgpulse                                 :  4;
     unsigned      reserved_11_8                             :  4;
     unsigned      dftidlrd                                  :  4;
     unsigned      dftb2brd                                  :  4;
     unsigned      dftrdspc                                  :  2;
     unsigned      reserved_25_22                            :  4;
     unsigned      dftddlup                                  :  1;
     unsigned      dftzqup                                   :  1;
     unsigned      dftdly                                    :  4;
#endif
} ncp_phy_DQSDR0_t;

/*! @struct ncp_phy_DQSDR1_t
 *  @brief null
 *  @details DQS Drift Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DQSDR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_24 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dftrdb2bf </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Drift Back-to-Back Read Cycles Factor. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dftrdidlf </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Drift Idle Read Cycles Factor. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dftrdb2bc </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Drift Back-to-Back Read Cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dftrdidlc </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Drift Idle Read Cycles. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DQSDR1_t
 *
 * Implemented by: 
 *      DQSDR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_24                            :  8;
     unsigned      dftrdb2bf                                 :  4;
     unsigned      dftrdidlf                                 :  4;
     unsigned      dftrdb2bc                                 :  8;
     unsigned      dftrdidlc                                 :  8;
#else    /* Little Endian */
     unsigned      dftrdidlc                                 :  8;
     unsigned      dftrdb2bc                                 :  8;
     unsigned      dftrdidlf                                 :  4;
     unsigned      dftrdb2bf                                 :  4;
     unsigned      reserved_31_24                            :  8;
#endif
} ncp_phy_DQSDR1_t;

/*! @struct ncp_phy_DQSDR2_t
 *  @brief null
 *  @details DQS Drift Register 2
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DQSDR2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_24 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dftthrsh </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Drift Threshold. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dftmntprd </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Drift Monitor Period. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DQSDR2_t
 *
 * Implemented by: 
 *      DQSDR2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_24                            :  8;
     unsigned      dftthrsh                                  :  8;
     unsigned      dftmntprd                                 : 16;
#else    /* Little Endian */
     unsigned      dftmntprd                                 : 16;
     unsigned      dftthrsh                                  :  8;
     unsigned      reserved_31_24                            :  8;
#endif
} ncp_phy_DQSDR2_t;

/*! @struct ncp_phy_DCUAR_t
 *  @brief null
 *  @details DCU Address Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DCUAR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_20 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param csaddr_r </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Cache Slice Address. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cwaddr_r </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Cache Word Address. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param atype </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Access Type. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param inca </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Increment Address. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param csel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Cache Select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param csaddr_w </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Cache Slice Address. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cwaddr_w </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Cache Word Address. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DCUAR_t
 *
 * Implemented by: 
 *      DCUAR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_20                            : 12;
     unsigned      csaddr_r                                  :  4;
     unsigned      cwaddr_r                                  :  4;
     unsigned      atype                                     :  1;
     unsigned      inca                                      :  1;
     unsigned      csel                                      :  2;
     unsigned      csaddr_w                                  :  4;
     unsigned      cwaddr_w                                  :  4;
#else    /* Little Endian */
     unsigned      cwaddr_w                                  :  4;
     unsigned      csaddr_w                                  :  4;
     unsigned      csel                                      :  2;
     unsigned      inca                                      :  1;
     unsigned      atype                                     :  1;
     unsigned      cwaddr_r                                  :  4;
     unsigned      csaddr_r                                  :  4;
     unsigned      reserved_31_20                            : 12;
#endif
} ncp_phy_DCUAR_t;

/*! @struct ncp_phy_DCUDR_t
 *  @brief null
 *  @details DCU Data Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DCUDR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cdata </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Cache Data. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DCUDR_t
 *
 * Implemented by: 
 *      DCUDR
 */
 
typedef struct
{
     unsigned  int                     cdata;
} ncp_phy_DCUDR_t;

/*! @struct ncp_phy_DCURR_t
 *  @brief null
 *  @details DCU Run Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DCURR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_24 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param xcen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Expected Compare Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rcen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Read Capture Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param scof </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Stop Capture On Full. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sonf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Stop On Nth Fail. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param nfail </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Number of Failures. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eaddr </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> End Address. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param saddr </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Start Address. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dinst </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DCU Instruction. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DCURR_t
 *
 * Implemented by: 
 *      DCURR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_24                            :  8;
     unsigned      xcen                                      :  1;
     unsigned      rcen                                      :  1;
     unsigned      scof                                      :  1;
     unsigned      sonf                                      :  1;
     unsigned      nfail                                     :  8;
     unsigned      eaddr                                     :  4;
     unsigned      saddr                                     :  4;
     unsigned      dinst                                     :  4;
#else    /* Little Endian */
     unsigned      dinst                                     :  4;
     unsigned      saddr                                     :  4;
     unsigned      eaddr                                     :  4;
     unsigned      nfail                                     :  8;
     unsigned      sonf                                      :  1;
     unsigned      scof                                      :  1;
     unsigned      rcen                                      :  1;
     unsigned      xcen                                      :  1;
     unsigned      reserved_31_24                            :  8;
#endif
} ncp_phy_DCURR_t;

/*! @struct ncp_phy_DCULR_t
 *  @brief null
 *  @details DCU Loop Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DCULR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param xleaddr </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Expected Data Loop End Address. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_27_18 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ida </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Increment DRAM Address. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param linf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Loop Infinite. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lcnt </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Loop Count. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param leaddr </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Loop End Address. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lsaddr </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Loop Start Address. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DCULR_t
 *
 * Implemented by: 
 *      DCULR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      xleaddr                                   :  4;
     unsigned      reserved_27_18                            : 10;
     unsigned      ida                                       :  1;
     unsigned      linf                                      :  1;
     unsigned      lcnt                                      :  8;
     unsigned      leaddr                                    :  4;
     unsigned      lsaddr                                    :  4;
#else    /* Little Endian */
     unsigned      lsaddr                                    :  4;
     unsigned      leaddr                                    :  4;
     unsigned      lcnt                                      :  8;
     unsigned      linf                                      :  1;
     unsigned      ida                                       :  1;
     unsigned      reserved_27_18                            : 10;
     unsigned      xleaddr                                   :  4;
#endif
} ncp_phy_DCULR_t;

/*! @struct ncp_phy_DCUGCR_t
 *  @brief null
 *  @details DCU General Configuration Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DCUGCR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rcsw </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Read Capture Start Word. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DCUGCR_t
 *
 * Implemented by: 
 *      DCUGCR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_16                            : 16;
     unsigned      rcsw                                      : 16;
#else    /* Little Endian */
     unsigned      rcsw                                      : 16;
     unsigned      reserved_31_16                            : 16;
#endif
} ncp_phy_DCUGCR_t;

/*! @struct ncp_phy_DCUTPR_t
 *  @brief null
 *  @details DCU Timing Parameters Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DCUTPR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_24 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdcut2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DCU Generic Timing Parameter 2. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdcut1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DCU Generic Timing Parameter 1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdcut0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DCU Generic Timing Parameter 0. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DCUTPR_t
 *
 * Implemented by: 
 *      DCUTPR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_24                            :  8;
     unsigned      tdcut2                                    :  8;
     unsigned      tdcut1                                    :  8;
     unsigned      tdcut0                                    :  8;
#else    /* Little Endian */
     unsigned      tdcut0                                    :  8;
     unsigned      tdcut1                                    :  8;
     unsigned      tdcut2                                    :  8;
     unsigned      reserved_31_24                            :  8;
#endif
} ncp_phy_DCUTPR_t;

/*! @struct ncp_phy_DCUSR0_t
 *  @brief null
 *  @details DCU Status Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DCUSR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_3 </td>
 *     <td width="20%" align="center"> 29 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfull </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Capture Full. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfail </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Capture Fail. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Run Done. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DCUSR0_t
 *
 * Implemented by: 
 *      DCUSR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_3                             : 29;
     unsigned      cfull                                     :  1;
     unsigned      cfail                                     :  1;
     unsigned      rdone                                     :  1;
#else    /* Little Endian */
     unsigned      rdone                                     :  1;
     unsigned      cfail                                     :  1;
     unsigned      cfull                                     :  1;
     unsigned      reserved_31_3                             : 29;
#endif
} ncp_phy_DCUSR0_t;

/*! @struct ncp_phy_DCUSR1_t
 *  @brief null
 *  @details DCU Status Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DCUSR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param lpcnt </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Loop Count. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param flcnt </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Fail Count. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdcnt </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Read Count. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DCUSR1_t
 *
 * Implemented by: 
 *      DCUSR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      lpcnt                                     :  8;
     unsigned      flcnt                                     :  8;
     unsigned      rdcnt                                     : 16;
#else    /* Little Endian */
     unsigned      rdcnt                                     : 16;
     unsigned      flcnt                                     :  8;
     unsigned      lpcnt                                     :  8;
#endif
} ncp_phy_DCUSR1_t;

/*! @struct ncp_phy_BISTRR_t
 *  @brief null
 *  @details BIST Run Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_BISTRR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_27 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bccsel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> BIST Clock Cycle Select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bcksel </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> BIST CK Select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bdxsel </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> BIST DATX8 Select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bdpat </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> BIST Data Pattern. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bdmen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> BIST Data Mask Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bacen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> BIST AC Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bdxen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> BIST DATX8 Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bsonf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> BIST Stop On Nth Fail. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param nfail </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Number of Failures. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param binf </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> BIST Infinite Run. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bmode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> BIST Mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param binst </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> BIST Instruction. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_BISTRR_t
 *
 * Implemented by: 
 *      BISTRR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_27                            :  5;
     unsigned      bccsel                                    :  2;
     unsigned      bcksel                                    :  2;
     unsigned      bdxsel                                    :  4;
     unsigned      bdpat                                     :  2;
     unsigned      bdmen                                     :  1;
     unsigned      bacen                                     :  1;
     unsigned      bdxen                                     :  1;
     unsigned      bsonf                                     :  1;
     unsigned      nfail                                     :  8;
     unsigned      binf                                      :  1;
     unsigned      bmode                                     :  1;
     unsigned      binst                                     :  3;
#else    /* Little Endian */
     unsigned      binst                                     :  3;
     unsigned      bmode                                     :  1;
     unsigned      binf                                      :  1;
     unsigned      nfail                                     :  8;
     unsigned      bsonf                                     :  1;
     unsigned      bdxen                                     :  1;
     unsigned      bacen                                     :  1;
     unsigned      bdmen                                     :  1;
     unsigned      bdpat                                     :  2;
     unsigned      bdxsel                                    :  4;
     unsigned      bcksel                                    :  2;
     unsigned      bccsel                                    :  2;
     unsigned      reserved_31_27                            :  5;
#endif
} ncp_phy_BISTRR_t;

/*! @struct ncp_phy_BISTWCR_t
 *  @brief null
 *  @details BIST Word Count Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_BISTWCR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bwcnt </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> BIST Word Count. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_BISTWCR_t
 *
 * Implemented by: 
 *      BISTWCR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved                                  : 16;
     unsigned      bwcnt                                     : 16;
#else    /* Little Endian */
     unsigned      bwcnt                                     : 16;
     unsigned      reserved                                  : 16;
#endif
} ncp_phy_BISTWCR_t;

/*! @struct ncp_phy_BISTMSKR0_t
 *  @brief null
 *  @details BIST Mask Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_BISTMSKR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param csmsk_rsvd </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param csmsk </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Mask bit for each of the up to 12 CS_N bits. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param actmsk </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Mask bit for the RAS. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_18 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param amsk </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Mask bit for each of the up to 16 address bits. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_BISTMSKR0_t
 *
 * Implemented by: 
 *      BISTMSKR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      csmsk_rsvd                                : 10;
     unsigned      csmsk                                     :  2;
     unsigned      actmsk                                    :  1;
     unsigned      reserved_18                               :  1;
     unsigned      amsk                                      : 18;
#else    /* Little Endian */
     unsigned      amsk                                      : 18;
     unsigned      reserved_18                               :  1;
     unsigned      actmsk                                    :  1;
     unsigned      csmsk                                     :  2;
     unsigned      csmsk_rsvd                                : 10;
#endif
} ncp_phy_BISTMSKR0_t;

/*! @struct ncp_phy_BISTMSKR1_t
 *  @brief null
 *  @details BIST Mask Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_BISTMSKR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dmmsk </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Mask bit for the data mask (DM) bit. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param parinmsk </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Mask bit for the PAR_IN. Only for DIMM parity support
 *        and only if the design is compiled for less than 3
 *        ranks.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cidmsk_rsvd </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cidmsk </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Mask bits for each of the up to 3 Chip IP bits. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odtmsk_rsvd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odtmsk </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Mask bit for each of the up to 8 ODT bits. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ckemsk_rsvd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ckemsk </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Mask bit for each of the up to 8 CKE bits. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bamsk </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Mask bit for each of the up to 4 bank address bits. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_3_0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_BISTMSKR1_t
 *
 * Implemented by: 
 *      BISTMSKR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      dmmsk                                     :  4;
     unsigned      parinmsk                                  :  1;
     unsigned      cidmsk_rsvd                               :  2;
     unsigned      cidmsk                                    :  1;
     unsigned      odtmsk_rsvd                               :  6;
     unsigned      odtmsk                                    :  2;
     unsigned      ckemsk_rsvd                               :  6;
     unsigned      ckemsk                                    :  2;
     unsigned      bamsk                                     :  4;
     unsigned      reserved_3_0                              :  4;
#else    /* Little Endian */
     unsigned      reserved_3_0                              :  4;
     unsigned      bamsk                                     :  4;
     unsigned      ckemsk                                    :  2;
     unsigned      ckemsk_rsvd                               :  6;
     unsigned      odtmsk                                    :  2;
     unsigned      odtmsk_rsvd                               :  6;
     unsigned      cidmsk                                    :  1;
     unsigned      cidmsk_rsvd                               :  2;
     unsigned      parinmsk                                  :  1;
     unsigned      dmmsk                                     :  4;
#endif
} ncp_phy_BISTMSKR1_t;

/*! @struct ncp_phy_BISTMSKR2_t
 *  @brief null
 *  @details BIST Mask Register 2
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_BISTMSKR2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dqmsk </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Mask bit for each of the 8 data (DQ) bits. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_BISTMSKR2_t
 *
 * Implemented by: 
 *      BISTMSKR2
 */
 
typedef struct
{
     unsigned  int                     dqmsk;
} ncp_phy_BISTMSKR2_t;

/*! @struct ncp_phy_BISTLSR_t
 *  @brief null
 *  @details BIST LFSR Seed Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_BISTLSR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param seed </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> LFSR seed for pseudo-random BIST patterns. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_BISTLSR_t
 *
 * Implemented by: 
 *      BISTLSR
 */
 
typedef struct
{
     unsigned  int                      seed;
} ncp_phy_BISTLSR_t;

/*! @struct ncp_phy_BISTAR0_t
 *  @brief null
 *  @details BIST Address Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_BISTAR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param bbank </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> BIST Bank Address. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_27_12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bcol </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> BIST Column Address. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_BISTAR0_t
 *
 * Implemented by: 
 *      BISTAR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      bbank                                     :  4;
     unsigned      reserved_27_12                            : 16;
     unsigned      bcol                                      : 12;
#else    /* Little Endian */
     unsigned      bcol                                      : 12;
     unsigned      reserved_27_12                            : 16;
     unsigned      bbank                                     :  4;
#endif
} ncp_phy_BISTAR0_t;

/*! @struct ncp_phy_BISTAR1_t
 *  @brief null
 *  @details BIST Address Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_BISTAR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_20 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bmrank </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> BIST Maximum Rank. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bainc </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> BIST Address Increment. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param brank </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> BIST Rank. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_BISTAR1_t
 *
 * Implemented by: 
 *      BISTAR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_20                            : 12;
     unsigned      bmrank                                    :  4;
     unsigned      bainc                                     : 12;
     unsigned      brank                                     :  4;
#else    /* Little Endian */
     unsigned      brank                                     :  4;
     unsigned      bainc                                     : 12;
     unsigned      bmrank                                    :  4;
     unsigned      reserved_31_20                            : 12;
#endif
} ncp_phy_BISTAR1_t;

/*! @struct ncp_phy_BISTAR2_t
 *  @brief null
 *  @details BIST Address Register 2
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_BISTAR2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param bmbank </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> BIST Maximum Bank Address. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_27_12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bmcol </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> BIST Maximum Column Address. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_BISTAR2_t
 *
 * Implemented by: 
 *      BISTAR2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      bmbank                                    :  4;
     unsigned      reserved_27_12                            : 16;
     unsigned      bmcol                                     : 12;
#else    /* Little Endian */
     unsigned      bmcol                                     : 12;
     unsigned      reserved_27_12                            : 16;
     unsigned      bmbank                                    :  4;
#endif
} ncp_phy_BISTAR2_t;

/*! @struct ncp_phy_BISTAR3_t
 *  @brief null
 *  @details BIST Address Register 3
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_BISTAR3_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_18 </td>
 *     <td width="20%" align="center"> 14 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param brow </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> BIST Row Address. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_BISTAR3_t
 *
 * Implemented by: 
 *      BISTAR3
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_18                            : 14;
     unsigned      brow                                      : 18;
#else    /* Little Endian */
     unsigned      brow                                      : 18;
     unsigned      reserved_31_18                            : 14;
#endif
} ncp_phy_BISTAR3_t;

/*! @struct ncp_phy_BISTAR4_t
 *  @brief null
 *  @details BIST Address Register 4
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_BISTAR4_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_18 </td>
 *     <td width="20%" align="center"> 14 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bmrow </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> BIST Maximum Row Address. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_BISTAR4_t
 *
 * Implemented by: 
 *      BISTAR4
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_18                            : 14;
     unsigned      bmrow                                     : 18;
#else    /* Little Endian */
     unsigned      bmrow                                     : 18;
     unsigned      reserved_31_18                            : 14;
#endif
} ncp_phy_BISTAR4_t;

/*! @struct ncp_phy_BISTUDPR_t
 *  @brief null
 *  @details BIST User Data Pattern Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_BISTUDPR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param budp1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> BIST User Data Pattern 1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param budp0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> BIST User Data Pattern 0. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_BISTUDPR_t
 *
 * Implemented by: 
 *      BISTUDPR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      budp1                                     : 16;
     unsigned      budp0                                     : 16;
#else    /* Little Endian */
     unsigned      budp0                                     : 16;
     unsigned      budp1                                     : 16;
#endif
} ncp_phy_BISTUDPR_t;

/*! @struct ncp_phy_BISTGSR_t
 *  @brief null
 *  @details BIST General Status Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_BISTGSR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rasber </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> RAS_n/ACT_n Bit Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dmber </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> DM Bit Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_19_12 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_11 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bdxerr </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> BIST Data Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bacerr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> BIST Address/Command Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bdone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> BIST Done. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_BISTGSR_t
 *
 * Implemented by: 
 *      BISTGSR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      rasber                                    :  2;
     unsigned      dmber                                     :  8;
     unsigned      reserved_19_12                            :  8;
     unsigned      reserved_11                               :  1;
     unsigned      bdxerr                                    :  9;
     unsigned      bacerr                                    :  1;
     unsigned      bdone                                     :  1;
#else    /* Little Endian */
     unsigned      bdone                                     :  1;
     unsigned      bacerr                                    :  1;
     unsigned      bdxerr                                    :  9;
     unsigned      reserved_11                               :  1;
     unsigned      reserved_19_12                            :  8;
     unsigned      dmber                                     :  8;
     unsigned      rasber                                    :  2;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_BISTGSR_t;

/*! @struct ncp_phy_BISTWER0_t
 *  @brief null
 *  @details BIST Word Error Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_BISTWER0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_18 </td>
 *     <td width="20%" align="center"> 14 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param acwer </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address/Command Word Error. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_BISTWER0_t
 *
 * Implemented by: 
 *      BISTWER0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_18                            : 14;
     unsigned      acwer                                     : 18;
#else    /* Little Endian */
     unsigned      acwer                                     : 18;
     unsigned      reserved_31_18                            : 14;
#endif
} ncp_phy_BISTWER0_t;

/*! @struct ncp_phy_BISTWER1_t
 *  @brief null
 *  @details BIST Word Error Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_BISTWER1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxwer </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Byte Word Error. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_BISTWER1_t
 *
 * Implemented by: 
 *      BISTWER1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_16                            : 16;
     unsigned      dxwer                                     : 16;
#else    /* Little Endian */
     unsigned      dxwer                                     : 16;
     unsigned      reserved_31_16                            : 16;
#endif
} ncp_phy_BISTWER1_t;

/*! @struct ncp_phy_BISTBER0_t
 *  @brief null
 *  @details BIST Bit Error Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_BISTBER0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param aber </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address Bit Error. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_BISTBER0_t
 *
 * Implemented by: 
 *      BISTBER0
 */
 
typedef struct
{
     unsigned  int                      aber;
} ncp_phy_BISTBER0_t;

/*! @struct ncp_phy_BISTBER1_t
 *  @brief null
 *  @details BIST Bit Error Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_BISTBER1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param csber_rsvd </td>
 *     <td width="20%" align="center"> 20 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param csber </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> CS_N Bit Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param baber </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Bank Address Bit Error. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_BISTBER1_t
 *
 * Implemented by: 
 *      BISTBER1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      csber_rsvd                                : 20;
     unsigned      csber                                     :  4;
     unsigned      baber                                     :  8;
#else    /* Little Endian */
     unsigned      baber                                     :  8;
     unsigned      csber                                     :  4;
     unsigned      csber_rsvd                                : 20;
#endif
} ncp_phy_BISTBER1_t;

/*! @struct ncp_phy_BISTBER2_t
 *  @brief null
 *  @details BIST Bit Error Register 2
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_BISTBER2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dqber0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data Bit Error. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_BISTBER2_t
 *
 * Implemented by: 
 *      BISTBER2
 */
 
typedef struct
{
     unsigned  int                    dqber0;
} ncp_phy_BISTBER2_t;

/*! @struct ncp_phy_BISTBER3_t
 *  @brief null
 *  @details BIST Bit Error Register 3
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_BISTBER3_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dqber1 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data Bit Error. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_BISTBER3_t
 *
 * Implemented by: 
 *      BISTBER3
 */
 
typedef struct
{
     unsigned  int                    dqber1;
} ncp_phy_BISTBER3_t;

/*! @struct ncp_phy_BISTBER4_t
 *  @brief null
 *  @details BIST Bit Error Register 4
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_BISTBER4_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_14 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cidber_rsvd </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cidber </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Chip ID Bit Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param aber </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address Bit Error. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_BISTBER4_t
 *
 * Implemented by: 
 *      BISTBER4
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_14                            : 18;
     unsigned      cidber_rsvd                               :  4;
     unsigned      cidber                                    :  2;
     unsigned      reserved_7_4                              :  4;
     unsigned      aber                                      :  4;
#else    /* Little Endian */
     unsigned      aber                                      :  4;
     unsigned      reserved_7_4                              :  4;
     unsigned      cidber                                    :  2;
     unsigned      cidber_rsvd                               :  4;
     unsigned      reserved_31_14                            : 18;
#endif
} ncp_phy_BISTBER4_t;

/*! @struct ncp_phy_BISTWCSR_t
 *  @brief null
 *  @details BIST Word Count Status Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_BISTWCSR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dxwcnt </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Byte Word Count. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param acwcnt </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address/Command Word Count. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_BISTWCSR_t
 *
 * Implemented by: 
 *      BISTWCSR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      dxwcnt                                    : 16;
     unsigned      acwcnt                                    : 16;
#else    /* Little Endian */
     unsigned      acwcnt                                    : 16;
     unsigned      dxwcnt                                    : 16;
#endif
} ncp_phy_BISTWCSR_t;

/*! @struct ncp_phy_BISTFWR0_t
 *  @brief null
 *  @details BIST Fail Word Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_BISTFWR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param cswebs_rsvd </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cswebs </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Bit status during a word error for each of the up
 *        to 12 CS_N bits.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_19 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param actwebs </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Bit status during a word error for the RAS. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param awebs </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Bit status during a word error for each of the up
 *        to 16 address bits.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_BISTFWR0_t
 *
 * Implemented by: 
 *      BISTFWR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      cswebs_rsvd                               : 10;
     unsigned      cswebs                                    :  2;
     unsigned      reserved_19                               :  1;
     unsigned      actwebs                                   :  1;
     unsigned      awebs                                     : 18;
#else    /* Little Endian */
     unsigned      awebs                                     : 18;
     unsigned      actwebs                                   :  1;
     unsigned      reserved_19                               :  1;
     unsigned      cswebs                                    :  2;
     unsigned      cswebs_rsvd                               : 10;
#endif
} ncp_phy_BISTFWR0_t;

/*! @struct ncp_phy_BISTFWR1_t
 *  @brief null
 *  @details BIST Fail Word Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_BISTFWR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dmwebs </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Bit status during a word error for the data mask (DM)
 *        bit.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_27_24 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cidwebs_rsvd </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cidwebs </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Bit status during a word error for each of the up
 *        to 3 chip ID bits.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bawebs </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Bit status during a word error for each of the up
 *        to 3 bank address bits.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odtwebs_rsvd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odtwebs </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Bit status during a word error for each of the up
 *        to 8 ODT bits.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ckewebs_rsvd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ckewebs </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Bit status during a word error for each of the up
 *        to 8 CKE bits.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_BISTFWR1_t
 *
 * Implemented by: 
 *      BISTFWR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      dmwebs                                    :  4;
     unsigned      reserved_27_24                            :  4;
     unsigned      reserved_23                               :  1;
     unsigned      cidwebs_rsvd                              :  2;
     unsigned      cidwebs                                   :  1;
     unsigned      bawebs                                    :  4;
     unsigned      odtwebs_rsvd                              :  6;
     unsigned      odtwebs                                   :  2;
     unsigned      ckewebs_rsvd                              :  6;
     unsigned      ckewebs                                   :  2;
#else    /* Little Endian */
     unsigned      ckewebs                                   :  2;
     unsigned      ckewebs_rsvd                              :  6;
     unsigned      odtwebs                                   :  2;
     unsigned      odtwebs_rsvd                              :  6;
     unsigned      bawebs                                    :  4;
     unsigned      cidwebs                                   :  1;
     unsigned      cidwebs_rsvd                              :  2;
     unsigned      reserved_23                               :  1;
     unsigned      reserved_27_24                            :  4;
     unsigned      dmwebs                                    :  4;
#endif
} ncp_phy_BISTFWR1_t;

/*! @struct ncp_phy_BISTFWR2_t
 *  @brief null
 *  @details BIST Fail Word Register 2
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_BISTFWR2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dqwebs </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Bit status during a word error for each of the 8 data
 *        (DQ) bits.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_BISTFWR2_t
 *
 * Implemented by: 
 *      BISTFWR2
 */
 
typedef struct
{
     unsigned  int                    dqwebs;
} ncp_phy_BISTFWR2_t;

/*! @struct ncp_phy_BISTBER5_t
 *  @brief null
 *  @details BIST Bit Error Register 5
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_BISTBER5_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param odtber_rsvd </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odtber </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> ODT Bit Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ckeber_rsvd </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ckeber </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CKE Bit Error. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_BISTBER5_t
 *
 * Implemented by: 
 *      BISTBER5
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      odtber_rsvd                               : 12;
     unsigned      odtber                                    :  4;
     unsigned      ckeber_rsvd                               : 12;
     unsigned      ckeber                                    :  4;
#else    /* Little Endian */
     unsigned      ckeber                                    :  4;
     unsigned      ckeber_rsvd                               : 12;
     unsigned      odtber                                    :  4;
     unsigned      odtber_rsvd                               : 12;
#endif
} ncp_phy_BISTBER5_t;

/*! @struct ncp_phy_RANKIDR_t
 *  @brief null
 *  @details Rank ID Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_RANKIDR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_20 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rankrid </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Rank Read ID. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rankwid </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Rank Write ID. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_RANKIDR_t
 *
 * Implemented by: 
 *      RANKIDR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_20                            : 12;
     unsigned      rankrid                                   :  4;
     unsigned      reserved_15_4                             : 12;
     unsigned      rankwid                                   :  4;
#else    /* Little Endian */
     unsigned      rankwid                                   :  4;
     unsigned      reserved_15_4                             : 12;
     unsigned      rankrid                                   :  4;
     unsigned      reserved_31_20                            : 12;
#endif
} ncp_phy_RANKIDR_t;

/*! @struct ncp_phy_RIOCR0_t
 *  @brief null
 *  @details Rank I/O Configuration Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_RIOCR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_28 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cspdr_rsvd </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cspdr </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> SDRAM CSN Power Down Receiver. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_12 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param csodt_rsvd </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param csodt </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> SDRAM CSN On-Die Termination. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_RIOCR0_t
 *
 * Implemented by: 
 *      RIOCR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_28                            :  4;
     unsigned      cspdr_rsvd                                : 10;
     unsigned      cspdr                                     :  2;
     unsigned      reserved_15_12                            :  4;
     unsigned      csodt_rsvd                                : 10;
     unsigned      csodt                                     :  2;
#else    /* Little Endian */
     unsigned      csodt                                     :  2;
     unsigned      csodt_rsvd                                : 10;
     unsigned      reserved_15_12                            :  4;
     unsigned      cspdr                                     :  2;
     unsigned      cspdr_rsvd                                : 10;
     unsigned      reserved_31_28                            :  4;
#endif
} ncp_phy_RIOCR0_t;

/*! @struct ncp_phy_RIOCR1_t
 *  @brief null
 *  @details Rank I/O Configuration Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_RIOCR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param odtpdr_rsvd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odtpdr </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Rank Power Down Receiver. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odtodt_rsvd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odtodt </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Rank On-Die Termination. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ckepdr_rsvd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ckepdr </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Rank Power Down Receiver. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ckeodt_rsvd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ckeodt </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Rank On-Die Termination. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_RIOCR1_t
 *
 * Implemented by: 
 *      RIOCR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      odtpdr_rsvd                               :  6;
     unsigned      odtpdr                                    :  2;
     unsigned      odtodt_rsvd                               :  6;
     unsigned      odtodt                                    :  2;
     unsigned      ckepdr_rsvd                               :  6;
     unsigned      ckepdr                                    :  2;
     unsigned      ckeodt_rsvd                               :  6;
     unsigned      ckeodt                                    :  2;
#else    /* Little Endian */
     unsigned      ckeodt                                    :  2;
     unsigned      ckeodt_rsvd                               :  6;
     unsigned      ckepdr                                    :  2;
     unsigned      ckepdr_rsvd                               :  6;
     unsigned      odtodt                                    :  2;
     unsigned      odtodt_rsvd                               :  6;
     unsigned      odtpdr                                    :  2;
     unsigned      odtpdr_rsvd                               :  6;
#endif
} ncp_phy_RIOCR1_t;

/*! @struct ncp_phy_RIOCR2_t
 *  @brief null
 *  @details Rank I/O Configuration Register 2
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_RIOCR2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param coemode_rsvd </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param coemode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> SDRAM C Output Enable (OE) Mode Selection. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param csoemode_rsvd </td>
 *     <td width="20%" align="center"> 20 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param csoemode </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> SDRAM CS_n Output Enable (OE) Mode Selection. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_RIOCR2_t
 *
 * Implemented by: 
 *      RIOCR2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      coemode_rsvd                              :  4;
     unsigned      coemode                                   :  2;
     unsigned      csoemode_rsvd                             : 20;
     unsigned      csoemode                                  :  4;
#else    /* Little Endian */
     unsigned      csoemode                                  :  4;
     unsigned      csoemode_rsvd                             : 20;
     unsigned      coemode                                   :  2;
     unsigned      coemode_rsvd                              :  4;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_RIOCR2_t;

/*! @struct ncp_phy_RIOCR3_t
 *  @brief null
 *  @details Rank I/O Configuration Register 3
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_RIOCR3_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpddmode_rsvd </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cpddmode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> SDRAM CID Power Down Driver (PDD) Mode Selection. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cspddmode_rsvd </td>
 *     <td width="20%" align="center"> 20 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cspddmode </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> SDRAM CS_n Power Down Driver (PDD) Mode Selection. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_RIOCR3_t
 *
 * Implemented by: 
 *      RIOCR3
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      cpddmode_rsvd                             :  4;
     unsigned      cpddmode                                  :  2;
     unsigned      cspddmode_rsvd                            : 20;
     unsigned      cspddmode                                 :  4;
#else    /* Little Endian */
     unsigned      cspddmode                                 :  4;
     unsigned      cspddmode_rsvd                            : 20;
     unsigned      cpddmode                                  :  2;
     unsigned      cpddmode_rsvd                             :  4;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_RIOCR3_t;

/*! @struct ncp_phy_RIOCR4_t
 *  @brief null
 *  @details Rank I/O Configuration Register 4
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_RIOCR4_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param ckepddmode_rsvd </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ckepddmode </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> SDRAM CKE Power Down Driver (PDD) Mode Selection. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ckeoemode_rsvd </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ckeoemode </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> SDRAM CKE Output Enable (OE) Mode Selection. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_RIOCR4_t
 *
 * Implemented by: 
 *      RIOCR4
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      ckepddmode_rsvd                           : 12;
     unsigned      ckepddmode                                :  4;
     unsigned      ckeoemode_rsvd                            : 12;
     unsigned      ckeoemode                                 :  4;
#else    /* Little Endian */
     unsigned      ckeoemode                                 :  4;
     unsigned      ckeoemode_rsvd                            : 12;
     unsigned      ckepddmode                                :  4;
     unsigned      ckepddmode_rsvd                           : 12;
#endif
} ncp_phy_RIOCR4_t;

/*! @struct ncp_phy_RIOCR5_t
 *  @brief null
 *  @details Rank I/O Configuration Register 5
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_RIOCR5_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param odtpddmode_rsvd </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odtpddmode </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> SDRAM On-die Termination Power Down Driver (PDD) Mode
 *        Selection.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odtoemode_rsvd </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odtoemode </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> SDRAM On-die Termination Output Enable (OE) Mode Selection. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_RIOCR5_t
 *
 * Implemented by: 
 *      RIOCR5
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      odtpddmode_rsvd                           : 12;
     unsigned      odtpddmode                                :  4;
     unsigned      odtoemode_rsvd                            : 12;
     unsigned      odtoemode                                 :  4;
#else    /* Little Endian */
     unsigned      odtoemode                                 :  4;
     unsigned      odtoemode_rsvd                            : 12;
     unsigned      odtpddmode                                :  4;
     unsigned      odtpddmode_rsvd                           : 12;
#endif
} ncp_phy_RIOCR5_t;

/*! @struct ncp_phy_ACIOCR0_t
 *  @brief null
 *  @details AC I/O Configuration Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ACIOCR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param acsr </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Address/Command Slew Rate (D3F I/O Only). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rstiom </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> SDRAM Reset I/O Mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rstpdr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> SDRAM Reset Power Down Receiver. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rstpdd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> SDRAM Reset Power Down Driver. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rstodt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> SDRAM Reset On-Die Termination. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_25_14 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ckpdr_rsvd </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ckpdr </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> CK Power Down Receiver. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_9 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ckodt_rsvd </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ckodt </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> CK On-Die Termination. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param acpdr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> AC Power Down Receiver. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param acodt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Address/Command On-Die Termination. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param aciom </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address/Command I/O Mode. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ACIOCR0_t
 *
 * Implemented by: 
 *      ACIOCR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      acsr                                      :  2;
     unsigned      rstiom                                    :  1;
     unsigned      rstpdr                                    :  1;
     unsigned      rstpdd                                    :  1;
     unsigned      rstodt                                    :  1;
     unsigned      reserved_25_14                            : 12;
     unsigned      ckpdr_rsvd                                :  2;
     unsigned      ckpdr                                     :  2;
     unsigned      reserved_9                                :  1;
     unsigned      ckodt_rsvd                                :  2;
     unsigned      ckodt                                     :  2;
     unsigned      acpdr                                     :  1;
     unsigned      reserved_3                                :  1;
     unsigned      acodt                                     :  1;
     unsigned      reserved_1                                :  1;
     unsigned      aciom                                     :  1;
#else    /* Little Endian */
     unsigned      aciom                                     :  1;
     unsigned      reserved_1                                :  1;
     unsigned      acodt                                     :  1;
     unsigned      reserved_3                                :  1;
     unsigned      acpdr                                     :  1;
     unsigned      ckodt                                     :  2;
     unsigned      ckodt_rsvd                                :  2;
     unsigned      reserved_9                                :  1;
     unsigned      ckpdr                                     :  2;
     unsigned      ckpdr_rsvd                                :  2;
     unsigned      reserved_25_14                            : 12;
     unsigned      rstodt                                    :  1;
     unsigned      rstpdd                                    :  1;
     unsigned      rstpdr                                    :  1;
     unsigned      rstiom                                    :  1;
     unsigned      acsr                                      :  2;
#endif
} ncp_phy_ACIOCR0_t;

/*! @struct ncp_phy_ACIOCR1_t
 *  @brief null
 *  @details AC I/O Configuration Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ACIOCR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param aoemode </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> SDRAM Address Output Enable (OE) Mode Selection. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ACIOCR1_t
 *
 * Implemented by: 
 *      ACIOCR1
 */
 
typedef struct
{
     unsigned  int                   aoemode;
} ncp_phy_ACIOCR1_t;

/*! @struct ncp_phy_ACIOCR2_t
 *  @brief null
 *  @details AC I/O Configuration Register 2
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ACIOCR2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param apddmode </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> SDRAM Address Power Down Driver (PDD) Mode Selection. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ACIOCR2_t
 *
 * Implemented by: 
 *      ACIOCR2
 */
 
typedef struct
{
     unsigned  int                  apddmode;
} ncp_phy_ACIOCR2_t;

/*! @struct ncp_phy_ACIOCR3_t
 *  @brief null
 *  @details AC I/O Configuration Register 3
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ACIOCR3_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param paroemode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> SDRAM Parity Output Enable (OE) Mode Selection. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bgoemode </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> SDRAM Bank Group Output Enable (OE) Mode Selection. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param baoemode </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> SDRAM Bank Address Output Enable (OE) Mode Selection. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param a17oemode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> SDRAM A[17] Output Enable (OE) Mode Selection. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param a16oemode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> SDRAM A[16] / RAS_n Output Enable (OE) Mode Selection. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param actoemode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> SDRAM ACT_n Output Enable (OE) Mode Selection (DDR4
 *        only).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ckoemode_rsvd </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ckoemode </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> SDRAM CK Output Enable (OE) Mode Selection. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ACIOCR3_t
 *
 * Implemented by: 
 *      ACIOCR3
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      paroemode                                 :  2;
     unsigned      bgoemode                                  :  4;
     unsigned      baoemode                                  :  4;
     unsigned      a17oemode                                 :  2;
     unsigned      a16oemode                                 :  2;
     unsigned      actoemode                                 :  2;
     unsigned      reserved_15_8                             :  8;
     unsigned      ckoemode_rsvd                             :  4;
     unsigned      ckoemode                                  :  4;
#else    /* Little Endian */
     unsigned      ckoemode                                  :  4;
     unsigned      ckoemode_rsvd                             :  4;
     unsigned      reserved_15_8                             :  8;
     unsigned      actoemode                                 :  2;
     unsigned      a16oemode                                 :  2;
     unsigned      a17oemode                                 :  2;
     unsigned      baoemode                                  :  4;
     unsigned      bgoemode                                  :  4;
     unsigned      paroemode                                 :  2;
#endif
} ncp_phy_ACIOCR3_t;

/*! @struct ncp_phy_ACIOCR4_t
 *  @brief null
 *  @details AC I/O Configuration Register 4
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ACIOCR4_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param parpddmode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> SDRAM Parity Power Down Driver (PDD) Mode Selection. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bgpddmode </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> SDRAM Bank Group Power Down Driver (PDD) Mode Selection. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bapddmode </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> SDRAM Bank Address Power Down Driver (PDD) Mode Selection. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param a17pddmode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> SDRAM A[17] / WE_n Power Down Driver (PDD) Mode Selection. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param a16pddmode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> SDRAM A[16] / CAS_n Power Down Driver (PDD) Mode Selection. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param actpddmode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> SDRAM RAS_n Power Down Driver (PDD) Mode Selection. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ckpddmode_rsvd </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ckpddmode </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> SDRAM CK Power Down Driver (PDD) Mode Selection. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ACIOCR4_t
 *
 * Implemented by: 
 *      ACIOCR4
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      parpddmode                                :  2;
     unsigned      bgpddmode                                 :  4;
     unsigned      bapddmode                                 :  4;
     unsigned      a17pddmode                                :  2;
     unsigned      a16pddmode                                :  2;
     unsigned      actpddmode                                :  2;
     unsigned      reserved_15_8                             :  8;
     unsigned      ckpddmode_rsvd                            :  4;
     unsigned      ckpddmode                                 :  4;
#else    /* Little Endian */
     unsigned      ckpddmode                                 :  4;
     unsigned      ckpddmode_rsvd                            :  4;
     unsigned      reserved_15_8                             :  8;
     unsigned      actpddmode                                :  2;
     unsigned      a16pddmode                                :  2;
     unsigned      a17pddmode                                :  2;
     unsigned      bapddmode                                 :  4;
     unsigned      bgpddmode                                 :  4;
     unsigned      parpddmode                                :  2;
#endif
} ncp_phy_ACIOCR4_t;

/*! @struct ncp_phy_IOVCR0_t
 *  @brief null
 *  @details IO  VREF Control Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_IOVCR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param acrefiom </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Address/command lane VREF IOM (Used only by D4MU IOs) </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param acrefpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Address/command lane VREF Pad Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param acrefeen </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Address/command lane Internal VREF Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param acrefsen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Address/command lane Single-End VREF Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param acrefien </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Address/command lane Internal VREF Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_22 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param acrefesel </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Address/command lane External VREF Select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param acrefssel </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Address/command lane Single-End VREF Select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param acvrefisel </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> REFSEL Control for internal AC IOs. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_IOVCR0_t
 *
 * Implemented by: 
 *      IOVCR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      acrefiom                                  :  3;
     unsigned      acrefpen                                  :  1;
     unsigned      acrefeen                                  :  2;
     unsigned      acrefsen                                  :  1;
     unsigned      acrefien                                  :  1;
     unsigned      reserved_23_22                            :  2;
     unsigned      acrefesel                                 :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      acrefssel                                 :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      acvrefisel                                :  6;
#else    /* Little Endian */
     unsigned      acvrefisel                                :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      acrefssel                                 :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      acrefesel                                 :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      acrefien                                  :  1;
     unsigned      acrefsen                                  :  1;
     unsigned      acrefeen                                  :  2;
     unsigned      acrefpen                                  :  1;
     unsigned      acrefiom                                  :  3;
#endif
} ncp_phy_IOVCR0_t;

/*! @struct ncp_phy_IOVCR1_t
 *  @brief null
 *  @details IO  VREF Control Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_IOVCR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_10 </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zqrefpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> ZQ VREF Pad Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zqrefien </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> ZQ Internal VREF Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zqrefisel </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> ZQ Internal VREF Select. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_IOVCR1_t
 *
 * Implemented by: 
 *      IOVCR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_10                            : 22;
     unsigned      zqrefpen                                  :  1;
     unsigned      zqrefien                                  :  1;
     unsigned      reserved_7_6                              :  2;
     unsigned      zqrefisel                                 :  6;
#else    /* Little Endian */
     unsigned      zqrefisel                                 :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      zqrefien                                  :  1;
     unsigned      zqrefpen                                  :  1;
     unsigned      reserved_31_10                            : 22;
#endif
} ncp_phy_IOVCR1_t;

/*! @struct ncp_phy_VTCR0_t
 *  @brief null
 *  @details VREF Training Control Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_VTCR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param tvref </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Number of ctl_clk required to meet (> 150ns) timing
 *        requirements during DRAM DQ VREF training.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dven </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> DRM DQ VREF training Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pdaen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Per Device Addressability Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_26_22 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dvss </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> DRAM DQ VREF step size used during DRAM VREF training. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dvmax </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Maximum VREF limit value used during DRAM VREF training. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dvmin </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Minimum VREF limit value used during DRAM VREF training. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dvinit </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Initial DRAM DQ VREF value used during DRAM VREF training. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_VTCR0_t
 *
 * Implemented by: 
 *      VTCR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      tvref                                     :  3;
     unsigned      dven                                      :  1;
     unsigned      pdaen                                     :  1;
     unsigned      reserved_26_22                            :  5;
     unsigned      dvss                                      :  4;
     unsigned      dvmax                                     :  6;
     unsigned      dvmin                                     :  6;
     unsigned      dvinit                                    :  6;
#else    /* Little Endian */
     unsigned      dvinit                                    :  6;
     unsigned      dvmin                                     :  6;
     unsigned      dvmax                                     :  6;
     unsigned      dvss                                      :  4;
     unsigned      reserved_26_22                            :  5;
     unsigned      pdaen                                     :  1;
     unsigned      dven                                      :  1;
     unsigned      tvref                                     :  3;
#endif
} ncp_phy_VTCR0_t;

/*! @struct ncp_phy_VTCR1_t
 *  @brief null
 *  @details VREF Training Control Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_VTCR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param hvss </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Host VREF step size used during VREF training. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hvmax </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Maximum VREF limit value used during DRAM VREF training. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hvmin </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Minimum VREF limit value used during DRAM VREF training. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vwcr </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> VREF Word Count. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_11 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param shrnk </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Static Host Vref Rank Value. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param shren </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Static Host Vref Rank Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tvrefio </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Number of ctl_clk required to meet (> 200ns) VREF
 *        Settling timing requirements during Host IO VREF training.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param eoff </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Eye LCDL Offset value for VREF training. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enum </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Number of LCDL Eye points for which VREF training
 *        is repeated.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hven </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> HOST (IO) internal VREF training Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hvio </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Host IO Type Control. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_VTCR1_t
 *
 * Implemented by: 
 *      VTCR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      hvss                                      :  4;
     unsigned      hvmax                                     :  6;
     unsigned      hvmin                                     :  6;
     unsigned      vwcr                                      :  4;
     unsigned      reserved_11                               :  1;
     unsigned      shrnk                                     :  2;
     unsigned      shren                                     :  1;
     unsigned      tvrefio                                   :  3;
     unsigned      eoff                                      :  2;
     unsigned      Enum                                      :  1;
     unsigned      hven                                      :  1;
     unsigned      hvio                                      :  1;
#else    /* Little Endian */
     unsigned      hvio                                      :  1;
     unsigned      hven                                      :  1;
     unsigned      Enum                                      :  1;
     unsigned      eoff                                      :  2;
     unsigned      tvrefio                                   :  3;
     unsigned      shren                                     :  1;
     unsigned      shrnk                                     :  2;
     unsigned      reserved_11                               :  1;
     unsigned      vwcr                                      :  4;
     unsigned      hvmin                                     :  6;
     unsigned      hvmax                                     :  6;
     unsigned      hvss                                      :  4;
#endif
} ncp_phy_VTCR1_t;

/*! @struct ncp_phy_ACBDLR0_t
 *  @brief null
 *  @details AC Bit Delay Line Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ACBDLR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ck3bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> CK3 Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_22 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ck2bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> CK2 Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ck1bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> CK1 Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ck0bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> CK0 Bit Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ACBDLR0_t
 *
 * Implemented by: 
 *      ACBDLR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      ck3bd                                     :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      ck2bd                                     :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      ck1bd                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      ck0bd                                     :  6;
#else    /* Little Endian */
     unsigned      ck0bd                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      ck1bd                                     :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      ck2bd                                     :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      ck3bd                                     :  6;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_ACBDLR0_t;

/*! @struct ncp_phy_ACBDLR1_t
 *  @brief null
 *  @details AC Bit Delay Line Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ACBDLR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param parbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Delay select for the BDL on Parity. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_22 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param a16bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Delay select for the BDL on Address A[16]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param a17bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Delay select for the BDL on Address A[17]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param actbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Delay select for the BDL on ACTN. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ACBDLR1_t
 *
 * Implemented by: 
 *      ACBDLR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      parbd                                     :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      a16bd                                     :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      a17bd                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      actbd                                     :  6;
#else    /* Little Endian */
     unsigned      actbd                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      a17bd                                     :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      a16bd                                     :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      parbd                                     :  6;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_ACBDLR1_t;

/*! @struct ncp_phy_ACBDLR2_t
 *  @brief null
 *  @details AC Bit Delay Line Register 2
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ACBDLR2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bg1bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Delay select for the BDL on BG[1]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_22 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bg0bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Delay select for the BDL on BG[0]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reser.ved Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ba1bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Delay select for the BDL on BA[1]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ba0bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Delay select for the BDL on BA[0]. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ACBDLR2_t
 *
 * Implemented by: 
 *      ACBDLR2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      bg1bd                                     :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      bg0bd                                     :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      ba1bd                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      ba0bd                                     :  6;
#else    /* Little Endian */
     unsigned      ba0bd                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      ba1bd                                     :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      bg0bd                                     :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      bg1bd                                     :  6;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_ACBDLR2_t;

/*! @struct ncp_phy_ACBDLR3_t
 *  @brief null
 *  @details AC Bit Delay Line Register 3
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ACBDLR3_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cs3bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Delay select for the BDL on CS[3]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_22 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cs2bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Delay select for the BDL on CS[2]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cs1bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Delay select for the BDL on CS[1]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cs0bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Delay select for the BDL on CS[0]. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ACBDLR3_t
 *
 * Implemented by: 
 *      ACBDLR3
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      cs3bd                                     :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      cs2bd                                     :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      cs1bd                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      cs0bd                                     :  6;
#else    /* Little Endian */
     unsigned      cs0bd                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      cs1bd                                     :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      cs2bd                                     :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      cs3bd                                     :  6;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_ACBDLR3_t;

/*! @struct ncp_phy_ACBDLR4_t
 *  @brief null
 *  @details AC Bit Delay Line Register 4
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ACBDLR4_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odt3bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Delay select for the BDL on ODT[3]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_22 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odt2bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Delay select for the BDL on ODT[2]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odt1bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Delay select for the BDL on ODT[1]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odt0bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Delay select for the BDL on ODT[0]. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ACBDLR4_t
 *
 * Implemented by: 
 *      ACBDLR4
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      odt3bd                                    :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      odt2bd                                    :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      odt1bd                                    :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      odt0bd                                    :  6;
#else    /* Little Endian */
     unsigned      odt0bd                                    :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      odt1bd                                    :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      odt2bd                                    :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      odt3bd                                    :  6;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_ACBDLR4_t;

/*! @struct ncp_phy_ACBDLR5_t
 *  @brief null
 *  @details AC Bit Delay Line Register 5
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ACBDLR5_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cke3bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Delay select for the BDL on CKE[3]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_22 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cke2bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Delay select for the BDL on CKE[2]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cke1bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Delay select for the BDL on CKE[1]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cke0bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Delay select for the BDL on CKE[0]. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ACBDLR5_t
 *
 * Implemented by: 
 *      ACBDLR5
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      cke3bd                                    :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      cke2bd                                    :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      cke1bd                                    :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      cke0bd                                    :  6;
#else    /* Little Endian */
     unsigned      cke0bd                                    :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      cke1bd                                    :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      cke2bd                                    :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      cke3bd                                    :  6;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_ACBDLR5_t;

/*! @struct ncp_phy_ACBDLR6_t
 *  @brief null
 *  @details AC Bit Delay Line Register 6
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ACBDLR6_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param a03bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Delay select for the BDL on Address A[3]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_22 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param a02bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Delay select for the BDL on Address A[2]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param a01bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Delay select for the BDL on Address A[1]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param a00bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Delay select for the BDL on Address A[0]. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ACBDLR6_t
 *
 * Implemented by: 
 *      ACBDLR6
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      a03bd                                     :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      a02bd                                     :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      a01bd                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      a00bd                                     :  6;
#else    /* Little Endian */
     unsigned      a00bd                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      a01bd                                     :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      a02bd                                     :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      a03bd                                     :  6;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_ACBDLR6_t;

/*! @struct ncp_phy_ACBDLR7_t
 *  @brief null
 *  @details AC Bit Delay Line Register 7
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ACBDLR7_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param a07bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Delay select for the BDL on Address A[7]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_22 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param a06bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Delay select for the BDL on Address A[6]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param a05bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Delay select for the BDL on Address A[5]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param a04bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Delay select for the BDL on Address A[4]. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ACBDLR7_t
 *
 * Implemented by: 
 *      ACBDLR7
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      a07bd                                     :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      a06bd                                     :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      a05bd                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      a04bd                                     :  6;
#else    /* Little Endian */
     unsigned      a04bd                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      a05bd                                     :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      a06bd                                     :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      a07bd                                     :  6;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_ACBDLR7_t;

/*! @struct ncp_phy_ACBDLR8_t
 *  @brief null
 *  @details AC Bit Delay Line Register 8
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ACBDLR8_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param a11bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Delay select for the BDL on Address A[11]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_22 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param a10bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Delay select for the BDL on Address A[10]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param a09bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Delay select for the BDL on Address A[9]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param a08bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Delay select for the BDL on Address A[8]. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ACBDLR8_t
 *
 * Implemented by: 
 *      ACBDLR8
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      a11bd                                     :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      a10bd                                     :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      a09bd                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      a08bd                                     :  6;
#else    /* Little Endian */
     unsigned      a08bd                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      a09bd                                     :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      a10bd                                     :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      a11bd                                     :  6;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_ACBDLR8_t;

/*! @struct ncp_phy_ACBDLR9_t
 *  @brief null
 *  @details AC Bit Delay Line Register 9
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ACBDLR9_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param a15bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Delay select for the BDL on Address A[15]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_22 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param a14bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Delay select for the BDL on Address A[14]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param a13bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Delay select for the BDL on Address A[13]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param a12bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Delay select for the BDL on Address A[12]. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ACBDLR9_t
 *
 * Implemented by: 
 *      ACBDLR9
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      a15bd                                     :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      a14bd                                     :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      a13bd                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      a12bd                                     :  6;
#else    /* Little Endian */
     unsigned      a12bd                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      a13bd                                     :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      a14bd                                     :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      a15bd                                     :  6;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_ACBDLR9_t;

/*! @struct ncp_phy_ACBDLR10_t
 *  @brief null
 *  @details AC Bit Delay Line Register 10
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ACBDLR10_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cid2bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Delay select for the BDL on Chip ID CID[2]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_22 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cid1bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Delay select for the BDL on Chip ID CID[1]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cid0bd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Delay select for the BDL on Chip ID CID[0]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param acpddbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Delay select for the BDL on AC PDD. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ACBDLR10_t
 *
 * Implemented by: 
 *      ACBDLR10
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      cid2bd                                    :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      cid1bd                                    :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      cid0bd                                    :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      acpddbd                                   :  6;
#else    /* Little Endian */
     unsigned      acpddbd                                   :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      cid0bd                                    :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      cid1bd                                    :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      cid2bd                                    :  6;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_ACBDLR10_t;

/*! @struct ncp_phy_ACBDLR11_t
 *  @brief null
 *  @details AC Bit Delay Line Register 11
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ACBDLR11_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ACBDLR11_t
 *
 * Implemented by: 
 *      ACBDLR11
 */
 
typedef struct
{
     unsigned  int             reserved_31_0;
} ncp_phy_ACBDLR11_t;

/*! @struct ncp_phy_ACBDLR12_t
 *  @brief null
 *  @details AC Bit Delay Line Register 12
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ACBDLR12_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ACBDLR12_t
 *
 * Implemented by: 
 *      ACBDLR12
 */
 
typedef struct
{
     unsigned  int             reserved_31_0;
} ncp_phy_ACBDLR12_t;

/*! @struct ncp_phy_ACBDLR13_t
 *  @brief null
 *  @details AC Bit Delay Line Register 13
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ACBDLR13_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ACBDLR13_t
 *
 * Implemented by: 
 *      ACBDLR13
 */
 
typedef struct
{
     unsigned  int             reserved_31_0;
} ncp_phy_ACBDLR13_t;

/*! @struct ncp_phy_ACBDLR14_t
 *  @brief null
 *  @details AC Bit Delay Line Register 14
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ACBDLR14_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ACBDLR14_t
 *
 * Implemented by: 
 *      ACBDLR14
 */
 
typedef struct
{
     unsigned  int             reserved_31_0;
} ncp_phy_ACBDLR14_t;

/*! @struct ncp_phy_ACLCDLR_t
 *  @brief null
 *  @details AC Local Calibrated Delay Line Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ACLCDLR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_9 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param acd </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address/Command Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ACLCDLR_t
 *
 * Implemented by: 
 *      ACLCDLR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_9                             : 23;
     unsigned      acd                                       :  9;
#else    /* Little Endian */
     unsigned      acd                                       :  9;
     unsigned      reserved_31_9                             : 23;
#endif
} ncp_phy_ACLCDLR_t;

/*! @struct ncp_phy_ACMDLR0_t
 *  @brief null
 *  @details AC Master Delay Line Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ACMDLR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_25 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tprd </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Target Period. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_9 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param iprd </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Initial Period. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ACMDLR0_t
 *
 * Implemented by: 
 *      ACMDLR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_25                            :  7;
     unsigned      tprd                                      :  9;
     unsigned      reserved_15_9                             :  7;
     unsigned      iprd                                      :  9;
#else    /* Little Endian */
     unsigned      iprd                                      :  9;
     unsigned      reserved_15_9                             :  7;
     unsigned      tprd                                      :  9;
     unsigned      reserved_31_25                            :  7;
#endif
} ncp_phy_ACMDLR0_t;

/*! @struct ncp_phy_ACMDLR1_t
 *  @brief null
 *  @details AC Master Delay Line Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ACMDLR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_9 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mdld </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MDL Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ACMDLR1_t
 *
 * Implemented by: 
 *      ACMDLR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_9                             : 23;
     unsigned      mdld                                      :  9;
#else    /* Little Endian */
     unsigned      mdld                                      :  9;
     unsigned      reserved_31_9                             : 23;
#endif
} ncp_phy_ACMDLR1_t;

/*! @struct ncp_phy_ZQCR_t
 *  @brief null
 *  @details ZQ Impedance Control Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ZQCR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param zctrl_upper </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Bits 31 - 28 of ZCTRL bus going to PZCTRL cell (for
 *        D4MU IOs).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param force_zcal_vt_update </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> When set to 1b1, forces a ZCAL VT update to the impedance
 *        calibration FSM.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dis_non_lin_comp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Set to 1b0 to disable non-linear compensation for
 *        single ended termination.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pu_odt_only </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Enable pullup only ODT calibration for all segments. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param asym_drv_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Enable Asynmmetric drive strength calibration for
 *        all segments.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param iodlmt </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> IO VT Drift Limit. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param avgen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Averaging algorithm enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param avgmax </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Maximum number of averaging rounds to be used by averaging
 *        algorithm.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zcalt </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Impedance Calibration Type. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pgwait </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Programmable Wait. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zqpd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> ZQ Power Down. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param term_off </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Termination OFF. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ZQCR_t
 *
 * Implemented by: 
 *      ZQCR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      zctrl_upper                               :  4;
     unsigned      force_zcal_vt_update                      :  1;
     unsigned      dis_non_lin_comp                          :  1;
     unsigned      pu_odt_only                               :  1;
     unsigned      asym_drv_en                               :  1;
     unsigned      iodlmt                                    :  7;
     unsigned      avgen                                     :  1;
     unsigned      avgmax                                    :  2;
     unsigned      zcalt                                     :  3;
     unsigned      pgwait                                    :  3;
     unsigned      reserved_7_4                              :  4;
     unsigned      reserved_3                                :  1;
     unsigned      zqpd                                      :  1;
     unsigned      term_off                                  :  1;
     unsigned      reserved_0                                :  1;
#else    /* Little Endian */
     unsigned      reserved_0                                :  1;
     unsigned      term_off                                  :  1;
     unsigned      zqpd                                      :  1;
     unsigned      reserved_3                                :  1;
     unsigned      reserved_7_4                              :  4;
     unsigned      pgwait                                    :  3;
     unsigned      zcalt                                     :  3;
     unsigned      avgmax                                    :  2;
     unsigned      avgen                                     :  1;
     unsigned      iodlmt                                    :  7;
     unsigned      asym_drv_en                               :  1;
     unsigned      pu_odt_only                               :  1;
     unsigned      dis_non_lin_comp                          :  1;
     unsigned      force_zcal_vt_update                      :  1;
     unsigned      zctrl_upper                               :  4;
#endif
} ncp_phy_ZQCR_t;

/*! @struct ncp_phy_ZQ0PR_t
 *  @brief null
 *  @details ZQ n Impedance Control Program Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ZQ0PR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_28 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zctrl_upper </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Bits 31:28 of ZCTRL bus going to PZCTRL cell (for
 *        D4MU IOs).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pd_drv_adjust </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Pulldown drive strength adjustment. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pu_drv_adjust </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Pullup drive strength adjustment. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zprog_pu_odt_only </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Impedance Divide Ratio. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zprog_asym_drv_pd </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Impedance Divide Ratio. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zprog_asym_drv_pu </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Impedance Divide Ratio. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zqdiv </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Impedance Divide Ratio. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ZQ0PR_t
 *
 * Implemented by: 
 *      ZQ0PR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_28                            :  4;
     unsigned      zctrl_upper                               :  4;
     unsigned      pd_drv_adjust                             :  2;
     unsigned      pu_drv_adjust                             :  2;
     unsigned      zprog_pu_odt_only                         :  4;
     unsigned      zprog_asym_drv_pd                         :  4;
     unsigned      zprog_asym_drv_pu                         :  4;
     unsigned      zqdiv                                     :  8;
#else    /* Little Endian */
     unsigned      zqdiv                                     :  8;
     unsigned      zprog_asym_drv_pu                         :  4;
     unsigned      zprog_asym_drv_pd                         :  4;
     unsigned      zprog_pu_odt_only                         :  4;
     unsigned      pu_drv_adjust                             :  2;
     unsigned      pd_drv_adjust                             :  2;
     unsigned      zctrl_upper                               :  4;
     unsigned      reserved_31_28                            :  4;
#endif
} ncp_phy_ZQ0PR_t;

/*! @struct ncp_phy_ZQ0DR_t
 *  @brief null
 *  @details ZQ n Impedance Control Data Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ZQ0DR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param drv_zden </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Drive strength over-ride enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odt_zden </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Termination over-ride Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zsegbyp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Calibration segment bypass. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_28 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zdata </td>
 *     <td width="20%" align="center"> 28 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Impedance Controller Impedance Data: </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ZQ0DR_t
 *
 * Implemented by: 
 *      ZQ0DR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      drv_zden                                  :  1;
     unsigned      odt_zden                                  :  1;
     unsigned      zsegbyp                                   :  1;
     unsigned      reserved_28                               :  1;
     unsigned      zdata                                     : 28;
#else    /* Little Endian */
     unsigned      zdata                                     : 28;
     unsigned      reserved_28                               :  1;
     unsigned      zsegbyp                                   :  1;
     unsigned      odt_zden                                  :  1;
     unsigned      drv_zden                                  :  1;
#endif
} ncp_phy_ZQ0DR_t;

/*! @struct ncp_phy_ZQ0SR_t
 *  @brief null
 *  @details ZQ n Impedance Control Status Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ZQ0SR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_12 </td>
 *     <td width="20%" align="center"> 20 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pd_drv_sat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Pulldown drive strength code saturated due to drive
 *        strength adjustment setting in ZQnPR register.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pu_drv_sat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Pullup drive strength code saturated due to drive
 *        strength adjustment setting in ZQnPR register.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zdone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Impedance Calibration Done. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zerr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Impedance Calibration Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opu </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> On-die termination (ODT) pull-up calibration status. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opd </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> On-die termination (ODT) pull-down calibration status. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zpu </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Output impedance pull-up calibration status. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zpd </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Output impedance pull-down calibration status. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ZQ0SR_t
 *
 * Implemented by: 
 *      ZQ0SR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_12                            : 20;
     unsigned      pd_drv_sat                                :  1;
     unsigned      pu_drv_sat                                :  1;
     unsigned      zdone                                     :  1;
     unsigned      zerr                                      :  1;
     unsigned      opu                                       :  2;
     unsigned      opd                                       :  2;
     unsigned      zpu                                       :  2;
     unsigned      zpd                                       :  2;
#else    /* Little Endian */
     unsigned      zpd                                       :  2;
     unsigned      zpu                                       :  2;
     unsigned      opd                                       :  2;
     unsigned      opu                                       :  2;
     unsigned      zerr                                      :  1;
     unsigned      zdone                                     :  1;
     unsigned      pu_drv_sat                                :  1;
     unsigned      pd_drv_sat                                :  1;
     unsigned      reserved_31_12                            : 20;
#endif
} ncp_phy_ZQ0SR_t;

/*! @struct ncp_phy_ZQ1PR_t
 *  @brief null
 *  @details ZQ n Impedance Control Program Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ZQ1PR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_28 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zctrl_upper </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Bits 31:28 of ZCTRL bus going to PZCTRL cell (for
 *        D4MU IOs).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pd_drv_adjust </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Pulldown drive strength adjustment. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pu_drv_adjust </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Pullup drive strength adjustment. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zprog_pu_odt_only </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Impedance Divide Ratio. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zprog_asym_drv_pd </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Impedance Divide Ratio. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zprog_asym_drv_pu </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Impedance Divide Ratio. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zqdiv </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Impedance Divide Ratio. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ZQ1PR_t
 *
 * Implemented by: 
 *      ZQ1PR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_28                            :  4;
     unsigned      zctrl_upper                               :  4;
     unsigned      pd_drv_adjust                             :  2;
     unsigned      pu_drv_adjust                             :  2;
     unsigned      zprog_pu_odt_only                         :  4;
     unsigned      zprog_asym_drv_pd                         :  4;
     unsigned      zprog_asym_drv_pu                         :  4;
     unsigned      zqdiv                                     :  8;
#else    /* Little Endian */
     unsigned      zqdiv                                     :  8;
     unsigned      zprog_asym_drv_pu                         :  4;
     unsigned      zprog_asym_drv_pd                         :  4;
     unsigned      zprog_pu_odt_only                         :  4;
     unsigned      pu_drv_adjust                             :  2;
     unsigned      pd_drv_adjust                             :  2;
     unsigned      zctrl_upper                               :  4;
     unsigned      reserved_31_28                            :  4;
#endif
} ncp_phy_ZQ1PR_t;

/*! @struct ncp_phy_ZQ1DR_t
 *  @brief null
 *  @details ZQ n Impedance Control Data Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ZQ1DR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param drv_zden </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Drive strength over-ride enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odt_zden </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Termination over-ride Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zsegbyp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Calibration segment bypass. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_28 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zdata </td>
 *     <td width="20%" align="center"> 28 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Impedance Controller Impedance Data: </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ZQ1DR_t
 *
 * Implemented by: 
 *      ZQ1DR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      drv_zden                                  :  1;
     unsigned      odt_zden                                  :  1;
     unsigned      zsegbyp                                   :  1;
     unsigned      reserved_28                               :  1;
     unsigned      zdata                                     : 28;
#else    /* Little Endian */
     unsigned      zdata                                     : 28;
     unsigned      reserved_28                               :  1;
     unsigned      zsegbyp                                   :  1;
     unsigned      odt_zden                                  :  1;
     unsigned      drv_zden                                  :  1;
#endif
} ncp_phy_ZQ1DR_t;

/*! @struct ncp_phy_ZQ1SR_t
 *  @brief null
 *  @details ZQ n Impedance Control Status Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ZQ1SR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_12 </td>
 *     <td width="20%" align="center"> 20 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pd_drv_sat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Pulldown drive strength code saturated due to drive
 *        strength adjustment setting in ZQnPR register.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pu_drv_sat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Pullup drive strength code saturated due to drive
 *        strength adjustment setting in ZQnPR register.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zdone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Impedance Calibration Done. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zerr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Impedance Calibration Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opu </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> On-die termination (ODT) pull-up calibration status. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opd </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> On-die termination (ODT) pull-down calibration status. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zpu </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Output impedance pull-up calibration status. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zpd </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Output impedance pull-down calibration status. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ZQ1SR_t
 *
 * Implemented by: 
 *      ZQ1SR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_12                            : 20;
     unsigned      pd_drv_sat                                :  1;
     unsigned      pu_drv_sat                                :  1;
     unsigned      zdone                                     :  1;
     unsigned      zerr                                      :  1;
     unsigned      opu                                       :  2;
     unsigned      opd                                       :  2;
     unsigned      zpu                                       :  2;
     unsigned      zpd                                       :  2;
#else    /* Little Endian */
     unsigned      zpd                                       :  2;
     unsigned      zpu                                       :  2;
     unsigned      opd                                       :  2;
     unsigned      opu                                       :  2;
     unsigned      zerr                                      :  1;
     unsigned      zdone                                     :  1;
     unsigned      pu_drv_sat                                :  1;
     unsigned      pd_drv_sat                                :  1;
     unsigned      reserved_31_12                            : 20;
#endif
} ncp_phy_ZQ1SR_t;

/*! @struct ncp_phy_ZQ2PR_t
 *  @brief null
 *  @details ZQ n Impedance Control Program Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ZQ2PR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_28 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zctrl_upper </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Bits 31:28 of ZCTRL bus going to PZCTRL cell (for
 *        D4MU IOs).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pd_drv_adjust </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Pulldown drive strength adjustment. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pu_drv_adjust </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Pullup drive strength adjustment. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zprog_pu_odt_only </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Impedance Divide Ratio. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zprog_asym_drv_pd </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Impedance Divide Ratio. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zprog_asym_drv_pu </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Impedance Divide Ratio. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zqdiv </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Impedance Divide Ratio. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ZQ2PR_t
 *
 * Implemented by: 
 *      ZQ2PR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_28                            :  4;
     unsigned      zctrl_upper                               :  4;
     unsigned      pd_drv_adjust                             :  2;
     unsigned      pu_drv_adjust                             :  2;
     unsigned      zprog_pu_odt_only                         :  4;
     unsigned      zprog_asym_drv_pd                         :  4;
     unsigned      zprog_asym_drv_pu                         :  4;
     unsigned      zqdiv                                     :  8;
#else    /* Little Endian */
     unsigned      zqdiv                                     :  8;
     unsigned      zprog_asym_drv_pu                         :  4;
     unsigned      zprog_asym_drv_pd                         :  4;
     unsigned      zprog_pu_odt_only                         :  4;
     unsigned      pu_drv_adjust                             :  2;
     unsigned      pd_drv_adjust                             :  2;
     unsigned      zctrl_upper                               :  4;
     unsigned      reserved_31_28                            :  4;
#endif
} ncp_phy_ZQ2PR_t;

/*! @struct ncp_phy_ZQ2DR_t
 *  @brief null
 *  @details ZQ n Impedance Control Data Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ZQ2DR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param drv_zden </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Drive strength over-ride enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odt_zden </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Termination over-ride Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zsegbyp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Calibration segment bypass. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_28 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zdata </td>
 *     <td width="20%" align="center"> 28 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Impedance Controller Impedance Data: </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ZQ2DR_t
 *
 * Implemented by: 
 *      ZQ2DR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      drv_zden                                  :  1;
     unsigned      odt_zden                                  :  1;
     unsigned      zsegbyp                                   :  1;
     unsigned      reserved_28                               :  1;
     unsigned      zdata                                     : 28;
#else    /* Little Endian */
     unsigned      zdata                                     : 28;
     unsigned      reserved_28                               :  1;
     unsigned      zsegbyp                                   :  1;
     unsigned      odt_zden                                  :  1;
     unsigned      drv_zden                                  :  1;
#endif
} ncp_phy_ZQ2DR_t;

/*! @struct ncp_phy_ZQ2SR_t
 *  @brief null
 *  @details ZQ n Impedance Control Status Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ZQ2SR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_12 </td>
 *     <td width="20%" align="center"> 20 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pd_drv_sat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Pulldown drive strength code saturated due to drive
 *        strength adjustment setting in ZQnPR register.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pu_drv_sat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Pullup drive strength code saturated due to drive
 *        strength adjustment setting in ZQnPR register.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zdone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Impedance Calibration Done. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zerr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Impedance Calibration Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opu </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> On-die termination (ODT) pull-up calibration status. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opd </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> On-die termination (ODT) pull-down calibration status. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zpu </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Output impedance pull-up calibration status. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zpd </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Output impedance pull-down calibration status. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ZQ2SR_t
 *
 * Implemented by: 
 *      ZQ2SR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_12                            : 20;
     unsigned      pd_drv_sat                                :  1;
     unsigned      pu_drv_sat                                :  1;
     unsigned      zdone                                     :  1;
     unsigned      zerr                                      :  1;
     unsigned      opu                                       :  2;
     unsigned      opd                                       :  2;
     unsigned      zpu                                       :  2;
     unsigned      zpd                                       :  2;
#else    /* Little Endian */
     unsigned      zpd                                       :  2;
     unsigned      zpu                                       :  2;
     unsigned      opd                                       :  2;
     unsigned      opu                                       :  2;
     unsigned      zerr                                      :  1;
     unsigned      zdone                                     :  1;
     unsigned      pu_drv_sat                                :  1;
     unsigned      pd_drv_sat                                :  1;
     unsigned      reserved_31_12                            : 20;
#endif
} ncp_phy_ZQ2SR_t;

/*! @struct ncp_phy_ZQ3PR_t
 *  @brief null
 *  @details ZQ n Impedance Control Program Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ZQ3PR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_28 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zctrl_upper </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Bits 31:28 of ZCTRL bus going to PZCTRL cell (for
 *        D4MU IOs).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pd_drv_adjust </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Pulldown drive strength adjustment. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pu_drv_adjust </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Pullup drive strength adjustment. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zprog_pu_odt_only </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Impedance Divide Ratio. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zprog_asym_drv_pd </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Impedance Divide Ratio. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zprog_asym_drv_pu </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Impedance Divide Ratio. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zqdiv </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Impedance Divide Ratio. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ZQ3PR_t
 *
 * Implemented by: 
 *      ZQ3PR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_28                            :  4;
     unsigned      zctrl_upper                               :  4;
     unsigned      pd_drv_adjust                             :  2;
     unsigned      pu_drv_adjust                             :  2;
     unsigned      zprog_pu_odt_only                         :  4;
     unsigned      zprog_asym_drv_pd                         :  4;
     unsigned      zprog_asym_drv_pu                         :  4;
     unsigned      zqdiv                                     :  8;
#else    /* Little Endian */
     unsigned      zqdiv                                     :  8;
     unsigned      zprog_asym_drv_pu                         :  4;
     unsigned      zprog_asym_drv_pd                         :  4;
     unsigned      zprog_pu_odt_only                         :  4;
     unsigned      pu_drv_adjust                             :  2;
     unsigned      pd_drv_adjust                             :  2;
     unsigned      zctrl_upper                               :  4;
     unsigned      reserved_31_28                            :  4;
#endif
} ncp_phy_ZQ3PR_t;

/*! @struct ncp_phy_ZQ3DR_t
 *  @brief null
 *  @details ZQ n Impedance Control Data Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ZQ3DR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param drv_zden </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Drive strength over-ride enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odt_zden </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Termination over-ride Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zsegbyp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Calibration segment bypass. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_28 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zdata </td>
 *     <td width="20%" align="center"> 28 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Impedance Controller Impedance Data: </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ZQ3DR_t
 *
 * Implemented by: 
 *      ZQ3DR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      drv_zden                                  :  1;
     unsigned      odt_zden                                  :  1;
     unsigned      zsegbyp                                   :  1;
     unsigned      reserved_28                               :  1;
     unsigned      zdata                                     : 28;
#else    /* Little Endian */
     unsigned      zdata                                     : 28;
     unsigned      reserved_28                               :  1;
     unsigned      zsegbyp                                   :  1;
     unsigned      odt_zden                                  :  1;
     unsigned      drv_zden                                  :  1;
#endif
} ncp_phy_ZQ3DR_t;

/*! @struct ncp_phy_ZQ3SR_t
 *  @brief null
 *  @details ZQ n Impedance Control Status Register
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_ZQ3SR_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_12 </td>
 *     <td width="20%" align="center"> 20 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved. Return zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pd_drv_sat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Pulldown drive strength code saturated due to drive
 *        strength adjustment setting in ZQnPR register.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pu_drv_sat </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Pullup drive strength code saturated due to drive
 *        strength adjustment setting in ZQnPR register.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zdone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Impedance Calibration Done. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zerr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Impedance Calibration Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opu </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> On-die termination (ODT) pull-up calibration status. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param opd </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> On-die termination (ODT) pull-down calibration status. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zpu </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Output impedance pull-up calibration status. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zpd </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Output impedance pull-down calibration status. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_ZQ3SR_t
 *
 * Implemented by: 
 *      ZQ3SR
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_12                            : 20;
     unsigned      pd_drv_sat                                :  1;
     unsigned      pu_drv_sat                                :  1;
     unsigned      zdone                                     :  1;
     unsigned      zerr                                      :  1;
     unsigned      opu                                       :  2;
     unsigned      opd                                       :  2;
     unsigned      zpu                                       :  2;
     unsigned      zpd                                       :  2;
#else    /* Little Endian */
     unsigned      zpd                                       :  2;
     unsigned      zpu                                       :  2;
     unsigned      opd                                       :  2;
     unsigned      opu                                       :  2;
     unsigned      zerr                                      :  1;
     unsigned      zdone                                     :  1;
     unsigned      pu_drv_sat                                :  1;
     unsigned      pd_drv_sat                                :  1;
     unsigned      reserved_31_12                            : 20;
#endif
} ncp_phy_ZQ3SR_t;

/*! @struct ncp_phy_DX0GCR0_t
 *  @brief null
 *  @details DATX8 n General Configuration Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0GCR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param calbyp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Calibration Bypass. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mdlen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Master Delay Line Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_29_24 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved. Returns zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rddly </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Number of Cycles (in terms of ctl_clk) to generate
 *        ctl_dx_get_static_rd input for the respective bypte
 *        lane of the PHY.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pllbyp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> PLL Bypass. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gshift </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Gear Shift. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pllpd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> PLL Power Down. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pllrst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> PLL Rest. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqsnsepdr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> DQSNSE Power Down Receiver. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqssepdr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> DQSSE Power Down Receiver. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rttoal </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> RTT On Additive Latency. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rttoh </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> RTT Output Hold. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_8_7 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqsrpd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> DQSR Power Down. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqsgpdr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> DQSG Power Down Receiver. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqsgpdd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> DQSG Power Down Driver. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqsgodt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> DQSG On-Die Termination. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqsgoe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> DQSG Output Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxiom </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Data I/O Mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data Byte Enable. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0GCR0_t
 *
 * Implemented by: 
 *      DX0GCR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      calbyp                                    :  1;
     unsigned      mdlen                                     :  1;
     unsigned      reserved_29_24                            :  6;
     unsigned      rddly                                     :  4;
     unsigned      pllbyp                                    :  1;
     unsigned      gshift                                    :  1;
     unsigned      pllpd                                     :  1;
     unsigned      pllrst                                    :  1;
     unsigned      reserved_15_14                            :  2;
     unsigned      dqsnsepdr                                 :  1;
     unsigned      dqssepdr                                  :  1;
     unsigned      rttoal                                    :  1;
     unsigned      rttoh                                     :  2;
     unsigned      reserved_8_7                              :  2;
     unsigned      dqsrpd                                    :  1;
     unsigned      dqsgpdr                                   :  1;
     unsigned      dqsgpdd                                   :  1;
     unsigned      dqsgodt                                   :  1;
     unsigned      dqsgoe                                    :  1;
     unsigned      dxiom                                     :  1;
     unsigned      dxen                                      :  1;
#else    /* Little Endian */
     unsigned      dxen                                      :  1;
     unsigned      dxiom                                     :  1;
     unsigned      dqsgoe                                    :  1;
     unsigned      dqsgodt                                   :  1;
     unsigned      dqsgpdd                                   :  1;
     unsigned      dqsgpdr                                   :  1;
     unsigned      dqsrpd                                    :  1;
     unsigned      reserved_8_7                              :  2;
     unsigned      rttoh                                     :  2;
     unsigned      rttoal                                    :  1;
     unsigned      dqssepdr                                  :  1;
     unsigned      dqsnsepdr                                 :  1;
     unsigned      reserved_15_14                            :  2;
     unsigned      pllrst                                    :  1;
     unsigned      pllpd                                     :  1;
     unsigned      gshift                                    :  1;
     unsigned      pllbyp                                    :  1;
     unsigned      rddly                                     :  4;
     unsigned      reserved_29_24                            :  6;
     unsigned      mdlen                                     :  1;
     unsigned      calbyp                                    :  1;
#endif
} ncp_phy_DX0GCR0_t;

/*! @struct ncp_phy_DX0GCR1_t
 *  @brief null
 *  @details DATX8 n General Configuration Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0GCR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dxpdrmode </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enables the PDR mode values for DQ[7:0]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxpddmode </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enables the PDD mode values for DQ[7:0]. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0GCR1_t
 *
 * Implemented by: 
 *      DX0GCR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      dxpdrmode                                 : 16;
     unsigned      dxpddmode                                 : 16;
#else    /* Little Endian */
     unsigned      dxpddmode                                 : 16;
     unsigned      dxpdrmode                                 : 16;
#endif
} ncp_phy_DX0GCR1_t;

/*! @struct ncp_phy_DX0GCR2_t
 *  @brief null
 *  @details DATX8 n General Configuration Register 2
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0GCR2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dxoemode </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enables the OE mode values for DQ[7:0]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxtemode </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enables the TE (ODT) mode values for DQ[7:0]. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0GCR2_t
 *
 * Implemented by: 
 *      DX0GCR2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      dxoemode                                  : 16;
     unsigned      dxtemode                                  : 16;
#else    /* Little Endian */
     unsigned      dxtemode                                  : 16;
     unsigned      dxoemode                                  : 16;
#endif
} ncp_phy_DX0GCR2_t;

/*! @struct ncp_phy_DX0GCR3_t
 *  @brief null
 *  @details DATX8 n General Configuration Register 3
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0GCR3_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdbvt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Read Data BDL VT Compensation. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wdbvt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Write Data BDL VT Compensation. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rglvt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Read DQS Gating LCDL Delay VT Compensation. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Read DQS LCDL Delay VT Compensation. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wdlvt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Write DQ LCDL Delay VT Compensation. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wllvt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Write Leveling LCDL Delay VT Compensation. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dmoemode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Enables the OE mode values for DM. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dmtemode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Enables the TE mode values for DM. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dmpdrmode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Enables the PDR mode values for DM. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dmpddmode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enables the PDD mode values for DM. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dsoemode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Enables the OE mode values for DQS. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dstemode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Enables the TE mode values for DQS. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dspdrmode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Enables the PDR mode values for DQS. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dspddmode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enables the PDD mode values for DQS. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0GCR3_t
 *
 * Implemented by: 
 *      DX0GCR3
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      rdbvt                                     :  1;
     unsigned      wdbvt                                     :  1;
     unsigned      rglvt                                     :  1;
     unsigned      rdlvt                                     :  1;
     unsigned      wdlvt                                     :  1;
     unsigned      wllvt                                     :  1;
     unsigned      reserved_23_16                            :  8;
     unsigned      dmoemode                                  :  2;
     unsigned      dmtemode                                  :  2;
     unsigned      dmpdrmode                                 :  2;
     unsigned      dmpddmode                                 :  2;
     unsigned      dsoemode                                  :  2;
     unsigned      dstemode                                  :  2;
     unsigned      dspdrmode                                 :  2;
     unsigned      dspddmode                                 :  2;
#else    /* Little Endian */
     unsigned      dspddmode                                 :  2;
     unsigned      dspdrmode                                 :  2;
     unsigned      dstemode                                  :  2;
     unsigned      dsoemode                                  :  2;
     unsigned      dmpddmode                                 :  2;
     unsigned      dmpdrmode                                 :  2;
     unsigned      dmtemode                                  :  2;
     unsigned      dmoemode                                  :  2;
     unsigned      reserved_23_16                            :  8;
     unsigned      wllvt                                     :  1;
     unsigned      wdlvt                                     :  1;
     unsigned      rdlvt                                     :  1;
     unsigned      rglvt                                     :  1;
     unsigned      wdbvt                                     :  1;
     unsigned      rdbvt                                     :  1;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_DX0GCR3_t;

/*! @struct ncp_phy_DX0GCR4_t
 *  @brief null
 *  @details DATX8 n General Configuration Register 4
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0GCR4_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dxrefiom </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Byte lane VREF IOM (Used only by D4MU IOs) </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxrefpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Byte Lane VREF Pad Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxrefeen </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Byte Lane Internal VREF Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxrefsen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Byte Lane Single-End VREF Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_24_22 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxrefesel </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Byte Lane External VREF Select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxrefssel </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Byte Lane Single-End VREF Select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxrefien </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> VREF Enable control for DQ IO (Single Ended) buffers
 *        of a byte lane.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxrefimon </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> VRMON control for DQ IO (Single Ended) buffers of
 *        a byte lane.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0GCR4_t
 *
 * Implemented by: 
 *      DX0GCR4
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      dxrefiom                                  :  3;
     unsigned      dxrefpen                                  :  1;
     unsigned      dxrefeen                                  :  2;
     unsigned      dxrefsen                                  :  1;
     unsigned      reserved_24_22                            :  3;
     unsigned      dxrefesel                                 :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dxrefssel                                 :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dxrefien                                  :  4;
     unsigned      dxrefimon                                 :  2;
#else    /* Little Endian */
     unsigned      dxrefimon                                 :  2;
     unsigned      dxrefien                                  :  4;
     unsigned      reserved_7_6                              :  2;
     unsigned      dxrefssel                                 :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dxrefesel                                 :  6;
     unsigned      reserved_24_22                            :  3;
     unsigned      dxrefsen                                  :  1;
     unsigned      dxrefeen                                  :  2;
     unsigned      dxrefpen                                  :  1;
     unsigned      dxrefiom                                  :  3;
#endif
} ncp_phy_DX0GCR4_t;

/*! @struct ncp_phy_DX0GCR5_t
 *  @brief null
 *  @details DATX8 n General Configuration Register 5
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0GCR5_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxrefiselr3 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Byte Lane internal VREF Select for Rank3. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_22 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxrefiselr2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Byte Lane internal VREF Select for Rank2. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxrefiselr1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Byte Lane internal VREF Select for Rank 1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxrefiselr0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Byte Lane internal VREF Select for Rank0. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0GCR5_t
 *
 * Implemented by: 
 *      DX0GCR5
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      dxrefiselr3                               :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      dxrefiselr2                               :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dxrefiselr1                               :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dxrefiselr0                               :  6;
#else    /* Little Endian */
     unsigned      dxrefiselr0                               :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dxrefiselr1                               :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dxrefiselr2                               :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      dxrefiselr3                               :  6;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_DX0GCR5_t;

/*! @struct ncp_phy_DX0GCR6_t
 *  @brief null
 *  @details DATX8 n General Configuration Register 6
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0GCR6_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxdqvrefr3 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> DRAM DQ VREF Select for Rank3. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_22 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxdqvrefr2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DRAM DQ VREF Select for Rank2. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxdqvrefr1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DRAM DQ VREF Select for Rank1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxdqvrefr0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM DQ VREF Select for Rank0. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0GCR6_t
 *
 * Implemented by: 
 *      DX0GCR6
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      dxdqvrefr3                                :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      dxdqvrefr2                                :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dxdqvrefr1                                :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dxdqvrefr0                                :  6;
#else    /* Little Endian */
     unsigned      dxdqvrefr0                                :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dxdqvrefr1                                :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dxdqvrefr2                                :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      dxdqvrefr3                                :  6;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_DX0GCR6_t;

/*! @struct ncp_phy_DX0GCR7_t
 *  @brief null
 *  @details DATX8 n General Configuration Register 7
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0GCR7_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0GCR7_t
 *
 * Implemented by: 
 *      DX0GCR7
 */
 
typedef struct
{
     unsigned  int             reserved_31_0;
} ncp_phy_DX0GCR7_t;

/*! @struct ncp_phy_DX0GCR8_t
 *  @brief null
 *  @details DATX8 n General Configuration Register 8
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0GCR8_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0GCR8_t
 *
 * Implemented by: 
 *      DX0GCR8
 */
 
typedef struct
{
     unsigned  int             reserved_31_0;
} ncp_phy_DX0GCR8_t;

/*! @struct ncp_phy_DX0GCR9_t
 *  @brief null
 *  @details DATX8 n General Configuration Register 9
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0GCR9_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0GCR9_t
 *
 * Implemented by: 
 *      DX0GCR9
 */
 
typedef struct
{
     unsigned  int             reserved_31_0;
} ncp_phy_DX0GCR9_t;

/*! @struct ncp_phy_DX0BDLR0_t
 *  @brief null
 *  @details DATX8 n Bit Delay Line Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0BDLR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq3wbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> DQ3 Write Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_22 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq2wbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DQ2 Write Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq1wbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DQ1 Write Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq0wbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DQ0 Write Bit Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0BDLR0_t
 *
 * Implemented by: 
 *      DX0BDLR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      dq3wbd                                    :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      dq2wbd                                    :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dq1wbd                                    :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dq0wbd                                    :  6;
#else    /* Little Endian */
     unsigned      dq0wbd                                    :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dq1wbd                                    :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dq2wbd                                    :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      dq3wbd                                    :  6;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_DX0BDLR0_t;

/*! @struct ncp_phy_DX0BDLR1_t
 *  @brief null
 *  @details DATX8 n Bit Delay Line Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0BDLR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq7wbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> DQ7 Write Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_22 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq6wbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DQ6 Write Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq5wbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DQ5 Write Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq4wbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DQ4 Write Bit Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0BDLR1_t
 *
 * Implemented by: 
 *      DX0BDLR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      dq7wbd                                    :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      dq6wbd                                    :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dq5wbd                                    :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dq4wbd                                    :  6;
#else    /* Little Endian */
     unsigned      dq4wbd                                    :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dq5wbd                                    :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dq6wbd                                    :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      dq7wbd                                    :  6;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_DX0BDLR1_t;

/*! @struct ncp_phy_DX0BDLR2_t
 *  @brief null
 *  @details DATX8 n Bit Delay Line Register 2
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0BDLR2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_22 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dsoebd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DQS/DM/DQ Output Enable Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dswbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DQS Write Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dmwbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DM Write Bit Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0BDLR2_t
 *
 * Implemented by: 
 *      DX0BDLR2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_22                            : 10;
     unsigned      dsoebd                                    :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dswbd                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dmwbd                                     :  6;
#else    /* Little Endian */
     unsigned      dmwbd                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dswbd                                     :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dsoebd                                    :  6;
     unsigned      reserved_31_22                            : 10;
#endif
} ncp_phy_DX0BDLR2_t;

/*! @struct ncp_phy_DX0BDLR3_t
 *  @brief null
 *  @details DATX8 n Bit Delay Line Register 3
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0BDLR3_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq3rbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> DQ3 Read Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_22 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq2rbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DQ2 Read Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq1rbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DQ1 Read Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq0rbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DQ0 Read Bit Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0BDLR3_t
 *
 * Implemented by: 
 *      DX0BDLR3
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      dq3rbd                                    :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      dq2rbd                                    :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dq1rbd                                    :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dq0rbd                                    :  6;
#else    /* Little Endian */
     unsigned      dq0rbd                                    :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dq1rbd                                    :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dq2rbd                                    :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      dq3rbd                                    :  6;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_DX0BDLR3_t;

/*! @struct ncp_phy_DX0BDLR4_t
 *  @brief null
 *  @details DATX8 n Bit Delay Line Register 4
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0BDLR4_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq7rbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> DQ7 Read Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_22 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq6rbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DQ6 Read Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq5rbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DQ5 Read Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq4rbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DQ4 Read Bit Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0BDLR4_t
 *
 * Implemented by: 
 *      DX0BDLR4
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      dq7rbd                                    :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      dq6rbd                                    :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dq5rbd                                    :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dq4rbd                                    :  6;
#else    /* Little Endian */
     unsigned      dq4rbd                                    :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dq5rbd                                    :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dq6rbd                                    :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      dq7rbd                                    :  6;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_DX0BDLR4_t;

/*! @struct ncp_phy_DX0BDLR5_t
 *  @brief null
 *  @details DATX8 n Bit Delay Line Register 5
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0BDLR5_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_22 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dsnrbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DQSN Read Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dsrbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DQS Read Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dmrbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DM Read Bit Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0BDLR5_t
 *
 * Implemented by: 
 *      DX0BDLR5
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_22                            : 10;
     unsigned      dsnrbd                                    :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dsrbd                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dmrbd                                     :  6;
#else    /* Little Endian */
     unsigned      dmrbd                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dsrbd                                     :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dsnrbd                                    :  6;
     unsigned      reserved_31_22                            : 10;
#endif
} ncp_phy_DX0BDLR5_t;

/*! @struct ncp_phy_DX0BDLR6_t
 *  @brief null
 *  @details DATX8 n Bit Delay Line Register 6
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0BDLR6_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_22 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param terbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Termination Enable Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pdrbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Power down receiver Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pddbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Power down driver Bit Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0BDLR6_t
 *
 * Implemented by: 
 *      DX0BDLR6
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_22                            : 10;
     unsigned      terbd                                     :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      pdrbd                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      pddbd                                     :  6;
#else    /* Little Endian */
     unsigned      pddbd                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      pdrbd                                     :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      terbd                                     :  6;
     unsigned      reserved_31_22                            : 10;
#endif
} ncp_phy_DX0BDLR6_t;

/*! @struct ncp_phy_DX0BDLR7_t
 *  @brief null
 *  @details DATX8 n Bit Delay Line Register 7
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0BDLR7_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0BDLR7_t
 *
 * Implemented by: 
 *      DX0BDLR7
 */
 
typedef struct
{
     unsigned  int             reserved_31_0;
} ncp_phy_DX0BDLR7_t;

/*! @struct ncp_phy_DX0BDLR8_t
 *  @brief null
 *  @details DATX8 n Bit Delay Line Register 8
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0BDLR8_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0BDLR8_t
 *
 * Implemented by: 
 *      DX0BDLR8
 */
 
typedef struct
{
     unsigned  int             reserved_31_0;
} ncp_phy_DX0BDLR8_t;

/*! @struct ncp_phy_DX0BDLR9_t
 *  @brief null
 *  @details DATX8 n Bit Delay Line Register 9
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0BDLR9_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0BDLR9_t
 *
 * Implemented by: 
 *      DX0BDLR9
 */
 
typedef struct
{
     unsigned  int             reserved_31_0;
} ncp_phy_DX0BDLR9_t;

/*! @struct ncp_phy_DX0LCDLR0_t
 *  @brief null
 *  @details DATX8 n Local Calibrated Delay Line Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0LCDLR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_9 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wld </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Write Leveling Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0LCDLR0_t
 *
 * Implemented by: 
 *      DX0LCDLR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_9                             : 23;
     unsigned      wld                                       :  9;
#else    /* Little Endian */
     unsigned      wld                                       :  9;
     unsigned      reserved_31_9                             : 23;
#endif
} ncp_phy_DX0LCDLR0_t;

/*! @struct ncp_phy_DX0LCDLR1_t
 *  @brief null
 *  @details DATX8 n Local Calibrated Delay Line Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0LCDLR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_9 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wdqd </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Write Data Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0LCDLR1_t
 *
 * Implemented by: 
 *      DX0LCDLR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_9                             : 23;
     unsigned      wdqd                                      :  9;
#else    /* Little Endian */
     unsigned      wdqd                                      :  9;
     unsigned      reserved_31_9                             : 23;
#endif
} ncp_phy_DX0LCDLR1_t;

/*! @struct ncp_phy_DX0LCDLR2_t
 *  @brief null
 *  @details DATX8 n Local Calibrated Delay Line Register 2
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0LCDLR2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_9 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqsgd </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Read DQS Gating Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0LCDLR2_t
 *
 * Implemented by: 
 *      DX0LCDLR2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_9                             : 23;
     unsigned      dqsgd                                     :  9;
#else    /* Little Endian */
     unsigned      dqsgd                                     :  9;
     unsigned      reserved_31_9                             : 23;
#endif
} ncp_phy_DX0LCDLR2_t;

/*! @struct ncp_phy_DX0LCDLR3_t
 *  @brief null
 *  @details DATX8 n Local Calibrated Delay Line Register 3
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0LCDLR3_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_9 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdqsd </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Read DQS Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0LCDLR3_t
 *
 * Implemented by: 
 *      DX0LCDLR3
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_9                             : 23;
     unsigned      rdqsd                                     :  9;
#else    /* Little Endian */
     unsigned      rdqsd                                     :  9;
     unsigned      reserved_31_9                             : 23;
#endif
} ncp_phy_DX0LCDLR3_t;

/*! @struct ncp_phy_DX0LCDLR4_t
 *  @brief null
 *  @details DATX8 n Local Calibrated Delay Line Register 4
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0LCDLR4_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_9 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdqsnd </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Read DQSN Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0LCDLR4_t
 *
 * Implemented by: 
 *      DX0LCDLR4
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_9                             : 23;
     unsigned      rdqsnd                                    :  9;
#else    /* Little Endian */
     unsigned      rdqsnd                                    :  9;
     unsigned      reserved_31_9                             : 23;
#endif
} ncp_phy_DX0LCDLR4_t;

/*! @struct ncp_phy_DX0LCDLR5_t
 *  @brief null
 *  @details DATX8 n Local Calibrated Delay Line Register 5
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0LCDLR5_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_9 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqsgsd </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DQS Gating Status Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0LCDLR5_t
 *
 * Implemented by: 
 *      DX0LCDLR5
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_9                             : 23;
     unsigned      dqsgsd                                    :  9;
#else    /* Little Endian */
     unsigned      dqsgsd                                    :  9;
     unsigned      reserved_31_9                             : 23;
#endif
} ncp_phy_DX0LCDLR5_t;

/*! @struct ncp_phy_DX0MDLR0_t
 *  @brief null
 *  @details DATX8 n Master Delay Line Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0MDLR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_25 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tprd </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Target Period. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_9 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param iprd </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Initial Period. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0MDLR0_t
 *
 * Implemented by: 
 *      DX0MDLR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_25                            :  7;
     unsigned      tprd                                      :  9;
     unsigned      reserved_15_9                             :  7;
     unsigned      iprd                                      :  9;
#else    /* Little Endian */
     unsigned      iprd                                      :  9;
     unsigned      reserved_15_9                             :  7;
     unsigned      tprd                                      :  9;
     unsigned      reserved_31_25                            :  7;
#endif
} ncp_phy_DX0MDLR0_t;

/*! @struct ncp_phy_DX0MDLR1_t
 *  @brief null
 *  @details DATX8 n Master Delay Line Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0MDLR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_9 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mdld </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MDL Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0MDLR1_t
 *
 * Implemented by: 
 *      DX0MDLR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_9                             : 23;
     unsigned      mdld                                      :  9;
#else    /* Little Endian */
     unsigned      mdld                                      :  9;
     unsigned      reserved_31_9                             : 23;
#endif
} ncp_phy_DX0MDLR1_t;

/*! @struct ncp_phy_DX0GTR0_t
 *  @brief null
 *  @details DATX8 n General Timing Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0GTR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_20 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wlsl </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Write Leveling System Latency. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dgsl </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DQS Gating System Latency. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0GTR0_t
 *
 * Implemented by: 
 *      DX0GTR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_20                            : 12;
     unsigned      wlsl                                      :  4;
     unsigned      reserved_15_5                             : 11;
     unsigned      dgsl                                      :  5;
#else    /* Little Endian */
     unsigned      dgsl                                      :  5;
     unsigned      reserved_15_5                             : 11;
     unsigned      wlsl                                      :  4;
     unsigned      reserved_31_20                            : 12;
#endif
} ncp_phy_DX0GTR0_t;

/*! @struct ncp_phy_DX0RSR0_t
 *  @brief null
 *  @details DATX8 n Rank Status Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0RSR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param qsgerr </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DQS Gate Training Error. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0RSR0_t
 *
 * Implemented by: 
 *      DX0RSR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_16                            : 16;
     unsigned      qsgerr                                    : 16;
#else    /* Little Endian */
     unsigned      qsgerr                                    : 16;
     unsigned      reserved_31_16                            : 16;
#endif
} ncp_phy_DX0RSR0_t;

/*! @struct ncp_phy_DX0RSR1_t
 *  @brief null
 *  @details DATX8 n Rank Status Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0RSR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvlerr </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Read Leveling Error. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0RSR1_t
 *
 * Implemented by: 
 *      DX0RSR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_16                            : 16;
     unsigned      rdlvlerr                                  : 16;
#else    /* Little Endian */
     unsigned      rdlvlerr                                  : 16;
     unsigned      reserved_31_16                            : 16;
#endif
} ncp_phy_DX0RSR1_t;

/*! @struct ncp_phy_DX0RSR2_t
 *  @brief null
 *  @details DATX8 n Rank Status Register 2
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0RSR2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wlawn </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Write Latency Adjustment (DQS off on some DQ lines)
 *        Warning.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0RSR2_t
 *
 * Implemented by: 
 *      DX0RSR2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_16                            : 16;
     unsigned      wlawn                                     : 16;
#else    /* Little Endian */
     unsigned      wlawn                                     : 16;
     unsigned      reserved_31_16                            : 16;
#endif
} ncp_phy_DX0RSR2_t;

/*! @struct ncp_phy_DX0RSR3_t
 *  @brief null
 *  @details DATX8 n Rank Status Register 3
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0RSR3_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wlaerr </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Write Leveling Adjustment Error. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0RSR3_t
 *
 * Implemented by: 
 *      DX0RSR3
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_16                            : 16;
     unsigned      wlaerr                                    : 16;
#else    /* Little Endian */
     unsigned      wlaerr                                    : 16;
     unsigned      reserved_31_16                            : 16;
#endif
} ncp_phy_DX0RSR3_t;

/*! @struct ncp_phy_DX0GSR0_t
 *  @brief null
 *  @details DATX8 n General Status Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0GSR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Reserved. Returns zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wldq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Write Leveling DQ Status. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_29_26 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Reserved. Returns zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gdqsprd </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Read DQS gating Period. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dplock </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DATX8 PLL Lock. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wlprd </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Write Leveling Period. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wlerr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Write Leveling Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wldone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Write Leveling Done. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wlcal </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Write Leveling Calibration. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gdqscal </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Read DQS gating Calibration. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdqsncal </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Read DQS_N Calibration. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdqscal </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Read DQS Calibration. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wdqcal </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Write DQ Calibration. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0GSR0_t
 *
 * Implemented by: 
 *      DX0GSR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31                               :  1;
     unsigned      wldq                                      :  1;
     unsigned      reserved_29_26                            :  4;
     unsigned      gdqsprd                                   :  9;
     unsigned      dplock                                    :  1;
     unsigned      wlprd                                     :  9;
     unsigned      wlerr                                     :  1;
     unsigned      wldone                                    :  1;
     unsigned      wlcal                                     :  1;
     unsigned      gdqscal                                   :  1;
     unsigned      rdqsncal                                  :  1;
     unsigned      rdqscal                                   :  1;
     unsigned      wdqcal                                    :  1;
#else    /* Little Endian */
     unsigned      wdqcal                                    :  1;
     unsigned      rdqscal                                   :  1;
     unsigned      rdqsncal                                  :  1;
     unsigned      gdqscal                                   :  1;
     unsigned      wlcal                                     :  1;
     unsigned      wldone                                    :  1;
     unsigned      wlerr                                     :  1;
     unsigned      wlprd                                     :  9;
     unsigned      dplock                                    :  1;
     unsigned      gdqsprd                                   :  9;
     unsigned      reserved_29_26                            :  4;
     unsigned      wldq                                      :  1;
     unsigned      reserved_31                               :  1;
#endif
} ncp_phy_DX0GSR0_t;

/*! @struct ncp_phy_DX0GSR1_t
 *  @brief null
 *  @details DATX8 n General Status Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0GSR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_25 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Reserved. Returns zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dltcode </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Delay Line Test Code. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dltdone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Delay Line Test Done. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0GSR1_t
 *
 * Implemented by: 
 *      DX0GSR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_25                            :  7;
     unsigned      dltcode                                   : 24;
     unsigned      dltdone                                   :  1;
#else    /* Little Endian */
     unsigned      dltdone                                   :  1;
     unsigned      dltcode                                   : 24;
     unsigned      reserved_31_25                            :  7;
#endif
} ncp_phy_DX0GSR1_t;

/*! @struct ncp_phy_DX0GSR2_t
 *  @brief null
 *  @details DATX8 n General Status Register 2
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0GSR2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param gsdqsprd </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Read DQS gating Status Period. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gsdqscal </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Read DQS Gating Status Calibration. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_21 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param srderr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Static Read Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_19_12 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved. Returns zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param estat </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Error Status. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wewn </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Write Eye Centering Warning. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param weerr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Write Eye Centering Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rewn </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Read Eye Centering Warning. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reerr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Read Eye Centering Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wdwn </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Write Bit Deskew Warning. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wderr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Write Bit Deskew Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdwn </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Read Bit Deskew Warning. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rderr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Read Bit Deskew Error. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0GSR2_t
 *
 * Implemented by: 
 *      DX0GSR2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      gsdqsprd                                  :  9;
     unsigned      gsdqscal                                  :  1;
     unsigned      reserved_21                               :  1;
     unsigned      srderr                                    :  1;
     unsigned      reserved_19_12                            :  8;
     unsigned      estat                                     :  4;
     unsigned      wewn                                      :  1;
     unsigned      weerr                                     :  1;
     unsigned      rewn                                      :  1;
     unsigned      reerr                                     :  1;
     unsigned      wdwn                                      :  1;
     unsigned      wderr                                     :  1;
     unsigned      rdwn                                      :  1;
     unsigned      rderr                                     :  1;
#else    /* Little Endian */
     unsigned      rderr                                     :  1;
     unsigned      rdwn                                      :  1;
     unsigned      wderr                                     :  1;
     unsigned      wdwn                                      :  1;
     unsigned      reerr                                     :  1;
     unsigned      rewn                                      :  1;
     unsigned      weerr                                     :  1;
     unsigned      wewn                                      :  1;
     unsigned      estat                                     :  4;
     unsigned      reserved_19_12                            :  8;
     unsigned      srderr                                    :  1;
     unsigned      reserved_21                               :  1;
     unsigned      gsdqscal                                  :  1;
     unsigned      gsdqsprd                                  :  9;
#endif
} ncp_phy_DX0GSR2_t;

/*! @struct ncp_phy_DX0GSR3_t
 *  @brief null
 *  @details DATX8 n General Status Register 3
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0GSR3_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_27 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param estat </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> VREF Training Error Status Code. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dvwrn </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> DRAM VREF Training Warning. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dverr </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DRAM VREF Training Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hvwrn </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Host VREF Training Warning. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hverr </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Host VREF Training Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param srdpc </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Static Read Delay Pass Count. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0GSR3_t
 *
 * Implemented by: 
 *      DX0GSR3
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_27                            :  5;
     unsigned      estat                                     :  3;
     unsigned      dvwrn                                     :  4;
     unsigned      dverr                                     :  4;
     unsigned      hvwrn                                     :  4;
     unsigned      hverr                                     :  4;
     unsigned      reserved_7_2                              :  6;
     unsigned      srdpc                                     :  2;
#else    /* Little Endian */
     unsigned      srdpc                                     :  2;
     unsigned      reserved_7_2                              :  6;
     unsigned      hverr                                     :  4;
     unsigned      hvwrn                                     :  4;
     unsigned      dverr                                     :  4;
     unsigned      dvwrn                                     :  4;
     unsigned      estat                                     :  3;
     unsigned      reserved_31_27                            :  5;
#endif
} ncp_phy_DX0GSR3_t;

/*! @struct ncp_phy_DX0GSR4_t
 *  @brief null
 *  @details DATX8 n General Status Register 4
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0GSR4_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved. Returns zeroes on reads. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0GSR4_t
 *
 * Implemented by: 
 *      DX0GSR4
 */
 
typedef struct
{
     unsigned  int             reserved_31_0;
} ncp_phy_DX0GSR4_t;

/*! @struct ncp_phy_DX0GSR5_t
 *  @brief null
 *  @details DATX8 n General Status Register 5
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0GSR5_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved. Returns zeroes on reads. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0GSR5_t
 *
 * Implemented by: 
 *      DX0GSR5
 */
 
typedef struct
{
     unsigned  int             reserved_31_0;
} ncp_phy_DX0GSR5_t;

/*! @struct ncp_phy_DX0GSR6_t
 *  @brief null
 *  @details DATX8 n General Status Register 6
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX0GSR6_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved. Returns zeroes on reads. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX0GSR6_t
 *
 * Implemented by: 
 *      DX0GSR6
 */
 
typedef struct
{
     unsigned  int             reserved_31_0;
} ncp_phy_DX0GSR6_t;

/*! @struct ncp_phy_DX1GCR0_t
 *  @brief null
 *  @details DATX8 n General Configuration Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1GCR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param calbyp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Calibration Bypass. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mdlen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Master Delay Line Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_29_24 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved. Returns zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rddly </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Number of Cycles (in terms of ctl_clk) to generate
 *        ctl_dx_get_static_rd input for the respective bypte
 *        lane of the PHY.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pllbyp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> PLL Bypass. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gshift </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Gear Shift. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pllpd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> PLL Power Down. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pllrst </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> PLL Rest. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqsnsepdr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> DQSNSE Power Down Receiver. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqssepdr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> DQSSE Power Down Receiver. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rttoal </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> RTT On Additive Latency. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rttoh </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> RTT Output Hold. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_8_7 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqsrpd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> DQSR Power Down. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqsgpdr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> DQSG Power Down Receiver. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqsgpdd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> DQSG Power Down Driver. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqsgodt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> DQSG On-Die Termination. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqsgoe </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> DQSG Output Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxiom </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Data I/O Mode. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data Byte Enable. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1GCR0_t
 *
 * Implemented by: 
 *      DX1GCR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      calbyp                                    :  1;
     unsigned      mdlen                                     :  1;
     unsigned      reserved_29_24                            :  6;
     unsigned      rddly                                     :  4;
     unsigned      pllbyp                                    :  1;
     unsigned      gshift                                    :  1;
     unsigned      pllpd                                     :  1;
     unsigned      pllrst                                    :  1;
     unsigned      reserved_15_14                            :  2;
     unsigned      dqsnsepdr                                 :  1;
     unsigned      dqssepdr                                  :  1;
     unsigned      rttoal                                    :  1;
     unsigned      rttoh                                     :  2;
     unsigned      reserved_8_7                              :  2;
     unsigned      dqsrpd                                    :  1;
     unsigned      dqsgpdr                                   :  1;
     unsigned      dqsgpdd                                   :  1;
     unsigned      dqsgodt                                   :  1;
     unsigned      dqsgoe                                    :  1;
     unsigned      dxiom                                     :  1;
     unsigned      dxen                                      :  1;
#else    /* Little Endian */
     unsigned      dxen                                      :  1;
     unsigned      dxiom                                     :  1;
     unsigned      dqsgoe                                    :  1;
     unsigned      dqsgodt                                   :  1;
     unsigned      dqsgpdd                                   :  1;
     unsigned      dqsgpdr                                   :  1;
     unsigned      dqsrpd                                    :  1;
     unsigned      reserved_8_7                              :  2;
     unsigned      rttoh                                     :  2;
     unsigned      rttoal                                    :  1;
     unsigned      dqssepdr                                  :  1;
     unsigned      dqsnsepdr                                 :  1;
     unsigned      reserved_15_14                            :  2;
     unsigned      pllrst                                    :  1;
     unsigned      pllpd                                     :  1;
     unsigned      gshift                                    :  1;
     unsigned      pllbyp                                    :  1;
     unsigned      rddly                                     :  4;
     unsigned      reserved_29_24                            :  6;
     unsigned      mdlen                                     :  1;
     unsigned      calbyp                                    :  1;
#endif
} ncp_phy_DX1GCR0_t;

/*! @struct ncp_phy_DX1GCR1_t
 *  @brief null
 *  @details DATX8 n General Configuration Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1GCR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dxpdrmode </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enables the PDR mode values for DQ[7:0]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxpddmode </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enables the PDD mode values for DQ[7:0]. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1GCR1_t
 *
 * Implemented by: 
 *      DX1GCR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      dxpdrmode                                 : 16;
     unsigned      dxpddmode                                 : 16;
#else    /* Little Endian */
     unsigned      dxpddmode                                 : 16;
     unsigned      dxpdrmode                                 : 16;
#endif
} ncp_phy_DX1GCR1_t;

/*! @struct ncp_phy_DX1GCR2_t
 *  @brief null
 *  @details DATX8 n General Configuration Register 2
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1GCR2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dxoemode </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enables the OE mode values for DQ[7:0]. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxtemode </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enables the TE (ODT) mode values for DQ[7:0]. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1GCR2_t
 *
 * Implemented by: 
 *      DX1GCR2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      dxoemode                                  : 16;
     unsigned      dxtemode                                  : 16;
#else    /* Little Endian */
     unsigned      dxtemode                                  : 16;
     unsigned      dxoemode                                  : 16;
#endif
} ncp_phy_DX1GCR2_t;

/*! @struct ncp_phy_DX1GCR3_t
 *  @brief null
 *  @details DATX8 n General Configuration Register 3
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1GCR3_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdbvt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Read Data BDL VT Compensation. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wdbvt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Write Data BDL VT Compensation. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rglvt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Read DQS Gating LCDL Delay VT Compensation. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Read DQS LCDL Delay VT Compensation. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wdlvt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Write DQ LCDL Delay VT Compensation. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wllvt </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Write Leveling LCDL Delay VT Compensation. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dmoemode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Enables the OE mode values for DM. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dmtemode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Enables the TE mode values for DM. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dmpdrmode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Enables the PDR mode values for DM. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dmpddmode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enables the PDD mode values for DM. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dsoemode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Enables the OE mode values for DQS. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dstemode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Enables the TE mode values for DQS. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dspdrmode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Enables the PDR mode values for DQS. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dspddmode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enables the PDD mode values for DQS. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1GCR3_t
 *
 * Implemented by: 
 *      DX1GCR3
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      rdbvt                                     :  1;
     unsigned      wdbvt                                     :  1;
     unsigned      rglvt                                     :  1;
     unsigned      rdlvt                                     :  1;
     unsigned      wdlvt                                     :  1;
     unsigned      wllvt                                     :  1;
     unsigned      reserved_23_16                            :  8;
     unsigned      dmoemode                                  :  2;
     unsigned      dmtemode                                  :  2;
     unsigned      dmpdrmode                                 :  2;
     unsigned      dmpddmode                                 :  2;
     unsigned      dsoemode                                  :  2;
     unsigned      dstemode                                  :  2;
     unsigned      dspdrmode                                 :  2;
     unsigned      dspddmode                                 :  2;
#else    /* Little Endian */
     unsigned      dspddmode                                 :  2;
     unsigned      dspdrmode                                 :  2;
     unsigned      dstemode                                  :  2;
     unsigned      dsoemode                                  :  2;
     unsigned      dmpddmode                                 :  2;
     unsigned      dmpdrmode                                 :  2;
     unsigned      dmtemode                                  :  2;
     unsigned      dmoemode                                  :  2;
     unsigned      reserved_23_16                            :  8;
     unsigned      wllvt                                     :  1;
     unsigned      wdlvt                                     :  1;
     unsigned      rdlvt                                     :  1;
     unsigned      rglvt                                     :  1;
     unsigned      wdbvt                                     :  1;
     unsigned      rdbvt                                     :  1;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_DX1GCR3_t;

/*! @struct ncp_phy_DX1GCR4_t
 *  @brief null
 *  @details DATX8 n General Configuration Register 4
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1GCR4_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dxrefiom </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Byte lane VREF IOM (Used only by D4MU IOs) </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxrefpen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Byte Lane VREF Pad Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxrefeen </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Byte Lane Internal VREF Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxrefsen </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Byte Lane Single-End VREF Enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_24_22 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxrefesel </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Byte Lane External VREF Select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxrefssel </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Byte Lane Single-End VREF Select. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxrefien </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> VREF Enable control for DQ IO (Single Ended) buffers
 *        of a byte lane.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxrefimon </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> VRMON control for DQ IO (Single Ended) buffers of
 *        a byte lane.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1GCR4_t
 *
 * Implemented by: 
 *      DX1GCR4
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      dxrefiom                                  :  3;
     unsigned      dxrefpen                                  :  1;
     unsigned      dxrefeen                                  :  2;
     unsigned      dxrefsen                                  :  1;
     unsigned      reserved_24_22                            :  3;
     unsigned      dxrefesel                                 :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dxrefssel                                 :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dxrefien                                  :  4;
     unsigned      dxrefimon                                 :  2;
#else    /* Little Endian */
     unsigned      dxrefimon                                 :  2;
     unsigned      dxrefien                                  :  4;
     unsigned      reserved_7_6                              :  2;
     unsigned      dxrefssel                                 :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dxrefesel                                 :  6;
     unsigned      reserved_24_22                            :  3;
     unsigned      dxrefsen                                  :  1;
     unsigned      dxrefeen                                  :  2;
     unsigned      dxrefpen                                  :  1;
     unsigned      dxrefiom                                  :  3;
#endif
} ncp_phy_DX1GCR4_t;

/*! @struct ncp_phy_DX1GCR5_t
 *  @brief null
 *  @details DATX8 n General Configuration Register 5
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1GCR5_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxrefiselr3 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Byte Lane internal VREF Select for Rank3. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_22 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxrefiselr2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Byte Lane internal VREF Select for Rank2. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxrefiselr1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Byte Lane internal VREF Select for Rank 1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxrefiselr0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Byte Lane internal VREF Select for Rank0. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1GCR5_t
 *
 * Implemented by: 
 *      DX1GCR5
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      dxrefiselr3                               :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      dxrefiselr2                               :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dxrefiselr1                               :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dxrefiselr0                               :  6;
#else    /* Little Endian */
     unsigned      dxrefiselr0                               :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dxrefiselr1                               :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dxrefiselr2                               :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      dxrefiselr3                               :  6;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_DX1GCR5_t;

/*! @struct ncp_phy_DX1GCR6_t
 *  @brief null
 *  @details DATX8 n General Configuration Register 6
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1GCR6_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxdqvrefr3 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> DRAM DQ VREF Select for Rank3. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_22 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxdqvrefr2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DRAM DQ VREF Select for Rank2. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxdqvrefr1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DRAM DQ VREF Select for Rank1. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dxdqvrefr0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM DQ VREF Select for Rank0. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1GCR6_t
 *
 * Implemented by: 
 *      DX1GCR6
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      dxdqvrefr3                                :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      dxdqvrefr2                                :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dxdqvrefr1                                :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dxdqvrefr0                                :  6;
#else    /* Little Endian */
     unsigned      dxdqvrefr0                                :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dxdqvrefr1                                :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dxdqvrefr2                                :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      dxdqvrefr3                                :  6;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_DX1GCR6_t;

/*! @struct ncp_phy_DX1GCR7_t
 *  @brief null
 *  @details DATX8 n General Configuration Register 7
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1GCR7_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1GCR7_t
 *
 * Implemented by: 
 *      DX1GCR7
 */
 
typedef struct
{
     unsigned  int             reserved_31_0;
} ncp_phy_DX1GCR7_t;

/*! @struct ncp_phy_DX1GCR8_t
 *  @brief null
 *  @details DATX8 n General Configuration Register 8
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1GCR8_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1GCR8_t
 *
 * Implemented by: 
 *      DX1GCR8
 */
 
typedef struct
{
     unsigned  int             reserved_31_0;
} ncp_phy_DX1GCR8_t;

/*! @struct ncp_phy_DX1GCR9_t
 *  @brief null
 *  @details DATX8 n General Configuration Register 9
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1GCR9_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved. Returns zeros on reads. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1GCR9_t
 *
 * Implemented by: 
 *      DX1GCR9
 */
 
typedef struct
{
     unsigned  int             reserved_31_0;
} ncp_phy_DX1GCR9_t;

/*! @struct ncp_phy_DX1BDLR0_t
 *  @brief null
 *  @details DATX8 n Bit Delay Line Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1BDLR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq3wbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> DQ3 Write Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_22 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq2wbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DQ2 Write Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq1wbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DQ1 Write Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq0wbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DQ0 Write Bit Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1BDLR0_t
 *
 * Implemented by: 
 *      DX1BDLR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      dq3wbd                                    :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      dq2wbd                                    :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dq1wbd                                    :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dq0wbd                                    :  6;
#else    /* Little Endian */
     unsigned      dq0wbd                                    :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dq1wbd                                    :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dq2wbd                                    :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      dq3wbd                                    :  6;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_DX1BDLR0_t;

/*! @struct ncp_phy_DX1BDLR1_t
 *  @brief null
 *  @details DATX8 n Bit Delay Line Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1BDLR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq7wbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> DQ7 Write Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_22 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq6wbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DQ6 Write Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq5wbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DQ5 Write Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq4wbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DQ4 Write Bit Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1BDLR1_t
 *
 * Implemented by: 
 *      DX1BDLR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      dq7wbd                                    :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      dq6wbd                                    :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dq5wbd                                    :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dq4wbd                                    :  6;
#else    /* Little Endian */
     unsigned      dq4wbd                                    :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dq5wbd                                    :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dq6wbd                                    :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      dq7wbd                                    :  6;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_DX1BDLR1_t;

/*! @struct ncp_phy_DX1BDLR2_t
 *  @brief null
 *  @details DATX8 n Bit Delay Line Register 2
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1BDLR2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_22 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dsoebd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DQS/DM/DQ Output Enable Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dswbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DQS Write Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dmwbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DM Write Bit Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1BDLR2_t
 *
 * Implemented by: 
 *      DX1BDLR2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_22                            : 10;
     unsigned      dsoebd                                    :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dswbd                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dmwbd                                     :  6;
#else    /* Little Endian */
     unsigned      dmwbd                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dswbd                                     :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dsoebd                                    :  6;
     unsigned      reserved_31_22                            : 10;
#endif
} ncp_phy_DX1BDLR2_t;

/*! @struct ncp_phy_DX1BDLR3_t
 *  @brief null
 *  @details DATX8 n Bit Delay Line Register 3
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1BDLR3_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq3rbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> DQ3 Read Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_22 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq2rbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DQ2 Read Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq1rbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DQ1 Read Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq0rbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DQ0 Read Bit Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1BDLR3_t
 *
 * Implemented by: 
 *      DX1BDLR3
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      dq3rbd                                    :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      dq2rbd                                    :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dq1rbd                                    :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dq0rbd                                    :  6;
#else    /* Little Endian */
     unsigned      dq0rbd                                    :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dq1rbd                                    :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dq2rbd                                    :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      dq3rbd                                    :  6;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_DX1BDLR3_t;

/*! @struct ncp_phy_DX1BDLR4_t
 *  @brief null
 *  @details DATX8 n Bit Delay Line Register 4
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1BDLR4_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_30 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq7rbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> DQ7 Read Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_23_22 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq6rbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DQ6 Read Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq5rbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DQ5 Read Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq4rbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DQ4 Read Bit Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1BDLR4_t
 *
 * Implemented by: 
 *      DX1BDLR4
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_30                            :  2;
     unsigned      dq7rbd                                    :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      dq6rbd                                    :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dq5rbd                                    :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dq4rbd                                    :  6;
#else    /* Little Endian */
     unsigned      dq4rbd                                    :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dq5rbd                                    :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dq6rbd                                    :  6;
     unsigned      reserved_23_22                            :  2;
     unsigned      dq7rbd                                    :  6;
     unsigned      reserved_31_30                            :  2;
#endif
} ncp_phy_DX1BDLR4_t;

/*! @struct ncp_phy_DX1BDLR5_t
 *  @brief null
 *  @details DATX8 n Bit Delay Line Register 5
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1BDLR5_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_22 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dsnrbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DQSN Read Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dsrbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DQS Read Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dmrbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DM Read Bit Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1BDLR5_t
 *
 * Implemented by: 
 *      DX1BDLR5
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_22                            : 10;
     unsigned      dsnrbd                                    :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dsrbd                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dmrbd                                     :  6;
#else    /* Little Endian */
     unsigned      dmrbd                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      dsrbd                                     :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      dsnrbd                                    :  6;
     unsigned      reserved_31_22                            : 10;
#endif
} ncp_phy_DX1BDLR5_t;

/*! @struct ncp_phy_DX1BDLR6_t
 *  @brief null
 *  @details DATX8 n Bit Delay Line Register 6
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1BDLR6_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_22 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param terbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Termination Enable Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pdrbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Power down receiver Bit Delay. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pddbd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Power down driver Bit Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1BDLR6_t
 *
 * Implemented by: 
 *      DX1BDLR6
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_22                            : 10;
     unsigned      terbd                                     :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      pdrbd                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      pddbd                                     :  6;
#else    /* Little Endian */
     unsigned      pddbd                                     :  6;
     unsigned      reserved_7_6                              :  2;
     unsigned      pdrbd                                     :  6;
     unsigned      reserved_15_14                            :  2;
     unsigned      terbd                                     :  6;
     unsigned      reserved_31_22                            : 10;
#endif
} ncp_phy_DX1BDLR6_t;

/*! @struct ncp_phy_DX1BDLR7_t
 *  @brief null
 *  @details DATX8 n Bit Delay Line Register 7
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1BDLR7_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1BDLR7_t
 *
 * Implemented by: 
 *      DX1BDLR7
 */
 
typedef struct
{
     unsigned  int             reserved_31_0;
} ncp_phy_DX1BDLR7_t;

/*! @struct ncp_phy_DX1BDLR8_t
 *  @brief null
 *  @details DATX8 n Bit Delay Line Register 8
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1BDLR8_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1BDLR8_t
 *
 * Implemented by: 
 *      DX1BDLR8
 */
 
typedef struct
{
     unsigned  int             reserved_31_0;
} ncp_phy_DX1BDLR8_t;

/*! @struct ncp_phy_DX1BDLR9_t
 *  @brief null
 *  @details DATX8 n Bit Delay Line Register 9
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1BDLR9_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1BDLR9_t
 *
 * Implemented by: 
 *      DX1BDLR9
 */
 
typedef struct
{
     unsigned  int             reserved_31_0;
} ncp_phy_DX1BDLR9_t;

/*! @struct ncp_phy_DX1LCDLR0_t
 *  @brief null
 *  @details DATX8 n Local Calibrated Delay Line Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1LCDLR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_9 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wld </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Write Leveling Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1LCDLR0_t
 *
 * Implemented by: 
 *      DX1LCDLR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_9                             : 23;
     unsigned      wld                                       :  9;
#else    /* Little Endian */
     unsigned      wld                                       :  9;
     unsigned      reserved_31_9                             : 23;
#endif
} ncp_phy_DX1LCDLR0_t;

/*! @struct ncp_phy_DX1LCDLR1_t
 *  @brief null
 *  @details DATX8 n Local Calibrated Delay Line Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1LCDLR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_9 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wdqd </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Write Data Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1LCDLR1_t
 *
 * Implemented by: 
 *      DX1LCDLR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_9                             : 23;
     unsigned      wdqd                                      :  9;
#else    /* Little Endian */
     unsigned      wdqd                                      :  9;
     unsigned      reserved_31_9                             : 23;
#endif
} ncp_phy_DX1LCDLR1_t;

/*! @struct ncp_phy_DX1LCDLR2_t
 *  @brief null
 *  @details DATX8 n Local Calibrated Delay Line Register 2
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1LCDLR2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_9 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqsgd </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Read DQS Gating Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1LCDLR2_t
 *
 * Implemented by: 
 *      DX1LCDLR2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_9                             : 23;
     unsigned      dqsgd                                     :  9;
#else    /* Little Endian */
     unsigned      dqsgd                                     :  9;
     unsigned      reserved_31_9                             : 23;
#endif
} ncp_phy_DX1LCDLR2_t;

/*! @struct ncp_phy_DX1LCDLR3_t
 *  @brief null
 *  @details DATX8 n Local Calibrated Delay Line Register 3
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1LCDLR3_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_9 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdqsd </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Read DQS Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1LCDLR3_t
 *
 * Implemented by: 
 *      DX1LCDLR3
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_9                             : 23;
     unsigned      rdqsd                                     :  9;
#else    /* Little Endian */
     unsigned      rdqsd                                     :  9;
     unsigned      reserved_31_9                             : 23;
#endif
} ncp_phy_DX1LCDLR3_t;

/*! @struct ncp_phy_DX1LCDLR4_t
 *  @brief null
 *  @details DATX8 n Local Calibrated Delay Line Register 4
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1LCDLR4_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_9 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdqsnd </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Read DQSN Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1LCDLR4_t
 *
 * Implemented by: 
 *      DX1LCDLR4
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_9                             : 23;
     unsigned      rdqsnd                                    :  9;
#else    /* Little Endian */
     unsigned      rdqsnd                                    :  9;
     unsigned      reserved_31_9                             : 23;
#endif
} ncp_phy_DX1LCDLR4_t;

/*! @struct ncp_phy_DX1LCDLR5_t
 *  @brief null
 *  @details DATX8 n Local Calibrated Delay Line Register 5
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1LCDLR5_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_9 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dqsgsd </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DQS Gating Status Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1LCDLR5_t
 *
 * Implemented by: 
 *      DX1LCDLR5
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_9                             : 23;
     unsigned      dqsgsd                                    :  9;
#else    /* Little Endian */
     unsigned      dqsgsd                                    :  9;
     unsigned      reserved_31_9                             : 23;
#endif
} ncp_phy_DX1LCDLR5_t;

/*! @struct ncp_phy_DX1MDLR0_t
 *  @brief null
 *  @details DATX8 n Master Delay Line Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1MDLR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_25 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tprd </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Target Period. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_9 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param iprd </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Initial Period. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1MDLR0_t
 *
 * Implemented by: 
 *      DX1MDLR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_25                            :  7;
     unsigned      tprd                                      :  9;
     unsigned      reserved_15_9                             :  7;
     unsigned      iprd                                      :  9;
#else    /* Little Endian */
     unsigned      iprd                                      :  9;
     unsigned      reserved_15_9                             :  7;
     unsigned      tprd                                      :  9;
     unsigned      reserved_31_25                            :  7;
#endif
} ncp_phy_DX1MDLR0_t;

/*! @struct ncp_phy_DX1MDLR1_t
 *  @brief null
 *  @details DATX8 n Master Delay Line Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1MDLR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_9 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mdld </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MDL Delay. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1MDLR1_t
 *
 * Implemented by: 
 *      DX1MDLR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_9                             : 23;
     unsigned      mdld                                      :  9;
#else    /* Little Endian */
     unsigned      mdld                                      :  9;
     unsigned      reserved_31_9                             : 23;
#endif
} ncp_phy_DX1MDLR1_t;

/*! @struct ncp_phy_DX1GTR0_t
 *  @brief null
 *  @details DATX8 n General Timing Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1GTR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_20 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wlsl </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Write Leveling System Latency. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_15_5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dgsl </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DQS Gating System Latency. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1GTR0_t
 *
 * Implemented by: 
 *      DX1GTR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_20                            : 12;
     unsigned      wlsl                                      :  4;
     unsigned      reserved_15_5                             : 11;
     unsigned      dgsl                                      :  5;
#else    /* Little Endian */
     unsigned      dgsl                                      :  5;
     unsigned      reserved_15_5                             : 11;
     unsigned      wlsl                                      :  4;
     unsigned      reserved_31_20                            : 12;
#endif
} ncp_phy_DX1GTR0_t;

/*! @struct ncp_phy_DX1RSR0_t
 *  @brief null
 *  @details DATX8 n Rank Status Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1RSR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param qsgerr </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DQS Gate Training Error. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1RSR0_t
 *
 * Implemented by: 
 *      DX1RSR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_16                            : 16;
     unsigned      qsgerr                                    : 16;
#else    /* Little Endian */
     unsigned      qsgerr                                    : 16;
     unsigned      reserved_31_16                            : 16;
#endif
} ncp_phy_DX1RSR0_t;

/*! @struct ncp_phy_DX1RSR1_t
 *  @brief null
 *  @details DATX8 n Rank Status Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1RSR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvlerr </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Read Leveling Error. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1RSR1_t
 *
 * Implemented by: 
 *      DX1RSR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_16                            : 16;
     unsigned      rdlvlerr                                  : 16;
#else    /* Little Endian */
     unsigned      rdlvlerr                                  : 16;
     unsigned      reserved_31_16                            : 16;
#endif
} ncp_phy_DX1RSR1_t;

/*! @struct ncp_phy_DX1RSR2_t
 *  @brief null
 *  @details DATX8 n Rank Status Register 2
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1RSR2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wlawn </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Write Latency Adjustment (DQS off on some DQ lines)
 *        Warning.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1RSR2_t
 *
 * Implemented by: 
 *      DX1RSR2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_16                            : 16;
     unsigned      wlawn                                     : 16;
#else    /* Little Endian */
     unsigned      wlawn                                     : 16;
     unsigned      reserved_31_16                            : 16;
#endif
} ncp_phy_DX1RSR2_t;

/*! @struct ncp_phy_DX1RSR3_t
 *  @brief null
 *  @details DATX8 n Rank Status Register 3
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1RSR3_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wlaerr </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Write Leveling Adjustment Error. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1RSR3_t
 *
 * Implemented by: 
 *      DX1RSR3
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_16                            : 16;
     unsigned      wlaerr                                    : 16;
#else    /* Little Endian */
     unsigned      wlaerr                                    : 16;
     unsigned      reserved_31_16                            : 16;
#endif
} ncp_phy_DX1RSR3_t;

/*! @struct ncp_phy_DX1GSR0_t
 *  @brief null
 *  @details DATX8 n General Status Register 0
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1GSR0_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> Reserved. Returns zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wldq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> Write Leveling DQ Status. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_29_26 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Reserved. Returns zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gdqsprd </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Read DQS gating Period. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dplock </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DATX8 PLL Lock. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wlprd </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Write Leveling Period. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wlerr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Write Leveling Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wldone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Write Leveling Done. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wlcal </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Write Leveling Calibration. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gdqscal </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Read DQS gating Calibration. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdqsncal </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Read DQS_N Calibration. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdqscal </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Read DQS Calibration. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wdqcal </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Write DQ Calibration. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1GSR0_t
 *
 * Implemented by: 
 *      DX1GSR0
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31                               :  1;
     unsigned      wldq                                      :  1;
     unsigned      reserved_29_26                            :  4;
     unsigned      gdqsprd                                   :  9;
     unsigned      dplock                                    :  1;
     unsigned      wlprd                                     :  9;
     unsigned      wlerr                                     :  1;
     unsigned      wldone                                    :  1;
     unsigned      wlcal                                     :  1;
     unsigned      gdqscal                                   :  1;
     unsigned      rdqsncal                                  :  1;
     unsigned      rdqscal                                   :  1;
     unsigned      wdqcal                                    :  1;
#else    /* Little Endian */
     unsigned      wdqcal                                    :  1;
     unsigned      rdqscal                                   :  1;
     unsigned      rdqsncal                                  :  1;
     unsigned      gdqscal                                   :  1;
     unsigned      wlcal                                     :  1;
     unsigned      wldone                                    :  1;
     unsigned      wlerr                                     :  1;
     unsigned      wlprd                                     :  9;
     unsigned      dplock                                    :  1;
     unsigned      gdqsprd                                   :  9;
     unsigned      reserved_29_26                            :  4;
     unsigned      wldq                                      :  1;
     unsigned      reserved_31                               :  1;
#endif
} ncp_phy_DX1GSR0_t;

/*! @struct ncp_phy_DX1GSR1_t
 *  @brief null
 *  @details DATX8 n General Status Register 1
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1GSR1_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_25 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Reserved. Returns zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dltcode </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Delay Line Test Code. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dltdone </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Delay Line Test Done. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1GSR1_t
 *
 * Implemented by: 
 *      DX1GSR1
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_25                            :  7;
     unsigned      dltcode                                   : 24;
     unsigned      dltdone                                   :  1;
#else    /* Little Endian */
     unsigned      dltdone                                   :  1;
     unsigned      dltcode                                   : 24;
     unsigned      reserved_31_25                            :  7;
#endif
} ncp_phy_DX1GSR1_t;

/*! @struct ncp_phy_DX1GSR2_t
 *  @brief null
 *  @details DATX8 n General Status Register 2
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1GSR2_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param gsdqsprd </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Read DQS gating Status Period. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param gsdqscal </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Read DQS Gating Status Calibration. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_21 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param srderr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Static Read Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_19_12 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved. Returns zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param estat </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Error Status. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wewn </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Write Eye Centering Warning. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param weerr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Write Eye Centering Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rewn </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Read Eye Centering Warning. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reerr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Read Eye Centering Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wdwn </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Write Bit Deskew Warning. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wderr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Write Bit Deskew Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdwn </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Read Bit Deskew Warning. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rderr </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Read Bit Deskew Error. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1GSR2_t
 *
 * Implemented by: 
 *      DX1GSR2
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      gsdqsprd                                  :  9;
     unsigned      gsdqscal                                  :  1;
     unsigned      reserved_21                               :  1;
     unsigned      srderr                                    :  1;
     unsigned      reserved_19_12                            :  8;
     unsigned      estat                                     :  4;
     unsigned      wewn                                      :  1;
     unsigned      weerr                                     :  1;
     unsigned      rewn                                      :  1;
     unsigned      reerr                                     :  1;
     unsigned      wdwn                                      :  1;
     unsigned      wderr                                     :  1;
     unsigned      rdwn                                      :  1;
     unsigned      rderr                                     :  1;
#else    /* Little Endian */
     unsigned      rderr                                     :  1;
     unsigned      rdwn                                      :  1;
     unsigned      wderr                                     :  1;
     unsigned      wdwn                                      :  1;
     unsigned      reerr                                     :  1;
     unsigned      rewn                                      :  1;
     unsigned      weerr                                     :  1;
     unsigned      wewn                                      :  1;
     unsigned      estat                                     :  4;
     unsigned      reserved_19_12                            :  8;
     unsigned      srderr                                    :  1;
     unsigned      reserved_21                               :  1;
     unsigned      gsdqscal                                  :  1;
     unsigned      gsdqsprd                                  :  9;
#endif
} ncp_phy_DX1GSR2_t;

/*! @struct ncp_phy_DX1GSR3_t
 *  @brief null
 *  @details DATX8 n General Status Register 3
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1GSR3_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_27 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param estat </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> VREF Training Error Status Code. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dvwrn </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> DRAM VREF Training Warning. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dverr </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DRAM VREF Training Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hvwrn </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Host VREF Training Warning. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param hverr </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Host VREF Training Error. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_7_2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved. Return zeroes on reads. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param srdpc </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Static Read Delay Pass Count. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1GSR3_t
 *
 * Implemented by: 
 *      DX1GSR3
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved_31_27                            :  5;
     unsigned      estat                                     :  3;
     unsigned      dvwrn                                     :  4;
     unsigned      dverr                                     :  4;
     unsigned      hvwrn                                     :  4;
     unsigned      hverr                                     :  4;
     unsigned      reserved_7_2                              :  6;
     unsigned      srdpc                                     :  2;
#else    /* Little Endian */
     unsigned      srdpc                                     :  2;
     unsigned      reserved_7_2                              :  6;
     unsigned      hverr                                     :  4;
     unsigned      hvwrn                                     :  4;
     unsigned      dverr                                     :  4;
     unsigned      dvwrn                                     :  4;
     unsigned      estat                                     :  3;
     unsigned      reserved_31_27                            :  5;
#endif
} ncp_phy_DX1GSR3_t;

/*! @struct ncp_phy_DX1GSR4_t
 *  @brief null
 *  @details DATX8 n General Status Register 4
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1GSR4_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved. Returns zeroes on reads. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1GSR4_t
 *
 * Implemented by: 
 *      DX1GSR4
 */
 
typedef struct
{
     unsigned  int             reserved_31_0;
} ncp_phy_DX1GSR4_t;

/*! @struct ncp_phy_DX1GSR5_t
 *  @brief null
 *  @details DATX8 n General Status Register 5
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1GSR5_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved. Returns zeroes on reads. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1GSR5_t
 *
 * Implemented by: 
 *      DX1GSR5
 */
 
typedef struct
{
     unsigned  int             reserved_31_0;
} ncp_phy_DX1GSR5_t;

/*! @struct ncp_phy_DX1GSR6_t
 *  @brief null
 *  @details DATX8 n General Status Register 6
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_phy_DX1GSR6_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved_31_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved. Returns zeroes on reads. </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_phy_DX1GSR6_t
 *
 * Implemented by: 
 *      DX1GSR6
 */
 
typedef struct
{
     unsigned  int             reserved_31_0;
} ncp_phy_DX1GSR6_t;

#ifdef __cplusplus
}
#endif

#endif /* _NCP_PHY_REGS_H_ */
