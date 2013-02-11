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
 **    (c) 2008-2009, LSI Corporation Inc.  All rights reserved.           *
 **                                                                        *
 **  ***********************************************************************
 **
 **  ***********************************************************************
 **   File:       $HeadURL: http://txasoft2.lsi.com/svn/software/src/trunk/rte/cli/ncpTaskRecvLiteLoopback.c $
 **   Version:    $Revision: 44058 $
 **   Date:       $Date: 2011-01-24 14:13:22 -0600 (Mon, 24 Jan 2011) $
 **  
 **************************************************************************/


#include <stdio.h>
#include "ncp.h"
#include "ncp_vpm.h"            /* TODO: should be included by ncp.h */
#include "ncp_getopt.h"
#include "ncp_crt.h"
#include "ncp_task_lite.h"

static void 
sendCompletionFn(void *val,
                 void *taskBuffer)
{
    ncp_task_lite_hdl_t  *taskLiteHdl = val;
    ncp_task_lite_recv_buf_t  *pRecvBuf = (ncp_task_lite_recv_buf_t  *)taskBuffer;    
    
    ncp_task_lite_supply_rxbuffer_to_nca(taskLiteHdl,
	                                     pRecvBuf,
	                                     pRecvBuf->bufferSize);
    
    return;
}

static const char synopsis[] =
    "Usage: ncpTaskRecvLiteLoopback [-i <devNum>] -u<update frequency> -s<sendVpName> -w -c<count> -q<queueSet> -n<nca queueId> \n -u: Number of tasks to process before updating counters\n";


static void
usage(void)
{
    printf(synopsis);
}


#if defined(OSE) && !defined(NCP_CRT_INTERFACE)

#include <shell.h>

static const char desc[] = "";

int
ncpTaskRecvLiteLoopbackMain(int argc, const char * argv[]);

void add_ncpTaskRecvLiteLoopback_cmd(void)
{
    shell_add_cmd_attrs("ncpTaskRecvLiteLoopback", synopsis, desc, (CmdType)ncpTaskRecvLiteLoopbackMain, 
                        OS_PRI_PROC, 16, 16384);
}

#else

