@
@  Board specific setup info
@
@  (C) Copyright 2013
@  LSI, <www.lsi.com>
@  John Jacques <john.jacques@lsi.com>
@
@  See file CREDITS for list of people who contributed to this
@  project.
@
@  This program is free software; you can redistribute it and/or
@  modify it under the terms of the GNU General Public License as
@  published by the Free Software Foundation; either version 2 of
@  the License, or (at your option) any later version.
@
@  This program is distributed in the hope that it will be useful,
@  but WITHOUT ANY WARRANTY; without even the implied warranty of
@  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
@  GNU General Public License for more details.
@
@  You should have received a copy of the GNU General Public License
@  along with this program; if not, write to the Free Software
@  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
@  MA 02111-1307 USA
@

#include <config.h>
#include <linux/linkage.h>

#if defined(AXXIA_FORCE_NORMAL_MODE) && defined(AXXIA_FORCE_SECURE_MODE)
#error "AXXIA_FORCE_SECURE_MODE And AXXIA_FORCE_SECURE_MODE Are Both Defined!"
#endif

#if defined(AXXIA_FORCE_NORMAL_MODE)
#warning "Forcing NORMAL Mode Regardless of Chip Type"
#endif

#if defined(AXXIA_FORCE_SECURE_MODE)
#warning "Forcing SECURE Mode Regardless of Chip Type"
#endif

	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@ Setup Page Tables
	@
	@ r0 - Physical address of page table memory.
	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

_setup_page_table_stack:

	.word	0

_setup_page_tables:

	mov	r3, r0
	add	r2, r3, #0x5000

	@@
	@ Save Registers
	ldr	r0, =_setup_page_table_stack
	str	r9, [r0]

	@ Clear

	mov     r0, #0
	mov	r1, r3
1:	str     r0, [r1], #4
	cmp     r1, r2
	blt     1b

#ifdef CONFIG_SPL_BUILD

	@@
	@ SPL Page Tables

	@ First 1G
	@
	@ Physical: 0x00_2000_0000
	@  Virtual: 0x2000_0000
	@     Size: 256K

	mov	r1, r3
	add	r1, #0x800
	ldr	r0, =0x4001
	add	r0, r0, r3
	str	r0, [r1], #4

	ldr	r0, =0x20000432
	add	r1, r3, #0x4000
	add	r2, r1, #0x100
1:	str	r0, [r1], #4
	cmp	r1, r2
	add	r0, #0x1000
	blt	1b

	@ System Memory.  Not cachable or bufferable.
	@
	@ Physical: 0x20_0000_0000
	@  Virtual: 0x4000_0000
	@     Size: 1G

#ifdef SYSCACHE_ONLY_MODE
	@ When running in L3 cache, don't write to ram!
        ldr     r0, =0x50c5e		@ Start at 0x20_0000_0000
#else
        ldr     r0, =0x40c52		@ Start at 0x20_0000_0000
#endif
        add     r1, r3, #0x1000
        add     r2, r3, #0x2000
1:    	mov     r9, #0
2:      str     r0, [r1], #4            @ Each supersection is repeated
        add     r9, r9, #1              @ 16 times.
        cmp     r9, #16
        blt     2b
        add     r0, r0, #0x1000000      @ 16M
        cmp     r1, r2
        blt     1b

	@ IO.  Not cachable or bufferable.
	@
	@ Physical: 0x00_0000_0000
	@  Virtual: 0x8000_0000
	@     Size: 1G

        ldr     r0, =0x40c12		@ Start at 0x00_0000_0000
        add     r1, r3, #0x2000
        add     r2, r3, #0x3000
1:    	mov     r9, #0
2:      str     r0, [r1], #4            @ Each supersection is repeated
        add     r9, r9, #1              @ 16 times.
        cmp     r9, #16
        blt     2b
        add     r0, r0, #0x1000000      @ 16M
        cmp     r1, r2
        blt     1b

#else

	@@
	@ U-Boot Page Tables

#ifndef SYSCACHE_ONLY_MODE

	@ First 1G of RAM, sharable, cacheable and bufferable.

#ifdef RUN_UNCACHED
	ldr     r0, =0xc02
#else
	ldr     r0, =0x10c0e
