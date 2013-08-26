/**************************************************************************
 **                                                                        *
 **   LSI Corporation, Inc. CONFIDENTIAL                                   *
 **                                                                        *
 **                       PROPRIETARY NOTE                                 *
 **                                                                        *
 **    This software contains information confidential and proprietary     *
 **    to LSI Corporation Inc.  It shall not be reproduced in whole or in  *
 **    part, or transferred to other documents, or disclosed to third      *
 **    parties, or used for any purpose other than that for which it was   *
 **    obtained, without the prior written consent of LSI Corporation Inc. *
 **    (c) 2008-2013, LSI Corporation Inc.  All rights reserved.           *
 **                                                                        *
 **  ***********************************************************************
 **
 **  ***********************************************************************
 **   File:       $HeadURL: http://txasoft2.agere.com/svn/software/src/trunk/rte/api/mme/ncp_mme_pvt.h $
 **   Version:    $Revision: 3317 $
 **   Date:       $Date: 2008-11-15 00:57:17 -0600 (Sat, 15 Nov 2008) $
 ** **************************************************************************/
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
#else
#define SWAP_LE_64(_source,_dest)                     \
{                                                     \
  _dest = _source; \
}
#endif

#define NCP_MME_VALIDATE_AND_LOCK \
    if ( ( mme == NULL) ||  \
         ( mme->cookie != NCP_MME_HANDLE_COOKIE)) { \
            ncpStatus = NCP_ST_MME_INVALID_HANDLE;  \
            goto ncp_return;  \
    } \
    ncp_sem_wait(&mme->lock);

#define NCP_MME_RETURN \
    if ( ( ncpStatus != NCP_ST_INVALID_HANDLE) && \
         ( ncpStatus != NCP_ST_MME_INVALID_HANDLE)) { \
              ncp_sem_post(&mme->lock); \
    } \
    return ncpStatus;

#endif /* __NCP_MME_PVT_H__ */
