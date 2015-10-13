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

#define NCP_TASK_USE_55XX_HEADERS
/*
#define DEBUG
#include <common.h>
#define NCP_TASK_DEBUG_MME
*/
#ifdef NCP_DEV_FBRS
#define NCP_TASK_NCA_GLOBALS
#endif

#if 0 /* UBOOT */
#include "ncp_dev.h"
#include "ncp_release_id.h"
#endif

#include "ncp_task_pvt.h"

#if 0 /* UBOOT */
#if !defined(NCP_KERNEL) || defined(NCP_VXWORKS)
#include "ncp.h"
#include "ncp_pvt.h"
#endif
#endif

#ifndef NCP_DEV_FBRS
#include "ncp_task_inline_funcs_axm55xx.h"
#endif


/* ========================================================================
 * This file contains config entry points and support functions for NCA on
 * ACP55xx
 * ========================================================================
 */


/*
 * ========================================
 * globals
 * ========================================
 */


/* =======================================
 * Functions
 * =======================================
 */

#ifdef NCP_DEV_FBRS
ncp_st_t
ncp_task_v2_fbrs_allocate_domain_object(int size, void **pAddr, ncp_bool_t doMemset)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    if (NULL == (*pAddr = malloc(size)))
        ncpStatus = NCP_ST_NO_MEMORY;
    else if (doMemset)
        memset(*pAddr, 0, size);
    return(ncpStatus);
}
#endif



#if 0 /* UBOOT */
/*
 * CONFIG Functions - only callable in user mode!
 * ==============================================
 */
#if !defined(NCP_KERNEL) || defined(NCP_VXWORKS)
ncp_st_t
ncp_task_v2_config_iPCQs_perThreadSet(ncp_map_t *map, ncp_int32_t tqsID, ncp_nca_t *nca)
{

    ncp_st_t ncpStatus=NCP_ST_SUCCESS;
    ncp_map_value_t *iPCQs[NCP_X7_NUM_IPCQ_PER_GROUP];
    ncp_map_t		*map2;
    int i;
    ncp_uint32_t num_iPCQs;
    int qID;


    /* How many iPCQs total in this group       */

    NCP_CALL(ncp_map_get_all_values(map, "TaskReceiveQueue", iPCQs,
            NCP_X7_NUM_IPCQ_PER_GROUP, &num_iPCQs, 0));


    pNcpNcaV2_TaskSwState->pcq_grp[pNcpNcaV2_TaskSwState->threadQueueSets[tqsID].grpId].num_iPCQs += num_iPCQs;

    NCP_MSG(NCP_MSG_DEBUG, "Configuring %d iPCQs\r\n", num_iPCQs);

    for (i=0; i < num_iPCQs; i++)
    {
#ifndef NCP_DEV_SOCKET
        char *strVal=NULL;
#endif

        if(iPCQs[i]->type != ncp_map_type_map)
        {
            continue;
        }

        map2 = iPCQs[i]->u.mapValue;

        NCP_CALL(ncp_map_get_i32(map2, "id", (ncp_int32_t *)(&qID)));

        if (0 == i)
        {
            pNcpNcaV2_TaskSwState->threadQueueSets[tqsID].first_iPCQ_id
                = qID;

            pNcpNcaV2_TaskSwState->threadQueueSets[tqsID].num_iPCQs_in_queueSet
                = num_iPCQs;
        }

        NCP_CALL(ncp_map_get_i32(map2, "entries", (ncp_int32_t *)(&pNcpNcaV2_TaskSwState->iPCQs[qID].nEntries)));

        NCP_CALL(ncp_map_get_i32(map2, "wrrWeight",
            &pNcpNcaV2_TaskSwState->iPCQs[qID].u.ipcq_info.wrrWeight));

        NCP_CALL(ncp_map_get_bool(map2, "allowMultiSegmentInputTask",
            (&pNcpNcaV2_TaskSwState
             ->iPCQs[qID].u.ipcq_info.multiSegRxOK)));

        NCP_CALL(ncp_map_get_i64(map2, "iPcqOffset",
                                (ncp_int64_t *)(&pNcpNcaV2_TaskSwState->iPCQs[qID].u.ipcq_info.iPcqOffset)));

#ifdef NCP_DEV_SOCKET
        /* Force automatic completion for socket mode.   We use the 34xx rdev interface,  but have no tPCQs in 55xx */
        pNcpNcaV2_TaskSwState->iPCQs[qID].u.ipcq_info.rxTaskCompletionMode
                = NCP_TASK_COMPLETION_HW_AUTOMATIC;
#else
        NCP_CALL(ncp_map_get_str(map2, "taskCompletionMode", &strVal));

        if (0 == strcmp(strVal, "Automatic"))
        {
            pNcpNcaV2_TaskSwState->iPCQs[qID].u.ipcq_info.rxTaskCompletionMode
                = NCP_TASK_COMPLETION_HW_AUTOMATIC;
        }
        else
        {
            pNcpNcaV2_TaskSwState->iPCQs[qID].u.ipcq_info.rxTaskCompletionMode
                = NCP_TASK_COMPLETION_MANUAL;
            pNcpNcaV2_TaskSwState->threadQueueSets[tqsID]
                .requiresCompletionData = TRUE;
        }
#endif /* NCP_DEV_SOCKET */
    }


NCP_RETURN_LABEL

    return(ncpStatus);
}


ncp_st_t
ncp_task_v2_config_allocators_perTQS(ncp_map_t *map,
                                     ncp_int32_t tqsID,
                                     ncp_nca_t *nca,
                                     ncp_int32_t domain)
{
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;
    ncp_map_value_t *allocator[NCP_X7_NUM_MME_ALLOCATORS];
    ncp_map_t		*map2, *map3;
    ncp_uint32_t    numAllocators;
    int i;
    ncp_nca_thread_queue_set_t *pTQS
        = &pNcpNcaV2_TaskSwState->threadQueueSets[tqsID];

    /* VP Managed Shared Pool ? */
    if (NCP_TASK_IS_SHARED_POOL(pTQS->poolID))
    {
        NCP_CALL(ncp_map_get_map(map, "Allocators", &map2));
        NCP_CALL(ncp_map_get_all_values(map2,
                                        "Allocator",
                                        allocator,
                                        NCP_X7_NUM_MME_ALLOCATORS,
                                        &numAllocators,
                                        0));



        pTQS->numAllocators = numAllocators;

        NCP_ASSERT((NULL != (pTQS->mme
            = (ncp_task_mme_allocator_t   *)
               ncp_nvm_malloc(
                            (sizeof(ncp_task_mme_allocator_t))
                             * numAllocators))),
                            NCP_ST_TASK_NO_MALLOC_MEM);

        memset(pTQS->mme,
               0,
               (sizeof(ncp_task_mme_allocator_t))
                             * numAllocators);

        for (i=0; i<numAllocators; i++)
        {
            if(allocator[i]->type != ncp_map_type_map)
            {
                pTQS->mme[i].valid = FALSE;
                continue;
            }
            map3 = allocator[i]->u.mapValue;

            pTQS->mme[i].valid = TRUE;
            NCP_CALL(ncp_map_get_i32(
                        map3,
                        "allocatorId",
                        (ncp_int32_t *)(&pTQS->mme[i].id)));

            NCP_CALL(ncp_map_get_i64(
                        map3,
                        "allocatorOffset",
                        &pTQS->mme[i].cfgOffset));
        }
    } /* VP Managed Shared Pool ? */

NCP_RETURN_LABEL

    return(ncpStatus);
}

ncp_st_t
ncp_task_v2_config_threadQueueSets_perGroup(ncp_map_t *map,
                                            ncp_int32_t grpId,
                                            ncp_nca_t *nca,
                                            ncp_int32_t domain)
{
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;
    ncp_map_value_t *threadQueueSets[NCP_X7_NUM_THREAD_QUEUESETS_PER_GROUP];
    ncp_map_t		*map2;
    int i;
    ncp_uint32_t num_threadQueueSets;
    char            *strVal=NULL;
    int poolID;

    /* How many threadQueueSets total in this group       */

    NCP_CALL(ncp_map_get_all_values(map, "ThreadQueueSet", threadQueueSets,
            NCP_X7_NUM_THREAD_QUEUESETS_PER_GROUP, &num_threadQueueSets, 0));

    NCP_ASSERT(num_threadQueueSets <= NCP_X7_NUM_THREAD_QUEUESETS_PER_GROUP, NCP_ST_TASK_CFG_TOO_MANY_THREAD_QUEUESETS_PER_GROUP);

    pNcpNcaV2_TaskSwState->pcq_grp[grpId].num_oPCQs = num_threadQueueSets;
    pNcpNcaV2_TaskSwState->pcq_grp[grpId].num_cPCQs = num_threadQueueSets;


    NCP_MSG(NCP_MSG_DEBUG, "Configuring %d threadQueueSets\r\n", num_threadQueueSets);

    for (i = 0; i < num_threadQueueSets; i++)
    {
        ncp_int32_t id;

        if(threadQueueSets[i]->type != ncp_map_type_map)
        {
            continue;
        }
        map2 = threadQueueSets[i]->u.mapValue;

        NCP_CALL(ncp_map_get_i32(map2, "id", (ncp_int32_t *)(&id)));

        pNcpNcaV2_TaskSwState->threadQueueSets[id].id = id;
        pNcpNcaV2_TaskSwState->threadQueueSets[id].grpId = grpId;
        NCP_CALL(ncp_map_get_i32(map2, "taskSendQEntries",
                                (ncp_int32_t *)(&pNcpNcaV2_TaskSwState->oPCQs[id].nEntries)));

        NCP_CALL(ncp_map_get_i32(map2, "configurationQEntries",
                                (ncp_int32_t *)(&pNcpNcaV2_TaskSwState->cPCQs[id].nEntries)));

        NCP_CALL(ncp_map_get_i32(map2, "copyToSharedPool",
                                (ncp_int32_t *)
                                (&pNcpNcaV2_TaskSwState->oPCQs[id].u.opcq_info.copyPool)));

        NCP_CALL(ncp_map_get_i32(map2, "memoryPool",
                                (ncp_int32_t *)(&poolID)));

        pNcpNcaV2_TaskSwState->threadQueueSets[id].poolID = poolID;

        pNcpNcaV2_TaskSwState->taskMemoryPool[poolID].tqsRefCount++;

        NCP_CALL(ncp_map_get_str(map2, "mode", &strVal));

        if (0 == strcmp(strVal, "USER"))
        {

#ifdef NCP_KMODE_DEBUG
            NCP_LOG(NCP_MSG_INFO,
                "Marking TQS %d and poolID %d as user mode\r\n",
                id, poolID);
#endif

            pNcpNcaV2_TaskSwState->threadQueueSets[id].uMode    = TRUE;
            pNcpNcaV2_TaskSwState->taskMemoryPool[poolID].uMode = TRUE;
        }
        else
        {
#ifdef NCP_KMODE_DEBUG
            NCP_LOG(NCP_MSG_INFO,
                "Marking TQS %d and poolID %d as kernel mode\r\n",
                id, poolID);
#endif

            pNcpNcaV2_TaskSwState->kernelModeConfigured = TRUE;
            pNcpNcaV2_TaskSwState->threadQueueSets[id].uMode    = FALSE;
            pNcpNcaV2_TaskSwState->taskMemoryPool[poolID].uMode = FALSE;
        }

        NCP_CALL(ncp_map_get_i64(map2, "oPcqOffset",
                                (ncp_int64_t *)(&pNcpNcaV2_TaskSwState->oPCQs[id].u.opcq_info.oPcqOffset)));

        NCP_CALL(ncp_map_get_i64(map2, "cPcqOffset",
                                (ncp_int64_t *)(&pNcpNcaV2_TaskSwState->cPCQs[id].u.cpcq_info.cPcqOffset)));


        pNcpNcaV2_TaskSwState->threadQueueSets[id].qsAccessMode
            = NCP_NCA_QS_AVAILABLE;

        NCP_CALL(ncp_task_v2_config_allocators_perTQS(map2,
                                                      id,
                                                      nca,
                                                      domain));

        NCP_CALL(ncp_task_v2_config_iPCQs_perThreadSet(map2, id, nca));

        pNcpNcaV2_TaskSwState->threadQueueSets[id].tqsDomain = domain;
    }

NCP_RETURN_LABEL

    return(ncpStatus);
}




/*
 * Configure Task Queue Groups
 * TODO: Save off info to be used later during h/w config
 */
ncp_st_t
ncp_task_v2_config_queue_groups(ncp_t *ncp, ncp_map_t *map, ncp_nca_t *nca)
{
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;
    ncp_map_value_t *queueGroups[NCP_X7_NUM_PCQ_GROUPS];
    ncp_map_value_t *ncaDomainInfos[NCP_X7_NUM_DOMAINS];
    ncp_map_value_t *domainEntry[NCP_X7_NUM_DOMAINS];
    ncp_uint32_t    numDomainEntries;
    ncp_uint32_t    numQueueGroups=0;
    ncp_uint32_t    numNcaDomainInfos=0;
    ncp_map_t		*map2, *map3;
    char            *strVal=NULL;
    int             i;



        /* Get domain bundle start and size */

        NCP_CALL(ncp_map_get_all_values(map, "NcaDomainInfo", ncaDomainInfos,
                 NCP_X7_NUM_PCQ_GROUPS, &numNcaDomainInfos, 0));

        if(ncaDomainInfos[0]->type != ncp_map_type_map)
        {
            NCP_CALL(NCP_ST_TASK_MISSING_NCADOMAININFO_SECTION);
        }
        map2 = ncaDomainInfos[0]->u.mapValue;

        for (i=0; i < numNcaDomainInfos; i++)
        {
            ncp_int32_t id;

            NCP_CALL(ncp_map_get_all_values(map2, "DomainEntry", domainEntry,
                 NCP_X7_NUM_PCQ_GROUPS, &numDomainEntries, 0));
            if(domainEntry[i]->type != ncp_map_type_map)
            {
                continue;
            }
            map3 = domainEntry[i]->u.mapValue;


            NCP_CALL(ncp_map_get_i32(map3, "id", &id));
            if (id != pNcpNcaV2_TaskSwState->myDomain)
            {
                continue;
            }
            /*
             * found it
             */
#if 1
            {
                ncp_int64_t tmpVA64=0;
                NCP_CALL(ncp_map_get_i64(map3, "vpIOControlVirtualBaseOffset",
                    (ncp_int64_t *)&tmpVA64));
                pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_VA
                    = (ncp_raw_addr_t) tmpVA64;
            }
#else
            pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_VA = 0;
#endif

            NCP_CALL(ncp_map_get_i64(map3, "startOffset",   (ncp_int64_t *)&pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_PA));
            NCP_CALL(ncp_map_get_i64(map3, "size",          (ncp_int64_t *)&pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_Size));
            /*
             * Output task backpressure offset
             */
            NCP_CALL(ncp_map_get_i64(map3, "otbpOffset",   (ncp_int64_t *)&pNcpNcaV2_TaskSwState->otbpInfo_Offset));
            break;
        }

        if (i == numNcaDomainInfos)
        {
            NCP_CALL(NCP_ST_TASK_MISSING_NCADOMAININFO_SECTION);
        }


        /* get group global data */


        /*
         * Preinit all groups to unused
         */
        for (i=0; i<NCP_X7_NUM_PCQ_GROUPS; i++)
        {
            pNcpNcaV2_TaskSwState->pcq_grp[i].id=0xFF; /* unused */
        }

        /*
         * Preinit all QueueSets to unused
         */
        for (i=0; i<NCP_X7_NUM_THREAD_QUEUESETS; i++)
        {
            pNcpNcaV2_TaskSwState->threadQueueSets[i].id=0xFF; /* unused */
        }



        /* How many queue groups total ? */

        NCP_CALL(ncp_map_get_all_values(map, "QueueGroup", queueGroups,
                 NCP_X7_NUM_PCQ_GROUPS, &numQueueGroups, 0));

        NCP_ASSERT(numQueueGroups <= NCP_X7_NUM_PCQ_GROUPS, NCP_ST_TASK_CFG_TOO_MANY_QUEUE_GROUPS);



        NCP_MSG(NCP_MSG_DEBUG, "Configuring %d queue groups\r\n", numQueueGroups);

        for (i=0; i < numQueueGroups; i++)
        {
            ncp_int32_t id;

            if(queueGroups[i]->type != ncp_map_type_map)
            {
                continue;
            }
            map2 = queueGroups[i]->u.mapValue;

            NCP_CALL(ncp_map_get_i32(map2, "id", &id));
            pNcpNcaV2_TaskSwState->pcq_grp[i].id = id;



            NCP_CALL(ncp_map_get_i32(map2, "managementDomain", &pNcpNcaV2_TaskSwState->pcq_grp[i].grpDomain));

            NCP_CALL(ncp_map_get_u32(map2, "pgitNormalLoadTimer", &pNcpNcaV2_TaskSwState->pcq_grp[i].pgitNormalLoadTimer));

            NCP_CALL(ncp_map_get_u32(map2, "pgitNormalUploadTimer", &pNcpNcaV2_TaskSwState->pcq_grp[i].pgitNormalUploadTimer));
            NCP_CALL(ncp_map_get_str(map2, "cpuId", &strVal));
            if (0 == strcmp(strVal, "INTERNAL_ANY"))
            {
                 pNcpNcaV2_TaskSwState->pcq_grp[i].cpuId = NCP_NCA_CPU_ANY;
            }
            else if (0 == strcmp(strVal, "INTERNAL_ZERO"))
            {
                pNcpNcaV2_TaskSwState->pcq_grp[i].cpuId=NCP_NCA_CPU_0;
            }
            else if (0 == strcmp(strVal, "INTERNAL_ONE"))
            {
                pNcpNcaV2_TaskSwState->pcq_grp[i].cpuId=NCP_NCA_CPU_1;
            }
            else if (0 == strcmp(strVal, "INTERNAL_TWO"))
            {
                pNcpNcaV2_TaskSwState->pcq_grp[i].cpuId=NCP_NCA_CPU_2;
            }
            else if (0 == strcmp(strVal, "INTERNAL_THREE"))
            {
                pNcpNcaV2_TaskSwState->pcq_grp[i].cpuId=NCP_NCA_CPU_3;
            }
            else if (0 == strcmp(strVal, "INTERNAL_PCIe0"))
            {
                pNcpNcaV2_TaskSwState->pcq_grp[i].cpuId=NCP_NCA_CPU_PCIe0;
            }
                else if (0 == strcmp(strVal, "INTERNAL_PCIe1"))
            {
                pNcpNcaV2_TaskSwState->pcq_grp[i].cpuId=NCP_NCA_CPU_PCIe1;
            }
            else if (0 == strcmp(strVal, "INTERNAL_PCIe2"))
            {
                pNcpNcaV2_TaskSwState->pcq_grp[i].cpuId=NCP_NCA_CPU_PCIe2;
            }
            else if (0 == strcmp(strVal, "INTERNAL_SRIO"))
            {
                pNcpNcaV2_TaskSwState->pcq_grp[i].cpuId=NCP_NCA_CPU_SRIO;
            }

            NCP_CALL(ncp_map_get_u32(map2, "pgitNormalLoadTimer", &pNcpNcaV2_TaskSwState->pcq_grp[i].pgitNormalLoadTimer));
            NCP_CALL(ncp_map_get_u32(map2, "pgitNormalUploadTimer", &pNcpNcaV2_TaskSwState->pcq_grp[i].pgitNormalUploadTimer));
            NCP_CALL(ncp_map_get_u32(map2, "pgitNcaEventLoadTimer", &pNcpNcaV2_TaskSwState->pcq_grp[i].pgitNcaEventLoadTimer));

            NCP_CALL(ncp_map_get_i32(map2, "taskArrivalsPerInterrupt", &pNcpNcaV2_TaskSwState->pcq_grp[i].taskArrivalsPerInterrupt));
            NCP_CALL(ncp_map_get_i32(map2, "taskArrivalInterruptMaxDelayTime",
                                            &pNcpNcaV2_TaskSwState->pcq_grp[i].taskArrivalInterruptMaxDelayTime));

            NCP_CALL(ncp_map_get_u32(map2, "pgitNcaEventUploadTimer", &pNcpNcaV2_TaskSwState->pcq_grp[i].pgitNcaEventUploadTimer));
            NCP_CALL(ncp_map_get_u32(map2, "pgitIpcqEmptyToNotEmptyLoadTimer",
                                            &pNcpNcaV2_TaskSwState->pcq_grp[i].pgitIpcqEmptyToNotEmptyLoadTimer));
            NCP_CALL(ncp_map_get_u32(map2, "pgitCpuEventLoadTimer", &pNcpNcaV2_TaskSwState->pcq_grp[i].pgitCpuEventLoadTimer));

            NCP_CALL(ncp_map_get_i32(map2, "pgitTaskArrivalEventThreshold",
                                            &pNcpNcaV2_TaskSwState->pcq_grp[i].pgitTaskArrivalEventThreshold));
            NCP_CALL(ncp_map_get_i32(map2, "pgitOutputEventThreshold", &pNcpNcaV2_TaskSwState->pcq_grp[i].pgitOutputEventThreshold));
            NCP_CALL(ncp_task_v2_config_threadQueueSets_perGroup(map2, i, nca, pNcpNcaV2_TaskSwState->pcq_grp[i].grpDomain));

            NCP_CALL(ncp_map_get_i64(map2, "ncaPgitOffset", (ncp_int64_t *)&pNcpNcaV2_TaskSwState->pcq_grp[i].ncaPgitOffset));
            NCP_CALL(ncp_map_get_i64(map2, "cpuPgitOffset", (ncp_int64_t *)&pNcpNcaV2_TaskSwState->pcq_grp[i].cpuPgitOffset));
      }
NCP_RETURN_LABEL
    return(ncpStatus);
}

