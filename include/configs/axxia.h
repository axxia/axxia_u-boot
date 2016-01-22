/*
 * Copyright (C) 2015 Intel
 *
 * Common definitions for Axxia.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __AXXIA_H
#define __AXXIA_H

#define CONFIG_AXXIA

#define CONFIG_AXXIA_SERIAL

/*
 */

#define CONFIG_LSI_NCR

#ifndef __ASSEMBLY__
void ncr_tracer_enable(void);
void ncr_tracer_disable(void);
int ncr_tracer_is_enabled(void);
void ncr_sysmem_init_mode_enable(void);
void ncr_sysmem_init_mode_disable(void);
#endif

/*
  ==============================================================================
  ==============================================================================
  Parameters
  ==============================================================================
  ==============================================================================
*/

#ifndef __ASSEMBLY__

#define PARAMETERS_MAGIC 0x12af34ec

#define PARAMETERS_GLOBAL_SET_VOLTAGE      0x00000001
#define PARAMETERS_GLOBAL_SET_CLOCKS       0x00000002
#define PARAMETERS_GLOBAL_SET_PEI          0x00000004
#define PARAMETERS_GLOBAL_SET_SMEM         0x00000008
#define PARAMETERS_GLOBAL_SET_CMEM         0x00000010
#define PARAMETERS_GLOBAL_ENABLE_RETENTION 0x00000020
#define PARAMETERS_GLOBAL_ENABLE_SW_MEM_MTEST 0x00800000
#define PARAMETERS_GLOBAL_ENABLE_SW_MEM_ADDR_TEST 0x01000000
#define PARAMETERS_GLOBAL_ENABLE_SW_MEM_DATA_TEST 0x02000000
#define PARAMETERS_GLOBAL_DISABLE_RESET    0x10000000
#define PARAMETERS_GLOBAL_RUN_CMEM_BIST    0x20000000
#define PARAMETERS_GLOBAL_RUN_SMEM_RANGES  0x40000000
#define PARAMETERS_GLOBAL_RUN_SMEM_BIST    0x80000000

typedef long long               ncp_int64_t;
typedef unsigned long long      ncp_uint64_t;
typedef unsigned                ncp_uint32_t;
typedef long                    ncp_int32_t;
typedef unsigned short          ncp_uint16_t;
typedef unsigned char           ncp_uint8_t;
typedef unsigned char           ncp_bool_t;
typedef void *                  ncp_dev_hdl_t;
typedef unsigned                ncp_region_id_t;

