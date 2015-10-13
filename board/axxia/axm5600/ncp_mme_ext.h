/*
*  Copyright (C) 2014 LSI (john.jacques@lsi.com)
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

#include "ncp_mme_pvt.h"

#ifndef __NCP_MME_EXT_H__
#define __NCP_MME_EXT_H__

typedef struct ncp_mme_pool_s ncp_mme_pool_t;
typedef struct ncp_mme_mpcq_s ncp_mme_mpcq_t;
typedef struct ncp_mme_mpcq_s ncp_mme_shared_pool_allocator_t;
typedef struct ncp_mme_s ncp_mme_t;

struct ncp_mme_pool_s
{
ncp_int64_t mrefSize;
ncp_int64_t mrefBase;
ncp_int64_t flsSize;
ncp_int64_t flsBase;
ncp_int64_t poolVirtBase;
ncp_int64_t poolPhysBase;
ncp_int64_t poolSize;
ncp_int64_t maxDynamic;
ncp_int64_t virtBase[NCP_MME_POOL_BLOCK_SIZES];
ncp_int64_t physBase[NCP_MME_POOL_BLOCK_SIZES];
ncp_uint32_t numBlocks[NCP_MME_POOL_BLOCK_SIZES];
ncp_uint32_t numReserveBlocks[NCP_MME_POOL_BLOCK_SIZES]; /* CpuPool only */
ncp_uint32_t blockSize[NCP_MME_POOL_BLOCK_SIZES];
ncp_bool_t valid;
};

struct ncp_mme_mpcq_s
{
ncp_bool_t valid;
ncp_int32_t id;
ncp_uint32_t pool;
ncp_uint64_t size;
ncp_uint64_t baseAddr[NCP_MME_MPCQ_BLOCK_SIZES];
ncp_uint32_t numEntries[NCP_MME_MPCQ_BLOCK_SIZES];
ncp_uint32_t entrySize[NCP_MME_MPCQ_BLOCK_SIZES];
ncp_uint64_t readPtrBaseAddress[NCP_MME_MPCQ_BLOCK_SIZES];
};

struct ncp_mme_s
{
ncp_uint32_t cookie;
ncp_uint32_t id;
ncp_hdl_t ncpHdl;
ncp_sem_t lock;
ncp_int64_t pool0ExtStaticSize;
ncp_int64_t pool0TotalStaticSize;
ncp_mme_pool_t mmePool[NCP_MME_MAX_POOL_ID + 1];
ncp_mme_mpcq_t mmeMPCQ[NCP_MME_MAX_MPCQ_ID + 1];
};

#if 0 /* UBOOT */
typedef enum
{
NCP_MME_CAT_SAVE_BASE_ADDR,
NCP_MME_CAT_SAVE_NUM_BLOCKS,
NCP_MME_CAT_SAVE_ALL,            /* Display all preceding elements */
} ncp_mme_cat_save_t;
#endif

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


#if 0 /* UBOOT */

/*! @fn ncp_st_t ncp_mme_cat_size(ncp_hdl_t ncpHdl, ncp_uint32_t *catSize)
@brief Retrieve the size in bytes required for MME CAT data
@param ncpHdl Incoming handle of the current NCP device
@param catSize Outgoing MME CAT size in bytes
*/
NCP_API ncp_st_t ncp_mme_cat_size(ncp_hdl_t ncpHdl, ncp_uint32_t *catSize);

#if !defined(NCP_KERNEL) || defined(NCP_VXWORKS)

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
#endif/* !defined(NCP_KERNEL) || defined(NCP_VXWORKS) */

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

#endif/* 0 */

#endif/* __NCP_MME_EXT_H__ */
