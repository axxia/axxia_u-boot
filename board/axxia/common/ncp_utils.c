
/*
 * ncp_nanosecond_to_clocks
 *  - helper function to convert nanoseconds to clock
 *  ticks for a given clock frequency
 */

ncp_uint32_t
ncp_ns_to_clk(
        ncp_uint32_t clk_in_mhz,
        ncp_uint32_t num_ns)
{
    ncp_uint32_t  ps;
    ncp_uint32_t  ps_per_tick;
    ncp_uint32_t  nclk;

    ps_per_tick = (1000 * 1000) / clk_in_mhz;

    if (num_ns > 0x400000) {
        /* handle large values to prevent overflow */
        nclk = (num_ns / ps_per_tick) * 1000;
    }
    else
    {
        /* handle smaller values with more accuracy */
        ps = (num_ns * 1000) + (ps_per_tick - 1);
        nclk = ( ps / ps_per_tick);
    }

    return nclk;

}
