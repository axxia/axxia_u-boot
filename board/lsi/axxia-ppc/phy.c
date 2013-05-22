/*
 * board/lsi/phy.c
 *
 * Basic PHY control.
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

#ifdef CONFIG_LSI

#include <common.h>
#include <asm/io.h>

/*
  ======================================================================
  ======================================================================
  Local Stuff
  ======================================================================
  ======================================================================
*/

/* Debugging */
#undef DEBUG
/*#define DEBUG*/
#if defined( DEBUG )
#define DEBUG_PRINT( format, args... ) do { \
printf( "phy:%s:%d - DEBUG - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else
#define DEBUG_PRINT( format, args... )
#endif

#define NUM_PHYS 32
#define PHY_RETRIES 10

typedef struct {
	int ( * duplex ) ( int );
	int ( * speed ) ( int );
} phy_ops_t;

static phy_ops_t * phy_ops [ NUM_PHYS ] = { ( phy_ops_t * ) 0 };

/*
  ======================================================================
  Micrel
  ======================================================================
*/

#define MICREL_PHY_ID_HIGH_ID   0x22
#define MICREL_PHY_ID_LOW_ID    0x05
#define MICREL_PHY_ID_LOW_MODEL 0x21

/* -- -- */

#define MICREL_PHY_AUXILIARY_CONTROL_STATUS 0x1f

typedef union {
	unsigned short raw;

	struct {
#ifdef __BIG_ENDIAN
		unsigned short                    : 3;
		unsigned short energy             : 1;
		unsigned short force_link         : 1;
		unsigned short power_saving       : 1;
		unsigned short interrupt_level    : 1;
		unsigned short jabber_enable      : 1;
		unsigned short autoneg_indication : 1;
		unsigned short enable_pause       : 1;
		unsigned short isolate            : 1;
		unsigned short op_mode_indication : 3;
		unsigned short                    : 2;
#else  /* __BIG_ENDIAN */
#endif /* __BIG_ENDIAN */
  } bits;
} micrel_phy_auxiliary_control_status_t;

/*
  ----------------------------------------------------------------------
  micrel_phy_duplex
*/

static int
micrel_phy_duplex( int phy )
{
	micrel_phy_auxiliary_control_status_t aux;

	aux.raw = mdio_read( phy, MICREL_PHY_AUXILIARY_CONTROL_STATUS );
	DEBUG_PRINT( "aux.raw=0x%x aux.bits.op_mode_indication=%d " \
		     "aux.bits.isolate=%d aux.bits.enable_pause=%d " \
		     "aux.bits.autoneg_indication=%d aux.bits.jabber_enable=%d " \
		     "aux.bits.interrupt_level=%d aux.bits.power_saving=%d " \
		     "aux.bits.force_link=%d aux.bits.energy=%d\n",
		     aux.raw, aux.bits.op_mode_indication, aux.bits.isolate,
		     aux.bits.enable_pause, aux.bits.autoneg_indication,
		     aux.bits.jabber_enable, aux.bits.interrupt_level,
		     aux.bits.power_saving, aux.bits.force_link, aux.bits.energy );

	return ( ( aux.bits.op_mode_indication >> 2 ) & 0x1 );
}

/*
  ----------------------------------------------------------------------
  micrel_phy_speed
*/

static int
micrel_phy_speed( int phy )
{
	micrel_phy_auxiliary_control_status_t aux;

	aux.raw = mdio_read( phy, MICREL_PHY_AUXILIARY_CONTROL_STATUS );
	DEBUG_PRINT( "aux.raw=0x%x aux.bits.op_mode_indication=%d " \
		     "aux.bits.autoneg_indication=%d aux.bits.jabber_enable=%d " \
		     "aux.bits.force_link=%d\n",
		     aux.raw, aux.bits.op_mode_indication, aux.bits.autoneg_indication,
		     aux.bits.jabber_enable, aux.bits.force_link );

	switch( ( aux.bits.op_mode_indication & 3 ) ) {
	case 2: return 1; break;
	case 1:	return 0; break;
	default: break;
	}

	return -1;
}

/*
  Micrel PHY Operations
*/

phy_ops_t micrel_phy_ops = {
	.duplex = micrel_phy_duplex,
	.speed = micrel_phy_speed
};

/*
  ======================================================================
  Broadcomm
  ======================================================================
*/

#define BC_PHY_ID_HIGH_ID   0x40
#define BC_PHY_ID_LOW_ID    0x18
#define BC_PHY_ID_LOW_MODEL 0x1e

/*
  ======================================================================
  VSC8634
*/

#define VSC8634_PHY_ID_HIGH_ID   0x7
#define VSC8634_PHY_ID_LOW_ID    0x1
#define VSC8634_PHY_ID_LOW_MODEL 0x24

#define VSC8634_PHY_AUXILIARY_CONTROL_STATUS 0x1c

typedef union {
	unsigned short raw;

	struct {
#ifdef __BIG_ENDIAN
		unsigned short autoneg_complete   : 1;
		unsigned short autoneg_disabled   : 1;
		unsigned short mdi_xover          : 1;
		unsigned short cd_swap            : 1;
		unsigned short a_pi               : 1;
		unsigned short b_pi               : 1;
		unsigned short c_pi               : 1;
		unsigned short d_pi               : 1;
		unsigned short actiphy_ls_toc1    : 1;
		unsigned short actiphy_enable     : 1;
		unsigned short fdx                : 1;
		unsigned short speed              : 2;
		unsigned short actiphy_ls_toc0    : 1;
		unsigned short                    : 2;
#else  /* __BIG_ENDIAN */
#endif /* __BIG_ENDIAN */
  } bits;
} vsc8634_phy_auxiliary_control_status_t;

/*
  ----------------------------------------------------------------------
  vsc8634_phy_duplex
*/

static int
vsc8634_phy_duplex( int phy )
{
	vsc8634_phy_auxiliary_control_status_t aux;

	aux.raw = mdio_read( phy, VSC8634_PHY_AUXILIARY_CONTROL_STATUS );

	return aux.bits.fdx;
}

/*
  ----------------------------------------------------------------------
  vsc8634_phy_speed
*/

static int
vsc8634_phy_speed( int phy )
{
	vsc8634_phy_auxiliary_control_status_t aux;

	aux.raw = mdio_read( phy, VSC8634_PHY_AUXILIARY_CONTROL_STATUS );

	return aux.bits.speed;
}

phy_ops_t vsc8634_phy_ops = {
	.duplex = vsc8634_phy_duplex,
	.speed = vsc8634_phy_speed
};

/*
  ======================================================================
  Local Functions
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  phy_identify
*/

static int
phy_identify( int phy )
{
	phy_id_high_t phy_id_high;
	phy_id_low_t phy_id_low;

	phy_id_high.raw = mdio_read( phy, PHY_ID_HIGH );
	DEBUG_PRINT( "phy_id_high.raw=0x%x phy_id_high.bits.id=0x%x\n",
		     phy_id_high.raw, phy_id_high.bits.id );
	phy_id_low.raw = mdio_read( phy, PHY_ID_LOW );
	DEBUG_PRINT( "phy_id_low.raw=0x%x phy_id_low.bits.id=0x%x "
		     "phy_id_low.bits.model=0x%x "
		     "phy_id_low.bits.revision=0x%x\n",
		     phy_id_low.raw, phy_id_low.bits.id, phy_id_low.bits.model,
		     phy_id_low.bits.revision );

	switch( phy_id_high.bits.id ) {
	case MICREL_PHY_ID_HIGH_ID:
		DEBUG_PRINT( "MICREL_PHY_ID_LOW_ID=0x%x "
			     "phy_id_low.bits.id=0x%x\n",
			     MICREL_PHY_ID_LOW_ID, phy_id_low.bits.id );
		/* Micrel PHY */
		if( ( MICREL_PHY_ID_LOW_ID == phy_id_low.bits.id ) &&
		    ( MICREL_PHY_ID_LOW_MODEL == phy_id_low.bits.model ) ) {
			/*
			  Micrel PHYs are used on ACP and APP3K
			*/
			phy_ops [ phy ] = & micrel_phy_ops;
			DEBUG_PRINT( "Setting up Micrel Operations.\n" );
			return 0;
		}
		break;
	case VSC8634_PHY_ID_HIGH_ID:
		if ((VSC8634_PHY_ID_LOW_ID == phy_id_low.bits.id) &&
		    (VSC8634_PHY_ID_LOW_MODEL == phy_id_low.bits.model)) {
			phy_ops[phy] = &vsc8634_phy_ops;

			return 0;
		}
		break;
	default:
		break;
	}

	printf( "Unknown PHY: high:0x%x low:0x%x model:0x%x rev:0x%x\n",
		phy_id_high.bits.id, phy_id_low.bits.id,
		phy_id_low.bits.model, phy_id_low.bits.revision );

	return -1;
}

/*
  ======================================================================
  Implementation of the Interface Defined in include/configs/lsi.h
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  phy_duplex
*/

int
phy_duplex( int phy )
{
	phy_ops_t * ops;

	DEBUG_PRINT( "\n" );

	if( ( phy_ops_t * ) 0 == ( ops = phy_ops [ phy ] ) ) {
		if( 0 != phy_identify( phy ) ) {
			return -1;
		}
		ops = phy_ops [ phy ];
	}

	DEBUG_PRINT( "ops=0x%x ops->duplex=0x%x\n", ops, ops->duplex );

	return ops->duplex( phy );
}

/*
  ----------------------------------------------------------------------
  phy_link
*/

int
phy_link( int phy )
{
	phy_control_t control;
	phy_status_t status;

	DEBUG_PRINT( "phy=%d\n", phy );

	control.raw = mdio_read( phy, PHY_CONTROL );
	status.raw = mdio_read( phy, PHY_STATUS );
	status.raw = mdio_read( phy, PHY_STATUS );

	return status.bits.link_status;
}

/*
  ----------------------------------------------------------------------
  phy_renegotiate
*/

int
phy_renegotiate( int phy, int ad_value )
{
	phy_control_t control;
	phy_status_t status;
	int autoneg_retries = PHY_RETRIES;
	int autoneg_complete_retries = PHY_RETRIES;

	DEBUG_PRINT( "\n" );
	mdio_write( phy, PHY_AUTONEG_ADVERTISE, ad_value );

	do {
		control.raw = mdio_read( phy, PHY_CONTROL );
		control.bits.restart_autoneg = 1;
		mdio_write( phy, PHY_CONTROL, control.raw );

		do {
			udelay( 500000 );
			status.raw = mdio_read( phy, PHY_STATUS );
		} while( ( 0 < -- autoneg_complete_retries ) &&
			 ( 0 == status.bits.autoneg_comp ) );

		if( 0 == status.bits.autoneg_comp ) {
			puts( "." );
		} else {
			break;
		}
	} while( 0 < -- autoneg_retries );

	if( 0 == status.bits.autoneg_comp ) {
		printf( "Auto Negotiation Failed\n" );
		return -1;
	}

	return 0;
}

/*
  ----------------------------------------------------------------------
  phy_reset
*/

int
phy_reset( int phy )
{
	phy_control_t control;
	int retries = PHY_RETRIES;

	DEBUG_PRINT( "\n" );

	control.raw = mdio_read( phy, PHY_CONTROL );
	control.bits.soft_reset = 1;
	mdio_write( phy, PHY_CONTROL, control.raw );

	do {
		control.raw = mdio_read( phy, PHY_CONTROL );
		-- retries;
	} while( ( 0 < retries ) && ( 0 != control.bits.soft_reset ) );

	if( 0 != control.bits.soft_reset ) {
		printf( "phy_reset( %d ) failed.\n", phy );
		return -1;
	}

	return 0;
}

/*
  ----------------------------------------------------------------------
  phy_speed
*/

int
phy_speed( int phy )
{
	phy_ops_t * ops;

	DEBUG_PRINT( "\n" );

	if( ( phy_ops_t * ) 0 == ( ops = phy_ops [ phy ] ) ) {

		if( 0 != phy_identify( phy ) ) {
			return -1;
		}

		ops = phy_ops [ phy ];
	}

	DEBUG_PRINT( "ops=0x%x ops->speed=0x%x\n", ops, ops->speed );

	return ops->speed( phy );
}

/*
  ----------------------------------------------------------------------
  phy_debug
*/

void
phy_debug( void )
{
#ifndef CONFIG_ACP2
	DEBUG_PRINT( "\n" );
	/* PHY Access Test */
	phy_renegotiate( 0x1e, PHY_AUTONEG_ADVERTISE_100FULL );
	printf( "phy_duplex( 0x1e ) returned 0x%x\n", phy_duplex( 0x1e ) );
	printf( "phy_link( 0x1e ) returned 0x%x\n", phy_link( 0x1e ) );
	printf( "phy_speed( 0x1e ) returned 0x%x\n", phy_speed( 0x1e ) );
	phy_renegotiate( 0x1e, PHY_AUTONEG_ADVERTISE_100 );
	printf( "phy_duplex( 0x1e ) returned 0x%x\n", phy_duplex( 0x1e ) );
	printf( "phy_link( 0x1e ) returned 0x%x\n", phy_link( 0x1e ) );
	printf( "phy_speed( 0x1e ) returned 0x%x\n", phy_speed( 0x1e ) );
	phy_renegotiate( 0x1e, PHY_AUTONEG_ADVERTISE_10FULL );
	printf( "phy_duplex( 0x1e ) returned 0x%x\n", phy_duplex( 0x1e ) );
	printf( "phy_link( 0x1e ) returned 0x%x\n", phy_link( 0x1e ) );
	printf( "phy_speed( 0x1e ) returned 0x%x\n", phy_speed( 0x1e ) );
	phy_renegotiate( 0x1e, PHY_AUTONEG_ADVERTISE_10 );
	printf( "phy_duplex( 0x1e ) returned 0x%x\n", phy_duplex( 0x1e ) );
	printf( "phy_link( 0x1e ) returned 0x%x\n", phy_link( 0x1e ) );
	printf( "phy_speed( 0x1e ) returned 0x%x\n", phy_speed( 0x1e ) );
#endif /* CONFIG_ACP2 */
}

#endif /* CONFIG_LSI */
