	#; ------------------------------------------------------------
	#; ------------------------------------------------------------
	#;
	#; (C) Copyright 2008 LSI Corporation
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
#include <asm/ppc4xx.h>
#include <version.h>
#include <ppc_asm.tmpl>
#include <ppc_defs.h>

#undef CLEAR_UTLB
#define CLEAR_UTLB

	.section	.text

	.global		acp_spintable_jump

acp_spintable_jump:

	mtspr		srr0,r4
	mfmsr		r6
	mtspr		srr1,r6
	li		r6,0
	rfi

	.section	.bootpg,"ax"

#ifdef CLEAR_UTLB
#ifdef CONFIG_ACP3

	#; ------------------------------------------------------------
	#; Define all the UTLB entries that need to be added.
	#; ------------------------------------------------------------

utlb_table:

	#; -- -- System Memory -- --
	#; Physical Address - 0x0000_0000_0000
	#; Virtual Address - 0x0000_0000
	#; Size - 256M (1 256M segment)
	.long		0x80000000,0x00000bf0,0x00000000,0x00030207

#ifdef ACP_ISS
	#; -- -- IO -- --
	#; Physical Address - 0x0020_0040_4000
	#; Virtual Address - 0xe000_0000
	#; Size - 4K
	.long		0x00000000,0xe0000800,0x40000001,0x00030507
#else
	#; -- -- IO -- --
	#; Physical Address - 0x0020_0040_0000
	#; Virtual Address - 0xf080_0000
	#; Size - 2M (2 1M segments)
	.long		0x80000000,0xf0800870,0x00400020,0x00030507
	.long		0x80000000,0xf0900870,0x00500020,0x00030507
#endif

	#; -- -- Local CPU memory -- --
#if ACP_25xx
	#; Physical Address - 0x0010_0002_0000
	#; Virtual Address - 0xf0a0_0000
	#; Size - 64K
	.long		0xe0000000,0xf0a00830,0x00020010,0x00030507
	#; Physical Address - 0x0010_0003_0000
	#; Virtual Address - 0xf0a1_0000
	#; Size - 64K
	.long		0xe0000000,0xf0a10830,0x00030010,0x00030507
	#; Physical Address - 0x0010_0000_0000
	#; Virtual Address - 0xf0a2_0000
	#; Size - 16K
	.long		0xe0000000,0xf0a20810,0x00000010,0x00030507
#else
	#; Physical Address - 0x0010_0000_0000
	#; Virtual Address - 0xf0a0_0000
	#; Size - 1M
	.long		0x80000000,0xf0a00870,0x00000010,0x00030507
#endif
	
	#; -- -- ROM -- -- (Note that ROM is writable on ISS)
#if ACP_25xx
	#; Physical Address - 0x002f_ffff_8000
	#; Virtual Address - 0xf0b0_0000
	#; Size - 32K (2 16K chunks)
#ifdef ISS
	.long		0x80000000,0xf0b0081000022294: 000000c7 abcd1234    .......4
,0xffff802f,0x00030507
	.long		0x80000000,0xf0b04810,0xffffc02f,0x00030507
#else
	.long		0x80000000,0xf0b00810,0xffff802f,0x00030505
	.long		0x80000000,0xf0b04810,0xffffc02f,0x00030505
#endif
#else
#ifdef ISS
	#; Physical Address - 0x002f_ffff_c000
	#; Virtual Address - 0xf0b0_0000
	#; Size - 16K
	.long		0x80000000,0xf0b00810,0xffffc02f,0x00030507
#else
	.long		0x80000000,0xf0b00810,0xffffc02f,0x00030505
#endif
#endif

utlb_table_end:

#endif
#endif

	.section	.text
	.global		_start_acp

_start_acp:

#if defined(ACP_25xx) && defined(CONFIG_ACP2)
	#; ------------------------------------------------------------
	#; In some cases, the core attempts to prefetch from system
	#; memory before it has been initialized.  To avoid this,
	#; remove the system memory TLB entry here, and re-create it
	#; just before initializing system memory.
	#; ------------------------------------------------------------

	lis		r0,0x8000
	lis		r1,0
	tlbwe		r1,r0,0
	tlbwe		r1,r0,1
	tlbwe		r1,r0,2
	isync

	#; ------------------------------------------------------------
	#; Put L2(1) to sleep.  This should have been done in the 1st
	#; stage before putting the core into WFI...
	#; ------------------------------------------------------------

