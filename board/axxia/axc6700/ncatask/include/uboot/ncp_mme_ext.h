/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


#include "uboot/ncp_mme_pvt.h"

#ifndef __NCP_MME_EXT_H__
#define __NCP_MME_EXT_H__
typedef struct ncp_mme_fixed_pool_int_s ncp_mme_fixed_pool_int_t;
typedef struct ncp_mme_pool_s ncp_mme_pool_t;
typedef struct ncp_mme_mpcq_s ncp_mme_mpcq_t;
typedef struct ncp_mme_mpcq_s ncp_mme_shared_pool_allocator_t;
typedef struct ncp_mme_s ncp_mme_t;


typedef struct ncp_mme_fixpool_Node_t
{
	ncp_uint64_t 	strtAddr;
	ncp_uint64_t	size;
       	struct  ncp_mme_fixpool_Node_t *next;
        struct ncp_mme_fixpool_Node_t *prev;
	/* [direction][blkId]
	 RIF-0, index-0, RIF-1, index-1, ERIF-0, index-2
	ERIF-1, index-3 and APPLICATION-index-4 */
	ncp_uint32_t	blkUseCnt[2][5];
} ncp_mme_fixpool_node_t;


struct ncp_mme_fixed_pool_int_s
{
    int id;
    ncp_int64_t bufferSize NCP_COMPAT_ALIGN64;
    ncp_int64_t l3LockedSize NCP_COMPAT_ALIGN64;
    ncp_int64_t writeBackSize NCP_COMPAT_ALIGN64;
    ncp_int64_t applicationSize NCP_COMPAT_ALIGN64;
    ncp_int64_t applicationMemoryStartOffset NCP_COMPAT_ALIGN64;
    ncp_int64_t totalSize NCP_COMPAT_ALIGN64;
    ncp_int64_t virtualBaseAddress NCP_COMPAT_ALIGN64;
    ncp_int64_t physicalBaseAddress NCP_COMPAT_ALIGN64;
    ncp_int64_t lastAllocatedOffset NCP_COMPAT_ALIGN64;
    ncp_mutex_t	fixpoolMemLock;
    NCP_DECLARE_POINTER(ncp_mme_fixpool_node_t, freeListHeadPtr);
    NCP_DECLARE_POINTER(ncp_mme_fixpool_node_t, usedListHeadPtr);
    ncp_mutex_t	fixpoolL3LockedMemLock;
    NCP_DECLARE_POINTER(ncp_mme_fixpool_node_t, freeListL3LockedHeadPtr);
    NCP_DECLARE_POINTER(ncp_mme_fixpool_node_t, usedListL3LockedHeadPtr);

    char         name[NCP_TASK_MAX_RESOURCE_NAME_LEN];
    ncp_bool_t valid;
} NCP_COMPAT_PACKED;

struct ncp_mme_pool_s
{
    ncp_int64_t mrefSize NCP_COMPAT_ALIGN64;
    ncp_int64_t mrefBase NCP_COMPAT_ALIGN64;
    ncp_int64_t flsSize NCP_COMPAT_ALIGN64;
    ncp_int64_t flsBase NCP_COMPAT_ALIGN64;
    ncp_int64_t poolVirtBase NCP_COMPAT_ALIGN64;
    ncp_int64_t poolPhysBase NCP_COMPAT_ALIGN64;
    ncp_int64_t poolSize NCP_COMPAT_ALIGN64;
    ncp_int64_t maxDynamic NCP_COMPAT_ALIGN64;
    ncp_int64_t virtBase[NCP_MME_POOL_BLOCK_SIZES] NCP_COMPAT_ALIGN64;
    ncp_int64_t physBase[NCP_MME_POOL_BLOCK_SIZES] NCP_COMPAT_ALIGN64;
    ncp_uint32_t numBlocks[NCP_MME_POOL_BLOCK_SIZES];
    ncp_uint32_t numReserveBlocks[NCP_MME_POOL_BLOCK_SIZES]; /* CpuPool only */
    ncp_uint32_t blockSize[NCP_MME_POOL_BLOCK_SIZES];
    char         name[NCP_TASK_MAX_RESOURCE_NAME_LEN];
    ncp_bool_t valid;
} NCP_COMPAT_PACKED;

