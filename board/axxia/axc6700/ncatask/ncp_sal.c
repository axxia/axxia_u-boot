/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.              *
 **                                                                       *
 **************************************************************************/

#include <common.h>
#include <linux/string.h>
#include <malloc.h>
#include "uboot/ncp_sal_types_linux.h"
#include "uboot/ncp_task_basetypes.h"
#include "uboot/ncp.h"

#include "uboot/ncp_sal.h"

/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

extern unsigned long ncp_nvm_vaddr;
extern unsigned long ncp_nvm_size;


#undef NCP_NVM_DEBUG
#ifndef NCP_KERNEL
/* #define NCP_NVM_DEBUG */   /* Uncomment to enable debug mode */
#endif

#ifdef NCP_KERNEL

#define CRASHME() 

/*
    #define NCP_MEMORY_CORUPTION_DEBUG
*/

#ifdef NCP_MEMORY_CORUPTION_DEBUG

#define NCP_MEM_HDR 9
#define NCP_MEM_FTR 1
#define NCP_MEM_CRPTN_DBG_ENTRIES 512

typedef struct 
{
    ncp_uint8_t memHdr[NCP_MEM_HDR];
    void *memPtr;
    ncp_uint32_t size;
    ncp_uint8_t memFtr[NCP_MEM_FTR];
} ncp_mem_crptn_dbg_info_t;

static ncp_mem_crptn_dbg_info_t *ncpMemCrptnDbgInfo[NCP_MEM_CRPTN_DBG_ENTRIES];
static spinlock_t memCrptnDbgLock = SPIN_LOCK_INIT;
static ncp_uint32_t ncpMemCrptnDbgIndex = 0;

void mem_block_alloc(void *ptr, ncp_uint32_t size)
{
    ncp_uint32_t index1 = 0;
    ncp_uint8_t *ptr1 = (ncp_uint8_t *)(ptr - NCP_MEM_HDR);
    
    /* lock the spinlock and update the index */
    NCP_SPINLOCK_LOCK(&memCrptnDbgLock);
    
    if(ncpMemCrptnDbgInfo[ncpMemCrptnDbgIndex] == NULL)
    {
        ncpMemCrptnDbgInfo[ncpMemCrptnDbgIndex] = __ncp_malloc(sizeof(ncp_mem_crptn_dbg_info_t));
    }
    
    /* store the memory data */            
    ncpMemCrptnDbgInfo[ncpMemCrptnDbgIndex]->size = size;
    ncpMemCrptnDbgInfo[ncpMemCrptnDbgIndex]->memPtr = ptr;
    ncp_memcpy(ncpMemCrptnDbgInfo[ncpMemCrptnDbgIndex]->memHdr, ptr - NCP_MEM_HDR, NCP_MEM_HDR);
    ncp_memcpy(ncpMemCrptnDbgInfo[ncpMemCrptnDbgIndex]->memFtr, ptr + size, NCP_MEM_FTR);

    ncpMemCrptnDbgIndex++;
    if(ncpMemCrptnDbgIndex == NCP_MEM_CRPTN_DBG_ENTRIES)
        ncpMemCrptnDbgIndex = 0;

    printf( "Allocating pointer 0x%x OK.\n", ptr);
    printf("Header: ");
    for(index1 = 0; index1 < NCP_MEM_HDR; index1++)
        printf( "0x%x ", ptr1[index1]);
    printf("\n");

    /* release spinlock */
    NCP_SPINLOCK_UNLOCK(&memCrptnDbgLock);
}

