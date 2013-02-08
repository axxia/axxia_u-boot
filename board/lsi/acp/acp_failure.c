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

  Called when there is a controlled failure (no exception) in software that
  requires a system reset.
*/

void
acp_failure(const char *file, const char *function, const int line)
{
	if (1 != console_not_available)
		printf("\n%s:%s:%d - System Failure\n", file, function, line);

#ifndef DISABLE_RESET
	acp_reset(0, NULL);
#endif

	while (1)
		;

	return;
}

/*
  -------------------------------------------------------------------------------
  acp_failure_exception

  Called for all unhandled exceptions except machine check.
*/

void
acp_failure_exception(unsigned long exception_number,
		      unsigned long original_lr)
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

	/*
	  N.B. Critical Input, Watchdog, and Debug are "critical"
	  exceptions, and use different sprs.
	*/

	if (1 != console_not_available) {
		unsigned long core;
		unsigned long srr0_value;
		unsigned long srr1_value;
		unsigned long esr_value;

		__asm__ __volatile__ ("mfspr %0,0x11e" : "=r" (core));
		__asm__ __volatile__ ("mfspr %0,0x03e" : "=r" (esr_value));

		if (0 == exception_number ||
		    12 == exception_number ||
		    15 == exception_number) {
			__asm__ __volatile__ ("mfspr %0,0x3a" :
					      "=r" (srr0_value));
			__asm__ __volatile__ ("mfspr %0,0x3b" :
					      "=r" (srr1_value));
		} else {
			__asm__ __volatile__ ("mfspr %0,0x1a" :
					      "=r" (srr0_value));
			__asm__ __volatile__ ("mfspr %0,0x1b" :
					      "=r" (srr1_value));
		}

		printf("\n"
		       "Unhandled Exception (%s)\n"
		       "CORE=%lu (C)SRR0=0x%08lx SRR1=0x%08lx LR=0x%08lx\n"
		       "ESR=0x%08lx\n"
		       "Board Reset Required!\n",
		       exception_names[exception_number],
		       core, srr0_value, srr1_value, original_lr,
		       esr_value);
	}

#ifdef CONFIG_ACP2
	if (0 != reset_enabled)
#endif
		acp_reset(0, NULL);

	while (1)
		;

	return;
}

/*
  -------------------------------------------------------------------------------
  acp_failure_machine_check

  Called for machine check exceptions.
*/

void
acp_failure_machine_check(unsigned long original_lr)
{
	if (1 != console_not_available) {
		unsigned long core;
		unsigned long mcsrr0_value;
		unsigned long mcsrr1_value;
		unsigned long esr_value;
		unsigned long mcsr_value;

		__asm__ __volatile__ ("mfspr %0,0x11e" : "=r" (core));
		__asm__ __volatile__ ("mfspr %0,0x23a" : "=r" (mcsrr0_value));
		__asm__ __volatile__ ("mfspr %0,0x23b" : "=r" (mcsrr1_value));
		__asm__ __volatile__ ("mfspr %0,0x03e" : "=r" (esr_value));
		__asm__ __volatile__ ("mfspr %0,0x23c" : "=r" (mcsr_value));

		printf("\n"
		       "Machine Check\n"
		       "CORE=%lu MCSRR0=0x%08lx MCSRR1=0x%08lx LR=0x%08lx\n"
		       "ESR=0x%08lx MCSR=0x%08lx\n"
		       "Board Reset Required!\n",
		       core, mcsrr0_value, mcsrr1_value, original_lr,
		       esr_value, mcsr_value);
	}

#ifdef CONFIG_ACP2
	if (0 != reset_enabled)
#endif
		acp_reset(0, NULL);

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
