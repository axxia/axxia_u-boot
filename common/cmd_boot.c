/*
 * (C) Copyright 2000-2003
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

/*
 * Misc boot support
 */
#include <common.h>
#include <command.h>
#include <net.h>
#include <asm/processor.h>
#include <asm/io.h>

#ifdef CONFIG_CMD_GO

/* Allow ports to override the default behavior */
__attribute__((weak))
unsigned long do_go_exec (ulong (*entry)(int, char * const []), int argc, char * const argv[])
{
#ifdef CONFIG_ACP3
	{
		unsigned long core;
		unsigned long os_base;
		char * envstring;
		int os_access_enabled = 0;
		char * ccr0_env;
		char * ccr1_env;
		char * ccr2_env;
		unsigned long ccr0_val;
		unsigned long ccr1_val;
		unsigned long ccr2_val;
		char buffer [ 80 ];
		unsigned long ppc_clock;

		envstring = getenv("os_access");

		if ((NULL != envstring) && (0 == strcmp("on", envstring))) {
			os_access_enabled = 1;
		}

		disable_interrupts( );

		if (0 != os_access_enabled)
			os_access_init( );

		ose_init( );
		os_base = (acp_osg_group_get_res(0, ACP_OS_BASE) *
			   1024 * 1024);
		sprintf( buffer, "valid=1" );
		ose_add_string( 0, buffer );

		if (0 != os_access_enabled) {
			sprintf( buffer, "nand_access_base=0x%lx",
				 ( unsigned long ) os_access_get_address( ) );
			ose_add_string( 0, buffer );
		}

		sprintf( buffer, "spintable_0=0x%lx",
			 ( unsigned long ) 
			 & ( ( acp_spintable [ 0 ] )->entry_address ) );
		ose_add_string( 0, buffer );
		sprintf( buffer, "spintable_1=0x%lx",
			 ( unsigned long )
			 & ( ( acp_spintable [ 1 ] )->entry_address ) );
		ose_add_string( 0, buffer );
#ifndef CONFIG_ACP_342X
		sprintf( buffer, "spintable_2=0x%lx",
			 ( unsigned long )
			 & ( ( acp_spintable [ 2 ] )->entry_address ) );
		ose_add_string( 0, buffer );
		sprintf( buffer, "spintable_3=0x%lx",
			 ( unsigned long )
			 & ( ( acp_spintable [ 3 ] )->entry_address ) );
#endif
		ose_add_string( 0, buffer );
		sprintf( buffer, "serclk0=%u", UART_CLOCK_SPEED);
		ose_add_string( 0, buffer );
		sprintf( buffer, "serclk1=%u", UART_CLOCK_SPEED);
		ose_add_string( 0, buffer );
		if( 0 == acp_clock_get( ppc, & ppc_clock ) ) {
			sprintf( buffer, "coreclk=%lu", ( ppc_clock * 1000 ) );
			ose_add_string( 0, buffer );
		} else {
			printf( "Error Getting PPC Clock!\n" );
		}

		envstring = getenv("ethaddr");

		if (NULL == envstring) {
			printf("ethaddr is NOT available!\n");
		} else {
			sprintf( buffer, "ethaddr=%s", envstring );
			ose_add_string( 0, buffer);
		}

		envstring = getenv("baudrate");

		if (NULL == envstring) {
			printf("baudrate is NOT available!\n");
		} else {
			sprintf( buffer, "baudrate=%s", envstring );
			ose_add_string( 0, buffer);
		}

		if( NULL != ( ccr0_env = getenv( "ccr0" ) ) ) {
			ccr0_val = simple_strtoul( ccr0_env, NULL, 16 );
		} else {
			ccr0_val = CCR0_DEFAULT;
		}

		if( NULL != ( ccr1_env = getenv( "ccr1" ) ) ) {
			ccr1_val = simple_strtoul( ccr1_env, NULL, 16 );
		} else {
			ccr1_val = CCR1_DEFAULT;
		}

		if( NULL != ( ccr2_env = getenv( "ccr2" ) ) ) {
			ccr2_val = simple_strtoul( ccr2_env, NULL, 16 );
		} else {
			ccr2_val = CCR2_DEFAULT;
		}

		printf( "CCR0=0x%08lx CCR1=0x%08lx CCR2=0x%08lx\n",
			ccr0_val, ccr1_val, ccr2_val );

		for( core = 1; core < ACP_NR_CORES; ++ core ) {
			( acp_spintable [ core ] )->ccr0_value = ccr0_val;
			( acp_spintable [ core ] )->ccr1_value = ccr1_val;
			( acp_spintable [ core ] )->ccr2_value = ccr2_val;
		}

		mtspr( ccr0, ccr0_val );
		mtspr( ccr1, ccr1_val );
		mtspr( ccr2, ccr2_val );
		isync( );
	}

	acp_unlock_stage3();

#endif /* CONFIG_ACP3 */

	return entry (argc, argv);
}

int do_go (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	ulong	addr, rc;
	int     rcode = 0;

	if (argc < 2)
		return CMD_RET_USAGE;

	addr = simple_strtoul(argv[1], NULL, 16);

	printf ("## Starting application at 0x%08lX ...\n", addr);

	/*
	 * pass address parameter as argv[0] (aka command name),
	 * and all remaining args
	 */
	rc = do_go_exec ((void *)addr, argc - 1, argv + 1);
	if (rc != 0) rcode = 1;

	printf ("## Application terminated, rc = 0x%lX\n", rc);
	return rcode;
}

/* -------------------------------------------------------------------- */

U_BOOT_CMD(
	go, CONFIG_SYS_MAXARGS, 1,	do_go,
	"start application at address 'addr'",
	"addr [arg ...]\n    - start application at address 'addr'\n"
	"      passing 'arg' as arguments"
);

#endif

U_BOOT_CMD(
	reset, 2, 0,	do_reset,
	"Perform RESET of the CPU",
	""
);
