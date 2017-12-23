/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.              *
 **                                                                       *
 **************************************************************************/
#include <common.h>
#include <linux/types.h>
#include <linux/ctype.h>
#include <linux/byteorder/generic.h>
#include <linux/byteorder/little_endian.h>

#if (defined NCP_SAL_HOSTMEM_NVM) && (defined NCP_SAL_SHM_NVM)
#error "Both NCP_SAL_HOSTMEM_NVM and NCP_SAL_SHM_NVM are defined"
#endif

#ifndef _XOPEN_SOURCE
/*
 * A header file bug in glibc 2.12 meant that the minimum value of 
 * _POSIX_C_SOURCE required to expose the declaration of ftruncate() was 200809L 
 * instead of 200112L. This has been fixed in later glibc versions.
 */
// LAPAJ extern int ftruncate(int fd, __off_t length);
#endif

#include <common.h>
#include "uboot/ncp_sal_types_linux.h"
#include "uboot/ncp_task_basetypes.h"
#include "uboot/ncp.h"

#include "uboot/ncp_sal.h"
#include "uboot/ncp_dev.h"

/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */



#ifndef __KERNEL__

#ifdef NCP_DEBUG
int ncp_trace_level = (NCP_MSG_INFO | NCP_MSG_ERROR);
#else
int ncp_trace_level = 0;
#endif

/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * NVM Access Interface
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * The NVM Access Interface provides a means by which API state 
 * information can be stored in a non-volatile memory for the 
 * purpose of allowing a warm-restart. The interface consits of
 * a routine to memory map the NVM into the application address
 * space, a library of memory allocation functions (e.g. malloc)
 * which use the user provided memory pool, and routines to get
 * and set a pointer to the root API state information in NVM.
 *
 * The NVM is currently simulated by using file-backed memory
 * mapped I/O. On linux systems this could be modified to map
 * onto /dev/mem to allow access to a physical non-volatile memory.
 */

#ifdef NCP_USE_NVM

/*
 * in order to support optional runtime specification of the
 * NVM address, we now use a global variable for the ncp_nvm_vaddr
 */
static ncp_bool_t ncp_nvm_initialized = FALSE;
unsigned long ncp_nvm_vaddr = NCP_NVM_VADDR;
unsigned long ncp_nvm_size = NCP_NVM_MAX_SIZE;
ncp_mutex_t *pNvmLock = NULL;
ncp_bool_t *pNvmActive = NULL;

char *
ncp_nvm_mmap(void)
{
    char *pnvm_base         = NULL;
    return pnvm_base;
}

int
ncp_nvm_munmap(void)
{
    int rc;

    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_nvm_munmap_entry, NCP_MSG_ENTRY, 
        " ");
    rc = munmap((void *) ncp_nvm_vaddr, ncp_nvm_size);
    ncp_nvm_initialized = FALSE;

    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_nvm_munmap_exit, NCP_MSG_EXIT, 
        "rc=%d\n", rc);
    return rc;
}


ncp_st_t
ncp_nvm_prefault(void)
{
    ncp_st_t     ncpStatus = NCP_ST_SUCCESS;
    volatile ncp_uint8_t *nvm_ptr = (volatile ncp_uint8_t *) ncp_nvm_vaddr;
    ncp_uint8_t  origValue;
    ncp_bool_t   success = FALSE;
    ncp_uint32_t nloop;
    int i;


    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_nvm_prefault_entry, NCP_MSG_ENTRY, 
        " ");
    /*
     * loop through all pages and do a read-write from/to each page.
     * this will prefault all pages into memory so we don't take 
     * page faults when they are accessed during application runtime.
     */
    for (i = 0; i < ncp_nvm_size / 4096; i++)
    {
        nloop = 0;
        do {
            /* 
             * if the compare_and_swap persistently fails then there's 
             * probably a h/w problem. Fail out.
             */
            if (++nloop >= 100000) 
            {
                NCP_RETURN(NCP_ST_NVM_ERROR);
            }

            origValue = nvm_ptr[i*4096];

            success = __sync_bool_compare_and_swap(
                &nvm_ptr[i*4096],
                 origValue,
                 origValue);
        } while (success == FALSE);
    }

NCP_RETURN_LABEL
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_nvm_prefault_exit, NCP_MSG_EXIT, 
        "ncpStatus=%d\n", ncpStatus);
    return ncpStatus;
}


/*
 * ncp_nvm_get_more_core() - a callback routine which is called by
 * the mpm library to request or free memory from the memory pool. 
 * This routine assumes a fixed NVM size.
 */
static __ptr_t
ncp_nvm_get_more_core (__malloc_ptrdiff_t size)
{
    ncp_nvm_addr_t   *pNvmAddr = (ncp_nvm_addr_t *) ncp_nvm_vaddr;
    char            *pcore = pNvmAddr->nxt_avail;

    if (size > 0)
    {
        if ((pNvmAddr->nxt_avail + size) > (char *) (ncp_nvm_size + ncp_nvm_vaddr)) {
#ifdef NCP_DEBUG
            NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_nvm_get_more_core_outOfNvm, NCP_MSG_DEBUG,
                           "ERROR: Out of NVM Memory Current pointer = 0x%p, Max address = 0x%s, Alloc size = %ld\n",
                           pNvmAddr->nxt_avail,
                           NCP_CONVERT_LONG_TO_HEX_STR((ncp_uint64_t)(ncp_nvm_size+ncp_nvm_vaddr)),
                           (unsigned long)size);
#endif
            return NULL;
        }
        memset(pcore, 0, size);
    }
        
    pNvmAddr->nxt_avail += size;
    return pcore;
}


