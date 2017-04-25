/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/

/*! @file      ncp_sal_types_linux.h
    @brief     OS Specific types are located here. 
*/


#ifndef __NCP_SAL_TYPES_LINUX_H__
#define __NCP_SAL_TYPES_LINUX_H__

/**************************************************************************
* Platform Dependent Type Definitions
**************************************************************************/

#ifdef __KERNEL__

//#include <linux/version.h>
//#include <linux/types.h>
//#include <linux/wait.h>

/* ========== BEGIN: Addional feature control ============ */

#if !defined(NCP_SWAIT_DISABLE) && defined(CONFIG_PREEMPT_RT_BASE)
#define NCP_USE_SWAIT
#else   /* NCP_USES_LINUX_PREEMPT_RT */
#undef  NCP_USE_SWAIT
#endif /* NCP_SWAIT_DISABLE */

#ifdef CONFIG_PREEMPT_RT_BASE
/* 
 * The Kconfig option CONFIG_IRQ_FORCED_THREADING forces all irq handlers
 * registered via request irq into bottom-half handlers.
 * CONFIG_IRQ_FORCED_THREADING is a prerequisite for CONFIG_PREEMPT_RT_FULL, as
 * is CONFIG_PREEMPT_RT_BASE. But CONFIG_PREEMPT_RT_BASE does not depend on
 * CONFIG_IRQ_FORCED_THREADING. Since our CONFIG_PREEMPT_RT_BASE code assumes
 * the ISRs run threaded, we must check these definitions at compile-time.
 */
#ifndef CONFIG_IRQ_FORCED_THREADING
#error "The RTE's Preempt RT support assumes preemptible ISRs -- i.e., kernels built with CONFIG_PREEMPT_RT_FULL."
#endif

#endif /* CONFIG_PREEMPT_RT_BASE */

#undef  NCP_USE_ATOMIC
/* ========== END: Addional feature control ============ */


typedef long long               ncp_int64_t;
typedef unsigned long long      ncp_uint64_t;
typedef unsigned                ncp_uint32_t;
typedef long                    ncp_int32_t;
typedef unsigned short          ncp_uint16_t;
typedef unsigned char           ncp_uint8_t;
typedef unsigned char           ncp_bool_t;

/*
   typedef __s8   ncp_int8_t;
   typedef __u8   ncp_uint8_t;
   typedef __s16  ncp_int16_t;
   typedef __u16  ncp_uint16_t;
   typedef __s32  ncp_int32_t;
   typedef __u32  ncp_uint32_t;
   typedef __s64  ncp_int64_t;
   typedef __u64  ncp_uint64_t;
   typedef __u8   ncp_bool_t;
*/
    /* Some older BSPs don't define uintptr_t in linux/types.h */
    #ifdef __LP64__
    typedef ncp_uint64_t ncp_uintptr_t;
    #else
    typedef ncp_uint32_t ncp_uintptr_t;
    #endif

#ifdef __GNUC__
	typedef __SIZE_TYPE__       __kernel_size_t;
#else
	typedef unsigned int        __kernel_size_t;
#endif
typedef long         __kernel_ssize_t;


// LAPAJ BEGIN
#ifndef _SIZE_T
#define _SIZE_T
	typedef __kernel_size_t     size_t;
#endif
#ifndef _SSIZE_T
#define _SSIZE_T
typedef __kernel_ssize_t    ssize_t;
#endif

typedef size_t  ncp_size_t;
typedef ssize_t ncp_ssize_t;
typedef int wait_queue_head_t;
// LAPAJ END

#ifdef NCP_USE_SWAIT
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 6, 0)
     typedef struct swait_queue_head  ncp_waitq_t;
#else
     typedef struct swait_head  ncp_waitq_t;
#endif
#else
    typedef wait_queue_head_t ncp_waitq_t;
#endif

	struct semaphore {
		unsigned int		count;
		void *mutex;
		void *mutexAttr;
	};

    /* Note that ncp_sem_t is deprecated,   and will be replaced by ncp_mutex_t below */
    typedef struct semaphore ncp_sem_t; 
    
    typedef struct semaphore ncp_mutex_t;

/* 
 * Macros for format specifiers in kernel space,
 * These are available in user-space in inttypes.h
 * In the linux kernel, nearly all platforms use 'long long' for the 64-bit
 * types (source:
 * http://www.linux-mips.org/archives/linux-mips/2013-11/msg00134.html).
 */
#define PRId64    "lld"
#define PRIu64    "llu"
#define PRIx64    "llx"

