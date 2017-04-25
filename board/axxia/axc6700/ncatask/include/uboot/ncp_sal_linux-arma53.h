/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/

/*! @file      ncp_sal_linux-arma53.h
    @brief     RTE Target ARM A53 layer specific definitions.
*/

#ifndef __NCP_SAL_LINUX_ARMA53_H__
#define __NCP_SAL_LINUX_ARMA53_H__

#ifdef __KERNEL__

//#include <linux/semaphore.h>
//#include <linux/timer.h>
#include <linux/math64.h>

#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NCP_LINUX
#define NCP_LINUX
#endif



#define   NCP_NVM_VADDR            0x50000000
#define   NCP_DMA_VADDR            0x70000000


#define NCP_EDEV_BUS_ENFORCE_ORDERING() 

#ifdef NCP_KERNEL
#define NCP_IOREMAP_CACHE(_addr, _size)                                   \
({  NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_ioremap_cache, NCP_MSG_DEBUG, "Map CACHED_WB %llx sz=%llx\r\n", _addr, _size);  \
    ioremap_cache(_addr, _size);                                          \
})
#else
#define NCP_IOREMAP_CACHE(_addr, _size)                                   \
({  NCP_TRACEPOINT(Intel_AXXIA_ncp_sal, ncp_sal_ioremap_cache, NCP_MSG_DEBUG, "Map CACHED_WB %llx sz=%llx\r\n", _addr, _size);  \
    ioremap_cache(_addr, _size);                                          \
})
#endif

#ifdef  __KERNEL__
#define NCP_I2C_DIV64_BY_32(div64,div32)                                \
        div_u64((div64), (div32))
#endif


#ifdef __cplusplus
}
#endif

#endif /* __NCP_SAL_LINUX_ARMA53_H__ */