typedef enum {
	/* Generic Status Codes */
	NCP_ST_SUCCESS = 0,                /*!< Operation was successful */
	NCP_ST_ERROR   = 1,                /*!< */
	NCP_ST_NO_MEMORY = 2,              /*!< Out of host memory */
	NCP_ST_INTERNAL_ERROR = 3,         /*!< */
	NCP_ST_INVALID_VALUE = 4,          /*!< */
	NCP_ST_INVALID_HANDLE = 5,         /*!< NCP Handle is either NULL or points to an invalid memory location  */
	NCP_ST_HANDLE_IN_USE = 6,          /*!< */
	NCP_ST_INVALID_PARAMETER = 7,      /*!< */
	NCP_ST_NOT_IMPLEMENTED = 8,        /*!< */
	NCP_ST_NVM_ERROR       = 9,        /*!< */
	NCP_ST_EOF             = 10,       /*!< */
	NCP_ST_PARSE_ERROR     = 11,       /*!< */
	NCP_ST_API_NOT_SUPPORTED = 12,     /*!< This API is not supported for this chip. */    
	NCP_ST_POLL_TIMEOUT      = 13,     /*!< The polling operation did complete within the specified time */
	NCP_ST_REF_COUNT_MISMATCH = 14,    /*!< ref count mismatch */

	/* ncp_map Interface Status Codes */
	NCP_ST_MAP_ERROR          = 101,   /*!< */
	NCP_ST_MAP_INTERNAL_ERROR = 102,   /*!< */
	NCP_ST_MAP_INVALID_MAP    = 103,   /*!< */
	NCP_ST_MAP_KEY_NOT_EXIST  = 104, /*!< */
	NCP_ST_MAP_INVALID_TYPE   = 105,   /*!< */
	NCP_ST_MAP_INVALID_INDEX  = 106,  /*!< */
	NCP_ST_MAP_INVALID_SEARCH = 107,   /*!< */
	NCP_ST_MAP_CALLBACK_ERROR = 108,   /*!< */

	/* ncp_config status codes */
	/*! No user defined configuration file read function
	 * was specified.
	 */
	NCP_ST_READFN_NULL        = 201,
	/*! The user specified configuration file is not a
	 *  valid config image
	 */
	NCP_ST_INVALID_CFG_FILE   = 202,
	/*! The user specified ACP device number exceeds
	 *  the maximum allowed value
	 */
	NCP_ST_INVALID_INSTANCE   = 203,
	/*!
	 * The "targetChipType" value specified in the .cfg map
	 * is incompatible with the current version of the hardware.
	 * E.g. trying to load a V2 configuration on a V1 chip.
	 */
	NCP_ST_INCOMPATIBLE_TARGET_DEVICE_REVISION = 204,

	/*! Invalid AMP configuration DomainID */
	NCP_ST_INVALID_DOMAIN_ID = 205,

	/*! Mismatch between current domain and domain-feature mapping */
	NCP_ST_SERVICE_UNAVAILABLE_ON_THIS_DOMAIN  = 206,

	/*! The user provided dynamic config modification callback
	 *  function did not succeed and the config load has been
	 *  aborted.
	 */
	NCP_ST_CONFIG_ABORTED                      = 207,
	/*! The requested ACP device configuration instance does not exist */
	NCP_ST_NOT_CONFIGURED                      = 208,

	/*! Cannot attach to this domain because configuration is not complete */
	NCP_ST_DOMAIN_NOT_CONFIGURED               = 209,

	/*! Cannot attach to this secondary domain because the primary domain
	 * has not yet been configured. */
	NCP_ST_PRIMARY_DOMAIN_NOT_CONFIGURED       = 210,

	NCP_ST_DOMAIN_NVM_BAD_ADDR                 = 211,
	NCP_ST_DOMAIN_NVM_BAD_SIZE                 = 212,
	/*! The NVM address in use by this domain overlaps system memory
	 * already in use by the OS for this or some other domain. */
	NCP_ST_DOMAIN_NVM_ADDR_OVERLAPS_OS         = 213,
	/*! The NVM address specified in the config image does not match
	 * the address being used by this domain. */
	NCP_ST_DOMAIN_NVM_ADDR_MISMATCH            = 214,
	/*! The NVM size specified in the config image does not match
	 * the size being used by this domain. */
	NCP_ST_DOMAIN_NVM_SIZE_MISMATCH            = 215,
	/*! The DMA address in use by this domain overlaps system memory
	 * already in use by the OS for this or some other domain. */
	NCP_ST_DOMAIN_DMA_BAD_ADDR                 = 216,
	NCP_ST_DOMAIN_DMA_BAD_SIZE                 = 217,
	NCP_ST_DOMAIN_DMA_ADDR_OVERLAPS_OS         = 218,
	/*! The DMA address specified in the config image does not match
	 * the address being used by this domain. */
	NCP_ST_DOMAIN_DMA_ADDR_MISMATCH            = 219,
	/*! The DMA size specified in the config image does not match
	 * the size being used by this domain. */
	NCP_ST_DOMAIN_DMA_SIZE_MISMATCH            = 220,

	/*! */
	NCP_ST_DOMAIN_RSVD_MEM_SIZE_MISMATCH       = 221,

	/*! The requested ACP device hardware has not been configured */
	NCP_ST_HW_NOT_CONFIGURED                   = 222,
	/*! The requested ACP device configuration instance is
	 * already configured and must be destroyed before it can
	 * be reconfigured.
	 */
	NCP_ST_ALREADY_CONFIGURED                  = 223,
	/*! The RTE release version string has an invalid value */
	NCP_ST_UNKNOWN_RELEASE_ID                  = 224,
	/*! The RTE cannot attach to the current NVM state because the
	 *  NVM state was created by a different version of the RTE software.
	 */
	NCP_ST_STATE_VERSION_MISMATCH              = 225,
	/*! The RTE cannot attach to the current NVM state after a host restart because
	 *  the NVM state and the current state of of the hardware may be inconsitent.
	 */
	NCP_ST_STATE_INCONSISTENT                  = 226,

	/* MUTEX function error codes */
	NCP_ST_MUTEX_ATTR_INIT_ERROR               = 301,    /*!< */
	NCP_ST_MUTEX_SHARED_INIT_ERROR             = 302,    /*!< */
	NCP_ST_MUTEX_INIT_ERROR                    = 303,    /*!< */
	NCP_ST_MUTEX_WAIT_ERROR                    = 304,    /*!< */
	NCP_ST_MUTEX_BUSY                          = 305,    /*!< */
	NCP_ST_MUTEX_TRYWAIT_ERROR                 = 306,    /*!< */
	NCP_ST_MUTEX_POST_ERROR                    = 307,    /*!< */
	NCP_ST_MUTEX_DESTROY_ERROR                 = 308,    /*!< */

	NCP_ST_PTHREAD_ONCE_ERROR                  = 309,    /*!< */
	NCP_ST_PTHREAD_SETSPECIFIC_ERROR           = 310,    /*!< */

	/* ncp_strlist Interface Status Codes */
	NCP_ST_STRLIST_INV_LIST                    = 401,    /*!< */
	NCP_ST_STRLIST_INV_NODE                    = 402,    /*!< */
	NCP_ST_STRLIST_INV_VALUE                   = 403,    /*!< */
	NCP_ST_STRLIST_INV_TYPE                    = 404,    /*!< */
	NCP_ST_STRLIST_INV_ITER                    = 405,    /*!< */
	NCP_ST_STRLIST_INV_CONV                    = 406,    /*!< */
	NCP_ST_STRLIST_INV_RANGE                   = 407,    /*!< */
	NCP_ST_STRLIST_ITEM_EXCEED                 = 408,    /*!< */

	/* Pattern API Status Codes */
	NCP_ST_AGEN_INVALID_HDL     = 501, /*!< Invalid handle */
	NCP_ST_AGEN_INVALID_INST    = 502, /*!< Invalid instruction (only while parsing FPO) */
	NCP_ST_AGEN_INVALID_FUNC    = 503, /*!< Invalid type of function */
	NCP_ST_AGEN_INVALID_OP      = 504, /*!< Invalid Operation on function */
	NCP_ST_AGEN_INVALID_INDEX   = 505, /*!< Invalid Index */
	NCP_ST_AGEN_INVALID_PTNWIDTH= 506, /*!< Invalid pattern width */
	NCP_ST_AGEN_VNUMS_EXHAUSTED = 507, /*!< Virtual numbers exhausted */
	NCP_ST_AGEN_INVALID_XSIZE   = 508, /*!< Invalid number of wild card bits */
	NCP_ST_AGEN_INVALID_UXSIZE  = 509, /*!< Invalid parent subnet size */
	NCP_ST_AGEN_NOT_YET_DONE    = 510, /*!< Not yet implemented */
	NCP_ST_AGEN_INVALID_PROGRAM_IMAGE = 511, /*!< Invalid program image */
	NCP_ST_AGEN_MEM_OVERFLOW    = 512, /*!< Out of tree memory */
	NCP_ST_AGEN_INVALID_FPO_VERSION   = 513,   /*!< Invalid FPO version */
	NCP_ST_AGEN_CB_ABORT        = 514, /*!< Operation aborted due to callback function */
	NCP_ST_AGEN_INVALID_FPO_BUFFER    = 515,   /*!< Invalid FPO buffer */
	NCP_ST_AGEN_INVALID_FPO_FILE_COOKIE = 516, /*!< Invalid FPO cookie */
	NCP_ST_AGEN_WRITE_EXCEEDS_TREESIZE  = 517, /*!< Write exceeds tree size */
	NCP_ST_AGEN_INVALID_TREE            = 518, /*!< Invalid tree id */
	NCP_ST_AGEN_INVALID_PTN             = 519, /*!< Invalid pattern */
	NCP_ST_AGEN_INVALID_ACTION          = 520, /*!< Invalid action */
	NCP_ST_AGEN_INVALID_CHECKPOINT      = 521, /*!< Invalid checkpoint */
	NCP_ST_AGEN_INVALID_CHECKPOINT_PROCESSOR = 522, /*!< Invalid chip specification in checkpoint */
	NCP_ST_AGEN_CHECKPOINT_READ_ERROR   = 523, /*!< Read error during checkpoint */
	NCP_ST_AGEN_CHECKPOINT_WRITE_ERROR  = 524, /*!< Write error during checkpoint */
	NCP_ST_AGEN_SYMBOL_TABLE_NOT_LOADED = 525, /*!< Symbol table not loaded */
	NCP_ST_AGEN_SYMBOL_NOT_FOUND        = 526, /*!< Symbol not found */
	NCP_ST_AGEN_INVALID_MODE            = 527, /*!< Invalid mode */
	NCP_ST_AGEN_INVALID_MODULE_NAME     = 528, /*!< Invalid module name */
	NCP_ST_AGEN_NO_FLOW_MEMORY          = 529, /*!< Not enough flow memory */

	/* Pattern API ISU related error codes */
	NCP_ST_AGEN_ISU_NOT_ENABLED         = 601, /*!< ISU not enabled */
	NCP_ST_AGEN_ISU_RMEM_TOO_SMALL      = 602, /*!< ISU - Rmem too small */
	NCP_ST_AGEN_ISU_FMEM_TOO_SMALL      = 604, /*!< ISU - Fmem too small */
	NCP_ST_AGEN_ISU_NEW_FN_NAME_CONFLICT    = 605, /*!< ISU - New function name conflicts */
	NCP_ST_AGEN_ISU_OLD_FN_NAME_MISMATCH    = 606, /*!< ISU - Old function name does not match */
	NCP_ST_AGEN_ISU_OLD_FN_TYPE_MISMATCH    = 607, /*!< ISU - Old function type does not match */
	NCP_ST_AGEN_ISU_OLD_FN_WIDTH_MISMATCH   = 608, /*!< ISU - Old function width does not match */
	NCP_ST_AGEN_ISU_OLD_FN_VSIZE_MISMATCH   = 609, /*!< ISU - Old function vsize does not match */
	NCP_ST_AGEN_ISU_OLD_FN_SRCFNS_MISMATCH  = 610, /*!< ISU - Old function source functions do not match */
	NCP_ST_AGEN_ISU_OLD_FN_SWIDTHS_MISMATCH = 611, /*!< ISU - Old function field widths do not match */
	NCP_ST_AGEN_ISU_DEL_FN_CALLER_EXISTS    = 612, /*!< ISU - Cannot delete function. A caller exists */
	NCP_ST_AGEN_ISU_VTREE_SRCFN_INVALID     = 613, /*!< ISU - Source function invalid for virtual tree */

	/* Pattern API scan related error codes */
	NCP_ST_AGEN_SCAN_REGEX_MISSING_PAREN    = 701,      /*!< Scan expression - missing parenthesis */
	NCP_ST_AGEN_SCAN_REGEX_MISSING_BRACE    = 702,      /*!< Scan expression - missing brace */
	NCP_ST_AGEN_SCAN_REGEX_INVALID_INTERVAL = 703,      /*!< Scan expression - invalid interval */
	NCP_ST_AGEN_SCAN_REGEX_MALFORMED_QUANTIFIER = 704,  /*!< Scan expression - malformed quantifier */
	NCP_ST_AGEN_SCAN_REGEX_UNEXPECTED_TOKEN = 705,      /*!< Scan expression - invalid token */

	/* NCP driver status codes */
	/*! The user specified ACP device number exceeds the maximum value */
	NCP_ST_DEV_INVALID_DEVICE_NUMBER         = 801,
	/*! The driver could not find the specified device */
	NCP_ST_DEV_DEVICE_NOT_FOUND              = 802,
	/*! An operating system call returned ENOENT
	 * (No such file or directory )
	 */
	NCP_ST_DEV_DEVICE_FILE_NOT_FOUND         = 803,
	/*! An error occurred during device driver configuration */
	NCP_ST_DEV_DEVICE_CONFIG_ERROR           = 804,
	/*! A device driver IOCTL call returned EINVAL */
	NCP_ST_DEV_INVALID_IOCTL_COMMAND         = 805,
	/*! A device driver OSE BIOS call returned EINVAL */
	NCP_ST_DEV_INVALID_BIOS_COMMAND          = 806,
	/*! The device-level API was called with an invalid devHdl */
	NCP_ST_DEV_INVALID_HANDLE                = 807,
	/*! The device-level API was called with an invalid buffer */
	NCP_ST_DEV_INVALID_BUFFER                = 808,
	/*! The device-level API was called with an invalid value for the flags */
	NCP_ST_DEV_INVALID_FLAGS                 = 809,
	/*! The device-level API was called with an invalid regionId */
	NCP_ST_DEV_INVALID_REGION_ID             = 810,
	/*! The attempted configuration I/O request is not supported
	 * for the specified regionId
	 */
	NCP_ST_DEV_INVALID_ACCESS                = 811,
	/*! There is no bus address mapped to access the requested region */
	NCP_ST_DEV_INVALID_PAGE_ACCESS           = 812,
	/*! The requested access width is not supported for the requested region */
	NCP_ST_DEV_INVALID_WIDTH                 = 813,
	/*! The requested offset is not supported for the requested region */
	NCP_ST_DEV_INVALID_OFFSET                = 814,
	/*! The requested command is not supported for the requested region */
	NCP_ST_DEV_INVALID_COMMAND               = 815,
	/*! The requested offset is not aligned with the requested transfer width */
	NCP_ST_DEV_UNALIGNED_OFFSET              = 816,
	/*! An operating system call failed for unexpected reasons */
	NCP_ST_DEV_UNMAPPED_ERROR                = 817,
	/*! memory allocation failed */
	NCP_ST_DEV_NO_MEMORY                     = 818,

	/*! An NCA PIO operation failed with an apparent bus error */
	NCP_ST_DEV_IO_ERROR                      = 819,
	/*! An NCA PIO operation completed with failed status  */
	NCP_ST_DEV_PIO_FAILED                    = 820,
	/*! An NCA PIO operation did not complete */
	NCP_ST_DEV_PIO_SW_TIMEOUT                = 821,
	/*! An NCA PIO operation failed with a Timeout error */
	NCP_ST_DEV_PIO_TIMEOUT_ERR               = 822,
	/*! An NCA PIO operation failed with a Decode error */
	NCP_ST_DEV_PIO_DECODE_ERR                = 823,
	/*! An NCA PIO operation failed with a Node error */
	NCP_ST_DEV_PIO_NODE_ERR                  = 824,
	/*! An NCA PIO operation failed with a Wrong Ack error */
	NCP_ST_DEV_PIO_WRONG_ACK_ERR             = 825,
	/*! An NCA PIO operation failed with a Ack Timeout error */
	NCP_ST_DEV_PIO_ACK_TIMEOUT_ERR           = 826,
	/*! An NCA PIO operation failed with a Unclaimed Header error */
	NCP_ST_DEV_PIO_UNCLAIMED_HDR_ERR         = 827,
	/*! An NCA PIO operation failed with a Ring0 Parity error */
	NCP_ST_DEV_PIO_RING0_PARITY_ERR          = 828,
	/*! An NCA PIO operation failed with a Ring1 Parity error */
	NCP_ST_DEV_PIO_RING1_PARITY_ERR          = 829,
	/*! An NCA PIO operation failed with a Ring2 Parity error */
	NCP_ST_DEV_PIO_RING2_PARITY_ERR          = 830,
	/*! Reserved */
	NCP_ST_DEV_INTERRUPTED                   = 831,
	/*! Target HW RTE Mismatch */
	NCP_ST_DEV_WRONG_TARGET_HW               = 832,

	NCP_ST_DEV_EVENT_TYPE_INVALID            = 833,     /*!< */
	NCP_ST_DEV_EVENT_CBK_INVALID             = 834,     /*!< */
	NCP_ST_DEV_EVENT_HDL_INVALID             = 835,     /*!< */
	NCP_ST_DEV_EVENT_HANDLER_IN_USE          = 836,     /*!< */

	NCP_ST_DEV_DMA_DISABLED                  = 837,     /*!< */
	NCP_ST_DEV_PCQ_TIMEOUT                   = 838,     /*!< */

	NCP_ST_DEV_ISR_ALREADY_REGISTERED        = 839,     /*!< */
	NCP_ST_DEV_ISR_NOT_REGISTERED            = 840,     /*!< */
	NCP_ST_DEV_CANT_MAP_VIRQ                 = 841,     /*!< */
	NCP_ST_DEV_CANT_SET_IRQ_TYPE             = 842,     /*!< */
	NCP_ST_DEV_REQUEST_IRQ_ERR               = 843,     /*!< */

	/*! An NCA PIO operation was unable to obtain the domain synchronization lock */
	NCP_ST_DEV_DOMAIN_LOCK_TIMEOUT           = 844,

	/* Errors related to L2C indirect accesses */
	/*! Unable to read/write because L2Cs being held in reset. */
	NCP_ST_DEV_L2C_RESET_ERROR               = 845,
	/*! L2C offset is out of range. */
	NCP_ST_DEV_L2C_INVALID_OFFSET            = 846,
	/*! L2C region reference not supported on current device. */
	NCP_ST_DEV_L2C_INVALID_REGIONID          = 847,
	/*! L2C virtual target reference is invalid. */
	NCP_ST_DEV_L2C_INVALID_TARGET            = 848,

	/* Errors related to various trace indirect accesses */
	/*! L2C offset is out of range. */
	NCP_ST_DEV_TRACE_INVALID_OFFSET          = 849,
	/*! L2C region reference not supported on current device. */
	NCP_ST_DEV_TRACE_INVALID_REGIONID        = 850,

	/*! attempted access over LBI interface has timed out */
	NCP_ST_DEV_LBI_NOT_SUPPORTED             = 851,
	NCP_ST_DEV_LBI_ACCESS_TIMEOUT            = 852,
	NCP_ST_DEV_LBI_CS_INVALID                = 853,
	NCP_ST_DEV_LBI_CS_NOT_CONFIGURED         = 854,
	NCP_ST_DEV_LBI_CS_DEV_WIDTH_INVALID      = 855,
	NCP_ST_DEV_LBI_GPIO_SEL_INVALID          = 856,
	NCP_ST_DEV_LBI_GPIO_MODE_INVALID         = 857,
	NCP_ST_DEV_LBI_GPIO_SEL_NOT_CONFIGURED   = 858,
	NCP_ST_DEV_LBI_GPIO_IN_USE               = 859,
	NCP_ST_DEV_LBI_INTR_SEL_INVALID          = 860,

	NCP_ST_DEV_INVALID_VAT_POOL_ID           = 861, /*!< the specified VAT Pool ID is invalid */
	NCP_ST_DEV_INVALID_VAT_POOL_ENTRY        = 862, /*!< the specified VAT Pool entry is not valid */

	NCP_ST_EDEV_INIT_FAILED                  = 863, /*!< */
	NCP_ST_EDEV_FINI_FAILED                  = 864, /*!< */

	NCP_ST_HWIO_TRACE_BUSY                   = 865, /*!< */

	NCP_ST_DEV_APB2SER_INDIRECT_TIMEOUT      = 866, /*!< the APB2SER indirect access timed out */

	/* PLL status codes */
	/*! The PLL handle contained in the ncp handle provided is not valid. */
	NCP_ST_PLL_HANDLE_INVALID                = 901,
	/*! Initialization of the PLL state protection semaphore failed. */
	NCP_ST_PLL_SEM_INIT_ERROR                = 902,
	/*! The frequency(ies) specified for the PLL are not supported */
	NCP_ST_PLL_FREQUENCY_INVALID             = 903,
	/*! The PLL operations is not supported on this device */
	NCP_ST_PLL_OPERATION_NOT_SUPPORTED       = 904,

	/* NS module status codes */
	NCP_ST_NS_INVALID_VALUE                  = 1001,                 /*!< */
	NCP_ST_NS_MEM_INIT_ERROR                 = 1002,                /*!< */
	/*! Undefined engine for read/info request */
	NCP_ST_NS_ENGINE_UNKNOWN                 = 1003,
	/*! Undefined entry for read/info request */
	NCP_ST_NS_ENTRY_OUT_OF_RANGE             = 1004,
	/*! Buffer too small for read/info request */
	NCP_ST_NS_BUFFER_TOO_SMALL               = 1005,

	/*!
	 * We can not access entries from the
	 * specific table (engine), because no namespaces
	 * have been defined for that table.
	 */
	NCP_ST_NS_NO_NAMESPACES_DEFINED          = 1006,

	/*!
	 * The given absolute namespace entry ID does not
	 * fall into any any Namespace defined in the
	 * configuration.
	 */
	NCP_ST_NS_ENTRY_ID_INVALID               = 1007,
	/*!
	 * Missing the required Callback function to configure
	 * the Base Registers or Static Entries.
	 */
	NCP_ST_NS_CALLBACK_MISSING               = 1008,

	/*!
	 * This happens when we detect there are static
	 * entries defined either under the FPL-managed
	 * Namespace or for the table with no callback
	 * to configure them.
	 */
	NCP_ST_NS_CANNOT_HAVE_STATIC_ENTRIES     = 1009,

	/*!
	 * The relative ID of a Nameespace Entry
	 * is greater than 'numEntries'
	 */
	NCP_ST_NS_ENTRY_ID_TOO_BIG               = 1010,
	/*!
	 * The Namespace Entry is not valid in this domain
	 */
	NCP_ST_NS_ENTRY_INVALID_IN_DOMAIN        = 1011,
	/*!
	 * The specified subtable is invalid
	 */
	NCP_ST_NS_INVALID_SUBTABLE               = 1012,

	/* RSRC module status codes */
	NCP_ST_RSRC_INIT_FAILED                  = 1101, /*! Initialization of the RSRC module failed. */
	NCP_ST_RSRC_INSUFF_IDS_AVAIL             = 1102, /*! Insufficient Ids configured in the RSRC to satify the request. */
	NCP_ST_RSRC_INSUFF_IDS_AVAIL_IN_RANGE    = 1103, /*! Insufficient contiguous Ids available in the RSRC currently to satify the request. */
	NCP_ST_RSRC_READ_ONLY                    = 1104, /*! RSRC is marked 'read only' and can not be changed. */

	/* PAB module status codes */
	NCP_ST_PAB_MEM_INIT_ERROR                = 1201, /*!< Failure to initialize one of PAB's memory regions */
	NCP_ST_PAB_INVALID_SHIFT_VALUE           = 1202, /*!< Invalid shift value observed for config of one of PAB's memory tables */
	NCP_ST_PAB_INVALID_VALUE                 = 1203, /*!< Invalid configuration argument observed */

	/* PIC codes */
	NCP_ST_PIC_INVALID_VALUE                 = 1301, /*!< Invalid configuration argument observed */

	/* PKA codes */
	NCP_ST_PKA_NOT_INSTALLED                 = 1401, /*!< PKA module not present in hardware */
	NCP_ST_PKA_NOT_AVAILABLE                 = 1402, /*!< PKA module not available; may be offline or otherwise out of service */
	NCP_ST_PKA_INVALID_VALUE                 = 1403, /*!< Invalid function argument or argument value observed */
	NCP_ST_PKA_INVALID_ARGUMENT_LENGTHS      = 1404, /*!< Combinations of argument lengths invalid for current operation, or too large for available memory */
	NCP_ST_PKA_OPERATION_NOT_RUNNING         = 1405, /*!< PKA operation expected to be running, but no operation is in progress */
	NCP_ST_PKA_OPERATION_IN_PROGRESS         = 1406, /*!< PKA module expected to be idle, but an operation is in progress */
	NCP_ST_PKA_INSUFFICIENT_ARGUMENT_LENGTHS = 1407, /*!< The pre-allocated size of one or more of the results arguments is insufficient to hold the calculated results. */

	/* TRNG codes */
	NCP_ST_TRNG_NOT_INSTALLED                = 1501, /*!< TRNG module not present in hardware */
	NCP_ST_TRNG_INVALID_VALUE                = 1502, /*!< Invalid function argument or argument value observed */
	NCP_ST_TRNG_RESEED_TIMEOUT               = 1503, /*!< Timeout failure reseeding the TRNG module */
	NCP_ST_TRNG_BIST_ERROR                   = 1504, /*!< Invalid response from BIST_SIG register during reseed of the TRNG module */
	NCP_ST_TRNG_FIPS_OUT_ERROR               = 1505, /*!< Failure initializing the TRNG module */
	NCP_ST_TRNG_STS_ERROR                    = 1506, /*!< TRNG (ACP2500) STS device failure */
	NCP_ST_TRNG_STS_GENERATE_ERROR           = 1507, /*!< TRNG (ACP2500) STS command generation failure */
	NCP_ST_TRNG_STS_INVALID_DATA_ERROR       = 1508, /*!< TRNG (ACP2500) STS invalid data generation failure */
	NCP_ST_TRNG_DOUT_VALUE_TIMEOUT           = 1509, /*!< TRNG (ACP2500) Timeout failure waiting for valid data */


	/* SPP codes */

	/*!
	 * Could not drain packets out of the
	 * SPP, while trying to upgrade the Firmware.
	 */
	NCP_ST_SPP_PACKET_DRAIN_FAILED           = 1601,

	/*!
	 * Trying to call an SPP API while SPP
	 * is not configured. This usually means
	 * the "Engines/SPP" element was not present
	 * in the config map.
	 */
	NCP_ST_SPP_NOT_CONFIGURED                = 1602,
	/*!
	 * Could not find a Firmware Script with a given name
	 */
	NCP_ST_SPP_DEVICE_UNKNOWN                = 1603,
	/*!
	 * Could not find a Firmware Script with a given name
	 */
	NCP_ST_SPP_FW_INV_SCRIPT_NAME            = 1604,
	/*!
	 * Returned by ncp_spp_fw_script_name_get()
	 * when a script with a given ID does not exist.
	 */
	NCP_ST_SPP_FW_INV_SCRIPT_ID              = 1605,
	/*!
	 * Indicates that SPP Firmware in the .cfg file is
	 * a wrong binary, corrupted, or incorrectly generated.
	 */
	NCP_ST_SPP_FW_FILE_INVALID               = 1606,
	/*!
	 * The .cfg file does not include the firmware binary.
	 */
	NCP_ST_SPP_FIRMWARE_MISSING              = 1607,
	/*!
	 * A Firmware script required by the "_context_set" API
	 * is missing from the current SPP Firmware image.
	 * This error code indicates that application tried to use
	 * protocol/algorithm combination not supported by the
	 * loaded Firmware, so a different image needs to be
	 * specified in the XML file by using
	 * "Engines/SPP/sppFirmwareFile" attribute.
	 */
	NCP_ST_SPP_CTX_SCRIPT_MISSING            = 1608,
	/*!
	 * Indicates that context pre-compute crypto library
	 * has not been installed. The default RTE package
	 * does not contain the cipher/hash algorithm
	 * implementation needed to perform "context_set"
	 * API call for some of the algorithms. In order
	 * to resolve this error please install the
	 * RTE add-on package that contains the missing
	 * library.
	 */
	NCP_ST_SPP_CTX_LIBRARY_MISSING           = 1609,
	/*!
	 * The context is not set/disabled
	 */
	NCP_ST_SPP_CTX_DISABLED                  = 1610,
	/*!
	 * The "protocol" enum value is invalid.
	 */
	NCP_ST_SPP_CTX_PROTO_INVALID             = 1611,
	/*!
	 * A 4-byte "fresh" value must be specified
	 * for a given 3GPP context.
	 */
	NCP_ST_SPP_CTX_NEED_4B_FRESH             = 1612,
	/*!
	 * The "fresh" value is not needed for a
	 * given 3GPP context, so it must be left empty.
	 */
	NCP_ST_SPP_CTX_FRESH_NOT_NEEDED          = 1613,

	/*!
	 * The authentication enum value is invalid.
	 */
	NCP_ST_SPP_CTX_AUTH_INVALID              = 1614,
	/*!
	 * The "NULL_GMAC" encryption choice shall only
	 * be used with GMAC authentication algorithms.
	 */
	NCP_ST_SPP_CTX_AUTH_MUST_BE_GMAC         = 1615,
	/*!
	 * The authentication must be set to NULL
	 * when GCM/CCM combined mode is selected as
	 * an encryption algorithm, because it does
	 * both encryption and authentication.
	 */
	NCP_ST_SPP_CTX_AUTH_MUST_BE_NULL         = 1616,
	/*!
	 * The combination of encryption and
	 * authentication algorithms (which may be
	 * meaningful otherwise) is not supported
	 * by the Firmware for the given protocol.
	 * Such combinations must be listed as
	 * "restrictions" in the documentation for
	 * the given "context_set" API.
	 */
	NCP_ST_SPP_CTX_COMB_NOT_SUPPORTED        = 1617,

	/*!
	 * The length of the authentication key is invalid
	 * for the chosen authentication algorithm.
	 */
	NCP_ST_SPP_CTX_AUTH_KEY_LEN_INVALID      = 1618,
	/*!
	 * Encryption is not supported by the device.
	 */
	NCP_ST_SPP_CTX_ENCR_NOT_SUPPORTED        = 1619,
	/*!
	 * The encryption enum value is invalid.
	 */
	NCP_ST_SPP_CTX_ENCR_INVALID              = 1620,
	/*!
	 * In order to perform AES-GMAC authentication
	 * for ESP with no encryption, the "encr" value
	 * must be set to 'NULL_GMAC'
	 */
	NCP_ST_SPP_CTX_ENCR_MUST_BE_NULL_GMAC    = 1621,
	/*!
	 * The length of the encryption key is invalid
	 * for the chosen encryption algorithm.
	 */
	NCP_ST_SPP_CTX_ENCR_KEY_LEN_INVALID      = 1622,
	/*!
	 * The chosen combination of encryption/authentication
	 * algorithms requires a 4-byte "salt" parameter
	 * to be specified.
	 */
	NCP_ST_SPP_CTX_NEED_4B_SALT              = 1623,
	/*!
	 * The ASE-CCM requires a 3-byte "salt"
	 * parameter to be specified.
	 */
	NCP_ST_SPP_CTX_NEED_3B_SALT              = 1624,
	/*!
	 * The chosen combination of encryption/authentication
	 * algorithm does not require the "salt" parameter,
	 * so it must not be specified.
	 */
	NCP_ST_SPP_CTX_SALT_NOT_NEEDED           = 1625,

	/*!
	 * If the "Extended Sequene Number" flag
	 * is true, then Anti-replay must be enabled
	 * for Inbound contexts and Sequence Number
	 * Rollover must be disabled for the Outbound.
	 */
	NCP_ST_SPP_CTX_NEED_ANTI_REPLAY_IN_ESN   = 1626,

	/*!
	 * SRTP Context: invalid length of the 'saltKey' parameter.
	 */
	NCP_ST_SPP_CTX_SALT_KEY_LEN_INVALID      = 1627,
	/*!
	 * The authTagLen is too big for the given authentication.
	 */
	NCP_ST_SPP_CTX_AUTH_TAG_LEN_INVALID      = 1628,
	/*!
	 * The context lifetime is invalid. Currently, it
	 * is returned for SRTP/SRTCP when the specified
	 * packet lifetime is larger than what's allowed
	 * by the protocol
	 */
	NCP_ST_SPP_CTX_LIFETIME_INVALID          = 1629,
	/*!
	 * Invalid Anti-replay window size was given
	 * to a "_context_set" API. The SPP only
	 * supports the sizes defined by
	 * by ::ncp_spp_arw_size_t enum
	 */
	NCP_ST_SPP_CTX_ARW_SIZE_INVALID          = 1630,
	/*!
	 * Generic context: if 'cntPresentLifetimeEn'
	 * is true, the 'countersPresent' must be
	 * true as well.
	 */
	NCP_ST_SPP_CTX_COUNTERS_MUST_BE_PRESENT  = 1631,

	/*!
	 * <b>TLS Context</b>: the length of the "iv" parameter is
	 * incorrect. See description in ::ncp_spp_tls_context_t
	 * for correct values. <br>
	 * <b> Generic Context/Algorithmic Only Acceleration </b> The "iv" 
	 * length is larger
	 * than the maximum allowed by the architecture.
	 */
	NCP_ST_SPP_CTX_IV_INVALID                = 1632,
	/*!
	 * Generic Context: the given cipher state is too large.
	 */
	NCP_ST_SPP_CTX_CIPHER_STATE_INVALID      = 1633,
	/*!
	 * "truncatedHmac" option is not supported
	 * by the SSL protocol
	 */
	NCP_ST_SPP_TRUNCATED_HMAC_INVALID_FOR_SSL = 1634,

	/*!
	 * The specified context configuration takes more
	 * memory than "entrySize" parameter for the
	 * "SPPSecurityContexts" Namespace sub-table where the
	 * Context ID is taken from.
	 * This context should use an ID from a different
	 * Namespace, where "entrySize" is sufficient.
	 * Note, you can determine the minimum required
	 * "entrySize" by using a "_context_size" API for
	 * the corresponding protocol.
	 */
	NCP_ST_SPP_CTX_TOO_BIG                   = 1635,

	/*!
	 * Returned by any SPP API reading a context
	 * when it detects an inconsistency in the
	 * context Data Structure (as read from the
	 * System Memory).
	 */
	NCP_ST_SPP_CTX_INVALID                   = 1636,

	/*!
	 * Returned by ncp_spp_context_counters_get()
	 * when it detects that counters are not
	 * present in the Context Record. NOTE:
	 * not returning this error code does <b>not</b>
	 * guarantee that the counters were there. If
	 * the counters are missing, it is possible for
	 * the API to mis-interpret some other field
	 * (e.g. anti-replay window bitmask) for the
	 * counters and retrieve invalid values.
	 */
	NCP_ST_SPP_CTX_COUNTERS_MISSING          = 1637,
	/*!
	 *  ICV length is invalid and does not match what is expected for that
	 * authentication type. returned by algorithmic acceleration context
	 *  set API.
	 */
	NCP_ST_SPP_CTX_ICV_LEN_INVALID           = 1638,

	/*!
	 *  word3 has to be present to indicate the length of SA when AID_SRC is
	 *  SA. This message is printed when the AIDSRC is SA and word3 is
	 *  missing.
	 */
	NCP_ST_SPP_CTX_WORD3_MISSING_AIDSRC_SA   = 1639,

	/*!
	 * AID length exceeded maximum size of 256.  
	 */
	NCP_ST_SPP_CTX_AID_LEN_MAX_256_EXCEED    = 1640,


	/* TIMER codes */
	/*! The specified Timer class is not valid. */
	NCP_ST_TIMER_INVALID_CLASS               = 1701,
	/*! The specified Timer index is not valid. */
	NCP_ST_TIMER_INVALID_INDEX               = 1702,
	/*! The specified Timer handle is not valid. */
	NCP_ST_TIMER_INVALID_HANDLE              = 1703,
	/*! The specified queue ID is not valid. */
	NCP_ST_TIMER_INVALID_QUEUE_ID            = 1704,
	/*! The specified Timer flag combination is not valid. */
	NCP_ST_TIMER_INVALID_FLAGS               = 1705,
	/*! There is no available Timer index. */
	NCP_ST_TIMER_NO_INDEX                    = 1706,
	/*! Initialization of the Timer module failed. */
	NCP_ST_TIMER_INIT_FAILED                 = 1707,
	/*! There is no valid Virtual Pipeline for Timer tasks. */
	NCP_ST_TIMER_NO_VALID_VP                 = 1708,
	/*! There is no valid Timer class handler for the specified class. */
	NCP_ST_TIMER_NO_VALID_CLASS_HANDLER      = 1709,
	/*! The reference strobe was triggered when the strobe output was not enabled. */
	NCP_ST_TIMER_REF_STROBE_OUTPUT_NOT_ENABLED = 1710,
	/*! Initialization of the Timer state protection semaphore failed. */
	NCP_ST_TIMER_SEM_INIT_ERROR                = 1711,
	/*! An invalid reference clock was specified. */
	NCP_ST_TIMER_INVALID_REFCLK                = 1712,
	/*! The CPU Timer was not stopped beforehand. */
	NCP_ST_TIMER_CPU_TIMER_NOT_STOPPED         = 1713,
	/*! The CPU Timer was not started beforehand. */
	NCP_ST_TIMER_CPU_TIMER_NOT_STARTED         = 1714,
	/*! The CPU Timer index has not been allocated. */
	NCP_ST_TIMER_CPU_TIMER_NOT_ALLOCATED       = 1715,
	/*! The specified Timer thread handle is not valid. */
	NCP_ST_TIMER_INVALID_THREAD_HANDLE         = 1716,
	/*! The specified Timer thread handle is still in use and cannot be freed. */
	NCP_ST_TIMER_THREAD_HANDLE_IN_USE          = 1717,
	/*! The specified Timer operation is not valid for the thread's TQS. */
	NCP_ST_TIMER_INVALID_OPERATION_FOR_TQS     = 1718,

	/* SMON codes */
	/*! The specified SMON module is not valid. */
	NCP_ST_SMON_INVALID_MODULE                 = 1801,
	/*! The specified SMON submodule is not valid. */
	NCP_ST_SMON_INVALID_SUBMODULE              = 1802,
	/*! The specified timer prescale value is not valid. */
	NCP_ST_SMON_INVALID_PRESCALE               = 1803,
	/*! The specified function value is not valid for the architecture. */
	NCP_ST_SMON_INVALID_FUNCTION               = 1804,
	/*! The specified function value is not valid for the architecture. */
	NCP_ST_SMON_INVALID_MODE                   = 1805,
	/*! A specified Mux value is not valid. */
	NCP_ST_SMON_INVALID_MUX                    = 1806,
	/*! A specified Mux mode value is not valid. */
	NCP_ST_SMON_INVALID_MUX_MODE               = 1807,
	/*! A specified Mux mode value is not valid. */
	NCP_ST_SMON_INVALID_PARAM                  = 1808,

	/* MMB codes */
	/*! The calculated MMB memory size does not match that included in the config map. */
	NCP_ST_MMB_INVALID_MEM_SIZE                = 1901,
	/*! The specified task or non-task threshold is not valid. */
	NCP_ST_MMB_INVALID_THRESHOLD               = 1902,
	/*! Static configuration of the MMB failed. */
	NCP_ST_MMB_INIT_FAILED                     = 1903,

	/* MME codes */
	/*! The specified mPCQ index is out of range. */
	NCP_ST_MME_INVALID_MPCQ_ID                 = 2001,
	/*! The specified mPCQ entry size is invalid. */
	NCP_ST_MME_INVALID_MPCQ_ENTRY_SIZE         = 2002,
	/*! The specified pool index is out of range. */
	NCP_ST_MME_INVALID_POOL_ID                 = 2003,
	/*! The specified pool size is invalid. */
	NCP_ST_MME_INVALID_BLOCK_SIZE              = 2004,
	/*! Static configuration of the MME failed. */
	NCP_ST_MME_INIT_FAILED                     = 2005,
	/*! The MME handle is invalid. */
	NCP_ST_MME_INVALID_HANDLE                  = 2006,
	/*! The MME CAT data format is invalid. */
	NCP_ST_MME_CAT_INVALID_FORMAT              = 2007,
	/*! After a pool flush, IFLS activity doesn't stop. */
	NCP_ST_MME_FLUSH_IFLS_NOT_STOPPED          = 2008,
	/*! After a pool flush, MREF activity doesn't stop. */
	NCP_ST_MME_FLUSH_MREF_NOT_STOPPED          = 2009,
	/*! After a pool flush, MPCQ activity doesn't stop. */
	NCP_ST_MME_FLUSH_MPCQ_NOT_STOPPED          = 2010,
	/*! The configured pool size is invalid. */
	NCP_ST_MME_INVALID_POOL_SIZE               = 2011,
	/*! Fixed pool is exhausted or can't allocate the requested size. */
	NCP_ST_MME_FIXPOOL_EXHAUSTED		= 2012,
	/*! Semaphore initialization failed */
	NCP_ST_MME_FIXPOOL_SEM_INIT_ERROR		= 2013,

	/*!< Semaphore initialization failed */
	NCP_ST_MME_FIXPOOL_INVALID_BLKID		= 2014,
	/*!< fixpool buffer registration failed */
	NCP_ST_MME_FIXPOOL_REGISTER_ERROR 		= 2015,
	/*!< registration attempt didn't find the entry in free pool.
	  may be it is already allocated. (not crirical error.)*/
	NCP_ST_MME_FIXPOOL_REGISTER_NODE_NOT_FOUND	= 2016,
	/*!< fixpool alloation failed due to boundary check not
	  being able to be satisfied. */
	NCP_ST_MME_FIXPOOL_ALLOC_BOUNDARY_ERR 	= 2017,
	/*!< Fixpool buffer free error. couldn't insert.. */
	NCP_ST_MME_FIXPOOL_FREE_ERROR		= 2018,
	/*!< Fixpool buffer register. Address not in range.. */
	NCP_ST_MME_FIXPOOL_REGISTER_ADDR_NOT_IN_RANGE = 2019,
	/*!< Fixpool operation; ncp_malloc() failure.. */
	NCP_ST_MME_FIXPOOL_ALLOC_FAILURE		= 2020,
	/*!< Fixpool buffer not in used list. */
	NCP_ST_MME_FIXPOOL_NOT_IN_USED_LIST		= 2021,
	/*!< Fixpool buffer not in used list. */
	NCP_ST_MME_FIXPOOL_ADDR_IN_USE		= 2022,
	/*!< Fixpool buffer in use as Rx. cant register for Rx again. */
	NCP_ST_MME_FIXPOOL_REGISTER_NODE_RXADDR_DUPLICATE = 2023,
	/*!< invalid direction */
	NCP_ST_MME_FIXPOOL_INVALID_DIR		= 2024,
	/*!< invalid size */
	NCP_ST_MME_FIXPOOL_INVALID_SIZE		= 2025,
	/*!< found in used pool but size not matching */
	NCP_ST_MME_FIXPOOL_USED_SIZE_MISMATCH	= 2026,

	/* PBM codes */
	/*! The PBM initialization routine failed */
	NCP_ST_PBM_INIT_FAILED                     = 2101,

	/* MTM codes */
	/*!
	 * The MTM handle contained in the ncp handle provided is not valid.
	 * This could happen if an MTM API is called when there is no MTM
	 * defined in the configuration.
	 */
	NCP_ST_MTM_HANDLE_INVALID                  = 2201,
	/*! Initialization of the MTM state protection semaphore failed. */
	NCP_ST_MTM_SEM_INIT_ERROR                  = 2202,
	/*! The rate rounding algorighm specified is invalid. */
	NCP_ST_MTM_RATE_ROUNDING_ALG_INVALID       = 2203,

	/*! The scheduling mode specified is not valid. */
	NCP_ST_MTM_SCHEDULING_MODE_INVALID         = 2204,
	/*!
	 * The parent scheduler already has a child at the strict priority
	 * level specified.
	 */
	NCP_ST_MTM_PRIORITY_LEVEL_IN_USE           = 2205,
	/*! A node in strict scheduling mode can not use PR/MR shaping mode. */
	NCP_ST_MTM_MR_IN_STRICT_MODE               = 2206,
	/*! The shaping mode specified is not valid. */
	NCP_ST_MTM_SHAPING_MODE_INVALID            = 2207,
	/*!
	 * There is no time scale value that allows the programming of the
	 * specified shaping rate and bucket depth values.
	 */
	NCP_ST_MTM_SHAPING_RATES_INCOMPATIBLE      = 2208,
	/*! The peak rate specified is less that the secondary rate specified. */
	NCP_ST_MTM_SHAPING_PEAK_LESS_THAN_SECONDARY = 2209,
	/*! One of the bucket size specified is less that the maximum packet size.*/
	NCP_ST_MTM_SHAPING_BUCKET_LESS_THAN_MAX_PACKET = 2210,
	/*!
	 * There was an attempt to change settings of the HW shaper on a node
	 * that is not configured to use the HW shaper.
	 */
	NCP_ST_MTM_HW_SHAPER_NOT_IN_USE            = 2211,
	/*! The time scale value specified is invalid. */
	NCP_ST_MTM_TIME_SCALE_INVALID              = 2212,
	/*!
	 * The specified shaping rates and bucket depths can not be programmed
	 * using the specified time scale value.
	 */
	NCP_ST_MTM_TIME_SCALE_INCOMPATIBLE         = 2213,
	/*! The service quantum specified is invalid. */
	NCP_ST_MTM_SERVICE_QUANTUM_INVALID         = 2214,
	/*! The service quantum is not applicable on STRICT_P3 nodes */
	NCP_ST_MTM_SERVICE_QUANTUM_NOT_APPLICABLE  = 2215,
	/*! The length of the script parameters specified is invalid. */
	NCP_ST_MTM_PARAMETER_LENGTH_INVALID        = 2216,
	/*! The offset for a script parameter update is invalid. */
	NCP_ST_MTM_OFFSET_INVALID                  = 2217,

	/*! The scheduler spedified as the parent does not exist. */
	NCP_ST_MTM_PARENT_DOES_NOT_EXIST           = 2218,
	/*! The scheduler ID spedified as the parent is not valid. */
	NCP_ST_MTM_PARENT_ID_INVALID               = 2219,
	/*! The scheduler specified as the parent is in the process of draining */
	NCP_ST_MTM_PARENT_DRAINING                 = 2220,
	/*! Adding the child would result in too many children for the parent. */
	NCP_ST_MTM_TOO_MANY_CHILDREN               = 2221,
	/*!
	 * The scheduler ID spedified as the parent for this scheduler is not
	 * one level up in the scheduling hierarchy.
	 */
	NCP_ST_MTM_PARENT_HIER_LEVEL_INCORRECT     = 2222,

	/*! The specified scheduler ID already exists. */
	NCP_ST_MTM_SCHEDULER_EXISTS                = 2223,
	/*! The specified scheduler ID does not exist. */
	NCP_ST_MTM_SCHEDULER_DOES_NOT_EXIST        = 2224,
	/*! The specified scheduler ID is not valid. */
	NCP_ST_MTM_SCHEDULER_ID_INVALID            = 2225,
	/*! The scheduler arbitration mode specified is not valid. */
	NCP_ST_MTM_SCHEDULER_ARB_MODE_INVALID      = 2226,
	/*! The traffic shaping script ID is not valid. */
	NCP_ST_MTM_SCHEDULER_TS_SCRIPT_ID_INVALID  = 2227,
	/*!
	 * A traffic shaping script with the specified ID
	 * does not exist or is not loaded.
	 */
	NCP_ST_MTM_SCHEDULER_TS_SCRIPT_DOES_NOT_EXIST = 2228,
	/*!
	 * A traffic shaping script is required for schedulers that are
	 * configured to performing script shaping and arbitration.
	 */
	NCP_ST_MTM_SCHEDULER_TS_SCRIPT_REQUIRED    = 2229,
	/*!
	 * A traffic shaping script was specified for the scheduler and
	 * there already is a scheduler in this nodes path to the root
	 * that is running a traffic shaping script.
	 */
	NCP_ST_MTM_SCHEDULER_TS_ALREADY_RUNNING    = 2230,
	/*! The scheduler node still has children attached. */
	NCP_ST_MTM_SCHEDULER_HAS_CHILDREN          = 2231,
	/*! Timeout waiting for scheduler to become inactive */
	NCP_ST_MTM_SCHEDULER_WAIT_FOR_INACTIVE_TIMEOUT = 2232,
	/*! The value spedified for the average error is invaid. */
	NCP_ST_MTM_SCHEDULER_AVG_ERROR_INVALID     = 2233,

	/*! The specified queue ID already exists. */
	NCP_ST_MTM_QUEUE_EXISTS                    = 2234,
	/*! The specified queue ID does not exist. */
	NCP_ST_MTM_QUEUE_DOES_NOT_EXIST            = 2235,
	/*! The specified queue ID is not valid. */
	NCP_ST_MTM_QUEUE_ID_INVALID                = 2236,
	/*!
	 * There is no scheduler node in the queue's path to the root
	 * that is running a traffic shaping script.
	 */
	NCP_ST_MTM_QUEUE_NO_TS_RUNNING             = 2237,
	/*!
	 * The relative hierarchy level specified for the higher level
	 * traffic management script parameters is not valid.
	 */
	NCP_ST_MTM_QUEUE_TM_PARAMS_HIGHER_LEVEL_INVALID = 2238,
	/*!
	 * The relative hierarchy level specified for the higher level
	 * traffic shaping script parameters is not valid.
	 */
	NCP_ST_MTM_QUEUE_TS_PARAMS_HIGHER_LEVEL_INVALID = 2239,
	/*! The traffic management script ID is not valid. */
	NCP_ST_MTM_QUEUE_TM_SCRIPT_ID_INVALID      = 2240,
	/*!
	 * A traffic management script with the specified ID
	 * does not exist or is not loaded.
	 */
	NCP_ST_MTM_QUEUE_TM_SCRIPT_DOES_NOT_EXIST  = 2241,

	/*! The specified node ID is not valid. */
	NCP_ST_MTM_NODE_ID_INVALID                 = 2242,
	/*!
	 * An attempt was made to drain or remove a queue, or drain scheduler
	 * while the drain mechanism is already busy.
	 */
	NCP_ST_MTM_DRAIN_BUSY                      = 2243,
	/*! An attempt to stop enqueues in order to drain a node timed out */
	NCP_ST_MTM_DRAIN_ENQUEUE_STOP_TIMEOUT      = 2244,
	/*! Draining of equeued tasks did not complete in the time specified */
	NCP_ST_MTM_DRAIN_TIMEOUT                   = 2245,
	/*! Attempt to remove or drain a node that is currently being drained */
	NCP_ST_MTM_NODE_DRAINING                   = 2246,

	/*! There is no free memory in the multicast flow table expansion area */
	NCP_ST_MTM_MCAST_NO_MEMORY                 = 2247,
	/*! The specified multicast group does not exist */
	NCP_ST_MTM_MCAST_GROUP_DOES_NOT_EXIST      = 2248,
	/*! The specified flow ID does not exist in the specified multicast group */
	NCP_ST_MTM_MCAST_FLOW_NOT_IN_GROUP         = 2249,

	/*!
	 * The MTM device did not return a done indication for initializing the
	 * TW QUEUE FIFO.
	 */
	NCP_ST_MTM_TW_QUEUE_FIFO_INIT_FAILED       = 2250,
	/*! The MTM software entered a state that should not be possible. */
	NCP_ST_MTM_INTERNAL_SW_ERROR               = 2251,

	/*! MTM background node removal is active. */
	NCP_ST_MTM_BG_NODE_REM_ACTIVE              = 2252,
	/*! MTM background node removal is not active. */
	NCP_ST_MTM_BG_NODE_REM_INACTIVE            = 2253,
	/*! MTM background node removal is shutting down. */
	NCP_ST_MTM_BG_NODE_REM_SHUTTINGDOWN        = 2254,
	/*! The queue is already scheduled for background remove. */
	NCP_ST_MTM_QUEUE_BG_REM_PENDING            = 2255,
	/*! The scheduler is already scheduled for background remove. */
	NCP_ST_MTM_SCHEDULER_BG_REM_PENDING        = 2256,
	/*!
	 * The resource handle provided is invalid,
	 * or the ID is not in the range for the resource,
	 * or the resrouce and ID are Valid but the ID is not currently allocated. */
	NCP_ST_MTM_BG_REM_RSRC_INVALID         = 2257,


	/* SE codes */
	/*! The table index specified is not valid. */
	NCP_ST_SE_INVALID_MLT_INDEX                = 2301,
	/*! The requested table access size is not valid. */
	NCP_ST_SE_INVALID_MLT_REQUEST_SIZE         = 2302,
	/*! The specified State Engine handle is not valid. */
	NCP_ST_SE_INVALID_HANDLE                   = 2303,
	/*! Initialization of the State Engine failed. */
	NCP_ST_SE_INIT_FAILED                      = 2304,
	/*! The FEM consumer queue pointer is not valid. */
	NCP_ST_SE_INVALID_FEM_POINTER              = 2305,
	/*! There are no events available on the FEM event queue. */
	NCP_ST_SE_FEM_NO_EVENTS                    = 2306,
	/*! FEM event reporting is not enabled. */
	NCP_ST_SE_FEM_NOT_ENABLED                  = 2307,
	/*! The FEM event queue was flushed.  No events were processed. */
	NCP_ST_SE_FEM_EVENT_QUEUE_FLUSHED          = 2308,
	/*! Initialization of the SE state protection semaphore failed. */
	NCP_ST_SE_SEM_INIT_ERROR                   = 2309,
	/*! The SE Namespace entries are not contiguous. */
	NCP_ST_SE_NS_NOT_CONTIGUOUS                = 2310,

	/*! SED codes */
	/*! The specified parameter index is not valid. */
	NCP_ST_SED_INVALID_PARAM_INDEX             = 2401,
	/*! The requested parameter table access size is not valid. */
	NCP_ST_SED_INVALID_PARAM_REQUEST_SIZE      = 2402,
	/*! The specified SED handle is not valid. */
	NCP_ST_SED_INVALID_HANDLE                  = 2403,
	/*! The specified SED Parameter is not valid. */
	NCP_ST_SED_INVALID_PARAM                   = 2404,
	/*! Initialization of the SED module failed. */
	NCP_ST_SED_INIT_FAILED                     = 2405,
	/*! Initialization of the SED state protection semaphore failed. */
	NCP_ST_SED_SEM_INIT_ERROR                  = 2406,

	/* CE common codes */

	/*! A specified Qualifier parameter size is not valid. */
	NCP_ST_CE_INVALID_PARAM_SIZE               = 2501,
	/*! The specified CE script is not compatible with this version of the CE. */
	NCP_ST_CE_INCOMPATIBLE_SCRIPT              = 2502,
	/*! The specified CE library is not compatible with this version of the CE. */
	NCP_ST_CE_INCOMPATIBLE_LIBRARY             = 2503,
	/*! The CE module was configured with an invalid number of ALUs */
	NCP_ST_CE_INVALID_NUM_ALUS                 = 2504,
	/*! The calculated memory size does not match the value included in the config map. */
	NCP_ST_CE_INVALID_MEM_SIZE                 = 2505,
	/*! The cno image contains a library name that is not valid */
	NCP_ST_CE_INVALID_LIBRARY_NAME             = 2506,
	/*! The signature of the library function does not match the signature of the symbol table entry. */
	NCP_ST_CE_INVALID_LIBRARY_FUNCTION         = 2507,
	/*! The specified CE is not valid. */
	NCP_ST_CE_INVALID_REGION                   = 2508,
	/*! A library function was not properly stored. */
	NCP_ST_CE_LIBRARY_FUNCTION_NOT_FOUND       = 2509,
	/*! There was not sufficient CE memory to load the script. */
	NCP_ST_CE_SCRIPT_NO_MEMORY                 = 2510,
	/*! A script ID was specified that was out of range. */
	NCP_ST_CE_SCRIPT_INVALID_ID                = 2511,
	/*! The specified PC address was not valid. */
	NCP_ST_CE_SCRIPT_INVALID_ADDRESS           = 2512,
	/*! A script specified for unloading is in use. */
	NCP_ST_CE_SCRIPT_IN_USE                    = 2513,
	/*! A script specified for unloading is in use. */
	NCP_ST_CE_SCRIPT_NOT_LOADED                = 2514,
	/*! A script specified for loading is already loaded. */
	NCP_ST_CE_SCRIPT_LOADED                    = 2515,
	/*! Loading the CE memory failed. */
	NCP_ST_CE_LOAD_FAILED                      = 2516,
	/*! Initializing the CE failed. */
	NCP_ST_CE_INIT_FAILED                      = 2517,

	/* MISC API codes */
	NCP_ST_MISCOMPARE                          = 2601, /*!< */
	NCP_ST_INVALID_REG_SIZE                    = 2602, /*!< */

	/* COW codes */

	/*!
	 * Invalid or engine not present in this platform/chip.
	 */
	NCP_ST_COW_INVALID_ENGINE                  = 2701, /*!< */

	/*!
	 * Invalid priority value. valid values are 0-7.
	 */
	NCP_ST_COW_INVALID_PRIORITY                = 2702, /*!< */

	/*!
	 * Invalid task priority to queue mapping value.
	 */
	NCP_ST_COW_INVALID_QUEUE_PRIO_MAP          = 2703, /*!< */

	/*!
	 * Invalid number of logical queues.
	 */
	NCP_ST_COW_INVALID_NUM_LOGICAL_QUEUES      = 2704, /*!< */

	/*!
	 * Invalid threshold group id value.
	 */
	NCP_ST_COW_INVALID_THRES_GROUP_ID          = 2705, /*!< */

	/*!
	 * Invalid destination instance range value.
	 */
	NCP_ST_COW_INVALID_DEST_INST_RANGE         = 2706, /*!< */

	/*!
	 * Invalid destination instance value.
	 */
	NCP_ST_COW_INVALID_DEST_INST               = 2707, /*!< */

	/*!
	 * Invalid random early discard slope value.
	 */
	NCP_ST_COW_INVALID_RED_SLOPE               = 2708, /*!< */

	/*!
	 * Invalid global buffer discard all threshold value.
	 */
	NCP_ST_COW_INVALID_GLOBAL_BUF_ALL_THRES    = 2709, /*!< */

	/*!
	 * Invalid global buffer discard random threshold value.
	 */
	NCP_ST_COW_INVALID_GLOBAL_BUF_RANDOM_THRES = 2710, /*!< */

	/*!
	 * Invalid threshold group discard random threshold value.
	 */
	NCP_ST_COW_INVALID_THRES_GROUP_RANDOM_THRES = 2711, /*!< */

	/*!
	 * Invalid threshold group discard all threshold value.
	 */
	NCP_ST_COW_INVALID_THRES_GROUP_ALL_THRES    = 2712, /*!< */

	/*!
	 * Invalid backpressure threshold value.
	 */
	NCP_ST_COW_INVALID_BACKPRESSURE_THRES       = 2713, /*!< */

	/*!
	 * Invalid threshold units value.
	 */
	NCP_ST_COW_INVALID_THRESH_UNIT              = 2714, /*!< */

	/*!
	 * Invalid backpressure threshold hysteresis value.
	 */
	NCP_ST_COW_INVALID_BP_THRESH_HYST           = 2715, /*!< */

	/*!
	 * Invalid TIL arbitration mode value.
	 */
	NCP_ST_COW_INVALID_ARB_MODE                 = 2716, /*!< */

	/*!
	 * Invalid load balance mode value.
	 */
	NCP_ST_COW_INVALID_LOAD_BALANCE_MODE        = 2717, /*!< */

	/*!
	 * Input param definition buffer is NULL.
	 */
	NCP_ST_COW_INVALID_PARAM_DEF_BUFFER         = 2718, /*!< */

	/*!
	 * Input param select buffer is NULL.
	 */
	NCP_ST_COW_INVALID_PARAM_SEL_BUFFER         = 2719, /*!< */

	/*!
	 * Template id value is more than the max available.
	 */
	NCP_ST_COW_INVALID_TEMPLATE_ID              = 2720, /*!< */

	/*!
	 * Input param definition size doesnt match hardware value.
	 */
	NCP_ST_COW_INVALID_PARAM_DEF_LEN            = 2721, /*!< */

	/*!
	 * Flow data entry size is not supported.
	 */
	NCP_ST_COW_INVALID_ENTRY_SIZE               = 2722, /*!< */

	/*!
	 * Virtual pipeline id value is more than what is supported.
	 */
	NCP_ST_COW_INVALID_VP_ID                    = 2723, /*!< */

	/*!
	 * Flow data max entries is zero when using flow data.
	 */
	NCP_ST_COW_INVALID_MAX_ENTRIES              = 2724, /*!< */

	/*!
	 * The engine is not a launch engine.
	 */
	NCP_ST_COW_NOT_LAUNCH_ENGINE                = 2725, /*!< */

	/*!
	 * Weighted round robin weight value is more than allowed value.
	 */
	NCP_ST_COW_INVALID_INPUT_QUEUE_WEIGHT       = 2726, /*!< */

	/*!
	 * Output template buffer is NULL.
	 */
	NCP_ST_COW_INVALID_OUT_TEMPLATE_BUFFER      = 2727, /*!< */

	/*!
	 * Task tracing feature is being used when debug mode is not set to log tasks.
	 */
	NCP_ST_COW_NOT_TASK_LOG_DEBUG_MODE          = 2728, /*!< */

	/*!
	 * Task tracing is already enabled.
	 */
	NCP_ST_COW_TASK_TRACE_ALREADY_ENABLED       = 2729, /*!< */

	/*!
	 * Task tracing is already disabled.
	 */
	NCP_ST_COW_TASK_TRACE_ALREADY_DISABLED      = 2730, /*!< */

	/*!
	 * Task trace trigger already disabled.
	 */
	NCP_ST_COW_TASK_TRACE_TRIGGER_ALREADY_DISABLED = 2731, /*!< */

	/*!
	 * Task tracing param offset is more than allowed value.
	 */
	NCP_ST_COW_TASK_TRACE_INVALID_PARAM_OFFSET  = 2732, /*!< */

	/*!
	 * COW TCLD module buffer initialization failed.
	 */
	NCP_ST_COW_TCLD_BUF_INIT_FAILURE            = 2733, /*!< */

	/*!
	 * COW TDGL module failed to come online.
	 */
	NCP_ST_COW_TDGL_ONLINE_FAILURE              = 2734, /*!< */

	/*!
	 * COW TIL module failed to come online.
	 */
	NCP_ST_COW_TIL_ONLINE_FAILURE               = 2735, /*!< */
    
	/*!
	 * The max number of destinations that can be backpressured from an 
	 * engine is reached.
	 */
	NCP_ST_COW_MAX_BP_DESTS                     = 2736,

	/*!
	 * The ratio of number of BP to discard threshold groups is not supported.
	 */
	NCP_ST_COW_UNSUPPORTED_BP_TO_DISCARD_THRESH_GROUP_RATIO = 2737,

	/*!
	 * Invalid or unsupported chip.
	 */
	NCP_ST_COW_INVALID_CHIP                  = 2738, /*!< */

	/*!
	 * Input discard stats buffer is NULL.
	 */
	NCP_ST_COW_INVALID_DISCARD_STATS_BUFFER         = 2739, /*!< */

	/*!
	 * Input queue index map buffer is NULL.
	 */
	NCP_ST_COW_INVALID_QUEUE_INDEX_MAP_BUFFER         = 2740, /*!< */

	/*!
	 * The queue id provided is invalid.
	 */
	NCP_ST_COW_INVALID_QUEUE                       = 2741, /*!< */

	/*!
	 * The queue id provided is invalid.
	 */
	NCP_ST_COW_INVALID_MODE_TASK_BUFFER            = 2742, /*!< */

	/*!
	 * The queue id provided is invalid.
	 */
	NCP_ST_COW_INVALID_NUM_ITEMS_BUFFER            = 2743, /*!< */

	/* Virtual Pipeline codes */
	/*!
	 * When the Virtual Pipeline handle passed to the API is invalid.
	 */
	NCP_ST_VPM_INVALID_VP_HDL                   = 2801, /*!< */
	/*!
	 * When the Virtual Pipeline name passed to ncp_vp_handle_get() API is NULL.
	 */
	NCP_ST_VPM_INVALID_VP_NAME                  = 2802, /*!< */
	/*!
	 * When the Engine Sequence name passed to ncp_vp_engine_seq_id_get() API
	 * is NULL.
	 */
	NCP_ST_VPM_INVALID_ENGINE_SEQUENCE_NAME     = 2803, /*!< */
	/*!
	 * When the cookie value passed to ncp_vp_handle_get() API does not match
	 * with the virtual pipeline cookie in configuration file.
	 */
	NCP_ST_VPM_C_COOKIE_MISMATCH                = 2804, /*!< */
	/*!
	 * When the Virtual Pipeline is not found.
	 */
	NCP_ST_VPM_VP_NOT_FOUND                     = 2805, /*!< */
	/*!
	 * When the flowData param passed to ncp_vp_flow_data_write() API is NULL.
	 */
	NCP_ST_VPM_INVALID_FLOW_DATA                = 2806, /*!< */
	/*!
	 * When the flowId param passed to ncp_vp_flow_data_write() API is more than
	 * allowable flow ids for the Virtual Pipeline.
	 */
	NCP_ST_VPM_INVALID_FLOW_ID                  = 2807, /*!< */
	/*!
	 * When the Virtual Pipeline does not have flow data defined in ASE, but,
	 * ncp_vp_flow_data_write() API is being used to write a flow data entry.
	 */
	NCP_ST_VPM_FLOW_DATA_NOT_DEFINED            = 2808, /*!< */
	/*!
	 * When the Engine Sequence provided in the API parameter is not found in
	 * the Virtual Pipeline.
	 */
	NCP_ST_VPM_ENGINE_SEQUENCE_NOT_FOUND        = 2809, /*!< */
	/*!
	 * When no engines are present in an Engine Sequence while loading a
	 * configuration file. This indicates that there is a problem in ASE.
	 */
	NCP_ST_VPM_ENGINE_NOT_FOUND                 = 2810, /*!< */
	/*!
	 * When the launch engine is out of range of enum ncp_launch_engine_type_t.
	 * If this happens while loading a configuration file, it indicates there is
	 * a problem in ASE. If this error is seen using an API, then the launch
	 * engine param passed to the API needs to be checked.
	 */
	NCP_ST_VPM_INVALID_LAUNCH_ENGINE            = 2811, /*!< */
	/*!
	 * When a vp is valid, but is not launched by the correct engine for the
	 * operation specified.
	 */
	NCP_ST_VPM_LAUNCH_ENGINE_MISMATCH           = 2812, /*!< */
	/*!
	 * When a vp is valid, but does not have the correct ouptut
	 * parameter format.
	 */
	NCP_ST_VPM_OUTPUT_FORMAT_INVALID            = 2813, /*!< */
	/*!
	 * When the engine parameter passed to ncp_vp_handle_get_by_template_id() API
	 * is out of range of enum ncp_engine_type_t.
	 */
	NCP_ST_VPM_INVALID_ENGINE                   = 2814, /*!< */
	/*!
	 * When the engine sequence does not terminate in CPU.
	 */
	NCP_ST_VPM_ENGINE_SEQUENCE_NOT_CPU_TERMINATING = 2815, /*!< */
	/*!
	 * When CPU is not the launch engine.
	 */
	NCP_ST_VPM_VP_NOT_CPU_LAUNCH_ENGINE         = 2816, /*!< */
	/*!
	 * When the flow data param type is not known to RTE. This means that a new
	 * data type has been added in ASE but not in RTE.
	 */
	NCP_ST_VPM_INVALID_FLOW_PARAM_TYPE          = 2817, /*!< */
	/*!
	 * When a vp is valid, but does not have the correct input
	 * parameter format.
	 */
	NCP_ST_VPM_INPUT_FORMAT_INVALID             = 2818, /*!< */

	/*!
	 * When the template Id buffer provided is invalid.
	 */
	NCP_VPM_INVALID_TEMPLATE_ID_BUFFER             = 2819, /*!< */

	/* I2C codes */
	NCP_ST_I2C_INVALID_HANDLE                   = 2901, /*!< */
	NCP_ST_I2C_INVALID_ARGUMENT                 = 2902, /*!< */
	NCP_ST_I2C_INVALID_NODE_ID                  = 2903, /*!< */
	NCP_ST_I2C_ERROR_SEMAPHORE                  = 2904, /*!< */
	NCP_ST_I2C_ERROR_MAST_XMT_CFG               = 2905, /*!< */
	NCP_ST_I2C_ERROR_MAST_XMT_STAT              = 2906, /*!< */
	NCP_ST_I2C_ERROR_MAST_RCV_CFG               = 2907, /*!< */
	NCP_ST_I2C_ERROR_MAST_RCV_STAT              = 2908, /*!< */
	NCP_ST_I2C_ERROR_READ_INCOMPLETE            = 2910, /*!< */
	NCP_ST_I2C_ERROR_MASTER_STATUS              = 2911, /*!< Usually used for secondary I2C busses in the board System FPGA */
	NCP_ST_I2C_ERROR_TIMEOUT                    = 2912, /*!< Failed to receive status in a timely fashion */
	NCP_ST_I2C_ERROR_KERNEL_TRANSFER	= 2913, /*!< Failed to do i2c_transfer from kernel */

	/* Remote device interface status codes */
	NCP_ST_RDEV_RECV_FAILED                     = 3001, /*!< */
	/*!
	 * The RTE reports this error when the native-mode ASE
	 * simulation stops responding. The simulator log should
	 * be examined for errors.
	 */
	NCP_ST_RDEV_RECV_TIMEOUT                    = 3002, /*!< */
	NCP_ST_RDEV_RECV_SELECT_ERROR               = 3003, /*!< */
	NCP_ST_RDEV_RECV_WRONG_SESSION              = 3004, /*!< */
	NCP_ST_RDEV_RECV_WRONG_CONN                 = 3005, /*!< */
	NCP_ST_RDEV_RECV_WRONG_MSG_TYPE             = 3006, /*!< */
	NCP_ST_RDEV_RECV_SEQUENCE_ERROR             = 3007, /*!< */
	NCP_ST_RDEV_SERVER_DEV_OPEN_FAILED          = 3008, /*!< */
	/*!
	 * The RTE client attempted to connect to the ASE simulator
	 * using the port specified by NCP_NCA_SOCKET but got no
	 * repsonse. Make sure the simulator is running and that
	 * NCP_NCA_SOCKET is set correctly.
	 */
	NCP_ST_RDEV_SERVER_NOT_RESPONDING           = 3009, /*!< */
	NCP_ST_RDEV_SERVER_NO_SESSIONS              = 3010, /*!< */
	NCP_ST_RDEV_SERVER_NO_MEMORY                = 3011, /*!< */
	NCP_ST_RDEV_SERVER_THREAD_CREATE_FAILED     = 3012, /*!< */
	NCP_ST_RDEV_SERVER_CONN_WAITING_FOR_EVENT   = 3013, /*!< */
	NCP_ST_RDEV_SERVER_NO_CONN_FOR_EVENT        = 3014, /*!< */
	NCP_ST_RDEV_SERVER_INVALID_MESSAGE          = 3015, /*!< */
	NCP_ST_RDEV_SERVER_API_NOT_IMPLEMENTED      = 3016, /*!< */
	NCP_ST_RDEV_SERVER_PREVIOUS_NON_ACK_WRITE_FAILED = 3017, /*!< */
	NCP_ST_RDEV_INVALID_DESCRIPTOR              = 3018, /*!< */
	NCP_ST_RDEV_INVALID_ENDPOINT                = 3019, /*!< */
	NCP_ST_RDEV_ADDR_IN_USE                     = 3020, /*!< */
	NCP_ST_RDEV_THREAD_CREATE_FAILED            = 3021, /*!< */
	NCP_ST_RDEV_THREAD_DETACH_FAILED            = 3022, /*!< */
	/*!
	 * The RTE client was unable to resolve the address for
	 * the ASE simulator. Either the NCP_NCA_SOCKET variable
	 * is not set or it specifies an invalid hostname.
	 */
	NCP_ST_RDEV_SERVER_ADDR_NOT_FOUND           = 3023, /*!< */
	NCP_ST_RDEV_MAPPING_FILE_NOT_FOUND          = 3024, /*!< */
	NCP_ST_RDEV_INVALID_HANDLE                  = 3025, /*!< */
	NCP_ST_RDEV_CONN_NOT_EXIST                  = 3026, /*!< */
	NCP_ST_RDEV_CLIENT_HAS_NO_CONNECTIONS       = 3027, /*!< */
	NCP_ST_RDEV_MSG_FRAG_SEQUENCE_ERR           = 3028, /*!< */
	NCP_ST_RDEV_MSG_SIZE_ERR                    = 3029, /*!< */
	NCP_ST_RDEV_MSG_LENGTH_EXCEEDS_MAX          = 3030, /*!< */
	NCP_ST_RDEV_MSG_EXCEEDS_MAX_PACKET_SIZE     = 3031, /*!< */
	NCP_ST_RDEV_MSG_SEND_FAILED                 = 3032, /*!< */
	NCP_ST_RDEV_MSG_RECV_FAILED                 = 3033, /*!< */
	/*!
	 * This error occurs when the socket connection between the
	 * RTE client and the ASE simulator is unexpectedly broken.
	 * This usually means that the software on the other side of
	 * the connection has crashed; i.e. the RTE reports this error
	 * when the simulator crashes.
	 */
	NCP_ST_RDEV_MSG_RECV_NOMSG                  = 3034, /*!< */
	NCP_ST_RDEV_SOCKET_ERROR                    = 3035, /*!< */
	NCP_ST_RDEV_INPUT_TASK_GET_UNDEFINED        = 3036, /*!< */

	/* MPPX status codes */
	NCP_ST_MPP_FBI_INIT_ERROR                   = 3101, /*!< */
	NCP_ST_MPP_HE_INIT_ERROR                    = 3102, /*!< */
	NCP_ST_MPP_SEM_INIT_ERROR                   = 3103, /*!< */
	NCP_ST_MPP_PQM_INIT_ERROR                   = 3104, /*!< */
	NCP_ST_MPP_HE_NS_INIT_ERROR                 = 3105, /*!< */
	NCP_ST_MPP_ETAC_SW_ADDR_ERROR               = 3106, /*!< */
	NCP_ST_MPP_ETAC_BW_ADDR_ERROR               = 3107, /*!< */
	NCP_ST_MPP_ETAC_FW_ADDR_ERROR               = 3108, /*!< */

	/* Tree memory staus codes */
	NCP_ST_TREE_PROG_INIT_ERROR                 = 3201, /*!< */
	NCP_ST_TREE_ROOT_INIT_ERROR                 = 3202, /*!< */
	NCP_ST_TREE_PROG_HIGHBW_ADDR_ERROR          = 3203, /*!< */
	NCP_ST_TREE_PROG_MEDBW_ADDR_ERROR           = 3204, /*!< */
	NCP_ST_TREE_PROG_LOWBW_ADDR_ERROR           = 3205, /*!< */
	NCP_ST_TREE_PROG_HIGHFW_ADDR_ERROR          = 3206, /*!< */
	NCP_ST_TREE_PROG_MEDFW_ADDR_ERROR           = 3207, /*!< */
	NCP_ST_TREE_PROG_LOWFW_ADDR_ERROR           = 3208, /*!< */
	NCP_ST_TREE_PROG_HIGHSW_ADDR_ERROR          = 3209, /*!< */
	NCP_ST_TREE_PROG_MEDSW_ADDR_ERROR           = 3210, /*!< */
	NCP_ST_TREE_PROG_LOWSW_ADDR_ERROR           = 3211, /*!< */
	NCP_ST_TREE_ROOT_HIGHBW_ADDR_ERROR          = 3212, /*!< */
	NCP_ST_TREE_ROOT_MEDBW_ADDR_ERROR           = 3213, /*!< */
	NCP_ST_TREE_ROOT_LOWBW_ADDR_ERROR           = 3214, /*!< */
	NCP_ST_TREE_ROOT_HIGHFW_ADDR_ERROR          = 3215, /*!< */
	NCP_ST_TREE_ROOT_MEDFW_ADDR_ERROR           = 3216, /*!< */
	NCP_ST_TREE_ROOT_LOWFW_ADDR_ERROR           = 3217, /*!< */
	NCP_ST_TREE_ROOT_HIGHSW_ADDR_ERROR          = 3218, /*!< */
	NCP_ST_TREE_ROOT_MEDSW_ADDR_ERROR           = 3219, /*!< */
	NCP_ST_TREE_ROOT_LOWSW_ADDR_ERROR           = 3220, /*!< */

	/********************* DPI HFA status codes **************/
	NCP_ST_DPI_HFA_INVALID_HDL                  = 3301,
	/*!<
	 * Invalid DPI handle.
	 */
    
	NCP_ST_DPI_HFA_INVALID_RST_MISSING_OYSTER_OR_V2RST = 3302,
	/*!<
	 * Ruleset file is missing the V2 or Oyster section. 
	 */
    
	NCP_ST_DPI_HFA_INVALID_RST_NUMBER_OF_SECTIONS_OOB = 3303,
	/*!<
	 * Ruleset contains an out of bounds section number.
	 */
    
	NCP_ST_DPI_INVALID_COMMAND                  = 3304, 
	/*!< 
	 * Invalid ruleset data load command. 
	 */

	NCP_ST_DPI_HFA_INVALID_RST_SECTION_TYPE     = 3305,
	/*!<
	 * Ruleset contains an invalid section type.
	 */

	NCP_ST_DPI_INITIALIZE_ERROR                 = 3306,
	/*!<
	 * Unable to initialize RegEx library in call to ncp_dpi_init().
	 * Typical causes include invalid ncp handle when ncp_dpi_hfa_config() failed.
	 */

	NCP_ST_DPI_OUTPUT_OVERFLOW                  = 3307,
	/*!<
	 * RegEx output exceeds allocated output buffer. Need to resubmit scan
	 * with a larger output buffer.
	 */

	NCP_ST_DPI_SC_STACK_OVERFLOW                = 3308,
	/*!<
	 * Start condition stack overflow. Pushed too many start conditions on the stack.
	 */

	NCP_ST_DPI_SC_STACK_UNDERFLOW               = 3309,
	/*!<
	 * Start condition stack underflow. Popped more start conditions off the
	 * stack than were pushed onto the stack.
	 */

	NCP_ST_DPI_JOB_TERMINATE                    = 3310,
	/*!<
	 * Scan job is terminated due to engine error.
	 */

	NCP_ST_DPI_INVALID_INSTR                    = 3311,
	/*!<
	 * Indicates the hardware encountered an invalid instruction in the compiled ruleset
	 * when executing a scan. This error is non-recoverable.
	 */

	NCP_ST_DPI_BACKUP_ERROR                     = 3312,
	/*!<
	 * DPI engine scan backup error.
	 */

	NCP_ST_DPI_UNCORRECTED_PARITY_ERROR         = 3313,
	/*!<
	 * DPI engine scan parity error.
	 */

	NCP_ST_DPI_LCB_ALLOCATION_ERROR             = 3314,
	/*!<
	 * Error attempting to allocate a LCB during a cross packet scan.
	 */

	NCP_ST_DPI_LCB_ALLOCATED                    = 3315,
	/*!<
	 * LCB is allocated for cross packet scan.
	 */

	NCP_ST_DPI_INVALID_PARAMETER                = 3316,
	/*!<
	 * Invalid parameter is passed into a DPI function.
	 */

	NCP_ST_DPI_THREAD_INIT_ERROR                = 3317,
	/*!<
	 * Error initializing RegEx thread handle.
	 */

	NCP_ST_DPI_MAX_THREADS_REACHED              = 3318,
	/*!<
	 * Maximum number of RegEx threads reached as specified by
	 * constant NCP_ST_DPI_MAX_THREADS.
	 */

	NCP_ST_DPI_INVALID_THREAD_ID                = 3319,
	/*!<
	 * A RegEx API is called with a thread id not allocated via ncp_dpi_thread_init()
	 * or with one already deinitialized via call to ncp_dpi_thread_deinit().
	 */

	NCP_ST_DPI_INVALID_STREAM_HANDLE            = 3320,
	/*!<
	 * A cross packet scan API is called with an invalid stream handle.
	 */

	NCP_ST_DPI_RULESET_LOAD_ERROR               = 3321,
	/*!<
	 * Error when loading ruleset file.
	 */

	NCP_ST_DPI_SCAN_ERROR                       = 3322,
	/*!<
	 * Error returned by DPI scan functions.
	 */

	NCP_ST_DPI_INVALID_FILE_FORMAT              = 3323,
	/*!<
	 * Invalid file format.  A typical cause would be trying to load an invalid
	 * ruleset (e.g. one not compiled with the RegEx compiler or one compiled
	 * with an out-of-date compiler that is not compatible with the current RegEx release).
	 */

	NCP_ST_DPI_INVALID_RULESET_BUFFER_FORMAT    = 3324,
	/*!<
	 * Invalid buffer format.  A typical cause would be trying to load an invalid
	 * ruleset (e.g. one not compiled with the RegEx compiler or one compiled
	 * with an out-of-date compiler that is not compatible with thec urrent RegEx release).
	 */

	NCP_ST_DPI_SCAN_TIMEOUT_ERROR               = 3325,
	/*!<
	 * Timeout error waiting for a pending a scan job to complete. This is defined
	 * for regression test.
	 */

	NCP_ST_DPI_SCAN_MODE_MISMATCH               = 3326,
	/*!<
	 * Attempted to do a blocking scan in non-blocking mode or vice versa. This is defined
	 * for regression test.
	 */

	NCP_ST_DPI_QUEUE_IS_FULL                    = 3327,
	/*!<
	 * Unable to submit scan job because input queue is full.
	 */

	NCP_ST_DPI_BUILD_HW_TABLE_ERROR             = 3328,
	/*!<
	 * Unable to compile RegEx ruleset.
	 */

	NCP_ST_DPI_INSUFFICIENT_RESOURCES_ERROR     = 3329,
	/*!<
	 * Error attempting to allocate internal resources. 
	 * Most likely cause is out of memory.
	 */

	NCP_ST_DPI_LIBRARY_NOT_INITIALIZED          = 3330,
	/*!<
	 * Failure to call ncp_dpi_init() prior to calling APIs dependent on the
	 * RegEx library being initialized..
	 */

	NCP_ST_DPI_LIBRARY_ALREADY_INITIALIZED      = 3331,
	/*!<
	 * Attempt to call ncp_dpi_init() after the RegEx library has already been initialized.
	 * In order to call ncp_dpi_init() again, the application must first call
	 * ncp_dpi_shutdown().
	 */

	NCP_ST_DPI_NO_RULESET_LOADED                = 3332,
	/*!<
	 * Attempt to run a scan job without first loading a ruleset.
	 */

	NCP_ST_DPI_XLATE_OVERFLOW                   = 3333,
	/*!<
	 * Token translation output overflow error.
	 */

	NCP_ST_DPI_FETCHED_TASK_BUSY                = 3334,
	/*!<
	 * Processing of fetched packets is not completed.
	 */

	NCP_ST_DPI_INVALID_HDL                      = 3335,
	/*!
	 * Invalid DPI HFA handle detected when loading the ruleset.
	 */

	NCP_ST_DPI_INVALID_JOB_ID                   = 3336,
	/*!<
	 * Invalid job ID.
	 */
    
	NCP_ST_DPI_INVALID_BLUT_SECTION             = 3337,
	/*!<
	 * BLUT section of the ruleset file is corrupt.
	 */

	NCP_ST_DPI_INVALID_SMALL_CONTEXT_MAX        = 3338,
	/*!<
	 * Attempt to get a cross packet stream id when maximum small context id is zero.
	 */
    
	NCP_ST_DPI_HFA_INVALID_RST_SRAM_OR_BLUT_MISSING = 3339,
	/*!<
	 * Ruleset file is missing the SRAMV2 or BLUT v2 section.
	 */

	NCP_ST_DPI_HFA_DMA_BURST_NOT_ENABLED = 3340,
	/*!<
	 * Ruleset DMA burst attempted, but DMA not enabled.
	 */

	/******************* Task I/O **********************/

	NCP_ST_TASK_LITE_UBOOT_NO_ALLOCATOR_REGISTERED = 3401,
	/*!<
	 * The Task I/O-LITE module requires that the client register function
	 * pointers for alloc, free, and va2pa before attempting to use the
	 * API or configure the NCA.
	 */
	NCP_ST_TASK_LITE_NULL_SEND_DONE_FUNCTION    = 3402,
	/*!<
	 * The Task I/O-LITE module requires that a send done function be set in the the send meta data.
	 */
	NCP_ST_TASK_LITE_QS_NOT_IN_USE              = 3403,
	/*!<
	 * The Task Lite Handle is not valid
	 */
	NCP_ST_TASK_LITE_QS_NOT_AVAILABLE           = 3404,
	/*!<
	 * The Task I/O-LITE module detected and invalid queueset.   It may be in use, out of range,  or managed
	 * by a different domain.
	 */
	NCP_ST_TASK_TDF_ZEROCOPY_AND_GATHERMODE_INVALID = 3405,
	/*!<
	 * The ncpTaskRecv CLI detected an invalid combination of tdf options.   Gather-mode DMA cannot be enabled if zeroCopy is
	 * also enabled.
	 */

	NCP_ST_TASK_SKB_COOKIE_VALIDATION_FAILED    = 3406,
	/*!<
	 * The Task I/O kernel interface detected a error when attempting to free a skb.   SKBs allocated via
	 * npt_task_buffer_alloc should have a cookie stored in them,   but this buffer did not.
	 */
	NCP_ST_TASK_NO_SKB_MEM                      = 3407,
	/*!<
	 * The Task I/O kernel interface was not able to allocate a SK buffer.
	 */
	NCP_ST_TASK_NO_RXBUFF_MEM                   = 3408,
	/*!<
	 * The Task I/O kernel interface was not able to allocate a receive buffer.
	 */
	NCP_ST_TASK_GSM_ALLOC_NOT_ALLOWED           = 3409,
	/*!<
	 * The Task I/O module detected an attempt to allocate from the GSM during warm restart
	 */

	NCP_ST_TASK_MMAP_FAILED                     = 3410,
	/*!<
	 * The Task I/O module received an error when attempting to map a physical memory region
	 */
	NCP_ST_TASK_QUESET_NOT_IN_LOCAL_DOMAIN      = 3411,
	/*!<
	 * The Thread Queue Set ID supplied references a queueset owned by another AMP domain.
	 */

	NCP_ST_TASK_NO_MAN_COMPLETION_OWED          = 3412,
	/*!<
	 * The task supplied in the ncp_task_recv_done API does not match one which is awaiting
	 * manual completion.
	 */
	NCP_ST_TASK_NULL_MAN_COMPLETION_LIST        = 3413,
	/*!<
	 * No tasks received on this task handle are awaiting manual completion.
	 */
	NCP_ST_TASK_RECEIVE_QUEUES_MUST_HAVE_SAME_SHARE_PERMISSION = 3414,
	/*!<
	 * All receive queues used by a thread must have same share permission,
	 * either all exclusive or all shared.
	 */
	NCP_ST_TASK_EXCLUSIVE_BINDING_NOT_AVAIL     = 3415,
	/*!<
	 * A request to bind to a queue or pipeline with exclusive access could
	 * not be completed.   This occurs when the resource has already been
	 * bound with either shared or exclusive access by another thread or
	 * process.
	 */
	NCP_ST_TASK_SHARED_BINDING_NOT_AVAIL        = 3416,
	/*!<
	 * A request to bind to a queueSet with shared access could
	 * not be completed.   This occurs when the resource has already been
	 * bound with exclusive access by another thread or
	 * process.
	 */
	NCP_ST_TASK_ORDERED_OUTPUT_MISMATCH         = 3417,
	/*!<
	 * When sharing queues all invocations of ncp_task_hdl_create must use the same setting for
	 * orderedTaskCompletion.
	 */
	NCP_ST_TASK_SHARED_PIPELINES_NOT_SUPPORTED  = 3418,
	/*!<
	 * A request to bind to a pipeline with shared access could
	 * not be completed.  Shared pipeline binding are no longer supported.  
	 */
	NCP_ST_TASK_SHARED_RECEIVE_QUEUES_NOT_SUPPORTED = 3419,
	/*!<
	 * A request to bind to a receive queue with shared access could
	 * not be completed.  Shared receive queues are no longer supported.  
	 */
	NCP_ST_TASK_EXCLUSIVE_VP_BINDING_NOT_AVAIL  = 3420,
	/*!<
	 * A request to bind to a VP in exclusive mode failed due to the associated nca queue
	 * or vp already being bound
	 */
	NCP_ST_TASK_INVALID_NCA_INPUT_QUEUE         = 3421,
	/*!<
	 * The NCA recevie queue specified in the bind exceeds
	 * the upper limit defined for this hardware platform.
	 */
	NCP_ST_TASK_INVALID_NCA_OUTPUT_QUEUE        = 3422,
	/*!<
	 * The NCA send queue specified in the bind exceeds
	 * the upper limit defined for this hardware platform.
	 */
	NCP_ST_TASK_INVALID_RECEIVE_QUEUE           = 3423,
	/*!<
	 * The software receive queue ID supplied for the request is not
	 * currently bound for this receive handle.
	 */
	NCP_ST_TASK_SEND_QUEUE_FULL                 = 3424,
	/*!<
	 * The NCA output queue (exclusive use) or intermediate software
	 * queue (shared use) is currently full.   This is not an error
	 * condition.   Applications that use blocking (wait==TRUE) task
	 * IO api calls should never receive this status.
	 */
	NCP_ST_TASK_RECV_QUEUE_EMPTY                = 3425,
	/*!<
	 * The NCA input queue (exclusive use) or intermediate software
	 * queue (shared use) is currently empty.   This is not an error
	 * condition.   Applications that use blocking (wait==TRUE) task
	 * IO api calls should never receive this status.
	 */
	NCP_ST_TASK_INVALID_TASK_HANDLE             = 3426,
	/*!<
	 * The task handle supplied for the API request is not valid.
	 * Task handles must be created using the ncp_task_hdl_create
	 * API function, and are valid only withing the contect of the
	 * thread that created them.
	 */
	NCP_ST_TASK_INVALID_VP_HANDLE               = 3427,
	/*!<
	 * The VpHdl (virtual pipeline handle) supplied to
	 * ncp_task_recv_queue_vp_unbind is invalid or NULL.
	 */
	NCP_ST_TASK_INVALID_BIND_TABLE_ENTRY        = 3428,
	/*!<
	 * The level 1 bind table receive queue is not null, but
	 * shared binding is specified.   This is an internal error.
	 */
	NCP_ST_TASK_NO_FREE_DYNAMIC_QUEUE           = 3429,
	/*!<
	 * There are no recevie queue IDs currently available.   Dynamic queue
	 * IDs are in the range 0..127
	 */
	NCP_ST_TASK_NULL_TASK_IN_RECVDONE           = 3430,
	/*!<
	 * The API function ncp_task_recv_done was called with a Null Task
	 * pointer
	 */
	NCP_ST_TASK_RX_TOO_BIG                      = 3431,
	/*!<
	 * The size of the task buffer allocation request exceeds the maximum
	 * size defined for the memory/rx pool.
	 */
	NCP_ST_TASK_BUFFER_POOL_NOT_FOUND           = 3432,
	/*!<
	 * The task memory/buffer pool is not associated with a receive buffer queue.
	 * This is an internal error.
	 */
	NCP_ST_TASK_REQUESTED_BUFF_POOL_TOO_BIG     = 3433,
	/*!<
	 * The task memory/buffer pool could not be allocated due to its reqested
	 * size being in excess of the amount of memory reserved for this purpose.
	 */
	NCP_ST_TASK_QMAP_ERR_TOO_BIG                = 3434,
	/*!<
	 * The specified queue ID exceeds the uppler limit for this hardware platform
	 */
	NCP_ST_TASK_BAD_QTYPE_FOR_STATUS_READ       = 3435,
	/*!<
	 * Invalid NCA queue type detected.   This is an internal error.
	 */
	NCP_ST_TASK_PUT_NULL_TASK_COMPLETION_QUEUE  = 3436,
	/*!<
	 * An inconsistensy has been detected in the NCA completion queue.
	 * This is an internal error.
	 */
	NCP_ST_TASK_PUT_NULL_TASK_OUTPUT_QUEUE      = 3437,
	/*!<
	 * An inconsistensy has been detected in the NCA output queue.
	 * This is an internal error.
	 */
	NCP_ST_TASK_INVALID_FIXED_QUEUEID           = 3438,
	/*!<
	 * The supplied receive queue ID is out of range, or in use.   Fixed queue IDs must
	 * be in the range 128..255.
	 */
	NCP_ST_TASK_NULL_RECVQUEUEID_PTR            = 3439,
	/*!<
	 * The application has called ncp_task_recv_queue_bind with a NULL
	 * pointer for the pRecvQueueId parameter. The API requires a valid address
	 * where the allocated receive queue ID can be returned.
	 */
	NCP_ST_TASK_HANDLE_HEAD_NULL                = 3440,
	/*!<
	 * A request to unbind a queue, or receive from a queue, could not be
	 * satisfied due to no queues being associated with the receive handle
	 * that was supplied.
	 */
	NCP_ST_TASK_SEND_NULL_METADATA_PTR          = 3441,
	/*!<
	 * The application did not provide a valid pointer to the task meta data.
	 * Task meta data is required for all task send requests.
	 */
	NCP_ST_TASK_SEND_NULL_TASK_PTR              = 3442,
	/*!<
	 * The application did not provide a valid pdu/buffer pointer.   If the
	 * pdu data size of a ncp_task_send request is non zero,   a valid buffer
	 * pointer is required.
	 */
	NCP_ST_TASK_NO_GSM                          = 3443,
	/*!<
	 * The internal shared memory segment used by the task IO module has not
	 * been created.   This is an internal error.
	 */
	NCP_ST_TASK_BUFFSIZE_TOO_LARGE              = 3444,
	/*!<
	 * A request to allocate a task buffer has failed due to the size requested
	 * exceeding the maximum size configured for the task rx buffer/memory pool.
	 */
	NCP_ST_TASK_CLIENT_FREE_NULLPTR             = 3445,
	/*!<
	 * The application has called ncp_task_buffer_free with a null pointer.
	 * A valid pointer to a buffer previously allocated with
	 * ncp_task_buffer_alloc must be provided.
	 */
	NCP_ST_TASK_CFG_TOO_MANY_TASK_MEMPOOLS      = 3446,
	/*!<
	 * The number of memory pools configured exceeds the maximum allowed
	 * for this hardware platform.  Note: VxWorks only supports one pool per domain.
	 */
	NCP_ST_TASK_CFG_TOO_MANY_RX_MEMPOOLS        = 3447,
	/*!<
	 * Exactly one receive buffer pool shall be defined for each task memory pool.
	 */
	NCP_ST_TASK_NO_RXPOOL_DEFINED               = 3448,
	/*!<
	 * Exactly one receive buffer pool shall be defined for each task memory pool.
	 */
	NCP_ST_TASK_NO_WARM_RESTART_VP              = 3449,
	/*!<
	 * The CPU-CPU virtual pipeline required for NCA warm restart was not found.
	 */
	NCP_ST_TASK_NO_IPCQ_FOR_RXB_POOL_IN_WARM_RESTART = 3450,
	/*!<
	 * Cannot drain receive buffer pool in NCA warm restart due to no NCA receive queues are configured to use
	 * a configured receive buffer pool.
	 */
	NCP_ST_TASK_CFG_TOO_MANY_RXB_POOLS          = 3451,
	/*!<
	 * The number of NCA receive pools associated with the configured task memory
	 * pool exceeds the maximum allowed for this hardware platform,  or exceeds
	 * the maximum currently supported by software (1).
	 */
	NCP_ST_TASK_CFG_TOO_MANY_QUEUE_GROUPS       = 3452,
	/*!<
	 * The number of queue groups configured exceeds the maximum allowed
	 * for this hardware platform.
	 */
	NCP_ST_TASK_RECV_QUEUE_NOT_IN_QUEUESET      = 3453,
	/*!<
	 * The ncaQueueId specified in the ncp_task_recv_queue_bind must be part of the
	 * thread queue set (outputQueueID) that was specified in the ncp_task_hdl_create API.
	 */
	NCP_ST_TASK_RECV_ACCESS_MODE_NOT_SAME_AS_QUEUESET = 3454,
	/*!<
	 * If the ncp_task_hdl_create API was used to open a queueset in exclusive mode, all assoiated receive queues must be bound in exclusive mode too.
	 */
	NCP_ST_TASK_CFG_TOO_MANY_THREAD_QUEUESETS_PER_GROUP = 3455,
	/*!<
	 * The number of thread queue sets configured for this group exceeds the
	 * maximum allowed per group for this hardware platform.
	 */
	NCP_ST_TASK_BUFFSZ_ORDER_ERR                = 3456,
	/*!<
	 * The configuration contains invalid sizes for the rx buffer pool.
	 * Buffer size 0 must be < buffer size 1 < buffer size 2, < buffer
	 * size 3.
	 */
	NCP_ST_TASK_BUFFSZ_OUT_OF_BOUNDS            = 3457,
	/*!<
	 * An invalid buffer size was detected during configuration.   This is
	 * an internal error.
	 */
	NCP_ST_TASK_NO_CACHE_ALLLIGNED_MEM          = 3458,
	/*!<
	 * The task IO module's private pool of cache alligned buffers has
	 * been exhausted.
	 */
	NCP_ST_TASK_NO_MALLOC_MEM                   = 3459,
	/*!<
	 * A request for memory allocation could not be satisfied due to
	 * insufficient resources.
	 */
	NCP_ST_TASK_NULL_RECV_QUEUE_PTR             = 3460,
	/*!<
	 * A invalid receive queue pointer address was detected when allocating
	 * task queue resources.
	 */
	NCP_ST_TASK_RECV_RET_SUCCESS_WITH_NULL_PTR  = 3461,
	/*!<
	 * A NULL pointer was returned during a task recevie operation.
	 * This is an internal error.
	 */
	NCP_ST_TASK_NULL_PCQ_PRODUCER_PTR           = 3462,
	/*!<
	 * The pointer to the producer index of a PCQ was NULL.   This is an
	 * internal error.
	 */
	NCP_ST_TASK_NULL_PCQ_CONSUMER_PTR           = 3463,
	/*!<
	 * The pointer to the consumer index of a PCQ was NULL.   This is an
	 * internal error.
	 */
	NCP_ST_TASK_NO_QUEUESET_IN_DOMAIN           = 3464,
	/*!<
	 * At least one task queue set must be defined for every management domain
	 */
	NCP_ST_TASK_NO_QUEUESET_IN_GRP              = 3465,
	/*!<
	 * At least one task queue set must be defined for every PCQ group
	 * configured for the NCA.
	 */
	NCP_ST_TASK_NO_TASKMEMPOOL_DEFINED          = 3466,
	/*!<
	 * No task memory pools were configured.   Task memory pools are required
	 * for all valid NCA configurations.
	 */
	NCP_ST_TASK_NO_RXB_POOL_DEFINED             = 3467,
	/*!<
	 * At least one NCA receive buffer pool must be defined for each task memory pool that is configured.
	 */
	NCP_ST_TASK_BUFFPOOL_CORRUPTION             = 3468,
	/*!<
	 * An inconsistency has been detected while processing the task memory pool.
	 */
	NCP_ST_TASK_POOLALLOC_RET_NULL              = 3469,
	/*!<
	 * The task IO module was unable to replenish the NCA's internal receive
	 * buffer pool due to a resource shortage.
	 */
	NCP_ST_TASK_POOLALLOC_RET_PHYSADDR_NULL     = 3470,
	/*!<
	 * Unexpected error encountered when computing the physical aqddress of the
	 * task buffer.  This is an internal error.
	 */
	NCP_ST_TASK_CORRUPT_NCA_INPUT_QUEUE         = 3471,
	/*!<
	 * An inconsistency has been detected while processing the NCA input queue.
	 * This is an internal error.
	 */
	NCP_ST_TASK_REQUEST_FOR_ZERO_LENGTH_TASK_BUFFER = 3472,
	/*!<
	 * The task IO task_buffer_alloc API was called with size equal zero,  which
	 * is invalid.
	 */
	NCP_ST_TASK_ALLOC_REQUIRES_POINTER          = 3473,
	/*!<
	 * The task IO task_buffer_alloc API was called with a NULL task pointer.
	 * The newly allocated buffer is returned at the address provided by the
	 * caller,   which requires a non NULL pointer.
	 */
	NCP_ST_TASK_DISPATCHED                      = 3474,
	/*!<
	 * This is an informational status code.   This status is returned when
	 * a call to ncp_tasK-recv results in tasks being dispatched to the receive
	 * dispatch function provided in the ncp_task_recv_queue_vp_bind API.
	 */
	NCP_ST_TASK_REQ_FOR_ZERO_LEN_CACHE_ALIGNED_MEM = 3475,
	/*!<
	 * A request for cache alligned memory contained an invalid size specifier.
	 * This is an internal error.
	 */
	NCP_ST_TASK_NCP_DESTROY_HANDLE_INVALID      = 3476,
	/*!<
	 * A request to destroy the NCA configuration could not be completed because
	 * the NCA handle is corrupt or invalid.   This is an internal error.
	 */
	NCP_ST_TASK_NO_SWQUEUE_MEM                  = 3477,
	/*!<
	 * An internal request for task queue memory could not be satisfied due to
	 * memory exhaustion.
	 */
	NCP_ST_TASK_HDL_CREATE_ERR                  = 3478,
	/*!<
	 * The task handle could not be created due to memory exhaustion.
	 */
	NCP_ST_TASK_TLS_RETRIEVAL_ERR               = 3479,
	/*!<
	 * The task IO module could not retrieve the thread local
	 * storage for this thread. The API function ncp_task_hdl_create
	 * must be called by every thread that wishes to will use the Task IO API.
	 */
	NCP_ST_TASK_ALLOC_SKB_FAILURE               = 3480,
	/*!<
	 * A task buffer could not be allocated due to skb pool exhaustion.   This
	 * error applies to kernel mode task IO clients.
	 */
	NCP_ST_TASK_BAD_GROUP_FOR_IRQ               = 3481,
	/*!<
	 * The PCQ group associated with the interrupt enable/disable request is not
	 * valid.
	 */
	NCP_ST_TASK_NULL_L1_BINDP                   = 3482,
	/*!<
	 * A request to unbind a pipeline via a call to
	 * ncp_task_recv_queue_vp_unbind failed due to no actively bound
	 * pipeline entry being found.
	 */
	NCP_ST_TASK_NO_MEM_L1BIND                   = 3483,
	/*!<
	 * The memory required to bind the virtual pipeline could not be allocated
	 * due to memory exhaustion.
	 */
	NCP_ST_TASK_NO_MEM_L2BIND                   = 3484,
	/*!<
	 * The memory required to bind the virtual pipeline could not be allocated
	 * due to memory exhaustion.
	 */
	NCP_ST_TASK_NO_BUFF_DESC                    = 3485,
	/*!<
	 * A call to ncp_task_free failed due to buffer descriptor exhaustion.
	 */
	NCP_ST_INVALID_BUFF_FOR_TASK_FREE           = 3486,
	/*!<
	 * A call to ncp_task_free failed due to the buffer not belong to the VA range of the pool.
	 */
	NCP_ST_TASK_SEND_SEGMENTS_INVALID_DESC      = 3487,
	/*!<
	 * A call to ncp_task_send_segments failed due to a NULL descriptor table
	 * pointer.
	 */
	NCP_ST_TASK_SEND_SEGMENTS_INVALID_NUM_SEGS  = 3488,
	/*!<
	 * A call to ncp_task_send_segments failed due to the number of segments being
	 * less that zero or greater than 16.
	 */
	NCP_ST_TASK_UNEXPECTED_QUEUE_TYPE           = 3489,
	/*!<
	 * A internal call to map a queue number to its associated PCQ pointer
	 * failed due to an invalid queue type.   This is an internal error.
	 */
	NCP_ST_TASK_SHUTDOWN                        = 3490,
	/*!<
	 * This status code is returned when the system is undergoing shutdown.
	 * previously bound resources should be unbound,   and all task IO resources
	 * should be returned.   Finally the application should exit.
	 */
	NCP_ST_TASK_MISMATCH                        = 3491,
	/*!<
	 * This status code is used by the ncpTaskRecv CLI to report data
	 * validation errors.
	 */
	NCP_ST_TASK_NO_LCM_MEMORY                   = 3492,
	/*!<
	 * Could not mmap VMA for accessing LCM, or LCM exhausted.
	 */
	NCP_ST_TASK_NO_GSM_MEMORY                   = 3493,
	/*!<
	 * Could not mmap VMA for accessing GSM, or GSM exhausted.
	 */
	NCP_ST_TASK_NO_TASK_CONTROL_MEMORY          = 3494,
	/*!<
	 * Could not mmap VMA for accessing Task Control are of GSM, or Task Control memory exhausted.
	 */
	NCP_ST_TASK_NO_THREADQUEUESET_TDF_SECTION   = 3495,
	/*!<
	 * TDF file does not contain a threadQueueSet section,  which is required.
	 */
	NCP_ST_TASK_NO_TASKSEND_TDF_SECTION         = 3496,
	/*!<
	 * TDF file does not contain a taskSend section,  which is required.
	 */
	NCP_ST_TASK_NO_TASKRECV_TDF_SECTION         = 3497,
	/*!<
	 * TDF file does not contain a taskRecv section,  which is required.
	 */
	NCP_ST_TASK_NO_TASKRECVQUEUEBIND_TDF_SECTION = 3498,
	/*!<
	 * TDF file does not contain a taskRecvQueueBind section,  which is required.
	 */
	NCP_ST_TASK_NO_TASKRECVQUEUEVPBIND_TDF_SECTION = 3499,
	/*!<
	 * TDF file does not contain a taskRecvQueueVpBind section,  which is required.
	 */
	NCP_ST_TASK_RECEIVE_QUEUE_NOT_FOUND         = 3500,
	/*
	 *!<
	 * The specified receive queue was not found in the list of receive
	 * queues associated with this task handle.
	 */
	NCP_ST_TASK_RETRY                           = 3501,
	/*
	 *!<
	 * The device ioctl must be retried
	 */
	NCP_ST_TASK_IOCTL_FAILED                    = 3502,
	/*
	 *!<
	 * The device ioctl has returned in error
	 */
	NCP_ST_TASK_QUEUE_STUCK_IN_WARM_RESTART     = 3503,
	/*
	 *!<
	 * Detected unresponsive hardware queue in warm restart
	 */
	NCP_ST_TASK_WARM_RESTART_UNSUPPORTED_PLATFORM = 3504,
	/*
	 *!<
	 * NCA Task I/O Is not supported on this platform.
	 */
	NCP_ST_TASK_SENDDONE_FN_WITH_VP_MANAGED_POOL = 3505,
	/*
	 *!<
	 * With NCA V2 (55XX),   the send done function can only be used when 
	 * the TQS poolID maps to a CPU managed pool.
	 */
	NCP_ST_TASK_NO_TQS_USES_POOL                = 3506,
	/*
	 *!<
	 * Could not populate CPU managed pool,  as no thread queue set has been configured to use it.
	 */
	/* Used internally by NCA simulator,   but not used by TaskIO API */
	NCP_ST_TASK_INVALID_NCA_TASK_COMPLETION_QUEUE = 3507,  /*!< */
	NCP_ST_TASK_TASK_COMPLETION_QUEUE_FULL      = 3508,   /*!< */
	NCP_ST_TASK_STATS_DISABLED                  = 3509,
	/*
	 *!<
	 * NCA Task I/O statistics collection is disabled - see compile-time
	 * define.
	 */
	NCP_ST_TASK_MISSING_NCADOMAININFO_SECTION   = 3510,
	/*
	 * !<
	 * Configuration file does not have a NcaDomainInfo map section.
	 */
	NCP_ST_TASK_NULL_TASK                       = 3511,
	/*
	 * !<
	 * The API detected that the task input parameter was NULL. 
	 */
	NCP_ST_TASK_NO_MME_ALLOCATOR                = 3512,
	/*
	 * !<
	 * No free MME allocation interface exists for this thread queue set.
	 */

	NCP_ST_TASK_BUFF_POOL_OVERRUN               = 3513,
	/*
	 * !<
	 * The task buffer overruns the maximum memory allocated for this pool.
	 */

	NCP_ST_TASK_CPU_POOL_IN_USE                 = 3514,
	/*
	 * !<
	 * When binding to a recevie queue in shared mode,   the task handle for the queueset containing the
	 * receive queue must have been created with shared=TRUE..
	 */

	NCP_ST_TASK_QUEUESET_NOT_SHARED             = 3515,
	/*
	 * !<
	 * When ptrCnt is non zero,   all pduSegSize<0..(ptrCnt-1)> must be non zero.
	 * receive queue must have been created with shared=TRUE..
	 */
	NCP_ST_TASK_ZERO_LEN_SEND_SEGMENT             = 3516,    

	/*
	 * !<
	 * Invalid pointer count,   range must be 0..6
	 */
	NCP_ST_TASK_BAD_PTR_CNT             = 3517,        
    
	/*
	 * !<
	 * Invalid invalid metaData
	 */
	NCP_ST_TASK_BAD_SEND_META_DATA             = 3518,            
    
	/* Backpressure related status codes */
	NCP_ST_NCA_BP_DEST_BIT_INVALID              = 3601,
	/*!< The destBit value is more than max possible. */
	NCP_ST_NCA_BP_BUFFER_INVALID                = 3602,
	/*!< The buffer provided is NULL. */
	NCP_ST_BP_INVALID_DEST_INDEX                = 3603,
	/*!< Backpressure destination not found. */
	NCP_ST_BP_DEST_ID_ALREADY_SET               = 3604,
	/*!< Backpressure destination is already used. */
	NCP_ST_BP_DEST_ID_ALREADY_UNSET             = 3605,
	/*!< Backpressure destination is already removed. */

	/* Backpressure aggregator related status codes */
	NCP_ST_BP_AGG_INVALID_INDEX                 = 3606, /*!< */
	/*!< Backpressure Aggregator index provided is not valid. */
    
	NCP_ST_BP_INVALID_BUFFER                    = 3607,
	/*!< The buffer provided is NULL. */

	NCP_ST_BP_INVALID_BUFFER_SIZE               = 3608,
	/*!< The buffer provided is NULL. */

	/* System Memory/Cache Initialization status codes */
	/*! The system memory controller could not be initialized because the
	 *  device has an unknown version of the system memory controller. */
	NCP_ST_UNKNOWN_MEMORY_CONTROLLER            = 3701,
	/*! The system cache initialize sequence was timed out by software. */
	NCP_ST_SYSCACHE_INIT_TIMEOUT                = 3702,
	/*! The system cache accelerated memory initialization was timed out
	 *  by software.  */
	NCP_ST_SYSCACHE_MEMINIT_TIMEOUT             = 3703,
	/*! not currently supported  */
	NCP_ST_SYSCACHE_INVALID_CONFIG              = 3704,
	/*! unable to initialize the syscache because the sysmem size is smaller
	 * than the minimum supported.
	 */
	NCP_ST_SYSCACHE_SYSMEM_TOO_SMALL            = 3705,
	/*! Task I/O resource names must be between 1 and 95 chanracters.
	 */
	NCP_ST_TASK_BAD_TQS_NAME                    = 3706,
	/*! Task I/O resource names must be between 1 and 95 chanracters.
	 */
	NCP_ST_TASK_BAD_RXQ_NAME                    = 3707,
	/*! The queue name does not exist in the local domain, or is not valid in this mode (user/kernel).
	 */
	NCP_ST_TASK_RECVQUEUE_NAME_NOT_FOUND        = 3708,
	/*! The tqs name does not exist in the local domain, or is not valid in this mode (user/kernel).
	 */
	NCP_ST_TASK_TQSNAME_NOT_FOUND               = 3709,
	/*! The tqs id does not exist in the local domain, or is not valid in this mode (user/kernel).
	 */
	NCP_ST_TASK_TQSID_NOT_FOUND               = 3710,
	/*! The nca queue id does not exist in the local domain, or is not valid in this mode (user/kernel).
	 */
	NCP_ST_TASK_RECV_QUEUE_ID_NOT_FOUND               = 3711,
	/*! Recursion detected while processing API in send_done  or free_done function.   Invalid API context.   Applications are not
	 * allowed to call certain APIs in the context of the send_done or free_done context.   Additionally, applications are not allowed to
	 * to call any variation of task buffer free if they are using task buffers from a VP managed shared pool (2..7)
	 */
	NCP_ST_TASK_SEND_DONE_RECURSION_DETECTED          = 3712,
	/*! The TQS has been explicitly disabled by a call to the ncp_task_tqs_disable API.   The API returning this error is 
	 * not allowed while the TQS in in this state.
	 */
	NCP_ST_TASK_TQS_DISABLED                          = 3713,
	/*! The API returning this status may only be called from user mode.
	 */
	NCP_ST_TASK_UMODE_ONLY_API                        = 3714,
	/*! The Task I/O resource specified in the API has a user/kernel mode designation that does not match the callers environment.
	 */
	NCP_ST_TASK_TQS_MODE_CONFLICT                     = 3715,
	/*! The application has issued a manual task completion,   but the underlying thread queue set does not have any input queues
	 * configured for manual task completion. 
	 */
	NCP_ST_TASK_UNEXPECTED_TASK_COMPLETION            = 3716,
	/*! FIXME: add description */
	NCP_ST_TASK_PCQ_GROUP_NOT_FOUND                   = 3717,
	/*! FIXME: add description */
	NCP_ST_TASK_LOGICAL_QUEUE_NOT_FOUND               = 3718,
	/*! FIXME: add description */
	NCP_ST_TASK_BAD_LOGICAL_QUEUE_NAME                = 3719,
	/*! FIXME: add description */
	NCP_ST_TASK_LOGICAL_QUEUE_NAME_NOT_FOUND          = 3720,
	/*! The application removed the task handle while it still owned
	 *  one or more buffers. This is only an alert -- the task buffers are 
	 *  flushed when the task handle is removed, but the developer needs to
	 *  fix the application so it doesn't leak buffers when Task Buffer 
	 *  Recovery is disabled.
	 */
	NCP_ST_TASK_TBR_BUFFERS_OWNED_DURING_REMOVE       = 3721,
	/*! The application request has timed out.   This is an informative status
	 * code, and the API may be retried if desired.
	 */
	NCP_ST_TASK_WAIT_TIMEOUT                          = 3722,    
	/*!
	 *  wait-WFI-mode (low power interrupt wait) is only supported for AXM5xxx devices and when
	 *  executing on the ARM local core(s) 
	 */
	NCP_ST_TASK_BAD_WFI_TARGET                        = 3723,          
	/*!
	 * it is invlalid to mix wait-ISR and wait-WFI modes on the same queue group.
	 */ 
	NCP_ST_TASK_INVALID_WFI_USE_CASE                  = 3724, 
    

	/*! The specified queue is not bound to the task handle. */
	NCP_ST_TASK_QUEUE_NOT_BOUND_TO_TASK_HANDLE        = 3725,    

	/*! The operation does not support MME-managed memory pools. */
	NCP_ST_TASK_SHARED_POOLS_NOT_SUPPORTED            = 3726,    

	/*! No task handle can be found that uses the specified pool */
	NCP_ST_TASK_NO_TASK_HDL_USES_POOL                 = 3727,

	/*! The task handle's associate pool is being reinitialized. */
	NCP_ST_TASK_POOL_IS_BEING_REINITIALIZED           = 3728,

	/*! The user requested a wait ISR profile for a CPU pool. */
	NCP_ST_INVALID_WAIT_PROFILE_FOR_POOL_TYPE         = 3729,

	/*! The requested queue usage is not allowed - see the TQS sharing and use flags */
	NCP_ST_TASK_TQS_SHARING_VIOLATION                  = 3730,
	/*! One or more pools are not valid for this thread queue set */
	NCP_ST_TASK_TQS_INVALID_POOL                       = 3731,
	/*! The buffer count provided exceeds the maximum supported for this API */
	NCP_ST_TASK_TOO_MANY_BUFFERS                       = 3732,
	/*! The tqs  is not configured in the ASE,  and has not been dynamically configured either */
	NCP_ST_TASK_TQS_NOT_CONFIGURED                     = 3733,
	/*! the summation of the pdu segment sizes does not equal the pdu size specified */
	NCP_ST_TASK_INVALID_PDU_SIZE                       = 3734,
	/*! manual completions cannot be issued if RX queue is configured for Automatic Task Completion */
	NCP_ST_TASK_RX_QUEUE_IS_AUTOMATIC_COMPLETION       = 3735,
	/*! ncp_task_complete called when mode is not MANUAL, or ncp_task_auto_deferred_complete when mode is not AUTO_DEFERRED */
	NCP_ST_TASK_WRONG_COMPLETION_MODE                  = 3736,
	/*! the number of task completions requested exceeds the number owed by this thread */
	NCP_ST_TASK_TOO_MANY_TASK_COMPLETIONS              = 3737,                  
	/*! application is attempting to unbind the tqs,  but task completions are owed */
	NCP_ST_TASK_EXITING_WITH_COMPLETIONS_OWED          = 3738,
	/*! if the TQSets rx queue is configured for manual completions,   then at least one txq must be used */
	NCP_ST_TASK_MANUAL_COMPLETION_REQUIRES_TXQ         = 3739,
	/*! numXXXX is too big.   The RTE limits bulk requests to 32 items */
	NCP_ST_TASK_BULK_REQUEST_TOO_BIG                   = 3740,
	/*! The PID table has been exhasuted */
	NCP_ST_TASK_OUT_OF_PIDS                            = 3741,
	/*! Process names must be unique system wide */
	NCP_ST_TASK_PROCESS_NAME_NOT_UNIQUE                = 3742,
	/*! All threads in the same process must use the same process name */
	NCP_ST_TASK_PROCESS_NAME_MISMATCH                  = 3743,
	/*! TBR detected that the buffer does not belong to the pool  */
	NCP_ST_TASK_TBR_INVALID_BUFFER                     = 3744,
	/*! TBR detected that the buffer is not in the expected state,  and pool corruption is likely */
	NCP_ST_TASK_TBR_FATAL_POOL_CORRUPTION              = 3745,
	/*! The process name failed validation */
	NCP_ST_TASK_BAD_PROCESS_NAME                       = 3746,
	/*! The thread name failed validation */
	NCP_ST_TASK_BAD_THREAD_NAME                        = 3747,
	/*! The value supplied for numTasks is too large */
	NCP_ST_TASK_INVALID_NUMTASKS                       = 3748,
	/* The tqs  handle supplied was either NULL or invalid  (failed cookie check) */
	NCP_ST_INVALID_TQS_HANDLE                           = 3749,
	/* The API ncp_task_deferred_consume can only be called if deferred consumption mode is enabled */
	NCP_ST_TASK_WRONG_CONSUMPTION_MODE                  = 3750,
	/*! application is attempting to unbind shutdown the tqs, but task
	 * completions are owed */
	NCP_ST_TASK_TAKING_PGIT_OFFLINE_WITH_COMPLETIONS_OWED = 3751,
	/*! a parameter of type ncp_task_resource_name_t was either NULL,  too long,   or not NULL terminated */
	NCP_ST_TASK_BAD_RESOURCE_NAME                       = 3752,
	/*! All threadNames within a given process name space must be unique, this is how we detect process crash/restart */
	NCP_ST_TASK_THREAD_NAME_NOT_UNIQUE                  = 3753,
	/*! The requested Task I/O process could not be found,   it may not be currently active */
	NCP_ST_TASK_PID_LOOKUP_FAILURE                      = 3754,
	/*! The pid value supplied is not a valid, it may be zero or be equal to a reserved pid value  */
	NCP_ST_TASK_INVALID_PID                             = 3755,
	/*! The buffer address is not valid for the bufer pool ID that was provided */
	NCP_ST_TASK_INVALID_BUFFER                          = 3756,
	/*! The TQS is not configured to use buffer pool ID that was provided */
	NCP_ST_TASK_BUFFER_POOL_NOT_CONFIGURED_FOR_TQS      = 3757,
	/*! The resource requires a zero use-count */
	NCP_ST_TASK_NONZERO_USE_COUNT                       = 3758,
	/*! The client thread is attempting to unbind the TQS when buffers are still owned,   which would result in a memory leak */
	NCP_ST_TASK_BUFFER_LEAK                             = 3759,
	/*! The last thread of a process is attempting to unbind when receive buffer refills are still owed to the NCA hardware. */
	NCP_ST_TASK_UNBIND_WHEN_REFILLS_OWED                = 3760,
	/*! When setting a TQS' set of queue groups, the TQS's allowed pools must
	 * be a superset of each queue group's member queue's allowed pools. */
	NCP_ST_TASK_ALLOWED_POOLS_MISMATCH                  = 3761,
	/*! When setting a TQS' set of queue groups, the TQS's virtual region must
	 * match each queue group's member queue's virtual region. */
	NCP_ST_TASK_VIRTUAL_REGION_MISMATCH                 = 3762,
	/*! When setting a TQS' set of queue groups, if this TQS is the last
	 * consumer of one of its current queue groups, that group's constituent
	 * NCA queues must be disabled. */
	NCP_ST_TASK_QUEUE_GROUP_HAS_ENABLED_NCA_QUEUE       = 3763,
	/*! The requested queue group was not found in the list of configured queue
	 * groups. */
	NCP_ST_TASK_QUEUE_GROUP_NOT_FOUND                   = 3764,
	/*! The requested NCA queue was not found in the list of configured NCA
	 * queues. */
	NCP_ST_TASK_NCA_QUEUE_NOT_FOUND                     = 3765,
	/*! The pool use count is going to zero,  but NCA refills are still owed */
	NCP_ST_TASK_POOL_USE_CNT_GOING_TO_ZERO_WHEN_REFILLS_OWED = 3766,
	/*! API cannot be issued when use TQS count is > 1 */
	NCP_ST_TASK_TQS_USE_CNT_NOT_ONE                     = 3767,
	/*! The requested pool was not found in the list of configured pools */ 
	NCP_ST_TASK_POOL_NOT_FOUND                          = 3768,
	/*! A process appears to be restarting                               */
	NCP_ST_TASK_PROCESS_RESTART_DETECTED                = 3769,
	/*! The shared data region mmap failed, likely because some portion of
	  the requested virtual address is occupied in the process' address
	  space. */
	NCP_ST_TASK_SHARED_DATA_REGION_MMAP_FAILED          = 3770,
	/*! The specified process name does not exist */
	NCP_ST_TASK_PROCESS_NOT_FOUND                       = 3771,
	/*! The specified thread name does not exist */
	NCP_ST_TASK_THREAD_NOT_FOUND                        = 3772,
	/*! The RTE has detected a buffer overrun in the output task! */
	NCP_ST_TASK_BUFFER_OVERRUN                          = 3773,
	/*! The output task header overlaps the data in pdu segment 0 */ 
	NCP_ST_TASK_HEADER_OVERLAPS_DATA                    = 3774,
	/*! The process is not recoverable due to terminating while in a critical section */
	NCP_ST_TASK_PROCESS_IN_CRITICAL_SECTION             = 3775,
	/*! The process is not recoverable due to terminating while in a critical section */
	NCP_ST_TASK_IN_GLOBAL_CRITICAL_SECTION              = 3776,
	/*! The requested shared region is not included in the thread queue set */
	NCP_ST_TASK_SHARED_REGION_NOT_FOUND                 = 3777,    
	/*! The fixed pool mmap failed, likely because some portion of
	  the requested virtual address is occupied in the process' address
	  space. */
	NCP_ST_TASK_FIXED_POOL_MMAP_FAILED                  = 3778,
	NCP_ST_TASK_FIXED_POOL_TASK_HEADER_VIOLATION        = 3779,
	/*! The user attempted an operation on an unconfigured NCA queue */
	NCP_ST_TASK_NCA_QUEUE_NOT_CONFIGURED                = 3780,
	/*! The user must specify a queue group for the NCA queue */
	NCP_ST_TASK_NCA_QUEUE_GROUP_NOT_SPECIFIED           = 3781,
	/*! The specified NCA queue is not a member of the queue group */
	NCP_ST_TASK_NCA_QUEUE_NOT_A_MEMBER                  = 3782,
	/*! The user attempted to add an NCA queue to a disabled queue group */
	NCP_ST_TASK_QUEUE_GROUP_NOT_ENABLED                 = 3783,
	/*! The pool associated with the task handle needs a restart. */
	NCP_ST_TASK_POOL_RESTART_NEEDED                     = 3784,
	/*! The pool associated with the task handle doesn't need a reinitialization. */
	NCP_ST_TASK_NO_POOL_REINIT_REQUIRED                 = 3785,
	/*! There is already a thread waiting on this CPU pool in this process */
	NCP_ST_TASK_THREAD_ALREADY_WAITING                  = 3786,
	/*! The requested operation is not valid for tasks with a combined header */
	NCP_ST_TASK_HEADER_IS_NOT_SEPARATE                  = 3787,
	/*! Recursion detected while processing API in send_done  or free_done function.   Invalid API context.   Applications are not
	 * allowed to call certain APIs in the context of the send_done or free_done context.   Additionally, applications are not allowed to
	 * to call any variation of task buffer free if they are using task buffers from a VP managed shared pool (2..7)
	 */
	NCP_ST_TASK_SENDQUEUE_CALLBACK_RECURSION_DETECTED   = 3788,
	/*! The queue group cannot be deleted when one or more iPCQs are fed by it */
	NCP_ST_TASK_QUEUE_GROUP_FEEDS_IPCQ                  = 3789,
	/*! The TQS is already configured */
	NCP_ST_TASK_TQS_ALREADY_CONFIGURED                  = 3790,
	/*! The config file specifies more than 16 enabled iPCQs. On the FPGA,
	 *  there are only 16. */
	NCP_ST_TASK_IPCQ_CONFIGURATION_EXCEEDS_16           = 3791,
	/*! The config file specifies more than 16 enabled NCA queues. On the FPGA,
	 *  there are only 16. */
	NCP_ST_TASK_NCA_QUEUE_CONFIGURATION_EXCEEDS_16      = 3792,
	/*! Attempted to configure a TQS on an A53 NCAP that does not exist. On the
	 * regular FPGA only NCAP0 exists, and on a super FPGA NCAPs 0, 2, and 4
	 * exist. */
	NCP_ST_TASK_NCAP_DOES_NOT_EXIST                     = 3793,

	/*
	 * ACHTUNG!! 
	 *
	 * All of the sysmem PHY status codes are duplicated for treemem.
	 * Since the PHY code is common between each, the PHY init code 
	 * just uses the sysmem code and then adds an offset if it was 
	 * initializing treemem. So if any new SYSMEM_PHY status codes 
	 * are added the same TREEMEM_PHY code must also be added in the
	 * same relative place.
	 */
   
	/*! The sysmem PHY CPC calibration sequence was timed out by software.  */
	NCP_ST_SYSMEM_PHY_CPC_CAL_TIMEOUT           = 3801,
	/*! The sysmem PHY training sequence was timed out by hardware
	 *   before the training operation was succesfully completed. */
	NCP_ST_SYSMEM_PHY_TRAIN_TIMEOUT             = 3802,
	/*!  The sysmem PHY training sequence was timed out by software. */
	NCP_ST_SYSMEM_PHY_TRAIN_SW_TIMEOUT          = 3803,
	/*!  The sysmem PHY write leveling sequence did not complete succesfully */
	NCP_ST_SYSMEM_PHY_WL_ERR                    = 3804,
	/*!  The sysmem PHY write leveling sequence could not complete due to an invalid delay value  */
	NCP_ST_SYSMEM_PHY_WL_DLY_ERR                = 3805,
	/*!  The sysmem PHY ECC write leveling sequence did not complete succesfully */
	NCP_ST_SYSMEM_PHY_ECC_WL_ERR                = 3806,
	/*!  The sysmem PHY ECC write leveling sequence could not complete due to an invalid delay value  */
	NCP_ST_SYSMEM_PHY_ECC_WL_DLY_ERR            = 3807,
	/*!  The sysmem PHY read fifo delay optimization function did not
	 *   complete successfully. */
	NCP_ST_SYSMEM_PHY_RDFIFO_OPT_ERR            = 3808,
	/*!  The sysmem PHY reported a CPC error */
	NCP_ST_SYSMEM_PHY_CPC_ERR                   = 3809,
	/*!  The sysmem PHY reported a RD_DLY error */
	NCP_ST_SYSMEM_PHY_RD_DLY_ERR                = 3810,
	/*!  The sysmem PHY reported a RD_CAL error */
	NCP_ST_SYSMEM_PHY_RD_CAL_ERR                = 3811,
	/*!  The sysmem PHY reported a WR_LVL error */
	NCP_ST_SYSMEM_PHY_WR_LVL_ERR                = 3812,
	/*!  The sysmem PHY reported a RD_LVL error */
	NCP_ST_SYSMEM_PHY_RD_LVL_ERR                = 3813,
	/*!  The sysmem PHY reported a Gate training error */
	NCP_ST_SYSMEM_PHY_GT_TRN_ERR                = 3814,
	/*!  The sysmem PHY reported a CMD_DLY error */
	NCP_ST_SYSMEM_PHY_CMD_DLY_ERR               = 3815,

	/*! The treemem PHY CPC calibration sequence was timed out by software.  */
	NCP_ST_TREEMEM_PHY_CPC_CAL_TIMEOUT          = 3901,
	/*! The treemem PHY training sequence was timed out by hardware
	 *   before the training operation was succesfully completed. */
	NCP_ST_TREEMEM_PHY_TRAIN_TIMEOUT            = 3902,
	/*!  The treemem PHY training sequence was timed out by software. */
	NCP_ST_TREEMEM_PHY_TRAIN_SW_TIMEOUT         = 3903,
	/*!  The treemem PHY write leveling sequence did not complete succesfully */
	NCP_ST_TREEMEM_PHY_WL_ERR                   = 3904,
	/*!  The treemem PHY write leveling sequence could not complete due to an invalid delay value  */
	NCP_ST_TREEMEM_PHY_WL_DLY_ERR               = 3905,
	/*!  The treemem PHY ECC write leveling sequence did not complete succesfully */
	NCP_ST_TREEMEM_PHY_ECC_WL_ERR               = 3906,
	/*!  The treemem PHY ECC write leveling sequence could not complete due to an invalid delay value  */
	NCP_ST_TREEMEM_PHY_ECC_WL_DLY_ERR           = 3907,
	/*!  The treemem PHY read fifo delay optimization function did not
	 *   complete successfully. */
	NCP_ST_TREEMEM_PHY_RDFIFO_OPT_ERR           = 3908,
	/*!  The treemem PHY reported a CPC error */
	NCP_ST_TREEMEM_PHY_CPC_ERR                  = 3909,
	/*!  The treemem PHY reported a RD_DLY error */
	NCP_ST_TREEMEM_PHY_RD_DLY_ERR               = 3910,
	/*!  The treemem PHY reported a RD_CAL error */
	NCP_ST_TREEMEM_PHY_RD_CAL_ERR               = 3911,
	/*!  The treemem PHY reported a WR_LVL error */
	NCP_ST_TREEMEM_PHY_WR_LVL_ERR               = 3912,
	/*!  The treemem PHY reported a RD_LVL error */
	NCP_ST_TREEMEM_PHY_RD_LVL_ERR               = 3913,
	/*!  The treemem PHY reported a Gate training error */
	NCP_ST_TREEMEM_PHY_GT_TRN_ERR               = 3914,
	/*!  The treemem PHY reported a CMD_DLY error */
	NCP_ST_TREEMEM_PHY_CMD_DLY_ERR              = 3915,

	/*!  DDR initialization resulted in error */
	NCP_ST_TREEMEM_DDR_INIT_ERR                 = 3950,

	/*! The sysmem handle is invalid */
	NCP_ST_SYSMEM_INVALID_HANDLE                = 3970,

	/*! There was an error initializing the sysmem lock */
	NCP_ST_SYSMEM_SEM_INIT_ERROR                = 3971,


	/*!  an invalid system memory ID was specified */
	NCP_ST_SYSMEM_INVALID_ID                    = 4001,
	/*!  and invalid system memory topology was specified */
	NCP_ST_SYSMEM_INVALID_TOPOLOGY              = 4002,

	/*! The system memory totalSize specified in the config MemoryLayout
	 *  section exceeds the total physical memory on this platform
	 */
	NCP_ST_SYSMEM_LAYOUT_SIZE_EXCEEDS_PHYS_SIZE = 4003,

	/*! The system memory being used by the current operating system
	 *  is greater than the OS Memory Size specified in the MemoryLayout
	 *  section of the config.
	 */
	NCP_ST_SYSMEM_LAYOUT_OS_MEMORY_SIZE_MISMATCH = 4004,

	/*! The dmaBuffersSize specified in the MemoryLayout section of
	 *  the config is smaller than that being used by the RTE.
	 */
	NCP_ST_SYSMEM_LAYOUT_DMA_BUFFER_SIZE_MISMATCH = 4005,

	/*! sysmem auto-detect found that DIMM slot 0 was not populated */
	NCP_ST_SM_DIMM0_NOT_POPULATED               = 4006,
	/*! sysmem auto-detect found that DIMM slot 1 was populated for one
	 * sysmem but not the other */
	NCP_ST_SM_DIMM1_NOT_POPULATED               = 4007,
	/*! sysmem auto-detect found that not all DIMMs have the same SPD */
	NCP_ST_SM_DIMM_SPD_MISMATCH                 = 4008,
	/*! the sysmem config specified ECC enabled, but the sysmem auto-detect
	 * found that the DIMM does not support ECC */
	NCP_ST_SM_DIMM_ECC_NOT_SUPPORTED            = 4009,

	/* Subnet API status codes */
	NCP_ST_SUBNET_SEM_INIT_ERROR                = 4101, /*!< Error in initializing semaphore */
	NCP_ST_SUBNET_INVALID_PTN                   = 4102, /*!< Invalid pattern */
	NCP_ST_SUBNET_INVALID_HDL                   = 4103, /*!< Invalid handle */
	NCP_ST_SUBNET_NO_MATCH                      = 4104, /*!< No match */
	NCP_ST_SUBNET_INVALID_XSIZE                 = 4105, /*!< Invalid number of wild card bits */
	NCP_ST_SUBNET_INVALID_BUCKET_IDX            = 4106, /*!< Invalid bucket index*/
	NCP_ST_SUBNET_INVALID_CHECKPOINT            = 4107, /*!< Invalid checkpoint */
	NCP_ST_SUBNET_READ_ERROR                    = 4108, /*!< Checkpoint read error */
	NCP_ST_SUBNET_WRITE_ERROR                   = 4109, /*!< Checkpoint write error */

	/* eioa status codes */
	NCP_ST_INVALID_TS_INDEX                     = 4201,
	/*!< Indexing error accessing the 64 entry timestamp table */
	NCP_ST_INVALID_TS_VALUE                     = 4202, /*!< */
	NCP_ST_MAC_INVALID_SPEED                    = 4203,
	/*!< When the port speed is out of range of enum ncp_mac_speed_t */
	NCP_ST_MAC_INVALID_DUPLEX                   = 4204,
	/*!<  The boolean duplex value is out of range, or Half Duplex value
	 * is being applied to an Full Duplex only port*/
	NCP_ST_MAC_INVALID_MAC                      = 4205,
	/*!< The EIOA handle contained in the ncp handle provided is not valid. */
	NCP_ST_EIOA_HANDLE_INVALID                  = 4206,
	/*!< Initialization of the EIOA state protection semaphore failed. */
	NCP_ST_EIOA_SEM_INIT_ERROR                  = 4207,
	/*!< When the MAC Channel is out of range of enum ncp_macChan_t */
	NCP_ST_EIOA_INVALID_TAG                     = 4208,
	/*!< When one or more of the tag parameters are out of range */
	NCP_ST_EIOA_INVALID_VLAN_TYPE               = 4209,
	/*!< When VLAN user type paramter(s) are out of range */
	NCP_ST_EIOA_INVALID_BUFFER                  = 4210,
	/*!< One or more pointers to external parameters passed to the API
	 * are NULL or bad */
	NCP_ST_EIOA_INVALID_PORT_CONFIG             = 4211,
	/*!< An API has detected an invalid port configuration. This may be
	 * bad parameter(s) or missing functioality for a specified port */
	NCP_ST_EIOA_MDIO_STATUS_MSB_READ_ERROR      = 4212,
	/*!< An API has detected that polloing of status_msb bit of the status
	 * register has finished without the status_msb bit change */
	NCP_ST_EIOA_MDIO_CONTROL_BUSY_READ_ERROR    = 4213,
	/*!< An API has detected that polloing of mdio_busy bit of the control
	 * register has finished without the mdio_busy bit change */
	NCP_ST_EIOA_PORT_NOT_CONFIGURED             = 4214,
	/*!< Port was not present while loading the configuration file, or
	 *   an error occurred during configuration of the port. */
	NCP_ST_EIOA_MCAST_TBL_IDX_ERROR             = 4215,
	/*!< Indexing error accessing the EIOA Multicast table */
	NCP_ST_EIOA_SPEED_NOT_SUPPORTED             = 4216,
	/*!< Port speed setting is not supported on this platform */
	NCP_ST_EIOA_FUNC_NOT_SUPPORTED              = 4217,
	/*!< Function not supported on this platform */
	NCP_ST_EIOA_PORT_SHAPER_INVALID_VALUE       = 4218,
	/*!< The shaper value specified is invalid */
	NCP_ST_EIOA_PORT_SCHEDULER_INVALID_VALUE    = 4219,
	/*!< The scheduler value specified is invalid */
	NCP_ST_EIOA_INVALID_EIOA                    = 4220,
	/*!The EIOA number is not valid. */
	NCP_ST_EIOA_MEM_INIT_ERROR                  = 4221,
	/*!Memory initialization failed on EIOA */
	NCP_ST_EIOA_COS_INVALID                     = 4222,
	/*!< The COS value specified is invalid. */
	NCP_ST_EIOA_DSCP_INVALID                    = 4223,
	/*!< The DSCP value specified is invalid. */
	NCP_ST_EIOA_INVALID_VLAN_ID                 = 4224,
	/*!< The vlan id specified is invalid or not configured. */
	NCP_ST_EIOA_VLAN_ID_ALREADY_DEFINED         = 4225,
	/*!< The vlan id is already defined. */
	NCP_ST_EIOA_PORT_DEFAULT_VLAN_ID            = 4226,
	/*!< The vlanid trying to be removed is used as default vlan id for port. */
	NCP_ST_EIOA_INVALID_CVLAN_ID                = 4227,
	/*!< The cvlan id specified is invalid or not configured. */
	NCP_ST_EIOA_HSS_PHY_APB2SER_CMD_TIMEOUT     = 4228,
	/*!< Timed out waiting for command on HSS to complete. */
	NCP_ST_EIOA_HSS_PHY_APB2SER_AHBL_TIMEOUT     = 4229,
	/*!< AHBL timeout status on HSS. */
	NCP_ST_EIOA_HSS_PHY_APB2SER_HRESP_ERR        = 4230,
	/*!< Non-zero response status on HSS. */
	NCP_ST_EIOA_HSS_PLL_ERR                      = 4231,
	/*!< Error in configuration of PLL for EIOA HSS */
	NCP_ST_EIOA_HSS_SERDES_APB2SER_CMD_TIMEOUT   = 4232,
	/*!< Timed out waiting for command on HSS to complete. */
	NCP_ST_EIOA_POWER_NOT_ENABLED                = 4233,
	/*!< No ports are defined for this EIOA. The EIOA is not enabled to save power. */
	NCP_ST_EIOA_PORT_SWITCHOVER_COMBINATION_NOT_SUPPORTED = 4234,
	/*!< EIOA port switchover combination is not supported. */
	NCP_ST_EIOA_PORT_SWITCHOVER_NOT_FIBER = 4235,
	/*!< EIOA port that is being switched over has isFiber as FALSE. */
	NCP_ST_EIOA_AUTO_NEGOTIATION_NOT_STARTED = 4236,
	/*!< Auto Negotiation is not set or started for FEC */
	NCP_ST_EIOA_PORT_SWITCHOVER_BAD_PARAMETERS   = 4237,
	/*!< EIOA port that is being switched over was given bad parameters */
	NCP_ST_EIOA_HSS_PHY_BAD_PARAMETERS           = 4238,
	/*!< EIOA HSS function given bad parameters */
	NCP_ST_EIOA_INVALID_HANDLE                   = 4239,
	/*!< EIOA handle is invalid */
	NCP_ST_EIOA_INVALID_PORT_HANDLE              = 4240,
	/*!< EIOA PORT handle is invalid */
	NCP_ST_EIOA_PORT_INVALID_INTERFACE_TYPE      = 4241,
	/*!< EIOA PORT wrong interface type */
	NCP_ST_EIOA_PORT_INVALID_PRIORITY      	 = 4242,
	/*!< EIOA PORT out of range priority value */
	NCP_ST_EIOA_INVALID_VIRTUAL_DOMAIN_ID        = 4243,
	/*!< The virtual domain id specified is invalid. */
	NCP_ST_EIOA_INVALID_MPLS_LABEL               = 4244,
	/*!< The MPLS label specified is invalid. */
	NCP_ST_EIOA_INVALID_ISB                      = 4245,
	/*!< ISB called with invalid node id. */
	NCP_ST_EIOA_MCAST_TBL_ADDR_ERROR             = 4246,
	/*!< Invalid Multicast Table Address. */

	NCP_ST_EIOA_SWITCH_HANDLE_INVALID           = 4301,
	/*!< The EIOA Switch handle contained in the ncp handle provided is not valid */
	NCP_ST_EIOA_SWITCH_SEM_INIT_ERROR           = 4302,
	/*!< Initialization of the EIOA Switch state protection semaphore failed. */
	NCP_ST_EIOA_SWITCH_ENTRY_DISABLED           = 4303,
	/*!< The entry corresponding to the specified ID is disabled. */
	NCP_ST_EIOA_EPP_MEMORY_INIT_TIMEOUT         = 4304,
	/*!< EIOA EPP memory init timed out */
	NCP_ST_EIOA_IPP_MEMORY_INIT_TIMEOUT         = 4305,
	/*!< EIOA IPP memory init timed out */
	NCP_ST_EIOA_ACL_MEMORY_INIT_TIMEOUT         = 4306,
	/*!< EIOA ACL memory init timed out */
	NCP_ST_EIOA_BRIDGE_MEMORY_INIT_TIMEOUT      = 4307,
	/*!< EIOA bridge memory init timed out */
	NCP_ST_EIOA_POLICER_MEMORY_INIT_TIMEOUT     = 4308,
	/*!< EIOA policer memory init timed out */
	NCP_ST_EIOA_BRIDGE_SUPERVISOR_LEARN_TIMEOUT = 4309,
	/*!< EIOA bridge supervisor learn timed out */
	NCP_ST_EIOA_BRIDGE_SUPERVISOR_LEARN_FAILED  = 4310,
	/*!< EIOA bridge supervisor learn failed */
	NCP_ST_EIOA_BRIDGE_AGE_TIMEOUT_CONFIG_ERROR = 4311,
	/*!< EIOA bridge age timeout units could not be configured */
	NCP_ST_EIOA_BRIDGE_AGGREGATION_HASH_INVALID_IDX = 4312,
	/*!< EIOA bridge aggregation hash idx is invalid (valid range is 0-31) */
	NCP_ST_EIOA_BRIDGE_INVALID_LOGICAL_PORT_ID  = 4313,
	/*!< EIOA bridge invalid logical port id (valid range is 0-9) */
	NCP_ST_EIOA_BRIDGE_INVALID_AGE              = 4314,
	/*!< EIOA bridge age is invalid (range is 0-63) and cannot exceed port's maximum age */
	NCP_ST_EIOA_BRIDGE_INVALID_KEY_TYPE         = 4315,
	/*!< EIOA bridge key type is invalid. For example, a key type of IVL requires the bridge mode to be configured as IVL */
	NCP_ST_EIOA_BRIDGE_LEARNING_NOTIFICATION_DISABLED = 4316,
	/*!< EIOA bridge learning notification is disabled */
	NCP_ST_EIOA_BRIDGE_SUPERVISOR_UNLEARN_TIMEOUT = 4317,
	/*!< EIOA bridge supervisor unlearn timed out */
	NCP_ST_EIOA_BRIDGE_SUPERVISOR_UNLEARN_FAILED  = 4318,
	/*!< EIOA bridge supervisor unlearn failed */
	NCP_ST_EIOA_BRIDGE_AGE_HYSTERESIS_INVALID = 4319,
	/*!< EIOA bridge age hysteresis value is out of range (0-63). */

	/* EIOA Policer status codes */

	NCP_ST_EIOA_POLICER_HANDLE_INVALID           = 4401,
	/*!< The EIOA Policer handle contained in the ncp handle provided is not valid */
	NCP_ST_EIOA_POLICER_GLOBAL_MAX_RATE_INVALID  = 4402,
	/*!< EIOA policer maximum policing rate cannot be programmed */
	NCP_ST_EIOA_POLICER_RATE_TOO_FAST            = 4403,
	/*!< EIOA policer specified with a rate higher than the maximum rate */
	NCP_ST_EIOA_POLICER_RATE_TOO_SLOW            = 4404,
	/*!< EIOA policer specified with a rate lower than the minimum rate */
	NCP_ST_EIOA_POLICER_RATE_PEAK_LESS_THAN_COMMITTED = 4405,
	/*!< EIOA policer peak rate specified is less that the committed rate specified */
	NCP_ST_EIOA_SWITCH_POLICER_MODE_INVALID      = 4406,
	/*!< EIOA policer call is not valid in the current policing mode */
	NCP_ST_EIOA_SWITCH_POLICER_ID_INVALID        = 4407,
	/*!< EIOA policer ID is invalid */
	NCP_ST_EIOA_SWITCH_POLICER_MAX_BURST_SIZE_INVALID = 4408,
	/*!< EIOA policer max burst size specification is invalid */
	NCP_ST_EIOA_SWITCH_POLICER_VLAN_ID_INVALID   = 4409,
	/*!< EIOA policer VLAN ID is invalid */
	NCP_ST_EIOA_SWITCH_POLICER_ACL_ID_INVALID    = 4410,
	/*!< EIOA policer ACL ID is invalid */
	NCP_ST_EIOA_SWITCH_POLICER_COLOR_INVALID     = 4411,
	/*!< EIOA policer COLOR specification invalid */
	NCP_ST_EIOA_SWITCH_POLICER_COS_INVALID       = 4412,
	/*!< EIOA policer COS value is invalid */
	NCP_ST_EIOA_SWITCH_POLICER_DSCP_INVALID      = 4413,
	/*!< EIOA policer DSCP value is invalid */

	NCP_ST_EIOA_SWITCH_STATS_MEMORY_INIT_TIMEOUT = 4414,
	/*!< EIOA SWITCH stats memory init timed out */
	NCP_ST_EIOA_SWITCH_STATS_COUNTER_NOT_DEFINED = 4415,
	/*!< EIOA SWITCH statistics counter not defined */
	NCP_ST_EIOA_SWITCH_STATS_INVALID_DIRECTION   = 4416,
	/*!< EIOA SWITCH statistics invalid direction parameter */
	NCP_ST_EIOA_SWITCH_STATS_INVALID_PORT_GROUP  = 4417,
	/*!< EIOA SWITCH statistics invalid port group parameter */
	NCP_ST_EIOA_SWITCH_STATS_INVALID_DSCP_GROUP  = 4418,
	/*!< EIOA SWITCH statistics invalid DSCP group parameter */
	NCP_ST_EIOA_SWITCH_STATS_INVALID_VLAN_GROUP  = 4419,
	/*!< EIOA SWITCH statistics invalid vlan group parameter */
	NCP_ST_EIOA_SWITCH_STATS_INVALID_DSCP        = 4420,
	/*!< EIOA_SWITCH statistics invalid dscp parameter */
	NCP_ST_EIOA_SWITCH_STATS_INVALID_VLAN        = 4421,
	/*!< EIOA_SWITCH statistics invalid vlan parameter */
	NCP_ST_EIOA_SWITCH_STATS_INVALID_COUNTER     = 4422,
	/*!< EIOA_SWITCH statistics invalid counter parameter */
	NCP_ST_EIOA_SWITCH_STATS_INVALID_PACKET_TYPE = 4423,
	/*!< EIOA_SWITCH statistics invalid packet type parameter */
	NCP_ST_TASK_GEN_RATE_LIMIT_CONFIG_ERROR      = 4424,
	/*!< EIOA task gen rate limit out of range */
	NCP_ST_MAC_PHY_OUI_UNKNOWN                   = 4425,
	/*!< Unknown Ethernet PHY connected to port */
	NCP_ST_MAC_PHY_OUI_FOUND                     = 4426,
	/*!< Known Ethernet PHY connected to port */
	NCP_ST_MAC_SPEED_REQUIRES_FIBER              = 4427,
	/*!< Speed setting requires Fiber interface */

	NCP_ST_EIOA_COMMON_SHARED_MAC_ADDR_INVALID_INDEX = 4428,
	/*!< Shared mac address index provided is out of range. */

	NCP_ST_EIOA_COMMON_SHARED_MAC_ADDR_INVALID_MAC_ADDR = 4429,
	/*!< Shared mac address provided is NULL or invalid. */

	NCP_ST_EIOA_COMMON_TASK_PRIORITY_INVALID     = 4430,
	/*!< Shared mac address provided is NULL or invalid. */

	NCP_ST_EIOA_COMMON_BRIDGING_VP_ID_INVALID    = 4431,
	/*!< EIOA bridging vp id is invalid */

	NCP_ST_EIOA_COMMON_VP_NOT_SET                = 4432,
	/*!< EIOA the vp has not been set and is undefined */

	NCP_ST_EIOA_COMMON_VP_TYPE_INVALID           = 4433,
	/*!< EIOA vp type is invalid */

	NCP_ST_EIOA_PORT_INGRESS_ETHERTYPE_IDX_INVALID = 4434,
	/*!< Ethertype index is either out of range or not defined as valid. */

	NCP_ST_EIOA_PORT_VLANS_PRESENT               = 4435,
	/*!< Vlans are still present in this port to change the qinq mode. */

	NCP_ST_EIOA_PORT_NON_QINQ                    = 4436,
	/*!< The EIOA port is configured for non qinq mode. */

	NCP_ST_EIOA_PORT_VLAN_MAP_FULL               = 4437,
	/*!< No free cvlan/svlan map entry is available for this port. */

	NCP_ST_EIOA_PORT_MACSEC_NOT_SUPPORTED        = 4438,
	/*!< MACsec not supported in this port. */

	NCP_ST_EIOA_PORT_MACSEC_TX_INVALID_SA        = 4439,
	/*!< Invalid Security Association value. */

	NCP_ST_EIOA_PORT_MACSEC_TX_INVALID_SC        = 4440,
	/*!< Invalid Security Channel value. */

	NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_ACL_ID   = 4441, /*!< Invalid ACL Id. For ACP2500 valid acl id is in the range 0 <= acl id < 32 */ 
	NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_RULE_ID  = 4442, /*!< Invalid Rule Id. For ACP2500 valid rule id is in the range 0 <= rule id < 16 */ 
	NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_RULES        = 4443, /*!< Number of ACL rules exceeds the limit. For ACP2500 the limit is 16 ACL rules */
	NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IPv4_ADDRESSES = 4444, /*!< Number of IPv4 addresses exceeds the limit. For ACP2500 the limit is 256 IPv4 addresses */
	NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_IP_ADDRESSES = 4445,       /*!< Number of IP addresses exceeds the limit. For ACP2500 the limit is 96 IP addresses */
	NCP_ST_EIOA_SWITCH_ACL_IPv6_ADDRESS_IN_IPv4_MODE = 4446,   /*!< Encountered an IPv6 address in IPv4 mode of operation */
	NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_LAYER_4_PORTS = 4447, /*!< Number of Layer 4 ports exceeds the limit. For ACP2500 the limit is 256 ports */
	NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_ADDRESSES = 4448, /*!< Number of MAC addresses exceeds the limit. For ACP2500 the limit is 256 addresses */
	NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MAC_WILDCARD_ADDRESSES = 4450, /*!< Number of MAC addresses with wildcards exceeds the limit. For ACP2500 the limit is 4 addresses */
	NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_MACSEC_ETHERTYPE_PROTOCOL_VALUES = 4451, /*!< Number of MAC Sec, Ethertype and Protocol combinations exceeds the limit. For ACP2500 the limit is 32 combinations */
	NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_DSCP_COS_VALUES = 4452, /*!< Number of DSCP and COS combinations exceeds the limit. For ACP2500 the limit is 32 */
	NCP_ST_EIOA_SWITCH_ACL_INVALID_COS           = 4453, /*!< Encountered a COS not in the range 0 <= COS < 8 */
	NCP_ST_EIOA_SWITCH_ACL_INVALID_DSCP          = 4454, /*!< Encountered a COS not in the range 0 <= DSCP < 64 */
	NCP_ST_EIOA_SWITCH_ACL_INVALID_VLAN_ID       = 4455, /*!< Encountered a VLAN Id not in the range 0 <= VLAN Id < 4096 */
	NCP_ST_EIOA_SWITCH_ACL_INVALID_POLICER_ID    = 4456, /*!< Encountered an invalid Policer Id */
	NCP_ST_EIOA_SWITCH_ACL_INVALID_POLICER_MAP   = 4457, /*!< Policer selection mode does not allow this map */
	NCP_ST_EIOA_SWITCH_ACL_TOO_MANY_ROUTES       = 4458, /*!< Number of routes exceed the limit. For ACP2500 the limit is 256*/
	NCP_ST_EIOA_SWITCH_ACL_UNKNOWN_ROUTE         = 4459, /*!< No matching route found for the given destination IP address */
	NCP_ST_EIOA_SWITCH_ACL_ROUTE_INVALID_SUB_INTERFACE = 4460, /*!< The sub interface specified in the route is unreachable by the destination VP*/
	NCP_ST_EIOA_SWITCH_ACL_OUT_OF_RANGE_PBR_ID   = 4461,         /*!< Invalid ACL Id. For ACP2500 valid acl id is in the range 0 <= acl id < 32 */ 
	NCP_ST_EIOA_SWITCH_ACL_ACTION_ID_CLASH       = 4462, /*!< Action Id was used before for another route hence unavailable*/
	NCP_ST_EIOA_SWITCH_ACL_INVALID_HANDLE        = 4463, /*!< Invalid ACL handle */
	NCP_ST_EIOA_SWITCH_ACL_MAC_WILDCARD_ADDRESS_PARTIAL_OVERLAP = 4464, /*!< If MAC wild card addresses can be thought of sets of MAC addresses, then there are at least two MAC wild card addresses that have an intersection which is not the NULL set and which is not equal to one of the two wild card addresses */
	NCP_ST_EIOA_SWITCH_ACL_UNSATISFIABLE_PORT_VLAN_TO_ACL_ID_COMBINATIONS = 5111, /*!< If in Port VLAN ACL selection mode, there are too many port VLAN to ACL id combinations than there is HW tables for */
	NCP_ST_EIOA_SWITCH_ACL_INVALID_DOMAIN_ID    = 5112, /*< If a Domain Id is not within the range 0 <= Domain Id < 512 */
	NCP_ST_EIOA_SWITCH_ACL_INVALID_NON_IP_TRUST_MODE = 5113, /*!< If an invalid Non IP trust mode is used */

	NCP_ST_EIOA_SWITCH_BRIDGE_INVALID_HANDLE     = 4465, /*!< Invalid Bridging handle */
	NCP_ST_EIOA_SWITCH_STATS_INVALID_HANDLE      = 4466, /*!< Invalid Statistics handle */
	NCP_ST_EIOA_SWITCH_BRIDGE_DESTINATION_VP_INVALID_NAME = 4467, /*!< Invalid Destination VP name */
	NCP_ST_EIOA_BRIDGE_DESTINATION_VP_DUPLICATE_NAME = 4468, /*!< Duplicate destination VP name */
	NCP_ST_EIOA_INVALID_DOMAIN_ID = 4469, /*! Invalid domain id (domain ids are in the range 0-511) */
	NCP_ST_EIOA_MAP_NOT_SET		= 4470, /*!< Map is not set and attempt is made to get/remove it */
	NCP_ST_EIOA_VLAN_MAP_PRESENT	= 4471, /*!< Map is already set; trying to overwrite */
	NCP_ST_EIOA_PAUSE_MODE_NOT_SUPPORTED = 4472, /*!< 802.3 pause mode not supported by this API.*/

	/* Crash Analysis Tools status codes */
	NCP_ST_CAT_NOT_CONFIGURED                    = 4501, /*!< CAT Module not configured */
	NCP_ST_CAT_NOT_ENABLED                       = 4502, /*!< CAT Module not enabled */
	NCP_ST_CAT_INSUFFICIENT_MEMORY               = 4503, /*!< Unable to allocate memory for CAT module */
	NCP_ST_CAT_MEMORY_SIZE_INVALID               = 4504, /*!< Configured memory size invalid e.g. zero */
	NCP_ST_CAT_MEMORY_ADDR_INVALID               = 4505, /*!< Configured memory storage address invalid e.g. zero */
	NCP_ST_CAT_MISSING_WRITEFN                   = 4506, /*!< No 'writeFn' ptr provided to ncp_cat_dev_iofns() */
	NCP_ST_CAT_MISSING_READFN                    = 4507, /*!< No 'readFn' ptr provided to ncp_cat_dev_iofns() */
	NCP_ST_CAT_DATA_BUFFER_INVALID               = 4508, /*!< Memory buffer invalid e.g. NULL pointer */
	NCP_ST_CAT_DATA_BUFSIZE_INVALID              = 4509, /*!< Memory buffer size invalid e.g. zero size */
	NCP_ST_CAT_INVALID_ITERATOR                  = 4510, /*!< Invalid offset/readSize arguments to ncp_dev_cat_read */
	NCP_ST_CAT_WRITE_ERROR                       = 4511, /*!< 'writeFn' encounters error */
	NCP_ST_CAT_READ_ERROR                        = 4512, /*!< 'readFn' encounters error */
	NCP_ST_CAT_DATA_EOF                          = 4513, /*!< ncp_dev_cat_read() completed */
	NCP_ST_CAT_MISMATCH_DATA_TRUNCATED           = 4514, /*!< Block of recovered registers provided to ncp_cat_save() is too short to contain all of the expected registers */
	NCP_ST_CAT_MISMATCH_DEVICE                   = 4515, /*!< Block of recovered registers provided to ncp_cat_save() was saved for a different ACP device than the current RTE expects */
	NCP_ST_CAT_MISMATCH_RTE_REVISION             = 4516, /*!< Block of recovered registers provided to ncp_cat_save() was saved for a different version of RTE software than the current version of RTE supports */
	NCP_ST_CAT_NO_RECOVERY_DATA                  = 4517, /*!< Block of recovered registers provided to ncp_cat_save() does not contain a valid block of information */
	NCP_ST_CAT_CORRUPT_RECOVERY_DATA             = 4518, /*!< CRC32 check on Block of recovered registers provided to ncp_cat_save() calculates a different checksum than the one expected i.e. data is apparently corrupt */
	NCP_ST_CAT_NO_PREVIOUS_WRITE                 = 4519, /*!< An invocation of 'ncp_cat_write()' must occur before this function call. */
	NCP_ST_CAT_RAW_DATA_POLL                     = 4520, /*!< 'ncp_cat_read_raw()' was used to poll for the size of a block without actually reading the data */

	/* SAL */
	NCP_ST_SAL_SSID_FAILURE                      = 4601, /*!< Could not change process ssid in sal daemonize */
	NCP_ST_SAL_CHDIR_FAILURE                     = 4602, /*!< could not chdir to root in sal daemonize */

	/* ACP device alarm reporting interface */
	NCP_ST_ALARM_NONE_PENDING                    = 4701, /*!< No alarms are pending */
	NCP_ST_ALARM_NOT_CONFIGURED                  = 4702, /*!< Alarm reporting has not been configured */
	NCP_ST_ALARM_NO_HANDLER_FOR_IRQ              = 4703, /*!< An alarm interrupt occurred, but no handler was registered for that IRQ */
	NCP_ST_ALARM_NO_SOURCE_FOR_IRQ               = 4704, /*!< An alarm interrupt occurred, but none of the source registers indicate an alarm */
	NCP_ST_ALARM_INVALID_IRQ                     = 4705, /*!< An RTE module attempted to register an unexpected IRQ (internal error) */

	/* TDMIOA status codes */
	NCP_ST_TDMIOA_INVALID_RX_PREPEND_SIZE        = 4801, /*!< Invalid receive prepend size */
	NCP_ST_TDMIOA_INVALID_TX_PREPEND_SIZE        = 4802, /*!< Invalid transmit prepend size */

	NCP_ST_PROFILER_ENTRIES_BUFFER_INVALID       = 4901, /*!< entries buffer provided is invalid */


	/* NRCP API status code */
	NCP_ST_NRCP_INVALID_PARAM                    = 5001, /*!< invalid NRCP parameter */
	NCP_ST_NRCP_POLL_TIMEOUT                     = 5002, /*!< NRCP poll timeout */
	NCP_ST_NRCP_NOT_SUPPORTED                    = 5003, /*!< NRCP feature not supported */

	/* ECM status codes */
	/*! ECM is not supported by the device */
	NCP_ST_ECM_NOT_SUPPORTED                    = 5101,
	/*! Offset is not a valid fuse addresss */
	NCP_ST_ECM_OFFSET_INVALID                   = 5102,
	/*! The length of the data to be written to the fuse field is invalid */
	NCP_ST_ECM_VALUE_LENGTH_INVALID             = 5103,
	/*! The ECM is busy */
	NCP_ST_ECM_BUSY                             = 5104,
	/*! Fuse read timed out */
	NCP_ST_ECM_FUSE_READ_TIMEOUT                = 5105,
	/*! Fuse write timed out */
	NCP_ST_ECM_FUSE_WRITE_TIMEOUT               = 5106,
	/*! Error occurred during fuse read sequence */
	NCP_ST_ECM_FUSE_READ_ERROR                  = 5107,
	/*! Error occurred during fuse write sequence */
	NCP_ST_ECM_FUSE_WRITE_ERROR                 = 5108,
	/*! Normal read following write did not return the expected data */
	NCP_ST_ECM_READ_MISCOMPARE                  = 5109,
	/*! Normal read following write did not return the expected data */
	NCP_ST_ECM_MARGIN_READ_MISCOMPARE           = 5110,

	/* DSP Status Codes */
	/*! DSP Initialization Failed */
	NCP_ST_DSP_INIT_FAILED                       = 5201,
	/*! DSP Application Memory Load Failed */
	NCP_ST_DSP_APP_NO_MEMORY                     = 5202,
	/*! DSP Queue Wait Timed Out */
	NCP_ST_DSP_DMA_QUEUE_FULL                    = 5203,
	/*! The specified DSP handle is not valid. */
	NCP_ST_DSP_INVALID_HANDLE                    = 5204,
	/*! There is a mix of unified and ext data/program regions. */
	NCP_ST_DSP_UNIFIED_FIELD_MISMATCH            = 5205,
	/*! The loaded application could not be verified. */
	NCP_ST_DSP_LOAD_ERROR                        = 5206,
	/*! The specified application is invalid. */
	NCP_ST_DSP_INVALID_APPLICATION               = 5207,
	/*! The DMA load timed out. */
	NCP_ST_DSP_DMA_LOAD_ERROR                    = 5208,
	/*! The DSP application unload process timed out. */
	NCP_ST_DSP_UNLOAD_TIMEOUT                    = 5209,
	/*! The specified core ID is invalid. */
	NCP_ST_DSP_INVALID_CORE_ID                   = 5210,
	/*! The specified core is already running. */
	NCP_ST_DSP_CORE_RUNNING                      = 5211,
	/*! The specified core ID is already shut down. */
	NCP_ST_DSP_CORE_SHUT_DOWN                    = 5212,
	/*! There was an error invalidating a cache. */
	NCP_ST_DSP_CACHE_INVALIDATE_ERROR            = 5213,


	/* LTEFE Status Codes */
	/*! LTEFE Initialization Failed */
	NCP_ST_LTEFE_INIT_FAILED                     = 5301,
	/*!< LTEFE handle is invalid */
	NCP_ST_LTEFE_INVALID_HANDLE                  = 5302,
	/*! The loaded application could not be verified */
	NCP_ST_LTEFE_LOAD_ERROR                      = 5303,
	/*!< The specified cluster is invalid. */
	NCP_ST_LTEFE_INVALID_CLUSTER                 = 5304,
	/*!< The LTEFE unload process timed out */
	NCP_ST_LTEFE_UNLOAD_TIMEOUT                  = 5305,
	/*!< The LTEFE application is invalid */
	NCP_ST_LTEFE_INVALID_APPLICATION             = 5306,

	/* RIF Status codes */
	/*! RIF is not configured. no handle available */
	NCP_ST_RIF_NOT_CONFIGURED			= 5401,
	/*! Invalid RIF Module Id */
	NCP_ST_RIF_INVALID_RIFMOD_ID		= 5402,
	/*! Invalid/ NULL buffer */
	NCP_ST_RIF_INVALID_BUFFER			= 5403,
	/*! AXC Map Missing in the map */
	NCP_ST_RIF_STREAM_AXC_MAP_MISSING		= 5404,
	/*! AXC Map already exists. */
	NCP_ST_RIF_STREAM_AXC_MAP_EXISTS		= 5405,
	/*! The RIF handle contained in the ncp handle provided is not valid. */
	NCP_ST_RIF_HANDLE_INVALID			= 5406,
	/*! Invalid data validation mode. */
	NCP_ST_RIF_INVALID_DATA_VALIDATION_MODE	= 5407,
	/*! Invalid Enque data format mode. */
	NCP_ST_RIF_INVALID_ENQUE_DATA_FORMAT_MODE	= 5408,
	/*! unimplemented feature/API. */
	NCP_ST_RIF_UNIMPLEMENTED			= 5409,
	/*! AxC container bandwith invalid. */
	NCP_ST_RIF_INVALID_AXC_BW			= 5410,
	/*! Buffer length/sub buffer length invalid. */
	NCP_ST_RIF_INVALID_BUFFER_LENGTH		= 5411,
	/*! Invalid sub buffer count. */
	NCP_ST_RIF_INVALID_SUB_BUFFER_COUNT		= 5412,
	/*! Invalid align length. */
	NCP_ST_RIF_INVALID_ALIGN_LENGTH		= 5413,
	/*! Stream is not created yet. */
	NCP_ST_RIF_STREAM_NOT_CREATED		= 5414,
	/*! Bitmap mode is invalid */
	NCP_ST_RIF_INVALID_BITMAP_MODE		= 5415,
	/*! Bitmap control selector is invalid */
	NCP_ST_RIF_INVALID_BITMAP_CTRL_SEL		= 5416,
	/*! Buffer mode is invalid */
	NCP_ST_RIF_INVALID_BUFFER_MODE		= 5417,
	/*! Bitmap mode enabled but bitmap ctrl disabled.*/
	NCP_ST_RIF_BITMAP_MODE_INCONSISTENT		= 5418,
	/*! lengthA value is invalid */
	NCP_ST_RIF_INVALID_LENGTHA_LENGTH		= 5419,
	/*! lengthB value is invalid */
	NCP_ST_RIF_INVALID_LENGTHB_LENGTH		= 5420,
	/*! Queue FIFO depth invalid */
	NCP_ST_RIF_INVALID_FIFO_DEPTH		= 5421,
	/*! Can't reconfigure an enabled stream.*/
	NCP_ST_RIF_STREAM_ENABLED_CANT_CONFIGURE	= 5422,
	/*! attemp to remap AxC not valid */
	NCP_ST_RIF_STREAM_AXC_ALREADY_MAPPED	= 5423,
	/*! No more space left in Queue FIFO */
	NCP_ST_RIF_FIFOQUEUE_EXHAUSTED		= 5424,
	/*! Buffer type is not one of continuous/sw triggered */
	NCP_ST_RIF_INVALID_BUFFER_TYPE		= 5425,
	/*! Link Id exceeds valid range. */
	NCP_ST_RIF_INVALID_LINK_ID			= 5426,
	/*! map lane Id > 64. */
	NCP_ST_RIF_INVALID_MAPLANE_ID		= 5427,
	/*! stream Id not in 0-127 range. */
	NCP_ST_RIF_INVALID_STREAM_ID		= 5428,
	/*! Trying to create a stream that exists */
	NCP_ST_RIF_STREAM_ALREADY_EXISTS		= 5429,
	/*! Initialization of the RIF state protection semaphore failed. */
	NCP_ST_RIF_SEM_INIT_ERROR			= 5430,
	/*! All stream Ids are provisioned in the system. 
	  no more free stream Ids available */
	NCP_ST_RIF_MAX_STREAM_LIMIT_REACHED		= 5431,
	/*! Attempt to re-enable a stream that is already enabled. */
	NCP_ST_RIF_STREAM_ALREADY_ENABLED		= 5432,
	/*! Attempt to disable a stream that is already disabled. */
	NCP_ST_RIF_STREAM_ALREADY_DISABLED		= 5433,
	/*! Align offset length is not a multiple of 4 or is > alignLength. */
	NCP_ST_RIF_INVALID_ALIGN_OFFSET_LENGTH	= 5434,
	/*! Virtual pipeline Id is not < 32 */
	NCP_ST_RIF_INVALID_VIRTUAL_PIPELINE_ID	= 5435,
	/*! AXC is not mapped yet to this stream. */
	NCP_ST_RIF_STREAM_AXC_MAP_NOT_AVAILABLE 	= 5436,
	/*! Buffer done task priotiy is not in valid rate of 0-7 */
	NCP_ST_RIF_INVALID_BUFFER_DONE_TASK_PRIORITY = 5437,
	/*! LinkId given in AXC Map to stream is not created yet. */
	NCP_ST_RIF_STREAM_MAP_LINK_NOT_VALID = 5438,
	/*! AXCId given in AXC Map to stream is not created yet. */
	NCP_ST_RIF_STREAM_MAP_AXC_NOT_VALID  = 5439,
	/*! Invalid RIF BCN Clock Source Selection */
	NCP_ST_RIF_INVALID_BCN_CLK_SRC_SEL		= 5440,
	/*! Invalid RIF BCN Divider */
	NCP_ST_RIF_INVALID_BCN_DIVIDER		= 5441,
	/*! Invalid RIF RFP Clock Source Selection */
	NCP_ST_RIF_INVALID_RFP_CLK_SRC_SEL		= 5442,
	/*! Invalid RIF RFP Divider */
	NCP_ST_RIF_INVALID_RFP_DIVIDER		= 5443,
	/*! Invalid BFN Start Position */
	NCP_ST_RIF_INVALID_BFN_START_POS		= 5444,
	/*! Invalid HFN Start Position */
	NCP_ST_RIF_INVALID_HFN_START_POS		= 5445,
	/*! Invalid Scrambler Seed */
	NCP_ST_RIF_INVALID_SCRAMBLER_SEED		= 5446,
	/*! Invalid Link Buffer Size per AxC */
	NCP_ST_RIF_INVALID_LINK_BUFFER_SIZE		= 5447,
	/*! Invalid Link Tx Protocol Version */
	NCP_ST_RIF_INVALID_TX_PROT_VERSION		= 5448,
	/*! Invalid Serdes Identifier */
	NCP_ST_RIF_INVALID_SERDES_ID		= 5449,
	/*! Invalid CPRI AxC Mapping Method */
	NCP_ST_RIF_INVALID_CPRI_MAP_METHOD		= 5450,
	/*! Invalid CPRI Oversampling Factor */
	NCP_ST_RIF_INVALID_OVERSAMPLING_FACTOR	= 5451,
	/*! Invalid CPRI K Value */
	NCP_ST_RIF_INVALID_CPRI_K_VALUE	= 5452,
	/*! Invalid RFP Delay */
	NCP_ST_RIF_INVALID_RFP_DELAY	= 5453,
	/*! Invalid RFP Async Reference */
	NCP_ST_RIF_INVALID_RFP_ASYNC_REF	= 5454,
	/*! Invalid RFP Input Counter */
	NCP_ST_RIF_INVALID_RFP_INPUT_COUNTER	= 5455,
	/*! Invalid RFP Sync Edge Selection */
	NCP_ST_RIF_INVALID_RFP_SYNC_EDGE	= 5456,
	/*! Invalid RFP Mode */
	NCP_ST_RIF_INVALID_RFP_MODE	= 5457,
	/*! Invalid RFP Output Mode */
	NCP_ST_RIF_INVALID_RFP_OUTPUT_MODE	= 5458,
	/*! Invalid CAR PLL Type */
	NCP_ST_RIF_INVALID_CAR_PLL	= 5459,
	/*! Invalid PHY Rate */
	NCP_ST_RIF_INVALID_PHY_RATE	= 5460,
	/*! Invalid SERDES Primary Clock Input */
	NCP_ST_RIF_INVALID_SERDES_PRIMARY_CLOCK_INPUT	= 5461,
	/*! Invalid SERDES VCO Frequency */
	NCP_ST_RIF_INVALID_SERDES_VCO_FREQ	= 5462,
	/*! Invalid SERDES MPLL Word Clock Frequency */
	NCP_ST_RIF_INVALID_SERDES_MPLL_WORD_CLK_FREQ	= 5463,
	/*! Invalid SERDES VCO Rx Frequency */
	NCP_ST_RIF_INVALID_SERDES_VCO_RX_FREQ	= 5464,
	/*! Invalid SERDES MPLL Selection */
	NCP_ST_RIF_INVALID_SERDES_MPLL_SELECTOR	= 5465,
	/*! Invalid SERDES MPLL SSC Range */
	NCP_ST_RIF_INVALID_SERDES_MPLL_SSC_RANGE	= 5466,
	/*! Invalid SERDES MPLL Div Multiplier */
	NCP_ST_RIF_INVALID_SERDES_MPLL_DIV_MULT	= 5467,
	/*! Invalid SERDES MPLL SSC Clock Select */
	NCP_ST_RIF_INVALID_SERDES_MPLL_SSC_CLK	= 5468,
	/*! Invalid SERDES MPLL Fraction Control */
	NCP_ST_RIF_INVALID_SERDES_MPLL_FRACTION_CONTROL	= 5469,
	/*! Invalid SERDES Tx Baud Rate */
	NCP_ST_RIF_INVALID_SERDES_TX_BAUD_RATE	= 5470,
	/*! Invalid SERDES Rx Baud Rate */
	NCP_ST_RIF_INVALID_SERDES_RX_BAUD_RATE	= 5471,
	/*! Invalid SERDES Tx Clock Frequency */
	NCP_ST_RIF_INVALID_SERDES_TX_CLOCK_FREQ	= 5472,
	/*! Invalid SERDES Rx Clock Frequency */
	NCP_ST_RIF_INVALID_SERDES_RX_CLOCK_FREQ	= 5473,
	/*! Invalid SERDES Tx Word Clock Frequency */
	NCP_ST_RIF_INVALID_SERDES_TX_WORD_CLOCK_FREQ	= 5474,
	/*! Invalid SERDES MPLL Tx Clock Source Selection */
	NCP_ST_RIF_INVALID_SERDES_MPLL_TX_CLK_SRC	= 5475,
	/*! Invalid SERDES Rx Data Width */
	NCP_ST_RIF_INVALID_SERDES_RX_DATA_WIDTH	= 5476,
	/*! Invalid SERDES Rx LOS Threshold */
	NCP_ST_RIF_INVALID_SERDES_RX_LOS_THRESH	= 5477,
	/*! Invalid SERDES Attenuator Setting */
	NCP_ST_RIF_INVALID_SERDES_ATT_SETTING	= 5478,
	/*! Invalid SERDES DFE Tap1 Setting */
	NCP_ST_RIF_INVALID_SERDES_DFE_TAP1_SETTING	= 5479,
	/*! Invalid SERDES Tx Data Width */
	NCP_ST_RIF_INVALID_SERDES_TX_DATA_WIDTH	= 5480,
	/*! Invalid SERDES Equalizer Pre-Emphasis setting */
	NCP_ST_RIF_INVALID_SERDES_EQ_PRE_EMP	= 5481,
	/*! Invalid SERDES Equalizer Post-Emphasis setting */
	NCP_ST_RIF_INVALID_SERDES_EQ_POST_EMP	= 5482,
	/*! Invalid SERDES Equalizer Main setting */
	NCP_ST_RIF_INVALID_SERDES_EQ_MAIN	= 5483,
	/*! Sub-buffer size and number of buffers provided 
	  don't satisfy 16K boundary crossing requirement */
	NCP_ST_RIF_STREAM_PTR_MODE_BUFFER_BOUNDARY_ERR= 5484,

	/*! Sub-buffer size address and the axi burst length 
	  don't satisfy 4K boundary crossing requirement */
	NCP_ST_RIF_STREAM_BUFFER_BOUNDARY_ERR= 5485,

	/*! Bufferaddress does not align to 4 or 16B as required. */
	NCP_ST_RIF_STREAM_BUFFADDR_ALIGN_ERROR = 5486,

	/*! Invalid AxC Container type */
	NCP_ST_RIF_INVALID_AXC_CTR_TYPE	= 5487,
	/*! Invalid AxC Container Id */
	NCP_ST_RIF_INVALID_AXC_ID	= 5488,
	/*! Invalid AxC Type */
	NCP_ST_RIF_INVALID_AXC_TYPE	= 5489,
	/*! Invalid AxC sub Type */
	NCP_ST_RIF_INVALID_AXC_SUBTYPE	= 5490,
	/*! Invalid AxC channel BW */
	NCP_ST_RIF_INVALID_AXC_CHANNEL_BW	= 5491,
	/*! Invalid AxC Start Byte */
	NCP_ST_RIF_INVALID_AXC_STARTBYTE	= 5492,
	/*! Invalid AxC Start Bit */
	NCP_ST_RIF_INVALID_AXC_STARTBIT	= 5493,
	/*! Invalid AxC Bit Width */
	NCP_ST_RIF_INVALID_AXC_BITWIDTH	= 5494,
	/*! Invalid AxC Map Lane Id */
	NCP_ST_RIF_INVALID_AXC_MAPLANEID	= 5495,
	/*! Link is not configured */
	NCP_ST_RIF_LINK_NOT_CONFIGURED	= 5496,
	/*! AxC is not configured */
	NCP_ST_RIF_AXC_NOT_CONFIGURED	= 5497,
	/*! AxC is already configured */
	NCP_ST_RIF_AXC_IS_CONFIGURED	= 5498,
	/*! AxC is enabled */
	NCP_ST_RIF_AXC_IS_ENABLED	= 5499,
	/*! Invalid Timing Sync Rx buffer init delay */
	NCP_ST_RIF_INVALID_SYNC_INIT_DELAY	= 5500,
	/*! Invalid Timing Sync RFP delay */
	NCP_ST_RIF_INVALID_SYNC_RFP_DELAY	= 5501,
	/*! Invalid Timing Sync RFP Terminal count */
	NCP_ST_RIF_INVALID_SYNC_RFP_TERM_COUNT	= 5502,
	/*! AxC is already used by another stream.*/
	NCP_ST_RIF_STREAM_MAP_AXC_ALREADY_USED = 5503,
	/*! AxC is mapped to stream.*/
	NCP_ST_RIF_AXC_IS_MAPPED_TO_STREAM = 5504,
	/*! Link is already configured */
	NCP_ST_RIF_LINK_IS_CONFIGURED	= 5505,
	/*! Link configured for Basic Mapping requires use of similar channel rate containers */
	NCP_ST_RIF_LINK_BASIC_MAP_REQ_SAME_AXC_RATES	= 5506,
	/*! Spec Maximum number of AxC's reached for LTE_1_4 channel bandwidth */
	NCP_ST_RIF_LINK_MAX_NUM_AXC_LTE_1_4_REACHED	= 5507,
	/*! Spec Maximum number of AxC's reached for LTE_3 channel bandwidth */
	NCP_ST_RIF_LINK_MAX_NUM_AXC_LTE_3_REACHED	= 5508,
	/*! Spec Maximum number of AxC's reached for LTE_5 channel bandwidth */
	NCP_ST_RIF_LINK_MAX_NUM_AXC_LTE_5_REACHED	= 5509,
	/*! Spec Maximum number of AxC's reached for LTE_10 channel bandwidth */
	NCP_ST_RIF_LINK_MAX_NUM_AXC_LTE_10_REACHED	= 5510,
	/*! Spec Maximum number of AxC's reached for LTE_15 channel bandwidth */
	NCP_ST_RIF_LINK_MAX_NUM_AXC_LTE_15_REACHED	= 5511,
	/*! Spec Maximum number of AxC's reached for LTE_20 channel bandwidth */
	NCP_ST_RIF_LINK_MAX_NUM_AXC_LTE_20_REACHED	= 5512,
	/*! RIF wise all uplink AxC's maximum capacity reached */
	NCP_ST_RIF_ALL_UPLINKS_MAX_AXC_CAPACITY_REACHED	= 5513,
	/*! RIF wise all downlink AxC's maximum capacity reached */
	NCP_ST_RIF_ALL_DOWNLINKS_MAX_AXC_CAPACITY_REACHED	= 5514,
	/*! Invalid Sample and Hold Interface Select for measurements */
	NCP_ST_RIF_INVALID_SH_CPRI_IF_SELECT	= 5515,
	/*! Invalid Sample and Hold Map Interface Lane identifier for measurements */
	NCP_ST_RIF_INVALID_SH_MAP_LANE_ID	= 5516,
	/*! Invalid Ethernet C & M channel control word in Z.194.0 per CPRI Spec v4.2 */
	NCP_ST_RIF_INVALID_CM_ETH_CONTROL_WORD	= 5517,
	/*! Invalid HDLC C & M Rate */
	NCP_ST_RIF_INVALID_CM_HDLC_RATE	= 5518,
	/*! Invalid HDLC C & M Idle Flag */
	NCP_ST_RIF_INVALID_CM_HDLC_IDLE_FLAG	= 5519,
	/*! Invalid AxC Control Type */
	NCP_ST_RIF_INVALID_AXC_CM_TYPE	= 5520,
	/*! Invalid C & M Ethernet Multicast Address for Hash based filtering */
	NCP_ST_RIF_INVALID_CM_ETH_MCAST_ADDR	= 5521,

	/*! In freerun mode, align offset enable is not allowed. */
	NCP_ST_RIF_STREAM_FREERUN_MODE_ALIGN_OFFSET_EN_INVALID = 5522,
	/*! RIF programmable base, bufferlength array entry is less than the bufferlength. */
	NCP_ST_RIF_STREAM_PROG_BASE_BUFFSIZE_EXCEED = 5523,
	/*! RIF programmable base, bufferlength array entry is less than the bufferlength. */
	NCP_ST_RIF_STREAM_PROG_BASE_BUFFSIZE_INVALID = 5524,

	/*! invalid multi stream mode */
	NCP_ST_RIF_INVALID_MULTI_STREAM_MODE = 5525,

	/*! multi stream mode, secondary streams can't have separate AxC */
	NCP_ST_RIF_MULTI_STREAM_MODE_SECONDARY_AXC_MAP_INVALID = 5526,

	/*! stream is already part of multistream, can't have multistream set. */
	NCP_ST_RIF_STREAM_ALREADY_PART_OF_MULTI_STREAM = 5527,

	/*! the secondary stream has multi stream enabled */
	NCP_ST_RIF_MULTI_STREAM_CANT_HAVE_NESTED	= 5528,

	/*! all streams in multi-stream mode dont have same aignLength */
	NCP_ST_RIF_MULTI_STREAM_ALIGN_LENGTH_MISMATCH = 5529,
	/*! Attempt to change dis-allowed AxC attribute */
	NCP_ST_RIF_INVALID_AXC_ATTRIB_CHANGE = 5530,
	/*! Invalid Serdes termination control setting */
	NCP_ST_RIF_INVALID_SERDES_TERM_CTRL_SETTING = 5531,
	/*! Invalid Voltage Gain Amplifier 1 setting */
	NCP_ST_RIF_INVALID_SERDES_VOLTAGE_GAIN_AMP_1 = 5532,
	/*! Invalid Voltage Gain Amplifier 2 setting */
	NCP_ST_RIF_INVALID_SERDES_VOLTAGE_GAIN_AMP_2 = 5533,

	/*! When stream maps Axc-Ctrl, autolength option is not valid */
	NCP_ST_RIF_STREAM_AXC_CTRL_AUTO_LEN_INVALID = 5534,


	/*! SW_trigger mode invalid threshold selector */
	NCP_ST_RIF_SW_TRIG_INVALID_THRESH_SEL	= 5535,

	/*! SW_trigger mode invalid watermark */
	NCP_ST_RIF_SW_TRIG_INVALID_WATERMARK = 5536,

	/*! SW_trigger mode invalid depth. */
	NCP_ST_RIF_SW_TRIG_INVALID_LARGE_QUEUE_FIFO_DEPTH= 5537,

	/*! SW_trigger mode large Queue count exceeded max 32. */
	NCP_ST_RIF_SW_TRIG_LARGE_QUEUE_FIFO_STREAM_CNT_EXCEED = 5538,

	/*! Invalid CAR clock source select */
	NCP_ST_RIF_INVALID_CAR_SOURCE_SELECT = 5539,
	/*! Invalid CAR divider */
	NCP_ST_RIF_INVALID_CAR_DIVIDER = 5540,
	/*! For VSB Support atleast one modulo rule must be enabled */
	NCP_ST_RIF_VSB_ENABLE_ATLEAST_ONE_MODULO_RULE = 5541,
	/*! Invalid VSB Word Mode specification */
	NCP_ST_RIF_INVALID_AXC_VSB_WORD_MODE = 5542,
	/*! Invalid VSB Modulo Rule Index */
	NCP_ST_RIF_INVALID_AXC_VSB_MODULO_RULE_INDEX = 5543,
	/*! Invalid CPRI Frame Format Xs Index */
	NCP_ST_RIF_INVALID_AXC_VSB_Xs = 5544,
	/*! Invalid CPRI Frame Format Ns Sub-Channel Index */
	NCP_ST_RIF_INVALID_AXC_VSB_Ns = 5545,
	/*! VSB Support not enabled */
	NCP_ST_RIF_VSB_SIGNALLING_NOT_ENABLED = 5546,
	/*! Insufficient number of word modules available to support intended VSB region */
	NCP_ST_RIF_VSB_INSUFFICIENT_WORD_MODULES_AVAILABLE = 5547,
	/*! Invalid VSB AxC due to overlap with exisiting VSB region */
	NCP_ST_RIF_VSB_INVALID_DUE_TO_REGION_OVERLAP = 5548,

	/*! Align Offset enable not valid for VSB.*/
	NCP_ST_RIF_STREAM_VSB_ALIGN_OFFSET_EN_INVALID = 5549,

	/*! Stream buffer set not allowed for fixed base mode */
	NCP_ST_RIF_STREAM_BUFF_SET_NOT_ALLOWED_BUFFMODE= 5550,

	/*! Stream buffer set allowed only for secondary */
	NCP_ST_RIF_STREAM_BUFF_SET_NOT_SECONDARY = 5551,
	/*! Invalid VSB byte in CPRI Z.<>.0 Format */
	NCP_ST_RIF_INVALID_AXC_VSB_BYTE = 5552,
	/*! AxC enabled flag is set to FALSE */
	NCP_ST_RIF_AXC_ENABLED_FLAG_IS_DISABLED = 5553,
	/*! CPRI 4.2 Y value not inline with link rate selected */
	NCP_ST_RIF_INVALID_Y_SELECT = 5554,

	/*! Invalid sub buffer number */
	NCP_ST_RIF_STREAM_INVALID_SUB_BUFF_NUM = 5555,

	/* ESHIM Status Codes */
	/*! Min BIP Packet size is not 8 or 12. */
	NCP_ST_ESHIM_INVALID_MIN_BIP_PKT_SIZE        = 5800,
	/*! Min BIP Packet size is not 8 or 12. */
	NCP_ST_ESHIM_NUM_DEFRAG_POLICY_ENTRIES_MISMATCH = 5801,



	/* ERIF Status codes */
	/*! The ERIF handle contained in the ncp handle provided is not valid. */
	NCP_ST_ERIF_HANDLE_INVALID              = 5900,
	/*! Invalid ERIF Module Id */
	NCP_ST_ERIF_INVALID_MOD_ID              = 5901,
	/*! Initialization of the ERIF state protection semaphore failed. */
	NCP_ST_ERIF_SEM_INIT_ERROR              = 5902,
	/*! ERIF param passed is NULL. */
	NCP_ST_ERIF_INVALID_BUFFER              = 5903,
	/*! ERIF direction passed is out of range. */
	NCP_ST_ERIF_INVALID_DIRECTION           = 5904,
	/*! BIP type is not in range. Valid range 0-7. */
	NCP_ST_ERIF_INVALID_BIP_TYPE            = 5905,
	/*! BIP id is not in range. Valid range 0-0Xfff. */
	NCP_ST_ERIF_INVALID_BIP_ID              = 5906,
	/*! Invalid map type. */
	NCP_ST_ERIF_INVALID_MAP_TYPE            = 5907,
	/*! BIP type/id is already defined. */
	NCP_ST_ERIF_BIP_TYPE_ID_ALREADY_DEFINED = 5908,
	/*! BIP type/id is not defined. */
	NCP_ST_ERIF_BIP_TYPE_ID_NOT_DEFINED     = 5909,
	/*! Invalid ERIF stream ID */
	NCP_ST_ERIF_INVALID_STREAM_ID           = 5910,
	/*! Invalid ERIF link type */
	NCP_ST_ERIF_INVALID_LINK_TYPE           = 5911,
	/*! Invalid ERIF payload format */
	NCP_ST_ERIF_INVALID_PAYLOAD_FORMAT      = 5912,
	/*! Invalid ERIF buffer mode */
	NCP_ST_ERIF_INVALID_BUFFER_MODE         = 5913,
	/*! Invalid ERIF number of buffers */
	NCP_ST_ERIF_INVALID_NUM_BUFFERS         = 5914,
	/*! Invalid ERIF buffer length */
	NCP_ST_ERIF_INVALID_BUFFER_LEN          = 5915,
	/*! Invalid ERIF sub buffer length */
	NCP_ST_ERIF_INVALID_SUB_BUFFER_LEN      = 5916,
	/*! Invalid ERIF bitmap select */
	NCP_ST_ERIF_INVALID_BITMAP_SELECT       = 5917,
	/*! Invalid ERIF payload concat mode */
	NCP_ST_ERIF_INVALID_PAYLOAD_CONCAT_MODE = 5918,
	/*! Invalid ERIF data validation mode */
	NCP_ST_ERIF_INVALID_DATA_VALIDATION_MODE = 5919,
	/*! Invalid ERIF correction mode */
	NCP_ST_ERIF_INVALID_CORRECTION_MODE     = 5920,
	/*! Invalid ERIF enqueue data format mode */
	NCP_ST_ERIF_INVALID_ENQUEUE_DATA_FORMAT_MODE = 5921,
	/*! Invalid ERIF processing type */
	NCP_ST_ERIF_INVALID_PROCESSING_TYPE     = 5922,
	/*! Invalid ERIF frame type */
	NCP_ST_ERIF_INVALID_FRAME_TYPE          = 5923,
	/*! Invalid ethernet header size. Valid values: 0x0E, 0x12, 0x16, 0x1A, 0x1E. */
	NCP_ST_ERIF_INVALID_ETH_HDR_SIZE        = 5924,
	/*! ERIF stream exists */
	NCP_ST_ERIF_STREAM_EXISTS               = 5925,
	/*! ERIF stream does not exist */
	NCP_ST_ERIF_STREAM_DOES_NOT_EXIST       = 5926,
	/*! ERIF stream is currently enabled */
	NCP_ST_ERIF_STREAM_ENABLED              = 5927,
	/*! ERIF stream is currently disabled */
	NCP_ST_ERIF_STREAM_DISABLED             = 5928,
	/*! ERIF feature not supported. */
	NCP_ST_ERIF_FEATURE_NOT_SUPPORTED       = 5929,
	/*! Invalid number of unit bits. Valid range: 6-20. */
	NCP_ST_ERIF_INVALID_NUM_UNIT_BITS       = 5930,
	/*! Invalid number of sunit bits. Valid range: 8-22. */
	NCP_ST_ERIF_INVALID_NUM_SUNIT_BITS      = 5931,
	/*! Invalid number of unit/sunit bits. unit + sunit bits != 28. */
	NCP_ST_ERIF_INVALID_NUM_UNIT_SUNIT_BITS = 5932,
	/*! ERIF Virtual buffer frame TTI select is invalid. */
	NCP_ST_ERIF_INVALID_VIRTUAL_BUF_FRAME_TTI_SELECT = 5933,
	/*! ERIF Vitual buffer length is invalid. */
	NCP_ST_ERIF_INVALID_VIRTUAL_BUF_LEN     = 5934,
	/*! ERIF Symbol timing reference index is invalid. */
	NCP_ST_ERIF_INVALID_SYMBOL_TIMING_REF_INDEX = 5935,
	/*! ERIF BIP sub buffer max range is invalid. */
	NCP_ST_ERIF_INVALID_BIP_SB_MAX_RANGE    = 5936,
	/*! ERIF frame initial value is invalid. */
	NCP_ST_ERIF_INVALID_FRAME_INITIAL_VALUE = 5937,
	/*! ERIF TTI initial value is invalid. */
	NCP_ST_ERIF_INVALID_TTI_INITIAL_VALUE   = 5938,
	/*! ERIF frame match value is invalid. */
	NCP_ST_ERIF_INVALID_FRAME_MATCH_VALUE   = 5939,
	/*! ERIF TTI match value is invalid. */
	NCP_ST_ERIF_INVALID_TTI_MATCH_VALUE     = 5940,
	/*! ERIF free match value is invalid. */
	NCP_ST_ERIF_INVALID_FREE_MATCH_VALUE    = 5941,
	/*! ERIF FRAME/TTI value is invalid. */
	NCP_ST_ERIF_INVALID_FRAME_TTI_VALUE     = 5942,
	/*! ERIF FRAME/TTI generation mode is invalid. */
	NCP_ST_ERIF_INVALID_FRAME_TTI_GENERATION_MODE  = 5943,
	/*! ERIF HW sequencer index is invalid. */
	NCP_ST_ERIF_INVALID_HW_SEQUENCER_INDEX  = 5944,
	/*! ERIF Initial BIP offset is invalid. */
	NCP_ST_ERIF_INVALID_BIP_OFFSET          = 5945,
	/*! ERIF system memory base address offset is invalid. */
	NCP_ST_ERIF_INVALID_BASE_ADDR_OFFSET    = 5946,
	/*! ERIF sub buffer number wrap is invalid. */
	NCP_ST_ERIF_INVALID_SB_NUM_WRAP         = 5947,

	/*! Coulf not enable PMU_USE_MODE */
	NCP_ST_PMU_USER_ENABLE_ERR              =6000,

	/* MUST BE LAST. DO NOT REMOVE! */
	NCP_ST_LAST_STATUS_CODE                      = 65535
} ncp_st_t;

