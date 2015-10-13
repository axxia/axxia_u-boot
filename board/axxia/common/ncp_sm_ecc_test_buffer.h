/**************************************************************************
 **                                                                       *
 **                           LSI CONFIDENTIAL      *
 **                           PROPRIETARY NOTE                            *
 **                                                                       *
 **    This software contains information confidential and proprietary    *
 **    to LSI Corporation Inc.  It shall not be reproduced in whole or in *
 **    part, or transferred to other documents, or disclosed to third     *
 **    parties, or used for any purpose other than that for which it was  *
 **    obtained, without the prior written consent of LSI Corporation Inc.*
 **    (c) 2008-2014, LSI Corporation Inc.  All rights reserved.          *
 **                                                                       *
 **
 **
 **************************************************************************/



/*
 * set of data patterns that yield unique ecc check codes
 * for a 32-bit wide bus (e.g. acp2500)
 */
ncp_uint32_t ecc_test_data_32bit[2][16] = {

    /* first two bursts */
    {
        0xe4c015af,  /* ecc = 1 */
        0x2d1bb4aa,  /* ecc = f */

        0x300a9d2b,  /* ecc = 7 */
        0x58189903,  /* ecc = e */

        0xeae21a1f,  /* ecc = 2 */
        0x35821f74,  /* ecc = d */

        0x63019843,  /* ecc = e */
        0x6e4160c7,  /* ecc = c */

        0xb69ec85a,  /* ecc = 9 */
        0xb6dee77a,  /* ecc = b */

        0x86958964,  /* ecc = 0 */
        0xaa91a6af,  /* ecc = a */

        0x023dd44a,  /* ecc = f */
        0xd607498d,  /* ecc = 9 */

        0xb045b813,  /* ecc = 3 */
        0x6ecf599d,  /* ecc = 8 */
    },


    /* another two bursts to alternate with similar to the inverse pattern */
    {
        0x9c40c36d,  /* ecc = 5 */
        0xfcce6858,  /* ecc = 7 */

        0xd2ce66fb,  /* ecc = 1 */
        0x0ae31c75,  /* ecc = 6 */

        0x3ee4d971,  /* ecc = b */
        0x11b35012,  /* ecc = 5 */

        0x21047581,  /* ecc = f */
        0x7171727c,  /* ecc = 2 */

        0xcee07543,  /* ecc = 0 */
        0x58670a42,  /* ecc = 0 */

        0xb68896ad,  /* ecc = 2 */
        0x958342a2,  /* ecc = 1 */

        0xf99ca9a3,  /* ecc = e */
        0xf111720a,  /* ecc = 3 */

        0xdae127ef,  /* ecc = 1 */
        0xf4c8d52f,  /* ecc = 4 */
    }
};

/*
 * set of data patterns that yield unique ecc check codes
 * for a 64-bit wide bus (e.g. axm5500)
 */
ncp_uint32_t ecc_test_data_64bit[2][32] =
{

    {
        0xed76c3c3, 0x92790f56,     /* 3b */
        0x14cffe90, 0xf414bafc,     /* 26 */
        0x0213a402, 0x29acc6ba,     /* 4e */
        0x923b6634, 0x40ff84f2,     /* 15 */
        0xf4b90a1c, 0x203eff5a,     /* 5e */
        0x32409395, 0x517a4434,     /* d0 */
        0x6780cade, 0x6aed1ab0,     /* 24 */
        0xe6f38088, 0xf1c96f7d,     /* f2 */

        0x9bf98feb, 0x7efffc08,     /* 85 */
        0xaa49f06d, 0x12c46b44,     /* 1e */
        0xac35d1a4, 0xbd1d02d1,     /* 81 */
        0x298b4e09, 0x1d0c0beb,     /* ed */
        0x1045f89d, 0x74ea7d2f,     /* 72 */
        0x55b65995, 0x591809be,     /* 0e */
        0x69f558ba, 0x0c894c83,     /* 8a */
        0xd27e9e7e, 0xe3dc14c9,     /* 4f */
    } ,

    {
        0xf1f76fd4, 0xb9df2547,     /* f8 */
        0x4d1a99d7, 0xbbec92ec,     /* 84 */
        0xd48b5ae6, 0x6287cd9e,     /* eb */
        0xa5536cf1, 0x987f4bce,     /* 96 */
        0xdfec8e2f, 0x3802c6b5,     /* b4 */
        0xd3d28b18, 0xafdee879,     /* cc */
        0x8c3de09a, 0xafe75289,     /* 79 */
        0x3c2521c5, 0xc0032135,     /* 1f */

        0xddcb086a, 0x85b4e341,     /* 09 */
        0xc343b341, 0x8e23d95e,     /* c4 */
        0x6757d6de, 0xc7c883d4,     /* b7 */
        0x746938ff, 0x42f92872,     /* 68 */
        0xbee0d90d, 0x6256228b,     /* a3 */
        0xaa230141, 0x36d7a3d5,     /* b0 */
        0x111f392e, 0x9ec0603c,     /* 87 */
        0x2ce3abba, 0xa9967c59,     /* 7b */
    }

};
