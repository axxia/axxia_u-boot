/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2015, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/

#ifndef  __NCP_MME_PVT_H__
#define  __NCP_MME_PVT_H__

#define NCP_MME_MAX_POOL_ID               23  /* 0 - 23 for X7 */
#define NCP_MME_MAX_MPCQ_ID               63  /* 0 - 63 for X7 */
#define NCP_MME_POOL_BLOCK_SIZES          4
#define NCP_MME_NUM_VPP_POOLS             2
#define NCP_MME_MPCQ_BLOCK_SIZES          4
#define NCP_MME_MPCQ_THRESH               15 /* Size in 64B blocks = 960B */
#define NCP_MME_MPCQ_NUM_ENTRIES          128
#define NCP_MME_VPP_POOL                  0
#define NCP_MME_SHARED_POOL               1
#define NCP_MME_CPU_USER_POOL             2
#define NCP_MME_CPU_KERNEL_POOL           3
#define NCP_MME_HANDLE_COOKIE             0x51112123
#define NCP_MME_MAX_POOL_SIZE             0x800000000ULL

#define NCP_MME_TOTAL_IFLS_ENTRIES    4096
#define NCP_MME_HWM                   0.80
#define NCP_MME_LWM                   0.20
#define NCP_MME_HWMH                  0.20
#define NCP_MME_LWMH                  0.20

#define NCP_MME_CAT_SIZE              0x780
#define NCP_MME_CAT_FORMAT_0          0
#define NCP_MME_CAT_NUM_ENTRIES       96
#define NCP_MME_CAT_WORDS_PER_ENTRY   5  /* 4B words */

#define NCP_MME_FLUSH_MAX_POLL_TIME   10000000    /* 10s */
#define NCP_MME_FLUSH_ITER_POLL_TIME  100000      /* 100ms */
#define NCP_MME_FLUSH_POLL_ITERS      (NCP_MME_FLUSH_MAX_POLL_TIME / NCP_MME_FLUSH_ITER_POLL_TIME)
#define NCP_MME_IFLS_POLL_ITERS       NCP_MME_FLUSH_POLL_ITERS
#define NCP_MME_IFLS_POLL_TIME        NCP_MME_FLUSH_ITER_POLL_TIME
#define NCP_MME_MREF_POLL_ITERS       NCP_MME_FLUSH_POLL_ITERS
#define NCP_MME_MREF_POLL_TIME        NCP_MME_FLUSH_ITER_POLL_TIME
#define NCP_MME_MPCQ_POLL_ITERS       NCP_MME_FLUSH_POLL_ITERS
#define NCP_MME_MPCQ_POLL_TIME        NCP_MME_FLUSH_ITER_POLL_TIME

#define NCP_MME_MPCQ_PER_VALID_POLL_RATE    2000000
#define NCP_MME_MPCQ_MAX_SERVICE_RATE       30000000
#define NCP_MME_MPCQ_CLOCK_RATE             400000000

#define MEM_ALIGN(alignee,numAlignBits) \
{ \
  if ( ( ( alignee >> numAlignBits) << numAlignBits) != alignee)        \
  { \
    alignee >>= numAlignBits; \
    alignee++;            \
    alignee <<= numAlignBits; \
  } \
}

#ifdef NCP_BIG_ENDIAN
#define SWAP_LE_64(_source,_dest)                     \
{                                                     \
  _dest = (((_source >> 56) & 0xffull)            |   \
           ((_source >> 40) & 0xff00ull)          |   \
           ((_source >> 24) & 0xff0000ull)        |   \
           ((_source >> 8)  & 0xff000000ull)      |   \
           ((_source << 8)  & 0xff00000000ull)    |   \
           ((_source << 24) & 0xff0000000000ull)  |   \
           ((_source << 40) & 0xff000000000000ull)|   \
           ((_source << 56) & 0xff00000000000000ull));\
}

#define SWAP_LE_32(_source, _dest)       \
({                                       \
    _dest = NCP_ENDIAN_SWAP_32(_source); \
})

#define SWAP_BE_32(_source, _dest) \
({                                 \
    _dest = _source;               \
})

#else
#define SWAP_LE_64(_source,_dest) \
{                                 \
  _dest = _source;                \
}

#define SWAP_LE_32(_source, _dest) \
({                                 \
    _dest = _source; \
})

#define SWAP_BE_32(_source, _dest)       \
({                                       \
    _dest = NCP_ENDIAN_SWAP_32(_source); \
})

#endif

#ifndef NCP_CHECK_DISABLED

#define NCP_MME_VALIDATE_HANDLE(_myHdl) ({ \
    ncp_st_t _st = NCP_ST_SUCCESS; \
    if ( ( _myHdl == NULL ) || \
	 ( _myHdl->cookie != NCP_MME_HANDLE_COOKIE)) {\
         _st = NCP_ST_MME_INVALID_HANDLE; \
    } \
    _st; \
})
#else /* #ifndef NCP_CHECK_DISABLED */
#define NCP_MME_VALIDATE_HANDLE(_myHdl) NCP_ST_SUCCESS
#endif


typedef struct
{
#ifdef NCP_BIG_ENDIAN
          /* word 0 */
     unsigned      mpcqId_63_32                      : 32;
          /* word 1 */
     unsigned      mpcqId_31_0                       : 32;
#else    /* Little Endian */
          /* word 0 */
     unsigned      mpcqId_63_32                      : 32;
          /* word 1 */
     unsigned      mpcqId_31_0                       : 32;
#endif
} ncp_mme_mpcq_poke_reg_t;

#endif /* __NCP_MME_PVT_H__ */
