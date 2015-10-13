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

#ifndef _NCP_ELM_REGS_H_
#define _NCP_ELM_REGS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*! @struct ncp_elm_control_r_t
 *  @brief ELM Control Register 1
 *  @details This register contains control information that sets the
     configuration of this instance of the ELM.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_control_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reencrypt_rate </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> This field controls the rate at which the cache lines
 *        are re-encrypted. The re-encryption mechanism re-encrypts
 *        one cache line every 32 clocks times the value in
 *        this field. A value of 0 re-encrypts system memory
 *        as fast as possible. This field cannot be written
 *        if the crypto_modes field in the Status register is
 *        set to no_encryption or no_encryption_1. When encryption
 *        is enabled, this field is frozen.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 6 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param two_elms </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> This field causes the ELM to ignore address bit 8
 *        from the SBSX. Note that the system memory uses only
 *        35 address bits, so some of upper SBSX address bits
 *        are always ignored. When this field is 0, the address
 *        from the SBSX is used unmodified. These are address
 *        bits 34:0. When this field is 1, SBSX address bit
 *        8 is ignored. The address which is used is {sbsx_addr[35:9],
 *        sbsx_addr[7:0]}. This field should be set to 0 when
 *        using one ELM;it should be set to 1 when using two
 *        ELMs.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param shields_up </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> This field causes the ELM to ignore all requests to
 *        the system memory from the interconnect logic (the
 *        SBSX). It is meant to be used when resetting the chip
 *        to prevent any glitches that might propagate to the
 *        system memory. CAUTION: if this bit is set during
 *        normal operation, it will cause the system to malfunction.
 *        When encryption is enabled, this field is forced to
 *        0.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param debug_plain_text </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> This field is used only in the debug mode. It allows
 *        the normal encryption pipeline timing to be used in
 *        the logic, but the data remains unencrypted. This
 *        field can only be set if the crypto_modes field in
 *        the Status register is set to ranged_encryption. When
 *        encryption is enabled, this field is frozen.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param force_encryption_off </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> This field can be used only when the crypto_mode in
 *        the ELM Status Register is set to ranged_encryption.
 *        When this field is set to 1, encryption is forced
 *        off as if the crypto_mode in the ELM Status Register
 *        were set to no_encryption or no_encryption_1. This
 *        is a debug mode used to test the chip and should not
 *        be used in normal operation. This field can only be
 *        set if the crypto_modes field in the Status register
 *        is set to ranged_encryption. When encryption is enabled,
 *        this field is frozen.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param force_encryption_on </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> This field can be used only when the crypto_mode in
 *        the ELM Status Register is set to ranged_encryption.
 *        When this field is set to 1 and the force_encryption_off
 *        is set to 0, encryption is forced on as if the crypto_mode
 *        in the ELM Status Register were set to forced_encryption.
 *        This is a debug mode used to test the chip and should
 *        not be used in normal operation. This field can only
 *        be set if the crypto_modes field in the Status register
 *        is set to ranged_encryption. When encryption is enabled,
 *        this field is frozen.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param crypto_enable </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enables encryption/decryption of the system memory.
 *        This field is only active when the crypto_mode field
 *        in the ELM Status Register is set to ranged_encryption
 *        or forced_encryption. The actual encryption enable
 *        status can be read from the crypto_enabled field in
 *        the ELM Status Register. This field cannot be set
 *        if the crypto_modes field in the Status register is
 *        set to no_encryption or no_encryption_1. Once encryption
 *        is enabled, it cannot be disabled.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_control_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reencrypt_rate                            : 16;
     unsigned      reserved0                                 :  6;
     unsigned      two_elms                                  :  1;
     unsigned      shields_up                                :  1;
     unsigned      debug_plain_text                          :  1;
     unsigned      force_encryption_off                      :  1;
     unsigned      force_encryption_on                       :  1;
     unsigned      reserved1                                 :  4;
     unsigned      crypto_enable                             :  1;
#else    /* Little Endian */
     unsigned      crypto_enable                             :  1;
     unsigned      reserved1                                 :  4;
     unsigned      force_encryption_on                       :  1;
     unsigned      force_encryption_off                      :  1;
     unsigned      debug_plain_text                          :  1;
     unsigned      shields_up                                :  1;
     unsigned      two_elms                                  :  1;
     unsigned      reserved0                                 :  6;
     unsigned      reencrypt_rate                            : 16;
#endif
} ncp_elm_control_r_t;

/*! @struct ncp_elm_status_r_t
 *  @brief ELM Status Register
 *  @details This register contains status information
     for this instance of the ELM.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_status_r_t\n
 *   </td>
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
 *     <td width="30%"> @param zeroization_in_prog </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Zeroization is in progress. This process is initialized
 *        by the the zeroization input or by the zeroization
 *        register. Zeroization clears the system memory and
 *        resets the encryption keys.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param init_in_prog </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> Initialization is in progress. This process is initialized
 *        by the initialization registers.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param crypto_key_loaded </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> This field indicates that the encryption/decryption
 *        keys are loaded into the LFSR and that keys are being
 *        calculated by the re-encryption logic. The key seeds
 *        must be loaded before this field is set.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param crypto_key_seeds_loaded </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> This field indicates that the crypto key seeds are
 *        successfully loaded. This field is set to zero when
 *        key seed register 0 is loaded, When all four key seed
 *        registers are loaded successfully, this field is set
 *        to 1. If it is 0 after loading all four key seed registers,
 *        the registers must be loaded again. This field indicates
 *        that at least one of 32 selected bits from the 128
 *        bit key seed changed from the last time that the key
 *        seed registers were loaded. After the chip is reset,
 *        it verifies that these selected 32 bits are not all
 *        zeros
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reencrypt_enabled </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> This field indicates that the re-encryption logic
 *        is enabled.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param encrypt_off </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> This field indicates that the ELM is in the no encryption
 *        mode whereby encryption is not allowed.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param encrypt_forced </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> This field indicates that the ELM is in the force
 *        encryption mode whereby the entire system memory is
 *        encrypted.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param crypto_mode </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> This field indicates the mode in which the encryption/decryption
 *        logic operates. This mode is set via fuses.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_status_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 23;
     unsigned      zeroization_in_prog                       :  1;
     unsigned      init_in_prog                              :  1;
     unsigned      crypto_key_loaded                         :  1;
     unsigned      crypto_key_seeds_loaded                   :  1;
     unsigned      reencrypt_enabled                         :  1;
     unsigned      encrypt_off                               :  1;
     unsigned      encrypt_forced                            :  1;
     unsigned      crypto_mode                               :  2;
#else    /* Little Endian */
     unsigned      crypto_mode                               :  2;
     unsigned      encrypt_forced                            :  1;
     unsigned      encrypt_off                               :  1;
     unsigned      reencrypt_enabled                         :  1;
     unsigned      crypto_key_seeds_loaded                   :  1;
     unsigned      crypto_key_loaded                         :  1;
     unsigned      init_in_prog                              :  1;
     unsigned      zeroization_in_prog                       :  1;
     unsigned      reserved0                                 : 23;
#endif
} ncp_elm_status_r_t;

/*! @struct ncp_elm_params_r_t
 *  @brief ELM Parameters Register
 *  @details This register contains some of the
             parameters used to build this version
             of the ELM.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_params_r_t\n
 *   </td>
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
 *     <td width="30%"> @param num_encrypt_ranges </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> The number of encryption ranges (minus 1) </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param max_sysmem_reqs </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The number of outstanding system memory requests outstanding
 *        allowed (minus 1) per channel (read and write)
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_params_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      num_encrypt_ranges                        :  8;
     unsigned      max_sysmem_reqs                           :  8;
#else    /* Little Endian */
     unsigned      max_sysmem_reqs                           :  8;
     unsigned      num_encrypt_ranges                        :  8;
     unsigned      reserved0                                 : 16;
#endif
} ncp_elm_params_r_t;

/*! @struct ncp_elm_sysmem_max_addr_r_t
 *  @brief System Memory Maximum Address Register
 *  @details This register holds the maximum system memory cache line address
             that is accessed either by a client or through the
             initialization logic.
             It is used for zeroization and setting the maximum
             system memory encryption address in the forced encryption
             mode.  Note that since it is a cache line address, it does not
             contain the least significant 6 bits in the byte address.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sysmem_max_addr_r_t\n
 *   </td>
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
 *     <td width="30%"> @param sysmem_max_addr </td>
 *     <td width="20%" align="center"> 29 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The maximum system memory cache line address which
 *        has been accessed.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sysmem_max_addr_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      sysmem_max_addr                           : 29;
#else    /* Little Endian */
     unsigned      sysmem_max_addr                           : 29;
     unsigned      reserved0                                 :  3;
#endif
} ncp_elm_sysmem_max_addr_r_t;

/*! @struct ncp_elm_reencrypt_thresh_addr_r_t
 *  @brief ELM Re-Encryption Threshold Address Register
 *  @details This register contains cache line threshold address.
             All cache lines accessed in system memory which are less than
             this threshold are encrypted/decrypted using key 1,
             All cache lines which are greater than or equal to this theshold
             are encrypted/decrypted using key 0.
             The cache line address is the byte address divided by 64 (shifted right
             6 bits).
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_reencrypt_thresh_addr_r_t\n
 *   </td>
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
 *     <td width="30%"> @param crypto_max_addr </td>
 *     <td width="20%" align="center"> 29 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The cache line threshold address at which the encryption
 *        key changes.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_reencrypt_thresh_addr_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      crypto_max_addr                           : 29;
#else    /* Little Endian */
     unsigned      crypto_max_addr                           : 29;
     unsigned      reserved0                                 :  3;
#endif
} ncp_elm_reencrypt_thresh_addr_r_t;

