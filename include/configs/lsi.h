/*
 * (C) Copyright 2009 LSI Corporation <www.lsi.com>
 * John Jacques <john.jacques@lsi.com>
 * Configuration settings for LSI development boards.
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

#ifndef __CONFIGS_LSI_H
#define __CONFIGS_LSI_H

#define CONFIG_LSI

/*
  ======================================================================
  ======================================================================
  Version
  ======================================================================
  ======================================================================
*/

#ifndef __ASSEMBLY__
const char *get_lsi_version(void);
#endif /* __ASSEMBLY__ */

/*
  ================================================================================
  ================================================================================
  Nuevo Conf Ring Access (see board/lsi/common/ncr.c for the implementation)
  ================================================================================
  ================================================================================
*/

#ifndef __ASSEMBLY__
#define NCP_REGION_ID( node, target ) \
( unsigned long ) ( ( ( ( node ) & 0xffff ) << 16 ) | ( ( target ) & 0xffff ) )
#define NCP_NODE_ID( region ) ( ( ( region ) >> 16 ) & 0xffff )
#define NCP_TARGET_ID( region ) ( ( region ) & 0xffff )
int ncr_read(unsigned long, unsigned long, int, void *);
int ncr_read8( unsigned long, unsigned long, unsigned char * );
int ncr_read16( unsigned long, unsigned long, unsigned short * );
int ncr_read32( unsigned long, unsigned long, unsigned long * );
int ncr_write(unsigned long, unsigned long, int, void *);
int ncr_write8( unsigned long, unsigned long, unsigned char );
int ncr_write16( unsigned long, unsigned long, unsigned short );
int ncr_write32( unsigned long, unsigned long, unsigned long );
int ncr_modify32( unsigned long, unsigned long, unsigned long, unsigned long );
int ncr_and( unsigned long, unsigned long, unsigned long );
int ncr_or( unsigned long, unsigned long, unsigned long );
int ncr_poll( unsigned long, unsigned long, unsigned long,
              unsigned long, unsigned long, unsigned long );
void ncr_tracer_enable( void );
void ncr_tracer_disable( void );
int ncr_tracer_is_enabled( void );
void ncr_enable( void );
void ncr_disable( void );
#endif

#endif /* __CONFIGS_LSI_H */
