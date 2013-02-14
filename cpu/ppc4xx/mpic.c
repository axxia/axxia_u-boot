/*
 * Copyright (c) 2010 LSI Inc.
 * John.jacques@lsi.com
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*#define LSI_DEBUG*/
#define LSI_WARN
/*#define LSI_LOGIO*/
#include <config.h>
#include <common.h>

/*
  ------------------------------------------------------------------------------
  pic_enable
*/

void
pic_enable(void)
{
	return;
}

/*
  ------------------------------------------------------------------------------
  pic_irq_enable
*/
  
void
pic_irq_enable(unsigned int interrupt)
{
	DEBUG_PRINT("\n");
}

/*
  ------------------------------------------------------------------------------
  pic_irq_disable
*/

void
pic_irq_disable(unsigned int interrupt)
{
	DEBUG_PRINT("\n");
}
  
/*
  ------------------------------------------------------------------------------
  pic_irq_ack
*/

void
pic_irq_ack(unsigned int interrupt)
{
	DEBUG_PRINT("\n");
}

/*
  ------------------------------------------------------------------------------
  external_interrupt
*/

void
external_interrupt(struct pt_regs *regs)
{
	DEBUG_PRINT("\n");
}
