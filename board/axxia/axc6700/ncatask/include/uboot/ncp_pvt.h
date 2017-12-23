/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


#ifndef __NCP_PVT_H__
#define __NCP_PVT_H__

#include "uboot/ncp.h"

#ifdef __cplusplus
extern "C" { 
#endif

#define NCP_DEBUG_FIELD     "debug"
#define NCP_DEBUG_NONE      "NONE"
#define NCP_DEBUG_TASK_LOG  "TASK_LOGGING"
#define NCP_DEBUG_PERF      "PERFORMANCE"

#define NCP_REF_CLOCK_FREQ              (125000000)
#define NCP_NTICKS_PER_SECOND_ASIC      (256000000)
#define NCP_NTICKS_PER_SECOND_FPGA      (4000000)
#define NCP_NTICKS_PER_SECOND_FPGA_55xx (1280000)
#define NCP_SYS_FREQ_FPGA               (6250000)
#define NCP_SYS_FREQ_FPGA_55xx          (2000000)
#define NCP_SYS_FREQ_SIM                (400000000)

typedef enum ncp_debug_mode_e {
    ncp_debug_mode_none,
    ncp_debug_mode_task_log,
    ncp_debug_mode_perf
} ncp_debug_mode_t;

/***************************************************************************
* Chip Description Types & Constants                                       *
***************************************************************************/
#define NCP_HANDLE_COOKIE 0x244e4350

#define NCP_CFG_MAX_CHIP_NAME_LEN 16

typedef struct ncp_s
{
    ncp_uint32_t        cookie;
    ncp_uint32_t        id;
    //ncp_mutex_t         lock; 
    char                chipName[NCP_CFG_MAX_CHIP_NAME_LEN];
    ncp_debug_mode_t    debug_mode;

    ncp_uint64_t        apiStateVersion;
    ncp_dev_hdl_t       devId;
    ncp_rev_id_t        rev;
    ncp_bus_adaptor_t   busAdaptor;
    ncp_uint32_t        domainId;
    ncp_bool_t          domainIsInternal; /* domain is on Local Core(s)? */

    ncp_bool_t          isFBRS;
    ncp_bool_t          isSimulator;
    ncp_bool_t          isFPGA;

    ncp_uint64_t        fplCookie;

    ncp_hdl_t           mppHdl;
    ncp_hdl_t           timerHdl;
    ncp_hdl_t           vpmHdl;
    ncp_hdl_t           seHdl;
    ncp_hdl_t           sedHdl;
    ncp_hdl_t           mmeHdl;
    ncp_hdl_t           mtmHdl;
    ncp_hdl_t           sppHdl;
    ncp_hdl_t           pllHdl;
    ncp_hdl_t           pkaHdl;
    ncp_hdl_t           trngHdl;
    ncp_hdl_t           catHdl;
    ncp_hdl_t           ncaHdl;
    ncp_hdl_t           eioaHdl;
    ncp_hdl_t           eioaSwitchHdl;
    ncp_hdl_t           bpAggHdl;
    ncp_hdl_t           dpiHdl;
    ncp_hdl_t           dspHdl;
    ncp_hdl_t           ltefeHdl;
    ncp_hdl_t           rifHdl;
    ncp_hdl_t           erifHdl;
    ncp_hdl_t           sysmemHdl;
    ncp_hdl_t           alarmHdl;

    ncp_uint32_t        numTreemem;
    ncp_uint32_t        memTestMode;

    ncp_bool_t          mmbConfigDone;
    ncp_bool_t          pabConfigDone;
    ncp_bool_t          picConfigDone;
    ncp_bool_t          configDone;
    ncp_bool_t          noPhyConfig; /* BZ: 42187 and 42192*/

    char               *userInfo;

    ncp_hdl_t           rsrc;

#ifdef NCP_PROFILER
    ncp_hdl_t           profilerHdl;
#endif
    /* 
     * This is a hack to support FPGA acp25xx v2 in eioa.
     * This value is used in eioa code to determine if its v2 in FPGA.
     */
    ncp_int32_t         targetChipRevision;

    /* 
     * This is used by the COW code to narrow down the detection logic to pick 
     * the engines in a certain chip instead of trying all engines in all 
     * supported chips.
     */
    ncp_int32_t         targetChipType;

    /* 
     * PDU segment 0 start offset value. It is used by COW TDGL code.
     */
    ncp_int32_t         pduSeg0StartOffset;

    ncp_uint8_t         ncaVersion;
} ncp_t;

#define NCP_IS_SIM(ncp) \
    (ncp->isSimulator || ncp->isFBRS)


/***************************************************************************
* I/O including ncp_hwio_trace() capability                                *
***************************************************************************/
NCP_API
int ncp_sim_usleep(
    ncp_hdl_t ncpHdl, 
    unsigned long usecs);

NCP_API
int ncp_usleep(
    unsigned long usecs);

NCP_API 
ncp_st_t ncp_reset(
    ncp_dev_hdl_t devHdl); 

NCP_API 
ncp_st_t ncp_poll(
    ncp_dev_hdl_t    devHdl,
    ncp_region_id_t  regionId,
    ncp_uint64_t     offset,
    ncp_uint32_t     mask,
    ncp_uint32_t     value,
    ncp_uint32_t     delayTime,
    ncp_uint32_t     delayLoops);

NCP_API
ncp_st_t ncp_read8(
    ncp_dev_hdl_t devHdl,
    ncp_region_id_t regionId,        /* IN: Node/target address */
    ncp_uint64_t offset,             /* IN: Node/target offset */
    ncp_uint8_t *value);             /* OUT: Pointer to read data buffer */

NCP_API
ncp_st_t ncp_read16(
    ncp_dev_hdl_t devHdl,
    ncp_region_id_t regionId,        /* IN: Node/target address */
    ncp_uint64_t offset,             /* IN: Node/target offset */
    ncp_uint16_t *value);            /* OUT: Pointer to read data buffer */

NCP_API
ncp_st_t ncp_read32(
    ncp_dev_hdl_t devHdl,
    ncp_region_id_t regionId,        /* IN: Node/target address */
    ncp_uint64_t offset,             /* IN: Node/target offset */
    ncp_uint32_t *value);            /* OUT: Pointer to read data buffer */

NCP_API
ncp_st_t ncp_read64(
    ncp_dev_hdl_t devHdl,
    ncp_region_id_t regionId,        /* IN: Node/target address */
    ncp_uint64_t offset,             /* IN: Node/target offset */
    ncp_uint64_t *value);            /* OUT: Pointer to read data buffer */

NCP_API
ncp_st_t ncp_block_read8(
    ncp_dev_hdl_t devHdl,
    ncp_region_id_t regionId,        /* IN: Node/target address */
    ncp_uint64_t offset,             /* IN: Node/target offset */
    ncp_uint8_t *buffer,             /* IN: Pointer to read data */
    ncp_uint32_t count,              /* IN: Number of 8-bit words to write */
    ncp_uint32_t flags);             /* IN: I/O flags */

NCP_API
ncp_st_t ncp_block_read16(
    ncp_dev_hdl_t devHdl,
    ncp_region_id_t regionId,        /* IN: Node/target address */
    ncp_uint64_t offset,             /* IN: Node/target offset */
    ncp_uint16_t *buffer,            /* IN: Pointer to read data */
    ncp_uint32_t count,              /* IN: Number of 16-bit words to write */
    ncp_uint32_t flags);             /* IN: I/O flags */

NCP_API
ncp_st_t ncp_block_read32(
    ncp_dev_hdl_t devHdl,
    ncp_region_id_t regionId,        /* IN: Node/target address */
    ncp_uint64_t offset,             /* IN: Node/target offset */
    ncp_uint32_t *buffer,            /* IN: Pointer to read data */
    ncp_uint32_t count,              /* IN: Number of 32-bit words to write */
    ncp_uint32_t flags);             /* IN: I/O flags */

NCP_API
ncp_st_t ncp_block_read64(
    ncp_dev_hdl_t devHdl,
    ncp_region_id_t regionId,        /* IN: Node/target address */
    ncp_uint64_t offset,             /* IN: Node/target offset */
    ncp_uint64_t *buffer,            /* IN: Pointer to read data */
    ncp_uint32_t count,              /* IN: Number of 64-bit words to write */
    ncp_uint32_t flags);             /* IN: I/O flags */

NCP_API
ncp_st_t ncp_write8(
    ncp_dev_hdl_t devHdl,
    ncp_region_id_t regionId,        /* IN: Node/target address */
    ncp_uint64_t offset,             /* IN: Node/target offset */
    ncp_uint8_t value);              /* IN: 8-bit data value */

NCP_API
ncp_st_t ncp_write16(
    ncp_dev_hdl_t devHdl,
    ncp_region_id_t regionId,        /* IN: Node/target address */
    ncp_uint64_t offset,             /* IN: Node/target offset */
    ncp_uint16_t value);             /* IN: 16-bit data value */

NCP_API
ncp_st_t ncp_write32(
    ncp_dev_hdl_t devHdl,
    ncp_region_id_t regionId,        /* IN: Node/target address */
    ncp_uint64_t offset,             /* IN: Node/target offset */
    ncp_uint32_t value);             /* IN: 32-bit data value */

NCP_API
ncp_st_t ncp_write64(
    ncp_dev_hdl_t devHdl,
    ncp_region_id_t regionId,        /* IN: Node/target address */
    ncp_uint64_t offset,             /* IN: Node/target offset */
    ncp_uint64_t value);             /* IN: 64-bit data value */

NCP_API
ncp_st_t ncp_block_write8(
    ncp_dev_hdl_t devHdl,
    ncp_region_id_t regionId,        /* IN: Node/target address */
    ncp_uint64_t offset,             /* IN: Node/target offset */
    ncp_uint8_t *buffer,             /* IN: Pointer to write data */
    ncp_uint32_t count,              /* IN: Number of 8-bit words to write */
    ncp_uint32_t flags);             /* IN: I/O flags */

NCP_API
ncp_st_t ncp_block_write16(
    ncp_dev_hdl_t devHdl,
    ncp_region_id_t regionId,        /* IN: Node/target address */
    ncp_uint64_t offset,             /* IN: Node/target offset */
    ncp_uint16_t *buffer,            /* IN: Pointer to write data */
    ncp_uint32_t count,              /* IN: Number of 16-bit words to write */
    ncp_uint32_t flags);             /* IN: I/O flags */

NCP_API
ncp_st_t ncp_block_write32(
    ncp_dev_hdl_t devHdl,
    ncp_region_id_t regionId,        /* IN: Node/target address */
    ncp_uint64_t offset,             /* IN: Node/target offset */
    ncp_uint32_t *buffer,            /* IN: Pointer to write data */
    ncp_uint32_t count,              /* IN: Number of 32-bit words to write */
    ncp_uint32_t flags);             /* IN: I/O flags */

NCP_API
ncp_st_t ncp_block_write64(
    ncp_dev_hdl_t devHdl,
    ncp_region_id_t regionId,        /* IN: Node/target address */
    ncp_uint64_t offset,             /* IN: Node/target offset */
    ncp_uint64_t *buffer,            /* IN: Pointer to write data */
    ncp_uint32_t count,              /* IN: Number of 64-bit words to write */
    ncp_uint32_t flags);             /* IN: I/O flags */

NCP_API ncp_st_t
ncp_block_fill(
    ncp_dev_hdl_t   devHdl,         /* IN: Device handle */
    ncp_region_id_t regionId,       /* IN: Node/target address */
    ncp_uint64_t    offset64,       /* IN: Node/target offset */
    ncp_fill_t     *ncp_fill_p,     /* IN: pointer to fill command buffer */
    ncp_uint32_t    flags);         /* IN: Operational control flags */

NCP_API ncp_st_t
ncp_read_modify_write(
    ncp_dev_hdl_t   devHdl,         /* IN: Device handle */
    ncp_region_id_t regionId,       /* IN: Node/target address */
    ncp_uint64_t    offset64,       /* IN: Node/target offset */
    ncp_rmw_t      *ncp_rmw_p,      /* IN: pointer to RMW structure */
    ncp_uint32_t    flags);         /* IN: Operational control flags */

NCP_API ncp_st_t
ncp_scatter_write(
    ncp_dev_hdl_t   devHdl,         /* IN: Device handle */
    ncp_region_id_t regionId,       /* IN: Node/target address */
    ncp_crsw_t     *crsw_p,         /* IN: pointer to CRSW structure */
    ncp_uint32_t    flags);         /* IN: Operational control flags */

NCP_API ncp_st_t
ncp_broadcast_block_write(
    ncp_dev_hdl_t   devHdl,         /* IN: Device handle */
    ncp_region_id_t regionId,       /* IN: Node/target address */
    ncp_uint64_t    offset64,       /* IN: Node/target offset */
    ncp_crbbw_t    *crbbw_p,        /* IN: pointer to CRBBW structure */
    ncp_uint32_t    flags);         /* IN: Operational control flags */

NCP_API ncp_st_t
ncp_broadcast_scatter_write(
    ncp_dev_hdl_t   devHdl,         /* IN: Device handle */
    ncp_region_id_t regionId,       /* IN: Node/target address */
    ncp_crbsw_t    *crbsw_p,        /* IN: pointer to CRBSW structure */
    ncp_uint32_t    flags);         /* IN: Operational control flags */

NCP_API ncp_st_t
ncp_broadcast_block_fill(
    ncp_dev_hdl_t   devHdl,         /* IN: Device handle */
    ncp_region_id_t regionId,       /* IN: Node/target address */
    ncp_uint64_t    offset64,       /* IN: Node/target offset */
    ncp_fill_t     *ncp_fill_p,     /* IN: pointer to ncp_fill_t structure */
    ncp_uint32_t    flags);         /* IN: Operational control flags */

NCP_API ncp_st_t
ncp_coherent_sysmem_read(
    ncp_dev_hdl_t   devHdl,         /* IN: Device handle */
    ncp_region_id_t regionId,       /* IN: Engine Node/target */
    ncp_uint64_t    address,        /* IN: sysmem address */
    ncp_uint8_t    *buffer,         /* IN: pointer read data */
    ncp_uint32_t    count,          /* IN: sizeof read data */
    ncp_uint32_t    xferWidth,      /* IN: xferWidth in bytes */
    ncp_uint32_t    flags);         /* IN: Operational control flags */

NCP_API ncp_st_t
ncp_coherent_sysmem_write(
    ncp_dev_hdl_t   devHdl,         /* IN: Device handle */
    ncp_region_id_t regionId,       /* IN: Engine Node/target */
    ncp_uint64_t    offset64,       /* IN: sysmem address */
    ncp_uint8_t    *buffer,         /* IN: pointer to write data */
    ncp_uint32_t    count,          /* IN: sizeof ncp_fill_t buffer */
    ncp_uint32_t    xferWidth,      /* IN: xferWidth in bytes */
    ncp_uint32_t    flags);         /* IN: Operational control flags */

NCP_API ncp_st_t
ncp_mdio_read(
    ncp_dev_hdl_t   devHdl,         /* IN: Device handle */
    ncp_region_id_t regionId,       /* IN: Engine Node/target */
    ncp_uint64_t    offset,         /* IN: register/device number */
    ncp_uint32_t   *buffer,         /* IN: pointer to read data */
    ncp_uint32_t    count,          /* IN: sizeof read data */
    ncp_uint32_t    flags);         /* IN: Operational control flags */

NCP_API ncp_st_t
ncp_mdio_write(
    ncp_dev_hdl_t   devHdl,         /* IN: Device handle */
    ncp_region_id_t regionId,       /* IN: Engine Node/target */
    ncp_uint64_t    offset,         /* IN: register/device number */
    ncp_uint32_t   *buffer,         /* IN: pointer to write data */
    ncp_uint32_t    count,          /* IN: sizeof read data */
    ncp_uint32_t    flags);         /* IN: Operational control flags */

NCP_API void
ncp_comment( const char *msg);

NCP_API void *ncpHwioTraceFuncArg;
NCP_API ncp_hwio_trace_func_t ncpHwioTraceFunc;

NCP_API ncp_dev_hdl_t ncp_dev_hdls[NCP_MAX_DEVS];
NCP_API ncp_uint8_t ncp_dev_hdl_users[NCP_MAX_DEVS];
NCP_API ncp_hdl_t **ncp_hdls;
NCP_API ncp_bool_t ncp_dev_initialized;

#if defined (_MSC_VER)
#define NCP_COMMENT( format, ... )          \
    do {                                        \
        char log_msg[128];                      \
        snprintf(log_msg, 128, format, __VA_ARGS__); \
        ncp_comment( log_msg );                 \
    } while( 0 );
#else
#define NCP_COMMENT( format, args... )          \
    do {                                        \
        char log_msg[128];                      \
        snprintf(log_msg, 128, format, ##args); \
        ncp_comment( log_msg );                 \
    } while( 0 );
#endif



/***************************************************************************
* Utility Functions                                                        *
***************************************************************************/

NCP_API ncp_st_t ncp_validate_handle(
    ncp_t *ncp);

NCP_API ncp_st_t ncp_config_dev_open(
    ncp_t *ncp,
    ncp_dev_hdl_t *dev);

NCP_API ncp_st_t ncp_config_dev_close(ncp_t *ncp);

NCP_API ncp_st_t ncp_hdls_init(ncp_bool_t);

NCP_API ncp_uint32_t ncp_ns_to_clk(
    ncp_uint32_t clk_in_mhz,
    ncp_uint32_t num_ns);

NCP_API ncp_st_t ncp_encode_ipchecksum_options(
    ncp_rev_id_t    rev,
    ncp_map_t      *map,
    ncp_uint32_t   *options,
    ncp_uint32_t   *invalidTcpFlagsHigh,          /* aka tcpflags00 */
    ncp_uint32_t   *invalidTcpFlagsLow,           /* aka tcpflags01 */
    ncp_uint32_t   *l3PassFailCriteria);

NCP_API const char *
ncp_release_id(void);

#include "uboot/ncp_config_pvt.h"

#ifdef __cplusplus
}
#endif

#endif /* __NCP_PVT_H__ */
