/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/

/*! @file      ncp_sal.h
    @brief     OS Specific definitions are located here. 
*/


#ifndef __NCP_SAL_H__
#define __NCP_SAL_H__

#include "uboot/ncp_types.h"
#include "uboot/ncp_sal_types.h"
#include "uboot/ncp_sal_linux.h"

#ifdef __cplusplus
extern "C" { 
#endif

#ifdef NCP_VALGRIND

#include "valgrind.h"

#else

#define	VALGRIND_CREATE_MEMPOOL(x,y,z);
#define	VALGRIND_DESTROY_MEMPOOL(x);
#define	VALGRIND_MAKE_MEM_NOACCESS(x,y);
#define VALGRIND_MALLOCLIKE_BLOCK(a,b,c,d);
#define VALGRIND_FREELIKE_BLOCK(a,b);

#endif /* #ifdef NCP_VALGRIND */


/* should not be in sal */
#ifndef MIN
#define MIN(a, b)        ((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a, b)        ((a) > (b) ? (a) : (b))
#endif


/*
 * Common byte swapping macros
 */
 
#define NCP_ENDIAN_SWAP_16(value)                          \
({                                                         \
     ncp_uint16_t  _val_= (ncp_uint16_t)value, _val1_;     \
     _val1_ = ( ((((_val_) & 0x00FF)) << 8) |              \
                ((((_val_) & 0xFF00)) >> 8));              \
      _val1_;                                              \
})    

#define NCP_ENDIAN_SWAP_32(value)                           \
({                                                          \
     ncp_uint32_t _val_ = (ncp_uint32_t)value, _val1_;      \
     _val1_ = (((((_val_) & 0x000000FF)) << 24) |           \
               ((((_val_) & 0x0000FF00)) << 8) |            \
               ((((_val_) & 0x00FF0000)) >> 8) |            \
               ((((_val_) & 0xFF000000)) >> 24)) ;          \
     _val1_; \
})   

#define	NCP_ENDIAN_SWAP_64(value)                               \
({                                                              \
    ncp_uint64_t _val_ = (ncp_uint64_t)(value), _val1_;         \
    _val1_ = (((ncp_uint64_t)(_val_) << 56) |                   \
    (((ncp_uint64_t)(_val_) << 40) & 0xff000000000000ULL) |     \
    (((ncp_uint64_t)(_val_) << 24) & 0xff0000000000ULL) |       \
    (((ncp_uint64_t)(_val_) << 8)  & 0xff00000000ULL) |         \
    (((ncp_uint64_t)(_val_) >> 8)  & 0xff000000ULL) |           \
    (((ncp_uint64_t)(_val_) >> 24) & 0xff0000ULL) |             \
    (((ncp_uint64_t)(_val_) >> 40) & 0xff00ULL) |               \
    ( (ncp_uint64_t)(_val_) >> 56));                            \
    _val1_;                                                     \
})  
            


#ifdef NCP_BIG_ENDIAN
#define NCP_HOST_TO_PCI16(n) NCP_ENDIAN_SWAP_16(n)
#define NCP_HOST_TO_PCI32(n) NCP_ENDIAN_SWAP_32(n)

#else
#define NCP_HOST_TO_PCI16(n) (n)
#define NCP_HOST_TO_PCI32(n) (n)
#endif /* NCP_BIG_ENDIAN */

#define NCP_PCI_TO_HOST16(n) NCP_HOST_TO_PCI16(n)
#define NCP_PCI_TO_HOST32(n) NCP_HOST_TO_PCI32(n)

/* Common macros to convert long integer to string */

#define NCP_CONVERT_LONG_TO_STR(val)     \
  ({                                     \
    char __i64str[22];                   \
    ncp_sprint_int64(__i64str, (val));   \
    __i64str;                            \
   })

#define NCP_CONVERT_ULONG_TO_STR(val)    \
  ({                                     \
    char __u64str[22];                   \
    ncp_sprint_uint64(__u64str, (val));  \
    __u64str;                            \
   })

#define NCP_CONVERT_LONG_TO_HEX_STR(val)   \
  ({                                       \
    char __x64str[22];                     \
    ncp_sprint_hexuint64(__x64str, (val)); \
    __x64str;                              \
   })


#define NCP_CONVERT_LONG_TO_HEX_STR_FORMAT(fmt, val)   \
  ({                                                   \
    char __x64str[22];                                 \
    ncp_sprint_hexuint64_format(__x64str, fmt, (val)); \
    __x64str;                                          \
   })

#ifndef NCP_I2C_DIV64_BY_32
#define NCP_I2C_DIV64_BY_32(div64,div32)	((div64)/(div32))
#endif

/*!
 * Common NCP String functions
 */
NCP_API int ncp_strlen(const char *s);
NCP_API char *ncp_strcpy(char *dest, const char *src);
NCP_API int ncp_stricmp(const char *s1, const char *s2);
NCP_API int ncp_strincmp(const char *s1, const char *s2, ncp_size_t n);
NCP_API char *ncp_strdup(const char *str);

/* New secure-code string APIs */
NCP_API size_t ncp_strnlen(const char *s, size_t maxLen);



#define NCP_MEMXXX_APIS_ARE_FUNCTIONS

#ifdef NCP_MEMXXX_APIS_ARE_FUNCTIONS
NCP_API void *ncp_memcpy(void *to, const void *from, ncp_uint32_t size);
NCP_API ncp_uint32_t ncp_memcmp(const void *m1, const void *m2, ncp_uint32_t size);
NCP_API void *ncp_memset(void *m, ncp_uint8_t val, ncp_uint32_t size);
#else
#define ncp_memcpy memcpy
#define ncp_memcmp memcmp
#define ncp_memset memset
#endif

/*!
 * NVM Access interface 
 */
/*!
 * pointers which are maintained by the API. These are allocated
 * at the beginning of the NVM segment by the API, they are not
 * managed by the mpm library.
 */
#define NCP_NVM_MAX_USER_POINTERS 11

#ifdef NCP_USE_NVM
#include "uboot/mp_malloc.h"

#define NCP_NVM_COOKIE       (0x4E564D41)

#ifdef NCP_DEBUG
#define NCP_NVM_INIT_ERR(s) \
    do { \
        printf("%s, line = %d\n", __FILE__,__LINE__); \
        (s); \
    } while (0);
#else
#define NCP_NVM_INIT_ERR(s)
#endif


typedef struct ncp_nvm_addr_s {
    char            *base;
    char            *nxt_avail;
    mp_info         *mp_info_ptr;
    ncp_uint32_t     cookie;
    void            *rootPtr;
    void            *userPtr[NCP_NVM_MAX_USER_POINTERS];
    ncp_mutex_t      nvmLock;
    ncp_bool_t      nvmActive;
} ncp_nvm_addr_t;


/*!
 * NCP_NVM_MAX_SIZE is set to preserve a 1MB aligned memory segment,
 * which will be used for DMA buffers/queues.
 */
#define NCP_NVM_MAX_SIZE     ((255 * 0x100000) - 4)

#endif /* #ifdef NCP_USE_NVM */

/* NVM stats */
typedef struct ncp_nvm_stats_s {
    ncp_uint32_t     bytes_total;
    ncp_uint32_t     chunks_used;
    ncp_uint32_t     bytes_used;
    ncp_uint32_t     chunks_free;
    ncp_uint32_t     bytes_free;
    ncp_uint32_t     nxt_avail_addr;
} ncp_nvm_stats_t;

/* NVM Access Interface Function Prototypes */
NCP_API int   ncp_nvm_init(ncp_bool_t coldStart);
NCP_API int   ncp_nvm_munmap(void);
NCP_API void  ncp_nvm_stats_get(ncp_nvm_stats_t *nvmStats);
NCP_API void *ncp_nvm_ptr_get(void);
NCP_API void  ncp_nvm_ptr_set(void * rootPtr);
NCP_API void *ncp_nvm_user_ptr_get(int idx);
NCP_API void  ncp_nvm_user_ptr_set(int idx, void * rootPtr);
NCP_API ncp_bool_t ncp_nvm_is_enabled(void);
NCP_API ncp_bool_t ncp_nvm_is_active(void);  /* Deprecated */
NCP_API ncp_st_t ncp_nvm_prefault(void);



#if !defined (NCP_LEAK_DEBUG)
/*
 * not NCP_LEAK_DEBUG, just declare the functions 
 */
NCP_API void *ncp_malloc(ncp_size_t size);
NCP_API void *ncp_realloc(void *ptr, ncp_size_t size);
NCP_API void *ncp_calloc(ncp_size_t no, ncp_size_t size);
NCP_API void  ncp_free(void *ptr);

/* The following ncp_nvm_* APIs are deprecated!   Use the new ncp_nvm_robust_* APIs instead.
 * and invoke them with NCP_CALL in order to handle robust mutex errors!
 *
 * The nvm_*alloc functions always exist, but are defined 
 * differently depending on whether NCP_USE_NVM is defined.
 */
NCP_API void *ncp_nvm_malloc(ncp_size_t size);
NCP_API void *ncp_nvm_realloc(void *ptr, ncp_size_t size);
NCP_API void *ncp_nvm_calloc(ncp_size_t no, ncp_size_t size);
NCP_API void  ncp_nvm_free(void *ptr);

#endif


/* 
 * New NVM APIs,   with support for robust mutexes
 *
 * Use the new NCP_NVM_ROBUST_* macros to invoke the ncp_nvm_robust_* APIs below instead of calling the ncp_nvm_* 
 * APIs listed above,   which are now deprecated!
 *
 * Invoke these with NCP_CALL (e.g. NCP_CALL(ncp_nvm_robust_malloc(sz, &ptr, doMemset)); ), in order to handle robust mutex errors!   
 * If calling from beyond the NCP_RETURN_LABEL, then consider passing any EOWNERDEAD error returned by these APIs back to the caller,   
 * as it most likely more serious than any current error,   and is expected to cause the caller to perform a system restart of some sort.
 */
 
NCP_API ncp_st_t ncp_nvm_robust_malloc(ncp_size_t size, void **ptr, ncp_bool_t doMemset);
NCP_API ncp_st_t ncp_nvm_robust_realloc(void *origPtr, ncp_size_t size, void **ptr);
NCP_API ncp_st_t ncp_nvm_robust_calloc(ncp_size_t no, ncp_size_t size, void **ptr);
NCP_API ncp_st_t ncp_nvm_robust_free(void **pPtr);
NCP_API ncp_st_t ncp_nvm_robust_is_active(ncp_bool_t *pIsActive);

/*
 * MISC APIs
 */
NCP_API int ncp_sys_usleep(unsigned long n);
NCP_API void ncp_host_to_pci_buf32(ncp_uint32_t *buf, int count);

typedef enum
{
    cBigEndian = 0,
    cLittleEndian = 1
} ncp_byte_order_t;

NCP_API ncp_byte_order_t ncp_get_byte_order(void);

NCP_API void ncp_convert_to_le(char *s, const char *bp, int len);
NCP_API void ncp_convert_to_be(char *s, const char *bp, int len);

typedef enum ncp_mem_map_e {
    ncp_mem_map_nvm_prepare,
    ncp_mem_map_nvm_attach,
    ncp_mem_map_task_mmio_prepare,
    ncp_mem_map_task_mmio_attach,
    ncp_mem_map_task_gsm_prepare,
    ncp_mem_map_task_gsm_attach,
    ncp_mem_map_task_lcm_prepare,
    ncp_mem_map_task_lcm_attach       
} ncp_mem_map_t;


enum {
    NCP_DEV_LBI_INTR_WAIT,
    NCP_DEV_LBI_CS_CONFIG,
    NCP_DEV_LBI_GPIO_CONFIG,
    NCP_DEV_LBI_GPIO_READ,
    NCP_DEV_LBI_GPIO_WRITE
};

#if defined(PROC_PPC476)

#define SPRN_TBL 268 /*0x10C*/
#define SPRN_TBU 269 /*0x10D*/

#define __stringify_1__(x)    #x
#define __stringify__(x)      __stringify_1__(x)


#define __mfspr__(rn)   ({unsigned long rval;                                   \
            __asm__ __volatile__("mfspr %0," __stringify__(rn)                  \
                : "=r" (rval)); rval; })

