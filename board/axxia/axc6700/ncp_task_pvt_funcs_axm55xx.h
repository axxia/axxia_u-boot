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

#ifndef __ncp_task_pvt_funcs_axm55xx_h__
#define __ncp_task_pvt_funcs_axm55xx_h__

/* ================================================================
 * Common across acp34xx platforms; hardware, socket, etc...
 * Forward and external function declarations
 * ================================================================
 */

ncp_st_t
ncp_task_v2_config(ncp_t         *ncp,
                    ncp_map_t     *map);

ncp_st_t
ncp_task_v2_warm_config(ncp_t         *ncp,
                    ncp_map_t     *map);

ncp_st_t
ncp_task_v2_destroy(ncp_t *ncp);

ncp_st_t
ncp_task_v2_mmap_attach(ncp_dev_hdl_t devHdl,
                        void **pDomainBundle,
                        ncp_task_ncaV2_t **pTaskSwState);

#if 0 /* UBOOT */
ncp_st_t
ncp_task_v2_get_taskHdl(ncp_task_hdl_t **taskHdl);
#endif

ncp_st_t
ncp_task_v2_output_queueset_bind(
    ncp_pvt_task_hdl_t  *myTaskHdl,
    ncp_bool_t          shared,
    ncp_uint8_t         ncaOutputQueueId);

ncp_st_t
ncp_task_v2_output_queueset_unbind(
    ncp_pvt_task_hdl_t  *myTaskHdl);

ncp_st_t ncp_task_v2_find_recv_queue(ncp_pvt_task_hdl_t *taskHdl, ncp_uint8_t recvQueueId, ncp_pvt_task_recv_queue_t **recvQueue);

ncp_st_t ncp_task_v2_validate_input_queue_binding(ncp_task_pcq_t *pcq);

ncp_st_t ncp_task_v2_initialize_sw_task_input_queue(ncp_pvt_task_hdl_t *taskHdl, ncp_pvt_task_recv_queue_t *recvQueuePtr, ncp_task_pcq_t *pcq,
ncp_bool_t fixedRecvQueueId, ncp_uint8_t *pRecvQueueId);

ncp_st_t ncp_task_v2_map_queuenum_to_pcq(ncp_task_pcq_type_t qType, ncp_uint8_t queueNum, ncp_task_pcq_t   **ppcq);

ncp_st_t ncp_task_v2_set_nca_load_indexes_reg(ncp_dev_hdl_t dev, ncp_uint8_t activeGrpMask);

ncp_st_t ncp_task_v2_set_nca_poke_and_timer_enable_reg(ncp_dev_hdl_t dev,
                                ncp_uint8_t hw_load_poke_enab,
                                ncp_uint8_t hw_upload_pore_enab,
                                ncp_uint8_t cpcq_poke_enable,
                                ncp_uint8_t tpcq_poke_enable,
                                ncp_uint8_t opcq_poke_enable,
                                ncp_uint8_t ipcq_poke_enable,
                                ncp_uint8_t grpMask,
                                ncp_uint8_t grp_load_enab,
                                ncp_uint8_t grp_upload_enab);

ncp_st_t
ncp_task_v2_set_nca_config_init_reg(
     ncp_dev_hdl_t    dev,
     ncp_uint8_t      itask_end_data_fill_off,
     ncp_uint8_t      cfg_ring_ack_timer_en,
     ncp_uint8_t      cpcq_en,
     ncp_uint8_t      otask_accum_en,
     ncp_uint8_t      itask_accum_en,
     ncp_uint8_t      otbp_soft_reset,
     ncp_uint8_t      mpbf_en,
     ncp_uint8_t      otbp_ext_mem_wen,
     ncp_uint8_t      cpcq_exec_disable,
     ncp_uint8_t      opcq_num_ent_per_req_m1,
     ncp_uint8_t      ota_num_beat,
     ncp_uint8_t      ita_num_beat,
     ncp_uint8_t      pgit_w_num_beat,
     ncp_uint8_t      pgit_r_num_beat);

ncp_st_t
ncp_task_v2_nca_warm_restart(ncp_hdl_t ncpHdl,
                        ncp_dev_hdl_t dev,
                        ncp_nca_t *nca);

ncp_st_t
ncp_task_v2_set_rbp_backpressure(ncp_dev_hdl_t dev, ncp_bool_t enable, ncp_uint32_t iPCQmask, ncp_uint32_t bSizeMask);

ncp_st_t
ncp_nca_alloc_bind_tables(ncp_nca_t *nca, int num_iPCQs);

ncp_st_t ncp_task_v2_config_hw(ncp_hdl_t ncpHdl, ncp_dev_hdl_t dev, ncp_nca_t *nca, ncp_bool_t warmRestart);

ncp_st_t
ncp_task_v2_kmode_phase2_config_hw(ncp_hdl_t ncpHdl,
                                   ncp_dev_hdl_t dev,
                                   ncp_nca_t *nca,
                                   ncp_bool_t warmRestart);

ncp_st_t
ncp_task_v2_config_free(ncp_nca_t *nca);

ncp_st_t
ncp_task_destroy_mutexes(ncp_nca_t *nca);

NCP_API ncp_st_t
ncp_task_attach_to_gsm(ncp_hdl_t ncpHdl,
                       void **pDomainBundle,
                       void **pTaskSwState);


void nca_task_v1_display_task_stats(void);

void
ncp_task_v2_check_onNca(void *taskAddr, int poolID);

void
ncp_task_v2_add_onNca(void *taskAddr, int poolID);

void
ncp_task_v2_del_onNca(void *taskAddr, int poolID);

void
ncp_task_v2_validate_buffer(void *taskAddr, int alloc, int poolID);

ncp_uint64_t
ncp_task_v2_va_2_pa(void * VA, int poolID);

void *
ncp_task_v2_pa_2_va(ncp_uint32_t high32, ncp_uint32_t low32, int poolID);


void
ncp_dev_nca_free(ncp_dev_hdl_t dev);

ncp_st_t ncp_task_v2_link_queue_to_taskHdl(ncp_pvt_task_hdl_t  *myTaskHdl,
                                 ncp_task_pcq_t  **pSwQueue,
                                 ncp_task_pcq_type_t type,
                                 ncp_uint8_t ncaQueueId);
void ncp_task_v2_unlink_queue_from_taskHdl(ncp_task_pcq_t * pQ);


ncp_st_t
ncp_task_v2_init_cpu_pools(
        ncp_dev_hdl_t   dev,
        ncp_nca_t       *nca);

void
ncp_task_v2_breakpoint(int reason);


#endif /* __ncp_task_pvt_funcs_acp34xx_h__ */
