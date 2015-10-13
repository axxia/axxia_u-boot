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
/*#define DEBUG 1*/
#ifdef DEBUG
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
#ifndef CONFIG_AXXIA_ARM
#define MICREL_PHY_ID_LOW_MODEL 0x21
#else
#define MICREL_PHY_ID_LOW_MODEL 0x15
#endif

/* -- -- */

#define MICREL_PHY_AUXILIARY_CONTROL_STATUS 0x1e

typedef union {
	unsigned short raw;

	struct {
#if 0
/* #ifdef __BIG_ENDIAN */
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
		unsigned short                    : 2;
		unsigned short op_mode_indication : 3;
		unsigned short isolate            : 1;
		unsigned short enable_pause       : 1;
		unsigned short autoneg_indication : 1;
		unsigned short jabber_enable      : 1;
		unsigned short interrupt_level    : 1;
		unsigned short power_saving       : 1;
		unsigned short force_link         : 1;
		unsigned short energy             : 1;
		unsigned short                    : 3;
#if 0
		unsigned short op_mode_indication : 3;
		unsigned short isolate            : 1;
		unsigned short energy             : 1;
		unsigned short mdi_state          : 1;
		unsigned short           : 1;
		unsigned short polarity          : 1;
		unsigned short link_status          : 1;
		unsigned short flow_ctrl          : 1;

#endif
#endif/* __BIG_ENDIAN */
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
	unsigned short duplex;

	aux.raw = mdio_read( phy, MICREL_PHY_AUXILIARY_CONTROL_STATUS );

#ifndef CONFIG_AXXIA_ARM
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
#else
duplex = aux.raw & 0x7;
if (0x6 == duplex || 0x5 == duplex)
return 1;
else
return 0;
#endif
}

/*
----------------------------------------------------------------------
micrel_phy_speed
*/

static int
micrel_phy_speed( int phy )
{
	micrel_phy_auxiliary_control_status_t aux;
	unsigned short speed;

	aux.raw = mdio_read( phy, MICREL_PHY_AUXILIARY_CONTROL_STATUS );

#ifndef CONFIG_AXXIA_ARM
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
#else
	speed = aux.raw & 0x7;
	if (0x6 == speed || 0x2 == speed)
		return 1;
	else
		return 0;
#endif

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

#define BCM5222_PHY_ID_HIGH_ID   0x40
#define BCM5222_PHY_ID_LOW_ID    0x18
#define BCM5222_PHY_ID_LOW_MODEL 0x1e

#define BCM5222_PHY_AUXILIARY_CONTROL_STATUS 0x18

typedef union {
	unsigned short raw;

	struct {
#ifdef __BIG_ENDIAN
		unsigned short jabber_disable   : 1;
		unsigned short force_link       : 1;
		unsigned short rsvd             : 6;
		unsigned short hsq_lsq          : 2;
		unsigned short edge_rate        : 2;
		unsigned short auto_neg         : 1;
		unsigned short force_ind        : 1;
		unsigned short speed            : 1;
		unsigned short full_duplex_ind  : 1;
#else  /* __BIG_ENDIAN */
		unsigned short full_duplex_ind  : 1;
		unsigned short speed            : 1;
		unsigned short force_ind        : 1;
		unsigned short auto_neg         : 1;
		unsigned short edge_rate        : 2;
		unsigned short hsq_lsq          : 2;
		unsigned short rsvd             : 6;
		unsigned short force_link       : 1;
		unsigned short jabber_disable   : 1;
#endif/* __BIG_ENDIAN */
} bits;
} bcm5222_phy_auxiliary_control_status_t;

static int
bcm5222_phy_duplex( int phy )
{
	bcm5222_phy_auxiliary_control_status_t aux;

	aux.raw = mdio_read( phy, BCM5222_PHY_AUXILIARY_CONTROL_STATUS );

	DEBUG_PRINT( "aux.raw=0x%x aux.bits.full_duplex_ind=%d " \
		     "aux.bits.speed=%d aux.bits.force_ind=%d " \
		     "aux.bits.auto_neg=%d aux.bits.edge_rate=%d\n ",
		     aux.raw, aux.bits.full_duplex_ind, aux.bits.speed,
		     aux.bits.force_ind, aux.bits.auto_neg,
		     aux.bits.edge_rate);

#if 0
	mdio_write( phy, BCM5222_PHY_AUXILIARY_CONTROL_STATUS, 0x4001 );

	aux.raw = mdio_read( phy, BCM5222_PHY_AUXILIARY_CONTROL_STATUS );

	DEBUG_PRINT( "aux.raw=0x%x aux.bits.full_duplex_ind=%d " \
		     "aux.bits.speed=%d aux.bits.force_ind=%d " \
		     "aux.bits.auto_neg=%d aux.bits.edge_rate=%d\n ",
		     aux.raw, aux.bits.full_duplex_ind, aux.bits.speed,
		     aux.bits.force_ind, aux.bits.auto_neg,
		     aux.bits.edge_rate);
#endif

	return aux.bits.full_duplex_ind;

}


static int
bcm5222_phy_speed( int phy )
{
	bcm5222_phy_auxiliary_control_status_t aux;

	aux.raw = mdio_read( phy, BCM5222_PHY_AUXILIARY_CONTROL_STATUS );

	return aux.bits.speed;
}

phy_ops_t bcm5222_phy_ops = {
	.duplex = bcm5222_phy_duplex,
	.speed = bcm5222_phy_speed
};


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
		unsigned short                    : 2;
		unsigned short actiphy_ls_toc0    : 1;
		unsigned short speed              : 2;
		unsigned short fdx                : 1;
		unsigned short actiphy_enable     : 1;
		unsigned short actiphy_ls_toc1    : 1;
		unsigned short d_pi               : 1;
		unsigned short c_pi               : 1;
		unsigned short b_pi               : 1;
		unsigned short a_pi               : 1;
		unsigned short cd_swap            : 1;
		unsigned short mdi_xover          : 1;
		unsigned short autoneg_disabled   : 1;
		unsigned short autoneg_complete   : 1;
#endif/* __BIG_ENDIAN */
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
	case BCM5222_PHY_ID_HIGH_ID:
		if ((BCM5222_PHY_ID_LOW_ID == phy_id_low.bits.id) &&
		    (BCM5222_PHY_ID_LOW_MODEL == phy_id_low.bits.model)) {
			phy_ops[phy] = &bcm5222_phy_ops;
			DEBUG_PRINT( "Setting up BCM5222 Operations.\n" );
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

	DEBUG_PRINT( "ops=0x%p ops->duplex=0x%p\n", ops, ops->duplex );

	return ops->duplex( phy );
}

/*
----------------------------------------------------------------------
phy_link
*/

int
phy_link( int phy )
{
	phy_status_t status;

	(void)mdio_read( phy, PHY_CONTROL );
	status.raw = mdio_read( phy, PHY_STATUS );
	status.raw = mdio_read( phy, PHY_STATUS );

	return status.bits.link_status;
}

/*
-------------------------------------------------------------------------------
phy_set
*/

int phy_set(int phy, int speed, int duplex)
{
	phy_control_t control;

	control.raw = mdio_read(phy, PHY_CONTROL);
	control.bits.autoneg_enable = 0;

	if (0 != speed)
		control.bits.force100 = 1;
	else
		control.bits.force100 = 0;

	if (0 != duplex)
		control.bits.full_duplex = 1;
	else
		control.bits.full_duplex = 0;

	mdio_write(phy, PHY_CONTROL, control.raw);

	return 0;
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

	/*
	  If the link is already up, and the ad value is correct,
	  don't renegotiate.
	*/

	status.raw = mdio_read(phy, PHY_STATUS);

	if ((ad_value == mdio_read(phy, PHY_AUTONEG_ADVERTISE)) &&
	    (0 != status.bits.autoneg_comp) && (1 == phy_link(phy)))
		return 0;

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
-------------------------------------------------------------------------------
phy_loopback
*/

int
phy_loopback(int phy, int state)
{
	phy_control_t control;

	control.raw = mdio_read(phy, PHY_CONTROL);
	control.bits.loop_back = state;
	mdio_write(phy, PHY_CONTROL, control.raw);

	return 0;
}

/*
----------------------------------------------------------------------
phy_reset
*/
#ifndef CONFIG_AXXIA_ARM
int
phy_reset( int phy )
#else
int
axxia_phy_reset( int phy )
#endif
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

	DEBUG_PRINT( "ops=0x%p ops->speed=0x%p\n", ops, ops->speed );

	return ops->speed( phy );
}

/*
----------------------------------------------------------------------
phy_debug
*/

void
phy_debug( void )
{

#ifndef CONFIG_AXXIA_EMU
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
#else
	DEBUG_PRINT( "\n" );
	/* PHY Access Test */
	phy_renegotiate( 0x3, PHY_AUTONEG_ADVERTISE_100FULL );
	printf( "phy_duplex( 0x3 ) returned 0x%x\n", phy_duplex( 0x3 ) );
	printf( "phy_link( 0x3 ) returned 0x%x\n", phy_link( 0x3 ) );
	printf( "phy_speed( 0x3 ) returned 0x%x\n", phy_speed( 0x3 ) );
	phy_renegotiate( 0x3, PHY_AUTONEG_ADVERTISE_100 );
	printf( "phy_duplex( 0x3 ) returned 0x%x\n", phy_duplex( 0x3 ) );
	printf( "phy_link( 0x3 ) returned 0x%x\n", phy_link( 0x3 ) );
	printf( "phy_speed( 0x3 ) returned 0x%x\n", phy_speed( 0x3 ) );
	phy_renegotiate( 0x3, PHY_AUTONEG_ADVERTISE_10FULL );
	printf( "phy_duplex( 0x3 ) returned 0x%x\n", phy_duplex( 0x3 ) );
	printf( "phy_link( 0x3 ) returned 0x%x\n", phy_link( 0x3 ) );
	printf( "phy_speed( 0x3 ) returned 0x%x\n", phy_speed( 0x3 ) );
	phy_renegotiate( 0x3, PHY_AUTONEG_ADVERTISE_10 );
	printf( "phy_duplex( 0x3 ) returned 0x%x\n", phy_duplex( 0x3 ) );
	printf( "phy_link( 0x3 ) returned 0x%x\n", phy_link( 0x3 ) );
	printf( "phy_speed( 0x3 ) returned 0x%x\n", phy_speed( 0x3 ) );
	phy_renegotiate( 0x3, PHY_AUTONEG_ADVERTISE_100FULL );
	printf( "phy_duplex( 0x3 ) returned 0x%x\n", phy_duplex( 0x3 ) );
	printf( "phy_link( 0x3 ) returned 0x%x\n", phy_link( 0x3 ) );
	printf( "phy_speed( 0x3 ) returned 0x%x\n", phy_speed( 0x3 ) );
	phy_renegotiate( 0x3, PHY_AUTONEG_ADVERTISE_100 );
	printf( "phy_duplex( 0x3 ) returned 0x%x\n", phy_duplex( 0x3 ) );
	printf( "phy_link( 0x3 ) returned 0x%x\n", phy_link( 0x3 ) );
	printf( "phy_speed( 0x3 ) returned 0x%x\n", phy_speed( 0x3 ) );
	phy_renegotiate( 0x3, PHY_AUTONEG_ADVERTISE_10FULL );
	printf( "phy_duplex( 0x3 ) returned 0x%x\n", phy_duplex( 0x3 ) );
	printf( "phy_link( 0x3 ) returned 0x%x\n", phy_link( 0x3 ) );
	printf( "phy_speed( 0x3 ) returned 0x%x\n", phy_speed( 0x3 ) );
	phy_renegotiate( 0x3, PHY_AUTONEG_ADVERTISE_10 );
	printf( "phy_duplex( 0x3 ) returned 0x%x\n", phy_duplex( 0x3 ) );
	printf( "phy_link( 0x3 ) returned 0x%x\n", phy_link( 0x3 ) );
	printf( "phy_speed( 0x3 ) returned 0x%x\n", phy_speed( 0x3 ) );
#endif
}
