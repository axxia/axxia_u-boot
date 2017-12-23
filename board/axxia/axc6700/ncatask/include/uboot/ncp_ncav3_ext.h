/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                        *
 **                                                                       *
 **************************************************************************/

#ifndef __NCP_NCAV3_EXT_H__
#define __NCP_NCAV3_EXT_H__

#include "uboot/ncp_task_pvt.h"

/* Inter-module structures */

typedef struct {
    ncp_uint32_t domainBundleSize;
    ncp_uint32_t taskPoolSize;
    ncp_uint32_t tqsSwStateSize;
    ncp_uint32_t queueStateSize;
    ncp_uint32_t queueGroupStateSize;
    ncp_uint32_t ncaHdlSize;
    ncp_uint32_t queueProfileSize;
    ncp_uint32_t unscheduledQueueSize;
    ncp_uint32_t appProfileSize;
    ncp_uint32_t fixedPoolSize;
    ncp_uint32_t sharedDataRegionMapSize;
} NCP_COMPAT_PACKED ncp_ncav3_struct_sizes_t;

/* Inter-module functions */

ncp_st_t
ncp_ncav3_config_parse(
    ncp_t     *ncp,
    ncp_map_t *map);

ncp_st_t
ncp_ncav3_config_hw(
    ncp_t     *ncp,
    ncp_map_t *map);

ncp_st_t
ncp_ncav3_warm_config(
    ncp_t     *ncp);

ncp_st_t
ncp_ncav3_destroy(
    ncp_t *ncp);

ncp_st_t
ncp_ncav3_get_app_profile(
    ncp_t *ncp,
    ncp_uint32_t appProfileId,
    ncp_ncav3_application_profile_t **appProfile);

ncp_st_t
ncp_ncav3_initialize_tqs_control(
    ncp_t                   *ncp,
    ncp_uint8_t              pgitId,
    ncp_ncav3_cpu_profile_t *profile);

ncp_st_t
ncp_ncav3_initialize_tqs_pcqs(
    ncp_t                   *ncp,
    ncp_dev_hdl_t            dev,
    ncp_uint32_t             ncapId,
    ncp_uint32_t             tqsId,
    ncp_uint8_t              pgitId,
    ncp_ncav3_cpu_profile_t *profile,
    ncp_uint32_t             base,
    ncp_uint8_t              upperBits);

ncp_st_t
ncp_ncav3_initialize_pool_maps(
    ncp_t *ncp,
    int    profileType);

ncp_st_t
ncp_ncav3_set_pgit_timers(
    ncp_dev_hdl_t dev,
    int           ncapId,
    int           relativeTqsId);

ncp_st_t
ncp_ncav3_enable_pgit_timers(
    ncp_dev_hdl_t dev,
    int           ncapId,
    int           relativeTqsId);

ncp_st_t
ncp_ncav3_initialize_tqs(
    ncp_t         *ncp,
    ncp_dev_hdl_t  dev,
    int            ncapId,
    int            relTqsId,
    ncp_uint8_t    pgitId,
    ncp_uint32_t   base,
    ncp_uint8_t    upperBits);

ncp_st_t
ncp_ncav3_enable_ncap(
    ncp_dev_hdl_t  dev,
    int            ncapId);

ncp_st_t
ncp_ncav3_initialize_ncap(
    ncp_t         *ncp,
    ncp_dev_hdl_t  dev,
    int            ncapId);

ncp_st_t
ncp_ncav3_parse_initialized_data_structure(
    ncp_map_t *profileMap,
    ncp_ncav3_initialized_data_structure_t *ids);

ncp_st_t
ncp_ncav3_parse_shared_pool_mappings(
    ncp_map_t *profileMap,
    ncp_uint32_t *numSharedPoolMaps,
    ncp_ncav3_shared_pool_map_t *sharedPoolMaps);

ncp_st_t
ncp_ncav3_parse_fixed_pool_mapping(
    ncp_map_t *profileMap,
    ncp_ncav3_pool_map_t *fixedPoolMap,
    ncp_uint32_t          profileType);

ncp_st_t
ncp_ncav3_parse_shared_data_region_mapping(
    ncp_map_t *profileMap,
    ncp_ncav3_cpu_profile_t *profile,
    ncp_uint32_t profileType);

