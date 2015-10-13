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

#ifndef __ncp_task_inline_funcs_axm55xx__
#define __ncp_task_inline_funcs_axm55xx__

#include <config.h>
/*
#define DEBUG
#include <common.h>
#define NCP_TASK_DEBUG_MME
*/
/*
* =============================
* old ncp_task_inline_funcs.c
* =============================
*/

#if defined(NCP_NCA_COHERENT_IO)
#ifdef NCP_BIG_ENDIAN
NCP_INLINE void
ncp_task_v2_cache_prefetch_L0(const void *pX)
{
if (/*unlikely*/(!(pX)))
return;

__asm__ __volatile__ ("dcbt 0,%0" : : "r" (pX));    /* L0 Cache */
}
NCP_INLINE void
ncp_task_v2_cache_prefetch_for_store_L2(const void *pX)
{
if (/*unlikely*/(!(pX)))
return;

__asm__ __volatile__ ("dcbtst 2,%0" : : "r" (pX));    /* L2 Cache */
}
NCP_INLINE void
ncp_task_v2_cache_prefetch_L2(const void *pX)
{
if (/*unlikely*/(!(pX)))
return;

__asm__ __volatile__ ("dcbt 2,%0" : : "r" (pX));    /* L2 Cache */
}
#else
NCP_INLINE void
ncp_task_v2_cache_prefetch_L0(const void *pX)
{
return;
}
NCP_INLINE void
ncp_task_v2_cache_prefetch_for_store_L2(const void *pX)
{
return;
}
NCP_INLINE void
ncp_task_v2_cache_prefetch_L2(const void *pX)
{
return;
}
#endif
#else
NCP_INLINE void
ncp_task_v2_cache_prefetch_L0(const void *pX)
{
return;
}
NCP_INLINE void
ncp_task_v2_cache_prefetch_for_store_L2(const void *pX)
{
return;
}
NCP_INLINE void
ncp_task_v2_cache_prefetch_L2(const void *pX)
{
return;
}
#endif/* NCP_NCA_COHERENT_IO */

/*
* Forwards
*/
#if !defined(NCP_DEV_SOCKET)
NCP_INLINE ncp_st_t
ncp_task_v2_put_deallocate_immediate(ncp_pvt_task_hdl_t *myTaskHdl,
ncp_ncaV2_task_oPCQ_entry_dealloc_immediate_t
*pDeallocImmediate,
ncp_bool_t wait);
#endif

/* UBOOT */
NCP_INLINE  ncp_st_t
ncp_vp_id_get(ncp_vp_hdl_t vpHdl,ncp_uint8_t *pVpId)
{
*pVpId = 1;  /* FIXME - what do we want here? Does it matter? */
return(NCP_ST_SUCCESS);
}
/* UBOOT */

NCP_INLINE ncp_st_t
ncp_task_v2_CpuPool_alloc_noLock(
ncp_task_ncaV2_pool_t *pPoolEntry,
		ncp_uint32_t size,
		void **taskAddr)
{
int i;

ncp_st_t ncpStatus=NCP_ST_SUCCESS;

/*
* Requested buffer exceeds maximum size ?
*/

#if 0 /* Performance opt - re-enable for debug */
/*
* Requested buffer exceeds maximum size ?
*/

if (size > pPoolEntry->u.cpu.buffListArray[NCP_TASK_NUM_BUFF_SIZES-1].size)
{
NCP_CALL(NCP_ST_TASK_BUFFSIZE_TOO_LARGE);
}
#endif

if (taskAddr == NULL)
{
NCP_MSG(NCP_MSG_ERROR, "NULL TASKADDR\r\n");
return(NCP_ST_NO_MEMORY);
}


for (i=0; i<(NCP_TASK_NUM_BUFF_SIZES); i++)
{
if (size <=  pPoolEntry->u.cpu.buffListArray[i].size)
{
ncp_task_bufflist_t *pBuffList = &pPoolEntry->u.cpu.buffListArray[i];
ncp_buffDescriptor_t *pBuffDesc;

if ((NULL == pBuffList) || (NULL == (*taskAddr = (void *)(pBuffDesc = pBuffList->free))))
{
NCP_MSG(NCP_MSG_INFO, "failed to allocate buffer of size %d in alloc_noLock, pPoolEntry=%p, pBuffList=%p\r\n",
size, pPoolEntry,pBuffList);
NCP_CALL(NCP_ST_NO_MEMORY);
}

#ifdef NCP_TASK_CPU_POOL_IS_LIFO  /* Make FIFO instgead of LIFO? */
pBuffList->free = pBuffDesc->next;
#else
if (NULL == (pBuffList->free = pBuffDesc->next))
{
pBuffList->last = NULL;
}
#endif

pBuffList->numFree--;
if (pBuffList->numFree < pBuffList->freeLowWaterMark)
{
pBuffList->freeLowWaterMark = pBuffList->numFree;
}
/* FIXME - add support for 55xx and multiple CPU pools */
#if defined(NCP_TASK_DBG_BUFFERS)

ncp_task_v2_check_onNca(*taskAddr, pPoolEntry->poolID);

{
if (NCP_TASK_FREE_BUFF_COOKIE != pBuffDesc->cookie)
{
ncp_task_v2_breakpoint(12);
}
				pBuffDesc->cookie = 0;
ncp_task_v2_validate_buffer(*taskAddr, 1, pPoolEntry->poolID);
}
#endif

break;
}
}

if (NCP_TASK_NUM_BUFF_SIZES == i)
{
NCP_CALL(NCP_ST_NO_MEMORY);
}


NCP_RETURN_LABEL

#ifdef NCP_TASK_DBG_TRACK_ALLOC_FREE
if (NCP_ST_SUCCESS == ncpStatus)
{
NCP_MSG(NCP_MSG_INFO, "allocated (noLock) %p\r\n",*taskAddr);
}
#endif
return(ncpStatus);
}

NCP_INLINE ncp_st_t
ncp_task_v2_CpuPool_free_noLock(
ncp_task_ncaV2_pool_t *pPoolEntry,
		void *taskAddr)
{
int i;
ncp_st_t ncpStatus=NCP_ST_SUCCESS;
ncp_bool_t validBuff = FALSE;

#ifdef NCP_TASK_DBG_TRACK_ALLOC_FREE
NCP_MSG(NCP_MSG_INFO, "free (noLock) %p\r\n",taskAddr);
#endif

if (   ((ncp_raw_addr_t)taskAddr >  (ncp_raw_addr_t)(pPoolEntry->pool_EndVA))
|| ((ncp_raw_addr_t)taskAddr <  (ncp_raw_addr_t)(pPoolEntry->pool_VA)))
{
NCP_CALL(NCP_ST_INVALID_VALUE);
}

for (i=0; i < NCP_TASK_NUM_BUFF_SIZES; i++)
{
if ((taskAddr >= pPoolEntry->u.cpu.buffListArray[i].VAstart)
&& (taskAddr < pPoolEntry->u.cpu.buffListArray[i].VAend))
{
ncp_task_bufflist_t *pBuffList
= &pPoolEntry->u.cpu.buffListArray[i];

ncp_buffDescriptor_t *pBuffDesc;

/* Normalize pointer to get start of buffer */
taskAddr = (void*)
((ncp_raw_addr_t)(taskAddr)
& pPoolEntry->u.cpu.buffListArray[i].mask);

pBuffDesc =  (ncp_buffDescriptor_t *)taskAddr;

#if defined(NCP_TASK_DBG_BUFFERS)
{
ncp_buffDescriptor_t *pDbgBuffDesc = (ncp_buffDescriptor_t *)taskAddr;

ncp_task_v2_check_onNca(taskAddr, pPoolEntry->poolID);

if (NCP_TASK_FREE_BUFF_COOKIE == pDbgBuffDesc->cookie)
{
ncp_task_v2_breakpoint(15);
}
ncp_task_v2_validate_buffer(taskAddr, 0, pPoolEntry->poolID);
#if 0
/* DEBUG */
{
int xx;
ncp_uint32_t *pFill=(ncp_uint32_t *)taskAddr;
ncp_uint32_t fillVal=(ncp_raw_addr_t)taskAddr;

fillVal |= 1;
NCP_MSG(NCP_MSG_INFO, "freebuff - fill %p with 0x%x\r\n",
pFill, fillVal);
for (xx=0; xx<(256/sizeof(ncp_uint32_t)); xx++)
{
pFill[xx]=fillVal;
}
}
/* END DEBUG */
#endif
pDbgBuffDesc->cookie = NCP_TASK_FREE_BUFF_COOKIE;
}
#endif


#ifdef NCP_TASK_CPU_POOL_IS_LIFO
pBuffDesc->next     = (struct ncp_buffDescriptor_s *)pBuffList->free;
pBuffList->free = pBuffDesc;
#else
{
ncp_buffDescriptor_t *pBuffDesc2 = pBuffList->last;
if (NULL != pBuffList->free)
{
pBuffList->last
= pBuffDesc2->next
= pBuffDesc;
}
else
{
pBuffList->free
= pBuffList->last
= pBuffDesc;
}
pBuffDesc->next = NULL;
}
#endif

pBuffList->numFree++;
validBuff = TRUE;
break;
}
}

if (FALSE == validBuff)
{
NCP_CALL(NCP_ST_INVALID_BUFF_FOR_TASK_FREE);
}
NCP_RETURN_LABEL

return(ncpStatus);
}

NCP_INLINE ncp_st_t
ncp_task_v2_CpuPool_alloc(
ncp_task_ncaV2_pool_t *pPoolEntry,
		ncp_uint32_t size,
		void **taskAddr)
{
int i;
ncp_st_t ncpStatus=NCP_ST_SUCCESS;
NCP_TASK_LOCK_FLAGS(flags);


#if 0 /* Performance opt - re-enable for debug */
/*
* Requested buffer exceeds maximum size ?
*/

if (size > pPoolEntry->u.cpu.buffListArray[NCP_TASK_NUM_BUFF_SIZES-1].size)
{
NCP_CALL(NCP_ST_TASK_BUFFSIZE_TOO_LARGE);
}
#endif

if (taskAddr == NULL)
{
NCP_MSG(NCP_MSG_INFO, "NULL TASKADDR\r\n");
return(NCP_ST_NO_MEMORY);
}


for (i=0; i<(NCP_TASK_NUM_BUFF_SIZES); i++)
{
if (size <=  pPoolEntry->u.cpu.buffListArray[i].size)
{
ncp_task_bufflist_t *pBuffList = &pPoolEntry->u.cpu.buffListArray[i];
ncp_buffDescriptor_t *pBuffDesc;

NCP_TASK_CLAIM_LOCK(pPoolEntry->poolLock, flags);

if ((NULL == pBuffList) || (NULL == (*taskAddr = (void *)(pBuffDesc = pBuffList->free))))
{
NCP_TASK_FREE_LOCK(pPoolEntry->poolLock, flags);
NCP_MSG(NCP_MSG_INFO, "failed to allocate buffer of size %d in alloc, pPoolEntry=%p, pBuffList=%p\r\n",
size, pPoolEntry,pBuffList);
NCP_CALL(NCP_ST_NO_MEMORY);
}

#ifdef NCP_TASK_CPU_POOL_IS_LIFO
pBuffList->free = pBuffDesc->next;
#else
if (NULL == (pBuffList->free = pBuffDesc->next))
{
pBuffList->last = NULL;
}
#endif
pBuffList->numFree--;
if (pBuffList->numFree < pBuffList->freeLowWaterMark)
{
pBuffList->freeLowWaterMark = pBuffList->numFree;
}

#if defined(NCP_TASK_DBG_BUFFERS)
{

ncp_task_v2_check_onNca(*taskAddr, pPoolEntry->poolID);

if (NCP_TASK_FREE_BUFF_COOKIE != pBuffDesc->cookie)
{
NCP_MSG(NCP_MSG_ERROR,
"ERROR: pBuffDesc->cookie=0x%x, pBuffDesc=%p, size=%d, pPoolEntry=%p",
pBuffDesc->cookie,
pBuffDesc,
size,
pPoolEntry);

ncp_task_v2_breakpoint(14);
}
pBuffDesc->cookie = 0;
ncp_task_v2_validate_buffer(*taskAddr, 1, pPoolEntry->poolID);
}
#endif

NCP_TASK_FREE_LOCK(pPoolEntry->poolLock, flags);

break;
}
}
if (NCP_TASK_NUM_BUFF_SIZES == i)
{
NCP_CALL(NCP_ST_NO_MEMORY);
}

NCP_RETURN_LABEL

#ifdef NCP_TASK_DBG_TRACK_ALLOC_FREE
if (NCP_ST_SUCCESS == ncpStatus)
{
NCP_MSG(NCP_MSG_INFO, "allocated %p\r\n",*taskAddr);
}
#endif
return(ncpStatus);
}


