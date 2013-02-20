/*
 *  Copyright (C) 2009 LSI Corporation
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

#include <common.h>
#include <asm/io.h>

#define WFC_TIMEOUT (400000)

#define LOCK_DOMAIN 0

static int ncr_tracer_disabled = 1;
static int ncr_sysmem_mode_disabled = 1;

#ifdef CONFIG_SPL_BUILD
void ncr_tracer_enable( void ) { ncr_tracer_disabled = 0; }
void ncr_tracer_disable( void ) { ncr_tracer_disabled = 1; }
int ncr_tracer_is_enabled( void ) { return 0 == ncr_tracer_disabled ? 1 : 0; }
void ncr_sysmem_init_mode_enable(void) { ncr_sysmem_mode_disabled = 0; }
void ncr_sysmem_init_mode_disable(void) { ncr_sysmem_mode_disabled = 1; }
#endif

static int
ncr_fail(const char *file, const char *function, const int line)
{
	if (1 == ncr_sysmem_mode_disabled)
		return -1;
	
	printf("Config Ring Access Failed: 0x%08x 0x%08x\n",
	       in_be32((u32 *)(NCA + 0xe4)), in_be32((u32 *)(NCA + 0xe8)));
	acp_failure(file, function, line);

	return -1;
}

#ifdef NCR_TRACER
static int short_read_count = 100;	/* Make sure this isn't in bss. */

void
ncr_trace_read8(unsigned long region, unsigned long offset)
{
	if (100 == short_read_count)
		short_read_count = 0;

	if (0 == short_read_count) {
		++short_read_count;
		printf("ncpRead   -w8 0.%lu.%lu.0x00%08lx",
		       NCP_NODE_ID(region), NCP_TARGET_ID(region), offset);
	} else {
		++short_read_count;

		if (64 == short_read_count) {
			printf(" 64\n");
			short_read_count = 0;
		}
	}

	return;
}

void
ncr_trace_read16(unsigned long region, unsigned long offset)
{
	printf("ncpRead    0.%lu.%lu.0x00%08lx 1\n",
	       NCP_NODE_ID(region), NCP_TARGET_ID(region), offset);

	return;
}

void
ncr_trace_read32(unsigned long region, unsigned long offset)
{
	printf("ncpRead    0.%lu.%lu.0x00%08lx 1\n",
	       NCP_NODE_ID(region), NCP_TARGET_ID(region), offset);

	return;
}

static int short_write_count = 100;	/* Make sure this isn't in bss. */

void
ncr_trace_write8(unsigned long region, unsigned long offset, unsigned long value)
{
	if (100 == short_write_count)
		short_write_count = 0;

	if (0 == short_write_count) {
		++short_write_count;
		printf("ncpWrite  -w8 0.%lu.%lu.0x00%08lx 0x%02lx",
		       NCP_NODE_ID(region), NCP_TARGET_ID(region),
		       offset, value);
	} else {
		++ short_write_count;
		printf(" 0x%02lx", value);

		if (4 == short_write_count) {
			printf("\n");
			short_write_count = 0;
		}
	}

	return;
}

void
ncr_trace_write16(unsigned long region,
		  unsigned long offset, unsigned long value)
{
	printf("ncpWrite   0.%lu.%lu.0x00%08lx 0x%04lx\n",
	       NCP_NODE_ID(region), NCP_TARGET_ID(region), offset, value);

	return;
}

void
ncr_trace_write32(unsigned long region,
		  unsigned long offset, unsigned long value)
{
	printf("ncpWrite   0.%lu.%lu.0x00%08lx 0x%08lx\n",
	       NCP_NODE_ID(region), NCP_TARGET_ID(region), offset, value);

	return;
}

void
ncr_trace_modify(unsigned long region,
		 unsigned long offset, unsigned long mask, unsigned long value)
{
	printf("ncpModify  0.%lu.%lu.0x00%08lx 0x%08lx 0x%08lx\n",
	       NCP_NODE_ID(region), NCP_TARGET_ID(region), offset, mask, value);

	return;
}