int mem_block_free(void *ptr)
{
    ncp_uint32_t index = 0;
    ncp_uint32_t index1 = 0;
    ncp_uint8_t *ptr1 = (ncp_uint8_t *)(ptr - NCP_MEM_HDR);
    int ret = 0;

    NCP_SPINLOCK_LOCK(&memCrptnDbgLock);
    
    for(index = 0; index < NCP_MEM_CRPTN_DBG_ENTRIES; index++)
    {
        /* look for the entry */
        if(ncpMemCrptnDbgInfo[index] != NULL && 
           ncpMemCrptnDbgInfo[index]->memPtr == ptr)
        {
            /* check for the header corruption */
            if(ncp_memcmp(ncpMemCrptnDbgInfo[index]->memHdr, ptr - NCP_MEM_HDR,
                          NCP_MEM_HDR) != 0)
            {
                printf("ERROR: Memory header corruption. ptr=0x%x\n", ptr);
                printf("Expected header: ");
                for(index1 = 0; index1 < NCP_MEM_HDR; index1++)
                    printf( "0x%x ", ncpMemCrptnDbgInfo[index]->memHdr[index1]);
                
                printf( "\nObserved header: ");
                for(index1 = 0; index1 < NCP_MEM_HDR; index1++)
                    printf( "0x%x ", ptr1[index1]);
                printf("\n");

                ret = 0;
                ncp_sleep(2);
                break;
            }
            else
            {
                __ncp_free(ncpMemCrptnDbgInfo[index]);
                ncpMemCrptnDbgInfo[index] = NULL;
                printf("Freeing pointer 0x%x OK.\n", ptr);                
                ret = 0;
                break;
            }
        }
    }

    NCP_SPINLOCK_UNLOCK(&memCrptnDbgLock);

    /* did not find the memory ptr. How is that possible?? */
    if(index == NCP_MEM_CRPTN_DBG_ENTRIES)
        printf( "WARN: Freeing pointer 0x%x not stored in table.\n", ptr);
    
    return ret;
}

#endif /* NCP_MEMORY_CORUPTION_DEBUG */

#else /* NCP_KERNEL */

#ifdef DEVELOPMENT_DIAGNOSTICS
#define CRASHME() \
   do {           \
       int n;     \
       int *p=0;  \
       n = *p;    \
   } while (0);     
#else 
#define CRASHME()
#endif
        
#endif /* NCP_KERNEL */

#ifdef NCP_NVM_DEBUG

#define NCP_NVM_DEBUG_OVERHEAD(_size) ((_size + (((2*sizeof(ncp_uint64_t)) + (sizeof(ncp_uint64_t) - 1)))) & ~((sizeof(ncp_uint64_t) - 1)))
#define NCP_NVM_DEBUG_END_OFFSET_FROM_USER_PTR(_size) (_size + ((sizeof(ncp_uint64_t) - 1) & ~(sizeof(ncp_uint64_t) - 1)))

void
ncp_nvm_breakpoint(void)
{
    volatile int i;
    i=0;
    i++;
#if 0 
    CRASHME();
#endif    
    return;
}

void *
ncp_nvm_add_dbg_fields(void *p, ncp_size_t size)       
{                                        
    ncp_uint64_t *pStart;               
    ncp_uint64_t *pEnd;                 
    ncp_uint64_t dbgval;
    ncp_uint64_t endOffset;                
                                         
    pStart = (ncp_uint64_t *)p;  

    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_nvm_add_dbg_fields_1, NCP_MSG_DEBUG,
                   "ncp_nvm_add_dbg_fields entered with real p=%p, size=%d",p, (int)size);
    
    /* user pointer starts immediately after debug prefix */          
    p = (void *)(ncp_uintptr_t)((ncp_uintptr_t)p + sizeof(ncp_uint64_t));
   
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_nvm_add_dbg_fields_2, NCP_MSG_DEBUG,
                   ", userP=%p",p);
        
    /* build debug fields */
    endOffset = NCP_NVM_DEBUG_END_OFFSET_FROM_USER_PTR(size);
    pEnd = (ncp_uint64_t *)(ncp_uintptr_t)((ncp_uintptr_t)p + endOffset);
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_nvm_add_dbg_fields_3, NCP_MSG_DEBUG,
                   ", pEnd=%p, endOffset=0x%llx",pEnd, (long long unsigned int)endOffset);
    dbgval = 0xDEADF00D00000000ULL;
    dbgval |= (0x00000000FFFFFFFFULL & (ncp_uint64_t)endOffset);
    *pStart = dbgval;
    dbgval = 0xBABEF00DBABEF00DULL;
    *pEnd  = dbgval;
    return(p);    
}   

void
ncp_nvm_validate_dbg_fields(void **pPtr)    