int
ncp_nvm_init(ncp_bool_t coldStart)
{
    ncp_nvm_addr_t   *pNvmAddr = NULL;
    char             *pnvm_base = NULL;

    /* 
     * check if the user has specified an alternative value for
     * the NVM address. If so reset the global ncp_nvm_vaddr.
     */
    char *vaddrEnv   = NULL;

    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_nvm_init_entry, NCP_MSG_ENTRY, 
        "coldStart=%d\n", coldStart);
    vaddrEnv = getenv("NCP_NVM_VADDR");
    if (vaddrEnv != NULL) {
    	NCP_NVM_INIT_ERR(printf("NCP_NVM_VADDR defined with invalid address %p\n", (void*) vaddrEnv));
    }
    
    if (coldStart == TRUE) 
    {
        if (ncp_nvm_initialized == TRUE) {
            pnvm_base = (char *) ncp_nvm_vaddr;
            ncp_nvm_munmap();
        }

        ncp_nvm_initialized = FALSE;
    }

    /* return immediately if already initialized */
    if (ncp_nvm_initialized == TRUE)
    {
        return 0;
    }

    pnvm_base = ncp_nvm_mmap();

    if ( pnvm_base == NULL )
    {
        return -1;
    }

    /*
     * allocate space at the beginning of the NVM area for local address 
     * pointers and the mp_info structure required by the mpmlib.
     */
    pNvmAddr = (ncp_nvm_addr_t *)pnvm_base;    


    /* 
     * Initialize the mpmlib; either with the mp_initialize
     * routine for cold starts, or with the mp_restart routine
     * for a warm restart.
     * For now, we determine whether or not it's a cold start by
     * checking the rootPtr. If it's zero, its cold start.
     *
     */
    if ((pNvmAddr->rootPtr == NULL) || (coldStart == TRUE))
    {
        memset(pNvmAddr, 0, sizeof(ncp_nvm_addr_t));
        pNvmAddr->base = pnvm_base;
        pNvmAddr->mp_info_ptr = (mp_info *) pnvm_base + sizeof(ncp_nvm_addr_t);
        pNvmAddr->nxt_avail = (char *) pNvmAddr->mp_info_ptr + sizeof(mp_info);
        if (!mp_initialize(pNvmAddr->mp_info_ptr, ncp_nvm_get_more_core))
        {
            NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_nvm_init_mp_initialize_error,
                           NCP_MSG_ERROR, "mp_init error\n");
            return -1;
        }
        
        /*
         * Initialize NVM locking semaphore to make the NVM alloc/free
         * functions multi-thread and multi-process safe
         */
        pNvmLock = &(pNvmAddr->nvmLock);
        pNvmActive = &(pNvmAddr->nvmActive);
        ncp_memset(pNvmLock, 0, sizeof(ncp_mutex_t));
        if (NCP_ST_SUCCESS != NCP_MUTEX_INIT(pNvmLock, TRUE))
        {
            NCP_NVM_INIT_ERR(printf("NVM sem_init failed\n"));
            return -1;
        }
        pNvmAddr->cookie = NCP_NVM_COOKIE;
    }
    else
    {
        /*
         * For a restart we make sure that the addresses we've mapped matches.
         */
        if ( pNvmAddr->base != pnvm_base) {
            NCP_NVM_INIT_ERR(printf(
                "NVM base address mismatch!  mapped %p, but NVM has %p\n",
                pnvm_base, pNvmAddr->base));
            return -1;
        }
        
        if (!mp_restart(pNvmAddr->mp_info_ptr, ncp_nvm_get_more_core))
        {
            NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_nvm_init_mp_restart_error,
                           NCP_MSG_ERROR, "mp_restart error\n");
            return -1;
        }
        pNvmLock = &(pNvmAddr->nvmLock);
        pNvmActive = &(pNvmAddr->nvmActive);
    }

    ncp_nvm_initialized = TRUE;

    return 0;
}

void
ncp_nvm_ptr_set(void *rootPtr)
{
    ncp_nvm_addr_t   *pNvmAddr = (ncp_nvm_addr_t *) ncp_nvm_vaddr;

    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_nvm_ptr_set_entry, NCP_MSG_ENTRY, 
        "rootPtr=%p\n", rootPtr);
    if (pNvmAddr->cookie != NCP_NVM_COOKIE)
    {
        pNvmAddr->rootPtr = 0;
#ifdef NCP_DEBUG
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_nvm_ptr_set_badCookie,
                       NCP_MSG_DEBUG, "ncp_nvm_ptr_set: bad cookie!\n");
#endif
        return;
    }
    pNvmAddr->rootPtr = rootPtr;
}

void *
ncp_nvm_ptr_get(void)
{
    ncp_nvm_addr_t   *pNvmAddr = (ncp_nvm_addr_t *) ncp_nvm_vaddr;

    if (pNvmAddr->cookie != NCP_NVM_COOKIE)
    {
#ifdef NCP_DEBUG
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_nvm_ptr_get_badCookie,
                       NCP_MSG_DEBUG, "ncp_nvm_ptr_get: bad cookie!\n");
#endif
        pNvmAddr->rootPtr = 0;
    }
    return (pNvmAddr->rootPtr);
}

void
ncp_nvm_user_ptr_set(int idx, void *userPtr)
{
    ncp_nvm_addr_t   *pNvmAddr = (ncp_nvm_addr_t *) ncp_nvm_vaddr;

    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_nvm_user_ptr_set_entry, NCP_MSG_ENTRY, 
        "idx=%d userPtr=%p\n", idx, userPtr);
    if (idx >= NCP_NVM_MAX_USER_POINTERS)
    {
#ifdef NCP_DEBUG
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_nvm_user_ptr_set_invalidIndex,
                       NCP_MSG_DEBUG, "ncp_nvm_user_ptr_set: invalid index (%d)\n", idx);
#endif
        return;
    }

    if (pNvmAddr->cookie != NCP_NVM_COOKIE)
    {
        pNvmAddr->userPtr[idx] = 0;
#ifdef NCP_DEBUG
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_nvm_user_ptr_set_badCookie,
                       NCP_MSG_DEBUG, "ncp_nvm_user_ptr_set: bad cookie!\n");
#endif
        return;
    }
    pNvmAddr->userPtr[idx] = userPtr;
}

