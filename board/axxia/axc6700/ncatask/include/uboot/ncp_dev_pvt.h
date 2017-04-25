/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


#ifndef __NCP_DEV_PVT_H__
#define __NCP_DEV_PVT_H__

#include "uboot/ncp_sal.h"

#if defined ( NCP_KERNEL ) 


extern void acp_spin_lock_init(void *);
extern void acp_spin_lock(void *);
extern void acp_spin_unlock(void *);
extern void acp_spin_lock_bh(void *);
extern void acp_spin_unlock_bh(void *);
extern void acp_spin_lock_irqsave(void *, unsigned long);
extern void acp_spin_unlock_irqrestore(void *, unsigned long);

#endif

/* BEGIN: Important forward type references */

typedef struct ncp_region_io_s ncp_region_io_t;
typedef struct ncp_region_coh_io_s ncp_region_coh_io_t;
typedef struct ncp_dev_s       ncp_dev_t;
typedef struct ncp_dev_cpcq_s  ncp_dev_cpcq_t;

/* END:   Important forward type references */

#include "uboot/ncp.h"
#include "uboot/ncp_pvt.h"
#include "uboot/ncp_dev.h"
#include "uboot/ncp_ncav3.h"
#include "uboot/ncp_ncav3_qpm.h"
#include "uboot/ncp_dev_config_regs.h"


/* --- Linux References --- */
#define NCP_MOD_NAME        "ncp"

/* ---- Conditional Debug */
#undef NCP_NCA_DBG_BOTTOM_HALF

/* --- Module Parameters --- */
extern int ncp_devs_found;
extern int ncp_devs_configured;
extern int ncp_access_checking;
extern int ncp_scatter_checking;
extern unsigned int ncp_vendor_id;
extern unsigned int ncp_device_id;
extern int ncp_safe_mode;
extern int ncp_pio_write_delay;
extern int ncp_pio_read_delay;
extern ncp_bool_t nca_axi_lock_required;
extern ncp_bool_t nca_int_generation_bug;
extern ncp_bool_t nca_wait_timeout_required;
extern int ncp_dma_threshold;
/* Temporary! Allows RTE developers to override interrupts for debugging
 * purposes. */
extern int ncp_disable_interrupts;
extern int ncp_use_hard_irq;
/* I2C bus speed. default: 100 KHz
 400 KHz
*/
extern int ncp_i2c_bus_speed; 



extern int ncp_trace_level;

#if defined(NCP_DEV_SRIOEP)
extern int ncp_srio_root_regs_start;
extern int ncp_srio_root_regs_length;
extern int ncp_srio_debug;
#endif


extern int ncp_pka_in_fpga;

/*
 * NCAv3 has 64 queue groups (or TQSs) among the A53 cores.
 */

#define NCP_NCA_MAX_PCQ_GROUPS 64

#define NCP_DEV_ACCESS_NONE            (0x00)
#define NCP_DEV_ACCESS_READ            (0x01)
#define NCP_DEV_ACCESS_WRITE           (0x02)
#define NCP_DEV_ACCESS_RW              (0x03)
#define NCP_DEV_ACCESS_BIG_ENDIAN      (0x04)
#define NCP_DEV_ACCESS_LITTLE_ENDIAN   (0x08)
#define NCP_DEV_ACCESS_ENDIAN          (0x0c)
#define NCP_DEV_ACCESS_IO_SYNC         (0x10)
#define NCP_DEV_ACCESS_PAGED           (0x20)
#define NCP_DEV_ACCESS_8B_ONLY         (0x40)

#define NCP_DEV_PAGE_MAPPED           (0x0100)


/* --- Internal Types & Definitions --- */

#define NCP_DEV_TAG         (0x67103388)    /* TODO - need a real tag for NCP*/

#ifdef NCP_BIG_ENDIAN
#define NCP_HOST_TO_BUS16(n) \
         ((((ncp_uint16_t)(n) >>  8) & 0x00ff) |  \
          (((ncp_uint16_t)(n) <<  8) & 0xff00))

#define NCP_HOST_TO_BUS32(n) \
        ((((ncp_uint32_t)(n) >> 24) & 0x000000ff) |  \
         (((ncp_uint32_t)(n) >>  8) & 0x0000ff00) |  \
         (((ncp_uint32_t)(n) <<  8) & 0x00ff0000) |  \
         (((ncp_uint32_t)(n) << 24) & 0xff000000))

#else
#define NCP_HOST_TO_BUS16(n) (n)
#define NCP_HOST_TO_BUS32(n) (n)
#endif /* NCP_BIG_ENDIAN */

#define NCP_BUS_TO_HOST16(n) NCP_HOST_TO_BUS16(n)
#define NCP_BUS_TO_HOST32(n) NCP_HOST_TO_BUS32(n)


#define NCP_DEV_CACHE_LINE_SHIFT_BITS    (4)      /* 16 bytes */
#define NCP_DEV_CACHE_LINE_SIZE          ( 1 << NCP_DEV_CACHE_LINE_SHIFT_BITS)
#define NCP_DEV_CACHE_LINE_ALIGN_MASK    (NCP_DEV_CACHE_LINE_SIZE - 1)
#define NCP_DEV_CACHE_LINE_MASK          (~NCP_DEV_CACHE_LINE_ALIGN_MASK)


#define EXTERNAL_HOST  /* TODO: Should get this from configuration! */

#define NCP_DEV_CMEM_ZQ_TIMER_INTERVAL               100   /* ms */
#define NCP_DEV_CMEM_ZQ_MAX_POLL_TIME                5000  /* 5ms */
#define NCP_DEV_CMEM_ZQ_ITER_POLL_TIME               100   /* 100us */
#define NCP_DEV_CMEM_ZQ_POLL_ITERS  (NCP_DEV_CMEM_ZQ_MAX_POLL_TIME / NCP_DEV_CMEM_ZQ_ITER_POLL_TIME)
#define NCP_DEV_CMEM_DDR_ACTIVE                      0x2



/*
 * NCP direct paged access
 *
 */

enum {
    /* Raw BAR access pages */
    NCP_DEV_PAGE_PCIE0_BAR_0 = 0,
    NCP_DEV_PAGE_PCIE0_BAR_1,
    NCP_DEV_PAGE_PCIE0_BAR_2,
    NCP_DEV_PAGE_PCIE0_PEI,
    NCP_DEV_PAGE_PCIE0_AXI_SLV,
    NCP_DEV_PAGE_PCIE0_AXI_GPREG,
    NCP_DEV_PAGE_PCIE0_CC_GPREG,

    NCP_DEV_PAGE_PCIE1_BAR_0,
    NCP_DEV_PAGE_PCIE1_BAR_1,
    NCP_DEV_PAGE_PCIE1_BAR_2,
    NCP_DEV_PAGE_PCIE1_PEI,
    NCP_DEV_PAGE_PCIE1_AXI_SLV,
    NCP_DEV_PAGE_PCIE1_AXI_GPREG,
    NCP_DEV_PAGE_PCIE1_CC_GPREG,

    NCP_DEV_PAGE_PCIE2_BAR_0,
    NCP_DEV_PAGE_PCIE2_BAR_1,
    NCP_DEV_PAGE_PCIE2_BAR_2,
    NCP_DEV_PAGE_PCIE2_PEI,
    NCP_DEV_PAGE_PCIE2_AXI_SLV,
    NCP_DEV_PAGE_PCIE2_AXI_GPREG,
    NCP_DEV_PAGE_PCIE2_CC_GPREG,

