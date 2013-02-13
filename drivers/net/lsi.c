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

static int initialized = 0;
static int femac;
static struct eth_device *device;

#if defined(CONFIG_AXXIA_EIOA)
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
_eth_init(struct eth_device *dev, bd_t *bd)
{
	int rc;

	update_femac();

	if (0 != femac)
		rc = lsi_femac_eth_init(dev, bd);
	else
		rc = acp_eioa_eth_init(dev, bd);

	return rc;
}

static void
_eth_halt(struct eth_device *dev)
{
	if (0 != femac)
		lsi_femac_eth_halt(struct eth_device *dev);
	else
		acp_eioa_eth_halt(struct eth_device *dev);

	return;
}
#else
static int
_eth_init(struct eth_device *dev, bd_t *bd)
{
	return lsi_femac_eth_init(dev, bd);
}

static void
_eth_halt(struct eth_device *dev)
{
	lsi_femac_eth_halt(dev);

	return;
}
#endif

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

int dumprx = 0;
int dumptx = 0;

void
dump_packet(const char *header, void *packet, int length)
{
	int i;

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

/*
  -------------------------------------------------------------------------------
  lsi_net_receive_test
*/

void
lsi_net_receive_test(void)
{
#if defined(CONFIG_AXXIA_EIOA)
	update_femac();

	if (0 != femac)
		lsi_femac_receive_test(device);
	else
		acp_eioa_receive_test(device);
#else
	lsi_femac_receive_test(device);
#endif
}

/*
  -------------------------------------------------------------------------------
  lsi_net_loopback_test
*/

void
lsi_net_loopback_test(void)
{
#if defined(CONFIG_AXXIA_EIOA)
	update_femac();

	if (0 != femac)
		lsi_femac_loopback_test(device);
	else
		acp_eioa_loopback_test(device);
#else
	lsi_femac_loopback_test(device);
#endif
}

/*
  ----------------------------------------------------------------------
  lsi_eth_init
*/

static int
lsi_eth_init(struct eth_device *dev, bd_t *bd)
{
	int rc;

	DEBUG_PRINT("\n");

	/* If already initialized, halt an do it again.	*/
	if (0 != initialized)
		dev->halt(dev);

	/* Call the appropriate eth_init. */
	rc = _eth_init(dev, bd);

	/* Change the state to "initialized" if successful. */
	if (0 == rc)
		initialized = 1;

	return rc;
}

/*
  -------------------------------------------------------------------------------
  lsi_eth_send
*/

static int
lsi_eth_send(struct eth_device *dev, volatile void *packet, int length)
{
	DEBUG_PRINT("\n");

	if (0 == initialized) {
		ERROR_PRINT("Networking Isn't Initialized!\n");
		return 0;
	}

#if defined(CONFIG_AXXIA_EIOA)
	if (0 != femac)
		return lsi_femac_eth_send(packet, length);
	else
		return acp_eioa_eth_send(packet, length);
#else
	return lsi_femac_eth_send(dev, packet, length);
#endif
}

/*
  -------------------------------------------------------------------------------
  lsi_eth_recv
*/

static int
lsi_eth_recv(struct eth_device *dev)
{
	DEBUG_PRINT("\n");

	if (0 == initialized) {
		ERROR_PRINT("Networking Isn't Initialized!\n");
		return 0;
	}

#if defined(CONFIG_AXXIA_EIOA)
	if (0 != femac)
		return lsi_femac_eth_recv(dev);
	else
		return acp_eioa_eth_recv(dev);
#else
	return lsi_femac_eth_recv(dev);
#endif
}

/*
  -------------------------------------------------------------------------------
  lsi_eth_halt
*/

static void
lsi_eth_halt(struct eth_device *dev)
{
	DEBUG_PRINT("\n");

#if defined(CONFIG_AXXIA_EIOA)
	if (0 != initialized) {
		if (0 != femac)
			lsi_femac_eth_halt(dev);
		else
			acp_eioa_eth_halt(dev);
	}
#else
	if (0 != initialized)
		lsi_femac_eth_halt(dev);
#endif

	return;
}

/*
  -------------------------------------------------------------------------------
  lsi_eth_write_hwaddr
*/

static int
lsi_eth_write_hwaddr(struct eth_device *dev)
{
	return 0;
}

/*
  ------------------------------------------------------------------------------
  board_eth_init
*/

int
board_eth_init(bd_t *bd)
{
	int i;
	char *ethaddr = NULL;
	char *endp;

	/*
	  Allocate a device structure and clear it.
	*/

	if (NULL ==
	    (device = (struct eth_device *)malloc(sizeof(struct eth_device)))) {
		ERROR_PRINT("unable to allocate memory\n");
		return -1;
	}

	memset((void *)device, 0, sizeof(struct eth_device *));

	/*
	  Get the Ethernet address from the environment.
	*/

	ethaddr = getenv("ethaddr");

	if (NULL == ethaddr) {
		ERROR_PRINT("ethaddr is not set.\n");
		return -1;
	}

	for (i = 0; i < 6; ++i) {
		device->enetaddr[i] = simple_strtoul(ethaddr, &endp, 16);

		if (endp == ethaddr) {
			ERROR_PRINT("Error parsing ethaddr.\n");
			return -1;
		}

		if (0 != *endp)
			ethaddr = (endp + 1);
	}

	for (i = 0; i < 6; ++i)
		bd->bi_enetaddr[i] = device->enetaddr[i];

	/*
	  Set up the reset of the eth_device structure and register it.
	*/

	sprintf(device->name, "LSI_FEMAC");
	device->init         = lsi_eth_init;
	device->halt         = lsi_eth_halt;
	device->send         = lsi_eth_send;
	device->recv         = lsi_eth_recv;
	device->write_hwaddr = lsi_eth_write_hwaddr;
	eth_register(device);

	return 0;
}
