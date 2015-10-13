/*
*  Copyright (C) 2013 LSI Corporation
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
#include <common.h>
#include <usb/ulpi.h>

/*
------------------------------------------------------------------------------
usb_phy_init
*/

int __weak
usb_phy_init(void)
{
struct ulpi_viewport ulpi_vp;
unsigned long value;

ulpi_vp.viewport_addr = CONFIG_USB_ADDR+ 0x170;
ulpi_vp.port_num = 0x0;

/*
	  setup ULPI viewport register to access FUSB2805 PHY reg 0x7
	  to complement VBUS signal for FAULT
	*/
value = ulpi_read(&ulpi_vp, (u8 *)0x7);
if (value == ULPI_ERROR) {
printf("ULPI PHY read failed\n");
return -1;
}
if (ulpi_write(&ulpi_vp, (u8 *)0x7, (value| 1 << 5))) {
printf("ULPI PHY write failed\n");
return -1;
}

	return 0;
}
