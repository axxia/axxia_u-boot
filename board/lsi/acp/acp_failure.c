/*
 *  Copyright (C) 2009 LSI Corporation
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

static int console_not_available = 1;

/*
  -------------------------------------------------------------------------------
  acp_failure
*/

void
acp_failure(const char *file, const char *function, const int line)
{
	if (1 != console_not_available)
		printf( "\n%s:%s:%d - System Failure", file, function, line );

	do_reset(NULL, 0, 0, NULL);

	while (1)
		;

	return;
}

/*
  -------------------------------------------------------------------------------
  acp_failure_exception
*/

void
acp_failure_exception(unsigned long exception_number,
		      unsigned long srr0_value, unsigned long lr_value)
{
	char *exception_names[] = {
		"Critical Input",
		"Machine Check",
		"Data Storage",
		"Instruction Storage",
		"External Input",
		"Alignment",
		"Program",
		"FP Unavailable",
		"System Call",
		"AP Unavailable",
		"Decrementer",
		"FIT",
		"Watchdog",
		"Data TLB Miss",
		"Instruction TLB Miss",
		"Debug"
	};

	if (1 != console_not_available) {
		unsigned long core;
		unsigned long sp;

		__asm__ __volatile__ ("mfspr %0,0x11e" : "=r" (core));
		__asm__ __volatile__ ("mr %0,1" : "=r" (sp));
		printf("\n"
		       "Unhandled Exception (%s)\n"
		       "CORE=%d SRR0=0x%08lx LR=0x%08lx SP=0x%08lx\n"
		       "Board Reset Required!\n",
		       exception_names[exception_number],
		       core, srr0_value, lr_value, sp);
	}

	do_reset(NULL, 0, 0, NULL);

	while (1)
		;

	return;
}

/*
  -------------------------------------------------------------------------------
  acp_failure_enable_console
*/

void
acp_failure_enable_console(void)
{
	console_not_available = 0;
}

/*
  -------------------------------------------------------------------------------
  acp_failure_disable_console
*/

void
acp_failure_disable_console(void)
{
	console_not_available = 1;
}
