/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                        *
 **                                                                       *
 **************************************************************************/

#ifndef __NCP_NCAV3_PVT_H__
#define __NCP_NCAV3_PVT_H__

#include "uboot/ncp_task_pvt.h"

/* Intra-module functions */

ncp_st_t
ncp_ncav3_supply_nca_buffers(
    ncp_t *ncp,
    ncp_task_pvt_tqsHdl_data_t *pvtTqsHdl);

ncp_st_t
ncp_ncav3_get_pcq_info(
    ncp_t *ncp,
    ncp_uint32_t tqsId,
    ncp_ncav3_pcq_type_t type,
    ncp_uint8_t opcqIndex,
    ncp_uint8_t poolId,
    ncp_uint8_t bufSizeBits,
    ncp_task_pcq_t *pcq);

ncp_st_t
ncp_ncav3_config_free(
    ncp_ncav3_hdl_t *nca,
    ncp_dev_hdl_t    dev);

ncp_st_t
ncp_ncav3_configure_cpu_pool_addr_convert_ram(
    ncp_dev_hdl_t dev,
    ncp_bool_t uMode);

ncp_st_t
ncp_ncav3_configure_fixed_pool_addr_convert_ram(
    ncp_ncav3_hdl_t *nca,
    ncp_dev_hdl_t dev,
    ncp_bool_t uMode);

ncp_st_t
ncp_ncav3_initialize_cpu_pools(
    ncp_dev_hdl_t dev,
    ncp_bool_t    uMode);

ncp_st_t
ncp_ncav3_map_unscheduled_queues(void);

ncp_st_t
ncp_ncav3_pop_unscheduled_queue_head(
    ncp_dev_hdl_t dev,
    ncp_uint32_t unscheduledQueueId,
    ncp_uint64_t *data);

ncp_st_t
ncp_ncav3_push_unscheduled_queue_tail(
    ncp_dev_hdl_t dev,
    ncp_uint32_t unscheduledQueueId,
    ncp_uint64_t data);

ncp_st_t
ncp_ncav3_get_unscheduled_queue_depth(
    ncp_dev_hdl_t dev,
    ncp_uint32_t  unscheduledQueueId,
    ncp_uint16_t *qDepth);

ncp_st_t
ncp_ncav3_map_shared_data_regions(
    ncp_task_pvt_tqsHdl_data_t *tqsHdl);

ncp_st_t
ncp_ncav3_unmap_shared_data_regions(
    ncp_task_pvt_tqsHdl_data_t *tqsHdl);

ncp_st_t
ncp_ncav3_map_fixed_pool(
    ncp_ncav3_cpu_profile_t *profile);

ncp_st_t
ncp_ncav3_unmap_fixed_pool(void);

ncp_st_t
ncp_ncav3_dmm_allocate(
    ncp_task_pvt_tqsHdl_data_t *tqsHdl,
    ncp_uint8_t tqsId,
    ncp_uint8_t poolId,
    ncp_uint8_t size,
    ncp_uint64_t *pBuffer);

ncp_st_t
ncp_ncav3_dmm_free(
    ncp_task_pvt_tqsHdl_data_t *tqsHdl,
    ncp_uint8_t tqsId,
    ncp_uint8_t poolId,
    ncp_uint8_t size,
    ncp_bool_t  mref,
    ncp_uint64_t pBuffer);

ncp_st_t
ncp_ncav3_fpga_lookup_ipd_entry(
    ncp_dev_hdl_t dev,
    ncp_uint8_t  ncapId,
    ncp_uint8_t  relTqsId,
    ncp_uint8_t *ipcqId);

ncp_st_t
ncp_ncav3_configure_tqs_hw(
    ncp_t                   *ncp,
    ncp_dev_hdl_t            dev,
    int                      ncapId,
    int                      relTqsId,
    ncp_ncav3_cpu_profile_t *profile);

ncp_st_t
ncp_ncav3_set_tracing_enable(
    ncp_dev_hdl_t dev,
    ncp_bool_t enable);

ncp_st_t
ncp_ncav3_queue_set_tracing_enable(
    ncp_dev_hdl_t dev,
    ncp_bool_t enable,
    ncp_uint32_t ncaQueueId);

ncp_st_t
ncp_ncav3_reset_pgit_indexes(
    ncp_t           *ncp,
    ncp_ncav3_hdl_t *nca,
    ncp_uint8_t      pgitId);

ncp_st_t
ncp_ncav3_init_pgit_monitor_grp_indexes(
    ncp_dev_hdl_t  dev,
    int            ncapId,
    ncp_uint8_t    tqsId);

ncp_st_t
ncp_ncav3_get_queue_profile(
    ncp_int32_t                     profileId,
    ncp_ncav3_nca_queue_profile_t **queueProfile);

ncp_st_t
ncp_ncav3_delete_gid_from_ipcq(
    ncp_t         *ncp,
    ncp_dev_hdl_t  dev,
    ncp_uint8_t    gidSlot,
    ncp_uint8_t    groupId,
    ncp_uint8_t    priority,
    ncp_uint8_t    ipcqId);

ncp_st_t
ncp_ncav3_add_gid_to_ipcq(
    ncp_t         *ncp,
    ncp_dev_hdl_t  dev,
    ncp_uint8_t    gidSlot,
    ncp_uint8_t    groupId,
    ncp_uint8_t    priority,
    ncp_uint8_t    ipcqId);

ncp_st_t
ncp_ncav3_take_nca_queue_offline(
    ncp_dev_hdl_t dev,
    ncp_uint32_t  queueId);

ncp_st_t
ncp_ncav3_bring_nca_queue_online(
    ncp_dev_hdl_t dev,
    ncp_uint32_t  queueId);

ncp_st_t
ncp_ncav3_free_tqs_state(
    ncp_uint32_t tqsId);

ncp_st_t
ncp_ncav3_configure_awtrace0(
    ncp_ncav3_hdl_t *nca,
    ncp_dev_hdl_t    dev);

ncp_st_t
ncp_ncav3_configure_awtrace1(
    ncp_ncav3_hdl_t *nca,
    ncp_dev_hdl_t    dev);

ncp_st_t
ncp_ncav3_init_ipd_ram(
    ncp_t        *ncp,
    ncp_dev_hdl_t dev,
    ncp_uint32_t ncapId,
    ncp_uint32_t relTqsId,
    ncp_uint8_t  pgitId,
    ncp_ncav3_cpu_profile_t *profile);

ncp_st_t
ncp_ncav3_static_supply_nca_buffers(
    ncp_t           *ncp,
    ncp_ncav3_hdl_t *nca,
    ncp_dev_hdl_t    dev,
    ncp_bool_t       uMode);

ncp_st_t
ncp_task_initialize_tqs_task_state(
    ncp_hdl_t  ncpHdl,
    ncp_bool_t uMode);

ncp_st_t
ncp_ncav3_get_ncap_id_list(
    ncp_t        *ncp,
    int          *numNCAPs,
    ncp_uint32_t **ncapList);

#endif /* __NCP_NCAV3_PVT_H__ */
