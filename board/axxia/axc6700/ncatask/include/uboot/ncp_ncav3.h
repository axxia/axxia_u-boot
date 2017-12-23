/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                        *
 **                                                                       *
 **************************************************************************/

#ifndef __NCP_NCAV3_H__
#define __NCP_NCAV3_H__

#include "uboot/ncp_pcq.h"

#define NCP_NCAV3_NUM_ALLOWED_POOLS 8
#define NCP_NCAV3_MAX_NUM_DOMAINS 34
#define NCP_NCAV3_NUM_NCAP 13
#define NCP_TASK_NUM_BUFF_SIZES 4
#define NCP_NCAV3_NUM_IPCQS_PER_TQS 1
#define NCP_NCAV3_NUM_OPCQS_PER_TQS 2
#define NCP_NCAV3_NUM_MPCQS_PER_TQS 24
#define NCP_TASK_VP_CONTROL_POOL_ID 0

/* Used for parameter validation and array sizing */
#define NCP_NCAV3_FIRST_SHARED_POOL_ID 2
#define NCP_NCAV3_LAST_SHARED_POOL_ID  7
#define NCP_NCAV3_FIRST_CPU_POOL_ID    8
#define NCP_NCAV3_NUM_CPU_POOLS        16
#define NCP_NCAV3_LAST_CPU_POOL_ID     23
#define NCP_NCAV3_NUM_TASK_MEMORY_POOLS (NCP_NCAV3_LAST_CPU_POOL_ID+1)
#define NCP_NCAV3_NUM_VIRTUAL_REGIONS  16
#define NCP_NCAV3_NUM_MEMORY_QUOTA_GROUPS 32

/* Used for parameter validation and array sizing */
#define NCP_NCAV3_MAX_NUM_QUEUE_GROUPS 256
#define NCP_NCAV3_MAX_NUM_NCAQS        204
#define NCP_NCAV3_MAX_NUM_CPUS         32
#define NCP_NCAV3_MAX_NUM_TQSETS       86     /* CPU limited to first 64 */
#define NCP_NCAV3_MAX_NUM_IPCQS        86 
#define NCP_NCAV3_MAX_NUM_OPCQS      (NCP_NCAV3_MAX_NUM_TQSETS * \
                                      NCP_NCAV3_NUM_OPCQS_PER_TQS)
#define NCP_NCAV3_MAX_NUM_UNSCHEDULED_QUEUES (32*1024)
#define NCP_NCAV3_MAX_NUM_SHARED_DATA_REGIONS 256

#define NCP_NCAV3_NUM_CPU_TQSETS     64
#define NCP_NCAV3_NUM_CPU_IPCQS      NCP_NCAV3_NUM_CPU_TQSETS
#define NCP_NCAV3_NUM_CPU_OPCQS     (NCP_NCAV3_NUM_CPU_TQSETS * \
                                     NCP_NCAV3_NUM_OPCQS_PER_TQS)
#define NCP_NCAV3_NUM_CPU_NCAPS 8
#define NCP_NCAV3_NUM_TQSETS_PER_CPU_NCAP 8
#define NCP_NCAV3_NUM_QUEUE_GROUPS_PER_IPCQ 8

/* The A53 cores all use a fixed virtual region */
#define NCP_NCAV3_CPU_VIRTUAL_REGION_ID 0
 
#define CPU_TQS_CONFIG 0
#define CPU_PROFILE 0


/**********************************************************************
 * TQS/PGIT data structures
 **********************************************************************/

/* Each TQS/PGIT structure occupies 4KB and is located at the end of NVM. */

typedef struct {
    ncp_tqs_t tqs; /* 256B */
    char reserved[3840]; /* reserved space for queues */
} ncp_ncav3_tqs_control_t;

/**********************************************************************
 * Configuration-related structures
 **********************************************************************/

typedef struct {
    ncp_int32_t depth;
    ncp_int32_t maxDepth;
    ncp_int32_t almostEmptySize;
    ncp_int32_t almostFullSize;
    ncp_int32_t numBuffersPerRequest;
} ncp_ncav3_queue_depth_t;

