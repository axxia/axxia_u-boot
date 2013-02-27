/*
 * (C) Copyright 2002
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
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

MEMORY { .lsm : ORIGIN = 0xf0a00000, LENGTH = 0x020000 }

MEMORY { .sys : ORIGIN = 0x00000000, LENGTH = 0x400000 }

OUTPUT_ARCH(powerpc)

SECTIONS
{
	.resetvec 0xf0a00000 :
	{
		KEEP(*(.resetvec))
	} = 0xffff

	.bootpg 0xf0a00010 :
	{
		arch/powerpc/cpu/ppc4xx/start.o	(.bootpg)
	} = 0xfffff

	.text :
	{
		arch/powerpc/cpu/ppc4xx/start.o	(.text)
		*(.text*)
	} > .lsm

	__start___ex_table = .;
	__ex_table :
	{
		*(__ex_table)
	}
	__stop___ex_table = .;

	.data :
	{
		*(.rodata*)
		*(.sdata*)
		*(.data*)
	} > .lsm

	.got2 :
	{
		*(.got2*)
	} > .lsm

	.fixup :
	{
		*(.fixup)
	} > .lsm

	.eh_frame :
	{
		*(.eh_frame)
	} > .lsm

	.u_boot_list :
	{
		#include "u-boot.lst"
	} > .lsm

	.brs 0xf0a1fc00 :
	{
		*(.brs)
	}

	.brs_vector 0xf0a1fffc :
	{
		KEEP(*(.brs_vector))
	}

	PROVIDE(_bss_start = .);
	.bss (NOLOAD):
	{
		*(.bss*)
		*(.sbss*)
	}
	. = ALIGN(256);
	PROVIDE(_bss_end = . );
}
