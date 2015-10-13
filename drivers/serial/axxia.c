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
#include <asm/io.h>
#include <asm/byteorder.h>
#include <serial.h>
#include <watchdog.h>

/*
  ======================================================================
  ======================================================================
  Private
  ======================================================================
  ======================================================================
*/

DECLARE_GLOBAL_DATA_PTR;

static unsigned int baudrate = CONFIG_BAUDRATE;

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

/*
  ------------------------------------------------------------------------------
  __serial_start
*/

static int
__serial_start(void)
{
	unsigned long lcr_h;
	unsigned long ibrd;
	unsigned long fbrd;
	ncp_uint32_t per_clock; 

	do {
		for (;;) {
			int rc;

			rc = acp_clock_get(clock_peripheral,
					   (ncp_uint32_t *)&per_clock);

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

	ibrd = per_clock / (16 * baudrate);

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

	fbrd = per_clock % (16 * baudrate);
	fbrd *= 128;
	fbrd += (16 * baudrate);
	fbrd /= (2 * (16 * baudrate));

	/*
	  Set up the timer.
	*/

#if defined(CONFIG_AXXIA_344X) || \
  defined(CONFIG_AXXIA_342X) || \
  defined(CONFIG_AXXIA_25xx)
	writel(0, (TIMER2 + TIMER_CONTROL));
	writel((per_clock / UART_CLOCK_SPEED) - 1, (TIMER2 + TIMER_LOAD));
	writel((TIMER_CONTROL_ENABLE | TIMER_CONTROL_MODE),
	       (TIMER2 + TIMER_CONTROL));
#endif

	/*
	  Wait for the end of transmission or reception of the
	  current character.

	  How should this be done for reception?
	*/

	while (0 == (readl(UART0_ADDRESS + UART_FR) & FR_TXFE))
		WATCHDOG_RESET();

	while (0 != (readl(UART0_ADDRESS + UART_FR) & FR_BUSY))
		WATCHDOG_RESET();

	/* Disable the UART. */
	writel(0, UART0_ADDRESS + UART_CR);

	/* Flush the transmit fifo. */
	lcr_h = readl(UART0_ADDRESS + UART_LCR_H);
	lcr_h &= ~0x10;
	writel(lcr_h, UART0_ADDRESS + UART_LCR_H);

	/* Reprogram. */
  	writel(ibrd, UART0_ADDRESS + UART_IBRD);
	writel(fbrd, UART0_ADDRESS + UART_FBRD);
	writel(0x70, UART0_ADDRESS + UART_LCR_H);

	/* Enable */
	writel(0x301, UART0_ADDRESS + UART_CR);

	return 0;
}

/*
  -------------------------------------------------------------------------------
  __serial_stop
*/

static int
__serial_stop(void)
{
	/* Disable the UART. */
	writel(0, (UART0_ADDRESS + UART_CR));

	/* Make sure all transmissions are finished. */
	while (0 == (readl(UART0_ADDRESS + UART_FR) & FR_TXFE))
		WATCHDOG_RESET();

	while (0 != (readl(UART0_ADDRESS + UART_FR) & FR_BUSY))
		WATCHDOG_RESET();

	/* Turn off the timer. */
#if defined(CONFIG_AXXIA_344X) || \
  defined(CONFIG_AXXIA_342X) || \
  defined(CONFIG_AXXIA_25xx)
	writel(0, (TIMER2 + TIMER_CONTROL));
#endif

	return 0;
}

/*
  ----------------------------------------------------------------------
  __serial_setbrg
*/

static void
__serial_setbrg(void)
{
	baudrate = gd->baudrate;
	__serial_stop();
	__serial_start();

	return;
}

/*
  ----------------------------------------------------------------------
  __serial_getc
*/

static int
__serial_getc(void)
{
	int character;

	while (0 != (readl(UART0_ADDRESS + UART_FR) & FR_RXFE))
		WATCHDOG_RESET();

	character = readl(UART0_ADDRESS + UART_DR);

	return character;
}

/*
  ----------------------------------------------------------------------
  __serial_tstc
*/

static int
__serial_tstc(void)
{
	int return_value = 0;

	return_value = (FR_RXFE != (readl(UART0_ADDRESS + UART_FR) & FR_RXFE));

	return return_value;
}

/*
  ----------------------------------------------------------------------
  __serial_putc
*/

static void
__serial_putc( const char c )
{
	while (0 != (readl(UART0_ADDRESS + UART_FR) & FR_TXFF))
		WATCHDOG_RESET();

	if ('\n' == c) {
		writel('\r', UART0_ADDRESS + UART_DR);
		while (0 != (readl(UART0_ADDRESS + UART_FR) & FR_TXFF))
			WATCHDOG_RESET();
	}

	writel(c, UART0_ADDRESS + UART_DR);

	/*
	  The following is useful for printf debugging; get all the
	  characters out!
	*/

	while (0 == (readl(UART0_ADDRESS + UART_FR) & FR_TXFE))
		WATCHDOG_RESET();

	while (0 != (readl(UART0_ADDRESS + UART_FR) & FR_BUSY))
		WATCHDOG_RESET();

	return;
}

/*
  ----------------------------------------------------------------------
  __serial_puts
*/

static void
__serial_puts(const char *s)
{
	while (*s)
		__serial_putc(*s++);

	return;

}

/*
  ======================================================================
  ======================================================================
  Public
  ======================================================================
  ======================================================================
*/

static struct serial_device axxia_serial_device0 = {
	.name = "Axxia uart0",
	.start = __serial_start,
	.stop = __serial_stop,
	.setbrg = __serial_setbrg,
	.getc = __serial_getc,
	.tstc = __serial_tstc,
	.putc = __serial_putc,
	.puts = __serial_puts
};

/*
  ------------------------------------------------------------------------------
  default_serial_console
*/

__weak struct serial_device *
default_serial_console(void)
{
	return &axxia_serial_device0;
}

/*
  ----------------------------------------------------------------------
  axxia_serial_initialize
*/

void
axxia_serial_initialize(void)
{
	serial_register(&axxia_serial_device0);
}
