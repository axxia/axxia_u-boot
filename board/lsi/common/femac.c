/*
 *  drivers/net/lsi_femac.c
 *
 *  Copyright (C) 2011 LSI (john.jacques@lsi.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * A Driver for the custom MAC included in LSI ASICs (APP3, APP3K, and ACP).
 *
 * -- Hardware Bugs -- With Software Fixes --
 *
 * -1- (APP ONLY)
 * The MAC (or any other device) can only DMA to the alias (0x6nnn nnnn).
 * For now, all addresses written to the parts will be modified.  The top
 * nibble will be overwritten by 0x6.
 * -2-
 * When the generation bits are equal, as are the pointers, instead of
 * considering the fifo empty (which it is) hardware considers it FULL.
 * In concequence, one descriptor will always be wasted...
 * -3-
 * When the MAC sends a packet, it zeros out the "data transfer length"
 * field...
 *
 */

#include <config.h>
#if defined(CONFIG_LSI_NET)
#if !defined(CONFIG_TRACER)
#include <common.h>
#include <command.h>
#include <net.h>
#include <exports.h>
#include <asm/io.h>
#include <asm/cache.h>
#include <asm/global_data.h>

/*
  Allow debugging output?  Removing it reduces the size of U-Boot...
*/

/*#define ALLOW_DEBUGGING*/

/*#define DUMP_STATS*/
/*#define EH_STATS*/

#ifdef EH_STATS
typedef struct {
	unsigned long rx_calls;
	unsigned long rx_packet_available;
	unsigned long rx_packet_ok;
	unsigned long rx_packet_overflow;
	unsigned long rx_packet_crc;
	unsigned long rx_packet_alignment;
	unsigned long rx_packet_bad_address;
	unsigned long tx_calls;
	unsigned long tx_packet_sent;
} eh_stats_t;

static eh_stats_t *eh_stats = (eh_stats_t *)0xf0a00000;
static int eh_stats_initialized = 0;
#endif

/*
  Dump Descriptors and Packets...
*/

#undef DUMP_DESCRIPTOR
#define DUMP_DESCRIPTOR
#define DUMP_DESCRIPTOR_COMPACT
#ifdef DUMP_DESCRIPTOR
#define DUMP_DESCRIPTOR_( address ) dump_descriptor_( __LINE__, ( address ) )
#else  /* DUMP_DESCRIPTOR */
#define DUMP_DESCRIPTOR_( address )
#endif /* DUMP_DESCRIPTOR */

#undef DUMP_PACKETS
#define DUMP_PACKETS
#ifdef DUMP_PACKETS
#define DUMP_PACKET( direction, data, length ) \
dump_packet_( direction, data, length );
#else  /* DUMP_PACKETS */
#define DUMP_PACKET( description, data, length )
#endif /* DUMP_PACKETS */

/*
  Debugging...
*/

