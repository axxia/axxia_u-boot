/*
 *  Copyright (C) 2013 LSI Corporation
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software;you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation;either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY;without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program;if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <config.h>
#include <common.h>
#include <i2c.h>
#include <asm/gpio.h>

/*
  -------------------------------------------------------------------------------
  sysmem_reset
*/

int __weak
sysmem_reset(void)
{

    printf("reset SDRAM using GPIO pin 14\n");
    gpio_request(14,NULL);
    gpio_direction_output(14,0);
    mdelay(1);
    gpio_direction_input(14);
    gpio_free(14);
    return 0;
}
