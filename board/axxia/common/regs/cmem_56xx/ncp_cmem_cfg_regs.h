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

#ifndef _NCP_CMEM_CFG_REGS_H_
#define _NCP_CMEM_CFG_REGS_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __UBOOT__
#include "ncp_sal_types.h"
#endif

/*! @struct ncp_cmem_cfg_ddr_cfg_r_t
 *  @brief DDR Configuration
 *  @details Configure the size and type of DDR used for CMEM interface. Program the same as Memory Controller
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_cmem_cfg_ddr_cfg_r_t\n
 *   </td>
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
 *     <td width="30%"> @param num_rank </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 24 </td>
 *   <td width="30%"> Number of Ranks/CS 0 = Single Rank DDR 1 = Dual
 *        Rank DDR
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param bnk_diff </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Bank Difference - The difference in the number of
 *        bank bits between MAX_BANK and actual DDR 0 = DDR
 *        part has 4 bank bits - DDR4 1 = DDR part has 3
 *        bank bits - DDR3
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
 *   <td width="30%"> Row Difference - The difference in the number of row
 *        bits between MAX_ROW and actual DDR 0 = DDR part
 *        has 17 row bits 7 = DDR part has 10 row bits
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved3 </td>
 *     <td width="20%" align="center"> 7 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param col_diff </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Column Differece - The difference in the number of
 *        column bits between MAX_COL and actual DDR 0 =
 *        DDR part has 11 column bits - True only for 8Gb DDR3.
 *        1 = DDR part has 10 column bits - True for all
 *        DDR4 and most DDR3.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_cmem_cfg_ddr_cfg_r_t
 *
 * Implemented by: 
 *      ddr_cfg
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  7;
     unsigned      num_rank                                  :  1;
     unsigned      reserved1                                 :  7;
     unsigned      bnk_diff                                  :  1;
     unsigned      reserved2                                 :  5;
     unsigned      row_diff                                  :  3;
     unsigned      reserved3                                 :  7;
     unsigned      col_diff                                  :  1;
#else    /* Little Endian */
     unsigned      col_diff                                  :  1;
     unsigned      reserved3                                 :  7;
     unsigned      row_diff                                  :  3;
     unsigned      reserved2                                 :  5;
     unsigned      bnk_diff                                  :  1;
     unsigned      reserved1                                 :  7;
     unsigned      num_rank                                  :  1;
     unsigned      reserved0                                 :  7;
#endif
} ncp_cmem_cfg_ddr_cfg_r_t;

/*! @struct ncp_cmem_cfg_duplication_cfg_r_t
 *  @brief CMEM Duplication Configuration
 *  @details Configure the duplication factors for MPP instructions
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_cmem_cfg_duplication_cfg_r_t\n
 *   </td>
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
 *     <td width="30%"> @param dbc </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Duplication Factor (DBC) 0 = No duplication of
 *        instructions 1 = Instructions are duplicated 2
 *        times 2 = Instructions are duplicated 4 times 3
 *        = Instructions are duplicated 8 times 4 = Instructions
 *        are duplicated 16 times
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_cmem_cfg_duplication_cfg_r_t
 *
 * Implemented by: 
 *      duplication_cfg
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 29;
     unsigned      dbc                                       :  3;
#else    /* Little Endian */
     unsigned      dbc                                       :  3;
     unsigned      reserved0                                 : 29;
#endif
} ncp_cmem_cfg_duplication_cfg_r_t;