NCP_INLINE ncp_st_t
ncp_task_v2_MMEpool_buffSzBits(void *va, int poolID, unsigned *sizeBits)
{
ncp_st_t ncpStatus = NCP_ST_SUCCESS;
ncp_task_ncaV2_pool_t *pPoolEntry = &pNcpNcaV2_TaskSwState->taskMemoryPool[poolID];
int i;

for (i = 0; i < 4; i++)
{
if ( (va >= pPoolEntry->blocksVA[i])
&& (va < pPoolEntry->blocksVAend[i]))
{
break;
}
}
if (4 == i)
{
NCP_CALL(NCP_ST_TASK_BUFFSZ_OUT_OF_BOUNDS);
}

/* return the size bits */

*sizeBits = i;

NCP_RETURN_LABEL
return(ncpStatus);

}

/* FIXME: Optimize */
NCP_INLINE ncp_st_t
ncp_task_v2_MMEpool_alloc(
ncp_pvt_task_hdl_t *myTaskHdl,
ncp_uint32_t size,
void **taskAddr)
{
ncp_st_t ncpStatus = NCP_ST_SUCCESS;
ncp_task_mme_allocator_if_t  *pAllocIF;
ncp_uint64_t x64;
ncp_raw_addr_t va;

debug("ncp_task_v2_MMEpool_alloc(): size=%d, queueValid=%d\n", size,
myTaskHdl->mmeAllocator->allocIF[0].queueValid);

#ifdef NCP_TASK_DEBUG_MME
NCP_LOG(NCP_MSG_INFO, "Enter mme alloc: request for %d bytes\r\n",size);
#endif

/*
* The following code will advance to a larger buffer,   if the best-fit
* size is not configured.
*/

if (0 == size)
{
NCP_CALL(NCP_ST_TASK_REQUEST_FOR_ZERO_LENGTH_TASK_BUFFER);
}
else if ((256 >= size) && myTaskHdl->mmeAllocator->allocIF[0].queueValid)
{
pAllocIF = &myTaskHdl->mmeAllocator->allocIF[0];
}
else if (((2*1024) >= size) && myTaskHdl->mmeAllocator->allocIF[1].queueValid)
{
pAllocIF = &myTaskHdl->mmeAllocator->allocIF[1];
}
else if (((16*1024) >= size) && myTaskHdl->mmeAllocator->allocIF[2].queueValid)
{
pAllocIF = &myTaskHdl->mmeAllocator->allocIF[2];
}
else if (((64*1024) >= size) && myTaskHdl->mmeAllocator->allocIF[3].queueValid)
{
pAllocIF = &myTaskHdl->mmeAllocator->allocIF[3];
}
else
{
NCP_LOG(NCP_MSG_INFO, "mme alloc request - buffSize %d too large for pool_%d\r\n",
size,
myTaskHdl->poolID);

NCP_CALL(NCP_ST_TASK_BUFFSIZE_TOO_LARGE);
}

#ifdef NCP_TASK_DEBUG_MME
NCP_LOG(NCP_MSG_INFO, "mme pAllocIF = %p, readP_swVA=0x%p\r\n",pAllocIF,
pAllocIF->readP_swVA);
#endif

mme_alloc_retry:

/*
* Get 64bit Virtual Index (addr) value stored in next mPCQ entry
*/
x64 = *(pAllocIF->readP_swVA);

/*    debug("ncp_task_v2_MMEpool_alloc(): readP_swVA=0x%llx\n", x64); */

if (0LL == x64)
{
/*        debug("ncp_task_v2_MMEpool_alloc(): poking 0x%llx\n",
pAllocIF->readP_hw_indx0_val);
*/
NCP_CALL(ncr_write32(
NCP_REGION_MME_POKE,
0,
(ncp_uint32_t)((pAllocIF->readP_hw_indx0_val
& 0xFFFFFFFF00000000LL) >> 32)));
NCP_CALL(ncr_write32(
NCP_REGION_MME_POKE,
0+4,
(ncp_uint32_t)(pAllocIF->readP_hw_indx0_val
& 0x00000000FFFFFFFFLL)));

goto mme_alloc_retry;
}

*(pAllocIF->readP_swVA) = 0LL; /* Is this eally necessary ? */

va = (ncp_raw_addr_t) x64;

#ifdef NCP_TASK_DEBUG_MME
NCP_LOG(NCP_MSG_INFO, "mPCQ read entry @ %p : VA = %p\r\n",
pAllocIF->readP_swVA,
((void *)va));
#endif

/* Advance read pointer */
if (pAllocIF->readP_swVA != pAllocIF->readP_swVA_max_val)
{
pAllocIF->readP_swVA++;
*(pAllocIF->readP_hwVA) += sizeof(ncp_uint64_t);
}
else
{
pAllocIF->readP_swVA    = pAllocIF->entries_baseVA;
*(pAllocIF->readP_hwVA) = pAllocIF->readP_hw_indx0_val;
}

#ifdef NCP_TASK_DEBUG_MME
NCP_LOG(NCP_MSG_INFO, "new swReadP is %p max is %p, hwReadp=%lld\r\n",
pAllocIF->readP_swVA,
pAllocIF->entries_baseVA,
*(pAllocIF->readP_hwVA));
#endif

*taskAddr = (void *)va;

NCP_RETURN_LABEL
if(ncpStatus != NCP_ST_SUCCESS) {
printf("ncp_task_v2_MMEpool_alloc(): status=%d\n", ncpStatus);
}

return(ncpStatus);
}

NCP_INLINE ncp_st_t
ncp_task_v2_MMEpool_free(
ncp_pvt_task_hdl_t *myTaskHdl,
void *taskAddr)
{
ncp_st_t ncpStatus = NCP_ST_SUCCESS;
ncp_ncaV2_task_oPCQ_entry_dealloc_immediate_t
deallocImmediate = {0}; /* Must init to avoid warning */
/*
* Hack for h/w performance test only!   Requires all traffix to use 256B buffs ONLY!
*/
#ifdef NCP_TASK_HW_WORKAROUND_FORCE_DEALLOC_IMMEDIATE_BUFFSZ_ZERO
ncp_uint32_t *pWords = (ncp_uint32_t *)&deallocImmediate;
pWords[1] = 0;
#endif

/* Note szBits field(s) not used for Shared Pools */
deallocImmediate.ptrCnt = 1;
deallocImmediate.pduSegAddr0
= (ncp_uint64_t)(ncp_raw_addr_t)taskAddr;
deallocImmediate.poolID = myTaskHdl->poolID;

NCP_CALL(NCP_NCA_LOWLEVEL_DEALLOC_IMMEDIATE(myTaskHdl,
&deallocImmediate,
TRUE));

NCP_RETURN_LABEL
return(ncpStatus);
}


NCP_INLINE void
ncp_task_v2_prepare_alloc_or_free_noLock(
ncp_task_ncaV2_pool_t *pPoolEntry,
spinlock_flags_t *retFlags)
{
spinlock_flags_t flags = 0;

NCP_TASK_CLAIM_LOCK(pPoolEntry->poolLock, flags);
*retFlags = flags;
return;
}


/*
* Same as above, except caller aquires lock, thereby allowing more than
* 1 buffer to be allocated per lock/unlock event
*/


NCP_INLINE void
ncp_task_v2_complete_alloc_or_free_noLock(
ncp_task_ncaV2_pool_t *pPoolEntry,
		spinlock_flags_t flags)
{

NCP_TASK_FREE_LOCK(pPoolEntry->poolLock, flags);
return;
}


NCP_INLINE ncp_st_t
ncp_task_v2_CpuPool_free(
ncp_task_ncaV2_pool_t *pPoolEntry,
		void *taskAddr)
{
int i;
ncp_st_t ncpStatus=NCP_ST_SUCCESS;
ncp_bool_t validBuff = FALSE;
NCP_TASK_LOCK_FLAGS(flags);

#ifdef NCP_TASK_DBG_TRACK_ALLOC_FREE
NCP_MSG(NCP_MSG_INFO, "free %p\r\n",taskAddr);
#endif

if (   ((ncp_raw_addr_t)taskAddr >  (ncp_raw_addr_t)(pPoolEntry->pool_EndVA))
|| ((ncp_raw_addr_t)taskAddr <  (ncp_raw_addr_t)(pPoolEntry->pool_VA)))
{
NCP_CALL(NCP_ST_INVALID_VALUE);
}

for (i=0; i < NCP_TASK_NUM_BUFF_SIZES; i++)
{
if ((taskAddr >= pPoolEntry->u.cpu.buffListArray[i].VAstart)
&& (taskAddr < pPoolEntry->u.cpu.buffListArray[i].VAend))
{
ncp_task_bufflist_t *pBuffList
= &pPoolEntry->u.cpu.buffListArray[i];
ncp_buffDescriptor_t *pBuffDesc;

/* Normalize pointer to get start of buffer */
taskAddr = (void*)
((ncp_raw_addr_t)(taskAddr)
& pPoolEntry->u.cpu.buffListArray[i].mask);

pBuffDesc =  (ncp_buffDescriptor_t *)taskAddr;

/* Found the range, so add it to the free list */
NCP_TASK_CLAIM_LOCK(pPoolEntry->poolLock, flags);

#if defined(NCP_TASK_DBG_BUFFERS)
{
ncp_buffDescriptor_t *pDbgBuffDesc = (ncp_buffDescriptor_t *)taskAddr;

ncp_task_v2_check_onNca(taskAddr, pPoolEntry->poolID);

if (NCP_TASK_FREE_BUFF_COOKIE == pDbgBuffDesc->cookie)
{
ncp_task_v2_breakpoint(15);
}
ncp_task_v2_validate_buffer(taskAddr, 0, pPoolEntry->poolID);
#if 0
/* DEBUG */
/* DEBUG */
{
int xx;
ncp_uint32_t *pFill=(ncp_uint32_t *)taskAddr;
ncp_uint32_t fillVal=(ncp_raw_addr_t)taskAddr;

fillVal |= 1;
NCP_MSG(NCP_MSG_INFO, "freebuf - fill %p with 0x%x\r\n",
pFill, fillVal);
for (xx=0; xx<(256/sizeof(ncp_uint32_t)); xx++)
{
pFill[xx]=fillVal;
}
}
/* END DEBUG */
/* END DEBUG */
#endif
pDbgBuffDesc->cookie = NCP_TASK_FREE_BUFF_COOKIE;
}
#endif

#ifdef NCP_TASK_CPU_POOL_IS_LIFO
pBuffDesc->next     = (struct ncp_buffDescriptor_s *)pBuffList->free;
pBuffList->free = pBuffDesc;
#else
{
ncp_buffDescriptor_t *pBuffDesc2 = pBuffList->last;
if (NULL != pBuffList->free)
{
pBuffList->last
= pBuffDesc2->next
= pBuffDesc;
}
else
{
pBuffList->free
= pBuffList->last
= pBuffDesc;
}
pBuffDesc->next = NULL;
}
#endif
pBuffList->numFree++;
validBuff = TRUE;
NCP_TASK_FREE_LOCK(pPoolEntry->poolLock, flags);
break;
}
}
if (FALSE == validBuff)
{
NCP_CALL(NCP_ST_INVALID_BUFF_FOR_TASK_FREE);
}
NCP_RETURN_LABEL

return(ncpStatus);
}

#if !defined(NCP_DEV_SOCKET)