{
    void *ptr = *pPtr;
    ncp_uint64_t *pStart;               
    ncp_uint64_t *pEnd;         
    ncp_uint64_t endOffsetFromUserPtr;
    
    /*
     * Perform sanity checks on existing buffer
     */
    pStart = (ncp_uint64_t *)(ncp_uintptr_t)((ncp_uintptr_t)ptr - sizeof(ncp_uint64_t));
    if (0xDEADF00D00000000ULL != (*pStart & 0xFFFFFFFF00000000ULL))
    {
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_nvm_validate_dbg_fields_badStart,
                       NCP_MSG_ERROR, "NVM Corruption ptr=%p. bad start val=0x%016llx\r\n",
                       ptr, (long long unsigned int)*pStart);
        ncp_nvm_breakpoint();
        return(NULL);
    }    
    endOffsetFromUserPtr = (*pStart & 0x00000000FFFFFFFFULL);
    pEnd = (ncp_uint64_t *)(ncp_uintptr_t)((ncp_uintptr_t)ptr + endOffsetFromUserPtr);
    if (0xBABEF00D00000000ULL != (*pEnd & 0xFFFFFFFF00000000ULL))
    {
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_nvm_validate_dbg_fields_badEnd,
                       NCP_MSG_ERROR, "NVM Corruption ptr=%p. bad end val=0x%016llx\r\n",
                       ptr, (long long unsigned int)*pEnd);
        ncp_nvm_breakpoint();        
        return(NULL);
    }  
    ptr = pStart; /* use the "real" start pointer for the "free" portion of realloc */
    *pPtr = ptr;  /* Modify callers pointer */
}    

#define NCP_NVM_ADD_DBG_FIELDS(_ptr, _size) \
    ncp_nvm_add_dbg_fields(_ptr, _size) 

#define NCP_NVM_VALIDATE_DBG_FIELDS(_pPtr) \
ncp_nvm_validate_dbg_fields((_pPtr))
  
#else 
#define NCP_NVM_DEBUG_OVERHEAD(_size) 0 
#define NCP_NVM_DEBUG_END_OFFSET_FROM_USER_PTR(_size) 0
#define NCP_NVM_ADD_DBG_FIELDS(_ptr, _size) (_ptr)
#define NCP_NVM_VALIDATE_DBG_FIELDS(_pPtr)
#endif
    

#undef NCP_MIN_ALLOC_SIZE
#ifdef NCP_ARCH_ARM
#define NCP_MIN_ALLOC_SIZE 64
#endif

#ifdef NCP_ARCH_PPC
#define NCP_MIN_ALLOC_SIZE 128
#endif

#ifdef NCP_MIN_ALLOC_SIZE 

#define NCP_SET_MIN_ALLOC_SIZE(_size) \
    if (_size < NCP_MIN_ALLOC_SIZE) _size = NCP_MIN_ALLOC_SIZE;

#else
#define NCP_SET_MIN_ALLOC_SIZE(_size)  
#endif



/* 
 * definitions of the ncp_malloc/ncp_nvm_malloc family of functions.
 */

#if !defined (NCP_LEAK_DEBUG)
void *
ncp_malloc(ncp_size_t size)
{
    void *p;

    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_malloc_entry, NCP_MSG_ENTRY, 
        "size=%lu\n", (unsigned long)size);
    if (0 == size)
    {
#if 0
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_malloc_zeroSize, NCP_MSG_DEBUG,
                       "WARNING:  ncp_malloc(%d) passed zero size.\n", size); */
#endif
        return 0;
    }

    /*
     * force cache line independence
     * just force min allocation size equal to cache line size
     */
    NCP_SET_MIN_ALLOC_SIZE(size);

    if ((p = __ncp_malloc(size)) == 0)
    {
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_malloc_failed, NCP_MSG_ERROR,
                       "ncp_malloc(%zu) failed.\n", size);
    }

#ifdef NCP_MEMORY_CORUPTION_DEBUG
    if(p != NULL)
    {
        mem_block_alloc(p, size);
    }
#endif
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_malloc_exit, NCP_MSG_EXIT, 
        "p=%p\n", p);
    return p;
}

void *
ncp_calloc(ncp_size_t no, ncp_size_t size)
{
    void *p;

    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_calloc_entry, NCP_MSG_ENTRY, 
        "no=%lu size=%lu\n", (unsigned long)no, (unsigned long)size);
    if (0 == size || 0 == no)
    {
#ifdef NCP_DEBUG
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_calloc_zeroSize, NCP_MSG_DEBUG,
                       "WARNING:  ncp_calloc(no=%lu, size=%lu) passed zero size.\n",
                       (unsigned long)no, (unsigned long)size);