/*! @struct ncp_cmem_cfg_ddr_ctl_r_t
 *  @brief DDR Control
 *  @details MISC Controls for DDR or PHY
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_cmem_cfg_ddr_ctl_r_t\n
 *   </td>
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
 *     <td width="30%"> @param erase_mem_mini </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> When set to 1, only the first 1 MB of memory is erased.
 *        Used for testing purposes ONLY
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param erase_mem_go </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Controls writing to memory with an initial data pattern
 *        of all 0s. Writing to 1 will start the process
 *        of wiping/erasing DDR contents. This should only be
 *        performed after the memory controller and ddr configuration
 *        registers have been written, and DDR has been initialized.
 *        Once ddr_erase_done has been received in the interrupt
 *        register, this bit can be cleared to 0
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param init_start </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Controls DFI INIT START bit to DDR PHY </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_cmem_cfg_ddr_ctl_r_t
 *
 * Implemented by: 
 *      ddr_ctl
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 14;
     unsigned      erase_mem_mini                            :  1;
     unsigned      erase_mem_go                              :  1;
     unsigned      reserved1                                 : 15;
     unsigned      init_start                                :  1;
#else    /* Little Endian */
     unsigned      init_start                                :  1;
     unsigned      reserved1                                 : 15;
     unsigned      erase_mem_go                              :  1;
     unsigned      erase_mem_mini                            :  1;
     unsigned      reserved0                                 : 14;
#endif
} ncp_cmem_cfg_ddr_ctl_r_t;

/*! @struct ncp_cmem_cfg_axi_ctl_r_t
 *  @brief AXI Control
 *  @details Various methods of controlling AXI bus
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_cmem_cfg_axi_ctl_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 20 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mpp_arqos </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> QOS Value for Read transactions from MPP block </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_arqos </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> QOS Value for Read transactions from CMEM config block </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cfg_awqos </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> QOS Value for Write transactions from CMEM config
 *        block
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_cmem_cfg_axi_ctl_r_t
 *
 * Implemented by: 
 *      axi_ctl
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 12;
     unsigned      mpp_arqos                                 :  4;
     unsigned      reserved1                                 :  4;
     unsigned      cfg_arqos                                 :  4;
     unsigned      reserved2                                 :  4;
     unsigned      cfg_awqos                                 :  4;
#else    /* Little Endian */
     unsigned      cfg_awqos                                 :  4;
     unsigned      reserved2                                 :  4;
     unsigned      cfg_arqos                                 :  4;
     unsigned      reserved1                                 :  4;
     unsigned      mpp_arqos                                 :  4;
     unsigned      reserved0                                 : 12;
#endif
} ncp_cmem_cfg_axi_ctl_r_t;

/*! @struct ncp_cmem_cfg_user_scrub_addr_r_t
 *  @brief Scrub Address
 *  @details Scrubbing
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_cmem_cfg_user_scrub_addr_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param scrub_addr </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Specific DDR address to perform a write scrubbing
 *        operation to. A scrub operation performs a read
 *        then write of the same data, potentially clearing
 *        any single bit ECC issues
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_cmem_cfg_user_scrub_addr_r_t
 *
 * Implemented by: 
 *      user_scrub_addr
 */
 
typedef struct
{
     unsigned  int                scrub_addr;
} ncp_cmem_cfg_user_scrub_addr_r_t;

/*! @struct ncp_cmem_cfg_max_scrub_addr_r_t
 *  @brief Max Scrub Address
 *  @details Scrubbing
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_cmem_cfg_max_scrub_addr_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param max_scrub_addr </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Specifies the maximum address to increment the Auto
 *        scrubber before returning to 0. This is dependent
 *        on the size of the DDR configured in the system.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_cmem_cfg_max_scrub_addr_r_t
 *
 * Implemented by: 
 *      max_scrub_addr
 */
 
typedef struct
{
     unsigned  int            max_scrub_addr;
} ncp_cmem_cfg_max_scrub_addr_r_t;

