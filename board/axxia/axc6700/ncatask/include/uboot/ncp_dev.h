/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/

/*! @file      ncp_dev.h
 *  @brief     Exported Device-level APIs.
 *  @addtogroup _device_APIs Device Level APIs
 *  Device-level APIs work with flat memory in each device, specifying addresses
 *  or ranges of addresses. The object-level APIs call these device-level APIs,
 *  and the host program can also call the device-level APIs directly.
 *
 *  @{
 */

#ifndef __NCP_DEV_H__
#define __NCP_DEV_H__

/*
 * ncp_dev.h
 *
 * This is the external header file for the NCP device driver.
 * This provides the function prototypes and associated definitions
 * needed for the user application to access the device APIs.
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Early / Forward type definitions of interest to the includes
 */
typedef void * ncp_dev_hdl_t;

/*
 * Includes
 */

#if (1 == USE_EIOA)
#include "uboot/ncp_sal_types_linux.h"
#include "uboot/ncp_sal_linux.h"
#endif

#include "uboot/ncp_types.h"
#include "uboot/ncp_dev_config_regs.h"
#include "uboot/ncp_task.h"
#include "uboot/ncp_nodes.h"


/* --- Maximum version string length --- */
#define NCP_DEV_MAX_VERSION_LENGTH  (41)

/* --- NCP I/O Flags --- */
#define NCP_IO_PIO                  (0x00000001)
#define NCP_IO_DMA                  (0x00000002)
#define NCP_IO_ZERO_COPY            (0x00000004)
#define NCP_IO_KERN_USER            (0x00000008)
#define NCP_IO_SYNC                 (0x00000010)
#define NCP_IO_TRANS                (0x00000020)
#define NCP_IO_COH_WRBACK           (0x00000040)
#define NCP_IO_COH_ATOMIC_TYPE      (0x00000080)
#define NCP_IO_I2C_SEEK             (0x00000100)
#define NCP_IO_IMC_WA               (0x00000200)
#define NCP_IO_BIG_ENDIAN           (0x00000400)
#define NCP_IO_LITTLE_ENDIAN        (0x00000800)
#define NCP_IO_ENDIAN               (0x00000c00)
#define NCP_IO_NONALIGN             (0x00001000)
#define NCP_IO_I2C_SMB              (0x00002000)
#define NCP_IO_I2C_10BIT            (0x00004000)
#define NCP_IO_I2C_OFFSET_1BYTE (0x00008000)
#define NCP_IO_I2C_OFFSET_2BYTE (0x00010000)
#define NCP_IO_I2C_OFFSET_3BYTE (0x00020000)
#define NCP_IO_I2C_OFFSET_4BYTE (0x00040000)
#define NCP_IO_CMEM_ZQ              (0x00080000)
#define NCP_IO_RESERVED             (0xFFF00000)

/* --- NCA Config Ring Commands --- */
#define NCP_NCA_CMD_STATUS          (0x00000002)
#define NCP_NCA_CMD_CRBR            (0x00000004)
#define NCP_NCA_CMD_CRBW            (0x00000005)
#define NCP_NCA_CMD_CRSW            (0x00000006)
#define NCP_NCA_CMD_CRBF            (0x00000007)
#define NCP_NCA_CMD_CRRMW           (0x00000008)
#define NCP_NCA_CMD_CRBBW           (0x00000009)
#define NCP_NCA_CMD_CRBSW           (0x0000000A)
#define NCP_NCA_CMD_CRBBF           (0x0000000B)
#define NCP_NCA_CMD_SMBR            (0x0000000C)
#define NCP_NCA_CMD_SMBW            (0x0000000D)
#define NCP_NCA_CMD_CSMBR           (0x0000000E)
#define NCP_NCA_CMD_CSMBW           (0x0000000F)

#define NCP_NCA_NUM_IO_CMDS         12

#define NCP_CFG_CMD_BUF_SIZE    (sizeof(ncp_coherent_sysmem_io_t))

#define NCP_SM_INTR_BITS            20

/* --- NCP Device Instance Flags --- */
#define NCP_DEV_FLAGS_MASK          (0x0000ffff) /* driver flags */
#define NCP_USER_FLAGS_MASK         (0xffff0000) /* user/API flags */

#define NCP_DEV_BUS_PCI             (0x00000001)
#define NCP_DEV_BUS_SRIO            (0x00000002)
#define NCP_DEV_BUS_PLB             (0x00000004)
#define NCP_DEV_BUS_SRIOEP          (0x00000008)
#define NCP_DEV_BUS_PLX				(0x00000010)
#define NCP_DEV_BUS_ACE				(0x00000020)
#define NCP_DEV_BUS_HW              (0x0000003F)  /* mask for all h/w adaptors*/
#define NCP_DEV_BUS_INTERNAL        ( NCP_DEV_BUS_PLB | NCP_DEV_BUS_ACE )  /* mask for all interal cores */
                                                  /* add'l adapters may be
                                                   * enumerated in the holes
                                                   * in the above listing. */
#define NCP_DEV_BUS_FBRS            (0x00000100)
#define NCP_DEV_BUS_SOCKET          (0x00000200)
#define NCP_DEV_IS_ASIC             (0x00000400)
#define NCP_DEV_CONFIGURED          (0x00000800)
#define NCP_DEV_ISR_ENABLED         (0x00001000)
#define NCP_DEV_TRANS_BUSY          (0x00002000)


/*
 * The flag bits masked by NCP_DEV_SCRATCHPAD_MASK
 * are also stored in the scratch-pad register.
 * This makes them persistant across a driver reload,
 * so that the prior h/w state may be restored.
 */
#define NCP_DEV_SCRATCHPAD_MASK     (0xffff0000)
#define NCP_CFG_LOAD_COMPLETE       (0x00010000)
#define NCP_DOMAIN_ID_SCRATCH_VALID (0x00020000)
#define NCP_DOMAIN_ID_SCRATCH_BITS  (0x003c0000)
#define NCP_DOMAIN_ID_SCRATCH_SHIFT (18)


/* --- NCP Device Handle --- */
#define NCP_DEV_INVALID_HANDLE  ((void *)-1)


/* --- NCP Device Info Structure --- */
typedef ncp_rev_id_t ncp_version_t;

typedef struct {
    ncp_uint8_t ndevs;
    ncp_uint32_t status[NCP_MAX_DEVS];
} ncp_dev_info_t;


/* --- NCP Device Statistics Structure --- */

typedef struct {
    ncp_uint32_t count;
    ncp_uint32_t nBytes;
    ncp_uint32_t minSize;
    ncp_uint32_t maxSize;
} ncp_dev_io_stats_t;


typedef struct {
    ncp_uint32_t count;
    ncp_uint32_t bytes;
    ncp_uint32_t minSize;
    ncp_uint32_t maxSize;
    ncp_uint32_t queueFullCount;
    ncp_uint32_t maxQueueDepth;
} ncp_dev_pdu_stats_t;

typedef struct {
    ncp_uint32_t timeout;
    ncp_uint32_t decode;
    ncp_uint32_t node;
    ncp_uint32_t wrongAck;
    ncp_uint32_t ackTimeout;
    ncp_uint32_t unclaimedHeader;
    ncp_uint32_t ring0Parity;
    ncp_uint32_t ring1Parity;
    ncp_uint32_t ring2Parity;
    ncp_uint32_t unknown;
} ncp_dev_pio_err_t;