#endif
        return 0;
    }

    /*
     * force cache line independence
     * just force min allocation size equal to cache line size
     */
    size = (no * size); 
    NCP_SET_MIN_ALLOC_SIZE(size);

    if (NULL != (p = __ncp_malloc(size)))
    {
        memset(p, 0,  size);
    }  
    else
    {
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_calloc_failed, NCP_MSG_ERROR,
                       "ncp_calloc(no=%zu, size=%zu) failed.\n", no, size);
    }
  
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_calloc_exit, NCP_MSG_EXIT, 
        "p=%p\n", p);
    return p;
}

void *
ncp_realloc(void *ptr, ncp_size_t size)
{
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_realloc_entry, NCP_MSG_ENTRY, 
        "ptr=%p size=%lu\n", ptr, (unsigned long)size);
    if (0 == size)
    {
#ifdef NCP_DEBUG
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_realloc_zeroSize, NCP_MSG_DEBUG,
                       "WARNING:  ncp_realloc(%lu) passed zero size.\n", (unsigned long)size);
#endif
        return 0;
    }
    
    /*
     * force cache line independence
     * just force min allocation size equal to cache line size
     */
    NCP_SET_MIN_ALLOC_SIZE(size);

    if ((ptr = __ncp_realloc(ptr, size)) == 0)
    {
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_realloc_failed, NCP_MSG_ERROR,
                       "ncp_realloc(ptr=%p, size=%zu) failed.\n", ptr, size);
    }
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_realloc_exit, NCP_MSG_EXIT, 
        "ptr=%p\n", ptr);
    return ptr;
}

void 
ncp_free(void *ptr)
{
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_free_entry, NCP_MSG_ENTRY, 
        "ptr=%p\n", ptr);
    if (ptr == NULL)
    {
#ifdef NCP_DEBUG
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_free_nullPointer, NCP_MSG_DEBUG,
                       "WARNING:  ncp_free(%p) passed a NULL pointer.\n", ptr);
#endif
        return;
    }
#ifdef NCP_USE_NVM
    if ((ptr > (void *) ncp_nvm_vaddr) &&
        (ptr < (void *) (ncp_nvm_vaddr + ncp_nvm_size)))
    {
#ifdef NCP_DEBUG
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_free_passedNvmPointer, NCP_MSG_DEBUG,
                       "WARNING: ncp_free(%p) passed a pointer in NVM region!\n", ptr);
#endif
        return;
    }
#endif

#ifdef NCP_MEMORY_CORUPTION_DEBUG
    if(mem_block_free(ptr) < 0)
        return;
#endif
    __ncp_free(ptr);
}

void *
ncp_nvm_malloc(ncp_size_t size)
{
    void *p;
    
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_nvm_malloc_entry, NCP_MSG_ENTRY, 
        "size=%lu\n", (unsigned long)size);
    if (0 == size)
    {
#ifdef NCP_DEBUG
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_nvm_malloc_zeroSize, NCP_MSG_DEBUG,
                       "WARNING:  ncp_nvm_malloc(%lu) passed zero size.\n", (unsigned long)size);
#endif
        return 0;
    }

    /*
     * force cache line independence
     * just force min allocation size equal to cache line size
     */
    NCP_SET_MIN_ALLOC_SIZE(size);

    if ((p = __ncp_nvm_malloc(size + NCP_NVM_DEBUG_OVERHEAD(size))) == 0)
    {
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_nvm_malloc_failed, NCP_MSG_ERROR,
                       "ncp_nvm_malloc(%zu) failed.\n", size);
    }
    
    p = NCP_NVM_ADD_DBG_FIELDS(p, size);

	VALGRIND_MALLOCLIKE_BLOCK(p, size, 0, 0);
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_nvm_malloc_exit, NCP_MSG_EXIT, 
        "p=%p\n", p);
    return p;
}

void *
ncp_nvm_calloc(ncp_size_t no, ncp_size_t size)
{
    void *p;

    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_nvm_calloc_entry, NCP_MSG_ENTRY, 
        "no=%lu size=%lu\n", (unsigned long)no, (unsigned long)size);
    if (0 == size || 0 == no)
    {
#ifdef NCP_DEBUG
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_nvm_calloc_zeroSize, NCP_MSG_DEBUG,
                       "WARNING:  ncp_nvm_calloc(no=%lu, size=%lu) passed zero size.\n",
                       (unsigned long)no, (unsigned long)size);
