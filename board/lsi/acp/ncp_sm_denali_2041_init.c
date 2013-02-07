
/********************************************************************
 * ncp_sm_denali_2041_init.c
 *
 *   Initialization routine for the 
 *   Denali System Memory Controller version 2041. 
 *
 *
 *   With the appropriate wrapper macros this code code can 
 *   be included and compiled for both u-boot and RTE. If you
 *   are editing this code from within the RTE please do not 
 *   add anything that will break the u-boot build!!
 *******************************************************************/

#ifndef UBOOT
#include "ncp.h"
#include "ncp_pvt.h"
#include "ncp_sysmem_ext.h"
#include "ncp_sysmem_lsiphy.h"
#endif


#define NCP_SM_ENCODE_RTT_NOM(val)  \
    ( ( (val & 0x1) << 2 ) |  /* a2 */ \
      ( (val & 0x2) << 5 ) |  /* a6 */ \
      ( (val & 0x4) << 7 ) )  /* a9 */
      

#define NCP_SM_ENCODE_DRV_IMP(val)  \
    ( ( (val & 0x1) << 1 ) |  /* a1 */ \
      ( (val & 0x2) << 4 ) )  /* a5 */ 


ncp_st_t
ncp_sm_denali_2041_init(
    ncp_dev_hdl_t dev,
    ncp_uint32_t  smId,
    ncp_sm_parms_t *parms)
{
    ncp_st_t ncpStatus = NCP_ST_SUCCESS;
    ncp_uint32_t value;
    ncp_uint32_t ctl_32, ctl_33, ctl_34;
    ncp_region_id_t ctlReg = NCP_REGION_ID(sm_nodes[smId], NCP_SYSMEM_TGT_DENALI);

    ncp_uint8_t *tRFC_vals = tRFC_vals_800;

    NCP_COMMENT("Sysmem %d Denali Controller init", smId);
    /* node_cfg */
    ncr_write32(ctlReg,  0x0010, 0x00000003);

    /* DENALI_CTL_00 */
    /* TODO: at some point the AP field may be st */
    ncr_write32(ctlReg,  0x0000, 0x01010100);

    /* DENALI_CTL_01 */
    ncr_write32(ctlReg,  0x0004, 0x01010100);

    /* DENALI_CTL_02 */
    ncr_write32(ctlReg,  0x0008, 0x00000100);

    /* DENALI_CTL_04 */
    ncr_write32(ctlReg,  0x0010, 0x00000001);

    /* DENALI_CTL_06 */
    ncr_write32(ctlReg,  0x0018, 0x00010000);

    /* DENALI_CTL_07 */
    ncr_write32(ctlReg,  0x001c, 0x00000001);

    /* DENALI_CTL_11 */
    value = 0;
    if (parms->primary_bus_width == 2) {
        /* set the controller half-data path mode for 32-bit bus */
        SV( ncp_denali_DENALI_CTL_11_t, reduc, 1 );
    }
    /* TODO: registered DIMM support !! */
    ncr_write32(ctlReg, 0x002c, value);


    /* DENALI_CTL_12 */
    ncr_write32(ctlReg,  0x0030, 0x01000001);

    /* DENALI_CTL_14 */
    ncr_write32(ctlReg,  0x0038, 0x00010100);

    /* DENALI_CTL_17 */
    ncr_write32(ctlReg,  0x0044, 0x00000100);

    /* DENALI_CTL_18 */
    ncr_write32(ctlReg,  0x0048, 0x00000200);

    /* DENALI_CTL_19 */
    ncr_write32(ctlReg,  0x004c, 0x00000300);

    /* DENALI_CTL_20 */
    /* TODO!! */
    ncr_write32(ctlReg,  0x0050, 0x00000000);

    /* DENALI_CTL_21 */
    ncr_write32(ctlReg,  0x0054, 0x02000000);

    /* DENALI_CTL_22 */
    ncr_write32(ctlReg,  0x0058, 0x03ff0000);

    /* DENALI_CTL_23 */
    ncr_write32(ctlReg,  0x005c, 0x00ff0000);

    /* DENALI_CTL_24 */
    ncr_write32(ctlReg,  0x0060, 0x04000000);

    /* DENALI_CTL_25 */
    ncr_write32(ctlReg,  0x0064, 0x00000605);

    /* DENALI_CTL_26 */
#if 0   /* TEMP until we have ASE config support */
    value = 0x04040a00;
#else
    value = 0x04040a00;
    if (parms->address_mirroring)
    {
        /* set the controller half-data path mode for 32-bit bus */
        SV( ncp_denali_DENALI_CTL_26_t, address_mirroring, 0xa);
    }
#endif
    ncr_write32(ctlReg,  0x0068, value);

    /* DENALI_CTL_27 */
    ncr_write32(ctlReg,  0x006c, 0x03030404);

    /* DENALI_CTL_28 */
    ncr_write32(ctlReg,  0x0070, 0x02020303);

    /* DENALI_CTL_29 */
    ncr_write32(ctlReg,  0x0074, 0x01010202);

    /* DENALI_CTL_30 */
    ncr_write32(ctlReg,  0x0078, 0x0c000101);

    /* DENALI_CTL_31 */
    value = 0;
    SV( ncp_denali_DENALI_CTL_31_t, dram_class, 6 );
    SV( ncp_denali_DENALI_CTL_31_t, cs_map, parms->topology );
    ncr_write32(ctlReg,  0x007c, value);

    /* DENALI_CTL_32 */
    /* DENALI_CTL_33 */
    /* DENALI_CTL_34 */
    /* These registers set up ODT based on topology. */
    /* Currently ACP2500 only supports two ranks */
    switch( parms->topology ) {
        case 0x1:
            ctl_32  = 0x00000000;
            ctl_33  = 0x00010000;
            ctl_34  = 0x00000201;
            break;
        case 0x3:
            ctl_32  = 0x00000000;
            ctl_33  = 0x02010000;
            ctl_34  = 0x00000000;
            break;
#if 0
        case 0x5:
            ctl_32  = 0x00040000;
            ctl_33  = 0x00040001;
            ctl_34  = 0x00000001;
            break;
        case 0xf:
            ctl_32  = 0x08040000;
            ctl_33  = 0x08040201;
            ctl_34  = 0x00000201;
            break;
#endif
        default:
            printf( "%d: Unsupported Topology.\n", parms->topology );
            acp_failure( __FILE__, __FUNCTION__, __LINE__ );
            break;
    }
    /* DENALI_CTL_32 */
    ncr_write32(ctlReg,  0x0080, ctl_32);
    /* DENALI_CTL_33 */
    ncr_write32(ctlReg,  0x0084, ctl_33);
    /* DENALI_CTL_34 */
    ncr_write32(ctlReg,  0x0088, ctl_34);

    /* DENALI_CTL_35 */
    ncr_write32(ctlReg,  0x008c, 0x00000002);

    /* DENALI_CTL_36 */
    value = 0;
    SV( ncp_denali_DENALI_CTL_36_t, twtr, 6 );      /* FREQDEP : 7.5ns @800MHz */
    SV( ncp_denali_DENALI_CTL_36_t, trp, parms->CAS_latency );
    ncr_write32(ctlReg,  0x0090, value );

    /* DENALI_CTL_37 */
    /* TODO : LARRY */
    ncr_write32(ctlReg,  0x0094, 0x00000808);

    /* DENALI_CTL_38 */
    value = 0;
    SV( ncp_denali_DENALI_CTL_38_t, caslat_lin, ( parms->CAS_latency * 2 ));
    ncr_write32(ctlReg,  0x0098, value);

    /* DENALI_CTL_39 */
    value = 0;
    /* tDAL = CL + tWR  = CL + 15ns */
    /* FREQDEP : tWR = 12 : 15ns @800MHz */
    SV( ncp_denali_DENALI_CTL_39_t, tdal, ( parms->CAS_latency + 12 ) ); 
    /* TODO : LARRY -- rdlat_adj??? */
    SV( ncp_denali_DENALI_CTL_39_t, rdlat_adj,  2);
    ncr_write32(ctlReg,  0x009c, value);

    /* DENALI_CTL_40 */
    /* FREQDEP */
    /* TFAW depends on memory organization  (sdram_device_width)
     *      and speed bin 
     *    x8 : 30ns  = 24 clks at 800MHz
     *   x16 : 40ns  = 32 clks at 800MHz 
     */
    value = 0;
    if ( (NCP_SM_SDRAM_DENSITY_8GBIT == parms->sdram_device_density) || 
         (NCP_SM_SDRAM_WIDTH_16BITS  == parms->sdram_device_width)) {
        SV(ncp_denali_DENALI_CTL_40_t, tfaw, 32);
    } else {
        SV(ncp_denali_DENALI_CTL_40_t, tfaw, 24);
    }
    SV(ncp_denali_DENALI_CTL_40_t, tdfi_phy_rdlat, parms->phy_rdlat);
    ncr_write32(ctlReg,  0x00a0, value);

    /* DENALI_CTL_41 */
    /* FREQDEP */
    /* tRC depends on CL : These are the only valid values for 800MHz
     *
     *       CL      tRC          value at 800 MHz
     *       8     45 ns              36
     *       9     46.25 ns           37
     *      10     47.5 ns            38
     *      11     48.75 ns           39 
     *
     * For these values it looks like tRC = CL + 28. 
     * Not sure if  this holds for all values but we'll use it for now...
     */
    value = 0;
    SV( ncp_denali_DENALI_CTL_41_t, tmrd, 4 );
    SV( ncp_denali_DENALI_CTL_41_t, trc, ( parms->CAS_latency + 28 ) );
    SV( ncp_denali_DENALI_CTL_41_t, twr_int, 12 );  /* FREQDEP */
    ncr_write32(ctlReg,  0x00a4, value);

    /* DENALI_CTL_42 */
    ncr_write32(ctlReg,  0x00a8, 0x00002819);

      
       

    /* DENALI_CTL_60 */
    /* TODO: tdfi_rdlvl_resplat = CL + AL + 15 */
    value = 0;
    SV( ncp_denali_DENALI_CTL_60_t, tdfi_rdlvl_resplat, parms->CAS_latency + 15 );
    ncr_write32(ctlReg,  0x00f0, value);

    /* DENALI_CTL_61 */
    ncr_write32(ctlReg,  0x00f4, 0x04000300);

    /* DENALI_CTL_62 */
    value = 0;
    SV( ncp_denali_DENALI_CTL_62_t, trcd_int, parms->CAS_latency );
    SV( ncp_denali_DENALI_CTL_62_t, tras_min, 28 ); /* FREQDEP - 35ns @800MHz */
    SV( ncp_denali_DENALI_CTL_62_t, tmod, 12 );
    ncr_write32(ctlReg,  0x00f8, value);

    /* DENALI_CTL_63 */
    ncr_write32(ctlReg,  0x00fc, 0x00006400);

    /* DENALI_CTL_64 */
    ncr_write32(ctlReg,  0x0100, 0x00640064);

    /* DENALI_CTL_65 */
    ncr_write32(ctlReg,  0x0104, 0x00400064);

    /* DENALI_CTL_69 */
    ncr_write32(ctlReg,  0x0114, 0x18621862);

    /* DENALI_CTL_70 */
    /*
     * FREQDEP
     *   TREF[29:16] reg temp 7800ns hi temp 3900ns
     */
    value = 0;
    if (parms->high_temp_dram) {
        SV(ncp_denali_DENALI_CTL_70_t, tref, 3120);   /* 3900ns at 800MHz */
    } else {
        SV(ncp_denali_DENALI_CTL_70_t, tref, 6240);   /* 7800ns at 800MHz */
    }
    ncr_write32(ctlReg,  0x0118, value);

    /* DENALI_CTL_84 */
    ncr_write32(ctlReg,  0x0150, 0x00050200);

    /* DENALI_CTL_85 */
    ncr_write32(ctlReg,  0x0154, 0x00140000);

    /* DENALI_CTL_86 */
    value = 0;
    SV( ncp_denali_DENALI_CTL_86_t, txsr, 0x0200 );
    SV( ncp_denali_DENALI_CTL_86_t,
        txsnr, ( tRFC_vals [ parms->sdram_device_density ] + 8 ) );
    ncr_write32(ctlReg,  0x0158, value);

    /* DENALI_CTL_89 */
    ncr_write32(ctlReg,  0x0164, 0x00000000);

    /* DENALI_CTL_93 */
    ncr_write32(ctlReg,  0x0174, 0x00000008);

    /* DENALI_CTL_94 */
    ncr_write32(ctlReg,  0x0178, 0x00000190);

    /* DENALI_CTL_95 */
    ncr_write32(ctlReg,  0x017c, 0x00008000);

    /* DENALI_CTL_126 */
    ncr_write32(ctlReg,  0x01f8, 0x000000a0);

    /* DENALI_CTL_181 */
    ncr_write32(ctlReg,  0x02d4, 0x00010000);

    /* TODO!!! handle added rank switch delays */
    /* DENALI_CTL_182 */
    ncr_write32(ctlReg,  0x02d8, 0x02020001);

    /* TODO!!! handle added rank switch delays */
    /* DENALI_CTL_183 */
    ncr_write32(ctlReg,  0x02dc, 0x00000104);

    /* DENALI_CTL_184 */
    value = 0;
    SV( ncp_denali_DENALI_CTL_184_t, trp_ab, parms->CAS_latency );
    ncr_write32(ctlReg,  0x02e0, value);

    /* DENALI_CTL_185 */
    /* 
     * tdfi_rdlvl_rr = 0x10c
     * tdfi_wrlvl_ww = 0xc8
     */ 
    ncr_write32(ctlReg,  0x02e4, 0x00c8010c);

    /* DENALI_CTL_186 */
    ncr_write32(ctlReg,  0x02e8, 0x02000100);

    /* DENALI_CTL_187 */
    /* DENALI_CTL_188 */
    /* MR0 */
    /* FREQDEP: tWR always equals 12 for 800MHz */
    if( parms->CAS_latency < 12 ) {
        value = 0x0c00 | ( ( parms->CAS_latency - 4 ) << 4 );
    } else {
        value = 0x0c04 | ( ( parms->CAS_latency - 12 ) << 4 );
    }
    value |= value << 16 ;
    ncr_write32(ctlReg,  0x02ec, value);
    ncr_write32(ctlReg,  0x02f0, value);

    /* DENALI_CTL_189 */
    /* DENALI_CTL_190 */
    /* MR1 */
    value  = NCP_SM_ENCODE_RTT_NOM(parms->sdram_rtt_nom);
    value |= NCP_SM_ENCODE_DRV_IMP(parms->sdram_data_drv_imp);
    value |= value << 16; 
    ncr_write32(ctlReg,  0x02f4, value);
    ncr_write32(ctlReg,  0x02f8, value);

    /* DENALI_CTL_191 */
    /* DENALI_CTL_192 */
    /* MR2 : FREQDEP */
    value  = ( parms->sdram_rtt_wr << 9) ; 
    value |= ( parms->CAS_write_latency - 5 ) << 3;
    value |= ( value << 16 );
    ncr_write32(ctlReg,  0x02fc, value);
    ncr_write32(ctlReg,  0x0300, value);
       
    /* DENALI_CTL_223 */
    ncr_write32(ctlReg,  0x037c, 0x00100000);

    /* DENALI_CTL_225 */
    ncr_write32(ctlReg,  0x0384, 0x00100000);


    /* DENALI_CTL_227 */
    ncr_write32(ctlReg,  0x038c, 0x02000404);

    /* DENALI_CTL_228 */
    ncr_write32(ctlReg,  0x0390, 0x02000200);

    /* DENALI_CTL_229 */
    /* FREQDEP */
    value = 0;
    if (parms->high_temp_dram) {
        SV(ncp_denali_DENALI_CTL_229_t, tras_max, 0x6db0); /* 35100ns @ 800MHz */
    } else {
        SV(ncp_denali_DENALI_CTL_229_t, tras_max, 0xdb60); /* 70200ns @ 800MHz */
    }
    ncr_write32(ctlReg,  0x0394, value);

    /* DENALI_CTL_230 */
    value = 0x02000000;
    SV( ncp_denali_DENALI_CTL_230_t,
        trfc, tRFC_vals [ parms->sdram_device_density ] );
    ncr_write32(ctlReg,  0x0398, value);

    /* DENALI_CTL_232 */
    ncr_write32(ctlReg,  0x03a0, 0x07070000);

    /* DENALI_CTL_234 */
    ncr_write32(ctlReg,  0x03a8, 0x24101065);

    /* DENALI_CTL_235 */
    ncr_write32(ctlReg,  0x03ac, 0x00001370);

    /* DENALI_CTL_236 */
    ncr_write32(ctlReg,  0x03b0, 0x00000003);

    /* DENALI_CTL_237 */
    ncr_write32(ctlReg,  0x03b4, 0x13030154);

    /* DENALI_CTL_238 */
    ncr_write32(ctlReg,  0x03b8, 0x00001367);

    /* DENALI_CTL_239 */
    ncr_write32(ctlReg,  0x03bc, 0x000fff0c);

    /* DENALI_CTL_240 */
    ncr_write32(ctlReg,  0x03c0, 0x00000800);

    /* DENALI_CTL_241 */
    ncr_write32(ctlReg,  0x03c4, 0x000012c0);

    /* DENALI_CTL_242 */
    ncr_write32(ctlReg,  0x03c8, 0x00000005);

    /* DENALI_CTL_244 */
    ncr_write32(ctlReg,  0x03d0, 0x00000808);

      
       

    /* DENALI_CTL_279 */
    ncr_write32(ctlReg,  0x045c, 0x00000000);
       
#if 0
    /* DENALI_CTL_327 */
    ncr_write32(ctlReg,  0x051c, 0x000079ea);
#endif

    /* DENALI_CTL_328 */
    ncr_write32(ctlReg,  0x0520, 0x01010002);

    /* DENALI_CTL_329 */
    ncr_write32(ctlReg,  0x0524, 0x03010100);

    /* DENALI_CTL_330 */
    ncr_write32(ctlReg,  0x0528, 0x00000003);

    /* DENALI_CTL_332 */
    ncr_write32(ctlReg,  0x0530, 0x00000040);

    /* DENALI_CTL_333 */
    /* 
     * The row/column/bank addressing has changed in the new 
     * version of the denali controller.
     *
     *     
     *   Density         Width         row_diff       col_diff
     *   512Mb           x8              3               1
     *   512Mb           x16             4               1
     *   1Gb             x8              2               1
     *   1Gb             x16             3               1
     *   2Gb             x8              1               1
     *   2Gb             x16             2               1
     *   4Gb             x8              0               1
     *   4Gb             x16             1               1
     *   8Gb             x8              0               1
     *   8Gb             x16             0               0
     *
     *  sdram_device_density is defined as follows:
     *   0=256M, 1=512Mb, 2=1Gb, 3=2Gb, 4=4Gb, 5=8Gb, and 6=16Gb
     *
     *  sdram_device_width is defined as follows:
     *   0=x4, 1=x8, 2=x16, and 3=x32 (note that x4 and x32 aren't supported)
     *
	 *  So, for all densities except 8Gb, row_diff = 3 + width - density
     *
     */
    value = 0;
    if ((parms->sdram_device_density != NCP_SM_SDRAM_DENSITY_8GBIT) && 
        (parms->sdram_device_width   != NCP_SM_SDRAM_WIDTH_16BITS) )
    {
        SV(ncp_denali_DENALI_CTL_333_t, col_diff,  1);
        SV(ncp_denali_DENALI_CTL_333_t, row_diff,  
                (3 + parms->sdram_device_width - parms->sdram_device_density));
    }
    ncr_write32(ctlReg,  0x0534, value);

    /* DENALI_CTL_334 */
    ncr_write32(ctlReg,  0x0538, 0x07010000);

    /* DENALI_CTL_127 */
    ncr_write32(ctlReg,  0x01fc, 0x80000000);


#if 0
    /* enable the controller ! */
    ncr_write32(ctlReg,  0x0030, 0x01010001 );

    /* wait for controller MC init to complete */
    if (0 != ncr_poll(ctlReg, NCP_DENALI_CTL_260, 0x200, 0x200, 100, 100) )
    {
        /* shouldn't happen */
        NCP_CALL(NCP_ST_ERROR);
    }
#endif



NCP_RETURN_LABEL
    return ncpStatus;
}