typedef struct {
    ncp_uint32_t    chipType;
    ncp_uint32_t    busAdaptor;

    /*
     * NCP device I/O statistics.
     */
    ncp_dev_io_stats_t pio[NCP_NCA_NUM_IO_CMDS];
    ncp_dev_io_stats_t dma[NCP_NCA_NUM_IO_CMDS];

    ncp_uint32_t dma_io8_delay_cnt;
    ncp_uint32_t dma_io32_delay_cnt;

    ncp_dev_pio_err_t  pio_err;
    ncp_uint32_t imcWorkaroundCnt;
    ncp_uint32_t imcWorkaroundFailed;

    /* PDU recv statistics */
    ncp_dev_pdu_stats_t pduRecv;

    /* PDU send statistics */
    ncp_dev_pdu_stats_t pduSend;

    /* Interrupt statistics */
    ncp_uint32_t spuriousIntCnt;

    /* sysmem interrupt statistics */
    ncp_uint32_t sysmem_intr_bits[NCP_SYSMEM_NUM_NODES][NCP_SM_INTR_BITS];

} ncp_dev_stats_t;

/*
 * GSM (Globally Shared Memory) and LCM config attibutes
 */
typedef struct ncp_dev_gsm_info_s {
    ncp_uint32_t    cookie;
    NCP_DECLARE_POINTER(ncp_uint8_t, hwGSM_uVA);
    NCP_DECLARE_POINTER(ncp_uint8_t, hwGSM_kernVA);
    ncp_uint32_t    hwGSM_size;
    NCP_DECLARE_RAW_ADDR(hwGSM_currOffset);     /* how far into hwGSM>? - used by alloc */
    ncp_uint64_t    hwGSM_PA NCP_COMPAT_ALIGN64;

    NCP_DECLARE_POINTER(ncp_uint8_t, LCM_uVA);
    NCP_DECLARE_POINTER(ncp_uint8_t, LCM_kernVA);
    ncp_uint32_t    LCM_size;
    ncp_uint64_t    LCM_PA NCP_COMPAT_ALIGN64;

    ncp_uint64_t    axiDmaBase NCP_COMPAT_ALIGN64;
    ncp_uint64_t    busDmaOffset NCP_COMPAT_ALIGN64;
    ncp_bool_t      useInterrupts;
} NCP_COMPAT_PACKED ncp_dev_gsm_info_t;

/* --- NCP PDU Vector Structure --- */
typedef struct {
    void * pduBuf;
    ncp_uint32_t pduBufSize;
} ncp_pdu_vec_t;


/* --- Device Target Access Map --- */
#if 0  /* Use struct that matches that used in the auto-generated RDL output include files */
typedef struct {
    ncp_uint32_t start;
    ncp_uint32_t end;
    ncp_uint8_t  rw;
} ncp_access_map_t;
#else
typedef struct ncp_access_map_s {
    ncp_uint64_t    begin;
    ncp_uint64_t    end;
    ncp_int32_t     word_size_in_bytes;
    ncp_int32_t     access_size_in_words;
} ncp_access_map_t;
#endif
/* --- Device Node/Target Address Space Map --- */
typedef struct {
    ncp_uint16_t node;
    ncp_uint16_t target;
    ncp_uint32_t size;
    ncp_access_map_t * accessMap;
} ncp_address_map_t;



/* --- NCP Device Level APIs --- */

/*! \defgroup devIoStatus Device Level I/O status codes *
 *
 * These error codes may be returned by any of the device
 * level I/O APIs.
 *
 * The following errors are detected by software as part of
 * the API parameter validation:
 * @return
 *     \li ::NCP_ST_DEV_INVALID_HANDLE
 *     \li ::NCP_ST_DEV_INVALID_BUFFER
 *     \li ::NCP_ST_DEV_INVALID_FLAGS
 *     \li ::NCP_ST_DEV_INVALID_REGION_ID
 *     \li ::NCP_ST_DEV_INVALID_ACCESS
 *     \li ::NCP_ST_DEV_INVALID_PAGE_ACCESS
 *     \li ::NCP_ST_DEV_INVALID_WIDTH
 *     \li ::NCP_ST_DEV_INVALID_OFFSET
 *     \li ::NCP_ST_DEV_INVALID_COMMAND
 *     \li ::NCP_ST_DEV_UNALIGNED_OFFSET
 *
 * The following errors indicate that an attempted PIO transfer
 * has failed for non-specific reasons.
 *     \li ::NCP_ST_DEV_IO_ERROR
 *     \li ::NCP_ST_DEV_PIO_FAILED
 *     \li ::NCP_ST_DEV_PIO_SW_TIMEOUT
 *
 * The following errors inidicate the cause of the PIO failure as
 * reported by the NCA engine. If driver tracing is enabled there
 * should be additional details about the error in the kernel log.
 * @return
 *     \li ::NCP_ST_DEV_PIO_TIMEOUT_ERR
 *     \li ::NCP_ST_DEV_PIO_DECODE_ERR
 *     \li ::NCP_ST_DEV_PIO_NODE_ERR
 *     \li ::NCP_ST_DEV_PIO_WRONG_ACK_ERR
 *     \li ::NCP_ST_DEV_PIO_ACK_TIMEOUT_ERR
 *     \li ::NCP_ST_DEV_PIO_UNCLAIMED_HDR_ERR
 *     \li ::NCP_ST_DEV_PIO_RING0_PARITY_ERR
 *     \li ::NCP_ST_DEV_PIO_RING1_PARITY_ERR
 *     \li ::NCP_ST_DEV_PIO_RING2_PARITY_ERR
 *
 * Note that the reporting of PIO errors differs between read and write
 * operations. Since write operations are posted, the write API can
 * return to the user before the operation has completed and the final
 * status is known. If the PIO operation fails the error will be detected
 * and reported by the next device I/O API call. Since read operations
 * must always complete they always return the true status of the operation,
 * unless they follow a failed write. If driver tracing is enabled it will
 * indicate the actual operation for which the error occurred.
 */

/*!
 * @fn ncp_st_t ncp_dev_init(void)
 * @brief Initializes the device driver.
 *        This API is available only in kernel mode.
 * @returns Status code indicating success or failure \link ncp_st_t \endlink
 */

NCP_API ncp_st_t ncp_dev_init(void);

/*!
 * @fn ncp_st_t ncp_dev_fini(void)
 * @brief Releases all system resources that are held by the device level API.
 *        This API is available only in kernel mode.
 * @returns Status code indicating success or failure \link ncp_st_t \endlink
 */

NCP_API ncp_st_t ncp_dev_fini(void);

/*!
 * @fn ncp_st_t ncp_dev_open( ncp_uint32_t devNum, ncp_uint32_t flags,
 *                            ncp_dev_hdl_t *devHdl)
 * @param devNum  IN: Device instance number
 * @param flags   IN: Open flags (not used sed to zero)
 * @param devHdl  OUT: Return location for NCP handle
 * @brief Converts an NCP device instance number into a device handle for
 *        use in subsequent device driver calls.
 *
 * Valid values for the device instance number range from
 * zero to [N . 1], where N represents the total number of NCP devices
 * in the system. NCP devices are numbered based on the order in which
 * they are found during the system bus enumeration process. Upon
 * successful completion, the NCP device handle is returned into the
 * memory location specified by devHdl.
 */