NCP_INLINE ncp_st_t
ncp_task_v2_supply_freebuffer_to_nca(ncp_pvt_task_hdl_t *myTaskHdl,
ncp_uint8_t sizeBits,
ncp_bool_t takeLock)
{
ncp_st_t ncpStatus=NCP_ST_SUCCESS;
void *taskAddr=NULL;
ncp_ncaV2_task_oPCQ_entry_dealloc_immediate_t
deallocImmediate = {0}; /* make compiler happy! */
int bufferSize;


/* FIXME - Take Lock ? use noLock Version ? */

/* Allocate a buffer of the appropriate size */
switch(sizeBits)
{
case 0:
bufferSize = NCP_X7_BUFFER_SZ0;
break;
case 1:
bufferSize = NCP_X7_BUFFER_SZ1;
break;
case 2:
bufferSize = NCP_X7_BUFFER_SZ2;
break;
case 3:
bufferSize = NCP_X7_BUFFER_SZ3;
break;
default:
NCP_CALL(NCP_ST_INVALID_VALUE);
break;

}

NCP_CALL(ncp_task_v2_CpuPool_alloc(
myTaskHdl->poolHdl,
bufferSize,
(void **)&taskAddr));

#ifdef NCP_TASK_DBG_BUFFERS
ncp_task_v2_add_onNca(taskAddr, myTaskHdl->poolID);
#endif

deallocImmediate.ptrCnt = 1;
deallocImmediate.pduSegAddr0
= (ncp_uint64_t)(ncp_raw_addr_t)taskAddr;
deallocImmediate.pduBlockSz0 = sizeBits;
deallocImmediate.poolID      = myTaskHdl->poolID;

/* provide receive buffer to NCA via oPCQ deallocate command */

while(1)
{
ncpStatus = NCP_NCA_LOWLEVEL_DEALLOC_IMMEDIATE(myTaskHdl,
&deallocImmediate,
FALSE);
if (NCP_ST_SUCCESS == ncpStatus)
{
break;
}
else if (NCP_ST_TASK_SEND_QUEUE_FULL == ncpStatus)      {
/* Add code here if debugging stalled oPCQs */
}
else
{
NCP_CALL(ncpStatus);
}
}

#if  defined(NCP_TASK_DBG_55XX_TASK_FLOW)
NCP_MSG(NCP_MSG_INFO,
"Provided RX Buff 0x%p\r\n",
taskAddr);
#endif


NCP_RETURN_LABEL

if ((NCP_ST_SUCCESS != ncpStatus) && taskAddr)
{
#ifdef NCP_KMODE_DEBUG
NCP_LOG(NCP_MSG_INFO,
"In supplyFreeBuff, Error - free Buffer=%p\r\n",
taskAddr);
#endif
ncp_task_v2_CpuPool_free(
myTaskHdl->poolHdl,
	        taskAddr);
NCP_CALL(ncpStatus);
}

return(ncpStatus);

}


/* New - ncaV2 Queue Management - BEGIN */

NCP_INLINE ncp_st_t
ncp_task_v2_process_oPCQ_auxData(ncp_task_pcq_t     *p_oPCQ,
ncp_ncaV2_task_oPCQ_entry_generic_t *p_oPCQentry,
ncp_uint32_t          cmdCode,
ncp_task_ncaV2_oPCQ_aux_data_t *pAuxData,
ncp_uint8_t poolID)
{
ncp_task_ncaV2_oPCQ_aux_data_t *pAuxEntry
= p_oPCQ->u.opcq_info.pAuxWriteEntry;
ncp_st_t ncpStatus = NCP_ST_SUCCESS;

if (cmdCode != 0)
{
pAuxEntry->cmdCode = cmdCode;
pAuxEntry->p_oPCQentry = (volatile ncp_uint64_t *)p_oPCQentry;

if (cmdCode <= NCP_NCAV2_OPCQ_ENTRY_OTASK_GT_2_PTRS)
{
pAuxEntry->clientFreeFn      = pAuxData->clientFreeFn;
pAuxEntry->clientFreeFnArg   = pAuxData->clientFreeFnArg;

switch (pAuxEntry->ptrCnt = pAuxData->ptrCnt)
{
case 6:
pAuxEntry->pduSegAddr5       = pAuxData->pduSegAddr5;
case 5:
pAuxEntry->pduSegAddr4       = pAuxData->pduSegAddr4;
case 4:
pAuxEntry->pduSegAddr3       = pAuxData->pduSegAddr3;
case 3:
pAuxEntry->pduSegAddr2       = pAuxData->pduSegAddr2;
case 2:
pAuxEntry->pduSegAddr1       = pAuxData->pduSegAddr1;
case 1:
pAuxEntry->pduSegAddr0       = pAuxData->pduSegAddr0;       break;
default:
break;
}
#ifdef NCP_TASK_DBG_TRACK_AUX_DATA
NCP_MSG(NCP_MSG_INFO, "added cmd code %d @%p, segAddr=%llx\r\n",
cmdCode, pAuxEntry, pAuxEntry->pduSegAddr0);
#endif
}
else
{
#ifdef NCP_TASK_DBG_TRACK_AUX_DATA
NCP_MSG(NCP_MSG_INFO, "added cmd code %d @%p\r\n",
cmdCode, pAuxEntry);
#endif
}
/*
* Advance
*/
pAuxEntry++;
if (pAuxEntry == p_oPCQ->u.opcq_info.pLastAuxEntry)
{
p_oPCQ->u.opcq_info.pAuxWriteEntry
=  pNcpNcaV2_TaskSwState->outputQueueAuxData[p_oPCQ->ncaQueueId];
}
else
{
p_oPCQ->u.opcq_info.pAuxWriteEntry =  pAuxEntry;
}
p_oPCQ->u.opcq_info.auxEntriesAvail--;
}

/*
* Can we free send buffers?
* FIXME - add support for send done function
*/

if (p_oPCQ->u.opcq_info.auxEntriesAvail != (p_oPCQ->nEntries-2))
{
ncp_task_ncaV2_oPCQ_aux_data_t   *pAuxEntry
= p_oPCQ->u.opcq_info.pAuxReadEntry;
ncp_task_ncaV2_pool_t          *pPool
=  &pNcpNcaV2_TaskSwState->taskMemoryPool[poolID];

do
{
/* Has NCA processed yet? */
if (0LL != (*(pAuxEntry->p_oPCQentry)))
{
break;
}

if ((NCP_NCAV2_OPCQ_ENTRY_OTASK_LE_2_PTRS == pAuxEntry->cmdCode)
|| (NCP_NCAV2_OPCQ_ENTRY_OTASK_GT_2_PTRS == pAuxEntry->cmdCode))
{
#ifdef NCP_TASK_DBG_TRACK_AUX_DATA
NCP_MSG(NCP_MSG_INFO, "processing cmd code %d @%p, segAddr=%llx\r\n",
cmdCode, pAuxEntry, pAuxEntry->pduSegAddr0);
#endif

switch(pAuxEntry->ptrCnt)
{
case 6:
ncp_task_v2_CpuPool_free(
pPool,
		                    (void *)(ncp_raw_addr_t)pAuxEntry->pduSegAddr5);
case 5:
ncp_task_v2_CpuPool_free(
pPool,
		                    (void *)(ncp_raw_addr_t)pAuxEntry->pduSegAddr4);
		            case 4:
ncp_task_v2_CpuPool_free(
pPool,
		                    (void *)(ncp_raw_addr_t)pAuxEntry->pduSegAddr3);
case 3:
ncp_task_v2_CpuPool_free(
pPool,
		                    (void *)(ncp_raw_addr_t)pAuxEntry->pduSegAddr2);
case 2:
ncp_task_v2_CpuPool_free(
pPool,
		                    (void *)(ncp_raw_addr_t)pAuxEntry->pduSegAddr1);
case 1:
ncp_task_v2_CpuPool_free(
pPool,
		                    (void *)(ncp_raw_addr_t)pAuxEntry->pduSegAddr0);
case 0: /* zero length sends do not use a task buffer */
break;
default:
NCP_CALL(NCP_ST_INTERNAL_ERROR);
break;
}
}
else
{
#ifdef NCP_TASK_DBG_TRACK_AUX_DATA
NCP_MSG(NCP_MSG_INFO, "processing cmd code %d @%p\r\n",
cmdCode, pAuxEntry);
#endif
}

pAuxEntry++;
if (pAuxEntry == p_oPCQ->u.opcq_info.pLastAuxEntry)
{
pAuxEntry
= pNcpNcaV2_TaskSwState->outputQueueAuxData[p_oPCQ->ncaQueueId];
}
p_oPCQ->u.opcq_info.auxEntriesAvail++;

} while(p_oPCQ->u.opcq_info.auxEntriesAvail != (p_oPCQ->nEntries-2));

p_oPCQ->u.opcq_info.pAuxReadEntry = pAuxEntry;
}

NCP_RETURN_LABEL

return(ncpStatus);
}


/*
* Queue task completion request to NCA
*/

NCP_INLINE ncp_st_t
ncp_task_v2_put_completion(ncp_pvt_task_hdl_t *myTaskHdl,
ncp_ncaV2_task_completion_data_t *taskAddr,
ncp_bool_t wait)
{
ncp_st_t ncpStatus       = NCP_ST_SUCCESS;
ncp_task_pcq_t  *p_oPCQ  = myTaskHdl->sendQueue;
ncp_ncaV2_task_oPCQ_entry_completion_t *pOutputQueueEntry
= (ncp_ncaV2_task_oPCQ_entry_completion_t *)
p_oPCQ->u.opcq_info.pOPCQentry;
ncp_uint32_t    *wordsEntry
=  (ncp_uint32_t    *)pOutputQueueEntry;
int producerIdx = p_oPCQ->u.opcq_info.opcqProducerIdx;
ncp_uint32_t    *wordsTask = (ncp_uint32_t *)taskAddr;
ncp_task_ncav2_min_completion_data_t *pCompData;


while (1)
{

if (NCP_TASK_55xx_OPCQ_FULL(p_oPCQ,
producerIdx,
myTaskHdl->poolID))
{
/* Queue is FULL */
{
#ifdef DBG_KMODE_INTS
pNcpNcaV2_TaskSwState->dbg_txQueueFull++;
#endif
NCP_TASK_CHECK_FOR_SHUTDOWN();
NCP_TASK_INC_STAT(TxQueueFull);
if (FALSE == wait)
{
ncpStatus = NCP_ST_TASK_SEND_QUEUE_FULL;
goto ncp_return;
}
else
{
NCP_TASK_BLOCK_ON_INTERRUPT(myTaskHdl,
myTaskHdl->dev,
NCP_NCA_WAIT_FOR_TX_INTR,
p_oPCQ->grpId,
p_oPCQ->ncaQueueId);
}
continue;
}
}
else
{
NCP_TASK_INC_STAT(TxQueueNotFull);
break;   /* Get out, we have room */
}
}   /* while(1) */


#ifdef NCP_DEBUG
ncp_memset(pOutputQueueEntry, 0, sizeof(ncp_task_ncaV2_oPCQ_entry_task_t));
#endif

/* All required fields are in 1st 2 words of task */
pCompData = p_oPCQ->u.opcq_info.pCompletionData;
pCompData += producerIdx;
pCompData->completionData_W0
= SWAP_32(wordsTask[0]);
pCompData->completionData_W1
= SWAP_32(wordsTask[1]);

/* Set up and swap word 0 of pcq entry */
pOutputQueueEntry->cmdCode
= NCP_NCAV2_OPCQ_ENTRY_TASK_COMPLETION;
pOutputQueueEntry->interruptOnComplete   = 1;
wordsEntry[0] = SWAP_32(wordsEntry[0]);

pOutputQueueEntry->poolID = myTaskHdl->poolID;
wordsEntry[1] = SWAP_32(wordsEntry[1]);

/* Set up and swap word 2..3 of pcq entry */
pOutputQueueEntry->taskAddr
= SWAP_64(((ncp_raw_addr_t)pCompData));

#if 0 && !defined(NCP_KERNEL)
NCP_MSG(NCP_MSG_INFO, "Task Completion %p",taskAddr);
ncp_r32(taskAddr,30);
#endif

NCP_TASK_55xx_UPDATE_OPCQ_PRODUCER_IDX(
p_oPCQ,
producerIdx,
NULL,
0,
NULL,
myTaskHdl->poolID);

#if defined(NCP_NCA_ARM_L2_CACHE_HINTS) && defined(PROC_ARMA15)
#if 1
ncp_task_prefetch_data_for_write(
(ncp_uint32_t *)p_oPCQ->u.opcq_info.nxtCacheLoadOPCQentry);

p_oPCQ->u.opcq_info.nxtCacheLoadOPCQentry += 1;

if (p_oPCQ->u.opcq_info.nxtCacheLoadOPCQentry
== p_oPCQ->u.opcq_info.maxCacheLoadOPCQentry)
{
p_oPCQ->u.opcq_info.nxtCacheLoadOPCQentry = p_oPCQ->pPCQbase;
}
#endif
#endif

NCP_RETURN_LABEL

return(ncpStatus);
}