void
ncr_trace_poll(unsigned long region,
	       unsigned long loops, unsigned long delay,
	       unsigned long offset, unsigned long mask, unsigned long value)
{
	printf("ncpPoll -l %lu -t %lu  0.%lu.%lu.0x00%08lx " \
	       "0x%08lx 0x%08lx\n",
	       loops, delay,
	       NCP_NODE_ID(region), NCP_TARGET_ID(region), offset, mask, value);

	return;
}

#define NCR_TRACE_READ8(region, offset) do { \
if (ncr_tracer_is_enabled()) { \
ncr_trace_read8(region, offset); } \
} while (0);
#define NCR_TRACE_READ16(region, offset) do { \
if (ncr_tracer_is_enabled()) { \
ncr_trace_read16(region, offset); } \
} while (0);
#define NCR_TRACE_READ32(region, offset) do { \
if (ncr_tracer_is_enabled()) { \
ncr_trace_read32(region, offset); } \
} while (0);
#define NCR_TRACE_WRITE8(region, offset, value) do { \
if (ncr_tracer_is_enabled()) { \
ncr_trace_write8(region, offset, value); } \
} while (0);
#define NCR_TRACE_WRITE16(region, offset, value) do { \
if (ncr_tracer_is_enabled()) { \
ncr_trace_write16(region, offset, value); } \
} while (0);
#define NCR_TRACE_WRITE32(region, offset, value) do { \
if (ncr_tracer_is_enabled()) { \
ncr_trace_write32(region, offset, value); } \
} while (0);
#define NCR_TRACE_MODIFY(region, offset, mask, value) do { \
if (ncr_tracer_is_enabled()) { \
ncr_trace_modify(region, offset, mask, value); } \
} while (0);
#define NCR_TRACE_POLL(region, loops, delay, offset, mask, value) do { \
if (ncr_tracer_is_enabled()) { \
ncr_trace_poll(region, loops, delay, offset, mask, value); } \
} while (0);
#else
#define NCR_TRACE_READ8(region, offset) {}
#define NCR_TRACE_READ16(region, offset) {}
#define NCR_TRACE_READ32(region, offset) {}
#define NCR_TRACE_WRITE8(region, offset, value) {}
#define NCR_TRACE_WRITE16(region, offset, value) {}
#define NCR_TRACE_WRITE32(region, offset, value) {}
#define NCR_TRACE_MODIFY(region, offset, mask, value) {}
#define NCR_TRACE_POLL(region, loops, delay, offset, mask, value) {}
#endif

/* Note that NCA in this case means nca_axi (0x101.0.0) */

typedef union {
	unsigned long raw;
	struct {
		unsigned long start_done          : 1;
#ifndef ACP_X1V1
		unsigned long                     : 2;
		unsigned long sysmem_access_type  : 4;
#else
		unsigned long                     : 6;
#endif
		unsigned long local_bit           : 1;
		unsigned long status              : 2;
		unsigned long byte_swap_enable    : 1;
		unsigned long cfg_cmpl_int_enable : 1;
		unsigned long cmd_type            : 4;
		unsigned long dbs                 : 16;
	} __attribute__ ( ( packed ) ) bits;
} __attribute__ ( ( packed ) ) command_data_register_0_t;

typedef union {
	unsigned long raw;
	struct {
		unsigned long target_address : 32;
	} __attribute__ ( ( packed ) ) bits;
} __attribute__ ( ( packed ) ) command_data_register_1_t;

typedef union {
	unsigned long raw;
	struct {
		unsigned long                         : 16;
		unsigned long target_node_id          : 8;
		unsigned long target_id_address_upper : 8;
	} __attribute__ ( ( packed ) ) bits;
} __attribute__ ( ( packed ) ) command_data_register_2_t;

/*
  ------------------------------------------------------------------------------
  ncr_register_read
*/