#ifndef RESET_INSTEAD_OF_IPI
	li		r0,0x84
	li		r1,0x400
#if 0
	mtdcrx		r0,r1
#else
	#; mtdcrx		r0,r1
	#; Use 0x7c000306 | (0 << 21) | (1 << 16)
	#; to avoid incomaptibility with older binutils...
	.long		0x7c010306
#endif

	li		r0,0x1
	li		r1,0x404
#if 0
	mtdcrx		r0,r1
#else
	#; mtdcrx		r0,r1
	#; Use 0x7c000306 | (0 << 21) | (1 << 16)
	#; to avoid incomaptibility with older binutils...
	.long		0x7c010306
#endif
#endif
#endif

	#; Clear the MSR

	lis		r0,0
	mtmsr		r0

	#; Clear the MCSR

	mfspr		r0,0x23c
	mtspr		0x33c,r0

	#; Clear the TCR

	mtspr		0x154,r0

	#; Clear the PID

	mtspr		0x030,r0	

	#; Invalidate L1/L2

	lis		r0,0
	#; iccci		r0,r0
	.long		0x7c00078c
	#; dccci		r0,r0
	.long		0x7c00038c
	#; msync
	.long		0x7c0004ac

	#; ------------------------------------------------------------
	#; Set all exceptions to point to the handlers.
	#; ------------------------------------------------------------

	lis		r0,acp_start_of_vectors@h
	mtspr		ivpr,r0

	lis		r0,0
	ori		r0,r0,acp_critical_input@l
	mtspr		ivor0,r0

	lis		r0,0
	ori		r0,r0,acp_machine_check@l
	mtspr		ivor1,r0

	lis		r0,0
	ori		r0,r0,acp_data_storage@l
	mtspr		ivor2,r0

	lis		r0,0
	ori		r0,r0,acp_instruction_storage@l
	mtspr		ivor3,r0

	lis		r0,0
	ori		r0,r0,acp_external@l
	mtspr		ivor4,r0
	
	lis		r0,0
	ori		r0,r0,acp_alignment@l
	mtspr		ivor5,r0
	
	lis		r0,0
	ori		r0,r0,acp_program@l
	mtspr		ivor6,r0
	
	lis		r0,0
	ori		r0,r0,acp_fp_unavailable@l
	mtspr		ivor7,r0
	
	lis		r0,0
	ori		r0,r0,acp_system_call@l
	mtspr		ivor8,r0
	
	lis		r0,0
	ori		r0,r0,acp_ap_unavailable@l
	mtspr		ivor9,r0
	
	lis		r0,0
	ori		r0,r0,acp_decrementer@l
	mtspr		ivor10,r0

	lis		r0,0
	ori		r0,r0,acp_fixed_interval_timer@l
	mtspr		ivor11,r0
	
	lis		r0,0
	ori		r0,r0,acp_watchdog_timer@l
	mtspr		ivor12,r0
	
	lis		r0,0
	ori		r0,r0,acp_data_tlb_miss@l
	mtspr		ivor13,r0
	
	lis		r0,0
	ori		r0,r0,acp_instruction_tlb_miss@l
	mtspr		ivor14,r0
	
	lis		r0,0
	ori		r0,r0,acp_debug@l
	mtspr		ivor15,r0

#ifdef CONFIG_ACP3
#ifdef CLEAR_UTLB

set_up_utlb:

	#; Put the System Memory entry in r24, r25, and r26

	lis		r24,0x000009f0@h
	ori		r24,r24,0x000009f0@l
	li		r25,0
	lis		r26,0x00030207@h
	ori		r26,r26,0x00030207@l

	#; Set up the mmucr

	li		r3,0
	mtspr		0x3b2,r3

	#; Set up for searches by page size.

	lis		r3,(0xfedcba90)@h
	ori		r3,r3,(0xfecdba90)@l
	mtspr		sspcr,r3
	mtspr		uspcr,r3
	lis		r3,(0x76543210)@h
	ori		r3,r3,(0x76543210)@l
	mtspr		ispcr,r3

	#; ------------------------------------------------------------
	#; Set up the TLB as described in tlb_table above.
	#; ------------------------------------------------------------

clear_all_utlb_entries:

	#; Set initial values.

	addis		r3,0,0x8000
	addi		r4,0,0
	addi		r5,0,0
	b		clear_utlb_entry

	#; Align the loop to speed things up.

	.align		6

