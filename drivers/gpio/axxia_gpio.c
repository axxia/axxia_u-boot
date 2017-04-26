/*
 *  drivers/gpio/axxia_gpio.c
 *
 *  Copyright (C) 2016 Intel (john.jacques@intel.com)
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
  -----------------------------------------------------------------------------
  read_reg
*/

static unsigned long
read_reg(axxia_gpio_t gpio, unsigned long offset)
{
	unsigned long base;
	unsigned long value;

	base = GPIO_BASE_ADDRESS + gpio * GPIO_GROUP_OFFSET;
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

	base = GPIO_BASE_ADDRESS + gpio * GPIO_GROUP_OFFSET;
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

	/* Range check... */
	if (0 > pin || 7 < pin)
		return -1;

	data = read_reg(gpio, (GPIODATA + ((1 << pin) * 4)));

	if (0 != data)
		return 1;

	return 0;
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
  name_to_gpio
*/

int name_to_gpio(const char *name)
{
	char *separator;
	int group, pin;

	separator = strchr(name, '_');

	if (NULL != separator) {
		/*
		  Older format, though not reasonably described, was
		  <bank>_<pin>.  If separator is not NULL, assume the
		  older format.
		*/

		group = simple_strtoul(name, NULL, 10);
		pin = simple_strtoul(separator + 1, NULL, 10);

		if ((group >= GPIO_GROUPS) || (pin < 0))
			return -1;

		return (group * GPIO_PINS_PER_GROUP + pin);
	}

	/*
	  Just assume that the pin is 0...(GPIO_GROUPS *
	  GPIO_PINS_PER_GROUP - 1).
	*/

	pin = simple_strtoul(name, NULL, 10);

	if ((GPIO_PINS_PER_GROUP * GPIO_GROUPS) <= pin)
		return -1;

	return pin;
}

/*
  ------------------------------------------------------------------------------
  gpio_direction_input

  Set the given pin to input.
*/

int
gpio_direction_input(unsigned pin)
{
	int rc;
	int group, pin_in_group;

	debug("%s:%d - GPIO pin %d set to input.\n", __FILE__, __LINE__, pin);

	if (GPIO_GROUPS * GPIO_PINS_PER_GROUP < pin)
		return -1;

	group = pin / GPIO_PINS_PER_GROUP;
	pin_in_group = pin % GPIO_PINS_PER_GROUP;
	rc = axxia_gpio_set_direction(group, pin_in_group, 0);

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
	int group, pin_in_group;

	debug("%s:%d - GPIO pin %d set to output containing %d.\n",
	      __FILE__, __LINE__, pin, value);

	if (GPIO_GROUPS * GPIO_PINS_PER_GROUP < pin)
		return -1;

	group = pin / GPIO_PINS_PER_GROUP;
	pin_in_group = pin % GPIO_PINS_PER_GROUP;
	rc = axxia_gpio_set_direction(group, pin_in_group, 1);
	rc |= axxia_gpio_set(group, pin_in_group, value);

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
	int group, pin_in_group;

	if (GPIO_GROUPS * GPIO_PINS_PER_GROUP < pin)
		return -1;

	group = pin / GPIO_PINS_PER_GROUP;
	pin_in_group = pin % GPIO_PINS_PER_GROUP;
	value = axxia_gpio_get(group, pin_in_group);

	debug("%s:%d - GPIO pin %u is at %d.\n",
	      __FILE__, __LINE__, pin, value);

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
	int group, pin_in_group;

	debug("%s:%d - GPIO pin %d set to %d.\n",
	      __FILE__, __LINE__, pin, value);

	if (GPIO_GROUPS * GPIO_PINS_PER_GROUP < pin)
		return -1;

	group = pin / GPIO_PINS_PER_GROUP;
	pin_in_group = pin % GPIO_PINS_PER_GROUP;
	axxia_gpio_set(group, pin_in_group, value);

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

	if (GPIO_GROUPS * GPIO_PINS_PER_GROUP > pin)
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

/*
  ------------------------------------------------------------------------------
  gpio_status
*/

int
axxia_gpio_status(void)
{
	int i;

	printf("Axxia GPIO, %d Banks of %d Pins (%d Total)\n",
	       GPIO_GROUPS, GPIO_PINS_PER_GROUP,
	       (GPIO_PINS_PER_GROUP * GPIO_GROUPS));

	for (i = 0; i < (GPIO_PINS_PER_GROUP * GPIO_GROUPS); ++i) {
		int g;
		int p;

		g = i / GPIO_PINS_PER_GROUP;
		p = i % GPIO_PINS_PER_GROUP;

		printf("%02d_%02d:%02d - Direction=%s Value=%d\n",
		       g, p, i,
		       0 == axxia_gpio_get_direction(g, p) ? "In " : "Out",
		       axxia_gpio_get(g, p));
	}

	return 0;
}
