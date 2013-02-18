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
	
	.brs :
	{
		*(.brs*)
	} > .lsm

	.text :
	{
		*(.text*)
	} > .lsm

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

	.bootpg :
	{
		*(.bootpg)
	} >.lsm

	.resetvec :
	{
		*(.resetvec)
	} > .lsm

	.fixup :
	{
		*(.fixup)
	} > .lsm

	.eh_frame :
	{
		*(.eh_frame)
	} > .lsm

	.bss :
	{
		*(.bss*)
		*(.sbss*)
	} > .lsm

	.u_boot_list :
	{
		#include "u-boot.lst"
	} > .lsm
}