clear_utlb_entry:

	tlbwe		r4,r3,0
	tlbwe		r5,r3,1
	tlbwe		r5,r3,2
	addis		r3,r3,0x2000
	cmpwi		r3,0
	bne		clear_utlb_entry
	addis		r3,0,0x8000
	addis		r4,r4,0x100
	cmpwi		r4,0
	bne		clear_utlb_entry

	#; Restore original entry.

	oris		r23,r23,0x8000  /* specify the way */
	tlbwe		r24,r23,0
	tlbwe		r25,r23,1
	tlbwe		r26,r23,2
	isync
1:

	#; Put the address of the first entry of the table in r4
	#; and the last in r5.

	bl		update_tlb_setup

update_tlb_setup:

	mflr		r6
	lis		r7,(update_tlb_setup)@h
	ori		r7,r7,(update_tlb_setup)@l
	sub		r6,r6,r7
	lis		r4,(utlb_table-4)@h
	ori		r4,r4,(utlb_table-4)@l
	add		r4,r4,r6
	lis		r5,(utlb_table_end-4)@h
	ori		r5,r5,(utlb_table_end-4)@l
	add		r5,r5,r6

update_tlb:

	lwzu		r6,4(r4)
	lwzu		r7,4(r4)
	tlbwe		r7,r6,0
	lwzu		r7,4(r4)
	tlbwe		r7,r6,1
	lwzu		r7,4(r4)
	tlbwe		r7,r6,2
	cmpw		r4,r5
	bne		update_tlb

	#; g. Perform a context synchronization to invalidate the shadow
	#;    TLB contents and to cause the new TLB contents to take effect.

	#; The first time source level debugging will be readily available
	#; is at the statement after "acp_relocate".

	lis		r3,(acp_relocate)@h
	ori		r3,r3,(acp_relocate)@l
	mtspr		srr0,r3
	mfmsr		r3
	mtspr		srr1,r3
	rfi

acp_relocate:

#endif

	#; Which core?

	mfspr		r22,0x11e

	#; 

	lis		r23,(0xa0000000)@h
	ori		r23,r23,(0xa0000000)@l
	lis		r24,0
	lis		r25,0
	lis		r26,0
	tlbwe		r24,r23,0
	tlbwe		r25,r23,1
	tlbwe		r26,r23,2
	lis		r23,(0xc0000000)@h
	ori		r23,r23,(0xc0000000)@l
	lis		r24,0
	lis		r25,0
	lis		r26,0
	tlbwe		r24,r23,0
	tlbwe		r25,r23,1
	tlbwe		r26,r23,2
	lis		r23,(0xe0000000)@h
	ori		r23,r23,(0xe0000000)@l
	lis		r24,0
	lis		r25,0
	lis		r26,0
	tlbwe		r24,r23,0
	tlbwe		r25,r23,1
	tlbwe		r26,r23,2

	#; If not core 0, skip the next bit...

	cmpwi		r22,SYSTEM_BOOTCORE
	bne		continue_start

	#; Determine whether this is a cold or warm reset.

#if defined(ACP_25xx) && !defined(ACP_EMU)
	#; 2500 Case
	lis		r23,(DCR_RESET_BASE + 0xe)@h
	ori		r23,r23,(DCR_RESET_BASE + 0xe)@l
#if 0
	mfdcrx		r21,r23
#else
	#; mfdcrx		r21,r23
	#; Use 0x7c000206 | (0x15 << 21) | (0x17 << 16)
	#; to avoid incomaptibility with older binutils...
	.long		0x7eb70206
#endif
	andi.		r21,r21,0xf
	ori		r22,r21,0
	lis		r23,(DCR_RESET_BASE + 0x8)@h
	ori		r23,r23,(DCR_RESET_BASE + 0x8)@l
#if 0
	mfdcrx		r21,r23
#else
	#; mfdcrx		r21,r23
	#; Use 0x7c000206 | (0x15 << 21) | (0x17 << 16)
	#; to avoid incomaptibility with older binutils...
	.long		0x7eb70206
#endif
	andi.		r21,r21,0x3
	or		r22,r22,r21
	lis		r23,(DCR_RESET_BASE + 0x6)@h
	ori		r23,r23,(DCR_RESET_BASE + 0x6)@l
#if 0
	mfdcrx		r21,r23
#else
	#; mfdcrx		r21,r23
	#; Use 0x7c000206 | (0x15 << 21) | (0x17 << 16)
	#; to avoid incomaptibility with older binutils...
	.long		0x7eb70206
#endif
	andi.		r21,r21,0x3
	or		r22,r22,r21
	cmpwi		r22,0
	beq		warm_start
