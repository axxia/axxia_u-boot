/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/

/*! @file      ncp_cow.h
 *  @brief     COW and Task Tracing features
 * 
 *  @addtogroup _cow_ Common Task Management
 * 
 *  @{
 */
#ifndef _NCP_COW_H_
#define _NCP_COW_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "uboot/ncp_types.h"
#include "uboot/ncp_sal.h"


/* 
 * Enum of HW engines in acp. The enum numbers from eioa0 thru tdmioa needs to be 
 * same as it matches HW dest type. 
 * expander needs to be next to mtm as thats how config file has it.
 */

/* 
 * @enum ncp_engine_type_t
 * @brief Enum of HW engines.
 */
typedef enum ncp_engine_type_e {
    ncp_engine_min      = 0,    /*!< Min value. Not used. */
    ncp_engine_eioa0    = 1,    /*!< eioa0 engine. */
    ncp_engine_timer    = 2,    /*!< timer engine. */
    ncp_engine_pab      = 3,    /*!< pab engine. */
    ncp_engine_mpp      = 4,    /*!< mpp engine. */
    ncp_engine_spp      = 5,    /*!< spp engine. */
    ncp_engine_sed      = 6,    /*!< sed engine. */
    ncp_engine_cpu      = 7,    /*!< cpu engine. */
    ncp_engine_dpi      = 8,    /*!< dpi engine. */
    ncp_engine_pic      = 9,    /*!< pic engine. */
    ncp_engine_mtm      = 10,   /*!< mtm engine. */
    ncp_engine_expander = 11,   /*!< expander engine. */
    ncp_engine_eioa1    = 12,   /*!< eioa1 engine. */
    ncp_engine_isb      = 13,   /*!< isb engine. */
    ncp_engine_tdmioa   = 14,   /*!< tdmioa engine. */
    ncp_engine_isbs     = 15,   /*!< isbs engine. */
    ncp_engine_eioa2    = 16,   /*!< eioa2 engine. */
    ncp_engine_eioa3    = 17,   /*!< eioa3 engine. */
    ncp_engine_eioa4    = 18,   /*!< eioa4 engine. */
    ncp_engine_eioa5    = 19,   /*!< eioa5 engine. */
    ncp_engine_eioa6    = 20,   /*!< eioa6 engine. */
    ncp_engine_eioa7    = 21,   /*!< eioa7 engine. */
    ncp_engine_isbs1    = 22,   /*!< isbs1 engine. */
    ncp_engine_decoder  = 23,   /*!< decoder engine. */
    ncp_engine_rif0     = 24,   /*!< rif0 engine. */
    ncp_engine_rif1     = 25,   /*!< rif1 engine. */
    ncp_engine_erif0    = 26,   /*!< erif0 engine. */
    ncp_engine_erif1    = 27,   /*!< erif1 engine. */
    ncp_engine_max              /*!< Max value. Not used. */
} ncp_engine_type_t;

/*!
 * @enum ncp_cow_bcn_capture_t
 * BCN Slave capture targets
 */
typedef enum
{
    NCP_COW_BCN_CAPTURE_SLAVE,          /*!< BCN Slave Count; captured on Master capture event */
    NCP_COW_BCN_CAPTURE_SLAVE_SYNC      /*!< BCN Slave Sync Count; captured when external sync is active */
} ncp_cow_bcn_capture_t;

/*!
 * @ingroup _cow_task_trace_
 * @brief Task Trace Entry
 * NOTE: Deprecated
 */
typedef struct ncp_task_trace_entry_s {
    ncp_uint8_t entrySize;
    ncp_uint64_t timestamp;
    ncp_byte_string_t taskHeader;
    ncp_byte_string_t nextTaskData;
} ncp_task_trace_entry_t;

  /* BCN Slave APIs */

