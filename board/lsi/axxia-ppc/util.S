
	#; ------------------------------------------------------------
	#; ------------------------------------------------------------
	#;
	#; (C) Copyright 2009 LSI Corporation
	#;
	#; This program is free software; you can redistribute it
	#; and/or modify it under the terms of the GNU General Public
	#; License as published by the Free Software Foundation; either
	#; version 2 of the License, or (at your option) any later
	#; version.
	#;
	#; This program is distributed in the hope that it will be
	#; useful, but WITHOUT ANY WARRANTY; without even the implied
	#; warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
	#; PURPOSE.  See the GNU General Public License for more
	#; details.
	#;
	#; You should have received a copy of the GNU General Public
	#; License along with this program; if not, write to the Free
	#; Software Foundation, Inc., 59 Temple Place, Suite 330,
	#; Boston, MA 02111-1307 USA
	#;
	#; ------------------------------------------------------------
	#; ------------------------------------------------------------

#include <config.h>
#include <ppc4xx.h>
#include <ppc_asm.tmpl>
#include <ppc_defs.h>

	.global mmfail

mmfail:

	b	mmfail

	.global	mmtest

mmtest:

	subi	r1,r1,132
	stw	r0,4(r1)
	mflr	r0
	stw	r0,8(r1)
	mtlr	r1
	stmw	r2,12(r1)
	ori	r6,r4,0
	ori	r16,r3,0
	ori	r17,r3,0
	ori	r18,r3,0
	ori	r19,r3,0
	ori	r20,r3,0
	ori	r21,r3,0
	ori	r22,r3,0
	ori	r23,r3,0
	ori	r24,r3,0
	ori	r25,r3,0
	ori	r26,r3,0
	ori	r27,r3,0
	ori	r28,r3,0
	ori	r29,r3,0
	ori	r30,r3,0
	ori	r31,r3,0

mmtest_fill_loop:

	stmw	r16,0(r4)
	addi	r4,r4,64
	cmpw	r4,r5
	blt	mmtest_fill_loop

	ori	r4,r6,0

mmtest_verify_loop:

	lmw	r16,0(r4)
	cmpw	r16,r3
	bne	mmfail
	cmpw	r17,r3
	bne	mmfail
	cmpw	r18,r3
	bne	mmfail
	cmpw	r19,r3
	bne	mmfail
	cmpw	r20,r3
	bne	mmfail
	cmpw	r21,r3
	bne	mmfail
	cmpw	r22,r3
	bne	mmfail
	cmpw	r23,r3
	bne	mmfail
	cmpw	r24,r3
	bne	mmfail
	cmpw	r25,r3
	bne	mmfail
	cmpw	r26,r3
	bne	mmfail
	cmpw	r27,r3
	bne	mmfail
	cmpw	r28,r3
	bne	mmfail
	cmpw	r29,r3
	bne	mmfail
	cmpw	r30,r3
	bne	mmfail
	cmpw	r31,r3
	bne	mmfail
	addi	r4,r4,64
	cmpw	r4,r5
	blt	mmtest_verify_loop

mmtest_done:
	mflr	r1
	lwz	r0,8(r1)
	mtlr	r0
	lwz	r0,4(r1)
	lmw	r2,12(r1)
	addi	r1,r1,132
	blr

###
### Local Variables:
### asm-comment-char: ?\#
### End:
###