/*
 * enumerated type for the four 'standard' topologies
 * the values are assigned as a bit mask of which ranks
 * (chip selects) exist.
 */
typedef enum {
	NCP_SM_TOPO_ONE_SINGLE_RANK = 0x1,
	NCP_SM_TOPO_ONE_DUAL_RANK   = 0x3,
	NCP_SM_TOPO_TWO_SINGLE_RANK = 0x5,
	NCP_SM_TOPO_TWO_DUAL_RANK   = 0xf
} ncp_sm_topology_t;

typedef enum {
	/*
	  NCP_SM_SDRAM_DENSITY_256MBIT  = 0,
	*/
	NCP_SM_SDRAM_DENSITY_512MBIT  = 1,
	NCP_SM_SDRAM_DENSITY_1GBIT    = 2,
	NCP_SM_SDRAM_DENSITY_2GBIT    = 3,
	NCP_SM_SDRAM_DENSITY_4GBIT    = 4,
	NCP_SM_SDRAM_DENSITY_8GBIT    = 5,
	NCP_SM_SDRAM_DENSITY_16GBIT   = 6
} ncp_sm_sdram_density_t;

typedef enum {
	NCP_SM_SDRAM_WIDTH_4BITS  = 0,
	NCP_SM_SDRAM_WIDTH_8BITS  = 1,
	NCP_SM_SDRAM_WIDTH_16BITS = 2,
	NCP_SM_SDRAM_WIDTH_32BITS = 3
} ncp_sm_sdram_width_t;