#if defined(VXWORKS) || defined(NCP_CRT_INTERFACE)
int
ncpTaskRecvLiteLoopbackMain(int argc, const char * argv[])
#else
int
main(int argc, const char * argv[])
#endif
{
    int c;
    int opt_t = 0;
    ncp_hdl_t ncpHdl = NULL;
    ncp_st_t ncpStatus;
    ncp_uint32_t devNum = 0;
    ncp_task_lite_hdl_t taskLiteHdl=NULL;
    ncp_uint32_t updateFreq=1;
    char sendVpName[100]= {0};
    ncp_uint8_t sendVpId;
    ncp_task_lite_send_meta_t taskLiteMetaData = {0};
    ncp_task_lite_rxQ_hdl_t taskLiteRxHdl = NULL;   
    ncp_bool_t wait = FALSE;
    int queueSetId;
    int ncaQueueId;
    int rxCount=0;

    /* init opt */
    ncp_initopt();

    /* Parse command line arguments */
    while ((c = ncp_getopt(argc, argv, "i:u:s:c:q:n:w")) != EOF)
    {
        switch (c)
        {
        case 'i':
            NCP_ASSERT_LITE((sscanf(ncp_optarg, "%d", &devNum) == 1),
                       NCP_ST_INVALID_PARAMETER);
            break;

        case 'c':
            NCP_ASSERT_LITE((sscanf(ncp_optarg, "%d", &rxCount) == 1),
                       NCP_ST_INVALID_PARAMETER);            
            break;           
            
        case 'n':
            NCP_ASSERT_LITE((sscanf(ncp_optarg, "%d", &ncaQueueId) == 1),
                       NCP_ST_INVALID_PARAMETER);
            break;           
            
       case 'q':
            NCP_ASSERT_LITE((sscanf(ncp_optarg, "%d", &queueSetId) == 1),
                       NCP_ST_INVALID_PARAMETER);                                   
            break;
                       
        case 'u':
            NCP_ASSERT_LITE((sscanf(ncp_optarg, "%d", &updateFreq) == 1),
                       NCP_ST_INVALID_PARAMETER);
            break;
         
        case 's':
            NCP_ASSERT_LITE((sscanf(ncp_optarg, "%s", &sendVpName) == 1),
                       NCP_ST_INVALID_PARAMETER);
            break;

        case 'w':
            wait = TRUE;
            break;
                                
        default:
            usage();
            return(NCP_ST_SUCCESS);
        }
    }


    

    /* Get ncpHdl */
    NCP_CALL_LITE(ncp_config_attach(devNum, &ncpHdl));


    if ('\0' != sendVpName[0])
    {
        ncp_vp_hdl_t vpHdl;
            
        /* Get vpHdl */
        NCP_CALL_LITE(ncp_vp_handle_get(
                 ncpHdl, 0, FALSE, ncp_launch_engine_cpu, sendVpName,
                 &vpHdl));
                
        /* The task-lite interface puts the burden on the client for supplying the vpid */    
        NCP_CALL_LITE(ncp_vp_id_get(vpHdl, &sendVpId));
    }
    else
    {
        printf("Must specify send Vp name\r\n");
        goto ncp_return;
    }    

    /* Create Task-Lite handle */
    NCP_CALL_LITE(ncp_task_lite_hdl_create(ncpHdl,    
                                 (ncp_uint8_t)queueSetId,
                                 &taskLiteHdl));

    /* Create Task-Lite RecvQueue Handle */
    NCP_CALL_LITE(ncp_task_lite_recv_hdl_create(
	        taskLiteHdl,
	        (ncp_uint8_t)ncaQueueId,
	        &taskLiteRxHdl));    
    
    
    
    /* Supply some receive buffers */
    /* NOTE - assumes size 3 == 2048 bytes */
    {
        int i;
        
        for (i=0;i<16; i++)
        {
            ncp_task_lite_recv_buf_t *pTask;
            
            NCP_CALL_LITE(ncp_task_buffer_alloc(2048, &pTask));
            NCP_CALL_LITE(ncp_task_lite_supply_rxbuffer_to_nca( taskLiteHdl,
	                                                            pTask,
	                                                            3));
        }
    }        
    
    
    
    
    /* 
     * Start receiving and looping back tasks 
     */
    {
        ncp_task_lite_send_meta_t taskLiteMetaData; 
        ncp_task_lite_recv_buf_t *task;
        void *taskData;
        int sendFreeThreshold = 0;
        
        /* 
         * Setup static portion of taskIO-lite meta data
         */
        taskLiteMetaData.vpId           = sendVpId;           
        taskLiteMetaData.flowId         = 0;
        taskLiteMetaData.clientFreeFn   = sendCompletionFn;
        taskLiteMetaData.clientFreeFnArg= taskLiteHdl;
        taskLiteMetaData.incTFCxmitCnt  = 0;      
        taskLiteMetaData.debugFieldV    = 0;
        taskLiteMetaData.debugData      = 0;
        
        while(1)
        {
            if (rxCount == 0)
            {
                break; /* done with this queue */
            }        
            ncpStatus = ncp_task_lite_recv(taskLiteHdl, taskLiteRxHdl, &task, &taskData, TRUE);
            if (ncpStatus == NCP_ST_TASK_RECV_QUEUE_EMPTY)
            {
                continue;
            }
            else if (ncpStatus != NCP_ST_SUCCESS)
            {
                NCP_CALL_LITE(ncpStatus)
            }   
            if (task->taskErr ||task->bufferSizeErr)
            { 
                /* just return the buffer to the NCA */
                NCP_CALL_LITE(ncp_task_lite_supply_rxbuffer_to_nca(taskLiteHdl,
                                                              task,
                                                              task->bufferSize));
                continue;                                              
            }    
            if (rxCount != -1)
            {    
                rxCount--;
            }    
            
            taskLiteMetaData.priority = task->taskPrio;            
            taskLiteMetaData.dataSize = task->dataSz;   
            taskLiteMetaData.taskBuffer = task;
            taskLiteMetaData.taskPduData = (void *)NCP_TASK_DATA(task); 

            /* Send task */
            do {
                
                if (NCP_ST_SUCCESS == (ncpStatus = ncp_task_lite_send(
                                taskLiteHdl, &taskLiteMetaData, TRUE)))
                {
                    if (++sendFreeThreshold == 16)
                    {
                        sendFreeThreshold = 0;
                        ncp_task_lite_free_send_buffers(taskLiteHdl);
                    }
                    break;
                }            
                else if (NCP_ST_TASK_SEND_QUEUE_FULL == ncpStatus)
                {
                    /* ncp_sys_usleep(0); */
                    continue;
                }
                else
                {
                    NCP_CALL_LITE(ncpStatus);
                }
            } while(1);   
        } /* while */
    } /* start looping back data */
    
NCP_RETURN_LABEL
    
    /*
     * Make sure final tallies are output
     * Ignore API errors here;  cleanup is best effort.
     */

    if (taskLiteRxHdl)
    {    
        ncp_task_lite_recv_hdl_remove(
            taskLiteHdl,
            taskLiteRxHdl);    
    }    
         
    if (taskLiteHdl)
    {     
        ncp_task_lite_hdl_remove(taskLiteHdl);            
    }    
       
    if (ncpStatus == NCP_ST_INVALID_PARAMETER)
    {
        usage();
    }
    else if (ncpStatus != NCP_ST_SUCCESS)
    {
        printf("Error", ncpStatus);
    }

    if (ncpHdl != NULL) 
    {
        ncp_config_detach(ncpHdl);
    }

    return (int)ncpStatus;
}

#endif /* #ifdef OSE */

/*
 * ncpTaskRecvLiteLoopback
 * 
 * VxWorks entry point.
 */
#if defined(VXWORKS) || defined(NCP_CRT_INTERFACE)
NCP_API int
ncpTaskRecvLiteLoopback(char *cmdArgs)
{
        return ncp_crt("ncpTaskRecvLiteLoopback", cmdArgs,  ncpTaskRecvLiteLoopbackMain);
}
#endif
