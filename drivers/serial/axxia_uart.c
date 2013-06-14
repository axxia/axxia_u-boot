/*
 *  Copyright (C) 2009 LSI <john.jacques@lsi.com>
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
#include <asm/byteorder.h>
#include <serial.h>

DECLARE_GLOBAL_DATA_PTR;

void serial_exit(void);

/*
  ======================================================================
  ======================================================================
  UART Registers
  ======================================================================
  ======================================================================
*/

#ifndef ACP_ISS

#define UART_DR      (0x00)
#define UART_FR      (0x18)
#define UART_IBRD    (0x24)
#define UART_FBRD    (0x28)
#define UART_LCR_H   (0x2c)
#define UART_CR      (0x30)
#define UART_IFLS    (0x34)
#define UART_IMSC    (0x38)
#define UART_ECR     (0x04)

#define FR_BUSY 0x08
#define FR_RXFE 0x10
#define FR_TXFF 0x20
#define FR_TXFE 0x80

typedef struct {
	unsigned long uart;
	unsigned long timer;
} acp_uart_t;

acp_uart_t uart = {1, 1};

#endif /* ACP_ISS */

/*
  ======================================================================
  ======================================================================
  Clocks and Divisors...
  ======================================================================
  ======================================================================
*/

#ifndef ACP_ISS

/*
  ======================================================================
*/

typedef struct {

	unsigned long divisor;
	unsigned char ibrd;
	unsigned char fbrd;

} clock_stuff_t;

static int get_clock_stuff(int, clock_stuff_t *);
//static void acp_serial_init(unsigned long, unsigned long, unsigned long);
static void axxia_serial_initialize(unsigned long, unsigned long, unsigned long);

/*
  ----------------------------------------------------------------------
  get_clock_stuff
*/

static int
get_clock_stuff(int baud_rate, clock_stuff_t * clock_stuff)
{
	unsigned long divisor = 0;
	unsigned long ibrd;
	unsigned long fbrd;
#ifndef CONFIG_AXXIA_ARM
	unsigned long per_clock;

	do {
		for (;;) {
			int rc;

			rc = acp_clock_get(clock_peripheral, &per_clock);

			if (0 == rc) {
				per_clock *= 1000;
				break;
			}
		}
	} while (0 == per_clock);

	/*
	 The input to the UART clock needs to be consistent, whether
	 the peripheral clock is on the reference clock or PLLB.  So,
	 the input to timer1 can be either 125 MHz or 200 MHz.
	*/

	divisor = (per_clock / UART_CLOCK_SPEED);
#endif
	ibrd = UART_CLOCK_SPEED / (16 * baud_rate);

	/*
	  The following forumla is from the ARM document (ARM DDI 0183E).

	  Baud Rate Divisor = ( Uart Clock / ( 16 * Baud Rate ) )

	  Baud Rate Divisor is then split into integral and fractional
	  parts.  The IBRD value is simply the itegral part.  The FBRD is
	  calculated as follows.

	  FBRD = fractional part of the Baud Rate Divisor * 64 + 0.5

	  The fractional part of the Baud Rate Divisor can be represented as
	  follows.

	  ( Uart Clock % ( 16 * baud_rate ) ) / ( 16 * baud_rate )

	  As long as the division isn't done till the end.  So, the above *
	  64 + 0.5 is the FBRD.  Also note that x/y + 1/2 = (2x+y)/2y.  This
	  leads to

	  ( ( Uart Clock % ( 16 * baud_rate ) ) * 64 * 2 + ( 16 * baud_rate ) )
	  ---------------------------------------------------------------------
	  2 * ( 16 * baud_rate )
	*/

#ifndef CONFIG_AXXIA_ARM
	fbrd = (per_clock / divisor);
#else
	fbrd = UART_CLOCK_SPEED;
#endif
	fbrd %= (16 * baud_rate);
	fbrd *= 128;
	fbrd += (16 * baud_rate);
	fbrd /= (2 * (16 * baud_rate));

	clock_stuff->divisor = (divisor - 1);
	clock_stuff->ibrd = ibrd;
	clock_stuff->fbrd = fbrd;

	return 0;
}

#endif /* ACP_ISS */

/*
  ------------------------------------------------------------------------------
  acp_serial_init
*/

void
//acp_serial_init(unsigned long divisor, unsigned long ibrd, unsigned long fbrd)
axxia_serial_initialize(unsigned long divisor, unsigned long ibrd, unsigned long fbrd)
{
#ifndef ACP_ISS
	unsigned long lcr_h;

	if (0 == uart.uart)
		return;

#ifndef CONFIG_AXXIA_ARM
	/* Set up the timer. */
	writel(0, (uart.timer + TIMER_CONTROL));
	writel(divisor, (uart.timer + TIMER_LOAD));
	writel((TIMER_CONTROL_ENABLE | TIMER_CONTROL_MODE),
	       (uart.timer + TIMER_CONTROL));
#endif
	/*
	  Wait for the end of transmission or reception of the
	  current character.

	  How should this be done for reception?
	*/
	while (0 == (readl(uart.uart + UART_FR) & FR_TXFE));
	while (0 != (readl(uart.uart + UART_FR) & FR_BUSY));

	/* Disable the UART. */
	writel(0, uart.uart + UART_CR);

	/* Flush the transmit fifo. */
	lcr_h = readl(uart.uart + UART_LCR_H);
	lcr_h &= ~0x10;
	writel(lcr_h, uart.uart + UART_LCR_H);

	/* Reprogram. */
  	writel(ibrd, uart.uart + UART_IBRD);
	writel(fbrd, uart.uart + UART_FBRD);
	writel(0x70, uart.uart + UART_LCR_H);

	/* Enable */
	writel(0x301, uart.uart + UART_CR);
#endif
	return;
}

