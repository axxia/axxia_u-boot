/*
 *  armboot - Startup Code for OMP2420/ARM1136 CPU-core
 *
 *  Copyright (c) 2004	Texas Instruments <r-woodruff2@ti.com>
 *
 *  Copyright (c) 2001	Marius Gröger <mag@sysgo.de>
 *  Copyright (c) 2002	Alex Züpke <azu@sysgo.de>
 *  Copyright (c) 2002	Gary Jennejohn <gj@denx.de>
 *  Copyright (c) 2003	Richard Woodruff <r-woodruff2@ti.com>
 *  Copyright (c) 2003	Kshitij <kshitij@ti.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <config.h>
#include <version.h>
.globl _start
_start: b	reset
#ifdef CONFIG_ONENAND_IPL
	ldr	pc, _hang
	ldr	pc, _hang
	ldr	pc, _hang
	ldr	pc, _hang
	ldr	pc, _hang
	ldr	pc, _hang
	ldr	pc, _hang

_hang:
	.word	do_hang
	.word	0x12345678
	.word	0x12345678
	.word	0x12345678
	.word	0x12345678
	.word	0x12345678
	.word	0x12345678
	.word	0x12345678	/* now 16*4=64 */
#else
	ldr	pc, _undefined_instruction
	ldr	pc, _software_interrupt
	ldr	pc, _prefetch_abort
	ldr	pc, _data_abort
	ldr	pc, _not_used
	ldr	pc, _irq
	ldr	pc, _fiq

_undefined_instruction: .word undefined_instruction
_software_interrupt:	.word software_interrupt
_prefetch_abort:	.word prefetch_abort
_data_abort:		.word data_abort
_not_used:		.word not_used
_irq:			.word irq
_fiq:			.word fiq
_pad:			.word 0x12345678 /* now 16*4=64 */
#endif	/* CONFIG_ONENAND_IPL */
.global _end_vect
_end_vect:

	.balignl 16,0xdeadbeef
/*
 *************************************************************************
 *
 * Startup Code (reset vector)
 *
 * do important init only if we don't start from memory!
 * setup Memory and board specific bits prior to relocation.
 * relocate armboot to ram
 * setup stack
 *
 *************************************************************************
 */

_TEXT_BASE:
	.word	TEXT_BASE

.globl _armboot_start
_armboot_start:
	.word _start

/*
 * These are defined in the board-specific linker script.
 */
.globl _bss_start
_bss_start:
	.word __bss_start

.globl _bss_end
_bss_end:
	.word _end

#ifdef CONFIG_USE_IRQ
/* IRQ stack memory (calculated at run-time) */
.globl IRQ_STACK_START
IRQ_STACK_START:
	.word	0x0badc0de

/* IRQ stack memory (calculated at run-time) */
.globl FIQ_STACK_START
FIQ_STACK_START:
	.word 0x0badc0de
#endif

/*
 * the actual reset code
 */

reset:
	/*
	 * set the cpu to SVC32 mode
	 */
	mrs	r0,cpsr
	bic	r0,r0,#0x1f
	orr	r0,r0,#0xd3
	msr	cpsr,r0

	/* the mask ROM code should have PLL and others stable */
#ifndef CONFIG_SKIP_LOWLEVEL_INIT
	bl  cpu_init_crit
#endif

#ifdef LSI_ARCH_APP3K
    ldr r0,=CONFIG_NORMAL_DDR2_CFG_BASE
    ldr r1,[r0]
    and r1,#0x00200000
    cmp r1,#0
    bne sim_skip_relocate_
#endif /* LSI_ARCH_APP3K */

#ifndef CONFIG_SKIP_RELOCATE_UBOOT
relocate:				/* relocate U-Boot to RAM	    */
    mov r0, pc
    bic r0, r0, #0x000000ff
    bic r0, r0, #0x0000ff00
    bic r0, r0, #0x000f0000
	ldr	r1, _TEXT_BASE		/* test if we run from flash or RAM */
	cmp	r0, r1			/* don't reloc during debug	    */
#ifndef CONFIG_ONENAND_IPL
	beq	stack_setup
#endif	/* CONFIG_ONENAND_IPL */

	ldr	r2, _armboot_start
	ldr	r3, _bss_start
	sub	r2, r3, r2		/* r2 <- size of armboot	    */
	add	r2, r0, r2		/* r2 <- source end address	    */

