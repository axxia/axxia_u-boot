/*
 *  drivers/i2c/axxia_i2c.c
 *
 *  Copyright (C) 2013 LSI (john.jacques@lsi.com)
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

#define DEBUG
#include <common.h>
#include <asm/gpio.h>
#include <asm/io.h>

/*
  ==============================================================================
  ==============================================================================
  Local
  ==============================================================================
  ==============================================================================
*/

static unsigned int current_bus = 0;

/*
  ==============================================================================
  ==============================================================================
  Global
  ==============================================================================
  ==============================================================================
*/

/*
  ==============================================================================
  ==============================================================================
  U-Boot Interface
  ==============================================================================
  ==============================================================================
*/

#ifdef CONFIG_I2C_MULTI_BUS

/*
  ------------------------------------------------------------------------------
  i2c_get_bus_num
*/

unsigned int
i2c_get_bus_num(void)
{
	return current_bus;
}

/*
  ------------------------------------------------------------------------------
  i2c_set_bus_num
*/

int
i2c_set_bus_num(unsigned int bus)
{
	if (2 < bus)
		return -1;

	current_bus = bus;

	return 0;
}

#endif	/* CONFIG_I2C_MULTI_BUS */

/*
  ------------------------------------------------------------------------------
  i2c_read
*/

int
i2c_read(uchar chip, uint address, int alen, uchar *buffer, int len)
{
	return -1;
}

/*
  ------------------------------------------------------------------------------
  i2c_write
*/

int
i2c_write(uchar chip, uint address, int alen, uchar *buffer, int len)
{
	return -1;
}

/*
  ------------------------------------------------------------------------------
  i2c_probe
*/

int
i2c_probe(uchar chip)
{
	return -1;
}

/*
  ------------------------------------------------------------------------------
  i2c_init
*/

void
i2c_init(int speed, int slave)
{
	return;
}