#else /* __KERNEL__ */

#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>
#include <pthread.h>

    /* ncp_sem_t is deprecated,  and will be replaced by ncp_mutex_t below */
    typedef struct ncp_sem_st {
        pthread_mutex_t     mutex;
        pthread_mutexattr_t mutexAttr;
    } ncp_sem_t;    
    
    typedef struct ncp_mutex_s {
        pthread_mutex_t     mutex;
        pthread_mutexattr_t mutexAttr;
    } ncp_mutex_t;  

    typedef int8_t     ncp_int8_t;
    typedef int16_t    ncp_int16_t;
    typedef int32_t    ncp_int32_t;

    typedef __uint8_t  ncp_uint8_t;
    typedef __uint16_t ncp_uint16_t;
    typedef __uint32_t ncp_uint32_t;

    typedef __uint8_t  ncp_bool_t;

    typedef int64_t    ncp_int64_t;
    typedef __uint64_t ncp_uint64_t;

    typedef uintptr_t  ncp_uintptr_t;

    typedef size_t     ncp_size_t;
    typedef ssize_t    ncp_ssize_t;

    typedef void * ncp_waitq_t;
#endif /* __KERNEL__ */


typedef unsigned long spinlock_flags_t;

#define NCP_API extern

/****************************************************
 * Support for 32-bit applications on 64-bit kernels
*****************************************************/
/* 32-bit compatibility support. (Not currently defined)*/


#ifdef NCP_32_BIT_COMPAT

/* Align all packed structures on 8 byte boundaries so any 64-bit fields
 * specified as aligned within them will be properly aligned. */
#define NCP_COMPAT_PACKED __attribute__((packed, aligned (8)))

/* Make sure all 64-bit types are 8-byte aligned, since ARM cannot perform
 * unaligned 64-bit loads and stores. */
#define NCP_COMPAT_ALIGN64 __attribute__((aligned (8)))

#ifdef __LP64__

#define NCP_DECLARE_RAW_ADDR(a) \
    union {                       \
        ncp_uint64_t   a;         \
        ncp_uint64_t __p;         \
    } __attribute__((packed, aligned (8))) u_##a

#define NCP_DECLARE_RAW_ADDR_AND_ZEROINIT(a) \
    union {                       \
        ncp_uint64_t   a;         \
        ncp_uint64_t __p;         \
    } __attribute__((packed, aligned (8))) u_##a = {.__p=0LL}

#define NCP_DECLARE_POINTER(t, a) \
    union {                       \
        t *a;                     \
        ncp_uint64_t __p;         \
    } __attribute__((packed, aligned (8))) u_##a

#define NCP_DECLARE_POINTER_NOALIGN(t, a) \
    union {                       \
        t *a;                     \
        ncp_uint64_t __p;         \
    } __attribute__((packed)) u_##a

#define NCP_INIT_POINTER(a) {a}

#define NCP_DECLARE_POINTER_ARRAY(t, a, _n) \
    union {                                 \
        t *a[_n];                           \
        ncp_uint64_t __p[_n];               \
    } __attribute__((packed, aligned (8))) u_##a

#define NCP_INIT_POINTER_ARRAY(...) {{__VA_ARGS__}}

#define NCP_INIT_POINTER_VALUE(a) a

#define NCP_DECLARE_FN_POINTER(t, a) \
    union {                          \
        t a;                         \
        ncp_uint64_t __p;            \
    } __attribute__((packed, aligned (8))) u_##a

#define NCP_INIT_FN_POINTER(a) {a}

#define NCP_DECLARE_HDL(t, a) NCP_DECLARE_FN_POINTER(t, a)

#define NCP_RAW_ADDR(a) u_##a.a

#define NCP_POINTER(a) u_##a.a

#define NCP_POINTER_64(a) u_##a.__p

#define NCP_POINTER_ARRAY(a, idx) u_##a.a[idx]

/* Fixups are performed in user-space.
 * For 64-bit apps, no fix-up is required. */
#define NCP_POINTER_FIXUP(a)
#define NCP_RAW_ADDR_FIXUP(a)

#else

#define NCP_DECLARE_RAW_ADDR(a) \
    union {                       \
        struct {                  \
            ncp_uint32_t a1;      \
            ncp_uint32_t a2;      \
        } s;                      \
        ncp_uint64_t __p;         \
    } __attribute__((packed, aligned (8))) u_##a

