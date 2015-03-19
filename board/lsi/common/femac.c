/*
 *  board/lsi/common/femac.c
 *
 *  Copyright (C) 2013 LSI (john.jacques@lsi.com)
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
 * A Driver for the custom MAC included in LSI Axxia ASICs
 *
 * -- Hardware Bugs -- With Software Fixes --
 *
 * -1-
 * When the generation bits are equal, as are the pointers, instead of
 * considering the fifo empty (which it is) hardware considers it FULL.
 * In concequence, one descriptor will always be wasted...
 * -2-
 * When the MAC sends a packet, it zeros out the "data transfer length"
 * field...
 *
 */

#include <config.h>
#include <common.h>
#include <command.h>
#include <net.h>
#include <exports.h>
#include <asm/io.h>
#include <asm/cache.h>
#include <asm/global_data.h>

/*#define ALLOW_DEBUGGING */
/*#define USE_LSM*/

#define DUMP_STATS
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

/*static void dump_descriptor_( unsigned long, void *);*/

#undef DUMP_PACKETS
#define DUMP_PACKETS
#ifdef DUMP_PACKETS
#define DUMP_PACKET(header, data, length) \
dump_packet_(header, data, length);
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
/* #define RX_DEBUG */
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

/* -- -- */

static int phy_address_ = CONFIG_AXXIA_PHY_ADDRESS;
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
#define ALIGN(address, bytes) \
  (((unsigned long long)(address) + \
    (unsigned long long)(bytes - 1)) & ~((unsigned long long)(bytes - 1)))

#define ALIGN64B(address) \
  (((unsigned long long)(address) + (64 - 1)) & ~(64 - 1))

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
extern int  eth_send( void *, int );

/*
  Data Structures.
*/

typedef struct {

#ifdef CONFIG_AXXIA_PPC

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

#else  /* CONFIG_AXXIA_PPC */

	/* Word 0 */
	/* 00=Fill|01=Block|10=Scatter */
	unsigned int transfer_type           : 2;
	unsigned int write                   : 1;
	unsigned int start_of_packet         : 1;
	unsigned int end_of_packet           : 1;
	unsigned int interrupt_on_completion : 1;
	unsigned int                         : 1;
	/* big endian to little endian */
	unsigned int byte_swapping_on        : 1;
	unsigned int                         : 24;

	/* Word 1 */
	unsigned int data_transfer_length : 16;
	unsigned int pdu_length           : 16;

	/* Word 2 */
	unsigned int target_memory_address;

	/* Word 3 */
	unsigned int host_data_memory_pointer;

#endif /* CONFIG_AXXIA_PPC */

} __attribute__ ( ( packed ) ) app3xxnic_dma_descriptor_t;

typedef union {
	unsigned long raw;

	struct {
#ifdef CONFIG_AXXIA_PPC
		unsigned long                : 11;
		unsigned long generation_bit : 1;
		unsigned long offset         : 20;
#else  /* CONFIG_AXXIA_PPC */
		unsigned int offset         : 20;
		unsigned int generation_bit : 1;
		unsigned int                : 11;
#endif /* CONFIG_AXXIA_PPC */
	} __attribute__ ( ( packed ) ) bits;
} __attribute__ ( ( packed ) ) app3xxnic_queue_pointer_t;

