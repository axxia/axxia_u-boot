#include <config.h>
#include <asm/armv8/mmu.h>
#include <asm/system.h>

	/*
	 * Set up page tables for U-Boot in Memory (SYSCACHE).  Space
	 * for the tables is reserved in the linker script.
	 */

#if defined(SYSCACHE_ONLY_MODE) && !defined(CONFIG_SPL_BUILD)

do_attributes:

	ldr	x5, =(PMD_TYPE_SECT | PMD_SECT_INNER_SHARE | PMD_SECT_AF)
	orr	x1, x1, x5

	/* retreive an output addr[47-29] */
	bic	x5, x1, #0x1fffffff
	/* increament by page size 512MB */
	ldr	x6, =0x20000000
	add	x5, x5, x6
	/* and check if this is yet memory */
	cmp	x5, x4
	b.le	set_memory
	ldr	x5, =MT_DEVICE_NGNRNE
	b	end_set_region

set_memory:

	ldr	x5, =MT_NORMAL

end_set_region:

	lsl	x5, x5, #2
	orr	x1, x1, x5

	ret

do_sctrl:

	adr	x0, __PGT__
	msr	ttbr0_el3, x0
	ldr	x0, =0x0000000080837516
	msr	tcr_el3, x0
	ldr	x0, =0x000000FF440C0400
	msr	mair_el3, x0
	dsb	sy
	tlbi	alle3
	dsb	sy
	isb

	ret

do_mmu:

	/*
	 * x1 - page table entry
	 * x2 - iterate until x2
	 * x3 - index
	 * x4 - mem ranges from 0 to x4
	 */

	adr	x0, __PGT__
	mov	x1, #0
	ldr	x2, =PGTABLE_SIZE
	lsr	x2, x2, #3

	mov	x3, #0
	mov	x4, #0x40000000
	mov	x29, x30        /* Save LR */

1:	lsl	x1, x1, #29	/*page table entry*/
	bl	do_attributes
	str	x1, [x0], #8 /*write page table entry to memory and increment */
	add	x3, x3, #1   /*increament index*/
	mov	x1, x3 /* set the init value for the next page table entry */
	cmp	x3, x2
	b.lt	1b
	bl	do_sctrl

	mov	x30, x29	/* Restore LR */

	ret

#endif /* SYSCACHE_ONLY_MODE && !CONFIG_SPL_BUILD */

	.global		lowlevel_init

lowlevel_init:

    /*
     * Do MMU for U-Boot
     */

#if defined(SYSCACHE_ONLY_MODE) && !defined(CONFIG_SPL_BUILD)
	mov x28, x30 /* Save LR */
	bl do_mmu
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

#if defined(SYSCACHE_ONLY_MODE) && !defined(CONFIG_SPL_BUILD)
	mov x30, x28 /*Restore LR */
#endif

	ret