static __inline__ unsigned long
ncr_register_read(unsigned *address)
{
	return in_be32(address);
}

/*
  ----------------------------------------------------------------------
  ncr_register_write
*/

static __inline__ void
ncr_register_write(const unsigned value, unsigned *address)
{
	out_be32(address, value);
}

/*
  ------------------------------------------------------------------------------
  ncr_lock
*/

static int
ncr_lock(int domain)
{
#ifdef ACP3
	unsigned long offset;
	unsigned long value;
	int loops = 400000;

	offset=(0xff80 + (domain * 4));

	do {
		value = in_be32((unsigned *)(NCA + offset));
	} while ((0 != value) && (0 < --loops));

	if (0 == loops)
		return -1;
#endif
	return 0;
}

/*
  ------------------------------------------------------------------------------
  ncr_unlock
*/

static void
ncr_unlock(int domain)
{
#ifdef ACP3
	unsigned long offset;

	offset=(0xff80 + (domain * 4));
	out_be32((unsigned *)(NCA + offset), 0);
#endif
	return;
}

/*
  ======================================================================
  ======================================================================
  Public Interface
  ======================================================================
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  ncr_read
*/

int
ncr_read(unsigned long region, unsigned long address, int number, void *buffer)
{
	command_data_register_0_t cdr0;	/* 0x101.0.0xf0 */
	command_data_register_1_t cdr1;	/* 0x101.0.0xf4 */
	command_data_register_2_t cdr2;	/* 0x101.0.0xf8 */
	int wfc_timeout = WFC_TIMEOUT;

	if (0 != ncr_lock(LOCK_DOMAIN))
		return -1;

	/*
	  Set up the read command.
	*/

	cdr2.raw = 0;

	if( NCP_REGION_ID( 512, 1 ) != region ) {
		cdr2.bits.target_node_id = NCP_NODE_ID( region );
		cdr2.bits.target_id_address_upper = NCP_TARGET_ID( region );
	}

	ncr_register_write( cdr2.raw, ( unsigned * ) ( NCA + 0xf8 ) );

	cdr1.raw = 0;

	if( NCP_REGION_ID( 512, 1 ) == region ) {
		cdr1.bits.target_address = address;
	} else {
		cdr1.bits.target_address = ( address >> 2 );
	}

	ncr_register_write( cdr1.raw, ( unsigned * ) ( NCA + 0xf4 ) );

	cdr0.raw = 0;
	cdr0.bits.start_done = 1;

	if( 0xff == cdr2.bits.target_id_address_upper ) {
		cdr0.bits.local_bit = 1;
	}

	if( NCP_REGION_ID( 512, 1 ) == region ) {
		cdr0.bits.cmd_type = 0xc;
#ifndef ACP_X1V1
		cdr0.bits.sysmem_access_type = 2;
#endif
	} else {
		cdr0.bits.cmd_type = 0x4;
	}

	/* TODO: Verify number... */
	cdr0.bits.dbs = ( number - 1 );
	ncr_register_write( cdr0.raw, ( unsigned * ) ( NCA + 0xf0 ) );

	/*
	  Wait for completion.
	*/

	do {
		--wfc_timeout;
	} while( (0x80000000 ==
		  ( ncr_register_read( ( unsigned * ) ( NCA + 0xf0 ) ) &
		    0x80000000 ) ) &&
		 0 < wfc_timeout);

	if (0 == wfc_timeout) {
		printf("ncr_read(): NCA Lockup!\n");
		ncr_unlock(LOCK_DOMAIN);
		return -1;
	}

	/*
	  Check status.
	*/

	if( 0x3 != ( ( ncr_register_read( ( unsigned * ) ( NCA + 0xf0 ) ) &
		       0x00c00000 ) >> 22 ) ) {
		ncr_unlock(LOCK_DOMAIN);
		return -1;
	}

	/*
	  Read the data into the buffer.
	*/

	if (NULL != buffer) {
		unsigned long address;

		address = (NCA + 0x1000);

		while (4 <= number) {
			*((unsigned long *)buffer) =
				ncr_register_read((unsigned *)address);
			address += 4;
			number -= 4;
			buffer += 4;
		}

		if (0 < number) {
			unsigned long temp;

			temp = ncr_register_read((unsigned *)address);
			memcpy(buffer, (void *)&temp, number);
		}
	}

	ncr_unlock(LOCK_DOMAIN);
	return 0;
}