/*! @struct ncp_elm_zeroize_r_t
 *  @brief ELM Zeroization Register
 *  @details This register can initiate zeroization
     in the ELM.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_zeroize_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param start_zeroization </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> Zeroize ELM. When this bit transitions from 0 to 1
 *        and the enable_zero field is set, ELM zeroization
 *        begins. Zeroization is normally initiated by tamper
 *        detection logic, but this field is so that the functionality
 *        can be tested. Zeroization clears the encryption keys
 *        and system memory.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param enable_zeroization </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enable zeroization. These bits must be set to the
 *        value in enable_int_value before the zeroization process
 *        can be initiated by the remaining fields in this register.
 *        These bits are automatically reset on the next configuration
 *        write, which means that the initialization must be
 *        initiated on this next configuration write.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_zeroize_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 13;
     unsigned      start_zeroization                         :  1;
     unsigned      reserved1                                 : 10;
     unsigned      enable_zeroization                        :  8;
#else    /* Little Endian */
     unsigned      enable_zeroization                        :  8;
     unsigned      reserved1                                 : 10;
     unsigned      start_zeroization                         :  1;
     unsigned      reserved0                                 : 13;
#endif
} ncp_elm_zeroize_r_t;

/*! @struct ncp_elm_sysmem_addr_munge_r_t
 *  @brief ELM System Memory Address Munge Register
 *  @details This register can manipulate the address bits sent to the system memory
             in order to make memory accesses more efficient.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sysmem_addr_munge_r_t\n
 *   </td>
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
 *     <td width="30%"> @param sm_addr_munge_xor_mask </td>
 *     <td width="20%" align="center"> 14 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> This field indicates which bits of the system memory
 *        address are affected by the munging function. Bits
 *        20:0 of the address are never changed by munging.
 *        The bits in this field correspond to bits 34:21. Setting
 *        this field to 0 disables munging. This value in this
 *        field should be a function of the system memory capacity
 *        (per system memory controller) and the number of ranks
 *        in the DRAMs. The most significant bit if this field
 *        which should be set is determined by the system memory
 *        capacity. The MSB is log2(System memory size) - 22.
 *        For 1-rank DRAMs, the next two least signficant bits
 *        should be set. For 2-rank DRAMs, the next three least
 *        signficant bits should be set. For 4-rank DRAMs, the
 *        next four least signficant bits should be set. For
 *        example, with 32 GB of system memory with 4-rank DRAMs,
 *        this field should be 0x3e00. For 8 GB of system memory
 *        with 2-rank DRAMs, the setting should be 0x0f00.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sm_addr_munge_hash_mask </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> This field determines which system memory address
 *        bits are used in the hash funtion which is applied
 *        to the address to form the munged address. The bits
 *        in this register correspond to bits 21:6 of the system
 *        memory address. Address bits 5:0 are never used and
 *        all bits above 21 are always used.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sysmem_addr_munge_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  2;
     unsigned      sm_addr_munge_xor_mask                    : 14;
     unsigned      sm_addr_munge_hash_mask                   : 16;
#else    /* Little Endian */
     unsigned      sm_addr_munge_hash_mask                   : 16;
     unsigned      sm_addr_munge_xor_mask                    : 14;
     unsigned      reserved0                                 :  2;
#endif
} ncp_elm_sysmem_addr_munge_r_t;

/*! @struct ncp_elm_sysmem_init_cache_addr_r_t
 *  @brief System Memory Initialization Cache Address Register
 *  @details This register is used during system memory initialization
             by setting the starting cache line address for the
             initialization.
             The initialization process starts by writing to the
             System Memory Initialization Data Register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sysmem_init_cache_addr_r_t\n
 *   </td>
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
 *     <td width="30%"> @param init_start_addr </td>
 *     <td width="20%" align="center"> 29 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> This field contains the starting cache line address
 *        used for system memory initialization. The cache line
 *        size is 64 bytes, so this address is the byte address
 *        shifted right by 6 bits.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sysmem_init_cache_addr_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      init_start_addr                           : 29;
#else    /* Little Endian */
     unsigned      init_start_addr                           : 29;
     unsigned      reserved0                                 :  3;
#endif
} ncp_elm_sysmem_init_cache_addr_r_t;

/*! @struct ncp_elm_sysmem_init_cache_count_r_t
 *  @brief System Memory Initialization Cache Line Count Register
 *  @details This register is used during system memory initialization
             by determining how many cache lines are written per
             initialization request.
             The initialization process starts by writing to the
             System Memory Initialization Data Register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sysmem_init_cache_count_r_t\n
 *   </td>
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
 *     <td width="30%"> @param init_cache_count </td>
 *     <td width="20%" align="center"> 29 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> This field contains the number of 64-byte cache lines
 *        written to memory per initialization request (through
 *        the System Memory Initialization Data Register). The
 *        number of cache lines written is the value of this
 *        register plus one. Thus, for the default value of
 *        0, one cache line is written. When the write is complete,
 *        this register is reset to 0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sysmem_init_cache_count_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      init_cache_count                          : 29;
#else    /* Little Endian */
     unsigned      init_cache_count                          : 29;
     unsigned      reserved0                                 :  3;
#endif
} ncp_elm_sysmem_init_cache_count_r_t;

/*! @struct ncp_elm_sysmem_init_data_r_t
 *  @brief System Memory Initialization Data Register
 *  @details This register stores the data used to write
             into system memory during the initialization
             process.
             The initialization process starts by writing to
             this register.
             The APB bus is released (acknowledged) when
             this register is written, but the actual
             initialization process can take a long
             time.  Therefore, do not write to any of
             the System Memory Initialization registers
             until initialization is complete.
             The initialization process is complete when
             System Memory Initialization Cache Count
             Register is reset to 0 (assuming it did
             not start at 0) and when the init_complete
             field in the interrupt status register is
             set.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sysmem_init_data_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param init_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> This field contains the data written into system memory
 *        during the initialization process. If the set_wl_pattern
 *        field of the the System Memory Write Leveling Control
 *        register is not set, the 4-byte data in this register
 *        is duplicated 16 times within each cache line. If
 *        the set_wl_pattern field of the the System Memory
 *        Write Leveling Control register is set, a calculated
 *        pattern is used instead of the data in this register,
 *        but a write to this register is still required to
 *        start the system memory write operation.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sysmem_init_data_r_t
 *
 */

typedef struct
{
     unsigned  int                 init_data;
} ncp_elm_sysmem_init_data_r_t;

/*! @struct ncp_elm_sysmem_write_level_ctl_r_t
 *  @brief System Memory Write Leveling Control Register
 *  @details This register works in conjunction with the
             System Memory Initialization Cache Line Address and Data
             registers and the System Memory Write Leveling Data
             registers to assist software in setting
             up the write leveling for the DRAMs.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sysmem_write_level_ctl_r_t\n
 *   </td>
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
 *     <td width="30%"> @param lines_per_init_req </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> Sets the maximum number of cache lines which are written
 *        per system memory requests during initialization.
 *        A higher number is more efficient than a lower number,
 *        but it is unknown at this time the maximum number
 *        that the system memory controller can handle. The
 *        size of the first system memory request is adjusted
 *        so the request does not span an aligned region of
 *        the defined size. For example, if this field is set
 *        to cache_line_per_sm_req_is_4, (256 bytes), the first
 *        system memory request will stop at a 256 byte bounary.
 *        Subsequent requests will start at 256 byte boundaries.
 *        NOTE: setting this field to cache_line_per_sm_req_is_128
 *        violates AXI protocol since AXI does not allow transfers
 *        to cross 4K byte boundaries. With this field set to
 *        cache_line_per_sm_req_is_128, 8K byte transfers are
 *        possible. This setting is included for debug purposes
 *        only.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param data_selector </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> This field defines which 8-byte segment (8-byte aligned)
 *        from the 64-byte cache line is returned when the System
 *        Memory Levelization Data 0 register is read. The segment
 *        addresses are little endian. This field is equivalent
 *        to system memory address bits 5:3.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param invert_wl_pattern </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> When this field is set, the pattern described in the
 *        set_wl_pattern field is inverted. If set_wl_pattern
 *        is not set, this field is ignored.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param set_wl_pattern </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> When this field is set, the ELM generates a pattern
 *        to be written into each cache line (64 bytes) of system
 *        memory at the address defined by the System Memory
 *        Initialization Cache Line Address register and a length
 *        defined by the System Memory Initialization Cache
 *        Line Count register. The pattern is an incrementing
 *        byte pattern with 0x00 stored in the least significant
 *        byte (little endian) and which increments by one for
 *        each subsequent byte. This pattern is inverted if
 *        the invert_pattern field is set. The system memory
 *        write is initiated by writing into the System Memory
 *        Initialization Data register although the data in
 *        that write request is ignored.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sysmem_write_level_ctl_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      lines_per_init_req                        :  3;
     unsigned      data_selector                             :  3;
     unsigned      invert_wl_pattern                         :  1;
     unsigned      set_wl_pattern                            :  1;
#else    /* Little Endian */
     unsigned      set_wl_pattern                            :  1;
     unsigned      invert_wl_pattern                         :  1;
     unsigned      data_selector                             :  3;
     unsigned      lines_per_init_req                        :  3;
     unsigned      reserved0                                 : 24;
#endif
} ncp_elm_sysmem_write_level_ctl_r_t;

/*! @struct ncp_elm_sysmem_write_level_read_0_r_t
 *  @brief System Memory Write Leveling Read Register 0
 *  @details Reading this register initiates a system memory
             read request at the address specified by the
             System Memory Initialization Cache Line Address
             register and the data_selector field in the
             System Memory Write Level Control register.
             The least significant (little endian) 4 bytes from that read
             response is stored in this register,
             and the most significant 4 bytes is stored
             in the System Memory Write Leveling Read
             Registers 1.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sysmem_write_level_read_0_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wl_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The least significant (little endian) of the system
 *        memory read initiated by reading this register.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sysmem_write_level_read_0_r_t
 *
 */

typedef struct
{
     unsigned  int                   wl_data;
} ncp_elm_sysmem_write_level_read_0_r_t;

