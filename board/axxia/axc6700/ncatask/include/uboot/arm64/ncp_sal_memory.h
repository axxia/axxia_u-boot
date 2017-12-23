/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2015, Intel Corporation.                               *
 **                                                                       *
 **************************************************************************/

#ifndef __SAL_ARCH_ARM64_MEMORY_H__
#define __SAL_ARCH_ARM64_MEMORY_H__

#if defined(NCP_NCA_COHERENT_IO)

static __inline__ void 
arch_prefetch_data_for_write(const void *mva)
{
    __asm__ __volatile__("prfm PSTL1KEEP, [%0]" :: "r"(mva) : );
}

static __inline__ void 
arch_prefetch_data(const void *mva)
{
    __asm__ __volatile__("prfm PLDL1KEEP, [%0]" :: "r"(mva) : );
}

static __inline__ void 
arch_prefetch_data_for_write_l2_keep(const void *mva)
{
    __asm__ __volatile__("prfm PSTL2KEEP, [%0]" :: "r"(mva) : );
}

static __inline__ void 
arch_prefetch_data_for_write_l2_stream(const void *mva)
{
    __asm__ __volatile__("prfm PSTL2STRM, [%0]" :: "r"(mva) : );
}

static __inline__ void 
arch_prefetch_data_l2_keep(const void *mva)
{
    __asm__ __volatile__("prfm PLDL2KEEP, [%0]" :: "r"(mva) : );
}

#else

static __inline__ void
arch_prefetch_data_for_write(const void *mva)
{
    return;
}

static __inline__ void
arch_prefetch_data(const void *mva)
{
    return;
}

static __inline__ void 
arch_prefetch_data_for_write_l2_keep(const void *mva)
{
    return;
}

static __inline__ void 
arch_prefetch_data_for_write_l2_stream(const void *mva)
{
    return;
}

static __inline__ void 
arch_prefetch_data_l2_keep(const void *mva)
{
    return;
}

#endif /* defined(NCP_NCA_COHERENT_IO) */

#endif /* __SAL_ARCH_ARM64_MEMORY_H__ */