    NCP_DEV_PAGE_SRIO_PIO_WIN_0,
    NCP_DEV_PAGE_SRIO_PIO_WIN_1,
    NCP_DEV_PAGE_SRIO_PIO_WIN_2,
    NCP_DEV_PAGE_SRIO_PIO_WIN_3,
    NCP_DEV_PAGE_SRIO_PIO_WIN_4,
    NCP_DEV_PAGE_SRIO_PIO_WIN_5,
    NCP_DEV_PAGE_SRIO_PIO_WIN_6,
    NCP_DEV_PAGE_SRIO_PIO_WIN_7,
    NCP_DEV_PAGE_SRIO_PIO_WIN_8,
    NCP_DEV_PAGE_SRIO_PIO_WIN_9,
    NCP_DEV_PAGE_SRIO_PIO_WIN_10,
    NCP_DEV_PAGE_SRIO_PIO_WIN_11,
    NCP_DEV_PAGE_SRIO_PIO_WIN_12,
    NCP_DEV_PAGE_SRIO_PIO_WIN_13,
    NCP_DEV_PAGE_SRIO_PIO_WIN_14,
    NCP_DEV_PAGE_SRIO_PIO_WIN_15,
    NCP_DEV_PAGE_SRIO_CFG_GRIO,
    NCP_DEV_PAGE_SRIO_CFG_RAB,
    NCP_DEV_PAGE_SRIO_AXI_SLV,

    /* do we really need all those PIO_WINs?? */
    NCP_DEV_PAGE_SRIO_1_CFG_GRIO,
    NCP_DEV_PAGE_SRIO_1_CFG_RAB,
    NCP_DEV_PAGE_SRIO_1_AXI_SLV,

    /* special regions */
    NCP_DEV_PAGE_DMA_MEM_LE,
    NCP_DEV_PAGE_DMA_MEM_BE,
    NCP_DEV_PAGE_TASK_MEM_LE,
    NCP_DEV_PAGE_TASK_MEM_BE,
    NCP_DEV_PAGE_PLB_SYSMEM,
    NCP_DEV_PAGE_PLB_SYSMEM_LE,
    NCP_DEV_PAGE_HOSTMEM_LE,
    NCP_DEV_PAGE_HOSTMEM_BE,

    NCP_DEV_PAGE_MPC_RIO_ENDPOINT,
    NCP_DEV_PAGE_MPC_RIO_MSG_UNIT,

    NCP_DEV_PAGE_SIMULATOR_IF,

    /* AXI address mappings */

    /* APB - not all exist on every chipType */
    NCP_DEV_PAGE_GPIO_0,
    NCP_DEV_PAGE_SSP,
    NCP_DEV_PAGE_SRIO_GPREG,
    NCP_DEV_PAGE_I2C,
    NCP_DEV_PAGE_UART_0,
    NCP_DEV_PAGE_TIMER,
    NCP_DEV_PAGE_MDIO,
    NCP_DEV_PAGE_APB2RC,
    NCP_DEV_PAGE_GPREG,

    NCP_DEV_PAGE_SRIO_CONF,
    NCP_DEV_PAGE_SRIO_1_CONF,
    NCP_DEV_PAGE_PL301_0_CONF,
    NCP_DEV_PAGE_PL301_1_CONF,
    NCP_DEV_PAGE_PL301_2_CONF,

    NCP_DEV_PAGE_SCB,
    NCP_DEV_PAGE_APB2SER,
    NCP_DEV_PAGE_TZC_0,
    NCP_DEV_PAGE_TZC_1,

    /* AHB */
    NCP_DEV_PAGE_NAND,
    NCP_DEV_PAGE_TRNG,
    NCP_DEV_PAGE_FEMAC,
    NCP_DEV_PAGE_USB,
    NCP_DEV_PAGE_GPDMA_0,
    NCP_DEV_PAGE_GPDMA_1,

    NCP_DEV_PAGE_MSD,
    NCP_DEV_PAGE_SBB,

    /* !!!! START OF AXI PERIPHERALS !!!! */
    NCP_DEV_PAGE_NCAV3_CMN,
    NCP_DEV_PAGE_NCAV3_QPM,
    NCP_DEV_PAGE_NCAV3_CORE,
    NCP_DEV_PAGE_NCAV3_DMM,
    NCP_DEV_PAGE_PKA,
    NCP_DEV_PAGE_ROM,
    NCP_DEV_PAGE_LCM,

    /* AXM5500 */
    NCP_DEV_PAGE_LSM,
    NCP_DEV_PAGE_MME_CONF,

    NCP_DEV_PAGE_XVRC,
    NCP_DEV_PAGE_SPF,
    NCP_DEV_PAGE_SYSCON,
    NCP_DEV_PAGE_X7_ECM,
    NCP_DEV_PAGE_IPI,
    NCP_DEV_PAGE_SMB,
    NCP_DEV_PAGE_MTC,
    NCP_DEV_PAGE_AXIS_GIC_CPU,
    NCP_DEV_PAGE_AXIS_GIC_DIST,
    NCP_DEV_PAGE_SEAHAWK_GIC,

    NCP_DEV_PAGE_APB2SER_PHY,
    NCP_DEV_PAGE_APB2SER_CPM,
    NCP_DEV_PAGE_APB2SER_CLK,

    NCP_DEV_PAGE_DICKENS,
    NCP_DEV_PAGE_M3SS,
    NCP_DEV_PAGE_STM,
    NCP_DEV_PAGE_CORESIGHT,

    /* AXM5600 */
    NCP_DEV_PAGE_AXI2SER4_CPM,
    NCP_DEV_PAGE_AXI2SER5,
    NCP_DEV_PAGE_AXI2SER6_USB,
    NCP_DEV_PAGE_AXI2SER7_ELM,

    /* Lionfish */
    NCP_DEV_PAGE_AW_LOCK,
    NCP_DEV_PAGE_FES,
    NCP_DEV_PAGE_AXI2SER8_NCAP,
    NCP_DEV_PAGE_AXI2SER9_CDC,
    NCP_DEV_PAGE_AXI2SER10_NLINK,
    NCP_DEV_PAGE_AXI2SER11,

    NCP_DEV_PAGE_SATA_CFG_0,
    NCP_DEV_PAGE_SATA_CFG_1,


    NCP_DEV_PAGE_AXI_MMAP_GPREG,
    NCP_DEV_PAGE_AXI_MMAP_SCB,
    NCP_DEV_PAGE_AXI_PERIPH_GPREG,
    NCP_DEV_PAGE_AXI_PERIPH_SCB,
    NCP_DEV_PAGE_AXI_PCI_GPREG,
    NCP_DEV_PAGE_AXI_PCI_SCB,
    NCP_DEV_PAGE_AXI_USB_GPREG,
    NCP_DEV_PAGE_AXI_USB_SCB,
    NCP_DEV_PAGE_USB_1,
    NCP_DEV_PAGE_AXI_USB_1_GPREG,
    NCP_DEV_PAGE_AXI_USB_1_SCB,

    NCP_DEV_PAGE_EAC,
    NCP_DEV_PAGE_FC,


    /* !!!! END OF TABLE MARKER */
    NCP_DEV_MAX_PAGES
};

typedef struct {
    ncp_uint32_t  pageId;
    char          *name;
} ncp_dev_page_name_t;


#define NCP_DEV_SRIO_NUM_PIO_WIN 16
#define NCP_DEV_PAGE_SRIO_PIO_WIN(n) (NCP_DEV_PAGE_SRIO_PIO_WIN_0 + n)


/*
 * the ppc476 simulator uses the top 256 bytes of NCA AXI register
 * space as our simulator control registers. We map this for all
 * platforms, on h/w these registers all read as 0.
 */
#define NCP_DEV_SIM_IF_REG_OFFSET 0x0001ff00


