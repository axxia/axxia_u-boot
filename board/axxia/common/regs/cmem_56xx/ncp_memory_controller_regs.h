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

#ifndef _NCP_MEMORY_CONTROLLER_REGS_H_
#define _NCP_MEMORY_CONTROLLER_REGS_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __UBOOT__
#include "ncp_sal_types.h"
#endif

/*! @struct ncp_memory_controller_DENALI_CTL_00_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_00_t\n
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
 *   <td width="30%"> Defines the class of DRAM memory which is connected
 *        to the controller.
 *   </td>
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_00_t
 *
 * Implemented by: 
 *      DENALI_CTL_00
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
} ncp_memory_controller_DENALI_CTL_00_t;

/*! @struct ncp_memory_controller_DENALI_CTL_01_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_01_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param max_cs_reg </td>
 *     <td width="20%" align="center"> 2 </td>
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_01_t
 *
 * Implemented by: 
 *      DENALI_CTL_01
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      read_data_fifo_depth                      :  8;
     unsigned      reserved0                                 :  6;
     unsigned      max_cs_reg                                :  2;
     unsigned      reserved1                                 :  4;
     unsigned      max_col_reg                               :  4;
     unsigned      reserved2                                 :  3;
     unsigned      max_row_reg                               :  5;
#else    /* Little Endian */
     unsigned      max_row_reg                               :  5;
     unsigned      reserved2                                 :  3;
     unsigned      max_col_reg                               :  4;
     unsigned      reserved1                                 :  4;
     unsigned      max_cs_reg                                :  2;
     unsigned      reserved0                                 :  6;
     unsigned      read_data_fifo_depth                      :  8;
#endif
} ncp_memory_controller_DENALI_CTL_01_t;

/*! @struct ncp_memory_controller_DENALI_CTL_02_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_02_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_02_t
 *
 * Implemented by: 
 *      DENALI_CTL_02
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
} ncp_memory_controller_DENALI_CTL_02_t;

/*! @struct ncp_memory_controller_DENALI_CTL_03_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_03_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_03_t
 *
 * Implemented by: 
 *      DENALI_CTL_03
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
} ncp_memory_controller_DENALI_CTL_03_t;

/*! @struct ncp_memory_controller_DENALI_CTL_04_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_04_t\n
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
 *     <td width="30%"> @param axi0_wrcmd_proc_fifo_log2_depth </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reports the depth of the AXI port 0 write command
 *        processing FIFO. Value is the log2 value of the depth.
 *        READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_trans_wrfifo_log2_depth </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reports the depth of the AXI port 0 transition write
 *        data FIFO. Value is the log2 value of the depth. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_wrfifo_log2_depth </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Reports the depth of the AXI port 0 write data FIFO.
 *        Value is the log2 value of the depth. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_04_t
 *
 * Implemented by: 
 *      DENALI_CTL_04
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      axi0_wrcmd_proc_fifo_log2_depth           :  8;
     unsigned      axi0_trans_wrfifo_log2_depth              :  8;
     unsigned      axi0_wrfifo_log2_depth                    :  8;
#else    /* Little Endian */
     unsigned      axi0_wrfifo_log2_depth                    :  8;
     unsigned      axi0_trans_wrfifo_log2_depth              :  8;
     unsigned      axi0_wrcmd_proc_fifo_log2_depth           :  8;
     unsigned      obsolete3                                 :  8;
#endif
} ncp_memory_controller_DENALI_CTL_04_t;

/*! @struct ncp_memory_controller_DENALI_CTL_05_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_05_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_05_t
 *
 * Implemented by: 
 *      DENALI_CTL_05
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
} ncp_memory_controller_DENALI_CTL_05_t;

/*! @struct ncp_memory_controller_DENALI_CTL_06_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_06_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_06_t
 *
 * Implemented by: 
 *      DENALI_CTL_06
 */
 
typedef struct
{
     unsigned  int                trst_pwron;
} ncp_memory_controller_DENALI_CTL_06_t;

/*! @struct ncp_memory_controller_DENALI_CTL_07_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_07_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_07_t
 *
 * Implemented by: 
 *      DENALI_CTL_07
 */
 
typedef struct
{
     unsigned  int              cke_inactive;
} ncp_memory_controller_DENALI_CTL_07_t;

/*! @struct ncp_memory_controller_DENALI_CTL_08_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_08_t\n
 *   </td>
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_08_t
 *
 * Implemented by: 
 *      DENALI_CTL_08
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
} ncp_memory_controller_DENALI_CTL_08_t;

/*! @struct ncp_memory_controller_DENALI_CTL_09_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_09_t\n
 *   </td>
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_09_t
 *
 * Implemented by: 
 *      DENALI_CTL_09
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
} ncp_memory_controller_DENALI_CTL_09_t;

/*! @struct ncp_memory_controller_DENALI_CTL_10_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_10_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_10_t
 *
 * Implemented by: 
 *      DENALI_CTL_10
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
} ncp_memory_controller_DENALI_CTL_10_t;

/*! @struct ncp_memory_controller_DENALI_CTL_11_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_11_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_11_t
 *
 * Implemented by: 
 *      DENALI_CTL_11
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
} ncp_memory_controller_DENALI_CTL_11_t;

/*! @struct ncp_memory_controller_DENALI_CTL_12_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_12_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_12_t
 *
 * Implemented by: 
 *      DENALI_CTL_12
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
} ncp_memory_controller_DENALI_CTL_12_t;

/*! @struct ncp_memory_controller_DENALI_CTL_13_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_13_t\n
 *   </td>
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_13_t
 *
 * Implemented by: 
 *      DENALI_CTL_13
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
} ncp_memory_controller_DENALI_CTL_13_t;

/*! @struct ncp_memory_controller_DENALI_CTL_14_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_14_t\n
 *   </td>
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_14_t
 *
 * Implemented by: 
 *      DENALI_CTL_14
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
} ncp_memory_controller_DENALI_CTL_14_t;

/*! @struct ncp_memory_controller_DENALI_CTL_15_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_15_t\n
 *   </td>
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
 *   <td width="30%"> Number of cycles after a multi-purpose register write
 *        command and before any other command.
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_15_t
 *
 * Implemented by: 
 *      DENALI_CTL_15
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
} ncp_memory_controller_DENALI_CTL_15_t;

/*! @struct ncp_memory_controller_DENALI_CTL_16_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_16_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_16_t
 *
 * Implemented by: 
 *      DENALI_CTL_16
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
} ncp_memory_controller_DENALI_CTL_16_t;

/*! @struct ncp_memory_controller_DENALI_CTL_17_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_17_t\n
 *   </td>
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
 *   <td width="30%"> DRAM supports allowing controller to issue commands
 *        to other banks while a bank is in auto pre-charge.
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_17_t
 *
 * Implemented by: 
 *      DENALI_CTL_17
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
} ncp_memory_controller_DENALI_CTL_17_t;

/*! @struct ncp_memory_controller_DENALI_CTL_18_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_18_t\n
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
 *   <td width="30%"> DRAM supports allowing the controller to execute auto
 *        pre-charge commands before the TRAS_MIN parameter
 *        expires. Set to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_18_t
 *
 * Implemented by: 
 *      DENALI_CTL_18
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
} ncp_memory_controller_DENALI_CTL_18_t;

/*! @struct ncp_memory_controller_DENALI_CTL_19_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_19_t\n
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
 *     <td width="30%"> @param address_mirroring </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Indicates which chip selects support address mirroring.
 *        Bit (0) controls cs0, bit (1) controls cs1, etc. Set
 *        each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved7 </td>
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_19_t
 *
 * Implemented by: 
 *      DENALI_CTL_19
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved4                                 :  7;
     unsigned      reserved3                                 :  1;
     unsigned      reserved5                                 :  7;
     unsigned      optimal_rmodw_en                          :  1;
     unsigned      reserved6                                 :  6;
     unsigned      address_mirroring                         :  2;
     unsigned      reserved7                                 :  7;
     unsigned      reg_dimm_enable                           :  1;
#else    /* Little Endian */
     unsigned      reg_dimm_enable                           :  1;
     unsigned      reserved7                                 :  7;
     unsigned      address_mirroring                         :  2;
     unsigned      reserved6                                 :  6;
     unsigned      optimal_rmodw_en                          :  1;
     unsigned      reserved5                                 :  7;
     unsigned      reserved3                                 :  1;
     unsigned      reserved4                                 :  7;
#endif
} ncp_memory_controller_DENALI_CTL_19_t;

/*! @struct ncp_memory_controller_DENALI_CTL_20_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_20_t\n
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
 *     <td width="30%"> @param reserved1 </td>
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_20_t
 *
 * Implemented by: 
 *      DENALI_CTL_20
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved1                                 :  7;
     unsigned      reserved0                                 :  1;
#else    /* Little Endian */
     unsigned      reserved0                                 :  1;
     unsigned      reserved1                                 :  7;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_memory_controller_DENALI_CTL_20_t;

/*! @struct ncp_memory_controller_DENALI_CTL_21_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_21_t\n
 *   </td>
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
 *     <td width="30%"> @param ca_parity_error_inject </td>
 *     <td width="20%" align="center"> 25 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Selects bit to corrupt on the CA bus for CA parity
 *        error injection.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_21_t
 *
 * Implemented by: 
 *      DENALI_CTL_21
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      ca_parity_error_inject                    : 25;
#else    /* Little Endian */
     unsigned      ca_parity_error_inject                    : 25;
     unsigned      reserved0                                 :  7;
#endif
} ncp_memory_controller_DENALI_CTL_21_t;

/*! @struct ncp_memory_controller_DENALI_CTL_22_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_22_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param ca_parity_cmd_execute_wait </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Time in controller cycles after a command issues from
 *        the controller when it is guaranteed to have executed
 *        in the DRAM without a parity error. Must include command
 *        delays from the controller to DRAM and ALERT_n from
 *        DRAM to controller delays.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ca_parity_error_ctl </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Control steps that the controller follows after a
 *        CA parity error occurs with DDR4. Bit (0) enables
 *        CA parity recovery. Set to 1 to enable. Bit (1) enables
 *        command holdoff at the port. If set to 1, the controller
 *        will stop accepting commands and write data on a command
 *        boundary at the port during CA parity error recovery.
 *        Bit (2) enables flushing of commands in the controller
 *        to get to fully IDLE state during recovery. Set to
 *        1 to enable. Bit (3) enables automatic self-refresh
 *        entry during recovery. Set to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ca_parity_error_resume </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Resume normal command execution after a CA parity
 *        error. Bit (0) resumes framework management (FM) commands.
 *        Bit (1) resumes data commands. Bit (2) is reserved.
 *        Set both bit (0) and bit (1) to 1 to re-enable normal
 *        operation.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_22_t
 *
 * Implemented by: 
 *      DENALI_CTL_22
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      ca_parity_cmd_execute_wait                :  8;
     unsigned      reserved0                                 :  4;
     unsigned      ca_parity_error_ctl                       :  4;
     unsigned      reserved1                                 :  5;
     unsigned      ca_parity_error_resume                    :  3;
     unsigned      reserved2                                 :  7;
     unsigned      ca_parity_error                           :  1;
#else    /* Little Endian */
     unsigned      ca_parity_error                           :  1;
     unsigned      reserved2                                 :  7;
     unsigned      ca_parity_error_resume                    :  3;
     unsigned      reserved1                                 :  5;
     unsigned      ca_parity_error_ctl                       :  4;
     unsigned      reserved0                                 :  4;
     unsigned      ca_parity_cmd_execute_wait                :  8;