#endif
        mov     r1, r3
        add     r2, r1, #0x1000

	@ First 3M as sections.

	str	r0, [r1], #4
	add	r0, r0, #0x100000
	str	r0, [r1], #4
	add	r0, r0, #0x100000
	str	r0, [r1], #4
	add	r0, r0, #0x100000

	@ Fourth 1M points to a second level table (below).

	ldr	r9, =0x4001
	add	r9, r9, r3
	str	r9, [r1], #4
	add	r0, r0, #0x100000

1:      str     r0, [r1], #4
        add     r0, r0, #0x100000
        cmp     r1, r2
        blt     1b

	@ Second Level Table

#ifdef RUN_UNCACHED
	ldr	r0, =0x300033
#else
	ldr	r0, =0x30043f
#endif
	add	r1, r3, #0x4000
	add	r2, r1, #0x300
1:	str	r0, [r1], #4
	add	r0, r0, #0x1000
	cmp	r1, r2
	blt	1b

	ldr	r0, =0x3c0033
	add	r1, r3, #0x4300
	add	r2, r1, #0x100
1:	str	r0, [r1], #4
	add	r0, r0, #0x1000
	cmp	r1, r2
	blt	1b

	@ Third 1G is IO, not cacheable or bufferable.

        ldr     r0,=0x40c52		@ Start at 0x20_0000_0000
        add     r1, r3, #0x2000
        add     r2, r3, #0x3000
1:      mov     r9, #0
2:      str     r0, [r1], #4            @ Each supersection is repeated
        add     r9, r9, #1              @ 16 times.
        cmp     r9, #16
        blt     2b
        add     r0, r0, #0x1000000      @ 16M
        cmp     r1, r2
        blt     1b

        @
        @ Fourth 1G is used by PCIe, not cacheable or bufferable.
        @
        @ Uses supersections to access IO beyond 4G physical address.
        @ PEI0 is currently using 256 MB for outbound mapping
        @ and  16 MB for MPAGE7 for config access
        @
        ldr     r0,=0x00040c72          @ Start at 0x30_0000_0000
        add     r1, r3, #0x3000
        add     r2, r3, #0x3400
1:      mov     r9, #0
2:      str     r0, [r1], #4            @ Each supersection is repeated
        add     r9, r9, #1              @ 16 times.
        cmp     r9, #16
        blt     2b
        add     r0, r0, #0x1000000      @ 16M
        cmp     r1, r2
        blt     1b

        ldr     r0,=0x38040c72          @ Start at 0x30_3800_0000
        add     r1, r3, #0x3400
        add     r2, r3, #0x3440
1:      mov     r9, #0
2:      str     r0, [r1], #4            @ Each supersection is repeated
        add     r9, r9, #1              @ 16 times.
        cmp     r9, #16
        blt     2b
        add     r0, r0, #0x1000000      @ 16M
        cmp     r1, r2
        blt     1b

        @
        @ PEI1 is currently using 256 MB for outbound mapping
        @ and  16 MB for MPAGE7 for config access
        @
        ldr     r0,=0x80040c72          @ Start at 0x30_8000_0000
        add     r1, r3, #0x3800
        add     r2, r3, #0x3c00
1:      mov     r9, #0
2:      str     r0, [r1], #4            @ Each supersection is repeated
        add     r9, r9, #1              @ 16 times.
        cmp     r9, #16
        blt     2b
        add     r0, r0, #0x1000000      @ 16M
        cmp     r1, r2
        blt     1b

        ldr     r0,=0xb8040c72          @ Start at 0x30_B800_0000
        add     r1, r3, #0x3c00
        add     r2, r3, #0x3c40
1:      mov     r9, #0
2:      str     r0, [r1], #4            @ Each supersection is repeated
        add     r9, r9, #1              @ 16 times.
        cmp     r9, #16
        blt     2b
        add     r0, r0, #0x1000000      @ 16M
        cmp     r1, r2
        blt     1b