#else
	#; Non-2500 Case
	lis		r23,(DCR_RESET_BASE + 1)@h
	ori		r23,r23,(DCR_RESET_BASE + 1)@l
#if 0
	mfdcrx		r21,r23
#else
	#; mfdcrx		r21,r23
	#; Use 0x7c000206 | (0x15 << 21) | (0x17 << 16)
	#; to avoid incomaptibility with older binutils...
	.long		0x7eb70206
#endif
	lis		r23,(0x00ffe000)@h
	ori		r23,r23,(0x00ffe000)@l
	and		r21,r21,r23
	cmpwi		r21,0
	beq		warm_start
#endif

cold_start:

	#; Cold start, core 0 makes a copy of the data segment for each core.

	lis		r3,_core_copy_core0@h
	ori		r3,r3,_core_copy_core0@l
	lis		r4,_core_copy_beginning@h
	ori		r4,r4,_core_copy_beginning@l
	mr		r5,r4
	lis		r6,_core_copy_end@h
	ori		r6,r6,_core_copy_end@l
	subf		r5,r5,r6
	bl		memcpy

	lis		r3,_core_copy_core1@h
	ori		r3,r3,_core_copy_core1@l
	lis		r4,_core_copy_beginning@h
	ori		r4,r4,_core_copy_beginning@l
	mr		r5,r4
	lis		r6,_core_copy_end@h
	ori		r6,r6,_core_copy_end@l
	subf		r5,r5,r6
	bl		memcpy

	lis		r3,_core_copy_core2@h
	ori		r3,r3,_core_copy_core2@l
	lis		r4,_core_copy_beginning@h
	ori		r4,r4,_core_copy_beginning@l
	mr		r5,r4
	lis		r6,_core_copy_end@h
	ori		r6,r6,_core_copy_end@l
	subf		r5,r5,r6
	bl		memcpy

	lis		r3,_core_copy_core3@h
	ori		r3,r3,_core_copy_core3@l
	lis		r4,_core_copy_beginning@h
	ori		r4,r4,_core_copy_beginning@l
	mr		r5,r4
	lis		r6,_core_copy_end@h
	ori		r6,r6,_core_copy_end@l
	subf		r5,r5,r6
	bl		memcpy

	b		continue_start

warm_start:

continue_start:

#endif

	#; ------------------------------------------------------------
	#; Update CCRn Settings
	#;
	#; At this point, the required CCRn settings are still
	#; changing.  Since the BootROM (1st stage) code has
	#; already been finalized, change to the final settings
	#; here.  Note that a context switch is required after
	#; changing the settings.
	#; ------------------------------------------------------------

	lis		r0,(CCR0_DEFAULT)@h
	ori		r0,r0,(CCR0_DEFAULT)@l
	mtspr		ccr0,r0

	lis		r0,(CCR1_DEFAULT)@h
	ori		r0,r0,(CCR1_DEFAULT)@l
	mtspr		ccr1,r0

	lis		r0,(CCR2_DEFAULT)@h
	ori		r0,r0,(CCR2_DEFAULT)@h
	mtspr		ccr2,r0

	isync

	#; ------------------------------------------------------------
	#; Write all GPRs and SPRGs
	#; ------------------------------------------------------------

	lis		r0,(0)@h
	ori		r0,r0,(0)@l
	mr		r1,r0
	mr		r2,r0
	mr		r3,r0
	mr		r4,r0
	mr		r5,r0
	mr		r6,r0
	mr		r7,r0
	mr		r8,r0
	mr		r9,r0
	mr		r10,r0
	mr		r11,r0
	mr		r12,r0
	mr		r13,r0
	mr		r14,r0
	mr		r15,r0
	mr		r16,r0
	mr		r17,r0
	mr		r18,r0
	mr		r19,r0
	mr		r20,r0
	mr		r21,r0
	mr		r22,r0
	mr		r23,r0
	mr		r24,r0
	mr		r25,r0
	mr		r26,r0
	mr		r27,r0
	mr		r28,r0
	mr		r29,r0
	mr		r30,r0
	mr		r31,r0
	mtspr		sprg0,r0
	mtspr		sprg1,r0
	mtspr		sprg2,r0
	mtspr		sprg3,r0
	mtspr		sprg4,r0
	mtspr		sprg5,r0
	mtspr		sprg6,r0
	mtspr		sprg7,r0
	mtspr		sprg8,r0

