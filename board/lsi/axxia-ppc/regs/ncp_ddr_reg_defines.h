/**************************************************************************
 **                                                                       *
 **    Copyright (c) 2001-2013, Intel Corporation.                     .    *
 **                                                                       *
 **************************************************************************/



#ifndef _NCP_DDR_REG_DEFINES_H_
#define _NCP_DDR_REG_DEFINES_H_

#ifdef __cplusplus
extern "C" {
#endif


    /* NODE 0x9 , TARGET 0x9*/


#define     NCP_DDR_NTEMC_DDR_APB_BRIDGE_STATUS                 (0x00000000)
#define     NCP_DDR_CFG_NTEMC_DDR_CTRL                          (0x00000004)
#define     NCP_DDR_CFG_NTEMC_DDR_STATUS                        (0x00000008)
#define     NCP_DDR_CFG_NTEMC_DESL                              (0x0000000c)
#define     NCP_DDR_CFG_NTEMC_MRS                               (0x00000010)
#define     NCP_DDR_CFG_NTEMC_ISSUE_MRS                         (0x00000014)
#define     NCP_DDR_CFG_NTEMC_DRAM_TYPE                         (0x00000018)
#define     NCP_DDR_CFG_NTEMC_SPECVAL1                          (0x0000001c)
#define     NCP_DDR_CFG_NTEMC_SPECVAL2                          (0x00000020)
#define     NCP_DDR_CFG_NTEMC_SPECVAL3                          (0x00000024)
#define     NCP_DDR_CFG_NTEMC_SPECVAL4                          (0x00000028)
#define     NCP_DDR_CFG_NTEMC_DFI_TIMING1                       (0x0000002c)
#define     NCP_DDR_CFG_NTEMC_DFI_TIMING2                       (0x00000030)
#define     NCP_DDR_CFG_NTEMC_DFI_TIMING3                       (0x00000034)
#define     NCP_DDR_CFG_NTEMC_DFI_TIMING4                       (0x00000038)
#define     NCP_DDR_CFG_NTEMC_DFI_TIMING5                       (0x0000003c)
#define     NCP_DDR_RD_STATE_FIFO_STAT                          (0x00000040)
#define     NCP_DDR_WR_STATE_FIFO_STAT                          (0x00000044)
#define     NCP_DDR_CFG_NTEMC_ECC_CTRL                          (0x00000048)
#define     NCP_DDR_CFG_NTEMC_FRCD_ERR_ADDR                     (0x0000004c)
#define     NCP_DDR_CFG_NTEMC_AXI_ECC_ERR_ADDR                  (0x00000050)
#define     NCP_DDR_CFG_NTEMC_CFG_ECC_ERR_ADDR                  (0x00000054)
#define     NCP_DDR_CFG_NTEMC_SCRUB_ECC_ERR_ADDR                (0x00000058)
#define     NCP_DDR_CFG_NTEMC_AXI_ECC_ERR_SYNU                  (0x0000005c)
#define     NCP_DDR_CFG_NTEMC_AXI_ECC_ERR_SYNL                  (0x00000060)
#define     NCP_DDR_CFG_NTEMC_CFG_ECC_ERR_SYNU                  (0x00000064)
#define     NCP_DDR_CFG_NTEMC_CFG_ECC_ERR_SYNL                  (0x00000068)
#define     NCP_DDR_CFG_NTEMC_SCRUB_ECC_ERR_SYNU                (0x0000006c)
#define     NCP_DDR_CFG_NTEMC_SCRUB_ECC_ERR_SYNL                (0x00000070)
#define     NCP_DDR_CFG_NTEMC_HW_TEST_CTRL                      (0x00000074)
#define     NCP_DDR_CFG_NTEMC_HW_TEST_DATA_UPR                  (0x00000078)
#define     NCP_DDR_CFG_NTEMC_HW_TEST_DATA_LWR                  (0x0000007c)
#define     NCP_DDR_CFG_SCRUB_ADDR                              (0x00000080)
#define     NCP_DDR_CFG_NTEMC_LD_SCRUB                          (0x00000084)
#define     NCP_DDR_CFG_NTEMC_LD_HWTESTWRT                      (0x00000088)
#define     NCP_DDR_CFG_NTEMC_DDR_SM_STATUS                     (0x0000008c)
#define     NCP_DDR_CFG_NTEMC_HWTEST_FAILADDR                   (0x00000090)
#define     NCP_DDR_CFG_NTEMC_HWTEST_FAILEXPU                   (0x00000094)
#define     NCP_DDR_CFG_NTEMC_HWTEST_FAILEXPL                   (0x00000098)
#define     NCP_DDR_CFG_NTEMC_HWTEST_FAILACTU                   (0x0000009c)
#define     NCP_DDR_CFG_NTEMC_HWTEST_FAILACTL                   (0x000000a0)
#define     NCP_DDR_CFG_NTEMC_PHY_DEBUG_STATUS                  (0x000000a4)
#define     NCP_DDR_CFG_NTEMC_LOGBANK0DEPTH                     (0x00000100)
#define     NCP_DDR_CFG_NTEMC_LOGBANK1DEPTH                     (0x00000104)
#define     NCP_DDR_CFG_NTEMC_LOGBANK2DEPTH                     (0x00000108)
#define     NCP_DDR_CFG_NTEMC_LOGBANK3DEPTH                     (0x0000010c)
#define     NCP_DDR_CFG_NTEMC_LOGBANK4DEPTH                     (0x00000110)
#define     NCP_DDR_CFG_NTEMC_LOGBANK5DEPTH                     (0x00000114)
#define     NCP_DDR_CFG_NTEMC_LOGBANK6DEPTH                     (0x00000118)
#define     NCP_DDR_CFG_NTEMC_LOGBANK7DEPTH                     (0x0000011c)
#define     NCP_DDR_CFG_NTEMC_PREFVALS                          (0x00000120)
#define     NCP_DDR_CFG_DDR_SMON_00                             (0x00000130)
#define     NCP_DDR_CFG_DDR_SMON_01                             (0x00000134)
#define     NCP_DDR_CFG_DDR_SMON_02                             (0x00000138)
#define     NCP_DDR_CFG_DDR_SMON_03                             (0x0000013c)
#define     NCP_DDR_CFG_DDR_SMON_04                             (0x00000140)
#define     NCP_DDR_CFG_DDR_SMON_10                             (0x00000144)
#define     NCP_DDR_CFG_DDR_SMON_11                             (0x00000148)
#define     NCP_DDR_CFG_DDR_SMON_12                             (0x0000014c)
#define     NCP_DDR_CFG_DDR_SMON_13                             (0x00000150)
#define     NCP_DDR_CFG_DDR_SMON_14                             (0x00000154)


#define     NCP_DDR_NTEMC_HIST_BASE                             (0x00000200)
#define     NCP_DDR_NTEMC_HIST(n)                               (0x00000200 + (8*(n)))
#define     NCP_DDR_NTEMC_HIST_ACCESS_SIZE                      (0x00000008) /* Bytes */
#define     NCP_DDR_NTEMC_HIST_COUNT                            (0x00000040)
#define     NCP_DDR_NTEMC_HIST_IDX(addr) \
                     (((addr) - NCP_DDR_NTEMC_HIST_BASE) / 8)          
#define     NCP_DDR_NTEMC_HIST_END                              (0x00000400)
#define     NCP_DDR_NTEMC_HIST_RANGE(addr) \
                  (((addr) >= NCP_DDR_NTEMC_HIST_BASE) && \
                          ((addr) < NCP_DDR_NTEMC_HIST_END))

#ifdef __cplusplus
}
#endif

#endif /* _NCP_DDR_REG_DEFINES_H_ */