typedef struct {
    int          id;
    ncp_uint64_t busAddr; /* 38-bit AXI address */
    ncp_uint64_t size;
    ncp_uint32_t flags;
} ncp_dev_addr_map_t;

typedef struct {
    void *          addr;       /* CPU virtual address */
    ncp_uint64_t    axiAddr;    /* 38-bit AXI address  */
    ncp_uint64_t    size;
    ncp_uint32_t    flags;
    ncp_uint32_t    curBase;    /* currently mapped page base for dynamic mappings */
    ncp_uint32_t    extraData;  /* access-method specific */
    char           *name;
} ncp_dev_page_t;

typedef struct {
    ncp_dev_addr_map_t  *map;
    ncp_uint32_t        numPages;
    char                *name;
} ncp_dev_mappings_t;

typedef ncp_st_t (*ncp_dev_bus_dyn_page_map_fn_t) (
        ncp_uint32_t    devNum,
        ncp_uint32_t    pageBase,
        ncp_dev_page_t *page);


/* ============================================
 * New ISR specific-wakeup support - Common across all hw platforms and operating systems
 */

typedef ncp_uint32_t (*ncp_cfgDma_condition_met_fn_ptr_t)(
    ncp_dev_cpcq_t *pcq,
    ncp_uint16_t idx);

typedef struct ncp_cfgDma_condition_met_s {
     ncp_cfgDma_condition_met_fn_ptr_t conditionMetFn;
     ncp_dev_cpcq_t *pcq;
     ncp_uint16_t idx;
} ncp_cfgDma_condition_met_t;

typedef ncp_bool_t (*ncp_iTask_condition_met_fn_ptr_t)(
    ncp_uint32_t  tqsId,
    ncp_st_t     *pNcpStatus);

typedef struct ncp_iTask_condition_met_s {
     ncp_iTask_condition_met_fn_ptr_t  conditionMetFn;
     ncp_uint32_t                      tqsId;
     ncp_st_t                         *pNcpStatus;
} ncp_iTask_condition_met_t;

typedef ncp_bool_t (*ncp_oTask_condition_met_fn_ptr_t)(
    ncp_uint32_t  tqsId,
    ncp_uint32_t  queueId,
    ncp_st_t     *pNcpStatus);

typedef ncp_oTask_condition_met_fn_ptr_t ncp_tTask_condition_met_fn_ptr_t;

typedef struct ncp_oTask_condition_met_s {
    ncp_oTask_condition_met_fn_ptr_t conditionMetFn;
    ncp_uint32_t tqsId;
    ncp_uint32_t queueId;
    ncp_st_t    *pNcpStatus;
} ncp_oTask_condition_met_t;

typedef ncp_oTask_condition_met_t ncp_tTask_condition_met_t;

/*
 * Used *only* for cfgDma, iTask, oTask (55xx +) and cfgDma iTask, oTask, and tTask (34/35xx) ISR handling.
 */
typedef union ncp_isr_condition_test_u {
    ncp_iTask_condition_met_t  iTaskConditionMet;
    ncp_oTask_condition_met_t  oTaskConditionMet;
    ncp_tTask_condition_met_t  tTaskConditionMet;
    ncp_cfgDma_condition_met_t cfgDmaConditionMet;
} ncp_isr_condition_test_t;

/*
 * This is the structure that will be hung of the specific nca group interrupt.
 * The isr will run this list waking up only those threads whose wait condition has been satisfied.
 */
typedef struct ncp_task_isr_wait_object_s
{
    struct ncp_task_isr_wait_object_s  *pNextWaitObj;
    ncp_isr_condition_test_t           waitCondition;
    ncp_task_isr_wait_primitive_t      *pWaitPrimitive;
} ncp_task_isr_wait_object_t;


ncp_st_t
ncp_task_isr_event_freelist_init(ncp_task_isr_wait_object_t **pFreeListObjs, int num);

ncp_st_t
ncp_dev_enable_1shot_nca_rx_ints(
    ncp_dev_hdl_t                      devHdl,
    ncp_uint8_t                        tqsId,
    ncp_iTask_condition_met_fn_ptr_t   conditionMetFn,
    ncp_task_isr_wait_object_t       **ppWaitStruct,
    ncp_st_t                          *pNcpStatus);

ncp_st_t
ncp_dev_enable_1shot_nca_tx_ints(
    ncp_dev_hdl_t                      devHdl,
    ncp_uint8_t                        tqsId,
    ncp_oTask_condition_met_fn_ptr_t   conditionMetFn,
    ncp_uint32_t                       queueId,
    ncp_task_isr_wait_object_t       **ppWaitStruct,
    ncp_st_t                          *pNcpStatus);

ncp_st_t
ncp_dev_disable_1shot_nca_rx_ints(
    ncp_dev_hdl_t               devHdl,
    ncp_uint8_t                 tqsId,
    ncp_task_isr_wait_object_t *pWaitStruct);

ncp_st_t
ncp_dev_disable_1shot_nca_tx_ints(
    ncp_dev_hdl_t               devHdl,
    ncp_uint8_t                 tqsId,
    ncp_task_isr_wait_object_t *pWaitStruct);

ncp_st_t
ncp_dev_disable_1shot_nca_task_completion_ints(
    ncp_dev_hdl_t                devHdl,
    ncp_uint8_t                  tqsId,
    ncp_task_isr_wait_object_t *pWaitStruct);

#define NCP_TASK_ENABLE_1SHOT_RX_INTS( \
    _dev,            \
    _tqsId,          \
    _conditionMetFn, \
    _ppWaitStruct,   \
    _pNcpStatus)     \
ncp_dev_enable_1shot_nca_rx_ints( \
    _dev,            \
    _tqsId,          \
    _conditionMetFn, \
    _ppWaitStruct,   \
    _pNcpStatus)

#define NCP_TASK_ENABLE_1SHOT_TX_INTS( \
    _dev,            \
    _tqsId,          \
    _conditionMetFn, \
    _queueId,        \
    _ppWaitStruct,   \
    _pNcpStatus)     \
ncp_dev_enable_1shot_nca_tx_ints( \
    _dev,            \
    _tqsId,          \
    _conditionMetFn, \
    _queueId,        \
    _ppWaitStruct,   \
    _pNcpStatus)


#define NCP_TASK_DISABLE_1SHOT_RX_INTS(_dev, _grp, _pWaitObj) \
ncp_dev_disable_1shot_nca_rx_ints(_dev, _grp, _pWaitObj)

#define NCP_TASK_DISABLE_1SHOT_TX_INTS(_dev, _grp, _pWaitObj) \
ncp_dev_disable_1shot_nca_tx_ints(_dev, _grp, _pWaitObj)

/*
 * PRIVATE - Task ISR Wait Control
 */

void
ncp_task_isr_wakeup_all(ncp_task_isr_wait_object_t *waitListHead);

void
ncp_task_isr_free_all_waitObjs(ncp_task_isr_wait_object_t *objListHead);

void
ncp_task_isr_put_waitObj(ncp_task_isr_wait_object_t **pWaitListHead,
                       ncp_task_isr_wait_object_t *pWaitObj);

#define ncp_dev_isr_write32(d, r, o, v) ncp_dev_write32(d, r, o, v)
#define ncp_dev_isr_read32(d, r, o, v) ncp_dev_read32(d, r, o, v)

void
ncp_task_isr_get_waitObj(ncp_task_isr_wait_object_t **pWaitListHead,
                       ncp_task_isr_wait_object_t **pWaitObj);
void
ncp_task_isr_remove_waitObj(ncp_task_isr_wait_object_t **pWaitListHead,
                       ncp_task_isr_wait_object_t *pWaitObj);