#endif
} ncp_memory_controller_DENALI_CTL_22_t;

/*! @struct ncp_memory_controller_DENALI_CTL_23_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_23_t\n
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
 *     <td width="30%"> @param tref_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Issue auto-refresh commands to the DRAMs at the interval
 *        defined in the TREF parameter. Set to 1 to enable.
 *   </td>
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
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param arefresh </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Initiate auto-refresh at the end of the current burst
 *        boundary. Set to 1 to trigger. WRITE-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved6 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sref_entry_wait_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enables a delay of CA_PARITY_CMD_EXECUTE_WAIT cycles
 *        following a self-refresh entry command issuing from
 *        the controller before the lp_ext_done is returned
 *        for that self-refresh entry command.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_23_t
 *
 * Implemented by: 
 *      DENALI_CTL_23
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved3                                 :  7;
     unsigned      tref_enable                               :  1;
     unsigned      reserved4                                 :  7;
     unsigned      reserved2                                 :  1;
     unsigned      reserved5                                 :  7;
     unsigned      arefresh                                  :  1;
     unsigned      reserved6                                 :  7;
     unsigned      sref_entry_wait_enable                    :  1;
#else    /* Little Endian */
     unsigned      sref_entry_wait_enable                    :  1;
     unsigned      reserved6                                 :  7;
     unsigned      arefresh                                  :  1;
     unsigned      reserved5                                 :  7;
     unsigned      reserved2                                 :  1;
     unsigned      reserved4                                 :  7;
     unsigned      tref_enable                               :  1;
     unsigned      reserved3                                 :  7;
#endif
} ncp_memory_controller_DENALI_CTL_23_t;

/*! @struct ncp_memory_controller_DENALI_CTL_24_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_24_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_24_t
 *
 * Implemented by: 
 *      DENALI_CTL_24
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 16;
     unsigned      reserved0                                 :  6;
     unsigned      trfc                                      : 10;
#else    /* Little Endian */
     unsigned      trfc                                      : 10;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 : 16;
#endif
} ncp_memory_controller_DENALI_CTL_24_t;

/*! @struct ncp_memory_controller_DENALI_CTL_25_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_25_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_25_t
 *
 * Implemented by: 
 *      DENALI_CTL_25
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
} ncp_memory_controller_DENALI_CTL_25_t;

/*! @struct ncp_memory_controller_DENALI_CTL_26_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_26_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_26_t
 *
 * Implemented by: 
 *      DENALI_CTL_26
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
} ncp_memory_controller_DENALI_CTL_26_t;

/*! @struct ncp_memory_controller_DENALI_CTL_27_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_27_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_27_t
 *
 * Implemented by: 
 *      DENALI_CTL_27
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
} ncp_memory_controller_DENALI_CTL_27_t;

/*! @struct ncp_memory_controller_DENALI_CTL_28_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_28_t\n
 *   </td>
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_28_t
 *
 * Implemented by: 
 *      DENALI_CTL_28
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
} ncp_memory_controller_DENALI_CTL_28_t;

/*! @struct ncp_memory_controller_DENALI_CTL_29_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_29_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param lp_cmd </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Low power software command request interface. Bit
 *        (0) controls exit, bit (1) controls entry, bits (4:2)
 *        define the low power state, bit (5) controls memory
 *        clock gating, bit (6) controls controller clock gating,
 *        and bit (7) controls lock. WRITE-ONLY
 *   </td>
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lowpower_refresh_enable </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enable refreshes while in low power mode. Bit (0)
 *        controls cs0, bit (1) controls cs1, etc. Set each
 *        bit to 1 to disable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_29_t
 *
 * Implemented by: 
 *      DENALI_CTL_29
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      lp_cmd                                    :  8;
     unsigned      cksrx                                     :  8;
     unsigned      cksre                                     :  8;
     unsigned      reserved0                                 :  6;
     unsigned      lowpower_refresh_enable                   :  2;
#else    /* Little Endian */
     unsigned      lowpower_refresh_enable                   :  2;
     unsigned      reserved0                                 :  6;
     unsigned      cksre                                     :  8;
     unsigned      cksrx                                     :  8;
     unsigned      lp_cmd                                    :  8;
#endif
} ncp_memory_controller_DENALI_CTL_29_t;

/*! @struct ncp_memory_controller_DENALI_CTL_30_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_30_t\n
 *   </td>
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
 *     <td width="30%"> @param lp_auto_exit_en </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 24 </td>
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
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lp_auto_entry_en </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 16 </td>
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
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lp_arb_state </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
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
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lp_state </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Low power state status parameter. Bits (4:0) indicate
 *        the current low power state and bit (5) set indicates
 *        that status bits are valid. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_30_t
 *
 * Implemented by: 
 *      DENALI_CTL_30
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  5;
     unsigned      lp_auto_exit_en                           :  3;
     unsigned      reserved1                                 :  5;
     unsigned      lp_auto_entry_en                          :  3;
     unsigned      reserved2                                 :  4;
     unsigned      lp_arb_state                              :  4;
     unsigned      reserved3                                 :  2;
     unsigned      lp_state                                  :  6;
#else    /* Little Endian */
     unsigned      lp_state                                  :  6;
     unsigned      reserved3                                 :  2;
     unsigned      lp_arb_state                              :  4;
     unsigned      reserved2                                 :  4;
     unsigned      lp_auto_entry_en                          :  3;
     unsigned      reserved1                                 :  5;
     unsigned      lp_auto_exit_en                           :  3;
     unsigned      reserved0                                 :  5;
#endif
} ncp_memory_controller_DENALI_CTL_30_t;

/*! @struct ncp_memory_controller_DENALI_CTL_31_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_31_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param lp_auto_sr_idle </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Number of long count sequences until the controller
 *        will place memory in self-refresh.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lp_auto_pd_idle </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the idle time until the controller will place
 *        memory in active power-down.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param lp_auto_mem_gate_en </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enable memory clock gating when entering a low power
 *        state via the auto low power counters. Bit (0) controls
 *        power-down, and bit (1) controls self-refresh. Set
 *        each bit to 1 to enable.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_31_t
 *
 * Implemented by: 
 *      DENALI_CTL_31
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      lp_auto_sr_idle                           :  8;
     unsigned      reserved0                                 :  4;
     unsigned      lp_auto_pd_idle                           : 12;
     unsigned      reserved1                                 :  6;
     unsigned      lp_auto_mem_gate_en                       :  2;
#else    /* Little Endian */
     unsigned      lp_auto_mem_gate_en                       :  2;
     unsigned      reserved1                                 :  6;
     unsigned      lp_auto_pd_idle                           : 12;
     unsigned      reserved0                                 :  4;
     unsigned      lp_auto_sr_idle                           :  8;
#endif
} ncp_memory_controller_DENALI_CTL_31_t;

/*! @struct ncp_memory_controller_DENALI_CTL_32_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_32_t\n
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
 *     <td width="30%"> @param lp_auto_sr_mc_gate_idle </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of long count sequences until the controller
 *        will place memory in self-refresh with controller
 *        and memory clock gating.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_32_t
 *
 * Implemented by: 
 *      DENALI_CTL_32
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 : 16;
     unsigned      reserved1                                 :  8;
     unsigned      lp_auto_sr_mc_gate_idle                   :  8;
#else    /* Little Endian */
     unsigned      lp_auto_sr_mc_gate_idle                   :  8;
     unsigned      reserved1                                 :  8;
     unsigned      obsolete2                                 : 16;
#endif
} ncp_memory_controller_DENALI_CTL_32_t;

/*! @struct ncp_memory_controller_DENALI_CTL_33_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_33_t\n
 *   </td>
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
 *     <td width="30%"> @param write </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 25 </td>
 *   <td width="30%"> One shot write </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param write_modereg </td>
 *     <td width="20%" align="center"> 25 </td>
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_33_t
 *
 * Implemented by: 
 *      DENALI_CTL_33
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      write                                     :  1;
     unsigned      write_modereg                             : 25;
#else    /* Little Endian */
     unsigned      write_modereg                             : 25;
     unsigned      write                                     :  1;
     unsigned      reserved0                                 :  6;
#endif
} ncp_memory_controller_DENALI_CTL_33_t;

/*! @struct ncp_memory_controller_DENALI_CTL_34_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_34_t\n
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
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param read_mpr_go </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Bit set triggers the read for READ_MPR. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param read_mpr </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Read the specified multi-purpose register. Bits (1:0)
 *        define the MPR page, middle bits define the target
 *        chip select.
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
 *        a WRITE_MODEREG parameter programming error. Bit (1)
 *        is Reserved. Bit (2) is Reserved. Bit (3) set indicates
 *        a self refresh or deep power down error. Bit (4) is
 *        Reserved. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_34_t
 *
 * Implemented by: 
 *      DENALI_CTL_34
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      reserved2                                 :  4;
     unsigned      read_mpr_go                               :  1;
     unsigned      read_mpr                                  :  3;
     unsigned      reserved3                                 :  7;
     unsigned      reserved1                                 :  1;
     unsigned      mrw_status                                :  8;
#else    /* Little Endian */
     unsigned      mrw_status                                :  8;
     unsigned      reserved1                                 :  1;
     unsigned      reserved3                                 :  7;
     unsigned      read_mpr                                  :  3;
     unsigned      read_mpr_go                               :  1;
     unsigned      reserved2                                 :  4;
     unsigned      obsolete3                                 :  8;
#endif
} ncp_memory_controller_DENALI_CTL_34_t;

/*! @struct ncp_memory_controller_DENALI_CTL_35_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_35_t\n
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
 *   <td width="30%"> Data read from the multi-purpose register 0 read requested
 *        by the READ_MPR parameter. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_35_t
 *
 * Implemented by: 
 *      DENALI_CTL_35
 */
 
typedef struct
{
     unsigned  int               mprr_data_0;
} ncp_memory_controller_DENALI_CTL_35_t;

/*! @struct ncp_memory_controller_DENALI_CTL_36_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_36_t\n
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
 *     <td width="30%"> @param mprr_data_0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data read from the multi-purpose register 0 read requested
 *        by the READ_MPR parameter. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_36_t
 *
 * Implemented by: 
 *      DENALI_CTL_36
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      mprr_data_0                               :  8;
#else    /* Little Endian */
     unsigned      mprr_data_0                               :  8;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_memory_controller_DENALI_CTL_36_t;

/*! @struct ncp_memory_controller_DENALI_CTL_37_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_37_t\n
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
 *   <td width="30%"> Data read from the multi-purpose register 1 read requested
 *        by the READ_MPR parameter. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_37_t
 *
 * Implemented by: 
 *      DENALI_CTL_37
 */
 