void *
ncp_nvm_user_ptr_get(int idx)
{
    ncp_nvm_addr_t   *pNvmAddr = (ncp_nvm_addr_t *) ncp_nvm_vaddr;

    if (idx >= NCP_NVM_MAX_USER_POINTERS)
    {
#ifdef NCP_DEBUG
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_nvm_user_ptr_get_invalidIndex,
                       NCP_MSG_DEBUG, "ncp_nvm_user_ptr_get: invalid index (%d)\n", idx);
#endif
        return NULL;
    }

    if (pNvmAddr->cookie != NCP_NVM_COOKIE)
    {
#ifdef NCP_DEBUG
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_nvm_user_ptr_get_badCookie,
                       NCP_MSG_DEBUG, "ncp_nvm_user_ptr_get: bad cookie!\n");
#endif
        pNvmAddr->userPtr[idx] = 0;
    }
    return (pNvmAddr->userPtr[idx]);
}

void 
ncp_nvm_stats_get(ncp_nvm_stats_t *nvmStats)
{
    ncp_nvm_addr_t   *pNvmAddr = (ncp_nvm_addr_t *) ncp_nvm_vaddr;
    struct mstats stats;

    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_nvm_stats_get_entry, NCP_MSG_ENTRY, 
        "nvmStats=%p\n", nvmStats);
    stats = mp_mstats();
    
    nvmStats->bytes_total    = stats.bytes_total;
    nvmStats->chunks_used    = stats.chunks_used;
    nvmStats->bytes_used     = stats.bytes_used;
    nvmStats->chunks_free    = stats.chunks_free;
    nvmStats->bytes_free     = stats.bytes_free;
    nvmStats->nxt_avail_addr = (unsigned long) pNvmAddr->nxt_avail;

    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_nvm_stats_get_exit, NCP_MSG_EXIT, 
        "nvmStats: bytes_total=%d chunks_used=%d bytes_used=%d chunks_free=%d"
        "bytes_free=%d nxt_avail_addr=%d\n", 
        nvmStats ? nvmStats->bytes_total : 0,
        nvmStats ? nvmStats->chunks_used : 0,
        nvmStats ? nvmStats->bytes_used : 0,
        nvmStats ? nvmStats->chunks_free : 0,
        nvmStats ? nvmStats->bytes_free : 0,
        nvmStats ? nvmStats->nxt_avail_addr : 0);
}

ncp_bool_t ncp_nvm_is_enabled(void)
{
    return TRUE;
}

/* 
 * This function is deprecated. It cannot handle robust mutex errors.
 * Use the new ncp_nvm_robust_is_active API instead.
 */
ncp_bool_t
ncp_nvm_is_active(void)
{
    ncp_nvm_addr_t     *pNvmAddr = (ncp_nvm_addr_t *)ncp_nvm_vaddr;
    return (pNvmAddr->nvmActive);
}

/* 
 * New API for testing for nvm active.   This API handles
 * robust mutexes.
 */
ncp_st_t 
ncp_nvm_robust_is_active(ncp_bool_t *pIsActive)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_nvm_addr_t     *pNvmAddr = (ncp_nvm_addr_t *)ncp_nvm_vaddr;
    NCP_MUTEX_LOCKED_FLAG_DECL(nvmLocked);    

    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_nvm_robust_is_active_entry, NCP_MSG_ENTRY, 
        "pIsActive=%p\n", pIsActive);
    *pIsActive = TRUE;                              /* Pessimistic */
    NCP_CALL(NCP_MUTEX_LOCK(pNvmLock, &nvmLocked)); /* Test lock for owner dead */
    *pIsActive =  (pNvmAddr->nvmActive);
    
NCP_RETURN_LABEL    
    NCP_MUTEX_UNLOCK(pNvmLock, &nvmLocked);
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_nvm_robust_is_active_exit, NCP_MSG_EXIT, 
        "ncpStatus=%d *pIsActive=%d\n", ncpStatus,
        pIsActive ? *pIsActive : 0);
    return (ncpStatus);
}

#else /* !#ifdef NCP_USE_NVM */

/* empty functions when NCP_USE_NVM not defined */

int ncp_nvm_init(ncp_bool_t coldStart)
{
    return 0;
}

int   ncp_nvm_munmap(void)
{
    return 0;
}


void ncp_nvm_stats_get(ncp_nvm_stats_t *nvmStats) 
{
    nvmStats = NULL;
}


void
ncp_nvm_ptr_set(void *rootPtr)
{
}

void *
ncp_nvm_ptr_get(void)
{
    return NULL;
}

void
ncp_nvm_user_ptr_set(int idx, void *userPtr)
{
}

void *
ncp_nvm_user_ptr_get(int idx)
{
    return NULL;
}

ncp_bool_t ncp_nvm_is_enabled(void)
{
    return FALSE;
}

ncp_bool_t ncp_nvm_is_active(void)
{
    return FALSE;
}

ncp_st_t 
ncp_nvm_robust_is_active(ncp_bool_t *pIsActive)
{
    *pIsActive =  FALSE;
    return (NCP_ST_SUCCESS);
}

#endif /* #ifdef NCP_USE_NVM */

int
ncp_stricmp(const char *s1, const char *s2)
{
    while (*s1 && *s2 && (toupper(*s1) == toupper(*s2)))
    {
        s1++, s2++;
    }
    return (*s1 - *s2);
}

int
ncp_strincmp(const char *s1, const char *s2, ncp_size_t n)
{
    while (--n && *s1 && *s2 && (toupper(*s1) == toupper(*s2)))
    {
        s1++, s2++;
    }
    return (*s1 - *s2);
}

ncp_uint16_t
ncp_ntohs(ncp_uint16_t v)
{
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_ntohs_entry, NCP_MSG_ENTRY, 
        "v=%d\n", v);
    return ntohs(v);
} 

ncp_uint16_t
ncp_htons(ncp_uint16_t v)
{
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_htons_entry, NCP_MSG_ENTRY, 
        "v=%d\n", v);
    return htons(v);
} 