/*
 * ISR Related Macros
 */
#if !defined(NCP_DEV_FBRS) && !defined(NCP_DEV_SOCKET) && !defined(NCP_DEV_FBDEV) && defined(NCP_KERNEL)
#define NCP_DEV_PWAITSTRUCT_DECL(_pWaitStruct) \
ncp_task_isr_wait_object_t *_pWaitStruct=NULL
#else
#define NCP_DEV_PWAITSTRUCT_DECL(_pWaitStruct)

enum irqreturn {
    IRQ_NONE        = (0 << 0),
    IRQ_HANDLED     = (1 << 0),
    IRQ_WAKE_THREAD     = (1 << 1),
};
typedef enum irqreturn irqreturn_t;
#endif

#ifndef NO_IRQ
#define NO_IRQ 0 /* Later versions of linux removed this constant and treat 0 as no irq */
#endif





/* ==============================================
 * End - For new ISR specific-wakeup support
 */

typedef struct {
    ncp_uint32_t dataBufferCount;
    ncp_uint32_t hdrCount;
    ncp_uint32_t unitSize;
    ncp_uint32_t statCount;
    ncp_uint32_t maxCmdXferCount;
} ncp_dev_cfg_cmd_var_t;


typedef void (*ncp_dev_cpcq_entry_put_fn_t) (
    struct ncp_dev_cpcq_s *pcq,
    ncp_uint16_t   *idx,
    ncp_uint32_t   *entry);

typedef void (*ncp_dev_cpcq_buffer_write_fn_t) (
        void *to,
        void *from,
        ncp_uint32_t size);

struct ncp_dev_cpcq_s {
    ncp_uint32_t  blockSize;
    ncp_uint32_t  nEntries;
    volatile ncp_uint16_t *producer_ptr;
    volatile ncp_uint16_t *consumer_ptr;
    ncp_uint32_t *baseCpuAddr;
    ncp_uint32_t *buffCpuAddr;
    ncp_uint64_t  buffBusAddr;
    ncp_uint8_t   buffShiftBits;
    ncp_uint8_t   grpId;
    ncp_bool_t    swap_desc;
    ncp_uint8_t   dba_mem_sel;
    ncp_uint16_t  ioCount;
    ncp_uint32_t  swTailIdx;
    ncp_uint32_t   *swState;
    ncp_dev_cpcq_entry_put_fn_t entryPutFn;
    ncp_dev_cpcq_buffer_write_fn_t bufferWriteFn;
    ncp_task_isr_wait_object_t  *cfgDmaWaitList;
    ncp_task_isr_wait_object_t  *free_cfgDmaWaitList;
};

#define  NCP_DEV_CPCQ_SWSTATE_DMA_COMPLETE           0xcccccccc
#define  NCP_DEV_CPCQ_SWSTATE_DMA_WRITE_PENDING      0x11111111
#define  NCP_DEV_CPCQ_SWSTATE_DMA_READ_PENDING       0xeeeeeeee
#define  NCP_DEV_CPCQ_SWSTATE_FREE                   0xffffffff

#define  NCP_DEV_CPCQ_INTR_INTVL   25

#define NCP_DEV_US_PER_MS   (1000)
#define NCP_DEV_IPCQ_DELAY_MS (10)
#define NCP_DEV_OPCQ_DELAY_MS (10)

#define NCP_DEV_CPCQ_DELAY_US (10)
#define NCP_DEV_CPCQ_MAX_XFER_SIZE          (65536)
#define NCP_DEV_CPCQ_MAX_XFER_COUNT         (NCP_DEV_CPCQ_MAX_XFER_SIZE / 4)
#define NCP_DEV_DMA_THRESHOLD                  (32)

#define NCP_DEV_PIO_DAT_REGS                  (128)
#define NCP_DEV_PIO_MAX_TRANSACTIONS           (64)
#define NCP_DEV_PIO_MAX_BCAST_TRANSACTIONS     (31)
#define NCP_DEV_CFG_NODE_LOCAL_TARGET         (255)

#define NCP_DEV_MAX_SW_FILL_SIZE            (65536)
#define NCP_DEV_MAX_HW_FILL_SIZE           (131072)

#define NCP_DEV_PIO_DELAY_MAX   (400000)

#if defined(NCP_DEV_FBDEV) || defined (NCP_TEMP_USE_APP_HW)
#define NCP_DEV_PIO_DELAY() (NCP_ST_SUCCESS)

#define NCP_DEV_DOMAIN_LOCK() (NCP_ST_SUCCESS)

#define NCP_DEV_DOMAIN_UNLOCK()
#define NCP_DEV_IRQ_DOMAIN_UNLOCK()

#define NCP_TIMER_EVENTS_PRESENT(_myDevHdl)     (1)
#define NCP_TIMER_CPU_TIMER_EXPIRED(_myLastSeq) (1)
#define NCP_SE_FEM_EVENTS_PRESENT(_myDevHdl)    (1)

#define NCP_DEV_NCA_CPCQ_IS_FULL(pcq) FALSE
#define NCP_DEV_NCA_CPCQ_IS_EMPTY(pcq) TRUE
#define NCP_DEV_NCA_CPCQ_IS_FULL_DELAY(dev, pcq, stat)
#define NCP_DEV_NCA_CPCQ_IS_EMPTY_DELAY(dev, pcq, stat)
#define NCP_DEV_NCA_PCQ_IDX_DECREMENT(pcq, idx)

#else
#define NCP_DEV_PIO_DELAY() ({ \
        ncp_st_t _st = NCP_ST_SUCCESS; \
        ncp_uint32_t _reg32_; \
        volatile ncp_ncap_cfg_pio_cdr0_reg_t * _cdr0_ = (ncp_ncap_cfg_pio_cdr0_reg_t *)&_reg32_; \
        int _pioDelay_ = NCP_DEV_PIO_DELAY_MAX; \
        while (_pioDelay_) { \
            _reg32_ = NCP_DEV_BUS_READ32( \
                  dev, NCP_DEV_PAGE_NCAV3_CMN, NCP_CMN_AXI_CFG_PIO_CDR0); \
            if (_cdr0_->start_done == 0) { \
                if ((_reg32_ != 0) && (_cdr0_->status != 3)) { \
                    _st = ncp_dev_pio_error(dev); \
                   if (_st == NCP_ST_SUCCESS) _st = NCP_ST_DEV_PIO_FAILED; \
                   break; \
                } \
                break; \
            } \
            if (_reg32_ == 0xffffffff) { \
                _st = NCP_ST_DEV_IO_ERROR; \
                break; \
            } \
            if (--_pioDelay_ == 0) { \
                _st = NCP_ST_DEV_PIO_SW_TIMEOUT; \
                break; \
            } \
        } \
_st; \
})

#define NCP_DEV_DOMAIN_LOCK() ({                                   \
    ncp_st_t _st = NCP_ST_SUCCESS;                                                           \
    ncp_uint32_t __nloops = 0;                                  \
    ncp_uint32_t domLockReg;                                    \
    domLockReg = NCP_DEV_BUS_READ32( dev, NCP_DEV_PAGE_NCAV3_CMN,     \
                NCP_CMN_AXI_NCA_PIO_LOCK(dev->config->domainId));       \
    while (domLockReg != 0)                                     \
    {                                                           \
        if (__nloops++ >= dev->config->domainLockRetryCnt) {    \
            _st = NCP_ST_DEV_DOMAIN_LOCK_TIMEOUT;                \
            break; \
        }                                                       \
        domLockReg = NCP_DEV_BUS_READ32( dev, NCP_DEV_PAGE_NCAV3_CMN, \
                NCP_CMN_AXI_NCA_PIO_LOCK(dev->config->domainId));       \
    }                                                           \