/*! @fn ncp_st_t ncp_cow_bcn_slave_enable(ncp_hdl_t ncpHdl, ncp_engine_type_t engine, ncp_uint32_t incrVal)
    @brief Enable BCN Slave Counter.
    @param[in] ncpHdl Incoming handle of the current NCP device
    @param[in] engine The Slave Counter engine.  Valid values are ncp_engine_rif0, ncp_engine_rif1, ncp_engine_erif0, ncp_engine_erif1, ncp_engine_timer, ncp_engine_eioa0, ncp_engine_eioa1, ncp_engine_eioa2, ncp_engine_eioa3, ncp_engine_eioa4, and ncp_engine_eioa5.
    @param[in] incrVal The amount the BCN Slave Counter increments each cycle
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_INVALID_VALUE incrVal cannot be represented in one byte
    @retval NCP_ST_COW_INVALID_ENGINE The engine does not include a BCN Slave
    @retval NCP_ST_COW_BCN_SLAVE_ENABLED The BCN Slave Counter is already enabled
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_cow_bcn_slave_enable(ncp_hdl_t ncpHdl, ncp_engine_type_t engine, ncp_uint32_t incrVal);

/*! @fn ncp_st_t ncp_cow_bcn_slave_disable(ncp_hdl_t ncpHdl, ncp_engine_type_t engine)
    @brief Disable BCN Slave Counter.
    @param[in] ncpHdl Incoming handle of the current NCP device
    @param[in] engine The Slave Counter engine.  Valid values are ncp_engine_rif0, ncp_engine_rif1, ncp_engine_erif0, ncp_engine_erif1, ncp_engine_timer, ncp_engine_eioa0, ncp_engine_eioa1, ncp_engine_eioa2, ncp_engine_eioa3, ncp_engine_eioa4, and ncp_engine_eioa5.
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_COW_INVALID_ENGINE The engine does not include a BCN Slave
    @retval NCP_ST_COW_BCN_SLAVE_DISABLED The BCN Slave Counter is already disabled
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_cow_bcn_slave_disable(ncp_hdl_t ncpHdl, ncp_engine_type_t engine);

/*! @fn ncp_st_t ncp_cow_bcn_slave_load_config(ncp_hdl_t ncpHdl, ncp_engine_type_t engine, ncp_uint64_t loadVal)
    @brief Configure a BCN Slave load event.  When the BCN Master generates a bcn_load signal, the Slave will load loadVal into the Slave Counter.
    @param[in] ncpHdl Incoming handle of the current NCP device
    @param[in] engine The Slave Counter engine.  Valid values are ncp_engine_rif0, ncp_engine_rif1, ncp_engine_erif0, ncp_engine_erif1, ncp_engine_timer, ncp_engine_eioa0, ncp_engine_eioa1, ncp_engine_eioa2, ncp_engine_eioa3, ncp_engine_eioa4, and ncp_engine_eioa5.
    @param[in] loadVal The value to be loaded into the BCN Slave Counter on a bcn_load signal
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_COW_INVALID_ENGINE The engine does not include a BCN Slave
    @retval NCP_ST_COW_BCN_SLAVE_ENABLED The BCN Slave Counter is already enabled
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_cow_bcn_slave_load_config(ncp_hdl_t ncpHdl, ncp_engine_type_t engine, ncp_uint64_t loadVal);

/*! @fn ncp_st_t ncp_cow_bcn_slave_load_trigger(ncp_hdl_t ncpHdl, ncp_engine_type_t engine)
    @brief Trigger a BCN Slave load event.  This API is used to force a load of the loadVal into the BCN Slave Counter, without generating a bcn_load signal from the BCN Master.
    @param[in] ncpHdl Incoming handle of the current NCP device
    @param[in] engine The Slave Counter engine.  Valid values are ncp_engine_rif0, ncp_engine_rif1, ncp_engine_erif0, ncp_engine_erif1, ncp_engine_timer, ncp_engine_eioa0, ncp_engine_eioa1, ncp_engine_eioa2, ncp_engine_eioa3, ncp_engine_eioa4, and ncp_engine_eioa5.
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_COW_INVALID_ENGINE The engine does not include a BCN Slave
    @retval NCP_ST_COW_BCN_SLAVE_DISABLED The BCN Slave Counter is not enabled
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_cow_bcn_slave_load_trigger(ncp_hdl_t ncpHdl, ncp_engine_type_t engine);

/*! @fn ncp_st_t ncp_cow_bcn_slave_get_capture_value(ncp_hdl_t ncpHdl, ncp_engine_type_t engine, ncp_cow_bcn_capture_t bcnCaptureTarget, ncp_uint64_t *captureVal)
    @brief Read a BCN Slave captured value
    @param[in] ncpHdl Incoming handle of the current NCP device
    @param[in] engine The Slave Counter engine.  Valid values are ncp_engine_rif0, ncp_engine_rif1, ncp_engine_erif0, ncp_engine_erif1, ncp_engine_timer, ncp_engine_eioa0, ncp_engine_eioa1, ncp_engine_eioa2, ncp_engine_eioa3, ncp_engine_eioa4, and ncp_engine_eioa5.
    @param[in] bcnCaptureTarget The capture value to read.  Valid values are NCP_COW_BCN_CAPTURE_SLAVE and NCP_COW_BCN_CAPTURE_SLAVE_SYNC.
    @param[out] captureVal The value read from the selected capture target
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_DEV_INVALID_BUFFER captureVal points to an invalid address
    @retval NCP_ST_COW_INVALID_ENGINE The engine does not include a BCN Slave
    @retval NCP_ST_COW_BCN_SLAVE_INVALID_CAPTURE_TARGET The BCN capture target is invalid
    @retval NCP_ST_* Lower level NCP device access error codes
*/
NCP_API ncp_st_t
ncp_cow_bcn_slave_get_capture_value(ncp_hdl_t ncpHdl, ncp_engine_type_t engine, ncp_cow_bcn_capture_t bcnCaptureTarget, ncp_uint64_t *captureVal);

    /*!
     *
     *  @brief     COW Task Trace APIs.
     *  @ingroup   _cow_
     *  @detail    Task Trace APIs. These APIs are deprecated 
     *             These APIs only here for binary compatibility purposes.
     *  @defgroup  _cow_task_trace_ COW Task Trace
     */