ncp_uint32_t
ncp_ntohl(ncp_uint32_t v)
{
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_ntohl_entry, NCP_MSG_ENTRY, 
        "v=%d\n", v);
    return ntohl(v);
}

ncp_uint32_t
ncp_htonl(ncp_uint32_t v)
{
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_htonl_entry, NCP_MSG_ENTRY, 
        "v=%d\n", v);
    return htonl(v);
}

ncp_uint64_t 
ncp_ntohll(ncp_uint64_t v)
{
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_ntohll_entry, NCP_MSG_ENTRY, 
        "v=%"PRIu64"\n", v);
#ifdef NO_LONG_LONG_SUPPORT
    return(ncp_ntohl((ncp_uint32_t)v));
#else
#ifdef NCP_BIG_ENDIAN
    return(v);
#else
    NCP_U32           a, b;

    a = (NCP_U32)(v >> 32);
    b = (NCP_U32)v;

    return (((ncp_uint64_t)ntohl(b) << 32) | ntohl(a));
#endif
#endif
}

ncp_uint64_t 
ncp_htonll(ncp_uint64_t v)
{
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_htonll_entry, NCP_MSG_ENTRY, 
        "v=%"PRIu64"\n", v);
#ifdef NO_LONG_LONG_SUPPORT
    return(ncp_htonl((ncp_uint32_t)v));
#else
#ifdef NCP_BIG_ENDIAN
    return(v);
#else
    NCP_U32           a, b;

    a = (NCP_U32)(v >> 32);
    b = (NCP_U32)v;

    return (((ncp_uint64_t)htonl(b) << 32) | htonl(a));
#endif
#endif
}

int
ncp_hr_time_compare(ncp_timespec_us_t *timespec1_us, ncp_timespec_us_t *timespec2_us)
{
    int ret=-1;
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_hr_time_compare_entry, NCP_MSG_ENTRY, 
        "timespec1_us=%p tv_sec=%ld tv_usec=%ld timespec2_us=%p tv_sec=%ld tv_usec=%ld\n", timespec1_us,
        timespec1_us ? timespec1_us->tv_sec : 0,
        timespec1_us ? timespec1_us->tv_usec : 0,
        timespec2_us,
        timespec2_us ? timespec2_us->tv_sec : 0,
        timespec2_us ? timespec2_us->tv_usec : 0);
    if (timespec1_us->tv_sec > timespec2_us->tv_sec)
    {
        ret=1;
    }
    else if (timespec1_us->tv_sec == timespec2_us->tv_sec)
    {    
        if (timespec1_us->tv_usec > timespec2_us->tv_usec)
        {   
            ret=1;
        }
        else if (timespec1_us->tv_usec == timespec2_us->tv_usec)    
        {
            ret=0;
        }
    }                
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_hr_time_compare_exit, NCP_MSG_EXIT, 
        "ret=%d\n", ret);
    return(ret);
}    

void                
ncp_hr_addtime_us(ncp_timespec_us_t *timespecStart_us, ncp_timespec_us_t *timespecEnd_us, ncp_uint64_t uSecs)
{
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_hr_addtime_us_entry, NCP_MSG_ENTRY, 
        "timespecStart_us=%p tv_sec=%ld tv_usec=%ld timespecEnd_us=%p tv_sec=%ld tv_usec=%ld uSecs=%"PRIu64" \n", 
        timespecStart_us,
        timespecStart_us ? timespecStart_us->tv_sec : 0,
        timespecStart_us ? timespecStart_us->tv_usec : 0,
        timespecEnd_us,
        timespecEnd_us ? timespecEnd_us->tv_sec : 0,
        timespecEnd_us ? timespecEnd_us->tv_usec : 0,
        uSecs);
    timespecEnd_us->tv_sec  = timespecStart_us->tv_sec  + (uSecs / 1000000);
    timespecEnd_us->tv_usec = timespecStart_us->tv_usec + (uSecs % 1000000);
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_hr_addtime_us_exit, NCP_MSG_EXIT, 
        "timespecEnd_us=%p tv_sec=%ld tv_usec=%ld\n", 
        timespecEnd_us,
        timespecEnd_us ? timespecEnd_us->tv_sec : 0,
        timespecEnd_us ? timespecEnd_us->tv_usec : 0);
    return;
}    
                
void 
ncp_hr_gettime_us(ncp_timespec_us_t *timespec_us)
{
#if 0
	LAPAJ
#ifdef NCP_PLATFORM_HAS_CLOCK_MONOTONIC    
    struct timespec      hr_timeval;
    clock_gettime(CLOCK_MONOTONIC, &hr_timeval);
    timespec_us->tv_sec  = hr_timeval.tv_sec;
    timespec_us->tv_usec = hr_timeval.tv_nsec*1000;    
#else
    struct timeval      hr_timeval;
    gettimeofday(&hr_timeval, NULL);  /* Note,   gettimeofday can go backwards due to NTP updates, timesets,  etc... */
    timespec_us->tv_sec  = hr_timeval.tv_sec;
    timespec_us->tv_usec = hr_timeval.tv_usec;    
#endif   
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_hr_gettime_us_entry, NCP_MSG_ENTRY, 
        "timespec_us=%p tv_sec=%ld tv_usec=%ld\n", timespec_us,
        timespec_us ? timespec_us->tv_sec : 0,
        timespec_us ? timespec_us->tv_usec : 0);
#endif
}
 

void
ncp_gettime(ncp_timespec_t *timespecval)
{
#if 0
    struct timeval      timevalval;
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_gettime_entry, NCP_MSG_ENTRY, 
        "timespecval=%p\n", timespecval);
    (void)gettimeofday(&timevalval, NULL);
    timespecval->tv_sec = timevalval.tv_sec;
    timespecval->tv_nsec = timevalval.tv_usec*1000;
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_gettime_exit, NCP_MSG_EXIT, 
        "timespecval: tv_sec=%ld tv_nsec=%ld\n", 
        timespecval ? timespecval->tv_sec : 0,
        timespecval ? timespecval->tv_nsec : 0);