_st; \
})

#define NCP_DEV_IRQ_DOMAIN_UNLOCK()
#define NCP_DEV_DOMAIN_UNLOCK()                                 \
{                                                               \
    NCP_DEV_BUS_WRITE32( dev, NCP_DEV_PAGE_NCAV3_CMN,                 \
            NCP_CMN_AXI_NCA_PIO_LOCK(dev->config->domainId), 0);         \
}

#define NCP_DEV_NCA_CPCQ_BUFFER_CPU_ADDR(pcq, idx) \
    ( (void *) (pcq)->buffCpuAddr + ( (idx) * (pcq)->blockSize))


/*
 * Is the PCQ full?
 */

#define NCP_DEV_NCA_CPCQ_PROD_IDX(pcq) \
     (pcq->swap_desc) ? NCP_ENDIAN_SWAP_16(*(pcq)->producer_ptr) : (*(pcq)->producer_ptr);

#define NCP_DEV_NCA_CPCQ_CONS_IDX(pcq) \
     (pcq->swap_desc) ? NCP_ENDIAN_SWAP_16(*(pcq)->consumer_ptr) : (*(pcq)->consumer_ptr);



#define NCP_DEV_NCA_CPCQ_IS_FULL(pcq)                                        \
    ({                                                                       \
         ncp_uint16_t prod, consumer;                                        \
         prod = NCP_DEV_NCA_CPCQ_PROD_IDX(pcq);                              \
         consumer = NCP_DEV_NCA_CPCQ_CONS_IDX(pcq);                          \
         (((( prod + 1) & (pcq->nEntries - 1)) == consumer) ? TRUE : FALSE); \
     })

/*
 * Is the PCQ empty?
 *
 * For PCQ empty we are just checking if (producer == consumer).
 * If the queue is empty this will be true regardless of whether
 * the values are swapped or not. So we don't bother swapping.
 */

#define NCP_DEV_NCA_CPCQ_IS_EMPTY(pcq)                \
    ({                                                \
         ncp_uint16_t prod, consumer;                 \
         prod = (*(pcq)->producer_ptr);               \
         consumer = (*(pcq)->consumer_ptr);           \
         ((prod == consumer) ? TRUE : FALSE);         \
     })


/*
 * advance non-consumer/producer mirror index using num PCQ entries as water mark
 */

#define NCP_DEV_NCA_PCQ_IDX_ADVANCE(pcq, idx) \
    {                                         \
        if ((idx) == (pcq->nEntries - 1))     \
            (idx) = 0;                        \
        else                                  \
            (idx)+=1;                         \
    }

#define NCP_DEV_NCA_PCQ_IDX_DECREMENT(pcq, idx) \
    {                                           \
        if ((idx) == 0)                         \
            (idx) = (pcq->nEntries - 1);        \
        else                                    \
            (idx)-=1;                           \
    }


#define NCP_DEV_NCA_PCQ_IDX_PUT(pcq, idx)                            \
    {                                                                \
        NCP_SYSMEM_BARRIER();                                        \
        if (pcq->swap_desc) {                                        \
            *pcq->producer_ptr = NCP_ENDIAN_SWAP_16(idx);            \
        } else {                                                     \
            *pcq->producer_ptr = idx;                                \
        }                                                            \
    }



#ifdef NCP_DEV_SOCKET
#define NCP_DEV_NCA_CPCQ_IS_FULL_DELAY(dev, pcq, stat)
#define NCP_DEV_NCA_CPCQ_IS_EMPTY_DELAY(dev, pcq, stat)
#else
#define NCP_DEV_NCA_CPCQ_IS_FULL_DELAY(dev, pcq, stat)          \
    {                                                           \
        ncp_uint32_t waitCount = 0;                             \
        while (NCP_DEV_NCA_CPCQ_IS_FULL(pcq))                   \
        {                                                       \
            /* TODO: This should wait on an interrupt event */  \
            ncp_usleep(NCP_DEV_CPCQ_DELAY_US);                  \
            NCP_DEV_BUS_READ32(dev, NCP_DEV_PAGE_SIMULATOR_IF, 0x10); \
            dev->stats.dma_io##stat##_delay_cnt++;              \
            if (++waitCount == dev->config->cpcqTimeoutMs)      \
            {                                                   \
                NCP_TRACEPOINT(Intel_AXXIA_ncp_dev,             \
                               ncp_xlf_dev_nca_cpcq_is_full_delay_cpcqTimeout, \
                               NCP_MSG_ERROR, "cPCQ timeout\n");       \
                NCP_CALL(NCP_ST_DEV_PCQ_TIMEOUT);               \
            }                                                   \
        }                                                       \
    }

#define NCP_DEV_NCA_CPCQ_IS_EMPTY_DELAY(dev, pcq, stat)         \
    {                                                           \
        ncp_uint32_t waitCount = 0;                             \
                                                                \
        for (waitCount = 0; waitCount < dev->config->cpcqTimeoutMs; \
             waitCount++)                                       \
        {                                                       \
            if (NCP_DEV_NCA_CPCQ_IS_EMPTY(pcq) == TRUE)         \
            {                                                   \
                break;                                          \
            }                                                   \
            ncp_usleep(NCP_DEV_CPCQ_DELAY_US);                  \
            NCP_DEV_BUS_READ32(dev, NCP_DEV_PAGE_SIMULATOR_IF, 0x10); \
            dev->stats.dma_io##stat##_delay_cnt++;              \
        }                                                       \
                                                                \
        if (NCP_DEV_NCA_CPCQ_IS_EMPTY(pcq) == FALSE)            \
        {                                                       \
            NCP_TRACEPOINT(Intel_AXXIA_ncp_dev,                 \
                           ncp_xlf_dev_nca_cpcq_is_empty_delay_cpcqTimeout, \
                           NCP_MSG_ERROR, "cPCQ timeout\n");    \
            NCP_CALL(NCP_ST_DEV_PCQ_TIMEOUT);                   \
        }                                                       \
    }
#endif


#define NCP_SE_FEM_EVENTS_PRESENT(_myDevHdl) \
    ({ \
    ncp_seng_event_q_wr_ptr_r_t _myFemWrPtr;  \
    ncp_seng_event_q_rd_ptr_r_t _myFemRdPtr; \
    ncp_seng_event_q_size_r_t _myFemQSize; \
    ncp_uint32_t _myQWrPtr = 0; \
    ncp_uint32_t _myQRdPtr = 0; \
    ncp_uint32_t _myQSize = 0; \
    ncp_bool_t _myQWrWrap = FALSE; \
    ncp_bool_t _myQRdWrap = FALSE; \
    ncp_bool_t _myEventsOnQueue; \
    void *_myU32Valp; \
    \
    _myU32Valp = &(_myFemQSize);       \
    NCP_CALL(ncp_dev_read32(_myDevHdl, \
                            NCP_REGION_MPP_SENG, \
                            NCP_SENG_EVENT_Q_SIZE, \
                            (ncp_uint32_t *)(_myU32Valp)));     \
    _myQSize = _myFemQSize.size; \
    _myU32Valp = &(_myFemWrPtr);       \
    NCP_CALL(ncp_dev_read32(_myDevHdl, \
                            NCP_REGION_MPP_SENG, \
                            NCP_SENG_EVENT_Q_WR_PTR, \
                            (ncp_uint32_t *)(_myU32Valp)));     \
    _myQWrPtr = _myFemWrPtr.write_ptr; \
    _myQWrWrap = _myFemWrPtr.write_wrap; \
    \
    _myU32Valp = &_myFemRdPtr; \
    NCP_CALL(ncp_dev_read32(_myDevHdl, \
                            NCP_REGION_MPP_SENG, \
                            NCP_SENG_EVENT_Q_RD_PTR, \
                            (ncp_uint32_t *)(_myU32Valp))); \
    _myQRdPtr = _myFemRdPtr.read_ptr; \
    _myQRdWrap = _myFemRdPtr.read_wrap; \
    if ( _myQWrWrap == _myQRdWrap)      \
    { \
        NCP_ASSERT( ( _myQWrPtr >= _myQRdPtr), NCP_ST_SE_INVALID_FEM_POINTER); \
        _myEventsOnQueue =  ( (_myQWrPtr - _myQRdPtr) != 0); \
    } else \
    { \
        NCP_ASSERT( ( _myQWrPtr <= _myQRdPtr), NCP_ST_SE_INVALID_FEM_POINTER); \
        _myEventsOnQueue = ( (_myQSize + _myQWrPtr - _myQRdPtr) != 0); \
    } \
    _myEventsOnQueue; \
    })