typedef struct
{
     unsigned  int               mprr_data_1;
} ncp_memory_controller_DENALI_CTL_37_t;

/*! @struct ncp_memory_controller_DENALI_CTL_38_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_38_t\n
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
 *     <td width="30%"> @param mprr_data_1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data read from the multi-purpose register 1 read requested
 *        by the READ_MPR parameter. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_38_t
 *
 * Implemented by: 
 *      DENALI_CTL_38
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      mprr_data_1                               :  8;
#else    /* Little Endian */
     unsigned      mprr_data_1                               :  8;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_memory_controller_DENALI_CTL_38_t;

/*! @struct ncp_memory_controller_DENALI_CTL_39_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_39_t\n
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
 *   <td width="30%"> Data read from the multi-purpose register 2 read requested
 *        by the READ_MPR parameter. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_39_t
 *
 * Implemented by: 
 *      DENALI_CTL_39
 */
 
typedef struct
{
     unsigned  int               mprr_data_2;
} ncp_memory_controller_DENALI_CTL_39_t;

/*! @struct ncp_memory_controller_DENALI_CTL_40_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_40_t\n
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
 *     <td width="30%"> @param mprr_data_2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data read from the multi-purpose register 2 read requested
 *        by the READ_MPR parameter. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_40_t
 *
 * Implemented by: 
 *      DENALI_CTL_40
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      mprr_data_2                               :  8;
#else    /* Little Endian */
     unsigned      mprr_data_2                               :  8;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_memory_controller_DENALI_CTL_40_t;

/*! @struct ncp_memory_controller_DENALI_CTL_41_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_41_t\n
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
 *   <td width="30%"> Data read from the multi-purpose register 3 read requested
 *        by the READ_MPR parameter. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_41_t
 *
 * Implemented by: 
 *      DENALI_CTL_41
 */
 
typedef struct
{
     unsigned  int               mprr_data_3;
} ncp_memory_controller_DENALI_CTL_41_t;

/*! @struct ncp_memory_controller_DENALI_CTL_42_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_42_t\n
 *   </td>
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
 *     <td width="30%"> @param mr0_data_0 </td>
 *     <td width="20%" align="center"> 17 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Data to program into memory mode register 0 for chip
 *        select 0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mprr_data_3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data read from the multi-purpose register 3 read requested
 *        by the READ_MPR parameter. READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_42_t
 *
 * Implemented by: 
 *      DENALI_CTL_42
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      mr0_data_0                                : 17;
     unsigned      mprr_data_3                               :  8;
#else    /* Little Endian */
     unsigned      mprr_data_3                               :  8;
     unsigned      mr0_data_0                                : 17;
     unsigned      reserved0                                 :  7;
#endif
} ncp_memory_controller_DENALI_CTL_42_t;

/*! @struct ncp_memory_controller_DENALI_CTL_43_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_43_t\n
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
 *     <td width="30%"> @param mr1_data_0 </td>
 *     <td width="20%" align="center"> 17 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 1 for chip
 *        select 0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_43_t
 *
 * Implemented by: 
 *      DENALI_CTL_43
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  7;
     unsigned      mr1_data_0                                : 17;
#else    /* Little Endian */
     unsigned      mr1_data_0                                : 17;
     unsigned      reserved0                                 :  7;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_memory_controller_DENALI_CTL_43_t;

/*! @struct ncp_memory_controller_DENALI_CTL_44_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_44_t\n
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
 *     <td width="30%"> @param mr2_data_0 </td>
 *     <td width="20%" align="center"> 17 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 2 for chip
 *        select 0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_44_t
 *
 * Implemented by: 
 *      DENALI_CTL_44
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  7;
     unsigned      mr2_data_0                                : 17;
#else    /* Little Endian */
     unsigned      mr2_data_0                                : 17;
     unsigned      reserved0                                 :  7;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_memory_controller_DENALI_CTL_44_t;

/*! @struct ncp_memory_controller_DENALI_CTL_45_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_45_t\n
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
 *     <td width="30%"> @param mrsingle_data_0 </td>
 *     <td width="20%" align="center"> 17 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register single write
 *        to chip select 0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_45_t
 *
 * Implemented by: 
 *      DENALI_CTL_45
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  7;
     unsigned      mrsingle_data_0                           : 17;
#else    /* Little Endian */
     unsigned      mrsingle_data_0                           : 17;
     unsigned      reserved0                                 :  7;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_memory_controller_DENALI_CTL_45_t;

/*! @struct ncp_memory_controller_DENALI_CTL_46_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_46_t\n
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
 *     <td width="30%"> @param mr3_data_0 </td>
 *     <td width="20%" align="center"> 17 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 3 for chip
 *        select 0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_46_t
 *
 * Implemented by: 
 *      DENALI_CTL_46
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  7;
     unsigned      mr3_data_0                                : 17;
#else    /* Little Endian */
     unsigned      mr3_data_0                                : 17;
     unsigned      reserved0                                 :  7;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_memory_controller_DENALI_CTL_46_t;

/*! @struct ncp_memory_controller_DENALI_CTL_47_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_47_t\n
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
 *     <td width="30%"> @param mr4_data_0 </td>
 *     <td width="20%" align="center"> 17 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 4 for chip
 *        select 0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_47_t
 *
 * Implemented by: 
 *      DENALI_CTL_47
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  7;
     unsigned      mr4_data_0                                : 17;
#else    /* Little Endian */
     unsigned      mr4_data_0                                : 17;
     unsigned      reserved0                                 :  7;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_memory_controller_DENALI_CTL_47_t;

/*! @struct ncp_memory_controller_DENALI_CTL_48_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_48_t\n
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
 *     <td width="30%"> @param mr5_data_0 </td>
 *     <td width="20%" align="center"> 17 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 5 for chip
 *        select 0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_48_t
 *
 * Implemented by: 
 *      DENALI_CTL_48
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  7;
     unsigned      mr5_data_0                                : 17;
#else    /* Little Endian */
     unsigned      mr5_data_0                                : 17;
     unsigned      reserved0                                 :  7;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_memory_controller_DENALI_CTL_48_t;

/*! @struct ncp_memory_controller_DENALI_CTL_49_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_49_t\n
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
 *     <td width="30%"> @param mr6_data_0 </td>
 *     <td width="20%" align="center"> 17 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 6 for chip
 *        select 0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_49_t
 *
 * Implemented by: 
 *      DENALI_CTL_49
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  7;
     unsigned      mr6_data_0                                : 17;
#else    /* Little Endian */
     unsigned      mr6_data_0                                : 17;
     unsigned      reserved0                                 :  7;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_memory_controller_DENALI_CTL_49_t;

/*! @struct ncp_memory_controller_DENALI_CTL_50_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_50_t\n
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
 *     <td width="30%"> @param mr0_data_1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 0 for chip
 *        select 1.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_50_t
 *
 * Implemented by: 
 *      DENALI_CTL_50
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  7;
     unsigned      mr0_data_1                                : 17;
#else    /* Little Endian */
     unsigned      mr0_data_1                                : 17;
     unsigned      reserved0                                 :  7;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_memory_controller_DENALI_CTL_50_t;

/*! @struct ncp_memory_controller_DENALI_CTL_51_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_51_t\n
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
 *     <td width="30%"> @param mr1_data_1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 1 for chip
 *        select 1.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_51_t
 *
 * Implemented by: 
 *      DENALI_CTL_51
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  7;
     unsigned      mr1_data_1                                : 17;
#else    /* Little Endian */
     unsigned      mr1_data_1                                : 17;
     unsigned      reserved0                                 :  7;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_memory_controller_DENALI_CTL_51_t;

/*! @struct ncp_memory_controller_DENALI_CTL_52_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_52_t\n
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
 *     <td width="30%"> @param mr2_data_1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 2 for chip
 *        select 1.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_52_t
 *
 * Implemented by: 
 *      DENALI_CTL_52
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  7;
     unsigned      mr2_data_1                                : 17;
#else    /* Little Endian */
     unsigned      mr2_data_1                                : 17;
     unsigned      reserved0                                 :  7;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_memory_controller_DENALI_CTL_52_t;

/*! @struct ncp_memory_controller_DENALI_CTL_53_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_53_t\n
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
 *     <td width="30%"> @param mrsingle_data_1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register single write
 *        to chip select 1.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_53_t
 *
 * Implemented by: 
 *      DENALI_CTL_53
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  7;
     unsigned      mrsingle_data_1                           : 17;
#else    /* Little Endian */
     unsigned      mrsingle_data_1                           : 17;
     unsigned      reserved0                                 :  7;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_memory_controller_DENALI_CTL_53_t;

/*! @struct ncp_memory_controller_DENALI_CTL_54_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_54_t\n
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
 *     <td width="30%"> @param mr3_data_1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 3 for chip
 *        select 1.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_54_t
 *
 * Implemented by: 
 *      DENALI_CTL_54
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  7;
     unsigned      mr3_data_1                                : 17;
#else    /* Little Endian */
     unsigned      mr3_data_1                                : 17;
     unsigned      reserved0                                 :  7;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_memory_controller_DENALI_CTL_54_t;

/*! @struct ncp_memory_controller_DENALI_CTL_55_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_55_t\n
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
 *     <td width="30%"> @param mr4_data_1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 4 for chip
 *        select 1.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_55_t
 *
 * Implemented by: 
 *      DENALI_CTL_55
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  7;
     unsigned      mr4_data_1                                : 17;
#else    /* Little Endian */
     unsigned      mr4_data_1                                : 17;
     unsigned      reserved0                                 :  7;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_memory_controller_DENALI_CTL_55_t;

/*! @struct ncp_memory_controller_DENALI_CTL_56_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_56_t\n
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
 *     <td width="30%"> @param mr5_data_1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 5 for chip
 *        select 1.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_56_t
 *
 * Implemented by: 
 *      DENALI_CTL_56
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 :  8;
     unsigned      reserved0                                 :  7;
     unsigned      mr5_data_1                                : 17;
#else    /* Little Endian */
     unsigned      mr5_data_1                                : 17;
     unsigned      reserved0                                 :  7;
     unsigned      obsolete1                                 :  8;
#endif
} ncp_memory_controller_DENALI_CTL_56_t;

/*! @struct ncp_memory_controller_DENALI_CTL_57_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_57_t\n
 *   </td>
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
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mr6_data_1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Data to program into memory mode register 6 for chip
 *        select 1.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_57_t
 *
 * Implemented by: 
 *      DENALI_CTL_57
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      bist_go                                   :  1;
     unsigned      reserved1                                 :  7;
     unsigned      mr6_data_1                                : 17;
#else    /* Little Endian */
     unsigned      mr6_data_1                                : 17;
     unsigned      reserved1                                 :  7;
     unsigned      bist_go                                   :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_memory_controller_DENALI_CTL_57_t;

/*! @struct ncp_memory_controller_DENALI_CTL_58_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_58_t\n
 *   </td>
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_58_t
 *
 * Implemented by: 
 *      DENALI_CTL_58
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
} ncp_memory_controller_DENALI_CTL_58_t;

/*! @struct ncp_memory_controller_DENALI_CTL_59_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_59_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_59_t
 *
 * Implemented by: 
 *      DENALI_CTL_59
 */
 