#endif /* UBOOT */


/*
 * Config entry point for NCA
 */


ncp_st_t
ncp_task_v2_config(ncp_t         *ncp,
               ncp_map_t     *map)
{
    ncp_st_t         ncpStatus = NCP_ST_SUCCESS;
    ncp_nca_t        *nca;

#if defined(NCP_KERNEL) && !defined(NCP_VXWORKS)
    NCP_CALL(NCP_ST_NOT_IMPLEMENTED);
#else
    ncp_mme_pool_t *pMMEpoolInfo;
    ncp_dev_hdl_t    devHdl = ncp_dev_hdls[ncp->id];
    ncp_task_hdl_t  taskHdl=NULL;
    ncp_uint8_t     tqsId;
    int i, j;
    int buffSizes[4] = {256, (2*1024), (16*1024), (64*1024)};

    NCP_ASSERT((NULL !=
                (nca = (ncp_nca_t *)ncp_nvm_malloc(sizeof(ncp_nca_t)))),
                NCP_ST_TASK_NO_MALLOC_MEM);

    ncp_memset(nca, 0, sizeof(ncp_nca_t));
    nca->cookie = NCP_TASK_STATE_COOKIE;

    NCP_ASSERT((NULL !=
                (nca->myNcpNcaTaskState =
                    ncp_nvm_malloc(sizeof(ncp_task_ncaV2_t)))),
                 NCP_ST_TASK_NO_MALLOC_MEM);
    ncp_memset(nca->myNcpNcaTaskState, 0, sizeof(ncp_task_ncaV2_t));
    pNcpNcaV2_TaskSwState = nca->myNcpNcaTaskState;
    ncp->ncaHdl = (ncp_nca_t *)nca;

    /* initialize alarm handler */
    NCP_CALL(ncp_nca_alarm_handler_register((ncp_hdl_t)ncp));


    /* Step 1: initialize COW - primary domain only */
    if (NCP_IS_PRIMARY_DOMAIN(ncp))
    {
        NCP_CALL(ncp_cow_engine_init(ncp, ncp_engine_cpu, map));
    }

    /*
     * Get task memory pool config from MME
     */

    NCP_CALL(ncp_mme_pool_config_get((ncp_hdl_t) ncp,  &pMMEpoolInfo));

    /*
     * Make a copy,  since the kernel mode task io module will need this
     */
    memcpy(&pNcpNcaV2_TaskSwState->MMEpoolInfo,
           pMMEpoolInfo,
           (NCP_X7_NUM_TASK_MEMORY_POOLS * sizeof(ncp_mme_pool_t)));

    for (i=0; i<NCP_X7_NUM_TASK_MEMORY_POOLS; i++)
    {
        /*
         * Just grab the fields that are needed by Task I/O.
         */
        pNcpNcaV2_TaskSwState->taskMemoryPool[i].pool_PA
            = pMMEpoolInfo[i].poolPhysBase;

        pNcpNcaV2_TaskSwState->taskMemoryPool[i].pool_Size
            = pMMEpoolInfo[i].poolSize;

        pNcpNcaV2_TaskSwState->taskMemoryPool[i].pool_VA
            = (ncp_raw_addr_t)pMMEpoolInfo[i].poolVirtBase;

        pNcpNcaV2_TaskSwState->taskMemoryPool[i].pool_EndVA
            = (ncp_raw_addr_t)pMMEpoolInfo[i].maxDynamic;

        for (j=0; j<NCP_TASK_NUM_BUFF_SIZES; j++)
        {
            /* NOTE: MME stores in reverse order from what Task I/O uses. */
            int taskIO_index = NCP_TASK_NUM_BUFF_SIZES - j - 1;
            ncp_uint64_t temp64;

            pNcpNcaV2_TaskSwState->taskMemoryPool[i].numBlocks[taskIO_index]
                = pMMEpoolInfo[i].numBlocks[j];

            pNcpNcaV2_TaskSwState->taskMemoryPool[i].blocksVA[taskIO_index]
                = (void *)(ncp_raw_addr_t)pMMEpoolInfo[i].virtBase[j];

            temp64 = (ncp_uint64_t)(ncp_raw_addr_t)
                pNcpNcaV2_TaskSwState->taskMemoryPool[i].blocksVA[taskIO_index];
            temp64 += (pMMEpoolInfo[i].numBlocks[j] * buffSizes[taskIO_index]);
            pNcpNcaV2_TaskSwState->taskMemoryPool[i].blocksVAend[taskIO_index]
                = (void *) ( ncp_raw_addr_t) temp64;

            pNcpNcaV2_TaskSwState->taskMemoryPool[i].blocksPA[taskIO_index]
                = pMMEpoolInfo[i].physBase[j];

            pNcpNcaV2_TaskSwState->taskMemoryPool[i].numBlocksRxReserve[taskIO_index]
                = pMMEpoolInfo[i].numReserveBlocks[j];
        }
    }

    /* NCA Task Queue Groups */
    NCP_CALL(ncp_task_v2_config_queue_groups(ncp, map, nca));

    /*
     * Config has been parsed and validated, so now configure the hardware
     */

    NCP_CALL(ncp_task_v2_config_hw((ncp_hdl_t)ncp, devHdl, nca, FALSE));



    /*
     * Create default config-time taskHdl so that other engines may send tasks as part of their
     * config-time init.  This will be release at config exit.  Ignore Errors!
     */
    NCP_CALL(ncp_task_get_default_queueset((ncp_hdl_t)ncp, &tqsId));

    NCP_CALL(ncp_task_hdl_create(ncp,
                                 tqsId,
                                 FALSE,
                                 FALSE,
                                 &taskHdl));

    /*
     * Step 2: Bring COW online - primary domain only. This needs to be done
     * last in engine config.
     */
    if (NCP_IS_PRIMARY_DOMAIN(ncp))
    {
        NCP_CALL(ncp_cow_engine_online(ncp, ncp_engine_cpu, map));
    }

#endif

NCP_RETURN_LABEL

    if (NCP_ST_SUCCESS != ncpStatus)
    {
        if (NULL != nca)
        {
#if !defined(NCP_KERNEL) || defined(NCP_VXWORKS)
            ncp_nvm_free(nca);
#else
            /* FIXME !! for kernel */
#endif
        }
    }
    return ncpStatus;
}

#endif  /* !defined(NCP_KERNEL) || defined(NCP_VXWORKS) */

/*
 * END - Config Functions
 * ==============================================
 */

/*
 * Get the pcq ptr, by mapping the sequential queue # to a group/queue pair
 */

ncp_st_t
ncp_task_v2_map_queuenum_to_pcq(ncp_task_pcq_type_t qType, ncp_uint8_t queueNum, ncp_task_pcq_t   **ppcq)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;


    /*
     * is queue value in the valid range for this type of queue?
     */

    if (NCP_TASK_PCQ_INPUT == qType)
    {
        if (NCP_X7_NUM_HW_INPUT_QUEUES <= queueNum)
        {
            NCP_CALL(NCP_ST_TASK_QMAP_ERR_TOO_BIG);
        }
    }
    else if (NCP_X7_NUM_HW_NONINPUT_QUEUES <= queueNum)
    {
        {
            NCP_CALL(NCP_ST_TASK_QMAP_ERR_TOO_BIG);
        }
    }

    switch (qType)
    {
    case NCP_TASK_PCQ_INPUT:

        *ppcq = &pNcpNcaV2_TaskSwState->iPCQs[queueNum];
        break;

    case NCP_TASK_PCQ_OUTPUT:

        *ppcq = &pNcpNcaV2_TaskSwState->oPCQs[queueNum];
        break;

    case NCP_TASK_PCQ_CONFIG:


        *ppcq = &pNcpNcaV2_TaskSwState->cPCQs[queueNum];
        break;

    default:

        NCP_CALL(NCP_ST_TASK_UNEXPECTED_QUEUE_TYPE);
    } /* switch */

#ifndef NCP_DEV_SOCKET
    /*
     * Don't clutter up the ncpTaskDebug CLI's output, let caller handle error, or not.
     */
    if (NULL == (*ppcq)->pProducerIdx)
    {
        ncpStatus = NCP_ST_TASK_NULL_PCQ_PRODUCER_PTR;
        goto ncp_return;
    }
    if (NULL == (*ppcq)->pConsumerIdx)
    {
        ncpStatus = NCP_ST_TASK_NULL_PCQ_CONSUMER_PTR;
        goto ncp_return;
    }
#endif /* NCP_DEV_SOCKET     */

NCP_RETURN_LABEL

    if (NCP_ST_SUCCESS != ncpStatus)
    {
        NCP_LOG(NCP_MSG_ERROR, "queue type %d, id=%d is not configured for mode=%d\r\n",
            qType,
            queueNum,
            pNcpNcaV2_TaskSwState->inUmode);

    }
    return(ncpStatus);
}

ncp_st_t
ncp_task_v2_init_version_specific_features(ncp_dev_hdl_t dev,
                                            ncp_nca_t *nca,
                                            ncp_uint32_t activeGroupMask,
                                            ncp_bool_t warmRestart,
                                            ncp_bool_t domainIsInternal)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    int i;

    if (!warmRestart && pNcpNcaV2_TaskSwState->inUmode)
    {

        /* primary domain? */
        if (0 == pNcpNcaV2_TaskSwState->myDomain)
        {
#if 0 /* FIXME - Disabled for now */
            /*
            * Only enable config dma queues if this platform
            * supports interrupts
            */
            if (pNcpNcaV2_TaskSwState->useInterrupts) {
                NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_DRIVER_CFG,
                            NCP_DEV_CFG_DMA_ENABLED, 1);
            }
#endif

            /*
            * Backpressure changed in V2
            *
            * program nca and cpu virtual index registers with 38 bit physaddr
            */
#ifdef NCP_TASK_OTBP_ALLOWED
            {
#if 0 /* UBOOT */
                ncp_uint64_t otaskBackPressurePhysAddr;
                ncp_nca_otbp_vi_reg0_55xx_t r0;
                ncp_nca_otbp_vi_reg1_55xx_t r1;
                ncp_uint32_t *pR0;
                ncp_uint32_t *pR1;

                pR0 = (ncp_uint32_t *)&r0;
                pR1 = (ncp_uint32_t *)&r1;
#endif

                NCP_CALL(NCP_TASK_INITIALIZE_DOMAIN_OBJ_VA(
                    pNcpNcaV2_TaskSwState->otbpInfo_Offset,
                    sizeof(ncp_uint32_t),
                    &pNcpNcaV2_TaskSwState->otbpInfo_VA,
                    TRUE));

#if 0 /* UBOOT */
                otaskBackPressurePhysAddr
                    = NCP_TASK_VA_2_PA(pNcpNcaV2_TaskSwState->otbpInfo_VA,
                                       0);

                if (domainIsInternal)
                {
                    r0.mem_sel = 0; /* Sysmem */
                }
                else
                {
                    r0.mem_sel = 1; /* AXI */
                }
                r0.pool_id = NCP_TASK_VP_CONTROL_POOL_ID;     /* Always 0 */


                r0.otbp_vi_upper = (ncp_uint32_t)   ((otaskBackPressurePhysAddr >> 32) & (0x0000000F));   /* 4 bits */
                r1.otbp_vi_lower = (ncp_uint32_t)   ((otaskBackPressurePhysAddr & 0xfffffffC) >> 2);      /* Byte address with low 2 bits 0 */

                NCP_DEV_NCA_WRITE_REG32(dev,
                    NCP_REGION_NCA_AXI,NCP_NCA_OTBP_VI_UPPER_55XX, *pR0);
                NCP_DEV_NCA_WRITE_REG32(dev,
                    NCP_REGION_NCA_AXI,NCP_NCA_OTBP_VI_LOWER_55XX, *pR1);
#endif

#ifdef NCP_TASK_PRINT_BASE_ADDRESSES_AND_MAPPINGS
    NCP_MSG(NCP_MSG_INFO, "initialized otbp base address PA=0x%llx, VA=%p\n",
                (long long unsigned int)otaskBackPressurePhysAddr,
                pNcpNcaV2_TaskSwState->otbpInfo_VA);
#endif

            }
#endif  /* NCP_TASK_OTBP_ALLOWED --- HACK  --- DISABLE */

#ifndef NCP_DEV_SOCKET

            /*
            * Interrupts changed in V2
            *
            * Enable routing of interrupts on a per group basis
            */
            {
#if 0 /* FIXME - enable after all isrs present */
                ncp_nca_mpic_ctrl_reg_55xx_t mpic_ctl;

                /* all groups regardless of domain,  and all non nca ints go to grp 0 */
                mpic_ctl.grp_int_en
                    = pNcpNcaV2_TaskSwState->allGrpMask;
                /* Enable h/w int too */
                mpic_ctl.hw_int_en = 1;
#endif
                NCP_DEV_NCA_WRITE_REG32(dev,
                                        NCP_REGION_NCA_AXI,
                                        NCP_NCA_MPIC_CTRL_55XX,
                                        *(ncp_uint32_t *)(&mpic_ctl));
            }

#endif

        } /* primary domain */

        /*
        * ====== Program V2+ only Timer/Poke Related Registers ======
        */


        for( i = 0; i < NCP_X7_NUM_PCQ_GROUPS; i++)
        {
            int groupId;

            if ((0xFF != (groupId = pNcpNcaV2_TaskSwState->pcq_grp[i].id))
                && (pNcpNcaV2_TaskSwState->pcq_grp[i].grpDomain == pNcpNcaV2_TaskSwState->myDomain))
            {

                NCP_MSG(NCP_MSG_DEBUG, "Programing POKE LOAD/UPLOAD/etc  for grp %d, (grpId from cfg %d),  on domain %d\r\n",
                        i,
                        groupId = pNcpNcaV2_TaskSwState->pcq_grp[i].id,
                        pNcpNcaV2_TaskSwState->myDomain);

                /* upload poke delay */
                if (NCP_TASK_ENABLE_PGIT_UPLOADS)
                {
                    NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,
                        NCP_NCA_DELAY_GRP_UPLOAD_TIMER_55XX(groupId),
                        pNcpNcaV2_TaskSwState->pcq_grp[groupId].pgitNcaEventUploadTimer);
                }

                /* load poke delay */

                NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,
                        NCP_NCA_DELAY_GRP_LOAD_TIMER_55XX(groupId),
                        pNcpNcaV2_TaskSwState->pcq_grp[groupId].pgitNcaEventLoadTimer);

                /* ipcq empty to not empty poke timer*/

                NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,
                        NCP_NCA_IPCQ_ETNE_DELAY_GRP_LOAD_TIMER_55XX(groupId),
                        pNcpNcaV2_TaskSwState->pcq_grp[groupId].pgitIpcqEmptyToNotEmptyLoadTimer);

                /* sw/CPU poke timer */

                NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,
                        NCP_NCA_SWPOKE_DELAY_GRP_LOAD_TIMER_55XX(groupId),
                        pNcpNcaV2_TaskSwState->pcq_grp[groupId].pgitCpuEventLoadTimer);

                 /* iTask arrival counter threshold */

                NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,
                        NCP_NCA_ITASK_ARRIVAL_POKE_GRP_CNT_CMPR_55XX(groupId),
                        pNcpNcaV2_TaskSwState->pcq_grp[groupId].pgitTaskArrivalEventThreshold);

                /* output counter threshold */

                NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,
                        NCP_NCA_OTASK_AND_CPCQ_ENTRY_GRP_CNT_CMPR_55XX(groupId),
                        pNcpNcaV2_TaskSwState->pcq_grp[groupId].pgitOutputEventThreshold);



            }

        } /* for */

#if 0 /* UBOOT */
        {
            ncp_nca_hw_poke_and_timer_enable_reg_55xx_t r32={0};
            ncp_uint32_t *pR32;

            pR32 = (ncp_uint32_t *)&r32;

            r32.ipcq_poke_enable = 1;
            r32.opcq_poke_enable = 1;
            r32.cpcq_poke_enable = 1;

            NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,
                        NCP_NCA_HW_POKE_AND_TIMER_ENABLE_WOSET_55XX,
                        *pR32);
        }

        {
            /* Note mask layout is same for all of the following registers */
            ncp_nca_software_pgit_load_poke_reg_55xx_t r32;
            ncp_uint32_t *pR32;

            pR32 = (ncp_uint32_t *)&r32;

            r32.software_load_poke_grp = (activeGroupMask & 0xffff);


            NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,
                NCP_NCA_PGIT_SOFTWARE_LOAD_POKE_REG_WOSET_55XX,
                *pR32);

            NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,
                NCP_NCA_GRP_LOAD_POKE_ENABLE_55XX,
                *pR32);

            NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,
                NCP_NCA_GRP_LOAD_TIMER_ENABLE_55XX,
                *pR32);

            if (NCP_TASK_ENABLE_PGIT_UPLOADS)
            {
                NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,
                    NCP_NCA_GRP_UPLOAD_POKE_ENABLE_55XX,
                    *pR32);

                NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,
                    NCP_NCA_GRP_UPLOAD_TIMER_ENABLE_55XX,
                    *pR32);
            }
        }
#endif
    }   /* !warm restart */

NCP_RETURN_LABEL

    return(ncpStatus);
}


ncp_st_t
ncp_task_v2_pcq_disable(
    ncp_dev_hdl_t dev,
    ncp_uint32_t pcqType,
    ncp_uint32_t queueId)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
#if 0 /* UBOOT */
    ncp_nca_PCQ_desc_reg0_55xx_t pcq_desc_r0 = {0};
    ncp_uint32_t offset;

    /* find the register offset for this queue */
    switch (pcqType) {
        case NCP_TASK_PCQ_INPUT:
            offset = NCP_NCA_PCQ_DESC_IPCQ_R0_55XX(queueId);
            NCP_MSG(NCP_MSG_DEBUG, "Enable iPCQ(%d)\r\n",queueId);
            break;

        case NCP_TASK_PCQ_OUTPUT:
            offset = NCP_NCA_PCQ_DESC_OPCQ_R0_55XX(queueId);
            NCP_MSG(NCP_MSG_DEBUG, "Enable oPCQ(%d)\r\n",queueId);
            break;

        case NCP_TASK_PCQ_CONFIG:
            offset = NCP_NCA_PCQ_DESC_CPCQ_R0_55XX(queueId);
            NCP_MSG(NCP_MSG_DEBUG, "Enable cPCQ(%d)\r\n",queueId);
            break;

        default:
            NCP_CALL(NCP_ST_ERROR);
    }

    NCP_DEV_NCA_READ_REG32(dev, NCP_REGION_NCA_AXI, offset, ((ncp_uint32_t *)&pcq_desc_r0));

    pcq_desc_r0.enable_bit = FALSE;

    NCP_DEV_NCA_WRITE_INDIRECT_REG32(dev,
                                     NCP_REGION_NCA_AXI,
                                     offset,
                                     ((ncp_uint32_t *)&pcq_desc_r0));