#define ncp_gettime_highres(timestamp)                                          \
{                                                                               \
    ncp_uint32_t *__pUpper = (ncp_uint32_t *)&timestamp;                        \
    ncp_uint32_t *__pLower = __pUpper + 1;                                      \
    ncp_uint32_t __upper1;                                                      \
    ncp_uint32_t __upper2;                                                      \
                                                                                \
    do                                                                          \
    {                                                                           \
        __upper1 = __mfspr__(SPRN_TBU);                                         \
        *__pLower = __mfspr__(SPRN_TBL);                                        \
        __upper2  = __mfspr__(SPRN_TBU);                                        \
    } while (__upper1 != __upper2);                                             \
    *__pUpper = __upper1;                                                       \
}

#else /* #if defined(PROC_PPC476) */

#define ncp_gettime_highres(timestamp)

#endif /* #if defined(PROC_PPC476) */

/* 
 * Common mutex macros.   
 * Use these interfaces,   and not the underlying implementations!
 */
 
#define NCP_MUTEX_INIT(_pMutex, _shared) ncp_mutex_init(_pMutex, _shared)

#define NCP_MUTEX_DESTROY(_pMutex)       ncp_mutex_destroy(_pMutex)

#define NCP_MUTEX_LOCKED_FLAG_DECL(_lockedFlag) ncp_bool_t _lockedFlag = FALSE

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
    
 
#define NCP_DO_MEMSET       TRUE
#define NCP_DO_NOT_MEMSET   FALSE   
     

