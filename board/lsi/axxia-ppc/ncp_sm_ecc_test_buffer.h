


/* set of data patterns that yield unique ecc check codes */
ncp_uint32_t ecc_test_data[2][16] = {

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

