/*********************************************************************
 *
 * memset.S
 *
 * An implementation of the Linux ARM architecture specific memset.
 *
 * r0 is the location to set
 * r1 is the value to set it to
 * r2 is the number of bytes
 *
 * r0 is returned unchanged
 *
 *********************************************************************/

#ifdef __HAVE_ARCH_MEMSET
        
        /*------------------------------------------------------------
         * memset
         */

        .global memset

memset:
        
        stmdb   sp!,{r0-r5,lr}  @ save registers
        ands    r3,r0,#3        @ is r0 4 byte aligned?
        beq     1f
        
        /*
           -- handle the unaligned case --
        */
        
        subs    r2,r2,#4
        blt     4f              @ less than 4 bytes, go to the end...
        cmp     r3,#2           @ r3 is the remainder, 0...3
        
        /*
           If r3 is 1, we need to write 3 zeros since 1 - 4 is -3.
           If r3 is 2, we need to write 2 zeros since 2 - 4 is -2.
           If r3 is 3, we neet to write 1 zero since 3 - 4 is -1.
        */
        
        strltb  r1,[r0],#1
        strleb  r1,[r0],#1
        strb    r1,[r0],#1
        add     r2,r2,r3        @ r2 = r2 - ( 4 - r3 )
        
        /*
           The pointer is now aligned (and zeros written in the
           un-aligned section between r0 and the boundry.
        */

1:      orr     r1,r1,r1,lsl #8 @ fill r1 with the value of the bottom byte
        orr     r1,r1,r1,lsl #16
        mov     r3,r1           @ fill r3-r5 with r1
        mov     r4,r1
        mov     r5,r1
        cmp     r2,#16
        blt     3f
2:      subs    r2,r2,#64
        stmgeia r0!,{r1,r3,r4,r5}       @ 64 bytes at a time
        stmgeia r0!,{r1,r3,r4,r5}
        stmgeia r0!,{r1,r3,r4,r5}
        stmgeia r0!,{r1,r3,r4,r5}
        bgt     2b
        tst     r2,#32
        stmneia r0!,{r1,r3,r4,r5}
        stmneia r0!,{r1,r3,r4,r5}
        tst     r2,#16
        stmneia r0!,{r1,r3,r4,r5}
3:      tst     r2,#8
        stmneia r0!,{r1,r3}
        tst     r2,#4
        strne   r1,[r0],#4
4:      tst     r2,#2
        strneb  r1,[r0],#1
        strneb  r1,[r0],#1
        tst     r2,#1        
        strneb  r1,[r0],#1
        ldmia   sp!,{r0-r5,pc}          @ restore registers and return

#endif