typedef enum {
	NCP_SM_PRIMARY_BUS_WIDTH_8BITS  = 0,
	NCP_SM_PRIMARY_BUS_WIDTH_16BITS = 1,
	NCP_SM_PRIMARY_BUS_WIDTH_32BITS = 2,
	NCP_SM_PRIMARY_BUS_WIDTH_64BITS = 3
} ncp_sm_primary_bus_width_t;

typedef struct __attribute__((packed)) {
	unsigned char sdram_rtt_nom[4];
	unsigned char sdram_rtt_wr[4];
	unsigned char sdram_data_drv_imp[4];
	unsigned long phy_min_cal_delay;
	unsigned long phy_adr_phase_select;
	unsigned long phy_dp_io_vref_set;
	unsigned long phy_adr_io_vref_set;
	unsigned long phy_rdlvl_cmp_even;
	unsigned long phy_rdlvl_cmp_odd;
	unsigned long phy_write_align_finetune;
} ncp_per_sysmem_parms_t;

typedef enum {
	NCP_SM_DDR3_MODE = 6,
	NCP_SM_DDR4_MODE = 10
} ncp_dram_class_t;

typedef enum {
	NCP_SM_REFRESH_MODE_1X = 0,
	NCP_SM_REFRESH_MODE_2X = 1,
	NCP_SM_REFRESH_MODE_4X = 2
} ncp_refresh_mode_t;