#ifndef ACP_X1V1

	#; ------------------------------------------------------------
	#; Write all FPRs
	#; ------------------------------------------------------------

	mfspr		r0,ccr1
	mr		r1,r0
	ori		r1,r1,0x400
	mtspr		ccr1,r1
	isync

	lis		r1,(clear_all_fp_regs)@h
	ori		r1,r1,(clear_all_fp_regs)@l
	mtspr		srr0,r1
	mfmsr		r1
	mr		r2,r1
	ori		r2,r2,0x2000
	mtspr		srr1,r2
	rfi

clear_all_fp_regs:

	fadd		0,0,0
	fadd		1,1,1
	fadd		2,2,2
	fadd		3,3,3
	fadd		4,4,4
	fadd		5,5,5
	fadd		6,6,6
	fadd		7,7,7
	fadd		8,8,8
	fadd		9,9,9
	fadd		10,10,10
	fadd		11,11,11
	fadd		12,12,12
	fadd		13,13,13
	fadd		14,14,14
	fadd		15,15,15
	fadd		16,16,16
	fadd		17,17,17
	fadd		18,18,18
	fadd		19,19,19
	fadd		20,20,20
	fadd		21,21,21
	fadd		22,22,22
	fadd		23,23,23
	fadd		24,24,24
	fadd		25,25,25
	fadd		26,26,26
	fadd		27,27,27
	fadd		28,28,28
	fadd		29,29,29
	fadd		30,30,30
	fadd		31,31,31

	lis		r2,(clear_all_fp_done)@h
	ori		r2,r2,(clear_all_fp_done)@l
	mtspr		srr0,r2
	mtspr		srr1,r1
	rfi

clear_all_fp_done:

	mtspr		ccr1, r0
	isync

#ifdef ACP3
acp_icache_init:

	#; Create a 64K page at virtual=0x40000000/physical=0x003f0000
	lis		r14,(0x80000000)@h
	ori		r14,r14,(0x80000000)@l
	lis		r15,(0x40000830)@h
	ori		r15,r15,(0x40000830)@l
	lis		r16,(0x003f0000)@h
	ori		r16,r16,(0x003f0000)@l
	lis		r17,(0x0000003f)@h
	ori		r17,r17,(0x0000003f)@l
	tlbwe		r15,r14,0
	tlbwe		r16,r14,1
	tlbwe		r17,r14,2
	isync

	lis		r3,(0x40000000)@h
	ori		r3,r3,(0x40000000)@l
	mtlr		r3
	addi		r4, 0, 1023
	mtctr		r4

	#; "b . + 32" instruction
	addis		r4, 0, 0x4800 
	ori		r4, r4,	0x0020

	addi		r3, r3, -32
1:
	stwu		r4, 32(r3)
	bdnz		1b

	#; "blr" instruction
	addis		r4, 0, 0x4E80 
	ori		r4, r4,	0x0020
	stwu		r4, 32(r3)

	#; Branch "b . +32" code
	blrl

	#; Take down the 64K page.
	lis		r14,(0x80000000)@h
	ori		r14,r14,(0x80000000)@l
	lis		r15,(0x40000000)@h
	ori		r15,r15,(0x40000000)@l
	lis		r16,(0x00000000)@h
	ori		r16,r16,(0x00000000)@l
	lis		r17,(0x00000000)@h
	ori		r17,r17,(0x00000000)@l
	tlbwe		r15,r14,0
	tlbwe		r16,r14,1
	tlbwe		r17,r14,2
	isync

	#; Invalidate the cache.
	lis		r14,0
	iccci		r14,r14
#endif
#endif

	#; ------------------------------------------------------------
	#; Set up the inital stack.
	#; ------------------------------------------------------------

#ifdef CONFIG_ACP2

#ifdef ACP_25xx

	lis		r4,CFG_INIT_RAM_ADDR@h
	ori		r4,r4,CFG_INIT_RAM_ADDR@l
	subi		r3,r4,0x4004
	lis		r5,0
1:	stwu		r5,4(r3)
	bne		1b

#endif

	lis		r1,CFG_INIT_RAM_ADDR@h
	ori		r1,r1,CFG_INIT_RAM_ADDR@l

#else
	
	mfspr		r0,0x11e
	cmpwi		r0,0
	beq		sis_core0
	cmpwi		r0,1
	beq		sis_core1
	cmpwi		r0,2
	beq		sis_core2
	b		sis_core3