/*! @struct ncp_cmem_cfg_scrub_cfg_r_t
 *  @brief Scrub config
 *  @details Scrubbing Configuration
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_cmem_cfg_scrub_cfg_r_t\n
 *   </td>
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
 *     <td width="30%"> @param scrub_interval </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Specifies the interval at which scrubbing will occur.
 *        The value configured into this field is << 13 or
 *        multiplied by 8k and is used as the interval counter.
 *        So every scrub_interval * 8k DDR clocks, a scrub
 *        operation will occur. Each scrub interval approximately
 *        corresponds to a refresh occurring.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_cmem_cfg_scrub_cfg_r_t
 *
 * Implemented by: 
 *      scrub_cfg
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 22;
     unsigned      scrub_interval                            : 10;
#else    /* Little Endian */
     unsigned      scrub_interval                            : 10;
     unsigned      reserved0                                 : 22;
#endif
} ncp_cmem_cfg_scrub_cfg_r_t;

/*! @struct ncp_cmem_cfg_fifo_status_r_t
 *  @brief FIFO Status
 *  @details Contains various status information for a FIFO
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_cmem_cfg_fifo_status_r_t\n
 *   </td>
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
 *     <td width="30%"> @param lvl </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Current FIFO Fill level. 0 = FIFO is empty </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param full </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Indicates FIFO is full </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param almstfull </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> Indicates FIFO is almost full </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param almstempty </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Indicates FIFO is almost empty </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param empty </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> Indicates FIFO is empty </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param overflow </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Indicates FIFO overflow </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param undrflow </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Indicates FIFO underflow </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_cmem_cfg_fifo_status_r_t
 *
 * Implemented by: 
 *      cmd_fifo_status
 *      data_fifo_status
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      lvl                                       :  8;
     unsigned      reserved1                                 :  2;
     unsigned      full                                      :  1;
     unsigned      almstfull                                 :  1;
     unsigned      almstempty                                :  1;
     unsigned      empty                                     :  1;
     unsigned      overflow                                  :  1;
     unsigned      undrflow                                  :  1;
#else    /* Little Endian */
     unsigned      undrflow                                  :  1;
     unsigned      overflow                                  :  1;
     unsigned      empty                                     :  1;
     unsigned      almstempty                                :  1;
     unsigned      almstfull                                 :  1;
     unsigned      full                                      :  1;
     unsigned      reserved1                                 :  2;
     unsigned      lvl                                       :  8;
     unsigned      reserved0                                 : 16;
#endif
} ncp_cmem_cfg_fifo_status_r_t;

/*! @struct ncp_cmem_cfg_wr_status_r_t
 *  @brief Write Status
 *  @details Contains various status information about ongoing writes
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_cmem_cfg_wr_status_r_t\n
 *   </td>
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
 *     <td width="30%"> @param outstnd_writes </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Number of Outstanding writes to DDR controller </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_cmem_cfg_wr_status_r_t
 *
 * Implemented by: 
 *      wr_status
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 26;
     unsigned      outstnd_writes                            :  6;
#else    /* Little Endian */
     unsigned      outstnd_writes                            :  6;
     unsigned      reserved0                                 : 26;
#endif
} ncp_cmem_cfg_wr_status_r_t;

/*! @struct ncp_cmem_cfg_ddrmc_info_r_t
 *  @brief DDR Config info
 *  @details Contains information about capabilities of DDR controller
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_cmem_cfg_ddrmc_info_r_t\n
 *   </td>
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
 *     <td width="30%"> @param max_bank </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> Maximum Bank Bits possible in DDR Memory Controller </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param max_row </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Maximum Row Bits possible in DDR Memory Controller </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param max_col </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Maximum Column Bits possible in DDR Memory Controller </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_cmem_cfg_ddrmc_info_r_t
 *
 * Implemented by: 
 *      ddrmc_info
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  8;
     unsigned      max_bank                                  :  8;
     unsigned      max_row                                   :  8;
     unsigned      max_col                                   :  8;
#else    /* Little Endian */
     unsigned      max_col                                   :  8;
     unsigned      max_row                                   :  8;
     unsigned      max_bank                                  :  8;
     unsigned      reserved0                                 :  8;
#endif
} ncp_cmem_cfg_ddrmc_info_r_t;