/*
* Queue task completion *plus* buffer deallocate request to NCA
*/

NCP_INLINE ncp_st_t
ncp_task_v2_put_completion_plus_deallocate(ncp_pvt_task_hdl_t *myTaskHdl,
ncp_task_ncaV2_recv_buf_t *taskAddr,
ncp_bool_t wait)
{
ncp_st_t ncpStatus       = NCP_ST_SUCCESS;
ncp_task_pcq_t  *p_oPCQ  = myTaskHdl->sendQueue;
ncp_ncaV2_task_oPCQ_entry_dealloc_t *pOutputQueueEntry
= (ncp_ncaV2_task_oPCQ_entry_dealloc_t *)p_oPCQ->u.opcq_info.pOPCQentry;
ncp_uint32_t    *wordsEntry =  (ncp_uint32_t    *)pOutputQueueEntry;
int producerIdx = p_oPCQ->u.opcq_info.opcqProducerIdx;

while (1)
{

/* Is Entry Available? */
if (NCP_TASK_55xx_OPCQ_FULL(p_oPCQ,
producerIdx,
myTaskHdl->poolID))
{
/* Queue is FULL */
{
#ifdef DBG_KMODE_INTS
pNcpNcaV2_TaskSwState->dbg_txQueueFull++;
#endif
NCP_TASK_CHECK_FOR_SHUTDOWN();
NCP_TASK_INC_STAT(TxQueueFull);
if (FALSE == wait)
{
ncpStatus = NCP_ST_TASK_SEND_QUEUE_FULL;
goto ncp_return;
}
else
{
NCP_TASK_BLOCK_ON_INTERRUPT(myTaskHdl,
myTaskHdl->dev,
NCP_NCA_WAIT_FOR_TX_INTR,
p_oPCQ->grpId,
p_oPCQ->ncaQueueId);
}
continue;
}
}
else
{
NCP_TASK_INC_STAT(TxQueueNotFull);
break;  /* Get out, we have room */
}
}   /* while(1) */

#ifdef NCP_DEBUG
ncp_memset(pOutputQueueEntry, 0, sizeof(ncp_task_ncaV2_oPCQ_entry_task_t));
#endif

/* debug and interrupt bits */

pOutputQueueEntry->cmdCode
= NCP_NCAV2_OPCQ_ENTRY_TASK_COMPLETION_PLUS_DEALLOC;

pOutputQueueEntry->interruptOnComplete   = 1;
pOutputQueueEntry->ptrCnt                = taskAddr->ptrCnt;
pOutputQueueEntry->poolID                = taskAddr->poolID;

/*
* WORKAROUND FOR HW BUG - Remove when fixed in production silicon!
*/
#ifdef NCP_TASK_BUFFSZ_BITS_REQ_FOR_SHARED_POOL_BUG
if (NCP_TASK_IS_SHARED_POOL(myTaskHdl->poolID))
{
unsigned sizeBits;

switch(taskAddr->ptrCnt)
{
case 6:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)taskAddr->pduSegAddr5,
myTaskHdl->poolID,
&sizeBits));
taskAddr->pduBlockSz5 = sizeBits;
case 5:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)taskAddr->pduSegAddr4,
myTaskHdl->poolID,
&sizeBits));
taskAddr->pduBlockSz4 = sizeBits;
case 4:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)taskAddr->pduSegAddr3,
myTaskHdl->poolID,
&sizeBits));
taskAddr->pduBlockSz3 = sizeBits;
case 3:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)taskAddr->pduSegAddr2,
myTaskHdl->poolID,
&sizeBits));
taskAddr->pduBlockSz2 = sizeBits;
case 2:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)taskAddr->pduSegAddr1,
myTaskHdl->poolID,
&sizeBits));
taskAddr->pduBlockSz1 = sizeBits;
case 1:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)taskAddr->pduSegAddr0,
myTaskHdl->poolID,
&sizeBits));
taskAddr->pduBlockSz0 = sizeBits;
default:
break;
}
}
#endif/* NCP_TASK_BUFFSZ_BITS_REQ_FOR_SHARED_POOL_BUG */

/* byte swap entry */
wordsEntry[0] = SWAP_32(wordsEntry[0]);
wordsEntry[1] = SWAP_32(wordsEntry[1]);
pOutputQueueEntry->taskAddr = SWAP_64(((ncp_raw_addr_t)taskAddr));

NCP_TASK_55xx_UPDATE_OPCQ_PRODUCER_IDX(
p_oPCQ,
producerIdx,
NULL,
0,
NULL,
myTaskHdl->poolID);

#if defined(NCP_NCA_ARM_L2_CACHE_HINTS) && defined(PROC_ARMA15)
#if 1
ncp_task_prefetch_data_for_write(
(ncp_uint32_t *)p_oPCQ->u.opcq_info.nxtCacheLoadOPCQentry);

p_oPCQ->u.opcq_info.nxtCacheLoadOPCQentry += 1;

if (p_oPCQ->u.opcq_info.nxtCacheLoadOPCQentry
== p_oPCQ->u.opcq_info.maxCacheLoadOPCQentry)
{
p_oPCQ->u.opcq_info.nxtCacheLoadOPCQentry = p_oPCQ->pPCQbase;
}
#endif
#endif

NCP_RETURN_LABEL

return(ncpStatus);
}

/*
* Queue buffer deallocate request to NCA
*/

NCP_INLINE ncp_st_t
ncp_task_v2_put_task_deallocate(    ncp_pvt_task_hdl_t *myTaskHdl,
ncp_task_ncaV2_recv_buf_t *taskAddr,
ncp_bool_t wait)
{
ncp_st_t ncpStatus       = NCP_ST_SUCCESS;
ncp_task_pcq_t  *p_oPCQ  = myTaskHdl->sendQueue;
ncp_ncaV2_task_oPCQ_entry_dealloc_t *pOutputQueueEntry
= (ncp_ncaV2_task_oPCQ_entry_dealloc_t *)p_oPCQ->u.opcq_info.pOPCQentry;
ncp_uint32_t    *wordsEntry =  (ncp_uint32_t    *)pOutputQueueEntry;
int producerIdx = p_oPCQ->u.opcq_info.opcqProducerIdx;

while (1)
{

/* Is Entry Available? */
if (NCP_TASK_55xx_OPCQ_FULL(p_oPCQ,
producerIdx,
myTaskHdl->poolID))
{
/* Queue is FULL */
{
#ifdef DBG_KMODE_INTS
pNcpNcaV2_TaskSwState->dbg_txQueueFull++;
#endif
NCP_TASK_CHECK_FOR_SHUTDOWN();
NCP_TASK_INC_STAT(TxQueueFull);
if (FALSE == wait)
{
ncpStatus = NCP_ST_TASK_SEND_QUEUE_FULL;
goto ncp_return;
}
else
{
NCP_TASK_BLOCK_ON_INTERRUPT(myTaskHdl,
myTaskHdl->dev,
NCP_NCA_WAIT_FOR_TX_INTR,
p_oPCQ->grpId,
p_oPCQ->ncaQueueId);
}
continue;
}
}
else
{
NCP_TASK_INC_STAT(TxQueueNotFull);
break; /* Get out, we have room */
}
}   /* while(1) */


#ifdef NCP_DEBUG
ncp_memset(pOutputQueueEntry, 0, sizeof(ncp_task_ncaV2_oPCQ_entry_task_t));
#endif

/* debug and interrupt bits */

pOutputQueueEntry->cmdCode
= NCP_NCAV2_OPCQ_ENTRY_TASK_DEALLOC;

pOutputQueueEntry->interruptOnComplete   = 1;
pOutputQueueEntry->ptrCnt                = taskAddr->ptrCnt;
pOutputQueueEntry->poolID                = taskAddr->poolID;

/*
* WORKAROUND FOR HW BUG - Remove when fixed in production silicon!
*/
#ifdef NCP_TASK_BUFFSZ_BITS_REQ_FOR_SHARED_POOL_BUG
if (NCP_TASK_IS_SHARED_POOL(myTaskHdl->poolID))
{
unsigned sizeBits;

switch(taskAddr->ptrCnt)
{
case 6:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)taskAddr->pduSegAddr5,
myTaskHdl->poolID,
&sizeBits));
taskAddr->pduBlockSz5 = sizeBits;
case 5:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)taskAddr->pduSegAddr4,
myTaskHdl->poolID,
&sizeBits));
taskAddr->pduBlockSz4 = sizeBits;
case 4:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)taskAddr->pduSegAddr3,
myTaskHdl->poolID,
&sizeBits));
taskAddr->pduBlockSz3 = sizeBits;
case 3:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)taskAddr->pduSegAddr2,
myTaskHdl->poolID,
&sizeBits));
taskAddr->pduBlockSz2 = sizeBits;
case 2:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)taskAddr->pduSegAddr1,
myTaskHdl->poolID,
&sizeBits));
taskAddr->pduBlockSz1 = sizeBits;
case 1:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)taskAddr->pduSegAddr0,
myTaskHdl->poolID,
&sizeBits));
taskAddr->pduBlockSz0 = sizeBits;
default:
break;
}
}
#endif/* NCP_TASK_BUFFSZ_BITS_REQ_FOR_SHARED_POOL_BUG */

/* byte swap entry */
wordsEntry[0] = SWAP_32(wordsEntry[0]);
wordsEntry[1] = SWAP_32(wordsEntry[1]);
pOutputQueueEntry->taskAddr = SWAP_64(((ncp_raw_addr_t)taskAddr));

NCP_TASK_55xx_UPDATE_OPCQ_PRODUCER_IDX(
p_oPCQ,
producerIdx,
NULL,
0,
NULL,
myTaskHdl->poolID);

#if defined(NCP_NCA_ARM_L2_CACHE_HINTS) && defined(PROC_ARMA15)
#if 1
ncp_task_prefetch_data_for_write(
(ncp_uint32_t *)p_oPCQ->u.opcq_info.nxtCacheLoadOPCQentry);

p_oPCQ->u.opcq_info.nxtCacheLoadOPCQentry += 1;

if (p_oPCQ->u.opcq_info.nxtCacheLoadOPCQentry
== p_oPCQ->u.opcq_info.maxCacheLoadOPCQentry)
{
p_oPCQ->u.opcq_info.nxtCacheLoadOPCQentry = p_oPCQ->pPCQbase;
}
#endif
#endif

NCP_RETURN_LABEL

return(ncpStatus);
}

/*
* Queue buffer deallocate-immediate request to NCA
*/

