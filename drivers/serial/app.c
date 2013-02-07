#include <common.h>
#include <config.h>
#include <asm/byteorder.h>

#ifdef CFG_APP3_SERIAL

#define	UART011_DR		0x0000
#define	UART011_ECR		0x0004
#define	UART011_FR		0x0018
#define	UART011_ILPR		0x0020
#define	UART011_IBRD		0x0024
#define	UART011_FBRD		0x0028
#define	UART011_LCR_H		0x002C
#define	UART011_CR		0x0030
#define	UART011_IFLS		0x0034
#define	UART011_IMSC		0x0038
#define	UART011_RIS		0x003C
#define	UART011_MIS		0x0040
#define	UART011_ICR		0x0044
#define	UART011_DMACR		0x0048

#define FCR_FIFO_EN     0x01		/* Fifo enable */
#define FCR_RXSR        0x02		/* Receiver soft reset */
#define FCR_TXSR        0x04		/* Transmitter soft reset */

#define MCR_DTR         0x01
#define MCR_RTS         0x02
#define MCR_DMA_EN      0x04
#define MCR_TX_DFR      0x08

#define LCR_WLS_MSK	0x03		/* character length slect mask */
#define LCR_WLS_5	0x00		/* 5 bit character length */
#define LCR_WLS_6	0x01		/* 6 bit character length */
#define LCR_WLS_7	0x02		/* 7 bit character length */
#define LCR_WLS_8	0x03		/* 8 bit character length */
#define LCR_STB		0x04		/* Number of stop Bits, off = 1, on = 1.5 or 2) */
#define LCR_PEN		0x08		/* Parity eneble */
#define LCR_EPS		0x10		/* Even Parity Select */
#define LCR_STKP	0x20		/* Stick Parity */
#define LCR_SBRK	0x40		/* Set Break */
#define LCR_BKSE	0x80		/* Bank select enable */

#define FR_RXFE     0x10
#define FR_TXFF     0x20

#define LCR_8N1		0x0070

#define LCRVAL LCR_8N1					            /* 8 data, 1 stop, no parity */
#define MCRVAL (MCR_DTR | MCR_RTS)			        /* RTS/DTR */
#define FCRVAL (FCR_FIFO_EN | FCR_RXSR | FCR_TXSR)	/* Clear & enable FIFOs */

#define	writel(v,a)	(*(volatile unsigned long*)(a)) = (v)
#define	readl(a)	(*(volatile unsigned long*)(a))

/*
  ======================================================================
*/

struct clock_stuff_ {

  int divisor;
  unsigned char ibrd;
  unsigned char fbrd;

};

typedef struct clock_stuff_ clock_stuff_t;

/*
  ----------------------------------------------------------------------
  get_clock_stuff_
*/

static int get_clock_stuff_( int baud_rate, clock_stuff_t * clock_stuff ) {

  unsigned long speed_;
  unsigned long ibrd_, fbrd_;

#if defined( LSI_ARCH_APP3K )
  speed_ = pll_get_clock( axi );
#elif defined( LSI_ARCH_APP3 )
  speed_ = pll_get_clock( arm_core );
#else
#error "Unknown Architecture"
#endif

  /*
    The UART clock is derived from the ARM core clock using the second
    timer (timer 1).  Each time timer 1 crosses zero, the UART clock
    gets toggled.  The timer load value acts as a divisor.

    Since the IBDR (integer part of the baud rate divisor) is a 16 bit
    quatity, find the minimum load value that will let the IBDR/FBDR
    result in the desired baud rate.
   */

  clock_stuff->divisor = 1;
 
  do {

    ibrd_ = ( speed_ / ++ clock_stuff->divisor ) / ( 16 * baud_rate );

  } while( 0xff < ibrd_ );

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

  fbrd_ = ( speed_ / clock_stuff->divisor ) % ( 16 * baud_rate );
  fbrd_ *= 128;
  fbrd_ += ( 16 * baud_rate );
  fbrd_ /= ( 2 * ( 16 * baud_rate ) );

  -- clock_stuff->divisor;
  clock_stuff->ibrd = ibrd_;
  clock_stuff->fbrd = fbrd_;

  /* that's all */
  return 0;

}

/*
  ======================================================================
  ======================================================================
  U-Boot Serial Interface
  ======================================================================
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  serial_init
*/

int serial_init( void ) {

  DECLARE_GLOBAL_DATA_PTR;

  clock_stuff_t clock_stuff_;

  get_clock_stuff_( gd->baudrate, & clock_stuff_ );
  * TIMER1_LOAD    = clock_stuff_.divisor;
  * TIMER1_CONTROL = 0xc0;
  writel(clock_stuff_.ibrd, APP3XX_UART_BASE + UART011_IBRD);
  writel(clock_stuff_.fbrd, APP3XX_UART_BASE + UART011_FBRD);
  writel(LCR_8N1, APP3XX_UART_BASE + UART011_LCR_H);
  writel(0x0301, APP3XX_UART_BASE + UART011_CR);
  /* Receive enable, Transmit enable,
   * uart enable */
  writel(0x0000, APP3XX_UART_BASE + UART011_IFLS);
  /* Trigger at 1/8 full */
  writel(0x0700, APP3XX_UART_BASE + UART011_IMSC);
  /* On read, return current masks for
   * RTIM, TXIm, RXIM interrupts */
  writel( 0x0000, APP3XX_UART_BASE + UART011_ECR);

  return 0;

}

/*
  ----------------------------------------------------------------------
  serial_setbrg
*/

void serial_setbrg( void ) {

  return;

}

/*
  ----------------------------------------------------------------------
  serial_putc
*/

void serial_putc( const char c ) {

  while( readl( APP3XX_UART_BASE + UART011_FR ) & FR_TXFF ) ;

  if( '\n' == c ) {

    writel( '\r', ( APP3XX_UART_BASE + UART011_DR ) );
    while( readl( APP3XX_UART_BASE + UART011_FR ) & FR_TXFF ) ;

  }

  writel( c, ( APP3XX_UART_BASE + UART011_DR ) );
  return;

}

/*
  ----------------------------------------------------------------------
  serial_puts
*/

void serial_puts( const char * s ) {

  while( * s ) {

    serial_putc( * s ++ );

  }

  return;

}

/*
  ----------------------------------------------------------------------
  serial_getc
*/

int serial_getc( void ) {

  while( readl( APP3XX_UART_BASE + UART011_FR) & FR_RXFE ) ;
  return readl( APP3XX_UART_BASE + UART011_DR );

}

/*
  ----------------------------------------------------------------------
  serial_tstc
*/

int serial_tstc( void ) {

  return ( readl( APP3XX_UART_BASE + UART011_FR ) & FR_RXFE ) == 0;

}

#endif /* CFG_APP3_SERIAL */