sis_core0:

	lis		r1,CFG_INIT_RAM_ADDR0@h
	ori		r1,r1,CFG_INIT_RAM_ADDR0@l
	b		stackstuff

sis_core1:

	lis		r1,CFG_INIT_RAM_ADDR1@h
	ori		r1,r1,CFG_INIT_RAM_ADDR1@l
	b		stackstuff


sis_core2:

	lis		r1,CFG_INIT_RAM_ADDR2@h
	ori		r1,r1,CFG_INIT_RAM_ADDR2@l
	b		stackstuff


sis_core3:

	lis		r1,CFG_INIT_RAM_ADDR3@h
	ori		r1,r1,CFG_INIT_RAM_ADDR3@l
	b		stackstuff


stackstuff:

#endif

	li		r0,0

	#; Terminate call chain.

	stwu		r0,-4(r1)
	stwu		r0,-4(r1)

	#; Save back chain and move stack pointer.

	stwu		r1,-8(r1)

	#; Address of the reset vector.

	lis		r0,RESET_VECTOR@h
	ori		r0,r0,RESET_VECTOR@l

	#; Save back chain and move stack pointer.

	stwu		r1,-8(r1)

	#; Save return address (underflow vector).

	stw		r0,+12(r1)

#if !defined(ACP_ISS)

	#; ------------------------------------------------------------
	#; Enable cache (L1 and L2) for LCM (stage 2) or
	#; system memory (stage 3).
	#; ------------------------------------------------------------

#ifdef CONFIG_ACP2
#ifdef ACP_25xx
	#; Physical Address - 0x0010_0002_0000
	#; Virtual Address - 0xf0a0_0000
	#; Size - 64K
	lis		r0,(0xe0000000)@h
	ori		r0,r0,(0xe0000000)@l
	lis		r2,(0xf0a00830)@h
	ori		r2,r2,(0xf0a00830)@l
	tlbwe		r2,r0,0
	lis		r2,(0x00020010)@h
	ori		r2,r2,(0x00020010)@l
	tlbwe		r2,r0,1
	lis		r2,(ACP_CACHE_TLB)@h
	ori		r2,r2,(ACP_CACHE_TLB)@l
	tlbwe		r2,r0,2
	#; Physical Address - 0x0010_0003_0000
	#; Virtual Address - 0xf0a1_0000
	#; Size - 64K
	lis		r0,(0xe0000000)@h
	ori		r0,r0,(0xe0000000)@l
	lis		r2,(0xf0a10830)@h
	ori		r2,r2,(0xf0a10830)@l
	tlbwe		r2,r0,0
	lis		r2,(0x00030010)@h
	ori		r2,r2,(0x00030010)@l
	tlbwe		r2,r0,1
	lis		r2,(ACP_CACHE_TLB)@h
	ori		r2,r2,(ACP_CACHE_TLB)@l
	tlbwe		r2,r0,2
	#; Physical Address - 0x0010_0000_0000
	#; Virtual Address - 0xf0a2_0000
	#; Size - 16K
	lis		r0,(0xe0000000)@h
	ori		r0,r0,(0xe0000000)@l
	lis		r2,(0xf0a20810)@h
	ori		r2,r2,(0xf0a20810)@l
	tlbwe		r2,r0,0
	lis		r2,(0x00000010)@h
	ori		r2,r2,(0x00000010)@l
	tlbwe		r2,r0,1
	lis		r2,(ACP_CACHE_TLB)@h
	ori		r2,r2,(ACP_CACHE_TLB)@l
	tlbwe		r2,r0,2
#else
	#; Physical Address - 0x0010_0000_0000
	#; Virtual Address - 0xf0a0_0000
	#; Size - 1M
	lis		r0,(0x80000000)@h
	ori		r0,r0,(0x80000000)@l
	lis		r2,(0xf0a00870)@h
	ori		r2,r2,(0xf0a00870)@l
	tlbwe		r2,r0,0
	lis		r2,(0x00000010)@h
	ori		r2,r2,(0x00000010)@l
	tlbwe		r2,r0,1
	lis		r2,(ACP_CACHE_TLB)@h
	ori		r2,r2,(ACP_CACHE_TLB)@l
	tlbwe		r2,r0,2
#endif
#else
	lis		r0,(0x80000000)@h
	ori		r0,r0,(0x80000000)@l
	lis		r2,(0x000009f0)@h
	ori		r2,r2,(0x000009f0)@l
	tlbwe		r2,r0,0
	lis		r2,(0x00000000)@h
	ori		r2,r2,(0x00000000)@l
	tlbwe		r2,r0,1
	lis		r2,(ACP_CACHE_TLB)@h
	ori		r2,r2,(ACP_CACHE_TLB)@l
	tlbwe		r2,r0,2