/*! @struct ncp_elm_sysmem_write_level_read_1_r_t
 *  @brief System Memory Write Leveling Read Register 1
 *  @details When the System Memory Write Leveling Read Register 0
             is read, the most significant 4 bytes from that ready
             response is stored in this register.
             Reading this register returns those bytes, but it
             does not cause any system memory request.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sysmem_write_level_read_1_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param wl_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The most significant (little endian) of the system
 *        memory read response which was initiated by reading
 *        the System Memory Write Leveling Register 0.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sysmem_write_level_read_1_r_t
 *
 */

typedef struct
{
     unsigned  int                   wl_data;
} ncp_elm_sysmem_write_level_read_1_r_t;

/*! @struct ncp_elm_crypto_key_seed_0_r_t
 *  @brief ELM Encryption Key Seed Registers
 *  @details This register contains 32 bits of a 128 bit
     value used to seed the generation of the crypto keys.
     This 128-bit seed value must never be set to 0.
     The key seed registers must be loaded in the order
     0, 1, 2, and 3.
     The registers may be reloaded at any time.
     This register is word 0.
     This register is not readable, but a function of
     its value can be read from the key_seed_signature
     field in the ELM Status Register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_crypto_key_seed_0_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param key_seed </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Word 0 of the key seed. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_crypto_key_seed_0_r_t
 *
 */

typedef struct
{
     unsigned  int                  key_seed;
} ncp_elm_crypto_key_seed_0_r_t;

/*! @struct ncp_elm_crypto_key_seed_1_r_t
 *  @brief ELM Encryption Key Seed Registers
 *  @details This register contains 32 bits of a 128 bit
     value used to seed the generation of the crypto keys.
     This 128-bit seed value must never be set to 0.
     The key seed registers must be loaded in the order
     0, 1, 2, and 3.
     The registers may be reloaded at any time.
     This register is word 1.
     This register is not readable, but a function of
     its value can be read from the key_seed_signature
     field in the ELM Status Register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_crypto_key_seed_1_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param key_seed </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Word 1 of the key seed. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_crypto_key_seed_1_r_t
 *
 */

typedef struct
{
     unsigned  int                  key_seed;
} ncp_elm_crypto_key_seed_1_r_t;

/*! @struct ncp_elm_crypto_key_seed_2_r_t
 *  @brief ELM Encryption Key Seed Registers
 *  @details This register contains 32 bits of a 128 bit
     value used to seed the generation of the crypto keys.
     This 128-bit seed value must never be set to 0.
     The key seed registers must be loaded in the order
     0, 1, 2, and 3.
     The registers may be reloaded at any time.
     This register is word 2.
     This register is not readable, but a function of
     its value can be read from the key_seed_signature
     field in the ELM Status Register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_crypto_key_seed_2_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param key_seed </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Word 2 of the key seed. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_crypto_key_seed_2_r_t
 *
 */

typedef struct
{
     unsigned  int                  key_seed;
} ncp_elm_crypto_key_seed_2_r_t;

/*! @struct ncp_elm_crypto_key_seed_3_r_t
 *  @brief ELM Encryption Key Seed Registers
 *  @details This register contains 32 bits of a 128 bit
     value used to seed the generation of the crypto keys.
     This 128-bit seed value must never be set to 0.
     The key seed registers must be loaded in the order
     0, 1, 2, and 3.
     The registers may be reloaded at any time.
     This register is word 3.
     This register is not readable, but a function of
     its value can be read from the key_seed_signature
     field in the ELM Status Register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_crypto_key_seed_3_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param key_seed </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Word 3 of the key seed. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_crypto_key_seed_3_r_t
 *
 */

typedef struct
{
     unsigned  int                  key_seed;
} ncp_elm_crypto_key_seed_3_r_t;

/*! @struct ncp_elm_crypto_range_start_r_t
 *  @brief ELM Crypto Range Starting Address Register
 *  @details This register contains the starting 8K byte address
             of system memory addresses which are to be
             encrypted.  The size of this range is defined in the
             corresponding Crypto Range Size Register.
             This address is the starting system memory byte address
             right-shifted by 13 bits.
             The granularity of the encryption range is
             8192 bytes.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_crypto_range_start_r_t\n
 *   </td>
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
 *     <td width="30%"> @param range_start </td>
 *     <td width="20%" align="center"> 22 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The starting 8K byte address of a range of system
 *        memory addresses to encrypt.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_crypto_range_start_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 10;
     unsigned      range_start                               : 22;
#else    /* Little Endian */
     unsigned      range_start                               : 22;
     unsigned      reserved0                                 : 10;
#endif
} ncp_elm_crypto_range_start_r_t;

/*! @struct ncp_elm_crypto_range_size_r_t
 *  @brief ELM Crypto Range Size Register
 *  @details This register contains size of an encryption range of system memory
             addresses that are encrypted. The value in this register is
             the number of 8K byte segments which
             are encrypted.  The range is disabled if the range_size
             field is 0.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_crypto_range_size_r_t\n
 *   </td>
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
 *     <td width="30%"> @param range_size </td>
 *     <td width="20%" align="center"> 23 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The number of 8K byte segments in this system encryption
 *        range. If this field is 0, this range is disabled.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_crypto_range_size_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  9;
     unsigned      range_size                                : 23;
#else    /* Little Endian */
     unsigned      range_size                                : 23;
     unsigned      reserved0                                 :  9;
#endif
} ncp_elm_crypto_range_size_r_t;

/*! @struct ncp_elm_sm_read_req_r_t
 *  @brief ELM System Memory Read Request Counter
 *  @details This register contains the count for the number of read requests that have been
             issued to the system memory.
             In an idle system, this count should be equal to the ELM System Memory Read Response
             Last Counter.
             This counter can be reset by writing a 1 to the reset_debug_regs field in the
             ELM System Memory Counter Control register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_read_req_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param count </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> This register holds the count for the number of read
 *        requests that have been issued to the system memory.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_read_req_r_t
 *
 */

typedef struct
{
     unsigned  int                     count;
} ncp_elm_sm_read_req_r_t;

/*! @struct ncp_elm_sm_read_resp_last_r_t
 *  @brief ELM System Memory Read Response Last Counter
 *  @details This register contains the count for the number of read response last beats that have been
             received from the system memory.
             In an idle system, this count should be equal to the ELM System Memory Read Request
             Counter.
             This counter can be reset by writing a 1 to the reset_debug_regs field in the
             ELM System Memory Counter Control register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_read_resp_last_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param count </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> This register holds the count for the number of read
 *        response last beats that have been received from the
 *        system memory.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_read_resp_last_r_t
 *
 */

typedef struct
{
     unsigned  int                     count;
} ncp_elm_sm_read_resp_last_r_t;

/*! @struct ncp_elm_sm_read_req_beat_r_t
 *  @brief ELM System Memory Read Request Beat Counter
 *  @details This register contains the count for the number of read request beats that have been
             requested from the system memory.
             In an idle system, this count should be equal to the ELM System Memory Read Response
             Counter.
             This counter can be reset by writing a 1 to the reset_debug_regs field in the
             ELM System Memory Counter Control register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_read_req_beat_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param count </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> This register holds the count for the number of read
 *        request beats that have been requested from the system
 *        memory.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_read_req_beat_r_t
 *
 */

typedef struct
{
     unsigned  int                     count;
} ncp_elm_sm_read_req_beat_r_t;

/*! @struct ncp_elm_sm_read_resp_beat_r_t
 *  @brief ELM System Memory Read Response Beat Counter
 *  @details This register contains the count for the number of read response beats that have been
             received from the system memory.
             In an idle system, this count should be equal to the ELM System Memory Read Request
             Beat Counter.
             This counter can be reset by writing a 1 to the reset_debug_regs field in the
             ELM System Memory Counter Control register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_read_resp_beat_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param count </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> This register holds the count for the number of read
 *        response beats that have been received from the system
 *        memory.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_read_resp_beat_r_t
 *
 */

typedef struct
{
     unsigned  int                     count;
} ncp_elm_sm_read_resp_beat_r_t;

/*! @struct ncp_elm_sm_write_req_beat_r_t
 *  @brief ELM System Memory Write Request Beat Counter
 *  @details This register contains the count for the number of write request beats that have been
             requested for the system memory.
             In an idle system, this count should be equal to the ELM System Memory Write Data
             Beat Counter.
             This counter can be reset by writing a 1 to the reset_debug_regs field in the
             ELM System Memory Counter Control register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_write_req_beat_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param count </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> This register holds the count for the number of write
 *        request beats that have been requested for the system
 *        memory.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_write_req_beat_r_t
 *
 */

typedef struct
{
     unsigned  int                     count;
} ncp_elm_sm_write_req_beat_r_t;

/*! @struct ncp_elm_sm_write_data_beat_r_t
 *  @brief ELM System Memory Write Data Beat Counter
 *  @details This register contains the count for the number of write request beats that have been
             requested for the system memory.
             In an idle system, this count should be equal to the ELM System Memory Write Request
             Beat Counter.
             This counter can be reset by writing a 1 to the reset_debug_regs field in the
             ELM System Memory Counter Control register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_write_data_beat_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param count </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> This register holds the count for the number of write
 *        data beats that have been issued to the system memory.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_write_data_beat_r_t
 *
 */

typedef struct
{
     unsigned  int                     count;
} ncp_elm_sm_write_data_beat_r_t;

/*! @struct ncp_elm_sm_write_req_r_t
 *  @brief ELM System Memory Write Request Counter
 *  @details This register contains the count for the number of write requests that have been
             issued to the system memory.
             In an idle system, this count should be equal to the ELM System Memory Write Data
             Last Counter and the ELM System Memory Write Response Counter.
             This counter can be reset by writing a 1 to the reset_debug_regs field in the
             ELM System Memory Counter Control register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_write_req_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param count </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> This register holds the count for the number of write
 *        requests that have been issued to the system memory.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_write_req_r_t
 *
 */