/* --- NCP trace level bit masks --- */
#define NCP_MSG_BITMASK_NONE                (0x00000000)
#define NCP_MSG_BITMASK_INFO                (0x00000001)
#define NCP_MSG_BITMASK_ERROR               (0x00000002)
#define NCP_MSG_BITMASK_ENTRY               (0x00000004)
#define NCP_MSG_BITMASK_EXIT                (0x00000008)
#define NCP_MSG_BITMASK_CALL                (NCP_MSG_BITMASK_ENTRY | NCP_MSG_BITMASK_EXIT)
#define NCP_MSG_BITMASK_IOR                 (0x00000010)
#define NCP_MSG_BITMASK_IOW                 (0x00000020)
#define NCP_MSG_BITMASK_IORW                (NCP_MSG_BITMASK_IOR | NCP_MSG_BITMASK_IOW)
#define NCP_MSG_BITMASK_MEM                 (0x00000040)
#define NCP_MSG_BITMASK_MDIO                (0x00000080)
#define NCP_MSG_BITMASK_DEBUG_MEM           (0x10000000)
#define NCP_MSG_BITMASK_DEBUG_IO            (0x20000000)
#define NCP_MSG_BITMASK_DEBUG               (0x40000000)
#define NCP_MSG_BITMASK_INTR                (0x80000000)
#define NCP_MSG_BITMASK_ALL                 (0xFFFFFFFF)