NCP_RETURN_LABEL
#endif
    return(ncpStatus);
}

ncp_st_t
ncp_task_v2_pcq_hw_init(
    ncp_dev_hdl_t dev,
    ncp_uint32_t pcqType,
    ncp_bool_t   enable,
    ncp_uint32_t queueId,
    ncp_uint32_t numEntries,
    ncp_uint32_t poolID,  /* copy Pool if oPCQ */
    ncp_uint64_t baseAddr,
    ncp_bool_t   domainIsInternal,
    ncp_bool_t   automaticTaskCompletion,
    ncp_uint32_t singleSegmentOnly)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
#if 0 /* UBOOT */
    ncp_nca_PCQ_desc_reg0_55xx_t pcq_desc_r0 = {0};
    ncp_nca_PCQ_desc_reg1_55xx_t pcq_desc_r1 = {0};
    ncp_nca_PCQ_desc_reg2_55xx_t pcq_desc_r2 = {0};
    ncp_nca_PCQ_desc_reg3_55xx_t pcq_desc_r3 = {0};
    ncp_uint32_t offset;


    /* find the register offset for this queue */
    switch (pcqType) {
        case NCP_TASK_PCQ_INPUT:
            offset = NCP_NCA_PCQ_DESC_IPCQ_R0_55XX(queueId);
            NCP_MSG(NCP_MSG_DEBUG, "Enable iPCQ(%d)\r\n",queueId);
            break;

        case NCP_TASK_PCQ_OUTPUT:
            offset = NCP_NCA_PCQ_DESC_OPCQ_R0_55XX(queueId);
            NCP_MSG(NCP_MSG_DEBUG, "Enable oPCQ(%d)\r\n",queueId);
            break;

        case NCP_TASK_PCQ_CONFIG:
            offset = NCP_NCA_PCQ_DESC_CPCQ_R0_55XX(queueId);
            NCP_MSG(NCP_MSG_DEBUG, "Enable cPCQ(%d)\r\n",queueId);
            break;

        default:
            NCP_CALL(NCP_ST_ERROR);
    }

    NCP_DEV_NCA_READ_REG32(dev, NCP_REGION_NCA_AXI, offset, ((ncp_uint32_t *)&pcq_desc_r0));
    NCP_DEV_NCA_READ_REG32(dev, NCP_REGION_NCA_AXI, offset+4, ((ncp_uint32_t *)&pcq_desc_r1));



    if (NCP_TASK_PCQ_INPUT == pcqType)
    {
        pcq_desc_r0.atfc = automaticTaskCompletion;
        pcq_desc_r0.cpu_single_ptr = singleSegmentOnly;
    }

    /* set up the register fields common across PCQ types */

    /*
     * FIXME - Copy pool should be configurable
     */
    pcq_desc_r0.number_of_queue_entries = numEntries;
    pcq_desc_r0.enable_bit = enable;
    pcq_desc_r0.reserved0 = 0;
    pcq_desc_r0.task_mem_sel = ((TRUE == domainIsInternal) ? 0 : 1); /* AXI == 1 */
    pcq_desc_r0.copy_pool_id = poolID;

    pcq_desc_r1.q_mem_sel = ((TRUE == domainIsInternal) ? 0 : 1); /* AXI == 1 */
    if (NCP_TASK_IS_SHARED_POOL(poolID))
    {
        ncp_uint32_t mask = (1 << poolID);
        pcq_desc_r1.cpu_allowd_pools = mask;
    }
    else
    {
        /*
         * Data copy is always required when PCQ is configured for CPU managed pool.
         */
        pcq_desc_r1.cpu_allowd_pools = 0;
    }

    pcq_desc_r1.q_pool_id = NCP_TASK_VP_CONTROL_POOL_ID;


    pcq_desc_r2.q_vi_upper
        = (ncp_uint32_t)   ((baseAddr >> 32) & (0x0000000F));    /* 4 bits */
    pcq_desc_r3.q_vi_lower
        = (ncp_uint32_t)   (baseAddr & 0xffffffff);



    NCP_DEV_NCA_WRITE_INDIRECT_REG32(dev,
                                     NCP_REGION_NCA_AXI,
                                     offset+0x4,
                                     (ncp_uint32_t *)&pcq_desc_r1);

    NCP_DEV_NCA_WRITE_INDIRECT_REG32(dev,
                                     NCP_REGION_NCA_AXI,
                                     offset+0x8,
                                     (ncp_uint32_t *)&pcq_desc_r2);

    NCP_DEV_NCA_WRITE_INDIRECT_REG32(dev,
                                     NCP_REGION_NCA_AXI,
                                     offset+0xc,
                                     (ncp_uint32_t *)&pcq_desc_r3);

    /*
     * Write R0 last since it has enable bit
     */

    NCP_DEV_NCA_WRITE_INDIRECT_REG32(dev,
                                     NCP_REGION_NCA_AXI,
                                     offset,
                                     ((ncp_uint32_t *)&pcq_desc_r0));

NCP_RETURN_LABEL
#endif
    return ncpStatus;
}

/*
 * Hw recommends setting r0 and r1 early,   and r2..r5 later in the init process
 */

ncp_st_t
ncp_task_v2_pcq_group_init_base_addresses(
    ncp_dev_hdl_t dev,
    ncp_uint32_t groupId)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
#if 0 /* UBOOT */
    ncp_uint64_t pgitBarAddr;
    ncp_uint64_t cpuPgitBarAddr;
    ncp_dev_pcq_grp_init_t pcq_grp_init = {{0}};

    if (pNcpNcaV2_TaskSwState->inUmode)
    {

        /*
         * Convert PGIT VAs to PAs suitable for programming into NCA base registers
         */

        if ((NULL == pNcpNcaV2_TaskSwState->pcq_grp[groupId].pNca_pgit) || (NULL == pNcpNcaV2_TaskSwState->pcq_grp[groupId].pCpu_pgit))
        {
            pgitBarAddr     = 0x0LL;    /* This group is not used,   go ahead and provide reasonably sane values anyway */
            cpuPgitBarAddr  = 0x0LL;    /* This group is not used,   go ahead and provide reasonably sane values anyway */

        }
        else
        {

            /*
             * Compute PGIT Phys Addrs.   These will be a VI from the pool 0 base.
             */

            pgitBarAddr
                = NCP_TASK_VA_2_PA(pNcpNcaV2_TaskSwState->pcq_grp[groupId].pNca_pgit,
                                   0);

            cpuPgitBarAddr
                = NCP_TASK_VA_2_PA(pNcpNcaV2_TaskSwState->pcq_grp[groupId].pCpu_pgit,
                                   0);

        }


        /*
         * program nca and cpu pgit base address registers with 38 bit virtual index
         */

        pcq_grp_init.r2.nca_pgit_vi_upper = (ncp_uint32_t)   ((pgitBarAddr >> 32) & (0x0000000F));    /* 4 bits */
        pcq_grp_init.r3.nca_pgit_vi_lower = (ncp_uint32_t)      ((pgitBarAddr & 0xffffffc0) >> 6);       /* 26 significant bits + lower 6 all zero */

        pcq_grp_init.r4.cpu_pgit_vi_upper = (ncp_uint32_t)  ((cpuPgitBarAddr >> 32) & (0x0000000F)); /* 4 bits */
        pcq_grp_init.r5.cpu_pgit_vi_lower = (ncp_uint32_t)  ((cpuPgitBarAddr & 0xffffffc0) >> 6);    /* 26 significant bits + lower 6 all zero */



        NCP_DEV_NCA_WRITE_INDIRECT_REG32(dev,
                           NCP_REGION_NCA_AXI,
                           NCP_NCA_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R2_55XX(groupId),
                           (ncp_uint32_t *)&pcq_grp_init.r2);

        NCP_DEV_NCA_WRITE_INDIRECT_REG32(dev,
                            NCP_REGION_NCA_AXI,
                            NCP_NCA_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R3_55XX(groupId),
                            (ncp_uint32_t *)&pcq_grp_init.r3);

        NCP_DEV_NCA_WRITE_INDIRECT_REG32(dev,
                             NCP_REGION_NCA_AXI,
                             NCP_NCA_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R4_55XX(groupId),
                             (ncp_uint32_t *)&pcq_grp_init.r4);

        NCP_DEV_NCA_WRITE_INDIRECT_REG32(dev,
                            NCP_REGION_NCA_AXI,
                            NCP_NCA_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R5_55XX(groupId),
                            (ncp_uint32_t *)&pcq_grp_init.r5);

#ifdef NCP_TASK_PRINT_BASE_ADDRESSES_AND_MAPPINGS
        NCP_MSG(NCP_MSG_INFO, "initialized PGIT base Addrs for group (%d) NCA PGIT PA=0x%llx, CPU PGIT PA = 0x%llx\n",
                    groupId,
                    (long long unsigned int)pgitBarAddr,
                    (long long unsigned int)cpuPgitBarAddr);
#endif

    }    /* uMode */

NCP_RETURN_LABEL
#endif
    return ncpStatus;
}



/*
 * Hw recommends setting r0 and r1 early,   and r2..r5 later in the init process
 */

ncp_st_t
ncp_task_v2_pcq_group_init(
    ncp_dev_hdl_t dev,
    ncp_nca_t *nca,
    int i,
    ncp_int32_t domain,
    ncp_bool_t  domainIsInternal,
    ncp_bool_t warmRestart)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
#if 0 /* UBOOT */
    ncp_dev_pcq_grp_init_t pcq_grp_init = {{0}};
#endif
    ncp_task_v2_pcq_grp_t *pPCQgrp = &pNcpNcaV2_TaskSwState->pcq_grp[i];
    ncp_uint32_t groupId = pPCQgrp->id;

    if (!warmRestart)
    {
        if ((pNcpNcaV2_TaskSwState->myDomain != 0) &&  (pNcpNcaV2_TaskSwState->myDomain != domain))
        {
            pNcpNcaV2_TaskSwState->hw.nca_pgit[groupId].ptr
             = NULL;
            goto ncp_return;
        }

        /*
         * We must program the # of queues in groups managed by the other domains,
         * so that the NCA and S/W's view of queue numbers is consistent.
         */

        /*
         * FIXME -
         * 1) for AMP,  memsel may not be same as local primary domain
         */
#if 0 /* UBOOT */
        pcq_grp_init.r0.num_out_queues            = pPCQgrp->num_oPCQs;
        pcq_grp_init.r0.num_in_queues             = pPCQgrp->num_iPCQs;
#if 0   /* FIXME */
        pcq_grp_init.r1.num_config_queues         = pPCQgrp->num_cPCQs;
#else
        pcq_grp_init.r1.num_config_queues         = 0;
#endif
        pcq_grp_init.r1.mem_sel = ((TRUE == domainIsInternal) ? 0 : 1); /* AXI == 1 */
        pcq_grp_init.r1.pool_id = NCP_TASK_VP_CONTROL_POOL_ID; /* VP Control is always in pool 0 */
        if (NCP_TASK_ENABLE_PGIT_UPLOADS)
        {
            pcq_grp_init.r1.upload_nca_pgit_en = 1;
        }
        else
        {
            pcq_grp_init.r1.upload_nca_pgit_en = 0;
        }

        NCP_DEV_NCA_WRITE_INDIRECT_REG32(dev,
                         NCP_REGION_NCA_AXI,  NCP_NCA_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R0_55XX(groupId),
                         (ncp_uint32_t *)&pcq_grp_init.r0);

        NCP_DEV_NCA_WRITE_INDIRECT_REG32(dev,
                         NCP_REGION_NCA_AXI,
                         NCP_NCA_NCA_PCQ_INIT_TABLE_GRP_PCQ_GRP_R1_55XX(groupId),
                         (ncp_uint32_t *)&pcq_grp_init.r1);
#endif

        if (pNcpNcaV2_TaskSwState->myDomain != domain)
        {
            pNcpNcaV2_TaskSwState->hw.nca_pgit[groupId].ptr
             = NULL;
            goto ncp_return;
        }


        NCP_MSG(NCP_MSG_DEBUG, "Configure Group (%d)\r\n",groupId);

        NCP_CALL(NCP_TASK_INITIALIZE_DOMAIN_OBJ_VA(pPCQgrp->ncaPgitOffset,
                                                    sizeof(ncp_dev_nca_pgit_t),
                                                    &pNcpNcaV2_TaskSwState->hw.nca_pgit[groupId].ptr,
                                                    TRUE));
        pPCQgrp->pNca_pgit = pNcpNcaV2_TaskSwState->hw.nca_pgit[groupId].ptr;


        NCP_CALL(NCP_TASK_INITIALIZE_DOMAIN_OBJ_VA(pPCQgrp->cpuPgitOffset,
                                                sizeof(ncp_dev_cpu_pgit_t),
                                                &pNcpNcaV2_TaskSwState->hw.cpu_pgit[groupId].ptr,
                                                TRUE));

        pPCQgrp->pCpu_pgit = pNcpNcaV2_TaskSwState->hw.cpu_pgit[groupId].ptr;


        /*
        * Configure NCA/CPU PGIT base addresses
        */

        NCP_CALL(ncp_task_v2_pcq_group_init_base_addresses(dev,
                                                   groupId));

        /*
         * Program those group related timers/thresholds that are not specific to a particular chip version
         */
        NCP_MSG(NCP_MSG_DEBUG, "Programing POKE LOAD/UPLOAD/etc  for grp %d, (grpId from cfg %d),  on domain %d\r\n",
                i,
                groupId = pNcpNcaV2_TaskSwState->pcq_grp[i].id,
                pNcpNcaV2_TaskSwState->myDomain);


        /*
         * Program NCA PGIT cpu load timer
         */
        NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,
                                NCP_NCA_PGIT_GRP_LOAD_TIMER_55XX(groupId),
                                pPCQgrp->pgitNormalLoadTimer);

        /*
         * Program NCA PGIT nca upload timer
         */
        if (NCP_TASK_ENABLE_PGIT_UPLOADS)
        {
            NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,
                                NCP_NCA_PGIT_GRP_UPLOAD_TIMER_55XX(groupId),
                                pPCQgrp->pgitNormalUploadTimer);
        }

        /*
         * Program Interrupt Aggregation Register
         */
        {
            ncp_nca_int_param_grp_reg_t  intAggregationReg;
            ncp_uint32_t                 *pReg32 = (ncp_uint32_t *)&intAggregationReg;

            *pReg32 = 0;
            intAggregationReg.wtask = pPCQgrp->taskArrivalsPerInterrupt;
            intAggregationReg.wtime = pPCQgrp->taskArrivalInterruptMaxDelayTime;
            NCP_DEV_NCA_WRITE_INDIRECT_REG32(dev, NCP_REGION_NCA_AXI,
                                NCP_NCA_INT_PARAM_GRP_55XX(groupId),
                                pReg32);
        }
    } /* !warmRestart */
    else
    {
        if (pNcpNcaV2_TaskSwState->myDomain != domain)
        {
            goto ncp_return;
        }
    }

#ifdef NCP_TASK_PRINT_BASE_ADDRESSES_AND_MAPPINGS
{
    ncp_raw_addr_t cpuEnd, ncaEnd;

    cpuEnd = (ncp_raw_addr_t)pNcpNcaV2_TaskSwState->hw.cpu_pgit[groupId].ptr;
    cpuEnd += sizeof(ncp_dev_cpu_pgit_t);

    ncaEnd = (ncp_raw_addr_t)pNcpNcaV2_TaskSwState->hw.nca_pgit[groupId].ptr;
    ncaEnd += sizeof(ncp_dev_nca_pgit_t);

    NCP_MSG(NCP_MSG_INFO, "initialized PGIT For group (%d) pNcpNcaV2_TaskSwState=%p, NCA uva=%p, endVA=%p, CPU uva=%p, endVA=%p\n",
                i,
                pNcpNcaV2_TaskSwState,
                pNcpNcaV2_TaskSwState->hw.nca_pgit[groupId].ptr,
                (void *)ncaEnd,
                pNcpNcaV2_TaskSwState->hw.cpu_pgit[groupId].ptr,
                (void *)cpuEnd);
}
#endif

NCP_RETURN_LABEL
    return ncpStatus;
}

ncp_st_t
ncp_task_v2_cpcq_init(
    ncp_dev_hdl_t         dev,
    ncp_uint32_t       groupId,
    ncp_uint32_t       queueId,
    ncp_uint8_t        linearQueueId,
    ncp_uint32_t       nEntries,
    ncp_uint32_t       blockSize,
    ncp_uint32_t       uMode,
    ncp_int32_t        domain,
    ncp_bool_t         domainIsInternal,
    ncp_bool_t         warmRestart)
{
    ncp_st_t              ncpStatus = NCP_ST_SUCCESS;
    ncp_task_v2_pcq_grp_t    *grp = &pNcpNcaV2_TaskSwState->pcq_grp[groupId];
    ncp_task_pcq_t        *pcq = &pNcpNcaV2_TaskSwState->cPCQs[linearQueueId];
#if 0
    ncp_uint32_t          i;
    ncp_uint64_t          bufAddr;
    ncp_task_cPCQ_entry_t *entry;
#endif


    if (!warmRestart)
    {
        if ((pNcpNcaV2_TaskSwState->myDomain != domain)
         || (pNcpNcaV2_TaskSwState->inUmode != uMode))
        {
            goto ncp_return;
        }

        NCP_CALL(NCP_TASK_INITIALIZE_DOMAIN_OBJ_VA(pcq->u.cpcq_info.cPcqOffset,
                                                          nEntries * sizeof(ncp_task_cPCQ_entry_t),
                                                          &pcq->pPCQbase,
                                                          TRUE));

        pcq->baseBusAddr = NCP_TASK_VA_2_PA(pcq->pPCQbase,
                                            0);

#if 0 /* FIXME --- get buffers offset from ase config */
        pcq->bufferCpuAddr
            = NCP_TASK_INITIALIZE_DOMAIN_OBJ_VA(pcq->u.cpcq_info.cPcqOffset);

        /* allocate space for the buffers */
        NCP_CALL(NCP_ALLOC_ALIGNED(&pcq->bufferCpuAddr,
                                          nEntries * blockSize,
                                          0x100));

        pcq->bufferBusAddr = NCP_TASK_VA_2_PA(pcq->bufferCpuAddr,
                                              0);

        /* set up the descriptor buffer pointers */
        entry = (ncp_task_cPCQ_entry_t *)pcq->pPCQbase;
        bufAddr = pcq->bufferBusAddr;
        for (i = 0; i < nEntries; i++, entry++, bufAddr += blockSize )
        {
            /* descriptor DBA is a 256-byte block address */
            entry->dataBufAddr = SWAP_32((ncp_uint32_t) (bufAddr >> 8));
        }
#endif

        pcq->nEntries           = nEntries;
        pcq->nEntriesMinusOne   = nEntries - 1;
        pcq->ncaQueueId         = linearQueueId;
        pcq->u.cpcq_info.blockSize  = blockSize;
        pcq->pProducerIdx           = &grp->pCpu_pgit->c_pIdx[queueId];
        pcq->pConsumerIdx           = &grp->pNca_pgit->c_cIdx[queueId];
        /* fixup for kernel pointers */

        NCP_CALL(ncp_task_v2_pcq_hw_init(dev,
                                        NCP_TASK_PCQ_CONFIG,
                                        TRUE,
                                        linearQueueId,
                                        nEntries,
                                        0,
                                        pcq->baseBusAddr,
                                        domainIsInternal,
                                        0,
                                        0));
   } /* !warmRestart */
   else  if (pNcpNcaV2_TaskSwState->myDomain != domain)
   {
       goto ncp_return;
   }


   pcq->u.cpcq_info.pCPCQentry = pcq->pPCQbase;


#ifdef NCP_TASK_PRINT_BASE_ADDRESSES_AND_MAPPINGS
{
    ncp_raw_addr_t endPCQ = (ncp_raw_addr_t)pcq->pPCQbase;
    endPCQ += (nEntries * sizeof(ncp_task_cPCQ_entry_t));

    NCP_MSG(NCP_MSG_INFO, "initialized CPCQ(%d) %p, ubase=%p, endVA=%p, pEntry=%p, uMode=%d\r\n",
                linearQueueId,
                pcq,
                pcq->pPCQbase,
                (void *)endPCQ,
                pcq->u.cpcq_info.pCPCQentry,
                pcq->uMode);
}
#endif

NCP_RETURN_LABEL
    return ncpStatus;
}

