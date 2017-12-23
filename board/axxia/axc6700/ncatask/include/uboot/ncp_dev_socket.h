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


/*
 * ncp_dev_socket.h
 *
 * adapatation layer for the NCP simulator socket adaptor
 *
 *
 */

#ifndef _NCP_DEV_SOCKET_H_
#define _NCP_DEV_SOCKET_H_

#ifdef __cplusplus
extern "C" { 
#endif


/* --- Types and Definitions --- */
#define NCP_DEV_BUS_ADAPTOR NCP_DEV_BUS_SOCKET

/* --- Function pointer assignment macros, used by the region map --- */
/* --- Don't forget to add prototype @ ncp_dev_pvt.h:NCP_DEV_IO_PROTOTYPE */
#define  __ncp_dev_direct_read                  ncp_dev_socket_direct_read
#define  __ncp_dev_direct_write                 ncp_dev_socket_direct_write
#define  __ncp_dev_indirect_read                ncp_dev_socket_indirect_read
#define  __ncp_dev_indirect_write               ncp_dev_socket_indirect_write
#define  __ncp_dev_dcr_read                     ncp_dev_socket_direct_read
#define  __ncp_dev_dcr_write                    ncp_dev_socket_direct_write
#define  __ncp_dev_srio_cfg_read                ncp_dev_socket_direct_read
#define  __ncp_dev_srio_cfg_write               ncp_dev_socket_direct_write
/* TODO: what do we do with bus config access? */
#define  __ncp_dev_bus_config_read              ncp_dev_socket_direct_read
#define  __ncp_dev_bus_config_write             ncp_dev_socket_direct_write
#define  __ncp_dev_sysmem_cr_read               ncp_dev_socket_sysmem_read
#define  __ncp_dev_sysmem_cr_write              ncp_dev_socket_sysmem_write
#define  __ncp_dev_sysmem_nic_read              ncp_dev_socket_sysmem_read
#define  __ncp_dev_sysmem_nic_write             ncp_dev_socket_sysmem_write
#define  __ncp_dev_paged_read                   ncp_dev_socket_sysmem_read
#define  __ncp_dev_paged_write                  ncp_dev_socket_sysmem_write
#define  __ncp_dev_paged_cached_read            ncp_dev_socket_sysmem_read
#define  __ncp_dev_paged_cached_write           ncp_dev_socket_sysmem_write
#define  __ncp_dev_coherent_read                ncp_dev_socket_sysmem_read
#define  __ncp_dev_coherent_write               ncp_dev_socket_sysmem_write
#define  __ncp_dev_internal_read                ncp_dev_internal_read
#define  __ncp_dev_internal_write               ncp_dev_internal_write
#define  __ncp_dev_mdio_read                    ncp_dev_mdio_read
#define  __ncp_dev_mdio_write                   ncp_dev_mdio_write
#define  __ncp_dev_i2cprot_read                 ncp_dev_i2cprot_read
#define  __ncp_dev_i2cprot_write                ncp_dev_i2cprot_write
#define  __ncp_dev_ntimc_read                   ncp_dev_socket_indirect_read
#define  __ncp_dev_ntimc_write                  ncp_dev_socket_indirect_write
#define  __ncp_dev_l2_indirect_read             ncp_dev_l2_indirect_read
#define  __ncp_dev_l2_indirect_write            ncp_dev_l2_indirect_write
#define  __ncp_dev_trace_indirect_read          ncp_dev_trace_indirect_read
#define  __ncp_dev_trace_indirect_write         ncp_dev_trace_indirect_write

#define  __ncp_dev_hss_phy_read                 ncp_dev_hss_phy_read
#define  __ncp_dev_hss_phy_write                ncp_dev_hss_phy_write
#define  __ncp_dev_apb2ser_indirect_read        ncp_dev_socket_direct_read
#define  __ncp_dev_apb2ser_indirect_write       ncp_dev_socket_direct_write
#define  __ncp_dev_cdc_paged_read               ncp_dev_socket_direct_read
#define  __ncp_dev_cdc_paged_write              ncp_dev_socket_direct_write



NCP_API ncp_st_t
ncp_dev_socket_open(
    ncp_uint32_t   devNum,          /* IN: Device instance number */
    ncp_uint32_t   flags,           /* IN: Open flags (not used; set to zero) */
    ncp_dev_hdl_t *devHdl);         /* OUT: Return location for NCP handle */

NCP_API ncp_st_t
ncp_dev_socket_close(
    ncp_dev_hdl_t      *devHdl);

NCP_API ncp_st_t
ncp_dev_socket_direct_read(
    ncp_dev_t          *dev,
    ncp_region_io_t    *region,
    ncp_uint64_t        offset,
    ncp_uint32_t       *buffer,
    ncp_uint32_t        count,
    ncp_uint32_t        flags,
    ncp_uint32_t        cmdType,
    ncp_uint32_t        xferWidth);

NCP_API ncp_st_t
ncp_dev_socket_indirect_read(
    ncp_dev_t          *dev,
    ncp_region_io_t    *region,
    ncp_uint64_t        offset,
    ncp_uint32_t       *buffer,
    ncp_uint32_t        count,
    ncp_uint32_t        flags,
    ncp_uint32_t        cmdType,
    ncp_uint32_t        xferWidth);

NCP_API ncp_st_t
ncp_dev_socket_sysmem_read(
    ncp_dev_t          *dev,
    ncp_region_io_t    *region,
    ncp_uint64_t        offset,
    ncp_uint32_t       *buffer,
    ncp_uint32_t        count,
    ncp_uint32_t        flags,
    ncp_uint32_t        cmdType,
    ncp_uint32_t        xferWidth);

NCP_API ncp_st_t
ncp_dev_socket_direct_write(
    ncp_dev_t         *dev,
    ncp_region_io_t   *region,
    ncp_uint64_t       offset,
    ncp_uint32_t      *buffer,
    ncp_uint32_t       count,
    ncp_uint32_t       flags,
    ncp_uint32_t       cmdType,
    ncp_uint32_t       xferWidth);

NCP_API ncp_st_t
ncp_dev_socket_indirect_write(
    ncp_dev_t         *dev,
    ncp_region_io_t   *region,
    ncp_uint64_t       offset,
    ncp_uint32_t      *buffer,
    ncp_uint32_t       count,
    ncp_uint32_t       flags,
    ncp_uint32_t       cmdType,
    ncp_uint32_t       xferWidth);

NCP_API ncp_st_t
ncp_dev_socket_sysmem_write(
    ncp_dev_t         *dev,
    ncp_region_io_t   *region,
    ncp_uint64_t       offset,
    ncp_uint32_t      *buffer,
    ncp_uint32_t       count,
    ncp_uint32_t       flags,
    ncp_uint32_t       cmdType,
    ncp_uint32_t       xferWidth);

#if  (1 == USE_NCAV3)
/* TODO - TWM */
NCP_API ncp_st_t
ncp_dev_socket_output_task_put(
    ncp_dev_t            *dev,
    ncp_uint8_t           nca_oPCQ_id, 
    void                 *pMetaData, 
    void                 *pTaskData,
    ncp_uint32_t          flags);
#else
NCP_API ncp_st_t
ncp_dev_socket_output_task_put(
    ncp_dev_t            *dev,
    ncp_uint8_t           nca_oPCQ_id, 
    ncp_task_send_meta_t *pMetaData, 
    void                 *pTaskData,
    ncp_uint32_t          flags);
#endif    

NCP_API ncp_st_t
ncp_dev_socket_input_task_get(
    ncp_dev_t                *dev,
    ncp_uint8_t               nca_iPCQ_id,
    ncp_uint8_t              *pTemplateId,
    ncp_uint8_t              *pPduDataStart,
#if 0
    ncp_input_task_header_t **pInputHdr,
#else
    void                    **pInputHdr,
#endif
    ncp_bool_t               *pTaskErr,
    ncp_uint32_t              flags);

NCP_API ncp_st_t
ncp_dev_socket_task_completion_put(
    ncp_dev_t                *dev,
    ncp_uint8_t               nca_tPCQ_id,
#if 0
    ncp_task_tPCQ_entry_t    *pTaskCompletionData,
#else
    void                     *pTaskCompletionData,
#endif
    ncp_uint32_t              flags);

#ifdef __cplusplus
}
#endif

#endif /* _NCP_DEV_SOCKET_H_ */