#ifdef NCP_LTTNG_DEFINE_LOGLEVELS

/* --- Mappings to LTTng loglevels --- */
#define NCP_MSG_INFO                TRACE_INFO
#define NCP_MSG_ERROR               TRACE_ERR
#define NCP_MSG_ENTRY               TRACE_DEBUG_FUNCTION
#define NCP_MSG_EXIT                TRACE_DEBUG_FUNCTION
#define NCP_MSG_CALL                TRACE_DEBUG_FUNCTION
#define NCP_MSG_IOR                 TRACE_DEBUG_MODULE
#define NCP_MSG_IOW                 TRACE_DEBUG_MODULE
#define NCP_MSG_MEM                 TRACE_DEBUG_UNIT
#define NCP_MSG_MDIO                TRACE_DEBUG_UNIT
#define NCP_MSG_DEBUG_MEM           TRACE_DEBUG_UNIT
#define NCP_MSG_DEBUG_IO            TRACE_DEBUG_UNIT
#define NCP_MSG_DEBUG               TRACE_DEBUG
#define NCP_MSG_INTR                TRACE_DEBUG_UNIT

/* --- Extra trace levels that map directly to LTTng loglevels --- */
#define NCP_MSG_EMERG               TRACE_EMERG
#define NCP_MSG_ALERT               TRACE_ALERT
#define NCP_MSG_CRIT                TRACE_CRIT
#define NCP_MSG_ERR                 TRACE_ERR
#define NCP_MSG_WARNING             TRACE_WARNING
#define NCP_MSG_NOTICE              TRACE_NOTICE
#define NCP_MSG_DEBUG_SYSTEM        TRACE_DEBUG_SYSTEM
#define NCP_MSG_DEBUG_PROGRAM       TRACE_DEBUG_PROGRAM
#define NCP_MSG_DEBUG_PROCESS       TRACE_DEBUG_PROCESS
#define NCP_MSG_DEBUG_MODULE        TRACE_DEBUG_MODULE
#define NCP_MSG_DEBUG_UNIT          TRACE_DEBUG_UNIT
#define NCP_MSG_DEBUG_FUNCTION      TRACE_DEBUG_FUNCTION
#define NCP_MSG_DEBUG_LINE          TRACE_DEBUG_LINE

