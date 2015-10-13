/*
 *  Copyright (C) 2014 LSI (john.jacques@lsi.com)
 *
 * This program is free software;you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation;either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY;without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program;if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __NCP_SYSMEM_LSIPHY_H__
#define __NCP_SYSMEM_LSIPHY_H__

#define NCP_SYSMEM_LSIPHY

/* register definitions for ACP25xx */
#define NCP_SYSMEM_LSIPHY
#include "regs/ncp_phy_regs_acp2500.h"
#include "regs/ncp_phy_reg_defines_acp2500.h"
#include "regs/ncp_denali_regs_acp2500.h"
#include "regs/ncp_denali_reg_defines_acp2500.h"

#ifndef UBOOT
#include "regs/ncp_ddr_regs.h"
#include "regs/ncp_ddr_reg_defines.h"
#else
#define NCP_API
#endif


/*
 * NCP_SM_PHY_REG_RESTORE:
 *   if defined, enable sysmem PHY register save/restore capability
 *   this is required to support the DDR retention feature
 *
 *   TODO: not yet supported for external RTE
 */
#ifdef CONFIG_MEMORY_RETENTION
#define NCP_SM_PHY_REG_RESTORE
#define DDR_PHY_REGS_TAG_SAVE 0x53415645
#define DDR_PHY_REGS_TAG_PROM 0x50524f4d
#define DDR_PHY_REGS_SIZE     128
extern void *retention;
extern unsigned *phyRegs;

#endif

#ifndef UBOOT
/* bindings for RTE build */

extern ncp_uint8_t tRFC_vals_800[];
extern ncp_uint8_t tRFC_vals_667[];

/*
 * sysmem compile time options
 */

/*
 * NCP_SM_PHY_REG_DUMP:
 *   if defined, enable dumping of sysmem PHY registers
 *   upon completion of the sysmem init sequence
 */
#define NCP_SM_PHY_REG_DUMP

/*
 * NCP_SM_WRLVL_DUP
 *   if defined, will only run the write leveling training
 *   on rank0, and will duplicate the write delays for rank1.
 *   This is a workaround for a problem with the original
 *   Odessa board design.
 */
#define NCP_SM_WRLVL_DUP



#define SMAV( regName, regField, newValue ) \
do { \
    regName *tmpMask = (regName *)&mask;\
    regName *tmpValue = (regName *)&value;\
    tmpMask->regField = -1;\
    tmpValue->regField = newValue;\
} while( 0 );

#define SV( regName, regField, newValue ) \
do { \
    regName *tmpValue = (regName *)&value;\
    tmpValue->regField = newValue;\
} while( 0 );

#define acp_failure(a, b, c)

#define ncr_write32(_region, _offset, _value) \
    NCP_CALL(ncp_write32(dev, _region, _offset, _value));

#define ncr_read32(_region, _offset, _value) \
    NCP_CALL(ncp_read32(dev, _region, _offset, _value));

#define ncr_modify32(_region, _offset, _mask, _value) \
    do { \
        ncp_rmw_pair_t rmw_pair;\
        ncp_rmw_t      rmw_buf;\
        rmw_pair.rmw_data = _value;\
        rmw_pair.rmw_mask = _mask;\
        rmw_buf.count = 1;\
        rmw_buf.rmw_buffer = &rmw_pair;\
        NCP_CALL(ncp_read_modify_write(dev, _region, _offset, &rmw_buf, 0));\
    } while (0);

#define ncr_poll(_region, _offset, _mask, _value, _dly, _lp) \
    ncp_poll(dev, _region, _offset, _mask, _value, _dly, _lp)

#define NCP_SM_POLL_FOR_OP_DONE(_region) \
    NCP_CALL(ncp_sm_lsiphy_poll_for_op_done(dev, _region));

#define NCR_TRACE(args...)

#else

#include <asm/io.h>

/* bindings for UBOOT built */

typedef long long               ncp_int64_t;
typedef unsigned long long      ncp_uint64_t;
typedef unsigned                ncp_uint32_t;
typedef long                    ncp_int32_t;
typedef unsigned short          ncp_uint16_t;
typedef unsigned char           ncp_uint8_t;
typedef unsigned char           ncp_bool_t;
typedef void *                  ncp_dev_hdl_t;
typedef unsigned                ncp_st_t;
typedef unsigned                ncp_region_id_t;

typedef ncp_uint32_t
(*ncp_sm_intr_status_fn_t) (
    ncp_dev_hdl_t   dev,
    ncp_region_id_t regionId,
    ncp_uint32_t    mask);

typedef ncp_st_t
(*ncp_sm_poll_controller_fn_t) (
    ncp_dev_hdl_t   dev,
    ncp_region_id_t regionId,
    ncp_sm_poll_event_t event);