/*
 * Input queue init
 */

ncp_st_t
ncp_task_v2_ipcq_init(
    ncp_dev_hdl_t         dev,
    ncp_uint32_t       groupId,
    ncp_uint32_t       queueId,
    ncp_uint8_t        linearQueueId,
    ncp_uint32_t       nEntries,
    ncp_uint8_t        auto_complete,
    ncp_uint8_t        pool,
    ncp_uint32_t       uMode,
    ncp_int32_t        domain,
    ncp_bool_t         domainIsInternal,
    ncp_bool_t         warmRestart)
{
    ncp_st_t              ncpStatus = NCP_ST_SUCCESS;
    ncp_task_v2_pcq_grp_t    *pPCQgrp = &pNcpNcaV2_TaskSwState->pcq_grp[groupId];
    ncp_task_pcq_t        *pcq = &pNcpNcaV2_TaskSwState->iPCQs[linearQueueId];



    if (!warmRestart)
    {
        if ((pNcpNcaV2_TaskSwState->myDomain != domain)
         || (pNcpNcaV2_TaskSwState->inUmode != uMode))
        {
            goto ncp_return;
        }


        NCP_CALL(NCP_TASK_INITIALIZE_DOMAIN_OBJ_VA(pcq->u.ipcq_info.iPcqOffset,
                                                nEntries * sizeof(ncp_task_ncaV2_iPCQ_entry_t),
                                                &pNcpNcaV2_TaskSwState->hw.NcaInputQueues[linearQueueId].entries,
                                                TRUE));

        pcq->pPCQbase = &(pNcpNcaV2_TaskSwState->hw.NcaInputQueues[linearQueueId].entries[0]);
        pcq->baseBusAddr = NCP_TASK_VA_2_PA(pcq->pPCQbase,
                                            0);


        pcq->u.ipcq_info.ipcqConsumerIdx    = 0;
        /* assumes nEntries is a power of 2 */
        pcq->nEntries                       = nEntries;
        pcq->nEntriesMinusOne               = nEntries - 1;
        pcq->grpId                          = groupId;
        pcq->ncaQueueId  = linearQueueId;
        pcq->pConsumerIdx = &pPCQgrp->pCpu_pgit->i_cIdx[queueId];
        pcq->pProducerIdx = &pPCQgrp->pNca_pgit->i_pIdx[queueId];

        NCP_CALL(ncp_task_v2_pcq_hw_init(dev,
                                        NCP_TASK_PCQ_INPUT,
                                        TRUE,
                                        linearQueueId,
                                        nEntries,
                                        pool,
                                        pcq->baseBusAddr,
                                        domainIsInternal,
                                        ((NCP_TASK_COMPLETION_HW_AUTOMATIC
                                            == pcq->u.ipcq_info.rxTaskCompletionMode) ?
                                            1 : 0),
                                        ((FALSE == pcq->u.ipcq_info.multiSegRxOK ) ?
                                            1 : 0)));

   } /* !warmRestart */
   else  if (pNcpNcaV2_TaskSwState->myDomain != domain)
   {
       goto ncp_return;
   }

   pcq->u.ipcq_info.pIPCQentry = pcq->pPCQbase;

#ifdef NCP_TASK_PRINT_BASE_ADDRESSES_AND_MAPPINGS
{
    ncp_raw_addr_t endPCQ = (ncp_raw_addr_t)pcq->pPCQbase;
    endPCQ += (nEntries * sizeof(ncp_task_ncaV2_iPCQ_entry_t));

    NCP_MSG(NCP_MSG_INFO, "initialized IPCQ(%d) %p, ubase=%p, endVA=%p, pEntry=%p, uMode=%d, pool=%d\r\n",
                linearQueueId,
                pcq,
                pcq->pPCQbase,
                (void *)endPCQ,
                pcq->u.ipcq_info.pIPCQentry,
                pcq->uMode,
                pool);
}
#endif

NCP_RETURN_LABEL
    return ncpStatus;
}

/*
 * Output queue init
 */

ncp_st_t
ncp_task_v2_opcq_init(
    ncp_dev_hdl_t         dev,
    ncp_uint32_t       groupId,
    ncp_uint32_t       queueId,
    ncp_uint8_t        linearQueueId,
    ncp_uint32_t       nEntries,
    ncp_uint32_t       uMode,
    ncp_int32_t        domain,
    ncp_bool_t         domainIsInternal,
    ncp_bool_t         warmRestart)
{
    ncp_st_t              ncpStatus = NCP_ST_SUCCESS;
    ncp_task_v2_pcq_grp_t    *grp = &pNcpNcaV2_TaskSwState->pcq_grp[groupId];
    ncp_task_pcq_t       *pcq = &pNcpNcaV2_TaskSwState->oPCQs[linearQueueId];



    if (!warmRestart)
    {
        if ((pNcpNcaV2_TaskSwState->myDomain != domain)
         || (pNcpNcaV2_TaskSwState->inUmode != uMode))
        {
            goto ncp_return;
        }


        NCP_CALL(NCP_TASK_INITIALIZE_DOMAIN_OBJ_VA(pcq->u.opcq_info.oPcqOffset,
                                                    nEntries *  sizeof(ncp_task_ncaV2_oPCQ_entry_t),
                                                    &pNcpNcaV2_TaskSwState->hw.NcaOutputQueues[linearQueueId].entries,
                                                    TRUE));

        pcq->pPCQbase     = &(pNcpNcaV2_TaskSwState->hw.NcaOutputQueues[linearQueueId].entries[0]);
        pcq->baseBusAddr = NCP_TASK_VA_2_PA(pcq->pPCQbase,
                                            0);

        pcq->nEntries           = nEntries;
        pcq->nEntriesMinusOne   = nEntries - 1;
        pcq->grpId          = groupId;
        pcq->ncaQueueId     = linearQueueId;
        pcq->pProducerIdx   = &grp->pCpu_pgit->o_pIdx[queueId];
        pcq->pConsumerIdx   = &grp->pNca_pgit->o_cIdx[queueId];

        NCP_CALL(ncp_task_v2_pcq_hw_init(dev,
                                        NCP_TASK_PCQ_OUTPUT,
                                        TRUE,
                                        linearQueueId,
                                        nEntries,
                                        pcq->u.opcq_info.copyPool,
                                        pcq->baseBusAddr,
                                        domainIsInternal,
                                        0,
                                        0));

   } /* !warmRestart */
   else  if (pNcpNcaV2_TaskSwState->myDomain != domain)
   {
       goto ncp_return;
   }

    pcq->u.opcq_info.pOPCQentry = pcq->pPCQbase;


    /*
     * Init Aux Data
     */

    if (NULL == (pNcpNcaV2_TaskSwState->outputQueueAuxData[linearQueueId]
         = (ncp_task_ncaV2_oPCQ_aux_data_t *)
           NCP_ALLOC_CACHEABLE(nEntries * sizeof(ncp_task_ncaV2_oPCQ_aux_data_t))))
    {
        NCP_CALL(NCP_ST_NO_MEMORY);
    }
    ncp_memset(pNcpNcaV2_TaskSwState->outputQueueAuxData[linearQueueId],
               0,
              (nEntries * sizeof(ncp_task_ncaV2_oPCQ_aux_data_t)));
    pcq->u.opcq_info.pAuxWriteEntry
        = pcq->u.opcq_info.pAuxReadEntry
        = pNcpNcaV2_TaskSwState->outputQueueAuxData[linearQueueId];
    pcq->u.opcq_info.pLastAuxEntry
        = pcq->u.opcq_info.pAuxReadEntry + nEntries;
    pcq->u.opcq_info.auxEntriesAvail  = nEntries-2;

#ifdef NCP_TASK_PRINT_BASE_ADDRESSES_AND_MAPPINGS
{
    ncp_raw_addr_t endPCQ = (ncp_raw_addr_t)pcq->pPCQbase;
    endPCQ += (nEntries * sizeof(ncp_task_ncaV2_oPCQ_entry_t));

    NCP_MSG(NCP_MSG_INFO, "initialized OPCQ(%d) %p, ubase=%p, endVA=%p, pEntry=%p, uMode=%d, auxData starts @ %p\r\n",
                linearQueueId,
                pcq,
                pcq->pPCQbase,
                (void *)endPCQ,
                pcq->u.opcq_info.pOPCQentry,
                pcq->uMode,
                pNcpNcaV2_TaskSwState->outputQueueAuxData[linearQueueId]);
}
#endif

NCP_RETURN_LABEL
    return ncpStatus;
}


ncp_st_t
ncp_task_v2_set_nca_load_indexes_reg(ncp_dev_hdl_t dev,
                                 ncp_uint8_t activeGrpMask)
{
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;
    ncp_nca_npgit_load_cpu_grp_indexes_reg_55xx_t regVal32={0};

   if (pNcpNcaV2_TaskSwState->inUmode)
   {

        NCP_DEV_NCA_READ_REG32(dev,
                                NCP_REGION_NCA_AXI,
                                NCP_NCA_NPGIT_LOAD_CPU_GRP_INDEXES_55XX,
                                (ncp_uint32_t *)&regVal32);

        regVal32.load_cpu_index_grp  |= activeGrpMask;

        NCP_DEV_NCA_WRITE_INDIRECT_REG32(dev,
                                         NCP_REGION_NCA_AXI,
                                         NCP_NCA_NPGIT_LOAD_CPU_GRP_INDEXES_55XX,
                                         (ncp_uint32_t *)&regVal32);
    } /* user mode */

NCP_RETURN_LABEL
    return(ncpStatus);
}

ncp_st_t
ncp_task_v2_set_nca_config_init_reg(
     ncp_dev_hdl_t dev,
     ncp_uint8_t     itask_end_data_fill_off,
     ncp_uint8_t     cfg_ring_ack_timer_en,
     ncp_uint8_t     cpcq_en,
     ncp_uint8_t     otask_accum_en,
     ncp_uint8_t     itask_accum_en,
     ncp_uint8_t     otbp_soft_reset,
     ncp_uint8_t     mpbf_en,
     ncp_uint8_t     otbp_ext_mem_wen,
     ncp_uint8_t     cpcq_exec_disable,
     ncp_uint8_t     opcq_num_ent_per_req_m1,
     ncp_uint8_t     ota_num_beat,
     ncp_uint8_t     ita_num_beat,
     ncp_uint8_t     pgit_w_num_beat,
     ncp_uint8_t     pgit_r_num_beat)
{
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;
#if 0 /* UBOOT */
    ncp_nca_config_init_reg_55xx_t regVal32;

    if (pNcpNcaV2_TaskSwState->inUmode)
    {

        NCP_DEV_NCA_READ_REG32(dev, NCP_REGION_NCA_AXI,
                               NCP_NCA_CONFIG_INIT_55XX,
                               (ncp_uint32_t *)&regVal32);


         regVal32.itask_end_data_fill_off   = itask_end_data_fill_off;
         regVal32.cfg_ring_ack_timer_en     = cfg_ring_ack_timer_en;
         regVal32.cpcq_en                   = cpcq_en;
         regVal32.otask_accum_en            = otask_accum_en;
         regVal32.itask_accum_en            = itask_accum_en;
         regVal32.otbp_soft_reset           = otbp_soft_reset;
         regVal32.mpbf_en                   = mpbf_en;
         regVal32.otbp_ext_mem_wen          = otbp_ext_mem_wen;
         regVal32.cpcq_exec_disable         = cpcq_exec_disable;
         regVal32.opcq_num_ent_per_req_m1   = opcq_num_ent_per_req_m1;
         regVal32.ota_num_beat              = ota_num_beat;
         regVal32.ita_num_beat              = ita_num_beat;
         regVal32.pgit_w_num_beat           = pgit_w_num_beat;
         regVal32.pgit_r_num_beat           = pgit_r_num_beat;

        NCP_DEV_NCA_WRITE_INDIRECT_REG32(dev, NCP_REGION_NCA_AXI,  (ncp_uint64_t)NCP_NCA_CONFIG_INIT_55XX, (ncp_uint32_t *)&regVal32);

    } /* user mode */

NCP_RETURN_LABEL
#endif
    return(ncpStatus);
}

ncp_st_t
ncp_task_v2_set_rbp_backpressure(ncp_dev_hdl_t dev, ncp_bool_t enable, ncp_uint32_t iPCQmask, ncp_uint32_t bSizeMask)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

#if 0 /* These are ncaV1 registers.   No NcaV2 Equivalent ???? */

    ncp_uint32_t regVal32=0;

    NCP_DEV_NCA_READ_REG32(dev, NCP_REGION_NCA_AXI, NCP_NCA_RBP_ITASK_BP_EN_34XX, (ncp_uint32_t *)&regVal32);

    if (enable)
    {
        regVal32 |= iPCQmask;
    }
    else
    {
        regVal32 &= ~iPCQmask;
    }
    NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,
                            NCP_NCA_RBP_ITASK_BP_EN_34XX, regVal32);
    if (enable)
    {
        /*
         * Backpressure on selected buff sizes
         */
        NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,  NCP_NCA_RBP_ITASK_BP_INCLD_BSIZ_34XX, bSizeMask);
    }
#endif /* if 0 */


NCP_RETURN_LABEL
    return(ncpStatus);
}


/*
 * Disbale the selcted set of PCQs,   while also making sure that certain fields actually remain valid;
 * nEntries, rxpoolID, etc...,   as this is required for AMP
 */

ncp_st_t
ncp_task_v2_disable_PCQs(ncp_dev_hdl_t dev,
            ncp_bool_t primaryDomain,
            ncp_bool_t domainIsInternal)
{
    int i;
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    for (i=0; i<NCP_X7_NUM_HW_INPUT_QUEUES; i++)
    {
        int grp = pNcpNcaV2_TaskSwState->iPCQs[i].grpId;
        if ((pNcpNcaV2_TaskSwState->iPCQs[i].uMode == pNcpNcaV2_TaskSwState->inUmode)
            &&
           ((primaryDomain) || (pNcpNcaV2_TaskSwState->pcq_grp[grp].grpDomain == pNcpNcaV2_TaskSwState->myDomain)))
        {
            NCP_CALL(ncp_task_v2_pcq_disable(
                     dev,
                     NCP_TASK_PCQ_INPUT,
                     i));
        }
    }
    for (i=0; i<NCP_X7_NUM_HW_OUTPUT_QUEUES; i++)
    {
        int grp = pNcpNcaV2_TaskSwState->oPCQs[i].grpId; /* same # for all q-types below */
        if ((pNcpNcaV2_TaskSwState->iPCQs[i].uMode == pNcpNcaV2_TaskSwState->inUmode)
            &&
            ((primaryDomain) || (pNcpNcaV2_TaskSwState->pcq_grp[grp].grpDomain == pNcpNcaV2_TaskSwState->myDomain)))
        {
           NCP_CALL(ncp_task_v2_pcq_disable(
                    dev,
                    NCP_TASK_PCQ_OUTPUT,
                    i));

           NCP_CALL(ncp_task_v2_pcq_disable(
                    dev,
                    NCP_TASK_PCQ_CONFIG,
                    i));

        }  /* in group managed by this domain */
    } /* for */

NCP_RETURN_LABEL
    return(ncpStatus);
}


ncp_st_t
ncp_task_v2_read_rbp_depths(ncp_dev_hdl_t dev, int rbpoolID, ncp_uint32_t *pDepth_sz0,
        ncp_uint32_t *pDepth_sz1, ncp_uint32_t *pDepth_sz2, ncp_uint32_t *pDepth_sz3)
{
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;
#if 0 /* UBOOT */
    ncp_uint32_t u32Val0, u32Val1;
    ncp_nca_rbp_depths_reg0_34xx_t *reg0 = (ncp_nca_rbp_depths_reg0_34xx_t *)&u32Val0;
    ncp_nca_rbp_depths_reg1_34xx_t *reg1 = (ncp_nca_rbp_depths_reg1_34xx_t *)&u32Val1;

    NCP_DEV_NCA_READ_REG32(dev,
                    NCP_REGION_NCA_AXI,
                    NCP_NCA_RBP_DEPTHS_34XX_R0_34XX(rbpoolID),
                    (ncp_uint32_t *)&u32Val0);

    NCP_DEV_NCA_READ_REG32(dev,
                    NCP_REGION_NCA_AXI,
                    NCP_NCA_RBP_DEPTHS_34XX_R1_34XX(rbpoolID),
                    (ncp_uint32_t *)&u32Val1);

    *pDepth_sz0 = reg0->rbp_depth_size0;
    *pDepth_sz1 = reg0->rbp_depth_size1;
    *pDepth_sz2 = reg1->rbp_depth_size2;
    *pDepth_sz3 = reg1->rbp_depth_size3;

NCP_RETURN_LABEL
#endif
    return(ncpStatus);
}

/* FIXME - TEMPORARILY DISABLED FOR 55XX */
#if (0) && ((!defined(NCP_KERNEL) || defined(NCP_VXWORKS)) && !defined(NCP_DEV_FBRS))

/*
 * ncp_task_v2_raw_rx_and_completion(ncp_pvt_task_hdl_t *taskHdl,
 *                       ncp_task_pcq_t  *p_iPCQ)
 *
 * Task a incoming task off the iPCQ and perform a automatic task comkpletion.
 *
 * WARNING - This function must not be called in normal mode - it makes assumptions
 * based on being in warm restart!
 *
 */