/*! @struct ncp_cmem_cfg_lvl_irq_stat_r_t
 *  @brief LVL_IRQ_STAT
 *  @details Indicates the current Masked + Inverted status of the level sensitive interrupts
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_cmem_cfg_lvl_irq_stat_r_t\n
 *   </td>
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
 *     <td width="30%"> @param unused </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> UNUSED </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_cmem_cfg_lvl_irq_stat_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 31;
     unsigned      unused                                    :  1;
#else    /* Little Endian */
     unsigned      unused                                    :  1;
     unsigned      reserved0                                 : 31;
#endif
} ncp_cmem_cfg_lvl_irq_stat_r_t;

/*! @struct ncp_cmem_cfg_lvl_irq_mask_r_t
 *  @brief LVL_IRQ_MASK
 *  @details Programmable mask for level sensitive interrupts.
		1 = Enable Interrupt
		0 = Mask Interrupt
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_cmem_cfg_lvl_irq_mask_r_t\n
 *   </td>
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
 *     <td width="30%"> @param unused </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> UNUSED </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_cmem_cfg_lvl_irq_mask_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 31;
     unsigned      unused                                    :  1;
#else    /* Little Endian */
     unsigned      unused                                    :  1;
     unsigned      reserved0                                 : 31;
#endif
} ncp_cmem_cfg_lvl_irq_mask_r_t;

/*! @struct ncp_cmem_cfg_lvl_irq_inv_r_t
 *  @brief LVL_IRQ_INV
 *  @details Programmable inversion of the level sensitive interrupt
		1 = Cause interrupt when signal is LOW
		0 = Cause interrupt when signal is HIGH
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_cmem_cfg_lvl_irq_inv_r_t\n
 *   </td>
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
 *     <td width="30%"> @param unused </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> UNUSED </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_cmem_cfg_lvl_irq_inv_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 31;
     unsigned      unused                                    :  1;
#else    /* Little Endian */
     unsigned      unused                                    :  1;
     unsigned      reserved0                                 : 31;
#endif
} ncp_cmem_cfg_lvl_irq_inv_r_t;

/*! @struct ncp_cmem_cfg_lvl_irq_nomask_r_t
 *  @brief LVL_IRQ_NOMASK
 *  @details Raw value of the level sensitive interrupt signals, without masking or inverting
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_cmem_cfg_lvl_irq_nomask_r_t\n
 *   </td>
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
 *     <td width="30%"> @param unused </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> UNUSED </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_cmem_cfg_lvl_irq_nomask_r_t
 *
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 31;
     unsigned      unused                                    :  1;
#else    /* Little Endian */
     unsigned      unused                                    :  1;
     unsigned      reserved0                                 : 31;
#endif
} ncp_cmem_cfg_lvl_irq_nomask_r_t;

