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
#include <ppc_asm.tmpl>
#include <ppc_defs.h>

	.section	.brs,"ax"

	#; ------------------------------------------------------------
	#; Define all the UTLB entries that need to be added.
	#; ------------------------------------------------------------

utlb_table:

	#; -- -- System Memory -- --
	#; Physical Address - 0x0000_0000_0000
	#; Virtual Address - 0x0000_0000
	#; Size - 1G
#ifdef ACP_ISS
	#; Only 256M on ISS.
	.long		0x80000000,0x000009f0,0x00000000,0x00030507
#else
	.long		0x80000000,0x00000bf0,0x00000000,0x00030507
#endif

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

#ifdef ACP_25xx
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
	#; -- -- Local CPU memory -- --
	#; Physical Address - 0x0010_0000_0000
	#; Virtual Address - 0xf0a0_0000
	#; Size - 1M
	.long		0x80000000,0xf0a00870,0x00000010,0x00030507
#endif
	
	#; -- -- ROM -- --
	#; Physical Address - 0x0021_0000_0000
	#; Virtual Address - 0xf0b0_0000
	#; Size - 1M
#ifdef ACP_ISS
	#; ROM is writable on ISS.
	.long		0x80000000,0xf0b00870,0xc000002f,0x00030507
#else
	.long		0x80000000,0xf0b00870,0xc000002f,0x00030507
#endif

utlb_table_end:

	#; ------------------------------------------------------------
	#; brs
	#;
	#; BootRom Simulator
	#;
	#; On ACP development systems, it is possible to load the
	#; second stage boot loader using an external system.  In that
	#; case the normal bootrom code won't get executed.  The
	#; following is intended to do what the bootrom would have done
	#; and then be overwritten.
	#; ------------------------------------------------------------

brs:

	#; ------------------------------------------------------------
	#; From the PPC476FP User's Guide
	#;
	#; 9.4 Initialization Software Requirements
	#; ------------------------------------------------------------

	#; 1. Branch backwards from effective address 0xFFFF FFFC to
	#;    the start of the initialization sequence.
	#; 
	#; See "reset_vector:" in vectors.S.

	#; 2. Invalidate the instruction cache (ici).

	#; ici

	#; 3. Invalidate the data cache (dci).

	#; dci

	#; 4. Synchronize memory accesses (msync).

	#; msync

	#; Doing this clears all breakpoints!
	#; 5. Clear the DBCR0 register to disable all debug events.

	li		r0,0
	mtdbcr0		r0

	#; 6. Clear the DBSR register to initialize all debug event status.

	mtspr		dbsr,r0

#ifndef ACP_ISS

	#; 7. Initialize the Core Configuration Register 0 (CCR0).

	lis		r0,(0x30004050)@h
	ori		r0,r0,(0x30004050)@l
	mtspr		ccr0,r0

	#; 8. Initialize the Core Configuration Register 1 (CCR1) register.

	lis		r23,(0x00000400)@h
	ori		r23,r23,(0x00000400)@l
	mtspr		ccr1,r23
	
	#; CCR2
#if 0	
	lis		r23,(0x04000000)@h
	ori		r23,r23,(0x04000000)@l
	mtspr		ccr2,r23
#endif
#endif
	
	#; 9. Configure the instruction and data cache regions.
	#;
	#; As caches won't be enabled until the 2nd stage, at least,
	#; this step is skipped.

	#; 10. Set up a TLB entry to cover the initial program memory page.
	#;
	#; a. Initialize the Memory Management Unit MMU Configuration
	#;    Register (MMUCR).

	#; ?
	
	#;
	#; b. Write a TLB entry for the initial program memory page.
	#;
	#; All boot UTLB entries get set up in the following.
	#;
	#; c. Initialize the PID to match the TID field of the TLB entry
	#;    (unless TID = 0).
	#;
	#; TID will remain 0.
	#;
	#; d. Set up for subsequent MSR[IS,DS] initialization to correspond
	#;    to the TS field of the TLB entry.
	#;
	#; TS will remain 0 (see all entries in utlb_table:).
	#;
	#; e. Set up for the subsequent change in the instruction fetch
	#;    address. This is necessary only if the EPN field of the TLB
	#;    entry changed from the initial value (EPN[0:19] != 0xFFFFF).
	#;
	#; Unnecessary, bootrom will keep the initial entry.
	#;
	#; f. Fully initialize the TLB. Issue a tlbwe to all three words
	#;    of each TLB entry; Issuing tlbre to TLB entries that are not
	#;    fully initialized can result in parity exceptions.
	#;
	#;  Handled by the following.