typedef struct
{
     unsigned  int                     count;
} ncp_elm_sm_write_req_r_t;

/*! @struct ncp_elm_sm_write_data_last_r_t
 *  @brief ELM System Memory Write Data Beat Counter
 *  @details This register contains the count for the number of write request last beats that have been
             sent to the system memory.
             In an idle system, this count should be equal to the ELM System Memory Write Request
             Counter and the ELM System Memory Write Response Counter.
             This counter can be reset by writing a 1 to the reset_debug_regs field in the
             ELM System Memory Counter Control register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_write_data_last_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param count </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> This register holds the count for the number of write
 *        data last beats that have been issued to the system
 *        memory.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_write_data_last_r_t
 *
 */

typedef struct
{
     unsigned  int                     count;
} ncp_elm_sm_write_data_last_r_t;

/*! @struct ncp_elm_sm_write_resp_r_t
 *  @brief ELM System Memory Write Response Counter
 *  @details This register contains the count for the number of write responses that have been
             received from the system memory.
             In an idle system, this count should be equal to the ELM System Memory Write Request
             Counter and the ELM System Memory Write Data Last Counter.
             This counter can be reset by writing a 1 to the reset_debug_regs field in the
             ELM System Memory Counter Control register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_write_resp_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param count </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> This register holds the count for the number of write
 *        responses last beats that have been received from
 *        the system memory.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_write_resp_r_t
 *
 */

typedef struct
{
     unsigned  int                     count;
} ncp_elm_sm_write_resp_r_t;

/*! @struct ncp_elm_sm_cnt_ctl_r_t
 *  @brief ELM System Memory Counter Control Register
 *  @details This register controls the operation of the System Memory count registers.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_cnt_ctl_r_t\n
 *   </td>
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
 *     <td width="30%"> @param reset_debug_regs </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> This field resets the nine system memory count registers
 *        to zeros. The registers are reset when this field
 *        is written with 1. It will always read as a 0. The
 *        registers which are reset by this field are the read
 *        request counter, the read request beat counter, the
 *        read response beat counter, the read response last
 *        counter, the write request counter, the write request
 *        beat counter, the write data beat counter, the write
 *        data last counter, and the write response counter.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_cnt_ctl_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 31;
     unsigned      reset_debug_regs                          :  1;
#else    /* Little Endian */
     unsigned      reset_debug_regs                          :  1;
     unsigned      reserved0                                 : 31;
#endif
} ncp_elm_sm_cnt_ctl_r_t;

/*! @struct ncp_elm_sm_debug_ctl_r_t
 *  @brief ELM System Memory Debug Control Register
 *  @details This register controls the operation of the System Memory debug logic.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_ctl_r_t\n
 *   </td>
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
 *     <td width="30%"> @param debug_unknown_id </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> This field is used for the reconstructed write data
 *        ID field when the data is received before the write
 *        command. It indicates that the ID is unknown.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param reserved1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param debug_reset </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> When this bit is set, the head and tail pointers into
 *        each capture SRAM are reset which effectively empties
 *        the SRAMs.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param debug_stop_on_full </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> When this bit is set, each SRAM stops capturing data
 *        when the SRAM is full.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param debug_run </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> Enable debug logic operation. When this bit is set,
 *        the capture SRAMs are enabled to capture bus signals
 *        to and from the system memory.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_ctl_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 12;
     unsigned      debug_unknown_id                          : 12;
     unsigned      reserved1                                 :  5;
     unsigned      debug_reset                               :  1;
     unsigned      debug_stop_on_full                        :  1;
     unsigned      debug_run                                 :  1;
#else    /* Little Endian */
     unsigned      debug_run                                 :  1;
     unsigned      debug_stop_on_full                        :  1;
     unsigned      debug_reset                               :  1;
     unsigned      reserved1                                 :  5;
     unsigned      debug_unknown_id                          : 12;
     unsigned      reserved0                                 : 12;
#endif
} ncp_elm_sm_debug_ctl_r_t;

/*! @struct ncp_elm_sm_debug_write_status_r_t
 *  @brief ELM System Memory Debug Write Status Register
 *  @details This register contains the status
             of the system memory debug logic on the write buses.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_write_status_r_t\n
 *   </td>
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
 *     <td width="30%"> @param debug_b_size_log2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> The log (base 2) of the size of the write response
 *        capture SRAM.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param debug_w_size_log2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> The log (base 2) of the size of the write data capture
 *        SRAM.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param debug_wa_size_log2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The log (base 2) of the size of the write address
 *        capture SRAM.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_write_status_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 20;
     unsigned      debug_b_size_log2                         :  4;
     unsigned      debug_w_size_log2                         :  4;
     unsigned      debug_wa_size_log2                        :  4;
#else    /* Little Endian */
     unsigned      debug_wa_size_log2                        :  4;
     unsigned      debug_w_size_log2                         :  4;
     unsigned      debug_b_size_log2                         :  4;
     unsigned      reserved0                                 : 20;
#endif
} ncp_elm_sm_debug_write_status_r_t;

/*! @struct ncp_elm_sm_debug_aw_status_r_t
 *  @brief ELM System Memory Debug Write Address Status Register
 *  @details This register contains the status for the write address capture SRAMs
             in the system memory debug logic.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_aw_status_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param debug_head_ptr </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> The write address capture SRAM head pointer. This
 *        points to the next SRAM address to be read from the
 *        configuration logic.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param debug_tail_ptr </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The write address capture SRAM tail pointer. This
 *        points to the next SRAM address to be written when
 *        a transaction is captured.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_aw_status_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      debug_head_ptr                            : 16;
     unsigned      debug_tail_ptr                            : 16;
#else    /* Little Endian */
     unsigned      debug_tail_ptr                            : 16;
     unsigned      debug_head_ptr                            : 16;
#endif
} ncp_elm_sm_debug_aw_status_r_t;

/*! @struct ncp_elm_sm_debug_w_status_r_t
 *  @brief ELM System Memory Debug Write Data Status Register
 *  @details This register contains the status for the write data capture SRAMs
             in the system memory debug logic.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_w_status_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param debug_head_ptr </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> The write data capture SRAM head pointer. This points
 *        to the next SRAM address to be read from the configuration
 *        logic.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param debug_tail_ptr </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The write data capture SRAM tail pointer. This points
 *        to the next SRAM address to be written when a transaction
 *        is captured.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_w_status_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      debug_head_ptr                            : 16;
     unsigned      debug_tail_ptr                            : 16;
#else    /* Little Endian */
     unsigned      debug_tail_ptr                            : 16;
     unsigned      debug_head_ptr                            : 16;
#endif
} ncp_elm_sm_debug_w_status_r_t;

/*! @struct ncp_elm_sm_debug_b_status_r_t
 *  @brief ELM System Memory Debug Write Response Status Register
 *  @details This register contains the status for the write response capture SRAMs
             in the system memory debug logic.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_b_status_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param debug_head_ptr </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> The write response capture SRAM head pointer. This
 *        points to the next SRAM address to be read from the
 *        configuration logic.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param debug_tail_ptr </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The write response capture SRAM tail pointer. This
 *        points to the next SRAM address to be written when
 *        a transaction is captured.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_b_status_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      debug_head_ptr                            : 16;
     unsigned      debug_tail_ptr                            : 16;
#else    /* Little Endian */
     unsigned      debug_tail_ptr                            : 16;
     unsigned      debug_head_ptr                            : 16;
#endif
} ncp_elm_sm_debug_b_status_r_t;

/*! @struct ncp_elm_sm_debug_b_ram_r_t
 *  @brief ELM System Memory Debug Write Response RAM
 *  @details This register contains the write response capture SRAM at the location
             indicated by the head pointer.
             If the SRAM is empty (head pointer == tail pointer),
             zeros are returned;otherwise, the data from the SRAM is
             read and the tail pointer is incremented.
             The debug_run bit in the ELM System Memory Debug Control
             Register should be off (0) when reading this RAM;
             otherwise erratic results can occur.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_b_ram_r_t\n
 *   </td>
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
 *     <td width="30%"> @param debug_bresp </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> The response code of the write response. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param debug_bid </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The ID of the write response. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_b_ram_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 18;
     unsigned      debug_bresp                               :  2;
     unsigned      debug_bid                                 : 12;
#else    /* Little Endian */
     unsigned      debug_bid                                 : 12;
     unsigned      debug_bresp                               :  2;
     unsigned      reserved0                                 : 18;
#endif
} ncp_elm_sm_debug_b_ram_r_t;

/*! @struct ncp_elm_sm_debug_aw_ram_0_r_t
 *  @brief ELM System Memory Debug Write Address RAM, Part 0
 *  @details This register contains bits 31:0 of the write address capture
             SRAM at the location indicated by the head pointer.
             If the SRAM is empty (head pointer == tail pointer),
             zeros are returned;otherwise, the data from the SRAM is read.
             The debug_run bit in the ELM System Memory Debug Control
             Register should be off (0) when reading this RAM;
             otherwise erratic results can occur.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_aw_ram_0_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param write_addr_lsb </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The least significant 32 bits of the write address. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_aw_ram_0_r_t
 *
 */

typedef struct
{
     unsigned  int            write_addr_lsb;
} ncp_elm_sm_debug_aw_ram_0_r_t;