#endif
}

/*
 * ncp_gettime_elapsed
 *
 * Compute elapsed time in seconds between two points in time: t1 and t2,
 * where "t1" is the first (earlier) time point and "t2" is the second
 * (later) time point.
 */
double
ncp_gettime_elapsed(
    ncp_timespec_t *t1,
    ncp_timespec_t *t2)
{
    double secs;

    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_gettime_elapsed_entry, NCP_MSG_ENTRY, 
        "t1=%p tv_sec=%ld tv_usec=%ld t2=%p tv_sec=%ld tv_usec=%ld\n", 
        t1,
        t1 ? t1->tv_sec : 0,
        t1 ? t1->tv_nsec : 0,
        t2,
        t2 ? t2->tv_sec : 0,
        t2 ? t2->tv_nsec : 0);
    if (t1->tv_nsec > t2->tv_nsec)
    {
        secs = ((t2->tv_sec - 1) - t1->tv_sec) +
               ((((double)t2->tv_nsec + 1000000000) - t1->tv_nsec) /
                1000000000);
    }
    else
    {
        secs = ((t2->tv_sec) - t1->tv_sec) +
               ((((double)t2->tv_nsec) - t1->tv_nsec) / 1000000000);
    }

    return secs;
}

ncp_st_t ncp_screen_startup(int *lines, int *cols)
{
#if 0 
	NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_screen_startup_entry, NCP_MSG_ENTRY, 
        "lines=%p cols=%p\n", lines, cols);
#ifdef NCP_CURSES
    initscr();

    getmaxyx(stdscr, *lines, *cols);

    wmove(stdscr, 0, 0);

    wclrtobot(stdscr);
#else
    struct winsize ws;

    ioctl(0, TIOCGWINSZ, &ws);

    if (ws.ws_row != 0)
        *lines = ws.ws_row;
    else
        *lines = 24;
    if (ws.ws_col != 0)
        *cols  = ws.ws_col;
    else
        *cols = 80;
#endif /* NCP_CURSES */

    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_screen_startup_exit, NCP_MSG_EXIT, 
        "lines=%d cols=%d\n", 
        lines ? *lines : 0,
        cols ? *cols :0);
#endif
	return NCP_ST_SUCCESS;
}


#ifdef NCP_MULTI_THREAD 

/* ======================================================================== */

/* 
 * Added Mar, 2016
 * Mutex init - initializes a robust mutex (if available in tool chain).   Caller must be prepared to handle owner died 
 * error when operating on the mutex.
 */
 
/* NOTE: Use NCP_MUTEX_LOCK macro to invoke.   Do not call directly! */ 
ncp_st_t
ncp_mutex_init(ncp_mutex_t *pMutex, ncp_int32_t shared)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
#if 0

    NCP_ASSERT((pthread_mutexattr_init(&pMutex->mutexAttr)) == 0, 
               NCP_ST_MUTEX_ATTR_INIT_ERROR);

#ifdef _XOPEN_SOURCE
#if (_XOPEN_SOURCE >= 600 )
    NCP_ASSERT((pthread_mutexattr_setprotocol(&pMutex->mutexAttr,
                PTHREAD_PRIO_INHERIT)
        == 0), NCP_ST_MUTEX_ATTR_INIT_ERROR);
#endif        
#if (_XOPEN_SOURCE >= 700 ) && !defined(NCP_ROBUST_MUTEX_DISABLED)       
    NCP_ASSERT((pthread_mutexattr_setrobust(&pMutex->mutexAttr,
                PTHREAD_MUTEX_ROBUST)
        == 0), NCP_ST_MUTEX_ATTR_INIT_ERROR);
#endif
#endif
      
    if (shared) {
        NCP_ASSERT((pthread_mutexattr_setpshared(&pMutex->mutexAttr, 
                                                 PTHREAD_PROCESS_SHARED)) == 0,
                   NCP_ST_MUTEX_SHARED_INIT_ERROR);
    }

    NCP_ASSERT((pthread_mutex_init(&pMutex->mutex, &pMutex->mutexAttr)) == 0,
               NCP_ST_MUTEX_INIT_ERROR);
#endif
NCP_RETURN_LABEL
    return ncpStatus;
}

extern int pthread_mutex_destroy(void *mutex);

ncp_st_t
ncp_mutex_destroy(ncp_mutex_t *pMutex)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    NCP_ASSERT((pthread_mutex_destroy(&pMutex->mutex)) == 0, NCP_ST_MUTEX_DESTROY_ERROR);

NCP_RETURN_LABEL
    return ncpStatus;
}

#ifdef NCP_ROBUST_MUTEX_TEST
extern ncp_bool_t ncp_owner_dead;
extern ncp_mutex_t* ncp_mutex_ptr;
#endif
#ifndef PROC_EP5020
extern int pthread_mutex_lock(void *mutex);
#endif
/* NOTE: Use NCP_MUTEX_LOCK macro to invoke.   Do not call directly! */
ncp_st_t
ncp_mutex_lock(ncp_mutex_t *pMutex)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
	return ncpStatus; 
    int err = 0;
    
#ifndef PROC_EP5020
    err = pthread_mutex_lock(&pMutex->mutex);
#else
    /*  
     * BZ 48367:
     * A multi-threaded app on the EP5020 has the potential to deadlock when
     * there is contention over a mutex. This appears to be due to coherency
     * issues in the EP5020 hardware or kernel, though the root cause is
     * unknown. Repeatedly calling pthread_mutex_trylock() as opposed to 
     * pthread_mutex_lock() appears to reduce the likelihood of deadlock.
     * This may be because trylock() always remains in user-space.
     */
    
    while (EBUSY == (err = pthread_mutex_trylock(&pMutex->mutex)));
    