ncp_st_t
ncp_ncav3_parse_task_queue_depths(
    ncp_map_t *profileMap,
    ncp_ncav3_queue_depth_t *pcqDepths);

ncp_st_t
ncp_ncav3_parse_task_tqs_queue_group_mapping(
    ncp_map_t *cpuTqsMap,
    ncp_uint32_t tqsId,
    ncp_bool_t   staticConfiguration);

ncp_st_t
ncp_ncav3_configure_addr_convert_pool_virt_base_ram(
    ncp_dev_hdl_t    dev,
    int              vrID,
    int              poolID,
    ncp_uint64_t     poolVA);

ncp_st_t
ncp_ncav3_purge_pgit(
    ncp_dev_hdl_t  dev,
    ncp_uint8_t    ncapId,
    ncp_uint8_t    pgitId);

ncp_st_t
ncp_ncav3_disable_ipcq(
    ncp_dev_hdl_t dev,
    ncp_uint8_t   ncapId,
    ncp_uint8_t   relTqsId,
    ncp_uint8_t   pgitId);

ncp_st_t
ncp_ncav3_enable_ipcq(
    ncp_dev_hdl_t dev,
    ncp_uint8_t   ncapId,
    ncp_uint8_t   relTqsId,
    ncp_uint8_t   pgitId);

ncp_st_t
ncp_ncav3_take_pgit_offline(
    ncp_task_tqs_hdl_t *tqsHdl,
    ncp_dev_hdl_t       dev,
    ncp_uint8_t         ncapId,
    ncp_uint8_t         relTqsId,
    ncp_uint8_t         pgitId);

ncp_st_t
ncp_ncav3_get_app_profile_from_name(
    ncp_t *ncp,
    char  *name,
    ncp_ncav3_application_profile_t **appProfile);

ncp_st_t
ncp_ncav3_nca_queue_enable(
    ncp_dev_hdl_t dev,
    ncp_uint32_t  queueId);

ncp_st_t
ncp_ncav3_nca_queue_disable(
    ncp_dev_hdl_t dev,
    ncp_uint32_t  queueId);

ncp_st_t
ncp_ncav3_config_cow_task_queue(
    ncp_ncav3_nca_queue_state_t *queue);

ncp_st_t
ncp_ncav3_write_itp_tpd_ram_entry(
    ncp_dev_hdl_t                dev,
    ncp_ncav3_nca_queue_state_t *queue);

ncp_st_t
ncp_ncav3_config_kernel(
    ncp_t                    *ncp,
    ncp_ncav3_hdl_t          *nca,
    ncp_dev_hdl_t             dev,
    ncp_ncav3_struct_sizes_t  sizes,
    ncp_bool_t                internal);

ncp_st_t
ncp_ncav3_kernel_destroy(
    ncp_t        *ncp,
    ncp_dev_hdl_t dev);

ncp_st_t
ncp_ncav3_init_tqs_configuration_state(
    ncp_ncav3_hdl_t                 *nca,
    ncp_uint8_t                      pgitId,
    ncp_ncav3_application_profile_t *profile,
    ncp_task_tqs_shared_t           *flags,
    ncp_bool_t                       updateKernelTQSState);

ncp_st_t
ncp_ncav3_reset_pcq_group(
    ncp_dev_hdl_t dev,
    ncp_uint8_t   ncapId,
    ncp_uint32_t  relTqsId);

ncp_st_t
ncp_ncav3_reset_tqs_sw_state(
    ncp_uint8_t   pgitId);

ncp_st_t
ncp_ncav3_get_absolute_group_id(
    int ncapId,
    int tqsId,
    ncp_uint8_t *grpId);

ncp_st_t
ncp_ncav3_get_ncap_and_tqs_id_from_absolute_group_id(
    ncp_uint8_t grpId,
    ncp_uint8_t *ncapId,
    ncp_uint8_t *relTqsId);

ncp_st_t
ncp_ncav3_disable_mpcqs(
    ncp_dev_hdl_t  dev,
    ncp_uint8_t    ncapId,
    ncp_uint8_t    relTqsId,
    ncp_uint8_t    pgitId);

