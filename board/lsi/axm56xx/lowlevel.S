#include <config.h>

	.global		lowlevel_init

lowlevel_init:

	/*
	 * Set the CNTFRQ register.
	 */

#ifdef CONFIG_SPL_BUILD
	mrs	x0, ID_PFR1_EL1
	and	w0, w0, 0x10000
	cbz	w0, 1f
	ldr	x0, =CONFIG_SYS_CNTR_FREQ
	msr	CNTFRQ_EL0, x0
1:
#endif

	ret