#define NCP_TIMER_EVENTS_PRESENT(_myDevHdl) \
    ({ \
    void *_myU32Valp; \
    ncp_uint32_t _myIruptStatus7 = 0; \
    ncp_bool_t _myEventPresent = FALSE; \
    \
    _myU32Valp = &(_myIruptStatus7);       \
    NCP_CALL(ncp_dev_read32(_myDevHdl, \
                            NCP_REGION_TIMER_TIMER_CORE, \
                            NCP_TIMER_CORE_INTERRUPT_STATUS7, \
                            (ncp_uint32_t *)(_myU32Valp)));     \
    if ( _myIruptStatus7 & NCP_TIMER_EVENT_INTR_MASK) \
    { \
        _myEventPresent = TRUE; \
    } else \
    { \
        _myEventPresent = FALSE; \
    } \
    _myEventPresent; \
    })

#define NCP_TIMER_CPU_TIMER_EXPIRED(_myLastSeq)        \
    ({ \
    (_myLastSeq < dev->cpuIsrSeq[timerIndex]);  \
    })

#endif


/*
 * common ncaV2 interrupt types
 */
typedef enum {
NCA_GRP_INTR_ITASK_ARRIVAL=1,
NCA_GRP_INTR_OPCQ_COMPLETE,
NCA_GRP_INTR_CPCQ_COMPLETE,
} ncp_dev_nca_intr_types_t;


/* NCA V1 Interrupt bit definitions */
/* ===================================================== */
/*
 * Setup some convenient masks
 */


#define NCP_SE_FEM_EVENT_INTR_MASK            0x1

#define NCP_TIMER_EVENT_INTR_MASK             0x200


#define NCP_NCA_INTR_SRC_COOKIE 0xABCD7777


/* --- NCP Device Interrupt Structure ---       */
/* --- Contains isr status snapshot for use by bottom half */

typedef struct ncp_dev_nca_isr_common_s {
    ncp_uint32_t devNum;
    ncp_uint32_t thisTQS;
    void         *pIsrInfoOSspecific; /* reverse pointer to base edev struct */

    /* linked list of waiters,  all to be awakened when interrupt occurs */
    ncp_bool_t                  waitListsInitialized;

    ncp_isr_spinlock_t          iPCQISRLock;
    ncp_task_isr_wait_object_t *iPCQWaitList;

    ncp_isr_spinlock_t          oPCQISRLock;
    ncp_task_isr_wait_object_t *oPCQWaitList;

    /* available wait objects - dynamically managed */
    ncp_task_isr_wait_object_t *freeoPCQWaitList;
    ncp_task_isr_wait_object_t *freeiPCQWaitList;

    /* Runtime control, stats, and flags */
    ncp_bool_t stop;

    /* ISR Control and state */
#ifdef NCP_KERNEL
    ncp_uint32_t asyncRxIntEnabCnt;
    ncp_uint32_t rxIntEnabCnt;

    ncp_uint32_t txIntEnabCnt;

    volatile ncp_bool_t   WFI_waitInprogress;
#endif

    /* Statistics */
    ncp_uint32_t numiPCQInts;
    ncp_uint32_t numoPCQInts;
    ncp_uint32_t numInterrupts;

} ncp_dev_nca_isr_common_t;


extern void ncp_dev_sched_async_rx_callback(ncp_dev_nca_isr_common_t *pIsrCommon);

irqreturn_t  ncp_dev_intr_gic(int irq, void *intrSrc);

extern void ncp_dev_timer_intr(void *intrSrc);

#define NCP_DEV_XLF_DRAM_MAX_ADDR  (0x4000000000ULL)


#define NCP_TIMER_MAX_POLL_TIME                10000 /* 10ms */
#define NCP_TIMER_ITER_POLL_TIME               1000  /* 1ms */
#define NCP_TIMER_NUM_POLL_ITERS  (NCP_TIMER_MAX_POLL_TIME / NCP_TIMER_ITER_POLL_TIME)

/*!
 * @fn ncp_st_t ncp_dev_timer_sync_external( ncp_dev_hdl_t devHdl);
 * @brief This function syncs the external clock to the Nuevo TS
 * @param devHdl     IN: Device handle
 */
ncp_st_t ncp_dev_timer_sync_external(ncp_dev_hdl_t devHdl);

#define NCP_DEV_BUS_ADDR(dev, pageId, offset) \
        ((dev)->pages[pageId].addr + offset)

#define NCP_DEV_PAGE_FLAGS(dev, pageId) (dev->pages[pageId].flags)

#define NCP_DEV_PAGE_FLAGS_NATIVE_ENDIAN(dev) \
    (dev->hostEndian == cBigEndian) ? NCP_DEV_ACCESS_BIG_ENDIAN : NCP_DEV_ACCESS_LITTLE_ENDIAN

#define NCP_DEV_PAGE_FLAGS_SWAPPED_ENDIAN(dev) \
    (dev->hostEndian == cBigEndian) ? NCP_DEV_ACCESS_LITTLE_ENDIAN : NCP_DEV_ACCESS_BIG_ENDIAN

/*
 * wakeup types
 */

enum {
    NCP_NCA_RX_INTR_WAITERS = 0,
    NCP_NCA_RX_INTR_ASYNC_WAITERS, /* <- will sched rx callback */
    NCP_NCA_TX_INTR_WAITERS,
    NCP_NCA_TCOMP_INTR_WAITERS,
    NCP_NCA_CPCQ_INTR_WAITERS
};

#define NCP_DEV_INIT_ISR_INFO(_devNUM, _grp, _intrData) \
    NCP_INIT_ISR_INFO(_devNUM, _grp, (_intrData))

#define NCP_DEV_CLEANUP_ISR_INFO(_devNum) \
    NCP_CLEANUP_ISR_INFO(_devNum)

/*
 * Basic i/o methods
 * Note that FBRS has it's own implementation of these defined
 * in ncp_dev_fbrs.h
 */

#if !defined (NCP_DEV_FBRS) && !defined (NCP_DEV_SOCKET)

#ifdef DEBUG_EDEV_IO
#define NCP_WRITE_LOG(ctx, dev, pageId, offset, value) \
    do { \
        NCP_TRACEPOINT(Intel_AXXIA_ncp_dev, ncp_xlf_dev_write_log, NCP_MSG_DEBUG_IO, \
            "%s: pageId=0x%x offset=0x%x addr=0x%x value=0x%02x\n", \
            ctx, pageId, offset, NCP_DEV_BUS_ADDR(dev, pageId, offset), value); \
    } while (0)
#else
#define NCP_WRITE_LOG(ctx, dev, pageId, offset, value)
#endif