NCP_API ncp_st_t
ncp_dev_open(
    ncp_uint32_t devNum,
    ncp_uint32_t flags,
    ncp_dev_hdl_t *devHdl);

/*!
 * @fn ncp_st_t ncp_config_attach( ncp_uint32_t devNum, ncp_hdl_t *ncpHdl)
 * @param devNum  IN: Device instance number
 * @param ncpHdl  OUT: Return location for NCP handle
 * @brief Converts an NCP device instance number into a NCP object handle for
 *        use in subsequent kernel resident API calls.
 *
 * Valid values for the device instance number range from
 * zero to [N . 1], where N represents the total number of NCP devices
 * in the system.
 * Upon successful completion, the NCP device handle is returned into the
 * memory location specified by devHdl.
 */
NCP_API ncp_st_t
ncp_config_attach(
    ncp_uint32_t devNum,
    ncp_hdl_t *ncpHdl);

/*!
 * @fn ncp_st_t ncp_dev_close( ncp_dev_hdl_t devHdl);
 * @param devHdl IN: Device handle
 * @brief Frees the specified device handle.
 */

NCP_API ncp_st_t
ncp_dev_close(
    ncp_dev_hdl_t devHdl);

 /*!
 * @fn ncp_st_t ncp_dev_enable_nca_rx_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp);
 * @return Status code indicating success or failure \link ncp_st_t \endlink
 * @brief Function to force nca rx interrupts to be enabled for the
 * specified queue group.
 * This API should only be used by NAPI clients.
 * This API is available only in kernel mode.
 *
 *        This API is available only in kernel mode.
 * @param devHdl    - IN: NCP device handle.
 * @param tqsId     - IN: NCA TQS ID
 */
NCP_API ncp_st_t
ncp_dev_enable_nca_rx_ints(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t tqsId);

/*!
 * @fn ncp_st_t ncp_dev_disable_nca_rx_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp);
 * @return Status code indicating success or failure \link ncp_st_t \endlink
 * @brief Function to force nca rx interrupts to be disabled for the
 * specified queue group.
 * This API should only be used by NAPI clients.
 * This API is available only in kernel mode.

 *
 *        This API is available only in kernel mode.
 * @param devHdl    - IN: NCP device handle.
 * @param tqsId     - IN: NCA TQS ID
 */
NCP_API ncp_st_t
ncp_dev_disable_nca_rx_ints(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t tqsId);


/*!
 * @fn ncp_st_t ncp_dev_enable_nca_tx_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp);
 * @return Status code indicating success or failure \link ncp_st_t \endlink
 * @brief Function to force nca tx interrupts to be enabled for the
 * specified queue group.
 * This API should only be used by NAPI clients.
 * This API is available only in kernel mode.
 * @param devHdl    - IN: NCP device handle.
 * @param tqsId     - IN: NCA TQS ID
 */
NCP_API ncp_st_t
ncp_dev_enable_nca_tx_ints(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t tqsId);

/*!
 * @fn ncp_st_t ncp_dev_disable_nca_tx_ints(ncp_dev_hdl_t devHdl, ncp_uint8_t grp);
 * @return Status code indicating success or failure \link ncp_st_t \endlink
 * @brief Function to force nca tx interrupts to be disabled for the
 * specified queue group.
 * This API should only be used by NAPI clients.
 * This API is available only in kernel mode.
 * @param devHdl    - IN: NCP device handle.
 * @param tqsId     - IN: NCA TQS ID
 */
NCP_API ncp_st_t
ncp_dev_disable_nca_tx_ints(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t tqsId);


