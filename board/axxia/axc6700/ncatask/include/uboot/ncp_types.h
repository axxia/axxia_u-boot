/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/

/*! @file      ncp_types.h */
/*!
 *  @brief     NCP specific defines and type definitions
 */

#ifndef NCP_TYPES_H
#define NCP_TYPES_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "uboot/ncp_sal_linux-arma53.h"

/**************************************************************************
 * ACP chip types 
 *
 * These are the base silicon chip types. Each chip may have one 
 * or more variants, but for the purpose of the chipType comparison
 * we only care about the base silicon version. For any variant the
 * driver will set the chipType in virtual register 0x301.0.0 to 
 * one of the following.
 **************************************************************************/

#define NCP_CHIP_ACP34xx             1
#define NCP_CHIP_ACP32xx             2
#define NCP_CHIP_ACP25xx             6
#define NCP_CHIP_ACP25xx_V2          7
#define NCP_CHIP_ACP55xx             9       /* AXM55xx, aka X7     */
#define NCP_CHIP_ACP55xxV2_FPGA     10       /* X7v2, FPGA only  */
#define NCP_CHIP_ACP56xx            11       /* AXM56xx, aka X9     */
#define NCP_CHIP_ACP15xx            15       /* AXE15xx, aka X15    */
#define NCP_CHIP_ACP35xx            16       /* AXM35xx, aka X3     */
#define NCP_CHIP_ACPXLF             24       /* XLF */

/***************************************************************************
* Constants                                                                *
***************************************************************************/
/* 
 * maximum number of devices (config instances) that can handled 
 * by a single application instance
 */
/* RWXXX #define NCP_MAX_DEVS 8 */
#define NCP_MAX_DEVS 1

/*
 * number of supported AMP domains
 * These will be numbered as Domains 0 through (NCP_CFG_NUM_DOMAINS-1)
 *
 *
 */
#define NCP_CFG_NUM_DOMAINS   4

/**************************************************************************
 * Debug Definitions
 **************************************************************************/

/*  #define NCP_CONFIG_DEBUG  */


/**************************************************************************
 * Commonly used constants
 **************************************************************************/
#define NCP_CONST_1KB      (1024)
#define NCP_CONST_2KB      (NCP_CONST_1KB * 2)
#define NCP_CONST_4KB      (NCP_CONST_1KB * 4)
#define NCP_CONST_8KB      (NCP_CONST_1KB * 8)
#define NCP_CONST_16KB     (NCP_CONST_1KB * 16)
#define NCP_CONST_32KB     (NCP_CONST_1KB * 32)
#define NCP_CONST_64KB     (NCP_CONST_1KB * 64)
#define NCP_CONST_128KB    (NCP_CONST_1KB * 128)
#define NCP_CONST_256KB    (NCP_CONST_1KB * 256)
#define NCP_CONST_512KB    (NCP_CONST_1KB * 512)
#define NCP_CONST_N_KB(n)  (NCP_CONST_1KB * (n))

#define NCP_CONST_1MB      (NCP_CONST_1KB * 1024)
#define NCP_CONST_2MB      (NCP_CONST_1MB * 2)
#define NCP_CONST_4MB      (NCP_CONST_1MB * 4)
#define NCP_CONST_8MB      (NCP_CONST_1MB * 8)
#define NCP_CONST_16MB     (NCP_CONST_1MB * 16)
#define NCP_CONST_32MB     (NCP_CONST_1MB * 32)
#define NCP_CONST_64MB     (NCP_CONST_1MB * 64)
#define NCP_CONST_128MB    (NCP_CONST_1MB * 128)
#define NCP_CONST_256MB    (NCP_CONST_1MB * 256)
#define NCP_CONST_512MB    (NCP_CONST_1MB * 512)
#define NCP_CONST_N_MB(n)  (NCP_CONST_1MB * (n))

#define NCP_CONST_1GB      (NCP_CONST_1MB * 1024)
#define NCP_CONST_2GB      (NCP_CONST_1GB * 2)
#define NCP_CONST_4GB      (NCP_CONST_1GB * 4ULL)
#define NCP_CONST_8GB      (NCP_CONST_1GB * 8ULL)
#define NCP_CONST_16GB     (NCP_CONST_1GB * 16ULL)
#define NCP_CONST_32GB     (NCP_CONST_1GB * 32ULL)
#define NCP_CONST_64GB     (NCP_CONST_1GB * 64ULL)
#define NCP_CONST_N_GB(n)  (NCP_CONST_1GB * (n))




