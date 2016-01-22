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

#ifndef _NCP_DENALI_5600_REGS_H_
#define _NCP_DENALI_5600_REGS_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __UBOOT__
#include "ncp_sal_types.h"
#endif

/*! @struct ncp_denali_DENALI_CTL_00_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_00_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param version </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Holds the controller version number. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dram_class </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the mode of operation of the controller. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param start </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Initiate command processing in the controller. Set
 *        to 1 to initiate.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_00_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      version                                   : 16;
     unsigned      reserved0                                 :  4;
     unsigned      dram_class                                :  4;
     unsigned      reserved1                                 :  7;
     unsigned      start                                     :  1;
#else    /* Little Endian */
     unsigned      start                                     :  1;
     unsigned      reserved1                                 :  7;
     unsigned      dram_class                                :  4;
     unsigned      reserved0                                 :  4;
     unsigned      version                                   : 16;
#endif
} ncp_denali_DENALI_CTL_00_5600_t;

/*! @struct ncp_denali_DENALI_CTL_01_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_01_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param read_data_fifo_depth </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reports the depth of the controller core read data
 *        queue. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param max_cs_reg </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Holds the maximum number of chip selects available.
 *        READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
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
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param max_row_reg </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Holds the maximum width of memory address bus. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_01_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      read_data_fifo_depth                      :  8;
     unsigned      reserved0                                 :  5;
     unsigned      max_cs_reg                                :  3;
     unsigned      reserved1                                 :  4;
     unsigned      max_col_reg                               :  4;
     unsigned      reserved2                                 :  3;
     unsigned      max_row_reg                               :  5;
#else    /* Little Endian */
     unsigned      max_row_reg                               :  5;
     unsigned      reserved2                                 :  3;
     unsigned      max_col_reg                               :  4;
     unsigned      reserved1                                 :  4;
     unsigned      max_cs_reg                                :  3;
     unsigned      reserved0                                 :  5;
     unsigned      read_data_fifo_depth                      :  8;
#endif
} ncp_denali_DENALI_CTL_01_5600_t;

/*! @struct ncp_denali_DENALI_CTL_02_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_02_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param memcd_rmodw_fifo_depth </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reports the depth of the controller core read/modify/write
 *        FIFO. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param write_data_fifo_ptr_width </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reports the width of the controller core write data
 *        latency queue pointer. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param write_data_fifo_depth </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reports the depth of the controller core write data
 *        latency queue. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param read_data_fifo_ptr_width </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reports the width of the controller core read data
 *        queue pointer. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_02_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      memcd_rmodw_fifo_depth                    :  8;
     unsigned      write_data_fifo_ptr_width                 :  8;
     unsigned      write_data_fifo_depth                     :  8;
     unsigned      read_data_fifo_ptr_width                  :  8;
#else    /* Little Endian */
     unsigned      read_data_fifo_ptr_width                  :  8;
     unsigned      write_data_fifo_depth                     :  8;
     unsigned      write_data_fifo_ptr_width                 :  8;
     unsigned      memcd_rmodw_fifo_depth                    :  8;
#endif
} ncp_denali_DENALI_CTL_02_5600_t;

/*! @struct ncp_denali_DENALI_CTL_03_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_03_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_rdfifo_log2_depth </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reports the depth of the AXI port 0 read data FIFO.
 *        Value is the log2 value of the depth. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_cmdfifo_log2_depth </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reports the depth of the AXI port 0 command FIFO.
 *        Value is the log2 value of the depth. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param async_cdc_stages </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reports the number of synchronizer delays specified
 *        for the asynchronous boundary crossings. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param memcd_rmodw_fifo_ptr_width </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reports the width of the controller core read/modify/write
 *        FIFO pointer. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_03_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      axi0_rdfifo_log2_depth                    :  8;
     unsigned      axi0_cmdfifo_log2_depth                   :  8;
     unsigned      async_cdc_stages                          :  8;
     unsigned      memcd_rmodw_fifo_ptr_width                :  8;
#else    /* Little Endian */
     unsigned      memcd_rmodw_fifo_ptr_width                :  8;
     unsigned      async_cdc_stages                          :  8;
     unsigned      axi0_cmdfifo_log2_depth                   :  8;
     unsigned      axi0_rdfifo_log2_depth                    :  8;
#endif
} ncp_denali_DENALI_CTL_03_5600_t;

/*! @struct ncp_denali_DENALI_CTL_04_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_04_5600_t\n
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
 *     <td width="30%"> @param axi0_wrcmd_proc_fifo_log2_depth </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reports the depth of the AXI port 0 write command
 *        processing FIFO. Value is the log2 value of the depth.
 *        READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_04_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 : 16;
     unsigned      axi0_wrcmd_proc_fifo_log2_depth           :  8;
     unsigned      obsolete0                                 :  8;
#else    /* Little Endian */
     unsigned      obsolete0                                 :  8;
     unsigned      axi0_wrcmd_proc_fifo_log2_depth           :  8;
     unsigned      obsolete2                                 : 16;
#endif
} ncp_denali_DENALI_CTL_04_5600_t;

/*! @struct ncp_denali_DENALI_CTL_05_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_05_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_05_5600_t
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
} ncp_denali_DENALI_CTL_05_5600_t;

/*! @struct ncp_denali_DENALI_CTL_06_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_06_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_06_5600_t
 *
 */
 
typedef struct
{
     unsigned  int                trst_pwron;
} ncp_denali_DENALI_CTL_06_5600_t;

/*! @struct ncp_denali_DENALI_CTL_07_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_07_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_07_5600_t
 *
 */
 
typedef struct
{
     unsigned  int              cke_inactive;
} ncp_denali_DENALI_CTL_07_5600_t;

/*! @struct ncp_denali_DENALI_CTL_08_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_08_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param wrlat </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> DRAM WRLAT value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param caslat_lin </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Sets latency from read command send to data receive
 *        from/to controller. Bit (0) is half-cycle increment
 *        and the upper bits define memory CAS latency for the
 *        controller.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdll </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM TDLL value in cycles. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_08_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      wrlat                                     :  5;
     unsigned      reserved1                                 :  2;
     unsigned      caslat_lin                                :  6;
     unsigned      tdll                                      : 16;
#else    /* Little Endian */
     unsigned      tdll                                      : 16;
     unsigned      caslat_lin                                :  6;
     unsigned      reserved1                                 :  2;
     unsigned      wrlat                                     :  5;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_08_5600_t;

/*! @struct ncp_denali_DENALI_CTL_09_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_09_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param tmrd_par </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> DRAM TMRD value when CA parity is enabled in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tmod_par </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DRAM TMOD value when CA parity is enabled in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ca_parity_lat </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DRAM CA parity latency value in cycles. </td>
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_09_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      tmrd_par                                  :  5;
     unsigned      tmod_par                                  :  8;
     unsigned      reserved1                                 :  4;
     unsigned      ca_parity_lat                             :  4;
     unsigned      reserved2                                 :  3;
     unsigned      additive_lat                              :  5;
#else    /* Little Endian */
     unsigned      additive_lat                              :  5;
     unsigned      reserved2                                 :  3;
     unsigned      ca_parity_lat                             :  4;
     unsigned      reserved1                                 :  4;
     unsigned      tmod_par                                  :  8;
     unsigned      tmrd_par                                  :  5;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_09_5600_t;

/*! @struct ncp_denali_DENALI_CTL_10_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_10_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tccd </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> DRAM CAS-to-CAS value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tbst_int_interval </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DRAM burst interrupt interval value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tparity_error_cmd_inhibit </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the window after the MC receives a parity
 *        error during which DRAM commands will not execute.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved for future use. Refer to the regconfig files
 *        for the default programming.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_10_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved1                                 :  3;
     unsigned      tccd                                      :  5;
     unsigned      reserved2                                 :  5;
     unsigned      tbst_int_interval                         :  3;
     unsigned      tparity_error_cmd_inhibit                 :  8;
     unsigned      reserved0                                 :  8;
#else    /* Little Endian */
     unsigned      reserved0                                 :  8;
     unsigned      tparity_error_cmd_inhibit                 :  8;
     unsigned      tbst_int_interval                         :  3;
     unsigned      reserved2                                 :  5;
     unsigned      tccd                                      :  5;
     unsigned      reserved1                                 :  3;
#endif
} ncp_denali_DENALI_CTL_10_5600_t;

/*! @struct ncp_denali_DENALI_CTL_11_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_11_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param trc </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> DRAM TRC value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trrd_l </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DRAM TRRD_L value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trrd </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DRAM TRRD value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tccd_l </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM CAS-to-CAS value within the same bank group in
 *        cycles.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_11_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      trc                                       :  8;
     unsigned      trrd_l                                    :  8;
     unsigned      trrd                                      :  8;
     unsigned      reserved0                                 :  3;
     unsigned      tccd_l                                    :  5;
#else    /* Little Endian */
     unsigned      tccd_l                                    :  5;
     unsigned      reserved0                                 :  3;
     unsigned      trrd                                      :  8;
     unsigned      trrd_l                                    :  8;
     unsigned      trc                                       :  8;
#endif
} ncp_denali_DENALI_CTL_11_5600_t;

/*! @struct ncp_denali_DENALI_CTL_12_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_12_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param trp </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> DRAM TRP value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param twtr_l </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DRAM TWTR_L value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param twtr </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DRAM TWTR value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tras_min </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM TRAS_MIN value in cycles. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_12_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      trp                                       :  8;
     unsigned      reserved0                                 :  2;
     unsigned      twtr_l                                    :  6;
     unsigned      reserved1                                 :  2;
     unsigned      twtr                                      :  6;
     unsigned      tras_min                                  :  8;
#else    /* Little Endian */
     unsigned      tras_min                                  :  8;
     unsigned      twtr                                      :  6;
     unsigned      reserved1                                 :  2;
     unsigned      twtr_l                                    :  6;
     unsigned      reserved0                                 :  2;
     unsigned      trp                                       :  8;
#endif
} ncp_denali_DENALI_CTL_12_5600_t;

/*! @struct ncp_denali_DENALI_CTL_13_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_13_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param tmrd </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> DRAM TMRD value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trtp_ap </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DRAM TRTP for auto-precharge value in cycles. </td>
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
 *     <td width="30%"> @param tfaw </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM TFAW value in cycles. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_13_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      tmrd                                      :  5;
     unsigned      reserved1                                 :  4;
     unsigned      trtp_ap                                   :  4;
     unsigned      reserved2                                 :  4;
     unsigned      trtp                                      :  4;
     unsigned      tfaw                                      :  8;
#else    /* Little Endian */
     unsigned      tfaw                                      :  8;
     unsigned      trtp                                      :  4;
     unsigned      reserved2                                 :  4;
     unsigned      trtp_ap                                   :  4;
     unsigned      reserved1                                 :  4;
     unsigned      tmrd                                      :  5;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_13_5600_t;

/*! @struct ncp_denali_DENALI_CTL_14_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_14_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param tras_max </td>
 *     <td width="20%" align="center"> 20 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DRAM TRAS_MAX value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tmod </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of cycles after MRS command and before any
 *        other command.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_14_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      tras_max                                  : 20;
     unsigned      tmod                                      :  8;
#else    /* Little Endian */
     unsigned      tmod                                      :  8;
     unsigned      tras_max                                  : 20;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_14_5600_t;

/*! @struct ncp_denali_DENALI_CTL_15_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_15_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param writeinterp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Allow controller to interrupt a write burst to the
 *        DRAMs with a read command. Set to 1 to allow interruption.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param twr_mpr </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of cycles after MPR write command and before
 *        any other command.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tckesr </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Minimum CKE low pulse width during a self-refresh. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tcke </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Minimum CKE pulse width. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_15_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      writeinterp                               :  1;
     unsigned      twr_mpr                                   :  8;
     unsigned      tckesr                                    :  8;
     unsigned      reserved1                                 :  4;
     unsigned      tcke                                      :  4;
#else    /* Little Endian */
     unsigned      tcke                                      :  4;
     unsigned      reserved1                                 :  4;
     unsigned      tckesr                                    :  8;
     unsigned      twr_mpr                                   :  8;
     unsigned      writeinterp                               :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_15_5600_t;

/*! @struct ncp_denali_DENALI_CTL_16_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_16_5600_t\n
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
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the number of cycles of delay after a MRW
 *        command that changes VREF value to the next command.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param twr </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DRAM TWR value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trcd </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM TRCD value in cycles. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_16_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      tvref                                     : 16;
     unsigned      reserved0                                 :  2;
     unsigned      twr                                       :  6;
     unsigned      trcd                                      :  8;
#else    /* Little Endian */
     unsigned      trcd                                      :  8;
     unsigned      twr                                       :  6;
     unsigned      reserved0                                 :  2;
     unsigned      tvref                                     : 16;
#endif
} ncp_denali_DENALI_CTL_16_5600_t;

/*! @struct ncp_denali_DENALI_CTL_17_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_17_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param concurrentap </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Allow controller to issue commands to other banks
 *        while a bank is in auto pre-charge. Set to 1 to enable.
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
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tmprr </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DRAM TMPRR value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tmrd_pda </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of cycles after a per-DRAM addressable MRW
 *        command data is complete to the next command.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_17_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      concurrentap                              :  1;
     unsigned      reserved1                                 :  7;
     unsigned      ap                                        :  1;
     unsigned      reserved2                                 :  4;
     unsigned      tmprr                                     :  4;
     unsigned      tmrd_pda                                  :  8;
#else    /* Little Endian */
     unsigned      tmrd_pda                                  :  8;
     unsigned      tmprr                                     :  4;
     unsigned      reserved2                                 :  4;
     unsigned      ap                                        :  1;
     unsigned      reserved1                                 :  7;
     unsigned      concurrentap                              :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_17_5600_t;

/*! @struct ncp_denali_DENALI_CTL_18_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_18_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param trp_ab </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> DRAM TRP all bank value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bstlen </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Encoded burst length sent to DRAMs during initialization.
 *        Program to 1 for BL2, program to 2 for BL4, or program
 *        to 3 for BL8.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdal </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DRAM TDAL value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tras_lockout </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allow the controller to execute auto pre-charge commands
 *        before the TRAS_MIN parameter expires. Set to 1 to
 *        enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_18_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      trp_ab                                    :  8;
     unsigned      reserved0                                 :  5;
     unsigned      bstlen                                    :  3;
     unsigned      reserved1                                 :  2;
     unsigned      tdal                                      :  6;
     unsigned      reserved2                                 :  7;
     unsigned      tras_lockout                              :  1;
#else    /* Little Endian */
     unsigned      tras_lockout                              :  1;
     unsigned      reserved2                                 :  7;
     unsigned      tdal                                      :  6;
     unsigned      reserved1                                 :  2;
     unsigned      bstlen                                    :  3;
     unsigned      reserved0                                 :  5;
     unsigned      trp_ab                                    :  8;
#endif
} ncp_denali_DENALI_CTL_18_5600_t;

/*! @struct ncp_denali_DENALI_CTL_19_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_19_5600_t\n
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
 *     <td width="30%"> @param address_inversion </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Indicates which chip selects support address inversion.
 *        Bit (0) controls cs0, bit (1) controls cs1, etc. Set
 *        each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param address_mirroring </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Indicates which chip selects support address mirroring.
 *        Bit (0) controls cs0, bit (1) controls cs1, etc. Set
 *        each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reg_dimm_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enable registered DIMM operation of the controller.
 *        Set to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_19_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      reserved0                                 :  4;
     unsigned      address_inversion                         :  4;
     unsigned      reserved1                                 :  4;
     unsigned      address_mirroring                         :  4;
     unsigned      reserved2                                 :  7;
     unsigned      reg_dimm_enable                           :  1;
#else    /* Little Endian */
     unsigned      reg_dimm_enable                           :  1;
     unsigned      reserved2                                 :  7;
     unsigned      address_mirroring                         :  4;
     unsigned      reserved1                                 :  4;
     unsigned      address_inversion                         :  4;
     unsigned      reserved0                                 :  4;
     unsigned      obsolete3                                 :  8;
#endif
} ncp_denali_DENALI_CTL_19_5600_t;

/*! @struct ncp_denali_DENALI_CTL_20_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_20_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param pda_invert_dev_cs1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the side for the device on CS 1. Set all bits
 *        for a device to 1 for A side.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pda_invert_dev_cs0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the side for the device on CS 0. Set all bits
 *        for a device to 1 for A side.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_20_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      pda_invert_dev_cs1                        : 16;
     unsigned      pda_invert_dev_cs0                        : 16;
#else    /* Little Endian */
     unsigned      pda_invert_dev_cs0                        : 16;
     unsigned      pda_invert_dev_cs1                        : 16;
#endif
} ncp_denali_DENALI_CTL_20_5600_t;

/*! @struct ncp_denali_DENALI_CTL_21_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_21_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved4 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved for future use. Refer to the regconfig files
 *        for the default programming.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved5 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param optimal_rmodw_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enables optimized RMODW logic in the controller. A
 *        value of 1 enables optimized RMODW operation. All
 *        RMODW operations are still supported in a non-optimal
 *        manner when the value is 0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved6 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pda_invert_ecc_dev_cs1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the side for the ECC device on CS 1. Set all
 *        bits for a device to 1 for A side.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved7 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pda_invert_ecc_dev_cs0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the side for the ECC device on CS 0. Set all
 *        bits for a device to 1 for A side.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_21_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved4                                 :  7;
     unsigned      reserved3                                 :  1;
     unsigned      reserved5                                 :  7;
     unsigned      optimal_rmodw_en                          :  1;
     unsigned      reserved6                                 :  6;
     unsigned      pda_invert_ecc_dev_cs1                    :  2;
     unsigned      reserved7                                 :  6;
     unsigned      pda_invert_ecc_dev_cs0                    :  2;
#else    /* Little Endian */
     unsigned      pda_invert_ecc_dev_cs0                    :  2;
     unsigned      reserved7                                 :  6;
     unsigned      pda_invert_ecc_dev_cs1                    :  2;
     unsigned      reserved6                                 :  6;
     unsigned      optimal_rmodw_en                          :  1;
     unsigned      reserved5                                 :  7;
     unsigned      reserved3                                 :  1;
     unsigned      reserved4                                 :  7;
#endif
} ncp_denali_DENALI_CTL_21_5600_t;

/*! @struct ncp_denali_DENALI_CTL_22_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_22_5600_t\n
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
 *     <td width="30%"> @param no_memory_dm </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Indicates that the external DRAM does not support
 *        DM masking. Set to 1 for no DM masking at the DRAM.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_22_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  7;
     unsigned      no_memory_dm                              :  1;
#else    /* Little Endian */
     unsigned      no_memory_dm                              :  1;
     unsigned      reserved0                                 :  7;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_22_5600_t;

/*! @struct ncp_denali_DENALI_CTL_23_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_23_5600_t\n
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
 *   <td width="30%"> RDIMM control word values for DIMM 0. Bits (3:0) correlate
 *        to control word 0, bits (7:4) correlate to control
 *        word 1, etc.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_23_5600_t
 *
 */
 
typedef struct
{
     unsigned  int               rdimm_ctl_0;
} ncp_denali_DENALI_CTL_23_5600_t;

/*! @struct ncp_denali_DENALI_CTL_24_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_24_5600_t\n
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
 *   <td width="30%"> RDIMM control word values for DIMM 0. Bits (3:0) correlate
 *        to control word 0, bits (7:4) correlate to control
 *        word 1, etc.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_24_5600_t
 *
 */
 
typedef struct
{
     unsigned  int               rdimm_ctl_0;
} ncp_denali_DENALI_CTL_24_5600_t;

/*! @struct ncp_denali_DENALI_CTL_25_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_25_5600_t\n
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
 *   <td width="30%"> RDIMM control word values for DIMM 0. Bits (3:0) correlate
 *        to control word 0, bits (7:4) correlate to control
 *        word 1, etc.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_25_5600_t
 *
 */
 
typedef struct
{
     unsigned  int               rdimm_ctl_0;
} ncp_denali_DENALI_CTL_25_5600_t;

/*! @struct ncp_denali_DENALI_CTL_26_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_26_5600_t\n
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
 *   <td width="30%"> RDIMM control word values for DIMM 0. Bits (3:0) correlate
 *        to control word 0, bits (7:4) correlate to control
 *        word 1, etc.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_26_5600_t
 *
 */
 
typedef struct
{
     unsigned  int               rdimm_ctl_0;
} ncp_denali_DENALI_CTL_26_5600_t;

/*! @struct ncp_denali_DENALI_CTL_27_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_27_5600_t\n
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
 *     <td width="30%"> @param rdimm_ctl_0 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> RDIMM control word values for DIMM 0. Bits (3:0) correlate
 *        to control word 0, bits (7:4) correlate to control
 *        word 1, etc.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_27_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      rdimm_ctl_0                               : 24;
#else    /* Little Endian */
     unsigned      rdimm_ctl_0                               : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_27_5600_t;

/*! @struct ncp_denali_DENALI_CTL_28_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_28_5600_t\n
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
 *   <td width="30%"> RDIMM control word values for DIMM 1. Bits (3:0) correlate
 *        to control word 0, bits (7:4) correlate to control
 *        word 1, etc.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_28_5600_t
 *
 */
 
typedef struct
{
     unsigned  int               rdimm_ctl_1;
} ncp_denali_DENALI_CTL_28_5600_t;

/*! @struct ncp_denali_DENALI_CTL_29_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_29_5600_t\n
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
 *   <td width="30%"> RDIMM control word values for DIMM 1. Bits (3:0) correlate
 *        to control word 0, bits (7:4) correlate to control
 *        word 1, etc.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_29_5600_t
 *
 */
 
typedef struct
{
     unsigned  int               rdimm_ctl_1;
} ncp_denali_DENALI_CTL_29_5600_t;

/*! @struct ncp_denali_DENALI_CTL_30_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_30_5600_t\n
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
 *   <td width="30%"> RDIMM control word values for DIMM 1. Bits (3:0) correlate
 *        to control word 0, bits (7:4) correlate to control
 *        word 1, etc.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_30_5600_t
 *
 */
 
typedef struct
{
     unsigned  int               rdimm_ctl_1;
} ncp_denali_DENALI_CTL_30_5600_t;

/*! @struct ncp_denali_DENALI_CTL_31_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_31_5600_t\n
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
 *   <td width="30%"> RDIMM control word values for DIMM 1. Bits (3:0) correlate
 *        to control word 0, bits (7:4) correlate to control
 *        word 1, etc.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_31_5600_t
 *
 */
 
typedef struct
{
     unsigned  int               rdimm_ctl_1;
} ncp_denali_DENALI_CTL_31_5600_t;

/*! @struct ncp_denali_DENALI_CTL_32_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_32_5600_t\n
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
 *     <td width="30%"> @param rdimm_ctl_1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> RDIMM control word values for DIMM 1. Bits (3:0) correlate
 *        to control word 0, bits (7:4) correlate to control
 *        word 1, etc.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_32_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      rdimm_ctl_1                               : 24;
#else    /* Little Endian */
     unsigned      rdimm_ctl_1                               : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_32_5600_t;

/*! @struct ncp_denali_DENALI_CTL_33_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_33_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param rdimm_cw_map </td>
 *     <td width="20%" align="center"> 27 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines which RDIMM control words will be updated
 *        during initialization. Bit (0) correlates to control
 *        word 0, bit (1) correlates to control word 1, etc.
 *        Set each bit to 1 to write.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_33_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  5;
     unsigned      rdimm_cw_map                              : 27;
#else    /* Little Endian */
     unsigned      rdimm_cw_map                              : 27;
     unsigned      reserved0                                 :  5;
#endif
} ncp_denali_DENALI_CTL_33_5600_t;

/*! @struct ncp_denali_DENALI_CTL_34_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_34_5600_t\n
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
 *     <td width="30%"> @param rdimm_tmrd </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the TMRD value in cycles for the registered
 *        DIMM. This is the delay required from a control word
 *        write to another control word write or to a DRAM access.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdimm_cw_hold_cke_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines if the CKE value will be held or asserted
 *        for all DDR3 RDIMM control word accesses. Set to 1
 *        to hold current value.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdimm_cww_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Triggers a control word write to all DIMMs specified
 *        in the RDIMM_CW_MAP parameter with the values in the
 *        RDIMM_CTL_X parameter(s). Ignored during initialization
 *        because an automatic control word write happens during
 *        initialization. WRITE-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_34_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      reserved0                                 :  4;
     unsigned      rdimm_tmrd                                :  4;
     unsigned      reserved1                                 :  7;
     unsigned      rdimm_cw_hold_cke_en                      :  1;
     unsigned      reserved2                                 :  7;
     unsigned      rdimm_cww_req                             :  1;
#else    /* Little Endian */
     unsigned      rdimm_cww_req                             :  1;
     unsigned      reserved2                                 :  7;
     unsigned      rdimm_cw_hold_cke_en                      :  1;
     unsigned      reserved1                                 :  7;
     unsigned      rdimm_tmrd                                :  4;
     unsigned      reserved0                                 :  4;
     unsigned      obsolete3                                 :  8;
#endif
} ncp_denali_DENALI_CTL_34_5600_t;

/*! @struct ncp_denali_DENALI_CTL_35_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_35_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param cs_map_dimm_0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines which chip selects are contained on DIMM 0.
 *        Bit (0) controls cs0, bit (1) controls cs1, etc. Set
 *        each bit to 1 to enable for DIMM 0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdimm_tstab </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the TSTAB value in cycles for the registered
 *        DIMM. This is the delay required from a control word
 *        write to CW2 or CW10 to another control word write
 *        or to a DRAM access.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_35_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      cs_map_dimm_0                             :  4;
     unsigned      rdimm_tstab                               : 24;
#else    /* Little Endian */
     unsigned      rdimm_tstab                               : 24;
     unsigned      cs_map_dimm_0                             :  4;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_35_5600_t;