/*
   ----------------------------------------------------------------------
  ncr_read8
*/

int
ncr_read8(unsigned long region, unsigned long offset, unsigned char *value)
{
	int rc;

	NCR_TRACE_READ8(region, offset);
	rc = ncr_read(region, offset, 1, value);

	if (0 != rc)
		return ncr_fail(__FILE__, __FUNCTION__, __LINE__);

	return 0;
}

/*
   ----------------------------------------------------------------------
  ncr_read16
*/

int
ncr_read16(unsigned long region, unsigned long offset, unsigned short *value)
{
	int rc = 0;

#ifdef ACP_25xx
	int wfc_timeout = WFC_TIMEOUT;

	/*
	  Handle the 0x115.1 node on the AXM25xx.
	*/

	if (NCP_REGION_ID(0x115, 1) == region) {
		unsigned long base;

		base = (IO + 0x3000);

		if (0xffff < offset) {
			printf("Bad Offset!\n");
			return -1;
		}

		WRITEL((0x84c00000 + offset), (base + 4));

		do {
			--wfc_timeout;
			*value = READL(base + 4);
		} while (0 != (*value & 0x80000000) &&
			 0 < wfc_timeout);

		if (0 == wfc_timeout) {
			printf("apb2ser read timed out!\n");
			return -1;
		}

		*value = READL(base + 8);

		return 0;
	}
#endif

	NCR_TRACE_READ16(region, offset);
	rc = ncr_read(region, offset, 2, value);

	if (0 != rc)
		return ncr_fail(__FILE__, __FUNCTION__, __LINE__);

	return 0;
}

/*
  ----------------------------------------------------------------------
  ncr_read32
*/

int
ncr_read32(unsigned long region, unsigned long offset, unsigned long *value)
{
	int rc = 0;

#ifdef ACP_25xx
	int wfc_timeout = WFC_TIMEOUT;

	/*
	  Handle the 0x115.0, 0x115.2, and 0x115.3 nodes on the AXM25xx.
	*/

	if ((NCP_REGION_ID(0x115, 0) == region) ||
	    (NCP_REGION_ID(0x115, 2) == region) ||
	    (NCP_REGION_ID(0x115, 3) == region)) {
		unsigned long base = 0;

		switch (NCP_TARGET_ID(region)) {
		case 0:
			base = (IO + 0x3030);
			break;
		case 2:
			base = (IO + 0x3010);
			break;
		case 3:
			base = (IO + 0x3020);
			break;
		default:
			/* Unreachable, due to the if() above. */
			break;
		}

		if (0xffff < offset)
			return -1;

		WRITEL((0x85400000 + offset), (base + 4));

		do {
			--wfc_timeout;
			*value = READL(base + 4);
		} while (0 != (*value & 0x80000000) &&
			 0 < wfc_timeout);

		if (0 == wfc_timeout) {
			printf("apb2ser read timed out!\n");
			return -1;
		}

		*value = READL(base + 8);

		return 0;
	}
#endif	/* ACP_25xx */

	NCR_TRACE_READ32(region, offset);
	rc = ncr_read(region, offset, 4, value);

	if (0 != rc)
		return ncr_fail(__FILE__, __FUNCTION__, __LINE__);

	return 0;
}


/*
  ------------------------------------------------------------------------------
  ncr_poll
*/

