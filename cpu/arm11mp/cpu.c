/*
 * (C) Copyright 2004 Texas Insturments
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * (C) Copyright 2002
 * Gary Jennejohn, DENX Software Engineering, <gj@denx.de>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * CPU specific code
 */

#include <common.h>
#include <command.h>

#ifdef CONFIG_USE_IRQ
DECLARE_GLOBAL_DATA_PTR;
#endif

#define PAGE_TABLE_ADDRESS 0x4000

/* read co-processor 15, register #1 (control register) */
static unsigned long read_p15_c1 (void)
{
	unsigned long value;

	__asm__ __volatile__(
				"mrc	p15, 0, %0, c1, c0, 0   @ read control reg\n"
				: "=r" (value)
				:
				: "memory");
	return value;
}

/* write to co-processor 15, register #1 (control register) */
static void write_p15_c1 (unsigned long value)
{
	__asm__ __volatile__(
						"mcr	p15, 0, %0, c1, c0, 0   @ write it back\n"
						:
						: "r" (value)
						: "memory");

	read_p15_c1 ();
}

/* read co-processor 15, register #2 (page table base) */
static unsigned long read_p15_c2 (void)
{
	unsigned long value;

	__asm__ __volatile__(
						"mrc	p15, 0, %0, c2, c0, 0   @ write table base\n"
						: "=r" (value)
						:
						: "memory");
	return value;
}

/* write to co-processor 15, register #2 (page table base) */
static void write_p15_c2 (unsigned long value)
{
	__asm__ __volatile__(
						"mcr	p15, 0, %0, c2, c0, 0   @ write table base\n"
						:
						: "r" (value)
						: "memory");

	read_p15_c2 ();
}

/* read co-processor 15, register #3 (domains) */
static unsigned long read_p15_c3 (void)
{
	unsigned long value;

	__asm__ __volatile__(
						"mrc	p15, 0, %0, c3, c0, 0   @ read domain reg\n"
						: "=r" (value)
						:
						: "memory");
	return value;
}

/* write to co-processor 15, register #3 (domains) */
static void write_p15_c3 (unsigned long value)
{
	__asm__ __volatile__(
						"mcr	p15, 0, %0, c3, c0, 0   @ write domain reg\n"
						:
						: "r" (value)
						: "memory");

	read_p15_c3 ();
}

static void cp_delay (void)
{
	volatile int i;

	/* Many OMAP regs need at least 2 nops  */
	for (i = 0; i < 100; i++);
}

/* See also ARM Ref. Man. */
#define C1_MMU		(1<<0)		/* mmu off/on */
#define C1_ALIGN	(1<<1)		/* alignment faults off/on */
#define C1_DC		(1<<2)		/* dcache off/on */
#define C1_WB		(1<<3)		/* merging write buffer on/off */
#define C1_BIG_ENDIAN	(1<<7)	/* big endian off/on */
#define C1_SYS_PROT	(1<<8)		/* system protection */
#define C1_ROM_PROT	(1<<9)		/* ROM protection */
#define C1_IC		(1<<12)		/* icache off/on */
#define C1_HIGH_VECTORS	(1<<13)	/* location of vectors: low/high addresses */
#define RESERVED_1	(0xf << 3)	/* must be 111b for R/W */

int cpu_init (void)
{
	/*
	 * setup up stacks if necessary
	 */
#ifdef CONFIG_USE_IRQ
	IRQ_STACK_START = _armboot_start - CFG_MALLOC_LEN - CFG_GBL_DATA_SIZE - 4;
	FIQ_STACK_START = IRQ_STACK_START - CONFIG_STACKSIZE_IRQ;
#endif
	return 0;
}