#endif
        return 0;
    }

    /*
     * force cache line independence
     * just force min allocation size equal to cache line size
     */

    size = no * size;
    NCP_SET_MIN_ALLOC_SIZE(size);


    if (NULL != (p = __ncp_nvm_malloc(size + NCP_NVM_DEBUG_OVERHEAD(size))))
    {
        memset(p, 0, size);
    }  
    else        
    {
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_nvm_calloc_failed, NCP_MSG_ERROR,
                       "ncp_nvm_calloc(no=%zu, size=%zu) failed.\n", no, size);
    }
    
    p = NCP_NVM_ADD_DBG_FIELDS(p, size);

	VALGRIND_MALLOCLIKE_BLOCK(p, (size), 0, 1);
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_nvm_calloc_exit, NCP_MSG_EXIT, 
        "p=%p\n", p);
    return p;
}

void *
ncp_nvm_realloc(void *ptr, ncp_size_t size)
{
    
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_nvm_realloc_entry, NCP_MSG_ENTRY, 
        "ptr=%p size=%lu\n", ptr, (unsigned long)size);
    if (0 == size)
    {
#ifdef NCP_DEBUG
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_nvm_realloc_zeroSize, NCP_MSG_DEBUG,
                       "WARNING:  ncp_nvm_realloc(ptr=%p, size=%lu) passed zero size.\n",
                       ptr, (unsigned long)size);
#endif
        return 0;
    }

    /*
     * force cache line independence
     * just force min allocation size equal to cache line size
     */
    NCP_SET_MIN_ALLOC_SIZE(size);

	VALGRIND_FREELIKE_BLOCK(ptr, 0);

    /* NOTE: this macro will modify the value of "ptr" if debug mode is selected */
    NCP_NVM_VALIDATE_DBG_FIELDS(&ptr);

    if (NULL == (ptr = __ncp_nvm_realloc(ptr, size + NCP_NVM_DEBUG_OVERHEAD(size))))
    {
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_nvm_realloc_failed, NCP_MSG_ERROR,
                       "ncp_nvm_realloc(ptr=%p, size=%zu) failed.\n", ptr, size);
        VALGRIND_MALLOCLIKE_BLOCK(ptr, size, 0, 1);
        return ptr;        
    }  

    ptr = NCP_NVM_ADD_DBG_FIELDS(ptr, size);
    
	VALGRIND_MALLOCLIKE_BLOCK(ptr, size, 0, 1);
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_nvm_realloc_exit, NCP_MSG_EXIT, 
        "ptr=%p\n", ptr);
    return ptr;
}
           
void 
ncp_nvm_free(void *ptr)
{
    
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_nvm_free_entry, NCP_MSG_ENTRY, 
        "ptr=%p\n", ptr);
    if (ptr == NULL)
    {
#ifdef NCP_DEBUG
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_nvm_free_nullPointer, NCP_MSG_DEBUG,
                       "WARNING:  ncp_nvm_free(%p) passed a NULL pointer.\n", ptr);
#endif
        return;
    }

#ifdef NCP_USE_NVM
    if (((unsigned long) ptr < ncp_nvm_vaddr) ||
        ((unsigned long) ptr > (ncp_nvm_vaddr + ncp_nvm_size)))
    {
#ifdef NCP_DEBUG
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_nvm_free_nonNvmPointer, NCP_MSG_DEBUG,
                       "WARNING: ncp_nvm_free(%p) passed a pointer not in NVM region!\n", ptr);
#endif
        return;
    }
#endif

    /* NOTE: this macro will modify the value of "ptr" if debug mode is selected */
    NCP_NVM_VALIDATE_DBG_FIELDS(&ptr);
        
    __ncp_nvm_free(ptr);
	VALGRIND_FREELIKE_BLOCK(ptr, 0);
    return;
}

#endif  /* NCP_LEAK_DEBUG */

int
ncp_strlen(const char *s)
{
    return strlen(s);
}

char *
ncp_strcpy(char *dest, const char *src)
{
    return strcpy(dest, src);
}

char *
ncp_strdup(const char *str)
{
    char *nstr;

    nstr = (char *)ncp_malloc(ncp_strlen(str) + 1);
    if (nstr == NULL) 
    {
        return NULL;
    }
    ncp_strcpy(nstr, str);
    return(nstr);
}