copy_loop:
	ldmia	r0!, {r3-r10}		/* copy from source address [r0]    */
	stmia	r1!, {r3-r10}		/* copy to   target address [r1]    */
	cmp	r0, r2			/* until source end addreee [r2]    */
	ble	copy_loop
#endif	/* CONFIG_SKIP_RELOCATE_UBOOT */

#ifdef LSI_ARCH_APP3K

    @
    @ Copy to address 0 as well (to get the exception handlers)
    @

    mov r0, pc
    bic r0, r0, #0x000000ff
    bic r0, r0, #0x0000ff00
    bic r0, r0, #0x000f0000
    mov r1, #0
    ldr	r2, _armboot_start
	ldr	r3, _bss_start
	sub	r2, r3, r2
	add	r2, r0, r2

copy_loop_2:

    ldmia r0!, {r3-r10}
    stmia r1!, {r3-r10}
    cmp   r0, r2
    ble   copy_loop_2

#endif
        
#ifdef LSI_ARCH_APP3K
sim_skip_relocate_:
#endif /* LSI_ARCH_APP3K */

	/* Set up the stack						    */
stack_setup:
	ldr	r0, _TEXT_BASE		/* upper 128 KiB: relocated uboot   */
#ifdef CONFIG_ONENAND_IPL
	sub	sp, r0, #128		/* leave 32 words for abort-stack   */
#else
	sub	r0, r0, #CFG_MALLOC_LEN /* malloc area			    */
	sub	r0, r0, #CFG_GBL_DATA_SIZE /* bdinfo			    */
#ifdef CONFIG_USE_IRQ
	sub	r0, r0, #(CONFIG_STACKSIZE_IRQ+CONFIG_STACKSIZE_FIQ)
#endif
	sub	sp, r0, #12		/* leave 3 words for abort-stack    */
#endif	/* CONFIG_ONENAND_IPL */

#ifdef LSI_ARCH_APP3K
        ldr     r0,=CONFIG_NORMAL_DDR2_CFG_BASE
        ldr     r1,[r0]
        and     r1,#0x00200000
        cmp     r1,#0
        bne     sim_skip_clbss_
#endif /* LSI_ARCH_APP3K */

clear_bss:
	ldr	r0, _bss_start		/* find start of bss segment	    */
	ldr	r1, _bss_end		/* stop here			    */
	mov	r2, #0x00000000		/* clear			    */

#ifndef CONFIG_ONENAND_IPL
clbss_l:str	r2, [r0]		/* clear loop...		    */
	add	r0, r0, #4
	cmp	r0, r1
	bne	clbss_l
#endif

#ifdef LSI_ARCH_APP3K
sim_skip_clbss_:
#endif /* LSI_ARCH_APP3K */

	ldr	pc, _start_armboot

#ifdef CONFIG_ONENAND_IPL
_start_armboot: .word start_oneboot
#else
_start_armboot: .word start_armboot
#endif


/*
 *************************************************************************
 *
 * CPU_init_critical registers
 *
 * setup important registers
 * setup memory timing
 *
 *************************************************************************
 */
cpu_init_crit:
	/*
	 * flush v4 I/D caches
	 */
	mov	r0, #0
	mcr	p15, 0, r0, c7, c7, 0	/* flush v3/v4 cache */
	mcr	p15, 0, r0, c8, c7, 0	/* flush v4 TLB */

	/*
	 * disable MMU stuff and caches
	 */
	mrc	p15, 0, r0, c1, c0, 0
	bic	r0, r0, #0x00002300	@ clear bits 13, 9:8 (--V- --RS)
	bic	r0, r0, #0x00000087	@ clear bits 7, 2:0 (B--- -CAM)
	orr	r0, r0, #0x00000002	@ set bit 2 (A) Align
	orr	r0, r0, #0x00001000	@ set bit 12 (I) I-Cache
	mcr	p15, 0, r0, c1, c0, 0

