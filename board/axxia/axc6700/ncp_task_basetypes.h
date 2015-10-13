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

#include <config.h>
#include <common.h>
#include <asm/string.h>
#include <ubi_uboot.h>

#define NCP_API extern
#define NCP_EXPORT_SYMBOL(sym) EXPORT_SYMBOL(sym)

/*
 * Basic memory types
 */

#include <linux/types.h>

/*
 * Boolean constants
 */
#define FALSE 0
#define TRUE  1

/*
 * Numeric types
 */
typedef unsigned char      __uint8_t;
typedef unsigned short     __uint16_t;
typedef unsigned           __uint32_t;
typedef unsigned long long __uint64_t;

typedef int8_t     ncp_int8_t;
typedef int16_t    ncp_int16_t;
typedef int32_t    ncp_int32_t;

typedef __uint8_t  ncp_uint8_t;
typedef __uint16_t ncp_uint16_t;
typedef __uint32_t ncp_uint32_t;

typedef __uint8_t  ncp_bool_t;

typedef int64_t    ncp_int64_t;
typedef __uint64_t ncp_uint64_t;



/*
 * These hanbdles do not really exist in UBOOT environment
 */
typedef void * ncp_hdl_t;
typedef void * ncp_vp_hdl_t;
typedef void * ncp_sem_t;
typedef void * ncp_dev_hdl_t;
typedef void * ncp_map_t;
typedef void * ncp_map_value_t;
typedef void * spinlock_flags_t;


/*
 * misc dev and ncp definitions
 */

/* macros to convert a 64-bit address to upper and lower 32-bit parts */
#define NCP_ADDR_UPPER(addr) ( (ncp_uint32_t) (addr >> 32) )
#define NCP_ADDR_LOWER(addr) ( (ncp_uint32_t) (addr & 0xFFFFFFFF))


#define NCP_REGION_NCA_AXI       (NCP_REGION_ID(0x101,  0)) /* 257.0 */
#define NCP_MAX_DEVS 1

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

typedef struct {
    int             id;
    ncp_rev_id_t    rev;
    ncp_nca_hdl_t   ncaHdl;
    ncp_bus_adaptor_t   busAdaptor;
    ncp_uint32_t        domainId;
    ncp_bool_t          domainIsInternal; /* domain is on Local Core(s)? */
} ncp_t;

typedef ncp_uint32_t ncp_region_id_t;


typedef struct ncp_task_ncaV2_domain_bundle_s
{
    ncp_uint64_t sharedPhysAddr;
    ncp_int32_t  sharedSize;
    void         *kernVA;
    ncp_bool_t   isMapped;
}ncp_task_ncaV2_domain_bundle_t;


typedef struct ncp_dev_s {
    ncp_task_ncaV2_domain_bundle_t myDomainBundle;
} ncp_dev_t;

/*
 * MISC SAL
 */

#define NCP_SYSMEM_BARRIER() \
    __asm__ __volatile__ ("dmb" : : : "memory")

#define NCP_ISYNC_BARRIER() \
    __asm__ __volatile__ ("dsb" : : : "memory")

#define NCP_PRINT_LINE_FILE
#define NCP_PRINT_LINE_FILE_MSG(...)

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

/*
 * API parameter checking can be disabled by defining NCP_CHECK_DISABLED.   Time-critical APIs
 * may be converted to use this new macro.
 */

#ifndef NCP_CHECK_DISABLED
#define NCP_CHECK(_condition, _err) NCP_ASSERT((_condition), (_err))
#else
#define NCP_CHECK(_condition, _err)
#endif


/*
 * A general purpose way to eliminate warnings due the the label not being referenced.
 *
 */
#define NCP_RETURN_LABEL \
goto ncp_return; \
ncp_return:

#define NCP_IS_PRIMARY_DOMAIN(n)    (n->domainId == 0)
#define NCP_IS_SECONDARY_DOMAIN(n)  (n->domainId  > 0)

#define NCP_MSG(type, ...) printf(__VA_ARGS__)
#define NCP_LOG NCP_MSG
#define NCP_MSG_INFO  1
#define NCP_MSG_ERROR 2
#define NCP_MSG_DEBUG 3

#define NCP_TASK_REGISTER_GROUP_INTERRUPTS(...)

#define NCP_MEM_MMAP(_dev, _startVA, _size, _physAddr) (_physAddr)
#define NCP_USER_MEM_UNMAP(...)
#define munmap(...)

#define ncp_nvm_malloc(_sz) malloc(_sz)
#define ncp_nvm_free(_ptr)  free(_ptr)
#define ncp_memcpy(_dst_,_src,_len) memcpy(_dst_,_src,_len)
#define ncp_memset(_dst, _val, _len) memset(_dst, _val, _len)
#define ncp_sys_usleep(_val) udelay(_val)

/*
 * Dummy versions of internal functions
 */

#define ncp_task_v2_get_taskHdl(...)    (NCP_ST_SUCCESS)
#define ncp_task_v2_store_taskHdl(...)  (NCP_ST_SUCCESS)
#define ncp_task_v2_destroy_key(...)
#define NCP_VP_VALIDATE_HANDLE(...)
#define NCP_NCA_VALIDATE_NCP_HDL(...)
#define ncp_vp_cpu_terminate_template_id_get(...)
#define ncp_vpm_task_param_decode(...)
#define ncp_vpm_task_param_encode(vpHdl, to, from)  \
    memcpy(to, from, 32)
#endif /* NCP_STATUS_H */