/* 
 * New secure-code string APIS
 */
size_t ncp_strnlen(const char *str, size_t maxlen)
{
     size_t i;
     for(i = 0; i < maxlen && str[i]; i++);
     return i;
}

#ifdef NCP_MEMXXX_APIS_ARE_FUNCTIONS
void *
ncp_memcpy(void *to, const void *from, ncp_uint32_t size)
{
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_memcpy_entry, NCP_MSG_ENTRY, 
        "to=%p size=%d\n", to, size);
    return memcpy(to, from, size);
}
ncp_uint32_t 
ncp_memcmp(const void *m1, const void *m2, ncp_uint32_t size)
{
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_memcmp_entry, NCP_MSG_ENTRY, 
        "size=%d\n", size);
    return memcmp(m1, m2, size);
}

void *
ncp_memset(void *m, ncp_uint8_t val, ncp_uint32_t size)
{
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_memset_entry, NCP_MSG_ENTRY, 
        "m=%p val=%d size=%d\n", m, val, size);
    return memset(m, val, size);
}
#endif

void
ncp_host_to_pci_buf32(ncp_uint32_t *buf, int count)
{
#ifdef NCP_BIG_ENDIAN
    int i;

    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_host_to_pci_buf32_entry, NCP_MSG_ENTRY, 
        "buf=%p count=%d\n", buf, count);
    for (i = 0; i < count; i++)
    {
        buf[i] = (((buf[i] & 0x000000ff) << 24) |
                  ((buf[i] & 0x0000ff00) <<  8) |
                  ((buf[i] & 0x00ff0000) >>  8) |
                  ((buf[i] & 0xff000000) >> 24));
    }
#endif
}

void
ncp_convert_to_le(char *s, const char *bp, int len)
{
    int i, j, k;
    int rem;
            
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_convert_to_le_entry, NCP_MSG_ENTRY, 
        "len=%d\n", len);
    for (k = 0;  k < len/4; k++)
    {
        i = k*4;
        j = i+3;
        s[i] = bp[j];
        s[j] = bp[i];
        s[i+1] = bp[j-1];
        s[j-1] = bp[i+1];
    }
    rem = len % 4;
    if (rem)
        switch (rem)
        {
        case 1:
            s[len - 1] = 0x00;
            s[len] = 0x00;
            s[len +1 ] = 0x00;
            s[len +2 ] = bp[len-1];
            break;
        case 2:
            s[len - 2] = 0x00;
            s[len - 1] = 0x00;
            s[len ] = bp[len -1];
            s[len +1 ] = bp[len-2];
            break;
        case 3:
            s[len - 3] = 0x00;
            s[len -2 ] = bp[len -1];
            s[len -1 ] = bp[len -2];
            s[len ] = bp[len-3];
            break;
        }
    return;
}

void
ncp_convert_to_be(char *s, const char *bp, int len)
{
    int i, j, k;
    int rem;
            
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_convert_to_be_entry, NCP_MSG_ENTRY, 
        "len=%d\n", len);
    for (k = 0;  k < len/4; k++)
    {
        i = k*4;
        j = i+3;
        s[i] = bp[j];
        s[j] = bp[i];
        s[i+1] = bp[j-1];
        s[j-1] = bp[i+1];
    }
    rem = len % 4;
    if (rem)
        switch (rem)
        {
        case 1:
            s[len - 1] = bp[len + 2];
         /* s[len     ] = 0x00;
            s[len + 1 ] = 0x00;
            s[len + 2 ] = 0x00; */
            break;
        case 2:
            s[len - 2] = bp[len + 1];
            s[len - 1] = bp[len    ];
         /* s[len    ] = 0x00;
            s[len + 1] = 0x00; */
            break;
        case 3:
            s[len - 3] = bp[len    ];
            s[len - 2] = bp[len - 1];
            s[len - 1] = bp[len - 2];
         /* s[len    ] = 0x00; */
            break;
        }
    return;
}

ncp_st_t
ncp_nvm_robust_malloc(ncp_size_t size, void **pPtr, ncp_bool_t doMemset)
{

	*pPtr = malloc(size + NCP_NVM_DEBUG_OVERHEAD(size));
	if (doMemset){
		memset(*pPtr,0,size + NCP_NVM_DEBUG_OVERHEAD(size));
	}
	return NCP_ST_SUCCESS;
} 