/*!
 * @fn ncp_st_t ncp_dev_read8( ncp_dev_hdl_t   devHdl, ncp_region_id_t regionId,
 *                             ncp_uint64_t    offset, ncp_uint8_t    *value)
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param value    OUT: Return location for read data
 *
 * @brief Reads an 8-bit value from the specified NCP device address space region
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_read8(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint8_t    *value);

/*!
 * @fn ncp_st_t ncp_dev_read16( ncp_dev_hdl_t  devHdl, ncp_region_id_t regionId,
 *                             ncp_uint64_t    offset, ncp_uint16_t    *value)
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param value    OUT: Return location for read data
 *
 * @brief Reads a 16-bit value from the specified NCP device address space region
 *
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_read16(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint16_t   *value);

/*!
 * @fn ncp_st_t ncp_dev_read32( ncp_dev_hdl_t  devHdl, ncp_region_id_t regionId,
 *                             ncp_uint64_t    offset, ncp_uint32_t    *value)
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param value    OUT: Return location for read data
 *
 * @brief Reads a 32-bit value from the specified NCP device address space region
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_read32(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint32_t   *value);
/*!
 * @fn ncp_st_t ncp_dev_read64( ncp_dev_hdl_t  devHdl, ncp_region_id_t regionId,
 *                             ncp_uint64_t    offset, ncp_uint64_t    *value)
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param value    OUT: Return location for read data
 *
 * @brief Reads a 64-bit value from the specified NCP device address space region
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_read64(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint64_t   *value);

/*!
 * @fn ncp_st_t ncp_dev_write8( ncp_dev_hdl_t  devHdl, ncp_region_id_t regionId,
 *                              ncp_uint64_t   offset, ncp_uint8_t     value)
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param value    IN: Write data
 *
 * @brief Writes an 8-bit value to the specified NCP device address space region
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_write8(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint8_t     value);

/*!
 * @fn ncp_st_t ncp_dev_write16( ncp_dev_hdl_t devHdl, ncp_region_id_t regionId,
 *                               ncp_uint64_t  offset, ncp_uint16_t    value)
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param value    IN: Write data
 *
 * @brief Writes an 16-bit value to the specified NCP device address space region
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_write16(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint16_t    value);

/*!
 * @fn ncp_st_t ncp_dev_write32( ncp_dev_hdl_t devHdl, ncp_region_id_t regionId,
 *                               ncp_uint64_t  offset, ncp_uint32_t     value)
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param value    IN: Write data
 *
 * @brief Writes an 32-bit value to the specified NCP device address space region
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_write32(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint32_t    value);

/*!
 * @fn ncp_st_t ncp_dev_write64( ncp_dev_hdl_t devHdl, ncp_region_id_t regionId,
 *                               ncp_uint64_t  offset, ncp_uint64_t     value)
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param value    IN: Write data
 *
 * @brief Writes an 64-bit value to the specified NCP device address space region
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_write64(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint64_t    value);

/*!
 * @fn ncp_st_t ncp_dev_block_read8( ncp_dev_hdl_t  devHdl, ncp_region_id_t regionId,
 *                      ncp_uint64_t   offset, ncp_uint8_t *buffer,
 *                      ncp_uint32_t   count,  ncp_uint32_t  flags)
 *
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param buffer  OUT: Return location for read data
 * @param count    IN: Number of 8-bit words to read
 * @param flags    IN: Operational control flags.
 *
 * @brief Reads a block of 8-bit values from the specified device address space
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_block_read8(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint8_t    *buffer,
    ncp_uint32_t    count,
    ncp_uint32_t    flags);

/*!
 * @fn ncp_st_t ncp_dev_block_read16(ncp_dev_hdl_t devHdl,
 *                                   ncp_region_id_t regionId,
 *                                   ncp_uint64_t  offset,
 *                                   ncp_uint16_t *buffer,
 *                                   ncp_uint32_t  count,
 *                                   ncp_uint32_t  flags)
 *
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param buffer  OUT: Return location for read data
 * @param count    IN: Number of 16-bit words to read
 * @param flags    IN: Operational control flags.
 *
 * @brief Reads a block of 16-bit values from the specified device address space
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_block_read16(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint16_t   *buffer,
    ncp_uint32_t    count,
    ncp_uint32_t    flags);

/*!
 * @fn ncp_st_t ncp_dev_block_read32( ncp_dev_hdl_t   devHdl,
 *                                    ncp_region_id_t regionId,
 *                                    ncp_uint64_t    offset,
 *                                    ncp_uint32_t   *buffer,
 *                                    ncp_uint32_t    count,
 *                                    ncp_uint32_t    flags)
 *
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param buffer  OUT: Return location for read data
 * @param count    IN: Number of 32-bit words to read
 * @param flags    IN: Operational control flags.
 *
 * @brief Reads a block of 32-bit values from the specified device address space
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_block_read32(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint32_t   *buffer,
    ncp_uint32_t    count,
    ncp_uint32_t    flags);

/*!
 * @fn ncp_st_t ncp_dev_block_read64( ncp_dev_hdl_t   devHdl,
 *                                    ncp_region_id_t regionId,
 *                                    ncp_uint64_t    offset,
 *                                    ncp_uint64_t   *buffer,
 *                                    ncp_uint32_t    count,
 *                                    ncp_uint32_t    flags)
 *
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param buffer  OUT: Return location for read data
 * @param count    IN: Number of 64-bit value to read
 * @param flags    IN: Operational control flags.
 *
 * @brief Reads a block of 32-bit values from the specified device address space
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_block_read64(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint64_t   *buffer,
    ncp_uint32_t    count,
    ncp_uint32_t    flags);

/*!
 * @fn ncp_st_t ncp_dev_block_write8( ncp_dev_hdl_t  devHdl, ncp_region_id_t regionId,
 *                       ncp_uint64_t   offset, ncp_uint8_t *buffer,
 *                       ncp_uint32_t   count,  ncp_uint32_t  flags)
 *
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param buffer  OUT: Return location for write data
 * @param count    IN: Number of 8-bit words to read
 * @param flags    IN: Operational control flags.
 *
 * @brief Writes a block of 8-bit values to the specified device address space
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_block_write8(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint8_t    *buffer,
    ncp_uint32_t    count,
    ncp_uint32_t    flags);


/*!
 * @fn ncp_st_t ncp_dev_block_write16( ncp_dev_hdl_t  devHdl, ncp_region_id_t regionId,
 *                        ncp_uint64_t   offset, ncp_uint16_t *buffer,
 *                        ncp_uint32_t   count,  ncp_uint32_t  flags)
 *
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param buffer  OUT: Return location for write data
 * @param count    IN: Number of 16-bit words to read
 * @param flags    IN: Operational control flags.
 *
 * @brief Writes a block of 16-bit values to the specified device address space
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_block_write16(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint16_t   *buffer,
    ncp_uint32_t    count,
    ncp_uint32_t    flags);


/*!
 * @fn ncp_st_t ncp_dev_block_write32( ncp_dev_hdl_t  devHdl, ncp_region_id_t regionId,
 *                        ncp_uint64_t   offset, ncp_uint32_t *buffer,
 *                        ncp_uint32_t   count,  ncp_uint32_t  flags)
 *
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param buffer  OUT: Return location for write data
 * @param count    IN: Number of 32-bit words to read
 * @param flags    IN: Operational control flags.
 *
 * @brief Writes a block of 32-bit values to the specified device address space
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_block_write32(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint32_t   *buffer,
    ncp_uint32_t    count,
    ncp_uint32_t    flags);

/*!
 * @fn ncp_st_t ncp_dev_block_write64( ncp_dev_hdl_t  devHdl, ncp_region_id_t regionId,
 *                        ncp_uint64_t   offset, ncp_uint64_t *buffer,
 *                        ncp_uint32_t   count,  ncp_uint32_t  flags)
 *
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param buffer  OUT: Return location for write data
 * @param count    IN: Number of 64-bit values to read
 * @param flags    IN: Operational control flags.
 *
 * @brief Writes a block of 32-bit values to the specified device address space
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_block_write64(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset,
    ncp_uint64_t   *buffer,
    ncp_uint32_t    count,
    ncp_uint32_t    flags);


/*!
 * @fn ncp_st_t ncp_dev_block_fill( ncp_dev_hdl_t  devHdl, ncp_region_id_t regionId,
 *                     ncp_uint64_t   offset, ncp_fill_t *ncp_fill_p,
 *                     ncp_uint32_t  flags)
 *
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param ncp_fill_p   IN: pointer to fill command buffer.
 * @param flags    IN: Operational control flags.
 *
 * @brief Fills a specified device address space with a constant value.
 *
 * For config ring targets the fill operation will use the NCA engine
 * Config Ring Block Fill (CRBF) command. This allows the user to
 * specify the width of the fill pattern and address stride for each
 * successive write.
 *
 * For non config ring targets only a simple 32-bit fill is supported.
 *
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_block_fill(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset64,
    ncp_fill_t     *ncp_fill_p,
    ncp_uint32_t    flags);

/*!
 * @fn ncp_st_t ncp_dev_read_modify_write(ncp_dev_hdl_t devHdl, ncp_region_id_t regionId,
 *                               ncp_uint64_t  offset, ncp_rmw_t *ncp_rmw_p,
 *                               ncp_uint32_t  flags)
 *
 * @param devHdl    IN: Device handle
 * @param regionId  IN: Node/target address
 * @param offset    IN: Node/target offset
 * @param ncp_rmw_p IN: pointer to read-modify-write(RMW) structure.
 * @param flags     IN: Operational control flags.
 *
 * @brief Performs an atomic Read Modify Write command on the specified
 * region offset.
 *
 * For each offset the user specifies a value/mask pair. The mask
 * indicates which bits of the register are to be modified.
 *
 * This command is only supported for real config ring targets (nodeId <= 0xff).
 *
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_read_modify_write(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset64,
    ncp_rmw_t      *ncp_rmw_p,
    ncp_uint32_t    flags);

/*!
 * @fn ncp_st_t ncp_dev_scatter_write(ncp_dev_hdl_t devHdl,
 *                                        ncp_region_id_t regionId,
 *                                        ncp_crsw_t   *crsw_p,
 *                                        ncp_uint32_t  flags)
 *
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param crsw_p   IN: pointer to CRSW structure.
 * @param flags    IN: Operational control flags.
 *
 * @brief Performs a 32-bit scatter write operation.
 *
 * The scatter buffer provides a set of address/data pairs, and
 * each data value will be written to the associated address.
 *
 * This command is only supported for real config ring targets (nodeId <= 0xff).
 *
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_scatter_write(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_crsw_t     *crsw_p,
    ncp_uint32_t    flags);

/*!
 * @fn ncp_st_t ncp_dev_broadcast_block_write(ncp_dev_hdl_t devHdl,
 *                                   ncp_region_id_t regionId,
 *                                   ncp_uint64_t  offset, ncp_crbbw_t *crbbw_p,
 *                                   ncp_uint32_t flags)
 *
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param buffer   IN: pointer to CRBBW structure.
 * @param flags    IN: Operational control flags.
 *
 * @brief Performs a broadcast block write of a 64-bit value
 *
 * The write operation will be broadcast to each node in the
 * specified nodeVector. They will all use the target specified
 * in the regionId. The node specified in the regionId should
 * be one of the nodes in the nodeVector.
 *
 * For example, to broadcast to regions 0.0, 2.0, 4.0, and 6.0,
 * one would set the nodeVector to 0x00000055, and set the
 * regionId to 0.0.
 *
 * This command is only supported for real config ring targets (nodeId <= 0xff).
 *
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_broadcast_block_write(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset64,
    ncp_crbbw_t    *crbbw_p,
    ncp_uint32_t    flags);

/*!
 * @fn ncp_st_t ncp_dev_broadcast_scatter_write(
 *                                     ncp_dev_hdl_t devHdl,
 *                                     ncp_region_id_t regionId,
 *                                     ncp_crbsw_t *crbsw_p,
 *                                     ncp_uint32_t flags)
 *
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param buffer   IN: pointer to CRBSW structure
 * @param flags    IN: Operational control flags.
 *
 * @brief Perform a broadcast scatter write of 64-bit values.
 *
 * The scatter buffer provides a set of address/data pairs, and
 * each data value will be written to the associated address.
 *
 * Each write operation will be broadcast to each node in the
 * specified nodeVector. They will all use the target specified
 * in the regionId. The node specified in the regionId should
 * be one of the nodes in the nodeVector.
 *
 * This command is only supported for real config ring targets (nodeId <= 0xff).
 *
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_broadcast_scatter_write(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_crbsw_t    *crbsw_p,
    ncp_uint32_t    flags);

/*!
 * @fn ncp_st_t ncp_dev_broadcast_block_fill(
 *                                           ncp_dev_hdl_t   devHdl,
 *                                           ncp_region_id_t regionId,
 *                                           ncp_uint64_t    offset64,
 *                                           ncp_fill_t     *ncp_fill_p,
 *                                           ncp_uint32_t    flags)
 * @param devHdl   IN: Device handle
 * @param regionId IN: Node/target address
 * @param offset   IN: Node/target offset
 * @param buffer   IN: pointer to ncp_fill_t structure
 * @param flags    IN: Operational control flags.
 *
 * @brief Perform a broadcast block fill of a 64-bit value.
 *
 * The broadcast fill operation does not support variable pattern
 * widths, it is always a 64-bit operation.
 *
 * This command is only supported for real config ring targets (nodeId <= 0xff).
 *
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_broadcast_block_fill(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    offset64,
    ncp_fill_t     *ncp_fill_p,
    ncp_uint32_t    flags);

/*!
 * @fn ncp_st_t ncp_dev_coherent_sysmem_read(ncp_dev_hdl_t devHdl,
 *                                  ncp_region_id_t regionId,
 *                                  ncp_uint64_t address,
 *                                  ncp_uint8_t *buffer,
 *                                  ncp_uint32_t  count,
 *                                  ncp_uint32_t  xferWidth,
 *                                  ncp_uint32_t  flags)
 *
 * @param devHdl   IN: Device handle
 * @param regionId IN: Engine Node/target
 * @param address  IN: System Memory Address
 * @param buffer  OUT: read data buffer
 * @param count    IN: number of bytes to read
 * @param xferWidth IN: transfer width in bytes
 * @param flags    IN: Operational control flags.
 *
 * @brief perform a system memory read that is coherent with respect
 * to the engine specified by regionId.
 *
 * Coherent sysmem access is only supported by the MPP State Engine,
 * MTM, SPP, and DPI, and the maximum transfer size is one cache line
 * (256 bytes).
 *
 * There are two bits in the 'flags' argument specific to the coherent
 * sysmem access: NCP_IO_COH_ATOMIC_TYPE and NCP_IO_COH_WRBACK. These
 * are used to set the atomic_type and wrback bits in the atomic update
 * control register. See the ACP register programming guide for details.
 *
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_coherent_sysmem_read(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    address,
    ncp_uint8_t    *buffer,
    ncp_uint32_t    count,
    ncp_uint32_t    xferWidth,
    ncp_uint32_t    flags);

/*!
 * @fn ncp_st_t ncp_dev_coherent_sysmem_write(ncp_dev_hdl_t devHdl,
 *                                   ncp_region_id_t regionId,
 *                                   ncp_uint64_t  address,
 *                                   ncp_uint8_t  *buffer,
 *                                   ncp_uint32_t count,
 *                                  ncp_uint32_t  xferWidth,
 *                                   ncp_uint32_t  flags)
 *
 * @param devHdl   IN: Device handle
 * @param regionId IN: Engine Node/target
 * @param address  IN: System Memory address
 * @param buffer   IN: write data
 * @param count    IN: number of bytes to write
 * @param xferWidth IN: transfer width in bytes
 * @param flags    IN: Operational control flags.
 *
 * @brief perform a system memory write that is coherent with respect
 * to the engine specified by regionId.
 *
 * Coherent sysmem access is only supported by the MPP State Engine,
 * MTM, SPP, and DPI, and the maximum transfer size is one cache line
 * (256 bytes).
 *
 * There are two bits in the 'flags' argument specific to the coherent
 * sysmem access: NCP_IO_COH_ATOMIC_TYPE and NCP_IO_COH_WRBACK. These
 * are used to set the atomic_type and wrback bits in the atomic update
 * control register. See the ACP register programming guide for details.
 *
 * @returns \link devIoStatus Device level I/O status codes \endlink
 */

