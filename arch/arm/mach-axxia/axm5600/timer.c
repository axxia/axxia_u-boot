
#include <common.h>
#include <div64.h>
#include <linux/types.h>        /* for size_t */
#include <linux/stddef.h>       /* for NULL */
#include <asm/io.h>

#define TICK_PER_TIME   ((SYSTIMER_RATE + CONFIG_SYS_HZ / 2) / CONFIG_SYS_HZ)
#define NS_PER_TICK     (1000000000 / SYSTIMER_RATE)

static inline unsigned long long tick_to_time(unsigned long long tick)
{
do_div(tick, TICK_PER_TIME);
return tick;
}

static inline unsigned long long time_to_tick(unsigned long long time)
{
return time * TICK_PER_TIME;
}

static inline unsigned long long us_to_tick(unsigned long long us)
{
unsigned long long tick = us * 1000;
tick += NS_PER_TICK - 1;
do_div(tick, NS_PER_TICK);
return tick;
}

ulong get_timer(ulong base)
{
return get_timer_masked() - base;
}

ulong get_timer_masked(void)
{
return tick_to_time(get_ticks());
}

ulong get_tbclk(void)
{
	ncp_uint32_t frequency;

	if (0 == acp_clock_get(clock_system, &frequency))
		return (ulong)(frequency * 1000);

	return CONFIG_SYS_HZ;
}

int timer_init(void)
{
	return 0;
}




unsigned long long get_ticks(void)
{
u32 cvall, cvalh;

asm volatile("mrrc p15, 0, %0, %1, c14" : "=r" (cvall), "=r" (cvalh));

return (unsigned long long)((unsigned long long)cvalh << 32 | cvall);
}

/*
* Delay x useconds AND preserve advance timstamp value
*     assumes timer is ticking at 1 msec
*/
void __udelay(ulong usec)
{
unsigned long long tmp;
ulong tmo;


tmo = us_to_tick(usec);
tmp = get_ticks() + tmo;        /* get current timestamp */

while (get_ticks() < tmp)       /* loop till event */
/*NOP*/;
}

