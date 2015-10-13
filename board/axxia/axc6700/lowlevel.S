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

	/*
	 * Initialize the pfuse global variable.
	 */

	ldr	x0, =SYSCON
	ldr	w0, [x0, 0x34]
	ldr	x1, =pfuse
	str	w0, [x1]

	/*
	 * Initialize the OS lock.
	 */

	mov	x0, #0
	msr	OSLAR_EL1, x0

	ret
