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

/********************************************************************
 * ncp_sm_denali_init_v1.h
 *
 *   Initialization routine for the
 *   V1 ASIC Denali System Memory Controller
 *
 *   With the appropriate wrapper macros this code code can
 *   be included and compiled for both u-boot and RTE. If you
 *   are editing this code from within the RTE please do not
 *   add anything that will break the u-boot build!!
 *******************************************************************/

#define NCP_SM_ENCODE_RTT_NOM(val)  \
    ( ( (val & 0x1) << 2 ) |  /* a2 */ \
      ( (val & 0x2) << 5 ) |  /* a6 */ \
      ( (val & 0x4) << 7 ) )  /* a9 */


#define NCP_SM_ENCODE_DRV_IMP(val)  \
    ( ( (val & 0x1) << 1 ) |  /* a1 */ \
      ( (val & 0x2) << 4 ) )  /* a5 */


    /*
     * Parameters based on device density:
     *    tRFC, tCPD, and tXSNR
     *
     * The values for tRFC are:
     *
     *         density        tRFC
     *           512Mb         90 ns/clk
     *             1GB        110 ns/clk
     *             2GB        160 ns/clk
     *             4GB        300 ns/clk
     *
     * tCPD = tXSNR = (tRFC + 5)
     *
     * Above we have defined a table of the tRFC values for 533MHz.
     *
     * NOTE!!! If we ever support some other clock speed we need to
     * change this!!
     */

    /*
     * Parameters based on CL
     *   tRCD_int, tRP, tRP_AB, tRC, tDAL, caslat /2ec
     */


    /*
      Intialize the Memory Controller (ncp_sm_denali_init)
     */

    switch( topology ) {
        case 0x1:
            ctl_26  = 0x01010a00;
            ctl_32  = 0x00000000;
            ctl_33  = 0x00010000;
            ctl_34  = 0x00000201;
            break;
        case 0x5:
            ctl_26  = 0x01010a00;
            ctl_32  = 0x00040000;
            ctl_33  = 0x00040001;
            ctl_34  = 0x00000001;
            break;
        case 0x3:
            ctl_26  = 0x01010a00;
            ctl_32  = 0x00000000;
            ctl_33  = 0x02010000;
            ctl_34  = 0x00000000;
            break;
        case 0xf:
            ctl_26  = 0x01010a00;
            ctl_32  = 0x08040000;
            ctl_33  = 0x08040201;
            ctl_34  = 0x00000201;
            break;
        default:
            printf( "%d: Unknown Topology.\n", i );
            acp_failure( __FILE__, __FUNCTION__, __LINE__ );
            break;
    }

    ncr_write32( controller, 0x000, 0x00010101 );
    ncr_write32( controller, 0x004, 0x01010101 );
    ncr_write32( controller, 0x008, 0x00000100 );
    ncr_write32( controller, 0x00c, 0x01000101 );
    ncr_write32( controller, 0x014, 0x01000000 );
    ncr_write32( controller, 0x018, 0x00010000 );
    ncr_write32( controller, 0x01c, 0x00000001 );

    /* DENALI_CTL_11 */
    if (primary_bus_width == 2) {
        /* set the controller half-data path mode for 32-bit bus */
        value = 0;
        SV( ncp_denali_DENALI_CTL_11_t, reduc, 1 );
        ncr_write32( controller, 0x2c, value);
    }


    ncr_write32( controller, 0x030, 0x01000001 );
    ncr_write32( controller, 0x038, 0x00010100 );
    ncr_write32( controller, 0x040, 0x02020000 );
    ncr_write32( controller, 0x044, 0x02020100 );
    ncr_write32( controller, 0x048, 0x02020200 );
    ncr_write32( controller, 0x04c, 0x02020300 );
    ncr_write32( controller, 0x050, 0x02000000 );
    ncr_write32( controller, 0x054, 0x01000000 );

    /* DENALI_CTL_22 */
    value = 0;
    SV( ncp_denali_DENALI_CTL_22_t, bstlen, 3 );
    SV( ncp_denali_DENALI_CTL_22_t, age_count, 7 );

        /*
        Density         Width           addr_pins       col_size
        512Mb           x8              3               3
        512Mb           x16             4               3
        1Gb             x8              2               3
        1Gb             x16             3               3
        2Gb             x8              1               3
        2Gb             x16             2               3
        4Gb             x8              0               3
        4Gb             x16             1               3
        8Gb             x8              0               2
        8Gb             x16             0               3

	sdram_device_density is defined as follows:
	0=256M, 1=512Mb, 2=1Gb, 3=2Gb, 4=4Gb, 5=8Gb, and 6=16Gb

	sdram_device_width is defined as follows:
	0=x4, 1=x8, 2=x16, and 3=x32 (note that x4 and x32 aren't supported)

	So, for all densities except 8Gb, addr_pins = 3 + width - density
    */

    if( 5 == sdram_device_density ) {
      SV( ncp_denali_DENALI_CTL_22_t, addr_pins, 0 );
    } else {
      SV( ncp_denali_DENALI_CTL_22_t, addr_pins,
	  ( 3 + sdram_device_width - sdram_device_density ) );
    }

    ncr_write32( controller, 0x058, value );

    /* DENALI_CTL_23 */
    value = 0;
    SV( ncp_denali_DENALI_CTL_23_t, command_age_count, 7 );

    if (5 == sdram_device_density && 1 == sdram_device_width) {
        SV( ncp_denali_DENALI_CTL_23_t, column_size, 2 )
    } else {
        SV( ncp_denali_DENALI_CTL_23_t, column_size, 3 )
    }

    ncr_write32( controller, 0x05c, value );


    ncr_write32( controller, 0x060, 0x04070000 );

    /*
     *   added_rank_switch_delay is now a parameter with value:
     *   v1 : 3
     *   v2 : 2 or 3, depending on topology and board design
     */
    value = 0;
    SV( ncp_denali_DENALI_CTL_25_t, w2r_diffcs_dly, added_rank_switch_delay);
    SV( ncp_denali_DENALI_CTL_25_t, trtp, 4);

    if (5 == sdram_device_density || 2 == sdram_device_width) {
        SV( ncp_denali_DENALI_CTL_25_t, trrd, 6);
    } else {
	SV( ncp_denali_DENALI_CTL_25_t, trrd, 4);
    }

    ncr_write32( controller, 0x064, value);

    /* DENALI_CTL_26 */
    if (address_mirroring) {
        ctl_26 |= 0xa;
    }
    ncr_write32( controller, 0x068, ctl_26 );
    ncr_write32( controller, 0x06c, 0x01010101 );
    ncr_write32( controller, 0x070, 0x01010101 );
    ncr_write32( controller, 0x074, 0x01010101 );
    ncr_write32( controller, 0x078, 0x0c000101 );

    /* DENALI_CTL_31 */
    value = 0;
    SV( ncp_denali_DENALI_CTL_31_t, dram_class, 6 );
    SV( ncp_denali_DENALI_CTL_31_t, cs_map, topology );
    SV( ncp_denali_DENALI_CTL_31_t, caslat, CAS_latency );
    ncr_write32( controller, 0x07c, value );

    /* DENALI_CTL_32 - DENALI_CTL_34 */
    ncr_write32( controller, 0x080, ctl_32 );
    ncr_write32( controller, 0x084, ctl_33 );
    ncr_write32( controller, 0x088, ctl_34 );

    ncr_write32( controller, 0x08c, 0x03000000 );

    /* DENALI_CTL_36 */
    value = 0;
    SV( ncp_denali_DENALI_CTL_36_t, twtr, 4 );
    SV( ncp_denali_DENALI_CTL_36_t, trp, CAS_latency );
    ncr_write32( controller, 0x090, value );

    ncr_write32( controller, 0x094, 0x00000506 );

    /* DENALI_CTL_38 */
    value = 0;
    SV( ncp_denali_DENALI_CTL_38_t, caslat_lin,
      ( CAS_latency + min_ctrl_roundtrip_delay ) * 2 );
    SV( ncp_denali_DENALI_CTL_38_t, caslat_lin_gate,
          ( CAS_latency + min_ctrl_roundtrip_delay ) * 2 );
    ncr_write32( controller, NCP_DENALI_CTL_38, value );

    /* DENALI_CTL_39 */
    value = 0;
    /* tDAL = CL + tWR  (tWR is always 8 for 533MHz) */
    SV( ncp_denali_DENALI_CTL_39_t, tdal, ( CAS_latency + 8 ) );
    SV( ncp_denali_DENALI_CTL_39_t, rdlat_adj,
          ( CAS_latency + min_ctrl_roundtrip_delay ) );
    ncr_write32( controller, NCP_DENALI_CTL_39, value );

    /* DENALI_CTL_40 */
    /* TFAW depends on memory organization  (sdram_device_width)
     *    x8 : 37.5ns  = 20 clks at 533MHz
     *   x16 : 50ns    = 27 clks at 533MHz
     */
    value = 0;

    if (5 == sdram_device_density || 2 == sdram_device_width) {
        SV(ncp_denali_DENALI_CTL_40_t, tfaw, 27);
    } else {
        SV(ncp_denali_DENALI_CTL_40_t, tfaw, 20);
    }

    SV(ncp_denali_DENALI_CTL_40_t, tdfi_phy_rdlat, phy_rdlat);
    SV(ncp_denali_DENALI_CTL_40_t, tdfi_rddata_en_base, 2);
    ncr_write32( controller, 0x0a0, value );

    /* DENALI_CTL_41 */
    /* tRC depends on CL : These are the only valid values for 533MHz
     *
     *       CL      tRC          value at 533 MHz
     *       6     48.75ns/clk        26
     *       7     50.625ns/clk       27
     *       8     52.5ns/clk         28
     *
     * For these values it looks like tRC = CL + 20.
     * Not sure if  this holds for all values but we'll use it for now...
     */
    value = 0;
    SV( ncp_denali_DENALI_CTL_41_t, tmrd, 4 );
    SV( ncp_denali_DENALI_CTL_41_t, trc, ( CAS_latency + 20 ) );
    SV( ncp_denali_DENALI_CTL_41_t, twr_int, 8 );
    ncr_write32( controller, NCP_DENALI_CTL_41, value );

    ncr_write32( controller, 0x0a8, 0x00002819 );
    ncr_write32( controller, 0x0e4, 0x40000000 );
    ncr_write32( controller, 0x0f0, 0x0a000000 );
    ncr_write32( controller, 0x0f4, 0x0a000000 );

    /* DENALI_CTL_62 */
    value = 0;
    SV( ncp_denali_DENALI_CTL_62_t, trcd_int, CAS_latency );
    SV( ncp_denali_DENALI_CTL_62_t, tras_min, 20 );
    SV( ncp_denali_DENALI_CTL_62_t, tmod, 12 );
    ncr_write32( controller, 0x0f8, value );

    /* DENALI_CTL_63 */
    /*
     * [ 7:0] v1 : tRFC
     *        v2+: obsolete, moved to 0x394
     *
     * presumably the obsoleted field has no effect on v1 so we just
     * always write it, and will write the v2 value later.
     */
    value = 0;
    SV( ncp_denali_DENALI_CTL_63_t, axi0_priority_relax, 0x64 );
    SV( ncp_denali_DENALI_CTL_63_t,
        trfc, tRFC_vals [ sdram_device_density ] );
    ncr_write32( controller, 0x0fc, value );

    ncr_write32( controller, 0x100, 0x00640064 );
    ncr_write32( controller, 0x104, 0x00400064 );

    /*
     *
     * # TREF[29:16] reg temp 7800ns hi temp 3900ns
     */
    value = 0;
    if (high_temp_dram) {
        SV(ncp_denali_DENALI_CTL_70_t, tref, 2080);/* 3900ns at 533MHz */
    } else {
        SV(ncp_denali_DENALI_CTL_70_t, tref, 4160);/* 7800ns at 533MHz */
    }
    ncr_write32( controller, 0x118, value);

    ncr_write32( controller, 0x11c, 0x00000000 );
    ncr_write32( controller, 0x120, 0x00000000 );
    ncr_write32( controller, 0x124, 0x00000000 );

    /* DENALI_CTL_82 */
    value = 0;
    SV( ncp_denali_DENALI_CTL_82_t,
        tcpd, ( tRFC_vals [ sdram_device_density ] + 5 ) );
    ncr_write32( controller, 0x148, value );

    ncr_write32( controller, 0x150, 0x00040200 );

    /*
     * [15:0] v1 : tRAS_max
     *        v2+: obsolete, moved to 0x394
     *
     * presumably this field has no effect on v1 so we just
     * always write it, and will write the v2 value later.
     *
     */
    value = 0;

    if (high_temp_dram) {
        SV(ncp_denali_DENALI_CTL_85_t, tras_max, 0x4920);/* 35100ns @ 533MHz */
    } else {
        SV(ncp_denali_DENALI_CTL_85_t, tras_max, 0x9240);/* 70200ns @ 533MHz */
    }
    SV(ncp_denali_DENALI_CTL_85_t, txpdll, 0xd);
    ncr_write32( controller, 0x154, value );

    /* DENALI_CTL_86 */
    value = 0;
    SV( ncp_denali_DENALI_CTL_86_t, txsr, 0x0200 );
    SV( ncp_denali_DENALI_CTL_86_t,
        txsnr, ( tRFC_vals [ sdram_device_density ] + 5 ) );
    ncr_write32( controller, 0x158, value );

    ncr_write32( controller, 0x174, 0x0001a0ab );
    ncr_write32( controller, 0x178, 0x000411ab );
    ncr_write32( controller, 0x1f8, 0x0001a0ab );
    ncr_write32( controller, 0x1fc, 0x00000055 );
    ncr_write32( controller, 0x2d4, 0x00000001 );

    /*
     */
    value = 0;
    SV( ncp_denali_DENALI_CTL_182_t, r2w_samecs_dly, 2);
    SV( ncp_denali_DENALI_CTL_182_t, r2w_diffcs_dly, added_rank_switch_delay);
    SV( ncp_denali_DENALI_CTL_182_t, r2r_diffcs_dly, added_rank_switch_delay);
    ncr_write32( controller, 0x2d8, value);

    value = 0;
    SV( ncp_denali_DENALI_CTL_183_t, w2w_diffcs_dly, added_rank_switch_delay);
    SV( ncp_denali_DENALI_CTL_183_t, tccd, 4);
    ncr_write32( controller, 0x2dc, value);

    /* DENALI_CTL_184 */
    value = 0;
    SV( ncp_denali_DENALI_CTL_184_t, trp_ab, CAS_latency );
    ncr_write32( controller, 0x2e0, value );

    ncr_write32( controller, 0x2e4, 0x00320032 );
    ncr_write32( controller, 0x2e8, 0x02000100 );

    /* MR0 : DENALI_CTL_187/188  */
    /* tWR always equals 8 for 533MHz */
    if( CAS_latency < 12 ) {
        value = 0x0800 | ( ( CAS_latency - 4 ) << 4 );
    } else {
        value = 0x0804 | ( ( CAS_latency - 12 ) << 4 );
    }

    value |= value << 16 ;
    ncr_write32( controller, 0x2ec, value );
    ncr_write32( controller, 0x2f0, value );

    /* MR1 : DENALI_CTL_189/190  */
    value  = NCP_SM_ENCODE_RTT_NOM(sdram_rtt_nom);
    value |= NCP_SM_ENCODE_DRV_IMP(sdram_data_drv_imp);
    value |= value << 16;
    ncr_write32( controller, 0x2f4, value );
    ncr_write32( controller, 0x2f8, value );

    /* MR2 : DENALI_CTL_191, DENALI_CTL_192 */
    value  = ( sdram_rtt_wr << 9) ;
    value |= ( CAS_write_latency - 5 ) << 3;
    value |= ( value << 16 );
    ncr_write32( controller, 0x2fc, value );
    ncr_write32( controller, 0x300, value );

    ncr_write32( controller, 0x304, 0x00000000 );
    ncr_write32( controller, 0x308, 0x00000000 );
    ncr_write32( controller, 0x37c, 0x00008000 );
    ncr_write32( controller, 0x380, 0x00000080 );
    ncr_write32( controller, 0x384, 0x00008000 );
    ncr_write32( controller, 0x388, 0x00000040 );
    ncr_write32( controller, 0x38c, 0x00000404 );

    /*
     * new registers/fields for v2/X2+
     */
    if (version >= 1) {
        /* tRAS_max */
        if (high_temp_dram) {
            ncr_write32( controller, 0x394, 0x00004920 );
        } else {
            ncr_write32( controller, 0x394, 0x00009240 );
        }

        /* tRFC */
        ncr_write32( controller, 0x398,  tRFC_vals [ sdram_device_density ] );
    }

    /* mask status interrupts so only error interrupts are reported */
    if (version == 0) {
        ncr_write32(controller, 0x168, 0x0003d000);
    } else {
        ncr_write32(controller, 0x168, 0x000fa000);
    }

    /* enable the controller ! */
    ncr_write32( controller, 0x030, 0x01010001 );


/*******************************************************************/