set_up_utlb:

	#; Set up for searches by page size.

	lis		r23,(0x9abcdef0)@h
	ori		r23,r23,(0x9abcdef0)@l
	mtspr		sspcr,r23
	mtspr		uspcr,r23
	lis		r23,(0x12345670)@h
	ori		r23,r23,(0x12345670)@l
	mtspr		ispcr,r23

	#; Set up the mmucr.

	mfspr		r23,mmucr
	lis		r24,(0xfffe0000)@h
	ori		r24,r24,(0xfffe0000)@l
	and		r23,r23,r24
	mtspr		mmucr,r23

	#; ------------------------------------------------------------
	#; Set up the TLB as described in tlb_table above.
	#; ------------------------------------------------------------

	#; Save the entry this code is currently executing in.

	bl		1f
1:	mflr		r23
	tlbsx		r23,0,r23
	tlbre		r24,r23,0
	tlbre		r25,r23,1
	tlbre		r26,r23,2

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

	oris		r23,r23,0x8000
	tlbwe		r24,r23,0
	tlbwe		r25,r23,1
	tlbwe		r26,r23,2
	isync

	#; Set up SRR0 (and SRR1) for rfi after the following.

	lis		r3,(init_core_relocate)@h
	ori		r3,r3,(init_core_relocate)@l
	mtspr		srr0,r3
	mfmsr		r3
	mtspr		srr1,r3

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

	#; Clear the initial entry

	lis		r0,(0xe0000000)@h
	ori		r0,r0,(0xe0000000)@l
	lis		r1,(0xfffff000)@h
	ori		r1,r1,(0xffff000)@l
	tlbwe		r1,r0,0

	#; g. Perform a context synchronization to invalidate the shadow
	#;    TLB contents and to cause the new TLB contents to take effect.

	#; The first time source level debugging will be readily available
	#; is at the statement after "init_core_relocate".

	rfi

init_core_relocate:

	#; 11. Initialize the interrupt resources.
	#;
	#; Any exceptions at this point will be fatal, so just send an
	#; error message... [TODO]

	#; 12. Configure the debug facilities as required.
	#;
	#; None required.

	#; 13. Configure the timer facilities as required. TSR is cleared.
	#;
	#; None required.

	#; 14. Initialize facilities outside the processor core that are
	#;     possible sources of asynchronous interrupt requests (including
	#;     Device Configuration Registers or other memory-mapped resources).
	#;     This must be done before enabling asynchronous interrupts in the
	#;     MSR.
	#; 15. Initialize the MSR to enable interrupts as required.
	#;
	#; No interrupts 'til later.

	#; 16. Initialize any other processor core resources as required by
	#;     the system (General Purpose Registers [GPRs], Special Purpose
	#;     Registers for general use (SPRGs), and so on).
	#; 17. Initialize any other facilities outside the processor core as
	#;     required by the system.
	#;
	#; System initialization starts in boot: (see boot.S).  Only core 0
	#; will initialize the system.
	
	#; 18. Initialize system memory as required by the system software.
	#;
	#; Handled by the 2nd stage boot loader.

	#; 19. Start the system software.

	#; ------------------------------------------------------------
	#; Put cores 1-3 in the "wait enable" state, set to jump to the
	#; base of the 3rd stage.
	#; ------------------------------------------------------------

	mfspr		r3,pir
#if defined(ACP_CORE1ONLY) && ! defined(ACP_ISS)
	cmpwi		r3,1
#else
	cmpwi		r3,SYSTEM_BOOTCORE
#endif
	bne		cold_reset_pen

	#; set up the PLB6

	li		r11,0x104
	li		r12,0x20
	isync
	mtdcrx		r11,r12
	li		r11,0x105
	isync
	mtdcrx		r11,r12
	li		r11,0x106
	isync
	mtdcrx		r11,r12
	li		r11,0x100
	lis		r12,0x80000000@h
	isync
	mtdcrx		r11,r12

	#; core 0 jumps to the base of LCM

	b		jump_to_the_2nd_stage