/*! @struct ncp_elm_sm_debug_aw_ram_1_r_t
 *  @brief ELM System Memory Debug Write Address RAM, Part 1
 *  @details This register contains bits 63:32 of the write address capture
             SRAM at the location indicated by the head pointer.
             If the SRAM is empty (head pointer == tail pointer),
             zeros are returned;otherwise, the data from the SRAM is read.
             The debug_run bit in the ELM System Memory Debug Control
             Register should be off (0) when reading this RAM;
             otherwise erratic results can occur.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_aw_ram_1_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param write_addr_cache_lsb </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> The write transaction cache (least signficant 3 bits). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param write_addr_lock </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> The write transaction lock. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param write_addr_burst </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> The write transaction burst type. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param write_addr_size </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> The write transaction size. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param write_addr_len </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> The write transaction length (minus 1). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param write_addr_id </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> The write address ID. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param write_addr_msb </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The most significant 3 bits of the write address. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_aw_ram_1_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      write_addr_cache_lsb                      :  3;
     unsigned      write_addr_lock                           :  1;
     unsigned      write_addr_burst                          :  2;
     unsigned      write_addr_size                           :  3;
     unsigned      write_addr_len                            :  8;
     unsigned      write_addr_id                             : 12;
     unsigned      write_addr_msb                            :  3;
#else    /* Little Endian */
     unsigned      write_addr_msb                            :  3;
     unsigned      write_addr_id                             : 12;
     unsigned      write_addr_len                            :  8;
     unsigned      write_addr_size                           :  3;
     unsigned      write_addr_burst                          :  2;
     unsigned      write_addr_lock                           :  1;
     unsigned      write_addr_cache_lsb                      :  3;
#endif
} ncp_elm_sm_debug_aw_ram_1_r_t;

/*! @struct ncp_elm_sm_debug_aw_ram_2_r_t
 *  @brief ELM System Memory Debug Write Address RAM, Part 2
 *  @details This register contains bits 71:64 of the write address capture
             SRAM at the location indicated by the head pointer.
             If the SRAM is empty (head pointer == tail pointer),
             zeros are returned;otherwise, the data from the SRAM is read
             and the tail pointer is incremented.
             The debug_run bit in the ELM System Memory Debug Control
             Register should be off (0) when reading this RAM;
             otherwise erratic results can occur.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_aw_ram_2_r_t\n
 *   </td>
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
 *     <td width="30%"> @param write_addr_qos </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> The write transaction QOS field. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param write_addr_prot </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> The write transaction protect field. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param write_addr_cache_msb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The write transaction cache (most signficant bit). </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_aw_ram_2_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      write_addr_qos                            :  3;
     unsigned      write_addr_prot                           :  4;
     unsigned      write_addr_cache_msb                      :  1;
#else    /* Little Endian */
     unsigned      write_addr_cache_msb                      :  1;
     unsigned      write_addr_prot                           :  4;
     unsigned      write_addr_qos                            :  3;
     unsigned      reserved0                                 : 24;
#endif
} ncp_elm_sm_debug_aw_ram_2_r_t;

/*! @struct ncp_elm_sm_debug_w_ram_0_r_t
 *  @brief ELM System Memory Debug Write Data RAM, Part 0
 *  @details This register contains bits 31:0 of the write data capture
             SRAM at the location indicated by the head pointer.
             If the SRAM is empty (head pointer == tail pointer),
             zeros are returned;otherwise, the data from the SRAM is read.
             The debug_run bit in the ELM System Memory Debug Control
             Register should be off (0) when reading this RAM;
             otherwise erratic results can occur.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_w_ram_0_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param write_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The write data. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_w_ram_0_r_t
 *
 */

typedef struct
{
     unsigned  int                write_data;
} ncp_elm_sm_debug_w_ram_0_r_t;

/*! @struct ncp_elm_sm_debug_w_ram_1_r_t
 *  @brief ELM System Memory Debug Write Data RAM, Part 1
 *  @details This register contains bits 63:32 of the write data capture
             SRAM at the location indicated by the head pointer.
             If the SRAM is empty (head pointer == tail pointer),
             zeros are returned;otherwise, the data from the SRAM is read.
             The debug_run bit in the ELM System Memory Debug Control
             Register should be off (0) when reading this RAM;
             otherwise erratic results can occur.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_w_ram_1_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param write_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The write data. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_w_ram_1_r_t
 *
 */

typedef struct
{
     unsigned  int                write_data;
} ncp_elm_sm_debug_w_ram_1_r_t;

/*! @struct ncp_elm_sm_debug_w_ram_2_r_t
 *  @brief ELM System Memory Debug Write Data RAM, Part 2
 *  @details This register contains bits 95:64 of the write data capture
             SRAM at the location indicated by the head pointer.
             If the SRAM is empty (head pointer == tail pointer),
             zeros are returned;otherwise, the data from the SRAM is read.
             The debug_run bit in the ELM System Memory Debug Control
             Register should be off (0) when reading this RAM;
             otherwise erratic results can occur.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_w_ram_2_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param write_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The write data. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_w_ram_2_r_t
 *
 */

typedef struct
{
     unsigned  int                write_data;
} ncp_elm_sm_debug_w_ram_2_r_t;

/*! @struct ncp_elm_sm_debug_w_ram_3_r_t
 *  @brief ELM System Memory Debug Write Data RAM, Part 3
 *  @details This register contains bits 127:96 of the write data capture
             SRAM at the location indicated by the head pointer.
             If the SRAM is empty (head pointer == tail pointer),
             zeros are returned;otherwise, the data from the SRAM is read.
             The debug_run bit in the ELM System Memory Debug Control
             Register should be off (0) when reading this RAM;
             otherwise erratic results can occur.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_w_ram_3_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param write_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The write data. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_w_ram_3_r_t
 *
 */

typedef struct
{
     unsigned  int                write_data;
} ncp_elm_sm_debug_w_ram_3_r_t;

/*! @struct ncp_elm_sm_debug_w_ram_4_r_t
 *  @brief ELM System Memory Debug Write Data RAM, Part 4
 *  @details This register contains bits 159:128 of the write data capture
             SRAM at the location indicated by the head pointer.
             If the SRAM is empty (head pointer == tail pointer),
             zeros are returned;otherwise, the data from the SRAM is read.
             The debug_run bit in the ELM System Memory Debug Control
             Register should be off (0) when reading this RAM;
             otherwise erratic results can occur.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_w_ram_4_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param write_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The write data. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_w_ram_4_r_t
 *
 */

typedef struct
{
     unsigned  int                write_data;
} ncp_elm_sm_debug_w_ram_4_r_t;

/*! @struct ncp_elm_sm_debug_w_ram_5_r_t
 *  @brief ELM System Memory Debug Write Data RAM, Part 5
 *  @details This register contains bits 191:160 of the write data capture
             SRAM at the location indicated by the head pointer.
             If the SRAM is empty (head pointer == tail pointer),
             zeros are returned;otherwise, the data from the SRAM is read.
             The debug_run bit in the ELM System Memory Debug Control
             Register should be off (0) when reading this RAM;
             otherwise erratic results can occur.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_w_ram_5_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param write_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The write data. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_w_ram_5_r_t
 *
 */

typedef struct
{
     unsigned  int                write_data;
} ncp_elm_sm_debug_w_ram_5_r_t;

/*! @struct ncp_elm_sm_debug_w_ram_6_r_t
 *  @brief ELM System Memory Debug Write Data RAM, Part 6
 *  @details This register contains bits 223:192 of the write data capture
             SRAM at the location indicated by the head pointer.
             If the SRAM is empty (head pointer == tail pointer),
             zeros are returned;otherwise, the data from the SRAM is read.
             The debug_run bit in the ELM System Memory Debug Control
             Register should be off (0) when reading this RAM;
             otherwise erratic results can occur.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_w_ram_6_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param write_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The write data. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_w_ram_6_r_t
 *
 */

typedef struct
{
     unsigned  int                write_data;
} ncp_elm_sm_debug_w_ram_6_r_t;

/*! @struct ncp_elm_sm_debug_w_ram_7_r_t
 *  @brief ELM System Memory Debug Write Data RAM, Part 7
 *  @details This register contains bits 255:224 of the write data capture
             SRAM at the location indicated by the head pointer.
             If the SRAM is empty (head pointer == tail pointer),
             zeros are returned;otherwise, the data from the SRAM is read.
             The debug_run bit in the ELM System Memory Debug Control
             Register should be off (0) when reading this RAM;
             otherwise erratic results can occur.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_w_ram_7_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param write_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The write data. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_w_ram_7_r_t
 *
 */

typedef struct
{
     unsigned  int                write_data;
} ncp_elm_sm_debug_w_ram_7_r_t;

/*! @struct ncp_elm_sm_debug_w_ram_8_r_t
 *  @brief ELM System Memory Debug Write Data RAM, Part 8
 *  @details This register contains bits 287:256 of the write data capture
             SRAM at the location indicated by the head pointer.
             If the SRAM is empty (head pointer == tail pointer),
             zeros are returned;otherwise, the data from the SRAM is read.
             The debug_run bit in the ELM System Memory Debug Control
             Register should be off (0) when reading this RAM;
             otherwise erratic results can occur.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_w_ram_8_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param write_data_strobes </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The write data strobes. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_w_ram_8_r_t
 *
 */

typedef struct
{
     unsigned  int        write_data_strobes;
} ncp_elm_sm_debug_w_ram_8_r_t;

/*! @struct ncp_elm_sm_debug_w_ram_9_r_t
 *  @brief ELM System Memory Debug Write Data RAM, Part 9
 *  @details This register contains bits 300:288 of the write data capture
             SRAM at the location indicated by the head pointer.
             If the SRAM is empty (head pointer == tail pointer),
             zeros are returned;otherwise, the data from the SRAM is read
             and the tail pointer is incremented.
             The debug_run bit in the ELM System Memory Debug Control
             Register should be off (0) when reading this RAM;
             otherwise erratic results can occur.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_w_ram_9_r_t\n
 *   </td>
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
 *     <td width="30%"> @param write_data_last </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> The write data last cycle. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param write_data_id </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The reconstructed ID for the write data. If the ID
 *        is not known, the contents of the unknown_id field
 *        from the ELM System Memory Debug Control register
 *        are used.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_w_ram_9_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 19;
     unsigned      write_data_last                           :  1;
     unsigned      write_data_id                             : 12;
#else    /* Little Endian */
     unsigned      write_data_id                             : 12;
     unsigned      write_data_last                           :  1;
     unsigned      reserved0                                 : 19;