ncp_st_t
ncp_ncav3_disable_pgit_timers(
    ncp_dev_hdl_t dev,
    int           ncapId,
    int           relativeTqsId);

ncp_st_t
ncp_ncav3_read_interrupt_queue(
    ncp_dev_hdl_t dev,
    ncp_uint32_t  intQueueId,
    ncp_uint16_t *eventQueueId,
    ncp_uint16_t *intQueueDepth);

ncp_st_t
ncp_ncav3_ack_interrupt_queue(
    ncp_dev_hdl_t dev,
    ncp_uint32_t  intQueueId);

ncp_st_t
ncp_ncav3_ack_event_queue_exception(
    ncp_dev_hdl_t dev,
    ncp_uint32_t  eventQueueId);

ncp_st_t
ncp_ncav3_get_qpm_stats(
    ncp_dev_hdl_t  dev,
    ncp_uint16_t   queueId,
    ncp_uint64_t  *fullQueue,
    ncp_uint64_t  *emptyQueue,
    ncp_uint64_t  *overflow);

ncp_st_t
ncp_ncav3_tqs_enable(
    ncp_uint16_t tqsId);

ncp_st_t
ncp_ncav3_tqs_disable(
    ncp_uint16_t tqsId);

ncp_st_t
ncp_ncav3_queue_group_add(
    ncp_dev_hdl_t dev,
    ncp_uint32_t queueGroupId,
    ncp_task_resource_name_t *name,
    ncp_ncav3_recv_queue_type_t ordering);

ncp_st_t
ncp_ncav3_queue_group_delete(
    ncp_dev_hdl_t dev,
    ncp_uint32_t queueGroupId);

ncp_st_t
ncp_ncav3_queue_group_modify(
    ncp_dev_hdl_t dev,
    ncp_uint32_t queueGroupId,
    ncp_ncav3_recv_queue_type_t ordering);

ncp_st_t
ncp_ncav3_nca_queue_group_set(
    ncp_dev_hdl_t dev,
    ncp_uint32_t ncaQueueId,
    ncp_uint32_t queueGroupId);

ncp_st_t
ncp_ncav3_tqs_queue_group_set(
    ncp_dev_hdl_t dev,
    ncp_uint32_t tqsId,
    ncp_task_queue_group_set_t pGrp[8],
    ncp_uint8_t numQueueGroups);

ncp_st_t
ncp_ncav3_nca_queue_configure(
    ncp_dev_hdl_t dev,
    ncp_uint32_t ncaQueueId,
    ncp_task_resource_name_t *queueName,
    ncp_task_resource_name_t *queueProfileName,
    ncp_int32_t queueGroupId,
    ncp_uint32_t paramsSize,
    ncp_task_nca_queue_sched_params_t *params);

ncp_st_t
ncp_ncav3_tqs_configure_flags_get(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t  tqsId,
    ncp_task_tqs_shared_t *pFlags);

ncp_st_t
ncp_ncav3_tqs_memory_quota_group_get(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t tqsId,
    ncp_uint32_t *pMemoryQuotaGroupId);

ncp_st_t
ncp_ncav3_tqs_queue_group_get(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t tqsId,
    ncp_task_queue_group_set_t pGrp[8],
    ncp_uint8_t *pNumQueueGroups);

ncp_st_t
ncp_ncav3_queue_group_membership_get(
    ncp_dev_hdl_t  devHdl,
    ncp_uint32_t   ncaQueueId,
    ncp_uint32_t  *pQueueGroupId);

ncp_st_t
ncp_ncav3_queue_group_name_get(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t queueGroupId,
    ncp_task_resource_name_t *name);

ncp_st_t
ncp_ncav3_tqs_name_get(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t tqsId,
    ncp_task_resource_name_t *pResourceName);

ncp_st_t
ncp_ncav3_nca_queue_name_get(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t ncaQueueId,
    ncp_task_resource_name_t *name);

ncp_st_t
ncp_ncav3_queue_group_id_get(
    ncp_dev_hdl_t devHdl,
    ncp_task_resource_name_t *name,
    ncp_uint32_t *pQueueGroupId);

