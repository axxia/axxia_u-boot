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

#ifndef __ncp_task_api_entry_h__
#define __ncp_task_api_entry_h__

/* UBOOT */ /* DELETED v1 entry points */

/* ===============================================================
 * ACP55xx forward defines
 * ===============================================================
 */

ncp_st_t
ncp_task_v2_get_default_queueset(
    ncp_hdl_t       ncpHdl,
    ncp_uint8_t     *pThreadQueueSetId);

ncp_st_t
ncp_task_v2_hdl_create(
    ncp_hdl_t       ncpHdl,
    ncp_uint8_t     threadQueueSetId,
    ncp_bool_t      shared,
    ncp_task_hdl_t  *taskHdl);

ncp_st_t
ncp_task_v2_hdl_remove(
	ncp_task_hdl_t taskHdl);

ncp_st_t
ncp_task_v2_send_mutex_disable(
	ncp_task_hdl_t taskHdl);

ncp_st_t
ncp_task_v2_recv_queue_bind(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t ncaQueueId,
	ncp_uint8_t weight,
	ncp_bool_t shared,
	ncp_bool_t fixedRecvQueueId,
	ncp_uint8_t *pRecvQueueId);

ncp_st_t
ncp_task_v2_recv_queue_unbind(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t recvQueueId);

ncp_st_t
ncp_task_v2_recv_queue_vp_bind(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t recvQueueId,
	ncp_vp_hdl_t vpHdl,
	ncp_uint8_t engineSequenceId,
	ncp_bool_t shared,
	ncp_task_recv_fn_t recvFunc,
	void *recvFuncArg);

ncp_st_t
ncp_task_v2_recv_queue_vp_unbind(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t recvQueueId,
	ncp_vp_hdl_t vpHdl,
	ncp_uint8_t engineSequenceId);


ncp_st_t
ncp_task_v2_legacy_recv(
	ncp_task_hdl_t taskHdl,
	ncp_uint8_t *pRecvQueueId,
	ncp_vp_hdl_t *pVpHdl,
	ncp_uint8_t *pEngineSequenceId,
	ncp_task_recv_buf_t **task,
	void                **taskData,
    void **recvHandlerArg,
	ncp_bool_t wait);

ncp_st_t
ncp_task_v2_completion_queue_flush(
	ncp_task_hdl_t taskHdl,
    ncp_bool_t wait,
    ncp_bool_t *pQueueStatus);

ncp_st_t
ncp_task_v2_recv_done(
	ncp_task_hdl_t taskHdl,
	ncp_task_recv_buf_t *task);

ncp_st_t
ncp_task_v2_send_queue_flush(
	ncp_task_hdl_t taskHdl,
    ncp_bool_t wait,
    ncp_bool_t *pQueueStatus);

ncp_st_t
ncp_task_v2_legacy_send(
	ncp_task_hdl_t        taskHdl,
	ncp_vp_hdl_t vpHdl,
	ncp_task_send_meta_t *clientTaskMetaData,
	void *taskBuffer,
	void *taskPduData,
	ncp_bool_t wait,
	ncp_task_send_done_fn_t sendDoneFn,
	void                    *sendDoneFuncArg);

ncp_st_t
ncp_task_v2_send_segments(
	ncp_task_hdl_t       taskHdl,
	ncp_vp_hdl_t         vpHdl,
	ncp_task_send_meta_t *clientTaskMetaData,
	ncp_uint8_t          numSegs,
    ncp_task_segment_entry_t    *pSegTable,
	ncp_bool_t                  wait,
	ncp_task_send_done_fn_t     sendDoneFn,
	void                        *sendDoneFuncArg);



NCP_API ncp_st_t
ncp_task_v2_reset_stats(ncp_hdl_t ncpHdl );


NCP_API ncp_st_t
ncp_task_v2_get_stats(	ncp_hdl_t ncpHdl,
                        ncp_task_stats_t *pStats);

ncp_st_t
ncp_task_v2_shutdown(ncp_uint32_t devNum);

ncp_st_t
ncp_task_v2_shutdown_wait(
    ncp_hdl_t   ncpHdl);

ncp_st_t
ncp_task_v2_attach_to_gsm(ncp_hdl_t ncpHdl, void **ppGSM, void **ppTaskGSM);

#if 0 /* UBOOT */
ncp_st_t
ncp_task_v2_get_taskHdl(ncp_pvt_task_hdl_t **myTaskHdl);

ncp_st_t
ncp_nca_v2_bp_dest_val_get(ncp_hdl_t ncpHdl, ncp_uint8_t destBit,
                        ncp_bool_t *destVal);

ncp_st_t
ncp_nca_v2_bp_state_get(ncp_hdl_t ncpHdl, ncp_uint32_t *bpState);

ncp_st_t
ncp_task_v2_config(ncp_t         *ncp, ncp_map_t     *map);

ncp_st_t
ncp_task_v2_warm_config(ncp_t    *ncp, ncp_map_t     *map);

ncp_st_t
ncp_task_v2_destroy(ncp_t *ncp);
#endif /* UBOOT */

#endif  /* __ncp_task_api_entry_h__ */
