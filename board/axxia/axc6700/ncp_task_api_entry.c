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

/* #include "ncp_dev_pvt.h" */
#if 0 /* UBOOT */
#include "ncp_dev.h"
#include "ncp_release_id.h"
#endif

#include "ncp_task_pvt.h"
#include "ncp_task_api_entry.h"


NCP_EXPORT_SYMBOL(ncp_task_get_default_queueset);
NCP_EXPORT_SYMBOL(ncp_task_hdl_create);
NCP_EXPORT_SYMBOL(ncp_task_hdl_remove);
NCP_EXPORT_SYMBOL(ncp_task_recv_queue_bind);
NCP_EXPORT_SYMBOL(ncp_task_recv_queue_unbind);
NCP_EXPORT_SYMBOL(ncp_task_recv_queue_vp_bind);
NCP_EXPORT_SYMBOL(ncp_task_recv_queue_vp_unbind);
NCP_EXPORT_SYMBOL(ncp_task_recv);
NCP_EXPORT_SYMBOL(ncp_task_completion_queue_flush);
NCP_EXPORT_SYMBOL(ncp_task_recv_done);
NCP_EXPORT_SYMBOL(ncp_task_send);
NCP_EXPORT_SYMBOL(ncp_task_send_segments);
NCP_EXPORT_SYMBOL(ncp_task_send_queue_flush);
NCP_EXPORT_SYMBOL(ncp_task_buffer_alloc);
NCP_EXPORT_SYMBOL(ncp_task_buffer_free);


ncp_st_t
ncp_task_get_default_queueset(
    ncp_hdl_t       ncpHdl,
    ncp_uint8_t     *pThreadQueueSetId)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    NCP_CALL(ncp_task_v2_get_default_queueset(ncpHdl,
                                                   pThreadQueueSetId));
NCP_RETURN_LABEL
    return ncpStatus;
}

ncp_st_t
ncp_task_hdl_create(
    ncp_hdl_t       ncpHdl,
    ncp_uint8_t     threadQueueSetId,
    ncp_bool_t      shared,
    ncp_bool_t      orderedTaskCompletion,
    ncp_task_hdl_t  *taskHdl)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;

    NCP_CALL(ncp_task_v2_hdl_create(ncpHdl,
                                         threadQueueSetId,
                                         shared,
                                         taskHdl));
NCP_RETURN_LABEL
    return ncpStatus;
}

ncp_st_t
ncp_task_hdl_remove(
	ncp_task_hdl_t taskHdl)
{
    ncp_st_t ncpStatus= NCP_ST_SUCCESS;

    NCP_CALL(ncp_task_v2_hdl_remove(taskHdl));

NCP_RETURN_LABEL
    return ncpStatus;
}

ncp_st_t
ncp_task_recv_queue_bind(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t ncaQueueId,
	ncp_uint8_t weight,
	ncp_bool_t shared,
	ncp_bool_t fixedRecvQueueId,
	ncp_uint8_t *pRecvQueueId)
{
    ncp_st_t ncpStatus= NCP_ST_SUCCESS;

    NCP_CALL(ncp_task_v2_recv_queue_bind(taskHdl,
	                                            ncaQueueId,
	                                            weight,
	                                            shared,
	                                            fixedRecvQueueId,
	                                            pRecvQueueId));
NCP_RETURN_LABEL
    return ncpStatus;
}

ncp_st_t
ncp_task_recv_queue_unbind(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t recvQueueId)
{
    ncp_st_t ncpStatus= NCP_ST_SUCCESS;

        NCP_CALL(ncp_task_v2_recv_queue_unbind(taskHdl,
	                                            recvQueueId));
NCP_RETURN_LABEL
    return ncpStatus;
}

ncp_st_t
ncp_task_recv_queue_vp_bind(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t recvQueueId,
	ncp_vp_hdl_t vpHdl,
	ncp_uint8_t engineSequenceId,
	ncp_bool_t shared,
	ncp_task_recv_fn_t recvFunc,
	void *recvFuncArg)
{
    ncp_st_t ncpStatus= NCP_ST_SUCCESS;

    NCP_CALL(ncp_task_v2_recv_queue_vp_bind(taskHdl,
	                                                recvQueueId,
	                                                vpHdl,
	                                                engineSequenceId,
	                                                shared,
	                                                recvFunc,
	                                                recvFuncArg));

NCP_RETURN_LABEL
    return ncpStatus;
}


ncp_st_t
ncp_task_recv_queue_vp_unbind(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t recvQueueId,
	ncp_vp_hdl_t vpHdl,
	ncp_uint8_t engineSequenceId)
{
    ncp_st_t ncpStatus= NCP_ST_SUCCESS;

    NCP_CALL(ncp_task_v2_recv_queue_vp_unbind(taskHdl,
	                                                recvQueueId,
	                                                vpHdl,
	                                                engineSequenceId));
NCP_RETURN_LABEL
    return ncpStatus;
}