/*! @struct ncp_denali_DENALI_CTL_36_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_36_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param rdimm_tmrd_l </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines the TMRD_L value in cycles for the registered
 *        DIMM. This is the delay required between accesses
 *        to RC03, RC04, RC05, RC0B or RC7x and the next control
 *        word write.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rank0_map_dimm_1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines which chip select is rank 0 on DIMM 1. Bit
 *        (0) controls cs0, bit (1) controls cs1, etc. Set one
 *        bit to 1 to enable for DIMM 1. No bits set indicate
 *        that DIMM 1 is unconnected.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rank0_map_dimm_0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines which chip select is rank 0 on DIMM 0. Bit
 *        (0) controls cs0, bit (1) controls cs1, etc. Set one
 *        bit to 1 to enable for DIMM 0. No bits set indicate
 *        that DIMM 0 is unconnected.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_36_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      rdimm_tmrd_l                              :  5;
     unsigned      reserved1                                 :  4;
     unsigned      rank0_map_dimm_1                          :  4;
     unsigned      reserved2                                 :  4;
     unsigned      rank0_map_dimm_0                          :  4;
     unsigned      reserved3                                 :  4;
     unsigned      cs_map_dimm_1                             :  4;
#else    /* Little Endian */
     unsigned      cs_map_dimm_1                             :  4;
     unsigned      reserved3                                 :  4;
     unsigned      rank0_map_dimm_0                          :  4;
     unsigned      reserved2                                 :  4;
     unsigned      rank0_map_dimm_1                          :  4;
     unsigned      reserved1                                 :  4;
     unsigned      rdimm_tmrd_l                              :  5;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_36_5600_t;

/*! @struct ncp_denali_DENALI_CTL_37_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_37_5600_t\n
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
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdimm_tmrc </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the TMRC value in cycles for the registered
 *        DIMM. This is the delay required between an access
 *        to RC06 and the next control word write or a DRAM
 *        access.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdimm_tmrd_l2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the TMRD_L2 value in cycles for the registered
 *        DIMM. This is the delay required between accesses
 *        to RC0D or RC0F and the next control word write.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_37_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 : 16;
     unsigned      reserved0                                 :  3;
     unsigned      rdimm_tmrc                                :  5;
     unsigned      reserved1                                 :  2;
     unsigned      rdimm_tmrd_l2                             :  6;
#else    /* Little Endian */
     unsigned      rdimm_tmrd_l2                             :  6;
     unsigned      reserved1                                 :  2;
     unsigned      rdimm_tmrc                                :  5;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete2                                 : 16;
#endif
} ncp_denali_DENALI_CTL_37_5600_t;

/*! @struct ncp_denali_DENALI_CTL_38_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_38_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param rdimm_cww_init_map_cke_low </td>
 *     <td width="20%" align="center"> 27 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enables control word write to RC0A and RC3x during
 *        initialization while CKE is low. Other control word
 *        writes enabled through RDIMM_CW_MAP will be issued
 *        during initialization when CKE is high. RC0A and RC3x
 *        will be skipped during the CKE high control word write
 *        sequence if this parameter is enabled.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_38_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  5;
     unsigned      rdimm_cww_init_map_cke_low                : 27;
#else    /* Little Endian */
     unsigned      rdimm_cww_init_map_cke_low                : 27;
     unsigned      reserved0                                 :  5;
#endif
} ncp_denali_DENALI_CTL_38_5600_t;

/*! @struct ncp_denali_DENALI_CTL_39_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_39_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param ca_parity_error_inject </td>
 *     <td width="20%" align="center"> 27 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Selects bit to corrupt on the CA bus for CA parity
 *        error injection.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_39_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  5;
     unsigned      ca_parity_error_inject                    : 27;
#else    /* Little Endian */
     unsigned      ca_parity_error_inject                    : 27;
     unsigned      reserved0                                 :  5;
#endif
} ncp_denali_DENALI_CTL_39_5600_t;

/*! @struct ncp_denali_DENALI_CTL_40_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_40_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param arefresh </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Initiate auto-refresh at the end of the current burst
 *        boundary. Set to 1 to trigger. WRITE-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved for future use. Refer to the regconfig files
 *        for the default programming.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved5 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved for future use. Refer to the regconfig files
 *        for the default programming.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved6 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ca_parity_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Contains one hot indication of registered DIMM parity
 *        errors. Value of 1 indicates an error on that DIMM.
 *        READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_40_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved3                                 :  7;
     unsigned      arefresh                                  :  1;
     unsigned      reserved4                                 :  4;
     unsigned      reserved2                                 :  4;
     unsigned      reserved5                                 :  5;
     unsigned      reserved1                                 :  3;
     unsigned      reserved6                                 :  7;
     unsigned      ca_parity_error                           :  1;
#else    /* Little Endian */
     unsigned      ca_parity_error                           :  1;
     unsigned      reserved6                                 :  7;
     unsigned      reserved1                                 :  3;
     unsigned      reserved5                                 :  5;
     unsigned      reserved2                                 :  4;
     unsigned      reserved4                                 :  4;
     unsigned      arefresh                                  :  1;
     unsigned      reserved3                                 :  7;
#endif
} ncp_denali_DENALI_CTL_40_5600_t;

/*! @struct ncp_denali_DENALI_CTL_41_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_41_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param trfc </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DRAM TRFC value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tref_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Issue auto-refresh commands to the DRAMs at the interval
 *        defined in the TREF parameter. Set to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved for future use. Refer to the regconfig files
 *        for the default programming.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_41_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved1                                 :  6;
     unsigned      trfc                                      : 10;
     unsigned      reserved2                                 :  7;
     unsigned      tref_enable                               :  1;
     unsigned      reserved3                                 :  7;
     unsigned      reserved0                                 :  1;
#else    /* Little Endian */
     unsigned      reserved0                                 :  1;
     unsigned      reserved3                                 :  7;
     unsigned      tref_enable                               :  1;
     unsigned      reserved2                                 :  7;
     unsigned      trfc                                      : 10;
     unsigned      reserved1                                 :  6;
#endif
} ncp_denali_DENALI_CTL_41_5600_t;

/*! @struct ncp_denali_DENALI_CTL_42_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_42_5600_t\n
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
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tref </td>
 *     <td width="20%" align="center"> 20 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM TREF value in cycles. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_42_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  4;
     unsigned      tref                                      : 20;
#else    /* Little Endian */
     unsigned      tref                                      : 20;
     unsigned      reserved0                                 :  4;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_42_5600_t;

/*! @struct ncp_denali_DENALI_CTL_43_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_43_5600_t\n
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
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tref_interval </td>
 *     <td width="20%" align="center"> 20 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the cycles between refreshes to different
 *        chip selects.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_43_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  4;
     unsigned      tref_interval                             : 20;
#else    /* Little Endian */
     unsigned      tref_interval                             : 20;
     unsigned      reserved0                                 :  4;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_43_5600_t;

/*! @struct ncp_denali_DENALI_CTL_44_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_44_5600_t\n
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
 *     <td width="30%"> @param tpdex </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM TPDEX value in cycles. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_44_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      txpdll                                    : 16;
     unsigned      tpdex                                     : 16;
#else    /* Little Endian */
     unsigned      tpdex                                     : 16;
     unsigned      txpdll                                    : 16;
#endif
} ncp_denali_DENALI_CTL_44_5600_t;

/*! @struct ncp_denali_DENALI_CTL_45_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_45_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param txsnr </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> DRAM TXSNR value in cycles. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param txsr </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DRAM TXSR value in cycles. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_45_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      txsnr                                     : 16;
     unsigned      txsr                                      : 16;
#else    /* Little Endian */
     unsigned      txsr                                      : 16;
     unsigned      txsnr                                     : 16;
#endif
} ncp_denali_DENALI_CTL_45_5600_t;

/*! @struct ncp_denali_DENALI_CTL_46_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_46_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param cke_delay </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Additional cycles to delay CKE for status reporting. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enable_quick_srefresh </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Allow user to interrupt memory initialization to enter
 *        self-refresh mode. Set to 1 to allow interruption.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param srefresh_exit_no_refresh </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Disables the automatic refresh request associated
 *        with self-refresh exit. Set to 1 to disable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pwrup_srefresh_exit </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allow powerup via self-refresh instead of full memory
 *        initialization. Set to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_46_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  5;
     unsigned      cke_delay                                 :  3;
     unsigned      reserved1                                 :  7;
     unsigned      enable_quick_srefresh                     :  1;
     unsigned      reserved2                                 :  7;
     unsigned      srefresh_exit_no_refresh                  :  1;
     unsigned      reserved3                                 :  7;
     unsigned      pwrup_srefresh_exit                       :  1;
#else    /* Little Endian */
     unsigned      pwrup_srefresh_exit                       :  1;
     unsigned      reserved3                                 :  7;
     unsigned      srefresh_exit_no_refresh                  :  1;
     unsigned      reserved2                                 :  7;
     unsigned      enable_quick_srefresh                     :  1;
     unsigned      reserved1                                 :  7;
     unsigned      cke_delay                                 :  3;
     unsigned      reserved0                                 :  5;
#endif
} ncp_denali_DENALI_CTL_46_5600_t;

/*! @struct ncp_denali_DENALI_CTL_47_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_47_5600_t\n
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
 *     <td width="30%"> @param cksrx </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Clock stable delay on self-refresh exit. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cksre </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Clock hold delay on self-refresh entry. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lowpower_refresh_enable </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enable refreshes while in low power mode. Bit (0)
 *        controls cs0, bit (1) controls cs1, etc. Set each
 *        bit to 1 to disable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_47_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      cksrx                                     :  8;
     unsigned      cksre                                     :  8;
     unsigned      reserved0                                 :  4;
     unsigned      lowpower_refresh_enable                   :  4;
#else    /* Little Endian */
     unsigned      lowpower_refresh_enable                   :  4;
     unsigned      reserved0                                 :  4;
     unsigned      cksre                                     :  8;
     unsigned      cksrx                                     :  8;
     unsigned      obsolete3                                 :  8;
#endif
} ncp_denali_DENALI_CTL_47_5600_t;

/*! @struct ncp_denali_DENALI_CTL_48_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_48_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param lpi_sr_wakeup </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines the DFI tLP_WAKEUP timing parameter (in DFI
 *        clocks) to be driven when memory is in self-refresh.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpi_pd_wakeup </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the DFI tLP_WAKEUP timing parameter (in DFI
 *        clocks) to be driven when memory is in power-down.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lp_cmd </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Low power software command request interface. Bit
 *        (0) controls exit, bit (1) controls entry, bits (4:2)
 *        define the low power state, bit (5) controls memory
 *        clock gating, bit (6) controls controller clock gating,
 *        and bit (7) controls lock. WRITE-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_48_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      lpi_sr_wakeup                             :  4;
     unsigned      reserved1                                 :  4;
     unsigned      lpi_pd_wakeup                             :  4;
     unsigned      obsolete1                                 :  8;
     unsigned      lp_cmd                                    :  8;
#else    /* Little Endian */
     unsigned      lp_cmd                                    :  8;
     unsigned      obsolete1                                 :  8;
     unsigned      lpi_pd_wakeup                             :  4;
     unsigned      reserved1                                 :  4;
     unsigned      lpi_sr_wakeup                             :  4;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_48_5600_t;

/*! @struct ncp_denali_DENALI_CTL_49_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_49_5600_t\n
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
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpi_wakeup_en </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enables the various low power wakeup parameters. Bit
 *        (0) enables power-down wakeup, bit (1) enables self-refresh
 *        wakeup, bit (2) enables self-refresh with memory and
 *        controller clock gating wakeup, bit (3) is reserved
 *        and bit (4) enables the LPI timer. Set each bit to
 *        1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpi_timer_wakeup </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the DFI tLP_WAKEUP timing parameter (in DFI
 *        clocks) to be driven when the LPI timer expires.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpi_sr_mcclk_gate_wakeup </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the DFI tLP_WAKEUP timing parameter (in DFI
 *        clocks) to be driven when memory is in self-refresh
 *        with memory and controller clock gating.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_49_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      reserved0                                 :  3;
     unsigned      lpi_wakeup_en                             :  5;
     unsigned      reserved1                                 :  4;
     unsigned      lpi_timer_wakeup                          :  4;
     unsigned      reserved2                                 :  4;
     unsigned      lpi_sr_mcclk_gate_wakeup                  :  4;
#else    /* Little Endian */
     unsigned      lpi_sr_mcclk_gate_wakeup                  :  4;
     unsigned      reserved2                                 :  4;
     unsigned      lpi_timer_wakeup                          :  4;
     unsigned      reserved1                                 :  4;
     unsigned      lpi_wakeup_en                             :  5;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete3                                 :  8;
#endif
} ncp_denali_DENALI_CTL_49_5600_t;

/*! @struct ncp_denali_DENALI_CTL_50_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_50_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param lpi_wakeup_timeout </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the LPI timeout time, the maximum cycles between
 *        a dfi_lp_req de-assertion and a dfi_lp_ack de-assertion.
 *        If this value is exceeded, an interrupt will occur.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lpi_timer_count </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the LPI timer count. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_50_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      lpi_wakeup_timeout                        : 12;
     unsigned      reserved1                                 :  4;
     unsigned      lpi_timer_count                           : 12;
#else    /* Little Endian */
     unsigned      lpi_timer_count                           : 12;
     unsigned      reserved1                                 :  4;
     unsigned      lpi_wakeup_timeout                        : 12;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_50_5600_t;

/*! @struct ncp_denali_DENALI_CTL_51_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_51_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param lp_arb_state </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
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
 *        value of 5 indicates that the controller is in control.
 *        READ-ONLY
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
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_lp_resp </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the DFI tLP_RESP timing parameter (in DFI
 *        clocks), the maximum cycles between a dfi_lp_req assertion
 *        and a dfi_lp_ack assertion.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_51_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      lp_arb_state                              :  4;
     unsigned      obsolete1                                 : 16;
     unsigned      reserved1                                 :  5;
     unsigned      tdfi_lp_resp                              :  3;
#else    /* Little Endian */
     unsigned      tdfi_lp_resp                              :  3;
     unsigned      reserved1                                 :  5;
     unsigned      obsolete1                                 : 16;
     unsigned      lp_arb_state                              :  4;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_51_5600_t;

/*! @struct ncp_denali_DENALI_CTL_52_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_52_5600_t\n
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
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lp_auto_exit_en </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enable auto exit from each of the low power states
 *        when a read or write command enters the command queue.
 *        Bit (0) controls power-down, bit (1) controls self-refresh,
 *        and bit (2) controls self-refresh with memory and
 *        controller clock gating. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lp_auto_entry_en </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enable auto entry into each of the low power states
 *        when the associated idle timer expires. Bit (0) controls
 *        power-down, bit (1) controls self-refresh, and bit
 *        (2) controls self-refresh with memory and controller
 *        clock gating. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_52_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      lp_auto_mem_gate_en                       :  2;
     unsigned      reserved1                                 :  5;
     unsigned      lp_auto_exit_en                           :  3;
     unsigned      reserved2                                 :  5;
     unsigned      lp_auto_entry_en                          :  3;
#else    /* Little Endian */
     unsigned      lp_auto_entry_en                          :  3;
     unsigned      reserved2                                 :  5;
     unsigned      lp_auto_exit_en                           :  3;
     unsigned      reserved1                                 :  5;
     unsigned      lp_auto_mem_gate_en                       :  2;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete3                                 :  8;
#endif
} ncp_denali_DENALI_CTL_52_5600_t;

/*! @struct ncp_denali_DENALI_CTL_53_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_53_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param lp_auto_sr_mc_gate_idle </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Number of long count sequences until the controller
 *        will place memory in self-refresh with controller
 *        and memory clock gating.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lp_auto_sr_idle </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of long count sequences until the controller
 *        will place memory in self-refresh.
 *   </td>
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_53_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      lp_auto_sr_mc_gate_idle                   :  8;
     unsigned      lp_auto_sr_idle                           :  8;
     unsigned      reserved0                                 :  4;
     unsigned      lp_auto_pd_idle                           : 12;
#else    /* Little Endian */
     unsigned      lp_auto_pd_idle                           : 12;
     unsigned      reserved0                                 :  4;
     unsigned      lp_auto_sr_idle                           :  8;
     unsigned      lp_auto_sr_mc_gate_idle                   :  8;
#endif
} ncp_denali_DENALI_CTL_53_5600_t;

/*! @struct ncp_denali_DENALI_CTL_54_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_54_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_54_5600_t
 *
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_54_5600_t;

/*! @struct ncp_denali_DENALI_CTL_55_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_55_5600_t\n
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
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved for future use. Refer to the regconfig files
 *        for the default programming.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_55_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 : 16;
     unsigned      reserved1                                 :  8;
     unsigned      obsolete0                                 :  8;
#else    /* Little Endian */
     unsigned      obsolete0                                 :  8;
     unsigned      reserved1                                 :  8;
     unsigned      obsolete2                                 : 16;
#endif
} ncp_denali_DENALI_CTL_55_5600_t;

/*! @struct ncp_denali_DENALI_CTL_56_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_56_5600_t\n
 *   </td>
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
 *   <td width="30%"> Write memory mode register data to the DRAMs. Bits
 *        (7:0) define the memory mode register number if bit
 *        (23) is set, bits (15:8) define the chip select if
 *        bit (24) is clear, bits (23:16) define which memory
 *        mode register/s to write, bit (24) defines whether
 *        all chip selects will be written, and bit (25) triggers
 *        the write.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_56_5600_t
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
} ncp_denali_DENALI_CTL_56_5600_t;

/*! @struct ncp_denali_DENALI_CTL_57_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_57_5600_t\n
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
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param read_mpr </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Read the specified MPR register. Bits (1:0) define
 *        the MPR page, middle bits define the target chip select,
 *        and the uppermost bit set triggers the read.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved for future use. Refer to the regconfig files
 *        for the default programming.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mrw_status </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Write memory mode register status. Bit (0) set indicates
 *        a WRITE_MODEREG parameter programming error. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_57_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      reserved2                                 :  3;
     unsigned      read_mpr                                  :  5;
     unsigned      reserved3                                 :  7;
     unsigned      reserved1                                 :  1;
     unsigned      mrw_status                                :  8;
#else    /* Little Endian */
     unsigned      mrw_status                                :  8;
     unsigned      reserved1                                 :  1;
     unsigned      reserved3                                 :  7;
     unsigned      read_mpr                                  :  5;
     unsigned      reserved2                                 :  3;
     unsigned      obsolete3                                 :  8;
#endif
} ncp_denali_DENALI_CTL_57_5600_t;

/*! @struct ncp_denali_DENALI_CTL_58_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_58_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param mprr_data_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data read from MPR 0 from memory multi-purpose register
 *        read requested by the READ_MPR parameter. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_58_5600_t
 *
 */
 
typedef struct
{
     unsigned  int               mprr_data_0;
} ncp_denali_DENALI_CTL_58_5600_t;

/*! @struct ncp_denali_DENALI_CTL_59_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_59_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param mprr_data_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data read from MPR 0 from memory multi-purpose register
 *        read requested by the READ_MPR parameter. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_59_5600_t
 *
 */
 
typedef struct
{
     unsigned  int               mprr_data_0;
} ncp_denali_DENALI_CTL_59_5600_t;

/*! @struct ncp_denali_DENALI_CTL_60_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_60_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param mprr_data_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data read from MPR 0 from memory multi-purpose register
 *        read requested by the READ_MPR parameter. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_60_5600_t
 *
 */
 
typedef struct
{
     unsigned  int               mprr_data_0;
} ncp_denali_DENALI_CTL_60_5600_t;

/*! @struct ncp_denali_DENALI_CTL_61_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_61_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param mprr_data_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data read from MPR 0 from memory multi-purpose register
 *        read requested by the READ_MPR parameter. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_61_5600_t
 *
 */
 
typedef struct
{
     unsigned  int               mprr_data_0;
} ncp_denali_DENALI_CTL_61_5600_t;

/*! @struct ncp_denali_DENALI_CTL_62_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_62_5600_t\n
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
 *     <td width="30%"> @param mprr_data_0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data read from MPR 0 from memory multi-purpose register
 *        read requested by the READ_MPR parameter. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_62_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      mprr_data_0                               : 16;
#else    /* Little Endian */
     unsigned      mprr_data_0                               : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_62_5600_t;

/*! @struct ncp_denali_DENALI_CTL_63_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_63_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param mprr_data_1 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data read from MPR 1 from memory multi-purpose register
 *        read requested by the READ_MPR parameter. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_63_5600_t
 *
 */
 
typedef struct
{
     unsigned  int               mprr_data_1;
} ncp_denali_DENALI_CTL_63_5600_t;

/*! @struct ncp_denali_DENALI_CTL_64_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_64_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param mprr_data_1 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data read from MPR 1 from memory multi-purpose register
 *        read requested by the READ_MPR parameter. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_64_5600_t
 *
 */
 
typedef struct
{
     unsigned  int               mprr_data_1;
} ncp_denali_DENALI_CTL_64_5600_t;

/*! @struct ncp_denali_DENALI_CTL_65_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_65_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param mprr_data_1 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data read from MPR 1 from memory multi-purpose register
 *        read requested by the READ_MPR parameter. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_65_5600_t
 *
 */
 
typedef struct
{
     unsigned  int               mprr_data_1;
} ncp_denali_DENALI_CTL_65_5600_t;

/*! @struct ncp_denali_DENALI_CTL_66_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_66_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param mprr_data_1 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data read from MPR 1 from memory multi-purpose register
 *        read requested by the READ_MPR parameter. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_66_5600_t
 *
 */
 
typedef struct
{
     unsigned  int               mprr_data_1;
} ncp_denali_DENALI_CTL_66_5600_t;

/*! @struct ncp_denali_DENALI_CTL_67_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_67_5600_t\n
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
 *     <td width="30%"> @param mprr_data_1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data read from MPR 1 from memory multi-purpose register
 *        read requested by the READ_MPR parameter. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_67_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      mprr_data_1                               : 16;
#else    /* Little Endian */
     unsigned      mprr_data_1                               : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_67_5600_t;

/*! @struct ncp_denali_DENALI_CTL_68_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_68_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param mprr_data_2 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data read from MPR 2 from memory multi-purpose register
 *        read requested by the READ_MPR parameter. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_68_5600_t
 *
 */
 
typedef struct
{
     unsigned  int               mprr_data_2;
} ncp_denali_DENALI_CTL_68_5600_t;

/*! @struct ncp_denali_DENALI_CTL_69_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_69_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param mprr_data_2 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data read from MPR 2 from memory multi-purpose register
 *        read requested by the READ_MPR parameter. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_69_5600_t
 *
 */
 
typedef struct
{
     unsigned  int               mprr_data_2;
} ncp_denali_DENALI_CTL_69_5600_t;

/*! @struct ncp_denali_DENALI_CTL_70_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_70_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param mprr_data_2 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data read from MPR 2 from memory multi-purpose register
 *        read requested by the READ_MPR parameter. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_70_5600_t
 *
 */
 
typedef struct
{
     unsigned  int               mprr_data_2;
} ncp_denali_DENALI_CTL_70_5600_t;

/*! @struct ncp_denali_DENALI_CTL_71_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_71_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param mprr_data_2 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data read from MPR 2 from memory multi-purpose register
 *        read requested by the READ_MPR parameter. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_71_5600_t
 *
 */
 
typedef struct
{
     unsigned  int               mprr_data_2;
} ncp_denali_DENALI_CTL_71_5600_t;

/*! @struct ncp_denali_DENALI_CTL_72_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_72_5600_t\n
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
 *     <td width="30%"> @param mprr_data_2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data read from MPR 2 from memory multi-purpose register
 *        read requested by the READ_MPR parameter. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_72_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      mprr_data_2                               : 16;
#else    /* Little Endian */
     unsigned      mprr_data_2                               : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_72_5600_t;

/*! @struct ncp_denali_DENALI_CTL_73_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_73_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param mprr_data_3 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data read from MPR 3 from memory multi-purpose register
 *        read requested by the READ_MPR parameter. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_73_5600_t
 *
 */
 
typedef struct
{
     unsigned  int               mprr_data_3;
} ncp_denali_DENALI_CTL_73_5600_t;

/*! @struct ncp_denali_DENALI_CTL_74_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_74_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param mprr_data_3 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data read from MPR 3 from memory multi-purpose register
 *        read requested by the READ_MPR parameter. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_74_5600_t
 *
 */
 
typedef struct
{
     unsigned  int               mprr_data_3;
} ncp_denali_DENALI_CTL_74_5600_t;

/*! @struct ncp_denali_DENALI_CTL_75_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_75_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param mprr_data_3 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data read from MPR 3 from memory multi-purpose register
 *        read requested by the READ_MPR parameter. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_75_5600_t
 *
 */
 
typedef struct
{
     unsigned  int               mprr_data_3;
} ncp_denali_DENALI_CTL_75_5600_t;

/*! @struct ncp_denali_DENALI_CTL_76_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_76_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param mprr_data_3 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data read from MPR 3 from memory multi-purpose register
 *        read requested by the READ_MPR parameter. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_76_5600_t
 *
 */
 
typedef struct
{
     unsigned  int               mprr_data_3;
} ncp_denali_DENALI_CTL_76_5600_t;

/*! @struct ncp_denali_DENALI_CTL_77_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_77_5600_t\n
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
 *     <td width="30%"> @param mprr_data_3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data read from MPR 3 from memory multi-purpose register
 *        read requested by the READ_MPR parameter. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_77_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      mprr_data_3                               : 16;
#else    /* Little Endian */
     unsigned      mprr_data_3                               : 16;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_77_5600_t;

/*! @struct ncp_denali_DENALI_CTL_78_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_78_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr0_data_0 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 0 for chip
 *        select 0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_78_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mr0_data_0                                : 18;
#else    /* Little Endian */
     unsigned      mr0_data_0                                : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_78_5600_t;

/*! @struct ncp_denali_DENALI_CTL_79_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_79_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr1_data_0 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 1 for chip
 *        select 0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_79_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mr1_data_0                                : 18;
#else    /* Little Endian */
     unsigned      mr1_data_0                                : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_79_5600_t;

/*! @struct ncp_denali_DENALI_CTL_80_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_80_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr2_data_0 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 2 for chip
 *        select 0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_80_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mr2_data_0                                : 18;
#else    /* Little Endian */
     unsigned      mr2_data_0                                : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_80_5600_t;

/*! @struct ncp_denali_DENALI_CTL_81_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_81_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mrsingle_data_0 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register single write
 *        to chip select 0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_81_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mrsingle_data_0                           : 18;
#else    /* Little Endian */
     unsigned      mrsingle_data_0                           : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_81_5600_t;

/*! @struct ncp_denali_DENALI_CTL_82_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_82_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr3_data_0 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 3 for chip
 *        select 0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_82_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mr3_data_0                                : 18;
#else    /* Little Endian */
     unsigned      mr3_data_0                                : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_82_5600_t;

