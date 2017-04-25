/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2015, Intel Corporation.                               *
 **                                                                       *
 **************************************************************************/

#ifndef __SAL_ARCH_ARM64_BARRIER_H__
#define __SAL_ARCH_ARM64_BARRIER_H__

#include "uboot/ncp_sal_types.h"

#define NCP_SYSMEM_BARRIER()  \
    __asm__ __volatile__ ("dmb 0xf" : : : "memory")

#define NCP_SYSMEM_STORE_BARRIER() \
    __asm__ __volatile__ ("dmb st" : : : "memory")

#define NCP_ISYNC_BARRIER() \
    __asm__ __volatile__ ("dsb SY" : : : "memory")

/** Load-acquire and store-release operations **/
#define ARCH_HAS_STORE_RELEASE_INSTRUCTION 1

static __inline__
void arch_store_release_16b(ncp_uint16_t val, volatile ncp_uint16_t *addr)
{
    /* 'Q': "A memory reference with base register and no offset," as required
     * by stlrh. By dereferencing addr, we tell Q to make a reference to the
     * address that addr points to.
     */
    __asm__ __volatile__("stlrh %w0, %1" :: "r" (val), "Q" (*addr) : "memory");
}

#endif /* __SAL_ARCH_ARM64_BARRIER_H__ */