#define NCP_DEV_BUS_READ8(dev, pageId, offset) \
        NCP_BUS_READ8(NCP_DEV_BUS_ADDR(dev, pageId, offset))

#define NCP_DEV_BUS_READ16(dev, pageId, offset) \
        NCP_BUS_READ16(NCP_DEV_BUS_ADDR(dev, pageId, offset),\
                NCP_DEV_PAGE_FLAGS(dev, pageId))

#define NCP_DEV_BUS_READ32_UNLOCKED(dev, pageId, offset) \
    ( { \
        unsigned long __val32; \
        __val32 = NCP_BUS_READ32(NCP_DEV_BUS_ADDR(dev, pageId, offset),\
                NCP_DEV_PAGE_FLAGS(dev, pageId)); \
      __val32; \
      } )

#ifdef NCP_KERNEL
#define NCP_DEV_BUS_READ32(dev, pageId, offset) \
    ( { \
        unsigned long __val32; \
        unsigned long _flags; \
        if ((FALSE == nca_axi_lock_required) ||                          \
            (pageId != NCP_DEV_PAGE_NCAV3_CMN))                                \
        {                                                                \
            __val32 = NCP_BUS_READ32(NCP_DEV_BUS_ADDR(dev, pageId, offset), \
                    NCP_DEV_PAGE_FLAGS(dev, pageId));                       \
        }                                                                   \
        else                                                                \
        {                                                                   \
            raw_spin_lock_irqsave(&dev->ncaAccessLock,         \
                                               _flags);                     \
            __val32 = NCP_BUS_READ32(NCP_DEV_BUS_ADDR(dev, pageId, offset), \
                    NCP_DEV_PAGE_FLAGS(dev, pageId));                       \
            raw_spin_unlock_irqrestore(&dev->ncaAccessLock,          \
                                               _flags);                     \
        }                                                                   \
      __val32;                                                              \
      } )
#else
#define NCP_DEV_BUS_READ32(dev, pageId, offset) \
    NCP_DEV_BUS_READ32_UNLOCKED((dev), (pageId), (offset))
#endif

#define NCP_DEV_BUS_WRITE8(dev, pageId, offset, value) \
    do { \
        NCP_WRITE_LOG("edev_bus_write8", dev, pageId, offset, value); \
        NCP_BUS_WRITE8( \
                NCP_DEV_BUS_ADDR(dev, pageId, offset), value); \
        if (NCP_DEV_PAGE_FLAGS(dev, pageId) & NCP_DEV_ACCESS_IO_SYNC) { \
             NCP_BUS_READ32( NCP_DEV_BUS_ADDR(dev, NCP_DEV_PAGE_PCIE0_PEI, NCP_PEI_CONFIG), \
                    NCP_DEV_ACCESS_LITTLE_ENDIAN); \
        } \
    } while (0);

#define NCP_DEV_BUS_WRITE16(dev, pageId, offset, value) \
    do { \
        NCP_WRITE_LOG("edev_bus_write16", dev, pageId, offset, value); \
        NCP_BUS_WRITE16( \
                NCP_DEV_BUS_ADDR(dev, pageId, offset), value); \
        if (NCP_DEV_PAGE_FLAGS(dev, pageId) & NCP_DEV_ACCESS_IO_SYNC) { \
             NCP_BUS_READ32( NCP_DEV_BUS_ADDR(dev, NCP_DEV_PAGE_PCIE0_PEI, NCP_PEI_CONFIG), \
                    NCP_DEV_ACCESS_LITTLE_ENDIAN); \
        } \
    } while (0);


#define NCP_DEV_BUS_WRITE32_UNLOCKED(dev, pageId, offset, value) \
    do { \
        NCP_WRITE_LOG("edev_bus_write32", dev, pageId, offset, value); \
        NCP_BUS_WRITE32(                       \
            NCP_DEV_BUS_ADDR(dev, pageId, offset),  \
            value,                                  \
            NCP_DEV_PAGE_FLAGS(dev, pageId));       \
        if (NCP_DEV_PAGE_FLAGS(dev, pageId) & NCP_DEV_ACCESS_IO_SYNC) { \
            NCP_BUS_READ32( NCP_DEV_BUS_ADDR(dev, NCP_DEV_PAGE_PCIE0_PEI, NCP_PEI_CONFIG), \
                    NCP_DEV_ACCESS_LITTLE_ENDIAN); \
        } \
    } while (0);

#ifdef NCP_KERNEL
#define NCP_DEV_BUS_WRITE32(dev, pageId, offset, value) \
    do { \
        unsigned long _flags; \
        NCP_WRITE_LOG("edev_bus_write32", dev, pageId, offset, value); \
        if ((FALSE == nca_axi_lock_required) ||                        \
            (pageId != NCP_DEV_PAGE_NCAV3_CMN))                              \
        {                                               \
            NCP_BUS_WRITE32(                            \
                NCP_DEV_BUS_ADDR(dev, pageId, offset),  \
                value,                                  \
                NCP_DEV_PAGE_FLAGS(dev, pageId));       \
        }                                               \
        else                                            \
        {                                               \
            raw_spin_lock_irqsave(&dev->ncaAccessLock, _flags); \
            NCP_BUS_WRITE32(                       \
                NCP_DEV_BUS_ADDR(dev, pageId, offset),  \
                value,                                  \
                NCP_DEV_PAGE_FLAGS(dev, pageId));       \
            raw_spin_unlock_irqrestore(&dev->ncaAccessLock, _flags); \
        }                                                                   \
        if (NCP_DEV_PAGE_FLAGS(dev, pageId) & NCP_DEV_ACCESS_IO_SYNC)       \
        {                                                                   \
            NCP_BUS_READ32( NCP_DEV_BUS_ADDR(dev, NCP_DEV_PAGE_PCIE0_PEI,   \
                NCP_PEI_CONFIG),                                            \
                NCP_DEV_ACCESS_LITTLE_ENDIAN);                              \
        }                                                                   \
    } while (0);
#else
#define NCP_DEV_BUS_WRITE32(dev, pageId, offset, value) \
    NCP_DEV_BUS_WRITE32_UNLOCKED((dev), (pageId), (offset), (value))
#endif

#endif /* NCP_DEV_FBRS */

/* macros for the hostmem access methods */
#define NCP_DEV_HOSTMEM_PAGE_SHIFT 18
#define NCP_DEV_HOSTMEM_PAGE_SIZE ( (ncp_uint64_t) 1 << NCP_DEV_HOSTMEM_PAGE_SHIFT)
#define NCP_DEV_HOSTMEM_PAGE_MASK (NCP_DEV_HOSTMEM_PAGE_SIZE - 1)
#define NCP_DEV_HOSTMEM_PAGE_BASE(x) \
        ( (ncp_uint32_t) ( ((x) & (~NCP_DEV_HOSTMEM_PAGE_MASK)) >> NCP_DEV_HOSTMEM_PAGE_SHIFT) )


/*
 * Include the bus-adaptor specific headers
 *
 *   first include any default empty macros that are defined only
 *   for one (or a few) bus adaptors.
 */

#define NCP_DEV_PCI_MPAGE_SETUP(dev)

#include "uboot/ncp_dev_linux.h"

#ifndef NCP_BAR_REGS
        /* Guesstimate used in kernel-independent code */
#ifndef EXTERNAL_HOST
        #define NCP_BAR_REGS              3
#else
        #define NCP_BAR_REGS              1
#endif
#endif



#define NCP_INIT_REG32(_reg,_v) {ncp_uint32_t *_x=(ncp_uint32_t *)&(_reg); *_x=_v;}

#if 0
#define NCP_DEV_EVENT_DEBUG
#endif