/*! @struct ncp_denali_DENALI_CTL_83_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_83_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr4_data_0 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 4 for chip
 *        select 0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_83_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mr4_data_0                                : 18;
#else    /* Little Endian */
     unsigned      mr4_data_0                                : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_83_5600_t;

/*! @struct ncp_denali_DENALI_CTL_84_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_84_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr5_data_0 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 5 for chip
 *        select 0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_84_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mr5_data_0                                : 18;
#else    /* Little Endian */
     unsigned      mr5_data_0                                : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_84_5600_t;

/*! @struct ncp_denali_DENALI_CTL_85_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_85_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr6_data_0 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 6 for chip
 *        select 0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_85_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mr6_data_0                                : 18;
#else    /* Little Endian */
     unsigned      mr6_data_0                                : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_85_5600_t;

/*! @struct ncp_denali_DENALI_CTL_86_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_86_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr0_data_1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 0 for chip
 *        select 1.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_86_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mr0_data_1                                : 18;
#else    /* Little Endian */
     unsigned      mr0_data_1                                : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_86_5600_t;

/*! @struct ncp_denali_DENALI_CTL_87_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_87_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr1_data_1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 1 for chip
 *        select 1.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_87_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mr1_data_1                                : 18;
#else    /* Little Endian */
     unsigned      mr1_data_1                                : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_87_5600_t;

/*! @struct ncp_denali_DENALI_CTL_88_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_88_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr2_data_1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 2 for chip
 *        select 1.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_88_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mr2_data_1                                : 18;
#else    /* Little Endian */
     unsigned      mr2_data_1                                : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_88_5600_t;

/*! @struct ncp_denali_DENALI_CTL_89_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_89_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mrsingle_data_1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register single write
 *        to chip select 1.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_89_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mrsingle_data_1                           : 18;
#else    /* Little Endian */
     unsigned      mrsingle_data_1                           : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_89_5600_t;

/*! @struct ncp_denali_DENALI_CTL_90_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_90_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr3_data_1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 3 for chip
 *        select 1.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_90_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mr3_data_1                                : 18;
#else    /* Little Endian */
     unsigned      mr3_data_1                                : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_90_5600_t;

/*! @struct ncp_denali_DENALI_CTL_91_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_91_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr4_data_1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 4 for chip
 *        select 1.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_91_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mr4_data_1                                : 18;
#else    /* Little Endian */
     unsigned      mr4_data_1                                : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_91_5600_t;

/*! @struct ncp_denali_DENALI_CTL_92_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_92_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr5_data_1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 5 for chip
 *        select 1.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_92_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mr5_data_1                                : 18;
#else    /* Little Endian */
     unsigned      mr5_data_1                                : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_92_5600_t;

/*! @struct ncp_denali_DENALI_CTL_93_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_93_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param bist_go </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Initiate a BIST operation. Set to 1 to trigger. WRITE-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr6_data_1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 6 for chip
 *        select 1.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_93_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      bist_go                                   :  1;
     unsigned      reserved1                                 :  6;
     unsigned      mr6_data_1                                : 18;
#else    /* Little Endian */
     unsigned      mr6_data_1                                : 18;
     unsigned      reserved1                                 :  6;
     unsigned      bist_go                                   :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_93_5600_t;

/*! @struct ncp_denali_DENALI_CTL_94_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_94_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param bist_addr_check </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Enable address checking with BIST operation. Set to
 *        1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bist_data_check </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enable data checking with BIST operation. Set to 1
 *        to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param addr_space </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Sets the number of address bits to check during BIST
 *        operation.
 *   </td>
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
 *   <td width="30%"> BIST operation status (pass/fail). Bit (0) indicates
 *        data check status and bit (1) indicates address check
 *        status. Value of 1 is a passing result. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_94_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      bist_addr_check                           :  1;
     unsigned      reserved1                                 :  7;
     unsigned      bist_data_check                           :  1;
     unsigned      reserved2                                 :  2;
     unsigned      addr_space                                :  6;
     unsigned      reserved3                                 :  6;
     unsigned      bist_result                               :  2;
#else    /* Little Endian */
     unsigned      bist_result                               :  2;
     unsigned      reserved3                                 :  6;
     unsigned      addr_space                                :  6;
     unsigned      reserved2                                 :  2;
     unsigned      bist_data_check                           :  1;
     unsigned      reserved1                                 :  7;
     unsigned      bist_addr_check                           :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_94_5600_t;

/*! @struct ncp_denali_DENALI_CTL_95_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_95_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_95_5600_t
 *
 */
 
typedef struct
{
     unsigned  int        bist_start_address;
} ncp_denali_DENALI_CTL_95_5600_t;

/*! @struct ncp_denali_DENALI_CTL_96_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_96_5600_t\n
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
 *     <td width="30%"> @param bist_start_address </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start BIST checking at this address. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_96_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      bist_start_address                        :  6;
#else    /* Little Endian */
     unsigned      bist_start_address                        :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_96_5600_t;

/*! @struct ncp_denali_DENALI_CTL_97_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_97_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_97_5600_t
 *
 */
 
typedef struct
{
     unsigned  int            bist_data_mask;
} ncp_denali_DENALI_CTL_97_5600_t;

/*! @struct ncp_denali_DENALI_CTL_98_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_98_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_98_5600_t
 *
 */
 
typedef struct
{
     unsigned  int            bist_data_mask;
} ncp_denali_DENALI_CTL_98_5600_t;

/*! @struct ncp_denali_DENALI_CTL_99_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_99_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_99_5600_t
 *
 */
 
typedef struct
{
     unsigned  int            bist_data_mask;
} ncp_denali_DENALI_CTL_99_5600_t;

/*! @struct ncp_denali_DENALI_CTL_100_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_100_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_100_5600_t
 *
 */
 
typedef struct
{
     unsigned  int            bist_data_mask;
} ncp_denali_DENALI_CTL_100_5600_t;

/*! @struct ncp_denali_DENALI_CTL_101_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_101_5600_t\n
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
 *     <td width="30%"> @param fwc </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Force a write check. Xor the XOR_CHECK_BITS parameter
 *        with the ECC code and write to memory. Set to 1 to
 *        trigger. WRITE-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> ECC error checking and correcting control. Clear to
 *        0 to disable ECC or set to 1 for ECC reporting and
 *        correcting.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_101_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 : 16;
     unsigned      reserved0                                 :  7;
     unsigned      fwc                                       :  1;
     unsigned      reserved1                                 :  7;
     unsigned      ecc_en                                    :  1;
#else    /* Little Endian */
     unsigned      ecc_en                                    :  1;
     unsigned      reserved1                                 :  7;
     unsigned      fwc                                       :  1;
     unsigned      reserved0                                 :  7;
     unsigned      obsolete2                                 : 16;
#endif
} ncp_denali_DENALI_CTL_101_5600_t;

/*! @struct ncp_denali_DENALI_CTL_102_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_102_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_102_5600_t
 *
 */
 
typedef struct
{
     unsigned  int            xor_check_bits;
} ncp_denali_DENALI_CTL_102_5600_t;

/*! @struct ncp_denali_DENALI_CTL_103_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_103_5600_t\n
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
 *     <td width="30%"> @param ecc_disable_w_uc_err </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Controls auto-corruption of ECC when un-correctable
 *        errors occur in R/M/W operations. Set to 1 to disable
 *        corruption.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_103_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  7;
     unsigned      ecc_disable_w_uc_err                      :  1;
#else    /* Little Endian */
     unsigned      ecc_disable_w_uc_err                      :  1;
     unsigned      reserved0                                 :  7;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_103_5600_t;

/*! @struct ncp_denali_DENALI_CTL_104_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_104_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_104_5600_t
 *
 */
 
typedef struct
{
     unsigned  int                ecc_u_addr;
} ncp_denali_DENALI_CTL_104_5600_t;

/*! @struct ncp_denali_DENALI_CTL_105_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_105_5600_t\n
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
 *     <td width="30%"> @param ecc_u_synd </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Syndrome for uncorrectable ECC event. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_u_addr </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address of uncorrectable ECC event. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_105_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 : 16;
     unsigned      ecc_u_synd                                :  8;
     unsigned      reserved0                                 :  2;
     unsigned      ecc_u_addr                                :  6;
#else    /* Little Endian */
     unsigned      ecc_u_addr                                :  6;
     unsigned      reserved0                                 :  2;
     unsigned      ecc_u_synd                                :  8;
     unsigned      obsolete2                                 : 16;
#endif
} ncp_denali_DENALI_CTL_105_5600_t;

/*! @struct ncp_denali_DENALI_CTL_106_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_106_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_106_5600_t
 *
 */
 
typedef struct
{
     unsigned  int                ecc_u_data;
} ncp_denali_DENALI_CTL_106_5600_t;

/*! @struct ncp_denali_DENALI_CTL_107_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_107_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_107_5600_t
 *
 */
 
typedef struct
{
     unsigned  int                ecc_u_data;
} ncp_denali_DENALI_CTL_107_5600_t;

/*! @struct ncp_denali_DENALI_CTL_108_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_108_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_108_5600_t
 *
 */
 
typedef struct
{
     unsigned  int                ecc_c_addr;
} ncp_denali_DENALI_CTL_108_5600_t;

/*! @struct ncp_denali_DENALI_CTL_109_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_109_5600_t\n
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
 *     <td width="30%"> @param ecc_c_synd </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Syndrome for correctable ECC event. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_c_addr </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address of correctable ECC event. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_109_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 : 16;
     unsigned      ecc_c_synd                                :  8;
     unsigned      reserved0                                 :  2;
     unsigned      ecc_c_addr                                :  6;
#else    /* Little Endian */
     unsigned      ecc_c_addr                                :  6;
     unsigned      reserved0                                 :  2;
     unsigned      ecc_c_synd                                :  8;
     unsigned      obsolete2                                 : 16;
#endif
} ncp_denali_DENALI_CTL_109_5600_t;

/*! @struct ncp_denali_DENALI_CTL_110_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_110_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_110_5600_t
 *
 */
 
typedef struct
{
     unsigned  int                ecc_c_data;
} ncp_denali_DENALI_CTL_110_5600_t;

/*! @struct ncp_denali_DENALI_CTL_111_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_111_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_111_5600_t
 *
 */
 
typedef struct
{
     unsigned  int                ecc_c_data;
} ncp_denali_DENALI_CTL_111_5600_t;

/*! @struct ncp_denali_DENALI_CTL_112_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_112_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param ecc_c_id </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Source ID associated with correctable ECC event. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_u_id </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Source ID associated with the uncorrectable ECC event.
 *        READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_112_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      ecc_c_id                                  : 13;
     unsigned      reserved1                                 :  3;
     unsigned      ecc_u_id                                  : 13;
#else    /* Little Endian */
     unsigned      ecc_u_id                                  : 13;
     unsigned      reserved1                                 :  3;
     unsigned      ecc_c_id                                  : 13;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_112_5600_t;

/*! @struct ncp_denali_DENALI_CTL_113_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_113_5600_t\n
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
 *     <td width="30%"> @param zqinit </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Number of cycles needed for a ZQINIT command. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param long_count_mask </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reduces the length of the long counter from 1024 cycles.
 *        The only supported values are 0x00 (1024 cycles),
 *        0x10 (512 clocks), 0x18 (256 clocks), 0x1C (128 clocks),
 *        0x1E (64 clocks) and 0x1F (32 clocks).
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_113_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      reserved0                                 :  4;
     unsigned      zqinit                                    : 12;
     unsigned      reserved1                                 :  3;
     unsigned      long_count_mask                           :  5;
#else    /* Little Endian */
     unsigned      long_count_mask                           :  5;
     unsigned      reserved1                                 :  3;
     unsigned      zqinit                                    : 12;
     unsigned      reserved0                                 :  4;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_113_5600_t;

/*! @struct ncp_denali_DENALI_CTL_114_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_114_5600_t\n
 *   </td>
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
 *   <td width="30%"> Number of cycles needed for a ZQCS command. </td>
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
 *   <td width="30%"> Number of cycles needed for a ZQCL command. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_114_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      zqcs                                      : 12;
     unsigned      reserved1                                 :  4;
     unsigned      zqcl                                      : 12;
#else    /* Little Endian */
     unsigned      zqcl                                      : 12;
     unsigned      reserved1                                 :  4;
     unsigned      zqcs                                      : 12;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_114_5600_t;

/*! @struct ncp_denali_DENALI_CTL_115_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_115_5600_t\n
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
 *     <td width="30%"> @param zq_on_sref_exit </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the type of ZQ calibration performed at self-refresh
 *        exit. Bit (0) selects ZQCS and bit (1) selects ZQCL.
 *        Set either bit to 1 to enable.
 *   </td>
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_115_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 : 16;
     unsigned      reserved0                                 :  6;
     unsigned      zq_on_sref_exit                           :  2;
     unsigned      reserved1                                 :  6;
     unsigned      zq_req                                    :  2;
#else    /* Little Endian */
     unsigned      zq_req                                    :  2;
     unsigned      reserved1                                 :  6;
     unsigned      zq_on_sref_exit                           :  2;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete2                                 : 16;
#endif
} ncp_denali_DENALI_CTL_115_5600_t;

/*! @struct ncp_denali_DENALI_CTL_116_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_116_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_116_5600_t
 *
 */
 
typedef struct
{
     unsigned  int               zq_interval;
} ncp_denali_DENALI_CTL_116_5600_t;

/*! @struct ncp_denali_DENALI_CTL_117_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_117_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param row_diff </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Difference between number of address pins available
 *        and number being used.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bank_diff </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Encoded number of banks on the DRAM(s). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zqcs_rotate </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Selects whether a ZQCS command will calibrate just
 *        one chip select or all chip selects. Set to 1 for
 *        rotating CS.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zq_in_progress </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Indicates that a ZQ command is currently running.
 *        Value of 1 indicates command in progress. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_117_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  5;
     unsigned      row_diff                                  :  3;
     unsigned      reserved1                                 :  6;
     unsigned      bank_diff                                 :  2;
     unsigned      reserved2                                 :  7;
     unsigned      zqcs_rotate                               :  1;
     unsigned      reserved3                                 :  7;
     unsigned      zq_in_progress                            :  1;
#else    /* Little Endian */
     unsigned      zq_in_progress                            :  1;
     unsigned      reserved3                                 :  7;
     unsigned      zqcs_rotate                               :  1;
     unsigned      reserved2                                 :  7;
     unsigned      bank_diff                                 :  2;
     unsigned      reserved1                                 :  6;
     unsigned      row_diff                                  :  3;
     unsigned      reserved0                                 :  5;
#endif
} ncp_denali_DENALI_CTL_117_5600_t;

/*! @struct ncp_denali_DENALI_CTL_118_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_118_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param aprebit </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Location of the auto pre-charge bit in the DRAM address. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved4 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved for future use. Refer to the regconfig files
 *        for the default programming.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved5 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved for future use. Refer to the regconfig files
 *        for the default programming.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved6 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param col_diff </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Difference between number of column pins available
 *        and number being used.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_118_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved3                                 :  4;
     unsigned      aprebit                                   :  4;
     unsigned      reserved4                                 :  7;
     unsigned      reserved2                                 :  1;
     unsigned      reserved5                                 :  3;
     unsigned      reserved1                                 :  5;
     unsigned      reserved6                                 :  4;
     unsigned      col_diff                                  :  4;
#else    /* Little Endian */
     unsigned      col_diff                                  :  4;
     unsigned      reserved6                                 :  4;
     unsigned      reserved1                                 :  5;
     unsigned      reserved5                                 :  3;
     unsigned      reserved2                                 :  1;
     unsigned      reserved4                                 :  7;
     unsigned      aprebit                                   :  4;
     unsigned      reserved3                                 :  4;
#endif
} ncp_denali_DENALI_CTL_118_5600_t;

/*! @struct ncp_denali_DENALI_CTL_119_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_119_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved4 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved for future use. Refer to the regconfig files
 *        for the default programming.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved5 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param addr_cmp_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enable address collision detection as a rule for command
 *        queue placement. Set to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param command_age_count </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Initial value of individual command aging counters
 *        for command aging.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param age_count </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Initial value of master aging-rate counter for command
 *        aging.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_119_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved4                                 :  7;
     unsigned      reserved3                                 :  1;
     unsigned      reserved5                                 :  7;
     unsigned      addr_cmp_en                               :  1;
     unsigned      command_age_count                         :  8;
     unsigned      age_count                                 :  8;
#else    /* Little Endian */
     unsigned      age_count                                 :  8;
     unsigned      command_age_count                         :  8;
     unsigned      addr_cmp_en                               :  1;
     unsigned      reserved5                                 :  7;
     unsigned      reserved3                                 :  1;
     unsigned      reserved4                                 :  7;
#endif
} ncp_denali_DENALI_CTL_119_5600_t;

/*! @struct ncp_denali_DENALI_CTL_120_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_120_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param rw_same_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Enable read/write grouping as a rule for command queue
 *        placement. Set to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param priority_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enable priority as a rule for command queue placement.
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
 *     <td width="30%"> @param placement_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enable placement logic for command queue. Set to 1
 *        to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bank_split_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enable bank splitting as a rule for command queue
 *        placement. Set to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_120_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      rw_same_en                                :  1;
     unsigned      reserved1                                 :  7;
     unsigned      priority_en                               :  1;
     unsigned      reserved2                                 :  7;
     unsigned      placement_en                              :  1;
     unsigned      reserved3                                 :  7;
     unsigned      bank_split_en                             :  1;
#else    /* Little Endian */
     unsigned      bank_split_en                             :  1;
     unsigned      reserved3                                 :  7;
     unsigned      placement_en                              :  1;
     unsigned      reserved2                                 :  7;
     unsigned      priority_en                               :  1;
     unsigned      reserved1                                 :  7;
     unsigned      rw_same_en                                :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_120_5600_t;

/*! @struct ncp_denali_DENALI_CTL_121_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_121_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rw_same_page_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enable page grouping when read/write grouping as a
 *        rule for command queue placement. This is only valid
 *        when the RW_SAME_EN parameter is set. Set to 1 to
 *        enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_121_5600_t
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
     unsigned      reserved3                                 :  7;
     unsigned      rw_same_page_en                           :  1;
#else    /* Little Endian */
     unsigned      rw_same_page_en                           :  1;
     unsigned      reserved3                                 :  7;
     unsigned      cs_same_en                                :  1;
     unsigned      reserved2                                 :  7;
     unsigned      w2r_split_en                              :  1;
     unsigned      reserved1                                 :  7;
     unsigned      disable_rw_group_w_bnk_conflict           :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_121_5600_t;

/*! @struct ncp_denali_DENALI_CTL_122_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_122_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param inhibit_dram_cmd </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Inhibit read/write command traffic and associated
 *        bank commands. Set to 1 to inhibit.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param disable_rd_interleave </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Disable read data interleaving for commands from the
 *        same port, regardless of the requestor ID.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param swap_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enable command swapping logic in execution unit. Set
 *        to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_122_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      inhibit_dram_cmd                          :  1;
     unsigned      reserved1                                 :  7;
     unsigned      disable_rd_interleave                     :  1;
     unsigned      reserved2                                 :  7;
     unsigned      swap_en                                   :  1;
     unsigned      reserved3                                 :  4;
     unsigned      num_q_entries_act_disable                 :  4;
#else    /* Little Endian */
     unsigned      num_q_entries_act_disable                 :  4;
     unsigned      reserved3                                 :  4;
     unsigned      swap_en                                   :  1;
     unsigned      reserved2                                 :  7;
     unsigned      disable_rd_interleave                     :  1;
     unsigned      reserved1                                 :  7;
     unsigned      inhibit_dram_cmd                          :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_122_5600_t;

/*! @struct ncp_denali_DENALI_CTL_123_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_123_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param memdata_ratio_0 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines the ratio of the DRAM device size on chip
 *        select 0 to the memory data width. Program with the
 *        log2 ratio of the memory data width to the device
 *        data width.
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
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param burst_on_fly_bit </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Identifies the burst-on-fly bit in the memory mode
 *        registers.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cs_map </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines which chip selects are active. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_123_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  5;
     unsigned      memdata_ratio_0                           :  3;
     unsigned      reserved1                                 :  7;
     unsigned      reduc                                     :  1;
     unsigned      reserved2                                 :  4;
     unsigned      burst_on_fly_bit                          :  4;
     unsigned      reserved3                                 :  4;
     unsigned      cs_map                                    :  4;
#else    /* Little Endian */
     unsigned      cs_map                                    :  4;
     unsigned      reserved3                                 :  4;
     unsigned      burst_on_fly_bit                          :  4;
     unsigned      reserved2                                 :  4;
     unsigned      reduc                                     :  1;
     unsigned      reserved1                                 :  7;
     unsigned      memdata_ratio_0                           :  3;
     unsigned      reserved0                                 :  5;
#endif
} ncp_denali_DENALI_CTL_123_5600_t;

/*! @struct ncp_denali_DENALI_CTL_124_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_124_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param controller_busy </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Indicator that the controller is processing a command.
 *        Evaluates all ports for outstanding transactions.
 *        Value of 1 indicates controller busy. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param in_order_accept </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Forces the controller to accept commands in the order
 *        in which they are placed in the command queue.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param q_fullness </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Quantity that determines command queue full. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param memdata_ratio_1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the ratio of the DRAM device size on chip
 *        select 1 to the memory data width. Program with the
 *        log2 ratio of the memory data width to the device
 *        data width.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_124_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      controller_busy                           :  1;
     unsigned      reserved1                                 :  7;
     unsigned      in_order_accept                           :  1;
     unsigned      reserved2                                 :  4;
     unsigned      q_fullness                                :  4;
     unsigned      reserved3                                 :  5;
     unsigned      memdata_ratio_1                           :  3;
#else    /* Little Endian */
     unsigned      memdata_ratio_1                           :  3;
     unsigned      reserved3                                 :  5;
     unsigned      q_fullness                                :  4;
     unsigned      reserved2                                 :  4;
     unsigned      in_order_accept                           :  1;
     unsigned      reserved1                                 :  7;
     unsigned      controller_busy                           :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_124_5600_t;

/*! @struct ncp_denali_DENALI_CTL_125_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_125_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param rd_preamble_training_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Enable read preamble training during data eye training.
 *        Set to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param preamble_support </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Selection of one or two cycle preamble for read and
 *        write burst transfers.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ctrlupd_req_per_aref_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enable an automatic controller-initiated update (dfi_ctrlupd_req)
 *        after every refresh. Set to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ctrlupd_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Assert the DFI controller-initiated update request
 *        signal dfi_ctrlupd_req. Set to 1 to trigger. WRITE-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_125_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      rd_preamble_training_en                   :  1;
     unsigned      reserved1                                 :  6;
     unsigned      preamble_support                          :  2;
     unsigned      reserved2                                 :  7;
     unsigned      ctrlupd_req_per_aref_en                   :  1;
     unsigned      reserved3                                 :  7;
     unsigned      ctrlupd_req                               :  1;
#else    /* Little Endian */
     unsigned      ctrlupd_req                               :  1;
     unsigned      reserved3                                 :  7;
     unsigned      ctrlupd_req_per_aref_en                   :  1;
     unsigned      reserved2                                 :  7;
     unsigned      preamble_support                          :  2;
     unsigned      reserved1                                 :  6;
     unsigned      rd_preamble_training_en                   :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_125_5600_t;

/*! @struct ncp_denali_DENALI_CTL_126_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_126_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param dfi_error </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Indicates that the DFI error flag has been asserted.
 *        READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rd_dbi_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enables controller support of DRAM DBI feature for
 *        read data with DDR4 devices. Set to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wr_dbi_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enables controller support of DRAM DBI feature for
 *        write data with DDR4 devices. Set to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_126_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      dfi_error                                 : 10;
     unsigned      reserved1                                 :  7;
     unsigned      rd_dbi_en                                 :  1;
     unsigned      reserved2                                 :  7;
     unsigned      wr_dbi_en                                 :  1;
#else    /* Little Endian */
     unsigned      wr_dbi_en                                 :  1;
     unsigned      reserved2                                 :  7;
     unsigned      rd_dbi_en                                 :  1;
     unsigned      reserved1                                 :  7;
     unsigned      dfi_error                                 : 10;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_126_5600_t;

/*! @struct ncp_denali_DENALI_CTL_127_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_127_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dfi_error_info </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Holds the encoded DFI error type associated with the
 *        DFI_ERROR parameter assertion. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_127_5600_t
 *
 */
 
typedef struct
{
     unsigned  int            dfi_error_info;
} ncp_denali_DENALI_CTL_127_5600_t;

/*! @struct ncp_denali_DENALI_CTL_128_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_128_5600_t\n
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
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reserved for future use. Refer to the regconfig files
 *        for the default programming.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved4 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bg_rotate_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enable bank group rotation. Set to 1 to enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dfi_error_info </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Holds the encoded DFI error type associated with the
 *        DFI_ERROR parameter assertion. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_128_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      reserved3                                 :  7;
     unsigned      reserved2                                 :  1;
     unsigned      reserved4                                 :  7;
     unsigned      bg_rotate_en                              :  1;
     unsigned      dfi_error_info                            :  8;
#else    /* Little Endian */
     unsigned      dfi_error_info                            :  8;
     unsigned      bg_rotate_en                              :  1;
     unsigned      reserved4                                 :  7;
     unsigned      reserved2                                 :  1;
     unsigned      reserved3                                 :  7;
     unsigned      obsolete3                                 :  8;
#endif
} ncp_denali_DENALI_CTL_128_5600_t;

/*! @struct ncp_denali_DENALI_CTL_129_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_129_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_129_5600_t
 *
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_129_5600_t;

/*! @struct ncp_denali_DENALI_CTL_130_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_130_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_130_5600_t
 *
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_130_5600_t;

/*! @struct ncp_denali_DENALI_CTL_131_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_131_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_131_5600_t
 *
 */
 
typedef struct
{
     unsigned  int                 obsolete0;
} ncp_denali_DENALI_CTL_131_5600_t;

/*! @struct ncp_denali_DENALI_CTL_132_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_132_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_132_5600_t
 *
 */
 
typedef struct
{
     unsigned  int         out_of_range_addr;
} ncp_denali_DENALI_CTL_132_5600_t;