int
ncr_poll( unsigned long region, unsigned long offset,
	  unsigned long mask, unsigned long desired_value,
	  unsigned long delay_time, unsigned long delay_loops )
{
	int i;
	int rc = 0;

	NCR_TRACE_POLL(region, delay_loops, delay_time,
		       offset, mask, desired_value);

	for( i = 0; i < delay_loops; ++ i ) {
		unsigned long value;

		rc |= ncr_read(region, offset, 4, &value);

		if( ( value & mask ) == desired_value ) {
			break;
		}

		udelay( delay_time );
	}

	if( delay_loops == i ) {
		return ncr_fail(__FILE__, __FUNCTION__, __LINE__);
	}

	if (0 != rc)
		return ncr_fail(__FILE__, __FUNCTION__, __LINE__);

	return 0;
}

/*
  ----------------------------------------------------------------------
  ncr_write
*/

int
ncr_write(unsigned long region, unsigned long address, int number, void *buffer)
{
	command_data_register_0_t cdr0;
	command_data_register_1_t cdr1;
	command_data_register_2_t cdr2;
	int dbs = (number - 1);
	int wfc_timeout = WFC_TIMEOUT;

	if (0 != ncr_lock(LOCK_DOMAIN))
		return -1;

	/*
	  Set up the write.
	*/

	cdr2.raw = 0;

	if( NCP_REGION_ID( 512, 1 ) != region ) {
		cdr2.bits.target_node_id = NCP_NODE_ID( region );
		cdr2.bits.target_id_address_upper = NCP_TARGET_ID( region );
	}

	ncr_register_write( cdr2.raw, ( unsigned * ) ( NCA + 0xf8 ) );

	cdr1.raw = 0;

	if( NCP_REGION_ID( 512, 1 ) == region ) {
		cdr1.bits.target_address = address;
	} else {
		cdr1.bits.target_address = ( address >> 2 );
	}

	ncr_register_write( cdr1.raw, ( unsigned * ) ( NCA + 0xf4 ) );

	/*
	  Copy data from the buffer.
	*/

	if (NULL != buffer) {
		unsigned long address;

		address = (NCA + 0x1000);

		while (4 <= number) {
			ncr_register_write(*((unsigned long *)buffer),
					   (unsigned *)address);
			address += 4;
			buffer += 4;
			number -= 4;
		}

		if (0 < number) {
			unsigned long temp;

			memcpy((void *)&temp, buffer, number);
			ncr_register_write(temp, (unsigned *)address);
		}
	}

	/*
	  Write
	*/

	cdr0.raw = 0;
	cdr0.bits.start_done = 1;

	if( 0xff == cdr2.bits.target_id_address_upper ) {
		cdr0.bits.local_bit = 1;
	}

	if( NCP_REGION_ID( 512, 1 ) == region ) {
		cdr0.bits.cmd_type = 0xd;
#ifndef ACP_X1V1
		cdr0.bits.sysmem_access_type = 2;
#endif
	} else {
		cdr0.bits.cmd_type = 0x5;
	}

	/* TODO: Verify number... */
	cdr0.bits.dbs = dbs;
	ncr_register_write( cdr0.raw, ( unsigned * ) ( NCA + 0xf0 ) );

	/*
	  Wait for completion.
	*/

	do {
		--wfc_timeout;
	} while( (0x80000000 ==
		  ( ncr_register_read( ( unsigned * ) ( NCA + 0xf0 ) ) &
		    0x80000000 ) ) &&
		 0 < wfc_timeout);

	if (0 == wfc_timeout) {
		printf("ncr_write(): NCA Lockup!\n");
		ncr_unlock(LOCK_DOMAIN);
		return -1;
	}

	/*
	  Check status.
	*/

	if( 0x3 !=
	    ( ( ncr_register_read( ( unsigned * ) ( NCA + 0xf0 ) ) &
		0x00c00000 ) >> 22 ) ) {
#ifdef NCR_TRACER
		printf( "ncr_write( ) failed: 0x%lx\n",
			( ( ncr_register_read( ( unsigned * ) ( NCA + 0xf0 ) ) &
			    0x00c00000 ) >> 22 ) );
#endif
		ncr_unlock(LOCK_DOMAIN);

		return -1;
	}

	ncr_unlock(LOCK_DOMAIN);
	return 0;
}