extern ncp_uint32_t sm_nodes[];

#ifdef CONFIG_AXXIA_ARM

typedef struct {
	unsigned version;
	unsigned flags;
	unsigned baud_rate;
	unsigned memory_ranges[16];
	unsigned sequence;
	char description[128];
} __attribute__((packed)) parameters_global_t;

#else  /* CONFIG_AXXIA_ARM */

typedef struct {
	unsigned version;
	unsigned flags;
} __attribute__((packed)) parameters_global_t;

#endif	/* CONFIG_AXXIA_ARM */

#ifdef CONFIG_AXXIA_ARM
typedef struct {
	unsigned version;
	unsigned char offsets[128];
} __attribute__((packed)) parameters_voltage_t;
#else
typedef struct {
	unsigned checksum;
	unsigned version;
	unsigned vofs;
	unsigned tvid;
	unsigned long long twait;
	unsigned VIDChecks;
	unsigned char vidLT[64];
} __attribute__((packed)) parameters_voltage_t;
#endif

#ifdef CONFIG_AXXIA_ARM
typedef struct {
	unsigned version;
	unsigned flags;
	unsigned syspll_prms;
	unsigned syspll_ctrl;
	unsigned syspll_csw;
	unsigned syspll_div;
	unsigned syspll_psd;
	unsigned cpupll_prms;
	unsigned cpupll_ctrl;
	unsigned cpupll_csw;
	unsigned cpupll_div;
	unsigned cpupll_psd;
	unsigned sm0pll_prms;
	unsigned sm0pll_ctrl;
	unsigned sm0pll_csw;
	unsigned sm0pll_div;
	unsigned sm0pll_psd;
	unsigned sm1pll_prms;
	unsigned sm1pll_ctrl;
	unsigned sm1pll_csw;
	unsigned sm1pll_div;
	unsigned sm1pll_psd;
	unsigned tmpll_prms;
	unsigned tmpll_ctrl;
	unsigned tmpll_csw;
	unsigned tmpll_div;
	unsigned tmpll_psd;
	unsigned fabpll_prms;
	unsigned fabpll_ctrl;
	unsigned fabpll_csw;
	unsigned fabpll_div;
	unsigned fabpll_psd;
	unsigned nrcpinput_csw;
	unsigned nrcpinput_div;
	unsigned per_csw;
	unsigned per_div;
	unsigned emmc_csw;
	unsigned emmc_div;
	unsigned debug_csw;
	unsigned stop_csw;
} __attribute__ ((packed)) parameters_clocks_t;
#else  /* CONFIG_AXXIA_ARM */
typedef struct {
#ifdef CONFIG_AXXIA_25xx
	unsigned syspll_prms;
	unsigned syspll_ctrl;
	unsigned syspll_mcgc;
	unsigned syspll_mcgc1;
	unsigned syspll_psd;
	unsigned ppcpll_prms;
	unsigned ppcpll_ctrl;
	unsigned ppcpll_mcgc;
	unsigned ppcpll_mcgc1;
	unsigned ppcpll_psd;
	unsigned smpll_prms;
	unsigned smpll_ctrl;
	unsigned smpll_mcgc;
	unsigned smpll_mcgc1;
	unsigned smpll_psd;
	unsigned tmpll_prms;
	unsigned tmpll_ctrl;
	unsigned tmpll_mcgc;
	unsigned tmpll_mcgc1;
	unsigned tmpll_psd;
	unsigned per_mcgc;
	unsigned per_mcgc1;
#else
	unsigned sys_control;
	unsigned sys_lftune_upper;
	unsigned sys_lftune_lower;
	unsigned sys_fftune;
	unsigned sys_locktune;
	unsigned ppc_control;
	unsigned ppc_lftune_upper;
	unsigned ppc_lftune_lower;
	unsigned ppc_fftune;
	unsigned ppc_locktune;
	unsigned ddr0_control;
	unsigned ddr1_control;
	unsigned ddr_lftune_upper;
	unsigned ddr_lftune_lower;
	unsigned ddr_fftune;
	unsigned ddr_locktune;
#endif
} __attribute__ ((packed)) parameters_clocks_t;