/*! @struct ncp_denali_DENALI_CTL_133_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_133_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param out_of_range_type </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Type of command that caused an out-of-range interrupt.
 *        READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param out_of_range_length </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Length of command that caused an out-of-range interrupt.
 *        READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param out_of_range_addr </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address of command that caused an out-of-range interrupt.
 *        READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_133_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      out_of_range_type                         :  7;
     unsigned      reserved1                                 :  3;
     unsigned      out_of_range_length                       : 13;
     unsigned      reserved2                                 :  2;
     unsigned      out_of_range_addr                         :  6;
#else    /* Little Endian */
     unsigned      out_of_range_addr                         :  6;
     unsigned      reserved2                                 :  2;
     unsigned      out_of_range_length                       : 13;
     unsigned      reserved1                                 :  3;
     unsigned      out_of_range_type                         :  7;
     unsigned      reserved0                                 :  1;
#endif
} ncp_denali_DENALI_CTL_133_5600_t;

/*! @struct ncp_denali_DENALI_CTL_134_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_134_5600_t\n
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
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param out_of_range_source_id </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Source ID of command that caused an out-of-range interrupt.
 *        READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_134_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      reserved0                                 :  3;
     unsigned      out_of_range_source_id                    : 13;
#else    /* Little Endian */
     unsigned      out_of_range_source_id                    : 13;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_134_5600_t;

/*! @struct ncp_denali_DENALI_CTL_135_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_135_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_135_5600_t
 *
 */
 
typedef struct
{
     unsigned  int             bist_exp_data;
} ncp_denali_DENALI_CTL_135_5600_t;

/*! @struct ncp_denali_DENALI_CTL_136_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_136_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_136_5600_t
 *
 */
 
typedef struct
{
     unsigned  int             bist_exp_data;
} ncp_denali_DENALI_CTL_136_5600_t;

/*! @struct ncp_denali_DENALI_CTL_137_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_137_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_137_5600_t
 *
 */
 
typedef struct
{
     unsigned  int             bist_exp_data;
} ncp_denali_DENALI_CTL_137_5600_t;

/*! @struct ncp_denali_DENALI_CTL_138_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_138_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_138_5600_t
 *
 */
 
typedef struct
{
     unsigned  int             bist_exp_data;
} ncp_denali_DENALI_CTL_138_5600_t;

/*! @struct ncp_denali_DENALI_CTL_139_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_139_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_139_5600_t
 *
 */
 
typedef struct
{
     unsigned  int             bist_exp_data;
} ncp_denali_DENALI_CTL_139_5600_t;

/*! @struct ncp_denali_DENALI_CTL_140_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_140_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_140_5600_t
 *
 */
 
typedef struct
{
     unsigned  int             bist_exp_data;
} ncp_denali_DENALI_CTL_140_5600_t;

/*! @struct ncp_denali_DENALI_CTL_141_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_141_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_141_5600_t
 *
 */
 
typedef struct
{
     unsigned  int             bist_exp_data;
} ncp_denali_DENALI_CTL_141_5600_t;

/*! @struct ncp_denali_DENALI_CTL_142_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_142_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_142_5600_t
 *
 */
 
typedef struct
{
     unsigned  int             bist_exp_data;
} ncp_denali_DENALI_CTL_142_5600_t;

/*! @struct ncp_denali_DENALI_CTL_143_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_143_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_143_5600_t
 *
 */
 
typedef struct
{
     unsigned  int            bist_fail_data;
} ncp_denali_DENALI_CTL_143_5600_t;

/*! @struct ncp_denali_DENALI_CTL_144_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_144_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_144_5600_t
 *
 */
 
typedef struct
{
     unsigned  int            bist_fail_data;
} ncp_denali_DENALI_CTL_144_5600_t;

/*! @struct ncp_denali_DENALI_CTL_145_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_145_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_145_5600_t
 *
 */
 
typedef struct
{
     unsigned  int            bist_fail_data;
} ncp_denali_DENALI_CTL_145_5600_t;

/*! @struct ncp_denali_DENALI_CTL_146_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_146_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_146_5600_t
 *
 */
 
typedef struct
{
     unsigned  int            bist_fail_data;
} ncp_denali_DENALI_CTL_146_5600_t;

/*! @struct ncp_denali_DENALI_CTL_147_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_147_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_147_5600_t
 *
 */
 
typedef struct
{
     unsigned  int            bist_fail_data;
} ncp_denali_DENALI_CTL_147_5600_t;

/*! @struct ncp_denali_DENALI_CTL_148_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_148_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_148_5600_t
 *
 */
 
typedef struct
{
     unsigned  int            bist_fail_data;
} ncp_denali_DENALI_CTL_148_5600_t;

/*! @struct ncp_denali_DENALI_CTL_149_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_149_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_149_5600_t
 *
 */
 
typedef struct
{
     unsigned  int            bist_fail_data;
} ncp_denali_DENALI_CTL_149_5600_t;

/*! @struct ncp_denali_DENALI_CTL_150_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_150_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_150_5600_t
 *
 */
 
typedef struct
{
     unsigned  int            bist_fail_data;
} ncp_denali_DENALI_CTL_150_5600_t;

/*! @struct ncp_denali_DENALI_CTL_151_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_151_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_151_5600_t
 *
 */
 
typedef struct
{
     unsigned  int            bist_fail_addr;
} ncp_denali_DENALI_CTL_151_5600_t;

/*! @struct ncp_denali_DENALI_CTL_152_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_152_5600_t\n
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
 *     <td width="30%"> @param bist_fail_addr </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address of BIST error. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_152_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      bist_fail_addr                            :  6;
#else    /* Little Endian */
     unsigned      bist_fail_addr                            :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_152_5600_t;

/*! @struct ncp_denali_DENALI_CTL_153_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_153_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_153_5600_t
 *
 */
 
typedef struct
{
     unsigned  int       port_cmd_error_addr;
} ncp_denali_DENALI_CTL_153_5600_t;

/*! @struct ncp_denali_DENALI_CTL_154_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_154_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param port_cmd_error_type </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Type of error and access type that caused the PORT
 *        command error. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param port_cmd_error_id </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Source ID of command that caused the PORT command
 *        error. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param port_cmd_error_addr </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address of command that caused the PORT command error.
 *        READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_154_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  5;
     unsigned      port_cmd_error_type                       :  3;
     unsigned      reserved1                                 :  3;
     unsigned      port_cmd_error_id                         : 13;
     unsigned      reserved2                                 :  2;
     unsigned      port_cmd_error_addr                       :  6;
#else    /* Little Endian */
     unsigned      port_cmd_error_addr                       :  6;
     unsigned      reserved2                                 :  2;
     unsigned      port_cmd_error_id                         : 13;
     unsigned      reserved1                                 :  3;
     unsigned      port_cmd_error_type                       :  3;
     unsigned      reserved0                                 :  5;
#endif
} ncp_denali_DENALI_CTL_154_5600_t;

/*! @struct ncp_denali_DENALI_CTL_155_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_155_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param odt_rd_map_cs1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Determines which chip(s) will have termination when
 *        a read occurs on chip select 1. Set bit X to enable
 *        termination on csX when cs1 is performing a read.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odt_wr_map_cs0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Determines which chip(s) will have termination when
 *        a write occurs on chip select 0. Set bit X to enable
 *        termination on csX when cs0 is performing a write.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odt_rd_map_cs0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Determines which chip(s) will have termination when
 *        a read occurs on chip select 0. Set bit X to enable
 *        termination on csX when cs0 is performing a read.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_155_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      odt_wr_map_cs1                            :  4;
     unsigned      reserved1                                 :  4;
     unsigned      odt_rd_map_cs1                            :  4;
     unsigned      reserved2                                 :  4;
     unsigned      odt_wr_map_cs0                            :  4;
     unsigned      reserved3                                 :  4;
     unsigned      odt_rd_map_cs0                            :  4;
#else    /* Little Endian */
     unsigned      odt_rd_map_cs0                            :  4;
     unsigned      reserved3                                 :  4;
     unsigned      odt_wr_map_cs0                            :  4;
     unsigned      reserved2                                 :  4;
     unsigned      odt_rd_map_cs1                            :  4;
     unsigned      reserved1                                 :  4;
     unsigned      odt_wr_map_cs1                            :  4;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_155_5600_t;

/*! @struct ncp_denali_DENALI_CTL_156_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_156_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param odt_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Enable support of DRAM ODT. When enabled, controller
 *        will assert and de-assert ODT output to DRAM as needed.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param todth_rd </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the DRAM minimum ODT high time after an ODT
 *        assertion for a read command.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param todth_wr </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the DRAM minimum ODT high time after an ODT
 *        assertion for a write command.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param todtl_2cmd </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the DRAM delay from an ODT de-assertion to
 *        the next non-write, non-read command.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_156_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      odt_en                                    :  1;
     unsigned      reserved1                                 :  4;
     unsigned      todth_rd                                  :  4;
     unsigned      reserved2                                 :  4;
     unsigned      todth_wr                                  :  4;
     unsigned      todtl_2cmd                                :  8;
#else    /* Little Endian */
     unsigned      todtl_2cmd                                :  8;
     unsigned      todth_wr                                  :  4;
     unsigned      reserved2                                 :  4;
     unsigned      todth_rd                                  :  4;
     unsigned      reserved1                                 :  4;
     unsigned      odt_en                                    :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_156_5600_t;

/*! @struct ncp_denali_DENALI_CTL_157_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_157_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param r2w_diffcs_dly </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Additional delay to insert between reads and writes
 *        to different chip selects. Program to a non-zero value.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param r2r_diffcs_dly </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Additional delay to insert between reads to different
 *        chip selects. Program to a non-zero value.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rd_to_odth </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the delay from a read command to ODT assertion. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved4 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved for future use. Refer to the regconfig files
 *        for the default programming.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_157_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved1                                 :  3;
     unsigned      r2w_diffcs_dly                            :  5;
     unsigned      reserved2                                 :  3;
     unsigned      r2r_diffcs_dly                            :  5;
     unsigned      reserved3                                 :  3;
     unsigned      rd_to_odth                                :  5;
     unsigned      reserved4                                 :  3;
     unsigned      reserved0                                 :  5;
#else    /* Little Endian */
     unsigned      reserved0                                 :  5;
     unsigned      reserved4                                 :  3;
     unsigned      rd_to_odth                                :  5;
     unsigned      reserved3                                 :  3;
     unsigned      r2r_diffcs_dly                            :  5;
     unsigned      reserved2                                 :  3;
     unsigned      r2w_diffcs_dly                            :  5;
     unsigned      reserved1                                 :  3;
#endif
} ncp_denali_DENALI_CTL_157_5600_t;

/*! @struct ncp_denali_DENALI_CTL_158_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_158_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param r2w_samecs_dly </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Additional delay to insert between reads and writes
 *        to the same chip select. Program to a non-zero value.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param r2r_samecs_dly </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Additional delay to insert between two reads to the
 *        same chip select. Any value including 0x0 supported.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param w2w_diffcs_dly </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Additional delay to insert between writes to different
 *        chip selects. Program to a non-zero value.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param w2r_diffcs_dly </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Additional delay to insert between writes and reads
 *        to different chip selects. Allowed programming dependent
 *        on memory system.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_158_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      r2w_samecs_dly                            :  5;
     unsigned      reserved1                                 :  3;
     unsigned      r2r_samecs_dly                            :  5;
     unsigned      reserved2                                 :  3;
     unsigned      w2w_diffcs_dly                            :  5;
     unsigned      reserved3                                 :  3;
     unsigned      w2r_diffcs_dly                            :  5;
#else    /* Little Endian */
     unsigned      w2r_diffcs_dly                            :  5;
     unsigned      reserved3                                 :  3;
     unsigned      w2w_diffcs_dly                            :  5;
     unsigned      reserved2                                 :  3;
     unsigned      r2r_samecs_dly                            :  5;
     unsigned      reserved1                                 :  3;
     unsigned      r2w_samecs_dly                            :  5;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_158_5600_t;

/*! @struct ncp_denali_DENALI_CTL_159_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_159_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param swlvl_load </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> User request to load delays and execute software leveling.
 *        Set to 1 to trigger. WRITE-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sw_leveling_mode </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the leveling operation for software leveling.
 *        Clear to 0 for none, program to 1 for write leveling,
 *        program to 2 for data eye training, or program to
 *        3 for gate training.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param w2w_samecs_dly </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Additional delay to insert between two writes to the
 *        same chip select. Any value including 0x0 supported.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param w2r_samecs_dly </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Additional delay to insert between writes and reads
 *        to the same chip select.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_159_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      swlvl_load                                :  1;
     unsigned      reserved1                                 :  5;
     unsigned      sw_leveling_mode                          :  3;
     unsigned      reserved2                                 :  3;
     unsigned      w2w_samecs_dly                            :  5;
     unsigned      reserved3                                 :  3;
     unsigned      w2r_samecs_dly                            :  5;
#else    /* Little Endian */
     unsigned      w2r_samecs_dly                            :  5;
     unsigned      reserved3                                 :  3;
     unsigned      w2w_samecs_dly                            :  5;
     unsigned      reserved2                                 :  3;
     unsigned      sw_leveling_mode                          :  3;
     unsigned      reserved1                                 :  5;
     unsigned      swlvl_load                                :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_159_5600_t;

/*! @struct ncp_denali_DENALI_CTL_160_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_160_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param swlvl_resp_0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Leveling response for data slice 0. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param swlvl_op_done </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Signals that software leveling is currently in progress.
 *        Value of 1 indicates operation complete. READ-ONLY
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_160_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      swlvl_resp_0                              :  1;
     unsigned      reserved1                                 :  7;
     unsigned      swlvl_op_done                             :  1;
     unsigned      reserved2                                 :  7;
     unsigned      swlvl_exit                                :  1;
     unsigned      reserved3                                 :  7;
     unsigned      swlvl_start                               :  1;
#else    /* Little Endian */
     unsigned      swlvl_start                               :  1;
     unsigned      reserved3                                 :  7;
     unsigned      swlvl_exit                                :  1;
     unsigned      reserved2                                 :  7;
     unsigned      swlvl_op_done                             :  1;
     unsigned      reserved1                                 :  7;
     unsigned      swlvl_resp_0                              :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_160_5600_t;

/*! @struct ncp_denali_DENALI_CTL_161_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_161_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param swlvl_resp_4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Leveling response for data slice 4. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param swlvl_resp_3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Leveling response for data slice 3. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param swlvl_resp_2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Leveling response for data slice 2. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param swlvl_resp_1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Leveling response for data slice 1. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_161_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      swlvl_resp_4                              :  1;
     unsigned      reserved1                                 :  7;
     unsigned      swlvl_resp_3                              :  1;
     unsigned      reserved2                                 :  7;
     unsigned      swlvl_resp_2                              :  1;
     unsigned      reserved3                                 :  7;
     unsigned      swlvl_resp_1                              :  1;
#else    /* Little Endian */
     unsigned      swlvl_resp_1                              :  1;
     unsigned      reserved3                                 :  7;
     unsigned      swlvl_resp_2                              :  1;
     unsigned      reserved2                                 :  7;
     unsigned      swlvl_resp_3                              :  1;
     unsigned      reserved1                                 :  7;
     unsigned      swlvl_resp_4                              :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_161_5600_t;

/*! @struct ncp_denali_DENALI_CTL_162_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_162_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param swlvl_resp_8 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Leveling response for data slice 8. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param swlvl_resp_7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Leveling response for data slice 7. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param swlvl_resp_6 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Leveling response for data slice 6. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param swlvl_resp_5 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Leveling response for data slice 5. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_162_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      swlvl_resp_8                              :  1;
     unsigned      reserved1                                 :  7;
     unsigned      swlvl_resp_7                              :  1;
     unsigned      reserved2                                 :  7;
     unsigned      swlvl_resp_6                              :  1;
     unsigned      reserved3                                 :  7;
     unsigned      swlvl_resp_5                              :  1;
#else    /* Little Endian */
     unsigned      swlvl_resp_5                              :  1;
     unsigned      reserved3                                 :  7;
     unsigned      swlvl_resp_6                              :  1;
     unsigned      reserved2                                 :  7;
     unsigned      swlvl_resp_7                              :  1;
     unsigned      reserved1                                 :  7;
     unsigned      swlvl_resp_8                              :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_162_5600_t;

/*! @struct ncp_denali_DENALI_CTL_163_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_163_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param wlmrd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Delay from issuing MRS to first write leveling strobe. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wldqsen </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Delay from issuing MRS to first DQS strobe for write
 *        leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_cs </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Specifies the target chip select for the write leveling
 *        operation initiated through the WRLVL_REQ parameter.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> User request to initiate write leveling. Set to 1
 *        to trigger. WRITE-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_163_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  2;
     unsigned      wlmrd                                     :  6;
     unsigned      reserved1                                 :  2;
     unsigned      wldqsen                                   :  6;
     unsigned      reserved2                                 :  6;
     unsigned      wrlvl_cs                                  :  2;
     unsigned      reserved3                                 :  7;
     unsigned      wrlvl_req                                 :  1;
#else    /* Little Endian */
     unsigned      wrlvl_req                                 :  1;
     unsigned      reserved3                                 :  7;
     unsigned      wrlvl_cs                                  :  2;
     unsigned      reserved2                                 :  6;
     unsigned      wldqsen                                   :  6;
     unsigned      reserved1                                 :  2;
     unsigned      wlmrd                                     :  6;
     unsigned      reserved0                                 :  2;
#endif
} ncp_denali_DENALI_CTL_163_5600_t;

/*! @struct ncp_denali_DENALI_CTL_164_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_164_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param dfi_phy_wrlvl_mode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Specifies the PHY support for DFI write leveling.
 *        Set to 1 for supported.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_interval </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Number of long count sequences counted between automatic
 *        write leveling commands.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enable the MC write leveling module. Set to 1 to enable. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_164_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      dfi_phy_wrlvl_mode                        :  1;
     unsigned      wrlvl_interval                            : 16;
     unsigned      reserved1                                 :  7;
     unsigned      wrlvl_en                                  :  1;
#else    /* Little Endian */
     unsigned      wrlvl_en                                  :  1;
     unsigned      reserved1                                 :  7;
     unsigned      wrlvl_interval                            : 16;
     unsigned      dfi_phy_wrlvl_mode                        :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_164_5600_t;

/*! @struct ncp_denali_DENALI_CTL_165_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_165_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param wrlvl_resp_mask </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Mask for the dfi_wrlvl_resp signal during write leveling. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_on_sref_exit </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enables automatic write leveling on a self-refresh
 *        exit. Set to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_periodic </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enables the use of the dfi_lvl_periodic signal during
 *        write leveling. Set to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_165_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      wrlvl_resp_mask                           :  9;
     unsigned      reserved1                                 :  7;
     unsigned      wrlvl_on_sref_exit                        :  1;
     unsigned      reserved2                                 :  7;
     unsigned      wrlvl_periodic                            :  1;
#else    /* Little Endian */
     unsigned      wrlvl_periodic                            :  1;
     unsigned      reserved2                                 :  7;
     unsigned      wrlvl_on_sref_exit                        :  1;
     unsigned      reserved1                                 :  7;
     unsigned      wrlvl_resp_mask                           :  9;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_165_5600_t;

/*! @struct ncp_denali_DENALI_CTL_166_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_166_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param wrlvl_error_status </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Holds the error associated with the write level error
 *        interrupt. Bit (0) set indicates a TDFI_WRLVL_MAX
 *        parameter violation and bit (1) set indicates a TDFI_WRLVL_RESP
 *        parameter violation. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_cs_map </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the chip select map for write leveling operations.
 *        Bit (0) controls cs0, bit (1) controls cs1, etc. Set
 *        each bit to 1 to enable chip for write leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_rotate </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enables rotational CS for interval write leveling.
 *        Set to 1 for rotating CS.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_aref_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enables refreshes and other non-data commands to execute
 *        in the middle of write leveling. Set to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_166_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      wrlvl_error_status                        :  2;
     unsigned      reserved1                                 :  4;
     unsigned      wrlvl_cs_map                              :  4;
     unsigned      reserved2                                 :  7;
     unsigned      wrlvl_rotate                              :  1;
     unsigned      reserved3                                 :  7;
     unsigned      wrlvl_aref_en                             :  1;
#else    /* Little Endian */
     unsigned      wrlvl_aref_en                             :  1;
     unsigned      reserved3                                 :  7;
     unsigned      wrlvl_rotate                              :  1;
     unsigned      reserved2                                 :  7;
     unsigned      wrlvl_cs_map                              :  4;
     unsigned      reserved1                                 :  4;
     unsigned      wrlvl_error_status                        :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_166_5600_t;

/*! @struct ncp_denali_DENALI_CTL_167_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_167_5600_t\n
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
 *   <td width="30%"> Specifies the target chip select for the data eye
 *        training operation initiated through the RDLVL_REQ
 *        parameter or the gate training operation initiated
 *        through the RDLVL_GATE_REQ parameter.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> User request to initiate gate training. Set to 1 to
 *        trigger. WRITE-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> User request to initiate data eye training. Set to
 *        1 to trigger. WRITE-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_167_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      rdlvl_cs                                  :  2;
     unsigned      reserved1                                 :  7;
     unsigned      rdlvl_gate_req                            :  1;
     unsigned      reserved2                                 :  7;
     unsigned      rdlvl_req                                 :  1;
#else    /* Little Endian */
     unsigned      rdlvl_req                                 :  1;
     unsigned      reserved2                                 :  7;
     unsigned      rdlvl_gate_req                            :  1;
     unsigned      reserved1                                 :  7;
     unsigned      rdlvl_cs                                  :  2;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete3                                 :  8;
#endif
} ncp_denali_DENALI_CTL_167_5600_t;

/*! @struct ncp_denali_DENALI_CTL_168_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_168_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_pat_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Non-default pattern 0 used for data eye training and
 *        gate training with DDR4 devices.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_168_5600_t
 *
 */
 
typedef struct
{
     unsigned  int               rdlvl_pat_0;
} ncp_denali_DENALI_CTL_168_5600_t;

/*! @struct ncp_denali_DENALI_CTL_169_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_169_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_format_0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPR read format used with non-default pattern 0 for
 *        data eye training and gate training with DDR4 devices.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_169_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  6;
     unsigned      rdlvl_format_0                            :  2;
#else    /* Little Endian */
     unsigned      rdlvl_format_0                            :  2;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_169_5600_t;

/*! @struct ncp_denali_DENALI_CTL_170_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_170_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_pat_1 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Non-default pattern 1 used for data eye training and
 *        gate training with DDR4 devices.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_170_5600_t
 *
 */
 
typedef struct
{
     unsigned  int               rdlvl_pat_1;
} ncp_denali_DENALI_CTL_170_5600_t;

/*! @struct ncp_denali_DENALI_CTL_171_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_171_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_format_1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPR read format used with non-default pattern 1 for
 *        data eye training and gate training with DDR4 devices.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_171_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  6;
     unsigned      rdlvl_format_1                            :  2;
#else    /* Little Endian */
     unsigned      rdlvl_format_1                            :  2;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_171_5600_t;

/*! @struct ncp_denali_DENALI_CTL_172_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_172_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_pat_2 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Non-default pattern 2 used for data eye training and
 *        gate training with DDR4 devices.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_172_5600_t
 *
 */
 
typedef struct
{
     unsigned  int               rdlvl_pat_2;
} ncp_denali_DENALI_CTL_172_5600_t;

/*! @struct ncp_denali_DENALI_CTL_173_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_173_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_format_2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPR read format used with non-default pattern 2 for
 *        data eye training and gate training with DDR4 devices.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_173_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  6;
     unsigned      rdlvl_format_2                            :  2;
#else    /* Little Endian */
     unsigned      rdlvl_format_2                            :  2;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_173_5600_t;

/*! @struct ncp_denali_DENALI_CTL_174_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_174_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_pat_3 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Non-default pattern 3 used for data eye training and
 *        gate training with DDR4 devices.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_174_5600_t
 *
 */
 
typedef struct
{
     unsigned  int               rdlvl_pat_3;
} ncp_denali_DENALI_CTL_174_5600_t;

/*! @struct ncp_denali_DENALI_CTL_175_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_175_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param dfi_phy_rdlvl_mode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Specifies the PHY support for DFI data eye training.
 *        Set to 1 for supported.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_seq_en </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Specifies the pattern, format and MPR for gate training. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_seq_en </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Specifies the pattern, format and MPR for data eye
 *        training.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_format_3 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> MPR read format used with non-default pattern 3 for
 *        data eye training and gate training with DDR4 devices.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_175_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      dfi_phy_rdlvl_mode                        :  1;
     unsigned      reserved1                                 :  4;
     unsigned      rdlvl_gate_seq_en                         :  4;
     unsigned      reserved2                                 :  4;
     unsigned      rdlvl_seq_en                              :  4;
     unsigned      reserved3                                 :  6;
     unsigned      rdlvl_format_3                            :  2;
#else    /* Little Endian */
     unsigned      rdlvl_format_3                            :  2;
     unsigned      reserved3                                 :  6;
     unsigned      rdlvl_seq_en                              :  4;
     unsigned      reserved2                                 :  4;
     unsigned      rdlvl_gate_seq_en                         :  4;
     unsigned      reserved1                                 :  4;
     unsigned      dfi_phy_rdlvl_mode                        :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_175_5600_t;

/*! @struct ncp_denali_DENALI_CTL_176_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_176_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param rdlvl_gate_periodic </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Enables the use of the dfi_lvl_periodic signal during
 *        gate training. Set to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_on_sref_exit </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enables automatic data eye training on a self-refresh
 *        exit. Set to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_periodic </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enables the use of the dfi_lvl_periodic signal during
 *        data eye training. Set to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dfi_phy_rdlvl_gate_mode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Specifies the PHY support for DFI gate training. Set
 *        to 1 for supported.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_176_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      rdlvl_gate_periodic                       :  1;
     unsigned      reserved1                                 :  7;
     unsigned      rdlvl_on_sref_exit                        :  1;
     unsigned      reserved2                                 :  7;
     unsigned      rdlvl_periodic                            :  1;
     unsigned      reserved3                                 :  7;
     unsigned      dfi_phy_rdlvl_gate_mode                   :  1;
#else    /* Little Endian */
     unsigned      dfi_phy_rdlvl_gate_mode                   :  1;
     unsigned      reserved3                                 :  7;
     unsigned      rdlvl_periodic                            :  1;
     unsigned      reserved2                                 :  7;
     unsigned      rdlvl_on_sref_exit                        :  1;
     unsigned      reserved1                                 :  7;
     unsigned      rdlvl_gate_periodic                       :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_176_5600_t;

