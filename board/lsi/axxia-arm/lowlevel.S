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

#ifndef CONFIG_SPL_BUILD

	@@
	@ Get the CPU number.

	mrc	p15, 0, r0, c0, c0, 5
	ands	r10, r0, #3
	bne	set_actlr2

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

	@@
	@ Set the CNTFRQ

#ifdef CONFIG_AXXIA_EMU
	ldr	r0, =4096000
#else
	ldr	r0, =256000000
#endif
	mcr	p15, 0, r0, c14, c0, 0

#ifndef CONFIG_SPL_BUILD

	@@
	@ The rest is only for core 0 of cluster 0.

	orr	r0, r10, r11
	cmp	r0, #0
	bne	jump_to_spin_table
	b	clear_page_tables

	@@
	@ All others, to the spin table.

jump_to_spin_table:	

	ldr	r0, =_spin_table_start_ofs
	ldr	r0, [r0]
	mov	pc, r0

#endif

	@@
	@ Clear the page table(s).

clear_page_tables:

	mov     r0, #0
	ldr 	r3, =_page_table_start
	ldr	r3, [r3]
	mov     r1, r3
	ldr	r2, =_page_table_end
	ldr	r2, [r2]
1:	str     r0, [r1], #4
	cmp     r1, r2
	blt     1b

#ifdef CONFIG_SPL_BUILD

	@@@@@@
	@@ SPL

	@@ Set up the page tables

	@ First 1G as a 1:1 mapping.  Covers the SPL.  Cachable and bufferable.
	@
	@ Physical: 0x00_0000_0000
	@  Virtual: 0x0000_0000
	@     Size: 1G

        ldr     r0, =0x40c1e		@ Start at 0x00_0000_0000
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

#ifndef SYSCACHE_ONLY_MODE
        ldr     r0, =0x40c52		@ Start at 0x20_0000_0000
#else
        ldr     r0, =0x50c5e		@ Start at 0x20_0000_0000
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
	orr     r0, r0, #0x5000         @ I-cache enaable, RR cache repl
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

#else
#ifndef SYSCACHE_ONLY_MODE

	@@@@@@@@@@@@
	@@ 3rd Stage

	@@
	@ Set up the page tables.

	@ First 1G of RAM, sharable, cacheable and bufferable.

	ldr     r0, =0x11c1e
        mov     r1, r3
        add     r2, r1, #0x1000
	str	r0, [r1], #4
	add	r0, r0, #0x100000
	str	r0, [r1], #4
	add	r0, r0, #0x100000
	str	r0, [r1], #4
	add	r0, r0, #0x100000

	ldr	r9, =0x4001
	add	r9, r9, r3
	str	r9, [r1], #4
	add	r0, r0, #0x100000

1:      str     r0, [r1], #4
        add     r0, r0, #0x100000
        cmp     r1, r2
        blt     1b

	@ Second Level Table

	ldr	r0, =0x30043f
	add	r1, r3, #0x4000
	add	r2, r1, #0x300
1:	str	r0, [r1], #4
	add	r0, r0, #0x1000
	cmp	r1, r2
	blt	1b

	ldr	r0, =0x3c0433
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
        ldr     r0,=0x00040cd2          @ Start at 0x30_0000_0000
        add     r1, r3, #0x3000
        mov     r9, #0
1:      str     r0, [r1], #4            @ Each supersection is repeated
        add     r9, r9, #1              @ 16 times.
        cmp     r9, #16
        blt     1b

        ldr     r0,=0x38040cd2          @ Start at 0x30_3800_0000
        add     r1, r3, #0x3040
        str     r0, [r1], #4            @ Each supersection is repeated once

        @
        @ PEI1 is currently using 256 MB for outbound mapping
        @ and  16 MB for MPAGE7 for config access
        @
        ldr     r0,=0x80040cd2          @ Start at 0x30_8000_0000
        add     r1, r3, #0x3080
        mov     r9, #0
1:      str     r0, [r1], #4            @ Each supersection is repeated
        add     r9, r9, #1              @ 16 times.
        cmp     r9, #16
        blt     1b

        ldr     r0,=0xb8040cd2          @ Start at 0x30_B800_0000
        add     r1, r3, #0x30c0
        str     r0, [r1], #4            @ Each supersection is repeated once

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
	orr     r0, r0, #0x5000         @ I-cache enaable, RR cache repl
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

#endif
#endif

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

#endif

	mov	pc, lr

###
### Local Variables:
### asm-comment-char: ?\@
### End:
###