/**************************************************************************
 * API Configuration Status Codes, Typedefs, etc.
 **************************************************************************/

typedef void*  ncp_hdl_t;
typedef void*  ncp_vp_hdl_t;

    /* Generic byte stream data structure */
/*!
 * @brief   Generic byte stream data structure
 */
typedef struct
{
    char *buf;
    ncp_uint32_t len;
} ncp_byte_string_t;

#define NCP_P2RNDUP(x, y)   (((x) + ((y) - 1)) & ~((y) - 1))


typedef void *ncp_config_t;

typedef int (*ncp_read_fn_t) (
    void *arg,
    void *buf,
    int   len);

typedef int (*ncp_write_fn_t) (
    void *arg,
    void *buf,
    int   len);

typedef struct
{
    int   scriptNo;
    char *scriptBuf;
    int   scriptBufLen;
} ncp_script_t;

/*!
 * @typedef ncp_region_id_t
 * @brief Holds the region id for registers
 * Region id is combination of node.target
 *
 */

typedef ncp_uint32_t ncp_region_id_t; /*!< Region ID - Node.Target */


/*---------------------------------------
 * NCA API Buffer Definitions
 *---------------------------------------
 */
 
 
/*
 * API buffers for read8, read16, read32,   write8,  write16,  and write 32 are simply arrays
 * of the appropriate sized items (eg. ncp_uint8_t *buffer, ?. ).
 */



/*!
 * @brief API buffer format for NCP Fill. 
 * Not used for accessing coherent system memory.
 *
 * the 'width' field only applies to CRBF operations, 
 * and the nvector only applies to CRBBF operations.
 *
 */

typedef struct ncp_fill_s {
    union {
        ncp_uint32_t    width;        /*!< width of fill buffer in # words */
        ncp_uint32_t    nvector;      /*!< broadcast vector (CRBBF only)   */
        ncp_uint32_t    word0;        /*!< opaque reference                */
    } u;
    NCP_DECLARE_POINTER_NOALIGN(ncp_uint32_t, value);  /*!< fill value buffer */
    ncp_uint32_t        count;        /*!< # of fill operations            */
    ncp_uint32_t        stride;       /*!< address increment in # words    */
} __attribute__((packed)) ncp_fill_t;


/*!
 * @brief  data format for ReadModifyWrite 
 */

typedef struct ncp_rmw_pair_s {
    ncp_uint32_t    rmw_mask;         /*!< bit mask for bits to be modified */
    ncp_uint32_t    rmw_data;         /*!< data to be written */
} __attribute__((packed)) ncp_rmw_pair_t;


/*!
 * @brief  API buffer format for NCA ReadModifyWrite commands
 */
typedef struct ncp_rmw_s {
    ncp_uint32_t     count;           /*!< number of rmw operations */
    NCP_DECLARE_POINTER_NOALIGN(ncp_rmw_pair_t, rmw_buffer); /*!< pointer to array of rmw data/mask pairs */
} __attribute__((packed)) ncp_rmw_t;


/*!
 * @brief data format for 32-bit Scatter Write 
 */
typedef struct ncp_swspec_s {
    ncp_uint32_t        addr;         /*!< address offset */
    ncp_uint32_t        data;         /*!< 32-bit data value */
} __attribute__((packed)) ncp_swspec_t;

/*!
 * @brief  API buffer format for NCA ScatterWrite commands
 */
typedef struct ncp_crsw_s {
    ncp_uint32_t        length;       /*!< number of 32-bit words to be written */
    NCP_DECLARE_POINTER_NOALIGN(ncp_swspec_t, swvector);  /*!< pointer to array of broadcast pairs*/
} __attribute__((packed)) ncp_crsw_t;

/*!
 * @brief 64-bit data for NCA CR broadcast class of APIs
 */
typedef struct ncp_bdata_s {
    ncp_uint32_t        h;            /*!< high word */
    ncp_uint32_t        l;            /*!< low word  */
} __attribute__((packed)) ncp_bdata_t;

/*! 
 * @brief Broadcast Scatter Write addr/data pair  
 */
typedef struct ncp_bswspec_s {
    ncp_uint32_t        addr;         /*!< address offset */
    ncp_bdata_t         data;         /*!< 64-bit data value */
} __attribute__((packed)) ncp_bswspec_t;

