/*
 * (C) Copyright 2013
 * LSI Corporation <www.lsi.com>
 * John Jacques <john.jacques@lsi.com>
 * Configuration settings for the LSI ACP development boards.
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

#ifndef __CONFIGS_AXXIA_H
#define __CONFIGS_AXXIA_H

#define CONFIG_AXXIA

/*
  ================================================================================
  ================================================================================
  GPIO
  ================================================================================
  ================================================================================
*/

#ifndef __ASSEMBLY__
#if 0

#define CONFIG_CMD_GPIO
#define CONFIG_AXXIA_GPIO

typedef enum { AXXIA_GPIO_0, AXXIA_GPIO_1 } axxia_gpio_t;

int axxia_gpio_get_direction(axxia_gpio_t gpio, int pin);
int axxia_gpio_set_direction(axxia_gpio_t gpio, int pin, int direction);
int axxia_gpio_get(axxia_gpio_t gpio, int pin);
int axxia_gpio_set(axxia_gpio_t gpio, int pin, int value);
#endif
#endif	/* __ASSEMBLY__ */

/*
  ================================================================================
  ================================================================================
  I2C
  ================================================================================
  ================================================================================
*/

#ifndef __ASSEMBLY__
#if 0
#define CONFIG_CMD_I2C
#define CONFIG_AXXIA_I2C
#define CONFIG_I2C_MULTI_BUS
#define CONFIG_SYS_I2C_SPEED 100000
#endif
#endif	/* __ASSEMBLY__ */

/*
  ================================================================================
  ================================================================================
  Include the Common LSI Header
  ================================================================================
  ================================================================================
*/

#include <configs/lsi.h>

#endif /* __CONFIGS_AXXIA_H */