struct ncp_mme_mpcq_s
{
    ncp_bool_t valid;
    ncp_int32_t id;
    ncp_uint32_t pool;
    ncp_uint64_t size;
    ncp_uint64_t baseAddr[NCP_MME_MPCQ_BLOCK_SIZES];
    ncp_uint32_t numEntries[NCP_MME_MPCQ_BLOCK_SIZES];
    ncp_uint32_t queueThreshold[NCP_MME_MPCQ_BLOCK_SIZES];
    ncp_bool_t queueThresholds;
    ncp_uint32_t entrySize[NCP_MME_MPCQ_BLOCK_SIZES];
    ncp_uint64_t readPtrBaseAddress[NCP_MME_MPCQ_BLOCK_SIZES];
};

typedef struct {
    ncp_int64_t size;
    ncp_int64_t virtualBase;
    ncp_int64_t physicalBase;
    char        name[NCP_TASK_MAX_RESOURCE_NAME_LEN];
} ncp_mme_sdr_t;

struct ncp_mme_s
{
    ncp_uint32_t cookie;
    ncp_uint32_t id;
    ncp_uint8_t  version;
    ncp_hdl_t ncpHdl;
    ncp_mutex_t lock;
    ncp_int64_t pool0ExtStaticSize;
    ncp_int64_t pool0TotalStaticSize;
    ncp_mme_pool_t mmePool[NCP_MME_MAX_POOL_ID + 1];
    ncp_mme_mpcq_t mmeMPCQ[NCP_MME_MAX_MPCQ_ID + 1];
    ncp_uint32_t   numSharedDataRegions;
    ncp_mme_sdr_t *sharedDataRegions;
    ncp_mme_fixed_pool_int_t mmeFixedPool;
    ncp_bool_t     lockActive;
};

typedef enum
{
    NCP_MME_CAT_SAVE_BASE_ADDR,
    NCP_MME_CAT_SAVE_NUM_BLOCKS,
    NCP_MME_CAT_SAVE_ALL,            /* Display all preceding elements */
} ncp_mme_cat_save_t;

/* Inter-module APIs */

/*! @fn ncp_st_t ncp_mme_mpcq_config_get(ncp_hdl_t ncpHdl, ncp_mme_mpcq_t **mmeMpcqInfo)
    @brief Retrieve MME mPCQ configuration info
    @param ncp Incoming handle of the current NCP device
    @param mmeMpcqInfo Pointer to the ncp_mme_mpcq_t array in the MME handle
*/
NCP_API
ncp_st_t ncp_mme_mpcq_config_get(ncp_hdl_t ncpHdl, ncp_mme_mpcq_t **mmeMpcqInfo);

/*! @fn ncp_st_t ncp_mme_pool_config_get(ncp_hdl_t ncpHdl, ncp_mme_pool_t **mmePoolInfo)
    @brief Retrieve MME pool configuration info
    @param ncp Incoming handle of the current NCP device
    @param mmePoolInfo Pointer to the ncp_mme_pool_t array in the MME handle
*/
NCP_API
ncp_st_t ncp_mme_pool_config_get(ncp_hdl_t ncpHdl, ncp_mme_pool_t **mmePoolInfo);

/*! @fn ncp_st_t ncp_mme_shared_data_regions_get(
        ncp_hdl_t       ncpHdl,
        ncp_uint32_t   *numSharedDataRegions,
        ncp_mme_sdr_t **sharedDataRegions)
    @brief Retrieve shared data region configuration info
    @param ncp Incoming handle of the current NCP device
    @param numSharedDataRegions Number of configured shared data regions
    @param sharedDataRegions Pointer to the ncp_mme_sdr_t array in the MME hdl 
*/
NCP_API ncp_st_t
ncp_mme_shared_data_regions_get(
    ncp_hdl_t ncpHdl,
    ncp_uint32_t *numSharedDataRegions,
    ncp_mme_sdr_t **sharedDataRegions);

/*! @fn ncp_st_t ncp_mme_cat_size(ncp_hdl_t ncpHdl, ncp_uint32_t *catSize)
    @brief Retrieve the size in bytes required for MME CAT data
    @param ncpHdl Incoming handle of the current NCP device
    @param catSize Outgoing MME CAT size in bytes
*/
NCP_API ncp_st_t ncp_mme_cat_size(ncp_hdl_t ncpHdl, ncp_uint32_t *catSize);