/*! @struct ncp_denali_DENALI_CTL_177_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_177_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param rdlvl_gate_rotate </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Enables rotational CS for interval gate training.
 *        Set to 1 for rotating CS.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_rotate </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enables rotational CS for interval data eye training.
 *        Set to 1 for rotating CS.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_aref_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enables refreshes and other non-data commands to execute
 *        in the middle of data eye training or gate training.
 *        Set to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_on_sref_exit </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enables automatic gate training on a self-refresh
 *        exit. Set to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_177_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      rdlvl_gate_rotate                         :  1;
     unsigned      reserved1                                 :  7;
     unsigned      rdlvl_rotate                              :  1;
     unsigned      reserved2                                 :  7;
     unsigned      rdlvl_aref_en                             :  1;
     unsigned      reserved3                                 :  7;
     unsigned      rdlvl_gate_on_sref_exit                   :  1;
#else    /* Little Endian */
     unsigned      rdlvl_gate_on_sref_exit                   :  1;
     unsigned      reserved3                                 :  7;
     unsigned      rdlvl_aref_en                             :  1;
     unsigned      reserved2                                 :  7;
     unsigned      rdlvl_rotate                              :  1;
     unsigned      reserved1                                 :  7;
     unsigned      rdlvl_gate_rotate                         :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_177_5600_t;

/*! @struct ncp_denali_DENALI_CTL_178_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_178_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param vref_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Enable VREF training during power-up initialization.
 *        Set to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_cs </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Specifies the target chip select for the VREF training
 *        operation.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_cs_map </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the chip select map for gate training operations.
 *        Bit (0) controls cs0, bit (1) controls cs1, etc. Set
 *        each bit to 1 to enable chip for gate training.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_cs_map </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the chip select map for data eye training
 *        operations. Bit (0) controls cs0, bit (1) controls
 *        cs1, etc. Set each bit to 1 to enable chip for data
 *        eye training.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_178_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      vref_en                                   :  1;
     unsigned      reserved1                                 :  6;
     unsigned      vref_cs                                   :  2;
     unsigned      reserved2                                 :  4;
     unsigned      rdlvl_gate_cs_map                         :  4;
     unsigned      reserved3                                 :  4;
     unsigned      rdlvl_cs_map                              :  4;
#else    /* Little Endian */
     unsigned      rdlvl_cs_map                              :  4;
     unsigned      reserved3                                 :  4;
     unsigned      rdlvl_gate_cs_map                         :  4;
     unsigned      reserved2                                 :  4;
     unsigned      vref_cs                                   :  2;
     unsigned      reserved1                                 :  6;
     unsigned      vref_en                                   :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_178_5600_t;

/*! @struct ncp_denali_DENALI_CTL_179_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_179_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param vref_val_dev1_0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 1 for CS 0. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev0_1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 0 for CS 1. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev0_0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 0 for CS 0. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_pda_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enable per-DRAM addressability during VREF training.
 *        Set to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_179_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      vref_val_dev1_0                           :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev0_1                           :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev0_0                           :  7;
     unsigned      reserved3                                 :  7;
     unsigned      vref_pda_en                               :  1;
#else    /* Little Endian */
     unsigned      vref_pda_en                               :  1;
     unsigned      reserved3                                 :  7;
     unsigned      vref_val_dev0_0                           :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev0_1                           :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev1_0                           :  7;
     unsigned      reserved0                                 :  1;
#endif
} ncp_denali_DENALI_CTL_179_5600_t;

/*! @struct ncp_denali_DENALI_CTL_180_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_180_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param vref_val_dev3_0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 3 for CS 0. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev2_1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 2 for CS 1. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev2_0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 2 for CS 0. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev1_1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 1 for CS 1. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_180_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      vref_val_dev3_0                           :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev2_1                           :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev2_0                           :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev1_1                           :  7;
#else    /* Little Endian */
     unsigned      vref_val_dev1_1                           :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev2_0                           :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev2_1                           :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev3_0                           :  7;
     unsigned      reserved0                                 :  1;
#endif
} ncp_denali_DENALI_CTL_180_5600_t;

/*! @struct ncp_denali_DENALI_CTL_181_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_181_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param vref_val_dev5_0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 5 for CS 0. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev4_1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 4 for CS 1. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev4_0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 4 for CS 0. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev3_1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 3 for CS 1. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_181_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      vref_val_dev5_0                           :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev4_1                           :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev4_0                           :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev3_1                           :  7;
#else    /* Little Endian */
     unsigned      vref_val_dev3_1                           :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev4_0                           :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev4_1                           :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev5_0                           :  7;
     unsigned      reserved0                                 :  1;
#endif
} ncp_denali_DENALI_CTL_181_5600_t;

/*! @struct ncp_denali_DENALI_CTL_182_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_182_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param vref_val_dev7_0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 7 for CS 0. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev6_1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 6 for CS 1. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev6_0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 6 for CS 0. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev5_1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 5 for CS 1. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_182_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      vref_val_dev7_0                           :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev6_1                           :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev6_0                           :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev5_1                           :  7;
#else    /* Little Endian */
     unsigned      vref_val_dev5_1                           :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev6_0                           :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev6_1                           :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev7_0                           :  7;
     unsigned      reserved0                                 :  1;
#endif
} ncp_denali_DENALI_CTL_182_5600_t;

/*! @struct ncp_denali_DENALI_CTL_183_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_183_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param vref_val_dev9_0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 9 for CS 0. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev8_1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 8 for CS 1. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev8_0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 8 for CS 0. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev7_1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 7 for CS 1. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_183_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      vref_val_dev9_0                           :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev8_1                           :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev8_0                           :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev7_1                           :  7;
#else    /* Little Endian */
     unsigned      vref_val_dev7_1                           :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev8_0                           :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev8_1                           :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev9_0                           :  7;
     unsigned      reserved0                                 :  1;
#endif
} ncp_denali_DENALI_CTL_183_5600_t;

/*! @struct ncp_denali_DENALI_CTL_184_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_184_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param vref_val_dev11_0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 11 for CS 0. If the VREF_PDA_EN parameter is
 *        not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev10_1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 10 for CS 1. If the VREF_PDA_EN parameter is
 *        not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev10_0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 10 for CS 0. If the VREF_PDA_EN parameter is
 *        not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev9_1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 9 for CS 1. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_184_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      vref_val_dev11_0                          :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev10_1                          :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev10_0                          :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev9_1                           :  7;
#else    /* Little Endian */
     unsigned      vref_val_dev9_1                           :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev10_0                          :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev10_1                          :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev11_0                          :  7;
     unsigned      reserved0                                 :  1;
#endif
} ncp_denali_DENALI_CTL_184_5600_t;

/*! @struct ncp_denali_DENALI_CTL_185_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_185_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param vref_val_dev13_0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 13 for CS 0. If the VREF_PDA_EN parameter is
 *        not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev12_1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 12 for CS 1. If the VREF_PDA_EN parameter is
 *        not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev12_0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 12 for CS 0. If the VREF_PDA_EN parameter is
 *        not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev11_1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 11 for CS 1. If the VREF_PDA_EN parameter is
 *        not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_185_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      vref_val_dev13_0                          :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev12_1                          :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev12_0                          :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev11_1                          :  7;
#else    /* Little Endian */
     unsigned      vref_val_dev11_1                          :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev12_0                          :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev12_1                          :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev13_0                          :  7;
     unsigned      reserved0                                 :  1;
#endif
} ncp_denali_DENALI_CTL_185_5600_t;

/*! @struct ncp_denali_DENALI_CTL_186_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_186_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param vref_val_dev15_0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 15 for CS 0. If the VREF_PDA_EN parameter is
 *        not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev14_1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 14 for CS 1. If the VREF_PDA_EN parameter is
 *        not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev14_0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 14 for CS 0. If the VREF_PDA_EN parameter is
 *        not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev13_1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 13 for CS 1. If the VREF_PDA_EN parameter is
 *        not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_186_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      vref_val_dev15_0                          :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev14_1                          :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev14_0                          :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev13_1                          :  7;
#else    /* Little Endian */
     unsigned      vref_val_dev13_1                          :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev14_0                          :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev14_1                          :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev15_0                          :  7;
     unsigned      reserved0                                 :  1;
#endif
} ncp_denali_DENALI_CTL_186_5600_t;

/*! @struct ncp_denali_DENALI_CTL_187_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_187_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param vref_val_ecc_dev1_0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        ECC DRAM 1 for CS 0. If the VREF_PDA_EN parameter
 *        is not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_ecc_dev0_1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        ECC DRAM 0 for CS 1. If the VREF_PDA_EN parameter
 *        is not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_ecc_dev0_0 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        ECC DRAM 0 for CS 0. If the VREF_PDA_EN parameter
 *        is not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev15_1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 15 for CS 1. If the VREF_PDA_EN parameter is
 *        not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_187_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      vref_val_ecc_dev1_0                       :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_ecc_dev0_1                       :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_ecc_dev0_0                       :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev15_1                          :  7;
#else    /* Little Endian */
     unsigned      vref_val_dev15_1                          :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_ecc_dev0_0                       :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_ecc_dev0_1                       :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_ecc_dev1_0                       :  7;
     unsigned      reserved0                                 :  1;
#endif
} ncp_denali_DENALI_CTL_187_5600_t;

/*! @struct ncp_denali_DENALI_CTL_188_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_188_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param axi0_r_priority </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Priority of read commands from AXI port 0. 0 is the
 *        highest priority.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_fixed_port_priority_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the priority control for AXI port 0 as per-port
 *        or per-command. Set to 1 for per-port with priority
 *        defined through the AXI.18._R_PRIORITY and AXI.18._W_PRIORITY
 *        parameters. Clear to 0 for per-command.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_all_strobes_used_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enables use of the AWALLSTRB signal for AXI port 0.
 *        Set to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_ecc_dev1_1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        ECC DRAM 1 for CS 1. If the VREF_PDA_EN parameter
 *        is not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_188_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      axi0_r_priority                           :  4;
     unsigned      reserved1                                 :  7;
     unsigned      axi0_fixed_port_priority_enable           :  1;
     unsigned      reserved2                                 :  7;
     unsigned      axi0_all_strobes_used_enable              :  1;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_ecc_dev1_1                       :  7;
#else    /* Little Endian */
     unsigned      vref_val_ecc_dev1_1                       :  7;
     unsigned      reserved3                                 :  1;
     unsigned      axi0_all_strobes_used_enable              :  1;
     unsigned      reserved2                                 :  7;
     unsigned      axi0_fixed_port_priority_enable           :  1;
     unsigned      reserved1                                 :  7;
     unsigned      axi0_r_priority                           :  4;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_188_5600_t;

/*! @struct ncp_denali_DENALI_CTL_189_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_189_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param axi0_address_range_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Determines if port 0 will use the axi.0._arregion
 *        / axi.0._awregion signals or the AXI.0._START_ADDR_Z
 *        / AXI.0._END_ADDR_Z parameters to define the region/range.
 *        Set to 1 for parameter control.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param port_addr_protection_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enable port address range protection logic and interrupt
 *        generation. Set to 1 to enable.
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
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_w_priority </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Priority of write commands from AXI port 0. 0 is the
 *        highest priority.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_189_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      axi0_address_range_enable                 :  1;
     unsigned      reserved1                                 :  7;
     unsigned      port_addr_protection_en                   :  1;
     unsigned      obsolete1                                 :  8;
     unsigned      reserved2                                 :  4;
     unsigned      axi0_w_priority                           :  4;
#else    /* Little Endian */
     unsigned      axi0_w_priority                           :  4;
     unsigned      reserved2                                 :  4;
     unsigned      obsolete1                                 :  8;
     unsigned      port_addr_protection_en                   :  1;
     unsigned      reserved1                                 :  7;
     unsigned      axi0_address_range_enable                 :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_189_5600_t;

/*! @struct ncp_denali_DENALI_CTL_190_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_190_5600_t\n
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
 *     <td width="30%"> @param axi0_start_addr_0 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 0. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_190_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_start_addr_0                         : 24;
#else    /* Little Endian */
     unsigned      axi0_start_addr_0                         : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_190_5600_t;

/*! @struct ncp_denali_DENALI_CTL_191_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_191_5600_t\n
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
 *     <td width="30%"> @param axi0_end_addr_0 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 0. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_191_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_end_addr_0                           : 24;
#else    /* Little Endian */
     unsigned      axi0_end_addr_0                           : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_191_5600_t;

/*! @struct ncp_denali_DENALI_CTL_192_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_192_5600_t\n
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
 *     <td width="30%"> @param axi0_start_addr_1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 1. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_192_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_start_addr_1                         : 24;
#else    /* Little Endian */
     unsigned      axi0_start_addr_1                         : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_192_5600_t;

/*! @struct ncp_denali_DENALI_CTL_193_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_193_5600_t\n
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
 *     <td width="30%"> @param axi0_end_addr_1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 1. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_193_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_end_addr_1                           : 24;
#else    /* Little Endian */
     unsigned      axi0_end_addr_1                           : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_193_5600_t;

/*! @struct ncp_denali_DENALI_CTL_194_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_194_5600_t\n
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
 *     <td width="30%"> @param axi0_start_addr_2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 2. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_194_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_start_addr_2                         : 24;
#else    /* Little Endian */
     unsigned      axi0_start_addr_2                         : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_194_5600_t;

/*! @struct ncp_denali_DENALI_CTL_195_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_195_5600_t\n
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
 *     <td width="30%"> @param axi0_end_addr_2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 2. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_195_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_end_addr_2                           : 24;
#else    /* Little Endian */
     unsigned      axi0_end_addr_2                           : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_195_5600_t;

/*! @struct ncp_denali_DENALI_CTL_196_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_196_5600_t\n
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
 *     <td width="30%"> @param axi0_start_addr_3 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 3. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_196_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_start_addr_3                         : 24;
#else    /* Little Endian */
     unsigned      axi0_start_addr_3                         : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_196_5600_t;

/*! @struct ncp_denali_DENALI_CTL_197_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_197_5600_t\n
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
 *     <td width="30%"> @param axi0_end_addr_3 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 3. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_197_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_end_addr_3                           : 24;
#else    /* Little Endian */
     unsigned      axi0_end_addr_3                           : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_197_5600_t;

/*! @struct ncp_denali_DENALI_CTL_198_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_198_5600_t\n
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
 *     <td width="30%"> @param axi0_start_addr_4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 4. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_198_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_start_addr_4                         : 24;
#else    /* Little Endian */
     unsigned      axi0_start_addr_4                         : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_198_5600_t;

/*! @struct ncp_denali_DENALI_CTL_199_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_199_5600_t\n
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
 *     <td width="30%"> @param axi0_end_addr_4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 4. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_199_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_end_addr_4                           : 24;
#else    /* Little Endian */
     unsigned      axi0_end_addr_4                           : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_199_5600_t;

/*! @struct ncp_denali_DENALI_CTL_200_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_200_5600_t\n
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
 *     <td width="30%"> @param axi0_start_addr_5 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 5. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_200_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_start_addr_5                         : 24;
#else    /* Little Endian */
     unsigned      axi0_start_addr_5                         : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_200_5600_t;

/*! @struct ncp_denali_DENALI_CTL_201_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_201_5600_t\n
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
 *     <td width="30%"> @param axi0_end_addr_5 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 5. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_201_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_end_addr_5                           : 24;
#else    /* Little Endian */
     unsigned      axi0_end_addr_5                           : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_201_5600_t;

/*! @struct ncp_denali_DENALI_CTL_202_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_202_5600_t\n
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
 *     <td width="30%"> @param axi0_start_addr_6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 6. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_202_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_start_addr_6                         : 24;
#else    /* Little Endian */
     unsigned      axi0_start_addr_6                         : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_202_5600_t;

/*! @struct ncp_denali_DENALI_CTL_203_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_203_5600_t\n
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
 *     <td width="30%"> @param axi0_end_addr_6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 6. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_203_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_end_addr_6                           : 24;
#else    /* Little Endian */
     unsigned      axi0_end_addr_6                           : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_203_5600_t;

/*! @struct ncp_denali_DENALI_CTL_204_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_204_5600_t\n
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
 *     <td width="30%"> @param axi0_start_addr_7 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 7. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_204_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_start_addr_7                         : 24;
#else    /* Little Endian */
     unsigned      axi0_start_addr_7                         : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_204_5600_t;

/*! @struct ncp_denali_DENALI_CTL_205_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_205_5600_t\n
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
 *     <td width="30%"> @param axi0_end_addr_7 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 7. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_205_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_end_addr_7                           : 24;
#else    /* Little Endian */
     unsigned      axi0_end_addr_7                           : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_205_5600_t;

/*! @struct ncp_denali_DENALI_CTL_206_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_206_5600_t\n
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
 *     <td width="30%"> @param axi0_start_addr_8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 8. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_206_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_start_addr_8                         : 24;
#else    /* Little Endian */
     unsigned      axi0_start_addr_8                         : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_206_5600_t;

/*! @struct ncp_denali_DENALI_CTL_207_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_207_5600_t\n
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
 *     <td width="30%"> @param axi0_end_addr_8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 8. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_207_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_end_addr_8                           : 24;
#else    /* Little Endian */
     unsigned      axi0_end_addr_8                           : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_207_5600_t;

/*! @struct ncp_denali_DENALI_CTL_208_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_208_5600_t\n
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
 *     <td width="30%"> @param axi0_start_addr_9 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 9. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_208_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_start_addr_9                         : 24;
#else    /* Little Endian */
     unsigned      axi0_start_addr_9                         : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_208_5600_t;

/*! @struct ncp_denali_DENALI_CTL_209_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_209_5600_t\n
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
 *     <td width="30%"> @param axi0_end_addr_9 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 9. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_209_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_end_addr_9                           : 24;
#else    /* Little Endian */
     unsigned      axi0_end_addr_9                           : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_209_5600_t;

/*! @struct ncp_denali_DENALI_CTL_210_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_210_5600_t\n
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
 *     <td width="30%"> @param axi0_start_addr_10 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 10. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_210_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_start_addr_10                        : 24;
#else    /* Little Endian */
     unsigned      axi0_start_addr_10                        : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_210_5600_t;

/*! @struct ncp_denali_DENALI_CTL_211_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_211_5600_t\n
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
 *     <td width="30%"> @param axi0_end_addr_10 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 10. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_211_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_end_addr_10                          : 24;
#else    /* Little Endian */
     unsigned      axi0_end_addr_10                          : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_211_5600_t;

/*! @struct ncp_denali_DENALI_CTL_212_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_212_5600_t\n
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
 *     <td width="30%"> @param axi0_start_addr_11 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 11. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_212_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_start_addr_11                        : 24;
#else    /* Little Endian */
     unsigned      axi0_start_addr_11                        : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_212_5600_t;

/*! @struct ncp_denali_DENALI_CTL_213_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_213_5600_t\n
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
 *     <td width="30%"> @param axi0_end_addr_11 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 11. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_213_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_end_addr_11                          : 24;
#else    /* Little Endian */
     unsigned      axi0_end_addr_11                          : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_213_5600_t;

/*! @struct ncp_denali_DENALI_CTL_214_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_214_5600_t\n
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
 *     <td width="30%"> @param axi0_start_addr_12 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 12. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_214_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_start_addr_12                        : 24;
#else    /* Little Endian */
     unsigned      axi0_start_addr_12                        : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_214_5600_t;

/*! @struct ncp_denali_DENALI_CTL_215_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_215_5600_t\n
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
 *     <td width="30%"> @param axi0_end_addr_12 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 12. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_215_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_end_addr_12                          : 24;
#else    /* Little Endian */
     unsigned      axi0_end_addr_12                          : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_215_5600_t;

/*! @struct ncp_denali_DENALI_CTL_216_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_216_5600_t\n
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
 *     <td width="30%"> @param axi0_start_addr_13 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 13. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_216_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_start_addr_13                        : 24;
#else    /* Little Endian */
     unsigned      axi0_start_addr_13                        : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_216_5600_t;

/*! @struct ncp_denali_DENALI_CTL_217_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_217_5600_t\n
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
 *     <td width="30%"> @param axi0_end_addr_13 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 13. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_217_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_end_addr_13                          : 24;
#else    /* Little Endian */
     unsigned      axi0_end_addr_13                          : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_217_5600_t;

/*! @struct ncp_denali_DENALI_CTL_218_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_218_5600_t\n
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
 *     <td width="30%"> @param axi0_start_addr_14 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 14. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_218_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_start_addr_14                        : 24;
#else    /* Little Endian */
     unsigned      axi0_start_addr_14                        : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_218_5600_t;

/*! @struct ncp_denali_DENALI_CTL_219_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_219_5600_t\n
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
 *     <td width="30%"> @param axi0_end_addr_14 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 14. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_219_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_end_addr_14                          : 24;
#else    /* Little Endian */
     unsigned      axi0_end_addr_14                          : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_219_5600_t;

/*! @struct ncp_denali_DENALI_CTL_220_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_220_5600_t\n
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
 *     <td width="30%"> @param axi0_start_addr_15 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start address of port 0 address range 15. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_220_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      axi0_start_addr_15                        : 24;
#else    /* Little Endian */
     unsigned      axi0_start_addr_15                        : 24;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_220_5600_t;

/*! @struct ncp_denali_DENALI_CTL_221_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_221_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param axi0_range_prot_bits_0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        0. Clear to 0 for privileged and secure only, program
 *        to 1 for secure (with or without privileged), program
 *        to 2 for privileged (with or without secure), or program
 *        to 3 for full access.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_end_addr_15 </td>
 *     <td width="20%" align="center"> 24 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> End address of port 0 address range 15. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_221_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_prot_bits_0                    :  2;
     unsigned      axi0_end_addr_15                          : 24;
#else    /* Little Endian */
     unsigned      axi0_end_addr_15                          : 24;
     unsigned      axi0_range_prot_bits_0                    :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_221_5600_t;

/*! @struct ncp_denali_DENALI_CTL_222_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_222_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_222_5600_t
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
} ncp_denali_DENALI_CTL_222_5600_t;

/*! @struct ncp_denali_DENALI_CTL_223_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_223_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_0 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_0 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_223_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      axi0_range_wid_check_bits_id_lookup_0     : 13;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_rid_check_bits_id_lookup_0     : 13;
#else    /* Little Endian */
     unsigned      axi0_range_rid_check_bits_id_lookup_0     : 13;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_wid_check_bits_id_lookup_0     : 13;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_223_5600_t;

/*! @struct ncp_denali_DENALI_CTL_224_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_224_5600_t\n
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
 *     <td width="30%"> @param axi0_range_rid_check_bits_1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed read IDs for port 0 address range 1. Bit (0)
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
 *     <td width="30%"> @param axi0_range_prot_bits_1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        1. Clear to 0 for privileged and secure only, program
 *        to 1 for secure (with or without privileged), program
 *        to 2 for privileged (with or without secure), or program
 *        to 3 for full access.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_224_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      axi0_range_rid_check_bits_1               : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_prot_bits_1                    :  2;
#else    /* Little Endian */
     unsigned      axi0_range_prot_bits_1                    :  2;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_rid_check_bits_1               : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_224_5600_t;

/*! @struct ncp_denali_DENALI_CTL_225_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_225_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_1.
 *   </td>
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_225_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      axi0_range_rid_check_bits_id_lookup_1     : 13;
     unsigned      axi0_range_wid_check_bits_1               : 16;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_1               : 16;
     unsigned      axi0_range_rid_check_bits_id_lookup_1     : 13;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_225_5600_t;

/*! @struct ncp_denali_DENALI_CTL_226_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_226_5600_t\n
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
 *     <td width="30%"> @param axi0_range_prot_bits_2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        2. Clear to 0 for privileged and secure only, program
 *        to 1 for secure (with or without privileged), program
 *        to 2 for privileged (with or without secure), or program
 *        to 3 for full access.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_1.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_226_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_prot_bits_2                    :  2;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_wid_check_bits_id_lookup_1     : 13;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_id_lookup_1     : 13;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_prot_bits_2                    :  2;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_226_5600_t;

/*! @struct ncp_denali_DENALI_CTL_227_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_227_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_227_5600_t
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
} ncp_denali_DENALI_CTL_227_5600_t;

/*! @struct ncp_denali_DENALI_CTL_228_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_228_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_2 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_2.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_2 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_2.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_228_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      axi0_range_wid_check_bits_id_lookup_2     : 13;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_rid_check_bits_id_lookup_2     : 13;
#else    /* Little Endian */
     unsigned      axi0_range_rid_check_bits_id_lookup_2     : 13;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_wid_check_bits_id_lookup_2     : 13;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_228_5600_t;

/*! @struct ncp_denali_DENALI_CTL_229_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_229_5600_t\n
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
 *     <td width="30%"> @param axi0_range_rid_check_bits_3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Allowed read IDs for port 0 address range 3. Bit (0)
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
 *     <td width="30%"> @param axi0_range_prot_bits_3 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        3. Clear to 0 for privileged and secure only, program
 *        to 1 for secure (with or without privileged), program
 *        to 2 for privileged (with or without secure), or program
 *        to 3 for full access.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_229_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      axi0_range_rid_check_bits_3               : 16;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_prot_bits_3                    :  2;
#else    /* Little Endian */
     unsigned      axi0_range_prot_bits_3                    :  2;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_rid_check_bits_3               : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_229_5600_t;

