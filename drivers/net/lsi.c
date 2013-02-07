/*
 *  drivers/net/lsi.c
 *
 *  Copyright (C) 2009 LSI (john.jacques@lsi.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <config.h>
#ifdef CONFIG_LSI_NET
#ifndef NCR_TRACER
#include <common.h>
#include <net.h>

unsigned char ethernet_address[6];

/*
  ===============================================================================
  ===============================================================================
  Private Interface
  ===============================================================================
  ===============================================================================
*/

static int initialized = 0;
static int femac;

#if defined(CONFIG_ACP2)
static int
_eth_init(bd_t *bd)
{
	return lsi_femac_eth_init(bd);
}

static void
_eth_halt(void)
{
	lsi_femac_eth_halt();

	return;
}
#elif defined(CONFIG_ACP3)
static void
update_femac(void)
{
	char *ethmode = NULL;

	ethmode = getenv("ethmode");

	if ((NULL != ethmode) &&
	    (0 == strncmp(ethmode, "eioa", strlen("eioa")))) {
		femac = 0;
	} else {
		femac = 1;
	}

	return;
}

static int
_eth_init(bd_t *bd)
{
	int rc;

	update_femac();

	if (0 != femac)
		rc = lsi_femac_eth_init(bd);
	else
		rc = acp_eioa_eth_init(bd);

	return rc;
}

static void
_eth_halt(void)
{
	if (0 != femac)
		lsi_femac_eth_halt();
	else
		acp_eioa_eth_halt();

	return;
}
#endif

static int
get_ethernet_address(bd_t *bd)
{
	int i;
	char *ethaddr = NULL;
	char *endp;

	ethaddr = getenv("ethaddr");

	if (NULL == ethaddr) {
		ERROR_PRINT("ethaddr is not set.\n");
		return -1;
	}

	for (i = 0; i < 6; ++i) {
		ethernet_address[i] = simple_strtoul(ethaddr, &endp, 16);

		if (endp == ethaddr) {
			ERROR_PRINT("Error parsing ethaddr.\n");
			return -1;
		}

		if (0 != *endp)
			ethaddr = (endp + 1);
	}

	DEBUG_PRINT("Ethernet Address : %02x:%02x:%02x:%02x:%02x:%02x\n",
		    ethernet_address[0], ethernet_address[1],
		    ethernet_address[2], ethernet_address[3],
		    ethernet_address[4], ethernet_address[5]);

	for (i = 0; i < 6; ++i)
		bd->bi_enetaddr[i] = ethernet_address[i];

	return 0;
}

/*
  ===============================================================================
  ===============================================================================
  Public Interface
  ===============================================================================
  ===============================================================================
*/

/*
  ----------------------------------------------------------------------
  dump_packet
*/

#ifdef CONFIG_ACP3

int dumprx = 0;
int dumptx = 0;

void
dump_packet(const char *header, void *packet, int length)
{
	int i;
	unsigned char *input = packet;

	printf("---------- %s (%d bytes)----------\n", header, length);

	for (i = 0; i < (length / 2); ) {
		int j;
		unsigned short *data;

		data = &(((unsigned short *)packet)[i]);

		for (j = 0; j < 8; ++j, ++i) {
			printf("%04x ", htons(data[j]));
		}

		puts("\n");
	}

	puts("--------------------\n");
}

#endif

/*
  ----------------------------------------------------------------------
  eth_init
*/

int
eth_init(bd_t *bd)
{
	int rc;

	DEBUG_PRINT("\n");

	/* If already initialized, halt an do it again.	*/
	if (0 != initialized)
		eth_halt();

	/* Get the Ethernet address from the environment. */
	if (0 != get_ethernet_address(bd))
		return -1;

	/* Call the appropriate eth_init. */
	rc = _eth_init(bd);

	/* Change the state to "initialized" if successful. */
	if (0 == rc)
		initialized = 1;

	return rc;
}

/*
  -------------------------------------------------------------------------------
  eth_halt
*/

void
eth_halt(void)
{
	DEBUG_PRINT("\n");

#if defined(CONFIG_ACP2)
	if (0 != initialized)
		lsi_femac_eth_halt();
#else
	if (0 != initialized) {
		if (0 != femac)
			lsi_femac_eth_halt();
		else
			acp_eioa_eth_halt();
	}
#endif

	return;
}

/*
  -------------------------------------------------------------------------------
  eth_send
*/

int
eth_send(volatile void *packet, int length)
{
	DEBUG_PRINT("\n");

	if (0 == initialized) {
		ERROR_PRINT("Networking Isn't Initialized!\n");
		return 0;
	}

#if defined(CONFIG_ACP2)
	return lsi_femac_eth_send(packet, length);
#else
	if (0 != femac)
		return lsi_femac_eth_send(packet, length);
	else
		return acp_eioa_eth_send(packet, length);
#endif
}

/*
  -------------------------------------------------------------------------------
  eth_rx
*/

int
eth_rx(void)
{
	DEBUG_PRINT("\n");

	if (0 == initialized) {
		ERROR_PRINT("Networking Isn't Initialized!\n");
		return 0;
	}

#if defined(CONFIG_ACP2)
	return lsi_femac_eth_rx();
#else
	if (0 != femac)
		return lsi_femac_eth_rx();
	else
		return acp_eioa_eth_rx();
#endif
}

/*
  -------------------------------------------------------------------------------
  eth_getenv_enetaddrg
*/

void
eth_getenv_enetaddrg(const char *name, unsigned char enetaddr[6])
{
	memcpy(enetaddr, ethernet_address, (sizeof(unsigned char) * 6));

	return 0;
}

#if !defined(CONFIG_ACP2)

/*
  -------------------------------------------------------------------------------
  lsi_net_receive_test
*/

void
lsi_net_receive_test(void)
{
	update_femac();

	if (0 != femac)
		lsi_femac_receive_test();
	else
		acp_eioa_receive_test();
}

/*
  -------------------------------------------------------------------------------
  lsi_net_loopback_test
*/

void
lsi_net_loopback_test(void)
{
	update_femac();

	if (0 != femac)
		lsi_femac_loopback_test();
	else
		acp_eioa_loopback_test();
}

#endif

/*
  ------------------------------------------------------------------------------
  board_eth_init

  This will get called by 
*/

int
board_eth_init(bd_t *bis)
{
	printf("%s:%d - LSI Ethernet Driver Initialization.\n",
	       __FILE__, __LINE__); /* ZZZ */

	return 0;
}

#endif /* NCR_TRACER */
#endif /* CONFIG_LSI_NET */