/*
* FIXME - Allow dealloc of +1 buffers with single call
*/
NCP_INLINE ncp_st_t
ncp_task_v2_put_deallocate_immediate(ncp_pvt_task_hdl_t *myTaskHdl,
ncp_ncaV2_task_oPCQ_entry_dealloc_immediate_t
*pDeallocImmediate,
ncp_bool_t wait)
{
ncp_st_t ncpStatus       = NCP_ST_SUCCESS;
ncp_task_pcq_t  *p_oPCQ  = myTaskHdl->sendQueue;
ncp_ncaV2_task_oPCQ_entry_dealloc_immediate_t *pOutputQueueEntry
= (ncp_ncaV2_task_oPCQ_entry_dealloc_immediate_t *)
p_oPCQ->u.opcq_info.pOPCQentry;
ncp_uint32_t *wordsEntry
= (ncp_uint32_t *)pOutputQueueEntry;
ncp_uint32_t *wordsDeallocImmediate
= (ncp_uint32_t *)pDeallocImmediate;
int producerIdx = p_oPCQ->u.opcq_info.opcqProducerIdx;

while (1)
{

/* Is Entry Available? */
if (NCP_TASK_55xx_OPCQ_FULL(p_oPCQ,
producerIdx,
myTaskHdl->poolID))
{

/* Queue is FULL */
{
#ifdef DBG_KMODE_INTS
pNcpNcaV2_TaskSwState->dbg_txQueueFull++;
#endif
NCP_TASK_CHECK_FOR_SHUTDOWN();
NCP_TASK_INC_STAT(TxQueueFull);
if (FALSE == wait)
{
ncpStatus = NCP_ST_TASK_SEND_QUEUE_FULL;
goto ncp_return;
}
else
{
NCP_TASK_BLOCK_ON_INTERRUPT(myTaskHdl,
myTaskHdl->dev,
NCP_NCA_WAIT_FOR_TX_INTR,
p_oPCQ->grpId,
p_oPCQ->ncaQueueId);
}
continue;
}
}
else
{
NCP_TASK_INC_STAT(TxQueueNotFull);
break; /* Get out, we have room */
}
}   /* while(1) */

/* debug and interrupt bits */

#ifdef NCP_DEBUG
ncp_memset(pOutputQueueEntry, 0, sizeof(ncp_task_ncaV2_oPCQ_entry_task_t));
#endif

/* === word 0 === */
pOutputQueueEntry->cmdCode
= NCP_NCAV2_OPCQ_ENTRY_TASK_DEALLOC_IMMEDIATE;
pOutputQueueEntry->interruptOnComplete   = 1;
wordsEntry[0] = SWAP_32(wordsEntry[0]);

/* === word 1 === */


/*
* WORKAROUND FOR HW BUG - Remove when fixed in production silicon!
*/
#ifdef NCP_TASK_BUFFSZ_BITS_REQ_FOR_SHARED_POOL_BUG
if (NCP_TASK_IS_SHARED_POOL(myTaskHdl->poolID))
{
unsigned sizeBits;

switch(pDeallocImmediate->ptrCnt)
{
case 6:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)
pDeallocImmediate->pduSegAddr5,
myTaskHdl->poolID,
&sizeBits));
pDeallocImmediate->pduBlockSz5 = sizeBits;
case 5:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)
pDeallocImmediate->pduSegAddr4,
myTaskHdl->poolID,
&sizeBits));
pDeallocImmediate->pduBlockSz4 = sizeBits;
case 4:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)
pDeallocImmediate->pduSegAddr3,
myTaskHdl->poolID,
&sizeBits));
pDeallocImmediate->pduBlockSz3 = sizeBits;
case 3:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)
pDeallocImmediate->pduSegAddr2,
myTaskHdl->poolID,
&sizeBits));
pDeallocImmediate->pduBlockSz2 = sizeBits;
case 2:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)
pDeallocImmediate->pduSegAddr1,
myTaskHdl->poolID,
&sizeBits));
pDeallocImmediate->pduBlockSz1 = sizeBits;
case 1:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)
pDeallocImmediate->pduSegAddr0,
myTaskHdl->poolID,
&sizeBits));
pDeallocImmediate->pduBlockSz0 = sizeBits;
default:
break;
}
}
#endif/* NCP_TASK_BUFFSZ_BITS_REQ_FOR_SHARED_POOL_BUG */

/* ptrCnt set by app,   buffsz bits set above,  if required          */
pDeallocImmediate->poolID = myTaskHdl->poolID; /* unavailable in app */
wordsEntry[1] = SWAP_32(wordsDeallocImmediate[1]);

/* === words 2..3 === */
#ifdef NCP_TASK_DBG_55XX_TASK_FLOW
NCP_MSG(NCP_MSG_INFO,
" Dealloc Immediate: VP=%p",
pDeallocImmediate->pduSegAddr0);
#endif

switch(pDeallocImmediate->ptrCnt)
{
case 6:
pOutputQueueEntry->pduSegAddr5
= SWAP_64(pDeallocImmediate->pduSegAddr5);
case 5:
pOutputQueueEntry->pduSegAddr4
= SWAP_64(pDeallocImmediate->pduSegAddr4);
case 4:
pOutputQueueEntry->pduSegAddr3
= SWAP_64(pDeallocImmediate->pduSegAddr3);
case 3:
pOutputQueueEntry->pduSegAddr2
= SWAP_64(pDeallocImmediate->pduSegAddr2);
case 2:
pOutputQueueEntry->pduSegAddr1
= SWAP_64(pDeallocImmediate->pduSegAddr1);
case 1:
pOutputQueueEntry->pduSegAddr0
= SWAP_64(pDeallocImmediate->pduSegAddr0);
break;
case 0:
default:
NCP_CALL(NCP_ST_INTERNAL_ERROR);
}

#ifdef NCP_TASK_DBG_55XX_TASK_FLOW
/* FIXME: Log all pdu seg addrs */
NCP_MSG(NCP_MSG_INFO,
" VI=0x%llx\r\n",
pOutputQueueEntry->pduSegAddr0);
#endif


NCP_TASK_55xx_UPDATE_OPCQ_PRODUCER_IDX(
p_oPCQ,
producerIdx,
NULL,
0,
NULL,
myTaskHdl->poolID);

#if defined(NCP_NCA_ARM_L2_CACHE_HINTS) && defined(PROC_ARMA15)
#if 1
ncp_task_prefetch_data_for_write(
(ncp_uint32_t *)p_oPCQ->u.opcq_info.nxtCacheLoadOPCQentry);

p_oPCQ->u.opcq_info.nxtCacheLoadOPCQentry += 1;

if (p_oPCQ->u.opcq_info.nxtCacheLoadOPCQentry
== p_oPCQ->u.opcq_info.maxCacheLoadOPCQentry)
{
p_oPCQ->u.opcq_info.nxtCacheLoadOPCQentry = p_oPCQ->pPCQbase;
}
#endif
#endif

NCP_RETURN_LABEL

return(ncpStatus);
}

/* NOTE - takes 34xx style meta data */
/* FIXME - optimization - combine swap with stores where practical */
NCP_INLINE ncp_st_t
ncp_task_v2_nca_legacy_put_segments_tOutput(
ncp_pvt_task_hdl_t              *myTaskHdl,
	                    ncp_vp_hdl_t                    vpHdl,
ncp_task_send_meta_t            *pTaskMetaData,
ncp_task_ncaV2_oPCQ_aux_data_t   *pTaskAuxData,
ncp_task_segment_entry_t        *pSegTable,
int                             numSegs,
ncp_bool_t                      wait)
{
ncp_st_t ncpStatus       = NCP_ST_SUCCESS;
ncp_task_pcq_t  *p_oPCQ  = myTaskHdl->sendQueue;
ncp_task_ncaV2_oPCQ_entry_task_t *pOutputQueueEntry
= (ncp_task_ncaV2_oPCQ_entry_task_t *)p_oPCQ->u.opcq_info.pOPCQentry;
ncp_uint32_t *wordsEntry = (ncp_uint32_t *) pOutputQueueEntry;
ncp_uint8_t vpId;
ncp_task_ncaV2_oPCQ_entry_task_extension_t *pOutputQueueEntryExt=NULL; /* Make compiler happy */
ncp_uint32_t *wordsExt=NULL; /* Make compiler happy */
int savCmdCode;
int producerIdx = p_oPCQ->u.opcq_info.opcqProducerIdx;

/*
* requests with more than 2 pdu segments will require 2 oPCQ entries.
* So,  go ahead and make sure we have room to store 2,  and setup
* extension pointer.
*/

if (numSegs > 2)
{
producerIdx++;
if (producerIdx == p_oPCQ->nEntries)
{
producerIdx = 0;
p_oPCQ->u.opcq_info.pOPCQentry = p_oPCQ->pPCQbase;
}
else
{
p_oPCQ->u.opcq_info.pOPCQentry++;
}
pOutputQueueEntryExt
= (ncp_task_ncaV2_oPCQ_entry_task_extension_t *)p_oPCQ->u.opcq_info.pOPCQentry;
wordsExt = (ncp_uint32_t *)pOutputQueueEntryExt;
}


while (1)
{

/* Is Queue Full? */
if (NCP_TASK_55xx_OPCQ_FULL(p_oPCQ,
producerIdx,
myTaskHdl->poolID))
{

/* Queue is FULL */
{
#ifdef DBG_KMODE_INTS
pNcpNcaV2_TaskSwState->dbg_txQueueFull++;
#endif
NCP_TASK_CHECK_FOR_SHUTDOWN();
NCP_TASK_INC_STAT(TxQueueFull);
if (FALSE == wait)
{
ncpStatus = NCP_ST_TASK_SEND_QUEUE_FULL;
goto ncp_return;
}
else
{
NCP_TASK_BLOCK_ON_INTERRUPT(myTaskHdl,
myTaskHdl->dev,
NCP_NCA_WAIT_FOR_TX_INTR,
p_oPCQ->grpId,
p_oPCQ->ncaQueueId);
}
continue;
}
}
else
{
NCP_TASK_INC_STAT(TxQueueNotFull);
break; /* Get out, we have room */
}
}   /* while(1) */

/* debug and interrupt bits */

#ifdef NCP_TASK_DBG_55XX_TASK_FLOW
NCP_MSG(NCP_MSG_INFO,
"Leagcay Send Segments: numSegs=%d: ",
numSegs);
{
int zz;
for (zz=0; zz<numSegs; zz++)
{
NCP_MSG(NCP_MSG_INFO,
"addr%d=%p, sz%d=%d ",
zz, pSegTable[zz].addr, zz,pSegTable[zz].size);
}
}
#endif

/*
* Now populate the oPCQ entry directly from the
* client task meta data
*/

#ifdef NCP_DEBUG
ncp_memset(pOutputQueueEntry, 0, sizeof(ncp_task_ncaV2_oPCQ_entry_task_t));
#endif

/* === Word 0 === */

if (numSegs <= 2)
{
savCmdCode = pOutputQueueEntry->cmdCode = NCP_NCAV2_OPCQ_ENTRY_OTASK_LE_2_PTRS;
}
else
{
savCmdCode = pOutputQueueEntry->cmdCode = NCP_NCAV2_OPCQ_ENTRY_OTASK_GT_2_PTRS;

#ifdef NCP_DEBUG
ncp_memset(pOutputQueueEntryExt, 0, sizeof(ncp_task_ncaV2_oPCQ_entry_task_extension_t));
#endif

}

pOutputQueueEntry->flowDataIndex
= pTaskMetaData->flowId;
pOutputQueueEntry->setTaskErr = 0;
pOutputQueueEntry->debugFieldV
= pTaskMetaData->debugFieldV;
pOutputQueueEntry->packetCtrl_forceCopy
= (NCP_TASK_FORCE_OTASK_COPY && (numSegs > 1));
pOutputQueueEntry->packetCtrl_returnBuffToMMEafterCopy
= ((NCP_TASK_IS_SHARED_POOL(myTaskHdl->poolID))
? 1 : 0);
pOutputQueueEntry->interruptOnComplete = 1;

/* === Word 1 === */


pOutputQueueEntry->debugData = pTaskMetaData->debugData;
NCP_CALL(ncp_vp_id_get(vpHdl, &vpId));
pOutputQueueEntry->virtualFlowID = vpId;


/* === Words 2..9 === */
ncp_vpm_task_param_encode(vpHdl,
&pOutputQueueEntry->params[0],
&pTaskMetaData->taskParms[0]);

/* === Word 10 === */

/*
* WORKAROUND FOR HW BUG - Remove when fixed in production silicon!
*/
#ifdef NCP_TASK_BUFFSZ_BITS_REQ_FOR_SHARED_POOL_BUG
if (NCP_TASK_IS_SHARED_POOL(myTaskHdl->poolID))
{
unsigned sizeBits;

switch(numSegs)
{
case 6:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)pSegTable[5].addr,
myTaskHdl->poolID,
&sizeBits));
pOutputQueueEntry->pduBlockSz5 = sizeBits;
case 5:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)pSegTable[4].addr,
myTaskHdl->poolID,
&sizeBits));
pOutputQueueEntry->pduBlockSz4 = sizeBits;
case 4:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)pSegTable[3].addr,
myTaskHdl->poolID,
&sizeBits));
pOutputQueueEntry->pduBlockSz3 = sizeBits;
case 3:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)pSegTable[2].addr,
myTaskHdl->poolID,
&sizeBits));
pOutputQueueEntry->pduBlockSz2 = sizeBits;
case 2:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)pSegTable[1].addr,
myTaskHdl->poolID,
&sizeBits));
pOutputQueueEntry->pduBlockSz1 = sizeBits;
case 1:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)pSegTable[0].addr,
myTaskHdl->poolID,
&sizeBits));
pOutputQueueEntry->pduBlockSz0 = sizeBits;
default:
break;
}
}
#else