ncp_st_t
ncp_ncav3_tqs_id_get(
    ncp_dev_hdl_t devHdl,
    ncp_task_resource_name_t *pResourceName,
    ncp_uint32_t *pTqsId);

ncp_st_t
ncp_ncav3_nca_queue_id_get(
    ncp_dev_hdl_t devHdl,
    ncp_task_resource_name_t *name,
    ncp_uint32_t *pNcaQueueId);

ncp_st_t
ncp_ncav3_cpu_app_profile_name_get(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t profileId,
    ncp_task_resource_name_t *name);

ncp_st_t
ncp_ncav3_nca_queue_profile_name_get(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t  profileId,
    ncp_task_resource_name_t *name);

ncp_st_t
ncp_ncav3_nca_queue_profile_id_get(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t ncaQueueId,
    ncp_uint32_t *pProfileId);

ncp_st_t
ncp_ncav3_pool_name_get(
    ncp_dev_hdl_t ncpHdl,
    ncp_uint8_t bufferPoolId,
    ncp_task_resource_name_t *name);

ncp_st_t
ncp_ncav3_pool_id_get(
    ncp_dev_hdl_t devHdl,
    ncp_task_resource_name_t *name,
    ncp_uint8_t *bufferPoolId);

ncp_st_t
ncp_ncav3_unset_inBind(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t  tqsId,
    ncp_bool_t    uMode);

ncp_st_t
ncp_ncav3_finish_configure(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t  tqsId,
    ncp_bool_t    uMode);

ncp_st_t
ncp_ncav3_set_tqs_configured_state(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t  tqsId,
    ncp_bool_t    configured);

ncp_st_t
ncp_ncav3_perform_tqs_bind_checks(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t  tqsId,
    ncp_bool_t    uMode);

NCP_API ncp_st_t
ncp_ncav3_tqs_configure(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t tqsId,
    ncp_task_resource_name_t *tqsName,
    ncp_task_resource_name_t *appProfileName,
    ncp_task_tqs_shared_t *pFlags,
    ncp_uint32_t mqgId,
    ncp_bool_t   uMode);

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
ncp_ncav3_reset_tracing(
    ncp_dev_hdl_t dev);

ncp_st_t
ncp_ncav3_update_kernel_tqs_state(
    ncp_dev_hdl_t dev,
    ncp_uint8_t   pgitId,
    ncp_int32_t   profileId);

ncp_st_t
ncp_ncav3_get_app_profile_id_from_name(
    ncp_t *ncp,
    char  *name,
    ncp_uint32_t *appProfileId);

ncp_st_t
ncp_ncav3_check_queue_group_for_orphaned_queues(
    ncp_dev_hdl_t dev,
    ncp_uint32_t tqsId,
    ncp_uint32_t groupIndex,
    ncp_bool_t   takeLock);

ncp_st_t
ncp_ncav3_enable_kernel_tqs(
    ncp_dev_hdl_t dev,
    ncp_uint16_t tqsId,
    ncp_bool_t   enable);

ncp_st_t
ncp_ncav3_get_app_profile_pool_mapping(
    ncp_dev_hdl_t dev,
    ncp_task_resource_name_t *appProfileName,
    ncp_bool_t poolEnabled[8]);

ncp_st_t
ncp_ncav3_get_app_profile_name(
    ncp_dev_hdl_t  dev,
    ncp_uint32_t tqsId,
    ncp_task_resource_name_t *appProfileName);

ncp_st_t
ncp_ncav3_get_unscheduled_receive_queue_profile_pool_mapping(
    ncp_dev_hdl_t dev,
    ncp_task_resource_name_t *appProfileName,
    ncp_bool_t poolEnabled[8]);

ncp_st_t
ncp_ncav3_get_unscheduled_recv_queue_profile_from_name(
    ncp_t *ncp,
    char  *name,
    ncp_ncav3_nca_queue_profile_t **queueProfile);

ncp_st_t
ncp_ncav3_get_unscheduled_receive_queue_profile_name(
    ncp_dev_hdl_t dev,
    ncp_uint32_t queueId,
    ncp_task_resource_name_t *queueProfileName);

#endif /* __NCP_NCAV3_EXT_H__ */
