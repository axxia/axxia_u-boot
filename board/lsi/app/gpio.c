/*
 * (C) Copyright 2008
 * LSI <www.lsi.com>
 * John Jacques <john.jacques@lsi.com>
 * Configuration settings for the LSI APP development boards.
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

#include <common.h>

#if defined(CONFIG_GPIO_PL061)

#include <configs/app3.h>

static unsigned int gpio_inited = 0;
static unsigned int gpio_mask   = 0;

#define	GPIODATA_MASKED		u8REG(CONFIG_NORMAL_GPIO_0_BASE+(gpio_mask<<2))
#define	GPIODATA_MASK(x)	u8REG(CONFIG_NORMAL_GPIO_0_BASE+((x&gpio_mask)<<2))

void gpio_init(void)
{
    *GPIOIE = 0x00;		/* Disable interrupts */
    *GPIOAFSEL = 0x00;		/* Disable hardware control */
    *GPIODIR = 0xFF;		/* Configure all pins as output */

    gpio_inited = 1;
    gpio_mask   = 0xFF;
}

void gpio_setdatamask(unsigned int mask)
{
    if( !gpio_inited )
        gpio_init();

    gpio_mask = (mask & 0xFF);
}

unsigned int gpio_readpin(unsigned int pin)
{
    if( !gpio_inited )
        gpio_init();

    if((pin < 0) || (pin >= GPIO_NUM_PINS))
        return 0;
    return (*GPIODATA_MASKED >> pin) & 0x1;
}

void gpio_writepin(unsigned int pin, unsigned int value)
{
    if( !gpio_inited )
        gpio_init();
    /*
    if((pin < 0) || (pin >= GPIO_NUM_PINS))
        return;
    if(value == GPIO_HIGH)
        *GPIODATA_MASK(pin) |= BIT(pin);
    else if(value == GPIO_LOW)
        *GPIODATA_MASK(pin) &= ~BIT(pin);
    */
}

void gpio_write(unsigned int mask)
{
    if( !gpio_inited )
        gpio_init();
    /*
    *GPIODATA_MASKED = (unsigned char) mask;
    */
}

unsigned int gpio_read(void)
{
    if( !gpio_inited )
        gpio_init();

    return (*GPIODATA_MASKED);
}

#endif  /* defined(CONFIG_GPIO_PL061) */