/*! @struct ncp_denali_DENALI_CTL_230_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_230_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_3.
 *   </td>
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_230_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      axi0_range_rid_check_bits_id_lookup_3     : 13;
     unsigned      axi0_range_wid_check_bits_3               : 16;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_3               : 16;
     unsigned      axi0_range_rid_check_bits_id_lookup_3     : 13;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_230_5600_t;

/*! @struct ncp_denali_DENALI_CTL_231_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_231_5600_t\n
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
 *     <td width="30%"> @param axi0_range_prot_bits_4 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        4. Clear to 0 for privileged and secure only, program
 *        to 1 for secure (with or without privileged), program
 *        to 2 for privileged (with or without secure), or program
 *        to 3 for full access.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_3.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_231_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_prot_bits_4                    :  2;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_wid_check_bits_id_lookup_3     : 13;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_id_lookup_3     : 13;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_prot_bits_4                    :  2;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_231_5600_t;

/*! @struct ncp_denali_DENALI_CTL_232_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_232_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Allowed write IDs for port 0 address range 4. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed read IDs for port 0 address range 4. Bit (0)
 *        correlates to requestor 0, bit (1) correlates to requestor
 *        1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_232_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      axi0_range_wid_check_bits_4               : 16;
     unsigned      axi0_range_rid_check_bits_4               : 16;
#else    /* Little Endian */
     unsigned      axi0_range_rid_check_bits_4               : 16;
     unsigned      axi0_range_wid_check_bits_4               : 16;
#endif
} ncp_denali_DENALI_CTL_232_5600_t;

/*! @struct ncp_denali_DENALI_CTL_233_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_233_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_4 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_4.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_4 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_4.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_233_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      axi0_range_wid_check_bits_id_lookup_4     : 13;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_rid_check_bits_id_lookup_4     : 13;
#else    /* Little Endian */
     unsigned      axi0_range_rid_check_bits_id_lookup_4     : 13;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_wid_check_bits_id_lookup_4     : 13;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_233_5600_t;

/*! @struct ncp_denali_DENALI_CTL_234_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_234_5600_t\n
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
 *        5. Clear to 0 for privileged and secure only, program
 *        to 1 for secure (with or without privileged), program
 *        to 2 for privileged (with or without secure), or program
 *        to 3 for full access.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_234_5600_t
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
} ncp_denali_DENALI_CTL_234_5600_t;

/*! @struct ncp_denali_DENALI_CTL_235_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_235_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_5 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_5.
 *   </td>
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_235_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      axi0_range_rid_check_bits_id_lookup_5     : 13;
     unsigned      axi0_range_wid_check_bits_5               : 16;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_5               : 16;
     unsigned      axi0_range_rid_check_bits_id_lookup_5     : 13;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_235_5600_t;

/*! @struct ncp_denali_DENALI_CTL_236_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_236_5600_t\n
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
 *     <td width="30%"> @param axi0_range_prot_bits_6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        6. Clear to 0 for privileged and secure only, program
 *        to 1 for secure (with or without privileged), program
 *        to 2 for privileged (with or without secure), or program
 *        to 3 for full access.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_5 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_5.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_236_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_prot_bits_6                    :  2;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_wid_check_bits_id_lookup_5     : 13;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_id_lookup_5     : 13;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_prot_bits_6                    :  2;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_236_5600_t;

/*! @struct ncp_denali_DENALI_CTL_237_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_237_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Allowed write IDs for port 0 address range 6. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed read IDs for port 0 address range 6. Bit (0)
 *        correlates to requestor 0, bit (1) correlates to requestor
 *        1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_237_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      axi0_range_wid_check_bits_6               : 16;
     unsigned      axi0_range_rid_check_bits_6               : 16;
#else    /* Little Endian */
     unsigned      axi0_range_rid_check_bits_6               : 16;
     unsigned      axi0_range_wid_check_bits_6               : 16;
#endif
} ncp_denali_DENALI_CTL_237_5600_t;

/*! @struct ncp_denali_DENALI_CTL_238_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_238_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_6 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_6.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_6 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_6.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_238_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      axi0_range_wid_check_bits_id_lookup_6     : 13;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_rid_check_bits_id_lookup_6     : 13;
#else    /* Little Endian */
     unsigned      axi0_range_rid_check_bits_id_lookup_6     : 13;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_wid_check_bits_id_lookup_6     : 13;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_238_5600_t;

/*! @struct ncp_denali_DENALI_CTL_239_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_239_5600_t\n
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
 *        7. Clear to 0 for privileged and secure only, program
 *        to 1 for secure (with or without privileged), program
 *        to 2 for privileged (with or without secure), or program
 *        to 3 for full access.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_239_5600_t
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
} ncp_denali_DENALI_CTL_239_5600_t;

/*! @struct ncp_denali_DENALI_CTL_240_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_240_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_7 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_7.
 *   </td>
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_240_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      axi0_range_rid_check_bits_id_lookup_7     : 13;
     unsigned      axi0_range_wid_check_bits_7               : 16;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_7               : 16;
     unsigned      axi0_range_rid_check_bits_id_lookup_7     : 13;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_240_5600_t;

/*! @struct ncp_denali_DENALI_CTL_241_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_241_5600_t\n
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
 *     <td width="30%"> @param axi0_range_prot_bits_8 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        8. Clear to 0 for privileged and secure only, program
 *        to 1 for secure (with or without privileged), program
 *        to 2 for privileged (with or without secure), or program
 *        to 3 for full access.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_7 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_7.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_241_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_prot_bits_8                    :  2;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_wid_check_bits_id_lookup_7     : 13;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_id_lookup_7     : 13;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_prot_bits_8                    :  2;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_241_5600_t;

/*! @struct ncp_denali_DENALI_CTL_242_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_242_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Allowed write IDs for port 0 address range 8. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed read IDs for port 0 address range 8. Bit (0)
 *        correlates to requestor 0, bit (1) correlates to requestor
 *        1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_242_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      axi0_range_wid_check_bits_8               : 16;
     unsigned      axi0_range_rid_check_bits_8               : 16;
#else    /* Little Endian */
     unsigned      axi0_range_rid_check_bits_8               : 16;
     unsigned      axi0_range_wid_check_bits_8               : 16;
#endif
} ncp_denali_DENALI_CTL_242_5600_t;

/*! @struct ncp_denali_DENALI_CTL_243_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_243_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_8 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_8.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_8 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_8.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_243_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      axi0_range_wid_check_bits_id_lookup_8     : 13;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_rid_check_bits_id_lookup_8     : 13;
#else    /* Little Endian */
     unsigned      axi0_range_rid_check_bits_id_lookup_8     : 13;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_wid_check_bits_id_lookup_8     : 13;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_243_5600_t;

/*! @struct ncp_denali_DENALI_CTL_244_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_244_5600_t\n
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
 *        9. Clear to 0 for privileged and secure only, program
 *        to 1 for secure (with or without privileged), program
 *        to 2 for privileged (with or without secure), or program
 *        to 3 for full access.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_244_5600_t
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
} ncp_denali_DENALI_CTL_244_5600_t;

/*! @struct ncp_denali_DENALI_CTL_245_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_245_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_9 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_9.
 *   </td>
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_245_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      axi0_range_rid_check_bits_id_lookup_9     : 13;
     unsigned      axi0_range_wid_check_bits_9               : 16;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_9               : 16;
     unsigned      axi0_range_rid_check_bits_id_lookup_9     : 13;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_245_5600_t;

/*! @struct ncp_denali_DENALI_CTL_246_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_246_5600_t\n
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
 *     <td width="30%"> @param axi0_range_prot_bits_10 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        10. Clear to 0 for privileged and secure only, program
 *        to 1 for secure (with or without privileged), program
 *        to 2 for privileged (with or without secure), or program
 *        to 3 for full access.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_9 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_9.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_246_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_prot_bits_10                   :  2;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_wid_check_bits_id_lookup_9     : 13;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_id_lookup_9     : 13;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_prot_bits_10                   :  2;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_246_5600_t;

/*! @struct ncp_denali_DENALI_CTL_247_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_247_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_10 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Allowed write IDs for port 0 address range 10. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_10 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed read IDs for port 0 address range 10. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_247_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      axi0_range_wid_check_bits_10              : 16;
     unsigned      axi0_range_rid_check_bits_10              : 16;
#else    /* Little Endian */
     unsigned      axi0_range_rid_check_bits_10              : 16;
     unsigned      axi0_range_wid_check_bits_10              : 16;
#endif
} ncp_denali_DENALI_CTL_247_5600_t;

/*! @struct ncp_denali_DENALI_CTL_248_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_248_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_10 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_10.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_10 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_10.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_248_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      axi0_range_wid_check_bits_id_lookup_10    : 13;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_rid_check_bits_id_lookup_10    : 13;
#else    /* Little Endian */
     unsigned      axi0_range_rid_check_bits_id_lookup_10    : 13;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_wid_check_bits_id_lookup_10    : 13;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_248_5600_t;

/*! @struct ncp_denali_DENALI_CTL_249_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_249_5600_t\n
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
 *        11. Clear to 0 for privileged and secure only, program
 *        to 1 for secure (with or without privileged), program
 *        to 2 for privileged (with or without secure), or program
 *        to 3 for full access.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_249_5600_t
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
} ncp_denali_DENALI_CTL_249_5600_t;

/*! @struct ncp_denali_DENALI_CTL_250_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_250_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_11 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_11.
 *   </td>
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_250_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      axi0_range_rid_check_bits_id_lookup_11    : 13;
     unsigned      axi0_range_wid_check_bits_11              : 16;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_11              : 16;
     unsigned      axi0_range_rid_check_bits_id_lookup_11    : 13;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_250_5600_t;

/*! @struct ncp_denali_DENALI_CTL_251_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_251_5600_t\n
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
 *     <td width="30%"> @param axi0_range_prot_bits_12 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        12. Clear to 0 for privileged and secure only, program
 *        to 1 for secure (with or without privileged), program
 *        to 2 for privileged (with or without secure), or program
 *        to 3 for full access.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_11 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_11.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_251_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_prot_bits_12                   :  2;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_wid_check_bits_id_lookup_11    : 13;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_id_lookup_11    : 13;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_prot_bits_12                   :  2;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_251_5600_t;

/*! @struct ncp_denali_DENALI_CTL_252_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_252_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Allowed write IDs for port 0 address range 12. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed read IDs for port 0 address range 12. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_252_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      axi0_range_wid_check_bits_12              : 16;
     unsigned      axi0_range_rid_check_bits_12              : 16;
#else    /* Little Endian */
     unsigned      axi0_range_rid_check_bits_12              : 16;
     unsigned      axi0_range_wid_check_bits_12              : 16;
#endif
} ncp_denali_DENALI_CTL_252_5600_t;

/*! @struct ncp_denali_DENALI_CTL_253_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_253_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_12 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_12.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_12 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_12.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_253_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      axi0_range_wid_check_bits_id_lookup_12    : 13;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_rid_check_bits_id_lookup_12    : 13;
#else    /* Little Endian */
     unsigned      axi0_range_rid_check_bits_id_lookup_12    : 13;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_wid_check_bits_id_lookup_12    : 13;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_253_5600_t;

/*! @struct ncp_denali_DENALI_CTL_254_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_254_5600_t\n
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
 *        13. Clear to 0 for privileged and secure only, program
 *        to 1 for secure (with or without privileged), program
 *        to 2 for privileged (with or without secure), or program
 *        to 3 for full access.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_254_5600_t
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
} ncp_denali_DENALI_CTL_254_5600_t;

/*! @struct ncp_denali_DENALI_CTL_255_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_255_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_13 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_13.
 *   </td>
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_255_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      axi0_range_rid_check_bits_id_lookup_13    : 13;
     unsigned      axi0_range_wid_check_bits_13              : 16;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_13              : 16;
     unsigned      axi0_range_rid_check_bits_id_lookup_13    : 13;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_255_5600_t;

/*! @struct ncp_denali_DENALI_CTL_256_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_256_5600_t\n
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
 *     <td width="30%"> @param axi0_range_prot_bits_14 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Allowed transaction types for port 0 address range
 *        14. Clear to 0 for privileged and secure only, program
 *        to 1 for secure (with or without privileged), program
 *        to 2 for privileged (with or without secure), or program
 *        to 3 for full access.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_13 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_13.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_256_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      axi0_range_prot_bits_14                   :  2;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_wid_check_bits_id_lookup_13    : 13;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_id_lookup_13    : 13;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_prot_bits_14                   :  2;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_256_5600_t;

/*! @struct ncp_denali_DENALI_CTL_257_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_257_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_14 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Allowed write IDs for port 0 address range 14. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_14 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Allowed read IDs for port 0 address range 14. Bit
 *        (0) correlates to requestor 0, bit (1) correlates
 *        to requestor 1, etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_257_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      axi0_range_wid_check_bits_14              : 16;
     unsigned      axi0_range_rid_check_bits_14              : 16;
#else    /* Little Endian */
     unsigned      axi0_range_rid_check_bits_14              : 16;
     unsigned      axi0_range_wid_check_bits_14              : 16;
#endif
} ncp_denali_DENALI_CTL_257_5600_t;

/*! @struct ncp_denali_DENALI_CTL_258_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_258_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_14 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_14.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_14 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_14.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_258_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      axi0_range_wid_check_bits_id_lookup_14    : 13;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_rid_check_bits_id_lookup_14    : 13;
#else    /* Little Endian */
     unsigned      axi0_range_rid_check_bits_id_lookup_14    : 13;
     unsigned      reserved1                                 :  3;
     unsigned      axi0_range_wid_check_bits_id_lookup_14    : 13;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_258_5600_t;

/*! @struct ncp_denali_DENALI_CTL_259_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_259_5600_t\n
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
 *        15. Clear to 0 for privileged and secure only, program
 *        to 1 for secure (with or without privileged), program
 *        to 2 for privileged (with or without secure), or program
 *        to 3 for full access.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_259_5600_t
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
} ncp_denali_DENALI_CTL_259_5600_t;

/*! @struct ncp_denali_DENALI_CTL_260_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_260_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param axi0_range_rid_check_bits_id_lookup_15 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_RID_CHECK_BITS_15.
 *   </td>
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_260_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      axi0_range_rid_check_bits_id_lookup_15    : 13;
     unsigned      axi0_range_wid_check_bits_15              : 16;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_15              : 16;
     unsigned      axi0_range_rid_check_bits_id_lookup_15    : 13;
     unsigned      reserved0                                 :  3;
#endif
} ncp_denali_DENALI_CTL_260_5600_t;

/*! @struct ncp_denali_DENALI_CTL_261_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_261_5600_t\n
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
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_range_wid_check_bits_id_lookup_15 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies which four ID bits to used to index into
 *        AXI.0._RANGE_WID_CHECK_BITS_15.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_261_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      reserved0                                 :  3;
     unsigned      axi0_range_wid_check_bits_id_lookup_15    : 13;
#else    /* Little Endian */
     unsigned      axi0_range_wid_check_bits_id_lookup_15    : 13;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_denali_DENALI_CTL_261_5600_t;

/*! @struct ncp_denali_DENALI_CTL_262_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_262_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_upper_address_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 0. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_262_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_upper_address_0;
} ncp_denali_DENALI_CTL_262_5600_t;

/*! @struct ncp_denali_DENALI_CTL_263_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_263_5600_t\n
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
 *     <td width="30%"> @param wrtprct_upper_address_0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 0. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_263_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_upper_address_0                   :  6;
#else    /* Little Endian */
     unsigned      wrtprct_upper_address_0                   :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_263_5600_t;

/*! @struct ncp_denali_DENALI_CTL_264_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_264_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_lower_address_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 0. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_264_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_lower_address_0;
} ncp_denali_DENALI_CTL_264_5600_t;

/*! @struct ncp_denali_DENALI_CTL_265_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_265_5600_t\n
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
 *     <td width="30%"> @param wrtprct_lower_address_0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 0. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_265_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_lower_address_0                   :  6;
#else    /* Little Endian */
     unsigned      wrtprct_lower_address_0                   :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_265_5600_t;

/*! @struct ncp_denali_DENALI_CTL_266_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_266_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_upper_address_1 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 1. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_266_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_upper_address_1;
} ncp_denali_DENALI_CTL_266_5600_t;

/*! @struct ncp_denali_DENALI_CTL_267_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_267_5600_t\n
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
 *     <td width="30%"> @param wrtprct_upper_address_1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 1. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_267_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_upper_address_1                   :  6;
#else    /* Little Endian */
     unsigned      wrtprct_upper_address_1                   :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_267_5600_t;

/*! @struct ncp_denali_DENALI_CTL_268_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_268_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_lower_address_1 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 1. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_268_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_lower_address_1;
} ncp_denali_DENALI_CTL_268_5600_t;

/*! @struct ncp_denali_DENALI_CTL_269_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_269_5600_t\n
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
 *     <td width="30%"> @param wrtprct_lower_address_1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 1. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_269_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_lower_address_1                   :  6;
#else    /* Little Endian */
     unsigned      wrtprct_lower_address_1                   :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_269_5600_t;

/*! @struct ncp_denali_DENALI_CTL_270_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_270_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_upper_address_2 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 2. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_270_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_upper_address_2;
} ncp_denali_DENALI_CTL_270_5600_t;

/*! @struct ncp_denali_DENALI_CTL_271_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_271_5600_t\n
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
 *     <td width="30%"> @param wrtprct_upper_address_2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 2. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_271_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_upper_address_2                   :  6;
#else    /* Little Endian */
     unsigned      wrtprct_upper_address_2                   :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_271_5600_t;

/*! @struct ncp_denali_DENALI_CTL_272_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_272_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_lower_address_2 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 2. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_272_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_lower_address_2;
} ncp_denali_DENALI_CTL_272_5600_t;

/*! @struct ncp_denali_DENALI_CTL_273_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_273_5600_t\n
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
 *     <td width="30%"> @param wrtprct_lower_address_2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 2. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_273_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_lower_address_2                   :  6;
#else    /* Little Endian */
     unsigned      wrtprct_lower_address_2                   :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_273_5600_t;

/*! @struct ncp_denali_DENALI_CTL_274_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_274_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_upper_address_3 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 3. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_274_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_upper_address_3;
} ncp_denali_DENALI_CTL_274_5600_t;

/*! @struct ncp_denali_DENALI_CTL_275_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_275_5600_t\n
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
 *     <td width="30%"> @param wrtprct_upper_address_3 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 3. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_275_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_upper_address_3                   :  6;
#else    /* Little Endian */
     unsigned      wrtprct_upper_address_3                   :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_275_5600_t;

/*! @struct ncp_denali_DENALI_CTL_276_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_276_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_lower_address_3 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 3. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_276_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_lower_address_3;
} ncp_denali_DENALI_CTL_276_5600_t;

/*! @struct ncp_denali_DENALI_CTL_277_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_277_5600_t\n
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
 *     <td width="30%"> @param wrtprct_lower_address_3 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 3. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_277_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_lower_address_3                   :  6;
#else    /* Little Endian */
     unsigned      wrtprct_lower_address_3                   :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_277_5600_t;

/*! @struct ncp_denali_DENALI_CTL_278_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_278_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_upper_address_4 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 4. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_278_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_upper_address_4;
} ncp_denali_DENALI_CTL_278_5600_t;

/*! @struct ncp_denali_DENALI_CTL_279_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_279_5600_t\n
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
 *     <td width="30%"> @param wrtprct_upper_address_4 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 4. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_279_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_upper_address_4                   :  6;
#else    /* Little Endian */
     unsigned      wrtprct_upper_address_4                   :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_279_5600_t;

/*! @struct ncp_denali_DENALI_CTL_280_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_280_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_lower_address_4 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 4. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_280_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_lower_address_4;
} ncp_denali_DENALI_CTL_280_5600_t;

/*! @struct ncp_denali_DENALI_CTL_281_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_281_5600_t\n
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
 *     <td width="30%"> @param wrtprct_lower_address_4 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 4. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_281_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_lower_address_4                   :  6;
#else    /* Little Endian */
     unsigned      wrtprct_lower_address_4                   :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_281_5600_t;

/*! @struct ncp_denali_DENALI_CTL_282_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_282_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_upper_address_5 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 5. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_282_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_upper_address_5;
} ncp_denali_DENALI_CTL_282_5600_t;

/*! @struct ncp_denali_DENALI_CTL_283_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_283_5600_t\n
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
 *     <td width="30%"> @param wrtprct_upper_address_5 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 5. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_283_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_upper_address_5                   :  6;
#else    /* Little Endian */
     unsigned      wrtprct_upper_address_5                   :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_283_5600_t;

/*! @struct ncp_denali_DENALI_CTL_284_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_284_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_lower_address_5 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 5. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_284_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_lower_address_5;
} ncp_denali_DENALI_CTL_284_5600_t;

/*! @struct ncp_denali_DENALI_CTL_285_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_285_5600_t\n
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
 *     <td width="30%"> @param wrtprct_lower_address_5 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 5. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_285_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_lower_address_5                   :  6;
#else    /* Little Endian */
     unsigned      wrtprct_lower_address_5                   :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_285_5600_t;

/*! @struct ncp_denali_DENALI_CTL_286_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_286_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_upper_address_6 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 6. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_286_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_upper_address_6;
} ncp_denali_DENALI_CTL_286_5600_t;

/*! @struct ncp_denali_DENALI_CTL_287_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_287_5600_t\n
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
 *     <td width="30%"> @param wrtprct_upper_address_6 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 6. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_287_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_upper_address_6                   :  6;
#else    /* Little Endian */
     unsigned      wrtprct_upper_address_6                   :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_287_5600_t;

/*! @struct ncp_denali_DENALI_CTL_288_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_288_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_lower_address_6 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 6. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_288_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_lower_address_6;
} ncp_denali_DENALI_CTL_288_5600_t;

/*! @struct ncp_denali_DENALI_CTL_289_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_289_5600_t\n
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
 *     <td width="30%"> @param wrtprct_lower_address_6 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 6. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_289_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_lower_address_6                   :  6;
#else    /* Little Endian */
     unsigned      wrtprct_lower_address_6                   :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_289_5600_t;

/*! @struct ncp_denali_DENALI_CTL_290_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_290_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_upper_address_7 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 7. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_290_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_upper_address_7;
} ncp_denali_DENALI_CTL_290_5600_t;

/*! @struct ncp_denali_DENALI_CTL_291_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_291_5600_t\n
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
 *     <td width="30%"> @param wrtprct_upper_address_7 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 7. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_291_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_upper_address_7                   :  6;
#else    /* Little Endian */
     unsigned      wrtprct_upper_address_7                   :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_291_5600_t;

/*! @struct ncp_denali_DENALI_CTL_292_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_292_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_lower_address_7 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 7. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_292_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_lower_address_7;
} ncp_denali_DENALI_CTL_292_5600_t;

/*! @struct ncp_denali_DENALI_CTL_293_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_293_5600_t\n
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
 *     <td width="30%"> @param wrtprct_lower_address_7 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 7. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_293_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_lower_address_7                   :  6;
#else    /* Little Endian */
     unsigned      wrtprct_lower_address_7                   :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_293_5600_t;

/*! @struct ncp_denali_DENALI_CTL_294_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_294_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_upper_address_8 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 8. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_294_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_upper_address_8;
} ncp_denali_DENALI_CTL_294_5600_t;

/*! @struct ncp_denali_DENALI_CTL_295_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_295_5600_t\n
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
 *     <td width="30%"> @param wrtprct_upper_address_8 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 8. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_295_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_upper_address_8                   :  6;
#else    /* Little Endian */
     unsigned      wrtprct_upper_address_8                   :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_295_5600_t;

/*! @struct ncp_denali_DENALI_CTL_296_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_296_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_lower_address_8 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 8. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_296_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_lower_address_8;
} ncp_denali_DENALI_CTL_296_5600_t;

/*! @struct ncp_denali_DENALI_CTL_297_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_297_5600_t\n
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
 *     <td width="30%"> @param wrtprct_lower_address_8 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 8. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_297_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_lower_address_8                   :  6;
#else    /* Little Endian */
     unsigned      wrtprct_lower_address_8                   :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_297_5600_t;

/*! @struct ncp_denali_DENALI_CTL_298_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_298_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_upper_address_9 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 9. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_298_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_upper_address_9;
} ncp_denali_DENALI_CTL_298_5600_t;

/*! @struct ncp_denali_DENALI_CTL_299_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_299_5600_t\n
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
 *     <td width="30%"> @param wrtprct_upper_address_9 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 9. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_299_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_upper_address_9                   :  6;
#else    /* Little Endian */
     unsigned      wrtprct_upper_address_9                   :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_299_5600_t;

/*! @struct ncp_denali_DENALI_CTL_300_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_300_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_lower_address_9 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 9. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_300_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_lower_address_9;
} ncp_denali_DENALI_CTL_300_5600_t;

/*! @struct ncp_denali_DENALI_CTL_301_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_301_5600_t\n
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
 *     <td width="30%"> @param wrtprct_lower_address_9 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 9. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_301_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_lower_address_9                   :  6;
#else    /* Little Endian */
     unsigned      wrtprct_lower_address_9                   :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_301_5600_t;

/*! @struct ncp_denali_DENALI_CTL_302_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_302_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_upper_address_10 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 10. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_302_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_upper_address_10;
} ncp_denali_DENALI_CTL_302_5600_t;

/*! @struct ncp_denali_DENALI_CTL_303_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_303_5600_t\n
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
 *     <td width="30%"> @param wrtprct_upper_address_10 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 10. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_303_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_upper_address_10                  :  6;
#else    /* Little Endian */
     unsigned      wrtprct_upper_address_10                  :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_303_5600_t;

/*! @struct ncp_denali_DENALI_CTL_304_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_304_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_lower_address_10 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 10. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_304_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_lower_address_10;
} ncp_denali_DENALI_CTL_304_5600_t;

/*! @struct ncp_denali_DENALI_CTL_305_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_305_5600_t\n
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
 *     <td width="30%"> @param wrtprct_lower_address_10 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 10. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_305_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_lower_address_10                  :  6;
#else    /* Little Endian */
     unsigned      wrtprct_lower_address_10                  :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_305_5600_t;

/*! @struct ncp_denali_DENALI_CTL_306_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_306_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_upper_address_11 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 11. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_306_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_upper_address_11;
} ncp_denali_DENALI_CTL_306_5600_t;

/*! @struct ncp_denali_DENALI_CTL_307_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_307_5600_t\n
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
 *     <td width="30%"> @param wrtprct_upper_address_11 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 11. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_307_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_upper_address_11                  :  6;
#else    /* Little Endian */
     unsigned      wrtprct_upper_address_11                  :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_307_5600_t;

/*! @struct ncp_denali_DENALI_CTL_308_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_308_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_lower_address_11 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 11. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_308_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_lower_address_11;
} ncp_denali_DENALI_CTL_308_5600_t;

/*! @struct ncp_denali_DENALI_CTL_309_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_309_5600_t\n
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
 *     <td width="30%"> @param wrtprct_lower_address_11 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 11. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_309_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_lower_address_11                  :  6;
#else    /* Little Endian */
     unsigned      wrtprct_lower_address_11                  :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_309_5600_t;