/*! 
 * @brief API buffer format for Broadcast Scatter Write 
 */

typedef struct ncp_crbsw_s {
    ncp_uint32_t        length;       /*!< number of 64-bit values */
    ncp_uint32_t        nvector;      /*!< broadcast node vector */
    NCP_DECLARE_POINTER_NOALIGN(ncp_bswspec_t, bswvector); /*!< pointer to array of broadcast pairs*/
} __attribute__((packed)) ncp_crbsw_t;

/*! 
 * @brief API buffer format for Broadcast Block Write 
 */

typedef struct ncp_crbbw_s {
    ncp_uint32_t        length;       /*!< number of 64-bit values */
    ncp_uint32_t        nvector;      /*!< broadcast node vector */
    NCP_DECLARE_POINTER_NOALIGN(ncp_bdata_t, data); /*!< pointer to array of 64-bit values */
} __attribute__((packed)) ncp_crbbw_t;


/*
 * Used for both coherent system memory read and write commands
 */
typedef struct {
     ncp_uint32_t  lower_address;
} ncp_atomic_update_control_r0_t;

typedef struct {
#ifdef NCP_BIG_ENDIAN
     unsigned      reserved0                                 :  3;
     unsigned      length2  /* for X7 SPP */                 :  9;
     unsigned      atomic_update_req                         :  1;
     unsigned      reserved1                                 :  1;
     unsigned      atomic_type                               :  2;
     unsigned      length                                    :  8;
     unsigned      wrback                                    :  1;
     unsigned      reserved2                                 :  3;
     unsigned      upper_address                             :  4;
#else    /* Little Endian */
     unsigned      upper_address                             :  4;
     unsigned      reserved2                                 :  3;
     unsigned      wrback                                    :  1;
     unsigned      length                                    :  8;
     unsigned      atomic_type                               :  2;
     unsigned      reserved1                                 :  1;
     unsigned      atomic_update_req                         :  1;
     unsigned      length2  /* for X7 SPP */                 :  9;
     unsigned      reserved0                                 :  3;
#endif
} ncp_atomic_update_control_r1_t; 

/*!
 * @brief the atomic update control registers. These are defined 
 * in the hardware RDL for each engine that supports coherent 
 * memory access 
 */
typedef struct {
     ncp_atomic_update_control_r0_t  control_0;    /* atomic update regs */
     ncp_atomic_update_control_r1_t  control_1;    /* atomic update regs */
} ncp_atomic_update_control_t;

/*!
 * @brief command buffer for coherent sysmem read/write operations
 */
typedef struct {
     ncp_uint32_t    engine_node_target;        /*!< engine for atomic update */
     ncp_uint32_t    engine_addr;               /*!< offset for atomic update regs */
     ncp_atomic_update_control_t  engine_data;  /*!< atomic update regs */
     ncp_uint32_t    count;                     /*!< number of 8-bit vals */
     ncp_uint32_t    pad[3];                    /*!< unused padding words */
     ncp_uint8_t     sysmem_buffer[256];        /*!< array of 8-bit items */
} ncp_coherent_sysmem_io_t;


/* 
 * Macros which define the size of the 'fixed' part of the command buffer.
 * Basically this is just the command structure size minus the size of
 * the pointer to the variable length buffer.
 */
#define NCP_NCA_CMD_CRBF_SIZE  (sizeof(ncp_fill_t) - sizeof(ncp_uint32_t *))
#define NCP_NCA_CMD_CRRMW_SIZE (sizeof(ncp_rmw_t) - sizeof(ncp_rmw_pair_t *))
#define NCP_NCA_CMD_CRSW_SIZE  (sizeof(ncp_crsw_t) - sizeof(ncp_swspec_t *))
#define NCP_NCA_CMD_CRBBW_SIZE (sizeof(ncp_crbbw_t) - sizeof(ncp_bdata_t *)) 
#define NCP_NCA_CMD_CRBSW_SIZE (sizeof(ncp_crbsw_t) - sizeof(ncp_bswspec_t *))

#define FPLC_ACP3400_OBJECT_COOKIE  0x56789ad0

/* macros to convert a 64-bit address to upper and lower 32-bit parts */
#define NCP_ADDR_UPPER(addr) ( (ncp_uint32_t) (addr >> 32) )
#define NCP_ADDR_LOWER(addr) ( (ncp_uint32_t) (addr & 0xFFFFFFFF))