#ifdef LSI_ARCH_APP3K
    /*
     * put all cores except 0 in the wait for interrupt state
     */
    mrc p15, 0, r0, c0, c0, 5   @ which core is this?
    and r0, r0, #0xf
    cmp r0, #0
    beq 1f                      @ if this is core 0, continue
    mrs r0, cpsr                @ if this is not core 0
    bic r0, r0, #0xdf
    orr r0, r0, #0x53           @ enable interrupts
    msr cpsr, r0
    mov r1, #0xc4000000         @ but not the cpu interface
    mov r0, #0                  @ which gets enabled in armlinux.c
    str r0, [r1, #0x100]
    wfi                         @ and enter the WFI state
    @mcr p15, 0, r0, c7, c0, 4   @ and enter the WFI state
1:
#endif /* LSI_ARCH_APP3K */

	/*
	 * Jump to board specific initialization... The Mask ROM will have already
     * initialized basic memory.  Go here to bump up clock rate and handle wake
     * up conditions.
	 */
	mov	ip, lr		/* persevere link reg across call */
	bl	lowlevel_init	/* go setup pll,mux,memory */
	mov	lr, ip		/* restore link */
	mov	pc, lr		/* back to my caller */

#ifndef CONFIG_ONENAND_IPL
/*
 *************************************************************************
 *
 * Interrupt handling
 *
 *************************************************************************
 */
@
@ IRQ stack frame.
@
#define S_FRAME_SIZE	72

#define S_OLD_R0	68
#define S_PSR		64
#define S_PC		60
#define S_LR		56
#define S_SP		52

#define S_IP		48
#define S_FP		44
#define S_R10		40
#define S_R9		36
#define S_R8		32
#define S_R7		28
#define S_R6		24
#define S_R5		20
#define S_R4		16
#define S_R3		12
#define S_R2		8
#define S_R1		4
#define S_R0		0

#define MODE_SVC 0x13
#define I_BIT	 0x80

/*
 * use bad_save_user_regs for abort/prefetch/undef/swi ...
 * use irq_save_user_regs / irq_restore_user_regs for IRQ/FIQ handling
 */

	.macro	bad_save_user_regs
	sub	sp, sp, #S_FRAME_SIZE		@ carve out a frame on current user stack
	stmia	sp, {r0 - r12}			@ Save user registers (now in svc mode) r0-r12

	ldr	r2, _armboot_start
	sub	r2, r2, #(CFG_MALLOC_LEN)
	sub	r2, r2, #(CFG_GBL_DATA_SIZE+8)	@ set base 2 words into abort stack
	ldmia	r2, {r2 - r3}			@ get values for "aborted" pc and cpsr (into parm regs)
	add	r0, sp, #S_FRAME_SIZE		@ grab pointer to old stack

	add	r5, sp, #S_SP
	mov	r1, lr
	stmia	r5, {r0 - r3}			@ save sp_SVC, lr_SVC, pc, cpsr
	mov	r0, sp				@ save current stack into r0 (param register)
	.endm

	.macro	irq_save_user_regs
	sub	sp, sp, #S_FRAME_SIZE
	stmia	sp, {r0 - r12}			@ Calling r0-r12
	add	r8, sp, #S_PC			@ !!!! R8 NEEDS to be saved !!!! a reserved stack spot would be good.
	stmdb	r8, {sp, lr}^			@ Calling SP, LR
	str	lr, [r8, #0]			@ Save calling PC
	mrs	r6, spsr
	str	r6, [r8, #4]			@ Save CPSR
	str	r0, [r8, #8]			@ Save OLD_R0
	mov	r0, sp
	.endm

	.macro	irq_restore_user_regs
	ldmia	sp, {r0 - lr}^			@ Calling r0 - lr
	mov	r0, r0
	ldr	lr, [sp, #S_PC]			@ Get PC
	add	sp, sp, #S_FRAME_SIZE
	subs	pc, lr, #4			@ return & move spsr_svc into cpsr
	.endm

	.macro get_bad_stack
	ldr	r13, _armboot_start		@ setup our mode stack (enter in banked mode)
	sub	r13, r13, #(CFG_MALLOC_LEN)	@ move past malloc pool
	sub	r13, r13, #(CFG_GBL_DATA_SIZE+8) @ move to reserved a couple spots for abort stack

	str	lr, [r13]			@ save caller lr in position 0 of saved stack
	mrs	lr, spsr			@ get the spsr
	str	lr, [r13, #4]			@ save spsr in position 1 of saved stack

	mov	r13, #MODE_SVC			@ prepare SVC-Mode
	@ msr	spsr_c, r13
	msr	spsr, r13			@ switch modes, make sure moves will execute
	mov	lr, pc				@ capture return pc
	movs	pc, lr				@ jump to next instruction & switch modes.
	.endm

	.macro get_bad_stack_swi
	sub	r13, r13, #4			@ space on current stack for scratch reg.
	str	r0, [r13]			@ save R0's value.
	ldr	r0, _armboot_start		@ get data regions start
	sub	r0, r0, #(CFG_MALLOC_LEN)	@ move past malloc pool
	sub	r0, r0, #(CFG_GBL_DATA_SIZE+8)	@ move past gbl and a couple spots for abort stack
	str	lr, [r0]			@ save caller lr in position 0 of saved stack
	mrs	r0, spsr			@ get the spsr
	str	lr, [r0, #4]			@ save spsr in position 1 of saved stack
	ldr	r0, [r13]			@ restore r0
	add	r13, r13, #4			@ pop stack entry
	.endm

	.macro get_irq_stack			@ setup IRQ stack
	ldr	sp, IRQ_STACK_START
	.endm

	.macro get_fiq_stack			@ setup FIQ stack
	ldr	sp, FIQ_STACK_START
	.endm
#endif	/* CONFIG_ONENAND_IPL */

/*
 * exception handlers
 */
#ifdef CONFIG_ONENAND_IPL
	.align	5
do_hang:
	ldr	sp, _TEXT_BASE			/* use 32 words about stack */
	bl	hang				/* hang and never return */
#else	/* !CONFIG_ONENAND IPL */
	.align	5
undefined_instruction:
	get_bad_stack
	bad_save_user_regs
	bl	do_undefined_instruction

	.align	5
software_interrupt:
	get_bad_stack_swi
	bad_save_user_regs
	bl	do_software_interrupt

	.align	5
prefetch_abort:
	get_bad_stack
	bad_save_user_regs
	bl	do_prefetch_abort

	.align	5
data_abort:
	get_bad_stack
	bad_save_user_regs
	bl	do_data_abort

	.align	5
not_used:
	get_bad_stack
	bad_save_user_regs
	bl	do_not_used

#ifdef CONFIG_USE_IRQ

	.align	5
irq:
	get_irq_stack
	irq_save_user_regs
	bl	do_irq
	irq_restore_user_regs

	.align	5
fiq:
	get_fiq_stack
	/* someone ought to write a more effiction fiq_save_user_regs */
	irq_save_user_regs
	bl	do_fiq
	irq_restore_user_regs

#else

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ Once core 0 is ready to start the kernel, the other cores will be
        @ awakened.  Once awakened, they will show up here.  At that time,
        @ each core should enter the kernel.
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        .global _secondary_start_address
_secondary_start_address:
        .word   0x00000000

        .global _secondary_in_progress
_secondary_in_progress:
        .word   0x00000000

	.align	5
irq:

        @
        @ If this is core 0, continue as if normal...
        @

        mrc     p15, 0, r0, c0, c0, 5
        and     r0, r0, #0xf
        cmp     r0, #0
        beq     2f                              @ continue if core 0

        @
        @ If this is core 1, send it to the kernel.
        @

        mrs     r0, cpsr                        @ disable interrupts
        orr     r0, r0, #0xc0
        msr     cpsr, r0
        adr     r1, _secondary_start_address
        adr     r8, _secondary_in_progress
        mov     r3, #1
        str     r3, [r8]
        ldr     r5, =(PMR_CII_BASE)
        ldr     r3, [r5, #0xc]
        str     r3, [r5, #0x10]
        mrc     p15, 0, r0, c1, c0, 0           @ disable caches
        bic     r0, r0, #0x1000
        bic     r0, r0, #0x4
        mcr     p15, 0, r0, c1, c0, 0
        mov     r0, #0
        mcr     p15, 0, r0, c7, c7, 0           @ invalidate, flush
        mcr     p15, 0, r0, c7, c10, 4          @ barrier
        adr     r5, _secondary_start_address
        ldr     r3, [r5]
        mov     r0, #0
        ldr     r1, =(CONFIG_APP_ARCHNO)
        ldr     pc, [r5]

2:      

	get_bad_stack
	bad_save_user_regs
	bl	do_irq

	.align	5
fiq:
	get_bad_stack
	bad_save_user_regs
	bl	do_fiq

#endif
	.align 5
.global arm1136_cache_flush
arm1136_cache_flush:
		mcr	p15, 0, r1, c7, c5, 0	@ invalidate I cache
		mov	pc, lr			@ back to caller
#endif	/* CONFIG_ONENAND_IPL */