#endif
#endif

	@@
	@ Turn it all on...

	mrc     p15, 0, r1, c0, c1, 4	@ read ID_MMFR0
	tst     r1, #0xf		@ VMSA
	mov     r0, #0
	mcr     p15, 0, r0, c7, c10, 4  @ drain write buffer
	tst     r1, #0xf		@ VMSA
	mcrne   p15, 0, r0, c8, c7, 0   @ flush I,D TLBs
	mrc     p15, 0, r0, c1, c0, 0   @ read control reg
	bic     r0, r0, #1 << 28        @ clear SCTLR.TRE
	orr     r0, r0, #0x5000         @ I-cache enaable, RR cache repl
	orr     r0, r0, #0x003c         @ write buffer
	orrne   r0, r0, #1              @ MMU enabled
	movne   r1, #0xfd
	mcrne   p15, 0, r3, c2, c0, 0   @ write page table pointer
	mcrne   p15, 0, r1, c3, c0, 0   @ write domain access control
	mcr     p15, 0, r0, c7, c5, 4   @ ISB
	mcr     p15, 0, r0, c1, c0, 0   @ write control register
	mrc     p15, 0, r0, c1, c0, 0   @ and read it back
	mov     r0, #0
	mcr     p15, 0, r0, c7, c5, 4   @ ISB

	@@
	@ Restore Registers
	ldr	r0, =_setup_page_table_stack
	ldr	r9, [r0]

	@@
	@ Return
	bx	lr

ENTRY(setup_page_tables)
	mov	r12, lr
	bl	_setup_page_tables
	mov	lr, r12
	bx	lr
ENDPROC(setup_page_tables)

	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@ In some cases (memory tests) it makes sense to run uncached.
	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#ifndef CONFIG_SPL_BUILD

	@@
	@ spin_loop

spin_loop_start:

	adr	r0, spin_loop_release
1:	ldr	r1, [r0]
	cmp	r1, #0
	beq	1b
	mov	pc, r1

	.align	4

spin_loop_release:

	.word	0

spin_loop_end:

	.global	spin_loop_release_offset

spin_loop_release_offset:

	.word	(spin_loop_release - spin_loop_start)

#endif

	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@ lowlevel_init
	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	.global	lowlevel_init

lowlevel_init:

#ifdef CONFIG_SPL_BUILD

	@@
	@ Set the secure_access bit in dickens.
	mov	r0, #0
	mov	r1, #1
	str	r1, [r0]

#else

	@@
	@ Get the CPU number.

	mrc	p15, 0, r0, c0, c0, 5
	ands	r10, r0, #3
	bne	set_actlr2		@ If not 0, 4, 8, or 12...

	@@
	@ If this is core 0 of cluster 0, set up the spin loop.

	lsr	r11, r0, #8
	ands	r11, r11, #0xf
	bne	set_l2ctlr

	@@
	@ Copy spin_loop (above) to _spin_table_start_ofs

	adr	r0, spin_loop_start
	adr	r1, spin_loop_end
	ldr	r2, =_spin_table_start_ofs
	ldr	r2, [r2]
1:	ldr	r3, [r0], #4
	str	r3, [r2], #4
	cmp	r0, r1
	blt	1b
	dsb

#endif

	@@
	@ Set up the MMU

	ldr	r0, =_page_table_start
	ldr	r0, [r0]
	mov	r8, lr
	bl	_setup_page_tables
	mov	lr, r8

