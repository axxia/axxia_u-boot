/*
 *  drivers/gpio/axxia_gpio.c
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

/*
  Axxia systems contain two ARM PL061 GPIOs.
 */

/*#define DEBUG*/
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

#define GPIODATA  0x000
#define GPIODIR   0x400
#define GPIOIS    0x404
#define GPIOIBE   0x408
#define GPIOIEV   0x40c
#define GPIOIE    0x410
#define GPIORIS   0x414
#define GPIOMIS   0x418
#define GPIOIC    0x41c
#define GPIOAFSEL 0x420

/*
  ------------------------------------------------------------------------------
  read_reg
*/

static unsigned long
read_reg(axxia_gpio_t gpio, unsigned long offset)
{
	unsigned long base;
	unsigned long value;

	if (AXXIA_GPIO_0 == gpio)
		base = GPIO0_ADDRESS;
	else
		base = GPIO1_ADDRESS;

	value = readl(base + offset);
	debug("%s:%d - Read 0x%lx from 0x%lx\n",
	      __FILE__, __LINE__, value, (base + offset));

	return value;
}

/*
  ------------------------------------------------------------------------------
  write_reg
*/

static void
write_reg(axxia_gpio_t gpio, unsigned long value, unsigned long offset)
{
	unsigned long base;

	if (AXXIA_GPIO_0 == gpio)
		base = GPIO0_ADDRESS;
	else
		base = GPIO1_ADDRESS;

	debug("%s:%d - Writing 0x%lx to 0x%lx\n",
	      __FILE__, __LINE__, value, (base + offset));
	writel(value, (base + offset));

	return;
}

/*
  ==============================================================================
  ==============================================================================
  Global
  ==============================================================================
  ==============================================================================
*/

/*
  ------------------------------------------------------------------------------
  axxia_gpio_get_direction
*/

int
axxia_gpio_get_direction(axxia_gpio_t gpio, int pin)
{
	unsigned long gpiodir_value;

	if (7 < pin)
		return -1;

	gpiodir_value = read_reg(gpio, GPIODIR);

	return (((1 << pin) & gpiodir_value) >> pin);
}

/*
  ------------------------------------------------------------------------------
  axxia_gpio_set_direction
*/

int
axxia_gpio_set_direction(axxia_gpio_t gpio, int pin, int direction)
{
	unsigned long gpiodir_value;

	if (7 < pin)
		return -1;

	gpiodir_value = read_reg(gpio, GPIODIR);

	if (0 == direction)
		gpiodir_value &= ~(1 << pin);
	else
		gpiodir_value |= (1 << pin);

	write_reg(gpio, gpiodir_value, GPIODIR);

	return 0;
}

/*
  ------------------------------------------------------------------------------
  axxia_gpio_get
*/

int
axxia_gpio_get(axxia_gpio_t gpio, int pin)
{
	unsigned long data;

	if (7 < pin)
		return -1;

	data = read_reg(gpio, (GPIODATA + ((1 << pin) * 4)));

	if (0 == data)
		return 0;
	else
		return 1;
}

/*
  ------------------------------------------------------------------------------
  axxia_gpio_set
*/

int
axxia_gpio_set(axxia_gpio_t gpio, int pin, int value)
{
	if (7 < pin)
		return -1;

	if (0 == value)
		write_reg(gpio, 0, (GPIODATA + ((1 << pin) * 4)));
	else
		write_reg(gpio, (1 << pin), (GPIODATA + ((1 << pin) * 4)));

	return 0;
}

/*
  ==============================================================================
  ==============================================================================
  U-Boot Interface
  ==============================================================================
  ==============================================================================
*/

/*
  ------------------------------------------------------------------------------
  gpio_direction_input

  Set the given pin to input.
*/

int
gpio_direction_input(unsigned pin)
{
	int rc;

	debug("%s:%d - GPIO pin %d set to input.\n", __FILE__, __LINE__, pin);

	if (15 < pin)
		return -1;

	if (8 > pin)
		rc = axxia_gpio_set_direction(AXXIA_GPIO_0, pin, 0);
	else
		rc = axxia_gpio_set_direction(AXXIA_GPIO_1, (pin - 8), 0);

	if (-1 == rc)
		return -1;

	return 0;
}

/*
  ------------------------------------------------------------------------------
  gpio_direction_output

  Set the given pin to output, and set the value to vlaue.
*/

int
gpio_direction_output(unsigned pin, int value)
{
	int rc;

	debug("%s:%d - GPIO pin %d set to output containing %d.\n",
	      __FILE__, __LINE__, pin, value);

	if (15 < pin)
		return -1;

	if (8 > pin) {
		rc = axxia_gpio_set_direction(AXXIA_GPIO_0, pin, 1);
		rc |= axxia_gpio_set(AXXIA_GPIO_0, pin, value);
	} else {
		rc = axxia_gpio_set_direction(AXXIA_GPIO_1, (pin - 8), 1);
		rc |= axxia_gpio_set(AXXIA_GPIO_1, (pin - 8), value);
	}

	if (-1 == rc)
		return -1;

	return 0;
}

/*
  ------------------------------------------------------------------------------
  gpio_get_value

  Read the value of the given pin.
*/

int
gpio_get_value(unsigned pin)
{
	int value;

	if (8 > pin)
		value = axxia_gpio_get(AXXIA_GPIO_0, pin);
	else
		value = axxia_gpio_get(AXXIA_GPIO_1, (pin - 8));

	debug("%s:%d - GPIO pin %u is at %d.\n", __FILE__, __LINE__, pin, value);

	return value;
}

/*
  ------------------------------------------------------------------------------
  gpio_set_value

  Set the value on a pin already reserved as an output.
*/

int
gpio_set_value(unsigned pin, int value)
{
	debug("%s:%d - GPIO pin %d set to %d.\n", __FILE__, __LINE__, pin, value);

	if (8 > pin)
		axxia_gpio_set(AXXIA_GPIO_0, pin, value);
	else
		axxia_gpio_set(AXXIA_GPIO_1, (pin - 8), value);

	return 0;
}

/*
  ------------------------------------------------------------------------------
  gpio_request

  Reserve a pin.
*/

int
gpio_request(unsigned pin, const char *label)
{
	debug("%s:%d - GPIO pin %d requested by %s\n",
	      __FILE__, __LINE__, pin, label);

	if (16 > pin)
		return 0;

	return -1;
}

/*
  ------------------------------------------------------------------------------
  gpio_free

  Free a previously reserved pin.
*/

int
gpio_free(unsigned pin)
{
	debug("%s:%d - GPIO pin %d freed.\n", __FILE__, __LINE__, pin);

	return 0;
}