/*! @struct ncp_denali_DENALI_CTL_310_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_310_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_upper_address_12 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 12. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_310_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_upper_address_12;
} ncp_denali_DENALI_CTL_310_5600_t;

/*! @struct ncp_denali_DENALI_CTL_311_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_311_5600_t\n
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
 *     <td width="30%"> @param wrtprct_upper_address_12 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 12. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_311_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_upper_address_12                  :  6;
#else    /* Little Endian */
     unsigned      wrtprct_upper_address_12                  :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_311_5600_t;

/*! @struct ncp_denali_DENALI_CTL_312_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_312_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_lower_address_12 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 12. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_312_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_lower_address_12;
} ncp_denali_DENALI_CTL_312_5600_t;

/*! @struct ncp_denali_DENALI_CTL_313_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_313_5600_t\n
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
 *     <td width="30%"> @param wrtprct_lower_address_12 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 12. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_313_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_lower_address_12                  :  6;
#else    /* Little Endian */
     unsigned      wrtprct_lower_address_12                  :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_313_5600_t;

/*! @struct ncp_denali_DENALI_CTL_314_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_314_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_upper_address_13 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 13. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_314_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_upper_address_13;
} ncp_denali_DENALI_CTL_314_5600_t;

/*! @struct ncp_denali_DENALI_CTL_315_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_315_5600_t\n
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
 *     <td width="30%"> @param wrtprct_upper_address_13 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 13. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_315_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_upper_address_13                  :  6;
#else    /* Little Endian */
     unsigned      wrtprct_upper_address_13                  :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_315_5600_t;

/*! @struct ncp_denali_DENALI_CTL_316_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_316_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_lower_address_13 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 13. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_316_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_lower_address_13;
} ncp_denali_DENALI_CTL_316_5600_t;

/*! @struct ncp_denali_DENALI_CTL_317_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_317_5600_t\n
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
 *     <td width="30%"> @param wrtprct_lower_address_13 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 13. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_317_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_lower_address_13                  :  6;
#else    /* Little Endian */
     unsigned      wrtprct_lower_address_13                  :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_317_5600_t;

/*! @struct ncp_denali_DENALI_CTL_318_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_318_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_upper_address_14 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 14. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_318_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_upper_address_14;
} ncp_denali_DENALI_CTL_318_5600_t;

/*! @struct ncp_denali_DENALI_CTL_319_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_319_5600_t\n
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
 *     <td width="30%"> @param wrtprct_upper_address_14 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 14. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_319_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_upper_address_14                  :  6;
#else    /* Little Endian */
     unsigned      wrtprct_upper_address_14                  :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_319_5600_t;

/*! @struct ncp_denali_DENALI_CTL_320_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_320_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_lower_address_14 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 14. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_320_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_lower_address_14;
} ncp_denali_DENALI_CTL_320_5600_t;

/*! @struct ncp_denali_DENALI_CTL_321_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_321_5600_t\n
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
 *     <td width="30%"> @param wrtprct_lower_address_14 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 14. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_321_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_lower_address_14                  :  6;
#else    /* Little Endian */
     unsigned      wrtprct_lower_address_14                  :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_321_5600_t;

/*! @struct ncp_denali_DENALI_CTL_322_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_322_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_upper_address_15 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 15. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_322_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_upper_address_15;
} ncp_denali_DENALI_CTL_322_5600_t;

/*! @struct ncp_denali_DENALI_CTL_323_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_323_5600_t\n
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
 *     <td width="30%"> @param wrtprct_upper_address_15 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Upper address of write protect region 15. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_323_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_upper_address_15                  :  6;
#else    /* Little Endian */
     unsigned      wrtprct_upper_address_15                  :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_323_5600_t;

/*! @struct ncp_denali_DENALI_CTL_324_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_324_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_lower_address_15 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 15. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_324_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_lower_address_15;
} ncp_denali_DENALI_CTL_324_5600_t;

/*! @struct ncp_denali_DENALI_CTL_325_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_325_5600_t\n
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
 *     <td width="30%"> @param wrtprct_lower_address_15 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Lower address of write protect region 15. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_325_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  2;
     unsigned      wrtprct_lower_address_15                  :  6;
#else    /* Little Endian */
     unsigned      wrtprct_lower_address_15                  :  6;
     unsigned      reserved0                                 :  2;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_325_5600_t;

/*! @struct ncp_denali_DENALI_CTL_326_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_326_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_error_address </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address of write attempt to a write protected region.
 *        READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_326_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      wrtprct_error_address;
} ncp_denali_DENALI_CTL_326_5600_t;

/*! @struct ncp_denali_DENALI_CTL_327_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_327_5600_t\n
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
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_error_length </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Length of write attempt to a write protected region.
 *        READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_error_address </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address of write attempt to a write protected region.
 *        READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_327_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      reserved0                                 :  3;
     unsigned      wrtprct_error_length                      : 13;
     unsigned      reserved1                                 :  2;
     unsigned      wrtprct_error_address                     :  6;
#else    /* Little Endian */
     unsigned      wrtprct_error_address                     :  6;
     unsigned      reserved1                                 :  2;
     unsigned      wrtprct_error_length                      : 13;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_327_5600_t;

/*! @struct ncp_denali_DENALI_CTL_328_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_328_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param mem_rst_valid </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Register access to mem_rst_valid signal. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cke_status </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Register access to cke_status signal. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrtprct_enable </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enable use of write protection. Bit (0) corresponds
 *        to write protect region 0, bit (1) corresponds to
 *        write protect region 1, etc. Set each bit to 1 to
 *        enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_328_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      mem_rst_valid                             :  1;
     unsigned      reserved1                                 :  4;
     unsigned      cke_status                                :  4;
     unsigned      wrtprct_enable                            : 16;
#else    /* Little Endian */
     unsigned      wrtprct_enable                            : 16;
     unsigned      cke_status                                :  4;
     unsigned      reserved1                                 :  4;
     unsigned      mem_rst_valid                             :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_328_5600_t;

/*! @struct ncp_denali_DENALI_CTL_329_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_329_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param tdfi_phy_wrlat </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Holds the calculated DFI tPHY_WRLAT timing parameter
 *        (in DFI PHY clocks), the maximum cycles between a
 *        write command and a dfi_wrdata_en assertion. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dll_rst_adj_dly </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Minimum cycles after setting master delay in DLL until
 *        the DLL reset signal dll_rst_n may be asserted. If
 *        this signal is not being used by the PHY, this parameter
 *        may be ignored.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dll_rst_delay </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Minimum cycles required for DLL reset signal dll_rst_n
 *        to be held. If this signal is not being used by the
 *        PHY, this parameter may be ignored.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_329_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      tdfi_phy_wrlat                            :  7;
     unsigned      dll_rst_adj_dly                           :  8;
     unsigned      dll_rst_delay                             : 16;
#else    /* Little Endian */
     unsigned      dll_rst_delay                             : 16;
     unsigned      dll_rst_adj_dly                           :  8;
     unsigned      tdfi_phy_wrlat                            :  7;
     unsigned      reserved0                                 :  1;
#endif
} ncp_denali_DENALI_CTL_329_5600_t;

/*! @struct ncp_denali_DENALI_CTL_330_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_330_5600_t\n
 *   </td>
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
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_rddata_en </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Holds the calculated DFI tRDDATA_EN timing parameter
 *        (in DFI PHY clocks), the maximum cycles between a
 *        read command and a dfi_rddata_en assertion. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_phy_rdlat </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the DFI tPHY_RDLAT timing parameter (in DFI
 *        PHY clocks), the maximum cycles between a dfi_rddata_en
 *        assertion and a dfi_rddata_valid assertion.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param update_error_status </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Identifies the source of any DFI MC-initiated or PHY-initiated
 *        update errors. Value of 1 indicates a timing violation
 *        of the associated timing parameter. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_330_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      dram_clk_disable                          :  4;
     unsigned      reserved1                                 :  1;
     unsigned      tdfi_rddata_en                            :  7;
     unsigned      reserved2                                 :  1;
     unsigned      tdfi_phy_rdlat                            :  7;
     unsigned      reserved3                                 :  1;
     unsigned      update_error_status                       :  7;
#else    /* Little Endian */
     unsigned      update_error_status                       :  7;
     unsigned      reserved3                                 :  1;
     unsigned      tdfi_phy_rdlat                            :  7;
     unsigned      reserved2                                 :  1;
     unsigned      tdfi_rddata_en                            :  7;
     unsigned      reserved1                                 :  1;
     unsigned      dram_clk_disable                          :  4;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_330_5600_t;

/*! @struct ncp_denali_DENALI_CTL_331_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_331_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param tdfi_ctrlupd_max </td>
 *     <td width="20%" align="center"> 20 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the DFI tCTRLUPD_MAX timing parameter (in
 *        DFI clocks), the maximum cycles that dfi_ctrlupd_req
 *        can be asserted. If programmed to a non-zero, a timing
 *        violation will cause an interrupt and bit (1) set
 *        in the UPDATE_ERROR_STATUS parameter.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_ctrlupd_min </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reports the DFI tCTRLUPD_MIN timing parameter (in
 *        DFI clocks), the minimum cycles that dfi_ctrlupd_req
 *        must be asserted. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_331_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      tdfi_ctrlupd_max                          : 20;
     unsigned      reserved1                                 :  4;
     unsigned      tdfi_ctrlupd_min                          :  4;
#else    /* Little Endian */
     unsigned      tdfi_ctrlupd_min                          :  4;
     unsigned      reserved1                                 :  4;
     unsigned      tdfi_ctrlupd_max                          : 20;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_331_5600_t;

/*! @struct ncp_denali_DENALI_CTL_332_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_332_5600_t\n
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
 *   <td width="30%"> Defines the DFI tPHYUPD_TYPE1 timing parameter (in
 *        DFI clocks), the maximum cycles that dfi_phyupd_req
 *        can assert after dfi_phyupd_ack for dfi_phyupd_type
 *        1. If programmed to a non-zero, a timing violation
 *        will cause an interrupt and bit (3) set in the UPDATE_ERROR_STATUS
 *        parameter.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_phyupd_type0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the DFI tPHYUPD_TYPE0 timing parameter (in
 *        DFI clocks), the maximum cycles that dfi_phyupd_req
 *        can assert after dfi_phyupd_ack for dfi_phyupd_type
 *        0. If programmed to a non-zero, a timing violation
 *        will cause an interrupt and bit (2) set in the UPDATE_ERROR_STATUS
 *        parameter.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_332_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      tdfi_phyupd_type1                         : 16;
     unsigned      tdfi_phyupd_type0                         : 16;
#else    /* Little Endian */
     unsigned      tdfi_phyupd_type0                         : 16;
     unsigned      tdfi_phyupd_type1                         : 16;
#endif
} ncp_denali_DENALI_CTL_332_5600_t;

/*! @struct ncp_denali_DENALI_CTL_333_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_333_5600_t\n
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
 *   <td width="30%"> Defines the DFI tPHYUPD_TYPE3 timing parameter (in
 *        DFI clocks), the maximum cycles that dfi_phyupd_req
 *        can assert after dfi_phyupd_ack for dfi_phyupd_type
 *        3. If programmed to a non-zero, a timing violation
 *        will cause an interrupt and bit (5) set in the UPDATE_ERROR_STATUS
 *        parameter.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_phyupd_type2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the DFI tPHYUPD_TYPE2 timing parameter (in
 *        DFI clocks), the maximum cycles that dfi_phyupd_req
 *        can assert after dfi_phyupd_ack for dfi_phyupd_type
 *        2. If programmed to a non-zero, a timing violation
 *        will cause an interrupt and bit (4) set in the UPDATE_ERROR_STATUS
 *        parameter.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_333_5600_t
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
} ncp_denali_DENALI_CTL_333_5600_t;

/*! @struct ncp_denali_DENALI_CTL_334_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_334_5600_t\n
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
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_phyupd_resp </td>
 *     <td width="20%" align="center"> 20 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the DFI tPHYUPD_RESP timing parameter (in
 *        DFI clocks), the maximum cycles between a dfi_phyupd_req
 *        assertion and a dfi_phyupd_ack assertion. If programmed
 *        to a non-zero, a timing violation will cause an interrupt
 *        and bit (6) set in the UPDATE_ERROR_STATUS parameter.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_334_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  4;
     unsigned      tdfi_phyupd_resp                          : 20;
#else    /* Little Endian */
     unsigned      tdfi_phyupd_resp                          : 20;
     unsigned      reserved0                                 :  4;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_334_5600_t;

/*! @struct ncp_denali_DENALI_CTL_335_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_335_5600_t\n
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
 *   <td width="30%"> Defines the DFI tCTRLUPD_INTERVAL timing parameter
 *        (in DFI clocks), the maximum cycles between dfi_ctrlupd_req
 *        assertions. If programmed to a non-zero, a timing
 *        violation will cause an interrupt and bit (0) set
 *        in the UPDATE_ERROR_STATUS parameter.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_335_5600_t
 *
 */
 
typedef struct
{
     unsigned  int      tdfi_ctrlupd_interval;
} ncp_denali_DENALI_CTL_335_5600_t;

/*! @struct ncp_denali_DENALI_CTL_336_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_336_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param tdfi_dram_clk_disable </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines the DFI tDRAM_CLK_DISABLE timing parameter
 *        (in DFI clocks), the delay between a dfi_dram_clock_disable
 *        assertion and the memory clock disable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_ctrl_delay </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the DFI tCTRL_DELAY timing parameter (in DFI
 *        clocks), the delay between a DFI command change and
 *        a memory command.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlat_adj </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Adjustment value for PHY write timing. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlat_adj </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Adjustment value for PHY read timing. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_336_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      tdfi_dram_clk_disable                     :  4;
     unsigned      reserved1                                 :  4;
     unsigned      tdfi_ctrl_delay                           :  4;
     unsigned      reserved2                                 :  1;
     unsigned      wrlat_adj                                 :  7;
     unsigned      reserved3                                 :  1;
     unsigned      rdlat_adj                                 :  7;
#else    /* Little Endian */
     unsigned      rdlat_adj                                 :  7;
     unsigned      reserved3                                 :  1;
     unsigned      wrlat_adj                                 :  7;
     unsigned      reserved2                                 :  1;
     unsigned      tdfi_ctrl_delay                           :  4;
     unsigned      reserved1                                 :  4;
     unsigned      tdfi_dram_clk_disable                     :  4;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_336_5600_t;

/*! @struct ncp_denali_DENALI_CTL_337_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_337_5600_t\n
 *   </td>
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
 *   <td width="30%"> Defines the DFI tWRLVL_WW timing parameter (in DFI
 *        clocks), the minimum cycles between dfi_wrlvl_strobe
 *        assertions.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_wrlvl_en </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the DFI tWRLVL_EN timing parameter (in DFI
 *        clocks), the minimum cycles from a dfi_wrlvl_en assertion
 *        to the first dfi_wrlvl_strobe assertion.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_dram_clk_enable </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the DFI tDRAM_CLK_ENABLE timing parameter
 *        (in DFI clocks), the delay between a dfi_dram_clk_disable
 *        de-assertion and the memory clock enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_337_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      tdfi_wrlvl_ww                             : 10;
     unsigned      tdfi_wrlvl_en                             :  8;
     unsigned      reserved1                                 :  4;
     unsigned      tdfi_dram_clk_enable                      :  4;
#else    /* Little Endian */
     unsigned      tdfi_dram_clk_enable                      :  4;
     unsigned      reserved1                                 :  4;
     unsigned      tdfi_wrlvl_en                             :  8;
     unsigned      tdfi_wrlvl_ww                             : 10;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_337_5600_t;

/*! @struct ncp_denali_DENALI_CTL_338_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_338_5600_t\n
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
 *   <td width="30%"> Defines the DFI tWRLVL_RESP timing parameter (in DFI
 *        clocks), the maximum cycles between a dfi_wrlvl_req
 *        assertion and a dfi_wrlvl_en assertion.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_338_5600_t
 *
 */
 
typedef struct
{
     unsigned  int           tdfi_wrlvl_resp;
} ncp_denali_DENALI_CTL_338_5600_t;

/*! @struct ncp_denali_DENALI_CTL_339_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_339_5600_t\n
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
 *   <td width="30%"> Defines the DFI tWRLVL_MAX timing parameter (in DFI
 *        clocks), the maximum cycles between a dfi_wrlvl_en
 *        assertion and a valid dfi_wrlvl_resp.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_339_5600_t
 *
 */
 
typedef struct
{
     unsigned  int            tdfi_wrlvl_max;
} ncp_denali_DENALI_CTL_339_5600_t;

/*! @struct ncp_denali_DENALI_CTL_340_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_340_5600_t\n
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
 *     <td width="30%"> @param tdfi_rdlvl_rr </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the DFI tRDLVL_RR timing parameter (in DFI
 *        clocks), the minimum cycles between read commands.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_rdlvl_en </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the DFI tRDLVL_EN timing parameter (in DFI
 *        clocks), the minimum cycles from a dfi_rdlvl_en or
 *        dfi_rdlvl_gate_en assertion to the first read or MRR.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_340_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      tdfi_rdlvl_rr                             : 10;
     unsigned      tdfi_rdlvl_en                             :  8;
#else    /* Little Endian */
     unsigned      tdfi_rdlvl_en                             :  8;
     unsigned      tdfi_rdlvl_rr                             : 10;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_340_5600_t;

/*! @struct ncp_denali_DENALI_CTL_341_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_341_5600_t\n
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
 *   <td width="30%"> Defines the DFI tRDLVL_RESP timing parameter (in DFI
 *        clocks), the maximum cycles between a dfi_rdlvl_req
 *        or dfi_rdlvl_gate_req assertion and a dfi_rdlvl_en
 *        or dfi_rdlvl_gate_en assertion.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_341_5600_t
 *
 */
 
typedef struct
{
     unsigned  int           tdfi_rdlvl_resp;
} ncp_denali_DENALI_CTL_341_5600_t;

/*! @struct ncp_denali_DENALI_CTL_342_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_342_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param rdlvl_gate_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Enable the MC gate training module. Set to 1 to enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enable the MC data eye training module. Set to 1 to
 *        enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_resp_mask </td>
 *     <td width="20%" align="center"> 9 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Mask for the dfi_rdlvl_resp signal during data eye
 *        training.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_342_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      rdlvl_gate_en                             :  1;
     unsigned      reserved1                                 :  7;
     unsigned      rdlvl_en                                  :  1;
     unsigned      reserved2                                 :  7;
     unsigned      rdlvl_resp_mask                           :  9;
#else    /* Little Endian */
     unsigned      rdlvl_resp_mask                           :  9;
     unsigned      reserved2                                 :  7;
     unsigned      rdlvl_en                                  :  1;
     unsigned      reserved1                                 :  7;
     unsigned      rdlvl_gate_en                             :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_denali_DENALI_CTL_342_5600_t;

/*! @struct ncp_denali_DENALI_CTL_343_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_343_5600_t\n
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
 *   <td width="30%"> Defines the DFI tRDLVL_MAX timing parameter (in DFI
 *        clocks), the maximum cycles between a dfi_rdlvl_en
 *        or dfi_rdlvl_gate_en assertion and a valid dfi_rdlvl_resp.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_343_5600_t
 *
 */
 
typedef struct
{
     unsigned  int            tdfi_rdlvl_max;
} ncp_denali_DENALI_CTL_343_5600_t;

/*! @struct ncp_denali_DENALI_CTL_344_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_344_5600_t\n
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
 *     <td width="30%"> @param rdlvl_interval </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Number of long count sequences counted between automatic
 *        data eye training commands.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_error_status </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Holds the error associated with the data eye training
 *        error or gate training error interrupt. Uppermost
 *        bit set indicates a TDFI_RDLVL_RESP parameter violation.
 *        Next uppermost bit set indicates a TDFI_RDLVL_MAX
 *        parameter violation. Lower bits are reserved. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_344_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      rdlvl_interval                            : 16;
     unsigned      reserved0                                 :  6;
     unsigned      rdlvl_error_status                        :  2;
#else    /* Little Endian */
     unsigned      rdlvl_error_status                        :  2;
     unsigned      reserved0                                 :  6;
     unsigned      rdlvl_interval                            : 16;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_344_5600_t;

/*! @struct ncp_denali_DENALI_CTL_345_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_345_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param tdfi_rdcslat </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines the DFI tPHY_RDCSLAT timing parameter (in
 *        DFI PHY clocks), the maximum cycles between a read
 *        command and a dfi_rddata_cs_n assertion.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_phy_wrdata </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the DFI tPHY_WRDATA timing parameter (in DFI
 *        PHY clocks), the maximum cycles between a dfi_wrdata_en
 *        assertion and a dfi_wrdata signal.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_gate_interval </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of long count sequences counted between automatic
 *        gate training commands.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_345_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      tdfi_rdcslat                              :  7;
     unsigned      reserved1                                 :  5;
     unsigned      tdfi_phy_wrdata                           :  3;
     unsigned      rdlvl_gate_interval                       : 16;
#else    /* Little Endian */
     unsigned      rdlvl_gate_interval                       : 16;
     unsigned      tdfi_phy_wrdata                           :  3;
     unsigned      reserved1                                 :  5;
     unsigned      tdfi_rdcslat                              :  7;
     unsigned      reserved0                                 :  1;
#endif
} ncp_denali_DENALI_CTL_345_5600_t;

/*! @struct ncp_denali_DENALI_CTL_346_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_346_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param pda_invert_dev_cs2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the side for the device on CS 2. Set all bits
 *        for a device to 1 for A side.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_parin_lat </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the DFI tPARIN_LAT timing parameter (in DFI
 *        PHY clocks), the maximum cycles between a DFI command
 *        and a dfi_parity_in signal assertion.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param tdfi_wrcslat </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the DFI tPHY_WRCSLAT timing parameter (in
 *        DFI PHY clocks), the maximum cycles between a write
 *        command and a dfi_wrdata_cs_n assertion.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_346_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      pda_invert_dev_cs2                        : 16;
     unsigned      reserved0                                 :  5;
     unsigned      tdfi_parin_lat                            :  3;
     unsigned      reserved1                                 :  1;
     unsigned      tdfi_wrcslat                              :  7;
#else    /* Little Endian */
     unsigned      tdfi_wrcslat                              :  7;
     unsigned      reserved1                                 :  1;
     unsigned      tdfi_parin_lat                            :  3;
     unsigned      reserved0                                 :  5;
     unsigned      pda_invert_dev_cs2                        : 16;
#endif
} ncp_denali_DENALI_CTL_346_5600_t;

/*! @struct ncp_denali_DENALI_CTL_347_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_347_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param pda_invert_ecc_dev_cs3 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines the side for the ECC device on CS 3. Set all
 *        bits for a device to 1 for A side.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pda_invert_ecc_dev_cs2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the side for the ECC device on CS 2. Set all
 *        bits for a device to 1 for A side.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param pda_invert_dev_cs3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the side for the device on CS 3. Set all bits
 *        for a device to 1 for A side.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_347_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      pda_invert_ecc_dev_cs3                    :  2;
     unsigned      reserved1                                 :  6;
     unsigned      pda_invert_ecc_dev_cs2                    :  2;
     unsigned      pda_invert_dev_cs3                        : 16;
#else    /* Little Endian */
     unsigned      pda_invert_dev_cs3                        : 16;
     unsigned      pda_invert_ecc_dev_cs2                    :  2;
     unsigned      reserved1                                 :  6;
     unsigned      pda_invert_ecc_dev_cs3                    :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_denali_DENALI_CTL_347_5600_t;

/*! @struct ncp_denali_DENALI_CTL_348_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_348_5600_t\n
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
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 22 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lp_state </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Low power state status parameter. Bits (4:0) indicate
 *        the current low power state and bit (5) set indicates
 *        that status bits are valid. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved for future use. Refer to the regconfig files
 *        for the default programming.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reserved for future use. Refer to the regconfig files
 *        for the default programming.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_348_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      reserved2                                 :  2;
     unsigned      lp_state                                  :  6;
     unsigned      reserved3                                 :  7;
     unsigned      reserved1                                 :  1;
     unsigned      reserved0                                 :  8;
#else    /* Little Endian */
     unsigned      reserved0                                 :  8;
     unsigned      reserved1                                 :  1;
     unsigned      reserved3                                 :  7;
     unsigned      lp_state                                  :  6;
     unsigned      reserved2                                 :  2;
     unsigned      obsolete3                                 :  8;
#endif
} ncp_denali_DENALI_CTL_348_5600_t;

/*! @struct ncp_denali_DENALI_CTL_349_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_349_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr0_data_2 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 0 for chip
 *        select 2.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_349_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mr0_data_2                                : 18;
#else    /* Little Endian */
     unsigned      mr0_data_2                                : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_349_5600_t;

/*! @struct ncp_denali_DENALI_CTL_350_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_350_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr1_data_2 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 1 for chip
 *        select 2.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_350_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mr1_data_2                                : 18;
#else    /* Little Endian */
     unsigned      mr1_data_2                                : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_350_5600_t;

/*! @struct ncp_denali_DENALI_CTL_351_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_351_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr2_data_2 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 2 for chip
 *        select 2.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_351_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mr2_data_2                                : 18;
#else    /* Little Endian */
     unsigned      mr2_data_2                                : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_351_5600_t;

/*! @struct ncp_denali_DENALI_CTL_352_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_352_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mrsingle_data_2 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register single write
 *        to chip select 2.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_352_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mrsingle_data_2                           : 18;
#else    /* Little Endian */
     unsigned      mrsingle_data_2                           : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_352_5600_t;

/*! @struct ncp_denali_DENALI_CTL_353_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_353_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr3_data_2 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 3 for chip
 *        select 2.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_353_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mr3_data_2                                : 18;
#else    /* Little Endian */
     unsigned      mr3_data_2                                : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_353_5600_t;

/*! @struct ncp_denali_DENALI_CTL_354_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_354_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr4_data_2 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 4 for chip
 *        select 2.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_354_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mr4_data_2                                : 18;
#else    /* Little Endian */
     unsigned      mr4_data_2                                : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_354_5600_t;

