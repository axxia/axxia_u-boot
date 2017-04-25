/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


#ifndef _NCP_DEV_CONFIG_REG_DEFINES_H_
#define _NCP_DEV_CONFIG_REG_DEFINES_H_

#ifdef __cplusplus
extern "C" {
#endif

    /* NODE 0x300  TARGET 0x00 : NCP_REGION_SIMULATOR_IF */
#define  NCP_DEV_SIM_IF_SIM_REG                       (0x00000000)
#define  NCP_DEV_SIM_IF_RTE_REG                       (0x00000004)
#define  NCP_DEV_SIM_IF_PPC_REG                       (0x00000008)
#define  NCP_DEV_SIM_IF_DBG_REG                       (0x0000000C)
#define  NCP_DEV_SIM_IF_SIM_VERSION                   (0x00000010)
#define  NCP_DEV_SIM_IF_ZERO_FILL_AMSB                (0x00000020)
#define  NCP_DEV_SIM_IF_ZERO_FILL_ALSB                (0x00000024)
#define  NCP_DEV_SIM_IF_ZERO_FILL_SIZE                (0x00000028)

     

    /* NODE 0x301  TARGET 0x 0 : NCP_REGION_DRIVER_CFG */

#define  NCP_DEV_CFG_REVISION_ID                      (0x00000000)
#define  NCP_DEV_CFG_BUS_ADAPTOR                      (0x00000004)
#define  NCP_DEV_CFG_TRACE_LEVEL                      (0x00000008)
#define  NCP_DEV_CFG_DMA_ENABLED                      (0x0000000C)
#define  NCP_DEV_CFG_DMA_THLD                         (0x00000010)
#define  NCP_DEV_CFG_PLL_INIT_DISABLE                 (0x00000014)
#define  NCP_DEV_CFG_SYSMEM_INIT_DISABLE              (0x00000018)
#define  NCP_DEV_CFG_CPCQ_TIMEOUT_MS                  (0x0000001c)
#define  NCP_DEV_CFG_SCRATCH                          (0x00000020)
#define  NCP_DEV_CFG_IMC_WORKAROUND_CTL               (0x00000024)

#define  NCP_DOMAIN_ID                                (0x00000028)
#define  NCP_DOMAIN_ID_VALID                          (0x0000002c)
#define  NCP_DOMAIN_LOCK_RETRY_CNT                    (0x00000030)
#define  NCP_DOMAIN_MEMORY_LAYOUT_CONTROL             (0x00000034)

/* memory layout for this domain */
#define  NCP_DOMAIN_LOCAL_NVM_BASE_ADDR               (0x00000040)
#define  NCP_DOMAIN_LOCAL_NVM_SIZE                    (0x00000044)
#define  NCP_DOMAIN_LOCAL_DMA_BASE_ADDR               (0x00000048)
#define  NCP_DOMAIN_LOCAL_DMA_SIZE                    (0x0000004c)
/* general memory access for any domain */
#define  NCP_DOMAIN_NVM_BASE_ADDR(n)                  (0x00000050 + (n * 0x10))
#define  NCP_DOMAIN_NVM_SIZE(n)                       (0x00000054 + (n * 0x10))
#define  NCP_DOMAIN_DMA_BASE_ADDR(n)                  (0x00000058 + (n * 0x10))
#define  NCP_DOMAIN_DMA_SIZE(n)                       (0x0000005c + (n * 0x10))
/* reserve offset 0x60-0xec for domains 1-3 */
#define  NCP_DOMAIN_CONFIG_0                          (0x00000050)
#define  NCP_DOMAIN_CONFIG_1                          (0x00000060)
#define  NCP_DOMAIN_CONFIG_2                          (0x00000070)
#define  NCP_DOMAIN_CONFIG_3                          (0x00000080)


    /* unused 0x90 - 0xdc */

#define NCP_DEV_ALARM_BITMASK(n)                      (0x000000e0 + (n * 4))
#define NCP_DEV_ALARM_BITMASK_0                       (0x000000e0)
#define NCP_DEV_ALARM_BITMASK_1                       (0x000000e4)
#define NCP_DEV_ALARM_BITMASK_2                       (0x000000e8)
#define NCP_DEV_ALARM_BITMASK_3                       (0x000000ec)
#define NCP_DEV_ALARM_BITMASK_4                       (0x000000f0)
#define NCP_DEV_ALARM_BITMASK_5                       (0x000000f4)
#define NCP_DEV_ALARM_BITMASK_6                       (0x000000f8)
#define NCP_DEV_ALARM_BITMASK_7                       (0x000000fc)
#define NCP_DEV_ALARM_BITMASK_8                       (0x00000100)
#define NCP_DEV_ALARM_BITMASK_9                       (0x00000104)
#define NCP_DEV_ALARM_BITMASK_10                      (0x00000108)
#define NCP_DEV_ALARM_BITMASK_11                      (0x0000010c)
#define NCP_DEV_ALARM_BITMASK_12                      (0x00000110)
#define NCP_DEV_ALARM_BITMASK_13                      (0x00000114)
#define NCP_DEV_ALARM_BITMASK_14                      (0x00000118)
#define NCP_DEV_ALARM_BITMASK_15                      (0x0000011c)

#define NCP_DEV_EVENT_DISPATCH                        (0x00000120)
#define     NCP_DEV_EVENT_DISPATCH_CFG_START              0x00000001
#define     NCP_DEV_EVENT_DISPATCH_CFG_COMPLETE           0x00000002
#define     NCP_DEV_EVENT_DISPATCH_CFG_DESTROY            0x00000004

/* reserve 124-12c */

#define NCP_DEV_LBI_ACCESS_TIMEOUT                    (0x00000130)
#define NCP_DEV_UBOOT_CMEM_INIT                       (0x00000134)
#if 0 /* TBD */
#define NCP_DEV_EIOA_INTR_FILTER_THRESHOLD            (0x00000138)
#define NCP_DEV_EIOA_LINK_MONITOR_TIMER_MS            (0x0000013c)
#define NCP_DEV_EIOA_TS_WA_DISABLE                    (0x00000140)
#endif
#define NCP_DEV_HSS_LOS_WA_SELECT                     (0x00000144)

    /*
typedef struct 
{
#ifdef NCP_BIG_ENDIAN
    unsigned isAsic          :  1;
    unsigned isFpga          :  1;
    unsigned isSim           :  1;
    unsigned useInterrupts   :  1;
    unsigned                 :  1;
    unsigned secDisable      :  1;
    unsigned sppDisable      :  1;
    unsigned cpuDisable      :  4;
    unsigned ecidChipType    :  5;
    unsigned                 :  1;
    unsigned packageType     :  4;
    unsigned chipVersion     :  3;
    unsigned chipVersionMinor:  3;
    unsigned chipType        :  5;
#else
    unsigned chipType        :  5;
    unsigned chipVersionMinor:  3;
    unsigned chipVersion     :  3;
    unsigned packageType     :  4;
    unsigned                 :  1;
    unsigned ecidChipType    :  5;
    unsigned cpuDisable      :  4;
    unsigned sppDisable      :  1;
    unsigned secDisable      :  1;
    unsigned                 :  1;
    unsigned useInterrupts   :  1;
    unsigned isSim           :  1;
    unsigned isFpga          :  1;
    unsigned isAsic          :  1;
#endif
} ncp_rev_id_t;
*/


typedef struct 
{
#ifdef NCP_BIG_ENDIAN
    unsigned timeout        : 8;
    unsigned retry          : 8;
    unsigned extraOff       : 8;
    unsigned                : 6;
    unsigned forceFixup     : 1;
    unsigned enable         : 1;
#else
    unsigned enable         : 1;
    unsigned forceFixup     : 1;
    unsigned                : 6;
    unsigned extraOff       : 8;
    unsigned retry          : 8;
    unsigned timeout        : 8;
#endif
} ncp_imc_wa_ctl_t;

typedef struct 
{
    ncp_uint32_t    nvmBaseAddr;
    ncp_uint32_t    nvmSize;
    ncp_uint32_t    dmaBaseAddr;
    ncp_uint32_t    dmaSize;
} ncp_domain_memory_layout_t;


/* 
 * --- NCP Device Config Structure --- 
 *  This is the C structure representation of the virtual 
 *  register space. A copy of this structure is malloced for
 *  each driver device instance (ncp_dev_t). 
 *
 *  User code can access any entry in this structure using
 *  the virtual registers defined above, whereas internally
 *  the driver can access the same value using this structure.
 */
typedef struct {
    ncp_rev_id_t        rev;
    ncp_uint32_t        busAdaptor;
    ncp_uint32_t        traceLevel;
    ncp_uint32_t        configDmaEnabled;
    ncp_uint32_t        configDmaThld;
    ncp_uint32_t        pllInitDisable;
    ncp_uint32_t        sysmemInitDisable;
    ncp_uint32_t        cpcqTimeoutMs;
    ncp_uint32_t        scratch;
    ncp_imc_wa_ctl_t    imc_wa_ctl;
    ncp_uint32_t        domainId;
    ncp_uint32_t        domainIdValid;
    ncp_uint32_t        domainLockRetryCnt;
    ncp_uint32_t        domainMemLayoutControl;
    ncp_uint32_t        reserved[2];
    ncp_domain_memory_layout_t  localDomainMem;
    ncp_domain_memory_layout_t  globalDomainMem[NCP_CFG_NUM_DOMAINS];
    ncp_uint32_t        reserved2[20];
    ncp_alarm_bitmask_t alarm;
    ncp_uint32_t        eventDispatch;
    ncp_uint32_t        reserved4[3];
    ncp_uint32_t        lbiAccessTimeoutCnt;
    ncp_uint32_t        ubootCmemInit;
    /* structure definition must match offsets. Gap of 3 is for eioaIntrFilterThreshold,
     * eioaLinkMonitorTimerMs, eioaTSWorkaroundDisable - all yet to be implemented */
    ncp_uint32_t        reserved5[3];
    ncp_uint32_t        hssLOSWorkaroundSelect;
} ncp_dev_config_t;


#ifdef __cplusplus
}
#endif

#endif /* _NCP_DEV_CONFIG_REG_DEFINES_H_ */