#undef DEBUG
/*#define DEBUG*/
#ifdef DEBUG
#define DEBUG_PRINT( format, args... ) do { \
printf( "app3_nic:%s:%d - DEBUG - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else  /* DEBUG */
#define DEBUG_PRINT( format, args... )
#endif /* DEBUG */

#undef TX_DEBUG
/*#define TX_DEBUG*/
#ifdef TX_DEBUG
#define TX_DEBUG_PRINT( format, args... ) do { \
printf( "app3_nic:%s:%d - TX_DEBUG - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else  /* TX_DEBUG */
#define TX_DEBUG_PRINT( format, args... )
#endif /* TX_DEBUG */

#undef RX_DEBUG
/*#define RX_DEBUG*/
#ifdef RX_DEBUG
#define RX_DEBUG_PRINT( format, args... ) do { \
printf( "app3_nic:%s:%d - RX_DEBUG - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else  /* RX_DEBUG */
#define RX_DEBUG_PRINT( format, args... )
#endif /* RX_DEBUG */

/*
  Tracing...
*/

#undef TRACE
/*#define TRACE_*/
#ifdef TRACE
#define TRACE_BEGINNING( format, args... ) do { \
printf( "app3_nic:%s:%d - TRACE BEGINNING - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#define TRACE_ENDING( format, args... ) do { \
printf( "app3_nic:%s:%d - TRACE ENDING - ", __FUNCTION__, __LINE__ ); \
printf( format, ##args ); \
} while( 0 );
#else  /* TRACE */
#define TRACE_BEGINNING( format, args... )
#define TRACE_ENDING( format, args... )
#endif /* TRACE */

static int initialized_ = 0;
static int rx_debug = 0;
static int rx_allow_all = 0;
static int dump_packets = 0;
static int dump_descriptors = 0;
static int loopback = 0;
DECLARE_GLOBAL_DATA_PTR;

/*
  ======================================================================
  ======================================================================
  IO Access Logging
  ======================================================================
  ======================================================================
*/
int test( void );
#undef LOG_IO_ACCESS
/*#define LOG_IO_ACCESS*/
#ifdef LOG_IO_ACCESS
static inline unsigned long
readio( unsigned long address )
{
	unsigned long value;
	value = acpreadio( ( unsigned * ) address );
	printf( " read: 0x%08lx from 0x%08lx\n", value, address );
	return value;
}
static inline void
writeio( unsigned long value, unsigned long address )
{
	acpwriteio( value, ( unsigned * ) address );
	printf( "wrote: 0x%08lx   to 0x%08lx\n", value, address );
	return;
}
#else  /* LOG_IO_ACCESS */
#define readio( address ) \
acpreadio( ( unsigned long * ) ( address ) )
#define writeio( value, address ) \
acpwriteio( ( value ), ( unsigned long * ) ( address ) )
#endif /* LOG_IO_ACCESS */

/* -- -- */

/*#define PHY_ADDRESS_ 0x1e*/
#define PHY_ADDRESS_ 0

/* Set to -1 to auto-detect. */
static int phy_address_ = PHY_ADDRESS_;
/*static int phy_address_ = -1;*/

static int phy_enable_( int );

/*
  ======================================================================
  ======================================================================
  ======================================================================

  NIC Interface

  ======================================================================
  ======================================================================
  ======================================================================
*/

#define DESCRIPTOR_GRANULARITY 64
#define BUFFER_GRANULARITY 64

#undef ALIGN
#define ALIGN( address, bytes ) \
( ( ( unsigned long ) ( address ) + ( ( unsigned long ) ( bytes ) - 1UL ) ) & \
~ ( ( unsigned long ) ( bytes ) - 1UL ) )

#define ALIGN_OFFSET( address, bytes ) \
( ALIGN( ( address ), ( bytes ) ) - ( unsigned long ) ( address ) )

#define ALIGN64B( address ) \
( ( ( ( unsigned long ) ( address ) + \
( 64UL - 1UL ) ) & ~ ( 64UL - 1UL ) ) )

#define ALIGN64B_OFFSET( address ) \
( ALIGN64B( address ) - ( unsigned long ) ( address ) )

/* SMII Status ------------------------------------------------------ */

#define APP3XXNIC_RX_SMII_STATUS        ( APP3XXNIC_RX_BASE + 0x10 )
#define APP3XXNIC_RX_SMII_STATUS_SPEED  0x01
#define APP3XXNIC_RX_SMII_STATUS_DUPLEX 0x02
#define APP3XXNIC_RX_SMII_STATUS_LINK   0x04
#define APP3XXNIC_RX_SMII_STATUS_JABBER 0x08
#define APP3XXNIC_RX_SMII_STATUS_FCD    0x10 /* False Carrier Detect */

#define SMII_SPEED_100( smii_status_ ) \
( 0 != ( smii_status_ & APP3XXNIC_RX_SMII_STATUS_SPEED ) )
#define SMII_DUPLEX( smii_status_ ) \
( 0 != ( smii_status_ & APP3XXNIC_RX_SMII_STATUS_DUPLEX ) )
#define SMII_LINK( smii_status_ ) \
( 0 != ( smii_status_ & APP3XXNIC_RX_SMII_STATUS_LINK ) )
#define SMII_JABBER( smii_status_ ) \
( 0 != ( smii_status_ & APP3XXNIC_RX_SMII_STATUS_JABBER ) )

/* Receive Configuration -------------------------------------------- */

#define APP3XXNIC_RX_CONF          ( APP3XXNIC_RX_BASE + 0x004c )
#define APP3XXNIC_RX_CONF_ENABLE   0x0001
/* Pass Any Packet */
#define APP3XXNIC_RX_CONF_PAP      0x0002
#define APP3XXNIC_RX_CONF_JUMBO9K  0x0008
#define APP3XXNIC_RX_CONF_STRIPCRC 0x0010
/* Accept All MAC Types */
#define APP3XXNIC_RX_CONF_AMT      0x0020
/* Accept Flow Control */
#define APP3XXNIC_RX_CONF_AFC      0x0040
/* Enable VLAN */
#define APP3XXNIC_RX_CONF_VLAN     0x0200
/* RX MAC Speed, 1=100MBS */
#define APP3XXNIC_RX_CONF_SPEED    0x0800
/* 1=Duplex Mode */
#define APP3XXNIC_RX_CONF_DUPLEX   0x1000
/* 1=Enable */
#define APP3XXNIC_RX_CONF_LINK     0x2000
/* Determines the action taken when the FE MAC
   receives an FC packet in FD mode.*/
#define APP3XXNIC_RX_CONF_RXFCE    0x4000
/* Controls the insertion of FC packets
   by the MAC transmitter. */
#define APP3XXNIC_RX_CONF_TXFCE    0x8000

/* Receive Stat Overflow -------------------------------------------- */

#define APP3XXNIC_RX_STAT_OVERFLOW ( APP3XXNIC_RX_BASE + 0x278 )

/* Receive Stat Packet OK ------------------------------------------- */

#define APP3XXNIC_RX_STAT_PACKET_OK ( APP3XXNIC_RX_BASE + 0x2c0 )

/* Receive Stat CRC Error ------------------------------------------- */

#define APP3XXNIC_RX_STAT_CRC_ERROR ( APP3XXNIC_RX_BASE + 0x2c8 )

/* Receive Stat Align Error ----------------------------------------- */

#define APP3XXNIC_RX_STAT_ALIGN_ERROR ( APP3XXNIC_RX_BASE + 0x2e8 )

/* Receive Ethernet Mode -------------------------------------------- */

#define APP3XXNIC_RX_MODE ( APP3XXNIC_RX_BASE + 0x0800 )
#define APP3XXNIC_RX_MODE_ETHERNET_MODE_ENABLE 0x00001

/* Receive Soft Reset ----------------------------------------------- */

#define APP3XXNIC_RX_SOFT_RESET ( APP3XXNIC_RX_BASE + 0x0808 )
#define APP3XXNIC_RX_SOFT_RESET_MAC_0 0x00001

/* Receive Internal Interrupt Control ------------------------------- */

#define APP3XXNIC_RX_INTERNAL_INTERRUPT_CONTROL \
( APP3XXNIC_RX_BASE + 0xc00 )
#define APP3XXNIC_RX_INTERNAL_INTERRUPT_CONTROL_MAC_0 0x1

/* Receive External Interrupt Control ------------------------------- */

#define APP3XXNIC_RX_EXTERNAL_INTERRUPT_CONTROL \
( APP3XXNIC_RX_BASE + 0xc04 )
#define APP3XXNIC_RX_EXTERNAL_INTERRUPT_CONTROL_MAC_0 0x1

/* Receive Interrupt Status ----------------------------------------- */

#define APP3XXNIC_RX_INTERRUPT_STATUS ( APP3XXNIC_RX_BASE + 0xc20 )
#define APP3XXNIC_RX_INTERRUPT_EXTERNAL_STATUS_MAC_0 0x10
#define APP3XXNIC_RX_INTERRUPT_INTERNAL_STATUS_MAC_0 0x1

/* Transmit Watermark ----------------------------------------------- */

#define APP3XXNIC_TX_WATERMARK (APP3XXNIC_TX_BASE + 0x18 )
#define APP3XXNIC_TX_WATERMARK_TXCONFIG_DTPA_ASSERT 0x8000
#define APP3XXNIC_TX_WATERMARK_TXCONFIG_DTPA_DISABLE 0x4000
#define APP3XXNIC_TX_WATERMARK_TXCONFIG_DTPA_WATER_MARK_HIGH 0x3f00
#define APP3XXNIC_TX_WATERMARK_TXCONFIG_DTPA_WATER_MARK_LOW 0x3f

/* Swap Source Address Registers ------------------------------------ */

#define APP3XXNIC_SWAP_SOURCE_ADDRESS_2 ( APP3XXNIC_TX_BASE + 0x20 )
#define APP3XXNIC_SWAP_SOURCE_ADDRESS_1 ( APP3XXNIC_TX_BASE + 0x24 )
#define APP3XXNIC_SWAP_SOURCE_ADDRESS_0 ( APP3XXNIC_TX_BASE + 0x28 )

/* Transmit Extended Configuration ---------------------------------- */

#define APP3XXNIC_TX_EXTENDED_CONF ( APP3XXNIC_TX_BASE + 0x0030 )
#define APP3XXNIC_TX_EXTENDED_CONF_TRANSMIT_COLLISION_WATERMARK_LEVEL 0xf000
#define APP3XXNIC_TX_EXTENDED_CONF_EXCESSIVE_DEFFERED_PACKET_DROP 0x200
#define APP3XXNIC_TX_EXTENDED_CONF_JUMBO9K 0x100
#define APP3XXNIC_TX_EXTENDED_CONF_LATE_COLLISION_WINDOW_COUNT 0xff

/* Transmit Half Duplex Configuration ------------------------------- */

#define APP3XXNIC_TX_HALF_DUPLEX_CONF ( APP3XXNIC_TX_BASE + 0x34 )
#define APP3XXNIC_TX_HALF_DUPLEX_CONF_RANDOM_SEED_VALUE 0xff

/* Transmit Configuration ------------------------------------------- */

#define APP3XXNIC_TX_CONF ( APP3XXNIC_TX_BASE + 0x50 )
#define APP3XXNIC_TX_CONF_ENABLE_SWAP_SA 0x8000
#define APP3XXNIC_TX_CONF_LINK           0x2000
#define APP3XXNIC_TX_CONF_DUPLEX         0x1000
#define APP3XXNIC_TX_CONF_SPEED          0x0800
#define APP3XXNIC_TX_CONF_XBK_RST_RX_NTX 0x0600
#define APP3XXNIC_TX_CONF_IFG            0x01f0
#define APP3XXNIC_TX_CONF_APP_CRC_ENABLE 0x0004
#define APP3XXNIC_TX_CONF_PAD_ENABLE     0x0002
#define APP3XXNIC_TX_CONF_ENABLE         0x0001

#define TX_CONF_SET_IFG( tx_configuration_, ifg_ ) do { \
( tx_configuration_ ) &= ~ APP3XXNIC_TX_CONF_IFG; \
( tx_configuration_ ) |= ( ( ifg_ & 0x1f ) << 4 ); \
} while( 0 );

/* Transmit Time Value Configuration -------------------------------- */

#define APP3XXNIC_TX_TIME_VALUE_CONF ( APP3XXNIC_TX_BASE + 0x5c )
#define APP3XXNIC_TX_TIME_VALUE_CONF_PAUSE_VALUE 0xffff

/* Transmit Stat Packet OK ------------------------------------------ */

#define APP3XXNIC_TX_STAT_PACKET_OK ( APP3XXNIC_TX_BASE + 0x318 )

/* Transmit Mode ---------------------------------------------------- */

#define APP3XXNIC_TX_MODE ( APP3XXNIC_TX_BASE + 0x800 )
#define APP3XXNIC_TX_MODE_ETHERNET_MODE_ENABLE 0x1

/* Transmit Soft Reset ---------------------------------------------- */

#define APP3XXNIC_TX_SOFT_RESET ( APP3XXNIC_TX_BASE + 0x808 )
#define APP3XXNIC_TX_SOFT_RESET_MAC_0 0x1

/* Transmit Interrupt Control --------------------------------------- */

#define APP3XXNIC_TX_INTERRUPT_CONTROL ( APP3XXNIC_TX_BASE + 0xc00 )
#define APP3XXNIC_TX_INTERRUPT_CONTROL_MAC_0 0x1

/* Transmit Interrupt Status ---------------------------------------- */

#define APP3XXNIC_TX_INTERRUPT_STATUS ( APP3XXNIC_TX_BASE + 0xc20 )
#define APP3XXNIC_TX_INTERRUPT_STATUS_MAC_0 0x1

/* */

#define APP3XXNIC_DMA_PCI_CONTROL ( APP3XXNIC_DMA_BASE + 0x00 )

/* */

#define APP3XXNIC_DMA_CONTROL ( APP3XXNIC_DMA_BASE + 0x08 )

/* DMA Interrupt Status --------------------------------------------- */

#define APP3XXNIC_DMA_INTERRUPT_STATUS ( APP3XXNIC_DMA_BASE + 0x18 )
#define APP3XXNIC_DMA_INTERRUPT_STATUS_RX 0x2
#define APP3XXNIC_DMA_INTERRUPT_STATUS_TX 0x1

#define RX_INTERRUPT( dma_interrupt_status_ ) \
( 0 != ( dma_interrupt_status_ & APP3XXNIC_DMA_INTERRUPT_STATUS_RX ) )
#define TX_INTERRUPT( dma_interrupt_status_ ) \
( 0 != ( dma_interrupt_status_ & APP3XXNIC_DMA_INTERRUPT_STATUS_TX ) )

/* DMA Interrupt Enable --------------------------------------------- */

#define APP3XXNIC_DMA_INTERRUPT_ENABLE ( APP3XXNIC_DMA_BASE + 0x1c )
#define APP3XXNIC_DMA_INTERRUPT_ENABLE_RECEIVE 0x1
#define APP3XXNIC_DMA_INTERRUPT_ENABLE_TRANSMIT 0x2

/* DMA Receive Queue Base Address ----------------------------------- */

#define APP3XXNIC_DMA_RX_QUEUE_BASE_ADDRESS ( APP3XXNIC_DMA_BASE + 0x30 )

/* DMA Receive Queue Size ------------------------------------------- */

#define APP3XXNIC_DMA_RX_QUEUE_SIZE ( APP3XXNIC_DMA_BASE + 0x34 )

/* DMA Transmit Queue Base Address ---------------------------------- */

#define APP3XXNIC_DMA_TX_QUEUE_BASE_ADDRESS ( APP3XXNIC_DMA_BASE + 0x38 )

/* DMA Transmit Queue Size ------------------------------------------ */

#define APP3XXNIC_DMA_TX_QUEUE_SIZE ( APP3XXNIC_DMA_BASE + 0x3c )

/* DMA Recevie Tail Pointer Address --------------------------------- */

#define APP3XXNIC_DMA_RX_TAIL_POINTER_ADDRESS ( APP3XXNIC_DMA_BASE + 0x48 )

/* DMA Transmit Tail Pointer Address -------------------------------- */

#define APP3XXNIC_DMA_TX_TAIL_POINTER_ADDRESS ( APP3XXNIC_DMA_BASE + 0x4c )

/* DMA Receive Head Pointer ----------------------------------------- */

#define APP3XXNIC_DMA_RX_HEAD_POINTER ( APP3XXNIC_DMA_BASE + 0x50 )
#define APP3XXNIC_DMA_RX_HEAD_POINTER_GB      0x100000
#define APP3XXNIC_DMA_RX_HEAD_POINTER_POINTER 0x0fffff

/* DMA Receive Tail Pointer Local Copy ------------------------------ */

#define APP3XXNIC_DMA_RX_TAIL_POINTER_LOCAL_COPY \
( APP3XXNIC_DMA_BASE + 0x54 )
#define APP3XXNIC_DMA_RX_TAIL_POINTER_LOCAL_COPY_GB      0x100000
#define APP3XXNIC_DMA_RX_TAIL_POINTER_LOCAL_COPY_POINTER 0x0fffff

/* DMA Transmit Head Pointer ---------------------------------------- */

#define APP3XXNIC_DMA_TX_HEAD_POINTER ( APP3XXNIC_DMA_BASE + 0x58 )
#define APP3XXNIC_DMA_TX_HEAD_POINTER_GB      0x100000
#define APP3XXNIC_DMA_TX_HEAD_POINTER_POINTER 0x0fffff

/* DMA Transmit Tail Pointer Local Copy ----------------------------- */

#define APP3XXNIC_DMA_TX_TAIL_POINTER_LOCAL_COPY \
( APP3XXNIC_DMA_BASE + 0x5c )
#define APP3XXNIC_DMA_TX_TAIL_POINTER_LOCAL_COPY_GB      0x100000
#define APP3XXNIC_DMA_TX_TAIL_POINTER_LOCAL_COPY_POINTER 0x0fffff

/*
  ======================================================================
  ======================================================================
  ======================================================================

  Prototypes

  ======================================================================
  ======================================================================
  ======================================================================
*/

extern int  eth_init( bd_t * );
extern void eth_halt( void );
extern int  eth_rx( void );
extern int  eth_send( volatile void *, int );

/*
  Data Structures.
*/

typedef struct {

#ifdef CONFIG_ACP

	/* Word 0 */
	unsigned long                         : 24;
	/* big endian to little endian */
	unsigned long byte_swapping_on        : 1;
	unsigned long                         : 1;
	unsigned long interrupt_on_completion : 1;
	unsigned long end_of_packet           : 1;
	unsigned long start_of_packet         : 1;
	unsigned long write                   : 1;
	/* 00=Fill|01=Block|10=Scatter */
	unsigned long transfer_type           : 2;

	/* Word 1 */
	unsigned long pdu_length           : 16;
	unsigned long data_transfer_length : 16;

	/* Word 2 */
	unsigned long target_memory_address;

	/* Word 3 */
	unsigned long host_data_memory_pointer;

#else  /* CONFIG_ACP */

	/* Word 0 */
	/* 00=Fill|01=Block|10=Scatter */
	unsigned long transfer_type           : 2;
	unsigned long write                   : 1;
	unsigned long start_of_packet         : 1;
	unsigned long end_of_packet           : 1;
	unsigned long interrupt_on_completion : 1;
	unsigned long                         : 1;
	/* big endian to little endian */
	unsigned long byte_swapping_on        : 1;
	unsigned long                         : 24;

	/* Word 1 */
	unsigned long data_transfer_length : 16;
	unsigned long pdu_length           : 16;

	/* Word 2 */
	unsigned long target_memory_address;

	/* Word 3 */
	unsigned long host_data_memory_pointer;

#endif /* CONFIG_ACP */

} __attribute__ ( ( packed ) ) app3xxnic_dma_descriptor_t;

typedef union {
	unsigned long raw;

	struct {
#ifdef CONFIG_ACP
		unsigned long                : 11;
		unsigned long generation_bit : 1;
		unsigned long offset         : 20;
#else  /* CONFIG_ACP */
		unsigned long offset         : 20;
		unsigned long generation_bit : 1;
		unsigned long                : 11;
#endif /* CONFIG_ACP */
	} __attribute__ ( ( packed ) ) bits;
} __attribute__ ( ( packed ) ) app3xxnic_queue_pointer_t;

static inline app3xxnic_queue_pointer_t
swab_queue_pointer( app3xxnic_queue_pointer_t old_queue )
{
	app3xxnic_queue_pointer_t new_queue;

	new_queue.raw = swab32( old_queue.raw );

	return new_queue;
}

/*
  Number of descriptors and buffers.

  ----- NOTES -----

  1) At least 64 descriptors must be allocated for the receive and
  transmit descriptor rings.  The size of each ring must be a
  multiple of 64 descriptors.  The buffer pointed to by each
  descriptor must be at least 64 bytes and a multiple of 64 bytes.
  In the driver, transmit buffers will be allocated as needed;
  therefore no transmit buffers are allocated up front.

  2) Make sure to update CFG_MALLOC_LEN when changing the following!
  For now, 2048 bytes for descriptors + 8192 bytes for receive
  buffers or 10240 bytes or 10k bytes.  In addition, the descriptor
  rings and buffer space must be 64 byte aligned so an additional
  64 bytes will be allocated for the descriptor rings and receive
  buffer or 192 bytes.

  3) In this implementation, the available buffer memory will be
  evenly divided among the descriptors.

  4) There is a bug in the hardware such that if the receive
  descriptor queue is empty (tail and head are equal) the
  hardware thinks it is full and won't transfer packets.  So,
  for now, keep one descriptor between them always.
*/

#define RX_NUMBER_OF_DESCRIPTORS 1024
#define RX_BUFFER_SIZE ( 128 * 1024 )
#define RX_BUFFER_PER_DESCRIPTOR \
( RX_BUFFER_SIZE / RX_NUMBER_OF_DESCRIPTORS )

static void * memory;

static unsigned rx_number_of_descriptors = RX_NUMBER_OF_DESCRIPTORS;
static unsigned rx_buffer_size = RX_BUFFER_SIZE;
static unsigned rx_buffer_per_descriptor = RX_BUFFER_PER_DESCRIPTOR;

static app3xxnic_dma_descriptor_t * rx_descriptors_;
static void * rx_buffer_;
static int rx_enabled_ = 0;
static app3xxnic_queue_pointer_t rx_tail_copy_;
static volatile app3xxnic_queue_pointer_t * rx_tail_;
static app3xxnic_queue_pointer_t rx_head_;

#define TX_NUMBER_OF_DESCRIPTORS 512
#define TX_BUFFER_SIZE ( 64 * 1024 )

static app3xxnic_dma_descriptor_t * tx_descriptors_;
static void * tx_buffer_;
static int tx_enabled_ = 0;
static app3xxnic_queue_pointer_t tx_tail_copy_;
static volatile app3xxnic_queue_pointer_t * tx_tail_;
static app3xxnic_queue_pointer_t tx_head_;

/*
  ======================================================================
  ======================================================================
  ======================================================================
  Test Functions.
  ======================================================================
  ======================================================================
  ======================================================================
*/

static void
dump_configuration(void)
{
	printf("RX: CONF:0x%lx MODE:0x%lx VLAN:0x%lx\n",
	       readio(APP3XXNIC_RX_CONF),
	       readio(APP3XXNIC_RX_MODE),
	       readio(APP3XXNIC_RX_BASE+0x1d0));
	printf("TX: WM:0x%lx EXCONF:0x%lx CONF:0x%lx TVCONF:0x%lx MODE:0x%lx\n",
	       readio(APP3XXNIC_TX_WATERMARK),
	       readio(APP3XXNIC_TX_EXTENDED_CONF),
	       readio(APP3XXNIC_TX_CONF),
	       readio(APP3XXNIC_TX_TIME_VALUE_CONF),
	       readio(APP3XXNIC_TX_MODE));
}

static void
dump_rx_stats(void)
{
	printf("RX: SMII:0x%lx VLAN:0x%lx OK:0x%lx OV:0x%lx CRC:0x%lx "
	       "ALIGN:0x%lx US:0x%lx\n",
	       readio(APP3XXNIC_RX_SMII_STATUS),
	       readio(APP3XXNIC_RX_BASE+0x270),
	       readio(APP3XXNIC_RX_STAT_PACKET_OK),
	       readio(APP3XXNIC_RX_STAT_OVERFLOW),
	       readio(APP3XXNIC_RX_STAT_CRC_ERROR),
	       readio(APP3XXNIC_RX_STAT_ALIGN_ERROR),
	       readio(APP3XXNIC_RX_BASE+0x280));
	printf("RX counts: 64:0x%lx 65_127:0x%lx 128_255:0x%lx 256_511:0x%lx "
	       "512_1023:0x%lx 1024_MAX:0x%lx OV:0x%lx\n",
	       readio(APP3XXNIC_RX_BASE+0x288),
	       readio(APP3XXNIC_RX_BASE+0x290),
	       readio(APP3XXNIC_RX_BASE+0x298),
	       readio(APP3XXNIC_RX_BASE+0x2a0),
	       readio(APP3XXNIC_RX_BASE+0x2a8),
	       readio(APP3XXNIC_RX_BASE+0x2b0),
	       readio(APP3XXNIC_RX_BASE+0x2b8));
}

/*
  ----------------------------------------------------------------------
  lsi_femac_receive_test
*/

void
lsi_femac_receive_test( void )
{

	bd_t * bd = gd->bd;
	int packets_received = 0;

	rx_debug = 1;
	rx_allow_all = 1;
	dump_packets = 1;
	dump_descriptors = 1;
	eth_halt( );

	if( 0 > eth_init( bd ) ) { eth_halt( ); return; }
	dump_configuration( );

	for( ; ; ) {

		if( 0 != eth_rx( ) ) { ++ packets_received; }
		if( ctrlc( ) ) { break; }
	}

	dump_descriptors = 0;
	dump_packets = 0;
	rx_allow_all = 0;
	rx_debug = 0;
	printf( "NIC Receive Test Interrupted.  Received %d packets.\n",
		packets_received );
	dump_rx_stats();
	eth_halt( );

	return;

}

/*
  ----------------------------------------------------------------------
  lsi_femac_loopback_test
*/

typedef struct {

	void * address;
	app3xxnic_queue_pointer_t queue_pointer;

} packet_log_header_t;

#define MAX_PACKET_SIZE (1536 + sizeof(packet_log_header_t))
#define PACKET_LOG_NUMBER 100

void
lsi_femac_loopback_test( void )
{

	bd_t * bd = gd->bd;
	int packet_size;
	void * packet = ( void * ) ( NetRxPackets [ 0 ] );
	packet_log_header_t * packet_log_headers;
	unsigned long packet_log_header_index = 0;
	void * packet_log;

	rx_allow_all = 1;
	rx_debug = 1;
	loopback = 1;

	packet_log_headers = malloc(PACKET_LOG_NUMBER * MAX_PACKET_SIZE);

	if (NULL == packet_log_headers) {
		printf("Couldn't allocate a packet log!\n");
		return;
	}

	packet_log = ( void * )
		( packet_log_headers +
		  ( PACKET_LOG_NUMBER * sizeof( packet_log_header_t ) ) );

	eth_halt( );
	if( 0 > eth_init( bd ) ) { eth_halt( ); return; }
	dump_configuration( );

	for( ; ; ) {

		if( 0 != ( packet_size = eth_rx( ) ) ) {

			if( packet_log_header_index < PACKET_LOG_NUMBER ) {

				packet_log_header_t * plh;

				plh = & ( packet_log_headers [ packet_log_header_index ++ ] );
				plh->address = packet_log;
				plh->queue_pointer.raw = rx_tail_copy_.raw ;
				memcpy( packet_log, packet, packet_size );
				packet_log += packet_size;
				packet_log += sizeof( unsigned long ) -
					( ( unsigned long ) packet_log % sizeof( unsigned long ) );

			}

			if( packet_size != eth_send( packet, packet_size ) ) {

				printf( "eth_send( ) failed: index %ld\n",
					packet_log_header_index - 1 );

			}

		}

		if( ctrlc( ) ) { break; }

	}

	{

		int index = 0;

		printf( "Logged %ld packets\n", packet_log_header_index );

		while( index < packet_log_header_index ) {

			packet_log_header_t * plh;

			plh = & ( packet_log_headers [ index ] );
			printf( "<%2d> address 0x%lx generation %d offset 0x%lx\n",
				index, ( unsigned long ) plh->address,
				plh->queue_pointer.bits.generation_bit,
				( unsigned long ) plh->queue_pointer.bits.offset );
			++ index;

			if( ctrlc( ) ) { break; }

		}

	}

	loopback = 0;
	rx_debug = 0;
	rx_allow_all = 0;
	eth_halt( );

	return;

}

/*
  ======================================================================
  ======================================================================
  ======================================================================
  Static Functions
  ======================================================================
  ======================================================================
  ======================================================================
*/

static inline void
readdescriptor( unsigned long address, app3xxnic_dma_descriptor_t * descriptor )
{
	unsigned long * from = ( unsigned long * ) address;
	unsigned long * to = ( unsigned long * ) descriptor;

#if 0
	invalidate_dcache_range( address,
				 ( address + sizeof( app3xxnic_dma_descriptor_t ) ) );
#endif
	* to ++ = swab32( * from ++ );
	* to ++ = swab32( * from ++ );
	* to ++ = swab32( * from ++ );
	* to ++ = swab32( * from ++ );

	return;
}

static inline void
writedescriptor( unsigned long address,
		 const app3xxnic_dma_descriptor_t * descriptor )
{
	unsigned long * to = ( unsigned long * ) address;
	unsigned long * from = ( unsigned long * ) descriptor;

	* to ++ = swab32( * from ++ );
	* to ++ = swab32( * from ++ );
	* to ++ = swab32( * from ++ );
	* to ++ = swab32( * from ++ );
#if 0
	flush_dcache_range( address,
			    ( address + sizeof( app3xxnic_dma_descriptor_t ) ) );
#endif

	return;
}

/*
  ----------------------------------------------------------------------
  queue_initialized_

  Returns the number of descriptors that are ready to receive packets
  or are waiting to transmit packets.
*/

static int queue_initialized_( app3xxnic_queue_pointer_t head,
			       app3xxnic_queue_pointer_t tail,
			       int size ) {

	int allocated_;

	/*
	  Calculate the number of descriptors currently allocated.
	*/

	if( head.bits.generation_bit == tail.bits.generation_bit ) {

		/* Same generation. */
		allocated_ = ( head.bits.offset - tail.bits.offset );

	} else {

		/* Different generation. */
		allocated_ = head.bits.offset +
			( size * sizeof( app3xxnic_dma_descriptor_t ) - tail.bits.offset );

	}

	/* Number of descriptors is offset / sizeof( a descriptor ). */
	allocated_ /= sizeof( app3xxnic_dma_descriptor_t );

	/*
	  That's all.
	*/

	return allocated_;

}

/*
  ----------------------------------------------------------------------
  queue_uninitialzed_

*/

static int queue_uninitialzed_( app3xxnic_queue_pointer_t head,
				app3xxnic_queue_pointer_t tail,
				int size ) {

	int allocated_;

	/*
	  Calculate the number of descriptors currently allocated.
	*/

	if( head.bits.generation_bit == tail.bits.generation_bit ) {

		/* Same generation. */
		allocated_ =
			( ( size * sizeof( app3xxnic_dma_descriptor_t ) ) -
			  head.bits.offset ) + tail.bits.offset;

	} else {

		/* Different generation. */
		allocated_ = tail.bits.offset - head.bits.offset;

	}

	/* Number of descriptors is offset / sizeof( a descriptor ). */
	allocated_ /= sizeof( app3xxnic_dma_descriptor_t );

	/*
	  That's all.
	*/

	return allocated_;

}

/*
  ----------------------------------------------------------------------
  queue_increment_
*/

static void queue_increment_( app3xxnic_queue_pointer_t * queue,
			      int size ) {

	queue->bits.offset += sizeof( app3xxnic_dma_descriptor_t );

	if( ( size * sizeof( app3xxnic_dma_descriptor_t ) ) ==
	    queue->bits.offset ) {

		queue->bits.offset = 0;
		queue->bits.generation_bit =
			( 0 == queue->bits.generation_bit ) ? 1 : 0;

	}

	return;

}

/*
  ----------------------------------------------------------------------
  queue_decrement_
*/

static void queue_decrement_( app3xxnic_queue_pointer_t * queue,
			      int size ) {

	if( 0 == queue->bits.offset ) {

		queue->bits.offset =
			( ( size - 1 ) * sizeof( app3xxnic_dma_descriptor_t ) );
		queue->bits.generation_bit =
			( 0 == queue->bits.generation_bit ) ? 1 : 0;

	} else {

		queue->bits.offset -= sizeof( app3xxnic_dma_descriptor_t );

	}

	return;

}

/*
  ----------------------------------------------------------------------
  rx_enable_
*/

static int rx_enable_( void ) {

	unsigned long rx_configuration_;

	TRACE_BEGINNING( "\n" );

	/*
	  Setup the receive configuration register (using smii status to set
	  speed/duplex and check the link status).
	*/

	rx_configuration_ = APP3XXNIC_RX_CONF_STRIPCRC;
	DEBUG_PRINT( "smii_status_=0x%x\n",
		     * ( ( volatile unsigned long * )
			 APP3XXNIC_RX_SMII_STATUS ) );
	DEBUG_PRINT( "phy_link=%d phy_speed=%d phy_duplex=%d\n",
		     phy_link( phy_address_ ), phy_speed( phy_address_ ),
		     phy_duplex( phy_address_ ) );

	if( 1 == phy_link( phy_address_ ) ) {

		if( 1 == phy_speed( phy_address_ ) ) {

			rx_configuration_ |= APP3XXNIC_RX_CONF_SPEED;

		}

		if( 1 == phy_duplex( phy_address_ ) ) {

			rx_configuration_ |= APP3XXNIC_RX_CONF_DUPLEX;

		}

		rx_configuration_ |= APP3XXNIC_RX_CONF_ENABLE;
		rx_configuration_ |= APP3XXNIC_RX_CONF_LINK;
		rx_configuration_ |= APP3XXNIC_RX_CONF_RXFCE;
		rx_configuration_ |= APP3XXNIC_RX_CONF_TXFCE;
		rx_enabled_ = 1;

	} else {

		rx_enabled_ = 0;

	}

	rx_configuration_ |= 0x4;
	writeio( rx_configuration_, APP3XXNIC_RX_CONF );

	/* that's all */
	TRACE_ENDING( "\n" );
	return ( 0 != rx_enabled_ ) ? 0 : 1;

}

/*
  ----------------------------------------------------------------------
  rx_disable_
*/

void rx_disable_( void ) {

	unsigned long rx_configuration_;

	TRACE_BEGINNING( "\n" );

	rx_configuration_ = readio( APP3XXNIC_RX_CONF );
	rx_configuration_ &= ~ APP3XXNIC_RX_CONF_ENABLE;
	writeio( rx_configuration_, APP3XXNIC_RX_CONF );
	rx_enabled_ = 0;

	/*
	  That's all.
	*/

	TRACE_ENDING( "\n" );
	return;

}

/*
  ----------------------------------------------------------------------
  tx_enable_

  -- NOTES --

  1) Does not change the default values in the extended and
  half-duplex configuration registers.
*/

static int
tx_enable_( void ) {

	unsigned long tx_configuration_;
	unsigned long swap_source_address_;

	TRACE_BEGINNING( "\n" );

	/*
	  Setup the transmit configuration register (using smii status
	  to set speed/duplex and check the link status).
	*/

	tx_configuration_ =
		( APP3XXNIC_TX_CONF_APP_CRC_ENABLE |
		  APP3XXNIC_TX_CONF_PAD_ENABLE );

	if( 0 == loopback ) {

		tx_configuration_ |= APP3XXNIC_TX_CONF_ENABLE_SWAP_SA;
		swap_source_address_ =
			( ( ethernet_address [ 4 ] ) << 8 ) | ethernet_address [ 5 ];
		writeio( swap_source_address_, APP3XXNIC_SWAP_SOURCE_ADDRESS_2 );
		swap_source_address_ =
			( ( ethernet_address [ 2 ] ) << 8 ) | ethernet_address [ 3 ];
		writeio( swap_source_address_, APP3XXNIC_SWAP_SOURCE_ADDRESS_1 );
		swap_source_address_ =
			( ( ethernet_address [ 0 ] ) << 8 ) | ethernet_address [ 1 ];
		writeio( swap_source_address_, APP3XXNIC_SWAP_SOURCE_ADDRESS_0 );

	}

	TX_CONF_SET_IFG( tx_configuration_, 0xf );

	if( 1 == phy_link( phy_address_ )  ) {

		if( 1 == phy_speed( phy_address_ ) ) {

			tx_configuration_ |= APP3XXNIC_TX_CONF_SPEED;

		}

		if( 1 == phy_duplex( phy_address_ ) ) {

			tx_configuration_ |= APP3XXNIC_TX_CONF_DUPLEX;

		}

		tx_configuration_ |=
			( APP3XXNIC_TX_CONF_LINK | APP3XXNIC_TX_CONF_ENABLE );
		tx_enabled_ = 1;

	} else {

		tx_enabled_ = 0;

	}

	writeio( tx_configuration_, APP3XXNIC_TX_CONF );

	/* that's all */
	TRACE_ENDING( "\n" );
	return ( 0 != tx_enabled_ ) ? 0 : 1;

}

/*
  ----------------------------------------------------------------------
  tx_disable_
*/

void tx_disable_( void ) {

	unsigned long tx_configuration_;

	TRACE_BEGINNING( "\n" );
	tx_configuration_ = readio( APP3XXNIC_TX_CONF );
	tx_configuration_ &= ~ APP3XXNIC_TX_CONF_ENABLE;
	writeio( tx_configuration_, APP3XXNIC_TX_CONF );
	tx_enabled_ = 0;

	/* that's all */
	TRACE_ENDING( "\n" );
	return;

}

/*
  ----------------------------------------------------------------------
  dump_descriptor_

  N.B. If you combine the printf statements, bad things will happen:>
*/

#ifdef DUMP_DESCRIPTOR

static void
dump_descriptor_( unsigned long line, void * address )
{
	app3xxnic_dma_descriptor_t descriptor;
	int rx = 0;

	if( 0 == dump_descriptors ) { return; }
	readdescriptor( ( unsigned long ) address, & descriptor );

	if( ( void * ) rx_descriptors_ < address &&
	    address <
	    ( void * ) ( rx_descriptors_ +
			 ( rx_number_of_descriptors *
			   sizeof( app3xxnic_dma_descriptor_t ) ) ) ) {
		rx = 1;
	}

#ifdef DUMP_DESCRIPTOR_COMPACT
	printf( "<%lu:%s:0x%x:bs=%d,ioc=%d,eop=%d,sop=%d,w=%d,tt=0x%x,pdul=0x%x,"
		"dtl=0x%x,tma=0x%x,hdmp=0x%x>\n",
		line, ( 1 == rx ) ? "RX" : "TX",
		( address - ( void * ) rx_descriptors_ ),
		( unsigned int ) ( descriptor.byte_swapping_on ),
		( unsigned int ) ( descriptor.interrupt_on_completion ),
		( unsigned int ) ( descriptor.end_of_packet ),
		( unsigned int ) ( descriptor.start_of_packet ),
		( unsigned int ) ( descriptor.write ),
		( unsigned int ) ( descriptor.transfer_type ),
		( unsigned int ) ( descriptor.pdu_length ),
		( unsigned int ) ( descriptor.data_transfer_length ),
		( unsigned int ) ( descriptor.target_memory_address ),
		( unsigned int ) ( descriptor.host_data_memory_pointer ) );
#else  /* DUMP_DESCRIPTOR_COMPACT */
	printf( "\n ---------- %s Descriptor at 0x%08lx\n",
		( 1 == rx ) ? "RX" : "TX", ( unsigned long ) address );
	printf( "        byte_swapping_on=%d\n" \
		" interrupt_on_completion=%d\n" \
		"           end_of_packet=%d\n" \
		"         start_of_packet=%d\n",
		( unsigned int ) ( descriptor.byte_swapping_on ),
		( unsigned int ) ( descriptor.interrupt_on_completion ),
		( unsigned int ) ( descriptor.end_of_packet ),
		( unsigned int ) ( descriptor.start_of_packet ) );
	printf( "                   write=%d\n"   \
		"           transfer_type=0x%x\n" \
		"              pdu_length=0x%x\n" \
		"    data_transfer_length=0x%x\n",
		( unsigned int ) ( descriptor.write ),
		( unsigned int ) ( descriptor.transfer_type ),
		( unsigned int ) ( descriptor.pdu_length ),
		( unsigned int ) ( descriptor.data_transfer_length ) );
	printf( "   target_memory_address=0x%x\n" \
		"host_data_memory_pointer=0x%x\n",
		( unsigned int ) ( descriptor.target_memory_address ),
		( unsigned int ) ( descriptor.host_data_memory_pointer ) );
#endif /* DUMP_DESCRIPTOR_COMPACT */

	return;
}

#endif /* DUMP_DESCRIPTOR */

/*
  ----------------------------------------------------------------------
  dump_packet_
*/

#ifdef DUMP_PACKETS

static void dump_packet_( int direction, void * data, int length ) {

	int data_index_ = 0;

	if( 0 == dump_packets) { return; }
	printf( "\n ---------- %s: address:0x%lx length=%d conf=0x%lx\n",
		( 0 == direction ) ? "RX" : "TX", ( unsigned long ) data, length,
		( 0 == direction ) ? readio( APP3XXNIC_RX_CONF ) :
		readio( APP3XXNIC_TX_CONF ) );

	while( data_index_ < ( length / 2 ) ) {

		int output_index_;
		unsigned short * data_ =
			& ( ( ( unsigned short * ) data ) [ data_index_ ] );

		for( output_index_ = 0;
		     ( output_index_ < 8 ) && ( data_index_ < length );
		     ++ output_index_, ++ data_index_ ) {

			printf( "%04x ", htons( data_ [ output_index_ ] ) );

		}

		printf( "\n" );

	}

	printf( " ----------\n\n" );

}

#endif /* DUMP_PACKETS */

/*
  ======================================================================
  ======================================================================
  ======================================================================
  PHY interface (BCM5221)
  ======================================================================
  ======================================================================
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  phy_scan_
*/

#ifndef CONFIG_ACP

static int
phy_scan_( void )
{
#ifndef CONFIG_ACP
	int phy_ = -1;
	int index_;

	TRACE_BEGINNING( "\n" );

	for( index_ = 31; index_ > -1; -- index_ ) {

		phy_id_high_t phy_id_high_;
		phy_id_low_t phy_id_low_;

		if( 0 != phy_read( index_, PHY_ID_HIGH, & phy_id_high_.raw, 0 ) ) {

#ifdef LSI_ARCH_APP3
			/*
			  Without this delay, the Broadcomm PHY at address 30 doesn't
			  get detected!
			*/
			mdelay( 250 );
#endif /* LSI_ARCH_APP3 */

			continue;

		}

		if( 0 != phy_read( index_, PHY_ID_LOW, & phy_id_low_.raw, 0 ) ) {

			continue;

		}

		if( ( BC_PHY_ID_HIGH_ID == phy_id_high_.bits.id ) &&
		    ( BC_PHY_ID_LOW_ID == phy_id_low_.bits.id ) &&
		    ( BC_PHY_ID_LOW_MODEL == phy_id_low_.bits.model ) ) {

			phy_ = index_;
			printf( "Found Broadcom PHY at 0x%x, revision %d.\n",
				( phy_ << 4 ), phy_id_low_.bits.revision );
			break;

		} else if( ( M_PHY_ID_HIGH_ID == phy_id_high_.bits.id ) &&
			   ( M_PHY_ID_LOW_ID == phy_id_low_.bits.id ) ) {

			phy_ = index_;
			printf( "Found Micrel PHY at 0x%x, revision 0x%x\n",
				( phy_ << 4 ), phy_id_low_.bits.revision );
			break;

		} else {

			phy_ = index_;
			printf( "Found unknown PHY at 0x%x: high=0x%x low=0x%x\n",
				( phy_ << 4 ), phy_id_high_.raw, phy_id_low_.raw );

		}

	}

	/* That's all */
	TRACE_ENDING( "\n" );
	return phy_;
#else  /* CONFIG_ACP */
	return 0x1e;
#endif /* CONFIG_ACP */
}

#endif /* CONFIG_ACP */

/*
  ----------------------------------------------------------------------
  get_env_ad_value
*/

static unsigned short
get_env_ad_value( void )
{
	char * ad_value_string_ = ( char * ) 0;
	unsigned long ad_value_;
	unsigned short return_value_;

	/*
	  0x1e1 - 10/100 half/full
	  0x181 - 100 half/full
	  0x0e1 - 100 half, 10 half/full
	  0x061 - 10 half/full
	  0x041 - 10 half
	*/

	ad_value_string_ = getenv( "ad_value" );

	if( ( char * ) 0 != ad_value_string_ ) {

		ad_value_ = simple_strtoul( ad_value_string_, NULL, 0 );
		return_value_ = ( unsigned short ) ( ad_value_ & 0xffff );

	} else {

		char ad_value_string_ [ 80 ];

		return_value_ = 0x61;

#ifdef CONFIG_APP
		if( ( IS_ASIC ) &&
		    ( 5 > APP3XX_RELEASE ) &&
		    ( 0 == APP3XX_RELEASE ) ) {

			/* 10M does not work on ASIC v1.0 */
			return_value_ = 0x181;

		}
#endif

		sprintf( ad_value_string_, "0x%x", return_value_ );
		setenv( "ad_value", ad_value_string_ );
		saveenv( );

	}

	/* that's all */
	return return_value_;
}

/*
  ----------------------------------------------------------------------
  phy_enable_
*/

static int
phy_enable_( int phy )
{
	TRACE_BEGINNING( "\n" );

	/*
	  Get the PHY address.
	*/

#ifndef CONFIG_ACP

	{

		char * phy_address_string_ = ( char * ) 0;

		if( ( char * ) 0 ==
		    ( phy_address_string_ = getenv( "phy_address" ) ) ) {

#if defined( LSI_ARCH_APP3K ) && defined( APP3K_NONOR )
			phy_address_ = * ( ( unsigned long * ) ( CONFIG_NORMAL_SHMEM_BASE ) );
			printf( "Using SHMEM for phy_address: 0x%x\n", phy_address_ );
#else  /*defined( LSI_ARCH_APP3K ) && defined( APP3K_NONOR ) */
			phy_address_ = 0x1f;
#endif /* defined( LSI_ARCH_APP3K ) && defined( APP3K_NONOR ) */

		} else if( 0 ==
			   strncmp( phy_address_string_, "scan", strlen( "scan" ) ) ) {

			phy_address_ = phy_scan_( );

		} else {

			phy_address_ = simple_strtoul( phy_address_string_, NULL, 0 );

		}

		if( 31 < phy_address_ || 0 > phy_address_ ) {

			ERROR_PRINT( "Unable to get valid PHY address!\n" );
			return -1;

		}

		printf( "PHY Address: 0x%x\n", phy_address_ );

	}

#else  /* CONFIG_ACP */

	phy_address_ = 0x1e;

#endif /* CONFIG_ACP */

	/*
	  Set up the link.
	*/

	if (0 != phy_renegotiate(phy_address_, get_env_ad_value())) {
		ERROR_PRINT( "PHY: Auto Negotiation Failed.\n" );
	}

	printf("%s %s\n",
	       0 == phy_speed(phy_address_) ? "10M" : "100M",
	       0 == phy_duplex(phy_address_) ? "Half Duplex" : "Full Duplex");

	return 0;
}

/*
  ======================================================================
  ======================================================================
  ======================================================================
  U-Boot NIC interface routines
  ======================================================================
  ======================================================================
  ======================================================================
*/

#ifdef ALLOW_DEBUGGING

/*
  ----------------------------------------------------------------------
  app3xxnic_tx_packets_
*/

static unsigned long app3xxnic_tx_packets_( void ) {

	static unsigned long tx_packets_ = 0;

	int registers_ [ ] = {

		( APP3XXNIC_TX_BASE + 0x0358 ),
		( APP3XXNIC_TX_BASE + 0x0360 )

	};

	int index_;

	for( index_ = 0; index_ < ( sizeof( registers_ ) / sizeof( int ) );
	     ++ index_ ) {

		tx_packets_ += readio( registers_ [ index_ ] );

	}

	/* that's all */
	return tx_packets_;

}

/*
  ----------------------------------------------------------------------
  app3xxnic_tx_bytes_
*/

static unsigned long app3xxnic_tx_bytes_( void ) {

	static unsigned long tx_bytes_ = 0;

	int registers_ [ ] = {

		( APP3XXNIC_TX_BASE + 0x0358 ),
		( APP3XXNIC_TX_BASE + 0x0360 )

	};

	int index_;

	for( index_ = 0; index_ < ( sizeof( registers_ ) / sizeof( int ) );
	     ++ index_ ) {

		tx_bytes_ += readio( registers_ [ index_ ] );

	}

	/* that's all */
	return tx_bytes_;

}

/*
  ----------------------------------------------------------------------
  app3xxnic_display_
*/

static void app3xxnic_display_( void ) {

	int registers_ [ ] = {

		( APP3XXNIC_RX_BASE + 0x0010 ),
		( APP3XXNIC_RX_BASE + 0x004c ),
		( APP3XXNIC_TX_BASE + 0x0300 ),
		( APP3XXNIC_TX_BASE + 0x0308 ),
		( APP3XXNIC_TX_BASE + 0x0310 ),
		( APP3XXNIC_TX_BASE + 0x0318 ),
		( APP3XXNIC_TX_BASE + 0x0320 ),
		( APP3XXNIC_TX_BASE + 0x0328 ),
		( APP3XXNIC_TX_BASE + 0x0330 ),
		( APP3XXNIC_TX_BASE + 0x0338 ),
		( APP3XXNIC_TX_BASE + 0x0340 ),
		( APP3XXNIC_TX_BASE + 0x0348 ),
		( APP3XXNIC_TX_BASE + 0x0350 ),
		( APP3XXNIC_TX_BASE + 0x0358 ),
		( APP3XXNIC_TX_BASE + 0x0360 ),
		( APP3XXNIC_TX_BASE + 0x0368 ),
		( APP3XXNIC_TX_BASE + 0x0370 ),
		( APP3XXNIC_TX_BASE + 0x0378 ),
		( APP3XXNIC_TX_BASE + 0x0380 ),
		APP3XXNIC_DMA_INTERRUPT_ENABLE,
		APP3XXNIC_DMA_INTERRUPT_STATUS,
		APP3XXNIC_TX_WATERMARK

	};

	int index_;

	printf( "NIC Registers:\n" );

	for( index_ = 0; index_ < ( sizeof( registers_ ) / sizeof( int ) );
	     ++ index_ ) {

		unsigned long value_ = readio( registers_ [ index_ ] );

		printf( " 0x%x:0x%x\n", registers_ [ index_ ], value_ );

	}

	puts( "\n" );

	/* that's all */
	return;

}

#endif

/*
  ----------------------------------------------------------------------
  lsi_femac_eth_init
*/

int
lsi_femac_eth_init(bd_t *board_info)
{
	size_t memory_needed;
	void * temp;

	TRACE_BEGINNING( "\n" );

	/* Don't initialize twice. */
	if( 0 != initialized_ ) {
		eth_halt( );
	}

	/* Reset the MAC */
	writeio( 0x80000000, APP3XXNIC_DMA_PCI_CONTROL );

	/*
	  Decide which interface to use, ARM attached MAC or the Management Port
	*/

	/*
	  -- WORKAROUND -- WORKAROUND -- WORKAROUND -- WORKAROUND -- WORKAROUND --
	  This is the software work around for defect 15129.  Use 64 byte
	  buffers for receive descriptors for all dma.
	  -- WORKAROUND -- WORKAROUND -- WORKAROUND -- WORKAROUND -- WORKAROUND --
	*/
#ifndef CONFIG_ACP
	if( 1 >= APP3XX_REVISION ) {
		printf( "++ Using work around for defect 15129\n" );
		rx_number_of_descriptors = 512;
		rx_buffer_size = ( 32 * 1024 );
		rx_buffer_per_descriptor = ( rx_buffer_size / rx_number_of_descriptors );
	}
#endif

	/* Assert that the number of descriptors is a multiple of 64. */

	if( ( 0 != ( rx_number_of_descriptors % DESCRIPTOR_GRANULARITY ) ) ||
	    ( 0 != ( TX_NUMBER_OF_DESCRIPTORS % DESCRIPTOR_GRANULARITY ) ) ) {
		ERROR_PRINT( "Number of descriptors is not a multiple of 64! " \
			     "rx=%d tx=%d\n",
			     rx_number_of_descriptors, TX_NUMBER_OF_DESCRIPTORS );
		TRACE_ENDING( "\n" );
		return 1;
	}

	/* Allocate Memory for Descriptors, Buffers, and Tail Pointers */
	memory_needed =
		( sizeof( app3xxnic_dma_descriptor_t ) * /* RX Descriptors */
		  rx_number_of_descriptors +
		  DESCRIPTOR_GRANULARITY ) +
		( sizeof( app3xxnic_dma_descriptor_t ) * /* TX Descriptors */
		  TX_NUMBER_OF_DESCRIPTORS +
		  DESCRIPTOR_GRANULARITY ) +
		( rx_buffer_size + BUFFER_GRANULARITY ) + /* RX Buffers */
		( TX_BUFFER_SIZE + BUFFER_GRANULARITY ) + /* TX Buffers */
		( 2 * sizeof( app3xxnic_queue_pointer_t ) ); /* Tail Pointers */

	if( ( void * ) 0 == ( memory = malloc( memory_needed ) ) ) {
		ERROR_PRINT( "Unable to allocate space for descriptors and buffers\n" );
		return 1;
	}

	/*
	  Set the zone to allow access by non-secure masters (the FEMAC).
	*/
#ifdef ACP_25xx
	if (0 != sbb_desecure_range(1, memory, memory_needed)) {
	  printf("sbb_desecure_range() failed!\n");
	}
#if 0
	{
	  unsigned long tzc_address;
	  unsigned long tzc_size;
	  unsigned long tzc_address_mask = 0x10000;
	  unsigned long tzc_size_field = 0xe;

	  tzc_address = (unsigned long)memory & ~(tzc_address_mask - 1);
	  tzc_size = 32 * 1024;

	  while ((tzc_address + tzc_size) <
		 ((unsigned long)memory + memory_needed)) {
	    tzc_address_mask <<= 1;
	    tzc_address = (unsigned long)memory & ~(tzc_address_mask - 1);
	    tzc_size *= 2;
	    ++tzc_size_field;
	  }

	  writeio(tzc_address, 0xf0941110);
	  writeio(0, 0xf0941114);
	  writeio(0xf0000001 | (tzc_size_field << 1), 0xf0941118);
	}
#endif
#endif

	temp = memory;

	rx_descriptors_ = ( app3xxnic_dma_descriptor_t * ) ALIGN64B( temp );
	temp = ( void * )
		( ( unsigned long ) rx_descriptors_ + 
		  ( rx_number_of_descriptors * sizeof( app3xxnic_dma_descriptor_t ) ) );
	DEBUG_PRINT( "temp=0x%x rx_descriptors_=0x%08x\n", temp, rx_descriptors_ );
	/*printf( "rx_descriptors_=0x%08x\n", rx_descriptors_ );*/

	tx_descriptors_ = ( app3xxnic_dma_descriptor_t * ) ALIGN64B( temp );
	temp = ( void * )
		( ( unsigned long ) tx_descriptors_ + 
		  ( TX_NUMBER_OF_DESCRIPTORS * sizeof( app3xxnic_dma_descriptor_t ) ) );
	DEBUG_PRINT( "temp=0x%x tx_descriptors_=0x%08x\n", temp, tx_descriptors_ );
	/*printf( "tx_descriptors_=0x%08x\n", tx_descriptors_ );*/

	rx_buffer_ = ( void * ) ALIGN64B( temp );
	temp = ( void * ) ( ( unsigned long ) rx_buffer_ + rx_buffer_size );
	DEBUG_PRINT( "rx_buffer_=0x%x\n", rx_buffer_ );
	/*printf( "rx_buffer_=0x%x\n", rx_buffer_ );*/

	tx_buffer_ = ( void * ) ALIGN64B( temp );
	temp = ( void * ) ( ( unsigned long ) tx_buffer_ + TX_BUFFER_SIZE );
	DEBUG_PRINT( "tx_buffer_=0x%x\n", tx_buffer_ );
	/*printf( "tx_buffer_=0x%x\n", tx_buffer_ );*/

	rx_tail_ = ( void * ) ALIGN( temp, sizeof( app3xxnic_queue_pointer_t ) );
	temp = ( void * ) ( rx_tail_ + sizeof( app3xxnic_queue_pointer_t ) );
	DEBUG_PRINT( "rx_tail_=0x%x\n", rx_tail_ );
	/*printf( "rx_tail_=0x%x\n", rx_tail_ );*/

	tx_tail_ = ( void * ) ALIGN( temp, sizeof( app3xxnic_queue_pointer_t ) );
	temp = ( void * ) ( tx_tail_ + sizeof( app3xxnic_queue_pointer_t ) );
	DEBUG_PRINT( "tx_tail_=0x%x\n", tx_tail_ );
	/*printf( "tx_tail_=0x%x\n", tx_tail_ );*/

	/* Initialize descriptors. */

	{
		app3xxnic_dma_descriptor_t descriptor_;
		void * buffer_;
		int index_;

		buffer_ = rx_buffer_;

		for( index_ = 0; index_ < rx_number_of_descriptors; ++ index_ ) {
			memset( ( void * ) & descriptor_, 0,
				( sizeof( app3xxnic_dma_descriptor_t ) ) );
			descriptor_.host_data_memory_pointer = ( unsigned long ) buffer_;
			descriptor_.data_transfer_length = rx_buffer_per_descriptor;
			descriptor_.write = 1;
			descriptor_.interrupt_on_completion = 1;
			writedescriptor( ( ( unsigned long ) rx_descriptors_ +
					   ( index_ * sizeof( app3xxnic_dma_descriptor_t ) ) ),
					 & descriptor_ );
			buffer_ += rx_buffer_per_descriptor;
		}
	}

	memset( ( void * ) tx_descriptors_, 0,
		( sizeof( app3xxnic_dma_descriptor_t ) * TX_NUMBER_OF_DESCRIPTORS ) );

	/* All is good! */
	DEBUG_PRINT( "Descriptors : receive=%d transmit=%d\n",
		     rx_number_of_descriptors, TX_NUMBER_OF_DESCRIPTORS );
	DEBUG_PRINT( "Receive Buffer Size : %d\n", rx_buffer_size );
	DEBUG_PRINT( "Enabling the MAC.\n" );
	writeio( 0x0, APP3XXNIC_RX_SOFT_RESET );
	writeio( 0x1, APP3XXNIC_RX_MODE );
	writeio( 0x0, APP3XXNIC_TX_SOFT_RESET );
	writeio( 0x1, APP3XXNIC_TX_MODE );
	if( is_asic( ) ) {
		writeio( 0x300a, APP3XXNIC_TX_WATERMARK );
	} else {
		writeio( 0xc00096, APP3XXNIC_TX_WATERMARK );
	}
	writeio( 0x1, APP3XXNIC_TX_HALF_DUPLEX_CONF );
	writeio( 0xffff, APP3XXNIC_TX_TIME_VALUE_CONF );
	writeio( 0x1, APP3XXNIC_TX_INTERRUPT_CONTROL );
	writeio( 0x5275, APP3XXNIC_TX_EXTENDED_CONF );
	writeio( 0x1, APP3XXNIC_RX_INTERNAL_INTERRUPT_CONTROL );
	writeio( 0x1, APP3XXNIC_RX_EXTERNAL_INTERRUPT_CONTROL );
	writeio( 0x40010000, APP3XXNIC_DMA_PCI_CONTROL );
	writeio( 0x30000, APP3XXNIC_DMA_CONTROL );
	writeio( 0x280044, APP3XXNIC_DMA_BASE + 0x60 );
	writeio( 0xc0, APP3XXNIC_DMA_BASE + 0x64 );

	/*
	  Update the tail pointer addresses and queue sizes.  The transmit
	  head pointer will be updated when there is something to transmit.
	*/

	writeio( ( unsigned int ) rx_descriptors_,
		 APP3XXNIC_DMA_RX_QUEUE_BASE_ADDRESS );
	writeio( ( unsigned int )
		 ( ( rx_number_of_descriptors *
		     sizeof( app3xxnic_dma_descriptor_t ) ) / 1024 ),
		 APP3XXNIC_DMA_RX_QUEUE_SIZE );

	memset( ( void * ) & rx_tail_copy_.raw, 0,
		sizeof( app3xxnic_queue_pointer_t ) );

	memset( ( void * ) rx_tail_, 0, sizeof( app3xxnic_queue_pointer_t ) );
	writeio( ( unsigned long ) rx_tail_, APP3XXNIC_DMA_RX_TAIL_POINTER_ADDRESS );

	writeio( 3, APP3XXNIC_DMA_BASE + 0x1c );

	writeio( ( unsigned int ) tx_descriptors_,
		 APP3XXNIC_DMA_TX_QUEUE_BASE_ADDRESS );
	writeio( ( unsigned int )
		 ( TX_NUMBER_OF_DESCRIPTORS *
		   sizeof( app3xxnic_dma_descriptor_t ) / 1024 ),
		 APP3XXNIC_DMA_TX_QUEUE_SIZE );

	memset( ( void * ) & tx_tail_copy_.raw, 0,
		sizeof( app3xxnic_queue_pointer_t ) );

	memset( ( void * ) tx_tail_, 0, sizeof( app3xxnic_queue_pointer_t ) );
	writeio( ( unsigned long ) tx_tail_, APP3XXNIC_DMA_TX_TAIL_POINTER_ADDRESS );

	rx_tail_->raw = readio( APP3XXNIC_DMA_RX_TAIL_POINTER_LOCAL_COPY );
	rx_tail_copy_.raw = rx_tail_->raw;
	rx_head_.raw = rx_tail_->raw;
	queue_decrement_( & rx_head_, rx_number_of_descriptors );
	rx_head_.bits.generation_bit =
		( 0 == rx_head_.bits.generation_bit ) ? 1 : 0;
	DEBUG_PRINT( "rx_head_.raw=0x%x rx_tail_->raw=0x%x "
		     "rx_tail_copy_.raw=0x%x\n",
		     rx_head_.raw, rx_tail_->raw, rx_tail_copy_.raw );
	writeio( rx_head_.raw, APP3XXNIC_DMA_RX_HEAD_POINTER );

	tx_tail_->raw = readio( APP3XXNIC_DMA_TX_TAIL_POINTER_LOCAL_COPY );
	tx_tail_copy_.raw = tx_tail_->raw;
	tx_head_.raw = tx_tail_->raw;
	DEBUG_PRINT( "tx_head_.raw=0x%08lx\n", tx_head_.raw );
	writeio( tx_head_.raw, APP3XXNIC_DMA_TX_HEAD_POINTER );

	/*
	  Enable the PHY, RX, and TX, unless booting in band.
	*/

	{

		int retries_ = 10;

		while( 0 != phy_enable_( phy_address_ ) ) {

			WARN_PRINT( "Failed to initialize the PHY, retrying!\n" );

			if( 0 == -- retries_ ) { break; }

		}

		if( 0 != rx_enable_( ) ) {

			WARN_PRINT( "Receiver not enabled, link down?\n" );

		}

		if( 0 != tx_enable_( ) ) {

			WARN_PRINT( "Transmitter not enabled, link down?\n" );

		}

	}

#ifdef EH_STATS
	if(0 == eh_stats_initialized) {
		printf("Clearing the eh_stats structure.\n");
		memset((void *)eh_stats, 0, sizeof(eh_stats_t));
		eh_stats_initialized = 1;
	}
#endif /* EH_STATS */

	/* set the "initialized" flag */
	initialized_ = 1;

	/* that's all */
	TRACE_ENDING( "\n" );
	return 0;

}

/*
  ----------------------------------------------------------------------
  lsi_femac_eth_halt
*/

void lsi_femac_eth_halt( void ) {

	TRACE_BEGINNING( "\n" );

	/* only once... */
	if( 0 == initialized_ ) {

		TRACE_ENDING( "\n" );
		return;

	}

	/*
	  Disable RX, and TX, unless booting in band
	*/

	rx_disable_( );
	tx_disable_( );

	/* free memory */
	free( memory );

	/* disable the MAC */
	writeio( 0, APP3XXNIC_RX_MODE );
	writeio( 1, APP3XXNIC_RX_SOFT_RESET );
	writeio( 0, APP3XXNIC_TX_MODE );
	writeio( 1, APP3XXNIC_TX_SOFT_RESET );

	/* set the "initialized" flag */
	initialized_ = 0;

	/* that's all */
	TRACE_ENDING( "\n" );
	return;

}

/*
  ----------------------------------------------------------------------
  lsi_femac_eth_rx
*/

int
lsi_femac_eth_rx( void )
{
	int bytes_received_ = 0;

	TRACE_BEGINNING( "\n" );

#ifdef DUMP_STATS
#ifdef EH_STATS
	++eh_stats->rx_calls;
#else
	{
		app3xxnic_dma_descriptor_t descriptor;
		app3xxnic_queue_pointer_t queue_;

		queue_.raw = rx_tail_copy_.raw;
		printf( "\t * %s:%d - 0x%lx 0x%lx/0x%lx/0x%lx/0x%lx 0x%lx 0x%lx 0x%lx %d\n",
			__FILE__, __LINE__,
			( unsigned long ) rx_descriptors_,
			readio( APP3XXNIC_RX_STAT_PACKET_OK ),
			readio( APP3XXNIC_RX_STAT_OVERFLOW ),
			readio( APP3XXNIC_RX_STAT_CRC_ERROR ),
			readio( APP3XXNIC_RX_STAT_ALIGN_ERROR ),
			rx_head_.raw, rx_tail_copy_.raw,
			( swab_queue_pointer( * rx_tail_ ) ).raw,
			queue_initialized_( swab_queue_pointer( * rx_tail_ ),
					    queue_, rx_number_of_descriptors ) );
		readdescriptor( ( ( unsigned long ) rx_descriptors_ +
				  ( swab_queue_pointer( * rx_tail_ ) ).bits.offset ),
				& descriptor );
		DUMP_DESCRIPTOR_( ( void * )
				  ( ( unsigned long ) rx_descriptors_ +
				    ( swab_queue_pointer( * rx_tail_ ) ).bits.offset ) );
		mdelay( 500 );
	}
#endif
#endif

	/*
	  If no packet is available, return 0;
	*/

	{

		app3xxnic_queue_pointer_t queue_;
		app3xxnic_dma_descriptor_t descriptor_;
		int packet_available_ = 0;

		queue_.raw = rx_tail_copy_.raw;

		while( 0 <
		       queue_initialized_( swab_queue_pointer( * rx_tail_ ),
					   queue_, rx_number_of_descriptors ) ) {
			readdescriptor( ( ( unsigned long ) rx_descriptors_ +
					  queue_.bits.offset ), & descriptor_ );
			DUMP_DESCRIPTOR_( ( void * ) ( ( unsigned long ) rx_descriptors_ +
						       queue_.bits.offset ) );

			if( 0 != descriptor_.end_of_packet ) {
				packet_available_ = 1;
				break;
			} else {
				queue_increment_( & queue_, rx_number_of_descriptors );
			}

		}

		if( 0 == packet_available_ ) {
			TRACE_ENDING( "\n" );
			return 0;
		}

	}

#ifdef DUMP_STATS
#ifdef EH_STATS
	++eh_stats->rx_packet_available;
#else
#endif
#endif

	RX_DEBUG_PRINT( "head=0x%x/%d tail=0x%x/%d tail_copy=0x%x/%d\n",
			rx_head_.bits.offset, rx_head_.bits.generation_bit,
			rx_tail_->bits.offset, rx_tail_->bits.generation_bit,
			rx_tail_copy_.bits.offset,
			rx_tail_copy_.bits.generation_bit );

	/*
	  Get the packet.
	*/

	{

		void * destination_ = ( void * ) ( NetRxPackets [ 0 ] );
		app3xxnic_dma_descriptor_t descriptor_;

		readdescriptor( ( ( unsigned long ) rx_descriptors_ +
				  rx_tail_copy_.bits.offset ), & descriptor_ );

		while( 0 <
		       queue_initialized_( swab_queue_pointer( * rx_tail_ ),
					   rx_tail_copy_, rx_number_of_descriptors ) ) {
			memcpy( destination_,
				( void * ) descriptor_.host_data_memory_pointer,
				descriptor_.pdu_length );
			destination_ += descriptor_.pdu_length;
			bytes_received_ += descriptor_.pdu_length;
			DUMP_DESCRIPTOR_( ( void * ) ( ( unsigned long ) rx_descriptors_ +
						       rx_tail_copy_.bits.offset ) );
			queue_increment_( & rx_tail_copy_, rx_number_of_descriptors );
			if( 0 != descriptor_.end_of_packet ) { break; }
			readdescriptor( ( ( unsigned long ) rx_descriptors_ +
					  rx_tail_copy_.bits.offset ), & descriptor_ );
		}

		{

			unsigned long overflow_, ok_, crc_, align_;

			overflow_ = readio( APP3XXNIC_RX_STAT_OVERFLOW );
			ok_ = readio( APP3XXNIC_RX_STAT_PACKET_OK );
			crc_ = readio( APP3XXNIC_RX_STAT_CRC_ERROR );
			align_ = readio( APP3XXNIC_RX_STAT_ALIGN_ERROR );

#ifdef DUMP_STATS
#ifdef EH_STATS
			eh_stats->rx_packet_ok += ok_;
			eh_stats->rx_packet_overflow += overflow_;
			eh_stats->rx_packet_crc += crc_;
			eh_stats->rx_packet_alignment += align_;
#else
#endif
#endif

			if( ( 0 == descriptor_.end_of_packet ) || ( 0 != overflow_ ) ||
			    ( 0 != crc_ ) || ( 0 != align_ ) ) {

				printf( "Bad Packet: "
					"bytes=%d ovf=%ld ok=%ld crc=%ld align=%ld\n",
					bytes_received_, overflow_, ok_, crc_, align_ );
				WARN_PRINT( "Bad Packet: "
					    "bytes=%d ovf=%ld ok=%ld crc=%ld align=%ld\n",
					    bytes_received_, overflow_, ok_, crc_, align_ );

			} else {

				unsigned char broadcast_ [ ] =
					{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
				unsigned char * destination_ =
					( unsigned char * ) NetRxPackets [ 0 ];

				if( ( 0 != rx_allow_all ) ||
				    ( ( 0 == memcmp( ( const void * ) & ( destination_ [ 0 ] ),
						     ( const void * ) & ( ethernet_address [ 0 ] ),
						     6 ) ) ||
				      ( 0 == memcmp( ( const void * ) & ( destination_ [ 0 ] ),
						     ( const void * ) & ( broadcast_ [ 0 ] ),
						     6 ) ) ) ) {

					DUMP_PACKET( 0,
						     ( void * ) ( NetRxPackets [ 0 ] ),
						     bytes_received_ );

					if( 0 == rx_debug ) {

#if 0
					  dump_packet("RX", (void *)destination_, bytes_received_);
#endif
						NetReceive( NetRxPackets[ 0 ],
							    bytes_received_ );

					}

				} else {

#ifdef DUMP_STATS
#ifdef EH_STATS
					++eh_stats->rx_packet_bad_address;
#else
					printf( "Dumping Packet Not Addressed to Us.\n" );
#endif
#endif

				}

			}

		}

	}

	RX_DEBUG_PRINT( "head=0x%x/%d tail=0x%x/%d tail_copy=0x%x/%d\n",
			rx_head_.bits.offset, rx_head_.bits.generation_bit,
			rx_tail_->bits.offset, rx_tail_->bits.generation_bit,
			rx_tail_copy_.bits.offset,
			rx_tail_copy_.bits.generation_bit );

	/*
	  Update the rx descriptor queue
	*/

	{

		int head_changed_ = 0;

		while( 1 < queue_uninitialzed_( rx_head_, rx_tail_copy_,
						rx_number_of_descriptors ) ) {

			app3xxnic_dma_descriptor_t descriptor_;

			readdescriptor( ( ( unsigned long ) rx_descriptors_ +
					  rx_head_.bits.offset ), & descriptor_ );
			descriptor_.data_transfer_length = rx_buffer_per_descriptor;
			descriptor_.write = 1;
			descriptor_.interrupt_on_completion = 1;
			descriptor_.byte_swapping_on = 0;
			writedescriptor( ( ( unsigned long ) rx_descriptors_ +
					   rx_head_.bits.offset ), & descriptor_ );
			queue_increment_( & rx_head_, rx_number_of_descriptors );
			head_changed_ = 1;

		}

		if( 0 != head_changed_ ) {

			writeio( rx_head_.raw, APP3XXNIC_DMA_RX_HEAD_POINTER );

		}

	}

	RX_DEBUG_PRINT( "head=0x%x/%d tail=0x%x/%d tail_copy=0x%x/%d\n",
			rx_head_.bits.offset, rx_head_.bits.generation_bit,
			rx_tail_->bits.offset, rx_tail_->bits.generation_bit,
			rx_tail_copy_.bits.offset,
			rx_tail_copy_.bits.generation_bit );

	/*
	  That's all
	*/

	TRACE_ENDING( "bytes_received_=%d\n", bytes_received_ );
	return bytes_received_;

}

/*
  ----------------------------------------------------------------------
  lsi_femac_eth_send
*/

int
lsi_femac_eth_send( volatile void * packet, int length )
{
	int bytes_sent_ = 0;

	TRACE_BEGINNING( "packet=0x%p length=%d\n", packet, length );
	DUMP_PACKET( 1, (void *)packet, length );
	TX_DEBUG_PRINT( "Sending %d byte packet\n", length );
	TX_DEBUG_PRINT( "tail=0x%x/%d tail_copy=0x%x/%d\n",
			tx_tail_->bits.offset, tx_tail_->bits.generation_bit,
			tx_tail_copy_.bits.offset,
			tx_tail_copy_.bits.generation_bit );

#ifdef DUMP_STATS
#ifdef EH_STATS
	++eh_stats->tx_calls;
#else
	printf("TX: %d bytes\n", length);
#endif
#endif

#if 0
	dump_packet("TX", packet, length);
#endif

	/*
	  Update tx_tail_copy_
	*/

	while( 0 < queue_initialized_( swab_queue_pointer( * tx_tail_ ),
				       tx_tail_copy_,
				       TX_NUMBER_OF_DESCRIPTORS ) ) {
		queue_increment_( & tx_tail_copy_, TX_NUMBER_OF_DESCRIPTORS );
	}

	TX_DEBUG_PRINT( "tail=0x%x/%d tail_copy=0x%x/%d\n",
			tx_tail_->bits.offset, tx_tail_->bits.generation_bit,
			tx_tail_copy_.bits.offset,
			tx_tail_copy_.bits.generation_bit );

	/*
	  If a transmit descriptor is available, allocate space for the
	  packet and initialize it.
	*/

#if 0
	invalidate_dcache_range( ( unsigned long ) tx_tail_,
				 ( ( unsigned long ) tx_tail_ +
				   sizeof( app3xxnic_queue_pointer_t ) ) );
#endif
	if( TX_NUMBER_OF_DESCRIPTORS >
	    queue_initialized_( tx_head_, swab_queue_pointer( * tx_tail_ ),
				TX_NUMBER_OF_DESCRIPTORS ) ) {
		app3xxnic_dma_descriptor_t descriptor_;
		unsigned long packets_sent_;

		TX_DEBUG_PRINT( "Transmit descriptor available, "
				"head=0x%x/%d tail=0x%x/%d\n",
				tx_head_.bits.offset,
				tx_head_.bits.generation_bit, 
				rx_head_.bits.offset,
				rx_head_.bits.generation_bit );
		memcpy( tx_buffer_, ( void * ) packet, length );
#if 0
		flush_dcache_range( ( unsigned long ) tx_buffer_,
				    ( unsigned long ) ( tx_buffer_ + length ) );
#endif
		readdescriptor( ( ( unsigned long ) tx_descriptors_ +
				  tx_head_.bits.offset ),
				& descriptor_ );
		descriptor_.host_data_memory_pointer =
			( unsigned long ) tx_buffer_;
		descriptor_.pdu_length = length;
		descriptor_.data_transfer_length = length;
		descriptor_.write = 1;
		descriptor_.start_of_packet = 1;
		descriptor_.end_of_packet = 1;
		descriptor_.byte_swapping_on = 0;
		writedescriptor( ( ( unsigned long ) tx_descriptors_ +
				   tx_head_.bits.offset ), & descriptor_ );
		DUMP_DESCRIPTOR_( ( void * ) ( ( unsigned long ) tx_descriptors_ +
					       tx_head_.bits.offset ) );
		queue_increment_( & tx_head_, TX_NUMBER_OF_DESCRIPTORS );
		writeio( tx_head_.raw, APP3XXNIC_DMA_TX_HEAD_POINTER );
		/* Wait for the transmit to finish. */
		TX_DEBUG_PRINT( "Waiting for transmit to finish.\n" );

		{
			int tries_ = 1000;

#if 0
			invalidate_dcache_range( ( unsigned long ) tx_tail_,
						 ( ( unsigned long ) tx_tail_ +
						   sizeof( app3xxnic_queue_pointer_t ) ) );
#endif
			while( ( tx_head_.raw != swab32( tx_tail_->raw ) ) &&
			       ( 0 < -- tries_ ) ) {
#if 0
				invalidate_dcache_range( ( unsigned long ) tx_tail_,
							 ( ( unsigned long ) tx_tail_ +
							   sizeof( app3xxnic_queue_pointer_t ) ) );
#endif
				__asm__ __volatile__ ( "eieio" );
				__asm__ __volatile__ ( "sync" );
				udelay( 100 );
			}

			if( 0 == tries_ ) {
				ERROR_PRINT( "TX timeout: tx_head_.raw=0x%08lx "
					     "tx_tail_->raw=0x%08x/0x%08x\n",
					     tx_head_.raw,
					     swab32( tx_tail_->raw ),
					     readl( APP3XXNIC_DMA_TX_TAIL_POINTER_LOCAL_COPY ) );
				/*app3xxnic_display_( );*/
				TRACE_ENDING( "\n" );
				return 0;

			} else {
				packets_sent_ = readio( APP3XXNIC_TX_STAT_PACKET_OK );
#ifdef DUMP_STATS
#ifdef EH_STATS
				++eh_stats->tx_packet_sent;
#else
				printf( "TX stats: OK=%d\n", packets_sent_ );
#endif
#endif
			}
		}

		TX_DEBUG_PRINT( "Done, sent %d bytes.\n", length );
		DEBUG_PRINT( "TX_HEAD=0x%08lx TX_TAIL_LC=0x%08lx\n",
			     readl( APP3XXNIC_DMA_TX_HEAD_POINTER ),
			     readl( APP3XXNIC_DMA_TX_TAIL_POINTER_LOCAL_COPY ) );
		bytes_sent_ = length;

	}

	/* That's all */

	TX_DEBUG_PRINT( "Done, returning %d.\n", bytes_sent_ );
	TRACE_ENDING( "bytes_sent_=%d\n", bytes_sent_ );
	return bytes_sent_;
}

#endif /* NCR_TRACER */
#endif /* CONFIG_LSI_NET */