/*
  ======================================================================
  ======================================================================
  U-Boot Interface
  ======================================================================
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  serial_start
*/

void serial_start( void ) {
}

/*
  ----------------------------------------------------------------------
  serial_setbrg
*/

void
serial_setbrg(void)
{
#ifndef ACP_ISS
	if (0 == uart.uart)
		return;

	serial_exit();
	serial_init();
#endif

	return;
}

/*
  ----------------------------------------------------------------------
  serial_putc
*/

void
serial_putc( const char c )
{
#ifdef ACP_ISS
	*((unsigned char *)0xe0000200) = c;
#else
	if (0 == uart.uart)
		return;

	while (0 != (readl(uart.uart + UART_FR) & FR_TXFF))
		;

	if ('\n' == c) {
		writel('\r', uart.uart + UART_DR);
		while (0 != (readl(uart.uart + UART_FR) & FR_TXFF))
			;
	}

	writel(c, uart.uart + UART_DR);

	/*
	  The following is useful for printf debugging; get all the
	  characters out!
	*/
	while (0 == (readl(uart.uart + UART_FR) & FR_TXFE))
		;

	while (0 != (readl(uart.uart + UART_FR) & FR_BUSY))
		;
#endif

	return;
}

/*
  ----------------------------------------------------------------------
  serial_puts
*/

void
serial_puts(const char *s)
{
	//ACP_LOCK();

	while (*s)
		serial_putc(*s++);

	//ACP_UNLOCK();

	return;

}

/*
  ----------------------------------------------------------------------
  serial_getc
*/

int
serial_getc(void)
{
	int character;

#ifdef ACP_ISS
	while ((*((unsigned char *)0xe0000205) & 1) == 0)
		;

	return *((unsigned char *)0xe0000200);
#else
	if (0 == uart.uart)
		for (;;)
			;
	while (0 != (readl(uart.uart + UART_FR) & FR_RXFE))
		;

	character = readl(uart.uart + UART_DR);

	return character;
#endif
}

/*
  ----------------------------------------------------------------------
  serial_tstc
*/

int
serial_tstc(void)
{
	int return_value = 0;

#ifdef ACP_ISS
	return_value = ((*((unsigned char *)0xe0000205) & 1) != 0);
#else
	if (0 != uart.uart)
		return_value =
			(FR_RXFE != (readl(uart.uart + UART_FR) & FR_RXFE));
#endif

	return return_value;
}

/*
  ======================================================================
  ======================================================================
  Public
  ======================================================================
  ======================================================================
*/

/* Set printbuffer to non-zero initial values to keep it in the data section */
char printbuffer [ CFG_PBSIZE ] = { 1, 8, 0, 8, 8 };

/*
  ------------------------------------------------------------------------------
  serial_exit
*/

void
serial_exit(void)
{
	if (0 == uart.uart)
		return;

	/* Disable the UART. */
	writel(0, (uart.uart + UART_CR));

	/* Make sure all transmissions are finished. */
	while (0 == (readl(uart.uart + UART_FR) & FR_TXFE));
	while (0 != (readl(uart.uart + UART_FR) & FR_BUSY));

#ifndef CONFIG_AXXIA_ARM
	/* Turn off the timer. */
	writel(0, (uart.timer + TIMER_CONTROL));
#endif

	uart.uart = 0;
	
	return;
}

/*
  ------------------------------------------------------------------------------
  serial_early_init
*/

int
serial_early_init()
{
	clock_stuff_t clock_stuff;

	memset((void *)printbuffer, 0, CFG_PBSIZE);

	uart.uart = UART0_ADDRESS;
#ifndef CONFIG_AXXIA_ARM
	uart.timer = TIMER2;
#endif

	get_clock_stuff(CONFIG_BAUDRATE, &clock_stuff);
	axxia_serial_initialize(clock_stuff.divisor,
				clock_stuff.ibrd, clock_stuff.fbrd);

	return 0;
}

/*
  ----------------------------------------------------------------------
  serial_init
*/

int
serial_init()
{
	clock_stuff_t clock_stuff;

	memset((void *)printbuffer, 0, CFG_PBSIZE);
	uart.uart = UART0_ADDRESS;
#ifndef CONFIG_AXXIA_ARM
	uart.timer = TIMER2;
#endif
	/*get_clock_stuff(gd->baudrate, &clock_stuff);*/
	get_clock_stuff(CONFIG_BAUDRATE, &clock_stuff);
	axxia_serial_initialize(clock_stuff.divisor,
				clock_stuff.ibrd, clock_stuff.fbrd);

	return 0;
}