/*! @struct ncp_cmem_cfg_edg_irq_stat_r_t
 *  @brief EDG_IRQ_STAT
 *  @details Indicates the current Masked and Inverted status of the Edge sensitive interrupts
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_cmem_cfg_edg_irq_stat_r_t\n
 *   </td>
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
 *     <td width="30%"> @param ddr_erase_done </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> DDR_ERASE_DONE </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param smon_irq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> SMON Interrupt </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mem_rst_vld </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DDR MC Memory Reset Valid </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mc_q_almst_full </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> DDR MC Queue Almost Full </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mc_ctlr_busy </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> DDR MC Controller Busy </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mc_port_busy </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> DDR MC Port Busy </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mc_dfi_init_comp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> DDR MC DFI INIT Complete </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmd_fifo_ovflw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CMD FIFO Overflow </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmd_fifo_undflw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CMD FIFO Underflow </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param data_fifo_ovflw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> DATA FIFO Overflow </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param data_fifo_undflw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DATA FIFO Underflow </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_cmem_cfg_edg_irq_stat_r_t
 *
 * Implemented by: 
 *      edg_irq_stat
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 21;
     unsigned      ddr_erase_done                            :  1;
     unsigned      smon_irq                                  :  1;
     unsigned      mem_rst_vld                               :  1;
     unsigned      mc_q_almst_full                           :  1;
     unsigned      mc_ctlr_busy                              :  1;
     unsigned      mc_port_busy                              :  1;
     unsigned      mc_dfi_init_comp                          :  1;
     unsigned      cmd_fifo_ovflw                            :  1;
     unsigned      cmd_fifo_undflw                           :  1;
     unsigned      data_fifo_ovflw                           :  1;
     unsigned      data_fifo_undflw                          :  1;
#else    /* Little Endian */
     unsigned      data_fifo_undflw                          :  1;
     unsigned      data_fifo_ovflw                           :  1;
     unsigned      cmd_fifo_undflw                           :  1;
     unsigned      cmd_fifo_ovflw                            :  1;
     unsigned      mc_dfi_init_comp                          :  1;
     unsigned      mc_port_busy                              :  1;
     unsigned      mc_ctlr_busy                              :  1;
     unsigned      mc_q_almst_full                           :  1;
     unsigned      mem_rst_vld                               :  1;
     unsigned      smon_irq                                  :  1;
     unsigned      ddr_erase_done                            :  1;
     unsigned      reserved0                                 : 21;
#endif
} ncp_cmem_cfg_edg_irq_stat_r_t;

/*! @struct ncp_cmem_cfg_edg_irq_mask_r_t
 *  @brief EDG_IRQ_MASK
 *  @details Programmable mask for level sensitive interrupts
		1 = Enable Interrupt
		0 = Mask Interrupt
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_cmem_cfg_edg_irq_mask_r_t\n
 *   </td>
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
 *     <td width="30%"> @param ddr_erase_done </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> DDR_ERASE_DONE </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param smon_irq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> SMON Interrupt </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mem_rst_vld </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DDR MC Memory Reset Valid </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mc_q_almst_full </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> DDR MC Queue Almost Full </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mc_ctlr_busy </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> DDR MC Controller Busy </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mc_port_busy </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> DDR MC Port Busy </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mc_dfi_init_comp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> DDR MC DFI INIT Complete </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmd_fifo_ovflw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CMD FIFO Overflow </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmd_fifo_undflw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CMD FIFO Underflow </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param data_fifo_ovflw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> DATA FIFO Overflow </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param data_fifo_undflw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DATA FIFO Underflow </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_cmem_cfg_edg_irq_mask_r_t
 *
 * Implemented by: 
 *      edg_irq_mask
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 21;
     unsigned      ddr_erase_done                            :  1;
     unsigned      smon_irq                                  :  1;
     unsigned      mem_rst_vld                               :  1;
     unsigned      mc_q_almst_full                           :  1;
     unsigned      mc_ctlr_busy                              :  1;
     unsigned      mc_port_busy                              :  1;
     unsigned      mc_dfi_init_comp                          :  1;
     unsigned      cmd_fifo_ovflw                            :  1;
     unsigned      cmd_fifo_undflw                           :  1;
     unsigned      data_fifo_ovflw                           :  1;
     unsigned      data_fifo_undflw                          :  1;
#else    /* Little Endian */
     unsigned      data_fifo_undflw                          :  1;
     unsigned      data_fifo_ovflw                           :  1;
     unsigned      cmd_fifo_undflw                           :  1;
     unsigned      cmd_fifo_ovflw                            :  1;
     unsigned      mc_dfi_init_comp                          :  1;
     unsigned      mc_port_busy                              :  1;
     unsigned      mc_ctlr_busy                              :  1;
     unsigned      mc_q_almst_full                           :  1;
     unsigned      mem_rst_vld                               :  1;
     unsigned      smon_irq                                  :  1;
     unsigned      ddr_erase_done                            :  1;
     unsigned      reserved0                                 : 21;
#endif
} ncp_cmem_cfg_edg_irq_mask_r_t;

