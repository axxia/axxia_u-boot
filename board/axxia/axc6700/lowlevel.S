#include <config.h>

	.global		lowlevel_init

lowlevel_init:

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