#define NCP_DECLARE_RAW_ADDR_AND_ZEROINIT(a) \
    union {                       \
        struct {                  \
            ncp_uint32_t a1;      \
            ncp_uint32_t a2;      \
        } s;                      \
        ncp_uint64_t __p;         \
    } __attribute__((packed, aligned (8))) u_##a = {.__p=0LL}

#define NCP_DECLARE_POINTER(t, a) \
    union {                       \
        struct {                  \
            t *a1;                \
            t *a2;                \
        } s;                      \
        ncp_uint64_t __p;         \
    } __attribute__((packed, aligned (8))) u_##a

#define NCP_DECLARE_POINTER_NOALIGN(t, a) \
    union {                       \
        struct {                  \
            t *a1;                \
            t *a2;                \
        } s;                      \
        ncp_uint64_t __p;         \
    } __attribute__((packed)) u_##a

#define NCP_INIT_POINTER(a) {{a, NULL}}

#define NCP_DECLARE_POINTER_ARRAY(t, a, _n) \
    union {                                 \
        struct {                            \
            t *a1;                          \
            t *a2;                          \
        } s[_n];                            \
        ncp_uint64_t __p[_n];               \
    } __attribute__((packed, aligned (8))) u_##a

#define NCP_INIT_POINTER_ARRAY(...) {{__VA_ARGS__}}

#define NCP_INIT_POINTER_VALUE(a) {a, NULL}

#define NCP_DECLARE_FN_POINTER(t, a) \
    union {                          \
        struct {                     \
            t a1;                    \
            t a2;                    \
        } s;                         \
        ncp_uint64_t __p;            \
    } __attribute__((packed, aligned (8))) u_##a

#define NCP_INIT_FN_POINTER(a) {{a,NULL}}

#define NCP_DECLARE_HDL(t, a) NCP_DECLARE_FN_POINTER(t, a)

#ifdef NCP_BIG_ENDIAN
#define NCP_RAW_ADDR(a) u_##a.s.a2
#define NCP_POINTER(a) u_##a.s.a2
#define NCP_POINTER_ARRAY(a, idx) u_##a.s[idx].a2
#else
#define NCP_RAW_ADDR(a) u_##a.s.a1
#define NCP_POINTER(a) u_##a.s.a1
#define NCP_POINTER_ARRAY(a, idx) u_##a.s[idx].a1
#endif

#define NCP_POINTER_64(a) u_##a.__p
#define NCP_POINTER_ARRAY_64(a, idx) u_##a.s[idx].__p

/* Fixups are performed in user-space.
 * For 32-bit apps, fix-ups are required. */
#define NCP_RAW_ADDR_FIXUP(a) \
    *(ncp_uint64_t *)&a &= 0x00000000ffffffffULL

#define NCP_POINTER_FIXUP(a) \
    *(ncp_uint64_t *)&a &= 0x00000000ffffffffULL

#endif

#else /* NCP_32_BIT_COMPAT */

#ifdef __LP64__
#define NCP_DECLARE_RAW_ADDR(a) ncp_uint64_t a
#define NCP_DECLARE_RAW_ADDR_AND_ZEROINIT(a) ncp_uint64_t a = 0LL
#else
#define NCP_DECLARE_RAW_ADDR(a) ncp_uint32_t a
#define NCP_DECLARE_RAW_ADDR_AND_ZEROINIT(a) ncp_uint32_t a = 0
#endif

#define NCP_COMPAT_PACKED
#define NCP_COMPAT_ALIGN64
#define NCP_DECLARE_POINTER(t, a) t *a
#define NCP_DECLARE_POINTER_NOALIGN(t, a) t *a
#define NCP_DECLARE_POINTER_ARRAY(t, a, _n) t *a[_n]
#define NCP_DECLARE_FN_POINTER(t, a) t a
#define NCP_DECLARE_HDL(t, a) t a
#define NCP_RAW_ADDR(a) a
#define NCP_POINTER(a) a
#define NCP_POINTER_64(a) a
#define NCP_RAW_ADDR_FIXUP(a) 
#define NCP_POINTER_FIXUP(a)
#define NCP_POINTER_ARRAY(a, idx) a[idx]
#define NCP_POINTER_ARRAY_64(a, idx) a[idx]

#define NCP_INIT_POINTER_ARRAY(...) {__VA_ARGS__}
#define NCP_INIT_POINTER_VALUE(a) a
#define NCP_INIT_POINTER(a) a
#define NCP_INIT_FN_POINTER(a) a

#endif


#endif /* NCP_SAL_TYPES_LINUX_H */