/*! @struct ncp_cmem_cfg_edg_irq_inv_r_t
 *  @brief EDG_IRQ_INV
 *  @details Programmable inversion of the edge sensitive interrupt
		1 = Cause interrupt on falling edge of signal
		0 = Cause interrupt on rising edge of signal
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_cmem_cfg_edg_irq_inv_r_t\n
 *   </td>
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
 *     <td width="30%"> @param ddr_erase_done </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> DDR_ERASE_DONE </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param smon_irq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> SMON Interrupt </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mem_rst_vld </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DDR MC Memory Reset Valid </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mc_q_almst_full </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> DDR MC Queue Almost Full </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mc_ctlr_busy </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> DDR MC Controller Busy </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mc_port_busy </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> DDR MC Port Busy </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mc_dfi_init_comp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> DDR MC DFI INIT Complete </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmd_fifo_ovflw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CMD FIFO Overflow </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmd_fifo_undflw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CMD FIFO Underflow </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param data_fifo_ovflw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> DATA FIFO Overflow </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param data_fifo_undflw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DATA FIFO Underflow </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_cmem_cfg_edg_irq_inv_r_t
 *
 * Implemented by: 
 *      edg_irq_inv
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 21;
     unsigned      ddr_erase_done                            :  1;
     unsigned      smon_irq                                  :  1;
     unsigned      mem_rst_vld                               :  1;
     unsigned      mc_q_almst_full                           :  1;
     unsigned      mc_ctlr_busy                              :  1;
     unsigned      mc_port_busy                              :  1;
     unsigned      mc_dfi_init_comp                          :  1;
     unsigned      cmd_fifo_ovflw                            :  1;
     unsigned      cmd_fifo_undflw                           :  1;
     unsigned      data_fifo_ovflw                           :  1;
     unsigned      data_fifo_undflw                          :  1;
#else    /* Little Endian */
     unsigned      data_fifo_undflw                          :  1;
     unsigned      data_fifo_ovflw                           :  1;
     unsigned      cmd_fifo_undflw                           :  1;
     unsigned      cmd_fifo_ovflw                            :  1;
     unsigned      mc_dfi_init_comp                          :  1;
     unsigned      mc_port_busy                              :  1;
     unsigned      mc_ctlr_busy                              :  1;
     unsigned      mc_q_almst_full                           :  1;
     unsigned      mem_rst_vld                               :  1;
     unsigned      smon_irq                                  :  1;
     unsigned      ddr_erase_done                            :  1;
     unsigned      reserved0                                 : 21;
#endif
} ncp_cmem_cfg_edg_irq_inv_r_t;

/*! @struct ncp_cmem_cfg_edg_irq_nomask_r_t
 *  @brief EDG_IRQ_NOMASK
 *  @details Current state of the edge sensitive interrupts without masks
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_cmem_cfg_edg_irq_nomask_r_t\n
 *   </td>
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
 *     <td width="30%"> @param ddr_erase_done </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> DDR_ERASE_DONE </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param smon_irq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> SMON Interrupt </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mem_rst_vld </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DDR MC Memory Reset Valid </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mc_q_almst_full </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> DDR MC Queue Almost Full </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mc_ctlr_busy </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> DDR MC Controller Busy </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mc_port_busy </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> DDR MC Port Busy </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mc_dfi_init_comp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> DDR MC DFI INIT Complete </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmd_fifo_ovflw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CMD FIFO Overflow </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmd_fifo_undflw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CMD FIFO Underflow </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param data_fifo_ovflw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> DATA FIFO Overflow </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param data_fifo_undflw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DATA FIFO Underflow </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_cmem_cfg_edg_irq_nomask_r_t
 *
 * Implemented by: 
 *      edg_irq_nomask
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 21;
     unsigned      ddr_erase_done                            :  1;
     unsigned      smon_irq                                  :  1;
     unsigned      mem_rst_vld                               :  1;
     unsigned      mc_q_almst_full                           :  1;
     unsigned      mc_ctlr_busy                              :  1;
     unsigned      mc_port_busy                              :  1;
     unsigned      mc_dfi_init_comp                          :  1;
     unsigned      cmd_fifo_ovflw                            :  1;
     unsigned      cmd_fifo_undflw                           :  1;
     unsigned      data_fifo_ovflw                           :  1;
     unsigned      data_fifo_undflw                          :  1;
#else    /* Little Endian */
     unsigned      data_fifo_undflw                          :  1;
     unsigned      data_fifo_ovflw                           :  1;
     unsigned      cmd_fifo_undflw                           :  1;
     unsigned      cmd_fifo_ovflw                            :  1;
     unsigned      mc_dfi_init_comp                          :  1;
     unsigned      mc_port_busy                              :  1;
     unsigned      mc_ctlr_busy                              :  1;
     unsigned      mc_q_almst_full                           :  1;
     unsigned      mem_rst_vld                               :  1;
     unsigned      smon_irq                                  :  1;
     unsigned      ddr_erase_done                            :  1;
     unsigned      reserved0                                 : 21;