static inline app3xxnic_queue_pointer_t
swab_queue_pointer(const app3xxnic_queue_pointer_t *old_queue)
{
#if defined(CONFIG_AXXIA_ARM)
        return *old_queue;
#elif defined(CONFIG_AXXIA_PPC)
	app3xxnic_queue_pointer_t new_queue;

	new_queue.raw = swab32(old_queue->raw);
	printf("%s:%d - 0x%08x 0x%08x\n",
	       __FILE__, __LINE__, new_queue.raw, old_queue->raw);

	return new_queue;
#else
#error "Unknown Architecture!"
#endif
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

#define RX_NUMBER_OF_DESCRIPTORS 128
#define RX_BUFFER_SIZE ( 128 * 1024 )
#define RX_BUFFER_PER_DESCRIPTOR \
	(RX_BUFFER_SIZE / RX_NUMBER_OF_DESCRIPTORS)

static void * memory;

static unsigned rx_number_of_descriptors = RX_NUMBER_OF_DESCRIPTORS;
static unsigned rx_buffer_size = RX_BUFFER_SIZE;
static unsigned rx_buffer_per_descriptor = RX_BUFFER_PER_DESCRIPTOR;

static app3xxnic_dma_descriptor_t * rx_descriptors_;
static void * rx_buffer_;
static int rx_enabled_ = 0;
static app3xxnic_queue_pointer_t rx_tail_copy_;
static app3xxnic_queue_pointer_t * rx_tail_;
static app3xxnic_queue_pointer_t rx_head_;

#define TX_NUMBER_OF_DESCRIPTORS 64 /* We only use one, but 64 is the minimum. */
#define TX_BUFFER_SIZE 1518	    /* Maximum packet size. */

static app3xxnic_dma_descriptor_t * tx_descriptors_;
static void * tx_buffer_;
static int tx_enabled_ = 0;
static app3xxnic_queue_pointer_t tx_tail_copy_;
static app3xxnic_queue_pointer_t * tx_tail_;
static app3xxnic_queue_pointer_t tx_head_;

DEFINE_ALIGN_BUFFER(unsigned char, rx_pkt_buf, 4096, 64);

/*
  ======================================================================
  ======================================================================
  ======================================================================
  Test Functions.
  ======================================================================
  ======================================================================
  ======================================================================
*/

#if 0
static void
dump_configuration(void)
{
	printf("RX: CONF:0x%lx MODE:0x%lx VLAN:0x%lx\n",
	       (unsigned long)readl(APP3XXNIC_RX_CONF),
	       (unsigned long)readl(APP3XXNIC_RX_MODE),
	       (unsigned long)readl(APP3XXNIC_RX_BASE+0x1d0));
	printf("TX: WM:0x%lx EXCONF:0x%lx CONF:0x%lx TVCONF:0x%lx MODE:0x%lx\n",
	       (unsigned long)readl(APP3XXNIC_TX_WATERMARK),
	       (unsigned long)readl(APP3XXNIC_TX_EXTENDED_CONF),
	       (unsigned long)readl(APP3XXNIC_TX_CONF),
	       (unsigned long)readl(APP3XXNIC_TX_TIME_VALUE_CONF),
	       (unsigned long)readl(APP3XXNIC_TX_MODE));
}
#endif

static void
dump_rx_stats(void)
{
	printf("RX: SMII:0x%lx VLAN:0x%lx OK:0x%lx OV:0x%lx CRC:0x%lx "
	       "ALIGN:0x%lx US:0x%lx\n",
	       (unsigned long)readl(APP3XXNIC_RX_SMII_STATUS),
	       (unsigned long)readl(APP3XXNIC_RX_BASE+0x270),
	       (unsigned long)readl(APP3XXNIC_RX_STAT_PACKET_OK),
	       (unsigned long)readl(APP3XXNIC_RX_STAT_OVERFLOW),
	       (unsigned long)readl(APP3XXNIC_RX_STAT_CRC_ERROR),
	       (unsigned long)readl(APP3XXNIC_RX_STAT_ALIGN_ERROR),
	       (unsigned long)readl(APP3XXNIC_RX_BASE+0x280));
	printf("RX counts: 64:0x%lx 65_127:0x%lx 128_255:0x%lx 256_511:0x%lx "
	       "512_1023:0x%lx 1024_MAX:0x%lx OV:0x%lx\n",
	       (unsigned long)readl(APP3XXNIC_RX_BASE+0x288),
	       (unsigned long)readl(APP3XXNIC_RX_BASE+0x290),
	       (unsigned long)readl(APP3XXNIC_RX_BASE+0x298),
	       (unsigned long)readl(APP3XXNIC_RX_BASE+0x2a0),
	       (unsigned long)readl(APP3XXNIC_RX_BASE+0x2a8),
	       (unsigned long)readl(APP3XXNIC_RX_BASE+0x2b0),
	       (unsigned long)readl(APP3XXNIC_RX_BASE+0x2b8));
}

/*
  ----------------------------------------------------------------------
  lsi_femac_receive_test
*/

void
lsi_femac_receive_test(struct eth_device *dev)
{

	bd_t * bd = gd->bd;
	int packets_received = 0;

	rx_debug = 1;
	rx_allow_all = 1;
	dump_packets = 1;
	dump_descriptors = 1;
	eth_halt( );

	if( 0 > eth_init( bd ) ) { eth_halt( ); return; }
	/*dump_configuration( );*/

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
  ===============================================================================
  ===============================================================================
  Loopback Tests
  ===============================================================================
  ===============================================================================
*/

typedef struct {
	void *address;
	int size;
	app3xxnic_queue_pointer_t queue_pointer;
} packet_header_t;

#define MAX_PACKET_SIZE 1536
#define PACKET_LOG_NUMBER 100

/*
  -------------------------------------------------------------------------------
  dump_everything
*/

#if 0
static void
dump_everything(void)
{
	app3xxnic_dma_descriptor_t *descriptor;
	void *packet;
	char buffer[80];
	int i;

	/* heads, tails, sizes, ... */
	printf("<rx tc=0x%p:0x%lx t=0x%p:0x%lx h=0x%p:0x%lx>\n",
	       &rx_tail_copy_, rx_tail_copy_.raw,
	       rx_tail_, rx_tail_->raw,
	       &rx_head_, rx_head_.raw);

	printf("<rx descriptors adr=0x%p num=0x%x>\n",
	       rx_descriptors_, rx_number_of_descriptors);

	printf("<rx buffers adr=0x%p sz=0x%x szpd=0x%x nmd=0x%x>\n",
	       rx_buffer_, rx_buffer_size, rx_buffer_per_descriptor,
	       rx_number_of_descriptors);
	
	printf("<tx tc=0x%p:0x%lx t=0x%p:0x%lx h=0x%p:0x%lx>\n",
	       &tx_tail_copy_, tx_tail_copy_.raw,
	       tx_tail_, tx_tail_->raw,
	       &tx_head_, tx_head_.raw);

	printf("<tx descriptors adr=0x%p num=0x%x>\n",
	       tx_descriptors_, TX_NUMBER_OF_DESCRIPTORS);

	printf("<tx buffer adr=0x%p sz=0x%x>\n",
	       tx_buffer_, TX_BUFFER_SIZE);

	/* femac registers */
	dump_configuration();
	dump_rx_stats();

	/* phy registers */
	for (i = 0; i < 0x20; ++i) {
		if (i >= 0xa && i < 0x10)
			continue;
		printf("mdio register 0x%02x = 0x%04x\n",
		       i, mdio_read(phy_address_, i));
	}

	mdio_write(phy_address_, 0x1f, 0x8b); /* Enable Shadow Registers */

	for (i = 0x1a; i < 0x1f; ++i) {
		printf("mdio shadow register 0x%02x = 0x%04x\n",
		       i, mdio_read(phy_address_, i));
	}

	mdio_write(phy_address_, 0x1f, 0x0b); /* Disable Shadow Registers */

	dump_descriptors = 1;

	/* descriptors (rx) */
	descriptor = rx_descriptors_;

	while ((unsigned long)descriptor <
	       ((unsigned long)rx_descriptors_ +
		(rx_number_of_descriptors *
		 sizeof(app3xxnic_dma_descriptor_t)))) {
		DUMP_DESCRIPTOR_(descriptor);
		++descriptor;
	}

	/* descriptors (tx) */
	descriptor = tx_descriptors_;

	while ((unsigned long)descriptor <
	       ((unsigned long)tx_descriptors_ +
		(TX_NUMBER_OF_DESCRIPTORS *
		 sizeof(app3xxnic_dma_descriptor_t)))) {
		DUMP_DESCRIPTOR_(descriptor);
		++descriptor;
	}

	dump_descriptors = 0;

	/* buffers (rx) */

	packet = rx_buffer_;

	for (i = 0; i < rx_number_of_descriptors; ++i) {
		sprintf(buffer, "rx buffer %d", i);
		axxia_dump_packet(buffer, packet, rx_buffer_per_descriptor);
		packet += rx_buffer_per_descriptor;
	}

	/* buffers (tx) */

	axxia_dump_packet("tx buffer 1", tx_buffer_, TX_BUFFER_SIZE);

	return;
}
#endif

/*
  -------------------------------------------------------------------------------
  mac_loopback_test

  Have the MAC loop packets back to the PNY.
*/

static void
mac_loopback_test(struct eth_device *device)
{
	void *input = (void *)rx_pkt_buf;
	int size;
	int looped = 0;

	for (;;) {
		if (ctrlc())
			break;	

		if (0 == (size = eth_rx()))
			continue;

		if (size != eth_send(input, size))
			printf("eth_send() failed: index %d\n", looped);
		else
			++looped;
	}

	printf("Looped back %d packets\n", looped);

	return;
}

/*
  -------------------------------------------------------------------------------
  phy_loopback_test

  Have the PHY loop packets back to the mac.
*/

#define PHY_LOOPBACK_PACKET_SIZE 1200

static void
phy_loopback_test(struct eth_device *device)
{
	void *out = NULL;
	void *in = (void *)rx_pkt_buf;
	int iteration = 0;
	int size;
	int i;

	/* Drop any existing packets. */
	while (0 != eth_rx())
		printf("Dropping pre-existing packet.\n");

	/* Write a known pattern to the buffers. */
	memset(rx_buffer_, 0x5a,
	       (rx_number_of_descriptors * rx_buffer_per_descriptor));
	memset(tx_buffer_, 0x7f, TX_BUFFER_SIZE);

	/*dump_everything();*/
	out = malloc(PHY_LOOPBACK_PACKET_SIZE);

	if (NULL == out) {
		printf("Couldn't allocate output packet.\n");
		goto phy_loopback_test_over;
	}

	for (;;) {
		int retries = 100000;
		unsigned char *packet;
		int count;

		if (ctrlc())
			break;

		/* As a sort of "random" data, use part of the U-Boot text. */
		/*memcpy(out, (void *)0x1000, PHY_LOOPBACK_PACKET_SIZE);*/

		/* Put a pattern in "out". */
		packet = out;
		count = iteration;

		for (i = 0; i < PHY_LOOPBACK_PACKET_SIZE; ++i) {
			*packet++ = (unsigned char)count++;

			if (0xff < count)
				count = 0;
		}

		/*
		  Fix up the header.
		*/

		((char *)out)[0]  = device->enetaddr[0];
		((char *)out)[1]  = device->enetaddr[1];
		((char *)out)[2]  = device->enetaddr[2];
		((char *)out)[3]  = device->enetaddr[3];
		((char *)out)[4]  = device->enetaddr[4];
		((char *)out)[5]  = device->enetaddr[5];
		((char *)out)[6]  = device->enetaddr[0];
		((char *)out)[7]  = device->enetaddr[1];
		((char *)out)[8]  = device->enetaddr[2];
		((char *)out)[9]  = device->enetaddr[3];
		((char *)out)[10] = device->enetaddr[4];
		((char *)out)[11] = device->enetaddr[5];

		((char *)out)[12] = 0x00;
		((char *)out)[13] = 0x40;

		axxia_dump_packet_tx("PHY Loopback TX", out,
				     PHY_LOOPBACK_PACKET_SIZE);

		if (PHY_LOOPBACK_PACKET_SIZE !=
		    eth_send(out, PHY_LOOPBACK_PACKET_SIZE)) {
			printf("Error sending packet.\n");
			goto phy_loopback_test_over;
		}

		do {
			size = eth_rx();

			if (0 == size)
				udelay(10);
		} while (0 == size && 0 < --retries);

		if (0 == retries) {
			printf("Timed out waiting for packet!\n");
			goto phy_loopback_test_over;
		}

		axxia_dump_packet_rx("PHY Loopback RX", out, size);

		if (PHY_LOOPBACK_PACKET_SIZE != size) {
			printf("Error receiving packet (size=%d).\n", size);
			goto phy_loopback_test_over;
		}

		if (0 != memcmp(in, out, PHY_LOOPBACK_PACKET_SIZE)) {
			printf("ERROR: Bad Packet Received (iteration %d).\n\n",
				iteration);
			/*dump_everything();*/
			axxia_dump_packet("out", out, size);
			axxia_dump_packet("in", in, size);
		}

		while (0 != (size = eth_rx())) {
			printf("ERROR: Extra Packet Received (iteration %d).\n\n",
			       iteration);
			/*dump_everything();*/
		}

		++iteration;
	}

phy_loopback_test_over:

	printf("Ran test %d times.\n", iteration);

	if (NULL != out)
		free(out);

	return;
}

/*
  ----------------------------------------------------------------------
  lsi_femac_loopback_test
*/

void
lsi_femac_loopback_test(struct eth_device *dev, int type)
{
	bd_t *bd = gd->bd;

	rx_allow_all = 1;
	rx_debug = 1;
	loopback = 1;

	eth_halt();

	if (0 > eth_init(bd)) {
		eth_halt( );
		return;
	}

	switch (type) {
	case 1:
		mac_loopback_test(dev);
		break;
	case 2:
		phy_loopback_test(dev);
		break;
	default:
		printf("Unknown test type.\n");
		break;
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

/*
  ------------------------------------------------------------------------------
  allocate_dma_memory
*/

#if 0
static void *
allocate_dma_memory(size_t size)
{
#if defined(CONFIG_AXXIA_ARM)
	if ((256 * 1024) < size)
		return NULL;
	else
		return (void *)0x3c0000UL;
#elif defined(CONFIG_AXXIA_PPC)
	return malloc(size);
#else
#error "Unknown Architecture!"
#endif
}
#endif

#if 0

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
#endif

static inline void
readdescriptor(unsigned long address, app3xxnic_dma_descriptor_t *descriptor)
{
        memcpy(descriptor, (void *) address, sizeof(app3xxnic_dma_descriptor_t));
        return;
}

static inline void
writedescriptor(unsigned long address,
                 const app3xxnic_dma_descriptor_t *descriptor)
{
	DEBUG_PRINT("address=0x%lx descriptor=0x%p size=%lu\n",
		    address, descriptor, sizeof(app3xxnic_dma_descriptor_t));
        memcpy((void *) address, descriptor, sizeof(app3xxnic_dma_descriptor_t));
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

static void
queue_increment_(app3xxnic_queue_pointer_t *queue, int size)
{
	queue->bits.offset += sizeof(app3xxnic_dma_descriptor_t);

	if ((size * sizeof(app3xxnic_dma_descriptor_t)) == queue->bits.offset) {
		queue->bits.offset = 0;
		queue->bits.generation_bit =
			(0 == queue->bits.generation_bit) ? 1 : 0;
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
	DEBUG_PRINT( "smii_status_=0x%lx\n",
		     * ( (  unsigned long * )
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
#if 0
		rx_configuration_ |= APP3XXNIC_RX_CONF_RXFCE;
		rx_configuration_ |= APP3XXNIC_RX_CONF_TXFCE;
#endif
		rx_enabled_ = 1;

	} else {

		rx_enabled_ = 0;

	}

	rx_configuration_ |= 0x4;

	writel( rx_configuration_, APP3XXNIC_RX_CONF );

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

	rx_configuration_ = readl( APP3XXNIC_RX_CONF );
	rx_configuration_ &= ~ APP3XXNIC_RX_CONF_ENABLE;
	writel( rx_configuration_, APP3XXNIC_RX_CONF );
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
tx_enable_(struct eth_device *device)
{
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

	if (0 == loopback) {
		tx_configuration_ |= APP3XXNIC_TX_CONF_ENABLE_SWAP_SA;
		swap_source_address_ =
			((device->enetaddr[4]) << 8) | device->enetaddr[5];
		writel(swap_source_address_, APP3XXNIC_SWAP_SOURCE_ADDRESS_2);
		swap_source_address_ =
			((device->enetaddr[2]) << 8) | device->enetaddr[3];
		writel(swap_source_address_, APP3XXNIC_SWAP_SOURCE_ADDRESS_1);
		swap_source_address_ =
			((device->enetaddr[0]) << 8) | device->enetaddr[1];
		writel(swap_source_address_, APP3XXNIC_SWAP_SOURCE_ADDRESS_0);
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

	writel( tx_configuration_, APP3XXNIC_TX_CONF );

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
	tx_configuration_ = readl( APP3XXNIC_TX_CONF );
	tx_configuration_ &= ~ APP3XXNIC_TX_CONF_ENABLE;
	writel( tx_configuration_, APP3XXNIC_TX_CONF );
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

	if (0 == dump_descriptors)
		return;

	readdescriptor( ( unsigned long ) address, & descriptor );

	if( ( void * ) rx_descriptors_ <= address &&
	    address <
	    ( void * ) ( (unsigned long)rx_descriptors_ +
			 ( rx_number_of_descriptors *
			   sizeof( app3xxnic_dma_descriptor_t ) ) ) ) {
		rx = 1;
	}

#ifdef DUMP_DESCRIPTOR_COMPACT
	printf( "<%lu:%s:0x%x:bs=%d,ioc=%d,eop=%d,sop=%d,w=%d,tt=0x%x,pdul=0x%x,"
		"dtl=0x%x,tma=0x%x,hdmp=0x%x>\n",
		line, ( 1 == rx ) ? "RX" : "TX",
		( unsigned int )( address - ( void * ) rx_descriptors_ ),
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

static void dump_packet_(const char *header, void *packet, int length)
{
	char buffer[256];
	char *string;
	unsigned long offset = 0;
	int i;
	unsigned char *data = packet;

	if (0 == dump_packets)
		return;

	printf("---- %s (%d bytes)\n", header, length);

	while (0 < length) {
		int this_line;

		string = buffer;
		string += sprintf(string, "%06lx ", offset);
		this_line = (16 > length) ? length : 16;

		for (i = 0; i < this_line; ++i) {
			string += sprintf(string, "%02x ", *data++);
			--length;
			++offset;
		}

		printf("%s\n", buffer);
	}

	printf("\n");
}

#endif	/* DUMP_PACKETS */

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


#if 0
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
#endif

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

	DEBUG_PRINT( "\n");
	ad_value_string_ = getenv( "ad_value" );
	DEBUG_PRINT( "\n");

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
#if 0
		saveenv( );
#endif

	}

	DEBUG_PRINT( "\n");
	/* that's all */
	return return_value_;
}

/*
  ----------------------------------------------------------------------
  phy_enable_
*/

static int
phy_enable_(int phy)
{
	char *macspeed = (char *)0;
	int link_retries;
#if 0
	unsigned long value;
#endif

	phy_address_ = phy;

#if 0
	/* Access Shadow reg 0x1d */
	value = mdio_read( phy_address_, PHY_BCM_TEST_REG );
	value |= 0x80;
	mdio_write( phy_address_, PHY_BCM_TEST_REG, value);

	/* Set RX FIFO size to 0x7 */
	mdio_write( phy_address_, PHY_AUXILIARY_MODE3, 0x7);
	
	/* Back to regular register access. */
	value &= ~0x80;
	mdio_write( phy_address_, PHY_BCM_TEST_REG, value);
#endif

	macspeed = getenv( "macspeed" );

	/*
	  Set up the phy.
	*/

	if( 0 == strncmp(macspeed, "auto", strlen("auto") ) ) {
		if (0 != phy_renegotiate(phy, get_env_ad_value())) {
			printf( "PHY: Auto Negotiation Failed.\n" );
			return -1;
		}
	} else {
		int speed;
		int duplex;

		if( 0 == strncmp(macspeed, "100MF", strlen("100MF") ) ) {
			speed = 1;
			duplex = 1;
		} else if( 0 == strncmp(macspeed, "100MH", strlen("100MH") ) ) {
			speed = 1;
			duplex = 0;
		} else if( 0 == strncmp(macspeed, "10MF", strlen("10MF") ) ) {
			speed = 0;
			duplex = 1;
		} else /*if( 0 == strncmp(macspeed, "10MH", strlen("10MH") ) ) */ {
			speed = 0;
			duplex = 0;
		}

		if (0 != phy_set(phy, speed, duplex)) {
			printf("PHY: Setup Failed.\n");
			return -1;
		}
	}

	/*
	  Verify that there is a link.
	*/

	link_retries = 100;

	while ((0 == phy_link(phy)) &&
	       (0 < --link_retries)) {
		mdelay(1);
	}

	if (0 == link_retries) {
		printf("PHY: no link\n");
		return -1;
	}

	printf("PHY: %s %s\n",
	       0 == phy_speed(phy) ? "10M" : "100M",
	       0 == phy_duplex(phy) ? "Half Duplex" : "Full Duplex");

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

		tx_packets_ += readl( registers_ [ index_ ] );

	}

	/* that's all */
	return tx_packets_;

}

#endif

/*
  ----------------------------------------------------------------------
  lsi_femac_eth_init
*/

int
lsi_femac_eth_init(struct eth_device *dev, bd_t *board_info)
{
	size_t memory_needed;
	void *temp;

	TRACE_BEGINNING( "\n" );

	/* Don't initialize twice. */
	if( 0 != initialized_ ) {
		eth_halt( );
	}

	/* Set the FEMAC to uncached. */
#if 0
	writel( 0, (GPREG + 0x78));
	printf("HPROT: 0x%x\n", readl(GPREG + 0x78));
#endif

	/* Reset the MAC */
	writel( 0x80000000, APP3XXNIC_DMA_PCI_CONTROL );

	/*
	  Decide which interface to use, ARM attached MAC or the Management Port
	*/

	/*
	  -- WORKAROUND -- WORKAROUND -- WORKAROUND -- WORKAROUND -- WORKAROUND --
	  This is the software work around for defect 15129.  Use 64 byte
	  buffers for receive descriptors for all dma.
	  -- WORKAROUND -- WORKAROUND -- WORKAROUND -- WORKAROUND -- WORKAROUND --
	*/

#if 0
#ifndef CONFIG_ACP
	if( 1 >= APP3XX_REVISION ) {
		printf( "++ Using work around for defect 15129\n" );
		rx_number_of_descriptors = 512;
		rx_buffer_size = ( 32 * 1024 );
		rx_buffer_per_descriptor = ( rx_buffer_size / rx_number_of_descriptors );
	}
#endif
#endif

	/* Assert that the number of descriptors is a multiple of 64. */

	if( ( 0 != ( rx_number_of_descriptors % DESCRIPTOR_GRANULARITY ) ) ||
	    ( 0 != ( TX_NUMBER_OF_DESCRIPTORS % DESCRIPTOR_GRANULARITY ) ) ) {
		printf( "Number of descriptors is not a multiple of 64! " \
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

#if 0
	if (NULL == (memory = allocate_dma_memory(memory_needed))) {
		printf("Unable to allocate space for descriptors and buffers\n");
		return 1;
	}
#else
#ifdef USE_LSM
#error "GOT HERE!"
	writel(0x2020, (GPREG + 0x4));
	memory = (void *)(0xa0000000);
#else
	/*memory = (void *)((4 * 1024 * 1024) - (256 * 1024));*/
#if 1
	memory =(void *)0x40000000ULL;
#else
	/*
	  This was a test -- Use LSM instead of system memory for DMA.
	*/

	{
	  unsigned long value;

	  memory =(void *)LSM;
	  value = readl(0x8080230018);
	  value |= 0x800000;
	  writel(value, 0x8080230018);
	}
#endif
#endif
	printf("FEMAC: Used %zu of 0x%x at 0x%p\n",
	       memory_needed, (256 * 1024), memory);
#endif

	/*
	  Set the zone to allow access by non-secure masters (the FEMAC).
	*/
#ifdef CONFIG_AXXIA_25xx
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

	  writel(tzc_address, 0xf0941110);
	  writel(0, 0xf0941114);
	  writel(0xf0000001 | (tzc_size_field << 1), 0xf0941118);
	}
#endif
#endif

	temp = memory;

	DEBUG_PRINT("temp=0x%p ALIGN64B(temp)=0x%llx\n",
		    temp, ALIGN64B(temp));
	rx_descriptors_ = ( app3xxnic_dma_descriptor_t * ) ALIGN64B( temp );
	temp = ( void * )
		( ( unsigned long ) rx_descriptors_ + 
		  ( rx_number_of_descriptors * sizeof( app3xxnic_dma_descriptor_t ) ) );
	DEBUG_PRINT( "temp=0x%p rx_descriptors_=0x%p\n",
		     temp, rx_descriptors_ );
	/*printf( "rx_descriptors_=0x%08x\n", rx_descriptors_ );*/

	DEBUG_PRINT("temp=0x%p ALIGN64B(temp)=0x%llx\n",
		    temp, ALIGN64B(temp));
	tx_descriptors_ = ( app3xxnic_dma_descriptor_t * ) ALIGN64B( temp );
	temp = ( void * )
		( ( unsigned long ) tx_descriptors_ + 
		  ( TX_NUMBER_OF_DESCRIPTORS * sizeof( app3xxnic_dma_descriptor_t ) ) );
	DEBUG_PRINT( "temp=0x%p tx_descriptors_=0x%p\n", temp, tx_descriptors_ );
	/*printf( "tx_descriptors_=0x%08x\n", tx_descriptors_ );*/

	DEBUG_PRINT("temp=0x%p ALIGN64B(temp)=0x%llx\n",
		    temp, ALIGN64B(temp));
	rx_buffer_ = ( void * ) ALIGN64B( temp );
	temp = ( void * ) ( ( unsigned long ) rx_buffer_ + rx_buffer_size );
	DEBUG_PRINT( "rx_buffer_=0x%p\n", rx_buffer_ );
	/*printf( "rx_buffer_=0x%x\n", rx_buffer_ );*/

	DEBUG_PRINT("temp=0x%p ALIGN64B(temp)=0x%llx\n",
		    temp, ALIGN64B(temp));
	tx_buffer_ = ( void * ) ALIGN64B( temp );
	temp = ( void * ) ( ( unsigned long ) tx_buffer_ + TX_BUFFER_SIZE );
	DEBUG_PRINT( "tx_buffer_=0x%p\n", tx_buffer_ );
	/*printf( "tx_buffer_=0x%x\n", tx_buffer_ );*/

	DEBUG_PRINT("temp=0x%p ALIGN(temp, %lu)=0x%llx\n",
		    temp, sizeof(app3xxnic_queue_pointer_t),
		    ALIGN(temp, sizeof(app3xxnic_queue_pointer_t)));
	rx_tail_ = ( void * ) ALIGN( temp, sizeof( app3xxnic_queue_pointer_t ) );
	temp = ( void * ) ( rx_tail_ + sizeof( app3xxnic_queue_pointer_t ) );
	DEBUG_PRINT( "rx_tail_=0x%p\n", rx_tail_ );
	/*printf( "rx_tail_=0x%x\n", rx_tail_ );*/

	DEBUG_PRINT("temp=0x%p ALIGN(temp, %lu)=0x%llx\n",
		    temp, sizeof(app3xxnic_queue_pointer_t),
		    ALIGN(temp, sizeof(app3xxnic_queue_pointer_t)));
	tx_tail_ = ( void * ) ALIGN( temp, sizeof( app3xxnic_queue_pointer_t ) );
	temp = ( void * ) ( tx_tail_ + sizeof( app3xxnic_queue_pointer_t ) );
	DEBUG_PRINT( "tx_tail_=0x%p\n", tx_tail_ );
	/*printf( "tx_tail_=0x%x\n", tx_tail_ );*/

	/* Initialize descriptors. */

	{
		app3xxnic_dma_descriptor_t descriptor_;
		void * buffer_;
		int index_;

		buffer_ = rx_buffer_;
		DEBUG_PRINT("buffer_=0x%p rx_buffer_=0x%p rx_buffer_per_descriptor=0x%x\n",
			    buffer_, rx_buffer_, rx_buffer_per_descriptor);

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
	writel( 0x0, APP3XXNIC_RX_SOFT_RESET );
	writel( 0x1, APP3XXNIC_RX_MODE );
	writel( 0x0, APP3XXNIC_TX_SOFT_RESET );
	writel( 0x1, APP3XXNIC_TX_MODE );

#ifdef CONFIG_AXXIA_EMU
	writel( 0x7f007f, APP3XXNIC_TX_WATERMARK );
#else
	writel( 0x300a, APP3XXNIC_TX_WATERMARK );
#endif

	writel( 0x1, APP3XXNIC_TX_HALF_DUPLEX_CONF );
	writel( 0xffff, APP3XXNIC_TX_TIME_VALUE_CONF );
	writel( 0x1, APP3XXNIC_TX_INTERRUPT_CONTROL );
	writel( 0x5275, APP3XXNIC_TX_EXTENDED_CONF );
	writel( 0x1, APP3XXNIC_RX_INTERNAL_INTERRUPT_CONTROL );
	writel( 0x1, APP3XXNIC_RX_EXTERNAL_INTERRUPT_CONTROL );
	writel( 0x40010000, APP3XXNIC_DMA_PCI_CONTROL );
	writel( 0x30000, APP3XXNIC_DMA_CONTROL );
	writel( 0x280044, APP3XXNIC_DMA_BASE + 0x60 );
	writel( 0xc0, APP3XXNIC_DMA_BASE + 0x64 );

	/*
	  Update the tail pointer addresses and queue sizes.  The transmit
	  head pointer will be updated when there is something to transmit.
	*/

#ifdef USE_LSM
	writel(((unsigned int )rx_descriptors_ - 0x80000000),
	       APP3XXNIC_DMA_RX_QUEUE_BASE_ADDRESS );
#else
	{
	  unsigned long offset;

	  offset = (unsigned long)
	    ((unsigned long long)rx_descriptors_ & 0xffffffffULL);
	  DEBUG_PRINT("offset=0x%lx rx_descriptors_=0x%p\n",
		      offset, rx_descriptors_);
	  writel(offset, APP3XXNIC_DMA_RX_QUEUE_BASE_ADDRESS );
	}
#endif
	writel( ( unsigned int )
		 ( ( rx_number_of_descriptors *
		     sizeof( app3xxnic_dma_descriptor_t ) ) / 1024 ),
		 APP3XXNIC_DMA_RX_QUEUE_SIZE );

	memset( ( void * ) & rx_tail_copy_.raw, 0,
		sizeof( app3xxnic_queue_pointer_t ) );

	memset( ( void * ) rx_tail_, 0, sizeof( app3xxnic_queue_pointer_t ) );
#ifdef USE_LSM
	writel(((unsigned long)rx_tail_ - 0x80000000),
	       APP3XXNIC_DMA_RX_TAIL_POINTER_ADDRESS);
#else
	writel((unsigned long)rx_tail_, APP3XXNIC_DMA_RX_TAIL_POINTER_ADDRESS);
#endif

	writel( 3, APP3XXNIC_DMA_BASE + 0x1c );

#ifdef USE_LSM
	writel(((unsigned int)tx_descriptors_ - 0x80000000),
	       APP3XXNIC_DMA_TX_QUEUE_BASE_ADDRESS);
#else
	{
	  unsigned long offset;

	  offset = (unsigned long)
	    ((unsigned long long)tx_descriptors_ & 0xffffffffULL);
	  DEBUG_PRINT("offset=0x%lx tx_descriptors_=0x%p\n",
		      offset, tx_descriptors_);
	  writel(offset, APP3XXNIC_DMA_TX_QUEUE_BASE_ADDRESS);
	}
#endif
	writel( ( unsigned int )
		 ( TX_NUMBER_OF_DESCRIPTORS *
		   sizeof( app3xxnic_dma_descriptor_t ) / 1024 ),
		 APP3XXNIC_DMA_TX_QUEUE_SIZE );

	memset( ( void * ) & tx_tail_copy_.raw, 0,
		sizeof( app3xxnic_queue_pointer_t ) );

	memset( ( void * ) tx_tail_, 0, sizeof( app3xxnic_queue_pointer_t ) );
#ifdef CONFIG_LSM
	writel(((unsigned long)tx_tail_ - 0x80000000),
	       APP3XXNIC_DMA_TX_TAIL_POINTER_ADDRESS);
#else
	writel((unsigned long)tx_tail_, APP3XXNIC_DMA_TX_TAIL_POINTER_ADDRESS);
#endif

	rx_tail_->raw = readl( APP3XXNIC_DMA_RX_TAIL_POINTER_LOCAL_COPY );
	rx_tail_copy_.raw = rx_tail_->raw;
	rx_head_.raw = rx_tail_->raw;
	queue_decrement_( & rx_head_, rx_number_of_descriptors );
	rx_head_.bits.generation_bit =
		( 0 == rx_head_.bits.generation_bit ) ? 1 : 0;
	DEBUG_PRINT( "rx_head_.raw=0x%lx rx_tail_->raw=0x%lx "
		     "rx_tail_copy_.raw=0x%lx\n",
		     rx_head_.raw, rx_tail_->raw, rx_tail_copy_.raw );
	writel( rx_head_.raw, APP3XXNIC_DMA_RX_HEAD_POINTER );

	tx_tail_->raw = readl( APP3XXNIC_DMA_TX_TAIL_POINTER_LOCAL_COPY );
	tx_tail_copy_.raw = tx_tail_->raw;
	tx_head_.raw = tx_tail_->raw;
	DEBUG_PRINT( "tx_head_.raw=0x%08lx\n", tx_head_.raw );
	writel( tx_head_.raw, APP3XXNIC_DMA_TX_HEAD_POINTER );

	/*
	  Enable the PHY, RX, and TX, unless booting in band.
	*/

	DEBUG_PRINT( "tx_head_.raw=0x%08lx\n", tx_head_.raw );
	mdio_initialize();
	DEBUG_PRINT( "tx_head_.raw=0x%08lx\n", tx_head_.raw );

	{

		int retries_ = 10;

		DEBUG_PRINT( "\n");
		while( 0 != phy_enable_( phy_address_ ) ) {

			printf( "Failed to initialize the PHY, retrying!\n" );

			if( 0 == -- retries_ ) { break; }

		}

		DEBUG_PRINT( "\n");
		if( 0 != rx_enable_( ) ) {

			printf( "Receiver not enabled, link down?\n" );

		}

		DEBUG_PRINT( "\n");
		if( 0 != tx_enable_(dev) ) {

			printf( "Transmitter not enabled, link down?\n" );

		}

	}

		DEBUG_PRINT( "\n");
#ifdef EH_STATS
	if(0 == eh_stats_initialized) {
		printf("Clearing the eh_stats structure.\n");
		memset((void *)eh_stats, 0, sizeof(eh_stats_t));
		eh_stats_initialized = 1;
	}
#endif /* EH_STATS */

	/* set the "initialized" flag */	
		DEBUG_PRINT( "\n");
		initialized_ = 1;

	/* that's all */	
		DEBUG_PRINT( "\n");
		TRACE_ENDING( "\n" );
	return 0;

}

/*
  ----------------------------------------------------------------------
  lsi_femac_eth_halt
*/

void lsi_femac_eth_halt(struct eth_device *device) {

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
#if 0
	free( memory );
#endif

	/* disable the MAC */
	writel( 0, APP3XXNIC_RX_MODE );
	writel( 1, APP3XXNIC_RX_SOFT_RESET );
	writel( 0, APP3XXNIC_TX_MODE );
	writel( 1, APP3XXNIC_TX_SOFT_RESET );

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
lsi_femac_eth_rx(struct eth_device *dev)
{
	int bytes_received_ = 0;
	app3xxnic_queue_pointer_t queue_;
	app3xxnic_dma_descriptor_t descriptor_;
	int packet_available_ = 0;
	void *destination_;
	unsigned long overflow_, ok_, crc_, align_;
	int head_changed_;

	/* If no packet is available, return 0.	*/
	queue_.raw = rx_tail_copy_.raw;

	while (0 < queue_initialized_(swab_queue_pointer(rx_tail_),
				      queue_, rx_number_of_descriptors)) {
		readdescriptor(((unsigned long)rx_descriptors_ +
				queue_.bits.offset), &descriptor_);
		DUMP_DESCRIPTOR_(&descriptor_);

		if (0 != descriptor_.end_of_packet) {
			packet_available_ = 1;
			break;
		} else {
			queue_increment_(&queue_, rx_number_of_descriptors);
		}
	}

	if (0 == packet_available_)
		return 0;

	/* Get the packet. */
	destination_ = (void *)rx_pkt_buf;

	readdescriptor(((unsigned long)rx_descriptors_ +
			rx_tail_copy_.bits.offset), &descriptor_);
	DUMP_DESCRIPTOR_(&descriptor_);

	while (0 < queue_initialized_(swab_queue_pointer(rx_tail_),
				      rx_tail_copy_, rx_number_of_descriptors)) {
		memcpy(destination_, (void *)((unsigned long long)descriptor_.host_data_memory_pointer),
		       descriptor_.pdu_length);
		destination_ += descriptor_.pdu_length;
		bytes_received_ += descriptor_.pdu_length;
		queue_increment_(&rx_tail_copy_, rx_number_of_descriptors);

		if (0 != descriptor_.end_of_packet)
			break;

		readdescriptor(((unsigned long) rx_descriptors_ +
				rx_tail_copy_.bits.offset), &descriptor_);
	}

	overflow_ = readl(APP3XXNIC_RX_STAT_OVERFLOW);
	ok_ = readl(APP3XXNIC_RX_STAT_PACKET_OK);
	crc_ = readl(APP3XXNIC_RX_STAT_CRC_ERROR);
	align_ = readl(APP3XXNIC_RX_STAT_ALIGN_ERROR);

	if (0 == descriptor_.end_of_packet ||
	    0 != overflow_ ||
	    0 != crc_ ||
	    0 != align_) {
		printf("Bad Packet: "
		       "bytes=%d ovf=%ld ok=%ld "
		       "crc=%ld align=%ld\n",
		       bytes_received_, overflow_, ok_,
		       crc_, align_ );
	} else {
		unsigned char broadcast_[] = {
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff
		};

		destination_ = (unsigned char *)rx_pkt_buf;

		if (0 != rx_allow_all ||
		    0 == memcmp((const void *)
				&(((unsigned char *)destination_)[0]),
				(const void *)&(dev->enetaddr[0]), 6) ||
		    0 == memcmp((const void *)
				&(((unsigned char *)destination_)[0]),
				(const void *)&(broadcast_[0]), 6)) {
			if (0 == rx_debug) {
				/*dump_packets = 1;*/
				DUMP_PACKET("Sending to Stack",
					    rx_pkt_buf, bytes_received_);
				dump_packets = 0;
				NetReceive(rx_pkt_buf, bytes_received_);
			}
		}
	}

	/* Update the rx descriptor queue. */
	head_changed_ = 0;

	while (1 < queue_uninitialzed_(rx_head_, rx_tail_copy_,
				       rx_number_of_descriptors)) {
		readdescriptor(((unsigned long)rx_descriptors_ +
				rx_head_.bits.offset), &descriptor_);
		descriptor_.data_transfer_length = rx_buffer_per_descriptor;
		descriptor_.write = 1;
		descriptor_.interrupt_on_completion = 1;
		descriptor_.byte_swapping_on = 0;
		writedescriptor(((unsigned long)rx_descriptors_ +
				 rx_head_.bits.offset), &descriptor_);
		queue_increment_(&rx_head_, rx_number_of_descriptors);
		head_changed_ = 1;
	}

	if (0 != head_changed_)
		writel(rx_head_.raw, APP3XXNIC_DMA_RX_HEAD_POINTER);

	return bytes_received_;
}

/*
  ----------------------------------------------------------------------
  lsi_femac_eth_send
*/

int
lsi_femac_eth_send(struct eth_device *device,  void *packet, int length)
{
	int bytes_sent_ = 0;
	int tries_;

	/*dump_packet_("TX", packet, length);*/

	/*
	  Update tx_tail_copy_
	*/

	while( 0 < queue_initialized_( swab_queue_pointer( tx_tail_ ),
				       tx_tail_copy_,
				       TX_NUMBER_OF_DESCRIPTORS ) ) {
		queue_increment_( & tx_tail_copy_, TX_NUMBER_OF_DESCRIPTORS );
	}

	/*
	  If a transmit descriptor is available, allocate space for the
	  packet and initialize it.
	*/

	if( TX_NUMBER_OF_DESCRIPTORS >
	    queue_initialized_( tx_head_, swab_queue_pointer( tx_tail_ ),
				TX_NUMBER_OF_DESCRIPTORS ) ) {
		app3xxnic_dma_descriptor_t descriptor_;

		TX_DEBUG_PRINT( "Transmit descriptor available, "
				"head=0x%x/%d tail=0x%x/%d\n",
				tx_head_.bits.offset,
				tx_head_.bits.generation_bit, 
				tx_tail_->bits.offset,
				tx_tail_->bits.generation_bit );
		DEBUG_PRINT("tx_buffer_=0x%p packet=0x%p length=%d\n",
			    tx_buffer_, packet, length);
		memcpy( tx_buffer_, ( void * ) packet, length );
		readdescriptor( ( ( unsigned long ) tx_descriptors_ +
				  tx_head_.bits.offset ),
				& descriptor_ );
		DEBUG_PRINT("host_data_memory_pointer=0x%x\n",
			    descriptor_.host_data_memory_pointer);
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
		/* TODO: SORT THIS OUT!!!! */
		/*asm volatile ("mcr p15,0,%0,c7,c10,4" : : "r" (0));*/
		queue_increment_( & tx_head_, TX_NUMBER_OF_DESCRIPTORS );
		writel( tx_head_.raw, APP3XXNIC_DMA_TX_HEAD_POINTER );

		/* Wait for the transmit to finish. */
		tries_ = 10000;

		while ((tx_head_.raw != (tx_tail_->raw)) &&
		       (0 < --tries_)) {
#ifndef CONFIG_AXXIA_ARM
			__asm__ __volatile__ ( "eieio" );
			__asm__ __volatile__ ( "sync" );
#else
			dmb();
#endif
			udelay( 1000 );
		}

		if (0 == tries_) {
			printf("%s:%d - Transmit Timed Out!\n",
			       __FILE__, __LINE__);
			return -1;
		}

		bytes_sent_ = length;
	}

	return bytes_sent_;
}

/*
 */

int
lsi_femac_write_hwaddr(struct eth_device *device)
{
	return 0;
}
