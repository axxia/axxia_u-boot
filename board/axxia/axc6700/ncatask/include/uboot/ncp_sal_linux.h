/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2017, Intel Corporation.                        *
 **                                                                       *
 **************************************************************************/

/*! @file      ncp_sal_linux.h
    @brief     OS Specific definitions are located here. 
*/


#ifndef __NCP_SAL_LINUX_H__
#define __NCP_SAL_LINUX_H__

#ifdef __KERNEL__
#ifdef NCP_DEV_PLB
#include <asm/dcr.h>
#endif

#else /* !#ifdef __KERNEL__ */

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/errno.h>
#include <unistd.h>
#define __USE_MISC 1
#include <sys/mman.h>
#include <syscall.h>
#include <inttypes.h>

#endif /* #ifdef __KERNEL__ */

#ifdef __cplusplus
extern "C" { 
#endif

#define NCP_SLEEP_POLL_INTERVAL 0

typedef ncp_waitq_t ncp_task_isr_wait_primitive_t;

/* RWXXX #include "ncp_modules.h" */
#if (1 == USE_EIOA)
#include "uboot/ncp_sal_types_linux.h"
#endif

/*
 * For use with higher resolution monotonic timers
 */
typedef struct {
    long        tv_sec;
    long        tv_usec;    
} ncp_timespec_us_t;
NCP_API void       ncp_hr_gettime_us(ncp_timespec_us_t *timespec);
NCP_API int        ncp_hr_time_compare(ncp_timespec_us_t *timespecStart_us, ncp_timespec_us_t *timespecEnd_us);
NCP_API void       ncp_hr_addtime_us(ncp_timespec_us_t *timespecStart_us, ncp_timespec_us_t *timespecEnd_us, ncp_uint64_t uSecs);

#if defined(NCP_USE_NVM) && !defined(NCP_NVM_VADDR)
/* 
 * For linux builds, the NCP_NVM_VADDR is now defined in the makefile.
 * Make sure that it really is defined
 */
#error "linux NCP_NVM_VADDR not defined - invalid RTE target ?!?"

#endif /* #if defined(NCP_USE_NVM) && !defined(NCP_NVM_VADDR) */

#define ncp_sprint_uint64(str, v)                 sprintf(str, "%" PRIu64, v);
#define ncp_sprint_int64(str, v)                  sprintf(str, "%" PRId64, v);
#define ncp_sprint_hexuint64(str, v)              sprintf(str, "%" PRIx64, v);
#define ncp_sprint_uint64_format(str, fmt, v)     sprintf(str, fmt PRIu64, v);
#define ncp_sprint_int64_format(str, fmt, v)      sprintf(str, fmt PRId64, v);
#define ncp_sprint_hexuint64_format(str, fmt, v)  sprintf(str, fmt PRIx64, v);


#define NCP_IRQ_TYPE_LEVEL_HIGH  IRQ_TYPE_LEVEL_HIGH
#define NCP_IRQ_TYPE_EDGE_RISING IRQ_TYPE_EDGE_RISING

#undef __KERNEL__
#ifdef __KERNEL__

#ifndef NCP_KERNEL
#define NCP_KERNEL __KERNEL__
#endif

#else

#define NCP_EXPORT_SYMBOL(sym);

#endif /* #ifdef __KERNEL__ */

#ifdef __KERNEL__

#define NCP_EXPORT_SYMBOL(sym);
//#define NCP_EXPORT_SYMBOL(sym) EXPORT_SYMBOL(sym)


#define NCP_TASK_ISR_EVENT_WAIT_TIMEOUT_VAL (HZ)
#define NCP_SE_FEM_ISR_EVENT_WAIT_TIMEOUT_VAL NCP_TASK_ISR_EVENT_WAIT_TIMEOUT_VAL
#define NCP_TIMER_ISR_EVENT_WAIT_TIMEOUT_VAL NCP_TASK_ISR_EVENT_WAIT_TIMEOUT_VAL

#define NCP_TASK_ISR_WAIT_OBJECT_SUPPLEMENT_DECL(_x)

 
/* Use simple wait if preempt-RT linux */    
#ifdef NCP_USE_SWAIT /*  ======================================== */

#define NCP_WAITQ_ALLOC(_pWaitQ) \
    do { \
        *(_pWaitQ) = ncp_malloc(sizeof(struct swait_queue_head)); \
        init_swait_queue_head((struct swait_queue_head *)*(_pWaitQ)); \
    } while (0)

#define NCP_WAITQ_FREE(_pWaitQ) \
    do { \
        if (_pWaitQ != NULL) { \
            ncp_free(_pWaitQ); \
        } \
    } while (0)

#define NCP_WAITQ_WAIT(_pWaitQ, _cond) \
     (_pWaitQ ? swait_event_interruptible((*_pWaitQ), (_cond)) : -1)

#define NCP_WAITQ_WAIT_TIMEOUT(_pWaitQ, _cond, timeout)       \
     (_pWaitQ ? swait_event_interruptible_timeout((*_pWaitQ), (_cond), timeout) : -1)

#define NCP_WAITQ_WAKEUP(_pWaitQ) \
    (_pWaitQ ? swake_up_all((_pWaitQ)) : -1)
    
#else /* NCP_USE_SWAIT ======================================== */
/* use traditional waitq */

#define NCP_WAITQ_ALLOC(_pWaitQ) \
    do { \
        *(_pWaitQ) = ncp_malloc(sizeof(wait_queue_head_t)); \
        init_waitqueue_head((wait_queue_head_t *)*(_pWaitQ)); \
    } while (0)

#define NCP_WAITQ_FREE(_pWaitQ) \
    do { \
        if (_pWaitQ != NULL) { \
            ncp_free(_pWaitQ); \
        } \
    } while (0)
    
#define NCP_WAITQ_WAIT(_pWaitQ, cond)  \
    (_pWaitQ ? wait_event_interruptible(*(_pWaitQ), cond) : -1)

#define NCP_WAITQ_WAIT_TIMEOUT(_pWaitQ, cond, timeout) \
    (_pWaitQ ? wait_event_interruptible_timeout(( *(_pWaitQ)), cond, timeout) : -1)

#define NCP_WAITQ_WAKEUP(_pWaitQ) \
    (_pWaitQ ? wake_up_interruptible_all((wait_queue_head_t *)(_pWaitQ)) : -1)


#endif


#define NCP_SIGNAL_PENDING() \
    (signal_pending(current))

#define NCP_DEV_IRQ_MASK(dev, irq) \
    if (dev->irqMask) dev->irqMask(dev, irq) 


void
ncp_edev_cleanup_isr_info(ncp_uint32_t devNum);

void
ncp_edev_init_isr_info(ncp_uint32_t devNum, ncp_uint8_t grp, void * intrData);

void
ncp_edev_wakeup_thread(void *pIsrInfoOSspecific, int wakeupType);

#define NCP_CLEANUP_ISR_INFO(_devNum) \
    ncp_edev_cleanup_isr_info(_devNum)

#define NCP_INIT_ISR_INFO(_devNum, _grp, _intrData) \
    ncp_edev_init_isr_info(_devNum, _grp, (_intrData))

#define NCP_INTERRUPT_DISABLE(intLevel) \
    local_irq_save(intLevel)

#define NCP_INTERRUPT_ENABLE(intLevel) \
    local_irq_restore(intLevel)

#define NCP_SPINLOCK_SW_FLAGS(flags)

#define NCP_SPINLOCK_SW_INTERRUPT_DISABLE(pSem, flags) \
    spin_lock_bh(pSem)

#define NCP_SPINLOCK_SW_INTERRUPT_ENABLE(pSem, flags) \
    spin_unlock_bh(pSem)

#if 0
#define NCP_SPINLOCK_FLAGS(flags) \
    unsigned long flags = 0
#endif


#ifdef NCP_TARGET_NO_RAW_SPINLOCK
#define raw_spin_lock_init(_l)             spin_lock_init(_l)
#define raw_spin_lock(_l)                  spin_lock(_l)
#define raw_spin_unlock(_l)                spin_unlock(_l)
#define raw_spin_lock_irqsave(_l, _f)      spin_lock_irqsave(_l, _f)
#define raw_spin_unlock_irqrestore(_l, _f) spin_unlock_irqrestore(_l, _f)
#endif



#define NCP_RESCHEDULE() \
    schedule()

#define NCP_CAT_DELAY_SETUP
#define NCP_CAT_DELAY_PQM()
#define NCP_CAT_DELAY_FEMAC()
#define NCP_CAT_DELAY_REGISTER()
#define NCP_CAT_DELAY_REGISTER_ROW()

#define NCP_IN_INTERRUPT() \
    ( in_interrupt() || in_serving_softirq() )


extern int ncp_trace_level;
extern int ncp_i2c_mode;

#define ncp_udelay(n) udelay(n)

typedef pid_t ncp_pid_t;

#define ncp_get_pid()   \
    current->pid

/*
 * NCP_MSG
 *
 *   Print a message to the system console.
 */
#define NCP_MSG(type, ...)                 \
    do {                                            \
        if ((type) & ncp_trace_level) {             \
            if ((type) == NCP_MSG_ERROR) {          \
                printk(KERN_ERR "ncp: ERROR: ");    \
            } else {                                \
                printk(KERN_WARNING "ncp: ");       \
            }                                       \
            printk(__VA_ARGS__);                   \
        }                                           \
    } while (0)

#else /* !#ifdef __KERNEL__ */

extern int ncp_trace_level;

#define NCP_MSG(type, ...) \
    do { \
        if ((type) & ncp_trace_level) { \
            printf(__VA_ARGS__); \
        }    \
    } while (0)


NCP_API ncp_st_t ncp_screen_startup(int *lines, int *cols);

NCP_API ncp_uint16_t ncp_ntohs(ncp_uint16_t v);
NCP_API ncp_uint16_t ncp_htons(ncp_uint16_t v);
NCP_API ncp_uint32_t ncp_ntohl(ncp_uint32_t v);
NCP_API ncp_uint32_t ncp_htonl(ncp_uint32_t v);
NCP_API ncp_uint64_t ncp_ntohll(ncp_uint64_t v);
NCP_API ncp_uint64_t ncp_htonll(ncp_uint64_t v);

typedef struct {
    long        tv_sec;
    long        tv_nsec;
} ncp_timespec_t;

NCP_API void ncp_gettime(ncp_timespec_t *timespec);
NCP_API double ncp_gettime_elapsed(ncp_timespec_t *t1, ncp_timespec_t *t2);

#define ncp_sem_alloc() \
    ncp_malloc(sizeof(ncp_sem_t))

#define ncp_sem_free(pMutex) \
    ncp_free(pMutex)

typedef pid_t ncp_pid_t;

extern int getpid(void);

#define ncp_get_pid()   \
    getpid()

#define ncp_sleep(s)    \
    sleep(s)

#define ncp_udelay(n) ncp_usleep(n)

int ncp_create_exec_process(const char *name, 
                char *arg1, char *arg2, char *arg3, char *arg4, char *arg5);



 
ncp_st_t ncp_daemonize_self(void);

#define NCP_DAEMONIZE_SELF() ncp_daemonize_self()

#define NCP_DAEMON_EXIT()

#define kmemleak_not_leak(p)

#endif /* #ifdef __KERNEL__ */
typedef unsigned long  spinlock_t ;
typedef unsigned long  raw_spinlock_t ;
typedef struct {
    raw_spinlock_t raw;
    spinlock_t     cooked;
} ncp_isr_spinlock_t ;

/* Placing this here to avoid circular include in LTTng case */
/* RWXXX #include "ncp_tracepoint_linux.h" */

struct ncp_isr_lock_fns {
    void (*lock)   (ncp_isr_spinlock_t *lock, unsigned long *flags);
    void (*unlock) (ncp_isr_spinlock_t *lock, unsigned long flags);
};

extern struct ncp_isr_lock_fns ncp_isr_lock_cooked ;
extern struct ncp_isr_lock_fns ncp_isr_lock_raw ;

void ncp_isr_spin_lock_init(ncp_isr_spinlock_t *lock) ;
void ncp_isr_spin_lock_raw(ncp_isr_spinlock_t *lock, unsigned long *flags);
void ncp_isr_spin_unlock_raw(ncp_isr_spinlock_t *lock, unsigned long flags);
void ncp_isr_spin_lock_cooked(ncp_isr_spinlock_t *lock, unsigned long *flags);
void ncp_isr_spin_unlock_cooked(ncp_isr_spinlock_t *lock, unsigned long flags);

ncp_st_t
ncp_mutex_init(ncp_mutex_t *sem, ncp_int32_t shared);

ncp_st_t
ncp_mutex_lock(ncp_mutex_t *pMutex);

ncp_st_t
ncp_mutex_unlock(ncp_mutex_t *pMutex);

ncp_st_t
ncp_mutex_destroy(ncp_mutex_t *pMutex);


/*!
 * @fn ncp_sem_init(ncp_sem_t *sem, ncp_int32_t shared, ncp_uint32_t value)
 */
NCP_API ncp_st_t
ncp_sem_init(ncp_sem_t *sem, ncp_int32_t shared, ncp_uint32_t value);

/*!
 * @fn ncp_sem_post(ncp_sem_t *sem)
 */
NCP_API ncp_st_t
ncp_sem_post(ncp_sem_t *sem);

/*!
 * @fn ncp_sem_wait(ncp_sem_t *sem)
 */
NCP_API ncp_st_t
ncp_sem_wait(ncp_sem_t *sem);

/*!
 * @fn ncp_sem_trywait(ncp_sem_t *sem)
 */
NCP_API ncp_st_t
ncp_sem_trywait(ncp_sem_t *sem);

/*!
 * @fn ncp_sem_destroy(ncp_sem_t *sem)
 */
NCP_API ncp_st_t
ncp_sem_destroy(ncp_sem_t *sem);

#if (defined(NCP_ARCH_ARM)  && defined(NCP_BIG_ENDIAN))
#define in_8(addr)    ({ u8 __v = (*(__force volatile u8 *) (addr)); __v; })
#define in_be16(addr) ({ u16 __v = (*(__force volatile u16 *) (addr)); __v; })
#define in_be32(addr) ({ u32 __v = (*(__force volatile u32 *) (addr)); __v; })
#define in_le16(addr) ({ u16 __v = le16_to_cpu(*(__force volatile __le16 *) (addr)); __v; })
#define in_le32(addr) ({ u32 __v = le32_to_cpu(*(__force volatile __le32 *) (addr)); __v; })

#define out_8(addr,b)    (void)((*(__force volatile u8 *) (addr)) = (b))
#define out_be16(addr,w) (void)((*(__force volatile u16 *) (addr)) = (w))
#define out_be32(addr,l) (void)((*(__force volatile u32 *) (addr)) = (l))
#define out_le16(addr,w) (void)((*(__force volatile __le16 *) (addr)) = cpu_to_le16(w))
#define out_le32(addr,l) (void)((*(__force volatile __le32 *) (addr)) = cpu_to_le32(l))
#endif


#ifdef __KERNEL__

#define NCP_BUS_READ8(addr) \
    ((ncp_pio_read_delay > 0) ? \
        ncp_sys_usleep(ncp_pio_read_delay), \
            readb((volatile ncp_uint8_t *) (addr)) : \
    readb((volatile ncp_uint8_t *) (addr)))

#ifdef NCP_BIG_ENDIAN
#define NCP_BUS_READ16_ENDIAN(endian, addr) \
    ((ncp_pio_read_delay > 0) ? \
        ncp_sys_usleep(ncp_pio_read_delay), \
            in_##endian##16((volatile ncp_uint16_t *) (addr)) : \
    in_##endian##16((volatile ncp_uint16_t __iomem *) (addr)))
#else
#define NCP_BUS_READ16_ENDIAN(endian, addr) \
    ((ncp_pio_read_delay > 0) ? \
        ncp_sys_usleep(ncp_pio_read_delay), \
        endian##16_to_cpu(readw((volatile ncp_uint16_t *) (addr))) : \
        endian##16_to_cpu(readw((volatile ncp_uint16_t __iomem *) (addr))) )
#endif


#define NCP_BUS_READ16_LE(addr) NCP_BUS_READ16_ENDIAN(le, addr)

#define NCP_BUS_READ16_BE(addr) NCP_BUS_READ16_ENDIAN(be, addr)

#define NCP_BUS_READ16(addr, flags) \
    (flags & NCP_DEV_ACCESS_BIG_ENDIAN) ?   \
        NCP_BUS_READ16_BE(addr) : NCP_BUS_READ16_LE(addr)

#ifdef NCP_BIG_ENDIAN
#define NCP_BUS_READ32_ENDIAN(endian, addr) \
    ((ncp_pio_read_delay > 0) ? \
        ncp_sys_usleep(ncp_pio_read_delay), \
            in_##endian##32((volatile ncp_uint32_t __iomem *) (addr)) : \
        in_##endian##32((volatile ncp_uint32_t __iomem *) (addr)))
#else
#define NCP_BUS_READ32_ENDIAN(endian, addr) \
    ((ncp_pio_read_delay > 0) ? \
        ncp_sys_usleep(ncp_pio_read_delay), \
        endian##32_to_cpu(readl((volatile ncp_uint32_t __iomem *) (addr))) : \
        endian##32_to_cpu(readl((volatile ncp_uint32_t __iomem *) (addr))))
#endif 


#define NCP_BUS_READ32_LE(addr) NCP_BUS_READ32_ENDIAN(le, addr)

#define NCP_BUS_READ32_BE(addr) NCP_BUS_READ32_ENDIAN(be, addr)

#define NCP_BUS_READ32(addr, flags) \
    (flags & NCP_DEV_ACCESS_BIG_ENDIAN) ?   \
        NCP_BUS_READ32_BE(addr) : NCP_BUS_READ32_LE(addr)

#ifdef NCP_BIG_ENDIAN
#define NCP_BUS_READ64_ENDIAN(endian, addr) \
    ((ncp_pio_read_delay > 0) ? \
        ncp_sys_usleep(ncp_pio_read_delay), \
            in_##endian##64((volatile ncp_uint64_t __iomem *) (addr)) : \
        in_##endian##64((volatile ncp_uint64_t __iomem *) (addr)))
#else
#define NCP_BUS_READ64_ENDIAN(endian, addr) \
    ((ncp_pio_read_delay > 0) ? \
        ncp_sys_usleep(ncp_pio_read_delay), \
        endian##64_to_cpu(readq((volatile ncp_uint64_t __iomem *) (addr))) : \
        endian##64_to_cpu(readq((volatile ncp_uint64_t __iomem *) (addr))))
#endif 


#define NCP_BUS_READ64_LE(addr) NCP_BUS_READ64_ENDIAN(le, addr)

#define NCP_BUS_READ64_BE(addr) NCP_BUS_READ64_ENDIAN(be, addr)

#ifdef __LP64__
#define NCP_BUS_READ64(addr, flags) \
    (flags & NCP_DEV_ACCESS_BIG_ENDIAN) ?   \
        NCP_BUS_READ64_BE(addr) : NCP_BUS_READ64_LE(addr)
#else
#define NCP_BUS_READ64(addr, flags) \
    ((flags & NCP_DEV_ACCESS_BIG_ENDIAN) ?                                \
      (((ncp_uint64_t) NCP_BUS_READ32_BE(addr)) << 32) :                  \
       ((ncp_uint64_t) NCP_BUS_READ32_LE(addr))) |                        \
    ((flags & NCP_DEV_ACCESS_BIG_ENDIAN) ?                                \
       ((ncp_uint64_t) NCP_BUS_READ32_BE((((ncp_uint8_t *) addr) + 4))) : \
      (((ncp_uint64_t) NCP_BUS_READ32_LE((((ncp_uint8_t *) addr) + 4))) << 32))
#endif


#define NCP_BUS_WRITE8(addr, data) \
    ((ncp_pio_write_delay > 0) ? \
        ncp_sys_usleep(ncp_pio_write_delay), \
            writeb((data), (volatile ncp_uint8_t *)(addr)) : \
    writeb((data), (volatile ncp_uint8_t *) (addr)) )

#ifdef NCP_BIG_ENDIAN
#define NCP_BUS_WRITE16_ENDIAN(endian, addr, data) \
    do { \
        ncp_uint16_t * __a__ = (ncp_uint16_t *) addr; \
        ncp_uint16_t __d__ = data; \
        if (ncp_pio_write_delay > 0) ncp_sys_usleep(ncp_pio_write_delay); \
        out_##endian##16((volatile ncp_uint16_t __iomem *) __a__, __d__); \
        NCP_EDEV_BUS_ENFORCE_ORDERING(); \
    } while (0);
#else
#define NCP_BUS_WRITE16_ENDIAN(endian, addr, data) \
    do { \
        ncp_uint16_t * __a__ = (ncp_uint16_t *) addr; \
        ncp_uint16_t __d__ = cpu_to_##endian##16(data); \
        if (ncp_pio_write_delay > 0) ncp_sys_usleep(ncp_pio_write_delay); \
        writew(__d__,(volatile ncp_uint16_t __iomem *) __a__); \
        NCP_EDEV_BUS_ENFORCE_ORDERING(); \
    } while (0);
#endif

#define NCP_BUS_WRITE16_LE(addr, data) \
    NCP_BUS_WRITE16_ENDIAN(le, addr, data) \

#define NCP_BUS_WRITE16_BE(addr, data) \
    NCP_BUS_WRITE16_ENDIAN(be, addr, data) \

#define NCP_BUS_WRITE16(addr, data, flags) \
    if (flags & NCP_DEV_ACCESS_BIG_ENDIAN) {   \
         NCP_BUS_WRITE16_BE(addr, data);    \
    } else {                                     \
         NCP_BUS_WRITE16_LE(addr, data);    \
    }

#ifdef NCP_BIG_ENDIAN
#define NCP_BUS_WRITE32_ENDIAN(endian, addr, data) \
    do { \
        ncp_uint32_t * __a__ = (ncp_uint32_t *) addr; \
        ncp_uint32_t __d__ = data; \
        if (ncp_pio_write_delay > 0) ncp_sys_usleep(ncp_pio_write_delay); \
        out_##endian##32((volatile ncp_uint32_t __iomem *) __a__, __d__); \
        NCP_EDEV_BUS_ENFORCE_ORDERING(); \
    } while (0);
#else
#define NCP_BUS_WRITE32_ENDIAN(endian, addr, data) \
    do { \
        ncp_uint32_t * __a__ = (ncp_uint32_t *) addr; \
        ncp_uint32_t __d__ = cpu_to_##endian##32(data); \
        if (ncp_pio_write_delay > 0) ncp_sys_usleep(ncp_pio_write_delay); \
        writel(__d__, (volatile ncp_uint32_t __iomem *) __a__); \
        NCP_EDEV_BUS_ENFORCE_ORDERING(); \
    } while (0);
#endif

#define NCP_BUS_WRITE32_LE(addr, data) \
    NCP_BUS_WRITE32_ENDIAN(le, addr, data) \

#define NCP_BUS_WRITE32_BE(addr, data) \
    NCP_BUS_WRITE32_ENDIAN(be, addr, data) \

#define NCP_BUS_WRITE32(addr, data, flags) \
    if (flags & NCP_DEV_ACCESS_BIG_ENDIAN) {   \
         NCP_BUS_WRITE32_BE(addr, data);    \
    } else {                                     \
         NCP_BUS_WRITE32_LE(addr, data);    \
    }

#ifdef NCP_BIG_ENDIAN
#define NCP_BUS_WRITE64_ENDIAN(endian, addr, data) \
    do { \
        ncp_uint64_t * __a__ = (ncp_uint64_t *) addr; \
        ncp_uint64_t __d__ = data; \
        if (ncp_pio_write_delay > 0) ncp_sys_usleep(ncp_pio_write_delay); \
        out_##endian##64((volatile ncp_uint64_t __iomem *) __a__, __d__); \
        NCP_EDEV_BUS_ENFORCE_ORDERING(); \
    } while (0);
#else
#define NCP_BUS_WRITE64_ENDIAN(endian, addr, data) \
    do { \
        ncp_uint64_t * __a__ = (ncp_uint64_t *) addr; \
        ncp_uint64_t __d__ = cpu_to_##endian##64(data); \
        if (ncp_pio_write_delay > 0) ncp_sys_usleep(ncp_pio_write_delay); \
        writeq(__d__, (volatile ncp_uint64_t __iomem *) __a__); \
        NCP_EDEV_BUS_ENFORCE_ORDERING(); \
    } while (0);
#endif

#define NCP_BUS_WRITE64_LE(addr, data) \
    NCP_BUS_WRITE64_ENDIAN(le, addr, data) \

#define NCP_BUS_WRITE64_BE(addr, data) \
    NCP_BUS_WRITE64_ENDIAN(be, addr, data) \

#ifdef __LP64__
#define NCP_BUS_WRITE64(addr, data, flags)   \
    if (flags & NCP_DEV_ACCESS_BIG_ENDIAN) { \
         NCP_BUS_WRITE64_BE(addr, data);     \
    } else {                                 \
         NCP_BUS_WRITE64_LE(addr, data);     \
    }
#else
#define NCP_BUS_WRITE64(addr, data, flags)                                    \
    if (flags & NCP_DEV_ACCESS_BIG_ENDIAN) {                                  \
         NCP_BUS_WRITE32_BE(addr, data >> 32);                                \
         NCP_BUS_WRITE32_BE((((ncp_uint8_t *) addr) + 4), data & 0xffffffff); \
    } else {                                                                  \
         NCP_BUS_WRITE32_LE(addr, data & 0xffffffff);                         \
         NCP_BUS_WRITE32_LE((((ncp_uint8_t *) addr) + 4), data >> 32);        \
    }
#endif


void *
ncp_dma_mem_map(
        ncp_uint32_t devNum,
        ncp_uint64_t physAddr,
        ncp_uint64_t size);

void *
ncp_mem_map(
        ncp_uint32_t devNum,
        ncp_uint64_t physAddr,
        ncp_uint64_t size);

#define NCP_DMA_MEM_MAP(_devNum, _physAddr, _size) \
        ncp_dma_mem_map(_devNum, _physAddr, _size)

#define NCP_DMA_MEM_UNMAP(_devNum, _dmaAddrPtr) \
    if (_dmaAddrPtr) {                              \
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_dma_mem_unmap, NCP_MSG_DEBUG_MEM, "NCP_DMA_MEM_UNMAP %p\r\n",_dmaAddrPtr); \
        iounmap((void *)(_dmaAddrPtr));             \
    }

#define NCP_MEM_MAP(_devNum, _physAddr, _size) \
        ncp_mem_map(_devNum, _physAddr, _size)

#define NCP_MEM_UNMAP(_devNum, _addrPtr) \
    if ((_addrPtr)) {                              \
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_mem_unmap, NCP_MSG_DEBUG_MEM, "NCP_MEM_UNMAP %p\r\n",_addrPtr); \
        iounmap((void *)(_addrPtr));               \
    }
    
#define NCP_TIMER_ADD(pTimer, timerFunc, timerFuncArg, duration) \
    (ncp_edev_timer_add(pTimer, timerFunc, timerFuncArg, duration))

#define NCP_TIMER_MOD(pTimer, duration) \
    (ncp_edev_timer_mod(pTimer, duration))

#define NCP_TIMER_CANCEL(pTimer) \
    (ncp_edev_timer_cancel(pTimer))

#define NCP_TIMER_CANCEL_SYNC(pTimer) \
    (ncp_edev_timer_cancel_sync(pTimer))

#define NCP_COPY_FROM_USER(to, from, size) \
    copy_from_user((void *)(to), (void *)(from), (unsigned long)(size))

#define NCP_COPY_TO_USER(to, from, size) \
    copy_to_user((void *)(to), (void *)(from), (unsigned long)(size))



#define NCP_RESCHEDULE() \
    schedule()


/* The definition of NCP_IOREMAP_CACHE varies depending
 * on the linux version/architecture. It is defined in
 * ncp_sal_linux_<target>.h
 */

#define NCP_IOREMAP_NOCACHE(_addr, _size)                                      \
({                                                                             \
    void *__p;                                                                 \
    __p = ioremap_nocache(_addr, _size);                                       \
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_ioremap_nocache, NCP_MSG_DEBUG_MEM, "NCP_IOREMAP_NOCACHE mapped %llx sz=%llx VA %p\r\n", _addr, _size, __p); \
    __p;                                                                       \
})    


#if defined(NCP_ARCH_ARM)
#define NCP_IOREMAP_DMA(_addr, _size) NCP_IOREMAP_NOCACHE(_addr, _size)
#else
#ifdef NCP_NCA_COHERENT_IO
#define NCP_IOREMAP_DMA(_addr, _size) NCP_IOREMAP_CACHE(_addr, _size)
#else 
#define NCP_IOREMAP_DMA(_addr, _size) NCP_IOREMAP_NOCACHE(_addr, _size)
#endif
#endif


#ifdef NCP_DEV_PLB

/*
 * PLB bus adaptor definitions
 * NOTE: This needs to be in sync with the BSP.
 *
 * For linux we define the APB Base VA as NULL,
 * the bus adaptor will do the mapping.
 */

#define NCP_DEV_PLB_APB_BASE_VADDR  NULL
 
#define NCP_DEV_PLB_MPIC1_DCR_BASE  0xEFC00000
#define NCP_DEV_PLB_MPIC0_DCR_BASE  0xFFC00000


/* DCR access from the internal core uses a special PPC instruction */
#define NCP_DCR_WRITE32(dcrAddr, val)  \
    mtdcr(dcrAddr, val)

#define NCP_DCR_READ32(dcrAddr) \
    mfdcr(dcrAddr)

#endif /* #ifdef NCP_DEV_PLB */

#endif /* #ifdef __KERNEL__ */

#ifdef __KERNEL__

#define ncp_task_buf_os_alloc(size)                 \
    ({                                              \
        struct sk_buff *__skb;                      \
        /* Allocate sk_buff */                      \
        __skb = dev_alloc_skb(size + NET_IP_ALIGN); \
        if(__skb != NULL) {                         \
            skb_reserve(__skb, NET_IP_ALIGN);       \
        }                                           \
        __skb;                                      \
    })

#define ncp_task_buf_os_free(taskAddr)  \
    kfree_skb((struct sk_buff *)taskAddr)

#define ncp_task_buf_data(skb)  \
    ((struct sk_buff *)(skb))->data

#else

#define NCP_USER_MEM_UNMAP(addrPtr, len)          \
    if ((addrPtr)) {                              \
        munmap((void *)(addrPtr), len);           \
    }


#define ncp_task_buf_os_alloc(size)     \
    ncp_nvm_malloc(size)

#define ncp_task_buf_os_free(taskAddr)  \
    ncp_nvm_free(taskAddr)

#define ncp_task_buf_data(buf)  \
    (buf)

NCP_API int snprintf(char *s, 
                     size_t n,
                     const char *format, 
                     ...);

#endif

#ifdef __KERNEL__

/*
 * we now define the kernel mode malloc to always use the 
 * GFP_KERNEL flag. It should never be called from atomic
 * context. We use the 'in_atomic()' macro to catch any 
 * case where it is incorrectly called from atomic context,
 * This should work on the preempt-rt kernel. The in_atomic()
 * macro is unreliable for non-preempt kernels, but as long 
 * as the calling code is correct it shouldn't matter. 
 */

#define __ncp_malloc(size)                  \
({                                          \
    void *__ptr = NULL;                     \
    if (in_atomic()) {                      \
        BUG();                              \
    } else {                                \
        __ptr = kmalloc(size, GFP_KERNEL);  \
    }                                       \
    __ptr;                                  \
}) 

#define __ncp_calloc(no, size)              \
({                                          \
    void *__ptr = NULL;                     \
    if (in_atomic()) {                      \
        BUG();                              \
    } else {                                \
        __ptr = kcalloc(no, size, GFP_KERNEL);      \
    }                                       \
    __ptr;                                  \
}) 

#define __ncp_free(ptr)                 kfree(ptr)
#define __ncp_realloc(ptr, size)        krealloc(ptr, size, GFP_KERNEL)

#define __ncp_nvm_malloc(size)          __ncp_malloc(size)
#define __ncp_nvm_free(ptr)             __ncp_free(ptr)
#define __ncp_nvm_realloc(ptr, size)    __ncp_realloc(ptr, size)
#define __ncp_nvm_calloc(no, size)      __ncp_calloc(no, size)


#define __ncp_nvm_robust_malloc(_size, _pPtr)                   \
({                                                              \
    ncp_st_t _st = NCP_ST_SUCCESS;                              \
    if (NULL == (*_pPtr = __ncp_malloc(_size)))                 \
    {                                                           \
        _st = NCP_ST_NO_MEMORY;                                 \
    }                                                           \
    _st;                                                        \
})

#define __ncp_nvm_robust_realloc(_origPtr, _size, _pPtr)        \
({                                                              \
    ncp_st_t _st = NCP_ST_SUCCESS;                              \
    if (NULL == (*_pPtr = __ncp_realloc(_origPtr, _size)))      \
    {                                                           \
        _st = NCP_ST_NO_MEMORY;                                 \
    }                                                           \
    _st;                                                        \
})

#define __ncp_nvm_robust_calloc(_num, _size, _pPtr)             \
({                                                              \
    ncp_st_t _st = NCP_ST_SUCCESS;                              \
    if (NULL == (*_pPtr = __ncp_calloc(_num, _size)))           \
    {                                                           \
        _st = NCP_ST_NO_MEMORY;                                 \
    }                                                           \
    _st;                                                        \
})

#define __ncp_nvm_robust_free(_ptr)                             \
({                                                              \
    ncp_st_t _st = NCP_ST_SUCCESS;                              \
    __ncp_free(_ptr);                                           \
    _st;                                                        \
})

#else /* !#ifdef __KERNEL__ */

#define __ncp_malloc(size)              malloc(size)
#define __ncp_free(ptr)                 free(ptr)
#define __ncp_realloc(ptr, size)        realloc(ptr, size)
#define __ncp_calloc(no, size)          calloc(no, size)

#ifdef NCP_USE_NVM

extern ncp_mutex_t *pNvmLock;
extern ncp_bool_t *pNvmActive;

#define __ncp_nvm_malloc(_size)                     \
    ({                                              \
        NCP_MUTEX_LOCKED_FLAG_DECL(_nvmLocked);     \
        void *__ptr = NULL;                         \
                                                    \
        if (NCP_ST_SUCCESS == NCP_MUTEX_LOCK(pNvmLock, &_nvmLocked))      \
        {                                           \
        	*pNvmActive = TRUE;         			\
            __ptr = mp_malloc((_size));             \
        	*pNvmActive = FALSE;         			\
        }                                           \
        NCP_MUTEX_UNLOCK(pNvmLock, &_nvmLocked);    \
        __ptr;                                      \
    })
    
#define __ncp_nvm_free(_ptr)                        \
    {                                               \
        NCP_MUTEX_LOCKED_FLAG_DECL(_nvmLocked);     \
        if (NCP_ST_SUCCESS == NCP_MUTEX_LOCK(pNvmLock, &_nvmLocked))      \
        {                                           \
        	*pNvmActive = TRUE;         			\
            mp_free(_ptr);                          \
        	*pNvmActive = FALSE;         			\
        }                                           \
        NCP_MUTEX_UNLOCK(pNvmLock, &_nvmLocked);    \
    }

#define __ncp_nvm_realloc(_origPtr, _size)          \
    ({                                              \
        NCP_MUTEX_LOCKED_FLAG_DECL(_nvmLocked);     \
        void *__ptr = NULL;                         \
        if (NCP_ST_SUCCESS == NCP_MUTEX_LOCK(pNvmLock, &_nvmLocked))      \
        {                                           \
        	*pNvmActive = TRUE;        			    \
            __ptr = mp_realloc(_origPtr, _size);    \
        	*pNvmActive = FALSE;         			\
        }                                           \
        NCP_MUTEX_UNLOCK(pNvmLock, &_nvmLocked);    \
        __ptr;                                      \
    })

#define __ncp_nvm_calloc(_no, _size)                \
    ({                                              \
        NCP_MUTEX_LOCKED_FLAG_DECL(_nvmLocked);     \
        void *__ptr = NULL;                         \
        if (NCP_ST_SUCCESS == NCP_MUTEX_LOCK(pNvmLock, &_nvmLocked))      \
        {                                           \
        	*pNvmActive = TRUE;         			\
            __ptr = mp_calloc(_no, _size);          \
        	*pNvmActive = FALSE;         			\
        }                                           \
        NCP_MUTEX_UNLOCK(pNvmLock, &_nvmLocked);    \
        __ptr;                                      \
    })


/*
 * NVM interfaces with Robust mutex support
 */

#define __ncp_nvm_robust_malloc(_size, _pPtr)  \
({                                              \
    ncp_st_t _st;                               \
    NCP_MUTEX_LOCKED_FLAG_DECL(_nvmLocked);     \
                                                \
    if (NCP_ST_SUCCESS == (_st = NCP_MUTEX_LOCK(pNvmLock, &_nvmLocked)))      \
    {                                           \
    	*pNvmActive = TRUE;         			\
        if (NULL == (*(_pPtr) = (void *)mp_malloc(_size)))    \
        {                                       \
            _st = NCP_ST_NO_MEMORY;             \
        }                                       \
    	*pNvmActive = FALSE;         			\
        NCP_MUTEX_UNLOCK(pNvmLock, &_nvmLocked);\
    }                                           \
    else                                        \
    {                                           \
        *_pPtr = NULL;                          \
    }                                           \
    _st;                                        \
})

#define __ncp_nvm_robust_calloc(_num, _size, _pPtr)             \
({                                                              \
    ncp_st_t _st = NCP_ST_SUCCESS;                              \
    NCP_MUTEX_LOCKED_FLAG_DECL(_nvmLocked);                     \
                                                                \
    if (NCP_ST_SUCCESS == (_st = NCP_MUTEX_LOCK(pNvmLock, &_nvmLocked)))      \
    {                                                           \
    	*pNvmActive = TRUE;         			                \
        if (NULL == (*(_pPtr) = mp_calloc(_num, _size)))       \
        {                                                       \
            _st = NCP_ST_NO_MEMORY;                             \
        }                                                       \
       	*pNvmActive = FALSE;         			                \
        NCP_MUTEX_UNLOCK(pNvmLock, &_nvmLocked);                \
    }                                                           \
    else                                                        \
    {                                                           \
        *_pPtr = NULL;                                          \
    }                                                           \
    _st;                                                        \
})

#define __ncp_nvm_robust_realloc(_origPtr, _size, _pPtr)   \
    ({                                              \
        ncp_st_t _st;                               \
        NCP_MUTEX_LOCKED_FLAG_DECL(_nvmLocked);     \
                                                    \
         if (NCP_ST_SUCCESS == (_st = NCP_MUTEX_LOCK(pNvmLock, &_nvmLocked)))      \
        {                                           \
        	*pNvmActive = TRUE;        			    \
            if (NULL == (*(_pPtr) = mp_realloc(_origPtr, _size)))   \
            {                                       \
                _st = NCP_ST_NO_MEMORY;             \
            }                                       \
        	*pNvmActive = FALSE;         			\
            NCP_MUTEX_UNLOCK(pNvmLock, &_nvmLocked);\
        }                                           \
        else                                        \
        {                                           \
            *_pPtr = NULL;                          \
        }                                           \
        _st;                                        \
    })
    
#define __ncp_nvm_robust_free(_ptr)                             \
({                                                              \
    ncp_st_t _st;                                               \
    NCP_MUTEX_LOCKED_FLAG_DECL(_nvmLocked);                     \
                                                                \
    if (NCP_ST_SUCCESS == (_st = NCP_MUTEX_LOCK(pNvmLock, &_nvmLocked)))      \
    {                                                           \
       	*pNvmActive = TRUE;         			                \
        mp_free(_ptr);                                          \
    	*pNvmActive = FALSE;         			                \
        NCP_MUTEX_UNLOCK(pNvmLock, &_nvmLocked);                \
    }                                                           \
    _st;                                                        \
})



#else

#define __ncp_nvm_malloc(size)          __ncp_malloc(size)
#define __ncp_nvm_free(ptr)             __ncp_free(ptr)
#define __ncp_nvm_realloc(ptr, size)    __ncp_realloc(ptr, size)
#define __ncp_nvm_calloc(no, size)      __ncp_calloc(no, size)


#define __ncp_nvm_robust_malloc(_size, _pPtr)                   \
({                                                              \
    ncp_st_t _st = NCP_ST_SUCCESS;                              \
    if (NULL == (*_pPtr = __ncp_malloc(_size)))                 \
    {                                                           \
        _st = NCP_ST_NO_MEMORY;                                 \
    }                                                           \
    _st;                                                        \
})

#define __ncp_nvm_robust_realloc(_origPtr, _size, _pPtr)        \
({                                                              \
    ncp_st_t _st = NCP_ST_SUCCESS;                              \
    if (NULL == (*_pPtr = __ncp_realloc(_origPtr, _size)))      \
    {                                                           \
        _st = NCP_ST_NO_MEMORY;                                 \
    }                                                           \
    _st;                                                        \
})

#define __ncp_nvm_robust_calloc(_num, _size, _pPtr)             \
({                                                              \
    ncp_st_t _st = NCP_ST_SUCCESS;                              \
    if (NULL == (*_pPtr = __ncp_calloc(_num, _size)))           \
    {                                                           \
        _st = NCP_ST_NO_MEMORY;                                 \
    }                                                           \
    _st;                                                        \
})


#define __ncp_nvm_robust_free(_ptr)                             \
({                                                              \
    ncp_st_t _st = NCP_ST_SUCCESS;                              \
    __ncp_free(_ptr);                                           \
    _st;                                                        \
})

#endif /* #ifdef NCP_USE_NVM */

NCP_API int
ncp_dev_udelay(unsigned long usecs);

NCP_API int
ncp_dev_mdelay(unsigned long msecs);

#endif /* #ifdef __KERNEL__ */

typedef struct ncp_task_pid_api_active_s {
    ncp_bool_t ce;
    ncp_bool_t eioa;
    ncp_bool_t eioaSwitch;
    ncp_bool_t mppSubnet;
    ncp_bool_t se;
    ncp_bool_t mtm;
    ncp_bool_t pll;
    ncp_bool_t sed;
    ncp_bool_t timer;
} ncp_task_pid_api_active_t;
#if !defined(__KERNEL__) && \
     defined(NCP_TASK_CPU_POOL_REINIT_AND_RESIZE_ENABLED)
extern volatile ncp_task_pid_api_active_t *pid_active;
#define UPDATE_API_ACTIVE(module, active, val) \
{                                 \
    active = val;                 \
    if (pid_active)               \
    {                             \
        pid_active->module = val; \
    }                             \
}
#else
#define UPDATE_API_ACTIVE(module, active, val) active = val
#endif

#ifdef __cplusplus
}
#endif

#endif /* __NCP_SAL_LINUX_H__ */