/* function prototype for event enable function */
typedef ncp_st_t (* ncp_dev_event_enable_fn_t)(ncp_dev_hdl_t devHdl);

/* function prototype for event init function */
typedef ncp_st_t (* ncp_dev_event_disable_fn_t)(ncp_dev_hdl_t devHdl);

typedef struct ncp_dev_event_st {
    ncp_dev_event_type_t type;              /* event type */
    ncp_bool_t bIdValid;                    /* TRUE if id field is valid for this event. */
    ncp_dev_event_enable_fn_t enableFn;     /* automatic enable function. Called when first callback is registered. */
    ncp_dev_event_disable_fn_t disableFn;   /* automatic disable function. Called when last callback is unregistered. */
} ncp_dev_event_t;

#define NCP_DEV_EVENT_HDL_COOKIE    (0x0a0b0c0d)

typedef struct ncp_dev_event_cbk_node_st {
    ncp_uint32_t                cookie;
    ncp_dev_event_handler_t     handlerInfo;
    struct ncp_dev_event_cbk_node_st   *next;
    struct ncp_dev_event_cbk_node_st   *prev;
    ncp_bool_t                  unlinked;
    ncp_bool_t                  inUse;
} ncp_dev_event_cbk_node_t;

typedef struct ncp_dev_event_hdlr_list_st {
    ncp_dev_event_cbk_node_t *cbkList;
    ncp_dev_event_t          *eventInfo;
} ncp_dev_event_hdlr_list_t;

typedef struct ncp_dev_event_list_st {
    ncp_dev_event_hdlr_list_t lists[NCP_DEV_EVENT_LAST];
} ncp_dev_event_list_t;

/* Function to notify an event */
ncp_st_t
ncp_dev_event_dispatch(ncp_dev_hdl_t devHdl, ncp_dev_event_type_t type,
                       ncp_uint32_t id, void *eventData);

#define NCP_DEV_LBI_CS_MAX 16

/*
 * ncp_dev_t
 *
 * Per-NCP instance device structure.
 *
 */
struct ncp_dev_s
{
    ncp_uint32_t             tag;           /* Structure validation tag */
    int                      num;           /* instance number */
    ncp_uint32_t             flags;         /* driver flags */
    ncp_byte_order_t         hostEndian;
    struct {
        ncp_uint64_t         busAddr;       /* BUS base address */
        ncp_uint64_t         hwAddr;        /* BUS base address (h/w view) */
        void                *cpuAddr;       /* CPU virtual base address */
        ncp_uint32_t         size;          /* size of BAR space */
    } bar[NCP_BAR_REGS];                    /* base addresses */
    ncp_dev_page_t           pages[NCP_DEV_MAX_PAGES];
    ncp_uint64_t             axiDmaBase;
    ncp_uint64_t             busDmaOffset;
    ncp_dev_addr_map_t      *pLcmMap;
    ncp_uint32_t             fixedTpage7;

    ncp_region_io_t         *lastRegion;    /* last valid region map entry */
    ncp_region_coh_io_t     *coherentMap;   /* pointer to the chip-specific coherent map */

    ncp_uint32_t             lastMappedPage; /* last paged access mapping */
    ncp_dev_bus_dyn_page_map_fn_t  dynamicPageMapFn;
    ncp_bool_t               initDevConfig;  /* devConfig init control */
    ncp_dev_config_t        *config;         /* driver configuration variables */

    ncp_uint32_t             ncaConfigInit; /* cached value of config_init reg*/
    ncp_uint32_t             ncaAckTimeoutCnt; /* NCA PIO timeout */

#ifdef NCP_DEV_SOCKET
    ncp_dev_hdl_t            sockHdl;
#endif

    ncp_hdl_t                vpmHdl;        /* handle for kernel vpm module */
    ncp_dev_event_list_t     eventList;     /* internal event management */
    ncp_hdl_t                eioaHdl;       /* handle for kernel eioa module */

    ncp_dev_event_hdl_t      eventHandlers[NCP_DEV_EVENT_LAST]; /* driver registered events */

    ncp_bool_t               useInterrupts; /* does platform support interrupts? */
    ncp_uint8_t              isrActive;     /* non-zero when in interrupt */
    ncp_uint8_t              ncaVersion;
    ncp_uint32_t             irqMax;
    ncp_uint32_t             ncaTqsIrqMin;
    ncp_uint32_t             ncaTqsIrqMax;
    ncp_uint32_t             timerIrq;
    const char             **irqNames;
    ncp_waitq_t              *fem_waitq;
    ncp_waitq_t              *alarm_waitq;

    ncp_uint32_t              nrcpOffset;
    ncp_uint32_t              nrcpSelGnd;

    ncp_waitq_t              *nrcp_waitq;
    ncp_uint32_t              nrcpIntrStat;

    ncp_waitq_t              *timer_waitq;
    ncp_waitq_t              *timer_cpu_waitq[16];
    ncp_waitq_t		     *rif_waitq[2][2]; /* RIF-0/1 intr/exception */
    ncp_uint32_t	     rifIntrStatFlag[2][2];

    raw_spinlock_t           ncaAccessLock;
    spinlock_t               lock;
    spinlock_t               mdioLock;
    spinlock_t               busLock;   /* lock for use by bus adaptor, if needed */
    spinlock_t               hssTimerLock;

//    ncp_mutex_t                dmaIoSem;
//    ncp_mutex_t                i2cLock;

    /* bottom half status bits */
    ncp_uint16_t             numQpmEventQueues;
    ncp_uint16_t             lastQpmEventQueueId;
    volatile ncp_ncav3_qpm_stats_t *qpmStats;
    ncp_dev_stats_t          stats;         /* device statistics */
    ncp_hdl_t                i2cHdl;        /* relevant runtime state */
    ncp_hdl_t                catHdl;        /* relevant runtime state */
    ncp_hdl_t                pkaHdl;        /* relevant runtime state */
    ncp_uint32_t             *ntimcWriteBuf;/* pointer to buffer for ntimc writes */
    ncp_uint64_t             refStrobeTs;  /* Captured ref strobe timestamp */
    ncp_uint64_t             cpuIsrSeq[16];  /* Captured CPU Timer timestamp */
#if defined(NCP_LINUX) && defined(NCP_KERNEL)
//    struct timer_list        hssTimer;
#else
    ncp_uint8_t hssTimer[0x20]; /* 0x20 ?? */
#endif /* NCP_LINUX */
    ncp_uint32_t hssTimerInterval;
    ncp_bool_t hssTimerInitted;
#ifdef NCP_PROFILER
    ncp_hdl_t                profilerHdl;
    ncp_hdl_t                profilerHdlIsr;
#endif
    ncp_bool_t               noPhyConfig;
    ncp_uint64_t             activeTQSMask; /* TQSes used by local domain */
    ncp_uint32_t             numThreadQueueSets;
    ncp_dev_cpcq_t           cpcq;
    ncp_bool_t               appmode_is32bit; /* so kernel driver knows bitWidth architecture of user mode apps */
};


ncp_st_t
ncp_se_fem_intr_enable(ncp_dev_hdl_t devHdl);

ncp_st_t
ncp_se_fem_intr_disable(ncp_dev_hdl_t devHdl);

ncp_st_t
ncp_timer_intr_enable(ncp_dev_hdl_t devHdl);

ncp_st_t
ncp_timer_intr_disable(ncp_dev_hdl_t devHdl);

ncp_st_t ncp_dev_gsm_info_get(
    ncp_dev_hdl_t devHdl,
    ncp_dev_gsm_info_t *gsmInfo);


#endif /* __NCP_DEV_PVT_H__ */