typedef struct
{
     unsigned  int        bist_start_address;
} ncp_memory_controller_DENALI_CTL_59_t;

/*! @struct ncp_memory_controller_DENALI_CTL_60_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_60_t\n
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
 *     <td width="30%"> @param bist_start_address </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Start BIST checking at this address. </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_60_t
 *
 * Implemented by: 
 *      DENALI_CTL_60
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  6;
     unsigned      bist_start_address                        :  2;
#else    /* Little Endian */
     unsigned      bist_start_address                        :  2;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_memory_controller_DENALI_CTL_60_t;

/*! @struct ncp_memory_controller_DENALI_CTL_61_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_61_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_61_t
 *
 * Implemented by: 
 *      DENALI_CTL_61
 */
 
typedef struct
{
     unsigned  int            bist_data_mask;
} ncp_memory_controller_DENALI_CTL_61_t;

/*! @struct ncp_memory_controller_DENALI_CTL_62_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_62_t\n
 *   </td>
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
 *     <td width="30%"> @param xor_check_bits </td>
 *     <td width="20%" align="center"> 14 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Value to xor with generated ECC codes for forced write
 *        check.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fwc </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Force a write check. Xor the XOR_CHECK_BITS parameter
 *        with the ECC code and write to memory. This will cause
 *        the XORed ECC code to modify data when the address
 *        is read. Writetn data will NOT match read data because
 *        of ECC modification. Set to 1 to trigger. WRITE-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_62_t
 *
 * Implemented by: 
 *      DENALI_CTL_62
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  2;
     unsigned      xor_check_bits                            : 14;
     unsigned      reserved1                                 :  7;
     unsigned      fwc                                       :  1;
     unsigned      reserved2                                 :  7;
     unsigned      ecc_en                                    :  1;
#else    /* Little Endian */
     unsigned      ecc_en                                    :  1;
     unsigned      reserved2                                 :  7;
     unsigned      fwc                                       :  1;
     unsigned      reserved1                                 :  7;
     unsigned      xor_check_bits                            : 14;
     unsigned      reserved0                                 :  2;
#endif
} ncp_memory_controller_DENALI_CTL_62_t;

/*! @struct ncp_memory_controller_DENALI_CTL_63_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_63_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_63_t
 *
 * Implemented by: 
 *      DENALI_CTL_63
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
} ncp_memory_controller_DENALI_CTL_63_t;

/*! @struct ncp_memory_controller_DENALI_CTL_64_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_64_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_64_t
 *
 * Implemented by: 
 *      DENALI_CTL_64
 */
 
typedef struct
{
     unsigned  int                ecc_u_addr;
} ncp_memory_controller_DENALI_CTL_64_t;

/*! @struct ncp_memory_controller_DENALI_CTL_65_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_65_t\n
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
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_u_synd </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Syndrome for uncorrectable ECC event. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_u_addr </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address of uncorrectable ECC event. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_65_t
 *
 * Implemented by: 
 *      DENALI_CTL_65
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 : 16;
     unsigned      reserved0                                 :  1;
     unsigned      ecc_u_synd                                :  7;
     unsigned      reserved1                                 :  6;
     unsigned      ecc_u_addr                                :  2;
#else    /* Little Endian */
     unsigned      ecc_u_addr                                :  2;
     unsigned      reserved1                                 :  6;
     unsigned      ecc_u_synd                                :  7;
     unsigned      reserved0                                 :  1;
     unsigned      obsolete2                                 : 16;
#endif
} ncp_memory_controller_DENALI_CTL_65_t;

/*! @struct ncp_memory_controller_DENALI_CTL_66_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_66_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_66_t
 *
 * Implemented by: 
 *      DENALI_CTL_66
 */
 
typedef struct
{
     unsigned  int                ecc_u_data;
} ncp_memory_controller_DENALI_CTL_66_t;

/*! @struct ncp_memory_controller_DENALI_CTL_67_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_67_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_67_t
 *
 * Implemented by: 
 *      DENALI_CTL_67
 */
 
typedef struct
{
     unsigned  int                ecc_c_addr;
} ncp_memory_controller_DENALI_CTL_67_t;

/*! @struct ncp_memory_controller_DENALI_CTL_68_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_68_t\n
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
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_c_synd </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Syndrome for correctable ECC event. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_c_addr </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address of correctable ECC event. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_68_t
 *
 * Implemented by: 
 *      DENALI_CTL_68
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 : 16;
     unsigned      reserved0                                 :  1;
     unsigned      ecc_c_synd                                :  7;
     unsigned      reserved1                                 :  6;
     unsigned      ecc_c_addr                                :  2;
#else    /* Little Endian */
     unsigned      ecc_c_addr                                :  2;
     unsigned      reserved1                                 :  6;
     unsigned      ecc_c_synd                                :  7;
     unsigned      reserved0                                 :  1;
     unsigned      obsolete2                                 : 16;
#endif
} ncp_memory_controller_DENALI_CTL_68_t;

/*! @struct ncp_memory_controller_DENALI_CTL_69_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_69_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_69_t
 *
 * Implemented by: 
 *      DENALI_CTL_69
 */
 
typedef struct
{
     unsigned  int                ecc_c_data;
} ncp_memory_controller_DENALI_CTL_69_t;

/*! @struct ncp_memory_controller_DENALI_CTL_70_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_70_t\n
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
 *     <td width="30%"> @param long_count_mask </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Reduces the length of the long counter from 1024 cycles.
 *        The only supported values are 0x00 (1024 cycles),
 *        0x10 (512 clocks), 0x18 (256 clocks), 0x1C (128 clocks),
 *        0x1E (64 clocks) and 0x1F (32 clocks).
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param obsolete0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> PADDING_BITS </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_70_t
 *
 * Implemented by: 
 *      DENALI_CTL_70
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete2                                 :  8;
     unsigned      reserved0                                 :  3;
     unsigned      long_count_mask                           :  5;
     unsigned      obsolete0                                 : 16;
#else    /* Little Endian */
     unsigned      obsolete0                                 : 16;
     unsigned      long_count_mask                           :  5;
     unsigned      reserved0                                 :  3;
     unsigned      obsolete2                                 :  8;
#endif
} ncp_memory_controller_DENALI_CTL_70_t;

/*! @struct ncp_memory_controller_DENALI_CTL_71_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_71_t\n
 *   </td>
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
 *     <td width="30%"> @param zqcl </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Number of cycles needed for a ZQCL command. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zqinit </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of cycles needed for a ZQINIT command. </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_71_t
 *
 * Implemented by: 
 *      DENALI_CTL_71
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  4;
     unsigned      zqcl                                      : 12;
     unsigned      reserved1                                 :  4;
     unsigned      zqinit                                    : 12;
#else    /* Little Endian */
     unsigned      zqinit                                    : 12;
     unsigned      reserved1                                 :  4;
     unsigned      zqcl                                      : 12;
     unsigned      reserved0                                 :  4;
#endif
} ncp_memory_controller_DENALI_CTL_71_t;

/*! @struct ncp_memory_controller_DENALI_CTL_72_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_72_t\n
 *   </td>
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
 *        exit. Program to 0x1 for ZQ Short (ZQCS) or program
 *        to 0x2 for ZQ Long (ZQCL). Clearing to 0x0 will not
 *        trigger any ZQ command on self-refresh exit.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zq_req </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> User request to initiate a ZQ calibration. Program
 *        to 0x1 for ZQ Short (ZQCS) or program to 0x2 for ZQ
 *        Long (ZQCL). Clearing to 0x0 will not trigger any
 *        ZQ command. This parameter should only be written
 *        when the ZQ_IN_PROGRESS parameter is cleared to 'b0.
 *        WRITE-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zqcs </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of cycles needed for a ZQCS command. </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_72_t
 *
 * Implemented by: 
 *      DENALI_CTL_72
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      zq_on_sref_exit                           :  2;
     unsigned      reserved1                                 :  6;
     unsigned      zq_req                                    :  2;
     unsigned      reserved2                                 :  4;
     unsigned      zqcs                                      : 12;
#else    /* Little Endian */
     unsigned      zqcs                                      : 12;
     unsigned      reserved2                                 :  4;
     unsigned      zq_req                                    :  2;
     unsigned      reserved1                                 :  6;
     unsigned      zq_on_sref_exit                           :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_memory_controller_DENALI_CTL_72_t;

/*! @struct ncp_memory_controller_DENALI_CTL_73_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_73_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_73_t
 *
 * Implemented by: 
 *      DENALI_CTL_73
 */
 
typedef struct
{
     unsigned  int               zq_interval;
} ncp_memory_controller_DENALI_CTL_73_t;

/*! @struct ncp_memory_controller_DENALI_CTL_74_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_74_t\n
 *   </td>
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
 *        one chip select or all chip selects. When rotation
 *        is off, all chip selects will be calibrated, requiring
 *        a longer time frame, but ZQ calibration will need
 *        to be performed less frequently. Set to 1 for rotating
 *        CS.
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_74_t
 *
 * Implemented by: 
 *      DENALI_CTL_74
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
} ncp_memory_controller_DENALI_CTL_74_t;

/*! @struct ncp_memory_controller_DENALI_CTL_75_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_75_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_75_t
 *
 * Implemented by: 
 *      DENALI_CTL_75
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
} ncp_memory_controller_DENALI_CTL_75_t;

/*! @struct ncp_memory_controller_DENALI_CTL_76_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_76_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_76_t
 *
 * Implemented by: 
 *      DENALI_CTL_76
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
} ncp_memory_controller_DENALI_CTL_76_t;

/*! @struct ncp_memory_controller_DENALI_CTL_77_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_77_t\n
 *   </td>
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_77_t
 *
 * Implemented by: 
 *      DENALI_CTL_77
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
} ncp_memory_controller_DENALI_CTL_77_t;

/*! @struct ncp_memory_controller_DENALI_CTL_78_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_78_t\n
 *   </td>
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_78_t
 *
 * Implemented by: 
 *      DENALI_CTL_78
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
} ncp_memory_controller_DENALI_CTL_78_t;

/*! @struct ncp_memory_controller_DENALI_CTL_79_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_79_t\n
 *   </td>
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
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param num_q_entries_act_disable </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of queue entries in which ACT requests will
 *        be disabled. Setting to X will disable ACT requests
 *        from the X entries lowest in the command queue.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_79_t
 *
 * Implemented by: 
 *      DENALI_CTL_79
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
     unsigned      reserved3                                 :  5;
     unsigned      num_q_entries_act_disable                 :  3;
#else    /* Little Endian */
     unsigned      num_q_entries_act_disable                 :  3;
     unsigned      reserved3                                 :  5;
     unsigned      swap_en                                   :  1;
     unsigned      reserved2                                 :  7;
     unsigned      disable_rd_interleave                     :  1;
     unsigned      reserved1                                 :  7;
     unsigned      inhibit_dram_cmd                          :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_memory_controller_DENALI_CTL_79_t;