/*
  ----------------------------------------------------------------------
  ncr_write8
*/

int
ncr_write8( unsigned long region, unsigned long offset, unsigned char value )
{
	int rc;

	NCR_TRACE_WRITE8(region, offset, value);
	rc = ncr_write(region, offset, 1, &value);

	if (0 != rc)
		return ncr_fail(__FILE__, __FUNCTION__, __LINE__);

	return 0;
}

/*
  ----------------------------------------------------------------------
  ncr_write16
*/

int
ncr_write16( unsigned long region, unsigned long offset, unsigned short value )
{
	int rc;
#ifdef ACP_25xx
	int wfc_timeout = WFC_TIMEOUT;

	/*
	  Handle the 0x115 nodes on AXM25xx
	*/

	if (NCP_REGION_ID(0x115, 1) == region) {
		unsigned long base;

		base = (IO + 0x3000);

		if (0xffff < offset)
			return -1;

		WRITEL(value, base);
		WRITEL((0xc4c00000 + offset), (base + 4));

		do {
			--wfc_timeout;
			value = READL(base + 4);
		} while (0 != (value & 0x80000000) &&
			 0 < wfc_timeout);

		if (0 == wfc_timeout) {
			printf("apb2ser write timed out!\n");
			return -1;
		}

		return 0;
	}
#endif

	NCR_TRACE_WRITE16(region, offset, value);
	rc = ncr_write(region, offset, 2, &value);

	if (0 != rc)
		return ncr_fail(__FILE__, __FUNCTION__, __LINE__);

	return 0;
}

/*
  ----------------------------------------------------------------------
  ncr_write32
*/

int
ncr_write32(unsigned long region, unsigned long offset, unsigned long value)
{
	int rc;
#ifdef ACP_25xx
	int wfc_timeout = WFC_TIMEOUT;

	/*
	  Handle the 0x115 nodes on AXM25xx
	*/

	if ((NCP_REGION_ID(0x115, 0) == region) ||
	    (NCP_REGION_ID(0x115, 2) == region) ||
	    (NCP_REGION_ID(0x115, 3) == region)) {
		unsigned long base = 0;

		switch (NCP_TARGET_ID(region)) {
		case 0:
			base = (IO + 0x3030);
			break;
		case 2:
			base = (IO + 0x3010);
			break;
		case 3:
			base = (IO + 0x3020);
			break;
		default:
			/* Unreachable, due to the if() above. */
			break;
		}

		if (0xffff < offset)
			return -1;

		WRITEL(value, base);
		WRITEL((0xc5400000 + offset), (base + 4));

		do {
			--wfc_timeout;
			value = READL(base + 4);
		} while (0 != (value & 0x80000000) &&
			 0 < wfc_timeout);

		if (0 == wfc_timeout) {
			printf("apb2ser write timed out!\n");
			return -1;
		}

		return 0;
	}
#endif	/* ACP_25xx */

	NCR_TRACE_WRITE32(region, offset, value);
	rc = ncr_write(region, offset, 4, &value);

	if (0 != rc)
		return ncr_fail(__FILE__, __FUNCTION__, __LINE__);

	return 0;
}

/*
  ------------------------------------------------------------------------------
  ncr_and
*/

int
ncr_and( unsigned long region, unsigned long offset, unsigned long value )
{
	unsigned long temp;
	int rc = 0;

	rc |= ncr_read(region, offset, 4, &temp);
	temp &= value;
	rc |= ncr_write(region, offset, 4, &temp);

	if (0 != rc)
		return ncr_fail(__FILE__, __FUNCTION__, __LINE__);

	return 0;
}

/*
  ------------------------------------------------------------------------------
  ncr_or
*/