typedef struct {
    ncp_int64_t size;
    ncp_int32_t regionId;
    ncp_task_resource_name_t name;
    ncp_bool_t  enabled;
    ncp_int64_t physicalStartAddress;
    ncp_int64_t physicalEndAddress;
    ncp_int64_t virtualStartAddress;
    ncp_int64_t virtualEndAddress;
} ncp_ncav3_shared_data_region_map_t;

typedef struct {
    ncp_int32_t poolId;
    ncp_bool_t  enabled;
    ncp_int64_t physicalStartAddress;
    ncp_int64_t physicalEndAddress;
    ncp_int64_t virtualStartAddress;
    ncp_int64_t virtualEndAddress;
} ncp_ncav3_pool_map_t;

typedef struct {
    ncp_ncav3_pool_map_t    poolMap;
    ncp_bool_t              allocatorNeeded;
    ncp_ncav3_queue_depth_t allocators[4];
} ncp_ncav3_shared_pool_map_t;

typedef struct {
    ncp_task_resource_name_t name;
    ncp_int32_t len;
    char bin[256];
} ncp_ncav3_initialized_data_structure_t;

typedef struct {
    ncp_int32_t id;
    ncp_task_resource_name_t name;
    ncp_bool_t uMode;
    ncp_ncav3_task_completion_mode_e  completionMode;
    ncp_ncav3_task_consumption_mode_e consumptionMode;
    ncp_ncav3_initialized_data_structure_t initDataStructure;
    ncp_int32_t receiveQueueDepth;
    ncp_int32_t receiveMaxQueueDepth;
    ncp_int32_t transmitQueue0Depth;
    ncp_int32_t transmitQueue1Depth;
    ncp_uint32_t numSharedPoolMaps;
    ncp_ncav3_shared_pool_map_t sharedPoolMaps[NCP_NCAV3_NUM_SHARED_POOLS];
    ncp_ncav3_pool_map_t cpuPoolMap;
    ncp_ncav3_pool_map_t fixedPoolMap;
    ncp_uint32_t numSharedDataRegionMaps;
    ncp_ncav3_shared_data_region_map_t *sharedDataRegionMap;
    ncp_int32_t taskSendCopyPool;
    ncp_int32_t endianness;
    ncp_int32_t parameterEndianness;
    ncp_int32_t virtualRegionId;
} ncp_ncav3_cpu_profile_t;

typedef struct {
    ncp_uint32_t profileType;
    ncp_ncav3_cpu_profile_t baseProfile;
    void *auxiliaryInfo;
} ncp_ncav3_application_profile_t;

typedef struct {
    ncp_int32_t poolId;
    ncp_bool_t  enabled;
} ncp_ncav3_recv_queue_pool_t;

typedef enum {
    IPCQ,
    OPCQ,
    MPCQ
} ncp_ncav3_pcq_type_t;

typedef struct {
    ncp_task_resource_name_t name;
    ncp_int32_t id;
    ncp_int32_t appProfileId;
    ncp_int32_t copyPool;
    ncp_bool_t  copyRuleForceCopy;
    ncp_int32_t copyRuleMinPduDataInFirstBlock;
    ncp_int32_t copyRuleMinFirstBlockPduOffset;
    ncp_int32_t copyRuleMinModifiableLength;
    ncp_bool_t  copyRuleSeparateHeader;
    ncp_int32_t memoryQuota;
    ncp_int32_t thresholdGroupId;
    ncp_int32_t numAllowedPools;
    ncp_ncav3_recv_queue_pool_t allowedPools[NCP_NCAV3_NUM_ALLOWED_POOLS];
    ncp_int32_t unissuedThreshold;
    ncp_int32_t unissuedQueuedThreshold;
} ncp_ncav3_nca_queue_profile_t;