ncp_st_t
ncp_task_recv(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t *pRecvQueueId,
	ncp_vp_hdl_t *pVpHdl,
	ncp_uint8_t *pEngineSequenceId,
	ncp_task_recv_buf_t **task,
	void                **taskData,
    void **recvHandlerArg,
	ncp_bool_t wait)
{
    ncp_st_t ncpStatus;

    ncpStatus = ncp_task_v2_legacy_recv(taskHdl,
	                                pRecvQueueId,
	                                pVpHdl,
	                                pEngineSequenceId,
	                                task,
	                                taskData,
                                    recvHandlerArg,
	                                wait);

	if (NCP_ST_SUCCESS != ncpStatus)
	{
	    if ((NCP_ST_TASK_RECV_QUEUE_EMPTY != ncpStatus)
	     && (NCP_ST_TASK_DISPATCHED != ncpStatus))
	    {
	        NCP_CALL(ncpStatus);
	    }
	}
NCP_RETURN_LABEL
    return ncpStatus;
}



ncp_st_t
ncp_task_completion_queue_flush(
	ncp_task_hdl_t taskHdl,
    ncp_bool_t wait,
    ncp_bool_t *pQueueStatus)
{
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;

    NCP_CALL(ncp_task_v2_completion_queue_flush(taskHdl,
                                                        wait,
                                                        pQueueStatus));
NCP_RETURN_LABEL
    return(ncpStatus);
}

ncp_st_t
ncp_task_recv_done(
	ncp_task_hdl_t taskHdl,
	ncp_task_recv_buf_t *task)
{
    ncp_st_t ncpStatus= NCP_ST_SUCCESS;

    NCP_CALL(ncp_task_v2_recv_done(taskHdl,
	                                    task));
NCP_RETURN_LABEL
    return ncpStatus;
}

ncp_st_t
ncp_task_send_queue_flush(
	ncp_task_hdl_t taskHdl,
    ncp_bool_t wait,
    ncp_bool_t *pQueueStatus)
{
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;

    NCP_CALL(ncp_task_v2_send_queue_flush(taskHdl,
                                                wait,
                                                pQueueStatus));
NCP_RETURN_LABEL
    return(ncpStatus);
}

ncp_st_t
ncp_task_send(
	ncp_task_hdl_t        taskHdl,
	ncp_vp_hdl_t vpHdl,
	ncp_task_send_meta_t *clientTaskMetaData,
	void *taskBuffer,
	void *taskPduData,
	ncp_bool_t wait,
	ncp_task_send_done_fn_t sendDoneFn,
	void                    *sendDoneFuncArg)
{
    ncp_st_t ncpStatus;

    ncpStatus = ncp_task_v2_legacy_send(taskHdl,
	                                vpHdl,
	                                clientTaskMetaData,
	                                taskBuffer,
	                                taskPduData,
	                                wait,
	                                sendDoneFn,
	                                sendDoneFuncArg);

	if (NCP_ST_SUCCESS != ncpStatus)
	{
	    if (NCP_ST_TASK_SEND_QUEUE_FULL != ncpStatus)
	    {
	        NCP_CALL(ncpStatus);
	    }
	}

NCP_RETURN_LABEL
    return ncpStatus;
}

ncp_st_t
ncp_task_send_segments(
	ncp_task_hdl_t       taskHdl,
	ncp_vp_hdl_t         vpHdl,
	ncp_task_send_meta_t *clientTaskMetaData,
	ncp_uint8_t          numSegs,
    ncp_task_segment_entry_t    *pSegTable,
	ncp_bool_t                  wait,
	ncp_task_send_done_fn_t     sendDoneFn,
	void                        *sendDoneFuncArg)
{
    ncp_st_t ncpStatus;

    ncpStatus = ncp_task_v2_send_segments(taskHdl,
	                                        vpHdl,
	                                        clientTaskMetaData,
						numSegs,
                                            pSegTable,
	                                        wait,
	                                        sendDoneFn,
	                                        sendDoneFuncArg);
	if (NCP_ST_SUCCESS != ncpStatus)
	{
	    if (NCP_ST_TASK_SEND_QUEUE_FULL != ncpStatus)
	    {
	        NCP_CALL(ncpStatus);
	    }
	}

NCP_RETURN_LABEL
    return ncpStatus;
}


ncp_st_t
ncp_task_buffer_alloc (
	ncp_uint32_t size,
	void **taskAddr)
{
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;

    ncp_task_hdl_t *taskHdl=NULL;

    NCP_CALL(ncp_task_v2_get_taskHdl((void *)&taskHdl));
    NCP_CALL(ncp_task_ncav2_buffer_alloc( taskHdl,
                                           size,
	                                       taskAddr));

NCP_RETURN_LABEL
    return(ncpStatus);
}


ncp_st_t
ncp_task_buffer_free (
	void *taskAddr)
{
    ncp_st_t ncpStatus=NCP_ST_SUCCESS;

    ncp_task_hdl_t *taskHdl=NULL;

    NCP_CALL(ncp_task_v2_get_taskHdl((void *)&taskHdl));
    NCP_CALL(ncp_task_ncav2_buffer_free(taskHdl,
                                         taskAddr));

NCP_RETURN_LABEL
    return(ncpStatus);
}


