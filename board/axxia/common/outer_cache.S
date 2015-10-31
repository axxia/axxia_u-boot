#include <config.h>
#include <linux/linkage.h>

/*
  ------------------------------------------------------------------------------
  set_outer_cache_state

  Set the mode in (0x10000 * offset) + 0x10, bits 1:0.  Verify that it
  got set by reading (0x10000 * offset) + 0x18), bits 3:2.

  The modes are as follows.

  0b00 - OFF
  0b01 - SFONLY
  0b10 - HALF
  0b11 - FULL
*/

set_outer_cache_state:
#ifndef CONFIG_AXXIA_SIM
	/* Make sure the give state is valid (0, 1, 2, or 3). */
	mov	w10, ~0x3
	and	w10, w0, w10
	cbnz	w10, set_outer_cache_state_failed

	/* Set the state. */
	mov	x10, 0x20
1:	mov	x11, 0x10000
	mul	x11, x10, x11
	ldr	x12, =(DICKENS + 0x10)
	add	x11, x11, x12
	str	w0, [x11]
	add	w10, w10, 1
	cmp	w10, 0x27
	ble	1b

	/* Wait for completion. */
	mov	x10, 0x20
1:	mov	x11, 0x10000
	mul	x11, x10, x11
	ldr	x12, =(DICKENS + 0x18)
	add	x11, x11, x12
2:	ldr	w13, [x11]
	and 	w13, w13, 0xf
	lsr	w13, w13, 2
	cmp	w0, w13
	bne	2b
	add	x10, x10, 1
	cmp	x10, 0x27
	ble	1b

set_outer_cache_state_failed:
	mov	x0, -1
	ret
set_outer_cache_state_succeeded:
#endif
	mov	x0, 0
	ret

ENTRY(__asm_flush_l3_cache)
	mov	x9, x30
	mov	x0, 1
	bl	set_outer_cache_state
#ifndef LEAVE_L3_IN_SFONLY
	mov	x0, 3
	bl	set_outer_cache_state
#endif
	mov	x30, x9
	ret
ENDPROC(__asm_flush_l3_cache)