/**************************************************************************
* Function Call Support Typedefs, Constants, Macros, etc.
**************************************************************************/

#ifdef NCP_ERR_DEBUG
#define NCP_PRINT_LINE_FILE \
    do { \
        NCP_TRACEPOINT(Intel_AXXIA_ncp_common, ncp_common_print_line_file,  NCP_MSG_INFO, \
                       "%s : %s, line = %d\n", ncp_status_get(ncpStatus), __FILE__,__LINE__); \
    } while (0)

#ifdef NCP_LTTNG_USERSPACE
#define NCP_PRINT_LINE_FILE_MSG(...)                                       \
    {                                                                           \
        NCP_TRACEPOINT(Intel_AXXIA_ncp_common, ncp_common_print_ln_file_msg,  NCP_MSG_INFO, \
                       " (%s : %s, line = %d)\n", ncp_status_get(ncpStatus), \
                       __FILE__,__LINE__);                                                 \
    }
#else
#define NCP_PRINT_LINE_FILE_MSG(...)                                       \
    {                                                                           \
        NCP_TRACEPOINT(Intel_AXXIA_ncp_common, ncp_common_print_ln_file_msg_va_args,  NCP_MSG_INFO, __VA_ARGS__);                                    \
        NCP_TRACEPOINT(Intel_AXXIA_ncp_common, ncp_common_print_ln_file_msg,  NCP_MSG_INFO, \
                       " (%s : %s, line = %d)\n", ncp_status_get(ncpStatus), \
                       __FILE__,__LINE__);                                                 \
    }
#endif
    
#else                           /* NCP_ERR_DEBUG */
#define NCP_PRINT_LINE_FILE
#define NCP_PRINT_LINE_FILE_MSG(...)
#endif

#define NCP_JUMP_RETURN() \
    do { \
        goto ncp_return; \
    } while (0)


#define NCP_RETURN(f) \
    do { \
        ncpStatus = (f); \
        goto ncp_return; \
    } while (0)

#define NCP_ERR(f) \
    do { \
        ncpStatus = (f); \
            NCP_PRINT_LINE_FILE; \
        goto ncp_return; \
    } while (0)

#define NCP_ARRAY_SIZE(array) (sizeof(array)/sizeof((array)[0]))

#define NCP_ASSERT(condition, err)   \
    if (condition)                   \
    {                                \
    /* intentional - optimization */ \
    }                                \
    else                             \
    {                                \
        ncpStatus = (err);           \
        NCP_PRINT_LINE_FILE;         \
        goto ncp_return;             \
    }

#define NCP_CALL(ncpFunc)                \
    do {                                 \
        ncpStatus = (ncpFunc);           \
        if (NCP_ST_SUCCESS == ncpStatus) \
        {                                \
        /* intentional - optimization */ \
        }                                \
        else                             \
        {                                \
	       /*Coverity[dead_error_line]*/ \
            NCP_PRINT_LINE_FILE;         \
            goto ncp_return;             \
        }                                \
    } while(0)

#define NCP_CLEANUP_CALL( fun) \
	do { \
	    ncp_st_t tStatus = NCP_ST_SUCCESS; \
	    tStatus = (fun); \
	    if( tStatus != NCP_ST_SUCCESS ) { \
	        NCP_PRINT_LINE_FILE; \
	        if( ncpStatus == NCP_ST_SUCCESS ) { \
	            ncpStatus = tStatus; \
	        } \
             } \
	} while(0)

#define NCP_CLEANUP_MUTEX_CALL(fun) \
    do { \
	ncp_st_t tStatus = NCP_ST_SUCCESS; \
	tStatus = (fun); \
	if( tStatus != NCP_ST_SUCCESS ) {\
	    NCP_PRINT_LINE_FILE; \
	    if( ( ncpStatus == NCP_ST_SUCCESS ) || \
		( tStatus == NCP_ST_PTHREAD_MUTEX_OWNER_DEAD )) { \
		ncpStatus = tStatus; \
	    } \
	} \
    } while(0)	    

#define NCP_CALL_MSG(ncpFunc, ...)       \
    do {                                 \
        ncpStatus = (ncpFunc);           \
        if (NCP_ST_SUCCESS == ncpStatus) \
        {                                \
            /* intentional - optimization */ \
        }                                \
        else                             \
        {                                \
            NCP_PRINT_LINE_FILE_MSG(__VA_ARGS__); \
            goto ncp_return;             \
        }                                \
    } while(0)