/*! @struct ncp_memory_controller_DENALI_CTL_80_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_80_t\n
 *   </td>
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cs_map </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines which chip selects are active. </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_80_t
 *
 * Implemented by: 
 *      DENALI_CTL_80
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
     unsigned      reserved3                                 :  6;
     unsigned      cs_map                                    :  2;
#else    /* Little Endian */
     unsigned      cs_map                                    :  2;
     unsigned      reserved3                                 :  6;
     unsigned      burst_on_fly_bit                          :  4;
     unsigned      reserved2                                 :  4;
     unsigned      reduc                                     :  1;
     unsigned      reserved1                                 :  7;
     unsigned      memdata_ratio_0                           :  3;
     unsigned      reserved0                                 :  5;
#endif
} ncp_memory_controller_DENALI_CTL_80_t;

/*! @struct ncp_memory_controller_DENALI_CTL_81_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_81_t\n
 *   </td>
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
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param q_fullness </td>
 *     <td width="20%" align="center"> 3 </td>
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_81_t
 *
 * Implemented by: 
 *      DENALI_CTL_81
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      controller_busy                           :  1;
     unsigned      reserved1                                 :  7;
     unsigned      in_order_accept                           :  1;
     unsigned      reserved2                                 :  5;
     unsigned      q_fullness                                :  3;
     unsigned      reserved3                                 :  5;
     unsigned      memdata_ratio_1                           :  3;
#else    /* Little Endian */
     unsigned      memdata_ratio_1                           :  3;
     unsigned      reserved3                                 :  5;
     unsigned      q_fullness                                :  3;
     unsigned      reserved2                                 :  5;
     unsigned      in_order_accept                           :  1;
     unsigned      reserved1                                 :  7;
     unsigned      controller_busy                           :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_memory_controller_DENALI_CTL_81_t;

/*! @struct ncp_memory_controller_DENALI_CTL_82_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_82_t\n
 *   </td>
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
 *   <td width="30%"> Enable read preamble training during gate training.
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_82_t
 *
 * Implemented by: 
 *      DENALI_CTL_82
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
} ncp_memory_controller_DENALI_CTL_82_t;

/*! @struct ncp_memory_controller_DENALI_CTL_83_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_83_t\n
 *   </td>
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
 *     <td width="30%"> @param bg_rotate_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Enable bank group rotation. Set to 1 to enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dfi_error_info </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Holds the encoded DFI error type associated with the
 *        DFI_ERROR parameter assertion. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dfi_error </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Indicates that the DFI error flag has been asserted.
 *        READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_83_t
 *
 * Implemented by: 
 *      DENALI_CTL_83
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      bg_rotate_en                              :  1;
     unsigned      dfi_error_info                            : 16;
     unsigned      reserved1                                 :  4;
     unsigned      dfi_error                                 :  4;
#else    /* Little Endian */
     unsigned      dfi_error                                 :  4;
     unsigned      reserved1                                 :  4;
     unsigned      dfi_error_info                            : 16;
     unsigned      bg_rotate_en                              :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_memory_controller_DENALI_CTL_83_t;

/*! @struct ncp_memory_controller_DENALI_CTL_84_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_84_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_84_t
 *
 * Implemented by: 
 *      DENALI_CTL_84
 */
 
typedef struct
{
     unsigned  int                int_status;
} ncp_memory_controller_DENALI_CTL_84_t;

/*! @struct ncp_memory_controller_DENALI_CTL_85_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_85_t\n
 *   </td>
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
 *     <td width="30%"> @param int_ack </td>
 *     <td width="20%" align="center"> 31 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Clear mask of the INT_STATUS parameter. WRITE-ONLY </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_85_t
 *
 * Implemented by: 
 *      DENALI_CTL_85
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  1;
     unsigned      int_ack                                   : 31;
#else    /* Little Endian */
     unsigned      int_ack                                   : 31;
     unsigned      reserved0                                 :  1;
#endif
} ncp_memory_controller_DENALI_CTL_85_t;

/*! @struct ncp_memory_controller_DENALI_CTL_86_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_86_t\n
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
 *   <td width="30%"> Mask for controller_int signal from the INT_STATUS
 *        parameter.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_86_t
 *
 * Implemented by: 
 *      DENALI_CTL_86
 */
 
typedef struct
{
     unsigned  int                  int_mask;
} ncp_memory_controller_DENALI_CTL_86_t;

/*! @struct ncp_memory_controller_DENALI_CTL_87_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_87_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_87_t
 *
 * Implemented by: 
 *      DENALI_CTL_87
 */
 
typedef struct
{
     unsigned  int         out_of_range_addr;
} ncp_memory_controller_DENALI_CTL_87_t;

/*! @struct ncp_memory_controller_DENALI_CTL_88_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_88_t\n
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
 *     <td width="30%"> @param out_of_range_type </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Type of command that caused an out-of-range interrupt.
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
 *     <td width="30%"> @param out_of_range_length </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Length of command that caused an out-of-range interrupt.
 *        READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param out_of_range_addr </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address of command that caused an out-of-range interrupt.
 *        READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_88_t
 *
 * Implemented by: 
 *      DENALI_CTL_88
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      reserved0                                 :  1;
     unsigned      out_of_range_type                         :  7;
     unsigned      reserved1                                 :  2;
     unsigned      out_of_range_length                       :  6;
     unsigned      reserved2                                 :  6;
     unsigned      out_of_range_addr                         :  2;
#else    /* Little Endian */
     unsigned      out_of_range_addr                         :  2;
     unsigned      reserved2                                 :  6;
     unsigned      out_of_range_length                       :  6;
     unsigned      reserved1                                 :  2;
     unsigned      out_of_range_type                         :  7;
     unsigned      reserved0                                 :  1;
     unsigned      obsolete3                                 :  8;
#endif
} ncp_memory_controller_DENALI_CTL_88_t;

/*! @struct ncp_memory_controller_DENALI_CTL_89_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_89_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_89_t
 *
 * Implemented by: 
 *      DENALI_CTL_89
 */
 
typedef struct
{
     unsigned  int             bist_exp_data;
} ncp_memory_controller_DENALI_CTL_89_t;

/*! @struct ncp_memory_controller_DENALI_CTL_90_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_90_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_90_t
 *
 * Implemented by: 
 *      DENALI_CTL_90
 */
 
typedef struct
{
     unsigned  int             bist_exp_data;
} ncp_memory_controller_DENALI_CTL_90_t;

/*! @struct ncp_memory_controller_DENALI_CTL_91_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_91_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_91_t
 *
 * Implemented by: 
 *      DENALI_CTL_91
 */
 
typedef struct
{
     unsigned  int            bist_fail_data;
} ncp_memory_controller_DENALI_CTL_91_t;

/*! @struct ncp_memory_controller_DENALI_CTL_92_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_92_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_92_t
 *
 * Implemented by: 
 *      DENALI_CTL_92
 */
 
typedef struct
{
     unsigned  int            bist_fail_data;
} ncp_memory_controller_DENALI_CTL_92_t;

/*! @struct ncp_memory_controller_DENALI_CTL_93_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_93_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_93_t
 *
 * Implemented by: 
 *      DENALI_CTL_93
 */
 
typedef struct
{
     unsigned  int            bist_fail_addr;
} ncp_memory_controller_DENALI_CTL_93_t;

/*! @struct ncp_memory_controller_DENALI_CTL_94_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_94_t\n
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
 *     <td width="30%"> @param bist_fail_addr </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address of BIST error. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_94_t
 *
 * Implemented by: 
 *      DENALI_CTL_94
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  6;
     unsigned      bist_fail_addr                            :  2;
#else    /* Little Endian */
     unsigned      bist_fail_addr                            :  2;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_memory_controller_DENALI_CTL_94_t;

/*! @struct ncp_memory_controller_DENALI_CTL_95_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_95_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_95_t
 *
 * Implemented by: 
 *      DENALI_CTL_95
 */
 
typedef struct
{
     unsigned  int       port_cmd_error_addr;
} ncp_memory_controller_DENALI_CTL_95_t;

/*! @struct ncp_memory_controller_DENALI_CTL_96_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_96_t\n
 *   </td>
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
 *     <td width="30%"> @param odt_rd_map_cs0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Determines which chip(s) will have termination when
 *        a read occurs on chip select 0. Set bit X to enable
 *        termination on csX when cs0 is performing a read.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param port_cmd_error_type </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Type of error and access type that caused the PORT
 *        command error. READ-ONLY
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param port_cmd_error_addr </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Address of command that caused the PORT command error.
 *        READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_96_t
 *
 * Implemented by: 
 *      DENALI_CTL_96
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      odt_rd_map_cs0                            :  2;
     unsigned      reserved1                                 :  6;
     unsigned      port_cmd_error_type                       :  2;
     unsigned      obsolete1                                 :  8;
     unsigned      reserved2                                 :  6;
     unsigned      port_cmd_error_addr                       :  2;
#else    /* Little Endian */
     unsigned      port_cmd_error_addr                       :  2;
     unsigned      reserved2                                 :  6;
     unsigned      obsolete1                                 :  8;
     unsigned      port_cmd_error_type                       :  2;
     unsigned      reserved1                                 :  6;
     unsigned      odt_rd_map_cs0                            :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_memory_controller_DENALI_CTL_96_t;

/*! @struct ncp_memory_controller_DENALI_CTL_97_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_97_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param todtl_2cmd </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Defines the DRAM delay from an ODT de-assertion to
 *        the next non-write, non-read command.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odt_wr_map_cs1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Determines which chip(s) will have termination when
 *        a write occurs on chip select 1. Set bit X to enable
 *        termination on csX when cs1 is performing a write.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odt_rd_map_cs1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Determines which chip(s) will have termination when
 *        a read occurs on chip select 1. Set bit X to enable
 *        termination on csX when cs1 is performing a read.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param odt_wr_map_cs0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Determines which chip(s) will have termination when
 *        a write occurs on chip select 0. Set bit X to enable
 *        termination on csX when cs0 is performing a write.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_97_t
 *
 * Implemented by: 
 *      DENALI_CTL_97
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      todtl_2cmd                                :  8;
     unsigned      reserved0                                 :  6;
     unsigned      odt_wr_map_cs1                            :  2;
     unsigned      reserved1                                 :  6;
     unsigned      odt_rd_map_cs1                            :  2;
     unsigned      reserved2                                 :  6;
     unsigned      odt_wr_map_cs0                            :  2;
#else    /* Little Endian */
     unsigned      odt_wr_map_cs0                            :  2;
     unsigned      reserved2                                 :  6;
     unsigned      odt_rd_map_cs1                            :  2;
     unsigned      reserved1                                 :  6;
     unsigned      odt_wr_map_cs1                            :  2;
     unsigned      reserved0                                 :  6;
     unsigned      todtl_2cmd                                :  8;
#endif
} ncp_memory_controller_DENALI_CTL_97_t;

