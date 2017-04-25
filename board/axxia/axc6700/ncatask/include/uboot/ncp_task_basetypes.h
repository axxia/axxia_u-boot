/*
 *  Copyright (C) 2014 LSI (john.jacques@lsi.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef NCP_TASK_BASETYPES_H
#define NCP_TASK_BASETYPES_H

#include <common.h>
/*
#include <config.h>
#include <asm/string.h>
#include <ubi_uboot.h>
*/

/* RWXXX */
//#include <unistd.h>

/* #include "uboot/axxia.h" */


#include <ncp_sal_types_linux.h>

#define debug_task(fmt, args...) printf("[%s:%s()]:%i: " fmt "\n",__FILE__,__func__ , __LINE__, ##args)


#define NCP_API extern

//#ifdef __KERNEL__

//#define NCP_EXPORT_SYMBOL(sym) EXPORT_SYMBOL(sym)

//#else

#define NCP_EXPORT_SYMBOL(sym);

//#endif

/*
 * Basic memory types
 */
 
#include <linux/types.h>

/*
 * Boolean constants
 */
#define FALSE 0
#define TRUE  1

/* LAPAJ START */
/* RWXXX
#ifdef __LP64__
typedef ncp_uint64_t ncp_uintptr_t;
#else
typedef ncp_uint32_t ncp_uintptr_t;
#endif
*/

/* typedef void *ncp_pid_t; */

/* typedef struct { */
/* 	long        tv_sec; */
/* 	long        tv_usec;     */
/* } ncp_timespec_us_t; */

typedef void *ncp_bitmap_t;
/* typedef void *ncp_task_v3_mutex_t; */




/* #define ncp_super_fpga(...) (NCP_ST_SUCCESS) */
#define NCP_REGION_NCAV3_CORE             (NCP_REGION_ID(0x101,  2)) /* 257.2 */
#define NCP_REGION_NCAV3_DMM              (NCP_REGION_ID(0x101,  3)) /* 257.3 */

#define     NCP_NCAP_GRP_LOAD_TIMER_ENABLE_WOCLR                (0x0001f224)
#define     NCP_NCAP_GRP_UPLOAD_TIMER_ENABLE_WOCLR              (0x0001f22c)
#define     NCP_NCAP_PGIT_GRP_LOAD_TIMER(n)                     (0x00010080 + (4*(n)))
#define     NCP_NCAP_DELAY_GRP_LOAD_TIMER(n)                    (0x00018100 + (4*(n)))
#define     NCP_NCAP_PGIT_GRP_UPLOAD_TIMER(n)                   (0x00010100 + (4*(n)))
#define     NCP_NCAP_PGITM_INIT_GRP_INDEXES                     (0x00010028)
#define     NCP_NCAP_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER(n)          (0x00018200 + (4*(n)))
#define     NCP_NCAP_DELAY_GRP_UPLOAD_TIMER(n)                  (0x00010180 + (4*(n)))


#define     NCP_NCAP_PCQ_DESC_IPCQ_R0(n)                        (0x00011000 + (16*(n)))
#define     NCP_NCAP_PCQ_DESC_IPCQ_R1(n)                        (0x00011004 + (16*(n)))
#define     NCP_NCAP_PCQ_DESC_IPCQ_R2(n)                        (0x00011008 + (16*(n)))
#define     NCP_NCAP_PCQ_DESC_IPCQ_R3(n)                        (0x0001100c + (16*(n)))


#define     NCP_NCAP_PCQ_DESC_MPCQ_R0(n)                        (0x00014000 + (16*(n)))
#define     NCP_NCAP_PCQ_DESC_MPCQ_R1(n)                        (0x00014004 + (16*(n)))
#define     NCP_NCAP_PCQ_DESC_MPCQ_R2(n)                        (0x00014008 + (16*(n)))
#define     NCP_NCAP_PCQ_DESC_MPCQ_R3(n)                        (0x0001400c + (16*(n)))

#define     NCP_NCAP_PCQ_DESC_OPCQ_R0(n)                        (0x00012000 + (16*(n)))
#define     NCP_NCAP_PCQ_DESC_OPCQ_R1(n)                        (0x00012004 + (16*(n)))
#define     NCP_NCAP_PCQ_DESC_OPCQ_R2(n)                        (0x00012008 + (16*(n)))
#define     NCP_NCAP_PCQ_DESC_OPCQ_R3(n)                        (0x0001200c + (16*(n)))

