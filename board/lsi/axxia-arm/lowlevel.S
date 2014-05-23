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

	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@ Setup Page Tables
	@
	@ r0 - Physical address of page table memory.
	@ r1 - NS bit
	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

setup_page_tables:

	mov	r3, r0
	add	r2, r3, #0x5000
	mov	r4, r1

	@ Clear

	mov     r0, #0
	mov	r1, r3
1:	str     r0, [r1], #4
	cmp     r1, r2
	blt     1b

#ifdef CONFIG_SPL_BUILD

	@@
	@ SPL Page Tables

	@ First 1G as a 1:1 mapping.  Covers the SPL.  Cachable and bufferable.
	@
	@ Physical: 0x00_0000_0000
	@  Virtual: 0x0000_0000
	@     Size: 1G

#ifdef RUN_UNCACHED
        ldr     r0, =0x40c02		@ Start at 0x00_0000_0000
#else
        ldr     r0, =0x50c0e		@ Start at 0x00_0000_0000
#endif
	cmp	r4, #0
	orrne	r0, r0, #0x8000		@ Set the NS bit if r4 is not 0
        mov     r1, r3
        add     r2, r3, #0x1000
1:    	mov     r9, #0
2:      str     r0, [r1], #4            @ Each supersection is repeated
        add     r9, r9, #1              @ 16 times.
        cmp     r9, #16
        blt     2b
        add     r0, r0, #0x1000000      @ 16M
        cmp     r1, r2
        blt     1b

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
	cmp	r4, #0
	orrne	r0, r0, #0x80000	@ Set the NS bit if r4 is not 0
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
	cmp	r4, #0
	orrne	r0, r0, #0x80000	@ Set the NS bit if r4 is not 0
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
	cmp	r4, #0
	orrne	r0, r0, #0x80000	@ Set the NS bit if r4 is not 0
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
	cmp	r4, #0
	orrne	r9, r9, #0x4		@ Set the NS bit if r4 is not 0
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
	cmp	r4, #0
	orrne	r0, r0, #0x80000	@ Set the NS bit if r4 is not 0
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
	cmp	r4, #0
	orrne	r0, r0, #0x80000	@ Set the NS bit if r4 is not 0
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
	cmp	r4, #0
	orrne	r0, r0, #0x80000	@ Set the NS bit if r4 is not 0
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
	cmp	r4, #0
	orrne	r0, r0, #0x80000	@ Set the NS bit if r4 is not 0
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
	cmp	r4, #0
	orrne	r0, r0, #0x80000	@ Set the NS bit if r4 is not 0
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

	mov	pc, lr			@ return

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
	mov	r0, #0
	mov	r1, #1
	str	r1, [r0]
#endif

#ifndef CONFIG_SPL_BUILD

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
	orr	r0, r0, #(1 << 12)
	orr	r0, r0, #(1 << 13)
	orr	r0, r0, #(1 << 14)
	mcr	p15, 1, r0, c15, c0, 0

	@@
	@ Iniitalize the ACTLR2 register (all cores).

set_actlr2:

	mrc 	p15, 1, r0, c15, c0, 4
	orr 	r0, r0, #(1 << 0)
	mcr 	p15, 1, r0, c15, c0, 4

#ifndef CONFIG_SPL_BUILD

	@@
	@ Allow User Mode Access to the Performance Counter
	@ and Disable Overflow Interrupts

	ldr	r0, =1
	mcr	p15, 0, r0, c9, c14, 0
	ldr	r0, =0x8000000f
	mcr	p15, 0, r0, c9, c14, 2

	@@
	@ Set the CNTFRQ
#ifdef CONFIG_AXXIA_SIM
	ldr	r0, =100000000
#else
	ldr	r0, =256000000
#endif
	mcr	p15, 0, r0, c14, c0, 0

#endif

	@@
	@ Non-Secure Mode/Secure Mode
	@
	@ Set up the page tables, initialize "pfuse", and set the mode
	@ based on silicon version (v1.0 => secure, v1.1 => non-secure).