NCP_API ncp_st_t
ncp_dev_coherent_sysmem_write(
    ncp_dev_hdl_t   devHdl,
    ncp_region_id_t regionId,
    ncp_uint64_t    address,
    ncp_uint8_t    *buffer,
    ncp_uint32_t    count,
    ncp_uint32_t    xferWidth,
    ncp_uint32_t    flags);


/*!
 * @fn ncp_st_t ncp_dev_info( ncp_dev_info_t *devInfo)
 * @param devInfo  OUT: Return location for device info
 *
 * @brief Retrieves system level device information.
 */

NCP_API ncp_st_t ncp_dev_info(
    ncp_dev_info_t *devInfo);

/*!
 * @fn ncp_st_t ncp_dev_info_get( ncp_dev_hdl_t devHdl, ncp_uint32_t *flags)
 * @brief Returns the current flags for a single NCP instance.
 * @param devHdl    IN: Device handle.
 * @param devInfo  OUT: Return location for device info
 *
 */

NCP_API ncp_st_t ncp_dev_info_get(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t *flags);

/*!
 * @fn ncp_st_t ncp_dev_info_set( ncp_dev_hdl_t devHdl, ncp_uint32_t flags)
 * @param devHdl    IN: Device handle.
 * @param flags    OUT: New flags for device.
 *
 * Sets the flags for a single NCP instance.
 */

NCP_API ncp_st_t ncp_dev_info_set(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t flags);

/*!
 * @fn ncp_st_t ncp_dev_hw_version_get( ncp_dev_hdl_t devHdl,
 *                                      ncp_version_t *version)
 * @brief Returns the version of the hardware device associated with devHdl.
 *        See NCP_CHIP_... constants for examples.
 * @param devHdl   IN: Device handle
 * @param version OUT: Return location for dev version
 *
 */