#endif
	isync

#endif

	#; ------------------------------------------------------------
	#; Initial setup.
	#; ------------------------------------------------------------

	bl		acp_init_f

	#; ------------------------------------------------------------
	#; Since the above call should never return, getting here at
	#; all is a fatal error...
	#; ------------------------------------------------------------

acp_start_failure:

	b		acp_start_failure

	#; ------------------------------------------------------------
	#;
	#; acp_mem_init
	#;
	#; r3 - Base Address of Stack in System Memory
	#; r4 -
	#; r5 - Address of final ACP initialization function
	#; ------------------------------------------------------------

	.global		acp_mem_init

acp_mem_init:

	#; ------------------------------------------------------------
	#; Set up the stack
	#; ------------------------------------------------------------

	mr		r1,r3
	li		r0,0

	#; Terminate call chain.

	stwu		r0,-4(r1)
	stwu		r0,-4(r1)

	#; Save back chain and move stack pointer.

	stwu		r1,-8(r1)

	#; Address of the reset vector.

	lis		r0,RESET_VECTOR@h
	ori		r0,r0,RESET_VECTOR@l

	#; Save back chain and move stack pointer.

	stwu		r1,-8(r1)

	#; Save return address (underflow vector).

	stw		r0,+12(r1)

	#; ------------------------------------------------------------
	#; Jump to the final initialization function
	#; ------------------------------------------------------------

	bl		acp_init_r

	#; ------------------------------------------------------------
	#; Exception Handlers
	#; ------------------------------------------------------------

#define ACP_UNHANDLED_EXCEPTION(name, number)          \
	.global		acp_##name;            \
	.align		4;                     \
acp_##name:;                                   \
	mtspr		sprg3,r3;              \
	li		r3,number;             \
	mtspr		sprg4,r4;              \
	mflr		r4;                    \
	bl		acp_failure_exception

	.section	.text
	.global		acp_start_of_vectors
	.align		4

acp_start_of_vectors:

	#; ------------------------------------------------------------
	#; Critical Input
	#; ------------------------------------------------------------

	ACP_UNHANDLED_EXCEPTION(critical_input, 0)

	#; ------------------------------------------------------------
	#; Machine Check
	#; ------------------------------------------------------------

	.global		acp_machine_check
	.align		4
acp_machine_check:
	mtspr		sprg3,r3
	mflr		r3
	bl		acp_failure_machine_check

	#; ------------------------------------------------------------
	#; Data Storage
	#; ------------------------------------------------------------

	ACP_UNHANDLED_EXCEPTION(data_storage, 2)

	#; ------------------------------------------------------------
	#; Instruction Storage
	#; ------------------------------------------------------------

	ACP_UNHANDLED_EXCEPTION(instruction_storage, 3)

	#; ------------------------------------------------------------
	#; External
	#; ------------------------------------------------------------

	ACP_UNHANDLED_EXCEPTION(external, 4)

	#; ------------------------------------------------------------
	#; Alignment
	#; ------------------------------------------------------------

	ACP_UNHANDLED_EXCEPTION(alignment, 5)

	#; ------------------------------------------------------------
	#; Program
	#; ------------------------------------------------------------

	ACP_UNHANDLED_EXCEPTION(program, 6)

	#; ------------------------------------------------------------
	#; FP Unavailable
	#; ------------------------------------------------------------

	ACP_UNHANDLED_EXCEPTION(fp_unavailable, 7)

	#; ------------------------------------------------------------
	#; System Call
	#; ------------------------------------------------------------

	ACP_UNHANDLED_EXCEPTION(system_call, 8)

	#; ------------------------------------------------------------
	#; AP Unavailable
	#; ------------------------------------------------------------

	ACP_UNHANDLED_EXCEPTION(ap_unavailable, 9)

	#; ------------------------------------------------------------
	#; Decrementer
	#; ------------------------------------------------------------

	.global		acp_decementer
	.align		4