#endif	/* CONFIG_AXXIA_ARM */

typedef struct {
	unsigned version;
	unsigned control;
} __attribute__((packed)) parameters_pciesrio_t;

typedef unsigned ncp_uint32_t;
typedef void *   ncp_dev_hdl_t;
typedef unsigned ncp_region_id_t;

typedef struct {
	unsigned char sdram_rtt_nom[4];
	unsigned char sdram_rtt_wr[4];
	unsigned char sdram_data_drv_imp[4];
	unsigned phy_min_cal_delay;
	unsigned phy_adr_phase_select;
	unsigned phy_dp_io_vref_set;
	unsigned phy_adr_io_vref_set;
	unsigned phy_rdlvl_cmp_even;
	unsigned phy_rdlvl_cmp_odd;
	unsigned phy_write_align_finetune;
} __attribute__((packed)) per_sysmem_parms_t;

typedef struct {
	unsigned char sdram_rtt_nom[4];
	unsigned char sdram_rtt_wr[4];
	unsigned char sdram_data_drv_imp[4];
} __attribute__((packed)) per_sysmem_sdram_parms_t;

typedef struct {
	ncp_uint32_t version;
	ncp_uint32_t ddrClockSpeedMHz;
	ncp_uint32_t autoDetect;
	ncp_uint32_t numInterfaces;
	ncp_uint32_t numRanks;
	ncp_uint32_t primary_bus_width;
	ncp_uint32_t topology;
	ncp_uint32_t minCtrlRoundtripDelay;
	ncp_uint32_t phy_rdlat;
	ncp_uint32_t addedRankSwitchDly;
	ncp_uint32_t zqcs_interval;
	ncp_uint32_t enableECC;
	ncp_uint32_t enableRuntime;
	ncp_uint32_t dramPrechargePolicy;
	ncp_uint32_t open_page_size;
	ncp_uint32_t syscacheControl;
	ncp_uint32_t sdram_device_density;
	ncp_uint32_t sdram_device_width;
	ncp_uint32_t CAS_latency;
	ncp_uint32_t CAS_write_latency;
	ncp_uint32_t address_mirroring;
	ncp_uint32_t registeredDimm;
	ncp_uint32_t rdimmCtl_0;
	ncp_uint32_t rdimmCtl_1;
	ncp_uint32_t rdimm_misc;
	ncp_uint32_t write_ODT_ctl;
	ncp_uint32_t read_ODT_ctl;
	ncp_uint32_t singleBitMPR;
	ncp_uint32_t high_temp_dram;
	per_sysmem_parms_t per_sysmem[2];
	ncp_uint32_t dram_class;
	per_sysmem_sdram_parms_t per_smem[4];
	ncp_uint32_t additive_latency;
	ncp_uint32_t binned_CAS_latency;
	ncp_uint32_t tck_ps;
	ncp_uint32_t refresh_mode;
	ncp_uint32_t address_inversion;
	ncp_uint32_t bstlen;
	ncp_uint32_t dm_masking;
	ncp_uint32_t rdimm_ctl_0_0;
	ncp_uint32_t rdimm_ctl_0_1;
	ncp_uint32_t rdimm_ctl_0_2;
	ncp_uint32_t rdimm_ctl_0_3;
	ncp_uint32_t rdimm_ctl_0_4;
	ncp_uint32_t rdimm_ctl_1_0;
	ncp_uint32_t rdimm_ctl_1_1;
	ncp_uint32_t rdimm_ctl_1_2;
	ncp_uint32_t rdimm_ctl_1_3;
	ncp_uint32_t rdimm_ctl_1_4;
	ncp_uint32_t vref_en;
	ncp_uint32_t vref_cs;
	ncp_uint32_t vref_val;
	ncp_uint32_t wr_protect_en_mask;
	ncp_uint32_t rdlvl_en;
	ncp_uint32_t dbi_rd_en;
	ncp_uint32_t dbi_wr_en;
	ncp_uint32_t ca_parity_en;  
	ncp_uint32_t rdlvl_gate_en;
	ncp_uint32_t rdlvl_interval;	
	ncp_uint32_t rdlvl_gate_interval;
	ncp_uint32_t preamble_support;
	ncp_uint32_t crc_mode;
	unsigned char dq_map_0[18];
 	unsigned char unused_0[2];
	unsigned char dq_map_1[18];
 	unsigned char unused_1[2];
	ncp_uint32_t dq_map_odd_rank_swap_0; 
	ncp_uint32_t dq_map_odd_rank_swap_1; 
	unsigned ddrRetentionEnable;
	unsigned ddrRecovery;
	unsigned long long totalSize;
} __attribute__((packed)) parameters_mem_t;