/*! @struct ncp_memory_controller_DENALI_CTL_98_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_98_t\n
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
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 5 </td>
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
 *     <td width="30%"> @param odt_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enable support of DRAM ODT. When enabled, controller
 *        will assert and de-assert ODT output to DRAM as needed.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved6 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param todth_rd </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the DRAM minimum ODT high time after an ODT
 *        assertion for a read command.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved7 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param todth_wr </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the DRAM minimum ODT high time after an ODT
 *        assertion for a write command.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_98_t
 *
 * Implemented by: 
 *      DENALI_CTL_98
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved4                                 :  3;
     unsigned      reserved3                                 :  5;
     unsigned      reserved5                                 :  7;
     unsigned      odt_en                                    :  1;
     unsigned      reserved6                                 :  4;
     unsigned      todth_rd                                  :  4;
     unsigned      reserved7                                 :  4;
     unsigned      todth_wr                                  :  4;
#else    /* Little Endian */
     unsigned      todth_wr                                  :  4;
     unsigned      reserved7                                 :  4;
     unsigned      todth_rd                                  :  4;
     unsigned      reserved6                                 :  4;
     unsigned      odt_en                                    :  1;
     unsigned      reserved5                                 :  7;
     unsigned      reserved3                                 :  5;
     unsigned      reserved4                                 :  3;
#endif
} ncp_memory_controller_DENALI_CTL_98_t;

/*! @struct ncp_memory_controller_DENALI_CTL_99_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_99_t\n
 *   </td>
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
 *     <td width="30%"> @param w2r_diffcs_dly </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Additional delay to insert between writes and reads
 *        to different chip selects. Allowed programming dependent
 *        on memory system.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param r2w_diffcs_dly </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Additional delay to insert between reads and writes
 *        to different chip selects. Program to a non-zero value.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param r2r_diffcs_dly </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Additional delay to insert between reads to different
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
 *     <td width="30%"> @param rd_to_odth </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the delay from a read command to ODT assertion. </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_99_t
 *
 * Implemented by: 
 *      DENALI_CTL_99
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      w2r_diffcs_dly                            :  5;
     unsigned      reserved1                                 :  3;
     unsigned      r2w_diffcs_dly                            :  5;
     unsigned      reserved2                                 :  3;
     unsigned      r2r_diffcs_dly                            :  5;
     unsigned      reserved3                                 :  3;
     unsigned      rd_to_odth                                :  5;
#else    /* Little Endian */
     unsigned      rd_to_odth                                :  5;
     unsigned      reserved3                                 :  3;
     unsigned      r2r_diffcs_dly                            :  5;
     unsigned      reserved2                                 :  3;
     unsigned      r2w_diffcs_dly                            :  5;
     unsigned      reserved1                                 :  3;
     unsigned      w2r_diffcs_dly                            :  5;
     unsigned      reserved0                                 :  3;
#endif
} ncp_memory_controller_DENALI_CTL_99_t;

/*! @struct ncp_memory_controller_DENALI_CTL_100_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_100_t\n
 *   </td>
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
 *     <td width="30%"> @param w2r_samecs_dly </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Additional delay to insert between writes and reads
 *        to the same chip select.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 21 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param r2w_samecs_dly </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Additional delay to insert between reads and writes
 *        to the same chip select. Program to a non-zero value.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param r2r_samecs_dly </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Additional delay to insert between two reads to the
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
 *     <td width="30%"> @param w2w_diffcs_dly </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Additional delay to insert between writes to different
 *        chip selects. Program to a non-zero value.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_100_t
 *
 * Implemented by: 
 *      DENALI_CTL_100
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      w2r_samecs_dly                            :  5;
     unsigned      reserved1                                 :  3;
     unsigned      r2w_samecs_dly                            :  5;
     unsigned      reserved2                                 :  3;
     unsigned      r2r_samecs_dly                            :  5;
     unsigned      reserved3                                 :  3;
     unsigned      w2w_diffcs_dly                            :  5;
#else    /* Little Endian */
     unsigned      w2w_diffcs_dly                            :  5;
     unsigned      reserved3                                 :  3;
     unsigned      r2r_samecs_dly                            :  5;
     unsigned      reserved2                                 :  3;
     unsigned      r2w_samecs_dly                            :  5;
     unsigned      reserved1                                 :  3;
     unsigned      w2r_samecs_dly                            :  5;
     unsigned      reserved0                                 :  3;
#endif
} ncp_memory_controller_DENALI_CTL_100_t;

/*! @struct ncp_memory_controller_DENALI_CTL_101_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_101_t\n
 *   </td>
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
 *     <td width="30%"> @param swlvl_start </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> User request to initiate software leveling of type
 *        in the SW_LEVELING_MODE parameter. Set to 1 to trigger.
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
 *     <td width="30%"> @param swlvl_load </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> User request to load delays and execute software leveling.
 *        Set to 1 to trigger. WRITE-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sw_leveling_mode </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the leveling operation for software leveling.
 *        Clear to 0 for none, program to 1 for write leveling,
 *        program to 2 for data eye training, or program to
 *        3 for gate training.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param w2w_samecs_dly </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Additional delay to insert between two writes to the
 *        same chip select. Any value including 0x0 supported.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_101_t
 *
 * Implemented by: 
 *      DENALI_CTL_101
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      swlvl_start                               :  1;
     unsigned      reserved1                                 :  7;
     unsigned      swlvl_load                                :  1;
     unsigned      reserved2                                 :  5;
     unsigned      sw_leveling_mode                          :  3;
     unsigned      reserved3                                 :  3;
     unsigned      w2w_samecs_dly                            :  5;
#else    /* Little Endian */
     unsigned      w2w_samecs_dly                            :  5;
     unsigned      reserved3                                 :  3;
     unsigned      sw_leveling_mode                          :  3;
     unsigned      reserved2                                 :  5;
     unsigned      swlvl_load                                :  1;
     unsigned      reserved1                                 :  7;
     unsigned      swlvl_start                               :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_memory_controller_DENALI_CTL_101_t;

/*! @struct ncp_memory_controller_DENALI_CTL_102_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_102_t\n
 *   </td>
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
 *     <td width="30%"> @param swlvl_resp_1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Leveling response for data slice 1. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param swlvl_resp_0 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Leveling response for data slice 0. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param swlvl_op_done </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Signals that software leveling is currently in progress.
 *        Value of 1 indicates operation complete. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param swlvl_exit </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> User request to exit software leveling. Set to 1 to
 *        exit. WRITE-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_102_t
 *
 * Implemented by: 
 *      DENALI_CTL_102
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      swlvl_resp_1                              :  1;
     unsigned      reserved1                                 :  7;
     unsigned      swlvl_resp_0                              :  1;
     unsigned      reserved2                                 :  7;
     unsigned      swlvl_op_done                             :  1;
     unsigned      reserved3                                 :  7;
     unsigned      swlvl_exit                                :  1;
#else    /* Little Endian */
     unsigned      swlvl_exit                                :  1;
     unsigned      reserved3                                 :  7;
     unsigned      swlvl_op_done                             :  1;
     unsigned      reserved2                                 :  7;
     unsigned      swlvl_resp_0                              :  1;
     unsigned      reserved1                                 :  7;
     unsigned      swlvl_resp_1                              :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_memory_controller_DENALI_CTL_102_t;

/*! @struct ncp_memory_controller_DENALI_CTL_103_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_103_t\n
 *   </td>
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
 *     <td width="30%"> @param wldqsen </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Delay from issuing MRS to first DQS strobe for write
 *        leveling.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_cs </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Specifies the target chip select for the write leveling
 *        operation initiated through the WRLVL_REQ parameter.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_req </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> User request to initiate write leveling. Set to 1
 *        to trigger. WRITE-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param swlvl_resp_2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Leveling response for data slice 2. READ-ONLY </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_103_t
 *
 * Implemented by: 
 *      DENALI_CTL_103
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  2;
     unsigned      wldqsen                                   :  6;
     unsigned      reserved1                                 :  7;
     unsigned      wrlvl_cs                                  :  1;
     unsigned      reserved2                                 :  7;
     unsigned      wrlvl_req                                 :  1;
     unsigned      reserved3                                 :  7;
     unsigned      swlvl_resp_2                              :  1;
#else    /* Little Endian */
     unsigned      swlvl_resp_2                              :  1;
     unsigned      reserved3                                 :  7;
     unsigned      wrlvl_req                                 :  1;
     unsigned      reserved2                                 :  7;
     unsigned      wrlvl_cs                                  :  1;
     unsigned      reserved1                                 :  7;
     unsigned      wldqsen                                   :  6;
     unsigned      reserved0                                 :  2;
#endif
} ncp_memory_controller_DENALI_CTL_103_t;

/*! @struct ncp_memory_controller_DENALI_CTL_104_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_104_t\n
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
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wlmrd </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Delay from issuing MRS to first write leveling strobe. </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_104_t
 *
 * Implemented by: 
 *      DENALI_CTL_104
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      wrlvl_interval                            : 16;
     unsigned      reserved0                                 :  7;
     unsigned      wrlvl_en                                  :  1;
     unsigned      reserved1                                 :  2;
     unsigned      wlmrd                                     :  6;
#else    /* Little Endian */
     unsigned      wlmrd                                     :  6;
     unsigned      reserved1                                 :  2;
     unsigned      wrlvl_en                                  :  1;
     unsigned      reserved0                                 :  7;
     unsigned      wrlvl_interval                            : 16;
#endif
} ncp_memory_controller_DENALI_CTL_104_t;

/*! @struct ncp_memory_controller_DENALI_CTL_105_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_105_t\n
 *   </td>
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
 *     <td width="30%"> @param wrlvl_resp_mask </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Mask for the dfi_wrlvl_resp signal during write leveling. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_on_sref_exit </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enables automatic write leveling on a self-refresh
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
 *     <td width="30%"> @param wrlvl_periodic </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enables the use of the dfi_lvl_periodic signal during
 *        write leveling. Set to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dfi_phy_wrlvl_mode </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Specifies the PHY support for DFI write leveling.
 *        Set to 1 for supported.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_105_t
 *
 * Implemented by: 
 *      DENALI_CTL_105
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  5;
     unsigned      wrlvl_resp_mask                           :  3;
     unsigned      reserved1                                 :  7;
     unsigned      wrlvl_on_sref_exit                        :  1;
     unsigned      reserved2                                 :  7;
     unsigned      wrlvl_periodic                            :  1;
     unsigned      reserved3                                 :  7;
     unsigned      dfi_phy_wrlvl_mode                        :  1;
#else    /* Little Endian */
     unsigned      dfi_phy_wrlvl_mode                        :  1;
     unsigned      reserved3                                 :  7;
     unsigned      wrlvl_periodic                            :  1;
     unsigned      reserved2                                 :  7;
     unsigned      wrlvl_on_sref_exit                        :  1;
     unsigned      reserved1                                 :  7;
     unsigned      wrlvl_resp_mask                           :  3;
     unsigned      reserved0                                 :  5;
#endif
} ncp_memory_controller_DENALI_CTL_105_t;

