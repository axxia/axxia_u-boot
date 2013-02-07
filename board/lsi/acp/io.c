/*
 * io.c
 *
 * IO routines for LSI's ACP.
 *
 * Copyright (C) 2009 LSI Corporation
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#ifdef CONFIG_ACP
#include <asm/io.h>

int lsi_debug_enable = 1;
int lsi_logio_enable = 1;

unsigned long
acpreadio( const volatile unsigned long * address )
{
        unsigned value;

        __asm__ __volatile__( "sync; \n"
			      "lwbrx %0,0,%1;\n"
			      "twi 0,%0,0;\n"
			      "isync"
			      : "=r" ( value )
			      : "r" ( address ), "m" ( * address ) );

        return value;
}

void
acpwriteio( unsigned long value, volatile unsigned long * address )
{
        __asm__ __volatile__( "sync; \n"
			      "stwbrx %1,0,%2;\n"
			      : "=m" ( * address )
			      : "r" ( value ), "r" ( address ) );
	__asm__ __volatile__ ( "sync" : : : "memory" );
	eieio( );
}

#endif /* CONFIG_ACP */