#endif

    if (0 == err)
    {
        /* intentionally blank */
    }
    else        
    {
#ifdef _XOPEN_SOURCE        
#if (_XOPEN_SOURCE >= 700 ) && !defined(NCP_ROBUST_MUTEX_DISABLED)         
        if ((EOWNERDEAD == err) || (ENOTRECOVERABLE == err))
        {  
            /* 
             * Robust mutex owner died.   We own the lock so we must unlock.
             * Do not recover the mutex!   We want all callers to see the OWNERDIED
             * error status.   The only recovery we support is to reconfigure/recreate
             * the lock.   It is likely that the software state is corrupt if this error is seen.
             *
             * Note that we only see EOWNERDEAD the first time we take a mutex after the owner has died.   From then
             * on we see ENOTRECOVERABLE.
             */
            ncp_mutex_unlock(pMutex);
            ncpStatus = NCP_ST_PTHREAD_MUTEX_OWNER_DEAD;
        }
        else
#endif 
#endif
           
        {
            ncpStatus = NCP_ST_MUTEX_WAIT_ERROR;
        }
    }
#ifdef NCP_ROBUST_MUTEX_TEST
    if (ncp_owner_dead)
    {
        ncp_owner_dead = FALSE;
        ncp_mutex_ptr = pMutex;
        pthread_exit(NULL);
    }
#endif

NCP_RETURN_LABEL

    return ncpStatus;
}

extern int pthread_mutex_unlock(void *mutex);
ncp_st_t
ncp_mutex_unlock(ncp_mutex_t *pMutex)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
	return ncpStatus;
    NCP_ASSERT((pthread_mutex_unlock(&pMutex->mutex)) == 0, NCP_ST_MUTEX_POST_ERROR);

NCP_RETURN_LABEL
    return ncpStatus;
}

/* ======================================================================== */

/* 
 * Legacy sem (mutex) init - does not support robust mutexes! Note that this API creates a user mode mutex,
 * as opposed to a semaphore!   This is an important distinction.   This API will be removed once all
 * RTE components have been refactored to support robust mutexes.
 */
ncp_st_t
ncp_sem_init(ncp_sem_t *sem, ncp_int32_t shared, ncp_uint32_t value)
{

    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
#if 0
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sem_init_entry, NCP_MSG_ENTRY, 
        "sem=%p shared=%d value=%d\n", sem, shared, value);
    NCP_ASSERT((pthread_mutexattr_init(&sem->mutexAttr)) == 0, 
               NCP_ST_MUTEX_ATTR_INIT_ERROR);

#ifdef _XOPEN_SOURCE
#if (_XOPEN_SOURCE >= 600 )
    NCP_ASSERT((pthread_mutexattr_setprotocol(&sem->mutexAttr,
                PTHREAD_PRIO_INHERIT)
        == 0), NCP_ST_MUTEX_ATTR_INIT_ERROR);
#endif 
#endif       
       
    if (shared) {
        NCP_ASSERT((pthread_mutexattr_setpshared(&sem->mutexAttr, 
                                                 PTHREAD_PROCESS_SHARED)) == 0,
                   NCP_ST_MUTEX_SHARED_INIT_ERROR);
    }

    NCP_ASSERT((pthread_mutex_init(&sem->mutex, &sem->mutexAttr)) == 0,
               NCP_ST_MUTEX_INIT_ERROR);

NCP_RETURN_LABEL
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sem_init_exit, NCP_MSG_EXIT, 
        "ncpStatus=%d\n", ncpStatus);
#endif
return ncpStatus;
}

ncp_st_t
ncp_sem_post(ncp_sem_t *sem)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sem_post_entry, NCP_MSG_ENTRY, 
        "sem=%p\n", sem);

    NCP_ASSERT((pthread_mutex_unlock(&sem->mutex)) == 0, NCP_ST_MUTEX_POST_ERROR);

NCP_RETURN_LABEL
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sem_post_exit, NCP_MSG_EXIT, 
        "ncpStatus=%d\n", ncpStatus);
    return ncpStatus;
}

ncp_st_t
ncp_sem_wait(ncp_sem_t *sem)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
	/* LAPAJ */
	return ncpStatus;
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sem_wait_entry, NCP_MSG_ENTRY, 
        "sem=%p\n", sem);
#ifndef PROC_EP5020
    NCP_ASSERT((pthread_mutex_lock(&sem->mutex)) == 0, NCP_ST_MUTEX_WAIT_ERROR);
#else
    /*  
     * BZ 48367:
     * A multi-threaded app on the EP5020 has the potential to deadlock when
     * there is contention over a mutex. This appears to be due to coherency
     * issues in the EP5020 hardware or kernel, though the root cause is
     * unknown. Repeatedly calling pthread_mutex_trylock() as opposed to 
     * pthread_mutex_lock() appears to reduce the likelihood of deadlock.
     * This may be because trylock() always remains in user-space.
     */
    int err = 0;
    while ((err = pthread_mutex_trylock(&sem->mutex)) == EBUSY);
    ncpStatus = (err == 0) ? NCP_ST_SUCCESS : NCP_ST_MUTEX_WAIT_ERROR;
#endif

NCP_RETURN_LABEL
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sem_wait_exit, NCP_MSG_EXIT, 
        "ncpStatus=%d\n", ncpStatus);
    return ncpStatus;
}

ncp_st_t
ncp_sem_trywait(ncp_sem_t *sem)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
#if 0 
    int rv = pthread_mutex_trylock(&sem->mutex);
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sem_trywait_entry, NCP_MSG_ENTRY, 
        "sem=%p\n", sem);

    if (rv != 0) {
        if (rv == EBUSY) {
            NCP_ERR(NCP_ST_MUTEX_BUSY);
        } else {
            NCP_ERR(NCP_ST_MUTEX_TRYWAIT_ERROR);
        }
    }

NCP_RETURN_LABEL
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sem_trywait_exit, NCP_MSG_EXIT, 
        "ncpStatus=%d\n", ncpStatus);
#endif
    return ncpStatus;
}