/*! @struct ncp_memory_controller_DENALI_CTL_106_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_106_t\n
 *   </td>
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wrlvl_cs_map </td>
 *     <td width="20%" align="center"> 2 </td>
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_106_t
 *
 * Implemented by: 
 *      DENALI_CTL_106
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      wrlvl_error_status                        :  2;
     unsigned      reserved1                                 :  6;
     unsigned      wrlvl_cs_map                              :  2;
     unsigned      reserved2                                 :  7;
     unsigned      wrlvl_rotate                              :  1;
     unsigned      reserved3                                 :  7;
     unsigned      wrlvl_aref_en                             :  1;
#else    /* Little Endian */
     unsigned      wrlvl_aref_en                             :  1;
     unsigned      reserved3                                 :  7;
     unsigned      wrlvl_rotate                              :  1;
     unsigned      reserved2                                 :  7;
     unsigned      wrlvl_cs_map                              :  2;
     unsigned      reserved1                                 :  6;
     unsigned      wrlvl_error_status                        :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_memory_controller_DENALI_CTL_106_t;

/*! @struct ncp_memory_controller_DENALI_CTL_107_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_107_t\n
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
 *     <td width="30%"> @param rdlvl_cs </td>
 *     <td width="20%" align="center"> 1 </td>
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_107_t
 *
 * Implemented by: 
 *      DENALI_CTL_107
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      reserved0                                 :  7;
     unsigned      rdlvl_cs                                  :  1;
     unsigned      reserved1                                 :  7;
     unsigned      rdlvl_gate_req                            :  1;
     unsigned      reserved2                                 :  7;
     unsigned      rdlvl_req                                 :  1;
#else    /* Little Endian */
     unsigned      rdlvl_req                                 :  1;
     unsigned      reserved2                                 :  7;
     unsigned      rdlvl_gate_req                            :  1;
     unsigned      reserved1                                 :  7;
     unsigned      rdlvl_cs                                  :  1;
     unsigned      reserved0                                 :  7;
     unsigned      obsolete3                                 :  8;
#endif
} ncp_memory_controller_DENALI_CTL_107_t;

/*! @struct ncp_memory_controller_DENALI_CTL_108_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_108_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_108_t
 *
 * Implemented by: 
 *      DENALI_CTL_108
 */
 
typedef struct
{
     unsigned  int               rdlvl_pat_0;
} ncp_memory_controller_DENALI_CTL_108_t;

/*! @struct ncp_memory_controller_DENALI_CTL_109_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_109_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_109_t
 *
 * Implemented by: 
 *      DENALI_CTL_109
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
} ncp_memory_controller_DENALI_CTL_109_t;

/*! @struct ncp_memory_controller_DENALI_CTL_110_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_110_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_110_t
 *
 * Implemented by: 
 *      DENALI_CTL_110
 */
 
typedef struct
{
     unsigned  int               rdlvl_pat_1;
} ncp_memory_controller_DENALI_CTL_110_t;

/*! @struct ncp_memory_controller_DENALI_CTL_111_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_111_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_111_t
 *
 * Implemented by: 
 *      DENALI_CTL_111
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
} ncp_memory_controller_DENALI_CTL_111_t;

/*! @struct ncp_memory_controller_DENALI_CTL_112_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_112_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_112_t
 *
 * Implemented by: 
 *      DENALI_CTL_112
 */
 
typedef struct
{
     unsigned  int               rdlvl_pat_2;
} ncp_memory_controller_DENALI_CTL_112_t;

/*! @struct ncp_memory_controller_DENALI_CTL_113_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_113_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_113_t
 *
 * Implemented by: 
 *      DENALI_CTL_113
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
} ncp_memory_controller_DENALI_CTL_113_t;

/*! @struct ncp_memory_controller_DENALI_CTL_114_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_114_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_114_t
 *
 * Implemented by: 
 *      DENALI_CTL_114
 */
 
typedef struct
{
     unsigned  int               rdlvl_pat_3;
} ncp_memory_controller_DENALI_CTL_114_t;

/*! @struct ncp_memory_controller_DENALI_CTL_115_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_115_t\n
 *   </td>
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_115_t
 *
 * Implemented by: 
 *      DENALI_CTL_115
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
} ncp_memory_controller_DENALI_CTL_115_t;

/*! @struct ncp_memory_controller_DENALI_CTL_116_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_116_t\n
 *   </td>
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_116_t
 *
 * Implemented by: 
 *      DENALI_CTL_116
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
} ncp_memory_controller_DENALI_CTL_116_t;

/*! @struct ncp_memory_controller_DENALI_CTL_117_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_117_t\n
 *   </td>
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_117_t
 *
 * Implemented by: 
 *      DENALI_CTL_117
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
} ncp_memory_controller_DENALI_CTL_117_t;

/*! @struct ncp_memory_controller_DENALI_CTL_118_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_118_t\n
 *   </td>
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
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param vref_cs </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Specifies the target chip select for the VREF training
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
 *     <td width="30%"> @param rdlvl_gate_cs_map </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Defines the chip select map for gate training operations.
 *        Bit (0) controls cs0, bit (1) controls cs1, etc. Set
 *        each bit to 1 to enable chip for gate training.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_cs_map </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the chip select map for data eye training
 *        operations. Bit (0) controls cs0, bit (1) controls
 *        cs1, etc. Set each bit to 1 to enable chip for data
 *        eye training.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_118_t
 *
 * Implemented by: 
 *      DENALI_CTL_118
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      vref_en                                   :  1;
     unsigned      reserved1                                 :  7;
     unsigned      vref_cs                                   :  1;
     unsigned      reserved2                                 :  6;
     unsigned      rdlvl_gate_cs_map                         :  2;
     unsigned      reserved3                                 :  6;
     unsigned      rdlvl_cs_map                              :  2;
#else    /* Little Endian */
     unsigned      rdlvl_cs_map                              :  2;
     unsigned      reserved3                                 :  6;
     unsigned      rdlvl_gate_cs_map                         :  2;
     unsigned      reserved2                                 :  6;
     unsigned      vref_cs                                   :  1;
     unsigned      reserved1                                 :  7;
     unsigned      vref_en                                   :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_memory_controller_DENALI_CTL_118_t;

/*! @struct ncp_memory_controller_DENALI_CTL_119_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_119_t\n
 *   </td>
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_119_t
 *
 * Implemented by: 
 *      DENALI_CTL_119
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
} ncp_memory_controller_DENALI_CTL_119_t;

/*! @struct ncp_memory_controller_DENALI_CTL_120_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_120_t\n
 *   </td>
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_120_t
 *
 * Implemented by: 
 *      DENALI_CTL_120
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
} ncp_memory_controller_DENALI_CTL_120_t;

/*! @struct ncp_memory_controller_DENALI_CTL_121_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_121_t\n
 *   </td>
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
 *     <td width="30%"> @param axi0_all_strobes_used_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Enables use of the AWALLSTRB signal for AXI port 0.
 *        Set to 1 to enable.
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
 *     <td width="30%"> @param vref_val_dev3_1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the range and value for VREF training for
 *        DRAM 3 for CS 1. If the VREF_PDA_EN parameter is not
 *        set, the device 0 value is used for all devices.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_121_t
 *
 * Implemented by: 
 *      DENALI_CTL_121
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      axi0_all_strobes_used_enable              :  1;
     unsigned      reserved1                                 :  1;
     unsigned      vref_val_ecc_dev0_1                       :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_ecc_dev0_0                       :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_dev3_1                           :  7;
#else    /* Little Endian */
     unsigned      vref_val_dev3_1                           :  7;
     unsigned      reserved3                                 :  1;
     unsigned      vref_val_ecc_dev0_0                       :  7;
     unsigned      reserved2                                 :  1;
     unsigned      vref_val_ecc_dev0_1                       :  7;
     unsigned      reserved1                                 :  1;
     unsigned      axi0_all_strobes_used_enable              :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_memory_controller_DENALI_CTL_121_t;

/*! @struct ncp_memory_controller_DENALI_CTL_122_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_122_t\n
 *   </td>
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cke_status </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Register access to cke_status signal. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_w_priority </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Priority of write commands from AXI port 0. 0 is the
 *        highest priority.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param axi0_r_priority </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Priority of read commands from AXI port 0. 0 is the
 *        highest priority.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_122_t
 *
 * Implemented by: 
 *      DENALI_CTL_122
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      mem_rst_valid                             :  1;
     unsigned      reserved1                                 :  6;
     unsigned      cke_status                                :  2;
     unsigned      reserved2                                 :  7;
     unsigned      axi0_w_priority                           :  1;
     unsigned      reserved3                                 :  7;
     unsigned      axi0_r_priority                           :  1;
#else    /* Little Endian */
     unsigned      axi0_r_priority                           :  1;
     unsigned      reserved3                                 :  7;
     unsigned      axi0_w_priority                           :  1;
     unsigned      reserved2                                 :  7;
     unsigned      cke_status                                :  2;
     unsigned      reserved1                                 :  6;
     unsigned      mem_rst_valid                             :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_memory_controller_DENALI_CTL_122_t;

/*! @struct ncp_memory_controller_DENALI_CTL_123_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_123_t\n
 *   </td>
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_123_t
 *
 * Implemented by: 
 *      DENALI_CTL_123
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
} ncp_memory_controller_DENALI_CTL_123_t;

/*! @struct ncp_memory_controller_DENALI_CTL_124_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_124_t\n
 *   </td>
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
 *     <td width="30%"> @param dram_clk_disable </td>
 *     <td width="20%" align="center"> 2 </td>
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_124_t
 *
 * Implemented by: 
 *      DENALI_CTL_124
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      dram_clk_disable                          :  2;
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
     unsigned      dram_clk_disable                          :  2;
     unsigned      reserved0                                 :  6;
#endif
} ncp_memory_controller_DENALI_CTL_124_t;

/*! @struct ncp_memory_controller_DENALI_CTL_125_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_125_t\n
 *   </td>
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
 *        must be asserted.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_125_t
 *
 * Implemented by: 
 *      DENALI_CTL_125
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
} ncp_memory_controller_DENALI_CTL_125_t;

/*! @struct ncp_memory_controller_DENALI_CTL_126_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_126_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_126_t
 *
 * Implemented by: 
 *      DENALI_CTL_126
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
} ncp_memory_controller_DENALI_CTL_126_t;

/*! @struct ncp_memory_controller_DENALI_CTL_127_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_127_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_127_t
 *
 * Implemented by: 
 *      DENALI_CTL_127
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
} ncp_memory_controller_DENALI_CTL_127_t;

/*! @struct ncp_memory_controller_DENALI_CTL_128_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_128_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_128_t
 *
 * Implemented by: 
 *      DENALI_CTL_128
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
} ncp_memory_controller_DENALI_CTL_128_t;

/*! @struct ncp_memory_controller_DENALI_CTL_129_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_129_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_129_t
 *
 * Implemented by: 
 *      DENALI_CTL_129
 */
 
typedef struct
{
     unsigned  int      tdfi_ctrlupd_interval;
} ncp_memory_controller_DENALI_CTL_129_t;

/*! @struct ncp_memory_controller_DENALI_CTL_130_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_130_t\n
 *   </td>
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_130_t
 *
 * Implemented by: 
 *      DENALI_CTL_130
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
} ncp_memory_controller_DENALI_CTL_130_t;

/*! @struct ncp_memory_controller_DENALI_CTL_131_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_131_t\n
 *   </td>
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_131_t
 *
 * Implemented by: 
 *      DENALI_CTL_131
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
} ncp_memory_controller_DENALI_CTL_131_t;

/*! @struct ncp_memory_controller_DENALI_CTL_132_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_132_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_132_t
 *
 * Implemented by: 
 *      DENALI_CTL_132
 */
 
