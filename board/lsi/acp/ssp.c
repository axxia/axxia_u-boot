/*
 * ssp.c
 *
 * Simple driver for the SSP controller in LSI's ACP.
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

#ifdef CONFIG_ACP

#include <common.h>
#include <malloc.h>
#include <asm/io.h>

#undef LOG
/*#define LOG*/
#ifdef LOG
READL( unsigned long * address ) {
	unsigned long value;
	value = acpreadio( ( address ) );
	printf( "%s:%s:%d - Read 0x%lx from 0x%lx\n",
		__FILE__, __FUNCTION__, __LINE__, value,
		( unsigned long ) address );
	return value;
}
static inline void
WRITEL( unsigned long value, unsigned long * address ) {
	acpwriteio( value, address );
	printf( "%s:%s:%d - Wrote 0x%lx to 0x%lx\n",
		__FILE__, __FUNCTION__, __LINE__, value,
		( unsigned long ) address );
	return;
}
#else
#define READL( address ) acpreadio( ( address ) )
#define WRITEL( value, address ) acpwriteio( ( value ), ( address ) )
#endif

#undef LOG_WRITES
/*#define LOG_WRITES*/

/*
  ======================================================================
  ======================================================================
  SSP
  ======================================================================
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  ssp_select_device
*/

static void
ssp_select_device( int device )
{
	WRITEL( ( 0x1f & ~ ( 1 << device ) ), ( unsigned long * ) ( SSP + SSP_CSR ) );
}

/*
  ----------------------------------------------------------------------
  ssp_deselect_all
*/

static void
ssp_deselect_all( void )
{
	WRITEL( 0x1f, ( unsigned long * ) ( SSP + SSP_CSR ) );
}

/*
  ----------------------------------------------------------------------
  ssp_write_device
*/

static unsigned short
ssp_write_device( unsigned short value )
{
	unsigned short input;

	/* Send the command to the device. */
	WRITEL( value, ( unsigned long * ) ( SSP + SSP_DR ) );
	/* Get the response from the receive buffer. */
	while( 0 == ( READL( ( unsigned long * ) ( SSP + SSP_SR ) ) & 4 ) );
	input = READL( ( unsigned long * ) ( SSP + SSP_DR ) );

	return input;
}

/*
  ----------------------------------------------------------------------
  ssp_init

  The Clock Rate is

  RATE = SSPCLK / (CPSDVR * (1 + SCR))
*/

#define SSP_DATA_RATE 1250000

int
ssp_init(void)
{
	int rc = 0;
#if 0
	unsigned long sspclk;
	unsigned long cpsdvr;
	unsigned long scr;

	do {
		for (;;) {
			int rc;

			rc = acp_clock_get(peripheral, &sspclk);

			if (0 == rc) {
				sspclk *= 1000;
				break;
			}
		}
	} while (0 == sspclk);

	/* Set up the timer. */
	WRITEL(0, (unsigned long *)(TIMER0 + TIMER_CONTROL));
	WRITEL(1, (unsigned long *) (TIMER0 + TIMER_LOAD));
	WRITEL((TIMER_CONTROL_ENABLE | TIMER_CONTROL_MODE),
	       (unsigned long *)(TIMER0 + TIMER_CONTROL));
	sspclk /= 2;
	mb();

	/*
	  Bit Rate = Clock / (cpsdvr * (scr + 1))

	  scr = ((Clock * cpsdvr) / Bit Rate) - 1

	  scr must be <= 0xff, cpsdvr must be 2, 4, 6, etc.
	*/

	cpsdvr = 0;

	do {
		cpsdvr += 2;
		scr = ((sspclk * cpsdvr) / SSP_DATA_RATE) - 1;
	} while (0xff < scr);

	/* Set up the SSP. */
	WRITEL(((scr << 8) | (0x07)), (unsigned long *) (SSP + SSP_CR0));
	WRITEL(0x2, (unsigned long *) (SSP + SSP_CR1));
	WRITEL(cpsdvr, (unsigned long *) (SSP + SSP_CPSR));
	WRITEL(0x1f, (unsigned long *) (SSP + SSP_CSR));
#else
	WRITEL(0x3107, (unsigned long *) (SSP + SSP_CR0));
	WRITEL(2, (unsigned long *) (SSP + SSP_CR1));
	WRITEL(2, (unsigned long *) (SSP + SSP_CPSR));
	WRITEL(0x1f, (unsigned long *) (SSP + SSP_CSR));
#endif

	return rc;
}

/*
  ======================================================================
  ======================================================================
  Serial EEPROM, Device 0
  ======================================================================
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  read_status
*/

static unsigned long
read_status( int chip )
{
	unsigned long status;

	ssp_select_device( chip );
	status = ssp_write_device( 5 );
	status = ssp_write_device( 0 );
	ssp_deselect_all( );

	return status;
}

/*
  ----------------------------------------------------------------------
  write_enable
*/

static void
write_enable( int chip )
{
	ssp_select_device( chip );
	ssp_write_device( 6 );
	ssp_deselect_all( );

	return;
}

