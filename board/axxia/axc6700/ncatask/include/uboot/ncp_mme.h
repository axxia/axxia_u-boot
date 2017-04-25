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
 *************************************************************************/


/*! @file      ncp_mme.h
 *  @brief     Memory Management Engine
 * 
 *  @addtogroup _mme_ Memory Management Engine
 *
 *  @{
 */

#ifndef __NCP_MME_H__
#define __NCP_MME_H__

#define NCP_MME_MEM_POOL_BLOCK_SIZES 4

typedef struct ncp_mme_fixed_pool_s ncp_mme_fixed_pool_t;
typedef struct ncp_mme_mem_pool_s ncp_mme_mem_pool_t;

/*!
 * @brief Data structure for MME memory pool information, used by
 *        ncp_mme_mem_pool_config_get()
 */
struct ncp_mme_mem_pool_s
{
    /*!
     * @brief Memory pool virtual base address
     */
    ncp_int64_t poolVirtBase NCP_COMPAT_ALIGN64;
    /*!
     * @brief Memory pool physical base address
     */
    ncp_int64_t poolPhysBase NCP_COMPAT_ALIGN64;
    /*!
     * @brief Memory pool total size, in bytes
     */
    ncp_int64_t totalSize NCP_COMPAT_ALIGN64;
    /*!
     * @brief Memory pool virtual base address for each block size. 0: 64KB, 1: 16KB, 2: 2KB, 3: 256B
     */
    ncp_int64_t virtBase[NCP_MME_MEM_POOL_BLOCK_SIZES] NCP_COMPAT_ALIGN64;
    /*!
     * @brief Memory pool physical base address for each block size. 0: 64KB, 1: 16KB, 2: 2KB, 3: 256B
     */
    ncp_int64_t physBase[NCP_MME_MEM_POOL_BLOCK_SIZES] NCP_COMPAT_ALIGN64;
    /*!
     * @brief Memory pool number of blocks for each block size. 0: 64KB, 1: 16KB, 2: 2KB, 3: 256B
     */
    ncp_uint32_t numBlocks[NCP_MME_MEM_POOL_BLOCK_SIZES];
    /*!
     * @brief Memory pool number of reserve blocks for each block size (valid for CPU pools only). 0: 64KB, 1: 16KB, 2: 2KB, 3: 256B
     */
    ncp_uint32_t numReserveBlocks[NCP_MME_MEM_POOL_BLOCK_SIZES]; /* CpuPool only */
    /*!
     * @brief Memory pool block sizes
     */
    ncp_uint32_t blockSize[NCP_MME_MEM_POOL_BLOCK_SIZES];
    /*!
     * @brief Memory pool name
     */
    char         name[NCP_TASK_MAX_RESOURCE_NAME_LEN];
    /*!
     * @brief Memory pool valid
     */
    ncp_bool_t valid;
} NCP_COMPAT_PACKED;

struct ncp_mme_fixed_pool_s
{
    /*!
     * @brief Fixed pool ID
     */
    int id;
    /*!
     * @brief Size of buffer, in bytes
     */
    ncp_int64_t bufferSize NCP_COMPAT_ALIGN64;
    /*!
     * @brief Size of L3 cache locked portion of fixed pool, in bytes
     */
    ncp_int64_t l3LockedSize NCP_COMPAT_ALIGN64;
    /*!
     * @brief Size of write-back portion of fixed pool, in bytes
     */
    ncp_int64_t writeBackSize NCP_COMPAT_ALIGN64;
   /*!
     * @brief Size of application portion of fixed pool, in bytes
     */
    ncp_int64_t applicationSize NCP_COMPAT_ALIGN64;

    /*!
     * @brief Total size of fixed pool, in bytes
     */
    ncp_int64_t totalSize NCP_COMPAT_ALIGN64;

   /*!
     * @brief Application start address
     */
    ncp_int64_t applicationMemoryStartOffset NCP_COMPAT_ALIGN64;