#endif
} ncp_elm_sm_debug_w_ram_9_r_t;

/*! @struct ncp_elm_sm_debug_read_status_r_t
 *  @brief ELM System Memory Debug Read Status Register
 *  @details This register contains the status
             of the system memory debug logic on the read buses.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_read_status_r_t\n
 *   </td>
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
 *     <td width="30%"> @param debug_r_size_log2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> The log (base 2) of the size of the read response
 *        capture SRAM.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param debug_ra_size_log2 </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The log (base 2) of the size of the read address capture
 *        SRAM.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_read_status_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      debug_r_size_log2                         :  4;
     unsigned      debug_ra_size_log2                        :  4;
#else    /* Little Endian */
     unsigned      debug_ra_size_log2                        :  4;
     unsigned      debug_r_size_log2                         :  4;
     unsigned      reserved0                                 : 24;
#endif
} ncp_elm_sm_debug_read_status_r_t;

/*! @struct ncp_elm_sm_debug_ar_status_r_t
 *  @brief ELM System Memory Debug Read Address Status Register
 *  @details This register contains the status for the read address capture SRAMs
             in the system memory debug logic.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_ar_status_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param debug_head_ptr </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> The read address capture SRAM head pointer. This points
 *        to the next SRAM address to be read from the configuration
 *        logic.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param debug_tail_ptr </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The read address capture SRAM tail pointer. This points
 *        to the next SRAM address to be written when a transaction
 *        is captured.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_ar_status_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      debug_head_ptr                            : 16;
     unsigned      debug_tail_ptr                            : 16;
#else    /* Little Endian */
     unsigned      debug_tail_ptr                            : 16;
     unsigned      debug_head_ptr                            : 16;
#endif
} ncp_elm_sm_debug_ar_status_r_t;

/*! @struct ncp_elm_sm_debug_r_status_r_t
 *  @brief ELM System Memory Debug Read Response Status Register
 *  @details This register contains the status for the read response capture SRAMs
             in the system memory debug logic.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_r_status_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param debug_head_ptr </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> The read response capture SRAM head pointer. This
 *        points to the next SRAM address to be read from the
 *        configuration logic.
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param debug_tail_ptr </td>
 *     <td width="20%" align="center"> 16 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The read response capture SRAM tail pointer. This
 *        points to the next SRAM address to be written when
 *        a transaction is captured.
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_r_status_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      debug_head_ptr                            : 16;
     unsigned      debug_tail_ptr                            : 16;
#else    /* Little Endian */
     unsigned      debug_tail_ptr                            : 16;
     unsigned      debug_head_ptr                            : 16;
#endif
} ncp_elm_sm_debug_r_status_r_t;

/*! @struct ncp_elm_sm_debug_ar_ram_0_r_t
 *  @brief ELM System Memory Debug Read Address RAM, Part 0
 *  @details This register contains bits 31:0 of the read address capture
             SRAM at the location indicated by the head pointer.
             If the SRAM is empty (head pointer == tail pointer),
             zeros are returned;otherwise, the data from the SRAM is read.
             The debug_run bit in the ELM System Memory Debug Control
             Register should be off (0) when reading this RAM;
             otherwise erratic results can occur.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_ar_ram_0_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param read_addr_lsb </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The least significant 32 bits of the read address. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_ar_ram_0_r_t
 *
 */

typedef struct
{
     unsigned  int             read_addr_lsb;
} ncp_elm_sm_debug_ar_ram_0_r_t;

/*! @struct ncp_elm_sm_debug_ar_ram_1_r_t
 *  @brief ELM System Memory Debug Read Address RAM, Part 1
 *  @details This register contains bits 63:32 of the read address capture
             SRAM at the location indicated by the head pointer.
             If the SRAM is empty (head pointer == tail pointer),
             zeros are returned;otherwise, the data from the SRAM is read.
             The debug_run bit in the ELM System Memory Debug Control
             Register should be off (0) when reading this RAM;
             otherwise erratic results can occur.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_ar_ram_1_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param read_addr_cache_lsb </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 29 </td>
 *   <td width="30%"> The read transaction cache (least signficant 3 bits). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param read_addr_lock </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 28 </td>
 *   <td width="30%"> The read transaction lock. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param read_addr_burst </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 26 </td>
 *   <td width="30%"> The read transaction burst type. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param read_addr_size </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 23 </td>
 *   <td width="30%"> The read transaction size. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param read_addr_len </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> The read transaction length (minus 1). </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param read_addr_id </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> The read address ID. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param read_addr_msb </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The most significant 3 bits of the read address. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_ar_ram_1_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      read_addr_cache_lsb                       :  3;
     unsigned      read_addr_lock                            :  1;
     unsigned      read_addr_burst                           :  2;
     unsigned      read_addr_size                            :  3;
     unsigned      read_addr_len                             :  8;
     unsigned      read_addr_id                              : 12;
     unsigned      read_addr_msb                             :  3;
#else    /* Little Endian */
     unsigned      read_addr_msb                             :  3;
     unsigned      read_addr_id                              : 12;
     unsigned      read_addr_len                             :  8;
     unsigned      read_addr_size                            :  3;
     unsigned      read_addr_burst                           :  2;
     unsigned      read_addr_lock                            :  1;
     unsigned      read_addr_cache_lsb                       :  3;
#endif
} ncp_elm_sm_debug_ar_ram_1_r_t;

/*! @struct ncp_elm_sm_debug_ar_ram_2_r_t
 *  @brief ELM System Memory Debug Read Address RAM, Part 2
 *  @details This register contains bits 71:64 of the read address capture
             SRAM at the location indicated by the head pointer.
             If the SRAM is empty (head pointer == tail pointer),
             zeros are returned;otherwise, the data from the SRAM is read
             and the tail pointer is incremented.
             The debug_run bit in the ELM System Memory Debug Control
             Register should be off (0) when reading this RAM;
             otherwise erratic results can occur.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_ar_ram_2_r_t\n
 *   </td>
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
 *     <td width="30%"> @param read_addr_qos </td>
 *     <td width="20%" align="center"> 3 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> The read transaction QOS field. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param read_addr_prot </td>
 *     <td width="20%" align="center"> 4 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> The read transaction protect field. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param read_addr_cache_msb </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The read transaction cache (most signficant bit). </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_ar_ram_2_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 24;
     unsigned      read_addr_qos                             :  3;
     unsigned      read_addr_prot                            :  4;
     unsigned      read_addr_cache_msb                       :  1;
#else    /* Little Endian */
     unsigned      read_addr_cache_msb                       :  1;
     unsigned      read_addr_prot                            :  4;
     unsigned      read_addr_qos                             :  3;
     unsigned      reserved0                                 : 24;
#endif
} ncp_elm_sm_debug_ar_ram_2_r_t;

/*! @struct ncp_elm_sm_debug_r_ram_0_r_t
 *  @brief ELM System Memory Debug Read Response RAM, Part 0
 *  @details This register contains bits 31:0 of the read response capture
             SRAM at the location indicated by the head pointer.
             If the SRAM is empty (head pointer == tail pointer),
             zeros are returned;otherwise, the data from the SRAM is read.
             The debug_run bit in the ELM System Memory Debug Control
             Register should be off (0) when reading this RAM;
             otherwise erratic results can occur.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_r_ram_0_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param read_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The read response data. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_r_ram_0_r_t
 *
 */

typedef struct
{
     unsigned  int                 read_data;
} ncp_elm_sm_debug_r_ram_0_r_t;

/*! @struct ncp_elm_sm_debug_r_ram_1_r_t
 *  @brief ELM System Memory Debug Read Response RAM, Part 1
 *  @details This register contains bits 63:32 of the read response capture
             SRAM at the location indicated by the head pointer.
             If the SRAM is empty (head pointer == tail pointer),
             zeros are returned;otherwise, the data from the SRAM is read.
             The debug_run bit in the ELM System Memory Debug Control
             Register should be off (0) when reading this RAM;
             otherwise erratic results can occur.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_r_ram_1_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param read_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The read response data. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_r_ram_1_r_t
 *
 */

typedef struct
{
     unsigned  int                 read_data;
} ncp_elm_sm_debug_r_ram_1_r_t;

/*! @struct ncp_elm_sm_debug_r_ram_2_r_t
 *  @brief ELM System Memory Debug Read Response RAM, Part 2
 *  @details This register contains bits 95:64 of the read response capture
             SRAM at the location indicated by the head pointer.
             If the SRAM is empty (head pointer == tail pointer),
             zeros are returned;otherwise, the data from the SRAM is read.
             The debug_run bit in the ELM System Memory Debug Control
             Register should be off (0) when reading this RAM;
             otherwise erratic results can occur.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_r_ram_2_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param read_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The read response data. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_r_ram_2_r_t
 *
 */

typedef struct
{
     unsigned  int                 read_data;
} ncp_elm_sm_debug_r_ram_2_r_t;

/*! @struct ncp_elm_sm_debug_r_ram_3_r_t
 *  @brief ELM System Memory Debug Read Response RAM, Part 3
 *  @details This register contains bits 127:96 of the read response capture
             SRAM at the location indicated by the head pointer.
             If the SRAM is empty (head pointer == tail pointer),
             zeros are returned;otherwise, the data from the SRAM is read.
             The debug_run bit in the ELM System Memory Debug Control
             Register should be off (0) when reading this RAM;
             otherwise erratic results can occur.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_r_ram_3_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param read_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The read response data. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_r_ram_3_r_t
 *
 */

typedef struct
{
     unsigned  int                 read_data;
} ncp_elm_sm_debug_r_ram_3_r_t;