ncp_st_t
ncp_sem_destroy(ncp_sem_t *sem)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sem_destroy_entry, NCP_MSG_ENTRY, 
        "sem=%p\n", sem);
    NCP_ASSERT((pthread_mutex_destroy(&sem->mutex)) == 0, NCP_ST_MUTEX_DESTROY_ERROR);

NCP_RETURN_LABEL
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sem_destroy_exit, NCP_MSG_EXIT, 
        "ncpStatus=%d\n", ncpStatus);
    return ncpStatus;
}

#else /* NCP_MULTI_THREAD */


/* ======================================================================== */

ncp_st_t
ncp_mutex_init(ncp_mutex_t *pMutex, ncp_int32_t shared)
{
    ncp_st_t     st = NCP_ST_SUCCESS;
    return st;
}

ncp_st_t
ncp_mutex_destroy(ncp_mutex_t *pMutex)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    return ncpStatus;
}

ncp_st_t
ncp_mutex_lock(ncp_mutex_t *pMutex)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    return ncpStatus;
}

ncp_st_t
ncp_mutex_unlock(ncp_mutex_t *pMutex)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    return ncpStatus;
}

/* ======================================================================== */

ncp_st_t
ncp_sem_init(ncp_sem_t *sem, ncp_int32_t shared, ncp_uint32_t value)
{
    ncp_st_t     st = NCP_ST_SUCCESS;
    return st;
}

ncp_st_t
ncp_sem_post(ncp_sem_t *sem)
{
    ncp_st_t     st = NCP_ST_SUCCESS;
    return st;
}

ncp_st_t
ncp_sem_wait(ncp_sem_t *sem)
{
    ncp_st_t     st = NCP_ST_SUCCESS;
    return st;
}

ncp_st_t
ncp_sem_trywait(ncp_sem_t *sem)
{
    ncp_st_t     st = NCP_ST_SUCCESS;
    return st;
}

ncp_st_t
ncp_sem_destroy(ncp_sem_t *sem)
{
    ncp_st_t     st = NCP_ST_SUCCESS;
    return st;
}



#endif /* NCP_MULTI_THREAD */

/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Linux Process-related Interfaces
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

/*mb: create a stub*/
#define fork(args...) (0)
#define execlp(args...) (0)

int
ncp_create_exec_process(
    const char *name, 
    char *arg1,
    char *arg2,
    char *arg3,
    char *arg4,
    char *arg5)
{
    pid_t pID = fork();

    if (pID == 0) /* child */
    {
        /* call the command */
        int execReturn = execlp(name, name, arg1, arg2, arg3, arg4, arg5, (char *)NULL);
        if (execReturn)
        {
            /* make compiler happy - macro requires return value ,  but will be optimized out */
        }
    }

    return pID;
}

void foo(int blah)
{
}

void ncp_isr_spin_lock_init(ncp_isr_spinlock_t *lock) 
{
}

void ncp_isr_spin_lock_raw(ncp_isr_spinlock_t *lock, unsigned long *flags)
{
}

void ncp_isr_spin_unlock_raw(ncp_isr_spinlock_t *lock, unsigned long flags)
{
}

void ncp_isr_spin_lock_cooked(ncp_isr_spinlock_t *lock, unsigned long *flags)
{
}

void ncp_isr_spin_unlock_cooked(ncp_isr_spinlock_t *lock, unsigned long flags)
{
}

#else /* !#ifndef __KERNEL__ */

int
ncp_hr_time_compare(ncp_timespec_us_t *timespecStart_us, ncp_timespec_us_t *timespecEnd_us)
{
    /* TODO */
    return(1);
}    

void                
ncp_hr_addtime_us(ncp_timespec_us_t *timespecStart_us, ncp_timespec_us_t *timespecEnd_us, ncp_uint64_t uSecs)
{
    /* TODO */    
    return;
}    
                
void 
ncp_hr_gettime_us(ncp_timespec_us_t *timespec_us)
{   
    /* TODO */    
    return;
}


/*
 * ncp_dma_mem_map
 *     Map a reserved segment of memory to be used for DMA
 *
 *  For external hosts the DMA memory must be uncached.
 *  For the internal PPC476 core the DMA memory is cache coherent.
 *  The macro NCP_EDEV_DMA_IOREMAP is defined for each bus adaptor
 *  to call the appropriate (cached or uncached) ioremap function.
 *
 */
void *
ncp_dma_mem_map(
        ncp_uint32_t devNum,
        ncp_uint64_t physAddr,
        ncp_uint64_t size)
{
    void *ncp_rsvd_ram = NULL;

    if (NULL == (ncp_rsvd_ram = NCP_IOREMAP_DMA(physAddr, size)))
    {
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_dma_mem_map_ioremapDmaFailed, NCP_MSG_ERROR,
                       "NCP_IOREMAP_DMA failed! addr=0x%llx, length=0x%llx\n",
                       physAddr, size);
    }
    else
    {
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_dma_mem_map_success, NCP_MSG_DEBUG_MEM,
                       "ncp_dma_mem_map mapped physAddr 0x%08llx to kernel VA=0x%p (0x%016llx bytes)\n",
                       physAddr, ncp_rsvd_ram, size);
    }

    return (ncp_rsvd_ram);
}

/*
 * ncp_mem_map
 *     Map a reserved segment of memory to be used for cachable taskio GSM
 *
 */
void *
ncp_mem_map(
        ncp_uint32_t devNum,
        ncp_uint64_t physAddr,
        ncp_uint64_t size)
{
    void  *ncp_rsvd_ram = NULL;

    if (NULL == (ncp_rsvd_ram = NCP_IOREMAP_CACHE(physAddr, size)))
    {
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_mem_map_failed, NCP_MSG_ERROR,
                       "ncp_mem_map failed! addr=0x%llx, length=0x%llx\n",
                       physAddr, size);
    }
    else
    {
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_mem_map_success, NCP_MSG_DEBUG_MEM,
                       "ncp_mem_map mapped physAddr 0x%llx to kernel VA=0x%p (0x%016llx bytes)\n",
                       physAddr, ncp_rsvd_ram, size);
    }

    return (ncp_rsvd_ram);
}

