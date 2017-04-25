/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/


#ifndef __NCP_DEV_LINUX_H__
#define __NCP_DEV_LINUX_H__

#ifdef __cplusplus
extern "C" {
#endif


#ifdef NCP_DEV_PCI
#include "ncp_bus_pci.h"
#endif
#ifdef NCP_DEV_PLX
#include "ncp_bus_plx.h"
#endif
#ifdef NCP_DEV_SRIO
#include "ncp_bus_srio.h"
#endif
#ifdef NCP_DEV_SRIOEP
#include "ncp_bus_srioep.h"
#endif
#ifdef NCP_DEV_PLB
#include "ncp_bus_plb.h"
#endif

#include "uboot/ncp_task.h"

#if (1 == USE_NCAV3)
#include "uboot/ncp_ncav3.h"
#include "uboot/ncp_task_pvt.h"
#endif

/******************************************************************************
* Constants and 'Switches'
******************************************************************************/

#define NCP_PQFPGA_CHECK_MULTIPLE

/******************************************************************************
* VM_RESERVED Flag is deprecated in Linux 3.10 kernel 
******************************************************************************/
#ifndef VM_RESERVED
#define VM_RESERVED (VM_DONTEXPAND | VM_DONTDUMP)
#endif


/******************************************************************************
* IOCTL Structures and constants
******************************************************************************/

#define NCP_MAX_IOCTL_CMDSIZE   (128)
#define NCP_MAX_IOCTL_BUFSIZE   (8 * 1024)

/*
 * IOC Structure typedefs, constants, and macros
 */

/* NCP_IOC_TR_LVL_SET IOCTL structure definition */
typedef struct ncp_ioc_tr_lvl_set_s {
    ncp_uint32_t     level;      /* trace level */
    NCP_DECLARE_POINTER(ncp_st_t, st);         /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_tr_lvl_set_t;

/* NCP_IOC_TR_LVL_GET IOCTL structure definition */
typedef struct ncp_ioc_tr_lvl_get_s {
    NCP_DECLARE_POINTER(ncp_uint32_t, level);      /* trace level */
    NCP_DECLARE_POINTER(ncp_st_t, st);         /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_tr_lvl_get_t;

/* NCP_IOC_VERSION IOCTL structure definition */
typedef struct ncp_ioc_version_s {
    NCP_DECLARE_POINTER(char, version);    /* version string return location */
    NCP_DECLARE_POINTER(ncp_st_t, st);         /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_version_t;

/* NCP_IOC_HW_VERSION IOCTL structure definition */
typedef struct ncp_ioc_hw_version_s {
    NCP_DECLARE_POINTER(ncp_version_t, version);/* version return location */
    NCP_DECLARE_POINTER(ncp_st_t, st);         /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_hw_version_t;

/* NCP_IOC_DEV_NUM_GET IOCTL structure definition */
typedef struct ncp_ioc_dev_num_get_s {
    NCP_DECLARE_POINTER(ncp_uint32_t, devNum);         /* OUT: device number */
    NCP_DECLARE_POINTER(ncp_st_t, st);             /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_dev_num_get_t;

/* NCP_IOC_INFO IOCTL structure definition */
typedef struct ncp_ioc_info_s {
    NCP_DECLARE_POINTER(ncp_dev_info_t, info);    /* device driver information */
    NCP_DECLARE_POINTER(ncp_st_t, st);         /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_info_t;

/* NCP_IOC_INFO_GET IOCTL structure definition */
typedef struct ncp_ioc_info_get_s {
    NCP_DECLARE_POINTER(ncp_uint32_t, info);       /* device driver state information */
    NCP_DECLARE_POINTER(ncp_st_t, st);         /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_info_get_t;

/* NCP_IOC_GSM_INFO IOCTL structure definition */
typedef struct ncp_ioc_gsm_info_s {
    NCP_DECLARE_POINTER(ncp_dev_gsm_info_t, info);
    NCP_DECLARE_POINTER(ncp_st_t, st);              /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_gsm_info_t;

/* NCP_IOC_TASK_KMODE_CFG_T structure definition */
typedef struct ncp_ioc_task_nca_kmode_cfg_s {
    NCP_DECLARE_POINTER(void,  cfgPtr);   /* ptr to swState */
    ncp_int32_t        cfgSize;          /* NumBytes to copy into kernel space */                                    
    NCP_DECLARE_POINTER(void, pGSMinfo);
    NCP_DECLARE_POINTER(ncp_st_t, st);    /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_task_nca_kmode_cfg_t;

/* NCP_IOC_TASK_FINISH_KMODE_CFG_T structure definition */
typedef struct ncp_ioc_task_nca_kmode_finish_cfg_s {
    NCP_DECLARE_POINTER(void, pGSMinfo);
    ncp_uint32_t        kmodePoolSz;
    NCP_DECLARE_POINTER(ncp_st_t, st);    /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_task_nca_kmode_finish_cfg_t;

/* NCP_IOC_TASK_KMODE_CFG_T structure definition */
typedef struct ncp_ioc_task_ncaV2_kmode_blocks_s {
    NCP_DECLARE_POINTER(ncp_st_t, st);  /* OUT: status code */
    ncp_uint32_t        poolId;         /* ID of pool to query */
    ncp_uint32_t        blockSize;      /* Blocksize to query */
    NCP_DECLARE_POINTER(ncp_uint32_t, numBlocks);   /* OUT: number of blocks available */
} NCP_COMPAT_PACKED ncp_ioc_task_ncaV2_kmode_blocks_t;

#if (1 == USE_NCAV3)
typedef struct ncp_ioc_ncav3_cfg_s {
    NCP_DECLARE_POINTER(ncp_task_swState_t, swState);
    NCP_DECLARE_POINTER(ncp_ncav3_hdl_t, nca);
    NCP_DECLARE_POINTER(ncp_st_t, st);
    ncp_ncav3_struct_sizes_t structSizes;
    ncp_bool_t               internal;
} NCP_COMPAT_PACKED ncp_ioc_ncav3_cfg_t;

typedef struct ncp_ioc_ncav3_ipcq_modify_s {
    ncp_uint8_t ncapId;
    ncp_uint8_t relTqsId;
    ncp_uint8_t pgitId;
    NCP_DECLARE_POINTER(ncp_st_t, st);
} NCP_COMPAT_PACKED ncp_ioc_ncav3_ipcq_modify_t;

typedef struct {
    ncp_uint32_t commandId;
    NCP_DECLARE_POINTER_ARRAY(void, p, 6);
    ncp_uint64_t v[6];
    NCP_DECLARE_POINTER(ncp_st_t, st);
} NCP_COMPAT_PACKED ncp_ioc_ncav3_generic_t;
#endif

typedef struct ncp_task_interrupt_s {
    ncp_uint32_t intrType;
    ncp_uint32_t grpRelQueueId; /* or mask if iPCQ(s) */
    ncp_uint8_t  grp;
    ncp_uint8_t  tqsID;
} NCP_COMPAT_PACKED ncp_task_interrupt_t;

typedef struct ncp_task_waiter_operation_s {
    ncp_uint32_t opCode;
    ncp_uint32_t poolID;
    ncp_uint32_t pid;
    NCP_DECLARE_POINTER(ncp_st_t, st);
} NCP_COMPAT_PACKED ncp_task_waiter_operation_t;

/* NCP_IOC_TASK_NCAV2_SET_DOMAIN_BUNDLE_T structure definition */
typedef struct ncp_ioc_task_ncaV2_set_domain_bundle_s {
    ncp_uint64_t domainBundlePA NCP_COMPAT_ALIGN64;
    ncp_int32_t  domainBundleSize;
    NCP_DECLARE_POINTER(ncp_st_t, st);         /* OUT: status code */    
} NCP_COMPAT_PACKED ncp_ioc_task_ncaV2_set_domain_bundle_t;

typedef struct ncp_task_tqs_state_modify_s {
    ncp_uint8_t      tqsID;      /* which TQS? */
    ncp_bool_t       disableTQS; /* TRUE->disable, FALSE->enable */
    ncp_uint8_t      grp;        /* grp membership */
    NCP_DECLARE_POINTER(ncp_st_t, st);         /* OUT: status code */    
} NCP_COMPAT_PACKED ncp_task_tqs_state_modify_t;

#if (1 == USE_NCA)
/* NCP_IOC_TASK_GET_KMODE_STATS IOCTL structure definition */
typedef struct ncp_ioc_get_task_stats_s {
    ncp_int32_t         cmd;
    ncp_int32_t         poolId;
    ncp_int32_t         copySize;
    NCP_DECLARE_POINTER(ncp_task_stats_t, pTaskStats);  /* pointer to Task I/O Stats Struct to receive data */
    NCP_DECLARE_POINTER(ncp_st_t, st);                  /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_get_task_stats_t;
#endif

/* NCP_IOC_INFO_SET IOCTL structure definition */
typedef struct ncp_ioc_info_set_s {
    ncp_uint32_t     info;             /* device driver state information */
    NCP_DECLARE_POINTER(ncp_st_t, st); /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_info_set_t;

/* NCP_IOC_STATS IOCTL structure definition */
typedef struct ncp_ioc_stats_s {
    NCP_DECLARE_POINTER(ncp_dev_stats_t, stats);  /* device driver statistics */
    NCP_DECLARE_POINTER(ncp_st_t, st);            /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_stats_t;

typedef struct ncp_ioc_status_s {
    NCP_DECLARE_POINTER(ncp_st_t, st);         /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_status_t;

/* NCP_IOC_TIMER_WAIT_FOR_INTERRUPT structure definition */
typedef struct ncp_ioc_timestamp_s {
    NCP_DECLARE_POINTER(ncp_uint64_t, ticks);  /* ref strobe timestamp */
    NCP_DECLARE_POINTER(ncp_st_t, st);         /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_timestamp_t;

/* NCP_IOC_TIMER_WAIT_FOR_CPU_INTERRUPT structure definition */
typedef struct ncp_ioc_cpu_timer_info_s {
    ncp_uint32_t timerIndex;  /* cpu timer index 0-15 */
    ncp_uint32_t     flags;
    ncp_uint64_t     lastSeq NCP_COMPAT_ALIGN64;  /* IN: last user captured sequence # for CPU Timer */
    NCP_DECLARE_POINTER(ncp_uint64_t, currentSeq);  /* OUT: sequence number of CPU Timer */
    NCP_DECLARE_POINTER(ncp_st_t, st);         /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_cpu_timer_info_t;

/* generic read/write IOCTL definition */
typedef struct ncp_ioc_rw_s {
    ncp_region_id_t  regionId;         /* NCP region ID */
    ncp_uint64_t     offset NCP_COMPAT_ALIGN64; /* start offset within NCP region */
    NCP_DECLARE_POINTER(void, buffer); /* buffer address */
    ncp_uint32_t     count;            /* transfer count */
    ncp_uint32_t     flags;            /* I/O control flags */
    ncp_uint32_t     xferWidth;        /* transfer width */
    NCP_DECLARE_POINTER(ncp_st_t, st); /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_rw_t;

/* NCP_IOC_TRANS_ADD */
typedef struct ncp_ioc_trans_add_s {
    ncp_dev_trans_type_t transType;
    union {
        ncp_dev_trans_udelay_t udelay;
        ncp_dev_trans_block_fill32_t bf32;
        ncp_dev_trans_block_write32_t bw32;
    } u;
    ncp_uint32_t flags;
    NCP_DECLARE_POINTER(ncp_st_t, st);
} NCP_COMPAT_PACKED ncp_ioc_trans_add_t;


/* NCP_IOC_ALARM_GET */
typedef struct ncp_ioc_alarm_s {
    ncp_bool_t           blocking;
    NCP_DECLARE_POINTER(ncp_alarm_bitmask_t, alarm);
    NCP_DECLARE_POINTER(ncp_st_t,            st);
} NCP_COMPAT_PACKED ncp_ioc_alarm_t;

typedef struct ncp_ioc_alarm_reg_s {
    ncp_uint32_t irq;
    ncp_uint32_t size;
    NCP_DECLARE_POINTER(ncp_alarm_intr_regs_t, regs);
    NCP_DECLARE_POINTER(ncp_st_t,              st);
} NCP_COMPAT_PACKED ncp_ioc_alarm_reg_t;

typedef struct ncp_ioc_eioa_hss_los_hdlr_s {
    ncp_uint32_t timerInterval;
} NCP_COMPAT_PACKED ncp_ioc_eioa_hss_los_hdlr_t;


/*
 * Begin New IOCTL structures for NCA Task IO, including the NCA Task IO system call model
 */


#define NCP_NCA_VM_FLAGS_COHERENT (VM_IO | VM_SHARED | VM_LOCKED)

/* #define NCP_NCA_PAGE_FLAGS_COHERENT (_PAGE_RW | _PAGE_COHERENT | _PAGE_ACCESSED | _PAGE_PRESENT | _PAGE_GUARDED) */
#define NCP_NCA_PAGE_FLAGS_COHERENT (_PAGE_RW | _PAGE_COHERENT | _PAGE_ACCESSED | _PAGE_PRESENT) 


void *
ncp_mem_mmap(ncp_dev_hdl_t devHdl, void *startAddr, ncp_uint32_t size, 
             ncp_uint64_t physAddr);
 
#define NCP_MEM_MMAP(devHdl, pStartAddr, size, physAddr)  \
     ({                                          \
         void *_ptr = NULL;                      \
         _ptr = ncp_mem_mmap((ncp_dev_hdl_t)devHdl, (void *)pStartAddr, size, physAddr);  \
         _ptr;                                   \
     })

 /*
  * End New IOCTL structures for NCA Task IO
  */


/********************* Begin data structs for VPM *************/

typedef struct ncp_vpm_kernel_info_st {
    NCP_DECLARE_HDL(ncp_hdl_t, uVpmHdl);
    NCP_DECLARE_POINTER(ncp_st_t, st);
} ncp_vpm_kernel_info_t;

/********************* End data structs for VPM *************/


/*
 * Begin IOCTL structures for EIOA kernel mode API's
 */
/*
 * generic stucture 
 */
#if (1 != USE_EIOA )
typedef struct ncp_eioa_t5_s {
    NCP_DECLARE_HDL(ncp_hdl_t, ncpHdl);
    ncp_uint32_t        macChan;
    ncp_uint32_t        vOne;
    ncp_uint32_t        vTwo;
    ncp_uint32_t        vThree;
    ncp_uint32_t        vFour;
    ncp_uint32_t        vFive;
    NCP_DECLARE_POINTER(void, pOne);
    NCP_DECLARE_POINTER(void, pTwo);
    NCP_DECLARE_POINTER(void, pThree);
    NCP_DECLARE_POINTER(void, pFour);
    NCP_DECLARE_POINTER(void, pFive);
    NCP_DECLARE_POINTER(ncp_st_t, ncp_status);
}  NCP_COMPAT_PACKED ncp_eioa_t5_t;

 /*
  * End IOCTL structures for EIOA API's ***********************
  */

#endif

/*
 * BEGIN IOCTL structures for Crash Analysis Tools ************
 */

typedef struct ncp_ioc_cat_config_s
{
    ncp_bool_t        catMemoryEnable;   /* IN: */
    ncp_uint64_t      catMemoryPhysAddr NCP_COMPAT_ALIGN64; /* IN: */
    ncp_uint64_t      catMemorySize NCP_COMPAT_ALIGN64;     /* IN: */
    NCP_DECLARE_POINTER(ncp_uint64_t, oCatMemoryNeeded);  /* OUT: */
    NCP_DECLARE_POINTER(ncp_st_t, ncp_status);        /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_cat_config_t;

typedef struct ncp_ioc_cat_write_s
{
    ncp_uint32_t      flags;      /* I/O control flags */
    NCP_DECLARE_POINTER(ncp_st_t, ncp_status); /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_cat_write_t;

typedef struct ncp_ioc_cat_write_raw_s
{
    NCP_DECLARE_POINTER(void, buffer);         /* buffer address */
    ncp_uint32_t      count;               /* byte count in buffer */
    ncp_uint32_t      flags;               /* I/O control flags */
    NCP_DECLARE_POINTER(ncp_st_t, ncp_status); /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_cat_write_raw_t;

typedef struct ncp_ioc_cat_write_finalize_s
{
    ncp_uint32_t      flags;      /* I/O control flags */
    NCP_DECLARE_POINTER(ncp_st_t, ncp_status); /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_cat_write_finalize_t;

typedef struct ncp_ioc_cat_read_s
{
    NCP_DECLARE_POINTER(ncp_uint8_t, buffer);     /* OUT: location to place read data */
    ncp_uint32_t      bufferSize; /* IN: max # of bytes to place in buffer */
    NCP_DECLARE_POINTER(ncp_uint64_t, offset);     /* OUT: displace into recovery data to read */
    NCP_DECLARE_POINTER(ncp_uint32_t, readSize);   /* OUT: # of bytes actually read */
    ncp_uint32_t      flags;      /* IN: I/O control flags */
    NCP_DECLARE_POINTER(ncp_st_t, ncp_status); /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_cat_read_t;

typedef struct ncp_ioc_cat_size_s
{
    NCP_DECLARE_POINTER(ncp_uint32_t, catMemorySize); /* OUT: Size of storage being used for CAT */
    NCP_DECLARE_POINTER(ncp_st_t, ncp_status); /* OUT: status code */
} NCP_COMPAT_PACKED ncp_ioc_cat_size_t;

/*
 * END IOCTL structures for Crash Analysis Tools ************
 */


/********************* Begin data structs for Profiler *************/

typedef struct ncp_ioc_profiler_num_entries_st
{
    NCP_DECLARE_POINTER(ncp_uint32_t, numEntries);
    NCP_DECLARE_POINTER(ncp_st_t, st);
} ncp_ioc_profiler_num_entries_t;

typedef struct ncp_ioc_profiler_entries_st
{
    ncp_uint32_t startEntry;
    ncp_uint32_t numEntries;
    NCP_DECLARE_POINTER(void, entries);
    NCP_DECLARE_POINTER(ncp_st_t, st);
} ncp_ioc_profiler_entries_t;


/********************* End data structs for Profiler *************/

/* generic structure for passing in an ncp_uint32_t value */
typedef struct ncp_ioc_u32_s {
    ncp_uint32_t    value;    /* array of u32 values */
    NCP_DECLARE_POINTER(ncp_st_t, st);
} NCP_COMPAT_PACKED ncp_ioc_u32_t;

typedef struct ncp_ioc_u64_s {
    ncp_uint64_t    value;    /* array of u64 values */
    NCP_DECLARE_POINTER(ncp_st_t, st);
} NCP_COMPAT_PACKED ncp_ioc_u64_t;



/* ==================================================================================== */
/* ========================= BEGIN IOCTL COMMAND CODES ================================ */
/* ==================================================================================== */


#if ( 1 == USE_EIOA )

#define NCP_IOC_UNREF_NR           1

/************ TRACE  ****************/

#define NCP_IOC_TR_LVL_SET_NR      2
#define NCP_IOC_TR_LVL_GET_NR      3

/************ VERSION ****************/

#define NCP_IOC_HW_VERSION_NR      4
#define NCP_IOC_VERSION_NR         5

/************DEVNUM ****************/

#define NCP_IOC_DEV_NUM_GET_NR     6

/************ RESET ****************/

#define NCP_IOC_RESET_NR           7
#define NCP_IOC_PCI_RESET_NR       8
#define NCP_IOC_PCI_REINIT_NR      9
#define NCP_IOC_ISR_DISABLE_NR     10

/************ MISC ****************/

#define NCP_IOC_INFO_NR            11
#define NCP_IOC_INFO_GET_NR        12
#define NCP_IOC_INFO_SET_NR        13
#define NCP_IOC_STATS_NR           14

/************ PIO *********************/

#define NCP_IOC_READ8_NR           15
#define NCP_IOC_READ16_NR          16
#define NCP_IOC_READ32_NR          17
#define NCP_IOC_READ64_NR          18
#define NCP_IOC_CSMBR_NR           19

#define NCP_IOC_WRITE8_NR          20
#define NCP_IOC_WRITE16_NR         21
#define NCP_IOC_WRITE32_NR         22
#define NCP_IOC_WRITE64_NR         23
#define NCP_IOC_CSMBW_NR           24
#define NCP_IOC_SW_NR              25

#define NCP_IOC_FILL_NR            26
#define NCP_IOC_RMW_NR             27
#define NCP_IOC_BBW_NR             28
#define NCP_IOC_BSW_NR             29
#define NCP_IOC_BBF_NR             30

/************* More MISC **************************/
#define NCP_IOC_APPMODE_IS32BIT_NR 31

/************* TRANSACTION SERVICES ***************/
#define NCP_IOC_TRANS_START_NR     32
#define NCP_IOC_TRANS_ADD_NR       33
#define NCP_IOC_TRANS_END_NR       34
/************* EVENT MANAGER **********************/

#define NCP_IOC_EVENT_CFG_START_NR    35
#define NCP_IOC_EVENT_CFG_COMPLETE_NR 36
#define NCP_IOC_EVENT_CFG_DESTROY_NR  37

/************* VPM **********************/

#define NCP_IOC_VPM_KERNEL_CONFIG_NR   40
#define NCP_IOC_VPM_KERNEL_DESTROY_NR  41

/************* TASK I/O -- NCA *********************/

#define NCP_IOC_TASK_WAIT_FOR_INTERRUPT_NR                50
#define NCP_IOC_TASK_REGISTER_NCAV3_INTERRUPTS_NR         51
#define NCP_IOC_TASK_REGISTER_GRP_INTERRUPTS_NR           52
#define NCP_IOC_TASK_DISPLAY_MEM_ATTTRIBUTES_NR           53
#define NCP_IOC_TASK_TQS_STATE_MODIFY_NR                  54
#define NCP_IOC_TASK_INITIATE_SHUTDOWN_NR                 55
#define NCP_IOC_TASK_MANAGE_KMODE_STATS_NR                56
#define NCP_IOC_TASK_GSM_INFO_GET_NR                      57
#define NCP_IOC_TASK_NCA_DO_KMODE_CFG_NR                  58
#define NCP_IOC_TASK_NCAV2_SET_DOMAIN_BUNDLE_NR           59
#define NCP_IOC_TASK_NCA_FINISH_KMODE_CFG_NR              60
#define NCP_IOC_TASK_NCAV2_KMODE_AVAILABLE_BLOCKS_GET_NR  61
#define NCP_IOC_TASK_NCAV3_CFG_NR                         62
#define NCP_IOC_TASK_NCAV3_KERNEL_DESTROY_NR              63
#define NCP_IOC_TASK_NCAV3_ENABLE_IPCQ_NR                 64
#define NCP_IOC_TASK_NCAV3_DISABLE_IPCQ_NR                65
#define NCP_IOC_TASK_WAITER_THREADS_OP_NR                 66
#define NCP_IOC_TASK_NCAV3_GENERIC_NR                     67
#define NCP_IOC_EIOA_GENERIC_NR                           70



/************* EIOA - one IOCTL code for all of EIOA. **********************/

#define NCP_IOC_EIOA_GENERIC_NR                70

/************* MDIO **********************/

#define NCP_IOC_MDIO_WRITE_NR                  71
#define NCP_IOC_MDIO_READ_NR                   72

/************* CAT **********************/

#define NCP_IOC_CAT_CONFIG_NR                  80
#define NCP_IOC_CAT_WRITE_NR                   81
#define NCP_IOC_CAT_WRITE_RAW_NR               82
#define NCP_IOC_CAT_WRITE_FINALIZE_NR          83
#define NCP_IOC_CAT_READ_NR                    84
#define NCP_IOC_CAT_SIZE_NR                    85

/************* PKA  **********************/

#define NCP_IOC_PKA_CONFIG_NR                  90
#define NCP_IOC_PKA_DESTROY_NR                 91
#define NCP_IOC_PKA_TRANS_START_NR             92
#define NCP_IOC_PKA_TRANS_POLL_NR              93
#define NCP_IOC_PKA_TRANS_BLOCKING_NR          94
#define NCP_IOC_PKA_TRANS_KILL_NR              95
#define NCP_IOC_PKA_INFO_NR                    96
#define NCP_IOC_PKA_PROF_RETRIEVE_NR           97
#define NCP_IOC_PKA_PROF_INIT_NR               98

/************* PROFILER **********************/

#define NCP_IOC_PROFILER_INIT_NR               100
#define NCP_IOC_PROFILER_FREE_NR               101
#define NCP_IOC_PROFILER_START_NR              102
#define NCP_IOC_PROFILER_STOP_NR               103
#define NCP_IOC_PROFILER_NUM_ENTRIES_GET_NR    104
#define NCP_IOC_PROFILER_ENTRIES_GET_NR        105
#define NCP_IOC_PROFILER_CLEAR_NR              106

/************* SE **********************/

#define NCP_IOC_SE_FEM_WAIT_FOR_INTERRUPT_NR   110

/************* SYSMEM **********************/

/************* HSS **********************/
#define NCP_IOC_EIOA_HSS_LOS_HDLR_START_NR     115
#define NCP_IOC_EIOA_HSS_LOS_HDLR_STOP_NR      116


/************* TIMER **********************/

#define NCP_IOC_TIMER_WAIT_FOR_INTERRUPT_NR       120
#define NCP_IOC_TIMER_WAIT_FOR_CPU_INTERRUPT_NR   121
#define NCP_IOC_TIMER_SYNC_EXTERNAL_NR            122

/************* MISC  **********************/

#define NCP_IOC_ALARM_IRQ_GET_NR   125
#define NCP_IOC_ALARM_REG_NR       126
#define NCP_IOC_PMU_USER_EN_NR     127


#if (1 == USE_RIF)
/**************** RIF **************/
#define NCP_IOC_RIF_EVENT_WAIT_NR 128

/************* USED FOR ARRAY SIZING ******/

#define NCP_IOC_LAST_NR            129 /* <- MUST BE LAST! */
#else
/************* USED FOR ARRAY SIZING ******/

#define NCP_IOC_LAST_NR            128 /* <- MUST BE LAST! */

#endif

#else /* Non-EIOA2 command codes */

#define NCP_IOC_UNREF_NR           1

/************ TRACE  ****************/

#define NCP_IOC_TR_LVL_SET_NR      2 
#define NCP_IOC_TR_LVL_GET_NR      3 

/************ VERSION ****************/

#define NCP_IOC_HW_VERSION_NR      4 
#define NCP_IOC_VERSION_NR         5 

/************DEVNUM ****************/

#define NCP_IOC_DEV_NUM_GET_NR     6 

/************ RESET ****************/    

#define NCP_IOC_RESET_NR           7 
#define NCP_IOC_PCI_RESET_NR       8 
#define NCP_IOC_PCI_REINIT_NR      9 
#define NCP_IOC_ISR_DISABLE_NR     10

/************ MISC ****************/

#define NCP_IOC_INFO_NR            11
#define NCP_IOC_INFO_GET_NR        12
#define NCP_IOC_INFO_SET_NR        13
#define NCP_IOC_STATS_NR           14

/************ PIO *********************/

#define NCP_IOC_READ8_NR           15
#define NCP_IOC_READ16_NR          16
#define NCP_IOC_READ32_NR          17
#define NCP_IOC_READ64_NR          18 
#define NCP_IOC_CSMBR_NR           19

#define NCP_IOC_WRITE8_NR          20
#define NCP_IOC_WRITE16_NR         21
#define NCP_IOC_WRITE32_NR         22
#define NCP_IOC_WRITE64_NR         23
#define NCP_IOC_CSMBW_NR           24
#define NCP_IOC_SW_NR              25

#define NCP_IOC_FILL_NR            26 
#define NCP_IOC_RMW_NR             27 
#define NCP_IOC_BBW_NR             28 
#define NCP_IOC_BSW_NR             29 
#define NCP_IOC_BBF_NR             30 

/************* More MISC **************************/
#define NCP_IOC_APPMODE_IS32BIT_NR 31
 
/************* TRANSACTION SERVICES ***************/
#define NCP_IOC_TRANS_START_NR     32
#define NCP_IOC_TRANS_ADD_NR       33
#define NCP_IOC_TRANS_END_NR       34 
/************* EVENT MANAGER **********************/

#define NCP_IOC_EVENT_CFG_START_NR    35
#define NCP_IOC_EVENT_CFG_COMPLETE_NR 36 
#define NCP_IOC_EVENT_CFG_DESTROY_NR  37 

/************* VPM **********************/

#define NCP_IOC_VPM_KERNEL_CONFIG_NR   43 
#define NCP_IOC_VPM_KERNEL_DESTROY_NR  44 

/************* TASK I/O -- NCA *********************/

#define NCP_IOC_TASK_WAIT_FOR_INTERRUPT_NR        50             
#define NCP_IOC_TASK_REGISTER_NCAV3_INTERRUPTS_NR 51
#define NCP_IOC_TASK_REGISTER_GRP_INTERRUPTS_NR   52            
#define NCP_IOC_TASK_DISPLAY_MEM_ATTTRIBUTES_NR   53            
#define NCP_IOC_TASK_TQS_STATE_MODIFY_NR          54            
#define NCP_IOC_TASK_INITIATE_SHUTDOWN_NR         55            
#define NCP_IOC_TASK_MANAGE_KMODE_STATS_NR        56            
#define NCP_IOC_TASK_GSM_INFO_GET_NR              57            
#define NCP_IOC_TASK_NCA_DO_KMODE_CFG_NR          58            
#define NCP_IOC_TASK_NCAV2_SET_DOMAIN_BUNDLE_NR   59            
#define NCP_IOC_TASK_NCA_FINISH_KMODE_CFG_NR      60           
#define NCP_IOC_TASK_NCAV2_KMODE_AVAILABLE_BLOCKS_GET_NR  61    
#define NCP_IOC_TASK_NCAV3_CFG_NR                         62     
#define NCP_IOC_TASK_NCAV3_KERNEL_DESTROY_NR              63     
#define NCP_IOC_TASK_NCAV3_ENABLE_IPCQ_NR                 64     
#define NCP_IOC_TASK_NCAV3_DISABLE_IPCQ_NR                65     
#define NCP_IOC_TASK_WAITER_THREADS_OP_NR                 66
#define NCP_IOC_TASK_NCAV3_GENERIC_NR                     67



/************* EIOA **********************/

#define NCP_IOC_EIOA_ALLOC_NR                  70 
#define NCP_IOC_EIOA_PORT_ALLOC_NR             71 
#define NCP_IOC_EIOA_PORT_ENABLE_GET_NR        72 
#define NCP_IOC_EIOA_PORT_ENABLE_SET_NR        73 
#define NCP_IOC_EIOA_QINQ_GET_NR               74 
#define NCP_IOC_EIOA_QINQ_SET_NR               75 
#define NCP_IOC_EIOA_AUTO_NEG_GET_NR           76 
#define NCP_IOC_EIOA_AUTO_NEG_SET_NR           77 
#define NCP_IOC_EIOA_MAC_STATS_GET_NR          78 
#define NCP_IOC_EIOA_VLAN_CONFIG_GET_NR        79 
#define NCP_IOC_EIOA_VLAN_CONFIG_SET_NR        80 
#define NCP_IOC_EIOA_TAG_CONFIG_GET_NR         81 
#define NCP_IOC_EIOA_TAG_CONFIG_SET_NR         82 
#define NCP_IOC_EIOA_TAG_ENABLE_GET_NR         83 
#define NCP_IOC_EIOA_TAG_ENABLE_SET_NR         84 
#define NCP_IOC_EIOA_TAG_CONFIG_ENABLE_SET_NR  85 
#define NCP_IOC_EIOA_MAC_TIMESTAMP_GET_NR      86 
#define NCP_IOC_EIOA_MAC_SPEED_DUPLEX_GET_NR   87 
#define NCP_IOC_EIOA_MAC_SPEED_DUPLEX_SET_NR   88 
#define NCP_IOC_EIOA_CRC_CONFIG_GET_NR         89 
#define NCP_IOC_EIOA_CRC_CONFIG_SET_NR         90 
#define NCP_IOC_EIOA_BROADCAST_FILTER_GET_NR   91 
#define NCP_IOC_EIOA_BROADCAST_FILTER_SET_NR   92 
#define NCP_IOC_EIOA_UNICAST_FILTER_GET_NR     93 
#define NCP_IOC_EIOA_UNICAST_FILTER_SET_NR     94 
#define NCP_IOC_EIOA_UNICAST_FILTER_ENABLE_NR  95 
#define NCP_IOC_EIOA_MULTICAST_FILTER_GET_NR   96 
#define NCP_IOC_EIOA_MULTICAST_FILTER_SET_NR   97 
#define NCP_IOC_EIOA_MULTICAST_FILTER_ADD_NR     98 
#define NCP_IOC_EIOA_MULTICAST_FILTER_DELETE_NR  99 
#define NCP_IOC_EIOA_MULTICAST_FILTER_ENABLE_NR  100
#define NCP_IOC_EIOA_MAC_PAUSE_GET_NR            101
#define NCP_IOC_EIOA_MAC_PAUSE_SET_NR            102
#define NCP_IOC_EIOA_VP_ID_GET_NR                103
#define NCP_IOC_EIOA_VP_ID_SET_NR                104
#define NCP_IOC_EIOA_SYNC_NR                     105
#define NCP_IOC_EIOA_PORT_SYNC_NR                106
#define NCP_IOC_EIOA_MAC_ADDR_GET_NR             107
#define NCP_IOC_EIOA_STAT_GET_NR                 108
#define NCP_IOC_EIOA_PHY_REG_GET_NR              109
#define NCP_IOC_EIOA_PHY_REG_SET_NR              110
#define NCP_IOC_EIOA_DESTROY_NR                  111 
#define NCP_IOC_EIOA_AN_START_NR                 112 
#define NCP_IOC_EIOA_AN_STOP_NR                  113 
#define NCP_IOC_EIOA_TX_MAXPKT_SET_NR            114 
#define NCP_IOC_EIOA_TX_MAXPKT_GET_NR            115 
#define NCP_IOC_EIOA_RX_MAXPKT_SET_NR            116 
#define NCP_IOC_EIOA_RX_MAXPKT_GET_NR            117 
#define NCP_IOC_EIOA_MAC_ADDR_SET_NR             118 
#define NCP_IOC_EIOA_LINK_STAT_GET_NR            119 
#define NCP_IOC_EIOA_LINK_STAT_GET_BLOCK_NR      120 
#define NCP_IOC_EIOA_OVRCLK_GET_NR               121 
#define NCP_IOC_EIOA_OVRCLK_SET_NR               122 
#define NCP_IOC_EIOA_CHAN_LOOPBACK_SET_NR        123
#define NCP_IOC_EIOA_MAC_TIMER_SHUTDOWN_NR       124 
#define NCP_IOC_EIOA_PORT_VP_GET_NR              125 
#define NCP_IOC_EIOA_PORT_VP_SET_NR              126 
#define NCP_IOC_EIOA_TS_MARKER_DELAY_GET_NR      127 
#define NCP_IOC_EIOA_TS_RESOLUTION_GET_NR        128 
#define NCP_IOC_EIOA_MAC_TIMESTAMP_GET_POLL_NR     129 
#define NCP_IOC_EIOA_FEC_SET_NR                    130 
#define NCP_IOC_EIOA_FEC_GET_NR                    131 
#define NCP_IOC_EIOA_STATS_MAX_PKT_LENGTH_SET_NR   132 
#define NCP_IOC_EIOA_STATS_MAX_PKT_LENGTH_GET_NR   133 
#define NCP_IOC_EIOA_PROMISC_ENABLE_NR	    	    134
#define NCP_IOC_EIOA_PROMISC_DISABLE_NR	    	    135 
#define NCP_IOC_EIOA_MAC_AN_TRACE_NR                136 
#define NCP_IOC_EIOA_IPP_PORT_VLAN_COUNT_UPDATE_NR  137 
#define NCP_IOC_EIOA_LINK_MONITOR_ENABLE_NR         138
#define NCP_IOC_EIOA_LINK_STAT_GET_BLOCK2_NR        139
                                                 /* 140 and 141 used below */
#define NCP_IOC_EIOA_AUTO_NEG_SET2_NR               142 

/************* MDIO **********************/

#define NCP_IOC_MDIO_WRITE_NR                  140 
#define NCP_IOC_MDIO_READ_NR                   141 
                                            /* 142 used above */

/************* NRCP **********************/

#define NCP_IOC_NRCP_EVENT_WAIT_NR             143

/************* CAT **********************/

#define NCP_IOC_CAT_CONFIG_NR                  145 
#define NCP_IOC_CAT_WRITE_NR                   146 
#define NCP_IOC_CAT_WRITE_RAW_NR               147 
#define NCP_IOC_CAT_WRITE_FINALIZE_NR          148 
#define NCP_IOC_CAT_READ_NR                    149 
#define NCP_IOC_CAT_SIZE_NR                    150 

/************* PKA  **********************/

#define NCP_IOC_PKA_CONFIG_NR                  155 
#define NCP_IOC_PKA_DESTROY_NR                 156 
#define NCP_IOC_PKA_TRANS_START_NR             157 
#define NCP_IOC_PKA_TRANS_POLL_NR              158 
#define NCP_IOC_PKA_TRANS_BLOCKING_NR          159 
#define NCP_IOC_PKA_TRANS_KILL_NR              160 
#define NCP_IOC_PKA_INFO_NR                    161 
#define NCP_IOC_PKA_PROF_RETRIEVE_NR           162 
#define NCP_IOC_PKA_PROF_INIT_NR               163 

/************* PROFILER **********************/

#define NCP_IOC_PROFILER_INIT_NR               170 
#define NCP_IOC_PROFILER_FREE_NR               171 
#define NCP_IOC_PROFILER_START_NR              172 
#define NCP_IOC_PROFILER_STOP_NR               173 
#define NCP_IOC_PROFILER_NUM_ENTRIES_GET_NR    174 
#define NCP_IOC_PROFILER_ENTRIES_GET_NR        175 
#define NCP_IOC_PROFILER_CLEAR_NR              176 

/************* SE **********************/

#define NCP_IOC_SE_FEM_WAIT_FOR_INTERRUPT_NR       180 

/************* SYSMEM **********************/

/************* HSS **********************/
#define NCP_IOC_EIOA_HSS_LOS_HDLR_START_NR         187 
#define NCP_IOC_EIOA_HSS_LOS_HDLR_STOP_NR          188

/************* TIMER **********************/

#define NCP_IOC_TIMER_WAIT_FOR_INTERRUPT_NR       190 
#define NCP_IOC_TIMER_WAIT_FOR_CPU_INTERRUPT_NR   191 
#define NCP_IOC_TIMER_SYNC_EXTERNAL_NR            192 

/************* MISC  **********************/

#define NCP_IOC_ALARM_IRQ_GET_NR   196 
#define NCP_IOC_ALARM_REG_NR       197 
#define NCP_IOC_PMU_USER_EN_NR     198


#if (1 == USE_RIF)
/**************** RIF **************/
#define NCP_IOC_RIF_EVENT_WAIT_NR 199

/************* USED FOR ARRAY SIZING ******/

#define NCP_IOC_LAST_NR            200 /* <- MUST BE LAST! */
#else
/************* USED FOR ARRAY SIZING ******/

#define NCP_IOC_LAST_NR            199 /* <- MUST BE LAST! */

#endif

#endif /* non-EIOA2 command codes. */


/* ==================================================================================== */
/* ========================= END IOCTL COMMAND CODES ================================== */
/* ==================================================================================== */




/* ==================================================================================== */
/* ========================= BEGIN IOCTL DEFINITIONS ================================== */
/* ==================================================================================== */


#define NCP_IOC                 ('n')

#define NCP_IOC_UNREF           _IO(NCP_IOC, NCP_IOC_UNREF_NR) /* reset module usage count */

/************ TRACE  ****************/

#define NCP_IOC_TR_LVL_SET      _IOWR(NCP_IOC, NCP_IOC_TR_LVL_SET_NR, ncp_ioc_tr_lvl_set_t)
#define NCP_IOC_TR_LVL_GET      _IOWR(NCP_IOC, NCP_IOC_TR_LVL_GET_NR, ncp_ioc_tr_lvl_get_t)

/************ VERSION ****************/

#define NCP_IOC_HW_VERSION      _IOWR(NCP_IOC, NCP_IOC_HW_VERSION_NR, ncp_ioc_hw_version_t)
#define NCP_IOC_VERSION         _IOWR(NCP_IOC, NCP_IOC_VERSION_NR, ncp_ioc_version_t)

/************DEVNUM ****************/

#define NCP_IOC_DEV_NUM_GET     _IOWR(NCP_IOC, NCP_IOC_DEV_NUM_GET_NR, ncp_ioc_dev_num_get_t)
#define NCP_IOC_RESET           _IOWR(NCP_IOC, NCP_IOC_RESET_NR, ncp_ioc_status_t)
#define NCP_IOC_PCI_RESET       _IOWR(NCP_IOC, NCP_IOC_PCI_RESET_NR, ncp_ioc_status_t)
#define NCP_IOC_PCI_REINIT      _IOWR(NCP_IOC, NCP_IOC_PCI_REINIT_NR, ncp_ioc_status_t)
#define NCP_IOC_ISR_DISABLE     _IOWR(NCP_IOC, NCP_IOC_ISR_DISABLE_NR, ncp_ioc_status_t)

/************ MISC ****************/

#define NCP_IOC_INFO            _IOWR(NCP_IOC, NCP_IOC_INFO_NR, ncp_ioc_info_t)
#define NCP_IOC_INFO_GET        _IOWR(NCP_IOC, NCP_IOC_INFO_GET_NR, ncp_ioc_info_get_t)
#define NCP_IOC_INFO_SET        _IOWR(NCP_IOC, NCP_IOC_INFO_SET_NR, ncp_ioc_info_set_t)
#define NCP_IOC_STATS           _IOWR(NCP_IOC, NCP_IOC_STATS_NR, ncp_ioc_stats_t)

/************ PIO *********************/

#define NCP_IOC_READ8           _IOWR(NCP_IOC, NCP_IOC_READ8_NR, ncp_ioc_rw_t)
#define NCP_IOC_READ16          _IOWR(NCP_IOC, NCP_IOC_READ16_NR, ncp_ioc_rw_t)
#define NCP_IOC_READ32          _IOWR(NCP_IOC, NCP_IOC_READ32_NR, ncp_ioc_rw_t)
#define NCP_IOC_READ64          _IOWR(NCP_IOC, NCP_IOC_READ64_NR, ncp_ioc_rw_t)
#define NCP_IOC_CSMBR           _IOWR(NCP_IOC, NCP_IOC_CSMBR_NR, ncp_ioc_rw_t)

#define NCP_IOC_WRITE8          _IOWR(NCP_IOC, NCP_IOC_WRITE8_NR, ncp_ioc_rw_t)
#define NCP_IOC_WRITE16         _IOWR(NCP_IOC, NCP_IOC_WRITE16_NR, ncp_ioc_rw_t)
#define NCP_IOC_WRITE32         _IOWR(NCP_IOC, NCP_IOC_WRITE32_NR, ncp_ioc_rw_t)
#define NCP_IOC_WRITE64         _IOWR(NCP_IOC, NCP_IOC_WRITE64_NR, ncp_ioc_rw_t)
#define NCP_IOC_CSMBW           _IOWR(NCP_IOC, NCP_IOC_CSMBW_NR, ncp_ioc_rw_t)
#define NCP_IOC_SW              _IOWR(NCP_IOC, NCP_IOC_SW_NR, ncp_ioc_rw_t)

#define NCP_IOC_FILL            _IOWR(NCP_IOC, NCP_IOC_FILL_NR, ncp_ioc_rw_t)
#define NCP_IOC_BBF             _IOWR(NCP_IOC, NCP_IOC_BBF_NR, ncp_ioc_rw_t)
#define NCP_IOC_RMW             _IOWR(NCP_IOC, NCP_IOC_RMW_NR, ncp_ioc_rw_t)
#define NCP_IOC_BBW             _IOWR(NCP_IOC, NCP_IOC_BBW_NR, ncp_ioc_rw_t)
#define NCP_IOC_BSW             _IOWR(NCP_IOC, NCP_IOC_BSW_NR, ncp_ioc_rw_t)
#define NCP_IOC_APPMODE_IS32BIT _IOWR(NCP_IOC, NCP_IOC_APPMODE_IS32BIT_NR, ncp_ioc_status_t)

/************* TRANSACTION SERVICES ***************/

#define NCP_IOC_TRANS_START     _IOWR(NCP_IOC, NCP_IOC_TRANS_START_NR, ncp_ioc_status_t)
#define NCP_IOC_TRANS_ADD       _IOWR(NCP_IOC, NCP_IOC_TRANS_ADD_NR, ncp_ioc_trans_add_t)
#define NCP_IOC_TRANS_END       _IOWR(NCP_IOC, NCP_IOC_TRANS_END_NR, ncp_ioc_status_t)

/************* EVENT MANAGER **********************/

#define NCP_IOC_EVENT_CFG_START     _IO(NCP_IOC, NCP_IOC_EVENT_CFG_START_NR)
#define NCP_IOC_EVENT_CFG_COMPLETE  _IO(NCP_IOC, NCP_IOC_EVENT_CFG_COMPLETE_NR)
#define NCP_IOC_EVENT_CFG_DESTROY   _IO(NCP_IOC, NCP_IOC_EVENT_CFG_DESTROY_NR)

/************* VPM **********************/

#define NCP_IOC_VPM_KERNEL_CONFIG   _IOWR(NCP_IOC, NCP_IOC_VPM_KERNEL_CONFIG_NR, ncp_vpm_kernel_info_t)
#define NCP_IOC_VPM_KERNEL_DESTROY  _IOWR(NCP_IOC, NCP_IOC_VPM_KERNEL_DESTROY_NR, ncp_vpm_kernel_info_t)

/************* TASK I/O **********************/

#define NCP_IOC_TASK_WAIT_FOR_INTERRUPT                 _IOWR(NCP_IOC, NCP_IOC_TASK_WAIT_FOR_INTERRUPT_NR, ncp_task_interrupt_t)
#define NCP_IOC_TASK_REGISTER_GRP_INTERRUPTS            _IOWR(NCP_IOC, NCP_IOC_TASK_REGISTER_GRP_INTERRUPTS_NR, ncp_ioc_u32_t)
#define NCP_IOC_TASK_DISPLAY_MEM_ATTTRIBUTES            _IOWR(NCP_IOC, NCP_IOC_TASK_DISPLAY_MEM_ATTTRIBUTES_NR, ncp_task_display_mem_atttributes_t)
#define NCP_IOC_TASK_TQS_STATE_MODIFY                   _IOWR(NCP_IOC, NCP_IOC_TASK_TQS_STATE_MODIFY_NR, ncp_task_tqs_state_modify_t)
#define NCP_IOC_TASK_INITIATE_SHUTDOWN                  _IO(NCP_IOC,   NCP_IOC_TASK_INITIATE_SHUTDOWN_NR)
#define NCP_IOC_TASK_MANAGE_KMODE_STATS                 _IOWR(NCP_IOC, NCP_IOC_TASK_MANAGE_KMODE_STATS_NR, ncp_ioc_get_task_stats_t)
#define NCP_IOC_TASK_GSM_INFO_GET                       _IOWR(NCP_IOC, NCP_IOC_TASK_GSM_INFO_GET_NR, ncp_ioc_gsm_info_t)
#define NCP_IOC_TASK_NCA_DO_KMODE_CFG                   _IOWR(NCP_IOC, NCP_IOC_TASK_NCA_DO_KMODE_CFG_NR, ncp_ioc_task_nca_kmode_cfg_t)
#define NCP_IOC_TASK_NCAV2_SET_DOMAIN_BUNDLE            _IOWR(NCP_IOC, NCP_IOC_TASK_NCAV2_SET_DOMAIN_BUNDLE_NR, ncp_ioc_task_ncaV2_set_domain_bundle_t)
#define NCP_IOC_TASK_NCA_FINISH_KMODE_CFG               _IOWR(NCP_IOC, NCP_IOC_TASK_NCA_FINISH_KMODE_CFG_NR, ncp_ioc_task_nca_kmode_finish_cfg_t)
#define NCP_IOC_TASK_NCAV2_KMODE_AVAILABLE_BLOCKS_GET   _IOWR(NCP_IOC, NCP_IOC_TASK_NCAV2_KMODE_AVAILABLE_BLOCKS_GET_NR, ncp_ioc_task_ncaV2_kmode_blocks_t)
#define NCP_IOC_TASK_NCAV3_CFG                          _IOWR(NCP_IOC, NCP_IOC_TASK_NCAV3_CFG_NR, ncp_ioc_ncav3_cfg_t)
#define NCP_IOC_TASK_NCAV3_KERNEL_DESTROY               _IOWR(NCP_IOC, NCP_IOC_TASK_NCAV3_KERNEL_DESTROY_NR, ncp_ioc_ncav3_cfg_t)
#define NCP_IOC_TASK_NCAV3_ENABLE_IPCQ                  _IOWR(NCP_IOC, NCP_IOC_TASK_NCAV3_ENABLE_IPCQ_NR, ncp_ioc_ncav3_ipcq_modify_t)
#define NCP_IOC_TASK_NCAV3_DISABLE_IPCQ                 _IOWR(NCP_IOC, NCP_IOC_TASK_NCAV3_DISABLE_IPCQ_NR, ncp_ioc_ncav3_ipcq_modify_t)
#define NCP_IOC_TASK_REGISTER_NCAV3_INTERRUPTS          _IOWR(NCP_IOC, NCP_IOC_TASK_REGISTER_NCAV3_INTERRUPTS_NR, ncp_ioc_u64_t)
#define NCP_IOC_TASK_WAITER_THREADS_OP                  _IOWR(NCP_IOC, NCP_IOC_TASK_WAITER_THREADS_OP_NR, ncp_task_waiter_operation_t)
#define NCP_IOC_TASK_NCAV3_GENERIC                      _IOWR(NCP_IOC, NCP_IOC_TASK_NCAV3_GENERIC_NR, ncp_ioc_ncav3_generic_t)

/************* EIOA **********************/

#define NCP_IOC_EIOA_ALLOC                  _IOWR(NCP_IOC, NCP_IOC_EIOA_ALLOC_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_PORT_ALLOC             _IOWR(NCP_IOC, NCP_IOC_EIOA_PORT_ALLOC_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_PORT_ENABLE_GET        _IOWR(NCP_IOC, NCP_IOC_EIOA_PORT_ENABLE_GET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_PORT_ENABLE_SET        _IOWR(NCP_IOC, NCP_IOC_EIOA_PORT_ENABLE_SET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_QINQ_GET               _IOWR(NCP_IOC, NCP_IOC_EIOA_QINQ_GET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_QINQ_SET               _IOWR(NCP_IOC, NCP_IOC_EIOA_QINQ_SET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_AUTO_NEG_GET           _IOWR(NCP_IOC, NCP_IOC_EIOA_AUTO_NEG_GET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_AUTO_NEG_SET           _IOWR(NCP_IOC, NCP_IOC_EIOA_AUTO_NEG_SET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MAC_STATS_GET          _IOWR(NCP_IOC, NCP_IOC_EIOA_MAC_STATS_GET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_VLAN_CONFIG_GET        _IOWR(NCP_IOC, NCP_IOC_EIOA_VLAN_CONFIG_GET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_VLAN_CONFIG_SET        _IOWR(NCP_IOC, NCP_IOC_EIOA_VLAN_CONFIG_SET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_TAG_CONFIG_GET         _IOWR(NCP_IOC, NCP_IOC_EIOA_TAG_CONFIG_GET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_TAG_CONFIG_SET         _IOWR(NCP_IOC, NCP_IOC_EIOA_TAG_CONFIG_SET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_TAG_ENABLE_GET         _IOWR(NCP_IOC, NCP_IOC_EIOA_TAG_ENABLE_GET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_TAG_ENABLE_SET         _IOWR(NCP_IOC, NCP_IOC_EIOA_TAG_ENABLE_SET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_TAG_CONFIG_ENABLE_SET  _IOWR(NCP_IOC, NCP_IOC_EIOA_TAG_CONFIG_ENABLE_SET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MAC_TIMESTAMP_GET      _IOWR(NCP_IOC, NCP_IOC_EIOA_MAC_TIMESTAMP_GET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MAC_SPEED_DUPLEX_GET   _IOWR(NCP_IOC, NCP_IOC_EIOA_MAC_SPEED_DUPLEX_GET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MAC_SPEED_DUPLEX_SET   _IOWR(NCP_IOC, NCP_IOC_EIOA_MAC_SPEED_DUPLEX_SET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_CRC_CONFIG_GET         _IOWR(NCP_IOC, NCP_IOC_EIOA_CRC_CONFIG_GET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_CRC_CONFIG_SET         _IOWR(NCP_IOC, NCP_IOC_EIOA_CRC_CONFIG_SET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_BROADCAST_FILTER_GET   _IOWR(NCP_IOC, NCP_IOC_EIOA_BROADCAST_FILTER_GET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_BROADCAST_FILTER_SET   _IOWR(NCP_IOC, NCP_IOC_EIOA_BROADCAST_FILTER_SET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_UNICAST_FILTER_GET     _IOWR(NCP_IOC, NCP_IOC_EIOA_UNICAST_FILTER_GET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_UNICAST_FILTER_SET     _IOWR(NCP_IOC, NCP_IOC_EIOA_UNICAST_FILTER_SET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_UNICAST_FILTER_ENABLE  _IOWR(NCP_IOC, NCP_IOC_EIOA_UNICAST_FILTER_ENABLE_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MULTICAST_FILTER_GET   _IOWR(NCP_IOC, NCP_IOC_EIOA_MULTICAST_FILTER_GET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MULTICAST_FILTER_SET   _IOWR(NCP_IOC, NCP_IOC_EIOA_MULTICAST_FILTER_SET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MULTICAST_FILTER_ADD   _IOWR(NCP_IOC, NCP_IOC_EIOA_MULTICAST_FILTER_ADD_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MULTICAST_FILTER_DELETE _IOWR(NCP_IOC, NCP_IOC_EIOA_MULTICAST_FILTER_DELETE_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MULTICAST_FILTER_ENABLE _IOWR(NCP_IOC, NCP_IOC_EIOA_MULTICAST_FILTER_ENABLE_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MAC_PAUSE_GET          _IOWR(NCP_IOC, NCP_IOC_EIOA_MAC_PAUSE_GET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MAC_PAUSE_SET          _IOWR(NCP_IOC, NCP_IOC_EIOA_MAC_PAUSE_SET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_VP_ID_GET              _IOWR(NCP_IOC, NCP_IOC_EIOA_VP_ID_GET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_VP_ID_SET              _IOWR(NCP_IOC, NCP_IOC_EIOA_VP_ID_SET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_SYNC                   _IOWR(NCP_IOC, NCP_IOC_EIOA_SYNC_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_PORT_SYNC              _IOWR(NCP_IOC, NCP_IOC_EIOA_PORT_SYNC_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MAC_ADDR_GET           _IOWR(NCP_IOC, NCP_IOC_EIOA_MAC_ADDR_GET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_STAT_GET               _IOWR(NCP_IOC, NCP_IOC_EIOA_STAT_GET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_PHY_REG_GET            _IOWR(NCP_IOC, NCP_IOC_EIOA_PHY_REG_GET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_PHY_REG_SET            _IOWR(NCP_IOC, NCP_IOC_EIOA_PHY_REG_SET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_DESTROY                _IOWR(NCP_IOC, NCP_IOC_EIOA_DESTROY_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_AN_START               _IOWR(NCP_IOC, NCP_IOC_EIOA_AN_START_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_AN_STOP                _IOWR(NCP_IOC, NCP_IOC_EIOA_AN_STOP_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_TX_MAXPKT_SET          _IOWR(NCP_IOC, NCP_IOC_EIOA_TX_MAXPKT_SET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_TX_MAXPKT_GET          _IOWR(NCP_IOC, NCP_IOC_EIOA_TX_MAXPKT_GET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_RX_MAXPKT_SET          _IOWR(NCP_IOC, NCP_IOC_EIOA_RX_MAXPKT_SET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_RX_MAXPKT_GET          _IOWR(NCP_IOC, NCP_IOC_EIOA_RX_MAXPKT_GET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MAC_ADDR_SET           _IOWR(NCP_IOC, NCP_IOC_EIOA_MAC_ADDR_SET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_LINK_STAT_GET          _IOWR(NCP_IOC, NCP_IOC_EIOA_LINK_STAT_GET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_LINK_STAT_GET_BLOCK    _IOWR(NCP_IOC, NCP_IOC_EIOA_LINK_STAT_GET_BLOCK_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_OVRCLK_GET             _IOWR(NCP_IOC, NCP_IOC_EIOA_OVRCLK_GET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_OVRCLK_SET             _IOWR(NCP_IOC, NCP_IOC_EIOA_OVRCLK_SET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_CHAN_LOOPBACK_SET      _IOWR(NCP_IOC, NCP_IOC_EIOA_CHAN_LOOPBACK_SET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MAC_TIMER_SHUTDOWN     _IOWR(NCP_IOC, NCP_IOC_EIOA_MAC_TIMER_SHUTDOWN_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_PORT_VP_GET            _IOWR(NCP_IOC, NCP_IOC_EIOA_PORT_VP_GET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_PORT_VP_SET            _IOWR(NCP_IOC, NCP_IOC_EIOA_PORT_VP_SET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_TS_MARKER_DELAY_GET    _IOWR(NCP_IOC, NCP_IOC_EIOA_TS_MARKER_DELAY_GET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_TS_RESOLUTION_GET      _IOWR(NCP_IOC, NCP_IOC_EIOA_TS_RESOLUTION_GET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MAC_TIMESTAMP_GET_POLL     _IOWR(NCP_IOC, NCP_IOC_EIOA_MAC_TIMESTAMP_GET_POLL_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_FEC_SET                    _IOWR(NCP_IOC, NCP_IOC_EIOA_FEC_SET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_FEC_GET                    _IOWR(NCP_IOC, NCP_IOC_EIOA_FEC_GET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_STATS_MAX_PKT_LENGTH_SET   _IOWR(NCP_IOC, NCP_IOC_EIOA_STATS_MAX_PKT_LENGTH_SET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_STATS_MAX_PKT_LENGTH_GET   _IOWR(NCP_IOC, NCP_IOC_EIOA_STATS_MAX_PKT_LENGTH_GET_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_PROMISC_ENABLE	    	    _IOWR(NCP_IOC, NCP_IOC_EIOA_PROMISC_ENABLE_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_PROMISC_DISABLE	    	_IOWR(NCP_IOC, NCP_IOC_EIOA_PROMISC_DISABLE_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_MAC_AN_TRACE               _IOWR(NCP_IOC, NCP_IOC_EIOA_MAC_AN_TRACE_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_IPP_PORT_VLAN_COUNT_UPDATE _IOWR(NCP_IOC, NCP_IOC_EIOA_IPP_PORT_VLAN_COUNT_UPDATE_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_LINK_MONITOR_ENABLE        _IOWR(NCP_IOC, NCP_IOC_EIOA_LINK_MONITOR_ENABLE_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_LINK_STAT_GET_BLOCK2       _IOWR(NCP_IOC, NCP_IOC_EIOA_LINK_STAT_GET_BLOCK2_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_AUTO_NEG_SET2              _IOWR(NCP_IOC, NCP_IOC_EIOA_AUTO_NEG_SET2_NR, ncp_eioa_t5_t)
#define NCP_IOC_EIOA_GENERIC                _IOWR(NCP_IOC, NCP_IOC_EIOA_GENERIC_NR, ncp_eioa_ioctl_data_t)

/************* MDIO **********************/

#define NCP_IOC_MDIO_WRITE                  _IOWR(NCP_IOC, NCP_IOC_MDIO_WRITE_NR, ncp_ioc_rw_t)
#define NCP_IOC_MDIO_READ                   _IOWR(NCP_IOC, NCP_IOC_MDIO_READ_NR, ncp_ioc_rw_t)

/************* NRCP **********************/
#define NCP_IOC_NRCP_EVENT_WAIT             _IOWR(NCP_IOC, NCP_IOC_NRCP_EVENT_WAIT_NR, ncp_ioc_info_get_t)

/************* CAT **********************/

#define NCP_IOC_CAT_CONFIG                  _IOWR(NCP_IOC, NCP_IOC_CAT_CONFIG_NR, ncp_ioc_cat_config_t)
#define NCP_IOC_CAT_WRITE                   _IOWR(NCP_IOC, NCP_IOC_CAT_WRITE_NR, ncp_ioc_cat_write_t)
#define NCP_IOC_CAT_WRITE_RAW               _IOWR(NCP_IOC, NCP_IOC_CAT_WRITE_RAW_NR, ncp_ioc_cat_write_raw_t)
#define NCP_IOC_CAT_WRITE_FINALIZE          _IOWR(NCP_IOC, NCP_IOC_CAT_WRITE_FINALIZE_NR, ncp_ioc_cat_write_finalize_t)
#define NCP_IOC_CAT_READ                    _IOWR(NCP_IOC, NCP_IOC_CAT_READ_NR, ncp_ioc_cat_read_t)
#define NCP_IOC_CAT_SIZE                    _IOWR(NCP_IOC, NCP_IOC_CAT_SIZE_NR, ncp_ioc_cat_size_t)

/************* SE **********************/

#define NCP_IOC_SE_FEM_WAIT_FOR_INTERRUPT       _IO(NCP_IOC, NCP_IOC_SE_FEM_WAIT_FOR_INTERRUPT_NR)

/************* BEGIN SYSMEM CODES  **********************/

/************* BEGIN HSS CODES  **********************/
#define NCP_IOC_EIOA_HSS_LOS_HDLR_START       _IOWR(NCP_IOC, NCP_IOC_EIOA_HSS_LOS_HDLR_START_NR, ncp_ioc_eioa_hss_los_hdlr_t)
#define NCP_IOC_EIOA_HSS_LOS_HDLR_STOP        _IOWR(NCP_IOC, NCP_IOC_EIOA_HSS_LOS_HDLR_STOP_NR, ncp_ioc_eioa_hss_los_hdlr_t)

/************* TIMER **********************/

#define NCP_IOC_TIMER_WAIT_FOR_INTERRUPT       _IOWR(NCP_IOC, NCP_IOC_TIMER_WAIT_FOR_INTERRUPT_NR, ncp_ioc_timestamp_t)
#define NCP_IOC_TIMER_WAIT_FOR_CPU_INTERRUPT   _IOWR(NCP_IOC, NCP_IOC_TIMER_WAIT_FOR_CPU_INTERRUPT_NR, ncp_ioc_cpu_timer_info_t)
#define NCP_IOC_TIMER_SYNC_EXTERNAL            _IO(NCP_IOC, NCP_IOC_TIMER_SYNC_EXTERNAL_NR)

/************* MISC  **********************/

#define NCP_IOC_ALARM_IRQ_GET   _IOWR(NCP_IOC, NCP_IOC_ALARM_IRQ_GET_NR, ncp_ioc_alarm_t)
#define NCP_IOC_ALARM_REG       _IOWR(NCP_IOC, NCP_IOC_ALARM_REG_NR, ncp_ioc_alarm_reg_t)
#define NCP_IOC_PMU_USER_EN     _IOWR(NCP_IOC, NCP_IOC_PMU_USER_EN_NR, ncp_ioc_status_t)

/* ==================================================================================== */
/* ========================= END IOCTL DEFINITIONS ==================================== */
/* ==================================================================================== */


/******************************************************************************
* Macros & Procedure Prototypes
******************************************************************************/


#define NCP_EDEV_INIT() ncp_edev_bus_init()
#define NCP_EDEV_FINI() ncp_edev_bus_fini()

#define NCP_EDEV_BUS_CLEANUP(devNum) ncp_edev_bus_cleanup(devNum)

#define NCP_EDEV_BUS_FIND_DEVS()   ncp_edev_bus_find_devs()

#define NCP_EDEV_BUS_SETUP(devNum) ncp_edev_bus_setup(devNum)

#define NCP_EDEV_BUS_MAP_PAGE(dev, pageAddress, cpuAddress) \
    ncp_edev_bus_map_page(dev, pageAddress, cpuAddress)

#define NCP_EDEV_BUS_MAP_PAGE_CACHED(dev, pageAddress, cpuAddress) \
    ncp_edev_bus_map_page_cached(dev, pageAddress, cpuAddress)

int
ncp_edev_bus_init(void);

int
ncp_edev_bus_fini(void);

ncp_st_t
ncp_edev_bus_cleanup(int);

int
ncp_edev_timer_add(
    void *pTimer,
    void *timerFunc,         
    void *timerFuncArg,     
    unsigned long duration);

int
ncp_edev_timer_mod(
    void *pTimer,
    unsigned long duration);

int
ncp_edev_timer_cancel(
    void *pTimer);

int
ncp_edev_timer_cancel_sync(
    void *pTimer);

/* --- Function pointer assignment macros, used by the region map --- */
/* --- Don't forget to add prototype @ ncp_dev_pvt.h:NCP_DEV_IO_PROTOTYPE */
#define  __ncp_dev_direct_read                  ncp_dev_direct_read
#define  __ncp_dev_direct_write                 ncp_dev_direct_write
#define  __ncp_dev_indirect_read                ncp_dev_indirect_read
#define  __ncp_dev_indirect_write               ncp_dev_indirect_write
#define  __ncp_dev_bus_config_read              ncp_dev_bus_config_read
#define  __ncp_dev_bus_config_write             ncp_dev_bus_config_write
#define  __ncp_dev_sysmem_cr_read               ncp_dev_sysmem_cr_read
#define  __ncp_dev_sysmem_cr_write              ncp_dev_sysmem_cr_write
#define  __ncp_dev_sysmem_nic_read              ncp_dev_sysmem_nic_read
#define  __ncp_dev_sysmem_nic_write             ncp_dev_sysmem_nic_write
#define  __ncp_dev_paged_read                   ncp_dev_paged_read
#define  __ncp_dev_paged_write                  ncp_dev_paged_write
#define  __ncp_dev_paged_cached_read            ncp_dev_paged_cached_read
#define  __ncp_dev_paged_cached_write           ncp_dev_paged_cached_write
#define  __ncp_dev_coherent_read                ncp_dev_coherent_read
#define  __ncp_dev_coherent_write               ncp_dev_coherent_write
#define  __ncp_dev_internal_read                ncp_dev_internal_read
#define  __ncp_dev_internal_write               ncp_dev_internal_write
#define  __ncp_dev_mdio_read                    ncp_dev_mdio_read
#define  __ncp_dev_mdio_write                   ncp_dev_mdio_write
#define  __ncp_dev_i2cprot_read                 ncp_dev_i2cprot_read
#define  __ncp_dev_i2cprot_write                ncp_dev_i2cprot_write
#define  __ncp_dev_ntimc_read                   ncp_dev_ntimc_read
#define  __ncp_dev_ntimc_write                  ncp_dev_ntimc_write
#define  __ncp_dev_l2_indirect_read             ncp_dev_l2_indirect_read
#define  __ncp_dev_l2_indirect_write            ncp_dev_l2_indirect_write
#define  __ncp_dev_trace_indirect_read          ncp_dev_trace_indirect_read
#define  __ncp_dev_trace_indirect_write         ncp_dev_trace_indirect_write
#define  __ncp_dev_hss_phy_read                 ncp_dev_hss_phy_read
#define  __ncp_dev_hss_phy_write                ncp_dev_hss_phy_write
#define  __ncp_dev_apb2ser_indirect_read        ncp_dev_apb2ser_indirect_read
#define  __ncp_dev_apb2ser_indirect_write       ncp_dev_apb2ser_indirect_write
#define  __ncp_dev_cdc_paged_read               ncp_dev_cdc_paged_read
#define  __ncp_dev_cdc_paged_write              ncp_dev_cdc_paged_write
#define  __ncp_dev_56xx_ddr_phy_write           ncp_dev_56xx_ddr_phy_write


/* ================================================================================= */
/* ========================= BEGIN NCAV3 COMMAND DEFINITIONS ======================= */
/* ================================================================================= */

#define NCAV3_GENERIC_GET_QPM_STATS                      1
#define NCAV3_GENERIC_ENABLE_KERNEL_TQS                  2
#define NCAV3_GENERIC_DISABLE_NCA_QUEUE                  3
#define NCAV3_GENERIC_ENABLE_NCA_QUEUE                   4
#define NCAV3_GENERIC_ADD_QUEUE_GROUP                    5
#define NCAV3_GENERIC_DELETE_QUEUE_GROUP                 6
#define NCAV3_GENERIC_MODIFY_QUEUE_GROUP                 7
#define NCAV3_GENERIC_SET_NCA_QUEUE_GROUP                8
#define NCAV3_GENERIC_SET_TQS_QUEUE_GROUPS               9
#define NCAV3_GENERIC_CONFIGURE_NCA_QUEUE                10
#define NCAV3_GENERIC_TQS_CONFIGURE_FLAGS_GET            11
#define NCAV3_GENERIC_TQS_MEMORY_QUOTA_GROUP_GET         12
#define NCAV3_GENERIC_TQS_QUEUE_GROUP_GET                13
#define NCAV3_GENERIC_QUEUE_GROUP_MEMBERSHIP_GET         14
#define NCAV3_GENERIC_QUEUE_GROUP_NAME_GET               15
#define NCAV3_GENERIC_TQS_NAME_GET                       16
#define NCAV3_GENERIC_QUEUE_GROUP_ID_GET                 17
#define NCAV3_GENERIC_TQS_ID_GET                         18
#define NCAV3_GENERIC_NCA_QUEUE_ID_GET                   19
#define NCAV3_GENERIC_CPU_APP_PROFILE_NAME_GET           20
#define NCAV3_GENERIC_NCA_QUEUE_PROFILE_NAME_GET         21
#define NCAV3_GENERIC_NCA_QUEUE_PROFILE_ID_GET           22
#define NCAV3_GENERIC_NCA_POOL_NAME_GET                  23
#define NCAV3_GENERIC_NCA_POOL_ID_GET                    24
#define NCAV3_GENERIC_GET_APP_PROFILE_NAME               25
#define NCAV3_GENERIC_NCA_PERFORM_TQS_BIND_CHECKS        26
#define NCAV3_GENERIC_NCA_SET_TQS_CONFIGURED_STATE       27
#define NCAV3_GENERIC_NCA_CONFIGURE_TQS                  28
#define NCAV3_GENERIC_SET_TRACING_ENABLE                 29
#define NCAV3_GENERIC_SET_QUEUE_TRACING_ENABLE           30
#define NCAV3_GENERIC_RESET_TRACING                      31
#define NCAV3_GENERIC_NCA_QUEUE_NAME_GET                 32
#define NCAV3_GENERIC_UPDATE_KERNEL_TQS_STATE            33
#define NCAV3_GENERIC_GET_APP_PROFILE_POOL_MAPPING       34
#define NCAV3_GENERIC_CHECK_QUEUE_GROUP_ORPHANED_QUEUES  35
#define NCAV3_GENERIC_GET_QPM_QUEUE_PROFILE_POOL_MAPPING 36
#define NCAV3_GENERIC_GET_QPM_QUEUE_PROFILE_NAME         37
/* ================================================================================= */
/* ========================= END NCAV3 COMMAND DEFINITIONS ========================= */
/* ================================================================================= */

#ifdef __cplusplus
}
#endif

#endif /* _NCP_DEV_LINUX_H_ */