#ifdef CONFIG_HW_WATCHDOG

	@@
	@ Re-enable the watchdog.

	ldr	r3, =SYSCON
	add	r3, r3, #0x1000
	mov	r0, #0xab
	str	r0, [r3, #0]
	ldr	r0, [r3, #0x4]
	orr	r0, r0, #0x40
	str	r0, [r3, #0x4]
	mov	r0, #0x80000000
	str	r0, [r3, #0x80c]
	ldr	r0, [r3, #0x8]
	orr	r0, r0, #0x80
	str	r0, [r3, #0x8]
	mov	r0, #0
	str	r0, [r3, #0]
	ldr	r3, =TIMER5
	mov	r0, #0
	str	r0, [r3, #0x8]
	ldr	r0, =0xffffffff
	str	r0, [r3]
	str	r0, [r3, #0x4]
	mov	r0, #0xe2
	str	r0, [r3, #0x8]

#endif

	@@
	@ Read pfuse into r7 and save

#ifdef CONFIG_AXXIA_EMU
	mov	r7, #0
#else
	ldr	r3, =SYSCON
	ldr	r7, [r3, #0x34]
#ifdef AXXIA_OR_IN_FUSE_FORCE
	add	r3, r3, #0x1000
	ldr	r8, [r3, #0x64]
	and	r8, r8, #0x3800
	lsl	r8, r8, #13
	orr	r7, r7, r8
	ldr	r8, [r3, #0x64]
	and	r8, r8, #0xf0
	lsl	r8, r8, #16
	orr	r7, r7, r8
#endif
#endif
	ldr	r3, =pfuse
	str	r7, [r3]

	@@
	@ Initialize the L2CTLR register (primary core in each cluster).

set_l2ctlr:

	mrc	p15, 1, r0, c9, c0, 2
	orr	r0, r0, #(1 << 1)
	orr	r0, r0, #(1 << 21)
	mcr	p15, 1, r0, c9, c0, 2

	@@
	@ Initialize the L2ACTLR register (primary core in each cluster).

set_l2actlr:

	mrc	p15, 1, r0, c15, c0, 0
	orr	r0, r0, #(1 << 3)
	orr	r0, r0, #(1 << 7)
	orr	r0, r0, #(1 << 12)
	orr	r0, r0, #(1 << 13)
	orr	r0, r0, #(1 << 14)
	mcr	p15, 1, r0, c15, c0, 0

	@@
	@ Workaround for ARM errata 811981, clusters 1, 2, and 3.
	@ Cluster 0 is handled later to allow console output if there is
	@ a failure.  Other clusters will fail silently.

	mrc	p15, 0, r0, c0, c0, 5
	lsr	r0, r0, #8
	ands	r0, r0, #0xf
	beq	wa_811981_okay

	@ Make sure cntpct is non-zero.

wa_811981_zero:

	mrrc	p15, 0, r10, r11, c14
	orr	r0, r10, r11
	cmp	r0, #0
	beq	wa_811981_zero

	@ Make sure cntpct is counting.

wa_811981_stuck:

	mrrc	p15, 0, r0, r1, c14
	cmp	r0, r10
	bne	wa_811981_okay
	cmp	r1, r11
	bne	wa_811981_okay
	b	wa_811981_stuck

wa_811981_okay:

	@@
	@ Iniitalize the ACTLR2 register (all cores).

set_actlr2:

	mrc 	p15, 1, r0, c15, c0, 4
	orr 	r0, r0, #(1 << 0)
	mcr 	p15, 1, r0, c15, c0, 4

#ifndef CONFIG_SPL_BUILD

	@@
	@ Set the CNTFRQ
#ifdef CONFIG_AXXIA_SIM
	ldr	r0, =100000000
#else
	ldr	r0, =256000000
#endif
	mcr	p15, 0, r0, c14, c0, 0

	@@
	@ Allow User Mode Access to the Performance Counter
	@ and Disable Overflow Interrupts

	ldr	r0, =1
	mcr	p15, 0, r0, c9, c14, 0
	ldr	r0, =0x8000000f
	mcr	p15, 0, r0, c9, c14, 2

	@@
	@ If not core 0, cluster 0, load pfuse into r7
	mrc	p15, 0, r0, c0, c0, 5
	ands	r10, r0, #3
	lsr	r11, r0, #8
	ands	r11, r11, #0xf
	orr	r0, r10, r11
	cmp	r0, #0
	beq	1f
	ldr	r0, =pfuse
	ldr	r7, [r0]
1:

#if !defined(CONFIG_AXXIA_EMU) && !defined(CONFIG_AXXIA_SIM)
	@@
	@ Turn 'wfe' into a nop for v1.0 silicon
	@ by setting bit 7 in the ACTLR.
	and	r4, r7, #0x7e0
	mov	r4, r4, lsr#5
	cmp	r4, #0
	bne	1f
	@ read the ACTLR, set bit 7, write the ACTLR
	mrc	p15, 0, r0, c1, c0, 1
	orr	r0, r0, #(1 << 7)
	mcr	p15, 0, r0, c1, c0, 1
1:
#endif

	@@
	@ The rest is only for core 0 of cluster 0.

	mrc	p15, 0, r0, c0, c0, 5
	ands	r10, r0, #3
	lsr	r11, r0, #8
	ands	r11, r11, #0xf
	orr	r0, r10, r11
	cmp	r0, #0
	bne	secondary_boot
	b	primary_boot

secondary_boot:

#ifdef AXXIA_FORCE_NORMAL_MODE
	b	secondary_boot_normal
#endif

#ifdef AXXIA_FORCE_SECURE_MODE
	b	secondary_boot_secure
#endif

	and	r4, r7, #0x7e0
	mov	r4, r4, lsr#5
	cmp	r4, #0
	beq	secondary_boot_secure
	b	secondary_boot_normal

secondary_boot_secure:

	b	secondary_spin

secondary_boot_normal:

	@ Write page table pointer for other CPUs
	ldr	r3, =hypmode_pgtable

	@@
	@ Turn it all on...
	mrc     p15, 0, r11, c0, c1, 4  @ read ID_MMFR0
	tst     r11, #0xf               @ VMSA
	mov     r0, #0
	mcr     p15, 0, r0, c7, c10, 4  @ drain write buffer
	tst     r11, #0xf               @ VMSA
	mcrne   p15, 0, r0, c8, c7, 0   @ flush I,D TLBs
	mrc     p15, 0, r0, c1, c0, 0   @ read control reg
	bic     r0, r0, #1 << 28        @ clear SCTLR.TRE
	orr     r0, r0, #0x5000         @ I-cache enable, RR cache repl
	orr     r0, r0, #0x003c         @ write buffer
	orrne   r0, r0, #1              @ MMU enabled
	movne   r1, #-1
	mcrne   p15, 0, r3, c2, c0, 0   @ load page table pointer
	mcrne   p15, 0, r1, c3, c0, 0   @ load domain access control
	mcr     p15, 0, r0, c7, c5, 4   @ ISB
	mcr     p15, 0, r0, c1, c0, 0   @ load control register
	mrc     p15, 0, r0, c1, c0, 0   @ and read it back
	mov     r0, #0
	mcr     p15, 0, r0, c7, c5, 4   @ ISB

	bl	arch_timer_init
	bl	non_secure_init
	bl	monitor_init
	bl	enter_ns
	bl	enter_hyp
	b	secondary_spin

secondary_spin:

	ldr	r0, =_spin_table_start_ofs
	ldr	r0, [r0]
	mov	pc, r0

#endif

primary_boot:

#ifndef CONFIG_SPL_BUILD

	@@
	@ Clear BSS
	mov	r0, #0
	ldr	r1, = _bss_start_ofs
	ldr	r1, [r1]
	ldr	r2, = _bss_end_ofs
	ldr	r2, [r2]
1:	str	r0, [r1], #4
	cmp	r1, r2
	blt	1b

#ifdef AXXIA_FORCE_NORMAL_MODE
	b	primary_boot_normal
#endif

#ifdef AXXIA_FORCE_SECURE_MODE
	b	primary_boot_secure
#endif

	and	r4, r7, #0x7e0
	mov	r4, r4, lsr#5
	cmp	r4, #0
	beq	primary_boot_secure
	b	primary_boot_normal

primary_boot_normal:

	bl	arch_timer_init
	bl	non_secure_init
	bl	monitor_init

primary_boot_secure:

#endif

	@@
	@ Return
	bl	_main

	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@
	@ Hyp Mode Page Table for Secondary CPUs
	@
	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#ifndef CONFIG_SPL_BUILD

	.ltorg
	.balign	0x4000
	.global	hypmode_pgtable
	
hypmode_pgtable:
	
	/* 32M of RAM: Virtual: 0x00000000 - 0x3fffffff */
	.rept	16
#ifdef RUN_UNCACHED
	.word	0x00000c12
#else
	.word	0x00010c1e
#endif
	.endr

	.rept	16
#ifdef RUN_UNCACHED
	.word	0x01000c12
#else
	.word	0x01010c1e
#endif
	.endr

	.fill	0x1000-128, 1, 0

	/* Virtual: 0x40000000 - 0x7fffffff */
	.fill	0x1000,   1, 0

	/* GIC as non cached: Virtual: 0x80000000 - 0xbfffffff */
	.rept	16
	.word	0x00040c52
	.endr
	.rept	16
	.word	0x01040c52
	.endr
	.rept	16
	.word	0x02040c52
	.endr
	.rept	16
	.word	0x03040c52
	.endr
	.fill	0x1000-256, 1, 0

#endif

###
### Local Variables:
### asm-comment-char: ?\@
### End:
###