typedef ncp_uint32_t
(*ncp_sm_ecc_enb_fn_t) (
    ncp_dev_hdl_t   dev,
    ncp_region_id_t regionId,
    ncp_uint32_t    value);



typedef parameters_mem_t     ncp_sm_parms_t;

#define TRUE   (1)
#define FALSE  (0)
#define NCP_RETURN_LABEL goto ncp_return;ncp_return:
#define NCP_DEV_BUS_FBRS 0xdead

#include "ncp_sysmem_ext.h"

/* TODO : don't need all this checking for u-boot */
#define NCP_SYSMEM_NUM_NODES 2
#define NCP_EXTMEM_NUM_NODES 4


enum {
    NCP_ST_SUCCESS = 0,
    NCP_ST_ERROR,
    NCP_ST_SYSMEM_INVALID_ID,
    NCP_ST_SYSMEM_PHY_CPC_CAL_TIMEOUT,
    NCP_ST_SYSMEM_PHY_TRAIN_TIMEOUT,
    NCP_ST_SYSMEM_PHY_TRAIN_SW_TIMEOUT,
    NCP_ST_SYSMEM_PHY_WL_ERR,
    NCP_ST_SYSMEM_PHY_WL_DLY_ERR,
    NCP_ST_SYSMEM_PHY_ECC_WL_ERR,
    NCP_ST_SYSMEM_PHY_ECC_WL_DLY_ERR,
    NCP_ST_SYSMEM_PHY_RDFIFO_OPT_ERR,
    NCP_ST_SYSMEM_PHY_CPC_ERR,
    NCP_ST_SYSMEM_PHY_RD_DLY_ERR,
    NCP_ST_SYSMEM_PHY_RD_CAL_ERR,
    NCP_ST_SYSMEM_PHY_WR_LVL_ERR,
    NCP_ST_SYSMEM_PHY_RD_LVL_ERR,
    NCP_ST_SYSMEM_PHY_GT_TRN_ERR,
    NCP_ST_SYSMEM_PHY_CMD_DLY_ERR
};

#define NCP_CALL(s) \
    ncpStatus = (s);\
    if (ncpStatus != NCP_ST_SUCCESS) { \
        printf("ncpStatus=%d\n", (int) ncpStatus);\
        printf("%s:%s:%d\n", \
              __FILE__, __FUNCTION__, __LINE__);\
        goto ncp_return;\
    }


#define NCP_SM_POLL_FOR_OP_DONE(_region) \
    do { \
        ncp_denali_DENALI_CTL_13_t ctl_13_mask = { 0 };\
        ncp_denali_DENALI_CTL_13_t ctl_13_value = { 0 };\
        ctl_13_mask.swlvl_op_done = 1;\
        ctl_13_value.swlvl_op_done = 1;\
        mb();\
        if (0 != ncr_poll(ctlRegion, NCP_DENALI_CTL_13, \
                  *((unsigned long *)&ctl_13_mask), \
                  *((unsigned long *)&ctl_13_value), \
                  10, 100)) { \
            NCR_TRACE("%s:%s:%d\n", \
                  __FILE__, __FUNCTION__, __LINE__);\
            return -1;\
        } \
    } while (0);

#define ncp_status_print(a, b)


#endif

#ifdef NCP_BIG_ENDIAN
#define NCP_SM_SWAP32(n) ((n & 0xff000000) >> 24 | \
                                    (n & 0x00ff0000) >> 8  | \
                                    (n & 0x0000ff00) << 8  | \
                                    (n & 0x000000ff) << 24)

#else
#define NCP_SM_SWAP32(n) (n)
#endif

#define NCP_SYSMEM_PHY_TRAIN_DELAY_LOOPS 100
#define NCP_SYSMEM_PHY_TRAIN_DELAY_USEC  10

#define NCP_SM_DENALI_V1_ECC_INTR_BITS 0x3c
#define NCP_SM_DENALI_V1_ERROR_INTR_BITS 0x3feff

#define NCP_SM_DENALI_V2_ECC_INTR_BITS 0x78
#define NCP_SM_DENALI_V2_ERROR_INTR_BITS 0x7fdff

#define NCP_SM_NUM_BYTE_LANES 5
#define NCP_CM_NUM_BYTE_LANES 2

typedef enum {
    NCP_SM_PHY_ADR_IMP_50_OHM = 0,
    NCP_SM_PHY_ADR_IMP_43_OHM = 1,
    NCP_SM_PHY_ADR_IMP_37_OHM = 2,
    NCP_SM_PHY_ADR_IMP_33_OHM = 3
} ncp_sm_phy_adr_imp_t;

typedef enum {
    NCP_SM_PHY_DAT_IMP_50_OHM = 0,
    NCP_SM_PHY_DAT_IMP_43_OHM = 1,
    NCP_SM_PHY_DAT_IMP_37_OHM = 2,
    NCP_SM_PHY_DAT_IMP_33_OHM = 3
} ncp_sm_phy_dat_imp_t;

