/* Copyright (C) 2006 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   Contributed by MontaVista Software, Inc. (written by Nicolas Pitre)

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#include <config.h>

#ifdef __HAVE_ARCH_MEMSET

/*
 * Data preload for architectures that support it (ARM V5TE and above)
 */
#if 0
#if defined( LSI_ARCH_APP3K )
#define PLD(code...)    code
#endif
#else
#define PLD(code...)
#endif

/*
 * This can be used to enable code to cacheline align the source pointer.
 * Experiments on tested architectures (StrongARM and XScale) didn't show
 * this a worthwhile thing to do.  That might be different in the future.
 */
//#define CALGN(code...)        code
#define CALGN(code...)

/*
 * Endian independent macros for shifting bytes within registers.
 */
#ifndef __ARMEB__
#define pull            lsr
#define push            lsl
#else
#define pull            lsl
#define push            lsr
#endif

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ memcpy
        @
        @ void * memcpy( void * dest, const void * src, size_t n )
        @ 
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        .global memcpy

memcpy:

		stmdb   sp!,{r0,r4,lr}

		subs	r2, r2, #4
		blt	8f
		ands	ip, r0, #3
	PLD(	pld	[r1, #0]		)
		bne	9f
		ands	ip, r1, #3
		bne	10f

1:		subs	r2, r2, #(28)
		stmfd	sp!, {r5 - r8}
		blt	5f

	CALGN(	ands	ip, r1, #31		)
	CALGN(	rsb	r3, ip, #32		)
	CALGN(	sbcnes	r4, r3, r2		)  @ C is always set here
	CALGN(	bcs	2f			)
	CALGN(	adr	r4, 6f			)
	CALGN(	subs	r2, r2, r3		)  @ C gets set
	CALGN(	add	pc, r4, ip		)

	PLD(	pld	[r1, #0]		)
2:	PLD(	subs	r2, r2, #96		)
	PLD(	pld	[r1, #28]		)
	PLD(	blt	4f			)
	PLD(	pld	[r1, #60]		)
	PLD(	pld	[r1, #92]		)

3:	PLD(	pld	[r1, #124]		)
4:		ldmia	r1!, {r3, r4, r5, r6, r7, r8, ip, lr}
		subs	r2, r2, #32
		stmia	r0!, {r3, r4, r5, r6, r7, r8, ip, lr}
		bge	3b
	PLD(	cmn	r2, #96			)
	PLD(	bge	4b			)

5:		ands	ip, r2, #28
		rsb	ip, ip, #32
		addne	pc, pc, ip		@ C is always clear here
		b	7f
6:		nop
		ldr	r3, [r1], #4
		ldr	r4, [r1], #4
		ldr	r5, [r1], #4
		ldr	r6, [r1], #4
		ldr	r7, [r1], #4
		ldr	r8, [r1], #4
		ldr	lr, [r1], #4

		add	pc, pc, ip
		nop
		nop
		str	r3, [r0], #4
		str	r4, [r0], #4
		str	r5, [r0], #4
		str	r6, [r0], #4
		str	r7, [r0], #4
		str	r8, [r0], #4
		str	lr, [r0], #4

	CALGN(	bcs	2b			)

7:		ldmfd	sp!, {r5 - r8}

8:		movs	r2, r2, lsl #31
		ldrneb	r3, [r1], #1
		ldrcsb	r4, [r1], #1
		ldrcsb	ip, [r1]
		strneb	r3, [r0], #1
		strcsb	r4, [r0], #1
		strcsb	ip, [r0]

		ldmfd	sp!, {r0, r4, pc}

9:		rsb	ip, ip, #4
		cmp	ip, #2
		ldrgtb	r3, [r1], #1
		ldrgeb	r4, [r1], #1
		ldrb	lr, [r1], #1
		strgtb	r3, [r0], #1
		strgeb	r4, [r0], #1
		subs	r2, r2, ip
		strb	lr, [r0], #1
		blt	8b
		ands	ip, r1, #3
		beq	1b

10:		bic	r1, r1, #3
		cmp	ip, #2
		ldr	lr, [r1], #4
		beq	17f
		bgt	18f


		.macro	forward_copy_shift pull push

		subs	r2, r2, #28
		blt	14f

	CALGN(	ands	ip, r1, #31		)
	CALGN(	rsb	ip, ip, #32		)
	CALGN(	sbcnes	r4, ip, r2		)  @ C is always set here
	CALGN(	subcc	r2, r2, ip		)
	CALGN(	bcc	15f			)

11:		stmfd	sp!, {r5 - r9}

	PLD(	pld	[r1, #0]		)
	PLD(	subs	r2, r2, #96		)
	PLD(	pld	[r1, #28]		)
	PLD(	blt	13f			)
	PLD(	pld	[r1, #60]		)
	PLD(	pld	[r1, #92]		)

12:	PLD(	pld	[r1, #124]		)
13:		ldmia	r1!, {r4, r5, r6, r7}
		mov	r3, lr, pull #\pull
		subs	r2, r2, #32
		ldmia	r1!, {r8, r9, ip, lr}
		orr	r3, r3, r4, push #\push
		mov	r4, r4, pull #\pull
		orr	r4, r4, r5, push #\push
		mov	r5, r5, pull #\pull
		orr	r5, r5, r6, push #\push
		mov	r6, r6, pull #\pull
		orr	r6, r6, r7, push #\push
		mov	r7, r7, pull #\pull
		orr	r7, r7, r8, push #\push
		mov	r8, r8, pull #\pull
		orr	r8, r8, r9, push #\push
		mov	r9, r9, pull #\pull
		orr	r9, r9, ip, push #\push
		mov	ip, ip, pull #\pull
		orr	ip, ip, lr, push #\push
		stmia	r0!, {r3, r4, r5, r6, r7, r8, r9, ip}
		bge	12b
	PLD(	cmn	r2, #96			)
	PLD(	bge	13b			)

		ldmfd	sp!, {r5 - r9}

14:		ands	ip, r2, #28
		beq	16f

15:		mov	r3, lr, pull #\pull
		ldr	lr, [r1], #4
		subs	ip, ip, #4
		orr	r3, r3, lr, push #\push
		str	r3, [r0], #4
		bgt	15b
	CALGN(	cmp	r2, #0			)
	CALGN(	bge	11b			)

16:		sub	r1, r1, #(\push / 8)
		b	8b

		.endm


		forward_copy_shift	pull=8	push=24

17:		forward_copy_shift	pull=16	push=16

18:		forward_copy_shift	pull=24	push=8

#if 0
/*********************************************************************
 *
 * memcpy.S
 *
 * An implementation of the Linux ARM architecture specific memset.
 *
 * r0 is the destination
 * r1 is the source
 * r2 is the number of bytes
 *
 * r0 is returned unchanged
 *
 *********************************************************************/

#include <config.h>
        
/* Data preload for architectures that support it. */
#if defined( LSI_ARCH_APP3K )
#define PLD( code... ) code
#else
#define PLD( code... )
#endif

#define pull            lsl
#define push            lsr
#define byte(x)         ((3-x)*8)

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ fcs (forward copy shift)
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        
        .macro  fcs pull push

        cmp     r2, #12
PLD(    pld     [r1, #0]                )
        blt     14f
        subs    r2, r2, #28
        blt     12f

PLD(    subs    r2, r2, #97             )
PLD(    blt     11f                     )
PLD(    pld     [r1, #32]               )

        @ cache alignment

PLD(    rsb     ip, r1, #36             )
PLD(    pld     [r1, #64]               )
PLD(    ands    ip, ip, #31             )
PLD(    pld     [r1, #96]               )
PLD(    beq     10f                     )
PLD(    cmp     r2, ip                  )
PLD(    pld     [r1, #128]              )
PLD(    blt     10f                     )
PLD(    sub     r2, r2, ip              )
        
9:

PLD(    mov     r3, lr, pull #\pull     )
PLD(    ldr     lr, [r1], #4            )
PLD(    subs    ip, ip, #4              )
PLD(    orr     r3, r3, lr, push #\push )
PLD(    str     r3, [r0], #4            )
PLD(    bgt     9b                      )

10:

PLD(    pld     [r1, #128]              )

11:

        mov     r3, lr, pull #\pull
        ldmia   r1!, {r4 - r9, ip, lr}
        subs    r2, r2, #32
        orr     r3, r3, r4, push #\push
        mov     r4, r4, pull #\pull
        orr     r4, r4, r5, push #\push
        mov     r5, r5, pull #\pull
        orr     r5, r5, r6, push #\push
        mov     r6, r6, pull #\pull
        orr     r6, r6, r7, push #\push
        mov     r7, r7, pull #\pull
        orr     r7, r7, r8, push #\push
        mov     r8, r8, pull #\pull
        orr     r8, r8, r9, push #\push
        mov     r9, r9, pull #\pull
        orr     r9, r9, ip, push #\push
        mov     ip, ip, pull #\pull
        orr     ip, ip, lr, push #\push
        stmia   r0!, {r3 - r9, ip}
        bge     10b
PLD(    cmn     r2, #97                 )
PLD(    bge     11b                     )
PLD(    add     r2, r2, #97             )
        cmn     r2, #16
        blt     13f
        
12:     
        
        mov     r3, lr, pull #\pull
        ldmia   r1!, {r4 - r6, lr}
        sub     r2, r2, #16
        orr     r3, r3, r4, push #\push
        mov     r4, r4, pull #\pull
        orr     r4, r4, r5, push #\push
        mov     r5, r5, pull #\pull
        orr     r5, r5, r6, push #\push
        mov     r6, r6, pull #\pull
        orr     r6, r6, lr, push #\push
        stmia   r0!, {r3 - r6}
        
13:     
        
        adds    r2, r2, #28
        blt     15f
        
14:     
        
        mov     r3, lr, pull #\pull
        ldr     lr, [r1], #4
        subs    r2, r2, #4
        orr     r3, r3, lr, push #\push
        str     r3, [r0], #4
        bge     14b

15:

        .endm

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ bcs (backward copy shift)
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        
        .macro  bcs push pull

        cmp     r2, #12
PLD(    pld     [r1, #-4]               )
        blt     32f
        subs    r2, r2, #28
        blt     30f

PLD(    subs    r2, r2, #96             )
PLD(    pld     [r1, #-32]              )
PLD(    blt     29f                     )
PLD(    pld     [r1, #-64]              )

        @ cache alignment

PLD(    ands    ip, r1, #31             )
PLD(    pld     [r1, #-96]              )
PLD(    beq     28f                     )
PLD(    cmp     r2, ip                  )
PLD(    pld     [r1, #-128]             )
PLD(    blt     28f                     )
PLD(    sub     r2, r2, ip              )

27:

PLD(    mov     r4, r3, push #\push     )
PLD(    ldr     r3, [r1, #-4]!          )
PLD(    subs    ip, ip, #4              )
PLD(    orr     r4, r4, r3, pull #\pull )
PLD(    str     r4, [r0, #-4]!          )
PLD(    bgt     27b                     )

28:
        
PLD(    pld     [r1, #-128]             )

29:
        
        mov     lr, r3, push #\push
        ldmdb   r1!, {r3 - r9, ip}
        subs    r2, r2, #32
        orr     lr, lr, ip, pull #\pull
        mov     ip, ip, push #\push
        orr     ip, ip, r9, pull #\pull
        mov     r9, r9, push #\push
        orr     r9, r9, r8, pull #\pull
        mov     r8, r8, push #\push
        orr     r8, r8, r7, pull #\pull
        mov     r7, r7, push #\push
        orr     r7, r7, r6, pull #\pull
        mov     r6, r6, push #\push
        orr     r6, r6, r5, pull #\pull
        mov     r5, r5, push #\push
        orr     r5, r5, r4, pull #\pull
        mov     r4, r4, push #\push
        orr     r4, r4, r3, pull #\pull
        stmdb   r0!, {r4 - r9, ip, lr}
        bge     28b
PLD(    cmn     r2, #96                 )
PLD(    bge     29b                     )
PLD(    add     r2, r2, #96             )
        cmn     r2, #16
        blt     31f

30:
        
        mov     r7, r3, push #\push
        ldmdb   r1!, {r3 - r6}
        sub     r2, r2, #16
        orr     r7, r7, r6, pull #\pull
        mov     r6, r6, push #\push
        orr     r6, r6, r5, pull #\pull
        mov     r5, r5, push #\push
        orr     r5, r5, r4, pull #\pull
        mov     r4, r4, push #\push
        orr     r4, r4, r3, pull #\pull
        stmdb   r0!, {r4 - r7}

31:
        
        adds    r2, r2, #28
        blt     33f

32:

        mov     r4, r3, push #\push
        ldr     r3, [r1, #-4]!
        subs    r2, r2, #4
        orr     r4, r4, r3, pull #\pull
        str     r4, [r0, #-4]!
        bge     32b

33:

        .endm
        
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ memcpy
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        .global memcpy

memcpy:

        stmdb   sp!,{r0-r9,ip,lr}
        subs    ip, r0, r1
        cmphi   r2, ip
        bhi     18f
        subs    r2, r2, #4
        blt     6f
PLD(    pld     [r1, #0]                )
        ands    ip, r0, #3
        bne     7f
        ands    ip, r1, #3
        bne     8f

1:

        subs    r2, r2, #8
        blt     5f
        subs    r2, r2, #20
        blt     4f

PLD(    subs    r2, r2, #65             )
PLD(    blt     3f                      )
PLD(    pld     [r1, #32]               )

        @ cache alignment
PLD(    ands    ip, r1, #31             )
PLD(    pld     [r1, #64]               )
PLD(    beq     2f                      )
PLD(    rsb     ip, ip, #32             )
PLD(    cmp     r2, ip                  )
PLD(    pld     [r1, #96]               )
PLD(    blt     2f                      )
PLD(    cmp     ip, #16                 )
PLD(    sub     r2, r2, ip              )
PLD(    ldmgeia r1!, {r3 - r6}          )
PLD(    stmgeia r0!, {r3 - r6}          )
PLD(    beq     2f                      )
PLD(    and     ip, ip, #15             )
PLD(    cmp     ip, #8                  )
PLD(    ldr     r3, [r1], #4            )
PLD(    ldrge   r4, [r1], #4            )
PLD(    ldrgt   r5, [r1], #4            )
PLD(    str     r3, [r0], #4            )
PLD(    strge   r4, [r0], #4            )
PLD(    strgt   r5, [r0], #4            )

2:

PLD(    pld     [r1, #96]               )
        
3:

        ldmia   r1!, {r3 - r9, ip}
        subs    r2, r2, #32
        stmia   r0!, {r3 - r9, ip}
        bge     2b
PLD(    cmn     r2, #65                 )
PLD(    bge     3b                      )
PLD(    add     r2, r2, #65             )
        
4:

        cmn     r2, #16
        ldmgeia r1!, {r3 - r6}
        subge   r2, r2, #16
        stmgeia r0!, {r3 - r6}
        adds    r2, r2, #20
        ldmgeia r1!, {r3 - r5}
        subge   r2, r2, #12
        stmgeia r0!, {r3 - r5}
5:

        adds    r2, r2, #8
        blt     6f
        subs    r2, r2, #4
        ldrlt   r3, [r1], #4
        ldmgeia r1!, {r4, r5}
        subge   r2, r2, #4
        strlt   r3, [r0], #4
        stmgeia r0!, {r4, r5}

6:

        adds    r2, r2, #4
        ldmeqia sp!,{r0-r9,ip,pc}
        cmp     r2, #2
        ldrb    r3, [r1], #1
        ldrgeb  r4, [r1], #1
        ldrgtb  r5, [r1], #1
        strb    r3, [r0], #1
        strgeb  r4, [r0], #1
        strgtb  r5, [r0], #1
        ldmia   sp!,{r0-r9,ip,pc}

7:

        rsb     ip, ip, #4
        cmp     ip, #2
        ldrb    r3, [r1], #1
        ldrgeb  r4, [r1], #1
        ldrgtb  r5, [r1], #1
        strb    r3, [r0], #1
        strgeb  r4, [r0], #1
        strgtb  r5, [r0], #1
        subs    r2, r2, ip
        blt     6b
        ands    ip, r1, #3
        beq     1b

8:

        bic     r1, r1, #3
        cmp     ip, #2
        ldr     lr, [r1], #4
        bgt     17f
        beq     16f

        fcs     pull=8  push=24
        sub     r1, r1, #3
        b       6b

16:
        
        fcs     pull=16 push=16
        sub     r1, r1, #2
        b       6b

17:
        
        fcs     pull=24 push=8
        sub     r1, r1, #1
        b       6b


18:     
        
        add r1, r1, r2
        add r0, r0, r2
        subs    r2, r2, #4
        blt 24f
PLD(    pld [r1, #-4]       )
        ands    ip, r0, #3
        bne 25f
        ands    ip, r1, #3
        bne 26f

19:

        subs    r2, r2, #8
        blt 23f
        subs    r2, r2, #20
        blt 22f

PLD(    subs    r2, r2, #96             )
PLD(    pld     [r1, #-32]              )
PLD(    blt     21f                     )

        @ cache alignment

PLD(    ands    ip, r1, #31             )
PLD(    pld     [r1, #-64]              )
PLD(    beq     20f                     )
PLD(    cmp     r2, ip                  )
PLD(    pld     [r1, #-96]              )
PLD(    blt     20f                     )
PLD(    cmp     ip, #16                 )
PLD(    sub     r2, r2, ip              )
PLD(    ldmgedb r1!, {r3 - r6}          )
PLD(    stmgedb r0!, {r3 - r6}          )
PLD(    beq     20f                     )
PLD(    and     ip, ip, #15             )
PLD(    cmp     ip, #8                  )
PLD(    ldr     r3, [r1, #-4]!          )
PLD(    ldrge   r4, [r1, #-4]!          )
PLD(    ldrgt   r5, [r1, #-4]!          )
PLD(    str     r3, [r0, #-4]!          )
PLD(    strge   r4, [r0, #-4]!          )
PLD(    strgt   r5, [r0, #-4]!          )

20:
        
PLD(    pld [r1, #-96]                  )
PLD(    pld [r1, #-128]                 )

21:
        
        ldmdb   r1!, {r3 - r6}
        subs    r2, r2, #32
        stmdb   r0!, {r3 - r6}
        ldmdb   r1!, {r3 - r6}
        stmgedb r0!, {r3 - r6}
        ldmgedb r1!, {r3 - r6}
        stmgedb r0!, {r3 - r6}
        ldmgedb r1!, {r3 - r6}
        subges  r2, r2, #32
        stmdb   r0!, {r3 - r6}
        bge     20b
PLD(    cmn     r2, #96                 )
PLD(    bge     21b                     )
PLD(    add     r2, r2, #96             )
        
22:     
        
        cmn     r2, #16
        ldmgedb r1!, {r3 - r6}
        subge   r2, r2, #16
        stmgedb r0!, {r3 - r6}
        adds    r2, r2, #20
        ldmgedb r1!, {r3 - r5}
        subge   r2, r2, #12
        stmgedb r0!, {r3 - r5}
        
23:     
        
        adds    r2, r2, #8
        blt     24f
        subs    r2, r2, #4
        ldrlt   r3, [r1, #-4]!
        ldmgedb r1!, {r4, r5}
        subge   r2, r2, #4
        strlt   r3, [r0, #-4]!
        stmgedb r0!, {r4, r5}

24:     
        
        adds    r2, r2, #4
        ldmeqia sp!,{r0-r9,ip,pc}
        cmp     r2, #2
        ldrb    r3, [r1, #-1]!
        ldrgeb  r4, [r1, #-1]!
        ldrgtb  r5, [r1, #-1]!
        strb    r3, [r0, #-1]!
        strgeb  r4, [r0, #-1]!
        strgtb  r5, [r0, #-1]!
        ldmia   sp!,{r0-r9,ip,pc}

25:     
        
        cmp     ip, #2
        ldrb    r3, [r1, #-1]!
        ldrgeb  r4, [r1, #-1]!
        ldrgtb  r5, [r1, #-1]!
        strb    r3, [r0, #-1]!
        strgeb  r4, [r0, #-1]!
        strgtb  r5, [r0, #-1]!
        subs    r2, r2, ip
        blt     24b
        ands    ip, r1, #3
        beq     19b

26:     
        
        bic     r1, r1, #3
        cmp     ip, #2
        ldr     r3, [r1], #0
        blt     35f
        beq     34f
        bcs     push=8  pull=24
        add     r1, r1, #3
        b       24b

34:     
        
        bcs     push=16 pull=16
        add     r1, r1, #2
        b       24b

35:     
        
        bcs     push=24 pull=8
        add     r1, r1, #1
        b       24b
#endif

#endif