typedef struct {
    ncp_int32_t numProfiles;
    ncp_ncav3_nca_queue_profile_t *queueProfiles;
    ncp_int32_t maxieord_full;
    ncp_int32_t maxieunord_full;
    ncp_int32_t bcam_afull_value;
} ncp_ncav3_task_receive_queue_config_t;

typedef struct {
    ncp_int32_t  numLogEntries;
    ncp_bool_t   traceEnabled;
    ncp_int64_t  logBaseAddress;
    ncp_bool_t   unlimitedLogWrap;
    ncp_int64_t  wrapThreshold;
} ncp_ncav3_task_trace_config_t;

typedef struct {
    ncp_int32_t domainId;
    ncp_bool_t  internal;
    ncp_int64_t physBase;
    ncp_int64_t size;
    ncp_int64_t otbpOffset;
    ncp_int64_t virtBase;
} ncp_ncav3_domain_info_t;

typedef struct{
    ncp_task_resource_name_t name;
    ncp_int32_t sharedPoolId;
    ncp_int64_t limit;
    ncp_bool_t  unlimited;
} ncp_ncav3_memory_quota_entry_t;

typedef struct {
    ncp_task_resource_name_t name;
    ncp_uint32_t numQuotaEntries;
    ncp_ncav3_memory_quota_entry_t quotaEntry[NCP_NCAV3_MAX_SHARED_POOLS];
} ncp_ncav3_memory_quota_t;

typedef struct {
    ncp_uint32_t numEntries;
    ncp_bool_t   enabled;
    ncp_int64_t  pcqVirtualIndex;
    ncp_ncav3_task_completion_mode_e completionMode;
} ncp_ncav3_task_queues_t;

typedef struct {
    ncp_int32_t              vpTableIndex;
    ncp_int32_t              vpId;
    ncp_int32_t              flowIndex;
    ncp_int32_t              priority;
    ncp_int32_t              pushTag;
    ncp_int32_t              popTag;
} ncp_ncav3_virtual_pipeline_t;

typedef enum {
    NCP_NCAV3_QPM_INTERRUPT_SERVICE = 0,
    NCP_NCAV3_QPM_TASK_SERVICE,
    NCP_NCAV3_QPM_NO_SERVICE,
} ncp_ncav3_qpm_service_type_e;

typedef struct {
    ncp_int32_t minQueueId;
    ncp_int32_t maxQueueId;
    ncp_int32_t size;
    ncp_int32_t almostEmptyThreshold;
    ncp_int32_t almostFullThreshold;
    ncp_ncav3_qpm_service_type_e serviceType;
    ncp_int32_t taskVpIndex;
    ncp_bool_t  vppTasksAllowed;
    ncp_int32_t taskProfileIndex;
} ncp_ncav3_unscheduled_queue_t;

typedef struct {
    ncp_int32_t numProfiles;
    ncp_ncav3_nca_queue_profile_t *queueProfiles;
    ncp_int32_t numPipelines;
    ncp_ncav3_virtual_pipeline_t *pipelines;
    ncp_int32_t numMonitoredQueues;
    ncp_ncav3_unscheduled_queue_t *monitoredQueues;
    ncp_int32_t numUnmonitoredQueues;
    ncp_ncav3_unscheduled_queue_t *unmonitoredQueues;
} ncp_ncav3_unscheduled_queue_config_t;

typedef struct {
    ncp_uint32_t                     numMemoryQuotas;
    ncp_ncav3_memory_quota_t        *memoryQuotas;
    ncp_uint32_t                     numProfiles;
    ncp_ncav3_application_profile_t *profiles;
    ncp_ncav3_task_receive_queue_config_t taskReceiveQueues;
    ncp_ncav3_unscheduled_queue_config_t  unscheduledQueueConfig;
    ncp_ncav3_task_trace_config_t     taskTrace;
    ncp_ncav3_domain_info_t           domainInfo[NCP_NCAV3_MAX_NUM_DOMAINS];
} ncp_ncav3_config_info_t;

#endif /* __NCP_NCAV3_H__ */