NCP_API ncp_st_t ncp_dev_hw_version_get(
    ncp_dev_hdl_t devHdl,
    ncp_version_t *version);

/*!
 * @fn ncp_st_t ncp_dev_stats( ncp_dev_hdl_t devHdl, ncp_dev_stats_t *devStats)
 * @param devHdl    IN: Device handle
 * @param devStats OUT: Return location for device stats
 *
 * @brief retrieve device driver statistics
 */

NCP_API ncp_st_t ncp_dev_stats(
    ncp_dev_hdl_t devHdl,
    ncp_dev_stats_t *devStats);

/*!
 * @fn ncp_st_t ncp_dev_version( char *version)
 * @param version OUT: Return location for version info
 *
 * @brief returns the device driver software version (release ID).
 */

NCP_API ncp_st_t ncp_dev_version(
    char *version);

/*!
 * @fn ncp_st_t ncp_dev_trace_level_get( ncp_dev_hdl_t devHdl,
 *                                       ncp_uint32_t *traceLevel)
 * @brief Gets the current trace level of the ACP device driver.
 *        The device driver supportes up to 32 distinct mesage classes,
 *        each class associated with a bit of the trace level.  [See
 *        NCP_MSG_...  bit handles for the values that have been
 *        implemented.]  Not all of the possible classes may be
 *        implemented.
 * @param devHdl      IN: Device handle
 * @param traceLevel OUT: Current trace level
 */

NCP_API ncp_st_t ncp_dev_trace_level_get(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t *traceLevel);

/*!
 * @fn ncp_st_t ncp_dev_trace_level_set( ncp_dev_hdl_t devHdl,
 *                                       ncp_uint32_t traceLevel)
 * @brief Gets the current trace level of the ACP device driver.
 *        The device driver supportes up to 32 distinct mesage classes,
 *        each class associated with a bit of the trace level.  One can
 *        independently enable and disable the classes.  [See NCP_MSG_...
 *        bit handles for the values that have been implemented.]  Not
 *        all of the possible classes may be implemented.
 * @param devHdl     IN: Device handle
 * @param traceLevel IN: Selected trace level
 */

NCP_API ncp_st_t ncp_dev_trace_level_set(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t traceLevel);

#if 0 
this is implemented
/*!
 * @fn ncp_st_t ncp_dev_reset( ncp_dev_hdl_t devHdl)
 * @brief Performs a reset of the hardware and software of the ACP device
 *        associated with devHdl.  Only the primary domain is permitted
 *        to reset the device.
 * @param devHdl  IN: Device handle
 */

NCP_API ncp_st_t ncp_dev_reset(
    ncp_dev_hdl_t devHdl);

#endif


/*!
 * @fn ncp_st_t ncp_dev_num_get( ncp_dev_hdl_t devHdl, ncp_uint32_t *devNum)
 * @brief Returns the device instance number for the specified ACP device.
 * @param devHdl   IN: Device handle
 * @param devNum   OUT: Device number
 */

NCP_API ncp_st_t ncp_dev_num_get(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t *devNum);

/*!
 * @fn ncp_st_t ncp_dev_alarm_irq_get( ncp_dev_hdl_t devHdl,
 *                                 ncp_bool_t    blocking,
 *                                 ncp_alarm_bitmask_t  *alarm );
 * @brief This functions retrieves the current alarm mask for the specified
 *        ACP device, possibly blocking until one or more has been triggered.
 *        The mask buffer must be allocated by the caller.  It should be
 *        large enough to contain a bit position for every possible alarm
 *        source.
 * @param devHdl     IN: Device handle
 * @param blocking   IN: API is blocking when true, non-blocking when false
 * @param alarm     OUT: bitmask of alarm interrupts
 */

NCP_API ncp_st_t ncp_dev_alarm_irq_get(
    ncp_dev_hdl_t devHdl,
    ncp_bool_t    blocking,
    ncp_alarm_bitmask_t *alarm);

/*!
 * @fn  ncp_st_t ncp_dev_alarm_handler_register( ncp_dev_hdl_t devHdl,
 *                                               ncp_uint32_t  irq,
 *                                               ncp_uint32_t  size,
 *                                               ncp_alarm_intr_regs_t *regs);
 * @brief Register the alarm ISR and enable  IRQ
 * @param devHdl     IN: Device handle
 * @param irq        IN: The IRQ instance to copy the registers from.
 * @param size       IN: The number of registers to copy.
 * @param regs      OUT: The registers from the specified IRQ.
 */
NCP_API ncp_st_t ncp_dev_alarm_handler_register(
     ncp_dev_hdl_t devHdl,
     ncp_uint32_t  irq,
     ncp_uint32_t  size,
     ncp_alarm_intr_regs_t *regs);


/*!
 * @fn ncp_st_t ncp_dev_se_fem_event_get( ncp_dev_hdl_t devHdl);
 * @brief This function waits for an SE service interrupt.  It blocks waiting for
 * the interrupt if interrupts are supported on the platform, and sleeps as part
 * of a polling implementation if interrupts are not supported.
 * @param devHdl     IN: Device handle
 */

#define NCP_SE_FEM_POLL_TIME 1000

NCP_API ncp_st_t ncp_dev_se_fem_event_get(ncp_dev_hdl_t devHdl);

/*!
 * @fn ncp_st_t ncp_dev_sm_treemem_zq_calibrate_start( ncp_hdl_t hdl, ncp_uint32_t timerInterval, ncp_uint32_t numCmems)
 * @brief Starts the software-based ZQCS routine
 * @param hdl            IN: Device handle
 * @param timerInterval  IN: Interval to send ZQCS command
 * @param numCmems       IN: Number of CMEMs to calibrate
 */
  NCP_API ncp_st_t ncp_dev_sm_treemem_zq_calibrate_start(ncp_hdl_t hdl, ncp_uint32_t timerInterval, ncp_uint32_t numCmems);

/*!
 * @fn ncp_st_t ncp_dev_sm_treemem_zq_calibrate_stop( ncp_hdl_t hdl)
 * @brief Stops the software-based ZQCS routine
 * @param hdl            IN: Device handle
 */
NCP_API ncp_st_t ncp_dev_sm_treemem_zq_calibrate_stop(ncp_hdl_t hdl);

/*!
 * @fn ncp_st_t ncp_dev_eioa_hss_los_hdlr_start ( ncp_hdl_t hdl, ncp_uint32_t timerInterval)
 * @brief Starts the software-based LOS-handler routine
 * @param hdl            IN: Device handle
 * @param timerInterval  IN: Interval to Poll
 */
  NCP_API ncp_st_t ncp_dev_eioa_hss_los_hdlr_start(ncp_hdl_t hdl, ncp_uint32_t timerInterval);

/*!
 * @fn ncp_st_t ncp_dev_eioa_hss_los_hdlr_stop (ncp_hdl_t hdl)
 * @brief Stops the software-based LOS-handler routine
 * @param hdl            IN: Device handle
 */
  NCP_API ncp_st_t ncp_dev_eioa_hss_los_hdlr_stop(ncp_hdl_t hdl);

/*!
 * @fn ncp_st_t ncp_dev_timer_event_get( ncp_dev_hdl_t devHdl,ncp_uint64_t *ticks);
 * @brief This function waits for a Timer service interrupt.  It blocks waiting for
 * the interrupt if interrupts are supported on the platform, and returns if
 * interrupts are not supported.
 * @param devHdl     IN: Device handle
 * @param ticks      OUT: Timer ref strobe timestamp
 */