ncp_st_t
ncp_task_v2_raw_rx_and_completion( ncp_pvt_task_hdl_t *taskHdl,
                    ncp_task_pcq_t  *p_iPCQ)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_ncaV2_iPCQ_entry_t *pInputQueueEntry;
    ncp_uint16_t          consumerVal;
    ncp_uint16_t          nEntries          = p_iPCQ->nEntries;
    ncp_task_pcq_t       *savTask_tPCQ;
    ncp_task_pcq_t       *savTask_oPCQ;
    ncp_task_ncaV2_iPCQ_entry_t *pIPCQentry;
    int bufferId;
    ncp_task_recv_buf_t         *pTask;


    if (FALSE == p_iPCQ->uMode)
    {
        pIPCQentry = (ncp_task_ncaV2_iPCQ_entry_t *) NCP_TASK_KVA_TO_UVA((p_iPCQ->u.ipcq_info.pIPCQentry));
    }
    else
    {
        pIPCQentry = p_iPCQ->u.ipcq_info.pIPCQentry;
    }

    pInputQueueEntry = pIPCQentry;
    consumerVal = pInputQueueEntry - ((ncp_task_ncaV2_iPCQ_entry_t *)p_iPCQ->pPCQbase);/* Must calulate this way! */
                                                                                    /* Consumer idx updated every 16 */
    /* FIXME - do not read producer pointer - instead read pointer in entry */
    if (SWAP_16(*(p_iPCQ->pProducerIdx)) != (consumerVal))
    {
        /* input Task(s) exist */

        NCP_DEV_IPCQ_ENTRY_GET(pInputQueueEntry, pInputQueueEntry);

        /*
         * Convert bufferId to Virtual address
         * CAREFUL - if this is a queue owned by the kernel then the VA will be a kernel VA
         * and we will have to convert it to a user mode VA.
         */


        /*
         * prevent speculative execution of following instructions.
         * if pInputQueueEntry is read speculatively it may have
         * stale data!
         */
        NCP_ISYNC_BARRIER();


        /* Note: NCA does ignore lower 3  bits */
        bufferId = (pInputQueueEntry->bufferId / 8);/* Note: NCA does ignore lower 3  bits */

        if (FALSE == p_iPCQ->uMode)
        {
            pTask = pNcpNcaV2_TaskSwState->k_pool_buffIdMap[bufferId];
            pTask = (ncp_task_recv_buf_t *) NCP_TASK_KVA_TO_UVA(pTask);
        }
        else
        {
            pTask = pNcpNcaV2_TaskSwState->NCA_BUFFID_MAP[bufferId];
        }

        NCP_DEV_RECV_BUFFER_HDR_GET(pTask, pTask);

        /*
         * Consume the entry
         */


        if (nEntries == (++consumerVal))
        {
            consumerVal = 0;
            pIPCQentry
                = pInputQueueEntry
                = (ncp_task_ncaV2_iPCQ_entry_t *)(p_iPCQ->pPCQbase);
        }
        else
        {
            pIPCQentry = ++pInputQueueEntry;
        }

        /* update consumer index immediately! no need for optimizations here */
        *(p_iPCQ->pConsumerIdx) = SWAP_16(consumerVal);


        /*
         * Now complete the task,  regardless of whether the queue was configured for
         * automatic completions or not! Note that we must temporarily alter the send and completion queues
         * since they may point to a s/w queue. (depracated)
         */

        savTask_tPCQ = taskHdl->completionQueue;
        savTask_oPCQ = taskHdl->sendQueue;
        taskHdl->sendQueue       = taskHdl->pThreadQueueSet->p_oPCQ;
#if 0
	    NCP_MSG(NCP_MSG_INFO, "in raw loopback: complete task %p (bufferId=%d), new P/C=%d/%d\r\n",
	            pTask, bufferId, (SWAP_16(*(p_iPCQ->pProducerIdx))), consumerVal);
#endif

        NCP_CALL(NCP_NCA_LOWLEVEL_TASK_COMPLETION(taskHdl, pTask));

        taskHdl->completionQueue    = savTask_tPCQ; /* restore original tPCQ */
        taskHdl->sendQueue          = savTask_oPCQ; /* restore original oPCQ */

#ifdef NCP_TASK_DBG_BUFFERS
        ncp_task_v2_del_onNca(pTask, taskHdl->poolID);
#endif

        /* ncp_task_v2_CpuPool_free(pTask); */ /* No need to free dma capable buffers in warm restart, we reinit pool */

    }  /* queue not empty */
    else
    {
        ncpStatus = NCP_ST_TASK_RECV_QUEUE_EMPTY;
    }
NCP_RETURN_LABEL


    if (FALSE == p_iPCQ->uMode)
    {
        p_iPCQ->u.ipcq_info.pIPCQentry =  (ncp_task_ncaV2_iPCQ_entry_t *)NCP_TASK_UVA_TO_KVA(pIPCQentry);
    }
    else
    {
        p_iPCQ->u.ipcq_info.pIPCQentry = pIPCQentry;
    }


    return(ncpStatus);
}

/* used in warm restart */
ncp_st_t
ncp_task_v2_warm_restart_drain_rxQ(ncp_hdl_t ncpHdl, int thisIPCQ, int tqsId)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_pcq_t  *p_iPCQ;
    ncp_pvt_task_hdl_t *taskHdl=NULL;


    NCP_CALL(ncp_task_hdl_create(
        ncpHdl,
        tqsId,
        FALSE,
        FALSE,
        (ncp_task_hdl_t *)&taskHdl));

    NCP_CALL(ncp_task_v2_map_queuenum_to_pcq(NCP_TASK_PCQ_INPUT, thisIPCQ, &p_iPCQ));

    /*
     * Drain S/W or NCA iPCQ, issuing task completions as we go
     */

    do
    {
        if (NCP_ST_SUCCESS != (ncpStatus = ncp_task_v2_raw_rx_and_completion( taskHdl, p_iPCQ)))

        {
            if (NCP_ST_TASK_RECV_QUEUE_EMPTY == ncpStatus)
            {
                break; /* get out,   queue has been drained */
            }
            else
            {
                NCP_CALL(ncpStatus);
            }
        }

    } while(1);



NCP_RETURN_LABEL

    if (taskHdl)
    {
        ncp_task_hdl_remove(taskHdl);
    }
    return(ncpStatus);

}




/* used in warm restart */
ncp_st_t
ncp_task_v2_warm_restart_loopback(ncp_hdl_t ncpHdl, ncp_dev_hdl_t dev, ncp_nca_t *nca, int rbpoolID, int firstIPCQ, int tqsId)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_task_pcq_t  *p_iPCQ;
    ncp_vp_hdl_t vpHdl;
    ncp_task_send_meta_t metaData;
    ncp_pvt_task_hdl_t *taskHdl=NULL;
    ncp_uint8_t engineSeqId;
    ncp_bool_t poolDrained = FALSE;
    ncp_bool_t restoreAuxPtrs = FALSE;

    NCP_MSG(NCP_MSG_DEBUG, "Enter warm restart loopback, pool=%d\r\n",rbpoolID);

    NCP_CALL(ncp_task_hdl_create(
        ncpHdl,
        tqsId,
        FALSE,
        FALSE,
        (ncp_task_hdl_t *)&taskHdl));



    /*
     * Get vpHdl
     * Note: no rxq or vp binds are necessary since we are doing raw receives
     */
    if (NCP_ST_SUCCESS !=
        ncp_vp_handle_get_by_name(ncpHdl,
                                  ncp_launch_engine_cpu,
                                  "NCA_WARM_RESTART",
                                  &vpHdl))
    {
        NCP_CALL(NCP_ST_TASK_NO_WARM_RESTART_VP);
    }

    ncp_vp_engine_seq_id_get(vpHdl, NULL, &engineSeqId);

    NCP_CALL(ncp_task_v2_map_queuenum_to_pcq(NCP_TASK_PCQ_INPUT, firstIPCQ, &p_iPCQ));

    /*
     * Drain NCA iPCQ, issuing task completions as we go
     */
    NCP_MSG(NCP_MSG_DEBUG, "restart loopback, drain iPCQ=%p\r\n",p_iPCQ);
    do
    {
        if (NCP_ST_SUCCESS != (ncpStatus = ncp_task_v2_raw_rx_and_completion( taskHdl, p_iPCQ)))

        {
            if (NCP_ST_TASK_RECV_QUEUE_EMPTY == ncpStatus)
            {
                break; /* get out,   queue has been drained */
            }
            else
            {
                NCP_CALL(ncpStatus);
            }
        }

    } while(1);


    ncp_memset(&metaData, 0, sizeof(ncp_task_send_meta_t));


    /* Initialize task meta data */
    metaData.taskParms[0] = firstIPCQ; /* Target send to iPCQ associated with the rx buff pool we are draining */

    /*
     * If TQS is kernel mode,  then we must temporarily change the kernel ptrs to user mode ptrs
     */
    if (FALSE == taskHdl->pThreadQueueSet->p_oPCQ->uMode)
    {
        /*
         * loop through each entry and set it's pointer to
         * it's aux data structure.
         */
        int                      e;
        int                      nEntries = taskHdl->pThreadQueueSet->p_oPCQ->nEntries;
        ncp_task_ncaV2_oPCQ_entry_t    *pQentry
                = (ncp_task_ncaV2_oPCQ_entry_t *) taskHdl->pThreadQueueSet->p_oPCQ->pPCQbase;

        for (e = 0; e < nEntries; e++, pQentry++)
        {
            pQentry->auxData = NCP_TASK_KVA_TO_UVA(pQentry->auxData);
        }
        restoreAuxPtrs = TRUE;
    }

    /* send and receive until rbp is empty */
    do
    {
        ncp_uint32_t depth_sz0;
        ncp_uint32_t depth_sz1;
        ncp_uint32_t depth_sz2;
        ncp_uint32_t depth_sz3;

        ncp_task_v2_read_rbp_depths(dev,
                                 rbpoolID,
                                 &depth_sz0,
                                 &depth_sz1,
                                 &depth_sz2,
                                 &depth_sz3);


        if ((0 == depth_sz0)
         && (0 == depth_sz1)
         && (0 == depth_sz2)
         && (0 == depth_sz3))
        {
            NCP_MSG(NCP_MSG_DEBUG, "pool appears to be drained\r\n");
            poolDrained = TRUE;
        }

        if (FALSE == poolDrained)
        {
            do
            {
                ncpStatus = ncp_task_send(taskHdl,
                                    vpHdl,
                                    &metaData,
                                    NULL,
                                    NULL,
                                    FALSE,
                                    NULL,
                                    NULL);
                if (NCP_ST_SUCCESS == ncpStatus)
                {
                    break;
                }
                else if (NCP_ST_TASK_SEND_QUEUE_FULL != ncpStatus)
                {
                    NCP_CALL(ncpStatus);
                }
            } while(1);
        }

        /* Make sure final NCA upload has occured */
        if (poolDrained)
        {
            ncp_sys_usleep(1000000);
        }

        do
        {
            if (NCP_ST_SUCCESS != (ncpStatus = ncp_task_v2_raw_rx_and_completion( taskHdl, p_iPCQ)))
            {
                if (NCP_ST_TASK_RECV_QUEUE_EMPTY == ncpStatus)
                {
                    ncpStatus = NCP_ST_SUCCESS;
                    break;
                }
                else
                {
                    NCP_CALL(ncpStatus);
                }
            }
        } while(1);

        if (poolDrained)
        {
            NCP_MSG(NCP_MSG_DEBUG, "exiting warm restart loopback\r\n");
            break;
        }
    } while(1);

#ifdef NCP_TASK_DBG_BUFFERS
    /*
     * If pool is really drained,  then the onNca list should be empty
     */
    {
        int onNcaIndex;
        for (onNcaIndex=0; onNcaIndex<NCP_TASK_NCA_RXPOOL_DEPTH; onNcaIndex++)
        {
            if (0 != pNcpNcaV2_TaskSwState->onNcaList[onNcaIndex])
            {
                ncp_task_v2_breakpoint(7);
            }
        }
    }
#endif

NCP_RETURN_LABEL

    if (taskHdl)
    {

        if (restoreAuxPtrs)
        {
            /*
             * loop through each entry and restore its KMODE pointer
             */
            int                      e;
            int                      nEntries = taskHdl->pThreadQueueSet->p_oPCQ->nEntries;
            ncp_task_ncaV2_oPCQ_entry_t    *pQentry
                    = (ncp_task_ncaV2_oPCQ_entry_t *) taskHdl->pThreadQueueSet->p_oPCQ->pPCQbase;
            for (e = 0; e < nEntries; e++, pQentry++)
            {
                pQentry->auxData = NCP_TASK_UVA_TO_KVA(pQentry->auxData);
            }
        }

        /*
         * Note: since we perform warm restart in user mode,  ncp_task_hdl_create
         * just clobbered our pcq entry poionter.   We'll restore it now.
         */

        if (FALSE == taskHdl->sendQueue->uMode)
        {
            /*
             * Restore OPCQ
             */
            taskHdl->sendQueue->u.opcq_info.pOPCQentry
                    = taskHdl->sendQueue->pPCQbase;

            taskHdl->sendQueue->u.opcq_info.pOPCQentry
                += NCP_DEV_NCA_PCQ_PRODUCER_IDX(taskHdl->sendQueue);

        }
        ncp_task_hdl_remove(taskHdl);
    }
    return(ncpStatus);

}

/* used in warm restart */
ncp_st_t
ncp_task_v2_drain_rbpool(ncp_hdl_t ncpHdl, ncp_dev_hdl_t dev, ncp_nca_t *nca, int rbpoolID)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    int firstIPCQ=0;
    int tqsId = -1;
    int i;

    /*
     * Find first iPCQ associated with this rbp
     */
    NCP_MSG(NCP_MSG_DEBUG, "enter ncp_task_v2_drain_rbpool poolId=%d\r\n", rbpoolID);
    for (i=0; i<NCP_X7_NUM_HW_INPUT_QUEUES; i++)
    {
        if (pNcpNcaV2_TaskSwState->mempool_cfg[rbpoolID].rbp_iPCQmask & (1<<i))
        {
            firstIPCQ = i;
            break;
        }
    }
    NCP_ASSERT((NCP_X7_NUM_HW_INPUT_QUEUES != i), NCP_ST_TASK_NO_IPCQ_FOR_RXB_POOL_IN_WARM_RESTART);

    /*
     * What thread queueset contains this rPCQ?
     */
    for(i=0; i < NCP_X7_NUM_THREAD_QUEUESETS; i++)
    {
        if ((firstIPCQ >= pNcpNcaV2_TaskSwState->threadQueueSets[i].first_iPCQ_id)
            && (firstIPCQ < (pNcpNcaV2_TaskSwState->threadQueueSets[i].first_iPCQ_id+pNcpNcaV2_TaskSwState->threadQueueSets[i].num_iPCQs_in_queueSet)))
        {
            tqsId = i;
            break;
        }
    }
    NCP_ASSERT((NCP_X7_NUM_HW_INPUT_QUEUES != i), NCP_ST_TASK_NO_IPCQ_FOR_RXB_POOL_IN_WARM_RESTART);

    NCP_CALL(ncp_task_v2_warm_restart_loopback(ncpHdl,
                                                dev,
                                                nca,
                                                rbpoolID,
                                                firstIPCQ,
                                                tqsId));


NCP_RETURN_LABEL

    return(ncpStatus);
}

/*
 * ncp_task_v2_nca_warm_restart(ncp_hdl_t ncpHdl,
 *                       ncp_dev_hdl_t dev,
 *                       ncp_nca_t *nca)
 *
 * Perform NCA Cleanup in preparation for warm restart.
 * We must examine the NCA/TaskIO state from the previous
 * execution instance.
 */

ncp_st_t
ncp_task_v2_nca_warm_restart(ncp_hdl_t ncpHdl,
                         ncp_dev_hdl_t dev,
                         ncp_nca_t *nca)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_pvt_task_hdl_t *myTaskHdl = NULL;
    ncp_uint32_t regConfigInitVal;
    ncp_nca_config_init_reg_55xx_t *pNca_ConfigInitReg
        = (ncp_nca_config_init_reg_55xx_t *)&regConfigInitVal;
    int i;
    int j;
    ncp_uint8_t tqsId;
    ncp_dev_gsm_info_t save_GSMinfo;

#if defined(NCP_DEV_SOCKET)
    NCP_CALL(NCP_ST_TASK_WARM_RESTART_UNSUPPORTED_PLATFORM)
#endif


    /*
     * ===================================================================================
     * Is NCA currently enabled?
     * If task accumulator is enabled,   then we have a previous successful config.
     * ===================================================================================
     */
    NCP_DEV_NCA_READ_REG32(dev,
                            NCP_REGION_NCA_AXI,
                            NCP_NCA_CONFIG_INIT_55XX,
                            (ncp_uint32_t *)&regConfigInitVal);

    if (0 == pNca_ConfigInitReg->itask_accum_en)
    {
        NCP_CALL(NCP_ST_NOT_CONFIGURED);
    }

    /*
     * ===================================================================================
     * Gain access to shared memory
     * ===================================================================================
     */

    NCP_CALL(ncp_task_attach_to_gsm(ncpHdl, (void **)(&pNcpNcaV2_domainBundle), (void **)(&pNcpNcaV2_TaskSwState)));


    /*
     * ==================================================================================
     * We need a view of the old mappings,   so temporarily restore them after saving
     * the current values
     * ==================================================================================
     */

     memcpy((void *)(&save_GSMinfo),
            (void *)(&pNcpNcaV2_TaskSwState->myGSMinfo),
            sizeof(ncp_dev_gsm_info_t));

     memcpy((void *)(&pNcpNcaV2_TaskSwState->myGSMinfo),
            (void *)(&pNcpNcaV2_TaskSwState->warmRestart_GSMinfo),
            sizeof(ncp_dev_gsm_info_t));


    pNcpNcaV2_TaskSwState->inWarmRestart   = TRUE;
    pNcpNcaV2_TaskSwState->shutdown        = FALSE;

    /*
     * ===================================================================================
     * Allocate and initialize locks used during warm restart
     * ===================================================================================
     */

#ifdef NCP_TASK_DBG_NVM_CORRUPTION
    if (NULL == pNcpNcaV2_TaskSwState->nvm_dbgLock)
    {
        pNcpNcaV2_TaskSwState->nvm_dbgLock = ncp_nvm_malloc(sizeof(ncp_task_mutex_t));
    }
    ncp_memset(pNcpNcaV2_TaskSwState->nvm_dbgLock, 0, sizeof(ncp_task_mutex_t));
    NCP_TASK_INIT_LOCK(pNcpNcaV2_TaskSwState->nvm_dbgLock, 1, 1);