int cleanup_before_linux (void)
{
	/*
	 * this function is called just before we call linux
	 * it prepares the processor for linux
	 *
	 * we turn off caches etc ...
	 */

	unsigned long i;

	disable_interrupts ();

#ifdef CONFIG_LCD
	{
		extern void lcd_disable(void);
		extern void lcd_panel_disable(void);

		lcd_disable(); /* proper disable of lcd & panel */
		lcd_panel_disable();
	}
#endif

	/* turn off I/D-cache */
	asm ("mrc p15, 0, %0, c1, c0, 0":"=r" (i));
	i &= ~(C1_DC | C1_IC);
	asm ("mcr p15, 0, %0, c1, c0, 0": :"r" (i));

	/* flush I/D-cache */
	i = 0;
	asm ("mcr p15, 0, %0, c7, c7, 0": :"r" (i));  /* invalidate both caches and flush btb */
	asm ("mcr p15, 0, %0, c7, c10, 4": :"r" (i)); /* mem barrier to sync things */
	return(0);
}

int do_reset (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
#if defined( LSI_ARCH_APP3K ) || defined ( LSI_ARCH_APP3 )
    pll_reset( 0 );
#else
	disable_interrupts ();
	reset_cpu (0);
#endif
	/*NOTREACHED*/
	return(0);
}

/*
  ======================================================================
  ======================================================================
  MMU and Caches
  ======================================================================
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  map_section
*/

static void map_section( unsigned long physical, unsigned long virtual,
                         unsigned long bits )
{

  unsigned long index_;
  unsigned long descriptor_;
  unsigned long * page_table = ( unsigned long * ) PAGE_TABLE_ADDRESS;

  index_ = ( virtual & ~ 0x00030000 ) >> 18; /* Index in the page table */
  descriptor_ = physical & ~ 0xfffff; /* Set the descriptor */
  descriptor_ |= bits & 0xfffff;
  page_table [ index_ / 4 ] = descriptor_; /* Write the descriptor */

  return;

}

/*
  ----------------------------------------------------------------------
  map_identity
*/

static void map_identity( void )
{

  unsigned long address_;
  unsigned long bits_;
  int index_ = 0;

  address_ = 0;
  bits_ = 0xc0e;

  while( 64 > index_ ) {

    map_section( address_, address_, bits_ );
    address_ += 0x100000;
    ++ index_;

  }

  bits_ = 0xc02;

  while( 4096 > index_ ) {

    map_section( address_, address_, bits_ );
    address_ += 0x100000;
    ++ index_;

  }

}

void dcache_enable (void)
{

  unsigned long c1;
  unsigned long page_table = ( unsigned long ) PAGE_TABLE_ADDRESS;

  printf( "Enabling the data cache\n" );
  c1 = read_p15_c1( );          /* Disable the MMU */
  c1 &= ~ 0x1;
  write_p15_c1( c1 );
  write_p15_c2( page_table );   /* Set the Page Table Base */
  write_p15_c3( 0xffffffff );   /* Set all Domains to Full Access */
  map_identity( );              /* Set up the MMU */
  c1 = read_p15_c1( );          /* Enable the MMU and Data Cache */
  c1 |= 0x5;
  write_p15_c1( c1 );

  return;

}

void dcache_disable (void)
{

  unsigned long value;

  value = 0;
  asm( "mcr p15, 0, %0, c7, c14, 0" : : "r" (value ) );
  asm( "mcr p15, 0, %0, c7, c5, 0" : : "r" (value ) );
  asm( "mcr p15, 0, %0, c7, c15, 0" : : "r" (value ) );
  value = read_p15_c1( );
  value &= ~ 0x4;
  write_p15_c1( value );
  value &= ~ 0x1;
  write_p15_c1( value );
  value = 0;
  asm( "mcr p15, 0, %0, c7, c7, 0" : : "r" ( value ) );
  asm( "mcr p15, 0, %0, c7, c10, 4" : : "r" ( value ) );
  return;

}

int dcache_status (void)
{
        return (read_p15_c1 () & C1_DC) != 0;
}

void icache_enable (void)
{
	ulong reg;

	reg = read_p15_c1 ();	/* get control reg. */
	cp_delay ();
	write_p15_c1 (reg | C1_IC);
}

void icache_disable (void)
{
	ulong reg;

	reg = read_p15_c1 ();
	cp_delay ();
	write_p15_c1 (reg & ~C1_IC);
}

int icache_status (void)
{
	return(read_p15_c1 () & C1_IC) != 0;
}