ncp_st_t
ncp_nvm_robust_realloc(void *origPtr, ncp_size_t size, void **pPtr)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_nvm_robust_realloc_entry, NCP_MSG_ENTRY, 
        "origPtr=%p size=%lu pPtr=%p\n", origPtr, (unsigned long)size, pPtr);
    if (0 == size)
    {
#ifdef NCP_DEBUG
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_nvm_robust_realloc_zeroSize, NCP_MSG_DEBUG,
                       "WARNING:  ncp_nvm_robust_realloc(origPtr=%p, size=%lu) passed zero size.\n",
                       origPtr, (unsigned long)size);
#endif
        *pPtr = NULL;
        NCP_RETURN(NCP_ST_INVALID_PARAMETER);
    }

    /*
     * force cache line independence
     * just force min allocation size equal to cache line size
     */
    NCP_SET_MIN_ALLOC_SIZE(size);

	VALGRIND_FREELIKE_BLOCK(origPtr, 0);

    /* NOTE: this macro will modify the value of "ptr" if debug mode is selected */
    NCP_NVM_VALIDATE_DBG_FIELDS(&origPtr);

    NCP_CALL(__ncp_nvm_robust_realloc(origPtr, size + NCP_NVM_DEBUG_OVERHEAD(size), pPtr));
    
    *pPtr = NCP_NVM_ADD_DBG_FIELDS(*pPtr, size);

	VALGRIND_MALLOCLIKE_BLOCK(*pPtr, size, 0, 0);

NCP_RETURN_LABEL
    if (ncpStatus != NCP_ST_SUCCESS)
    {
        *pPtr = NULL;
    }       
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_nvm_robust_realloc_exit, NCP_MSG_EXIT, 
        "ncpStatus=%d\n", ncpStatus);
    return(ncpStatus);
} 

ncp_st_t
ncp_nvm_robust_calloc(ncp_size_t num, ncp_size_t size, void **pPtr)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_nvm_robust_calloc_entry, NCP_MSG_ENTRY, 
        "num=%lu size=%lu pPtr=%p\n", (unsigned long)num, (unsigned long)size, pPtr);
    if (0 == size || 0 == num )
    {
#ifdef NCP_DEBUG
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_nvm_calloc_zeroSize, NCP_MSG_DEBUG,
                       "WARNING:  ncp_nvm_robust_calloc(num=%lu, size=%lu) passed zero size.\n",
                       (unsigned long)num, (unsigned long)size);
#endif
        *pPtr = NULL;
        NCP_RETURN(NCP_ST_INVALID_PARAMETER);
    }
    
#ifdef NCP_USE_NVM

    if ( NCP_NVM_MAX_SIZE/size < num )
    {
#ifdef NCP_DEBUG
        NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_nvm_calloc_zeroSize, NCP_MSG_DEBUG,
                       "WARNING:  ncp_nvm_robust_calloc(num=%lu, size=%lu) SIZE_T overflow.\n",
                       (unsigned long)num, (unsigned long)size);
#endif
        *pPtr = NULL;
        NCP_RETURN(NCP_ST_INVALID_PARAMETER);
    }

#endif 

    size = num * size;
    NCP_SET_MIN_ALLOC_SIZE(size);

    NCP_CALL(__ncp_nvm_robust_malloc(size + NCP_NVM_DEBUG_OVERHEAD(size), pPtr));
    ncp_memset(*pPtr, 0, size);
    
    *pPtr = NCP_NVM_ADD_DBG_FIELDS(*pPtr, size);

	VALGRIND_MALLOCLIKE_BLOCK(*pPtr, (size), 0, 1);

NCP_RETURN_LABEL
    if (NCP_ST_SUCCESS != ncpStatus )
    {
        *pPtr = NULL;
    }
    NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_nvm_robust_calloc_exit, NCP_MSG_EXIT, 
        "ncpStatus=%d\n", ncpStatus);
    return(ncpStatus);
} 

ncp_st_t 
ncp_nvm_robust_free(void **pPtr)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
	free (*pPtr);
	*pPtr = 0;


    return(ncpStatus);
}

ncp_byte_order_t 
ncp_get_byte_order(void)
{
#ifdef NCP_BIG_ENDIAN
    return cBigEndian;
#else
    return cLittleEndian;
#endif
}