#endif

    if (NULL == pNcpNcaV2_TaskSwState->taskIoResourceLock)
    {
        pNcpNcaV2_TaskSwState->taskIoResourceLock = ncp_nvm_malloc(sizeof(ncp_task_mutex_t));
    }
    ncp_memset(pNcpNcaV2_TaskSwState->taskIoResourceLock,
            0,
            sizeof(ncp_task_mutex_t));
    NCP_TASK_INIT_LOCK(pNcpNcaV2_TaskSwState->taskIoResourceLock, 1, 1);


    /*
     * ===================================================================================
     * Before we do anything else,   make sure we are in a consistent state!
     * Run task handles and check that none were in the middle of a critical section.
     * ===================================================================================
     */

    {
        myTaskHdl = pNcpNcaV2_TaskSwState->activeTaskHdlList;
        while(myTaskHdl)
        {
            if ((NCP_TASK_HDL_COOKIE != myTaskHdl->cookie)
             || (myTaskHdl->inCriticalSection))
            {
                NCP_CALL(NCP_ST_STATE_INCONSISTENT);
            }
            myTaskHdl                   = myTaskHdl->next;
        }
    }



    /*
     * ===================================================================================
     * Run the list of task handles,   processing queues, and releasing the
     * task handle!   We need to do this
     * before draining the NCA internal rx buffer pool in order to be sure that all
     * queue and queueset bindings are released.
     * ===================================================================================
     */

    {


        myTaskHdl = pNcpNcaV2_TaskSwState->activeTaskHdlList;
        ncp_pvt_task_hdl_t *myTmpTaskHdl = pNcpNcaV2_TaskSwState->activeTaskHdlList;


        while(myTaskHdl)
        {
            ncp_nca_thread_queue_set_t *pThreadQueueSet;

            if (NULL == (pThreadQueueSet = myTaskHdl->pThreadQueueSet))
            {
                break;
            }

            /*
             * Handle any pending manual completions owed for shared and exclusive rxQueues
             */
            {
                ncp_task_man_completion_list_element_t *curr = myTaskHdl->firstManCompletion;


                while(NULL != curr)
                {
                    curr = curr->next;
                    NCP_NCA_LOWLEVEL_TASK_COMPLETION(myTaskHdl, curr->task);
                    ncp_nvm_free(curr);
                }
            }

            /*
             * Now handle completions for tasks sitting on input PCQs.
             * Do recv queues exist for this task handle
             */
            {
                ncp_task_pcq_t      *taskPCQ;
                ncp_pvt_task_recv_queue_t *first, *recvQueuePtr;
                nncp_task_ncaV2_recv_buf_t *pSwAutoTaskCompletionTask;

                if (NULL != (first = recvQueuePtr = (myTaskHdl->currRecvPtr)))
                {
                    do {


                        taskPCQ = recvQueuePtr->taskQueue;

                        /*
                         * Handle delayed completion
                         */

                        if ((taskPCQ->u.ipcq_info.taskCompletionInfo.reserved)
                                && (NCP_TASK_COMPLETION_SW_AUTOMATIC == taskPCQ->u.ipcq_info.rxTaskCompletionMode))
                        {
                            /* FIXME if support is really required in 55xx */
                            NCP_CALL(NCP_ST_NOT_IMPLEMENTED);

                        } /* delayed completion for cached auto complete iPCQ info */

                        do
                        {
                            if (NCP_ST_SUCCESS !=
                                (ncpStatus = ncp_task_v2_raw_rx_and_completion(myTaskHdl, taskPCQ)))

                            {
                                if (NCP_ST_TASK_RECV_QUEUE_EMPTY == ncpStatus)
                                {
                                    break; /* get out,   queue has been drained */
                                }
                                else
                                {
                                    NCP_CALL(ncpStatus);
                                }
                            }

                        } while (1); /* processing all queued input tasks */

                        ncp_task_recv_queue_unbind(myTaskHdl, recvQueuePtr->recvQueueId);

                        recvQueuePtr = myTaskHdl->currRecvPtr;

                    } while(recvQueuePtr && (first != recvQueuePtr));

                } /* recv queues exist */

            } /* iPCQ handling */

            myTmpTaskHdl = myTaskHdl;
            myTaskHdl = myTaskHdl->next;

            /*
             * Free the task handle,   and associated resources
             */

            ncp_task_hdl_remove(myTmpTaskHdl);

        } /* while myTaskHdl */
    }

    /*
     * ===================================================================================
     * Drain the rxBuffer Pool(s).
     * (1) Turn off NCA backpressure
     * (2) Send loopback tasks though NCA_WARM_RESTART VP until rxPool is depleted.
     * Note: we must actually process these loopback tasks,   issuing completions,
     * and advancing the consumer PCQ idx,   but not replenishing the buffer pool.
     * --- WARNING --- must handle both user and kernel mode pools and iPCQs
     * ===================================================================================
     */

    for (i = 0; i < NCP_X7_NUM_TASK_MEMORY_POOLS; i++)
    {

        if ((0xff == pNcpNcaV2_TaskSwState->mempool_cfg[i].id)
         || (pNcpNcaV2_TaskSwState->myDomain
             != pNcpNcaV2_TaskSwState->mempool_cfg[i].taskMemPoolDomain))
        {
            NCP_MSG(NCP_MSG_DEBUG, "warm restart - skipping pool=%d\r\n", i);
            continue;
        }
        NCP_MSG(NCP_MSG_DEBUG, "warm restart - prepare to drain rbool=%d\r\n", i);

        NCP_CALL(ncp_task_v2_set_rbp_backpressure(dev,
            FALSE,
            pNcpNcaV2_TaskSwState->mempool_cfg[i].rbp_iPCQmask,
            0x8));

        NCP_CALL(ncp_task_v2_drain_rbpool(ncpHdl,
            dev,
            nca,
            pNcpNcaV2_TaskSwState->mempool_cfg[i].id));
     }



    /*
     * ===================================================================================
     * ReRun list of NCA inputPCQs,  and issue completions for unprocessed tasks
     * ===================================================================================
     */

    for (i = 0; i < NCP_X7_NUM_THREAD_QUEUESETS; i++)
    {
        ncp_nca_thread_queue_set_t *pThreadQueueSet = &pNcpNcaV2_TaskSwState->threadQueueSets[i];
        int k;

        if ((pThreadQueueSet->tqsDomain != pNcpNcaV2_TaskSwState->myDomain) || (0xFF == pThreadQueueSet->id))  /* unused ? */
        {
            continue;
        }

        k = pThreadQueueSet->num_iPCQs_in_queueSet;
        for (j = pThreadQueueSet->first_iPCQ_id; j < k; j++)
        {
             if (NCP_ST_SUCCESS != (ncp_task_v2_warm_restart_drain_rxQ(ncpHdl, j, pThreadQueueSet->id)))
             {
                if (NCP_ST_TASK_RECV_QUEUE_EMPTY == ncpStatus)
                {
                    break; /* get out,   queue has been drained */
                }
                else
                {
                    NCP_CALL(ncpStatus);
                }
            }
        }
     }




    /*
     * ===================================================================================
     * Clean up Hardware and software queue/pipeline bind tables.
     * ===================================================================================
     */

    for (i=0; i < NCP_X7_NUM_HW_INPUT_QUEUES; i++)
    {
        ncp_recv_queue_level1_bind_wrapper_t* pBindTableEntry;

        if (NULL !=
            (pBindTableEntry = pNcpNcaV2_TaskSwState->ncaQueueToPipelineBindings[i]))
        {
            pNcpNcaV2_TaskSwState->ncaQueueToPipelineBindings[i] = NULL;

            /*
             * Now its safe to free the level 1 bind table
             */
            ncp_nvm_free(pBindTableEntry);
        } /* for */
    }


    /*
     * ===================================================================================
     * Make sure all output-type PCQs are in empty state
     * ===================================================================================
     */

    for (i = 0; i < NCP_X7_NUM_THREAD_QUEUESETS; i++)
    {

        ncp_nca_thread_queue_set_t *pThreadQueueSet = &pNcpNcaV2_TaskSwState->threadQueueSets[i];
        ncp_task_pcq_t  *ncaQ;
        int k;

        if ((0xFF == pThreadQueueSet->id) || (pThreadQueueSet->tqsDomain != pNcpNcaV2_TaskSwState->myDomain))  /* unused ? */
        {
            continue;
        }

        for (k=0; k<2; k++)
        {
            ncaQ =  pThreadQueueSet->p_oPCQ;
            if (NCP_DEV_NCA_PCQ_IS_EMPTY(ncaQ))
            {
                break;
            }
            ncp_sys_usleep(1000);
        }
        if (2 == k)
        {
            NCP_CALL(NCP_ST_TASK_QUEUE_STUCK_IN_WARM_RESTART);
        }

        for (k=0; k<2; k++)
        {
            ncaQ =  pThreadQueueSet->p_cPCQ;
            if (NCP_DEV_NCA_PCQ_IS_EMPTY(ncaQ))
            {
                break;
            }
            ncp_sys_usleep(1000);
        }
        if (2 == k)
        {
            NCP_CALL(NCP_ST_TASK_QUEUE_STUCK_IN_WARM_RESTART);
        }
     }

    /*
     * If we made it to this point,   then we have successully cleaned up the previous boot instance,
     * so reconfig the hardware  as if this were a fresh config.
     *
     * Restore our mmap info to account for possibly
     * new kernel PA/VA mappings.
     */
    memcpy((void *)(&pNcpNcaV2_TaskSwState->myGSMinfo),
            (void *)(&save_GSMinfo),
            sizeof(ncp_dev_gsm_info_t));

    NCP_CALL(ncp_task_v2_config_hw(ncpHdl, dev, nca, TRUE));



    /*
     * Create default config-time taskHdl so that other engines may send tasks as part of their
     * config-time init.   This will be release at config exit.  Ignore Errors!
     */
    NCP_CALL(ncp_task_get_default_queueset((ncp_hdl_t)ncpHdl,
                                            &tqsId));

    NCP_CALL(ncp_task_hdl_create((ncp_hdl_t)ncpHdl,
                                 tqsId,
                                 FALSE,
                                 FALSE,
                                 (ncp_task_hdl_t)&myTaskHdl));


NCP_RETURN_LABEL
    return(ncpStatus);

}


ncp_st_t
ncp_task_v2_warm_config(ncp_t         *ncp,
                    ncp_map_t     *map)
{
    ncp_st_t         ncpStatus = NCP_ST_SUCCESS;
    ncp_nca_t        *nca = (ncp_nca_t *)ncp->ncaHdl;
    ncp_dev_hdl_t    devHdl = ncp_dev_hdls[ncp->id];

#if defined(NCP_KERNEL) && !defined(NCP_VXWORKS)

    NCP_CALL(NCP_ST_NOT_IMPLEMENTED);

#elif defined(NCP_DEV_FBRS)

    NCP_CALL(NCP_ST_SUCCESS);

#else

    if (nca == NULL)
    {
        NCP_CALL(NCP_ST_NOT_CONFIGURED);
    }

    if (nca->cookie != NCP_TASK_STATE_COOKIE)
    {
        NCP_CALL(NCP_ST_STATE_INCONSISTENT);
    }

    NCP_CALL(ncp_task_v2_nca_warm_restart((ncp_hdl_t)ncp,
                                        devHdl,
                                        nca));

    /* Initialize alarm handler */
    NCP_CALL(ncp_nca_alarm_handler_register((ncp_hdl_t)ncp));

#endif
NCP_RETURN_LABEL
    return(ncpStatus);
}

#endif /* (!defined(NCP_KERNEL) || defined(NCP_VXWORKS)) && !defined(NCP_DEV_FBRS) */ /* FIXME - TEMPORARILY DISABLED FOR 55XX */


/* FIXME - must unmap both the domain bundle and the in-use Task Memory Pool */
ncp_st_t
ncp_task_v2_config_free(ncp_nca_t *nca)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

#if !defined(NCP_DEV_SOCKET) && (!defined(NCP_KERNEL) || defined(NCP_VXWORKS))
    if (0 != (ncp_raw_addr_t)pNcpNcaV2_TaskSwState)
    {
        if (pNcpNcaV2_domainBundle)
        {
            munmap((void *)
                   pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_VA,
                   pNcpNcaV2_TaskSwState->domainMemMap.domainBundle_Size);
            pNcpNcaV2_domainBundle = NULL; /* Clear process local global */
        }

#ifdef DBG_NBM_CORRUPTION
        if (pNcpNcaV2_TaskSwState->nvm_dbgLock)
        {
            NCP_TASK_DESTROY_LOCK(pNcpNcaV2_TaskSwState->nvm_dbgLock);
            ncp_nvm_free(pNcpNcaV2_TaskSwState->nvm_dbgLock);
            pNcpNcaV2_TaskSwState->nvm_dbgLock = NULL;
        }
#endif
        if (pNcpNcaV2_TaskSwState->taskIoResourceLock)
        {
            NCP_TASK_DESTROY_LOCK(pNcpNcaV2_TaskSwState->taskIoResourceLock);
            ncp_nvm_free(pNcpNcaV2_TaskSwState->taskIoResourceLock);
            pNcpNcaV2_TaskSwState->taskIoResourceLock = NULL;
        }

        /*
         * FIXME - memory leak here - must deallocate all structs previously allocated out of NVM
         */

        pNcpNcaV2_TaskSwState = NULL;
    }

    if (nca)
    {
        ncp_nvm_free(nca);
    }
#endif

    return(ncpStatus);
}


ncp_st_t
ncp_task_v2_destroy(ncp_t *ncp)
{
    ncp_st_t        ncpStatus = NCP_ST_SUCCESS;
    ncp_nca_t       *nca = (ncp_nca_t *)ncp->ncaHdl;

    if (nca == NULL)
    {
        return NCP_ST_SUCCESS;
    }

    if (nca->cookie != NCP_TASK_STATE_COOKIE)
    {
        NCP_CALL(NCP_ST_TASK_NCP_DESTROY_HANDLE_INVALID);
    }

    ncp_task_v2_config_free(nca);

    ncp->ncaHdl = NULL;

NCP_RETURN_LABEL
    return ncpStatus;
}





ncp_st_t
ncp_task_v2_init_nca_vat_tables(ncp_dev_hdl_t devHdl, ncp_t *ncp)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    int i;
    int base;
    int nodeID;

    ncp_uint64_t axiAddr;
    ncp_uint32_t paHigh;
    ncp_uint32_t paLow;

    switch (ncp->busAdaptor)
    {
        /*
         * all of the page AXI addresses are defined within the
         * driver and not readily accessible to user-land code.
         * For now we just hard-code.
         */
        case NCP_DEV_BUS_PCI:
            axiAddr = 0x3000000000ULL;
            break;

        case NCP_DEV_BUS_SRIOEP:
            axiAddr = 0x3100000000ULL;
            break;

        case NCP_DEV_BUS_ACE:
        default:
            axiAddr = 0ULL;
            break;

    }

    paHigh = NCP_ADDR_UPPER(axiAddr);
    paLow  = NCP_ADDR_LOWER(axiAddr);

    if (TRUE == ncp->domainIsInternal)
    {
        nodeID      = 0x10;
    }
    else
    {
        nodeID      = 0x11;

        /* ====
         * Only Program Pool 0 if external
         * ====
         */

        /* size is 1GB */
        NCP_CALL(ncr_write32(NCP_REGION_ID(0x16, nodeID),
                             0x1000,
                             0x80000000));
        NCP_CALL(ncr_write32(NCP_REGION_ID(0x16, nodeID),
                             0x1004,
                             0x40000000-1));

        /* base is PCIe mem window 0x30_0000_0000 */

        NCP_CALL(ncr_write32(NCP_REGION_ID(0x16, nodeID),
                             0x1008,
                             paHigh));

        NCP_CALL(ncr_write32(NCP_REGION_ID(0x16, nodeID),
                             0x100c,
                             paLow));
    }

    /* ====
     * Pools 8 .. 23
     * ====
     */

    for (i=8, base=0x1080; i<=23; i++, base += 0x10)
    {
        ncp_task_ncaV2_pool_t *pPoolEntry
            = &pNcpNcaV2_TaskSwState->taskMemoryPool[i];

        /* size and valid bit */
        NCP_CALL(ncr_write32(NCP_REGION_ID(0x16, nodeID),
                             base,
                             0x80000000));

        NCP_CALL(ncr_write32(NCP_REGION_ID(0x16, nodeID),
                             base+4,
                             pPoolEntry->pool_Size));

        /*
         * base for external domain is PCIe mem window 0x30_0000_0000 + PA,
         * and 0LL+PA for internal domain. PA_high was set earlier
         */
        NCP_CALL(ncr_write32(NCP_REGION_ID(0x16, nodeID),
                             base+8,
                             paHigh));
        NCP_CALL(ncr_write32(NCP_REGION_ID(0x16, nodeID),
                             base+12,
                             pPoolEntry->pool_PA));
    }

NCP_RETURN_LABEL
    return(ncpStatus);
}


ncp_st_t
ncp_task_v2_allocate_completion_data(ncp_hdl_t ncpHdl)
{
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;
    ncp_pvt_task_hdl_t *myTaskHdl = NULL;
    int i;

    for(i=0; i < NCP_X7_NUM_THREAD_QUEUESETS; i++)
    {
        if ((pNcpNcaV2_TaskSwState
            ->threadQueueSets[i].requiresCompletionData)
         && (pNcpNcaV2_TaskSwState->inUmode
             == pNcpNcaV2_TaskSwState->threadQueueSets[i].uMode))
        {
            ncp_task_pcq_t *p_oPCQ;
            int sz;


            p_oPCQ = pNcpNcaV2_TaskSwState
                ->threadQueueSets[i].p_oPCQ;

            sz = p_oPCQ->nEntries *
               sizeof(ncp_task_ncav2_min_completion_data_t);

            NCP_CALL(ncp_task_hdl_create(
               ncpHdl,
               i,
               FALSE,
               FALSE,
               (ncp_task_hdl_t *)&myTaskHdl));


#if defined(NCP_TASK_PRINT_BASE_ADDRESSES_AND_MAPPINGS)
    NCP_MSG(NCP_MSG_INFO, "allocating task completion area for TQS=%d,   mode=%d, myMode=%d\n",
                i,
                pNcpNcaV2_TaskSwState->threadQueueSets[i].uMode,
                pNcpNcaV2_TaskSwState->inUmode
                );
#endif

            NCP_CALL(ncp_task_buffer_alloc(
                sz,
                (void **)&p_oPCQ->u.opcq_info.pCompletionData));

#if defined(NCP_TASK_PRINT_BASE_ADDRESSES_AND_MAPPINGS)
    NCP_MSG(NCP_MSG_INFO, "initialized task completion area for TQS=%d,   VA=%p\n",
                i,
                p_oPCQ->u.opcq_info.pCompletionData);
#endif

            memset(p_oPCQ->u.opcq_info.pCompletionData,
                   0,
                   sz);

            if (myTaskHdl)
            {
                ncp_task_hdl_remove((ncp_task_hdl_t)myTaskHdl);
            }
            myTaskHdl = NULL;

        }
    }

NCP_RETURN_LABEL

    if (myTaskHdl)
    {
        ncp_task_hdl_remove((ncp_task_hdl_t)myTaskHdl);
    }

    return(ncpStatus);
}

#if !defined(NCP_DEV_SOCKET) && !defined(NCP_DEV_FBRS)


ncp_st_t
ncp_task_v2_program_xlat_tables(ncp_dev_hdl_t dev)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    int poolID;
    int i;
    ncp_mme_pool_t *pMMEpoolInfo;

    pMMEpoolInfo = &pNcpNcaV2_TaskSwState->MMEpoolInfo[0];

    /*
     * Make sure we only clear the xlat tables once!
     */
    if ((FALSE == pNcpNcaV2_TaskSwState->inUmode)
        || (FALSE == pNcpNcaV2_TaskSwState->kernelModeConfigured))
    {
        /*
         * Clear all xlat tables
         */
        NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,
                            NCP_NCA_MEM_INIT_DONE_55XX,
                            0x2);
    }

    /*
     * Program NCAV2 XLAT Tables for *all* pools except 0 and 1,   even if
     * not used by Task I/O
     */
    for (poolID = 2;
         poolID < NCP_X7_NUM_TASK_MEMORY_POOLS;
         poolID++)
    {

        ncp_task_ncaV2_pool_t *pPoolEntry
         = &pNcpNcaV2_TaskSwState->taskMemoryPool[poolID];
#if 0 /* UBOOT */
        ncp_uint32_t vaBaseLow;
        ncp_uint32_t vaBaseHigh;
        ncp_uint32_t vaDynamicLow;
        ncp_uint32_t vaDynamicHigh;
        ncp_uint32_t ota_regAddr = 0x14000 + (poolID*0x10);
#endif

        if (NCP_TASK_IS_SHARED_POOL(poolID)
           && (FALSE == pNcpNcaV2_TaskSwState->inUmode))
        {
            /*
             * Shared pools not supported in kernel mode,  so let
             * user mode config componenet program these
             */
            continue;
        }


        if (NCP_TASK_IS_SHARED_POOL(poolID)
            || (pNcpNcaV2_TaskSwState->inUmode == pPoolEntry->uMode))
        {
#if 0 /* UBOOT */
            ncp_uint64_t poolVA     = (ncp_uint64_t)pPoolEntry->pool_VA;
#endif
            ncp_uint64_t poolEndVA  = (ncp_uint64_t)pPoolEntry->pool_EndVA;

            poolEndVA++;    /* need to add 1 due to h/w dropping 8 bits */

#if 0 /* UBOOT */
            if (sizeof(void *) > 4)
            {
                vaBaseHigh = (poolVA & 0xFFFFFFFF00000000LL) >> 32;
                vaBaseLow  = (poolVA & 0x00000000FFFFFFFFLL);
                vaDynamicHigh = (poolEndVA & 0xFFFFFFFF00000000LL) >> 32;
                vaDynamicLow  = (poolEndVA & 0x00000000FFFFFFFFLL);
            }
            else
            {
                vaBaseHigh = 0;;
                vaBaseLow  = poolVA;
                vaDynamicHigh = 0;
                vaDynamicLow  = poolEndVA;
            }

            /*
             * OTA xlat table - Note: only need to program 1 table.   Values will
             * be automatically updated in all 3.
             */

            NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,
                                ota_regAddr,
                                vaBaseHigh);
            NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,
                                ota_regAddr+4,
                                vaBaseLow);
            NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,
                                ota_regAddr+8,
                                vaDynamicHigh);
            NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,
                                ota_regAddr+12,
                                vaDynamicLow);