/*! @struct ncp_elm_sm_debug_r_ram_4_r_t
 *  @brief ELM System Memory Debug Read Response RAM, Part 4
 *  @details This register contains bits 159:128 of the read response capture
             SRAM at the location indicated by the head pointer.
             If the SRAM is empty (head pointer == tail pointer),
             zeros are returned;otherwise, the data from the SRAM is read.
             The debug_run bit in the ELM System Memory Debug Control
             Register should be off (0) when reading this RAM;
             otherwise erratic results can occur.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_r_ram_4_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param read_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The read response data. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_r_ram_4_r_t
 *
 */

typedef struct
{
     unsigned  int                 read_data;
} ncp_elm_sm_debug_r_ram_4_r_t;

/*! @struct ncp_elm_sm_debug_r_ram_5_r_t
 *  @brief ELM System Memory Debug Read Response RAM, Part 5
 *  @details This register contains bits 191:160 of the read response capture
             SRAM at the location indicated by the head pointer.
             If the SRAM is empty (head pointer == tail pointer),
             zeros are returned;otherwise, the data from the SRAM is read.
             The debug_run bit in the ELM System Memory Debug Control
             Register should be off (0) when reading this RAM;
             otherwise erratic results can occur.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_r_ram_5_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param read_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The read response data. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_r_ram_5_r_t
 *
 */

typedef struct
{
     unsigned  int                 read_data;
} ncp_elm_sm_debug_r_ram_5_r_t;

/*! @struct ncp_elm_sm_debug_r_ram_6_r_t
 *  @brief ELM System Memory Debug Read Response RAM, Part 6
 *  @details This register contains bits 223:192 of the read response capture
             SRAM at the location indicated by the head pointer.
             If the SRAM is empty (head pointer == tail pointer),
             zeros are returned;otherwise, the data from the SRAM is read.
             The debug_run bit in the ELM System Memory Debug Control
             Register should be off (0) when reading this RAM;
             otherwise erratic results can occur.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_r_ram_6_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param read_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The read response data. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_r_ram_6_r_t
 *
 */

typedef struct
{
     unsigned  int                 read_data;
} ncp_elm_sm_debug_r_ram_6_r_t;

/*! @struct ncp_elm_sm_debug_r_ram_7_r_t
 *  @brief ELM System Memory Debug Read Response RAM, Part 7
 *  @details This register contains bits 255:224 of the read response capture
             SRAM at the location indicated by the head pointer.
             If the SRAM is empty (head pointer == tail pointer),
             zeros are returned;otherwise, the data from the SRAM is read.
             The debug_run bit in the ELM System Memory Debug Control
             Register should be off (0) when reading this RAM;
             otherwise erratic results can occur.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_r_ram_7_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param read_data </td>
 *     <td width="20%" align="center"> 32 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The read response data. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_r_ram_7_r_t
 *
 */

typedef struct
{
     unsigned  int                 read_data;
} ncp_elm_sm_debug_r_ram_7_r_t;

/*! @struct ncp_elm_sm_debug_r_ram_8_r_t
 *  @brief ELM System Memory Debug Read Response RAM, Part 8
 *  @details This register contains bits 270:256 of the read data capture
             SRAM at the location indicated by the head pointer.
             If the SRAM is empty (head pointer == tail pointer),
             zeros are returned;otherwise, the data from the SRAM is read
             and the tail pointer is incremented.
             The debug_run bit in the ELM System Memory Debug Control
             Register should be off (0) when reading this RAM;
             otherwise erratic results can occur.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_sm_debug_r_ram_8_r_t\n
 *   </td>
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
 *     <td width="30%"> @param read_data_last </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> The read response last cycle. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param read_resp_code </td>
 *     <td width="20%" align="center"> 2 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> The read response code. </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param read_resp_id </td>
 *     <td width="20%" align="center"> 12 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> The ID of the read response. </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_sm_debug_r_ram_8_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 17;
     unsigned      read_data_last                            :  1;
     unsigned      read_resp_code                            :  2;
     unsigned      read_resp_id                              : 12;
#else    /* Little Endian */
     unsigned      read_resp_id                              : 12;
     unsigned      read_resp_code                            :  2;
     unsigned      read_data_last                            :  1;
     unsigned      reserved0                                 : 17;
#endif
} ncp_elm_sm_debug_r_ram_8_r_t;

/*! @struct ncp_elm_AW_smon01_sbsx_mon_r_t
 *  @brief AW_smon CONTROL1 register
 *  @details This is used to configure the operation of the 2 internal counters in the SMON
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_AW_smon01_sbsx_mon_r_t\n
 *   </td>
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
 *     <td width="30%"> @param mode1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> select input signal for SMON1 engine </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param mode0 </td>
 *     <td width="20%" align="center"> 8 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> select input signal for SMON0 engine </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_AW_smon01_sbsx_mon_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 16;
     unsigned      mode1                                     :  8;
     unsigned      mode0                                     :  8;
#else    /* Little Endian */
     unsigned      mode0                                     :  8;
     unsigned      mode1                                     :  8;
     unsigned      reserved0                                 : 16;
#endif
} ncp_elm_AW_smon01_sbsx_mon_r_t;

/*! @struct ncp_elm_interrupt_status_r_t
 *  @brief Interrupt Status Register
 *  @details This register holds interrupt status
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_interrupt_status_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sbsx_smon </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> The SMON connected to the SBSX interface has issued
 *        an interrupt Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param meminf_write_cam_pop_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> The CAM in the write memory interface has a pop error
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param meminf_write_cam_push_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> The CAM in the write memory interface has a push error
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param meminf_read_cam_pop_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> The CAM in the read memory interface has a pop error
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param meminf_read_cam_push_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> The CAM in the read memory interface has a push error
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wdata_fifo_par_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> A parity error has occurred in the SBSX Write Data
 *        FIFO Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param waddr_fifo_par_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> A parity error has occurred in the SBSX Write Address
 *        FIFO Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rresp_fifo_par_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> A parity error has occurred in the SBSX Read Response
 *        FIFO Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param raddr_fifo_par_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> A parity error has occurred in the SBSX Read Address
 *        FIFO Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zeroization_complete </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> The system memory zeroization has completed. Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zeroization_detected </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> The zeroize signal has been asserted. Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param initialization_complete </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> The system memory initialization has completed. Status </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fifo_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> A FIFO overflow, underflow, or parity error has occurred.
 *        The FIFO status registers must be read to determine
 *        the type of error and in which FIFO the error occurred.
 *        Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sysmem_write_resp_3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> A write operation to the system memory resulted in
 *        a write response code of 3. Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sysmem_write_resp_2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> A write operation to the system memory resulted in
 *        a write response code of 2. Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sysmem_write_resp_1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> A write operation to the system memory resulted in
 *        a write response code of 1. Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sysmem_read_resp_3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> A read operation to the system memory resulted in
 *        a read response code of 3. Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sysmem_read_resp_2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> A read operation to the system memory resulted in
 *        a read response code of 2. Status
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sysmem_read_resp_1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> A read operation to the system memory resulted in
 *        a read response code of 1. Status
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_interrupt_status_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 13;
     unsigned      sbsx_smon                                 :  1;
     unsigned      meminf_write_cam_pop_error                :  1;
     unsigned      meminf_write_cam_push_error               :  1;
     unsigned      meminf_read_cam_pop_error                 :  1;
     unsigned      meminf_read_cam_push_error                :  1;
     unsigned      wdata_fifo_par_error                      :  1;
     unsigned      waddr_fifo_par_error                      :  1;
     unsigned      rresp_fifo_par_error                      :  1;
     unsigned      raddr_fifo_par_error                      :  1;
     unsigned      zeroization_complete                      :  1;
     unsigned      zeroization_detected                      :  1;
     unsigned      initialization_complete                   :  1;
     unsigned      fifo_error                                :  1;
     unsigned      sysmem_write_resp_3                       :  1;
     unsigned      sysmem_write_resp_2                       :  1;
     unsigned      sysmem_write_resp_1                       :  1;
     unsigned      sysmem_read_resp_3                        :  1;
     unsigned      sysmem_read_resp_2                        :  1;
     unsigned      sysmem_read_resp_1                        :  1;
#else    /* Little Endian */
     unsigned      sysmem_read_resp_1                        :  1;
     unsigned      sysmem_read_resp_2                        :  1;
     unsigned      sysmem_read_resp_3                        :  1;
     unsigned      sysmem_write_resp_1                       :  1;
     unsigned      sysmem_write_resp_2                       :  1;
     unsigned      sysmem_write_resp_3                       :  1;
     unsigned      fifo_error                                :  1;
     unsigned      initialization_complete                   :  1;
     unsigned      zeroization_detected                      :  1;
     unsigned      zeroization_complete                      :  1;
     unsigned      raddr_fifo_par_error                      :  1;
     unsigned      rresp_fifo_par_error                      :  1;
     unsigned      waddr_fifo_par_error                      :  1;
     unsigned      wdata_fifo_par_error                      :  1;
     unsigned      meminf_read_cam_push_error                :  1;
     unsigned      meminf_read_cam_pop_error                 :  1;
     unsigned      meminf_write_cam_push_error               :  1;
     unsigned      meminf_write_cam_pop_error                :  1;
     unsigned      sbsx_smon                                 :  1;
     unsigned      reserved0                                 : 13;
#endif
} ncp_elm_interrupt_status_r_t;