ncp_st_t
ncp_mutex_init(ncp_mutex_t *pMutex, ncp_int32_t shared)
{
    sema_init(pMutex, 1); /* val == 1 implies Mutex mode */
    return NCP_ST_SUCCESS;
}

ncp_st_t
ncp_mutex_lock(ncp_mutex_t *pMutex)
{
    if (down_interruptible(pMutex)) {
        /* semaphore not acquired; received a signal */
        return NCP_ST_DEV_INTERRUPTED;
    }
    return NCP_ST_SUCCESS;
}

ncp_st_t
ncp_mutex_unlock(ncp_mutex_t *pMutex)
{
    up(pMutex);
    return NCP_ST_SUCCESS;
}

ncp_st_t
ncp_mutex_destroy(ncp_mutex_t *pMutex)
{
    return NCP_ST_SUCCESS;
}

ncp_st_t
ncp_sem_init(ncp_sem_t *sem, ncp_int32_t shared, ncp_uint32_t value)
{
    sema_init(sem, value);
    return NCP_ST_SUCCESS;
}

ncp_st_t
ncp_sem_destroy(ncp_sem_t *sem)
{
    return NCP_ST_SUCCESS;
}

ncp_st_t 
ncp_sem_post(ncp_sem_t *sem)
{
    up(sem);
    return NCP_ST_SUCCESS;
}
    
ncp_st_t
ncp_sem_wait(ncp_sem_t *sem)
{
    if (down_interruptible(sem)) {
        /* semaphore not acquired; received a signal */
        return NCP_ST_DEV_INTERRUPTED;
    }
    return NCP_ST_SUCCESS;
}


#include <linux/spinlock.h>


/*
 * ncp_isr_spin_lock interface
 *
 *   When running with the linux PREEMPT_RT kernel,
 *   the default behavior is for ISRs to run in 
 *   threaded context and spinlocks are converted
 *   to mutexes. The RTE provides a USE_HARD_IRQ 
 *   option to override this behavior and run the 
 *   ISR in hard IRQ context. In this case we must 
 *   use a raw_spinlock to prevent it being converted
 *   to a mutex. 
 *
 *   Since the same functions may end up getting run
 *   in either ISR context we need a spinlock that can
 *   be either a regular (convertable) spinlock or a
 *   raw spinlock. This is accomplished with the 
 *   ncp_isr_spin_lock interface. This interface will
 *   initialize a pair of spinlocks (one raw, one 'cooked'),
 *   and provide a pair of lock/unlock functions for each.
 *   The choice of which to use can be made at runtime by
 *   selecting the table with desired function pointers. 
 */
 
void ncp_isr_spin_lock_init(ncp_isr_spinlock_t *lock) 
{
    spin_lock_init(&lock->cooked);
    raw_spin_lock_init(&lock->raw);
}


inline void ncp_isr_spin_lock_raw(ncp_isr_spinlock_t *lock, unsigned long *flags)
{
    raw_spin_lock_irqsave(&lock->raw, *flags);
}

inline void ncp_isr_spin_unlock_raw(ncp_isr_spinlock_t *lock, unsigned long flags)
{
    raw_spin_unlock_irqrestore(&lock->raw, flags);
}

inline void ncp_isr_spin_lock_cooked(ncp_isr_spinlock_t *lock, unsigned long *flags)
{
    spin_lock_irqsave(&lock->cooked, *flags);
}

inline void ncp_isr_spin_unlock_cooked(ncp_isr_spinlock_t *lock, unsigned long flags)
{
    spin_unlock_irqrestore(&lock->cooked, flags);
}

#endif /* #ifndef __KERNEL__ */

struct ncp_isr_lock_fns ncp_isr_lock_raw = {
    ncp_isr_spin_lock_raw,
    ncp_isr_spin_unlock_raw,
};

struct ncp_isr_lock_fns ncp_isr_lock_cooked = {
    ncp_isr_spin_lock_cooked,
    ncp_isr_spin_unlock_cooked,
};


#if 0
LAPAJ
#ifndef _XOPEN_SOURCE
#ifndef __KERNEL__
#ifdef __cplusplus
    extern "C" int usleep(__useconds_t usec);
#else
    extern int usleep(__useconds_t usec);
#endif /* #ifdef __cplusplus */
#endif /* #ifndef __KERNEL__ */
#endif /* #ifndef _XOPEN_SOURCE */
#endif

/*
 * ncp_sys_usleep()
 *
 * Suspend current task for at least "n" microseconds.
 */

int
ncp_sys_usleep(unsigned long usec)
{
#ifdef __KERNEL__
    int msec;

    msec = (usec + 999) / 1000;
    msleep(msec);
    
#else
#ifdef _XOPEN_SOURCE
#if (_XOPEN_SOURCE >= 700 ) /* POSIX 2008 or later? */
    struct timespec  tNano;

    tNano.tv_sec = usec / (1000 * 1000);
    tNano.tv_nsec = (usec % (1000 * 1000)) * 1000;

    /* Automatically store remainder back into time if interrupted */
   while( (-1 == nanosleep(&tNano, &tNano)) && (errno == EINTR))
   {
        continue;
   }
    
#else
   (void)udelay(usec);       /* deprecated in POSIX 2008 */
#endif
#else
   (void)udelay(usec);       /* deprecated in POSIX 2008 */
#endif
#endif
    return 0;
}

#ifdef __KERNEL__
int 
ncp_dev_udelay(unsigned long usecs)
{
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_dev_udelay_entry, NCP_MSG_ENTRY, 
        "usecs=%lu\n", usecs);
    udelay(usecs);
    return 0;
}

int 
ncp_dev_mdelay(unsigned long msecs)
{
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_dev_mdelay_entry, NCP_MSG_ENTRY, 
        "msecs=%lu\n", msecs);
    mdelay(msecs);
    return 0;
}
#endif

#ifndef __KERNEL__
volatile ncp_task_pid_api_active_t *pid_active;
#endif