#ifndef CONFIG_SPL_BUILD

	@ Set up the MMU, in secure mode, to enable access to the GIC.

	ldr	r0, =_secure_page_table_start
	ldr	r0, [r0]
	mov	r1, #0
	mov	r8, lr
	bl	setup_page_tables
	mov	lr, r8

	@ Turn it all on...

	ldr	r3, =_secure_page_table_start
	ldr	r3, [r3]
	mrc     p15, 0, r11, c0, c1, 4  @ read ID_MMFR0
	tst     r11, #0xf               @ VMSA
	mov     r0, #0
	mcr     p15, 0, r0, c7, c10, 4  @ drain write buffer
	tst     r11, #0xf               @ VMSA
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

	@ If this is v1.0 silicon, switch to secure mode

#ifdef CONFIG_AXXIA_EMU
#ifdef AXXIA_5500_EMU_V_1_0
	mov	r7, #0
#else
	mov	r7, #0x29
#endif
#else
	ldr	r3, =SYSCON
	ldr	r7, [r3, #0x34]
#endif
	ldr	r3, =pfuse
	str	r7, [r3]
	and	r1, r7, #0x7e0
	mov	r1, r1, lsr#5
	cmp	r1, #0
	bne	continue_nonsecure

	@ Turn it all off...

	ldr	r3, =_secure_page_table_start
	ldr	r3, [r3]
	mrc     p15, 0, r11, c0, c1, 4  @ read ID_MMFR0
	tst     r11, #0xf               @ VMSA
	mov     r0, #0
	mcr     p15, 0, r0, c7, c10, 4  @ drain write buffer
	tst     r11, #0xf               @ VMSA
	mcrne   p15, 0, r0, c8, c7, 0   @ flush I,D TLBs
	mrc     p15, 0, r0, c1, c0, 0   @ read control reg
	bic     r0, r0, #0x1000         @ Disable I-Cache
	bic     r0, r0, #0x5    	@ Disable D-Cache and MMU
	mcr     p15, 0, r0, c7, c5, 4   @ ISB
	mcr     p15, 0, r0, c1, c0, 0   @ write control register
	mrc     p15, 0, r0, c1, c0, 0   @ and read it back
	mov     r0, #0
	mcr     p15, 0, r0, c7, c5, 4   @ ISB

	b	secure_mode

continue_nonsecure:

	@ Set all interrupts to be non-secure

	ldr	r3, =GIC_DIST_BASE
	ldr	r1, [r3, #0x04]
	and	r1, r1, #0x1f
	add	r1, r1, #1
	add	r2, r3, #0x80
	add	r1, r1, r2
	mov	r4, #-1
1:	str	r4, [r2], #4
	cmp	r2, r1
	blt	1b

	@ Disable group 0 interrupts and enable group 1 interrupts

	ldr	r4, [r3]
	ldr	r2, =0xfffffffe
	and	r4, r4, r2
	orr	r4, r4, #2
	str	r4, [r3]

	@ Set GIC priority mask, bit 7

	ldr	r3, =GIC_CPU_BASE
	ldr	r4, [r3]
	orr	r4, r4, #2
	str	r4, [r3]


	@ Set NSACR to allow coprocessor access from non-secure
	mrc	p15, 0, r0, c1, c1, 2
	ldr	r1, =0x43fff
	orr	r0, r0, r1
	mcr	p15, 0, r0, c1, c1, 2

	@ Turn it all off...

	ldr	r3, =_secure_page_table_start
	ldr	r3, [r3]
	mrc     p15, 0, r11, c0, c1, 4  @ read ID_MMFR0
	tst     r11, #0xf               @ VMSA
	mov     r0, #0
	mcr     p15, 0, r0, c7, c10, 4  @ drain write buffer
	tst     r11, #0xf               @ VMSA
	mcrne   p15, 0, r0, c8, c7, 0   @ flush I,D TLBs
	mrc     p15, 0, r0, c1, c0, 0   @ read control reg
	bic     r0, r0, #0x1000         @ Disable I-Cache
	bic     r0, r0, #0x5    	@ Disable D-Cache and MMU
	mcr     p15, 0, r0, c7, c5, 4   @ ISB
	mcr     p15, 0, r0, c1, c0, 0   @ write control register
	mrc     p15, 0, r0, c1, c0, 0   @ and read it back
	mov     r0, #0
	mcr     p15, 0, r0, c7, c5, 4   @ ISB

	@ Get the core and cluster numbers

	mrc	p15, 0, r0, c0, c0, 5
	ands	r10, r0, #3
	lsr	r11, r0, #8
	ands	r11, r11, #0xf
	orr	r9, r10, r11

	@ Initialize the montior if core 0, cluster 0
	@ Enter Non-Secure mode and Enable Hyp

	cmp	r9, #0
	beq	1f

	@ Not core 0, cluster 0

	b	jump_to_spin_table

1:

	@ Core 0, cluster 0, or SPL
	b	turn_on_mmu

	@@
	@ Secure Mode

secure_mode:

	@ Get the core and cluster numbers

	mrc	p15, 0, r0, c0, c0, 5
	ands	r10, r0, #3
	lsr	r11, r0, #8
	ands	r11, r11, #0xf
	orr	r0, r10, r11
	cmp	r0, #0
	bne	jump_to_spin_table

#endif

	b	turn_on_mmu

	@@
	@ Jump to the spin table

#ifndef CONFIG_SPL_BUILD
jump_to_spin_table:

#if !defined(CONFIG_AXXIA_EMU) && !defined(CONFIG_AXXIA_SIM)
	@@
	@ Turn 'wfe' into a nop for v1.0 silicon
	@ by setting bit 7 in the ACTLR.
	ldr	r3, =pfuse
	ldr	r4, [r3]
	and	r4, r4, #0x7e0
	mov	r4, r4, lsr#5
	cmp	r4, #0
	bne	1f
	@ read the ACTLR, set bit 7, write the ACTLR
	mrc	p15, 0, r0, c1, c0, 1
	orr	r0, r0, #(1 << 7)
	mcr	p15, 0, r0, c1, c0, 1
1:
#endif

	ldr	r0, =_spin_table_start_ofs
	ldr	r0, [r0]
	mov	pc, r0
#endif

	@@
	@ Turn on the MMU

turn_on_mmu:

#ifndef CONFIG_SPL_BUILD
	ldr	r0, =pfuse
	str	r7, [r0]
	ldr	r1, [r0]
	and	r1, r1, #0x7e0
	mov	r1, r1, lsr#5
	cmp	r1, #0
	beq	1f
	mov	r1, #1
	b	2f
1:	mov	r1, #0
2:
#else
	mov	r1, #0
#endif
	ldr	r0, =_page_table_start
	ldr	r0, [r0]
	mov	r8, lr
	bl	setup_page_tables
	mov	lr, r8

	@ Turn it all on...

	ldr	r3, =_page_table_start
	ldr	r3, [r3]
	mrc     p15, 0, r11, c0, c1, 4  @ read ID_MMFR0
	tst     r11, #0xf               @ VMSA
	mov     r0, #0
	mcr     p15, 0, r0, c7, c10, 4  @ drain write buffer
	tst     r11, #0xf               @ VMSA
	mcrne   p15, 0, r0, c8, c7, 0   @ flush I,D TLBs
	mrc     p15, 0, r0, c1, c0, 0   @ read control reg
	bic     r0, r0, #1 << 28        @ clear SCTLR.TRE
	orr     r0, r0, #0x5000         @ I-cache enaable, RR cache repl
	orr     r0, r0, #0x003c         @ write buffer
	orrne   r0, r0, #1              @ MMU enabled
	movne   r1, #0xfd
	mcrne   p15, 0, r3, c2, c0, 0   @ load page table pointer
	mcrne   p15, 0, r1, c3, c0, 0   @ load domain access control
	mcr     p15, 0, r0, c7, c5, 4   @ ISB
	mcr     p15, 0, r0, c1, c0, 0   @ load control register
	mrc     p15, 0, r0, c1, c0, 0   @ and read it back
	mov     r0, #0
	mcr     p15, 0, r0, c7, c5, 4   @ ISB

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

	@@
	@ Turn 'wfe' into a nop for v1.0 silicon
	@ by setting bit 7 in the ACTLR.
#if !defined(CONFIG_AXXIA_EMU) && !defined(CONFIG_AXXIA_SIM)
	ldr	r3, =pfuse
	ldr	r4, [r3]
	and	r3, r4, #0x7e0
	mov	r3, r3, lsr#5
	cmp	r3, #0
	bne	1f
	@ read the ACTLR, set bit 7, write the ACTLR
	mrc	p15, 0, r0, c1, c0, 1
	orr	r0, r0, #(1 << 7)
	mcr	p15, 0, r0, c1, c0, 1
1:
#endif
#endif

	@@
	@ Return
	mov	pc, lr

###
### Local Variables:
### asm-comment-char: ?\@
### End:
###
