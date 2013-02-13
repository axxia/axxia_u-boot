/**************************************************************************
 **                                                                        *
 **   LSI Corporation, Inc. CONFIDENTIAL                                   *
 **                                                                        *
 **                       PROPRIETARY NOTE                                 *
 **                                                                        *
 **    This software contains information confidential and proprietary     *
 **    to LSI Corporation Inc.  It shall not be reproduced in whole or in  *
 **    part, or transferred to other documents, or disclosed to third      *
 **    parties, or used for any purpose other than that for which it was   *
 **    obtained, without the prior written consent of LSI Corporation Inc. *
 **    (c) 2008, LSI Corporation Inc.  All rights reserved.                *
 **                                                                        *
 **  ***********************************************************************
 **
 **  ***********************************************************************
 **   File:       $HeadURL: $
 **   Version:    $Revision: $
 **   Date:       $Date: $
 ** **************************************************************************/
 
#ifndef _NCP_H_
#define _NCP_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * @brief NAND and BIR access API status codes.
 */
typedef enum ncp_status_e {
    NCP_SUCCESS,
    NCP_VERSION_MISMATCH,
    NCP_BIOS_INVALID_CMD,
    NCP_BIOS_OPEN_ERROR,
    NCP_BIOS_CALL_ERROR,
    NCP_BIR_INVALID_BIR,
    NCP_BIR_INVALID_PARAM_NAME,
    NCP_BIR_PARAM_NOT_FOUND,
    NCP_BIR_INVALID_BUF,
    NCP_BIR_INVALID_SIZE,
    NCP_BIR_BUF_TOO_SMALL,
    NCP_NAND_BASE_NOT_DEFINED,
    NCP_NAND_INVALID_PARTITION,
    NCP_NAND_PARTITION_NOT_FOUND,
    NCP_NAND_OFFSET_TOO_BIG,
    NCP_NAND_INVALID_BUF,
    NCP_NAND_INVALID_SIZE,
    NCP_NAND_SIZE_TOO_BIG,
    NCP_NAND_HW_READ_FAIL,
    NCP_NAND_HW_WRITE_FAIL,
    NCP_NAND_HW_ERASE_FAIL,
    NCP_UBOOT_INVALID_PARAM_NAME,
    NCP_UBOOT_PARAM_NAME_NOT_FOUND,
    NCP_UBOOT_INVALID_PARAM_VAL,
    NCP_UBOOT_PARAM_VAL_SIZE_TOO_SMALL,
    NCP_UBOOT_INVALID_SIZE,
    NCP_UBOOT_ENV_FULL
} ncp_status_t;

/*!
 * @brief Function to read from NAND partition. 
 * @param[in] partition Name of the NAND partition to read from.
 * @param[in] startOffset The starting offset to read from. It starts from zero 
 *                        thru the size of partition.
 * @param[in,out] buf The buffer where the contents are written to.
 * @param[in] size The size of the buffer. The startOffset + size needs to be <= partition size.
 * @retval NCP_SUCCESS When buf contains the data read from NAND.
 * @retval NCP_VERSION_MISMATCH When NCP_ACCESS_VERSION does not match with in-memory version 
 *         created by uboot.
 * @retval NCP_NAND_INVALID_PARTITION When partition is NULL.
 * @retval NCP_NAND_PARTITION_NOT_FOUND When the partition is not defined.
 * @retval NCP_NAND_OFFSET_TOO_BIG When the startOffset is more then the size of partition.
 * @retval NCP_NAND_INVALID_BUF When buf is NULL.
 * @retval NCP_NAND_INVALID_SIZE When size is zero.
 * @retval NCP_NAND_SIZE_TOO_BIG When startOffset + size is more than partition size.
 * @retval NCP_NAND_HW_READ_FAIL When the read failed in hardware.
 */

ncp_status_t ncp_nand_read(const char *partition, unsigned int startOffset, 
                           char *buf, unsigned int size);

/*!
 * @brief Function to write to NAND partition.
 * @param[in] partition Name of the NAND partition to write to.
 * @param[in] startOffset The starting offset to write to. It starts from zero 
 *                        thru the size of partition.
 * @param[in,out] buf The buffer where the contents are read from.
 * @param[in] size The size of the buffer. The startOffset + size needs to be <= partition size.
 * @retval NCP_SUCCESS When buf contents has been written to NAND.
 * @retval NCP_VERSION_MISMATCH When NCP_ACCESS_VERSION does not match with in-memory version 
 *         created by uboot.
 * @retval NCP_NAND_INVALID_PARTITION When partition is NULL.
 * @retval NCP_NAND_PARTITION_NOT_FOUND When the partition is not defined.
 * @retval NCP_NAND_OFFSET_TOO_BIG When the startOffset is more then the size of partition.
 * @retval NCP_NAND_INVALID_BUF When buf is NULL.
 * @retval NCP_NAND_INVALID_SIZE When size is zero.
 * @retval NCP_NAND_SIZE_TOO_BIG When startOffset + size is more than partition size.
 * @retval NCP_NAND_HW_WRITE_FAIL When the write failed in hardware.
 */

ncp_status_t ncp_nand_write(const char *partition, unsigned int startOffset, 
                            const char *buf, unsigned int size);