NCP_API ncp_st_t ncp_dev_timer_event_get(ncp_dev_hdl_t devHdl, ncp_uint64_t *ticks);

/*!
 * @fn ncp_st_t ncp_dev_timer_cpu_timer_event_wait(ncp_hdl_t hdl,
 *                    ncp_uint32_t timerIndex, ncp_uint64_t lastSeq,
 *                    ncp_uint64_t *currentSeq, ncp_uint32_t flags);
 * @brief Block on CPU Timer event.  Blocks until a CPU timer fires with sequence number greater than lastSeq.
 * @param hdl         IN: Device handle
 * @param timerIndex  IN: Timer index for the requested CPU timer.  Range from 0-15.
 * @param lastSeq     IN: The last captured sequence number for this CPU timer.
 * @param currentSeq OUT: The returned sequence number for this CPU timer.
 * @param flags       IN: Don't block if NCP_TIMER_FLAGS_CPU_TIMER_WAIT_NO_BLOCK is specified.
 */
NCP_API ncp_st_t ncp_dev_timer_cpu_timer_event_wait(ncp_hdl_t hdl, ncp_uint32_t timerIndex, ncp_uint64_t lastSeq, ncp_uint64_t *currentSeq, ncp_uint32_t flags);


/* --- NCP Device Level Transaction Interfaces --- */

typedef enum {
    NCP_DEV_TRANS_UNKNOWN = 0,
    NCP_DEV_TRANS_UDELAY,
    NCP_DEV_TRANS_BLOCK_FILL32,
    NCP_DEV_TRANS_BLOCK_WRITE32,
    NCP_DEV_TRANS_BLOCK_SCATTER32,
    NCP_DEV_TRANS_BLOCK_FILL64
} ncp_dev_trans_type_t;

typedef ncp_uint32_t ncp_dev_trans_udelay_t;

typedef struct {
    ncp_region_id_t regionId;
    ncp_uint32_t offset;
    ncp_uint32_t value;
    ncp_uint32_t reserved;
    ncp_uint32_t count;
} ncp_dev_trans_block_fill32_t;

typedef struct {
    ncp_region_id_t regionId;
    ncp_uint32_t offset;
    NCP_DECLARE_POINTER(ncp_uint32_t, dataBuf);
    ncp_uint32_t reserved;
    ncp_uint32_t count;
} ncp_dev_trans_block_write32_t;

#if     !defined(DOXYGEN)

/*!
 * @fn ncp_st_t ncp_dev_transaction_start( ncp_dev_hdl_t devHdl)
 *
 * @brief Return the client architecture bitwidth.   Used in compatibility (mixed) mode.
 *
 * @param devHdl   IN: Device handle
 *
 */

NCP_API ncp_st_t
ncp_dev_transaction_start(
    ncp_dev_hdl_t devHdl);

/*!
 * @fn ncp_st_t ncp_dev_transaction_add( ncp_dev_hdl_t devHdl,
 *                                       ncp_dev_trans_type_t transType,
 *                                       void *trans, ncp_uint32_t flags);
 * @param devHdl   IN: Device handle
 */

NCP_API ncp_st_t
ncp_dev_transaction_add(
    ncp_dev_hdl_t devHdl,
    ncp_dev_trans_type_t transType,
    void *trans,
    ncp_uint32_t flags);

/*!
 * @fn ncp_st_t ncp_dev_transaction_end( ncp_dev_hdl_t devHdl)
 * @param devHdl   IN: Device handle
 *
 */

NCP_API ncp_st_t
ncp_dev_transaction_end(
    ncp_dev_hdl_t devHdl);

#endif  /* !defined(DOXYGEN) */

typedef enum {
    NCP_DEV_CLIENT_INVALID=0,
    NCP_DEV_CLIENT_IS_32BIT=1,    
    NCP_DEV_CLIENT_IS_64BIT=2
} ncp_dev_client_bitwidth_e;

/*!
 * @fn ncp_st_t ncp_dev_userspace_bitwidth_get( ncp_dev_hdl_t devHdl,
 *                                       ncp_dev_client_bitwidth_e *pResult);
 * @param devHdl   IN: Device handle
 * @param pResult  OUT: pointer to enum that will be populated with the client architecture bitwidth
 * 
 * @retval NCP_ST_INVALID_PARAMETER: The dev handle and/or result pointer is null.
 * @retval NCP_ST_SUCCESS: *pResult contains the client architecture bitwidth
 *
 */  
NCP_API ncp_st_t
ncp_dev_userspace_bitwidth_get(ncp_dev_hdl_t devHdl, ncp_dev_client_bitwidth_e *pResult);

/*!
 * @enum ncp_dev_event_type_t.
 * @brief Enum defining different event types supported for registering
 *        callback functions.
 */

/*
 * WARN: When adding new events, add entries in eventInfo table (ncp_dev_event.c).
 */
typedef enum ncp_dev_event_type_e {
    /* this needs to be first */
    NCP_DEV_EVENT_FIRST = 0,

    NCP_DEV_EVENT_CFG_START = 0,
    NCP_DEV_EVENT_CFG_COMPLETE,
    NCP_DEV_EVENT_CFG_DESTROY,

    NCP_DEV_EVENT_NCA_GRP_ANY,               /* any nca grp interrupt source */
    NCP_DEV_EVENT_NCA_GRP_I_PCQ_INTERRUPT,
    NCP_DEV_EVENT_NCA_GRP_O_PCQ_INTERRUPT,
    NCP_DEV_EVENT_NCA_GRP_T_PCQ_INTERRUPT,
    NCP_DEV_EVENT_NCA_GRP_C_PCQ_INTERRUPT,
    NCP_DEV_EVENT_NCA_GRP0_ERROR_INTERRUPT,  /* Only valid for group 0 */

    NCP_DEV_EVENT_NCA_SHUTDOWN,              /* ncp driver is being unloaded */
    NCP_DEV_EVENT_PHY_STATUS_CHANGE,         /* Port Link Change event */
    NCP_DEV_EVENT_HOLDOVER,         	     /* Holdover event */

    /* this needs to be the last */
    NCP_DEV_EVENT_LAST
} ncp_dev_event_type_t;

/*!
 * @typedef ncp_dev_event_hdl_t
 * @brief NCP device event handle.
 */
typedef void * ncp_dev_event_hdl_t;

/* forward decleration */
struct ncp_dev_event_handler_st;

/*!
 * @fn NCP device event callback function.
 * @param cbk_info  - IN: Type of event for which the callback is being called.
 * @param eventData - IN: Parameter passed at register time.
 */

typedef void (* ncp_dev_event_fn_t)(const struct ncp_dev_event_handler_st *event,
                                    const void *eventData);

/*!
 * @struct ncp_dev_event_handler_t
 * @brief Event callback handler registration struct
 */

typedef struct ncp_dev_event_handler_st {
    ncp_dev_event_type_t type;      /* Type of event that has occured. */
    ncp_uint32_t id;                /* id of object for which the event has occured. */
    ncp_dev_event_fn_t cbkFn;       /* Callback function to be called when this event happens. */
    void *cbkArg;                   /* Parameter to be passed when calling the callback function. */
} ncp_dev_event_handler_t;