/*! @struct ncp_denali_DENALI_CTL_355_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_355_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr5_data_2 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 5 for chip
 *        select 2.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_355_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mr5_data_2                                : 18;
#else    /* Little Endian */
     unsigned      mr5_data_2                                : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_355_5600_t;

/*! @struct ncp_denali_DENALI_CTL_356_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_356_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr6_data_2 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 6 for chip
 *        select 2.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_356_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mr6_data_2                                : 18;
#else    /* Little Endian */
     unsigned      mr6_data_2                                : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_356_5600_t;

/*! @struct ncp_denali_DENALI_CTL_357_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_357_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr0_data_3 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 0 for chip
 *        select 3.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_357_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mr0_data_3                                : 18;
#else    /* Little Endian */
     unsigned      mr0_data_3                                : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_357_5600_t;

/*! @struct ncp_denali_DENALI_CTL_358_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_358_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr1_data_3 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 1 for chip
 *        select 3.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_358_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mr1_data_3                                : 18;
#else    /* Little Endian */
     unsigned      mr1_data_3                                : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_358_5600_t;

/*! @struct ncp_denali_DENALI_CTL_359_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_359_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr2_data_3 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 2 for chip
 *        select 3.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_359_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mr2_data_3                                : 18;
#else    /* Little Endian */
     unsigned      mr2_data_3                                : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_359_5600_t;

/*! @struct ncp_denali_DENALI_CTL_360_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_360_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mrsingle_data_3 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register single write
 *        to chip select 3.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_360_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mrsingle_data_3                           : 18;
#else    /* Little Endian */
     unsigned      mrsingle_data_3                           : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_360_5600_t;

/*! @struct ncp_denali_DENALI_CTL_361_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_361_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr3_data_3 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 3 for chip
 *        select 3.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_361_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mr3_data_3                                : 18;
#else    /* Little Endian */
     unsigned      mr3_data_3                                : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_361_5600_t;

/*! @struct ncp_denali_DENALI_CTL_362_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_362_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr4_data_3 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 4 for chip
 *        select 3.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_362_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mr4_data_3                                : 18;
#else    /* Little Endian */
     unsigned      mr4_data_3                                : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_362_5600_t;

/*! @struct ncp_denali_DENALI_CTL_363_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_363_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr5_data_3 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 5 for chip
 *        select 3.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_363_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  6;
     unsigned      mr5_data_3                                : 18;
#else    /* Little Endian */
     unsigned      mr5_data_3                                : 18;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_denali_DENALI_CTL_363_5600_t;

/*! @struct ncp_denali_DENALI_CTL_364_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_364_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param memdata_ratio_2 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines the ratio of the DRAM device size on chip
 *        select 2 to the memory data width. Program with the
 *        log2 ratio of the memory data width to the device
 *        data width.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr6_data_3 </td>
 *     <td width="20%" align="center"> 18 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 6 for chip
 *        select 3.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_364_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  5;
     unsigned      memdata_ratio_2                           :  3;
     unsigned      reserved1                                 :  6;
     unsigned      mr6_data_3                                : 18;
#else    /* Little Endian */
     unsigned      mr6_data_3                                : 18;
     unsigned      reserved1                                 :  6;
     unsigned      memdata_ratio_2                           :  3;
     unsigned      reserved0                                 :  5;
#endif
} ncp_denali_DENALI_CTL_364_5600_t;

/*! @struct ncp_denali_DENALI_CTL_365_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_365_5600_t\n
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
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param memdata_ratio_3 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the ratio of the DRAM device size on chip
 *        select 3 to the memory data width. Program with the
 *        log2 ratio of the memory data width to the device
 *        data width.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_365_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  5;
     unsigned      memdata_ratio_3                           :  3;
#else    /* Little Endian */
     unsigned      memdata_ratio_3                           :  3;
     unsigned      reserved0                                 :  5;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_365_5600_t;

/*! @struct ncp_denali_DENALI_CTL_366_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_366_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param int_status </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Status of interrupt features in the controller. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_366_5600_t
 *
 */
 
typedef struct
{
     unsigned  int                int_status;
} ncp_denali_DENALI_CTL_366_5600_t;

/*! @struct ncp_denali_DENALI_CTL_367_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_367_5600_t\n
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
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param int_status </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Status of interrupt features in the controller. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_367_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  5;
     unsigned      int_status                                :  3;
#else    /* Little Endian */
     unsigned      int_status                                :  3;
     unsigned      reserved0                                 :  5;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_367_5600_t;

/*! @struct ncp_denali_DENALI_CTL_368_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_368_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param int_ack </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Clear mask of the INT_STATUS parameter. WRITE-ONLY </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_368_5600_t
 *
 */
 
typedef struct
{
     unsigned  int                   int_ack;
} ncp_denali_DENALI_CTL_368_5600_t;

/*! @struct ncp_denali_DENALI_CTL_369_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_369_5600_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param int_ack </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Clear mask of the INT_STATUS parameter. WRITE-ONLY </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_369_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  6;
     unsigned      int_ack                                   :  2;
#else    /* Little Endian */
     unsigned      int_ack                                   :  2;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_369_5600_t;

/*! @struct ncp_denali_DENALI_CTL_370_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_370_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param int_mask </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Mask for controller_int signals from the INT_STATUS
 *        parameter.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_370_5600_t
 *
 */
 
typedef struct
{
     unsigned  int                  int_mask;
} ncp_denali_DENALI_CTL_370_5600_t;

/*! @struct ncp_denali_DENALI_CTL_371_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_371_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param odt_rd_map_cs3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Determines which chip(s) will have termination when
 *        a read occurs on chip select 3. Set bit X to enable
 *        termination on csX when cs3 is performing a read.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odt_wr_map_cs2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Determines which chip(s) will have termination when
 *        a write occurs on chip select 2. Set bit X to enable
 *        termination on csX when cs2 is performing a write.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odt_rd_map_cs2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Determines which chip(s) will have termination when
 *        a read occurs on chip select 2. Set bit X to enable
 *        termination on csX when cs2 is performing a read.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param int_mask </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Mask for controller_int signals from the INT_STATUS
 *        parameter.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_371_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      odt_rd_map_cs3                            :  4;
     unsigned      reserved1                                 :  4;
     unsigned      odt_wr_map_cs2                            :  4;
     unsigned      reserved2                                 :  4;
     unsigned      odt_rd_map_cs2                            :  4;
     unsigned      reserved3                                 :  5;
     unsigned      int_mask                                  :  3;
#else    /* Little Endian */
     unsigned      int_mask                                  :  3;
     unsigned      reserved3                                 :  5;
     unsigned      odt_rd_map_cs2                            :  4;
     unsigned      reserved2                                 :  4;
     unsigned      odt_wr_map_cs2                            :  4;
     unsigned      reserved1                                 :  4;
     unsigned      odt_rd_map_cs3                            :  4;
     unsigned      reserved0                                 :  4;
#endif
} ncp_denali_DENALI_CTL_371_5600_t;

/*! @struct ncp_denali_DENALI_CTL_372_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_372_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param vref_val_dev1_2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 1 for CS 2. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev0_3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 0 for CS 3. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev0_2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 0 for CS 2. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odt_wr_map_cs3 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Determines which chip(s) will have termination when
 *        a write occurs on chip select 3. Set bit X to enable
 *        termination on csX when cs3 is performing a write.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_372_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      vref_val_dev1_2                           :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev0_3                           :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev0_2                           :  7;
     unsigned      reserved3                                 :  4;
     unsigned      odt_wr_map_cs3                            :  4;
#else    /* Little Endian */
     unsigned      odt_wr_map_cs3                            :  4;
     unsigned      reserved3                                 :  4;
     unsigned      vref_val_dev0_2                           :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev0_3                           :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev1_2                           :  7;
     unsigned      reserved0                                 :  1;
#endif
} ncp_denali_DENALI_CTL_372_5600_t;

/*! @struct ncp_denali_DENALI_CTL_373_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_373_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param vref_val_dev3_2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 3 for CS 2. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev2_3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 2 for CS 3. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev2_2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 2 for CS 2. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev1_3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 1 for CS 3. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_373_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      vref_val_dev3_2                           :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev2_3                           :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev2_2                           :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev1_3                           :  7;
#else    /* Little Endian */
     unsigned      vref_val_dev1_3                           :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev2_2                           :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev2_3                           :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev3_2                           :  7;
     unsigned      reserved0                                 :  1;
#endif
} ncp_denali_DENALI_CTL_373_5600_t;

/*! @struct ncp_denali_DENALI_CTL_374_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_374_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param vref_val_dev5_2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 5 for CS 2. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev4_3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 4 for CS 3. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev4_2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 4 for CS 2. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev3_3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 3 for CS 3. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_374_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      vref_val_dev5_2                           :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev4_3                           :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev4_2                           :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev3_3                           :  7;
#else    /* Little Endian */
     unsigned      vref_val_dev3_3                           :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev4_2                           :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev4_3                           :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev5_2                           :  7;
     unsigned      reserved0                                 :  1;
#endif
} ncp_denali_DENALI_CTL_374_5600_t;

/*! @struct ncp_denali_DENALI_CTL_375_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_375_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param vref_val_dev7_2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 7 for CS 2. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev6_3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 6 for CS 3. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev6_2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 6 for CS 2. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev5_3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 5 for CS 3. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_375_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      vref_val_dev7_2                           :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev6_3                           :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev6_2                           :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev5_3                           :  7;
#else    /* Little Endian */
     unsigned      vref_val_dev5_3                           :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev6_2                           :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev6_3                           :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev7_2                           :  7;
     unsigned      reserved0                                 :  1;
#endif
} ncp_denali_DENALI_CTL_375_5600_t;

/*! @struct ncp_denali_DENALI_CTL_376_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_376_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param vref_val_dev9_2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 9 for CS 2. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev8_3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 8 for CS 3. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev8_2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 8 for CS 2. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev7_3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 7 for CS 3. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_376_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      vref_val_dev9_2                           :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev8_3                           :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev8_2                           :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev7_3                           :  7;
#else    /* Little Endian */
     unsigned      vref_val_dev7_3                           :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev8_2                           :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev8_3                           :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev9_2                           :  7;
     unsigned      reserved0                                 :  1;
#endif
} ncp_denali_DENALI_CTL_376_5600_t;

/*! @struct ncp_denali_DENALI_CTL_377_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_377_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param vref_val_dev11_2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 11 for CS 2. If the VREF_PDA_EN parameter is
 *        not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev10_3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 10 for CS 3. If the VREF_PDA_EN parameter is
 *        not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev10_2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 10 for CS 2. If the VREF_PDA_EN parameter is
 *        not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev9_3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 9 for CS 3. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_377_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      vref_val_dev11_2                          :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev10_3                          :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev10_2                          :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev9_3                           :  7;
#else    /* Little Endian */
     unsigned      vref_val_dev9_3                           :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev10_2                          :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev10_3                          :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev11_2                          :  7;
     unsigned      reserved0                                 :  1;
#endif
} ncp_denali_DENALI_CTL_377_5600_t;

/*! @struct ncp_denali_DENALI_CTL_378_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_378_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param vref_val_dev13_2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 13 for CS 2. If the VREF_PDA_EN parameter is
 *        not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev12_3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 12 for CS 3. If the VREF_PDA_EN parameter is
 *        not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev12_2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 12 for CS 2. If the VREF_PDA_EN parameter is
 *        not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev11_3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 11 for CS 3. If the VREF_PDA_EN parameter is
 *        not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_378_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      vref_val_dev13_2                          :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev12_3                          :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev12_2                          :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev11_3                          :  7;
#else    /* Little Endian */
     unsigned      vref_val_dev11_3                          :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev12_2                          :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev12_3                          :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev13_2                          :  7;
     unsigned      reserved0                                 :  1;
#endif
} ncp_denali_DENALI_CTL_378_5600_t;

/*! @struct ncp_denali_DENALI_CTL_379_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_379_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param vref_val_dev15_2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 15 for CS 2. If the VREF_PDA_EN parameter is
 *        not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev14_3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 14 for CS 3. If the VREF_PDA_EN parameter is
 *        not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev14_2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 14 for CS 2. If the VREF_PDA_EN parameter is
 *        not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev13_3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 13 for CS 3. If the VREF_PDA_EN parameter is
 *        not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_379_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      vref_val_dev15_2                          :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev14_3                          :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev14_2                          :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev13_3                          :  7;
#else    /* Little Endian */
     unsigned      vref_val_dev13_3                          :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev14_2                          :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_dev14_3                          :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_dev15_2                          :  7;
     unsigned      reserved0                                 :  1;
#endif
} ncp_denali_DENALI_CTL_379_5600_t;

/*! @struct ncp_denali_DENALI_CTL_380_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_380_5600_t\n
 *   </td>
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
 *     <td width="30%"> @param vref_val_ecc_dev1_2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        ECC DRAM 1 for CS 2. If the VREF_PDA_EN parameter
 *        is not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_ecc_dev0_3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        ECC DRAM 0 for CS 3. If the VREF_PDA_EN parameter
 *        is not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_ecc_dev0_2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        ECC DRAM 0 for CS 2. If the VREF_PDA_EN parameter
 *        is not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_dev15_3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 15 for CS 3. If the VREF_PDA_EN parameter is
 *        not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_380_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      vref_val_ecc_dev1_2                       :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_ecc_dev0_3                       :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_ecc_dev0_2                       :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev15_3                          :  7;
#else    /* Little Endian */
     unsigned      vref_val_dev15_3                          :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_ecc_dev0_2                       :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_ecc_dev0_3                       :  7;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_ecc_dev1_2                       :  7;
     unsigned      reserved0                                 :  1;
#endif
} ncp_denali_DENALI_CTL_380_5600_t;

/*! @struct ncp_denali_DENALI_CTL_381_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_381_5600_t\n
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
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_val_ecc_dev1_3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        ECC DRAM 1 for CS 3. If the VREF_PDA_EN parameter
 *        is not set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_381_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  1;
     unsigned      vref_val_ecc_dev1_3                       :  7;
#else    /* Little Endian */
     unsigned      vref_val_ecc_dev1_3                       :  7;
     unsigned      reserved0                                 :  1;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_denali_DENALI_CTL_381_5600_t;

/*! @struct ncp_denali_DENALI_CTL_382_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_382_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param init_start </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 31 </td>
 *   <td width="30%"> DFI_INIT_START. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mc_w_dly </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 30 </td>
 *   <td width="30%"> MC_W_DATA_DLY. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param perf_mon_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Set to 1 to enable the performance logic and associated
 *        clock.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsv1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> UNUSED. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rresp_block </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 27 </td>
 *   <td width="30%"> Set to 1 to block any error response on the Read Response
 *        bus. Set to 0 to enable normal error responses.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsv2 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> UNUSED. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param awallstrb_gen_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> Set to 1 to enable the generation of the AWALLSTRB
 *        signal. This creates more efficient writes to the
 *        controller for 64 byte bursts. This signal is only
 *        useful when ECC is enabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rsv3 </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> UNUSED. </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_382_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      init_start                                :  1;
     unsigned      mc_w_dly                                  :  1;
     unsigned      perf_mon_en                               :  1;
     unsigned      rsv1                                      :  1;
     unsigned      rresp_block                               :  1;
     unsigned      rsv2                                      :  3;
     unsigned      awallstrb_gen_en                          :  1;
     unsigned      rsv3                                      : 23;
#else    /* Little Endian */
     unsigned      rsv3                                      : 23;
     unsigned      awallstrb_gen_en                          :  1;
     unsigned      rsv2                                      :  3;
     unsigned      rresp_block                               :  1;
     unsigned      rsv1                                      :  1;
     unsigned      perf_mon_en                               :  1;
     unsigned      mc_w_dly                                  :  1;
     unsigned      init_start                                :  1;
#endif
} ncp_denali_DENALI_CTL_382_5600_t;

/*! @struct ncp_denali_DENALI_CTL_383_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_383_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_383_5600_t
 *
 */
 
typedef struct
{
     unsigned  int            user_def_reg_1;
} ncp_denali_DENALI_CTL_383_5600_t;

/*! @struct ncp_denali_DENALI_CTL_384_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_384_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_384_5600_t
 *
 */
 
typedef struct
{
     unsigned  int         user_def_reg_ro_0;
} ncp_denali_DENALI_CTL_384_5600_t;

/*! @struct ncp_denali_DENALI_CTL_385_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_385_5600_t\n
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_385_5600_t
 *
 */
 
typedef struct
{
     unsigned  int         user_def_reg_ro_1;
} ncp_denali_DENALI_CTL_385_5600_t;

/*! @struct ncp_denali_DENALI_CTL_386_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_386_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param crc_mode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines CRC checking/verification support. Bit (0)
 *        controls write CRC; set to 1 to enable CRC generation/checking.
 *        Bit (1) defines where CRC is performed; set to 1 for
 *        MC responsibility or clear to 0 for PHY responsibility.
 *        Bit (1) has no meaning if bit (0) is cleared.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved for future use. Refer to the regconfig files
 *        for the default programming.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_wr_array_log2_depth </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reports the depth of the AXI port 0 write data array.
 *        Value is the log2 value of the depth. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_386_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved2                                 :  6;
     unsigned      crc_mode                                  :  2;
     unsigned      reserved3                                 :  6;
     unsigned      reserved1                                 : 10;
     unsigned      axi0_wr_array_log2_depth                  :  8;
#else    /* Little Endian */
     unsigned      axi0_wr_array_log2_depth                  :  8;
     unsigned      reserved1                                 : 10;
     unsigned      reserved3                                 :  6;
     unsigned      crc_mode                                  :  2;
     unsigned      reserved2                                 :  6;
#endif
} ncp_denali_DENALI_CTL_386_5600_t;

/*! @struct ncp_denali_DENALI_CTL_387_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_387_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dq_map_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the DQ mapping of the output DQ pins from
 *        the MC/PHY for DIMM 0. Bits (7:0) correspond to the
 *        DQ mapping index for nibble DQ (3:0) of the MC/PHY
 *        output, bits (15:8) correspond to the DQ mapping index
 *        for nibble DQ (7:4), etc. The DQ mapping indexes are
 *        the same as in the JEDEC DDR4 RDIMM specification.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_387_5600_t
 *
 */
 
typedef struct
{
     unsigned  int                  dq_map_0;
} ncp_denali_DENALI_CTL_387_5600_t;

/*! @struct ncp_denali_DENALI_CTL_388_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_388_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dq_map_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the DQ mapping of the output DQ pins from
 *        the MC/PHY for DIMM 0. Bits (7:0) correspond to the
 *        DQ mapping index for nibble DQ (3:0) of the MC/PHY
 *        output, bits (15:8) correspond to the DQ mapping index
 *        for nibble DQ (7:4), etc. The DQ mapping indexes are
 *        the same as in the JEDEC DDR4 RDIMM specification.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_388_5600_t
 *
 */
 
typedef struct
{
     unsigned  int                  dq_map_0;
} ncp_denali_DENALI_CTL_388_5600_t;

/*! @struct ncp_denali_DENALI_CTL_389_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_389_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dq_map_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the DQ mapping of the output DQ pins from
 *        the MC/PHY for DIMM 0. Bits (7:0) correspond to the
 *        DQ mapping index for nibble DQ (3:0) of the MC/PHY
 *        output, bits (15:8) correspond to the DQ mapping index
 *        for nibble DQ (7:4), etc. The DQ mapping indexes are
 *        the same as in the JEDEC DDR4 RDIMM specification.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_389_5600_t
 *
 */
 
typedef struct
{
     unsigned  int                  dq_map_0;
} ncp_denali_DENALI_CTL_389_5600_t;

/*! @struct ncp_denali_DENALI_CTL_390_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_390_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dq_map_0 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the DQ mapping of the output DQ pins from
 *        the MC/PHY for DIMM 0. Bits (7:0) correspond to the
 *        DQ mapping index for nibble DQ (3:0) of the MC/PHY
 *        output, bits (15:8) correspond to the DQ mapping index
 *        for nibble DQ (7:4), etc. The DQ mapping indexes are
 *        the same as in the JEDEC DDR4 RDIMM specification.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_390_5600_t
 *
 */
 
typedef struct
{
     unsigned  int                  dq_map_0;
} ncp_denali_DENALI_CTL_390_5600_t;

/*! @struct ncp_denali_DENALI_CTL_391_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_391_5600_t\n
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
 *     <td width="30%"> @param dq_map_odd_rank_swap_0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines which chip selects will have DQ bits swapped
 *        with respect to the DQ map specified in DQ_MAP_0 for
 *        DIMM 0. Bit 0 is swapped with 1, bit 2 with 3, bit
 *        4 with 5 and bit 6 with 7. Bit (0) controls cs0, bit
 *        (1) controls cs1, etc. Set each bit to 1 to enable
 *        for DIMM 0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq_map_0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the DQ mapping of the output DQ pins from
 *        the MC/PHY for DIMM 0. Bits (7:0) correspond to the
 *        DQ mapping index for nibble DQ (3:0) of the MC/PHY
 *        output, bits (15:8) correspond to the DQ mapping index
 *        for nibble DQ (7:4), etc. The DQ mapping indexes are
 *        the same as in the JEDEC DDR4 RDIMM specification.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_391_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      reserved0                                 :  4;
     unsigned      dq_map_odd_rank_swap_0                    :  4;
     unsigned      dq_map_0                                  : 16;
#else    /* Little Endian */
     unsigned      dq_map_0                                  : 16;
     unsigned      dq_map_odd_rank_swap_0                    :  4;
     unsigned      reserved0                                 :  4;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_denali_DENALI_CTL_391_5600_t;

/*! @struct ncp_denali_DENALI_CTL_392_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_392_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dq_map_1 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the DQ mapping of the output DQ pins from
 *        the MC/PHY for DIMM 1. Bits (7:0) correspond to the
 *        DQ mapping index for nibble DQ (3:0) of the MC/PHY
 *        output, bits (15:8) correspond to the DQ mapping index
 *        for nibble DQ (7:4), etc. The DQ mapping indexes are
 *        the same as in the JEDEC DDR4 RDIMM specification.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_392_5600_t
 *
 */
 
typedef struct
{
     unsigned  int                  dq_map_1;
} ncp_denali_DENALI_CTL_392_5600_t;

/*! @struct ncp_denali_DENALI_CTL_393_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_393_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dq_map_1 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the DQ mapping of the output DQ pins from
 *        the MC/PHY for DIMM 1. Bits (7:0) correspond to the
 *        DQ mapping index for nibble DQ (3:0) of the MC/PHY
 *        output, bits (15:8) correspond to the DQ mapping index
 *        for nibble DQ (7:4), etc. The DQ mapping indexes are
 *        the same as in the JEDEC DDR4 RDIMM specification.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_393_5600_t
 *
 */
 
typedef struct
{
     unsigned  int                  dq_map_1;
} ncp_denali_DENALI_CTL_393_5600_t;

/*! @struct ncp_denali_DENALI_CTL_394_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_394_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dq_map_1 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the DQ mapping of the output DQ pins from
 *        the MC/PHY for DIMM 1. Bits (7:0) correspond to the
 *        DQ mapping index for nibble DQ (3:0) of the MC/PHY
 *        output, bits (15:8) correspond to the DQ mapping index
 *        for nibble DQ (7:4), etc. The DQ mapping indexes are
 *        the same as in the JEDEC DDR4 RDIMM specification.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_394_5600_t
 *
 */
 
typedef struct
{
     unsigned  int                  dq_map_1;
} ncp_denali_DENALI_CTL_394_5600_t;

/*! @struct ncp_denali_DENALI_CTL_395_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_395_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param dq_map_1 </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the DQ mapping of the output DQ pins from
 *        the MC/PHY for DIMM 1. Bits (7:0) correspond to the
 *        DQ mapping index for nibble DQ (3:0) of the MC/PHY
 *        output, bits (15:8) correspond to the DQ mapping index
 *        for nibble DQ (7:4), etc. The DQ mapping indexes are
 *        the same as in the JEDEC DDR4 RDIMM specification.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_395_5600_t
 *
 */
 
typedef struct
{
     unsigned  int                  dq_map_1;
} ncp_denali_DENALI_CTL_395_5600_t;

/*! @struct ncp_denali_DENALI_CTL_396_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_396_5600_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Reserved for future use. Refer to the regconfig files
 *        for the default programming.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq_map_odd_rank_swap_1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Defines which chip selects will have DQ bits swapped
 *        with respect to the DQ map specified in DQ_MAP_1 for
 *        DIMM 1. Bit 0 is swapped with 1, bit 2 with 3, bit
 *        4 with 5 and bit 6 with 7. Bit (0) controls cs0, bit
 *        (1) controls cs1, etc. Set each bit to 1 to enable
 *        for DIMM 1.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq_map_1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the DQ mapping of the output DQ pins from
 *        the MC/PHY for DIMM 1. Bits (7:0) correspond to the
 *        DQ mapping index for nibble DQ (3:0) of the MC/PHY
 *        output, bits (15:8) correspond to the DQ mapping index
 *        for nibble DQ (7:4), etc. The DQ mapping indexes are
 *        the same as in the JEDEC DDR4 RDIMM specification.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_396_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved3                                 :  7;
     unsigned      reserved2                                 :  1;
     unsigned      reserved4                                 :  4;
     unsigned      dq_map_odd_rank_swap_1                    :  4;
     unsigned      dq_map_1                                  : 16;
#else    /* Little Endian */
     unsigned      dq_map_1                                  : 16;
     unsigned      dq_map_odd_rank_swap_1                    :  4;
     unsigned      reserved4                                 :  4;
     unsigned      reserved2                                 :  1;
     unsigned      reserved3                                 :  7;
#endif
} ncp_denali_DENALI_CTL_396_5600_t;

/*! @struct ncp_denali_DENALI_CTL_397_5600_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_denali_DENALI_CTL_397_5600_t\n
 *   </td>
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
 * Applies to: 5600 --> ncp_denali_DENALI_CTL_397_5600_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 30;
     unsigned      wr_order_req                              :  2;
#else    /* Little Endian */
     unsigned      wr_order_req                              :  2;
     unsigned      reserved0                                 : 30;
#endif
} ncp_denali_DENALI_CTL_397_5600_t;

#ifdef __cplusplus
}
#endif

#endif /* _NCP_DENALI_5600_REGS_H_ */
