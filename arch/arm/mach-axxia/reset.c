#include <common.h>
#include <asm/io.h>

void reset_cpu(ulong ignored)
{
	unsigned int reset_ctl;

	if (0 != (global->flags & PARAMETERS_GLOBAL_DISABLE_RESET)) {
		stop_watchdog();
		asm volatile ("7: b 7b");
	}

	/*
	Chip Reset
	*/

	writel(0xab, SYSCON + 0x2000);
	reset_ctl = readl(SYSCON + 0x2008);
	reset_ctl |= 0x2;
	writel(reset_ctl, SYSCON + 0x2008);

	printf("Reset failed!\n"); /* Should never get here... */
}