/*
* pduBlockSz0..5 = 0 (not needed since not returning ptrs to mme)
*/

#endif/* NCP_TASK_BUFFSZ_BITS_REQ_FOR_SHARED_POOL_BUG */

pOutputQueueEntry->priority = pTaskMetaData->priority;
pOutputQueueEntry->ptrCnt = numSegs;
pOutputQueueEntry->poolID = myTaskHdl->poolID;

/* === Words 11 and beyond, including extension === */

switch(numSegs)
{
case 6:
pOutputQueueEntryExt->pduSegSize5 = pSegTable[5].size;
pOutputQueueEntryExt->pduSegAddr5 = SWAP_64(((ncp_raw_addr_t)pSegTable[5].addr));
case 5:
pOutputQueueEntryExt->pduSegSize4 = pSegTable[4].size;
pOutputQueueEntryExt->pduSegAddr4 = SWAP_64(((ncp_raw_addr_t)pSegTable[4].addr));
/* segSz4..5 */
wordsExt[3] = SWAP_32(wordsExt[3]);
case 4:
pOutputQueueEntryExt->pduSegSize3 = pSegTable[3].size;
pOutputQueueEntryExt->pduSegAddr3 = SWAP_64(((ncp_raw_addr_t)pSegTable[3].addr));
case 3:
pOutputQueueEntryExt->pduSegSize2 = pSegTable[2].size;
pOutputQueueEntryExt->pduSegAddr2 = SWAP_64(((ncp_raw_addr_t)pSegTable[2].addr));

/*
* We know this was a multi-entry request,  since ptrCnt > 2
*/

/* cmdCode */
pOutputQueueEntryExt->cmdCode = NCP_NCAV2_OPCQ_ENTRY_OTASK_EXTENSION;
wordsExt[0] = SWAP_32(wordsExt[0]);
/* SegSz2..3 */
wordsExt[2] = SWAP_32(wordsExt[2]);

case 2:
pOutputQueueEntry->pduSegSize1 = pSegTable[1].size;
pOutputQueueEntry->pduSegAddr1 = SWAP_64(((ncp_raw_addr_t)pSegTable[1].addr));
case 1:
pOutputQueueEntry->pduSegSize0 = pSegTable[0].size;
pOutputQueueEntry->pduSegAddr0 = SWAP_64(((ncp_raw_addr_t)pSegTable[0].addr));
break;

default:
NCP_CALL(NCP_ST_INVALID_VALUE);
} /* switch */

/*
* perform byte swaping on entries, except params
*/
wordsEntry[0] = SWAP_32(wordsEntry[0]);
wordsEntry[1] = SWAP_32(wordsEntry[1]);
wordsEntry[10] = SWAP_32(wordsEntry[10]);
wordsEntry[11] = SWAP_32(wordsEntry[11]);

/*
* Note:   If this were a muti-entry request,   then the producer index was already incremented once
* earlier in this function.  It will now be incremented again to reflect that both queue entries have been
* posted to the NCA.
*/
NCP_TASK_55xx_UPDATE_OPCQ_PRODUCER_IDX(
p_oPCQ,
producerIdx,
pOutputQueueEntry,
savCmdCode,
pTaskAuxData,
myTaskHdl->poolID);

#if defined(NCP_NCA_ARM_L2_CACHE_HINTS) && defined(PROC_ARMA15)
#if 1
ncp_task_prefetch_data_for_write(
(ncp_uint32_t *)p_oPCQ->u.opcq_info.nxtCacheLoadOPCQentry);

p_oPCQ->u.opcq_info.nxtCacheLoadOPCQentry += 1;

if (p_oPCQ->u.opcq_info.nxtCacheLoadOPCQentry
== p_oPCQ->u.opcq_info.maxCacheLoadOPCQentry)
{
p_oPCQ->u.opcq_info.nxtCacheLoadOPCQentry = p_oPCQ->pPCQbase;
}
#endif
#endif



NCP_RETURN_LABEL

return(ncpStatus);

}



/* NOTE - takes 34xx style meta data */
/* FIXME - optimization - combine swap with stores where practical */
NCP_INLINE ncp_st_t
ncp_task_v2_legacy_put_tOutput(ncp_pvt_task_hdl_t *myTaskHdl,
	ncp_vp_hdl_t vpHdl,
ncp_task_send_meta_t          *pTaskMetaData,
void                          *taskPduData,
ncp_task_ncaV2_oPCQ_aux_data_t *pTaskAuxData,
ncp_bool_t wait)
{
ncp_st_t ncpStatus       = NCP_ST_SUCCESS;
ncp_task_pcq_t  *p_oPCQ  = myTaskHdl->sendQueue;
ncp_task_ncaV2_oPCQ_entry_task_t *pOutputQueueEntry
= (ncp_task_ncaV2_oPCQ_entry_task_t *)p_oPCQ->u.opcq_info.pOPCQentry;
ncp_uint32_t *wordsEntry = (ncp_uint32_t *) pOutputQueueEntry;
ncp_uint8_t vpId;
int producerIdx = p_oPCQ->u.opcq_info.opcqProducerIdx;

while (1)
{
/* Is Queue Full? */
if (NCP_TASK_55xx_OPCQ_FULL(p_oPCQ,
producerIdx,
myTaskHdl->poolID))
{

/* Queue is FULL */
{
#ifdef DBG_KMODE_INTS
pNcpNcaV2_TaskSwState->dbg_txQueueFull++;
#endif
NCP_TASK_CHECK_FOR_SHUTDOWN();
NCP_TASK_INC_STAT(TxQueueFull);
if (FALSE == wait)
{
ncpStatus = NCP_ST_TASK_SEND_QUEUE_FULL;
goto ncp_return;
}
else
{
NCP_TASK_BLOCK_ON_INTERRUPT(myTaskHdl,
myTaskHdl->dev,
NCP_NCA_WAIT_FOR_TX_INTR,
p_oPCQ->grpId,
p_oPCQ->ncaQueueId);
}
continue;
}
}
else
{
NCP_TASK_INC_STAT(TxQueueNotFull);
break; /* Get out, we have room */
}
}   /* while(1) */

/* debug and interrupt bits */

#ifdef NCP_TASK_DBG_55XX_TASK_FLOW
NCP_MSG(NCP_MSG_INFO,
"Leagcay Send Task VA=%p",
taskPduData);
#endif

/*
* Now populate the oPCQ entry directly from the
* client task meta data
*/

#ifdef NCP_DEBUG
ncp_memset(pOutputQueueEntry, 0, sizeof(ncp_task_ncaV2_oPCQ_entry_task_t));
#endif

/* === Word 0 === */

pOutputQueueEntry->cmdCode
= NCP_NCAV2_OPCQ_ENTRY_OTASK_LE_2_PTRS;
pOutputQueueEntry->flowDataIndex
= pTaskMetaData->flowId;
pOutputQueueEntry->setTaskErr = 0;
pOutputQueueEntry->debugFieldV
= pTaskMetaData->debugFieldV;
/*
* No neede to force copy here since we have at most 1 pduSegment
*/
pOutputQueueEntry->packetCtrl_forceCopy = 0;/* NCP_TASK_FORCE_OTASK_COPY */
pOutputQueueEntry->packetCtrl_returnBuffToMMEafterCopy
= ((NCP_TASK_IS_SHARED_POOL(myTaskHdl->poolID))
? 1 : 0);
pOutputQueueEntry->interruptOnComplete = 1;

/* === Word 1 === */


pOutputQueueEntry->debugData = pTaskMetaData->debugData;
NCP_CALL(ncp_vp_id_get(vpHdl, &vpId));
pOutputQueueEntry->virtualFlowID = vpId;


/* === Words 2..9 === */
ncp_vpm_task_param_encode(vpHdl,
&pOutputQueueEntry->params[0],
&pTaskMetaData->taskParms[0]);

/* === Word 10 === */

pOutputQueueEntry->priority
= pTaskMetaData->priority;
pOutputQueueEntry->poolID = myTaskHdl->poolID;
if (0 !=
(pOutputQueueEntry->pduSegSize0 = pTaskMetaData->dataSize))
{
pOutputQueueEntry->ptrCnt             = 1;

/*
* WORKAROUND FOR HW BUG - Remove when fixed in production silicon!
*/
#ifdef NCP_TASK_BUFFSZ_BITS_REQ_FOR_SHARED_POOL_BUG
if (NCP_TASK_IS_SHARED_POOL(myTaskHdl->poolID))
{
unsigned sizeBits;
{
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)taskPduData,
myTaskHdl->poolID,
&sizeBits));
pOutputQueueEntry->pduBlockSz0 = sizeBits;
}
}
#endif/* NCP_TASK_BUFFSZ_BITS_REQ_FOR_SHARED_POOL_BUG */


}
else
{
pOutputQueueEntry->ptrCnt             = 0;
}

/* === Word 11 === */
/* seg0 done above in word 10 section */

/* === Word 12..13 === */
if (pTaskMetaData->dataSize)
{
#ifdef NCP_TASK_DBG_55XX_TASK_FLOW
NCP_MSG(NCP_MSG_INFO,
" VI=0x%llx\r\n",
pOutputQueueEntry->pduSegAddr0);
#endif
}

/* === Word 14..15 === */


/* perform byte swaping on entries, except params */
wordsEntry[0] = SWAP_32(wordsEntry[0]);
wordsEntry[1] = SWAP_32(wordsEntry[1]);
wordsEntry[10] = SWAP_32(wordsEntry[10]);
wordsEntry[11] = SWAP_32(wordsEntry[11]);
pOutputQueueEntry->pduSegAddr0
= SWAP_64(((ncp_raw_addr_t)taskPduData));

NCP_TASK_55xx_UPDATE_OPCQ_PRODUCER_IDX(
p_oPCQ,
producerIdx,
pOutputQueueEntry,
NCP_NCAV2_OPCQ_ENTRY_OTASK_LE_2_PTRS,
pTaskAuxData,
myTaskHdl->poolID);

#if defined(NCP_NCA_ARM_L2_CACHE_HINTS) && defined(PROC_ARMA15)
#if 1
ncp_task_prefetch_data_for_write(
(ncp_uint32_t *)p_oPCQ->u.opcq_info.nxtCacheLoadOPCQentry);

p_oPCQ->u.opcq_info.nxtCacheLoadOPCQentry += 1;

if (p_oPCQ->u.opcq_info.nxtCacheLoadOPCQentry
== p_oPCQ->u.opcq_info.maxCacheLoadOPCQentry)
{
p_oPCQ->u.opcq_info.nxtCacheLoadOPCQentry = p_oPCQ->pPCQbase;
}
#endif
#endif

NCP_RETURN_LABEL

return(ncpStatus);
}