#define     NCP_NCAP_GRP_UPLOAD_TIMER_ENABLE_WOSET              (0x0001f32c)
#define     NCP_NCAP_GRP_LOAD_TIMER_ENABLE_WOSET                (0x0001f324)


/* LAPAJ END */



/* 
 * These hanbdles do not really exist in UBOOT environment 
 */
typedef void * ncp_hdl_t;
typedef void * ncp_vp_hdl_t;
/* RWXXX typedef void * ncp_sem_t; */
typedef void * ncp_dev_hdl_t;
typedef void * ncp_map_t;
/* typedef void * ncp_map_value_t; */
/* RWXXX typedef void * spinlock_flags_t; */


/* 
 * misc dev and ncp definitions
 */
 
/* macros to convert a 64-bit address to upper and lower 32-bit parts */
#define NCP_ADDR_UPPER(addr) ( (ncp_uint32_t) (addr >> 32) )
#define NCP_ADDR_LOWER(addr) ( (ncp_uint32_t) (addr & 0xFFFFFFFF))
 
 
#define NCP_REGION_NCA_AXI       (NCP_REGION_ID(0x101,  0)) /* 257.0 */
/* #define NCP_MAX_DEVS 1 */
 
/* --- NCP Device Instance Flags --- */
#define NCP_DEV_FLAGS_MASK          (0x0000ffff) /* driver flags */
#define NCP_USER_FLAGS_MASK         (0xffff0000) /* user/API flags */

#define NCP_DEV_BUS_PCI             (0x00000001)
#define NCP_DEV_BUS_SRIO            (0x00000002)
#define NCP_DEV_BUS_PLB             (0x00000004)
#define NCP_DEV_BUS_SRIOEP          (0x00000008)
#define NCP_DEV_BUS_PLX             (0x00000010)
#define NCP_DEV_BUS_ACE             (0x00000020)
#define NCP_DEV_BUS_HW              (0x0000003F)  /* mask for all h/w adaptors*/
                                                  /* add'l adapters may be
                                                   * enumerated in the holes
                                                   * in the above listing. */
#define NCP_DEV_BUS_FBRS            (0x00000100)
#define NCP_DEV_BUS_SOCKET          (0x00000200)
#define NCP_DEV_IS_ASIC             (0x00000400)

 
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
    unsigned chipVersion     :  6;
    unsigned chipType        :  5;
#else
    unsigned chipType        :  5;
    unsigned chipVersion     :  6;
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

typedef ncp_uint32_t    ncp_bus_adaptor_t;
typedef void * ncp_nca_hdl_t;
typedef ncp_uint32_t ncp_region_id_t;


/*
 * MISC SAL
 */
 
/* #define NCP_SYSMEM_BARRIER() \ */
/*     asm volatile ("dmb sy" : : : "memory") */

/* #define NCP_ISYNC_BARRIER() \ */
/*     asm volatile ("dsb sy" : : : "memory") */

#define NCP_PRINT_LINE_FILE
#define NCP_PRINT_LINE_FILE_MSG(...)

/*
#define NCP_ASSERT(condition, err)  \
    if (!(condition)) {             \
        ncpStatus = (err);          \
        NCP_PRINT_LINE_FILE;        \
        goto ncp_return;            \
    }

#define NCP_CALL(ncpFunc)                \
    do {                                 \
        ncpStatus = (ncpFunc);           \
        if (ncpStatus != NCP_ST_SUCCESS) \
        {                                \
            NCP_PRINT_LINE_FILE; \
            goto ncp_return;             \
        }                                \
    } while(0);
*/