/*
 * Task Trace APIs  -- These APIs are deprecated.
 *
 */

/*!
 * @ingroup _cow_task_trace_
 * @fn ncp_st_t ncp_task_trace_enable(ncp_hdl_t ncpHdl, ncp_engine_type_t engine)
 * NOTE: Deprecated
 */
NCP_API ncp_st_t
ncp_task_trace_enable(ncp_hdl_t ncpHdl, ncp_engine_type_t engine);

/*!
 * @ingroup _cow_task_trace_
 * @fn ncp_st_t ncp_task_trace_disable(ncp_hdl_t ncpHdl, ncp_engine_type_t engine)
 * NOTE: Deprecated
 */
NCP_API ncp_st_t
ncp_task_trace_disable(ncp_hdl_t ncpHdl, ncp_engine_type_t engine);

/*!
 * @ingroup _cow_task_trace_
 * @fn ncp_st_t ncp_task_trace_trigger_enable(ncp_hdl_t ncpHdl, ncp_engine_type_t engine)
 * NOTE: Deprecated
 */
NCP_API ncp_st_t
ncp_task_trace_trigger_enable(ncp_hdl_t ncpHdl, ncp_engine_type_t engine);

/*!
 * @ingroup _cow_task_trace_
 * @fn ncp_st_t ncp_task_trace_trigger_disable(ncp_hdl_t ncpHdl, ncp_engine_type_t engine)
 * NOTE: Deprecated
 */
NCP_API ncp_st_t
ncp_task_trace_trigger_disable(ncp_hdl_t ncpHdl, ncp_engine_type_t engine);

/*!
 * @ingroup _cow_task_trace_
 * @fn ncp_st_t ncp_task_trace_trigger_set(ncp_hdl_t ncpHdl,
 *                         ncp_engine_type_t engine,
 *                         ncp_bool_t countMatches,
 *                         ncp_uint32_t countThreshold,
 *                         ncp_bool_t triggerStart,
 *                         ncp_byte_string_t taskHeaderPattern,
 *                         ncp_byte_string_t taskParamPattern,
 *                         ncp_byte_string_t taskHeaderMask,
 *                         ncp_bool_t taskParamMask[8],
 *                         ncp_uint8_t taskParamByteAddr[8])
 *
 *
 * NOTE: Deprecated
 */
NCP_API ncp_st_t
ncp_task_trace_trigger_set(ncp_hdl_t ncpHdl,
                           ncp_engine_type_t engine,
                           ncp_bool_t countMatches,
                           ncp_uint32_t countThreshold,
                           ncp_bool_t triggerStart,
                           ncp_byte_string_t taskHeaderPattern,
                           ncp_byte_string_t taskParamPattern,
                           ncp_byte_string_t taskHeaderMask,
                           ncp_bool_t taskParamMask[8],
                           ncp_uint8_t taskParamByteAddr[8]);

/*!
 * @ingroup _cow_task_trace_
 * @fn ncp_st_t ncp_task_trace_buffer_get(ncp_hdl_t ncpHdl,
 *                        ncp_engine_type_t engine,
 *                        ncp_task_trace_entry_t *entryList,
 *                        ncp_uint32_t startEntry,
 *                        ncp_uint32_t maxEntries,
 *                        ncp_uint32_t *numEntries)
 *
 *
 * NOTE: Deprecated
 */
NCP_API ncp_st_t
ncp_task_trace_buffer_get(ncp_hdl_t ncpHdl,
                          ncp_engine_type_t engine,
                          ncp_task_trace_entry_t *entryList,
                          ncp_uint32_t startEntry,
                          ncp_uint32_t maxEntries,
                          ncp_uint32_t *numEntries);

/*!
 * @ingroup _cow_task_trace_
 * @fn ncp_st_t ncp_task_trace_buffer_clear(ncp_hdl_t ncpHdl, ncp_engine_type_t engine)
 *
 * NOTE: Deprecated
 */
NCP_API ncp_st_t
ncp_task_trace_buffer_clear(ncp_hdl_t ncpHdl,
                            ncp_engine_type_t engine);

/*!
 *
 *  @addtogroup _cow_ Common Task Management
 *
 *  @{
 */