#endif
        }   /* execution mode same as pool mode */
    }   /* for */

   /* Defect 44455: write additional register values */
    /* TODO: Re-locate, if necessary */

    /*
     * ota_vpp_base_addr_table 0x101.0x0.0x14400
     * programmed with 4 64-bit virt base addr's for 64k/16k/2k/256 blks pool0-7
     */
    /*
     * ota_return_ptr_fifo_vpp_base_addr_table 0x101.0x0.0x15c00
     * (same as 0x14400)
     */

    /* Shared pools are not supported in kernel mode */
    if (pNcpNcaV2_TaskSwState->inUmode)
    {
        for ( i = 0; i < NCP_X7_NUM_SHARED_MEMORY_POOLS; i++)
        {
            ncp_ncaV2_base_addr_register_t baReg;
            void *myU32Valp = NULL;
            memset( &baReg, 0, sizeof(baReg));
            baReg.base_addr_256_h = pMMEpoolInfo[i].virtBase[3] >> 32;
            baReg.base_addr_256_l = pMMEpoolInfo[i].virtBase[3];
            baReg.base_addr_2k_h = pMMEpoolInfo[i].virtBase[2] >> 32;
            baReg.base_addr_2k_l = pMMEpoolInfo[i].virtBase[2];
            baReg.base_addr_16k_h = pMMEpoolInfo[i].virtBase[1] >> 32;
            baReg.base_addr_16k_l = pMMEpoolInfo[i].virtBase[1];
            baReg.base_addr_64k_h = pMMEpoolInfo[i].virtBase[0] >> 32;
            baReg.base_addr_64k_l = pMMEpoolInfo[i].virtBase[0];

            myU32Valp = &baReg;
            NCP_CALL(ncr_write(NCP_REGION_NCA_AXI, 0,
                                 0x14400 + (i * 0x20), /* TODO: remove hard-coding */
                                 8, /* 8 32-bit words */
                                 ((ncp_uint32_t*)(myU32Valp))));
            NCP_CALL(ncr_write(NCP_REGION_NCA_AXI, 0,
                               0x15c00 + (i * 0x20), /* TODO: remove hard-coding */
                               8, /* 8 32-bit words */
                               ((ncp_uint32_t*)(myU32Valp))));
        }
    }

    /*
     * ota_return_ptr_fifo_xlat_table 0x101.0x0.0x15800
     * written with virt base addresses and maxDynamic for each pool
     */

    for ( i = 2; i < NCP_X7_NUM_TASK_MEMORY_POOLS; i++)
    {
        ncp_ncaV2_base_addr_max_dyn_register_t bamdReg;
        void *myU32Valp = NULL;
        ncp_uint64_t virtBase;
        ncp_uint64_t maxDynamic;

        if (0ULL == pMMEpoolInfo[i].maxDynamic)
        {
            continue;
        }
        if (NCP_TASK_IS_SHARED_POOL(i))
        {
           if (FALSE == pNcpNcaV2_TaskSwState->inUmode)
           {
                /*
                 * Shared pools not supported in kernel mode,  so let
                 * user mode config componenet program these
                 */
                continue;
            }
            virtBase    = pMMEpoolInfo[i].poolVirtBase;
            maxDynamic  = pMMEpoolInfo[i].maxDynamic
                          + pMMEpoolInfo[i].poolVirtBase;
        }
        else
        {
            ncp_task_ncaV2_pool_t *pPoolEntry
                    = &pNcpNcaV2_TaskSwState->taskMemoryPool[i];

            if (pNcpNcaV2_TaskSwState->inUmode != pPoolEntry->uMode)
            {
                if ((TRUE == pNcpNcaV2_TaskSwState->inUmode)
                    && (0ULL == pMMEpoolInfo[i].maxDynamic))
                {
                    /*
                     * user mode and unused pool - init now!
                     */
                }
                else
                {
                    continue;
                }
            }
            if (pNcpNcaV2_TaskSwState->inUmode)
            {
                virtBase    = pMMEpoolInfo[i].poolVirtBase;
                maxDynamic  = pMMEpoolInfo[i].maxDynamic
                              + pMMEpoolInfo[i].poolVirtBase;
            }
            else
            {
/* Not sure what to do here! */
#if 0
                virtBase    = (ncp_uint64_t) pPoolEntry->pool_VA;
                maxDynamic  = (ncp_uint64_t) pPoolEntry->pool_EndVA;
#else
                virtBase    = pMMEpoolInfo[i].poolVirtBase;
                maxDynamic  = pMMEpoolInfo[i].maxDynamic
                              + pMMEpoolInfo[i].poolVirtBase;
#endif
            }
        }

#if defined(NCP_KMODE_DEBUG)
        NCP_LOG(NCP_MSG_INFO, "In xlat ota return - pool %d virtBase=%llx, maxDynamic=%llx\r\n",
            i,
            virtBase,
            maxDynamic);
#endif


        memset( &bamdReg, 0, sizeof(bamdReg));
        bamdReg.base_addr_h = virtBase >> 32;
        bamdReg.base_addr_l = virtBase;
        bamdReg.max_dynamic_h = maxDynamic >> 32;
        bamdReg.max_dynamic_l = maxDynamic;

        myU32Valp = &bamdReg;
        NCP_CALL(ncr_write(NCP_REGION_NCA_AXI, 0,
                           0x15800 + (i * 0x10), /* TODO: remove hard-coding */
                           4, /* 4 32-bit words */
                           ((ncp_uint32_t*)(myU32Valp))));

    }   /* for */

NCP_RETURN_LABEL

    return(ncpStatus);
}




ncp_st_t
ncp_task_v2_enable_all_pools(ncp_dev_hdl_t dev, ncp_hdl_t ncpHdl)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_pvt_task_hdl_t *myTaskHdl = NULL;
    ncp_nca_mme_buf_fetch_en_size0_reg_55xx_t fetchMask={0};
    int tqsID;
    int poolID;

    for (poolID = 2;
         poolID < NCP_X7_NUM_TASK_MEMORY_POOLS;
         poolID++)
    {
        ncp_task_ncaV2_pool_t *pPoolEntry;
        pPoolEntry = &pNcpNcaV2_TaskSwState->taskMemoryPool[poolID];

        /*
         * We do not support shared pools in kernel mode
         */
        if (NCP_TASK_IS_SHARED_POOL(poolID)
            && (FALSE == pNcpNcaV2_TaskSwState->inUmode))
        {
            continue;
        }

        if (pNcpNcaV2_TaskSwState->inUmode == pPoolEntry->uMode)
        {

#ifdef NCP_KMODE_DEBUG
                NCP_LOG(NCP_MSG_INFO,
                        "kmode config for pool %d, uMode=%d\r\n",
                        poolID,
                        pPoolEntry->uMode
                        );
#endif

             /* Find first thread queue set that uses this pool */

            for (tqsID=0; tqsID < NCP_X7_NUM_THREAD_QUEUESETS; tqsID++)
            {
                if (poolID
                    == pNcpNcaV2_TaskSwState->threadQueueSets[tqsID].poolID)
                {
#ifdef NCP_KMODE_DEBUG
                    if (FALSE == pNcpNcaV2_TaskSwState->inUmode)
                    {
                        NCP_LOG(NCP_MSG_INFO,
                                "first tqs using poolID %d is %d\r\n",
                                poolID,
                                tqsID);
                    }
#endif

                    break;
                }
            }

            /* pool used by Task I/O ? */
            if (NCP_X7_NUM_THREAD_QUEUESETS != tqsID)
            {

                /*
                 * Enable MME FIFO fetch for this pool
                 */

                /* size 0 */
                if (0 != pNcpNcaV2_TaskSwState->taskMemoryPool[poolID].numBlocks[0])
                {
                    NCP_DEV_NCA_READ_REG32(dev, NCP_REGION_NCA_AXI,
                                            NCP_NCA_MME_BUF_FETCH_EN_SIZE0_55XX,
                                            (ncp_uint32_t *)(&fetchMask));
                    fetchMask.mme_buf_fetch_en_size0 |= 1<<poolID;
                    NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,
                                            NCP_NCA_MME_BUF_FETCH_EN_SIZE0_55XX,
                                            *(ncp_uint32_t *)(&fetchMask));
                }

                /* size 1 */
                if (0 != pNcpNcaV2_TaskSwState->taskMemoryPool[poolID].numBlocks[1])
                {
                    NCP_DEV_NCA_READ_REG32(dev, NCP_REGION_NCA_AXI,
                                            NCP_NCA_MME_BUF_FETCH_EN_SIZE1_55XX,
                                            (ncp_uint32_t *)(&fetchMask));
                    fetchMask.mme_buf_fetch_en_size0 |= 1<<poolID;
                    NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,
                                            NCP_NCA_MME_BUF_FETCH_EN_SIZE1_55XX,
                                            *(ncp_uint32_t *)(&fetchMask));
                }

                /* size 2 */
                if (0 != pNcpNcaV2_TaskSwState->taskMemoryPool[poolID].numBlocks[2])
                {
                    NCP_DEV_NCA_READ_REG32(dev, NCP_REGION_NCA_AXI,
                                            NCP_NCA_MME_BUF_FETCH_EN_SIZE2_55XX,
                                            (ncp_uint32_t *)(&fetchMask));
                    fetchMask.mme_buf_fetch_en_size0 |= 1<<poolID;
                    NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,
                                            NCP_NCA_MME_BUF_FETCH_EN_SIZE2_55XX,
                                            *(ncp_uint32_t *)(&fetchMask));
                }

                /* size 3 */
                if (0 != pNcpNcaV2_TaskSwState->taskMemoryPool[poolID].numBlocks[3])
                {
                    NCP_DEV_NCA_READ_REG32(dev, NCP_REGION_NCA_AXI,
                                            NCP_NCA_MME_BUF_FETCH_EN_SIZE3_55XX,
                                            (ncp_uint32_t *)(&fetchMask));
                    fetchMask.mme_buf_fetch_en_size0 |= 1<<poolID;
                    NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,
                                            NCP_NCA_MME_BUF_FETCH_EN_SIZE3_55XX,
                                            *(ncp_uint32_t *)(&fetchMask));
                }


                if (NCP_TASK_IS_CPU_POOL(poolID))
                {
                    int i;
                    int sz=0;

#ifdef NCP_KMODE_DEBUG
                        NCP_LOG(NCP_MSG_INFO,
                                "kmode - fill CPU pool for poolID %d tqs %d\r\n",
                                poolID,
                                tqsID);
#endif

                    NCP_CALL(ncp_task_hdl_create(
                       ncpHdl,
                       tqsID,
                       FALSE,
                       FALSE,
                       (ncp_task_hdl_t *)&myTaskHdl));

                    for (sz=0; sz < 4; sz++)
                    {
                        int numRxBuffs
                            = pNcpNcaV2_TaskSwState->taskMemoryPool[poolID].numBlocksRxReserve[sz];

                        for (i=0; i < numRxBuffs; i++)
                        {
                            NCP_CALL(ncp_task_v2_supply_freebuffer_to_nca(
                                myTaskHdl,
                                sz,
                                FALSE));
                        }

                    } /* For sz */

                    if (myTaskHdl)
                    {
                        ncp_task_hdl_remove((ncp_task_hdl_t)myTaskHdl);
                        myTaskHdl = NULL;
                    }

                }
            }   /* pool used by Task I/O ? */
        }  /* pool  mode matches current execution mode */
    } /* for poolID */

NCP_RETURN_LABEL

#ifdef NCP_KMODE_DEBUG
    if (NCP_ST_SUCCESS != ncpStatus)
    {
       NCP_LOG(NCP_MSG_ERROR,
           "kmode - enable all pools returning %d\t\n", ncpStatus);
    }
#endif

    if (myTaskHdl)
    {
        ncp_task_hdl_remove((ncp_task_hdl_t)myTaskHdl);
    }

    return(ncpStatus);
}

#endif /* !defined(NCP_DEV_SOCKET) && !defined(NCP_DEV_FBRS) */



ncp_st_t
ncp_task_v2_config_mme_for_tqs(ncp_int32_t tqsID)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_nca_thread_queue_set_t *pTQS
        = &pNcpNcaV2_TaskSwState->threadQueueSets[tqsID];
    int i;

#ifdef NCP_TASK_DEBUG_MME
    NCP_LOG(NCP_MSG_INFO,"config_mme_for_tqs (%d)\r\n",tqsID);
#endif

    if (NCP_TASK_IS_SHARED_POOL(pTQS->poolID))
    {
        ncp_task_ncaV2_pool_t *pPoolEntry;
        pPoolEntry = &pNcpNcaV2_TaskSwState->taskMemoryPool[pTQS->poolID];

        for (i=0; i < pTQS->numAllocators; i++)
        {
            ncp_uint64_t *p64_VA;

            /*
             * Get VA and memset entire allocation interface.
             * Size is 4 queues of 128 64bit entries plus
             * 4 64bit read pointers.   The read pointers index
             * into the queues,   which are populated by MME with
             * free task buffers.
             */
            NCP_CALL(NCP_TASK_INITIALIZE_DOMAIN_OBJ_VA(
                pTQS->mme[i].cfgOffset,
                ((sizeof(ncp_uint64_t)*128*4)+(4*sizeof(ncp_uint64_t))),
                &pTQS->mme[i].baseVA,
                FALSE));

            p64_VA = (ncp_uint64_t *)pTQS->mme[i].baseVA;

            /*
             * Initialize MME Queues.
             * Queues are laid out from 64K to 256B
             */

            /* 64K queue */
#ifdef NCP_TASK_DEBUG_MME
            NCP_LOG(NCP_MSG_INFO, "64K queue entries start at %p\r\n",((void *)(ncp_raw_addr_t)p64_VA));
#endif
            pTQS->mme[i].allocIF[3].entries_baseVA
                = p64_VA;
            p64_VA +=  128;

           /* 16K Queue */
#ifdef NCP_TASK_DEBUG_MME
            NCP_LOG(NCP_MSG_INFO, "16K queue entries start at %p\r\n",((void *)(ncp_raw_addr_t)p64_VA));
#endif
             pTQS->mme[i].allocIF[2].entries_baseVA
                = p64_VA;
            p64_VA +=  128;

            /* 2K queue */
#ifdef NCP_TASK_DEBUG_MME
            NCP_LOG(NCP_MSG_INFO, "2K queue entries start at %p\r\n",((void *)(ncp_raw_addr_t)p64_VA));
#endif
            pTQS->mme[i].allocIF[1].entries_baseVA
                = p64_VA;
            p64_VA +=  128;

            /* 256B queue */
#ifdef NCP_TASK_DEBUG_MME
            NCP_LOG(NCP_MSG_INFO, "256B queue entries start at %p\r\n",((void *)(ncp_raw_addr_t)p64_VA));
#endif
            pTQS->mme[i].allocIF[0].entries_baseV
                = p64_VA;
            p64_VA +=  128;

            /*
             * Read Pointers are laid out as follows: 2K, 16K, 64K, 256B
             *
             * Inititalize Read Pointer related state.
             * We will maintain a pointer to the "real" h/w read ptr area,
             * where we will manage a physAddr that us read by the h/w.
             * We will also maintain a sw pointer for direct access into
             * mPCQ entries. Test for queue wrap will be performed on
             * the s/w pointer,  since that is a 32-bit test with current
             * target platforms.
             */


            /* 2K */
#ifdef NCP_TASK_DEBUG_MME
            NCP_LOG(NCP_MSG_INFO, "2K readPtr @ %p\r\n",((void *)(ncp_raw_addr_t)p64_VA));
#endif
            pTQS->mme[i].allocIF[1].queueValid
                = ((pPoolEntry->numBlocks[1] == 0)? FALSE : TRUE);

            pTQS->mme[i].allocIF[1].readP_hwVA = (ncp_uint64_t *)p64_VA;
            pTQS->mme[i].allocIF[1].readP_hw_indx0_val
                = NCP_TASK_VA_2_PA(
                        pTQS->mme[i].allocIF[1].entries_baseVA,
                        0);
            pTQS->mme[i].allocIF[1].readP_swVA
                = pTQS->mme[i].allocIF[1].entries_baseVA;
            pTQS->mme[i].allocIF[1].readP_swVA_max_val
                = (ncp_uint64_t *)pTQS->mme[i].allocIF[1].readP_swVA + 127;

#if defined(NCP_TASK_DEBUG_MME) && !defined(NCP_KERNEL)
            NCP_LOG(NCP_MSG_INFO, "Contents:\r\n");
            ncp_r32((ncp_uint32_t *)pTQS->mme[i].allocIF[1].entries_baseVA, 256);
#endif

            /* 16K */

            p64_VA++;
#ifdef NCP_TASK_DEBUG_MME
            NCP_LOG(NCP_MSG_INFO, "16K readPtr @ %p\r\n",((void *)(ncp_raw_addr_t)p64_VA));
#endif
            pTQS->mme[i].allocIF[2].queueValid
                = ((pPoolEntry->numBlocks[2] == 0)? FALSE : TRUE);
            pTQS->mme[i].allocIF[2].readP_hwVA = (ncp_uint64_t *)p64_VA;
            pTQS->mme[i].allocIF[2].readP_hw_indx0_val
                = NCP_TASK_VA_2_PA(
                        pTQS->mme[i].allocIF[2].entries_baseVA,
                        0);
            pTQS->mme[i].allocIF[2].readP_swVA
                = pTQS->mme[i].allocIF[2].entries_baseVA;
            pTQS->mme[i].allocIF[2].readP_swVA_max_val
                = (ncp_uint64_t *)pTQS->mme[i].allocIF[2].readP_swVA + 127;


#if defined(NCP_TASK_DEBUG_MME) && !defined(NCP_KERNEL)
            NCP_LOG(NCP_MSG_INFO, "Contents:\r\n");
            ncp_r32((ncp_uint32_t *)pTQS->mme[i].allocIF[2].entries_baseVA, 256);
#endif

            /* 64K */
            p64_VA++;

#ifdef NCP_TASK_DEBUG_MME
            NCP_LOG(NCP_MSG_INFO, "64K readPtr @ %p\r\n",((void *)(ncp_raw_addr_t)p64_VA));
#endif
            pTQS->mme[i].allocIF[3].queueValid
                = ((pPoolEntry->numBlocks[3] == 0)? FALSE : TRUE);

            pTQS->mme[i].allocIF[3].readP_hwVA = (ncp_uint64_t *)p64_VA;
            pTQS->mme[i].allocIF[3].readP_hw_indx0_val
                = NCP_TASK_VA_2_PA(
                        pTQS->mme[i].allocIF[3].entries_baseVA,
                        0);
            pTQS->mme[i].allocIF[3].readP_swVA
                = pTQS->mme[i].allocIF[3].entries_baseVA;
            pTQS->mme[i].allocIF[3].readP_swVA_max_val
                = (ncp_uint64_t *)pTQS->mme[i].allocIF[3].readP_swVA + 127;


#if defined(NCP_TASK_DEBUG_MME) && !defined(NCP_KERNEL)
            NCP_LOG(NCP_MSG_INFO, "Contents:\r\n");
            ncp_r32((ncp_uint32_t *)pTQS->mme[i].allocIF[3].entries_baseVA, 256);
#endif

            /* 256B */
            p64_VA++;
#ifdef NCP_TASK_DEBUG_MME
            NCP_LOG(NCP_MSG_INFO, "256B readPtr @ %p\r\n",((void *)(ncp_raw_addr_t)p64_VA));
#endif

            pTQS->mme[i].allocIF[0].queueValid
                = ((pPoolEntry->numBlocks[0] == 0)? FALSE : TRUE);

            pTQS->mme[i].allocIF[0].readP_hwVA = (ncp_uint64_t *)p64_VA;
            pTQS->mme[i].allocIF[0].readP_hw_indx0_val
                = NCP_TASK_VA_2_PA(
                        pTQS->mme[i].allocIF[0].entries_baseVA,
                        0);
            pTQS->mme[i].allocIF[0].readP_swVA
                = pTQS->mme[i].allocIF[0].entries_baseVA;
            pTQS->mme[i].allocIF[0].readP_swVA_max_val
                = (ncp_uint64_t *)pTQS->mme[i].allocIF[0].readP_swVA + 127;


#if defined(NCP_TASK_DEBUG_MME) && !defined(NCP_KERNEL)
            NCP_LOG(NCP_MSG_INFO, "Contents:\r\n");
            ncp_r32((ncp_uint32_t *)pTQS->mme[i].allocIF[0].entries_baseVA, 256);
#endif

            p64_VA++;

#ifdef NCP_TASK_PRINT_BASE_ADDRESSES_AND_MAPPINGS

           NCP_MSG(NCP_MSG_INFO, "initialized shared pool allocator (%d) @offset 0x%llx baseVA=%p, endVA=%p\r\n",
                pTQS->mme[i].id,
                pTQS->mme[i].cfgOffset,
                (void *)pTQS->mme[i].baseVA,
                (void *)p64_VA);
#endif

        }
    }


