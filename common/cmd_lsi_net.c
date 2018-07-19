/*
 * common/cmd_lsi_net.c
 *
 * (C) Copyright 2009
 * LSI, john.jacques@lsi.com
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

#ifndef CONFIG_SPL_BUILD

#include <config.h>
#include <common.h>
#include <exports.h>
#include <command.h>

DECLARE_GLOBAL_DATA_PTR;

extern int dumprx;
extern int dumptx;

/*
  ======================================================================
  Local Stuff
*/

/*
  ----------------------------------------------------------------------
  do_net
*/

int
do_net(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	if( 0 == strncmp( argv[1], "dr", strlen( "dr" ) ) ) {
		dumprx = dumprx ? 0 : 1;
		printf("Dump receive packets %s\n", dumprx ? "On" : "Off");

		return 0;
	}

	if( 0 == strncmp( argv[1], "dt", strlen( "dt" ) ) ) {
		dumptx = dumptx ? 0 : 1;
		printf("Dump transmit packets %s\n", dumptx ? "On" : "Off");

		return 0;
	}

	if( 0 == strncmp( argv[1], "l", strlen( "l" ) ) ) {
		int test = 0;

		if (3 == argc) {
			if (0 == strncmp(argv[2], "n", strlen("n"))) {
				test = 1;
			} else if (0 == strncmp(argv[2], "p", strlen("p"))) {
				test = 2;
			} else {
				printf("Unknow Loopback Type!\n");
				return -1;
			}
		}

		printf("Starting Loopback Test -- Ctrl-C to Exit.\n");
		lsi_net_loopback_test(eth_get_dev(), test);

		return 0;
	}

	if( 0 == strncmp(argv[1], "p" , strlen("p") ) ) {
		lsi_net_pong_test(eth_get_dev());

		return 0;
	}

	if( 0 == strncmp( argv[1], "r", strlen( "r" ) ) ) {
		printf( "Receiving Packets -- Ctrl-C to Exit.\n" );
		lsi_net_receive_test(eth_get_dev());

		return 0;
	}

	if( 0 == strncmp( argv[1], "s", strlen( "s" ) ) ) {
		char * buffer = malloc( 60 );

		if( ( char * ) 0 == buffer ) {
			printf( "malloc() failed!\n" );
			printf( "%s", cmdtp->usage);

			return -1;
		} else {
			/* Copy Uboot to buffer */
			memmove(buffer, 0, 60);
			printf( "Sending Packet...\n" );
			eth_init( );
			eth_send( ( void * ) buffer, 60 );
			eth_halt( );
			free( buffer );

			return 0;
		}
	}

	printf( "%s", cmdtp->usage );

	return -1;
}

extern int take_snapshot(void);
extern ncp_st_t tx_rx_task(void);


#define DEBUG
#include <config.h>

#ifdef CONFIG_AXXIA_XLF
int
do_net_macstats(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	take_snapshot();

	return CMD_RET_SUCCESS;
}
#endif	/* CONFIG_AXXIA_XLF */

int
do_bu(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned magic = 0x27051956;  /* Image Magic Number*/
	unsigned word0 = 0x1400000a;
	unsigned *ih = (unsigned*)(volatile unsigned long)0;
	unsigned ih_magic = be32_to_cpu(*ih);
	unsigned ih_size = be32_to_cpu(*(ih+3)); /* Image Data Size */

	if (magic == ih_magic) {
		printf("Found U-Boot mkimage'd.");
		memmove((void*)0, (void*)0x40, ih_size);
	} else if (*ih == word0) {
		printf("Found U-Boot binary.");
	} else {
		printf("Not U-Boot. Giving up\n");
		return CMD_RET_FAILURE;
	}

	printf(" Booting...\n");

	void (*entry)(void*, void*) = (void(*)(void*,void*)) 0;
	cleanup_before_linux();
	entry(NULL, NULL);

	return CMD_RET_FAILURE;
}

/*
  ======================================================================
  Command Definitions
  ======================================================================
*/

U_BOOT_CMD(net, 3, 0, do_net,
	   "net loopback|receive|send|pong|dr|dt [type]\n",
	   "l,oopback loop all received packets back, specify the type\n"
	   "     net -- loop packets from the network back out\n"
	   "     phy -- expect the phy to loop packets back\n"
	   "            Remeber to put the PHY in loopback mode!\n"
	   "r,ecevie packets, and dump them to the screen\n"
	   "s,end send one packet\n"
	   "p,ing receive ICMP Request and Reply\n"
	   "dr toggle the \"dumprx\" flag\n"
	   "dt toggle the \"dumptx\" flag\n");

U_BOOT_CMD(bu, 1, 1, do_bu,
	   "boot U-Boot from address 0",
	   "");

#ifdef CONFIG_AXXIA_XLF
U_BOOT_CMD(macstats, 1, 0, do_net_macstats,
	   "run gmac counter stats", 
	   "");
#endif	/* CONFIG_AXXIA_XLF */

#endif /* CONFIG_SPL_BUILD */
