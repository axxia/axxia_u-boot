@
@  Board specific setup info
@
@  (C) Copyright 2008
@  LSI <www.lsi.com>
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

#define LANG_ASM
        
#include <config.h>
#include <version.h>

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ Constants
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#define MAGIC_NUMBER 0x4f7a5478

#define MBYTES_32   0x02000000
#define MBYTES_64   0x04000000
#define MBYTES_128  0x08000000
#define MBYTES_256  0x10000000
#define MBYTES_512  0x20000000
#define MBYTES_1024 0x40000000

#define MHZ_125 0x7735940
#define MHZ_133 0x7f28155
#define MHZ_166 0x9ef21aa
#define MHZ_180 0xaba9500
#define MHZ_200 0xbebc200

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ Macros
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ pll_read
        @
        @ Reads a PLL register.  Based on the description in the 'Register
        @ Programming Guide'.
        @
        @ Trashes r3 and returns the result in r0.
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        .macro  pll_read,offset
        ldr     r3,=CONFIG_NORMAL_ASI_BASE
        str     \offset,[r3,#0x104]     @ Set the offset
        mov     r0,#0x80000000          @ Command is start
        str     r0,[r3,#0x100]          @ Write the command
        mcr     p15,0,r0,c7,c10,4       @ Drain the write buffer.
1:      ldr     r0,[r3,#0x100]          @ Wait for completion
        and     r0,r0,#0x80000000
        cmp     r0,#0
        bne     1b
        ldr     r0,[r3,#0x108]          @ Result in r0
        .endm

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ pll_write
        @
        @ Write a PLL register.  Based on the description in the 'Register
        @ Programming Guide'.
        @
        @ Trashes r3 and \value.
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        .macro  pll_write,value,offset
        ldr     r3,=CONFIG_NORMAL_ASI_BASE
        str     \offset,[r3,#0x104]             @ Set the offset
        str     \value,[r3,#0x108]              @ Set the value
        mov     \value,#0x80000000              @ Command is start,
        orr     \value,\value,#0x4              @ and write.
        str     \value,[r3,#0x100]              @ Write the command
        mcr     p15,0,r0,c7,c10,4               @ Drain the write buffer.
1:      ldr     \value,[r3,#0x100]              @ Wait for completion
        and     \value,\value,#0x80000000
        cmp     \value,#0
        bne     1b
        .endm

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ cbi_read
        @
        @ CBI read.  Based on the description in the 'Register Programming
        @ Guide'.
        @
        @ node, target, and offset must be unique.  The answer will be in
        @ offset.
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        .macro  cbi_read,node,target,offset
        mov     \node,\node,lsl #10
        orr     \node,\target, lsl #4
        orr     \node,\node,#0x80000000         @ start bit
        orr     \node,\node,#0x40000            @ 4 bytes
        orr     \node,\node,#1                  @ read, block mode
        ldr     \target,=CONFIG_NORMAL_ASI_BASE
        str     \offset,[\target,#0x17c]        @ write the offset
        str     \node,[\target,#0x178]          @ write the command
        mov     \node,#0
        mcr     p15,0,\node,c7,c10,4            @ drain the write buffer
1:      ldr     \node,[\target,#0x178]          @ wait for completion
        and     \node,\node,#0x80000000
        cmp     \node,#0
        bne     1b
        ldr     \offset,[\target,#0x180]        @ store result in \offset
        .endm

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ cbi_write
        @
        @ CBI write.  Based on the description in the 'Register Programming
        @ Guide'.
        @
        @ node, target, offset, and value must be unique.
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        .macro  cbi_write,node,target,offset,value
        mov     \node,\node,lsl #10             @ node
        orr     \node,\target, lsl #4           @ target
        orr     \node,\node,#0x80000000         @ start bit
        orr     \node,\node,#0x40000            @ 4 bytes
        orr     \node,\node,#0x5                @ write, block mode
        ldr     \target,=CONFIG_NORMAL_ASI_BASE
        str     \offset,[\target,#0x17c]        @ write the offset
        str     \value,[\target,#0x180]         @ write the value
        str     \node,[\target,#0x178]          @ write the command
        mov     \node,#0                        @ drain the write buffer
        mcr     p15,0,\node,c7,c10,4
1:      ldr     \node,[\target,#0x178]          @ wait for completion
        and     \node,\node,#0x80000000
        cmp     \node,#0
        bne     1b
        .endm

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ divide
        @
        @ Trashes r3 and returns the result in r0
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        .macro  divide,dividend,divisor
        cmp     \divisor,#0
        beq     30f
        mov     r0,#0
        mov     r3,#1
10:
        cmp     \divisor,\dividend
        movls   \divisor,\divisor,lsl #1
        movls   r3,r3,lsl #1
        bls     10b
20:
        cmp     \dividend,\divisor
        subcs   \dividend,\dividend,\divisor
        addcs   r0,r0,r3
        movs    r3,r3,lsr #1
        movcc   \divisor,\divisor,lsr #1
        bcc     20b
        b       40f
30:
        mov     r0,#0                           @ Divide by zero
40:
        .endm

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ is_fpga
        @
        @ ssr = System Status Register
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        .macro  is_fpga,ssr,result
        and     \result,\ssr,#0x80000000
        .endm

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ release
        @
        @ ssr = System Status Register
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        .macro  release,ssr,result
        and     \result,\ssr,#0xe0
        mov     \result,\result,lsr #5
        .endm

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ revision
        @
        @ ssr = System Status Register
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        .macro  revision,ssr,result
        and     \result,\ssr,#0x1f
        .endm

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ version
        @
        @ ssr = System Status Register
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        .macro  version,ssr,result
        and     \result,\ssr,#0xff
        .endm

#undef DEBUG
@#define DEBUG
#ifdef DEBUG

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ debug_uart_init
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        .macro  debug_uart_init,s1,s2
        ldr     \s1,=(GPIO_MUX)
        ldr     \s2,=(0x54141555)
        str     \s2,[\s1]
        ldr     \s1,=(CONFIG_NORMAL_CT_BASE)
        mov     \s2,#0x01
        str     \s2,[\s1,#0x20]
        mov     \s2,#0xc0
        str     \s2,[\s1,#0x28]
        ldr     \s1,=(CONFIG_NORMAL_UART_BASE)
        mov     \s2,#0x88
        str     \s2,[\s1,#0x24]
        mov     \s2,#0x0a
        str     \s2,[\s1,#0x28]
        mov     \s2,#0x70
        str     \s2,[\s1,#0x2c]
        ldr     \s2,=(0x301)
        str     \s2,[\s1,#0x30]
        mov     \s2,#0x00
        str     \s2,[\s1,#0x34]
        ldr     \s2,=(0x700)
        str     \s2,[\s1,#0x38]
        mov     \s2,#0x00
        str     \s2,[\s1,#0x04]
        .endm

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ debug_uart_put
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        .macro  debug_uart_put,value,s1,s2
        ldr     \s1,=(CONFIG_NORMAL_UART_BASE)
1001:   ldr     \s2,[\s1,#0x18]
        tst     \s2,#0x20
        bne     1001b
        str     \value,[\s1]
        cmp     \value,#'\n'
        moveq   \value,#'\r'
        beq     1001b
        .endm

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ debug_uart_puts
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        .macro  debug_uart_puts,string,s1,s2,s3
2001:   mov             \s1,#0
        ldrb            \s1,[\string],#1
        debug_uart_put  \s1,\s2,\s3
        cmp             \s1,#0
        bne             2001b
        .endm

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ debug_uart_putreg
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        .macro  debug_uart_putreg,value,s1,s2,s3
        mov             \s1,#'0'
        debug_uart_put  \s1,\s2,\s3
        mov             \s1,#'x'
        debug_uart_put  \s1,\s2,\s3
        and             \s1,\value,#0xf0000000
        mov             \s1,\s1,lsr #28
        cmp             \s1,#9
        addle           \s1,\s1,#'0'
        addgt           \s1,\s1,#0x57
        debug_uart_put  \s1,\s2,\s3
        and             \s1,\value,#0xf000000
        mov             \s1,\s1,lsr #24
        cmp             \s1,#9
        addle           \s1,\s1,#'0'
        addgt           \s1,\s1,#0x57
        debug_uart_put  \s1,\s2,\s3
        and             \s1,\value,#0xf00000
        mov             \s1,\s1,lsr #20
        cmp             \s1,#9
        addle           \s1,\s1,#'0'
        addgt           \s1,\s1,#0x57
        debug_uart_put  \s1,\s2,\s3
        and             \s1,\value,#0xf0000
        mov             \s1,\s1,lsr #16
        cmp             \s1,#9
        addle           \s1,\s1,#'0'
        addgt           \s1,\s1,#0x57
        debug_uart_put  \s1,\s2,\s3
        and             \s1,\value,#0xf000
        mov             \s1,\s1,lsr #12
        cmp             \s1,#9
        addle           \s1,\s1,#'0'
        addgt           \s1,\s1,#0x57
        debug_uart_put  \s1,\s2,\s3
        and             \s1,\value,#0xf00
        mov             \s1,\s1,lsr #8
        cmp             \s1,#9
        addle           \s1,\s1,#'0'
        addgt           \s1,\s1,#0x57
        debug_uart_put  \s1,\s2,\s3
        and             \s1,\value,#0xf0
        mov             \s1,\s1,lsr #4
        cmp             \s1,#9
        addle           \s1,\s1,#'0'
        addgt           \s1,\s1,#0x57
        debug_uart_put  \s1,\s2,\s3
        and             \s1,\value,#0xf
        cmp             \s1,#9
        addle           \s1,\s1,#'0'
        addgt           \s1,\s1,#0x57
        debug_uart_put  \s1,\s2,\s3
        .endm

#endif
        
#if defined( LSI_ARCH_APP3K )
#if defined( CL3 )
#include "app3k.cl3.meminit"
#elif defined( CL4 )
#error "CL4 Memory is not support at present"
#include "app3k.cl4.meminit"
#else
#error "Unknown AP Memory Type"
#endif
#elif defined( LSI_ARCH_APP3 )
#if defined( CL3 )
#include "app3.cl3.meminit"
#elif defined( CL4 )
#error "CL4 Memory is not support at present"
#include "app3.cl4.meminit"
#else
#error "Unknown AP Memory Type"
#endif
#endif

_TEXT_BASE:
        .word   TEXT_BASE               @ sdram load addr from config.mk

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ lowlevel_init
        @
        @ Gets called from start.S before the copy to RAM.  Assumes r0-r10
        @ are "volatile".
        @
        @ Address 0x50000000 is equivalent to
        @   9056/2.2.0x380000 or Np5/1.0.0x00000000
        @ Address 0x58000000 is equivalent to
        @   9056/2.2.0x300000 or Np5/1.2.0x00000000
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        .align  5
        .globl  lowlevel_init

lowlevel_init:

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ Allow access to the host interface registers.  Without this write,
        @ the network processor registers won't be accessible.
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        ldr     r0,=CONFIG_NORMAL_AEI_BASE
        ldr     r1,=MAGIC_NUMBER
        @ CONFIG_NORMAL_AEI_BASE + 0x8 = 0x4f7a5478
        str     r1,[r0,#0x08]

#ifdef DEBUG
        
        b                       debug_display_splash

        debug_splash_:
        .asciz                  "\n\n** Low Level Debug Enabled **\n"
        .align

debug_display_splash:

        debug_uart_init         r0,r1
        adr                     r0,debug_splash_
        debug_uart_puts         r0,r1,r2,r3
        @ldr                     r0,=0xabcddcba
        @debug_uart_putreg       r0,r1,r2,r3
        @mov                     r0,#'\n'
        @debug_uart_put          r0,r1,r2

#endif
        
        b       ram_test
        
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ Determine whether running in FLASH or RAM.  It would not be wise to
        @ try to initialize RAM while running in it...
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        .global _started_in_ram
        
_started_in_ram:
        
        .word   0x00000000

RAM_TEST_VALUE:

        .word   0x12345678

ram_test:       

        adr             r2,RAM_TEST_VALUE
        ldr             r0,[r2]                 @ Load the value at
                                                @ RAM_TEST_VALUE into r0
        mvn             r1,r0                   @ Store the complement in r1
        str             r1,[r2]                 @ Write r1 to RAM_TEST_VALUE
        ldr             r1,[r2]                 @ Load r1 from RAM_TEST_VALUE
        cmp             r0,r1                   @ Compare r0 and r1 to determine
                                                @ whether RAM_TEST_VALUE is
                                                @ writable
        adrne           r2,_started_in_ram      @ Change the local variable,
        movne           r0,#1                   @ _started_in_ram, to 1 if
        strne           r0,[r2]                 @ already in ram
        bne             done

#if defined( LSI_ARCH_APP3K )
        
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ Jump to the NOR flash alias (0x5000_0000 + pc).
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        ldr     r0,=CONFIG_NORMAL_NOR_ALIAS_BASE
        adr     r1,jump_label
        bic     r1,#0xff000000
        bic     r1,#0x00f00000
        add     r1,r1,r0
        bic     lr,#0xff000000
        bic     lr,#0x00f00000
        add     lr,lr,r0
        bic     ip,#0xff000000
        bic     ip,#0x00f00000
        add     ip,ip,r0
        mov     pc,r1
        
jump_label:

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ Change to the normal memory map
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        ldr     r0,=CONFIG_NORMAL_REMAP_BASE
        mov     r1,#1
        str     r1,[r0,#0x4]
        
#endif

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ Check for a warm restart with or without a loaded configuration.
        @ If a configuration was loaded by the RTE, bit 16 of the scratch
        @ register will be set.  If not, the APP3K still must not try to
        @ configure the AP memory controller.  In this case, Linux will write
        @ 0xaabb5544 to register 9.
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        ldr     r1,=CONFIG_NORMAL_ASI_BASE
        ldr     r0,[r1,#0x14]
        tst     r0,#0x10000
        bne     clear_memory_32
#if defined( LSI_ARCH_APP3K )
        ldr     r1,=0xaabb5544
        cmp     r9,r1
        beq     clear_memory_32
#endif

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ Determine whether running on an FPGA or ASIC.  The FPGA does not
        @ have the PLL, the clocks values are fixed.
        @
        @ agNp5(Read|Write) 0.0.0 = 0x2000_0000
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

fpga_test:      

        @ Use bit 31 of the 'System Status Register' to determine
        @ whether this is an ASIC or an FPGA.

        ldr             r0,=CONFIG_NORMAL_ASI_BASE
        ldr             r8,[r0,#0xc]            @ r8 contains the ssr value

        @ ASIC initialization, use the PLL to determine the speed of
        @ the clocks and then use that to pick the ddr recipe
        
        is_fpga         r8,r1
        cmp             r1,#0
        beq             setup_clocks

        @ Since the FPGA clocks are fixed, use CLOCKS_FPGA
        
        ldr             r9,=CLOCKS_FPGA         @ r9 contains the core clock
        ldr             r10,=CLOCKS_FPGA        @ r10 contains the ddr clock

        mov             r7,lr
        bl              ddr_init_fpga
        mov             lr,r7

        b               ram_initialized

setup_clocks:

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#if defined( LSI_ARCH_APP3K )

        ldr     r4,=CONFIG_NORMAL_DDR2_CFG_BASE
        mov     r5,#0
        str     r5,[r4]

#elif defined( LSI_ARCH_APP3 )

        @ DDRI) @@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @ DDRI) PLL Setup
        mov     r4,#0x50000000          @ r4 = 1.2. (3.0)
        orr     r3,r4,#0x8000000        @ r3 = 1.0. (3.4)
        @ DDRI) 0x5800_0000 = 0x0000_0000
        mov     r5,#0
        str     r5,[r3]

#endif

        @ 0x3 in the scratch field of the reconfig control register
        @ indicates that the PLL next registers have been set up and
        @ a reconfig should be issued.

        mov             r1,#0x3c
        pll_read        r1
        and             r2,r0,#0xf      @ r2 contains the scratch bits
        cmp             r2,#0x3
        bne             initialize_ram

        mov             r0,#0xf2
        mov             r1,#0x3c
        pll_write       r0,r1           @ start the reconfig.

        @ The above write should reset the chip, the following
        @ code should never be reached!

initialize_ram:

        @ Store the core clock speed in r9

        mov             r1,#0xc
        pll_read        r1
        mov             r4,r0
        mov             r7,lr
        bl              platform_get_clock_
        mov             lr,r7
        mov             r9,r0,lsl #1

        @ Store the ddr clock speed in r10

        mov             r1,#0x10
        pll_read        r1
        mov             r4,r0
        mov             r7,lr
        bl              platform_get_clock_
        mov             lr,r7
        mov             r10,r0

        @ Initialize the memory controller

#if defined( LSI_ARCH_APP3K )
#if 1
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @ AP, PP, and PK address lines should be held low for 50 msecs
        @
        @ Enable the RX and TX interfaces in the system control register
        ldr             r0,=CONFIG_NORMAL_ASI_BASE
        ldr             r1,=0x0003000f
        str             r1,[r0,#0x08]
        @ AP DESL
        ldr             r0,=CONFIG_NORMAL_DDR2_CFG_BASE
        mov             r1,#0x6c0000
        str             r1,[r0,#0x10]
        @ PP DESL
        mov             r1,#0x40000
        mov             r0,#1
        mov             r2,#0
        mov             r3,#0x10
        cbi_write       r0,r2,r3,r1
        @ PK DESL
        mov             r0,#3
        mov             r2,#0
        mov             r3,#0x290
        cbi_write       r0,r2,r3,r1
        @ 50 msec delay
        mov             r0,#50
        mov             r7,lr
        bl              platform_msleep_
        mov             lr,r7
#endif
#endif

        @ Up to 125 MHz, use ddr_init_125

        ldr             r0,=MHZ_125
        cmp             r10,r0
        bgt             1f
        mov             r7,lr
        bl              ddr_init_125
        mov             lr,r7
        b               clear_phase_shift

        @ Up to 133 MHz, use ddr_init_133

1:      

        ldr             r0,=MHZ_133
        cmp             r10,r0
        bgt             2f
        ldr             r1,=CONFIG_NORMAL_ASI_BASE
        str             r0,[r1,#0x14]
        mov             r7,lr
        bl              ddr_init_133
        mov             lr,r7
        b               clear_phase_shift

        @ Up to 166 MHz, use ddr_init_166

2:
        
        ldr             r0,=MHZ_166
        cmp             r10,r0
        bgt             3f
        mov             r7,lr
        bl              ddr_init_166
        mov             lr,r7
        b               clear_phase_shift

        @ Up to 200 MHz, or as a last resort, use ddr_init_200

3:      

        mov             r7,lr
        bl              ddr_init_200
        mov             lr,r7
        b               clear_phase_shift

clear_phase_shift:

        @ Clear the PLL phase shift register.  See defect 19925.
        mov             r0,#0
        mov             r1,#0x7c
        pll_write       r0,r1

ram_initialized:

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ Set termination (ODT).
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        mov             r7,lr
        bl              set_termination
        mov             lr,r7

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ Set the number of banks, 4 or 8, and the column address width.
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        
        mov             r7,lr
        bl              banks_and_columns
        mov             lr,r7

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ Adjust the specification value based on density and ddr clock.
        @ Note that the number of banks and the column address width must
        @ be set first.
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        @ Check for FGPA
        is_fpga         r8,r0
        cmp             r0,#0
        movne           r7,lr
        blne            ddr_adj_fpga
        movne           lr,r7
        bne             ram_size

        @ Up to 125 MHz, call ddr_adj_125

        ldr             r0,=MHZ_125
        cmp             r10,r0
        movle           r7,lr
        blle            ddr_adj_125
        movle           lr,r7
        ble             ram_size

        @ Up to 133 MHz, call ddr_adj_133

        ldr             r0,=MHZ_133
        cmp             r10,r0
        movle           r7,lr
        blle            ddr_adj_133
        movle           lr,r7
        ble             ram_size

        @ Up to 166 MHz, call ddr_adj_166

        ldr             r0,=MHZ_166
        cmp             r10,r0
        movle           r7,lr
        blle            ddr_adj_166
        movle           lr,r7
        ble             ram_size

        @ Up to 200 MHz, or as a last resort, use ddr_init_200

        mov             r7,lr
        bl              ddr_adj_200
        mov             lr,r7
        b               ram_size

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ Figure out how much memory there is.
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

RAM_BASE:
        .word   PHYS_RAM_BASE
CHUNK_SIZE:
        .word   0x800000
MAX_SIZE:
#if defined( LSI_ARCH_APP3K )
        .word   0x40000000
#else
        .word   0x10000000
#endif

ram_size:

        adr     r3,RAM_BASE
        ldr     r0,[r3]         @ r0 contains the base address of RAM
        adr     r3,CHUNK_SIZE
        ldr     r1,[r3]         @ r1 contains the chunk size
        adr     r3,MAX_SIZE
        ldr     r2,[r3]         @ r2 contains the maximum size
        mov     r3,r1           @ r3 contains the chunk size
        mov     r7,#0x12000000
        orr     r7,r7,#0x340000
        orr     r7,r7,#0xab00
        orr     r7,r7,#0xcd

ram_size_loop:

        add     r5,r3,r0
        mov     r6,r3,lsl #1
        add     r6,r6,r0
        sub     r5,r5,#4
        sub     r6,r6,#4
        str     r7,[r5]
        mvn     r8,r7
        str     r8,[r6]
        ldr     r8,[r5]
        ldr     r9,[r6]
        cmp     r8,r9
        beq     ram_size_done
        add     r3,r3,r1
        mov     r6,r3,lsl #1
        cmp     r6,r2
        bls     ram_size_loop
        mov     r3,r2
        
ram_size_done:
        mov     r1,r3           @ r1 contains the size of RAM
        b       clear_memory

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ Clear Lower 32 Mbytes
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

clear_memory_32:

        ldr     r1,=MBYTES_32
        b       clear_memory

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ Clear memory
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

clear_memory:

#if defined( LSI_ARCH_APP3 )
        @ Only clear the first 32 Mbytes.  For now, all memory must be
        @ cleared on the APP3K...
        ldr     r1,=MBYTES_32
#endif
        
        ldr     r0,=PHYS_RAM_BASE       @ r0 contains the base address of RAM
        mov     r2,#0                   @ r2 contains the fill value

        ands    r3,r0,#3                @ is r0 4 byte aligned?
        beq     mz_aligned_
        
        /*
           -- handle the unaligned case --
        */
        
        subs    r1,r1,#4
        blt     less_than_4_    @ less than 4 bytes, go to the end...
        cmp     r3,#2           @ r3 is the remainder, 0...3
        
        /*
           If r3 is 1, we need to write 3 zeros since 1 - 4 is -3.
           If r3 is 2, we need to write 2 zeros since 2 - 4 is -2.
           If r3 is 3, we neet to write 1 zero since 3 - 4 is -1.
        */

        ldrltb  r2,[r0]        
        strltb  r2,[r0],#1
        ldrleb  r2,[r0]        
        strleb  r2,[r0],#1
        ldrb    r2,[r0]
        strb    r2,[r0],#1
        add     r1,r1,r3        @ r1 = r1 - ( 4 - r3 )
        
        /*
           The pointer is now aligned (and zeros written in the
           un-aligned section between r0 and the boundry.
        */

mz_aligned_:
        
        mov     r3,r2           @ fill r3-r5 with r2
        mov     r4,r2
        mov     r5,r2
        cmp     r1,#16
        blt     eight_or_less_

sixtyfour_byte_loop_:  
        
        subs    r1,r1,#64
        stmgeia r0!,{r2,r3,r4,r5}       @ 64 bytes at a time
        stmgeia r0!,{r2,r3,r4,r5}
        stmgeia r0!,{r2,r3,r4,r5}
        stmgeia r0!,{r2,r3,r4,r5}
        bgt     sixtyfour_byte_loop_
        beq     done
        tst     r1,#32
        stmneia r0!,{r2,r3,r4,r5}
        stmneia r0!,{r2,r3,r4,r5}
        tst     r1,#16
        stmneia r0!,{r2,r3,r4,r5}

eight_or_less_:
        
        tst     r1,#8
        stmneia r0!,{r2,r3}
        tst     r1,#4
        strne   r2,[r0],#4

less_than_4_:

        tst     r1,#2
        strneb  r2,[r0],#1
        strneb  r2,[r0],#1
        tst     r1,#1        
        strneb  r2,[r0],#1

done:

#if defined( LSI_ARCH_APP3K )
        @ Clear ECC errors caused by the above...
        ldr     r1,=CONFIG_NORMAL_DDR2_CFG_BASE
        ldr     r0,[r1,#0x20]
        bic     r0,#0x3
        str     r0,[r1,#0x20]
#endif

        mov     pc,lr

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ platform_msleep_
        @
        @ Trashes r1-2.  Expects the ARM core clock speed (in MHz) in r9.
        @
        @ Don't try to delay more than 10 seconds!
        @
        @@@@ IN @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ r0 - The number of msec to sleep
        @
        @@@@ OUT @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ nothing
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        .align  5

platform_msleep_:

        @ clear the timer

        ldr             r1,=CONFIG_NORMAL_CT_BASE
        mov             r2,#0
        str             r2,[r1,#0x8]

        @ set the load value

        mov             r2,r9,lsr #10           @ counts in 1 ms
        mul             r1,r2,r0
        mov             r2,r1
        ldr             r1,=CONFIG_NORMAL_CT_BASE
        str             r2,[r1]

        @ start the timer

        mov             r2,#0xc3
        str             r2,[r1,#0x8]

        @ wait for it to finish

platform_msleep_wait_:

        ldr             r2,[r1,#0x4]
        cmp             r2,#0
        bne             platform_msleep_wait_

platform_msleep_done_:  

        mov             pc,lr

        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ platform_get_clock_
        @
        @ Trashes r0...r6
        @
        @@@@ IN @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ r4 - The PLL select register
        @
        @@@@ OUT @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @ r0 - The clock speed
        @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

platform_get_clock_:

#if defined( LSI_ARCH_APP3K )
        mov             r1,#0x90
        pll_read        r1
        mov             r2,r0           @ Misc. config register
#endif

        @ Put the pll control registers in r5 and r6

        and             r0,r4,#0x8      @ PLL select bit
        teq             r0,#0
        bne             use_pll_1_

use_pll_0_:

        mov             r1,#0
        pll_read        r1
        mov             r5,r0
        mov             r1,#4
        pll_read        r1
        mov             r6,r0
#if defined( LSI_ARCH_APP3K )
        tst             r2,#0x40
        ldreq           r2,=APP3XX_PCI_CLOCK
        ldrne           r2,=APP3XX_REF_CLOCK
#elif defined( LSI_ARCH_APP3 )
        ldr             r2,=APP3XX_REF_CLOCK
#endif
        b               get_vco_
        
use_pll_1_:


        mov             r1,#0x20
        pll_read        r1
        mov             r5,r0
        mov             r1,#0x24
        pll_read        r1
        mov             r6,r0
#if defined( LSI_ARCH_APP3K )
        tst             r2,#0x80
        ldreq           r2,=APP3XX_PCI_CLOCK
        ldrne           r2,=APP3XX_REF_CLOCK
#elif defined( LSI_ARCH_APP3 )
        ldr             r2,=APP3XX_REF_CLOCK
#endif

get_vco_:

        and             r1,r5,#0xf
        add             r1,r1,#1
        divide          r2,r1
        mov             r2,r0,lsl #1
        and             r1,r6,#0x3f
        add             r1,r1,#2
        mul             r3,r2,r1
        and             r1,r5,#0x20
        cmp             r1,#0
        movne           r3,r3,lsr #1
        mov             r5,r3
        
        @ r4 is the select register, r5 is the vco

        mov             r2,r5

        @ get mux1_control

        and             r1,r4,#0x7

        @ =0 => speed = reference

        cmp             r1,#0
        ldreq           r2,=APP3XX_REF_CLOCK
        beq             mux1_done_

        @ =2 => speed /= 2

        cmp             r1,#2
        moveq           r2,r2,lsr #1
        beq             mux1_done_

        @ =3 => speed /= 3

        cmp             r1,#3
        bne             100f
        divide          r2,r1
        mov             r2,r0
        beq             mux1_done_

100:     

        @ =4 => speed /= 4

        cmp             r1,#4
        moveq           r2,r2,lsr #2
        beq             mux1_done_

        @ =5 => speed /= 5

        cmp             r1,#5
        bne             200f
        divide          r2,r1
        mov             r2,r0
        b               mux1_done_

200:      

        @ =6 => speed = reference * 2

        cmp             r1,#6
        ldreq           r2,=APP3XX_REF_CLOCK
        moveq           r2,r2,lsl #1

mux1_done_:
        
        @ get mux2_control

        and             r1,r4,#0x30
        mov             r1,r1,lsr #4

        @ =1 => speed /= 2

        cmp             r1,#1
        moveq           r2,r2,lsr #1
        beq             300f

        @ =2 => speed /= 4

        cmp             r1,#2
        moveq           r2,r2,lsr #2
        beq             300f

        @ =3 => speed /= 8

        cmp             r1,#3
        moveq           r2,r2,lsr #3

300:    

        @ return

        mov             r0,r2
        mov             pc,lr