/*! @struct ncp_elm_interrupt_en_r_t
 *  @brief Interrupt Enable Register
 *  @details This register enables interrupts
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_interrupt_en_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sbsx_smon </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> The SMON connected to the SBSX interface has issued
 *        an interrupt Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param meminf_write_cam_pop_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> The CAM in the write memory interface has a pop error
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param meminf_write_cam_push_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> The CAM in the write memory interface has a push error
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param meminf_read_cam_pop_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> The CAM in the read memory interface has a pop error
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param meminf_read_cam_push_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> The CAM in the read memory interface has a push error
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wdata_fifo_par_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> A parity error has occurred in the SBSX Write Data
 *        FIFO Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param waddr_fifo_par_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> A parity error has occurred in the SBSX Write Address
 *        FIFO Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rresp_fifo_par_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> A parity error has occurred in the SBSX Read Response
 *        FIFO Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param raddr_fifo_par_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> A parity error has occurred in the SBSX Read Address
 *        FIFO Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zeroization_complete </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> The system memory zeroization has completed. Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zeroization_detected </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> The zeroize signal has been asserted. Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param initialization_complete </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> The system memory initialization has completed. Enable </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fifo_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> A FIFO overflow, underflow, or parity error has occurred.
 *        The FIFO status registers must be read to determine
 *        the type of error and in which FIFO the error occurred.
 *        Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sysmem_write_resp_3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> A write operation to the system memory resulted in
 *        a write response code of 3. Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sysmem_write_resp_2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> A write operation to the system memory resulted in
 *        a write response code of 2. Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sysmem_write_resp_1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> A write operation to the system memory resulted in
 *        a write response code of 1. Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sysmem_read_resp_3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> A read operation to the system memory resulted in
 *        a read response code of 3. Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sysmem_read_resp_2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> A read operation to the system memory resulted in
 *        a read response code of 2. Enable
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sysmem_read_resp_1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> A read operation to the system memory resulted in
 *        a read response code of 1. Enable
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_interrupt_en_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 13;
     unsigned      sbsx_smon                                 :  1;
     unsigned      meminf_write_cam_pop_error                :  1;
     unsigned      meminf_write_cam_push_error               :  1;
     unsigned      meminf_read_cam_pop_error                 :  1;
     unsigned      meminf_read_cam_push_error                :  1;
     unsigned      wdata_fifo_par_error                      :  1;
     unsigned      waddr_fifo_par_error                      :  1;
     unsigned      rresp_fifo_par_error                      :  1;
     unsigned      raddr_fifo_par_error                      :  1;
     unsigned      zeroization_complete                      :  1;
     unsigned      zeroization_detected                      :  1;
     unsigned      initialization_complete                   :  1;
     unsigned      fifo_error                                :  1;
     unsigned      sysmem_write_resp_3                       :  1;
     unsigned      sysmem_write_resp_2                       :  1;
     unsigned      sysmem_write_resp_1                       :  1;
     unsigned      sysmem_read_resp_3                        :  1;
     unsigned      sysmem_read_resp_2                        :  1;
     unsigned      sysmem_read_resp_1                        :  1;
#else    /* Little Endian */
     unsigned      sysmem_read_resp_1                        :  1;
     unsigned      sysmem_read_resp_2                        :  1;
     unsigned      sysmem_read_resp_3                        :  1;
     unsigned      sysmem_write_resp_1                       :  1;
     unsigned      sysmem_write_resp_2                       :  1;
     unsigned      sysmem_write_resp_3                       :  1;
     unsigned      fifo_error                                :  1;
     unsigned      initialization_complete                   :  1;
     unsigned      zeroization_detected                      :  1;
     unsigned      zeroization_complete                      :  1;
     unsigned      raddr_fifo_par_error                      :  1;
     unsigned      rresp_fifo_par_error                      :  1;
     unsigned      waddr_fifo_par_error                      :  1;
     unsigned      wdata_fifo_par_error                      :  1;
     unsigned      meminf_read_cam_push_error                :  1;
     unsigned      meminf_read_cam_pop_error                 :  1;
     unsigned      meminf_write_cam_push_error               :  1;
     unsigned      meminf_write_cam_pop_error                :  1;
     unsigned      sbsx_smon                                 :  1;
     unsigned      reserved0                                 : 13;
#endif
} ncp_elm_interrupt_en_r_t;

/*! @struct ncp_elm_interrupt_force_r_t
 *  @brief Interrupt Force Register
 *  @details This address is an alias for the Interrupt Status register
		that allows normal CFG writes (as opposed to the Clear-On-Write-One
		behavior if the Interrupt Status register address is used).  This
		allows CFG to set interrupt bits for testing purposes.  Reading this
		address returns the current value of the Interrupt Status Register.
 *  <table width="70%" align="center">
 *  <tr>
 *   <td colspan="4" align="center">
 *    struct ncp_elm_interrupt_force_r_t\n
 *   </td>
 *  </tr>
 *  <tr>
 *     <td width="30%"><b> Name </b></td>
 *     <td width="20%" align="center"><b> Width </b></td>
 *     <td width="20%" align="center"><b> Start Offset </b></td>
 *     <td width="30%"><b> Description </b></td>
 *  </tr>
 *   <tr>
 *     <td width="30%"> @param reserved0 </td>
 *     <td width="20%" align="center"> 13 </td>
 *     <td width="20%" align="center"> 19 </td>
 *   <td width="30%"> Reserved for future use </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sbsx_smon </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 18 </td>
 *   <td width="30%"> The SMON connected to the SBSX interface has issued
 *        an interrupt Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param meminf_write_cam_pop_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 17 </td>
 *   <td width="30%"> The CAM in the write memory interface has a pop error
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param meminf_write_cam_push_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 16 </td>
 *   <td width="30%"> The CAM in the write memory interface has a push error
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param meminf_read_cam_pop_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 15 </td>
 *   <td width="30%"> The CAM in the read memory interface has a pop error
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param meminf_read_cam_push_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 14 </td>
 *   <td width="30%"> The CAM in the read memory interface has a push error
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param wdata_fifo_par_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 13 </td>
 *   <td width="30%"> A parity error has occurred in the SBSX Write Data
 *        FIFO Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param waddr_fifo_par_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 12 </td>
 *   <td width="30%"> A parity error has occurred in the SBSX Write Address
 *        FIFO Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param rresp_fifo_par_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 11 </td>
 *   <td width="30%"> A parity error has occurred in the SBSX Read Response
 *        FIFO Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param raddr_fifo_par_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 10 </td>
 *   <td width="30%"> A parity error has occurred in the SBSX Read Address
 *        FIFO Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zeroization_complete </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 9 </td>
 *   <td width="30%"> The system memory zeroization has completed. Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param zeroization_detected </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 8 </td>
 *   <td width="30%"> The zeroize signal has been asserted. Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param initialization_complete </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 7 </td>
 *   <td width="30%"> The system memory initialization has completed. Force </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param fifo_error </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 6 </td>
 *   <td width="30%"> A FIFO overflow, underflow, or parity error has occurred.
 *        The FIFO status registers must be read to determine
 *        the type of error and in which FIFO the error occurred.
 *        Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sysmem_write_resp_3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 5 </td>
 *   <td width="30%"> A write operation to the system memory resulted in
 *        a write response code of 3. Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sysmem_write_resp_2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 4 </td>
 *   <td width="30%"> A write operation to the system memory resulted in
 *        a write response code of 2. Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sysmem_write_resp_1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 3 </td>
 *   <td width="30%"> A write operation to the system memory resulted in
 *        a write response code of 1. Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sysmem_read_resp_3 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 2 </td>
 *   <td width="30%"> A read operation to the system memory resulted in
 *        a read response code of 3. Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sysmem_read_resp_2 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *   <td width="30%"> A read operation to the system memory resulted in
 *        a read response code of 2. Force
 *   </td>
 * </tr>
 *   <tr>
 *     <td width="30%"> @param sysmem_read_resp_1 </td>
 *     <td width="20%" align="center"> 1 </td>
 *     <td width="20%" align="center"> 0 </td>
 *   <td width="30%"> A read operation to the system memory resulted in
 *        a read response code of 1. Force
 *   </td>
 * </tr>
 * </table>
 * Applies to: 5500 --> ncp_elm_interrupt_force_r_t
 *
 */

typedef struct
{
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 : 13;
     unsigned      sbsx_smon                                 :  1;
     unsigned      meminf_write_cam_pop_error                :  1;
     unsigned      meminf_write_cam_push_error               :  1;
     unsigned      meminf_read_cam_pop_error                 :  1;
     unsigned      meminf_read_cam_push_error                :  1;
     unsigned      wdata_fifo_par_error                      :  1;
     unsigned      waddr_fifo_par_error                      :  1;
     unsigned      rresp_fifo_par_error                      :  1;
     unsigned      raddr_fifo_par_error                      :  1;
     unsigned      zeroization_complete                      :  1;
     unsigned      zeroization_detected                      :  1;
     unsigned      initialization_complete                   :  1;
     unsigned      fifo_error                                :  1;
     unsigned      sysmem_write_resp_3                       :  1;
     unsigned      sysmem_write_resp_2                       :  1;
     unsigned      sysmem_write_resp_1                       :  1;
     unsigned      sysmem_read_resp_3                        :  1;
     unsigned      sysmem_read_resp_2                        :  1;
     unsigned      sysmem_read_resp_1                        :  1;
#else    /* Little Endian */
     unsigned      sysmem_read_resp_1                        :  1;
     unsigned      sysmem_read_resp_2                        :  1;
     unsigned      sysmem_read_resp_3                        :  1;
     unsigned      sysmem_write_resp_1                       :  1;
     unsigned      sysmem_write_resp_2                       :  1;
     unsigned      sysmem_write_resp_3                       :  1;
     unsigned      fifo_error                                :  1;
     unsigned      initialization_complete                   :  1;
     unsigned      zeroization_detected                      :  1;
     unsigned      zeroization_complete                      :  1;
     unsigned      raddr_fifo_par_error                      :  1;
     unsigned      rresp_fifo_par_error                      :  1;
     unsigned      waddr_fifo_par_error                      :  1;
     unsigned      wdata_fifo_par_error                      :  1;
     unsigned      meminf_read_cam_push_error                :  1;
     unsigned      meminf_read_cam_pop_error                 :  1;
     unsigned      meminf_write_cam_push_error               :  1;
     unsigned      meminf_write_cam_pop_error                :  1;
     unsigned      sbsx_smon                                 :  1;
     unsigned      reserved0                                 : 13;
#endif
} ncp_elm_interrupt_force_r_t;

#ifdef __cplusplus
}
#endif

#endif /* _NCP_ELM_REGS_H_ */