/*!
 * @fn ncp_st_t ncp_dev_event_handler_register(ncp_dev_hdl_t devHdl,
 *                              ncp_dev_event_handler_t *handlerInfo,
 *                              ncp_dev_event_hdl_t *eventHdl);
 * @return Status code indicating success or failure \link ncp_st_t \endlink
 * @brief NCP device event callback registration function.
 *        This API is available only in kernel mode.
 * @param devHdl    - IN: NCP device handle.
 * @param eventType - IN: Type of event for which the callback is being called.
 * @param eventHdl  - OUT: Handle to event.
 */

NCP_API ncp_st_t
ncp_dev_event_handler_register(ncp_dev_hdl_t devHdl,
                               ncp_dev_event_handler_t *handlerInfo,
                               ncp_dev_event_hdl_t *eventHdl);

/*!
 * @fn ncp_st_t ncp_dev_event_handler_unregister(ncp_dev_hdl_t devHdl,
 *                                               ncp_dev_event_hdl_t eventHdl);
 * @return Status code indicating success or failure \link ncp_st_t \endlink
 * @brief NCP device event callback un-registration function.
 *        This API is available only in kernel mode.
 * @param devHdl    - IN: NCP device handle.
 * @param eventHdl  - IN: Handle to event.
 */

NCP_API ncp_st_t
ncp_dev_event_handler_unregister(ncp_dev_hdl_t devHdl,
                                 ncp_dev_event_hdl_t eventHdl);

/*!
 * @fn ncp_st_t ncp_dev_event_dispatch_cfg_start(ncp_dev_hdl_t devHdl);
 * @brief Function to dispatch config load start event.
 *        This API is available only in kernel mode.
 * @param devHdl    - IN: NCP device handle.
 */

NCP_API ncp_st_t
ncp_dev_event_dispatch_cfg_start(ncp_dev_hdl_t devHdl);

/*!
 * @fn ncp_st_t ncp_dev_event_dispatch_cfg_complete(ncp_dev_hdl_t devHdl);
 * @brief Function to dispatch config complete event.
 *        This API is available only in kernel mode.
 * @param devHdl    - IN: NCP device handle.
 */

NCP_API ncp_st_t
ncp_dev_event_dispatch_cfg_complete(ncp_dev_hdl_t devHdl);

/*!
 * @fn ncp_st_t ncp_dev_event_dispatch_cfg_destroy(ncp_dev_hdl_t devHdl);
 * @brief Function to dispatch config destroy event.
 *        This API is available only in kernel mode.
 * @param devHdl    - IN: NCP device handle.
 */

NCP_API ncp_st_t
ncp_dev_event_dispatch_cfg_destroy(ncp_dev_hdl_t devHdl);

/*!
 * @fn ncp_st_t ncp_dev_mdioRead(
 *                                ncp_dev_hdl_t  devHdl,
 *                                ncp_region_id_t    regionId,
 *                                ncp_uint64_t        offset,
 *                                ncp_uint32_t       *buffer,
 *                                ncp_uint32_t        count,
 *                                ncp_uint32_t        flag)
 *
 * @brief Perform MDIO read sequence from PHY at target PHY address,
 *        and register offset.
 * @param devHdl    - IN: NCP device handle.
 * @param regionId  - IN: Node/Target of register
 * @param offset    - IN: Specific (start) register displacement
 * @param buffer    - OUT: Location to place results
 * @param count     - IN: Number of registers to read
 * @param flag      - IN: Control flag bits for read operation
 */

ncp_st_t
ncp_dev_mdioRead(
    ncp_dev_hdl_t       devHdl,
    ncp_region_id_t    regionId,
    ncp_uint64_t        offset,
    ncp_uint32_t       *buffer,
    ncp_uint32_t        count,
    ncp_uint32_t        flag);

/*!
 * @fn ncp_st_t ncp_dev_mdioWrite(
 *                                 ncp_dev_hdl_t       devHdl,
 *                                 ncp_region_id_t     regionId,
 *                                 ncp_uint64_t        offset,
 *                                 ncp_uint32_t       *buffer,
 *                                 ncp_uint32_t        count,
 *                                 ncp_uint32_t        flags)
 *
 * @brief Perform MDIO write sequence to PHY at target PHY address,
 *        and register offset.
 * @param devHdl    - IN: NCP device handle.
 * @param regionId  - IN: Node/Target of register
 * @param offset    - IN: Specific (start) register displacement
 * @param buffer    - IN: Location to provide write data
 * @param count     - IN: Number of registers to write
 * @param flag      - IN: Control flag bits for write operation
 */

ncp_st_t
ncp_dev_mdioWrite(
    ncp_dev_hdl_t       devHdl,
    ncp_region_id_t     regionId,
    ncp_uint64_t        offset,
    ncp_uint32_t       *buffer,
    ncp_uint32_t        count,
    ncp_uint32_t        flags);

/*!
 * @fn ncp_st_t ncp_dev_nrcp_event_wait( ncp_dev_hdl_t devHdl, ncp_uint32_t *nrcpIntrStat)
 * @brief Returns the current flags for a single NCP instance.
 * @param devHdl    IN: Device handle.
 * @param devInfo  OUT: Return location for device info
 *
 */

NCP_API ncp_st_t ncp_dev_nrcp_event_wait(
            ncp_dev_hdl_t devHdl,
                ncp_uint32_t *nrcpIntrStat);


/*!
 * @}
 */



NCP_API ncp_st_t
ncp_dev_nca_initiate_shutdown(ncp_dev_hdl_t devHdl);

#ifdef NCP_KERNEL
NCP_API void
ncp_dev_nca_taskio_write_reg32(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t  offset,
    ncp_uint32_t  val);

NCP_API void
ncp_dev_nca_taskio_read_reg32(
    ncp_dev_hdl_t devHdl,
    ncp_uint32_t  offset,
    ncp_uint32_t  *pVal);
#endif

NCP_API ncp_st_t
ncp_dev_nca_wait_for_isr_wakeup(
    ncp_dev_hdl_t dev,
    ncp_uint32_t intrType,
    ncp_uint8_t grp,
    ncp_uint32_t grpRelQueueId,
    ncp_uint8_t  tqsID);

ncp_st_t ncp_dev_nca_grp_intr_disable(
        ncp_dev_hdl_t devHdl,
        ncp_uint32_t type,
        ncp_uint32_t ncapId,
        ncp_uint8_t grp);

ncp_st_t
ncp_dev_nca_grp_intr_enable(
        ncp_dev_hdl_t devHdl,
        ncp_uint32_t type,
        ncp_uint32_t ncapId,
        ncp_uint8_t grp);

void 
ncp_dev_isr_spin_lock(ncp_dev_hdl_t devHdl, 
        ncp_isr_spinlock_t *lock, 
        unsigned long *flags);

void 
ncp_dev_isr_spin_unlock(ncp_dev_hdl_t devHdl, 
        ncp_isr_spinlock_t *lock, 
        unsigned long flags);

            


void 
ncp_dev_isr_spin_lock(ncp_dev_hdl_t devHdl, 
        ncp_isr_spinlock_t *lock, 
        unsigned long *flags);

void 
ncp_dev_isr_spin_unlock(ncp_dev_hdl_t devHdl, 
        ncp_isr_spinlock_t *lock, 
        unsigned long flags);

            

#ifdef __cplusplus
}
#endif

#endif /* __NCP_DEV_H__ */