#define NCP_CALL_GOTO(ncpFunc, g)        \
    do {                                 \
        if ((ncpFunc) != NCP_ST_SUCCESS) \
        {                                \
            goto g;                      \
        }                                \
    } while(0)


/*
 * API parameter checking can be disabled by defining NCP_CHECK_DISABLED.   Time-critical APIs
 * may be converted to use this new macro.
 */

#ifndef NCP_CHECK_DISABLED
#define NCP_CHECK(_condition, _err) NCP_ASSERT((_condition), (_err))  
#else
#define NCP_CHECK(_condition, _err) ((void)(_condition),(void)(_err))
#endif

#ifndef NCP_TASKIO_CHECK_DISABLED
#define NCP_TASKIO_CHECK(_condition, _err) NCP_ASSERT((_condition), (_err))  
#else
#define NCP_TASKIO_CHECK(_condition, _err) 
#endif

/*
 * Read-Modify-Write helper macros
 *
 * NCP_RMW_REG can be used to declare and initialize two registers
 * of 'type' with the names 'name' and 'nameMask'. 
 *
 * NCP_RMW_SET will initialize the given field in both registers.
 * The field entry in the mask register will be set to all ones.
 */
#define NCP_RMW_REG(regType, regName) \
    regType regName = {0}; \
    regType regName##Mask = {0};

#define NCP_RMW_SET_FIELD(regName, field, value) \
    regName.field = value; \
    regName##Mask.field = -1;

#define NCP_RMW(dev, region, offset, regName) \
    do { \
        ncp_rmw_pair_t rmw_pair; \
        ncp_rmw_t      rmw_buf;  \
        ncp_uint32_t  *mask = (ncp_uint32_t *) &regName##Mask; \
        rmw_pair.rmw_data = *(ncp_uint32_t *)&regName; \
        rmw_pair.rmw_mask = *(ncp_uint32_t *)&regName##Mask; \
        rmw_buf.count = 1; \
        rmw_buf.NCP_POINTER(rmw_buffer) = &rmw_pair; \
        NCP_CALL(ncp_read_modify_write(dev, region, offset, &rmw_buf, 0)); \
        *mask = 0; \
    } while (0)

/* 
 * A general purpose way to eliminate warnings due the the label not being referenced.
 * 
 */
#define NCP_RETURN_LABEL \
goto ncp_return; \
ncp_return:

#define NCP_IS_PRIMARY_DOMAIN(n)    (n->domainId == 0)
#define NCP_IS_SECONDARY_DOMAIN(n)  (n->domainId  > 0)


/*
 * Platform independant 64-bit integer type, used for
 * 64-bit fill operations.  This should work even if the
 * kernel driver is compiled without 64-bit int support.
 */
typedef struct ncp_dev_fill64_s {
    ncp_uint32_t data[2];
} ncp_dev_fill64_t;

typedef struct {
    ncp_region_id_t regionId;
    ncp_uint32_t offset;
    ncp_dev_fill64_t value;
    ncp_uint32_t count;
} ncp_dev_trans_block_fill64_t;


/*
 * ACP device alarm interface 
 */

#define NCP_DEV_ALARM_BITMASK_WORDS 16
typedef struct {
    ncp_uint32_t    bits[NCP_DEV_ALARM_BITMASK_WORDS];
} ncp_alarm_bitmask_t;


/*
 * The standard Nuevo interrupt register programming model
 * is 'set bit to enable, clear bit to mask'. However, some
 * legacy and 3rd-party modules do not conform to this standard. 
 * We define bits in the flags field to indicate non-standard
 * behavior.
 */
#define NCP_ALARM_BITS_INVERTED   0x00000001
#define NCP_ALARM_SKIP_ENABLE	  0x00000002

typedef struct {
    ncp_uint32_t        irq;
    ncp_region_id_t     regionId;
    ncp_uint32_t        offset;
    ncp_uint32_t        value;
} ncp_alarm_source_t;

typedef struct {
    ncp_region_id_t             regionId;
    ncp_uint32_t                enbRegOffset;
    ncp_uint32_t                statRegOffset;
    ncp_uint32_t                alarmMask;
    ncp_uint32_t                serviceMask;
    ncp_uint32_t                flags;
} ncp_alarm_intr_regs_t;



#ifdef __cplusplus
}
#endif

#endif                          /* NCP_TYPES_H */