int
ncr_or( unsigned long region, unsigned long offset, unsigned long value )
{
	unsigned long temp;
	int rc = 0;

	rc |= ncr_read(region, offset, 4, &temp);
	temp |= value;
	rc |= ncr_write(region, offset, 4, &temp);

	if (0 != rc)
		return ncr_fail(__FILE__, __FUNCTION__, __LINE__);

	return 0;
}

/*
  ----------------------------------------------------------------------
  ncr_modify
*/

int
ncr_modify(unsigned long region, unsigned long address, int count,
	   void *masks, void *values)
{
	command_data_register_0_t cdr0;
	command_data_register_1_t cdr1;
	command_data_register_2_t cdr2;
	unsigned long data_word_base;
	int wfc_timeout = WFC_TIMEOUT;

	if (0 != ncr_lock(LOCK_DOMAIN))
		return -1;

	/*
	  Set up the write.
	*/

	cdr2.raw = 0;

	if( NCP_REGION_ID( 512, 1 ) != region ) {
		cdr2.bits.target_node_id = NCP_NODE_ID( region );
		cdr2.bits.target_id_address_upper = NCP_TARGET_ID( region );
	}

	ncr_register_write( cdr2.raw, ( unsigned * ) ( NCA + 0xf8 ) );

	cdr1.raw = 0;

	if( NCP_REGION_ID( 512, 1 ) == region ) {
		cdr1.bits.target_address = address;
	} else {
		cdr1.bits.target_address = ( address >> 2 );
	}

	ncr_register_write( cdr1.raw, ( unsigned * ) ( NCA + 0xf4 ) );

	/*
	  Copy from buffer to the data words.
	*/

	data_word_base = ( NCA + 0x1000 );
	ncr_register_write( count, ( unsigned * ) data_word_base );
	data_word_base += 4;

	while( 0 < count ) {
		ncr_register_write( * ( ( unsigned long * ) masks ),
				    ( unsigned * ) data_word_base );
		data_word_base += 4;
		ncr_register_write( * ( ( unsigned long * ) values ),
				    ( unsigned * ) data_word_base );
		data_word_base += 4;
		masks += 4;
		values += 4;
		-- count;
	}

	cdr0.raw = 0;
	cdr0.bits.start_done = 1;

	if( 0xff == cdr2.bits.target_id_address_upper ) {
		cdr0.bits.local_bit = 1;
	}

	cdr0.bits.cmd_type = 0x8;

	ncr_register_write( cdr0.raw, ( unsigned * ) ( NCA + 0xf0 ) );

	/*
	  Wait for completion.
	*/

	do {
		--wfc_timeout;
	} while( (0x80000000 ==
		  ( ncr_register_read( ( unsigned * ) ( NCA + 0xf0 ) ) &
		    0x80000000 ) ) &&
		 0 < wfc_timeout);

	if (0 == wfc_timeout) {
		printf("ncr_modify(): NCA Lockup!\n");
		ncr_unlock(LOCK_DOMAIN);
		return -1;
	}

	/*
	  Check status.
	*/

	if( 0x3 !=
	    ( ( ncr_register_read( ( unsigned * ) ( NCA + 0xf0 ) ) &
		0x00c00000 ) >> 22 ) ) {
#ifdef NCR_TRACER
		printf( "ncr_write( ) failed: 0x%lx\n",
			( ( ncr_register_read( ( unsigned * ) ( NCA + 0xf0 ) ) &
			    0x00c00000 ) >> 22 ) );
#endif
		ncr_unlock(LOCK_DOMAIN);
		return -1;
	}

	ncr_unlock(LOCK_DOMAIN);
	return 0;
}

/*
  ----------------------------------------------------------------------
  ncp_modify32
*/

int
ncr_modify32( unsigned long region, unsigned long offset,
	      unsigned long mask, unsigned long value )
{
	int rc;

	NCR_TRACE_MODIFY(region, offset, mask, value);
	rc = ncr_modify( region, offset, 1, & mask, & value );

	if (0 != rc)
		return ncr_fail(__FILE__, __FUNCTION__, __LINE__);

	return 0;
}