/*
  ----------------------------------------------------------------------
  write_disable
*/

static void
write_disable( int chip )
{
	ssp_select_device( chip );
	ssp_write_device( 4 );
	ssp_deselect_all( );

	return;
}

/*
  ----------------------------------------------------------------------
  seeprom_read
*/

int
seeprom_read( void * buffer, int offset, int bytes )
{
	int return_code = 0;
	unsigned char * output = ( unsigned char * ) buffer;

	ssp_select_device( 0 );
	ssp_write_device( 3 );
	ssp_write_device( ( offset & 0x10000 ) >> 16 );
	ssp_write_device( ( offset & 0xff00 ) >> 8 );
	ssp_write_device( offset & 0xff );

	while( 0 < bytes -- ) {
		unsigned short value;

		value = ssp_write_device( 0 );
		* output ++ = ( unsigned char ) ( value & 0xff );
	}

	ssp_deselect_all( );

	return return_code;
}

/*
  ----------------------------------------------------------------------
  seeprom_write
*/

int
seeprom_write( void * buffer, int offset, int length )
{
	int return_code = 0;
	unsigned char *input = (unsigned char *)buffer;
	unsigned char *verify;
	unsigned char *verify_input;
	int verify_offset;
	int verify_length;

	verify = malloc(length);
	verify_input = input;
	verify_offset = offset;
	verify_length = length;

	if ((unsigned char *)0 == verify) {
		printf("Allocation of verification buffer failed!\n");
		return -1;
	}

	while( 0 < length ) {
		int this_write;
		int this_written = 0;

		write_enable( 0 );
		ssp_select_device( 0 );
		ssp_write_device( 2 );
		ssp_write_device( ( offset & 0x10000 ) >> 16 );
		ssp_write_device( ( offset & 0xff00 ) >> 8 );
		ssp_write_device( offset & 0xff );
		this_write = 256 - ( offset % 256 );

#ifdef LOG_WRITES
		printf( "offset=0x%05x length=0x%05x\n", offset, length );
#endif

		while( ( this_written < this_write ) && ( 0 < length ) ) {
			unsigned long value = ( unsigned long ) ( * input );
#ifdef LOG_WRITES
			printf( "<0x%02x> ", value );
#endif
			ssp_write_device( value );
			++ this_written;
			++ input;
			++ offset;
			-- length;
		}

#ifdef LOG_WRITES
		printf( "\n" );
#endif
		ssp_deselect_all( );
		udelay( 5000 ); /* TODO: This shouldn't be necessary... */
	}

	seeprom_read(verify, verify_offset, verify_length);

	if (0 != memcmp(verify, verify_input, verify_length)) {
		free(verify);
		printf("Verification Failed!\n");
		return -1;
	}

	free(verify);

	return return_code;
}

#if 0

/*
  ----------------------------------------------------------------------
  seeprom_test01
*/

void
seeprom_test01( void )
{
	write_disable( 0 );
	printf( "status: 0x%lx\n", read_status( 0 ) );
	write_enable( 0 );
	printf( "status: 0x%lx\n", read_status( 0 ) );
	write_disable( 0 );
	printf( "status: 0x%lx\n", read_status( 0 ) );

	return;
}

/*
  ----------------------------------------------------------------------
  seeprom_test02
*/

void
seeprom_test02( void )
{
	printf( "Writing...\n" );
	write_enable( 0 );
	ssp_select_device( 0 );
	ssp_write_device( 0x200 );
	ssp_write_device( 0 );
	{
		int i;
		unsigned short * input = ( unsigned short * ) 0;
		for( i = 0; i < 128; ++ i ) {
			ssp_write_device( * input );
			printf( "[0x%04x]", * input );
			++ input;
		}
	}
	printf( "\nFinished Writing\n" );
	ssp_deselect_all( );

	printf( "Reading...\n" );
	ssp_select_device( 0 );
	ssp_write_device( 0x300 );
	ssp_write_device( 0 );
	{
		int i;
		unsigned long data;
		for( i = 0; i < 128; ++ i ) {
			/* Write 0s to drive the clock. */
			data = ssp_write_device( 0 );
			printf( "<0x%04lx>", data );
		}
		printf( "\n" );
	}
	ssp_deselect_all( );

	return;
}

/*
  ----------------------------------------------------------------------
  seeprom_test03
*/

void
seeprom_test03( void )
{
	int page;
	int byte;

	printf( "Erasing\n" );

	for( page = 0; 512 > page; ++ page ) {
		unsigned long offset;

		printf( "." );
		write_enable( 0 );
		ssp_select_device( 0 );
		offset = ( page * 256 );
		ssp_write_device( 0x0200 | ( ( offset & 0xff0000 ) >> 16 ) );
		ssp_write_device( offset & 0xffff );

		for( byte = 0; 256 > byte; byte += 2 ) {
			ssp_write_device( 0 );
		}

		ssp_deselect_all( );
	}

	return;
}

#endif

#endif /* CONFIG_ACP */
