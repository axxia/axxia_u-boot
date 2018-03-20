/*
 *  drivers/net/axxia.c
 *
 *  Copyright (C) 2009 LSI (john.jacques@lsi.com)
 *
 * This program is free software;you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation;either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY;without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program;if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*#define DEBUG*/
#include <config.h>
#include <common.h>
#include <malloc.h>
#include <net.h>

unsigned char ethernet_address[6];
int dumprx = 0;
int dumptx = 0;
bool pong = false;

int axxia_mdio_init(void);
int nemac_initialize(bd_t *);

/*
  ===============================================================================
  ===============================================================================
  Private Interface
  ===============================================================================
  ===============================================================================
*/

/*
  ===============================================================================
  ===============================================================================
  Public Interface
  ===============================================================================
  ===============================================================================
*/

/*
  ----------------------------------------------------------------------
  axxia_dump_packet

  The format is so you can import to WireShark...
*/

void
axxia_dump_packet(const char *header, void *packet, int length)
{
	char buffer[256];
	char *string;
	unsigned long offset = 0;
	int i;
	unsigned char *data = packet;

	if (NULL != header)
		printf("---- %s ----\n", header);

	while (0 < length) {
		int this_line;

		string = buffer;
		string += sprintf(string, "%06lx ", offset);
		this_line = (16 > length) ? length : 16;

		for (i = 0;i < this_line;++i) {
			string += sprintf(string, "%02x ", *data++);
			--length;
			++offset;
		}

		printf("%s\n", buffer);
	}

	printf("\n");
}

/*
  -------------------------------------------------------------------------------
  axxia_dump_packet_rx
*/

void
axxia_dump_packet_rx(const char *header, void *packet, int length)
{
	if (0 != dumprx)
		axxia_dump_packet(header, packet, length);

	return;
}

/*
  -------------------------------------------------------------------------------
  axxia_dump_packet_tx
*/

void
axxia_dump_packet_tx(const char *header, void *packet, int length)
{
	if (0 != dumptx)
		axxia_dump_packet(header, packet, length);

	return;
}

/*
  ------------------------------------------------------------------------------
  board_eth_init
*/

int
board_eth_init(bd_t *bd)
{
	axxia_mdio_init();

#if defined(CONFIG_AXXIA_NEMAC)
	if (nemac_initialize(bd) != 0) {
		puts("Failed to add NEMAC device.\n");
	}
#endif

#if defined(CONFIG_AXXIA_FEMAC)

	debug("Adding LSI_FEMAC device\n");

	/*
	  Get the Ethernet address from the environment.
	*/

	if (eth_getenv_enetaddr("ethaddr", ethernet_address)) {
		struct eth_device *device;

		/*
		  Allocate a device structure and clear it.
		*/

		device = (struct eth_device *)malloc(sizeof(struct eth_device));

		if (NULL == device) {
			printf("Unable to allocate memory for LSI_FEMAC eth_device.\n");
			return -1;
		}

		memset((void *)device, 0, sizeof(struct eth_device *));
		memcpy(device->enetaddr, ethernet_address, (sizeof(unsigned char) * 6));

		/*
		  Set up the rest of the eth_device structure and register it.
		*/

		sprintf(device->name, "LSI_FEMAC");
		device->init         = lsi_femac_eth_init;
		device->halt         = lsi_femac_eth_halt;
		device->send         = lsi_femac_eth_send;
		device->recv         = lsi_femac_eth_rx;
		device->write_hwaddr = lsi_femac_write_hwaddr;

		eth_register(device);
	} else {
		/* returns is_valid... 1=true, 0=false */
		printf("Failed to add LSI_FEMAC device. Error getting ethaddr.\n");
	}
#endif

#if defined(CONFIG_AXXIA_EIOA)
{
	struct eth_device *device;
	debug("Adding LSI_EIOA device\n");

	/*
	  Get the Ethernet address from the environment.
	  Try first eth1addr. If doesn't exist than from ethaddr.
	*/
	if (!eth_getenv_enetaddr("eth1addr", ethernet_address))
		if (!eth_getenv_enetaddr("ethaddr", ethernet_address)) {
			/* returns is_valid... 1=true, 0=false */
			printf("Failed to add LSI_EIOA device."
			       " Error getting eth1addr nor ethaddr.\n");
			return -1;
		}


	/*
	  Allocate a device structure and clear it.
	*/

	device = (struct eth_device *)malloc(sizeof(struct eth_device));

	if (NULL == device) {
		printf("Unable to allocate memory for LSI_EIOA eth_device.\n");
		return -1;
	}

	memset((void *)device, 0, sizeof(struct eth_device *));
	memcpy(device->enetaddr, ethernet_address, (sizeof(unsigned char) * 6));

	/*
	  Set up the rest of the eth_device structure and register it.
	*/

	sprintf(device->name, "LSI_EIOA");
	device->init         = lsi_eioa_eth_init;
	device->halt         = lsi_eioa_eth_halt;
	device->send         = lsi_eioa_eth_send;
	device->recv         = lsi_eioa_eth_rx;
	device->write_hwaddr = NULL;

	eth_register(device);
}
#endif

#if !defined(CONFIG_AXXIA_EIOA) && !defined(CONFIG_AXXIA_FEMAC) && !defined(CONFIG_AXXIA_NEMAC)
#error "Axxia networking is defined, but no interface has been!"
#endif

	return 0;
}

void lsi_net_receive_test(struct eth_device *dev)
{
	char *act = getenv("ethact");

	/* set current device to whats in ethact */
	eth_set_current();

	if(act) {
		if(strcmp(act, "LSI_FEMAC") == 0) {
#ifdef CONFIG_AXXIA_FEMAC
			lsi_femac_receive_test(dev);
#endif
		} else if(strcmp(act, "LSI_EIOA") == 0) {
#ifdef CONFIG_AXXIA_EIOA
			lsi_eioa_receive_test(dev);
#endif
		}
	}
}

#include <watchdog.h>
void lsi_net_pong_test(struct eth_device *dev)
{
	char *act = getenv("ethact");

	/* set current device to whats in ethact */
	eth_set_current();

	if (!act)
		return;

	if ( (0 == strncmp(act, "LSI_EIOA", 8)) ||
	     (0 == strncmp(act, "NEMAC", 5)) )
	{
		printf("Run ICMP ECHO Reply in response to ping"
		       " -- Ctrl-C to Exit.\n");
		printf("Listening on %s %s\n",
			act, strncmp(act,"LSI_EIOA",8) ? "" : getenv("gmacport"));

		pong = true;

		eth_halt();

		if (0 != eth_init()) {
			pong = false;
			eth_halt();
			return;
		}

		for (;;) {
			WATCHDOG_RESET();
			eth_rx(); /*just listen to all the traffic.
				    Processing of ECHO Reply alreadu sits in
				    eth_rx()/net_process_received_packet() */
			if (ctrlc())
				break;
		}

		pong = false;
		eth_halt();
	}
	return;
}

void lsi_net_loopback_test(struct eth_device *dev, int type)
{
	char *act = getenv("ethact");

	/* set current device to whats in ethact */
	eth_set_current();

	if(act) {
		if(strcmp(act, "LSI_FEMAC") == 0) {
#ifdef CONFIG_AXXIA_FEMAC
			lsi_femac_loopback_test(dev, type);
#endif
		} else if(strcmp(act, "LSI_EIOA") == 0) {
#ifdef CONFIG_AXXIA_EIOA
			lsi_eioa_loopback_test(dev);
#endif
		}
	}
}