/*! @fn ncp_st_t ncp_mme_warm_config(ncp_t *ncp);
    @brief Provide MME warm restart functionality
    @param ncpHdl Handle for the NCP that the MME is part of.
*/
NCP_API ncp_st_t ncp_mme_warm_config(ncp_t *ncp);

/*! @fn ncp_st_t ncp_mme_destroy(ncp_t *ncp);
    @brief Release the resources that were allocated to the MME associated
           with the NCP instance.
    @param ncp Handle for the NCP that the MME is part of.
*/
NCP_API ncp_st_t ncp_mme_destroy(ncp_t *ncp);

#if !defined(NCP_KERNEL)

/*! @fn ncp_st_t ncp_mme_cat_dump_info(ncp_dev_hdl_t devHdl, ncp_mme_cat_save_t iSelect, ncp_uint32_t iNumEntries, ncp_uint32_t iWordsPerEntry, ncp_uint8_t *iBuffer, ncp_uint32_t iFormatRev, FILE *oFile)
    @brief Dump the specified MME CAT data from iBuffer to the file.
    @param devHdl Incoming handle of the current NCP device
    @param iSelect Specifies what portions of data to dump (pool base addresses, pool number of blocks, or both)
    @param iNumEntries The number of entries to dump
    @param iWordsPerEntry The number of words per entry
    @param iBuffer The CAT data to write to the file
    @param iFormatRev The revision number for the MME CAT format
    @param oFile The output file
*/

typedef int FILE;

NCP_API ncp_st_t ncp_mme_cat_dump_info(ncp_dev_hdl_t devHdl,
                               ncp_mme_cat_save_t iSelect,
                               ncp_uint32_t iNumEntries,
                               ncp_uint32_t iWordsPerEntry,
                               ncp_uint8_t *iBuffer,
                               ncp_uint32_t iFormatRev,
                               FILE *oFile);

/*! @fn ncp_st_t ncp_mme_cat_load_info(ncp_hdl_t ncpHdl, ncp_uint32_t wordCount, ncp_uint8_t *oBuffer, ncp_uint32_t *oNumEntries, ncp_uint32_t *oWordsPerEntry, ncp_uint32_t *oFormatRev)
    @brief Write the MME CAT data into oBuffer.
    @param ncpHdl Incoming handle of the current NCP device
    @param wordCount The size of oBuffer, in 32-bit words
    @param oBuffer The buffer the MME CAT data is written to
    @param oNumEntries The number of entries of data
    @param oWordsPerEntry The number of 32-bit words per entry of MME data
    @param oFormatRev The revision number for the MME CAT format
*/
NCP_API ncp_st_t ncp_mme_cat_load_info(ncp_hdl_t ncpHdl,
                               ncp_uint32_t wordCount,
                               ncp_uint8_t *oBuffer,
                               ncp_uint32_t *oNumEntries,
                               ncp_uint32_t *oWordsPerEntry,
                               ncp_uint32_t *oFormatRev);
#endif /* !defined(NCP_KERNEL) */

/*! @fn ncp_st_t ncp_mme_config(ncp_t *ncp, ncp_map_t *map)
    @brief Entry point to handle MME relevant configuration portions
           of an NCP configuration, and perform appropriate hardware
           initialization.
    @param ncp Incoming handle of the current NCP device
    @param map Incoming handle of the configuration image
*/
ncp_st_t ncp_mme_config(ncp_t *ncp, ncp_map_t *map);

ncp_st_t
ncp_mme_config_free(ncp_mme_t *mme);

ncp_st_t
ncp_mme_caal_vat_set(ncp_t *ncp, ncp_uint32_t regionId);

ncp_st_t
ncp_mme_pool_valid_get(ncp_t *ncp, ncp_uint32_t *validPools);

ncp_st_t
ncp_mme_mpcq_poke_by_addr(ncp_hdl_t ncpHdl, ncp_uint64_t baseAddr);

ncp_st_t
ncp_mme_enable_mpcq(ncp_hdl_t ncpHdl,
                           ncp_uint32_t mpcqId);

#endif /* __NCP_MME_EXT_H__ */
