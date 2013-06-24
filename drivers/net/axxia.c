/*
 *  drivers/net/axxia.c
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
#include <common.h>
#include <malloc.h>
#include <net.h>

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

	printf("---- %s\n", header);

	while (0 < length) {
		int this_line;

		string = buffer;
		string += sprintf(string, "%06lx ", offset);
		this_line = (16 > length) ? length : 16;

		for (i = 0; i < this_line; ++i) {
			string += sprintf(string, "%02x ", *data++);
			--length;
			++offset;
		}

		printf("%s\n", buffer);
	}

	printf("\n");
}

/*
  ------------------------------------------------------------------------------
  board_eth_init
*/

int
board_eth_init(bd_t *bd)
{
	int rc;
	unsigned char enetaddr[6];
	struct eth_device *device;

	/*
	  Get the Ethernet address from the environment.
	*/

	rc = eth_getenv_enetaddr("ethaddr", enetaddr);

	if (0 == rc) {		/* returns is_valid... 1=true, 0=false */
		printf("Error getting Ethernet address.\n");
		return -1;
	}

#if defined(CONFIG_AXXIA_FEMAC)
	/*
	  Allocate a device structure and clear it.
	*/
 
	device = (struct eth_device *)malloc(sizeof(struct eth_device));

	if (NULL == device) {
		printf("Unable to allocate memory for eth_device.\n");
		return -1;
	}

	memset((void *)device, 0, sizeof(struct eth_device *));

	/*
	  Set up the reset of the eth_device structure and register it.
	*/

	sprintf(device->name, "LSI_FEMAC");
	memcpy(device->enetaddr, enetaddr, (sizeof(unsigned char) * 6));
	device->init         = lsi_femac_eth_init;
	device->halt         = lsi_femac_eth_halt;
	device->send         = lsi_femac_eth_send;
	device->recv         = lsi_femac_eth_rx;
	device->write_hwaddr = lsi_femac_write_hwaddr;
	eth_register(device);
#elif defined(CONFIG_AXXIA_EIOA)
#warning "EIOA has not been implemented in the new U-Boot branch."
#else
#error "Axxia networking is defined, but no interface has been!"
#endif

	return 0;
}