typedef parameters_mem_t ncp_sm_parms_t;

#ifdef CONFIG_AXXIA_ARM
typedef struct {
	unsigned magic;
	unsigned size;
	unsigned checksum;
	unsigned version;
	unsigned chipType;
	unsigned globalOffset;
	unsigned globalSize;
	unsigned pciesrioOffset;
	unsigned pciesrioSize;
	unsigned voltageOffset;
	unsigned voltageSize;
	unsigned clocksOffset;
	unsigned clocksSize;
	unsigned systemMemoryOffset;
	unsigned systemMemorySize;
	unsigned classifierMemoryOffset;
	unsigned classifierMemorySize;
	unsigned systemMemoryRetentionOffset;
	unsigned systemMemoryRetentionSize;
} __attribute__((packed)) parameters_header_t;
#else  /* CONFIG_AXXIA_ARM */
typedef struct {
	unsigned sysmemSize;
	unsigned sysmemOffset;
	unsigned clocksSize;
	unsigned clocksOffset;
	unsigned voltageSize;
	unsigned voltageOffset;
	unsigned pciesrioSize;
	unsigned pciesrioOffset;
	unsigned globalSize;
	unsigned globalOffset;
	unsigned version;
	unsigned checksum;
	unsigned size;
	unsigned magic;
} __attribute__((packed)) parameters_header_t;
#endif	/* CONFIG_AXXIA_ARM */