NCP_INLINE ncp_st_t
ncp_task_v2_put_tOutput(ncp_pvt_task_hdl_t *myTaskHdl,
	ncp_vp_hdl_t vpHdl,
ncp_task_ncaV2_send_meta_t     *pTaskMetaData,
ncp_task_ncaV2_oPCQ_aux_data_t *pTaskAuxData,
ncp_bool_t wait)
{
ncp_st_t ncpStatus       = NCP_ST_SUCCESS;
ncp_task_pcq_t  *p_oPCQ  = myTaskHdl->sendQueue;
ncp_task_ncaV2_oPCQ_entry_task_t *pOutputQueueEntry
= (ncp_task_ncaV2_oPCQ_entry_task_t *)p_oPCQ->u.opcq_info.pOPCQentry;
ncp_uint32_t *wordsEntry = (ncp_uint32_t *) pOutputQueueEntry;
ncp_uint32_t *wordsMetaData = (ncp_uint32_t *) pTaskMetaData;
ncp_task_ncaV2_oPCQ_entry_task_extension_t *pOutputQueueEntryExt;
ncp_uint32_t *wordsExt;
int savCmdCode;
int producerIdx = p_oPCQ->u.opcq_info.opcqProducerIdx;
#if 0 /* UBOOT */
ncp_uint8_t vpId;
#endif

debug("ncp_task_v2_put_tOutput(): pOutputQueueEntry=0x%p, producerIdx=%d\n",
pOutputQueueEntry, producerIdx);

/*
* requests with more than 2 pdu segments will require 2 oPCQ entries.
* So,  go ahead and make sure we have room to store 2,  and setup
* extension pointer.
*/

if (pTaskMetaData->ptrCnt > 2)
{
producerIdx++;
if (producerIdx == p_oPCQ->nEntries)
{
producerIdx = 0;
p_oPCQ->u.opcq_info.pOPCQentry = p_oPCQ->pPCQbase;
}
else
{
p_oPCQ->u.opcq_info.pOPCQentry++;
}
pOutputQueueEntryExt
= (ncp_task_ncaV2_oPCQ_entry_task_extension_t *)p_oPCQ->u.opcq_info.pOPCQentry;
wordsExt = (ncp_uint32_t *)pOutputQueueEntryExt;
savCmdCode = pTaskMetaData->cmdCode = NCP_NCAV2_OPCQ_ENTRY_OTASK_GT_2_PTRS;
pTaskMetaData->cmdCodeExt = NCP_NCAV2_OPCQ_ENTRY_OTASK_EXTENSION;
}
else
{
pOutputQueueEntryExt=NULL; /* Make compiler happy */
wordsExt=NULL; /* Make compiler happy */
savCmdCode = pTaskMetaData->cmdCode = NCP_NCAV2_OPCQ_ENTRY_OTASK_LE_2_PTRS;
}

/*
* WORKAROUND FOR HW BUG - Remove when fixed in production silicon!
*/
#ifdef NCP_TASK_BUFFSZ_BITS_REQ_FOR_SHARED_POOL_BUG
debug("ncp_task_v2_put_tOutput(): before NCP_TASK_IS_SHARED_POOL\n");
if (NCP_TASK_IS_SHARED_POOL(myTaskHdl->poolID))
{
unsigned sizeBits;

switch(pTaskMetaData->ptrCnt)
{
case 6:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)pTaskMetaData->pduSegAddr5,
myTaskHdl->poolID,
&sizeBits));
pTaskMetaData->pduBlockSz5 = sizeBits;
case 5:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)pTaskMetaData->pduSegAddr4,
myTaskHdl->poolID,
&sizeBits));
pTaskMetaData->pduBlockSz4 = sizeBits;
case 4:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)pTaskMetaData->pduSegAddr3,
myTaskHdl->poolID,
&sizeBits));
pTaskMetaData->pduBlockSz3 = sizeBits;
case 3:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)pTaskMetaData->pduSegAddr2,
myTaskHdl->poolID,
&sizeBits));
pTaskMetaData->pduBlockSz2 = sizeBits;
case 2:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)pTaskMetaData->pduSegAddr1,
myTaskHdl->poolID,
&sizeBits));
pTaskMetaData->pduBlockSz1 = sizeBits;
case 1:
NCP_CALL(ncp_task_v2_MMEpool_buffSzBits(
(void *)(ncp_raw_addr_t)pTaskMetaData->pduSegAddr0,
myTaskHdl->poolID,
&sizeBits));
pTaskMetaData->pduBlockSz0 = sizeBits;
default:
break;
}
}
#endif/* NCP_TASK_BUFFSZ_BITS_REQ_FOR_SHARED_POOL_BUG */

while (1)
{
/* Is Queue Full? */
if (NCP_TASK_55xx_OPCQ_FULL(p_oPCQ,
producerIdx,
myTaskHdl->poolID))
{

/* Queue is FULL */
{
#ifdef DBG_KMODE_INTS
pNcpNcaV2_TaskSwState->dbg_txQueueFull++;
#endif
NCP_TASK_CHECK_FOR_SHUTDOWN();
NCP_TASK_INC_STAT(TxQueueFull);
if (FALSE == wait)
{
ncpStatus = NCP_ST_TASK_SEND_QUEUE_FULL;
goto ncp_return;
}
else
{
NCP_TASK_BLOCK_ON_INTERRUPT(myTaskHdl,
myTaskHdl->dev,
NCP_NCA_WAIT_FOR_TX_INTR,
p_oPCQ->grpId,
p_oPCQ->ncaQueueId);
}
continue;
}
}
else
{
debug("ncp_task_v2_put_tOutput(): got opcq\n");
NCP_TASK_INC_STAT(TxQueueNotFull);
break; /* Get out, we have room */
}
}   /* while(1) */

#if (NCP_TASK_NCAV2_SHPOOL_PTR_DEBUG) || defined(NCP_TASK_DBG_55XX_TASK_FLOW)
NCP_MSG(NCP_MSG_INFO,
"Native NcaV2 Send: numPduSegs=%d: ",
pTaskMetaData->ptrCnt);
switch(pTaskMetaData->ptrCnt)
{
case 6:
NCP_MSG(NCP_MSG_INFO,
"addr5=%p, sz=%d ",
((void *)(ncp_raw_addr_t)pTaskMetaData->pduSegAddr5),
(int)pTaskMetaData->pduSegSize5);
case 5:
NCP_MSG(NCP_MSG_INFO,
"addr4=%p, sz=%d \r\n",
((void *)(ncp_raw_addr_t)pTaskMetaData->pduSegAddr4),
(int)pTaskMetaData->pduSegSize4);
case 4:
NCP_MSG(NCP_MSG_INFO,
"addr3=%p, sz=%d ",
((void *)(ncp_raw_addr_t)pTaskMetaData->pduSegAddr3),
(int)pTaskMetaData->pduSegSize3);
case 3:
NCP_MSG(NCP_MSG_INFO,
"addr2=%p, sz=%d \r\n",
((void *)(ncp_raw_addr_t)pTaskMetaData->pduSegAddr2),
(int)pTaskMetaData->pduSegSize2);
case 2:
NCP_MSG(NCP_MSG_INFO,
"addr1=%p, sz=%d ",
((void *)(ncp_raw_addr_t)pTaskMetaData->pduSegAddr1),
(int)pTaskMetaData->pduSegSize1);
case 1:
NCP_MSG(NCP_MSG_INFO,
"addr0=%p, sz=%d \r\n",
((void *)(ncp_raw_addr_t)pTaskMetaData->pduSegAddr0),
(int)pTaskMetaData->pduSegSize0);
break;
default:
break;
}   /* switch */
#endif

#ifdef NCP_DEBUG
ncp_memset(pOutputQueueEntry, 0, sizeof(ncp_task_ncaV2_oPCQ_entry_task_t));
if (pTaskMetaData->ptrCnt > 2)
{

ncp_memset(pOutputQueueEntryExt, 0, sizeof(ncp_task_ncaV2_oPCQ_entry_task_extension_t));
}
#endif

debug("ncp_task_v2_put_tOutput(): setting up meta data\n");
/*
* Complete setting up fields in meta data that
* were not set by calling application
*/

/* Word 0 in meta data */
pTaskMetaData->setTaskErr = 0;
pTaskMetaData->packetCtrl_forceCopy
= (NCP_TASK_FORCE_OTASK_COPY && (pTaskMetaData->ptrCnt > 1));
pTaskMetaData->packetCtrl_returnBuffToMMEafterCopy
= ((NCP_TASK_IS_SHARED_POOL(myTaskHdl->poolID))
? 1 : 0);
pTaskMetaData->interruptOnComplete = 1;

#if 0 /* UBOOT */
/* Word 1 in Meta data */
NCP_CALL(ncp_vp_id_get(vpHdl, &vpId));
pTaskMetaData->virtualFlowID = vpId;
#endif/* UBOOT */

/* Word 10 */
pTaskMetaData->poolID = myTaskHdl->poolID;

/*
* Now write the oPCQ entry!
*/

/* === Word 0 === */

wordsEntry[0] = SWAP_32(wordsMetaData[0]);

/* === Word 1 === */

wordsEntry[1] = SWAP_32(wordsMetaData[1]);

/* === Words 2..9 === */
ncp_vpm_task_param_encode(vpHdl,
&pOutputQueueEntry->params[0],
&pTaskMetaData->params[0]);

/* === Word 10 === */

wordsEntry[10] = SWAP_32(wordsMetaData[10]);

/* === Words 11 and beyond, including extension === */

switch(pTaskMetaData->ptrCnt)
{
case 6:
pOutputQueueEntryExt->pduSegAddr5 = SWAP_64(pTaskMetaData->pduSegAddr5);
case 5:
pOutputQueueEntryExt->pduSegAddr4 = SWAP_64(pTaskMetaData->pduSegAddr4);
/* segSz4..5 */
wordsExt[3] = SWAP_32(wordsMetaData[19]);
case 4:
pOutputQueueEntryExt->pduSegAddr3 = SWAP_64(pTaskMetaData->pduSegAddr3);
case 3:
pOutputQueueEntryExt->pduSegAddr2 = SWAP_64(pTaskMetaData->pduSegAddr2);
/* ext command code */
wordsExt[0] = SWAP_32(wordsMetaData[16]);
/* pduSegSz 2..3 */
wordsExt[2] = SWAP_32(wordsMetaData[18]);

/* Extension is fully populated now! */

case 2:
pOutputQueueEntry->pduSegAddr1 = SWAP_64(pTaskMetaData->pduSegAddr1);
case 1:
pOutputQueueEntry->pduSegAddr0 = SWAP_64(pTaskMetaData->pduSegAddr0);
/* pduSegSz 0..1 */
wordsEntry[11] = SWAP_32(wordsMetaData[11]);
break;
default:
NCP_CALL(NCP_ST_INVALID_VALUE);
} /* switch */

/*
* Note:   If this were a muti-entry request,   then the producer index was already
* incremented once (but not written to NCA)
* earlier in this function.  It will now be incremented again to reflect that both
* queue entries have been
* posted to the NCA.
*/

debug("ncp_task_v2_put_tOutput(): before NCP_TASK_55xx_UPDATE_OPCQ_PRODUCER_IDX\n");

NCP_TASK_55xx_UPDATE_OPCQ_PRODUCER_IDX(
p_oPCQ,
producerIdx,
pOutputQueueEntry,
savCmdCode,
pTaskAuxData,
myTaskHdl->poolID);

#if defined(NCP_NCA_ARM_L2_CACHE_HINTS) && defined(PROC_ARMA15)
#if 1
ncp_task_prefetch_data_for_write(
(ncp_uint32_t *)p_oPCQ->u.opcq_info.nxtCacheLoadOPCQentry);

p_oPCQ->u.opcq_info.nxtCacheLoadOPCQentry += 1;

if (p_oPCQ->u.opcq_info.nxtCacheLoadOPCQentry
== p_oPCQ->u.opcq_info.maxCacheLoadOPCQentry)
{
p_oPCQ->u.opcq_info.nxtCacheLoadOPCQentry = p_oPCQ->pPCQbase;
}
#endif
#endif



NCP_RETURN_LABEL

return(ncpStatus);

}

