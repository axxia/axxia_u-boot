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

	.global	lowlevel_init

lowlevel_init:

#ifdef CONFIG_SPL_BUILD

	@@@@@@
	@@ SPL

	@@ Set up the page tables

	@ Clear

	mov     r0, #0
	mov 	r3, #0x40000
	mov     r1, r3
	add     r2, r3, #0x4000
1:	str     r0, [r1], #4
	cmp     r1, r2
	blt     1b

	@ First 1G of RAM, cacheable and bufferable.

        ldr     r0, =0x40c1e
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

	@ Second 1G of RAM, not cacheable and not bufferable.

        ldr     r0, =0x40040c12
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

	@ Third 1G is IO, not cacheable or bufferable.

        ldr     r0,=0x10040c52          @ Start at 0x20_1000_0000
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

	@@ Turn it all on...

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

	@ Load page table pointer
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

	@@@@@@@@@@@@
	@@ 3rd Stage

	@@ Auxiliary control register 2

	@Read Auxiliary Control Register 2
	mrc p15, 1, r0, c15, c0, 4

	@Set bit 0 execute data cache clean as data cache clean/invalidate
	orr r0, r0, #(0x1 << 0)
	
	@Write Auxiliary Control Register 2
	mcr p15, 1, r0, c15, c0, 4

	@@ Set up the page tables

	@ Clear

	mov     r0, #0
	mov 	r3, #0x40000
	mov     r1, r3
	add     r2, r3, #0x4000
1:	str     r0, [r1], #4
	cmp     r1, r2
	blt     1b

	@ First 1G of RAM, cacheable and bufferable.

        ldr     r0, =0x40c1e
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

	@ Second 1G of RAM, not cacheable and not bufferable.

        ldr     r0, =0x40040c12
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

	@ Third 1G is IO, not cacheable or bufferable.

        ldr     r0,=0x10040c52          @ Start at 0x20_1000_0000
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

	@@ Turn it all on...

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

	@ Load page table pointer
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

	mov	pc, lr

###
### Local Variables:
### asm-comment-char: ?\@
### End:
###