NCP_RETURN_LABEL
    return(ncpStatus);
}

ncp_st_t
ncp_task_v2_init_groups_and_queues(ncp_t            *ncp,
                                   ncp_dev_hdl_t    dev,
                                   ncp_nca_t        *nca,
                                   ncp_bool_t       warmRestart,
                                   ncp_uint8_t      *pLinear_iPCQ)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    int  j, grpId;
    ncp_uint8_t linear_iPCQ=0;

    NCP_CALL(ncp_task_v2_disable_PCQs(
            dev,
            ((0 == pNcpNcaV2_TaskSwState->myDomain)? TRUE : FALSE),
            ncp->domainIsInternal));

    for (grpId=0; grpId < NCP_X7_NUM_PCQ_GROUPS; grpId++)
    {
        int grpDomain = pNcpNcaV2_TaskSwState->pcq_grp[grpId].grpDomain;
        int tqsID=0;
        int grpRelative_iPCQ=0;
        ncp_bool_t first_iPCQ_recorded = FALSE;

        if (0xFF == pNcpNcaV2_TaskSwState->pcq_grp[grpId].id)
        {
            continue;
        }

        NCP_MSG(NCP_MSG_DEBUG, "configuring group %d\r\n", grpId);
        /*
         * Find first queueset in this group
         */
        while(pNcpNcaV2_TaskSwState->threadQueueSets[tqsID].grpId != grpId)
        {
            tqsID++;
            NCP_ASSERT((NCP_X7_NUM_THREAD_QUEUESETS > tqsID), NCP_ST_TASK_NO_QUEUESET_IN_GRP);
        }

        NCP_CALL(ncp_task_v2_pcq_group_init(dev,
                                        nca,
                                        grpId,
                                        grpDomain,
                                        ncp->domainIsInternal,
                                        warmRestart));

        /*
         * Configure iPCQs (if any),  and output-type PCQs within this group (oPCQ, and cPCQ).
         * There is exactly one output-type PCQ of each type per queueset.
         */

        for (j=0; j<pNcpNcaV2_TaskSwState->pcq_grp[grpId].num_oPCQs; j++)
        {
            ncp_uint8_t pool = pNcpNcaV2_TaskSwState->threadQueueSets[tqsID].poolID;

           /*
            * oPCQ
            */

            NCP_CALL(ncp_task_v2_opcq_init(dev,
                        grpId,                                  /* Group Id */
                        j,                                      /* Queue Id - group relative */
                        tqsID,                            /* flat id */
                        pNcpNcaV2_TaskSwState->oPCQs[tqsID].nEntries, /* Depth */
                        pNcpNcaV2_TaskSwState->threadQueueSets[tqsID].uMode, /* user mode ? */
                        grpDomain,
                        ncp->domainIsInternal,
                        warmRestart));

           /*
            * cPCQ
            */
            NCP_CALL(ncp_task_v2_cpcq_init(dev,
                        grpId,
                        j,
                        tqsID,
                        NCP_NCA_DEFAULT_CPCQ_DEPTH,
                        NCP_NCA_DEFAULT_CPCQ_BLOCK_SIZE,
                        pNcpNcaV2_TaskSwState->threadQueueSets[tqsID].uMode, /* user mode ? */
                        grpDomain,
                        ncp->domainIsInternal,
                        warmRestart));

           /*
            * Configure iPCQs within this group and queueSet
            */

           {
                int iPCQs_inSet = pNcpNcaV2_TaskSwState->threadQueueSets[tqsID].num_iPCQs_in_queueSet;
                int k;

                linear_iPCQ = pNcpNcaV2_TaskSwState->threadQueueSets[tqsID].first_iPCQ_id;
                for (k = 0; k < iPCQs_inSet; k++)
                {

                    if (FALSE == first_iPCQ_recorded)
                    {
                        pNcpNcaV2_TaskSwState->pcq_grp[grpId].first_iPCQ_inGroup = linear_iPCQ;
                        first_iPCQ_recorded = TRUE;
                    }

                    NCP_CALL(ncp_task_v2_ipcq_init(dev,
                                grpId,                                  /* Group Id */
                                grpRelative_iPCQ,                       /* Queue Id - group relative */
                                linear_iPCQ,                            /* flat id */
                                pNcpNcaV2_TaskSwState->iPCQs[linear_iPCQ].nEntries,      /* Depth */
                                pNcpNcaV2_TaskSwState->iPCQs[linear_iPCQ].u.ipcq_info.rxTaskCompletionMode, /* Completion Mode */
                                pool,  /* rx buffer pool Id */
                                pNcpNcaV2_TaskSwState->threadQueueSets[tqsID].uMode, /* user mode ? */
                                grpDomain,
                                ncp->domainIsInternal,
                                warmRestart));

                    grpRelative_iPCQ++;
                    linear_iPCQ++;
                }
            }

            pNcpNcaV2_TaskSwState->threadQueueSets[tqsID].first_iPCQ_inGroup = pNcpNcaV2_TaskSwState->pcq_grp[grpId].first_iPCQ_inGroup;

            /*
             * Now configure mme allocation interfaces in this TQS
             */

            NCP_CALL(ncp_task_v2_config_mme_for_tqs(tqsID));

            tqsID++;
        }


        pNcpNcaV2_TaskSwState->allGrpMask |= (1<<grpId);

        if (grpDomain == pNcpNcaV2_TaskSwState->myDomain)
        {
            pNcpNcaV2_TaskSwState->activeGrpMask |= (1<<grpId);

        }

    }

	NCP_MSG(NCP_MSG_DEBUG, "active grp Mask = 0x%x, total group mask = 0x%x\r\n",
        pNcpNcaV2_TaskSwState->activeGrpMask,
        pNcpNcaV2_TaskSwState->allGrpMask);


#if !defined(NCP_DEV_SOCKET) && !defined(NCP_DEV_FBRS)
    /*
     * Link thread queue set struct to physical queues
     */
    for (j = 0; j < NCP_X7_NUM_THREAD_QUEUESETS; j++)
    {

        ncp_nca_thread_queue_set_t *pThreadQueueSet = &pNcpNcaV2_TaskSwState->threadQueueSets[j];

        if ((0xFF == pThreadQueueSet->id)  /* unused ? */
         || (pThreadQueueSet->tqsDomain != pNcpNcaV2_TaskSwState->myDomain)
         || (pNcpNcaV2_TaskSwState->inUmode
             != pNcpNcaV2_TaskSwState->threadQueueSets[j].uMode))
        {
            continue;
        }
        NCP_CALL(ncp_task_v2_map_queuenum_to_pcq(NCP_TASK_PCQ_OUTPUT, j, &pThreadQueueSet->p_oPCQ));
        NCP_CALL(ncp_task_v2_map_queuenum_to_pcq(NCP_TASK_PCQ_CONFIG, j, &pThreadQueueSet->p_cPCQ));


    }
#endif


    *pLinear_iPCQ  = linear_iPCQ;

NCP_RETURN_LABEL
    return(ncpStatus);
}

ncp_st_t
ncp_task_v2_enable_rbp_backpressure(ncp_dev_hdl_t   dev,
                                    ncp_uint8_t     linear_iPCQ)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    int i;

    if ((NCP_TASK_ENABLE_RBP_BACKPRESSURE) && (pNcpNcaV2_TaskSwState->inUmode))
    {
        ncp_uint32_t rbbp_mask=0;

        /* we counted these earlier */
        for (i=0; i < linear_iPCQ; i++)
        {
            rbbp_mask |= (1<<i);
        }
        /*
         * Enable backpressure for all of our queues but only when out of largest buffer
         */
        pNcpNcaV2_TaskSwState->myInputPCQbitMask = rbbp_mask;
        NCP_CALL(ncp_task_v2_set_rbp_backpressure(dev,
                    TRUE,
                    rbbp_mask,
                    0x8));
    }
    else
    {
        /* Backpressure OFF */
        NCP_CALL(ncp_task_v2_set_rbp_backpressure(dev,
                    FALSE,
                    0,
                    0));
    }

NCP_RETURN_LABEL
    return(ncpStatus);
}



/*
 * Perform NcaV2 hardware configuration
 */

ncp_st_t ncp_task_v2_config_hw(ncp_hdl_t ncpHdl, ncp_dev_hdl_t dev, ncp_nca_t *nca,  ncp_bool_t warmRestart)
{
     ncp_st_t ncpStatus=NCP_ST_SUCCESS;
     ncp_t *ncp = ncpHdl;
     ncp_uint8_t linear_iPCQ=0;

    debug("Configuring local domain %d\r\n", pNcpNcaV2_TaskSwState->myDomain);

    /*
     * Hook task I/O state off nca handle
     */
     nca->myNcpNcaTaskState = pNcpNcaV2_TaskSwState;

    /*
     * Cache items from ncp handle
     */
    pNcpNcaV2_TaskSwState->myDomain = ncp->domainId;
    pNcpNcaV2_TaskSwState->ncpId = ncp->id;

    /*
     * Is *this* thread of execution running in user or kernel mode?
     * Subsequent functions and actions may vary depending on execution
     * mode,   so we need to set the local mode now.
     */

#if !defined(NCP_KERNEL) || defined(NCP_VXWORKS)
    pNcpNcaV2_TaskSwState->inUmode = TRUE;
    pNcpNcaV2_TaskSwState->domainIsInternal = ncp->domainIsInternal;
#else
    ncp->domainIsInternal = pNcpNcaV2_TaskSwState->domainIsInternal;
    ncp->rev.chipType = ((ncp_dev_t *)dev)->config->rev.chipType;
    pNcpNcaV2_TaskSwState->inUmode = FALSE;
#endif

    /*
     * Map in domain bundle and perform sw state initialization
     */

    NCP_CALL(NCP_TASK_LOWLEVEL_MEMCFG(ncpHdl, dev, nca, warmRestart));

    /*
     * <<<=== Start NcaV2 Hardware Initialization ===>>>
     */

    /*
     * First we'll let the kernel config the resources that it is
     * managing.
     */

    if (pNcpNcaV2_TaskSwState->kernelModeConfigured)
    {
        NCP_CALL(NCP_TASK_DO_KMODE_CFG_FOR_TASKIO(ncpHdl,
                                              pNcpNcaV2_TaskSwState));
    }

    /*
     * We already have all of the pool info from ASE,  so init the
     * vat tables for all pools
     */

    NCP_CALL(ncp_task_v2_init_nca_vat_tables(dev, ncp));

    /*
     * Configure NcaV2 Queue groups, PCQs, and sw TQSets
     * Note that while we we do this regardless of the domain,   different
     * actions are taken by the low level routines based on whether we are the
     * primary domain and/or
     * the resource is owned by the local domain.
     *
     */

    NCP_CALL(ncp_task_v2_init_groups_and_queues(ncp,
                                                dev,
                                                nca,
                                                warmRestart,
                                                &linear_iPCQ));

    if  ((!warmRestart) &&
        (0 == pNcpNcaV2_TaskSwState->myDomain)) /* primary domain? */
    {
        NCP_CALL(ncp_task_v2_set_nca_config_init_reg(
            dev,
            0, /* itask_end_data_fill_off     :  1 */
            1, /* cfg_ring_ack_timer_en       :  1 */
            0, /* cpcq_en                     :  1 */
            0, /* otask_accum_en              :  1 */
            0, /* itask_accum_en              :  1 */
            0, /* otbp_soft_reset             :  1 */
            1, /* mpbf_en                     :  1 */
            0, /* otbp_ext_mem_wen            :  1 */
            0, /* cpcq_exec_disable           :  1 */
            0, /* opcq_num_ent_per_req_m1     :  2 */
            2, /* ota_num_beat                :  2 */
            2, /* ita_num_beat                :  2 */
            2, /* pgit_w_num_beat             :  2 */
            2  /* pgit_r_num_beat             :  2 */           ));


    }  /* !warmRestart and Primary domain */


    NCP_CALL(NCP_TASK_V2_INIT_CPU_POOLS(dev,
                    nca));

    /*
     * Register for interrupts
     */

    NCP_MSG(NCP_MSG_DEBUG,
        "Register interrupts for grp with mask=0x%x\r\n",
        pNcpNcaV2_TaskSwState->activeGrpMask);

    NCP_TASK_REGISTER_GROUP_INTERRUPTS(dev,
                                       pNcpNcaV2_TaskSwState->activeGrpMask);

    if (!warmRestart)
    {
        /*
         * X1_V2/X2 and beyond has different implementations/capabilities
         *
         *
         * 1) Start timers
         * 2) Force an immediate PGIT refresh for the newly added groups.
         * Since a mask is used,   the operation will apply to all of them,
         * and need not be applied individually as queue groups are added.
         */
        ncp_task_v2_init_version_specific_features(dev,
                                    nca,
                                    pNcpNcaV2_TaskSwState->activeGrpMask, warmRestart,
                                    ncp->domainIsInternal);


        NCP_CALL(ncp_task_v2_set_nca_load_indexes_reg(dev,
                                                  pNcpNcaV2_TaskSwState->activeGrpMask));
    } /* !warm restart */

#ifdef NCP_TASK_USE_MME_RECOVER_PTR_MODE

    /*
     * Set MME control to recover pointer mode
     */
    NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,
                            NCP_NCA_MME_CTL_55XX,
                            0x83f01);
#else
    NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,
                            NCP_NCA_MME_CTL_55XX,
                            0x83f00);
#endif


    /*
     * Initialze NPGIT to all zeros
     */

    if (pNcpNcaV2_TaskSwState->inUmode)
    {
        NCP_DEV_NCA_WRITE_REG32(dev, NCP_REGION_NCA_AXI,
                NCP_NCA_NPGIT_INIT_GRP_INDEXES_55XX,
                0xffff);
    }


    /*
     * XLAT tables must be programmed while accumulators are idle.
     * Do not access them after they are enabled.
     */
    NCP_CALL(NCP_TASK_V2_PROGRAM_XLAT_TABLES(dev));

    if (pNcpNcaV2_TaskSwState->inUmode)
    {

        /*
         * Make sure pgit is stable before proceeding
         */

        NCP_ISYNC_BARRIER();

        /*
         *************** HERE WE GO, ENABLE NCA TASK PROCESSING *************
         */
        if (0 == pNcpNcaV2_TaskSwState->myDomain)
        {

                if (!warmRestart)
                {

                    NCP_CALL(ncp_task_v2_set_nca_config_init_reg(
                        dev,
                        1, /* itask_end_data_fill_off     :  1 */
                        1, /* cfg_ring_ack_timer_en       :  1 */
                        1, /* cpcq_en                     :  1 */
                        1, /* otask_accum_en              :  1 */
                        1, /* itask_accum_en              :  1 */
                        0, /* otbp_soft_reset             :  1 */
                        1, /* mpbf_en                     :  1 */
    #ifdef NCP_TASK_OTBP_ALLOWED
                        1, /* otbp_ext_mem_wen            :  1 */
    #else
                        0, /* HACK - Disable!!!!  */
    #endif
                        0, /* cpcq_exec_disable           :  1 */
                        3, /* opcq_num_ent_per_req_m1     :  2 */
                        2, /* ota_num_beat                :  2 */
                        2, /* ita_num_beat                :  2 */
                        2, /* pgit_w_num_beat             :  2 */
                        2  /* pgit_r_num_beat             :  2 */  ));

                }  /* !warmRestart */
        } /* primary domain */



        /*
         * Enable backpressure ?
         */


        NCP_CALL(NCP_TASK_V2_ENABLE_RBP_BACKPRESSURE(dev, linear_iPCQ));

        NCP_CALL(NCP_TASK_V2_ENABLE_ALL_POOLS(dev,
                                              ncpHdl));

        /*
         * Allocate a sw managed completion data array for any thread
         * queue sets that contain iPCQs configured for manual
         * task completion.
         */
        NCP_CALL(NCP_TASK_V2_ALLOCATE_COMPLETION_DATA(ncpHdl));

        /*
         * Now unmap all user mode task Memory Pools that were mapped in as part of config
         */

        NCP_TASK_V2_UNMAP_ALL_MEMORY_POOLS(dev);


        /* Clear warm restart flag */
        pNcpNcaV2_TaskSwState->inWarmRestart = FALSE;

    }    /* pNcpNcaV2_TaskSwState->inUmode */

    /*
     * Complete kernel portion of hardware config
     */
    if (pNcpNcaV2_TaskSwState->kernelModeConfigured)
    {
        NCP_CALL(NCP_TASK_FINISH_KMODE_CFG_FOR_TASKIO(ncpHdl,
                                              pNcpNcaV2_TaskSwState));
    }

NCP_RETURN_LABEL

    return(ncpStatus);
}

#if defined(NCP_KERNEL) && defined(NCP_LINUX)

ncp_st_t
ncp_task_v2_kmode_phase2_config_hw(ncp_hdl_t ncpHdl,
                                   ncp_dev_hdl_t dev,
                                   ncp_nca_t *nca,
                                   ncp_bool_t warmRestart)
{
     ncp_st_t ncpStatus=NCP_ST_SUCCESS;

     NCP_CALL(NCP_TASK_V2_ENABLE_ALL_POOLS(dev,
                                          ncpHdl));

    /*
     * Allocate a sw managed completion data array for any thread
     * queue sets that contain iPCQs configured for manual
     * task completion.
     */
     NCP_CALL(NCP_TASK_V2_ALLOCATE_COMPLETION_DATA(ncpHdl));



NCP_RETURN_LABEL

    if (NCP_ST_SUCCESS != ncpStatus)
    {
        NCP_LOG(NCP_MSG_INFO, "Kernel Mode Phase 2 Task I/O Config - returning error %d\r\n", ncpStatus);
    }

    return(ncpStatus);
}

#endif /*  defined(NCP_KERNEL) && defined(NCP_LINUX) */

#if defined(NCP_DEV_SOCKET)  || defined(NCP_DEV_FBRS)

ncp_st_t
ncp_task_v2_ase_memcfg(ncp_nca_t *nca)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    /* set process local global - This region is not used by simulator */
    pNcpNcaV2_domainBundle = NULL;
    /* nca->myNcpNcaGSM = NULL; */

    /*====================================
     * Initialize task I/O semaphores.
     *====================================
     */

    /*
     * Allocate and initialize locks used during warm restart
     */

#ifdef NCP_TASK_DBG_NVM_CORRUPTION
    pNcpNcaV2_TaskSwState->nvm_dbgLock = ncp_nvm_malloc(sizeof(ncp_task_mutex_t));
    ncp_memset(pNcpNcaV2_TaskSwState->nvm_dbgLock, 0, sizeof(ncp_task_mutex_t));
    NCP_TASK_INIT_LOCK(pNcpNcaV2_TaskSwState->nvm_dbgLock, 1, 1);
#endif

    pNcpNcaV2_TaskSwState->taskIoResourceLock
        = ncp_nvm_malloc(sizeof(ncp_task_mutex_t));
    ncp_memset(pNcpNcaV2_TaskSwState->taskIoResourceLock,
            0,
            sizeof(ncp_task_mutex_t));
    NCP_TASK_INIT_LOCK(pNcpNcaV2_TaskSwState->taskIoResourceLock, 1, 1);

NCP_RETURN_LABEL
    return(ncpStatus);
}
#endif /* NCP_SOCKET */