typedef struct
{
     unsigned  int           tdfi_wrlvl_resp;
} ncp_memory_controller_DENALI_CTL_132_t;

/*! @struct ncp_memory_controller_DENALI_CTL_133_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_133_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_133_t
 *
 * Implemented by: 
 *      DENALI_CTL_133
 */
 
typedef struct
{
     unsigned  int            tdfi_wrlvl_max;
} ncp_memory_controller_DENALI_CTL_133_t;

/*! @struct ncp_memory_controller_DENALI_CTL_134_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_134_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_134_t
 *
 * Implemented by: 
 *      DENALI_CTL_134
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
} ncp_memory_controller_DENALI_CTL_134_t;

/*! @struct ncp_memory_controller_DENALI_CTL_135_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_135_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_135_t
 *
 * Implemented by: 
 *      DENALI_CTL_135
 */
 
typedef struct
{
     unsigned  int           tdfi_rdlvl_resp;
} ncp_memory_controller_DENALI_CTL_135_t;

/*! @struct ncp_memory_controller_DENALI_CTL_136_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_136_t\n
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
 *     <td width="30%"> @param rdlvl_gate_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Enable the MC gate training module. Set to 1 to enable. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_en </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Enable the MC data eye training module. Set to 1 to
 *        enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rdlvl_resp_mask </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Mask for the dfi_rdlvl_resp signal during data eye
 *        training.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_136_t
 *
 * Implemented by: 
 *      DENALI_CTL_136
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete3                                 :  8;
     unsigned      reserved0                                 :  7;
     unsigned      rdlvl_gate_en                             :  1;
     unsigned      reserved1                                 :  7;
     unsigned      rdlvl_en                                  :  1;
     unsigned      reserved2                                 :  5;
     unsigned      rdlvl_resp_mask                           :  3;
#else    /* Little Endian */
     unsigned      rdlvl_resp_mask                           :  3;
     unsigned      reserved2                                 :  5;
     unsigned      rdlvl_en                                  :  1;
     unsigned      reserved1                                 :  7;
     unsigned      rdlvl_gate_en                             :  1;
     unsigned      reserved0                                 :  7;
     unsigned      obsolete3                                 :  8;
#endif
} ncp_memory_controller_DENALI_CTL_136_t;

/*! @struct ncp_memory_controller_DENALI_CTL_137_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_137_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_137_t
 *
 * Implemented by: 
 *      DENALI_CTL_137
 */
 
typedef struct
{
     unsigned  int            tdfi_rdlvl_max;
} ncp_memory_controller_DENALI_CTL_137_t;

/*! @struct ncp_memory_controller_DENALI_CTL_138_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_138_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_138_t
 *
 * Implemented by: 
 *      DENALI_CTL_138
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
} ncp_memory_controller_DENALI_CTL_138_t;

/*! @struct ncp_memory_controller_DENALI_CTL_139_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_139_t\n
 *   </td>
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_139_t
 *
 * Implemented by: 
 *      DENALI_CTL_139
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
} ncp_memory_controller_DENALI_CTL_139_t;

/*! @struct ncp_memory_controller_DENALI_CTL_140_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_140_t\n
 *   </td>
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
 *     <td width="30%"> @param ca_parity_cmd_abort_status </td>
 *     <td width="20%" align="center"> 11 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Indicates the command sequences that were in progress
 *        when a CA parity error was detected. If CA parity
 *        error recovery is not enabled in CA_PARITY_ERROR_CTL
 *        bit (0), no bits will be set in this parameter. Each
 *        bit corresponds to a different command sequence: Bit
 *        (0) - Initialization, Bit (1) - MRW sequence, Bit
 *        (2) - Refresh, Bit (3) - ZQ, Bit (4) - Write leveling,
 *        Bit (5) - Gate training, Bit (6) - Read leveling,
 *        Bit (7) - VREF training, Bit (8) - Reserved, Bit (9)
 *        - Low power software lock broken, Bit (10) - MPR read
 *        sequence. Each bit set to 1 indicates that the associated
 *        command was in progress. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
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
 *     <td width="30%"> @param reserved2 </td>
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_140_t
 *
 * Implemented by: 
 *      DENALI_CTL_140
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  5;
     unsigned      ca_parity_cmd_abort_status                : 11;
     unsigned      reserved1                                 :  5;
     unsigned      tdfi_parin_lat                            :  3;
     unsigned      reserved2                                 :  1;
     unsigned      tdfi_wrcslat                              :  7;
#else    /* Little Endian */
     unsigned      tdfi_wrcslat                              :  7;
     unsigned      reserved2                                 :  1;
     unsigned      tdfi_parin_lat                            :  3;
     unsigned      reserved1                                 :  5;
     unsigned      ca_parity_cmd_abort_status                : 11;
     unsigned      reserved0                                 :  5;
#endif
} ncp_memory_controller_DENALI_CTL_140_t;

/*! @struct ncp_memory_controller_DENALI_CTL_141_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_141_t\n
 *   </td>
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
 *     <td width="30%"> @param ecc_c_id </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Source ID associated with correctable ECC event. READ-ONLY </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param ecc_u_id </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Source ID associated with the uncorrectable ECC event.
 *        READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_141_t
 *
 * Implemented by: 
 *      DENALI_CTL_141
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      ecc_c_id                                  : 10;
     unsigned      reserved1                                 :  6;
     unsigned      ecc_u_id                                  : 10;
#else    /* Little Endian */
     unsigned      ecc_u_id                                  : 10;
     unsigned      reserved1                                 :  6;
     unsigned      ecc_c_id                                  : 10;
     unsigned      reserved0                                 :  6;
#endif
} ncp_memory_controller_DENALI_CTL_141_t;

/*! @struct ncp_memory_controller_DENALI_CTL_142_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_142_t\n
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
 *     <td width="30%"> @param crc_mode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines CRC checking/verification support. Bit (0)
 *        controls write CRC; set to 1 to enable CRC generation/checking.
 *        Bit (1) defines where CRC is performed; set to 1 for
 *        MC responsibility or clear to 0 for PHY responsibility.
 *        Bit (1) has no meaning if bit (0) is cleared.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_142_t
 *
 * Implemented by: 
 *      DENALI_CTL_142
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      obsolete1                                 : 24;
     unsigned      reserved0                                 :  6;
     unsigned      crc_mode                                  :  2;
#else    /* Little Endian */
     unsigned      crc_mode                                  :  2;
     unsigned      reserved0                                 :  6;
     unsigned      obsolete1                                 : 24;
#endif
} ncp_memory_controller_DENALI_CTL_142_t;

/*! @struct ncp_memory_controller_DENALI_CTL_143_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_143_t\n
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
 *        the MC/PHY. Bits (7:0) correspond to the DQ mapping
 *        index for nibble DQ (3:0) of the MC/PHY output, bits
 *        (15:8) correspond to the DQ mapping index for nibble
 *        DQ (7:4), etc.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_143_t
 *
 * Implemented by: 
 *      DENALI_CTL_143
 */
 
typedef struct
{
     unsigned  int                  dq_map_0;
} ncp_memory_controller_DENALI_CTL_143_t;

/*! @struct ncp_memory_controller_DENALI_CTL_144_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_144_t\n
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
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq_map_odd_rank_swap_0 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Indicates that the DQ bits of odd ranks are swapped
 *        with respect to the DQ bits of even ranks. DQ0 is
 *        swapped with DQ1, DQ2 with DQ3, DQ4 with DQ5 and DQ6
 *        with DQ7. Bit (0) controls cs0, bit (1) controls cs1,
 *        etc. Set each bit to 1 to enable.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param dq_map_0 </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Defines the DQ mapping of the output DQ pins from
 *        the MC/PHY. Bits (7:0) correspond to the DQ mapping
 *        index for nibble DQ (3:0) of the MC/PHY output, bits
 *        (15:8) correspond to the DQ mapping index for nibble
 *        DQ (7:4), etc.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_144_t
 *
 * Implemented by: 
 *      DENALI_CTL_144
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved3                                 :  7;
     unsigned      reserved2                                 :  1;
     unsigned      reserved4                                 :  6;
     unsigned      dq_map_odd_rank_swap_0                    :  2;
     unsigned      dq_map_0                                  : 16;
#else    /* Little Endian */
     unsigned      dq_map_0                                  : 16;
     unsigned      dq_map_odd_rank_swap_0                    :  2;
     unsigned      reserved4                                 :  6;
     unsigned      reserved2                                 :  1;
     unsigned      reserved3                                 :  7;
#endif
} ncp_memory_controller_DENALI_CTL_144_t;

/*! @struct ncp_memory_controller_DENALI_CTL_145_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_145_t\n
 *   </td>
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
 *     <td width="30%"> @param port_cmd_error_id </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Source ID of command that caused the PORT command
 *        error. READ-ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param out_of_range_source_id </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Source ID of command that caused an out-of-range interrupt.
 *        READ-ONLY
 *   </td>
 * </tr>
 * </table>
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_145_t
 *
 * Implemented by: 
 *      DENALI_CTL_145
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  6;
     unsigned      port_cmd_error_id                         : 10;
     unsigned      reserved1                                 :  6;
     unsigned      out_of_range_source_id                    : 10;
#else    /* Little Endian */
     unsigned      out_of_range_source_id                    : 10;
     unsigned      reserved1                                 :  6;
     unsigned      port_cmd_error_id                         : 10;
     unsigned      reserved0                                 :  6;
#endif
} ncp_memory_controller_DENALI_CTL_145_t;

/*! @struct ncp_memory_controller_DENALI_CTL_146_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_146_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_146_t
 *
 * Implemented by: 
 *      DENALI_CTL_146
 */
 
typedef struct
{
     unsigned  int            user_def_reg_0;
} ncp_memory_controller_DENALI_CTL_146_t;

/*! @struct ncp_memory_controller_DENALI_CTL_147_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_147_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_147_t
 *
 * Implemented by: 
 *      DENALI_CTL_147
 */
 
typedef struct
{
     unsigned  int            user_def_reg_1;
} ncp_memory_controller_DENALI_CTL_147_t;

/*! @struct ncp_memory_controller_DENALI_CTL_148_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_148_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_148_t
 *
 * Implemented by: 
 *      DENALI_CTL_148
 */
 
typedef struct
{
     unsigned  int         user_def_reg_ro_0;
} ncp_memory_controller_DENALI_CTL_148_t;

/*! @struct ncp_memory_controller_DENALI_CTL_149_t
 *  @brief null
 *  @details null
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_memory_controller_DENALI_CTL_149_t\n
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
 * Applies to: 56xx xlf --> ncp_memory_controller_DENALI_CTL_149_t
 *
 * Implemented by: 
 *      DENALI_CTL_149
 */
 
typedef struct
{
     unsigned  int         user_def_reg_ro_1;
} ncp_memory_controller_DENALI_CTL_149_t;

#ifdef __cplusplus
}
#endif

#endif /* _NCP_MEMORY_CONTROLLER_REGS_H_ */