#else

/* --- Mappings to NCP trace level bit masks --- */
#define NCP_MSG_NONE                NCP_MSG_BITMASK_NONE
#define NCP_MSG_INFO                NCP_MSG_BITMASK_INFO
#define NCP_MSG_ERROR               NCP_MSG_BITMASK_ERROR
#define NCP_MSG_ENTRY               NCP_MSG_BITMASK_ENTRY
#define NCP_MSG_EXIT                NCP_MSG_BITMASK_EXIT
#define NCP_MSG_CALL                NCP_MSG_BITMASK_CALL
#define NCP_MSG_IOR                 NCP_MSG_BITMASK_IOR
#define NCP_MSG_IOW                 NCP_MSG_BITMASK_IOW
#define NCP_MSG_IORW                (NCP_MSG_BITMASK_IOR | NCP_MSG_BITMASK_IOW)
#define NCP_MSG_MEM                 NCP_MSG_BITMASK_MEM
#define NCP_MSG_MDIO                NCP_MSG_BITMASK_MDIO
#define NCP_MSG_DEBUG_MEM           NCP_MSG_BITMASK_DEBUG_MEM
#define NCP_MSG_DEBUG_IO            NCP_MSG_BITMASK_DEBUG_IO
#define NCP_MSG_DEBUG               NCP_MSG_BITMASK_DEBUG
#define NCP_MSG_INTR                NCP_MSG_BITMASK_INTR
#define NCP_MSG_ALL                 NCP_MSG_BITMASK_ALL

/* -- Mappings for extra trace levels for LTTng --- */
#define NCP_MSG_EMERG               NCP_MSG_BITMASK_ERROR
#define NCP_MSG_ALERT               NCP_MSG_BITMASK_ERROR
#define NCP_MSG_CRIT                NCP_MSG_BITMASK_ERROR
#define NCP_MSG_ERR                 NCP_MSG_BITMASK_ERROR
#define NCP_MSG_WARNING             NCP_MSG_BITMASK_ERROR
#define NCP_MSG_NOTICE              NCP_MSG_BITMASK_INFO
#define NCP_MSG_DEBUG_SYSTEM        NCP_MSG_BITMASK_DEBUG
#define NCP_MSG_DEBUG_PROGRAM       NCP_MSG_BITMASK_DEBUG
#define NCP_MSG_DEBUG_PROCESS       NCP_MSG_BITMASK_DEBUG
#define NCP_MSG_DEBUG_MODULE        NCP_MSG_BITMASK_DEBUG
#define NCP_MSG_DEBUG_UNIT          NCP_MSG_BITMASK_DEBUG
#define NCP_MSG_DEBUG_FUNCTION      NCP_MSG_BITMASK_DEBUG
#define NCP_MSG_DEBUG_LINE          NCP_MSG_BITMASK_DEBUG

#endif /* ! LTTng */


#ifdef __cplusplus
}
#endif

#endif /* __NCP_SAL_H__ */