/*! @fn ncp_st_t ncp_cow_queue_discard_stats_get(ncp_hdl_t ncpHdl, 
                                ncp_engine_type_t engine, 
                                ncp_uint32_t destInstance, 
				                ncp_uint8_t taskPriority,
                                ncp_uint32_t *discardStats)
    @brief Returns the discard stats for the given engine/destInstance/taskPriority.
    @param[in] ncpHdl Incoming handle of the current NCP device
    @param[in] engine The engine to read the discard stats. 
    @param[in] destInstance The destination instance to read the discard stats.
               The values to be provided as below.
               TIMER, MPP, SED, PIC, PAB, SPP, DPI:
                   All Chips: destInstance = 0.
               MTM:
                   All Chips: destInstance = 0, 1.
               EIOA:
                   AXX55xx, AXX56xx: 0-4,16-20,32,33,48,49,64,65,80,81,96,97,112,113.
                   AXC67xx: 0-4,16-20,32-35,48-51,64-66,80-82.
               NCA:
                   Task Queues:
                       AXX55xx, AXM56xx: destInstance = 0-63.
                       AXC67xx: destInstance = 0-203.
                   Logical Queues:
                       AXX55xx, AXM56xx: 128-135.
                       AXC67xx: None.
    @param[in] taskPriority The task priority to read the discard stats.
               Valid values are 0-7.
    @param[out] discardStats Pointer to ncp_uint32_t where discard stats is stored.
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_COW_INVALID_ENGINE The engine specified is invalid or not present in this chip.
    @retval NCP_ST_COW_INVALID_DEST_INST The destInstance param is invalid.
    @retval NCP_ST_COW_INVALID_PRIORITY The taskPriority param is invalid.
    @retval NCP_ST_COW_INVALID_DISCARD_STATS_BUFFER The discardStats param is invalid.
*/
NCP_API ncp_st_t
ncp_cow_queue_discard_stats_get(ncp_hdl_t ncpHdl, 
                                ncp_engine_type_t engine, 
                                ncp_uint32_t destInstance, 
				                ncp_uint8_t taskPriority,
                                ncp_uint32_t *discardStats);

/*!
 * @brief struct for priority to queue index mapping.
 * @see ncp_cow_priority_to_queue_index_map_get
 */

typedef struct ncp_cow_queue_index_map_st {
	ncp_uint8_t queueIndex[8]; /*!< queue index per priority. */
}  ncp_cow_queue_index_map_t;

/*! @fn ncp_cow_priority_to_queue_index_map_get(ncp_hdl_t ncpHdl,
                                     ncp_engine_type_t engine,
                                     ncp_uint32_t destInstance,
                                     ncp_cow_queue_index_map_t *queueIndexMap)
    @brief Returns the queue indexes for the given engine/destInstance.
    @param[in] ncpHdl Incoming handle of the current NCP device
    @param[in] engine The engine to read the queue index.
    @param[in] destInstance The destination instance to read the queue index.
               The values to be provided as below.
               TIMER, MPP, SED, PIC, PAB, SPP, DPI:
                   All Chips: destInstance = 0.
               MTM:
                   All Chips: destInstance = 0, 1.
               EIOA:
                   AXX55xx, AXX56xx: 0-4,16-20,32,33,48,49,64,65,80,81,96,97,112,113.
                   AXC67xx: 0-4,16-20,32-35,48-51,64-66,80-82.
               NCA:
                   Task Queues:
                       AXX55xx, AXM56xx: destInstance = 0-63.
                       AXC67xx: destInstance = 0-203.
                   Logical Queues:
                       AXX55xx, AXM56xx: 128-135.
                       AXC67xx: None.
    @param[out] queueIndexMap Pointer to ncp_cow_queue_index_map_t where
                queue indexes are stored.
    @retval NCP_ST_SUCCESS On success
    @retval NCP_ST_INVALID_HANDLE The handle of the NCP instance is invalid
    @retval NCP_ST_COW_INVALID_ENGINE The engine specified is invalid or not present in this chip.
    @retval NCP_ST_COW_INVALID_DEST_INST The destInstance param is invalid.
    @retval NCP_ST_COW_INVALID_QUEUE_INDEX_MAP_BUFFER The queueIndexMap param is invalid.
*/
NCP_API ncp_st_t
ncp_cow_priority_to_queue_index_map_get(ncp_hdl_t ncpHdl,
                                        ncp_engine_type_t engine,
                                        ncp_uint32_t destInstance,
                                        ncp_cow_queue_index_map_t *queueIndexMap);

/*!
 *
 *  @}
 */

#ifdef __cplusplus
}
#endif

/*!
 *
 *  @}
 *
 */

#endif /* #ifndef _NCP_TASK_TRACE_H_ */