acp_decrementer:
	#; Use sprg0 and sprg1 to get some usable GPRs.
	mtspr	sprg0,r20
	mtspr	sprg1,r21
	mfcr	r20
	subi	r21,r1,256
	#; Save SPRs
	stw	r20,_CCR(r21)
	mflr	r20
	stw	r20,_LINK(r21)
	mfctr	r20
	stw	r20,_CTR(r21)
	#; Save GPRs
	stw	r0,GPR0(r21)
	stw	r1,GPR1(r21)
	stw	r2,GPR2(r21)
	stw	r3,GPR3(r21)
	stw	r4,GPR4(r21)
	stw	r5,GPR5(r21)
	stw	r6,GPR6(r21)
	stw	r7,GPR7(r21)
	stw	r8,GPR8(r21)
	stw	r9,GPR9(r21)
	stw	r10,GPR10(r21)
	stw	r11,GPR11(r21)
	stw	r12,GPR12(r21)
	stw	r13,GPR13(r21)
	stw	r14,GPR14(r21)
	stw	r15,GPR15(r21)
	stw	r16,GPR16(r21)
	stw	r17,GPR17(r21)
	stw	r18,GPR18(r21)
	stw	r19,GPR19(r21)
	stw	r22,GPR22(r21)
	stw	r23,GPR23(r21)
	stw	r24,GPR24(r21)
	stw	r25,GPR25(r21)
	stw	r26,GPR26(r21)
	stw	r27,GPR27(r21)
	stw	r28,GPR28(r21)
	stw	r29,GPR29(r21)
	stw	r30,GPR30(r21)
	stw	r31,GPR31(r21)
	#; Call the handler
	mr	r1,r21
	lis	r20,timer_interrupt@h
	ori	r20,r20,timer_interrupt@l
	mtlr	r20
	blrl
	sync
	isync
	#; Restore GPRs
	lwz	r0,GPR0(r21)
	lwz	r1,GPR1(r21)
	lwz	r2,GPR2(r21)
	lwz	r3,GPR3(r21)
	lwz	r4,GPR4(r21)
	lwz	r5,GPR5(r21)
	lwz	r6,GPR6(r21)
	lwz	r7,GPR7(r21)
	lwz	r8,GPR8(r21)
	lwz	r9,GPR9(r21)
	lwz	r10,GPR10(r21)
	lwz	r11,GPR11(r21)
	lwz	r12,GPR12(r21)
	lwz	r13,GPR13(r21)
	lwz	r14,GPR14(r21)
	lwz	r15,GPR15(r21)
	lwz	r16,GPR16(r21)
	lwz	r17,GPR17(r21)
	lwz	r18,GPR18(r21)
	lwz	r19,GPR19(r21)
	lwz	r22,GPR22(r21)
	lwz	r23,GPR23(r21)
	lwz	r24,GPR24(r21)
	lwz	r25,GPR25(r21)
	lwz	r26,GPR26(r21)
	lwz	r27,GPR27(r21)
	lwz	r28,GPR28(r21)
	lwz	r29,GPR29(r21)
	lwz	r30,GPR30(r21)
	lwz	r31,GPR31(r21)
	#; Restore SPRs
	lwz	r20,_CCR(r21)
	mtcr	r20
	lwz	r20,_LINK(r21)
	mtlr	r20
	lwz	r20,_CTR(r21)
	mtctr	r20
	#; Restore r20 and r21
	mfspr	r20,sprg0
	mfspr	r21,sprg1
	#; Return
	rfi

	#; ------------------------------------------------------------
	#; Fixed Interval Timer
	#; ------------------------------------------------------------

	ACP_UNHANDLED_EXCEPTION(fixed_interval_timer, 11)

	#; ------------------------------------------------------------
	#; Watchdog Timer
	#; ------------------------------------------------------------

	ACP_UNHANDLED_EXCEPTION(watchdog_timer, 12)

	#; ------------------------------------------------------------
	#; Data TLB Miss
	#;
	#; Test with the following.
	#;         unsigned long junk;
	#;         junk = *((unsigned long *)0xa0000000);
	#;         printf("junk is 0x%08lx\n", junk);
	#; ------------------------------------------------------------

	ACP_UNHANDLED_EXCEPTION(data_tlb_miss, 13)

	#; ------------------------------------------------------------
	#; Instruction TLB Miss
	#; Test with the following.
	#;         void (*junk)(void)
	#;         junk = (void (*)(void))0xa0000000;
	#;         junk();
	#; ------------------------------------------------------------

	ACP_UNHANDLED_EXCEPTION(instruction_tlb_miss, 14)

	#; ------------------------------------------------------------
	#; Debug
	#; ------------------------------------------------------------

	ACP_UNHANDLED_EXCEPTION(debug, 15)

###
### Local Variables:
### asm-comment-char: ?\#
### End:
###
