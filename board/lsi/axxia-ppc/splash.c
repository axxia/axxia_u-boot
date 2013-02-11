/*
 * ssp.c
 *
 * Simple driver for the SSP controller in LSI's ACP.
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

#include <config.h>

#ifdef CONFIG_ACP

#if defined( CONFIG_ACP2 )

char * splash_string = \
"     __    _   _  __   _         __          __                     \n" \
" /  (  /  /_| / )/__)  _)   _/  ( _/_ _ _   / _)   _/  /    _ _/_ _ \n" \
"(____)(  (  |(__/     /__/)(/  __)/(/(/(-  /(_)()()/  (__()(/(/(-/  \n" \
"                                    _/                              \n";

#elif defined( CONFIG_ACP3 )

static char * splash_string = \
"     __    _   _  __   _         __          __                     \n" \
" /  (  /  /_| / )/__)  _) _ _/  ( _/_ _ _   / _)   _/  /    _ _/_ _ \n" \
"(____)(  (  |(__/     __)/ (/  __)/(/(/(-  /(_)()()/  (__()(/(/(-/  \n" \
"                                    _/                              \n";

#else
#error "No Board Type Defined!"
#endif

/*
  ----------------------------------------------------------------------
  acp_splash
*/

void
acp_splash( void )
{
	printf( "\n%s\n", splash_string );

	return;
}

#endif /* CONFIG_ACP */