    /*!
     * @brief Fixed pool virtual base address
     */
    ncp_int64_t virtualBaseAddress NCP_COMPAT_ALIGN64;
    /*!
     * @brief Fixed pool physical base address
     */
    ncp_int64_t physicalBaseAddress NCP_COMPAT_ALIGN64;

    /*!
     * @brief Fixed pool last allocated address
     *
     */
    ncp_int64_t lastAllocatedOffset NCP_COMPAT_ALIGN64;
 
    /*!
     * @brief Fixed pool name
     */
    char         name[NCP_TASK_MAX_RESOURCE_NAME_LEN];
    /*!
     * @brief Fixed pool valid
     */
    ncp_bool_t valid;
} NCP_COMPAT_PACKED;

/*! @fn ncp_st_t ncp_mme_mpcq_poke(ncp_hdl_t ncpHdl, ncp_uint32_t mpcqId)
    @brief Request more valid mPCQ entries from the MME.
    @param ncpHdl Incoming handle of the current NCP device
    @param mpcqId Id of the mPCQ to poke
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_MME_INVALID_HANDLE The MME module was not properly configured
    @retval NCP_ST_MME_INVALID_MPCQ_ID The specified mPCQ is not valid
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t ncp_mme_mpcq_poke(ncp_hdl_t ncpHdl,
                                   ncp_uint32_t mpcqId);

/*! @fn ncp_st_t ncp_mme_mpcq_polling_interval_get(ncp_hdl_t ncpHdl, ncp_uint32_t *cycles)
    @brief Query the MME mPCQ read pointer polling interval.
    @param ncpHdl Incoming handle of the current NCP device
    @param cycles Returned number of cycles between mPCQ read pointer polls
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_MME_INVALID_HANDLE The MME module was not properly configured
    @retval NCP_ST_DEV_INVALID_BUFFER cycles is not a valid buffer
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t ncp_mme_mpcq_polling_interval_get(ncp_hdl_t ncpHdl,
                                                   ncp_uint32_t *cycles);

/*! @fn ncp_st_t ncp_mme_mpcq_polling_interval_set(ncp_hdl_t ncpHdl, ncp_uint32_t cycles)
    @brief Set the MME mPCQ read pointer polling interval.
    @param ncpHdl Incoming handle of the current NCP device
    @param cycles Number of cycles between mPCQ read pointer polls (range 0 - 255)
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_MME_INVALID_HANDLE The MME module was not properly configured
    @retval NCP_ST_INVALID_VALUE cycles is not a valid value
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t ncp_mme_mpcq_polling_interval_set(ncp_hdl_t ncpHdl,
                                                   ncp_uint32_t cycles);


/*! @fn ncp_st_t ncp_mme_available_blocks_get(ncp_hdl_t ncpHdl, ncp_uint32_t poolId, ncp_uint32_t blockSize, ncp_uint32_t *numBlocks)
    @brief Query the number of available blocks for a specified pool and block size
    @param ncpHdl Incoming handle of the current NCP device
    @param poolId Id of the pool to query
    @param blockSize Block size to query
    @param numBlocks Returned number of available blocks
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_MME_INVALID_HANDLE The MME module was not properly configured
    @retval NCP_ST_MME_INVALID_POOL_ID The specified poolId is not valid
    @retval NCP_ST_MME_INVALID_BLOCK_SIZE The specified blockSize is not valid
    @retval NCP_ST_DEV_INVALID_BUFFER numBlocks is not a valid buffer
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t ncp_mme_available_blocks_get(ncp_hdl_t ncpHdl,
                                              ncp_uint32_t poolId,
                                              ncp_uint32_t blockSize,
                                              ncp_uint32_t *numBlocks);

/*! @fn ncp_st_t ncp_mme_pool_flush(ncp_hdl_t ncpHdl, ncp_uint32_t poolId);
    @brief Flush an MME pool, returning it to its original state.
    @param ncpHdl Incoming handle of the current NCP device
    @param poolId Id of the pool to flush
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_MME_INVALID_HANDLE The MME module was not properly configured
    @retval NCP_ST_MME_INVALID_POOL_ID The specified poolId is not valid
    @retval NCP_ST_MME_FLUSH_MPCQ_NOT_STOPPED Activity for an mPCQ associated with the pool could not be stopped
    @retval NCP_ST_MME_FLUSH_MREF_NOT_STOPPED mREF activity for the pool could not be stopped
    @retval NCP_ST_MME_FLUSH_IFLS_NOT_STOPPED IFLS activity for the pool could not be stopped
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t ncp_mme_pool_flush(ncp_hdl_t ncpHdl,
                                    ncp_uint32_t poolId);

/*! @fn ncp_st_t ncp_mme_mem_pool_config_get(ncp_hdl_t ncpHdl, ncp_uint32_t poolId, ncp_mme_mem_pool_t *mmePoolInfo)
    @brief Retrieve MME memory pool configuration info
    @param ncpHdl Incoming handle of the current NCP device
    @param poolId Incoming pool ID, for which configuration
                  information is requested
    @param mmePoolInfo Outgoing ncp_mme_mem_pool_t struct, populated
                       with configuration information
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_MME_INVALID_HANDLE The MME module was not properly configured
    @retval NCP_ST_MME_INVALID_POOL_ID The specified poolId is not valid
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API
ncp_st_t ncp_mme_mem_pool_config_get(ncp_hdl_t ncpHdl, ncp_uint32_t poolId, ncp_mme_mem_pool_t *mmeMemPoolInfo);

/*! @fn ncp_st_t ncp_mme_fixed_pool_config_get(ncp_hdl_t ncpHdl, ncp_uint32_t poolId, ncp_mme_fixed_pool_t *mmeFixedPoolInfo)
    @brief Retrieve MME fixed pool configuration info
    @param ncpHdl Incoming handle of the current NCP device
    @param poolId Incoming fixed pool ID, for which configuration
                  information is requested
    @param mmePoolInfo Outgoing ncp_mme_fixed_pool_t struct,
                       populated with configuration information
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_MME_INVALID_HANDLE The MME module was not properly configured
    @retval NCP_ST_MME_INVALID_POOL_ID The specified poolId is not valid
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API
ncp_st_t ncp_mme_fixed_pool_config_get(ncp_hdl_t ncpHdl, ncp_uint32_t poolId, ncp_mme_fixed_pool_t *mmeFixedPoolInfo);

/*! @fn ncp_st_t ncp_mme_refcnt_get(
            ncp_hdl_t ncpHdl,
            void         *buffer,
            ncp_uint32_t *refCnt)
    @brief Retrieve reference count of the given shared pool buffer.
    @note  Do not use this function unless you are very familiar with the
            details of hardware reference count management. This function
            returns the value of the reference count in memory which, due to
            hardware optimizations, may not match the *actual* reference count
            of the buffer.

           For example, the MME has an optimization to prevent unnecessary
           memory writes, so that when a buffer is freed its reference count is
           unchanged. For example, if an engine requests the MME to decrement
           buffer X's reference count by 3, and the current value is 3, the MME
           will simply free X and leave its reference count at 3.  A free and
           a singly-referenced buffer can have *any* value as its reference
           count, not just 0.

    @param[in]  ncpHdl Incoming handle of the current NCP device
    @param[in]  buffer Shared pool buffer address
    @param[out] refCnt Outgoing 32-bit unsigned integer,
                       populated with the reference count.
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_MME_INVALID_HANDLE The MME module was not properly configured
    @retval NCP_ST_MME_INVALID_POOL_ID The specified poolId is not valid
    @retval NCP_ST_INVALID_PARAMETER The buffer is not a shared pool buffer.
    @retval NCP_ST_NOT_IMPLEMENTED This function is only supported on the XLF
                device. The RTE returns this error when this function is called
                on another device.
    @retval NCP_ST_* Lower level NCP device access error codes
*/

NCP_API
ncp_st_t
ncp_mme_refcnt_get(
    ncp_hdl_t     ncpHdl,
    void         *buffer,
    ncp_uint32_t *refCnt);

/*
 *  @}
 */

#endif /* __NCP_MME_H__ */