cold_reset_pen:

	#; Set the "soft interrupt" vector to send the core to the 3rd stage.

	li		r0,0
	mtspr		ivpr,r0
	mtspr		ivor0,r0
	mtspr		ivor1,r0
	mtspr		ivor2,r0
	mtspr		ivor3,r0
	mtspr		ivor4,r0
	mtspr		ivor5,r0
	mtspr		ivor6,r0
	mtspr		ivor7,r0
	mtspr		ivor8,r0
	mtspr		ivor9,r0
	mtspr		ivor10,r0
	mtspr		ivor11,r0
	mtspr		ivor12,r0
	mtspr		ivor13,r0
	mtspr		ivor14,r0
	mtspr		ivor15,r0

	#; ---------------------------------------------------------------------
	#; Set up the MPIC
	#; ---------------------------------------------------------------------

	#; Set the "Current Task Priority" register for this core to 0.
	#; This means any interrupt with a non-zero priority will be received.

	#; WRITEDCR( 0, 0xffc00080 )

	lis		r11,(0xffc00080)@h
	ori		r11,r11,(0xffc00080)@l
	li		r12,0
	isync
	#; mtdcrx		r11,r12
	#; Use 0x7c000306 | (0xb << 21) | (0xc << 16)
	#; to avoid incomaptibility with older binutils...
	.long		0x7d6c0306

	#; Disable 8259 Bypass Mode

	#; WRITEDCR( 0x2000000f, 0xffc01020 )

	lis		r11,(0xffc01020)@h
	ori		r11,r11,(0xffc01020)@l
	lis		r12,(0x2000000f)@h
	ori		r12,r12,(0x2000000f)@l
	isync
	#; mtdcrx		r11,r12
	#; Use 0x7c000306 | (0xb << 21) | (0xc << 16)
	#; to avoid incomaptibility with older binutils...
	.long		0x7d6c0306

	#; Set the "IPI Vector/Priority" register for this core.

	#;     - first wait for the activity bit to be clear.

	lis		r11,(0xffc010a0)@h
	ori		r11,r11,(0xffc010a0)@l
	lis		r12,(0x40000000)@h
	#; mfdcrx		r3,r11
	#; Use 0x7c000306 | (0x3 << 21) | (0xb << 16)
	#; to avoid incomaptibility with older binutils...
1:	.long		0x7c6b0206
	isync
	and		r3,r3,r12
	cmpwi		r3,0
	bne		1b

	#;     - then set the priority.

	lis		r3,(0x000f0000)@h
	#; mtdcrx		r11,r3
	#; Use 0x7c000306 | (0xb << 21) | (0x3 << 16)
	#; to avoid incomaptibility with older binutils...
	.long		0x7d630306

	#; Enable IPIs (set the MSR EE bit).
#if ! defined(ACP_CORE1ONLY) || defined(ACP_ISS)
	mfmsr		r3
	lis		r4,(0x00008000)@h
	ori		r4,r4,(0x00008000)@l
	or		r3,r3,r4
	mtmsr		r3
	isync
#endif
	#; Go to sleep.

	mfmsr		r3
	lis		r4,(0x00040000)@h
	ori		r4,r4,(0x00040000)@l
	or		r3,r3,r4
	mtmsr		r3
	isync

	#; Should never get here!

	ori		r1,r1,0
	ori		r1,r1,0
	ori		r1,r1,0
	ori		r1,r1,0
	ori		r1,r1,0
	b		cold_reset_pen

	#; ------------------------------------------------------------
	#; Clear the initial UTLB entry and jump to the base of LCM.
	#; ------------------------------------------------------------

jump_to_the_2nd_stage:

	lis		r3,(LCM)@h
	ori		r3,r3,(LCM)@l
	mtspr		srr0,r3
	li		r3,0
	mtspr		srr1,r3

	#; Clear out the UTLB shadow registers and jump to LCM.

	rfi

	.section	.brs_vector,"ax"

brs_vector:

	b		brs

###
### Local Variables:
### asm-comment-char: ?\#
### End:
###