#define NCP_JUMP_RETURN() \
	do { \
		goto ncp_return; \
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

/* #define NCP_MSG(type, ...) printf(__VA_ARGS__) */
#define NCP_LOG NCP_MSG
//#define NCP_MSG_NONE  0
//#define NCP_MSG_INFO  1
//#define NCP_MSG_ERROR 2
//#define NCP_MSG_DEBUG 3

#define NCP_TASK_REGISTER_GROUP_INTERRUPTS(...)

/* #define NCP_MEM_MMAP(_dev, _startVA, _size, _physAddr) (_physAddr) */
/* #define NCP_MEM_UNMAP(...) */
/* #define NCP_USER_MEM_UNMAP(...) */
#define __munmap(_a, _b) ((void)(_a), (void)(_b))
#define munmap(_a, _b) ({__munmap(_a, _b); 0; })
/* RWXXX */
/* #define udelay(s) usleep(s) */
/* #define ncp_nvm_malloc(_sz) malloc(_sz) */
/* #define ncp_nvm_free(_ptr)  free(_ptr) */
/* #define ncp_memcpy(_dst_,_src,_len) memcpy(_dst_,_src,_len) */
/* #define ncp_memset(_dst, _val, _len) memset(_dst, _val, _len) */
/* #define ncp_sys_usleep(_val) udelay(_val) */

/*
 * Dummy versions of internal functions
 */
 

#define NCP_CHECK_DISABLED
#if !defined(NCP_KERNEL) && !defined(NCP_CHECK_DISABLED)
#define NCP_VALIDATE_NCP_HDL(ncpHdl)     ncp_validate_handle(ncpHdl)
#define NCP_VP_VALIDATE_HANDLE(vpHdl)        ncp_vp_validate_handle(vpHdl)
#else
#define NCP_VALIDATE_NCP_HDL(ncpHdl)   NCP_ST_SUCCESS
#define NCP_VP_VALIDATE_HANDLE(vpHdl)  NCP_ST_SUCCESS
#endif /* NCP_KERNEL */



/* #define ncp_vp_cpu_terminate_template_id_get(...) */
/* #define ncp_vpm_task_param_decode(...) */
/* #define ncp_vpm_task_param_encode(vpHdl, to, from)  \ */
/*     memcpy(to, from, 32) */

#define NCP_TRACEPOINT(...) debug("Trace")
#define cond 0
#define NCP_TASKIO_TRACEPOINT(_a, _b, _c, fmt, args...) \
	do { \
		if (cond) \
			printf(pr_fmt(fmt), ##args); \
	} while(0)	\

/* #define ncp_comment(...) */


#define NCP_RETURN(f) \
	do { \
		ncpStatus = (f); \
		goto ncp_return; \
	} while (0)

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





#define NCP_POINTER(a) a


#define NCP_ST_TASK_PID_MISMATCH NCP_ST_ERROR
#define NCP_ST_MUTEX_CANNOT_CHANGE_TYPE NCP_ST_ERROR
#define NCP_ST_MUTEX_WRONG_STATE NCP_ST_ERROR
#define NCP_ST_TASK_UNSCHEDULED_QUEUE_IS_EMPTY NCP_ST_ERROR
#define NCP_ST_PTHREAD_MUTEX_OWNER_DEAD NCP_ST_ERROR
#define NCP_ST_TASK_BAD_POOL_OWNER_PROCESS NCP_ST_ERROR


#define NCP_SLEEP_POLL_INTERVAL 0
#define NCP_DO_MEMSET       TRUE



/* #define NCP_MUTEX_LOCKED_FLAG_DECL(a) int a; a = 0; if (a){}; */

/* #define NCP_MUTEX_LOCK(_pMutex, _pUnlockRequired)    ({ncp_st_t _st_mutex = NCP_ST_SUCCESS; _st_mutex;}) */
/* #define NCP_MUTEX_UNLOCK(_pMutex, _pUnlockRequired)  ({ncp_st_t _st_mutex = NCP_ST_SUCCESS; _st_mutex;}) */

/* RWXXX disabled for now
#define NCP_MUTEX_LOCK(_pMutex, _pUnlockRequired)           \
    ({                                                          \
    ncp_st_t _st_mutex = NCP_ST_SUCCESS;                          \
    if (NCP_ST_SUCCESS == (_st_mutex = ncp_mutex_lock(_pMutex)))  \
    {                                                       \
    *(ncp_bool_t *)(_pUnlockRequired) = TRUE;           \
    }                                                       \
    else                                                    \
    {                                                       \
    *(ncp_bool_t *)(_pUnlockRequired) = FALSE;          \
    }                                                       \
    _st_mutex;                                                    \
    })

#define NCP_MUTEX_UNLOCK(_pMutex, _pUnlockRequired)         \
    ({                                                          \
    ncp_st_t _st_mutex = NCP_ST_SUCCESS;                          \
    if (TRUE == *(ncp_bool_t *)_pUnlockRequired)            \
    {                                                       \
    _st_mutex = ncp_mutex_unlock(_pMutex);                    \
    *(ncp_bool_t *)(_pUnlockRequired) = FALSE;          \
    }                                                       \
    _st_mutex;                                                    \
    })
*/


/* #define NCP_TASK_LOCK_FLAGS(...) */
/* #define NCP_TASK_CLAIM_LOCK_HDL(...) (NCP_ST_SUCCESS) */
/* #define NCP_TASK_CLAIM_LOCK(...) (NCP_ST_SUCCESS) */
/* #define NCP_CLEANUP_MUTEX_CALL(...) */
/* #define NCP_TASK_FREE_LOCK_HDL(...) (NCP_ST_SUCCESS) */
/*
#ifndef NCP_CHECK_DISABLED
#define NCP_TASKIO_CHECK(_condition, _err) NCP_ASSERT((_condition), (_err))
#else
#define NCP_TASKIO_CHECK(_condition, _err)
#endif
*/

/* #define NCP_TASK_TQS_DISABLE(...) */
/* #define NCP_TASK_TQS_ENABLE(...) */
/* #define NCP_TASK_INIT_LOCK_HDL(...) (NCP_ST_SUCCESS) */
/* #define NCP_TASK_INIT_LOCK(...) (NCP_ST_SUCCESS) */
/* #define NCP_TASK_DESTROY_LOCK(...) */

#define NCP_TASK_PMU_ENABLE()

/* #define NCP_DEV_NCA_WRITE_INDIRECT_REG32(...) */

/* #define NCP_TASK_INITIATE_SHUTDOWN(_dev) */

#define NCP_SYSMEM_STORE_BARRIER() \
	__asm__ __volatile__ ("dmb st" : : : "memory")
#define NCP_OPCQ_SYSMEM_BARRIER() NCP_SYSMEM_STORE_BARRIER()

/* #define NCP_TASK_PREFETCH_PCQ_ENTRY(_pQueueEntry)       arch_prefetch_data((void *)_pQueueEntry) */

/* #define NCP_TASK_MEM_UNMAP(_devNum, _addr, _len) \ */
/* 	if (_len) {} \ */
/* 	NCP_MEM_UNMAP((((ncp_dev_t *)_dev)->num), _addr) */

/* LAPAJ
#define NCP_MEM_MAP(...) \
	(void *) 0;
*/


/* #define NCP_TASK_MEM_MMAP(_dev, _startVA, _size, _physAddr) \ */
/* 	mmap_stub((void *) _startVA,_size,(void *) _physAddr) */

/* #define NCP_TASK_IRQ_WAIT(_dev, _type, _grp, _tqsRelId, _tqsID) \ */
/* 	ncp_dev_nca_wait_for_isr_wakeup(_dev, _type, _grp, _tqsRelId, _tqsID) */


/* extern ncp_dev_hdl_t ncp_dev_hdls[NCP_MAX_DEVS]; */
/* ncp_pid_t ncp_get_pid(void); */
size_t ncp_strnlen(const char *s, size_t maxLen);
/* void arch_prefetch_data(const void *mva); */
/* void arch_prefetch_data_for_write(const void *mva); */
void *ncp_malloc(ncp_size_t size);
void *ncp_calloc(ncp_size_t no, ncp_size_t size);
void *ncp_nvm_calloc(ncp_size_t no, ncp_size_t size);
void  ncp_free(void *ptr);
/* void  ncp_hr_gettime_us(ncp_timespec_us_t *timespec); */
/* int   ncp_hr_time_compare(ncp_timespec_us_t *timespecStart_us, ncp_timespec_us_t *timespecEnd_us); */
/* void  ncp_hr_addtime_us(ncp_timespec_us_t *timespecStart_us, ncp_timespec_us_t *timespecEnd_us, ncp_uint64_t uSecs); */
#define NCP_S32       ncp_int32_t
NCP_S32 ncp_bitmap_delete(ncp_bitmap_t *map);
void *mmap_stub(void *start, size_t length, void *physAddr);

#endif /* NCP_STATUS_H */
