/*
 * spintable.c
 *
 * Handles all non-zero cores on LSI's ACP.
 *
 * Copyright (C) 2009 LSI Corporation
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

/*
  ===============================================================================
  ===============================================================================
  ===============================================================================
  Local
  ===============================================================================
  ===============================================================================
  ===============================================================================
*/

/*ACP_DEFINE_SPINLOCK(system);*/
extern unsigned long __acp_system_section;
static volatile unsigned int *stage3_lock = (void *)&__acp_system_section;

/*
  ===============================================================================
  ===============================================================================
  ===============================================================================
  Global
  ===============================================================================
  ===============================================================================
  ===============================================================================
*/

/*
  -------------------------------------------------------------------------------
  acp_initialize_stage3_lock
*/

void
acp_initialize_stage3_lock(void)
{
	*stage3_lock = 0;
}

/*
  -------------------------------------------------------------------------------
  acp_lock_stage3
*/

void
acp_lock_stage3(void)
{
#if !defined(ACP_EMU)
	acp_spin_lock(stage3_lock);
#endif
}

/*
  -------------------------------------------------------------------------------
  acp_unlock_stage3
*/

void
acp_unlock_stage3(void)
{
#if !defined(ACP_EMU)
	acp_spin_unlock(stage3_lock);
#endif
}