/*!
 * @brief Function to erase NAND partition.
 * @param[in] partition Name of the NAND partition to erase.
 * @retval NCP_SUCCESS When buf contents has been written to NAND.
 * @retval NCP_VERSION_MISMATCH When NCP_ACCESS_VERSION does not match with in-memory version 
 *         created by uboot.
 * @retval NCP_NAND_INVALID_PARTITION When partition is NULL.
 * @retval NCP_NAND_PARTITION_NOT_FOUND When the partition is not defined.
 * @retval NCP_NAND_HW_ERASE_FAIL When the write to NAND failed.
 */

ncp_status_t ncp_nand_erase(const char *partition);

/*!
 * @brief Function to get Uboot environment parameter.
 * @param[in] paramName Name of the Uboot environment param. 
 * @param[in,out] paramVal The buffer to store the param value.
 * @param[in] size The size of paramVal buffer. 
 * @retval NCP_SUCCESS When the param is read successfully.
 * @retval NCP_VERSION_MISMATCH When NCP_ACCESS_VERSION does not match with in-memory version 
 *         created by uboot.
 * @retval NCP_UBOOT_INVALID_PARAM_NAME When paramName is NULL.
 * @retval NCP_UBOOT_PARAM_NAME_NOT_FOUND When param name is not found in environment.
 * @retval NCP_UBOOT_INVALID_PARAM_VAL When paramVal is NULL.
 * @retval NCP_UBOOT_PARAM_VAL_SIZE_TOO_SMALL When paramVal size is too small compared to the size
 *         in environment.
 * @retval NCP_UBOOT_INVALID_SIZE When size is zero.
 */

ncp_status_t ncp_uboot_param_get(const char *paramName, char *paramVal, int size);

/*!
 * @brief Function to set Uboot environment parameter.
 * @param[in] paramName Name of the Uboot environment param. 
 * @param[in,out] paramVal The buffer containing the param value to be written.
 * @param[in] size The size of paramVal buffer. 
 * @retval NCP_SUCCESS When buf contents has been written successfully.
 * @retval NCP_VERSION_MISMATCH When NCP_ACCESS_VERSION does not match with in-memory version 
 *         created by uboot.
 * @retval NCP_UBOOT_INVALID_PARAM_NAME When paramName is NULL.
 * @retval NCP_UBOOT_INVALID_PARAM_VAL When paramVal is NULL.
 * @retval NCP_UBOOT_ENV_FULL When there is not enough space in environment to write this param.
 */

ncp_status_t ncp_uboot_param_set(const char *paramName, const char *paramVal);

/*!
 * @brief Function to save Uboot envorinment.
 * @retval NCP_SUCCESS When the Uboot environment is successfully saved.
 * @retval NCP_VERSION_MISMATCH When NCP_ACCESS_VERSION does not match with in-memory version 
 *         created by uboot.
 * @retval NCP_NAND_HW_WRITE_FAIL When the write to NAND failed.
 */

ncp_status_t ncp_uboot_env_save(void);

/*!
 * @brief Function to read parameter value from Boot Info Region (BIR) and return as string.
 * @param[in] paramName Name of the parameter to be read from BIR.
 * @param[in,out] buf The buffer where the parameter value is written to.
 * @param[in] size The size of the buffer.
 * @retval NCP_SUCCESS When buf contains the parameter value read from BIR.
 * @retval NCP_BIR_INVALID_PARAM_NAME When paramName is NULL.
 * @retval NCP_BIR_INVALID_BUF When buf is NULL.
 * @retval NCP_BIR_INVALID_SIZE When size is zero.
 * @retval NCP_BIR_INVALID_BIR When the BIR is not valid for the core that is accessing it.
 * @retval NCP_BIR_PARAM_NOT_FOUND When paramName if not found in BIR.
 * @retval NCP_BIR_BUF_TOO_SMALL When buf size is too small for the value found in BIR.
 */
ncp_status_t ncp_bir_param_get(const char *paramName, char *buf, int size);

#define NCP_BIOS_SERVICE_NAME "ncp_access"

typedef enum ncp_bios_cmd_e
{
    NCP_BIOS_CMD_BIR_PARAM_GET,
    NCP_BIOS_CMD_NAND_READ,
    NCP_BIOS_CMD_NAND_WRITE,
    NCP_BIOS_CMD_NAND_ERASE,
    NCP_BIOS_CMD_UBOOT_PARAM_GET,
    NCP_BIOS_CMD_UBOOT_PARAM_SET,
    NCP_BIOS_CMD_UBOOT_ENV_SAVE
} ncp_bios_cmd_t;

typedef ncp_status_t (* nand_read_fn)(const char *partition, unsigned int startOffset, 
                                      char *buf, unsigned int size);

typedef ncp_status_t (* nand_write_fn)(const char *partition, unsigned int startOffset, 
                                       const char *buf, unsigned int size);

typedef ncp_status_t (* nand_erase_fn)(const char *partition);

typedef ncp_status_t (* uboot_param_get_fn)(const char *paramName, char *paramVal, int size);

typedef ncp_status_t (* uboot_param_set_fn)(const char *paramName, const char *paramVal);

typedef ncp_status_t (* uboot_env_save_fn)(void);

#define NCP_ACCESS_VERSION 1

typedef struct nand_access_st
{
    int version;
    nand_read_fn readFn;
    nand_write_fn writeFn;
    nand_erase_fn eraseFn;
    uboot_param_get_fn paramGetFn;
    uboot_param_set_fn paramSetFn;
    uboot_env_save_fn envSaveFn; 
} nand_access_t;

#ifdef __cplusplus
}
#endif

#endif /* _NCP_H_ */