typedef struct {
	parameters_header_t *header;
	parameters_global_t *global;
	parameters_voltage_t *voltage;
	parameters_clocks_t *clocks;
	parameters_pciesrio_t *pciesrio;
	parameters_mem_t *sysmem;
	parameters_mem_t *cmem;
} parameters_t;

extern parameters_header_t *header;
extern parameters_global_t *global;
extern parameters_pciesrio_t *pciesrio;
extern parameters_voltage_t *voltage;
extern parameters_clocks_t *clocks;
extern parameters_mem_t *sysmem;
extern parameters_mem_t *cmem;
#ifdef CONFIG_AXXIA_ARM
extern void *retention;
#endif

int read_parameters(void);
int write_parameters(void);

#ifndef CONFIG_SPL_BUILD
#define CONFIG_CMD_LSI_PARAMETERS
#endif

#endif	/* __ASSEMBLY__ */

/*
  ==============================================================================
  ==============================================================================
  Networking
  ==============================================================================
  ==============================================================================
*/

#ifndef CONFIG_SPL_BUILD

#if defined(CONFIG_AXXIA_FEMAC) || defined(CONFIG_AXXIA_EIOA) || defined(CONFIG_AXXIA_NEMAC)
#define CONFIG_AXXIA_NET
#define CONFIG_AXXIA_MDIO
#define CONFIG_CMD_NET
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_PING
#define CONFIG_CMD_MII
#define CONFIG_PHYLIB
#define CONFIG_MII
#define CONFIG_PHY_BROADCOM
#define CONFIG_PHY_DAVICOM
#define CONFIG_PHY_MICREL
#define CONFIG_PHY_VITESSE
#endif

#ifndef MDIO_CLK_OFFSET_DEFAULT
#ifdef CONFIG_AXXIA_EMU
/*#define MDIO_CLK_OFFSET_DEFAULT 0x10*/
#define MDIO_CLK_OFFSET_DEFAULT 0x5
#else
#define MDIO_CLK_OFFSET_DEFAULT 0x1c
#endif
#endif

#ifndef MDIO_CLK_PERIOD_DEFAULT
#ifdef CONFIG_AXXIA_EMU
/*#define MDIO_CLK_PERIOD_DEFAULT 0x2c*/
#define MDIO_CLK_PERIOD_DEFAULT 0xc
#else
#define MDIO_CLK_PERIOD_DEFAULT 0xf0
#endif
#endif

#endif	/* CONFIG_SPL_BUILD */

/*
  ==============================================================================
  ==============================================================================
  SSP Access
  ==============================================================================
  ==============================================================================
*/

#define SSP_CR0       0x000
#define SSP_CR1       0x004
#define SSP_DR        0x008
#define SSP_SR        0x00c
#define SSP_CPSR      0x010
#define SSP_IMSC      0x014
#define SSP_RIS       0x018
#define SSP_MIS       0x01c
#define SSP_ICR       0x020
#define SSP_DMACR     0x024
#define SSP_CSR       0x030
#define SSP_PERIPHID0 0xfe0
#define SSP_PERIPHID1 0xfe4
#define SSP_PERIPHID2 0xfe8
#define SSP_PERIPHID3 0xfec
#define SSP_PCELLID0  0xff0
#define SSP_PCELLID1  0xff4
#define SSP_PCELLID2  0xff8
#define SSP_PCELLID3  0xffc

#define SSP_MAXIMUM_CLOCK 25000000

#ifndef __ASSEMBLY__
int ssp_read(void *, unsigned, unsigned);
int ssp_set_speed(unsigned *);
int ssp_init(int);
#endif

/*
  ==============================================================================
  ==============================================================================
  Clocks
  ==============================================================================
  ==============================================================================
*/

#ifndef __ASSEMBLY__

#define CLK_REF0 125000000

typedef enum {
	clock_system, clock_core, clock_memory, clock_peripheral,
	clock_fab, clock_treemem, clock_emmc
} acp_clock_t;

int acp_clock_get(acp_clock_t, ncp_uint32_t *);

unsigned int spi_get_per_clk(void);

#endif /* __ASSEMBLY__ */

/*
  ==============================================================================
  ==============================================================================
  System Memory
  ==============================================================================
  ==============================================================================
*/

#ifndef __ASSEMBLY__
int sysmem_reset(void);
unsigned long long sysmem_size(void);
#endif

/*
  ==============================================================================
  ==============================================================================
  Special Test
  ==============================================================================
  ==============================================================================
*/

/**********************************************************************
 * CONFIG_HYBRID_MBIST
 *
 * In order to use the MBIST controller to test a specific CPU linear range
 * of memory, software must understand the address munging algorithm and convert
 * the CPU linear range into multiple DDR physical sub-ranges. And, even after
 * doing this, due to the complicated nature of the munging algorithm and
 * limitations of the MBIST controller hardware, there will be some sub
 * ranges that cannot be tested using the MBIST hardware and therefore would
 * need to be tested via a software based memory test. Hence, we have this
 * hybrid approach for range based memory testing. This approach uses
 * the MBIST hardware in combination with software testing
 * of memory areas that cannot be covered by the MBIST controller. With
 * the hybrid approach, the user can only protect 768M or less of sysmem
 * by specifying the memory ranges on which they want the hybrid tests run.
 * It has been observed that hybrid approach versus s/w based memory testing
 * on the same range is 10-12 times faster.
 * If the user defines CONFIG_HYBRID_MBIST, then the ranges specified in
 * parameter file for memory range testing, will use the hybrid approach and
 * if CONFIG_HYBRID_MBIST is not defined, then s/w based spl_mtest will be
 * used for memory range testing. The user can specific which kind of spl_mtest
 * needs to be run by setting bits in Global Flags
 */
#define CONFIG_HYBRID_MBIST

/* Please note that CONFIG_SPL_MTEST just tests 0-1GB of sysmem */
/*#define CONFIG_SPL_MTEST*/
/*#define SM_PLL_533_MHZ*/
/*#define RUN_UNCACHED*/
/*#define RUN_NONSECURE*/
/*#define SINGLE_SMEM_MODE*/
/*#define DISPLAY_PARAMETERS*/

#define CONFIG_LSI
#define UBOOT

/*
  ==============================================================================
  ==============================================================================
  Version
  ==============================================================================
  ==============================================================================
*/

#ifndef __ASSEMBLY__
const char *get_lsi_version(void);
#endif /* __ASSEMBLY__ */

/*
  ==============================================================================
  ==============================================================================
  Nuevo Conf Ring Access (see board/lsi/common/ncr.c for the implementation)
  ==============================================================================
  ==============================================================================
*/

#ifndef __ASSEMBLY__
#define NCP_REGION_ID( node, target ) \
( ncp_uint32_t ) ( ( ( ( node ) & 0xffff ) << 16 ) | ( ( target ) & 0xffff ) )
#define NCP_NODE_ID( region ) ( ( ( region ) >> 16 ) & 0xffff )
#define NCP_TARGET_ID( region ) ( ( region ) & 0xffff )
int ncr_read(ncp_uint32_t, ncp_uint32_t, ncp_uint32_t, int, void *);
int ncr_read8( ncp_uint32_t, ncp_uint32_t, unsigned char * );
int ncr_read16( ncp_uint32_t, ncp_uint32_t, unsigned short * );
int ncr_read32( ncp_uint32_t, ncp_uint32_t, ncp_uint32_t * );
int ncr_write(ncp_uint32_t, ncp_uint32_t, ncp_uint32_t, int, void *);
int ncr_write8( ncp_uint32_t, ncp_uint32_t, unsigned char );
int ncr_write16( ncp_uint32_t, ncp_uint32_t, unsigned short );
int ncr_write32( ncp_uint32_t, ncp_uint32_t, ncp_uint32_t );
int ncr_modify32( ncp_uint32_t, ncp_uint32_t, ncp_uint32_t, ncp_uint32_t );
int ncr_and( ncp_uint32_t, ncp_uint32_t, ncp_uint32_t );
int ncr_or( ncp_uint32_t, ncp_uint32_t, ncp_uint32_t );
int ncr_poll( ncp_uint32_t, ncp_uint32_t, ncp_uint32_t,
              ncp_uint32_t, ncp_uint32_t, ncp_uint32_t );
void ncr_tracer_enable( void );
void ncr_tracer_disable( void );
int ncr_tracer_is_enabled( void );
void ncr_enable( void );
void ncr_disable( void );
#endif

/*
  ==============================================================================
  ==============================================================================
  Errata
  ==============================================================================
  ==============================================================================
*/

#ifndef __ASSEMBLY__
int setup_security(void);
int voltage_init(void);
#endif

#endif /* __AXXIA_H */