#endif
} ncp_cmem_cfg_edg_irq_nomask_r_t;

/*! @struct ncp_cmem_cfg_edg_irq_raw_r_t
 *  @brief EDG_IRQ_RAW
 *  @details Raw value of the edge sensitive interrupt signals. This does not look at any edges, just the current state.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_cmem_cfg_edg_irq_raw_r_t\n
 *   </td>
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
 *     <td width="30%"> @param ddr_erase_done </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> DDR_ERASE_DONE </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param smon_irq </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> SMON Interrupt </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mem_rst_vld </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> DDR MC Memory Reset Valid </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mc_q_almst_full </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> DDR MC Queue Almost Full </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mc_ctlr_busy </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> DDR MC Controller Busy </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mc_port_busy </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> DDR MC Port Busy </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mc_dfi_init_comp </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> DDR MC DFI INIT Complete </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmd_fifo_ovflw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> CMD FIFO Overflow </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param cmd_fifo_undflw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> CMD FIFO Underflow </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param data_fifo_ovflw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> DATA FIFO Overflow </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param data_fifo_undflw </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> DATA FIFO Underflow </td>
 * </tr>
 * </table>
 * Applies to: 5600 xlf --> ncp_cmem_cfg_edg_irq_raw_r_t
 *
 * Implemented by: 
 *      edg_irq_raw
 */
 
typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 21;
     unsigned      ddr_erase_done                            :  1;
     unsigned      smon_irq                                  :  1;
     unsigned      mem_rst_vld                               :  1;
     unsigned      mc_q_almst_full                           :  1;
     unsigned      mc_ctlr_busy                              :  1;
     unsigned      mc_port_busy                              :  1;
     unsigned      mc_dfi_init_comp                          :  1;
     unsigned      cmd_fifo_ovflw                            :  1;
     unsigned      cmd_fifo_undflw                           :  1;
     unsigned      data_fifo_ovflw                           :  1;
     unsigned      data_fifo_undflw                          :  1;
#else    /* Little Endian */
     unsigned      data_fifo_undflw                          :  1;
     unsigned      data_fifo_ovflw                           :  1;
     unsigned      cmd_fifo_undflw                           :  1;
     unsigned      cmd_fifo_ovflw                            :  1;
     unsigned      mc_dfi_init_comp                          :  1;
     unsigned      mc_port_busy                              :  1;
     unsigned      mc_ctlr_busy                              :  1;
     unsigned      mc_q_almst_full                           :  1;
     unsigned      mem_rst_vld                               :  1;
     unsigned      smon_irq                                  :  1;
     unsigned      ddr_erase_done                            :  1;
     unsigned      reserved0                                 : 21;
#endif
} ncp_cmem_cfg_edg_irq_raw_r_t;

#ifdef __cplusplus
}
#endif

#endif /* _NCP_CMEM_CFG_REGS_H_ */