typedef enum {
    NCP_SM_PHY_RCV_IMP_150_OHM = 0,
    NCP_SM_PHY_RCV_IMP_75_OHM = 1,
    NCP_SM_PHY_RCV_IMP_50_OHM = 2
} ncp_sm_phy_rcv_imp_t;

/*
 * we define all per-bytelane structures large enough to handle
 * either system or classifier memory.
 */

typedef struct {
    ncp_uint16_t    upper;
    ncp_uint16_t    lower;
} ncp_nibble_t;


typedef struct {
    ncp_phy_CFG_SYSMEM_PHY_GTTRAINSTAT0_r_t stat0;
    ncp_phy_CFG_SYSMEM_PHY_GTTRAINSTAT1_r_t stat1;
} ncp_sm_lsiphy_gttrn_stat_t;


typedef struct {
    ncp_phy_CFG_SYSMEM_PHY_RDLVLSTATNEDGE_r_t   nedge;
    ncp_phy_CFG_SYSMEM_PHY_RDLVLSTATPEDGE_r_t   pedge;
    ncp_phy_CFG_SYSMEM_PHY_RDDSKWSTAT_r_t       dskew;
    ncp_phy_CFG_SYSMEM_PHY_RDDSKWFATALSTAT_r_t  dskew_fatal;
} ncp_sm_lsiphy_rdlvl_stat_t;


typedef struct {
    ncp_phy_CFG_SYSMEM_PHY_WRLVLSMSTAT_r_t stat;

} ncp_sm_lsiphy_wrlvl_stat_t;

typedef struct {
    ncp_phy_CFG_SYSMEM_PHY_STAT_r_t   phyStat;
    ncp_sm_lsiphy_gttrn_stat_t  gttrn;
    ncp_sm_lsiphy_rdlvl_stat_t  rdlvl;
    ncp_sm_lsiphy_wrlvl_stat_t  wrlvl;
} ncp_sm_lsiphy_stat_t;

NCP_API ncp_st_t
ncp_sm_phy_errs(
        ncp_dev_hdl_t dev,
        ncp_uint32_t  smId);

NCP_API ncp_st_t
ncp_sm_lsiphy_static_init(
        ncp_dev_hdl_t   dev,
        ncp_uint32_t    smId,
        ncp_sm_parms_t *parms);

NCP_API ncp_st_t
ncp_sm_phy_training_setup(
        ncp_dev_hdl_t   dev,
        ncp_uint32_t  smId,
        ncp_sm_parms_t *parms);

NCP_API ncp_st_t
ncp_sm_phy_training_run(
        ncp_dev_hdl_t               dev,
        ncp_uint32_t                smId,
        ncp_uint32_t                rank,
        ncp_sm_phy_training_mode_t  mode,
	ncp_sm_parms_t             *parms);

NCP_API ncp_st_t
ncp_sm_lsiphy_coarse_write_leveling(
        ncp_dev_hdl_t   dev,
        ncp_uint32_t    smId,
        ncp_uint32_t    rank,
        ncp_uint64_t    addr,
        ncp_sm_parms_t *parms);

NCP_API ncp_st_t
ncp_sm_lsiphy_runtime_adj(
        ncp_dev_hdl_t   dev,
        ncp_uint32_t    smId,
        ncp_sm_parms_t *parms);

NCP_API ncp_st_t
ncp_sm_lsiphy_status_get(
        ncp_dev_hdl_t dev,
        ncp_uint32_t  smId,
        ncp_sm_lsiphy_stat_t *stat);

NCP_API ncp_st_t
ncp_sm_lsiphy_reg_dump(
        ncp_dev_hdl_t dev,
        ncp_uint32_t  smId,
        ncp_uint32_t  chipType);

NCP_API ncp_st_t
ncp_sm_lsiphy_training_run(
        ncp_dev_hdl_t               dev,
        ncp_uint32_t                smId,
        ncp_uint32_t                rank,
        ncp_uint32_t                edge,
        ncp_sm_phy_training_mode_t  mode,
        ncp_sm_parms_t             *parms);

NCP_API ncp_st_t
ncp_sm_lsiphy_gate_training(
        ncp_dev_hdl_t               dev,
        ncp_uint32_t                smId,
        ncp_uint32_t                rank,
        ncp_sm_parms_t             *parms);

NCP_API ncp_st_t
ncp_sm_denali_2041_init(
        ncp_dev_hdl_t   dev,
        ncp_uint32_t    smId,
        ncp_sm_parms_t *parms);

NCP_API ncp_st_t
ncp_sm_dimm_spd_query(
        ncp_dev_hdl_t       dev,
        ncp_sm_parms_t     *parms);


#endif