#ifdef USE_CACHE_SYNC
/* align it with lower 64 byte aligned address */
#define INVALIDATE_DCACHE_RANGE_ALIGN(buf, size) \
invalidate_dcache_range(((unsigned long)buf & ~(0x3f)), (((unsigned long)buf & ~(0x3f)) + 64))
#endif

/*
* Optimized for ncaV2 with VPP managed pool
* Note - removed s/w cache line avoidance logic - we can accomplish the same thing by setting the almost full register
* TODO - delay advancing iPCQ consumer index if auto complete.   NCA completes N immediately instead of waiting
* for N+1 to be received.
*/

NCP_INLINE ncp_st_t
ncp_task_v2_check_input_queue( ncp_pvt_task_hdl_t          *myTaskHdl,
ncp_pvt_task_recv_queue_t   *myRecvQueue,
ncp_task_ncaV2_recv_buf_t         **task,
ncp_uint8_t                 *pBuffSizeBits)
{
ncp_st_t ncpStatus = NCP_ST_SUCCESS;
ncp_task_pcq_t        *p_iPCQ = myRecvQueue->taskQueue;
ncp_task_ncaV2_iPCQ_entry_t *pInputQueueEntry = p_iPCQ->u.ipcq_info.pIPCQentry;
ncp_uint64_t taskAddr64;

/* HACK: Temporary invalidate until cache coherency is figured in uboot */
#ifdef USE_CACHE_SYNC
kdfldfk
INVALIDATE_DCACHE_RANGE_ALIGN(pInputQueueEntry, sizeof(ncp_task_ncaV2_iPCQ_entry_t));
#endif
if (0LL != (ncp_uint64_t)(pInputQueueEntry->taskAddr))
{
ncp_task_ncaV2_recv_buf_t  *pHdr;
ncp_uint32_t              *wordsHdr;

debug("ncp_task_v2_check_input_queue(): saw a task!!! addr=0x%llx\n",
pInputQueueEntry->taskAddr);

/*
* prevent speculative execution of following instructions.
* if pInputQueueEntry is read speculatively it may have
* stale data!
*/
NCP_ISYNC_BARRIER();

/* byte swap input task entry */
taskAddr64 = SWAP_64(pInputQueueEntry->taskAddr);
pHdr = *task = (void *)(ncp_raw_addr_t)taskAddr64;

/*
* No need to swap words 2 and 3 of iPCQ entry.
* NCA needs LE format for Hw Auto Completion
* and we do not use them anyway
*/

#if 0 && !defined(NCP_KERNEL)
NCP_MSG(NCP_MSG_INFO, "RX Task, %p",pHdr);
ncp_r32(pHdr,30);
#endif

/* byte swap task input header */
wordsHdr = (ncp_uint32_t *)pHdr;
wordsHdr[0] = SWAP_32(wordsHdr[0]);
wordsHdr[1] = SWAP_32(wordsHdr[1]);
wordsHdr[10] = SWAP_32(wordsHdr[10]);

/*
* Task input header is variable length
*/

/*
* Fix up segment pointers
*/
switch(pHdr->ptrCnt)
{
case 6:
pHdr->pduSegAddr5 = SWAP_64(pHdr->pduSegAddr5);
#ifdef NCP_TASK_DBG_BUFFERS
ncp_task_v2_del_onNca((void *)(ncp_raw_addr_t)pHdr->pduSegAddr5, myTaskHdl->poolID);
#endif
case 5:
pHdr->pduSegAddr4 = SWAP_64(pHdr->pduSegAddr4);
/* swap pduSegSz4..5 */
wordsHdr[17] = SWAP_32(wordsHdr[17]);
#ifdef NCP_TASK_DBG_BUFFERS
ncp_task_v2_del_onNca((void *)(ncp_raw_addr_t)pHdr->pduSegAddr4, myTaskHdl->poolID);
#endif
case 4:
pHdr->pduSegAddr3 = SWAP_64(pHdr->pduSegAddr3);
#ifdef NCP_TASK_DBG_BUFFERS
ncp_task_v2_del_onNca((void *)(ncp_raw_addr_t)pHdr->pduSegAddr3, myTaskHdl->poolID);
#endif
case 3:
pHdr->pduSegAddr2 = SWAP_64(pHdr->pduSegAddr2);
/* swap pduSegSz2..3 */
wordsHdr[16] = SWAP_32(wordsHdr[16]);
#ifdef NCP_TASK_DBG_BUFFERS
ncp_task_v2_del_onNca((void *)(ncp_raw_addr_t)pHdr->pduSegAddr2, myTaskHdl->poolID);
#endif
case 2:
pHdr->pduSegAddr1 = SWAP_64(pHdr->pduSegAddr1);
#ifdef NCP_TASK_DBG_BUFFERS
ncp_task_v2_del_onNca((void *)(ncp_raw_addr_t)pHdr->pduSegAddr1, myTaskHdl->poolID);
#endif
case 1:
pHdr->pduSegAddr0 = SWAP_64(pHdr->pduSegAddr0);
/* swap pduSegSz0..1 */
wordsHdr[11] = SWAP_32(wordsHdr[11]);
#ifdef NCP_TASK_DBG_BUFFERS
/* Use buffer base here,  not start of pdu data */
ncp_task_v2_del_onNca((void *)pHdr, myTaskHdl->poolID);
#endif
default:
break;
}     /* switch */

/* swap debug data, if present */
if (pHdr->debug)
{
switch(pHdr->ptrCnt)
{
case 0:
wordsHdr[11] = SWAP_32(wordsHdr[11]);
wordsHdr[12] = SWAP_32(wordsHdr[12]);
break;
case 1:
wordsHdr[14] = SWAP_32(wordsHdr[14]);
wordsHdr[15] = SWAP_32(wordsHdr[15]);
break;
case 2:
wordsHdr[16] = SWAP_32(wordsHdr[16]);
wordsHdr[17] = SWAP_32(wordsHdr[17]);
break;
case 3:
wordsHdr[20] = SWAP_32(wordsHdr[20]);
wordsHdr[21] = SWAP_32(wordsHdr[21]);
break;
case 4:
wordsHdr[22] = SWAP_32(wordsHdr[22]);
wordsHdr[23] = SWAP_32(wordsHdr[23]);
break;
case 5:
wordsHdr[24] = SWAP_32(wordsHdr[24]);
wordsHdr[25] = SWAP_32(wordsHdr[25]);
break;
case 6:
wordsHdr[26] = SWAP_32(wordsHdr[26]);
wordsHdr[27] = SWAP_32(wordsHdr[27]);
break;
default:
break;
}
}


#if (NCP_TASK_NCAV2_SHPOOL_PTR_DEBUG) || defined(NCP_TASK_DBG_55XX_TASK_FLOW)
NCP_MSG(NCP_MSG_INFO,
"RX Task VA=0x%p\r\n",
pHdr);

switch(pHdr->ptrCnt)
{
case 6:
NCP_LOG(NCP_MSG_INFO,"va5=%p\r\n",
((void *)(ncp_raw_addr_t)pHdr->pduSegAddr5));

case 5:
NCP_LOG(NCP_MSG_INFO,"va4=%p\r\n",
((void *)(ncp_raw_addr_t)pHdr->pduSegAddr4));

case 4:
NCP_LOG(NCP_MSG_INFO,"va5=%p\r\n",
((void *)(ncp_raw_addr_t)pHdr->pduSegAddr3));
case 3:
NCP_LOG(NCP_MSG_INFO,"va2=%p\r\n",
((void *)(ncp_raw_addr_t)pHdr->pduSegAddr2));
case 2:
NCP_LOG(NCP_MSG_INFO,"va1=%p\r\n",
((void *)(ncp_raw_addr_t)pHdr->pduSegAddr1));
break;

case 1:
NCP_LOG(NCP_MSG_INFO,"va0=%p\r\n",
((void *)(ncp_raw_addr_t)pHdr->pduSegAddr0));
break;

default:
break;
}

#endif

/*
* consume the entry and update state
*/
pInputQueueEntry->taskAddr = 0LL;  /* Mark that we had read this entry */

NCP_SYSMEM_BARRIER();

p_iPCQ->u.ipcq_info.ipcqConsumerIdx++;
if (0 ==
(p_iPCQ->u.ipcq_info.ipcqConsumerIdx
&= p_iPCQ->nEntriesMinusOne))
{
/* HW Optimization in effect? */
if (NCP_TASK_NCAV2_USES_WRAP_BIT)
{
if (0 != p_iPCQ->pcqToggleBitVal)
{
p_iPCQ->pcqToggleBitVal = 0;
}
else
{
p_iPCQ->u.ipcq_info.ipcqConsumerIdx
= p_iPCQ->pcqToggleBitVal
= NCP_TASK_NVAV2_PGIT_WRAP_BIT;
}
}
p_iPCQ->u.ipcq_info.pIPCQentry
= (ncp_task_ncaV2_iPCQ_entry_t *)(p_iPCQ->pPCQbase);
}
else
{
p_iPCQ->u.ipcq_info.pIPCQentry++;
}

*(p_iPCQ->pConsumerIdx)
= SWAP_16(p_iPCQ->u.ipcq_info.ipcqConsumerIdx);

if (NCP_TASK_CACHE_PRELOAD)
{

#if defined(NCP_NCA_ARM_L2_CACHE_HINTS) && defined(PROC_ARMA15)
#if 0
/*
* ARM only!
*/
pInputQueueEntry = p_iPCQ->u.ipcq_info.pIPCQentry;
ncp_task_prefetch_data((void *)pInputQueueEntry);
{
ncp_ncaV2_input_task_header_t *pItaskHdr;

if (NULL !=
(pItaskHdr = (ncp_ncaV2_input_task_header_t *)
(ncp_raw_addr_t)pInputQueueEntry->taskAddr))
{
ncp_task_prefetch_data((void *)(ncp_raw_addr_t)pItaskHdr->pduSegAddr0);
}
}
#endif
#endif
}

/*
* Replenish receive buffers if CPU pool
* FIXME - handle buffer outage!
*/
if (NCP_TASK_IS_CPU_POOL(myTaskHdl->poolID))
{
switch(pHdr->ptrCnt)
{
case 6:
NCP_CALL(ncp_task_v2_supply_freebuffer_to_nca(
myTaskHdl,
pHdr->pduBlockSz5,
TRUE));
case 5:
NCP_CALL(ncp_task_v2_supply_freebuffer_to_nca(
myTaskHdl,
pHdr->pduBlockSz4,
TRUE));
case 4:
NCP_CALL(ncp_task_v2_supply_freebuffer_to_nca(
myTaskHdl,
pHdr->pduBlockSz3,
TRUE));
case 3:
NCP_CALL(ncp_task_v2_supply_freebuffer_to_nca(
myTaskHdl,
pHdr->pduBlockSz2,
TRUE));
case 2:
NCP_CALL(ncp_task_v2_supply_freebuffer_to_nca(
myTaskHdl,
pHdr->pduBlockSz1,
TRUE));
case 1:
case 0:   /* Zero length tasks consume a buffer too */
NCP_CALL(ncp_task_v2_supply_freebuffer_to_nca(
myTaskHdl,
pHdr->pduBlockSz0,
TRUE));
break;
default:
break;
}   /* switch */
}
}
else
{
ncpStatus = NCP_ST_TASK_RECV_QUEUE_EMPTY;
}

NCP_RETURN_LABEL

return(ncpStatus);
}

#if !defined(NCP_DEV_SOCKET)
NCP_INLINE ncp_st_t
ncp_task_v2_free_send_buffers(ncp_task_pcq_t   *p_oPCQ, ncp_bool_t bulkFree)
{
ncp_st_t ncpStatus = NCP_ST_SUCCESS;

/* FIXME - Still needed for 55xx if CPU managed pool */
/* Must use Auxdata,   since NCA will overwrite 1st 64 bytes
* (includes cmdCode) as part of queue processing
*/

NCP_RETURN_LABEL
return(ncpStatus);
}
#endif

#endif/* #if !defined(NCP_DEV_SOCKET) */

#endif/* #ifndef __ncp_task_inline_funcs_axm55xx__ */

